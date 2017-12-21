/*
Djikstra in C++
Read from a file and reallocate the memory to vectors.
*/

#include <vector>
#include <iostream>
#include <cstdio>

int main(int argv, char **argc) {

  FILE *graph_file;
  int node1;
  int node2;
  int weight;
  std::vector<int> i1_;
  std::vector<int> i2_;
  std::vector<int> w_vec_;

  graph_file = fopen("example.txt", "r");

  while (fscanf(graph_file, "%d %d %d", &node1, &node2, &weight) != EOF)
  {
    i1_.push_back(node1);
    i2_.push_back(node2);
    w_vec_.push_back(weight);
  }
  fclose(graph_file);

  for (std::vector<int>::const_iterator i = i1_.begin(); i != i1_.end(); ++i)
  {
    std::cout << *i << "\n";
  }
  std::vector<int>::clear();

  return 0;
}
