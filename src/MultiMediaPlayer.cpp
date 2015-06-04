#include "MediaEngineInterface.h"
#include "MultiMediaPlayer.h"

/* Include each media engines here with proper gaurds */


class MediaEngineFactory{
  public:
    MediaEngineFactory(MediaEngineConstructor constructor, MediaEngineSupportsType supportsType)
      m_constructor(constructor),
      m_supportsType(supportsType)
    {}

    MediaEngineConstructor m_constructor;
    MediaEngineSupportsType m_supportsType;
};


