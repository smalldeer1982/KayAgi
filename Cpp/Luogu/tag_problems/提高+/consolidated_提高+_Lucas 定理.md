---
title: "[GCJ 2008 #3] Endless Knight"
layout: "post"
diff: 提高+/省选-
pid: P13473
tag: ['2008', '组合数学', '容斥原理', 'Lucas 定理', 'Google Code Jam']
---
# [GCJ 2008 #3] Endless Knight
## 题目描述

In the game of chess, there is a piece called the knight. A knight is special -- instead of moving in a straight line like other pieces, it jumps in an "L" shape. Specifically, a knight can jump from square $(r_1, c_1)$ to $(r_2, c_2)$ if and only if $(r_1 - r_2)^2 + (c_1 - c_2)^2 = 5$.

In this problem, one of our knights is going to undertake a chivalrous quest of moving from the top-left corner (the $(1, 1)$ square) to the bottom-right corner (the $(H, W)$ square) on a gigantic board. The chessboard is of height $H$ and width $W$.

Here are some restrictions you need to know.

* The knight is so straightforward and ardent that he is only willing to move towards the right and the bottom. In other words, in each step he only moves to a square with a bigger row number and a bigger column number. Note that, this might mean that there is no way to achieve his goal, for example, on a 3 by 10 board.
* There are $R$ squares on the chessboard that contain rocks with evil power. Your knight may not land on any of such squares, although flying over them during a jump is allowed.

Your task is to find the number of unique ways for the knight to move from the top-left corner to the bottom-right corner, under the above restrictions. It should be clear that sometimes the answer is huge. You are asked to output the remainder of the answer when divided by $10007$, a prime number.
## 输入格式

Input begins with a line containing a single integer, $N$. $N$ test cases follow.

The first line of each test case contains 3 integers, $H$, $W$, and $R$. The next $R$ lines each contain 2 integers each, $r$ and $c$, the row and column numbers of one rock. You may assume that $(1, 1)$ and $(H, W)$ never contain rocks and that no two rocks are at the same position.

## 输出格式

For each test case, output a single line of output, prefixed by "Case #$X$: ", where $X$ is the 1-based case number, followed by a single integer indicating the number of ways of reaching the goal, modulo $10007$.
## 样例

### 样例输入 #1
```
5
1 1 0
4 4 1
2 1
3 3 0
7 10 2
1 2
7 1
4 4 1
3 2
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
Case #3: 0
Case #4: 5
Case #5: 1
```
## 提示

**Limits**

- $1 \leq N \leq 100$
- $0 \leq R \leq 10$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq W \leq 100$
- $1 \leq H \leq 100$
- $1 \leq r \leq H$
- $1 \leq c \leq W$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq W \leq 10^{8}$
- $1 \leq H \leq 10^{8}$
- $1 \leq r \leq H$
- $1 \leq c \leq W$


---

---
title: "[ZJOI2010] 排列计数"
layout: "post"
diff: 提高+/省选-
pid: P2606
tag: ['动态规划 DP', '数学', '2010', '各省省选', '浙江', '组合数学', 'Lucas 定理']
---
# [ZJOI2010] 排列计数
## 题目描述

称一个 $1 \sim n$ 的排列 $p_1,p_2, \dots ,p_n$ 是 Magic 的，当且仅当  
$$\forall i \in [2,n],p_i > p_{\lfloor i/2 \rfloor}$$
计算 $1 \sim n$ 的排列中有多少是 Magic 的，答案可能很大，只能输出模 $m$ 以后的值。
## 输入格式

一行两个整数 $n,m$，含义如上所述。

## 输出格式

输出文件中仅包含一个整数，表示 $1\sim n$ 的排列中， Magic 排列的个数模 $m$ 的值。

## 样例

### 样例输入 #1
```
20 23 
```
### 样例输出 #1
```
16

```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 10^6$, $1\le m \le 10^9$，$m$ 是一个质数。



---

---
title: "《瞿葩的数字游戏》T3-三角圣地"
layout: "post"
diff: 提高+/省选-
pid: P2675
tag: ['数学', '贪心', '洛谷原创', '组合数学', 'Lucas 定理']
---
# 《瞿葩的数字游戏》T3-三角圣地
## 题目背景

国王1带大家到了数字王国的中心：三角圣地。

## 题目描述

不是说三角形是最稳定的图形嘛，数字王国的中心便是由一个倒三角构成。这个倒三角的顶端有一排数字，分别是1~N。1~N可以交换位置。之后的每一行的数字都是上一行相邻两个数字相加得到的。这样下来，最底端就是一个比较大的数字啦！数字王国称这个数字为“基”。国王1希望“基”越大越好，可是每次都自己去做加法太繁琐了，他希望你能帮他通过编程计算出这个数的最大值。但是这个值可能很大，所以请你输出它mod 10007 的结果。


任务：给定N，求三角形1~N的基的最大值 再去 mod 10007。

## 输入格式

一个整数N

## 输出格式

一个整数，表示1~N构成的三角形的最大的“基”

## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
1125
```
### 样例输出 #2
```
700
```
## 提示

数据：

20%    0<=N<=100

50%    0<=N<=3000

100% 0<=N<=1000000

样例解释：

1   3   4   2

4    7   6

11  13

24
是N=4的时候的最大值，当然还有别的构成形式。


PS：它叫做三角圣地，其实它就是个三角形~


本题数据已经更新，目前全部正确无误！

不要面向数据编程！



---

---
title: "【模板】卢卡斯定理/Lucas 定理"
layout: "post"
diff: 提高+/省选-
pid: P3807
tag: ['递归', '素数判断,质数,筛法', '进制', '组合数学', '逆元', 'Lucas 定理']
---
# 【模板】卢卡斯定理/Lucas 定理
## 题目背景

这是一道模板题。

## 题目描述

给定整数 $n, m, p$ 的值，求出 $C_{n + m}^n \bmod p$ 的值。

输入数据保证 $p$ 为质数。

注: $C$ 表示组合数。
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据: 

一行，三个整数 $n, m, p$。
## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
2
1 2 5
2 1 5
```
### 样例输出 #1
```
3
3
```
## 提示

对于 $100\%$ 的数据，$1 \leq n, m, p \leq 10^5$，$1 \leq T \leq 10$。


---

---
title: "「Stoi2033」园游会"
layout: "post"
diff: 提高+/省选-
pid: P7976
tag: ['数学', 'O2优化', '数位 DP', 'Lucas 定理']
---
# 「Stoi2033」园游会
## 题目背景

> 我顶着大太阳 只想为你撑伞  
> 你靠在我肩膀 深呼吸怕遗忘  
> 因为捞鱼的蠢游戏我们开始交谈  
> 多希望话题不断园游会永不打烊  
> 气球在我手上 我牵着你瞎逛  
> 有话想对你讲 你眼睛却装忙  
> 鸡蛋糕跟你嘴角果酱我都想要尝  
> 园游会影片在播放 这个世界约好一起逛  
> ——《园游会》
## 题目描述

设 $F(x)=(x+1)\bmod 3-1$，给定 $n$，求：

$$\sum_{l=0}^n \sum_{r=l}^n F\left(C_{r}^{l}\right)$$

对 $1732073999$ 取模。其中 $C_{r}^{l}$ 为组合数，具体地，

$$C_{r}^{l}=\dfrac{r!}{l!(r-l)!}$$
## 输入格式

**本题有多组询问。**

第一行两个正整数 $t,maxn$，表示询问组数与询问的最大可能值。

接下来 $t$ 行，每行一个正整数 $n$。
## 输出格式

共 $t$ 行，第 $i$ 行一个整数，为第 $i$ 次询问的答案对 $1\ 732\ 073\ 999$ 取模的结果。
## 样例

### 样例输入 #1
```
4 173
1
5
20
34
```
### 样例输出 #1
```
3
12
52
94
```
## 提示

### 数据范围

**本题采用捆绑测试。**

| Subtask | 分值 | $1\le t \le$ | $1\le n \le maxn \le$ |
| :-: | :-: | :-: | :-: |
| $1$ | $16$ | $1$ | $300$ |
| $2$ | $37$ | $300$ | $7 \times 10^6$ |
| $3$ | $47$ | $3 \times 10^4$ | $2 \times 10^{16}$ |

对于 $100\%$ 的数据，$1 \le t \le 3 \times 10^4,1 \le n \le maxn \le 2 \times 10^{16}$。


---

