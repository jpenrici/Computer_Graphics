#!/bin/bash

make

echo "test ..."
./dptcc argv[1] argv[2]
./dptcc argv[1]
./dptcc
./dptcc /directory/images

echo "gui ..."
./dptcc --gui

make clean