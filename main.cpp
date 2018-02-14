#include <iostream>
#include <vector>
#include <ga/ga.h>
#include "fitness.h"
#include "grade.h"

static std::vector<int> to_std_vector(const GAListGenome<int> &g)
{
	std::vector<int> rv;
	GAListIter<int> tmp(g);

	int *tail = tmp.tail();
	for (int *i=tmp.head(); i ; i=tmp.next()) {
		rv.push_back(*i);
		if (i == tail)
			break;
	}
	return rv;
}

static float objective(GAGenome &g)
{
	float score = 0.0;
	std::vector<int> v = to_std_vector((GAListGenome<int> &)g);

	if (is_all_students_allocated(v)) {
		score += 1;
	}
	score += valid_class_size_count(v, 8, 12);
#if 1
	score += satisfied_peer_pref_count(v)/ 100;
#endif
	return score;
}

static void ListInitializer(GAGenome & c)
{
	GAListGenome<int> &child=(GAListGenome<int> &)c;
	while(child.head()) child.destroy(); // destroy any pre-existing list

	// First insert the students
	int n=student_count();
	child.insert(0,GAListBASE::HEAD); // the head node contains a '0'
	for(int i=1; i<n; i++)
		child.insert(i);		// each subsequent node contains a number

	// Now insert the teachers
	for (int i=0; i<teacher_count(); i++) {
		child.insert(-i - 1);
	}

	// Jumble them all up
	for(int j=0; j<n; j++)
		child.swap(GARandomInt(0,n-1), GARandomInt(0,n-1));
}

template<> int
GAListGenome<int>::write(std::ostream & os) const
{
	std::vector<int> v = to_std_vector(*this);

	std::vector<int>::const_iterator iter;
	for (iter = v.begin(); iter != v.end(); iter++) {
		int i = *iter;
		if (i < 0) {
			os << "----" << teacher(-i - 1) << "----" << std::endl;
		} else {
			auto s = get_student(i);
			os << s.name << std::endl;
		}
	}

	return os.fail() ? 1 : 0;
}

int main()
{
	GAParameterList params;
	GASteadyStateGA::registerDefaultParameters(params);
	params.set(gaNpopulationSize, 1000);	// population size
	params.set(gaNpCrossover, 0.6);		// probability of crossover
	params.set(gaNpMutation, 0.01);		// probability of mutation
	params.set(gaNnGenerations, 5000);	// number of generations
	params.set(gaNpReplacement, 0.05);	// how much of pop to replace each gen
	params.set(gaNscoreFrequency, 10);	// how often to record scores
	params.set(gaNnReplacement, 10);		// how much of pop to replace each gen
	params.set(gaNflushFrequency, 10);	// how often to dump scores to file
	params.set(gaNscoreFilename, "bog.dat");

	GAListGenome<int> genome(objective);
	genome.initializer(ListInitializer);
	genome.mutator(GAListGenome<int>::SwapMutator);

	GASteadyStateGA ga(genome);
	ga.crossover(GAListGenome<int>::PartialMatchCrossover);
	ga.parameters(params);
	ga.evolve();

	genome = ga.statistics().bestIndividual();

	//std::cout << "the ga generated the following list (objective score is ";
	//std::cout << genome.score() << "):\n" << genome << "\n";
	std::cout << genome ;
	std::cout << ga.statistics();

	return 0;
}
