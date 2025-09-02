---
title: "William The Oblivious"
layout: "post"
diff: 提高+/省选-
pid: CF1609E
tag: ['线段树', '矩阵乘法']
---

# William The Oblivious

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609E/0e83a16b376d35306235c93a9bc0616a224b28a1.png)Before becoming a successful trader William got a university degree. During his education an interesting situation happened, after which William started to listen to homework assignments much more attentively. What follows is a formal description of the homework assignment as William heard it:

You are given a string $ s $ of length $ n $ only consisting of characters "a", "b" and "c". There are $ q $ queries of format ( $ pos, c $ ), meaning replacing the element of string $ s $ at position $ pos $ with character $ c $ . After each query you must output the minimal number of characters in the string, which have to be replaced, so that the string doesn't contain string "abc" as a subsequence. A valid replacement of a character is replacing it with "a", "b" or "c".

A string $ x $ is said to be a subsequence of string $ y $ if $ x $ can be obtained from $ y $ by deleting some characters without changing the ordering of the remaining characters.

## 输入格式

The first line contains two integers $ n $ and $ q $ $ (1 \le n, q \le 10^5) $ , the length of the string and the number of queries, respectively.

The second line contains the string $ s $ , consisting of characters "a", "b" and "c".

Each of the next $ q $ lines contains an integer $ i $ and character $ c $ $ (1 \le i \le n) $ , index and the value of the new item in the string, respectively. It is guaranteed that character's $ c $ value is "a", "b" or "c".

## 输出格式

For each query output the minimal number of characters that would have to be replaced so that the string doesn't contain "abc" as a subsequence.

## 说明/提示

Let's consider the state of the string after each query:

1. $ s =  $ "aaaaccccc". In this case the string does not contain "abc" as a subsequence and no replacements are needed.
2. $ s =  $ "aaabccccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "aaaaccccc". This string does not contain "abc" as a subsequence.
3. $ s =  $ "ababccccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ aaaaccccc". This string does not contain "abc" as a subsequence.
4. $ s =  $ "ababacccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaaaacccc". This string does not contain "abc" as a subsequence.
5. $ s =  $ "bbabacccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
6. $ s =  $ "bbababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbacacccc". This string does not contain "abc" as a subsequence.
7. $ s =  $ "bbabcbccc". In this case 1 replacements can be performed to get, for instance, string $ s =  $ "bbcbcbccc". This string does not contain "abc" as a subsequence.
8. $ s =  $ "baabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "bbbbcbccc". This string does not contain "abc" as a subsequence.
9. $ s =  $ "aaabcbccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacccccc". This string does not contain "abc" as a subsequence.
10. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
11. $ s =  $ "aaababccc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaacacccc". This string does not contain "abc" as a subsequence.
12. $ s =  $ "aaababbcc". In this case 2 replacements can be performed to get, for instance, string $ s =  $ "aaababbbb". This string does not contain "abc" as a subsequence.

## 样例 #1

### 输入

```
9 12
aaabccccc
4 a
4 b
2 b
5 a
1 b
6 b
5 c
2 a
1 a
5 a
6 b
7 b
```

### 输出

```
0
1
2
2
1
2
1
2
2
2
2
2
```



---

---
title: "Once Again..."
layout: "post"
diff: 提高+/省选-
pid: CF582B
tag: ['枚举', '矩阵乘法']
---

# Once Again...

## 题目描述

现有一个长度为 $n×T$ 的序列 $a_1, a_2, ..., a_{n×T}$ ，满足 $a_i=a_{i-n} (n<i<=n×T)$ 。请找出这个序列中的最长不降子序列的长度。

## 输入格式

输入的第一行有两个空格隔开的整数 $n$ 和 $T$ $(1<=n<=100,1<=T<=10^7)$ 。第二行有$n$ 个空格隔开的正整数 $a_1,a_2,...,a_n (1<=a_i<=300)$ 描述了这个序列的前 $n$ 项。

## 输出格式

输出一个整数——最长不降子序列的长度。

## 输入输出样例
略

## 说明/提示

样例中给出的序列如下：3, **1**, 4, **2**, **3**, 1, **4**, 2, 3, 1, **4**, 2. 加粗的数字是一种最长不降子序列的方案。

## 样例 #1

### 输入

```
4 3
3 1 4 2

```

### 输出

```
5

```



---

---
title: "Wet Shark and Blocks"
layout: "post"
diff: 提高+/省选-
pid: CF621E
tag: ['动态规划 DP', '矩阵乘法', '构造']
---

# Wet Shark and Blocks

## 题目描述

有 $b$ 个格子，每个格子有 $n$ 个数字，各个格子里面的数字都是相同的. 求从 $b$ 个格子中各取一个数字, 构成一个 $b$ 位数, 使得这个 $b$ 位数模 $x$ 为 $k$ 的方案数（同一格子内相同的数字算不同方案）.答案对 $1\times 10^9+7$ 取模.

## 输入格式

第一行有4个整数 $n,b,k,x$ ,其中 $2\leq n\leq 50000,1\leq b\leq 10^{9},0\leq k< x\leq 100,x\ge2$ 
第二行有 $n$ 个数, 为每个格子里面的数字(每个格子里面的数字都是相同的.)

## 输出格式

即从每个块中选择一个数构成一个大数, 使得其模x为k的方案数对 $1\times 10^9+7$ 取模.
注意:

样例二中没有一种方案使得模2为1
样例三中11,13,21,23,31,33满足模2余1.

感谢@aiyougege 提供的翻译

## 样例 #1

### 输入

```
12 1 5 10
3 5 6 7 8 9 5 1 1 1 1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 1 2
6 2 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2 1 2
3 1 2

```

### 输出

```
6

```



---

