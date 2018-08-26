#!/bin/bash

echo "compile and execute..."
# g++ -std=c++17 image_processing.cpp -o image_processing

# use cmake
./run image_processing.cpp

# test [argc, argv]
# echo "test 1 ..."
# ./image_processing 1 2 3                        ; echo      # usage ...
# ./image_processing 1 2                          ; echo      # ignore
# ./image_processing 1                            ; echo      # ignore
# ./image_processing                              ; echo      # is empty
# ./image_processing -png                         ; echo      # ignore
# ./image_processing --PNG                        ; echo      # is empty
# ./image_processing --JPG                        ; echo      # is empty
# ./image_processing /directory/images            ; echo      # ignore

# echo "test 2 ..."
# ./image_processing --PNG images                 ; echo      # list
# ./image_processing --JPG images                 ; echo      # list

# echo "test 3 ..."
# ./image_processing /original/leaf_diseases.svg          ; echo      # ignore
# ./image_processing /original/leaf_diseases.jpg          ; echo      # ignore
# ./image_processing --PNG /original/leaf_diseases.jpg    ; echo      # ignore

# echo "test 4 ..."
./image_processing images