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

void usage(char **argv)
{
  fprintf(stderr, "Usage: %s file1 file2\n",
          argv[0]);
  exit(1);
}

int main(int argc, char **argv)
{
  switch(argc)
  {
    case 1:
      usage(argv);

    case 2:
      fprintf(stderr, "%s: required parameter missing - file2\n",
              argv[0]);
      usage(argv);
  }

  int status = 0;
  status = link(argv[1], argv[2]);

  if(status != 0)
  {
    fprintf(stderr, "%s: could not create link: %s\n",
            argv[0], strerror(errno));
    return 1;
  }

  return 0;
}
