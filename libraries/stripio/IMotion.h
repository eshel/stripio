#ifndef _IMOTION_H_
#define _IMOTION_H_

#include "MotionSample.h"

class IMotion {
public:
	virtual const MotionSample& getSample(uint16_t offset = 0) const = 0;
};

#endif // #ifndef _IMOTION_H_