all:
	cncc -O3 --bang-mlu-arch=MLU270 nramrb-half.mlu -o dist/nramrb-half.o
	gcc -O3 dist/nramrb-half.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAMRB-HALF
clean:
	rm dist/*.o
	rm dist/NRAMRB-HALF
