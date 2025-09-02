---
title: "Swap and Maximum Block"
layout: "post"
diff: 省选/NOI-
pid: CF1716E
tag: ['线段树', '位运算']
---

# Swap and Maximum Block

## 题目描述

You are given an array of length $ 2^n $ . The elements of the array are numbered from $ 1 $ to $ 2^n $ .

You have to process $ q $ queries to this array. In the $ i $ -th query, you will be given an integer $ k $ ( $ 0 \le k \le n-1 $ ). To process the query, you should do the following:

- for every $ i \in [1, 2^n-2^k] $ in ascending order, do the following: if the $ i $ -th element was already swapped with some other element during this query, skip it; otherwise, swap $ a_i $ and $ a_{i+2^k} $ ;
- after that, print the maximum sum over all contiguous subsegments of the array (including the empty subsegment).

For example, if the array $ a $ is $ [-3, 5, -3, 2, 8, -20, 6, -1] $ , and $ k = 1 $ , the query is processed as follows:

- the $ 1 $ -st element wasn't swapped yet, so we swap it with the $ 3 $ -rd element;
- the $ 2 $ -nd element wasn't swapped yet, so we swap it with the $ 4 $ -th element;
- the $ 3 $ -rd element was swapped already;
- the $ 4 $ -th element was swapped already;
- the $ 5 $ -th element wasn't swapped yet, so we swap it with the $ 7 $ -th element;
- the $ 6 $ -th element wasn't swapped yet, so we swap it with the $ 8 $ -th element.

So, the array becomes $ [-3, 2, -3, 5, 6, -1, 8, -20] $ . The subsegment with the maximum sum is $ [5, 6, -1, 8] $ , and the answer to the query is $ 18 $ .

Note that the queries actually change the array, i. e. after a query is performed, the array does not return to its original state, and the next query will be applied to the modified array.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 18 $ ).

The second line contains $ 2^n $ integers $ a_1, a_2, \dots, a_{2^n} $ ( $ -10^9 \le a_i \le 10^9 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains one integer $ k $ ( $ 0 \le k \le n-1 $ ) describing the $ i $ -th query.

## 输出格式

For each query, print one integer — the maximum sum over all contiguous subsegments of the array (including the empty subsegment) after processing the query.

## 说明/提示

Transformation of the array in the example: $ [-3, 5, -3, 2, 8, -20, 6, -1] \rightarrow [-3, 2, -3, 5, 6, -1, 8, -20] \rightarrow [2, -3, 5, -3, -1, 6, -20, 8] \rightarrow [5, -3, 2, -3, -20, 8, -1, 6] $ .

## 样例 #1

### 输入

```
3
-3 5 -3 2 8 -20 6 -1
3
1
0
1
```

### 输出

```
18
8
13
```



---

---
title: "GCD is Greater"
layout: "post"
diff: 省选/NOI-
pid: CF1945H
tag: ['位运算']
---

# GCD is Greater

## 题目描述

In the evenings during the hike, Kirill and Anton decided to take out an array of integers $ a $ of length $ n $ from their backpack and play a game with it. The rules are as follows:

1. Kirill chooses from $ 2 $ to $ (n-2) $ numbers and encircles them in red.
2. Anton encircles all the remaining numbers in blue.
3. Kirill calculates the greatest common divisor ([GCD](https://en.wikipedia.org/wiki/Greatest_common_divisor)) of all the red numbers.
4. Anton calculates the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of all the blue numbers and adds the number $ x $ to the result.
5. If the GCD of all the red numbers is strictly greater than the sum of the bitwise AND of all the blue numbers and the number $ x $ , then Kirill wins; otherwise, Anton wins.

Help Kirill to beat Anton or tell if it's impossible.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 20\,000 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 4\le n \le 4\cdot 10^5 $ , $ 0 \le x \le 4\cdot 10^5 $ ) — the number of integers and the number $ x $ respectively.

The second line contains an array $ a $ of length $ n $ ( $ 1 \le a_i \le 4\cdot 10^5 $ ).

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 4\cdot 10^5 $ . It is also guaranteed that the sum of the maximum values of $ a_i $ for each test case does not exceed $ 4\cdot 10^5 $ .

## 输出格式

For each test case, output "YES" on the first line if the condition can be met, on the second line, output the number of chosen numbers by Kirill and the numbers themselves in any order separated by a space, and on the third line, output the size of the second set and the numbers in it.

Otherwise, output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 样例 #1

### 输入

```
8
4 1
4 3 1 8
4 1
4 5 8 4
5 0
1 1 1 1 1
5 2
31 63 127 63 31
4 1
1 3 3 3
8 3
4 3 4 1 2 2 5 3
4 2
1 4 3 6
8 48
31 61 37 15 53 26 61 12
```

### 输出

```
YES
2 4 8
2 3 1 
YES
2 4 4
2 5 8 
NO
YES
2 63 63
3 31 127 31
YES
2 3 3
2 1 3
YES
2 4 4
6 3 1 2 2 5 3
YES
2 3 6
2 1 4 
YES
2 61 61
6 31 37 15 53 26 12
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
title: "Maximize Nor"
layout: "post"
diff: 省选/NOI-
pid: CF2103F
tag: ['线段树', '位运算']
---

# Maximize Nor

## 题目描述

对于一个包含 $k$ 位整数的数组 $b_1, b_2, \ldots, b_m$，其按位或非运算$^{\text{∗}}$可以通过从左到右累积计算得到。更正式地说，对于 $m \ge 2$，$\operatorname{nor}(b_1, b_2, \ldots, b_m) = \operatorname{nor}(\operatorname{nor}(b_1, b_2, \ldots, b_{m - 1}), b_m)$，而 $\operatorname{nor}(b_1) = b_1$。

给定一个包含 $k$ 位整数的数组 $a_1, a_2, \ldots, a_n$。对于每个下标 $i$（$1 \le i \le n$），找出所有包含下标 $i$ 的子数组$^{\text{†}}$中按位或非运算的最大值。换句话说，对于每个下标 $i$，找出所有满足 $1 \le l \le i \le r \le n$ 的子数组 $a_l, a_{l+1}, \ldots, a_r$ 中 $\operatorname{nor}(a_l, a_{l+1}, \ldots, a_r)$ 的最大值。

$^{\text{∗}}$ 两个布尔值的逻辑或非运算定义为：当两个值都为 $0$ 时结果为 $1$，否则为 $0$。两个 $k$ 位整数的按位或非运算是对每对对应位进行逻辑或非运算得到的结果。

例如，将 $2$ 和 $6$ 表示为 $4$ 位二进制数时，计算 $\operatorname{nor}(2, 6)$。$2$ 的二进制表示为 $0010_2$，$6$ 为 $0110_2$。因此，$\operatorname{nor}(2,6) = 1001_2 = 9$，因为从左到右逐位进行逻辑或非运算：
- $\operatorname{nor}(0,0) = 1$
- $\operatorname{nor}(0,1) = 0$
- $\operatorname{nor}(1,0) = 0$
- $\operatorname{nor}(1,1) = 0$

注意，如果 $2$ 和 $6$ 表示为 $3$ 位整数，则 $\operatorname{nor}(2,6) = 1$。

$^{\text{†}}$ 数组 $x$ 是数组 $y$ 的子数组，当且仅当 $x$ 可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^5$，$1 \le k \le 17$）——数组的元素个数和数组元素的位数。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 2^k - 1$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数，其中第 $i$ 个整数是所有包含下标 $i$ 的子数组中按位或非运算的最大值。


## 说明/提示

在第一个测试用例中：
- 包含下标 $1$ 的子数组有 $[1]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $1$ 和 $0$。因此，下标 $1$ 的答案为 $1$。
- 包含下标 $2$ 的子数组有 $[3]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $3$ 和 $0$。因此，下标 $2$ 的答案为 $3$。

在第二个测试用例中：
- 对于 $i = 1$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 2$，按位或非运算最大的子数组是 $[a_2] = [7]$，$\operatorname{nor}(7) = 7$。
- 对于 $i = 3$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 4$，按位或非运算最大的子数组是 $[a_4] = [6]$，$\operatorname{nor}(6) = 6$。
- 对于 $i = 5$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2 2
1 3
5 3
1 7 4 6 2
```

### 输出

```
1 3
5 7 5 6 5
```



---

---
title: "AND Graph"
layout: "post"
diff: 省选/NOI-
pid: CF986C
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS', '位运算']
---

# AND Graph

## 题目描述

给定一个 $m$ 个整数的集合，每个整数在 $0$ 到 $2^n-1$ 之间，以每一个整数作为顶点建无向图，当两个点 $x$ 和 $y$ 做与运算值为 $0$ 时，则认为 $x$ 和 $y$ 是连通的，即 $x$ 和 $y$ 之间有一条无向边。请求出图中连通块的个数。

## 输入格式

第一行输入两个整数 $n$ 和 $m$（$0 \leq  n\leq22$，$1 \leq  m\leq2^n$）。  
第二行输入 $m$ 个整数，即集合里的元素。

## 输出格式

一个整数，表示图中连通块的个数。

## 样例 #1

### 输入

```
2 3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5
5 19 10 20 12

```

### 输出

```
2

```



---

