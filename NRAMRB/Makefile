all:
	cncc -O3 --bang-mlu-arch=MLU270 nramrb.mlu -o dist/nramrb.o
	gcc -O3 dist/nramrb.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAMRB
clean:
	rm dist/*.o
	rm dist/NRAMRB
