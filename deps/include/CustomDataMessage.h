#ifndef CUSTOM_DATA_MESSAGE_H
#define CUSTOM_DATA_MESSAGE_H

#include "SerialDataMessage.h"

class CustomDataMessage : public SerialDataMessage<double>
{
public:
	CustomDataMessage(const double xl, const double zl, const double yr);
	
	inline double getXl() const noexcept { return _data[TupleIndex::XL]; }
	inline double getZl() const noexcept { return _data[TupleIndex::ZL]; }
	inline double getYr() const noexcept { return _data[TupleIndex::YR]; }

private:
	enum TupleIndex
	{
		XL = 0,
		ZL = 1,
		YR = 2
	};

	using SerialDataMessage::SerialDataMessage;
};

#endif