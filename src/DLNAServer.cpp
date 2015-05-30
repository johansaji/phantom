#include <stdio.h>

#include "plog.h"
#include "DLNAServer.h"

DLNAServer* DLNAServer::m_instance = NULL;

DLNAServer::DLNAServer()
{

}

DLNAServer* DLNAServer::getInstance()
{
  if(NULL == m_instance){
    m_instance = new DLNAServer();
  }
  return m_instance;
}

void DLNAServer::runServer()
{
  //TODO: 
}