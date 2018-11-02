#!/usr/bin/env sh

wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz -O googletest.tar.gz
tar -zxvf googletest.tar.gz
mkdir googletest-release-1.8.0/build
cd googletest-release-1.8.0/build
sudo cmake ..
sudo make
sudo make install
cd -
