#ifndef ALLOTMENT_H
#define ALLOTMENT_H

#include <cstdint>

class Allotment
{
	public:
		virtual uint16_t teacher(uint16_t student_id) const = 0;
};

#endif
