#!/bin/bash

cd ./Builds/LinuxMakefile/
make -j2
cd ../../

bash install.sh
