all: main.c
	gcc main.c -o invmat -pthread -DLIKWID_PERFMON -I/home/soft/likwid/include -L/home/soft/likwid/lib -llikwid -lm -O3 -mavx -march=native

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
