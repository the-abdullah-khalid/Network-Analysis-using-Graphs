#pragma once
#include "List.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int convertToInt(string value)
{
	int returner = 0;
	for (int i = 0; i < value.length(); i++)
	{
		returner = (returner * 10) + (value[i] - 48);
	}
	return returner;
}
template <typename T>
class Graph
{
private:
	List<T> vertices;
	List<List<T>> adjacencyList;
public:
	Graph(string);
	int getTotalvertices();
	int getEdges();
	int getIsolatedNodes();
	int getSourceNodes();
	int getSinkNodes();
	int getBridgeEdges();
	int getArticulationNodes();
	bool reachable(T, T);
	bool reachable(T);
	int* shortestPath(T);
	void shortestPathDistribution(int);
	int Diameter();
	void InDistribution(double, double);
	void OutDistribution(double, double);
	List<T>& BFS(T);
	List<T>& IN(T);
	void SCC(int);
	int LargestSCC();
};


template<typename T>
inline Graph<T>::Graph(string path)
{
	ifstream ifile;
	ifile.open(path);
	string readed;
	int vertex1 = 0; 
	int vertex2 = 0;
	while (!ifile.eof())
	{
		getline(ifile, readed);
		string current = "";
		string current2 = "";
		bool flag = false;
		for (int i = 0; i < readed.length(); i++)
		{
			if (readed[i] == '\t')
			{
				flag = true;
				continue;
			}
			if (!flag)
			{
				current = current + readed[i];
			}
			else
			{
				current2 = current2 + readed[i];
			}
		}
		vertex1 = convertToInt(current);
		vertex2 = convertToInt(current2);
		//cout << current << endl;
		if (!vertices.find(vertex1))
		{
			//	cout << "Hi" << endl;
			vertices.insert(vertex1);
			List<T> temp;
			adjacencyList.insert(temp);
			if (!flag)
				continue;
			adjacencyList.get(vertices.getIndex(vertex1)).insert(vertex2);
		}
		else
		{
			//cout << vertices.getIndex(current) << endl;
			if (!flag)
				continue;
			adjacencyList.get(vertices.getIndex(vertex1)).insert(vertex2);
		}
		if (!flag)
			continue;
		if (!vertices.find(vertex2))
		{
			vertices.insert(vertex2);
			List<T> temp;
			//temp.insert(current);
			adjacencyList.insert(temp);
		}
		else
		{
			//adjacencyList.get(vertices.getIndex(current2)).insert(current);
		}
		//cout << "Hello" << endl;
	}
}

template<typename T>
inline int Graph<T>::getTotalvertices()
{
	return vertices.getSize();
}

template<typename T>
inline int Graph<T>::getEdges()
{
	int edges = 0;
	for (int i = 0; i < adjacencyList.getSize(); i++)
	{
		edges += adjacencyList.get(i).getSize();
	}
	//edges = edges / 2;
	return edges;
}

template<typename T>
inline int Graph<T>::getIsolatedNodes()
{
	int count = 0;
	for (int i = 0; i < adjacencyList.getSize(); i++)
	{
		if (adjacencyList.get(i).getSize() == 0)
		{
			T currentvertex = vertices.get(i);
			bool found = false;
			Node<List<T>>* head = adjacencyList.Gethead();
			for (int j = 0; j < adjacencyList.getSize(); j++)
			{
				if (head->value.find(currentvertex))
				{
					found = true;
					break;
				}
				head = head->Next;
			}
			if (!found)
				count++;
		}
	}
	return count;
}

template<typename T>
inline int Graph<T>::getSourceNodes()
{
	int count = 0;
	for (int i = 0; i < vertices.getSize(); i++)
	{
		T currentvertex = vertices.get(i);
		bool found = false;
		Node<List<T>>* head = adjacencyList.Gethead();
		for (int j = 0; j < adjacencyList.getSize(); j++)
		{
			if (head->value.find(currentvertex))
			{
				found = true;
				break;
			}
			head = head->Next;
		}
		if (!found)
			count++;
	}
	return count;
}

template<typename T>
inline int Graph<T>::getSinkNodes()
{
	int count = 0;
	for (int i = 0; i < adjacencyList.getSize(); i++)
	{
		if (adjacencyList.get(i).getSize() == 0)
			count++;
	}
	return count;
}

template<typename T>
inline int Graph<T>::getBridgeEdges()
{
	int count = 0;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		for (int j = 0; j < adjacencyList.get(vertices.getIndex(vertices.get(i))).getSize(); j++)
		{
			if (!reachable(vertices.get(i), adjacencyList.get(vertices.getIndex(vertices.get(i))).get(j)))
			{
				count++;
			}
		}
	}
	return count;
}

template<typename T>
inline int Graph<T>::getArticulationNodes()
{
	int count = 0;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		if (!reachable(vertices.get(i)))
		{	
			count++;
		}
	}
	return count;
}

template<typename T>
inline bool Graph<T>::reachable(T node1, T node2)
{
	T* arr = new T[getTotalvertices()];
	int discovered = 0;
	int finished = 0;
	arr[discovered] = vertices.get(0);
	discovered++;
	T current;
	while(discovered!= finished)
	{
		current = arr[finished];
		finished++;
		for(int i = 0; i < adjacencyList.get(vertices.getIndex(current)).getSize(); i++)
		{
			if (current == node1 && adjacencyList.get(vertices.getIndex(current)).get(i) == node2)
				continue;
			bool found = false;
			for (int j = 0; j < discovered; j++)
			{
				if (adjacencyList.get(vertices.getIndex(current)).get(i) == arr[j])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				arr[discovered] = adjacencyList.get(vertices.getIndex(current)).get(i);
				discovered++;
			}
		}
	}
	if (discovered < getTotalvertices() - getIsolatedNodes())
	{
		return false;
	}
	else
		return true;
}

template<typename T>
inline bool Graph<T>::reachable(T node)
{
	T* arr = new T[getTotalvertices()];
	int discovered = 0;
	int finished = 0;
	if(vertices.get(0) != node)
		arr[discovered] = vertices.get(0);
	else
		arr[discovered] = vertices.get(1);
	
	discovered++;
	T current;
	while (discovered != finished)
	{
		current = arr[finished];
		finished++;
		for (int i = 0; i < adjacencyList.get(vertices.getIndex(current)).getSize(); i++)
		{
			bool found = false;
			for (int j = 0; j < discovered; j++)
			{
				if (adjacencyList.get(vertices.getIndex(current)).get(i) == arr[j])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				if (adjacencyList.get(vertices.getIndex(current)).get(i) == node)
					continue;
				arr[discovered] = adjacencyList.get(vertices.getIndex(current)).get(i);
				discovered++;
			}
		}
	}
	if (discovered < getTotalvertices() - 1 - getIsolatedNodes())
	{
		return false;
	}
	else
		return true;
}

template<typename T>
inline int* Graph<T>::shortestPath(T source)
{
	T* arr = new T[getTotalvertices()];
	int* lengths = new int[getTotalvertices()];
	for (int i = 0; i < getTotalvertices(); i++)
	{
		lengths[i] = -1;
	}

	int discovered = 0;
	int finished = 0;
	arr[discovered] = source;
	lengths[discovered] = 0;
	discovered++;
	T current;
	while (discovered != finished)
	{
		current = arr[finished];
		finished++;
		int Index = vertices.getIndex(current);
		List<T> l = adjacencyList.get(Index);
		int size = l.getSize();
		for (int i = 0; i < size; i++)
		{
			bool found = false;
			T value = l.get(i);
			for (int j = 0; j < discovered; j++)
			{
				if (value == arr[j])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				arr[discovered] = value;
				lengths[discovered] = lengths[finished - 1] + 1;
				discovered++;
			}
		}
	}
	return lengths;
}

template<typename T>
inline void Graph<T>::shortestPathDistribution(int endNumber)
{
	int* lengths;
	int* count = new int[endNumber];
	for (int i = 0; i < endNumber; i++)
	{
		count[i] = 0;
	}
	for (int j = 0; j < getTotalvertices(); j++)
	{
		T source = vertices.get(j);
		lengths = shortestPath(source);
		for (int i = 0; i < endNumber; i++)
		{
			for (int k = 0; k < getTotalvertices(); k++)
			{
				if (lengths[k] == i + 1)
					count[i] = count[i] + 1;
			}
		}
	}
	cout << "___________________________________________" << endl;
	cout << "|     Length      |     Number of  Paths   |" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < endNumber; i++)
	{
		cout << "|    ";
		cout << setw(5) << i + 1;
		cout << setw(12) << "   |   ";
		cout << setw(5) << count[i];
		cout << setw(17) << "     |" << endl;
	}
	cout << "--------------------------------------------" << endl;
}

template<typename T>
inline int Graph<T>::Diameter()
{
	int* lengths;
	int diameter = 0;
	for (int j = 0; j < getTotalvertices(); j++)
	{
		T source = vertices.get(j);
		lengths = shortestPath(source);
		for (int k = 0; k < getTotalvertices(); k++)
		{
			if (diameter < lengths[k])
			{
				diameter = lengths[k];
			}
		}
	}
	return diameter;
}

template<typename T>
inline void Graph<T>::InDistribution(double min, double max)
{
	cout << "___________________________________________" << endl;
	cout << "|     Vertex      |    Distribution        |" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		Node<List<T>>* Head = adjacencyList.Gethead();
		T value = vertices.get(i);
		int count = 0;
		for (int j = 0; j < getTotalvertices(); j++)
		{
			if ((Head->value).find(value))
				count++;
			Head = Head->Next;
		}
		double distribution = double(count) / double(getTotalvertices());
		if (!(distribution >= min && distribution <= max))
			continue;
		cout << "|    ";
		cout << setw(5) << vertices.get(i);
		cout << setw(12) << "   |   ";
		cout << setw(15) << distribution;
		cout << setw(7) << "     |" << endl;
	}
	cout << "--------------------------------------------" << endl;
}

template<typename T>
inline void Graph<T>::OutDistribution(double min, double max)
{
	cout << "___________________________________________" << endl;
	cout << "|     Vertex      |    Distribution        |" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		double distribution = double(adjacencyList.get(i).getSize()) / double(getTotalvertices());
		if (!(distribution >= min && distribution <= max))
			continue;
		cout << "|    ";
		cout << setw(5) << vertices.get(i);
		cout << setw(12) << "   |   ";
		cout << setw(15) << distribution;
		cout << setw(7) << "     |" << endl;
	}
	cout << "--------------------------------------------" << endl;

}


template<typename T>
inline List<T>& Graph<T>::BFS(T source)
{
	T* arr = new T[getTotalvertices()];
	int discovered = 0;
	int finished = 0;
	arr[discovered] = source;

	discovered++;
	T current;
	while (discovered != finished)
	{
		current = arr[finished];
		finished++;
		List<T> list = adjacencyList.get(vertices.getIndex(current));
		for (int i = 0; i < list.getSize(); i++)
		{
			bool found = false;
			for (int j = 0; j < discovered; j++)
			{
				if (list.get(i) == arr[j])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				arr[discovered] = list.get(i);
				discovered++;
			}
		}
	}
	List<T> answer;
	for (int j = 0; j < discovered; j++)
	{
		answer.insert(arr[j]);
	}
	return answer;
}

template<typename T>
inline List<T>& Graph<T>::IN(T current)
{
	List<T> answer;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		T vertex = vertices.get(i);
		List<T> bfsList = BFS(vertex);
		if (bfsList.find(current))
		{
			answer.insert(vertex);
		}
	}
	return answer;
}

template<typename T>
inline void Graph<T>::SCC(int endNumber)
{
	int* count = new int[endNumber];
	for (int i = 0; i < endNumber; i++)
	{
		count[i] = 0;
	}
	List<List<T>> answer;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		T vertex = vertices.get(i);
		List<T> in = IN(vertex);
		List<T> out = BFS(vertex);
		List<T> final;
		for (int j = 0; j < in.getSize(); j++)
		{
			T value = in.get(j);
			if (out.find(value))
				final.insert(value);
		}
		answer.insert(final);
	}
	List<List<T>> finalAnswer;
	finalAnswer.insert(answer.get(0));
	for (int i = 1; i < answer.getSize(); i++)
	{
		bool found = true;
		List<T> l1 = answer.get(i);
		for (int j = 0; j < finalAnswer.getSize(); j++)
		{
			found = true;
			List<T> l2 = finalAnswer.get(j);
			if (l1.getSize() == l2.getSize())
			{
				for (int k = 0; k < l2.getSize(); k++)
				{
					if (!l1.find(l2.get(k)))
					{
						found = false;
						break;
					}

				}
			}
			else
			{
				found = false;
			}
			if (found)
				break;
		}
		if (!found)
		{
			finalAnswer.insert(l1);
		}
	}
	for (int i = 0; i < finalAnswer.getSize(); i++)
	{
		List<T> L = finalAnswer.get(i);
		for (int k = 0; k < endNumber; k++)
		{
			if (L.getSize() == k + 1)
				count[k]++;
		}
	}
	cout << "____________________________________________" << endl;
	cout << "|     Size        |     Number of SCC's    |" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < endNumber; i++)
	{
		cout << "|    ";
		cout << setw(5) << i + 1;
		cout << setw(12) << "   |   ";
		cout << setw(5) << count[i];
		cout << setw(17) << "     |" << endl;
	}
	cout << "--------------------------------------------" << endl;
}

template<typename T>
inline int Graph<T>::LargestSCC()
{
	List<List<T>> answer;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		List<T> in = IN(vertices.get(i));
		List<T> out = BFS(vertices.get(i));
		List<T> final;
		for (int j = 0; j < in.getSize(); j++)
		{
			T value = in.get(j);
			if (out.find(value))
				final.insert(value);
		}
		answer.insert(final);
	}
	List<T> L = answer.get(0);
	int max = L.getSize();
	for (int i = 0; i < answer.getSize(); i++)
	{
		L = answer.get(i);
		if (L.getSize() > max)
			max = L.getSize();
	}
	return max;
}
