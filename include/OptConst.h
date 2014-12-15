#ifndef OPTCONST_H
#define OPTCONST_H

#include <getopt.h>  //cmdline parsing

#define short_options "v"

struct option long_options[] = {
  {"version", no_argument, 0, 'v'},
  { 0 ,0 , 0, 0} //End of long_option
  };

#endif //OPTCONST_H
