all:
	scp ./unit.c edison1:~/src/unit/unit.c
	ssh edison1 'cd ~/src/unit/ && gcc -lmraa -o unit_dameon unit.c'
