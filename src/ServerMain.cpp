#include <Version.in>

#include <stdio.h>
#include <unistd.h>
#include <OptConst.h>
#include "ErrorCodes.h"

void print_version()
{
  printf("phantom %s.%s.%s\n", PH_MAJOR_VERSION, PH_MINOR_VERSION, PH_BUILD);
  printf("Copyright (C) 2015 Blue Fire OS.\n");
  printf("This is free software; see the source for copying conditions.  There is NO\n");
  printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}

int process_cmdline(int argc, char **argv)
{
  int option = 0;
  int option_id = 0;
  while(-1 != (option = getopt_long(argc, argv, short_options,
                              long_options, &option_id))){
    switch(option){
    case 'v':
      print_version();
      break;
    case '?':
      printf("unknown option\n");
    }
  }
  return PH_SUCCESS;
}


int main(int argc, char** argv)
{
  
  process_cmdline(argc, argv);
  return 0;
}
