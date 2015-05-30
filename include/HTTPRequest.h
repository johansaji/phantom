#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HTTPRequest{
  public:
    HTTPRequest();
    HTTPRequest(struct mg_connection *);
    bool isExitRequest(void);
	bool isUrlValid(void);
  private:
    struct mg_connection *m_connection;
};

#endif //HTTPREQUEST_H
