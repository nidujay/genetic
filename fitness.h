#ifndef FITNESS_H
#define FITNESS_H

#include <cstdint>
#include <vector>

#include "allotment.h"

class Fitness
{
	public:
		virtual void process(uint16_t student, const Allotment &a) = 0;
		virtual float evaluate() = 0;
};

// Ensure teacher load within acceptable limits
class Teacher_load : public Fitness
{
	public:
		Teacher_load(uint16_t n_teachers);

		virtual void process(uint16_t student, const Allotment &a) override;
		virtual float evaluate() override;

	private:
		std::vector<uint16_t> load_;
		uint16_t total_;
};

// Ensure at-least one of the requested friends are in new class
class Friend_requests : public Fitness
{
	public:
		Friend_requests();
		virtual void process(uint16_t student, const Allotment &a) override;
		virtual float evaluate() override;

	private:
		uint16_t total_;
		uint16_t matches_;
};

// Ensure that students are mixed across classes
class Cross_mix : public Fitness
{
	public:
		Cross_mix(uint16_t n_old_teachers, uint16_t n_new_teachers);
		virtual void process(uint16_t student, const Allotment &a) override;
		virtual float evaluate() override;

	private:
		// This is a 2D array that keeps track of how many students
		// for the new teacher share the same previous teacher. The goal
		// is the even this out.
		uint16_t total_;
		uint16_t cell_count_;
		typedef std::vector<uint16_t> Previous_teachers;
		typedef std::vector<Previous_teachers> Next_teachers;

		Next_teachers next_teachers_;
};

bool is_all_students_allocated(const std::vector<int> &students);
int valid_class_size_count(const std::vector<int> &students, int min_size, int max_size);
int satisfied_peer_pref_count(const std::vector<int> &students);

#endif
