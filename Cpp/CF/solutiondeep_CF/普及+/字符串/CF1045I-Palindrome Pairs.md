# 题目信息

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出

```
6
```

# AI分析结果



# Palindrome Pairs

## 题目描述

在学习了很多太空探索知识后，一个名叫Ana的小女孩想换个主题。

Ana是一个热爱回文串（可以正读反读都一样的字符串）的女孩。她已经学会了如何判断单个字符串是否是回文，但很快就对这个简单问题感到厌倦，于是她提出了一个更有趣的问题，需要你的帮助来解决：

给定一个仅由小写字母组成的字符串数组，任务是找出其中有多少对回文对。回文对的定义是：这对字符串的拼接结果存在至少一个排列是回文串。换句话说，如果两个字符串分别为"aab"和"abcac"，它们的拼接结果"aababcac"是否存在某种排列（例如"aabccbaa"）是回文。

注意：两对字符串$(i,j)$和$(j,i)$视为同一对，不应重复计算。

## 样例 #1

### 输入
```
3
aa
bb
cd
```

### 输出
```
1
```

## 样例 #2

### 输入
```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出
```
6
```

---

### 题解综合分析

#### 关键思路总结
所有题解均采用**字符奇偶性状态压缩**的核心技巧：
1. 将每个字符串编码为26位二进制数（每位表示对应字母出现次数的奇偶性）
2. 合法配对的条件是两数异或结果最多有1位不同（即汉明距离≤1）
3. 使用哈希表（unordered_map）快速查询满足条件的配对数量

#### 最优技巧提炼
1. **位运算压缩状态**：通过二进制位表示字符出现次数的奇偶性，将问题转化为数值匹配问题
2. **异或操作判条件**：两数异或后计算1的个数（__builtin_popcount）或直接枚举可能的不同位
3. **哈希表预存状态**：通过遍历时动态更新哈希表，实现O(1)复杂度查询历史状态

---

### 高分题解推荐

#### 1. yijan（⭐⭐⭐⭐⭐）
**关键亮点**：
- 清晰的状态压缩思路说明
- 预处理排序优化查询效率
- 边遍历边统计的高效实现方式

**核心代码**：
```cpp
for(ll i=0;i<n;++i){
    res += S[num[i]]; // 完全相同的状态
    for(ll j=0;j<26;++j)
        if((num[i]>>j)&1) res += S[num[i]^(1<<j)]; // 枚举差异位
    ++S[num[i]];
}
```

#### 2. mrsrz（⭐⭐⭐⭐）
**关键亮点**：
- 极简代码实现（仅20行）
- 实时更新哈希表的在线处理
- 直观的异或位运算逻辑

**核心代码**：
```cpp
b[a[1]]=1;
for(int i=2;i<=n;++i){
    ans += b[a[i]]; // 相同状态
    for(int j=0;j<26;++j) // 枚举可能的不同位
        ans += b[a[i]^(1<<j)];
    ++b[a[i]];
}
```

#### 3. lzyqwq（⭐⭐⭐⭐）
**关键亮点**：
- 严谨的数学形式化描述
- 清晰的复杂度分析
- 结合CF提交记录的可靠实现

**思路亮点**：
> 枚举每个状态$S$的所有可能匹配状态（包括自身和差异1位的状态），利用哈希表快速统计历史出现次数

---

### 拓展与总结

#### 类似问题套路
1. **字符统计类问题**：当涉及字符出现次数的奇偶性/模数性质时，可考虑位压缩
2. **配对计数问题**：需要快速查询满足特定条件的配对数量时，哈希表是首选结构
3. **状态差异判断**：汉明距离相关问题常使用位掩码+预计算的技巧

#### 推荐练习
1. [CF914F Substrings in a String](https://www.luogu.com.cn/problem/CF914F) - 位掩码处理字符串匹配
2. [P7537 [COCI2016-2017#4] Rima](https://www.luogu.com.cn/problem/P7537) - 回文性质与状态处理
3. [P7642 [BalticOI 2006 Day 1] BITTER ALCOHOL](https://www.luogu.com.cn/problem/P7642) - 状态压缩与哈希结合应用

#### 调试经验摘录
来自Adchory题解：
> 注意本题卡空间，因此需要使用map而非数组存储状态。这启示我们在ACM赛制中需灵活选择数据结构，平衡时间与空间复杂度。

---
处理用时：47.50秒