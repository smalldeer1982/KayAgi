---
title: "Tree Master"
layout: "post"
diff: 提高+/省选-
pid: CF1806E
tag: ['剪枝', '分块', '根号分治']
---

# Tree Master

## 题目描述

You are given a tree with $ n $ weighted vertices labeled from $ 1 $ to $ n $ rooted at vertex $ 1 $ . The parent of vertex $ i $ is $ p_i $ and the weight of vertex $ i $ is $ a_i $ . For convenience, define $ p_1=0 $ .

For two vertices $ x $ and $ y $ of the same depth $ ^\dagger $ , define $ f(x,y) $ as follows:

- Initialize $ \mathrm{ans}=0 $ .
- While both $ x $ and $ y $ are not $ 0 $ : 
  - $ \mathrm{ans}\leftarrow \mathrm{ans}+a_x\cdot a_y $ ;
  - $ x\leftarrow p_x $ ;
  - $ y\leftarrow p_y $ .
- $ f(x,y) $ is the value of $ \mathrm{ans} $ .

You will process $ q $ queries. In the $ i $ -th query, you are given two integers $ x_i $ and $ y_i $ and you need to calculate $ f(x_i,y_i) $ .

 $ ^\dagger $ The depth of vertex $ v $ is the number of edges on the unique simple path from the root of the tree to vertex $ v $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 10^5 $ ; $ 1 \le q \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ).

The third line contains $ n-1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ).

Each of the next $ q $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1\le x_i,y_i\le n $ ). It is guaranteed that $ x_i $ and $ y_i $ are of the same depth.

## 输出格式

Output $ q $ lines, the $ i $ -th line contains a single integer, the value of $ f(x_i,y_i) $ .

## 说明/提示

Consider the first example:

In the first query, the answer is $ a_4\cdot a_5+a_3\cdot a_3+a_2\cdot a_2+a_1\cdot a_1=3+4+25+1=33 $ .

In the second query, the answer is $ a_6\cdot a_6+a_2\cdot a_2+a_1\cdot a_1=1+25+1=27 $ .

## 样例 #1

### 输入

```
6 2
1 5 2 3 1 1
1 2 3 3 2
4 5
6 6
```

### 输出

```
33
27
```

## 样例 #2

### 输入

```
14 8
3 2 5 3 1 4 2 2 2 5 5 5 2 4
1 2 3 1 1 4 7 3 3 1 5 3 8
4 4
4 10
13 10
3 12
13 9
3 12
9 10
11 5
```

### 输出

```
47
53
48
36
42
36
48
14
```



---

---
title: "Sum of Progression"
layout: "post"
diff: 提高+/省选-
pid: CF1921F
tag: ['根号分治']
---

# Sum of Progression

## 题目描述

You are given an array $ a $ of $ n $ numbers. There are also $ q $ queries of the form $ s, d, k $ .

For each query $ q $ , find the sum of elements $ a_s + a_{s+d} \cdot 2 + \dots + a_{s + d \cdot (k - 1)} \cdot k $ . In other words, for each query, it is necessary to find the sum of $ k $ elements of the array with indices starting from the $ s $ -th, taking steps of size $ d $ , multiplying it by the serial number of the element in the resulting sequence.

## 输入格式

Each test consists of several testcases. The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases. Next lines contain descriptions of testcases.

The first line of each testcase contains two numbers $ n, q $ ( $ 1 \le n \le 10^5, 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array $ a $ and the number of queries.

The second line contains $ n $ integers $ a_1, ... a_n $ ( $ -10^8 \le a_1, ..., a_n \le 10^8 $ ) — elements of the array $ a $ .

The next $ q $ lines each contain three integers $ s $ , $ d $ , and $ k $ ( $ 1 \le s, d, k \le n $ , $ s + d\cdot (k - 1) \le n $ ).

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 10^5 $ , and that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5  $ .

## 输出格式

For each testcase, print $ q $ numbers in a separate line — the desired sums, separated with space.

## 样例 #1

### 输入

```
5
3 3
1 1 2
1 2 2
2 2 1
1 1 2
3 1
-100000000 -100000000 -100000000
1 1 3
5 3
1 2 3 4 5
1 2 3
2 3 2
1 1 5
3 1
100000000 100000000 100000000
1 1 3
7 7
34 87 5 42 -44 66 -32
2 2 2
4 3 1
1 3 2
6 2 1
5 2 2
2 5 2
6 1 2
```

### 输出

```
5 1 3 
-600000000 
22 12 55 
600000000 
171 42 118 66 -108 23 2
```



---

---
title: "Alter the GCD"
layout: "post"
diff: 提高+/省选-
pid: CF2005D
tag: ['数论', '根号分治']
---

# Alter the GCD

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

You must perform the following operation exactly once:

- choose any indices $ l $ and $ r $ such that $ 1 \le l \le r \le n $ ;
- swap $ a_i $ and $ b_i $ for all $ i $ such that $ l \leq i \leq r $ .

Find the maximum possible value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once. Also find the number of distinct pairs $ (l, r) $ which achieve the maximum value.

## 输入格式

In the first line of the input, you are given a single integer $ t $ ( $ 1 \le t \le 10^5 $ ), the number of test cases. Then the description of each test case follows.

In the first line of each test case, you are given a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), representing the number of integers in each array.

In the next line, you are given $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

In the last line, you are given $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the elements of the array $ b $ .

The sum of values of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output a line with two integers: the maximum value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once, and the number of ways.

## 说明/提示

In the first, third, and fourth test cases, there's no way to achieve a higher GCD than $ 1 $ in any of the arrays, so the answer is $ 1 + 1 = 2 $ . Any pair $ (l, r) $ achieves the same result; for example, in the first test case there are $ 36 $ such pairs.

In the last test case, you must choose $ l = 1 $ , $ r = 2 $ to maximize the answer. In this case, the GCD of the first array is $ 5 $ , and the GCD of the second array is $ 1 $ , so the answer is $ 5 + 1 = 6 $ , and the number of ways is $ 1 $ .

## 样例 #1

### 输入

```
5
8
11 4 16 17 3 24 25 8
8 10 4 21 17 18 25 21
4
6 4 24 13
15 3 1 14
2
13 14
5 8
8
20 17 15 11 21 10 3 7
9 9 4 20 14 9 13 1
2
18 13
15 20
```

### 输出

```
2 36
3 2
2 3
2 36
6 1
```



---

---
title: "Monster"
layout: "post"
diff: 提高+/省选-
pid: CF2035E
tag: ['动态规划 DP', '模拟退火', '根号分治']
---

# Monster

## 题目描述

Man, this Genshin boss is so hard. Good thing they have a top-up of $ 6 $ coins for only $  \$4.99 $ . I should be careful and spend no more than I need to, lest my mom catches me...



You are fighting a monster with $ z $ health using a weapon with $ d $ damage. Initially, $ d=0 $ . You can perform the following operations.

- Increase $ d $ — the damage of your weapon by $ 1 $ , costing $ x $ coins.
- Attack the monster, dealing $ d $ damage and costing $ y $ coins.

You cannot perform the first operation for more than $ k $ times in a row.

Find the minimum number of coins needed to defeat the monster by dealing at least $ z $ damage.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases.

The only line of each test case contains 4 integers $ x $ , $ y $ , $ z $ , and $ k $ ( $ 1\leq x, y, z, k\leq 10^8 $ ) — the first operation's cost, the second operation's cost, the monster's health, and the limitation on the first operation.

## 输出格式

For each test case, output the minimum number of coins needed to defeat the monster.

## 说明/提示

In the first test case, $ x = 2 $ , $ y = 3 $ , $ z = 5 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 12 $ coins:

- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.

You deal a total of $ 3 + 3 = 6 $ damage, defeating the monster who has $ 5 $ health. The total number of coins you use is $ 2 + 2 + 2 + 3 + 3 = 12 $ coins.

In the second test case, $ x = 10 $ , $ y = 20 $ , $ z = 40 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 190 $ coins:

- Increase damage by $ 5 $ , costing $ 5\cdot x $ = $ 50 $ coins.
- Attack the monster once, dealing $ 5 $ damage, costing $ 20 $ coins.
- Increase damage by $ 2 $ , costing $ 2\cdot x $ = $ 20 $ coins.
- Attack the monster $ 5 $ times, dealing $ 5\cdot 7 = 35 $ damage, costing $ 5\cdot y $ = $ 100 $ coins.

You deal a total of $ 5 + 35 = 40 $ damage, defeating the monster who has exactly $ 40 $ health. The total number of coins you use is $ 50 + 20 + 20 + 100 = 190 $ coins.

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10
```

### 输出

```
12
190
280
160
```



---

---
title: "I've Been Flipping Numbers for 300 Years and Calculated the Sum"
layout: "post"
diff: 提高+/省选-
pid: CF2072G
tag: ['根号分治']
---

# I've Been Flipping Numbers for 300 Years and Calculated the Sum

## 题目描述

经过三百年的史莱姆养殖，Akito 终于获得了魔法数字 $n$。当他找到商人准备兑换黄金时，商人却给了他一个任务。

商人表示，完成这个任务需要用到技能 $\text{rev}(n, p)$，而 Akito 恰好最近学会了这个技能。$\text{rev}(n, p)$ 表示以下操作流程：

1. 将数字 $n$ 以 $p$ 进制表示，记作 $n = \overline{n_{\ell - 1} \ldots n_1 n_0}$，其中 $\ell$ 是 $n$ 的 $p$ 进制表示的位数长度。
2. 反转这个 $p$ 进制表示，得到 $m = \overline{n_0 n_1 \ldots n_{\ell - 1}}$。
3. 将 $m$ 转换回十进制并作为结果返回。

商人的任务是计算总和 $x = \sum\limits_{p = 2}^{k} \text{rev}(n, p)$。由于这个数字可能非常大，只需要输出 $x$ 对 $10^9 + 7$ 取模后的余数。商人还提到，上一个旅行者计算这个和已经用了三百年仍未完成。但你一定会帮助 Akito 更快完成，对吗？

## 输入格式

第一行包含一个数 $t$（$1 \le t \le 5000$）——测试用例的数量。

每个测试用例的唯一一行包含两个数 $n$ 和 $k$（$1 \le n \le 3 \cdot 10^5$，$2 \le k \le 10^{18}$）——魔法数字和求和的进制上限。

请注意，所有测试用例的 $n$ 之和没有限制。

## 输出格式

对于每个测试用例，输出一个数字——$x = \sum\limits_{p = 2}^{k} \text{rev}(n, p)$ 对 $10^9 + 7$ 取模后的结果。

## 说明/提示

在第三个测试用例中，$n = 1$。数字 1 在任何进制下都表示为单个数字，这意味着对于任意 $p \ge 2$ 都有 $\text{rev}(1, p) = 1$。因此，$x = \sum\limits_{p = 2}^{k} 1 = \sum\limits_{p = 2}^{10} 1 = 10 - 2 + 1 = 9$。

在第四个测试用例中，$x = \text{rev}(4, 2) + \text{rev}(4, 3) + \text{rev}(4, 4)$。计算各项：
- $4 = 100_2 \rightarrow \text{rev}(4, 2) = 001_2 = 1$
- $4 = 11_3 \rightarrow \text{rev}(4, 3) = 11_3 = 4$
- $4 = 10_4 \rightarrow \text{rev}(4, 4) = 01_4 = 1$
因此，$x = 1 + 4 + 1 = 6$。

在第七个测试用例中，$x = \text{rev}(9, 2) + \text{rev}(9, 3)$。计算各项：
- $9 = 1001_2 \rightarrow \text{rev}(9, 2) = 1001_2 = 9$
- $9 = 100_3 \rightarrow \text{rev}(9, 3) = 001_3 = 1$
因此，$x = 9 + 1 = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
12
3 2
42 52
1 10
4 4
16 2
69 69
9 3
19 84
9982 44353
100000 1000000007
17 30
777 1000000000000000000
```

### 输出

```
3
7594
9
6
1
33471
10
2006
120792461
584502117
775
46058362
```



---

---
title: "La Vaca Saturno Saturnita"
layout: "post"
diff: 提高+/省选-
pid: CF2094H
tag: ['二分', '数论', '根号分治']
---

# La Vaca Saturno Saturnita

## 题目描述

Saturnita 的情绪取决于一个长度为 $n$ 的数组 $a$（只有他知道其含义）以及一个函数 $f(k, a, l, r)$（只有他知道如何计算）。以下是该函数的伪代码实现：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

给定 $q$ 个查询，每个查询包含整数 $k$、$l$ 和 $r$。对于每个查询，请输出 $f(k,a,l,r)$ 的值。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \leq n \leq 10^5$，$1 \leq q \leq 5 \cdot 10^4$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$2 \leq a_i \leq 10^5$）。

接下来的 $q$ 行，每行包含三个整数 $k$、$l$ 和 $r$（$1 \leq k \leq 10^5$，$1 \leq l \leq r \leq n$）。

保证所有测试用例的 $n$ 之和不超过 $10^5$，且所有测试用例的 $q$ 之和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个查询，在新的一行输出答案。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
2 3 5 7 11
2 1 5
2 2 4
2310 1 5
4 3
18 12 8 9
216 1 2
48 2 4
82944 1 4
```

### 输出

```
5
6
1629
13
12
520
```



---

