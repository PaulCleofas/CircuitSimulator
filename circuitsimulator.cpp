#include "elematrix.h"
#include "findmesh.h"
#include "LU.h"
#include "results.h"
using namespace std;

int main()
{
    int nodes, max_edges, origin, destin;
    int resistance, voltage;
    cout << "Enter number of nodes: ";
    cin >> nodes;
    ElementMatrix A(nodes); // matrix for adjacency
    ElementMatrix R(nodes); // matrix for resistance
    ElementMatrix V(nodes); // matrix for voltages

    max_edges = nodes * (nodes - 1);
    for(int i = 0; i < max_edges; i++)
    {
        cout << "Enter branch (-1 -1 to exit): ";
        cin >> origin >> destin;
        if((origin == -1) && (destin == -1))
            break;
        A.addComponent(origin, destin, 1);
        A.addComponent(destin, origin, 1);

        //For resistance
        cout << "   Enter resistance in branch(" << origin << "," << destin << "): ";
        cin >> resistance;
        R.addComponent(origin, destin, resistance);
        R.addComponent(destin, origin, resistance);

        //For voltage
        cout << "   Enter voltage in branch("<< origin << "," << destin << "): ";
        cin >> voltage;
        V.addComponent(origin, destin, voltage);
        V.addComponent(destin, origin, -(voltage)); // voltage orientation is NOT arbitrary
    }

    cout << "Adjacency Matrix" << endl;
    A.display();
    cout << "Resistance Matrix" << endl;
    R.display();
    cout << "Voltage Matrix" << endl;
    V.display();

    ElementMatrix B(nodes);  // adjacency matrix for spanning tree
    vector<int> C;  // list of vertices to be included in the spanning tree

    spanTree(nodes, A, B, C);
    cout << "Spanning Tree" << endl;
    B.display();

    vector<ElementMatrix> mesh;  // array of current loops to be found
    getMesh(nodes, A, B, mesh);
    setOrientation(nodes, mesh);

    // Displays all current loops
    int display_counter = 1;
    for(auto iter = mesh.begin(); iter != mesh.end(); iter++) {
        switch(display_counter) {
            case 1:
                cout << display_counter << "st mesh" << endl;
                display_counter++;
                break;
            case 2:
                cout << display_counter << "nd mesh" << endl;
                display_counter++;
                break;
            case 3:
                cout << display_counter << "rd mesh" << endl;
                display_counter++;
                break;
            default:
                cout << display_counter << "th mesh" << endl;
                display_counter++;
                break;
        }

        (*iter).display();
        cout << endl;
    }

    // LHS is the coefficient matrix A in equation AX = B
    auto LHS = computeLHS(nodes, mesh, R, V);
    cout << "LHS Matrix" << endl;
    LHS.display();
    cout << endl;

    // RHS is the matrix B in AX = B
    auto RHS = computeRHS(nodes, mesh, V);
    cout << "RHS Matrix" << endl;
    for (auto iter = RHS.begin(); iter != RHS.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl << endl;

    // Decompose LHS
    ElementMatrix L(mesh.size());
    ElementMatrix U(mesh.size());

    decompose(mesh.size(), LHS, L, U);

    cout << "L Matrix" << endl;
    L.display();
    cout << endl;
    cout << "U Matrix" << endl;
    U.display();
    cout << endl;


    vector<float> X = solveEquation(mesh.size(), L, U, RHS);
    cout << "Mesh currents:" << endl;
    for (auto iter = X.begin(); iter != X.end(); iter++){
        cout<< *iter << endl;
    }
    cout << endl;

    ElementMatrix I(nodes);
    I = getCurrent(nodes, X, mesh, I);
    I.display();

    
    
    return 0;
}