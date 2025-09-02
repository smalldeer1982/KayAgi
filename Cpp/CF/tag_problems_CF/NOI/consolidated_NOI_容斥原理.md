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
title: "Doping"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1750G
tag: ['组合数学', '容斥原理']
---

# Doping

## 题目描述

We call an array $ a $ of length $ n $ fancy if for each $ 1 < i \le n $ it holds that $ a_i = a_{i-1} + 1 $ .

Let's call $ f(p) $ applied to a permutation $ ^\dagger $ of length $ n $ as the minimum number of subarrays it can be partitioned such that each one of them is fancy. For example $ f([1,2,3]) = 1 $ , while $ f([3,1,2]) = 2 $ and $ f([3,2,1]) = 3 $ .

Given $ n $ and a permutation $ p $ of length $ n $ , we define a permutation $ p' $ of length $ n $ to be $ k $ -special if and only if:

- $ p' $ is lexicographically smaller $ ^\ddagger $ than $ p $ , and
- $ f(p') = k $ .

Your task is to count for each $ 1 \le k \le n $ the number of $ k $ -special permutations modulo $ m $ .

 $ ^\dagger $ A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ A permutation $ a $ of length $ n $ is lexicographically smaller than a permutation $ b $ of length $ n $ if and only if the following holds: in the first position where $ a $ and $ b $ differ, the permutation $ a $ has a smaller element than the corresponding element in $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2000 $ , $ 10 \le m \le 10^9 $ ) — the length of the permutation and the required modulo.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the permutation $ p $ .

## 输出格式

Print $ n $ integers, where the $ k $ -th integer is the number of $ k $ -special permutations modulo $ m $ .

## 说明/提示

In the first example, the permutations that are lexicographically smaller than $ [1,3,4,2] $ are:

- $ [1,2,3,4] $ , $ f([1,2,3,4])=1 $ ;
- $ [1,2,4,3] $ , $ f([1,2,4,3])=3 $ ;
- $ [1,3,2,4] $ , $ f([1,3,2,4])=4 $ .

Thus our answer is $ [1,0,1,1] $ .

In the second example, the permutations that are lexicographically smaller than $ [3,2,1] $ are:

- $ [1,2,3] $ , $ f([1,2,3])=1 $ ;
- $ [1,3,2] $ , $ f([1,3,2])=3 $ ;
- $ [2,1,3] $ , $ f([2,1,3])=3 $ ;
- $ [2,3,1] $ , $ f([2,3,1])=2 $ ;
- $ [3,1,2] $ , $ f([3,1,2])=2 $ .

Thus our answer is $ [1,2,2] $ .

## 样例 #1

### 输入

```
4 666012
1 3 4 2
```

### 输出

```
1 0 1 1
```

## 样例 #2

### 输入

```
3 10
3 2 1
```

### 输出

```
1 2 2
```

## 样例 #3

### 输入

```
7 1000000000
7 2 1 3 5 4 6
```

### 输出

```
1 6 40 201 705 1635 1854
```

## 样例 #4

### 输入

```
10 11
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
1 9 9 0 1 5 5 0 1 0
```



---

---
title: "Segment Covering"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1774G
tag: ['倍增', '最近公共祖先 LCA', '组合数学', '容斥原理']
---

# Segment Covering

## 题目描述

ChthollyNotaSeniorious gives DataStructures a number axis with $ m $ distinct segments on it. Let $ f(l,r) $ be the number of ways to choose an even number of segments such that the union of them is exactly $ [l,r] $ , and $ g(l,r) $ be the number of ways to choose an odd number of segments such that the union of them is exactly $ [l,r] $ .

ChthollyNotaSeniorious asked DataStructures $ q $ questions. In each query, ChthollyNotaSeniorious will give DataStructures two numbers $ l, r $ , and now he wishes that you can help him find the value $ f(l,r)-g(l,r) $ modulo $ 998\,244\,353 $ so that he wouldn't let her down.

## 输入格式

The first line of input contains two integers $ m $ ( $ 1 \leq m \leq 2 \cdot 10^5 $ ) and $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of segments and queries, correspondingly.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \leq x_i < y_i \leq 10^9 $ ), denoting a segment $ [x_i, y_i] $ .

It is guaranteed that all segments are distinct. More formally, there do not exist two numbers $ i, j $ with $ 1 \le i < j \le m $ such that $ x_i = x_j $ and $ y_i = y_j $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq 10^9 $ ), describing a query.

## 输出格式

For each query, output a single integer — $ f(l_i,r_i)-g(l_i,r_i) $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first query, we have to find $ f(1, 4) - g(1, 4) $ . The only subset of segments with union $ [1, 4] $ is $ \{[1, 3], [2, 4]\} $ , so $ f(1, 4) = 1, g(1, 4) = 0 $ .

In the second query, we have to find $ f(1, 5) - g(1, 5) $ . The only subsets of segments with union $ [1, 5] $ are $ \{[1, 3], [2, 4], [3, 5]\} $ and $ \{[1, 3], [3, 5]\} $ , so $ f(1, 5) = 1, g(1, 5) = 1 $ .

## 样例 #1

### 输入

```
4 2
1 3
4 6
2 4
3 5
1 4
1 5
```

### 输出

```
1
0
```



---

---
title: "Unique Strings"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1954F
tag: ['群论', '容斥原理']
---

# Unique Strings

## 题目描述

Let's say that two strings $ a $ and $ b $ are equal if you can get the string $ b $ by cyclically shifting string $ a $ . For example, the strings 0100110 and 1100100 are equal, while 1010 and 1100 are not.

You are given a binary string $ s $ of length $ n $ . Its first $ c $ characters are 1-s, and its last $ n - c $ characters are 0-s.

In one operation, you can replace one 0 with 1.

Calculate the number of unique strings you can get using no more than $ k $ operations. Since the answer may be too large, print it modulo $ 10^9 + 7 $ .

## 输入格式

The first and only line contains three integers $ n $ , $ c $ and $ k $ ( $ 1 \le n \le 3000 $ ; $ 1 \le c \le n $ ; $ 0 \le k \le n - c $ ) — the length of string $ s $ , the length of prefix of 1-s and the maximum number of operations.

## 输出格式

Print the single integer — the number of unique strings you can achieve performing no more than $ k $ operations, modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, the only possible string is 1.

In the second test case, the possible strings are: 100, 110, and 111. String 101 is equal to 110, so we don't count it.

In the third test case, the possible strings are: 10000, 11000, 10100. String 10010 is equal to 10100, and 10001 is equal to 11000.

## 样例 #1

### 输入

```
1 1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5 1 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
6 2 2
```

### 输出

```
7
```

## 样例 #5

### 输入

```
24 3 11
```

### 输出

```
498062
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

