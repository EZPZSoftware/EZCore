/*
  EZCore - yes utility
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
