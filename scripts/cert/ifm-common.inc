#############################################################################
# int dio_loop_test() - loop based test for DIO pins on the industrial
# terminal block connector or IFM-DIxOx modules
# DIO_INx pins are connected to DIO_OUTx correspondingly, so setting a value on
# a DIO_OUTx causes a corresponding DIO_INx get the same value
# Use dioset/dioget utilities for setting values to DIO_OUTs and getting from DIO_INs
#############################################################################
function dio_loop_test() {
	local slot=${1}
	local loops=${2}
	# Array of DIs:
	declare -a DI_ARR=($(seq 0 $((loops-1))))
	# Array of DOs
	declare -a DO_ARR=($(seq 0 $((loops-1))))
	# Array of OUT values to be set
	declare -a VAL_ARR=(1 0 1 0)
	local ret=0
	for j in $(seq 0 $(( ${#DO_ARR[@]} - 1))) ; do
		for _v in ${VAL_ARR[@]} ; do
			# Use dioget/dioset utilities
			${DIN_LIB_HOME}/${DIO_SET} -m ${slot} ${DO_ARR[${j}]} ${_v}
			ret=$(${DIN_LIB_HOME}/${DIO_GET} -m ${slot} ${DI_ARR[${j}]})
			if [[ ${_v} -ne ${ret} ]]; then
				return 1;
			fi
		done
	done
	return 0;
}

#############################################################################
# int ping_pong_tty_test() - loop-back based communication test for industrial
# terminal block connector pins or IFM-RSxxx modules
# Sends pre-defined messages from tty_ping to tty_pong and back (ping-pong like)
# and checks received message correctness
#############################################################################
function ping_pong_tty_test() {
# A receiver side for a given sender side
declare -A PING_PONG_RECEIVER=(
		[ping]="pong"
		[pong]="ping"
	)
	local btest=${1:-"ping"}
	local etest=${2:-"pong"}
	for tty in ${btest} ${etest} ; do
		devtty=tty_${tty}
		[[ -c $(readlink -f /dev/${!devtty}) ]] || return 1
		stty -F /dev/${!devtty} ${serial_speed} ${serial_opts} # Setup tty
		timeout 1 cat /dev/${!devtty} &>/dev/null # Clean pipe
	done
	ping_pong_tty_out=${CERT_TEST_OUTPUT}/ping_pong_tty_out.log # Prepare log filename for output
	for sender in ${btest} ${etest} ; do
		: > ${ping_pong_tty_out} # Cleanup log file
		## 1.2. Evaluate sender and receiver sides
		tty_sender=tty_${sender}
		receiver=${PING_PONG_RECEIVER[${sender}]}
		tty_receiver=tty_${receiver}
		## 1.3. Evaluate msg to be sent
		local msg=${sender^}
		smsg="${!msg}"
		info_msg "${sender^^} test: testing [${!tty_sender}] ==> [${!tty_receiver}] loop..."
		cat /dev/${!tty_receiver} > ${ping_pong_tty_out} & pid=$! # Read tty_receiver
		sleep 0.5
		echo -en "${smsg}" > /dev/${!tty_sender} # Send pattern via tty_sender
		sleep 0.7
		## 2.3. Stop getting data from the tty_receiver
		sync
		kill -15 ${pid}
		wait ${pid} &> /dev/null
		rmsg=$(cat ${ping_pong_tty_out}) # Read received data into variable
		# Remove output file
		rm ${ping_pong_tty_out}
		if [[ "${rmsg}" != "$(echo -ne "${smsg}")" ]]; then
			return 1;
		fi
	done
	return 0;
}
