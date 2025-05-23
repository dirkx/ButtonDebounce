/*
  ButtonDebounce.h - Library for Button Debounce.
  Created by Maykon L. Capellari, September 30, 2017.
  Released into the public domain.
*/
#ifndef ButtonDebounce_h
#define ButtonDebounce_h

#include "Arduino.h"
#include "Ticker.h"
#include <functional>

class ButtonDebounce {
  public:
    ButtonDebounce(int pin, unsigned long delay = 100 /* mSeconds stable */);
    ~ButtonDebounce();
    void setAnalogThreshold(unsigned short val); // Set to 0 to go back to digital again.

    bool state();
    bool rawState();
    [[deprecated]] void update() // No longer required; is called by a background Ticker.
        {};

    typedef std::function<bool(const int)> digitalReadFunction;
    void setDigitalReadFunction(digitalReadFunction func) { _digitalRead = func; };

    typedef std::function<float(const int)> analogReadFunction;
    void setAnalogReadFunction(analogReadFunction func) { _analogRead = func; };

    typedef std::function<void(const int)> ButtonCallback;
    void setCallback(ButtonCallback,int mode = CHANGE);

    bool operator ==(int s) { return (s ? HIGH : LOW) == _lastStateBtn; };
    bool operator !=(int s) { return (s ? HIGH : LOW) != _lastStateBtn; };
 
    void _ticker_update();
  private:
    int _pin;
    int _mode; // Interrupt mode (RISING, FALLING, CHANGE, ONLOW, ONHIGH -- see Arduino.h)
    unsigned short _analogThreshold = 0;
    unsigned long _delay;
    unsigned long _lastChangeTime;
    bool _lastStateBtn, _prevStateBtn;
    ButtonCallback _callBack = NULL;
    digitalReadFunction _digitalRead = &digitalRead;
    analogReadFunction _analogRead = &analogRead;
    Ticker * _ticker;
};
#endif
