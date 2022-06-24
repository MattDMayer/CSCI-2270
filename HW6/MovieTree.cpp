#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Helper function: Create new node using provided args
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  root=nullptr;
}

void destructor(MovieNode *current)
{
  if(current!=nullptr)
  {
    destructor(current->left);
    destructor(current->right);
    delete current;
  }
}

MovieTree::~MovieTree() 
{
  destructor(root);  
  root=nullptr;
}

void printHelper(MovieNode *node)
{
  if(node==nullptr)
  {
    return;
  }
  else
  {
    printHelper(node->left);
    cout<<"Movie: "<<node->title<<" ("<<node->rating<<")"<<endl;
    printHelper(node->right);
  }
}

void MovieTree::printMovieInventory() 
{
  if(root==nullptr)
  {
    cout<<"Tree is empty. Cannot print."<<endl;
  }
  else
  {
    printHelper(root);
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) 
{
  MovieNode *node=new MovieNode;
  node->ranking=ranking;
  node->title=title;
  node->year=year;
  node->rating=rating;
  MovieNode *pres=root;
  MovieNode *prev=nullptr;
  if(root==nullptr)
  {
    root=node;
  }
  else
  {
    while(pres!=nullptr)
    {
      prev=pres;
      if(node->title.compare(pres->title)<0)
      {
        pres=pres->left;
        if(pres==nullptr)
        {
          prev->left=node;
          return;
        }
      }
      else if(node->title.compare(pres->title)==0)
      {
        return;
      }
      else
      {
        pres=pres->right;
        if(pres==nullptr)
        {
          prev->right=node;
          return;
        }
      }
    }
  } 
}

void MovieTree::findMovie(string title)
{
  MovieNode *node;
  node=root;
  while(node!=nullptr)
  {
    if(node->title==title)
    {
      cout<<"Movie Info:"<<endl;
      cout<<"=================="<<endl;
      cout<<"Ranking:"<< node->ranking <<endl;
      cout<<"Title  :"<< node->title <<endl;
      cout<<"Year   :"<< node->year <<endl;
      cout<<"Rating :"<< node->rating <<endl;
      return;
    }
    else if(title.compare(node->title)<0)
    {
      node=node->left;
    }
    else
    {
      node=node->right;
    }
  }
  cout<<"Movie not found."<<endl;
  return;
}

void queryRecursive(float rating, int year, MovieNode *node)
{
  if(node==nullptr)
  {
    return;
  }
  else
  {
    if(node->year>year&&(node->rating>=rating))
    {
      cout<<node->title<<" ("<<node->year<<") "<<node->rating<<endl;
    }
    queryRecursive(rating,year,node->left);
    queryRecursive(rating,year,node->right);
  }
}

void MovieTree::queryMovies(float rating, int year) 
{
  if(root==nullptr)
  {
    cout<<"Tree is Empty. Cannot query Movies."<<endl;
  }
  else
  {
    cout<<"Movies that came out after "<<year<<" with rating at least "<<rating<<":"<<endl;
    queryRecursive(rating,year,root);
  }
}

void averageRatingRecursive(MovieNode *node, float *total, int *count)
{
  if(node==nullptr)
  {
    return;
  }
  else
  {
    *count+=1;
    *total+=node->rating;
    averageRatingRecursive(node->left,total,count);
    averageRatingRecursive(node->right,total,count);
  }
}

void MovieTree::averageRating() 
{
  if(root==nullptr)
  {
    cout<<"Average rating:0.0"<<endl;
  }
  else
  {
    float *total=new float;
    *total=0;
    int *count=new int;
    *count=0;
    averageRatingRecursive(root,total,count);
    cout<<"Average rating:"<<(*total/(*count))<<endl;
    delete total;
    delete count;
  }
}

void printLevelNodesHelp(MovieNode *node, int target, int row)
{
  if(node==nullptr)
  {
    return;
  }
  if(row==target)
  {
    cout<<"Movie: "<<node->title<<" ("<<node->rating<<")"<<endl;
  }
  row++;
  printLevelNodesHelp(node->left,target,row);
  printLevelNodesHelp(node->right,target,row);
}

void MovieTree::printLevelNodes(int level) 
{
  printLevelNodesHelp(root,level,0);
}