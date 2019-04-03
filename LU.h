#ifndef _LU_H_
#define _LU_H_

#include "adjmatrix.h"
#include "findmesh.h"
#include "elematrix.h"

using namespace std;

vector<AdjacencyMatrix> prepareLU(int n, vector<AdjacencyMatrix>& mesh, ElementMatrix& R, ElementMatrix& V);

#endif