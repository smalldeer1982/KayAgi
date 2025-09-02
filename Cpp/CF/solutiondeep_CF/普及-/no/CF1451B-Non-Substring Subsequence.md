# 题目信息

# Non-Substring Subsequence

## 题目描述

Hr0d1y has $ q $ queries on a binary string $ s $ of length $ n $ . A binary string is a string containing only characters '0' and '1'.

A query is described by a pair of integers $ l_i $ , $ r_i $ $ (1 \leq l_i \lt r_i \leq n) $ .

For each query, he has to determine whether there exists a good subsequence in $ s $ that is equal to the substring $ s[l_i\ldots r_i] $ .

- A substring $ s[i\ldots j] $ of a string $ s $ is the string formed by characters $ s_i s_{i+1} \ldots s_j $ .
- String $ a $ is said to be a subsequence of string $ b $ if $ a $ can be obtained from $ b $ by deleting some characters without changing the order of the remaining characters.
- A subsequence is said to be good if it is not contiguous and has length $ \ge 2 $ . For example, if $ s $ is "1100110", then the subsequences $ s_1s_2s_4 $ ("1100110") and $ s_1s_5s_7 $ ("1100110") are good, while $ s_1s_2s_3 $ ("1100110") is not good.

Can you help Hr0d1y answer each query?

## 说明/提示

In the first test case,

- $ s[2\ldots 4] =  $ "010". In this case $ s_1s_3s_5 $ ("001000") and $ s_2s_3s_6 $ ("001000") are good suitable subsequences, while $ s_2s_3s_4 $ ("001000") is not good.
- $ s[1\ldots 3] =  $ "001". No suitable good subsequence exists.
- $ s[3\ldots 5] =  $ "100". Here $ s_3s_5s_6 $ ("001000") is a suitable good subsequence.

## 样例 #1

### 输入

```
2
6 3
001000
2 4
1 3
3 5
4 2
1111
1 4
2 3```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容
# 非子串子序列

## 题目描述
Hr0d1y 对一个长度为 $n$ 的二进制字符串 $s$ 有 $q$ 次查询。二进制字符串是仅包含字符 '0' 和 '1' 的字符串。

一次查询由一对整数 $l_i$，$r_i$ （$1 \leq l_i \lt r_i \leq n$）描述。

对于每次查询，他必须确定在 $s$ 中是否存在一个好子序列，该子序列等于子串 $s[l_i\ldots r_i]$ 。
- 字符串 $s$ 的子串 $s[i\ldots j]$ 是由字符 $s_i s_{i + 1} \ldots s_j$ 组成的字符串。
- 如果字符串 $a$ 可以通过从字符串 $b$ 中删除一些字符而不改变其余字符的顺序得到，则称字符串 $a$ 是字符串 $b$ 的子序列。
- 如果一个子序列不连续且长度 $\geq 2$，则称该子序列是好的。例如，如果 $s$ 是 "1100110"，那么子序列 $s_1s_2s_4$（"1100110"）和 $s_1s_5s_7$（"1100110"）是好的，而子序列 $s_1s_2s_3$（"1100110"）不是好的。

你能帮助 Hr0d1y 回答每个查询吗？

## 说明/提示
在第一个测试用例中，
- $s[2\ldots 4] = $ "010"。在这种情况下，$s_1s_3s_5$（"001000"）和 $s_2s_3s_6$（"001000"）是合适的好子序列，而 $s_2s_3s_4$（"001000"）不是好的。
- $s[1\ldots 3] = $ "001"。不存在合适的好子序列。
- $s[3\ldots 5] = $ "100"。这里 $s_3s_5s_6$（"001000"）是一个合适的好子序列。

## 样例 #1
### 输入
```
2
6 3
001000
2 4
1 3
3 5
4 2
1111
1 4
2 3
```

### 输出
```
YES
NO
YES
NO
YES
```

### 算法分类
字符串

### 题解综合分析与结论
所有题解的核心思路都是判断对于给定区间 $[l, r]$ 的子串，是否能通过移动其首字符或尾字符的位置来构造出一个非连续的子序列。即判断在子串首字符左侧是否存在与之相同的字符，或者在子串尾字符右侧是否存在与之相同的字符。若存在，则输出 `YES`，否则输出 `NO`。不同题解在代码实现细节上略有差异，如循环写法、变量命名、输入输出优化等，但整体思路和算法复杂度基本一致，时间复杂度均为 $O(t \times q \times n)$ 。由于各题解思路和实现较为基础，没有特别突出的优化，整体质量未达到4星标准。

### 通用建议与扩展思路
对于此类字符串子序列相关问题，关键在于理解子序列和子串的概念区别，以及如何根据题目对非连续子序列的限定条件来设计算法。可以进一步拓展到更复杂的字符串匹配问题，例如考虑多个字符的移动、不同字符匹配规则等。在解决这类问题时，要善于利用字符串的性质，如字符出现的位置、频率等信息，通过预处理或优化搜索方式来提高算法效率。

### 相似知识点洛谷题目
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串匹配与统计，需要在给定字符串中查找特定单词的出现次数及位置。
2. [P2375 [NOIP2017 普及组] 手链样式](https://www.luogu.com.cn/problem/P2375)：关于字符串循环同构相关问题，通过对字符串的旋转和比较来求解不同样式的数量。
3. [P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502)：结合了字符串处理与二维坐标问题，需要在二维字符矩阵中按特定窗口条件进行统计。 

---
处理用时：43.48秒