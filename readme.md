# **MyJudge**

本实验为软件工程课程实验作业，目标是实现一个 **`OJ` 等价性判断工具**，即对于给定的一组 OJ 程序，使用该工具两两进行判断，将等价与不等价的程序对分别保存在 `out/equal.csv` 和 `out/inequal.csv` 中。

程序等价性的定义为：
- 函数的所有输入值都是随机生成的，且相互独立。
- 判断等价时两个函数的输入（或输出）个数可以不同，顺序也可以不同。
- 将输入和输出都看作【集合】的概念，比较两个函数在输入相同的时候，输出值的集合是不是呈现包含关系。若呈现包含关系，则二者等价，否则为不等价。
- 当输入个数不同时（例如一个为 `i`，一个为 `j`，且 `i < j`），输入相同即表示两个函数拥有相同的 `i` 个输入，且输入个数为 `j` 的那个函数会有额外的 `j-i` 个随机生成的输入。输入值也是集合的概念，两个函数中相同的变量名不一定具有相同的输入值。
- 另一种等价的情况是待判断的两个函数都遇到运行时错误或都陷入无限循环。

定义引自：https://seg.nju.edu.cn/curriculums/Software_Engineering_(Fall_2022)/lab1.html

以下为本次实验报告内容。

#
## **1. 实验进度**

- 实现了简易版的等价判断工具和等价确认工具；
- 学会使用 `git` 相关操作进行版本控制；
- 将项目上传至个人 `GitHub` 公开仓库；

#

## **2. 实验结果**

实现了简易等价判断工具，可以自动判断一组 `OJ` 程序中两两是否等价或不等价，并且将结果保存至对应的 `csv` 文件中。

<div align=center><img width = '400' height ='270' src = pic/result.png/></div>

#

## **3. 实验过程**

本实验工作环境为 `Ubuntu20.04` ，交互界面通过 `Linux Terminal` 实现，因此需要实现 `OJ` 等价判断的 `cpp` 文件及运行程序的 `makefile` 文件，接下来通过程序的运行顺序依次介绍。

### **3.0 程序执行思路**

为判断两个 `OJ` 程序是否等价，我们采用的思路是：

- 根据输入格式文件 `stdin_format.txt` 创建多组输入（保证涵盖所有可能的情况）；
- 为每个 `OJ` 程序编写脚本，运行脚本，将多组输入交给 `OJ` 程序多次执行，保存为输出文件；
- 执行判断程序，根据等价性定义对每个程序的输入进行两两比较，保存至对应的结果文件中。

基于此流程，编写的 `makefile` 文件如下：
```makefile
# makefile
input:
	@ touch input.txt
	@ g++ -g standard_input.cpp -o input
	@ ./input

output:
	@ g++ -g 21508887.cpp -o test1
	@ sudo ./out1.sh

	... # same as first oj file

judge:
	@ g++ -g myjudge.cpp -o myjudge
	@ ./myjudge

clean:
	@ rm -rf input
	@ rm -rf test*
	@ rm -rf myjudge

remove:
	@ rm -rf output*
```

其中 `input` , `output` , `judge`分别对应以上三个步骤，在下一节中会具体展示。

### **3.1 创建 `OJ` 输入**

首先根据 `stdin_format.txt` 文件格式创建输入文件，通过 `standard_input.cpp` 程序实现：
```cpp
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    //make standard input
    int a,b; // read from stdin_format.txt
    a = 1;
    b = 100;
    fstream file("input.txt",ios::app);
    if(file.is_open())
    {
        for(int i=a;i<=b;i++)
        {
            file << i << endl;
        }
        cout<<"make input success!"<<endl;
    }
}
```

运行**创建输入命令 `make input`**, 程序会执行并创建一个标准输入文件 `input.txt`, 执行过程如图：

<div align=center><img width = '400' height ='80' src = pic/input.png/></div>

此后我们调用得到的标准输入文件 `input.txt` 执行程序。


### **3.2 执行 `OJ` 程序**

首先我们为每个 `OJ` 程序编写对应脚本 `outi.sh`(在 `makefile` 文件中有所体现), 以第一组第一个OJ程序为例，编写的脚本如下：

```bash
# out1.sh
while read rows
do
  ./test1 $rows >> output1.txt
  echo >> output1.txt
done < input.txt
```

使用该脚本可以将标准输入文件 `input.txt` 中的每一行作为一次输入，执行一次 `OJ` 程序，并将结果保存至 `output1.txt` 中。循环次数为 `input.txt` 文件中的输入个数，循环执行完之后，该输出文件中将有若干次输出，完成了多次执行 `OJ` 程序获取输出的要求。

运行**创建输出命令 `make output`**, 可以生成所有 `OJ` 程序的输出文件：

<div align=center><img width = '500' height ='230' src = pic/output.png/></div>

此后我们使用得到的输出文件 `outputi.txt` 判断程序等价性。

### **3.3 判断等价性并保存结果**

有了每个 `OJ` 程序的输出文件后，我们只需要将每组的 `OJ` 程序的输出文件两两进行比较，若相同则将该 `OJ` 程序对记录在 `equal.csv` 文件中，否则记录在 `inequal.csv` 文件中，从而实现了等价性判断的要求。我们通过下面的代码实现这个步骤：
```cpp
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    //make final judge
    int n = 8; //num of OJ cpp
    int size = 10*10; //size of output
    string oj_name[n+1] = {/*all the oj name*/};

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
```

运行**判断程序等价性命令 `make judge`**, 可以两两比较组中的 `OJ` 程序是否相等，并将其记录在对应的 `csv` 文件中。

<div align=center><img width = '500' height ='250' src = pic/judge.png/></div>

至此，已经实现了简易的 `OJ` 等价性判断工具，最终结果在 `2.实验结果` 中。

#

## **4. 使用 `Git` 操作管理项目**

本项目依托 `git` 实现版本控制，部分 `git` 操作运行截图如下：


使用 `git init` 命令创建并初始化仓库：
<div align=center><img width = '500' height ='150' src = 'pic/git init.png'/></div>
 
使用 `git commit -m` 命令提交更新内容：
<div align=center><img width = '500' height ='250' src = 'pic/git commit.png'/></div>

使用 `git log` 等命令查看当前版本等：
<div align=center><img width = '500' height ='200' src = 'pic/git log.png'/></div>

#

## **5. 在 `Github` 上实现项目开源**

本项目现已在 `Github` 上开源。

公开仓库地址：
https://github.com/Florentino-73/MyJudge

#

## **6. 实验心得**
本次实验历时三周，实验重点在于对程序等价性的理解和学会自己从零开始搭建一个项目平台。

实验中遇到的最大挑战莫过于学习编写 `makefile` 运行程序，`makefile` 的语法较为繁多而复杂，本次实验中仅用到了一小部分。此外通过这次实验更加熟悉了 `git` 版本控制的相关操作，对于项目的修改及编写有很大的帮助。

最后感谢老师和助教提供的悉心指导的实验手册，希望之后的实验也可以一帆风顺！✌️
