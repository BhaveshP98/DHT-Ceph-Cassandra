#include "Cassandra.h"

void balance_load(Node** head, Node** tail, int nodeID1, int nodeID2, int NodeCount, int load, int m, int r)
{
	Node* node1_next = *head;
	Node* node1 = *tail;
	int i=0;
	while(i<NodeCount)
	{
		if(node1->getNodeID() == nodeID1)
		{
			Node* prev= node1;
			Node* cur = node1_next;
			Node* node2;
			while(cur->getNodeID() != nodeID2)
			{
				cur->setHashValue(load);
				cur = cur->getNext();
			}
			cur->setHashValue(load);
			node2 = cur;
			cur = node1_next;
			
			while(prev!=node2)
			{
				Node* cur2 = cur;
				Node* prev2 = prev;
				prev2->enterOriginalData(int(pow(2, m)));
				cur2->enterOriginalData(int(pow(2, m)));
				for(int i=0;i<r;i++)
				{
					vector<unordered_set<int>> prevData = prev2->getData();
					for(int j=0;j<r-1;j++)
					{
						cur2->SetData(prevData[j], j+1);
					}
					prev2 = cur2;
					cur2 = cur2->getNext();
				}
				prev = cur;
				cur = cur->getNext();
			}
		}
		node1 = node1_next;
		node1_next = node1_next->getNext();
		i++;
	}
}

void AddNode(Node** head, Node** tail, int nodeID, int hashValue, int r, int m)
{
	Node* newNode = new Node(nodeID, hashValue, r);
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
				cur = newNode;
				break;
			}
		}
		prev->enterOriginalData(int(pow(2, m)));
		cur->enterOriginalData(int(pow(2, m)));
		

		for(int i=0;i<r;i++)
		{
			vector<unordered_set<int>> prevData = prev->getData();
			for(int j=0;j<r-1;j++)
			{
				cur->SetData(prevData[j], j+1);
			}
			prev = cur;
			cur = cur->getNext();
		}
	}
}

void RemoveNode(Node** head, Node** tail, int nodeID, int r, int m)
{
	if(head == NULL)
	{
		return;
	}
	else
	{
		Node* cur = *head;
		Node* prev = *tail;
		while(cur->getNext() != *head)
		{
			if(cur->getNodeID() != nodeID)
			{
				prev = cur;
				cur = cur->getNext();
			}
			else{
				Node* cur_next = cur->getNext();
				prev->setNext(&cur_next);
				cur->setNext(NULL);
				free(cur);
				cur = cur_next;
				break;
			}
		}
		prev->enterOriginalData(int(pow(2, m)));
		//cur->enterOriginalData(int(pow(2, m)));
		

		for(int i=0;i<r;i++)
		{
			vector<unordered_set<int>> prevData = prev->getData();
			for(int j=0;j<r-1;j++)
			{
				cur->SetData(prevData[j], j+1);
			}
			prev = cur;
			cur = cur->getNext();
		}
	}
}


void locate_data(Node** head, int hashValue, int NodeCount)
{
	Node* cur = *head;
	int i=0;
	while(i<NodeCount)
	{
		vector<unordered_set<int>> data = cur->getData();
		if(data[0].find(hashValue) == data[0].end())
		{
			cur = cur->getNext();
			i++;
		}
		else
		{
			int nodeID = cur->getNodeID();
			cout<<"Given hash value is located at node Id: "<<nodeID<<endl;
		}
	}
}

void print_data_all(Node** head, int NodeCount)
{
	Node* cur = *head;
	int i=0;
	while(i<NodeCount)
	{
		vector<unordered_set<int>> NodeData;
		cout<<"NodeID is "<<cur->getNodeID()<<endl;
		NodeData = cur->getData();
		for(int i=0;i<NodeData.size();i++)
		{
			for(auto it = NodeData[i].begin(); it != NodeData[i].end(); it++)
			{
				cout<<*it<<" "<<i<<" ";
			}
			cout<<endl;
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
		Node* newNode = new Node(NodeCount, hashValue, r);
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
	int j=0;

	while(j<NodeCount)
	{
		cur->insertData(r, m);
		cur = cur->getNext();
		j++;
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
		cout<<"5. Print data in all nodes"<<endl;
		cout<<"6. Exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter hash value of newly added node"<<endl;
				int hashvalue;
				cin>>hashvalue;
				AddNode(&head, &tail, NodeCount, hashvalue, r, m);
				NodeCount++;
				break;
			}
			case 2:
			{
				cout<<"Enter the ID of node to be removed"<<endl;
				int nodeID;
				cin>> nodeID;
				RemoveNode(&head, &tail, nodeID, r, m);
				NodeCount--;
				break;
			}
			case 3:
			{
				cout<<"Enter the hash value of data to be located"<<endl;
				int data;
				cin >> data;
				locate_data(&head, data, NodeCount);
				break;
			}
			case 4:
			{
				cout<<"Enter the nodeIDs of underloaded and overloaded nodes"<<endl;
				int nodeID1, nodeID2, load;
				cin >> nodeID1 >> nodeID2;
				cout<<"Enter the amount of load to be balanced"<<endl;
				cin >> load;
				
				balance_load(&head, &tail, nodeID1, nodeID2, load, NodeCount, m, r);
				
				break;
			}
			case 5:
				print_data_all(&head, NodeCount);
				break;
			case 6:
				break;
			default:
			{
				cout<<"Invalid Option"<<endl;
				break;
			}
		}
	}while(choice!=6);
	
	return 0;	
}