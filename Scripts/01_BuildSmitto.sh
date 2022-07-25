#!/bin/bash

mkdir -p ../Build/Smitto
cd ../Build/Smitto

QT_SELECT=qt5 qmake ../../Smitto.pro
make -j4
