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
    
  private:
    HTTPServer();
    static int httpServerMsgHandler(struct mg_connection *, enum mg_event);
    static HTTPServer *m_instance;

    bool m_serverStarted;
    struct mg_server *m_server;
};

#endif //HTTPSERVER_H
