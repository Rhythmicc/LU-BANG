all:
	gcc -O3  main.c ../include/cu2bang_util.c -I $(NEUWARE)/include -L $(NEUWARE)/lib64 -I ../include -lcnrt -lm -o dist/CPU
clean:
	rm dist/*.o
	rm dist/CPU
