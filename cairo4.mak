cairo4 : cairo4.c
	gcc -o cairo4 cairo4.c `pkg-config --cflags --libs gtk+-3.0`
