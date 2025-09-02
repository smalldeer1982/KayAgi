---
title: "[ICPC 2024 Xi'an I] Guess The Tree"
layout: "post"
diff: 提高+/省选-
pid: P10553
tag: ['2024', '交互题', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Guess The Tree
## 题目描述

There is a full binary tree with $n$ levels(so it has exactly $2^n-1$ nodes). Each node has an integer ID from $1$ to $2^n-1$, and the $2^n-1$ IDs form an arrangement from $1$ to $2^n-1$, but you don't know.

You need to find the IDs of the $2^n-1$ nodes using at most $4800$ queries.
## 输入格式

The first line contains one integer $n(1\leq n\leq 10)$, the levels of the full binary tree.

To ask a query, you need to pick two nodes with IDs $u,v(1\leq u,v\leq 2^n-1)$, and print the line of the following form:

> "? u v"

After that, you will receive:

> "t"

The lowest common ancestor's ID of $u$ and $v$.

You can ask at most $4800$ queries.

If you have found the structure of the tree, print a line of the following form:

"! $f_1\ f_2\ f_3\ f_4$ ... $f_{2^n-1}$"

$f_i$ means the i-th node's father's ID. If it has no father, then $f_i=-1$.

After printing a query or the answer for a test case, do not forget to output the end of line and flush the output. Otherwise, you will get the verdict 'Idleness Limit Exceeded'. To do this, use:

`fflush(stdout)` or `cout.flush()` in C++;

`System.out.flush()` in Java;

`stdout.flush()` in Python.

The interactor in this task is not adaptive.
## 样例

### 样例输入 #1
```
2

3

3

3
```
### 样例输出 #1
```

? 1 2

? 2 3

? 1 3

! 3 3 -1
```
## 提示

In this case, the tree's root is $3$, it's two sons are $1$ and $2$.

For any query "? a b",if $a\neq b$, the jury will return answer $3$.

So we found the tree's root is $3$ .


---

---
title: "[ICPC 2024 Xi'an I] Turn Off The Lights"
layout: "post"
diff: 提高+/省选-
pid: P10554
tag: ['2024', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Turn Off The Lights
## 题目描述

Kitty has $n^2$ lights, which form an $n\times n$ matrix.

One day, Kitty found that some of these lights were on, and some were off. Kitty wants to turn them all off.

To achieve her goal, Kitty can perform three types of operations:

- (1) Choose a row, reverse the state of this row. It means if a light of this row is on, after this operation, it is now off. If a light of this row is off, after this operation, it is now on.

- (2) Choose a column, reverse the state of this column. It means if a light of this column is on, after this operation, it is now off. If a light of this column is off, after this operation, it is now on.

- (3) Choose exactly one light, reverse the state of this light. **This operation can only be performed not more than $k$ times.**

For the current state, help Kitty achieve her goal within $3n$ operations.
## 输入格式

The first line contains two integers $n(1\leq n\leq 1000),k(0\leq k < n)$, indicating as described above.

Then $n$ lines follow, each line has exactly $n$ numbers, $0$ represents that the light is turned off at this time, while $1$ represents the opposite.

The $y$-th number of the $(x+1)$-th line in input means the light at coordinate $(x,y)$.
## 输出格式

If Kitty can not achieve her goal,print $-1$ in a single line.

Otherwise, print $M(0\leq M\leq 3n)$ in the first line, indicating the number of operations she needs to perform.

The next $M$ lines, each line contains $2$ integers $x,y$, separated by white space.

If $1\leq x\leq n,1\leq y\leq n$, it means Kitty will reverse the light at coordinate $(x,y)$.

If $x=0,1\leq y\leq n$, it means Kitty will reverse all lights at coordinates $(z,y)1\leq z\leq n$.

If $1\leq x\leq n,y=0$, it means Kitty will reverse all lights at coordinates $(x,z)1\leq z\leq n$.

If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
2 0
0 1
1 0
```
### 样例输出 #1
```
2
0 2
2 0
```
### 样例输入 #2
```
3 1
1 0 0
0 1 0
0 0 1
```
### 样例输出 #2
```
-1
```


---

---
title: "[ICPC 2024 Xi'an I] Fix the Tree"
layout: "post"
diff: 提高+/省选-
pid: P10555
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Fix the Tree
## 题目描述

You are given a tree consisting of $n$ vertices. Each vertex $i$ of this tree has a value $w_i$ assigned to it.

Now the vertex $u$ will be broken. Once it's broken, vertex $u$ and all edges with one end at vertex $u$ will be removed from the tree.

To make the tree connected, you can do the following operation any number of times(possibly zero) in any order:

- First choose two vertices $u$ and $v$ from the tree;
- Then pay $w_u+w_v$ coins, and add an edge between vertices $u$ and $v$;
- At last, replace $w_u+1$ with $w_u$, replace $w_v+1$ with $w_v$.

Your task is to calculate the minimum number of coins to be paid.

But you don't know which vertex $u$ is, so you need to find the answer for each $1\le u\le n$. Please answer all the queries independently.
## 输入格式

The first line contains a single integer $n(2\le n\le 10^6)$ --- the number of vertices in this tree.

The next line contains $n$ numbers, the $i$ -th number is $w_i(1\le w_i\le n)$.

The next $n-1$ lines contain a description of the tree's edges. The $i$ -th of these lines contains two integers $u_i$ and $v_i(1\le u_i,v_i\le n) $ --- the numbers of vertices connected by the $i$ -th edge.

It is guaranteed that the given edges form a tree.
## 输出格式

Print $n$ integers, the $i$ -th integer is the answer when $u=i$.
## 样例

### 样例输入 #1
```
6
1 1 1 1 1 1
1 2
1 3
1 4
2 5
2 6
```
### 样例输出 #1
```
4 4 0 0 0 0
```
### 样例输入 #2
```
4
1 2 3 4
1 2
1 3
1 4
```
### 样例输出 #2
```
12 0 0 0
```
### 样例输入 #3
```
7
1 2 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7
```
### 样例输出 #3
```
5 12 16 0 0 0 0
```
## 提示

给定一个有 $n$ 个点组成的树，每个点有一个权值 $w_i$。  
点 $u$ 和相邻的边被删除。  
你可以进行以下操作任意次数（可以为 $0$）,让树重新成为连通图：
1. 选择两个点 $u$、$v$；
2. 花费 $w_u + w_v$ 的代价连接一条边 $(u,v)$；
3. $w_u \leftarrow w_u+1,w_v \leftarrow w_v+1$。

对于每个 $u$ 计算最小代价。


---

---
title: "[ICPC 2024 Xi'an I] Dumb Robot"
layout: "post"
diff: 提高+/省选-
pid: P10557
tag: ['2024', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Dumb Robot
## 题目描述

You have a dumb robot, and you are going to let it play games with $n$ robots.

There is a matrix $A$ with three rows and three columns in the game. We call the number of row $i$ and column $j$ of this matrix $A_{i,j}$. The game goes like this:

Two players each choose an integer from $[1,3]$ at the same time. We call the number your robot chooses $i$, and the number the other robot chooses $j$.
The score is $A_{i,j}$.
In game $i$, your robot will play this game with the $i$ -th robot. The $i$ -th robot has a probability of choosing $1$ as $p_{i,1}$, a probability of choosing $2$ as $p_{i,2}$, and a probability of choosing $3$ as $p_{i,3}$.

Your goal is to make the expected value of the score not negative in each game. But your robot is very dumb, so it will choose $1$ with probability $q_1$, $2$ with probability $q_2$, and $3$ with probability $q_3$, and you don't know the value of $q_1,q_2,q_3$.

We all know that $q_1+q_2+q_3=1$. If $q_1,q_2,q_3$ are chosen uniformly at random from a set of all possible cases, please calculate the probability that you will reach your goal.
## 输入格式

The first line contains one integer $n$($1\le n\le10^4$).

Each of the next $3$ lines contains $3$ integers, the $j$ -th integer in the $i$ -th of these lines is $A_{i,j}$($-20\le A_{i,j}\le20$).

Each of the next $n$ lines contains $3$ real numbers, the $j$ -th number in the $i$ -th of these lines is $p_{i,j}$. It is guaranteed that $p_{i,1}+p_{i,2}+p_{i,3}=1$ and $0\le p_{i,j}$.
## 输出格式

Output the answer to the problem. It is guaranteed that the answer will never be $0$.

Your answer is considered correct if its absolute or relative error does not exceed $10^{-2}$. Formally, let your answer be $a$, and the jury's answer be $b$. Your answer is accepted if and only if $\frac{|a-b|}{max(1,|b|)} \leq 10^{-2}$.


## 样例

### 样例输入 #1
```
1
1 1 1
 -1 2 1
0 -3 2
0.1 0.6 0.3
```
### 样例输出 #1
```
0.748252
```
### 样例输入 #2
```
8
1 3 -2
0 0 2
-2 2 1
0.1 0.3 0.6
0 0 1
0.5 0.2 0.3
0 0 1
1 0 0
0 0 1 
0.33 0.33 0.34
0.16 0.16 0.68
```
### 样例输出 #2
```
0.111111
```
## 提示

In example $1$, for example, $(q_1=1,q_2=0,q_3=0)$ is ok. In this case, Your robot will always choose $1$, so no matter what number will robot $1$ choose, the score will always be $1$, which is enough to reach your goal.


---

---
title: "[SEERC 2020] Disk Sort"
layout: "post"
diff: 提高+/省选-
pid: P10739
tag: ['2020', 'Special Judge', 'ICPC']
---
# [SEERC 2020] Disk Sort
## 题目描述

你有 $n+1$ 根棍子，一开始 $1 \sim n$ 的每根棍子上面都会存在 $3$ 个盘，颜色不超过 $n$ 种。

每次操作，你可以选择一对 $(a_i,b_i)$，表示将 $a_i$ 最顶上的圆盘放到 $b_i$ 最上面（$a_i$ 的圆盘数量至少为 $1$，$b_i$ 的数量至多为 $2$）。

你需要构造出一种合法方案使得操作结束后每个盘上的颜色都一样且 $n+1$ 号为空。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 1000)$，表示共有 $n$ 根棍子。

接下来 $3$ 行，每行 $n$ 个整数 $c_{i,j}\ (1 \leq c_{i,j} \leq n)$，表示第 $j$ 个棍子上面自上向下数第 $i$ 个的颜色。
## 输出格式

第一行一个整数 $k\ (1 \leq k \leq 6n)$，表示操作次数。

然后 $k$ 行，每行一对 $(a_i,b_i)$，表示交换的对象。
## 样例

### 样例输入 #1
```
4
2 3 1 4
2 1 1 4
2 3 3 4
```
### 样例输出 #1
```
8
3 5
3 5
2 3
2 5
2 3
5 2
5 2
5 2

```
### 样例输入 #2
```
2
1 2
1 2
1 2
```
### 样例输出 #2
```
0
```


---

---
title: "[SEERC 2020] Fence Job"
layout: "post"
diff: 提高+/省选-
pid: P10741
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Fence Job
## 题目描述

Fred 有一个长度为 $n$ 的排列 $h$，每次操作他可以选择一段区间 $[l,r]$，令 $h_i = \min_{j=l}^{r}h_j\ (i \in [l,r])$。

问进行若干次操作（可以为 $0$ 次）后不同的数组数量，对 $10^9 + 7$ 取模。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 3000)$。

接下来一行 $n$ 个整数 $h_i\ (1 \leq h_i \leq n)$。
## 输出格式

输出操作后不同数组的数量模 $10^9+7$ 的值。
## 样例

### 样例输入 #1
```
3
1 3 2
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
1 2 3 4 5

```
### 样例输出 #2
```
42
```
### 样例输入 #3
```
7
1 4 2 5 3 6 7
```
### 样例输出 #3
```
124
```


---

---
title: "[SEERC 2020] Modulo Permutations"
layout: "post"
diff: 提高+/省选-
pid: P10744
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Modulo Permutations
## 题目描述

求长度为 $n$ 的 $1 \sim n$ 的所有排列总数，其中满足 $p_i \bmod p_{i+1} \leq 2$ 的（此处 $p_{n+1} = p_1$），对 $10^9 + 7$ 取模后的值。
## 输入格式

一个整数 $n\ (1 \leq n \leq 10^6)$。
## 输出格式

输出答案模 $10^9+7$ 后的值。
## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
2
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3
```
### 样例输出 #3
```
6
```
### 样例输入 #4
```
4
```
### 样例输出 #4
```
16
```
### 样例输入 #5
```
5
```
### 样例输出 #5
```
40
```
### 样例输入 #6
```
1000000
```
### 样例输出 #6
```
581177467
```


---

---
title: "[EC Final 2020] City Brain"
layout: "post"
diff: 提高+/省选-
pid: P10819
tag: ['贪心', '2020', '三分', 'Special Judge', 'O2优化', '最短路', 'ICPC']
---
# [EC Final 2020] City Brain
## 题目描述

Prof. Pang works for the City Brain program of Capital Grancel. The road network of Grancel can be represented by an undirected graph. Initially, the speed limit on each road is $1$m/s. Prof. Pang can increase the speed limit on a road by $1$m/s with the cost of $1$ dollar. Prof. Pang has $k$ dollars. He can spend any nonnegative integral amount of money on each road. If the speed limit on some road is $a$m/s, it takes $1/a$ seconds for anyone to go through the road in either direction.

After Prof. Pang spent his money, Prof. Du starts to travel from city $s_1$ to city $t_1$ and Prof. Wo starts to travel from city $s_2$ to city $t_2$. Help Prof. Pang to spend his money wisely to minimize the sum of minimum time of Prof. Du's travel and Prof. Wo's travel. It is guaranteed that $s_1$ and $t_1$ are connected by at least one path and that $s_2$ and $t_2$ are connected by at least one path.
## 输入格式

The first line contains three integers $n$, $m$, $k$ ($1\le n \le 5000$, $0\le m \le 5000$, $0\le k\le 10^9$) separated by single spaces denoting the number of vertices, the number of edges in the graph and the number of dollars Prof. Pang has.

Each of the following $m$ lines contains two integers $a$, $b$ ($1\le a, b\le n, a\neq b$) separated by a single space denoting the two endpoints of one road. There can be multiple roads between the same pair of cities.

The following line contains four integers $s_1$, $t_1$, $s_2$, $t_2$ ($1\le s_1, t_1, s_2, t_2\le n$) separated by single spaces denoting the starting vertices and ending vertices of Prof. Du and Prof. Wo's travels.
## 输出格式

Output one decimal in the only line -- the minimum sum of Prof. Du's travel time and Prof. Wo's travel time. The answer will be considered correct if its absolute or relative error does not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
6 5 1
1 2
3 2
2 4
4 5
4 6
1 5 3 6
```
### 样例输出 #1
```
5.000000000000
```
### 样例输入 #2
```
1 0 100
1 1 1 1
```
### 样例输出 #2
```
0.000000000000
```
### 样例输入 #3
```
4 2 3
1 2
3 4
1 2 3 4
```
### 样例输出 #3
```
0.833333333333
```


---

---
title: "[NERC2024] BitBitJump"
layout: "post"
diff: 提高+/省选-
pid: P12093
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] BitBitJump
## 题目描述

BitBitJump is a one instruction set computer. Thus, it has only one instruction: $\texttt{bbj a, b, c}$, which copies an $a$-th bit of memory to the $b$-th bit of memory and then jumps to address $c$.

Let's consider a 16-bit BitBitJump computer. It has $2^{16}$ bits of memory organized in $2^{12}$ 16-bit words. Words are counted from 0, and 
bits in a word are counted from the least significant (0-th) bit to the most significant (15-th) bit. 

This computer has a single instruction pointer register $(\mathrm{IP})$, and execution starts with $\mathrm{IP}=0$. If the current $\mathrm{IP} \ge 2^{12}-2$, the computer stops. Otherwise, it uses the $\mathrm{IP}$-th word as~$a$, the $(\mathrm{IP}+1)$-th word as~$b$, the $(\mathrm{IP}+2)$-th word as $c$, and performs the \texttt{bbj a, b, c} instruction: copies the $(a \& 15)$-th bit of the $(a \gg 4)$-th word to the $(b \& 15)$-th bit of the $(b \gg 4)$-th word, and sets $\mathrm{IP}=c$. Here, $\&$ represents bitwise AND, and $\gg$ represents bitwise shift right operation. Notice that the value of $c$ is read from memory after the bit copy, so if the instruction modified its own $c$, the new value will be used for $\mathrm{IP}$.

For example, the $\texttt{bbj 32, 35, 5}$ instruction placed at the memory start will
be executed as follows:

- $a=32$ and $b=35$ are read from the memory.
- The 0-th bit of the 2-nd word (its value is $5 \& 1 = 1$) will be copied to the 3-rd bit of the same word, so the 2-nd word will have the value of $5 + 2^3 = 13$.
- Then $c=13$ is read from memory, and $\mathrm{IP}$ is set to 13.

Let's call the $(2^{12}-1)$-th word ($2^{16}-16 \ldots 2^{16}-1$-th bits of memory) an $\textit{IO-word}$. An $\textit{x-comparator}$ is a program which checks whether the value of the IO-word is equal to $x$. It should stop after execution of no more than $2^{12}$ instructions, leaving the lowest bit of the IO-word equal to $1$ if the original value of the IO-word was equal to $x$, and $0$ otherwise.

Write a program that generates an $x$-comparator for the given value of $x$.
## 输入格式

The input contains a single decimal integer $x$ ($0 \le x < 2^{16}$) --- the value for which to build the $x$-comparator.
## 输出格式

The output should contain the $x$-comparator program dump. Dump consists of values for the first $n$ words of the memory ($1 \le n \le 2^{12}-1$). All other words, except the IO-word, are filled with zeroes.

For each of the $n$ words, output its value as a four-character hexadecimal number. Values should be delimited by space or new line characters.
## 样例

### 样例输入 #1
```
0
```
### 样例输出 #1
```
fff0 0026 0003  fff1 0056 0006  fff2 0086 0009  fff3 00b6 000c  fff4 00e6 000f 
fff5 0116 0012  fff6 0146 0015  fff7 0176 0018  fff8 01a6 001b  fff9 01d6 001e 
fffa 0206 0021  fffb 0236 0024  fffc 0266 0027  fffd 0296 002a  fffe 02c6 002d 
ffff 02f6 0030                                                  
0004 fff0 0fff                                                  
0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff 
0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff 
0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff  0000 fff0 0fff 
0000 fff0 0fff
```
## 提示

A dump in the sample output contains a 0-comparator. It consists of the following blocks:
- 16 instructions: the $i$-th of them, counting from 0, copies the $i$-th bit of the input word to the 6-th bit of its own $c$. If the copied bit is zero, it will proceed to the next instruction; otherwise, the next instruction number will be increased by 64.
- The following instruction copies the 4-th bit of the 0-th word (value 1) to the 0-th bit of the IO-word and jumps to the stop address.
- 16 unused words filled with 0.
- 16 equal instructions (starting from word 67). Each of them copies the 0-th bit of the 0-th word (value 0) to the 0-th bit of the IO-word and jumps to the stop address.


---

---
title: "[NWRRC2024] Defective Script"
layout: "post"
diff: 提高+/省选-
pid: P12108
tag: ['2024', '数论', '高斯消元', 'ICPC', '俄罗斯西北']
---
# [NWRRC2024] Defective Script
## 样例

### 样例输入 #1
```
5
4
9 9 6 8
2
3 5
9
9 9 8 2 4 4 3 5 3
3
777 777 777
6
0 1 0 1 0 1
```
### 样例输出 #1
```
5
1
0
777
0
```


---

---
title: "[ICPC 2022 WF] Toy Train Tracks"
layout: "post"
diff: 提高+/省选-
pid: P12308
tag: ['2022', 'Special Judge', '构造', 'ICPC']
---
# [ICPC 2022 WF] Toy Train Tracks
## 样例

### 样例输入 #1
```
4 12

```
### 样例输出 #1
```
LSRLLRLSLSRLLSRL

```
### 样例输入 #2
```
1 5

```
### 样例输出 #2
```
LLLL

```


---

---
title: "[NAC 2025] A Totient Quotient"
layout: "post"
diff: 提高+/省选-
pid: P12620
tag: ['2025', '数论', 'ICPC', '欧拉函数', 'NAC']
---
# [NAC 2025] A Totient Quotient
## 题目描述

For a positive integer $k$, Euler's totient function $\phi(k)$ is defined as the number of positive integers less than or equal to $k$ and relatively prime to $k$.
For example, $\phi(9) = 6$, $\phi(24) = 8,$ and $\phi(1) = 1$. (As a reminder, the greatest common divisor (gcd) of two positive integers $a$ and $b$ is the greatest positive integer that divides both $a$ and $b$. Two positive integers are relatively prime if their gcd is $1$.)

Euler's product formula gives the value of $\phi(k)$ in terms of the prime factorization of $k$. For a prime $p$, let $\nu_p(k)$ be the highest power of $p$ which divides $k$ (so for example, $\nu_2(48) = 4$, $\nu_3(48)=1$, and $\nu_5(48)=0$). If $k$ is a product of powers of prime factors, $k = \prod_{i=1}^j p_i^{\nu_{p_i}(k)}$ (where the product only includes primes $p_i$ with $\nu_{p_i}(k) > 0$), 
then 
$$ \phi(k) = \prod_{i=1}^j \left[(p_i - 1)\left(p_i^{\nu_{p_i}(k)-1}\right)\right].$$

A recent edition of The American Mathematical Monthly (Li et al., *Positive Rational Numbers of the Form $\phi(m^2)/\phi(n^2)$*, 128(2), 2021) proved the following fact about totient quotients: for any pair of positive integers $a$, $b$ there is a unique pair of positive integers $m$, $n$ for which:
- $\frac{a}{b} = \frac{\phi(m^2)}{\phi(n^2)};$
- if a prime $p$ divides the product $mn$, then $\nu_p(m) \neq \nu_{p}(n)$;
- $\gcd(m,n)$ is square-free: that is, for every prime $p$, $\gcd(m,n)$ is not divisible by $p^2$.

Conditions 2 and 3 guarantee that $m$ and $n$ are the unique smallest pair of positive integers satisfying condition 1.

You'd like to verify this claim numerically. Write a program which takes as input two integers $a$ and $b$ and outputs the corresponding pair $m, n$.
## 输入格式

The only line of input contains two space-separated integers $a$ and $b$ ($ 1 \leq a, b \leq 10\,000$). These two integers are guaranteed to be relatively prime. Additionally, $a$ and $b$ will be chosen so that output values $m$ and $n$ are less than $2^{63}$.
## 输出格式

Print the two positive integers $m$ and $n$ satisfying all three of the conditions of The American Mathematical Monthly's theorem, separated by a space. It is guaranteed that $ m, n < 2^{63}$.
## 样例

### 样例输入 #1
```
9 13
```
### 样例输出 #1
```
18 13
```
### 样例输入 #2
```
19 47
```
### 样例输出 #2
```
13110 18612
```


---

---
title: "[NAC 2025] Circle of Leaf"
layout: "post"
diff: 提高+/省选-
pid: P12621
tag: ['动态规划 DP', '2025', '树形 DP', 'ICPC', 'NAC']
---
# [NAC 2025] Circle of Leaf
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/at1ek3bh.png)

Ouroboros from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ouroboros-Zanaq.svg)

## 题目描述

Your friend has given you a rooted tree: a connected graph with $N$ nodes and $N-1$ edges. The nodes of the tree are numbered from $1$ to $N$, with node $1$ being the root of the tree and other nodes numbered arbitrarily.

However, you recently learned about the Ouroboros, an ancient mythical snake that eats its own tail, signifying a cycle with no beginning and end. You dislike the fact that the tree you were given has a very clear beginning at the root, and clear ends at its leaves, so you decide to completely change the structure of this tree into a new graph which you have named an *Ouroboros Graph*.

To construct this Ouroboros Graph, you take the leaves of the tree (the nodes with no direct children) and draw special "leaf" edges that connect every leaf directly to the root. **If there is already an edge connecting a leaf to the root, you still add a duplicate edge.**

With this special graph structure, you can now create lots of different trees by removing some subset of edges, and in the spirit of Ouroboros, the leaves and roots can change depending on which subset of edges you remove. How many different trees can you make by removing a subset of edges from the Ouroboros Graph? Two trees are considered different if one tree has an edge that the other tree does not. (If both a regular and a "leaf" edge connect the same pair of nodes, then they are distinguishable from each other and are considered different edges.) Since the number of trees can be large, compute the answer modulo $998\,244\,353$.
## 输入格式

The first line of input contains a single integer $N$ ($2 \leq N \leq 200\,000$), the number of nodes in the tree.

Each of the next $N-1$ lines contains two space separated integers $a$ and $b$ ($1 \leq a,b \leq N$) specifying that an edge exists between parent node $a$ and child node $b$ in the tree. The input graph is indeed guaranteed to be a tree: there is a unique path of edges between every pair of nodes in the graph.
## 输出格式

Print the number of different trees modulo $998\,244\,353$ that can be created by removing some subset of edges from the input tree's Ouroboros Graph.

## 样例

### 样例输入 #1
```
8
1 3
3 2
1 4
1 7
7 6
6 5
6 8
```
### 样例输出 #1
```
72
```
## 提示

In the diagram below, the left subfigure illustrates the Ouroboros Graph corresponding to Sample Input 1, with the original edges of the tree drawn in black and the "leaf" edges dashed in red. The tree on the right illustrates one of the $72$ possible different trees that can be formed by deleting some subset of edges from the Ouroboros Graph: in this case, original edges $6$--$5$ and $1$--$3$ and "leaf" edges $1$--$8$ and $1$--$4$ were deleted.

![](https://cdn.luogu.com.cn/upload/image_hosting/ljg58dpq.png)


---

---
title: "[NAC 2025] Geometry Rush"
layout: "post"
diff: 提高+/省选-
pid: P12623
tag: ['2025', 'ICPC', '双指针 two-pointer', 'NAC']
---
# [NAC 2025] Geometry Rush
## 题目描述

You are playing the summer's hottest rhythm-based action platformer---Geometry Rush! The game is played on a 2D plane. Your character begins at $(0,0)$ and every second must move at a $45$-degree angle either up-right or down-right, which takes your character from position $(x,y)$ to $(x+1,y+1)$ or $(x+1, y-1)$ respectively. You can change which direction you move every second, but not in between moves. There are obstacles protruding from the floor and ceiling that you must dodge. You win the game if, after $w$ seconds, you reach the line $x=w$ without having touched any obstacles on the way.

The play area extends vertically from $y=-h$ to $y=h$. Obstacles are two polygonal curves: one curve starts at $(0,h)$ and ends at $(w,h)$ and represents a ceiling of varying height. The $x$ values of the vertices of this curve are non-decreasing, and the $y$ values lie between $-h$ and $h$ inclusive. A second polygonal curve starts at $(0,-h)$ and ends at $(w,-h)$ and represents the floor. Its vertices satisfy similar constraints.

Your character is a point of negligible extent: you can move from position $(x,y)$ to $(x+1,y\pm 1)$ so long as the line segment between your start and end position does not intersect either obstacle. (Exactly touching either polygonal curve counts as intersecting an obstacle, and loses the game.)

You have played *a lot* of games of Geometry Rush. To keep the game interesting, you have started to set challenges for yourself. For example: you win the game no matter where you cross the $x=w$ goal line. But for what maximum value of $y$ can you win the game by crossing at $(w,y)$ without touching any obstacles on the way? For what minimum value? Compute these numbers.
## 输入格式

The first line of the input contains four space-separated integers $n$, $m$, $w$, and $h$. The first two integers ($3 \leq n, m \leq 10^{5}$) are the number of vertices in the ceiling and floor polygonal curves, respectively. The second two integers ($3 \leq w, h \leq 10^{5}$) are the width and height of the play area, as described above.

The next $n$ lines each contain two space-separated integers $x$ and $y$ ($0 \leq x \leq w$; $-h \leq y \leq h$): the coordinates of the vertices of the ceiling polygonal curve, in order from left to right. It is guaranteed that the first vertex is at $(0,h)$ and the last vertex is at $(w,h)$.

The next $m$ lines each contain two space-separated integers $x$ and $y$ ($0 \leq x \leq w$; $-h \leq y \leq h$): the coordinates of the vertices of the floor polygonal curve, in order from left to right. It is guaranteed that the first vertex is at $(0,-h)$ and the last vertex is at $(w,-h)$.

For both polygonal curves: the $x$ coordinates are non-decreasing, all vertices are distinct, and the curve does not self-intersect. Neither curve intersects $(0,0)$. (The floor and ceiling curves might intersect each other, in which case the game is unwinnable.)
## 输出格式

If it is impossible to win the game, print $\texttt{impossible}$. Otherwise, print two space-separated integers: the minimum and maximum $y$ values that the player could reach at $x=w$ without losing the game by touching an obstacle along the way.
## 样例

### 样例输入 #1
```
4 4 5 5
0 5
0 2
5 2
5 5
0 -5
0 -2
5 -2
5 -5
```
### 样例输出 #1
```
-1 1
```
### 样例输入 #2
```
4 4 6 5
0 5
0 2
6 2
6 5
0 -5
0 -2
6 -2
6 -5
```
### 样例输出 #2
```
0 0
```
### 样例输入 #3
```
3 3 7 5
0 5
5 -1
7 5
0 -5
2 1
7 -5
```
### 样例输出 #3
```
impossible
```
### 样例输入 #4
```
4 3 5 5
0 5
0 2
5 2
5 5
0 -5
3 -1
5 -5
```
### 样例输出 #4
```
-1 1
```


---

---
title: "[NAC 2025] Mob Grinder"
layout: "post"
diff: 提高+/省选-
pid: P12625
tag: ['2025', 'Special Judge', 'ICPC', 'NAC']
---
# [NAC 2025] Mob Grinder
## 题目描述

In a certain popular sandbox video game, one can build a structure called a *mob grinder*.

A mob grinder consists of an $N\times M$ rectangular grid of tiles. Monsters, also known as "mobs", appear continuously at random places on the grid. The goal of a mob grinder is to move all of the monsters to the top-right tile in the grid, no matter where they originally appear. To accomplish this goal, each tile (except for the top-right tile) has a conveyor belt on it with a specified direction (up, right, down, or left). A monster on a conveyor belt gets moved to the orthogonally adjacent tile in the direction specified by the conveyor belt orientation.

Your job is to place a conveyor belt on each tile (other than the top-right corner) so that no matter where a monster appears on the grid, it will get moved to the top-right corner after a finite amount of time, without ever leaving the bounds of the grid. However, there is a limit on how many conveyor belts you can use of each orientation: your final design must have exactly $U$ conveyor belts going up, $R$ going right, $D$ going down, and $L$ going left.

You are asked to design multiple mob grinders, each with a specification of how many conveyor belts of each type you are allowed to use. Design a valid mob grinder that meets each specification, if possible.
## 输入格式

The first line of input contains an integer $T$ ($1 \leq T \leq 10^5$): the number of mob grinders you need to design.

Each of the next $T$ lines of input contains six space-separated integers that describe one mob grinder specification. The first two integers, $N$ and $M$, ($1\leq N,M$ and $N\cdot M \leq 10^5)$ are the number of rows and columns in the grid, respectively. The last four, $U$, $R$, $D$, $L$ $(0 \leq U, R, D, L$ and $U+R+D+L = (N \cdot M)-1)$, are the number of times you must use each conveyor belt orientation in your design.

It is guaranteed that the sum of $N\cdot M$ over all $T$ mob grinders does not exceed $10^5$.
## 输出格式

Print $T$ mob grinder designs, one for each specification. Separate consecutive designs with a single empty line.

If it is impossible to construct a valid mob grinder respecting the given constraints for the given specification, print $\texttt{impossible}$. Otherwise, print an $N\times M$ grid of ASCII characters. The top-right tile must be a $\texttt{*}$. 
Every other character in the grid must be either $\texttt{U}$, $\texttt{R}$, $\texttt{D}$, or $\texttt{L}$, representing the orientation of the conveyor belt on that grid tile.

**This problem is whitespace-sensitive.** You *must* separate each mob grinder design with exactly one empty line (containing just a newline character). You *must not* print an empty line, or any other extraneous output, after the last mob grinder design (though the last line of output must be terminated with a newline). Please see the Sample Output for examples of how to correctly format your mob grinder designs.
## 样例

### 样例输入 #1
```
2
4 3 5 3 1 2
1 2 0 1 0 0
```
### 样例输出 #1
```
RR*
URU
UDU
ULL

R*
```
### 样例输入 #2
```
3
3 3 0 0 0 8
2 2 0 2 0 1
1 1 0 0 0 0
```
### 样例输出 #2
```
impossible

impossible

*
```


---

---
title: "[NAC 2025] Ornaments on a Tree"
layout: "post"
diff: 提高+/省选-
pid: P12627
tag: ['贪心', '2025', 'ICPC', 'NAC']
---
# [NAC 2025] Ornaments on a Tree
## 题目描述

You're helping your friend decorate their Christmas tree! Funnily enough, the places to put your ornaments on their Christmas tree can be represented
by a (graph-theoretic) tree with nodes labeled $1$ to $N$, with node $1$ being the root of the tree and other nodes numbered arbitrarily. You have an infinite supply of ornaments of every non-negative integer weight
(including $0$), and you must place exactly one ornament on each node of the tree.

However, your friend has some restrictions on how they want their tree decorated. First, they have strong opinions about which ornament must go on some of the tree nodes; you are only allowed to choose decorations on the other nodes. Second, each region of their tree can support only so much weight: if the sum of the weights of the ornaments on a node and all of its immediate children exceeds a constant $K$, the whole tree will come crashing down!

Your friend wants to know the largest possible total weight of ornaments on their tree, given the above restrictions. Can you help them find out?
## 输入格式

The first line of input has two space-separated integers $N$ and $K$ ($1 \leq N \leq 2 \cdot 10^5, 0 \leq K \leq 10^9$), the number of nodes in the tree and the weight constant, respectively.

The next line contains $N$ space-separated integers. The $i^\text{th}$ integer (starting at $i=1$) is either $-1$ or a non-negative integer. If it is $-1$, you are free to choose any ornament for node $i$. If it is a non-negative integer $w_i$ ($0 \leq w_i \leq 10^9$), your friend insists you place an ornament with weight $w_i$  on node $i$.

The next $N-1$ lines each contain two space-separated integers $a$ and $b$ ($1 \leq a, b \leq N$), indicating that nodes $a$ and $b$ are connected by an edge. The input graph is guaranteed to be a tree: there is a unique path of edges between every pair of nodes in the graph.
## 输出格式

If it is impossible to place ornaments on the tree in a way that satisfies all of the constraints described above, print $-1$.
Otherwise, print the maximum possible total weight of the ornaments on the tree, subject to the constraints.
## 样例

### 样例输入 #1
```
5 10
-1 2 3 -1 -1
1 2
1 3
2 4
2 5
```
### 样例输出 #1
```
18
```
### 样例输入 #2
```
1 5
-1
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
2 5
5 5
1 2
```
### 样例输出 #3
```
-1
```


---

---
title: "[NAC 2025] Solar Farm"
layout: "post"
diff: 提高+/省选-
pid: P12631
tag: ['2025', 'ICPC', 'NAC']
---
# [NAC 2025] Solar Farm
## 题目描述

You are building a new solar farm.  The area in which you are allowed to build
is a circular field of radius $r$, and the solar panels each take up a
rectangular space of size $w \times h$.  You must place all the panels in the same
orientation of your choice in a single rectangular array (so that all of the panels combined
exactly form a single rectangle).  What is the maximum number of panels that you can fit in this farm?
## 输入格式

The first line of input contains a single integer $T$ ($1\leq T \leq 1\,000$).
This is the number of test cases.

The next $T$ lines of input each represent one test case and consist of three space-separated integers $r$, $w$, and $h$
($1 \leq r, w, h \leq 10^9$): the radius of the field, the width of
each solar panel, and the height of each solar panel, respectively.
## 输出格式

For each test case, print a line with a single integer: the maximum
number of solar panels that can be placed in a solar farm within the circular
field.
## 样例

### 样例输入 #1
```
3
5 4 3
2 2 2
8 1 5
```
### 样例输出 #1
```
4
1
24
```
### 样例输入 #2
```
2
500000003 1 600000010
511374200 637192506 100000000
```
### 样例输出 #2
```
799999999
7
```
## 提示

The diagram below illustrates one optimal layout of solar panels for each of the three test cases in Sample Input 1 (from left to right).

![](https://cdn.luogu.com.cn/upload/image_hosting/l3d8fv6t.png)


---

---
title: "[NERC 2022] Amazing Trick"
layout: "post"
diff: 提高+/省选-
pid: P12790
tag: ['模拟', '图论', '2022', 'Special Judge', '置换', '随机化', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2022] Amazing Trick
## 题目描述

Alice is a magician and she creates a new trick. She has $n$ cards with different numbers from $1$ to $n$ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $i$-th card from the left has the number $a_i$ on it. 

Then Alice picks two permutations $p$ and $q$. There is a restriction on $p$ and $q$ --- $\textbf{permutations can't have fixed points}$. Which means $\forall i: p_i \ne i\ and\ q_i \ne i$.

After permutations are chosen, Alice shuffles the cards according to them. Now the $i$-th card from the left is the card $a[p[q[i]]$. The trick is considered successful if $i$-th card from the left has the number $i$ on it after the shuffles.

Help Alice pick the permutations $p$ and $q$ or say it is not possible for the specific starting permutation $a$. 
## 输入格式

The first line of the input contains the number of tests $t$ ($1 \leq t \leq 10^5$). 

Each test is described in two lines. The first line contains one integer $n$ --- the number of cards ($1 \leq n \leq 10^5$). The second line contains $n$ integers $a_i$ --- the initial permutation of the cards ($1 \leq a_i \leq n$; $\forall i \neq j: a_i \neq a_j$). 

It is guaranteed that the sum of $n$ over all tests does not exceed $10^5$.
## 输出格式

Print the answer for each test case in the same order the cases appear in the input.

For each test case, print $\tt{Impossible}$ in a single line, if no solution exists.

Otherwise, print $\tt{Possible}$ in the first line, and in the following two lines print permutations $p$ and $q$.
## 样例

### 样例输入 #1
```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3
```
### 样例输出 #1
```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2
```


---

---
title: "[NERC 2022] BinCoin"
layout: "post"
diff: 提高+/省选-
pid: P12791
tag: ['2022', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] BinCoin
## 题目描述

There are $n$ employees in the BinCoin company numbered from $1$ to $n$. The subordination structure in this company is a rooted tree. In other words:
- There is one CEO in the company --- the main boss.
- Each other employee has exactly one direct superior.
- There are no cycles in the subordination structure.
  
Moreover, due to the inexplicable love of the CEO of BinCoin for all the binary stuff, the subordination structure in the company is a $\textbf{binary}$ rooted tree. That means each employee is directly superior to exactly zero or two other employees.

In the CEO's opinion, working in this company is almost as dangerous as in mines. So, employees should sign the waiver of claims sometimes. This process happens in the following way. Initially, CEO takes the journal, then recursively the following procedure is performed:

- If an employee that holds the journal does not have any subordinates, they sign the waiver in the journal and give it back to their superior. The procedure stops if that was the CEO, who has no superior.
- Otherwise
  - they choose one of two of their direct subordinates uniformly at random and give the journal to one of them;
  - when they get the journal back, they sign it;
  - and then they give it to another direct subordinate;
  - when they get it back again, they give it back to their superior. The procedure stops if that was the CEO, who has no superior.

All random choices are independent.

One day, the CEO realized that they could not remember the subordination tree. Fortunately, they have the journal with $k$ records. Each record is a sequence of employees in the order they've signed in a journal.

Help CEO restore the subordination tree.
## 输入格式

The first line contains two integers $n$ and $k$ --- the number of employees and the number of records in the journal ($1 \le n \le 999$; $50 \le k \le 100$).

Each of the next $k$ lines contains a permutation of integers from $1$ to $n$ --- the order of employees in the corresponding record.

It is guaranteed that the input was obtained as described in the statement with a real random choice.
## 输出格式

Output $n$ integers $p_i$. If $i$ is a CEO, then $p_i$ should be $-1$. Otherwise, $p_i$ should be the index of the direct superior of $i$-th employee.

Your output should correspond to a binary rooted tree. If there are several trees satisfying the input, you can output any one of them.
## 样例

### 样例输入 #1
```
3 50
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    1 2 3    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    1 2 3    3 2 1
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    1 2 3    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    1 2 3
1 2 3    1 2 3    3 2 1    1 2 3
3 2 1    3 2 1    1 2 3    3 2 1
1 2 3    3 2 1    3 2 1    1 2 3
1 2 3    3 2 1    1 2 3    3 2 1
3 2 1    3 2 1    1 2 3    1 2 3
3 2 1    3 2 1    
```
### 样例输出 #1
```
2 -1 2
```
### 样例输入 #2
```
5 60
2 4 3 5 1    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 3 4 2    1 5 3 4 2
1 5 3 4 2    1 5 3 4 2    1 5 3 4 2
3 4 2 5 1    2 4 3 5 1    1 5 2 4 3
3 4 2 5 1    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    3 4 2 5 1    1 5 3 4 2
1 5 2 4 3    1 5 3 4 2    1 5 2 4 3
2 4 3 5 1    2 4 3 5 1    2 4 3 5 1
2 4 3 5 1    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    1 5 2 4 3    3 4 2 5 1
1 5 3 4 2    3 4 2 5 1    3 4 2 5 1
1 5 2 4 3    2 4 3 5 1    1 5 2 4 3
1 5 3 4 2    2 4 3 5 1    2 4 3 5 1
1 5 2 4 3    1 5 2 4 3    1 5 2 4 3
1 5 2 4 3    1 5 2 4 3    3 4 2 5 1
3 4 2 5 1    3 4 2 5 1    1 5 2 4 3
1 5 3 4 2    1 5 3 4 2    2 4 3 5 1
3 4 2 5 1    1 5 2 4 3    3 4 2 5 1
```
### 样例输出 #2
```
5 4 4 5 -1
```
## 提示

In order to fit on the page, several consecutive lines in the examples were joined into one. The real inputs follow the input description.


---

---
title: "[NERC 2021] Even Split"
layout: "post"
diff: 提高+/省选-
pid: P12818
tag: ['二分', '2021', 'Special Judge', '构造', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Even Split
## 题目描述

A revolution has recently happened in Segmentland. The new government is committed to equality, and they hired you to help with land redistribution in the country.

Segmentland is a segment of length $l$ kilometers, with the capital in one of its ends. There are $n$ citizens in Segmentland, the home of $i$-th citizen is located at the point $a_i$ kilometers from the capital. No two homes are located at the same point. Each citizen should receive a segment of positive length with ends at integer distances from the capital that contains her home. The union of these segments should be the whole of Segmentland, and they should not have common points besides their ends. To ensure equality, the difference between the lengths of the longest and the shortest segments should be as small as possible.
## 输入格式

The first line of the input contains two integers $l$ and $n$ ($2 \leq l \leq 10^9; 1 \leq n \leq 10^5$).

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($0 < a_1 < a_2 < \dots < a_n < l$).
## 输出格式

Output $n$ pairs of numbers $s_i, f_i$ ($0 \leq s_i < f_i \leq l$), one pair per line. The pair on $i$-th line denotes the~ends of the $[s_i, f_i]$ segment that $i$-th citizen receives.

If there are many possible arrangements with the same difference between the lengths of the longest and the shortest segments, you can output any of them.
## 样例

### 样例输入 #1
```
6 3
1 3 5
```
### 样例输出 #1
```
0 2
2 4
4 6
```
### 样例输入 #2
```
10 2
1 2
```
### 样例输出 #2
```
0 2
2 10
```
## 提示

In the first example, it is possible to make all segments equal. $\textit{Viva la revolucion!}$

![](https://cdn.luogu.com.cn/upload/image_hosting/3wu9r2og.png)

In the second example, citizens live close to the capital, so the length of the shortest segment is 2 and the length of the longest segment is 8.

![](https://cdn.luogu.com.cn/upload/image_hosting/j6sev5h6.png)


---

---
title: "[NERC 2021] Fancy Stack"
layout: "post"
diff: 提高+/省选-
pid: P12819
tag: ['动态规划 DP', '2021', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Fancy Stack
## 题目描述

Little Fiona has a collection of $n$ blocks of various sizes $a_1, a_2, \ldots, a_n$, where $n$ is even. Some of the blocks can be equal in size. She would like to put all these blocks one onto another to form a $\textit{fancy}$ stack.

Let $b_1, b_2, \ldots, b_n$ be the sizes of blocks in the stack from top to bottom. Since Fiona is using all her blocks, $b_1, b_2, \ldots, b_n$ must be a permutation of $a_1, a_2, \ldots, a_n$. Fiona thinks the stack is $\textit{fancy}$ if both of the following conditions are satisfied:
- The second block is strictly bigger than the first one, and then each block is alternately strictly smaller or strictly bigger than the previous one. Formally, $b_1 < b_2 > b_3 < b_4 > \ldots > b_{n-1} < b_n$.
- The sizes of the blocks on even positions are strictly increasing. Formally, $b_2 < b_4 < b_6 < \ldots < b_n$ (remember that $n$ is even).

![](https://cdn.luogu.com.cn/upload/image_hosting/16lldnv3.png)

Two stacks are considered different if their corresponding sequences $b_1, b_2, \ldots, b_n$ differ in at least one position.

Fiona wants to know how many different fancy stacks she can build with all of her blocks. Since large numbers scare Fiona, find this number modulo $998\,244\,353$.
## 输入格式

Each input contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2500$). Description of the test cases follows.

The first line of each test case contains a single integer $n$ --- the number of blocks at Fiona's disposal ($2 \le n \le 5000$; $n$ is even). The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ --- the sizes of the blocks in non-decreasing order ($1 \le a_1 \le a_2 \le \dotsb \le a_n \le n$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $5000$.
## 输出格式

For each test case, print the number of ways to build a fancy stack, modulo $998\,244\,353$.
## 样例

### 样例输入 #1
```
2
4
1 2 3 4
8
1 1 2 3 4 4 6 7
```
### 样例输出 #1
```
2
4
```


---

---
title: "[NERC 2021] Job Lookup"
layout: "post"
diff: 提高+/省选-
pid: P12823
tag: ['2021', 'Special Judge', '区间 DP', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Job Lookup
## 题目描述

Julia's $n$ friends want to organize a startup in a new country they moved to. They assigned each other numbers from 1 to $n$ according to the jobs they have, from the most front-end tasks to the most back-end ones. They also estimated a matrix $c$, where $c_{ij} = c_{ji}$ is the average number of messages per month between people doing jobs $i$ and $j$.

Now they want to make a hierarchy tree. It will be a $\textbf{binary tree}$ with each node containing one member of the team. Some member will be selected as a leader of the team and will be contained in the root node. In order for the leader to be able to easily reach any subordinate, for each node $v$ of the tree, the following should apply: all members in its left subtree must have smaller numbers than $v$, and all members in its right subtree must 
have larger numbers than $v$.

After the hierarchy tree is settled, people doing jobs $i$ and $j$ will be communicating via the shortest path in the tree between their nodes. Let's denote the length of this path as $d_{ij}$. Thus, the cost of their communication is $c_{ij} \cdot d_{ij}$.

Your task is to find a hierarchy tree that minimizes the total cost of communication over all pairs: $\sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij}$.
## 输入格式

The first line contains an integer $n$ ($1 \le n \le 200$) -- the number of team members organizing a startup.

The next $n$ lines contain $n$ integers each, $j$-th number in $i$-th line is $c_{ij}$ ---
the estimated number of messages per month between team members $i$ and $j$ ($0 \le c_{ij} \le 10^9; c_{ij} = c_{ji}; c_{ii} = 0$).
## 输出格式

Output a description of a hierarchy tree that minimizes the total cost of communication. To do so, for each team member from 1 to $n$ output the number of the member in its parent node, or 0 for the leader. If there are many optimal trees, output a description of any one of them.

## 样例

### 样例输入 #1
```
4
0 566 1 0
566 0 239 30
1 239 0 1
0 30 1 0
```
### 样例输出 #1
```
2 4 2 0
```
## 提示

The minimal possible total cost is $566 \cdot 1+239 \cdot 1+30 \cdot 1+1 \cdot 2+1 \cdot 2=839$:

![](https://cdn.luogu.com.cn/upload/image_hosting/isxizhg5.png)


---

---
title: "[NERC 2020] Digits"
layout: "post"
diff: 提高+/省选-
pid: P12903
tag: ['动态规划 DP', '数学', '2020', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Digits
## 题目描述

Diana loves playing with numbers. She's got $n$ cards with positive integer numbers $a_i$ written on them. She spends her free time multiplying the numbers on the cards. She picks a 
non-empty subset of the cards and multiplies all the numbers $a_i$ written on them.

Diana is happy when the product of the numbers ends with her favorite digit $d$. Now she is curious what cards she should pick so that the product of the numbers on them is the largest possible and the last decimal digit of the product is $d$. Please, help her.
## 输入格式

The first line contains the integers $n$ and $d$ ($1\le n\le 10^5$, $0\le d\le 9$). The second line contains $n$ integers $a_i$ ($1\le a_i\le 1000$). 
## 输出格式

On the first line, print the number of chosen cards $k$ ($1\le k\le n$). On the next line, print the numbers written on the chosen cards in any order. 

If it is impossible to choose a subset of cards with the product that ends with the digit $d$, print the single line with $-1$.
## 样例

### 样例输入 #1
```
6 4
4 11 8 2 1 13
```
### 样例输出 #1
```
5
1 2 4 11 13
```
### 样例输入 #2
```
3 1
2 4 6
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
5 7
1 3 1 5 3
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
6 3
8 9 4 17 11 5
```
### 样例输出 #4
```
3
9 11 17
```
### 样例输入 #5
```
5 6
2 2 2 2 2
```
### 样例输出 #5
```
4
2 2 2 2
```
## 提示

In the first example, $1 \times 2 \times 4 \times 11 \times 13 = 1144$, which is the largest product that ends with the digit 4. The same set of cards without the number 1 is also a valid answer, as well as a set of 8, 11, and 13 with or without 1 that also has the product of 1144.

In the second example, all the numbers on the cards are even and their product cannot end with an odd digit 1.

In the third example, the only possible products are 1, 3, 5, 9, 15, and 45, none of which end with the digit 7.

In the fourth example, $9 \times 11 \times 17 = 1683$, which ends with the digit 3. 

In the fifth example, $2 \times 2 \times 2 \times 2 = 16$, which ends with the digit 6.


---

---
title: "[NWRRC 2023] Based Zeros"
layout: "post"
diff: 提高+/省选-
pid: P13582
tag: ['数学', '2023', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Based Zeros
## 题目描述

Barbara has always known how to represent integers in the decimal numeral system (base ten), using digits $0, 1, 2, \ldots, 9$. Recently she has learned that for any integer base $b \ge 2$, she can also represent integers in base $b$, using symbols with values from $0$ to $b-1$, inclusive, as digits.

Barbara's favorite digit is $0$. Luckily, it looks the same in all bases.

Today Barbara is playing with a positive integer $n$. Now she wonders: in what bases does the representation of $n$ contain the biggest number of zeros? Help her to find all such bases.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 1000$). The description of the test cases follows.

The only line of each test case contains a single integer $n$ ($2 \le n \le 10^{18}$).
## 输出格式

For each test case, in the first line, print two integers $k$ and $m$, denoting the maximum number of zeros the representation of $n$ can have in any integer base, and the number of such bases, respectively.

In the second line, print $m$ integers $b_1, b_2, \ldots, b_m$, denoting all such bases in increasing order ($2 \le b_1 < b_2 < \cdots < b_m \le n$).
## 样例

### 样例输入 #1
```
3
11
1007
239
```
### 样例输出 #1
```
1 3
2 3 11
2 2
3 10
1 4
2 6 15 239
```
## 提示

Here are the representations with the maximum number of zeros for the example test cases:

- $11   = \mathtt{1011}_2     = \mathtt{102}_3    = \mathtt{10}_{11}$ (one zero);
- $1007 = \mathtt{1101022}_3  = \mathtt{1007}_{10}$ (two zeros);
- $239  = \mathtt{11101111}_2 = \mathtt{1035}_6 = \mathtt{10E}_{15} = \mathtt{10}_{239}$ (one zero).

In the $239 = \mathtt{10E}_{15}$ representation, $\mathtt{E}$ stands for a digit with the value of $14$.


---

---
title: "[NWRRC 2023] Intersegment Activation"
layout: "post"
diff: 提高+/省选-
pid: P13589
tag: ['2023', '交互题', 'Special Judge', '枚举', '构造', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Intersegment Activation
## 题目描述

This is an interactive problem.

There is an array of $n$ cells, numbered from $1$ to $n$. For each pair of integers $(i, j)$, where $1 \le i \le j \le n$, there is a barrier covering all cells from $i$ to $j$, inclusive. Each barrier is either $\textit{active}$ or $\textit{inactive}$. A cell is $\textit{visible}$ if there are no active barriers that cover it. Otherwise, the cell is $\textit{invisible}$.

The state of each barrier is unknown to you. All you can observe is the number of visible cells. But you can flip the state of any barrier: if it's active, it turns inactive, and the other way around. Your task is to make all barriers inactive, so that all cells become visible.

### Interaction Protocol

First, read an integer $n$, denoting the number of cells ($1 \le n \le 10$).

The following interaction will proceed in rounds. Your program should start each round by reading an integer $k$, denoting the number of currently visible cells ($0 \le k \le n$).

- If $k = n$, then the task is done and your program must exit. 
- If $k < n$, you can flip the state of any barrier. On a separate line, print two integers $i$ and $j$ to flip the state of the $(i, j)$ barrier ($1 \le i \le j \le n$). After your query, the next round begins, and your program should read a new value of $k$.

Your solution must make all cells visible using at most $2500$ flips. In the beginning, not all cells are visible ($k < n$ in the first round).

The interactor is not adaptive: in every test, the state of all barriers is chosen before the program execution.
## 输入格式

See Interaction Protocol.
## 输出格式

See Interaction Protocol.
## 样例

### 样例输入 #1
```
3
0

0

1

2

3
```
### 样例输出 #1
```


2 2

2 3

1 2

2 2
```
## 提示

Initial State.

![](https://cdn.luogu.com.cn/upload/image_hosting/f8uw3js6.png)

In the example, initially, only two barriers, $(1, 2)$ and $(2, 3)$, are active. These two barriers cover all three cells, so $k$ is equal to 0 in the first round.

- After flipping the $(2, 2)$ barrier, there are now three active barriers, and still $k = 0$ visible cells.
- After flipping the $(1, 2)$ barrier, cell $1$ becomes visible, so now there is $k = 1$ visible cell.
- After flipping the $(2, 3)$ barrier, cell $3$ also becomes visible. The only invisible cell now is $2$, covered by the only active barrier, $(2, 2)$, and there are $k = 2$ visible cells.
- After flipping the $(2, 2)$ barrier, all barriers are now inactive, and all cells are visible. After reading $k = 3$, the program terminates.


---

---
title: "[ICPC 2025 APC] Bit Counting Sequence"
layout: "post"
diff: 提高+/省选-
pid: P13617
tag: ['2024', '位运算', '构造', 'ICPC']
---
# [ICPC 2025 APC] Bit Counting Sequence
## 题目描述

对于一个非负整数 $x$，令 $p(x)$ 为 $x$ 的二进制表示中 1 的个数。例如，$p(26)=3$，因为 $26=(11010)_2$。

给定一个包含 $n$ 个整数的序列 $(a_1, a_2, ..., a_n)$。你的任务是判断是否存在一个非负整数 $x$，使得序列 $(p(x), p(x+1), ..., p(x+n-1))$ 与 $(a_1, a_2, ..., a_n)$ 相等。此外，如果存在，你需要计算满足条件的最小的 $x$。
## 输入格式

输入的第一行包含一个整数 $t (1 \le t \le 1000)$，代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例的格式如下。

第一行包含一个整数 $n (1 \le n \le 500,000)$。
第二行包含 $n$ 个整数 $a_1, a_2, ..., a_n(0 \le a_i \le 60)$。

在单个输入文件中，所有测试用例的 $n$ 的总和不超过 $500,000$。
## 输出格式

对于每个测试用例，输出满足上述条件的最小非负整数 $x$。如果不存在这样的 $x$，则输出 $-1$。
## 样例

### 样例输入 #1
```
4
5
3 3 4 1 2
3
2 1 2
2
60 60
2
8 0
```
### 样例输出 #1
```
13
3
2305843009213693949
-1
```
## 提示

**样例解释 #1**

对于第一个测试用例，$x=13$ 满足上述条件，因为 $(p(13), p(14), p(15), p(16), p(17))=(3, 3, 4, 1, 2)$。可以证明，不存在比 $13$ 更小的非负整数满足上述条件。

翻译由 Gemini 2.5 Pro 完成。


---

---
title: "[ICPC 2025 APC] Duplicates"
layout: "post"
diff: 提高+/省选-
pid: P13619
tag: ['2024', '图论建模', '二分图', '构造', 'ICPC']
---
# [ICPC 2025 APC] Duplicates
## 题目描述

我们称一个数字序列**含有重复元素**，如果序列中存在出现一次以上的元素。形式化地讲，一个序列 $(a_1, \dots, a_n)$ 含有重复元素，如果存在两个不等的下标 $i$ 和 $j$ 使得 $a_i = a_j$。

给定一个 $n \times n$ 的矩阵 $X$。$X$ 中的每个元素都是一个 $1$ 到 $n$ 之间（含两端）的整数。你可以将 $X$ 中零个或多个元素修改为 $1$ 到 $n$ 之间（含两端）的任意整数。不同的元素可以修改为不同的整数。

你的任务是通过修改 $X$ 中的元素，使得以下所有条件都成立：

* 对于每一行 $i$，序列 $(X_{i1}, X_{i2}, \dots, X_{in})$ 含有重复元素。
* 对于每一列 $j$，序列 $(X_{1j}, X_{2j}, \dots, X_{nj})$ 含有重复元素。

你需要计算达成此目标所需的**最小**修改次数。同时，找出一种可行的修改方案。对于每次修改，你需要指明修改的是哪个元素以及它的新值。请注意，当给定的矩阵 $X$ 已经满足上述条件时，所需的最小修改次数可以为零。
## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$），代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例的格式如下。

一个测试用例的第一行包含一个整数 $n$（$3 \le n \le 100$）。
接下来的 $n$ 行，每行包含 $n$ 个整数。第 $i$ 行的第 $j$ 个整数代表 $X_{ij}$（$1 \le X_{ij} \le n$）。

在单个输入文件中，所有测试用例的 $n^2$ 的总和不超过 $10,000$。
## 输出格式

对于每个测试用例，按以下格式输出一组修改方案。

第一行输出一个整数 $m$，代表需要修改的元素的最小数量。
在接下来的 $m$ 行中，每行输出三个整数 $i, j, v$。这代表一次修改，即将元素 $X_{ij}$ 的值修改为 $v$。这三个整数都必须在 $1$ 和 $n$ 之间（含两端）。

如果存在多种解法，你可以输出其中任意一种。

## 样例

### 样例输入 #1
```
5
4
3 2 1 1
2 1 3 4
1 3 3 1
4 4 4 2
3
1 3 1
2 1 3
3 2 2
5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
3
1 1 2
2 2 1
2 3 2
3
1 1 3
3 2 1
3 1 3
```
### 样例输出 #1
```
2
2 1 1
4 2 3
3
2 1 3
2 2 3
3 3 3
0
1
1 2 2
1
2 1 1
```
## 提示

**样例解释 #1**

在第一个测试用例中，修改后的矩阵如下所示。

$$
\begin{bmatrix}
3 & 2 & 1 & 1 \\
1 & 1 & 3 & 4 \\
1 & 3 & 3 & 1 \\
4 & 3 & 4 & 2 \\
\end{bmatrix}
$$


---

---
title: "[CERC 2020] Art Transaction"
layout: "post"
diff: 提高+/省选-
pid: P13651
tag: ['模拟', '2020', 'ICPC', 'CERC']
---
# [CERC 2020] Art Transaction
## 题目描述

The largest picture stolen by the gangsters from the State Gallery is to be evaluated by an expert before it is sold on the black market. The composition of the picture clearly follows mainstream tendencies in contemporary AI art. The picture can be viewed as a grid of square cells where each cell is either empty or non-empty. A non-empty cell contains exactly one of these objects: a sun, a house, a chupacabra, a left slope, a right slope, a bird, a drake, or a grill. Two cells are adjacent if they share an edge in the grid. A connection between two cells is a sequence of cells which contains both given cells and in which each two consecutive cells are adjacent in the picture. An area is a set of cells. It is connected if there is a connection between any two cells in the area.

The value of the picture is the total of all values generated by all rules listed below.

- Suns:\
A non-empty cell, not containing a sun, is illuminated by a sun if there is no other object on a straight line between the cell and another cell with a sun. The straight line may be horizontal, vertical or diagonal (both diagonal directions apply). When a cell is illuminated by multiple suns it is still counted only once. A sun cannot illuminate itself. Each illuminated cell generates $100$ .

- Biggest bird:\
A drake is a bird. A flock of birds is maximal connected area of cells each of which contains a bird. The width of a flock is the length of a maximum contiguous sequence of cells on one line in a flock. A flock of birds generates $500 \cdot (\text{width of the flock})$.

- Flock perimeter:\
Each flock of birds (see previous rule) generates value $60 \cdot (\text{flock perimeter})$. Flock perimeter is the total number of edges each of which separates a flock cell from a cell which does not contain a bird or from the outside of the picture.

- House view up:\
When an empty cell is located above a cell containing a house, it is in the same column, and there is no non-empty field between the empty cell and the house, the empty cell generates $10$.

- $3 \times 3$ blocks:\
Each unique $3 \times 3$ block (possibly overlapping) generates $1$.

- Animals I:\
Each edge between a cell with an animal and an empty cell generates $15$.

- Freedom:\
Cell X is a freedom cell if it is either adjacent to the picture border or there is a connection between a cell adjacent to the picture border and a cell adjacent to X and the connection contains only empty cells. Each non-empty freedom cell generates $7$.

- Chupacabra:\
A drake is a bird. Each bird which can be reached by a chupacabra performing one chess knight move in the grid generates $200$

- Peaks:\
A pair of adjacent cells with characters `/` (left slope) and `\` (right slope, in this order) on one line is a peak. Peak summit is an imaginary point in the middle of the segment connecting the uppermost points of both symbols in the peak. Peak value is equal to the maximum Manhattan distance from the peak summit to the summit of another peak in the grid. Note that peak value is an integer. Each peak P generates $50 \cdot (P \text{ value})$ when there are at least two peaks in the picture. Otherwise, a single peak in the picture generates $0$.

- Drake/grill:\
Each cell with a drake and with at least one adjacent cell with a grill generates $500$ .

- Minimum frequency:\
Frequency of an object X is the number of the objects (including X) of the same type as X in the entire picture. Each single object which frequency is minimum among all objects in the picture generates $10$.

- Empty fields:\
Each empty field generates $1$.

- Animals II:\
All animals in the picture together generate single value $1 \cdot (\text{number of chupacabras}) \cdot (\text{number of birds which are not drakes}) \cdot (\text{number of drakes})$.

- House view down:\
When an empty field is located above a house, is in the same column, and there is no non-empty field between the empty field and the house, the empty field generates $5$.

- Grill/drake:\
Each cell with a grill and with at least one adjacent cell with a drake generates $50$.

- Houses and grills:\
Houses and grills in the picture generate $3 \cdot \min \{ \text{number of all houses}, \text{number of all grills} \}$.
## 输入格式

The first input line contains one integer $N$ ($1 \leq N \leq 50$), the number of the rows and the columns in the picture. Next, there are $N$ lines, each specifies one line in the picture. One character on the line represents one cell and its contents.

The interpretation of particular characters in the picture representation follows:
empty cell ` ` (space), sun `*`, house `^`, chupacabra `!`, left slope `/`, right slope `\`, bird `v`, drake `D`, grill `G`.
## 输出格式

Print one integer, the value of the input picture.
## 样例

### 样例输入 #1
```
9
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
 *^!/\vDG
```
### 样例输出 #1
```
12672
```
### 样例输入 #2
```
3
!  
  v
 D 
```
### 样例输出 #2
```
2059
```


---

---
title: "[CERC 2020] Pizzo Collectors"
layout: "post"
diff: 提高+/省选-
pid: P13653
tag: ['2020', 'ICPC', 'CERC']
---
# [CERC 2020] Pizzo Collectors
## 题目描述

Lavish Circle (LC) is the fashionable circular avenue in the residential area of the town. Houses on LC are exceptionally expensive and some of them are currently empty. LC is under heavy control of the town mafia who wants to populate the empty houses with new owners loyal to the mafia. When LC is completely populated, each house owner will live in one house on LC. LC is a circular avenue of houses numbered from $1$ to $N$, that is for $i < N$, $i$-th and $i+1$-th houses are neighboring and also houses $N$ and $1$ are neighboring.

The house owners, both the existing ones and the new ones, fall into few categories according to the sum they can pay the mafia monthly for protecting them. The money is called pizzo and it is typically collected by a person called a pizzo collector (PC). The mafia employs a group of them.

The job of a PC is to go around entire LC exactly once in a month and collect pizzo from the selected houses on the journey. All selected houses on a journey of a PC must have owners of the same pizzo category. The journey must also start and end at the same house, it is a check PC completed the journey correctly. The pizzo is collected from this house only once, at the beginning or at the end of the journey. During his journey, a PC always moves forward by a fixed number of houses, until the PC arrives again to the starting house. That is, the number of houses a PC skips on each move is a non-negative integer $d$, which remains constant during the entire journey of this PC. It must hold that $(d+1)$ divides $N$ evenly.

The mafia wants to employ as many PCs as possible. Of course, employing a number of PCs means that some owners quite probably have to pay pizzo more than once in a month, but the mafia does not care... Unfortunately, there is a complication. PCs are peaceful citizens and they do not tend to shoot at each other under normal conditions. However, when two PCs find out that at their respective collection journeys they visit the same set of houses, and it does not matter in which order they visit the houses, the collectors tend to shoot each other and thus attract the police, which is a behavior the mafia wants to avoid at any cost. So, no two collectors who may shoot each other can be employed simultaneously.

The total value of all collected pizzo depends also on the categories of the owners of the newly populated houses. The mafia decides on the category of each new house owner. Obviously the mafia wants to maximize their income. You have been hired as an analyst to find the maximum possible total value of all collected pizzo in one month, when LC gets completely and suitably populated. The mafia is going to decide on the pizzo category of each new house owner based on your recommendations. The number of houses on LC is a non-negative integer power of a prime number.

## 输入格式

The first line contains integer $N$ ($1 \leq N \leq 10^5$), a non-negative integer power of some prime number $p$. The second row contains string $S$ of length $N$, which consists of only capital letters of English alphabet and the character "?". The characters of the string represent the houses on LC in the order they appear on LC. The "?" character represents a currently empty house, each of the other characters represent the pizzo category of the house owner.

The next line contains integer $k$ ($1 \leq k \leq 26$), the number of different pizzo categories. Each of the next $k$ lines contains an integer pair $c_i$ $v_i$, where $c_i$ is a capital English character and $1 \leq v_i \leq 10^6$ is the money value which is paid by a house owner of pizzo category $c_i$ in one visit of a PC to the house.

It is guaranteed that for every category that appears in $S$, there is a pair $c_i$ and $v_i$ which defines its money value which is paid on the PC's visit.

## 输出格式

Print the maximum possible total value of all collected pizzo in one month, when LC is completely populated.
## 样例

### 样例输入 #1
```
4
A?A?
2
A 10
B 25
```
### 样例输出 #1
```
140
```
### 样例输入 #2
```
4
A??A
2
A 10
B 25
```
### 样例输出 #2
```
120
```


---

---
title: "[CERC 2020] Pickpockets"
layout: "post"
diff: 提高+/省选-
pid: P13658
tag: ['2020', 'ICPC', '状压 DP', 'CERC']
---
# [CERC 2020] Pickpockets
## 题目描述

The police station stands at the very top of the Jewellery Stores lane, a location vitally important for the pickpocket business in the town. The policemen start their daily patrol at the top end of the lane, progress slowly down and then return back to the top, seldom reaching the bottom end of the lane during the day. There are many regularities in the police habits, and therefore Big Pickpocket Boss (BPB) can make a smart plan for the holidays. The stores on the lane are labeled by successive integers, beginning from 1, from the bottom of the lane to its top. For each day of holidays, BPB can guarantee some number of stores, from the beginning up to a particular label, to be clean from the police unwelcome scrutiny. Teams of pickpockets will do the job for BPB. There are many teams available, each of them can operate on a single store for a number of consecutive days. Not necessarily all teams must be employed.

BPB is a formidable boss, his rules must be obeyed to the letter:

- There will be exactly one team operating in each store on any day the store is clean.
- When a team starts operating in a store they will operate there for some number of consecutive days.
- When a store will not be clean on a particular day, no team will operate in the store on that day.
- No team will operate in two or more stores.
- No team will operate twice or more times during the holidays.
- No team will operate on any day before or after the holidays.

It is known that each team can generate their specific minimum income for BPB during their entire operation. BPB knows he has to maximize his minimum total income. He wants that figure from you, today, by 3 PM and not later. Do not even try to disappoint him.

## 输入格式

The first line contains two integers $H$ and $T$ ($1 \leq H \leq 10^5$, $1 \leq T \leq 16$), the number of days in the holidays and the number of teams available. The second line contains $H$ integers $C_k$ ($0 \leq C_k \leq 10^5$, $1 \leq k \leq H$), the highest labels of a clean store on the $k$-th day of holidays. Label 0 means there is no clean store on the $k$-th day of holidays. Each of the next $T$ lines contains two integers $D_t$ and $I_t$ ($1 \leq D_t \leq H$, $0 \leq I_t \leq 10^6$, $1 \leq t \leq T$), the duration of the operation of team $t$ in days, and the minimum income the team generates.

## 输出格式

Print the maximum value of the minimum total income the teams can generate when appropriately scheduled. Print $0$ when the conditions of BPB cannot be met.
## 样例

### 样例输入 #1
```
3 4
2 1 2
3 2
1 1
1 2
1 3
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
4 7
2 2 1 1
3 1
1 1
1 4
1 1
2 4
2 2
2 1
```
### 样例输出 #2
```
11
```


---

---
title: "[GCPC 2023] Freestyle Masonry"
layout: "post"
diff: 提高+/省选-
pid: P13671
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Freestyle Masonry
## 题目描述

Fred got a simple task, he just has to build a $w\times h$ wall.

![](https://cdn.luogu.com.cn/upload/image_hosting/jdfpt5uu.png)

:::align{center}
An interesting brick layout, photo by [Bobo Boom](https://commons.wikimedia.org/wiki/File:Intricate_patterns_in_brick-laying_(29947248771).jpg)
:::

To make this even easier, he was provided with enough $2\times1$ bricks and also a few $1\times1$ bricks to complete the wall.
Knowing that this task should not be too hard, Fred went to work and started building the wall without thinking too much about the design.
Only when he ran out of $1\times1$ bricks, Fred noticed that this might have been a bad idea...

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/f5wolnfs.png)

Figure F.1: Visualization of Sample Input 2. The red bricks have already been placed by Fred. The blue bricks still need to be placed to complete the wall (the only possible design in this case).
:::

Maybe he should have made a plan before starting to build the wall, but now it is too late.
Fred only has a bunch of $2\times1$ bricks left and wants to finish the wall.
Can he still complete it with the remaining $2\times 1$ bricks?
Note that the wall to be built should have a width of exactly $w$ units and a height of exactly $h$ units.
## 输入格式

The input consists of:
- One line with two integers $w$ and $h$ ($1\leq w\leq2\cdot10^5$, $1\leq h\leq10^6$), the width and height of the wall Fred wants to build.
- One line with $w$ integers $h_1,\dots,h_n$ ($0\leq h_i\leq 10^6$), where $h_i$ is the current height of the wall at position $i$.
## 输出格式

Output "$\texttt{possible}$" if Fred can complete his wall and "$\texttt{impossible}$" otherwise.
## 样例

### 样例输入 #1
```
3 3
0 0 1
```
### 样例输出 #1
```
possible
```
### 样例输入 #2
```
6 3
1 0 1 1 0 1
```
### 样例输出 #2
```
possible
```
### 样例输入 #3
```
6 2
1 0 1 1 0 1
```
### 样例输出 #3
```
impossible
```
### 样例输入 #4
```
5 2
1 2 3 2 2
```
### 样例输出 #4
```
impossible
```


---

---
title: "[GCPC 2023] Kaldorian Knights"
layout: "post"
diff: 提高+/省选-
pid: P13676
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Kaldorian Knights
## 题目描述

The king of Kaldoria traditionally celebrates his birthday by
inviting the knights of his realm to a big jousting tournament,
and every noble house participates by sending their best knights to win fame and glory.
At the end of the tournament, the king does not only choose a
winner but ranks all $n$ knights from worst to best.

![](https://cdn.luogu.com.cn/upload/image_hosting/om9e57x8.png)

:::align{center}
Painting of a medieval tournament, [Codex Manesse](https://commons.wikimedia.org/wiki/File:Codex_Manesse_(Herzog)_von_Anhalt.jpg).
:::

The number of knights belonging to house $i$ is denoted by $k_i$.
Each knight serves at most one house.
There can be knights who do not serve any house.
The houses are ordered by their influence in the kingdom (with the first one being the most influential).
If the $k_1$ knights of the most powerful house take the last $k_1$ places in
the tournament, the house will incite a revolt against king and crown.
The members of the second most influential house are not that powerful.
Even if all its $k_2$ knights end up at the bottom of the ranking, it
would be considered a strong provocation but the house would not be able to start a revolt.
However, if the last $k_1 + k_2$ places are taken by all the
knights of the two most influential houses combined, then the two houses will unite
and start fighting the king.
More generally, if the knights of the $\ell$ most powerful houses occupy the last $k_1 + k_2 + \dots + k_\ell$ places in the tournament, they will unite and incite a revolt.

Of course, a revolt has to be avoided at all cost. Knowing that the
king often chooses the ranking spontaneously and without too much
consideration, the chief mathematician of the crown has been tasked with analysing
how many rankings will *not* lead to a revolt.
## 输入格式

The input consists of:
- One line with integers $n$ ($1 \leq n \leq 10^6$) and $h$ ($0 \leq h \leq 5000$), the number of knights and the number of houses.
- $h$ lines, with the $i$th line containing an integer $k_i$ ($1 \leq k_i \leq n$), denoting the number of knights from house $i$. Note that every house is represented by at least one knight.


It holds that $\sum_{i=1}^h k_i \leq n$.
## 输出格式

Output the number of rankings that do not lead to a revolt. As this number can be quite large, it should be output modulo $10^9+7$.
## 样例

### 样例输入 #1
```
3 0
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
4 1
3
```
### 样例输出 #2
```
18
```
### 样例输入 #3
```
4 2
2
1
```
### 样例输出 #3
```
16
```


---

---
title: "[NWERC 2023] Jogging Tour"
layout: "post"
diff: 提高+/省选-
pid: P13709
tag: ['2023', 'Special Judge', 'ICPC']
---
# [NWERC 2023] Jogging Tour
## 题目描述

You may know that in the 17th century, a group of Dutchmen founded a settlement called New Amsterdam on Manhattan Island that later went on to become New York City.
Less well-known is the story of another group of Dutchmen that also moved over to America and founded a city called *New Delft*.
Like its bigger counterpart, New Delft has been built on a grid made up of two sets of parallel streets that meet each other at a perpendicular angle.

Some stroopwafel bakeries have already been built in New Delft, but none of the streets have been constructed.
Your task is to lay out the grid of streets.
For this, you need to decide on an orientation for the grid so that there are two orthogonal directions for the two types of streets.
Once the orientation is fixed, you may build arbitrary streets, as long as each of them has one of the two given directions, as shown in Figure J.1.
Each street can be traversed in either direction.

![](https://cdn.luogu.com.cn/upload/image_hosting/v576odlj.png)

:::align{center}
Figure J.1: Illustration of Sample Input 2 with a possible street layout that gives the shortest possible path that visits all bakeries in some order.
:::


The street layout should be created in an optimal way for the annual *Stroopwafel Run*.
This is an event in which a group of runners visits all the bakeries in some order of their choosing, and they may start and end their run at any point in the city.
Your task is to come up with a grid layout that makes this shortest path as short as possible.
## 输入格式

The input consists of:
- One line with an integer $n$ ($2 \le n \le 12$), the number of stroopwafel bakeries in New Delft.
- $n$ lines, each with two integers $x$ and $y$ ($0 \le x,y \le 10^6$), the coordinates of one of the bakeries.


The bakeries are at distinct coordinates, so for any $1 \le i,j \le n$ with $i \neq j$, it holds that $(x_i, y_i) \neq (x_j, y_j)$.

## 输出格式

Output the length of the shortest possible path that visits all bakeries in some order, assuming an optimal grid layout.

Your answer should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
3
0 1
1 2
3 0
```
### 样例输出 #1
```
4.24264068712
```
### 样例输入 #2
```
4
1 4
6 0
5 3
2 6
```
### 样例输出 #2
```
11.1566387517
```


---

---
title: "[GCPC 2024] Dark Alley"
layout: "post"
diff: 提高+/省选-
pid: P13719
tag: ['线段树', '2024', 'ICPC']
---
# [GCPC 2024] Dark Alley
## 题目描述

One cold and foggy night, you walk down a shady alley.
There should be a lamp every few metres but none of them seem to work, and in this night, not even the moon enlightens your path.
Alone and in the dark, you wonder:
"Even if there was a working lamp somewhere, how much would it lighten my way".
Now, back at home, you want to calculate this.

![](https://cdn.pixabay.com/photo/2019/06/13/05/24/the-park-at-night-4270765_1280.jpg)

:::align{center}
A foggy alley. [Photo by Henryk Niestrój](https://pixabay.com/de/photos/park-in-der-nacht-dunkle-stra\%C3\%9Fe-4270765/)

:::

The alley can be modelled as a line with a length of $n$ metres.
The fog has a uniform density and reduces the light of a lamp by a factor of $1-p$ every metre.
The brightness at one point is the sum of the light that reaches this point from every lamp.
You want to calculate this brightness at some points after placing some lamps.
## 输入格式

The input consists of:
- One line with two integers $n$ and $q$ and one real number $p$  ($1\leq n, q\leq 2\cdot10^5, 0 < p < 1$), the length of the alley, the number of queries and the density of the fog. The density $p$ of the fog will be given with at most $6$ digits behind the decimal point.
- $q$ lines containing one of three query types:
  
  1. "$\texttt{+ b x}$" given two integers $b$ and $x$ ($1\leq b \leq 10^9$ and $1\leq x \leq n$), place a lamp with brightness $b$ at position $x$.
  2. "$\texttt{- b x}$" given integers $b$ and $x$ ($1\leq b \leq 10^9$ and $1\leq x \leq n$), remove a lamp with brightness $b$ at position $x$. It is guaranteed that a lamp with that brightness was placed there earlier.
  3. "$\texttt{? x}$" given one integer $x$ ($1\leq x \leq n$), calculate the brightness at position $x$.

## 输出格式

It can be shown that the brightness can be calculated as a fraction $\frac{P}{Q}$ where $Q$ is not divisible by $10^9+7$. For each query of type "$\texttt{?}$", print the brightness as $P\cdot Q^{-1} \bmod 10^9+7$ in a single line.
## 样例

### 样例输入 #1
```
5 6 0.25
+ 4 2
? 1
? 2
? 3
? 4
? 5
```
### 样例输出 #1
```
3
4
3
250000004
187500003
```
### 样例输入 #2
```
5 7 0.33
+ 9 1
? 5
+ 4 3
? 2
? 5 
- 9 1
? 2
```
### 样例输出 #2
```
312342734
470000012
341542736
760000008
```
## 提示

In the first sample case, the brightness in the alley after placing the lamp will look like this:

| $3$ | $4$ | $3$ | $2.25$ | $1.6875$ |
|:-:|:-:|:-:|:-:|:-:|





---

---
title: "[GCPC 2024] Even Odd Game"
layout: "post"
diff: 提高+/省选-
pid: P13720
tag: ['博弈论', '2024', '交互题', 'Special Judge', 'ICPC']
---
# [GCPC 2024] Even Odd Game
## 题目描述

As every Saturday, Eve is paying her local game club a visit.
Today, Bob has brought a new game he has designed on his own.
After thorough investigation, you claim that there exists a dominant strategy, so one player can always win.
Bob is hesitant to accept that his game is boring to play, so he challenges you to play a round!
Since you claim that there exists a dominant strategy, you may determine who begins the game.

![](https://cdn.luogu.com.cn/upload/image_hosting/119eym2b.png)

:::align{center}
Figure E.1: The cards in the two sample interactions.
:::

The rules are as follows.
There are $n$ cards on the table, each containing a maths operation ($\texttt{+}$ or $\texttt{*}$) and an integer, as shown in Figure E.1.
Eve and Bob alternate picking cards to manipulate a common number using one of the cards.
For instance, if the current value of the number is $5$, and the card says $+3$, then the value gets updated to $8$.
Each card can only be used once, and the game ends when all the cards have been used.
The player who makes the first move wins if the final number is odd, and the other player wins if the final number is even.
Given the list of cards and the starting value, help Eve win the game.

## 输入格式

The interactor begins by outputting the starting state of the game in the following format:
- One line with an integer $n$ ($1 \le n \le 300$), the number of cards.
- $n$ lines, each with a character $o$ and an integer $x$ ($o \in \{$'$\texttt{+}$'$, $'$\texttt{*}$'$\}$, $1 \le x \le 10^6$) indicating one of the cards.
- One line with an integer $x$ ($1 \le x \le 10^6$), the starting value.


It is guaranteed that the $n$ cards in the input are distinct.

  Then, your submission must output one of "$\texttt{me}$" or "$\texttt{you}$", depending on if you want to go first or you want the interactor to go first.

  Then your submission and the interactor alternate outputting cards in the same format as above.
  No card can be played more than once.
  Your submission must exit when all cards have been played, regardless of which player made the last move.

  Your submission will be accepted if it follows all the rules above and the final value has the parity indicated on the first line of your output.

  Make sure you flush the buffer after each write.

  A testing tool is provided to help you develop your solution.
## 样例

### 样例输入 #1
```
3
+ 7
* 4
+ 2
1


* 4
```
### 样例输出 #1
```





me
+ 2

+ 7
```
### 样例输入 #2
```
2
+ 8
* 5
10

+ 8
```
### 样例输出 #2
```




you

* 5
```


---

---
title: "[GCPC 2024] Geometric Gridlock"
layout: "post"
diff: 提高+/省选-
pid: P13722
tag: ['2024', 'Special Judge', '构造', 'ICPC']
---
# [GCPC 2024] Geometric Gridlock
## 题目描述

*Pentominous* is a grid logic puzzle based on the twelve pentominoes. A pentomino is a polygon formed by connecting five equal-sized squares edge to edge.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/dwgeqnjb.png)

Figure G.1: The twelve pentominoes (up to mirroring and rotations) and their names.
:::

The goal of this puzzle is to divide a grid into regions of size $5$ (that is, pentominoes), so that no two regions that share a side have the same shape.
You are allowed to rotate and mirror the pentominoes, but such rotations and reflections count as the same shape.
The twelve possible shapes can be seen in Figure G.1.

In a normal *Pentominous* puzzle, the player is given some pre-filled cells, for which the shape of their region is already predetermined.
In this problem, you are working with a completely blank grid of dimensions $h\times w$, and your task is to create any valid arrangement of pentominoes.
## 输入格式

The input consists of:
- One line with two integers $h$ and $w$ ($1 \le h,w \le 100$), the height and width of the grid.
## 输出格式

If there is no valid $h\times w$ *Pentominous* grid, output "$\texttt{no}$".
  Otherwise, output "$\texttt{yes}$", followed by $h$ lines of width $w$ each, a possible grid using the letters from Figure G.1.
  If there is more than one solution, any one of them will be accepted.
## 样例

### 样例输入 #1
```
3 5
```
### 样例输出 #1
```
yes
UUXUU
UXXXU
UUXUU
```
### 样例输入 #2
```
2 10
```
### 样例输出 #2
```
yes
LLLLNNNPPP
LIIIIINNPP
```
### 样例输入 #3
```
99 17
```
### 样例输出 #3
```
no
```
### 样例输入 #4
```
6 10
```
### 样例输出 #4
```
yes
IPPYYYYVVV
IPPXYLLLLV
IPXXXFZZLV
ITWXFFFZUU
ITWWNNFZZU
TTTWWNNNUU
```
### 样例输入 #5
```
1 5
```
### 样例输出 #5
```
yes
IIIII
```
## 提示

:::align{center}

| ![](https://cdn.luogu.com.cn/upload/image_hosting/xzo3g55c.png) | ![](https://cdn.luogu.com.cn/upload/image_hosting/arn3qmip.png) | ![](https://cdn.luogu.com.cn/upload/image_hosting/e6kfe7wa.png) |
|:-:|:-:|:-:|
| Illustration of Sample Output 1. | Illustration of Sample Output 2. | Illustration of Sample Output 4. |


| [![](https://cdn.luogu.com.cn/upload/image_hosting/5c9kokf9.png)](https://puzz.link/p?pentominous/10/10/s9967k09h77j4o4o1h157jbjbj00h87k30a8s) | [![](https://cdn.luogu.com.cn/upload/image_hosting/dz1q9nmw.png)](https://puzz.link/p?pentominous/10/10/s5558k95h78j4o5o3o4o42h61k88a6s) |
|:-:|:-:|
| [![](https://cdn.luogu.com.cn/upload/image_hosting/ung8r57e.png)](https://puzz.link/p?pentominous/10/10/r44a44k4j4j7j4j44454k4o3o4o4i47r) | [![](https://cdn.luogu.com.cn/upload/image_hosting/8ltajbb5.png)](https://puzz.link/p?pentominous/10/10/s3327k22h71j1o7l1h1l1h2o21h11k7337s) |


Example *Pentominous* puzzles for you to try after the contest.

:::




---

---
title: "[GCPC 2024] Laundry"
layout: "post"
diff: 提高+/省选-
pid: P13727
tag: ['2024', 'ICPC', '分类讨论']
---
# [GCPC 2024] Laundry
## 题目描述

Every Sunday is laundry day, and there is always a huge pile of clothes waiting to be washed, which is certainly going to take you forever. 
You are particularly annoyed by how careful you have to be when washing certain items, and how important it is that you choose an appropriate washing programme for each item. 

:::align{center}
![](https://cdn.pixabay.com/photo/2018/04/02/01/14/hanging-3282769_1280.jpg)

Laundry hanging to dry [Image by gregroose on Pixabay](https://pixabay.com/photos/hanging-architecture-clothesline-3282769/)
:::

Fortunately, your washing machine is quite old and only supports three different washing programmes: A, B, and C.
You can put at most $k$ items in one load, 
and each load can be washed using one of the programmes. 

Some items are easy to care for, and you can put them in any load you like. 
More delicate items must not be washed using a specific programme, but the other two are fine. 
Of course, the worst clothes are the ones for which only one programme is appropriate. 

You have already sorted the items into seven piles by putting items together for which the same combination of programmes is fine, so 
you know how many items are in each pile. 

What is the minimum number of loads you need to wash? 

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/sd620u2k.png)

Figure L.1: Illustration of Sample Input 2 with an optimal solution. The figure on the left shows seven piles, one for each combination. The figure on the right shows a (possible) optimal solution, where each pile is washed in one load. The numbers on the pile represent how many items of each combination are washed with this load. In particular, the leftmost pile is washed using programme A, the two piles in the middle with programme B, and the two piles on the right with programme C. Thus, we need five loads to wash all items, which is optimal since we have 15 items in total.
:::

## 输入格式

The input starts with a line containing one integer $t$ ($1 \leq t \leq 10^4$), the number of test cases. Then for each test case: 
- One line with an integer $k$ ($1\leq k\leq 10^9$), the number of items you can put in one load.
- One line with seven integers $c_1, \ldots, c_7$ ($0 \leq c_i \leq 10^9$), the number of items for each combination of programmes. The integers are given in this order: A, B, C, AB, BC, AC, ABC. For example, $c_4$ must be washed using either programme A or programme B.  
## 输出格式

For each test case, output the minimum number of loads that are needed to wash all clothes.
## 样例

### 样例输入 #1
```
4
10
15 11 9 5 2 7 1
120
0 0 0 0 0 0 0
6
5 6 8 9 1 0 0
1213
295053681 137950336 87466375 956271897 344992260 31402049 988259763
```
### 样例输出 #1
```
6
0
6
2342454
```
### 样例输入 #2
```
1
3
1 2 1 3 3 2 3
```
### 样例输出 #2
```
5
```


---

---
title: "[NWERC 2024] It's a Kind of Magic"
layout: "post"
diff: 提高+/省选-
pid: P13747
tag: ['2024', '容斥原理', 'ICPC', '筛法']
---
# [NWERC 2024] It's a Kind of Magic
## 题目描述

Everyone knows that a $3\times3$ magic square must meet two criteria:
1. All nine numbers must be positive and distinct.
2. The sums along all rows, columns, and diagonals are equal.

Everyone, except maybe Matt Parker$^1$.
He wants to create a magic square of squares, that is, a magic square that also meets a third criterion:

3. Each number is a square of a positive integer.

His "result" can be seen in the picture in the corner.
As you may notice, his square is not that magic... Not only do most of the values appear twice, it also has a diagonal with the wrong sum.
To be honest, apart from containing non-square values, there is not much that could make this square worse.
Well, at least he tried!

:::align{center}

![](https://images.squarespace-cdn.com/content/v1/548b5b70e4b0b57ba182907d/1460978229774-7K3041H67ZE4FMREF4XF/image-asset.jpeg?format=2500w)

The Parker Square. © [Brady Haran](https://www.bradyharanblog.com/the-parker-square), used with permission

:::

But that is all in the past.
After finding the *Parker Square*, he decided to completely ignore property $3$ from now on and to instead give property $2$ a new twist.
He now considers multiplicative magic squares, which are exactly like normal magic squares except that the *products* along all rows, columns, and diagonals have to be equal, instead of the sums.
Who knows, Matt might even manage to find a proper multiplicative magic square in the future!

With this definition at hand, Matt wrote some terrible Python code -- his words, not ours -- to count the number of multiplicative magic $3\times 3$ squares where the product of the numbers in a single row, column, or diagonal is at most $n$.
As you may have guessed by now, his code is way too slow.
Therefore, we task you to do the same, just more efficiently.
Given an integer $n$, count the number of multiplicative magic $3\times 3$ squares with product at most $n$.

---

$^1$Recreational mathematician, author, comedian, YouTube personality, and science communicator.


## 输入格式

The input consists of:
- One line with an integer $t$ ($1 \leq t \leq 10^5$), the number of test cases.
- $t$ lines, each with an integer $n$ ($1 \leq n \leq 10^{18}$), the maximum product.
## 输出格式

For each test case, output the number of multiplicative magic squares with product at most $n$.
## 样例

### 样例输入 #1
```
3
500
1000
3000
```
### 样例输出 #1
```
8
16
56
```


---

---
title: "[CERC 2021] Airline"
layout: "post"
diff: 提高+/省选-
pid: P13763
tag: ['2021', '树形 DP', '树的遍历', 'ICPC', 'CERC']
---
# [CERC 2021] Airline
## 题目描述

An airline company offers regular flights involving $n$ different airports. Each flight links two airports directly (i.e. without stopping at any other airport) and allows travel in both directions. The flights are arranged such that for any choice of starting airport $s$ and destination airport $t$, there exists exactly one sequence of flights between the two airports without visiting any airport more than once. The number of flights in this sequence is called the distance between $s$ and $t$.

Were the airline to add another flight, say between airports $x$ and $y$, it is possible that for some pairs $(s, t)$, another, shorter sequence of flights from $s$ to $t$ would form. The more pairs affected, the more promising the new connection between $x$ and $y$ is considered to be. The airline is asking you to help them evaluate several possible additions $(x, y)$ with respect to this criterion.
## 输入格式

An airline company offers regular flights involving $n$ different airports. Each flight links two airports directly (i.e. without stopping at any other airport) and allows travel in both directions. The flights are arranged such that for any choice of starting airport $s$ and destination airport $t$, there exists exactly one sequence of flights between the two airports without visiting any airport more than once. The number of flights in this sequence is called the distance between $s$ and $t$.

Were the airline to add another flight, say between airports $x$ and $y$, it is possible that for some pairs $(s, t)$, another, shorter sequence of flights from $s$ to $t$ would form. The more pairs affected, the more promising the new connection between $x$ and $y$ is considered to be. The airline is asking you to help them evaluate several possible additions $(x, y)$ with respect to this criterion.
## 输出格式

Output $q$ lines; in the $i$-th line, output the number of pairs $(s, t)$ such that $1 \leq s < t \leq n$ and the distance between airports $s$ and $t$ would decrease if the original network of $n - 1$ flights were supplemented by a direct flight connection between the airports $x_i$ and $y_i$.
## 样例

### 样例输入 #1
```
8 2
1 5
5 2
7 3
3 8
6 4
4 5
6 3
5 7
2 6
```
### 样例输出 #1
```
10
4
```
## 提示

### Input limits

* $2 \leq n \leq 10^6$
* $1 \leq q \leq 10^5$
* $1 \leq u_i \leq n; 1 \leq v_i \leq n; u_i \neq v_i$
* $1 \leq x_i \leq n; 1 \leq y_i \leq n; x_i \neq y_i$
* $\sum_{i=1}^{q} d_i \leq 10^7$, where $d_i$ is the distance between $x_i$ and $y_i$ in the original flight network.



---

---
title: "[CERC 2021] Fishing"
layout: "post"
diff: 提高+/省选-
pid: P13767
tag: ['线段树', '2021', 'ICPC', 'CERC']
---
# [CERC 2021] Fishing
## 题目描述

There is a small village situated on the coast of the Adriatic Sea. The fishermen map the sea as a grid of $N \times M$ cells such that the first row is adjacent to the coast and the last row is the furthest away. They track the movement of fish and other items floating in the sea. The sea is mostly empty, but there are $K$ grid cells of interest. The location of each such point is denoted by row $R_i$ and column $C_i$. The fishermen estimate that their catch from fishing in the $i$-th cell is going to be worth $V_i$. Note that $V_i$ can be zero or negative if the corresponding area is predominantly occupied by undesired items. All other cells are considered to have a value of 0.

Every day, the local council approves a rectangular fishing area that includes columns from $X$ to $Y$ and extends $H$ rows from the shore into the sea. To fish in the selected area, the fishermen will prepare a fishing net that is exactly $H$ units long. Although the net has a fixed length, it can be rolled out to an arbitrary width $W$ that doesn't exceed $Y - X + 1$. Based on their information about the sea, they will drop the net somewhere within the approved fishing area to maximize the catch defined as the sum of cell values covered by the net.

The fishermen aim to choose the optimal fishing location every day. Write a program that will find the best value of their catch for the approved fishing areas for the next $Q$ days. You may assume that the cell values are constant; they are not depleted from fishing on previous days.
## 输入格式

The first line contains the number of rows $N$, the number of columns $M$ and the number of non-empty cells $K$. These cells are described in the following $K$ lines with their row $R_i$, column $C_i$ and value $V_i$, separated by a space. Rows are numbered from 1 to $N$ and columns from 1 to $M$. All values $V_i$ are integers.

The next line contains the number of queries $Q$. The $j$-th query is described by three integers $A'_j$, $X'_j$ and $Y'_j$. To ensure that your solution answers queries in the given order, the queries are given in an encoded form. The actual query can be computed as

$$
\begin{aligned}
H_j &= H'_j \oplus A_{j-3}, \\
X_j &= X'_j \oplus A_{j-2}, \\
Y_j &= Y'_j \oplus A_{j-1},
\end{aligned}
$$

where $A_j$ denotes the answer to the $j$-th query (or 0 if $j \leq 0$) and $\oplus$ denotes a bitwise xor operation. Your program should find the region with the maximum catch value that spans the first $H_j$ rows and some subrange of columns from $X_j$ to $Y_j$.

## 输出格式

For each query, output a single line with the maximum value of the catch. Note that the fishermen can always choose to keep an empty net with the value of 0.
## 样例

### 样例输入 #1
```
10 7
12
2 6 -5
3 3 3
4 2 -2
4 6 2
5 3 -1
5 5 5
7 1 8
7 7 4
8 4 -3
8 5 1
9 6 -4
10 3 2
6
5 1 5
10 1 0
7 1 11
15 15 6
9 1 0
3 7 1
```
### 样例输出 #1
```
7
13
0
6
3
0
```
## 提示

### Comment

The decoded list of queries:

```
5 1 5
10 1 7
7 6 6
8 2 6
4 1 6
3 1 2
```

### Input limits

* $1 \leq N, M, K, Q \leq 300\,000$
* $|V_i| \leq 1000$


---

---
title: "[CERC 2021] Regional development"
layout: "post"
diff: 提高+/省选-
pid: P13771
tag: ['2021', '网络流', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2021] Regional development
## 题目描述

The King has received several complaints that certain regions of his kingdom are economically neglected. The citizens have not seen a single merchant travelling on certain roads between villages in a very long time. To fix this problem and return wealth and prosperity to his kingdom, the King has appointed his royal mathematician to come up with a viable plan of merchant's routes.

The plan will consist of a positive number of merchants travelling along each road in one of the directions. The number of merchants entering a village along the roads should be equal to the number of merchants exiting it. To ensure a somewhat even distribution of merchants throughout the kingdom, the King has requested that the number of merchants travelling along each road should be at least one and less than $M$.

The royal mathematician has been summoned by the King to present his findings. His future is uncertain as he has not been able to solve the problem. However, he did make some progress. He found a plan with a valid number of merchants travelling along each road. The only problem is that the incoming and outgoing merchants in the villages do not add up (at least not exactly). Their difference might not be zero for every village, but it is equal to zero modulo $M$. He is willing to share his findings with you, if you can write a program that finds a valid plan or reports that it doesn't exist.
## 输入格式

The first line contains $N$, the number of villages, $R$, the number of roads and the number $M$.

The following $R$ lines describe the roads with numbers $A_i$, $B_i$ and $C_i$ that indicate a road between villages $A_i$ and $B_i$ with $C_i$ merchants travelling from $A_i$ to $B_i$. Cities are numbered from 1 to $N$. There is at most one road between each pair of villages and no road connects a village with itself. The difference between incoming and outgoing merchants in each village is equal to 0 modulo $M$.
## 输出格式

Print the number of merchants travelling along each road. Print them in the same order as they were given in the input and on separate lines. If the merchants travel in the opposite direction with respect to the order of cities that defined a road in the input, indicate this with a negative value (e.g. if there are $X$ merchants travelling from $B_i$ to $A_i$, indicate this with $-X$ in the $i$-th line of output).

If there are multiple solutions, you can output any of them. If no solution exists, print the word "IMPOSSIBLE" in a single line (without the quotes).
## 样例

### 样例输入 #1
```
4 5 4
1 2 1
2 3 2
4 1 1
2 4 3
3 4 2
```
### 样例输出 #1
```
2
3
2
-1
3
```
## 提示

### Input limits

* $1 \leq N \leq 1000$
* $0 \leq R \leq 10\ 000$
* $2 \leq M \leq 1000$
* $1 \leq A_i, B_i \leq N$
* $0 < C_i < M$


---

---
title: "[SWERC 2023] Supporting everyone"
layout: "post"
diff: 提高+/省选-
pid: P13793
tag: ['2023', '二分图', 'ICPC']
---
# [SWERC 2023] Supporting everyone
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/9b693d641063096ae32c5b06333b6fdf2138d3da.png)

:::

Alice is attending a sport event with many national teams and one thing is important to her: supporting every country.


There are $N$ countries represented and she has two ways to support a country: either have the flag drawn on her or have a pin with the name of the country. Alice has a list containing, for each country, the colours needed to make its flag. A total of $M$ colours that may appear across all flags and, in Alice&#39;s list, each colour is conveniently represented as an integer between $1$ and $M$.


Each crayon and pin cost $1$, but her budget is tight... Can you help her find the minimum she can spend to support everyone?
## 输入格式

The first line contains the two space-separated numbers $N$ and $M$.
Then follow $2N$ lines, grouped in pairs; the $(2i-1)^{\text{th}}$ and $2i^{\text{th}}$ lines represent the $i^{\text{th}}$ country.
More precisely, the $(2i-1)^{\text{th}}$ line contains a single integer $k_i$: the number of colours in the flag of the $i^{\text{th}}$ country.
Then, the $2i^{\text{th}}$ line contains $k_i$ space-separated numbers $c_{i,1}, c_{i,2}, \dots , c_{i,k_i}$; these are the colours in the flag of the $i^{\text{th}}$ country.


**Limits**
	
- $1 \leq N \leq 1\,000$;
- $1 \leq M \leq 100$;
- $1 \leq k_i \leq M$ for all $i \leq N$;
- $1 \leq c_{i,j} \leq M$ for all $i \leq N$ and $j \leq k_i$;
- for all $i \leq N$, the $M$ colour numbers 


## 输出格式

The output should contain a single line, consisting of a single number: the minimum amount Alice can spend on crayons and pins to represent every country.
## 样例

### 样例输入 #1
```
7 6
3
1 4 5
3
1 4 5
3
1 4 5
3
3 4 5
3
3 4 5
3
3 4 5
3
2 5 6
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
8 12
2
7 9
12
1 2 3 4 5 6 7 8 9 10 11 12
2
7 9
2
7 9
3
3 4 11
2
7 9
2
7 9
2
7 9
```
### 样例输出 #2
```
4
```
## 提示

**Sample Explanation 1**

The three first countries could be France, the Netherlands, and the Czech Republic, all represented by
blue (1), white (4), and red (5). The three next countries could be Italy, Hungary, and Bulgaria, with
green (3), white (4) and red (5). The last one could be Germany, with black (2), red (5), and yellow (6).
The minimum cost is 5: we buy four (blue, green, white, and red) crayons and one pin (for Germany).


**Sample Explanation 2**

We can buy two crayons for the colours 7 and 11 and buy two pins for a total cost of 4. All six countries
with flag colours 7 (red) and 11 (white) could be Canada, Indonesia, Japan, Malta, Monaco, and Poland.
The flag of Belize has 12 colours, including red and white, and the fifth country could be Botswana.


---

---
title: "[SWERC 2023] Break a leg!"
layout: "post"
diff: 提高+/省选-
pid: P13799
tag: ['计算几何', '2023', 'ICPC', '双指针 two-pointer']
---
# [SWERC 2023] Break a leg!
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a2628cf785edc53f8245d1203533bdfe5a5f491a.png)

:::

For the first time, breakdance will be featured in the Olympics. And you get to participate! Well, you get to participate to the jury... More precisely, you get to build the table in front of which the jury will be seated: still, that is an impressive feat, congratulations!


Actually, the top of the table is already built: it is plane, has constant width and constant density, and its shape consists in the interior of an $N$-sided non-crossing polygon $P_1 P_2 \dots P_N$ in which no three vertices are collinear (i.e., no line goes through three vertices or more). You have three table legs of same length and negligible width. Your task is to place them at distinct corners of the table so that the table remains stable when standing on these legs. In other words, you must choose three vertices $P_i$, $P_j$ and $P_k$ of the polygon such that the centre of gravity of the polygon lies in the interior of the triangle $P_i P_j P_k$ (and not on its boundary).


In how many different ways can you do this? If two ways of placing legs differ only by a permutation
of the legs, they are not counted as different ways.
## 输入格式

The first line contains the number $N$. Then follow $N$ lines: the $i^\text{th}$ of these lines contains two space-separated integers $x_i$ and $y_i$, which are the $x$-coordinate and the $y$-coordinate of the vertex $P_i$.

**Limits**
	
- $3 \leq N \leq 100~000$;
- $-1~000~000 \leq x_i \leq 1~000~000$ and $-1~000~000 \leq y_i \leq 1~000~000$ for all $i \leq N$;
- whenever $1 \leq i < j < k \leq N$, the vertices $P_i$, $P_j$ and $P_k$ are not collinear;
- the polygonal shape $P_1 P_2 \dots P_N$ is non-crossing.


## 输出格式

The output should contain a single line, consisting of a single integer: the number of ways of placing legs such that the table remains stable.
## 样例

### 样例输入 #1
```
4
0 0
1 0
1 1
0 1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4
0 0
5 0
6 6
0 5
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
5
0 0
2 0
2 20
1 1
0 20
```
### 样例输出 #3
```
5
```


---

---
title: "[SWERC 2023] Team selection"
layout: "post"
diff: 提高+/省选-
pid: P13802
tag: ['二分', '2023', 'ICPC']
---
# [SWERC 2023] Team selection
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/f3377480e15684bf0ebb3d7761cfa23137b681ff.png)

:::


Two team leaders get to assemble their teams by choosing team members among a set of players that are numbered from 1 to $N$. The leaders take turns, each picking the $k^\text{th}$ player among the remaining ones, according to their ideas of which one of the remaining players would be the best addition to their teams.

Given the choices of the two leaders (the first team leader starts first), please compute the list of players in each team.
## 输入格式

The input consists of three lines. The first line contains the single integer $N$. The second line contains $N/2$ space-separated integers $a_1, a_2, \dots, a_{N/2}$ representing the choices of the first team leader: during the $(2k-1)^\text{th}$ turn, the first leader chose the $a_k^\text{th}$ remaining player. The third line contains $N/2$ space-separated integers $b_1, b_2, \dots, b_{N/2}$ representing the choices of the second team leader: during the $2k^\text{th}$ turn, the second leader chose the $b_k^\text{th}$ remaining player.

**Limits**
	
- $2 \leq M \leq 4~000~000$;
- $N$ is multiple of 2;
- the choices of the team leaders are valid: at each step, they are between 1 and the number of remaining players (inclusive).
## 输出格式

The output should contain two lines, each containing $N/2$ space-separated integers. The first line should contain the list $x_1, x_2, \dots, x_{N/2}$ of the players chosen to become members of the first team, in the order they were chosen: the player $x_k$ was chosen during the $(2k-1)^\text{th}$ turn. The second line should contain the list $y_1, y_2, \dots, y_{N/2}$ of the players chosen to become members of the second team, in the order they were chosen: the player $y_k$ was chosen during the $2k^\text{th}$ turn.
## 样例

### 样例输入 #1
```
4
1 1
2 1
```
### 样例输出 #1
```
1 2
3 4
```


---

---
title: "[SWERC 2023] Broken trophy "
layout: "post"
diff: 提高+/省选-
pid: P13803
tag: ['2023', 'Special Judge', 'ICPC']
---
# [SWERC 2023] Broken trophy 
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/5a9ceba0bef33460fb6104cd612fce7a771f3f73.png)

:::

Coming back home after triumphally winning your long-coveted trophy, you discover that it was shattered to pieces in your trunk. It just remains to repair it.


Your trophy had the shape of a rectangle of size $3 \times N$, for some integer $N \geq 1$, thereby consisting of 3 lines and $N$ columns, containing a total of $3N$ unit squares. It was broken into $K$ pieces, the $k^\text{th}$ piece being a rectangle of size $A_k \times B_k$ for some integers $A_k$ and $B_k$ such that $1 \leq A_k \leq B_k \leq 3$. Such pieces may have been rotated, or even flipped, in the havoc that is your trunk.


As the first step towards repairing your trophy, you should reassemble them in the form of a rectangle of size $3 \times N$. More precisely, you have drawn, on a sheet of paper, a $3 \times N$ rectangle on which you will place your $K$ pieces, and you need to know, for all integers $i \leq 3$ and $j \leq N$, which piece will cover the unit square on the $i^\text{th}$ line and $j^\text{th}$ column of your rectangle.

## 输入格式

The input consists of three lines, each one containing space-separated integers. The first line contains the numbers $K$ and $N$. The second line contains the numbers $A_1, A_2, \dots, A_K$. The third line contains the numbers $B_1, B_2, \dots, B_K$.

**Limits**
	
- $1 \leq K \leq 300~000$;
- $1 \leq N \leq 100~000$;
- $1 \leq A_k \leq B_k \leq 3$ for all $k \leq K$;
- the pieces described in the input can be reassembled in the form of a rectangle of size $3 \times N$.
## 输出格式

The output should contain three lines, each one consisting of $N$ space-separated integers. If you plan to cover the unit square on the $i^\text{th}$ line and $j^\text{th}$ column with the $k^\text{th}$ piece, the $j^\text{th}$ number on the $i^\text{th}$ output line should be the integer $k$.


In case there are several ways to reassemble your pieces in the form of a rectangle of size $3 \times N$, every output representing one of these ways is considered correct.
## 样例

### 样例输入 #1
```
16 17
1 2 1 1 2 1 2 1 1 1 1 1 2 2 1 1
3 3 1 3 2 3 3 1 1 2 2 3 3 3 1 3
```
### 样例输出 #1
```
1 2 2 2 12 6 4 13 13 16 16 16 9 10 10 7 7
1 2 2 2 12 6 4 13 13 5 5 14 14 14 11 7 7
1 3 15 8 12 6 4 13 13 5 5 14 14 14 11 7 7
```
## 提示

**Sample Explanation 1**

This output represents the following reassembling:

:::align{center}

![](https://espresso.codeforces.com/ebe5fa074a7004f06adef36774082b3ef1655782.png)

:::

Another valid reassembling could be: 

:::align{center}

![](https://espresso.codeforces.com/109dea523bad83462aeee9eb8b60ee35eff479d2.png)

:::


---

---
title: "[CERC 2022] Combination Locks"
layout: "post"
diff: 提高+/省选-
pid: P13806
tag: ['2022', '二分图', 'ICPC', 'CERC']
---
# [CERC 2022] Combination Locks
## 题目描述

Alice and Bob are playing with combination locks. Each of them has a combination lock that consists of $N$ rotating discs with digits 0 to 9 engraved on them. Their friend Charlie doesn’t have a lock and has devised a game to keep them occupied. He will keep track of whether the corresponding digits of their locks match and will describe the current situation with a difference pattern string $S$. The $j$-th character of $S$ is either '=' or '.' and indicates whether the $j$-th digits in Alice's and Bob's locks match or not, respectively.

Charlie will officiate the game, while Alice and Bob take turns with Alice starting first. On each move, a player has to change one digit of their combination lock. As Charlie only keeps track of the difference patterns, this pattern has to change for a move to be valid. He is also rather superstitious and has brought a list of patterns $P_i$ that must not appear during the game. Charlie's main task is to enforce the rule that no difference pattern repeats during the course of the game. The player who can't make a move loses the game.

Write a program that will determine the winner of the game if both players play optimally.
## 输入格式

The first line contains the number of test cases $T$. Each test case starts with a line containing two space-separated integers $N$ and $C$. This is followed by two lines that describe the starting configuration of Alice's and Bob's combination lock. A lock configuration is a string of $N$ digits. The following $C$ lines describe Charlie's superstitious patterns $P_i$. The superstitious list doesn't contain duplicates and it is guaranteed that the difference pattern of the starting lock configurations is not on the superstitious list.
## 输出格式

For every test case output one line with the name of the winner.
## 样例

### 样例输入 #1
```
3
2 2
12
89
=.
==
3 1
204
101
.==
3 2
000
000
...
==.
```
### 样例输出 #1
```
Alice
Bob
Bob
```
## 提示

### Comment

In the first example, the only move for Alice is to change the second digit from 2 to 9. Any other move is invalid because it doesn't change the difference pattern or because it would result in a superstitious pattern. Bob doesn't have a valid move, therefore Alice wins.

### Input limits

* $1 \leq T \leq 20$
* $1 \leq N \leq 10$
* $0 \leq C \leq 1000$


---

---
title: "[CERC 2023] Cakes"
layout: "post"
diff: 提高+/省选-
pid: P13847
tag: ['2023', '网络流', 'ICPC', 'CERC']
---
# [CERC 2023] Cakes
## 题目描述

Your local cake shop is making a business plan for the next few months. The bakers have $C$ different recipes, each requiring their own set of ingredients and tools. During the baking, the ingredients are consumed, but the tools are not and can be reused for other recipes. Currently, the bakery has no ingredients or tools – they were all destroyed in the recent floods or taken away by the tax bureau.

The son of the main chef managed to convince everyone to only bake each type of cake once. Individuals on the internet are supposedly happy to pay extra to be the only owners of their own unique Nutty-Fudge Tart (NFT). In fact, the son has already gone ahead and estimated how much money they can earn for each type of cake. Now bakers are looking at each other, trying to figure out which types of cake to prepare for maximum profit. You are given the costs of all ingredients, tools, and prices of cakes. Your task is to determine how much profit the bakers can make.
## 输入格式

The first line contains three integers: $G$, $C$, and $T$, the number of ingredients, the number of recipes, and the number of different tools in them, respectively. The second line contains $C$ space-separated integers $c_1, \ldots, c_C$, the prices of each cake. The third line contains $G$ space-separated integers $g_1, \ldots, g_G$, representing the prices of each ingredient. The fourth line contains $T$ space-separated integers $t_1, \ldots, t_T$, representing the prices of all tools.

This is followed by $C$ lines, each containing $G$ space-separated integers $a_{i,j}$, corresponding to the amount of ingredient $j$ in cake $i$.

Finally, this is followed by $C$ lines of the following format: the $i$-th row starts with an integer $n_i$, the number of tools required for $i$-th cake. This is followed by $n_i$ space-separated integers $b_{i,k}$, indicating that we need tool $b_{i,k}$ to prepare cake $i$ (listed tools are distinct).
## 输出格式

Print a single number: the maximum profit that the cake shop can make.
## 样例

### 样例输入 #1
```
5 3 4
14 18 21
1 2 3 1 2
5 6 3 10
0 0 1 2 0
1 2 0 1 2
5 2 1 0 0
2 1 2
2 2 3
2 3 4
```
### 样例输出 #1
```
3
```
## 提示

### Comment

The maximum profit is made by baking cakes 1 and 2, but not cake 3.

### Input limits

- $1 \leq G, C, T \leq 200$
- $0 \leq c_i, t_i \leq 10^9$
- $0 \leq g_j, a_{i,j} \leq 10^8$
- $0 \leq n_i \leq T$
- $1 \leq b_{i,k} \leq T$


---

---
title: "[CERC 2023] Drying Laundry"
layout: "post"
diff: 提高+/省选-
pid: P13848
tag: ['动态规划 DP', '2023', 'ICPC', 'bitset', 'CERC']
---
# [CERC 2023] Drying Laundry
## 题目描述

Harry the Beaver runs a hotel and has to wash bed sheets every Sunday night for the next $Q$ weeks until the tourist season ends. On week $j$, he has $N$ freshly washed bed sheets that he wants to dry by hanging them on two parallel clotheslines of length $L_j$ each. The sheets can be hung next to each other but must not overlap. Each sheet is $d_i$ units wide and rather long, therefore he will always orient it so that it will take up $d_i$ units of the line when hung to dry. The sheets have different drying times that are not related to their sizes because of different materials. Thus, the $i$-th sheet needs $t_i^{\text{slow}}$ minutes to dry. However, if it is hung over both lines at the same time, it dries quicker in $t_i^{\text{fast}}$ minutes, but also takes up space on the other line. To avoid smelly sheets, Harry the Beaver has to start drying all of them immediately after washing, i.e. all sheets have to be hung simultaneously.

Harry the Beaver wants to go to sleep as soon as possible on Sundays, therefore, he asks you to help him determine the minimal required drying time for each week $j$, or inform him that it is impossible to finish drying the sheets that week.
## 输入格式

The first line contains an integer $N$, the number of sheets, and an integer $Q$, the number of weeks until the end of the tourist season. The next $N$ lines contain space-separated integers $d_i$, $t_i^{\text{fast}}$, and $t_i^{\text{slow}}$, which correspond to the width, the shorter drying time, and the longer drying time of the $i$-th sheet, respectively. The final $Q$ lines the the input contain integers $L_j$, $j$-th of which represents the length of the clothesline for week $j$.
## 输出格式

Print $Q$ lines, with $j$-th of them containing the minimal required drying time for week $j$, or "-1" (without the quotes) if it is impossible to finish drying the sheets that week.
## 样例

### 样例输入 #1
```
3 3
1 2 2
1 1 4
2 3 100
3
1
4
```
### 样例输出 #1
```
4
-1
3
```
## 提示

### Input limits

- $1 \leq N \leq 3 \cdot 10^4$
- $1 \leq Q \leq 3 \cdot 10^5$
- $1 \leq d_i \leq 3 \cdot 10^5$ for all $1 \leq i \leq N$
- $1 \leq t_i^{\text{fast}} \leq t_i^{\text{slow}} \leq 10^9$ for all $1 \leq i \leq N$
- $1 \leq L_j \leq 3 \cdot 10^5$ for all $1 \leq j \leq Q$


---

---
title: "[CERC 2023] Interactive Reconstruction[Can't judge yet]"
layout: "post"
diff: 提高+/省选-
pid: P13853
tag: ['2023', '交互题', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2023] Interactive Reconstruction[Can't judge yet]
## 题目描述

This is an interactive task where your program will communicate with a grader through standard input and output. Your task is to reconstruct a labelled tree with $N$ nodes and $N-1$ edges. Nodes are labelled from $1$ to $N$.

Your program is allowed to make a few queries of the following type: Your program should print a string of $N$ characters, consisting only of zeros and ones, one corresponding to each node. The grader will return a sequence of $N$ space-separated integers, the $i$-th representing the sum of the values (i.e. digits of the query string) of all neighbours of the $i$-th node. That is, if node $j$ is a neighbour of node $i$, then the $j$-th digit of the query string counts towards the sum in the $i$-th number of the grader’s answer.

See the example below for an illustration.

### Input and output data

The first input line will contain the number $N$, the number of nodes in the tree.

Your program then has two options:

1. Print "QUERY" (without quotation marks), a space, and a string of $N$ zeros and ones.
2. Print "ANSWER" (without quotation marks), a newline, and $N-1$ lines, each containing a pair of space-separated integers $a, b$, indicating that there exists an edge between nodes $a$ and $b$.

If your program prints a query, this will be followed by the grader returning a line with $N$ space-separated integers, one per node. If your program prints an answer, the grader will check the returned tree for correctness.

If there was a mistake in your queries, either due to incorrect formatting or due to an exceeded number of queries, the grader will print “ERROR” (no quotation marks) instead of the answer.

Important: Ensure that your program flushes its output after printing and correctly exits after printing the answer. It is up to you whether to implement the ERROR handling. Its purpose is to allow your program to exit gracefully and get a WA instead of a TLE verdict in the case of an error.

### Input limits

- $2 \leq N \leq 3 \cdot 10^{4}$
- At most $2 \uparrow \uparrow 3 = 2^{(2^{2})} = 16$ queries are allowed. The final answer does not count toward this restriction.
## 样例

### 样例输入 #1
```
5

0 0 1 2 0

1 1 0 0 1

0 0 0 1 0
```
### 样例输出 #1
```

QUERY 10001

QUERY 00010

QUERY 10000

ANSWER
1 4
4 2
5 4
3 5
```
## 提示

### Comment

The tree in question is the following one:

```
1-4-2
  |
  5-3
```

With the three queries in the example, it is possible to reconstruct it uniquely.


---

---
title: "[CERC 2023] Jumbled Stacks"
layout: "post"
diff: 提高+/省选-
pid: P13854
tag: ['2023', 'Special Judge', '构造', 'ICPC', 'CERC']
---
# [CERC 2023] Jumbled Stacks
## 题目描述

We are given a set of $n$ cards, labelled from $1$ to $n$, which are distributed into $k$ stacks $S_1, S_2, \ldots, S_k$. Each stack has a limited capacity: the $i$-th stack, $S_i$, can contain at most $C_i$ cards. The only way we can manipulate these cards is by taking the top card of a stack and moving it to the top of some other stack (as long as this wouldn’t exceed the capacity of the destination stack).

Using a sequence of such moves, we would like to rearrange the cards so that the first few stacks (0 or more) with the smallest indices are filled to capacity, the stack immediately after them is not filled to capacity (and may even be empty) and all stacks after that are completely empty. Moreover, if we stack together all the stacks from $S_1$ at the bottom to $S_k$ at the top, the cards should be ordered from smallest to largest, with $1$ at the bottom and $n$ at the top.

It is guaranteed that $n \leq \left( \sum_{i=1}^{k} C_i \right) - \max_{1 \leq i \leq k} C_i$.

Suppose we had $n = 6$ cards on $k = 3$ stacks, with capacities $C_1 = 4$, $C_2 = C_3 = 3$, and with the following initial state: $S_1 = [2, 3, 0, 0]$ (from bottom to top; $0$ indicates an empty slot), $S_2 = [4, 1, 6]$, $S_3 = [5, 0, 0]$. Then the desired end state is $S_1 = [1, 2, 3, 4]$, $S_2 = [5, 6, 0]$ and $S_3 = [0, 0, 0]$.

## 输入格式

The first line contains two integers, $n$ (the number of cards) and $k$ (the number of stacks), separated by a space. The remaining $k$ lines describe the initial state of the stacks; the $i$-th of these lines describes $S_i$ and contains $C_i + 1$ integers, separated by spaces. The first of these integers is $C_i$ (the capacity of the stack $S_i$), the rest of them are the labels of the cards on $S_i$, from bottom to top. If the stack $S_i$ contains fewer than $C_i$ cards (it could even be empty), the last few integers in the line will be $0$.

## 输出格式

Print a sequence of moves that bring the stacks into the desired end state. For each move, output a line containing two integers, separated by a space: first the number of the stack from which the card is being moved and then the number of the stack to which it is being moved (the stacks are numbered from $1$ to $k$; the destination stack must not be the same as the source stack). The number of moves must not exceed $10^5$. After the end of the sequence of moves, print a line containing “0 0” (without the quotation marks). If there are several possible solutions, you may output any of them.
## 样例

### 样例输入 #1
```
6 3
4 2 3 0 0
3 4 1 6
3 5 0 0
```
### 样例输出 #1
```
2 3
2 3
1 2
1 2
3 1
2 1
2 1
3 2
3 1
2 3
1 3
2 1
3 2
3 2
0 0
```
## 提示

### Comment

This is the example discussed earlier in the problem statement. The sample output shows
a sequence of 14 moves which bring the stacks into the desired end state.

### Input limits

- $1 \leq n \leq 100$
- $3 \leq k \leq 100$
- $1 \leq C_i \leq n$


---

---
title: "[CERC 2023] Keys"
layout: "post"
diff: 提高+/省选-
pid: P13855
tag: ['2023', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2023] Keys
## 题目描述

Alice and Bob live in a massive mansion with $n$ rooms (one of them denoting outdoors, where they play the Moon game) and $m$ doors between them. Each door connects two rooms or a room with the outdoors and has a single unique key that opens this door only. Every door closes behind you and locks automatically, so one always needs a key to pass through. The building is very large, but Alice and Bob only use one room – their bedroom. Other rooms are only there to make the house look bigger and make the neighbors jealous.

This unusual way of building their house is now causing some trouble for Alice and Bob. Bob is leaving for a two-week-long trip. In a week, Alice is also going abroad for a month and when she leaves, she needs the right keys to leave the house. However, Bob also needs keys to get back in since Alice will not be there at the time to let him in. Alice and Bob are now trying to figure out how to split the keys to the doors for Alice to be able to get from room $0$ (their bedroom) to $1$ (outdoors) and Bob to go from room $1$ (outdoors) to $0$ (bedroom) one week later.

Fortunately, Alice remembered that she could drop some of the keys on her way out for Bob to pick up on his way back. This way, they can both pass through the same doors. She, of course, cannot drop any keys in room $1$ (outdoors) since the neighbors could find them and break into their house.

Can you help Alice and Bob split their keys and plan their trip through the house?

### Task

You are given the description of Alice and Bob’s mansion: $m$ doors between $n$ rooms numbered $0$ to $n-1$, where $1$ is outdoors and $0$ is the bedroom. The $i$-th door can be opened with the key number $i$ (0-indexed).

You should first print two lines containing space-separated numbers of keys for Alice and Bob, respectively. It is fine if they do not use all the keys, but it is not allowed for them to both have a copy of the same key (or for one of them to have multiple copies of a key).

You should then print instructions that Alice and Bob will follow. First, print Alice’s movements from room $0$ to $1$ by printing commands of one of the two types:

- "MOVE $x$" to move to room $x$ (assuming that there is a door between Alice's current location and $x$ and that Alice has the key),
- "DROP $k_1$ $k_2$ …" to drop keys $k_1, k_2, …$ (printed as space-separated integers) in the room where Alice currently stands. This means that Alice no longer carries these keys.

Once Alice is done with her movements, print “DONE” in a new line. She should finish her movement in room $1$. It is fine if Alice passes through room $0$ or $1$ multiple times while following the printed instructions.

Second, print Bob’s movements from room $1$ to $0$ by printing commands of one of the two types:

- “MOVE $x$” to move to room $x$ (assuming that there is a door between Bob’s current location and $x$ and that Bob has the key),
- “GRAB” to grab any keys in the room where Bob is currently standing. Bob always grabs all the keys that Alice left in the room. If Alice left none, he does not grab any.

Once Bob is done with his movements, print “DONE” in a new line. He should finish his movement in room $0$. It is fine if Bob passes through room $0$ or $1$ multiple times while following the printed instructions.

Remarks: It is considered acceptable, albeit useless, to DROP an empty list of keys or to grab keys in a room that has no keys, or grab keys in room $1$ (i.e. outside).


## 输入格式

The first line contains integers $n$ and $m$, the number of rooms (outdoors included) and number of doors. This is followed by $m$ lines that describe the doors. The $i$-th line (count starting from $0$) is described by integers $a_i$, $b_i$, indicating that there is a door between rooms $a_i$ and $b_i$, opened with key $i$.

## 输出格式

First, print two lines, describing the split of keys. Then, print all the instructions for Alice and Bob, as described in the task description, one per line. If there is no solution, print "No solution" (without the quotes). If there are multiple valid solutions, any of them is accepted.

## 样例

### 样例输入 #1
```
5 5
0 1
1 2
2 3
3 4
4 1
```
### 样例输出 #1
```
0 1 2
3 4
MOVE 1
MOVE 2
MOVE 3
DROP 0
MOVE 2
MOVE 1
DONE
MOVE 4
MOVE 3
GRAB
MOVE 4
MOVE 1
MOVE 0
DONE
```
### 样例输入 #2
```
3 2
0 2
1 2
```
### 样例输出 #2
```
No solution
```
## 提示

### Comment

The first example represents the following floor plan, where blue numbers correspond to
key IDs required for each door:

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/rtcgheon.png)
:::

Alice takes keys $0$, $1$, and $2$ while Bob takes keys $3$ and $4$. Alice walks from $0$ to $1$, then to $2$, and then to $3$. There, she drops key $0$. She retraces her way back to $1$. Bob starts in $1$, walks to $4$, then to $3$, where he picks up key $0$. He retraces his way back to $1$, and with the newly picked-up key $0$, opens up the door to $0$.

In the second example, there is no way for both Alice and Bob to reach their destination. Note that Alice cannot drop keys in room $1$.


### Input and output limits

- $2 \leq n, m \leq 10^5$
- $0 \leq a_i, b_i < n$
- It is guaranteed that it’s always possible to reach any room from any other room if you have all the keys.
- Each pair of rooms is connected with at most one door.
- No room is connected to itself.
- Your program may print at most $4 \cdot 10^5$ instructions.


---

---
title: "[SEERC 2019] Game on a Tree"
layout: "post"
diff: 提高+/省选-
pid: P5801
tag: ['2019', 'ICPC']
---
# [SEERC 2019] Game on a Tree
## 题目描述

Alice 和 Bob 在树上玩游戏。最初的时候，树上的所有节点都是白色的。

Alice 先手，她可以任选一个节点并在该点上放置一个标记，该点变为黑色。在这之后，玩家轮流进行游戏，每一回合中玩家可以将标记从所在点移动到该点的白色祖先节点或儿子节点中，并将移动到的点变为黑色。无法进行移动的玩家即输。

谁会赢得游戏呢？

在有根树上，节点 $v$ 的*祖先节点*是指从树根到节点 $v$ 的路径上的任意点。

在有根树上，节点 $v$ 的*儿子节点*是指满足节点 $v$ 在从树根到节点 $w$ 路径上的任意点 $w$。

规定树的树根为点 $1$。
## 输入格式

第一行包含一个整数 $n \ (1 \leq n \leq 100 \ 000)$，代表树的节点数。

接下来的 $n-1$ 行中，每一行包含两个整数 $u$ 和 $v \ (1 \leq u, v \leq n)$，代表树上的一条边 $(u, v)$。数据保证这些边会构成一棵树。
## 输出格式

输出一行，如果 Alice 赢得了游戏，则输出 `Alice`，否则输出 `Bob`。
## 样例

### 样例输入 #1
```
4
1 2
2 3
3 4
```
### 样例输出 #1
```
Bob
```
### 样例输入 #2
```
7
2 1
2 6
1 3
2 5
7 2
2 4
```
### 样例输出 #2
```
Alice
```
## 提示

第一组样例中，树的形态是 $4$ 个点的一条链，所以 Bob 总是可以把标记移到最后的白点上。

第二组样例中，Alice 的最佳策略是先把标记放在点 $3$ 上，然后 $3$ 会变为黑色。Bob 只能移动标记到点 $1$ 上。Alice 可以选择点 $4, 5, 6$ 或 $7$ 来移动。Bob 只能选择 $2$。Alice 选择 $2$ 的任一白色子节点，Bob 就无法移动了。


---

---
title: "[SEERC 2018] Matrix Queries"
layout: "post"
diff: 提高+/省选-
pid: P5869
tag: ['2018', 'ICPC']
---
# [SEERC 2018] Matrix Queries
## 题目描述

给定一个 $2^n \times 2^n$ 的矩阵，最开始每个格子都是白色的。格子的颜色可以是白色或黑色。定义一个矩阵的*价值*为：

1. 如果矩阵是单色的，则它的价值为 $1$ 金币；
2. 否则，将矩阵分割成 $4$ 个大小相等的子矩阵，矩阵的价值为子矩阵的价值之和加 $1$ 金币。

给定 $q$ 个询问，每个询问给定一个行/列的编号 $x$，你需要改变这一行/列中每个格子的颜色（黑色变为白色，白色变为黑色），然后计算出改变之后的新矩阵的*价值*。
## 输入格式

第一行包含两个整数 $n$ 和 $q \ (0 \leq n \leq 20, 1 \leq q \leq 10^6)$，代表矩阵的大小为 $2^n \times 2^n$ 以及有 $q$ 个询问。

接下来 $q$ 行每行包含两个整数 $t$ 和 $x \ (0 \leq t \leq 1, 1 \leq x \leq 2^n)$。如果 $t=0$，则改变第 $x$ 行的颜色；否则，改变第 $x$ 列的颜色。
## 输出格式

对于每个询问，输出一行答案。
## 样例

### 样例输入 #1
```
2 7
1 3
0 2
1 1
1 4
0 4
0 3
1 1
```
### 样例输出 #1
```
13
17
21
17
21
17
13
```
## 提示

样例中，每个询问后的矩阵如下图所示：

![样例图](https://cdn.luogu.com.cn/upload/image_hosting/1cyezquq.png)


---

---
title: "[ICPC 2019 WF] Beautiful Bridges"
layout: "post"
diff: 提高+/省选-
pid: P6252
tag: ['计算几何', '2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Beautiful Bridges
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

What connects us all? Well, it is often bridges. Since ancient times, people have been building bridges for roads, for trains, for pedestrians, and as aqueducts to transport water. It is humanity's way of not taking inconvenient geography for an answer.

The company Arch Bridges Construction (ABC) specializes in—you guessed it—the construction of arch bridges. This classical style of bridge is supported by pillars that extend from the ground below the bridge. Arches between pillars distribute the bridge's weight onto the adjacent pillars.

The bridges built by ABC often have pillars spaced at irregular intervals. For aesthetic reasons, ABC's bridges always have semicircular arches, as illustrated in Figure B.1. However, while a bridge arch can touch the ground, it cannot extend below the ground. This makes some pillar placements impossible.

![](https://cdn.luogu.com.cn/upload/image_hosting/r95zwobd.png)

Given a ground profile and a desired bridge height $h$, there are usually many ways of building an arch bridge. We model the ground profile as a piecewise-linear function described by $n$ key points $(x_1, y_1),(x_2, y_2), \dots ,(x_n, y_n)$, where the $x-\text{coordinate}$ of a point is the position along the bridge, and the $y-\text{coordinate}$ is the elevation of the ground above sea level at this position along the bridge. The first and last pillars must be built at the first and last key points, and any intermediate pillars can be built only at these key points. The cost of a bridge is the cost of its pillars (which is proportional to their heights) plus the cost of its arches (which is proportional to the amount of material used). So a bridge with $k$ pillars of heights $h_1, \dots , h_k$ that are separated by horizontal distances $d_1, \dots , d_{k - 1}$ has a total cost of
$$\alpha \cdot \sum_{i = 1}^{k} h_i + \beta \cdot \sum_{i = 1}^{k - 1} d_i^2$$
for some given constants $\alpha$ and $\beta$. ABC wants to construct each bridge at the lowest possible cost.
## 输入格式

The first line of input contains four integers $n, h, \alpha, and \beta$, where $n$ ($2 \leq n \leq 10^4$) is the number of points describing the ground profile, $h$ ($1 \leq h \leq 10^5$) is the desired height of the bridge above sea level, and $\alpha, \beta$ ($1 \leq \alpha, \beta \leq 10^4$) are the cost factors as described earlier. Then follow $n$ lines, the $i^{\text{th}}$ of which contains two integers $x_i, y_i$ ($0 \leq x_1 < x_2 < . . . < x_n \leq 10^5$ and $0 \leq yi < h$), describing the ground profile.
## 输出格式

Output the minimum cost of building a bridge from horizontal position $x_1$ to $x_n$ at height $h$ above sea level. If it is impossible to build any such bridge, output `impossible`.
## 样例

### 样例输入 #1
```
5 60 18 2
0 0
20 20
30 10
50 30
70 20
```
### 样例输出 #1
```
6460
```
### 样例输入 #2
```
4 10 1 1
0 0
1 9
9 9
10 0
```
### 样例输出 #2
```
impossible
```
## 提示

Source: ICPC 2019 World Finals.
## 题目翻译

给定一个地形剖面图，用 $n$（$n≤10^4$）个点描述，点 $i$ 和点 $i+1$ 之间有直线连接的地面。

你需要建一座拱桥，连接点 $1$ 和点 $n$，桥面的高度为 $h$。

你可以在桥中间建若干个柱子，以分配重量，柱子只能恰好建在给出的 $n$ 个点上（点 $1$ 和点 $n$ 上必须有柱子）。

相邻的两根柱子之间需要建一个半圆形的拱，准确地说，拱的半径为两根柱子之间的距离的一半，并且与两根柱子和桥面相切。

拱可以与地面相切，但不能相交。

同时，桥的花费与柱子高度和拱面积有关，具体地，给出两个参数 $α$ 和 $β$，则花费为：

$$\alpha \cdot \sum_{i = 1}^{k} h_i + \beta \cdot \sum_{i = 1}^{k - 1} d_i^2$$

其中 $k$ 为柱子数量，$h_i$ 为第 $i$ 个柱子的高度，$d_i$ 为第 $i$ 个柱子到第 $i+1$ 个柱子的距离。

问是否可以建出桥，若可以，问最小花费，否则输出
`impossible` 。


---

---
title: "[ICPC 2019 WF] Hobson's Trains"
layout: "post"
diff: 提高+/省选-
pid: P6258
tag: ['2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Hobson's Trains
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

Mr. Hobson has retired from running a stable and has invested in a more modern form of transport,trains. He has built a rail network with n stations. However, he has retained his commitment to free the passenger from the burden of too many choices: from each station, a passenger can catch a train to exactly one other station. Such a journey is referred to as a **$leg$**. Note that this is a one-way journey, and it might not be possible to get back again.

Hobson also offers exactly one choice of ticket, which allows a passenger to travel up to $k$ legs in one trip. At the exit from each station is an automated ticket reader (only one, so that passengers do not need
to decide which to use). The reader checks that the distance from the initial station to the final station does not exceed $k$ legs.

Each ticket reader must be programmed with a list of valid starting stations, but the more memory this list needs, the more expensive the machine will be. Help Hobson by determining, for each station $A$, the
number of stations (including $A$) from which a customer can reach $A$ in at most $k$ legs.

![](https://cdn.luogu.com.cn/upload/image_hosting/l1j8vud2.png)
## 输入格式

The first line of input contains two integers $n$ and $k$, where $n$ $(2 \leq n \leq 5\times10^5)$ is the number of stations and $k$ $(1 \leq k \leq n − 1)$ is the maximum number of legs that may be traveled on a ticket. Then follow $n$ lines, the $i^{th}$ of which contains an integer $d_i$ $(1 \leq d_i \leq n$ and $d_i ≠ i)$, the station which may be reached from station $i$ in one leg.

## 输出格式

Output $n$ lines, with the $i^{th}$ line containing the number of stations from which station $i$ can be reached in at most $k$ legs.

## 样例

### 样例输入 #1
```
6 2
2
3
4
5
4
3

```
### 样例输出 #1
```
1
2
4
5
3
1
```
### 样例输入 #2
```
5 3
2
3
1
5
4

```
### 样例输出 #2
```
3
3
3
2
2
```
## 提示

Source: ICPC World Finals 2019.
## 题目翻译

**【题目描述】**

Hobson 先生从管理马厩的工作中退休后，投资于一种更加现代的交通方式：火车。

他已经修建了一个包含 $n$ 个火车站的铁路网。然而，他兑现了让乘客摆脱选择困难症的承诺：对于每个站点，乘客只能乘坐火车前往一个站点，别无其它选择。

这样的一段旅程被称作一趟。要注意这是单向的旅程，可能无法再回到出发点。

Hobson 同样也只提供一种车票，允许乘客一次旅行的距离不超过 $k$ 趟。在每个站点的出口会有一个自动读票机（只有一个，所以乘客就不用纠结于要用哪个）。机器会检查从始发站到到达站的距离是否不超过 $k$ 趟。

每个读票机必须编入一个合法始发站列表，但是列表消耗的存储空间越多，机器就越贵。

请帮助 Hobson 先生确定：对于每个站点 $A$，能够在最多 $k$ 趟的旅程中到达 $A$ 的站点个数（包含 $A$ 本身）。

![](https://cdn.luogu.com.cn/upload/image_hosting/1hewt4ho.png)

上图为样例输入 1 对应的示意图。每个圆圈代表了一个站点，圆圈旁边的数字为当 $k=2$ 时需要编入读票机的站点编号。

**【输入格式】**

第一行包含两个整数 $n, k$，$n$ 为站点个数，$k$ 为一张票允许旅行的最多趟数。  
接下来 $n$ 行，第 $i$ 行包含一个整数 $d_i$，表示第 $i$ 个站点经过一趟到达的站点。

**【输出格式】**

输出 $n$ 行，第 $i$ 行输出能在 $k$ 趟内到达站点 $i$ 的站点数目。

**【译者注】**

在不侵犯原题版权的情况下，本题面中文翻译基于[知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-sa/4.0/)发布，注明出处时需指向本题链接。

Translate By @小粉兔 


---

---
title: "[ICPC 2019 WF] Karel the Robot"
layout: "post"
diff: 提高+/省选-
pid: P6259
tag: ['模拟', '2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Karel the Robot
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。
## 题目描述

Did you know that the word "robot" is almost 100 years old? It was first introduced in 1920, in the science-fiction theatrical play $R.U.R.$ , written by Karel Capek. As a tribute to this Czech writer, an educational programming language was named Karel many years later at Stanford University. Your task is to implement an interpreter of a simplified version of this programming language.

The Karel programming language controls a robot named Karel, who lives in a grid of unit squares. Some of the squares are free, while others contain a barrier. Karel always occupies one of the free squares and faces one of the four cardinal directions. The two basic commands are "move forward" and "turn left." The language also provides simple conditional and looping statements. The main educational potential of the language lies in the possibility of defining new procedures for more complex tasks.

Our simplified version of the language can be described by the following grammar:

```plain
<program> := "" | <command> <program>
<command> := "m" | "l" | <proc-call> |
             "i" <condition> "(" <program> ")(" <program> ")" |
             "u" <condition> "(" <program> ")"
<condition> := "b" | "n" | "s" | "e" | "w"
<proc-call> := <uppercase-letter>
<proc-def> := <uppercase-letter> "=" <program>
```
There are five types of commands:

- $\texttt m$ ("move forward") advances Karel's position by one grid square in its current heading, unless there is a barrier, in which case the command has no effect.
- $\texttt l$ ("turn left") makes Karel turn left $90$ degrees.
- $\texttt X$ where $\texttt X$ is any uppercase letter, invokes the procedure named $\texttt X$. 
- $\texttt i$ ("if") followed by a single-letter condition, and two programs in parentheses. If the condition is satisfied, the first program is executed. Otherwise, the second program is executed.
- $\texttt u$ ("until") followed by a single-letter condition, and a program in parentheses. If the condition is satisfied, nothing is done. Otherwise, the program is executed and then the command is repeated.

A condition can be either '$b$', which is satisfied if and only if there is a barrier in the next square in Karel's current heading, or one of the four directional letters `n`, `s`, `e`, or `w`, which is satisfied if and only if Karel's current heading is north, south, east, or west, respectively.


For instance, a simple program `ub(m)` can be understood to mean: “keep moving forward until there is a barrier," while `un(l)` means "turn to the north." A procedure definition `R=lll` defines a new procedure `R` which effectively means "turn right."

## 输入格式

The first line of input contains four integers $r, c, d$ and $e$, where $r$ and $c$ $(1 \leq r, c \leq 40)$ are the dimensions of the grid in which Karel lives, $d$ $(0 \leq d \leq 26)$ is the number of procedure definitions, and $e$ $(1 \leq e \leq 10)$ is the number of programs to be executed.

Then follow $r$ lines describing the grid (running north to south), each containing c characters (running west to east), each character being either `.` (denoting a free square) or `#` (denoting a barrier). All squares outside this given area are considered barriers, which means Karel may never leave the area.

Each of the next $d$ lines contains a procedure definition, associating a procedure name (one uppercase letter) with a program forming the procedure body. No procedure name is defined more than once. Procedure bodies may contain invocations of procedures that have not yet been defined.

The last $2e$ lines describe the programs to be executed. Each such description consists of a pair of lines. The first line of each pair contains two integers $i$ and $j$ and a character $h$, where $i$ $(1 \leq i\leq r)$ is the row and $j$ $(1 \leq j \leq c)$ is the column of Karel's initial position, and $h \in \{ \texttt n, \texttt s, \texttt e, \texttt w\}$ represents Karel's initial heading. It is guaranteed that the initial position is a free square. The second line of each pair contains a program to be executed from that initial position.

All procedure bodies and all programs to be executed are at least $1$ and at most $100$ characters long, syntactically correct, and only contain invocations of procedures that are defined. The lines with procedure definitions and programs to be executed contain no whitespace characters.

## 输出格式

For each program execution, output the final position of Karel after the complete program is executed from the respective initial position. Follow the format used to describe initial positions, that is, two numbers and a directional character. If a particular execution never terminates, output `inf` instead.

## 样例

### 样例输入 #1
```
4 8 5 7
.......#
..#....#
.###...#
.....###
R=lll
G=ub(B)
B=ub(m)lib(l)(m)
H=ib()(mmHllmll)
I=III
1 1 w
G
1 1 e
G
2 2 n
G
2 6 w
BR
4 1 s
ib(lib()(mmm))(mmmm)
1 1 e
H
2 2 s
I

```
### 样例输出 #1
```
1 1 w
inf
1 1 w
2 4 s
4 4 e
1 4 e
inf

```
## 提示

Source: ICPC World Finals 2019.
## 题目翻译

## 题目描述

你知道“机器人”这个词已经有100年的历史了吗？它最早出现在1920年的科幻戏剧《R.U.R.R.U.R.》中，卡雷尔·卡佩克写的。为了向这位捷克作家致敬，一种教育编程语言在多年后在斯坦福大学被命名为Karel。您的任务是实现此编程语言简化版本的解释器。

Karel编程语言控制着一个名叫Karel的机器人，他生活在一个单位方格的网格中。一些方块是自由的，而另一些方块包含障碍物。卡雷尔总是占据一个自由正方形，面向四个基本方向之一。两个基本命令是“向前移动”和“向左转”。该语言还提供简单的条件语句和循环语句。该语言的主要教育潜力在于为更复杂的任务定义新程序的可能性。

我们简化的语言版本可以用以下语法描述：

```
<program> := "" | <command> <program>
<command> := "m" | "l" | <proc-call> |
             "i" <condition> "(" <program> ")(" <program> ")" |
             "u" <condition> "(" <program> ")"
<condition> := "b" | "n" | "s" | "e" | "w"
<proc-call> := <uppercase-letter>
<proc-def> := <uppercase-letter> "=" <program>
```
有五种类型的命令：

m（“向前移动”）在当前航向中将Karel的位置向前移动一个方格，除非有障碍物，在这种情况下，命令无效。

l（“左转”）使卡雷尔左转9090度。

x，其中x是任何大写字母，调用名为x的过程。

i（“if”）后跟一个单字母条件，括号中有两个程序。如果满足条件，则执行第一个程序。否则，执行第二个程序。

u（“直到”），后跟一个单字母条件，括号中是一个程序。如果条件满足，则什么也不做。否则，将执行该程序，然后重复该命令。

条件可以是“b”，当且仅当Karel当前航向的下一个方格中存在障碍物时满足，或者四个方向字母n、s、e或w中的一个，当且仅当Karel当前航向分别为北、南、东或西时满足。

例如，一个简单的程序ub（m）可以理解为“继续前进，直到有障碍物为止”，而un（l）表示“转向北方”。程序定义R=lll定义了一个新的程序R，它实际上意味着“右转”

输入的第一行包含四个整数r、c、dr、c、d和e，其中r和c（1≤r、 c≤40）是Karel居住的网格的尺寸，d（0≤D≤26）是程序定义的数量，e（1）≤E≤10） 是要执行的程序数。

然后沿着描述网格的r行（从北到南），每个包含c字符（从西到东），每个字符都是。（表示自由正方形）或#（表示障碍物）。该区域以外的所有广场都被视为障碍物，这意味着卡雷尔可能永远不会离开该区域。

接下来的d行中的每一行都包含一个过程定义，将过程名称（一个大写字母）与构成过程主体的程序相关联。没有多次定义过程名称。过程主体可能包含尚未定义的过程调用。

最后两行描述了要执行的程序。每个这样的描述由一对行组成。每对的第一行包含两个整数ii和jj以及一个字符hh，其中i（1≤我≤r） 是行和j（1）≤J≤c） 是Karel初始位置的列，h∈{n，s，e，w}代表Karel的初始标题。保证初始位置为自由正方形。每对的第二行包含从该初始位置执行的程序。

所有要执行的过程体和所有程序的长度至少为11个字符，最多为100100个字符，语法正确，并且仅包含已定义过程的调用。包含要执行的过程定义和程序的行不包含空格字符。

输出格式

对于每个程序执行，在从各自的初始位置执行完整程序后，输出Karel的最终位置。遵循用于描述初始位置的格式，即两个数字和一个方向字符。如果特定执行从未终止，则改为输出inf。


---

---
title: "[ICPC 2014 WF] Crane Balancing"
layout: "post"
diff: 提高+/省选-
pid: P6894
tag: ['数学', '计算几何', '2014', 'ICPC']
---
# [ICPC 2014 WF] Crane Balancing
## 题目描述

Wherever there is large-scale construction, you will find cranes that do the lifting. One hardly ever thinks about what marvelous examples of engineering cranes are: a structure of (relatively) little weight that can lift much heavier loads. But even the best-built cranes may have a limit on how much weight they can lift.

The Association of Crane Manufacturers (ACM) needs a program to compute the range of weights that a crane can lift. Since cranes are symmetric, ACM engineers have decided to consider only a cross section of each crane, which can be viewed as a polygon resting on the $x$-axis.

![](https://cdn.luogu.com.cn/upload/image_hosting/2lyejm47.png)

   Figure 1: Crane cross section 

Figure 1 shows a cross section of the crane in the first sample input. Assume that every $1 \times 1$ unit of crane cross section weighs 1 kilogram and that the weight to be lifted will be attached at one of the polygon vertices (indicated by the arrow in Figure 1). Write a program that determines the weight range for which the crane will not topple to the left or to the right.
## 输入格式

The input consists of a single test case. The test case starts with a single integer $n$ ($3 \le n \le 100$), the number of points of the polygon used to describe the crane’s shape. The following $n$ pairs of integers $x_ i, y_ i$ ($-2\, 000 \le x_ i \le 2\, 000, 0 \le y_ i \le 2\, 000$) are the coordinates of the polygon points in order. The weight is attached at the first polygon point and at least two polygon points are lying on the $x$-axis.
## 输出格式

Display the weight range (in kilograms) that can be attached to the crane without the crane toppling over. If the range is $[a,b]$, display $\lfloor a \rfloor $ .. $\lceil b \rceil $. For example, if the range is $[1.5,13.3]$, display 1 .. 14. If the range is $[a,\infty )$, display $\lfloor a \rfloor $ .. inf. If the crane cannot carry any weight, display unstable instead.
## 样例

### 样例输入 #1
```
7
50 50
0 50
0 0
30 0
30 30
40 40
50 40

```
### 样例输出 #1
```
0 .. 1017

```
### 样例输入 #2
```
7
50 50
0 50
0 0
10 0
10 30
20 40
50 40

```
### 样例输出 #2
```
unstable

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

无论哪里有大规模的施工，您都会发现起重机可以起重。人们几乎从未想过工程起重机的奇妙例子是什么：一种（相对）重量很小的结构，可以举起更重的负载。但即使是最好的起重机也可能对它们可以举起的重量有限制。

起重机制造商协会（ACM）需要一个程序来计算起重机可以提升的重量范围。由于起重机是对称的，ACM工程师决定只考虑每台起重机的横截面，这可以看作是一个多边形，位于x-轴。

图1显示了第一个样本输入中起重机的横截面。

假设每个1×1单位起重机横截面重1公斤，要提升的重量将附着在其中一个多边形顶点（如图1中的箭头所示）。编写一个程序，确定起重机不会向左或向右倾倒的重量范围。

输入由单个测试用例组成。测试用例以单个整数n开头,用于描述起重机形状的多边形的点数。以下n对整数是按顺序排列的点的坐标。权重附着在第一个多边形点上，并且至少有两个多边形点位于x-轴。

输出格式

显示可在起重机不倒塌的情况下连接到起重机的重量范围（以千克为单位）。如果范围是 [a,b], 显示⌊a⌋ .. ⌈b⌉. 例如，如果范围是[1.5,13.3], 显示 1 ..14. 如果范围是[a,∞), 显示⌊a⌋ .. inf. 如果起重机不能承载任何重量，请显示unstable.


说明/提示

时间限制： 1000 ms， 内存限制： 1048576 kB.

2014年国际大学生编程大赛（ACM-ICPC）世界总决赛


---

---
title: "[ICPC 2014 WF] Game Strategy"
layout: "post"
diff: 提高+/省选-
pid: P6895
tag: ['2014', 'ICPC']
---
# [ICPC 2014 WF] Game Strategy
## 题目描述

Alice and Bob are playing a board game. The board is divided into positions labeled $a, b, c, d, \dots $ and the players use a gamepiece to mark the current position. Each round of the game consists of two steps:

Alice makes a choice. Depending on the current position, she has different options, where each option is a set of positions. Alice chooses one set $S$ among the available sets of positions.

Bob makes a choice. His choice is one position $p$ from the set $S$ that Alice chose in step 1. Bob moves the gamepiece to position $p$, which is the position for the start of the next round.

Prior to the first round, each player independently selects one of the positions and reveals it at the start of the game. Bob’s position is where the game starts. Alice wins the game if she can force Bob to move the gamepiece to the position she has chosen. To make things interesting, they have decided that Bob will pay Alice a certain amount if he loses, but Alice must pay Bob a certain amount after every round. The game now ends if Alice’s position is reached or when Alice runs out of cash.

Both Alice and Bob play optimally: Alice will always choose an option that will lead to her winning the game, if this is possible, and Bob will always try to prevent Alice from winning.

For all possible start and end positions, Alice would like you to determine whether she can win the game and if so, how many rounds it will take.
## 输入格式

The input consists of a single test case. The first line contains the number of positions $n$ ($1 \leq n \leq 25$). The $n$ positions are labeled using the first $n$ letters of the English alphabet in lowercase. The rest of the test case consists of $n$ lines, one for each position $p$, in alphabetical order. The line for position $p$ contains the options available to Alice in position $p$. It starts with the number of options $m$ ($1 \leq m < 2^ n$), which is followed by $m$ distinct strings, one for each option. Each string contains the positions available to Bob if Alice chooses that option. The string has at least $1$ character, the characters (which correspond to valid board positions) are in alphabetical order, and no characters are duplicated. The total number of options for the test case is at most $10^6$.
## 输出格式

For each position $p$ in alphabetical order, display one line. In that line, for each position $q$ in alphabetical order display the minimal number of rounds in which Alice can be guaranteed to arrive at position $q$ when starting the game in position $p$, or $-1$ if Alice cannot be guaranteed to reach $q$ from $p$.
## 样例

### 样例输入 #1
```
2
2 ab b
1 b

```
### 样例输出 #1
```
0 1 
-1 0

```
### 样例输入 #2
```
3
1 b
2 b a
2 ab ac

```
### 样例输出 #2
```
0 1 -1 
1 0 -1 
2 2 0

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

### **题目描述**

Alice 和 Bob 正在玩一款棋盘游戏。棋盘被分成了标有 $a,b,c,d,...$ 的位置，玩家们使用游戏棋子来标记当前位置。游戏的每一轮包括两个步骤：

Alice 行动。根据当前位置，她有不同的选择，每个选择都是一组位置。Alice 将从可用的位置集合中选择一个集合 $S$。

Bob 行动。他的选择是集合 $S$ 中的一个位置 $p$。Bob 将游戏棋子移动到位置 $p$，这会是下一轮游戏的起始位置。

在第一轮之前，每个玩家独立选择一个位置并在游戏开始时公开位置。Bob 的位置是游戏开始的地方。如果 Alice 能够迫使 Bob 将游戏棋子移动到她选择的位置，Alice 就赢得了比赛。为了使事情更有趣，他们决定如果 Bob 输了，他将支付给 Alice 一定金额，但 Alice 必须在每轮之后向 Bob 支付一定金额。如果 Bob 到达 Alice 的位置或者 Alice 没钱了，游戏就结束了。Alice 和 Bob 都采取最佳策略：如果可能的话，Alice 总是选择会能让她赢得比赛的方案，而 Bob 总是试图阻止 Alice 获胜。对于所有可能的起始和结束位置，Alice 希望你确定她是否能够赢得比赛，如果可以，需要多少轮才能赢得比赛。

### **输入格式**

输入由单组数据组成。第一行包含位置数 $n$ $(1\le n\le 25)$，这些位置用英文小写字母的前 $n$ 个字母标记。接下来 $n$ 行，每行表示位置 $p$，按字母顺序排列。位置 $p$ 这一行包含 $Alice$ 在该位置的可选项。每行首先输入一个数 $m$ $(1 \le m < 2^n)$，后跟 $m$ 个不同字符串，每个字符串表示 Alice 选择该方案时 Bob 可移动到的位置。字符串至少包含 $1$ 个字符，这些字符（对应有效的棋盘位置）按字母顺序排列，没有重复字符。数据的方案总数最多为 $10^6$。

### **输出格式**

对于每一个 $p$ 单独输出一行。在该行中，按字母顺序输出每个位置 $q$ 表示 Alice 开始游戏时可以保证到达的最小轮次，或者如果 Alice 不能保证从 $p$ 到达 $q$，则显示 $-1$。

### **说明/提示**

时间限制： $5000$ ms，空间限制：$1048576$ kB。

来源：International Collegiate Programming Contest (ACM-ICPC) World Finals 2014


---

---
title: "[ICPC 2014 WF] Surveillance"
layout: "post"
diff: 提高+/省选-
pid: P6902
tag: ['2014', '倍增', 'ICPC']
---
# [ICPC 2014 WF] Surveillance
## 题目描述

The International Corporation for Protection and Control (ICPC) develops efficient technology for, well, protection and control. Naturally, they are keen to have their own headquarters protected and controlled. Viewed from above, the headquarters building has the shape of a convex polygon. There are several suitable places around it where cameras can be installed to monitor the building. Each camera covers a certain range of the polygon sides (building walls), depending on its position. ICPC wants to minimize the number of cameras needed to cover the whole building.
## 输入格式

The input consists of a single test case. Its first line contains two integers $n$ and $k$ ($3 \le n \le 10^6$ and $1 \le k \le 10^6$), where $n$ is the number of walls and $k$ is the number of possible places for installing cameras. Each of the remaining $k$ lines contains two integers $a_ i$ and $b_ i$ ($1 \le a_ i, b_ i \le n$). These integers specify which walls a camera at the $i^{th}$ place would cover. If $a_ i \le b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le b_ i$. If $a_ i > b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le n$ or $1 \le j \le b_ i$.
## 输出格式

Display the minimal number of cameras that suffice to cover each wall of the building. The ranges covered by two cameras may overlap. If the building cannot be covered, display impossible instead.
## 样例

### 样例输入 #1
```
100 7
1 50
50 70
70 90
90 40
20 60
60 80
80 20

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
8 2
8 3
5 7

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
8 2
8 4
5 7

```
### 样例输出 #3
```
2

```
## 提示

Time limit: 4000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

### 题目描述
给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的满足环被完全覆盖的区域数量。
### 输入格式
第一行两个整数 $n$，$k$。
接下来 $k$ 行，每行两个整数表示一个区域。
### 输出格式
若环不可能被完全覆盖，输出 `impossible`；否则输出一个整数，表示最少的区域数量。


---

---
title: "[ICPC 2015 WF] Cutting Cheese"
layout: "post"
diff: 提高+/省选-
pid: P6907
tag: ['2015', 'Special Judge', 'ICPC']
---
# [ICPC 2015 WF] Cutting Cheese
## 题目描述

 ![](https://vj.z180.cn/5f637f1053193ffad543787cd8bc5b2a?v=1601501213)  

Of course you have all heard of the International Cheese Processing Company. Their machine for cutting a piece of cheese into slices of exactly the same thickness is a classic. Recently they produced a machine able to cut a spherical cheese (such as Edam) into slices – no, not all of the same thickness, but all of the same weight! But new challenges lie ahead: cutting Swiss cheese. 

Swiss cheese such as Emmentaler has holes in it, and the holes may have different sizes. A slice with holes contains less cheese and has a lower weight than a slice without holes. So here is the challenge: cut a cheese with holes in it into slices of equal weight.

By smart sonar techniques (the same techniques used to scan unborn babies and oil fields), it is possible to locate the holes in the cheese up to micrometer precision. For the present problem you may assume that the holes are perfect spheres.

Each uncut block has size $100 \times 100 \times 100$ where each dimension is measured in millimeters. Your task is to cut it into $s$ slices of equal weight. The slices will be $100$ mm wide and $100$ mm high, and your job is to determine the thickness of each slice.
## 输入格式

The first line of the input contains two integers $n$ and $s$, where $0 \leq n \leq 10\, 000$ is the number of holes in the cheese, and $1 \le s \le 100$ is the number of slices to cut. The next $n$ lines each contain four positive integers $r$, $x$, $y$, and $z$ that describe a hole, where $r$ is the radius and $x$, $y$, and $z$ are the coordinates of the center, all in micrometers.

The cheese block occupies the points $(x,y,z)$ where $0 \le x,y,z \le 100\, 000$, except for the points that are part of some hole. The cuts are made perpendicular to the $z$ axis.

You may assume that holes do not overlap but may touch, and that the holes are fully contained in the cheese but may touch its boundary.
## 输出格式

Display the $s$ slice thicknesses in millimeters, starting from the end of the cheese with $z=0$. Your output should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
0 4

```
### 样例输出 #1
```
25.000000000
25.000000000
25.000000000
25.000000000

```
### 样例输入 #2
```
2 5
10000 10000 20000 20000
40000 40000 50000 60000

```
### 样例输出 #2
```
14.611103142
16.269801734
24.092457788
27.002992272
18.023645064

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

# 题目背景

当然，你们都已经听说过国际奶酪加工公司。他们将一块奶酪切成完全相同厚度的薄片的机器是一个经典。最近，他们生产了一种能将球形奶酪（比如荷兰球形干酪）切成薄片的机器——不，不是所有的厚度都一样，而是所有的质量都一样！但是新的挑战摆在面前：切瑞士奶酪。

瑞士奶酪，比如瑞士多孔奶酪，在其中有很多洞，并且这些洞大小可能不同。一片有空洞的奶酪比一片没有洞的奶酪含量更少，质量更轻。所以这是一个挑战：将一块有空洞的奶酪切成质量相同的薄片。

通过智能声呐技术（与过去常常探测未出生的婴儿和油田的技术一样），可以将空洞定位精确到微米级别。对于目前的问题，你可以认为这些洞是完美球体。

每一个未切割的奶酪块尺寸为 $100\times100\times100$，其中单位为毫米。你的任务是把它切成 $s$ 个质量相等的薄片。这些薄片宽度和高度都应当是 $100\operatorname{mm}$，然后你的工作是求出每个薄片的厚度。

## 简化题意

有一个 $100 \text{mm} \times 100 \text{mm} \times 100 \text{mm}$ 的质地均匀的正方体，垂直于 $z$ 轴的切成 $s$ 个薄片，使得每一片质量相等。每一薄片宽度和高度都是 $100 \text{mm}$，请从奶酪底端 $z=0$ 开始依次输出每一片的厚度。

# 输入格式

输入的第一行包含两个整数 $n$ 和 $s$，其中 $0 \leq n \leq 10000$ 表示奶酪中洞的个数，然后 $1 \le s \le 100$ 表示要切割的薄片数。接下来的 $n$ 行分别包含四个描述空洞的正整数 $r,x,y,z$，其中 $r$ 表示半径，$x$、$y$ 和 $z$ 表示空洞中心坐标，都以微米为单位。

奶酪的圆心 $(x,y,z)$ 中 $0 \le x,y,z \le 100000$，除了某个孔的部分点（即某个孔的部分点可能超出该范围，但是圆心一定在这之内）。刀切的方向垂直于 $z$ 轴。

你可以认为这些洞没有重叠但是可能接触，并且这些孔完全包含在奶酪里，但可能接触奶酪的边界。

# 输出格式

输出保留 $9$ 位小数。从奶酪底端 $z=0$ 开始，以毫米为单位输出 $s$ 个薄片厚度。相对误差或绝对误差不能超过 $10^{-6}$。

# 说明/提示

时间限制：$3000 \text{ms}$，空间限制：$1048576\text{kB}$。

2015年国际大学生编程大赛（ACM-ICPC）世界总决赛


---

---
title: "[ICPC 2015 WF] Evolution in Parallel"
layout: "post"
diff: 提高+/省选-
pid: P6908
tag: ['2015', 'Special Judge', 'ICPC']
---
# [ICPC 2015 WF] Evolution in Parallel
## 题目描述

It is 2178, and alien life has been discovered on a distant planet. There seems to be only one species on the planet and they do not reproduce as animals on Earth do. Even more amazing, the genetic makeup of every single organism is identical!

The genetic makeup of each organism is a single sequence of nucleotides. The nucleotides come in three types, denoted by ‘A’ (Adenine), ‘C’ (Cytosine), and ‘M’ (Muamine). According to one hypothesis, evolution on this planet occurs when a new nucleotide is inserted somewhere into the genetic sequence of an existing organism. If this change is evolutionarily advantageous, then organisms with the new sequence quickly replace ones with the old sequence.

It was originally thought that the current species evolved this way from a single, very simple organism with a single-nucleotide genetic sequence, by way of mutations as described above. However, fossil evidence suggests that this might not have been the case. Right now, the research team you are working with is trying to validate the concept of “parallel evolution” – that there might actually have been two evolutionary paths evolving in the fashion described above, and eventually both paths evolved to the single species present on the planet today. Your task is to verify whether the parallel evolution hypothesis is consistent with the genetic material found in the fossil samples gathered by your team.
## 输入格式

The input begins with a number $n$ ($1\le n\le 4\, 000$) denoting the number of nucleotide sequences found in the fossils. The second line describes the nucleotide sequence of the species currently living on the planet. Each of the next $n$ lines describes one nucleotide sequence found in the fossils.

Each nucleotide sequence consists of a string of at least one but no more than $4\, 000$ letters. The strings contain only upper-case letters A, C, and M. All the nucleotide sequences, including that of the currently live species, are distinct.
## 输出格式

Display an example of how the nucleotide sequences in the fossil record participate in two evolutionary paths. The example should begin with one line containing two integers $s_1$ and $s_2$, the number of nucleotide sequences in the fossil record that participate in the first path and second path, respectively. This should be followed by $s_1$ lines containing the sequences attributed to the first path, in chronological order (from the earliest), and then $s_2$ lines containing the sequences attributed to the second path, also in chronological order. If there are multiple examples, display any one of them. If it is possible that a sequence could appear in the genetic history of both species, your example should assign it to exactly one of the evolutionary paths.

If it is impossible for all the fossil material to come from two evolutionary paths, display the word impossible.
## 样例

### 样例输入 #1
```
5
AACCMMAA
ACA
MM
ACMAA
AA
A

```
### 样例输出 #1
```
1 4
MM
A
AA
ACA
ACMAA

```
### 样例输入 #2
```
3
ACMA
ACM
ACA
AMA

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
1
AM
MA

```
### 样例输出 #3
```
impossible

```
### 样例输入 #4
```
4
AAAAAA
AA
AAA
A
AAAAA

```
### 样例输出 #4
```
0 4
A
AA
AAA
AAAAA

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

### 题目背景

公元2178年，人类在一颗遥远的行星上发现了外星生命。但是似乎这颗行星上只有单一物种而且它们并不像地球上的动物一样繁殖。更神奇的是，每个生物的基因构成是完全相同的！

每个生物的基因构成是单一核苷酸序列。在它们基因中有三种核苷酸，表示为‘A’  (腺嘌呤，Adenine), ‘C’ (胞嘧啶，Cytosine), and ‘M’ (膜嘌呤，Muamine)。根据某种假说，在这颗星球上只有某个新的核苷酸插入现存的生物基因序列某处时才会出现进化。如果这个改变是对进化有利的，这个带有新基因序列的生物会迅速取代没有变异的旧生物。

我们起初认为这种生物是从基因序列只含有单一核苷酸的生物经过多次上述的变异进化而来。然而化石证据表明可能并不是一直是这种情况。目前，与你协作的科研团队正在尝试证实“平行进化”的概念。“平行进化”指可能事实上有两条如同上述的进化路径，最终他们都进化成了这颗行星如今的物种。你的任务是证实平行进化假说是否与你的团队在化石中发现的遗传物质样本一致。 

( TRANSLATED by  [@MolotovM](https://www.luogu.com.cn/user/99461))

### 题目含义

给定1个字符串，n个字符串，求不多于两个的字符串的子串包含其他所有字符串，且这不多于两个的字符串都是给定字符串的子串。

### 输入格式

第一行输入为一个整数$n (1\le n\le 4\, 000)$，表示化石中发现的遗传物质样本数量

第二行输入为给定字符串表示当前生物的基因序列

接下来n行，每行输入一个字符串，表示化石中发现的遗传物质样本

每个遗传物质样本由不超过4000个字母构成，且只包含大写字母A,C和M。

包括当前生物基因序列的所有基因序列都是独特的。

### 输出格式

输出每个化石中的遗传物质样本是怎样参与两条进化路径的。

第一行包含两个整数$s_1,s_2$为两条进化路径的化石数量。

接下来$s_1$行每行包含一个字符串表示第一条进化路径中的遗传物质样本

接下来$s_2$行每行包含一个字符串表示第二条进化路径中的遗传物质样本

样本按年代顺序输出(从最早的开始)，如果一个样本可以同时出现在两条进化路径中，你需要表明它具体参与了哪种进化。

如果不可能满足有不多于两条进化路径，输出"impossible"。

### 时空限制

时间限制: 2000 ms

空间限制: 1048576 kB


---

---
title: "[ICPC 2015 WF] Qanat"
layout: "post"
diff: 提高+/省选-
pid: P6911
tag: ['2015', 'Special Judge', 'ICPC']
---
# [ICPC 2015 WF] Qanat
## 题目描述

A qanat is an irrigation system widely used to deliver water in hot, arid climates. The technology was originally developed by Persians over 2000 years ago. In Morocco, qanats are known as khettara and are still used today in the southern part of the country.

The basic feature of a qanat is an essentially horizontal channel that brings water from an underground water source to an outlet near a civilization. There is also a shaft known as a mother well that rises vertically from the underground water source to the surface of a mountain or hill. Creating such a system is extremely expensive, and was especially so in ancient times, since all of the materials excavated from the channel and mother well must be carried above ground, either through the channel outlet or the top of the mother well. To aid in the construction, there are often one or more additional vertical shafts placed at strategic locations above the underground channel. Although these shafts must also be excavated, they provide a means for lifting additional dirt from the horizontal channel as illustrated in Figure 1.

  ![](https://vj.z180.cn/4dea3d690f1497e79acad3985c8a9915?v=1603314265) 

   Figure 1: An illustration of a qanat. 

For this problem, model the cross-section of a qanat as shown in Figure 2, with the channel outlet at $(0,0)$, the water source at $(w,0)$, and the top of the mother well at $(w,h)$ with $w > h$. The surface of the mountain extends along a straight line from $(w,h)$ to $(0,0)$.

  ![](https://vj.z180.cn/a58cc42544b91877083973369ca77d3c?v=1603314265) 

   Figure 2: A simplified model of a qanat cross-section. 

Every qanat must have a vertical mother well from the water source to the mountain surface above, along with $n$ additional vertical shafts. The channel and all shafts are modeled as line segments. Your goal is to determine the placement for those additional shafts so as to minimize the overall excavation cost. This cost is equal to the sum of the distances that each piece of excavated dirt must be transported to reach the surface (using any combination of horizontal and vertical movement). For example, the cost of excavating a continuous section of dirt starting from the surface and going along a path of length $\ell $ (possibly including turns) is $\int _0^{\ell } x \, dx = \frac{1}{2} \ell ^2$.
## 输入格式

The input consists of a single line containing three integers $w$ ($1 \le w \le 10\, 000$), $h$ ($1 \le h < w$), and $n$ ($1 \le n \le 1\, 000$). The value $w$ is the horizontal distance from the water source to the qanat outlet. The value $h$ is the vertical distance from the water source to the mountain surface. The value $n$ is the number of vertical shafts that must be used in addition to the mother well.
## 输出格式

First, display the minimum overall excavation cost. Next, display the $x$-coordinates, in increasing order, for $n$ optimally placed vertical shafts. If $n > 10$, display only the first $10$ $x$-coordinates. Answers within an absolute or relative error of $10^{-4}$ will be accepted. You may assume that there is a unique solution. No test case will result in a shaft within $0.001$ units from the outlet of the qanat channel or from another shaft.
## 样例

### 样例输入 #1
```
8 4 1

```
### 样例输出 #1
```
31.500000
3.000000

```
### 样例输入 #2
```
195 65 2

```
### 样例输出 #2
```
12220.000000
48.000000
108.000000

```
### 样例输入 #3
```
10000 1 1000

```
### 样例输出 #3
```
30141.885677
9.956721
19.913443
29.870164
39.826887
49.783610
59.740334
69.697060
79.653786
89.610515
99.567245

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

[原题面链接](https://icpc.global/worldfinals/problems/2015-ICPC-World-Finals/icpc2015.pdf)

### **题目描述**

qanat 是一种广泛用在气候炎热、干旱的地区中供水的灌溉系统。这项技术最初由波斯人在 $2000$ 多年前发明。在摩洛哥，qanat 被称为 khettara。至今该系统在该国南部地区仍然被使用。

qanat 的基本特点是用一个基本上是水平的沟渠，把水从地下水源带到靠近城市的出水口。还有一个被称为母井的轴垂直向上延升，从地下水源上升到山脉或山丘的地表。建设这样的系统非常昂贵，在古代更加如此，因为从沟渠和母井中挖出的所有材料都必须在地表运输。这可以通过沟渠出口或母井顶部来进行。为了帮助施工，通常在地下沟渠上方的关键位置还会放置一个或多个额外的垂直井口。尽管这些井口也必须需要被挖掘，但它们提供了一种从水平沟渠中运输额外泥土的手段，如图 $1$ 所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/s71tofvr.png)

对于这个问题，模拟一个 qanat 的横截面，如图 $2$ 所示，其中通道出口在 $(0,0)$，水源在 $(w,0)$，母井顶部在 $(w,h)$，其中 $w > h$。山的表面沿着一条直线延伸，从 $(w,h)$ 到 $(0,0)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4bk00ojs.png)

每个 qanat 必须从水源到山体表面上有一个垂直的母井，还需要 $n$ 个额外的垂直井。水道和所有垂直井都被建模为线段。你的目标是确定这些额外井的位置，以最小化整体的挖掘成本。这个成本等于每块挖掘的土壤必须被运输到表面的距离的总和（任何水平和垂直运动的组合）。例如，从表面开始并沿着长度为 $l$ 的路径挖掘连续的土壤的成本为 $\int_0^l x \ \mathop{}\!\mathrm{dx}=\frac{1}{2}l^2$。

### **输入格式**

输入是一行，包含三个整数 $w$ $(1\le w\le 10000)$， $h$ $(1\le h<w)$，和 $n$ $(1\le n\le 1000)$，分别表示水源到 qanat 出口的水平距离，水源到山体表面的垂直距离和除了母井之外必须使用的垂直井口的数量。

### **输出格式**

首先，输出最小开挖成本。接下来，按照递增顺序输出 $n$ 个最优放置的竖井的 $x$ 坐标。如果 $n > 10$，则仅输出前 $10$ 个 $x$ 坐标。相对误差可以在 $10^{-4}$ 之内。你可以假设存在唯一解决方案。没有数据会导致竖井距离 qanat 渠道出口或其他竖井小于0.001单位。

### **说明/提示**

时间限制：$2000$ ms，空间限制：$1048576$ kB。

来源：

> International Collegiate Programming Contest (ACM-ICPC) World Finals 2015


---

---
title: "[ICPC 2016 WF] Balanced Diet"
layout: "post"
diff: 提高+/省选-
pid: P6917
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Balanced Diet
## 题目描述

Every day, Danny buys one sweet from the candy store and eats it. The store has $m$ types of sweets, numbered from $1$ to $m$. Danny knows that a balanced diet is important and is applying this concept to his sweet purchasing. To each sweet type $i$, he has assigned a target fraction, which is a real number $f_ i$ ($0 < f_ i \le 1$). He wants the fraction of sweets of type $i$ among all sweets he has eaten to be roughly equal to $f_ i$. To be more precise, let $s_ i$ denote the number of sweets of type $i$ that Danny has eaten, and let $n = \sum _{i=1}^ m s_ i$. We say the set of sweets is balanced if for every $i$ we have

\[ n f_ i - 1 < s_ i < n f_ i + 1. \] 

Danny has been buying and eating sweets for a while and during this entire time the set of sweets has been balanced. He is now wondering how many more sweets he can buy while still fulfilling this condition. Given the target fractions $f_ i$ and the sequence of sweets he has eaten so far, determine how many more sweets he can buy and eat so that at any time the set of sweets is balanced.
## 输入格式

The input consists of three lines. The first line contains two integers $m$ ($1 \le m \le 10^5$), which is the number of types of sweets, and $k$ ($0 \le k \le 10^5$), which is the number of sweets Danny has already eaten.

The second line contains $m$ positive integers $a_1, \ldots , a_ m$. These numbers are proportional to $f_1, \ldots , f_ m$, that is, $\displaystyle f_ i = \frac{a_ i}{\sum _{j = 1}^ m a_ j}$. It is guaranteed that the sum of all $a_ j$ is no larger than $10^5$.

The third line contains $k$ integers $b_1, \ldots , b_ k$ ($1 \le b_ i \le m$), where each $b_ i$ denotes the type of sweet Danny bought and ate on the $i^\text {th}$ day. It is guaranteed that every prefix of this sequence (including the whole sequence) is balanced.
## 输出格式

Display the maximum number of additional sweets that Danny can buy and eat while keeping his diet continuously balanced. If there is no upper limit on the number of sweets, display the word forever.
## 样例

### 样例输入 #1
```
6 5
2 1 6 3 5 3
1 2 5 3 5

```
### 样例输出 #1
```
1


```
### 样例输入 #2
```
6 4
2 1 6 3 5 3
1 2 5 3

```
### 样例输出 #2
```
forever


```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

## 题目描述

每天，Danny 都会从糖果店买一颗糖并吃掉它。糖果店中有 $m$ 种糖，编号为 $1 \dots m$ 。

Danny 知道均衡饮食很重要，他正在尝试在购买糖果时有一个均衡的饮食。因此他给每种糖 $i$ 分配了一个目标分数 $f_i (0 \le f_i \le 1, f_i$ 为一个实数 $) $, 。他希望他所吃的所有糖中，第 $i$ 种糖的数量占比大概为 $f_i$ 。

准确的说， 令 $s_ i$ 表示 Danny 已经吃掉的第 $i$ 种糖的数量,  $n = \sum _{i=1}^ m s_ i$, 我们认为一种吃糖的方法是均衡的仅当对于所有的 $i$，满足：

$$n f_ i - 1 < s_ i < n f_ i + 1$$

Danny 已经购买并吃掉了一些糖，并且他保证每个前缀的饮食都是均衡的。他想知道在保证每个前缀均衡饮食的条件下，他最多还能吃多少颗糖。

给定目标分数 $f_i$
和他已经吃过的糖果序列，请你确定在保证每个前缀均衡饮食的条件下，Danny 最多还能购买并吃掉多少颗糖果。

## 输入格式

输入包含三行。第一行包括两个整数 m $1 \le m \le 10^5$ 表示糖果的种类, $k(0 \le k \le 10^5)$ 表示 Danny 已经吃掉的糖果数量。

第二行包括 $m$ 个正整数 $a_1 \dots a_m$, 有   $ \displaystyle f_ i = \frac{a_ i}{\sum _{j = 1}^ m a_ j}$, 保证
$\sum_{i=1}^m a_i \le 10^5$ 。

第三行包括 $k$ 个正整数 $b_1 \dots b_k (1 \le b_i \le m)$, 表示 Danny 在第 $i$ 天购买并吃掉的糖的种类。保证序列的每个前缀（包括整个序列）是饮食均衡的。

## 输出格式
输出在保证每个前缀饮食均衡的条件下，Danny 最多还能购买并吃掉多少颗糖。

如果糖果的数量没有上限（即 Danny 能一直买下去），输出 `forever`。



---

---
title: "[ICPC 2016 WF] Clock Breaking"
layout: "post"
diff: 提高+/省选-
pid: P6920
tag: ['模拟', '2016', '枚举', 'ICPC']
---
# [ICPC 2016 WF] Clock Breaking
## 题目描述

After numerous unfortunate freak fatalities and the lawsuits, settlements, protests, and boycotts that naturally followed, the beleaguered executives at ACME Clock Manufacturers have decided they need to finally fix their disastrous quality control issues. It has been known for years that the digital clocks they manufacture have an unacceptably high ratio of faulty liquid-crystal display (LCD) screens, and yet these heartless souls have repeatedly failed to address the issue, or even warn their hapless consumers!

You have been called in as a quality consultant to finally put a stop to the madness. Your job is to write an automated program that can test a clock and find faults in its display.

These clocks use a standard 7-segment LCD display for all digits (shown on the left in Figure 1), plus two small segments for the ‘:’, and show all times in a 24-hour format. The minute before midnight is 23:59, and midnight is 0:00. The ‘:’ segments of a working clock are on at all times. The representation of each digit using the seven segments is shown on the right in Figure 1.

![](https://cdn.luogu.com.cn/upload/image_hosting/3ornshtp.png)

   Figure 1: LCD display of each digit. 

Your program will be given the display of a clock at several consecutive minutes, although you do not know exactly what time these displays start. Some of the LCD segments are burnt out (permanently off) and some are burnt in (permanently on). Your program must determine, where possible, which segments are definitely malfunctioning and which are definitely in working order.
## 输入格式

The first input line contains a single integer $n$ ($1 \leq n \leq 100$), which is the number of consecutive minutes of a clock’s display. The next $8n-1$ lines contain $n$ ASCII images of these clock displays of size $7 \times 21$, with a single blank line separating the representations.

All digit segments are represented by two characters, and each colon segment is represented by one character. The character ‘X’ indicates a segment that is on. The character ‘.’ indicates anything else (segments that are off or non-segment portions of the display). See the sample input/output for details; the first output shows every possible LCD segment along with the smaller segments used to represent the ‘:’. No clock representation has an ‘X’ in a non-segment position or only half of a segment showing.
## 输出格式

Display a $7 \times 21$ ASCII image with a ‘0’ for every segment that is burnt out, a ‘1’ for every segment that is burnt in, a ‘W’ for every segment that is definitely working, and a ‘?’ for every segment for which the status cannot be determined. Use ‘.’ for non-segments. If the given displays cannot come from consecutive minutes, display impossible.
## 样例

### 样例输入 #1
```
3
......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

.............XX...XX.
........X...X..X....X
........X.X.X..X....X
.............XX......
........X...X..X.X..X
........X...X..X.X..X
......XX.....XX...XX.

```
### 样例输出 #1
```
.??...WW.....??...??.
?..?.W..?...?..1.0..?
?..?.W..?.?.?..1.0..?
.??...??.....11...WW.
?..?.W..?.0.W..?.1..?
?..?.W..?...W..?.1..?
.??...11.....??...??.

```
### 样例输入 #2
```
2
......XX.....XX...XX.
...X....X...X..X.X..X
...X....X.X.X..X.X..X
......XX..........XX.
...X.X....X.X..X.X..X
...X.X......X..X.X..X
......XX.....XX...XX.

......XX.....XX......
...X....X...X..X.....
...X....X.X.X..X.....
......XX.............
...X.X....X.X..X.....
...X.X......X..X.....
......XX.....XX......

```
### 样例输出 #2
```
impossible

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

### 题目描述  

在无数不幸的畸形死亡事件以及随之而来的诉讼、和解、抗议和抵制之后，ACME时钟制造商的高管们决定最终解决灾难性的质量控制问题。多年来，人们都知道，他们制造的数字钟的液晶显示屏故障率高得令人无法接受，然而，这些无情的人们却一再未能解决这个问题，甚至未能警告他们不幸的消费者！  

你被邀请担任质量顾问，最终制止了这种疯狂。你的工作是编写一个自动程序，可以测试时钟并发现其显示中的故障。  

这些时钟使用标准的7段LCD显示屏显示所有数字（如图1左侧所示），加上两个小段显示`：`，并以24小时计时法显示所有时间。午夜前一分钟是23:59，午夜是0:00。工作时钟的`：`段始终打开。图1右侧显示了使用七段表示的`0~9`每个数字。  

![图1：每个数字的LCD显示。](https://cdn.luogu.com.cn/upload/image_hosting/3ornshtp.png)   

图1：每个数字的LCD显示。

### 输入格式  

第一行有一个数$n(1\ \le\ n\ \le\ 100)$，这是时钟显示的连续分钟数。  

接下来$8n-1$行包括$n$个时钟显示的$7\times 21$的ASCII图像，每两个之间会有一行的空白用于间隔  

所有表示数字的段由两个连续的字符表示，每个表示冒号的段由一个字符表示。字符`X`表示打开的段。字符`.`指示其他任何内容（显示的分段或非分段部分）。详见样本输入、输出；第一个输出显示每个可能的LCD段以及用于表示`：`的较小段。没有时钟表示在非段位置有`X`，或仅显示段的一半。  

### 输出格式  

显示一个$7\times 21$ASCII图像，每个烧坏的段显示一个`0`，每个烧进的段显示`1`，每个正常工作的段显示为`W`，以及一个`？`对于无法确定状态的每个段。使用`.`对于非分段。如果给定的显示不能来自连续分钟，则显示`impossible`。  

### 输入输出样例  

### 说明/提示  

时间限制：3000ms=3s  

空间限制：1048576KB=1024MB=1GB  

出处:2016年国际大学生编程大赛（`ACM-ICPC`）世界总决赛


---

---
title: "[ICPC 2016 WF] Forever Young"
layout: "post"
diff: 提高+/省选-
pid: P6921
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Forever Young
## 题目描述

My birthday is coming up. Alas, I am getting old and would like to feel young again. Fortunately, I have come up with an excellent way of feeling younger: if I write my age as a number in an appropriately chosen base $b$, then it appears to be smaller. For instance, suppose my age in base $10$ is $32$. Written in base $16$ it is only $20$!

However, I cannot choose an arbitrary base when doing this. If my age written in base $b$ contains digits other than $0$ to $9$, then it will be obvious that I am cheating, which defeats the purpose. In addition, if my age written in base $b$ is too small then it would again be obvious that I am cheating.

Given my age $y$ and a lower bound $\ell $ on how small I want my age to appear, find the largest base $b$ such that $y$ written in base $b$ contains only decimal digits, and is at least $\ell $ when interpreted as a number in base $10$.
## 输入格式

The input consists of a single line containing two base 10 integers $y$ ($10 \le y \le 10^{18}$ – yes, I am very old) and $\ell $ ($10 \le \ell \le y$).
## 输出格式

Display the largest base $b$ as described above.
## 样例

### 样例输入 #1
```
32 20

```
### 样例输出 #1
```
16

```
### 样例输入 #2
```
2016 100

```
### 样例输出 #2
```
42

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

# 题目大意
我的生日快到了！唉，但如今我已经老了，我想重新获得年轻的感觉。

幸运的是，我想出了一个让人感觉更年轻的好方法：如果我把我的年龄以适当选择的$b$进制书写，那么它看起来会更小。例如，假设我以$10$进制书写的年龄是$32$岁；以$16$进制书写，它只有$20$($0x20$)！

然而，在这样做时，我不能选择任意进制数。如果以$b$进制为数写的我的年龄包含$0-9$以外的数字，那么很明显我在作弊，这违背了目的。此外，如果我的年龄的进制数$b$太小，那么很明显我在作弊。

在我希望我的年龄看起来有多小的问题上,考虑到我的年龄$y$和下限$l$，找到最大的进制数$b$，这样写在基数$b$中的$y$只包含十进制数字，并且当将其看做一个十进制数字时至少是$l$。
# 输入格式
输入由一行组成，其中包含两个$10$进制的整数$y$ ($10\le y\le10^{18}$ –是的,我很老）和$l$($10\le l \le y$)
# 输出格式
如上所述，输出最大进制数$b$。
# 说明/提示
时间限制：$1s$，内存限制：$1GB$

(洛谷这里实际是$512MB$,但原题是$1GB$)

$2016年$国际大学生编程大赛$ACM$-$ICPC$世界总决赛


---

---
title: "[ICPC 2016 WF] String Theory"
layout: "post"
diff: 提高+/省选-
pid: P6926
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] String Theory
## 题目描述

Nested quotations are great not only for writing literature with a complex narrative structure, but also in programming languages. While it may seem necessary to use different quotation marks at different nesting levels for clarity, there is an alternative. We can display various nesting levels using $k$-quotations, which are defined as follows.

A $1$-quotation is a string that begins with a quote character, ends with another quote character and contains no quote characters in-between. These are just the usual (unnested) quotations. For example, 'this is a string' is a $1$-quotation.

For $k > 1$, a $k$-quotation is a string that begins with $k$ quote characters, ends with another $k$ quote characters and contains a nested string in-between. The nested string is a non-empty sequence of $(k-1)$-quotations, which may be preceded, separated, and/or succeeded by any number of non-quote characters. For example, ''All 'work' and no 'play''' is a $2$-quotation.

Given a description of a string, you must determine its maximum possible nesting level.
## 输入格式

The input consists of two lines. The first line contains an integer $n$ ($1 \le n \le 100$). The second line contains $n$ integers $a_1, a_2, \ldots , a_ n$ ($1 \le a_ i \le 100$), which describe a string as follows. The string starts with $a_1$ quote characters, which are followed by a positive number of non-quote characters, which are followed by $a_2$ quote characters, which are followed by a positive number of non-quote characters, and so on, until the string ends with $a_ n$ quote characters.
## 输出格式

Display the largest number $k$ such that a string described by the input is a $k$-quotation. If there is no such $k$, display no quotation instead.
## 样例

### 样例输入 #1
```
5
2 1 1 1 3

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
1
22

```
### 样例输出 #2
```
4

```
### 样例输入 #3
```
1
1

```
### 样例输出 #3
```
no quotation

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

定义 $1$ 级引用是一个以引号字符 ' 开头和结尾，中间不包含引号字符的字符串。定义 $k$ 级引用为两端各有连续 $k(k>1)$ 个引号，中间有若干个 $k-1$ 级引用的字符串，其中第一个 $k-1$ 级引用前，最后一个 $k-1$ 级引用后，相邻两个 $k-1$ 级引用之间都可以添加任意个非引用字符。

现给定一个字符串中极长连续引号段的个数 $n(n\le100)$，和这 $n$ 个极长连续引号段的长度 $a_1,...,a_n$，求最大的 $k$，使得这个字符串是一个 $k$ 级引用。
若这样的 $k$ 不存在，输出 `no quotation`。

translated by @Starlight237


---

---
title: "[ICPC 2016 WF] Swap Space"
layout: "post"
diff: 提高+/省选-
pid: P6927
tag: ['贪心', '2016', 'ICPC']
---
# [ICPC 2016 WF] Swap Space
## 题目描述

You administer a large cluster of computers with hard drives that use various file system types to store data. You recently decided to unify the file systems to the same type. That is quite a challenge since all the drives are currently in use, all of them are filled with important data to the limits of their capacities, and you cannot afford to lose any of the data. Moreover, reformatting a drive to use a new file system may significantly change the drive’s capacity. To make the reformat possible, you will have to buy an extra hard drive. Obviously, you want to save money by minimizing the size of such extra storage.

You can reformat the drives in any order. Prior to reformatting a drive, you must move all data from that drive to one or more other drives, splitting the data if necessary. After a drive is reformatted, you can immediately start using it to store data from other drives. It is not necessary to put all the data on the same drives they originally started on – in fact, this might even be impossible if some of the drives have smaller capacity with the new file system. It is also allowed for some data to end up on the extra drive.

As an example, suppose you have four drives $A$, $B$, $C$, and $D$ with drive capacities $6$, $1$, $3$, and $3$ GB. Under the new file system, the capacities become $6$, $7$, $5$, and $5$ GB, respectively. If you buy only $1$ GB of extra space, you can move the data from drive $B$ there and then reformat drive $B$. Now you have $7$ GB free on drive $B$, so you can move the $6$ GB from drive $A$ there and reformat drive $A$. Finally, you move the six total gigabytes from drives $C$ and $D$ to drive $A$, and reformat $C$ and $D$.
## 输入格式

The input begins with a line containing one integer $n$ ($1 \le n \le 10^6$), which is the number of drives in your cluster. Following this are $n$ lines, each describing a drive as two integers $a$ and $b$, where $a$ is the capacity with the old file system and $b$ is the capacity with the new file system.

All capacities are given in gigabytes and satisfy $1 \le a,b \le 10^9$. (One thousand petabytes should be enough for everyone, right?)
## 输出格式

Display the total extra capacity in gigabytes you must buy to reformat the drives.
## 样例

### 样例输入 #1
```
4
6 6
1 7
3 5
3 5

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
4
2 2
3 3
5 1
5 10

```
### 样例输出 #2
```
5

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

### 题目描述

你有许多电脑，它们的硬盘用不同的文件系统储存数据。你想要通过格式化来统一文件系统。格式化硬盘可能使它的容量发生变化。为了格式化，你需要买额外的硬盘。当然，你想要买容量最小的额外储存设备以便省钱。你可以按任意顺序格式化硬盘。格式化之前，你要把该硬盘上所有数据移到一个或更多的其他硬盘上（可以分割数据）。格式化后，该硬盘可以立刻开始使用。你没有必要把数据放到它原来所在的硬盘上。数据也可以被放到你额外买的硬盘上。举个例子，假设你有4个硬盘A、B、C、D，容量分别为6、1、3、3(GB)。新的文件系统下，它们的容量变为6、7、5、5(GB)。如果你只买1GB额外空间，你可以把B硬盘的数据放过去然后格式化硬盘B。现在你的B硬盘有7GB容量了，那么你就可以把A的数据放过去然后格式化A，最后把C、D的数据放到A上，再格式化C和D。

### 输入格式

第一行一个数 $n(1≤n≤1,000,000)$，表示你的硬盘数。接下来 $n$ 行，每行两个数 $a$ 和 $b$，分别表示该硬盘的原容量和新文件系统下的容量。所有容量都以 GB 为单位，且$1≤a,b≤1,000,000,000$。

### 输出格式

输出如果要格式化所有硬盘，你最少需要购买多少额外空间(GB)。




---

---
title: "[ICPC 2017 WF] Visual Python++"
layout: "post"
diff: 提高+/省选-
pid: P6940
tag: ['2017', 'Special Judge', 'ICPC']
---
# [ICPC 2017 WF] Visual Python++
## 题目描述



In the recently proposed Visual Python++ programming language, a block of statements is represented as a rectangle of characters with top-left corner in row $r_{1}$ and column $c_{1},$ and bottom-right corner in row $r_{2}$ and column $c_{2}.$ All characters at locations $(r , c)$ with $r_{1} \le r \le r_{2}$ and $c_{1} \le c \le c_{2}$ are then considered to belong to that block. Among these locations, the ones with $r = r_{1}$ or $r = r_{2}$ or $c = c_{1}$ or $c = c_{2}$ are called a border.

Statement blocks can be nested (rectangles contained in other rectangles) to an arbitrary level. In a syntactically correct program, every two statement blocks are either nested (one contained in the other) or disjoint (not overlapping). In both cases, their borders may not overlap.

Programmers are not expected to draw the many rectangles contained in a typical program $-$ this takes too long, and Visual $Pytho_n++$ would not have a chance to become the next ICPC programming language. So a programmer only has to put one character $‘p'$ in the top-left corner of the rectangle and one character $‘y'$ in the bottom-right corner. The parser will automatically match up the appropriate corners to obtain the nesting structure of the program.

Your team has just been awarded a five-hour contract to develop this part of the parser.


## 输入格式



The first line of the input contains an integer $n (1 \le n \le 10^{5}),$ the number of corner pairs. Each of the next $n$ lines contains two integers $r$ and $c (1 \le r , c \le 10^{9}),$ specifying that there is a top-left corner in row $r$ and column $c$ of the program you are parsing. Following that are $n$ lines specifying the bottom-right corners in the same way. All corner locations are distinct.


## 输出格式



Display $n$ lines, each containing one integer. A number $j$ in line $i$ means that the $i^{th}$ top-left corner and the $j^{th}$ bottom-right corner form one rectangle. Top-left and bottom-right corners are each numbered from $1$ to $n$ in the order they appear in the input. The output must be a permutation of the numbers from $1$ to $n$ such that the matching results in properly nested rectangles. If there is more than one valid matching, any one will be accepted. If no such matching exists, display syntax error.


## 样例

### 样例输入 #1
```
2
4 7
9 8
14 17
19 18

```
### 样例输出 #1
```
2
1

```
### 样例输入 #2
```
2
4 7
14 17
9 8
19 18

```
### 样例输出 #2
```
1
2

```
### 样例输入 #3
```
2
4 8
9 7
14 18
19 17

```
### 样例输出 #3
```
syntax error

```
### 样例输入 #4
```
3
1 1
4 8
8 4
10 6
6 10
10 10

```
### 样例输出 #4
```
syntax error

```
## 提示

Time limit: 5 s, Memory limit: 512 MB. 


## 题目翻译

# 题意

有 $n$ 个矩形，每个矩形左上角为 $(r_1,c_1)$ ，右下角为 $(r_2,c_2)$。

矩形可以嵌套（矩形包含在其他矩形中）任意层。在合法的情况下，任意两个矩形要么是嵌套的（一个包含在另一个中），要么是不交的（不重叠）。在这两种情况中，他们的 **边界也不能重叠**。

# 输入格式

第一行包含一个整数 $n(1\leq n \leq 10^5)$ ，表示矩形的数量。

接下来 $n$ 行，每行两个整数 $r$ 和 $c(1\leq r,c\leq 10^9)$ ，指定 $(r,c)$ 为第 $i$ 个左上角坐标。

接下来 $n$ 行，每行两个整数 $r$ 和 $c(1\leq r,c\leq 10^9)$ ，指定 $(r,c)$ 为第 $j$ 个右下角坐标。

所有给定坐标互不相同。

# 输出格式

输出 $n$ 行，每行包含一个整数。第 $i$ 行整数 $j$ 表示第 $i$ 个左上角和第 $j$ 个右下角组成一个矩形。左上角和右下角均按照他们在输入中的顺序从 $1$ 到 $n$ 标号。输出必须是 $1$ 到 $n$ 的排列，从而匹配可能嵌套的矩形。如果存在超过一种合法的匹配，任意一组合法的匹配都是可接受的。如果不存在合法的匹配，输出 `syntax error`。


---

---
title: "[ICPC 2018 WF] Catch the Plane"
layout: "post"
diff: 提高+/省选-
pid: P6941
tag: ['2018', 'Special Judge', 'ICPC']
---
# [ICPC 2018 WF] Catch the Plane
## 题目描述



Your plane to the ICPC Finals departs in a short time, and the only way to get to the airport is by bus. Unfortunately, some of the bus drivers are considering going on strike, so you do not know whether you can get to the airport on time. Your goal is to plan your journey in such a way as to maximize the probability of catching your plane.

You have a detailed map of the city, which includes all the bus stations. You are at station $0$ and the airport is at station $1$ . You also have a complete schedule of when each bus leaves its start station and arrives at its destination station. Additionally, for each bus you know the probability that it is actually going to run as scheduled, as opposed to its driver going on strike and taking the bus out of service. Assume all these events are independent. That is, the probability of a given bus running as planned does not change if you know whether any of the other buses run as planned.

If you arrive before the departure time of a bus, you can transfer to that bus. But if you arrive exactly at the departure time, you will not have enough time to get on the bus. You cannot verify ahead of time whether a given bus will run as planned $-$ you will find out only when you try to get on the bus. So if two or more buses leave a station at the same time, you can try to get on only one of them.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15689/1.png)

Figure A.1 : Bus schedule corresponding to Sample Input $1$ .

Consider the bus schedule shown in Figure A.1 . It lists the start and destination stations of several bus routes along with the departure and arrival times. You have written next to some of these the probability that that route will run. Bus routes with no probability written next to them have a $100\%$ chance of running. You can try catching the first listed bus. If it runs, it will take you straight to the airport, and you can stop worrying. If it does not, things get more tricky. You could get on the second listed bus to station $2$ . It is certain to leave, but you would be too late to catch the third listed bus which otherwise would have delivered you to the airport on time. The fourth listed bus $-$ which you can catch $-$ has only a $0$ . $1$ probability of actually running. That is a bad bet, so it is better to stay at station $0$ and wait for the fifth listed bus. If you catch it, you can try to get onto the sixth listed bus to the airport; if that does not run, you still have the chance of returning to station $0$ and catching the last listed bus straight to the airport.


## 输入格式



The first line of input contains two integers $m (1 \le m \le 10^{6})$ and $n (2 \le n \le 10^{6}),$ denoting the number of buses and the number of stations in the city. The next line contains one integer $k (1 \le k \le 10^{18}),$ denoting the time by which you must arrive at the airport.

Each of the next $m$ lines describes one bus. Each line contains integers a and $b (0 \le $ a , $b < n$ , a $≠ b)$ , denoting the start and destination stations for the bus. Next are integers $s$ and $t (0 \le s < t \le k)$ , giving the departure time from station a and the arrival time at station $b$ . The last value on the line is $p (0 \le p \le 1$ , with at most $10$ digits after the decimal point), which denotes the probability that the bus will run as planned.


## 输出格式



Display the probability that you will catch your plane, assuming you follow an optimal course of action. Your answer must be correct to within an absolute error of $10^{−6}.$


## 样例

### 样例输入 #1
```
8 4
1000
0 1 0 900 0.2
0 2 100 500 1.0
2 1 500 700 1.0
2 1 501 701 0.1
0 3 200 400 0.5
3 1 500 800 0.1
3 0 550 650 0.9
0 1 700 900 0.1

```
### 样例输出 #1
```
0.3124

```
### 样例输入 #2
```
4 2
2
0 1 0 1 0.5
0 1 0 1 0.5
0 1 1 2 0.4
0 1 1 2 0.2

```
### 样例输出 #2
```
0.7

```
## 提示

Time limit: 10 s, Memory limit: 1024 MB. 

spj provider:@[shenyouran](/user/137367).
## 题目翻译

给定一个图，有 $n$ 个点和 $m$ 条有向边，你现在在 $0$ 号点，你要在 $k$ 的时间前到达 $1$ 号点。

每条边从 $a$ 连向 $b$，在 $s$ 时间到达 $a$ 就可以用 $t$ 的时间到达 $b$，如果你要从 $a$ 到达 $b$，可以选择提前到达然后在 $a$ 等待，或者刚刚好用 $s$ 的时候到达 $a$，但是超过 $s$ 的时间到达就不能通过这条边到达 $b$ 了。每条边有 $p$ 的概率不能通过。

求准时到达 $1$ 号点的概率。

翻译者：一只书虫仔


---

---
title: "[ICPC 2018 WF] Single Cut of Failure"
layout: "post"
diff: 提高+/省选-
pid: P6948
tag: ['2018', 'Special Judge', 'ICPC']
---
# [ICPC 2018 WF] Single Cut of Failure
## 题目描述



The Intrusion and Crime Prevention Company (ICPC) builds intrusion detection systems for homes and businesses. The International Collegiate Programming Contest (in a strange coincidence also known as ICPC) is considering hiring the company to secure the room that contains the problem set for next year's World Finals.

The contest staff wants to prevent the intrusion attempts that were made in past years, such as rappelling down the outside of the building to enter through a window, crawling through air ducts, impersonating Bill Poucher, and the creative use of an attack submarine. For that reason, the problems will be stored in a room that has a single door and no other exits.

ICPC (the company) proposes to install sensors on the four sides of the door, where pairs of sensors are connected by wires. If somebody opens the door, any connected sensor pair will detect this and cause an alarm to sound.

The system has one design flaw, however. An intruder might cut the wires before opening the door. To assess the security of the system, you need to determine the minimum number of line segments that cut all wires. Figure H.1 shows two configurations of wires on the door (corresponding to the two sample inputs), and minimum-size cuts that intersect all wires.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15696/1.png)

Figure H.1 : Illustrations of Sample Inputs $1$ and $2$ .


## 输入格式



The input starts with a line containing three integers $n , w$ , and $h$ , which represent the number of wires installed $(1 \le n \le 10^{6})$ and the dimensions of the door $(1 \le w , h \le 10^{8}).$ This is followed by $n$ lines, each describing a wire placement. Each of these lines contains four integers $x_{1}, y_{1}, x_{2},$ and $y_{2} (0 \le x_{1}, x_{2} \le w , 0 \le y_{1}, y_{2} \le h)$ , meaning that a wire goes from $(x_{1}, y_{1})$ to $(x_{2}, y_{2}).$ Each wire connects different sides of the door. No wire is anchored to any of the four corners of the door. All locations in the input are distinct.


## 输出格式



Display a minimum-size set of straight line cuts that intersect all wires. First, display the number of cuts needed. Then display the cuts, one per line in the format $x_{1} y_{1} x_{2} y_{2}$ for the cut between $(x_{1}, y_{1})$ and $(x_{2}, y_{2}).$ Each cut has to start and end on different sides of the door. Cuts cannot start or end closer than $10^{−6}$ to any wire anchor location or any corner of the door.

Cuts may be displayed in any order. The start and end locations of each cut may be displayed in either order. If there are multiple sets of cuts with the same minimum size, display any of them.


## 样例

### 样例输入 #1
```
4 4 6
0 1 4 4
0 5 2 0
0 3 3 6
2 6 4 2

```
### 样例输出 #1
```
1
0 4 4 3

```
### 样例输入 #2
```
5 4 6
0 2 2 0
0 3 2 6
1 6 3 0
1 0 4 4
3 6 4 2

```
### 样例输出 #2
```
2
0 4 4 4.5
0 1 4 1

```
## 提示

Time limit: 6 s, Memory limit: 1024 MB. 


## 题目翻译

#### 题目描述

入侵与犯罪预防公司 (the Intrusion and Crime Prevection Company, 简称 ICPC) 为家庭和商业公司建立了入侵检测系统。国际大学生编程竞赛 (the International Collegiate Programming Contest, 碰巧也简称 ICPC) 正在考虑雇佣该公司来确保下一年 World Finals 的题目文件的储藏房间的安全。

比赛工作人员希望防止过去几年发生的入侵尝试，例如在大楼的外部垂直速降然后从窗户进入，从排气管道爬进来，冒充 Bill Poucher （译者注：某知名计算机科学教授，ACM-ICPC 的执行董事），以及创造性地使用攻击潜艇。正因如此，题目文件将被储藏在仅有一扇门而没有任何其他出入口的房间里。

ICPC （指公司）建议在门的四边安装传感器，每对传感器由电线连接。如果有人打开了门，任何连接的一对传感器将检测到这个动作并引起警报声。

然而这个系统存在一个设计缺陷。入侵者可以在开门之前剪断这些电线。为了评估这个系统的安全性，你需要使用最少的线段剪断所有电线。下图展示了两种具有不同电线分布的门（对应于两个样例）以及最少的与所有电线相交的线段。

![图](http://173.82.2.245/share/eh-1.png)

#### 输入格式

第一行三个整数 $n, w, h$ 分别表示电线的数量 ($1 \le n \le 10^6$) 以及门的尺寸 ($1 \le w, h \le 10^8$) 。接下来 $n$ 行，每行描述一个电线的位置。这些行中每行包含四个整数 $x_1, y_1, x_2, y_2$ ($0 \le x_1, x_2 \le w, 0 \le y_1, y_2 \le h$) 表示该电线从 $(x_1, y_1)$ 连接到 $(x_2, y_2)$ 。每根电线连接门的不同的两边。没有电线连接到门的四个角落。输入的所有位置都是两两不同的。

#### 输出格式

输出最少的一组线段与所有电线有交。首先第一行输出线段的数量。然后逐行输出线段，每行以 $x_1$ $y_1$ $x_2$ $y_2$ 的格式给出一个从 $(x_1, y_1)$ 到 $(x_2, y_2)$ 的线段。每条线段的两个端点必须在门的不同的两边。线段的端点与任何电线端点及门的四个角落的距离不能小于 $10^{-6}$ 。

线段可以以任意顺序输出。线段的两个端点也可以以任意顺序输出。如果有多种可行的解，输出任意一组解即可。

译者注：线段的端点坐标可以是满足限制的任意**实数**。



---

---
title: "[NEERC 2017] Connections"
layout: "post"
diff: 提高+/省选-
pid: P6954
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NEERC 2017] Connections
## 题目描述



Hard times are coming to Byteland. Quantum computing is becoming mainstream and Qubitland is going to occupy Byteland. The main problem is that Byteland does not have enough money for this war, so the King of Byteland Byteman $0x0B$ had decided to reform its road system to reduce expenses.

Byteland has $n$ cities that are connected by $m$ one-way roads and it is possible to get from any city to any other city using these roads. No two roads intersect outside of the cities and no other roads exist. By the way, roads are one-way because every road has a halfway barrier that may be passed in one direction only. These barriers are intended to force enemies to waste their time if they choose the wrong way.

The idea of the upcoming road reform is to abandon some roads so that exactly $2n$ roads remain. Advisers of the King think that it should be enough to keep the ability to get from any city to any other city. (Maybe even less is enough? They do not know for sure. ) The problem is how to choose roads to abandon. Everyone in Byteland knows that you are the only one who can solve this problem.


## 输入格式



Input consists of several test cases. The first line of the input contains the number of tests cases.

The first line of each test case contains $n$ and $m$ -- the number of cities and the number of roads correspondingly $(n \ge 4 , m > 2n).$ Each of the next $m$ lines contains two numbers $x_i$ and $y_i$ denoting a road from city $x_{i}$ to city $y_{i} (1 \le x_{i}, y_{i} \le n , x_{i} ≠ y_{i}).$ It is guaranteed that it is possible to get from any city to any other city using existing roads only. For each pair $(x , y)$ of cities there is at most one road going from city $x$ to city $y$ and at most one road going from city $y$ to city $x$ . The solution is guaranteed to exist. The sum of $m$ over all test cases in a single input does not exceed $100 000$ .


## 输出格式



For each test case output $m − 2n$ lines. Each line describes a road that should be abandoned. Print the road in the same format as in the input: the number of the source city and the number of the destination city. The order of roads in the output does not matter, but each road from the input may appear in the output at most once and each road in the output must have been in the input. It still must be possible to get from any city to any other city using the remaining roads.


## 样例

### 样例输入 #1
```
1
4 9
1 2
1 3
2 3
2 4
3 2
3 4
4 1
4 2
4 3

```
### 样例输出 #1
```
1 3

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

给定一个 $n$ 点有向图，要求保留 $2n$ 条边使得强连通关系不变，输出删去的边


---

---
title: "[NEERC 2016] Kids Designing Kids"
layout: "post"
diff: 提高+/省选-
pid: P6972
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NEERC 2016] Kids Designing Kids
## 题目描述



Kevin and Kimberly have freckles on their foreheads.

They both drew their freckle pictures on sheets of paper. Each picture is a rectangle of `pixels`: every cell either has a freckle or it has no freckle.

They are jokingly proposing that when they grow up, marry, and have a child, her freckle picture is produced as a result of the following procedure:

Kevin's and Kimberly's pictures are moved by a parallel translation, and then in each cell a child has a freckle if and only if exactly one of the parents has a freckle in this position.

Now they wonder, whether there is a parallel translation that gives their child a specific freckle picture (for example, a lightning), and what is this parallel translation.


## 输入格式



The first line contains two integers, $h_{1 }and w_{1} (1 \le h_{1}, w_{1} \le 1000)$ -- the height and the width of Kevin's freckle picture. Each of the next $h_{1}$ lines consists of $w_{1}$ characters $‘ \times '$ and $‘. '.$ Character $‘ \times '$ means that there is a freckle, and $‘. '$ that there is not.

The next lines contain Kimberly's picture in the same format. Its height and width $h_2$ and $w_2$ follow the same constraints.

It is guaranteed that Kevin and Kimberly have at least one freckle each.

The next lines contain the picture they want for their child in the same format. Its dimensions $h_{3}$ and $w_{3}$ also have the same constraints.


## 输出格式



In the first line output `YES` if the desired picture can be produced, and `NO` otherwise.

If the answer is positive, then in the second line output two integers, $x$ and $y$ , with the following meaning: if you overlay the pictures so that their upper left corners coincide, then move Kimberly's picture $x$ cells right (negative number means moving picture left) and $y$ cells down (negative number means moving picture up), and then apply the procedure described above, the resulting picture can be moved by a parallel translation to coincide with the third picture from the input file.


## 样例

### 样例输入 #1
```
3 3
..*
.*.
*.*
3 3
**.
..*
.*.
5 2
.*
*.
**
.*
*.

```
### 样例输出 #1
```
YES
0 2

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

给定三个 01 矩阵（``*`` 表示 $1$，``.`` 表示 $0$），大小分别为 $h_1\times w_1$、$h_2\times w_2$ 和 $h_3\times w_3$，你可以将前两个矩阵的左上角重叠，然后将第二个矩阵向右平移 $x$ 个长度、向下平移 $y$ 个长度（$x,y$ 可以为负数，表示反方向）。然后将对应位置异或起来（超出部分均视为 $0$）。

你需要判断得到的矩阵是否可能能够通过平移和第三个矩阵重合（超出部分均视为 $0$），并给出方案。

保证前两个矩阵都含有至少一个 $1$。

$h,w\le 10^3$。


---

---
title: "[NEERC 2013] ASCII Puzzle"
layout: "post"
diff: 提高+/省选-
pid: P6996
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] ASCII Puzzle
## 题目描述



Fili and Floi play a puzzle game. Fili takes a rectangular piece of paper that is lined with a $W \times H$ grid of square cells, cuts it into pieces on its grid lines, and carefully shuffles the pieces so that pieces do not rotate. Floi has to recombine the pieces back into the rectangle without rotating them.

Fili observes a number of constraints while cutting an original paper into pieces to make sure that the resulting puzzle is well-formed. First of all, Fili picks three integer numbers $w , h$ , and $n$ , so that an original rectangular paper has a width of $W = w_n$ cells and a height of $H = h_n$ cells. Here $w$ and $h$ are known to Floi, but $n , W$ , and $H$ are not. This way, the original rectangular piece of paper can be cut into a trivial puzzle of $k = n^{2}$ rectangles with a width of $w$ cells and a height of $h$ cells each. However, this trivial puzzle for $k > 1$ is not considered a well-formed puzzle for this game. Instead, the pieces int which the original rectangle is cut are based on these trivial $w \times h$ cell rectangles with the jagged edges between the adjacent pieces. Formally, the pieces into which the original $W \times H$ paper is cut satisfy the following constraints of a well-formed puzzle:

There are $k = n^{2}$ pieces.

Each piece is a simple $4-connected$ region of cells without holes.

Each cell of the original rectangular $W \times H$ paper is a part of exactly one piece.

Each piece contains four corners of the corresponding $w \times h$ rectangle in the trivial puzzle for the original paper.

The cells of each piece can come only from the corresponding $w \times h$ rectangle in the trivial puzzle, from the cells adjacent to this rectangle, and from the interior cells of the adjacent rectangles in the trivial puzzle.

The cut between two adjacent pieces cannot be straight. Only pieces that lie on the border of the original $W \times H$ paper have straight sides.

The corollary of these constraints is that each piece of a well-formed puzzle fits into a rectangle of (3w $− 2) \times $ (3h $− 2)$ cells. Moreover, the description of each piece will be given as a (3w $− 2) \times $ (3h $− 2)$ grid of cells in such a way, that the corresponding $w \times h$ rectangle of the trivial puzzle is exactly in the center.

The picture below to the left shows a sample rectangular piece of paper that is lined with a $W \times H = 12 \times 9$ square grid of cells and is cut into a trivial puzzle of $k = 9$ rectangles with a width of $w = 4$ cells and a height of $h = 3$ cells each with bold dashed lines. The corners of the central $3 \times 4$ piece of this trivial puzzle are shown in black. They have to be a part of the central piece of any well-formed puzzle. The other potential cells of the central piece of a well-formed puzzle are shown in gray. The bold black line shows (3w $− 2) \times $ (3h $− 2) = 10 \times 7$ rectangular region that will be describing this central piece. The picture to the right shows the same for the piece in the upper-right corner of the puzzle.

![](/upload/images2/neerc_a.png)

Your task is to help Floi solve the puzzle.


## 输入格式



The first line of the input file contains there integers $k , w$ and $h$ . Here $k$ is the number of pieces in the puzzle, $w$ is a width and $h$ is a height of a trivial puzzle piece $(k = n^{2}$ for $1 \le n \le 4 , 3 \le w , h \le 5)$ . The rest of the input file contains descriptions of $k$ pieces of a well-formed puzzle. Each piece is described by 3h $− 2$ lines that contain 3w $− 2$ characters each. Pieces are labeled with a consecutive English letters in uppercase (1st piece -- $‘A', 2nd$ piece -- $‘B',$ and etc). Each piece description uses only two characters on its 3h $− 2$ lines of 3w $− 2$ characters. The English letter corresponding to the piece denotes a cell that is a part of this piece, while $‘. '$ (dot) character denotes a cell that is not.

Empty lines separate different pieces.


## 输出格式



The first line of the output file shall contain $W$ and $H$ -- the size of the original piece of paper that was cut into the puzzle pieces. The following $H$ lines shall contain $W$ English letters each, describing the solution of the puzzle. Letters denote the cells that belong to the corresponding puzzle pieces. If there are multiple ways to solve the puzzle, then print any solution.


## 样例

### 样例输入 #1
```
4 4 3
..........
..........
...AAAA...
...AAAAAA.
...A.AA...
..........
..........

..........
..........
...BBBB...
.....BB...
...BBBB...
....BB....
.....B....

..........
..........
...C..C...
..CCC.C...
...CCCC...
..........
..........

..........
....D.....
...DDDD...
...DDD....
...DDDD...
..........
..........

```
### 样例输出 #1
```
8 6
AAAABBBB
AAAAAABB
ADAABBBB
DDDDCBBC
DDDCCCBC
DDDDCCCC

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

Fili 和 Floi 在玩一个拼图游戏。Fili 准备了一个被划分为 $W\times H$ 个格子的矩形纸片，并沿着格子的边缘将纸片剪成了若干个小片，然后小心地重排这些纸片使得纸片没有被旋转。

Fili 观察到满足一些限制的裁剪方案会产生一个**良好**的拼图游戏：首先，Fili 选择了三个整数 $w,h,n$，使得原先矩形的长宽分别满足 $W = wn$ 和 $H = hn$。此处 $w,h$ 是 Floi 知道的。这样最初的拼图游戏就可以变为 $k=n^2$ 个 $w\times h$ 的矩形构成的**平凡的拼图**。然而，平凡的拼图游戏不被认为是良好的。一个良好的游戏被定义为在拼图间有着参差不齐的边界（译者注：即有缺口和凸起的拼图）的游戏。更形式化地，一个将 $W\times H$ 纸片裁剪成拼图游戏的裁剪方案被认为是良好的当且仅当它满足以下性质：

- 有 $k=n^2$ 片拼图，且该拼图的每一块与平凡的拼图中的 $n^2$ 个 $w\times h$ 矩形一一对应。
- 每片拼图是一个没有洞的四联通区域。
- 每个原 $W\times H$ 纸片的格子属于恰好一片拼图。
- 每片拼图都包含了其对应的 $w\times h$ 矩形的四个角落处的格子。
- 每片拼图只能包含有：其对应的 $w\times h$ 矩形中的格子，与该矩形相邻的格子，以及与该矩形相邻矩形的内部格子。
- 两个相邻的拼图的边界不是直的。只有恰好贴着纸片边界的拼图的边界是直的。

注意到每块拼图必然包含于以其对应的 $w\times h$ 矩形为中心的一个 $(3w-2)(3h-2)$ 大小的矩形，于是输入文件以此方式给出。

你需要找到拼图的一种拼法。

$k=n^2$，$1\le n\le 4$，$3\le w,h\le 5$。


---

---
title: "[NEERC 2013] Green Energy"
layout: "post"
diff: 提高+/省选-
pid: P7002
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Green Energy
## 题目描述



The technological progress in Flatland is impressive. This year, for example, the solar power stations of a new type will be build. In these stations solar panels are mounted not on the ground, but on high towers, along their heights.

There are $n$ towers to be mounted. The towers are already bought. The height of i-th tower is $h_{i}.$ Now engineers want to choose the points where they should be mounted to get the maximal total power.

The landscape of a territory of the power plant is described by a polyline with $m$ vertices. Vertices of the landscape polyline have coordinates $(x_{i}, y_{i}),$ such that $x_{i} < x_{i+1}.$

The sun angle is always $α$ degrees in Flatland. The sun is shining from the top-left to the bottom-right. The power that is produced by a tower depends on the length of its surface illuminated by the sun.

When two towers are mounted close to each other, the shadow of the left tower may fall onto the right tower, so the power, produced by the right tower, decreases. Also, the landscape itself may contain high points that drop shadows on some towers.

![](/upload/images2/ge.png)

Your task is to find the points on the territory of the plant to mount the given towers to maximize the total length of towers surface that is illuminated by the sun.


## 输入格式



The first line of the input file contains three integers $n , m$ and $α (1 \le n \le 10^{4}, 2 \le m \le 10^{4}, 1 \le α < 90)$ . The second line contains $n$ integers $h_{i}$ -- the heights of the towers $(1 \le h_{i} \le 10^{3}).$ The following $m$ lines contain pairs $x_{i}, y_{i}$ -- the coordinates of the vertices of the landscape $(|x_{i}| \le 10^{5}, x_{i} < x_{i+1}, |y_{i}| \le 10^{3}).$


## 输出格式



On the first line output the maximal possible summary length of towers that can be illuminated by the sun with an absolute precision of at least $10^{-6}.$ On the next $n$ lines output the x-coordinates of the points where the towers should be mounted to achieve this maximum with an absolute precision of at least $10^{-9}.$ Towers should be listed in the same order they are given in the input file.


## 样例

### 样例输入 #1
```
5 4 10
20 10 20 15 10
0 10
40 20
50 0
70 30

```
### 样例输出 #1
```
52.342888649592545
16.0
0.0
70.0
65.3
65.3

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

## 题目描述 ##
平地上的技术进步令人惊叹。今年正要建造一种新型的太阳能发电站。在这些发电站中，太阳能电池板不是安装在地面上，而是安装在高塔上。

在二为世界中有要安装$i$个高塔。这些塔塔高固定。第$i$座塔的高度是$h_i$。现在，工程师们想要选择安装点，以获得最大的总功率。

电厂区域由有$m$顶点的线连接。这些线的顶点坐标为$(x_i,y_i)$满足$x_i<x_{i+1}$
在平地上，太阳的角度总是$\alpha$度。太阳从左上角照射到右下角。塔产生的功率取决于其表面被太阳照射的面积(其实是长度)。

当安装的两个塔彼此靠近时，左侧塔的阴影可能落在右侧塔上，从而右侧塔产生的功率降低。此外，电厂区域本身可能包含在某些塔楼上投下阴影的高点。

你的任务是在电厂区域内找到安装给定塔架的点，以得到太阳照射下塔架最大总表面积(长度)。

## 输入格式 ##

输入第一行包含三个整数：$n$,$m$,$\alpha$ $(1 \le n \le 10^4,2 \le m \le 10^4,1 \le \alpha <90)$。第二行包含$n$整数$h_i$(塔高）$(1 \le h_i \le 10^3)$。后面的$m$行每行有$x_i$,$y_i$一对数（电厂顶点坐标)$(|x_i|\le 10^5,x_i < x_{i+1},|y_i|\le 10^3)$

## 输出格式 ##

第一行:以至少$10^{-6}$精度输出可被太阳照亮的塔的最大可能汇总面积（长度)。在后n行上，输出此时塔安装点的x坐标，绝对精度至少为$10^{-9}$。塔的输出顺序应与输入顺序相同。

## 说明/提示 ##
时间限制：1h

空间顺序：128PB


---

---
title: "[NEERC 2013] Hack Protection"
layout: "post"
diff: 提高+/省选-
pid: P7003
tag: ['2013', 'ICPC']
---
# [NEERC 2013] Hack Protection
## 题目描述



Pavel is sending to his friend Egor some array of non-negative integers. He wants to be sure, that nobody hacks the array before his friend gets it. To solve this problem Pavel need to compute some kind of a checksum or a digest for his array. Pavel has an innovative mind, so he invents the following algorithm to compute the digest for his array: count the number of subarrays in which the bitwise xor of the numbers in the subarray is equal to the bitwise and of the same numbers.

For example, consider an array of four binary numbers `01`, `10`, `11`, and `11`. The table below to the left lists the results of the bitwise xor of numbers for each subarray of this array, and the table below to the right list the results of the bitwise and of numbers for each subarray of this array. The rows of the table correspond to the starting elements of the subarray from the $1st$ element of the array to the $4th$ one, while columns correspond to the ending elements of the subarray. Matching values are highlighted with gray background.

![](/upload/images2/hp.png)

Your task is to help Pavel compute this kind of a digest of the given array.


## 输入格式



The first line contains one integer $n (1 \le n \le 100 000)$ . The second line contains $n$ non-negative integers $a_{i} (0 \le a_{i} \le 2^{31}-1)$ that are written in decimal notation.


## 输出格式



On the first line of the output print Pavel's digest of the given array.


## 样例

### 样例输入 #1
```
4
1 2 3 3

```
### 样例输出 #1
```
6

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

给定一个序列$a_i$，求有多少个区间满足区间内的数的异或和等于与的和的值。


---

---
title: "[CERC2013] Magical GCD"
layout: "post"
diff: 提高+/省选-
pid: P7009
tag: ['2013', 'ICPC']
---
# [CERC2013] Magical GCD
## 题目描述

The Magical GCD of a nonempty sequence of positive integers is defined as the product of its length and the greatest common divisor of all its elements.

Given a sequence $(a_1, \ldots , a_ n)$, find the largest possible Magical GCD of its connected subsequences.
## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

The description of each test case starts with a line containing a single integer $n$, $1 \leq n \leq 100\, 000$. The next line contains the sequence $a_1, a_2 , \ldots , a _ n$, $1 \leq a_ i \leq 10^{12}$.
## 输出格式

For each test case output one line containing a single integer: the largest Magical GCD of a connected subsequence of the input sequence.
## 样例

### 样例输入 #1
```
1
5
30 60 20 20 20

```
### 样例输出 #1
```
80

```
## 提示

Time limit: 8000 ms, Memory limit: 1048576 kB. 

 Central Europe Regional Contest (CERC) 2013
## 题目翻译

有 $T$ 组询问，每次给出 $n$ 个数 $a_i$。  

你需要找到这个数组的一个子序列（要求编号连续），使得该序列中所有数的最大公约数和序列长度的乘积最大，并输出这个最大值。


---

---
title: "[CERC2013] Subway"
layout: "post"
diff: 提高+/省选-
pid: P7010
tag: ['2013', 'ICPC']
---
# [CERC2013] Subway
## 题目描述



Johny is going to visit his friend Michelle. His dad allowed him to go there on his own by subway. Johny loves traveling by subway and would gladly use this opportunity to spend half a day underground, but his dad obliged him to make as few line changes as possible. There are a lot of stations in the city, and several subway lines connecting them. All trains are perfectly synchronized $-$ the travel between two consecutive stations on every line takes exactly one minute, and changing lines at any station takes no time at all.

Given the subway map, help Johny to plan his trip so that he can travel for as long as possible, while still following his dad's order.


## 输入格式



First line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

The description of each test case starts with an empty line. The next two lines begin with the strings Stops: and Lines:, and contain the names (separated by a comma and a space) of all subway stops and lines, respectively. A single line for each subway line follows (in no particular order), beginning with route: and listing the names of the stops along this particular line. The final two lines specify the names of the (different) stations nearby Johny's and Michelle's homes.

In each test case, there are at most $300 000$ stations and $100 000$ lines, whose total length does not exceed $1 000 000$ . The names of lines and stations are between $1$ and $50$ characters long and can contain letters, digits, hyphens $(-),$ apostrophes $(‘)$ and `and` signs $(&).$ All lines are bidirectional (although changing the direction of travel counts as a line change) and there are no self-crossings.


## 输出格式



Print the answers to the test cases in the order in which they appear in the input. For each test case, print a single line summarizing the optimal route Johny can take (see example output for exact format). You may assume that such a route always exists.


## 样例

### 样例输入 #1
```
3

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at King'sCross
Michelle lives at GreenPark

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at PiccadillyCircus
Michelle lives at LeicesterSquare

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at Victoria
Michelle lives at HydeParkCorner

```
### 样例输出 #1
```
optimal travel from King'sCross to GreenPark: 1 line, 3 minutes
optimal travel from PiccadillyCircus to LeicesterSquare: 1 line, 1 minute
optimal travel from Victoria to HydeParkCorner: 2 lines, 7 minutes

```
## 提示

Time limit: 8 s, Memory limit: 128 MB. 


## 题目翻译

### 题目描述

$Johny$ 准备去拜访他的朋友 $Michelle$。他的父亲允许他乘地铁独自去那里。$Johny$ 喜欢乘地铁旅行，并很愿意用这次机会在地铁里呆上半天，但是父亲要求他尽量减少换乘次数。这个城市有很多地铁车站，并有几条地铁线路连接它们。所有列车都完全同步——在每条线上的两个连续地铁站点之间地铁行驶的时间恰好需要 $1$ 分钟，而在该城市的任何一个地铁站点上更改线路是不需要花费时间的。

现在 $Johny$ 有了该城市的地铁线路图，请帮助 $Johny$ 计划行程，以便他可以尽可能长时间的在地铁里呆着，同时还要尽量减少换乘次数。

### 输入格式

输入的第 $1$ 行为测试数据 $T$ 的数量。

每组测试数据均用空行分隔。接下来的两行以字符串以 $ Stops: $ 和  $Lines: $ 开头，并分别包含所有地铁站和线路的名称（以逗号和空格分隔）。每条地铁线路中的其中一条线路（不分先后）从 $route: $ 开始，并一一列出了该条线路的站点名称。最后两行给定了 $Johny$ 和 $Michelle$ 的家附近的车站的名称。

在每组测试数据中，最多有 $300000$ 个站点以及 $100000$ 条铁路线路，保证其总长度不超过 $1000000$；铁路线路和地铁站点的名称长度均在 $1$ 至 $50$ 个字符之间，其名称中可以含有字母、数字、连字符 `-`、引号 `'` 和特殊符号 `&`。所有的地铁线路都是双向的（改变行进方向即该条线路被改变），并保证没有自交叉。

### 输出格式

按照在输入中测试数据的顺序来输出每组测试数据的答案。对于每组测试用例，需输出一行来总结 Johny 可以采用的最佳路线（参见样例输出）。假设这样的线路始终存在。

### 输入输出样例

**输入 #1**

```txt
3

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at King'sCross
Michelle lives at GreenPark

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at PiccadillyCircus
Michelle lives at LeicesterSquare

Stops: OxfordCircus, PiccadillyCircus, HydeParkCorner, King'sCross, GreenPark, Arsenal, Victoria, Highbury&Islington, LeicesterSquare
Lines: Blue, Cyan
Cyan route: Highbury&Islington, King'sCross, OxfordCircus, GreenPark, Victoria
Blue route: HydeParkCorner, GreenPark, PiccadillyCircus, LeicesterSquare, King'sCross, Arsenal
Johny lives at Victoria
Michelle lives at HydeParkCorner
```

**输出 #1**

```txt
optimal travel from King'sCross to GreenPark: 1 line, 3 minutes
optimal travel from PiccadillyCircus to LeicesterSquare: 1 line, 1 minute
optimal travel from Victoria to HydeParkCorner: 2 lines, 7 minutes
```

### 说明 / 提示

时间限制：$8s$

内存限制：$256\texttt{MB}$


---

---
title: "[NWRRC 2016] Digital Addition"
layout: "post"
diff: 提高+/省选-
pid: P7034
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Digital Addition
## 题目描述



Deidra is doing a columnar addition. She writes down two non-negative integer summands one below the other, left-pads them with zeroes so that they have equal length, and calculates the sum (e.g. $ 77 + 05 = 82$) . If the sum is longer than each of the summands (because of a carry, as in $96 + 07 = 103$) she appends a zero at the beginning of each summand ($096 + 007 = 103)$ . She allows herself to use unnecessary leading zeroes ( $007 + 004 = 011)$ as soon as the length of all three numbers is the same.

Also Deidra has a homemade printing press. She decided to print her addition without a plus or $a horizontal$ line, using the following standard font:

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.11.png)

Unfortunately, she messed up with spacing, and all the digits were printed over each other in the following way. Digits that were supposed to be horizontally adjacent were printed so that the right two segments of the left digit coincide with the left two segments of the right digit. Digits that were supposed to be vertically adjacent were printed so that the bottom half (a square with 4 segments) of the upper digit coincides with the top half of the lower digit.

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.17.png)

When one or more black segments are printed at the same position, the result looks black. When only empty segments are printed at the position, the result looks white.

Given the resulting picture, find a correct addition that could produce it or detect that there is none.


## 输入格式



The first line of the input contains an integer $w (1 \le w \le 100)$ -- the width of Deidra's addition $(number of$ digits in each line).

The following $9$ lines contain the description of the picture printed with the bad spacing. Each line contains $w$ or $w + 1$ digits. ‘1' denotes a black segment, ‘0' denotes a white one. Even lines start with a space. See the examples for clarification.


## 输出格式



If there is no valid addition, output `NO`.

Otherwise output a valid addition that produces the given figure. The output should consist of three lines, each containing $w$ digits.

If there are several solutions, output any of them.


## 样例

### 样例输入 #1
```
2
 1 1
0 1 1
 1 0
0 1 1
 1 1
0 1 1
 1 0
0 1 1
 0 0

```
### 样例输出 #1
```
37
34
71

```
### 样例输入 #2
```
1
 1
0 1
 1
1 1
 1
1 1
 1
0 1
 0

```
### 样例输出 #2
```
2
2
4

```
### 样例输入 #3
```
1
 1
1 0
 1
1 1
 1
1 1
 1
0 1
 0

```
### 样例输出 #3
```
NO

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

Deidra正在做一个列式的加法。她写下两个正整数来对其进行求和，且一个在另一个下方，在它们的左边添0，使得他们拥有相同的长度，然后相加计算结果（例如 $77 + 05 = 82$）。如果这个结果的长度大于这两个加数任何一个的长度（由于进位，例如$96 + 07 = 103$），就在两个加数前面附加零（$096 + 007 = 103$）。她允许不必要的前导零的出现（$007 + 004 = 011$）只要算式中的三个数字的长度都相同。

Deidra还有一台自制的打印机。她决定在没有加号和水平线的情况下打印她的加法算式，使用下面的标准字体
![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.11.png)

不幸的是，她弄乱了这些数字的间距，所有的数字都将以以下方式打印。打印这些本应水平相邻的数字时左边数字的右两段与右边数字的左两端重合。打印应该竖直相邻的数字时，上边数字的下半部分（由四段组成的正方形部分）与下边数字的上半部分重合。

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.17.png)

如果在同一位置打印一个或多个线段时，将显示为黑色。当所在位置仅打印空段时，将显示为白色。

给定一个生成的图片，找到可以通过打印机产生这个图片的正确算式。如果找不到符合要求的算式，就输出 `NO` 

## 输入格式
第一行包含一个整数$w$$(1\le w \le 100)$ 代表Deidra加法的宽度（接下来每行的数字个数）

接下来的$9$行包含对于用错误打印机输出的图片的描述。每行包含$w$或$w+1$个数字。"1"表示黑色段，"0"表示白色段。偶数行以空格开头。有关说明请参阅样例。

## 输出格式

如果没有符合要求的算式，则输出 `NO` 。

否则输出给定图片所对应的有效算式。输出应由三行组成，每行包含$w$个数字。

如果有多个符合规定的算式，请输出其任何一个。


---

---
title: "[NWRRC 2015] Fygon"
layout: "post"
diff: 提高+/省选-
pid: P7053
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Fygon
## 题目描述



Frederick is a young programmer. He participates in all programming contests he can find and always uses his favorite programming language Fygon. Unfortunately, he often receives Time Limit Exceeded outcome, even when his algorithm is asymptotically optimal. That's because the Fygon interpreter is very slow. Nevertheless, Frederick likes Fygon so much, that he uses non-asymptotical optimizations to fit the solution into time limit. To make it easier, he asks you to write a program, which will be able to estimate the exact number of operations that his Fygon program makes.

For simplicity, we will assume that Fygon has only two statements. The first statement is lag. It substitutes almost any other statement. The second statement is a for loop:

for in range $():$

This means that iterates over values from $0$ to $−1$ . In Fygon is a lowercase letter from a to $z$ , and is either already defined or a positive integer constant. The of the loop is indented by four spaces and contains at least one statement.

The program receives the input in the variable $n$ . This variable has special meaning and cannot be used as a loop variable.

Your task is to find the formula that calculates the number of performed lag operations by the given Fygon program, depending on the value of the variable $n$ .


## 输入格式



The input file contains the Fygon program. No two loops use the same variable as iterators. Each variable used inside a range is either $n$ or declared in some outer loop.

The program has at most $20$ statements and at most $6$ of them are loops. All integer constants are from $1$ to $9$ . Outpu


## 输出格式



Output the formula for the number of performed lag operations depending on $n$ . The length of the formula should be at most $100$ characters (excluding spaces). The formula should correspond to the following grammar:

$〈Expressio_n〉 ::= 〈Product〉 ( (‘+' | ‘-') 〈Product〉) ^{ \times }$

$〈Product〉 ::= 〈Value〉 (‘ \times '〈Value〉) ^{ \times }$

$〈Value〉 ::= ‘n' | 〈Number〉 | ‘-'〈Value〉 | ‘('〈Expressio_n〉‘)'$

$〈Number〉 ::= [‘0' \cdots ‘9'] ^{+} (‘/' [‘0' \cdots ‘9'] ^{+}) ^{?}$


## 样例

### 样例输入 #1
```
for i in range(n):
    for j in range(i):
        lag
for x in range(5):
    for y in range(n):
        for z in range(n):
            lag
    lag

```
### 样例输出 #1
```
1/2 * n * (n-1) + 5 * (n*n + 1)

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

# [NWRRC2015] Fygon 翻译

## 题目描述

弗雷德里克是一名年轻的程序员。他参加了所有能找到的编程比赛，并总是使用他最喜欢的编程语言 Fygon。不幸的是，他经常收到 "超过时间限制 "的结果，即使他的算法是渐近最优的。这是因为 Fygon 解释器非常慢。尽管如此，弗雷德里克还是非常喜欢 Fygon，所以他使用了非渐进优化的方法来使求解符合时间限制。为了方便起见，他要求你写一个程序，能够估算出他的 Fygon 程序所做的确切操作次数。

为了简单起见，我们假设 Fygon 只有两条语句。第一条语句是滞后的。它几乎可以替代任何其他语句。第二条语句是 for 循环：

for in range $():$

这意味着遍历从 $0$ 到 $-1$ 的值。 在 Fygon 中是从 $a$ 到 $z$ 的小写字母，并且要么是已经定义的，要么是正整数常数。循环语句缩进四个空格，至少包含一条语句。

程序接收变量 $n$ 的输入。该变量具有特殊含义，不能用作循环变量。您的任务是根据变量 $n$ 的值，找出计算 Fygon 程序执行滞后操作次数的公式。

## 输入格式

输入文件包含 Fygon 程序。没有两个循环使用相同的变量作为迭代器。范围内使用的每个变量要么是 $n$，要么是在某个外循环中声明的。

程序最多有 $20$ 语句，其中最多有 $6$ 是循环。所有整数常量从 $1$ 到 $9$ 不等。
## 输出格式

根据 $n$ 输出已执行滞后运算次数的公式。公式长度最多为 $100$ 字符（不包括空格）。公式应符合以下语法：

$〈表达式〉 ::= 〈产物〉 ( (‘+' | ‘-') 〈产物〉) ^{ \times }$

$〈产物〉 ::= 〈价值〉 (‘ \times '〈价值〉) ^{ \times }$

$〈价值〉 ::= ‘n' | 〈数〉 | ‘-'〈价值〉 | ‘('〈表达式〉‘)'$

$〈数〉 ::= [‘0' \cdots ‘9'] ^{+} (‘/' [‘0' \cdots ‘9'] ^{+}) ^{?}$

## 样例 #1

### 样例输入 #1

```
for i in range(n):
    for j in range(i):
        lag
for x in range(5):
    for y in range(n):
        for z in range(n):
            lag
    lag
```

### 样例输出 #1

```
1/2 * n * (n-1) + 5 * (n*n + 1)
```

## 提示

时间限制：2 秒，内存限制：256 MB。


---

---
title: "[NWRRC 2014] Hiking in the Hills"
layout: "post"
diff: 提高+/省选-
pid: P7067
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NWRRC 2014] Hiking in the Hills
## 题目描述



Helen is hiking with her friends in a highland. Their plan is to hike from their camp $A$ to a beautiful showplace $B$ .

Unfortunately, Helen started feeling dizzy due to altitude sickness. Help her group find a route such that the topmost height on that route is as small as possible.

![](https://cdn.luogu.com.cn/upload/image_hosting/o2199eky.png)

## 输入格式



The input file contains full information about the landscape of a square region $10^{6} \times 10^{6}$ in the following format. The first line contains integer $n$ — the number of triangles in the landscape $(2 \le n \le 2000)$ . Each of following $n$ lines contains nine integers $x_{i_1}, y_{i_1}, z_{i_1}, x_{i_2}, y_{i_2}, z_{i_2}, x_{i3}, y_{i3}, z_{i3}$ — coordinates of a triangle. All coordinates belong to the closed interval $[0 , 10^{6}]$. The two last lines contain three integers each: $x_{A}, y_{A}, z_{A}$ and $x_{B}, y_{B}, z_{B}$ — coordinates of the camp A and the showplace $B$ .

The given triangles are guaranteed to describe a consistent continuous landscape. Projections of triangles onto $XY$ plane are non-degenerate and fill the square without overlapping. A vertex of one triangle never lays inside an edge of another triangle. Points $A$ and $B$ belong to the landscape surface and are different.


## 输出格式



Output a polyline route from $A$ to $B$ with the smallest possible topmost height. The first line should contain $m$ , the number of vertices in this polyline. Each of following $m$ lines should contain three integer coordinates of a polyline vertex: $x_{i}, y_{i},$ and $z_{i}.$ Vertices must be listed along the polyline, from $A$ to $B$ (including these two endpoints).

All coordinates of polyline vertices should be integer. Each polyline edge must belong to some triangle from the input file (possibly, to its edge). The number of vertices in the polyline must not exceed $5n$.


## 样例

### 样例输入 #1
```
8
1000000 0 0 1000000 1000000 150000 600000 600000 400000
0 1000000 0 600000 600000 400000 600000 1000000 300000
0 1000000 0 400000 300000 150000 600000 600000 400000
400000 0 200000 1000000 0 0 400000 300000 150000
400000 300000 150000 1000000 0 0 600000 600000 400000
600000 600000 400000 1000000 1000000 150000 600000 1000000 300000
0 0 0 400000 0 200000 400000 300000 150000
0 1000000 0 0 0 0 400000 300000 150000
100000 700000 37500
900000 400000 137500

```
### 样例输出 #1
```
4
100000 700000 37500
400000 300000 150000
900000 150000 100000
900000 400000 137500

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述

H正在和她的朋友在高原徒步，他们计划着从他们的营地A徒步到一个风景名胜B。

可惜的是，H有了点高原反应。请你帮助他们找到一条路线，使该路线的最高高度尽可能小。
![](https://cdn.luogu.com.cn/upload/image_hosting/o2199eky.png)（$1:10^5$）

### 输入格式

输入数据包含整个$10^6 \times 10^6$的的完整信息，格式如下：

第一行包含了一个整数$n$，表示着这个空间内的三角形的数量。接下来的$n$行，每行包含九个整数，分别是
$x_{i_1},y_{i_1},z_{i_1},x_{i_2},y_{i_2},z_{i_2},x_{i_3},y_{i_3},z_{i_3}$
，是一个三角形的坐标。每个三角形的坐标都在区间[$0, 10^6$]之间。最后两行分别包含了A处的坐标和B处的坐标。

给定的三角形保证在一个一致的坐标系。三角形在XY平面上的投影是非简并的，并且填充正方形而不重叠。一个三角形的顶点永远不会位于另一个三角形的边内。A点和B点属于同一个坐标系，且两者不同位置。

### 输出格式

输出从A到B的路线，其最高高度可能最小。第一行应包含m，即此多段线中的顶点数。下面的每m条线都应该包含多段线顶点的三个整数坐标。

顶点必须沿路线列出，从A到B（包括这两个端点）。
路线顶点的所有坐标都应为整数。每个多段线边必须属于输入文件（可能是其边）中的某个三角形。路线的拐点数不能超过5n。


---

---
title: "[NWRRC 2014] Kebab House"
layout: "post"
diff: 提高+/省选-
pid: P7070
tag: ['2014', 'ICPC']
---
# [NWRRC 2014] Kebab House
## 题目描述



The young man Vahtang Bumerang makes kebabs at the world-famous fast-food chain Kebab House. Each kebab contains many ingredients.

This morning Vahtang has received an order to make $n$ kebabs. At first, he should put $q_{1}$ ingredients to the first kebab, then $q_{2}$ ingredients in the second one and so on. Vahtang spends one second to put one ingredient to a kebab, so it takes $q_{i}$ seconds to make the i-th kebab. When he finishes the kebab he immediately proceeds to the next one.

Vahtang often dreams about his lovely boomerang while making kebabs. Each dream takes exactly one second and Vahtang forgets to put one ingredient to kebab during this second. Fortunately, he never dreams twice in any consecutive $(t + 1)$ seconds.

Due to dreams about boomerang, some kebabs may have lesser than the desired number of ingredients, but customers are still happy if the $i$-th kebab has at least $x_{i}$ ingredients in it.

Vahtang wants to calculate the number of ways to have dream seconds during his work while keeping all customers happy. Can you help him? The real answer may be very huge, so you have to calculate it modulo $10^{9} + 7$ .


## 输入格式



The first line of the input file contains two integers $n$ and $t$ — the number of kebabs and minimal possible time between dream seconds $(1 \le n \le 1000$ ; $0 \le t \le 100)$ .

Each of the next $n$ lines contains two integers $q_{i}, x_{i}$ — the number of ingredients in the $i$-th kebab and the minimum number of ingredients to make the $i$-th customer happy $(1 \le q_{i} \le 250$ ; $0 \le x_{i} \le q_{i}).$


## 输出格式



The only line of the output file must contain one integer -- the number of ways to distribute dream seconds modulo $10^{9} + 7$ .


## 样例

### 样例输入 #1
```
3 1
4 3
2 2
2 1

```
### 样例输出 #1
```
15

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

## 题目描述

一个叫Vahtang Bumerang的年轻人在世界知名的连锁快餐店做肉串，每个肉串包含许多成分。

今晨，VB接到了一个肉串订单，首先，他应该将$ q_{1}$种配料放入第一个烤肉串，将$ q_{2}$种配料放入第二个，依此类推。VB将一种配料放进一个肉串需要 $1$ 秒，所以做第 $i$ 个肉串需要 $q_{i}$ 秒。当他完成一个肉串时，他会立即制作一个肉串。

VB在做肉串时经常梦见他可爱的boomerang，做一次梦要一秒钟，而VB却忘了在这一秒钟里将一种配料放到肉串上。幸运的是，他从不在任何连续的 $ (t + 1) $ 秒内做梦超过一次。

由于梦见boomerang，一些肉串可能少于订单所需的配料数量，但如果第 $i$ 个肉串中至少含有 $x_{i}$ 种配料，则客户仍然会感到满意。

VB想知道在让顾客开心的前提下自己有多少种不同的梦见boomerang的方案，请你计算在满足条件下分配做梦秒数的方法数量，答案可能很大，请输出其对$ 10^{9} + 7 $ 取模的结果。

## 输入格式

第一行包含两个整数 $n$ 和 $t$ ，表示烤肉串的数量和两次幻想之间的最小可能秒数。$ (1 \le n \le 1000, 0≤t≤100) $

接下来 $n$ 行，每行包含两个整数 $ q_{i}, x_{i}$ 表示第 $i$ 个订单规定肉串中的配料数量以及使第 $i$ 个客户满意的最少配料数量。$(1 \le q_{i}≤250 ; 0 \le x_{i} \le q_{i})$

输出仅一行，包含一个整数-以模数形式分配梦想秒数的方法数量在 $mod$  $10^9+7$ 意义下的答案。

## 说明/提示

时间限制: 2 s, 空间限制: 256 MB


---

---
title: "[NWRRC 2013] Dwarf Tower"
layout: "post"
diff: 提高+/省选-
pid: P7082
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Dwarf Tower
## 题目描述

Little Vasya is playing a new game named "Dwarf Tower". In this game there are $n$ different items, which you can put on your dwarf character. Items are numbered from $1$ to $n$ . Vasya wants to get the item with number $1$ .

There are two ways to obtain an item:

You can buy an item. The i-th item costs $c_i$ money.

You can craft an item. This game supports only $m$ types of crafting. To craft an item, you give two particular different items and get another one as a result.

Help Vasya to spend the least amount of money to get the item number $1$ .

## 输入格式

The first line contains two integers $n$ and $m (1 \le n \le 10000 , 0 \le m \le 100000) -$ the number of different items and the number of crafting types.

The second line contains $n$ integers $c_i -$ values of the items $(0 \le c_i \le 10^9)$ .

The following $m$ lines describe crafting types, each line contains three distinct integers $a_i, x_i, y_i$ -- $a_i$ is the item that can be crafted from items $x_i$ and $y_i (1 \le  a_i, x_i, y_i \le n , a_i \ne x_i, x_i \ne y_i, y_i \ne a_i)$.
## 输出格式


Print a single integer -- the least amount of money to spend. 
## 样例

### 样例输入 #1
```
5 3
5 0 1 2 5
5 2 3
4 2 3
1 4 5

```
### 样例输出 #1
```
2

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述
小Vasya 在玩一个新游戏叫做 Dwarf Tower。在这个游戏中有 $n$ 个不同的衣物给你的矮人。衣物从 $1$ 到 $n$ 进行编号。Vasya 想要获得编号为 $1$ 的衣物。

现在有两种方法获得一件衣物：

1. 你可以买它，第 $i$ 件物品花费 $c_i$ 元。

1. 你还可以制作它，这个游戏支持 $m$ 中制作方法。要制作一个衣物，你需要花费两个特定的衣物。

算出 Vasya 至少需要多少钱来获得一号衣物。

### 输入格式
第一行输入两个整数 $n$ , $m$ $(1 \le n \le 10000 , 0 \le m \le 100000) $ 代表有 $n$ 种衣物和有 $m$ 种制作方法。

第二行输入 $n$ 个整数，第 $i$ 个整数代表 $c_i$ $(0 \le c_i \le 10^9)$ 。

接下来 $m$ 行每行有三个整数 $a_i, x_i, y_i$ $(1 \le a_i, x_i, y_i \le n , a_i \ne x_i, x_i \ne y_i, y_i \ne a_i)$ ，$a_i$ 代表 $a_i$ 可以被 $x_i$ 和 $y_i$ 制作。

### 输出格式
一个整数，代表 Vasya 至少需要多少钱来获得一号衣物。


---

---
title: "[NWRRC 2013] J"
layout: "post"
diff: 提高+/省选-
pid: P7088
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] J
## 题目描述



The $J$ programming language, developed in the early $1990s$ by Kenneth $E$ . Iverson and Roger Hui, is a synthesis of APL (also by Iverson) and the FP and FL function-level languages created by John Backus.

Wikipedia. $J$ (programming language)

APL language family is famous for its support of advanced operations on vectors and arrays, and $J$ is not an exception. For example, all unary and binary numeric operations in these languages by default are applicable to vectors and arrays of different dimensions. Plus operation $(‘+')$ can add not only scalars, like in other languages, but also scalars and vectors (the scalar is added to each component of the vector), or vectors and vectors (the vectors are added component-wise).

The expressive power of $J$ is amazing (as well as its cryptic syntax), but for this problem we need just a small subset of the language. We consider a single expression, where we may use one vector variable $X$ , one scalar variable $N$ -- the length of the vector $X$ , and the following operations:

We can add $(‘+'),$ subtract $(‘-')$ or multiply $(‘ \times ')$ two vectors, vector and scalar, or two scalars.

We can use unary minus $(‘-')$ and unary squaring operations $(‘ \times :')$ for scalars and vectors $(component-wise).$

We can fold a vector with plus operation $(‘+/')$ -- that is, compute the sum of a vector (unary operation).

Operations are evaluated right-to-left, natural precedence of operations is ignored in $J$ . The order of evaluation can be altered by parentheses. More precisely the syntax is specified in the following BNF.

$〈expressio_n〉 ::= 〈ter_m〉 | 〈ter_m〉 (‘+' | ‘-' | ‘ \times ') 〈expressio_n〉 | (‘-' | ‘ \times :' | ‘+/') 〈expressio_n〉$

$〈ter_m〉 ::= ‘('〈expressio_n〉‘)' | ‘X' | ‘N' | 〈number〉$

$〈number〉 ::= (‘0' | ‘1' |$ . . . $| ‘9')^{+}$

To correctly impose one more limitation on expression syntax, let us define complexity of an expression:

complexity of scalars (numbers, $‘N',$ and result of fold) is zero;

complexity of $‘X'$ is one;

complexity of addition and subtraction is the maximum of their operands' complexities;

complexity of multiplication is the sum of its operands' complexities;

complexity of unary squaring is twice the complexity of its operand.

For example, the complexity of expression $`(3-+/ \times : \times :X)-X \times \times :X`$ is $3$ , while the complexity of its subexpression $` \times : \times :X`$ is $4$ .

Your program is given a scalar-valued expression and a value of the vector $X$ , and it should compute the expression result modulo $10^{9}.$ The complexity of each subexpression in the given expression does not exceed $10$ .


## 输入格式



The first line contains one integer number $N (1 \le N \le 10^{5})$ -- the length of the vector $X$ .

The second line contains $N$ integers -- components of the vector $X (0 \le X_{i} < 10^{9}).$

The third line contains the expression to be computed, a non-empty string of not more than $105$ symbols. Each number in the expression is less than $109$ . The fold is never applied to a scalar.


## 输出格式



Output a single integer number -- the expression result modulo $10^{9}.$


## 样例

### 样例输入 #1
```
5
1 2 3 4 5
+/*:X

```
### 样例输出 #1
```
55

```
### 样例输入 #2
```
5
1 2 3 4 5
N++/X-X+1

```
### 样例输出 #2
```
0

```
### 样例输入 #3
```
3
11 56 37
+/(3-+/*:*:X)-X**:X

```
### 样例输出 #3
```
964602515

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

本题中，J 语言为一个表达式，满足如下的 Backus-Naur 范式：
```
<expression> ::= <term> | <term> ('+' | '-' | '*') <expression> | ('-' | > '*:' | '+/') <expression>
<term> ::= '(' <expression> ')' | 'X' | 'N' | <number>
<number> ::= ('0' | '1' | ... | '9')+
```
对于一个双目运算符，当操作数为数值和向量时，它的效果是将数值和向量中的每一维分量分别做运算；当操作数为两个向量时，它的效果是将向量中的每一维分量对应做运算。特别地，在本题中，所有的向量均相同。  

Backus-Naur 范式中出现的记号解释如下：
- 加法、减法、乘法运算 `'+','-','*'`
- 单目运算 `'-','*:','+/'`。`-A` 表示对 A 取负，`*:A` 表示对 A 求平方，`+/` A 称为**折叠**，表示对向量 A 的所有分量求和。
- 括号 `'(',')'`。没有括号时，所有运算符优先级相同，括号可以改变运算顺序，效果同通常的括号。
- 数字。
- 字母 `'N','X'`。N 在处理时等价于一个事先被给定的数字，X 则等价于一个事先被给定的向量。
- 单元。表达式、数字和字母被统称为单元。
- 表达式。若干个单元用双目和单目运算符按照符合语法规则的方式连接起来，所得到的字符串称为一个表达式。表达式中不得包含上文中没有提到的其他字符。
- 注意：J 语言的表达式是**右结合**的，你可以理解为从右往左计算，但是对于不满足交换律的减法操作，我们规定 `A-B` 仍然表示用 A 减去 B 而不是 B 减去 A。对于一个数字，我们规定它仍然是从左往右读的。比如 `123` 应当理解为 100+20+3 而不是 300+20+1。

每个表达式被定义了一个**复杂度**，我们规定所有数值（标量）的复杂度为 0，`X` 的复杂度为 1，加法运算和减法运算 `A+B,A-B` 的复杂度为 `A` 和 `B` 复杂度的最大值。`A*B` 的复杂度为两者复杂度之和，单目取反运算不改变表达式的复杂度，平方运算将表达式的复杂度变成它的两倍，折叠运算将表达式的复杂度变成 0。

你首先需要读入 $N,X(N\le10^5)$，保证 N 等于 X 的长度。X 中所有分量全为不超过 $10^9$ 的正整数。然后一行读入一个表达式 `expr`，保证它的复杂度不超过 10，并且长度不超过 $10^5$ 个字符，且完全符合语法规则。你需要求出 `expr` 的值模 $10^9$ 的结果（保证值一定是个标量而不是向量）。

translated by @Starlight237


---

---
title: "[NWRRC 2013] Kids in a Friendly Class"
layout: "post"
diff: 提高+/省选-
pid: P7089
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NWRRC 2013] Kids in a Friendly Class
## 题目描述

Kevin resembles his class in primary school. There were girls and boys in his class. Some of them were friends, some were not. But if one person considered another person a friend, the opposite was also true.

Interestingly, every girl had exactly a friends among girls and exactly $b$ friends among boys, whereas every boy had exactly $c$ friends among girls and exactly $d$ friends among boys.

Kevin does not remember the size of his class. Help him reconstruct the class with minimal possible number of kids, such that the above conditions are satisfied.
## 输入格式

The only line contains four integers $a , b , c$ , and $d (1 \le a , b , c , d \le 50)$ .

## 输出格式


Output an example of a class of minimal possible size satisfying the above conditions.

The first line should contains two positive integers: $m$ -- the number of girls, and $n$ -- the number of boys.

Let's assign numbers $1$ through $m$ to the girls and $m + 1$ through $m + n$ to the boys.

Each of the next lines should contain a pair of distinct integers describing a pair of friends by their numbers. Each pair of friends should appear exactly once in this list. 
## 样例

### 样例输入 #1
```
1 2 1 2

```
### 样例输出 #1
```
2 4
1 2
1 3
1 5
2 4
2 6
3 4
3 5
4 6
5 6

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述
凯文的班级里有女生也有男生。他们中有些人是朋友，有些人不是。但是，如果A认为B是他的朋友，那么B也认为A是他的朋友。

有趣的是，每个女生都有 a 个女性朋友和 b 个男性朋友，而每个男生都有 c 个女性朋友和 d 个男性朋友。

凯文不记得自己班级的人数。请算出班级的人数，使得班级人数尽可能少，同时又能满足上面的条件。
### 输入格式
只有一行，包括4个整数 a , b , c，d (1≤a,b,c,d≤50) .
### 输出格式
输出一个班级人数，使得其数量尽可能小又满足上述条件。

第一行应该包括两个正整数 m —— 女生人数 n —— 男生人数。

用编号1 到 m 表示女生，编号 m+1 到m+n 表示男生。

接下来的每一行，都应该包含一对不同的整数，来表示一对朋友，而且每对朋友只出现一次。


---

---
title: "[CERC2018] Game of Stones"
layout: "post"
diff: 提高+/省选-
pid: P7467
tag: ['2018', 'ICPC']
---
# [CERC2018] Game of Stones
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [Game of Stones](https://contest.felk.cvut.cz/18cerc/solved/stones.pdf)**

Petyr 和 Varys 两个人在玩游戏。游戏中选手从 $N$ 堆石子中轮流取走一些石子。在自己的回合中，Petyr 可以从任意一堆中取走最多 $A$ 个石子，Varys 可以从任意一堆中取走最多 $B$ 个石子。每一轮选手至少要取走一个石子。取走最后一个石子的一方获胜。

游戏已经开始，并且现在 Petyr 要取石子。你的任务是判断在双方均采用最优策略的情况下 Petyr 是否能赢。
## 输入格式

输入的第一行包含三个整数 $N,A,B$，表示有 $N$ 堆石子和两人的限制。

第二行 $N$ 个数 $X_1,X_2,…,X_N$，表示当前所有堆中石子个数。
## 输出格式

输出获胜者的名字。
## 样例

### 样例输入 #1
```
2 3 4
2 3
```
### 样例输出 #1
```
Petyr
```
### 样例输入 #2
```
7 8 9
1 2 3 4 5 6 7
```
### 样例输出 #2
```
Varys
```
## 提示

$1≤N,A,B,≤10^5,1≤X_i≤10^6$


---

---
title: "[ICPC 2020 WF] The Cost of Speed Limits"
layout: "post"
diff: 提高+/省选-
pid: P8129
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] The Cost of Speed Limits
## 题目背景

ICPC2020 WF B
## 题目描述

By the year 3031, the ICPC has become so popular that a whole new town has to be built to house all the
World Finals teams.
The town is beautifully designed, complete with a road network.
Unfortunately, when preparing the budget, the town planners forgot to take into account the cost of speed-limit signs.
They have asked you to help them determine the minimum additional funds they will need.

The ICPC road network consists of roads, each connecting two intersections. Each road is two-way
and has already been assigned a speed limit, valid for both directions.
To save money, the minimum possible number of roads was used. In other words, there is exactly
one route from any intersection to any other intersection.

The speed-limit signs need to be installed
in all places where the speed limit may change for any driver that follows any route.
More precisely, if there exists an intersection where at least two roads meet with different speed limits,
then *all* of the roads going from that intersection need a speed-limit sign installed at that intersection. 
Note that some roads might need two speed-limit signs, one at each end.

It costs $c$ dollars to install one speed-limit sign. It is also possible to improve the safety and quality of
any road so that its speed limit can be increased, which may in turn reduce the number of speed-limit signs required.
It costs $x$ dollars to increase the speed limit of one road by $x$ km/h (in both directions).
To avoid complaints, the town council does not allow decreasing any of the already-assigned speed limits.

Figure B.1 illustrates the situation given in both Sample Input 1 and Sample Input 2.


![](https://cdn.luogu.com.cn/upload/image_hosting/4kx82pq4.png)
## 输入格式

The first line of input contains two integers $n$ and $c$, where $n$ ($1 \le n \le 20\,000$) is the number of intersections
and $c$ ($1 \le c \le 10^5$) is the cost of installing one sign.
Each of the remaining $n-1$ lines contains three integers $u$, $v$, and $s$, where $u$ and $v$ ($1 \le u, v \le n; u \ne v$)
are the intersections at the ends of a road, and $s$ ($1 \le s \le 10^5$) is the current speed limit of that
road in kilometers per hour.
## 输出格式

Output the minimum cost to upgrade roads and install speed-limit signs such that the town
plan satisfies all the rules above.
## 样例

### 样例输入 #1
```
5 2
1 2 10
1 3 5
1 4 7
2 5 9
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
5 100
1 2 10
1 3 5
1 4 7
2 5 9
```
### 样例输出 #2
```
9
```
## 题目翻译

到 3031 年，ICPC 已经变得如此受欢迎，以至于必须建造一个全新的 ICPC 镇来容纳所有参加 World Finals 的队伍。这座城镇设计精美，有完整的道路网。不幸的是，在编制预算时，城市规划者忘记了考虑限速标志的成本。他们要求你帮助他们确定他们需要的最低额外资金。

ICPC 镇的道路网由道路组成，每条道路连接两个十字路口。每条道路都是**双向**的，并且已经指定了一个速度限制 $s$，对两个方向都有效。为了省钱，ICPC 镇使用了尽可能少的道路。换句话说，从任何交叉口到任何其他交叉口只有一条路线。

限速标志需要安装在所有可能改变任何路线驾驶员限速的地方。更准确地说，如果存在至少两条道路满足不同限速要求的交叉口，那么从该交叉口出发的所有道路都需要在该交叉口安装限速标志。请注意，有些道路可能需要两个限速标志，每端一个。

安装一个限速标志需要花费 $c$ 美元。还可以提高任何道路的安全性和质量，从而提高其限速，从而减少所需限速标志的数量。将一条道路的限速提高 $x$ 公里每小时（**双向**）需要 $x$ 美元。为了避免投诉，市议会**不允许降低任何已经指定的限速**。

数据范围：

- $1\leqslant n\leqslant 2\times 10^4$，$1\leqslant c\leqslant 10^5$。
- $1\leqslant s\leqslant 10^5$。

Translated by Eason_AC


---

---
title: "[ICPC 2020 WF] ’S No Problem"
layout: "post"
diff: 提高+/省选-
pid: P8137
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] ’S No Problem
## 题目背景

ICPC2020 WF J
## 题目描述

The Yllihc Engineering and Technological Institute (YETI),
located in upper northern Snowblovia, has two problems: snow
and money. Specifically, they have too much of the former and not
enough of the latter. Every winter (and fall and spring for that matter)
the campus is covered with blankets of snow. The maintenance staff
must clear all the sidewalks connecting the campus buildings, but they
have only two snow blowers and have been told in no uncertain
terms that they cannot expect to obtain any more in the near future.

To preserve the longevity of these two precious machines,
the staff has decided on the following snow removal procedure.
Each machine is assigned a fixed route connecting two of the
buildings on campus. Whenever snow must be removed, each snow blower
is taken from the building at one end of its route and used to clear snow,
ending up in the building at the other end of its route, where it is
stored until the next snowfall.
The reverse movement will occur during the next snow removal event---each
machine will trace its assigned route in the opposite direction.
This process cycles throughout the eleven-month snow season.
Note that a route might involve doubling back over sidewalks that
have already been cleared. Also, it is
possible that the same building might be an endpoint for both
snow blower routes.

The campus sidewalks are laid out in the form of a tree.
To run the machines as little as possible, the staff wants
to minimize the total distance
that the snow blowers must travel as they are guided along their routes.
Figure J.1 shows an optimal
solution for the sidewalk layout of the first sample input.

![](https://cdn.luogu.com.cn/upload/image_hosting/xu2fv7az.png)

The YETI maintenance crew would ask the Computer Science Department
at YETI to figure this out, but they were wiped out in the Great
Blizzard of '$06$, so they have come to you for help.
## 输入格式

The first line of input contains an integer $n$ ($4\leq n\leq 100\,000$),
the number of buildings on the YETI campus. Buildings are numbered from $1$
to $n$.
Each of the remaining $n-1$ lines contains three integers
$a$, $b$, and $d$
indicating that a two-way sidewalk exists between buildings $a$ and $b$
($1 \leq a, b \leq n$; $a\ne b$) of length $d$ ($1\leq d\leq 500$).
## 输出格式

Output the minimum total distance the two machines must travel in
any snow removal event.
## 样例

### 样例输入 #1
```
7
1 4 2
2 4 3
3 4 1
4 5 1
5 6 2
5 7 4
```
### 样例输出 #1
```
15
```
### 样例输入 #2
```
4
1 2 1
2 3 2
3 4 3
```
### 样例输出 #2
```
6
```
## 题目翻译

## 题目描述
位于斯诺布洛维亚北部的 某·工程技术学院 (YETI) 面临两个问题：雪和金钱。具体来说，他们有太多的前者而没有足够的后者。每年冬天（以及秋天和春天），校园都覆盖着雪毯。维护人员必须清理连接校园建筑的所有人行道，但他们只有两台吹雪机，并且已经明确告知他们在不久的将来不能再获得更多。

为了保持这两台珍贵机器的使用寿命，工作人员决定采用以下除雪程序。每台机器都被分配了一条连接校园内两座建筑物的固定路线。每当必须除雪时，每台吹雪机都会从其路线一端的建筑物中取出并用于清除积雪，最终进入其路线另一端的建筑物中，并存放在那里直到下一次降雪。在下一次除雪活动期间将发生反向运动——每台机器将沿相反方向追踪其分配的路线。这个过程在整个 1 个月的雪季循环。请注意，路线可能涉及翻过已清理的人行道。此外，同一建筑物可能是两条吹雪机路线的终点。

校园人行道以树的形式布置。为了尽可能少地运行机器，工作人员希望尽量减少吹雪机在沿路线引导时必须行驶的总距离。图 J.1 显示了第一个样本输入的人行道布局的最佳解决方案。

YETI 维护人员会要求 YETI 的计算机科学系解决这个问题，但他们在 06 年的大暴雪中失败了，所以他们来找你帮忙。
## 输入格式

输入的第一行包含一个整数 n(4≤n≤100000)，即 YETI 校园内的建筑物数量。 建筑物的编号从 1 到 n。其余n−1 行中的每一行包含三个整数 a、b和d，表示建筑物 a和 b之间存在双向人行道 (1≤a,b≤n) 长度为 d(1≤d≤500)。
## 输出格式
输出两台机器在任何除雪事件中必须行驶的最小总距离。


---

---
title: "[ICPC 2020 WF] Which Planet is This?!"
layout: "post"
diff: 提高+/省选-
pid: P8142
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Which Planet is This?!
## 题目背景

ICPC2020 WF O
## 题目描述

It's the year 2521, and interstellar probes have reached planets in distant
solar systems. The Interstellar Consortium of Planet Cartographers (ICPC) has
created detailed maps of these planets, and they seem to indicate the
existence of alien life! On each map, the ICPC has recorded the locations of
what appear to be alien dwellings.

The ICPC was planning to release this exciting news to the public, but at the
last moment, disaster struck. One of the ICPC's interns deleted all
meta-data associated with the maps. So while the maps themselves are safe, the
ICPC does not know which maps belong to which planets. For this, they have come back
in time to ask for your help. Given two maps, can you determine whether they describe the same planet?
Hopefully, a 500-year head start will be enough time to solve this important
problem!

The planetary maps consist of sets of points on the (spherical) planet
surface. They are specified in terms of latitude (the angle north or south of
the equator) and longitude (the angle west or east of the noon meridian, which
is the location of the sun when the map's data was collected). Two maps for
the same planet always agree on the latitudes of the points, since the
planet's axis does not change. However, the longitudes of the points might
differ, because the planet rotates between measurements.
## 输入格式

The first line of input contains an integer $n$ ($1 \le n \le 400\,000$), the
number of points in each of the two maps to be compared. Then follow $n$ lines
describing the first map. Each of these lines contains two real numbers $a$
and $b$, where $a$ ($-90 < a < 90$) is the latitude and $b$ ($-180 < b \le
180$) is the longitude. Coordinates are expressed in degrees and have at most
four digits after the decimal point. No two points on the map will
have the same coordinates. The remaining $n$ lines describe the second map in the same format as the
first.
## 输出格式

Output $\texttt{Same}$ if there is a rotation around the planet's axis that transforms one map into
the other. Otherwise, output $\texttt{Different}$.
## 样例

### 样例输入 #1
```
4
0.0000 0.0000
30.0000 90.0000
-45.0000 -30.0000
30.0000 60.0000
30.0000 150.0000
30.0000 120.0000
0.0000 60.0000
-45.0000 30.0000
```
### 样例输出 #1
```
Same
```
### 样例输入 #2
```
3
0.0000 0.0000
30.0000 0.0000
30.0000 90.0000
0.0000 0.0000
30.0000 0.0000
30.0000 -90.0000
```
### 样例输出 #2
```
Different
```
## 题目翻译

### 题目描述
这是2521年，星际探测器已经到达了遥远的太阳系的行星。星际行星制图者联盟(ICPC)已经绘制了这些行星的详细地图，它们似乎表明外星生命的存在!ICPC在每张地图上都记录了疑似外星人住所的位置。

ICPC本打算向公众公布这一激动人心的消息，但在最后一刻，灾难发生了。ICPC的一名实习生删除了所有与地图相关的元数据。因此，虽然地图本身是安全的，但ICPC并不知道哪些地图属于哪些行星。为此，他们及时回来请求您的帮助。给定两幅地图，你能确定它们是否描述的是同一颗行星吗?希望领先500年的时间足以解决这个重要的问题!

行星图由(球面)行星表面的点集组成。它们是根据纬度(赤道南北的夹角)和经度(正午子午线的西半球或东半球的夹角，这是地图数据采集时太阳的位置)来指定的。同一颗行星的两幅地图在纬度上总是一致的，因为行星的轴是不变的。然而，这两个点的经度可能不同，因为行星在两次测量之间会旋转。

### 输入格式
输入的第一行包含一个整数$n$ ($1 \le n \le 400000=4\times10^5$)，这是要比较的两个地图射中每个地图中的点数。然后跟随描述第一张地图的$n$条线。每条线包含两个实数$a$和$b$，其中$a$($-90<a<90$)是纬度，$b$($-180<a<180$)是经度。坐标以度表示，小数点后最多有四位数字。地图上没有两个点的坐标是相同的。其余的$n$行以与第一个相同的格式描述第二个映射。

### 输出格式
如果有一种围绕行星轴旋转的方式使得地图1和地图2相同，输出`Same`，否则输出`Different`


---

---
title: "[ICPC 2022 Xi'an R] Cells Coloring"
layout: "post"
diff: 提高+/省选-
pid: P9359
tag: ['2022', '网络流', 'O2优化', '二分图', 'ICPC']
---
# [ICPC 2022 Xi'an R] Cells Coloring
## 题目描述

You are given an $n \times m$ grid. Some of the cells are obstacles, the others are empty. Choose a non-negative integer $k$ and color all empty cells with $k+1$ colors $0, 1, 2, \ldots k$. You can not color two cells in the same row or same column with the same **non-zero** color. 

You are given two non-negative integers $c$ and $d$. For a coloring plan, define $z$ as the number of the cells with color $0$. Define the cost of the plan is $ck+dz$.

Find the minimum cost.
## 输入格式

The first line contains four integers $n$, $m$ ($1\leq n, m\leq 250$), $c$ and $d$ ($0\leq c, d\leq 10 ^ 9$).

The $i$-th line of the next $n$ lines contains a string of $m$ characters. The $j$-th character is `*` if the cell in the $i$-th row and the $j$-th column is an obstacle. The $j$-th character is `.` if the cell in the $i$-th row and the $j$-th column is empty.
## 输出格式

Output a line with a single number, representing the answer.
## 样例

### 样例输入 #1
```
3 4 2 1
.***
*..*
**..

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
3 4 1 2
.***
*..*
**..

```
### 样例输出 #2
```
2
```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem B.

**Author**: csy2005.
## 题目翻译

### 题目描述

给定一个 $n\times m$ 的网格。一些格子是障碍，其它格子是空的。选择一个非负整数 $k$，并用 $k + 1$ 种颜色 $0, 1, \ldots, k$ 给空格子染色。不能有同一行或同一列的两个格子被染成了相同的 **非零** 颜色。

给定两个非负整数 $c, d$。对于一组染色方案，定义 $z$ 表示染成颜色 $0$ 的格子数量，则该方案的代价为 $ck + dz$。

求出最小代价。

$1\leq n, m \leq 250$，$0\leq c, d\leq 10 ^ 9$。

### 输入格式

第一行四个整数 $n, m, c, d$。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串。字符串的第 $j$ 个字符为 `*` 表示第 $i$ 行第 $j$ 列的格子为障碍，为 `.` 表示为空。

### 输出格式

输出一行一个整数表示答案。




---

---
title: "[ICPC 2021 WF] Crystal Crosswind"
layout: "post"
diff: 提高+/省选-
pid: P9439
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Crystal Crosswind
## 题目描述

You are part of a scientific team developing a new technique to image crystal structures at the molecular level. The technique involves blowing a very fine wind over the surface of the crystal at various angles to detect boundaries (indicated by molecules that are exposed to the wind). This is repeated with different wind directions and the boundaries observed for each direction are recorded. Your team has already collected the data, but – as is often the case with applied science – now the real work, analysis, must begin.

For a given crystal, you will receive the directions in which wind blew over the surface, and the locations of all boundaries encountered by each of these winds. For a wind blowing in direction ($w_x, w_y$), a boundary is defined as a location ($x, y$) such that a molecule exists at ($x, y$) and no molecule exists at ($x-w_x, y-w_y$). Note that for technical reasons $w_x$ and $w_y$ are not necessarily relatively prime.

The data might not uniquely determine the structure of the crystal. You must find the two unique structures with the minimal and maximal number of molecules consistent with the observations.

For example, in the first sample input, nine different molecules are directly encountered by the given winds. There must be a molecule at location ($3, 3$) because otherwise ($4, 2$) would be a boundary for the third wind. For similar reasons, there must be molecules at ($4, 4$) and ($5, 5$). There cannot be any further molecules as they would result in additional observations for some of the winds.
## 输入格式

The first line of input contains three integers $d_x$, $d_y$, and $k$, where $d_x$ and $d_y$ ($1 \leq d_x, d_y \leq 10^3$) are the maximum dimensions of the crystal structure, and $k (1 \leq k \leq 10)$ is the number of times wind was blown over the crystal.

Each of the remaining $k$ lines specifies the data for one wind. These lines each start with two integers $w_x$ and $w_y$ ($-d_x \leq w_x \leq d_x$ and $-d_y \leq w_y \leq d_y$, but not both zero) denoting the direction of the wind. Then comes an integer $b$ ($0 \leq b \leq 10^5$) giving the number of boundaries encountered by this wind. The line finishes with $b$ distinct pairs of integers $x,y$ ($1 \leq x \leq d_x$ and $1 \leq y \leq d_y$) listing each observed boundary.

You may assume the input is consistent with at least one crystal and that no molecules exist outside the specified dimensions.
## 输出格式

Output two textual representations of the crystal structure separated by an empty line. Each structure has $d_y$ rows of $d_x$ characters, with the top-left corner corresponding to location ($1, 1$). The first is the structure with the minimal number of molecules consistent with the observations, the second is the maximal one. Use '#' for a location where a molecule exists and '.' for a location where no molecule exists.
## 样例

### 样例输入 #1
```
6 6 3
1 1 3 3 1 1 3 2 2
0 2 6 3 1 1 3 2 2 6 4 5 3 4 2
1 -1 4 1 3 2 4 3 5 4 6

```
### 样例输出 #1
```
..#...
.#.#..
#.#.#.
.#.#.#
..#.#.
...#..

..#...
.#.#..
#.#.#.
.#.#.#
..#.#.
...#..

```
### 样例输入 #2
```
5 4 2
1 0 6 1 1 4 1 2 2 5 2 2 3 3 4
0 -1 7 1 1 4 1 5 2 2 3 3 4 4 4 5 4

```
### 样例输出 #2
```
#..#.
.#..#
.#...
..###

##.##
.##.#
.###.
..###

```
## 题目翻译

## 题目描述
你是一个科学团队中的一员，正在开发一种在分子级别上成像晶体结构的新技术。这种技术涉及在晶体表面吹送一股非常微弱的风，并以不同的角度吹送，以便检测边界（通过暴露给风的分子来表示）。这个过程会重复进行，每个吹送方向的边界都会被记录下来。你的团队已经收集到了数据，但是如同大多数应用科学一样，现在真正的工作，即分析工作必须开始。

对于给定的晶体，你将接收到风以不同方向吹送过晶体表面的数据，以及每个风吹过时遇到的所有边界的位置。对于在方向（$w_x, w_y$）吹送的风，边界被定义为位置（$x, y$），使得一个分子位于（$x, y$），并且没有分子位于（$x-w_x, y-w_y$）。请注意，出于技术原因，$w_x$ 和 $w_y$ 不一定互质。

这些数据可能无法唯一确定晶体的结构。你必须找到两个与观测数据一致且分子数最少和最多的晶体结构。

例如，在第一个示例输入中，通过给定的风，出现了9个不同的分子。必须有一个在位置（$3, 3$）处的分子，否则（$4, 2$）将成为第三股风的边界。出于类似的原因，必须在位置（$4, 4$）和（$5, 5$）处有分子。不能再有其他分子，因为它们会导致一些风的附加观测结果。

## 输入格式

输入的第一行包含三个整数 $d_x$、$d_y$ 和 $k$，其中 $d_x$ 和 $d_y$（$1 \leq d_x, d_y \leq 10^3$）是晶体结构的最大尺寸，$k$（$1 \leq k \leq 10$）是风吹过晶体的次数。

接下来的 $k$ 行中，每一行都描述了一次吹风的数据。第一对整数 $w_x$ 和 $w_y$（$-d_x \leq w_x \leq d_x$，$-d_y \leq w_y \leq d_y$，但不能同时为零）表示风的方向。然后是一个整数 $b$（$0 \leq b \leq 10^5$），表示这股风遇到的边界数量。接下来的 $b$ 对不同的整数 $x$、$y$（$1 \leq x \leq d_x$，$1 \leq y \leq d_y$）表示每个观测到的边界。

你可以假设输入数据与至少一个晶体是一致的，并且没有分子存在于指定尺寸范围之外。

## 输出格式

输出两个晶体结构的文本表示，两个结构之间用一个空行分隔。每个结构有 $d_y$ 行，每行有 $d_x$ 个字符，左上角对应位置（$1, 1$）。第一个结构是与观测结果一致的包含最少分子数量的结构，第二个结构是包含最多分子数量的结构。使用 '#' 表示分子存在的位置，使用 '.' 表示分子不存在的位置。


---

---
title: "[ICPC 2021 WF] Fair Division"
layout: "post"
diff: 提高+/省选-
pid: P9441
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Fair Division
## 题目描述

After sailing the Seven Seas and raiding many ships, Cap'n Red and his crew of fellow pirates are finally ready to divide their loot. According to ancient traditions, the crew stands in a circle ordered by a strict pirate hierarchy. Cap'n Red starts by taking a fraction $f$ of the loot and passing the remainder on to the next pirate. That pirate takes the same fraction $f$ of the loot left over by the previous pirate and passes the remainder on to the following pirate. Each pirate behaves in the same way, taking a fraction $f$ of what is left and passing on the rest. The last pirate in the hierarchy passes the remainder on to Cap'n Red, who starts another round of this "fair" division, and so on, indefinitely.

Fortunately, pirates in the 21st century can use a computer to avoid this lengthy process and constant nitpicking when the fraction $f$ does not exactly divide the loot at some step. You have been captured by the pirates and asked to come up with a suitable fraction $f$. As an incentive, Cap'n Red has promised to leave you alive if you succeed.

The fraction $f$ needs to be a rational number strictly between $0$ and $1$. It is not necessary that $f$ exactly divides the loot remaining at any step of the round-robin process described above. However, the total loot that would be assigned to each pirate by carrying out this process infinitely needs to be an integer.
## 输入格式

The input contains one line with two integers $n$ and $m$, where $n$ ($6 \leq n \leq 10^6$) is the number of pirates including Cap'n Red and $m$ ($1 \leq m \leq 10^{18}$) is the total value of their loot.
## 输出格式

Output one line with two positive integers $p$ and $q$, where $f = \frac{p}{q}$ as specified above. If there are multiple suitable fractions, choose one with the smallest $q$. Among multiple suitable fractions with the same smallest $q$ choose the one with the smallest $p$. If there is no suitable fraction, output $\texttt{impossible}$ instead and hope for mercy.
## 样例

### 样例输入 #1
```
8 51000

```
### 样例输出 #1
```
1 2
```
### 样例输入 #2
```
6 91000

```
### 样例输出 #2
```
2 3

```
### 样例输入 #3
```
10 1000000000000000000

```
### 样例输出 #3
```
impossible

```
## 题目翻译

### 题目描述
$n$ 个人按如下的方式分 $m$ 块钱：先指定一个分数 $f$，$n$ 个人围成一圈，第一个人先拿走总钱数的 $f$，把剩下的钱给第二个人，然后第二个人拿走剩余钱数的 $f$，把剩下的钱交给第三个人...每一个人都从剩余的钱中拿走剩余钱数的 $f$，然后把钱交给下一个人。这种操作可以无限进行下去。

现在给定 $n,m$，你需要构造 $f=\dfrac{p}{q}$，使得 $0<f<1$，并且在分钱无限进行下去之后，最终每个人拿到的钱都是整数。如果有多解，你构造的解需要在 $q$ 尽可能小的情况下 $p$ 尽可能小。如果无解，输出 `impossible`。

$6\le n\le 10^6$，$1\le m\le 10^{18}$。

### 输入格式

仅一行两个整数 $n,m$，含义如题目所述。
### 输出格式
如果有解，输出一行两个整数 $p,q$，分别是你构造的分数 $f$ 的分子和分母。

如果无解，输出 `impossible`。


---

---
title: "[ICPC 2021 WF] Prehistoric Programs"
layout: "post"
diff: 提高+/省选-
pid: P9446
tag: ['2021', 'Special Judge', 'ICPC']
---
# [ICPC 2021 WF] Prehistoric Programs
## 题目描述

Archaeologists have discovered exciting clay tablets in deep layers of Alutila Cave. Nobody was able to decipher the script on the tablets, except for two symbols that seem to describe nested structures not unlike opening and closing parentheses in LISP. Could it be that humans wrote programs thousands of years ago?

Taken together, the tablets appear to describe a great piece of work $-$ perhaps a program, or an epic, or even tax records! Unsurprisingly, after such a long time, the tablets are in a state of disorder. Your job is to arrange them into a sequence so that the resulting work has a properly nested parenthesis structure. Considering only opening and closing parentheses, a properly nested structure is either

- $()$, or
- $(A)$, where $A$ is a properly nested structure, or
- $AB$, where $A$ and $B$ are properly nested structures.
## 输入格式

The first line of input contains one integer $n$ ($1 \leq n \leq 10^6$), the number of tablets. Each of the remaining $n$ lines describes a tablet, and contains a non-empty string of opening and closing parentheses; symbols unrelated to the nesting structure are omitted. The strings are numbered from $1$ to $n$ in the order that they appear in the input. The input contains at most $10^7$ parentheses.
## 输出格式

Output a permutation of the numbers from $1$ to $n$ such that concatenating the strings in this order results in a properly nested structure. If this happens for multiple permutations, any one of them will be accepted. If there is no such permutation, output $\texttt{impossible}$ instead.
## 样例

### 样例输入 #1
```
2
())())()
((()

```
### 样例输出 #1
```
2
1
```
### 样例输入 #2
```
5
(
))
((
))
(

```
### 样例输出 #2
```
1
5
3
4
2

```
### 样例输入 #3
```
2
((
)

```
### 样例输出 #3
```
impossible

```
## 题目翻译

给定 $n$ 个括号序列，要求以某个顺序排列这些序列后，连接起来，整个括号序是合法匹配的。输出连接顺序，无解输出 `impossible`。

translated by [liangbowen](https://www.luogu.com.cn/user/367488).


---

---
title: "[ICPC 2021 WF] Where Am I?"
layout: "post"
diff: 提高+/省选-
pid: P9450
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Where Am I?
## 题目描述

Who am I? What am I? Why am I? These are all difficult questions that have kept philosophers reliably busy over the past millennia. But when it comes to "Where am I", then, well, modern smartphones and GPS satellites have pretty much taken the excitement out of that question.

To add insult to the injury of newly unemployed spatial philosophers formerly pondering the "where" question, the Instant Cartographic Positioning Company (ICPC) has decided to run a demonstration of just how much more powerful a GPS is compared to old-fashioned maps. Their argument is that maps are useful only if you already know where you are, but much less so if you start at an unknown location.

For this demonstration, the ICPC has created a test area that is arranged as an unbounded Cartesian grid. Most grid cells are empty, but a finite number of cells have a marker at their center (see Figure L.1(a) for an example with five marked cells). All empty grid cells look the same, and all cells with markers look the same. Suppose you are given a map of the test area (that is, the positions of all the markers), and you are placed at an (unknown to you) grid cell. How long will it take you to find out where you actually are? ICPC's answer is clear: potentially a very, very long time, while a GPS would give you the answer instantly. But how long exactly?

![](https://cdn.luogu.com.cn/upload/image_hosting/ydxjurja.png)

Figure L.1: Sample grid and the order in which test subjects explore the grid.

In the trial, test subjects will explore their environment by following an expanding clockwise spiral whose first few steps are shown in Figure L.1(b). The starting cell is labeled "0", and the numbers show the order in which other cells are visited. The test subjects can see a marker only if they are at its grid cell, and they will stop their exploration as soon as they know where they are based on the grid cells that they have seen so far. That means that the observed sequence of empty and marked grid cells could have begun only at a single possible starting position. The grid is unbounded, but the exploration will be finite since once a test subject has seen all markers on the grid, they'll definitely know where they are.

Having hundreds of test subjects literally running in circles can be expensive, so the ICPC figures that writing a simulation will be cheaper and faster. Maybe you can help?
## 输入格式

The input describes a single grid. It starts with a line containing two integers $d_x$ , $d_y$ ($1 \leq d_x, d_y \leq 100$). The following $d_y$ lines contain $d_x$ characters each, and describe part of the test grid. The $i^{th}$ character of the $j^{th}$ line of this grid description specifies the contents of the grid cell at coordinate ($i$, $d_y-j+1$). The character is either '$\texttt{.}$' or '$\texttt{X}$', meaning that the cell is either empty, or contains a marker, respectively.

The total number of markers in the grid will be between $1$ and $100$, inclusive. All grid cells outside the range described by the input are empty.
## 输出格式


In ICPC's experiment, a test subject knows they will start at some position ($x$, $y$) with $1 \leq x \leq d_x$, $1 \leq y \leq d_y$.

Output three lines. The first line should have the expected number of steps needed to identify the starting position, assuming that the starting position is chosen uniformly at random. This number needs to be exact to within an absolute error of $10^{-3}$.

The second line should have the maximum number of steps necessary until one can identify the starting position.

The third line should list all starting coordinates ($x$, $y$) that require that maximum number of steps. The coordinates should be sorted by increasing $y$-coordinates, and then (if the $y$-coordinates are the same) by increasing $x$-coordinates.
## 样例

### 样例输入 #1
```
5 5
....X
.X...
.....
X..X.
..X..

```
### 样例输出 #1
```
9.960000000
18
(1,4) (4,5)

```
### 样例输入 #2
```
5 1
..XX.

```
### 样例输出 #2
```
4.600000000
7
(1,1) (5,1)

```
## 题目翻译

输入描述:

一个单独的网格。它以包含两个整数 dx, dy (1≤dx, dy≤100) 的一行开始。接下来的 dy 行每行包含 dx 个字符，并描述了测试网格的一部分。网格描述的第 i 行第 j 列的字符指定了坐标 (i, dy-j+1) 处网格单元的内容。字符可以为 '.' 或 'X'，分别表示该单元格为空或包含标记。

网格中标记的总数将在1到100之间，包括1和100。输入未包含的网格单元都为空。

输出三行。

第一行应该是估计需要识别起始位置的步骤数，假设起始位置是均匀随机选择的。这个数需要精确到$10^{-3}$的绝对误差。

第二行应该是识别起始位置所需的最大步骤数。

第三行应该列出所有需要最大步骤数的起始坐标(x, y)。坐标应按递增的y坐标排序，如果y坐标相同，则按递增的x坐标排序。


---

---
title: "[ICPC 2020 Nanjing R] Harmonious Rectangle"
layout: "post"
diff: 提高+/省选-
pid: P9629
tag: ['2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Harmonious Rectangle
## 题目描述

A vertex-colored rectangle is a rectangle whose four vertices are all painted with colors. For a vertex-colored rectangle, it's harmonious if and only if we can find two adjacent vertices with the same color, while the other two vertices also have the same color with each other.

For example, $\begin{bmatrix} 1 & 0\\ 1 & 0 \end{bmatrix}$, $\begin{bmatrix} 0 & 0\\ 1 & 1 \end{bmatrix}$ and $\begin{bmatrix} 1 & 1\\ 1 & 1 \end{bmatrix}$ are harmonious, while $\begin{bmatrix} 1 & 0\\ 0 & 1 \end{bmatrix}$ is not (same number for same color, and different numbers for different colors).

For each point in $\{(x,y) | 1 \le x \le n, 1 \le y \le m, x,y \in \mathbb{Z}\}$, where $\mathbb{Z}$ is the set of all integers, Kotori wants to paint it into one of the three colors: red, blue, yellow. She wonders the number of different ways to color them so that there exists at least one harmonious rectangle formed by the points, whose edges are all parallel to the $x$- or $y$-axis. That is to say, there exists $1 \le x_1 < x_2 \le n$ and $1 \le y_1 < y_2 \le m$ such that

$$\begin{cases}
\text{color}(x_1, y_1) = \text{color}(x_1, y_2)\\
\text{color}(x_2, y_1) = \text{color}(x_2, y_2)\\
\end{cases}
$$ 
or
$$\begin{cases}
\text{color}(x_1, y_1) = \text{color}(x_2, y_1)\\
\text{color}(x_1, y_2) = \text{color}(x_2, y_2)\\
\end{cases}
$$

where $\text{color}(x, y)$ is the color of point $(x, y)$.

Two coloring plans are considered different if there exists a point having different colors in the two coloring plans.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^4$) indicating the number of test cases. For each test case:

The first and only line contains three integers $n$, $m$($1 \le n, m \le 2 \times 10^3$).
## 输出格式

For each test case output one line containing one integer indicating the number of different ways of coloring modulo $(10^9 + 7)$.
## 样例

### 样例输入 #1
```
3
1 4
2 2
3 3
```
### 样例输出 #1
```
0
15
16485
```
## 题目翻译

### 题目描述

一个顶点着色的矩形是指四个顶点都被涂上颜色的矩形。对于一个顶点着色的矩形来说，如果我们可以找到两个相邻顶点的颜色相同，而另外两个顶点也互相颜色相同，则称这个矩形是和谐的。

例如，矩阵 
$\begin{bmatrix} 1 & 0\\ 1 & 0 \end{bmatrix}$，$\begin{bmatrix} 0 & 0\\ 1 & 1 \end{bmatrix}$ 和 $\begin{bmatrix} 1 & 1\\ 1 & 1 \end{bmatrix}$ 都是和谐的，而 $\begin{bmatrix} 1 & 0\\ 0 & 1 \end{bmatrix}$ 不是（相同的颜色有相同的数字，不同的颜色有不同的数字）。

对于集合中的每个点 $\{(x,y) |	1 \le x \le n, 1 \le y \le m, x,y \in \mathbb{Z}\}$，其中 $\mathbb{Z}$ 是所有整数的集合，Kotori 想将其涂成三种颜色之一：红色、蓝色或黄色。她想知道有多少种不同的着色方案，使得至少存在一个由这些点形成的边都平行于 $x$ 或 $y$ 轴的和谐矩形。也就是说，存在 $1 \le x_1 < x_2 \le n$ 和 $1 \le y_1 < y_2 \le m $，满足以下条件之一：

$\begin{cases} \text{color}(x_1, y_1) = \text{color}(x_1, y_2)\\ \text{color}(x_2, y_1) = \text{color}(x_2, y_2)\\ \end{cases}$

或者

$\begin{cases} \text{color}(x_1, y_1) = \text{color}(x_2, y_1)\\ \text{color}(x_1, y_2) = \text{color}(x_2, y_2)\\ \end{cases}$

其中 $\text{color}(x, y)$ 表示点 $(x, y)$ 的颜色。

如果两个着色计划中存在一个点在两个着色计划中颜色不同，那么认为这两个着色计划是不同的。

### 输入格式：
输入包含多个测试用例。第一行输入一个整数 $T$ $(1 \le T \le 10^4)$，表示测试用例的数量。对于每个测试用例：

第一行输入三个整数 $n, m$ $(1 \le n, m \le 2 \times 10^3)$，表示边界的大小。

### 输出格式：
对于每个测试用例，输出一行，包含一个整数，表示着色的不同方案数量模 $(10^9 + 7)$。


---

---
title: "[ICPC 2020 Nanjing R] Monster Hunter"
layout: "post"
diff: 提高+/省选-
pid: P9634
tag: ['动态规划 DP', '2020', 'Special Judge', 'O2优化', '树形 DP', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Monster Hunter
## 题目描述

There is a rooted tree with $n$ vertices and the root vertex is $1$. In each vertex, there is a monster. The hit points of the monster in the $i$-th vertex is $hp_i$.

Kotori would like to kill all the monsters. The monster in the $i$-th vertex could be killed if the monster in the direct parent of the $i$-th vertex has been killed. The power needed to kill the $i$-th monster is the sum of $hp_i$ and the hit points of all other living monsters who lives in a vertex $j$ whose direct parent is $i$. Formally, the power equals to 
$$
hp_i + \sum_{\begin{array}{c}\text{the monster in vertex } j \text{ is \bf{alive}} \\ \text{and } i \text{ is the direct parent of } j \end{array}} hp_j
$$

In addition, Kotori can use some magic spells. If she uses one magic spell, she can kill any monster using $0$ power without any restriction. That is, she can choose a monster even if the monster in the direct parent is alive.

For each $m=0,1,2,\cdots,n$, Kotori would like to know, respectively, the minimum total power needed to kill all the monsters if she can use $m$ magic spells.
## 输入格式

There are multiple test cases. The first line of input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($2 \le n \le 2 \times 10^3$), indicating the number of vertices.

The second line contains $(n-1)$ integers $p_2,p_3,\cdots,p_n$ ($1 \le p_i < i$), where $p_i$ means the direct parent of vertex $i$.

The third line contains $n$ integers $hp_1,hp_2,\cdots,hp_n$ ($1 \le hp_i \le 10^9$) indicating the hit points of each monster.

It's guaranteed that the sum of $n$ of all test cases will not exceed $2 \times 10^3$.
## 输出格式

For each test case output one line containing $(n+1)$ integers $a_0, a_1, \cdots, a_n$ separated by a space, where $a_m$ indicates the minimum total power needed to kill all the monsters if Kotori can use $m$ magic spells.

Please, DO NOT output extra spaces at the end of each line, otherwise your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
3
5
1 2 3 4
1 2 3 4 5
9
1 2 3 4 3 4 6 6
8 4 9 4 4 5 2 4 1
12
1 2 2 4 5 3 4 3 8 10 11
9 1 3 5 10 10 7 3 7 9 4 9
```
### 样例输出 #1
```
29 16 9 4 1 0
74 47 35 25 15 11 7 3 1 0
145 115 93 73 55 42 32 22 14 8 4 1 0
```
## 题目翻译

给定一棵树和点权 $hp_i$，如果需要标记一个点 $i$ 的话，你会付出 $hp_i$ 再加上**所有 $i$ 的直接子节点的权值**的代价，必须先标记 $i$ 的父节点才能标记 $i$（根节点除外）。你可以使用魔法，每使用一次魔法，可以选择一个**未被标记**的点 $x$ 进行无代价标记（即在 $x$ 的父节点未被标记的时候）。求所有点都被标记掉的最少代价。


---

---
title: "[ICPC 2021 Macao R] Laser Trap"
layout: "post"
diff: 提高+/省选-
pid: P9658
tag: ['计算几何', '2021', 'O2优化', '叉积', 'ICPC', '双指针 two-pointer', '澳门']
---
# [ICPC 2021 Macao R] Laser Trap
## 题目描述

BaoBao is playing the famous game $\textit{Elden Ring}$ these days. It's an open-world game in which you can control your character to travel from places to places. However, your character could also enter a trap and you need to figure out how to escape. Right now, BaoBao's character is stuck in a 2-dimensional plane with deadly lasers. There are $n$ laser generators (each can be regarded as a point) shooting laser beams between every pair of them (so there are $\frac{n(n-1)}{2}$ laser beams in total). The beams start and end at generator points and do not stretch to infinity.

Starting at point $(0,0)$, BaoBao wants to escape to point $(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}})$ without touching any laser beam or generator. In order to do so, BaoBao can ask her friend DreamGrid to remove any number of laser generators, together with any laser beam that starts or ends at these generators. Output the minimum number of laser generators that need to be erased for the escape.

Note that BaoBao does not need to move in a specific direction to escape. Her escaping route can even be a curve if necessary.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^6$) indicating the number of laser generators.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$) indicating the location of the $i$-th laser generator.

It is guaranteed that no two generators coincide, and no laser beam or generator will touch $(0,0)$.

It is also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the minimum number of generators that need to be removed.
## 样例

### 样例输入 #1
```
3
2
1 0
2 0
3
1 0
0 1
-1 -1
5
2 -1
1 2
-1 2
-2 -1
0 -2
```
### 样例输出 #1
```
0
1
2
```
## 提示

The second and the third sample test cases are shown below. Solid dots and lines represent the remaining laser generators and beams, while hollow dots and dashed lines represent the removed laser generators and beams. The arrow is the escaping route.

![](https://cdn.luogu.com.cn/upload/image_hosting/b0sz7cm0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dwcsdmj6.png)
## 题目翻译

一直角坐标系中，BaoBao 在原点位置，平面上有 $n$ 个发射装置，任意两个发射器之间都有激光束，共 $(n-1) \times n / 2$ 条激光，BaoBao 的朋友可以去除任何发射器，问最少去除多少发射器，能使 BaoBao不会被激光所伤还能从 $(0,0)$ 逃逸到 $\left(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}}\right)$。

tip.发射器不会重合，也不会存在激光束穿过 $(0,0)$。


---

---
title: "[ICPC 2021 Macao R] Cyclic Buffer"
layout: "post"
diff: 提高+/省选-
pid: P9662
tag: ['动态规划 DP', '2021', 'O2优化', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Cyclic Buffer
## 题目描述

There is a cyclic buffer of size $n$ with readers from the $1$-st position to the $k$-th position (both inclusive). Let $a_i$ ($1 \le i \le n$) be the integer at the $i$-th position of the buffer initially. What's more, $a_1, a_2, \cdots, a_n$ form a permutation of $n$.

We're going to visit all the integers from $1$ to $n$ (both inclusive) in increasing order. An integer can be visited only when it is residing in positions with readers (that is to say, when it is in the first $k$ positions). In case that an integer cannot be visited, we can shift the whole buffer in either directions any number of times.

- If we shift the buffer to the left once, integers in the $i$-th position will be moved to the $(i - 1)$-th position if $i > 1$, and integer in the $1$-st position will be moved to the $n$-th position.
- If we shift the buffer to the right once, integers in the $i$-th position will be moved to the $(i + 1)$-th position if $i < n$, and integer in the $n$-th position will be moved to the $1$-st position.

What's the minimum number of times to shift the buffer so that we can visit all the integers in increasing order?
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $k$ ($1 \le k \le n \le 10^6$) indicating the size of the buffer and the number of readers.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le n$) where $a_i$ indicates the integer in the $i$-th position of the buffer initially.

It's guaranteed that the given $n$ integers form a permutation of $n$. It's also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the minimum number of times to shift the buffer so that all integers can be visited in increasing order.
## 样例

### 样例输入 #1
```
2
5 3
2 4 3 5 1
1 1
1
```
### 样例输出 #1
```
3
0
```
## 提示

For the first sample test case:
- Shift to the right once so the buffer becomes $\{1, 2, 4, 3, 5\}$. $1$ and $2$ can now be visited in order as they are in the first $3$ positions.
- Shift to the left twice so the buffer becomes $\{4, 3, 5, 1, 2\}$. $3$, $4$ and $5$ can now be visited in order as they are in the first $3$ positions.
## 题目翻译

**【题目描述】**

有一个大小为 $n$ 的循环缓冲区，读入流从第 $1$ 个位置到第 $k$ 个位置（两者都包含在内）。设 $a_i$ ($1 \le i \le n$) 是缓冲区初始时第 $i$ 个位置上的整数。此外，$a_1, a_2, \cdots, a_n$ 形成 $n$ 的一个排列。

我们将以递增顺序访问从 $1$ 到 $n$ 的所有整数（两者都包含在内）。只有当整数位于具有读入流的位置（即位于前 $k$ 个位置）时，才能访问整数。如果某个整数无法访问，则可以将整个缓冲区向任意方向移动任意次数。

- 如果我们向左移动缓冲区一次，则位于第 $i$ 个位置的整数将移动到第 $(i - 1)$ 个位置（如果 $i > 1$），并且位于第 $1$ 个位置的整数将移动到第 $n$ 个位置。
- 如果我们向右移动缓冲区一次，则位于第 $i$ 个位置的整数将移动到第 $(i + 1)$ 个位置（如果 $i < n$），并且位于第 $n$ 个位置的整数将移动到第 $1$ 个位置。

我们需要移动缓冲区的最小次数，以便以递增顺序访问所有整数。

**【输入格式】**

每个测试文件中包含多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个整数 $n$ 和 $k$ ($1 \le k \le n \le 10^6$)，表示缓冲区的大小和读入流的数量。

第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le n$)，其中 $a_i$ 表示缓冲区初始时第 $i$ 个位置上的整数。

保证给定的 $n$ 个整数构成 $n$ 的一个排列。还保证所有测试用例中 $n$ 的总和不超过 $10^6$。

**【输出格式】**

对于每个测试用例，输出一行，包含一个整数，表示移动缓冲区的最小次数，以便所有整数可以以递增顺序访问。

**【样例解释】**

对于第一个样例测试用例：
- 向右移动一次，使缓冲区变为 $\{1, 2, 4, 3, 5\}$。现在 $1$ 和 $2$ 可以按顺序访问，因为它们位于前 $3$ 个位置。
- 向左移动两次，使缓冲区变为 $\{4, 3, 5, 1, 2\}$。现在 $3$、$4$ 和 $5$ 可以按顺序访问，因为它们位于前 $3$ 个位置。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[ICPC 2022 Jinan R] Quick Sort"
layout: "post"
diff: 提高+/省选-
pid: P9673
tag: ['2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Quick Sort
## 题目描述

When Prof. Pang was young, he wrote the following code for quick sort. Please calculate how many swaps are performed when calling $\textbf{quicksort}$$(A, 1, n)$. $A$ is a given permutation with length $n$.

![](https://cdn.luogu.com.cn/upload/image_hosting/8ig9i3bq.png)
## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the first line contains one positive integer $n~(1\le n \le 5\times 10^5)$. The next line contains $n$ integers $a_1,\ldots, a_n~(1 \le a_i\le n)$ denoting the permutation $A$. It is guaranteed that $a_1,\ldots, a_n$ form a permutation, i.e.~$a_i\neq a_j$ for $i \neq j$. 

It is guaranteed that the sum of $n$ over all test cases is no more than $5\times 10^5$.
## 输出格式

For each test case, output one line containing the number of swaps performed when calling $\texttt{quicksort}(A, 1, n)$.
## 样例

### 样例输入 #1
```
3
3
3 2 1
5
2 4 5 3 1
10
7 2 4 6 1 9 10 8 5 3
```
### 样例输出 #1
```
1
4
7
```
## 题目翻译

### 题目描述

给定一个长度为 $n$ 的排列 $A$。现使用如下伪代码对 $A$ 进行排序：

```
procedure QUICKSORT(A,lo,hi)
    if lo>=0 and hi>=0 and lo<hi then
    	p=PARTITION(A,lo,hi)
        QUICKSORT(A,lo,p)
        QUICKSORT(A,p+1,hi)
    end if
end procedure
procedure PARTITION(A,lo,hi)
    pivot=A[floor((hi+lo)/2)]
    i=lo-1
    j=hi+1
    while True do
        repeat
            i=i+1
        until A[i]>=pivot
        repeat
            j=j-1
        until A[j]<=pivot
        if i>=j then
            return j
        end if
        Swap A[i] with A[j]
    end while
end procedure
```

试计算：调用 `QUICKSORT(A,1,n)` 函数过程中，`Swap` 操作执行了多少次。

### 输入格式

第一行包含一个整数 $T$ $(1\leqslant T\leqslant 10^5)$，表示测试数据组数。

对于每组测试数据：

第一行包含一个正整数 $n$ $(1\leqslant n\leqslant 5\times 10^5)$。

第二行包含 $n$ 个整数 $a_1,\dots,a_n$ $(1\leqslant a_i\leqslant n)$，表示排列 $A$。保证 $a_1,\dots,a_n$ 构成一个排列，即：$\forall i\not= j,a_i\not=a_j$。

保证所有测试数据中 $n$ 的和不超过 $5\times 10^5$。

### 输出格式

对于每组测试数据，输出一行一个整数，表示调用 `QUICKSORT(A,1,n)` 函数过程中，`Swap` 操作执行的次数。


---

---
title: "[EC Final 2022] Best Carry Player 2"
layout: "post"
diff: 提高+/省选-
pid: P9718
tag: ['2022', 'O2优化', '数位 DP', 'ICPC']
---
# [EC Final 2022] Best Carry Player 2
## 题目描述

Given a positive integer $x$, find the minimum positive integer $y$ such that the number of $\textbf{carries}^1$ of $x+y$ is exactly $k$.

We adds numbers $\textbf{by column addition in base-ten}$, just like what we normally do in primary school. For example, there are two carries in the following addition.

![](https://cdn.luogu.com.cn/upload/image_hosting/pfnper3r.png)

$^1$ which means ``进位`` in Chinese.
## 输入格式

The first line contains an integer $T$ $(1\leq T\leq 10^5)$ $-$ the number of test cases.

For each test case, the first line contains two integers $x, k$ $(1\leq x < 10^{18}, 0\leq k \leq 18)$.
## 输出格式

For each test case, output one integer representing the answer in one line. If there is no solution, output $-1$ instead.
## 样例

### 样例输入 #1
```
4
12345678 0
12345678 5
12345678 18
990099 5
```
### 样例输出 #1
```
1
54322
999999999987654322
9910
```
## 题目翻译

**【题目描述】**

给定一个正整数 $x$，找到最小的正整数 $y$，使得 $x+y$ 的 $\textbf{进位}$ 数量恰好为 $k$。

我们按照十进制中的列加法进行相加，就像我们在小学时所做的那样。例如，下面的加法中有两次进位。

![](https://cdn.luogu.com.cn/upload/image_hosting/pfnper3r.png)

**【输入格式】**

第一行包含一个整数 $T$ $(1\leq T\leq 10^5)$ $-$ 测试用例的数量。

对于每个测试用例，第一行包含两个整数 $x, k$ $(1\leq x < 10^{18}, 0\leq k \leq 18)$。

**【输出格式】**

对于每个测试用例，输出一行一个整数，表示答案。如果没有解决方案，则输出 $-1$。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[EC Final 2022] Inversion"
layout: "post"
diff: 提高+/省选-
pid: P9721
tag: ['2022', '交互题', 'Special Judge', 'O2优化', '排序', 'ICPC']
---
# [EC Final 2022] Inversion
## 题目描述

$\textbf{This is an interactive problem.}$

There is a hidden permutation $p_1, p_2, \dots, p_n$ of $\{1, 2, \dots, n\}$. You want to find it by asking the parity of the number of inversions of $p_l,\ldots, p_r$.

You can query in the format ${?~l~r}$, and the interactor will respond you $\left( \sum_{l\leq i < j\leq r} [p_i > p_j]\right) \bmod 2$. $[p_i>p_j]$ is $1$ when $p_i>p_j$ and $0$ when $p_i\le p_j$.
## 输入格式

Firstly, you should read the integer $n$ ($1\le n\le 2000$).

After that, you can make no more than $4 \times 10^4$ queries. To make a query, output ``${?~l~r}$'' ($1 \leq l \leq r \leq n$) on a separate line, then you should read the response from standard input. 

To give your answer, print ``${!~p_1~p_2~\dots~p_n}$'' on a separate line. The output of the answer is \textbf{not} counted towards the limit of $4 \times 10^4$ queries. 

After that, your program should terminate. 

After printing a query, do not forget to output end of line and flush the output. To do this, use $\texttt{fflush(stdout)}$ or $\texttt{cout.flush()}$ in C++, $\texttt{System.out.flush()}$ in Java, $\texttt{flush(output)}$ in Pascal, or $\texttt{stdout.flush()}$ in Python. 

It is guaranteed that the permutation is fixed in advance. 
## 样例

### 样例输入 #1
```
3

0

0

1

```
### 样例输出 #1
```

? 1 2

? 1 3

? 2 3

! 2 3 1
```
## 题目翻译

**【题目描述】**

这是一个交互式问题。

有一个隐藏的排列 $p_1, p_2, \dots, p_n$，其中包含 $\{1, 2, \dots, n\}$ 的排列。你想通过询问 $p_l,\ldots, p_r$ 的逆序对数量的奇偶性来找到它。

你可以以 ${?~l~r}$ 的格式进行查询，交互器会回答你 $\left( \sum_{l\leq i < j\leq r} [p_i > p_j]\right) \bmod 2$。其中 $[p_i>p_j]$ 在 $p_i>p_j$ 时为 $1$，在 $p_i\le p_j$ 时为 $0$。

首先，你需要读入整数 $n$（$1\le n\le 2000$）。

之后，你可以进行不超过 $4 \times 10^4$ 次查询。要进行查询，输出 ${?~l~r}$（$1 \leq l \leq r \leq n$）在单独的一行上，然后你应该从标准输入中读取响应。

要给出你的答案，将 ${!~p_1~p_2~\dots~p_n}$ 打印在单独的一行上。答案的输出 $\textbf{不}$ 计入 $4 \times 10^4$ 次查询的限制。

之后，你的程序应该终止。

在打印查询后，不要忘记输出换行并刷新输出。要做到这一点，在 C++ 中使用 $\texttt{fflush(stdout)}$ 或 $\texttt{cout.flush()}$，在 Java 中使用 $\texttt{System.out.flush()}$，在 Pascal 中使用 $\texttt{flush(output)}$，或者在 Python 中使用 $\texttt{stdout.flush()}$。

保证排列提前固定。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[EC Final 2022] Chinese Checker"
layout: "post"
diff: 提高+/省选-
pid: P9723
tag: ['2022', 'O2优化', '广度优先搜索 BFS', 'ICPC']
---
# [EC Final 2022] Chinese Checker
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/krp4wk8f.png)

Prof. Pang is playing Chinese Checkers. The game board is the same as the figure shown above. There are $n$ checkers on the board. Prof. Pang wants to know how many different moves there are on the current board.

One **move** consists of several **steps**. At first, Prof. Pang needs to choose one checker $a$ to move. In each step, Prof. Pang needs to choose another checker $b$ as the pivot, and move the checker $a$ to the symmetrical position about the checker $b$. (In one move, Prof. Pang cannot change his choice of $a$ between steps. **If after a step, the checker $a$ will return to its position before the move, this step is not allowed.**) There are several conditions about the pivot $b$:

- The segment connecting $a$ and $b$ needs to be parallel to one of the coordinate axis. Note: There are three axes on the hexagonal board. One of them is horizontal and any pair of axes intersect at an angle of $\pi/3$.
- $a$ and $b$ **do not** need to be adjacent.
- There cannot be extra checkers other than $b$ on the segment connecting $a$ and its symmetrical position.
- The symmetrical position should be on the hexagonal board and is not occupied by any other checker.

A move must have at least one step. After the first step, Prof. Pang can stop at any time he wants. And Prof. Pang can choose any checker on the board as the moving checker. Output the number of different moves Prof. Pang can make. Two moves are different if and only if the sets of positions of all checkers are different after these two moves, i.e., the checkers are indistinguishable. 
## 输入格式

The first line contains an integer $T~(1\leq T\leq 100)$ -- the number of test cases.

For each test case, the first line contains an integer $n~(1\leq n\leq 121)$ -- the number of checkers.

Each of the following $n$ lines contains two integers, indicating the position of a checker. The first number indicates which row it is in, and the second number indicates which one of this row it is. They are counting from top to bottom and left to right, starting from $1$.

It is guaranteed that checkers' positions are different.
## 输出格式

For each test case, output one integer in a line -- the number of different moves.
## 样例

### 样例输入 #1
```
5
1
1 1
2
1 1
2 1
2
9 4
9 6
10
1 1
2 1
2 2
3 1
3 2
3 3
4 1
4 2
4 3
4 4
10
1 1
2 1
2 2
5 7
3 2
3 3
4 1
4 2
4 3
4 4

```
### 样例输出 #1
```
0
1
2
6
13

```
## 题目翻译

棋盘上有 $n$ 个棋子，你需要求对于当前局面，下一次移动有多少种不同的走法。

一次移动由若干步组成。假设当前要移动的棋子为 $a$，在每一步中，首先需要选择另一个棋子 $b$ 作为跳台，然后将 $a$ 走到关于 $b$ 的对称位置（在一次移动中，你无法更改需要移动的棋子 $a$。并且在某一步中，棋子 $a$ 回到此次移动前所在的位置是不被允许的）。

关于跳台 $b$ 的选择有一些条件：

- $a$ 和 $b$ 之间的连线应当平行于棋盘的某条坐标轴。注：棋盘上一共有三条坐标轴，其中一条与水平线平行，并且任意两条坐标轴之间的夹角均为 $\frac{\pi}{3}$。

- $a$ 和 $b$ 不必相邻。

- 除了跳台 $b$ 以外，$a$ 和其关于 $b$ 的对称点的连线上不能有其他棋子。

- 对称点的位置应当落在棋盘上，并且没有被其他棋子占据。

一次移动需要至少走一步。在第一步以后，你可以随时停下来。你可以选择棋盘上任意一个棋子作为移动棋子。请输出有多少种不同的走法。

两种走法不同当且仅当两次移动后所有棋子的位置组成的集合不同，并且棋子之间不可区分。

### 输入格式
第一行一个整数 $T$，表示数据组数。

对于每组数据，第一行一个整数 $n$，表示棋子数量。

接下来 $n$ 行，每行两个整数，表示棋子位置。第一个整数表示棋子所在行，第二个整数表示棋子所在列（棋子在这一行的第几个位置上，注意每一行的起始位置和列数有可能是不一样的）。行列的编号从 $1$ 开始，分别从上到下，从左到右递增。

保证每个棋子的位置互不相同。

### 输出格式
输出 $T$ 行，每行一个整数，表示不同走法的数量。


---

---
title: "[EC Final 2022] Chase Game"
layout: "post"
diff: 提高+/省选-
pid: P9724
tag: ['2022', 'O2优化', '最短路', 'ICPC']
---
# [EC Final 2022] Chase Game
## 题目描述

Prof. Shou is being chased by Prof. Pang on an undirected unweighted simple graph. Initially, Prof. Shou is at vertex $1$. His destination is vertex $n$. Prof. Pang is at vertex $k$.

In each second, Prof. Shou may choose an adjacent vertex and walk to that vertex. Then Prof. Shou is attacked by Prof. Pang. The damage of this attack is equal to $d-dis$ where $d$ is Prof. Pang's attack range and $dis$ is the distance (number of edges in the shortest path) between Prof. Shou and Prof. Pang on the graph. However, when $dis$ is greater than or equal to $d$, Prof. Pang cannot deal any positive damage. In this case, instead of attacking with non-positive damage, he will teleport to the vertex where Prof. Shou is and then deal $d$ damage. (When $dis$ is less than $d$, Prof. Pang will stay at his current vertex.)

Please find the minimum sum of damage Prof. Shou will take to reach vertex $n$ from vertex $1$. Prof. Shou will take the last attack at vertex $n$.
## 输入格式

The first line contains $4$ integers $n, m, k, d$ ($2\le n\le 10^5, n-1\le m\le 2\times 10^5, 1\le k\le n, 1\le d\le 2\times 10^5$).

Each of the next $m$ lines contains two integers $a, b$ ($1\le a, b\le n, a \ne b$) representing an edge of the graph. The edges are distinct. ($a\ b$ and $b\ a$ represents the same edge. Thus, only one of these two lines may appear in the input.)

It is guaranteed that the graph is connected.
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
5 5 3 1
1 2
2 4
4 5
1 3
3 5

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
13 17 12 3
1 2
2 3
3 4
4 13
5 13
7 8
7 9
7 10
7 11
7 6
12 7
1 8
8 9
9 10
10 11
11 6
6 13

```
### 样例输出 #2
```
7

```
## 题目翻译

**【题目描述】**

Shou 教授被 Pang 教授在一个无向无权简单图上追赶。最初，Shou 教授在顶点 $1$。他的目的地是顶点 $n$。Pang 教授在顶点 $k$。

每秒钟，Shou 教授可以选择一个相邻的顶点并走向该顶点。然后，Shou 教授会受到 Pang 教授的攻击。此次攻击的伤害等于 $d-dis$，其中 $d$ 是 Pang 教授的攻击范围，$dis$ 是图上从 Shou 教授到 Pang 教授的距离（最短路径上的边数）。然而，当 $dis$ 大于或等于 $d$ 时，Pang 教授无法造成任何正伤害。在这种情况下，他将不会使用非正的伤害攻击，而是会传送到 Shou 教授所在的顶点，然后造成 $d$ 伤害。（当 $dis$ 小于 $d$ 时，Pang 教授将停留在当前顶点。）

请找出 Shou 教授从顶点 $1$ 到顶点 $n$ 所需的最小伤害总和。Shou 教授将在顶点 $n$ 处受到最后一次攻击。

**【输入格式】**

第一行包含 $4$ 个整数 $n, m, k, d$ ($2\le n\le 10^5, n-1\le m\le 2\times 10^5, 1\le k\le n, 1\le d\le 2\times 10^5$)。

接下来的 $m$ 行中，每行包含两个整数 $a, b$ ($1\le a, b\le n, a \ne b$)，表示图的一条边。边是不同的。($a\ b$ 和 $b\ a$ 表示相同的边。因此，在输入中只会出现这两行中的一行。)

保证图是连通的。

**【输出格式】**

输出一行整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[NERC 2018] Cactus Search"
layout: "post"
diff: 提高+/省选-
pid: P9793
tag: ['2018', '交互题', 'Special Judge', 'ICPC']
---
# [NERC 2018] Cactus Search
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) C 题。

如果你想让数组问题更难解决，可以在树上解决；如果你想让树的问题更难解决，可以在仙人掌上解决。
## 题目描述

在前几年，就有过人提出了许多关于仙人掌——连通无向图的问题，其中每条边最多属于一个简单的循环。更加直观地说，仙人掌是一棵树的概括，在这棵树上允许有一些环。下面的图片给出了仙人掌的一个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/a44vr6aa.png)

你和 Chloe 在一个仙人掌上玩游戏，你有一株仙人掌，但是淘气的 Chloe 偷偷拿走了一个顶点 $v$，你需要在 $10$ 次以内猜出 $v$，如果你猜到了 $v$，那你就赢了，如果你猜测的是另一个点 $u$，Chloe 会告诉你一个点 $w$，其中 $w$ 到 $v$ 经过的边数严格小于 $u$ 到 $v$。
## 输入格式

首先，第一行给你两个整数 $n$ 和 $m$，其中 $n$ 表示一共有 $n$ 个顶点，图的边由一组边不同的路径表示，$m$ 表示它们的数量。

接下来一行，$m$ 个整数 $k_i$，表示该条路径经过了 $k_i$ 个顶点，然后接下来 $k_i$ 个整数，表示一次经过的路径（不会重复经过点）。输入中的图形是一个仙人掌。每次猜测，程序会返回你一些返回值，如果是 `FOUND`，说明你猜对了，否则是 `GO w`，表示 $w$ 到 $v$ 经过的边数严格小于你猜测的点到 $v$ 的边数。你的程序每次询问要猜测不超过 $10$ 次，如果你猜测的次数 $> 10$ 次，那么你就不通过该测试点。

此外为了避免你是蒙对的，需要进行 $n$ 次询问，每次猜测成功后，你直接进行下一轮询问，询问 $n$ 次完直接退出。
## 输出格式

每次询问，你需要向**标准输出**输出一个整数 $u$，代表你猜测的结果，**然后清空缓冲区**。

你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。
## 样例

### 样例输入 #1
```
5 2
5 1 2 3 4 5
2 1 3

FOUND
GO 4
FOUND
GO 2
FOUND
GO 1
FOUND
GO 4
GO 5
FOUND
```
### 样例输出 #1
```




3
3
4
3
2
3
1
3
4
5
```
## 提示

数据保证 $1 \leq n \leq 500$，$0 \leq m \leq 500$，$1 \leq k_i \leq 500$。

注：为了方便比对，在样例输入输出上加入了一些空行进行对齐，实际输入输出中没有这些空行。


---

---
title: "[NERC 2018] Fractions"
layout: "post"
diff: 提高+/省选-
pid: P9796
tag: ['2018', 'Special Judge', 'ICPC']
---
# [NERC 2018] Fractions
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) F 题。
## 题目描述

给你一个整数 $n$，你需要构造出若干个形如 $\dfrac{a_i}{b_i}$ 的真分数，使得 $\sum^k_{i=1} \frac{a_i}{b_i} = 1 - \frac{1}{n}$，且 $b_i$ 可以整除 $n$。
## 输入格式

一个正整数 $n (2 \leq n \leq 10^9)$。
## 输出格式

如果不能构造，输出一行 `NO`。

否则的话就构造出其中一种的合法方案，输出 `YES`，然后让 $\sum^k_{i=1} \frac{a_i}{b_i} = 1 - \frac{1}{n}$，按第二行第一个整数 $k$，接下来 $k$ 行一行两个整数 $a_i$ 和 $b_i(b_i \neq n)$。

注意你输出的 $k$ 的范围是 $2 \leq k \leq 10^5$。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
NO
```
### 样例输入 #2
```
6
```
### 样例输出 #2
```
YES
2
1 2
1 3
```
## 提示

对于所有的数据，保证 $1 \leq n \leq 10^9$。

对于第一个样例，不存在一种方案使得答案总和为 $\frac{1}{2}$。

对于第二个样例，$\frac{1}{2} + \frac{1}{3} = \frac{5}{6}$。


---

---
title: "[NERC 2018] Minegraphed"
layout: "post"
diff: 提高+/省选-
pid: P9803
tag: ['2018', 'Special Judge', 'ICPC']
---
# [NERC 2018] Minegraphed
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) M 题。
## 题目描述

Marika 正在制作一款名为 Minegraphed 的游戏，游戏内容是你在一个三维的矩形立方体上移动。平行六面体游戏场地的每个单元格都是空单元格或障碍单元格。你总是在一个空建筑里面，要么在最底层，要么在一个障碍的顶部。对于每次移动，你可以选择东南西北中的一项进行移动，移动的规则如下：

- 你不能移动至矩形立方体外面。

- 如果你面前的单元格是空的，那么你可以向前移动一格，然后向底部落下，直到你到达最底层或者一个障碍。

- 如果你在非最顶层，你前面的单元格是一个障碍物，你上面的单元格和上面的单元格都是空的，然后你可以爬到该障碍物的顶部。

- 其余情况，你不能进行移动。

Marika 还有一个 $n \times n$ 的二维数组 $a$，你需要满足当 $a_{i,j} = 1$ 时，$i$ 能到达 $j$。

请构造一种合法方案。
## 输入格式

第一行一个整数 $n \ (1 \leq n \leq 9)$。

然后 $n$ 行，每行 $n$ 个数分别为 $a_{i,1},a_{1,2},\ldots,a_{i,n}$，$a_{i,j}$ 的含义见题目描述。
## 输出格式

输出第一行 $x,y,z$ 表示你的矩形立方体的长宽高，你需要保证 $x \times y \times z \leq 10^6$。

然后 $z$ 层（自上向下），每层一个 $x \times y$ 的矩形，如果 $map_{i,j}$ 为 `#`，表示它是障碍，如果为 `.`，表示是通路。否则若为数字，表示对应到 $n$ 的 $map_{i,j}$ 的数字。

保证存在解法。
## 样例

### 样例输入 #1
```
4
0 1 0 1
0 0 1 0
0 1 0 0
1 0 0 0
```
### 样例输出 #1
```
4 2 3
..#.
.4..
####
1#.#
..3.
#2..

```
## 提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/w4266sez.png)

对于所有数据保证 $1 \leq n \leq 9$，$a_{i,j} \in \{0, 1\}$。


---

---
title: "[ICPC 2020 Shanghai R] Sum of Log"
layout: "post"
diff: 提高+/省选-
pid: P9821
tag: ['2020', '上海', 'O2优化', '数位 DP', 'ICPC']
---
# [ICPC 2020 Shanghai R] Sum of Log
## 题目描述

Given two non-negative integers $X$ and $Y$, determine the value of 
$$ \sum_{i=0}^{X}\sum_{j=[i=0]}^{Y}[i\&j=0]\lfloor\log_2(i+j)+1\rfloor $$
modulo $10^9+7$ where
- $\&$ denotes bitwise AND;
- $[A]$ equals 1 if $A$ is true, otherwise $0$;
- $\lfloor x\rfloor$ equals the maximum integer whose value is no more than $x$.
## 输入格式

The first line contains one integer $T\,(1\le T \le 10^5)$ denoting the number of test cases.

Each of the following $T$ lines contains two integers $X, Y\,(0\le X,Y \le 10^9)$ indicating a test case.
## 输出格式

For each test case, print one line containing one integer, the answer to the test case.
## 样例

### 样例输入 #1
```
3
3 3
19 26
8 17
```
### 样例输出 #1
```
14
814
278
```
## 提示

For the first test case:
- Two $(i,j)$ pairs increase the sum by 1: $(0, 1), (1, 0)$
- Six $(i,j)$ pairs increase the sum by 2: $(0, 2), (0, 3), (1, 2), (2, 0), (2, 1), (3, 0)$

So the answer is $1\times 2 + 2\times 6 = 14$.
## 题目翻译

给定两个非负整数 $X,Y$，计算下列式子对 $10^9+7$ 取模的值：
$$
\sum\limits_{i=0}^{X}{\sum\limits_{j=[i=0]}^{Y}{[i \& j=0]\lfloor \log_2(i+j)+1\rfloor}}
$$
其中：

- $\&$ 表示按位与。
- $[A]$ 等于 $1$，当且仅当表达式 $A$ 为真；否则 $[A]$ 等于 $0$。
- $\lfloor x \rfloor$ 表示不大于 $x$ 的最大整数。


---

---
title: "[ICPC 2020 Shanghai R] The Journey of Geor Autumn"
layout: "post"
diff: 提高+/省选-
pid: P9823
tag: ['动态规划 DP', '2020', '上海', 'O2优化', '组合数学', '逆元', 'ICPC']
---
# [ICPC 2020 Shanghai R] The Journey of Geor Autumn
## 题目描述

Once upon a time, there was a witch named Geor Autumn, who set off on a journey across the world. Along the way, she would meet all kinds of people, from a country full of ICPC competitors to a horse in love with dota---but with each meeting, Geor would become a small part of their story, and her own world would get a little bit bigger.

Geor just arrived at the state of Shu where people love poems. A poem is a permutation $(a_1,\ldots, a_n)$ of $[n]$. ($(a_1,\ldots, a_n)$ is a permutation of $[n]$ means that each $a_i$ is an integer in $[1,n]$ and that $a_1,\ldots, a_n$ are distinct.) One poem is $\textit{good}$ if for all integer $i$ satisfying $i> k$ and $i\le n$, $a_i>\min(a_{i-k}, \ldots, a_{i-1})$. Here $\min(a_{i-k}, \ldots, a_{i-1})$ denotes the minimum value among $a_{i-k}, \ldots, a_{i-1}$.

Help Geor calculate how many good poems there are, given $n$ and $k$. To avoid huge numbers, output the answer modulo $998244353$.
## 输入格式

The first line contains two integers $n$ and $k$ separated by a single space ($1\le n\le 10^7$, $1\le k\le 10^7$).
## 输出格式

Output only one integer in one line---the number of good poems modulo $998244353$.
## 样例

### 样例输入 #1
```
1 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
2 3
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
3 2
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
4 2
```
### 样例输出 #4
```
10
```
## 题目翻译

### 题意简述
给定 $1 \le k \le n$，我们规定满足以下性质的 $1 \sim n$ 的排列称之为“好排列”：

$\forall k<i \le n,~a_i > \min{a_{i-k},a_{i-k+1},...,a_{i-1}}$

求好排列的个数。对 $998244353$ 取模。
### 输入格式
一行，两个整数 $n,k$。
### 输出格式
一行，为好排列的个数对 $998244353$ 取模的值。


---

---
title: "[ICPC 2020 Shanghai R] Rice Arrangement"
layout: "post"
diff: 提高+/省选-
pid: P9826
tag: ['数学', '贪心', '2020', '上海', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Rice Arrangement
## 题目描述

Wowo is a hospitable Xinjiang uncle. $k$ guests will have Uyghur Polo (a traditional Uyghur food) in Wowo's house around a big round table. $n$ ($n\ge k$) chairs are placed around the table uniformly. Each guest sits on a chair and no two guests sit on the same chair. $k$ bowls of Uyghur Polo are on the table. Each bowl is next to some chair ($\textbf{with or without}$ some guest sitting on it). No two bowls locate at the same position.

![](https://cdn.luogu.com.cn/upload/image_hosting/q3gqhsvq.png)

As a waiter, you are supposed to assign each person with exactly one bowl of Uyghur Polo. The table can be rotated, so each time you can turn it $\frac{2\pi}{n}$ degrees clockwise or counterclockwise. The bowls turn with the table while the chairs and guests do not move. When one bowl of Uyghur Polo is in front of a guest, he can either take it or wait for another.

You want to minimize the total times of table rotating so that everybody can have meals as quickly as possible.

(Formal definition: The boundary of the table is a circle. $n$ chairs are at $n$ points on the circle whose convex hull is a regular polygon with $n$ vertices. We name the points $0,\ldots, n-1$ in counterclockwise order. The $i$-th bowl is at point $b_i$ ($0\le b_i<n$) initially. The $i$-th guest is at point $a_i$ ($0\le a_i < n$) initially. If you turn the table counterclockwise, the bowl at point $b_i$ ($1\le i\le k$) will be moved to point $(b_i+ 1) \bmod n$ after the rotation. If you turn the table clockwise, the bowl at point $b_i$ ($1\le i\le k$) will be moved to point $(b_i-1) \bmod n$ after the rotation. ($x\bmod n$ is defined as the smallest nonnegative integer $r$ such that $x-r$ is a multiple of $n$.))

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n,k$ ($1\le n \le 10^9,1 \le k \le \min(n,1000)$) indicating the size of the table and the number of persons and bowls of Uyghur Polo. 

In the second line, there are $k$ integers $a_1,a_2,\dots,a_k$ ($0 \le a_i < n$), indicating the positions of the persons. No two guests share the same position.

In the third line, there are $k$ integers $b_1,b_2,\dots,b_k$ ($0 \le b_i < n$), indicating the initial positions of the bowls. No two bowls of Uyghur Polo locate at the same position.

It is guaranteed that the sum of $k$ over all test cases does not exceed $5000$.
## 输出格式

For each test case, output the minimal total times of rotations such that each guest can have exactly one bowl of Uyghur Polo.
## 样例

### 样例输入 #1
```
1
4 2
0 3
1 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
1
14 5
0 12 13 8 9
9 2 6 13 5
```
### 样例输出 #2
```
6
```
## 题目翻译

Wowo 是一名好客的新疆大叔。$k$ 名客人将在 Wowo 的房子里，围在圆桌旁享用新疆抓饭。$n(n \ge k)$ 把椅子已经被均匀的放置在桌子周围，每个客人坐在一把椅子上，没有两名客人坐在同一把椅子上。$k$ 份新疆抓饭已经放在了桌子上，每份抓饭都放在了一把椅子面前（可能没有客人坐在这把椅子上），没有两份抓饭放在同一个位置上。

作为服务员，你需要为每一名客人指定正好一碗抓饭。桌子可以旋转，每次你可以顺时针或逆时针旋转桌子 $\dfrac{2\pi}{n}$ 度。碗随着桌子旋转，但客人和椅子不会随之移动。当一碗饭转到某个客人面前时，他可以选择拿走这碗饭，或等待另一碗。

你想要最小化旋转桌子的次数，使得每个人可以最快得到饭。


---

---
title: "[ICPC 2020 Shanghai R] Traveling in the Grid World"
layout: "post"
diff: 提高+/省选-
pid: P9830
tag: ['数学', '贪心', '2020', '上海', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Traveling in the Grid World
## 题目描述

Consider a grid pattern with $n$ rows and $m$ columns. There are $(n+1)\times(m+1)$ grid points in total which is the intersections of $n+1$ horizontal lines and $m+1$ vertical lines. We number the horizontal lines from $0$ to $n$ from top to bottom. We number the vertical lines from $0$ to $m$ from left to right. The intersection of horizontal line $i$ and vertical line $j$ is named $(i, j)$ ($0\le i\le n, 0\le j\le m$).

There are some constraints when you travel in the grid world. When you are located at point $(x,y)$, you can choose a destination $(x',y')$ and walk to it along the line segment between $(x, y)$ and $(x', y')$. We call this operation a $\textit{walk}$. A walk is forbidden if there exists another grid point different from $(x, y)$ and $(x', y')$ lying on the line segment between them. You can walk as many times as you want but the directions of two consecutive walks cannot be the same. (Specifically, if you walk from $(x_0, y_0)$ to $(x_1, y_1)$ and then walk from $(x_1, y_1)$ to $(x_2, y_2)$, you must make sure that $(x_0-x_1)(y_1-y_2)\neq (x_1-x_2)(y_0-y_1)$.) The length of a walk from $(x, y)$ to $(x', y')$ is defined as the Euclidean distance between the two endpoints, $\sqrt{(x-x')^2+(y'-y)^2}$.

Starting from $(0,0)$, you are planning to arrive at $(n,m)$ by several walks. Because of the annoying rules, you may need some turning points to achieve your goal. Please find the minimum total length of your walks.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n,m$ ($1\le n,m \le 10^6$) indicating the size of the grid graph.

It is guaranteed that the sum of the values of $\max(n,m)$ over all test cases does not exceed $10^6$.
## 输出格式

For each test case, output the minimum total length of walks. Your answer will be considered correct if its absolute or relative error does not exceed $10 ^{-9}$.
## 样例

### 样例输入 #1
```
2
2 2
2 3
```
### 样例输出 #1
```
3.236067977499790
3.605551275463989
```
## 题目翻译

### 题目描述

考虑具有 $n$ 行和 $m$ 列的网格模式。总共有$（n+1）\times（m+1）$网格点，即$n+1$水平线和$m+1$垂直线的交点。我们将水平线从上到下从 $0$ 到 $n$ 编号。我们将垂直线从左到右编号从 $0$ 到 $m$。水平线 $i$ 和垂直线 $j$ 的交点命名为 $(i,j)$($0 \le i \le n， 0 \le j \le m$)。

当您在网格世界中旅行时，会有一些限制。当您位于点 $(x,y)$ 时，您可以选择一个目的地 $(x',y')$ 并沿着 $(x,y)$ 和 $(x',y')$ 之间的线段步行到该目的地。我们将此操作称为 $\textit{walk}$。如果它们之间的线段上存在另一个不同于 $(x,y)$ 和 $(x', y')$ 的网格点，则禁止行走。您可以随心所欲地走很多次，但连续两次步行的方向不能相同。（具体来说，如果从 $(x_0,y_0)$ 到 $(x_1, y_1)$，然后从 $(x_1, y_1)$ 到 $（x_2， y_2）$，则必须确保 $(x_0-x_1)(y_1-y_2) \neq (x_1-x_2)(y_0-y_1)$。从 $(x,y)$ 到 $(x',y')$ 的步行长度定义为两个端点之间的欧几里得距离 $\sqrt{(x-x')^2+(y'-y)^2}$。

从 $(0,0)$ 开始，您计划通过几次步行到达 $(n，m)$。由于烦人的规则，您可能需要一些转折点来实现您的目标。请找到您步行的最小总长度。

### 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例，
第一行包含两个整数 $n,m$ （$1 \le n,m \le 10^6$），表示网格图的大小。

保证所有测试用例中 $\max(n,m)$ 的值之和不超过 $10^6$。


---

---
title: "[ICPC 2021 Nanjing R] Paimon Segment Tree"
layout: "post"
diff: 提高+/省选-
pid: P9844
tag: ['线段树', '2021', 'Special Judge', 'O2优化', '矩阵乘法', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon Segment Tree
## 题目描述

Paimon just learns the persistent segment tree and decides to practice immediately. Therefore, Lumine gives her an easy problem to start:

Given a sequence $a_1, a_2, \cdots, a_n$ of length $n$, Lumine will apply $m$ modifications to the sequence. In the $i$-th modification, indicated by three integers $l_i$, $r_i$ ($1 \le l_i \le r_i \le n$) and $x_i$, Lumine will change $a_k$ to $(a_k + x_i)$ for all $l_i \le k \le r_i$.

Let $a_{i, t}$ be the value of $a_i$ just after the $t$-th operation. This way we can keep track of all historial versions of $a_i$. Note that $a_{i,t}$ might be the same as $a_{i,t-1}$ if it hasn't been modified in the $t$-th modification. For completeness we also define $a_{i, 0}$ as the initial value of $a_i$.

After all modifications have been applied, Lumine will give Paimon $q$ queries about the sum of squares among the historical values. The $k$-th query is indicated by four integers $l_k$, $r_k$, $x_k$ and $y_k$ and requires Paimon to calculate

$$\sum\limits_{i=l_k}^{r_k}\sum\limits_{j=x_k}^{y_k} a_{i, j}^2$$

Please help Paimon compute the result for all queries. As the answer might be very large, please output the answer modulo $10^9 + 7$.
## 输入格式

There is only one test case in each test file.

The first line of the input contains three integers $n$, $m$ and $q$ ($1 \le n, m, q \le 5 \times 10^4$) indicating the length of the sequence, the number of modifications and the number of queries.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($|a_i| < 10^9 + 7$) indicating the initial sequence.

For the following $m$ lines, the $i$-th line contains three integers $l_i$, $r_i$ and $x_i$ ($1 \le l_i \le r_i \le n$, $|x_i| < 10^9 + 7$) indicating the $i$-th modification.

For the following $q$ lines, the $i$-th line contains four integers $l_i$, $r_i$, $x_i$ and $y_i$ ($1 \le l_i \le r_i \le n$, $0 \le x_i \le y_i \le m$) indicating the $i$-th query.
## 输出格式

For each query output one line containing one integer indicating the answer modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
3 1 1
8 1 6
2 3 2
2 2 0 0

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
4 3 3
2 3 2 2
1 1 6
1 3 3
1 3 6
2 2 2 3
1 4 1 3
4 4 2 3

```
### 样例输出 #2
```
180
825
8

```
## 题目翻译

## 题目描述

派蒙刚刚学习了可持久化线段树，她想马上练习一下。因此，荧决定给她出一道简单的问题：

给定数列$a_1, a_2, \cdots, a_n$，并进行$m$次操作。操作包含3个参数$l_i$, $r_i$ ($1 \le l_i \le r_i \le n$) 和 $x_i$，代表对该序列第$l_i$到第$r_i$个元素加上$x_i$。

记$a_{i, t}$为$t$次操作后$a_i$的值。注意若$a_i$未被修改，则$a_{i,t}$的值与$a_{i,t-1}$相同。定义$a_{i, 0}$是$a_i$的初始值。


完成所有操作后，荧进行$q$次询问，询问包含4个整数$l_k$, $r_k$, $x_k$ and $y_k$，派蒙需要回答

$$\sum\limits_{i=l_k}^{r_k}\sum\limits_{j=x_k}^{y_k} a_{i, j}^2$$

请将答案对$10^9 + 7$取模后输出。

## 输入格式
每个测试点含一组测试数据。

第一行3个整数$n$,$m$,$q$ ($1 \le n, m, q \le 5 \times 10^4$) 分别表示数列的长度，操作的次数和询问的次数。

第2行$n$个整数 $a_1, a_2, \cdots, a_n$ ($|a_i| < 10^9 + 7$) ，表示原始数列。

接下来$m$行每行3个整数 $l_i$, $r_i$ $x_i$ ($1 \le l_i \le r_i \le n$, $|x_i| < 10^9 + 7$)，表示区间加操作。

接下来$q$行每行包含四个整数 $l_i$, $r_i$, $x_i$  $y_i$ ($1 \le l_i \le r_i \le n$, $0 \le x_i \le y_i \le m$)，表示询问。

## 输出格式

对每个询问单起一行输出答案模$10^9 + 7$的结果。


---

---
title: "[ICPC 2021 Nanjing R] Crystalfly"
layout: "post"
diff: 提高+/省选-
pid: P9847
tag: ['动态规划 DP', '2021', 'Special Judge', 'O2优化', '树形 DP', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Crystalfly
## 题目描述

Paimon is catching crystalflies on a tree, which are a special kind of butterflies in Teyvat. A tree is a connected graph consisting of $n$ vertices and $(n - 1)$ undirected edges. 

![](https://cdn.luogu.com.cn/upload/image_hosting/awi9prsr.png)

There are initially $a_i$ crystalflies on the $i$-th vertex. When Paimon reaches a vertex, she can catch all the remaining crystalflies on the vertex immediately. However, the crystalflies are timid. When Paimon reaches a vertex, all the crystalflies on the adjacent vertices will be disturbed. For the $i$-th vertex, if the crystalflies on the vertex are disturbed for the first time at the beginning of the $t'$-th second, they will disappear at the end of the $(t' + t_{i})$-th second.

At the beginning of the $0$-th second, Paimon reaches vertex $1$ and stays there before the beginning of the $1$-st second. Then at the beginning of each following second, she can choose one of the two operations:
- Move to one of the adjacent vertices of her current vertex and stay there before the beginning of the next second (if the crystalflies in the destination will disappear at the end of that second she can still catch them).
- Stay still in her current vertex before the beginning of the next second.

Calculate the maximum number of crystalflies Paimon can catch in $10^{10^{10^{10^{10}}}}$ seconds.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$) indicating the number of vertices.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le 10^9$) where $a_i$ is the number of crystalflies on the $i$-th vertex.

The third line contains $n$ integers $t_1, t_2, \cdots, t_n$ ($1 \le t_i \le 3$) where $t_i$ is the time before the crystalflies on the $i$-th vertex disappear after disturbed.

For the next $(n - 1)$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating an edge connecting vertices $u_i$ and $v_i$ in the tree.

It's guaranteed that the sum of $n$ of all the test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the maximum number of crystalflies Paimon can catch.
## 样例

### 样例输入 #1
```
2
5
1 10 100 1000 10000
1 2 1 1 1
1 2
1 3
2 4
2 5
5
1 10 100 1000 10000
1 3 1 1 1
1 2
1 3
2 4
2 5

```
### 样例输出 #1
```
10101
10111

```
## 提示

For the first sample test case, follow the strategy below.
- During the $0$-th second
  - Paimon arrives at vertex $1$;
  - Paimon catches $1$ crystalfly;
  - Crystalflies in vertices $2$ and $3$ are disturbed.
- During the $1$-st second
  - Paimon arrives at vertex $3$;
  - Paimon catches $100$ crystalflies.
- During the $2$-nd second
  - Paimon arrives at vertex $1$;
  - Crystalflies in vertex $2$ disappears.
- During the $3$-rd second
  - Paimon arrives at vertex $2$;
  - Crystalflies in vertices $4$ and $5$ are disturbed.
- During the $4$-th second
  - Paimon arrives at vertex $5$;
  - Paimon catches $10000$ crystalflies;
  - Crystalflies in vertex $4$ disappears.

For the second sample test case, the optimal strategy is the same with the first sample test case. Crystalflies in vertex $2$ are scheduled to disappear at the end of the $3$-rd (instead of the $2$-nd) second, allowing Paimon to catch them.
## 题目翻译

给定一个 $n(1\le n\le10^5)$ 个节点的树，每个节点上有 $a_i$ 只晶蝶。派蒙最初在 $1$ 号节点，并获得 $1$ 号节点的所有晶蝶，接下来每一秒她可以移动到相邻的节点上并获得节点上的所有晶蝶，但是当她每到达一个节点 $u$ 后，对于每个与 $u$ 相邻的节点 $v$，节点 $v$ 上的的晶蝶会在 $t_v(1\le t_v\le3)$ 秒内消失，在 $t_v$ 秒后再到达节点 $v$ 将无法获得节点上的晶蝶。现在需要你求出最多可以获得的晶蝶数。


---

---
title: "[ICPC 2021 Nanjing R] Cloud Retainer's Game"
layout: "post"
diff: 提高+/省选-
pid: P9848
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Cloud Retainer's Game
## 题目描述

Cloud Retainer, the builder of the Dwelling in the clouds above Qingyun Peak, is very interested in mechanics. Although there is more than one month away from the Lantern Rite Festival in Liyue, she has already started the design of a gaming event for it.

![](https://cdn.luogu.com.cn/upload/image_hosting/ye0zfdit.png)

The game is mainly about releasing pinballs to get a score as high as possible. It is played on the 2-dimensional plane with two horizontal straight lines $y = 0$ and $y = H$. Between the two lines, there are $n$ tiny wooden boards and $m$ coins, both can be regarded as single points. The $i$-th wooden board is located at $(x_i, y_i)$ while the $i$-th coin is located at $(x'_i, y'_i)$.

A pinball is released from $(10^{-9}, 10^{-9})$ by the player. Let $\overrightarrow{v} = (v_x, v_y)$ be the velocity of the ball (that is to say, if the ball is currently located at $(x, y)$ it will move to $(x + v_x\epsilon, y + v_y\epsilon)$ after $\epsilon$ seconds). Initially $\overrightarrow{v} = (1, 1)$.

When the ball hits a wooden board or one of the two horizontal straight lines, $v_y$ will be negated (that is, $v_y$ becomes $-v_y$) while $v_x$ remains unchanged. If the ball hits a coin, the player's score is increased by $1$ and the velocity of the ball remains unchanged.

To gain a higher score, the player can choose to remove any number of wooden boards before the pinball is released. It is also OK not to remove any wooden board. Cloud Retainer wants you to help her estimate the difficulty by computing the maximum score the player can get after $10^{10^{10^{10^{10}}}}$ seconds under the best strategy?
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $H$ ($2 \le H \le 10^9$).

The second line contains one integer $n$ ($1 \le n \le 10^5$) indicating the number of wooden boards.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($1 \le x_i \le 10^9$, $1 \le y_i < H$) indicating a wooden board located at $(x_i, y_i)$.

The following line contains one integer $m$ ($1 \le m \le 10^5$) indicating the number of coins.

For the following $m$ lines, the $i$-th line contains two integers $x'_i$ and $y'_i$ ($1 \le x'_i \le 10^9$, $1 \le y'_i < H$) indicating a coin located at $(x'_i, y'_i)$.

It's guaranteed that the given $(n + m)$ points in the same test case will be distinct. It's also guaranteed that neither the sum of $n$ nor the sum of $m$ of all test cases will exceed $5 \times 10^5$.
## 输出格式

For each test case output one line containing one integer indicating the maximum score the player can get after removing some (or not removing any) wooden boards.
## 样例

### 样例输入 #1
```
2
4
3
1 1
2 2
6 2
4
3 1
3 3
5 1
7 3
3
1
4 2
3
1 1
6 2
9 1

```
### 样例输出 #1
```
3
3

```
## 提示

The two sample test cases are shown below. Solid diamonds represent the remaining wooden boards, while hollow diamonds represent the removed wooden boards and round dots represent the coins.

![](https://cdn.luogu.com.cn/upload/image_hosting/st3aejoc.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/oojtcbv6.png)
## 题目翻译

参考题中所给图片，有上下两根直线，之间的距离为 $H$，还有 $n$ 个镜子，可以反射光线，也可以让其穿过，有 $m$ 个物品，一开始有一束从原点出发四十五度向右上方射出的一条光线，请你控制每个镜子的开关，求这条光线最多能经过几个物品。

——By @紊莫


---

---
title: "[ICPC 2021 Nanjing R] Xingqiu's Joke"
layout: "post"
diff: 提高+/省选-
pid: P9849
tag: ['数学', '递推', '2021', 'Special Judge', 'O2优化', '最大公约数 gcd', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Xingqiu's Joke
## 题目描述

Once again, Xingqiu hides Chongyun's ice cream into a box with a strange lock. Liyue's summer has been always very hot and Chongyun suffers more because of his excessive yang (positive) energy, so he needs that ice cream desperately.

![](https://cdn.luogu.com.cn/upload/image_hosting/2dtcr426.png)

There are two integers $a$ and $b$ on the lock. Chongyun can perform the following three types of operations any number of times:
- Minus $1$ from both $a$ and $b$;
- Plus $1$ to both $a$ and $b$;
- Divide both $a$ and $b$ by one of their common $\textbf{prime}$ factor (that is to say, divide them by a $\textbf{prime}$ $g$ where $a$ and $b$ are both divisible by $g$).

The box will be unlocked if either $a$ or $b$ or both become $1$. To help Chongyun gets the ice cream back as quickly as possible, please tell him the minimum number of operations needed to unlock the box.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 300$) indicating the number of test cases. For each test case:

The first and only line contains two integers $a$ and $b$ ($1 \le a, b \le 10^9$, $a \ne b$).
## 输出格式

For each test case output one line containing one integer indicating the minimum number of operations to make $a$ or $b$ or both equal $1$.
## 样例

### 样例输入 #1
```
5
4 7
9 8
32 84
11 35
2 1

```
### 样例输出 #1
```
2
7
5
4
0

```
## 提示

For the first sample test case, the optimal way is $(4, 7) \rightarrow (3, 6) \rightarrow (1, 2)$.

For the second sample test case, the optimal way is to apply the first type of operation $7$ times.

For the third sample test case, the optimal way is $(32, 84) \rightarrow (16, 42) \rightarrow (15, 41) \rightarrow (14, 40) \rightarrow (13, 39) \rightarrow (1, 3)$.

For the fourth sample test case, the optimal way is $(11, 35) \rightarrow (12, 36) \rightarrow (6, 18) \rightarrow (2, 6) \rightarrow (1, 3)$.
## 题目翻译

## 题目描述
有 $T$ 个盒子，每盒子上有一个锁，锁上有两个整数 $a$ 和 $b$。你可以对这个锁做若干次以下 3 种操作：

- $a$ 和 $b$ 分别减去 $1$
- $a$ 和 $b$ 分别增加 $1$
- $a$ 和 $b$ 分别除以它们共同的素数因子

如果 $a$ 或 $b$ 或两者都变为 $1$，盒子就会解锁。请你编写一个程序，计算每个盒子的锁打开的最少步骤数量。

## 输入格式
第一行输入一个整数 $T(1≤T≤300)$。

接下来 $T$ 行，每行输入 $a$ 和 $b$，表示每个盒子的锁的信息。

## 输出格式  

共输出 $T$ 行，每行输出对应盒子解锁的最少步骤。


---

---
title: "[EC Final 2021] Beautiful String"
layout: "post"
diff: 提高+/省选-
pid: P9873
tag: ['字符串', '2021', 'O2优化', 'ICPC']
---
# [EC Final 2021] Beautiful String
## 题目描述

Prof. Pang recently got a dictionary of the elvish language, including many strings representing their words. He thinks a partition of string $s$ is beautiful if both of the following conditions are satisfied:

- $s = s_1 + s_2 + s_3 + s_4 + s_5 + s_6$, where $s_i (1\leq i\leq 6)$ are nonempty substrings. $a + b$ means the concatenation of string $a$ and $b$ here.
- $s_1 = s_2 = s_5, s_3 = s_6$.


For example, you can partition the string ``114514`` into $6$ parts : ``114514`` = ``1`` + ``1`` + ``4`` + ``5`` + ``1`` + ``4``. The first, second, fifth parts are the same, and the third and sixth parts are the same. Thus, the partition of $s=$``114514`` into $s_1=$``1``, $s_2=$``1``, $s_3=$``4``, $s_4=$``5``, $s_5=$``1``, and $s_6=$``4`` is beautiful. 

Accordingly, the beauty of a string $s$ is defined as the number of beautiful partitions of $s$.

Given a string $t$, please help Prof. Pang to figure out the sum of beauties of all substrings of $t$.

## 输入格式

The first line contains a single integer $T~(1\leq T \le 50)$ indicating the number of test cases. 

For each test case, there is one single line containing the string $t$, consisting of digits from `0' to `9'.

It is guaranteed that the length of each $t$ in each test case will not exceed $5000$ and the total length will not exceed $30000$.
## 输出格式

For each test case, output a single line containing an integer, indicating the sum of beauties of all substrings of $t$.
## 样例

### 样例输入 #1
```
2
114514
0000000
```
### 样例输出 #1
```
1
3
```
## 题目翻译

当字符串 $s$ 的一个**划分**满足如下条件：

- $s = s_1 + s_2 + s_3 + s_4 + s_5 + s_6$，其中 $s_i (1\leq i\leq 6)$ 为非空子串，$a + b$ 表示将字符串 $b$ 接于 $a$ 后。

- $s_1 = s_2 = s_5, s_3 = s_6$。

则称该**划分**是**美丽的**。

字符串 $s$ 的**美丽值**定义为 $s$ 的不同的**美丽的划分**的个数。

给出字符串 $s$，求其**所有子串**的**美丽值之和**。


---

---
title: "[EC Final 2021] Prof. Pang and Poker"
layout: "post"
diff: 提高+/省选-
pid: P9876
tag: ['2021', 'O2优化', 'ICPC', '分类讨论']
---
# [EC Final 2021] Prof. Pang and Poker
## 题目描述

Prof. Pang is playing a card game with his two friends Alice and Bob. All cards are drawn from a standard 52-card deck. A standard 52-card deck comprises $13$ ranks in each of the four French suits: clubs ($\clubsuit$), diamonds ($\diamondsuit$), hearts ($\heartsuit$) and spades ($\spadesuit$). Each suit includes an Ace (A), a King (K), a Queen (Q), and a Jack (J), each depicted alongside a symbol of its suit; and numerals or pip cards from the Deuce (Two) to the Ten, with each card depicting that many symbols (pips) of its suit. $\textbf{No card can be drawn more than once.}$

![](https://cdn.luogu.com.cn/upload/image_hosting/3xtu6g4z.png)

Individual cards are ranked as follows (high-to-low): A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2. $\textbf{Suits do not affect ranks of the cards.}$ For example, Ace of diamonds and Ace of clubs have the same rank. No one of them is ranked strictly higher than the other.

Initially, Alice and Bob will hold one or more cards while Prof. Pang will hold exactly one card. $\textbf{Each player can see cards held by himself/herself and cards held by other players.}$ They will play the game in the following multi-round rule:

- The initiative player chooses one card and put it out to start one round.
- The next player can pass or put out a new card, then the player after the next can also pass or put out a new card, and so on. The only constraint is that the rank of the newly put card should be strictly higher than all previous cards in this round.
- The round ends when two players choose to pass consecutively. The one who put out the last card becomes the initiative player in the next round.
- If someone put out all the cards in his/her hand, the game ends immediately.

In this game, Alice is the initiative player in the first round. Bob, Prof. Pang,  and Alice are the next players of Alice, Bob,  and Prof. Pang respectively. Prof. Pang will be happy if and only if he is the one that first put out all the cards. (Prof. Pang wants to be happy, of course.) Alice wants to drink milk tea so she decides to make Prof. Pang happy and then asks him to buy milk tea for her. However, Bob doesn't want it to happen, so he decides to avoid Prof. Pang from being happy. If they play the game optimally for themselves, will Prof. Pang be happy in the end?
## 输入格式

The first line contains a single integer $T$ ($1\le T \le 10^4$) denoting the number of test cases. For each test case:

The first line contains two integers $n,m$ ($1\le n,m \le 50$) denoting the number of cards in Alice's hand and Bob's hand initially.

The second line contains $n$ strings $a_i$ ($1\le i \le n$) denoting the cards in Alice's hand.

The third line contains $m$ strings $b_i$ ($1\le i \le m$) denoting the cards in Bod's hand.

The fourth line contains one string $p$ denoting the card in Prof. Pang's hand.

For each card, the first character of its corresponding string denotes its rank. (Possible ranks are `2` ,`3`,`4`,`5`,`6`,`7`,`8`,`9`,`T`,`J`,`Q`,`K`,`A`. `T` denotes $10$.) The second character denotes its suit. `C` denotes clubs. `D` denotes diamonds. `H` denotes hearts. `S` denotes spades.

It is guaranteed that each card appears at most once in one test case.
## 输出格式

For each test case, print one line. Print $\texttt{Pang}$ if Prof. Pang will be happy. Otherwise, print $\texttt{Shou}$.
## 样例

### 样例输入 #1
```
2
2 2
2H 2D
3H 3D
4S
2 2
2H 2D
3H 4D
4S
```
### 样例输出 #1
```
Pang
Shou
```
## 提示

- For the first case, Prof. Pang can always put out his only card ``4S``.
- For the second case, Bob can put out ``4D`` and become the initiative player in the second round regardless of the card Alice put out in the first round, then Bob put out ``3H`` and the game ends.
## 题目翻译

舒克、贝塔、卢本伟在打抽象版斗地主。

+ 因为卢本伟不想再被飞机炸弹秒掉，所以所有人**只能出单牌**，牌的大小依次为（从小到大列举）：$2,3,4,5,6,7,8,9,\texttt{T},\texttt{J},\texttt{Q},\texttt{K},\texttt{A}$。
+ 因为舒克是色盲，所以牌的**花色无关紧要**（即：两牌数字相同时没有大小之分）。
+ 因为贝塔技不如人，所以所有人**明牌打**。
+ 其余和普通斗地主一样：
    + 主动方选一张牌，打出去开始新一轮比赛。
    + 下一个玩家可以出牌或跳过，出牌需满足牌值**严格大于**上一张牌。
    + 当两名玩家连续跳过后，另一名玩家开始一个新的回合，这另一名玩家成为了主动方。
    + 谁把牌打光谁就赢了。
   
现在，给你一个残局，舒克剩 $n$ 张牌，贝塔剩 $m$ 张牌，斗地主大师卢本伟只剩一张牌了。

现在是新一个回合，顺序是舒克、贝塔、卢本伟。舒克想让卢本伟赢，贝塔想让卢本伟输。

作为著名动画片的主角与斗地主慈善家，三人都绝顶聪明。问最后谁会赢，卢本伟赢输出 `Pang`，否则输出 `Shou`。注意**舒克赢不算卢本伟赢**。

translated by 卢本伟。


---

---
title: "[EC Final 2021] Elden Ring"
layout: "post"
diff: 提高+/省选-
pid: P9881
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Elden Ring
## 题目描述

Prof. Pang is getting addicted to the game called Elden Ring, in which the world is a connected graph including $n$ vertices indexed from $1$ to $n$ and $m$ undirected edges. Players start at vertex $1$ and travel across the world to slay the god on vertex $n$.

However, it's not that easy. For any vertex $i$ except vertex $1$, there is exactly one boss whose level is $l_i$, and the player starts the game with level $l_1$. For each day, the player can travel to any vertex $i$ from vertex $1$ and challenge the boss there. If the current level of the player is greater than the boss, the boss will be eliminated from the world (inactivated) and the level of the player will be increased by $A$. Notice that traveling through a vertex that has an active boss is forbidden. (In other words, Prof. Pang can travel from vertex $1$ to vertex $i$ if there is a path in the graph from vertex $1$ to vertex $i$ such that each vertex on this path, except for vertex $i$, has no active boss.) Meanwhile, at the beginning of each day, all the remaining bosses in the world will also be promoted by $B$ levels.

To finish a playthrough of the game, you need to slay the boss on vertex $n$ (Elden Beast). Given the information of the world, Prof. Pang is wondering how many days he needs at least to do so. 

The Player can only challenge one boss each day.
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^5)$ denoting the number of test cases. 

For each test case, the first line includes four integers $n, m, A, B~(2\leq n\leq 2\times 10^5, 1 \le m, A, B\le 2\times 10^5)$. In next $m$ lines, each line contains two integers $a_i, b_i~(1 \le a_i, b_i \le n)$, denoting the endpoints of the $i$-th undirected edge. The last line contains $n$ integers $l_i~(1 \le l_i \le 2 \times 10^5)$, representing the initial levels of the player and bosses mentioned above.

It is guaranteed that the sum of $n$ over all test cases will not exceed $10^6$ and the sum of $m$ over all test cases will not exceed $10^6$.
## 输出格式

For each test case, output a single line containing an integer, indicating the minimum number of days Prof. Pang needs to finish the game. If it is impossible to do so, please output $-1$.
## 样例

### 样例输入 #1
```
2
5 4 5 8
1 2
1 3
1 4
4 5
15 1 1 1 1
5 4 10 5
1 2
1 3
1 4
4 5
10 4 4 4 19

```
### 样例输出 #1
```
2
4

```
## 题目翻译

有一个 $n$ 个节点 $m$ 条边的无向图，每个节点 $i$ 上有一个初始等级为 $l_i$ 的 boss。玩家开始时位于 1 号节点，初始等级为 $l_1$。（保证 1 号节点没有 boss）

每天开始后，玩家从 1 号节点开始，经过**没有 boss** 的节点到达一个有 boss 的节点 $i$，并击杀节点 $i$ 的 boss。玩家等级必须大于 boss 的等级才能将 boss 击杀，且每天只能击杀一个 boss。

每击杀一个 boss，玩家的等级会增加 $A$。每天开始时，所有**仍存在**的 boss 等级增加 $B$。输出至少需要多少天才能击杀节点 $n$ 的 boss 并通关，如果不能通关输出  -1 。


---

---
title: "[ICPC 2018 Qingdao R] Tournament"
layout: "post"
diff: 提高+/省选-
pid: P9890
tag: ['2018', 'O2优化', '构造', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Tournament
## 题目描述

DreamGrid, the king of Gridland, is making a knight tournament. There are $n$ knights, numbered from 1 to $n$, participating in the tournament. The rules of the tournament are listed as follows:

- The tournament consists of $k$ rounds. Each round consists of several duels. Each duel happens between exactly two knights.
- Each knight must participate in exactly one duel during each round.
- For each pair of knights, there can be at most one duel between them during all the $k$ rounds.
- Let $1 \le i, j \le k$, $i \ne j$, and $1 \le a, b, c, d \le n$, $a, b, c, d$ be four distinct integers. If
    - Knight $a$ fights against knight $b$ during round $i$, and
    - Knight $c$ fights against knight $d$ during round $i$, and
    - Knight $a$ fights against knight $c$ during round $j$,
- then knight $b$ must fight against knight $d$ during round $j$.

As DreamGrid's general, you are asked to write a program to arrange all the duels in all the $k$ rounds, so that the resulting arrangement satisfies the rules above. 
## 输入格式

There are multiple test cases. The first line of the input is an integer $T$, indicating the number of test cases. For each test case:

The first and only line contains two integers $n$ and $k$ ($1 \le n, k \le 1000$), indicating the number of knights participating in the tournament and the number of rounds.

It's guaranteed that neither the sum of $n$ nor the sum of $k$ in all test cases will exceed $5000$.
## 输出格式

For each test case:

- If it's possible to make a valid arrangement, output $k$ lines. On the $i$-th line, output $n$ integers $c_{i, 1}, c_{i, 2}, \dots, c_{i, n}$ separated by one space, indicating that in the $i$-th round, knight $j$ will fight against knight $c_{i, j}$ for all $1 \le j \le n$.   
If there are multiple valid answers, output the lexicographically smallest answer.   
Consider two answers $A$ and $B$, let's denote $a_{i, j}$ as the $j$-th integer on the $i$-th line in answer $A$, and $b_{i, j}$ as the $j$-th integer on the $i$-th line in answer $B$. Answer $A$ is lexicographically smaller than answer $B$, if there exists two integers $p$ ($1 \le p \le k$) and $q$ ($1 \le q \le n$), such that
    - for all $1 \le i < p$ and $1 \le j \le n$, $a_{i, j} = b_{i, j}$, and
    - for all $1 \le j < q$, $a_{p, j} = b_{p, j}$, and finally $a_{p, q} < b_{p, q}$.
-If it's impossible to make a valid arrangement, output ``Impossible`` (without quotes) in one line.

Please, DO NOT output extra spaces at the end of each line, or your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
2
3 1
4 3
```
### 样例输出 #1
```
Impossible
2 1 4 3
3 4 1 2
4 3 2 1
```
## 题目翻译

$n$ 个骑士要进行 $m$ 轮对决，每一轮每个骑士都要有一个对手。而且每个对手只能打一次。假设 $a$ 与 $b$ 打了，$c$ 与 $d$ 打了，那么后面的任意一轮如果 $a$ 与 $c$ 打了，那么 $b$ 就必须和 $d$ 打，问是否存在方案，存在就输出字典序最小的一组，否则输出 ```Impossible```。


---

