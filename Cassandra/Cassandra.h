#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	Node Class structure of each node in CEPH DHT.
*/
class Node{
    private:
        int NodeId; // Unique identifier for the node.
		int hashValue; // Weight assigned to each node.
		vector<unordered_set<int>> data; // Data held by the node in the form of <HashValue, ReplicaNo>.
		Node* next; // Pointer pointing to the next node in the distributed system.
		
    public:
		/* Constructor for Node Class. */
        Node(int NodeID, int hashValue, int r)
		{
			this->NodeId = NodeID;
			this->hashValue = hashValue;
			for(int i=0;i<r;i++)
				data.push_back({});

			this->next = NULL;
		}
        ~Node();

		void enterOriginalData(int total)
		{
			int curHashValue = this->hashValue;
			int nextHashValue = (this->next)->hashValue;
			unordered_set<int> nodeData;
			while(curHashValue%total != nextHashValue)
			{
				nodeData.insert(curHashValue);
				curHashValue++;
			}
			data[0] = nodeData;
		}
		
		/* Function to insert the data(hash value and replica no in our case)*/
        void insertData(int r, int m)
		{
			Node* cur = this;
			int curHashValue = this->hashValue;
			int nextHashValue = (this->next)->hashValue;
			int total = pow(2, m);
			if(data[0].size() == 0)
			{
				enterOriginalData(total);
			}
			int i=0;
			while(i<r)
			{
				cur->SetData(data[0], i);
				cur = cur->next;
				i++;
			}
			return;
		}
		

		void SetData(unordered_set<int> data, int idx)
		{
			this->data[idx] = data;
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
			{
				this->next = NULL;
				return;
			}
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

		void setHashValue(int load)
		{
			this->hashValue+=load;
		}
		
		vector<unordered_set<int>> getData()
		{
			return this->data;
		}
		
};





