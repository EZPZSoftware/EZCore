## Makefile for EZCore
## Made by ethancodes2020 <ethanatchley2006@gmail.com>

all:
	gcc -g uname.c -o uname
	gcc -g yes.c -o yes

clean:

	rm -rf yes uname
