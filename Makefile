## Makefile for EZCore
## Made by ethancodes2020 <ethanatchley2006@gmail.com>
## and Thomas Sirack <tsirack@gmail.com>

CFLAGS := -g -Wall -O3
UTILS := uname \
	 yes

all:
	$(CC) $(CFLAGS) uname.c -o uname
	$(CC) $(CFLAGS) yes.c -o yes

clean:
	rm -rf $(UTILS)
