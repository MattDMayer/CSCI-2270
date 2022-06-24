#include <iostream>
#include <fstream>
using namespace std;

struct studentData
{
    string studentName;
    int homework;
    int recitation;
    int quiz; 
    int exam;
    double average;
};

int split (string toBeSplit, char delim, string arr[], int size)
{
    int lastPos = 0;
    int arryPosition=0;
    int maxCol = 50;
    int length = toBeSplit.length();
    for (int i = 0; i < length; i++){
        if (arryPosition >= size){
            return -1;
        }
        else if (toBeSplit[i]==delim){
            arr[arryPosition] = toBeSplit.substr(lastPos,i-lastPos);
            arryPosition = arryPosition+1;
            lastPos=i+1;
        }
        else if (i == length-1){
            arr[arryPosition] = toBeSplit.substr(lastPos);
            arryPosition = arryPosition+1;
            lastPos=i+1;
        }
    }
    //returns the number of things in the array
    return arryPosition;
}

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length)
{
    students[length].studentName=studentName;
    students[length].homework=homework;
    students[length].recitation=recitation;
    students[length].quiz=quiz;
    students[length].exam=exam;
    students[length].average=double((homework+recitation+quiz+exam)/4.0);
}

char calcLetter(double avg)
{
    if(avg>=90)
    {
        return'A';
    }
    else if(avg>80&&avg<=89.99)
    {
        return 'B';
    }
    else if(avg>70&&avg<=79.99)
    {
        return 'C';
    }
    else if(avg>60&&avg<=69.99)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

void printList(const studentData students[], int length)
{
    for(int i=0;i<length;i++)
    {
        cout<<students[i].studentName<< " earned "<< students[i].average<<" which is a(n) "<< calcLetter(students[i].average)<<endl;
    }
}

int main(int argc, char *argv[])
{
    string tempArr[5];
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    string line;
    int length=0;
    ifstream fileI;
    ofstream fileO;
    studentData students[10];
    fileI.open(argv[1]);
    while(getline(fileI,line))
    {
        split(line,',',tempArr,5);
        studentName=tempArr[0];
        homework=stoi(tempArr[1]);
        recitation=stoi(tempArr[2]);
        quiz=stoi(tempArr[3]);
        exam=stoi(tempArr[4]);
        addStudentData(students,studentName,homework,recitation,quiz,exam,length);
        length++;
    }
    fileI.close();
    printList(students, length);
    fileO.open(argv[2]);
    double upper, lower;
    if(*argv[4]=='A')
    {
        upper=100;
    }
    else if(*argv[4]=='B')
    {
        upper=90;
    }
    else if(*argv[4]=='C')
    {
        upper=80;
    }
    else if(*argv[4]=='D')
    {
        upper =70;
    }
    else if(*argv[4]=='F')
    {
        upper=60;
    }

    if(*argv[3]=='A')
    {
        lower=90;
    }
    else if(*argv[3]=='B')
    {
        lower=80;
    }
    else if(*argv[3]=='C')
    {
        lower=70;
    }
    else if(*argv[3]=='D')
    {
        lower =60;
    }
    else if(*argv[3]=='F')
    {
        lower=0;
    }

    for(int i=0;i<length;i++)
    {
        if(students[i].average>=lower&&students[i].average<upper)
        {
            fileO<<students[i].studentName<<","<<students[i].average<<","<<calcLetter(students[i].average)<<endl;
        }
    }
    fileO.close();
    return 0;
}