---
title: "[蓝桥杯 2025 国 A] 斐波那契数列"
layout: "post"
diff: 提高+/省选-
pid: P12847
tag: ['2025', '矩阵加速', '线性代数', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 A] 斐波那契数列
## 题目描述

斐波那契数列是一个满足如下要求的数列

$$\begin{cases} F_1 = 1 \\ F_2 = 1 \\ F_i = F_{i-1} + F_{i-2} \ (i > 2) \end{cases}$$

我们规定一个类似的数列满足

$$\begin{cases} G_1 = 2 \\ G_2 = 3 \\ G_i = G_{i-1} \times G_{i-2} \ (i > 2) \end{cases}$$

求该数列 $G$ 的前 $n$ 项的乘积对 $998244353$ 取模的结果。
## 输入格式

输入一行包含一个正整数 $n$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
69984
```
## 提示

**【评测用例规模与约定】**

对于 70% 的评测用例，$n \leq 10^6$；

对于所有评测用例，$1 \leq n \leq 10^{18}$。


---

---
title: "[GCJ 2008 EMEA SemiFinal] Scaled Triangle"
layout: "post"
diff: 提高+/省选-
pid: P13482
tag: ['数学', '2008', 'Special Judge', '线性代数', 'Google Code Jam']
---
# [GCJ 2008 EMEA SemiFinal] Scaled Triangle
## 题目描述

You are given two triangle-shaped pictures. The second picture is a possibly translated, rotated and scaled version of the first. The two triangles are placed on the table, with the second one placed completely inside (possibly touching the boundary of) the first one. The second triangle is always scaled by a factor that is strictly between 0 and 1.

You need to process the picture, and for that you need a point in the picture which overlaps with the same point of the scaled picture. If there is more than one solution, you can return any of them. If there are no solutions, print "No Solution" (without the quotes) for that test case.
## 输入格式

The first line of input gives the number of cases, $N$. Then for each test case, there will be two lines, each containing six space-separated integers -- the coordinates of one of the triangles -- in the format "$x_1$ $y_1$ $x_2$ $y_2$ $x_3$ $y_3$". The point $(x_1, y_1)$ in the first triangle corresponds to the same corner of the picture as $(x_1, y_1)$ in the second triangle, and similarly for $(x_2, y_2)$ and $(x_3, y_3)$.

## 输出格式

For each test case, output one line containing "Case #$x$: " followed two real numbers representing the coordinates of the overlapping point separated by one space character, or the string "No Solution". Answers with a relative or absolute error of at most $10^{-5}$ will be considered correct.
## 样例

### 样例输入 #1
```
2
0 0 0 2 2 0
0 0 0 1 1 0
10 0 0 10 0 0
3 3 1 1 3 1
```
### 样例输出 #1
```
Case #1: 0.000000 0.000000
Case #2: 2.692308 1.538462
```
## 提示

**Limits**

- $1 \leqslant N \leqslant 10$.
- The coordinates of the points will be integer numbers between $-10\, 000$ and $10\, 000$. The three points in each triangle will not be collinear.

**Small dataset (Test set 1 - Visible)**

- All tests will contain isosceles right-angle triangles. (i.e., the triangle's angles will be 45 degrees, 45 degrees, and 90 degrees.)

**Large dataset (Test set 2 - Hidden)**

- The triangles can have any shape.



---

---
title: "【模板】高斯消元法"
layout: "post"
diff: 提高+/省选-
pid: P3389
tag: ['Special Judge', '线性代数', '高斯消元']
---
# 【模板】高斯消元法
## 题目背景

如果想要更好地测试高斯消元算法模板请在通过此题后尝试通过 [SDOI2006 线性方程组](https://www.luogu.com.cn/problem/P2455) 这一题。
## 题目描述

给定一个线性方程组，对其求解。

$$ \begin{cases} a_{1, 1} x_1 + a_{1, 2} x_2 + \cdots + a_{1, n} x_n = b_1 \\ a_{2, 1} x_1 + a_{2, 2} x_2 + \cdots + a_{2, n} x_n = b_2 \\ \cdots \\ a_{n,1} x_1 + a_{n, 2} x_2 + \cdots + a_{n, n} x_n = b_n \end{cases}$$

## 输入格式

第一行，一个正整数 $n$。

第二至 $n+1$ 行，每行 $n+1$ 个整数，为 $ a_1, a_2, \dots ,a_n$ 和 $b$，代表一组方程。

## 输出格式

共 $n$ 行，每行一个数，第 $i$ 行为 $x_i$（四舍五入保留 $2$ 位小数）。

如果不存在唯一解或无解，在第一行输出 `No Solution`.

## 样例

### 样例输入 #1
```
3
1 3 4 5
1 4 7 3
9 3 2 2
```
### 样例输出 #1
```
-0.97
5.18
-2.39
```
## 提示

本题 special judge 用于处理可能由于浮点数问题输出 `-0.00` 的情况。若某个 $x_i$ 的解四舍五入后是 `0.00`，那么你的程序输出 `-0.00` 和输出 `0.00` 都是正确的。

数据范围：$1 \leq n \leq 100, \left | a_i \right| \leq {10}^4 , \left |b \right| \leq {10}^4 $。保证数据若有解则所有解均满足 $|x_i|\le 10^3$，且 $x_i\pm 10^{-6}$ 和 $x_i$ 四舍五入后的结果相同（即不会因为较小的精度误差导致四舍五入后的结果不同）。


---

---
title: "小猴打架"
layout: "post"
diff: 提高+/省选-
pid: P4430
tag: ['数学', '生成树', '线性代数']
---
# 小猴打架
## 题目描述

一开始森林里面有 $N$ 只互不相识的小猴子，它们经常打架，但打架的双方都必须不是好朋友。每次打完架后，打架的双方以及它们的好朋友就会互相认识，成为好朋友。经过 $N-1$ 次打架之后，整个森林的小猴都会成为好朋友。   
现在的问题是，总共有多少种不同的打架过程。   
比如当 $N=3$ 时，就有 $\{1-2,1-3\}\{1-2,2-3\}\{1-3,1-2\}\{1-3,2-3\}\{2-3,1-2\}\{2-3,1-3\}$ 六种不同的打架过程。 

## 输入格式

一个整数 $N$。 
## 输出格式

一行，方案数 $\bmod 9999991$。 
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
96
```
## 提示

$50\%$ 的数据 $N\le 10^3$。  
$100\%$ 的数据 $N\le10^6$。 


---

---
title: "【模板】行列式求值"
layout: "post"
diff: 提高+/省选-
pid: P7112
tag: ['数学', 'O2优化', '线性代数']
---
# 【模板】行列式求值
## 题目背景

模板题，无背景。

数据于 2020/12/5 更新，新增两组数据分别叉掉 [mrsrz](https://www.luogu.com.cn/user/6813) 和 [gxy001](https://www.luogu.com.cn/user/55707) 的提交。

数据于 2021/3/12 更新，新增数据叉掉 [wangrx](https://www.luogu.com.cn/user/104726) 的提交。
## 题目描述

给定一个 $n$ 阶行列式 $A$，求 $|A|$。结果对 $p$ 取模。
## 输入格式

第一行两个正整数 $n$ 和 $p$。

接下来共 $n$ 行，第 $i+1$ 行 $n$ 个正整数，其中第 $j$ 个表示 $A_{i,j}$。
## 输出格式

输出 $|A|$ 在模 $p$ 意义下的最小自然数值。
## 样例

### 样例输入 #1
```
2 998244353
1 4
1 5
```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 600$，$1\le a_{i,j}< 10^9+7$，$1\le p\le 10^9+7$。

存在部分测试点满足 $p$ 为素数、$\mu{(p)}\ne 0$ ，可以用于测试其他算法。~~对 CRT 能不能通过该测试点表示怀疑~~。

如果有错误做法过了可以私聊我，视情况更新数据。


---

