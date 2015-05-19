
#include "mongoose.h"
#include "kronos.h"
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
  }

  for (;;) {
        mg_poll_server(m_server, 1000);   // Infinite loop, Ctrl-C to stop
          }
}

int Server::event_handler(struct mg_connection *conn, enum mg_event ev) {
  KRONOS_LOG(KRONOS_TRACE, "elixir.phantom", "Enter");
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    default: return MG_FALSE;
  }
  KRONOS_LOG(KRONOS_TRACE, "elixir.phantom", "Leave");
}
