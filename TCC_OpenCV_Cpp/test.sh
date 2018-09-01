#!/bin/bash

make

echo "test ..."

echo "./dptcc argv[1] argv[2]"
./dptcc argv[1] argv[2]

echo "./dptcc argv[1]"
./dptcc argv[1]

echo "./dptcc"
./dptcc

echo "./dptcc /directory/images"
./dptcc /directory/images

echo "gui ..."
./dptcc --gui

# make clean