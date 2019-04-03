#include "adjmatrix.h"
#include "elematrix.h"
#include "findmesh.h"
#include "LU.h"
using namespace std;

/*
 * Main
 */ 
int main()
{
    int nodes, max_edges, origin, destin;
    float resistance, voltage;
    cout << "Enter number of nodes: ";
    cin >> nodes;
    AdjacencyMatrix A(nodes); // matrix for adjacency
    ElementMatrix R(nodes); // matrix for resistance
    ElementMatrix V(nodes); // matrix for voltages

    max_edges = nodes * (nodes - 1);
    for(int i = 0; i < max_edges; i++)
    {
        cout << "Enter branch (-1 -1 to exit): ";
        cin >> origin >> destin;
        if((origin == -1) && (destin == -1))
            break;
        A.addEdge(origin, destin);

        //For resistance
        cout << "   Enter resistance in branch(" << origin << "," << destin << "): ";
        cin >> resistance;
        R.addComponent(origin, destin, resistance);

        //For voltage
        cout << "   Enter voltage in branch("<< origin << "," << destin << "): ";
        cin >> voltage;
        V.addComponent(origin, destin, voltage);
    }

    cout << "Adjacency Matrix" << endl;
    A.display();
    cout << "Resistance Matrix" << endl;
    R.display();
    cout << "Voltage Matrix" << endl;
    V.display();

    AdjacencyMatrix B(nodes);  // adjacency matrix for spanning tree
    vector<int> C;  // list of vertices to be included in the spanning tree

    spanTree(nodes, A, B, C);
    cout << "Spanning Tree" << endl;
    B.display();

    vector<AdjacencyMatrix> mesh;  // array of current loops to be found
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

    vector<AdjacencyMatrix> LUVector;
    LUVector = prepareLU(nodes, mesh, R, V);

    // Display the LU matrices
    int display_counter_new = 1;
    for(auto iter = LUVector.begin(); iter != LUVector.end(); iter++) {
        switch(display_counter_new) {
            case 1:
                cout << "Matrix A" << endl;
                display_counter_new++;
                break;
            case 2:
                cout << "Matrix B" << endl;
                display_counter_new++;
                break;
            default:
                cout << display_counter << "Too many meshes" << endl;
                display_counter_new++;
                break;
        }

        (*iter).display();
        cout << endl;
    }

    return 0;
}