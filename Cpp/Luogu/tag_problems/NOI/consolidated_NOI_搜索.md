---
title: "[集训队互测 2023] 虹"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10016
tag: ['集训队互测', '2023', '数论', '深度优先搜索 DFS', '最近公共祖先 LCA', '分块', '位运算']
---
# [集训队互测 2023] 虹
## 题目描述

给定一棵 $n$ 个点的树。

- 称点集 $S$ **连通**，当且仅当 $\forall u,v \in S$，所有 $u$ 到 $v$ 的简单路径上的点均在 $S$ 中。
- 称点集 $S$ 是 $[l,r]$ 的**虹**，当且仅当 $S$ **连通**，且 $S$ 包含 $[l,r]$ 中的所有点。
- 称点集 $S_0$ 是 $[l,r]$ 的**最小虹**，当且仅当 $S_0$ 是 $[l,r]$ 的所有**虹**中大小最小的。可以证明，$S_0$ 是唯一的。

点带权，点 $u$ 的权值为 $w_u$，初始所有点权均为 $0$。同时，给定序列 $\{z_1,z_2,\cdots,z_n\}$。

给定 $q$ 次命令，每次命令形如以下两类之一：

- `1 l r`：令 $S_0$ 为 $[l,r]$ 的**最小虹**，$\forall u \in S_0$，将 $w_u$ 加 $1$。
- `2 l r u`：求 $\left(\sum_{i=l}^r 19901991^{z_{\gcd(i,u)} w_i} \right) \bmod {20242024}$ 的值。
## 输入格式

第一行两个正整数 $n,q$。

第二行 $n$ 个非负整数，依次表示 $z_1,z_2,\cdots,z_n$。

接下来 $n-1$ 行，每行两个正整数 $u,v$，描述一条树上从 $u$ 到 $v$ 的边。

最后 $q$ 行，每行 $3$ 或 $4$ 个正整数，描述一次命令。

**注意：本题输入文件行末有 `\r`，请选手自行过滤。**
## 输出格式

对于每次询问（即第二类命令）输出答案。
## 样例

### 样例输入 #1
```
5 4
1 0 0 0 1
1 2
1 3
3 4
3 5
1 2 3
2 1 3 3
1 4 5
2 3 5 3
```
### 样例输出 #1
```
19561959
19561959
```
## 提示

**本题采用捆绑测试**。

对于所有测试数据保证：$1 \le n, q \le 8 \times 10^4,0 \le z_i \le 10^9$，所有命令满足 $1 \le l \le r \le n, 1 \le u \le n$，**保证第一类命令的 $(l,r)$ 随机生成**。随机生成方式如下：
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $l$。
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $r$。
- 若 $l>r$，则交换 $l,r$。

| 子任务编号 | 分值 | $n \le$ | $q \le$ | 特殊性质 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :----------: |
| $1$ | $10$ | $10^3$ | $10^3$ | 无 | 无 |
| $2$ | $20$ | $65536$ | $65536$ | A, B | 无 |
| $3$ | $20$ | $65536$ | $65536$ | A | 依赖于子任务 $2$ |
| $4$ | $30$ | $65536$ | $65536$ | 无 | 依赖于子任务 $1,2,3$ |
| $5$ | $20$ | $80000$ | $80000$ | 无 | 依赖于子任务 $1,2,3,4$ |

特殊性质 A：保证所有第二类命令均在所有第一类命令之后。

特殊性质 B：保证第二类命令次数 $\le 20$。


---

---
title: "【MX-X5-T7】「GFOI Round 1」Der Richter"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11135
tag: ['搜索', 'Special Judge', 'O2优化', '剪枝', '状压 DP', '梦熊比赛']
---
# 【MX-X5-T7】「GFOI Round 1」Der Richter
## 题目背景

原题链接：<https://oier.team/problems/X5H>。

---

> [Der Richter - Ωμεγα](https://www.bilibili.com/video/BV11SpberEjC/)
## 题目描述

我们首先给出关于本题的一些定义。

定义一个 $1 \sim n$ 的排列 $p_1, p_2, \ldots, p_n$ 是**好的**，当且仅当 $\exists k \in [1, n - 1], \max\limits_{i = 1}^k p_i = k$。

定义一个序列 $x_1, x_2, \ldots, x_k$ 是一个排列 $p_1, p_2, \ldots, p_n$ 的**交换方案**，当且仅当：

- $\forall 1 \le i \le k$，$1 \le x_i \le n - 1$ 且 $x_i$ 是整数；
- 对所有 $i = 1 \sim k$ **依次**执行交换 $p$ 中 $x_i$ 和 $x_i + 1$ 位置上的数的操作之后，$p$ 是**好的**。

特别地，序列 $x$ 可以为空，代表不进行任何交换操作。

定义一个序列 $x_1, x_2, \ldots, x_k$ 是一个排列 $p_1, p_2, \ldots, p_n$ 的**关键交换方案**，当且仅当：

- $x$ 是 $p$ 的一个**交换方案**；
- $x$ 是 $p$ 的所有**交换方案**中长度最小的。

定义 $f(p)$ 为排列 $p$ 的不同的**关键交换方案**的个数。

定义一个排列 $q$ 是另一个排列 $p$ 的一个**终态**，当且仅当：

- $p$ 的长度与 $q$ 相等；
- $q$ 是**好的**；
- 存在一个 $p$ 的**关键交换方案** $x_1, x_2, \ldots, x_k$，使得对所有 $i = 1 \sim k$ **依次**执行交换 $p$ 中 $x_i$ 和 $x_i + 1$ 位置上的数的操作之后，$p$ 与 $q$ 相同（即 $\forall 1 \le i \le |p|, p_i = q_i$）。

定义一个排列 $p$ 是**极好的**，当且仅当只存在**一个**排列 $q$，使得 $q$ 是 $p$ 的**终态**。

给定一个**质数** $P$ 和 $q$ 次询问，每次询问给定两个整数 $n, m$，你需要构造任意一个**极好的**长度为 $n$ 且 $f(p) \equiv m \pmod P$ 的 $1 \sim n$ 的排列 $p$，或报告无解。

本题将使用**自定义校验器**检查你构造的排列是否正确，即若有解输出任意一个满足要求的排列都会被认为通过。
## 输入格式

第一行输入两个正整数 $q, P$，表示询问次数和模数。

接下来 $q$ 行，每行包含两个整数 $n, m$。
## 输出格式

对于每次询问：

- 若无解输出一行一个整数 $-1$；
- 否则输出一行 $n$ 个整数，表示任意一个符合要求的 $1 \sim n$ 的排列 $p_1, p_2, \ldots, p_n$。

本题将使用**自定义校验器**检查你构造的排列是否正确，即若有解输出任意一个满足要求的排列都会被认为通过。
## 样例

### 样例输入 #1
```
5 998244353
5 1
6 1
6 2
6 3
10 20

```
### 样例输出 #1
```
4 1 5 3 2
5 4 3 2 1 6
3 6 2 5 1 4
-1
5 10 4 3 2 9 8 7 1 6

```
## 提示

**【样例解释】**

对于第一次询问，排列 $p = [4, 1, 5, 3, 2]$ 的**关键交换方案**只有 $x = [1]$，且因为 $p$ 的**终态**只有 $q = [1, 4, 5, 3, 2]$ 所以 $p$ 是**极好的**。

对于第二次询问，排列 $p = [5, 4, 3, 2, 1, 6]$ 的**关键交换方案**只有 $x = []$，且因为 $p$ 的**终态**只有 $q = [5, 4, 3, 2, 1, 6]$ 所以 $p$ 是**极好的**。

对于第三次询问，排列 $p = [3, 6, 2, 5, 1, 4]$ 的**关键交换方案**有 $x = [2, 4, 3]$ 和 $x = [4, 2, 3]$，且因为 $p$ 的**终态**只有 $q = [3, 2, 1, 6, 5, 4]$ 所以 $p$ 是**极好的**。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n \le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $8$ | 无 | $17$ |
| $2$ | $50$ | A | $3$ |
| $3$ | $50$ | B | $3$ |
| $4$ | $18$ | 无 | $19$ |
| $5$ | $40$ | 无 | $16$ |
| $6$ | $50$ | 无 | $9$ |
| $7$ | $60$ | 无 | $10$ |
| $8$ | $70$ | 无 | $11$ |
| $9$ | $80$ | 无 | $12$ |

- 特殊性质 A：$m = 0$。
- 特殊性质 B：$m = 1$。

对于所有数据，满足 $1 \le q \le 10^4$，$9 \times 10^8 < P < 10^9$，$2 \le n \le 80$，$0 \le m < P$，$P$ 是**质数**。


---

---
title: "[CSP-S 2024] 擂台游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11234
tag: ['贪心', '递归', '2024', 'O2优化', '深度优先搜索 DFS', '树形 DP', '差分', 'CSP-S 提高级']
---
# [CSP-S 2024] 擂台游戏
## 题目描述

小 S 想要举办一场擂台游戏，如果共有 $2^k$ 名选手参加，那么游戏分为 $k$ 轮进行：

- 第一轮编号为 $1, 2$ 的选手进行一次对局，编号为 $3, 4$ 的选手进行一次对局，以此类推，编号为 $2^k - 1, 2^k$ 的选手进行一次对局。
- 第二轮在只保留第一轮的胜者的前提下，相邻的两位依次进行一场对局。
- 以此类推，第 $k - 1$ 轮在只保留第 $k - 2$ 轮的 $4$ 位胜者的前提下，前两位、后两位分别进行对局，也就是所谓的半决赛。
- 第 $k$ 轮即为半决赛两位胜者的决赛。

确定了游戏晋级的规则后，小 S 将比赛的规则设置为了擂台赛。具体而言，每位选手都有一个能力值 $a_1, a_2, \dots , a_{2^k}$，能力值为 $[0,2^{31}-1]$ 之内的整数。对于每场比赛，会先抽签决定一个数 $0/1$，我们将第 $R$ 轮的第 $G$ 场比赛抽到的数记为 $d_{R,G}$。抽到 $0$ 则表示表示编号小的选手为擂主，抽到 $1$ 则表示编号大的选手为擂主。擂主获胜当且仅当他的能力值 $a\geq R$。也就是说，游戏的胜负只取决于**擂主的能力值**与**当前比赛是第几轮**的大小关系，**与另一位的能力值无关**。

现在，小 S 先后陆续收到了 $n$ 位选手的报名信息，他们分别告知了小 S 自己的能力值。小 S 会按照报名的先后顺序对选手进行编号为 $1, 2, \dots, n$。小 S 关心的是，补充**尽量少**的选手使总人数为 $2$ 的整次幂，且所有选手进行一次完整的擂台游戏后，所有可能成为总冠军的选手的**编号之和**是多少。

形式化地，设 $k$ 是最小的非负整数使得 $2^k\geq n$，那么应当补充 $(2^k-n)$ 名选手，且补充的选手的能力值可以任取 $[0,2^{31}-1]$ 之内的整数。**如果补充的选手有可能取胜，也应当计入答案中**。

当然小 S 觉得这个问题还是太简单了，所以他给了你 $m$ 个询问 $c_1,c_2,\dots,c_m$。小 S 希望你帮忙对于每个 $c_i$ 求出，在只收到前 $c_i$ 位选手的报名信息时，这个问题的答案是多少。
## 输入格式

**本题的测试点包含有多组测试数据。** 但不同测试数据只是通过修改 $a_1, a_2, \dots , a_n$ 得到，其他内容均保持不变，请参考以下格式。其中 $\oplus$ 代表异或运算符，$a \bmod b$ 代表 $a$ 除以 $b$ 的余数。

输入的第一行包含两个正整数 $n, m$，表示报名的选手数量和询问的数量。

输入的第二行包含 $n$ 个非负整数 $a'_1,a'_2,\dots,a'_n$，这列数将用来计算真正的能力值。

输入的第三行包含 $m$ 个正整数 $c_1, c_2, \dots , c_m$，表示询问。

设 $K$ 是使得 $2^K \geq n$ 的最小的非负整数，接下来的 $K$ 行当中，第 $R$ 行包含 $2^{K-R}$ 个数（无空格），其中第 $G$ 个数表示第 $R$ 轮的第 $G$ 场比赛抽签得到的 $d_{R,G}=0/1$。

注意，由于询问只是将人数凑齐到 $2^k\geq c_i$，这里的 $k\leq K$，因此你未必会用到全部的输入值。

接下来一行包含一个正整数 $T$，表示有 $T$ 组测试数据。

接下来共 $T$ 行，每行描述一组数据，包含 $4$ 个非负整数 $X_0,X_1,X_2,X_3$，该组数据的能力值 $a_i=a'_i \oplus X_{i\bmod 4}$，其中 $1\leq i\leq n$。
## 输出格式

共输出 $T$ 行，对于每组数据，设 $A_i$ 为第 $i$（$1 \leq i \leq m$）组询问的答案，你只需要输出一行包含一个整数，表示 $(1\times A_1) \oplus (2\times A_2) \oplus \dots \oplus (m\times A_m)$ 的结果。
## 样例

### 样例输入 #1
```
5 5
0 0 0 0 0
5 4 1 2 3
1001
10
1
4
2 1 0 0
1 2 1 0
0 2 3 1
2 2 0 1
```
### 样例输出 #1
```
5
19
7
1
```
## 提示

**【样例 1 解释】**

共有 $T = 4$ 组数据，这里只解释第一组。$5$ 名选手的真实能力值为 $[1, 0, 0, 2, 1]$。$5$ 组询问分别是对长度为 $5, 4, 1, 2, 3$ 的前缀进行的。

1. 对于长度为 $1$ 的前缀，由于只有 $1$ 号一个人，因此答案为 $1$。
2. 对于长度为 $2$ 的前缀，由于 $2$ 个人已经是 $2$ 的幂次，因此不需要进行扩充。根据抽签 $d_{1,1} = 1$ 可知 $2$ 号为擂主，由于 $a_2 < 1$，因此 $1$ 号获胜，答案为 $1$。
3. 对于长度为 $3$ 的前缀，首先 $1$ 号、$2$ 号比赛是 $1$ 号获胜（因为 $d_{1,1} = 1$，故 $2$ 号为擂主，$a_2 < 1$），然后虽然 $4$ 号能力值还不知道，但 $3$ 号、$4$ 号比赛一定是 $4$ 号获胜（因为 $d_{1,2} = 0$，故 $3$ 号为擂主，$a_3 < 1$），而决赛 $1$ 号、$4$ 号谁获胜都有可能（因为 $d_{2,1} = 1$，故 $4$ 号为擂主，如果 $a_4 < 2$ 则 $1$ 号获胜，$a_4 \geq 2$ 则 $4$ 号获胜）。综上所述，答案为 $1 + 4 = 5$。
4. 对于长度为 $4$ 的前缀，我们根据上一条的分析得知，由于 $a_4 \geq 2$ ，所以决赛获胜的是 $4$ 号。
5. 对于长度为 $5$ 的前缀，可以证明，可能获胜的选手包括 $4$ 号、$7$ 号、$8$ 号，答案为 $19$。

因此，该组测试数据的答案为 $(1 \times 19) \oplus (2 \times 4) \oplus (3 \times 1) \oplus (4 \times 1) \oplus (5 \times 5) = 5$。

**【样例 2】**

见选手目录下的 arena/arena2.in 与 arena/arena2.ans。

这组样例满足特殊性质 A。

**【样例 3】**

见选手目录下的 arena/arena3.in 与 arena/arena3.ans。

这组样例满足特殊性质 B。

**【样例 4】**

见选手目录下的 arena/arena4.in 与 arena/arena4.ans。

**【样例 5】**

见选手目录下的 arena/arena5.in 与 arena/arena5.ans。

**【数据范围】**

对于所有测试数据，保证：$2 \leq n, m \leq 10^5$，$0 \leq a_i, X_j < 2^{31}$，$1 \leq c_i \leq n$，$1 \leq T \leq 256$。

| 测试点 | $T=$ | $n,m\leq$ | 特殊性质 A | 特殊性质 B |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim 3$ | $1$ | $8$ | 否 | 否 |
| $4,5$ | $1$ | $500$ | 是 | 否 |
| $6\sim 8$ | $1$ | $500$ | 否 | 是 |
| $9,10$ | $1$ | $5000$ | 否 | 否 |
| $11,12$ | $1$ | $10^5$ | 是 | 否 |
| $13\sim 15$ | $1$ | $10^5$ | 否 | 是 |
| $16,17$ | $4$ | $10^5$ | 否 | 否 |
| $18,19$ | $16$ | $10^5$ | 否 | 否 |
| $20,21$ | $64$ | $10^5$ | 否 | 否 |
| $22,23$ | $128$ | $10^5$ | 否 | 否 |
| $24,25$ | $256$ | $10^5$ | 否 | 否 |


特殊性质 A：保证询问的 $c_i$ 均为 $2$ 的幂次。

特殊性质 B：保证所有的 $d_{R,G} = 0$。


---

---
title: "[Sloi 2024]D1T2 简单的反链求和问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11418
tag: ['搜索', '数学', '数论']
---
# [Sloi 2024]D1T2 简单的反链求和问题
## 题目背景

本题 **idea from**：[Projecteuler P386](https://pe-cn.github.io/386/).

![](https://cdn.luogu.com.cn/upload/image_hosting/0yeo7vce.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8r5uh8th.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/h7syotrv.png)

图源：[zhihu](https://www.zhihu.com/question/19813666/answer/45229974).
## 题目描述

反链是序理论中的一个极其优美的结构。

---

给定正整数 $n$，记 $S(n)$ 为 $n$ 的约数构成的集合。

若 $S(n)$ 的子集 $A$ 只包含一个元素，或者 $A$ 中任意一个元素均不能整除其它元素，则称 $A$ 为 $S(n)$ 的**反链**。

例如：$S(30) = \{1, 2, 3, 5, 6, 10, 15, 30\}$。

- $\{2, 5, 6\}$ 不是 $S(30)$ 的反链。

- $\{2, 3, 5\}$ 是 $S(30)$ 的反链。

**hhoppitree** 喜欢长的反链，记 $f(n)$ 表示 $S(n)$ 的最长反链长度，她需要你帮忙求出 $ans=\sum\limits_{k=1}^n f(k)$。

~~如果做不出来，她就会喵的一声扑向你~~
## 输入格式

一行一个正整数表示 $n$。
## 输出格式

一行一个正整数表示 $ans$。

**可以证明答案一定在 `long long` 范围内。**
## 样例

### 样例输入 #1
```
10

```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
20
```
### 样例输出 #2
```
27
```
### 样例输入 #3
```
2347
```
### 样例输出 #3
```
6126
```
### 样例输入 #4
```
9234799
```
### 样例输出 #4
```
43445933
```
### 样例输入 #5
```
99234799
```
### 样例输出 #5
```
524524311
```
### 样例输入 #6
```
1000000000
```
### 样例输出 #6
```
5844921982
```
### 样例输入 #7
```
23477145069
```
### 样例输出 #7
```
154961952468
```
## 提示

样例 $1$：除了 $f(6)=f(10)=2$，其余 $f(k)=1(1\le k\le 10)$。

样例 $2$：除了 $f(6)=f(10)=f(12)=f(14)=f(15)=f(18)=f(20)=2$，其余 $f(k)=1(1\le k\le 20)$。

---

**本题采用捆绑测试**

对于所有测试数据，保证 $1\le n\le 123477145069\approx 1.2\times 10^{11}$。

**可以证明答案一定在 `long long` 范围内。**

|Subtask	| $n \le$ | Score |
| :--: | :--: | :--: |
|$1$ | $10$ | $5$ |
|$2$ | $2500$ | $5$ |
|$3$ | $10^6$ | $10$ |
|$4$ | $10^7$ | $10$ |
|$5$ | $10^8$ | $10$ |
|$6$ | $10^9$ | $20$ |
|$7$ | $23477145069$ | $20$ |
|$8$ | $123477145069$ | $20$ |


---

---
title: "基础构造练习题 2（P11635 加强版）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12081
tag: ['搜索', '网络流', '交互题', 'Special Judge', '剪枝', '通信题']
---
# 基础构造练习题 2（P11635 加强版）
## 题目背景

本题较 P11635（CTS 2025 Day 2 T2）添加了 $K = 8, 9, 10$ 的情形，并提高了 $K = 6, 7$ 时 $N$ 的限制。注意：P11635 的所有 `unsigned int` 需要修改为 `unsigned long long`。
## 题目描述

**这是一道通信题。**

有若干个节点，它们一开始分别存储有一个数字 $a_i \in \{0, 1\}$，它们想要通过 $K$ 轮通信知道其它每个节点存储的数字。

每一轮通信开始的时候，每个节点 $i$ 对每个节点 $j$，都会选择一个数字 $c_{i,j} \in \{0, 1\}$，表示它将会向节点 $j$ 发送数字 $c_{i,j}$，而在这轮通信结束的时候，节点 $j$ 会收到所有节点向它发送的数字的和，具体而言节点 $j$ 会收到一个数字 $s_j = \sum_{i} c_{i,j}$。

现在给定 $K$，你需要找到一个尽量大的 $N$，满足在通过 $K$ 轮通信之后每个节点都可以知道所有节点存储的数字。

### 实现细节

**你不需要，也不应该实现 `main` 函数。**

你需要实现以下函数：

1. `int init(int K);`
   - 该函数传入通信总轮数 $K$ 的值。**保证** $1 \leq K \leq 10$。
   - 该函数需要返回你选择的节点数量 $N$，**你需要保证** $1 \leq N \leq 60$。
   - 对于每次代码运行，**保证在任意 `send` 函数调用前，该函数会被交互库调用恰好一次**。

2. `unsigned long long send(int K, int N, int round, int number, const std::vector<int>& received);`
   - 该函数传入通信总轮数 $K$，你实现的 `init` 函数返回的节点数量 $N$，当前通信的轮数 `round`，当前你需要实现的节点的编号 `number`，当前节点之前通信的轮数中收到的数字 `received`，其中 `received[0]` 表示这个节点一开始存储的数字，而 `received[i] (1 \leq i < \text{round})` 表示这个节点第 $i$ 轮通信结束的时候收到的数字。**保证** $1 \leq K \leq 10$，$1 \leq \text{round} \leq K + 1$，$0 \leq \text{number} < N$，**且 `received` 的长度为 `round`**。
   - 若 $1 \leq \text{round} \leq K$，你需要返回一个无符号 $64$ 位整数 $x$ 表示在这轮通信中节点 `number` 发送给所有节点的数字，其中 $x$ 的第 $i$ 位为节点 `number` 发送给节点 $i$ 的数字，高位用 $0$ 补齐。
   - 若 $\text{round} = K + 1$，你需要返回一个无符号 $64$ 位整数 $x$ 表示节点 `number` 经过 $K$ 轮通信后确定的每个节点存储的数字，其中 $x$ 的第 $i$ 位为编号为 $i$ 的节点存储的数字，高位用 $0$ 补齐。
   - 对于每次代码运行，**保证该函数会被交互库调用不超过 $10^5$ 次**。

注意：你需要保证，对于任意两次传入参数相同的函数调用（包括 `init` 和 `send`），返回值也应当相同，否则你的程序将会直接被判定为错误。

题目保证在规定的限制下，交互库在每次代码运行中的运行时间不会超过 $100\, \mathrm{ms}$；交互库使用的内存大小固定，且不超过 $64\, \mathrm{MiB}$。这意味着在每次代码运行中你的代码可以使用至少 $900\, \mathrm{ms}$ 的时间和 $448\,\mathrm{MiB}$ 的空间。

## 提示

### 测试程序方式

**下发文件中的 `grader.cpp` 是提供的交互库参考实现，最终测试时所用的交互库实现与该参考实现有所不同，因此你的解法不应该依赖交互库实现。**

将你的程序命名为 `message.cpp` 并放置于下发文件目录下后，你可以在下发文件目录下使用如下命令进行测试：

```bash
g++ grader.cpp message.cpp -o grader -std=c++17 -O2
./grader
```

上述脚本将从**标准输入**读入以下格式的数据：

- 输入的第一行一个整数 $0$。
- 输入的第二行两个正整数 $T, K$，其中 $T$ 表示进行通信的次数，$K$ 表示每次通信的轮数。你需要保证 $1 \leq T \leq 101$，$1 \leq K \leq 10$。
- 输入的第 $i + 2 (0 \leq i < T)$ 行一个无符号 $64$ 位整数 $x_i$，表示第 $i$ 次通信时每个节点初始存储的数字，其中 $x_i$ 的第 $j$ 位表示 $j$ 号节点初始存储的数字。你需要保证 $\forall 0 \leq i < T, 0 \leq x_i < 2^{64}$。

上述脚本将输出以下格式的数据到**标准输出**：

- 若通信结果正确，则输出 `Accepted! (N = [N], K = [K])`；
- 若通信结果错误，则输出 `Wrong answer!`。

### 下发文件说明

在下发文件中：

1. `grader.cpp` 是提供的交互库参考实现。
2. `template_message.cpp` 是提供的示例代码，你可以在此代码的基础上实现。

### 子任务

本题共有 $10$ 个子任务，每个子任务分值为 $100$ 分，总分为 $1000$ 分。一个子任务的得分为其中所有测试点的得分最小值。

对于所有测试数据，保证 $1 \leq K \leq 10$，且对于每次代码运行，`send` 会被交互库调用不超过 $10^5$ 次。**对于第 $i$ 个子任务，保证 $K = i$。**

### 评分方式

**注意**：

- 你不应当通过非法方式获取交互库的内部信息，如试图直接读取交互库中存储的值，或直接与标准输入、输出流进行交互。此类行为将被视为作弊；
- **最终的评测交互库与样例交互库的实现有所不同，因此你的解法不应该依赖交互库实现。**

**本题首先会受到和传统题相同的限制**，例如编译错误会导致整道题目得 0 分，运行时错误、超过时间限制、超过空间限制等会导致相应测试点得 0 分等。你只能在程序中访问自己定义的和交互库给出的变量及其对应的内存空间，尝试访问其他空间将可能导致编译错误或运行错误。

在上述条件基础上，在每个测试点中，程序得到的分数将按照以下方式计算：

- 若对于任意两次传入参数相同的该函数调用，返回值不同，则获得 0 分；
- 若 $K$ 轮通信后确定的每个节点存储的数字与每个节点初始存储的数字不同，则获得 0 分；
- 否则设 $N$ 为调用函数 `init()` 得到的结果，则该测试点的得分为 $s \times {0.7}^{\max(C(K) - N, 0)}$，其中 $s$ 为该测试点的分值，$C(K)$ 的计算方式如下表所示：

| 子任务编号 $= K =$ | $C(K) =$ |
| :-: | :-: |
| $1$ | $2$ |
| $2$ | $4$ |
| $3$ | $6$ |
| $4$ | $11$ |
| $5$ | $14$ |
| $6$ | $22$ |
| $7$ | $26$ |
| $8$ | $36$ |
| $9$ | $41$ |
| $10$ | $47$ |



---

---
title: "[GCJ Farewell Round #4] Hey Google, Drive!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12963
tag: ['2023', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ Farewell Round #4] Hey Google, Drive!
## 题目描述

The Google Assistant and Android Auto teams are collaborating on a new prototype car that can be driven via voice commands. The early prototype works through a phone connected to a car simulator. Unfortunately, one of the early testers dropped their phone in the toilet, damaging the microphone and making it harder to use the new feature. Since they do not want to miss out on the opportunity, they want your help to use it anyway.

The early prototype moves on a simple grid of $\mathbf{R}$ rows and $\mathbf{C}$ columns and only understands 4 very simple voice commands: north, south, east, and west. Each command makes the car try to move exactly one cell in the corresponding direction. Because of the microphone issues, however, the system may mishear and interchange north and south, and separately, east and west. That means that a command of north may make the car move north or south, a command of south may make the car move south or north, and similarly both commands east and west may make the car move east or west when issued. In all cases, both movement options can happen with equal probability $(1 / 2)$.

The tester set up a driving grid such that each cell can contain either a wall, a hazard, or be empty. If a command would make the car move into a wall, or outside the grid, it does nothing instead. If a command makes the car move into a hazard, the car cannot execute any more commands.

The tester has marked some empty cells of the grid as interesting starts and others as interesting finishes. A pair of an interesting start and an interesting finish is drivable if there is a strategy to drive the car through voice commands from the start that makes it end at the finish with probability at least $1-10^{-100}$. A strategy can choose which command to issue and when to stop depending on the outcome of the previous commands. Notice that if the car moves into a hazard it stops moving, so it cannot make it to the finish. The tester wants your help finding the list of all drivable pairs.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns of the grid. Then, $\mathbf{R}$ lines follow containing a string of $\mathbf{C}$ characters each. The $j$-th character on the $i$-th of these lines $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$ represents the grid in the $i$-th row and $j$-th column as follows:

*   A period (. ) represents an uninteresting empty cell.
*   A hash symbol (#) represents a cell containing a wall.
*   An asterisk (*) represents a cell containing a hazard.
*   An English lowercase letter (a through z) represents an empty cell that is an interesting start.
*   An English uppercase letter (A through z) represents an empty cell that is an interesting finish.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is NONE if there are no drivable pairs. Otherwise, $y$ must be a series of 2 character strings separated by spaces, representing all drivable pairs with the start letter first and the finish letter second, in alphabetical order.
## 样例

### 样例输入 #1
```
4
1 2
aZ
4 4
a..c
**.*
.Y.#
bX#Z
2 2
a*
*Z
2 7
a*bcd*.
...*F#.
```
### 样例输出 #1
```
Case #1: aZ
Case #2: aY bX bY cY
Case #3: NONE
Case #4: dF
```
## 提示

**Sample Explanation**

In Sample Case #1, simply repeating the west command until reaching the finish is a viable strategy. Each time there is a $1 / 2$ probability of reaching the finish and a $1 / 2$ probability of staying in the same place. Thus, the probability of not reaching the finish in $10^{101}$ or fewer steps is $2^{-10^{101}}<10^{-10^{100}}$.

In Sample Case #2 a similar strategy as in Sample Case #1 can be used to get the car from any position in the top row (1) to any other with probability as high as desired, and similarly for all non-wall positions in the third row from the top (2). Analogously, but using the south command, the car can move between non-wall positions on the third column from the left (3).

From both a and c we can use (1) to get to the third column from the left, then (3) to get right next to $\mathrm{Y}$ and then (2) to get to $\mathrm{Y}$ making both $\mathrm{aY}$ and $\mathrm{cY}$ drivable. Notice, however, that safely using the north or south commands from the third row can only be done in the third column, or otherwise the car may go into a hazard. Therefore, there is no safe way to move the car from the third to the fourth row, making $\mathrm{aX}$ and $\mathrm{cX}$ not drivable.

From $\mathrm{b}$, however, the car can use a similar strategy to get to $\mathrm{x}$, and from $\mathrm{x}$ the car can get to $\mathrm{Y}$ by using the north or south command repeatedly (and stop when reaching $\mathrm{Y}$, never risking going into the hazard above).

Finally, the finish $\mathrm{z}$ is completely isolated, so it cannot be part of a drivable pair.

In Sample Case #3, every path from the interesting start to the interesting finish goes through a hazard, which makes the pair not drivable.

In Sample Case #4, only the interesting start $\mathrm{d}$ has a viable strategy to get to the finish $\mathrm{F}$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$ is either a period (.), a hash symbol (#), an asterisk (*) or a lowercase or uppercase English letter, for all $i, j$.
- The set $\left\{\mathbf{G}_{\mathbf{i}, \mathbf{j}}\right.$ for all $\left.i, j\right\}$ contains at least 1 lowercase and at least 1 uppercase English letter.
- Each lowercase and uppercase letter appears at most once among all $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$.

**Test Set 1 (5 Pts, Visible Verdict)**

- $1 \leq \mathbf{R} \leq 20$.
- $1 \leq \mathbf{C} \leq 20$.

**Test Set 2 (17 Pts, Hidden Verdict)**

- $1 \leq \mathbf{R} \leq 100$.
- $1 \leq \mathbf{C} \leq 100$.


---

---
title: "【MX-X13-T7】「KDOI-12」No one can be anything without comparison."
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13012
tag: ['O2优化', '深度优先搜索 DFS', '树论', '前缀和', '分块', '梦熊比赛']
---
# 【MX-X13-T7】「KDOI-12」No one can be anything without comparison.
## 题目描述

**请注意本题对 $\bm{n,k}$ 的特殊限制。**

$n$ 名选手参加了 $k$ 场 Tetris Tournament。每一场 Tetris Tournament 包含 $n-1$ 轮，每轮会选出两个目前还未淘汰的选手 $x,y$ 并让他们参加一场比赛，输的人淘汰。最后会有唯一胜者。你现在得知第 $j$ 个人在第 $i$ 场 Tetris Tournament 中被 $a_{i,j}$ 淘汰了。$j$ 是第 $i$ 场 Tetris Tournament 的胜者当且仅当 $a_{i,j}=0$。

选手们喜欢比较。他们都希望自己在某种意义上能够胜过别人，或至少跟别人水平差不多。

定义第 $i$ 场 Tetris Tournament 中 $x$ 严格吊打 $y$ 当且仅当存在 $x=p_1,p_2,\dots,p_m=y$（$m\ge 2$，也就是说 $x\neq y$），使得对于任意 $1\leq j<m$，$a_{i,p_{j+1}}=p_j$。

定义一个有序的选手 $k$ 元组 $(i_1,i_2,\dots,i_k)$ 是水平相似的当且仅当对于 $1\leq j<k$，$i_j$ 在第 $j$ 场比赛中严格吊打 $i_{j+1}$ 且 $i_k$ 在第 $k$ 场比赛中严格吊打 $i_1$。

求水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 输入格式

第一行，两个正整数 $n,k$。**保证 $\bm{3\leq k\leq 5}$**。

接下来 $k$ 行，第 $i$ 行 $n$ 个非负整数 $a_{i,1}, \ldots, a_{i,n}$。
## 输出格式

仅一行，一个非负整数，表示水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3 3
0 1 2
3 0 2
3 1 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 5
0 1 1 2 3 4
3 3 0 6 6 1
2 4 1 0 1 1
3 0 2 6 6 2
5 3 6 1 0 4
```
### 样例输出 #2
```
18
```
## 提示

**【样例解释 \#1】**

符合要求的三元组 $(i_1,i_2,i_3)$ 有：$(1,2,3)$，$(2,3,1)$。

**【数据范围】**

**本题使用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | $k=$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $7$ | $100$ | $3$ | 无 |
| $2$ | $8$ | $500$ | $3$ | 无 |
| $3$ | $13$ | $3\times10^3$ | $3$ | 无 |
| $4$ | $14$ | $2.5\times10^5$ | $3$ | A |
| $5$ | $15$ | $10^5$ | $3$ | B |
| $6$ | $7$ | $10^5$ | $3$ | 无 |
| $7$ | $14$ | $2.5\times10^5$ | $3$ | 无 |
| $8$ | $7$ | $5\times10^4$ | $4$ | 无 |
| $9$ | $6$ | $7.5\times10^4$ | $4$ | 无 |
| $10$ | $9$ | $4\times10^4$ | $5$ | 无 |

* 特殊性质 A：对于 $1\leq i\leq n$，$a_{1,i}=a_{2,i}$；
* 特殊性质 B：对于 $1\leq i\leq k$，不存在 $1\leq j_1<j_2\leq n$ 使得 $a_{i,j_1}=a_{i,j_2}$。

对于所有数据：$1\leq n\leq2.5\times10^5$，$\bm{3\leq k\leq 5}$，保证 $a$ 数组符合题意，且：

* $k=3$ 时，$n\leq2.5\times10^5$；
* $k=4$ 时：$n\leq7.5\times10^4$；
* $k=5$ 时：$n\leq4\times10^4$。


---

---
title: "[GCJ 2019 Finals] Won't sum? Must now"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13125
tag: ['搜索', '数学', '2019', 'Special Judge', '剪枝', '数位 DP', 'Google Code Jam']
---
# [GCJ 2019 Finals] Won't sum? Must now
## 题目描述

In 2016, it was shown that every positive integer can be written as the sum of three or fewer palindromic terms. For the purposes of this problem, a palindromic term is a string of digits (with no leading zeroes) that represents a positive integer and reads the same forward and backward.

Given a positive integer $\mathbf{S}$, find $\mathbf{K}$ palindromic terms that sum to $\mathbf{S}$, such that $\mathbf{K}$ is minimized.
## 输入格式

The first line of input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ lines follow, each containing a positive integer $\mathbf{S}$.

## 输出格式

For each test case, output one line of the form Case #x: $A_1$ (if only one term is needed), Case #x: $A_1$ $A_2$ (if only two terms are needed), or Case #x: $A_1$ $A_2$ $A_3$ (if three terms are needed), where $x$ is the case number (counting starting from 1), each $A_i$ is a palindromic term (as described above), and the sum of the $A_i$s equals $\mathbf{S}$.

## 样例

### 样例输入 #1
```
3
1
198
1234567890
```
### 样例输出 #1
```
Case #1: 1
Case #2: 191 7
Case #3: 672787276 94449 561686165
```
## 提示

**Sample Explanation**

In Sample Case #1, the input is already a palindrome.

In Sample Case #2, note that `99 99`, for example, would also be an acceptable answer. Even though there are multiple instances of 99, they count as separate terms, so this solution uses the same number of terms as 191 7.

Also note that `191 07`, `181 8 9`, `0110 88`, `101 97`, `7.0 191.0`, and `-202 4`, for example, would not be acceptable answers.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.

**Test set 1 (5 Pts, Visible)**

- $1 \leq \mathbf{S} \leq 10^{10}$.

**Test set 2 (22 Pts, Hidden)**

- $1 \leq \mathbf{S} \leq 10^{40}$.


---

---
title: "[GCJ 2017 Finals] Stack Management"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13183
tag: ['图论', '2017', '深度优先搜索 DFS', '图论建模', 'Google Code Jam']
---
# [GCJ 2017 Finals] Stack Management
## 题目描述

You are playing a solitaire game in which there are $\mathbf{N}$ stacks of face-up cards, each of which initially has $\mathbf{C}$ cards. Each card has a value and a suit, and no two cards in the game have the same value/suit combination.

In one move, you can do one of the following things:

1. If there are two or more cards with the same suit that are on top of different stacks, you may remove the one of those cards with the smallest value from the game. (Whenever you remove the last card from a stack, the stack is still there — it just becomes empty.)
2. If there is an empty stack, you may take a card from the top of any one of the non-empty stacks and place it on top of (i.e., as the only card in) that empty stack.

You win the game if you can make a sequence of moves such that eventually, each stack contains at most one card. Given a starting arrangement, determine whether it is possible to win the game.
## 输入格式

The first line of the input gives the number $\mathbf{P}$ of premade stacks that will be used in the test cases. Then, $\mathbf{P}$ lines follow. The i-th of those lines begins with an integer $\mathbf{C}_{\mathbf{i}}$, the number of cards in the i-th of those premade stacks, and continues with $\mathbf{C}_{\mathbf{i}}$ ordered pairs of integers. The j-th of these ordered pairs has two integers $\mathbf{V}_{\mathbf{i j}}$ and $\mathbf{S}_{\mathbf{i j}}$, representing the value and suit of the j-th card from the top in the i-th premade stack.

Then, there is another line with one integer $\mathbf{T}$, the number of test cases. $\mathbf{T}$ test cases follow. Each case begins with one line with two integers $\mathbf{N}$ and $\mathbf{C}$: the number of stacks, and the number of cards in each of those stacks. Then, there is one line with $\mathbf{N}$ integers $\mathbf{P}_{\mathbf{i}}$, representing the indexes (starting from 0) of the test case's set of premade stacks.

## 输出格式

For each test case, output one line containing Case #x: y, where $x$ is the test case number (starting from 1) and $y$ is POSSIBLE if it is possible to win the game, or IMPOSSIBLE otherwise.
## 样例

### 样例输入 #1
```
5
2 7 2 7 1
2 6 4 7 4
2 3 2 6 2
2 4 2 10 2
2 5 4 7 3
2
2 2
0 2
3 2
4 1 3
```
### 样例输出 #1
```
Case #1: POSSIBLE
Case #2: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In sample case #1, there are two stacks, each of which has two cards. The first stack has a 7 of suit 2 on top and a 7 of suit 1 below that. The second stack has a 3 of suit 2 on top and a 6 of suit 2 below that.

It is possible to win the game as follows:

* Remove the 3 of suit 2 from the second stack.
* Remove the 6 of suit 2 from the second stack. This makes the second stack empty.
* Move the 7 of suit 2 to the second stack. Then the win condition is satisfied: all stacks have at most one card.

In sample case #2, there are three stacks, each of which has two cards. It is not possible to win the game in this case; the only possible move is to remove the 5 of suit 4 on top of the third stack, and this does not open up any new moves.

**Limits**

- $1 \leq T \leq 100$.
- $2 \leq P \leq 60000$.
- $0 \leq P_i < P$, for all $i$.
- The $P_i$-th premade stack has exactly $C$ cards.
- No two cards in a test case have the same value/suit combination.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leq N \leq 4$.
- $2 \leq C_i \leq 13$, for all $i$.
- $2 \leq C \leq 13$.
- $1 \leq V_{ij} \leq 13$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 4$, for all $i$ and $j$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $2 \leq N \leq 50000$.
- $2 \leq C_i \leq 50000$, for all $i$.
- $2 \leq C \leq 50000$.
- $4 \leq N \times C \leq 10^5$.
- $1 \leq V_{ij} \leq 50000$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 50000$, for all $i$ and $j$.


---

---
title: "[GCJ 2016 Finals] Map Reduce"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13209
tag: ['贪心', '2016', 'Special Judge', '广度优先搜索 BFS', '构造', 'Ad-hoc', 'Google Code Jam']
---
# [GCJ 2016 Finals] Map Reduce
## 题目描述

Ben the brilliant video game designer is trying to design maps for his upcoming augmented-reality mobile game. Recently, he has created a map which is represented as a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. The map consists of a bunch of `.` characters representing empty squares, a bunch of `#` characters representing impassable walls, a single start position represented by `S` and a single finish position represented by `F`. For example, the map could look like:

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
```

In Ben's game, a path is a sequence of steps (up, down, left or right) to go from one cell to another while not going through any impassable walls.

Ben considers a good map to have the following properties:

- There is a path between any two empty squares (including the start and finish positions).
- To preserve structural integrity, impassable walls must meet at edges and not just corners. For every $2 \times 2$ region in the map, if the region contains exactly two walls, then those walls are either in the same row or the same column. In other words, there is no $2 \times 2$ region where the walls are in one of these two configurations:
  ```
  #.   .#
  .#   #.
  ```
- The boundary consists of only impassable walls. A cell is considered part of the boundary if it is in the uppermost/lowermost rows or if it is in the leftmost/rightmost columns.

The distance of the shortest path is the minimum number of steps required to reach the finish position from the start position. For instance, the shortest path in the above example takes $17$ steps.

Being such a clever mapmaker, Ben realized that he has created a map that is too hard for his friends to solve. He would like to reduce its difficulty by removing some of the impassable walls. In particular, he wants to know whether it is possible to remove zero or more impassable walls from his map such that the shortest path from start to finish takes exactly $\mathbf{D}$ steps, and that the resulting map is still good. Note that it is not enough to simply find a path with $\mathbf{D}$ steps; $\mathbf{D}$ must be the number of steps in the shortest path.

For example, if $\mathbf{D} = 15$, we could remove the impassable wall directly below the finish position to get a good solution.

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
```

There is no solution if $\mathbf{D}=5$.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three space-separated integers $\mathbf{R}$, $\mathbf{C}$ and $\mathbf{D}$: the number of rows and columns in the map, and the desired number of steps in the shortest path from start to finish after possibly removing impassable walls. $\mathbf{R}$ lines follow, each consisting of $\mathbf{C}$ characters (either ., #, S or F) representing Ben's map.

It is guaranteed that the map is good, as described in the problem statement.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the word POSSIBLE or IMPOSSIBLE, depending on whether the shortest path can be made equal to $\mathbf{D}$ by removing some number of walls such that the map is still good. If it is possible, output $\mathbf{R}$ more lines containing $\mathbf{C}$ characters each, representing the new map. In your output, replace the # characters for removed walls (if any) with . characters.

If multiple solutions are possible, you may output any of them.
## 样例

### 样例输入 #1
```
3
6 13 15
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
5 8 3
########
#S.....#
####...#
#F.....#
########
4 10 11
##########
#S#...#.F#
#...#...##
##########
```
### 样例输出 #1
```
Case #1: POSSIBLE
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
##########
#S#...#.F#
#...#...##
##########
```
## 提示

**Sample Explanation**

The sample output displays one set of answers to the sample cases. Other answers may be possible.

Sample case #1 is the example in the problem statement.

In sample case #2, it is possible to remove walls to make the distance of the shortest path either 2 or 4, for example. However, there is no way to make the distance of the shortest path exactly 3.

In sample case #3, the shortest path already takes 11 steps to begin with, so there is no need to reduce the difficulty of the map.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- Each test case contains exactly one $\mathbf{S}$ and exactly one $\mathbf{F}$.
- The input file is at most 3MB in size.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $3 \leq \mathbf{R} \leq 40$.
- $3 \leq \mathbf{C} \leq 40$.
- $1 \leq \mathbf{D} \leq 1600$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~300~~ 75 seconds.
- $3 \leq \mathbf{R} \leq 1000$.
- $3 \leq \mathbf{C} \leq 1000$.
- $1 \leq \mathbf{D} \leq 10^6$.
- NOTE: The Large output breaks the usual cap on Code Jam output size, but you can upload it as normal.


---

---
title: "[GCJ 2014 #3] Willow"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13263
tag: ['动态规划 DP', '博弈论', '2014', '记忆化搜索', '树形 DP', 'Google Code Jam']
---
# [GCJ 2014 #3] Willow
## 题目描述

Hanaa and Sherine are playing Willow, a game that is played on a board containing $\mathbf{N}$ cities. The $\mathrm{i}^{\text {th }}$ city contains $\mathbf{C}_{\mathrm{i}}$ coins, and there are $\mathbf{N}-1$ bidirectional roads running between the cities. All cities are reachable from one another. The game is played as follows:

First Hanaa chooses one of the cities as her starting location, then Sherine chooses one of the cities (possibly the same one Hanaa chose) as her starting location. Afterwards, they take turns playing the game, with Hanaa going first.

On a player's turn, that player must take all the coins on the city where she currently is, if there are any; there might be none if the city starts with no coins, or if one of the players has already started a turn in that city. Then, if possible, the player must travel to an adjacent city on a road. It might not be possible, because each road can be used at most once. This means that after one player has used a road, neither player is allowed to use the same road later. The game ends when neither Hanaa nor Sherine can make a move.

After the game ends, each player's score is equal to the difference between the number of coins she has and the number of coins her opponent has. If her opponent has more coins, this means that her score will be negative. Both players are trying to maximize their scores. Assuming that they are both using the best possible strategy to maximize their scores, what is the highest score that Hanaa can obtain?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing one integer $\mathbf{N}$, the number of cities on the board. $\mathbf{N}$ lines then follow, with the $\mathrm{i}^{\text {th }}$ line containing an integer $\mathbf{C}_{\mathrm{i}}$, the number of coins in city $\mathrm{i}$.

Finally there will be another $\mathbf{N}-1$ lines, with the $\mathrm{i}^{\text {th }}$ line $(\mathrm{i}$ starts from 1$)$ containing a single integer $\mathrm{j}(\mathrm{i}<\mathrm{j} \leq \mathbf{N})$ indicating that there is a road between city $\mathrm{i}$ and city $\mathrm{j}$. All cities are guaranteed to be reachable from one another at the start of the game.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $\mathrm{x}$ is the case number (starting from 1) and $y$ is the highest score that Hanaa can obtain.
## 样例

### 样例输入 #1
```
3
3
1000
200
1000
2
3
8
8
0
8
0
0
0
0
10
2
5
4
5
6
7
8
10
150
200
0
5000
0
100
0
0
0
10000
10
3
8
5
8
7
8
9
10
```
### 样例输出 #1
```
Case #1: 200
Case #2: -2
Case #3: 5100
```
## 提示

**Limits**

- Memory limit: 1 GB.
- $1 \leq \mathbf{T} \leq 50 .$
- $0 \leq \mathbf{C}_{\mathrm{i}} \leq 10000 .$

**Small dataset(15 Pts)**

- Time limit: ~~60~~ 30 seconds.
- $2 \leq \mathbf{N} \leq 80 .$

**Large dataset(24 Pts)**

- Time limit: ~~120~~ 30 seconds.
- $2 \leq \mathbf{N} \leq 500 .$



---

---
title: "[GCJ 2012 Finals] Shifting Paths"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13336
tag: ['动态规划 DP', '2012', '折半搜索 meet in the middle', 'Google Code Jam']
---
# [GCJ 2012 Finals] Shifting Paths
## 题目描述

You have been walking in the woods for hours, and you want to go home.

The woods contain $N$ clearings labeled $1, 2, \dots, N$. You are now at clearing $1$, and you must reach clearing $N$ in order to leave the woods. Each clearing from $1$ to $N-1$ has a left path and a right path leading out to other clearings, as well as some number of one-way paths leading in. Unfortunately, the woods are haunted, and any time you enter a clearing, one of the two outgoing paths will be blocked by shifty trees. More precisely, on your $k^{th}$ visit to any single clearing:

- You must leave along the left path if $k$ is odd.
- You must leave along the right path if $k$ is even.
- All paths are one-way, so you have no choice at each step: you must go forward through the one unblocked outgoing path.

So the first time you are in clearing #1, you will leave along the left path. If you ever come back to clearing #1 for a second time, you would leave along the right path; the third time, you'd leave along the left path again; and so on.

You begin at clearing #1, and when you get to clearing #N, you can leave the woods. How many paths do you need to follow before you get out?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each beginning with a line containing a single integer $N$.

$N-1$ lines follow, each containing two integers $L_i$ and $R_i$. Here, $L_i$ represents the clearing you would end up at if you follow the left path out of clearing $i$, and $R_i$ represents the clearing you would end up at if you follow the right path out of clearing $i$.

No paths are specified for clearing $N$ because once you get there, you are finished.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the number of paths you need to follow to get to clearing $N$. If you will never get to clearing $N$, output "Infinity" instead.
## 样例

### 样例输入 #1
```
2
4
2 1
3 1
2 4
3
2 2
1 2
```
### 样例输出 #1
```
Case #1: 8
Case #2: Infinity
```
## 提示

**Sample Explanation**

In the first sample case, your route through the woods will be as shown below:

| Paths followed | Clearing | Path direction |
|:-:|:-:|:-:|
| 0 | 1 | Left |
| 1 | 2 | Left |
| 2 | 3 | Left |
| 3 | 2 | Right |
| 4 | 1 | Right |
| 5 | 1 | Left |
| 6 | 2 | Left |
| 7 | 3 | Right |
| 8 | 4 | - |

**Limits**

- $1 \leq T \leq 30.$
- $1 \leq L_i, R_i \leq N$ for all $i$.

**Test set 1 (5 Pts, Visible Verdict)**

- $2 \leq N \leq 10.$

**Test set 2 (46 Pts, Hidden Verdict)**

- $2 \leq N \leq 40.$


---

---
title: "[NOI2003] 智破连环阵"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1526
tag: ['搜索', '2003', 'NOI', '剪枝']
---
# [NOI2003] 智破连环阵
## 题目描述

B 国在耗资百亿元之后终于研究出了新式武器——连环阵（Zenith Protected Linked Hybrid Zone）。传说中，连环阵是一种永不停滞的自发性智能武器。但经过 A 国间谍的侦察发现，连环阵其实是由 $M$ 个编号为 $1, 2,\ldots, M$ 的独立武器组成的。最初，$1$ 号武器发挥着攻击作用，其他武器都处在无敌自卫状态。以后，一旦第 $i$（$1\leq i< M$）号武器被消灭，$1$ 秒种以后第 $i+1$ 号武器就自动从无敌自卫状态变成攻击状态。当第 $M$ 号武器被消灭以后，这个造价昂贵的连环阵就被摧毁了。

为了彻底打击 B 国科学家，A 国军事部长打算用最廉价的武器——炸弹来消灭连环阵。经过长时间的精密探测，A 国科学家们掌握了连环阵中 M 个武器的平面坐标，然后确定了 $n$ 个炸弹的平面坐标并且安放了炸弹。每个炸弹持续爆炸时间为 $5$ 分钟。在引爆时间内，每枚炸弹都可以在瞬间消灭离它平面距离不超过 $k$ 的、处在攻击状态的 B 国武器。和连环阵类似，最初 $a_1$ 号炸弹持续引爆 $5$ 分钟时间，然后 $a_2$ 号炸弹持续引爆 $5$ 分钟时间，接着 $a_3$ 号炸弹引爆$\ldots$以此类推，直到连环阵被摧毁。

显然，不同的序列 $a_1, a_2, a_3\ldots$ 消灭连环阵的效果也不同。好的序列可以在仅使用较少炸弹的情况下就将连环阵摧毁；坏的序列可能在使用完所有炸弹后仍无法将连环阵摧毁。现在，请你决定一个最优序列 $a_1, a_2, a_3\ldots$ 使得在第 $a_x$ 号炸弹引爆的时间内连环阵被摧毁。这里的 $x$ 应当尽量小。
## 输入格式

第一行包含三个整数：$M$、$n$ 和 $k$，分别表示 B 国连环阵由 M 个武器组成，A 国有 $n$ 个炸弹可以使用，炸弹攻击范围为 $k$。以下 $M$ 行，每行由一对整数 $x_i, y_i$ 组成，表示第 $i$ 号武器的平面坐标。再接下来 $n$ 行，每行由一对整数 $u_i, v_i$ 组成，表示第 $i$ 号炸弹的平面坐标。输入数据保证随机、无误、并且必然有解。

## 输出格式

一行包含一个整数 $x$，表示实际使用的炸弹数。

## 样例

### 样例输入 #1
```
4 3 6
0 6
6 6
6 0
0 0
1 5
0 3
1 1

```
### 样例输出 #1
```
2

```
## 提示

对于 $100\%$ 的数据，$1\leq M, n\leq 100$，$1\leq k\leq 1000$，$0\leq x_i, y_i\leq 10000$，$0\leq u_i, v_i\leq 10000$。

各个测试点 $2$ 秒。



---

---
title: "[NOI2010] 旅行路线"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1933
tag: ['动态规划 DP', '搜索', '2010', 'NOI', 'O2优化', '剪枝', '插头 DP']
---
# [NOI2010] 旅行路线
## 题目描述

2010 年，世博会在中国上海举办，吸引了数以千万计的中外游客前来参观。暑假期间小 Z 也来到了上海世博园， 她对世博园的拥挤早有所闻，对有的展馆甚至要排上好几个小时的队才能进入也做好了充分准备，但为了使得自己的世博之旅更加顺利舒畅，小 Z 决定在游玩之前先制定一份详细的旅行路线。

小 Z 搜集到了世博园的地图，她发现从整体上看世博园是一块非常狭长的区域，而每一个展馆占用了其中一个几乎相同大小的方块。因此可以将整个园区看成一个 $n \times m$ 的矩阵（$n \leq 3$），其中每一个格子为一个主题展馆。

由于不同展馆受到的关注度会有一些差别，因此排队时间的长短也不尽相同。小 Z 根据统计信息给每一个展馆 $(x, y)$ 标记了 $T_{x,y} = 0$ 或 $1$，如果 $T_{x,y} = 1$，表示这个展馆非常热门，需要排很长时间的队；如果 $T_{x,y} = 0$，表示这个展馆相对比较普通，几乎不需要排队即可进入参观。小 Z 希望能够制定一份合理的路线，使得能交替参观热门馆和普通馆，既不会因为总是参观热门馆而长时间在排队，也不会因为总是参观普通馆而使得游览过于平淡。同时，小 Z 办事很讲究效率，她希望在游遍所有展馆的同时，又不会走冤枉路浪费体力。因此她希望旅行路线满足以下几个限制：

1. 在参观完位于 $(x, y)$ 的展馆后，下一个参观的是一个相邻的且未被参观过的展馆 $(x^\prime, y^\prime)$，即 $|x-x^\prime|+|y-y^\prime|=1$；
2. 路线的起点位于整个矩阵的边界上，即 $x = 1$ 或 $x = n$ 或 $y = 1$ 或 $y = m$；

她制定了一个长度为 $n \times m$ 的 01 序列 $L$，她希望第 $i$ 个参观的展馆 $(x,y)$ 满足 $T_{x,y}=L_i$。

小 Z 想知道有多少条不同的旅行路线能够满足她的要求。由于最终的结果可能很大，小 Z 只想知道可行的旅行路线总数 $\bmod\space 11\,192\,869$ 的值。

## 输入格式

第一行包含两个正整数 $n, m$。

第 2 行至第 $n+1$ 行，每行有 $m$ 个 01 整数，其中第 $i+1$ 行第 $j$ 个数表示 $T_{i,j}$。

第 $n+2$ 行有 $n \times m$ 个 01 整数，其中第 $i$ 个数表示 $L_i$ 的值。
## 输出格式

仅包含一个整数，表示可行的旅行路线总数 $\bmod \space 11\,192\,869$ 的值。
## 样例

### 样例输入 #1
```
2 2
1 0
0 1
1 0 1 0
```
### 样例输出 #1
```
4

```
## 提示

【样例说明】

这四条可行的旅行路线分别为：

$$
\begin{aligned}
(1,1) \to (1,2) \to (2,2) \to (2,1)\\
(1,1) \to (2,1) \to (2,2) \to (1,2)\\
(2,2) \to (1,2) \to (1,1) \to (2,1)\\
(2,2) \to (2,1) \to (1,1) \to (1,2)
\end{aligned}
$$

【数据规模和约定】

- 对于 $10\%$ 的数据：$n=1$；
- 对于 $30\%$ 的数据：$n=2$；
- 对于 $60\%$ 的数据：$n=3$，其中 $20\%$ 的数据 $T_{i,j}$ 全为 $0$；
- 对于 $100\%$ 的数据：$m \leq 50$，$L_i,T_{i,j} = 0$ 或 $1$。


---

---
title: "[NOI2011] 兔兔与蛋蛋游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1971
tag: ['2011', 'NOI', '深度优先搜索 DFS', '二分图']
---
# [NOI2011] 兔兔与蛋蛋游戏
## 题目描述

这些天，兔兔和蛋蛋喜欢上了一种新的棋类游戏。

这个游戏是在一个 $n$ 行 $m$ 列的棋盘上进行的。游戏开始之前，棋盘上有一个格子是空的，其它的格子中都放置了一枚棋子，棋子或者是黑色，或者是白色。

每一局游戏总是兔兔先操作，之后双方轮流操作，具体操作为：

* 兔兔每次操作时，选择一枚与空格相邻的白色棋子，将它移进空格。
* 蛋蛋每次操作时，选择一枚与空格相邻的黑色棋子，将它移进空格。

第一个不能按照规则操作的人输掉游戏。为了描述方便，下面将操作“将第x行第y列中的棋子移进空格中”记为 $M(x,y)$。

例如下面是三个游戏的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/6wfmhuf2.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/j7vox6n7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/er1t5wpb.png)

最近兔兔总是输掉游戏，而且蛋蛋格外嚣张，于是兔兔想请她的好朋友——你——来帮助她。她带来了一局输给蛋蛋的游戏的实录，请你指出这一局游戏中所有她“犯错误”的地方。

注意：

* 两个格子相邻当且仅当它们有一条公共边。
* 兔兔的操作是“犯错误”的，当且仅当，在这次操作前兔兔有必胜策略，而这次操作后蛋蛋有必胜策略。

## 输入格式

输入的第一行包含两个正整数 $n,m$。

接下来 $n$ 行描述初始棋盘。其中第 $i$ 行包含 $m$ 个字符，每个字符都是大写英文字母 `X`、大写英文字母 `O` 或点号 `.` 之一，分别表示对应的棋盘格中有黑色棋子、有白色棋子和没有棋子。其中点号 `.` 恰好出现一次。

接下来一行包含一个整数 $k$（$1\leq k\leq 1000$） ，表示兔兔和蛋蛋各进行了 $k$ 次操作。

接下来 $2k$ 行描述一局游戏的过程。其中第 $2i - 1$ 行是兔兔的第 $i$ 次操作（编号为 $i$ 的操作） ，第 $2i$ 行是蛋蛋的第 $i$ 次操作。每个操作使用两个整数 $x,y$ 来描述，表示将第 $x$ 行第 $y$ 列中的棋子移进空格中。

输入保证整个棋盘中只有一个格子没有棋子， 游戏过程中兔兔和蛋蛋的每个操作都是合法的，且最后蛋蛋获胜。

## 输出格式

输出文件的第一行包含一个整数 $r$，表示兔兔犯错误的总次数。

接下来 $r$ 行按递增的顺序给出兔兔“犯错误”的操作编号。其中第 $i$ 行包含一个整数 $a_i$ 表示兔兔第 $i$ 个犯错误的操作是他在游戏中的第 $a_i$ 次操作。


## 样例

### 样例输入 #1
```
1 6 
XO.OXO 
1 
1 2 
1 1 
```
### 样例输出 #1
```
1
1
```
### 样例输入 #2
```
3 3 
XOX 
O.O 
XOX 
4 
2 3 
1 3 
1 2 
1 1 
2 1 
3 1 
3 2 
3 3 
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4 4 
OOXX 
OXXO 
OO.O 
XXXO 
2 
3 2 
2 2 
1 2 
1 3 
```
### 样例输出 #3
```
2
1
2
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 40$，$1 \leq m\leq 40$，$1\leq k\leq 1000$。

|测试点编号|$n$|$m$|
|:-:|:-:|:-:|
|$1,2$|$n=1$|$1\leq m\leq 20$|
|$3$|$n=3$|$m=4$|
|$4,5$|$n=4$|$m=4$|
|$6,7$|$n=4$|$m=5$|
|$8$|$n=3$|$m=7$|
|$9\sim 14$|$n=2$|$1\leq m\leq 40$|
|$15,16$|$1\leq n\leq 16$|$1\leq m\leq 16$|
|$17\sim 20$|$1\leq n\leq 40$|$1\leq m\leq 40$|



---

---
title: "[SCOI2009] 骰子的学问"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2565
tag: ['搜索', '贪心', '2009', '四川', '各省省选', 'Special Judge', '置换']
---
# [SCOI2009] 骰子的学问
## 题目描述

小鱼儿是个数学天才。一天晚上他研究一个和字符串有关的penney-ante游戏。游戏的规则如下：

1．有两个玩家，开始时每人选择一个长度相同的字符串；

2．一个字符生成器不断的随机生成字母添加到字符串S的末尾，S初始为空串；

3．如果S包含了某个玩家选择的字符串则游戏结束，该玩家获胜。


假设玩家1和玩家2分别选择了两个字符串A和B，如果玩家1可以以较大概率战胜玩家2，我们记作A>B。 咋一看来，小鱼儿觉得如果A>B且B>C则A>C。可事实恰好相反，存在字符串A, B, C使得A>B, B>C, C>A。


小鱼儿被这种戏的一个反常现象所吸引，通过查阅资料，他了解到这种现象被称为“非传递性悖论”，在许多非完全信息游戏（比如军棋）中，经常会有这样的例子。可是它到底是如何产生的呢？小鱼儿决定设计一种游戏，从中可以容易的找到非传递的例子，以便更清楚的认识“非传递性”。当然，这样的游戏越简单道理越深刻，于是小鱼儿想起了最简单的掷骰子游戏……


这个游戏是这样的，假设有n个骰子D1~Dn，每个骰子有m个面。每个面上标有一个1~n×m的正整数，并且所有骰子的所有n×m个面上的数字各不相同。满足这条编号要求，并且每个面被随到的概率相等的，这样的n个骰子称为一组“好骰子”。游戏开始时，两个玩家分别选两个骰子Di和Dj，各掷一次来比较掷出来那一面的数值，数大的获胜。


小鱼儿请你帮忙设计一组“好骰子”，使得对任意一个骰子Di，它总能战胜Dai。此处战胜是指选择前者的玩家获胜的概率超过1/2；a1~an为输入的1~n的正整数。

## 输入格式

第一行为两个整数n, m。第二行有n个整数，为a1，a2, …, an。

## 输出格式

包含n行，每行m个1~n×m的正整数，各不相同，以空格分开。

如果有多解，输出任意一组解；如果无解，输出一个整数0。

## 样例

### 样例输入 #1
```
3 4
2 1 2

```
### 样例输出 #1
```
0
```
## 提示

30%的数据满足n, m≤10

100%的数据满足3≤n, m≤200

感谢 @cn：苏卿念 提供spj


---

---
title: "[CQOI2015] 标识设计"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3170
tag: ['动态规划 DP', '搜索', '2015', '重庆', '各省省选', '记忆化搜索']
---
# [CQOI2015] 标识设计
## 题目描述

一家名字缩写为 LLL 的公司正在设计 logo，他们的初步方案是在一张方格上放置 $3$ 个 L 形的图案以及一些额外的装饰性图形，例如：![](https://cdn.luogu.com.cn/upload/pic/15558.png)  （灰色区域表示装饰性图形）。

$3$ 个 L 图案和装饰性图形均放置在方格之中，且必须占满方格。L 的横竖笔画长短均可，但长度必须大于 $0$（即不能退化为一条线段）。另外，为了使 L 图案醒目且容易辨别，设计师规定 $3$ 个 L 形图案之间不能有重叠或交叉的部分。当然，L 形图案也不能穿过装饰图形或与之重叠。

现在设计师已经确定了所有装饰性图形的位置，希望你计算一下放置不同的 L 形图案总共可以设计出多少个 logo。

## 输入格式

第一行包含两个空格分开的正整数 $n$ 和 $m$，分别表示方格的行数和列数。

接下来 $n$ 行，每行 $m$ 个字符，第 $(i + 1)$ 行第 $j$ 个字符代表第 $i$ 行第 $j$ 列的图形，该字符只可能为 `.` 或 `#`。`#` 表示该方格为装饰性图形，`.` 表示可以放置 L 图案的空白区域。
## 输出格式

输出一个整数，为可能的logo总数。

## 样例

### 样例输入 #1
```
4 4
....
#...
....
..#.
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n,m\leq 30$。


---

---
title: "[ZJOI2016] 电阻网络"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3351
tag: ['动态规划 DP', '搜索', '2016', '各省省选', '浙江']
---
# [ZJOI2016] 电阻网络
## 题目描述

小 Y 是一个充满智慧的女孩子，但是她只会使用串并联的方法计算两个节点之间的电阻。现在小 Y 有一个电阻网络问有多少点对 $u, v$（$u \ne v$）之间的电阻可以用串并联的方法计算出来。

我们来形式化地定义一下点对 $u, v$（$u \ne v$）之间的电阻能否用串并联的方法计算出来。首先我们把电阻网络看成一个 $n$ 个点 $m$ 条边的图（每个电阻对应一条边）。

令 $S$ 表示从 $u$ 到 $v$ 的所有简单路径（不经过重复的点的路径）上点的并集，也就是对于一个点 $x$，如果存在一条从 $u$ 到 $v$ 的简单路径经过这个点，那么它就在集合 $S$ 中。

如果 $S$ 非空且 $S$ 的导出子图是 $u, v$ 为端点的二端串并联图，那么 $u, v$ 之间的电阻就能用串并联方法计算。

一个有两个不同端点 $s, t$ 的图被称为二端图，其中一个称为源点，另一个称为汇点。两个二端图 $X, Y$ 并联（parallel composition）是指建一个新图，把 $X$ 和 $Y$ 的源点和汇点分别合并起来。两个二端图 $X, Y$ 串联（series composition）是指建一个新图，把 $X$ 的汇点和 $Y$ 的源点合并起来。由若干个两个点一条边的二端图经过一系列串并联变化之后形成的图称为二端串并联图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9xagyluf.png)

集合 $S$ 的导出子图点集为 $S$，边集由原图中两个端点都在 $S$ 中的边构成。
## 输入格式

第一行包含两个正整数 $n, m$，表示电阻网络中的节点数和电阻数。  
接下来 $m$ 行，每行包含两个正整数 $u, v$（$1 \le u, v \le n$，$u \ne v$），表示有一个电阻在节点 $u$ 和 $v$ 之间。
## 输出格式

输出共一行，表示答案，即有多少点对之间的电阻可以使用串并联的方法计算出来。
## 样例

### 样例输入 #1
```
6 6
1 2
1 3
1 4
2 3
2 4
5 6

```
### 样例输出 #1
```
6

```
## 提示

**【样例解释 #1】**

可行的点对有 $(1, 2), (1, 3), (1, 4), (2, 3), (2, 4), (5, 6)$。

**【数据范围】**

对于 $10 \%$ 的数据，$n, m \le 10$，保证原图连通，并且不存在一个点删去之后使得原图不连通。  
对于另外 $10 \%$ 的数据，$n, m \le 100$，保证原图连通，并且不存在一个点删去之后使得原图不连通。  
对于 $30 \%$ 的数据，$n, m \le 100$。  
对于 $40 \%$ 的数据，$n, m \le 1000$。  
对于另外 $30 \%$ 的数据，保证原图连通，并且不存在一个点删去之后使得原图不连通。  
对于 $100 \%$ 的数据，$1 \le n, m \le {10}^5$。


---

---
title: "[POI 2013] CEN-Price List"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3547
tag: ['2013', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2013] CEN-Price List
## 题目描述

Railway has always been the most popular mean of transport in Byteotia.

Out of $n$ towns in the land, $m$ pairs are connected by track segments    belonging to Byteotian State Railways (BSR).

The tracks do not cross outside of towns, and may lead through picturesque    bridges and somewhat less picturesque tunnels.

The ticket for travelling between any two towns    directly connected by rail costs $a$ bythalers.

Currently the transportation market in Byteotia is changing.

As of now, BSR faces a new competitor: Byteotian Airlines (BA).

BA plans to operate flights between some pairs of towns.

Since Byteotian railways are quite comfortable, the BA board has decided to    operate flights only between pairs of towns that are not directly    connected by rail.  Due to economy, BA will fly only between towns    for which the cheapest railway connection requires exactly one change.

The ticket for each such flight is going to cost $b$ bythalers.

To help Byteotian citizens in planning their trips, the Byteotian    Ministry for Transport (BMT) has decided to issue leaflets specifying the    cheapest routes between all possible towns.  A sequence of an    arbitrary number of direct railway or airplane connections is    called a route.  A BMT officer by the name of Byteasar has been    commissioned with the task of preparing the price list for the leaflets.

Could you help him in writing a program that will determine the right    prices?

Let us clarify that all the connections in Byteotia, both by railway and    airplane, are bidirectional.

## 输入格式

The first line of the standard input contains five integers,$n$,$m$,$k$,$a$ and $b$ ($2\le n\le 100\ 000$, $\le m\le 100\ 000$, $1\le k\le n$, $1\le a,b\le 1\ 000$),      separated by single spaces.

The numbers $n$ and $m$ denote the number of towns and the number of      direct railway connections in Byteotia, respectively.

For simplicity, we number the towns in Byteotia from $1$ to $n$. The other numbers denote:$k$ - the number of the source town for which the connection prices are to be determined;$a$ - the price of a direct railway connection;$b$ - the price of a direct airplane connection.

Each of the following $m$ lines contains a pair of integers $u_i$ and $v_i$($1\le u_i,v_i\le n$,$u_i\ne v_i$ for $i=1,2,\cdots,m$), separated by a single space, specifying the number of towns directly connected by tracks.


You may assume that all towns are reachable by railway from the town no. $k$.

## 输出格式

Your program should print $n$ lines to the standard output.

The line no. $i$ (for $i=1,2,\cdots,n$) should contain a single integer:

the cost of the cheapest route from town no. $k$ to town no. $i$.

Among those, the line no. $k$ should contain the number $0$.

## 样例

### 样例输入 #1
```
5 5 1 3 2
1 2
2 3
3 4
4 5
3 1

```
### 样例输出 #1
```
0
3
3
2
5

```
## 提示



------------

2024/2/4 添加了一部分来自 bzoj 的数据。
## 题目翻译

给定一个 $n$ 个点 $m$ 条边的无向图，边权均为 $a$。

现在将原来图中满足最短路等于 $2a$ 所有的点对 $(x,y)$ 之间加一条长度为 $b$ 的无向边。

给定 $k$，求点 $k$ 到所有点的最短路是多少。



---

---
title: "辉夜姬的十道难题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3798
tag: ['模拟', '动态规划 DP', '搜索', '贪心', '洛谷原创', '提交答案', '剪枝', '记忆化搜索']
---
# 辉夜姬的十道难题
## 题目背景

妹红最近玩了一款叫 $2048$ 的小游戏。

![](https://cdn.luogu.com.cn/upload/pic/5857.png)

(图为个人无撤销最高纪录~ 纯手玩)。
## 题目描述

$2048$ 是一个非常简单的数字游戏，它在 $4\times 4$ 的棋盘上进行，通过移动来合并数字，达到 $2048$ 即算胜利。妹红最近沉迷上了这个游戏，事情传到辉夜那里后，辉夜决定用曾经无人破解的十道难题来考考妹红。

游戏规则：

1. 游戏在 $n\times m$ 的方格棋盘上进行。

2. 两个玩家，其中一个可以移动棋盘上的数字，记做 M，另外一个可以向棋盘上放数字，记做 C。

3. 移动数字的规则如下：可以向上/下/左/右四个方向的其中之一移动。选定好方向后，所有数字都会向该方向靠拢，相同的两个数字相撞时会合并成一个新数字，这个数字是它们的和。在一次移动中，每个数字最多只能合并一次，优先合并靠近移动方向棋盘边缘的数字。

以 $n=2,m=4$ 的情况举例如下（$0$ 表示该位置为空）：

```
2 2 2 2
2 2 0 2
```

向左移动后变为：

```
4 4 0 0
4 2 0 0
```

每次合并后，将会获得一定的分数，获得的分数等于所有合并后数字相加之和。若无任何合并发生，则不得分。在上例中，得分为 $12$。

移动前后，若棋盘上的所有数字大小和位置均没有变化，则不算做有效移动，否则即是有效移动。

4. 向棋盘放置数字的规则如下：只能选择棋盘上没有数字的位置放置一个数字，可以放置的数字和放置方法在每个子任务中会具体描述。

5. 游戏开始时棋盘为空，分数为 $0$。先由玩家 C 行动两步，接着玩家 M 和 C 轮流行动，中间的每一步都必须是有效的。当轮到玩家 M 时，若不能够进行有效移动，则游戏结束，此时的得分为最终得分。

本题目为提交答案题，共有 $10$ 个子任务需要你来完成。将你的答案写到 $10$ 个文件中，分别命名为 ```gamex.out```，$x$ 表示子任务的编号（$0\ldots 9$）。

子任务内无部分分，你可以得到该任务的分数当且仅当你的输出和标准答案完全相同。

十道难题如下:

0. $n=1,m=2$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示在一局游戏中玩家 M 最多可以行动 $x$ 次，那么这个 $x$ 的最值是多少？输出两行，第一行一个整数表示 $x$ 的最小值，第二行一个整数表示 $x$ 的最大值。

1. $n=10738029,m=921023$。玩家 C 行动时可以放置 $2$ 或 $4$。若用 $x$ 表示棋盘上所有数字之和，请问 $x$ 的最大值是多少。因为这个值可能过大，只需要输出它除以 $10^9+7$ 的余数即可。

2. $n=2,m=2$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字， $x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，求一个最大的 $x$，使得玩家 M 能达到自己的目标。

3. $n=4,m=4$。玩家 C 行动时可以放置 $2,4$。输出两行，每行一个数字。第一行的数字表示能达到的最大分数。第二行的数字表示当数字总和达到最大时，分数的最小值。

4. $n=7393,m=9133$。玩家 C 可以放置数字 $2$ 共 $6144$ 次。棋盘初始为空，初始分数为 $0$。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

5. $n=7,m=233$。初始分数为 $0$,玩家 C 可以放置数字 $2$ 共 $233$ 次，数字 $4$ 共 $66$ 次。棋盘第一行一开始有若干数字，第 $i$ 列的数字为 $\text{lowbit}(i)\times 2$，$\text{lowbit}(i)$ 表示数字 $i$ 的二进制形式只取最后一个 $1$ 构成的数字。如 $\text{lowbit}(1\ldots 8)$ 为 $1,2,1,4,1,2,1,8$。棋盘的其他位置均为空。首先由玩家 C 连续行动，直到用完所有放置机会或中途主动放弃。然后连续向上移动直到向上方向不能构成有效移动。输出一行一个整数，表示最大得分。

6. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。用 $x$ 表示目标数字，$x$ 一定为 $2$ 的正整数幂。玩家 M 的目标是使盘面上出现数字 $x$，玩家 C 的目标是在盘面上出现数字 $x$ 之前使游戏结束。在两方均最优决策的情况下，输出一个最大的 $x$，使得玩家 M 能达到自己的目标。

7. $n=3,m=3$。玩家 C 行动时可以放置 $2,4$。玩家 M 的目标是让得分最大化，玩家 C 的目标是让得分最小化，在两方均最优决策的情况下，输出一个整数，表示最终的分数。

8. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。用 $x$ 表示目标数字，玩家 M 的目标是使盘面上出现大于等于数字 $x$ 的数。在玩家 M 最优决策的情况下，输出一行，$9$ 个实数，四舍五入到小数点后 $2$ 位，用空格隔开，分别表示 $x=2,4,8,16,32,64,128,256,512$ 时，达成目标数字的概率。

9. $n=3,m=3$。玩家 C 行动时，有 $90\%$ 的几率放置一个 $2$，$10\%$ 的几率放置一个 $4$，放置在各个空位的几率均等。玩家 M 的目标是让分数最大化。在玩家 M 最优决策的情况下，输出一个实数，四舍五入保留整数，表示分数的期望值。

妹红虽然对 $2048$ 有一定了解，但她并不能解决全部的问题，于是就交给了学 OI 的你。
## 输入格式

见题目描述

## 输出格式

见题目描述

## 样例

### 样例输入 #1
```
样例任务（无需提交）:
 n=2,m=2。 玩家C行动时只可以放置2。请输出一个整数，表示棋盘上可能出现的最大数字。

```
### 样例输出 #1
```
16
```
## 提示

如果对移动规则有疑惑，可以到 $2048$ 网站进行尝试:

http://gabrielecirulli.github.io/2048/

by-orangebird



---

---
title: "[IOI 2017] Nowruz"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3836
tag: ['搜索', '贪心', '2017', 'IOI', '提交答案', 'Special Judge', '深度优先搜索 DFS']
---
# [IOI 2017] Nowruz
## 题目背景

**[数据以及checker下载](http://pan.baidu.com/s/1o8jwPmy)**

## 题目描述

再过几天就是诺鲁孜节了（波斯人的新年），爷爷邀请他的全家人到他的花园来聚会。在众多的宾客中有$k$个小孩。为了让这些孩子们在聚会中更开心，爷爷打算让他们玩一个捉迷藏的游戏。

整个花园可以看成一个有$m\times n$个方格的网格。其中有一些（或许没有）方格被岩石堵住了，而剩下的方格就称为**空格**。如果两个格子共享同一条边，我们就称这两个格子是**邻居**。因此，每一个方格最多有$4$个邻居：两个水平方向的和两个垂直方向的。爷爷想把花园变成一个迷宫。为达此目的，他会在花园中的一些**空格**上种植灌木来堵住他们。而这些被灌木丛堵住的方格就不再是**空格**了。

一个迷宫必须具有下面所述的性质。在迷宫中的任意一对空格$a$和$b$之间都只会恰有唯一的一条简单路径相连。而这条由$a$到$b$的简单路径就是一个从空格$a$开始并以空格$b$结束的序列，序列中所有的方格必须是不同的，而且每个相连的方格都是邻居。

一个小孩能够躲藏的方格当且仅当这个方格是**空格**，而且它恰有唯一一个邻居是空格。同一个空格内只能躲藏一个小孩。

题目会给出整个花园的地图作为输入文件。你的任务就是帮助爷爷构造一个能够躲藏尽量多小孩的迷宫。


## 评分

一个**有效**的输出文件必须符合下列所有的条件：

- 除了把输入文件中的任意多个字母`.`修改成字母`X`（即被灌木堵塞）外，输出的地图必须和输入地图完全一样。

- 输出的地图必须符合在上文中提及的迷宫的所有性质。


对于某一个测试数据，如果你的输出不是**有效**的，你的这个测试数据的得分将会是$0$。反之，你的得分是$\min(10, 10\cdot l/k)$，向下取值至小数后二位，这里的$l$是指你输出的迷宫中能够最多藏着的小孩，而$k$则表示在输入文件中题目要求你躲藏的小孩数目。对于一个测试数据，你能够得到$10$分，当且仅当你的输入是一个能够躲藏$k$个或更多个小孩的迷宫。

对于每组测试数据都存在一个能得到$10$分的答案。

请注意如果你答案是有效的，但根据上述公式你的得分仍然是$0$分，则在评分系统中，现实的结果将会是'Wrong Answer'。

## 输入格式

这是一个提交答案型的题目，而且它有部份分。题目会给出$10$个描述爷爷花园的输入文件。对于每个输入文件你应该提交一个含有迷宫的地图作为输出文件我们会根据你提交的每个输入文件中的迷宫能够躲藏的小孩数目来给出你的分数。

这道题目你不需要提交任何源代码。

每个输入文件都描述了一个表示整个花园的网格，我们也会给出爷爷邀请的小孩数目$k$。格式如下：

第$1$行： $1 : \ \ m \ n \ k$

第$1+i\ (1 \leqslant i \leqslant m)$行： 网格中的第$i$行，它是一个长度为$n$的字符串，包含以下的字符（中间没有空格）：

- `.`： 一个空格，

- `#`： 一块岩石。

## 输出格式

第$i\ (1 \leqslant i \leqslant m)$行： 迷宫中的第$i$行（种植了树木的花园）。它是一个长度为$n$的字符串，包含以下字母（中间没有空格）：

\* `.` ： 一个空格，

\* `#`： 一块岩石，

\* `X`： 一个灌木（注意字母X必须为大写字母）。

## 样例

### 样例输入 #1
```
4 5 5
....#
.#..#
...#.
....#
```
### 样例输出 #1
```
.X.X#
.#..#
...#X
XX..#

//这是其中一个有效的输出

```
## 提示

样例输出是其中一个有效的输出。

对于这个输出，因为$l=4$个小孩能够这个迷宫中，所以这个解答能够得到$10 \cdot 4 / 5 = 8$分。小孩能够躲藏的方格如下以O所示：

```plain
OXOX#
.#.O#
...#X
XX.O#
```
以下的三个输出都不是有效的输出：

```plain
.XXX#    ...X#    XXXX#
.#XX#    .#.X#    X#XX#
...#.    ...#X    ..X#X
XX..#    XXXX#    ..XX#
```
在最左边的输出中，左上角的空格和最右列（位于右下方）的空格之间并没有一条简单路径。

在其他的两个输出中，对于任意两个空格之间都恰有两条简单路径相连。


## 限制条件

$1 \leqslant m,n \leqslant 1024$


---

---
title: "[JLOI2008] CODES"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3881
tag: ['字符串', '动态规划 DP', '搜索', '2008', '各省省选', '吉林']
---
# [JLOI2008] CODES
## 题目描述

给定n个01编码串S1,S2,…,Sn，你的任务是寻找一个编码串T，使得它至少可以被分解为两种不同的Si的排列。

例如：

给定5个01编码串：S1=0110，S2=00，S3=111，S4=001100，S5=110。那么一个符合要求的编码串T是：001100110，它有以下两种分解方法：

 00+110+0110 (S2+S5+S1) 或 001100+110 (S4+S5)

而0110110就不符合要求，它只有一种分解方法 0110+110 (S1+S5)。

你要寻找长度最短的符合要求的编码串T。若有多个符合要求的最短编码串T，则输出字典顺序最小的。

## 输入格式

输入文件第一行包含一个整数n，n不超过20，表示01编码串总数。接下来的n行每行给出一个长度不超过20的01编码串。

## 输出格式

输出文件共有两行，第一行为要求的编码串T的长度，第二行输出编码串T。对所有的测试数据，问题总有解。

## 样例

### 样例输入 #1
```
5
0110
00
111
001100
110

```
### 样例输出 #1
```
9
001100110

```


---

---
title: "[USACO17DEC] Push a Box P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4082
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [USACO17DEC] Push a Box P
## 题目描述

**题目译自 [USACO 2017 December Contest, Platinum](http://usaco.org/index.php?page=dec17results) Problem 2. [Push a Box](http://usaco.org/index.php?page=viewproblem2&cpid=769)**

一个谷仓是一个 $N \times M$ 的矩形网格，有一些网格里有干草。 Bessie 站在其中一个格子内，还有一个格子里有一个大木箱。 Bessie 不能和大木箱在一个格子里，也不能和干草在一个格子里。

如果她不与干草在同一个格子，她就可以往自己旁边的四个方向（东西南北）移动，如果她想移动到有木箱的格子里，那个木箱就会被她推一格（只要木箱的那个方向还有空间），如果没有空间，那 Bessie 就不能移动了。

给你谷仓的布局（空格子，干草以及木箱位置）以及 Bessie 的出发位置和箱子要被推到的位置，请你帮忙计算 Bessie 能不能把木箱推到指定位置。
## 输入格式

第一行有三个数 $N,M,Q$，其中 $N$ 是谷仓的行数，$M$ 是列数，$Q$ 是询问数。

接下来 $N$ 行是谷仓的初始布局，其中 `.` 代表空格子， `#` 代表干草格子， `A` 代表 Bessie 的初始位置， `B` 是木箱的初始位置。

接下来 $Q$ 行，每行一个坐标 $(R,C)$ ，代表第 $R$ 行第 $C$ 行。对于每行，你要输出 Bessie 是否有可能把箱子推到这个位置。
## 输出格式

$Q$ 行，每行一个答案，如果 Bessie 能走到，输出 `YES` ，否则输出 `NO` 。
## 样例

### 样例输入 #1
```
5 5 4
##.##
##.##
A.B..
##.##
##.##
3 2
3 5
1 3
5 3
```
### 样例输出 #1
```
NO
YES
NO
NO
```
## 提示

对于 $100\%$ 的数据，保证 $1\leq N,M \leq 1500$，$1\leq Q\leq 50000$。


---

---
title: "[SHOI2006] 有色图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4128
tag: ['搜索', '2006', '各省省选', '上海', '群论', '置换', 'Pólya 定理']
---
# [SHOI2006] 有色图
## 题目描述

如果一张无向完全图（完全图就是任意两个不同的顶点之间有且仅有一条边相连）的每条边都被染成了一种颜色，我们就称这种图为有色图。如果两张有色图有相同数量的顶点，而且经过某种顶点编号的重排，能够使得两张图对应的边的颜色是一样的，我们就称这两张有色图是同构的。以下两张图就是同构的，因为假如你把第一张图的顶点 $(1,2,3,4)$ 置换成第二张图的 $(4,3,2,1)$，就会发现它们是一样的。

![](https://cdn.luogu.com.cn/upload/pic/13240.png) 

你的任务是，对于计算所有顶点数为 $n$，颜色种类不超过 $m$ 的图，最多有几张是两两不同构的图。由于最后的答案会很大，你只要输出结论模 $p$ 的余数就可以了（$p$ 是一个质数）。

## 输入格式

输入文件只有一行，由三个正整数 $n,m,p$ 组成。
## 输出格式

即总数模 $p$ 后的余数。
## 样例

### 样例输入 #1
```
1 1 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 2 97
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
3 4 97
```
### 样例输出 #3
```
20
```
## 提示

对于 $100 \%$ 的数据，$1\leq n\leq 53$，$1\leq m\leq 1000$，$n<p\leq 10^9$。


---

---
title: "[WC2015] k 小割"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4153
tag: ['搜索', '2015', 'O2优化', '优先队列', '最小割', 'WC']
---
# [WC2015] k 小割
## 题目描述

给出一个有向带权网络 $G = (V, E)$，权值函数 $w: E \rightarrow \mathbb{Z^{*}}$（即任意边 $e$ 的权值 $w(e)$ 均为正整数），和点 $s, t \in V$，使得在 $G' = (V, E - S)$ 上不存在 $s$ 到 $t$ 的路径。


设 $\mathfrak{S}$ 是所有满足条件的边集 $S$ 的全集，按 $w(S)$ 从小到大输出 $\mathfrak{S}$ 中前 $k$ 小的边集的边权和。其中 $w(S) = \sum_{e \in S} w(e)$。

## 输入格式

第一行包含 $5$ 个正整数 $n, m, s, t, k$，其中 $s, t, k$ 意义如上，$n, m$ 分别表示 $\lvert V \rvert, \lvert E \rvert$（即点数和边数）。规定图中的节点用 $1$ 到 $n$ 的整数表示。保证 $s \neq t$。


接下来 $m$ 行，每行 $3$ 个整数 $x, y, z$，表示一条边权为 $z$ 的从 $x$ 到 $y$ 的边。可能有重边但保证没有自环。

## 输出格式

如果 $\lvert \mathfrak{S} \rvert < k$，先输出 $\lvert \mathfrak{S} \rvert$ 行，每行包含一个整数，表示前 $\lvert \mathfrak{S} \rvert$ 个 $w(S)$；再输出一行一个整数 $-1$。


如果 $\lvert \mathfrak{S} \rvert \geq k$，则输出 $k$ 行，表示前 $k$ 个 $w(S)$。


两种情况均需按照 $w(S)$ 从小到大输出。

## 样例

### 样例输入 #1
```
3 3 1 3 100
1 2 3
2 3 4
1 3 5

```
### 样例输出 #1
```
8
9
12
-1

```
### 样例输入 #2
```
5 8 1 5 10
1 2 45176
1 3 41088
1 4 32001
2 5 48931
3 5 39291
4 5 28970
2 3 48131
4 2 49795

```
### 样例输出 #2
```
116468
117192
118265
120223
145438
147235
149193
157556
158280
161311

```
## 提示

| 测试点编号 | $n \le$ | $m$ | $k \le$ | 约束 |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 2$ | $10$ | $\le 20$ | ${10}^6$ | 边权不超过 $65536$ |
| $3 \sim 6$ | $50$ | $\le 100$ | $100$ | 边权不超过 $65536$ |
| $7 \sim 10$ | $3000$ | $= 2 n - 4$ | $5 \times {10}^5$ | $s$ 有边连向所有非 $t$ 节点，所有非 $s$ 结点有边连向 $t$，边权不超过 $2^{31} - 1$ |
| $11 \sim 14$ | $1.5 \times {10}^5$ | $= 2 n - 4$ | $5 \times {10}^5$ | $s$ 有边连向所有非 $t$ 节点，所有非 $s$ 结点有边连向 $t$，边权不超过 $2^{31} - 1$ |
| $15 \sim 20$ | $50$ | $\le 1500$ | $100$ | 边权不超过 $65536$ |


---

---
title: "[THUWC 2017] 随机二分图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4547
tag: ['搜索', '2017', '记忆化搜索', 'THUWC', '状压 DP']
---
# [THUWC 2017] 随机二分图
## 题目背景

# 滥用本题评测将被封号
## 题目描述

某人在玩一个非常神奇的游戏。这个游戏中有一个左右各 $n$ 个点的二分图，图中的边会按照一定的规律随机出现。

为了描述这些规律，某人将这些边分到若干个组中。每条边或者不属于任何组 （这样的边一定不会出现），或者只属于一个组。

有且仅有以下三类边的分组：

0.  这类组每组只有一条边，该条边恰好有 $50\%$ 的概率出现。

1. 这类组每组恰好有两条边，这两条边有 $50\%$ 的概率同时出现，有 $50\%$ 的概率同时不出现。
2. 这类组每组恰好有两条边，这两条边恰好出现一条，各有 $50\%$ 的概率出现。

组和组之间边的出现都是完全独立的。

某人现在知道了边的分组和组的种类，想要知道完美匹配数量的期望是多少。你能帮助她解决这个问题吗？
## 输入格式

从标准输入读入数据。

第一行两个数 $n$ 和 $m$，表示图左右点数的数量和边的组的个数。我们用 $(a,b)$ （其中 $1 \le a,b \le n$）表示一条左端点为二分图左侧第 $a$ 个点，右端点为二分图右侧第 $b$ 个点的边。

接下来 $m$ 行，每行描述一个组。开头第一个数 $t$ 表示组的种类，$t=0$ 表示是一条边的组，$t=1$ 表示是两条边的组中的第一种，$t=2$ 表示是两条边的组中的第二种。如果 $t=0$， 接下来两个数 $a_1,b_1$ 表示组内的第一条边；否则，接下来四个数 $a_1,b_1,a_2,b_2$， 表示该组内的两条边分别为 $(a_1,b_1)$  和 $(a_2,b_2)$。保证每条边至多出现一次。
## 输出格式

输出到标准输出。

假设期望的完美匹配数量是$E$。输出一行表示
$$
(2^{n} E) \bmod (10^9 + 7)
$$
可以看出上式一定是一个整数。
## 样例

### 样例输入 #1
```
2 2
1 2 1 2 2
2 1 2 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 5
1 1 2 3 3
1 3 2 2 2
1 1 1 1 3
1 2 1 3 1
0 2 3
```
### 样例输出 #2
```
7
```
### 样例输入 #3
```
4 9
2 4 1 4 2
1 3 2 1 4
2 2 1 4 4
2 3 4 1 1
2 4 3 2 4
2 2 2 3 1
0 1 3
0 3 3
1 2 3 1 2
```
### 样例输出 #3
```
20
```
## 提示

## 【定义解释】

如果你对完美匹配和期望的定义很熟悉，那么你可以跳过本段。

对于一个左右各 $n$ 个点的二分图，它的一个完美匹配是指 $n$ 条没有公共点的边构成的匹配。

两个完美匹配不同，当且仅当它们至少含有一条不同的边。一个二分图完美匹配的数量定义为这张图能找到的两两不同的完美匹配的数量。

在题目的图中，边都是随机出现的，因此这个图中完美匹配的数量是一个随机变量。一个（离散型）随机变量 $X$ 的期望定义为以概率为权，$X$ 所有可能取值的加权平均数，即
$$
\sum_{x \in V(X)}P[X=x]\cdot x
$$
其中 $V(X)$ 表示 $X$ 所有可能的取值集合，$P[X=x]$ 表示 $X$ 取值为 $x$ 的概率。

## 【数据规模和约定】

对于 $5\%$ 的数据 $n \le 5$ 。  
对于另 $5\%$ 的数据 $n \le 8$ 。  
对于另 $10\%$ 的数据 $n \le 10$ 。  
对于另 $15\%$ 的数据，只有$t = 0$ 的情况。  
对于另 $5\%$ 的数据，只有$t = 0$ 的情况，且$m = n^2$，也就是该图为一个完全图。  
对于另 $20\%$ 的数据，只有 $t =0$ 或者 $t=1$ 的情况。
对于另 $20\%$ 的数据，只有 $t =0$ 或者 $t=2$ 的情况。
对于 $100\%$ 的数据，$n \le 15$。


---

---
title: "[APIO2018] 选圆圈"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4631
tag: ['搜索', '2018', 'APIO', '剪枝']
---
# [APIO2018] 选圆圈
## 题目描述

在平面上，有 $n$ 个圆，记为 $c_1, c_2,...,c_n$ 。我们尝试对这些圆运行这个算法：

1. 找到这些圆中半径最大的。如果有多个半径最大的圆，选择编号最小的。记为 $c_i$。
2. 删除 $c_i$ 及与其有交集的所有圆。两个圆有交集当且仅当平面上存在一个点，这个点同时在这两个圆的圆周上或圆内。（原文直译：如果平面上存在一个点被这两个圆所包含，我们称这两个圆有交集。一个点被一个圆包含，当且仅当它位于圆内或圆周上。）
3. 重复上面两个步骤直到所有的圆都被删除。

![QQ20180525194902.png](https://cdn.luogu.com.cn/upload/pic/19974.png)

当 $c_i$ 被删除时，若循环中第 $1$ 步选择的圆是 $c_j$，我们说 $c_i$ 被 $c_j$ 删除。对于每个圆，求出它是被哪一个圆删除的。
## 输入格式

第一行包含一个整数 $n$，表示开始时平面上圆的数量。

接下来 $n$ 行，每行包含三个整数 $x_i, y_i, r_i$ 依次描述圆 $c_i$ 圆心的 $x$ 坐标、$y$ 坐标和它的半径。
## 输出格式

输出一行，包含 $n$ 个整数 $a_1, a_2, ..., a_n$，其中 $a_i$ 表示圆 $c_i$ 是被圆 $c_{a_i}$ 删除的。
## 样例

### 样例输入 #1
```
11
9 9 2
13 2 1
11 8 2
3 3 2
3 12 1
12 14 1
9 8 5
2 8 2
5 2 1
14 4 2
14 14 1

```
### 样例输出 #1
```
7 2 7 4 5 6 7 7 4 7 6
```
## 提示

**提示**

题目描述中的图片对应了样例一中的情形。

**子任务（注：这里给出的子任务与本题在这里的最终评测无关，仅供参考）**

- Subtask 1(points: $7$): $n \leq 5000$
- Subtask 2(points: $12$): $n \leq 3 × 10^5$，对于所有的圆 $y_i = 0$
- Subtask 3(points: $15$): $n \leq 3 × 10^5$，每个圆最多和一个其他圆有交集
- Subtask 4(points: $23$): $n \leq 3 × 10^5$，所有的圆半径相同
- Subtask 5(points: $30$): $n \leq 10^5$
- Subtask 6(points: $13$): $n \leq 3 × 10^5$

所有数据均满足：$-10^9 ≤ x_i, y_i ≤ 10^9, 1 ≤ r_i ≤ 10^9$。


---

---
title: "孤舟蓑笠翁"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4730
tag: ['搜索', 'O2优化', '广度优先搜索 BFS']
---
# 孤舟蓑笠翁
## 题目背景

![Background](https://i.loli.net/2018/07/04/5b3cc42f57e64.png)

出于保护鱼类的目的，最优秀的渔翁才能在洞庭湖继续捕鱼。经过层层选拔，洞庭湖上只剩下孤舟蓑笠翁。以前跟其他渔翁一起钓鱼、打牌、切磋武艺，而如今只剩孤单一人，蓑笠翁不禁黯然神伤。选拔被淘汰，如今他们都去哪里了呢？大概回家种田养猪了吧。
## 题目描述

![Description](https://i.loli.net/2018/07/04/5b3cc3f0cd5f5.png)

蓑笠翁现在闲暇时在练的武术名为"左右互搏术"，相传是周伯通首创的武功。

练功时，蓑笠翁的双手在某竖直平面内运动，以该平面上某点作为坐标原点，向右为 $x$ 轴正方向，向上为 $y$ 轴正方向建立直角坐标系。那么该平面内的一个点就可以用坐标 $(x, y)$ 来表示。

该武功有 $n$ 个可停顿点，分别为 $p_1 = (x_1, y_1), p_2 = (x_2, y_2), \ldots, p_n = (x_n, y_n)$。我们可以将蓑笠翁练功的过程分成一秒一秒来看，第 $i$ 秒时，双手都处于可停顿点上。而第 $i$ 秒末双手进行移动，移动到其它可停顿点上。（当然也可以不移动）

左右互搏术中，有 $k$ 种绝招。第 $i$ 种绝招为：左手处于 $v_i$ 号可停顿点，右手处于 $u_i$ 号可停顿点，则可以发动绝招。

练武功也有禁忌，在两只手停顿的时候，如果两只手的曼哈顿距离小于 $d_{min}$，则容易走火入魔。如果两只手的曼哈顿距离大于 $d_{max}$，则蓑笠翁的胳膊显然快被扯断了。所以假设左手在 $l$ 号停顿点，右手在 $r$ 号停顿点，则需要满足 $d_{min} \leq |x_l - x_r| + |y_l - y_r| \leq d_{max}$。

从一个停顿点移动到另一个停顿点也有讲究，而且对于左右手还不一样。有 $m$ 个移动条件，每个移动条件形如：左手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点，或右手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点。对于某一秒末，蓑笠翁的手没那么快，所以每只手至多只能进行移动一次。上面未提到的移动方式均为非法。

蓑笠翁希望能发动连击。即先发动第 $i$ 种绝招，经过 $t$ 秒的移动后，又发动了第 $j$ 种绝招，且 $i \neq j$。

给出 $p_1, \ldots , p_n$，$v_1, \ldots v_k$，$u_1, \ldots , u_k$，$d_{min}$，$d_{max}$，和 $m$ 个移动条件，现在蓑笠翁想知道，发动第 $i$ 种绝招之后，最少经过多少秒的移动后能发动某个编号不为 $i$ 的绝招，即发动连击的最短耗时。请对于每个 $1 \leq i \leq k$ 输出答案。
## 输入格式

![Input](https://i.loli.net/2018/07/04/5b3ce144d752b.png)

第一行两个正整数 $n,m$。

第二行两个非负整数 $d_{min}, d_{max}$。保证 $d_{min} \leq d_{max}$。

接下来 $n$ 行，这 $n$ 行中的第 $i$ 行每行两个正整数 $x, y$ 表示 $i$ 号停顿点的坐标。

接下来的一行一个正整数 $k$ 。

接下来 $k$ 行，这 $k$ 行中的第 $i$ 行每行两个正整数 $v, u$ 表示 $i$ 号绝招。左手处于 $v$ 号可停顿点，右手处于 $u$ 号可停顿点时能发动该绝招。保证 $1 \leq v, u \leq n$，不会有两个绝招完全相同，保证 $v, u$ 的曼哈顿距离不小于 $d_{min}$ 不大于 $d_{max}$。

接下来 $m$ 行，每行三个正整数 $a, b, type$，若 $type = 0$ 则表示左手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点，若 $type = 1$ 则表示右手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点。保证 $1 \leq a, b \leq n$，$type \in \{0, 1\}$。
## 输出格式

![Output](https://i.loli.net/2018/07/04/5b3cc520d9fa0.png)

$k$ 行，第 $i$ 行表示第 $i$ 个绝招发动一次连击的最短耗时。

如果无论如何都无法连击，请输出 $-1$。
## 样例

### 样例输入 #1
```
5 5
1 6
3 2
9 2
7 3
7 8
4 9
3
5 4
1 3
1 2
1 2 0
2 5 0
1 5 1
1 3 1
3 4 1
```
### 样例输出 #1
```
2
2
-1
```
### 样例输入 #2
```
6 14
2 7
3 10
8 9
3 4
6 5
3 10
6 7
4
6 2
1 2
5 2
3 6
5 2 0
4 5 1
2 3 1
5 4 0
1 2 1
1 4 0
6 4 1
5 4 1
4 6 0
1 5 0
4 1 0
6 4 0
5 5 0
1 2 0
```
### 样例输出 #2
```
2
1
1
-1
```
## 提示

**【样例解释】**

![Explain](https://i.loli.net/2018/07/04/5b3cc62a913ae.png)

**对于样例一的解释**　对于绝招 $1$，可以先同时将左手移动到 $2$ 号可停顿点，右手移动到 $3$ 号可停顿点，这样耗时 $1 \textrm{ s}$，再将左手移动到 $1$ 号可停顿点，右手不动，这样可以发动绝招 $2$，共用时 $2 \textrm{ s}$。对于绝招 $2$ 可以把刚才的过程反过来，发动绝招 $1$。对于绝招 $3$，无论如何右手都无法移动，不能发动任何绝招，故输出 $-1$。

**对于样例二的解释**　不解释。

**【数据范围】**

![Constraint](https://i.loli.net/2018/07/04/5b3cc6528795b.png)

其中 $20 \%$ 的数据，$n \leq 50$，$m \leq 100$，$k \leq 100$。  
另有 $30 \%$ 的数据，$n \leq 500$，$m \leq 2000$，$k \leq 10000$，$d_{min} = 0$，$d_{max} = 10000$。  
对于 $100 \%$ 的数据，$n \leq 1000$，$m \leq 4000$，$1 \leq x_i, y_i \leq 1000$，$0 \leq d_{min} \leq d_{max} \leq {10}^9$。


---

---
title: "[CTSC2000] 逻辑范式"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6127
tag: ['搜索', '贪心', '2000', 'Special Judge', 'CTSC/CTS']
---
# [CTSC2000] 逻辑范式
## 题目描述

逻辑学是对命题以及命题真假性进行研究的一门科学。命题一般用一个小写字母表示，任何命题的值非真即假。我们用 `T` 表示命题的值为真，用 `F` 表示命题的值为假。

命题间的运算符称为命题操作联结词，简称联结词。逻辑系统中最基本的三个联结词是非、且和或，为了简便，我们用 $!$ 表示联结词非，用 $\&$ 表示联结词且，用 $|$ 表示联结词或。

联结词非是一个一元联结词，对于任意命题 $p$ ，$!p$ 的真值总是和 $p$ 相反。

联结词且又称合取，是一个二元联结词，对于任意命题 $p$ 和 $q$ ，当且仅当 $p$ 和 $q$ 同为真时， $p\&q$ 为真，否则 $p\&q$ 为假。

联结词或又称析取，是一个二元联结词，对于任意命题 $p$ 和 $q$ ，当且仅当 $p$ 和 $q$ 同为假时， $p|q$ 为假，否则 $p|q$ 为真。

下面给出三个基本命题运算联结词的真值表：

| 命题 $p$ | 命题 $q$ | $!p$ | $p\&q$ | $p\|q$   |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| T | T | F | T | T |
| T | F | F | F | T | 
| F | T | T | F | T |
| F | T | T | F | T |
| F | F | T | F | F | 


逻辑表达式是由命题、联结词和括号组成的。它的定义如下：

`<表达式>      ::=<合取式> or <析取式> or <否定式> or (<表达式>) or <元素>`

`<合取式>      ::=<表达式>&<表达式>`

`<析取式>      ::=<表达式>|<表达式>`

`<否定式>      ::=!<表达式>`

`<元素>      ::=<命题>`

注：其中 <命题> 是 $a$ 到 $z$ 的小写字母，`::=` 表示定义为， `or` 表示或。

对表达式的求值过程是根据表达式中各命题的值和真值表进行命题运算操作的过程。运算优先级为 $()$ 、 $!$ 、 $\&$ 和 $|$ 。$\&$ 和 $|$ 的优先级相同。相同优先级从左到右运算。

与或非逻辑范式（这里简称为范式）是一种逻辑表达式，它能够符合特定的真值表。例如一般逻辑里定义的蕴涵运算 $\rightarrow$ 的真值表为：

| 命题 $p$ | 命题 $q$ | $p \rightarrow q$ |
| :----------: | :----------: | :----------: |
| T | T | T |
| T | F | F |
| F | T | T |
| F | F | T |


我们可以用表达式 $!p|q$ 来表示这个蕴涵运算。表达式  $!p|q$ 的真值表为：

| 命题 $p$ | 命题 $q$ | $!p\|q$ |
| :----------: | :----------: | :----------: |
| T | T | T |
| T | F | F |
| F | T | T |
| F | F | T |

这样，我们就说 $p \to q$ 的范式为 $!p|q$ 。

完备定理告诉我们，对于任意一个 $n$ 元逻辑运算函数 $A$ ，已知 $A$ 的真值表，总可以求出 $A$ 的范式。范式只含命题、三个基本联结词和括号。例如，下面是一个三元运算 $A(p,q,r)$ 的真值表：

| 命题 $p$ | 命题 $q$ | 命题 $r$ | $A(p,q,r)$ |
| :----------: | :----------: | :----------: | :----------: |
| T | T | T | T |
| T | T | F | T |
| T | F | T | T |
| T | F | F | F |
| F | T | T | T |
| F | T | F | F |
| F | F | T | F |
| F | F | F | F |

也就是说，在命题 $p,q,r$ 有两个或两个以上为真时， $A$ 为真；反之 $A$ 为假。

当然，范式并不是唯一的。假设存在一种 $A$ 的范式为 $(p\&q\&r)|(!p\&q\&r)|(p\&!q\&r)|(p\&q\&!r)$ ， 表达式 $(p\&q)|(q\&r)|(p\&r)$ 也是 $A$ 的范式，并且它的长度比前式更短。

我们的要求是：给定 $n$ 元函数 $A$ 的真值表，求 $A$ 的范式，并要求范式尽可能短。
## 输入格式

输入文件第一行为 $n$（$n \leq 6$），表示 $A$ 是 $n$ 元函数。随后有 $2^n$ 行，每行为一个长度为 $n+1$ 的字符串。字符串仅包含字符 `T` 和 `F` 。前 $n$ 个依次表示第 $n$ 个命题的值，最后一个表示当 $n$ 个命题按此取值时 $A$ 的值。
## 输出格式

输出文件包含一行，为你给出的范式。命题依次用小写字母 $a, b, c, d, \ldots $表示。
## 样例

### 样例输入 #1
```
3
TTTT
TTFT
TFTT
TFFF
FTTT
FTFF
FFTF
FFFF

```
### 样例输出 #1
```
a&b|(a|b&c)
```
## 提示

**评分标准**：

- 如果你给定的范式错误或者在规定时间内没有出解，该测试点得 $0$ 分。
- 如果你给定的范式长度小于等于标准答案的长度，该测试点得满分。
- 如果你给定的范式长度大于等于标准答案长度的两倍，该测试点得 $0$ 分。
- 如果你给定的范式长度大于标准答案的长度，小于标准答案长度的两倍，该测试点得分计算公式为： 

$$
Score=FullScore \times \frac{2L_{std}-L}{L_{std}}
$$

其中 $FullScore$ 为该测试点满分， $L_{std}$ 为标准答案长度， $L$ 为你的答案长度。

**感谢 [tiger2005](https://www.luogu.com.cn/user/60864) 提供 SPJ ！**



---

---
title: "『MdOI R2』Little Goth"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6385
tag: ['字符串', '动态规划 DP', '贪心', '后缀自动机 SAM', 'O2优化', '广度优先搜索 BFS', '动态树 LCT', '分块', '后缀树', '洛谷月赛']
---
# 『MdOI R2』Little Goth
## 题目背景

小 M 和小 B 是一对好朋友，她们很喜欢爬山。
## 题目描述

山可以抽象为一个长为 $n$ 的字符串 $S$，串中仅包含小写字母。

对于一个字符串 $S$，我们定义 $|S|$ 表示串的长度，$S_{L\ldots R}$ 表示由 $S$ 中从左往右数，第 $L$ 个字符到第 $R$ 个字符依次连接形成的字符串。

小 M 一开始的位置是 $i$，她想要到达位置在 $k$ 处的山顶，而小 B 则要帮助她。为此，她们需要进行一系列操作。

她们**必须**在所有操作之前使用**一次**位于 $p$ 处的传送法阵，通过施展法术，可以使小 B 的位置变为任意满足 $j \geq i$ 且 $S_{i \ldots j} = S_{p \ldots p + (j-i)}$ 的 $j$。但同时，她们需要付出 $n-j$ 的代价。保证这样的 $j$ 存在。

之后，假设小 M ，小 B 的位置分别为 $i$ 和 $j$，她们可以任意次进行下列操作中的一种：

- 让小 M 爬，即令 $i=i+1$ 或 $i = i-1$。如果这一步操作之后 $i>j$，则 令 $j=i$。

- 让小 B 爬，即令 $j=j+1$ 或 $j=j-1$。如果这一步操作之后 $i>j$，则令 $i=j$。

- 使用螺旋升天，具体而言，选择两个下标 $l$ 和 $r$，满足 $S_{l \ldots r} = S_{i \ldots j}$，然后令 $i=l,j=r$。

出于某些原因，任何一次操作结束后，需要保证 $1 \leq i , j \leq n$。进行一次上述任意一种操作，都需要付出 $1$ 的代价。

爬山是很累的，因此她们想知道，至少需要付出多少代价才能让小 M 到达山顶，也就是让 $i=k$。又因为她们很喜欢爬山，她们有很多组询问要问你。
## 输入格式

第一行两个整数，$n$ 和 $q$，表示串 $S$ 的长度和询问的个数。

第二行一个长度为 $n$ 的字符串 $S$，仅包含小写字母。

接下来 $q$ 行，每行三个整数 $i,p$ 和 $k$，表明小 M 的位置，传送法阵位置和山顶的位置。
## 输出格式

共 $q$ 行，第 $i$ 行一个整数，表示对于第 $i$ 个询问给定的 $i,p$ 和 $k$，至少需要付出多少代价，才能让小 M 到达山顶，也就是，让小 M 的位置 $i=k$。
## 样例

### 样例输入 #1
```
8 2
dacdaaaa
5 8 1
1 4 5
```
### 样例输出 #1
```
5
8
```
## 提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。

[样例输入](https://www.luogu.com.cn/paste/j7u8z9ir) [样例输出](https://www.luogu.com.cn/paste/fh19p0a4)

--------
【样例解释】

对于样例的第一组询问，使用传送法术时，只能令 $j=5$，付出 $8-5=3$ 的代价。之后，首先使用一次第三种操作，选择 $l=2,r=2$，令 $i=l,j=r$，然后使用一次第一种操作，令 $i-1$，即可使 $i=k$，一共付出 $5$ 的代价。

对于第二组询问，可以选择 $j=2$，付出 $8-2=6$ 的代价，然后使用一次第三种操作，选取 $l=4,r=5$ 并使 $i=l,j=r$，然后进行一次第一种操作，令 $i+1$ 即可使 $i=k$。一共付出 $8$ 的代价。

---

【数据范围】

**本题采用捆绑测试。**

对于全部数据，保证 $1 \leq n,q \leq 3\times 10^4$，$S$ 中仅包含小写字母。

| 子任务编号 |      $n\leq$      |     $q \leq$      |      特殊性质       | 分值 | 时间限制 |
| :--------: | :---------------: | :---------------: | :-----------------: | :--: | :------: |
| Subtask 1  |       $15$        |       $15$        |         无          | $3$  |    1s    |
| Subtask 2  |       $80$        |       $80$        |         无          | $14$ |    1s    |
| Subtask 3  |  $2 \times 10^4$  |  $2 \times 10^4$  |   $S$ 中仅包含`a`   | $8$  |    3s    |
| Subtask 4  |  $2 \times 10^4$  |  $2 \times 10^4$  |        $S_1$        | $7$ |    3s    |
| Subtask 5  |       $400$       |       $400$       |         无          | $9$  |    1s    |
| Subtask 6  |  $2\times 10^4$   |  $2 \times 10^4$  | 所有询问的 $k$ 相同 | $10$ |    3s    |
| Subtask 7  |      $10^3$       |      $10^3$       |         无          | $10$ |    2s    |
| Subtask 8  | $1.5 \times 10^4$ | $1.5 \times 10^4$ |         无          | $11$ |    3s    |
| Subtask 9  |  $3 \times 10^4$  |  $3 \times 10^4$  |         无          | $28$ |    3s    |



性质 $S_1$ 是，对于给定的 $p$，满足条件的 $j$ 唯一。




---

---
title: "[BalticOI 2010] Lego (Day1)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6762
tag: ['模拟', '搜索', '2010', 'BalticOI（波罗的海）', '状压 DP']
---
# [BalticOI 2010] Lego (Day1)
## 题目描述

给定一些 $2 \times 2$ 的乐高方块，分别有白色（W），灰色（G）和黑色（B）。现在您要往 $6 \times 6$ 的底板上放置方块，需要保证不能有完全浮空的方块（即四个方格均无放置的地方）也不能超出 $6 \times 6$ 的底板。

现在给定一个放置完方块的底板的一面的示意图，和这一面逆时针旋转 $90^\circ$ 后的一面的示意图，求有多少种放置方块的方法数。
## 输入格式

第一行一个整数 $H$ 代表这种放置方块的高度。    
接下来 $H$ 行每行六个字符，代表从这一面看到的示意图。    
接下来 $H$ 行每行六个字符，代表从上一面逆时针旋转 $90^\circ$ 后的示意图。   
只能从前面，后面，左面，右面看，不能从上面，下面看。
## 输出格式

一行一个整数代表答案。          
答案保证在 64 位有符号整数内。
## 样例

### 样例输入 #1
```
2
WWGG..
.BB.WW
.WGG..
WWGG..
```
### 样例输出 #1
```
6
```
## 提示

#### 样例 1 解释

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/njr2rk9l.png)

第一个是从 $A$ 面观察到的示意图。    
第二个是从 $B$ 面（$A$ 面逆时针旋转 $90^\circ$）观察到的示意图。

下面是这 $6$ 种情况（感谢 Vonov 提供的图片！）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wymozlif.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/1vw0fu3t.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/umn2hync.png)             
![](https://cdn.luogu.com.cn/upload/image_hosting/pykojvay.png)           
![](https://cdn.luogu.com.cn/upload/image_hosting/9z9wvzxp.png)          
![](https://cdn.luogu.com.cn/upload/image_hosting/hkp3tjfp.png)

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le H \le 6$。

#### 说明

翻译自 [BalticOI 2010 Day1 B Lego](https://boi.cses.fi/files/boi2010_day1.pdf)。


---

---
title: "[IOI 2020] 网络站点"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6838
tag: ['2020', 'IOI', '交互题', 'Special Judge', '深度优先搜索 DFS']
---
# [IOI 2020] 网络站点
## 题目描述

新加坡的互联网主干网由 $n$ 个网络站点组成，这些站点分配了从 $0$ 到 $n-1$ 的 **序号**。互联网中还有 $n-1$ 条双向链路，它们从 $0$ 到 $n-2$ 编号。每条链路连接两个不同的站点。被一条链路连接着的两个站点互相称作对方的邻居。

一个由互不相同的站点所组成的站点序列 $a_0,a_1,\ldots,a_p$ 被称作一条从站点 $x$ 到站点 $y$ 的路径，当且仅当 $a_0=x$，$a_p=y$，并且序列中每两个连续的站点都是邻居。保证从任意站点 $x$ 到任意其他站点 $y$ **有且仅有** 一条路径。

任意站点 $x$ 可以生成一个数据包，并把它发送给任意其他站点 $y$，站点 $y$ 称作这个数据包的 **目的站点**。数据包需要按下述规则在站点 $x$ 到站点 $y$ 的唯一路径上进行路由。假设数据包当前发送到了站点 $z$，其中 $y$ 是数据包的目的站点且 $z \ne y$，则站点 $z$ 会：

1. 执行 **路由函数**，找到 $z$ 到 $y$ 的唯⼀路径中 $z$ 的邻居。然后
2. 将数据包转发给这个邻居。

然而，站点有存储内存限制，可能无法存下路由函数中需要使用的完整的主干网链路列表。

你的任务是实现主干网的路由机制，它由两个函数组成。

- 第一个函数的输入参数为 $n$、主干网链路的列表和一个整数 $k \ge n-1$。该函数需要为每个站点分配一个独一无二的  **编号**，其大小在 $0$ 到 $k-1$ 之间（包括 $0$ 和 $k-1$）。
- 第二个函数是路由函数，它在站点编号分配好后部署到所有站点上。它的输入参数如下：
	- $s$，数据包当前所处的站点的 **编号**，
	- $t$，数据包的目的站点的 **编号** $(t \ne s)$，
	- $c$，表示 $s$ 的所有邻居站点的 **编号** 的列表。
    
该函数应该返回一个 $s$ 的邻居的 **编号**，表示数据包需要转发到的下个站点。

在每个子任务中，你的得分取决于所有站点被分配到的编号的最大值（通常来说，编号最大值越小越好）。

#### 实现细节

你需要实现下列函数：

```cpp
int[] label(int n, int k, int[] u, int[] v)
  ```

- $n$: 主干网中站点的数量。
- $k$: 可用的编号的最大值。
- $u$ 和 $v$: 大小为 $n-1$ 的数组，表示链路。对每个 $i(0 \le i \le  \le n-2)$，链路 $i$ 连接着序号为 $u[i]$ 和 $v[i]$ 的站点。
- 该函数应该返回一个大小为 $n$ 的数组 $L$。对每个 $i(0 \le i \le n-1)$，$L[i]$ 表示序号为 $i$ 的站点所分配到的编号。数组 $L$ 中的所有元素必须互不相同并且大小在 $0$ 到 $k$ 之间。

```cpp
int find_next_station(int s, int t, int[] c)
```

- $s$: 数据包当前所在站点的编号。
- $t$: 数据包目的站点的编号。
- $c$: 一个数组，包含 $s$ 的所有邻居的编号。数组 $c$ 按照元素大小升序排列。
- 该函数应该返回一个 $s$ 的邻居的编号，表示数据包需要转发到的下个站点。

每个测试用例包含一个或多个独立的场景（也就是不同的主干网描述）。 对于一个包含 $r$ 个场景的测试用例，调用上述函数的评测程序会按下列步骤运行恰好两次。

程序第一次运行期间：

- `label` 函数被调用 $r$ 次，
- 返回的编号将被评测系统保存，并且
- `find_next_station` 不会被调用。

程序第二次运行期间：

- `find_next_station` 会被调用若干次。对于每次调用，评测程序会选择任意某个场景，该场景中的 `label` 函数所返回的编号方式将用于本次 `find_next_station` 调用。
- `label` 不会被调用。
- 特别地，在评测程序第一次运行期间，保存在静态或全局变量中的信息将无法在 `find_next_station` 函数中使用。
## 提示

#### 样例说明

#### 例 1

考虑下列调用：

```cpp
label(5, 10, [0, 1, 1, 2], [1, 2, 3, 4])
```

共有 $5$ 个站点和 $4$ 条链路，链路对应的站点序号对分别为 $(0,1)$, $(1,2)$, $(1,3)$ 和 $(2,4)$。编号的大小范围为 $0$ 到 $k=10$。

为了返回下列编号方案：

|序号|编号|
|:-:|:-:|
|$0$| $6$|
|$1$| $2$|
|$2$|$9$|
|$3$ |$3$|
|$4$ |$7$|

函数 `label` 应该返回 $[6,2,9,3,7]$。下图中的数字表示站点的序号（左图）与分配到的编号（右图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/xpq3km1p.png)

假设编号按照上图所示进行分配，考虑下列的调用：

```cpp
find_next_station(9, 6, [2, 7])
```

它表示数据包当前所处的站点编号为 $9$，其目的站点的编号为 $6$。从当前站点到目的站点的路径上，站点编号依次为 $[9,2,6]$。因此，函数应该返回 $2$，表示数据包应该转发给编号为 $2$ 的站点（其序号为 $1$）。

考虑另一个可能的调用：

```cpp
find_next_station(2, 3, [3, 6, 9])
  ```
该函数应该返回 $3$，因为目的站点（编号 $3$）是当前站点（编号 $2$）的邻居，因此目的站点直接接收到了数据包。

#### 约束条件

- $1 \le r \le 10$

对于 `label` 的每次调用：

- $2 \le n \le 1000$
- $k \ge n-1$
- $0 \le u[i],v[i] \le n-1$（对于所有 $0 \le i \le n-2$）

对于 `find_next_station` 的每次调用，其输入参数来自于任意选择的某次之前对 `label` 的调用。考虑它所产生的编号，

- $s$ 和 $t$ 是两个不同站点的编号。
- $c$ 是编号为 $s$ 的站点的所有邻居的编号的序列，升序排列。

对于每个测试用例，所有场景加到⼀起，传递给函数  `find_next_station` 的所有数组 $c$ 的总长度不超过 $10^5$。

#### 子任务

1. （5 分）$k=1000$，不会出现拥有多于 $2$ 个邻居的站点。
2. （8 分）$k=1000$，链路 $i$ 连接站点 $i+1$ 和 $\lfloor\frac{i}{2}\rfloor$。
3. （16 分）$k=10^6$，最多一个站点拥有多于 $2$ 个的邻居。
4. （10 分）$n \le 6$，$k \le 10^9$
5. （61 分）$k \le 10^9$

在子任务 5 中，你可以获得部分分。 令 $m$ 为所有场景中 `label` 返回的最大编号。 对于这个子任务，你的得分将根据下表计算得到：

|最大编号|得分|
|:-:|:-:|
|$m \ge 10^9$|$0$|
|$2000 \le m < 10^9$|$50 \cdot \log_{5 \cdot10^5}(\frac{10^9}{m})$|
|$1000 < m < 5000$|$50$|
|$m \le 1000$|$61$|

#### 评测程序示例

评测程序示例以如下格式读取输入数据：

第 $1$ 行：$r$

接下来是 $r$ 块内容，每块描述了一个单独的场景，格式如下：

第 $1$ 行：$n\ k$        
第 $2+i(0 \le i \le n-2)$ 行：$u[i]\ v[i]$         
第 $1+n$ 行：$q$，`find_next_station` 的调用次数    
第 $2+n+j(0 \le j \le q-1)$ 行：$z[j]\ y[j]\ w[j]$，第 $j$ 次调用 `find_next_station` 时所涉及的站点的 **序号**。此时，数据包在站点 $z[j]$，目的站点为 $y[j]$，应该要转发给站点 $w[j]$。

评测程序示例以如下格式打印你的结果：

第 $1$ 行：$m$

接下来是 $r$ 块内容，分别对应输入中的场景。每块的格式如下：

第 $1+j(0 \le j \le q-1)$ 行：站点的 **序号**，它所对应的 **编号** 是第 $j$ 次调用 `find_next_station` 时返回的结果。

注意：评测程序示例每次执行时会同时调用 `label` 和 `find_next_station`。


---

---
title: "[THUWC 2017] 大葱的神力"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6849
tag: ['动态规划 DP', '搜索', '2017', '提交答案', 'Special Judge', '剪枝', '模拟退火', '背包 DP', '费用流', '随机化', 'THUWC']
---
# [THUWC 2017] 大葱的神力
## 题目背景

**本题为提交答案题。**

大葱是我国自古以来的美食，像我国传统美食北京烤鸭，用鸭子点缀出大葱的香味，令人赞不绝口。民间也流传着有「每天一棵葱，不当单身狗」的说法。

然而，大葱要发挥出独属于自己的神力，也是有条件的。
## 题目描述

现在小葱同学有 $N$ 棵大葱和 $M$ 个抽屉，将第 $i$ 棵大葱放到第 $j$ 个抽屉里面会产生 $w_{i,j}$ 的神力。自然小葱同学希望获得尽量多的神力，但是抽屉有着容积的限制，大葱也有着自己的体积。第 $i$ 棵大葱的体积为 $a_i$，第 $j$ 个抽屉的容积为 $b_j$。一个抽屉里面装着的大葱的体积之和不能超过这个抽屉的容积，一棵大葱不能拆分放到两个抽屉中。

小葱同学现在想知道，在这样的条件下，这些大葱最多会产生多少的神力？
## 输入格式

**本题为提交答案题**，输入文件为 `drawer1.in ~ drawer10.in`，详见附加文件。

第一行两个整数 $N,M$，代表大葱的个数和抽屉的个数。

接下来一行 $N$ 个整数，代表每棵大葱的体积。

接下来一行 $M$ 个整数，代表每个抽屉的容积。

接下来 $N$ 行每行 $M$ 个整数，第 $i$ 行第 $j$ 个数代表第 $i$ 棵大葱放到第 $j$ 个抽屉中会产生的神力。
## 输出格式

输出文件为 `drawer1.out ~ drawer10.out`，分别对应相应的输入文件。

对于每组输入数据，输出 $N$ 行每行一个整数，第 $i$ 个数代表第 $i$ 棵大葱被放到了哪个抽屉里面。如果第 $i$ 棵大葱没有被放到任何一个抽屉里面，则输出 $0$。
## 样例

### 样例输入 #1
```
3 4
1 1 2
2 1 2 3
1 2 1 1
2 1 2 1
3 1 0 1
```
### 样例输出 #1
```
2
0
1
```
## 提示

#### 样例说明

样例只是一种合法情况，获得的总神力值为 $2+3=5$。

#### 评分方式

**本题使用 Special Judge**，对于每个测试点，我们都有 $10$ 个参数 $a_1,a_2,\cdots,a_{10}$，如果你的输出所产生的的神力 $v$ 满足 $v \ge a_i$，则我们保证该测试点你至少会得到 $i$ 分。

#### 如何测试你的输出

在附加文件中，我们提供了 `scorer.cpp`，请自行编译来测试输出，这个程序将用于评判你的输出能够产生多少的神力。

若编译后文件名称为 `scorer`，在终端（Linux）中，输入以下命令：

```plain
./scorer <input_name> <output_name>
```

或在命令提示符（Windows）中，输入以下命令：
```plain
scorer <input_name> <output_name>
```
来对你的输出进行评判。其中 `<input_name>` 为输入文件名称，`<output_name>` 为输出文件名称。


---

---
title: "「MCOI-03」数据"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7047
tag: ['搜索', '高精度', 'O2优化', '剪枝', '洛谷月赛']
---
# 「MCOI-03」数据
## 题目背景

Rin 正在给 MCOI Round 998244353 的题目出数据。

但是她太菜了，把数据生成器写出锅了，于是数据只生成了一半然后生成器就 RE 了。

现在她想请你用这一半的数据恢复出完整的数据。
## 题目描述

以下是一些常见的定义，如果你很熟悉它们你也可以不看。

01 串是指仅包含 ```0``` 和 ```1``` 两种字符的字符串，仅包含其中一种也是可以的。

一个字符串取出其连续的一段称为子串。容易发现一个长度为 $2n$ 的字符串有 $n+1$ 个长度为 $n$ 的子串。

一组实数 $A$ 的平均值 $\overline{A}=\frac{\sum_{x\in A}x}{|A|}$，即所有元素的和除以元素的个数。

在此基础上，$A$ 的方差 $S^2=\frac{\sum_{x\in A}(x-\overline{A})^2}{|A|}$，即所有元素与平均值的差的平方和除以元素的个数。

一个长度为 $n$ 的 01 串 $S$ 的二进制值等于 $\sum_{i=1}^nS_i2^{n-i}$，其中 $S_i$ 是 $S$ 从左向右第 $i$ 个字符上的数字。

在本题中，给出如下定义：

一组数据是一个长度为 $2n$ 的 01 串。

一组数据的毒瘤度定义为，其所有长度为 $n$ 的子串的二进制值的方差。

现在，给定一组数据的前 $n$ 个字符。你需要找到使得这组数据的毒瘤度 **最小** 的后 $n$ 个字符。如果有多解，请按照这后 $n$ 个字符构成的子串的二进制值从小到大排序输出。


## 输入格式

输入数据共一行，包含一个长度为 $n$ 的 01 串，表示一组数据的前 $n$ 个字符。
## 输出格式

输出若干行，每一行一个长度为 $n$ 的 01 串，表示一组毒瘤度最小的数据的后 $n$ 个字符，按照其二进制值从小到大排序输出。
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
10
```
## 提示

#### 样例一解释

在本例中 $n=2$，存在四组满足要求的数据分别是 ```1000```，```1001```，```1010```，```1011```。

```1010``` 有三个长度为 $2$ 的子串，分别为 ```10```，```01```，```10```。它们的二进制值分别为 $2,1,2$。${2,1,2}$ 的平均值为 $\frac{5}{3}$，方差为 $\frac{2}{9}$。故 ```1010``` 的毒瘤度为 $\frac{2}{9}$。

可以计算出这四组数据的毒瘤度分别为 $\frac{8}{9},\frac{2}{3},\frac{2}{9},\frac{2}{3}$。其中 ```1010``` 是唯一毒瘤度最小的，故程序输出其后 $2$ 个字符 ```10```。

#### 数据范围与提示

保证所有数据随机生成。对于 01 串的每一位，其为 ```1``` 的概率都是 $\frac{1}{2}$ 且不同位相互独立。

本题不采用捆绑测试，按点给分。测试点 $1$ 计 $1$ 分，其他测试点每个计 $3$ 分。

每个测试点 $n$ 的规模如下表：

| 测试点编号 | $1$ | $2\sim 7$ | $8\sim 13$ | $14\sim 16$ | 
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $n$ | $\le 3$ | $\le20$ | $=26$ | $=56$ | 
|**测试点编号**|$17\sim 20$ | $21\sim 24$ | $25\sim 28$ | $29\sim 34$ |
|$n$|$=200$ | $=500$ | $\le1000$ | $\le 1500$ |

提示：在 C++ 中您可以使用 $128$ 位整数```__int128```。


---

---
title: "[USACO21JAN] Paint by Letters P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7295
tag: ['图论', 'USACO', '并查集', '2021', 'cdq 分治', '广度优先搜索 BFS', '平面图欧拉公式', '前缀和', '栈', '分块']
---
# [USACO21JAN] Paint by Letters P
## 题目描述

Bessie 最近收到了一套颜料。画布可以用一个 $N×M$ 的矩形方阵表示，其中行从上往下编号为 $1…N$，列从左往右编号为 $1…M$（$1≤N,M≤1000$）。被涂色的方格的颜色可以用一个 `A` 到 `Z` 的大写字母表示。初始时，所有方格均未被涂色，每个方格至多只能被涂色一次。

Bessie 指定了每个方格她所希望的颜色。她一笔可以将一些组成连通分量的方格涂上颜色，也就是说这些方格之间可以通过相邻方格互相到达。如果两个方格有公共边则认为它们是相邻的。

例如，$3×3$ 的画布

```
AAB
BBA
BBB
```

可以用如下四笔完成涂色：

```
...    ..B    AAB    AAB    AAB
... -> ... -> ... -> BB. -> BBA
...    ...    ...    BBB    BBB
```

使用少于四笔不可能得到最终结果。

作为一名先锋派艺术家，Bessie 只会对这个画布中的一个子矩形进行涂色。现在，她正在考虑 $Q$
个候选子矩形（$1≤Q≤1000$），每一候选给定四个整数 $x_1$、$y_1$、$x_2$ 和 $y_2$，表示由第 $x_1$ 行到第 $x_2$ 行及第 $y_1$ 列到第 $y_2$ 列的所有方格组成的子矩形。

对于每个候选子矩形，将所有子矩形内的方格都涂上所希望的颜色，并且子矩形外的方格均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选的回答是独立的。

注意：本题每个测试点的时间限制为默认限制的 1.5 倍，且内存限制为默认限制的 2 倍，为 512MB。 
## 输入格式

输入的第一行包含 $N$、$M$ 和 $Q$。

以下 $N$ 行每行包含一个由 $M$ 个大写字母组成的字符串，表示画布每行所希望的颜色。

以下 $Q$ 行每行包含四个空格分隔的整数 $x_1,y_1,x_2,y_2$，表示一个候选子矩形（$1≤x_1≤x_2≤N$, $1≤y_1≤y_2≤M$）。
## 输出格式

对于 $Q$ 个候选子矩形的每一个，输出一行，包含答案。
## 样例

### 样例输入 #1
```
4 8 9
ABBAAAAA
ABAAAABA
CAADABBA
AAAAAAAA
1 1 4 8
3 5 3 8
1 3 2 4
1 4 2 5
1 1 3 3
4 4 4 4
2 6 4 8
3 5 4 6
1 6 3 8
```
### 样例输出 #1
```
6
3
2
1
4
1
3
2
2
```
## 提示

#### 样例 1 解释

第一个候选由整个画布组成，可以用六笔完成涂色。

第二个候选的子矩形所希望的颜色为

```
ABBA
```

可以用三笔完成涂色。注意，尽管在考虑整个画布时方格 $(3,5)$ 和 $(3,8)$ 可以用一笔涂上颜色 $A$，但如果仅考虑子矩形内的方格则并非如此。 

#### 测试点性质：

 - 测试点 1-2 满足 $N,M≤50$。
 - 测试点 3-5 中，画布不包含由单一颜色所组成的环。也就是说，不存在由不同方格所组成的序列 $c_1,c_2,c_3,…,c_k$ 满足以下条件：
   - $k>2$
   - 所有的 $c_1,…,c_k$ 颜色相同。
   - 对于所有的 $1≤i<k$，$c_i$ 与 $c_i+1$ 相邻。
   - $c_k$ 与 $c_1$ 相邻。
   注意，问题描述中的 3×3 画布包含单一颜色所组成的环（左下角的四个 B）。
 - 测试点 6-8 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的两行两列的正方形所包含。问题描述中的 $3×3$ 画布不符合这一性质（由五个 B 组成的连通分量不能被一个两行两列的正方形包含）。
 - 测试点 9-11 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的三行三列的正方形所包含。问题描述中的 $3×3$ 画布符合这一性质。
 - 测试点 12-20 没有额外限制。

供题：Andi Qu 


---

---
title: "「MCOI-08」Fast Enumeration"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8281
tag: ['搜索', '洛谷原创', 'O2优化', '剪枝', '洛谷月赛']
---
# 「MCOI-08」Fast Enumeration
## 题目描述

Technoblade 将 Skyblock 抽象为一张 $n$（$n\le 50$）节点 $m$ 条边的简单有向图。他需要求出该图 **所有** 哈密尔顿回路，即所有排列 $p_1,p_2,\dots,p_n$ 使得 $p_1=1$ 并且 $p_1\to p_2\to \dots\to p_{n-1}\to p_n\to p_1$ 为一个合法路径。

**数据保证哈密尔顿回路数量非零并小于 $10^4$**。

**数据从所有合法数据随机采样。**
## 输入格式

第一行两个正整数 $n,m$。

接下来 $m$ 行，每行两个正整数 $u,v$。
## 输出格式

输出若干行；每行输出 $n$ 个正整数，为一个哈密尔顿回路。按照递增字典序输出。
## 样例

### 样例输入 #1
```
3 3
1 2
2 3
3 1
```
### 样例输出 #1
```
1 2 3
```
### 样例输入 #2
```
4 6
1 3
1 4
2 1
2 3
3 4
4 2
```
### 样例输出 #2
```
1 3 4 2
```
### 样例输入 #3
```
5 8
1 2
2 3
3 4
4 1
2 5
4 5
5 1
5 3
```
### 样例输出 #3
```
1 2 3 4 5
1 2 5 3 4
```
### 样例输入 #4
```
5 10
1 2
1 3
2 3
2 4
3 4
3 5
4 1
4 5
5 1
5 2
```
### 样例输出 #4
```
1 2 3 4 5
1 3 5 2 4
```
### 样例输入 #5
```
6 15
1 3
1 4
1 5
2 1
2 3
2 4
3 1
3 4
4 2
4 6
5 2
5 3
6 1
6 2
6 3
```
### 样例输出 #5
```
1 5 2 3 4 6
1 5 2 4 6 3
1 5 3 4 6 2
```
### 样例输入 #6
```
6 15
1 3
1 5
2 1
2 4
3 1
3 2
3 4
3 5
3 6
4 6
5 1
5 4
5 6
6 3
6 5
```
### 样例输出 #6
```
1 3 2 4 6 5
1 5 4 6 3 2
```
### 样例输入 #7
```
6 16
1 3
1 6
2 3
2 4
2 6
3 1
3 6
4 2
4 3
4 5
4 6
5 2
5 6
6 1
6 3
6 5
```
### 样例输出 #7
```
1 6 5 2 4 3
```
### 样例输入 #8
```
6 21
1 2
1 5
1 6
2 1
2 3
2 4
2 5
3 1
3 2
3 4
3 6
4 1
4 2
4 6
5 1
5 2
5 4
5 6
6 2
6 3
6 4
```
### 样例输出 #8
```
1 2 5 4 6 3
1 2 5 6 3 4
1 5 2 3 6 4
1 5 2 4 6 3
1 5 4 6 2 3
1 5 4 6 3 2
1 5 6 2 3 4
1 5 6 3 2 4
1 5 6 3 4 2
1 5 6 4 2 3
1 6 3 2 5 4
1 6 3 4 2 5
```
## 提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/lth4lrb1.png)

有 $1$ 个哈密尔顿回路：

 - $1\to2\to3\to1$。

#### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/if0vz8gm.png)

有 $1$ 个哈密尔顿回路：

 - $1\to3\to4\to2\to1$。

#### 样例 3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/dv1tul62.png)

有 $2$ 个哈密尔顿回路：

 - $1\to2\to3\to4\to5\to1$；
 - $1\to2\to5\to3\to4\to1$。

#### 样例 4 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/wggv2mfd.png)

有 $2$ 个哈密尔顿回路：

 - $1\to2\to3\to4\to5\to1$；
 - $1\to3\to5\to2\to4\to1$。

#### 样例 5 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/cfi80wob.png)

有 $3$ 个哈密尔顿回路：

 - $1\to5\to2\to3\to4\to6\to1$；
 - $1\to5\to2\to4\to6\to3\to1$；
 - $1\to5\to3\to4\to6\to2\to1$。

#### 样例 6 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/wqd9tpl8.png)

有 $2$ 个哈密尔顿回路：

 - $1\to3\to2\to4\to6\to5\to1$；
 - $1\to5\to4\to6\to3\to2\to1$。

#### 样例 7 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/jff0k373.png)

有 $1$ 个哈密尔顿回路：

 - $1\to6\to5\to2\to4\to3\to1$。

#### 样例 8 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/x2j19zoc.png)

有 $12$ 个哈密尔顿回路：

 - $1\to2\to5\to4\to6\to3\to1$；
 - $1\to2\to5\to6\to3\to4\to1$；
 - $1\to5\to2\to3\to6\to4\to1$；
 - $1\to5\to2\to4\to6\to3\to1$；
 - $1\to5\to4\to6\to2\to3\to1$；
 - $1\to5\to4\to6\to3\to2\to1$；
 - $1\to5\to6\to2\to3\to4\to1$；
 - $1\to5\to6\to3\to2\to4\to1$；
 - $1\to5\to6\to3\to4\to2\to1$；
 - $1\to5\to6\to4\to2\to3\to1$；
 - $1\to6\to3\to2\to5\to4\to1$；
 - $1\to6\to3\to4\to2\to5\to1$。

#### 数据规模与约定

对于固定 $n$ 和 $P$，任意一张 $m$ 条边的图权重为 $\left(\frac{1}{P}\right)^m\left(\frac{P-1}{P}\right)^{n^2-n-m}$。

 - Subtask 1（1 pts）：为样例。
 - Subtask 2（16 pts）：$n=15$。
 - Subtask 3（20 pts）：$n=30$。
 - Subtask 4（26 pts）：$n=40$。
 - Subtask 5（37 pts）：$n=50$。



---

---
title: "[NOI2023] 合并书本"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9483
tag: ['搜索', '2023', 'NOI', 'O2优化']
---
# [NOI2023] 合并书本
## 题目描述

小 C 有 $n$ 本书，每本书都有一个重量，他决定把它们合并成一摞。

每一次合并小 C 可以把一摞书放到另一摞书上面，使得它们合并到一摞。如果小 C 把第 $i$ 摞书放到第 $j$ 摞书上面，小 C 需要消耗的体力为**第 $i$ 摞书的重量**加上**两摞书的磨损值之和**。

初始时每本书自成一摞且磨损值均为 $0$。每当小 C 将两摞书合并后，形成的新的一摞书的磨损值为合并前的两摞书的磨损值的**较大值的两倍再加一**，重量为合并前的两摞书的**重量之和**。

你的任务是设计出合并的次序方案，使小 C 耗费的体力最少，并输出这个最小的体力耗费值。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个正整数 $t$，表示数据组数。

接下来依次输入每组测试数据，对于每组测试数据：

输入的第一行包含一个正整数 $n$，表示有 $n$ 本书。

输入的第二行包含 $n$ 个正整数，第 $i$ 个数 $w_i$ 表示第 $i$ 本书的重量。
## 输出格式

对于每组测试数据输出一行一个整数，表示将 $n$ 本书合并成一摞需要消耗的最少体力。
## 样例

### 样例输入 #1
```
1
4
1 1 1 1

```
### 样例输出 #1
```
6

```
### 样例输入 #2
```
见附件中的 book/book2.in。
```
### 样例输出 #2
```
见附件中的 book/book2.ans。
```
### 样例输入 #3
```
见附件中的 book/book3.in。
```
### 样例输出 #3
```
见附件中的 book/book3.ans。
```
### 样例输入 #4
```
见附件中的 book/book4.in。
```
### 样例输出 #4
```
见附件中的 book/book4.ans。
```
## 提示

**【样例解释 #1】**

如果小 C 将 $4$ 本书两两合并再将得到的两摞合并成一摞，那么前两次需要消耗的体力值各为 $1$。第三次将一摞重量为 $2$ 的书放到另一摞上面，两摞书磨损值各为 $1$，需要消耗的体力为 $2 + 1 + 1 = 4$。

因此如果选择这个方案，小 C 耗费的体力只有 $1 + 1 + 4 = 6$。

可以证明，在上述例子中，$6$ 为最小的体力耗费值。

**【数据范围】**

对于所有测试数据保证：$1 \le t \le 10$，$1 \le n \le 100$，$1 \le w_i \le 10 ^ 9$。

|测试点编号|$n \le$|是否有特殊性质|
|:-:|:-:|:-:|
|$1 \sim 2$|$7$|否|
|$3$|$11$|否|
|$4$|$13$|否|
|$5 \sim 6$|$22$|否|
|$7 \sim 8$|$28$|否|
|$9 \sim 13$|$50$|否|
|$14$|$60$|否|
|$15$|$70$|否|
|$16$|$80$|否|
|$17 \sim 18$|$100$|是|
|$19 \sim 20$|$100$|否|

特殊性质：保证 $w_i = 1$。


---

