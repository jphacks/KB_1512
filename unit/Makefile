.PHONY: all
all: poller pump
poller:
	scp ./unit.c edison1:~/src/unit/unit.c
	ssh edison1 'cd ~/src/unit/ && gcc -lmraa -o unit_daemon unit.c'

pump:
	scp ./pump.c edison1:~/src/unit/pump.c
	ssh edison1 'cd ~/src/unit/ && gcc -lmraa -o pump pump.c'
.PHONY: test
test: all
	ssh edison1 '~/src/unit/unit_daemon'
