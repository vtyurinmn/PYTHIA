#!/bin/bash

mkdir -p /data/$HOSTNAME/

touch /data/$HOSTNAME/Double_Jpsi_DPS.lhe
ln -s /data/$HOSTNAME/Double_Jpsi_DPS.lhe Double_Jpsi_DPS.lhe

./main201
