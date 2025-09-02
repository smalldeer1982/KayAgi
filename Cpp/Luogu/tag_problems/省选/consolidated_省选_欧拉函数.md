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
title: "Dirichlet 半在线卷积"
layout: "post"
diff: 省选/NOI-
pid: P2025
tag: ['洛谷原创', 'Dirichlet 卷积', '欧拉函数']
---
# Dirichlet 半在线卷积
## 题目描述

已知函数 $f$ 满足 $f(1)=1$，且

$$f(n)=\sum_{d|n,d<n}f(d)\varphi(n/d).$$

给定正整数 $n$，试求出 $f(1),f(2),\cdots,f(n)$ 的值。为控制输出量，你只需输出下式的值：

$$\bigoplus_{k=1}^n\left(f(k)\bmod 2^{32}\right). $$

其中 $\oplus$ 代表异或。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个非负整数，代表 $\bigoplus_{k=1}^n\left(f(k)\bmod 2^{32}\right) $ 的值。
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
1000000
```
### 样例输出 #2
```
3527171714
```
### 样例输入 #3
```
10000000
```
### 样例输出 #3
```
191685100
```
## 提示

对于所有数据，$1\le n\le 5\times 10^7$。

对于样例一，$f$ 的前 $10$ 项依次为：$1,1,2,3,4,6,6,9,10,12$。

时限为 std 的 1.5 倍。


---

---
title: "[HAOI2012] 外星人"
layout: "post"
diff: 省选/NOI-
pid: P2350
tag: ['数学', '2012', '河南', '各省省选', '欧拉函数']
---
# [HAOI2012] 外星人
## 题目描述

艾莉欧在她的被子上发现了一个数字 $N$，她觉得只要找出最小的 $x$ 使得，$\varphi^x(N) = 1$。根据这个 $x$ 她就能找到曾经绑架她的外星人的线索了。当然，她是不会去算，请你帮助她算出最小的 $x$。
## 输入格式

第一行一个正整数 $\mathrm{test}$，接下来 $\mathrm{test}$ 组数据每组数据第一行一个正整数 $m$，接下来 $m$ 行每行两个正整数 $p_i, q_i$

其中 $\displaystyle \prod_{i = 1}^{m} p_i^{q_i}$ 为 $N$ 的标准分解形式。

$\prod$ 为连乘

$\varphi^x(N)$ 表示嵌套 $x$ 次，不是幂
## 输出格式

输出 $\mathrm{test}$ 行，每行一个整数，表示答案。
## 样例

### 样例输入 #1
```
1
2
2 2
3 1

```
### 样例输出 #1
```
3

```
## 提示

$30\%$ 的数据，$N \le 10^6$。

$60\%$ 的数据，$x \le 100$。

$100\%$ 的数据，$\mathrm{test} \le 50$，$1 \le p_i \le {10}^5$，$1 \le q_i \le {10}^9$，$m \le 2000$。

$\varphi$ 为欧拉函数，$\varphi(n)$ 即小于等于 $n$ 的数中与 $n$ 互质的数的个数。

提示：$\varphi(\prod_{i=1}^mp_i^{q_i})=\prod_{i=1}^m(p_i-1)*p_i^{q_i-1}$。


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

