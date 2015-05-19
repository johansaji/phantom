
#include "mongoose.h"
#include "plog.h"
#include "Server.h"

Server* Server::m_instance = NULL;

Server::Server():
  m_server(0),
  m_status(ServerStopped)
{
}

Server::~Server()
{
}

Server* Server::getInstance()
{
  if(!m_instance){
    m_instance = new Server();
  }
  return m_instance;
}

bool Server::stopServer()
{
  return false;
}

bool Server::shutdownServer()
{
  return false;
}

ServerStatus Server::getServerStatus()
{
  return m_status;
}

void Server::start(uint16_t port)
{
  if (m_status != ServerStarted && m_status != ServerRunning){
    m_server = mg_create_server(NULL, Server::event_handler);
    mg_set_option(m_server, "listening_port", "8080");
    startPollThread();
  }

}

bool Server::isServerRunning()
{
  return true;
}

void Server::startPollThread()
{
 int ret =  pthread_create( &m_pollThreadId, NULL, serverPollThread, (void*) m_server);
 if (ret){
  PLOG_CRIT("Error - pthread_create() return code: %d\n",ret);
 }
}

void *Server::serverPollThread(void *serverctx)
{
  Server *serverInst = Server::getInstance();
  struct mg_server *server = (struct mg_server *)serverctx;

  while (serverInst->isServerRunning()){
    mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
    PLOG_TRACE("Server hearbeat");
  }

  return NULL;
}

int Server::event_handler(struct mg_connection *conn, enum mg_event ev) {
  //PLOG_TRACE("Enter");
  PLOG_TRACE("Mongoose event = %d ", ev);
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      mg_printf(conn, "HTTP/1.1 200 OK\r\n"
                      "Content-Type: video/mp4\r\n");
        PLOG_DEBUG("*********************************************************");
      for (int i = 0; i < conn->num_headers; i++){
        PLOG_DEBUG("  %-15s : %s ", conn->http_headers[i].name, conn->http_headers[i].value);
      }
        PLOG_DEBUG("*********************************************************");
      return MG_MORE;
    default: return MG_FALSE;
  }
  //PLOG_TRACE("Leave");
}
