#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>
#include <cstdint>

enum Academic_level
{
	Q1,
	Q2,
	Q3,
	Q4
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

#endif
