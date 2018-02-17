#include <iostream>
#include <ga/ga.h>
#include "fitness.h"
#include "grade.h"

#define MAX_VALUE	4

typedef GA1DArrayGenome<int> Grade;

static float objective(GAGenome &g)
{
	auto &grade = static_cast<const Grade &>(g);

	Teacher_load f1(MAX_VALUE, 8, 12);

	for (int i = 0; i < grade.length(); i++) {
		f1.process(i, grade[i]);
	}

	return f1.evaluate();
}

static void GradeInitializer(GAGenome & g)
{
	auto &grade = static_cast<Grade &>(g);

	for (int i = 0; i < grade.length(); i++) {
		grade[i] = GARandomInt(0, MAX_VALUE);
	}
}

template<> int
Grade::write(std::ostream & os) const
{
	auto &grade = static_cast<const Grade &>(*this);

	for (auto t = 0; t < teacher_count(); t++) {
		os << "----" << teacher(t) << "----" << std::endl;
		for (int i = 0; i < grade.length(); i++) {
			if (grade[i] == t) {
				auto &s = get_student(i);
				os << "  " << s.name << std::endl;
			}
		}
	}

	return os.fail() ? 1 : 0;
}

int main()
{
	Grade genome(50, objective);
	genome.initializer(GradeInitializer);

	GAParameterList params;
	GASteadyStateGA::registerDefaultParameters(params);

	GASteadyStateGA ga(genome);
	ga.parameters(params);
  	ga.populationSize(1000);
	ga.maximize();
  	ga.selectScores(GAStatistics::AllScores);
  	ga.pMutation(0.02);
  	ga.pCrossover(1.0);
	ga.evolve();

	std::cout << ga.statistics() << std::endl;
	std::cout << ga.statistics().bestIndividual() << std::endl;

	return 0;
}
