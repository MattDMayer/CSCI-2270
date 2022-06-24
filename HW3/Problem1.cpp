#include <iostream>
using namespace std;

bool append(string* &str_arr, string s, int &numEntries, int &arraySize)
{
    if(numEntries==arraySize)
    {
        string* temp= new string[arraySize*2];
        for(int i=0;i<arraySize;i++)
        {
            temp[i]=str_arr[i];
        }
        delete [] str_arr;
        str_arr=temp;
        str_arr[arraySize]=s;
        numEntries++;
        arraySize=arraySize*2;
        return true;
    }
    else
    {
        for(int i=0;i<arraySize;i++)
        {
            if(str_arr[i]=="")
            {
                str_arr[i]=s;
                numEntries++;
                return false;
            }
        }
    }
    //This is never hit but is there so it won't read as an error that a return can't be hit.
    return false;
}

int main()
{
    return 0;
}