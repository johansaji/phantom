
#include <stdio.h>
#include "HTTPRequest.h"

HTTPRequest::HTTPRequest():
  m_connection(NULL)
{
}

HTTPRequest::HTTPRequest(struct mg_connection *connection):
  m_connection(connection)
{
}


