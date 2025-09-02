# 题目信息

# Different is Good

## 题目描述

A wise man told Kerem "Different is good" once, so Kerem wants all things in his life to be different.

Kerem recently got a string $ s $ consisting of lowercase English letters. Since Kerem likes it when things are different, he wants all substrings of his string $ s $ to be distinct. Substring is a string formed by some number of consecutive characters of the string. For example, string "aba" has substrings "" (empty substring), "a", "b", "a", "ab", "ba", "aba".

If string $ s $ has at least two equal substrings then Kerem will change characters at some positions to some other lowercase English letters. Changing characters is a very tiring job, so Kerem want to perform as few changes as possible.

Your task is to find the minimum number of changes needed to make all the substrings of the given string distinct, or determine that it is impossible.

## 说明/提示

In the first sample one of the possible solutions is to change the first character to 'b'.

In the second sample, one may change the first character to 'a' and second character to 'b', so the string becomes "abko".

## 样例 #1

### 输入

```
2
aa
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
koko
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
murat
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 不同即好

## 题目描述
一位智者曾经告诉凯雷姆（Kerem）“不同就是好”，所以凯雷姆希望他生活中的所有事物都与众不同。

凯雷姆最近得到了一个由小写英文字母组成的字符串 $ s $。由于凯雷姆喜欢事物与众不同，他希望字符串 $ s $ 的所有子串都不同。子串是由字符串中若干连续字符组成的字符串。例如，字符串 "aba" 的子串有 ""（空串）、"a"、"b"、"a"、"ab"、"ba"、"aba"。

如果字符串 $ s $ 至少有两个相同的子串，那么凯雷姆将把某些位置的字符改为其他小写英文字母。更改字符是一项非常累人的工作，所以凯雷姆希望尽可能少地进行更改。

你的任务是找出使给定字符串的所有子串都不同所需的最少更改次数，或者确定这是不可能的。

## 说明/提示
在第一个样例中，一种可能的解决方案是将第一个字符改为 'b'。

在第二个样例中，可以将第一个字符改为 'a'，第二个字符改为 'b'，这样字符串就变成了 "abko"。

## 样例 #1
### 输入
```
2
aa
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
koko
```
### 输出
```
2
```

## 样例 #3
### 输入
```
5
murat
```
### 输出
```
0
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先判断字符串长度是否大于 26，若大于 26 则直接判定无解输出 -1，因为小写字母只有 26 个，长度超过 26 必然会有重复子串。对于长度不超过 26 的字符串，不同题解采用了不同方法来计算最少更改次数：
- 江山_远方和 Corsair 用桶记录每个字母的出现次数，统计出现次数大于 1 的字母需要更改的数量。
- jijidawang 提出可以用排序或离散化后用桶标记的方法，还给出了 STL 的做法。
- 两个封禁用户分别用排序遍历和 bool 数组标记的方法来计算需要更改的字母数量。

### 所选的题解
- 江山_远方（4星）：思路清晰，代码简洁，直接用桶记录字母出现次数，计算需要更改的字母数量。关键亮点在于利用抽屉原理快速判断无解情况，然后用桶计数计算更改次数。
- Corsair（3星）：同样使用桶计数，不过在判断无解时考虑了不能改变到的字母数量，逻辑稍复杂。
- jijidawang（3星）：提供了多种思路，包括排序、离散化和 STL 做法，但部分表述不够详细。

### 重点代码
#### 江山_远方的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string st;
int b[200];
int main()
{
    cin>>n;
    getline(cin,st);
    getline(cin,st);
    if(n>26){cout<<-1;return 0;}
    for(int i=1;i<=n;i++)b[st[i-1]]++;
    for(int i='a';i<='z';i++)if(b[i]>1)ans+=b[i]-1;
    cout<<ans;
    return 0; 
} 
```
核心实现思想：先判断字符串长度是否大于 26，若大于则无解。然后用桶 `b` 记录每个字母的出现次数，遍历桶，将出现次数大于 1 的字母的多余数量累加到 `ans` 中。

### 最优关键思路或技巧
- 利用抽屉原理，快速判断长度大于 26 的字符串无解。
- 使用桶（数组）记录字母的出现次数，方便统计需要更改的字母数量。

### 可拓展之处
同类型题可能会有不同的字符集，或者要求在更改字符时有更多限制条件。类似算法套路可以用于处理其他需要判断字符重复或统计字符数量的字符串问题。

### 推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得
- Corsair：提到在判断无解时要注意是 `ans + s > 26`，自己在这被卡了几次，提醒我们在处理边界条件时要仔细。

---
处理用时：27.76秒