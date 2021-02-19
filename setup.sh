#!/bin/sh

sudo apt -y update
sudo apt -y install git g++ make cmake libssl-dev openssl

mkdir vendor
cd vendor

git clone -b master https://github.com/chriskohlhoff/asio.git
cd asio/asio
./autogen.sh
./configure
make
sudo make install

cd ../..

git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j
sudo make install
cd ../..