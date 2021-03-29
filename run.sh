#!/bin/bash

# This script runs "make" or "make fclean" for linux

if [[ "$1" == "fclean" ]]; then
    make fclean IS_LINUX=1
elif [[ "$1" == "valgrind" ]]; then
	make IS_LINUX=1 VALGRIND=1
elif [[ "$1" == "" ]]; then
    make IS_LINUX=1 && ./exec scenes/correct/basic.cub
	#make IS_LINUX=1 && ./exec scenes/correct/basic.cub
else
    echo "Run script as: ./run.sh [fclean]."
    exit 1
fi

# If valgrind is selected, run it
if [[ "$1" == "valgrind" ]]; then
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec scenes/correct/basic.cub
fi