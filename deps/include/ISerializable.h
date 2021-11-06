#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <cstddef>

class ISerializable
{
public:
	virtual inline const void* const getRawData() const noexcept = 0;
	virtual inline const std::size_t getRawDataSize() const noexcept = 0;
};

#endif