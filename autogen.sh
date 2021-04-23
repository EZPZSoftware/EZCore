#!/bin/sh
## This is to make sure that the working directory is ready to be built
aclocal
autoheader
automake
autoconf
