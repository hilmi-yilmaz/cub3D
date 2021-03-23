#!/bin/bash

# This script runs "make" or "make fclean" for linux

if [[ "$1" == "fclean" ]]; then
    make fclean IS_LINUX=1
elif [[ "$1" == "" ]]; then
    make IS_LINUX=1 && ./exec scenes/incorrect/wrong_format_5.cub
else
    echo "Run script as: ./run.sh [fclean]."
    exit 1
fi