#include "Graph.h"
#include "UndirectedGraph.h"
#include <iostream>
using namespace std;


int main()
{
	cout << "Please enter file path: ";
	string path;
	cin >> path;
	int choice;
	Graph<int> g(path);
	UndirectedGraph<int> g2(path);
	while (true)
	{
		cout << "Press 1 to get Total Vertices in the graph" << endl;
		cout << "Press 2 to get Total Edges in the graph" << endl;
		cout << "Press 3 to get Total Isolated Nodes in the graph" << endl;
		cout << "Press 4 to get Total Source Nodes in the graph" << endl;
		cout << "Press 5 to get Total Sink Nodes in the graph" << endl;
		cout << "Press 6 to get Total Bridge Edges in the graph" << endl;
		cout << "Press 7 to get Total Articulation Vertices in the graph" << endl;
		cout << "Press 8 to display shortest Path distribution in the graph" << endl;
		cout << "Press 9 to display the diameter of the graph" << endl;
		cout << "Press 10 to display the In degree distribution of the graph" << endl;
		cout << "Press 11 to display the Out degree distribution of the graph" << endl;
		cout << "Press 12 to display the Size of Largest SCC of the graph" << endl;
		cout << "Press 13 to display the Size distribution of SCC's of the graph" << endl;
		cout << "Press 14 to display the Size of Largest WCC of the graph" << endl;
		cout << "Press 15 to display the Size distribution of WCC's of the graph" << endl;
		cout << "Press 16 to exit the program" << endl;
		cin >> choice;
		cout << endl << endl << endl;
		if (choice == 1)
		{
			cout << "Total Vertices = " <<  g.getTotalvertices() << endl;
		}
		else if (choice == 2)
		{
			cout << "Total Edges = " << g.getEdges() << endl;
		}
		else if (choice == 3)
		{
			cout << "Total Isolated Vertices = " << g.getIsolatedNodes() << endl;
		}
		else if (choice == 4)
		{
			cout << "Total Source Nodes = " << g.getSourceNodes() << endl;
		}
		else if (choice == 5)
		{
			cout << "Total Sink Nodes = " << g.getSinkNodes() << endl;
		}
		else if (choice == 6)
		{
			cout << "Total Bridge Edges = " << g.getBridgeEdges() << endl;
		}
		else if (choice == 7)
		{
			cout << "Total Articulation Nodes = " << g.getArticulationNodes() << endl;
		}
		else if (choice == 8)
		{
			cout << "Please enter the maximum length till which you want to display the Distribution : ";
			int maxLength;
			cin >> maxLength;
			cout << endl << endl;
			cout << "                  Shortest Path distribution  " << endl;
			g.shortestPathDistribution(maxLength);
		}
		else if (choice == 9)
		{
			cout << "Diamater = " << g.Diameter() << endl;
		}
		else if (choice == 10)
		{
			cout << "Please enter the minimum Distribution till which you want to display : ";
			double min;
			cin >> min;
			cout << "Please enter the maximum Distribution till which you want to display : ";
			double max;
			cin >> max;
			cout << "                  In Degree distribution  " << endl;
			g.InDistribution(min, max);
		}
		else if (choice == 11)
		{
			cout << "Please enter the minimum Distribution till which you want to display : ";
			double min;
			cin >> min;
			cout << "Please enter the maximum Distribution till which you want to display : ";
			double max;
			cin >> max;
			cout << "                  Out Degree distribution  " << endl;
			g.OutDistribution(min, max);
		}
		else if (choice == 12)
		{
			cout << "Largest Strongly Connected Component Size : " << g.LargestSCC() << endl;
		}
		else if (choice == 13)
		{
			cout << "Please enter the maximum size till which you want to display the Distribution : ";
			int maxSize;
			cin >> maxSize;
			g.SCC(maxSize);
		}
		else if (choice == 14)
		{
			cout << "Largest Weakly Connected Component Size : " << g2.LargestWCC() << endl;
		}
		else if (choice == 15)
		{
			cout << "Please enter the maximum size till which you want to display the Distribution : ";
			int maxSize;
			cin >> maxSize;
			g2.WCC(maxSize);
		}
		else if (choice == 16)
		{
			cout << "Exiting the Program" << endl;
			break;
		}
		cout << endl << endl << endl;
	}
}