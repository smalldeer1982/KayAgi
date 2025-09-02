# 题目信息

# Largest Subsequence

## 题目描述

Given is a string $ s $ of length $ n $ . In one operation you can select the lexicographically largest $ ^\dagger $ subsequence of string $ s $ and cyclic shift it to the right $ ^\ddagger $ .

Your task is to calculate the minimum number of operations it would take for $ s $ to become sorted, or report that it never reaches a sorted state.

 $ ^\dagger $ A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

 $ ^\ddagger $ By cyclic shifting the string $ t_1t_2\ldots t_m $ to the right, we get the string $ t_mt_1\ldots t_{m-1} $ .

## 说明/提示

In the first test case, the string $ s $ is already sorted, so we need no operations.

In the second test case, doing one operation, we will select cb and cyclic shift it. The string $ s $ is now abc which is sorted.

In the third test case, $ s $ cannot be sorted.

In the fourth test case we will perform the following operations:

- The lexicographically largest subsequence is zca. Then $ s $ becomes abzc.
- The lexicographically largest subsequence is zc. Then $ s $ becomes abcz. The string becomes sorted.

Thus, we need $ 2 $ operations.

## 样例 #1

### 输入

```
6
5
aaabc
3
acb
3
bac
4
zbca
15
czddeneeeemigec
13
cdefmopqsvxzz```

### 输出

```
0
1
-1
2
6
0```

# AI分析结果

### 题目内容重写
给定一个长度为 $n$ 的字符串 $s$。每次操作可以选择字符串 $s$ 中字典序最大的子序列，并将其向右循环移位。向右循环移位的定义是将子序列 $t_1t_2\ldots t_m$ 变为 $t_mt_1\ldots t_{m-1}$。

你的任务是计算使字符串 $s$ 变为有序的最小操作次数，如果无法使字符串有序，则输出 `-1`。

### 算法分类
贪心、字符串

### 题解分析与结论
各题解的核心思路是找到字符串中字典序最大的子序列，并通过循环移位操作将其排序。主要难点在于如何高效地找到最大字典序子序列，并确定最小操作次数。以下是对各题解的总结与对比：

1. **wmrqwq** 的题解：
   - 思路：通过贪心策略找到最大字典序子序列，并将其反转后插入原字符串，判断是否有序。
   - 难点：如何高效地找到最大字典序子序列，并确定操作次数。
   - 评分：4星
   - 关键亮点：通过贪心策略找到最大子序列，并通过反转操作简化问题。

2. **huangrenheluogu** 的题解：
   - 思路：维护最大字典序子序列，并通过循环移位操作将其排序。
   - 难点：如何处理子序列中相同字符的情况。
   - 评分：4星
   - 关键亮点：通过维护子序列并处理相同字符，优化了操作次数。

3. **Luzhuoyuan** 的题解：
   - 思路：通过倒序遍历找到最大字典序子序列，并通过翻转操作将其排序。
   - 难点：如何高效地找到最大子序列，并确定操作次数。
   - 评分：4星
   - 关键亮点：通过倒序遍历找到最大子序列，并通过翻转操作简化问题。

### 最优关键思路
最优的思路是通过贪心策略找到最大字典序子序列，并通过循环移位操作将其排序。具体实现中，可以通过倒序遍历字符串，找到最大子序列，并通过翻转操作将其插入原字符串，判断是否有序。

### 可拓展之处
类似的问题可以通过贪心策略和字符串操作来解决，例如在字符串中找到特定模式的子序列，或者通过循环移位操作将字符串变为特定状态。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得摘录
- **wmrqwq**：通过贪心策略找到最大子序列，并通过反转操作简化问题，调试中发现最大子序列不一定是后缀，及时修正了思路。
- **huangrenheluogu**：在处理相同字符时，发现需要减去相同字符的长度，避免重复操作，优化了代码。
- **Luzhuoyuan**：通过倒序遍历找到最大子序列，并通过翻转操作简化问题，调试中发现需要处理相同字符的情况，及时修正了代码。

### 核心代码片段
```cpp
// wmrqwq 的代码片段
for(int i=n-1;i>=0;i--) {
    if((long long)s[i]>=maxn)
        maxn=(long long)s[i],vis[i]=1,ss+=s[i];
}
for(int i=ss.size()-1;i>=0;i--)
    if(ss[i]!=ss[i-1]) {
        ans=i;
        break;
    }
```
该代码通过倒序遍历找到最大字典序子序列，并通过反转操作将其插入原字符串，判断是否有序。

---
处理用时：30.19秒