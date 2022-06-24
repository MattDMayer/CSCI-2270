#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct wordRecord
{
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordsFileName, string ignoreWords[])
{
    ifstream file;
    int index=0;
    file.open(ignoreWordsFileName);
    string line;
    while(file>>line)
    {
        ignoreWords[index]=line;
        index++;
    }
    file.close();
}

bool isIgnoreWord(string word, string ignoreWords[])
{
    for(int i=0;i<50;i++)
    {
        if(word==ignoreWords[i])
        {
            return 1;
        }
    }
    return 0;
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length)
{
    int sum=0;
    for(int i=0;i<length;i++)
    {
        sum+=distinctWords[i].count;
    }
    return sum;
}

void sortArray(wordRecord distinctWords[], int length)
{
    wordRecord tempVal;
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<length-i-1;j++)
        {
            if(distinctWords[j+1].count>distinctWords[j].count||(distinctWords[j+1].count==distinctWords[j].count&&(distinctWords[j+1].word.substr(0,1)<distinctWords[j].word.substr(0,1))))
            {
                tempVal=distinctWords[j+1];
                distinctWords[j+1]=distinctWords[j];
                distinctWords[j]=tempVal;
            }
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords)
{
    float prob;
    for(int i=0;i<10;i++)
    {
        prob=float(distinctWords[N+i].count)/totalNumWords;
        cout<<setprecision(5)<<fixed<<prob<<" - "<<distinctWords[N+i].word<<endl;
    }
}

int split(string toBeSplit, char splitPoint, string splitPieces[], int sizeOfSplitPieces)
{
    string looking;
    string splitPointConvert;
    splitPointConvert+=splitPoint;
    int finalLength=0;
    int placement, last=0;
    for(int i=0;i<toBeSplit.length()&&(sizeOfSplitPieces>placement);i++)
    {
        looking=toBeSplit.substr(i,1);
        if((looking==splitPointConvert))
        {
            splitPieces[placement]=toBeSplit.substr(last,i-last);
            placement++;
            last=i+1;
        }
        else if(i==toBeSplit.length()-1&&placement!=0)
        {
            for(int j=0;j<placement;j++)
            {
                finalLength+=splitPieces[j].length()+1;
            }
            if(placement<=sizeOfSplitPieces)
            {
                splitPieces[placement]=toBeSplit.substr(finalLength,toBeSplit.length()-(finalLength));
            }
        }
        else if(i==toBeSplit.length()-1&&placement==0)
        {
            splitPieces[placement]=toBeSplit;
        }
    }
    if(toBeSplit=="")
    {
        return 0;
    }
    else if(sizeOfSplitPieces<=placement)
    {
        return -1;
    }
    else
    {
        return placement+1;
    }
}

int isWordDistinct(string word, int length, wordRecord distinctWords[])
{
    for(int i=0;i<length;i++)
    {
        if(word==distinctWords[i].word)
        {
            return i;
        }
    }
    return-1;
}
int main(int argc, char *argv[])
{
    if(argc!= 4)
    {
        cout<<"Usage: Assignment2Solution <number of words><inputfilename.txt> <ignoreWordsfilename.txt>"<<endl;
        return 0;
    }
    string ignoreWords[50];
    ifstream file;
    getIgnoreWords(argv[3],ignoreWords);
    file.open(argv[2]);
    int width=100;
    wordRecord *wordArr = new wordRecord[width];
    string word;
    int doubled =0;
    int uniqueWords=0;
    while(file>>word)
    {
        if(uniqueWords==width)
        {
            wordRecord *tempArr = new wordRecord[width*2];
            for(int i=0;i<width;i++)
            {
                tempArr[i]=wordArr[i];
            }
            delete [] wordArr;
            wordArr=tempArr;
            doubled++;
            width=width*2;
        }
        if(isIgnoreWord(word, ignoreWords)==false)
        {
            if(isWordDistinct(word,uniqueWords,wordArr)==-1)
            {
                wordArr[uniqueWords].word=word;
                wordArr[uniqueWords].count++;
                uniqueWords++;
                
            }
            else
            {
                wordArr[isWordDistinct(word,uniqueWords,wordArr)].count++;
            }
        }
    }
    file.close();
    cout<<"Array doubled: "<<doubled<<endl;
    cout<<"Distinct non-common words: "<<uniqueWords<<endl;
    int totalWord=0;
    for(int i=0;i<uniqueWords;i++)
    {
        totalWord+=wordArr[i].count;
    }
    cout<<"Total non-common words: "<<totalWord<<endl;
    cout<<"Probability of next 10 words from rank "<<argv[1]<<endl;
    for(int i=0;i<39;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    sortArray(wordArr,uniqueWords);
    const string number = argv[1];
    int convert = stoi(number);
    printTenFromN(wordArr,convert,totalWord);
    return 0;
}