---
title: "Lucky Tickets"
layout: "post"
diff: 省选/NOI-
pid: CF1096G
tag: ['组合数学', '快速数论变换 NTT']
---

# Lucky Tickets

## 题目描述

All bus tickets in Berland have their numbers. A number consists of $ n $ digits ( $ n $ is even). Only $ k $ decimal digits $ d_1, d_2, \dots, d_k $ can be used to form ticket numbers. If $ 0 $ is among these digits, then numbers may have leading zeroes. For example, if $ n = 4 $ and only digits $ 0 $ and $ 4 $ can be used, then $ 0000 $ , $ 4004 $ , $ 4440 $ are valid ticket numbers, and $ 0002 $ , $ 00 $ , $ 44443 $ are not.

A ticket is lucky if the sum of first $ n / 2 $ digits is equal to the sum of remaining $ n / 2 $ digits.

Calculate the number of different lucky tickets in Berland. Since the answer may be big, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (2 \le n \le 2 \cdot 10^5, 1 \le k \le 10) $ — the number of digits in each ticket number, and the number of different decimal digits that may be used. $ n $ is even.

The second line contains a sequence of pairwise distinct integers $ d_1, d_2, \dots, d_k $ $ (0 \le d_i \le 9) $ — the digits that may be used in ticket numbers. The digits are given in arbitrary order.

## 输出格式

Print the number of lucky ticket numbers, taken modulo $ 998244353 $ .

## 说明/提示

In the first example there are $ 6 $ lucky ticket numbers: $ 1111 $ , $ 1818 $ , $ 1881 $ , $ 8118 $ , $ 8181 $ and $ 8888 $ .

There is only one ticket number in the second example, it consists of $ 20 $ digits $ 6 $ . This ticket number is lucky, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 8

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20 1
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
10 5
6 1 4 0 3

```

### 输出

```
569725

```

## 样例 #4

### 输入

```
1000 7
5 4 0 1 8 3 2

```

### 输出

```
460571165

```



---

---
title: "Red-White Fence"
layout: "post"
diff: 省选/NOI-
pid: CF1251F
tag: ['数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Red-White Fence

## 题目描述

Polycarp想在他家附近建一道栅栏。他有$n$个白板和$k$个红板去建造它。每一块板都有一个整数长度。

一个好的栅栏应由一块红板和几块（可能是零块）白板组成。红色的板应该在这道栅栏中是**最长的**，而且红板前的板子长度应为递增，而红板之后的板子长度为递减。如果用了$m$块板子，它们的长度从左到右依次是$l_1,l_2,…,l_m$，那么应该符合以下条件

①栅栏上应**有且只有一块**红板，设其序号为$j$

②对于所有的$i∈[1,j-1]$有$l_i<l_{i+1}$

③对于所有的$i∈[j,m-1]$有$l_i>l_{i+1}$

在Polycarp建造他的栅栏时，他会从左向右在$0$高度上放置所有板，没有间隙，所以这些板将会组成一个多边形

例图：一个栅栏的板长数组为$[1,2,3,4,5]$，第二个板是红板。栅栏的周长是$20$。Polycrp对一些特殊周长的栅栏感兴趣。他有喜欢的$q$个偶整数$[Q_1,Q_2,…,Q_q]$，对于每个这样的整数$Q_i$，他想计算有几种不同的周长是$Q_i$的篱笆可以被造出来（如果两个篱笆的板长排列不同，那么就认为这两个篱笆是不同的）你可以帮他计算这些数值吗？

## 输入格式

输入第一行是两个正整数$n,k(1≤n≤3*10^5,1≤k≤5)$，表示Polycarp拥有的白板和红板的数量

第二行有$n$个正整数$[a_1,a_2,...,a_n](1≤a_i≤3*10^5)$，表示Polycarp拥有的$n$块白板的长度

第三行有$k$个正整数$[b_1,b_2,...,b_k](1≤b_i≤3*10^5)$，表示Polycarp拥有的$k$块红板的长度，所有$b_i$都是不相同的

第四行是一个正整数$q(1≤q≤3*10^5)$，表示特殊周长的数量

第五行有$q$个正整数$[Q_1,Q_2,...,Q_q](4≤Q_i≤12*10^5)$，每个$Q_i$都是偶数，表示Polycarp喜欢的特殊整数（即特殊周长）

## 输出格式

对于每个$Q_i$，输出一个整数，表示有多少种符合约束条件的周长为$Q_i$的栅栏，由于数量可能很大，结果请对$998244353$取模，每个输出占一行

## 说明/提示

对于第一个样例，可能的长度序列有（红板加粗）

·周长为$6$：$[$**2**$]$

·周长为$8$：$[1,$ **2**$]$,$[$**2**$,1]$

·周长为$10$：$[1,$ **2**$,1]$,$[$**4**$]$

·周长为$12$：$[1,$ **4**$]$,$[3,$ **4**$]$,$[$**4**$,1]$,$[$**4**$,3]$

·周长为$14$：$[1,$ **4**$,1]$,$[1,$ **4**$,3]$,$[3,$ **4**$,1]$,$[3,$ **4**$,3]$,$[1,3,$ **4**$]$,$[$**4**$,3,1]$

·周长为$16$：$[1,$ **4**$,3,1]$,$[3,$ **4**$,3,1]$,$[1,3,$ **4**$,1]$,$[1,3,$ **4**$,3]$

·周长为$18$：$[1,3,$ **4**$,3,1]$

## 样例 #1

### 输入

```
5 2
3 3 1 1 1
2 4
7
6 8 10 12 14 16 18

```

### 输出

```
1
2
2
4
6
4
1

```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
1 2 3 4 5
4
4 8 10 14

```

### 输出

```
1
3
5
20

```



---

---
title: "Cute number"
layout: "post"
diff: 省选/NOI-
pid: CF1687D
tag: ['数学', '数论']
---

# Cute number

## 题目描述

> 蓝智力相当高，尤其擅长数学。据说连人类所无法想象程度的计算都能够在瞬间完成。——《东方求闻史纪》

[八云蓝](https://www.luogu.com.cn/user/149196)是一个很喜欢出可爱的数学题的可爱的女孩子。

定义 $f(x)$ 表示严格大于 $x$ 的最小的完全平方数，定义 $g(x)$ 为小于等于 $x$ 的最大的完全平方数。例如，$f(1)=f(2)=g(4)=g(8)=4$。

蓝认为，一个正整数是“可爱”的，当且仅当 $x-g(x)<f(x)-x$，例如，$1,5,11$ 是可爱的正整数，而 $3,8,15$ 不是。

蓝给了你一个长度为 $n$ 的正整数数列 $a_i$，你需要帮她找到最小的非负整数 $k$，使得对于 $\forall i$，$a_i+k$ 是可爱的。

## 输入格式

第一行输入一个正整数 $n(1 \leq n \leq 10^6)$，表示正整数数列的长度。

第二行输入 $n$ 个正整数 $a_i(1 \leq a_1 \leq a_2 \leq \cdots \leq a_n \leq 2 \times 10^6)$。

## 输出格式

输出符合题目要求的最小非负整数 $k$。

## 样例 #1

### 输入

```
4
1 3 8 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 3 8 9 11
```

### 输出

```
8
```

## 样例 #3

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
48
```



---

---
title: "LCM Sum (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1712E2
tag: ['线段树', '树状数组', '数论']
---

# LCM Sum (hard version)

## 题目描述

We are sum for we are many

Some Number



This version of the problem differs from the previous one only in the constraint on $ t $ . You can make hacks only if both versions of the problem are solved.

You are given two positive integers $ l $ and $ r $ .

Count the number of distinct triplets of integers $ (i, j, k) $ such that $ l \le i < j < k \le r $ and $ \operatorname{lcm}(i,j,k) \ge i + j + k $ .

Here $ \operatorname{lcm}(i, j, k) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ i $ , $ j $ , and $ k $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ \bf{1 \le t \le 10^5} $ ). Description of the test cases follows.

The only line for each test case contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 2 \cdot 10^5 $ , $ l + 2 \le r $ ).

## 输出格式

For each test case print one integer — the number of suitable triplets.

## 说明/提示

In the first test case, there are $ 3 $ suitable triplets:

- $ (1,2,3) $ ,
- $ (1,3,4) $ ,
- $ (2,3,4) $ .

In the second test case, there is $ 1 $ suitable triplet:

- $ (3,4,5) $ .

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868
```

### 输出

```
3
1
78975
969
109229059713337
```



---

---
title: "Wooden Spoon"
layout: "post"
diff: 省选/NOI-
pid: CF1784D
tag: ['数学', '组合数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Wooden Spoon

## 题目描述

$ 2^n $ people, numbered with distinct integers from $ 1 $ to $ 2^n $ , are playing in a single elimination tournament. The bracket of the tournament is a full binary tree of height $ n $ with $ 2^n $ leaves.

When two players meet each other in a match, a player with the smaller number always wins. The winner of the tournament is the player who wins all $ n $ their matches.

A virtual consolation prize "Wooden Spoon" is awarded to a player who satisfies the following $ n $ conditions:

- they lost their first match;
- the player who beat them lost their second match;
- the player who beat that player lost their third match;
- $ \ldots $ ;
- the player who beat the player from the previous condition lost the final match of the tournament.

It can be shown that there is always exactly one player who satisfies these conditions.

Consider all possible $ (2^n)! $ arrangements of players into the tournament bracket. For each player, find the number of these arrangements in which they will be awarded the "Wooden Spoon", and print these numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \le n \le 20 $ ) — the size of the tournament.

There are $ 20 $ tests in the problem: in the first test, $ n = 1 $ ; in the second test, $ n = 2 $ ; $ \ldots $ ; in the $ 20 $ -th test, $ n = 20 $ .

## 输出格式

Print $ 2^n $ integers — the number of arrangements in which the "Wooden Spoon" is awarded to players $ 1, 2, \ldots, 2^n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the "Wooden Spoon" is always awarded to player $ 2 $ .

In the second example, there are $ 8 $ arrangements where players $ 1 $ and $ 4 $ meet each other in the first match, and in these cases, the "Wooden Spoon" is awarded to player $ 3 $ . In the remaining $ 16 $ arrangements, the "Wooden Spoon" is awarded to player $ 4 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
0
0
8
16
```

## 样例 #3

### 输入

```
3
```

### 输出

```
0
0
0
1536
4224
7680
11520
15360
```



---

---
title: "Carousel of Combinations"
layout: "post"
diff: 省选/NOI-
pid: CF1957E
tag: ['数论', '组合数学']
---

# Carousel of Combinations

## 题目描述

You are given an integer $ n $ . The function $ C(i,k) $ represents the number of distinct ways you can select $ k $ distinct numbers from the set { $ 1, 2, \ldots, i $ } and arrange them in a circle $ ^\dagger $ .

Find the value of 
$$
\sum\limits_{i=1}^n \sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)
$$
Here, the operation  $ x \\bmod y $  denotes the remainder from dividing  $ x $  by  $ y $ .</p><p>Since this value can be very large, find it modulo  $ 10^9+7 $ .</p><p> $ ^\\dagger $  In a circular arrangement, sequences are considered identical if one can be rotated to match the other. For instance,  $ \[1, 2, 3\] $  and  $ \[2, 3, 1\]$$$ are equivalent in a circle.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

## 输出格式

For each test case, output a single integer on a new line — the value of the expression to be calculated modulo $ 10^9+7 $ .

## 说明/提示

In the first test case, $ C(1,1) \bmod 1 = 0 $ .

In the second test case:

- $ C(1,1)=1 $ (the arrangements are: $ [1] $ );
- $ C(2,1)=2 $ (the arrangements are: $ [1] $ , $ [2] $ );
- $ C(2,2)=1 $ (the arrangements are: $ [1, 2] $ );
- $ C(3,1)=3 $ (the arrangements are: $ [1] $ , $ [2] $ , $ [3] $ );
- $ C(3,2)=3 $ (the arrangements are: $ [1, 2] $ , $ [2, 3] $ , $ [3, 1] $ );
- $ C(3,3)=2 $ (the arrangements are: $ [1, 2, 3] $ , $ [1, 3, 2] $ ).

 In total, $ \left(C(1,1) \bmod 1\right) + \left(C(2,1) \bmod 1\right) + \left(C(2,2) \bmod 2\right) + \left(C(3,1) \bmod 1\right) + \left(C(3,2) \bmod 2\right) + \left(C(3,3) \bmod 3\right) = 4 $ .

## 样例 #1

### 输入

```
4
1
3
6
314159
```

### 输出

```
0
4
24
78926217
```



---

---
title: "Permutation Problem (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1986G2
tag: ['数论']
---

# Permutation Problem (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \leq 5 \cdot 10^5 $ and the sum of $ n $ for all sets of input data does not exceed $ 5 \cdot 10^5 $ .

You are given a permutation $ p $ of length $ n $ . Calculate the number of index pairs $ 1 \leq i < j \leq n $ such that $ p_i \cdot p_j $ is divisible by $ i \cdot j $ without remainder.

A permutation is a sequence of $ n $ integers, in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of sets of input data. Then follows their description.

The first line of each set of input data contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ) — the length of the permutation $ p $ .

The second line of each set of input data contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n $ ) — the permutation $ p $ .

It is guaranteed that the sum of $ n $ for all sets of input data does not exceed $ 5 \cdot 10^5 $ .

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
title: "Court Blue (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2002F2
tag: ['数论']
---

# Court Blue (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is not guaranteed that $ n=m $ , and the time limit is higher. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 输入格式

The first line contains an integer $ t $ ( $ 1\leq t \leq 10^3 $ ) — the number of test cases.

The only line of each test case contains four integers $ n $ , $ m $ , $ l $ , $ f $ ( $ 2\leq n\leq m \leq 2\cdot 10^7 $ , $ 1\leq l,f \leq 10^9 $ ): $ n $ , $ m $ give the upper bound on the number of Lelle and Flamm's wins, $ l $ and $ f $ determine the final score of the performance.

Unusual additional constraint: it is guaranteed that, for each test, there are no pairs of test cases with the same pair of $ n $ , $ m $ .

## 输出格式

For each test case, output a single integer — the maximum total score of a successful performance.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Flamm wins, $ \gcd(1,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 1\cdot2+4\cdot5=22 $ .

## 样例 #1

### 输入

```
8
3 4 2 5
4 4 1 4
6 6 2 2
7 9 2 3
8 9 9 1
2 7 1 4
5 9 1 4
5 6 6 7
```

### 输出

```
22
17
18
37
77
30
41
59
```

## 样例 #2

### 输入

```
2
3082823 20000000 1341 331
20000000 20000000 3 5
```

### 输出

```
10754065643
159999991
```

## 样例 #3

### 输入

```
1
139 1293 193 412
```

### 输出

```
559543
```



---

---
title: "Alternative Platforms"
layout: "post"
diff: 省选/NOI-
pid: CF2038F
tag: ['数学', '快速数论变换 NTT']
---

# Alternative Platforms

## 题目描述

Suppose you are working in the Ministry of Digital Development of Berland, and your task is to monitor the industry of video blogging.

There are $ n $ bloggers in Berland. Recently, due to the poor state of the main video platform in Berland, two alternative platforms were introduced. That's why bloggers started to reupload their videos to these alternative platforms. You've got the statistics that the $ i $ -th blogger uploaded $ v_i $ videos to the first alternative platform and $ r_i $ videos to the second alternative platform.

You think that a potential user will be upset if even at least one of his favorite bloggers doesn't upload anything. However, if a blogger uploads videos to both platforms, the user will watch that blogger on the platform where more videos are available. So, you've come up with the following function to estimate user experience. Suppose a user watches $ k $ bloggers $ b_1, b_2, \dots, b_k $ ; then, let user experience be  $E(b_1, \dots, b_k) = \max\left(\min_{i=1..k}{v[b_i]}, \min_{i=1..k}{r[b_i]}\right).$ 

In order to get some statistics, you want to calculate the value  $ \mathit{avg}\_k $  that is equal to an average experience among all subsets of bloggers of size  $ k $ . Also, you have to calculate  $ \mathit{avg}\_k $  for each  $ k $  from  $ 1 $  to  $ n $. 

Since answers may be too large, print them modulo  $ 998\,244\,353$.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of bloggers.

The second line contains $ n $ integers $ v_1, v_2, \dots, v_n $ ( $ 0 \le v_i \le 10^6 $ ), where $ v_i $ is the number of videos of the $ i $ -th blogger on the first alternative platform.

The third line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ 0 \le r_i \le 10^6 $ ), where $ r_i $ is the number of videos of the $ i $ -th blogger on the second alternative platform.

## 输出格式

Print $ n $ integers $ \mathit{avg}_1, \mathit{avg}_2, \dots, \mathit{avg}_n $ .

It can be proven that $ \mathit{avg}_k $ may be represented as an irreducible fraction $ \dfrac{x}{y} $ where $ y \not\equiv 0 \pmod{998\,244\,353} $ . So, print $ \mathit{avg}_k $ in a form $ x \cdot y^{-1} \bmod 998\,244\,353 $ .

## 说明/提示

In the first example, $ 332748119 $ is $ \frac{4}{3} $ . In the third example, $ 199648873 $ is $ \frac{12}{5} $ .

## 样例 #1

### 输入

```
3
2 1 2
1 2 1
```

### 输出

```
2 332748119 1
```

## 样例 #2

### 输入

```
4
5 5 5 5
0 0 0 0
```

### 输出

```
5 5 5 5
```

## 样例 #3

### 输入

```
5
1 9 3 7 5
2 4 6 8 5
```

### 输出

```
6 4 3 199648873 2
```



---

---
title: "Shohag Loves Counting (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2039F1
tag: ['动态规划 DP', '数论', '莫比乌斯反演', '容斥原理']
---

# Shohag Loves Counting (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ t $ , $ m $ , and the sum of $ m $ . You can only make hacks if both versions of the problem are solved.

For an integer array $ a $ of length $ n $ , define $ f(k) $ as the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the maximum values of all subarrays $ ^{\text{∗}} $ of length $ k $ . For example, if the array is $ [2, 1, 4, 6, 2] $ , then $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4]), \operatorname{max}([1, 4, 6]), \operatorname{max}([4, 6, 2])) = \operatorname{gcd}(4, 6, 6) = 2 $ .

An array is good if $ f(i) \neq f(j) $ is satisfied over all pairs $ 1 \le i \lt j \le n $ .

Shohag has an integer $ m $ . Help him count the number, modulo $ 998\,244\,353 $ , of non-empty good arrays of arbitrary length such that each element of the array is an integer from $ 1 $ to $ m $ .

 $ ^{\text{∗}} $ An array $ d $ is a subarray of an array $ c $ if $ d $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains an integer $ m $ ( $ 1 \le m \le 10^5 $ ).

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

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
title: "Modulo 3"
layout: "post"
diff: 省选/NOI-
pid: CF2104G
tag: ['并查集', '数论', '线段树分治']
---

# Modulo 3

## 题目描述

给定基环内向森林，每个点有且仅有一条出边 $g_i$，可能有自环。

所有点的初始颜色均为 $1$，你可以执行如下操作**任意次**（可以为零次）：

- 选择一个顶点 $u \in [1,n]$，再选择一种颜色 $c \in [1,k]$，将 $u$ 能到达的所有点（包括 $u$ 本身）染成颜色 $c$。

你需要求出，最终能形成的不同的图的数量，**答案对 $3$ 取模**。

两个图不同，当且仅当存在一个编号为 $i$ 的节点，它的颜色在两图中不同。

现在有 $q$ 次修改操作，每次给定 $x,y,k$：

- 将 $g_x$ 修改为 $y$。
- 对于本次输入的 $k$，输出答案，对 $3$ 取模。

对 $g_x$ 的修改操作是永久的，对后面有影响。但是在每次询问答案时，所有顶点的初始颜色都是 $1$。

## 输入格式

第一行包含两个整数 $n$ 和 $q$。

第二行包含 $n$ 个整数 $g_1, g_2, \dots, g_n$。

接下来是 $q$ 行，第 $i$ 行包含三个整数 $x_i$ 、 $y_i$ 和 $k_i$ （$1 \le k_i \le 10^9$ ）。

## 输出格式

共 $q$ 行，每行一个在 $[0,3)$ 的整数。

## 说明/提示

$1 \le n, q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
4 5
2 3 1 4
4 3 1
2 1 2
3 4 3
4 1 5
2 4 4
```

### 输出

```
1
2
0
2
1
```

## 样例 #2

### 输入

```
8 10
7 4 6 8 7 7 1 4
1 7 5
2 3 3
8 6 1
3 1 3
7 2 5
5 2 4
2 7 4
4 6 5
5 2 3
4 5 1
```

### 输出

```
1
0
1
0
2
1
1
2
0
1
```



---

