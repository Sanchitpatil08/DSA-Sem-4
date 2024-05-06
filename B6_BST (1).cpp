#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

class Tree
{
    private:
        Node *root;
    
    public:
        Tree()
        {
            root = NULL;
        }
        
        Node* createNode(int data)
        {
            Node *newNode = new Node();
            if (!newNode) 
            {
                cout << "Memory error\n";
                return NULL;
            }
            newNode->data = data;
            newNode->left = newNode->right = NULL;
            return newNode;
        }

        Node* insertNode(Node* root, int data)
        {
            if (root == NULL) 
            {
                root = createNode(data);
                return root;
            }

            if (data < root->data)
                root->left = insertNode(root->left, data);
            else
                root->right = insertNode(root->right, data);

            return root;
        }

        void insert(int data)
        {
            root = insertNode(root, data);
        }
        
        void inorder(Node* temp)
        {
            if (temp == NULL)
                return;

            inorder(temp->left);
            cout << temp->data << ' ';
            inorder(temp->right);
        }
        
        void display()
        {
            inorder(root);
            cout<<"\n";
        }
		
		Node* search_data(int key, Node* t)
		{
			Node* temp ;
			temp = t;
			
			while(temp != NULL)
			{
				if(temp->data == key)
				{
					return temp;
				}
				
				if(key>temp->data)
				{
					return search_data(key,temp->right);
				}
				else
				{
					return search_data(key, temp->left);
				}
			}
			return NULL;
		}
		
		void search(int data)
		{
			Node *p;
			p =	search_data(data,root);
			
			if( p== NULL)
			{
				cout<<"The data is not present, Sorry !"<<endl;
			}
			else
				cout<<"The data is present"<<endl;
		}
		
		int minimum()
		{
			Node* temp;
			temp = root;
			
			while(temp->left != NULL)
			{
				temp = temp->left;
			}
			return temp->data;
		}
		
		Node* swap(Node* root)
		{
			Node* p;
			if(root!=NULL)
			{
				p = root->left;
				root->left = swap(root->right);
				root->right = swap(p);
			}
			
			return root;
		}
		
		Node* mirror()
		{
			return this->swap(root);
		}
		
		int maximum(int x, int y)
		{
			if(x>y)
			{
				return x;
			}
			else
			{
				return y;
			}
		}
		
		int height_node(Node* root)
		{
			if(root == NULL)
			{
				return 0;
			}
			else if(root->left == NULL && root->right == NULL)
			{
				return 1;
			}
			else
			{
				return max(height_node(root->left), height_node(root->right)) + 1;
			}
		}
		
		int height()
		{
			return this->height_node(root);
		}
};

int main()
{
	Tree a;
	int flag = 0;
	do
	{
		int choice;
		cout<<"1.Insert\n2.Display\n3.Mirror\n4.Max Height\n5.Minimum Data\n6.Search Data\n7.Exit\nChoice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				int c;
				cout<<"Data To be Inserted : ";
				cin>>c;
				a.insert(c);
				cout<<"\n";
				break;
				
			case 2:
				a.display();
				cout<<"\n";
				break;
				
			case 3:
				a.mirror();
				a.display();
				cout<<"\n";
				break;
				
			case 4:
				cout<<"The maximum Height of the Tree is : "<<a.height()<<"\n";
				cout<<"\n";
				break;
				
			case 5:
				cout<<"The smallest Data in the given Tree is : "<<a.minimum()<<"\n";
				cout<<"\n";
				break;
				
			case 6:
				int y;
				cout<<"What is to be Searched : ";
				cin>>y;
				a.search(y);
				cout<<"\n";
				break;
				
			case 7:
				flag = 1;
				cout<<"\n";
				break;
				
			default:
				cout<<"Please Enter A valid Number";
				cout<<"\n";
				break;
		}
		
	}while(flag != 1);
	
	return 0;
}
