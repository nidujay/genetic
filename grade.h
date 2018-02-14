#ifndef GRADE_H
#define GRADE_H

#include <string>

struct Student
{
	int class_id;
	std::string name;
	int prefs[4];
};

int student_count();
const Student &get_student(int id);

int teacher_count();
const std::string teacher(int id);

#endif
