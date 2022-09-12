#include "miniGit.hpp"
#include <iostream>
#include <string>
using namespace std;

void printMenu()
{
    //A function to print the menu
    cout << "\\_________________________________/" << endl;
    cout << "1) Initialize" << endl;
    cout << "2) Add File" << endl;
    cout << "3) Remove File" << endl;
    cout << "4) Commit" << endl;
    cout << "5) Checkout" << endl;
    cout << "6) Quit" << endl;
    cout << "\\_________________________________/" << endl;
    cout << ">";
}

int main()
{
    int menuChoice = 0;
    bool initialized = false;
    miniGit git;

    while(menuChoice != 6)
    {
        //Call menu print to prompt the user
        printMenu();
        cin>>menuChoice;
        //Switch statement to handle user choice
        switch(menuChoice)
        {
            case 1: //Initalizing the miniGit object
                if(!initialized)
                {
                    //Only actually tries to initialize if there isn't already a miniGit
                    initialized = true;
                    git.initialize();
                    cout << "miniGit initialized." << endl;
                }
                else
                {   
                    //Informs user that miniGit is already existing
                    cout << "miniGit already initialized." << endl;
                }
                break;
            case 2: //Add files to the commit
                if(!initialized) //Doesn't allow modification of git if it doesnt exist
                {
                    cout << "Please initialize the miniGit first." << endl;
                }
                else
                {
                    git.addFile(); //Call addFile to add it to the commit
                }
                break;
            case 3: //Remove files from the commit
                if(!initialized) //Doesn't allow modification of git if it doesnt exist
                {
                    cout << "Please initialize the miniGit first." << endl;
                }
                else
                {
                    git.removeFile(); //Call removeFile to remove rmvFile
                }
                break;
            case 4: //Commit's the state of the git
                if(!initialized) //Doesn't allow modification of git if it doesnt exist
                {
                    cout << "Please initialize the miniGit first." << endl;
                }
                else
                {
                    cout << "Attemping to commit." << endl;
                    git.commit(); //Call commit, commit will have feedback for the user
                }
                break;
            case 5: //Checkout an older video
                if(!initialized) //Doesn't allow modification of git if it doesnt exist
                {
                    cout << "Please initialize the miniGit first." << endl;
                }
                else
                {
                    int commitNo;
                    cout << "Enter the number of the commit you'd like to checkout, or -1 to return to the latest commit: ";
                    cin >> commitNo;
                    cin.clear();
                    cin.ignore(100, '\n');
                    git.checkout(commitNo);
                }
                break;
            case 6:
                cout << "Goodbye!";
                break;
            default:
                cout << "Please enter a valid choice." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                break;
        }
    }
}