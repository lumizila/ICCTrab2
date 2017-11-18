all: main.c
	gcc main.c -o invmat -pthread -DLIKWID_PERFMON -I/home/adolfo/likwid/include -L/home/adolfo/likwid/lib -llikwid -lm -O3 -mavx -march=native

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
