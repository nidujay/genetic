#include "fitness.h"
#include "grade.h"

#include <cmath>
#include <iostream>

Teacher_load::Teacher_load(uint16_t n_teachers)
	: total_(0)
{
	for (auto i = 0; i < n_teachers; i++) {
		load_.push_back(0);
	}
}

void Teacher_load::process(uint16_t student, const Allotment &a)
{
	auto teacher = a.teacher(student);
	load_[teacher]++;
	total_++;
}

float Teacher_load::evaluate()
{
	const float target = static_cast<float>(total_) / load_.size();
	float score = 0.0;

	for (const auto &n : load_) {
		auto diff = fabs(target - n);
		score += static_cast<float>(total_ - diff) / total_;
	}

	return score / load_.size();
}

Friend_requests::Friend_requests()
	: total_(0),
	matches_(0)
{
}

void Friend_requests::process(uint16_t student, const Allotment &a)
{
	auto &s = get_student(student);
	bool matched = false;

	for (auto &peer : s.prefs) {
		total_++;
		if (!matched && a.teacher(student) == a.teacher(peer)) {
			matches_++;
			matched = true;
		}
	}
}

float Friend_requests::evaluate()
{
	return static_cast<float>(matches_) / static_cast<float>(total_);
}

bool is_all_students_allocated(const std::vector<int> &students)
{
	// values < 0 are indices to teachers
	return students[0] < 0;
}

Cross_mix::Cross_mix(uint16_t n_old_teachers, uint16_t n_new_teachers)
	: total_(0),
	  cell_count_(n_old_teachers * n_new_teachers)
{
	Previous_teachers p(n_old_teachers, 0);
	next_teachers_.assign(n_new_teachers, p);
}

void Cross_mix::process(uint16_t student, const Allotment &a)
{
	auto s = get_student(student);
	auto teacher = a.teacher(student);
	auto &prev_list = next_teachers_[teacher];
	prev_list[s.prev_teacher]++;
	total_++;
}

float Cross_mix::evaluate()
{
	auto cell_target = total_ / (cell_count_);
	float score = 0.0;

	for (const auto &prev_list : next_teachers_) {
		for (const auto &cell : prev_list) {
			auto diff = abs(cell - cell_target);
			if (diff <= 1) {
				score++;
			}
		}
	}

	return (score / cell_count_) / 2;
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
