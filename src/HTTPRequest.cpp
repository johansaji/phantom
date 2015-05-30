
#include <stdio.h>
#include <string.h>
#include <mongoose.h>
#include "HTTPRequest.h"

#define VALID_URL "/phantom/"
#define EXIT_URL "/phantom/exit"


HTTPRequest::HTTPRequest():
  m_connection(NULL)
{
}

HTTPRequest::HTTPRequest(struct mg_connection *connection):
  m_connection(connection)
{
}

bool HTTPRequest::isExitRequest(void)
{
  return (!strcmp(m_connection->uri, EXIT_URL)) ? true : false ;
}

bool HTTPRequest::isUrlValid(void)
{
  return strstr(m_connection->uri, VALID_URL) ? true : false;
}