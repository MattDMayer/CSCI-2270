/*******************************************************************/
/*                CUBuildingNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*       This class uses a linked-list of CUBuilding nodes to      */
/*       represent communication paths between buildings           */
/*******************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() 
{
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the CUBuilding *previous and the CUBuilding that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int totalRoom) 
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding *newBuild=new CUBuilding;
    newBuild->name=buildingName;
    newBuild->totalRoom=totalRoom;
    newBuild->next=nullptr;
    CUBuilding *temp = new CUBuilding;
    CUBuilding *left=previous;
    if(left==nullptr)
    {
        newBuild->next=head;
        head=newBuild;
        cout<<"adding: "<<buildingName<< " (HEAD)"<<endl;
    }
    else if(left->next==nullptr)
    {
        left->next=newBuild;
        cout<<"adding: "<<buildingName<<" (prev: " <<left->name<<")"<<endl;
    }
    else
    {
        temp->next=left->next;
        left->next=newBuild;
        newBuild->next=temp->next;
        cout<<"adding: "<<buildingName<<" (prev: " <<left->name<<")"<<endl;
    }

}

/*
 * Purpose: populates the network with the predetermined CUBuildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    // TODO: Copy-paste your solution from Assignment 3
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings
    deleteEntireNetwork();
    CUBuilding *Build= new CUBuilding;
    Build=nullptr;
    addBuildingInfo(Build,"FLMG",2);
    Build=searchForBuilding("FLMG");
    addBuildingInfo(Build,"DLC",10);
    Build=searchForBuilding("DLC");
    addBuildingInfo(Build,"ECOT",6);
    Build=searchForBuilding("ECOT");
    addBuildingInfo(Build,"CASE",5);
    Build=searchForBuilding("CASE");
    addBuildingInfo(Build,"AERO",4);
    Build=searchForBuilding("AERO");
    addBuildingInfo(Build,"RGNT",9);

}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding *temp =head;
    while(temp!=nullptr)
    {
        if(temp->name==buildingName)
        {
            return temp;
        }
        temp=temp->next;
    }
    return nullptr;

}

/*
 * Purpose: Relay a message through the linked list until the specified CUBuilding
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding *building = new CUBuilding;
    bool nowhere = false;
    if(head==nullptr)
    {
        cout<<"Empty list"<<endl;
    }
    else if(searchForBuilding(receiver)==nullptr)
    {
        cout<<"Building not found"<<endl;
    }
    else
    {
        
        building=head;
        while(building->name!=receiver)
        {
            building->numberMessages++;
            building->message="available room at " +building->name+" is " + to_string(building->totalRoom);
            cout<<building->name<<" [# messages received: " <<building->numberMessages<<"] received: "<<building->message<<endl;
            building=building->next;
        }
        building->numberMessages++;
        building->message="available room at " +building->name+" is " + to_string(building->totalRoom);
        cout<<building->name<<" [# messages received: " <<building->numberMessages<<"] received: "<<building->message<<endl;
    }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() 
{
    // TODO: Copy-paste your solution from Assignment 3
    cout<<"== CURRENT PATH =="<<endl;
    if(head==nullptr)
    {
        cout<<"nothing in path"<<endl;
    }
    else
    {
        CUBuilding *building = new CUBuilding;
        building=head;
        while(building!=nullptr)
        {
            cout<<building->name<<"("<<building->totalRoom<<") -> ";
            building=building->next;
        }
        cout<<"NULL"<<endl;
    } 
    cout<<"==="<<endl;

}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the CUBuilding in the network with the specified name.
 * @param buildingName name of the CUBuilding to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) 
{
    CUBuilding *pres =new CUBuilding;
    CUBuilding *prev = new CUBuilding;
    CUBuilding *temp = new CUBuilding;
    pres=head;
    int counter=0;
    if(searchForBuilding(buildingName)==nullptr)
    {
        cout<<"Building does not exist."<<endl;
    }
    while(pres->next!=nullptr)
    {
        if(pres->name==buildingName)
        {
            if(counter==0)
            {
                temp=head;
                head=head->next;
                pres=head;
                delete temp;
            }
            else
            {
                prev->next=pres->next;
                temp =pres;
                pres=prev->next;
                delete temp;
            }           
        }
        prev=pres;
        pres=pres->next;
        counter++;
    }
    if(searchForBuilding(buildingName)!=nullptr)
    {
        prev=head;
        pres=prev->next;
        while(prev->next->name!=buildingName)
        {
            prev=pres;
            pres=pres->next;
        }
        prev->next=nullptr;
        delete pres;
        pres=nullptr;
    }
}

/*
 * Purpose: deletes all CUBuildings in the network starting at the head CUBuilding.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    if(head==nullptr)
    {
        return;
    }
    else
    {
        CUBuilding *pres = new CUBuilding;
        CUBuilding *next= new CUBuilding;
        pres=head;
        while(pres!=nullptr)
        {
            cout<<"deleting: "<<pres->name<<endl;
            next=pres->next;
            delete pres;
            pres=next;
        }
        head=nullptr;
        cout<<"Deleted network"<<endl;
    }
}

/*
* Purpose: Creates a loop from last node to the CUBuilding specified.
* @param buildingName name of the CUBuilding to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) 
{
    // TODO: Complete this function
    CUBuilding *pres=head;
    CUBuilding *temp = searchForBuilding(buildingName);
    while(pres->next!=nullptr)
    {
        pres=pres->next;
    }
    if(temp==nullptr)
    {
        return pres;
    }
    else
    {
        pres->next=temp;
    }
    return pres;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUBuildingNetwork::detectLoop() 
{
    // TODO: Complete this function
    if(head==nullptr)
    {
        return false;
    }
    CUBuilding *ahead = head->next;
    CUBuilding *behind=head;
    while((ahead->next!=nullptr)&&ahead!=nullptr&&(ahead!=nullptr))
    {
        if(ahead==behind)
        {
            return true;
        }
        ahead=ahead->next->next;
        behind=behind->next;
    }
    return false;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start_index, end_index
 * @return: none
 */
void CUBuildingNetwork::readjustNetwork(int start_index, int end_index)
{
    // TODO: Complete this function
    if(head==nullptr)
    {
        cout<<"Linked List is Empty"<<endl;
        return;
    }
    else if(start_index>end_index)
    {
        cout<<"Invalid indices"<<endl;
        return;
    }
    else if(end_index<0)
    {
        cout<<"Invalid end index"<<endl;
        return;
    }
    else if(start_index<0)
    {
        cout<<"Invalid start index"<<endl;
        return;
    }
    else
    {
        int index=0;
        CUBuilding *pres=head;
        while(pres->next!=nullptr)
        {
            pres=pres->next;

            index++;
        }
        if(end_index>=index)
        {
            cout<<"Invalid end index"<<endl;
            return;
        }
        if(start_index>=index)
        {
            cout<<"Invalid start index"<<endl;
            return;
        }
        pres=head;
        CUBuilding *start;
        CUBuilding *end;
        CUBuilding *beforeStart;
        CUBuilding *afterEnd;
        CUBuilding *prev;
        index=0;
        prev=nullptr;
        while(pres->next!=nullptr)
        {
            if(index==start_index)
            {
                start=pres;
                if(index==0)
                {
                    beforeStart=nullptr;
                }
                else
                {
                    beforeStart=prev;
                } 
            }
            if(index==end_index)
            {
                end=pres;
                afterEnd=pres->next;
            }
            prev=pres;
            pres=pres->next;
            index++;
        }
        if(beforeStart==nullptr)
        {
            beforeStart=afterEnd;
            head=beforeStart;
        }
        else
        {
            beforeStart->next=afterEnd;
        }
        pres->next=start;
        end->next=nullptr;
    } 
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUBuildingNetwork::~CUBuildingNetwork()
{
    // TODO: Complete this function

}
