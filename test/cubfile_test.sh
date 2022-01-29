#!/bin/bash

GREEN="\033[32m"
RESET="\033[0m"

execute() {
	echo -e $GREEN "<" $1 ">"$RESET
	./testcubfile.out $1
	echo
}


UTILS="../src/utils/*.c"
CUBFILE=" ../src/cubfile/get_color.c"
CUBFILE+=" ../src/cubfile/read_file.c"
CUBFILE+=" ../src/cubfile/init_player.c"
CUBFILE+=" ../src/cubfile/validate_map.c"
CUBFILE+=" ../src/cubfile/skip_empty_line.c"
CUBFILE+=" ../src/cubfile/get_path_to_texture.c"
CUBFILE+=" ../src/cubfile/init_cubfile.c"
CUBFILE+=" ../src/cubfile/init_player_dir.c"
CUBFILE+=" ../src/cubfile/init_player_pos.c"

gcc -Wall -Wextra -Werror -g -I../include/ cubfile_test.c $UTILS $CUBFILE -o testcubfile.out

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
