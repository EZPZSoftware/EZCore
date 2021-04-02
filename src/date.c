/*
  ezcore - date utility
  written by Thomas Sirack (tsirack@gmail.com)

  compliant to:
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/date.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const char *default_format = "%a %b %e %H:%M:%S %Z %Y";
const char *options = "hu";

struct tm ts;
time_t now;

short option_u = 0;

/* let's play it safe */
char output[1024];
char *format;

void usage(char **argv)
{
  fprintf(stderr, "Usage: %s [-hu] [+format]\n",
                  argv[0], argv[0]);
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

      case 'u':
        option_u = 1;
        break;
    }
  }
}

int main(int argc, char **argv)
{
  parse_args(argc, argv);

  now = time(NULL);
  if(option_u)
    setenv("TZ", "UTC0", 1);

  ts = *localtime(&now);

  if(argv[optind])
  {
    format = (char*)calloc(strlen(argv[optind]), sizeof(char));
    if(!format)
      return 1;

    strncpy(format, argv[optind]+1, strlen(argv[optind]) - 1);
  }

  if(!argv[optind])
    strftime(output, 1024, default_format, &ts);
  else
    strftime(output, 1024, format, &ts);

  puts(output);

  if(format)
    free(format);
  return 0;
}
