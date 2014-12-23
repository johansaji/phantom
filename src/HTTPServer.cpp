
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <mongoose.h>
#include <pthread.h>

#include "HTTPServer.h"
#include "HTTPRequest.h"

#define HTTP_PORT "8090"

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
  mg_set_option(m_server, "listening_port", HTTP_PORT);
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
  static int count = 0;
  switch(event){
  case MG_AUTH:
    /*Do the authentication here*/ 
    return MG_TRUE;
  case MG_REQUEST:
  {
    /*Process the request here */
    int *temp = (int *)malloc(sizeof(int));
    printf("url -> %s\n", connection->uri);
    count++;
    *temp = count;
    connection->connection_param = temp;
    printf("No = %p\n", (int *)(connection->connection_param));
    HTTPRequest *request = new HTTPRequest(connection);
    if (request->isExitRequest()){
      HTTPServer::getInstance()->stop();
    }
    //getchar();
    return MG_MORE;
  }
  case MG_POLL:
    printf("POLL  ");
    printf("Connection Number = %d \n", (connection->connection_param != NULL)? *(int *)(connection->connection_param):0);
    printf("No = %p\n", (int *)(connection->connection_param));
    return MG_FALSE;
  case MG_CLOSE:
    printf("CLOSE\n");
    free(connection->connection_param);
    return MG_TRUE;
  default:
    printf("DEF %d\n", event);
    printf("Handler url -> %s\n", connection->uri); 
    return MG_FALSE;
  }
}
