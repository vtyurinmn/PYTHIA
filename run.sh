#!/bin/bash

./build.sh

docker run --rm -it --name=pythia-dev pythia:dev