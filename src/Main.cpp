#include <signal.h>
#include <glib.h>

#include "plog.h"
#include "Server.h"

GMainLoop *loop;

void signal_handler(int signal)
{
  switch(signal){
    case SIGINT:
       PLOG_INFO("Got keyboard interrupt");
       g_main_loop_quit (loop);
       break;
    default:
       break;
  }
}

int main(int argc, char** argv)
{
  kronos_init("./kronos.conf");
  signal(SIGINT, signal_handler);

  Server *server = Server::getInstance();
  server->start(8080); 

  PLOG_DEBUG("Starting main loop");
  loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (loop);
  PLOG_DEBUG("Main loop exited");

  g_main_loop_unref (loop);
  return 0;

}
