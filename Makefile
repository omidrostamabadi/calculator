EXECUTIVEFILES=main calc_code calculator_2
CFILES=main.c calc_code.c calculator_2.c

main: Makefile main.c
	$(CC) -o main main.c

calc_code: Makefile calc_code.c
	$(CC) -o calc_code calc_code.c

calculator_2: Makefile calculator_2.c
	$(CC) -o calculator_2 calculator_2.c

clean: 
	rm main calc_code calculator_2
