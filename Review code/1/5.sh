#!/bin/bash
echo "Hello $USER"
# ten cua os
echo "OS name: $(uname -s)"
# id 
echo "$(id -g)"
#date
echo "$(date)"
#show
ls -la
echo $TERM
echo $PATH
echo $HOME
echo "Goodbye $(date)"