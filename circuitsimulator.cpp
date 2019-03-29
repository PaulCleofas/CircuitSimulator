#include "adjmatrix.h"
#include "elematrix.h"
#include "findmesh.h"
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
    vector<AdjacencyMatrix> mesh;  // array of current loops to be found
    // int mesh_count = 0;

    spanTree(nodes, A, B, C);
    getMesh(nodes, A, B, mesh);

    // Displays all current loops
    for(auto iter = mesh.begin(); iter != mesh.end(); iter++) {
        int i = 1;
        switch(i) {
            case 1:
                cout << i << "st mesh" << endl;
                break;

            case 2:
                cout << i << "nd mesh" << endl;
                break;

            case 3:
                cout << i << "rd mesh" << endl;

            default:
                cout << i << "th mesh" << endl;
        }

        for(int j = 0; j < nodes; j++) {
            for(int k = 0; k < nodes; k++) {
                cout << (*iter).accessMatrix(j, k)<<"  ";
            }

            cout << endl;
        }

        i++;
    }

        
    return 0;
}