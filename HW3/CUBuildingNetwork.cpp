/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
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
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) 
{
    CUBuilding *newBuild=new CUBuilding;
    newBuild->name=buildingName;
    newBuild->totalRoom=numOfroom;
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
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
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
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
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
