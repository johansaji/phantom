
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
  conn->status_code = 200;
  mg_printf(conn, "HTTP/1.1 200 OK\r\n"
                  "Content-Type: video/mpeg\r\n"
                  "Connection: close\r\nCache-control: private\r\n"
                  "Server: lighttpd/1.4.26\r\n\r\n");
}

void HTTPHeader::Error400Code(struct mg_connection *conn)
{
  mg_send_status(conn, 400);
	mg_send_header(conn, "Content-Type", "text/plain");
  mg_send_data(conn, conn->content, conn->content_len);
  mg_send_data(conn, "", 0);
  
 /* mg_printf(conn,"<html><body>"
                 "<h2>OOPS !!!!</h2>"
                 "<p>Check the url... Url is malformed</p>"
                 "</body></html>");
  */
                 
}

void HTTPHeader::NotFound404Code(struct mg_connection *conn)
{
  mg_send_status(conn, 404);
	mg_send_header(conn, "Content-Type", "text/plain");
  mg_send_data(conn, conn->content, conn->content_len);
  mg_send_data(conn, "", 0);
  /*mg_printf(conn,"<html><body>"
                 "<h2>404 !!!!</h2>"
                 "<p>File not found</p>"
                 "</body></html>");*/
}