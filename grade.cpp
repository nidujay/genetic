#include "grade.h"

#define ACADEMIC_LEVEL_STRING(level) std::string(#level),
static const std::vector<std::string> levels = {
	ACADEMIC_LEVELS(ACADEMIC_LEVEL_STRING)
};

std::string academic_level(Academic_level l)
{
	return levels[l];
}

const std::vector<std::string> &academic_levels()
{
	return levels;
}

static Academic_level level_from_string(const std::string &s)
{
	auto it = std::find(levels.begin(), levels.end(), s);
	if (it == levels.end()) {
		throw std::invalid_argument(s);
	}

	return static_cast<Academic_level>(std::distance(levels.begin(), it));
}

Grade_info::Grade_info(std::istream &is)
{
	nlohmann::json j;

	is >> j;
	teachers_ = j["teachers"].get<std::vector<std::string>>();

	Student_id_map id_map;
	uint16_t id = 0;
	for (const auto &s : j["students"]) {
		id_map[s["name"]] = id++;
	}

	for (const auto &s : j["students"]) {
		parse_student(s, id_map);
	}
}

void Grade_info::parse_student(const nlohmann::json &s, const Student_id_map &id_map)
{
	Student parsed;

	parsed.name = s["name"];
	parsed.level = level_from_string(s["level"]);
	parsed.prev_teacher = extract_from_id(s["from"]);

	if (s.find("friends") != s.end()) {
		for (const auto &f : s["friends"]) {
			uint16_t id = id_map.at(f);
			parsed.prefs.push_back(id);
		}
	}

	students_.push_back(parsed);
}

uint16_t Grade_info::extract_from_id(const std::string &from)
{
	uint16_t result = 0;

	auto it = std::find(from_.begin(), from_.end(), from);
	if (it == from_.end()) {
		result = from_.size();
		from_.push_back(from);
	} else {
		result = std::distance(from_.begin(), it);
	}

	return result;
}

const std::vector<std::string> &Grade_info::teachers() const
{
	return teachers_;
}

const std::vector<Student> &Grade_info::students() const
{
	return students_;
}

const std::vector<std::string> &Grade_info::from_classes() const
{
	return from_;
}

static const Grade_info &instance()
{
	static Grade_info gi(std::cin);

	return gi;
}

int student_count()
{
	auto &gi = instance();
	return gi.students().size();
}

const Student &get_student(int id)
{
	auto &gi = instance();
	auto &students = gi.students();

	return students[id];
}

int teacher_count()
{
	auto &gi = instance();
	auto &teachers = gi.teachers();

	return teachers.size();
}

const std::vector<std::string> &from_classes()
{
	auto &gi = instance();
	return gi.from_classes();
}

const std::string teacher(int id)
{
	auto &gi = instance();
	auto &teachers = gi.teachers();

	return teachers[id];
}


