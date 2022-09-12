#ifndef MINIGIT_H
#define MINIGIT_H

#include <filesystem>
#include <iostream>
using namespace std;

struct fileList
{
    string fileName;    //Unnumbered filename
    string fileVersion; //Version numbered filename, in .minigit/
    fileList* next;     //SLL functionallity
};

struct commitList
{
    int commitNumber;   //commit identity
    fileList* fileHead; //The commit's file list
    commitList* prev;   //Previous commit
    commitList* next;   //Next commit
};

class miniGit
{
    public:
        void initialize();              //Initialize the miniGit system
        void addFile();    //Add a file to the commit
        void removeFile(); //Remove a file from the commit
        void commit();                  //Commit the changes
        void checkout(int commitNumber);//Return to an old state
    private:
        commitList* commits;
};

#endif