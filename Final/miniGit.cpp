#include "miniGit.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;


bool fileExists(string filename){
    filename.insert(0,"./.minigit/");
    ifstream file;
    //cout << "Checking: " << filename << endl;
    file.open(filename);
    if(!file.is_open()){
        //cout << "File not found!" << endl;
        return false;
    }else{
        return true;
    }
}

void miniGit::initialize()
{
    commitList *newCommit = new commitList;       //A new DLL is added with it's commit number as 0 and everything is null
    newCommit->commitNumber = 0;
    newCommit->next = nullptr;
    newCommit->prev = nullptr;
    newCommit->fileHead = nullptr;
    commits=newCommit;
    fs::remove_all(".minigit");       //The minigit directory is then made. It is cleared first in case you already have a repository from
    fs::create_directory(".minigit"); //testing
}  

void miniGit::addFile()
{
    bool naming = true;
    string fileName;
    ifstream fileI;
    while(naming == true)      //A while loop for naming it won't break if you try to do a file that isn't in the directory.
    {
        cout<<"Enter a file name:"<<endl;
        cin>>fileName;
        if(fileName=="q")  //A return is here if the file name is set to "q" so you aren't stuck in an infinite loop if you have no files.
        {
            return;
        }
        fileI.open(fileName);
        if(fileI.fail()) //This use of opening an ifstream is to see if the file can be found in the current directory, if it fails i.e.
        {                //it can't be found, the program says it can't be found.
            cout<<"A file with that name could not be found, enter another file name or enter 'q' to quit"<<endl;
        }     
        else
        {
            naming=false; //If a file with the given file name is found the loop control variable is set to false so the loop can end.
        }   
        fileI.close();
    }
    fileList *temp;
    temp = commits->fileHead;
    while(temp!=nullptr) //Here I set the temp singley list node to the head and search through to see if the file already is in the SLL.
    {
        if(temp->fileName.substr(0,fileName.length())==fileName)
        {
            cout<<"This file has already been added."<<endl;
            return;
        }
        temp=temp->next;
    }
    fileList *adding = new fileList;  //If the file doesn't already exist I make a new SLL node and set it's attributes.
    adding->fileName = fileName;
    adding->next = nullptr;
    string prefix;
    string suffix;
    for(int i=0;i<fileName.size();i++) //Here the version name is made.
    {
        if(fileName.substr(i,1)==".")
        {
            prefix = fileName.substr(0,i);
            suffix = fileName.substr(i,4);
        }
    }
    string version = prefix + "_00" + suffix;
    adding->fileVersion = version;
    if(temp==commits->fileHead)    //Here the SLL node is placed in the SLL.
    {
        commits->fileHead = adding;
    }
    else
    {
        temp = commits->fileHead;
        while(temp->next!=nullptr)
        {
            temp=temp->next;
        }
        temp->next = adding;
    }  
}

void miniGit::removeFile()
{
    fileList *temp;
    fileList *prev;
    prev = nullptr;
    temp = commits->fileHead;
    if (temp == nullptr) //Here it checks if the SLL is empty already, if it is, a file can't be removed.
    {
        cout << "Cannot remove file, commit is empty." << endl;
        return;
    }
    string rmvFile;
    ifstream file;
    bool naming = true;
    while(naming == true)      //A while loop for naming it won't break if you try to do a file that isn't in the directory.
    {
        cout<<"Enter a file for deletion:"<<endl;
        cin>>rmvFile;
        if(rmvFile=="q")  //A return is here if the file name is set to "q" so you aren't stuck in an infinite loop if you have no files.
        {
            return;
        }
        file.open(rmvFile);
        if(file.fail()) //This use of opening an ifstream is to see if the file can be found in the current directory, if it fails i.e.
        {                //it can't be found, the program says it can't be found.
            cout<<"A file with that name could not be found, enter another file name or enter 'q' to quit"<<endl;
        }     
        else
        {
            naming=false; //If a file with the given file name is found the loop control variable is set to false so the loop can end.
        }   
        file.close();
    }
    while(temp != nullptr)
    {
        if(temp->fileName == rmvFile && (temp == commits->fileHead)) //Here is the case where the file being removed is the head of the SLL.
        {
            commits->fileHead = temp->next;
            cout<<"Removed "<<temp->fileName<<"."<<endl;
            delete temp;
            return;
        }
        else if(temp->fileName == rmvFile && (temp != commits->fileHead)) //Here is the code for every other case.
        {
            prev->next = temp->next;
            cout << "Removed " << temp->fileName << "." << endl;
            delete temp;
            return;
        }
        else   //This moves the search along.
        {
            prev = temp;   
            temp = temp->next;
        }
    }
    cout<<"File by that name could not be found, no files removed."<<endl; //If the file to be removed can't be found, it says as much.
    return;
}

fileList* cloneList(fileList* list){ //HELPER FUNCTION that just copies the previous SSL to the next one.

    fileList* newNode = new fileList;
    newNode->fileName = list->fileName;
    newNode->fileVersion = list->fileVersion;
    if(list->next != NULL)
    {
        newNode->next = cloneList(list->next);
    }
    return newNode;
}

void copyFile(string filename, string destination){
    ifstream file;
    file.open(filename);
    string fileContents;
    if(file){
        ostringstream ss;
        ss << file.rdbuf(); //this line is supposed to read the file and put in in the string (thanks string stream)
        fileContents = ss.str();
    }
    // while (getline(file, fileContents)){
    //     fileContents.append(fileContents);
    // }
    //cout << "Writing: " << endl << fileContents << endl;
    ofstream writeFile(destination);
    writeFile << fileContents;
}


void miniGit::commit()
{
    //cout << "1" << endl;
    //Create a new commit with changes of the added files
    auto search = commits->fileHead;
    while(search != nullptr){
        if(!fileExists(search->fileVersion)){
            string filename = search->fileVersion;
            filename.insert(0, ".minigit/");
            //cout << "at copy 1 " << endl;
            copyFile(search->fileName, filename);//Im pretty sure this is going to be able to take the file from ssl and put it in .minigit as its "file_00.txt" ver
        }else if(fileExists(search->fileVersion)){
            string readFile;
            string file1;
            string file2;
            string filename = search->fileVersion;
            filename.insert(0, ".minigit/");
            ifstream file1file;
            ifstream file2file;
            file1file.open(search->fileName);
            file2file.open(filename);
            while (getline(file1file, readFile))//comparing the files
            {
                file1.append(readFile);
            }
            while(getline(file2file, readFile)){
                file2.append(readFile);
            }
            if(file1 != file2){
                string newFileName = search->fileVersion;
                bool period = false;
                int periodInt = 0; 
                string verString;
                string newVerString;
                int ver = stoi(newFileName.substr(newFileName.find_last_of("_") + 1, 2)); 
                int newVer = ver;
                newVerString = to_string(ver + 1);
                if(ver < 9){
                    newVerString.insert(0,"0");
                    newFileName.replace(newFileName.end()-6, newFileName.end()-4, newVerString);
                }else{
                    newFileName.replace(newFileName.end()-6, newFileName.end()-4, newVerString);
                }
                search->fileVersion = newFileName;
                //TODO: File name needs to be incrimented a version up.
                //the file name change should also be reflected in search->fileversion
                newFileName.insert(0, ".minigit/");
                //cout << "At copy 2" << endl;
                copyFile(search->fileName, newFileName);
            }
            else
            {
                cout<<"A version of this file already exists, skipping file."<<endl;
            }   
        }
        search = search->next;
    }
    commitList* temp = new commitList;
    temp->prev = commits;
    commits->next = temp;
    commits = temp;
    commits->fileHead = cloneList(commits->prev->fileHead);
    commits->commitNumber=commits->prev->commitNumber+1;
    cout << "Commit Finished" << endl;
    cout << "Current LL:" << endl;
    auto find = commits->fileHead;
    while(find != NULL){
        cout << find->fileVersion << endl;
        find = find->next;
    }
}

void replaceFiles(fileList* file) //HELPER FUNCTION to run through the fileList and place those versions in the current 
{
    if(file == NULL)
    {
        //This should never be called, BUT if it DOES, it will stop catastrophic failure, hopefully
        cout << "File storage error." << endl;
        return;
    }
    string source = file->fileVersion;
    source = ".minigit/" + source; //Gets the source of the file replacement stored in the .minigit folder
    string destination = file->fileName; //Gets the destination file that will be replaced with checkout
    string curLine; //A temporary string to facilitate transfer of source to destination
    ifstream inFile;
    ofstream outFile;  

    //Copy each line of text in source to the destination file
    inFile.open(source);
    outFile.open(destination);
    while(getline(inFile, curLine))
    {
        outFile << curLine;
    }

    //Finally progress to the next node of the fileList, if it exists
    if(file->next != NULL)
    {
        replaceFiles(file->next);
    }
}

void miniGit::checkout(int commitNumber)
{
    //Return the state of the commitNumber'th commit

    if(commitNumber == -1)
    {
        //If the user wants to return to the latest commit return to the top of the commitList
        replaceFiles(commits->fileHead);
        cout << "Returned files to latest versions." << endl;
        return;
    }

    if(commitNumber > commits->commitNumber || commitNumber < 0)
    {
        //If the commit number is invalid there will be no attempt to find it
        cout << "Please enter a valid commit number." << endl;
        return;
    }

    //Warn users about unsaved work
    cout << "Checking out will clear all noncommited work, would you like to procede? (y/n): ";
    string input;
    cin >> input;
    if(input == "n" || input == "N")
    {
        //If the user doesn't want to procede it quits the checkout
        return;
    }

    //Else it is assumed that the user wants to continue
    commitList* checkout = commits;
    while (checkout->commitNumber != commitNumber && checkout != NULL) //We've already checked if the commit exists so we just need to find it
    {
        checkout = checkout->prev;
    }
    
    //After finding the commitList node we replace the current version of the files commited with the commited version
    replaceFiles(checkout->fileHead);
    cout << "Returned files to their state from commit #" << commitNumber << ".\n";
}
