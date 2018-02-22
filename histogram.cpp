#include <iostream>
#include "histogram.h"

const uint16_t Histogram::operator[](const std::string &bucket) const
{
	try {
		return bins_.at(bucket);
	} catch(std::out_of_range &e) {
		return 0;
	}
}

uint16_t &Histogram::operator[](const std::string &bucket)
{
	return bins_[bucket];
}

std::ostream& operator<< (std::ostream& stream, const Histogram &h)
{
	for (const auto &pair : h.bins_) {
		stream << pair.first << " ";
		for (auto i = 0; i < pair.second; i++) {
			stream << '#';
		}
		stream << std::endl;
	}

	return stream;
}
