#!/bin/bash

mkdir -p ../Build/Smitto-Core
cd ../Build/Smitto-Core

QT_SELECT=qt5 qmake ../../Smitto-core.pro
make -j4
