# 题目信息

# [USACO1.2] 命名那个数字 Name That Number

## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。


## 样例 #1

### 输入

```
4734
NMSL
GREG
LSDC
....(太多了不写了)```

### 输出

```
GREG
```

# AI分析结果

• 综合分析与结论：
    - 思路方面，多数题解采用将字母翻译为数字后与给定编号对比的方法。少数题解使用DFS、BFS等搜索算法生成可能名字再匹配，或用哈希表、字典树优化查找。
    - 算法要点：主要涉及字符串处理、数组或映射的使用来存储字母与数字对应关系，以及循环遍历、条件判断等操作。
    - 解决难点：输入格式较坑，需正确读取编号和字典；数据量虽不大，但要考虑优化以避免超时，如剪枝操作。
    - 整体来看，多数题解思路清晰，但部分代码可读性欠佳，一些复杂算法实现如哈希表、字典树未做详细注释。

• 所选的题解：
  - 作者：bjrjk （5星）
    - 关键亮点：代码简洁高效，利用`vector`存储字典，通过剪枝操作（对比字符串长度）减少不必要比较，整体思路清晰，代码可读性高。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> Dict; 
string str; 
const char * str_trans = "2223334445556667 77888999"; 
int main(){
    ios::sync_with_stdio(false); 
    cin >> str;
    string tmp;
    while (cin >> tmp){ 
        Dict.push_back(tmp);
    }
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){ 
        if (len!= Dict[i].length())continue; 
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A']!= str[j]){ 
                flag = false; 
                break;
            }
        }
        if (flag){ 
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag){ 
        cout << "NONE" << endl;
    }
}
```
核心思想是先读入编号和字典，遍历字典中每个名字，若长度与编号不同则跳过，相同则对比每个字母对应的数字是否与编号对应位置数字相同，若都相同则输出该名字，若无匹配则输出NONE。

  - 作者：玉环小姐姐 （4星）
    - 关键亮点：思路直接易懂，通过结构体存储名字及其对应的数字串，方便后续比对。代码逻辑清晰，适合初学者理解。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct a{
    string old,new1;
}q[5100];
int main()
{
    string n,n_new="";
    cin>>n;
    for(int i=1;i<=4617;i++)
    {
        cin>>q[i].old;
    }
    for(int i=1;i<4617;i++)
    { 
        q[i].new1="";
        for(int j=0;j<q[i].old.size();j++)
        {
            if(q[i].old[j]=='A'||q[i].old[j]=='B'||q[i].old[j]=='C')
            {
                q[i].new1+='2';
            }
            if(q[i].old[j]=='D'||q[i].old[j]=='E'||q[i].old[j]=='F')
            {
                q[i].new1+='3';
            }
            if(q[i].old[j]=='H'||q[i].old[j]=='G'||q[i].old[j]=='I')
            {
                q[i].new1+='4';
            }
            if(q[i].old[j]=='J'||q[i].old[j]=='K'||q[i].old[j]=='L')
            {
                q[i].new1+='5';
            }
            if(q[i].old[j]=='M'||q[i].old[j]=='N'||q[i].old[j]=='O')
            {
                q[i].new1+='6';
            }
            if(q[i].old[j]=='P'||q[i].old[j]=='S'||q[i].old[j]=='R')
            {
                q[i].new1+='7';
            }
            if(q[i].old[j]=='T'||q[i].old[j]=='V'||q[i].old[j]=='U')
            {
                q[i].new1+='8';
            }
            if(q[i].old[j]=='X'||q[i].old[j]=='W'||q[i].old[j]=='Y')
            {
                q[i].new1+='9';
            }
        }
    }
    bool p=true;
    for(int i=1;i<=4617;i++)
    {
        if(q[i].new1==n)
        {
            cout<<q[i].old<<endl;
            p=false;
        }
    }
    if(p)
    {
        cout<<"NONE";
    }
    return 0;
}
```
核心思想是先读入编号和所有名字，将每个名字转换为对应的数字串存储在结构体中，最后遍历结构体，对比数字串与输入编号，若相同则输出名字，若无匹配则输出NONE。

  - 作者：cellur925 （4星）
    - 关键亮点：使用`map`建立字母与数字的映射关系，代码简洁明了，逻辑清晰，能较好地解决字母到数字的转换问题。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<iostream>
using namespace std;
int cnt,len;
char num[20];
char word[1000];
map<char,int>m;
void init()
{
    m['A']=2;m['B']=2;m['C']=2;
    m['D']=3;m['E']=3;m['F']=3;
    m['G']=4;m['H']=4;m['I']=4;
    m['J']=5;m['K']=5;m['L']=5;
    m['M']=6;m['N']=6;m['O']=6;
    m['P']=7;m['R']=7;m['S']=7;
    m['T']=8;m['U']=8;m['V']=8;
    m['W']=9;m['Y']=9;m['Z']=9;
    m['Q']=0;m['Z']=0;
}
bool check()
{
    int lenw=strlen(word);
    if(lenw!=len) return 0;
    for(int i=0;i<len;i++)
        if(m[word[i]]!=(int)(num[i]-'0')) return 0;
    return 1;
}
int main()
{
    scanf("%s",num);
    len=strlen(num);
    init();
    while(scanf("%s",word)!=EOF)
    {
        if(check())
            printf("%s\n",word),cnt++;
    }
    if(!cnt)
        printf("NONE");
    return 0;
}
```
核心思想是先初始化`map`建立字母数字映射，读入编号后，每次读入一个名字，通过`check`函数对比名字长度及每个字母对应的数字与编号是否一致，若一致则输出名字，若无匹配则输出NONE。

• 最优关键思路或技巧：
    - **剪枝优化**：如bjrjk题解中，通过提前对比字符串长度，剪掉长度不同的字符串，减少不必要的字符对比操作，提高效率。
    - **合理数据结构**：使用`vector`存储字典方便遍历，`map`建立字母数字映射简洁高效，结构体存储名字及其对应数字串使逻辑更清晰。

• 可拓展之处：
同类型题可涉及更多复杂的字符与数字转换规则，或更大数据量下的优化问题。类似算法套路包括预处理数据建立映射关系，利用剪枝优化暴力枚举，以及使用合适数据结构存储和查找数据。

• 推荐洛谷题目：
    - P1036 [选数](https://www.luogu.com.cn/problem/P1036)：涉及枚举与剪枝技巧，与本题优化思路类似。
    - P1164 小A点菜：通过枚举和条件判断解决问题，锻炼字符串处理和逻辑判断能力。
    - P1909 买铅笔：同样是根据不同条件进行枚举和选择，与本题思路有相似之处。

• 个人心得摘录与总结：
    - **Kewth**：发现洛谷输入需将namenum.in和dict.txt按顺序放在标准输入，否则得分异常。总结为做题时要注意平台输入格式要求，仔细研究测试数据输入方式。 

---
处理用时：44.13秒