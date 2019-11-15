#!/bin/bash

read -p " What folder should be backed up: " folder
read -p " What type of files should be backed up: " suffix

echo "$folder.$suffix"
