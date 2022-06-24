#include <iostream>
#include <fstream>
using namespace std;
int addToArrayAsc(float sortedArray[], int numElements, float newValue);

int main(int argc, char *argv[])
{
    ifstream file;
    int numElements=0;
    file.open(argv[1]);
    if(file.fail())
    {
        cout<<"Failed to open the file."<<endl;
        return 0;
    }
    string line;
    float newVal;
    float sortedArray[100];
    while(getline(file,line))
    {
        newVal=stof(line);
        addToArrayAsc(sortedArray,numElements,newVal);
        numElements++;
    }
    return 0;
}

int addToArrayAsc(float sortedArray[], int numElements, float newValue)
{
    float tempVal;
    sortedArray[numElements]=newValue;
    numElements++;
    for(int i=0;i<numElements;i++)
    {
        for(int j=0;j<numElements-i-1;j++)
        {
            if(sortedArray[j]>sortedArray[j+1])
            {
                tempVal=sortedArray[j+1];
                sortedArray[j+1]=sortedArray[j];
                sortedArray[j]=tempVal;
            }
        }
    }

    for(int i=0;i<numElements;i++)
    {
        {
            if(i==numElements-1)
            {
                cout<<sortedArray[i]<<endl;
            }
            else
            {
                cout<<sortedArray[i]<<",";
            }
        }
    }
    return numElements+1;
}
