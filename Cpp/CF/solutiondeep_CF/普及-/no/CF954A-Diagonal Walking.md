# 题目信息

# Diagonal Walking

## 题目描述

Mikhail walks on a 2D plane. He can go either up or right. You are given a sequence of Mikhail's moves. He thinks that this sequence is too long and he wants to make it as short as possible.

In the given sequence moving up is described by character U and moving right is described by character R. Mikhail can replace any pair of consecutive moves RU or UR with a diagonal move (described as character D). After that, he can go on and do some other replacements, until there is no pair of consecutive moves RU or UR left.

Your problem is to print the minimum possible length of the sequence of moves after the replacements.

## 说明/提示

In the first test the shortened sequence of moves may be DUD (its length is $ 3 $ ).

In the second test the shortened sequence of moves can be UUDRRRDUDDUUU (its length is $ 13 $ ).

## 样例 #1

### 输入

```
5
RUURU
```

### 输出

```
3
```

## 样例 #2

### 输入

```
17
UUURRRRRUUURURUUU
```

### 输出

```
13
```

# AI分析结果

### 题目翻译
米哈伊尔在一个二维平面上行走。他可以向上或向右移动。给定米哈伊尔的一系列移动。他认为这个序列太长了，想让它尽可能短。

在给定的序列中，向上移动用字符 U 表示，向右移动用字符 R 表示。米哈伊尔可以用对角线移动（用字符 D 表示）替换任意一对连续的移动 RU 或 UR。之后，他可以继续进行其他替换，直到没有连续的 RU 或 UR 对为止。

你的任务是打印替换后移动序列的最小可能长度。

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是遍历给定的移动序列，找出相邻的 RU 或 UR 对并将其替换为 D，从而计算出替换后序列的最小长度。不同题解在实现细节上有所差异，主要体现在如何避免重复替换上。部分题解使用标记数组，部分题解直接跳过已处理的字符。

### 所选题解
- **applese（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过指针移动来避免重复处理，易于理解。
    - **重点代码**：
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,i;
string st;
int main()
{
    cin>>n;
    cin>>st;
    int sum=n;
    while(i!=n)
    {
        if(st[i]=='R'&&st[i+1]=='U'||st[i]=='U'&&st[i+1]=='R')
        {
            i+=2;
            sum--;
        }
        else
            i++;
    }
    cout<<sum;
    return 0;
}
```
**核心实现思想**：遍历字符串，当遇到 RU 或 UR 对时，指针直接向后移动两位，同时总长度减 1，否则指针向后移动一位。

- **LJY_ljy（4星）**
    - **关键亮点**：使用标记数组避免重复计算，解释详细，对新手友好。
    - **重点代码**：
```cpp
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 110;
bool flag[MAXN];
int n, ans;
string str;

int main() {
    cin >> n;
    getline(cin, str);
    getline(cin, str);
    ans = n;
    for (int i = 0; i < str.size() - 1; i++) {
        if (str[i] != str[i + 1] && !flag[i] && !flag[i + 1]) {
            ans--;
            flag[i] = flag[i + 1] = true;
        }
    }
    printf("%d\n", ans);
    return 0;
} 
```
**核心实现思想**：遍历字符串，当遇到相邻字符不同且未被标记时，总长度减 1，并标记这两个字符已被处理。

- **恨穹不是妹（4星）**
    - **关键亮点**：将匹配过的字符置为空格避免重复匹配，思路简单直接。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000010];
int main()
{
    int n,count=0;
    cin>>n;
    cin>>a+1;
    for(int i=1;i<=n;i++)
    {
        if((a[i]=='U'&&a[i+1]=='R')||(a[i]=='R'&&a[i+1]=='U'))
        {
            count++;
            a[i]=' ';
            a[i+1]=' ';
        }
    }
    cout<<n-count;
}
```
**核心实现思想**：遍历字符串，当遇到 RU 或 UR 对时，计数器加 1，并将这两个字符置为空格，最后用总长度减去计数器的值。

### 最优关键思路或技巧
- 遍历字符串时，遇到可替换的 RU 或 UR 对，直接跳过这两个字符，避免重复处理。
- 使用标记数组记录已处理的字符，防止重复计算。

### 拓展思路
同类型题目可能会有更多的移动方向和替换规则，解题思路仍然是遍历序列，根据规则进行替换和计算。类似的算法套路包括字符串处理、模拟操作等。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
- [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

### 个人心得摘录与总结
- **恨穹不是妹**：提到在不爆空间的基础上尽量多开数组，这是因为在处理字符串时，可能会遇到较长的输入，足够大的数组可以避免越界问题。
- **LJY_ljy**：通过具体例子说明了使用标记数组的必要性，避免了重复计算导致的错误结果。

---
处理用时：30.56秒