#ifndef CONFIG_H
#define CONFIG_H

#include <glib.h>

class Config{

  public:
    Config();
    ~Config();
    gboolean loadConfiguration(char *fileName);

    gboolean hasGroup(const char *group);
    gboolean hasKey(const char *group, const char *key);
    /* get functions */
    gchar*   getStartGroup();
    gchar**  getAllGroups(gsize *length);
    gchar**  getAllKeys(const char *group, gsize *length);
    gchar*   getValue(const char *group, const char *key);
    gchar*   getString(const char *group, const char *key);
    gboolean getBoolean(const char *group, const char *key);
    gint     getInteger(const char *group, const char *key);
    gint64   getInt64(const char *group, const char *key);
    guint    getUInteger(char *group, char *key);
    gdouble  getDouble(char *group, char *key);

    /* set functions*/
    //TODO: Add set functions

  private:
    GKeyFile *m_KeyFile;
};

#endif //CONFIG_H
