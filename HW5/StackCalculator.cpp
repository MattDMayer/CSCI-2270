#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead=nullptr;
}

StackCalculator::~StackCalculator()
{
  //TODO: 

}

bool StackCalculator::isEmpty()
{
	//TODO:
  if(stackHead==nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void StackCalculator::push(float number)
{
  //TODO:
  Operand *top = new Operand;
  if(isEmpty())
  {
    top->next=nullptr;
  }
  else
  {
    top->next=stackHead;
  } 
  top->number=number;
  stackHead=top;
}

void StackCalculator::pop()
{
	//TODO:
  if(stackHead==nullptr)
  {
    cout<<"Stack empty, cannot pop an item."<<endl;
  }
  else
  {
    Operand *top=stackHead;
    stackHead=stackHead->next;
    delete top;
  }
}

Operand* StackCalculator::peek()
{
	//TODO:
  if(stackHead==nullptr)
  {
    cout<<"Stack empty, cannot peek."<<endl;
    return nullptr;
  }
  else
  {
    return stackHead;
  }
}

bool StackCalculator:: evaluate(string* s, int size)
{
  float temp1;
  float temp2;
  float solution;
  int operands;
  for(int i=size-1;i>=0;i--)
  {
    if(isNumber(s[i]))
    {
      push(stof(s[i]));
      operands++;
    }
    else if((s[i]=="*"||s[i]=="+")&&operands>=2)
    {
      operands=operands-1;
      if(s[i]=="*")
      {
        temp1=peek()->number;
        pop();
        temp2=peek()->number;
        pop();
        solution=temp1*temp2;
      }
      else
      {
        temp1=peek()->number;
        pop();
        temp2=peek()->number;
        pop();
        solution=temp1+temp2;
      }
      push(solution);
    }
    else
    {
      if(s[i]!="+"&&(s[i])!="*")
      {
        cout<<"err: invalid operation"<<endl;
      }
      else
      {
        cout<<"err: not enough operands"<<endl;
      }  
      return false;
    }
  }
  return true;
}