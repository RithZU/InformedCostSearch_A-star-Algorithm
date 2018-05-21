/*
Name : Sokhavirith SORN
Task : Hand-on Informed Search Algorithm

*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

class Node {
private:
	int nodeId;
	int nodeWeight;
	int h;
	int f;
public:
	Node(int nodeId, int nodeWeight,int estimatedValue) {
		this->nodeId = nodeId;
		this->nodeWeight = nodeWeight;
		this->h = estimatedValue;
	}
	int getId() {
		return nodeId;
	}
	int getWeight() {
		return nodeWeight;
	}
	int getEstimatedValue()
	{
		return h;
	}
	

};

class Edge {
private:
	int NodeId;
	int Weight;
public:
	Edge(int NodeId, int NodeWeight) {
		this->NodeId = NodeId;
		this->Weight = NodeWeight;
	}
	int getNodeId()
	{
		return NodeId;
	}
	int getNodeWeight()
	{
		return Weight;
	}


};

int indexOf(std::vector<Node*> vec, int val) {

	bool found = false;
	int index = 0;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->getId() != val)
			index++;
		else {
			found = true;
			break;
		}
	}
	if (found)
		return index;
	else
		return -1;
}


class Graph {
private:
	int RootNode = 0;
	Node* n;
	int goal = 4;
public:
	std::vector<Node*> adj[12];
	void addEdge(int u, int v, int weight,int estimatedValue)
	{
		adj[u].push_back(new Node(v, weight,estimatedValue));

	}
	void printGraph()
	{
		std::cout << "Adjacency List Graph's Representation : " << std::endl;
		for (unsigned int i = 0; i < 12; i++)
		{
			std::cout << i;
			for (unsigned int j = 0; j < adj[i].size(); j++)
			{
				std::cout << " ---> " << adj[i][j]->getId() << "," << adj[i][j]->getWeight()<<","<<adj[i][j]->getEstimatedValue();
			}
			std::cout << std::endl;
		}
	}
	bool InformedCostSearch()
	{
		std::vector<Node*> OPEN;
		std::vector<Node*> CLOSED;
		//1. Set OPEN = { s }, CLOSED = {}, c(s) = 0, f(s) = h(s)


		OPEN.push_back(new Node(RootNode, 0,12));

		std::cout << "OPEN : " << std::endl;
		//2. Fail: if OPEN = {}, Terminate with failure
		while (!OPEN.empty())
		{
			//3. Select the minimum cost of f state, n, from OPEN and save n in CLOSED
			Node* minCost = NULL;
			
			for (unsigned int i = 0; i < OPEN.size(); i++)
			{
				std::cout<< OPEN[i]->getId() << "\t";

				minCost = OPEN[0];
				if (OPEN[i]->getEstimatedValue() < minCost->getEstimatedValue())
					minCost = OPEN[i];
			}
			std::cout << std::endl;

			n = minCost;

			OPEN.erase(OPEN.begin() + indexOf(OPEN, n->getId()));

			CLOSED.push_back(n);


			//4. if n ϵ G, terminate with success, return f(n)
			if (n->getId() == goal) {
				std::cout << "CLOSED : " << std::endl;
				for (unsigned int i = 0; i < CLOSED.size(); i++) {
					std::cout << CLOSED[i]->getId() << " ";
				}
				std::cout << std::endl;
				return true;
			}
				
			//5. Expand: Generate the successors of n using O. For each successor, m 

			for (unsigned int i = 0; i < adj[n->getId()].size(); i++)
			{
				Node* m = adj[n->getId()][i];

				int c_of_n = n->getWeight();
				int c_of_nm = m->getWeight();
				int c_of_m = c_of_n + c_of_nm;
				int f = c_of_m + m->getEstimatedValue();


				//if m not in OPEN or CLOSED
				if (((indexOf(OPEN, m->getId())) == -1) && ((indexOf(CLOSED, m->getId())) == -1))
				{
					//Set C(m) = C(n) + C(n, m) and insert m in OPEN
					OPEN.push_back(new Node(m->getId(), c_of_m, f));
				}
				//if m ϵ[OPEN ⋃ CLOSED]
				else {
					
					//Set C(m) = min{ C(m), C(n) + C(n, m) }
					int index_m_open = indexOf(OPEN, m->getId());
					int index_m_closed = indexOf(CLOSED, m->getId());
					int old_c_of_m;
					int old_f;
					//if m in open
					if (index_m_open !=-1)
					{
						old_c_of_m = OPEN[index_m_open]->getWeight();
						old_f = OPEN[index_m_open]->getEstimatedValue();
					}
					//if m in closed
					else {
						old_c_of_m = CLOSED[index_m_closed]->getWeight();
						old_f = CLOSED[index_m_closed]->getEstimatedValue();
					}
			
					int new_f = c_of_m + m->getEstimatedValue();


					//if C(m) has decreased and m є CLOSED, move it to OPEN
					if (new_f < old_f)
					{
						OPEN.push_back(new Node(m->getId(), c_of_m, new_f));
					}

				}

			}
		}


		return false;
	}
	int getGoal()
	{
		return goal;
	}

};




int main()
{

	Graph* myGraph = new Graph();


	myGraph->addEdge(0, 1, 2,10);
	myGraph->addEdge(0, 4, 1,12);
	myGraph->addEdge(1, 2, 1,16);
	myGraph->addEdge(1, 5, 3,7);
	myGraph->addEdge(2, 3, 1,15);
	myGraph->addEdge(3, 7, 1,15);
	myGraph->addEdge(4, 8, 1,12);
	myGraph->addEdge(5, 4, 5,12);
	myGraph->addEdge(5, 6, 1,11);
	myGraph->addEdge(5, 9, 4,4);
	myGraph->addEdge(6, 2, 3,16);
	myGraph->addEdge(6, 10, 10,1);
	myGraph->addEdge(7, 6, 5,11);
	myGraph->addEdge(7, 11, 15,0);
	myGraph->addEdge(8, 9, 8,4);
	myGraph->addEdge(9, 10, 3,1);
	myGraph->addEdge(10, 11, 1,0);
	myGraph->printGraph();
	std::cout << "Goal = " << myGraph->getGoal() << std::endl << std::endl;

	myGraph->InformedCostSearch() ? std::cout << "Goal Found" : std::cout << "Not Found";



	getchar();

	return 0;




}