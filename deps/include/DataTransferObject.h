#ifndef DATA_TRANSFER_OBJECT_H
#define DATA_TRANSFER_OBJECT_H

#include "ISerializable.h"

class DataTransferObject : public ISerializable
{
public:
	DataTransferObject(const void* const data, const std::size_t dataSize);
    DataTransferObject(DataTransferObject&& dto);
	~DataTransferObject();

	inline const void* const getRawData() const noexcept override { return _data; }
	inline const std::size_t getRawDataSize() const noexcept override { return _dataSize; }

private:
	void* _data;
	const std::size_t _dataSize;
};

#endif