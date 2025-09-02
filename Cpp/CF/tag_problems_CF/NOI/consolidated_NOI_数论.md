---
title: "Become Big For Me"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1687E
tag: ['数论', '容斥原理', '构造']
---

# Become Big For Me

## 题目描述

> 『来吧，让我们构筑起一个不会遗弃弱者的乐园吧！』——少名针妙丸&鬼人正邪，《东方辉针城》

针妙丸有一个万宝槌，可以将物体变大或者变小。她现在在对一个序列 $a$ 测试这一功能。具体而言，她有一个实数 $v=1$，她希望在不超过 $10^5$ 次操作后，将 $v$ 变为 $\gcd \limits_{i \neq j} \{a_i \times a_j\}$。其中，$\gcd \limits_{i \neq j} \{a_i \times a_j\}$ 指的是，序列 $a$ 中两个不同元素相乘得到的所有乘积的最大公约数。

在每一次操作中，针妙丸可以选择序列 $a$ 中的一个子序列 $b$，并且对其做如下两种操作中的一个：

- 放大：令 $v \leftarrow v \times \operatorname{lcm(b)}$；
- 缩小：令 $v \leftarrow \dfrac{v}{\operatorname{lcm(b)}}$。

其中，$\operatorname{lcm(b)}$ 指的是序列 $b$ 中所有元素的最小公倍数。此外，她不要求 $v$ 一定是个整数，也就是说执行缩小操作的时候，$v$ 可以不是 $\operatorname{lcm(b)}$ 的倍数。

更进一步地说，针妙丸希望她选取的所有子序列 $b$ 的长度不超过 $10^6$，即 $\sum |b| \leq 10^6$。请你为她找到一种操作方案。注意，您无需最小化任何东西。

## 输入格式

第一行输入一个正整数 $n(2 \leq n \leq 10^5)$，表示序列 $a$ 的长度。

第二行输入 $n$ 个正整数 $a_1,a_2,\dots a_n(1 \leq a_i \leq 10^6)$。

保证最后的答案一定存在。

## 输出格式

第一行输出一个正整数 $k$，表示操作次数。

第二行开始往下输出 $k$ 行，每行包含若干个整数。对于每一行，首先输出两个整数 $f \in \{0,1\}$ 和 $p$，其中 $f=0$ 表示执行放大操作，而 $f=1$ 表示执行缩小操作。$p$ 表示所截取的子序列 $b$ 的长度。接下来是 $p$ 个正整数 $i_1,i_2,\dots,i_p(1 \leq i_1<i_2<\dots<i_p \leq n)$，表示所截取的子序列 $b$ 对应原序列 $a$ 的下标。形式化地说，$b_j=a_{i_j}$。

## 样例 #1

### 输入

```
3
6 10 15
```

### 输出

```
1
0 3 1 2 3
```

## 样例 #2

### 输入

```
4
2 4 8 16
```

### 输出

```
2
0 1 4
1 1 1
```



---

---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```



---

---
title: "Maximum GCD Sum Queries"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1973F
tag: ['动态规划 DP', '数论']
---

# Maximum GCD Sum Queries

## 题目描述

For $ k $ positive integers $ x_1, x_2, \ldots, x_k $ , the value $ \gcd(x_1, x_2, \ldots, x_k) $ is the greatest common divisor of the integers $ x_1, x_2, \ldots, x_k $ — the largest integer $ z $ such that all the integers $ x_1, x_2, \ldots, x_k $ are divisible by $ z $ .

You are given three arrays $ a_1, a_2, \ldots, a_n $ , $ b_1, b_2, \ldots, b_n $ and $ c_1, c_2, \ldots, c_n $ of length $ n $ , containing positive integers.

You also have a machine that allows you to swap $ a_i $ and $ b_i $ for any $ i $ ( $ 1 \le i \le n $ ). Each swap costs you $ c_i $ coins.

Find the maximum possible value of $ $$$\gcd(a_1, a_2, \ldots, a_n) + \gcd(b_1, b_2, \ldots, b_n) $ $  that you can get by paying in total at most  $ d $  coins for swapping some elements. The amount of coins you have changes a lot, so find the answer to this question for each of the  $ q $  possible values  $ d\_1, d\_2, \\ldots, d\_q$$$.

## 输入格式

There are two integers on the first line — the numbers $ n $ and $ q $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ , $ 1 \leq q \leq 5 \cdot 10^5 $ ).

On the second line, there are $ n $ integers — the numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^8 $ ).

On the third line, there are $ n $ integers — the numbers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 10^8 $ ).

On the fourth line, there are $ n $ integers — the numbers $ c_1, c_2, \ldots, c_n $ ( $ 1 \leq c_i \leq 10^9 $ ).

On the fifth line, there are $ q $ integers — the numbers $ d_1, d_2, \ldots, d_q $ ( $ 0 \leq d_i \leq 10^{15} $ ).

## 输出格式

Print $ q $ integers — the maximum value you can get for each of the $ q $ possible values $ d $ .

## 说明/提示

In the first query of the first example, we are not allowed to do any swaps at all, so the answer is $ \gcd(1, 2, 3) + \gcd(4, 5, 6) = 2 $ . In the second query, one of the ways to achieve the optimal value is to swap $ a_2 $ and $ b_2 $ , then the answer is $ \gcd(1, 5, 3) + \gcd(4, 2, 6) = 3 $ .

In the second query of the second example, it's optimal to perform swaps on positions $ 1 $ and $ 3 $ , then the answer is $ \gcd(3, 3, 6, 9, 3) + \gcd(8, 4, 4, 8, 4) = 7 $ and we have to pay $ 40 $ coins in total.

## 样例 #1

### 输入

```
3 4
1 2 3
4 5 6
1 1 1
0 1 2 3
```

### 输出

```
2 3 3 3
```

## 样例 #2

### 输入

```
5 5
3 4 6 8 4
8 3 4 9 3
10 20 30 40 50
5 55 13 1000 113
```

### 输出

```
2 7 3 7 7
```

## 样例 #3

### 输入

```
1 1
3
4
5
0
```

### 输出

```
7
```



---

---
title: "Zimpha Fan Club"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1975G
tag: ['快速数论变换 NTT']
---

# Zimpha Fan Club

## 题目描述

One day, Zimpha casually came up with a problem. As a member of "Zimpha fan club", you decided to solve that problem.

You are given two strings $ s $ and $ t $ of length $ n $ and $ m $ , respectively. Both strings only consist of lowercase English letters, - and \*.

You need to replace all occurrences of \* and -, observing the following rules:

- For each -, you must replace it with any lowercase English letter.
- For each \*, you must replace it with a string of any (possibly, zero) length which only consists of lowercase English letters.

Note that you can replace two different instances of - with different characters. You can also replace each two different instances of \* with different strings.

Suppose $ s $ and $ t $ have been transformed into $ s' $ and $ t' $ . Now you're wondering if there's a replacement that makes $ s'=t' $ .

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 2 \cdot 10^6 $ ) — the length of the strings $ s $ and $ t $ , respectively.

The second line contains the string $ s $ of length $ n $ . It is guaranteed that $ s $ only consists of lowercase English letters, - and \*.

The third line contains the string $ t $ of length $ m $ . It is guaranteed that $ t $ only consists of lowercase English letters, - and \*.

## 输出格式

For each test case, output "Yes" if there is a replacement that makes $ s'=t' $ , and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the second test case, we can transform both strings into ttklwxx. In $ s $ , - will be replaced with l. In $ t $ , \* will be replaced by the empty string with the first and second - will be replaced with k and w respectively.

In the fifth test case, we can transform both strings into bulijiojioxdibuliduo.

## 样例 #1

### 输入

```
10 10
justmonika
j-stsayori
```

### 输出

```
No
```

## 样例 #2

### 输入

```
7 8
ttk-wxx
*tt-l-xx
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
13 11
asoulwangziji
-soulg*z-y-
```

### 输出

```
No
```

## 样例 #4

### 输入

```
7 3
abc*cba
a*c
```

### 输出

```
No
```

## 样例 #5

### 输入

```
20 18
bulijiojio-dibuliduo
*li*ji-*ox*i*-du*-
```

### 输出

```
Yes
```



---

---
title: "Prime Split Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1991H
tag: ['博弈论', '数论']
---

# Prime Split Game

## 题目描述

Alice and Bob are playing a game with $ n $ piles of stones, where the $ i $ -th pile has $ a_i $ stones. Players take turns making moves, with Alice going first.

On each move, the player does the following three-step process:

1. Choose an integer $ k $ ( $ 1 \leq k \leq \frac n 2 $ ). Note that the value of $ k $ can be different for different moves.
2. Remove $ k $ piles of stones.
3. Choose another $ k $ piles of stones and split each pile into two piles. The number of stones in each new pile must be a prime number.

The player who is unable to make a move loses.

Determine who will win if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of piles of stones.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ) — the number of stones in the piles.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "Alice" (without quotes) if Alice wins and "Bob" (without quotes) otherwise.

You can output each letter in any case (upper or lower). For example, the strings "alIcE", "Alice", and "alice" will all be considered identical.

## 说明/提示

In the first test case, there are $ 2 $ piles of stones with $ 2 $ and $ 1 $ stones respectively. Since neither $ 1 $ nor $ 2 $ can be split into two prime numbers, Alice cannot make a move, so Bob wins.

In the second test case, there are $ 3 $ piles of stones with $ 3 $ , $ 5 $ , and $ 7 $ stones respectively. Alice can choose $ k = 1 $ , remove the pile of $ 7 $ stones, and then split the pile of $ 5 $ stones into two piles of prime numbers of stones, $ 2 $ and $ 3 $ . Then, the piles consist of $ 3 $ piles of stones with $ 3 $ , $ 2 $ , and $ 3 $ stones respectively, leaving Bob with no valid moves, so Alice wins.

In the third test case, there are $ 4 $ piles of stones with $ 4 $ , $ 6 $ , $ 8 $ , and $ 10 $ stones respectively. Alice can choose $ k = 2 $ , removing two piles of $ 8 $ and $ 10 $ stones. She splits the pile of $ 4 $ stones into two piles of prime numbers of stones, $ 2 $ and $ 2 $ , and the pile of $ 6 $ stones into two piles of $ 3 $ and $ 3 $ stones. Then, Bob has no valid moves, so Alice wins.

In the fourth test case, there are $ 5 $ piles of stones, each containing $ 8 $ stones. It can be shown that if both players play optimally, Bob will win.

## 样例 #1

### 输入

```
4
2
2 1
3
3 5 7
4
4 6 8 10
5
8 8 8 8 8
```

### 输出

```
Bob
Alice
Alice
Bob
```



---

---
title: "Rayan vs. Rayaneh"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034H
tag: ['数论']
---

# Rayan vs. Rayaneh

## 题目描述

为了赢得 Reyhaneh 的芳心，Rayan 宣称自己比计算机（波斯语中称为 Rayaneh）更强。为了验证他的说法，Reyhaneh 请教了 Khwarizmi。Khwarizmi 解释道，一个整数集合如果集合中的任何一个元素都不能表示为其他元素的整数线性组合，则称为整数线性无关。 Rayan 每次收到一个整数集合，他的任务是找出其中一个尽可能大的整数线性无关子集。

值得注意的是，单个元素始终被认为是整数线性无关的子集。

对于整数 $ a_1, \ldots, a_k $，它们的整数线性组合是形式为 $ c_1 \cdot a_1 + c_2 \cdot a_2 + \ldots + c_k \cdot a_k $ 的任何和式，这里 $ c_1, c_2, \ldots, c_k $ 为整数（可以是零、正数或负数）。

## 输入格式

第一行输入一个整数 $ t $（$ 1 \leq t \leq 100 $），表示测试用例的数量。

接下来每个测试用例第一行包含一个整数 $ n $（$ 1 \leq n \leq 10^5 $），表示这个集合的大小。第二行包含 $ n $ 个互不相同的整数 $ a_1, a_2, \ldots, a_n $（$ 1 \leq a_i \leq 10^5 $）。

所有测试用例中的整数总数（即 $ n $ 的总和）不超过 $ 3 \cdot 10^6 $。

## 输出格式

对于每个测试用例，第一行输出最大整数线性无关子集的元素数量。

在第二行，以任意顺序输出该子集。如果有多个符合条件的子集，任意输出一个即可。

## 说明/提示

例子 1 中，集合 $\{4, 6\}$ 是一个整数线性无关的子集。可以证明不存在包含至少 3 个元素的整数线性无关子集。

例子 2 中，集合 $\{35, 21, 30\}$ 是一个整数线性无关的子集，因为任意两个元素的整数线性组合无法生成第三个元素。没有包含至少 4 个元素的整数线性无关子集。

例子 3 中，集合 $\{2, 3, 6\}$ 并不是一个整数线性无关的子集，因为 6 可以表示为 $ 6 \cdot 2 + (-2) \cdot 3 $，这是 $\{2, 3\}$ 的整数线性组合。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
2 4 6 8 10
5
12 15 21 30 35
3
2 3 6
```

### 输出

```
2
4 6
3
35 21 30
2
2 3
```



---

---
title: "Shohag Loves Counting (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2039F2
tag: ['矩阵运算', '数论', '莫比乌斯反演']
---

# Shohag Loves Counting (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ t $ , $ m $ , and the sum of $ m $ . You can only make hacks if both versions of the problem are solved.

For an integer array $ a $ of length $ n $ , define $ f(k) $ as the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the maximum values of all subarrays $ ^{\text{∗}} $ of length $ k $ . For example, if the array is $ [2, 1, 4, 6, 2] $ , then $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4]), \operatorname{max}([1, 4, 6]), \operatorname{max}([4, 6, 2])) = \operatorname{gcd}(4, 6, 6) = 2 $ .

An array is good if $ f(i) \neq f(j) $ is satisfied over all pairs $ 1 \le i \lt j \le n $ .

Shohag has an integer $ m $ . Help him count the number, modulo $ 998\,244\,353 $ , of non-empty good arrays of arbitrary length such that each element of the array is an integer from $ 1 $ to $ m $ .

 $ ^{\text{∗}} $ An array $ d $ is a subarray of an array $ c $ if $ d $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 3 \cdot 10^5 $ ) — the number of test cases.

The first and only line of each test case contains an integer $ m $ ( $ 1 \le m \le 10^6 $ ).

Note that there is no limit on the sum of $ m $ over all test cases.

## 输出格式

For each test case, output an integer — the number of valid arrays modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the valid arrays are $ [1] $ , $ [1, 2] $ , $ [2] $ , and $ [2, 1] $ .

In the second test case, there are a total of $ 29 $ valid arrays. In particular, the array $ [2, 1, 4] $ with length $ n = 3 $ is valid because all elements are from $ 1 $ to $ m = 5 $ and $ f(1) $ , $ f(2) $ and $ f(n = 3) $ all are distinct:

- $ f(1) = \operatorname{gcd}(\operatorname{max}([2]), \operatorname{max}([1]), \operatorname{max}([4])) = \operatorname{gcd}(2, 1, 4) = 1. $
- $ f(2) = \operatorname{gcd}(\operatorname{max}([2, 1]), \operatorname{max}([1, 4])) = \operatorname{gcd}(2, 4) = 2. $
- $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4])) = \operatorname{gcd}(4) = 4. $

## 样例 #1

### 输入

```
3
2
5
9
```

### 输出

```
4
29
165
```



---

---
title: "Shohag Loves Pebae"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2039G
tag: ['数论', '标签475']
---

# Shohag Loves Pebae

## 题目描述

# Shohag Loves Pebae


Shohag 有一棵有 $ n $ 个节点的树。

Pebae 有一个整数 $ m $。 她想给每个节点赋一个值--一个从 $ 1 $ 到 $ m $ 的整数。 所以她要求 Shohag 计算出，模数为 $ 998\,244\,353 $ 的赋值中，满足以下条件的赋值个数：

- 对于每一对 $ 1 \le u \lt v \le n $ ，从 $ u $ 到 $ v $ 的唯一简单路径中节点值的 [最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) 不能被路径中的节点数整除。
- 从 $ 1 $ 到 $ n $ 的所有节点值的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor) 是 $ 1 $ 。

但这个问题对 Shohag 来说太难了。因为 Shohag 喜欢 Pebae，所以他必须解决这个问题。请救救 Shohag！

## 输入格式

第一行包含两个整数 $ n $ 和 $ m $ ( $ 2 \le n \le 10^6 $ , $ 1 \le m \le 10^{9} $ )。

接下来的每一行 $ n - 1 $ 包含两个整数 $ u $ 和 $ v $ ( $ 1 \le u, v \le n $ ) 表示顶点 $ u $ 和 $ v $ 之间有一条边。 保证给定的边构成一棵树。

## 输出格式

输出一个整数，为每个顶点赋值的有效方式的数量，数过大时要 $\bmod 998\,244\,353 $ 。

## 样例 #1

### 样例输入 #1

```
6 6
1 2
2 3
3 4
4 5
3 6
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 5
1 2
```

### 样例输出 #2

```
7
```

## 样例 #3

### 样例输入 #3

```
12 69
3 5
1 4
2 3
4 5
5 6
8 9
7 3
4 8
9 10
1 11
12 1
```

### 样例输出 #3

```
444144548
```

## 说明/提示

样例一中，有效赋值是 $ [1, 1, 1, 1, 1] $ 和 $ [1, 1, 1, 1, 5] $ 。

样例二中，有效赋值是 $ [1, 1] $ , $ [1, 3] $ , $ [1, 5] $ , $ [3, 1] $ , $ [3, 5] $ , $ [5, 1] $ 和 $ [5, 3] $ 。

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 4
4 5
3 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5
1 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
12 69
3 5
1 4
2 3
4 5
5 6
8 9
7 3
4 8
9 10
1 11
12 1
```

### 输出

```
444144548
```



---

---
title: "Grid Game 3-angle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045F
tag: ['博弈论', '数论']
---

# Grid Game 3-angle

## 题目描述

Anda 和 Kamu 决定玩一个叫作「网格游戏」的游戏，并请你来做裁判。作为裁判，你需要设置一个大小为 $N$ 的三角形网格。这个网格共有 $N$ 行（从 $1$ 到 $N$ 编号）。第 $r$ 行有 $r$ 个格子，第 $r$ 行的第 $c$ 个格子记作 $(r, c)$。

![示例图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/d40475d9abd66fd4b8b1753d7ed7b9ab45f87e16.png)

在开始游戏前，有 $M$ 个不同的格子被选中（编号从 $1$ 到 $M$），并在格子 $(R_i, C_i)$ 上放置 $A_i$ 颗石子。随后，你给 Anda 和 Kamu 一个整数 $K$，游戏随即开始。

玩家 Anda 和 Kamu 轮流进行游戏，由 Anda 先手。每个玩家在他的回合中必须：

- 选择一个至少包含一颗石子的格子 $(r, c)$；
- 从该格子中移除至少一颗但不超过 $K$ 颗石子；
- 对于每个满足 $r + 1 \leq x \leq \min(N, r + K)$ 且 $c \leq y \leq c + x - r$ 的格子 $(x, y)$，可以向其中添加零颗或多颗，但不超过 $K$ 颗的石子。

下图显示了当 $K = 3$ 时，可以添加石子的所有可能格子。左图选择了 $(2, 1)$，右图选择了 $(4, 3)$。

![示例图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/b2d9c6a56735a1903fa39837671da9d8b4751eac.png)

无法进行有效回合（即因为没有足够的石子）的一方将输掉比赛，而对方将获胜。请判断，如果双方都采取最佳策略，谁将赢得比赛。

## 输入格式

本题包含多组测试数据。第一行是一个整数 $T$（$1 \leq T \leq 100$），表示测试数据的组数。

每组测试数据的第一行包含三个整数 $N$、$M$ 和 $K$（$1 \leq N \leq 10^9; 1 \leq M, K \leq 200\,000$）。接下来的 $M$ 行中，每行包含三个整数 $R_i$、$C_i$ 和 $A_i$（$1 \leq C_i \leq R_i \leq N; 1 \leq A_i \leq 10^9$）。每对 $(R_i, C_i)$ 都是独特的。

所有测试数据中 $M$ 的总和不超过 $200\,000$。

## 输出格式

对于每组测试数据，输出一行字符串，表示如果双方都采取最佳策略，哪位玩家将赢得比赛。如果 Anda 获胜，输出“Anda”；否则，输出“Kamu”。

## 示例说明

对于第一个例子，Anda 在第一回合将从格子 $(1, 1)$ 移除所有石子，然后在 $(2, 1)$ 添加三颗石子。此时，唯一剩余的有石子的格子是 $(2, 1)$，其中有五颗石子，因此 Kamu 必须在该回合中从中移除石子。无论 Kamu 移除多少，Anda 都能在随后一回合中移除剩下的所有石子，从而赢得比赛。

对于第二个例子，Kamu 可以通过模仿 Anda 的所有操作，即使 Anda 无法完成回合，使得自己成为胜利者。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 2 4
1 1 3
2 1 2
100 2 1
4 1 10
4 4 10
10 5 2
1 1 4
3 1 2
4 2 5
2 2 1
5 3 4
```

### 输出

```
Anda
Kamu
Anda
```



---

---
title: "GCDDCG"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045K
tag: ['数论', '容斥原理']
---

# GCDDCG

## 题目描述

你正在参加一场名为“最大公约数牌组构建”的卡牌游戏。这款游戏中共有 $N$ 张牌（编号从 $1$ 到 $N$），第 $i$ 张牌的点数为 $A_i$，其中 $A_i$ 是 $1$ 到 $N$ 之间的整数（包括 $1$ 和 $N$）。

游戏由 $N$ 轮组成（从第 $1$ 轮到第 $N$ 轮）。在每一轮中，玩家需要将牌分成两个非空牌组：牌组 $1$ 和牌组 $2$。每一张牌不能同时出现在两个牌组里，并且允许有些牌不用。第 $i$ 轮的要求是，两个牌组中每个牌组的牌值的最大公约数（GCD）都要等于 $i$。

在第 $i$ 轮，你的创造力点数等于 $i$ 乘以可以构建这两个有效牌组的方案数。如果其中一个牌组的组成不同，那么视为不同的方案。

请计算所有 $N$ 轮中创造力点数的总和。因为这个总和可能会非常大，结果需要对 $998\,244\,353$ 取模。

## 输入格式

第一行是一个整数 $N$，表示牌的数量 ($2 \leq N \leq 200,000$)。

第二行包含 $N$ 个整数 $A_i$，表示每张牌的点数 ($1 \leq A_i \leq N$)。

## 输出格式

输出一个整数，即所有 $N$ 轮中创造力点数的总和对 $998,244,353$ 取模后的结果。

## 说明/提示

在样例输入/输出 #1 中，第 $1$ 轮和第 $2$ 轮的创造力点数均为 $0$。

在第 $3$ 轮，有 $12$ 种构建两个牌组的方法。记 $B$ 和 $C$ 为牌组 $1$ 和牌组 $2$ 中各自的牌号集合。这 $12$ 种方法包括：

- $B = \{ 1 \}, C = \{ 2 \}$
- $B = \{ 1 \}, C = \{ 3 \}$
- $B = \{ 1 \}, C = \{ 2, 3 \}$
- $B = \{ 2 \}, C = \{ 1 \}$
- $B = \{ 2 \}, C = \{ 3 \}$
- $B = \{ 2 \}, C = \{ 1, 3 \}$
- $B = \{ 3 \}, C = \{ 1 \}$
- $B = \{ 3 \}, C = \{ 2 \}$
- $B = \{ 3 \}, C = \{ 1, 2 \}$
- $B = \{ 1, 2 \}, C = \{ 3 \}$
- $B = \{ 2, 3 \}, C = \{ 1 \}$
- $B = \{ 1, 3 \}, C = \{ 2 \}$

在样例输入/输出 #2 中，第 $1$、$2$、$3$ 和 $4$ 轮中的构建方案数分别为 $0$、$18$、$0$ 和 $2$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 3 3
```

### 输出

```
36
```

## 样例 #2

### 输入

```
4
2 2 4 4
```

### 输出

```
44
```

## 样例 #3

### 输入

```
9
4 2 6 9 7 7 7 3 3
```

### 输出

```
10858
```



---

---
title: "RGB Walking"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2077G
tag: ['数论']
---

# RGB Walking

## 题目描述

[Red and Blue and Green - fn and Silentroom](https://www.youtube.com/watch?v=UeN7U474cxE)

给定一个包含 $n$ 个顶点和 $m$ 条双向边的连通图，每条边的权重不超过 $x$。第 $i$ 条边连接顶点 $u_i$ 和 $v_i$，权重为 $w_i$，颜色为 $c_i$（$1 \leq i \leq m$，$1 \leq u_i, v_i \leq n$）。颜色 $c_i$ 为红色（red）、绿色（green）或蓝色（blue）。保证图中至少存在一条每种颜色的边。

对于一条允许重复顶点和边的路径，设 $s_r$、$s_g$、$s_b$ 分别表示路径中经过的红色、绿色和蓝色边的权重之和。若某条边被多次遍历，每次遍历均会被单独计数。

请找到从顶点 $1$ 到顶点 $n$ 的所有可能路径中，$\max(s_r, s_g, s_b) - \min(s_r, s_g, s_b)$ 的最小值。


## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行输入三个整数 $n$、$m$ 和 $x$（$4 \leq n \leq 2 \cdot 10^5$，$n-1 \leq m \leq 2 \cdot 10^5$，$1 \leq x \leq 2 \cdot 10^5$）——分别表示顶点数量、边的数量和边权重的上限。

接下来的 $m$ 行每行输入三个整数 $u_i, v_i, w_i$ 和一个字符 $c_i$（$1 \leq u_i, v_i \leq n$，$1 \leq w_i \leq x$），表示一条连接顶点 $u_i$ 和 $v_i$ 的双向边，其权重为 $w_i$，颜色为 $c_i$。颜色 $c_i$ 为 'r'、'g' 或 'b'，分别代表红色、绿色和蓝色。

保证图是连通的且至少包含一条每种颜色的边。图中可能存在重边和自环。

此外，保证所有测试用例的 $n$ 总和、$m$ 总和以及 $x$ 总和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——从顶点 $1$ 到顶点 $n$ 的所有路径中 $\max(s_r, s_g, s_b) - \min(s_r, s_g, s_b)$ 的最小值。

## 说明/提示

第一个测试用例中，最优路径为 $1 \to 2 \to 3 \to 4$。使用的边依次为：
- $1 \to 2$（红色，权重 $2$）
- $2 \to 3$（绿色，权重 $3$）
- $3 \to 4$（蓝色，权重 $2$）

此时 $s_r = 2$，$s_g = 3$，$s_b = 2$，因此答案为 $1$。

第二个测试用例中，一条最优路径为 $1 \to 1 \to 2 \to 1 \to 2 \to 3 \to 4$。使用的边依次为：
- $1 \to 1$（红色，权重 $1$）
- $1 \to 2$（红色，权重 $1$）
- $2 \to 1$（红色，权重 $1$）
- $1 \to 2$（红色，权重 $1$）
- $2 \to 3$（绿色，权重 $4$）
- $3 \to 4$（蓝色，权重 $4$）

此时 $s_r = s_g = s_b = 4$，因此答案为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 3 3
1 2 2 r
2 3 3 g
3 4 2 b
4 5 4
1 2 1 r
1 1 1 r
2 1 1 r
2 3 4 g
3 4 4 b
4 6 4
1 2 2 r
1 2 2 r
2 3 3 b
1 3 4 r
1 4 1 g
3 4 4 g
```

### 输出

```
1
0
0
```



---

---
title: "Hard Formula"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2081G1
tag: ['数论', '标签475']
---

# Hard Formula

## 题目描述

这是本题的简单版本。两个版本的区别在于此版本对 $n$ 的限制和时间限制更小。只有当您解决了该问题的所有版本时才能进行 hack。

给定一个整数 $n$，你需要计算 $(\sum_{k=1}^n k \bmod \varphi(k)) \bmod 2^{32}$，其中 $\varphi(k)$ 表示不大于 $k$ 且与 $k$ 互质的正整数的数量。

## 输入格式

输入仅包含一个整数 $n$（$1 \le n \le 10^{10}$）。

## 输出格式

输出一个整数，表示 $(\sum_{k=1}^n k \bmod \varphi(k)) \bmod 2^{32}$ 的值。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10000000
```

### 输出

```
2316623097
```

## 样例 #3

### 输入

```
10000000000
```

### 输出

```
282084447
```



---

---
title: "Hard Formula (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2081G2
tag: ['数论', '标签461', '标签475']
---

# Hard Formula (Hard Version)

## 题目描述

这是本题的困难版本。两个版本的区别在于此版本对 $n$ 的限制和时间限制更高。只有当您解决了该问题的所有版本时才能进行 hack。

给定一个整数 $n$，你需要计算 $(\sum_{k=1}^n k \bmod \varphi(k)) \bmod 2^{32}$，其中 $\varphi(k)$ 表示不大于 $k$ 且与 $k$ 互质的正整数的数量。

## 输入格式

输入仅包含一个整数 $n$（$1 \le n \le 10^{12}$）。

## 输出格式

输出一个整数，表示 $(\sum_{k=1}^n k \bmod \varphi(k)) \bmod 2^{32}$ 的值。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10000000
```

### 输出

```
2316623097
```

## 样例 #3

### 输入

```
10000000000
```

### 输出

```
282084447
```



---

