#ifndef _LU_H_
#define _LU_H_

#include "findmesh.h"
#include "elematrix.h"

using namespace std;


ElementMatrix computeLHS(int n, vector<ElementMatrix>& mesh, ElementMatrix& R, ElementMatrix& V);
/* 
Input(s):
    mesh is a collection of ORIENTED, independent loops
    R is the nxn resistance matrix
    V is the nxn voltage matrix

Return(s): matrix A in the equation AI = B. I is the matrix containing mesh currents.
*/

vector<int> computeRHS(int n, vector<ElementMatrix>& mesh, ElementMatrix& V);
/* 
Input(s):
    mesh is a collection of ORIENTED, independent loops
    V is the nxn voltage matrix

Return(s): one-dimensional matrix B in the equation AI = B. I is the matrix containing mesh currents.
*/

void decompose(int m, ElementMatrix& A, ElementMatrix& L, ElementMatrix& U);
/*
This function will decompose A such that A = LU

Input(s):
    A is the mxm matrix A to be decomposed
    L is the matrix where lower half of the decomposition will be stored
    U is the matrix where upper half of the decomposition will be stored

Return(s): none
*/

vector<float> solveEquation(int m, ElementMatrix& L, ElementMatrix& U, vector<int>& B);
/*
This function solves for X in the equation LUX = B.

Input(s):
    L is the mxm lower triangle of the decomposed matrix A
    U is the mxm upper triangle of the decomposed matrix A

Return(s):
    The one-dimensional matrix X.
*/

#endif