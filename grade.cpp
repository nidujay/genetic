#include "grade.h"

static const std::string teachers[] = {
	"Teacher A",
	"Teacher B",
	"Teacher C",
	"Teacher D",
};

static const Student students[] = {
	{ 0, "Student 0", Q2, {60,61,59,23,}},
	{ 7, "Student 1", Q3, {37,79,10,}},
	{ 0, "Student 2", Q3, {23,60,61,}},
	{ 3, "Student 3", Q2, {16,18,50,77,}},
	{ 4, "Student 4", Q3, {34,9,43,}},
	{ 2, "Student 5", Q1, {19,36,49,12,}},
	{ 5, "Student 6", Q2, {26,29,66,76,}},
	{ 1, "Student 7", Q2, {55,14,64,}},
	{ 6, "Student 8", Q2, {32,25,35,}},
	{ 4, "Student 9", Q2, {4,67,34,}},
	{ 7, "Student 10", Q1, {44,37,1,73,}},
	{ 2, "Student 11", Q2, {40,75,17,5,}},
	{ 2, "Student 12", Q1, {19,74,49,63,}},
	{ 7, "Student 13", Q2, {10,79,44,}},
	{ 1, "Student 14", Q3, {64,39,20,69,}},
	{ 7, "Student 15", Q2, {10,1,79,}},
	{ 3, "Student 16", Q2, {3,77,70,50,}},
	{ 2, "Student 17", Q4, {40,5,74,63,}},
	{ 3, "Student 18", Q4, {16,56,45,77,}},
	{ 2, "Student 19", Q3, {46,31,24,63,}},
	{ 1, "Student 20", Q4, {7,14,69,64,}},
	{ 1, "Student 21", Q3, {30,69,53,}},
	{ 5, "Student 22", Q4, {6,47,62,29,}},
	{ 0, "Student 23", Q2, {0,2,82,54,}},
	{ 2, "Student 24", Q2, {5,17,40,}},
	{ 6, "Student 25", Q3, {32,28,48,}},
	{ 5, "Student 26", Q2, {76,29,47,}},
	{ 7, "Student 27", Q4, {79,71,68,}},
	{ 6, "Student 28", Q3, {8,25,35,}},
	{ 5, "Student 29", Q3, {62,26,51,}},
	{ 1, "Student 30", Q2, {55,53,41,69,}},
	{ 2, "Student 31", Q2, {17,49,24,63,}},
	{ 6, "Student 32", Q3, {35,48,25,}},
	{ 0, "Student 33", Q1, {60,0,59,78,}},
	{ 4, "Student 34", Q2, {4,43,9,}},
	{ 6, "Student 35", Q4, {48,25,28,}},
	{ 2, "Student 36", Q2, {24,49,31,52,}},
	{ 7, "Student 37", Q1, {44,68,13,}},
	{ 1, "Student 38", Q2, {20,64,55,69,}},
	{ 1, "Student 39", Q3, {21,57,7,20,}},
	{ 2, "Student 40", Q1, {11,75,63,}},
	{ 1, "Student 41", Q2, {57,30,64,}},
	{ 5, "Student 42", Q3, {47,29,51,}},
	{ 4, "Student 43", Q1, {4,34,9,}},
	{ 7, "Student 44", Q2, {37,71,10,}},
	{ 3, "Student 45", Q3, {77,16,70,50,}},
	{ 2, "Student 46", Q4, {19,63,49,24,}},
	{ 5, "Student 47", Q2, {6,66,62,}},
	{ 6, "Student 48", Q1, {25,28,32,}},
	{ 2, "Student 49", Q1, {19,11,52,12,}},
	{ 3, "Student 50", Q2, {45,3,18,}},
	{ 5, "Student 51", Q4, {29,26,42,47,}},
	{ 2, "Student 52", Q4, {74,80,75,}},
	{ 1, "Student 53", Q4, {55,64,30,39,}},
	{ 0, "Student 54", Q1, {81,59,65,61,}},
	{ 1, "Student 55", Q2, {30,69,20,53,}},
	{ 3, "Student 56", Q2, {58,3,50,}},
	{ 1, "Student 57", Q3, {69,39,7,}},
	{ 3, "Student 58", Q4, {50,70,56,45,}},
	{ 0, "Student 59", Q4, {54,33,23,}},
	{ 0, "Student 60", Q3, {59,33,78,61,}},
	{ 0, "Student 61", Q4, {60,65,33,}},
	{ 5, "Student 62", Q3, {6,47,29,66,}},
	{ 2, "Student 63", Q2, {80,12,49,}},
	{ 1, "Student 64", Q2, {55,21,39,14,}},
	{ 0, "Student 65", Q1, {72,59,33,82,}},
	{ 5, "Student 66", Q3, {62,22,76,47,}},
	{ 4, "Student 67", Q2, {43,9,34,}},
	{ 7, "Student 68", Q2, {27,73,13,15,}},
	{ 1, "Student 69", Q2, {21,41,30,57,}},
	{ 3, "Student 70", Q4, {16,45,18,3,}},
	{ 7, "Student 71", Q4, {79,68,37,1,}},
	{ 0, "Student 72", Q3, {59,81,54,60,}},
	{ 7, "Student 73", Q3, {37,1,71,10,}},
	{ 2, "Student 74", Q2, {24,5,49,12,}},
	{ 2, "Student 75", Q3, {49,31,40,5,}},
	{ 5, "Student 76", Q2, {66,42,51,47,}},
	{ 3, "Student 77", Q3, {3,56,18,70,}},
	{ 0, "Student 78", Q4, {72,60,65,81,}},
	{ 7, "Student 79", Q1, {1,73,71,44,}},
	{ 2, "Student 80", Q3, {12,31,5,17,}},
	{ 0, "Student 81", Q3, {33,23,61,0,}},
	{ 0, "Student 82", Q2, {72,59,81,61,}},
};

int student_count()
{
	return sizeof(students)/sizeof(students[0]);
}

const Student &get_student(int id)
{
	if (id >= student_count()) {
		throw "out of bounds";
	}

	return students[id];
}

int teacher_count()
{
	return sizeof(teachers)/sizeof(teachers[0]);
}

const std::string teacher(int id)
{
	if (id >= teacher_count()) {
		throw "out of bounds";
	}

	return teachers[id];
}
