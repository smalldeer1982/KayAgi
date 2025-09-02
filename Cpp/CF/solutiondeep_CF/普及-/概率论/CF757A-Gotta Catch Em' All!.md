# 题目信息

# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur
```

### 输出

```
1
```

## 样例 #2

### 输入

```
F
```

### 输出

```
0
```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
### 必须抓住它们！

#### 题目描述
巴什（Bash）有一天想成为一名宝可梦大师。虽然他喜欢很多宝可梦，但他一直对妙蛙种子（Bulbasaur）最为着迷。很快，事情开始变得严肃起来，他的迷恋变成了一种痴迷。由于他年纪太小，不能出去捕捉妙蛙种子，他想出了自己捕捉妙蛙种子的方式。

每天，他都会拿报纸的头版。他从报纸头版的任何地方一次剪下一个字母，组成“Bulbasaur”这个单词（不带引号），然后把它贴在墙上。巴什对大小写非常讲究——“Bulbasaur”的第一个字母必须是大写，其余字母必须是小写。通过这样做，他认为自己捕捉到了一只妙蛙种子。然后他在剩余的报纸部分重复这个步骤。他一直这样做，直到无法再从报纸上组成“Bulbasaur”这个单词为止。

给定报纸头版的文本，你能告诉他今天会捕捉到多少只妙蛙种子吗？

#### 说明/提示
在第一个样例中，你可以选取：Bulbbasaur。

在第二个样例中，没有办法组成哪怕一个“Bulbasaur”。

在第三个样例中，你可以重新排列字符串为 BulbasaurBulbasauraddrgndgddgargndbb，从而得到两个“Bulbasaur”单词。

#### 样例 #1
##### 输入
```
Bulbbasaur
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
F
```
##### 输出
```
0
```

#### 样例 #3
##### 输入
```
aBddulbasaurrgndgbualdBdsagaurrgndbb
```
##### 输出
```
2
```

### 综合分析与结论
这些题解的核心思路都是先统计输入字符串中组成“Bulbasaur”所需各个字母的数量，再考虑字母 'a' 和 'u' 出现两次的情况进行处理，最后找出数量最少的字母对应的个数，即为能组成“Bulbasaur”的最大数量。

- **算法要点**：
    - 字母计数：使用数组、`map` 等数据结构统计每个字母的出现次数。
    - 重复字母处理：对 'a' 和 'u' 的计数除以 2。
    - 木桶原理：最终结果取决于数量最少的字母。
- **解决难点**：
    - 大小写区分：不同题解通过不同方式处理大小写，如单独统计大写 'B'。
    - 重复字母：对 'a' 和 'u' 进行特殊处理，保证其数量能正确匹配。

### 评分较高的题解
- **外太空（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了题目背景和解题思路，注释丰富，适合新手。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std; 
int B,s,r,a,b,l,u;
int main()
{
    string st;
    cin>>st;
    int n=st.length();
    for(int i=0;i<n;i++)
    {
        if(st[i]=='B') B++;
        if(st[i]=='u') u++;
        if(st[i]=='l') l++;
        if(st[i]=='b') b++;
        if(st[i]=='a') a++;
        if(st[i]=='s') s++;
        if(st[i]=='r') r++;
    }
    a/=2;
    u/=2;
    cout<<min(min(B,min(u,l)),min(min(b,a),min(s,r)));
} 
```
- **pigstd（4星）**
    - **关键亮点**：使用数组存储字母出现次数，逻辑清晰，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char b[]={"Bulbasr"};
int a[20];
char s[100010];
int main()
{
    cin>>s;
    int len=strlen(s);
    int lenb=strlen(b);
    for (int i=0;i<len;i++)
    {
        char ch=s[i];
        for (int j=0;j<lenb;j++)
            if (b[j]==ch)
                a[j]++;
    }
    a[4]/=2;
    a[1]/=2;
    int minn=999999;
    for (int i=0;i<lenb;i++)
        minn=min(minn,a[i]);
    cout<<minn;
    return 0;
}
```
- **moqizhu2005（4星）**
    - **关键亮点**：使用 `map` 存储字母出现次数，代码简洁，体现了 `map` 的便捷性。
    - **核心代码**：
```cpp
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
string a;
map<char,int> m;
char c[10]="Bulbasr";
int ans=999999;
int main()
{
    cin>>a;
    for(int i=0;i<a.length();i++)
        m[a[i]]++;
    m['u']/=2,m['a']/=2;
    for(int i=0;i<7;i++)
        ans=min(ans,m[c[i]]);
    cout<<ans;
    return 0;
}
```

### 最优关键思路或技巧
- 使用数组或 `map` 统计字母出现次数，简化计数过程。
- 利用木桶原理，通过找出数量最少的字母确定最终结果。
- 对重复字母 'a' 和 'u' 的计数除以 2，确保正确匹配。

### 可拓展之处
同类型题目可能会改变目标单词，或增加更多复杂的条件，如区分更多大小写、处理更多重复字母等。解题思路依然是统计字母数量并找出限制因素。

### 洛谷相似题目推荐
- P1055 [NOIP2008 普及组] ISBN 号码
- P1308 [NOIP2011 普及组] 统计单词数
- P1597 语句解析

### 个人心得摘录与总结
- **Hanson水题大佬**：在 `if` 后面误加了分号，导致程序出错，后被大佬发现。总结是编码时要仔细，避免这种低级错误。
- **_Cloud_**：表示自己的码风奇怪，提醒大家注意代码风格的规范性。 

---
处理用时：34.91秒