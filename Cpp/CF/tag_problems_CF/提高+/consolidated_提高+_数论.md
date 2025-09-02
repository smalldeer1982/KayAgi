---
title: "Please, another Queries on Array?"
layout: "post"
diff: 提高+/省选-
pid: CF1114F
tag: ['线段树', '数论']
---

# Please, another Queries on Array?

## 题目描述

你有一个数组 $a_1,a_2,\cdots,a_n$。

现在你需要完成 $q$ 次操作，有以下两种操作形式：

1. `MULTIPLY l r x`，对于所有 $i(l\le i\le r)$，将 $a_i$ 乘上 $x$。

2. `TOTIENT l r`，求出 $\varphi(\prod_{i=l}^ra_i)$，对 $10^9+7$ 取模后的结果。其中 $\varphi$ 表示欧拉函数，$\varphi(n)$ 的定义为 $1\cdots n$ 中与 $n$ 互质的数的个数。


保证数据中至少有一次操作 $2$。

## 输入格式

输入的第一行有两个数 $n,q$，保证 $1\le n\le 4\times10^5,1\le q\le 2\times 10^5$，表示序列的长度以及询问的个数。

第二行是 $n$ 个数 $a_i$ 表示序列，满足 $1\le a_i\le 300$。

## 输出格式

对于每一个操作 $2$ 输出一行，表示答案。

## 说明/提示

在样例中：  
对于第 $1$ 个询问 $\varphi(1)=1$；  
对于第 $2$ 个询问 $\varphi(2)=1$；  
对于第 $3$ 个询问 $\varphi(6)=2$。

## 样例 #1

### 输入

```
4 4
5 9 1 2
TOTIENT 3 3
TOTIENT 3 4
MULTIPLY 4 4 3
TOTIENT 4 4

```

### 输出

```
1
1
2

```



---

---
title: "Power Board"
layout: "post"
diff: 提高+/省选-
pid: CF1646E
tag: ['数论']
---

# Power Board

## 题目描述

You have a rectangular board of size $ n\times m $ ( $ n $ rows, $ m $ columns). The $ n $ rows are numbered from $ 1 $ to $ n $ from top to bottom, and the $ m $ columns are numbered from $ 1 $ to $ m $ from left to right.

The cell at the intersection of row $ i $ and column $ j $ contains the number $ i^j $ ( $ i $ raised to the power of $ j $ ). For example, if $ n=3 $ and $ m=3 $ the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/f966495b3fd71da241cb3a79e264d10b59256e95.png)Find the number of distinct integers written on the board.

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1\le n,m\le 10^6 $ ) — the number of rows and columns of the board.

## 输出格式

Print one integer, the number of distinct integers on the board.

## 说明/提示

The statement shows the board for the first test case. In this case there are $ 7 $ distinct integers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 8 $ , $ 9 $ , and $ 27 $ .

In the second test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/36fd681eff28bb5ca921155ad4010ac8be1c65a1.png)There are $ 5 $ distinct numbers: $ 1 $ , $ 2 $ , $ 4 $ , $ 8 $ and $ 16 $ .

In the third test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/a5987da66d8c80ffc8e49f428e2b3197bf00bc43.png)There are $ 6 $ distinct numbers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 9 $ and $ 16 $ .

## 样例 #1

### 输入

```
3 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4 2
```

### 输出

```
6
```



---

---
title: "Madoka and The Best University"
layout: "post"
diff: 提高+/省选-
pid: CF1717E
tag: ['数论', '素数判断,质数,筛法']
---

# Madoka and The Best University

## 题目描述

Madoka wants to enter to "Novosibirsk State University", but in the entrance exam she came across a very difficult task:

Given an integer $ n $ , it is required to calculate $ \sum{\operatorname{lcm}(c, \gcd(a, b))} $ , for all triples of positive integers $ (a, b, c) $ , where $ a + b + c = n $ .

In this problem $ \gcd(x, y) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of $ x $ and $ y $ , and $ \operatorname{lcm}(x, y) $ denotes the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of $ x $ and $ y $ .

Solve this problem for Madoka and help her to enter to the best university!

## 输入格式

The first and the only line contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ).

## 输出格式

Print exactly one interger — $ \sum{\operatorname{lcm}(c, \gcd(a, b))} $ . Since the answer can be very large, then output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, there is only one suitable triple $ (1, 1, 1) $ . So the answer is $ \operatorname{lcm}(1, \gcd(1, 1)) = \operatorname{lcm}(1, 1) = 1 $ .

In the second example, $ \operatorname{lcm}(1, \gcd(3, 1)) + \operatorname{lcm}(1, \gcd(2, 2)) + \operatorname{lcm}(1, \gcd(1, 3)) + \operatorname{lcm}(2, \gcd(2, 1)) + \operatorname{lcm}(2, \gcd(1, 2)) + \operatorname{lcm}(3, \gcd(1, 1)) = \operatorname{lcm}(1, 1) + \operatorname{lcm}(1, 2) + \operatorname{lcm}(1, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(2, 1) + \operatorname{lcm}(3, 1) = 1 + 2 + 1 + 2 + 2 + 3 = 11 $

## 样例 #1

### 输入

```
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
```

### 输出

```
11
```

## 样例 #3

### 输入

```
69228
```

### 输出

```
778304278
```



---

---
title: "Josuke and Complete Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1780E
tag: ['数论', '最大公约数 gcd']
---

# Josuke and Complete Graph

## 题目描述

Josuke 收到了一个巨大的无向带权完全图 $G$ 作为他祖父的礼物。该图形包含$10^{18}$ 个顶点。

这个礼物的特点是不同顶点 $u$ 和 $v$ 之间的边的权重等于 $\gcd(u,v)$ 。

Josuke 决定制作一个新的图 $G'$。为此，他选择两个整数 $l\le r$ ，并删除除 $l\le v\le r$ 的顶点 $v$ 之外的所有顶点以及与其相连的边。

现在 Josuke 想知道 $G'$ 中有的边多少种不同的权重。

## 输入格式

第 $1$ 行一个整数 $t\;(1\le t\le100)$ ，表示数据组数。

接下来 $t$ 行每行两个整数 $l,r\;(1\le l\le r\le10^{18},l\le10^9\;)$ ，表示一组数据中的 $l,r$ 。

## 输出格式

每行一个整数，表示每组数据 $G'$ 中不同权重的边的数量。

Translated by @[w9095](https://www.luogu.com.cn/user/569235)

## 样例 #1

### 输入

```
7
2 4
16 24
2 6
1 10
3 3
2562 2568
125 100090
```

### 输出

```
2
6
3
5
0
5
50045
```



---

---
title: "Game of the Year"
layout: "post"
diff: 提高+/省选-
pid: CF1783E
tag: ['数学', '贪心', '树状数组', '数论', '前缀和', 'ST 表']
---

# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 输入格式

第一行输入一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) — 样例数。

每个样例第一行输入一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — BOSS的数量。

每个样例第二行输入 $ n $ 个整数： $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — Monocarp 撒死每只BOSS的尝试次数。

每个样例第三行输入 $ n $ 个整数： $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ) — Polycarp 撒死每只BOSS的尝试次数。

所有测试样例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个样例输出两行。第一行应该包含一个正整数 $ \mathit{cnt} $ — 从 $ 1 $ 到 $ n $ 使得 Monocarp 可以撒死所有BOSS的 $ k $ 的总数。第二行应该包含 $ \mathit{cnt} $ 个正整数 — 所有 $ k $ 的值。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1
```

### 输出

```
3
1 2 3 
1
1 
2
2 4
```



---

---
title: "Divisors and Table"
layout: "post"
diff: 提高+/省选-
pid: CF1792E
tag: ['数论', '素数判断,质数,筛法', '构造']
---

# Divisors and Table

## 题目描述

给定一张 $n \times n$ 的表格和一个正整数 $m = m_1 \times m_2$，表格第 $i$ 行第 $j$ 列的数 $a_{i, j} = i \times j$。

现在需要你求出 $m$ 的每个因子 $d$ 是否在表格中出现，若出现，则求出其出现在表格中的最小行号。

## 输入格式

第一行一个整数 $t$，表示测试用例的组数。

## 输出格式

对于每组测试用例，设 $d_1, d_2, \dots, d_k$ 为升序排序下 $m$ 的所有因子，$a_1, a_2, \dots, a_k$ 为这些因子在表格中出现的最小行号，特殊地，若 $d_i$ 不在表格中出现，则 $a_i = 0$。

输出一行两个整数 $s, X$。其中 $s$ 表示 $m$ 的因子在表格中出现的个数，$X$ 表示答案序列的异或和，形式化地，$X = a_1 \oplus a_2 \oplus \dots \oplus a_k$。

## 样例 #1

### 输入

```
3
3 72 1
10 10 15
6 1 210
```

### 输出

```
6 2
10 0
8 5
```



---

---
title: "Large Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1978F
tag: ['并查集', '数论']
---

# Large Graph

## 题目描述

Given an array $ a $ of length $ n $ . Let's construct a square matrix $ b $ of size $ n \times n $ , in which the $ i $ -th row contains the array $ a $ cyclically shifted to the right by $ (i - 1) $ . For example, for the array $ a = [3, 4, 5] $ , the obtained matrix is

 $ $$$b = \begin{bmatrix} 3 & 4 & 5 \\ 5 & 3 & 4 \\ 4 & 5 & 3 \end{bmatrix} $ $ </p><p>Let's construct the following graph:</p><ul> <li> The graph contains  $ n^2 $  vertices, each of which corresponds to one of the elements of the matrix. Let's denote the vertex corresponding to the element  $ b\_{i, j} $  as  $ (i, j) $ .</li><li> We will draw an edge between vertices  $ (i\_1, j\_1) $  and  $ (i\_2, j\_2) $  if  $ |i\_1 - i\_2| + |j\_1 - j\_2| \\le k $  and  $ \\gcd(b\_{i\_1, j\_1}, b\_{i\_2, j\_2}) &gt; 1 $ , where  $ \\gcd(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a> of integers  $ x $  and  $ y $ . </li></ul><p>Your task is to calculate the number of connected components $ ^{\\dagger} $  in the obtained graph.</p><p> $ ^{\\dagger}$$$A connected component of a graph is a set of vertices in which any vertex is reachable from any other via edges, and adding any other vertex to the set violates this rule.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^6 $ , $ 2 \le k \le 2 \cdot 10^6 $ ) — the length of the array and the parameter $ k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the number of connected components in the obtained graph.

## 说明/提示

In the first test case, the matrix $ b $ is given in the statement. The first connected component contains the vertices $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ . The second connected component contains the vertices $ (1, 2) $ , $ (2, 3) $ , and $ (3, 1) $ . The third connected component contains the vertices $ (1, 3) $ , $ (2, 1) $ , and $ (3, 2) $ . Thus, the graph has $ 3 $ connected components.

In the second test case, the following matrix is obtained:

 $ $$$b = \begin{bmatrix} 3 & 4 & 9 \\ 9 & 3 & 4 \\ 4 & 9 & 3 \end{bmatrix} $ $ </p><p>The first connected component contains all vertices corresponding to elements with values  $ 3 $  and  $ 9 $ . The second connected component contains all vertices corresponding to elements with the value  $ 4$$$.

In the fourth test case, all vertices are in one connected component.

## 样例 #1

### 输入

```
6
3 3
3 4 5
3 3
3 4 9
3 2
3 4 9
2 2
2 8
5 3
8 27 5 4 3
4 10
2 2 2 2
```

### 输出

```
3
2
3
1
4
1
```



---

---
title: "Permutation Problem (Simple Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1986G1
tag: ['数论']
---

# Permutation Problem (Simple Version)

## 题目描述

This is a simple version of the problem. The only difference is that in this version $ n \leq 10^5 $ and the sum of $ n $ for all sets of input data does not exceed $ 10^5 $ .

You are given a permutation $ p $ of length $ n $ . Calculate the number of index pairs $ 1 \leq i < j \leq n $ such that $ p_i \cdot p_j $ is divisible by $ i \cdot j $ without remainder.

A permutation is a sequence of $ n $ integers, where each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

## 输入格式

Each test consists of multiple sets of input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of sets of input data. Then follows their description.

The first line of each set of input data contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the permutation $ p $ .

The second line of each set of input data contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n $ ) — the permutation $ p $ .

It is guaranteed that the sum of $ n $ for all sets of input data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output the number of index pairs $ 1 \leq i < j \leq n $ such that $ p_i \cdot p_j $ is divisible by $ i \cdot j $ without remainder.

## 说明/提示

In the first set of input data, there are no index pairs, as the size of the permutation is $ 1 $ .

In the second set of input data, there is one index pair $ (1, 2) $ and it is valid.

In the third set of input data, the index pair $ (1, 2) $ is valid.

In the fourth set of input data, the index pairs $ (1, 2) $ , $ (1, 5) $ , and $ (2, 5) $ are valid.

## 样例 #1

### 输入

```
6
1
1
2
1 2
3
2 3 1
5
2 4 1 3 5
12
8 9 7 12 1 10 6 3 2 4 11 5
15
1 2 4 6 8 10 12 14 3 9 15 5 7 11 13
```

### 输出

```
0
1
1
3
9
3
```



---

---
title: "Court Blue (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2002F1
tag: ['数论']
---

# Court Blue (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ n=m $ and the time limit is lower. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 输入格式

The first line contains an integer $ t $ ( $ 1\leq t \leq 10^3 $ ) — the number of test cases.

The only line of each test case contains four integers $ n $ , $ m $ , $ l $ , $ f $ ( $ 2\leq n\leq m \leq 2\cdot 10^7 $ , $ 1\leq l,f \leq 10^9 $ , $ \bf{n=m} $ ): $ n $ , $ m $ gives the upper bound on the number of Lelle and Flamm's wins, $ l $ and $ f $ determine the final score of the performance.

Unusual additional constraint: it is guaranteed that, for each test, there are no pairs of test cases with the same pair of $ n $ , $ m $ .

## 输出格式

For each test case, output a single integer — the maximum total score of a successful performance.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Lelle wins, $ \gcd(2,3)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 2\cdot2+3\cdot5=19 $ .

In the third test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Lelle wins, $ \gcd(2,1)=1 $ .
- Lelle wins, $ \gcd(3,1)=1 $ .
- Lelle wins, $ \gcd(4,1)=1 $ .
- Lelle wins, $ \gcd(5,1)=1 $ .
- Flamm wins, $ \gcd(5,2)=1 $ .
- Flamm wins, $ \gcd(5,3)=1 $ .
- Flamm wins, $ \gcd(5,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 5\cdot2+4\cdot2=18 $ . Note that Lelle and Flamm can stop the match even if neither of them has $ n $ wins.

## 样例 #1

### 输入

```
8
3 3 2 5
4 4 1 4
6 6 2 2
7 7 2 3
9 9 9 1
2 2 1 4
5 5 1 4
8 8 6 7
```

### 输出

```
19
17
18
33
86
9
24
86
```

## 样例 #2

### 输入

```
1
20000000 20000000 1341 331
```

### 输出

```
33439999007
```

## 样例 #3

### 输入

```
2
1984 1984 19 84
9982 9982 44 35
```

### 输出

```
204143
788403
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
title: "Eri and Expanded Sets"
layout: "post"
diff: 提高+/省选-
pid: CF2006C
tag: ['数学', '二分', '数论', 'ST 表']
---

# Eri and Expanded Sets

## 题目描述

### 题目翻译


------------

有一个包含合法的数的集合。为了将这个集合扩展的尽可能大，Eri可以在集合中选择两个整数 $x \neq y $ ，它们的平均数 $ \frac{x+y}2 $ 是一个合法的不在集合中的数，然后把 $ \frac{x+y}2 $ 置入这个集合。整数 $ x $ 和 $ y $ 仍在这个集合中。

如果我们称这个集合为连续集，那么，当集合内的元素被排序后，相邻的两个元素之间极差为 $1$ 。例如, 集合 $ \{2\} $ , $ \{2, 5, 4, 3\} $ , $ \{5, 6, 8, 7\} $ 是连续集, 但 $ \{2, 4, 5, 6\} $ , $ \{9, 7\} $ 不是。

Eri 喜欢连续集. 假使我们有一序列 $ b $ ,  Eri 把 $ b $ 中所有的元素置入集合。 如果经过上述若干次操作后，该集合转化为了一个连续集，这个序列 $ b $ 就会被我们称作是“闪耀的”。

需要注意的是，如果一个相同的整数多次出现在序列中，我们只会把它加入集合一次，集合总是只包含合法的数。

Eri 有一个序列 $ a $ 包含 $ n $ 个合法的数。请帮他算出整数数对 $ (l,r) $ 的数量$( 1 \leq l \leq r \leq n )$ ，令子序列 $ a_l, a_{l+1}, \ldots, a_r $ 是闪耀的。

## 输入格式

每一个测试点包含多组测试数据。第一行只有一个整数  $ t $ $(1 \leq t \leq 10^4)$ 表示测试数据的组数。   
对于每组数据，第一行包含一个整数 $ n $ $( 1 \leq n \leq 4 \cdot 10^5 )$ 表示序列 $ a $ 的长度。

第二行有 $ n $ 个整数 $ a_1, a_2, \ldots a_n $  $( 1 \leq a_i \leq 10^9 )$ 表示序列中的元素 $ a_i $ 。  

保证 $Σn \leq 4 \cdot 10^5$ 。

## 输出格式

对于每组测试数据，输出一行一个整数，表示“闪耀的”子序列的数量。
#### 样例解释
在第一组测试数据中，序列 $ a = [2, 2] $ 有 $ 3 $ 个子序列：$ [2] $ , $ [2] $ ,  $ [2, 2] $ 。这些子序列构造的集合中只包含一个整数 $ 2 $ ，因此它总是连续集。 所有的子序列都是闪耀的，所以答案是 $ 3 $ .

在第二组测试数据中，注意到子序列 $ [3, 6, 10] $ . 我们可以进行下列操作：

$\{3,6,10\} \xrightarrow{x=6,y=10} \{3,6,8,10\} \xrightarrow{x=6,y=8} \{3,6,7,8,10\} \xrightarrow{x=3,y=7} \{3,5,6,7,8,10\} $ $     $ $ \xrightarrow{x=3,y=5} \{3,4,5,6,7,8,10\} \xrightarrow{x=8,y=10} \{3,4,5,6,7,8,9,10\} $   
   
$ \\{3,4,5,6,7,8,9,10\\} $  是一个连续集，所以子序列 $ \[3, 6, 10\]$ 是闪耀的。

## 样例 #1

### 输入

```
6
2
2 2
6
1 3 6 10 15 21
5
6 30 18 36 9
1
1000000000
6
1 1 4 5 1 4
12
70 130 90 90 90 108 612 500 451 171 193 193
```

### 输出

```
3
18
5
1
18
53
```



---

---
title: "Prefix GCD"
layout: "post"
diff: 提高+/省选-
pid: CF2013E
tag: ['贪心', '数论']
---

# Prefix GCD

## 题目描述

Since Mansur is tired of making legends, there will be no legends for this task.

You are given an array of positive integer numbers $ a_1, a_2, \ldots, a_n $ . The elements of the array can be rearranged in any order. You need to find the smallest possible value of the expression $ $$$\gcd(a_1) + \gcd(a_1, a_2) + \ldots + \gcd(a_1, a_2, \ldots, a_n), $ $  where  $ \\gcd(a\_1, a\_2, \\ldots, a\_n) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor (GCD)</a> of  $ a\_1, a\_2, \\ldots, a\_n$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single number $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the initial array.

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

The sum of $ \max(a_1, a_2, \ldots, a_n) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number on a separate line — the answer to the problem.

## 说明/提示

In the first test case, the elements can be rearranged as follows: $ [2, 4, 2] $ . Then the answer will be $ \gcd(2) + \gcd(2, 4) + \gcd(2, 4, 2) = 2 + 2 + 2 = 6 $ .

In the third test case, the elements can be rearranged as follows: $ [6, 10, 15] $ . Then the answer will be $ \gcd(6) + \gcd(6, 10) + \gcd(6, 10, 15) = 6 + 2 + 1 = 9 $ .

## 样例 #1

### 输入

```
5
3
4 2 2
2
6 3
3
10 15 6
5
6 42 12 52 20
4
42 154 231 66
```

### 输出

```
6
6
9
14
51
```



---

---
title: "Common Generator"
layout: "post"
diff: 提高+/省选-
pid: CF2029E
tag: ['数学', '数论', '标签475']
---

# Common Generator

## 题目描述

For two integers $ x $ and $ y $ ( $ x,y\ge 2 $ ), we will say that $ x $ is a generator of $ y $ if and only if $ x $ can be transformed to $ y $ by performing the following operation some number of times (possibly zero):

- Choose a divisor $ d $ ( $ d\ge 2 $ ) of $ x $ , then increase $ x $ by $ d $ .

For example,

- $ 3 $ is a generator of $ 8 $ since we can perform the following operations: $ 3 \xrightarrow{d = 3} 6 \xrightarrow{d = 2} 8 $ ;
- $ 4 $ is a generator of $ 10 $ since we can perform the following operations: $ 4 \xrightarrow{d = 4} 8 \xrightarrow{d = 2} 10 $ ;
- $ 5 $ is not a generator of $ 6 $ since we cannot transform $ 5 $ into $ 6 $ with the operation above.

Now, Kevin gives you an array $ a $ consisting of $ n $ pairwise distinct integers ( $ a_i\ge 2 $ ).

You have to find an integer $ x\ge 2 $ such that for each $ 1\le i\le n $ , $ x $ is a generator of $ a_i $ , or determine that such an integer does not exist.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 2\le a_i\le 4\cdot 10^5 $ ) — the elements in the array $ a $ . It is guaranteed that the elements are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer $ x $ — the integer you found. Print $ -1 $ if there does not exist a valid $ x $ .

If there are multiple answers, you may output any of them.

## 说明/提示

In the first test case, for $ x=2 $ :

- $ 2 $ is a generator of $ 8 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 4} 8 $ ;
- $ 2 $ is a generator of $ 9 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 3} 9 $ .
- $ 2 $ is a generator of $ 10 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 2} 8 \xrightarrow{d = 2} 10 $ .

In the second test case, it can be proven that it is impossible to find a common generator of the four integers.

## 样例 #1

### 输入

```
4
3
8 9 10
4
2 3 4 5
2
147 154
5
3 6 8 25 100000
```

### 输出

```
2
-1
7
3
```



---

---
title: "Grid Walk"
layout: "post"
diff: 提高+/省选-
pid: CF2038K
tag: ['动态规划 DP', '数论']
---

# Grid Walk

## 题目描述

### 题意翻译
给定一个 $n\times n$ 的矩阵和两个正整数 $a$ 和 $b$，第 $i$ 行第 $j$ 列的权值 $c_{i,j}=\gcd(i,a)+\gcd(j,b)$，一开始你在点 $(1,1)$，你可以向右或者向下走，一直走到点 $(n,n)$。

你需要规划一条路径，使得从点 $(1,1)$ 走到点 $(n,n)$ 所经过的点的权值和 $\sum c_{i,j}$ 最小，输出这个最小值。

## 输入格式

一行输入三个正整数 $n,a,b$。（$2\le n \le 10^6$；$1\le a,b \le 10^6$）

## 输出格式

输出一个整数表示所求答案。

翻译人：[gcx12012](https://www.luogu.com.cn/user/494601)

## 样例 #1

### 输入

```
4 2 4
```

### 输出

```
21
```

## 样例 #2

### 输入

```
10 210 420
```

### 输出

```
125
```



---

---
title: "Serval and Modulo"
layout: "post"
diff: 提高+/省选-
pid: CF2085E
tag: ['数论']
---

# Serval and Modulo

## 题目描述

给定一个由 $n$ 个非负整数组成的数组 $a$ 和一个魔法数 $k$（$k \ge 1$ 且为整数）。Serval 构造了另一个长度为 $n$ 的数组 $b$，其中对于所有 $1 \leq i \leq n$，满足 $b_i = a_i \bmod k^{\text{∗}}$。随后，他将 $b$ 打乱了顺序。

现在给定数组 $a$ 和 $b$，请找出一个可能的魔法数 $k$。如果 Serval 欺骗了你且这样的整数不存在，则输出 $-1$。

可以证明，在题目约束下，若这样的 $k$ 存在，则存在一个不超过 $10^9$ 的有效答案。你需要在输出中保证 $k \leq 10^9$。

$^{\text{∗}}$符号 $a_i \bmod k$ 表示 $a_i$ 除以 $k$ 的余数。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 10^4$）——数组 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq 10^6$）——数组 $a$ 的元素。

第三行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$0 \leq b_i \leq 10^6$）——数组 $b$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $10^4$。

## 输出格式

对于每个测试用例，输出一个整数 $k$（$1 \leq k \leq 10^9$）——找到的魔法数。若不存在这样的整数，输出 $-1$。

若存在多个答案，输出任意一个即可。

## 说明/提示

第一个测试案例中，若 $k \ge 3$，则 $2 = a_3 \bmod k$ 必须出现在数组 $b$ 中，但这会导致矛盾。当 $k = 1$ 时，$[a_1 \bmod k, a_2 \bmod k, a_3 \bmod k, a_4 \bmod k] = [0,0,0,0]$，无法通过打乱顺序得到 $b$。当 $k = 2$ 时，$[a_1 \bmod k, a_2 \bmod k, a_3 \bmod k, a_4 \bmod k] = [1,1,0,1]$，可以打乱为 $b$。因此唯一可能的答案是 $k = 2$。

第二个测试案例中，注意 $b$ 可以通过打乱 $a$ 直接得到。因此所有 $6$ 到 $10^9$ 的整数都是合法答案。

第三个测试案例中，可以证明这样的 $k$ 不存在。Serval 欺骗了你！

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4
3 5 2 7
0 1 1 1
5
3 1 5 2 4
1 2 3 4 5
6
2 3 4 7 8 9
1 2 3 6 7 8
5
21 22 25 28 20
0 1 2 1 0
6
1 1 2 3 5 8
0 0 1 1 0 0
```

### 输出

```
2
31415926
-1
4
-1
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

---
title: "Unusual Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF900D
tag: ['数论', '莫比乌斯反演', '组合数学', '容斥原理']
---

# Unusual Sequences

## 题目描述

Count the number of distinct sequences $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i} $ ) consisting of positive integers such that $ gcd(a_{1},a_{2},...,a_{n})=x $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900D/b6b0405f12ef386aeb195f818cd0534bcf4623e0.png). As this number could be large, print the answer modulo $ 10^{9}+7 $ .

 $ gcd $ here means the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 输入格式

The only line contains two positive integers $ x $ and $ y $ ( $ 1<=x,y<=10^{9} $ ).

## 输出格式

Print the number of such sequences modulo $ 10^{9}+7 $ .

## 说明/提示

There are three suitable sequences in the first test: $ (3,3,3) $ , $ (3,6) $ , $ (6,3) $ .

There are no suitable sequences in the second test.

## 样例 #1

### 输入

```
3 9

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
0

```



---

