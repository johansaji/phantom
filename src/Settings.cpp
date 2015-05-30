#include "plog.h"
#include "Config.h"
#include "Settings.h"

Settings* Settings::m_instance = NULL;

Settings::Settings():
  m_httpPort(0)
{
}

Settings::~Settings()
{

}

Settings* Settings::getInstance()
{
  if (m_instance == NULL){
    m_instance = new Settings();
  }
  return m_instance;
}

void Settings::loadSetingsfromFile(char *conf)
{
  Config configuration;
  if (configuration.loadConfiguration(conf)){
    m_httpPort = configuration.getInteger("HTTPServer", "Port");
  }else{
    PLOG_ERROR("Unable to process the configuration file %s", conf);
  }
}

gint Settings::getHTTPPort()
{
  return m_httpPort;
}