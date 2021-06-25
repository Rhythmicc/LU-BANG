all:
	cncc -O3 --bang-mlu-arch=MLU270 nram.mlu -o dist/nram.o
	gcc -O3 dist/nram.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAM
clean:
	rm dist/*.o
	rm dist/NRAM
