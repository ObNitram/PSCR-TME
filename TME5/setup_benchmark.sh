#!/bin/bash

# Setup build
(
  rm -rf build
  mkdir build
  cd build || exit 1
  cmake -DCMAKE_BUILD_TYPE=Release ..
  make
  echo "Build done"
)

# Setup python
(
  if [ ! -d "venv" ]; then
    python3 -m venv venv
  fi
  source venv/bin/activate
  pip install -r requirements.txt
  echo "Python setup done"
)

echo "Setup done"