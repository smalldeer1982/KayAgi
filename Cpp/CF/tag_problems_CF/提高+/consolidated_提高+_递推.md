---
title: "One-X"
layout: "post"
diff: 提高+/省选-
pid: CF1905E
tag: ['递推', '线段树']
---

# One-X

## 题目描述

In this sad world full of imperfections, ugly segment trees exist.

A segment tree is a tree where each node represents a segment and has its number. A segment tree for an array of $ n $ elements can be built in a recursive manner. Let's say function $ \operatorname{build}(v,l,r) $ builds the segment tree rooted in the node with number $ v $ and it corresponds to the segment $ [l,r] $ .

Now let's define $ \operatorname{build}(v,l,r) $ :

- If $ l=r $ , this node $ v $ is a leaf so we stop adding more edges
- Else, we add the edges $ (v, 2v) $ and $ (v, 2v+1) $ . Let $ m=\lfloor \frac{l+r}{2} \rfloor $ . Then we call $ \operatorname{build}(2v,l,m) $ and $ \operatorname{build}(2v+1,m+1,r) $ .

So, the whole tree is built by calling $ \operatorname{build}(1,1,n) $ .

Now Ibti will construct a segment tree for an array with $ n $ elements. He wants to find the sum of $ \operatorname{lca}^\dagger(S) $ , where $ S $ is a non-empty subset of leaves. Notice that there are exactly $ 2^n - 1 $ possible subsets. Since this sum can be very large, output it modulo $ 998\,244\,353 $ .

 $ ^\dagger\operatorname{lca}(S) $ is the number of the least common ancestor for the nodes that are in $ S $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^{18} $ ) — the length of the array for which the segment tree is built.

## 输出格式

For each test case, output a single integer — the required sum modulo $ 998\,244\,353 $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905E/fbb65ae036ad668eae2530f36a15f5bf19bb463d.png)In the first test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{2\})=2 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{2,3\})=1 $ .

Thus, the answer is $ 2+3+1=6 $ .

In the second test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{4\})=4 $ ;
- $ \operatorname{lca}(\{5\})=5 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{4,5\})=2 $ ;
- $ \operatorname{lca}(\{4,3\})=1 $ ;
- $ \operatorname{lca}(\{5,3\})=1 $ ;
- $ \operatorname{lca}(\{4,5,3\})=1 $ ;

Thus, the answer is $ 4+5+3+2+1+1+1=17 $ .

## 样例 #1

### 输入

```
5
2
3
4
5
53278
```

### 输出

```
6
17
36
69
593324855
```



---

---
title: "Small Permutation Problem (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1909F1
tag: ['递推']
---

# Small Permutation Problem (Easy Version)

## 题目描述

[Andy Tunstall - MiniBoss](https://soundcloud.com/tunners/miniboss)

⠀



In the easy version, the $ a_i $ are in the range $ [0, n] $ ; in the hard version, the $ a_i $ are in the range $ [-1, n] $ and the definition of good permutation is slightly different. You can make hacks only if all versions of the problem are solved.

You are given an integer $ n $ and an array $ a_1, a_2 \dots, a_n $ of integers in the range $ [0, n] $ .

A permutation $ p_1, p_2, \dots, p_n $ of $ [1, 2, \dots, n] $ is good if, for each $ i $ , the following condition is true:

- the number of values $ \leq i $ in $ [p_1, p_2, \dots, p_i] $ is exactly $ a_i $ .

Count the good permutations of $ [1, 2, \dots, n] $ , modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le n $ ), which describe the conditions for a good permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing the number of good permutations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only good permutation is $ [1, 2, 3, 4, 5] $ .

In the second test case, there are $ 4 $ good permutations: $ [2, 1, 5, 6, 3, 4] $ , $ [2, 1, 5, 6, 4, 3] $ , $ [2, 1, 6, 5, 3, 4] $ , $ [2, 1, 6, 5, 4, 3] $ . For example, $ [2, 1, 5, 6, 3, 4] $ is good because:

- $ a_1 = 0 $ , and there are $ 0 $ values $ \leq 1 $ in $ [p_1] = [2] $ ;
- $ a_2 = 2 $ , and there are $ 2 $ values $ \leq 2 $ in $ [p_1, p_2] = [2, 1] $ ;
- $ a_3 = 2 $ , and there are $ 2 $ values $ \leq 3 $ in $ [p_1, p_2, p_3] = [2, 1, 5] $ ;
- $ a_4 = 2 $ , and there are $ 2 $ values $ \leq 4 $ in $ [p_1, p_2, p_3, p_4] = [2, 1, 5, 6] $ ;
- $ a_5 = 4 $ , and there are $ 4 $ values $ \leq 5 $ in $ [p_1, p_2, p_3, p_4, p_5] = [2, 1, 5, 6, 3] $ ;
- $ a_6 = 6 $ , and there are $ 6 $ values $ \leq 6 $ in $ [p_1, p_2, p_3, p_4, p_5, p_6] = [2, 1, 5, 6, 3, 4] $ .

In the third test case, there are no good permutations, because there are no permutations with $ a_6 = 5 $ values $ \leq 6 $ in $ [p_1, p_2, p_3, p_4, p_5, p_6] $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
6
0 2 2 2 4 6
6
0 1 3 4 5 5
6
1 2 3 2 4 6
15
0 0 1 1 1 2 3 4 5 6 7 9 11 13 15
```

### 输出

```
1
4
0
0
532305727
```



---

---
title: "CGCDSSQ"
layout: "post"
diff: 提高+/省选-
pid: CF475D
tag: ['枚举', '最大公约数 gcd', '线性递推']
---

# CGCDSSQ

## 题目描述

Given a sequence of integers $ a_{1},...,a_{n} $ and $ q $ queries $ x_{1},...,x_{q} $ on it. For each query $ x_{i} $ you have to count the number of pairs $ (l,r) $ such that $ 1<=l<=r<=n $ and $ gcd(a_{l},a_{l+1},...,a_{r})=x_{i} $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475D/57fa10a542946ca7729b1feeb84648963b002c6d.png) is a greatest common divisor of $ v_{1},v_{2},...,v_{n} $ , that is equal to a largest positive integer that divides all $ v_{i} $ .

## 输入格式

Given a sequence of integers $ a_{1},...,a_{n} $ and $ q $ queries $ x_{1},...,x_{q} $ on it. For each query $ x_{i} $ you have to count the number of pairs $ (l,r) $ such that $ 1<=l<=r<=n $ and $ gcd(a_{l},a_{l+1},...,a_{r})=x_{i} $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475D/57fa10a542946ca7729b1feeb84648963b002c6d.png) is a greatest common divisor of $ v_{1},v_{2},...,v_{n} $ , that is equal to a largest positive integer that divides all $ v_{i} $ .

## 输出格式

For each query print the result in a separate line.

## 样例 #1

### 输入

```
3
2 6 3
5
1
2
3
4
6

```

### 输出

```
1
2
2
0
1

```

## 样例 #2

### 输入

```
7
10 20 3 15 1000 60 16
10
1
2
3
4
5
6
10
20
60
1000

```

### 输出

```
14
0
2
2
2
0
2
2
1
1

```



---

---
title: "Obsessive String"
layout: "post"
diff: 提高+/省选-
pid: CF494B
tag: ['字符串', '递推', '前缀和']
---

# Obsessive String

## 题目描述

给定两个字符串 $s$ 和 $t$。定义一种合法的截取方案为，在字符串 $s$ 中截取若干（大于 $0$）个互不相交的子串，满足 $t$ 是每个这些子串的子串。

请你输出总方案数模 $10^9 + 7$ 的值。

## 输入格式

输入共两行。第一行一个字符串 $s$，第二行一个字符串 $t$。

## 输出格式

输出共一行，一个非负整数表示答案。

## 说明/提示

保证 $1 \leq |s|, |t| \leq 10^5$，字符串中只包含小写拉丁字母。

## 样例 #1

### 输入

```
ababa
aba

```

### 输出

```
5

```

## 样例 #2

### 输入

```
welcometoroundtwohundredandeightytwo
d

```

### 输出

```
274201

```

## 样例 #3

### 输入

```
ddd
d

```

### 输出

```
12

```



---

---
title: "Bindian Signalizing"
layout: "post"
diff: 提高+/省选-
pid: CF5E
tag: ['动态规划 DP', '递推', '栈']
---

# Bindian Signalizing

## 题目描述

**题面大意**

给定一个圆和圆弧上的 $n$ 座山，每座山上有一名看守员，若连接两名看守员的圆弧（注：圆弧有左右两条，任意一条满足即可）两条中没有比（这两个看守员所在的）两座山中任何一座更高的山，则这两名看守人彼此能看到各自的信号。现在给定 $n$ 座山的高度，求能够看到彼此信号的成对看守人的数量

## 输入格式

输入数据的第一行包含一个整数 $n$（$3\le n\le10^6$），表示该圆圈上的山丘数量。

第二行包含 $n$ 个数字整数表示山的高度（按顺时针顺序排列）。所有的高度介于 $1$ 和 $10^9$ 之间

## 输出格式

一个整数，表示答案

## 样例 #1

### 输入

```
5
1 2 4 5 3

```

### 输出

```
7

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

---
title: "XOR-pyramid"
layout: "post"
diff: 提高+/省选-
pid: CF983B
tag: ['动态规划 DP', '递推', '递归']
---

# XOR-pyramid

## 题目描述

For an array $ b $ of length $ m $ we define the function $ f $ as

 $  f(b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f(b[1] \oplus b[2],b[2] \oplus b[3],\dots,b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}  $ where $ \oplus $ is [bitwise exclusive OR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, $ f(1,2,4,8)=f(1\oplus2,2\oplus4,4\oplus8)=f(3,6,12)=f(3\oplus6,6\oplus12)=f(5,10)=f(5\oplus10)=f(15)=15 $

You are given an array $ a $ and a few queries. Each query is represented as two integers $ l $ and $ r $ . The answer is the maximum value of $ f $ on all continuous subsegments of the array $ a_l, a_{l+1}, \ldots, a_r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ) — the elements of the array.

The third line contains a single integer $ q $ ( $ 1 \le q \le 100\,000 $ ) — the number of queries.

Each of the next $ q $ lines contains a query represented as two integers $ l $ , $ r $ ( $ 1 \le l \le r \le n $ ).

## 输出格式

Print $ q $ lines — the answers for the queries.

## 说明/提示

In first sample in both queries the maximum value of the function is reached on the subsegment that is equal to the whole segment.

In second sample, optimal segment for first query are $ [3,6] $ , for second query — $ [2,5] $ , for third — $ [3,4] $ , for fourth — $ [1,2] $ .

## 样例 #1

### 输入

```
3
8 4 1
2
2 3
1 2

```

### 输出

```
5
12

```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2

```

### 输出

```
60
30
12
3

```



---

