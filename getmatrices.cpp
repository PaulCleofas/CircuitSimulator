#include "adjmatrix.h"
#include "elematrix.h"
using namespace std;
// void getResistance()
    

/*
 * Main
 */ 
int main()
{
    int nodes, max_edges, origin, destin;
    float resistance, voltage;
    cout<<"Enter number of nodes: ";
    cin>>nodes;
    AdjacencyMatrix A(nodes); // matrix for adjacency
    ElementMatrix R(nodes); // matrix for resistance
    ElementMatrix V(nodes); // matrix for voltages

    max_edges = nodes * (nodes - 1);
    for (int i = 0; i < max_edges; i++)
    {
        cout<<"Enter branch (-1 -1 to exit): ";
        cin>>origin>>destin;
        if((origin == -1) && (destin == -1))
            break;
        A.addEdge(origin, destin);

        //For resistance
        cout<< "   Enter resistance in branch("<< origin << "," << destin << "): ";
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
        
    return 0;
}