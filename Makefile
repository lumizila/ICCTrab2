all: main.c
	gcc main.c -o invmat -DLIKWID_PERFMON -I/home/local/likwid/include -L/home/local/likwid/lib -llikwid -lm -O3 -mavx -march=native

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
