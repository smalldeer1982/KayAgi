# 题目信息

# String Transformation

## 题目描述

You are given a string $ s $ consisting of $ |s| $ small english letters.

In one move you can replace any character of this string to the next character in alphabetical order (a will be replaced with b, s will be replaced with t, etc.). You cannot replace letter z with any other letter.

Your target is to make some number of moves (not necessary minimal) to get string abcdefghijklmnopqrstuvwxyz (english alphabet) as a subsequence. Subsequence of the string is the string that is obtained by deleting characters at some positions. You need to print the string that will be obtained from the given string and will be contain english alphabet as a subsequence or say that it is impossible.

## 样例 #1

### 输入

```
aacceeggiikkmmooqqssuuwwyy
```

### 输出

```
abcdefghijklmnopqrstuvwxyz
```

## 样例 #2

### 输入

```
thereisnoanswer
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 字符串转换

## 题目描述
给定一个由 $|s|$ 个小写英文字母组成的字符串 $s$。

在一次操作中，你可以将这个字符串中的任何一个字符替换为字母表中的下一个字符（a 会被替换为 b，s 会被替换为 t，以此类推）。你不能将字母 z 替换为其他任何字母。

你的目标是进行若干次操作（不一定是最少次数），使得字符串 abcdefghijklmnopqrstuvwxyz（英文字母表）成为该字符串的一个子序列。字符串的子序列是通过删除某些位置的字符得到的字符串。你需要输出通过给定字符串得到的、包含英文字母表作为子序列的字符串，或者说明这是不可能的。

## 样例 #1
### 输入
```
aacceeggiikkmmooqqssuuwwyy
```
### 输出
```
abcdefghijklmnopqrstuvwxyz
```

## 样例 #2
### 输入
```
thereisnoanswer
```
### 输出
```
-1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路基本一致，都是通过模拟的方法，从字符 'a' 开始，遍历输入字符串，若当前字符小于等于当前目标字符，则将其替换为目标字符，并将目标字符更新为下一个字符，直到目标字符超过 'z' 或者遍历完整个字符串。最后判断是否能得到包含 'a' 到 'z' 的子序列，若不能则输出 -1，否则输出变换后的字符串。

不同题解的区别主要在于代码实现的细节，如变量命名、循环条件的判断等，但整体思路相同。

### 所选的题解
- **cq_loves_Capoo（5星）**
    - **关键亮点**：思路清晰，代码简洁，注释详细，使用 `ios::sync_with_stdio(false)` 优化输入输出速度。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
char a='a';
int main()
{
    ios::sync_with_stdio(false);
    cin>>st;
    for(int i=0;i<st.length();i++)
        if(st[i]<=a)
        {
            st[i]=a;
            a++;
            if(a>'z') break;
        }
    if(a<='z') 
    {
        cout<<"-1";
        return 0;
    }
    cout<<st;
    return 0;
}
```
核心实现思想：从 'a' 开始，遍历字符串，若当前字符小于等于 'a'，则将其替换为 'a'，并将 'a' 更新为 'b'，以此类推，直到 'a' 超过 'z' 或者遍历完字符串。最后判断是否能得到包含 'a' 到 'z' 的子序列。

### 最优关键思路或技巧
- 维护一个目标字符变量，从 'a' 开始，依次遍历字符串，将满足条件的字符替换为目标字符，并更新目标字符。
- 当目标字符超过 'z' 时，说明已经得到包含 'a' 到 'z' 的子序列，可提前结束遍历。

### 拓展思路
同类型题目通常会涉及字符串的变换和子序列的判断，可采用类似的模拟方法，根据具体题目要求调整判断条件和变换规则。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

### 个人心得
无

---
处理用时：23.59秒