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

### 题目内容（已为中文，无需重写）
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB"，再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)。
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"。
现在给出转变后的字符串，求出原来的字符串。

### 综合分析与结论
这些题解的核心思路都是对输入字符串进行处理，将其中的 "WUB" 去除，并在合适的位置添加空格以还原原字符串。各题解的主要区别在于处理 "WUB" 和空格的具体方式。

#### 思路对比
- **遍历替换法**：多数题解采用遍历字符串，当遇到 "WUB" 时进行跳过或替换操作，如封禁用户、happybob、Hu_Tao、liuyifan、Eason_AC、_Legacy、灵光一闪的题解。
- **查找替换法**：使用 `string` 类的 `find` 和 `replace` 函数进行查找和替换，如 Argon_Cube、SIXIANG32 的题解。

#### 算法要点
- **去除 "WUB"**：通过判断连续三个字符是否为 "WUB" 来跳过或替换。
- **处理空格**：避免出现多余空格，保证单词间只有一个空格。

#### 解决难点
- **多余空格问题**：不同题解采用不同方法处理，如标记法、判断上一个字符是否为空格等。
- **开头和结尾空格问题**：部分题解通过特殊处理或利用评测机制忽略。

### 题解评分与选择
- **封禁用户（5星）**：思路清晰，代码简洁，通过标记法有效处理空格问题。
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
核心实现思想：先将字符串中的 "WUB" 替换为空格，再通过标记 `flag` 控制空格输出，保证单词间只有一个空格。

- **Hu_Tao（4星）**：详细分析问题，代码逻辑清晰，通过 `substr` 函数判断 "WUB" 并处理空格。
```cpp
string s;
string ans;
int main(int argc, char const *argv[])
{
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
核心实现思想：遍历字符串，遇到 "WUB" 则跳过，否则将字符添加到结果字符串 `ans` 中，若下一个是 "WUB" 则添加空格。

- **Argon_Cube（4星）**：利用 `string` 类的 `find` 方法查找 "WUB" 并替换为空格，通过 `last` 字符变量处理多余空格。
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
核心实现思想：不断查找 "WUB" 并替换为空格，遍历字符串时，通过 `last` 变量判断是否输出空格，避免多余空格。

### 最优关键思路或技巧
- **标记法**：通过标记变量控制空格输出，避免多余空格，如封禁用户的题解。
- **`string` 类方法**：利用 `find`、`substr`、`replace` 等方法简化字符串处理，如 Argon_Cube、Hu_Tao 的题解。

### 可拓展之处
同类型题可能涉及更复杂的字符串替换和处理，如替换不同长度的子串、处理大小写敏感等。类似算法套路包括遍历字符串、使用标记变量、利用字符串库函数等。

### 推荐洛谷题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1553 数字反转（升级版）](https://www.luogu.com.cn/problem/P1553)

### 个人心得摘录与总结
- **封禁用户**：表示这是一道简单的字符串模拟题，强调了处理空格的重要性。
- **Hu_Tao**：详细分析了模拟过程中需要解决的问题，如找 "WUB"、跳过空格、处理多余空格等。
- **灵光一闪**：指出本题的难点在于处理前面的空格，并提出直接将循环变量加到不是空格处的解决方法。 

---
处理用时：31.75秒