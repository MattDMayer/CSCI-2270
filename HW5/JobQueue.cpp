    #include "JobQueue.hpp"
    #include <string>
    #include <iostream>
    using namespace std;

    JobQueue::JobQueue()
    {
        counter =0;
        queueEnd=0;
        queueFront=0;
    }
    bool JobQueue::isEmpty()
    {
        if (counter==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool JobQueue::isFull()
    {
        if(counter==SIZE)
        {
            return true;
        }
        else
        {
            return false;
        } 
    }
    void JobQueue::enqueue(std::string job)
    {
        if(isFull()==true)
        {
            cout<<"Queue full, cannot add new job"<<endl;
        }
        else
        {   
            if(queueEnd==SIZE)
            {
                queueEnd=0;
            }
            queue[queueEnd]=job;
            if(queueEnd!=SIZE)
            {
                queueEnd++;
            }
            counter++;
        }   
    }
    void JobQueue::dequeue()
    {
        if(isEmpty()==false)
        {
            if(queueFront==SIZE)
            {
                queueFront=0;
            }
            queue[queueFront]="";
            if(queueFront!=SIZE)
            {
                queueFront++;
            }
            counter--;
        }
        else
        {
            cout<<"Queue empty, cannot dequeue a job"<<endl;
        }  
    }
    string JobQueue::peek()
    {
        if(isEmpty())
        {
            cout<<"Queue empty, cannot peek"<<endl;
        }
        else
        {
            return queue[queueFront];
        } 
    }
    int JobQueue::queueSize()
    {
        return counter;
    }
int JobQueue::getQueueFront() 
{ return queueFront; }
int JobQueue::getQueueEnd() 
{ return queueEnd; }
std::string* JobQueue::getQueue()
{ return queue; }

