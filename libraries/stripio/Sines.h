#ifndef __SINES_H__
#define __SINES_H__

#include <Arduino.h>
#include "Animation.h"
#include "ColorUtils.h"
#include "IMotion.h"
#include <avr/pgmspace.h>

extern const uint8_t PROGMEM sinetable[256];

class Sines : public Animation {
public:
	Sines(MultiNeoPixel& strip, IMotion* motion, bool active) : Animation(strip, active), mMotion(motion)
	{
	}

protected:
	virtual void performDraw() {
		update();
		sinRainbow();
	}

public:
	void sinRainbow() {
		uint32_t currentTime = getTime();
		int32_t t = (currentTime >> 11) + mValue*5;
		//Serial.print(currentTime >> 11); Serial.print(" "); Serial.println(mValue);
		for(int32_t x=0; x < mStrip.getSizeX(); x++) {
			for(int32_t y=0; y < mStrip.getSizeY(); y++) {
				int val = (sine((x*571 + t)/23) + sine((y*353 + t)/27) - 255);
				int val2 = 3*(sine((x*153 + t)/43) + sine((y*61 + t)/27)) >> 1;
				//int val = 64*(sin((x*131 + currentTime)/151.f) + sin((y*71 + currentTime)/131.f));
				//int val2 = 384 + 192*(sin((x*113 - currentTime)/131.f) + sin((y*31 + currentTime)/151.f));
				//int val3 = 64*(sin((x*11 + getFrameCount())/27.f) + sin((y*11 - getFrameCount())/17.f));
				//int val = 64*(sin((x*131 + t)/151.f) + sin((y*71 + t)/131.f));
				//int val2 = 384 + 192*(sin((x*113 - t)/131.f) + sin((y*31 + t)/151.f));
				mStrip.setPixelColor(x,y, Wheel(val2, max(val-15, 0)));
			}
		}
	}
	virtual void begin() {
		mValue = 0;
	}

	virtual void clear() {
		mIsActive = 0;
	}

	virtual void update();

	inline byte sine(byte offset) {
		return pgm_read_byte_near(&(sinetable[offset]));
	}

private:
	int32_t mValue;
	IMotion* mMotion;
};


#endif // #ifndef __SINES_H__
