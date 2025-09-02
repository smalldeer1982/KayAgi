# 题目信息

# Infinite Prefixes

## 题目描述

You are given string $ s $ of length $ n $ consisting of 0-s and 1-s. You build an infinite string $ t $ as a concatenation of an infinite number of strings $ s $ , or $ t = ssss \dots $ For example, if $ s = $ 10010, then $ t = $ 100101001010010...

Calculate the number of prefixes of $ t $ with balance equal to $ x $ . The balance of some string $ q $ is equal to $ cnt_{0, q} - cnt_{1, q} $ , where $ cnt_{0, q} $ is the number of occurrences of 0 in $ q $ , and $ cnt_{1, q} $ is the number of occurrences of 1 in $ q $ . The number of such prefixes can be infinite; if it is so, you must say that.

A prefix is a string consisting of several first letters of a given string, without any reorders. An empty prefix is also a valid prefix. For example, the string "abcd" has 5 prefixes: empty string, "a", "ab", "abc" and "abcd".

## 说明/提示

In the first test case, there are 3 good prefixes of $ t $ : with length $ 28 $ , $ 30 $ and $ 32 $ .

## 样例 #1

### 输入

```
4
6 10
010010
5 3
10101
1 0
0
2 0
01```

### 输出

```
3
0
1
-1```

# AI分析结果

【题目内容】
# Infinite Prefixes

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，由 0 和 1 组成。你通过无限次拼接 $s$ 来构建一个无限字符串 $t$，即 $t = ssss \dots$。例如，如果 $s = $ 10010，那么 $t = $ 100101001010010...

计算 $t$ 的前缀中平衡值等于 $x$ 的前缀的数量。某个字符串 $q$ 的平衡值等于 $cnt_{0, q} - cnt_{1, q}$，其中 $cnt_{0, q}$ 是 $q$ 中 0 的个数，$cnt_{1, q}$ 是 $q$ 中 1 的个数。如果这样的前缀数量是无限的，你必须说明这一点。

前缀是指由给定字符串的前几个字符组成的字符串，不能重新排序。空前缀也是一个有效的前缀。例如，字符串 "abcd" 有 5 个前缀：空字符串、"a"、"ab"、"abc" 和 "abcd"。

## 说明/提示

在第一个测试用例中，$t$ 有 3 个平衡值为 10 的前缀：长度为 $28$、$30$ 和 $32$ 的前缀。

## 样例 #1

### 输入

```
4
6 10
010010
5 3
10101
1 0
0
2 0
01```

### 输出

```
3
0
1
-1```

【算法分类】前缀和

【题解分析与结论】
本题的核心在于通过前缀和来计算无限字符串 $t$ 的前缀平衡值，并根据平衡值是否等于 $x$ 来统计符合条件的数量。题解主要分为两种情况：
1. 当 $s$ 的平衡值 $p = 0$ 时，如果存在某个前缀的平衡值等于 $x$，则输出 `-1`，否则输出 `0`。
2. 当 $p \neq 0$ 时，通过计算 $(x - A_i) \mod p = 0$ 的数量来统计符合条件的数量。

【评分较高的题解】
1. 作者：DepletedPrism (5星)
   - 关键亮点：思路清晰，代码简洁，详细讨论了 $p = 0$ 和 $p \neq 0$ 的情况，并处理了 $x = 0$ 的特殊情况。
   - 代码实现：
     ```cpp
     int p = A[n];
     if (!p) {
         bool infty = false;
         for (int i = 0; i <= n && !infty; ++i)
             if (A[i] == x) infty = true;
         puts(infty? "-1": "0");
     } else {
         int ans = x == 0;
         for (int i = 1; i <= n; ++i)
             if (1LL * (x-A[i]) * p >= 0 && (x - A[i]) % p == 0) ++ans;
         printf("%d\n", ans);
     }
     ```

2. 作者：E1_de5truct0r (4星)
   - 关键亮点：思路清晰，代码简洁，详细讨论了 $pre_n = 0$ 和 $pre_n \neq 0$ 的情况，并处理了 $x = 0$ 的特殊情况。
   - 代码实现：
     ```cpp
     if(now[n]==0) {
         if(flag) puts("-1");
         else puts("0");
         continue;
     }
     for(int i=1;i<=n;i++)
         if((x-now[i])%now[n]==0 && 1ll*(x-now[i])*now[n]>=0) ans++;
     printf("%d\n",ans);
     ```

【最优关键思路或技巧】
- 使用前缀和数组 $A_i$ 来记录 $s$ 的前缀平衡值。
- 通过分类讨论 $p = 0$ 和 $p \neq 0$ 的情况，分别处理无限和有限的情况。
- 注意处理 $x = 0$ 时的空字符串情况。

【可拓展之处】
- 类似问题可以扩展到其他平衡值计算，如字符出现次数的差值、字符权重的差值等。
- 可以进一步优化时间复杂度，或者扩展到多维前缀和的计算。

【推荐题目】
1. P1115 最大子段和
2. P3406 海底高铁
3. P3131 [USACO16JAN]Subsequences Summing to Sevens S

---
处理用时：34.15秒