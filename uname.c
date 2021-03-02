/*
  EZCore - uname utility
  
  compliant to:
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/uname.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

struct utsname sysinfo;

short option_a = 0;
short option_m = 0;
short option_n = 0;
short option_r = 0;
short option_s = 0;
short option_v = 0;

const char *options = "ahmnrsv";

void usage(char **argv)
{
  printf("Usage: %s [-ahmnrsv]\n", argv[0]);
  exit(0);
}

void parse_args(int argc, char **argv)
{
  int c = 0;
  while((c = getopt(argc, argv, options)) != -1)
  {
    switch(c)
    {
      case 'a': /* "Behave as though all of the options
                -mnrsv were specified." */
        option_a = 1;
        break;

      case 'h': /* help */
        usage(argv);
        break;

      case 'm': /* "Write the name of the hardware type on
                which the system is running to standard output." */
        option_m = 1;
        break;

      case 'n': /* "Write the name of this node within an
                implementation-defined communications network." */
        option_n = 1;
        break;

      case 'r': /* "Write the current release level of the
                operating system implementation." */
        option_r = 1;
        break;

      case 's': /* "Write the name of the implementation of
                the operating system." */
        option_s = 1;
        break;

      case 'v': /* "Write the current version level of this
                release of the operating system implementation." */
        option_v = 1;
    }
  }
}

int main(int argc, char **argv)
{
  if(argc == 1) /* no arguments, act as if -s */
    option_s = 1;
  else
    parse_args(argc, argv);

  uname(&sysinfo);

  /* we want to add segments if multiple options are specified,
  so create the longest possible string to hold all this*/
  size_t length = 0;
  length += strlen(sysinfo.sysname);
  length += strlen(sysinfo.nodename);
  length += strlen(sysinfo.release);
  length += strlen(sysinfo.version);
  length += strlen(sysinfo.machine);
  length++;

  char string[length];
  strcpy(string, "");

  if(option_a)
  {
    strcat(string, sysinfo.sysname);
    strcat(string, " ");
    strcat(string, sysinfo.nodename);
    strcat(string, " ");
    strcat(string, sysinfo.release);
    strcat(string, " ");
    strcat(string, sysinfo.version);
    strcat(string, " ");
    strcat(string, sysinfo.machine);
  }

  if(option_r)
  {
    strcat(string, sysinfo.release);
    strcat(string, " ");
  }

  if(option_v)
  {
    strcat(string, sysinfo.version);
    strcat(string, " ");
  }

  if(option_s)
  {
    strcat(string, sysinfo.sysname);
    strcat(string, " ");
  }

  if(option_m)
  {
    strcat(string, sysinfo.machine);
    strcat(string, " ");
  }

  if(option_n)
  {
    strcat(string, sysinfo.nodename);
    strcat(string, " ");
  }

  puts(string);

  return 0;
}
