#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>

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
        Node(int NodeID, int hashValue)
		{
			this->NodeId = NodeID;
			this->hashValue = hashValue;
			this->next = NULL;
		}
        ~Node();
		
		/* Function to insert the data(hash value and replica no in our case)*/
        void insertData(int r, int m)
		{
			Node* cur = this;
			int curHashValue = this->hashValue;
			int nextHashValue = (this->next)->hashValue;
			int i = 0;
			int total = int(pow(2,m));
			while(i<r)
			{
				while(curHashValue%total != nextHashValue)
				{
					cur->data[curHashValue] = i;
					curHashValue++;
				}
				curHashValue = this->hashValue;
				cur = cur->next;
				i++;
			}
			return;
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

		int getHashValue()
		{
			return this->hashValue;
		}
		
		unordered_map<int, int> getData()
		{
			return this->data;
		}
		
};





