/*
  EZCore - link utility

  compliant to:
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/link.html
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *options = "hv";

short flag_verbose = 0;

void usage(char **argv)
{
  fprintf(stderr, "Usage: %s [-hv] file1 file2\n",
          argv[0]);
  exit(1);
}

void parse_args(int argc, char **argv)
{
  int c = 0;
  while((c = getopt(argc, argv, options)) != -1)
  {
    switch(c)
    {
      case 'h':
        usage(argv);
        break; /* not reached */

      case 'v':
        flag_verbose = 1;
        break;
    }
  }
}

int main(int argc, char **argv)
{
  if(argc == 1)
    usage(argv);
  else
    parse_args(argc, argv);

  if(!argv[optind + 1])
  {
    fprintf(stderr, "%s: required parameter missing\n", argv[0]);
    exit(1);
  }

  int status = 0;
  status = link(argv[optind], argv[optind + 1]);
  if(flag_verbose)
  {
    printf("%s -> %s\n", argv[optind], argv[optind + 1]);
  }


  if(status != 0)
  {
    fprintf(stderr, "%s: could not create link: %s\n",
            argv[0], strerror(errno));
    return 1;
  }

  return 0;
}
