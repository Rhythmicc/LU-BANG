all:
	cncc -O3 --bang-mlu-arch=MLU270 nramnrs_1.mlu -o dist/nramnrs_1.o
	cncc -O3 --bang-mlu-arch=MLU270 nramnrs_2.mlu -o dist/nramnrs_2.o
	gcc -O3 dist/nramnrs_1.o dist/nramnrs_2.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAMNRS
clean:
	rm dist/*.o
	rm dist/NRAMNRS
