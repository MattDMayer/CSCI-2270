#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;



int main()
{
  // stack to hold the operands
  StackCalculator stack;

  int numElement = 0;
  string* inparr = new string[50];

  // enter a number
  string number;
  cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;
  while(true)
  {
    cout << "#> ";
    getline(cin, number);

   if(number!="=")
   {
     inparr[numElement]=number;
     numElement++;
   }
   else
   {
     break;
   }
  }

 if(inparr[0]=="")
 {
   cout<<"No operands: Nothing to evaluate"<<endl;
 }
 else
 {
   if(stack.evaluate(inparr, numElement)==true)
   {
     cout<<"Result= "<<stack.getStackHead()->number<<endl;
   }  
 }
  return 0;
}
