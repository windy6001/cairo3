cairo3 : cairo3.c
	gcc -o cairo3 cairo3.c `pkg-config --cflags --libs gtk+-3.0`
