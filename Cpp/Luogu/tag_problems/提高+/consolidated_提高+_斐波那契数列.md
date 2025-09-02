---
title: "斐波那契公约数"
layout: "post"
diff: 提高+/省选-
pid: P1306
tag: ['数学', '倍增', '线性数据结构', '递归', '斐波那契数列']
---
# 斐波那契公约数
## 题目描述

对于 Fibonacci 数列：

$$ f_i = \begin{cases}
  [i = 1]               & i \leq 1 \\
  f_{i - 1} + f_{i - 2} & i \gt 1
\end{cases}$$

请求出 $f_n$ 与 $f_m$ 的最大公约数，即 $\gcd(f_n, f_m)$。
## 输入格式

一行两个正整数 $n$ 和 $m$ 。
## 输出格式

输出一行一个整数，代表 $f_n$ 和 $f_m$ 的最大公约数。答案请对 $10^8$ 取模。
## 样例

### 样例输入 #1
```
4 7
```
### 样例输出 #1
```
1
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 10^9$。


---

---
title: "[POI 2005] SUM-Fibonacci Sums"
layout: "post"
diff: 提高+/省选-
pid: P3424
tag: ['贪心', '2005', 'POI（波兰）', '斐波那契数列']
---
# [POI 2005] SUM-Fibonacci Sums
## 题目描述

Fibonacci numbers are an integer sequence defined in the following way: $Fib_0=1$, $Fib_1=1$, $Fib_i=Fib_{i-1}+Fib_{i-2}$ (for $i\ge 2$). The first few numbers in this sequence are: ($1,1,2,3,5,8,\cdots$).

The great computer scientist Byteazar is constructing an unusual computer, in which numbers are represented in Fibonacci system i.e. a bit string $(b_1,b_2,\cdots,b_n)$ denotes the number $b_1\cdot Fib_1+b_2\cdot Fib_2+\cdots+b_n\cdot Fib_n$. (Note that we do not use $Fib_0$.) Unfortunately, such a representation is ambiguous i.e. the same number can have different representations. The number $42$, for instance, can be written as: $(0,0,0,0,1,0,0,1)$, $(0,0,0,0,1,1,1,0)$ or $(1,1,0,1,0,1,1)$. For this very reason, Byteazar has limited himself to only using representations satisfying the following conditions:

if $n>1$, then $b_n=1$, i.e. the representation of a number does not contain leading zeros.

if $b_i=1$, then $b_{i+1}=0$ (for $i=1,\cdots,n-1$), i.e. the representation of a number does not contain two (or more) consecutive ones.

The construction of the computer has proved more demanding than Byteazar supposed. He has difficulties implementing addition. Help him!

TaskWrite a programme which:

reads from the standard input the representations of two positive integers,calculates and writes to the standard output the representation of their sum.
## 输入格式

The input contains the Fibonacci representations (satisfying the aforementioned conditions) of two positive integers $x$ and $y$ - one in the first, the other in the second line. Each of these representations is in the form of a sequence of non-negative integers, separated by single spaces. The first number in the line denotes the length of the representation $n$, $1\le n\le 1\ 000\ 000$. It is followed by $n$ zeros and/or ones.

## 输出格式

In the first and only line of the output your programme should write the Fibonacci representation (satisfying the aforementioned conditions) of the sum $x+y$. The representation should be in the form of a sequence of non-negative integers, separated by single spaces, as it has been described in the Input section. The first number in the line denotes the length of the representation $n$, $1\le n\le 1\ 000\ 000$. It is followed by $n$ zeros and/or ones.

## 样例

### 样例输入 #1
```
4 0 1 0 1
5 0 1 0 0 1
```
### 样例输出 #1
```
6 1 0 1 0 0 1
```
## 题目翻译

斐波那契数是一个这样定义的整数：$F(0)=1$，$F(1)=1$，$F(i)=F(i-1)+F(i-2)$  $(i>=2)$，前几个数是这样的 $1, 1, 2, 3, 5, 8, \ldots$ 

伟大的计算机学家 $\texttt{Byteazar}$ 正在做一个非凡的计算机，其中的数由斐波那契表示！

如一个数列 $b_1, b_2, \ldots , b_n$ 表示数字 $F(1) \times b_1+b_2 \times F(2)+ \ldots +b_n \times F(n)$（不使用 $F(0)$ ）。

不幸的是，这样的表示并不明确，即相同的数字可以有不同的表示。比如 $42$ 可以表示为 $(0,0,0,0,1,0,0,1)$，$(0,0,0,0,1,1,1,0)$ 或 $(1,1,0,1,0,1,1)$，于是  $\texttt{Byteazar}$ 加了一个限制：

- 如果 $n>1$，那么$b_n=1$，即数字的表示不包含前导零。
- 如果 $b_i=1$，那么 $b_{i+1}=0$，即数字的表示不包含两个（或多个）连续的数字。

这个计算机的建设比  $\texttt{Byteazar}$ 所认为的要难，现在请你来帮帮他~。

你需要写一个程序：

读取两个正整数的表示，计算并向标准输出写入其和的表示。

### 输入格式

输入的第一行先是一个正整数，为 $x$ 的斐波那契表示的长度，接下来的序列是 $x$ 的斐波那契表示。

第二行的第一个数字也是一个正整数，为 $y$ 的斐波那契表示的长度，接下来的序列是 $y$ 的斐波那契表示。

### 输出格式

输出只有一行程序，应写入$x+y$ 的和的斐波纳契表示（满足上述条件），同样是先输出一个正整数 $n$ ，表示 $x+y$ 的和的斐波纳契表示的长度，然后再输出 $x+y$ 的和的斐波那契表示。

$1\leq n \leq 10^6$。

感谢@codesonic 提供的翻译


---

---
title: "斐波那契数列"
layout: "post"
diff: 提高+/省选-
pid: P3986
tag: ['数学', '递归', '枚举', '不定方程', '斐波那契数列', '洛谷月赛']
---
# 斐波那契数列
## 题目描述

定义一个数列：


$f(0) = a, f(1) = b, f(n) = f(n - 1) + f(n - 2)$


其中 $a, b$ 均为正整数，$n \geq 2$。


问有多少种 $(a, b)$，使得 $k$ 出现在这个数列里，且不是前两项。


由于答案可能很大，你只需要输出答案模 $10^9 + 7$ 的结果即可。

## 输入格式

一行一个整数 $k$。

## 输出格式

一行一个数，表示答案模 $10^9 + 7$ 的结果。

## 样例

### 样例输入 #1
```
19260817
```
### 样例输出 #1
```
34166325
```
### 样例输入 #2
```
1000000000
```
### 样例输出 #2
```
773877569
```
## 提示

$1 \leq k \leq 10^9$



---

---
title: "[BJOI2012] 最多的方案"
layout: "post"
diff: 提高+/省选-
pid: P4133
tag: ['贪心', '递推', '2012', '各省省选', '北京', 'O2优化', '枚举', '斐波那契数列']
---
# [BJOI2012] 最多的方案
## 题目描述

第二关和很出名的斐波那契数列有关，地球上的 OIer 都知道：  
$$F_n = \begin{cases} 1 & (n \le 2) \\ F_{n-1}+F_{n-2} & (n \ge 3) \end{cases}$$ 
每一项都可以称为斐波那契数。  

现在给一个正整数 $n$，它可以写成一些斐波那契数的和的形式。如果我们要求不同的方案中不能有相同的斐波那契数，那么对一个 $n$ 最多可以写出多少种方案呢？

## 输入格式

只有一个整数 $n$。

## 输出格式

一个整数表示方案数。
## 样例

### 样例输入 #1
```
16
```
### 样例输出 #1
```
4
```
## 提示

Hint：16=3+13=3+5+8=1+2+13=1+2+5+8

【数据范围】   
对于 $30\%$ 的数据，$n \le 256$；  
对于 $100\%$ 的数据，$n \le 10^{18}$。



---

---
title: "猜数"
layout: "post"
diff: 提高+/省选-
pid: P4862
tag: ['递推', '斐波那契数列', '线性递推']
---
# 猜数
## 题目背景

Iris 和 Beryl 两人在玩一个猜数的游戏。
## 题目描述

游戏是这样进行的：给定一个正整数 $n$，Iris 在 $S=\{1,2,...,n\}$ 中选择一个数 $m$。  

然后，Iris 要如实回答 Beryl 的若干个问题，这些问题的形式是：“$m$ 是集合 $A$ 中的元素吗？”其中 $A\subseteq S$。   
如果Iris回答“是”，则 Beryl 要给 Iris $a$ 元钱；否则，Beryl 要给 Iris $b$ 元钱。（数据保证 $a>b$）

那么，Beryl 至少准备多少钱，就一定能确定 Iris 心中的数字呢？
## 输入格式

第一行：两个正整数 $a$ 和 $b$ 以及数据组数 $t$。   
接下来 $t$ 行，每行一个给定的正整数 $n$，意义如上所述。
## 输出格式

$t$ 行，表示对于每一组数据，Beryl 需要准备的最小钱数。
## 样例

### 样例输入 #1
```
2 1 2
3
6
```
### 样例输出 #1
```
3
5
```
### 样例输入 #2
```
5 3 1
3
```
### 样例输出 #2
```
8
```
## 提示

【样例1的第1组数据解释】 

Beryl先对集合 $\{1\}$ 进行询问，若得到的答案是“是”，则已经确定 Iris 选的数为 $1$，需要 $2$ 元。若得到的答案是“否”，则再对集合 $\{2\}$ 进行询问，显然运气最差要再花 $2$ 元，共 $3$ 元，故答案为 $3$ 元。   

----   

【数据范围】  

| 测试点编号 | $n$ |$t$| $a$,$b$ |
| :----------- | :----------- | :----------- | :----------- |
| 1 | $\leq 20$ | $\leq 10$ | $\leq 20$ |
| 2 | $\leq 20$ | $\leq 10$ | $\leq 20$ |
| 3 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 4 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 5 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 6 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
|7  | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 8 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |
| 9 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |
| 10 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |




---

---
title: "帕秋莉的手环"
layout: "post"
diff: 提高+/省选-
pid: P4910
tag: ['数学', '图论', '递推', '矩阵加速', '斐波那契数列']
---
# 帕秋莉的手环
## 题目背景

帕秋莉是蕾米莉亚很早结识的朋友，现在住在红魔馆地下的大图书馆里。不仅擅长许多魔法，还每天都会开发出新的魔法。只是身体比较弱，因为哮喘，会在咏唱符卡时遇到麻烦。

她所用的属性魔法，主要是生命和觉醒的“木”，变化和活动的“火”，基础和不动的“土”，果实和丰收的“金”，寂静和净化的“水”，机动和攻击的“日”，被动和防御的“月”七种属性

没有窗户的图书馆或许充满了灰尘，不过她认为在书旁边才是自己，所以她不能从书的旁边离开。这样已经一百年了。
## 题目描述

经过数年魔法的沉淀，帕秋莉将她那浩瀚无边的魔法的一部分浓缩到了一些特质的珠子中。

由于帕秋莉爱好和平，她只把象征生命和觉醒的木属性魔法和果实和丰收的金属性魔法放入了珠子中。

她认为光要这些珠子没有什么用处，于是她想将这些珠子串成魔法手环，这样就好看多了。于是，她拿出来用来串这些珠子的线 - 雾雨灵径。

她将这些珠子串到一起之后发现了一些性质：一段雾雨灵径的颜色是由两边的珠子的属性决定的，当一段雾雨灵径连接的两个珠子中只要有一个是金属性的，那么这段雾雨灵径的颜色就为金色

帕秋莉想要一个全都是金色的手环，而且她还想知道一共有多少种方案。由于她还要研究新的魔法，她就把这件事交给了你。由于她的魔法浩瀚无边，她有无穷的珠子

她并不想看着好几十位的数字，于是你需要对 $1000000007$ 进行取模
## 输入格式

输入包含多组数据

第一行一个正整数 $T$ ，表示数据组数。

之后每组数据有一个 $n$ 代表木属性珠子和金属性珠子的总个数
## 输出格式

对于每组数据，输出取模后的方案数

## 样例

### 样例输入 #1
```
2
5
20
```
### 样例输出 #1
```
11
15127
```
### 样例输入 #2
```
3
9
99
999
```
### 样例输出 #2
```
76
281781445
445494875
```
### 样例输入 #3
```
5  
123
1234
12345
123456
1234567
```
### 样例输出 #3
```
528790589
200102666
537707871
262341000
534036342

```
## 提示

这里给出 $n = 5$ 时，样例的解释


使用 $1, 2, 3, 4, 5$ 来代表各个珠子

可行的方案是

$\{1, 3, 5\}, \{1, 2, 4\}, \{1, 3, 4\}, \{2, 3, 5\}, \{2, 4, 5\}$

$\{1, 2, 3, 4\}, \{1, 2, 3, 5\}, \{1, 2, 4, 5\}, \{1, 3, 4, 5\}, \{2, 3, 4, 5\}$

$\{1, 2, 3, 4, 5\}$



对于 $20\%$ 的数据，有 $1 \le n \le 10$ ；

对于 $40\%$ 的数据，有 $1 \le n \le 10^2$ ；

对于 $60\%$ 的数据，有 $1\le n \le 10^6$ ；

对于 $90\%$ 的数据，有 $1 \le n \le 10^9$ ；

对于全部的数据，有 $1\le T \le 10,  1\le n \le 10^{18}$


---

