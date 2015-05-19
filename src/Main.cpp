#include <unistd.h>

#include "kronos.h"
#include "Server.h"

int main(int argc, char** argv)
{
  kronos_init("./kronos.conf");
  Server *server = Server::getInstance();
  server->start(8080); 

  while(1){
    KRONOS_LOG(KRONOS_TRACE, "elixir.phantom", "waiting");
    sleep(2);
  }
  return 0;

}
