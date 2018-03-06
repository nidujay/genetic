#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

#include "json.hpp"

#define ACADEMIC_LEVELS(macro)	\
	macro(Q1)		\
	macro(Q2)		\
	macro(Q3)		\
	macro(Q4)

#define ACADEMIC_LEVEL_ENUM(level)	level,
enum Academic_level
{
	ACADEMIC_LEVELS(ACADEMIC_LEVEL_ENUM)
};

struct Student
{
	uint16_t prev_teacher;
	std::string name;
	Academic_level level;
	std::vector<int> prefs;
};

class Grade_info
{
	public:
		Grade_info(std::istream &s);

		const std::vector<std::string> &teachers() const;
		const std::vector<std::string> &from_classes() const;
		const std::vector<Student> &students() const;

	private:
		std::vector<std::string> teachers_;
		std::vector<Student> students_;
		std::vector<std::string> from_;

		typedef std::map<std::string, uint16_t> Student_id_map;
		void parse_student(const nlohmann::json &s, const Student_id_map &);

		uint16_t extract_from_id(const std::string &from);
};

// The following are convenience functions for old
// design
int student_count();
const Student &get_student(int id);

int teacher_count();
const std::string teacher(int id);

const std::vector<std::string> &from_classes();

std::string academic_level(Academic_level l);
const std::vector<std::string> &academic_levels();

#endif
