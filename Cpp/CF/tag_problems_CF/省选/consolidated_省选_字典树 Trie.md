---
title: "Keep XOR Low"
layout: "post"
diff: 省选/NOI-
pid: CF1616H
tag: ['动态规划 DP', '字典树 Trie']
---

# Keep XOR Low

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ and an integer $ x $ .

Find the number of non-empty subsets of indices of this array $ 1 \leq b_1 < b_2 < \ldots < b_k \leq n $ , such that for all pairs $ (i, j) $ where $ 1 \leq i < j \leq k $ , the inequality $ a_{b_i} \oplus a_{b_j} \leq x $ is held. Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). As the answer may be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ x $ ( $ 1 \leq n \leq 150\,000 $ , $ 0 \leq x < 2^{30} $ ). Here, $ n $ is the size of the array.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{30} $ ): the array itself.

## 输出格式

Print one integer: the number of non-empty subsets such that the bitwise XOR of every pair of elements is at most $ x $ , modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 2
0 1 2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 6
4 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
4 0
1 1 2 2
```

### 输出

```
6
```



---

---
title: "Xorderable Array"
layout: "post"
diff: 省选/NOI-
pid: CF2045J
tag: ['字典树 Trie', '位运算', 'Ad-hoc']
---

# Xorderable Array

## 题目描述

给定一个整数数组 $A$，包含 $N$ 个元素，记作 $[A_1, A_2, \dots, A_N]$。

如果可以重新排列数组 $A$，使得对任意 $1 \leq i < j \leq N$ 的索引对 $(i, j)$，阵列满足：$A_i \oplus p \leq A_j \oplus q$ 且 $A_i \oplus q \leq A_j \oplus p$，那么称数组 $A$ 为 $(p, q)$-可排序的，其中 $\oplus$ 表示按位异或。

另有一个长度为 $M$ 的整数数组 $X$：$[X_1, X_2, \dots, X_M]$。求出所有满足 $1 \leq u < v \leq M$ 且数组 $A$ 可以是 $(X_u, X_v)$-可排序的索引对 $(u, v)$ 的数量。

## 输入格式

第一行包含两个整数 $N$ 和 $M$（$2 \leq N, M \leq 200\,000$）。

第二行是数组 $A$ 的 $N$ 个整数，每个数满足 $0 \leq A_i < 2^{30}$。

第三行是数组 $X$ 的 $M$ 个整数，每个数满足 $0 \leq X_u < 2^{30}$。

## 输出格式

输出一个整数，表示满足条件的索引对 $(u, v)$ 的数量。

## 说明/提示

关于样例的说明：
- 在样例 1 中，通过将数组 $A$ 重新排列为 $[0, 0, 3]$，可以达到 $(1, 1)$-可排序的要求。
- 在样例 2 中，通过将数组 $A$ 重新排列为 $[13, 0, 7, 24, 22]$，数组 $A$ 可以满足 $(12, 10)$-可排序条件。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 4
0 3 0
1 2 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
0 7 13 22 24
12 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3
0 0 0
1 2 3
```

### 输出

```
0
```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

---
title: "Two Subsequences"
layout: "post"
diff: 省选/NOI-
pid: CF83E
tag: ['动态规划 DP', '字典树 Trie']
---

# Two Subsequences

## 题目描述

# CF83E 两个子序列
在一堂IT课上，Valera 学习了数据压缩。我们现在将向你介绍老师所讲解的一种新的数据压缩方法。

定义压缩函数 $f()$：

- $f($空序列$)=$ 空字符串
- 对于任意一个字符串 $s$，$f(s)=s$。
- 对于任意两个字符串 $s_{1}$，$s_{2}$，$f(s1,s2)$ 为包含前缀 $s_{1}$ 且包含后缀 $s_{2}$ 的字符串中长度最小的一个。
- 对于任意 $n$ 个字符串，$f({s_{1},s_{2},\ldots,s_{n}})=f(f({s_{1},s_{2},\ldots,s_{n-1}}),s_{n})$

例如：
1. $ f(001,011)=0011 $ 
2. $ f(111,011)=111011 $ 
2. $f(000,000,111)=f(f(000,000),111)=f(000,111)=000111 $ .

现在 Valera 面临一个难题：他需要将给定的需要压缩的序列 ${a_{1},a_{2},\ldots,a_{n}}$ 分成两个新的序列 ${b_{1},b_{2},\ldots,b_{k}}$ 和 ${c_{1},c_{2},\ldots,c_{m}}$ $(k+m=n)$ ，使得$S=|f({b_{1},b_{2},\ldots,b_{k}})|+|f({c_{1},c_{2},\ldots,c_{m}})|$ 的值最小。这里 $|p|$ 表示字符串 $p$ 的长度。

**注意**：
1. 不允许在子序列中更改元素的相对顺序。
2. 可以使得 $mk=0$ 即可以使得序列 $b$ $c$ 中的一个为空。
3. 对于原序列 $a$ 中的任意一项 $a_{i}$，不得既不存在于 $b$ 中，亦不存在于 $c$ 中。也不得同时存在于 $b$ 和 $c$ 中。
4.  $b$  $c$ 中的元素在 $a$ 中不必连续，即 $b$ 和 $c$ 的元素可以在 $a$ 中交替出现(参见样例2、3)。

## 输入格式

第一行一个整数 $n$，表示序列 $a$ 的项数。

接下来 $n$ 行，每行一个字符串，第 $i+1$ 行输入的字符串表示序列 $a$ 的第 $i$ 项，即 $a_{i}$。

输入数据保证序列 $a$ 中的所有项长度相同，并且仅由数字 $0$ 或 $1$ 组成。

## 输出格式

一行一个整数，$S$ 的最小值。
### 样例解释
1. 样例解释1

最佳的方法为：一个子序列为空，另一个子序列等于原始序列 $a$。此时$S_{min}=|f(01,10,01)|=|f(f(01,00),01)|=| f(010,01)|=|0101|=4$。故输出 $4$。

2. 最好的选择是：$b={000,001}$，$c={111,110}$。此时$S_{min}=|f（000,001）|+|f（111,110）|=|0001|+|1110|=8$。故输出 $8$。

3. 最好的选择是：$b={10101,01010,01000}，c={11111,10010}$。此时$S_{min}=(|10101000 |+|111110010 |=17$。故输出 $16$。

Translated by: @xhz0311

## 样例 #1

### 输入

```
3
01
10
01

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
000
111
110
001

```

### 输出

```
8

```

## 样例 #3

### 输入

```
5
10101
01010
11111
01000
10010

```

### 输出

```
17

```



---

