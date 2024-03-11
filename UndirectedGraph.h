#pragma once
#include "List.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
template <typename T>
class UndirectedGraph
{
private:
	List<T> vertices;
	List<List<T>> adjacencyList;
public:
	UndirectedGraph(string);
	int getTotalvertices();
	int getEdges();
	List<T>& BFS(T);
	void WCC(int);
	int LargestWCC();
};

template<typename T>
inline UndirectedGraph<T>::UndirectedGraph(string path)
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
		if (!vertices.find(vertex1))
		{
			vertices.insert(vertex1);
			List<T> temp;
			adjacencyList.insert(temp);
			if (!flag)
				continue;
			adjacencyList.get(vertices.getIndex(vertex1)).insert(vertex2);
		}
		else
		{
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
			adjacencyList.insert(temp);
			adjacencyList.get(vertices.getIndex(vertex2)).insert(vertex1);
		}
		else
		{
			adjacencyList.get(vertices.getIndex(vertex2)).insert(vertex1);
		}
	}
}

template<typename T>
inline int UndirectedGraph<T>::getTotalvertices()
{
	return  vertices.getSize();
}

template<typename T>
inline int UndirectedGraph<T>::getEdges()
{
	int edges = 0;
	for (int i = 0; i < adjacencyList.getSize(); i++)
	{
		edges += adjacencyList.get(i).getSize();
	}
	edges = edges / 2;
	return edges;
}

template<typename T>
inline List<T>& UndirectedGraph<T>::BFS(T source)
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
				arr[discovered] = adjacencyList.get(vertices.getIndex(current)).get(i);
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
inline void UndirectedGraph<T>::WCC(int endNumber)
{
	int* count = new int[endNumber];
	for (int i = 0; i < endNumber; i++)
	{
		count[i] = 0;
	}
	List<List<T>> answer;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		List<T> final = BFS(vertices.get(i));;
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
inline int UndirectedGraph<T>::LargestWCC()
{
	List<List<T>> answer;
	for (int i = 0; i < getTotalvertices(); i++)
	{
		List<T> final = BFS(vertices.get(i));
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
