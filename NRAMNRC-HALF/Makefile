all:
	cncc -O3 --bang-mlu-arch=MLU270 nramnrc.mlu -o dist/nramnrc.o
	gcc -O3 dist/nramnrc.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAMNRC-HALF
clean:
	rm dist/*.o
	rm dist/NRAMNRC-HALF
