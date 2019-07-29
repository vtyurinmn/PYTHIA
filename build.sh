#!/bin/bash

docker build -t pythia8243:dev .

if [ $(docker images | grep '<none>' | wc -l) -ne 0 ]
then
    echo "Cleaning..."
    docker rmi $(docker images | grep '<none>' | awk '{ print $3 }')
fi