#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <vector>
#include "TimerEventListener.h"

class Timer{
  uint32_t timeout;
  uint32_t startMillis;
  bool paused;

  std::vector<TimerEventListener*> listeners;
public:
  Timer();
  virtual ~Timer();

  void update();

  void addEventListener(TimerEventListener *listener);

  void start(uint32_t timoutToSet);
  void stop();
  void pause();
  void resume();
  void reset();
  bool isPaused();
};

#endif