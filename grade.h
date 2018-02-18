#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>

struct Student
{
	int class_id;
	std::string name;
	std::vector<int> prefs;
};

int student_count();
const Student &get_student(int id);

int teacher_count();
const std::string teacher(int id);

#endif
