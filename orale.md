

# lib

# prod_cons : tp7

# pipe : tp7

```bash
/bin/cat src/pipe/pipe.cpp | /bin/wc -l

valgrind ./cmake-build-debug/tme7_pipe  /bin/cat src/pipe/pipe.cpp "|" /bin/wc -l
```