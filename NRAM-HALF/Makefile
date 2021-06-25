all:
	cncc -O3 --bang-mlu-arch=MLU270 nram-half.mlu -o dist/nram-half.o
	gcc -O3 dist/nram-half.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAM-HALF
clean:
	rm dist/*.o
	rm dist/NRAM-HALF
