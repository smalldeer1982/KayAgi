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
title: "[GCJ 2021 Qualification] Median Sort"
layout: "post"
diff: 提高+/省选-
pid: P13024
tag: ['2021', '三分', '交互题', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2021 Qualification] Median Sort
## 题目描述

You want to sort $\mathbf{N}$ distinct items, $x_1$, $x_2$, $\ldots$, $x_{\mathbf{N}}$. Unfortunately, you do not have a way of comparing two of these items. You only have a way to, given three of them, find out which one is the median, that is, which one is neither the minimum nor the maximum among the three.

For example, suppose $\mathbf{N} = 5$ and you know that:

* $x_1$ is the median of $\{x_1, x_2, x_3\}$
* $x_2$ is the median of $\{x_2, x_3, x_4\}$
* $x_3$ is the median of $\{x_3, x_4, x_5\}$

Then, it is guaranteed that the sorted order of the elements is either $x_4, x_2, x_1, x_3, x_5$ or its reverse $x_5, x_3, x_1, x_2, x_4$. Notice that by knowing only medians, it is impossible to distinguish the order of any list from its reverse, since the median question has the same result for any three elements in both cases.

Your program will have to find the order of $\mathbf{T}$ lists of $\mathbf{N}$ elements using at most $\mathbf{Q}$ median questions in total (or $\mathbf{Q}/\mathbf{T}$ queries per list on average). In each case, finding either the right order or its reverse is considered correct. The order for each case is generated uniformly at random from all possible orders, and independently of any other information.

### Interactive Protocol

This is an interactive problem.

Initially, the judge will send you a single line containing three integers $\mathbf{T}$, $\mathbf{N}$, and $\mathbf{Q}$: the number of test cases, the number of elements to sort within each test case, and the total number of questions you are allowed across all test cases, respectively. Then, you must process $\mathbf{T}$ test cases. Each test case consists of a series of question exchanges plus an additional exchange to provide the answer.

For a question exchange, your program must print a single line containing three distinct integers $i$, $j$, $k$ all between 1 and $\mathbf{N}$, inclusive, which corresponds to asking the judge "which element is the median of the set $\{x_i, x_j, x_k\}$?" The judge will respond with a single line containing a single integer $\mathbf{L}$, meaning that the median of that set is $x_{\mathbf{L}}$ ($\mathbf{L}$ is always equal to one of $i$, $j$, or $k$). If you try to perform a $(\mathbf{Q} + 1)$-th question exchange, the judge will simply output -1.

Once you are ready to state the result, print a line containing $\mathbf{N}$ integers representing the indices of the elements in sorted or reverse sorted order. The judge will respond with a single integer 1 if your answer is correct or -1 if it is not. After receiving the judge's answer for the $\mathbf{T}$-th case, your program must finish in time in order to not receive a Time Limit Exceeded error. In addition, if you print additional information after receiving the result for the $\mathbf{T}$-th case, you will get a Wrong Answer judgment.

If the judge receives an invalidly formatted line or invalid values from your program at any moment, the judge will print a single number -1. After the judge prints -1 for any of the reasons explained above, it will not print any further output. If your program continues to wait for the judge after receiving a -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2 5 600

2

3

4

1

3

4

5

1
```
### 样例输出 #1
```

1 2 3

4 2 3

5 4 3

5 4 3 2 1

1 2 3

2 3 4

3 4 5

1 3 5 4 2
```
## 提示

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our interactive runner for that. For more information, read the instructions in comments in that file, and also check out the Interactive Problems section of the FAQ.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $\mathbf{T} = 100$.

**Test Set 1 (7 Pts, Visible Verdict)**

- $\mathbf{N} = 10$.
- $\mathbf{Q} = 300 \cdot \mathbf{T}$.

**Test Set 2 (11 Pts, Visible Verdict)**

- $\mathbf{N} = 50$.
- $\mathbf{Q} = 300 \cdot \mathbf{T}$.

**Test Set 3 (10 Pts, Hidden Verdict)**

- $\mathbf{N} = 50$.
- $\mathbf{Q} = 170 \cdot \mathbf{T}$.


---

---
title: "[六省联考 2017] 期末考试"
layout: "post"
diff: 提高+/省选-
pid: P3745
tag: ['数学', '贪心', '2017', '各省省选', '三分', '枚举', '前缀和']
---
# [六省联考 2017] 期末考试
## 题目描述

有 $n$ 位同学，每位同学都参加了全部的 $m$ 门课程的期末考试，都在焦急的等待成绩的公布。

第 $i$ 位同学希望在第 $t_i$ 天或之前得知**所有**课程的成绩。如果在第 $t_i$ 天，有至少一门课程的成绩没有公布，他就会等待最后公布成绩的课程公布成绩，每等待一天就会产生 $C$ 不愉快度。

对于第 $i$ 门课程，按照原本的计划，会在第 $b_i$ 天公布成绩。

有如下两种操作可以调整公布成绩的时间:
1. 将负责课程 $X$ 的部分老师调整到课程 $Y$，调整之后公布课程 $X$ 成绩的时间推迟一天，公布课程 $Y$ 成绩的时间提前一天；每次操作产生 $A$ 不愉快度。
2. 增加一部分老师负责学科 $Z$，这将导致学科 $Z$ 的出成绩时间提前一天；每次操作产生 $B$ 不愉快度。

上面两种操作中的参数 $X, Y, Z$ 均可任意指定，每种操作均可以执行多次，每次执行时都可以重新指定参数。

现在希望你通过合理的操作，使得最后总的不愉快度之和最小，输出最小的不愉快度之和即可。
## 输入格式

第一行三个非负整数 $A, B, C$，描述三种不愉快度，详见【题目描述】；  
第二行两个正整数 $n, m$，分别表示学生的数量和课程的数量；  
第三行 $n$ 个正整数 $t_i$，表示每个学生希望的公布成绩的时间；  
第四行 $m$ 个正整数 $b_i$，表示按照原本的计划，每门课程公布成绩的时间。
## 输出格式

输出一行一个整数，表示最小的不愉快度之和。
## 样例

### 样例输入 #1
```
100 100 2
4 5
5 1 2 3
1 1 2 3 3
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 5 4
5 6
1 1 4 7 8
2 3 3 1 8 2
```
### 样例输出 #2
```
33
```
## 提示

### 样例解释 1

由于调整操作产生的不愉快度太大，所以在本例中最好的方案是不进行调整；全部的 $5$ 门课程中，最慢的在第 $3$ 天出成绩；  
同学 $1$ 希望在第 $5$ 天或之前出成绩，所以不会产生不愉快度；  
同学 $2$ 希望在第 $1$ 天或之前出成绩，产生的不愉快度为 $(3 - 1) \times 2 = 4$；  
同学 $3$ 希望在第 $2$ 天或之前出成绩，产生的不愉快度为 $(3 - 2) \times 2 = 2$；  
同学 $4$ 希望在第 $3$ 天或之前出成绩，所以不会产生不愉快度；  
不愉快度之和为 $4 + 2 = 6$。

### 数据范围

| Case # | $n, m, t_i, b_i$ | $A, B, C$ |
|:-:|:-:|:-:|
| 1, 2 | $1 \leq n, m, t_i, b_i \leq 2000$ | $A = 10^9; B = 10^9; 0 \leq C \leq 10^2$ |
| 3, 4 | $1 \leq n, m, t_i, b_i \leq 2000$ | $0 \leq A; C \leq 10^2; B = 10^9$ |
| 5, 6, 7, 8 | $1 \leq n, m, t_i, b_i \leq 2000$ | $0 \leq B \leq A \leq 10^2; 0 \leq C \leq 10^2$ |
| 9 - 12 | $1 \leq n, m, t_i, b_i \leq 2000$ | $0 \leq A, B, C \leq 10^2$ |
| 13, 14 | $1 \leq n, m, t_i, b_i \leq 10^5$ | $0 \leq A, B \leq 10^5; C = 10^{16}$ |
| 15 - 20 | $1 \leq n, m, t_i, b_i \leq 10^5$ | $0 \leq A, B, C \leq 10^5$ |


---

