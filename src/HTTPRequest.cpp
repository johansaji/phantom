
#include <stdio.h>
#include <string.h>
#include <mongoose.h>
#include "HTTPRequest.h"

#define EXIT_URL "/server/exit"


HTTPRequest::HTTPRequest():
  m_connection(NULL)
{
}

HTTPRequest::HTTPRequest(struct mg_connection *connection):
  m_connection(connection)
{
}

int HTTPRequest::isExitRequest()
{
  return !strcmp(m_connection->uri, EXIT_URL);
}
