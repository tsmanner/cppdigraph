#!/usr/bin/env sh

wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz -O googletest.tar.gz
tar -zxvf googletest.tar.gz
cd googletest-release-1.8.0/googletest
sudo cmake .
sudo make
sudo mv libg* /usr/lib/
sudo cp include/gtest/ /usr/include/ -rf
cd -
cd googletest-release-1.8.0/googlemock
sudo cmake .
sudo make
sudo mv libg* /usr/lib/
sudo cp include/gmock/ /usr/include/ -rf
cd -