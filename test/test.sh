#!/bin/bash

GREEN="\033[32m"
RESET="\033[0m"
ALIVE_TIME=1

execute() {
	(./cub3D $1 2>$2) & sleep ${ALIVE_TIME}

	if [ -s $2 ]; then
		echo -e "${GREEN}[[${2}]]${RESET}\nOK"
	else
		echo -e "${GREEN}[[${2}]]${RESET}\nNG"
	fi
	rm $2
}

cubfiles=`find ./cubfiles -name "error*"`
for filepath in $cubfiles; do
	NAME=`basename $filepath`
	execute $filepath $NAME &
done
wait
killall cub3D 2>/dev/null
echo -n
