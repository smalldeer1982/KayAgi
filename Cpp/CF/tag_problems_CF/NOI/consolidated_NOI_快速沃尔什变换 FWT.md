---
title: "Lost Array"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1713F
tag: ['快速沃尔什变换 FWT']
---

# Lost Array

## 题目描述

My orzlers, we can optimize this problem from $ O(S^3) $ to $ O\left(T^\frac{5}{9}\right) $ !

— Spyofgame, founder of Orzlim religion



A long time ago, Spyofgame invented the famous array $ a $ ( $ 1 $ -indexed) of length $ n $ that contains information about the world and life. After that, he decided to convert it into the matrix $ b $ ( $ 0 $ -indexed) of size $ (n + 1) \times (n + 1) $ which contains information about the world, life and beyond.

Spyofgame converted $ a $ into $ b $ with the following rules.

- $ b_{i,0} = 0 $ if $ 0 \leq i \leq n $ ;
- $ b_{0,i} = a_{i} $ if $ 1 \leq i \leq n $ ;
- $ b_{i,j} = b_{i,j-1} \oplus b_{i-1,j} $ if $ 1 \leq i, j \leq n $ .

Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Today, archaeologists have discovered the famous matrix $ b $ . However, many elements of the matrix has been lost. They only know the values of $ b_{i,n} $ for $ 1 \leq i \leq n $ (note that these are some elements of the last column, not the last row).

The archaeologists want to know what a possible array of $ a $ is. Can you help them reconstruct any array that could be $ a $ ?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ b_{1,n}, b_{2,n}, \ldots, b_{n,n} $ ( $ 0 \leq b_{i,n} < 2^{30} $ ).

## 输出格式

If some array $ a $ is consistent with the information, print a line containing $ n $ integers $ a_1, a_2, \ldots, a_n $ . If there are multiple solutions, output any.

If such an array does not exist, output $ -1 $ instead.

## 说明/提示

If we let $ a = [1,2,3] $ , then $ b $ will be:

  $ \bf{0} $  $ \bf{1} $  $ \bf{2} $  $ \bf{3} $  $ \bf{0} $  $ 1 $  $ 3 $  $ 0 $  $ \bf{0} $  $ 1 $  $ 2 $  $ 2 $  $ \bf{0} $  $ 1 $  $ 3 $  $ 1 $ The values of $ b_{1,n}, b_{2,n}, \ldots, b_{n,n} $ generated are $ [0,2,1] $ which is consistent with what the archaeologists have discovered.

## 样例 #1

### 输入

```
3
0 2 1
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
1
199633
```

### 输出

```
199633
```

## 样例 #3

### 输入

```
10
346484077 532933626 858787727 369947090 299437981 416813461 865836801 141384800 157794568 691345607
```

### 输出

```
725081944 922153789 481174947 427448285 516570428 509717938 855104873 280317429 281091129 1050390365
```



---

---
title: "Message Spread"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2029H
tag: ['快速沃尔什变换 FWT', '快速沃尔什变换 FWT']
---

# Message Spread

## 题目描述

Given is an undirected graph with $ n $ vertices and $ m $ edges. Each edge connects two vertices $ (u, v) $ and has a probability of $ \frac{p}{q} $ of appearing each day.

Initially, vertex $ 1 $ has a message. At the end of the day, a vertex has a message if and only if itself or at least one of the vertices adjacent to it had the message the day before. Note that each day, each edge chooses its appearance independently.

Calculate the expected number of days before all the vertices have the message, modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1\leq n\leq 21 $ , $ n-1\leq m\leq\frac{n(n-1)}{2} $ ).

Then $ m $ lines follow, each containing four integers $ u $ , $ v $ , $ p $ , and $ q $ ( $ 1\leq u\neq v\leq n $ , $ 1\leq p<q<998\,244\,353 $ , $ \gcd(p,q)=1 $ ) — there is an undirected edge between $ u $ and $ v $ , and it has a probability of appearance of $ \frac{p}{q} $ each day.

It is guaranteed that there are no self-loops or multiple-edges in the graph and that the graph is connected if all of the edges appear.

Additional constraint in the input: Let $ g_{i,j} $ be the probability of appearance of the edge between $ i $ and $ j $ ( $ g_{i,j}=0 $ if there is no edge between $ i $ and $ j $ ). It is guaranteed that for any $ S\subseteq\{1,2,\ldots,n\} $ ( $ |S|\ge 1 $ ), $ $$$ \prod_{i\in S}\left(\prod_{j\in\{1,2,\ldots,n\}\setminus S}(1-g_{i,j})\right)\not\equiv1\pmod{998\,244\,353}.  $ $$$

## 输出格式

Print a single integer in the only line of the output — the expected number of days, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the exact answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test, the answer is equal to the expected number of days before the only edge in the graph first appears, and that is $ \frac{1}{0.1}=10 $ .

In the second test, the answer is equal to $ \frac{20}{9} $ before it is taken modulo $ 998\,244\,353 $ .

In the third test, the only vertex already has the message, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
2 1
1 2 1 10
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 3
1 2 1 2
1 3 1 2
2 3 1 2
```

### 输出

```
887328316
```

## 样例 #3

### 输入

```
1 0
```

### 输出

```
0
```

## 样例 #4

### 输入

```
5 8
1 2 1 11
1 3 2 11
1 4 3 11
1 5 4 11
2 4 5 11
2 5 6 11
3 4 7 11
4 5 8 11
```

### 输出

```
469993557
```

## 样例 #5

### 输入

```
21 22
1 2 3 4
2 3 4 5
3 4 5 6
5 6 7 8
6 7 8 9
7 8 9 10
8 9 2 3
9 10 3 4
10 11 4 5
11 12 5 6
12 13 6 7
13 14 7 8
14 15 8 9
15 16 9 10
16 17 2 3
17 18 3 4
18 19 4 5
19 20 5 6
20 21 6 7
1 10 100 1001
15 4 147 220
4 11 1 998244352
```

### 输出

```
299529765
```



---

---
title: "Wonderful XOR Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2096H
tag: ['多项式', '快速沃尔什变换 FWT', '快速沃尔什变换 FWT']
---

# Wonderful XOR Problem

## 题目描述

你是...算了，直接解决这个问题吧。

有 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \ldots [l_n, r_n]$。对于每个 $x$ 从 $0$ 到 $2^m - 1$，求满足以下条件的序列 $a_1, a_2, \ldots a_n$ 的数量（模 $998\,244\,353$）：

- 对于所有 $i$ 从 $1$ 到 $n$，有 $l_i \leq a_i \leq r_i$；
- $a_1 \oplus a_2 \oplus \ldots \oplus a_n = x$，其中 $\oplus$ 表示[按位异或运算符](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

第一行包含两个整数 $n$ 和 $m$（$1 \leq n \leq 2 \cdot 10^5$，$1 \leq m \leq 18$）。

接下来的 $n$ 行中，第 $i$ 行包含两个整数 $l_i$ 和 $r_i$（$0 \leq l_i \leq r_i < 2^m$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$，且所有测试用例的 $2^m$ 之和不超过 $2^{18}$。


## 输出格式

对于每个 $x$ 从 $0$ 到 $2^m - 1$，定义：

- $f_x$ 为有效序列的数量，模 $998\,244\,353$；
- $g_x = f_x \cdot 2^x \mod 998\,244\,353$。

这里，$f_x$ 和 $g_x$ 都是区间 $[0, 998\,244\,352]$ 内的整数。

设 $h = g_0 \oplus g_1 \oplus \ldots \oplus g_{2^m - 1}$。

输出一个整数——$h$ 的值本身。不要进行模运算。


## 说明/提示

对于第一个测试用例，$f_x$ 的值如下：

- $f_0 = 2$，因为有 $2$ 个有效序列：$[1, 1]$ 和 $[2, 2]$；
- $f_1 = 2$，因为有 $2$ 个有效序列：$[0, 1]$ 和 $[2, 3]$；
- $f_2 = 2$，因为有 $2$ 个有效序列：$[0, 2]$ 和 $[1, 3]$；
- $f_3 = 3$，因为有 $3$ 个有效序列：$[0, 3]$、$[1, 2]$ 和 $[2, 1]$。

$g_x$ 的值如下：

- $g_0 = f_0 \cdot 2^0 = 2 \cdot 2^0 = 2$；
- $g_1 = f_1 \cdot 2^1 = 2 \cdot 2^1 = 4$；
- $g_2 = f_2 \cdot 2^2 = 2 \cdot 2^2 = 8$；
- $g_3 = f_3 \cdot 2^3 = 3 \cdot 2^3 = 24$。

因此，输出的值为 $2 \oplus 4 \oplus 8 \oplus 24 = 22$。

对于第二个测试用例，$f_x$ 的值如下：

- $f_{0} = 120$；
- $f_{1} = 120$；
- $f_{2} = 119$；
- $f_{3} = 118$；
- $f_{4} = 105$；
- $f_{5} = 105$；
- $f_{6} = 106$；
- $f_{7} = 107$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 2
0 2
1 3
5 3
3 7
1 3
0 2
1 5
3 6
10 14
314 1592
653 5897
932 3846
264 3383
279 5028
841 9716
939 9375
105 8209
749 4459
230 7816
1 5
0 29
```

### 输出

```
22
9812
75032210
1073741823
```



---

