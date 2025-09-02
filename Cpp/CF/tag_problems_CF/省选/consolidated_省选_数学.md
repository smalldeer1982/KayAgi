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
title: "Lunar New Year and a Recursive Sequence"
layout: "post"
diff: 省选/NOI-
pid: CF1106F
tag: ['数学', '矩阵加速']
---

# Lunar New Year and a Recursive Sequence

## 题目描述

Lunar New Year is approaching, and Bob received a gift from his friend recently — a recursive sequence! He loves this sequence very much and wants to play with it.

Let $ f_1, f_2, \ldots, f_i, \ldots $ be an infinite sequence of positive integers. Bob knows that for $ i > k $ , $ f_i $ can be obtained by the following recursive equation:

 $ $$$f_i = \left(f_{i - 1} ^ {b_1} \cdot f_{i - 2} ^ {b_2} \cdot \cdots \cdot f_{i - k} ^ {b_k}\right) \bmod p, $ $ </p><p>which in short is</p><p> $ $ f_i = \left(\prod_{j = 1}^{k} f_{i - j}^{b_j}\right) \bmod p, $ $ </p><p>where  $ p = 998\\,244\\,353 $  (a widely-used prime),  $ b\_1, b\_2, \\ldots, b\_k $  are known integer constants, and  $ x \\bmod y $  denotes the remainder of  $ x $  divided by  $ y $ .</p><p>Bob lost the values of  $ f\_1, f\_2, \\ldots, f\_k $ , which is extremely troublesome – these are the basis of the sequence! Luckily, Bob remembers the first  $ k - 1 $  elements of the sequence:  $ f\_1 = f\_2 = \\ldots = f\_{k - 1} = 1 $  and the  $ n $ -th element:  $ f\_n = m $ . Please find any possible value of  $ f\_k$$$. If no solution exists, just tell Bob that it is impossible to recover his favorite sequence, regardless of Bob's sadness.

## 输入格式

The first line contains a positive integer $ k $ ( $ 1 \leq k \leq 100 $ ), denoting the length of the sequence $ b_1, b_2, \ldots, b_k $ .

The second line contains $ k $ positive integers $ b_1, b_2, \ldots, b_k $ ( $ 1 \leq b_i < p $ ).

The third line contains two positive integers $ n $ and $ m $ ( $ k < n \leq 10^9 $ , $ 1 \leq m < p $ ), which implies $ f_n = m $ .

## 输出格式

Output a possible value of $ f_k $ , where $ f_k $ is a positive integer satisfying $ 1 \leq f_k < p $ . If there are multiple answers, print any of them. If no such $ f_k $ makes $ f_n = m $ , output $ -1 $ instead.

It is easy to show that if there are some possible values of $ f_k $ , there must be at least one satisfying $ 1 \leq f_k < p $ .

## 说明/提示

In the first sample, we have $ f_4 = f_3^2 \cdot f_2^3 \cdot f_1^5 $ . Therefore, applying $ f_3 = 4 $ , we have $ f_4 = 16 $ . Note that there can be multiple answers.

In the third sample, applying $ f_7 = 1 $ makes $ f_{23333} = 1 $ .

In the fourth sample, no such $ f_1 $ makes $ f_{88888} = 66666 $ . Therefore, we output $ -1 $ instead.

## 样例 #1

### 输入

```
3
2 3 5
4 16

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
4 7 1 5 6
7 14187219

```

### 输出

```
6

```

## 样例 #3

### 输入

```
8
2 3 5 6 1 7 9 10
23333 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
1
2
88888 66666

```

### 输出

```
-1

```

## 样例 #5

### 输入

```
3
998244352 998244352 998244352
4 2

```

### 输出

```
-1

```

## 样例 #6

### 输入

```
10
283 463 213 777 346 201 463 283 102 999
2333333 6263423

```

### 输出

```
382480067

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
title: "Cards"
layout: "post"
diff: 省选/NOI-
pid: CF1278F
tag: ['数学']
---

# Cards

## 题目描述

Consider the following experiment. You have a deck of $ m $ cards, and exactly one card is a joker. $ n $ times, you do the following: shuffle the deck, take the top card of the deck, look at it and return it into the deck.

Let $ x $ be the number of times you have taken the joker out of the deck during this experiment. Assuming that every time you shuffle the deck, all $ m! $ possible permutations of cards are equiprobable, what is the expected value of $ x^k $ ? Print the answer modulo $ 998244353 $ .

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m < 998244353 $ , $ 1 \le k \le 5000 $ ).

## 输出格式

Print one integer — the expected value of $ x^k $ , taken modulo $ 998244353 $ (the answer can always be represented as an irreducible fraction $ \frac{a}{b} $ , where $ b \mod 998244353 \ne 0 $ ; you have to print $ a \cdot b^{-1} \mod 998244353 $ ).

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 1 5000

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2 2 2

```

### 输出

```
499122178

```

## 样例 #4

### 输入

```
998244352 1337 5000

```

### 输出

```
326459680

```



---

---
title: "Résumé Review"
layout: "post"
diff: 省选/NOI-
pid: CF1344D
tag: ['数学']
---

# Résumé Review

## 题目描述

Uh oh! Applications to tech companies are due soon, and you've been procrastinating by doing contests instead! (Let's pretend for now that it is actually possible to get a job in these uncertain times.)

You have completed many programming projects. In fact, there are exactly $ n $ types of programming projects, and you have completed $ a_i $ projects of type $ i $ . Your résumé has limited space, but you want to carefully choose them in such a way that maximizes your chances of getting hired.

You want to include several projects of the same type to emphasize your expertise, but you also don't want to include so many that the low-quality projects start slipping in. Specifically, you determine the following quantity to be a good indicator of your chances of getting hired:

 $ $$$ f(b_1,\ldots,b_n)=\sum\limits_{i=1}^n b_i(a_i-b_i^2).  $ $ </p>     <p>Here,  $ b\_i $  denotes the number of projects of type  $ i $        you include in your résumé. Of course, you cannot include more       projects than you have completed, so you require  $ 0\\le b\_i \\le a\_i $  for all  $ i $ .</p>     <p>Your résumé only has enough room for  $ k $  projects, and you       will absolutely not be hired if your résumé has empty space, so       you require  $ \\sum\\limits\_{i=1}^n b\_i=k $ .</p>     <p>Find values for  $ b\_1,\\ldots, b\_n $  that maximize the value of        $ f(b\_1,\\ldots,b\_n)$$$ while satisfying the above two constraints.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1\le       n\le 10^5 $ , $ 1\le k\le \sum\limits_{i=1}^n a_i $ ) — the number of types of programming projects and the résumé size, respectively.

The next line contains $ n $ integers $ a_1,\ldots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — $ a_i $ is equal to the number of completed projects of type $ i $ .

## 输出格式

In a single line, output $ n $ integers $ b_1,\ldots, b_n $ that achieve the maximum value of $ f(b_1,\ldots,b_n) $ , while satisfying the requirements $ 0\le b_i\le a_i $ and $ \sum\limits_{i=1}^n b_i=k $ . If there are multiple solutions, output any.

 Note that you do not have to output the value $ f(b_1,\ldots,b_n) $ .

## 说明/提示

For the first test, the optimal answer is $ f=-269 $ . Note that a larger $ f $ value is possible if we ignored the constraint $ \sum\limits_{i=1}^n b_i=k $ .

For the second test, the optimal answer is $ f=9 $ .

## 样例 #1

### 输入

```
10 32
1 2 3 4 5 5 5 5 5 5
```

### 输出

```
1 2 3 3 3 4 4 4 4 4
```

## 样例 #2

### 输入

```
5 8
4 4 8 2 1
```

### 输出

```
2 2 2 1 1
```



---

---
title: "Emotional Fishermen"
layout: "post"
diff: 省选/NOI-
pid: CF1437F
tag: ['动态规划 DP', '组合数学']
---

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 5000 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print one integer — the number of emotional orders, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
4 2 1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97
```

### 输出

```
19200
```



---

---
title: "Top-Notch Insertions"
layout: "post"
diff: 省选/NOI-
pid: CF1558D
tag: ['线段树', '二分', '平衡树', '组合数学']
---

# Top-Notch Insertions

## 题目描述

Consider the insertion sort algorithm used to sort an integer sequence $ [a_1, a_2, \ldots, a_n] $ of length $ n $ in non-decreasing order.

For each $ i $ in order from $ 2 $ to $ n $ , do the following. If $ a_i \ge a_{i-1} $ , do nothing and move on to the next value of $ i $ . Otherwise, find the smallest $ j $ such that $ a_i < a_j $ , shift the elements on positions from $ j $ to $ i-1 $ by one position to the right, and write down the initial value of $ a_i $ to position $ j $ . In this case we'll say that we performed an insertion of an element from position $ i $ to position $ j $ .

It can be noticed that after processing any $ i $ , the prefix of the sequence $ [a_1, a_2, \ldots, a_i] $ is sorted in non-decreasing order, therefore, the algorithm indeed sorts any sequence.

For example, sorting $ [4, 5, 3, 1, 3] $ proceeds as follows:

- $ i = 2 $ : $ a_2 \ge a_1 $ , do nothing;
- $ i = 3 $ : $ j = 1 $ , insert from position $ 3 $ to position $ 1 $ : $ [3, 4, 5, 1, 3] $ ;
- $ i = 4 $ : $ j = 1 $ , insert from position $ 4 $ to position $ 1 $ : $ [1, 3, 4, 5, 3] $ ;
- $ i = 5 $ : $ j = 3 $ , insert from position $ 5 $ to position $ 3 $ : $ [1, 3, 3, 4, 5] $ .

You are given an integer $ n $ and a list of $ m $ integer pairs $ (x_i, y_i) $ . We are interested in sequences such that if you sort them using the above algorithm, exactly $ m $ insertions will be performed: first from position $ x_1 $ to position $ y_1 $ , then from position $ x_2 $ to position $ y_2 $ , ..., finally, from position $ x_m $ to position $ y_m $ .

How many sequences of length $ n $ consisting of (not necessarily distinct) integers between $ 1 $ and $ n $ , inclusive, satisfy the above condition? Print this number modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m < n $ ) — the length of the sequence and the number of insertions.

The $ i $ -th of the following $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 2 \le x_1 < x_2 < \ldots < x_m \le n $ ; $ 1 \le y_i < x_i $ ). These lines describe the sequence of insertions in chronological order.

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Note that there is no constraint on the sum of $ n $ of the same kind.

## 输出格式

For each test case, print the number of sequences of length $ n $ consisting of integers from $ 1 $ to $ n $ such that sorting them with the described algorithm produces the given sequence of insertions, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the algorithm performs no insertions — therefore, the initial sequence is already sorted in non-decreasing order. There are $ 10 $ such sequences: $ [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 2, 3], [1, 3, 3], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3] $ .

In the second test case, the only sequence satisfying the conditions is $ [3, 2, 1] $ .

In the third test case, $ [4, 5, 3, 1, 3] $ is one of the sought sequences.

## 样例 #1

### 输入

```
3
3 0
3 2
2 1
3 1
5 3
3 1
4 1
5 3
```

### 输出

```
10
1
21
```



---

---
title: "A Random Code Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1626F
tag: ['动态规划 DP', '状态合并', '组合数学']
---

# A Random Code Problem

## 题目描述

给你一个数组 $a$ 和一个整数 $k$ ，执行下面的代码：
```cpp
long long ans = 0; //定义一个初始值为 0 的长整型变量
for(int i = 1; i <= k; i++) {
	int idx = rnd.next(0, n - 1); //生成一个介于0到n-1的随机数（含 0 和 n-1）
  								 //每个数被选中的概率是相同的
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
您需要在执行此代码后计算变量 $ans$ 的期望。

数组 $a$ 是输入时根据特殊规则生成的。

## 输入格式

仅一行，六个整数 $n$ , $a_0$ , $x$ , $y$ , $k$ 和 $M$ 。

数组 $a$ 由以下规则生成：

* $a_0$ 由输入给出
* 对于 $a_1$ 至 $a_{n-1}$，$a_i=(a_{i-1}\times x+y)\bmod M$。

## 输出格式

令 $E$ 为 $ans$ 的期望，输出 $E\times n^k$，对 $998244353$ 取模。

## 说明/提示

$1\le n\le10^7$

$1\le a_0,x,y<M\le998244353$

$1\le k\le17$

## 样例 #1

### 输入

```
3 10 3 5 13 88
```

### 输出

```
382842030
```

## 样例 #2

### 输入

```
2 15363 270880 34698 17 2357023
```

### 输出

```
319392398
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
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF1697E
tag: ['动态规划 DP', '图论', '组合数学']
---

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of points.

Then $ n $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i, y_i \le 10^8 $ ).

No two points have the same coordinates (i. e. if $ i \ne j $ , then either $ x_i \ne x_j $ or $ y_i \ne y_j $ ).

## 输出格式

Print one integer — the number of ways to choose the colors for the points. Since it can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3
```

### 输出

```
240
```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0
```

### 输出

```
24
```



---

---
title: "Game of AI (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1704H1
tag: ['组合数学']
---

# Game of AI (easy version)

## 题目描述

这是本题的简单版本。简单版本与困难版本的区别在于对 $k$ 的约束和时间限制。此外，在本版本中，你只需要计算 $n=k$ 时的答案。只有当两个版本均被解决时，你才能进行 hack。

Cirno 正在玩一款战争模拟游戏，其中有 $n$ 座塔（编号为 $1$ 至 $n$）和 $n$ 个机器人（编号为 $1$ 至 $n$）。初始时，第 $i$ 座塔被第 $i$ 个机器人占据（$1 \le i \le n$）。

在游戏开始前，Cirno 首先选择一个长度为 $n$ 的排列 $p = [p_1, p_2, \ldots, p_n]$（一个长度为 $n$ 的排列是指每个 $1$ 到 $n$ 的整数恰好出现一次的数组）。接着，她选择一个序列 $a = [a_1, a_2, \ldots, a_n]$（满足 $1 \le a_i \le n$ 且 $a_i \ne i$ 对所有 $1 \le i \le n$ 成立）。

游戏包含 $n$ 轮攻击。在第 $i$ 轮中，如果第 $p_i$ 个机器人仍在游戏中，它将发起攻击，导致第 $a_{p_i}$ 座塔被第 $p_i$ 个机器人占据；原本占据第 $a_{p_i}$ 座塔的机器人将失去该塔。如果第 $p_i$ 个机器人已不在游戏中，此轮不会发生任何事。

每轮结束后，如果一个机器人未占据任何塔，它将被淘汰并退出游戏。注意一座塔不能同时被多个机器人占据，但一个机器人可以在游戏中占据多座塔。

游戏结束时，Cirno 将记录结果序列 $b = [b_1, b_2, \ldots, b_n]$，其中 $b_i$ 表示结束时占据第 $i$ 座塔的机器人编号。

然而，作为数学大师，她希望你解决以下计数问题而非亲自游戏：

计算所有可能的序列 $a$ 和排列 $p$ 能生成的不同序列对 $(a, b)$ 的数量。

由于结果可能很大，请输出其对 $M$ 取模后的值。

## 输入格式

仅一行包含两个正整数 $k$ 和 $M$（$1 \le k \le 5000$，$2 \le M \le 10^9$）。保证 $2^{18}$ 是 $M-1$ 的因数且 $M$ 是质数。

你需要计算当 $n=k$ 时的答案。

## 输出格式

输出一个整数——当 $n=k$ 时不同序列对的数量对 $M$ 取模后的结果。

## 说明/提示

当 $n=1$ 时，不存在合法的序列 $a$，因此答案为 $0$。

当 $n=2$ 时，唯一可能的数组 $a$ 是 $[2, 1]$：
- 当 $a$ 为 $[2, 1]$ 且 $p$ 为 $[1, 2]$ 时，最终序列 $b$ 为 $[1, 1]$。具体过程：
  - 第一轮，第一个机器人发起攻击并占领第 $2$ 座塔。此轮结束后，第二个机器人因失去所有塔而被淘汰。
  - 第二轮，第二个机器人已不在游戏中。
- 当 $a$ 为 $[2, 1]$ 且 $p$ 为 $[2, 1]$ 时，最终序列 $b$ 为 $[2, 2]$。具体过程：
  - 第一轮，第二个机器人发起攻击并占领第 $1$ 座塔。此轮结束后，第一个机器人被淘汰。
  - 第二轮，第一个机器人已不在游戏中。

因此当 $n=2$ 时，不同的序列对 $(a, b)$ 的数量为 $2$（即 $([2, 1], [1, 1])$ 和 $([2, 1], [2, 2])$）。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
1 998244353
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 998244353
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 998244353
```

### 输出

```
24
```

## 样例 #4

### 输入

```
8 998244353
```

### 输出

```
123391016
```



---

---
title: "Partial Virtual Trees"
layout: "post"
diff: 省选/NOI-
pid: CF1707D
tag: ['数学', '树形 DP', '容斥原理']
---

# Partial Virtual Trees

## 题目描述

Kawashiro Nitori is a girl who loves competitive programming. One day she found a rooted tree consisting of $ n $ vertices. The root is vertex $ 1 $ . As an advanced problem setter, she quickly thought of a problem.

Kawashiro Nitori has a vertex set $ U=\{1,2,\ldots,n\} $ . She's going to play a game with the tree and the set. In each operation, she will choose a vertex set $ T $ , where $ T $ is a partial virtual tree of $ U $ , and change $ U $ into $ T $ .

A vertex set $ S_1 $ is a partial virtual tree of a vertex set $ S_2 $ , if $ S_1 $ is a subset of $ S_2 $ , $ S_1 \neq S_2 $ , and for all pairs of vertices $ i $ and $ j $ in $ S_1 $ , $ \operatorname{LCA}(i,j) $ is in $ S_1 $ , where $ \operatorname{LCA}(x,y) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ x $ and $ y $ on the tree. Note that a vertex set can have many different partial virtual trees.

Kawashiro Nitori wants to know for each possible $ k $ , if she performs the operation exactly $ k $ times, in how many ways she can make $ U=\{1\} $ in the end? Two ways are considered different if there exists an integer $ z $ ( $ 1 \le z \le k $ ) such that after $ z $ operations the sets $ U $ are different.

Since the answer could be very large, you need to find it modulo $ p $ . It's guaranteed that $ p $ is a prime number.

## 输入格式

The first line contains two integers $ n $ and $ p $ ( $ 2 \le n \le 2000 $ , $ 10^8 + 7 \le p \le 10^9+9 $ ). It's guaranteed that $ p $ is a prime number.

Each of the next $ n-1 $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), representing an edge between $ u_i $ and $ v_i $ .

It is guaranteed that the given edges form a tree.

## 输出格式

The only line contains $ n-1 $ integers — the answer modulo $ p $ for $ k=1,2,\ldots,n-1 $ .

## 说明/提示

In the first test case, when $ k=1 $ , the only possible way is:

1. $ \{1,2,3,4\} \to \{1\} $ .

When $ k=2 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,3\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,4\} \to \{1\} $ .

When $ k=3 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,2\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,4\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,3\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,4\} \to \{1\} $ .

## 样例 #1

### 输入

```
4 998244353
1 2
2 3
1 4
```

### 输出

```
1 6 6
```

## 样例 #2

### 输入

```
7 100000007
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
1 47 340 854 880 320
```

## 样例 #3

### 输入

```
8 1000000007
1 2
2 3
3 4
4 5
5 6
6 7
7 8
```

### 输出

```
1 126 1806 8400 16800 15120 5040
```



---

---
title: "Bags with Balls"
layout: "post"
diff: 省选/NOI-
pid: CF1716F
tag: ['组合数学', 'Stirling 数']
---

# Bags with Balls

## 题目描述

# Bags with Balls 袋中之球


这里有 $ n $ 个袋子，每个袋子里面有 $ m $ 个带有从 $ 1 $ - $ m $ 标记的球。对于每一个 $ 1 $ ≤ $ i $ ≤ $ m $  来说，每个袋子中都一定存在一个带有 $ i $ 标记的球。

你需要在每个袋子中取出一个球 ( 所有的袋子都是不同的，比如在 $ 1 $ 号袋子取 $ 2 $ 号球 并且从 $ 2 $ 号袋子里取 $ 1 $ 号球 与 从 $ 1 $ 号袋子取 $ 1 $ 号球并且从 $ 2 $ 号袋子取 $ 2 $ 号球是不同的两种方案 ) 然后计算出你取出的标号是奇数的球的数量，记这个数量为 $ F $ 。

你的任务是计算所有可能的取球方案的 $ F^k $ 之和。

## 输入格式

第一行包含一个整数 $ t $ ( $ 1 \le t \le 5000 $ ) — 测试组数的数量

每组第一行输入三个整数 $ n $ , $ m $ 和 $ k $ ( $ 1 \le n, m \le 998244352 $ ; $ 1 \le k \le 2000 $ ).

## 输出格式

每组测试输出一个整数 —  $ F^k $ ( 意义见题面 ). 由于它可能会很大，请将它模 $ 998244353 $ 后输出.

## 样例 #1

### 输入

```
5
2 3 8
1 1 1
1 5 10
3 7 2000
1337666 42424242 2000
```

### 输出

```
1028
1
3
729229716
652219904
```



---

---
title: "Illumination"
layout: "post"
diff: 省选/NOI-
pid: CF1728G
tag: ['动态规划 DP', '状态合并', '组合数学', '容斥原理', '快速沃尔什变换 FWT']
---

# Illumination

## 题目描述

Consider a segment $ [0, d] $ of the coordinate line. There are $ n $ lanterns and $ m $ points of interest in this segment.

For each lantern, you can choose its power — an integer between $ 0 $ and $ d $ (inclusive). A lantern with coordinate $ x $ illuminates the point of interest with coordinate $ y $ if $ |x - y| $ is less than or equal to the power of the lantern.

A way to choose the power values for all lanterns is considered valid if every point of interest is illuminated by at least one lantern.

You have to process $ q $ queries. Each query is represented by one integer $ f_i $ . To answer the $ i $ -th query, you have to:

- add a lantern on coordinate $ f_i $ ;
- calculate the number of valid ways to assign power values to all lanterns, and print it modulo $ 998244353 $ ;
- remove the lantern you just added.

## 输入格式

The first line contains three integers $ d $ , $ n $ and $ m $ ( $ 4 \le d \le 3 \cdot 10^5 $ ; $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le m \le 16 $ ) — the size of the segment, the number of lanterns and the number of points of interest, respectively.

The second line contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \le l_i \le d - 1 $ ), where $ l_i $ is the coordinate of the $ i $ -th lantern.

The third line contains $ m $ integers $ p_1, p_2, \dots, p_m $ ( $ 1 \le p_i \le d - 1 $ ), where $ p_i $ is the coordinate of the $ i $ -th point of interest.

The fourth line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

The fifth line contains $ q $ integers $ f_1, f_2, \dots, f_q $ ( $ 1 \le f_i \le d - 1 $ ), where $ f_i $ is the integer representing the $ i $ -th query.

Additional constraint on the input: during the processing of each query, no coordinate contains more than one object (i. e. there cannot be two or more lanterns with the same coordinate, two or more points of interest with the same coordinate, or a lantern and a point of interest with the same coordinate).

## 输出格式

For each query, print one integer — the answer to it, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5
```

### 输出

```
48
47
47
```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3
```

### 输出

```
44
46
```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8
```

### 输出

```
413
```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9
```

### 输出

```
190431
187503
188085
189903
189708
```



---

---
title: "Function Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1731F
tag: ['组合数学']
---

# Function Sum

## 题目描述

Suppose you have an integer array $ a_1, a_2, \dots, a_n $ .

Let $ \operatorname{lsl}(i) $ be the number of indices $ j $ ( $ 1 \le j < i $ ) such that $ a_j < a_i $ .

Analogically, let $ \operatorname{grr}(i) $ be the number of indices $ j $ ( $ i < j \le n $ ) such that $ a_j > a_i $ .

Let's name position $ i $ good in the array $ a $ if $ \operatorname{lsl}(i) < \operatorname{grr}(i) $ .

Finally, let's define a function $ f $ on array $ a $ $ f(a) $ as the sum of all $ a_i $ such that $ i $ is good in $ a $ .

Given two integers $ n $ and $ k $ , find the sum of $ f(a) $ over all arrays $ a $ of size $ n $ such that $ 1 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ modulo $ 998\,244\,353 $ .

## 输入格式

The first and only line contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 50 $ ; $ 2 \leq k < 998\,244\,353 $ ).

## 输出格式

Output a single integer — the sum of $ f $ over all arrays $ a $ of size $ n $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

  $ f([1,1,1]) = 0 $  $ f([2,2,3]) = 2 + 2 = 4 $  $ f([1,1,2]) = 1 + 1 = 2 $  $ f([2,3,1]) = 2 $  $ f([1,1,3]) = 1 + 1 = 2 $  $ f([2,3,2]) = 2 $  $ f([1,2,1]) = 1 $  $ f([2,3,3]) = 2 $  $ f([1,2,2]) = 1 $  $ f([3,1,1]) = 0 $  $ f([1,2,3]) = 1 $  $ f([3,1,2]) = 1 $  $ f([1,3,1]) = 1 $  $ f([3,1,3]) = 1 $  $ f([1,3,2]) = 1 $  $ f([3,2,1]) = 0 $  $ f([1,3,3]) = 1 $  $ f([3,2,2]) = 0 $  $ f([2,1,1]) = 0 $  $ f([3,2,3]) = 2 $  $ f([2,1,2]) = 1 $  $ f([3,3,1]) = 0 $  $ f([2,1,3]) = 2 + 1 = 3 $  $ f([3,3,2]) = 0 $  $ f([2,2,1]) = 0 $  $ f([3,3,3]) = 0 $  $ f([2,2,2]) = 0 $ Adding up all of these values, we get $ 28 $ as the answer.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
28
```

## 样例 #2

### 输入

```
5 6
```

### 输出

```
34475
```

## 样例 #3

### 输入

```
12 30
```

### 输出

```
920711694
```



---

---
title: "List Generation"
layout: "post"
diff: 省选/NOI-
pid: CF1747E
tag: ['递推', '组合数学', '容斥原理']
---

# List Generation

## 题目描述

For given integers $ n $ and $ m $ , let's call a pair of arrays $ a $ and $ b $ of integers good, if they satisfy the following conditions:

- $ a $ and $ b $ have the same length, let their length be $ k $ .
- $ k \ge 2 $ and $ a_1 = 0, a_k = n, b_1 = 0, b_k = m $ .
- For each $ 1 < i \le k $ the following holds: $ a_i \geq a_{i - 1} $ , $ b_i \geq b_{i - 1} $ , and $ a_i + b_i \neq a_{i - 1} + b_{i - 1} $ .

Find the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ . Since the answer can be very large, output it modulo $ 10^9 + 7 $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t (1 \leq t \leq 10^4) $ — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ m $ $ (1 \leq n, m \leq 5 \cdot 10^6) $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^6 $ and the sum of $ m $ over all test cases does not exceed $ 5 \cdot 10^6 $ .

## 输出格式

For each test case, output a single integer — the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, the good pairs of arrays are

- $ ([0, 1], [0, 1]) $ , length = $ 2 $ .
- $ ([0, 1, 1], [0, 0, 1]) $ , length = $ 3 $ .
- $ ([0, 0, 1], [0, 1, 1]) $ , length = $ 3 $ .

Hence the sum of the lengths would be $ {2 + 3 + 3} = 8 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 2
100 100
```

### 输出

```
8
26
101
886336572
```



---

---
title: "Koxia and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1770E
tag: ['数学', '递推', '期望']
---

# Koxia and Tree

## 题目描述

Imi has an undirected tree with $ n $ vertices where edges are numbered from $ 1 $ to $ n-1 $ . The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ . There are also $ k $ butterflies on the tree. Initially, the $ i $ -th butterfly is on vertex $ a_i $ . All values of $ a $ are pairwise distinct.

Koxia plays a game as follows:

- For $ i = 1, 2, \dots, n - 1 $ , Koxia set the direction of the $ i $ -th edge as $ u_i \rightarrow v_i $ or $ v_i \rightarrow u_i $ with equal probability.
- For $ i = 1, 2, \dots, n - 1 $ , if a butterfly is on the initial vertex of $ i $ -th edge and there is no butterfly on the terminal vertex, then this butterfly flies to the terminal vertex. Note that operations are sequentially in order of $ 1, 2, \dots, n - 1 $ instead of simultaneously.
- Koxia chooses two butterflies from the $ k $ butterflies with equal probability from all possible $ \frac{k(k-1)}{2} $ ways to select two butterflies, then she takes the distance $ ^\dagger $ between the two chosen vertices as her score.

Now, Koxia wants you to find the expected value of her score, modulo $ 998\,244\,353^\ddagger $ .

 $ ^\dagger $ The distance between two vertices on a tree is the number of edges on the (unique) simple path between them.

 $ ^\ddagger $ Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 2 \leq k \leq n \leq 3 \cdot {10}^5 $ ) — the size of the tree and the number of butterflies.

The second line contains $ k $ integers $ a_1, a_2, \dots, a_k $ ( $ 1 \leq a_i \leq n $ ) — the initial position of butterflies. It's guaranteed that all positions are distinct.

The $ i $ -th line in following $ n − 1 $ lines contains two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \neq v_i $ ) — the vertices the $ i $ -th edge connects.

It is guaranteed that the given edges form a tree.

## 输出格式

Output a single integer — the expected value of Koxia's score, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the tree is shown below. Vertices containing butterflies are noted as bold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/b5933c313633856733c2f7b6fac2b7be83ed7851.png)There are only $ 2 $ butterflies so the choice of butterflies is fixed. Let's consider the following $ 4 $ cases:

- Edges are $ 1 \rightarrow 2 $ and $ 2 \rightarrow 3 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ doesn't move. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 1 \rightarrow 2 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ moves to vertex $ 2 $ , but butterfly on vertex $ 3 $ can't move to vertex $ 2 $ because it's occupied. The distance between vertices $ 2 $ and $ 3 $ is $ 1 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 2 \rightarrow 3 $ : butterflies on both vertex $ 1 $ and vertex $ 3 $ don't move. The distance between vertices $ 1 $ and $ 3 $ is $ 2 $ .
- Edges are $ 2 \rightarrow 1 $ and $ 3 \rightarrow 2 $ : butterfly on vertex $ 1 $ doesn't move, but butterfly on vertex $ 3 $ move to vertex $ 2 $ . The distance between vertices $ 1 $ and $ 2 $ is $ 1 $ .

Therefore, the expected value of Koxia's score is $ \frac {1+1+2+1} {4} = \frac {5} {4} $ , which is $ 748\,683\,266 $ after modulo $ 998\,244\,353 $ .

In the second test case, the tree is shown below. Vertices containing butterflies are noted as bold. The expected value of Koxia's score is $ \frac {11} {6} $ , which is $ 831\,870\,296 $ after modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1770E/c99c1f065a7b394b09acc90fcc6d66aa233890d9.png)

## 样例 #1

### 输入

```
3 2
1 3
1 2
2 3
```

### 输出

```
748683266
```

## 样例 #2

### 输入

```
5 3
3 4 5
1 2
1 3
2 4
2 5
```

### 输出

```
831870296
```



---

---
title: "Laboratory on Pluto"
layout: "post"
diff: 省选/NOI-
pid: CF1775F
tag: ['动态规划 DP', '组合数学', '构造']
---

# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 输入格式

The first line contains two integers $ t $ and $ u $ ( $ 1 \le t \le 2\cdot 10^5 $ , $ 1 \le u \le 2 $ ) — the number of test cases and the test type. If $ u=1 $ , you need to find any way to build the lab in an optimal way, and if $ u=2 $ , you need to calculate the number of ways to do it.

If $ u=2 $ , then in the following line of input there is a prime integer $ m $ ( $ 10^8 \le m \le 10^9 + 9 $ ), modulo which you need to calculate the number of ways.

Each of the following $ t $ lines of input contains a description of a test case consisting of one integer $ n $ ( $ 1 \le n \le 4\cdot 10^5 $ ) — the number of blocks the lab should consist of.

It is guaranteed that if $ u=1 $ , then the sum of $ n $ on all test cases does not exceed $ 8\cdot10^5 $ .

## 输出格式

For each test case, output the answers in the format below, separating them with a newline. The output format depends on $ u $ in the input data.

If $ u=1 $ , in the first line you need to print two integers $ h $ and $ w $ —the height and width of the area in which the lab should be built. Then, in each of the following $ h $ lines, you must output a line $ s_i $ consisting of $ w $ characters "\#" and ".". If the $ j $ -th character of the row $ s_i $ is "\#", then the corresponding square must contain a block of laboratory, otherwise, it is considered empty. Thus, we get a matrix of symbols. The condition must also be met that the first and last rows of the matrix, as well as the first and last columns, must have at least one character "\#", otherwise we could output the same lab layout, but with smaller $ h $ and $ w $ . If there are many options to build an optimal lab, you can print any of them.

If $ u=2 $ , you need to print two integers $ p $ and $ c $ — the number of outside walls in an optimal lab, and the remainder of the number of ways by prime modulo $ m $ .

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7
```

### 输出

```
1 1
#
1 2
##
2 4
.###
####
```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7
```

### 输出

```
4 1
6 2
12 22
```



---

---
title: "Bracket Insertion"
layout: "post"
diff: 省选/NOI-
pid: CF1781F
tag: ['动态规划 DP', '组合数学', '前缀和', '概率论']
---

# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 输入格式

The only line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 500 $ ; $ 0 \le q \le 10^4 $ ). Here $ n $ is equal to the number of bracket insertion operations, and the probability that Vika chooses string "()" on every step of the algorithm is equal to $ p = q \cdot 10^{-4} $ .

## 输出格式

Print the probability that Vika's final bracket sequence will be regular, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500
```

### 输出

```
249561089
```

## 样例 #2

### 输入

```
2 6000
```

### 输出

```
519087064
```

## 样例 #3

### 输入

```
5 4000
```

### 输出

```
119387743
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
title: "Graph Coloring (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1792F1
tag: ['动态规划 DP', '图论', '组合数学']
---

# Graph Coloring (easy version)

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

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^3 $ ).

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



---

---
title: "Count Voting"
layout: "post"
diff: 省选/NOI-
pid: CF1799G
tag: ['动态规划 DP', '组合数学', '容斥原理']
---

# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the number of people.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ) — desired number of votes. It is guaranteed, that $ \sum\limits_{i=1}^{n} c_i = n $ .

The third line contains $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 1 \leq t_i \leq n $ ) — team numbers.

## 输出格式

Print a single integer — the number of possible votings by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4
```

### 输出

```
5
```



---

---
title: "Another n-dimensional chocolate bar"
layout: "post"
diff: 省选/NOI-
pid: CF1801F
tag: ['动态规划 DP', '数学']
---

# Another n-dimensional chocolate bar

## 题目描述

Mom bought the boy Vasya a $ n $ -dimensional chocolate bar, which is a $ n $ -dimensional cube with the length of each side equal to $ 1 $ . The chocolate is planned to be divided into slices. According to the $ i $ th dimension, it can be divided by hyperplanes into $ a_i $ equal parts. Thus, the chocolate is divided in total into $ a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n $ slices, each slice has a length of $ i $ -th dimension equal to $ \frac{1}{a_i} $ , respectively, the volume of each slice is $ \frac{1}{a_1 a_2 \cdots a_n} $ .Vasya and his friends want to cut a chocolate bar to get at least $ k $ pieces, while Vasya wants to maximize the volume of the smallest of them. It is possible to cut the chocolate bar only at the junction of the lobules, and each incision must pass through the entire chocolate bar along some hyperplane involved in the formation of lobules. Only after making all the cuts, Vasya disassembles the chocolate into pieces.

More formally, Vasya wants to choose the numbers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le a_i $ ) — the number of parts into which Vasya will cut the chocolate bar along each dimension. The condition $ b_1 \cdot b_2 \cdot \ldots \cdot b_n \ge k $ must be met to get at least $ k $ pieces after all cuts. It can be noted that with optimal cutting with such parameters, the minimum piece will contain $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor $ slices, and its volume will be equal to $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} $ .

Vasya wants to get the maximum possible value of the volume of the minimum piece multiplied by $ k $ , that is, he wants to maximize the number of $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} \cdot k $ . Help him with this.

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1 \le n \le 100 $ , $ 1 \le k \le 10^7) $ — the dimension of the chocolate bar, and how many parts it needs to be divided into.

The second line contains $ n $ integers $ a_1,\ a_2,\ \dots,\ a_n $ $ (1 \le a_i \le 10^7) $ — the number of pieces on which the chocolate is placed along each of the dimensions.

## 输出格式

Print one number — the maximum possible volume of the smallest of the obtained pieces, multiplied by $ k $ , with an absolute or relative error of no more than $ 10^{-9} $ .

If it is impossible to cut a chocolate bar into at least $ k $ pieces under the given restrictions, output $ 0 $ .

## 说明/提示

In the first example, a one – dimensional chocolate bar can be divided as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/f5840bc9b6fba83080f4985e511bff8530afd934.png)

Then the answer will be $ \frac{2}{5} \cdot 2 = 0.8 $

In the second example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/627b4397ae726c6c50e5194d712fdc53a32a0b7f.png)

Then the answer will be $ \frac{2}{5} \cdot \frac{3}{10} \cdot 6 = 0.72 $

In the third example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/40196c672f43b7ab300ba0a5b9511f838e6ac4ad.png) Then the answer will be $ \frac{2}{4} \cdot \frac{1}{4} \cdot 7 = 0.875 $

## 样例 #1

### 输入

```
1 2
5
```

### 输出

```
0.8
```

## 样例 #2

### 输入

```
2 6
5 10
```

### 输出

```
0.72
```

## 样例 #3

### 输入

```
2 7
4 4
```

### 输出

```
0.875
```

## 样例 #4

### 输入

```
2 3
4 5
```

### 输出

```
0.75
```

## 样例 #5

### 输入

```
4 444
57 179 239 2
```

### 输出

```
0.97557326850704739751
```

## 样例 #6

### 输入

```
2 5
2 2
```

### 输出

```
0
```



---

---
title: "M-tree"
layout: "post"
diff: 省选/NOI-
pid: CF1810F
tag: ['数学', '线段树']
---

# M-tree

## 题目描述

A rooted tree is called good if every vertex of the tree either is a leaf (a vertex with no children) or has exactly $ m $ children.

For a good tree, each leaf $ u $ has a positive integer $ c_{u} $ written on it, and we define the value of the leaf as $ c_{u} + \mathrm{dep}_{u} $ , where $ \mathrm{dep}_{u} $ represents the number of edges of the path from vertex $ u $ to the root (also known as the depth of $ u $ ). The value of a good tree is the maximum value of all its leaves.

Now, you are given an array of $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ , which are the integers that should be written on the leaves. You need to construct a good tree with $ n $ leaves and write the integers from the array $ a $ to all the leaves. Formally, you should assign each leaf $ u $ an index $ b_{u} $ , where $ b $ is a permutation of length $ n $ , and represent that the integer written on leaf $ u $ is $ c_u = a_{b_{u}} $ . Under these constraints, you need to minimize the value of the good tree.

You have $ q $ queries. Each query gives you $ x $ , $ y $ and changes $ a_{x} $ to $ y $ , and after that, you should output the minimum value of a good tree based on the current array $ a $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Their description follows.

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 1\le n,q \le 2 \cdot 10^5 $ , $ 2\le m \le 2\cdot 10^5 $ , $ n \equiv 1 \pmod {m - 1} $ ) — the number of the leaves, the constant $ m $ , and the number of queries.

The second line contains $ n $ integers $ a_{1},a_{2}, \ldots, a_{n} $ ( $ 1 \le a_{i} \le n $ ) — the initial array.

For the following $ q $ lines, each line contains two integers $ x $ and $ y $ ( $ 1\le x,y\le n $ ), representing a query changing $ a_{x} $ to $ y $ .

It is guaranteed that both the sum of $ n $ and the sum of $ q $ do not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ q $ integers in one line, the $ i $ -th of which is the minimum tree value after the $ i $ -th change.

## 说明/提示

In the first test case, after the first query, the current array $ a $ is $ [4,3,4,4,5] $ . We can construct such a good tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1810F/88a3cbbc1b6fe16413368f21af94bcc26c8f2029.png)The first number inside a vertex is its index (in this problem, the indices do not matter, but help to understand the figure). If a vertex is a leaf, the second number inside the vertex is the integer written on it.

We can tell that $ \mathrm{dep}_{3}=\mathrm{dep}_{4}=1,\mathrm{dep}_{5}=\mathrm{dep}_{6}=\mathrm{dep}_{7}=2 $ and the value of the tree, which is the maximum value over all leaves, is $ 5+1=6 $ . The value of leaves $ 5 $ , $ 6 $ , $ 7 $ is also equal to $ 6 $ . It can be shown that this tree has the minimum value over all valid trees.

## 样例 #1

### 输入

```
3
5 3 3
3 3 4 4 5
1 4
2 4
3 5
5 2 4
3 3 4 4 5
1 4
2 5
3 5
4 5
7 3 4
1 2 2 3 3 3 4
1 4
2 1
5 5
6 6
```

### 输出

```
6 6 6
7 7 7 8
6 6 6 7
```



---

---
title: "Balanced Subsequences"
layout: "post"
diff: 省选/NOI-
pid: CF1924D
tag: ['组合数学', 'Catalan 数']
---

# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 3 \cdot 10^3 $ ). Description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m, k \le 2 \cdot 10^3 $ )

## 输出格式

For each test case, print one integer — the answer to the problem.

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1
```

### 输出

```
2
0
4
```



---

---
title: "2..3...4.... Wonderful! Wonderful!"
layout: "post"
diff: 省选/NOI-
pid: CF1930E
tag: ['组合数学', '排列组合']
---

# 2..3...4.... Wonderful! Wonderful!

## 题目描述

Stack has an array $ a $ of length $ n $ such that $ a_i = i $ for all $ i $ ( $ 1 \leq i \leq n $ ). He will select a positive integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ) and do the following operation on $ a $ any number (possibly $ 0 $ ) of times.

- Select a subsequence $ ^\dagger $ $ s $ of length $ 2 \cdot k + 1 $ from $ a $ . Now, he will delete the first $ k $ elements of $ s $ from $ a $ . To keep things perfectly balanced (as all things should be), he will also delete the last $ k $ elements of $ s $ from $ a $ .

Stack wonders how many arrays $ a $ can he end up with for each $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ). As Stack is weak at counting problems, he needs your help.

Since the number of arrays might be too large, please print it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements. For example, $ [1, 3] $ , $ [1, 2, 3] $ and $ [2, 3] $ are subsequences of $ [1, 2, 3] $ . On the other hand, $ [3, 1] $ and $ [2, 1, 3] $ are not subsequences of $ [1, 2, 3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^6 $ ) — the length of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test, on a new line, print $ \lfloor \frac{n-1}{2} \rfloor $ space-separated integers — the $ i $ -th integer representing the number of arrays modulo $ 998\,244\,353 $ that Stack can get if he selects $ k=i $ .

## 说明/提示

In the first test case, two $ a $ are possible for $ k=1 $ :

- $ [1,2,3] $ ;
- $ [2] $ .

In the second test case, four $ a $ are possible for $ k=1 $ :

- $ [1,2,3,4] $ ;
- $ [1,3] $ ;
- $ [2,3] $ ;
- $ [2,4] $ .

In the third test case, two $ a $ are possible for $ k=2 $ :

- $ [1,2,3,4,5] $ ;
- $ [3] $ .

## 样例 #1

### 输入

```
4
3
4
5
10
```

### 输出

```
2 
4 
10 2 
487 162 85 10
```



---

---
title: "Nene vs. Monsters (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1956E2
tag: ['数学']
---

# Nene vs. Monsters (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

Nene is fighting with $ n $ monsters, located in a circle. These monsters are numbered from $ 1 $ to $ n $ , and the $ i $ -th ( $ 1 \le i \le n $ ) monster's current energy level is $ a_i $ .

Since the monsters are too strong, Nene decided to fight with them using the Attack Your Neighbour spell. When Nene uses this spell, the following actions happen in the following order one by one:

- The $ 1 $ -st monster attacks the $ 2 $ -nd monster;
- The $ 2 $ -nd monster attacks the $ 3 $ -rd monster;
- $ \ldots $
- The $ (n-1) $ -th monster attacks the $ n $ -th monster;
- The $ n $ -th monster attacks the $ 1 $ -st monster.

When the monster with energy level $ x $ attacks the monster with the energy level $ y $ , the energy level of the defending monster becomes $ \max(0, y-x) $ (the energy level of the attacking monster remains equal to $ x $ ).

Nene is going to use this spell $ 10^{100} $ times and deal with the monsters that will still have a non-zero energy level herself. She wants you to determine which monsters will have a non-zero energy level once she will use the described spell $ 10^{100} $ times.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of test cases follows.

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of monsters.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the current energy levels of monsters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case,

- in the first line output an integer $ m $ — the number of monsters with non-zero energy level after $ 10^{100} $ uses of the spell;
- in the second line of output $ m $ integers $ i_1,i_2,\ldots,i_m $ ( $ 1 \le i_1 < i_2 < \ldots < i_m \le n $ ) — the indices of these monsters in the increasing order.

If $ m=0 $ , you may either output an empty line or don't output it.

## 说明/提示

In the first test case, the following actions happen during the first $ 3 $ uses of the spell in this order:

- Nene uses the Attack Your Neighbour spell for the first time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 5-2)=3 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 3-3)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the second time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 3-2)=1 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-1)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the third time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 1-2)=0 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-0)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ .

After each of the next uses of the spell, energy levels of monsters do not change. Thus, only the $ 1 $ -st monster has a non-zero energy level in the end.

In the second test case, both monsters initially have zero energy level.

## 样例 #1

### 输入

```
5
3
2 5 3
2
0 0
4
1 5 7 2
4
4 2 1 2
13
1 1 4 5 1 4 1 9 1 9 8 1 0
```

### 输出

```
1
1 
0

1
1 
2
1 3 
6
1 3 6 8 10 12
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
title: "Many Games"
layout: "post"
diff: 省选/NOI-
pid: CF2023D
tag: ['动态规划 DP', '数学', '剪枝', '概率论']
---

# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of games offered to play.

The $ i $ -th of the following $ n $ lines contains two integers $ p_i $ and $ w_i $ ( $ 1 \leq p_i \leq 100 $ , $ 1 \leq w_i, p_i \cdot w_i \leq 2 \cdot 10^5 $ ) — the probability of winning and the size of the winnings in the $ i $ -th game.

## 输出格式

Output a single number — the maximum expected value of winnings in the casino that can be obtained by choosing some subset of games.

Your answer will be accepted if the relative or absolute error does not exceed $ 10^{-6} $ . Formally, if $ a $ is your answer and $ b $ is the jury's answer, it will be accepted if $ \frac{|a-b|}{\max(b, 1)} \le 10^{-6} $ .

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200
```

### 输出

```
112.00000000
```

## 样例 #2

### 输入

```
2
100 1
100 1
```

### 输出

```
2.00000000
```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1
```

### 输出

```
20.00000000
```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79
```

### 输出

```
395.20423800
```



---

---
title: "The Destruction of the Universe (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G1
tag: ['组合数学', '排列组合']
---

# The Destruction of the Universe (Easy Version)

## 题目描述

这是问题的简单版本，满足 $ n \leq 5000 $。如果两个版本的问题都被解决，才可以进行挑战。

猩猩是强大的生物，它们只需要 $1$ 个单位时间就能摧毁宇宙中每一个脆弱的星球！

宇宙中有 $n$ 个星球。每个星球在一个区间 $[l, r]$ 内是脆弱的，期间随时可能被猩猩摧毁。猩猩可以把任意一个星球的脆弱区间扩展 $1$ 个单位。

具体来说，如果对某个星球 $p$ 的脆弱区间 $[l_p, r_p]$ 进行扩展，结果可以是 $[l_p - 1, r_p]$ 或 $[l_p, r_p + 1]$ 中的任一个。

给定一组星球，如果它们的所有脆弱区间中至少有一个共同点，那么这组星球就能被摧毁。我们把这样一组星球的“得分”定义为实现摧毁所需的最小扩展次数。

猩猩关注的是宇宙中所有非空星球子集的得分之和。由于可能结果非常大，请输出答案对 $998\,244\,353$ 取模后的结果。

## 输入格式

第一行是一个整数 $t$（$1 \leq t \leq 1000$）——测试用例的数量。

每个测试用例的第一行有一个整数 $n$（$1 \leq n \leq 5000$）——星球的数量。

接下来的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq n$），表示第 $i$ 个星球的初始脆弱区间。

保证所有测试用例中，星球数量的总和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——所有非空星球子集的得分之和，对 $998\,244\,353$ 取模。

## 说明/提示

以第一个测试用例为例，需考虑以下七个非空子集：

- 对于子集 $\{[1,1]\}, \{[2,3]\}, \{[3,3]\}$，得分为 $0$。
- 对于子集 $\{[2,3], [3,3]\}$，得分为 $0$，因为点 $3$ 已经位于这两个星球的脆弱区间之内。
- 对于子集 $\{[1,1], [2,3]\}$，得分为 $1$。通过一次操作，将第二个星球的脆弱区间改为 $[1,3]$，这样两个星球的脆弱区间都包含点 $1$。
- 对于子集 $\{[1,1], [3,3]\}$，得分为 $2$。通过两次操作，将第一个星球的脆弱区间改为 $[1,3]$，使得两个星球的区间都包含点 $3$。
- 对于子集 $\{[1,1], [2,3], [3,3]\}$，得分为 $2$。通过一次操作把第一个星球的区间改为 $[1,2]$，再用一次操作把第三个星球的区间改为 $[2,3]$，这样三个星球都包含点 $2$。

所以，第一个测试用例中，所有非空子集的得分之和为 $0 \times 4 + 1 \times 1 + 2 \times 2 = 5$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "The Destruction of the Universe (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G2
tag: ['组合数学', '排列组合', '前缀和']
---

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of planets in the universe.

The following $ n $ lines contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ) — the initial interval of vulnerability of the $ i $ -th planet.

It is guaranteed that the sum of $ n $ does not exceed $ 10^6 $ over all test cases.

## 输出格式

For each test case, output an integer — the sum of scores to destroy all non-empty subsets of the planets in the universe, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "Barrels"
layout: "post"
diff: 省选/NOI-
pid: CF2038E
tag: ['数学', '贪心']
---

# Barrels

## 题目描述

假设你拥有 $n$ 个水桶，它们依次排放，编号为 $1$ 到 $n$。

每个水桶是相同的，底面积为一个单位，因此水桶内的水量对应水柱的高度。起初，第 $i$ 个水桶中含有 $v_i$ 单位的水。

相邻的水桶之间通过管道相连。具体来说，对于每个从 $1$ 到 $n-1$ 的 $i$，水桶 $i$ 与水桶 $i+1$ 通过一个高度为 $h_i$ 的水平管道相连。管道的宽度可以忽略不计。这些管道可以让水在水桶之间流动。

现在，你想对这些水桶进行操作。你的目标是通过向水桶中投放粘土来最大化第一个水桶中的水量。每一步，你可以选择任意一个水桶，向其中添加一单位的粘土。粘土的单位体积与水相同，但粘土比水重且不会与水混合，因此它会下沉并均匀分布在桶底。

由于粘土具有黏性，当粘土的高度足够时，它会封住管道。更确切地说，如果管道的高度为 $h$，当粘土的高度达到或低于 $h$ 时，管道仍然能正常工作。然而，一旦你向水桶中多加了一单位的粘土，管道就会立刻被封住，阻止水在水桶之间流动。

你拥有大量的粘土，因此可以多次执行上述操作。但在每次操作之后，你需要等待水达到新的平衡状态。

你能让第一个水桶中的水量达到的最大值是多少？

假定水桶足够高，因此不会溢出，并且可以忽略管道的宽度。

## 输入格式

第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示水桶的数量。

第二行包含 $n$ 个整数 $v_1, v_2, \dots, v_n$（$0 \le v_i \le 10^6$），表示每个水桶的初始水量。

第三行包含 $n - 1$ 个整数 $h_1, h_2, \dots, h_{n - 1}$（$1 \le h_i \le 10^6$），表示水桶之间的管道高度。

请注意，输入数据保证水最初处于平衡状态。

## 输出格式

输出一个数字，表示第一个水桶中可能达到的最大水量。你的答案将被认为是正确的，如果其绝对误差或相对误差不超过 $10^{-6}$。

格式上，设你的答案为 $a$，标准答案为 $b$。当且仅当 $\frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6}$ 时，答案被接受。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
1 2
2
```

### 输出

```
2.500000000000000
```

## 样例 #2

### 输入

```
3
3 0 0
6 9
```

### 输出

```
3.000000000000000
```

## 样例 #3

### 输入

```
5
10 0 0 0 5
11 1 2 5
```

### 输出

```
11.916666666666667
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
title: "Narrower Passageway"
layout: "post"
diff: 省选/NOI-
pid: CF2045E
tag: ['数学', 'ST 表', '单调栈']
---

# Narrower Passageway

## 题目描述

你是 ICPC 王国的一名战略家，近日你收到情报，王国附近的一条狭窄通道将遭遇怪物的袭击。这条通道可以简化为一个 2 行 $N$ 列的网格。我们用 $(r, c)$ 表示网格中第 $r$ 行第 $c$ 列的格子。每天会安排一个力量值为 $P_{r, c}$ 的士兵驻守在 $(r, c)$ 位置上。

这里常年大雾，每列都有 $50\%$ 的概率被雾气笼罩。一旦某列被雾气覆盖，两个驻守该列的士兵将无法执行任务。否则，士兵将正常部署。

我们定义一个连通区域 $[u, v]$（$u \leq v$）为从第 $u$ 列到第 $v$ 列连续且无雾的列。下面的示例中，灰色部分代表被雾覆盖的格子，共有四个连通区域：$[1, 2]$、$[4, 6]$、$[9, 9]$ 和 $[11, 11]$。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/47744495c3a12fb362399d4924e5c674c3e83888.png)

连通区域 $[u, v]$ 的力量可以这样计算。设 $m_1$ 和 $m_2$ 分别为该区域内第一行和第二行士兵力量的最大值。具体来说，对于 $r \in \{1, 2\}$，有 $m_r = \max (P_{r, u}, P_{r, u + 1}, \dots, P_{r, v})$。如果 $m_1 = m_2$，则该区域的力量是 $0$；否则，力量为 $\min (m_1, m_2)$。

一个工作日的总力量定义为所有连通区域力量的总和。请计算在任意一天部署的期望总力量。

## 输入格式

第一行是一个整数 $N$，表示列数（$1 \leq N \leq 100\,000$）。

接下来的两行，每行包含 $N$ 个整数，表示士兵的力量值 $P_{r, c}$（$1 \leq P_{r, c} \leq 200\,000$）。

## 输出格式

设 $M = 998\,244\,353$。可以证明期望总力量表示为一个不可约分数 $\frac{x}{y}$，其中 $x$ 和 $y$ 是整数，且 $y \not\equiv 0 \pmod{M}$。请输出一个整数 $k$，使得 $0 \leq k < M$ 且 $k \cdot y \equiv x \pmod{M}$。

## 说明/提示

样例输入/输出 #1 解释

这条通道可能有 $8$ 种不同的布局。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/70a3bbc18f3f05a2f49fd32453ba66ee47116d57.png)

每种布局出现的概率是相同的。因此，期望总力量为 $(0 + 5 + 10 + 5 + 5 + 0 + 5 + 0) / 8 = \frac{15}{4}$。由于 $249\,561\,092 \cdot 4 \equiv 15 \pmod{998\,244\,353}$，所以样例的输出为 $249\,561\,092$。

样例输入/输出 #2 解释

期望总力量为 $\frac{67}{16}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
8 4 5
5 4 8
```

### 输出

```
249561092
```

## 样例 #2

### 输入

```
5
10 20 5 8 5
5 20 7 5 8
```

### 输出

```
811073541
```



---

---
title: "Club of Young Aircraft Builders (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF2066D2
tag: ['动态规划 DP', '组合数学']
---

# Club of Young Aircraft Builders (hard version)

## 题目描述

这是该问题的困难版本。各版本间的区别在于此版本中不要求所有 $a_i = 0$。只有当您解决了该问题的所有版本时才能进行 hack。

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层恰好住着一位居民。

今天全体居民有一个重要目标：共同发射至少 $c$ 架纸飞机。居民们将依次发射飞机。当第 $i$ 层的居民发射一架飞机时，从第 $1$ 层到第 $i$ 层的所有居民都能看到它降落到地面的过程。如果从第 $i$ 层居民的视角看，已有至少 $c$ 架飞机被发射，则该居民自己不会再发射更多飞机。已知到当天结束时，从每位居民的视角看至少发射了 $c$ 架飞机，且总共发射了 $m$ 架飞机。

您仔细记录了这次快闪活动，记录了每架飞机的发射者所在楼层。遗憾的是，关于部分飞机的具体发射者信息已经丢失。请找出填补空缺信息使其可信的方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

也可能您的记录存在错误，导致无法恢复任何有效信息。此时答案视为 $0$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含三个整数 $n, c, m$（$1 \le n \le 100$，$1 \le c \le 100$，$c \le m \le n \cdot c$）——建筑物的层数、所需最小飞机数、实际发射的飞机数。

每个测试用例的第二行包含 $m$ 个整数 $a_1, a_2, \ldots, a_m$（$0 \le a_i \le n$）——$a_i$ 表示发射第 $i$ 架飞机的居民所在楼层；$a_i = 0$ 表示空缺。

保证所有测试用例的 $m$ 值之和不超过 $10^4$。

## 输出格式

对于每个测试用例，输出用 $1$ 至 $n$ 填补空缺信息使其可信的方案数对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试样例中，所有六种可能的填补方案如下：
1. $[1, 1, 3, 3]$
2. $[1, 2, 3, 3]$
3. $[1, 3, 2, 3]$
4. $[2, 1, 3, 3]$
5. $[2, 2, 3, 3]$
6. $[3, 1, 2, 3]$

注意数组 $[2, 3, 1, 3]$ 不是有效方案，因为第三架飞机不可能由第 $1$ 层的居民发射——从他们的视角看，当时已有 $c = 2$ 架飞机被发射。

同样地，数组 $[1, 1, 2, 3]$ 也不是有效方案，因为从第 $3$ 层居民的视角看，仅发射了 $1$ 架飞机，而 $c = 2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0
6 1 3
2 0 0
2 3 5
0 0 1 0 2
3 3 4
3 3 3 0
2 1 2
0 1
2 1 2
0 2
5 3 12
0 0 1 0 2 4 0 0 0 5 0 5
```

### 输出

```
6
190
3
2
0
0
1
14
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
title: "Wish Upon a Satellite (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2084G1
tag: ['动态规划 DP', '数学']
---

# Wish Upon a Satellite (Easy Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，本版本中 $t \le 1000$、$n \le 5000$ 且所有测试用例的 $n$ 之和不超过 $5000$。只有当你解决了该问题的所有版本时才能进行 hack。

对于一个长度为 $k$ 的非空序列 $c$，定义 $f(c)$ 如下：

- Turtle 和 Piggy 正在一个序列上玩游戏。他们被给定序列 $c_1, c_2, \ldots, c_k$，由 Turtle 先手。Turtle 和 Piggy 轮流进行操作（Turtle 第一步，Piggy 第二步，Turtle 第三步，依此类推）。
- 游戏规则如下：
  - 设当前序列长度为 $m$。如果 $m = 1$，游戏结束。
  - 如果游戏未结束且轮到 Turtle，Turtle 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\min(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
  - 如果游戏未结束且轮到 Piggy，Piggy 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\max(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
- Turtle 希望最终 $c_1$ 的值最大化，而 Piggy 希望最终 $c_1$ 的值最小化。
- $f(c)$ 表示双方都采取最优策略时，最终 $c_1$ 的值。

对于一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$，Turtle 定义该排列的美观度为 $\sum\limits_{i = 1}^n \sum\limits_{j = i}^n f([p_i, p_{i + 1}, \ldots, p_j])$（即所有 $p$ 的非空子段 $^{\text{†}}$ $c$ 的 $f(c)$ 之和）。

Piggy 给 Turtle 一个长度为 $n$ 的排列 $a$，其中部分元素缺失（用 $0$ 表示）。

Turtle 请你确定一个排列 $b$，满足以下条件：

- $b$ 可以通过填充 $a$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $a_i \ne 0$，则 $b_i = a_i$）。
- 排列 $b$ 的美观度最大化。

为了方便，你只需要找到这样的排列 $b$ 的最大美观度。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

$^{\text{†}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 1000$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5000$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le n$）。保证 $a$ 中非 $0$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——排列 $b$ 的最大美观度。


## 说明/提示

- 在第一个测试用例中，美观度最大的排列 $b$ 是 $[1, 2]$。$[1, 2]$ 的美观度为 $4$，因为 $f([1]) + f([2]) + f([1, 2]) = 1 + 2 + 1 = 4$。如果 $c = [1, 2]$，则 $f(c) = 1$，因为 Turtle 只能选择 $i = 1$，并将 $c_1$ 设为 $\min(c_1, c_2) = 1$。

- 在第二个测试用例中，美观度最大的排列之一是 $[3, 2, 1]$。$[3, 2, 1]$ 的美观度为 $12$，因为 $f([3]) + f([2]) + f([1]) + f([3, 2]) + f([2, 1]) + f([3, 2, 1]) = 3 + 2 + 1 + 2 + 1 + 3 = 12$。

- 在第三个测试用例中，美观度最大的排列之一是 $[2, 1, 3]$。

- 在第四个测试用例中，如果 $c = [3, 2, 4, 5, 1]$，则 $f(c) = 3$。一种可能的游戏过程如下：
  - Turtle 选择 $i = 3$，将 $c_3$ 设为 $\min(c_3, c_4) = 4$ 并删除 $c_4$。序列变为 $[3, 2, 4, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3, 4, 1]$。
  - Turtle 选择 $i = 2$，将 $c_2$ 设为 $\min(c_2, c_3) = 1$ 并删除 $c_3$。序列变为 $[3, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3]$。
  - 序列长度为 $1$，游戏结束。最终 $c_1$ 的值为 $3$。

- 在第五个测试用例中，美观度最大的排列之一是 $[1, 3, 2, 5, 6, 4, 7]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
1 0
3
0 0 0
3
0 1 0
5
3 2 4 5 1
7
0 3 2 5 0 0 0
10
1 2 6 5 8 9 0 0 0 0
5
0 4 1 0 0
5
0 1 5 2 3
```

### 输出

```
4
12
11
44
110
300
45
40
```



---

---
title: "Homework"
layout: "post"
diff: 省选/NOI-
pid: CF2097D
tag: ['数学', '线性代数', '高斯消元', '标签465']
---

# Homework

## 题目描述

有些老师在"天狼星"教育中心工作的同时还在大学学习。这种情况下，出差并不能免除他们完成作业的义务，因此他们直接在飞机上做作业。Artem 就是这样一位老师，他在大学被布置了以下作业。

对于任意长度为偶数 $m$ 的字符串 $a$，他可以执行以下操作。Artem 将字符串 $a$ 分成两个长度相等的部分 $x$ 和 $y$，然后执行以下三种操作之一：

- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $x_i = (x_i + y_i) \bmod 2$；
- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $y_i = (x_i + y_i) \bmod 2$；
- 对字符串 $x$ 和 $y$ 分别执行任意次数的上述操作（递归应用），注意此时 $x$ 和 $y$ 的长度必须为偶数。

操作完成后，字符串 $a$ 将被替换为按原顺序连接的 $x$ 和 $y$。不幸的是，Artem 在飞机上睡着了，所以你需要替他完成作业。Artem 有两个长度为 $n$ 的二进制字符串 $s$ 和 $t$，每个字符串都由 $n$ 个字符 0 或 1 组成。请判断是否可以通过任意次数的操作使字符串 $s$ 等于字符串 $t$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^5$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^6$）——字符串 $s$ 和 $t$ 的长度。

每个测试用例的第二行包含长度为 $n$ 的字符串 $s$，仅由字符 0 和 1 组成。

每个测试用例的第三行包含长度为 $n$ 的字符串 $t$，仅由字符 0 和 1 组成。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，如果可以使字符串 $s$ 等于字符串 $t$，则输出 "Yes"（不带引号），否则输出 "No"。

答案大小写不敏感。例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被接受为肯定回答。


## 说明/提示

在第一个测试用例中，字符串 00001001 可以通过两次操作转换为 10101001。操作序列如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097D/168d2d9e52ff66afe40aa42de1043dc65663a285.png)

在第二个测试用例中，字符串 00000000 无法转换为除自身外的任何其他字符串，因为在任何操作中都无法产生非零元素。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
8
00001001
10101001
8
00000000
00001001
6
010110
100010
```

### 输出

```
Yes
No
Yes
```



---

---
title: "Number Challenge"
layout: "post"
diff: 省选/NOI-
pid: CF235E
tag: ['数学', '枚举', '概率论']
---

# Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235E/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 输入格式

The first line contains three space-separated integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=2000 $ ).

## 输出格式

Print a single integer — the required sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
20

```

## 样例 #2

### 输入

```
4 4 4

```

### 输出

```
328

```

## 样例 #3

### 输入

```
10 10 10

```

### 输出

```
11536

```



---

---
title: "Painting The Wall"
layout: "post"
diff: 省选/NOI-
pid: CF398B
tag: ['数学', '概率论', '期望']
---

# Painting The Wall

## 题目描述

User ainta decided to paint a wall. The wall consists of $ n^{2} $ tiles, that are arranged in an $ n×n $ table. Some tiles are painted, and the others are not. As he wants to paint it beautifully, he will follow the rules below.

1. Firstly user ainta looks at the wall. If there is at least one painted cell on each row and at least one painted cell on each column, he stops coloring. Otherwise, he goes to step 2.
2. User ainta choose any tile on the wall with uniform probability.
3. If the tile he has chosen is not painted, he paints the tile. Otherwise, he ignores it.
4. Then he takes a rest for one minute even if he doesn't paint the tile. And then ainta goes to step 1.

However ainta is worried if it would take too much time to finish this work. So he wants to calculate the expected time needed to paint the wall by the method above. Help him find the expected time. You can assume that choosing and painting any tile consumes no time at all.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=2·10^{3} $ ; $ 0<=m<=min(n^{2},2·10^{4}) $ ) — the size of the wall and the number of painted cells.

Next $ m $ lines goes, each contains two integers $ r_{i} $ and $ c_{i} $ ( $ 1<=r_{i},c_{i}<=n $ ) — the position of the painted cell. It is guaranteed that the positions are all distinct. Consider the rows of the table are numbered from $ 1 $ to $ n $ . Consider the columns of the table are numbered from $ 1 $ to $ n $ .

## 输出格式

In a single line print the expected time to paint the wall in minutes. Your answer will be considered correct if it has at most $ 10^{-4} $ absolute or relative error.

## 样例 #1

### 输入

```
5 2
2 3
4 1

```

### 输出

```
11.7669491886

```

## 样例 #2

### 输入

```
2 2
1 1
1 2

```

### 输出

```
2.0000000000

```

## 样例 #3

### 输入

```
1 1
1 1

```

### 输出

```
0.0000000000

```



---

---
title: "Different Subsets For All Tuples"
layout: "post"
diff: 省选/NOI-
pid: CF660E
tag: ['组合数学']
---

# Different Subsets For All Tuples

## 题目描述

For a sequence $ a $ of $ n $ integers between $ 1 $ and $ m $ , inclusive, denote $ f(a) $ as the number of distinct subsequences of $ a $ (including the empty subsequence).

You are given two positive integers $ n $ and $ m $ . Let $ S $ be the set of all sequences of length $ n $ consisting of numbers from $ 1 $ to $ m $ . Compute the sum $ f(a) $ over all $ a $ in $ S $ modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the number of elements in arrays and the upper bound for elements.

## 输出格式

Print the only integer $ c $ — the desired sum modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
14

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
174

```



---

---
title: "Anton and School - 2"
layout: "post"
diff: 省选/NOI-
pid: CF785D
tag: ['组合数学']
---

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 输入格式

The only line of the input contains a string $ s $ — the bracket sequence given in Anton's homework. The string consists only of characters "(" and ")" (without quotes). It's guaranteed that the string is not empty and its length doesn't exceed $ 200000 $ .

## 输出格式

Output one number — the answer for the task modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()

```

### 输出

```
6

```

## 样例 #2

### 输入

```
()()()

```

### 输出

```
7

```

## 样例 #3

### 输入

```
)))

```

### 输出

```
0

```



---

---
title: "Coprime Arrays"
layout: "post"
diff: 省选/NOI-
pid: CF915G
tag: ['数学', '前缀和', '差分']
---

# Coprime Arrays

## 题目描述

#### 题意：

我们称一个大小为 $n$ 的数组 $a$ 互质，当且仅当 $gcd(a_1,a_2,\cdots,a_n)=1$，$gcd$ 是最大公约数的意思。

给定 $n,k$，对于每个 $i$ $(1\le i\le k)$，你都需要确定这样的数组的个数——长度为 $n$ 的互质数组 $a$ ，满足对每个 $j$ $(1\le j\le n)$，都有 $1\le a_j\le i$。

答案可能非常大，请对 $10^9+7$ 取模。

## 输入格式

只有一行，两个数 $n,k$ $(1\le n,k\le 2\cdot10^6)$，分别表示数组的大小和数组元素大小的上限。

## 输出格式

为了降低输出的时间，你需要对输出进行如下处理：

把 $i$ 的答案（对 $10^9+7$ 取模后）记作 $b_i$。你需要输出 $\sum_{i=1}^{k} (b_i\oplus i)$，再对 $10^9+7$ 取模。

这里 $\oplus$ 表示按位异或，在 c++ 和 Java 中写作 ```^```，在 Pascal 中写作 ```xor```。

## 说明/提示

因为互质数组的数量比较多，我们只列出不互质的：

当 $i=1$ 时，唯一的数组就是互质的，$b_1=1$。

当 $i=2$ 时，数组 $[2,2,2]$ 不是互质的，$b_2=7$。

当 $i=3$ 时，数组 $[2,2,2],[3,3,3]$ 不是互质的，$b_3=25$。

当 $i=4$ 时，数组 $[2,2,2],[3,3,3],[2,2,4],[2,4,2],[2,4,4],[4,2,2],[4,2,4],[4,4,2],[4,4,4]$ 不是互质的，$b_4=55$。

Translated by 小粉兔

## 样例 #1

### 输入

```
3 4

```

### 输出

```
82

```

## 样例 #2

### 输入

```
2000000 8

```

### 输出

```
339310063

```



---

