all: main.c
	gcc main.c -o invmat -DLIKWID_PERFMON -I/home/soft/likwid/include -L/home/soft/likwid/lib -llikwid -lm -Wall -O3 -mavx -march=native

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
