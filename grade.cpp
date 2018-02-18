#include "grade.h"

static const std::string teachers[] = {
	"Teacher A",
	"Teacher B",
	"Teacher C",
	"Teacher D",
	"Teacher E",
};

static const Student students[] = {
	{  0 , "Brice Rubio", {7,5,1,} },
	{  0 , "Heidy Manning", {7,8,4,} },
	{  0 , "Camryn Swanson", {9,5,7,4,} },
	{  0 , "Yael Washington", {9,6,0,} },
	{  0 , "Karsyn Osborne", {9,1,7,} },
	{  0 , "Bradyn Ali", {4,6,0,} },
	{  0 , "Skye Hood", {8,4,1,2,} },
	{  0 , "Halle Drake", {4,8,2,0,} },
	{  0 , "Destinee Morton", {5,9,6,2,} },
	{  0 , "Jamir Schneider", {3,2,7,6,} },
	{  1 , "Emma Hogan", {17,16,11,} },
	{  1 , "Christine Sanders", {17,13,16,10,} },
	{  1 , "Salma Horn", {11,19,10,} },
	{  1 , "Clay Shelton", {12,19,16,15,} },
	{  1 , "Peyton Mays", {13,17,15,18,} },
	{  1 , "Miles Chambers", {17,14,11,10,} },
	{  1 , "Pamela Yoder", {18,19,10,} },
	{  1 , "Jayvion Hopkins", {14,12,15,} },
	{  1 , "Carlie Galvan", {11,19,17,16,} },
	{  1 , "Messiah Hobbs", {17,11,16,15,} },
	{  2 , "Daniela Rosales", {23,26,25,29,} },
	{  2 , "Jordan Arroyo", {28,29,22,} },
	{  2 , "Jensen Robles", {24,21,27,20,} },
	{  2 , "Savanah Lam", {26,28,21,} },
	{  2 , "Darwin Middleton", {23,29,22,20,} },
	{  2 , "Nyasia Randall", {22,21,24,23,} },
	{  2 , "Marc Nixon", {20,22,27,} },
	{  2 , "Abigayle Downs", {23,26,21,} },
	{  2 , "Sullivan Skinner", {21,23,24,} },
	{  2 , "Hallie Morrison", {21,26,24,28,} },
	{  3 , "Ethen Howe", {37,39,38,34,} },
	{  3 , "Kristina Montoya", {39,38,30,37,} },
	{  3 , "Cali Archer", {35,31,36,33,} },
	{  3 , "Rebekah Hawkins", {37,35,36,32,} },
	{  3 , "Taniyah Kerr", {39,37,32,36,} },
	{  3 , "Janiyah Ball", {32,37,34,} },
	{  3 , "Maverick Peck", {37,32,35,39,} },
	{  3 , "Karina Mitchell", {35,33,39,38,} },
	{  3 , "Ronnie Schmitt", {33,35,32,34,} },
	{  3 , "Bernard Welch", {36,37,33,} },
	{  4 , "Edith Montes", {44,46,47,48,} },
	{  4 , "Ashlee Stephenson", {48,43,42,44,} },
	{  4 , "Danna Yu", {46,43,41,45,} },
	{  4 , "Izayah Oliver", {47,49,42,48,} },
	{  4 , "Livia Barnett", {45,41,42,47,} },
	{  4 , "Davion Benton", {42,43,49,} },
	{  4 , "Yuliana Garrison", {43,42,45,} },
	{  4 , "Serena Ho", {48,46,40,} },
	{  4 , "Quintin Ortega", {46,43,42,} },
	{  4 , "Sawyer Arellano", {43,46,45,} },
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
