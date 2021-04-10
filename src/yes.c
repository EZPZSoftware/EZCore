/*
  EZCore - yes utility
  written by Thomas Sirack (tsirack@protonmail.com)
*/

#include <stdio.h>

int main(int argc, char **argv)
{
  if(argc == 1)
  {
    while(1)
    {
      puts("y");
    }
  }else if(argv[1])
  {
    while(1)
    {
      puts(argv[1]);
    }
  }
  
  return 0;
}
