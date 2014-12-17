#include <Version.in>

/*-- System Includes --*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

/*-- User Includes --*/
#include <OptConst.h>
#include <mongoose.h>
#include "ErrorCodes.h"
#include "HTTPServer.h"

/*
 * print_version() 
 */
void printVersion()
{
  printf("phantom %s.%s.%s\n", PH_MAJOR_VERSION, PH_MINOR_VERSION, PH_BUILD);
  printf("Copyright (C) 2015 Blue Fire OS.\n");
  printf("This is free software; see the source for copying conditions.  There is NO\n");
  printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}

int processCmdline(int argc, char **argv)
{
  int option = 0;
  int option_id = 0;
  while(-1 != (option = getopt_long(argc, argv, short_options,
                              long_options, &option_id))){
    switch(option){
    case 'v':
      printVersion();
      break;
    case '?':
      printf("unknown option\n");
    }
  }
  return PH_SUCCESS;
}

/*
 * Signal handler for propper exit
 */
void signalHandler(int sigNum)
{
  printf("Got signal %d ...\n", sigNum);
  switch(sigNum){
  case SIGSEGV:
    printf("Got segmentation fault server...\n");
    HTTPServer::getInstance()->stop();
    exit(1);
  case SIGINT:
    printf("Shutting down the server...\n");
    HTTPServer::getInstance()->stop();
    //exit(0);
  }
}

int main(int argc, char** argv)
{
  signal(SIGSEGV, signalHandler);
  signal(SIGINT, signalHandler);
  processCmdline(argc, argv);
  /* start the server */
  HTTPServer::getInstance()->start();
  HTTPServer::getInstance()->run();
  pthread_join(HTTPServer::getInstance()->getThread(), NULL);
  
  return 0;
}
