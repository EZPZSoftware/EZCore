## Makefile for EZCore
## Made by ethancodes2020 <ethanatchley2006@gmail.com>
## and Thomas Sirack <tsirack@gmail.com>
## and Nikita Nikiforov (amdbtw) <efifb@yandex.ru>

CFLAGS := -g -Wall -O2
UTILS := link \
         uname \
         yes \
	 chmod

all:
	$(CC) $(CFLAGS) link.c -o link
	$(CC) $(CFLAGS) uname.c -o uname
	$(CC) $(CFLAGS) yes.c -o yes
	$(CC) $(CFLAGS) chmod.c -o chmod

clean:
	rm -rf $(UTILS)
