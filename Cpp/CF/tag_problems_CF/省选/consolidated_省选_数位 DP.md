---
title: "Segment Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1073E
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Segment Sum

## 题目描述

You are given two integers $ l $ and $ r $ ( $ l \le r $ ). Your task is to calculate the sum of numbers from $ l $ to $ r $ (including $ l $ and $ r $ ) such that each number contains at most $ k $ different digits, and print this sum modulo $ 998244353 $ .

For example, if $ k = 1 $ then you have to calculate all numbers from $ l $ to $ r $ such that each number is formed using only one digit. For $ l = 10, r = 50 $ the answer is $ 11 + 22 + 33 + 44 = 110 $ .

## 输入格式

The only line of the input contains three integers $ l $ , $ r $ and $ k $ ( $ 1 \le l \le r < 10^{18}, 1 \le k \le 10 $ ) — the borders of the segment and the maximum number of different digits.

## 输出格式

Print one integer — the sum of numbers from $ l $ to $ r $ such that each number contains at most $ k $ different digits, modulo $ 998244353 $ .

## 说明/提示

For the first example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{50 \cdot 51}{2} - \frac{9 \cdot 10}{2} = 1230 $ . This example also explained in the problem statement but for $ k = 1 $ .

For the second example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{2345 \cdot 2346}{2} = 2750685 $ .

For the third example the answer is $ 101 + 110 + 111 + 112 + 113 + 114 + 115 + 116 + 117 + 118 + 119 + 121 + 122 + 131 + 133 + 141 + 144 + 151 = 2189 $ .

## 样例 #1

### 输入

```
10 50 2

```

### 输出

```
1230

```

## 样例 #2

### 输入

```
1 2345 10

```

### 输出

```
2750685

```

## 样例 #3

### 输入

```
101 154 2

```

### 输出

```
2189

```



---

---
title: "XOR Matrix"
layout: "post"
diff: 省选/NOI-
pid: CF2075E
tag: ['数位 DP', '组合数学', '位运算']
---

# XOR Matrix

## 题目描述

对于两个数组 $a = [a_1, a_2, \dots, a_n]$ 和 $b = [b_1, b_2, \dots, b_m]$，我们定义大小为 $n \times m$ 的异或矩阵 $X$，其中对于每对 $(i,j)$（$1 \le i \le n$；$1 \le j \le m$），有 $X_{i,j} = a_i \oplus b_j$。符号 $\oplus$ 表示按位异或运算。

给定四个整数 $n, m, A, B$。请计算满足以下条件的数组对 $(a, b)$ 的数量：
- 数组 $a$ 包含 $n$ 个整数，每个整数的取值范围是 $0$ 到 $A$；
- 数组 $b$ 包含 $m$ 个整数，每个整数的取值范围是 $0$ 到 $B$；
- 由这些数组生成的异或矩阵中，不同值的数量不超过两个。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例由一行组成，包含四个整数 $n, m, A, B$（$2 \le n, m, A, B \le 2^{29} - 1$）。

## 输出格式

对于每个测试用例，输出一个整数——满足所有三个条件的数组对 $(a, b)$ 的数量。由于该数值可能非常大，请输出其对 $998244353$ 取模的结果。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
2 2 2 2
2 3 4 5
5 7 4 3
1337 42 1337 42
4 2 13 37
536870902 536370902 536390912 466128231
```

### 输出

```
57
864
50360
439988899
112000
732195491
```



---

---
title: "Numbers and Strings"
layout: "post"
diff: 省选/NOI-
pid: CF2104F
tag: ['二分', '数位 DP']
---

# Numbers and Strings

## 题目描述

对于每个从 $1$ 到 $n$ 的整数 $x$，我们将按照以下规则生成字符串 $S(x)$：

- 计算 $x+1$；
- 将 $x$ 和 $x+1$ 在十进制表示下无分隔符、无前导零地拼接在一起；
- 将得到的字符串中的所有数字按非递减顺序排序。

例如，字符串 $S(139)$ 是 `011349`（排序前的拼接结果是 `139140`）。字符串 $S(99)$ 是 `00199`。

你的任务是统计 $S(1), S(2), \dots, S(n)$ 中不同字符串的数量。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

每个测试用例由一行组成，包含一个整数 $n$（$1 \le n \le 10^{9} - 2$）。

## 输出格式

对于每个测试用例，输出一个整数，表示表示不同的字符串数量。

## 样例 #1

### 输入

```
2
42
1337
```

### 输出

```
42
948
```



---

---
title: "Beautiful numbers"
layout: "post"
diff: 省选/NOI-
pid: CF55D
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Beautiful numbers

## 题目描述

Volodya is an odd boy and his taste is strange as well. It seems to him that a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits. We will not argue with this and just count the quantity of beautiful numbers in given ranges.

## 输入格式

The first line of the input contains the number of cases $ t $ ( $ 1<=t<=10 $ ). Each of the next $ t $ lines contains two natural numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=9·10^{18} $ ).

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

Output should contain $ t $ numbers — answers to the queries, one number per line — quantities of beautiful numbers in given intervals (from $ l_{i} $ to $ r_{i} $ , inclusively).

## 样例 #1

### 输入

```
1
1 9

```

### 输出

```
9

```

## 样例 #2

### 输入

```
1
12 15

```

### 输出

```
2

```



---

