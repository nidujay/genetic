#ifndef FITNESS_H
#define FITNESS_H

#include <vector>

bool is_all_students_allocated(const std::vector<int> &students);
int valid_class_size_count(const std::vector<int> &students, int min_size, int max_size);
int satisfied_peer_pref_count(const std::vector<int> &students);

#endif
