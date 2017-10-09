all: main.c
	gcc main.c -o invmat -lm -Wall

doc: 
	doxygen; 

clean:
	rm invmat; rm -r "html"
