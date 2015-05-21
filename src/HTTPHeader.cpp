
#include <mongoose.h>
#include "plog.h"
#include <HTTPHeader.h>

void HTTPHeader::PrintHeader(struct_header *headers, int num_header)
{
  PLOG_DEBUG("*********************************************************");
  for (int i = 0; i < num_header; i++){
    PLOG_DEBUG("  %-15s : %s ", headers[i].name, headers[i].value);
  }
  PLOG_DEBUG("*********************************************************");
}

void HTTPHeader::OK200Code(struct mg_connection *conn)
{
  mg_printf(conn, "HTTP/1.1 200 OK\r\n"
                  "Content-Type: video/mpeg\r\n"
                  "Connection: close\r\nCache-control: private\r\n"
                  "Server: lighttpd/1.4.26\r\n\r\n");
}

