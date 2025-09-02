---
title: "Weakened Common Divisor"
layout: "post"
diff: 普及/提高-
pid: CF1025B
tag: ['素数判断,质数,筛法']
---

# Weakened Common Divisor

## 题目描述

与  $GCD$  （最大公约数）类似，我们引进  $WCD$ （弱公约数）的概念， $ WCD$  的定义如下：

给出几对数 $\left( a_1,b_1 \right) ,\left( a_2,b_2 \right) ,\cdots ,\left( a_n,b_n \right)$ ，它们的  $WCD$  满足大于  $1 $ ，且能整除每个数对中至少一个数。  $WCD$  在一些情况下，可能不存在。

例如，给出这几对数 $\left[ \left( \text{12,}15 \right) ,\left( \text{25,}18 \right) ,\left( \text{10,}24 \right) \right]$  ，它们的   $WCD$  可以是 $ 2,3,5,6$  （这些数都满足严格大于  $1$  ，且能整除每个数对中至少一个数）

现在给你几对数，求他们的   $WCD$  。

## 输入格式

第一行一个整数 $ n$  ，  $1\leqslant n\leqslant \text{150\ 000}$  表示数对的组数。

接下来  $ n$  行，每行两个整数  $2\leqslant a_i,b_i\leqslant 2\cdot 10^9$

## 输出格式

一个整数，表示这些数对的  $WCD$  ，如果这些数对不存在   $WCD$  ，输出  $−1$ 。
### 样例解释

第一组样例中，  $6$  可以分别整除 $18,24,12$ ，当然输出其他可能的答案也行。

第二个样例，没有满足条件的  $WCD$  。

第三个样例，可以是  $5$  ，当然也可以是 $3,15$ 等。你没有必要输出最大或者最小的答案。

感谢@enor2017 提供的翻译

## 样例 #1

### 输入

```
3
17 18
15 24
12 15

```

### 输出

```
6
```

## 样例 #2

### 输入

```
2
10 16
7 17

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5
90 108
45 105
75 40
165 175
33 30

```

### 输出

```
5

```



---

---
title: "Prime Permutation"
layout: "post"
diff: 普及/提高-
pid: CF123A
tag: ['字符串', '素数判断,质数,筛法', '构造']
---

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 输入格式

The only line contains the initial string $ s $ , consisting of small Latin letters ( $ 1<=|s|<=1000 $ ).

## 输出格式

If it is possible to rearrange the characters in the string so that the above-mentioned conditions were fulfilled, then print in the first line "YES" (without the quotes) and print on the second line one of the possible resulting strings. If such permutation is impossible to perform, then print the single string "NO".

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc

```

### 输出

```
YES
abc

```

## 样例 #2

### 输入

```
abcd

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
xxxyxxx

```

### 输出

```
YES
xxxxxxy

```



---

---
title: "Interesting Ratio"
layout: "post"
diff: 普及/提高-
pid: CF2091E
tag: ['数论', '素数判断,质数,筛法']
---

# Interesting Ratio

## 题目描述

最近，Misha 在 IT Campus "NEIMARK" 的夏令营中学习了新课题 —— 欧几里得算法。

当发现 $a \cdot b = \text{lcm}(a, b) \cdot \text{gcd}(a, b)$ 时，他有些惊讶。其中 $\text{gcd}(a, b)$ 是 $a$ 和 $b$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $\text{lcm}(a, b)$ 是[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。Misha 想到既然 LCM 和 GCD 的乘积存在，或许它们的商也值得研究：$F(a, b) = \frac{\text{lcm}(a, b)}{\text{gcd}(a, b)}$。

例如，他取 $a = 2$ 和 $b = 4$，计算得到 $F(2, 4) = \frac{4}{2} = 2$，结果是一个质数（一个数如果恰好有两个因数则为质数）！现在他认为当 $a < b$ 且 $F(a, b)$ 是质数时，这个比值 $F(a, b)$ 是"有趣的比值"。

由于 Misha 刚接触数论，他需要你帮忙计算 —— 满足 $F(a, b)$ 是"有趣的比值"且 $1 \leq a < b \leq n$ 的不同数对 $(a, b)$ 有多少个？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^3$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含一个整数 $n$ ($2 \leq n \leq 10^7$)。

保证所有测试用例的 $n$ 之和不超过 $10^7$。


## 输出格式

对于每个测试用例，输出满足条件 $1 \leq a < b \leq n$ 的"有趣比值" $F(a, b)$ 的数量。


## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
10
34
10007
```

### 输出

```
4
11
49
24317
```



---

---
title: "Array and GCD"
layout: "post"
diff: 普及/提高-
pid: CF2104D
tag: ['贪心', '素数判断,质数,筛法', '前缀和']
---

# Array and GCD

## 题目描述

给定一个大小为 $n$ 的整数数组 $a$。

你可以执行以下操作任意次数（包括零次）：
- 支付 1 枚硬币并将数组中的任意一个元素增加 $1$（执行此操作时你至少需要有 1 枚硬币）；
- 获得 1 枚硬币并将数组中的任意一个元素减少 $1$。

我们称一个数组是理想的，当且仅当满足以下两个条件：
1. 数组中的每个元素都至少为 $2$；
2. 对于任意两个不同的下标 $i$ 和 $j$（$1 \le i, j \le n$；$i \ne j$），$a_i$ 和 $a_j$ 的最大公约数（GCD）等于 $1$。如果数组元素少于 2 个，则此条件自动满足。

我们称一个数组是美丽的，如果可以通过上述操作将其转换为理想数组，且初始时你没有硬币。如果数组已经是理想的，那么它也是美丽的。

给定的数组不一定是美丽或理想的。你可以从中删除任意数量的元素（包括删除整个数组或不删除任何元素）。你的任务是计算为了使数组变得美丽，最少需要删除多少个元素（可以是零个）。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 4 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$2 \le a_i \le 10^9$）。

输入数据的额外约束：所有测试用例的 $n$ 之和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了使数组变得美丽，最少需要删除的元素数量（可以是零个）。


## 说明/提示

在第一个样例中，你不需要删除任何元素，因为数组已经是美丽的。可以通过以下操作将其转换为理想数组：$[5, 5, 5] \rightarrow [4, 5, 5] \rightarrow [4, 4, 5] \rightarrow [4, 3, 5]$（最终你会拥有 3 枚硬币）。

在第二个样例中，你需要删除 2 个元素才能使数组变得美丽。如果保留元素 $[2, 3]$ 并删除其他元素，那么给定的数组已经是理想的（因此也是美丽的）。

在第三个样例中，你不需要删除任何元素，因为数组已经是理想的（因此也是美丽的）。

在第四个样例中，数组是美丽的。可以通过以下操作将其转换为理想数组：$[2, 100, 2] \rightarrow [2, 99, 2] \rightarrow [2, 99, 3] \rightarrow [2, 98, 3] \rightarrow [2, 97, 3]$（最终你会拥有 2 枚硬币）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
5 5 5
4
2 3 2 4
1
3
3
2 100 2
5
2 4 2 11 2
```

### 输出

```
0
2
0
0
1
```



---

---
title: "T-primes"
layout: "post"
diff: 普及/提高-
pid: CF230B
tag: ['数学', '枚举', '素数判断,质数,筛法']
---

# T-primes

## 题目描述

我们知道质数是只有两个不同的正数因数的正整数。相似的，我们把一个正整数 _t_ 叫做 T质数，如果 _t_ 恰好有三个不同的正整数因数。 

你被给了一个含有 _n_ 个正整数的数组。你要给其中所有的数判断它是否是 T质数。

## 输入格式

第一行只有一个正整数， _n_ （1<= _n_ <=10⁵）,代表数组里有几个数字。下一行包含了 _n_ 个被空格分开了的整数 _Xᵢ_ （1<=Xᵢ<=10¹²)。

请勿在C++中使用 %lld 用来读写64位整数。建议使用cin、cout流或 %I64d。

## 输出格式

输出 _n_ 行：如果第 _i_ 行的数 _Xᵢ_ 是T质数，则输出YES，否则输出NO。

## 说明/提示

给定样例有三个数。第一个数4恰好有三个因数--1、2和4，因此对这个数字输出YES。第二个数5有两个因数（1和5），第三个数6有四个因数（1、2、3和6），因此这两个数的答案是NO。

## 样例 #1

### 输入

```
3
4 5 6

```

### 输出

```
YES
NO
NO

```



---

---
title: "Taxes"
layout: "post"
diff: 普及/提高-
pid: CF735D
tag: ['数学', '素数判断,质数,筛法']
---

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=2·10^{9} $ ) — the total year income of mr. Funt.

## 输出格式

Print one integer — minimum possible number of burles that mr. Funt has to pay as a tax.

## 样例 #1

### 输入

```
4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
27

```

### 输出

```
3

```



---

---
title: "Bash's Big Day"
layout: "post"
diff: 普及/提高-
pid: CF757B
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Bash's Big Day

## 题目描述

Bash 已经踏上了成为最伟大的口袋妖怪大师的旅程。为了得到他的第一个口袋妖怪，他去了 Zulu 教授的实验室。由于 Bash 是 Zulu 教授最喜欢的学生，Zulu 允许他从实验室里取出任意数量的口袋妖怪。

但是 Zulu 警告他，每个小精灵都有一个力量值，例如 $k(k>1)$ 个小精灵在一起，它们的力量值为 $s_1,s_2,\dots,s_k$，如果 $\gcd(s_1,s_2,\dots s_k)=1$（见 $\gcd$ 的定义注释），它们之间就会互相打架。

Bash 作为一个聪明的人，不希望他的口袋妖怪互相斗争。然而，他也想最大化他从实验室里带走的神奇宝贝的数量。你能帮 Bash 找出他能带走的最大数量的口袋妖怪吗？

**注意：口袋妖怪不能与自己战斗。**

## 输入格式

输入包含两行。

第一行一个整数 $n(1\le n \le 10^5)$，表示实验室中的小精灵总数。

第二行 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 个小精灵的力量值 $s_i(1 \le s_i \le 10^5)$。

## 输出格式

一行包含一个整数，表示能拿走的小精灵数量最大值。

## 样例 #1

### 输入

```
3
2 3 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
2 3 4 6 7

```

### 输出

```
3

```



---

---
title: "Sherlock and his girlfriend"
layout: "post"
diff: 普及/提高-
pid: CF776B
tag: ['枚举', '素数判断,质数,筛法']
---

# Sherlock and his girlfriend

## 题目描述

Sherlock 有一个新女朋友。现在情人节就要到了，他想送给她一些珠宝。 

他买了几件首饰。第 $i$ 件的价格等于 $i+ 1$，也就是说，珠宝的价格分别为 $2,3,4,n + 1$ 。

现在需要给这些珠宝首饰上色。**当一件珠宝的价格是另一件珠宝的价格的素因子时，这两件的颜色就不允许相同。** 此外，要最少化使用的颜色数量。

## 输入格式

一行，包含单个整数 $n(1\le n\leq 100000)$ 指珠宝的数量。

## 输出格式

第一行的输出包含一个整数 $K$，指最少颜色的颜色种类数。

第二行由 $n$ 个整数（$1$ 到 $k$）组成，按价格从小到大来表示每件珠宝的颜色。

如果有多种方法，则可以输出它们中的任何一种。

## 说明/提示

在第一个样例中，第一、第二和第三件首饰的价格分别为 $2$、$3$、$4$,它们的颜色分别为 $1$ 、$1$ 和 $2$。

在这种情况下，由于 $2$ 是 $4$ 的因子，所以具有因数 $2$ 和 $4$ 的珠宝的颜色必须是不同的。

Translated by @皎月半洒花。

## 样例 #1

### 输入

```
3

```

### 输出

```
2
1 1 2 
```

## 样例 #2

### 输入

```
4

```

### 输出

```
2
2 1 1 2

```



---

---
title: "Jamie and Interesting Graph"
layout: "post"
diff: 普及/提高-
pid: CF916C
tag: ['最短路', '生成树', '素数判断,质数,筛法']
---

# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 输入格式

First line of input contains 2 integers $ n $ , $ m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/2d5925c368d31be87894bfaeb81a5671f57414c2.png) — the required number of vertices and edges.

## 输出格式

In the first line output 2 integers $ sp $ , $ mstw $ $ (1<=sp,mstw<=10^{14}) $ — the length of the shortest path and the sum of edges' weights in the minimum spanning tree.

In the next $ m $ lines output the edges of the graph. In each line output 3 integers $ u $ , $ v $ , $ w $ $ (1<=u,v<=n,1<=w<=10^{9}) $ describing the edge connecting $ u $ and $ v $ and having weight $ w $ .

## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4

```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4

```

## 样例 #2

### 输入

```
5 4

```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4

```



---

---
title: "Vile Grasshoppers"
layout: "post"
diff: 普及/提高-
pid: CF937B
tag: ['枚举', '素数判断,质数,筛法']
---

# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 输入格式

The only line contains two integers $ p $ and $ y $ $ (2<=p<=y<=10^{9}) $ .

## 输出格式

Output the number of the highest suitable branch. If there are none, print -1 instead.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
-1

```



---

