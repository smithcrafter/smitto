#!/bin/bash

sudo ln -s $PWD/../Lib/libSmitto.so.0 /usr/local/lib/libSmitto.so.0
sudo ln -s $PWD/../Lib/libSmitto.so /usr/local/lib/libSmitto.so
sudo ln -s $PWD/../Lib/libSmitto-core.so.0 /usr/local/lib/libSmitto-core.so.0
sudo ln -s $PWD/../Lib/libSmitto-core.so /usr/local/lib/libSmitto-core.so 
sudo ldconfig
