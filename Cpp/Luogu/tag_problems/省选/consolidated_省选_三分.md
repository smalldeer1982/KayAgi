---
title: "[蓝桥杯 2023 国 Python A] 等腰三角形"
layout: "post"
diff: 省选/NOI-
pid: P10989
tag: ['2023', '三分', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Python A] 等腰三角形
## 题目背景

Python 用户建议使用 PyPy3 提交本题。
## 题目描述

给定一个包含 $n$ 个数的序列 $A_i$，每次操作可以选择其中任意一个数将其
$+1$ 或 $−1$。

我们要让这个序列满足能够从中任选三个数，这三个数对应长度的三条边总能组成一个等腰三角形。问最少需要多少次操作才能让序列满足条件。

## 输入格式

输入的第一行包含一个整数 $n$。

第二行包含 $n$ 个整数，分别表示 $A_1, A_2, \cdots, A_n$，相邻两个整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数，表示最少的操作次数。

## 样例

### 样例输入 #1
```
5
3 3 5 7 7

```
### 样例输出 #1
```
3

```
## 提示

对于 $40\%$ 的评测用例，$n \le 5000,A_i \le5000$；

对于 $70\%$ 的评测用例，$n \le 2 \times 10^5,A_i \le 10^6$；

对于所有评测用例，$1 \le n \le 2 \times 10^5,1 \le A_i \le 10^9$。

#### 样例解释

将原序列修改为 $4, 4, 4, 7, 7$ 即可。



---

---
title: "[ICPC 2022/2023 WF] Carl’s Vacation"
layout: "post"
diff: 省选/NOI-
pid: P12298
tag: ['计算几何', '2022', '2023', '三分', 'Special Judge', 'ICPC']
---
# [ICPC 2022/2023 WF] Carl’s Vacation
## 题目描述

Carl the ant is back! After traversing meandering paths (Problem A, 2004 World Finals) and wandering over octahedrons (Problem C, 2009 World Finals) it is time for a little vacation — time to see the sights! And where better to see the sights than at the tips of tall structures like, say, pyramids!! And where better to see tall pyramids but Egypt!!! (This is so exciting!!!!!)

After taking in the view from the tip of one pyramid, Carl would like to go to the tip of another. Since ants do not do particularly well in the hot sun, he wants to find the minimum distance to travel between the tips of these two pyramids, assuming he can only walk on the surfaces of the pyramids and the plane which the pyramids sit upon. The pyramids are, geometrically, right square pyramids, meaning the apex of the pyramid lies directly above the center of a square base.

![](https://cdn.luogu.com.cn/upload/image_hosting/t5j6zy9j.png)

Illustration of two pyramids corresponding to Sample Input 1. The black line shows the shortest path between their apexes.
## 输入格式

The first line of input contains five integers $x_1, y_1, x_2, y_2, h$ where $x_1, y_1, x_2, y_2$ ($-10^5 \le x_1, x_2, y_1, y_2 \le 10^5$ and $(x_1, y_1) \neq (x_2, y_2)$) define an edge of the first pyramid, with the body of the pyramid lying to the left of the directed vector from $(x_1, y_1)$ to $(x_2, y_2)$, and $h$ ($1 \le h \le 10^5$) is the height of the pyramid. The second line of input describes the second pyramid in the same format. The intersection of the bases of the two pyramids has $0$ area.
## 输出格式

Output the minimum distance Carl travels between the tips of the two pyramids. Your answer should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
0 0 10 0 4
9 18 34 26 42

```
### 样例输出 #1
```
60.866649532

```


---

---
title: "[GCJ 2012 #3] Quality Food"
layout: "post"
diff: 省选/NOI-
pid: P13330
tag: ['数学', '2012', '二分', '三分', 'Google Code Jam']
---
# [GCJ 2012 #3] Quality Food
## 题目描述

You just moved from your hometown to a big metropolitan city! You love everything about your new environment, except for the food. Your hometown provides the best food in the region (called "quality food") and you sure will miss it.

Fortunately, the largest restaurant in your hometown provides a food delivery service. You can purchase any amount of food in one delivery. There is a constant delivery fee for every delivery, regardless of the amount of food purchased in the delivery.

This restaurant serves different types of food. Each type of food has two properties: a price-per-meal, and a time-to-stale. One "meal" of food will feed you for one day; once a meal has been eaten, it cannot be eaten again. The time-to-stale of a type of food is the maximum number of days for which that food can still be eaten, counting from when you received it. A time-to-stale of zero means you must eat that type of food on the day of delivery.

In a single delivery you can purchase as many different types of food, and as many meals of each of those types, as you have money for. Note that if a particular type of food has a time-to-stale of $t$, it doesn't make any sense to order more than $t+1$ meals of that food in one delivery: at least one meal would go stale before you could eat it.

This restaurant has a very fast delivery service, so you will receive all the food in a delivery on the same day that you purchased it, and you may eat some of the food on the same day. Food delivery is the only way for you to receive quality food.

Given an amount of money, which you can spend on meal prices and delivery fees, what is the maximum number of days for which you can eat quality food every day?
## 输入格式

The first line of input gives the number of test cases, $T$. $T$ test cases follow. Each test case will begin with three integers, $M$, $F$ and $N$, denoting the amount of money you have, the delivery fee, and the number of types of food provided by the restaurant, respectively. $N$ lines follow, each will consist of two integers, $P_i$ and $S_i$, denoting respectively the price-per-meal and time-to-stale of one type of food.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the maximum number of days that you can keep eating at least one meal of quality food everyday.
## 样例

### 样例输入 #1
```
3
32 5 2
5 0
10 2
10 10 1
10 10
10 1 1
1 5
```
### 样例输出 #1
```
Case #1: 3
Case #2: 0
Case #3: 8
```
## 提示

**Sample Explanation**

An example scenario for the first case is by purchasing one meal of the first type and one meal of the second type during your first day in the city (costing a total of 20). Eat the first type of food that day, and eat the second type the next day. During your third day, purchase one meal of the first type and eat it on the same day. This accounts for three days.

**Limits**

- $1 \leq T \leq 50.$
- $1 \leq F \leq M.$
- $1 \leq N \leq 200.$
- $1 \leq P_i \leq M.$

**Test set 1 (9 Pts, Visible Verdict)**

- $0 \leq S_i \leq 2,000,000.$
- $1 \leq M \leq 2,000,000.$

**Test set 2 (18 Pts, Hidden Verdict)**

- $0 \leq S_i \leq 10^{18}.$
- $1 \leq M \leq 10^{18}.$


---

---
title: "[USACO19FEB] Cow Dating P"
layout: "post"
diff: 省选/NOI-
pid: P5242
tag: ['2019', 'USACO', '三分', '斜率优化']
---
# [USACO19FEB] Cow Dating P
## 题目描述

由于目前可供奶牛们使用的约会网站并没有给 Farmer John 留下深刻印象，他决定推出一个基于新匹配算法的奶牛交友网站，该算法可基于公牛和母牛间的共同兴趣对公牛和母牛进行匹配。

Bessie 在寻找情人节 Barn Dance 的合作伙伴时，决定试用这个网站。在注册账户之后，FJ 的算法为他给出了一个长度为 $ N $（$1 \leq N \leq 10^6$） 的匹配列表，列表上每头公牛接受她舞蹈邀请的概率为 $ p $（$0 < p < 1$）。

Bessie 决定向列表中的一个连续区间内的奶牛发送邀请，但Bessie希望**恰好只有一个奶牛**接受邀请。请帮助 Bessie 求出**恰好只有一个奶牛**接受邀请的最大概率是多少。
## 输入格式

第一行输入一个整数 $ N $ 。

接下来 $ N $ 行，每行包含一个整数，它的含义是 $ p_i $ 乘以 $ 10^6 $ 后的结果。
## 输出格式

请输出**恰好只有一个奶牛**接受邀请的最大概率乘以 $ 10^6 $ 后向下取整后的结果。
## 样例

### 样例输入 #1
```
3
300000
400000
350000

```
### 样例输出 #1
```
470000
```
## 提示

样例的最优方案是向第二和第三只奶牛发送邀请。

子任务：对于 $ 25\% $ 的数据， $ N \leq 4000 $ 。


---

---
title: "[JRKSJ R6] func"
layout: "post"
diff: 省选/NOI-
pid: P8568
tag: ['数学', '二分', '2022', '三分', '洛谷原创', '交互题', 'Special Judge', 'O2优化']
---
# [JRKSJ R6] func
## 题目描述

**这是一道 IO 交互题．**

你有一个一次函数 $f(x)=kx+b$（$1\le x \le n-1$）．这个一次函数满足 $k,b$ 均为整数且 $k>0$．

vectorwyx 修改了这个函数，具体而言，他会选择一个整数 $t$（$1\le t \le n-1$），将这个函数在直线 $x=t$ 及右侧的部分向右平移一个单位长度，并把两部分的端点用直线段连接，得到一个分段函数 $g(x)$：

$$
g(x)=\begin{cases}
kx+b&1\le x<t\\
kt+b& t\le x <t+1\\
k(x-1)+b& t+1\le x \le n
\end{cases}
$$

请通过交互的方式得到 $t$ 的值．

### 交互方式

**本题单个测试点中含有多组数据．**

1. 首先从标准输入流读入一个整数 $T$，表示数据组数．
1. 接下来你将进行 $T$ 组数据的交互．对于每组数据，首先从标准输入流读入三个整数 $n,Q,P$．
1. 你可以通过向标准输出流输出 `? l r p` $(1\le l \le r \le n$，$2\le p \le P$$)$ 的方式来询问．在单组数据中，你最多只能进行 $Q$ 次 `?` 操作．交互库会根据你的询问依次做出以下判断并向标准输入流发送返回结果：
    - 若你的询问数据范围错误，回答为 $-2$．此时交互库会直接返回 WA．你需要立刻退出你的程序来避免与已经结束程序的交互库交互引起超时．
    - 若 $g(l)=g(r)$，回答为 $-1$．
    - 否则回答为 $(g(l) + g(r))\bmod p$．
1. 你可以通过向标准输出流输出 `! t` 的方式来给出答案．你只能进行一次回答操作，且回答操作必须是你在每组数据中进行的最后一个操作．交互完成后，从标准输入流读入一个零或一的整数 $x$．若 $x=1$ 则代表当前数据回答正确，你需要回到步骤 $2$ 以进行下一组数据的交互．否则 $x=0$，你需要立刻退出自己的程序．

**不要忘记在每次输出后刷新缓冲区，否则你将会 TLE．**

下面是一些语言的刷新缓冲区操作：

- C++：`fflush(stdout)` 或 `cout.flush()`．
- C: `fflush(stdout)`．
- Java: `System.out.flush()`．
- Python: `stdout.flush()`．
- Pascal: `flush(output)`．
- 其他语言：请参考对应语言的帮助文档．

## 输入格式

见「交互方式」．
## 输出格式

见「交互方式」，
## 样例

### 样例输入 #1
```
1
5 999 999

0

1

1
```
### 样例输出 #1
```


? 1 3 2

? 4 5 2

! 3
```
## 提示

### 样例解释

请注意，样例仅用来表示交互的规则，不保证有逻辑性．

#### 样例 #1

$f(x)=3x-2$（$1\le x \le 4$），$t=3$．

$$
g(x)=\begin{cases}
3x-2&1\le x<3\\
7& 3\le x <4\\
3x-5& 4\le x \le 5.
\end{cases}
$$

所以第一次询问的结果 $(g(1) + g(3))\bmod 2 = (1+7)\bmod 2=0$，第二次询问的结果 $(g(4)+g(5))\bmod 2 = (7+ 10)\bmod 2=1$．

### 数据范围与约束

**本题采用捆绑测试．且不存在一个 Subtask 包含其它所有 Subtask 的限制．**

| Subtask | 分值 |    $n$     | $Q=$ |       $P=$        | $g(x)\le$ |    特殊性质     |
| ------- | ---- | ---------- | ---- | ----------------- | --------- | --------------- |
| $1$     | $10$ | $\le 10^9$ | $42$ | $2\times 10^{18}$ | $10^{18}$ | 无              |
| $2$     | $20$ | $\le 10^9$ | $30$ | $2$               | $10^{18}$ | 斜率 $k$ 为奇数 |
| $3$     | $30$ | $\le 10^9$ | $42$ | $50$              | $10^{18}$ | 无              |
| $4$     | $39$ | $\le 10^9$ | $32$ | $50$              | $10^{18}$ | 无              |
|$5$|$1$|$ = 1162261531$| $32$| $50$| $7857125847061472735$|无|

对于 $100\%$ 的数据，保证 $1 \le T \le 10$，$2\le n\le 1162261531$．且满足 $\forall x \in [1,n], 0 \le g(x)\le 7857125847061472735$．

### 提示

由于本题不存在一个 Subtask 包含其它所有 Subtask 的限制．所以数据范围中「对于 $100\%$ 的数据」部分的 $n$ 和 $g(x)$ 的上界没有任何意义．但由于直接写「对于 $100\%$ 的数据，满足 $n \ge 2$，$g(x)\ge 0$」会被某些管理以「你管这叫数据范围」打回，故此题中保留该没有意义的上界．


---

