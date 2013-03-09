#!/usr/bin/env bash

NUM_CORES=$(cat /proc/cpuinfo | grep processor | wc -l)
make clean && make -j $NUM_CORES
read -p "Code built; press enter to deploy"

make deploy
read -p "Code deployed; press enter to start monitoring"

socat UDP4-RECV:6666 STDOUT
