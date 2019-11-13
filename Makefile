all: confine

confine: confine.c
	gcc -g -O $< -o $@
