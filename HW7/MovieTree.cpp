#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void listDestructor(TreeNode* current)
{
	LLMovieNode *pres=current->head;
	LLMovieNode *ahead=nullptr;
	while(pres!=nullptr)
	{
		ahead=pres->next;
		delete pres;
		pres=ahead;
	}
	current=nullptr;
}
void destructor(TreeNode *current)
{
	if(current==nullptr)
	{
		return;
	}
	else
	{
		destructor(current->leftChild);
		destructor(current->rightChild);
		listDestructor(current);
		delete current;	
	}
}

MovieTree::~MovieTree() 
{
  destructor(root);  
  root=nullptr;
}

/* ------------------------------------------------------ */
void inorderTraversalHelper(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		inorderTraversalHelper(root->leftChild);
		cout << root->titleChar << " ";
		inorderTraversalHelper(root->rightChild);
}

void MovieTree::inorderTraversal() {
	inorderTraversalHelper(root);
	cout << endl;
}

/* ------------------------------------------------------ */
TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/* ------------------------------------------------------ */
void showCollectionTraversalHelper(TreeNode* root)
{
	if (root==nullptr)
	{
		return;
	}
	else
	{
		showCollectionTraversalHelper(root->leftChild);
		if(root->head!=nullptr)
		{
			cout<<"Movies starting with letter: "<<root->titleChar<<endl;
			LLMovieNode *temp=root->head;
			while(temp->next!=nullptr)
			{
				cout<<" >> "<<temp->title<<" "<<temp->rating<<endl;
				temp=temp->next;
			}
			cout<<" >> "<<temp->title<<" "<<temp->rating<<endl;
		}
		showCollectionTraversalHelper(root->rightChild);
	}	
}

void MovieTree::showMovieCollection()
{
	showCollectionTraversalHelper(root);
}

//------------------------------------------------------

void MovieTree::insertMovie(int ranking, std::string title, int year, float rating)
{
	LLMovieNode *node=new LLMovieNode;
	node->ranking=ranking;
	node->title=title;
	node->year=year;
	node->rating=rating;
	if(searchCharNode(title[0])==nullptr)
	{
		TreeNode *temp=new TreeNode;
		temp->titleChar=title[0];
		temp->head=node;
		TreeNode *pres=root;
		TreeNode *prev=nullptr;
		if(root==nullptr)
		{
			root=temp;
		}
		else
		{
			while(pres!=nullptr)
			{
				prev=pres;
				if(temp->titleChar<pres->titleChar)
				{
					pres=pres->leftChild;
					if (pres==nullptr)
					{
						prev->leftChild=temp;
						temp->parent=prev;
						return;
					}
				}
				else
				{
					pres=pres->rightChild;
					if(pres==nullptr)
					{
						prev->rightChild=temp;
						temp->parent=prev;
						return;
					}
				}
			}
		}
	}	
	else
	{
		LLMovieNode *present;
		LLMovieNode *previous;
		present=searchCharNode(title[0])->head;
		previous=nullptr;
		if(present==nullptr||(node->title<present->title))
		{
			searchCharNode(title[0])->head=node;
			node->next=present;
			return;
		}
		previous=present;
		present=present->next;
		while(present!=nullptr)
		{
			if(node->title<present->title)
			{
				node->next=present;
				previous->next=node;
				return;
			}
			previous=previous->next;
			present=present->next;
		}
		previous->next=node;
		node->next=nullptr;
		return;
	}
}

//-------------------------------------------------

void MovieTree::removeMovieRecord(std::string title)
{
	if((root==nullptr)||searchCharNode(title[0])->head==nullptr)
	{
		cout<<"Movie not found."<<endl;
		return;
	}
	else
	{
		LLMovieNode *pres = searchCharNode(title[0])->head;
		LLMovieNode *prev =nullptr;
		if(pres->title==title&&(prev==nullptr))
		{
			searchCharNode(title[0])->head=pres->next;
			delete pres;
			return;
		}
		else
		{
			while(pres!=nullptr)
			{
				if(pres->title==title)
				{
					prev->next=pres->next;
					delete pres;
					return;
				}
				prev=pres;
				pres=pres->next;
			}
			cout<<"Movie not found."<<endl;
			return;
		}	
	}
}
//------------------------------------------------

void MovieTree::leftRotation(TreeNode* curr)
{
	TreeNode *x=curr;
	if(curr->rightChild==NULL)
	{
		return;
	}
	TreeNode *y=curr->rightChild;
	if(x==root)
	{
		y->parent=NULL;
		x->parent=y;
		x->rightChild=y->leftChild;
		y->leftChild=x;
		root=y;
	}
	else
	{
		TreeNode *orgin=curr->parent;
		y->parent=x->parent;
		x->parent=y;
		x->rightChild=y->leftChild;
		y->leftChild=x;
		if(y->titleChar<orgin->titleChar)
		{
			orgin->leftChild=y;
		}
		else if (y->titleChar>orgin->titleChar)
		{
			orgin->rightChild=y;
		}
	}	
}