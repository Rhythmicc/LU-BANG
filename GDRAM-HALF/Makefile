all:
	cncc -O3 --bang-mlu-arch=MLU270 gdram_half.mlu -o dist/gdram_half.o
	gcc -O3 dist/gdram_half.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/GDRAM-HALF
clean:
	rm dist/*.o
	rm dist/GDRAM-HALF
