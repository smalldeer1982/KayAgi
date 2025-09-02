# 题目信息

# [ABC039C] ピアニスト高橋君

## 题目描述

题意描述
高桥君在一个钢琴键上，向右转，查看了20个键的颜色，问他所在的键是哪个？（钢琴键重复着白黑白黑白白黑白黑白黑白，音阶是 Do，#Do，Re，#Re，Mi，Fa，#Fa，So，#So，La，#La,Si）

## 样例 #1

### 输入

```
WBWBWWBWBWBWWBWBWWBW```

### 输出

```
Do```

# AI分析结果

### 题目翻译
【题目内容】
# [ABC039C] 钢琴家高桥君

## 题目描述
高桥君站在钢琴的一个琴键上，他向右转，查看了右边 20 个琴键的颜色，要求根据这 20 个琴键的颜色判断他所在的琴键对应的音阶是什么。（钢琴键的颜色排列是按照“白黑白黑白白黑白黑白黑白”的规律循环，对应的音阶依次是 Do，#Do，Re，#Re，Mi，Fa，#Fa，So，#So，La，#La，Si）

## 样例 #1
### 输入
```
WBWBWWBWBWBWWBWBWWBW
```
### 输出
```
Do
```

### 题解综合分析与结论
这些题解的核心思路都是利用钢琴键 12 个为一个周期的规律，通过打表的方式解决问题。具体做法是将 12 种可能的琴键颜色组合与对应的音阶进行关联，然后将输入的 20 个字符截取前 12 个与表中的情况进行比对，输出匹配的音阶。

各题解的算法要点主要包括输入处理、制表、查找匹配和输出结果。在解决难点上，都着重处理了如何准确制表以及高效查找匹配的问题。部分题解还提到了输入方式的注意事项，如避免使用 `scanf` 读取 `string` 类型的数据。

### 评分较高的题解
1. **作者：JimmyF（5星）**
    - **关键亮点**：思路清晰，将解题过程分为输入、制表、查找、输出 4 个步骤，代码结构良好，可读性高。通过数组存储所有情况，便于查找和维护。
    - **核心代码**：
```cpp
#include <bits/stdc++.h> 
using namespace std;
string st,st2;    
string st3[13]= 
{
    {""},
    {"WBWBWWBWBWBW"},
    {"BWBWWBWBWBWW"},
    {"WBWWBWBWBWWB"},
    {"BWWBWBWBWWBW"},
    {"WWBWBWBWWBWB"},
    {"WBWBWBWWBWBW"},
    {"BWBWBWWBWBWW"},
    {"WBWBWWBWBWWB"},
    {"BWBWWBWBWWBW"},
    {"WBWWBWBWWBWB"},
    {"BWWBWBWWBWBW"},
    {"WWBWBWWBWBWB"},
};
string st1[25]={"1","Do","#Do","Re","#Re","Mi","Fa","#Fa","So","#So","La","#La","Si"}; 
int main()
{
    cin>>st;  
    for(int i=0; i<=11; i++)
        st2+=st[i]; 
    for(int i=1; i<=12; i++)
        if(st3[i]==st2){cout<<st1[i]<<endl;return 0;} 
    return 0;
}
```
核心实现思想：先输入字符串，截取前 12 位，然后遍历存储琴键颜色组合的数组，找到匹配的情况后输出对应的音阶。

2. **作者：Cheese_int（4星）**
    - **关键亮点**：详细强调了输入方式的注意事项，避免了可能出现的错误。通过表格清晰列出所有情况，代码虽然使用多个 `if` 语句，但逻辑简单直接。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;	
int main () {
    cin >> s;
    if (s.substr (0, 12) == "WBWBWWBWBWBW")	printf ("Do");	
    if (s.substr (0, 12) == "BWBWWBWBWBWW")	printf ("#Do");
    if (s.substr (0, 12) == "WBWWBWBWBWWB")	printf ("Re");
    if (s.substr (0, 12) == "BWWBWBWBWWBW")	printf ("#Re");
    if (s.substr (0, 12) == "WWBWBWBWWBWB")	printf ("Mi");
    if (s.substr (0, 12) == "WBWBWBWWBWBW")	printf ("Fa");
    if (s.substr (0, 12) == "BWBWBWWBWBWW")	printf ("#Fa");
    if (s.substr (0, 12) == "WBWBWWBWBWWB")	printf ("So");
    if (s.substr (0, 12) == "BWBWWBWBWWBW")	printf ("#So");
    if (s.substr (0, 12) == "WBWWBWBWWBWB")	printf ("La");
    if (s.substr (0, 12) == "BWWBWBWWBWBW")	printf ("#La");
    if (s.substr (0, 12) == "WWBWBWWBWBWB")	printf ("Si");	
    return 0;
}
```
核心实现思想：输入字符串后，通过 `substr` 截取前 12 位，使用多个 `if` 语句逐一判断是否与预定义的情况匹配，匹配则输出对应的音阶。

3. **作者：makerlife（4星）**
    - **关键亮点**：代码结构清晰，通过数组存储琴键颜色组合和对应的音阶，便于查找和管理。逻辑明确，易于理解。
    - **核心代码**：
```cpp
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
string s,str;
string s1[20]={"","WBWBWWBWBWBW","BWBWWBWBWBWW","WBWWBWBWBWWB","BWWBWBWBWWBW","WWBWBWBWWBWB","WBWBWBWWBWBW","BWBWBWWBWBWW","WBWBWWBWBWWB","BWBWWBWBWWBW","WBWWBWBWWBWB","BWWBWBWWBWBW","WWBWBWWBWBWB"};
string s2[20]={"","Do","#Do","Re","#Re","Mi","Fa","#Fa","So","#So","La","#La","Si"};
int main()
{
    cin>>s;
    for(int i=0;i<=11;i++)
    {
        str+=s[i];
    }
    for(int i=1;i<=12;i++)
    {
        if(str==s1[i])
        {
            cout<<s2[i]<<endl;
            return 0;
        }
    }
    return 0;
}
```
核心实现思想：输入字符串后，截取前 12 位，遍历存储琴键颜色组合的数组，找到匹配的情况后输出对应的音阶。

### 最优关键思路或技巧
- 利用钢琴键 12 个为一个周期的规律，只截取输入字符串的前 12 位进行处理，减少不必要的计算。
- 采用打表的方式，将所有可能的情况存储在数组中，便于查找和匹配。

### 可拓展之处
同类型题可能会有不同的周期规律或更多的状态组合，解题思路仍然可以采用打表法，先找出周期规律，然后列出所有可能的情况进行匹配。类似的算法套路还可以应用于密码匹配、状态判断等问题。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察对周期规律和区间处理的理解。
2. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：涉及数组的使用和简单的模拟。
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要对二维空间进行模拟和判断。

### 个人心得摘录与总结
- **Cheese_int**：提醒在 AT 题库里不要打多余的换行，使用 `scanf` 读入 `string` 类型的数据会报错，考试中读入字符串尽量用 `cin`，避免出现 RE 错误。总结：在竞赛中要注意输入输出的规范和不同输入方式的适用情况。

---
处理用时：49.74秒