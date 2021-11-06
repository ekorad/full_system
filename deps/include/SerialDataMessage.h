#ifndef SERIAL_DATA_MESSAGE_H
#define SERIAL_DATA_MESSAGE_H

#include "ISerializable.h"
#include <vector>

template <typename DataType>
class SerialDataMessage : public ISerializable
{
public:
	template <typename... Data>
	SerialDataMessage(const Data&... data);

	inline const std::vector<DataType>& getData() const noexcept { return _data; }
	inline const void* const getRawData() const noexcept override;
	inline const std::size_t getRawDataSize() const noexcept override;

protected:
	std::vector<DataType> _data;
};

template <typename DataType>
template <typename... Data>
SerialDataMessage<DataType>::SerialDataMessage(const Data&... data)
	:_data{ data... } {}

template <typename DataType>
inline const void* const SerialDataMessage<DataType>::getRawData() const noexcept
{
	return _data.data();
}

template <typename DataType>
inline const std::size_t SerialDataMessage<DataType>::getRawDataSize() const noexcept
{
	return sizeof(DataType) * _data.size();
}

#endif