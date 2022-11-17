#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    //make standard input
    int a,b; // from stdin_format.txt
    a = 1;
    b = 16;
    fstream file("input.txt",ios::app);
    if(file.is_open())
    {
        for(int i=a;i<=b;i++)
        {
            for(int j=a;j<=b;j++)
            {
               file << i << " " << j << endl; 
            }
        }
        cout<<"make input success!"<<endl;
    }
}