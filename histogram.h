#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cstdint>
#include <map>
#include <iostream>

class Histogram
{
	public:
		const uint16_t operator[](const std::string &bucket) const;
		uint16_t &operator[](const std::string &bucket);

		friend std::ostream& operator<< (std::ostream& stream, const Histogram &h);

	private:
		std::map<std::string, uint16_t> bins_;
};

#endif
