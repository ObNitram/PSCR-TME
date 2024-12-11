#!/bin/bash



CSV_NAME="./analyse/benchmark_tuxedo_martin_v2"


(
  cd ./build
  make
)


# Exécution du programme

./build/tme5 --nb_de_sphere=100000 --scene_size=100 --csv_name=$CSV_NAME
./build/tme5 --nb_de_sphere=10000 --scene_size=100 --csv_name=$CSV_NAME
./build/tme5 --nb_de_sphere=1000 --scene_size=1000 --csv_name=$CSV_NAME
./build/tme5 --nb_de_sphere=10 --scene_size=1000 --csv_name=$CSV_NAME


python3 analyse.py
