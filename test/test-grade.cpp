#include <CppUTest/TestHarness.h>
#include <fitness.h>
#include <grade.h>
#include <sstream>
#include <exception>

TEST_GROUP(Grade)
{
};

TEST(Grade, Teachers_StreamWithArrayOfTeachers__ReturnsExpected)
{
	std::stringstream ss(
		R"(
		{
			"teachers": ["John", "Paul", "Mary"]
		}
		)"
	);

	const std::vector<std::string> expected = {"John", "Paul", "Mary"};

	Grade_info gi(ss);
	CHECK(expected == gi.teachers());
}

bool operator==(const Student& lhs, const Student& rhs)
{
	return lhs.prev_teacher == rhs.prev_teacher
		&& lhs.name == rhs.name
		&& lhs.level == rhs.level
		&& lhs.prefs == rhs.prefs;
}

TEST(Grade, Students_StreamWithArrayOfOneStudent__NameOfStudentAsExpected)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1B",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &students = gi.students();
 	CHECK_EQUAL(1, students.size());
 	CHECK_EQUAL(std::string("Student Name"), students[0].name);
}

TEST(Grade, Students_StreamWithArrayOfOneStudent__LevelOfStudentAsExpected)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1B",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &students = gi.students();
 	CHECK_EQUAL(1, students.size());
 	CHECK_EQUAL(Q1, students[0].level);
}

TEST(Grade, Students_StreamWithInvalidLevel__ThrowsInvalidArgument)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1B",
				"name": "Student Name",
				"level": "Q0",
				"friends": []
			}
		]
	}
	)");

	CHECK_THROWS(std::invalid_argument, Grade_info(ss));
}

TEST(Grade, Students_StreamWithArrayOfStudents__ParsesFromAsNumericIndex)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1A",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			},
			{
				"from": "Grade 1B",
				"name": "Student Name 2",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &students = gi.students();
 	CHECK_EQUAL(0, students[0].prev_teacher);
 	CHECK_EQUAL(1, students[1].prev_teacher);
}

TEST(Grade, From_StreamWithArrayOfStudents__FromIndexMatchesStudentFromField)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1A",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			},
			{
				"from": "Grade 1B",
				"name": "Student Name 2",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &from = gi.from_classes();
	const std::vector<std::string> expected = {
		"Grade 1A",
		"Grade 1B"
	};

 	CHECK(expected == from);
}

TEST(Grade, From_StreamWithArrayOfStudentsFromSameClass__DuplicateFromFieldsMerged)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1A",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			},
			{
				"from": "Grade 1A",
				"name": "Student Name 2",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &from = gi.from_classes();
	const std::vector<std::string> expected = {
		"Grade 1A",
	};

 	CHECK(expected == from);
}

TEST(Grade, From_StreamWithArrayOfStudentsFromSameClass__BothStudentFromFieldsSame)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1A",
				"name": "Student Name",
				"level": "Q1",
				"friends": []
			},
			{
				"from": "Grade 1A",
				"name": "Student Name 2",
				"level": "Q1",
				"friends": []
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &students = gi.students();

 	CHECK_EQUAL(0, students[0].prev_teacher);
 	CHECK_EQUAL(0, students[1].prev_teacher);
}

// friends: indices match vector offsets of students
TEST(Grade, Students_StudentWithFriendsNominated__FriendsFieldsAsExpected)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1A",
				"name": "Student Name 1",
				"level": "Q1",
				"friends": [
					"Student Name 2",
					"Student Name 3"
				]
			},
			{
				"from": "Grade 1A",
				"name": "Student Name 2",
				"level": "Q1",
				"friends": [
					"Student Name 3",
					"Student Name 1"
				]
			},
			{
				"from": "Grade 1A",
				"name": "Student Name 3",
				"level": "Q1",
				"friends": [
					"Student Name 1",
					"Student Name 2"
				]
			}
		]
	}
	)");

	const std::vector<int> expected = {
		1, 2
	};

	Grade_info gi(ss);
	const auto &students = gi.students();

 	CHECK(expected == students[0].prefs);
}

TEST(Grade, Grade_StudentWithoutNominatedFriends__DoesNotThrow)
{
	std::stringstream ss(R"(
	{
		"teachers": ["a", "b"],
		"students": [
			{
				"from": "Grade 1B",
				"name": "Student Name",
				"level": "Q1"
			}
		]
	}
	)");

	Grade_info gi(ss);
	const auto &students = gi.students();
	CHECK_EQUAL(0, students[0].prefs.size());
}

// friends: Throws if friend name is not in students list
