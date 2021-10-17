#!/bin/bash

# This script runs "make" for linux or macos.
# Two arguments:
# 1: Scene file
# 2: memory tool either asan or valgrind.

# Run like: ./run.sh  [clean|fclean|re] [scene_file.cub] [valgrind|asan]

OS="$(uname)"

if [[ "$OS" == "Linux" ]]; then
	

	if [[ "$1" == "clean" ]]; then
		make __LINUX__=1 clean
		exit 0
	elif [[ "$1" == "fclean" ]]; then
		make __LINUX__=1 fclean
		exit 0
	elif [[ "$1" == "re" ]]; then
		make __LINUX__=1 re
		exit 0
	fi

	if [[ "$2" == "valgrind" ]]; then
		echo "Running: make __LINUX__=1 VALGRIND=1 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec $1"
		make __LINUX__=1 VALGRIND=1 && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec "$1"
	elif [[ "$2" == "asan" ]]; then
		echo "Running: make __LINUX__=1 ASAN=1 && ./exec $1"
		make __LINUX__=1 ASAN=1 && ./exec "$1"
	elif [[ "$2" == "" ]]; then
		echo "Running: make __LINUX__=1 && ./exec $1"
		make __LINUX__=1 && ./exec "$1"
	else
		echo "Run like: ./run.sh scene_file.cub [valgrind|asan] [clean] [fclean]"
	fi

else

	if [[ "$1" == "clean" ]]; then
		make clean
		exit 0
	elif [[ "$1" == "fclean" ]]; then
		make fclean
		exit 0
	elif [[ "$1" == "re" ]]; then
		make re
		exit 0
	fi

	if [[ "$2" == "asan" ]]; then
		echo "Running: make ASAN=1 && ./exec $1"
		make ASAN=1 && ./exec "$1"
	elif [[ "$2" == "" ]]; then
		echo "Running: make && ./exec $1"
		make && ./exec "$1"
	else
		echo "Run like: ./run.sh scene_file.cub [valgrind|asan] [clean] [fclean]"
	fi
fi