#include "Config.h"

Config::Config()
{
  m_KeyFile = g_key_file_new();
}

Config::~Config()
{
  if (m_KeyFile)
      g_key_file_free(m_KeyFile);
}

gboolean Config::loadConfiguration(char *fileName)
{
  if(!m_KeyFile)
    return FALSE;
  
  return g_key_file_load_from_file (m_KeyFile, fileName, G_KEY_FILE_NONE, NULL);
}

gboolean Config::hasGroup(const char *group)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_has_group(m_KeyFile, group);
}

gboolean Config::hasKey(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_has_key(m_KeyFile, group, key, NULL);
}

gchar*   Config::getStartGroup()
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_start_group(m_KeyFile);
}

gchar**  Config::getAllGroups(gsize *length)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_groups(m_KeyFile, length);
}

gchar**  Config::getAllKeys(const char *group, gsize *length)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_keys(m_KeyFile, group, length, NULL);
}

gchar*   Config::getValue(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_value(m_KeyFile, group, key, NULL);
}

gchar*   Config::getString(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_string(m_KeyFile, group, key, NULL);
}

gboolean Config::getBoolean(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_boolean(m_KeyFile, group, key, NULL);
}

gint     Config::getInteger(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_integer(m_KeyFile, group, key, NULL);
}

gint64   Config::getInt64(const char *group, const char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_int64(m_KeyFile, group, key, NULL);\
}

guint  Config::getUInteger(char *group, char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_uint64(m_KeyFile, group, key, NULL);
}

gdouble  Config::getDouble(char *group, char *key)
{
  if(!m_KeyFile)
    return FALSE;
  return g_key_file_get_double(m_KeyFile, group, key, NULL);
}
