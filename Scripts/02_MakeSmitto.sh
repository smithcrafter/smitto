#!/bin/bash

cd ../
mkdir ./Build
cd ./Build
mkdir Smitto
cd ./Smitto
make clean
QT_SELECT=qt5 qmake ../../Smitto.pro
make -j4
