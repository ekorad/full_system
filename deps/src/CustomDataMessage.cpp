#include "CustomDataMessage.h"

CustomDataMessage::CustomDataMessage(const double xl, const double zl, const double yr)
	: SerialDataMessage{ xl, zl, yr } {}