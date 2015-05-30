#include <signal.h>
#include <glib.h>

#include "plog.h"
#include "Settings.h"
#include "Server.h"
#include "DLNAServer.h"

GMainLoop *loop;

void signal_handler(int signal)
{
  switch(signal){
    case SIGINT:
       PLOG_INFO("Got keyboard interrupt");
       Server::getInstance()->shutdownServer();
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

  /* Initialize required subsystems */
#if !GLIB_CHECK_VERSION(2,35,0)
  g_type_init ();
#endif
  //g_thread_init(NULL);

  Settings::getInstance()->loadSetingsfromFile("./phantom.conf");
  
  
  Server *server = Server::getInstance();
  server->start(); 

  DLNAServer *dlnaServer = DLNAServer::getInstance();
  dlnaServer->runServer();

  PLOG_DEBUG("Starting main loop");
  loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (loop);
  PLOG_DEBUG("Main loop exited");

  g_main_loop_unref (loop);
  return 0;

}
