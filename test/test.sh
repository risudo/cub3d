#!/bin/bash

GREEN="\033[32m"
RESET="\033[0m"
ALIVE_TIME=2

execute() {
	LOG="${2}.log"
	rm -f $LOG
	(./cub3D $1 2>${LOG}) & sleep ${ALIVE_TIME}

	if [ -s $LOG ]; then
		echo -e "${GREEN}[[ ${2} ]]${RESET}\nOK\n"
	else
		echo -e "${GREEN}[[ ${2} ]]${RESET}\nNG\n"
	fi
}

cubfiles=`find ./cubfiles -name "error*"`
for filepath in $cubfiles; do
	NAME=`basename $filepath`
	execute $filepath $NAME &
done
execute "no_such_file.cub" "no_such_file"
execute 2>/dev/null
wait
killall cub3D 2>/dev/null

rm -f log.txt
for filepath in $cubfiles; do
	NAME=`basename $filepath`
	LOG="${NAME}.log"
	echo -e "$GREEN [[ ${LOG} ]] $RESET" >> log.txt
	cat $LOG >> log.txt
	echo >> log.txt
	rm $LOG
done
rm .log no_such_file.log
