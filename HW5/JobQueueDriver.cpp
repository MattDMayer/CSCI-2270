/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	int control=0;
	string name;
	JobQueue q;
	while(control!=3)
	{
		menu();
		cin>>control;
		switch(control)
		{
			case 1:
			{
				cout<<"Enter the number of jobs to be created:"<<endl;
				cin>>control;
				for(int i=1;i<=control;i++)
				{
					cout<<"job"<<i<<":"<<endl;
					cin>>name;
					q.enqueue(name);
				}
				control=0;
				break;
			}
			case 2:
			{
				cout<<"Enter the number of jobs to be dispatched:"<<endl;
				cin>>control;
				
				if(control>20)
				{
					for(int i=0;i<SIZE;i++)
					{
						cout<<"Dispatched: "<<q.peek()<<endl;
						q.dequeue();
					}
					cout<<"No more jobs to be dispatched from queue"<<endl;
				}
				else
				{
					if(q.queueSize()>=control)
					{
						for(int i=0;i<control;i++)
						{
							cout<<"Dispatched: "<<q.peek()<<endl;
							q.dequeue();
						}
					}
					else
					{
						for(int i=q.queueSize();i>0;i--)
						{
							cout<<"Dispatched: "<<q.peek()<<endl;
							q.dequeue();
						}
						cout<<"No more jobs to be dispatched from queue"<<endl;
					}		
				}
				control=0;
				break;
			}
			case 3:
			{
				cout<<"Number of jobs in the queue:"<<q.queueSize();
				break;
			}
		}
	}
	return 0;
}