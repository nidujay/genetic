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
		if (!matched && a.teacher(student) == a.teacher(peer)) {
			matches_++;
			matched = true;
		}
	}
	total_++;
}

float Friend_requests::evaluate()
{
	return static_cast<float>(matches_) / static_cast<float>(total_);
}

Academic_levels::Academic_levels(uint16_t n_teachers)
	: class_dist_(n_teachers),
	  total_(0)
{
}

void Academic_levels::process(uint16_t student, const Allotment &a)
{
	auto s = get_student(student);
	auto level = academic_level(s.level);
	dist_[level]++;
	auto teacher = a.teacher(student);
	auto &cd = class_dist_[teacher];
	cd[level]++;
	total_++;
}

float Academic_levels::evaluate()
{
	float score = 0;
	const auto &levels = academic_levels();

	for (const auto &l : levels) {
		const auto target = static_cast<float>(dist_[l]) / class_dist_.size();
		for (const auto &cd : class_dist_) {
			auto actual = cd[l];
			float diff = fabs(target - actual);
			score += (total_ - diff) / total_;
		}
	}

	return (score / levels.size()) / class_dist_.size();
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

