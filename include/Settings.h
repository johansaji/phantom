#ifndef SETTINGS_H
#define SETTINGS_H

#include <glib.h>

class Settings{
  public:
    static Settings* getInstance();
    ~Settings();
    gint getHTTPPort();
    void loadSetingsfromFile(char * conf);

  private:
    Settings();
    

  private:
    static Settings* m_instance;
    gint m_httpPort;
    gchar *m_serverName;
    

    
};

#endif //SETTINGS_H
