---
title: "LuoTianyi and the Floating Islands (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1824B2
tag: ['树论', '排列组合']
---

# LuoTianyi and the Floating Islands (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ k\le n $ . You can make hacks only if both versions of the problem are solved.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/12896184a3f823fcd8518f46dc5b68823c932f0f.png) Chtholly and the floating islands.LuoTianyi now lives in a world with $ n $ floating islands. The floating islands are connected by $ n-1 $ undirected air routes, and any two of them can reach each other by passing the routes. That means, the $ n $ floating islands form a tree.

One day, LuoTianyi wants to meet her friends: Chtholly, Nephren, William, .... Totally, she wants to meet $ k $ people. She doesn't know the exact positions of them, but she knows that they are in pairwise distinct islands. She define an island is good if and only if the sum of the distances $ ^{\dagger} $ from it to the islands with $ k $ people is the minimal among all the $ n $ islands.

Now, LuoTianyi wants to know that, if the $ k $ people are randomly set in $ k $ distinct of the $ n $ islands, then what is the expect number of the good islands? You just need to tell her the expect number modulo $ 10^9+7 $ .

 $ ^{\dagger} $ The distance between two islands is the minimum number of air routes you need to take to get from one island to the other.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1\le k \le n \le 2\cdot 10^5 $ ) — the number of the islands and people respectively.

Next $ n−1 $ lines describe the air routes. The $ i $ -th of them contains two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i,v_i \le n, u_i \neq v_i $ ) — the islands connected by the $ i $ -th air route.

## 输出格式

Print a single integer — the expect number of the good islands modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 $ ( $ \operatorname{mod} M $ ). Output the integer equal to $ p \cdot q^{-1} $ $ \operatorname{mod} M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p $ ( $ \operatorname{mod} M $ ).

## 说明/提示

In the first example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/f98245759af7851bb13c350e387c9b296063f10a.png) If the people are in the islands $ 1 $ and $ 2 $ , then islands $ 1 $ and $ 2 $ will be good.

The sum of the distances from island $ 1 $ or $ 2 $ to all the people is $ 1+0=1 $ , which is the minimal. While the sum of the distances from island $ 3 $ to all the people is $ 2+1=3 $ , which is greater than $ 1 $ .

Like this, when the people are in island $ 1 $ and $ 3 $ , then islands $ 1,2 $ and $ 3 $ will be good.

When the people are in islands $ 1 $ and $ 4 $ , then islands $ 1,2,3 $ and $ 4 $ will be good.

When the people are in islands $ 2 $ and $ 3 $ , then islands $ 2 $ and $ 3 $ will be good.

When the people are in islands $ 2 $ and $ 4 $ , then islands $ 2,3 $ and $ 4 $ will be good.

When the people are in islands $ 3 $ and $ 4 $ , then islands $ 3 $ and $ 4 $ will be good.

So the expect of the number of the good islands is $ \frac{16}{6} $ , which equals to $ 666666674 $ modulo $ 10^9+7 $ .

In the second example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/2f411e079090512cd14c27f9186226921a07c282.png)We can see that there is one person in each island, and only the island $ 3 $ is good. So the expect number is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4
```

### 输出

```
666666674
```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
3 5
```

### 输出

```
1
```



---

---
title: "Girl Permutation"
layout: "post"
diff: 提高+/省选-
pid: CF1946E
tag: ['组合数学', '排列组合']
---

# Girl Permutation

## 题目描述

Some permutation of length $ n $ is guessed.

You are given the indices of its prefix maximums and suffix maximums.

Recall that a permutation of length $ k $ is an array of size $ k $ such that each integer from $ 1 $ to $ k $ occurs exactly once.

Prefix maximums are the elements that are the maximum on the prefix ending at that element. More formally, the element $ a_i $ is a prefix maximum if $ a_i > a_j $ for every $ j < i $ .

Similarly, suffix maximums are defined, the element $ a_i $ is a suffix maximum if $ a_i > a_j $ for every $ j > i $ .

You need to output the number of different permutations that could have been guessed.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains three integers $ n, m_1 $ and $ m_2 $ ( $ 1 \le m_1, m_2 \le n \le 2 \cdot 10^5 $ ) — the length of the permutation, the number of prefix maximums, and the number of suffix maximums, respectively.

The second line of each test case contains $ m_1 $ integers $ p_1 < p_2 < \ldots < p_{m_1} $ ( $ 1 \le p_i \le n $ ) — the indices of the prefix maximums in increasing order.

The third line of each test case contains $ m_2 $ integers $ s_1 < s_2 < \ldots < s_{m_2} $ ( $ 1 \le s_i \le n $ ) — the indices of the suffix maximums in increasing order.

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer on a separate line — the number of suitable permutations modulo $ 10^9 + 7 $ .

## 说明/提示

The following permutations are suitable for the second set of input data:

- $ [1, 4, 3, 2] $
- $ [2, 4, 3, 1] $
- $ [3, 4, 2, 1] $

The following permutations are suitable for the sixth set of input data:

- $ [2, 1, 6, 5, 3, 4] $
- $ [3, 1, 6, 5, 2, 4] $
- $ [3, 2, 6, 5, 1, 4] $
- $ [4, 1, 6, 5, 2, 3] $
- $ [4, 2, 6, 5, 1, 3] $
- $ [4, 3, 6, 5, 1, 2] $
- $ [5, 1, 6, 4, 2, 3] $
- $ [5, 2, 6, 4, 1, 3] $
- $ [5, 3, 6, 4, 1, 2] $
- $ [5, 4, 6, 3, 1, 2] $

## 样例 #1

### 输入

```
6
1 1 1
1
1
4 2 3
1 2
2 3 4
3 3 1
1 2 3
3
5 3 4
1 2 3
2 3 4 5
20 5 4
1 2 3 4 12
12 13 18 20
6 2 3
1 3
3 4 6
```

### 输出

```
1
3
1
0
317580808
10
```



---

---
title: "Rare Coins"
layout: "post"
diff: 提高+/省选-
pid: CF1948F
tag: ['排列组合']
---

# Rare Coins

## 题目描述

There are $ n $ bags numbered from $ 1 $ to $ n $ , the $ i $ -th bag contains $ a_i $ golden coins and $ b_i $ silver coins.

The value of a gold coin is $ 1 $ . The value of a silver coin is either $ 0 $ or $ 1 $ , determined for each silver coin independently ( $ 0 $ with probability $ \frac{1}{2} $ , $ 1 $ with probability $ \frac{1}{2} $ ).

You have to answer $ q $ independent queries. Each query is the following:

- $ l $ $ r $ — calculate the probability that the total value of coins in bags from $ l $ to $ r $ is strictly greater than the total value in all other bags.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 3 \cdot 10^5 $ ) — the number of bags and the number of queries, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^6 $ ) — the number of gold coins in the $ i $ -th bag.

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 0 \le b_i \le 10^6 $ ) — the number of silver coins in the $ i $ -th bag.

Next $ q $ lines contain queries. The $ j $ -th of the next $ q $ lines contains two integers $ l_j $ and $ r_j $ ( $ 1 \le l_j \le r_j \le n $ ) — the description of the $ j $ -th query.

Additional constraints on the input:

- the sum of the array $ a $ doesn't exceed $ 10^6 $ ;
- the sum of the array $ b $ doesn't exceed $ 10^6 $ .

## 输出格式

For each query, print one integer — the probability that the total value of coins in bags from $ l $ to $ r $ is strictly greater than the total value in all other bags, taken modulo $ 998244353 $ .

Formally, the probability can be expressed as an irreducible fraction $ \frac{x}{y} $ . You have to print the value of $ x \cdot y^{-1} \bmod 998244353 $ , where $ y^{-1} $ is an integer such that $ y \cdot y^{-1} \bmod 998244353 = 1 $ .

## 说明/提示

In both queries from the first example, the answer is $ \frac{1}{4} $ .

## 样例 #1

### 输入

```
2 2
1 0
0 2
2 2
1 1
```

### 输出

```
748683265 748683265
```

## 样例 #2

### 输入

```
4 3
2 3 4 5
1 0 7 3
3 3
2 3
1 4
```

### 输出

```
997756929 273932289 1
```



---

---
title: "MEXimize the Score"
layout: "post"
diff: 提高+/省选-
pid: CF2030E
tag: ['动态规划 DP', '组合数学', '排列组合']
---

# MEXimize the Score

## 题目描述

Suppose we partition the elements of an array $ b $ into any number $ k $ of non-empty multisets $ S_1, S_2, \ldots, S_k $ , where $ k $ is an arbitrary positive integer. Define the score of $ b $ as the maximum value of $ \operatorname{MEX}(S_1) $ $ ^{\text{∗}} $ $  + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k) $ over all possible partitions of $ b $ for any integer $ k $ .

Envy is given an array $ a $ of size $ n $ . Since he knows that calculating the score of $ a $ is too easy for you, he instead asks you to calculate the sum of scores of all $ 2^n - 1 $ non-empty subsequences of $ a $ . $ ^{\text{†}} $ Since this answer may be large, please output it modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ that does not occur in the collection $ c $ . For example, $ \operatorname{MEX}([0,1,2,2]) = 3 $ and $ \operatorname{MEX}([1,2,2]) = 0 $

 $ ^{\text{†}} $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the answer, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, we must consider seven subsequences:

- $ [0] $ : The score is $ 1 $ .
- $ [0] $ : The score is $ 1 $ .
- $ [1] $ : The score is $ 0 $ .
- $ [0,0] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,0,1] $ : The score is $ 3 $ .

 The answer for the first testcase is $ 1+1+2+2+2+3=11 $ .In the last testcase, all subsequences have a score of $ 0 $ .

## 样例 #1

### 输入

```
4
3
0 0 1
4
0 0 1 1
5
0 0 1 2 2
4
1 1 1 1
```

### 输出

```
11
26
53
0
```



---

---
title: "Kuro and Topological Parity"
layout: "post"
diff: 提高+/省选-
pid: CF979E
tag: ['递推', '排列组合']
---

# Kuro and Topological Parity

## 题目描述

给定 $n$ 个点，每个点有黑白两种颜色（如果没有颜色，那么你可以把它任意涂成黑色或白色），同时你可以在这个图上任意加入一些边（当然不能加入重边或自环），要求：加入的边必须从编号小的点指向编号大的点

我们称一条好的路径为经过的点为黑白相间的路径，如果一个图好的路径的总数 $\bmod 2=p$，那么我们称这个图为好的图，现在给定你 $n$ 个点的情况，求这 $n$ 个点能组成的好的图的个数，答案对 $10^9+7$ 取模。

## 输入格式

第一行两个整数 $n,p$，分别表示点的个数和 $p$。其中 $n\leq 50$，$p \in \{0,1\}$。

第二行 $n$ 个整数，每个整数只有三种取值：$-1,0,1$。其中，$-1$ 表示这个点未被涂色，你可以随意为他选择一种颜色，$0$ 表示这个点为黑色，$1$ 表示这个点为白色。

## 输出格式

一行一个整数，表示答案对 $10^9+7$ 取模的结果

## 样例 #1

### 输入

```
3 1
-1 0 1

```

### 输出

```
6
```

## 样例 #2

### 输入

```
2 1
1 0

```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1
-1

```

### 输出

```
2
```



---

