# 题目信息

# Reverse Binary Strings

## 题目描述

You are given a string $ s $ of even length $ n $ . String $ s $ is binary, in other words, consists only of 0's and 1's.

String $ s $ has exactly $ \frac{n}{2} $ zeroes and $ \frac{n}{2} $ ones ( $ n $ is even).

In one operation you can reverse any substring of $ s $ . A substring of a string is a contiguous subsequence of that string.

What is the minimum number of operations you need to make string $ s $ alternating? A string is alternating if $ s_i \neq s_{i + 1} $ for all $ i $ . There are two types of alternating strings in general: 01010101... or 10101010...

## 说明/提示

In the first test case, string 10 is already alternating.

In the second test case, we can, for example, reverse the last two elements of $ s $ and get: 0110 $ \rightarrow $ 0101.

In the third test case, we can, for example, make the following two operations:

1. 11101000 $ \rightarrow $ 10101100;
2. 10101100 $ \rightarrow $ 10101010.

## 样例 #1

### 输入

```
3
2
10
4
0110
8
11101000```

### 输出

```
0
1
2```

# AI分析结果

【题目内容】
# 反转二进制字符串

## 题目描述

给定一个长度为偶数 $n$ 的二进制字符串 $s$。字符串 $s$ 仅由 0 和 1 组成，且恰好包含 $\frac{n}{2}$ 个 0 和 $\frac{n}{2}$ 个 1。

每次操作可以选择 $s$ 的任意子串进行反转。子串是指字符串中连续的子序列。

问最少需要多少次操作才能使字符串 $s$ 变为交替字符串？交替字符串是指 $s_i \neq s_{i + 1}$ 对所有 $i$ 都成立。交替字符串有两种形式：01010101... 或 10101010...

## 说明/提示

在第一个测试用例中，字符串 10 已经是交替字符串。

在第二个测试用例中，我们可以反转最后两个字符，得到：0110 $ \rightarrow $ 0101。

在第三个测试用例中，我们可以进行以下两次操作：

1. 11101000 $ \rightarrow $ 10101100;
2. 10101100 $ \rightarrow $ 10101010.

## 样例 #1

### 输入

```
3
2
10
4
0110
8
11101000```

### 输出

```
0
1
2```

【算法分类】
贪心

【题解分析与结论】
本题的核心是通过最少的反转操作将二进制字符串变为交替字符串。多数题解都基于以下观察：每次反转操作可以减少连续相同字符的段数。因此，问题的关键在于统计字符串中连续相同字符的段数，并根据这些段数计算所需的最少操作次数。

【评分较高的题解】
1. **作者：yu__xuan (赞：9)**
   - **星级：4**
   - **关键亮点：** 通过统计连续相同字符的段数，直接取最大值作为操作次数。思路简洁，代码清晰。
   - **核心代码：**
     ```cpp
     int ans1 = 0, ans0 = 0;
     for (int i = 1; i < n; ++i) {
         if (sss[i] == '1' && sss[i - 1] == '1') ++ans1;
         if (sss[i] == '0' && sss[i - 1] == '0') ++ans0;
     }
     printf("%d\n", max(ans1, ans0));
     ```

2. **作者：itisover (赞：4)**
   - **星级：4**
   - **关键亮点：** 通过分析连续相同字符的段数的奇偶性，得出操作次数的公式。思路清晰，代码简洁。
   - **核心代码：**
     ```cpp
     for (int i = 1; i < n; i++)
         if (s[i] == s[i - 1]) ++ans;
     printf("%d\n", (ans + 1) >> 1);
     ```

3. **作者：小王子2021 (赞：1)**
   - **星级：4**
   - **关键亮点：** 通过统计连续相同字符的段数，取最大值作为操作次数。思路简单，代码易读。
   - **核心代码：**
     ```cpp
     for (int i = 2; i <= n; i++)
         if (s[i] == s[i - 1]) {
             if (s[i] == '0') ans0++;
             else ans1++;
         }
     cout << max(ans0, ans1) << endl;
     ```

【最优关键思路】
通过统计字符串中连续相同字符的段数，取最大值作为所需的最少操作次数。这种方法简洁高效，适用于类似问题。

【可拓展之处】
类似的问题可以扩展到其他类型的字符串操作，如交换字符、插入字符等。通过统计连续相同字符的段数，可以快速计算所需的最少操作次数。

【推荐题目】
1. [CF1437B Reverse Binary Strings](https://www.luogu.com.cn/problem/CF1437B)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

【个人心得】
在处理字符串操作问题时，统计连续相同字符的段数是一种常见的技巧。通过这种方法，可以快速简化问题并找到最优解。

---
处理用时：33.71秒