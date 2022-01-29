#!/bin/bash

GREEN="\033[32m"
RESET="\033[0m"

execute() {
	echo -e $GREEN "<" $1 ">"$RESET
	./testcubfile.out $1
	echo
}

gcc -Wall -Wextra -Werror -g -I../include/ cubfile_test.c ../src/utils/* ../src/cubfile/read_file.c ../src/cubfile/init_cubfile.c ../src/cubfile/validate_map.c ../src/cubfile/is_player_pos.c -o testcubfile.out

if [ $? != 0 ]; then
	exit 1;
fi

while getopts e OPT
do
  case $OPT in
     e) exit 0;;
  esac
done

cubfiles="../cubfiles/*"
for filepath in $cubfiles; do
	execute $filepath
done

rm testcubfile.out
