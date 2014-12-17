#ifndef HTTPSERVER_H
#define HTTPSERVER_H

typedef enum {
  HS_SUCCESS = 0,
  HS_FAIL,
  HS_RUNNING
} ServerResult;

class HTTPServer{
  public:
    static HTTPServer* getInstance();
    ServerResult start();
    ServerResult run();
    ServerResult stop();
    pthread_t getThread();
    
    
  private:
    HTTPServer();
    static int httpServerMsgHandler(struct mg_connection *, enum mg_event);
    static void *serverThread(void *);
    static HTTPServer *m_instance;

    struct mg_server *m_server;
    bool m_serverStarted;
    pthread_t thread;
};

#endif //HTTPSERVER_H
