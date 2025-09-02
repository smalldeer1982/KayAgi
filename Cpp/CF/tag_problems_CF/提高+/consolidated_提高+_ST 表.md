---
title: "Qpwoeirut and Vertices"
layout: "post"
diff: 提高+/省选-
pid: CF1706E
tag: ['线段树', 'Kruskal 重构树', 'ST 表', '整体二分']
---

# Qpwoeirut and Vertices

## 题目描述

You are given a connected undirected graph with $ n $ vertices and $ m $ edges. Vertices of the graph are numbered by integers from $ 1 $ to $ n $ and edges of the graph are numbered by integers from $ 1 $ to $ m $ .

Your task is to answer $ q $ queries, each consisting of two integers $ l $ and $ r $ . The answer to each query is the smallest non-negative integer $ k $ such that the following condition holds:

- For all pairs of integers $ (a, b) $ such that $ l\le a\le b\le r $ , vertices $ a $ and $ b $ are reachable from one another using only the first $ k $ edges (that is, edges $ 1, 2, \ldots, k $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ q $ ( $ 2\le n\le 10^5 $ , $ 1\le m, q\le 2\cdot 10^5 $ ) — the number of vertices, edges, and queries respectively.

Each of the next $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ ) — ends of the $ i $ -th edge.

It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1\le l\le r\le n $ ) — descriptions of the queries.

It is guaranteed that that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print $ q $ integers — the answers to the queries.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/8251767c792df96adbc7d8ce1ae896aca10bb309.png)Graph from the first test case. The integer near the edge is its number.In the first test case, the graph contains $ 2 $ vertices and a single edge connecting vertices $ 1 $ and $ 2 $ .

In the first query, $ l=1 $ and $ r=1 $ . It is possible to reach any vertex from itself, so the answer to this query is $ 0 $ .

In the second query, $ l=1 $ and $ r=2 $ . Vertices $ 1 $ and $ 2 $ are reachable from one another using only the first edge, through the path $ 1 \longleftrightarrow 2 $ . It is impossible to reach vertex $ 2 $ from vertex $ 1 $ using only the first $ 0 $ edges. So, the answer to this query is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/af65cd675bd4523d08062174925e59fd8900ee43.png)Graph from the second test case. The integer near the edge is its number.In the second test case, the graph contains $ 5 $ vertices and $ 5 $ edges.

In the first query, $ l=1 $ and $ r=4 $ . It is enough to use the first $ 3 $ edges to satisfy the condition from the statement:

- Vertices $ 1 $ and $ 2 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 $ (edge $ 1 $ ).
- Vertices $ 1 $ and $ 3 $ are reachable from one another through the path $ 1 \longleftrightarrow 3 $ (edge $ 2 $ ).
- Vertices $ 1 $ and $ 4 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 1 $ and $ 3 $ ).
- Vertices $ 2 $ and $ 3 $ are reachable from one another through the path $ 2 \longleftrightarrow 1 \longleftrightarrow 3 $ (edges $ 1 $ and $ 2 $ ).
- Vertices $ 2 $ and $ 4 $ are reachable from one another through the path $ 2 \longleftrightarrow 4 $ (edge $ 3 $ ).
- Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ).

If we use less than $ 3 $ of the first edges, then the condition won't be satisfied. For example, it is impossible to reach vertex $ 4 $ from vertex $ 1 $ using only the first $ 2 $ edges. So, the answer to this query is $ 3 $ .

In the second query, $ l=3 $ and $ r=4 $ . Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ). If we use any fewer of the first edges, nodes $ 3 $ and $ 4 $ will not be reachable from one another.

## 样例 #1

### 输入

```
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3
```

### 输出

```
0 1 
3 3 0 5 5 
2
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
title: "Invertible Bracket Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF1976D
tag: ['线段树', 'ST 表']
---

# Invertible Bracket Sequences

## 题目描述

### 题意翻译
### 题面描述
我们定义一个合法的括号序列，是仅由 `(` 和 `)` 构成的字符串且：
1. 空串 $\epsilon$ 是合法的括号序列。
2. 若 $s$ 为合法的括号序列，则 $(s)$ 也为合法的括号序列。
3. 若 $s,t$ 均为合法的括号序列，则 $st$ 也为合法的括号序列。（其中 $st$ 表示将字符串 $s$ 和 $t$ 拼接。）

定义对一个括号序列的**翻转**操作为：将这个括号序列的所有 `(` 变为 `)`，所有 `)` 变为 `(`。

如 `()(((` 翻转后成为 `)()))`。

给定一个**保证合法**的字符串 $s$。

你可以选择字符串 $s$ 的一个**子串**进行翻转操作。（注意是**子串**，与**子序列区分**，子串要求**连续**。）

问**翻转**了一个**子串**后得到的字符串 $s'$ 仍然是**合法括号序列**的方案数。

## 输入格式

先是一个数字 $t$ 表示数据组数。

接下来 $t$ 行，每行一个合法括号序列 $s$。

## 输出格式

对于每组数据，输出一个数字 $x$，表示翻转 $s$ 的一个子串后仍然是合法括号序列的方案数。

## 说明/提示

在本题中，不可以翻转长度为 $0$ 的子串。

translate by Hoks。

## 样例 #1

### 输入

```
4
(())
()
()()()
(()())(())
```

### 输出

```
1
0
3
13
```



---

---
title: "Eliminating Balls With Merging (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1998E1
tag: ['线段树', '分治', 'ST 表', '单调栈']
---

# Eliminating Balls With Merging (Easy Version)

## 题目描述

_喝水_ 

—— 孙武，程序员健康指南

**这是问题的简单版本。本题中 $x=n$ 。你必须同时解决这两个版本的问题，才能  hack**。

给你两个整数 $n$ 和 $x$ ( $x=n$ )。有 $n$ 个球排成一排，从左到右编号为 $1$ 到 $n$ 。最初，在第 $i$ 个球上写着一个值 $a_i$。

对于从 $1$ 到 $n$ 的每个整数 $i$ ，我们定义一个函数 $f(i)$ 如下：

- 假设有一个集合 $S = \{1, 2, \ldots, i\}$ 。
    
- 在每次运算中，必须从 $S$ 中选择一个整数 $l$ ( $1 \leq l < i$ )，使得 $l$ 不是 $S$ 的最大元素。假设 $r$ 是 $S$ 中大于 $l$ 的最小元素。
    
    - 如果是 $a_l > a_r$ ，则令 $a_l = a_l + a_r$ 并从 $S$ 中删除 $r$ 。
    - 如果是 $a_l < a_r$ ，则令 $a_r = a_l + a_r$ ，并从 $S$ 删除 $l$ 。
    - 如果是 $a_l = a_r$ ，则从 $S$ 中选择删除整数 $l$ 或 $r$ ：
        - 如果选择从 $S$ 中删除 $l$ ，则设置 $a_r = a_l + a_r$ 并从 $S$ 中删除 $l$ 。
        - 如果您选择从 $S$ 中删除 $r$ ，则需要设置 $a_l = a_l + a_r$ ，并从 $S$ 中删除 $r$ 。
    
- $f(i)$ 表示这样的整数 $j$ ( $1 \le j \le i$ )的个数，即执行上述操作恰好 $i - 1$ 次后可以得到 $S = \{j\}$ 。

对 $x$ 到 $n$ 的每个整数 $i$ 都需要求出 $f(i)$ 。

## 输入格式

第一行包含 $t$ ( $1 \leq t \leq 10^4$ ) ，表示测试用例数。

每个测试用例的第一行包含两个整数 $n$ 和 $x$ ( $1 \leq n \leq 2 \cdot 10^5; x = n$ )--球的个数和最小索引 $i$ ，您需要找到该索引的 $f(i)$ 。

每个测试用例的第二行包含 $a_1, a_2, \ldots, a_n$ ( $1 \leq a_i \leq 10^9$ ) - 写在每个球上的初始数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，在一行中输出 $n-x+1$ 个空格分隔的整数，其中第 $j$ 个整数表示 $f(x+j-1)$ 。

**样例解释**

在第一个测试用例中，要计算 $f(5)$ 。可以看出，经过 $4$ 次运算后， $S$ 可以包含 $2$ 、 $3$ 或 $4$ 。下面是生成 $S = \{4\}$ 所需的运算。

- 最初是 $S = \{1, 2, 3, 4, 5\}$ 和 $a = [1, 2, 3, 2, 1]$ 。
- 选择 $l = 1$ 。自然是 $r = 2$ 。由于 $a_1< a_2$ ，我们设置 $a_2 = 1 + 2$ ，并从 $S$ 中删除 $1$ 。现在， $S = \{2, 3, 4, 5\}$ 和 $a = [1, 3, 3, 2, 1]$ 。
- 选择 $l = 4$ 。自然是 $r = 5$ 。由于 $a_4> a_5$ ，我们设置 $a_4 = 2 + 1$ ，并从 $S$ 中删除 $5$ 。现在， $S = \{2, 3, 4\}$ 和 $a = [1, 3, 3, 3, 1]$ 。
- 选择 $l = 3$ 。自然是 $r = 4$ 。由于 $a_3 = a_4$ ，我们可以选择删除 $3$ 或 $4$ 。既然要保留 $4$ ，那么就删除 $3$ 。因此，设置 $a_4 = 3 + 3$ 并从 $S$ 中删除 $3$ 。现在， $S = \{2, 4\}$ 和 $a = [1, 3, 3, 6, 1]$ 。
- 选择 $l = 2$ 。自然是 $r = 4$ 。由于 $a_2< a_4$ ，我们设置 $a_4 = 3 + 6$ ，并从 $S$ 中删除 $2$ 。最后是 $S = \{4\}$ 和 $a = [1, 3, 3, 9, 1]$ 。

在第二个测试案例中，要求计算 $f(7)$ 。可以证明，经过 $6$ 次运算后， $S$ 可以包含 $2$ 、 $4$ 、 $6$ 或 $7$ 。

## 样例 #1

### 输入

```
3
5 5
1 2 3 2 1
7 7
4 5 1 2 1 4 5
11 11
1 2 3 1 1 9 3 2 4 1 3
```

### 输出

```
3
4
4
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

