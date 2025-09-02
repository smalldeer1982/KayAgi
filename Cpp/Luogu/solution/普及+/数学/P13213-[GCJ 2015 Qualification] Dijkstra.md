# [GCJ 2015 Qualification] Dijkstra

## 题目描述

荷兰计算机科学家 Edsger Dijkstra 对该领域做出了许多重要贡献，其中包括以他名字命名的最短路径算法。但本题与该算法无关。

你在一次算法考试中因为拼错了 “Dijkstra” 而被扣了一分——你在 d 和 stra 之间写入了一些字符，每个字符都是 $i$、$j$ 或 $k$。你准备用四元数（一种实际存在的数系，扩展自复数）来为自己辩解。四元数的乘法结构如下表所示：

|   | $1$ | $i$ | $j$ | $k$ |
|:---:|:---:|:---:|:---:|:---:|
| $1$ | $1$ | $i$ | $j$ | $k$ |
| $i$ | $i$ | $-1$ | $k$ | $-j$ |
| $j$ | $j$ | $-k$ | $-1$ | $i$ |
| $k$ | $k$ | $j$ | $-i$ | $-1$ |

要将一个四元数与另一个四元数相乘，请查找第一个四元数所在的行和第二个四元数所在的列。例如，要计算 $i$ 乘以 $j$，查找 $i$ 行和 $j$ 列，得到 $k$。要计算 $j$ 乘以 $i$，查找 $j$ 行和 $i$ 列，得到 $-k$。

如上例所示，四元数的乘法不是交换律的——即存在某些 $\mathbf{a}$ 和 $\mathbf{b}$，使得 $\mathbf{a} \times \mathbf{b} \neq \mathbf{b} \times \mathbf{a}$。但它满足结合律——对于任意 $\mathbf{a}$、$\mathbf{b}$ 和 $\mathbf{c}$，都有 $\mathbf{a} \times (\mathbf{b} \times \mathbf{c}) = (\mathbf{a} \times \mathbf{b}) \times \mathbf{c}$。

四元数前的负号与通常意义下的负号一致——对于任意四元数 $\mathbf{a}$ 和 $\mathbf{b}$，都有 $-\mathbf{a} \times -\mathbf{b} = \mathbf{a} \times \mathbf{b}$，且 $-\mathbf{a} \times \mathbf{b} = \mathbf{a} \times -\mathbf{b} = -(\mathbf{a} \times \mathbf{b})$。

你想要证明你的拼写错误等价于正确拼写的 `ijk`，方法是：你能否将由 $i$、$j$、$k$ 组成的字符串在两个位置切分，形成三个子串，使得最左边的子串在四元数乘法下约化为 $i$，中间的子串约化为 $j$，最右边的子串约化为 $k$。（例如，`jij` 被解释为 $j \times i \times j$；$j \times i$ 等于 $-k$，$-k \times j$ 等于 $i$，所以 `jij` 约化为 $i$。）如果可以做到，你就能拿回那一分。你能找到切分方法吗？

## 说明/提示

**样例解释**

在第 1 组样例中，字符串长度太短，无法切分为三个子串。

在第 2 组样例中，可以直接将字符串切分为 i、j 和 k。

在第 3 组样例中，唯一的切分方式是 k、j、i，这不满足要求。

在第 4 组样例中，字符串为 $\mathbf{jijijijijiji}$。可以切分为 $\mathbf{jij}$（约化为 i）、$\mathbf{iji}$（约化为 j）、$\mathbf{jijiji}$（约化为 k）。

在第 5 组样例中，无论如何切分子串，都无法得到约化为 j 或 k 的部分。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{L} \leq 10000$。

**小数据集（11 分）**

- 时间限制：5 秒。
- $1 \leq \mathbf{X} \leq 10000$。
- $1 \leq \mathbf{L} \times \mathbf{X} \leq 10000$。

**大数据集（17 分）**

- 时间限制：10 秒。
- $1 \leq \mathbf{X} \leq 10^{12}$。
- $1 \leq \mathbf{L} \times \mathbf{X} \leq 10^{16}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 1
ik
3 1
ijk
3 1
kji
2 6
ji
1 10000
i```

### 输出

```
Case #1: NO
Case #2: YES
Case #3: NO
Case #4: YES
Case #5: NO```

