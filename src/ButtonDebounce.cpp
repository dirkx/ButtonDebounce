#include "ButtonDebounce.h"
#define SAMPLES_PER_DELAY (4)

static void _update(uint32_t arg) {
	ButtonDebounce * c = (ButtonDebounce*)arg;
	c->update();
}

ButtonDebounce::ButtonDebounce(int pin, unsigned long delay){
  _pin = pin;
  _delay = delay;
  _lastChangeTime = 0;
  _prevStateBtn = _lastStateBtn = digitalRead(_pin) ? HIGH : LOW;
  _ticker = new Ticker();
  _ticker->attach_ms(
    delay/SAMPLES_PER_DELAY,_update,(uint32_t )this
  );
}

ButtonDebounce::~ButtonDebounce() {
	delete _ticker;
};

void ButtonDebounce::update(){
  int btnState = digitalRead(_pin) ? HIGH : LOW;

  if(btnState != _prevStateBtn) {
        _lastChangeTime = millis();
	_prevStateBtn = btnState;
	return;
  };

  if (_lastStateBtn == btnState)
	return; // no change

  if (millis() - _lastChangeTime < _delay)
   	return;
  // We are longer than delay in a stable state that
  // differs from our last state; so we can consider
  // it suitably debounced now.
  //
  _prevStateBtn =  _lastStateBtn = btnState;

  if (!this->_callBack) 
	return;

  if  (
	 (_mode == CHANGE) || 
	((_mode == ONLOW   || _mode == FALLING) && btnState == LOW) ||
	((_mode == ONHIGH  || _mode == RISING) && btnState == HIGH)
  ) this->_callBack(_lastStateBtn);
}

int ButtonDebounce::state(){
  return _lastStateBtn;
}

void ButtonDebounce::setCallback(ButtonCallback callback, int mode) { 
 this->_callBack = callback; 
 this->_mode = mode;
}
