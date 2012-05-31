target:	main.o list.o set.o
	cc -o proyecto main.o list.o set.o
main.o:	main.c
	cc -c main.c
list.o:	list.c list.h
	cc -c list.c
set.o:	set.c set.h
	cc -c set.c
clean:
	rm main.o list.o set.o
