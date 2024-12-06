

# lib

# TME4
voir le fichier banque


# TME5
graphique avec analyse 

# TME6


# TME7
## prod_cons : tp7
```bash
cd TME7/
./cmake-build-debug/tme7_prod_cons producer
./cmake-build-debug/tme7_prod_cons consumer
```

## pipe : tp7
```bash
/bin/cat src/pipe/pipe.cpp | /bin/wc -l

valgrind ./cmake-build-debug/tme7_pipe  /bin/cat src/pipe/pipe.cpp "|" /bin/wc -l
```

