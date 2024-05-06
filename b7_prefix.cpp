#include <iostream>
#include <string>
#include <stack>
using namespace std;

class node{
	public:
		char value;
		node* left;
		node* right;
		
		//Constructor
		node(char c){
			this->value=c;
			this->right=NULL;
			this->left=NULL;
		}
};

class ExpressionTree{
	node* root;
	public:
		ExpressionTree(){
			root=NULL;
		}
		
		bool isOperator(char c){
			return c=='+' || c=='-' || c=='*' || c=='/' ;
		}
		
		node* constructTree(const string& prefix);
		void postOrderTraversal(node* root);
		void deleteTree(node* root);
		void BuildAndTraverse();
};

node* ExpressionTree::constructTree(const string& prefix){
	stack<node*> s;
	for(int i=prefix.length();i>=0;i--){
		char c=prefix[i];
		node* temp=new node(c);
		
		if(isOperator(c)){			
			temp->left=s.top();
			s.pop();
			temp->right=s.top();
			s.pop();
			s.push(temp);
		}else{
			s.push(temp);			
		}
	}
	return s.top();
}

void ExpressionTree::postOrderTraversal(node* root){
	stack<node*> s1,s2;
	node* T=root;
	s1.push(T);
	
	while(!s1.empty()){
		T=s1.top();
		s1.pop();
		s2.push(T);
		if(T->left!=NULL){
			s1.push(T->left);
		}
		if(T->right!=NULL){
			s1.push(T->right);
		}
	}
	while(!s2.empty()){
		T=s2.top();
		s2.pop();
		cout<<T->value;
	}
	cout<<endl;
}

void ExpressionTree::deleteTree(node* root){
	if(root==NULL){
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	cout <<endl<<"Deleting node : " << root->value<<endl;	
	delete root;
}

void ExpressionTree::BuildAndTraverse(){
	string expression;
	cout<<"\nEnter Prefix Expression:";
	getline(cin,expression);
	
	root=constructTree(expression);
	cout<<"\nPost order Traversal:";
	postOrderTraversal(root);
	deleteTree(root);
	root=NULL;
}
int main(){
	ExpressionTree expTree;
	expTree.BuildAndTraverse();
}
