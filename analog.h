﻿#include "FastLED.h"

///@ingroup chipsets
///@{

// note - dmx simple must be included before FastSPI for this code to be enabled
template <uint8_t RED, uint8_t GREEN, uint8_t BLUE, uint8_t WHITE = 99, bool WHITEONLY = false,EOrder RGB_ORDER = RGB> class AnalogPWMController : public CPixelLEDController<RGB_ORDER> {
public:
	// initialize the LED controller
	virtual void init() { 
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    if(WHITE != 99)
      pinMode(WHITE, OUTPUT);
  }

protected:
	virtual void showPixels(PixelController<RGB_ORDER> & pixels) {
		int iChannel = 1;
		if(pixels.has(1)) {
      boolean isWhite = false;
      if(WHITE != 99){
        if(pixels.loadAndScale0() == pixels.loadAndScale1() && pixels.loadAndScale0() == pixels.loadAndScale2()) {            
          analogWrite(WHITE, pixels.loadAndScale0());
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          isWhite = true;
        }
        else
          analogWrite(WHITE, 0);
      }

      if(isWhite == false || (isWhite == true && WHITEONLY == false)) {
  			analogWrite(RED, pixels.loadAndScale0());
  			analogWrite(GREEN, pixels.loadAndScale1());
  			analogWrite(BLUE, pixels.loadAndScale2());
      }
      
			pixels.advanceData();
			pixels.stepDithering();
		}
	}
};