# 题目信息

# [ABC029B] カキ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc029/tasks/abc029_b

英小文字からなる $ 12 $ 個の文字列 $ S_1 $, $ S_2 $, ..., $ S_{12} $ が入力されます。  
これらの文字列のうち、文字 `r` が含まれるものの個数を数えてください。

## 说明/提示

### Sample Explanation 1

$ S_1 $, $ S_2 $, $ S_3 $, $ S_4 $, $ S_9 $, $ S_{10} $, $ S_{11} $, $ S_{12} $ の $ 8 $ 個の文字列に文字 `r` が含まれています。 $ S_2 $ には `r` が $ 2 $ 回出現していますが、一度しか数えません。

## 样例 #1

### 输入

```
january

february

march

april

may

june

july

august

september

october

november

december```

### 输出

```
8```

## 样例 #2

### 输入

```
rrrrrrrrrr

srrrrrrrrr

rsr

ssr

rrs

srsrrrrrr

rssrrrrrr

sss

rrr

srr

rsrrrrrrrr

ssrrrrrrrr```

### 输出

```
11```

# AI分析结果

### 题目翻译
英文字母组成的 12 个字符串 $ S_1 $, $ S_2 $, ..., $ S_{12} $ 会被输入。请统计这些字符串中包含字符 `r` 的字符串的个数。

### 综合分析与结论
这些题解的核心思路都是输入 12 个字符串，然后判断每个字符串中是否包含字符 `r`，包含则计数器加 1，最后输出计数器的值。但实现方式各有不同，主要分为以下几类：
1. **使用字符串查找函数**：利用 `find`、`pos`、`strstr` 等函数查找字符 `r` 是否存在。
2. **正则表达式**：使用正则表达式匹配包含字符 `r` 的字符串。
3. **暴力枚举**：遍历字符串的每个字符，判断是否为 `r`。
4. **递归**：通过递归的方式搜索字符串中是否包含字符 `r`。

### 所选题解
- **hjxxcbq（4星）**
    - **关键亮点**：思路清晰，使用 `find` 函数简洁地解决问题，并且指出了输出需要换行的坑点。
    - **个人心得**：一开始没注意输出要换行导致 WA，提醒大家注意 AT 题的输出格式。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int s;
int main()
{
    for(int i=0;i<12;i++)
    {
        cin>>a;
        if(a.find('r')!=-1)s++;
    }
    cout<<s<<endl;
    return 0;
}
```
- **Ophelia（4星）**
    - **关键亮点**：详细介绍了 `string` 库中 `find` 函数的使用方法，代码简洁易懂。
    - **核心代码**：
```cpp
#include<string>
#include<iostream>
using namespace std;
string s;
int sum;
int main()
{
    for(int i=1; i<=12; i++)
    {
        cin>>s;
        if(s.find('r',0)!=string::npos)
            sum++;
    }
    cout<<sum<<endl;
    return 0;
}
```
- **Xiamo_Azure（4星）**
    - **关键亮点**：通过双重循环遍历每个字符串的每个字符，思路直接，代码简单。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
string s[25];
int main()
{
    for(int i=1;i<=12;i++) cin>>s[i];
    for(int i=1;i<=12;i++){
        for(int j=0;j<s[i].size();j++)
            if(s[i][j]=='r') {
                ans++;
                break;
            }
    }
    cout<<ans<<"\n";
    return 0;
}
```

### 最优关键思路或技巧
使用 `string` 类的 `find` 函数可以简洁高效地判断字符串中是否包含某个字符，代码实现简单，可读性高。

### 可拓展之处
同类型题目可能会改变输入的字符串数量、查找的字符，或者要求统计不同字符的出现情况等。类似算法套路可以用于处理字符串匹配、查找子串等问题。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串的处理和字符匹配。
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：需要对字符串中的字符进行统计和处理。
3. [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：包含字符串的操作和字符计算。

### 个人心得总结
- hjxxcbq 提醒大家注意 AT 题的输出格式，输出要换行，否则会 WA。
- xxxjz 提到搜索时要有退出条件，否则会 TLE。

---
处理用时：26.22秒