#!/bin/bash

CSV_NAME="./analyse/benchmark_tuxedo_martin"

# Correction: Utiliser ${CSV_NAME} avec la commande date
CSV_NAME="${CSV_NAME}_$(date +%Y%m%d)"

(
  cd ./build || exit 1
  make
)

# Exécution du programme
./build/tme5 --nb_de_sphere=100000 --scene_size=100 --csv_name="$CSV_NAME"
./build/tme5 --nb_de_sphere=10000 --scene_size=100 --csv_name="$CSV_NAME"
./build/tme5 --nb_de_sphere=1000 --scene_size=1000 --csv_name="$CSV_NAME"
./build/tme5 --nb_de_sphere=10 --scene_size=1000 --csv_name="$CSV_NAME"


python3 analyse.py
