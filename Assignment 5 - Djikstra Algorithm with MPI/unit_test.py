import numpy as np

def find_min_vec(vector):

  min_dist = 1000000
  for i in range(len(vector)):
    if vector[i] != 0 and vector[i] <= min_dist:
      min_dist = vector[i]
      locat = i
  return min_dist, i

arb_graph = [[0, 4, 0, 0, 0, 0, 0, 8, 0],
           [4, 0, 8, 0, 0, 0, 0, 11, 0],
           [0, 8, 0, 7, 0, 4, 0, 0, 2],
           [0, 0, 7, 0, 9, 14, 0, 0, 0],
           [0, 0, 0, 9, 0, 10, 0, 0, 0],
           [0, 0, 4, 14, 10, 0, 2, 0, 0],
           [0, 0, 0, 0, 0, 2, 0, 1, 6],
           [8, 11, 0, 0, 0, 0, 1, 0, 7],
           [0, 0, 2, 0, 0, 0, 6, 7, 0]]

arb_graph = np.asarray(arb_graph)

def djikstra(graph):

  for i in range(graph.shape[0]):
   min_vec, locat = find_min_vec(graph[i, i:])
   print graph[i, i:]
   print min_vec

djikstra(arb_graph)
