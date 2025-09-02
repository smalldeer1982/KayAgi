# 题目信息

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 样例 #1

### 输入

```
WUBWUBABCWUB
```

### 输出

```
ABC ```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB
```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND ```

# AI分析结果

### 题解综合分析与结论
这些题解核心思路都是对输入字符串进行处理，将其中的 "WUB" 去除，并保证单词间仅有一个空格。各题解的主要差异在于处理 "WUB" 和空格的具体方式。
- **算法要点对比**
    - 部分题解（如封禁用户、Argon_Cube、灵光一闪）是先将 "WUB" 替换为空格，再处理多余空格。
    - 部分题解（如 happybob、Hu_Tao、liuyifan、Eason_AC、_Legacy）是在遍历过程中直接跳过 "WUB"，并适时添加空格。
    - SIXIANG32 的题解使用 `find` 和 `replace` 函数将 "WUB" 替换为三个空格，再构造目标字符串。
- **难点解决对比**
    - 处理多余空格是各题解都需解决的难点。有的通过标记（如封禁用户、_Legacy），有的通过判断上一个字符（如 Argon_Cube）来避免多余空格。
    - 对于开头空格，灵光一闪的题解通过直接跳过行首空格来处理。

### 所选题解
- **封禁用户（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂。先将 "WUB" 替换为空格，再通过标记保证单词间仅有一个空格。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s;
bool flag=true;
int main()
{
    cin>>s;
    for(int i=2;i<s.length();++i)
        if(s[i]=='B'&&s[i-1]=='U'&&s[i-2]=='W')
            s[i]=s[i-1]=s[i-2]=' ';
    for(int i=0;i<s.length();++i)
    {
        if(s[i]!=' ')
            flag=false;
        if(!flag)
            cout<<s[i];
        if(s[i]==' ')
            flag=true;
    }
    return 0;
}
```
- **Hu_Tao（4星）**
    - **关键亮点**：详细分析了模拟过程中需要解决的问题，代码注释清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
string s;
string ans;
int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin>>s;
    for(int i=0;i<s.size();)
    {
        if(i+2<s.size()&&s.substr(i,3)=="WUB")
        {
            i+=3;
            continue;
        }
        ans+=s[i];
        i++;
        if(i+2<s.size()&&s.substr(i,3)=="WUB")ans+=' ';
    }
    cout<<ans;
    return 0;
}
```
- **Argon_Cube（4星）**
    - **关键亮点**：使用 `string` 类的 `find` 方法查找 "WUB"，并通过记录上一个字符避免多余空格。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int main(int argc,char *argv[],char *env[])
{
    string org;
    unsigned long long pos;
    cin>>org;
    while((pos=org.find("WUB"))!=string::npos)
        org[pos]=org[pos+1]=org[pos+2]=' ';
    char last=' ';
    for(char tmp:org)
    {
        if(tmp==' ')
        {
            if(last!=' ')
                cout<<' ';
        }
        else
            cout<<tmp;
        last=tmp;
    }
    return 0;
}
```

### 最优关键思路与技巧
- 可以先将 "WUB" 替换为空格，再通过标记或判断上一个字符来处理多余空格，使代码逻辑更清晰。
- 使用 `string` 类的 `find` 方法可以方便地查找子字符串。

### 拓展思路
同类型题可能会涉及对字符串的其他替换、删除、插入操作，或者对处理后的字符串进行进一步的分析。类似算法套路包括先对字符串进行预处理，再根据条件进行筛选和输出。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码
- P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here
- P1308 [NOIP2011 普及组] 统计单词数

### 个人心得摘录与总结
- **封禁用户**：提到“我又来水CF了……”，体现出轻松的做题心态。
- **Hu_Tao**：详细分析了模拟过程中可能遇到的问题，如加空格会导致多个空格的情况，通过具体例子说明，有助于理解。
- **灵光一闪**：指出本题难点在于处理前面的空格，并给出了解决方法。 

---
处理用时：29.93秒