#ifndef _FINDMESH_H_
#define _FINDMESH_H_

#include <iostream>
#include <vector>
#include "adjmatrix.h"

using namespace std;
void spanTree(int n, AdjacencyMatrix& A, AdjacencyMatrix& B, vector<int>& C);
    // A is the original adjacency matrix
    // B is the adjacency matrix of the spanning tree
    // C is a vector of size n and is the list of vertices already included in the spanning tree


void prune(int n, AdjacencyMatrix* D);


void getMesh(int n, AdjacencyMatrix& A, AdjacencyMatrix& B, vector<AdjacencyMatrix>& mesh);
    // m is the number of fundamental cycles
    // A, B, C, D are matrices of size n×n (and 0 ≤ k ≤ m−1);

    // A is the original adjacency matrix
    // B is the adjacency matrix of the spanning tree
    // D is the adjacency matrix of the spanning tree , augmented with the addition of the k−th discarded link
    // mesh contains a collection of fundamental cycles, a.k.a. loop currents, represented as matrices

#endif
