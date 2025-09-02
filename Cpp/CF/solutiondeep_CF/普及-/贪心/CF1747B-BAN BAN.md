# 题目信息

# BAN BAN

## 题目描述

You are given an integer $ n $ .

Let's define $ s(n) $ as the string "BAN" concatenated $ n $ times. For example, $ s(1) $ = "BAN", $ s(3) $ = "BANBANBAN". Note that the length of the string $ s(n) $ is equal to $ 3n $ .

Consider $ s(n) $ . You can perform the following operation on $ s(n) $ any number of times (possibly zero):

- Select any two distinct indices $ i $ and $ j $ $ (1 \leq i, j \leq 3n, i \ne j) $ .
- Then, swap $ s(n)_i $ and $ s(n)_j $ .

You want the string "BAN" to not appear in $ s(n) $ as a subsequence. What's the smallest number of operations you have to do to achieve this? Also, find one such shortest sequence of operations.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first testcase, $ s(1) =  $ "BAN", we can swap $ s(1)_1 $ and $ s(1)_2 $ , converting $ s(1) $ to "ABN", which does not contain "BAN" as a subsequence.

In the second testcase, $ s(2) =  $ "BANBAN", we can swap $ s(2)_2 $ and $ s(2)_6 $ , converting $ s(2) $ to "BNNBAA", which does not contain "BAN" as a subsequence.

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1
1 2
1
2 6```

# AI分析结果



【题目翻译】
# BAN BAN

## 题目描述

给定整数 $n$，定义 $s(n)$ 为由 $n$ 个 "BAN" 连接而成的字符串。例如 $s(1)$ = "BAN"，$s(3)$ = "BANBANBAN"。字符串长度为 $3n$。

你可以通过交换任意两个不同位置的字符来修改字符串。要求通过最少操作次数使得修改后的字符串中不存在 "BAN" 作为子序列。请输出最小操作次数及一种具体方案。

子序列定义为通过删除若干字符（可不连续）得到的序列。

---

【题解分析】

各题解核心思路一致：通过交换不同 "BAN" 块的 A 和 N 来破坏子序列结构，最优解为交换次数 $\lceil n/2 \rceil$。关键技巧在于：

1. **对称破坏**：将第 $i$ 个 "BAN" 的 A 与倒数第 $i$ 个 "BAN" 的 N 交换，每次操作破坏两个块。
2. **奇偶处理**：奇数情况下中间块单独处理，通过交换 A 和 N 破坏自身结构。
3. **位置映射**：利用公式 $3i-1$ 和 $3(n-i+1)$ 快速计算交换位置。

---

【精选题解】

1. **CR7_houyetong（4.5星）**
   - **亮点**：最早提出对称交换策略，清晰说明奇偶处理逻辑，代码简洁高效。
   - **代码核心**：
     ```cpp
     for (i=1;i<=(n+1)/2;i++)
         cout<<3*i-1<<" "<<(n-i+1)*3<<endl;
     ```
     **实现思路**：循环 $\lceil n/2 \rceil$ 次，每次交换第 $i$ 个块的 A（位置 $3i-1$）与倒数第 $i$ 个块的 N（位置 $3(n-i+1)$）。

2. **HNOIRPplusplus（4星）**
   - **亮点**：从子序列构成条件（B在A前、A在N前）切入，提出将 A 移动到 B 左侧的通用思路。
   - **代码核心**：
     ```cpp
     for(int i=1, j=3*n-1; i < j; i +=3, j -=3)
         cout<<i<<" "<<j<<endl;
     ```
     **实现思路**：双指针从两端向中间移动，交换 B 和 N 的位置（第一个块的 B 与最后一个块的 N）。

---

【关键思路总结】
- **成对破坏**：每次交换处理两个 "BAN" 块，将时间复杂度优化至 $O(n)$。
- **索引映射**：利用固定公式直接计算交换位置，避免复杂模拟。
- **奇偶统一**：$\lceil n/2 \rceil$ 公式天然处理奇偶情况，中间块只需单次操作。

---

【拓展与心得】
- **同类问题**：类似破坏子序列结构的题目（如 CF118B），可考虑关键字符的位置置换。
- **调试心得**：需注意字符串索引从1开始，部分题解误用0-based索引导致错误。
- **思维突破**：将字符串视为多个重复块的整体处理，而非逐个字符分析。

---

【相似题目推荐】
1. [CF118B - Present from Lena](https://www.luogu.com.cn/problem/CF118B)（字符串模式破坏）
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心选择最优操作）
3. [CF1328C - Ternary XOR](https://www.luogu.com.cn/problem/CF1328C)（对称构造策略）

---
处理用时：77.95秒