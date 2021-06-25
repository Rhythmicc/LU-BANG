all:
	cncc -O3 --bang-mlu-arch=MLU270 gdram.mlu -o dist/gdram.o
	gcc -O3 dist/gdram.o main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/GDRAM
clean:
	rm dist/*.o
	rm dist/GDRAM
