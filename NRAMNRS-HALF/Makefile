all:
	cncc -O3 --bang-mlu-arch=MLU270 nramnrs_1_half.mlu -o dist/nramnrs_1_half.o
	cncc -O3 --bang-mlu-arch=MLU270 nramnrs_2_half.mlu -o dist/nramnrs_2_half.o
	gcc -O3 dist/nramnrs_1_half.o dist/nramnrs_2_half.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/NRAMNRS-HALF
clean:
	rm dist/*.o
	rm dist/NRAMNRS-HALF
