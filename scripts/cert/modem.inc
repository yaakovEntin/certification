READ_PID=
#############################################################################
# int initialize_the_modem_TTY_device() - initialises the modem TTY device
# The tty configuration is stored in the MODEM_TTY_CFG global variable
#############################################################################
function initialize_the_modem_TTY_device() {
	# Verify the modem TTY device exists
	if [[ ! -c  ${at_modem} ]]; then
		return 1;
	fi
	stty -F ${at_modem} ${at_modem_speed} ${at_modem_opts} ; rval=$? # Configure a Modem TTY device
	sleep ${at_test_modem_timeout}
	return ${rval};
}

#############################################################################
# int Spawn_reading_process() - reads an output from the modem
# The output file name is stored in the MODEM_OUTPUT global variable
#############################################################################
function Spawn_reading_process() {
	cat ${at_modem} > ${at_test_output} &
	READ_PID=$!
	sleep ${at_test_modem_timeout}
}

function Write_AT_command_to_the_Modem_TTY_device() {
	local AT_COMMAND=${1:-"AT"}
	echo -e "${AT_COMMAND}\r" > ${at_modem}
	sleep ${at_test_modem_timeout}
}

function modem_query_status() {
	local __retval=$1
	local local_retval=0
	ret=`grep -c "OK" ${at_test_output}` # Check output file
	if [[ ${ret} -eq 0 ]]; then
		local_retval=1
	fi
	# Propagate the return value to the external variable
	eval $__retval="'$local_retval'"
}

#############################################################################
# int modem_query_at_port(str at_cmd) - sends generic AT command to the modem
# @at_cmd: AT command; If not set the func sends 'AT" test command
# The command output is written to a temp file which name is stored in
# MODEM_OUTPUT global variable. It's a caller responsibility to parse the
# output file for any data of interest.
# Returns 0 in case of success, 1 otherwise
#############################################################################
function modem_query_at_port() {
	local AT_COMMAND=${1:-${AT_DEFAULT_CMD}}
	local check_status=${2:-0}
	local ret=0
	Spawn_reading_process
	Write_AT_command_to_the_Modem_TTY_device ${AT_COMMAND}
	kill -9 ${READ_PID} > /dev/null
#	wait ${READ_PID} 2> /dev/null
	if [[ ${check_status} -ne 0 ]] ; then
		modem_query_status ret
	fi
	return ${ret};
}
