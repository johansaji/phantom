#ifndef SERVER_H
#define SERVER_H

//#include "mongoose.h"

typedef enum{
  ServerStopped = 0,
  ServerStarted,
  ServerRunning,
  ServerStopping
}ServerStatus;

/**
 Server
 HTTP server structure
 */
class Server{
  public:  /* Public Methods*/
    static Server* getInstance();
    ~Server();

  private: /* Private Methods */
    Server();
    bool stopServer();
    bool shutdownServer();
    ServerStatus getServerStatus();

  public:  /* Public Members */

  private: /* Private Members */
    static Server* m_instance;
    struct mg_server *m_server;
    ServerStatus m_status;

};

#endif
