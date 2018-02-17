#include "fitness.h"
#include "grade.h"
#include <iostream>

Teacher_load::Teacher_load(uint16_t n_teachers,
		uint16_t min_students, uint16_t max_students)
	: min_(min_students),
	max_(max_students)
{
	for (auto i = 0; i < n_teachers; i++) {
		load_.push_back(0);
	}
}

void Teacher_load::process(uint16_t student, uint16_t teacher)
{
	load_[teacher]++;
}

float Teacher_load::evaluate()
{
	float score = 0.0;

	for (auto &n : load_) {
		if (n >= min_ && n <= max_) {
			score++;
		}
	}

	return score / load_.size();
}

bool is_all_students_allocated(const std::vector<int> &students)
{
	// values < 0 are indices to teachers
	return students[0] < 0;
}

static std::vector<int> next_class(const std::vector<int> &grade,
	std::vector<int>::const_iterator &iter)
{
	std::vector<int> rv;
	bool found_head = false;

	for(; iter != grade.end(); iter++) {
		if (found_head) {
			if (*iter < 0) {
				break;
			}
			rv.push_back(*iter);
		} else {
			if (*iter < 0) {
				rv.push_back(*iter);
				found_head = true;
			}
		}
	}

	return rv;
}

int valid_class_size_count(const std::vector<int> &students, int min_size, int max_size)
{
	int count = 0;
	int size = 0;

	for (auto i = students.begin(); ; i++) {
		if ((*i < 0 ) || i == students.end()) {
			if ((size >= min_size) && (size <= max_size)) {
				count++;
			}
			size = 0;
			if ( i == students.end()) {
				break;
			}
		} else {
			size++;
		}
	}

	return count;
}

static int count_matching_preferences(const Student &s, int candidate)
{
	int count = 0;
	for (int i=0; i < sizeof(s.prefs)/sizeof(s.prefs[0]); i++) {
		if (s.prefs[i] == candidate) {
			count++;
		}
	}
	return count;
}

static int count_matching_preferences(const Student &s,
	const std::vector<int> &class_mates)
{
	int count = 0;
	for (auto i : class_mates) {
		if (i < 0)
			continue;

		count += count_matching_preferences(s, i);
	}

	return count;
}

int satisfied_peer_pref_count(const std::vector<int> &students)
{
	int count = 0;
	auto iter = students.begin();

	do
	{
		auto class_ = next_class(students, iter);
		for (auto i : class_) {
			if (i < 0)
				continue;

			auto s = get_student(i);
			count += count_matching_preferences(s, class_);
		}
	} while (iter != students.end());

	return count;
}
