all: main.c
	gcc main.c -o invmat -llikwid -lm -Wall -O3 -mavx -march=native

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
