#include <iostream>
#include <iomanip>
#include <ga/ga.h>
#include "fitness.h"
#include "grade.h"
#include "allotment.h"
#include "histogram.h"

typedef GA1DArrayGenome<int> Representation;

class Grade : public Allotment
{
	public:
		Grade(const Representation &genome)
			: genome_(genome)
		{
		}

		virtual uint16_t teacher(uint16_t student_id) const override
		{
			return genome_[student_id];
		}

	private:
		const Representation &genome_;
};

static float objective(GAGenome &g)
{
	auto &repr = static_cast<const Representation &>(g);

	Grade grade(repr);
	Teacher_load teacher_load(teacher_count());
	Friend_requests friend_requests;
	Academic_levels academic_levels(teacher_count());

	for (int i = 0; i < repr.length(); i++) {
		teacher_load.process(i, grade);
		friend_requests.process(i, grade);
		academic_levels.process(i, grade);
	}

	return teacher_load.evaluate()
	       	+ friend_requests.evaluate()
	       	+ academic_levels.evaluate();
}

static void RepresentationInitializer(GAGenome & g)
{
	auto &grade = static_cast<Representation &>(g);

	for (int i = 0; i < grade.length(); i++) {
		grade[i] = GARandomInt(0, teacher_count() - 1);
	}
}

static void writePrefs(const Student &s, uint16_t teacher_id,
	       	const Representation &grade, std::ostream & os)
{
	for (auto &p : s.prefs) {
		auto & info = get_student(p);
		if (teacher_id == grade[p]) {
			os << std::setw(15) << info.name;
		}
	}
}

template<> int
Representation::write(std::ostream & os) const
{
	auto &grade = static_cast<const Representation &>(*this);
	Histogram global_hist;

	auto &from = from_classes();

	for (auto t = 0; t < teacher_count(); t++) {
		os << "----" << teacher(t) << "----" << std::endl;
		os << "  "
			<< " |" << std::setw(15) << "Name"
			<< " |" << std::setw(3) << "Lvl"
			<< " |" << std::setw(5) << "From"
			<< " |" << std::setw(15) << "Friends"
			<< std::endl;

		Histogram hist;
		for (int i = 0; i < grade.length(); i++) {
			if (grade[i] == t) {
				auto &s = get_student(i);
				os << "  "
					<< " |" << std::setw(15) << s.name
					<< " |" << std::setw(3) << academic_level(s.level)
					<< " |" << std::setw(5) << from[s.prev_teacher]
					<< " |";

				writePrefs(s, t, grade, os);
				os << std::endl;

				hist[academic_level(s.level)]++;
				global_hist[academic_level(s.level)]++;
			}
		}
		os << std::endl
			<< "Academic level distribution in class" << std::endl
			<< hist << std::endl;
	}

	os << std::endl
		<< "Grade wide academic level distribution" << std::endl << std::endl
		<< global_hist;

	return os.fail() ? 1 : 0;
}

int main()
{
	Representation genome(student_count(), objective);

	genome.initializer(RepresentationInitializer);

	GAParameterList params;
	GASteadyStateGA::registerDefaultParameters(params);

	GASteadyStateGA ga(genome);
	params.set(gaNnGenerations, 5000);
	params.set(gaNscoreFrequency, 1);
	params.set(gaNflushFrequency, 50);
	params.set(gaNscoreFilename, "bog.dat");
	ga.parameters(params);
  	ga.populationSize(1000);
	ga.maximize();
  	ga.selectScores(GAStatistics::AllScores);
  	ga.pMutation(0.03);
  	ga.pCrossover(2.0);
	ga.evolve();

	//std::cout << ga.statistics() << std::endl;
	std::cout << ga.statistics().bestIndividual() << std::endl;

	return 0;
}
