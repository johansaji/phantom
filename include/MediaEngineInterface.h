#ifndef MEDIAENGINEINETRFACE_H
#define MEDIAENGINEINETRFACE_H

class MediaEngineInterface{
  public:
    virtual void load(char *url) const = 0;
    virtual void play() const = 0;
    virtual void pause() const  = 0;
    virtual void stop() const = 0;
};

#endif // MEDIAENGINEINETRFACE_H