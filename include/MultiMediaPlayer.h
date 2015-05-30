#ifndef MULTIMEDIAPLAYER_H
#define MULTIMEDIAPLAYER_H

#include "MediaEngineInterface.h"



class MultiMediaPlayer{
  public:
    enum SupportsType { IsNotSupported, IsSupported, MayBeSupported };

  public:
    void load(char *url);
    void play();
    void pause();
    void stop();
    
  private:
    MediaEngineInterface *getBestEngine(char *url, char *mimeType);
    
  private:
    MediaEngineInterface m_engine;
};

typedef MediaEngineInterface *(*MediaEngineConstructor)(MultiMediaPlayer *);
typedef MultiMediaPlayer::SupportsType (*MediaEngineSupportsType)(char *mimeType, char* url);


#endif //MULTIMEDIAPLAYER_H
