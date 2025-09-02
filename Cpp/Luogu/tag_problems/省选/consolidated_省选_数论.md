---
title: "[YDOI R1] Lattice"
layout: "post"
diff: 省选/NOI-
pid: P10186
tag: ['数论', '素数判断,质数,筛法', '莫比乌斯反演', '杜教筛']
---
# [YDOI R1] Lattice
## 题目背景

se 喜欢点阵。
## 题目描述

se 有一个正方形点阵，这个点阵以 $(1,1)$ 为左下角，以 $(n,n)$ 为右上角。

se 还有一条直线，其表达式为 $y=kx$，其中 $k\in(0,\infty)$。

对于任意一个 $k$，设该直线经过了 $cnt$ 个点阵中的点，se 对这条直线有一个喜爱程度，为 $cnt^2$。

se 想知道所有直线的喜爱程度和对 $10^9+7$ 取模的结果，请你告诉 se。
## 输入格式

一行一个整数 $n$。
## 输出格式

输出一个整数，表示喜爱程度和对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
1919810
```
### 样例输出 #2
```
107114211
```
## 提示

### 样例解释 #1
当 $k$ 为 $\frac{1}{2}$ 时，直线过点阵中的点 $(2,1)$，喜爱程度为 $1^2=1$；当 $k$ 为 $1$ 时，直线过点阵中的点 $(1,1)$ 和点 $(2,2)$，喜爱程度为 $2^2=4$；当 $k$ 为 $2$ 时，直线过点阵中的点 $(1,2)$，喜爱程度为 $1^2=1$。喜爱程度和为 $1+4+1=6$。
### 数据范围
**本题采用捆绑测试**。
|子任务编号|$n\le$|分值|
|:--:|:--:|:--:|
|$1$|$8$|$5$|
|$2$|$10^3$|$15$|
|$3$|$10^6$|$30$|
|$4$|$2^{31}-1$|$50$|

对于 $100\%$ 的数据，$1\le n\le 2^{31}-1$。


---

---
title: "实力派"
layout: "post"
diff: 省选/NOI-
pid: P10269
tag: ['数论', '素数判断,质数,筛法', '最大公约数 gcd', '莫比乌斯反演']
---
# 实力派
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/z8ednvb2.png)
## 题目描述

来自全国各地的 $n$ 位 OIer 组成了一个名为“实力派”的团队，每个人有一个实力值 $a_i$。共有 $m$ 场比赛向他们发送了参赛邀请，其中第 $i$ 场比赛要求 $k_i$ 个人组成一个队伍参加。为了决定他们是否应该参加某场比赛，他们想出了如下两个衡量实力的数据：

- 定义 $x$ 阶最低实力表示从这 $n$ 个人中选出 $x$ 个人，使得这 $x$ 个人实力值的 $\gcd=1$ 的方案数；

- 定义 $x$ 阶最高实力表示从这 $n$ 个人中选出 $x$ 个人，所有方案的 $x$ 个人的 $\gcd$ 之和。

请你对于每场比赛，告诉他们他们在这场比赛中的 $k_i$ 阶最低实力和最高实力。对了，为了不让别人听懂，你需要将答案对一个秘密模数 $p$ 取模。
## 输入格式

第一行三个整数 $n,m,p$，分别表示团队人数，比赛场数及秘密模数；

第二行 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个人的实力值 $a_i$。

接下来 $m$ 行，第 $i$ 行一个整数 $k_i$，表示第 $i$ 场比赛的要求参赛人数。
## 输出格式

输出共 $m$ 行，第 $i$ 行两个整数 $min_i,max_i$，分别表示他们在第 $i$ 场比赛中的最低实力和最高实力，答案对 $p$ 取模。
## 样例

### 样例输入 #1
```
4 4 998244353
8 15 12 6
2
3
4
5
```
### 样例输出 #1
```
1 19
2 7
1 1
0 0
```
### 样例输入 #2
```
6 4 19260817
11 45 14 19 19 810
2
1
2
2
```
### 样例输出 #2
```
12 78
0 918
12 78
12 78
```
### 样例输入 #3
```
8 3 19491001
3 2 2 3 1 2 1 2
5
3
4
```
### 样例输出 #3
```
56 56
52 60
69 71
```
## 提示

**样例** $\mathbf{1}$ **解释**

第一场比赛要求选出 $2$ 人参加，仅有 $(8,15)$ 一种方案的 $\gcd=1$，因此最低实力为 $1$；所有方案的 $\gcd$ 之和为 $19$，因此最高实力为 $19$；

第二场比赛要求选出 $3$ 人参加，有 $(8,15,12)$ 和 $(8,15,6)$ 两种 $\gcd=1$ 的方案，因此最低实力为 $2$；所有方案的 $\gcd$ 之和为 $7$，因此最高实力为 $7$。

**数据范围**

对于所有数据，$1\leq n,m,k_i\leq 2\times 10^5$，$1\leq a_i\leq 10^6$，$10^7\leq p\leq 10^9$，$p\in \mathbb{P}$。

本题共 $30$ 个测试点，**采用捆绑测试**，子任务及数据点分配如下：

| 子任务编号 | 数据点编号 | 特殊性质 | 分值 | 时限 |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $1\sim 4$ | $n\leq 20$ | $10$ | $1s$ |
| $1$ | $5\sim 8$ | $n,a_i\leq 300$ | $10$ | $1s$ | 
| $2$ | $9\sim 12$ | $k_i\leq 2$ | $20$ | $1.5s$ |
| $3$ | $13\sim 16$ | $a_i\leq 3$ | $10$ | $1s$ |
| $4$ | $17\sim 22$ | $a_i\leq 10^5$ | $20$ | $1s$ |
| $5$ | $23\sim 30$ | 无特殊性质 | $30$ | $1.5s$ |

**提示**

$\mathbb{P}$ 表示全体质数集合，$\gcd$ 表示最大公因数。


---

---
title: "高洁（Purity）"
layout: "post"
diff: 省选/NOI-
pid: P10322
tag: ['数学', '数论', '洛谷原创', 'O2优化', '莫比乌斯反演', '拉格朗日插值法', '洛谷比赛']
---
# 高洁（Purity）
## 题目背景

简洁、准确而永恒的美丽 —— 高洁。
****
「高洁之光」拉姆，身为精灵王的他可以完美使用《阿梅斯草纸书》的力量。
## 题目描述

拉姆使用「暴风箭雨」一次射出了 $n$ 支箭，其中第 $i$ 支箭的原始攻击力是 $i$。不过，这些箭会经过一些强化。

对于常数 $d$，设原始攻击力为 $i$ 的箭，其**能级**为 $v(i)$：

- 若不存在正整数 $k$ 使得 $i^k$ 是 $d$ 的整数倍，则 $v(i)=0$；  
- 否则 $v(i)$ 为**最小的**、使得 $i^k$ 是 $d$ 的整数倍的正整数 $k$。

那么这支箭强化后的攻击力为 $i^{v(i)+1}$。

拉姆想知道所有箭在**强化后**的攻击力之和，由于答案可能很大，你只需要求出答案对 $998244353$ 取模的结果。（即求出答案除以 $998244353$ 的余数）
## 输入格式

第一行一个正整数 $T$，表示数据组数。  
接下来 $T$ 行，每行两个正整数 $n,d$，意义如题目描述。
## 输出格式

输出 $T$ 行，每行对应一组数据的答案。
## 样例

### 样例输入 #1
```
5
15 12
400 2520
5000000 68256
10000000 65536
10000000000 3628800
```
### 样例输出 #1
```
462
946645637
231125775
290821843
602104955
```
## 提示

【样例解释】   
对于第一组数据，$d=12$。其中 $v(6)=2$，因为 $12$ 能整除 $6^2$，而不整除 $6^1$，同样也能得到 $v(12)=1$。
可以发现 $n=15$ 以内的其它数能级都为 $0$，故答案为：

$$\left(\sum_{i=1}^{15}i\right)-6-12+6^3+12^2=462$$

对于第二组数据，可以证明 $n$ 以内只有 $v(210)=3$ 非零，由此可以算出答案为 $1944889990$，对 $998244353$ 取模后为 $946645637$。

【数据范围】  
**本题采用捆绑测试。**

Subtask 1（15 pts）：$1 \le n,d \le 10^4$；  
Subtask 2（15 pts）：$d$ 为质数；  
Subtask 3（20 pts）：$d$ 为质数的正整数幂；  
Subtask 4（20 pts）：不存在大于 $1$ 的整数 $x$，使得 $x^4$ 整除 $d$；  
Subtask 5（30 pts）：无特殊限制。

对于全部数据，$1\le T \le 1000$，$1\le n < 2^{63}$，$1\le d \le 10^8$。

【提示】  
此题的时间限制较为宽松，即使你的代码在某些细节上没有优化，也可以正常通过此题。


---

---
title: "BZOJ3518 点组计数"
layout: "post"
diff: 省选/NOI-
pid: P10636
tag: ['数论', 'O2优化', '莫比乌斯反演']
---
# BZOJ3518 点组计数
## 题目描述

平面上摆放着一个 $n\times m$ 的点阵，如下图是一个 $3\times 4$ 的点阵图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6tq3jene.png)

现问，有多少个三元点对组 $(a,b,c)$ 满足 $a,b,c$ 三点共线，顺序无关紧要，例如 $(a,b,c)$ 与 $(b,c,a)$ 算一组。答案对 $10^9+7$ 取模。
## 输入格式

一行，两个正整数 $n,m$。
## 输出格式

一行一个整数，表示答案对 $10^9+7$ 取模后的结果。
## 样例

### 样例输入 #1
```
3 4
```
### 样例输出 #1
```
20
```
## 提示

数据保证，$1\leq n,m\leq 5\times 10^4$。


---

---
title: "BZOJ4833 最小公倍佩尔数"
layout: "post"
diff: 省选/NOI-
pid: P10663
tag: ['数论', 'O2优化', '莫比乌斯反演', '容斥原理']
---
# BZOJ4833 最小公倍佩尔数
## 题目背景

题目来自 BZOJ 2017 年 4 月月赛。
## 题目描述

令 $(1+\sqrt{2})^n=e(n)+\sqrt{2}f(n)$，其中 $e(n),f(n)$ 都是整数，显然有 $(1-\sqrt{2})^n=e(n)-\sqrt{2}f(n)$。令 $g(n)=\operatorname{lcm}(f(1),f(2),\dots,f(n))$。

给定两个正整数 $n,p$，其中 $p$ 是质数，并且保证 $f(1),f(2),\dots,f(n)$ 在模 $p$ 意义下均不为 $0$，请计算 $\sum \limits_{i=1}^n i\times g(i)$ 模 $p$ 的值。
## 输入格式

第一行包含一个正整数 $T$，表示有 $T$ 组数据。

接下来是测试数据。每组测试数据只占一行，包含两个正整数 $n$ 和 $p$。
## 输出格式

对于每组测试数据，输出一行一个非负整数，表示这组数据的答案。
## 样例

### 样例输入 #1
```
5
1 233
2 233
3 233
4 233
5 233
```
### 样例输出 #1
```
1
5
35
42
121
```
## 提示

对于 $100\%$ 的数据，$1\leq T\leq 210$，$1\leq n\leq 10^6$，$2\leq p\leq 10^9+7$，$\sum n\leq 3\times 10^6$。


---

---
title: "BZOJ3328 PYXFIB"
layout: "post"
diff: 省选/NOI-
pid: P10664
tag: ['原根', '数论', 'O2优化', '矩阵乘法', '单位根反演']
---
# BZOJ3328 PYXFIB
## 题目描述

给定整数 $n,k,p$，要求计算下列式子对 $p$ 取模的值：

$$\sum_{i=0}^{\lfloor \frac{n}{k} \rfloor} C_n^{i\times k}\times F_{i\times k}$$

其中：
- $p$ 为质数，且 $p$ 除以 $k$ 的余数为 $1$。
- $C$ 为组合数，即 $C_m^n=\frac{n!}{m!(n-m)!}$。
- $F_n$ 为斐波那契数列，即 $F_0=1$，$F_1=1$，$F_n=F_{n-1}+F_{n-2}(n\geq 2)$。
## 输入格式

第一行输入一个正整数 $T$，表示数据组数。

接下来 $T$ 行，每行三个正整数 $n,k,p$。
## 输出格式

输出 $T$ 行，每行一个整数，表示结果。
## 样例

### 样例输入 #1
```
1
1 2 3
```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^{18}$，$1\leq k \leq 20000$，$1\leq T\leq 20$，$1\leq p\leq 10^9$，$p$ 为质数，且 $p$ 除以 $k$ 的余数为 $1$。


---

---
title: "【MX-X2-T4】「Cfz Round 4」Gcd with Xor"
layout: "post"
diff: 省选/NOI-
pid: P10855
tag: ['数学', '数论', 'O2优化', '莫比乌斯反演', '容斥原理', '字典树 Trie', '梦熊比赛']
---
# 【MX-X2-T4】「Cfz Round 4」Gcd with Xor
## 题目背景

原题链接：<https://oier.team/problems/X2D>。

---

ねえ もしも全て投げ捨てられたら  
呐 若然能将一切舍弃的话

笑って生きることが楽になるの  
笑着活下去这样的事就会变的轻松吗
## 题目描述

给定两个正整数 $n,k$。

定义 $\displaystyle f(x)=\sum_{i=1}^x \gcd(i,i\oplus x)^k$。计算 $\displaystyle \sum_{i=1}^n f(i)$。其中 $\gcd(a,b)$ 表示 $a$ 和 $b$ 的最大公因数，$\oplus$ 表示**按位异或**，即 C++ 中的 `^`。

由于答案可能很大，所以你只需要输出答案对 $10^9+7$ 取模的结果。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据，输入一行两个正整数 $n,k$。
## 输出格式

对于每组测试数据，输出一行一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5
3 2
10 1
261 261
2333 2333
124218 998244353
```
### 样例输出 #1
```
17
134
28873779
470507314
428587718

```
## 提示

**【样例解释】**

对于第 $1$ 组测试数据：

$f(1)=\gcd(1,0)^2=1$。

$f(2)=\gcd(1,3)^2+\gcd(2,0)^2=5$。

$f(3)=\gcd(1,2)^2+\gcd(2,1)^2+\gcd(3,0)^2=11$。

$f(1)+f(2)+f(3)=17$。

**【数据范围】**

对于所有测试数据，$1\le T\le 1000$，$1\le n\le 2\times 10^5$，$\sum n\le 2\times 10^5$，$1\le k\le 10^9$。

**本题采用捆绑测试。**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

- Subtask 1（10 points）：$\sum n\le 2000$。
- Subtask 2（12 points）：$\sum n\le 10^4$。
- Subtask 3（15 points）：$k=1$。
- Subtask 4（45 points）：$\sum n\le 10^5$。
- Subtask 5（18 points）：无特殊限制。


---

---
title: "选择困难症"
layout: "post"
diff: 省选/NOI-
pid: P10895
tag: ['数学', '数论', '洛谷原创', 'O2优化']
---
# 选择困难症
## 题目背景

Parviz 认为，如果一道题有一个可以显著优化复杂度的方法而不去使用，那这题就是有遗憾的。

Alice 认为，任何算法难度大于思维难度的题，出在正式比赛中都是没有意义的。

猫猫认为，ta 是学数学学的。

$\textsf{linyue}$ 认为……啊？你们在说啥？

很有喜剧效果的是这四个名字你可能都没法一下子对上号（
## 题目描述

Alice 与 Bob 在下棋之余，也需要一些娱乐活动来放松身心，比如去小吃街吃饭。作为一名绅士，Bob 每次都让 Alice 选择要去吃哪家。这却让 Alice 犯了难——她有选择困难症。

小吃街有 $n$ 家饭店，在第 $i$ 家就餐需要 $i$ 元钱。如果预算为 $a$ 元，则可以选择前 $a$ 家餐厅。

在长期的纠结后，Alice 想到一种方法：她提前在心里想好一个非负整数 $k< \text{lcm}_{i=1}^{n} i$ ，在得知预算 $a$ 之后，选择在第 $(k$ $\text{mod}$ $a)+1$ 家餐厅就餐。

由于买棋盘与棋子的市场价格浮动，每次就餐的预算未必相同，但都是 $[2,n]$ 之间的整数。Alice 想每次都换换口味，希望对于不同的 $a$，最后选定的餐厅各不相同。她想要知道满足要求的 $k$ 的个数，但又忙于与 Bob 下棋没有时间算，于是只好求助于你啦。

形式化地说，对于给定的 $n$，你需要求有多少个整数 $k \in [0, \text{lcm}_{i=1}^{n}i)$ ，满足 $k\bmod 2,k\bmod3 ,..., k\bmod n$ 各不相同。答案对 $998244353$ 取模。
## 输入格式

第一行一个整数 $T$，表示共有 $T$ 组数据。

接下来 $T$ 行，每行一个整数 $n$ ，含义见题面。
## 输出格式

共 $T$ 行，每行一个整数，表示满足要求的 $k$ 的数量。
## 样例

### 样例输入 #1
```
3
3
4
5
```
### 样例输出 #1
```
4
3
6
```
### 样例输入 #2
```
5
13860108
13850709
220000633
693439571
1004535809
```
### 样例输出 #2
```
188051653
724253523
444803502
370347248
425186012
```
## 提示

**【样例解释1】**

$n=3,4$ 时，$k$ 的取值集合分别为 $\{2, 3, 4, 5\}$ 、 $\{3, 10, 11\}$。

$n=5$ 时：

| $k$ | $k \bmod 2$ | $k \bmod 3$ | $k \bmod 4$ | $k \bmod 5$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $27$ | $1$ | $0$ | $3$ | $2$ |
| $34$ | $0$ | $1$ | $2$ | $4$ |
| $35$ | $1$ | $2$ | $3$ | $0$ |
| $39$ | $1$ | $0$ | $3$ | $4$ |
| $58$ | $0$ | $1$ | $2$ | $3$ |
| $59$ | $1$ | $2$ | $3$ | $4$ |

$\text{lcm}_{i=1}^{n}i=60$，可以验证在 $[0,60)$ 内不存在其他的 $k$ 满足条件，故答案为 $6$。

| 测试点编号 | $T \leq$ | $n \leq$ |
| -----------: | -----------: | -----------: |
| $1-2$ | $15$ | $15$ |
| $3-6$ | $1000$ | $1000$ |
| $7-12$ | $1000$ | $2 \times 10^7$ |
| $13-20$ | $15$ | $2 \times 10^9$ |

对于 $100\%$ 的数据，满足 $3 \leq n \leq 2 \times 10^9$，$ T \leq 1000$。


---

---
title: "「ALFR Round 4」D 罪人的终幕"
layout: "post"
diff: 省选/NOI-
pid: P11014
tag: ['数论', 'Special Judge', 'O2优化', '李超线段树']
---
# 「ALFR Round 4」D 罪人的终幕
## 题目背景

> 而我承诺你，一切都将在一场盛大的，如同戏剧般的审判中结束……  
> 小小地旋转，轻轻地跳跃，然后便是「罪人」的谢幕。
## 题目描述

定义函数 $a(x)$ 表示自然数 $x$ 的不同的质因子的和。

若 $x=\prod\limits_{p_i\in\mathbb{P}}p_i^{d_i}$，则 $a(x)=\sum\limits_{p_i\in \mathbb{P}}p_i\times[d_i\ge1]$，其中 $\mathbb{P}$ 是质数集，$a(1)=0$。

从诞生的第一天开始，Furina 便有了一个期待值 $m_1$。

在最终的审判来临前，她每天都会选择整理自己的心情，具体的方法如下：

假设今天是第 $i$ 天，Furina 会把今天的期待值 $m_i$ 定为 $\max\{\dfrac{m_j}{a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k\}$，其中 $2\le i\le n$，$1\le j<i$，$k$ 是观看审判所获得的期待值。

请你求出 $\sum\limits_{i=1}^nm_i$。
## 输入格式

第一行三个整数 $n,m_1,k$ 分别表示第一天距最终的审判（包括第一天）的天数，第一天的期待值和观看审判能获得的期待值。
 
第二行共 $n$ 个整数表示 $w_1,w_2,w_3,\cdots,w_n$。
## 输出格式

一行一个实数表示 $\sum\limits_{i=1}^nm_i$。**答案与正确答案的绝对误差不超过 $10^{-6}$ 即判为正确**。
## 样例

### 样例输入 #1
```
4 4 7
7 10 16 8
```
### 样例输出 #1
```
28.047619
```
## 提示

### 样例解释

这 $4$ 天的期待值分别是 $4,7.285714,7.809524,8.952381$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $30$ | $n,m_1,k\le10^3$，$w_i\le29$ |
| $1$ | $70$ | - |

对于 $100\%$ 的数据，$1\le n\le182376$，$1\le m_1\le10^7$，$0\le k\le10^6$，$2\le w_i\le182376$。

本题数据可能偏弱，欢迎大家提供对于错误做法的 hack。


---

---
title: "『STA - R8』随机数生成器"
layout: "post"
diff: 省选/NOI-
pid: P11211
tag: ['数学', '数论', '交互题', 'Special Judge', 'O2优化', '中国剩余定理 CRT']
---
# 『STA - R8』随机数生成器
## 题目背景

**Upd on 2024/10/22** 加入一组 Hack 数据（#13）
## 题目描述

**这是一道交互题。**

Lloyd 有一个随机数生成器，对于随机种子 $s$ 和生成器类型 $t$，它第 $x$ 次（$x<p$）生成的随机数是：
$$r_{s,t}(x)=\begin{cases}s^x\bmod p&t=1\\x^s\bmod p&t=2\end{cases}$$
其中 $p$ 是一个固定素数。$0\le s<p-1$。

现在给定 $p,t$。已知随机数生成器在你询问之前已经生成过若干随机数，而在你生成随机数的时候不会有任何其他随机数生成访问（也就是你生成的是一段连续的随机数）。你每次可以调用随机数生成器来获取一个随机数，并且在若干次调用之后找出随机数种子 $s$ 的值。**保证有解且 5 次询问后一定能得到唯一的解。**

***
**实现细节**

本题采用 IO 交互模式。

第一行输入两个正整数 $t,p$。

接下来，可以向交互库发送以下两种操作：
- `?`，表示调用一次随机数生成器，随即你可以从标准输入中读入随机数生成器生成的数值。
- `! s`，报告你发现的 $s$。

发送 `!` 操作后你应该立即结束程序。另外在每一次操作后都需要清空缓冲区。评分方式见数据范围部分。

如果你的操作不符合交互格式可能出现不可预料的结果。保证在交互次数不超过 19930（也就是至少可以获得 1 分）时交互库的运行时间不超过 100ms。对于 19930 之上的交互次数不保证交互库运行时间。
## 输入格式

见题目描述中实现细节部分。
## 输出格式

见题目描述中实现细节部分。
## 样例

### 样例输入 #1
```
1 10007

4960
```
### 样例输出 #1
```

?

! 114
```
### 样例输入 #2
```
2 10007

4960

6980
```
### 样例输出 #2
```

?

?

! 514
```
## 提示

**样例解释**

样例仅供参考，不一定具有实际逻辑。

第一组样例：$p=10007$，$s=114$，在询问之前生成过 $513$ 次随机数。

第二组样例：$p=10007$，$s=514$，在询问之前生成过 $113$ 次随机数。
***

**数据范围**

**本题采用捆绑测试。**（Subtask 分数为 Subtask 内各测试点分数之最小值）

- Subtask 1 (20pts)：$t=1$。
- Subtask 2 (20pts)：$p\le 10^3$。
- Subtask 3 (60pts)：无特殊限制。

对于全部数据，$2\le p\le2\times10^6$ 且 $p$ 是素数，$t\in\{1,2\}$，保证有解。

对于每个测试点，如果你向交互库发送了 $c$ 次 `?` 操作，那么你可以得到的分数由如下表达式给出：
$$\mathrm{score}=\begin{cases}100&c\le 5\\\max\{0,100-\lceil10\ln(c)\rceil\}&\text{otherwise.}\end{cases}$$


---

---
title: "「FAOI-R5」波特检测"
layout: "post"
diff: 省选/NOI-
pid: P11658
tag: ['动态规划 DP', '2025', '洛谷原创', 'O2优化', '矩阵加速', '组合数学', '快速数论变换 NTT', '洛谷比赛']
---
# 「FAOI-R5」波特检测
## 题目背景

正在验证您是否是真人。这可能需要几秒钟时间。
## 题目描述

小 H 是一个 bot，他内置一个序列 $\{A_n\}$ 和一个长度为 $n$ 的 01 串 $H$。询问他一个区间 $[l,r]$，他可以给出一个**集合** $g(l,r)$:
- 设置序列 $\{B_n\}$，对于 $i=1,2,\ldots,n$，执行以下操作：
  - 如果 $H_i=\tt{0}$，$B_i=A_i$（即小 H 不能修改 $A_i$ 的值）；
  - 如果 $H_i=\tt{1}$，可以任意选择一个非负整数 $v$，令 $B_i=v$（即小 H 可以任意修改 $A_i$ 的值，**修改后的值可以不在 $\boldsymbol{[0,2^k-1]}$ 范围内**）。
- $g(l,r)=\{B_l\operatorname{xor}B_{l+1},B_{l+1}\operatorname{xor}B_{l+2},\cdots,B_{r-1}\operatorname{xor}B_{r}\}$。

喵仔牛奶需要对小 H 进行若干次检测，每次选取 $[l,r],[L,R]$ 两个区间，满足 $r\le L$，并向小 H 询问得出 $g(l,r),g(L,R)$。若 $g(l,r)\cap g(L,R)\neq\varnothing$，则检测失败，小 H 的 bot 身份会被发现。

若小 H 存在一种策略可以回答所有可能的询问并不存在检测失败（也就是对于任意满足 $r\le L$ 区间 $[l,r],[L,R]$ 都不会检测失败），我们就称这个 01 串 $H$ 是「可用的」。

给定 $n,k$，序列 $\{A_n\}$ 的每一项都在 $[0,2^k-1]$ 中均匀随机选取。你需要求出「可用的」01 串 $H$ 的个数的期望值。答案对 $998244353$ 取模。
## 输入格式

一行两个非负整数 $n,k$，表示序列长度与值域大小。
## 输出格式

一行一个非负整数，表示「可用的」01 串 $H$ 的个数的期望值对 $998244353$ 取模后的结果。

如果你不知道如何进行有理数取模：
- 令 $M=998244353$。可以证明，答案可以被表示为最简分数 $\frac{p}{q}$，其中 $p$ 和 $q$ 是正整数且 $q\not\equiv 0\pmod M$。你只需要输出一个非负整数 $x\in[0,M)$ 使得 $x\cdot q\equiv p\pmod M$。
- 如果你不知道如何找出所述的 $x$，可以参考 P2613。
## 样例

### 样例输入 #1
```
1 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2 1
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
3 1
```
### 样例输出 #3
```
499122184
```
### 样例输入 #4
```
5 2
```
### 样例输出 #4
```
655097885
```
### 样例输入 #5
```
10 3
```
### 样例输出 #5
```
972670600
```
### 样例输入 #6
```
114 514
```
### 样例输出 #6
```
802524221
```
## 提示

### 样例 1 解释

唯一一种可能的情况是 $A=[0]$，此时 $H=\tt 0$ 和 $H=\tt 1$ 都是「可用的」，故答案为 $2$。

### 样例 2 解释

有以下 $4$ 种可能的情况：

- $A=[0,0]$。
- $A=[0,1]$。
- $A=[1,0]$。
- $A=[1,1]$。

在不修改的情况下，它们都能通过检测（对应的答案均为 $2^2=4$），故答案为 $2^2=4$。

### 样例 3 解释

有以下 $8$ 种可能的情况：
- $A=[0,0,0]$，$H$ 的个数为 $7$。
- $A=[0,0,1]$，$H$ 的个数为 $8$。
- $A=[0,1,0]$，$H$ 的个数为 $7$。
- $A=[0,1,1]$，$H$ 的个数为 $8$。
- $A=[1,0,0]$，$H$ 的个数为 $8$。
- $A=[1,0,1]$，$H$ 的个数为 $7$。
- $A=[1,1,0]$，$H$ 的个数为 $8$。
- $A=[1,1,1]$，$H$ 的个数为 $7$。

当 $A=[0,1,0]$ 时，$H=\tt{000}$ 不是「可用的」。当询问 $[1,2],[2,3]$ 时：
- 小 H 每次只能原封不动地保留 $A$。
- 当询问 $[1,2]$ 时，$g(1,2)=\{1\}$。
- 当询问 $[2,3]$ 时，$g(2,3)=\{1\}$。
- $g(1,2)\cap g(2,3)=\{1\}$，检测失败。

当 $A=[1,1,1]$ 时，$H=\tt{010}$ 是「可用的」。当询问 $[1,2],[2,3]$ 时：
- 小 H 可以任意修改 $A$ 的值，**并且每次询问时修改的值可以不一样**。
- 当询问 $[1,2]$ 时，小 H 令 $B=[1,2,1]$，$g(1,2)=\{3\}$。
- 当询问 $[2,3]$ 时，小 H 令 $B=[1,1,1]$，$g(2,3)=\{0\}$。
- $g(1,2)\cap g(2,3)=\varnothing$，检测成功。

故答案为 $(7\times 4+8\times 4)\times\dfrac{1}{8}=\dfrac{15}{2}$。

注意到 $2\times 499122184\equiv 15\pmod{998244353}$，答案即为 $499122184$。

### 样例 4 解释

答案为 $\dfrac{907}{32}\equiv655097885\pmod{998244353}$。

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n\leq2$。
- Subtask 2（10 pts）：$n\leq 6$，$k\leq 2$。
- Subtask 3（10 pts）：$n\leq 50$，$k\leq6$。
- Subtask 4（10 pts）：$n\leq 500$，$k\leq 20$。
- Subtask 5（20 pts）：$n\leq 2\times10^3$。
- Subtask 6（20 pts）：$n\leq 5\times10^4$。
- Subtask 7（20 pts）：无特殊限制。

对于所有数据，$1\leq n\leq 10^6$，$0\leq k\leq 10^9$。


---

---
title: "[JRKSJ ExR] 淇宝的划分"
layout: "post"
diff: 省选/NOI-
pid: P11694
tag: ['贪心', '2025', '数论', '洛谷原创', 'O2优化']
---
# [JRKSJ ExR] 淇宝的划分
## 题目背景

题目中人名纯属虚构，如有雷同纯属巧合。
## 题目描述

淇宝有一个由正整数构成的大小为 $n$ 的可重集 $A$，他想把这个可重集划分成两部分 $S,T$。具体地，非空可重集 $S,T$ 满足任意正整数 $v$ 在 $S,T$ 中的出现次数之和等于其在 $A$ 中的出现次数。

淇宝作为举世闻名的全世界最年轻获得 LGM（LCM and GCD Master）的选手，计算出了 $\gcd_{v\in S}v$ 和 $\operatorname{lcm}_{v\in T}v$。

现在他希望你求出所有划分方案中，$\lvert(\gcd_{v\in S}v)-(\operatorname{lcm}_{v\in T}v)\rvert$ 的最小值。
## 输入格式

**本题包含多组测试数据。**

第一行一个正整数 $T$ 表示测试数据组数。

对于每组测试数据：

第一行一个正整数 $n$，表示可重集的大小。

第二行 $n$ 个正整数 $a_{1\sim n}$ 表示可重集 $A$ 内的元素。保证 $a_1\leq a_2\leq\dots\leq a_n$。
## 输出格式

对于每组测试数据，输出一行，一个非负整数，表示 $\lvert(\gcd_{v\in S}v)-(\operatorname{lcm}_{v\in T}v)\rvert$ 的最小值。
## 样例

### 样例输入 #1
```
3
4
1 2 3 4
5
3 3 4 5 5
6
4 6 12 13 26 39
```
### 样例输出 #1
```
0
2
1
```
## 提示

### 样例解释

第一组数据的最优解 $S=\{2,3,4\},T=\{1\}$。

第二组数据存在一组最优解 $S=\{4,5,5\},T=\{3,3\}$。

第三组数据的最优解 $S=\{13,26,39\},T=\{4,6,12\}$。

### 数据规模与约定
**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\leq$ | $\sum n\leq$ | $a_i\leq$ | 分数 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $16$ | $100$ | $10^{18}$ | $6$ |
| $2$ | $300$ | $3\times10^3$ | $100$ | $19$ |
| $3$ | $2\times10^4$ | $2\times10^5$ | $10^6$ | $13$ |
| $4$ | $2\times10^4$ | $2\times10^5$ | $10^9$ | $15$ |
| $5$ | $2\times10^5$ | $2\times10^6$ | $10^9$ | $22$ |
| $6$ | $10^6$ | $5\times10^6$ | $10^{18}$ | $25$ |

对于所有数据，$1\leq T\leq10^4$，$2\leq n\leq10^6$，$\sum n\leq5\times10^6$，$1\leq a_i\leq10^{18}$，$a_1\leq \dots\leq a_n$。

**部分数据点输入数据较大，请使用较为快速的读入方式。**


---

---
title: "报社天狗"
layout: "post"
diff: 省选/NOI-
pid: P11772
tag: ['数论', '洛谷原创', 'O2优化', '分块', '洛谷月赛', '整除分块']
---
# 报社天狗
## 题目背景

因为天依想不到新歌歌词怎么写破防了，所以这题的主人公不是天依。
## 题目描述

新一期《文文。新闻》开售了！

$n$ 只$^\dag$妖怪排队购买《文文。新闻》，将她们依次编号 $1\sim n$，每一只妖怪会购买若干份。然而，她们购买《文文。新闻》并不是为了阅读，而是是为了送给所有编号是自己倍数的的妖怪一份（自己可以不留）。也就是说，对于 $1\sim n$ 的每只妖怪，依次进行：当手上的《文文。新闻》数量足够时，不进行购买，直接赠送；而不够时便会先向文文购买至刚好足够，再进行赠送。

文文为了使收益最大化，为每只妖怪详细制定了价格方案。具体地，第 $i$ 只妖怪在已有 $j$ 份《文文。新闻》时再买一份花费的价钱是 $a_i\times b_{j+1}$，其中 $a,b$ 是两个从 $1$ 开始的长为 $10^6+1$ 的正整数序列。

现在文文需要一个合理的定价方案，她决定从 $a,b$ 全为 $1$ 时开始调整。具体地，有以下三种操作：

- `1 x` 询问以当前的 $a,b$ 数组，$n=x$ 时文文能有多少营业额，因为结果可能很大，你需要求出答案对 $2^{32}$ 取模后的结果。
- `2 x y` 适当地调整 $a$ 数组的值：令 $a_x=y$；
- `3 x y` 适当地调整 $b$ 数组的值：令 $b_x=y$。

$\dag$：经查证，量词为『只』和『个』的情况均有出现，THBwiki 中『一只妖怪』的匹配量显著多于『一个妖怪』，于是本题中采用『只』，并不是出题人的种族歧视。
## 输入格式

第一行一个整数 $T$ 表示操作的数量。

第 $2\sim T+1$ 行，每行 $2$ 或 $3$ 个整数，表示题目中的一次操作。
## 输出格式

每行一个整数，表示每次询问的获利对 $2^{32}$ 取模后的结果。
## 样例

### 样例输入 #1
```
5
1 5
2 2 5
3 1 3
1 5
1 6
```
### 样例输出 #1
```
4
6
12
```
## 提示

### 样例解释

第一个询问中，$n=5$，两个序列中所有的元素均为 $1$。$1$ 号妖怪买了 $4$ 份报纸，每份报纸的收益都是 $1$，其他的妖怪都没有买报纸，总收益为 $4$。

第二个询问中，有 $n=5,a_2=3,b_1=5$，序列中其他元素均为 $1$。$1$ 号妖怪买了 $4$ 份报纸，其中第 $1$ 份报纸的收益是 $3$，第 $2$ 份到第 $4$ 份报纸的收益都是 $1$，其他的妖怪都没有买报纸，总收益为 $6$。

第三个询问中，有 $n=6,a_2=3,b_1=5$，序列中其他元素均为 $1$。让我们具体来看看这次询问中的过程：

+ $1$ 号妖怪需要送其他每个妖怪各一份报纸，但是她没有报纸。于是她需要买 $5$ 份报纸。其中第一份报纸的收益是 $a_1\times b_1=3$，第 $2$ 份到第 $5$ 份报纸的收益都是 $1$。然后她给了其他每个妖怪各一份报纸。

+ $2$ 号妖怪需要送 $4$ 号妖怪和 $6$ 号妖怪各一份报纸，她已经从 $1$ 号妖怪手中获得了一份报纸。于是她还需要买 $1$ 份报纸，这份报纸的收益是 $a_2\times b_2=5$。

+ $3$ 号妖怪需要送 $6$ 号妖怪一份报纸，她已经从 $1$ 号妖怪手中获得了一份报纸，不需要再买报纸。

+ $4$ 号妖怪到 $6$ 号妖怪都不需要送出报纸，也不需要再买报纸。

总收益为 $12$。

### 数据规模与约定

**本题采用捆绑测试。** 仅当你通过了该子任务的全部测试数据才能获得该子任务的分值。

对于 $100\%$ 的数据，$1 \leq T \leq 10^5$，$1 \leq x,n\leq 10^6$，$1\le y\le 10^9$。

对于不同的子任务，作如下约定：

| 子任务编号 |  特殊性质                  | 子任务分值 |
| :-----: | :----------------------------------: | :----: |
|    $1$    |      没有修改操作                      | $10$ |
|    $2$    | 第一种操作中的每个 $n$ 都相等 | $20$ |
|    $3$    |    $n,T \leq 10^5$                   | $30$ |
|    $4$    | 无 | $40$ |


---

---
title: "「Stoi2025」爱的飞行日记"
layout: "post"
diff: 省选/NOI-
pid: P11888
tag: ['2025', '数论', 'O2优化', '莫比乌斯反演', '容斥原理', '逆元', '洛谷比赛', '整除分块', 'Dirichlet 卷积', '筛法']
---
# 「Stoi2025」爱的飞行日记
## 题目背景

![](bilibili:BV1fx411N7bU?page=125)
## 题目描述

$t$ 组询问，每次询问给定正整数 $n,m$，计算

$$\prod_{a_1=1}^{m}\prod_{a_2=1}^{m}\cdots\prod_{a_n=1}^{m}\operatorname{lcm}(f_{a_1},f_{a_2},\dots,f_{a_n})\bmod{37426667}$$

的值。其中 $f_i$ 是斐波那契数，满足 $f_1=f_2=1$，且 $f_i=f_{i-1}+f_{i-2},\forall n\ge3$。
## 输入格式

第一行输入一个正整数 $t$ 表示询问组数。

接下来 $t$ 行，每行两个正整数 $n,m$ 表示一次询问。
## 输出格式

每次询问输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2
1 3
2 3

```
### 样例输出 #1
```
2
32

```
## 提示

#### 样例解释

对于第一组询问，有答案为 $f_1f_2f_3=1\times1\times2=2$。

对于第二组询问，当 $a_1,a_2\in\{1,2\}$ 时 $\operatorname{lcm}(f_{a_1},f_{a_2})=1$，否则 $\operatorname{lcm}(f_{a_1},f_{a_2})=2$。故答案为 $2^5=32$。

#### 数据范围与限制

**本题采用捆绑测试，各 Subtask 的限制与分值如下。**

| Subtask No. | $t\le$ | $n\le$ | $m\le$ | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $1$ | $2$ | $2 \times 10^3$ | $13$ |
| $2$ | $5$ | $2 \times 10^5$ | $2 \times 10^5$ | $24$ |
| $3$ | $5$ | $2 \times 10^7$ | $2 \times 10^7$ | $36$ |
| $4$ | $300$ | $2 \times 10^{17}$ | $2 \times 10^7$ | $27$ |

对于所有数据，满足 $1 \le t \le 300, 1 \le n \le 2 \times 10^{17}, 1 \le m \le 2 \times 10^7$。


---

---
title: "「ZHQOI R1」幂和"
layout: "post"
diff: 省选/NOI-
pid: P11957
tag: ['数学', 'O2优化', '快速数论变换 NTT', '洛谷比赛']
---
# 「ZHQOI R1」幂和
## 题目描述

给定 $n,x,k$，求下列式子的值：
$$
\sum_{i=0}^n (-1)^{\operatorname{popcnt}(i)} (i+x)^k
$$
答案对 $998244353$ 取模。

特殊地，定义 $0^0=1$。

函数 $\operatorname{popcnt}(x)$ 表示 $x$ 在二进制表示下 $1$ 的个数。
## 输入格式

一行，三个整数 $n,x,k$。
## 输出格式

输出一个数表示答案。
## 样例

### 样例输入 #1
```
5 5 2
```
### 样例输出 #1
```
23
```
### 样例输入 #2
```
12345678 1919810 11451
```
### 样例输出 #2
```
69157901
```
### 样例输入 #3
```
999999999999 125432670 1000
```
### 样例输出 #3
```
154496571
```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据：$0\le n\le 10^{12},0\le x\le 10^9,0\le k\le 10^5$。

| 子任务编号 | $n\le $        | $k\le $ | 分数 |
| :----------: | :--------------: | :-------: | :----: |
| 1          | $10^6$         | $10^5$  | $7$  |
| 2          | $10^8$ | $10^5$  | $8$  |
| 3          | $10^{12}$          | $0$     | $5$  |
| 4          | $10^{12}$          | $1$     | $10$ |
| 5          | $10^{12}$          | $2$     | $10$ |
| 6          | $10^{12}$          | $100$   | $10$ |
| 7          | $10^{12}$          | $10^3$  | $15$ |
| 8          | $10^{12}$          | $10^4$  | $15$ |
| 9          | $10^{12}$          | $10^5$  | $20$ |


---

---
title: "【MX-X10-T6】[LSOT-4] 集合"
layout: "post"
diff: 省选/NOI-
pid: P12010
tag: ['数学', '数论', '中国剩余定理 CRT', 'Lucas 定理', '梦熊比赛']
---
# 【MX-X10-T6】[LSOT-4] 集合
## 题目描述

记全集为 $U$。

定义一个操作方案为对每个非空集合 $S \subseteq U$ 选择 $S$ 中任意一个元素作为 $S$ 的代表元，记为 $r(S)$。

一种操作方案是好的当且仅当对任意非空集合 $S \subseteq U$，满足对于任意将其划分为 $m$ 个非空子集的方案 $A_1, A_2, \ldots, A_m$，$\exists 1 \le i \le m, r(A_i) = r(S)$。

求 $U=\{1, 2, \ldots, n\}$ 时的本质不同的好的操作方案数，将答案对 $1000000087$ 取模。

两个操作方案是本质不同的，当且仅当存在某个非空集合 $S 
\subseteq U$，使得 $r(S)$ 在两个操作方案中不同。

## 输入格式

仅一行，两个正整数 $n, m$。

## 输出格式

仅一行，一个整数，表示方案数对 $1000000087$ 取模的结果。
## 样例

### 样例输入 #1
```
3 1

```
### 样例输出 #1
```
24

```
### 样例输入 #2
```
3 2

```
### 样例输出 #2
```
6

```
### 样例输入 #3
```
4 3

```
### 样例输出 #3
```
2592

```
### 样例输入 #4
```
114514 3

```
### 样例输出 #4
```
750017326

```
### 样例输入 #5
```
114514 19198

```
### 样例输出 #5
```
274658403

```
## 提示

**【样例解释 #1】**

所有方案都是好的，所以答案为 $1^3 \times 2^3 \times 3 = 24$。

**【样例解释 #2】**

$6$ 种方案分别为：

$r(\{1, 2, 3\}) = 1$，$ r(\{1, 2\}) = 1$，$ r(\{1, 3\}) = 1$，$ r(\{2, 3\}) = 2$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$；

$r(\{1, 2, 3\}) = 1$，$ r(\{1, 2\}) = 1$，$ r(\{1, 3\}) = 1$，$ r(\{2, 3\}) = 3$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$；

$r(\{1, 2, 3\}) = 2$，$ r(\{1, 2\}) = 2$，$ r(\{1, 3\}) = 1$，$ r(\{2, 3\}) = 2$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$；

$r(\{1, 2, 3\}) = 2$，$ r(\{1, 2\}) = 2$，$ r(\{1, 3\}) = 3$，$ r(\{2, 3\}) = 2$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$；

$r(\{1, 2, 3\}) = 3$，$ r(\{1, 2\}) = 1$，$ r(\{1, 3\}) = 3$，$ r(\{2, 3\}) = 3$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$；

$r(\{1, 2, 3\}) = 3$，$ r(\{1, 2\}) = 2$，$ r(\{1, 3\}) = 3$，$ r(\{2, 3\}) = 3$，$ r(\{1\}) = 1$，$ r(\{2\}) = 2$，$ r(\{3\}) = 3$。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（5 分）：$m = 2$。
- 子任务 2（6 分）：$n \le 4$。
- 子任务 3（10 分）：$n \le 3 \times 10^3$。
- 子任务 4（18 分）：$m = 1$。
- 子任务 5（26 分）：$m \le 3 \times 10^3$。
- 子任务 6（35 分）：无特殊限制。

对于全部的数据，$1 \le m < n \le 2 \times 10^5$。


---

---
title: "[蓝桥杯 2023 国 Java A] 游戏的得分"
layout: "post"
diff: 省选/NOI-
pid: P12239
tag: ['2023', '数论', '蓝桥杯国赛', '大步小步算法 BSGS']
---
# [蓝桥杯 2023 国 Java A] 游戏的得分
## 题目描述

小蓝和小乔正在玩游戏，一开始双方分数均为 $1$，每局游戏都有多个轮次。游戏的每轮总有一个人获胜/失败，其中获胜者分数变为原来的 $4$ 倍，失败者分数变为原来的 $2$ 倍。小蓝和小乔玩了很多局游戏，它们记下了每局游戏最终的分数对 $998\,244\,353$ 取模的结果，但他们忘记了每局游戏进行的轮次数。

请输出每局游戏中要得到给定的结果所需的最少轮次数。特别地，如果小蓝和小乔记错了游戏的结果，也就是无论如何也得不到输入的分数，请输出 $-1$。
## 输入格式

输入的第一行包含一个整数 $T$ 表示游戏局数。

接下来 $T$ 行，每行包含两个整数 $a_i$，$b_i$ 分别表示小蓝和小乔在第 $i$ 局游戏的记录。

## 输出格式

输出 $T$ 行，每行包含一个整数，其中第 $i$ 行的整数表示得到第 $i$ 局游戏给定结果所需的最少轮次数。
## 样例

### 样例输入 #1
```
4
4 2
6 3
8 8
1 2
```
### 样例输出 #1
```
1
-1
2
665496235
```
## 提示

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$T \leq 5$；
- 对于 $40\%$ 的评测用例，$T \leq 2000$；
- 对于所有评测用例，$1 \leq T \leq 10^5$，$1 \leq a_i, b_i < 998244353$。


---

---
title: "调和级数求和 2"
layout: "post"
diff: 省选/NOI-
pid: P12390
tag: ['数论', 'O2优化', 'Stirling 数']
---
# 调和级数求和 2
## 题目背景

前情提要：[调和级数求和](https://www.luogu.com.cn/problem/P5702)。←注意，解决这道题目对于解决本题可能并不会有什么帮助。
## 题目描述

给定正整数 $n,p,k$。定义 $\operatorname{inv}(x,p^k)$ 是满足 $ax\equiv 1\pmod{p^k}$ 的小于 $p^k$ 的非负整数 $a$，如果不存在这样的 $a$ 则 $\operatorname{inv}(x,p^k)=0$。可以证明，如果存在这样的 $a$，那么它是唯一的。

现在，你需要求出下式的值：
$$\sum_{i=1}^n\operatorname{inv}(i,p^k)$$
由于答案可能很大，所以需要对 $p^k$ 取模。

**注意此处 $\bm p$ 不一定是质数。**
## 输入格式

一行三个正整数 $n,p,k$。
## 输出格式

一行一个正整数，表示欲求式子的值。答案对 $p^k$ 取模。
## 样例

### 样例输入 #1
```
4 3 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
123456 78 9
```
### 样例输出 #2
```
37527411787678151
```
### 样例输入 #3
```
142857142857142857 2 59
```
### 样例输出 #3
```
573170602055236649
```
## 提示

**本题采用捆绑测试。**

- Subtask 1 (10pts)：$k=1$。
- Subtask 2 (40pts)：$\frac np\le 10^4$。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，有 $1\le n\le 10^{18}$，$2\le p\le 10^6$，$p^k\le 10^{18}$。




---

---
title: "[Math×Girl] 互质与整除"
layout: "post"
diff: 省选/NOI-
pid: P12470
tag: ['多项式', '数论', 'O2优化', '背包 DP', '生成函数', 'Dirichlet 卷积', '欧拉函数']
---
# [Math×Girl] 互质与整除
## 题目背景

>“还可以连接一个东西。”米尔嘉说，“$1$ 的原始 $n$ 次方根的个数是欧拉老师 $\varphi$ 函数的值。函数 $\varphi(n)$ 在 $1\le k<n$ 的范围内表示与 $n$ 互质的自然数的个数，也表示循环群的生成元的个数。”米尔嘉像是描绘 $\varphi$ 似地挥动手指，“最喜欢互质的尤里不在这里真可惜，今天你怎么没带她来？”  
>米尔嘉瞪我。

“互质？”米尔嘉看着窗外说，“我们来做道有趣的题吧！”  
## 题目描述

给定一个数 $n$，求出满足以下方程的 $x$ 的个数。
$$\varphi(x)\mid n$$

其中 $\mid$ 为整除符号，$a\mid b$ 表示 $a$ 整除 $b$。  
$\varphi(x)$ 为欧拉 $\varphi$ 函数，详见题目背景。
## 输入格式

本题有多组数据，第一行输入一个整数 $T$，表示数据组数。  

_米尔嘉已经帮你实现了 Pollard-Rho 算法，_  
所以输入给出的是 $n$ 的标准质因子分解形式 $n=\prod_{i=1}^s p_i^{\alpha_i}$。

对于每一组询问，我们首先给出一个整数 $s$。  
后面 $s$ 行每行两个整数表示 $p_i,\alpha_i$，保证 $p_i<p_{i+1}$。
## 输出格式

对于每组数据，一行输出一个数表示解的个数。  

_为了节约你的时间，米尔嘉已经封装好了 modint 以进行中国剩余定理合并答案。_  
所以输出对 $998244353$ 取模后的结果即可。  
## 样例

### 样例输入 #1
```
3
1
2 3
3
2 3
11 1
23 1
6
2 1
3 2
5 1
7 1
101 2
178187 1
```
### 样例输出 #1
```
14
53
53
```
## 提示

### 样例解释

质因数分解前 $n$ 分别为：  
$8,2024,1145141919810$

第一个例子中的 $14$ 个解是：  
$\varphi(15)=\varphi(16)=\varphi(20)=\varphi(24)=\varphi(30)=8\mid 8$  
$\varphi(5)=\varphi(8)=\varphi(10)=\varphi(12)=4\mid 8$  
$\varphi(3)=\varphi(4)=\varphi(6)=2\mid 8$  
$\varphi(1)=\varphi(2)=1\mid 8$

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $n\in[1,10^7]$ |
| $1$ | $10$ | $n\in[1,10^9]$ |
| $2$ | $20$ | $n\in[1,10^{12}]$ |
| $3$ | $20$ | $n\in[1,10^{14}]$ |
| $4$ | $20$ | $n\in[1,10^{16}]$ |
| $5$ | $20$ | - |

对于 $100\%$ 数据，保证 $T=5$，$n\in[1,10^{18}],s\ge 1$。 


---

---
title: "回报"
layout: "post"
diff: 省选/NOI-
pid: P12735
tag: ['2025', '洛谷原创', '组合数学', '容斥原理', '快速数论变换 NTT', '洛谷月赛']
---
# 回报
## 题目背景

> 在我看来，得到太多的人明明是我，反倒是我该思考怎么回报才对。\
——浅村悠太
## 题目描述

悠太需要帮沙季找到合适的学习用音乐。

他找到了一个包含 $n$ 首音乐的专辑，其中的音乐编号为从 $1$ 至 $n$，播放每首音乐均需要 $1$ 分钟。沙季有 A 和 B 两门需要学的课程，每次学习 A 和 B 分别需要花 $a,b$ 分钟。为了更好地帮助她，悠太打算将音乐的播放顺序重新排列。具体地，他要选择一个长为 $n$ 的排列 $p_1,\dots,p_n$，使得其中存在两个长度分别为 $a,b$ 的循环 $A,B$，且 $A$ 中的任意一个元素小于 $B$ 中的任意一个元素。

排列中的一个长为 $k$ 的循环 $C$ 是一个由不同整数组成的序列 $c_1,\dots,c_k$，满足 $1\le c_1\le n$，$c_{i+1}=p_{c_i},i=1,\dots,k-1$，且 $p_{c_k}=c_1$。

悠太想要求出有多少满足要求的排列 $p$。由于答案可能很大，你只需要告诉他答案对 $998244353$ 取模的结果。
## 输入格式

输入一行三个整数表示序列长度 $n$ 与 $a,b$。
## 输出格式

输出一行一个整数，表示满足要求的排列的数量取模 $998244353$ 的结果。
## 样例

### 样例输入 #1
```
4 2 1

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
678 12 34

```
### 样例输出 #2
```
951781526

```
### 样例输入 #3
```
1987 654 321

```
### 样例输出 #3
```
27905503

```
### 样例输入 #4
```
1000000 13 20

```
### 样例输出 #4
```
912829543

```
## 提示

#### 样例 1 解释

满足要求的排列有 $(2,1,3,4),(3,2,1,4),(1,3,2,4)$，共 $3$ 个。

#### 数据范围与限制

**本题采用捆绑测试，各 Subtask 的限制与分值如下。**

| Subtask No. | $n\le$ | 特殊性质 | 分值 | 依赖子任务 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $10$ | 有 | $7$ |  |
| $2$ | $700$ | 有 | $10$ | $1$ |
| $3$ | $700$ | 无 | $20$ | $1,2$ |
| $4$ | $2000$ | 有 | $10$ | $1,2$ |
| $5$ | $2000$ | 无 | $30$ | $1,2,3,4$ |
| $6$ | $10^6$ | 有 | $20$ | $1,2,4$ |
| $7$ | $10^6$ | 无 | $3$ | $1,2,3,4,5,6$ |

特殊性质：$\min(a,b)=1$。

对于所有数据，$1\le n\le10^6$，$1\le a,b<a+b\le n$。


---

---
title: "[POI 2018 R3] 多项式 Polynomial"
layout: "post"
diff: 省选/NOI-
pid: P12771
tag: ['2018', 'POI（波兰）', 'Special Judge', '快速数论变换 NTT']
---
# [POI 2018 R3] 多项式 Polynomial
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5079)。
## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi25-3/dashboard/) [Wielomian](https://szkopul.edu.pl/problemset/problem/9JvSAnyf5d1FlPAEXEdUAtCz/statement/)**

Bajtazar 在数学课上行为不端，作为惩罚，他需计算一个具有 $n$ 个整数系数的长多项式 $W$：

$$
W(x) = a_0 + a_1 x + a_2 x^2 + \ldots + a_{n-2} x^{n-2} + a_{n-1} x^{n-1}
$$

在点 $q^1, q^2, \ldots, q^n$ 处的取值。为便于老师检查，他需先给出这些取值之和除以 $m$ 的余数，再给出各取值除以 $m$ 的余数。

Bajtazar 不仅调皮，还很懒惰，他请你帮忙，自己却跑去派对了。临走前，他提醒你：$n$ 是 $2$ 的幂，且 $q^n$ 除以 $m$ 的余数为 $1$（即 $q^n \bmod m = 1$）。他认为这些性质可大幅减少计算量。
## 输入格式

第一行包含三个整数 $n, m, q$（$n \geq 1$，$n$ 为 $2$ 的幂，$2 \leq m \leq 10^9$，$1 \leq q < m$，$q^n \bmod m = 1$）。

第二行包含 $n$ 个整数 $a_0, a_1, \ldots, a_{n-1}$ $(0 \leq a_i \leq 10^9)$，表示多项式系数。
## 输出格式

第一行输出一个整数，表示多项式 $W$ 在点 $q^1, q^2, \ldots, q^n$ 的取值之和除以 $m$ 的余数。

第二行输出 $n$ 个整数，表示 $W(q^1), W(q^2), \ldots, W(q^n)$ 除以 $m$ 的余数，空格分隔。
## 样例

### 样例输入 #1
```
4 13 5
3 2 2 1
```
### 样例输出 #1
```
12
6 2 9 8
```
## 提示

**样例 1 解释**

多项式为 $W(x) = 3 + 2x + 2x^2 + x^3$，其在各点取值为 $W(5) = 188$，$W(5^2) = 16928$，$W(5^3) = 1984628$，$W(5^4) = 244923128$。第一行输出 $188 + 16928 + 1984628 + 244923128 = 246924872$ 除以 $13$ 的余数，即 $12$。第二行输出各取值除以 $13$ 的余数：$188 \bmod 13 = 6$，$16928 \bmod 13 = 2$，$1984628 \bmod 13 = 9$，$244923128 \bmod 13 = 8$。

**附加样例**

1. $n=8, m=10, q=3$。
2. $n=256, m=10, q=9$。
3. $n=2^{13}, m=17, q=6$。
4. $n=2^{20}, m=1114129, q=2$。

若和正确但某取值错误，程序可获得 $40\%$ 的分数，且第二行需输出 $n$ 个 $[0, m-1]$ 范围的数。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 2^{10}$          | $17$ |
| $2$    | $n \leq 2^{15}$          | $9$  |
| $3$    | $n \leq 2^{20}$          | $74$ |


---

---
title: "[GCJ 2021 Finals] Divisible Divisions"
layout: "post"
diff: 省选/NOI-
pid: P13046
tag: ['动态规划 DP', '数学', '2021', '数论', '中国剩余定理 CRT', 'Google Code Jam']
---
# [GCJ 2021 Finals] Divisible Divisions
## 题目描述

We have a string $\mathbf{S}$ consisting of decimal digits. A division of $\mathbf{S}$ is created by dividing $\mathbf{S}$ into contiguous substrings. For example, if $\mathbf{S}$ is 0145217, two possible divisions are 014 5 21 7 and 0 14 52 17. Each digit must be used in exactly one substring, and each substring must be non-empty. If $\mathbf{S}$ has $L$ digits, then there are exactly $2^{L-1}$ possible divisions of it.

Given a positive integer $\mathbf{D}$, a division of $\mathbf{S}$ is called divisible by $\mathbf{D}$ if for every pair of consecutive substrings, at least one of the integers they represent in base 10 is divisible by $\mathbf{D}$. If $\mathbf{D}=7$, the first example division above is divisible because 014, 21, and 7 represent integers divisible by 7. The second example division is not divisible because 52 and 17 are consecutive substrings and neither represents an integer divisible by 7. Dividing 0145217 as 0145217 is divisible by any $\mathbf{D}$ because there are no pairs of consecutive substrings.

Given $\mathbf{S}$ and $\mathbf{D}$, count how many divisions of $\mathbf{S}$ exist that are divisible by $\mathbf{D}$. Since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^{9}+7$ ($1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow. Each line represents a test case with a string of digits $\mathbf{S}$ and a positive integer $\mathbf{D}$, as mentioned above.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of different divisions of $\mathbf{S}$ that are divisible by $\mathbf{D}$, modulo the prime $10^{9}+7$ ($1000000007$).
## 样例

### 样例输入 #1
```
3
0145217 7
100100 10
5555 12
```
### 样例输出 #1
```
Case #1: 16
Case #2: 30
Case #3: 1
```
## 提示

**Sample Explanation**

In Sample Case #1, all $16$ divisible divisions of $\mathbf{S}$ are:

- 0145217,
- 0 145217,
- 0 14 5217,
- 0 14 5 217,
- 0 14 5 21 7,
- 0 14 521 7,
- 0 145 217,
- 0 145 21 7,
- 0 14521 7,
- 014 5217,
- 014 5 217,
- 014 5 21 7,
- 014 521 7,
- 0145 217,
- 0145 21 7, and
- 014521 7.

In Sample Case #2, there are $2^{5}=32$ ways to divide in total. To get two consecutive substrings to not be divisible by 10, we need both of them to not end in 0. The only 2 ways of doing that are $1 \ 001 \ 00$ and $1 \ 001 \ 0 \ 0$, which means the other 30 divisions of $\mathbf{S}$ are divisible by 10.

In Sample Case #3, no possible substring represents an even integer, which in turn means it is not divisible by 12. Therefore, the only way to not have two consecutive substrings that are not divisible by 12 is to not have two consecutive substrings at all, which can be done in only 1 way: 5555.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{D} \leq 10^{6}$.

**Test Set 1 (10 Pts, Visible Verdict)**

- $1 \leq$ the length of $\mathbf{S} \leq 1000$.

**Test Set 2 (35 Pts, Hidden Verdict)**

- $1 \leq$ the length of $\mathbf{S} \leq 10^{5}$.


---

---
title: "Mivik 写书"
layout: "post"
diff: 省选/NOI-
pid: P1316
tag: ['字符串', '枚举', '容斥原理', '快速数论变换 NTT']
---
# Mivik 写书
## 题目背景

Mivik 想当大作家。
## 题目描述

Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。由于 Mivik 不会写文章，所以他只好**等概率**随机乱按了 $n$ 个键，打出了一篇文章。

Mivik 定义一篇文章的复杂度是这篇文章所有**非空**本质不同子串的数目。我们认为两个字符串本质不同当且仅当它们的长度不同或者它们有任意一位上的字符不同。例如，文章 `abaa` 的复杂度是 8，因为它一共有 `a`、`b`、`ab`、`ba`、`aa`、`aba`、`baa`、`abaa` 这 8 个非空的本质不同子串。

Mivik 现在想知道，这篇文章期望的复杂度是多少。由于 Mivik 不喜欢奇形怪状的小数，你只需要输出期望的复杂度对 $10^9+7$ 取模后的值。
## 输入格式

一行两个整数 $n$ 和 $m$，意义见题目描述。
## 输出格式

一行一个整数，代表答案对 $10^9+7$ 取模后的值。
## 样例

### 样例输入 #1
```
2 2
```
### 样例输出 #1
```
500000006
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
3 4
```
### 样例输出 #3
```
250000007
```
## 提示

### 样例解释

样例一：假设键盘上的字符分别为 `a` 和 `b`，那么可能打出来的文章一共有 `aa`、`ab`、`ba`、`bb` 四种，它们的复杂度分别为 2、3、3、2，因此答案为 $\frac{2+3+3+2}{4}=\frac{5}{2}$，对 $10^9+7$ 取模后得到 500000006。

### 数据范围

对于全部数据，有 $1\le n\le 20$，$1\le m\le 5\cdot 10^6$。

Subtask 1 (10 pts)：满足 $1\le n, m\le 7$。

Subtask 2 (20 pts)：满足 $1\le n\le 5$。

Subtask 3 (20 pts)：满足 $1\le n\le 10$。

Subtask 4 (50 pts)：无特殊限制。


---

---
title: "[GCJ 2016 Finals] Gallery of Pillars"
layout: "post"
diff: 省选/NOI-
pid: P13208
tag: ['2016', '数论', '莫比乌斯反演', '容斥原理', 'Google Code Jam']
---
# [GCJ 2016 Finals] Gallery of Pillars
## 题目描述

Your friend Cody-Jamal is working on his new artistic installment called "Gallery of Pillars". The installment is to be exhibited in a square gallery of $\mathbf{N}$ by $\mathbf{N}$ meters. The gallery is divided into $\mathbf{N}^{2}$ squares of 1 by 1 meter, forming an $\mathbf{N}$ by $\mathbf{N}$ matrix. The exact center of the southwest corner cell is called the viewpoint; a person viewing the artwork is supposed to stand there. Each other cell contains a cylindrical pillar. All pillars have two circular bases of radius $\mathbf{R}$: one resting on the floor, in the center of its corresponding cell, and the other touching the gallery's ceiling. The observer will stand in the viewpoint, observe the $\mathbf{N}^{2} - 1$ pillars, and marvel.

Cody-Jamal is currently scouting venues trying to see how large he can make the value of $\mathbf{N}$. Also, he has not decided which material the pillars will be made of; it could be concrete, or carbon nanotubes, so the radius $\mathbf{R}$ of the base of each pillar could vary from 1 micrometer to almost half a meter. Notice that a radius of half a meter would make neighboring pillars touch.

You, as a trained mathematician, quickly observe that there could be pillars impossible to see from the viewpoint. Cody-Jamal asks your help in determining, for different combinations of $\mathbf{N}$ and $\mathbf{R}$, the number of visible pillars. Formally, a pillar is visible if and only if there is a straight line segment that runs from the center of the southwest corner cell (the viewpoint) to any point on the pillar's boundary, and does not touch or intersect any other pillar.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow. Each line describes a different test case with two integers $\mathbf{N}$ and $\mathbf{R}$. $\mathbf{N}$ is the number of 1 meter square cells along either dimension of the gallery, and $\mathbf{R}$ is the radius of each pillar, in micrometers. Thus, $\mathbf{R} / 10^{6}$ is the radius of each pillar in meters.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of pillars in the installment that are visible from the viewpoint.
## 样例

### 样例输入 #1
```
4
4 100000
4 300000
3 300000
100 499999
```
### 样例输出 #1
```
Case #1: 9
Case #2: 7
Case #3: 5
Case #4: 3
```
## 提示

**Sample Explanation**

The pictures below illustrate the first two samples (not to scale). In the center of the black circle is the observer. The other circles are pillars, with the visible ones in gray and the not visible ones in red. The blue dotted lines represent some of the unblocked lines of sight; the red dotted lines represent blocked lines of sight (that turn gray at the point at which they are first blocked).

![](https://cdn.luogu.com.cn/upload/image_hosting/kz9mmqav.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/zbn7wv7d.png)

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{R} < 10^{6} / 2$.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leqslant \mathbf{N} \leqslant 300$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $2 \leqslant \mathbf{N} \leqslant 10^{9}$.


---

---
title: "[GCJ 2011 #3] Mystery Square"
layout: "post"
diff: 省选/NOI-
pid: P13381
tag: ['数学', '2011', '数论', 'Google Code Jam']
---
# [GCJ 2011 #3] Mystery Square
## 题目描述

I have written down a large perfect square in binary, and then replaced some of the digits with question marks. Can you figure out what my original number was?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, one per line. Each line contains $S$: a perfect square written in binary, but with some of the digits replaced by question marks.

## 输出格式

For each test case, output one line containing "Case #$x$: $N$", where $x$ is the case number (starting from 1) and $N$ is a perfect square written in binary, obtained by replacing each '?' character in $S$ with either a '0' character or a '1' character.
## 样例

### 样例输入 #1
```
3
1???
1
10??110??00??1000??
```
### 样例输出 #1
```
Case #1: 1001
Case #2: 1
Case #3: 1011110110000100001
```
## 提示

**Limits**

- $1 \leq T \leq 25$.
- $S$ begins with '1'.
- $S$ contains only the characters '0', '1', and '?'.
- In every test case, there is exactly one possible choice for $N$.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $S$ is at most $60$ characters long.
- $S$ contains at most $20$ '?' characters.
- Time limit: ~~30~~ 6 seconds.

**Large dataset (31 Pts, Test set 2 - Hidden)**

- $S$ is at most $125$ characters long.
- $S$ contains at most $40$ '?' characters.
- Time limit: ~~60~~ 20 seconds.


---

---
title: "[CCPC 2024 重庆站] 乘积，欧拉函数，求和"
layout: "post"
diff: 省选/NOI-
pid: P13568
tag: ['重庆', '2024', '数论', '容斥原理', 'XCPC', '欧拉函数']
---
# [CCPC 2024 重庆站] 乘积，欧拉函数，求和
## 题目背景

本题目来自仓库 https://github.com/Disposrestfully/CCPC-CQ-2024/tree/main
## 题目描述

给定 $n$ 个数 $a_1,a_2,\cdots,a_n$，你需要求以下式子的值：

$$\sum_{S \subseteq \{1,2,\cdots,n\}} \varphi \left(\prod_{i \in S} a_i\right).$$

其中 $\varphi$ 为欧拉函数，$\varphi(x)$ 表示在 $[1,x]$ 内与 $x$ 互质的整数数量，例如

- $\varphi(6) = 2$，因为在 $[1,6]$ 内有 $1$ 和 $5$ 与 $6$ 互质。
- $\varphi(1) = 1$，因为在 $[1,1]$ 内有 $1$ 与 $1$ 互质。

另外，我们定义 $\prod_{i \in \varnothing} a_i = 1$。

答案可能很大，你需要求出其对质数 $998244353$ 取模的结果。

## 输入格式

输入的第一行为一个整数 $n \ (1 \le n \le 2000)$ 表示数的数量，接下来一行 $n$ 个整数 $a_1,a_2,\cdots, a_n \ (1 \le a_i \le 3000)$。
## 输出格式

输出一行一个整数表示答案，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
12
```
## 提示

共有八种 $S$ 的选择，所有选择得到的 $\prod_{i \in S} a_i$ 分别为 $1,1,2,2,3,3,6,6$。可以计算得到 $\varphi(1) = \varphi(2) = 1, \varphi(3) = \varphi(6) = 2$，因此答案为 $1 \times 4 + 2 \times 4 = 12$。


---

---
title: "[GCPC 2023] Highway Combinatorics"
layout: "post"
diff: 省选/NOI-
pid: P13673
tag: ['2023', '数论', 'Special Judge', 'Fibonacci 数列', '随机化', 'ICPC', '折半搜索 meet in the middle']
---
# [GCPC 2023] Highway Combinatorics
## 题目描述

You are the new minister of transport in Berland.
Recently, you allowed free parking on a two lane road segment of $200$ metres length.
Since then, that road segment has constantly been jammed by parked cars due to some
genius drivers who had the idea to park their cars across both lanes...

![](https://cdn.luogu.com.cn/upload/image_hosting/x81bkouf.png)

:::align{center}
Jam caused by parking bus, [Nevermind2](https://commons.wikimedia.org/wiki/File:Moscow_traffic_congestion.JPG)
:::


However, this is not your concern.
You are more interested in parking some of your own cars on the road segment while it is empty.
More specifically, you want to park some of your cars in such a way that the number of different ways to fill the remaining empty space with cars is congruent to your lucky number $n$ modulo $10^9+7$.

![](https://cdn.luogu.com.cn/upload/image_hosting/ntad7154.png)

:::align{center}
Figure H.1: Visualization of Sample Output 1.
:::

Each car has a size of $1\times2$ metres, each of the two lanes is $1$ metre wide and $200$ metres long. You own more than $200$ cars which you could park on the road segment.

## 输入格式

The input consists of:
- One line with one integer $n$ ($0\leq n<10^9+7$), the desired number of possible ways to fill the road modulo $10^9+7$.

It can be proven that at least one valid solution exists for each possible value of $n$.

## 输出格式

Output the state of the two lanes in two lines.
Print "$\texttt{\#}$" for an occupied spot and "$\texttt{.}$" for an empty spot. Note that the two lines should have the same length of at least $1$ metre and at most $200$ metres, and the occupied spots must correspond to some parked cars. If your solution uses a road segment shorter than $200$ metres, the remaining part of the road segment is assumed to be blocked by parked cars. 
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
##..#.......
....#.##....
```
### 样例输入 #2
```
27
```
### 样例输出 #2
```
...##........
........##...
```


---

---
title: "Mivik 的标题"
layout: "post"
diff: 省选/NOI-
pid: P1393
tag: ['字符串', '数学', 'KMP 算法', '快速数论变换 NTT']
---
# Mivik 的标题
## 题目背景

Mivik 现在已经写好了他的书，他现在准备给这本书起个书名去投稿。
## 题目描述

由于 Mivik 写书是乱敲键盘敲出来的，他准备对书名干同样的事情。Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。Mivik 决定在这个键盘上**等概率**随机敲 $n$ 次敲出标题。但出于某些原因，Mivik 希望书名中要包含有一个人的名字 $S$。于是 Mivik 来问你，他随机敲出的标题有多大的概率包含有这个名字。

同样的，Mivik 并不喜欢奇形怪状的小数，所以你只需要输出这个概率对 $998244353$ 取模后的值。
## 输入格式

第一行三个整数 $n$、$m$、$|S|$，其中 $|S|$ 代表这个名字的长度。

第二行给出 $|S|$ 个整数 $a_i$，代表这个名字。
## 输出格式

一行一个整数，代表概率对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
3 2 2
1 1
```
### 样例输出 #1
```
623902721
```
### 样例输入 #2
```
6 3 4
1 2 3 2
```
### 样例输出 #2
```
480636170
```
## 提示

### 样例解释

样例一：为方便描述，我们定义键盘上两个按键为 `a` 和 `b`。那么长度为 3 的所有字符串共有 `aaa`、`aab`、`aba`、`abb`、`baa`、`bab`、`bba`、`bbb` 这 8 个，其中包含有指定名字 `aa` 的共有 `aaa`、`aab`、`baa` 这三个，则概率为 $\frac{3}{8}$，取模后得到 623902721。

### 数据范围

对于全部数据，有 $1\le |S|\le 10^5$，$|S|\le n\le |S|+10^5$，$1\le m\le 10^8$。

Subtask 1 (5 pts)：满足 $m=1$。

Subtask 2 (20 pts)：满足 $1\le n, m\le 250$。

Subtask 3 (30 pts)：满足 $1\le n, m\le 5000$。

Subtask 3 (45 pts)：无特殊限制。


---

---
title: "DGF 等比求和"
layout: "post"
diff: 省选/NOI-
pid: P1998
tag: ['数论', 'Dirichlet 卷积']
---
# DGF 等比求和
## 题目描述

给定数论函数 $f$，定义 $f^n$ 为：

$$f^n=\begin{cases}f&n=1\\f^{n-1}* f &n\ge 2\end{cases}.$$

其中 $* $ 是 Dirichlet 卷积。

对于正整数 $n,m$，记数论函数 $g=f+f^2+\cdots+f^m$，请求出 $g(1),g(2),\cdots,g(n)$，答案对 $10^9+7$ 取模。

为控制输出量，只需输出 $\bigoplus_{k=1}^n(g(k)\bmod (10^9+7))$ 的值即可。
## 输入格式

第一行两个正整数 $n,m$。

第二行共 $n$ 个自然数，顺次代表 $f(1),f(2),\cdots,f(n)$。
## 输出格式

一行一个自然数，代表 $\bigoplus_{k=1}^n(g(k)\bmod (10^9+7))$。
## 样例

### 样例输入 #1
```
10 10
1 1 4 5 1 4 1 9 1 9
```
### 样例输出 #1
```
1864
```
## 提示

对于所有数据，保证 $1\le n\le 10^6,1\le m\le 10^9$，且对于 $1\le i\le n$，恒有 $0\le f(i)\le 10^9$。

特别地，$f(1)=1,f(2)\neq 0$。

对于样例一，$g$ 的前 $10$ 项依次为 $10, 55, 220, 440, 55, 1540, 55, 2475,2695,825$。

时限为 std 的 4 倍，请使用较快的读入方式。


---

---
title: "[USACO18FEB] Cow Gymnasts P"
layout: "post"
diff: 省选/NOI-
pid: P4270
tag: ['2018', 'USACO', '数论', '欧拉函数']
---
# [USACO18FEB] Cow Gymnasts P
## 题目描述

Bored of farm life, the cows have sold all their earthly possessions and joined the crew of a traveling circus. So far, the cows had been given easy acts: juggling torches, walking tightropes, riding unicycles -- nothing a handy-hoofed cow couldn't handle. However, the ringmaster wants to create a much more dramatic act for their next show.
The stage layout for the new act involves $N$ platforms arranged in a circle. On each platform, between $1$ and $N$ cows must form a stack, cow upon cow upon cow. When the ringmaster gives the signal, all stacks must simultaneously fall clockwise, so that the bottom cow in a stack doesn't move, the cow above her moves one platform clockwise, the next cow moves two platforms clockwise, and so forth. Being accomplished gymnasts, the cows know they will have no trouble with the technical aspect of this act. The various stacks of cows will not "interfere" with each other as they fall, so every cow will land on the intended platform. All of the cows landing on a platform form a new stack, which does not fall over.

The ringmaster thinks the act will be particularly dramatic if after the stacks fall, the new stack on each platform contains the same number of cows as the original stack on that platform. We call a configuration of stack sizes "magical" if it satisfies this condition. Please help the cows by computing the number of magical configurations. Since this number may be very large, compute its remainder modulo $10^9 + 7$.

Two configurations are considered distinct if there is any platform for which the configurations assign a different number of cows.
## 输入格式

The input is a single integer, $N$ ($1 \leq N \leq 10^{12}$).
## 输出格式

A single integer giving the number of magical configurations modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
6
```
## 提示

For $N = 4$, the valid configurations are $(1,1,1,1)$, $(2,2,2,2)$, $(3,3,3,3)$, $(4,4,4,4)$, $(2,3,2,3)$, and $(3,2,3,2)$.

Problem credits: Dhruv Rohatgi
## 题目翻译

### 题目描述

厌倦了农场生活的奶牛们卖掉了所有的财产，加入了一个巡回马戏团。到目前为止，奶牛们被分配了一些简单的表演：杂耍火炬、走钢丝、骑独轮车——没有什么是一头灵巧的奶牛无法应付的。然而，马戏团团长希望为他们的下一场演出创造一个更加戏剧性的表演。

新表演的舞台布局包括 $N$ 个平台，排列成一个圆圈。在每个平台上，必须有 $1$ 到 $N$ 头奶牛堆叠成一摞，奶牛一头叠在另一头上面。当团长发出信号时，所有的堆叠必须同时顺时针倒下，使得堆叠底部的奶牛不动，她上面的奶牛移动一个平台顺时针，再上面的奶牛移动两个平台顺时针，依此类推。作为技艺高超的体操运动员，奶牛们知道她们在技术方面不会有任何问题。各个奶牛堆叠在倒下时不会相互“干扰”，因此每头奶牛都会落在目标平台上。所有落在平台上的奶牛会形成一个新的堆叠，这个堆叠不会倒下。

团长认为，如果堆叠倒下后，每个平台上的新堆叠包含的奶牛数量与原始堆叠相同，那么这个表演将特别戏剧化。我们称满足这一条件的堆叠大小为“魔法”配置。请帮助奶牛们计算魔法配置的数量。由于这个数字可能非常大，请计算其对 $10^9 + 7$ 取模的结果。

如果两个配置在任何平台上分配的奶牛数量不同，则认为它们是不同的配置。

### 输入格式

输入是一个整数 $N$（$1 \leq N \leq 10^{12}$）。

### 输出格式

输出一个整数，表示魔法配置的数量对 $10^9 + 7$ 取模的结果。

### 提示

对于 $N = 4$，有效的配置是 $(1,1,1,1)$、$(2,2,2,2)$、$(3,3,3,3)$、$(4,4,4,4)$、$(2,3,2,3)$ 和 $(3,2,3,2)$。

题目来源：Dhruv Rohatgi


---

---
title: "[HAOI2018] 染色"
layout: "post"
diff: 省选/NOI-
pid: P4491
tag: ['2018', '河南', '各省省选', 'O2优化', '容斥原理', '生成函数', '快速数论变换 NTT']
---
# [HAOI2018] 染色
## 题目背景

HAOI2018 Round2 第二题
## 题目描述

为了报答小 C 的苹果，小 G 打算送给热爱美术的小 C 一块画布，这块画布可以抽象为一个长度为 $N$ 的序列，每个位置都可以被染成 $M$ 种颜色中的某一种。

然而小 C 只关心序列的 $N$ 个位置中出现次数恰好为 $S$ 的颜色种数，如果恰好出现了 $S$ 次的颜色有 $K$ 种，则小 C 会产生 $W_k$ 的愉悦度。

小 C 希望知道对于所有可能的染色方案，他能获得的愉悦度的和对 $1004535809$
取模的结果是多少。
## 输入格式

从标准输入读入数据。第一行三个整数 $N, M, S$。

接下来一行 $M + 1$ 个整数，第 $i$ 个数表示 $W_{i-1}$。
## 输出格式

输出到标准输出中。输出一个整数表示答案。
## 样例

### 样例输入 #1
```
8 8 3
3999 8477 9694 8454 3308 8961 3018 2255 4910
```
### 样例输出 #1
```
524070430
```
### 样例输入 #2
```
见 sample.zip/data2.in
```
### 样例输出 #2
```
见 sample.zip/data2.ans
```
## 提示

特殊性质: $\forall 1 \le i \le m, W_i = 0$。

对于 $100\%$ 的数据，满足 $1 \le N \le 10 ^ 7$，$1 \le M \le 10 ^ 5$，$1 \le S \le 150$，$0 \le W_i < 1004535809$。

![Data](https://cdn.luogu.com.cn/upload/pic/18057.png)



---

---
title: "【模板】多项式除法"
layout: "post"
diff: 省选/NOI-
pid: P4512
tag: ['快速数论变换 NTT']
---
# 【模板】多项式除法
## 题目描述

给定一个 $n$ 次多项式 $F(x)$ 和一个 $m$ 次多项式  $G(x)$ ，请求出多项式 $Q(x)$, $R(x)$，满足以下条件：

 - $Q(x)$ 次数为 $n-m$，$R(x)$ 次数小于 $m$
 - $F(x) = Q(x) * G(x) + R(x)$

所有的运算在模 $998244353$ 意义下进行。
## 输入格式

第一行两个整数 $n$，$m$，意义如上。  
第二行 $n+1$ 个整数，从低到高表示 $F(x)$ 的各个系数。  
第三行 $m+1$ 个整数，从低到高表示 $G(x)$ 的各个系数。
## 输出格式

第一行 $n-m+1$ 个整数，从低到高表示 $Q(x)$ 的各个系数。    
第二行 $m$ 个整数，从低到高表示 $R(x)$ 的各个系数。    
如果 $R(x)$ 不足 $m-1$ 次，多余的项系数补 $0$。
## 样例

### 样例输入 #1
```
5 1
1 9 2 6 0 8
1 7
```
### 样例输出 #1
```
237340659 335104102 649004347 448191342 855638018
760903695
```
## 提示

对于所有数据，$1 \le m < n \le 10^5$，给出的系数均属于 $[0, 998244353) \cap \mathbb{Z}$。


---

---
title: "【模板】分治 FFT"
layout: "post"
diff: 省选/NOI-
pid: P4721
tag: ['分治', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】分治 FFT
## 题目背景

也可用多项式求逆解决。
## 题目描述

给定序列 $g_{1\dots n - 1}$，求序列 $f_{0\dots n - 1}$。

其中 $f_i=\sum_{j=1}^if_{i-j}g_j$，边界为 $f_0=1$。

答案对 $998244353$ 取模。
## 输入格式

第一行一个整数 $n$ 。

第二行 $n-1$ 个整数 $g_{1\dots n - 1}$。
## 输出格式

一行 $n$ 个整数，表示 $f_{0\dots n - 1}$ 对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
4
3 1 2
```
### 样例输出 #1
```
1 3 10 35
```
### 样例输入 #2
```
10
2 456 32 13524543 998244352 0 1231 634544 51
```
### 样例输出 #2
```
1 2 460 1864 13738095 55389979 617768468 234028967 673827961 708520894
```
## 提示

$2\leq n\leq 10^5$，$0\leq g_i<998244353$。


---

---
title: "【模板】多项式对数函数（多项式 ln）"
layout: "post"
diff: 省选/NOI-
pid: P4725
tag: ['数学', '洛谷原创', 'O2优化', '导数', '积分', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】多项式对数函数（多项式 ln）
## 题目描述

给出 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $B(x)$，满足 $B(x) \equiv \ln A(x)$.

在  $\text{mod } 998244353$  下进行，且 $a_i \in [0, 998244353) \cap \mathbb{Z}$
## 输入格式

第一行一个整数 $n$.

下一行有 $n$ 个整数，依次表示多项式的系数 $a_0, a_1, \cdots, a_{n-1}$.

保证 $a_0 = 1$.
## 输出格式

输出 $n$ 个整数，表示答案多项式中的系数 $a_0, a_1, \cdots, a_{n-1}$.
## 样例

### 样例输入 #1
```
6
1 927384623 878326372 3882 273455637 998233543
```
### 样例输出 #1
```
0 927384623 817976920 427326948 149643566 610586717
```
## 提示

对于 $100\%$ 的数据，$n \le 10^5$.


---

---
title: "[集训队作业2013] 城市规划"
layout: "post"
diff: 省选/NOI-
pid: P4841
tag: ['数学', '2013', '集训队互测', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# [集训队作业2013] 城市规划
## 题目描述

刚刚解决完电力网络的问题，阿狸又被领导的任务给难住了。

刚才说过，阿狸的国家有 $n$ 个城市，现在国家需要在某些城市对之间建立一些贸易路线，使得整个国家的任意两个城市都直接或间接的连通。

为了省钱, 每两个城市之间最多只能有一条直接的贸易路径。对于两个建立路线的方案，如果存在一个城市对，在两个方案中是否建立路线不一样，那么这两个方案就是不同的，否则就是相同的。现在你需要求出一共有多少不同的方案。

好了，这就是困扰阿狸的问题。换句话说，你需要求出 $n$ 个点的简单 (无重边无自环) 有标号无向连通图数目。

由于这个数字可能非常大, 你只需要输出方案数对 $1004535809$ ( $479 \times 2 ^{21} + 1$ ) 取模即可。
## 输入格式

仅一行一个整数 $n$
## 输出格式

仅一行一个整数，为方案数 $\bmod \space 1004535809$。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4
```
### 样例输出 #2
```
38
```
### 样例输入 #3
```
100000
```
### 样例输出 #3
```
829847355

```
## 提示

【数据范围】   
对于 $20\%$ 的数据，$n \le 10$    
对于 $40\%$ 的数据，$n \le 1000$     
对于 $60\%$ 的数据，$n \le 30000$    
对于 $80\%$ 的数据，$n \le 60000$     
对于 $100\%$ 的数据，$n \le 130000$   

试题来源：$2013$ 中国国家集训队第二次作业


---

---
title: "【模板】多项式开根"
layout: "post"
diff: 省选/NOI-
pid: P5205
tag: ['快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】多项式开根
## 题目背景

模板题，无背景
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个在 ${} \bmod x^n$ 意义下的多项式 $B(x)$，使得 $B^2(x) \equiv A(x) \pmod{x^n}$。若有多解，请取零次项系数较小的作为答案。

多项式的系数在 ${}\bmod 998244353$ 的意义下进行运算。
## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 个整数，依次表示多项式的系数 $a_0, a_1, \dots, a_{n-1}$。

保证 $a_0 = 1$。
## 输出格式

输出 $n$ 个整数，表示答案多项式的系数 $b_0, b_1, \dots, b_{n-1}$。
## 样例

### 样例输入 #1
```
3
1 2 1

```
### 样例输出 #1
```
1 1 0

```
### 样例输入 #2
```
7
1 8596489 489489 4894 1564 489 35789489  

```
### 样例输出 #2
```
1 503420421 924499237 13354513 217017417 707895465 411020414

```
## 提示

对于 $100 \%$ 的数据：$1 \le n \leq 10^5$，$0 \le a_i < 998244353$。


---

---
title: "多项式三角函数"
layout: "post"
diff: 省选/NOI-
pid: P5264
tag: ['倍增', 'O2优化', '构造', '快速数论变换 NTT']
---
# 多项式三角函数
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $F(x)$，满足 $F(x)\equiv\sin{A(x)}$ 或 $F(x)\equiv\cos{A(x)}$。

所有运算在 $\bmod\ 998244353$ 意义下进行。
## 输入格式

第一行 **两个** 整数 $n,type$，若 $type=0$ 代表求 $\sin$，若 $type=1$ 代表求 $\cos$；

第二行 $n$ 个整数，依次表示多项式的系数 $a_0,a_1,\cdots,a_{n-1}$。

保证 $a_0=0$。
## 输出格式

输出一行 $n$ 个整数，表示答案多项式中的系数 $f_0,f_1,\cdots,f_{n-1}$。
## 样例

### 样例输入 #1
```
8 0
0 4 2 6 1 5 3 7
```
### 样例输出 #1
```
0 4 2 332748113 998244338 931694687 998244320 72887640
```
### 样例输入 #2
```
8 1
0 4 2 6 1 5 3 7
```
### 样例输出 #2
```
1 0 998244345 998244345 665496220 332748123 44366450 133099314
```
## 提示

对于 $100\%$ 的数据：$n\leq10^5$，$a_i\in[0,998244352]\cap\mathbb{Z}$。

前 $5$ 个点 $type=0$，后 $5$ 个点 $type=1$。


---

---
title: "【模板】多项式幂函数（加强版）"
layout: "post"
diff: 省选/NOI-
pid: P5273
tag: ['数学', '2019', '快速数论变换 NTT']
---
# 【模板】多项式幂函数（加强版）
## 题目背景

[普通版传送门](https://www.luogu.com.cn/problem/P5245)

模板题，无背景。
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个在 $\bmod\ x^n$ 意义下的多项式 $B(x)$，使得 $B(x) \equiv (A(x))^k \ (\bmod\ x^n)$。

多项式的系数在 $\bmod\ 998244353$ 的意义下进行运算。
## 输入格式

第一行两个整数 $n,k$。

接下来 $n$ 个整数，依次表示 $A(x)$ 的系数 $a_0, a_1,...,a_{n-1}$。
## 输出格式

输出 $n$ 个整数，依次表示 $B(x)$ 的前 $n$ 项系数 $b_0, b_1,...,b_{n-1}$ 在模 $998244353$ 意义下的最小自然数值。
## 样例

### 样例输入 #1
```
2 2
1 1
```
### 样例输出 #1
```
1 2
```
## 提示

对于 $100\%$ 的数据，$1< n \leq 10^5$，$0 \leq k \leq 10^{10^5}$，$a_i \in [0,998244352]$。

[数据更新时间](https://www.luogu.com.cn/paste/897zk1ia)


---

---
title: "【模板】多项式开根（加强版）"
layout: "post"
diff: 省选/NOI-
pid: P5277
tag: ['快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】多项式开根（加强版）
## 题目背景

模板题，无背景
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$ ，求一个在 $\bmod\ {x^n}$ 意义下的多项式 $B(x)$ ，使得 $B^2(x)\equiv A(x)\pmod {x^n}$。

多项式的系数在 $\bmod\ 998244353$ 的意义下进行运算。
## 输入格式

第一行一个正整数$n$。

接下来$n$个整数，依次表示多项式的系数$a_0,a_1,\cdots ,a_{n-1}$

**不保证$a_0=1$，但保证$a_0$是$\bmod\ 998244353$下的二次剩余。**
## 输出格式

输出 $n$ 个非负整数，表示答案多项式的系数$b_0,b_1\cdots ,b_{n-1}$。如有多解，输出**系数序列**（而非字符序列）字典序最小的。
## 样例

### 样例输入 #1
```
3
1 2 1

```
### 样例输出 #1
```
1 1 0
```
### 样例输入 #2
```
7
1 8596489 489489 4894 1564 489 35789489  

```
### 样例输出 #2
```
1 503420421 924499237 13354513 217017417 707895465 411020414

```
## 提示

对于$25\%$的数据，有$n \leq 1000$

对于$50\%$的数据，有$n \leq 10^4$

对于$75\%$的数据，有$n \leq 5\times 10^4$

对于$100\%$的数据，有$n \leq 10^5,a_i \in [0,998244352] \cap \mathbb{Z}$


---

---
title: "【模板】下降幂多项式乘法"
layout: "post"
diff: 省选/NOI-
pid: P5394
tag: ['快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】下降幂多项式乘法
## 题目背景

模板题，无背景。
## 题目描述

给定一个 $n$ 次下降幂多项式 $A(x)$ 和 $m$ 次下降幂多项式 $B(x)$，你要求出一个 $n+m$ 次下降幂多项式 $F(x)$ 满足 $F(x)=A(x)B(x)$。

由于结果会很大，你输出的多项式的系数应对 $998244353$ 取模。
## 输入格式

第一行两个正整数 $n,m$，表示下降幂多项式的次数。

第二行 $n+1$ 个非负整数 $a_0,a_1,a_2,\dots,a_n$，表示 $A(x)$ 的系数。即 $A(x)=a_0+a_1x+a_2x^{\underline 2}+\dots+a_nx^{\underline n}$。

第三行$m+1$个非负整数$b_0,b_1,b_2,\dots,b_m$，表示 $B(x)$ 的系数。即 $B(x)=b_0+b_1x+b_2x^{\underline 2}+\dots+b_mx^{\underline m}$。


## 输出格式

一行，共 $n+m+1$ 个非负整数，表示 $F(x)$ 的各项系数对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
2 3
1 2 3
1 2 3 4

```
### 样例输出 #1
```
1 8 52 148 89 12

```
## 提示

对于 $20\%$的数据，$n,m\leqslant 1000$。

对于 $100\%$ 的数据，$1\leqslant n,m\leqslant 10^5$，$a_i,b_i\in[0,998244353)$，$a_n,b_m \neq 0$。

## 提示

$x^{\underline n}=\left\{\begin{matrix}1 & n=0\\ x\times (x-1)^{\underline{n-1}} & n\geqslant 1 \end{matrix}\right.$

$\sum\limits_{i=0}^n a_ix^{\underline i},a_n\neq 0$ 是 $x$ 的 $n$ 次下降幂多项式。

容易证明 $n$ 次下降幂多项式唯一确定一个 $n$ 次多项式，所以下降幂多项式乘积的定义就是对应的多项式的乘积对应的下降幂多项式。 


---

---
title: "基于值域预处理的快速 GCD"
layout: "post"
diff: 省选/NOI-
pid: P5435
tag: ['数论', 'O2优化', '最大公约数 gcd']
---
# 基于值域预处理的快速 GCD
## 题目背景

模板题，无背景。
## 题目描述

给定 $n$ 个正整数 $a_1,a_2,\dots,a_n$，再给定 $n$ 个正整数 $b_1,b_2,\dots,b_n$，你需要对每对 $(i,j)$ 求出 $a_i$ 与 $b_j$ 的最大公因数。

不难发现你的输出应有 $n^2$ 个正整数。为了减少输出对程序的运行效率的影响，你只需要输出 $n$ 行，每行一个整数 $A_i$。

其中对于 $i\in[1,n]$，$A_i=\sum_{j=1}^{n}i^j\gcd(a_i,b_j)$。由于答案可能过大，你只需要输出模 $998,244,353$ 后的结果即可。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数，表示 $a_1,a_2,\dots,a_n$。

第三行 $n$ 个正整数，表示 $b_1,b_2,\dots,b_n$。
## 输出格式

共 $n$ 行，第 $i$ 行应输出一个非负整数 $A_i$。意义见题目描述。
## 样例

### 样例输入 #1
```
5
200 300 300 300 23333
666 666 666 666 123456

```
### 样例输出 #1
```
16
564
3636
14328
3905

```
## 提示

对于 $20\%$ 的数据，$1\leqslant n\leqslant 500$。

对于 $100\%$ 的数据，$1\leqslant n\leqslant 5000;1\leqslant a_i,b_i\leqslant 10^6$。

**请注意常数因子对程序运行效率的影响**


---

---
title: "差分与前缀和"
layout: "post"
diff: 省选/NOI-
pid: P5488
tag: ['数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 差分与前缀和
## 题目描述

给定一个长为 $n$ 的序列 $a$，求出其 $k$ 阶差分或前缀和。    
结果的每一项都需要对 $1004535809$ 取模。
## 输入格式

第一行三个整数 $n,k,t$，若 $t=0$ 表示求前缀和，$t=1$ 表示求差分。  
第二行 $n$ 个整数，表示序列 $a$。
## 输出格式

输出一行 $n$ 个整数，表示 $a$ 的 $k$ 阶差分或前缀和。
## 样例

### 样例输入 #1
```
8 3 0
1 9 2 6 0 8 1 7
```
### 样例输出 #1
```
1 12 35 76 135 220 332 478 
```
### 样例输入 #2
```
8 3 1
1 9 2 6 0 8 1 7
```
### 样例输出 #2
```
1 6 1004535787 26 1004535788 24 1004535780 28
```
## 提示

【数据范围】  

$1 \le n \le 10^5$  
$0 \le a_i \le 10^9$   
$1\le k \le 10^{2333}, k \not \equiv 0 \pmod{1004535809}$


---

---
title: "【CSGRound2】开拓者的卓识"
layout: "post"
diff: 省选/NOI-
pid: P5641
tag: ['数学', '快速傅里叶变换 FFT', '快速数论变换 NTT', '洛谷月赛']
---
# 【CSGRound2】开拓者的卓识
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ozu5pj.png)

（上图转载于某神仙的题目描述）

小 K 又在做白日梦了。他进入到他的幻想中，发现了一个非常有趣的序列$a$和一个非常有趣的数$k$。
## 题目描述

我们记一个序列 $[l,r]$ 的 $k$ 阶子段和为 $sum_{k,l,r}$，有

$$sum_{k,l,r}=\begin{cases}\sum\limits_{i=l}^{r}a_i&,k=1\\\sum\limits_{i=l}^{r}\sum\limits_{j=i}^{r}sum_{k-1,i,j}&,k\geq 2\end{cases}$$

他现在站在位置 $1$ 上，他每一次往右开拓一个格子就可以增加他 IOI 赛场的 rp，所以他想尽可能的多开拓格子。可是每一次他从 $r$ 开拓到 $r+1$ 需要正确的回答 $sum_{k,1,r}$。小 K 不屑于算，就把任务交给你了。
## 输入格式

两行。第一行 $n,k$，表示 $a$ 的长度和 $k$。

第二行 $n$ 个正整数，表示 $a$。
## 输出格式

一行，第 $i$ 个数为 $sum_{k,1,i}$。由于答案过大，您只需要求出答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 1
1 2 3
```
### 样例输出 #1
```
1 3 6
```
### 样例输入 #2
```
3 2
1 2 3
```
### 样例输出 #2
```
1 6 20
```
### 样例输入 #3
```
3 10
1 2 3
```
### 样例输出 #3
```
1 30 420
```
## 提示

### 样例解释 2

$sum_{2,1,1}=sum_{1,1,1}=1$

$sum_{2,1,2}=sum_{1,1,1}+sum_{1,1,2}+sum_{1,2,2}=1+3+2=6$

$sum_{2,1,3}=sum_{1,1,1}+sum_{1,1,2}+sum_{1,1,3}+sum_{1,2,2}+sum_{1,2,3}+sum_{1,3,3}=1+3+6+2+5+3=20$

### 数据范围

| 测试点编号 |  $n$ 的范围 |  $k$ 的范围 |  $a_i$ 的范围 |
| :-: | :-: | :-: | :-: |
|  $1\sim 2$ |  $\le 10$ |  $\le 10$ |  $\le 10$ |
|  $3\sim 8$ |  $\le 10^3$ |  $\le 10^3$ |  $\le 10^5$ |
|  $9$ |  $\le 10^5$ |  $=1$ |  $\le 998244353$ | 
|  $10$ |  $\le 10^5$ |  $=2$ |  $\le 998244353$ |
|  $11$ |  $\le 10^5$ |  $=3$ |  $\le 998244353$ |
|  $12$ |  $\le 10^5$ |  $\le 10$ |  $\le 998244353$ |
|  $13\sim 17$ |  $\le 10^5$ |  $\le 10^2$ |  $\le 998244353$ |
|  $18$ |  $\le 10^5$ |  $\le 10^5$ |  $\le 998244353$ |
|  $19\sim 25$ |  $\le 10^5$ |  $\le 998244353$ |  $\le 998244353$ |


---

---
title: "拉格朗日插值2"
layout: "post"
diff: 省选/NOI-
pid: P5667
tag: ['快速傅里叶变换 FFT', '快速数论变换 NTT', '拉格朗日插值法']
---
# 拉格朗日插值2
## 题目描述

给定一个不超过 $n$ 次的多项式的 $n+1$ 个点值 $f(0),f(1) \dots f(n)$，和一个正整数 $m$，求 $f(m),f(m+1) \dots f(m+n)$。

答案对 $998244353$ 取模。
## 输入格式

第一行两个正整数 $n,m$，意义如题目描述。  
第二行 $n+1$ 个整数，表示 $f(0),f(1) \dots f(n)$。
## 输出格式

输出一行 $n+1$ 个整数，表示 $f(m),f(m+1) \dots f(m+n)$。
## 样例

### 样例输入 #1
```
5 6
1 1 4 5 1 4
```
### 样例输出 #1
```
54 232 673 1579 3232 6007
```
## 提示

【数据范围】     
对于 $100\%$ 的数据：  
$1 \le n \le 160000$，$n < m \le 10^8$，$0 \le f(i) < 998244353$。


---

---
title: "排列计数"
layout: "post"
diff: 省选/NOI-
pid: P5825
tag: ['动态规划 DP', '组合数学', 'Stirling 数', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 排列计数
## 题目描述

我们记一个排列 $P$ 的升高为 $k$ 当且仅当存在 $k$ 个位置 $i$ 使得 $P_i<P_{i+1}$。

现在给定排列长度 $n$，对于所有整数 $k\in [0,n]$ 求有多少个排列的升高为 $k$。
## 输入格式

一个整数 $n$。
## 输出格式

一行，$n+1$ 个整数，第 $i$ 个整数表示长度为 $n$ 且升高为 $i-1$ 个排列的个数，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
1 11 11 1 0
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^5$。


---

---
title: "悔改"
layout: "post"
diff: 省选/NOI-
pid: P6300
tag: ['2020', 'O2优化', '枚举', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 悔改
## 题目描述

Daniel13265 有一些同样长的小木棍，他把这些木棍随意砍成两段，使得每段的长都不超过 $m$。

现在他想把小木棍拼接成原来的样子，但是却遗失了部分小木棍，而且忘记了自己开始时有多少根木棍和它们的长度。所以他打算把剩下的小木棍拼接出尽可能多的相同长度的木棍。

给出每段小木棍的长度，求出从剩下的木棍中最多能够拼接出的相同长度的木棍的个数与能拼接出来相同长度的木棍个数最多时木棍的最小可能长度。

## 输入格式

输入共 $2$ 行。
  
第一行包含两个正整数 $n,m$，分别表示剩余木棍个数与剩余木棍的最大可能长度。  
第二行共 $n$ 个用单个空格隔开的正整数，第 $i$ 个数 $a_i$ 表示第 $i$ 个木棍的长度。
## 输出格式

输出一行两个整数，分别表示从剩下的木棍中最多能够拼接出的相同长度的木棍的个数与能拼接出来相同长度的木棍个数最多时木棍的最小可能长度。
## 样例

### 样例输入 #1
```
7 10
1 1 2 4 7 8 9

```
### 样例输出 #1
```
2 9
```
## 提示

### 样例解释

如果要拼接出尽量多的长度为 $11$ 的木棍，可以将长度为 $2$ 和 $9$ 的木棍拼接在一起，将长度为 $4$ 和 $7$ 的木棍拼接在一起。然而如果将长度为 $1$ 和 $8$ 的木棍拼接在一起，将长度为 $2$ 和 $7$ 的木棍拼接在一起，可以拼接出 $2$ 根长度为 $9$ 的木棍。  

可以发现能拼接出来相同长度的木棍个数的最大值就是 $2$，此时木棍的长度可能为 $9,10$ 或 $11$，其中最小的为 $9$。


### 数据范围

**本题采用捆绑测试。你每通过一个子任务的所有数据点，就能得到该子任务的全部分数。**

| 子任务编号 | $n\le$ | $m\le$ | 分值 |
|:-:|:-:|:-:|:-:|
| $1$ | $10$ | $10^5$ | $5$ |
| $2$ | $10^3$ | $10^3$ | $10$ |
| $3$ | $10^3$ | $10^5$ | $10$ |
| $4$ | $10^5$ | $10$ | $5$ |
| $5$ | $10^5$ | $10^3$ | $10$ |
| $6$ | $10^5$ | $10^5$ | $60$ |

对于 $100\%$ 的数据，满足 $2\le n,m\le10^5,1\le a_i\le m$。


---

---
title: "强迫症"
layout: "post"
diff: 省选/NOI-
pid: P6694
tag: ['数学', '2020', 'O2优化', '生成函数', '快速数论变换 NTT']
---
# 强迫症
## 题目背景

小 L 是一个严重的强迫症患者。

由于他严重的强迫症，所以他画图时总是要把点画在一个圆上。
## 题目描述

一天，他问了小 H 和小 W 这样一个问题：

如果在一个圆上有 $n$ 个不同的点，依次标号为 $1$ 到 $n$，有多少种方案能把它们连成一棵树？

小 H & 小 W：这不是sb题吗？

小 L：那如果**连边不能相交**呢？

小 H & 小 W：这不是sb题吗？

小 L：那如果把「树」换成「图」呢呢？

小 H & 小 W：这不是sb题吗？

小 L：那如果给每个点一个权值 $a_i$，连接 $(i,j)$ 的边权值为 $a_i\times a_j$，求**满足上面**的图的**期望所有边权值之和**呢？

小 H & 小 W：这不是sb题吗？

小 L 见自己辛苦做了许久都没写出的题目被 dalao 轻松秒杀后十分郁闷。为了安慰他，你需要帮他做出这个问题。

**注意**：
1. 两条边在端点处**不视作相交**。
1. **没有边的图（即只有 $n$ 个点，之间没有边相连）也合法**
1. 点**按顺时针从 $1$ 到 $n$** 编号。
1. 图中**不能有自环和重边**
## 输入格式

第一行一个正整数 $n$，意义如上。

接下来一行 $n$ 个非负整数，第 $i$ 个数为 $a_i$，表示第 $i$ 个点的点权。
## 输出格式

一个正整数，表示结果。答案对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
4
1 1 1 1
```
### 样例输出 #1
```
665496238
```
### 样例输入 #2
```
13
1 1 4 5 1 4 1 9 1 9 8 1 0
```
### 样例输出 #2
```
748867567
```
## 提示

对于样例一，全部 $64$ 张图如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/zfa8hs0v.png)

其中左侧 $48$ 张图合法，右侧 $16$ 张图不合法，所有边的权值均为 $1$。

期望边权和为 $\dfrac{8}{3}$，模 $998244353$ 意义下结果为 $665496238$。

### 数据范围

**本题采用捆绑测试。**

- Subtask 1( $10\%$ )：$n\leq 6$。
- Subtask 2( $30\%$ )：$n\leq 3000$。
- Subtask 3( $60\%$ )：无特殊限制。

对于 $100\%$ 的数据，$2\leq n\leq 10^5,0\leq a_i\leq10^6$。

Subtask 1 和 Subtask 2 时限 $1s$，Subtask 3 时限 $2s$。

------------
如果你不知道如何对一个有理数取模，请自行百度「乘法逆元」


---

---
title: "「Wdsr-2」白泽教育"
layout: "post"
diff: 省选/NOI-
pid: P6736
tag: ['2020', '递归', '数论', '洛谷原创', 'O2优化', '哈希 hashing', '根号分治', '欧拉降幂']
---
# 「Wdsr-2」白泽教育
## 题目背景

上白泽慧音在给雾之湖的妖精们讲课。

某天，慧音在上数学课时，提到了一种非常有趣的记号：**高德纳箭号表示法**。它可以用来描述非常巨大的数字。~~比如紫的年龄。~~

对于非负整数 $a, b$ 和正整数 $n$，高德纳箭号表示法的定义为：

$$a \uparrow^n b = \begin{cases}
1\ (b = 0) \\
a^b\ (n = 1\ \operatorname{and}\ b > 0) \\
a \uparrow^{n - 1} (a \uparrow^n (b - 1))\ (n > 1\ \operatorname{and}\ b > 0)
\end{cases}$$

一些简单的例子：

- $2 \uparrow 31 = 2^{31} = 2147483648$

- $2 \uparrow \uparrow 4 = 2^{2^{2^2}} = 2^{2^4} = 2^{16} = 65536$

注：
1. $a \uparrow b$ 与 $a \uparrow^1 b$ 相同；

2. $a \uparrow \uparrow b$ 与 $a \uparrow^2 b$ 相同；

3. 请注意幂运算的顺序。
## 题目描述

慧音希望琪露诺解决以下关于 $x$ 的方程：

$$a \uparrow^n x \equiv b \pmod p$$

其中，$a, n, b, p$ 为已知的常数，$x$ 为未知数。

琪露诺被高德纳箭号表示法搞得云里雾里的，但是她不想被头槌。你能帮帮她吗？
## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，四个整数 $a, n, b, p$。
## 输出格式

对于每组数据，输出一行，一个整数，如果原方程有解，输出该方程的最小非负整数解；否则，输出 $-1$。
## 样例

### 样例输入 #1
```
3
2 1 1 3
3 1 2 7
7 1 2 4
```
### 样例输出 #1
```
0
2
-1
```
### 样例输入 #2
```
3
2 2 4 7
3 2 4 6
5 2 1 3
```
### 样例输出 #2
```
2
-1
0
```
### 样例输入 #3
```
3
4 3 5 8
2 3 9 11
6 3 1 5
```
### 样例输出 #3
```
-1
3
0
```
## 提示

**本题开启捆绑测试。**

| Subtask | $n$ | $p$ | $T$ | 分值 | 时限 |
| :------: | :------: | :------: | :------: | :------: | :------: |
| $1$ | $n = 1$ | $2 \leq p \leq 10^9$ 且 $p$ 为质数 | $1 \leq T \leq 100$ | $15 \operatorname{pts}$ | $2.00 \operatorname{s}$ |
| $2$ | $n = 2$ | 无特殊限制 | $1 \leq T \leq 5 \times 10^3$ | $25 \operatorname{pts}$ | $1.00 \operatorname{s}$ |
| $3$ | $n = 3$ | 无特殊限制 | 无特殊限制 | $60 \operatorname{pts}$ | $2.00 \operatorname{s}$ |

对于 $100\%$ 的数据，$1 \leq a \leq 10^9$，$1 \leq n \leq 3$，$0 \leq b < p \leq 10^9$，$1 \leq T \leq 2 \times 10^4$。


---

---
title: "「PMOI-2」简单构造题"
layout: "post"
diff: 省选/NOI-
pid: P7423
tag: ['数学', 'O2优化', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「PMOI-2」简单构造题
## 题目描述

某次模拟赛中，NaCly\_Fish 遇见这样一道题：
****
定义一个长度为 $n$ 的序列 $A$ 的权值为：

$$\sum_{l=1}^n\sum_{r=l}^n f_A(l,r)$$
其中 $f_A(l,r)$ 就是在 $A$ 的区间 $[l,r]$ 中，「所有**在该区间内出现过的**元素出现次数的乘积」再乘上「区间内所有元素的乘积」。  

要求构造一个长为 $n$ 的序列，其中每个元素都是 $[1,m]$ 中的整数，最大化其权值。
****
她并不会，只好均匀随机 $n$ 个 $[1,m]$ 中的整数组成一个数列，然后输出其权值。

当然，她的这份程序一分都没拿到；但她想知道，生成出的序列期望权值是多少。

为了防止精度问题，答案需要对 $998244353$ 取模。
## 输入格式

一行两个正整数 $n,m$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 2
```
### 样例输出 #1
```
623902740
```
### 样例输入 #2
```
5 3
```
### 样例输出 #2
```
887328630
```
### 样例输入 #3
```
80 233
```
### 样例输出 #3
```
913763047
```
### 样例输入 #4
```
114514 19260817
```
### 样例输出 #4
```
850727003
```
## 提示

【样例一解释】  

显然有 $8$ 种可能的序列：  
$[1,1,1],[1,1,2],[1,2,1],[1,2,2],[2,1,1],[2,1,2],[2,2,1],[2,2,2]$。

权值分别为 $10,12,12,23,12,17,23,46$，期望值就是 $\frac{155}{8}$。

【样例二解释】

期望值是 $\frac{76842}{243}$。

【数据范围】  

**本题采用捆绑测试**。

- Subtask 1（5 pts）：$1\le n,m \le 8$；  
- Subtask 2（7 pts）：$1\le n,m \le 100$；  
- Subtask 3（11 pts）：$1 \le n,m \le 400$； 
- Subtask 4（13 pts）：$1\le n,m \le 5000$；
- Subtask 5（25 pts）：$1\le n \le 5000$；
- Subtask 6（39 pts）：无特殊限制。

对于 $100\%$ 的数据满足，$1\le n \le 2 \times 10^5$，$1\le m \le 10^8$。




---

---
title: "[THUPC 2017] 小 L 的计算题"
layout: "post"
diff: 省选/NOI-
pid: P7431
tag: ['2017', '分治', '快速傅里叶变换 FFT', '快速数论变换 NTT', 'THUPC']
---
# [THUPC 2017] 小 L 的计算题
## 题目描述

现有一个长度为 $n$ 的非负整数数组 $\{a_i\}$ 。小 L 定义了一种神奇变换：
$$f_k=\left(\sum_{i=1}^na_i^k\right)\bmod 998244353$$
小 L 计划用变换生成的序列 $f$ 做一些有趣的事情，但是他并不擅长算乘法，所以来找你帮忙，希望你能帮他尽快计算出 $f_{1\dots n}$。
## 输入格式

输入包含多组数据。

输入的第一行包含一个整数 $T$ , 表示数据组数。

接下来 $2T$ 行，每两行代表一组测试数据。

每组数据的第一行包含一个整数 $n$，表示数组 $\{a_i\}$ 的长度。接下来一行 $n$ 个整数，描述数组 $\{a_i\}$。

保证输入的 $a_i$ 满足 $0\le a_i\le10^9$。在一个测试文件中，保证有 $\sum n\le 4\times 10^5$。
## 输出格式

我们不想让你输出过多的数。因此，令 $ans=\bigoplus_{i=1}^{n}f_i$，其中 $\bigoplus$ 表示**异或**操作，在 C++ / Java / Python 中，它可以表示为 `^`。

对每组数据，你需要输出一行一个整数，表示 $ans$。
## 样例

### 样例输入 #1
```
2
3
2 3 3
5
1 2 3 4 5
```
### 样例输出 #1
```
32
4675
```
## 提示

对于 $100\%$ 的数据，$0\le a_i\le10^9$，$1\le n\le 2\times 10^5$，$\sum n\le 4\times 10^5$。

#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "简单的排列计数"
layout: "post"
diff: 省选/NOI-
pid: P7435
tag: ['动态规划 DP', '数学', 'O2优化', '动态规划优化', '组合数学', '排列组合', 'Stirling 数', '生成函数', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 简单的排列计数
## 题目描述

设 $\text{inv}_{\pi}$ 表示排列 $\pi$ 的逆序对数。如果 $\pi$ 长度为 $n$ 则有

$$\text{inv}_{\pi}=\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}[\pi_i>\pi_j]$$

给定两个正整数 $n,k$，和一个排列 $\pi^\prime$，定义一个长度为 $n$ 的排列 $\pi$ 的权值 $\text{val}_{\pi}$ 为

$$\text{val}_{\pi}=\prod\limits_{i=1}^{n}\prod_{j=i+1}^{n}\pi_i^{[\pi_{i}>\pi_j]}$$

对于 $0\leq m\leq k$ 求

$$\sum\limits_{\pi}[\text{inv}_\pi=m]\text{val}_\pi$$

其中 $\pi$ 是长度为 $n$ 的排列。
## 输入格式

第一行两个整数 $n,k$。
## 输出格式

一行 $k+1$ 个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3 3
```
### 样例输出 #1
```
1 5 15 18
```
## 提示

### 样例解释 1

$$\text{inv}_{(1,2,3)}=0,\text{inv}_{(1,3,2)}=1,\text{inv}_{(2,1,3)}=1,\text{inv}_{(2,3,1)}=2,\text{inv}_{(3,1,2)}=2,\text{inv}_{(3,2,1)}=3$$

$$\text{val}_{(1,2,3)}=1,\text{val}_{(1,3,2)}=3,\text{val}_{(2,1,3)}=2,\text{val}_{(2,3,1)}=6,\text{val}_{(3,1,2)}=9,\text{val}_{(3,2,1)}=18$$

所以当 $m=0$ 时答案为 $1$，$m=1$ 时为 $5$， $m=2$ 时为 $15$，$m=3$ 时为 $18$。

### 数据范围

| 子任务编号 | 分值 | $n\leq $ | $k\leq $ |
| :----------: | :----------: | :----------: | :----------: |
| Subtask 1 | $1$ | $6$ |  |
| Subtask 2 | $12$ | $40$ |  |
| Subtask 3 | $1$ | $998244352$ | $1$ |
| Subtask 4 | $16$ | $998244352$ | $10$ |
| Subtask 5 | $24$ | $2\times 10^5$ |  |
| Subtask 6 | $46$ | $998244352$ |  |

对于 $100\%$ 的数据，$2\leq n\leq 998244352$，$1\leq k\leq \min(2\times 10^5,\frac{n(n-1)}{2})。$


---

---
title: "[传智杯 #3 决赛] 旅人1969"
layout: "post"
diff: 省选/NOI-
pid: P7493
tag: ['动态规划 DP', '多项式', 'O2优化', '快速数论变换 NTT', '传智杯']
---
# [传智杯 #3 决赛] 旅人1969
## 题目背景

在被称为未来的二十一世纪里，只残留着不安与少许的幻想。

永远与须臾的罪人啊，二十世纪的诺亚方舟，承载着期待与不安向着天空飞去呢！

而作为希望的你，在这并不永恒的旅途中，会怎样地前行呢？
## 题目描述

一条笔直的公路上有 $n$ 个旅店，第 $i$ 个旅店的坐标是 $i$，每一天早上从旅店出发走最多 $m$ 个距离，同时固定给你一个常数 $k$。

给定 $q$ 组询问，每次给定 $u,v$，求早上从旅店 $u$ 出发到旅店 $v$，途径不超过 $k$ 个旅店（不含起点 $u$）且行走方向不变的方案数。两种方案不同当且仅当存在一个不同的旅店选择，答案对 $998244353$ 取模。

对于所有数据，$n,q\leq 10^5$，$m,k\leq 10^4$，$mk\leq 10^5$，$u,v\leq n$。
## 输入格式

输入共 $q+1$ 行。

第一行输入 $4$ 个正整数 $n,m,k,q$。

接下来 $q$ 行，每行输入 $2$ 个正整数 $u,v$，表示一组询问。
## 输出格式

输出共 $q$ 行，每行输入 $1$ 个整数表示答案。
## 样例

### 样例输入 #1
```
3 2 2 2
1 3
2 3
```
### 样例输出 #1
```
2
1
```
### 样例输入 #2
```
2077 30 200 3
1949 2021
1969 2077
1970 2004

```
### 样例输出 #2
```
360658315
804081653
603979748
```


---

---
title: "『JROI-2 / Stoi2039』等你下课"
layout: "post"
diff: 省选/NOI-
pid: P7779
tag: ['数学', '数论', '不定方程']
---
# 『JROI-2 / Stoi2039』等你下课
## 题目背景

![](bilibili:BV1hW411v7GC)
## 题目描述

给定正整数 $d$，定义

$$S_v=\{(x,y):x,y \in \mathbb{Z_{\ge 0}},x^2-dy^2=v\}$$

求：

$$\sum_{v=1}^{\lfloor\sqrt{d}\rfloor}v[S_v \neq \varnothing]$$

多组询问。
## 输入格式

第一行一个正整数 $t$ 表示询问次数。

接下来 $t$ 行，每行一个正整数 $d$ 表示一次询问。
## 输出格式

对于每次询问输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
4
10
13
16
19

```
### 样例输出 #1
```
1
4
5
5

```
## 提示

#### 样例解释

- 对于 $d=10$，只有 $v=1$ 满足 $S_v \neq \varnothing$。
- 对于 $d=13$，有 $v=1,3$ 满足 $S_v \neq \varnothing$。
- 对于 $d=16$，有 $v=1,4$ 满足 $S_v \neq \varnothing$。
- 对于 $d=19$，有 $v=1,4$ 满足 $S_v \neq \varnothing$。

#### 数据范围

- 对于 $30\%$ 的数据，$t=1$，$1 \le d \le 70$。
- 对于 $60\%$ 的数据，$t=1$。
- 对于 $100\%$ 的数据，$1 \le t \le 4 \times 10^3$，$1 \le d \le 2 \times 10^6$。

-----
Source：[JROI-2 Summer Fun Round](https://www.luogu.com.cn/contest/30241) - T4

Idea&Sol&Std&Data：[VinstaG173](/user/59388)

Retest：None


---

---
title: "【模板】Meissel-Lehmer"
layout: "post"
diff: 省选/NOI-
pid: P7884
tag: ['2021', '数论', '洛谷原创']
---
# 【模板】Meissel-Lehmer
## 题目描述

给定整数 $n$，求出 $\pi(n)$ 的值。

$\pi(n)$ 表示 $1 \sim n$ 的整数中质数的个数。
## 输入格式

一行，一个整数 $n$。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
4
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^{13}$。


---

---
title: "[BalkanOI 2003] Farey 序列"
layout: "post"
diff: 省选/NOI-
pid: P8058
tag: ['2003', '二分', '数论', '素数判断,质数,筛法', '最大公约数 gcd', '莫比乌斯反演', 'Stern-Brocot 树', 'BalkanOI（巴尔干半岛）']
---
# [BalkanOI 2003] Farey 序列
## 题目描述

把所有分子和分母都 $\leq n$ 的**最简真分数**从小到大排成一行，形成的序列称为 Farey 序列。

求出 $n$ 所对应的 Farey 序列中第 $k$ 小的数。
## 输入格式

一行，两个整数 $n, k$。
## 输出格式

一行，两个整数 $p, q$，表示答案 $\frac{p}{q}$。
## 样例

### 样例输入 #1
```
5 6
```
### 样例输出 #1
```
3 5
```
## 提示

对于 $100\%$ 的数据，$2 \leq n \leq 4 \times 10^4$，$1 \leq k \leq$ 符合条件的分数的个数。


---

---
title: "[USACO22FEB] Sleeping in Class P"
layout: "post"
diff: 省选/NOI-
pid: P8193
tag: ['贪心', 'USACO', '2022', '数论', '素数判断,质数,筛法', '前缀和']
---
# [USACO22FEB] Sleeping in Class P
## 题目描述

最近终于线下授课了，奶牛 Bessie 十分兴奋！不幸的是，Farmer John 是一个非常无聊的讲师，因此她经常课堂上睡觉。

Farmer John 注意到了 Bessie 上课走神。他要求班上的另一个学生 Elsie 跟踪记录给定课上 Bessie 睡觉的次数。一共有 $N$ 堂课，Elsie 记录下了 Bessie 在第 $i$ 堂课睡了 $a_i$ 次。所有课上 Bessie 一共睡觉的次数最多为 $10^{18}$。

Elsie 认为自己是 Bessie 的竞争对手，所以她想让 FJ 觉得在每堂课上 Bessie 都一直睡了同样多次——让 FJ 觉得这个问题显然完全是 Bessie 的错，而不是 FJ 有时上课很无聊的问题。

Elsie 修改记录只有以下两种方式：把两堂课的记录合起来，或者把一堂课的记录分成两堂课。例如，如果 $a=[1,2,3,4,5]$，那么如果 Elsie 将第二堂和第三堂课的记录合起来，记录就会变为 $[1,5,4,5]$。如果 Elsie 继续选择让第三堂课的记录分为两堂，记录就可能变为 $[1,5,0,4,5],[1,5,1,3,5],[1,5,2,2,5],[1,5,3,1,5]$ 或 $[1,5,4,0,5]$。

给定 $Q$ 个候选的 Bessie 最不喜欢的数字 $q_1,\ldots,q_Q$，对于每个数字，请帮助 Elsie 计算她至少要操作多少次，才能让记录里的所有数字都变成这个数字。
## 输入格式

第一行一个整数 $N$（$2\le N\le 10^5$）。

第二行 $N$ 个整数 $a_1,a_2,\ldots, a_N$（$1\le a_i\le 10^{18}$）。

第三行一个整数 $Q$（$1\le Q\le 10^5$）。

接下来 $Q$ 行，每行一个整数 $q_i$（$1\le q_i\le 10^{18}$），表示 Bessie 最不喜欢的数字。
## 输出格式

对于每个 $q_i$，计算 Elsie 把记录里的每个数都变成 $q_i$ 所需要的最小操作次数。如果不能把所有数都变成 $q_i$，输出 $-1$。
## 样例

### 样例输入 #1
```
6
1 2 3 1 1 4
7
1
2
3
4
5
6
12
```
### 样例输出 #1
```
6
6
4
5
-1
4
5
```
## 提示

**【样例解释】**

Elsie 需要至少 $4$ 次修改才能让记录里的所有数都变成 $3$。

$$
\begin{aligned}
&\ 1\ 2\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 5\\
\rightarrow&\ 3\ 3\ 6\\
\rightarrow&\ 3\ 3\ 3\ 3\\
\end{aligned}
$$

Elsie 不可能把记录中的所有数都变成 $5$，因此输出 $-1$。这是正确的。

**【数据范围】**

- 对于第 $2\sim 4$ 组数据，$N,Q\le 5000$。
- 对于第 $5\sim 7$ 组数据，所有 $a_i$ 最多为 $10^9$。
- 对于第 $8\sim 26$ 组数据，无附加限制。


---

---
title: "[THUPC 2023 初赛] 快速 LCM 变换"
layout: "post"
diff: 省选/NOI-
pid: P9135
tag: ['2023', '数论', 'O2优化', '快速傅里叶变换 FFT', 'THUPC']
---
# [THUPC 2023 初赛] 快速 LCM 变换
## 题目描述

小 I 今天学习了快速最小公倍数变换（Fast Least-Common-Multiple Transform, FLT），于是他想考考你。

给定一个长度为 $n$ 的正整数序列 $r_1,r_2,\cdots,r_n$。你需要做以下操作恰好一次：

- 选择整数 $i,j$ 使得 $1 \le i < j \le n$。在序列末尾加入 $(r_i+r_j)$，并将 $r_i$ 和 $r_j$ 从序列中删除。

可以注意到总共有 $\frac{n(n-1)}{2}$ 种可能的操作，每种操作会得到一个长度为 $n-1$ 的序列。

你需要对所有的这 $\frac{n(n-1)}{2}$ 个序列，求出序列中所有元素的最小公倍数，并给出它们的和模 $998244353$ 的值。
## 输入格式

输入的第一行包含一个正整数 $n$，表示序列的长度。接下来一行 $n$ 个正整数 $r_1,r_2,\cdots,r_n$，描述初始序列。
## 输出格式

输出一行一个整数，表示所有序列的最小公倍数的和模 $998244353$ 的值。
## 样例

### 样例输入 #1
```
3
2 3 4

```
### 样例输出 #1
```
40

```
## 提示

#### 样例解释 1

- $i=1,j=2$ 时，得到的序列为 $\{4,5\}$，最小公倍数为 $20$；
- $i=1,j=3$ 时，得到的序列为 $\{3,6\}$，最小公倍数为 $6$；
- $i=2,j=3$ 时，得到的序列为 $\{2,7\}$，最小公倍数为 $14$。

因此输出为 $20+6+14=40$。

#### 子任务

对于所有测试数据，$2 \le n \le 5 \times 10^5, 1 \le r_1,r_2,\cdots,r_n \le 10^6$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "『STA - R3』大豆"
layout: "post"
diff: 省选/NOI-
pid: P9511
tag: ['数学', '数论', 'O2优化']
---
# 『STA - R3』大豆
## 题目背景

大豆 (Soy / Soybean) 非常有前途。

![](https://cdn.luogu.com.cn/upload/image_hosting/60aceba1.png)
## 题目描述

对于一个序列 $\{a\}$，定义其大豆化 (Soybeanization) 序列 $\{b\}$ 由如下操作得到：
1. 初始 $\{b\}$ 和 $\{a\}$ 相等。
2. $n$ 从小到大遍历整个正整数集，对于每个 $n$，进行操作：
   - $i$ 从小到大遍历整个不小于 2 的正整数集，对于每个 $i$，操作 $b_n\gets b_n-b_{\lfloor\frac ni\rfloor}$。
   - 如果 $i>n$，结束过程。

进而，定义一个序列的 $k$-大豆化序列为进行 $k$ 次大豆化操作后得到的序列。

现在给你一个整数序列 $\{t_n\}$，将 $\{t\}$ 复制无穷遍得到序列 $\{a\}$，求 $\{a\}$ 的 $k$-大豆化序列的第 $m$ 项。

序列下标从 1 开始。答案可能很大，对 $23068673$（一个质数）取模。
## 输入格式

第一行，三个正整数 $n,m,k$。

第二行，$n$ 个正整数，描述序列 $\{t\}$。
## 输出格式

一行，表示答案，对 $23068673$ 取模。
## 样例

### 样例输入 #1
```
2 3 1
1 2
```
### 样例输出 #1
```
23068672
```
### 样例输入 #2
```
3 5 2
2 1 2
```
### 样例输出 #2
```
23068666
```
### 样例输入 #3
```
5 1000000000 1
1 5 10 3 2
```
### 样例输出 #3
```
68769

```
### 样例输入 #4
```
5 1000000000 3
1 5 10 3 2
```
### 样例输出 #4
```
5430204
```
## 提示

### 样例解释
**样例 1 解释**

按如下流程构造序列 $\{b\}$：
- $b_1=a_1=1$。
- $b_2=a_2-b_{\lfloor\frac 22\rfloor}=a_2-b_1=1$。 
- $b_3=a_3-b_{\lfloor\frac 32\rfloor}-b_{\lfloor\frac 33\rfloor}=a_3-b_1-b_1=-1$。

从而，答案为 $b_3=-1\equiv 23068672\pmod{23068673}$。

**样例 2 解释**

第一次大豆化后的序列前 5 项：$2,\,-1,\,-2,\,-1,\ -4$。

第二次大豆化后的序列前 5 项：$2,\,-3,\,-6,\,-2,\,-7$。

所以答案为 $-7\equiv 23068666\pmod{23068673}$。
### 数据范围
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{m}\le & \textbf{分值} & \textbf{特殊性质} \\\hline
\textsf{1} & 10^6 & 10 & \\\hline
\textsf{2} & 10^9 & 20 & \\\hline
\textsf{3} & 10^{10} & 20 & k=1  \\\hline
\textsf{4} & 10^{10} & 50 & \\\hline\hline
\end{array}
$$
对于全部数据，$1\le n\le 10^4$，$1\le m\le 10^{10}$，$k\in\{1,2,3\}$，$0\le a_i\le 10^9$。


---

---
title: "「PHOI-1」斗之魂"
layout: "post"
diff: 省选/NOI-
pid: P9551
tag: ['数学', '数论', 'O2优化', '素数判断,质数,筛法', '快速数论变换 NTT']
---
# 「PHOI-1」斗之魂
## 题目背景

**本题数据已加强。**

小 X 忙了一天，于是打起了一款叫斗之魂的游戏。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ha5fx0q.png)
## 题目描述

小 X 要击败 $n$ 个 BOSS，他可以选择以下两种击败 BOSS 的方式：

1. 独自一人击败第 $i$ 个 BOSS 并获得 $k_{i,0}$ 块稀有金属，且保证 $k_{i,0}=k_{i,1}=k_{i,2}$。
2. 和小 Y 一起击败第 $i$ 个 BOSS ，小 X 理应获得 $k_{i,1}$ 块稀有金属，小 Y 理应获得 $k_{i,2}$ 块稀有金属，但是 BOSS 本身实力并没有因为人数的改变而改变，击败难度相对要简单一点，所以系统判定两人实际各获得 $k_{i,0}$ 块稀有金属，其中保证 $\dfrac{1}{k_{i,0}}=\dfrac{1}{k_{i,1}}+\dfrac{1}{k_{i,2}}$。

小 X 已经计划好用第 $b_i$ 种方式击败第 $i$ 个 BOSS，但是考虑到某些因素，小 X 有 $q$ 次询问，每次询问给定一个正整数 $m$，为小 X 击败完所有 BOSS 后获得的稀有金属总数，已知 $k_{i,0},k_{i,1},k_{i,2}$ 均为正整数，求每次询问后所有可能的 $k$ 的值的方案数，两种方案不同当且仅当至少存在一个 $k$ 的值不同，由于这个答案可能很大，你只需要输出它对 $998244353$ 取模后的结果。
## 输入格式

第一行有两个整数 $n$ 和 $q$，分别表示 BOSS 个数和小 X 的询问次数。

第二行有 $n$ 个正整数 $b_i$，表示小 X 用 $b_i$ 种方式击败第 $i$ 个 BOSS。

接下来的 $q$ 行中每行有一个整数 $m$，为该次询问中小 X 击败完所有 BOSS 后获得的稀有金属总数。
## 输出格式

输出共 $q$ 行，第 $i$ 行输出一个答案为当小 X 击败完所有 BOSS 后获得的稀有金属总数为 $m$ 时，所有可能的 $k$ 的值的方案数并对它取模 $998244353$ 后的结果。
## 样例

### 样例输入 #1
```
2 2
2 1
3
4

```
### 样例输出 #1
```
4
7

```
### 样例输入 #2
```
5 5
1 2 1 2 1
4
6
8
10
12

```
### 样例输出 #2
```
0
9
119
630
2210
```
## 提示

**本题采用捆绑测试。**

| Subtask |      $n\le$       |      $m \le$      | $q \le$ |  时限  | 分值 |
| :-----: | :---------------: | :---------------: | :-----: | :----: | :--: |
|   $0$   |       $10$        |       $20$        |   $5$   |  $1s$  | $8$  |
|   $1$   |       $30$        |       $60$        |   $5$   |  $1s$  | $7$  |
|   $2$   |       $40$        |       $100$       | $10^3$  |  $1s$  | $5$  |
|   $3$   |       $150$       |       $500$       | $10^3$  |  $1s$  | $5$  |
|   $4$   |       $200$       |      $5000$       | $10^4$  |  $1s$  | $20$ |
|   $5$   |      $2000$       |  $5 \times 10^4$  | $10^5$  |  $1s$  | $25$ |
|   $6$   | $1.5 \times 10^5$ | $2.5 \times 10^5$ | $10^5$  | $1.8s$ | $30$ |

对于 $100\%$ 的数据，保证 $1 \le n \le 1.5 \times 10^5$，$1 \le m \le 2.5 \times 10^5$，$1 \le b_i \le 2$，$1 \le q \le 10^5$。

### 样例解释 #1：

- 当 $m=3$ 时，所有可能的 $k$ 的值的方案数为 $4$。

    第 $1$ 种：$k_{1,0}=1,k_{1,1}=k_{1,2}=2,k_{2,0}=k_{2,1}=k_{2,2}=2$

    第 $2$ 种：$k_{1,0}=2,k_{1,1}=3,k_{1,2}=6,k_{2,0}=k_{2,1}=k_{2,2}=1$

    第 $3$ 种：$k_{1,0}=2,k_{1,1}=k_{1,2}=4,k_{2,0}=k_{2,1}=k_{2,2}=1$

    第 $4$ 种：$k_{1,0}=2,k_{1,1}=6,k_{1,2}=3,k_{2,0}=k_{2,1}=k_{2,2}=1$

- 当 $m=4$ 时，所有可能的 $k$ 的值的方案数为 $7$。

    第 $1$ 种：$k_{1,0}=1,k_{1,1}=k_{1,2}=2,k_{2,0}=k_{2,1}=k_{2,2}=3$

    第 $2$ 种：$k_{1,0}=2,k_{1,1}=3,k_{1,2}=6,k_{2,0}=k_{2,1}=k_{2,2}=2$

    第 $3$ 种：$k_{1,0}=2,k_{1,1}=k_{1,2}=4,k_{2,0}=k_{2,1}=k_{2,2}=2$

    第 $4$ 种：$k_{1,0}=2,k_{1,1}=6,k_{1,2}=3,k_{2,0}=k_{2,1}=k_{2,2}=2$

    第 $5$ 种：$k_{1,0}=3,k_{1,1}=4,k_{1,2}=12,k_{2,0}=k_{2,1}=k_{2,2}=1$

    第 $6$ 种：$k_{1,0}=3,k_{1,1}=6,k_{1,2}=6,k_{2,0}=k_{2,1}=k_{2,2}=1$

    第 $7$ 种：$k_{1,0}=3,k_{1,1}=12,k_{1,2}=4,k_{2,0}=k_{2,1}=k_{2,2}=1$


---

---
title: "『GROI-R2』 记忆碎片"
layout: "post"
diff: 省选/NOI-
pid: P9654
tag: ['动态规划 DP', '数学', '数论', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 『GROI-R2』 记忆碎片
## 题目描述

记忆的碎片散落在各个角落，而爱丽丝想把它们拼合在一起。

碎片的顺序是给定的，因为记忆显然不能反过来进行。但是，碎片各自的形状和内容是可以打磨和修正的——毕竟所有人的记忆都会歪曲和遗忘。

每个碎片上的记忆都可以用一个**非负整数**来表示。而相邻的两个碎片能够完整地拼合起来，当且仅当它们记忆的和是一个**完全平方数**。

现在，爱丽丝可以打磨若干块碎片，使得每一对相邻的碎片都能够完整地拼合起来。对于每一次打磨，爱丽丝可以选择一块碎片，将这块碎片上的记忆修改为任意一个**非负整数**。爱丽丝想知道，她至少要打磨多少块碎片，才能实现她的目标。同时，她还希望你给出打磨之后，每块碎片上留有的记忆是多少。

**形式化题面**

给定一个**非负整数**序列 $\{a_n\}$，我们定义一次操作是任意选择一个 $i\in [1,n]$ 并将 $a_i$ 改为任意一个**非负整数** $x$。

问至少进行几次操作才可以满足 $\forall i\in [1,n-1]$ 有 $a_i+a_{i+1}$ 为**完全平方数**，并给出修改方案。
## 输入格式

第一行输入一个整数 $n$，表示记忆碎片的个数。

第二行输入一个长度为 $n$ 的非负整数序列 $a$，表示每个记忆碎片上的记忆。
## 输出格式

第一行输出一个整数，表示最少打磨次数。

第二行输出一个长度为 $n$ 的整数序列，表示所有打磨过后的记忆碎片上的记忆。

你必须保证你打磨后的记忆满足题目条件，且与你给出的最少打磨次数相符，并满足每个碎片上的记忆都在 $[0,10^{18}]$ 的范围内。
## 样例

### 样例输入 #1
```
4
1 3 5 8
```
### 样例输出 #1
```
1
1 3 1 8
```
### 样例输入 #2
```
3
3 4 5
```
### 样例输出 #2
```
1
0 4 5
```
## 提示

**样例解释**

对于第一组样例，不难证明爱丽丝至少要打磨一块碎片才能使所有的记忆满足条件。

请一定注意记忆碎片的顺序是不能改变的。

**评分规则**

如果你对于某一测试点输出的最少打磨次数是正确的，你将获得该测试点 $30\%$ 的分数。

如果你在最少打磨次数正确的基础上给出了正确的构造，你将获得该测试点 $100\%$ 的分数。

如果你只会求解最少打磨次数，那也请你在第二行输出以空格隔开的 $n$ 个在 $[0,10^{18}]$ 范围内的整数，否则可能被判为 $0$ 分。

请注意，你在每个 subtask 中得到的 $30\%$ 分数会被下取整计算。

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $2$ | $10^8$ |  | $5$ |
| $2$ | $3$ | $10^8$ |  | $20$ |
| $3$ | $4$ | $10^8$ |  | $15$ |
| $4$ | $10^3$ | $10^8$ |  | $15$ |
| $5$ | $10^6$ | $10^4$ |  | $10$ |
| $6$ | $10^6$ | $10^8$ | $\text{A}$ | $10$ |
| $7$ | $10^6$ | $10^8$ |  | $25$ |

特殊性质 $\text{A}$：$\forall 1\le i,j\le n$ 满足 $a_i=a_j$。

对于 $100\%$ 的数据满足 $1\le n\le 10^6$，$0\le a_i\le 10^8$。


---

---
title: "[ICPC 2021 Macao R] Pass the Ball!"
layout: "post"
diff: 省选/NOI-
pid: P9660
tag: ['2021', '多项式', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Pass the Ball!
## 题目描述

There are $n$ children playing with $n$ balls. Both children and balls are numbered from $1$ to $n$.

Before the game, $n$ integers $p_1, p_2, \cdots, p_n$ are given. In each round of the game, child $i$ will pass the ball he possesses to child $p_i$. It is guaranteed that no child will pass his ball to himself, which means $p_i \neq i$. Moreover, we also know that after each round, each child will hold exactly one ball.

Let $b_i$ be the ball possessed by child $i$. At the beginning of the game, child $i$ ($1 \le i \le n$) will be carrying ball $i$, which means $b_i=i$ initially. You're asked to process $q$ queries. For each query you're given an integer $k$ and you need to compute the value of $\sum\limits_{i=1}^{n} i \times b_i$ after $k$ rounds.
## 输入格式

There is only one test case for each test file.

The first line of the input contains two integers $n$ ($2 \le n \le 10^5$) and $q$ ($1 \le q \le 10^5$), indicating the number of children and the number of queries.

The second line contains $n$ integers $p_1, p_2, \cdots, p_n$ ($1 \le p_i \le n$) indicating how the children pass the balls around.

For the following $q$ lines, the $i$-th line contains one integer $k_i$ ($1 \le k_i \le 10^9$) indicating a query asking for the result after $k_i$ rounds.
## 输出格式

For each query output one line containing one integer indicating the answer.
## 样例

### 样例输入 #1
```
4 4
2 4 1 3
1
2
3
4
```
### 样例输出 #1
```
25
20
25
30
```
## 提示

The sample test case is explained below.

$$
\begin{array}{|c|c|c|c|c|c|} \hline \textbf{Round} & \textbf{b1} & \textbf{b2} & \textbf{b3} & \textbf{b4} & \textbf{Answer} \\\hline 
1 & 3 & 1 & 4 & 2 & 25 \\\hline
2 & 4 & 3 & 2 & 1 & 20 \\\hline
3 & 2 & 4 & 1 & 3 & 25 \\\hline
4 & 1 & 2 & 3 & 4 & 30 \\\hline
\end{array}
$$
## 题目翻译

**【题目描述】**

有 $n$ 个孩子和 $n$ 个球在玩游戏。孩子和球都从 $1$ 编号到 $n$。

游戏开始前，给出了 $n$ 个整数 $p_1, p_2, \cdots, p_n$。在游戏的每一轮中，孩子 $i$ 会把他手里的球传给孩子 $p_i$。保证没有孩子会把他手里的球传给自己，也就是说 $p_i \neq i$。此外，我们还知道在每一轮之后，每个孩子手里都会正好持有一个球。

设 $b_i$ 表示孩子 $i$ 所持有的球。在游戏开始时，孩子 $i$（$1 \le i \le n$）将携带球 $i$，也就是说 $b_i=i$。你需要处理 $q$ 个查询。对于每个查询，你会得到一个整数 $k$，你需要计算在 $k$ 轮后 $\sum\limits_{i=1}^{n} i \times b_i$ 的值。


**【输入格式】**

输入的第一行包含两个整数 $n$（$2 \le n \le 10^5$）和 $q$（$1 \le q \le 10^5$），表示孩子的数量和查询的数量。

第二行包含 $n$ 个整数 $p_1, p_2, \cdots, p_n$（$1 \le p_i \le n$），表示孩子之间传球的方式。

接下来的 $q$ 行中，第 $i$ 行包含一个整数 $k_i$（$1 \le k_i \le 10^9$），表示询问在 $k_i$ 轮后的结果。

**【输出格式】**

对于每个查询，输出一行包含一个整数，表示答案。

**【样例解释】**

示例测试用例解释如下。

$$
\begin{array}{|c|c|c|c|c|c|} \hline \textbf{轮次} & \textbf{b1} & \textbf{b2} & \textbf{b3} & \textbf{b4} & \textbf{答案} \\\hline 
1 & 3 & 1 & 4 & 2 & 25 \\\hline
2 & 4 & 3 & 2 & 1 & 20 \\\hline
3 & 2 & 4 & 1 & 3 & 25 \\\hline
4 & 1 & 2 & 3 & 4 & 30 \\\hline
\end{array}
$$

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

