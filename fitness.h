#ifndef FITNESS_H
#define FITNESS_H

#include <cstdint>
#include <vector>

class Fitness
{
	public:
		virtual void process(uint16_t student, uint16_t teacher) = 0;
		virtual float evaluate() = 0;
};

class Teacher_load : public Fitness
{
	public:
		Teacher_load(uint16_t n_teachers,
				uint16_t min_students, uint16_t max_students);

		virtual void process(uint16_t student, uint16_t teacher) override;
		virtual float evaluate() override;

	private:
		std::vector<uint16_t> load_;
		uint16_t min_;
		uint16_t max_;
};

bool is_all_students_allocated(const std::vector<int> &students);
int valid_class_size_count(const std::vector<int> &students, int min_size, int max_size);
int satisfied_peer_pref_count(const std::vector<int> &students);

#endif
