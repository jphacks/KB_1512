.PHONY: all
all: pump

pump:
	scp ./pump.c edison1:~/src/unit/pump/pump.c
	ssh edison1 'cd ~/src/unit/pump/ && gcc -lmraa -o pump pump.c'
.PHONY: test
test: all
	ssh edison1 '~/src/unit/unit_daemon'
