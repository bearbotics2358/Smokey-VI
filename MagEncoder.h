#ifndef MAGENCODER_H
#define MAGENCODER_H

#include "AnalogChannel.h"

class MagEncoder : public AnalogChannel{
//adsfasdfasdfasdfa


public:
	MagEncoder(UINT32 channel);
	~MagEncoder();
	double MagEncoder::PIDGet();
};

#endif
