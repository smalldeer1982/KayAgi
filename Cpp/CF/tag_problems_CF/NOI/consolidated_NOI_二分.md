---
title: "Chests and Keys"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1519F
tag: ['动态规划 DP', '二分图']
---

# Chests and Keys

## 题目描述

Alice and Bob play a game. Alice has got $ n $ treasure chests (the $ i $ -th of which contains $ a_i $ coins) and $ m $ keys (the $ j $ -th of which she can sell Bob for $ b_j $ coins).

Firstly, Alice puts some locks on the chests. There are $ m $ types of locks, the locks of the $ j $ -th type can only be opened with the $ j $ -th key. To put a lock of type $ j $ on the $ i $ -th chest, Alice has to pay $ c_{i,j} $ dollars. Alice can put any number of different types of locks on each chest (possibly, zero).

Then, Bob buys some of the keys from Alice (possibly none, possibly all of them) and opens each chest he can (he can open a chest if he has the keys for all of the locks on this chest). Bob's profit is the difference between the total number of coins in the opened chests and the total number of coins he spends buying keys from Alice. If Bob's profit is strictly positive (greater than zero), he wins the game. Otherwise, Alice wins the game.

Alice wants to put some locks on some chests so no matter which keys Bob buys, she always wins (Bob cannot get positive profit). Of course, she wants to spend the minimum possible number of dollars on buying the locks. Help her to determine whether she can win the game at all, and if she can, how many dollars she has to spend on the locks.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 6 $ ) — the number of chests and the number of keys, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 4 $ ), where $ a_i $ is the number of coins in the $ i $ -th chest.

The third line contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ 1 \le b_j \le 4 $ ), where $ b_j $ is the number of coins Bob has to spend to buy the $ j $ -th key from Alice.

Then $ n $ lines follow. The $ i $ -th of them contains $ m $ integers $ c_{i,1}, c_{i,2}, \dots, c_{i,m} $ ( $ 1 \le c_{i,j} \le 10^7 $ ), where $ c_{i,j} $ is the number of dollars Alice has to spend to put a lock of the $ j $ -th type on the $ i $ -th chest.

## 输出格式

If Alice cannot ensure her victory (no matter which locks she puts on which chests, Bob always has a way to gain positive profit), print $ -1 $ .

Otherwise, print one integer — the minimum number of dollars Alice has to spend to win the game regardless of Bob's actions.

## 说明/提示

In the first example, Alice should put locks of types $ 1 $ and $ 3 $ on the first chest, and locks of type $ 2 $ and $ 3 $ on the second chest.

In the second example, Alice should put locks of types $ 1 $ and $ 2 $ on the first chest, and a lock of type $ 3 $ on the second chest.

## 样例 #1

### 输入

```
2 3
3 3
1 1 4
10 20 100
20 15 80
```

### 输出

```
205
```

## 样例 #2

### 输入

```
2 3
3 3
2 1 4
10 20 100
20 15 80
```

### 输出

```
110
```

## 样例 #3

### 输入

```
2 3
3 4
1 1 4
10 20 100
20 15 80
```

### 输出

```
-1
```



---

---
title: "Two Arrays"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1710E
tag: ['博弈论', '二分图']
---

# Two Arrays

## 题目描述

You are given two arrays of integers $ a_1,a_2,\dots,a_n $ and $ b_1,b_2,\dots,b_m $ .

Alice and Bob are going to play a game. Alice moves first and they take turns making a move.

They play on a grid of size $ n \times m $ (a grid with $ n $ rows and $ m $ columns). Initially, there is a rook positioned on the first row and first column of the grid.

During her/his move, a player can do one of the following two operations:

1. Move the rook to a different cell on the same row or the same column of the current cell. A player cannot move the rook to a cell that has been visited $ 1000 $ times before (i.e., the rook can stay in a certain cell at most $ 1000 $ times during the entire game). Note that the starting cell is considered to be visited once at the beginning of the game.
2. End the game immediately with a score of $ a_r+b_c $ , where $ (r, c) $ is the current cell (i.e., the rook is on the $ r $ -th row and $ c $ -th column).

Bob wants to maximize the score while Alice wants to minimize it. If they both play this game optimally, what is the final score of the game?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n,m \leq 2 \cdot 10^5 $ ) — the length of the arrays $ a $ and $ b $ (which coincide with the number of rows and columns of the grid).

The second line contains the $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 5 \cdot 10^8 $ ).

The third line contains the $ m $ integers $ b_1, b_2,\dots, b_n $ ( $ 1 \leq b_i \leq 5 \cdot 10^8 $ ).

## 输出格式

Print a single line containing the final score of the game.

## 说明/提示

In the first test case, Alice moves the rook to $ (2, 1) $ and Bob moves the rook to $ (1, 1) $ . This process will repeat for $ 999 $ times until finally, after Alice moves the rook, Bob cannot move it back to $ (1, 1) $ because it has been visited $ 1000 $ times before. So the final score of the game is $ a_2+b_1=4 $ .

In the second test case, the final score of the game is $ a_3+b_5 $ .

## 样例 #1

### 输入

```
2 1
3 2
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 5
235499701 451218171 355604420 132973458
365049318 264083156 491406845 62875547 175951751
```

### 输出

```
531556171
```



---

---
title: "Doremy's Perfect DS Class (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1764G3
tag: ['二分']
---

# Doremy's Perfect DS Class (Hard Version)

## 题目描述

The only difference between this problem and the other two versions is the maximum number of queries. In this version, you are allowed to ask at most $ \mathbf{20} $ queries. You can make hacks only if all versions of the problem are solved.

This is an interactive problem.

"Everybody! Doremy's Perfect Data Structure Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's Data Structure class, Doremy is teaching everyone a powerful data structure — Doremy tree! Now she gives you a quiz to prove that you are paying attention in class.

Given an array $ a $ of length $ m $ , Doremy tree supports the query $ Q(l,r,k) $ , where $ 1 \leq l \leq r \leq m $ and $ 1 \leq k \leq m $ , which returns the number of distinct integers in the array $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ .

Doremy has a secret permutation $ p $ of integers from $ 1 $ to $ n $ . You can make queries, in one query, you give $ 3 $ integers $ l,r,k $ ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ ) and receive the value of $ Q(l,r,k) $ for the array $ p $ . Can you find the index $ y $ ( $ 1 \leq y \leq n $ ) such that $ p_y=1 $ in at most $ \mathbf{20} $ queries?

Note that the permutation $ p $ is fixed before any queries are made.

## 输出格式

You begin the interaction by reading an integer $ n $ ( $ 3 \le n \le 1024 $ ) in the first line — the length of the permutation.

To make a query, you should output

- "? $ l\ r\ k $ " ( $ 1 \leq l \leq r \leq n $ , $ 1 \leq k \leq n $ )

 in a separate line. After each query, you should read an integer $ x $ — the value of $ Q(l,r,k) $ for $ p $ . In this version of the problem, you can make at most $ 20 $ such queries.To give the answer, you should output

- "! $ y $ " ( $ 1 \leq y \leq n $ )

 in a separate line, where $ p_y=1 $ .After printing a query or the answer, do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks Format

The first line of the hack contains an integer $ n $ ( $ 3 \le n \le 1024 $ ) — the length of the permutation.

The second line of the hack contains $ n $ distinct integers $ p_1,p_2,\ldots,p_n $ ( $ 1 \le p_i\le n $ ) — the permutation.

## 说明/提示

The permutation in the example is $ [3,5,2,1,4] $ .

The input and output for example illustrate possible interaction on that test (empty lines are inserted only for clarity).

In this interaction process:

- For the first query, $ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $ , so the answer is $ 2 $ .
- For the second query, $ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $ , so the answer is still $ 2 $ .
- For the third query, $ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $ , so the answer is $ 1 $ .
- For the fourth query, $ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $ , so the answer is $ 3 $ .

The correct answer is got after $ 4 $ queries, so this process will be judged correct.

## 样例 #1

### 输入

```
5

2

2

1

3
```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4
```



---

---
title: "Simultaneous Coloring"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1989F
tag: ['强连通分量', '整体二分']
---

# Simultaneous Coloring

## 题目描述

You are given a matrix, consisting of $ n $ rows and $ m $ columns.

You can perform two types of actions on it:

- paint the entire column in blue;
- paint the entire row in red.

Note that you cannot choose which color to paint the row or column.

In one second, you can perform either one action or multiple actions at the same time. If you perform one action, it will be free. If you perform $ k > 1 $ actions at the same time, it will cost $ k^2 $ coins. When multiple actions are performed at the same time, for each cell affected by actions of both types, the color can be chosen independently.

You are asked to process $ q $ queries. Before each query, all cells become colorless. Initially, there are no restrictions on the color of any cells. In the $ i $ -th query, a restriction of the following form is added:

- $ x_i~y_i~c_i $ — the cell in row $ x_i $ in column $ y_i $ should be painted in color $ c_i $ .

Thus, after $ i $ queries, there are $ i $ restrictions on the required colors of the matrix cells. After each query, output the minimum cost of painting the matrix according to the restrictions.

## 输入格式

The first line contains three integers $ n, m $ and $ q $ ( $ 1 \le n, m, q \le 2 \cdot 10^5 $ ) — the size of the matrix and the number of queries.

In the $ i $ -th of the next $ q $ lines, two integers $ x_i, y_i $ and a character $ c_i $ ( $ 1 \le x_i \le n $ ; $ 1 \le y_i \le m $ ; $ c_i \in $ {'R', 'B'}, where 'R' means red, and 'B' means blue) — description of the $ i $ -th restriction. The cells in all queries are pairwise distinct.

## 输出格式

Print $ q $ integers — after each query, output the minimum cost of painting the matrix according to the restrictions.

## 样例 #1

### 输入

```
2 2 4
1 1 R
2 2 R
1 2 B
2 1 B
```

### 输出

```
0
0
0
16
```

## 样例 #2

### 输入

```
3 5 10
1 1 B
2 5 B
2 2 B
2 3 R
2 1 B
3 2 R
3 3 B
1 2 R
1 3 B
3 1 B
```

### 输出

```
0
0
0
0
0
0
16
16
25
25
```



---

---
title: "Dora's Paint"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2006F
tag: ['拓扑排序', '二分图']
---

# Dora's Paint

## 题目描述

不幸的是，朵拉在绘制班级壁画时颜料洒了。她将壁画视作一个 $n \times n$ 的矩阵 $b$，最开始时，矩阵中所有元素 $b_{i,j}$ 都是 0。

朵拉有两支不同颜色的画笔，在一次操作中，她可以使用其中一支画笔来为矩阵上色：

- 第一支画笔的颜色为 1，可以为矩阵中的某一列上色。具体来说，朵拉选择某一列 $1 \leq j \leq n$，然后将这一列中所有的元素设置为 1，即 $b_{i,j} := 1$ 对于所有 $1 \leq i \leq n$；
- 第二支画笔的颜色为 2，可以为矩阵中的某一行上色。具体来说，朵拉选择某一行 $1 \leq i \leq n$，然后将这一行中所有的元素设置为 2，即 $b_{i,j} := 2$ 对于所有 $1 \leq j \leq n$。

朵拉需要最终让整个矩阵 $b$ 只包含颜色 1 和颜色 2。

对于任意矩阵 $b$，定义 $f(b)$ 为从初始全 0 矩阵经过最少操作次数变为矩阵 $b$ 所需的最小步骤数。矩阵 $b$ 的“美丽值”是指用恰好 $f(b)$ 次操作将初始矩阵变为 $b$ 的不同方法数。如果不能将初始矩阵变为 $b$，那么美丽值为 0。

然而，朵拉随手犯了一个错误；实际的矩阵 $a$ 和真正应该得到的矩阵 $b$ 仅有一个元素不同。换句话说，存在一个唯一的元素位置 $(i, j)$，使得 $a_{i,j} = 3 - b_{i,j}$。

请帮助朵拉计算在所有可能错误的情况下，真实矩阵 $b$ 的期望美丽值，并对结果取模 $998\,244\,353$。

由于矩阵比较大，朵拉只告诉我们 $m$ 个颜色为 1 的元素的位置，剩下的 $n^2 - m$ 个元素的颜色为 2。

## 输入格式

每个测试点有多个测试用例。第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。接下来是每个测试用例的具体内容。

对于每个测试用例的第一行，输入两个整数 $n$ 和 $m$ ($2 \leq n \leq 2 \cdot 10^5$, $0 \leq m \leq \min(10^6, n^2)$)，表示矩阵的大小以及颜色为 1 的元素数量。

接下来 $m$ 行，每行包含两个整数 $x_i$ 和 $y_i$ ($1 \leq x_i, y_i \leq n$)，表示矩阵 $a$ 中位置 $(x_i, y_i)$ 的元素是颜色 1。

确保当 $i \neq j$ 时，$(x_i, y_i) \neq (x_j, y_j)$。

保证所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$，$m$ 的总和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出一个整数——这个整数是对真实矩阵 $b$ 的期望美丽值取模 $998\,244\,353$ 的结果。

## 说明/提示

在第一个测试用例中，矩阵 $a = \left[\begin{matrix}1&1\\2&2\end{matrix}\right]$。考虑将元素 $(1,1)$ 改变以计算答案。

可以证明，将初始矩阵变为 $\left[\begin{matrix}2&1\\2&2\end{matrix}\right]$ 需要至少 3 步。具体方法是，先将第一行涂成颜色 2，然后将第二列涂成颜色 1，最后将第二行涂成颜色 2。操作过程如下：
$$
\left[\begin{matrix}0&0\\0&0\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&2\\0&0\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&1\\0&1\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&1\\2&2\end{matrix}\right]
$$

事实证明，这种方法是唯一可以用3步实现的方法。因此，矩阵 $\left[\begin{matrix}2&1\\2&2\end{matrix}\right]$ 的美丽值为 1。类似地，如果改变矩阵中的其他元素，美丽值仍然是 1，所以真实矩阵 $b$ 的期望美丽值为 1。

在第二个测试用例中，矩阵 $a = \left[\begin{matrix}1&2\\2&2\end{matrix}\right]$。考虑将元素 $(2, 2)$ 改变以计算答案。

可以证明无法将初始矩阵变为 $\left[\begin{matrix}1&2\\2&1\end{matrix}\right]$，因此其美丽值是 0。如果改变矩阵中的其他任何元素，美丽值总是 2，所以期望美丽值为 $\frac{0 + 2 + 2 + 2}{4} = \frac{6}{4} \equiv 499\,122\,178 \pmod {998\,244\,353}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
2 2
1 1
1 2
2 1
1 1
3 2
1 1
3 3
6 0
5 10
1 1
1 2
1 3
2 1
2 3
5 1
5 2
5 3
5 4
5 5
3 5
1 1
1 3
2 2
3 1
3 3
4 3
1 1
2 3
2 4
```

### 输出

```
1
499122178
665496236
120
79859554
776412275
1
```



---

---
title: "Go Learn! (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G1
tag: ['动态规划 DP', '二分']
---

# Go Learn! (Easy Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3000 $ and the sum of $ n $ does not exceed $ 10^4 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3000 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
2
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
```

### 输出

```
3 78
3 839271911
```



---

---
title: "Go Learn! (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G2
tag: ['动态规划 DP', '二分', '动态规划优化']
---

# Go Learn! (Hard Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3\cdot 10^5 $ and the sum of $ n $ does not exceed $ 10^6 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3 \cdot 10^5 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
3
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
300000 1
5 10
```

### 输出

```
3 78
3 839271911
0 702730519
```



---

---
title: "Formation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2057F
tag: ['二分', '扫描线']
---

# Formation

## 题目描述

某天，“T 世代”的老师们为了培养学生的纪律性，让他们排成一列进行计算。这一列共有 $n$ 名学生，第 $i$ 名学生的身高为 $a_i$。

如果满足对于每一个从 $1$ 到 $n-1$ 的 $i$，都有 $a_i \cdot 2 \ge a_{i + 1}$，则称这一列为舒适的。目前，这一列已经是一列舒适的队伍。

老师们希望队列中的最大身高可以更高一些，所以打算让学生们吃比萨。已知每个学生每吃一个比萨，他的身高就会增加 $1$。一份比萨只能让一个学生吃，但每个学生可以无限次吃比萨。在所有学生吃完比萨后，需要确保这一列依然是舒适的。

老师们有 $q$ 个选择计划，决定要订多少个比萨。对于每种方案 $k_i$，你的任务是回答：当学生们最多吃掉 $k_i$ 个比萨时，能达到的最大身高 $\max(a_1, a_2, \ldots, a_n)$ 是多少？

## 输入格式

每次输入包含多组测试用例。第一行是一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。随后是每组测试用例的数据。

每组测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 5 \cdot 10^4$），分别表示学生的人数和订购比萨方案的数量。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$），表示学生们的初始身高，且保证此时队列是舒适的。

接下来的 $q$ 行中，每行包含一个整数 $k_i$（$1 \le k_i \le 10^9$），表示当前订购比萨的上限数量。

保证所有测试用例中 $n$ 的总和不超过 $5 \cdot 10^4$。

保证所有测试用例中 $q$ 的总和不超过 $5 \cdot 10^4$。

## 输出格式

对于每组测试用例中的每个比萨数量方案，输出在确保队列仍然舒适的情况下，可能达到的最大身高值 $\max(a_1, a_2, \ldots, a_n)$。

## 说明/提示

在第一组输入数据的第一个查询中，可以给第一个学生吃 $3$ 个比萨，再给第二个学生吃 $6$ 个比萨，那么最终的身高数组会是 $[13, 26]$（满足 $13 \cdot 2 \ge 26$，所以队列是舒适的），此时最大身高是 $26$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 1
10 20
10
6 7
3 1 2 4 5 6
1
2
4
8
16
32
64
10 4
1 2 4 8 16 32 64 128 256 512
10
100
1000
10000
```

### 输出

```
26
7 8 10 12 19 35 67
513 560 1011 10001
```



---

---
title: "Points and Segments"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF429E
tag: ['图论', '离散化', '二分图']
---

# Points and Segments

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct segments $ [l_{i},r_{i}] $ on the $ OX $ axis. He can draw each segment with either red or blue. The drawing is good if and only if the following requirement is met: for each point $ x $ of the $ OX $ axis consider all the segments that contains point $ x $ ; suppose, that $ r_{x} $ red segments and $ b_{x} $ blue segments contain point $ x $ ; for each point $ x $ inequality $ |r_{x}-b_{x}|<=1 $ must be satisfied.

A segment $ [l,r] $ contains a point $ x $ if and only if $ l<=x<=r $ .

Iahub gives you the starting and ending points of all the segments. You have to find any good drawing for him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of segments. The $ i $ -th of the next $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ) — the borders of the $ i $ -th segment.

It's guaranteed that all the segments are distinct.

## 输出格式

If there is no good drawing for a given test, output a single integer -1. Otherwise output $ n $ integers; each integer must be 0 or 1. The $ i $ -th number denotes the color of the $ i $ -th segment (0 is red and 1 is blue).

If there are multiple good drawings you can output any of them.

## 样例 #1

### 输入

```
2
0 2
2 3

```

### 输出

```
0 1

```

## 样例 #2

### 输入

```
6
1 5
1 3
3 5
2 10
11 11
12 12

```

### 输出

```
0 1 0 1 0 0

```



---

---
title: "Summer Dichotomy"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF538H
tag: ['深度优先搜索 DFS', '二分图', '构造']
---

# Summer Dichotomy

## 题目描述

 $ T $ students applied into the ZPP class of Summer Irrelevant School. The organizing committee of the school may enroll any number of them, but at least $ t $ students must be enrolled. The enrolled students should be divided into two groups in any manner (it is possible that one of the groups will be empty!)

During a shift the students from the ZPP grade are tutored by $ n $ teachers. Due to the nature of the educational process, each of the teachers should be assigned to exactly one of two groups (it is possible that no teacher will be assigned to some of the groups!). The $ i $ -th teacher is willing to work in a group as long as the group will have at least $ l_{i} $ and at most $ r_{i} $ students (otherwise it would be either too boring or too hard). Besides, some pairs of the teachers don't like each other other and therefore can not work in the same group; in total there are $ m $ pairs of conflicting teachers.

You, as the head teacher of Summer Irrelevant School, have got a difficult task: to determine how many students to enroll in each of the groups and in which group each teacher will teach.

## 输入格式

The first line contains two space-separated integers, $ t $ and $ T $ ( $ 1<=t<=T<=10^{9} $ ).

The second line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n<=10^{5} $ , $ 0<=m<=10^{5} $ ).

The $ i $ -th of the next $ n $ lines contain integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ).

The next $ m $ lines describe the pairs of conflicting teachers. Each of these lines contain two space-separated integers — the indices of teachers in the pair. The teachers are indexed starting from one. It is guaranteed that no teacher has a conflict with himself and no pair of conflicting teachers occurs in the list more than once.

## 输出格式

If the distribution is possible, print in the first line a single word 'POSSIBLE' (without the quotes). In the second line print two space-separated integers $ n_{1} $ and $ n_{2} $ — the number of students in the first and second group, correspondingly, the contstraint $ t<=n_{1}+n_{2}<=T $ should be met. In the third line print $ n $ characters, the $ i $ -th of which should be 1 or 2, if the $ i $ -th teacher should be assigned to the first or second group, correspondingly. If there are multiple possible distributions of students and teachers in groups, you can print any of them.

If the sought distribution doesn't exist, print a single word 'IMPOSSIBLE' (without the quotes).

## 样例 #1

### 输入

```
10 20
3 0
3 6
4 9
16 25

```

### 输出

```
POSSIBLE
4 16
112

```

## 样例 #2

### 输入

```
1 10
3 3
0 10
0 10
0 10
1 2
1 3
2 3

```

### 输出

```
IMPOSSIBLE

```



---

---
title: "Tanya is 5!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF737E
tag: ['网络流', '二分图']
---

# Tanya is 5!

## 题目描述

Tanya 五岁了！所以她所有的朋友都来给她庆祝生日。包括Tanya在内，一共有 $n$ 个孩子参加了庆典。

庆典就快要结束了，还有最后一项活动——玩游戏机没有完成。在大厅里放着 $m$ 台游戏机，它们的编号为 $1\!\sim\!m$ 。 每个孩子都有一个游戏机清单，上面有他想玩的游戏机编号和对应的时间。对于每一台游戏机，在同一时刻只能被一个孩子使用。

现在已经是傍晚了，大人们都想快点回家。为了加快这个活动的进程，对于每一台机器你都可以额外租用**一台**备用机器。对于编号为 $j$ 的机器的备用机，租金为 $p_j$ 。当你租用了一台备用机以后，它可以在任何时间被使用。备用机和游戏机一样，在同一时刻只能被一个孩子使用。

如果你有 $b$ 元预算来租用备用机，需要多长时间才能使所有孩子都完成他们的游戏机清单？每台游戏机只有一台备用机可租用，所以你不可能拥有三台编号相同的机器。

孩子们可以在任意时间停止或者继续游戏。在你租用了第 $j$ 台游戏机的备用机后，如果第 $i$ 个孩子想要玩第 $j$ 台游戏机，他可以花一部分时间玩第 $j$ 台游戏机，花另一部分时间玩第 $j$ 台游戏机的备用机（每一部分都可以为空）。停止和改变使用机器的行为都可以在任何整数时刻发生，并且认为是瞬间完成，不花费时间。当然，一个孩子不可能同时使用两台机器。

记住，这不是为了省钱（没有人会为了省钱而牺牲孩子的快乐！）, 这是为了尽量缩短孩子们完成清单所需的时间。

## 输入格式

第一行包含三个整数 $n$，$m$ 和 $b$ $(1\!\le\!n\!\le\!40 $，$1\!\le\!m\!\le\!10$，$0\!\le\!b\!\le\!10^6)$，分别表示孩子数量，游戏机数量和预算。

第二行包含 $m$ 个整数 $p_1$，$p_2$，$\dots$，$p_m(1\!\le\!p_j\!\le\!10^6)$，其中 $p_j$ 表示编号为 $j$ 的游戏机的备用机所需租金。

接下来有 $n$ 行，第 $i$ 行描述了第 $i$ 个孩子的游戏机清单。每一行开头有一个整数 $k_i(0\!\le\!k_i\!\le\!m)$ ，表示第 $i$ 个孩子想玩的游戏机的数量。之后有 $k_i$ 对数，第 $y$ 对是 $x_{iy},t_{iy}$ 。这表示第 $i$ 个孩子想在编号为 $x_{iy}$ 的游戏机上玩 $t_{iy}$ 分钟。在这 $n$ 行中，$x_{iy}$ 的值是不同的。$(1\!\le\!x_{iy}\!\le\!m$，$1\!\le\!t_{iy}\!\le\!2500)$

## 输出格式

在第一行输出所有孩子完成他们的游戏机清单的最小时间。

在第二行输出一个长度为 $m$ 的$01$字符串，如果租用了编号为 $j$ 的游戏机的备用机，那么第 $j$ 个字符为  $1$，否则为 $0$。

在第三行输出一个整数 $g(0\le\!g\!\le10^6)$，表示所有孩子连续玩游戏机的时间片段总数。
接下来 $g$ 行输出四个整数 $i$，$j$，$s$，$d$，表示第 $i$ 个孩子从 $s$ $(0\le\!s)$ 时刻开始玩了 $d\;(1\le\!d)$。你可以以任意顺序输出这些行。

如果有多个可能的答案，请输出其中任意一个。

## 样例 #1

### 输入

```
2 2 100
3 7
2 1 3 2 1
2 1 3 2 1

```

### 输出

```
4
10
8
1 1 0 1
2 2 0 1
1 1 1 1
2 1 1 1
2 1 2 1
1 1 2 1
1 2 3 1
2 1 3 1

```

## 样例 #2

### 输入

```
3 2 15
11 7
2 2 10 1 5
1 2 20
2 1 4 2 3

```

### 输出

```
20
01
17
2 2 0 4
2 2 4 1
1 1 5 2
2 2 5 2
1 2 7 5
2 2 7 5
2 2 12 1
1 2 12 1
3 1 13 4
2 2 13 4
1 2 13 4
1 1 17 2
3 2 17 2
2 2 17 2
1 1 19 1
2 2 19 1
3 2 19 1

```



---

