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
## [ABC029B] 柿子

### 题目描述
[problemUrl]: https://atcoder.jp/contests/abc029/tasks/abc029_b

输入由小写英文字母组成的 12 个字符串 $ S_1 $, $ S_2 $,..., $ S_{12} $。
请统计这些字符串中包含字符 `r` 的字符串的个数。

### 说明/提示
#### 示例解释 1
$ S_1 $, $ S_2 $, $ S_3 $, $ S_4 $, $ S_9 $, $ S_{10} $, $ S_{11} $, $ S_{12} $ 这 8 个字符串中包含字符 `r`。$ S_2 $ 中 `r` 出现了 2 次，但只统计一次。

### 样例 #1
#### 输入
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
december
```
#### 输出
```
8
```

### 样例 #2
#### 输入
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
ssrrrrrrrr
```
#### 输出
```
11
```

### 综合分析与结论
这些题解的核心思路都是统计 12 个输入字符串中包含字符 `r` 的字符串个数，不过采用了不同的方法：
- **字符串查找函数法**：利用 `find()`、`pos()` 等函数查找字符 `r` 是否存在于字符串中，若存在则计数加 1。
- **正则表达式法**：使用正则表达式匹配包含字符 `r` 的字符串，匹配成功则计数加 1。
- **遍历法**：逐个遍历字符串中的字符，若找到字符 `r` 则计数加 1 并跳出当前字符串的遍历。
- **递归法**：通过递归的方式处理每个字符串，若找到字符 `r` 则计数加 1 并终止递归。

### 高评分题解
- **hjxxcbq（5星）**
    - **关键亮点**：思路清晰，使用 `find()` 函数简洁地解决问题，同时分享了调试过程中的错误及修正方法，对初学者有很大帮助。
    - **个人心得**：一开始未注意换行导致 WA，提醒大家注意 AT 题输出要换行。
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
    - **关键亮点**：详细介绍了 `string` 库中 `find()` 函数的使用方法，代码简洁易懂。
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
    - **关键亮点**：采用最基础的遍历方法，代码逻辑清晰，容易理解，适合初学者。
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
使用 `string` 类的 `find()` 函数可以简洁高效地判断字符串中是否包含指定字符，避免了手动遍历字符串的繁琐。

### 拓展思路
同类型题目可能会要求统计包含多个字符或子串的字符串个数，或者对输入字符串的数量和长度有不同的限制。类似算法套路可以使用字符串查找函数、正则表达式或遍历字符串等方法。

### 洛谷相似题目推荐
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1597 语句解析](https://www.luogu.com.cn/problem/P1597)
3. [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603)

### 个人心得摘录与总结
- **hjxxcbq**：一开始未注意 AT 题输出要换行导致 WA，提醒大家在做题时要注意输出格式。
- **xxxjz**：搜索时要设置好退出条件，否则可能会导致 TLE。 

---
处理用时：29.17秒