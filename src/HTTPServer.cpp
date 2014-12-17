
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mongoose.h>
#include <pthread.h>
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
  printf("Server started running at %s\n", mg_get_option(m_server, "listening_port"));
  return HS_SUCCESS;
}

ServerResult HTTPServer::run()
{
  int ret;
  pthread_attr_t threadAttr;
  // initialize thraed attribute
  ret = pthread_attr_init(&threadAttr);
  if (ret != 0){
    printf("Init Failed.\n");
    return HS_FAIL;
  } 
  // create a new thread
  ret = pthread_create(&thread, &threadAttr, HTTPServer::serverThread, (void *)this);
  if (ret != 0){
    printf("Thread Create Failed.\n");
    return HS_FAIL;
  }
  // destroy created thread
  ret = pthread_attr_destroy(&threadAttr);
  if (ret != 0){
    printf("Unable to destroy the attr\n");
    return HS_FAIL;
  }
  return HS_SUCCESS;
}

ServerResult HTTPServer::stop()
{
  if (!m_serverStarted)
    return HS_SUCCESS;

  m_serverStarted = false;
  return HS_SUCCESS;
}

pthread_t HTTPServer::getThread()
{
  return thread;
}

void *HTTPServer::serverThread(void *data)
{
  HTTPServer *server = (HTTPServer *) data;
  while (server->m_serverStarted){
    mg_poll_server(server->m_server, 1000);
  }
  mg_destroy_server(&server->m_server);
  return NULL;
}

int HTTPServer::httpServerMsgHandler(struct mg_connection *connection, enum mg_event event)
{
  switch(event){
  case MG_AUTH:
    printf("AUTH\n");
    printf("url -> %s\n", connection->uri); 
    return MG_TRUE;
  case MG_REQUEST:
    printf("REQU\n");
    printf("url -> %s\n", connection->uri); 
    //while(1){sleep(10); }
    return MG_TRUE;
  case MG_POLL:
    printf("POLL\n");
    printf("url -> %s\n", connection->uri); 
    return MG_FALSE;
  case MG_CLOSE:
    printf("CLOSE\n");
    printf("url -> %s\n", connection->uri); 
    return MG_TRUE;
  default:
    printf("DEF %d\n", event);
    printf("Handler url -> %s\n", connection->uri); 
    return MG_FALSE;
  }
}
