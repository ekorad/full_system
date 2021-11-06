#include "DataTransferObject.h"
#include <stdexcept>
#include <cstring>

using std::runtime_error;
using std::memcpy;
using std::free;

DataTransferObject::DataTransferObject(const void* const data, const std::size_t dataSize)
	: _dataSize{ dataSize }
{
	if (!data)
	{
		throw runtime_error("Null message data");
	}
	else
	{
		_data = malloc(dataSize);
		memcpy(_data, data, dataSize);
	}
}

DataTransferObject::DataTransferObject(DataTransferObject&& dto)
	: _data{ dto._data }, _dataSize{ dto._dataSize }
{
	dto._data = nullptr;
}

DataTransferObject::~DataTransferObject()
{
	if (_data)
	{
		free(_data);
	}
}