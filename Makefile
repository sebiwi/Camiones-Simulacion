target:	main.c list.c set.c
	cc -o proyecto main.c list.c set.c informe.c -lm
clean:
	rm proyecto
