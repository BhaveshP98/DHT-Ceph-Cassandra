#include "Cassandra.h"

void balance_load(Node** head, Node** tail, int nodeID, bool balance_type, int NodeCount, int balance_percent)
{
	
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


/*void locate_data(Node** head, int data)
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
				//locate_data(&head, data);
				break;
			}
			case 4:
			{
				cout<<"Enter the nodeID and new weight"<<endl;
				int nodeID, balance_type, balance_percent;
				cin >> nodeID;
				cout<<"Please select the type of load balance"<<endl;
				cout<<"1.Increase the load of node."<<endl;
				cout<<"2.Decrease the load of node."<<endl;
				cin>>balance_type;
				if(balance_type == 1 || balance_type == 2)
				{
					cout<<"Please enter the percentage increase/decrease of load"<<endl;
					cin>>balance_percent;
					balance_load(&head, &tail, nodeID, balance_type-1,NodeCount, balance_percent);
				}
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