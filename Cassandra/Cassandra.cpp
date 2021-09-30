#include "Cassandra.h"

/*int insert_data(Node** head,  int NodeCount)
{
	Node *cur_node = *head;
	
	while(NodeCount--)
	{
		
	}
	
	return -1;
}

void setCumulativeWeight(Node* cur, int nodeID, int weight)
{
	if(cur == NULL)
		return;
	
	if(cur->getNodeID() == nodeID)
	{
		cur->setWeight(weight);
		return;
	}
	
	setCumulativeWeight(cur->getNext(), nodeID, weight);
	cur->setCumulativeWeight();
}

void balance_load(Node** head, int nodeID, int weight, int NodeCount)
{
	Node* cur = *head;
	
	setCumulativeWeight(cur, nodeID, weight);
	
	cur = *head;
	
	unordered_map<int, vector<int>> MovableData;
	
	while(cur!= NULL /* && cur->getNodeID() != nodeID)
	{
		if(cur->getStatus() != false)
		{
			unordered_map<int, int> nodeData = cur->getData();
			int cumulative_weight = cur->getCumulativeWeight();
			for(auto it = nodeData.begin(); it != nodeData.end(); ++it)
			{
				int hashValue = it->first;
				int replicaNo = it->second;
				
				float hash = float((hashValue+replicaNo)%cumulative_weight)/cumulative_weight;
				if(hash >= cur->getCumulativeWeightRatio())
				{
					MovableData[hashValue].push_back(replicaNo);
					MovableData[hashValue].push_back(cur->getNodeID());
				}
			}
		}
		cur = cur->getNext();
	}
	
	for(auto it = MovableData.begin(); it!= MovableData.end(); ++it)
	{
		int dest = insert_data(head, it->first, it->second[0], NodeCount);
		it->second.push_back(dest);
	}

}*/

void AddNode(Node** head, Node** tail, int nodeID, int hashValue)
{
	Node* newNode = new Node(nodeID, hashValue);
	if(head == NULL)
	{
		*head = newNode;
	}
	else
	{
		Node* cur = *head;
		Node* prev = *tail;
		while(cur->getNext() != *head)
		{
			if(hashValue > cur->getHashValue())
			{
				prev = cur;
				cur = cur->getNext();
			}
			else{
				prev->setNext(&newNode);
				newNode->setNext(&cur);
				break;
			}
		}
		newNode->setNext(head);
		*head = newNode;
	}
}

/*void RemoveNode(Node** head, int nodeID, int NodeCount, vector<int> replicaTable)
{
	if(head == NULL)
	{
		cout<<"Invalid Head."<<endl;
		return;
	}
	else
	{
		Node* cur = *head;
		int weight = 0;
		unordered_map<int, int> FailedData;
		while(cur != NULL)
		{
			if(nodeID == cur->getNodeID())
			{
				cur->setStatus(false);
				weight = cur->getWeight();
				FailedData = cur->getData();
				break;
			}
			cur = cur->getNext();
		}
		
		for(auto it = FailedData.begin(); it!= FailedData.end(); ++it)
		{
			int dest = insert_data(head, it->first, replicaTable[it->first] , NodeCount);
			replicaTable[it->first]++;
		}	
	}
}	

void locate_data(Node** head, int data)
{
	Node* cur = *head;
	
	while(cur != NULL)
	{
		unordered_map<int, int> NodeData;
		NodeData = cur->getData();
		if(NodeData.find(data) != NodeData.end())
		{
			int NodeID = cur->getNodeID();
			int replicaNo = NodeData[data];
			cout<<NodeID<<" "<<replicaNo<<endl;
		}
		cur = cur->getNext();
	}
}*/

void print_data_all(Node** head, int NodeCount)
{
	Node* cur = *head;
	int i=0;
	while(i<NodeCount)
	{
		unordered_map<int, int> NodeData;
		cout<<"NodeID is "<<cur->getNodeID()<<endl;
		NodeData = cur->getData();
		for(auto it = NodeData.begin(); it != NodeData.end(); it++)
		{
			cout<<it->first<<" "<<it->second<<" ";
		}
		cout<<endl;
		cur = cur->getNext();
		i++;
	}
}

int main()
{
	int n, m, r;
	cout<<"Enter the values of n, m and r"<<endl;
	cin>>n>>m>>r;
	
	Node* head = NULL;
	Node* tail = NULL;
	int NodeCount = 0;
	
	for(int i=0;i<n;i++)
	{
		int hashValue = i*(pow(2, m)/n);
		Node* newNode = new Node(NodeCount, hashValue);
		if(tail == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->setNext(&head);
			tail->setNext(&newNode);
			tail = newNode;
		}
		NodeCount++;
	}
	
	Node* cur = head;
	int i=0;

	while(i<NodeCount)
	{
		cur->insertData(r, m);
		cur = cur->getNext();
		i++;
	}
	
	print_data_all(&head, NodeCount);
	
	int choice;
	
	do
	{
		cout<<"Please Select your operation."<<endl;
		cout<<"1. Add Node"<<endl;
		cout<<"2. Remove Node"<<endl;
		cout<<"3. Locate Data"<<endl;
		cout<<"4. Balance Load"<<endl;
		cout<<"5. Exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter hash value of newly added node"<<endl;
				int hashvalue;
				cin>>hashvalue;
				AddNode(&head, &tail, NodeCount, hashvalue);
				NodeCount++;
				break;
			}
			case 2:
			{
				cout<<"Enter the ID of node to be removed"<<endl;
				int nodeID;
				cin>> nodeID;
				//RemoveNode(&head, nodeID, NodeCount, replicaTable);
				break;
			}
			case 3:
			{
				cout<<"Enter the hash value of data to be located"<<endl;
				int data;
				cin >> data;
				//locate_data(&head, data);
				break;
			}
			case 4:
			{
				cout<<"Enter the nodeID and new weight"<<endl;
				int nodeID, weight;
				cin >> nodeID >> weight;
				//balance_load(&head, nodeID, weight, NodeCount);
				break;
			}
			case 5:
				break;
			case 6:
				print_data_all(&head, NodeCount);
				break;
			default:
			{
				cout<<"Invalid Option"<<endl;
				break;
			}
		}
	}while(choice!=5);
	
	return 0;	
}