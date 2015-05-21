
#include "mongoose.h"
#include "plog.h"
#include "kronos.h"
#include "HTTPHeader.h"
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
    case MG_REQUEST:{
      HTTPHeader::PrintHeader((struct_header *)conn->http_headers, conn->num_headers);
      HTTPHeader::OK200Code(conn);
      FILE *fp = fopen("./yan.mp4", "r");
      conn->connection_param = (void *)fp;
      return MG_MORE;
    }
    case MG_POLL:
    {
      FILE *fp = (FILE *)conn->connection_param;
      if (fp != NULL){
        char buff[1024];
        int n = fread(buff, 1, sizeof(buff), fp);
        mg_write(conn, buff, n);
      }
    }
    default: return MG_FALSE;
  }
  //PLOG_TRACE("Leave");
}
