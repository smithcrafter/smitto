#!/bin/bash

cd ../
mkdir ./Build
cd ./Build
mkdir Smitto-Core
cd ./Smitto-Core
make clean
QT_SELECT=qt5 qmake ../../Smitto-core.pro
make -j4
