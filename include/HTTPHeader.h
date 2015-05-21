#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include "mongoose.h"

typedef struct mg_header {
  const char *name;         // HTTP header name
  const char *value;        // HTTP header value
}struct_header;

class HTTPHeader{
  public:
    static void PrintHeader(struct_header *headers, int num_header);
    static void OK200Code(struct mg_connection *);
};

#endif //HTTPHEADER_H
