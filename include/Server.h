#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <pthread.h>
#include "mongoose.h"

typedef enum{
  ServerStopped = 0,
  ServerStarted,
  ServerRunning
}ServerStatus;

/**
 Server
 HTTP server structure
 */
class Server{
  public:  /* Public Methods*/
    static Server* getInstance();
    static int event_handler(struct mg_connection *, enum mg_event );
    void shutdownServer();
    static void *serverPollThread (void *);
    ~Server();
    void start();

  private: /* Private Methods */
    Server();
    bool stopServer();
    ServerStatus getServerStatus();
    bool isServerRunning();
    void startPollThread();

  public:  /* Public Members */

  private: /* Private Members */
    static Server* m_instance;
    struct mg_server *m_server;
    ServerStatus m_status;
    pthread_t m_pollThreadId;

};

#endif
