---
title: "COT - Count on a tree"
layout: "post"
diff: 省选/NOI-
pid: SP10628
tag: ['可持久化线段树']
---

# COT - Count on a tree

## 题目描述

# 本题必须使用 C++98 提交

给你一棵有n个结点的树，节点编号为1~n。

每个节点都有一个权值。              

要求执行以下操作：

U V K：求从节点u到节点v的第k小权值。

## 输入格式

第一行有两个整数n和m（n，m≤100000）
第二行有n个整数。
第i个整数表示第i个节点的权值。              

接下来的n-1行中，每行包含两个整数u v，表示u和v之间有一条边。              

接下来的m行，每行包含三个整数U V K，进行一次操作。

## 输出格式

对于每个操作，输出结果。

## 样例 #1

### 输入

```
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
2 5 2
2 5 3
2 5 4
7 8 2 
```

### 输出

```
2
8
9
105
7 
```



---

---
title: "TTM - To the moon"
layout: "post"
diff: 省选/NOI-
pid: SP11470
tag: ['线段树', '可持久化线段树', '可持久化']
---

# TTM - To the moon

## 题目描述

一个长度为 $N$ 的数组 $\{A\}$，$4$ 种操作 ：

- `C l r d`：区间 $[l,r]$ 中的数都加 $d$ ，同时当前的时间戳加 $1$。

- `Q l r`：查询当前时间戳区间 $[l,r]$ 中所有数的和 。

- `H l r t`：查询时间戳 $t$ 区间 $[l,r]$ 的和 。

- `B t`：将当前时间戳置为 $t$ 。

　　所有操作均合法 。

ps：刚开始时时间戳为 $0$

## 输出格式

数据保证：$1\le N,M\le 10^5$，$|A_i|\le 10^9$，$1\le l \le r \le N$，$|d|\le10^4$。在刚开始没有进行操作的情况下时间戳为 $0$，且保证 `B` 操作不会访问到未来的时间戳。

由 @bztMinamoto @yzy1 提供翻译

## 样例 #1

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
```

### 输出

```
4
55
9
15

```

## 样例 #2

### 输入

```
2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1
```

### 输出

```
0
1
```



---

---
title: "GOT - Gao on a tree"
layout: "post"
diff: 省选/NOI-
pid: SP11985
tag: ['线段树', '树链剖分']
---

# GOT - Gao on a tree

## 题目描述

 There's a tree, with each vertex assigned a number. For each query (a, b, c), you are asked whether there is a vertex on the path from a to b, which is assigned number c?

## 输入格式

There are multiple cases, end by EOF.

For each case, the first line contains n (n <= 100000) and m (m <= 200000), representing the number of vertexes (numbered from 1 to n) and the number of queries.

Then n integers follows, representing the number assigned to the i-th vertex.

Then n-1 lines, each of which contains a edge of the tree.

Then m lines, each of which contains three integers a, b and c (0 <= c <= n), representing a query.

## 输出格式

You should output "`Find`" or "`NotFind`" for every query on one line.

Output a blank line AFTER every case.

## 样例 #1

### 输入

```
5 5

1 2 3 4 5

1 2

1 3

3 4

3 5

2 3 4

2 4 3

2 4 5

4 5 1

4 5 3
```

### 输出

```
NotFind

Find

NotFind

NotFind

Find
```



---

---
title: "PT07J - Query on a tree III"
layout: "post"
diff: 省选/NOI-
pid: SP1487
tag: ['深度优先搜索 DFS', '可持久化线段树']
---

# PT07J - Query on a tree III

## 题目描述

你被给定一棵带点权的 $n$ 个点的有根树，点从 $1$ 到 $n$ 编号。

定义查询 $q(x,k)$：寻找以 $x$ 为根的子树中的第 $k$ 小点的编号（从小到大排序第 $k$ 个点）。

保证没有两个相同的点权。

## 样例 #1

### 输入

```
5
1 3 5 2 7
1 2
2 3
1 4
3 5
4
2 3
4 1
3 2
3 2
```

### 输出

```
5
4
5
5
```



---

---
title: "GSS2 - Can you answer these queries II"
layout: "post"
diff: 省选/NOI-
pid: SP1557
tag: ['线段树', '排序']
---

# GSS2 - Can you answer these queries II

## 题目描述

Being a completist and a simplist, kid Yang Zhe cannot solve but get Wrong Answer from most of the OI problems. And he refuse to write two program of same kind at all. So he always failes in contests.

When having a contest, Yang Zhe looks at the score of every problems first. For the problems of the same score, Yang Zhe will do only one of them. If he's lucky enough, he can get all the scores wanted.

Amber is going to hold a contest in SPOJ. She has made a list of _N_ candidate problems, which fit Yang Zhe very well. So Yang Zhe can solve any problem he want. Amber lined up the problems, began to select. She will select a subsequence of the list as the final problems. Being A girl of great compassion, she'd like to select such a subsequence (can be empty) that Yang Zhe will get the maximal score over all the possible subsequences.

Amber found the subsequence easily after a few minutes. To make things harder, Amber decided that, Yang Zhe can take this contest only if Yang Zhe can answer her _Q_ questions. The question is: if the final problems are limited to be a subsequence of _list_\[_X_.._Y_\] (1 <= _X_ <= _Y_ <= N), what's the maximal possible score Yang Zhe can get?

As we know, Yang Zhe is a bit idiot (so why did he solve the problem with a negative score?), he got Wrong Answer again... Tell him the correct answer!

## 输入格式

- Line 1: integer _N_ (1 <= _N_ <= 100000);
- Line 2: _N_ integers denoting the score of each problem, each of them is a integer in range \[-100000, 100000\];
- Line 3: integer _Q_ (1 <= _Q_ <= 100000);
- Line 3+_i_ (1 <= _i_ <= _Q_): two integers _X_ and _Y_ denoting the _i_th question.

## 输出格式

- Line _i_: a single integer, the answer to the _i_th question.

## 样例 #1

### 输入

```
9
4 -2 -2 3 -1 -4 2 2 -6
3
1 2
1 5
4 9
```

### 输出

```
4
5
3
```



---

---
title: "SEQPAR2 - Sequence Partitioning II"
layout: "post"
diff: 省选/NOI-
pid: SP1748
tag: ['动态规划 DP', '线段树']
---

# SEQPAR2 - Sequence Partitioning II

## 题目描述

Given a sequence of _N_ ordered pairs of positive integers (_A $ _{i} $_ , _B $ _{i} $_ ), you have to partition it into several contiguous parts. Let _p_ be the number of these parts, whose boundaries are (_l_ $ _{1} $ , _r_ $ _{1} $ ), (_l_ $ _{2} $ , _r_ $ _{2} $ ), ... ,(_l $ _{p} $_ , _r $ _{p} $_ ), which satisfy _l $ _{i} $_ = _r $ _{i-} $_  $ _{1} $ + 1, _l $ _{i} $_ <= _r $ _{i} $_ , _l_ $ _{1} $ = 1, _r $ _{p} $_ = _n_. The parts themselves also satisfy the following restrictions:

1. For any two pairs (_A $ _{p} $_ , _B $ _{p} $_ ), (_A $ _{q} $_ , _B $ _{q} $_ ), where (_A $ _{p} $_ , _B $ _{p} $_ ) is belongs to the _T $ _{p} $_ th part and (_A $ _{q} $_ , _B $ _{q} $_ ) the _T $ _{q} $_ th part. If _T $ _{p} $_ < _T $ _{q} $_ , then _B $ _{p} $_ > _A $ _{q} $_ .
2. Let _M $ _{i} $_  be the maximum _A_-component of elements in the _i_th part, say
  
  _M $ _{i} $_  = max {_A $ _{li} $_ , _A $ _{li+} $_  $ _{1} $ , ..., _A $ _{ri} $_ }, 1 <= _i_ <= _p_
  
  it is provided that
  
  ![](../../content/crazyb0y:SEQPAR2_1.bmp)  
   where Limit is a given integer.

Let _S $ _{i} $_  be the sum of _B_-components of elements in the _i_th part.

Now I want to minimize the value

max{_S $ _{i} $_ :1 <= _i_ <= p}

Could you tell me the minimum?

## 输入格式

The input contains exactly one test case. The first line of input contains two positive integers N (N <= 50000), Limit (Limit <= 2 $ ^{31} $ -1). Then follow N lines each contains a positive integers pair (_A_, _B_). It's always guaranteed that

 max{_A_ $ _{1} $ , _A_ $ _{2} $ , ..., _A $ _{n} $_ } <= Limit  
![](../../content/crazyb0y:SEQPAR2_2.bmp)

## 输出格式

Output the minimum target value.

## 样例 #1

### 输入

```
4 6
4 3
3 5
2 5
2 4
```

### 输出

```
9
```



---

---
title: "GSS5 - Can you answer these queries V"
layout: "post"
diff: 省选/NOI-
pid: SP2916
tag: ['线段树', '前缀和']
---

# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 输入格式

 The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.

## 输出格式

 Your program should output the results of the M queries for each test case, one query per line.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1
```

### 输出

```
2
3
1
```



---

---
title: "GSS7 - Can you answer these queries VII"
layout: "post"
diff: 省选/NOI-
pid: SP6779
tag: ['线段树', '树链剖分', '动态树 LCT']
---

# GSS7 - Can you answer these queries VII

## 题目描述

给定一棵树，有$N(N \le 100000)$个节点，每一个节点都有一个权值$x_i (|x_i| \le 10000)$

你需要执行$Q (Q \le 100000)$次操作：

1. `1 a b` 查询`(a,b)`这条链上的最大子段和，可以为空（即输出$0$）
2. `2 a b c` 将`(a,b)`这条链上的所有点权变为`c` $(|c| <= 10000)$

## 输入格式

第一行一个整数$N$

接下来一行有$N$个整数表示$x_i$

接下来$N-1$行，每行两个整数$u,v$表示$u$和$v$之间有一条边相连

接下来一行一个整数$Q$

之后有$Q$行，每行诸如`1 a b`或者`2 a b c`

## 输出格式

对于每一个询问，输出答案

# 输入样例

``` plain
5
-3 -2 1 2 3
1 2
2 3
1 4
4 5
3
1 2 5
2 3 4 2
1 2 5
```

# 输出样例

``` plain
5
9
```

## 样例 #1

### 输入

```
5
-3 -2 1 2 3
1 2
2 3
1 4
4 5
3
1 2 5
2 3 4 2
1 2 5
```

### 输出

```
5
9
```



---

---
title: "LPERMUT - Longest Permutation"
layout: "post"
diff: 省选/NOI-
pid: SP744
tag: ['莫队', '枚举', '可持久化线段树']
---

# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 输入格式

- Line 1: n (1<=n<=100000)
- Line 2: n numbers A $ _{1} $ , A $ _{2} $ , ... ,A $ _{n} $ (1<=A $ _{i} $ <=n)

## 输出格式

A single integer that is the length of the longest permutation

## 样例 #1

### 输入

```
5

4 1 3 1 2
```

### 输出

```
3
```



---

