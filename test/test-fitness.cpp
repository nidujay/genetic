#include <CppUTest/TestHarness.h>
#include <fitness.h>
#include <grade.h>

TEST_GROUP(Fitness)
{
};

#if 0
TEST(Fitness, FirstSpotAllocatedToTeacher)
{
	std::vector<int> students;
	students.push_back(-1);
 	CHECK_EQUAL(true, is_all_students_allocated(students));
}

TEST(Fitness, ValidSizeClassCount_AllClassesWithinLimits_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(1);
	students.push_back(2);
	students.push_back(-2);
	students.push_back(3);
	students.push_back(4);

 	CHECK_EQUAL(2, valid_class_size_count(students, 2, 2));
}

TEST(Fitness, ValidSizeClassCount_SomeClassesTooSmall_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(1);
	students.push_back(-2);
	students.push_back(3);
	students.push_back(4);

 	CHECK_EQUAL(1, valid_class_size_count(students, 2, 2));
}

TEST(Fitness, ValidSizeClassCount_SomeClassesTooBig_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(1);
	students.push_back(2);
	students.push_back(-2);
	students.push_back(3);
	students.push_back(4);
	students.push_back(5);

 	CHECK_EQUAL(1, valid_class_size_count(students, 2, 2));
}

TEST(Fitness, ValidSizeClassCount_ContainsEmptyClasses_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(-2);
	students.push_back(3);
	students.push_back(4);

 	CHECK_EQUAL(1, valid_class_size_count(students, 2, 2));
}

TEST(Fitness, ValidSizeClassCount_LastClassEmpty_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(1);
	students.push_back(2);
	students.push_back(-2);

 	CHECK_EQUAL(1, valid_class_size_count(students, 2, 2));
}

TEST(Fitness, ValidSizeClassCount_FirstClassEmpty_ReturnsValidCount)
{
	std::vector<int> students;
	students.push_back(-1);
	students.push_back(-2);
	students.push_back(1);
	students.push_back(2);

 	CHECK_EQUAL(1, valid_class_size_count(students, 2, 2));
}

static const Student *mock_list;
static int mock_list_count;

const Student &get_student(int id)
{
	if (id >= mock_list_count) {
		throw "Bad ref";
	}

	return mock_list[id];
}

TEST(Fitness, SatisifiedPeerPrefCount_FirstStudentSatisfied_ReturnsMatchCount)
{
	const Student dummy[] =
	{
		{0, "Student 0", { 1, 2, 3, 4}},
		{0, "Student 1", { 4, 4, 4, 4}},
		{0, "Student 2", { 4, 4, 4, 4}},
		{0, "Student 3", { 4, 4, 4, 4}},
	};

	mock_list = dummy;
	mock_list_count = sizeof(dummy)/sizeof(dummy[0]);

	std::vector<int> students = {-1, 0, 1, 2, 3};
 	CHECK_EQUAL(3, satisfied_peer_pref_count(students));
}

TEST(Fitness, SatisifiedPeerPrefCount_NoneSatisfied_ReturnsMatchCount)
{
	const Student dummy[] =
	{
		{0, "Student 0", { 4, 4, 4, 4}},
		{0, "Student 1", { 4, 4, 4, 4}},
		{0, "Student 2", { 4, 4, 4, 4}},
		{0, "Student 3", { 4, 4, 4, 4}},
	};

	mock_list = dummy;
	mock_list_count = sizeof(dummy)/sizeof(dummy[0]);

	std::vector<int> students = {-1, 0, 1, 2, 3};
 	CHECK_EQUAL(0, satisfied_peer_pref_count(students));
}

TEST(Fitness, SatisifiedPeerPrefCount_TwoClassesWithMatchesInSecond_ReturnsMatchCount)
{
	const Student dummy[] =
	{
		{0, "Student 0", { 4, 4, 4, 4}},
		{0, "Student 1", { 4, 4, 4, 4}},
		{0, "Student 2", { 4, 4, 4, 4}},
		{0, "Student 3", { 4, 4, 4, 4}},
		{0, "Student 4", { 5, 6, 7, 9}},
		{0, "Student 5", { 9, 9, 9, 9}},
		{0, "Student 6", { 9, 9, 9, 9}},
		{0, "Student 7", { 9, 9, 9, 9}},
	};

	mock_list = dummy;
	mock_list_count = sizeof(dummy)/sizeof(dummy[0]);

	std::vector<int> students = {-1, 0, 1, 2, 3, -2, 4, 5, 6, 7};
 	CHECK_EQUAL(3, satisfied_peer_pref_count(students));
}

TEST(Fitness, SatisifiedPeerPrefCount_StudentsWithUndefinedPreferences_ReturnsMatchCount)
{
	const Student dummy[] =
	{
		{0, "Student 0", { -1, -1, -1, -1}},
		{0, "Student 1", { -1, -1, -1, -1}},
		{0, "Student 2", { -1, -1, -1, -1}},
		{0, "Student 3", { -1, -1, -1, -1}},
		{0, "Student 4", { 5, 6, 7, -1}},
		{0, "Student 5", { -1, -1, -1, -1}},
		{0, "Student 6", { -1, -1, -1, -1}},
		{0, "Student 7", { -1, -1, -1, -1}},
	};

	mock_list = dummy;
	mock_list_count = sizeof(dummy)/sizeof(dummy[0]);

	std::vector<int> students = {-1, 0, 1, 2, 3, -2, 4, 5, 6, 7};
 	CHECK_EQUAL(3, satisfied_peer_pref_count(students));
}
#endif
