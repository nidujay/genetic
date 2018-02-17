#include <iostream>
#include <ga/ga.h>

#define MAX_VALUE	4

typedef GA1DArrayGenome<int> Grade;

static float objective(GAGenome &g)
{
	auto &grade = static_cast<const Grade &>(g);
	float score = 0.0;

	for (int i = 0; i < grade.length(); i++) {
		if (grade[i] == (i % (MAX_VALUE + 1))) {
			score++;
		}
	}

	return score;
}

static void GradeInitializer(GAGenome & g)
{
	auto &grade = static_cast<Grade &>(g);

	for (int i = 0; i < grade.length(); i++) {
		grade[i] = GARandomInt(0, MAX_VALUE);
	}
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
