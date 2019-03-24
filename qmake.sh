#!/bin/bash

##
# Script for createing the make file with qmake and building it with make
##

qmake player.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
make -j4
