# 题目信息

# Digits Sequence Dividing

## 题目描述

You are given a sequence $ s $ consisting of $ n $ digits from $ 1 $ to $ 9 $ .

You have to divide it into at least two segments (segment — is a consecutive sequence of elements) (in other words, you have to place separators between some digits of the sequence) in such a way that each element belongs to exactly one segment and if the resulting division will be represented as an integer numbers sequence then each next element of this sequence will be strictly greater than the previous one.

More formally: if the resulting division of the sequence is $ t_1, t_2, \dots, t_k $ , where $ k $ is the number of element in a division, then for each $ i $ from $ 1 $ to $ k-1 $ the condition $ t_{i} < t_{i + 1} $ (using numerical comparing, it means that the integer representations of strings are compared) should be satisfied.

For example, if $ s=654 $ then you can divide it into parts $ [6, 54] $ and it will be suitable division. But if you will divide it into parts $ [65, 4] $ then it will be bad division because $ 65 > 4 $ . If $ s=123 $ then you can divide it into parts $ [1, 23] $ , $ [1, 2, 3] $ but not into parts $ [12, 3] $ .

Your task is to find any suitable division for each of the $ q $ independent queries.

## 样例 #1

### 输入

```
4
6
654321
4
1337
2
33
4
2122
```

### 输出

```
YES
3
6 54 321
YES
3
1 3 37
NO
YES
2
21 22
```

# AI分析结果



# Digits Sequence Dividing

## 题目描述

给定一个由 $n$ 个 1 到 9 的数字组成的序列 $s$，要求将其分割成至少两个连续子段，使得每个子段表示的整数严格递增。例如 $s=654$ 可以分割为 [6,54]，但 [65,4] 不满足条件。

---

**算法分类**：构造、贪心

---

## 题解综合分析

该题的核心在于发现多位数一定比少位数大的特性。所有题解均围绕以下思路展开：
- **n < 2**：无法分割，直接输出 NO
- **n = 2**：比较两个字符的大小
- **n > 2**：将第一个字符单独分割，剩余部分作为第二段

**关键技巧**：利用字符串长度差异保证数值大小关系。当分割后的第二部分长度远大于第一部分时，其数值必然更大，无需逐位比较。

---

### 精选题解

#### 1. 作者：精神小伙！ (★★★★★)
**亮点**：
- 输入处理正确，代码简洁
- 分三类情况处理，逻辑清晰
- 核心代码实现仅需 10 行

**核心代码**：
```cpp
cin >> n >> s;
if (n > 2) {
    cout << "YES\n2\n" << s[0] << " ";
    for (int i=1; i<n; ++i) cout << s[i];
    cout << endl;
}
```

#### 2. 作者：Reywmp (★★★★☆)
**亮点**：
- 强调多位数必然大于少位数的贪心性质
- 通过特判 n=2 的边界情况确保正确性
- 代码中正确处理输入流跳转问题

**心得**：  
> "CF的题目往往考驗智商而非复杂算法，需要敏锐观察数字字符串的构造特性。"

#### 3. 作者：BlackPanda (★★★★☆)
**亮点**：
- 代码结构工整，条件分支明确
- 直接比较字符而非转换为数字，提升效率
- 注释清晰，便于理解分段逻辑

---

### 推荐练习
1. [CF1107A - 原题](https://www.luogu.com.cn/problem/CF1107A)  
2. [P1235 分段](https://www.luogu.com.cn/problem/P1235)  
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心策略的经典应用）

---
处理用时：116.79秒