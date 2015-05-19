
#include "mongoose.h"
#include "Server.h"

Server* Server::m_instance = NULL;

Server::Server():
  m_server(0),
  m_status(ServerStopped)
{
}

Server* Server::getInstance()
{
  if(!m_instance){
    m_instance = new Server();
  }
  return m_instance;
}


