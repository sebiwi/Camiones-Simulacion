target:	main.c list.c set.c
	cc -o proyecto main.c list.c set.c -lm
clean:
	rm proyecto
