#!/bin/sh

rm final_files/*

cp -v top_and_bottom/ecg-Front.* final_files
cp -v top_and_bottom/ecg-Back.* final_files
cp -v top_and_bottom/ecg-Mask_Front.* final_files
cp -v top_and_bottom/ecg-Mask_Back.* final_files
cp -v top_and_bottom/ecg-SoldP_Back.* final_files
cp -v top_and_bottom/ecg-SoldP_Front.* final_files

cp -v inner_layers/ecg-Power.* final_files
cp -v inner_layers/ecg-Ground.* final_files
cp -v inner_layers/ecg-Signal1.* final_files
cp -v inner_layers/ecg-Signal2.* final_files
cp -v inner_layers/ecg-PCB_Edges.* final_files
cp -v inner_layers/ecg-NPTH.drl final_files
cp -v inner_layers/ecg.drl final_files

