---
title: "[GESP202503 五级] 原根判断"
layout: "post"
diff: 提高+/省选-
pid: P11961
tag: ['2025', '原根', '数论', 'GESP', '欧拉函数']
---
# [GESP202503 五级] 原根判断
## 题目背景

截止 2025 年 3 月，本题可能超出了 GESP 考纲范围。在该时间点下，原根是 NOI 大纲 8 级知识点（NOI 级），而相对简单的无需原根知识的做法中，使用的费马小定理与欧拉定理也属于 NOI 大纲 7 级知识点（提高级），且均未写明于 GESP 大纲中。需要注意，GESP 大纲和 NOI 大纲是不同的大纲。

若对题目中原根这一概念感兴趣，可以学习完成 [【模板】原根](https://www.luogu.com.cn/problem/P6091)。
## 题目描述

小 A 知道，对于质数 $p$ 而言，$p$ 的原根 $g$ 是满足以下条件的正整数：

+ $1<g<p$；
+ $g^{p-1}\bmod{p}=1$；
+ 对于任意 $1\le i<p-1$ 均有 $g^i\bmod{p}\neq1$。

其中 $a\bmod{p}$ 表示 $a$ 除以 $p$ 的余数。

小 A 现在有一个整数 $a$，请你帮他判断 $a$ 是不是 $p$ 的原根。
## 输入格式

第一行，一个正整数 $T$，表示测试数据组数。

每组测试数据包含一行，两个正整数 $a,p$。
## 输出格式

对于每组测试数据，输出一行，如果 $a$ 是 $p$ 的原根则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
3
3 998244353
5 998244353
7 998244353
```
### 样例输出 #1
```
Yes
Yes
No
```
## 提示

#### 数据范围

对于 $40\%$ 的测试点，保证 $3\le p\le10^3$。

对于所有测试点，保证 $1\le T\le20$，$3\le p\le10^9$，$1<a<p$，$p$ 为质数。


---

---
title: "[蓝桥杯 2024 国 Python B] 全 X 数"
layout: "post"
diff: 提高+/省选-
pid: P12272
tag: ['2024', '数论', '蓝桥杯国赛', '欧拉函数']
---
# [蓝桥杯 2024 国 Python B] 全 X 数
## 题目描述

我们称 $22222, 3333, 7777$ 等由单一数字组成的十进制数为全 $X$ 数。

给定一个整数 $n$，小蓝想知道 $n$ 的所有倍数中最小的全 $X$ 数是多少。由于答案可能很大，你只需要输出答案对 $998244353$ 取模的结果。如果不存在任何答案，请输出 $-1$。
## 输入格式

输入一行包含一个整数 $n$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
12 
```
### 样例输出 #1
```
444
```
## 提示

### 评测用例规模与约定

- 对于 $50\%$ 的评测用例，$n \leq 5000$；
- 对于 $75\%$ 的评测用例，$n \leq 10^6$；
- 对于所有评测用例，$1 \leq n \leq 10^9$。


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
title: "疯狂 LCM"
layout: "post"
diff: 提高+/省选-
pid: P1891
tag: ['数学', '欧拉函数']
---
# 疯狂 LCM
## 题目背景

众所周知，czmppppp 是数学大神犇。一天，他给众蒟蒻们出了一道数论题，蒟蒻们都惊呆了。
## 题目描述

给定 $n$，求

$$\sum_{i = 1}^n \operatorname{lcm}(i, n)$$

其中 $\operatorname{lcm}(i, j)$ 表示 $i$ 和 $j$ 的最小公倍数。
## 输入格式

**本题单测试点内有多组数据**。

输入的第一行是一个整数 $T$，表示数据组数。

接下来 $T$ 行，每行一个整数，表示一组数据的 $n$。
## 输出格式

对于每组数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
1
2
5

```
### 样例输出 #1
```
1

4

55
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $T \leq 5$，$n \leq 10^5$。
- 对于 $100\%$ 的数据，$1 \leq T \leq 3 \times 10^5$，$1 \leq n \leq 10^6$。



---

---
title: "[SDOI2008] 仪仗队"
layout: "post"
diff: 提高+/省选-
pid: P2158
tag: ['2008', '各省省选', '山东', '素数判断,质数,筛法', '欧拉函数']
---
# [SDOI2008] 仪仗队
## 题目描述

作为体育委员，C 君负责这次运动会仪仗队的训练。仪仗队是由学生组成的 $N \times N$ 的方阵，为了保证队伍在行进中整齐划一，C 君会跟在仪仗队的左后方，根据其视线所及的学生人数来判断队伍是否整齐（如下图）。

![](https://cdn.luogu.com.cn/upload/pic/1149.png)

现在，C 君希望你告诉他队伍整齐时能看到的学生人数。
## 输入格式

一行，一个正整数 $N$。
## 输出格式

输出一行一个数，即 C 君应看到的学生人数。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
9
```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 40000$。


---

---
title: "[SDOI2012] Longge 的问题"
layout: "post"
diff: 提高+/省选-
pid: P2303
tag: ['数学', '2012', '各省省选', '山东', 'O2优化', '欧拉函数']
---
# [SDOI2012] Longge 的问题
## 题目背景

Longge 的数学成绩非常好，并且他非常乐于挑战高难度的数学问题。
## 题目描述

现在问题来了：给定一个整数 $n$，你需要求出 $\sum\limits_{i=1}^n \gcd(i, n)$，其中 $\gcd(i, n)$ 表示 $i$ 和 $n$ 的最大公因数。  
## 输入格式

输入只有一行一个整数，表示 $n$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
6

```
### 样例输出 #1
```
15
```
## 提示

#### 数据规模与约定

- 对于 $60\% $ 的数据，保证 $n\leq 2^{16}$。
- 对于 $100\% $ 的数据，保证 $1\leq n< 2^{32}$。


---

---
title: "GCD SUM"
layout: "post"
diff: 提高+/省选-
pid: P2398
tag: ['素数判断,质数,筛法', '欧拉函数']
---
# GCD SUM
## 题目描述

求

$$\sum_{i=1}^n \sum_{j=1}^n \gcd(i, j)$$
## 输入格式

第一行一个整数 $n$。
## 输出格式

第一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
5
```
## 提示

对于 $30\%$ 的数据，$n\leq 3000$。

对于 $60\%$ 的数据，$7000\leq n\leq 7100$。

对于 $100\%$ 的数据，$n\leq 10^5$。



---

