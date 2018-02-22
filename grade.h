#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>
#include <cstdint>

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

int student_count();
const Student &get_student(int id);

int teacher_count();
const std::string teacher(int id);

std::string academic_level(Academic_level l);
const std::vector<std::string> &academic_levels();

#endif
