#include <iostream>
#include <string>
#include <cmath>
#include<iostream>
#include<math.h>
#include<vector>
#include<unordered_map>

using namespace std;


/*
	Node Class structure of each node in CEPH DHT.
	
*/
class Node{
    private:
        int NodeId; // Unique identifier for the node.
		int hashValue; // Weight assigned to each node.
		unordered_map<int,int> data; // Data held by the node in the form of <HashValue, ReplicaNo>.
		Node* next; // Pointer pointing to the next node in the distributed system.
		
    public:
		/* Constructor for Node Class. */
        Node(int NodeID, int weight)
		{
			this->NodeId = NodeID;
			this->next = NULL;
		}
        ~Node();
		
		/* Function to insert the data(hash value and replica no in our case)*/
        void insertData()
		{
			int curHashValue = this->hashValue;
			int nextHashValue = (this->next)->hashValue;
			for(int i=curHashValue; i<nextHashValue; i++)
			{
				this->data[hashValue] = 0;
			}
			return;
		}

		void insertReplicas(int r)
		{
			Node* cur = this->next;
			unordered_map<int> tempData;
			for(auto it = this->data.begin(); it != this->data.end(); it++)
			{
				if(it->second == 0)
				{
					tempData[it->first]=it->second+1;
				}
			}
			
		}

		void SetData(unordered_map<int, int> data)
		{
			this->data = data;
		}
		
		/*Get the pointer to next Node*/
		Node* getNext()
		{
			return this->next;
		}
		
		/*Set the next pointer of current node to point to next node. */
		void setNext(Node** node)
		{
			if(node == NULL)
				return;
			this->next = *node;
		}
		
		/*Return Node ID*/
		int getNodeID()
		{
			return this->NodeId;
		}
		
		unordered_map<int, int> getData()
		{
			return this->data;
		}
		
};





