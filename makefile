all:
	gcc -g -Wall -o run main.c water_mark_manage.c  -lgd

clean:
	rm -f run
