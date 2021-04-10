## Makefile for EZCore
## Made by ethancodes2020 <ethanatchley2006@gmail.com>
## and Thomas Sirack <tsirack@protonmail.com>
## and Nikita Nikiforov (amdbtw) <efifb@yandex.ru>

CFLAGS := -g -Wall -O3
UTILS := link \
         uname \
         yes \
         chmod \
         date \

all:
	$(CC) $(CFLAGS) src/link.c -o link
	$(CC) $(CFLAGS) src/uname.c -o uname
	$(CC) $(CFLAGS) src/yes.c -o yes
	$(CC) $(CFLAGS) src/chmod.c -o chmod
	$(CC) $(CFLAGS) src/date.c -o date

clean:
	rm -rf $(UTILS)
