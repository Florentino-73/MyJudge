#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    //make final judge
    int n = 8; //num of OJ cpp
    int size = 10*10; //size of output
    string oj_name[9] = {"", "48762087.cpp", "84822638.cpp", "84822639.cpp", "101036360.cpp", 
                        "117364748.cpp", "127473352.cpp", "134841308.cpp", "173077807.cpp"};

    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            string s1 = "output"+to_string(i)+".txt";
            string s2 = "output"+to_string(j)+".txt";
            fstream in_file1(s1,ios::in);
            fstream in_file2(s2,ios::in);
            if(in_file1.is_open() && in_file2.is_open())
            {
                // make judgement
                bool judge = true;
                for(int row=1;row<size;row++)
                {
                    string str1, str2;
                    getline(in_file1,str1);
                    getline(in_file2,str2);
                    if(str1 != str2)
                    {
                        judge = false;
                        break;
                    }
                }

                //show the judge result
                if(judge)
                {
                    cout << "oj" << i << " is equal with oj " << j << endl;
                    fstream out_file("../../output/equal.csv",ios::app);
                    out_file << "input/4A/" << oj_name[i] << ",";
                    out_file << "input/4A/" << oj_name[j] << endl;
                }
                else
                {
                    cout << "oj" << i << " is not equal with oj " << j << endl;
                    fstream out_file("../../output/inequal.csv",ios::app);
                    out_file << "input/4A/" << oj_name[i] << ",";
                    out_file << "input/4A/" << oj_name[j] << endl;
                }
            }
        }
    }
    return 0;
}