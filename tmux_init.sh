#!/bin/bash

# Project directory
DIR="/home/hilmi/Desktop/codam/curriculum/cub3d/"

# To be used text editor
TEXT_EDITOR="vim"

# Source files to open for $SRC_WINDOW
file_0_0="v1_raycaster/raycaster_init.c"    # file to open at window 0, pane 0
file_0_1="v1_raycaster/intersections.c"     # file to open at window 0, pane 1
file_0_2="v1_raycaster/checks.c"
file_0_4="v1_raycaster/hooks.c"
file_0_5="v1_raycaster/raycaster_utils.c"
file_1_0="cub3d.h"
file_1_1="Makefile"

# Session name
SESSION="cub3d"

# Source and includes window
SRC_WINDOW="src"            # this is the zeroth window (0)
INCL_WINDOW="incl"          # this is the first window (1)

# Source window looks like below. Each number represents the pane ID.
#   |-----|-----|-----|
#   |  0  |  1  |  2  |
#   |-----|-----|-----|
#   |  5  |  4  |  3  |
#   |-----|-----|-----|

# The includes window looks like:
#   |-----|-----|
#   |  0  |  1  |
#   |-----|-----|

# Create a new session called $SESSION with a window called $SRC_WINDOW
tmux new -s $SESSION -d -n "srcs"
tmux send-keys -t $SESSION:0 "$TEXT_EDITOR $file_0_0" Enter

# Create 6 panes for $SRC_WINDOW
tmux split-window -h -t $SESSION:0
tmux send-keys -t $SESSION:0 "$TEXT_EDITOR $file_0_1" Enter
tmux split-window -h -t $SESSION:0
tmux send-keys -t $SESSION:0 "$TEXT_EDITOR $file_0_2" Enter
tmux select-layout -t $SESSION:0 even-horizontal
tmux split-window -v -t $SESSION:0
tmux selectp -t 1
tmux split-window -v -t $SESSION:0
tmux send-keys -t $SESSION:0 "$TEXT_EDITOR $file_0_4" Enter
tmux selectp -t 0
tmux split-window -v -t $SESSION:0
tmux send-keys -t $SESSION:0 "$TEXT_EDITOR $file_0_5" Enter

# Create another window called $INCL_WINDOW for includes and makefiles
tmux new-window -n "incl" -t $SESSION
tmux send-keys -t $SESSION:1 "$TEXT_EDITOR $file_1_0" Enter
tmux split-window -h -t $SESSION:1
tmux send-keys -t $SESSION:1 "$TEXT_EDITOR $file_1_1" Enter

# Fill the panes with vim editors
#tmux send-keys -t $SESSION:0.0 "$TEXT_EDITOR $file_0_0" Enter
#tmux send-keys -t $SESSION:0.1 "$TEXT_EDITOR $file_0_1" Enter
#tmux send-keys -t $SESSION:0.2 "$TEXT_EDITOR $file_0_2" Enter
#tmux send-keys -t $SESSION:0.4 "$TEXT_EDITOR $file_0_4" Enter
#tmux send-keys -t $SESSION:0.5 "$TEXT_EDITOR $file_0_5" Enter
#tmux send-keys -t $SESSION:1.0 "$TEXT_EDITOR $file_1_0" Enter
#tmux send-keys -t $SESSION:1.1 "$TEXT_EDITOR $file_1_1" Enter

# Create an extra  window
tmux new-window -n "extra" -t $SESSION

# Attach to the session
tmux attach -t $SESSION
