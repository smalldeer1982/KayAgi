# 题目信息

# Paranoid String

## 题目描述

Let's call a binary string $ T $ of length $ m $ indexed from $ 1 $ to $ m $ paranoid if we can obtain a string of length $ 1 $ by performing the following two kinds of operations $ m-1 $ times in any order :

- Select any substring of $ T $ that is equal to 01, and then replace it with 1.
- Select any substring of $ T $ that is equal to 10, and then replace it with 0.For example, if $ T =  $ 001, we can select the substring $ [T_2T_3] $ and perform the first operation. So we obtain $ T =  $ 01.

You are given a binary string $ S $ of length $ n $ indexed from $ 1 $ to $ n $ . Find the number of pairs of integers $ (l, r) $ $ 1 \le l \le r \le n $ such that $ S[l \ldots r] $ (the substring of $ S $ from $ l $ to $ r $ ) is a paranoid string.

## 说明/提示

In the first sample, $ S $ already has length $ 1 $ and doesn't need any operations.

In the second sample, all substrings of $ S $ are paranoid. For the entire string, it's enough to perform the first operation.

In the third sample, all substrings of $ S $ are paranoid except $ [S_2S_3] $ , because we can't perform any operations on it, and $ [S_1S_2S_3] $ (the entire string).

## 样例 #1

### 输入

```
5
1
1
2
01
3
100
4
1001
5
11111```

### 输出

```
1
3
4
8
5```

# AI分析结果

### 题目内容
# 多疑字符串

## 题目描述
我们称长度为 $m$ 且从 $1$ 到 $m$ 编号的二进制字符串 $T$ 是“多疑的”，如果我们可以通过以下两种操作，以任意顺序执行 $m - 1$ 次，得到一个长度为 $1$ 的字符串：
- 选择 $T$ 中任意一个等于 $01$ 的子串，然后将其替换为 $1$。
- 选择 $T$ 中任意一个等于 $10$ 的子串，然后将其替换为 $0$。
例如，如果 $T = 001$，我们可以选择子串 $[T_2T_3]$ 并执行第一个操作，这样我们就得到 $T = 01$。

给定一个长度为 $n$ 且从 $1$ 到 $n$ 编号的二进制字符串 $S$，找出满足 $1 \le l \le r \le n$ 的整数对 $(l, r)$ 的数量，使得 $S[l \ldots r]$（$S$ 从 $l$ 到 $r$ 的子串）是一个“多疑字符串”。

## 说明/提示
在第一个样例中，$S$ 的长度已经为 $1$，无需任何操作。

在第二个样例中，$S$ 的所有子串都是“多疑的”。对于整个字符串，执行第一个操作就足够了。

在第三个样例中，$S$ 的所有子串都是“多疑的”，除了 $[S_2S_3]$，因为我们无法对其执行任何操作，以及 $[S_1S_2S_3]$（整个字符串）。

## 样例 #1
### 输入
```
5
1
1
2
01
3
100
4
1001
5
11111
```
### 输出
```
1
3
4
8
5
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路一致，均是发现两种操作本质为删除相邻不同字符中左边的字符，最后一位字符总会保留。基于此，对于以 $S_i$ 结尾的子串，当 $S_i = S_{i - 1}$ 时，对答案贡献为 $1$；当 $S_i \neq S_{i - 1}$ 时，对答案贡献为 $i$ 。通过遍历字符串并累加贡献得到最终结果。各题解在思路清晰度、代码可读性和优化程度上差异不大，都直接实现该思路，时间复杂度均为 $O(Tn)$ 。

### 通用建议与扩展思路
此类题目关键在于深入理解操作本质，进而发现子串规律。可拓展思路为思考更复杂的字符串操作规则下，如何寻找满足特定条件的子串。对于同类型题，可关注其他基于字符串操作并统计符合条件子串数量的题目，重点分析操作对字符串结构产生的影响。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1332 血色先锋队](https://www.luogu.com.cn/problem/P1332)
- [P1348  Couple number](https://www.luogu.com.cn/problem/P1348) 

---
处理用时：24.78秒