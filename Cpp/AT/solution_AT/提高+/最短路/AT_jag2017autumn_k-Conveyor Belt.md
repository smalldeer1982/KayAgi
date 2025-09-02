# Conveyor Belt

## 题目描述

[题目链接]: https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_k

## 说明/提示

**本翻译由 AI 自动生成**

# 题解

## 作者：elbissoPtImaerD (赞：1)

我喜欢 **0-index**。$n$ 个物品标号为 $[0,n)$，以时刻 $0$ 为起始时刻。输出答案时 $+1$。

考虑用点对 $(x,y)$ 表示在第 $y$ 秒结束时，位置 $x$ 有物品。

那么：
- 将一个物品在 $t$ 时刻放上 $a$ 运到 $b$ 就是集合 $S(a,b,t)=\{(i,t+i-a)\mid \forall i\in[a,b]\}$。（注意右端点是闭的因为每秒每个位置至多做一件事）
- 一个运输方案 $S(a,b,t)$ 合法就是 $\nexists (x,y) \in S(a,b,t)$，$x > y$，这个即为 $a\le t$。（因为初始传送带为空）
- 两个运输方案不冲突等价于 $S(a_1,b_1,t_1) \cap S(a_2,b_2,t_2) = \emptyset$。（每个盒子至多放一件物品）
- 问题就是给定若干个形如 $(a,b)$ 的二元组，你要构造 $t_i \ge 0$ 使得：$\forall i \neq j$，$S(a_i,b_i,t_i) \cap S(a_j,b_j,t_j) =\emptyset$ 且 $\forall i$，$a_i \le t_i$。在此前提下最小化 $\max_i t_i+b_i-a_i$。

将不冲突的表述写开就是 $\nexists i\in[a_1,b_1],j\in[a_2,b_2]$，使 $i=j$ 且 $a_1+i-t_1=a_2+j-t_2$，即 $a_1 - t_1 \neq a_2 - t_2$ 或 $[a_1,b_1] \cap [a_2,b_2] = \emptyset$。这启发我们将集合 $S$ 按 $t-a$ 分组，然后只需考虑组内线段相交关系。形式化地，转化问题为：构造序列 $p_i = t_i - a_i\ge 0$，使 $\forall i\neq j \wedge p_i = p_j$，$[a_i,b_i] \cap [a_j,b_j] = \emptyset$。在此前提下最小化 $\max_i p_i+b_i$。

将对象从区间变成点，在右端点处统计答案，有：$\max_i p_i+b_i \ge \max\limits_{i \in \{b\}}(\min\limits_{j, i \in [a_j,b_j]} b_j + \max\limits_{j, i \in [a_j,b_j]} p_j) = \max\limits_{i \in \{b\}} (i + \sum\limits_j [i \in [a_j,b_j]] - 1)$。

我们猜测这个下界（记为 $K$）即为答案，尝试构造枝。

考虑维护一个数列 $x$。初始时 $x=(0)$。对位置扫描线，考虑加入区间 $[L,R]$。若 $\min_i x_i < L$，取 $P = \min_i [x_i = \min_j x_j] i$；否则令 $x \gets x + (0)$，令 $P = |x|$。让 $x_P=R$ 即可。显然 $P = \sum_j [R \in [a_j,b_j]] - 1$，从而保证了 $P+R \le K$。

所以最后输出的答案就是 $\max\limits_{i \in \{b\}} (i + \sum\limits_j [i \in [a_j,b_j]])$，开一个 HashTable 维护 $\{b\}$，再写一颗线段树支持区间加，求全局最大值即可。

---

