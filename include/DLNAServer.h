#ifndef DLNASERVER_H
#define DLNASERVER_H

class DLNAServer{
  public:
    static DLNAServer* getInstance();
    void runServer();

  private:
    DLNAServer();
    
  private:
    static DLNAServer *m_instance;
};

#endif
