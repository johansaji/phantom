
#include <stdio.h>
#include <string.h>
#include <mongoose.h>
#include "HTTPServer.h"

HTTPServer* HTTPServer::m_instance;

HTTPServer::HTTPServer():
  m_server(0),
  m_serverStarted(false)
{
}

HTTPServer* HTTPServer::getInstance()
{
  if (NULL == m_instance){
    m_instance = new HTTPServer();
  }
  return m_instance;
}

ServerResult HTTPServer::start()
{
  if (m_serverStarted)
    return HS_RUNNING;
  
  m_server = mg_create_server(NULL, HTTPServer::httpServerMsgHandler);
  mg_set_option(m_server, "listening_port", "8080");
  m_serverStarted = true;
  printf("Server started running at %s", mg_get_option(m_server, "listening_port"));
  return HS_SUCCESS;
}

ServerResult HTTPServer::run()
{
  while (m_serverStarted){
    mg_poll_server(m_server, 1000);
  }
}
ServerResult HTTPServer::stop()
{
  if (!m_serverStarted)
    return HS_SUCCESS;

  mg_destroy_server(&m_server);
  m_serverStarted = false;
  return HS_SUCCESS;
}

int HTTPServer::httpServerMsgHandler(struct mg_connection *connection, enum mg_event event)
{
  printf("Message Handler\n");
}
