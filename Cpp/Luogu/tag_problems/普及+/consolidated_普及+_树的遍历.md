---
title: "[BCSP-X 2024 6 月小学高年级组] 先序遍历"
layout: "post"
diff: 普及+/提高
pid: B4173
tag: ['贪心', '2024', '北京', '树的遍历', 'BCSP-X']
---
# [BCSP-X 2024 6 月小学高年级组] 先序遍历
## 题目描述

按照根-左-右的顺序遍历**二叉树**：

- 先序遍历 = 根 + 左子树先序遍历 + 右子树先序遍历
- 空树的先序遍历 = 空

![](https://cdn.luogu.com.cn/upload/image_hosting/rz3z5ke0.png)

给一棵 $n$ 个点的二叉树（根节点为 $1$），你可以进行以下操作至多 $1$ 次：

- 选择 $1$ 个（除了根之外的）点 $u$，断开 $u$ 和其父节点之间的边；然后重新选择另一个点作为 $u$ 的父节点、将 $u$ 接上去，需要保证操作之后仍然是一棵以 $1$ 为根的二叉树。

你想要操作之后的二叉树有字典序最小的先序遍历序列，输出这个序列。
## 输入格式

第一行 $1$ 个整数 $T$，代表有 $T$ 组数据。

每组数据第一行 $1$ 个整数 $n$；接下来 $n$ 行，第 $i$ 行 2 个整数 $ls[i], rs[i]$ 代表 $i$ 号结点的左右儿子编号，没有左右儿子的话用 $0$ 表示。

## 输出格式

对于每组数据，输出一行 $n$ 个整数，代表字典序最小的二叉树先序遍历。
## 样例

### 样例输入 #1
```
12
4
2 3
0 4
0 0
0 0
5
2 3
0 4
0 5
0 0
0 0
6
5 2
3 6
4 0
0 0
0 0
0 0
6
2 3
6 4
0 5
0 0
0 0
0 0
6
5 2
3 0
4 0
6 0
0 0
0 0
6
3 2
4 6
0 0
5 0
0 0
0 0
6
4 2
5 3
0 0
0 0
0 6
0 0
6
3 2
0 0
5 4
0 6
0 0
0 0
6
2 3
0 0
5 4
0 6
0 0
0 0
6
3 2
4 5
0 0
0 6
0 0
0 0
6
2 3
0 4
0 0
0 5
0 6
0 0
6
2 5
3 4
0 0
0 0
6 0
0 0
```
### 样例输出 #1
```
1 2 3 4
1 2 3 4 5
1 2 3 4 5 6
1 2 4 3 5 6
1 2 3 4 6 5
1 2 4 5 3 6
1 2 5 4 6 3
1 2 3 5 4 6
1 2 3 4 5 6
1 2 4 3 6 5
1 2 3 4 5 6
1 2 3 4 5 6
```
## 提示

### 样例解释 #1

- 对于第一个样例，可以把 3 号结点连在 2 号结点的左儿子处。
- 对于第二个样例，可以把 4 号结点连在 3 号结点的左儿子处。

### 数据范围

对于所有数据，令 $\sum n$ 代表每组数据中 $n$ 的和，$1 \leq T \leq 100, 1 \leq n \leq 10^5, 1 \leq \sum n \leq 3 \times 10^5$，保证输入是一棵以 1 为根的二叉树。

- 对于测试点 1~3：$n \leq 10$；
- 对于测试点 4~8：$n \leq 200$；
- 对于测试点 9~11：$n \leq 1000$；
- 对于测试点 12~14：$n \leq 10^5$ 且所有 $ls[i] = 0$；
- 对于测试点 15：$n \leq 10^5$ 且所有 $rs[i] = 0$；
- 对于测试点 16~20：$n \leq 10^5$；


---

---
title: "[GESP202406 七级] 黑白翻转"
layout: "post"
diff: 普及+/提高
pid: P10723
tag: ['2024', '树形 DP', '树的遍历', 'GESP']
---
# [GESP202406 七级] 黑白翻转
## 题目描述

小杨有一棵包含 $n$ 个节点的树，这棵树上的任意一个节点要么是白色，要么是黑色。小杨认为一棵树是美丽树当且仅当在删除所有白色节点之后，剩余节点仍然组成一棵树。

小杨每次操作可以选择一个白色节点将它的颜色变为黑色，他想知道自己最少要执行多少次操作可以使得这棵树变为美丽树。

## 输入格式

第一行包含一个正整数 $n$，代表树的节点数。

第二行包含 $n$ 个非负整数 $a_1,a_2,\ldots,a_n$，其中如果 $a_i=0$，则节点 $i$ 的颜色为白色，否则为黑色。

之后 $n-1$ 行，每行包含两个正整数 $x_i,y_i$，代表存在一条连接节点 $x_i$ 和 $y_i$ 的边。

## 输出格式

输出一个整数，代表最少执行的操作次数。

## 样例

### 样例输入 #1
```
5
0 1 0 1 0
1 2
1 3
3 4
3 5

```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

将节点 $1$ 和 $3$ 变为黑色即可使这棵树变为美丽树，此时删除白色节点 $5$，剩余黑色节点仍然组成一棵树。

### 数据范围
子任务编号|数据点占比|$n$ |$a_i$ |特殊条件
:-:|:-:|:-:|:-:|:-:
$1$|$30\%$ |$\leq 10^5$ | $0\leq a_i\leq 1$|树的形态为一条链
$2$|$30\%$ | $\leq 10^5$ | $0\leq a_i\leq 1$| 只有两个节点颜色为黑色
$3$|$40\%$|$\leq 10^5$|$0\leq a_i\leq 1$|

对于全部数据，保证有 $1\leq n\leq 10^5$，$0\leq a_i\leq 1$。


---

---
title: "[GESP202406 八级] 最远点对"
layout: "post"
diff: 普及+/提高
pid: P10725
tag: ['2024', '树的遍历', 'GESP']
---
# [GESP202406 八级] 最远点对
## 题目描述

小杨有⼀棵包含 $n$ 个节点的树，这棵树上的任意⼀个节点要么是白色，要么是黑色。

小杨想知道相距最远的一对不同颜色节点的距离是多少。
## 输入格式

第一行包含⼀个正整数 $n$，代表树的节点数。

第二行包含 $n$ 个非负整数 $a_1,a_2,\cdots,a_n$（对于所有的 $1\le i\le n$，均有 $a_i$ 等于 $0$ 或 $1$），其中如果 $a_i=0$，则节点 $i$ 的颜色为白色；如果 $a_i=1$，则节点 $i$ 的颜色为黑色。

之后 $(n-1)$ 行，每行包含两个正整数 $x_i,y_i$，代表存在一条连接节点 $x_i$ 和 $y_i$ 的边。

保证输入的树中存在不同颜色的点。
## 输出格式

输出⼀个整数，代表相距最远的一对不同颜色节点的距离。
## 样例

### 样例输入 #1
```
5
0 1 0 1 0
1 2
1 3
3 4
3 5
```
### 样例输出 #1
```
3
```
## 提示

#### 样例解释

相距最远的不同颜色的一对节点为节点 $2$ 和 $5$。

#### 数据范围

**本题采用捆绑测试。**

| 子任务编号 | 得分 | $n$ | $a_i$ | 特殊条件 |
| :--: | :--: | :--: | :--: | :--: |
| $1$ |  $30$ | $\le 10^5$ | $0\le a_i\le 1$ | 树的形态为一条链 |
| $2$ | $30$ | $\le 10^3$ | $0\le a_i\le 1$ | |	
| $3$ | $40$ | $\le 10^5$ | $0\le a_i\le 1$ | |	

对于全部数据，保证有 $1\le n\le 10^5$，$0\le a_i\le 1$。


---

---
title: "[USACO25FEB] Vocabulary Quiz S"
layout: "post"
diff: 普及+/提高
pid: P11840
tag: ['USACO', '2025', '树的遍历']
---
# [USACO25FEB] Vocabulary Quiz S
## 题目描述

Bessie 正在帮助 Elsie 准备她即将到来的词汇测验。要测验的单词将从 $M$ 个不同单词的词库中抽取，其中词库里没有一个单词是另一个单词的前缀。

当词库非空时，Bessie 将从词库中选择一个单词，将其从词库中移除，并从左到右逐个字符地读给 Elsie。Elsie 的任务是在她能够唯一确定该单词时告诉 Bessie，此后 Bessie 将停止朗读。

Bessie 已经决定按顺序 $w_1,w_2,\dots,w_M$ 朗读单词。如果 Elsie 尽可能快地回答，Bessie 将朗读每个单词的多少个字符？

这些单词以一种压缩格式给出。我们将首先定义 $N+1$（$1\le N\le 10^6$）个不同的单词，然后词库将由其中所有不作为另一个单词前缀的单词组成。这些单词定义如下：

- 初始时，第 $0$ 个单词为空字符串。
- 然后对于每一个 $1\le i\le N$，第 $i$ 个单词将等于第 $p_i$ 个单词在末尾加上一个额外的字符（$0\le p_i<i$）。字符的选择使得所有 $N+1$ 个单词各不相同。
## 输入格式

输入的第一行包含 $N$，其中 $N+1$ 是以压缩格式给出的单词的数量。

以下一行包含 $p_1,p_2,\dots,p_N$，其中 $p_i$ 表示第 $i$ 个单词是通过取第 $p_i$ 个单词并在末尾添加一个字符形成的。

令 $M$ 为不是某个其他单词前缀的单词数量。以下 $M$ 行将包含 $w_1,w_2,\dots,w_M$，表示第 $w_i$ 个单词将是第 $i$ 个被朗读的单词。输入保证朗读的单词形成词库中单词的一个排列。
## 输出格式

输出 $M$ 行，其中第 $i$ 行包含 Bessie 对第 $i$ 个单词朗读的字符数量。

## 样例

### 样例输入 #1
```
5
0 1 2 3 4
5
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4
0 0 1 1
4
3
2
```
### 样例输出 #2
```
2
1
0
```
### 样例输入 #3
```
4
0 0 1 1
2
3
4
```
### 样例输出 #3
```
1
2
0
```
## 提示

样例 1 解释：

有 $6$ 个单词编号为 $0 \dots 5$。单词 $5$ 是唯一一个不是另一个单词的前缀的单词，因此它是词库中唯一的单词。一般地说，一旦库中仅剩下一个单词，Elsie 就不再需要任何字符以确定它。

样例 2 解释：

词库由单词 $2$，$3$ 和 $4$ 组成。

Elsie 需要两个字符来确定单词 $4$，因为单词 $3$ 和 $4$ 的第一个字符相同。

一旦 Bessie 朗读了单词 $3$ 的第一个字符，Elsie 就有了足够的字符来唯一确定它，因为单词 $4$ 已经被朗读。

- 测试点 $4\sim 5$：所有单词的长度均不超过 $20$。
- 测试点 $6\sim 10$：词库中所有单词的长度之和不超过 $10^7$。
- 测试点 $11\sim 18$：没有额外限制。


---

---
title: "[蓝桥杯 2024 国 Java B] 园丁"
layout: "post"
diff: 普及+/提高
pid: P12255
tag: ['2024', '数论', '树的遍历', '素数判断,质数,筛法', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Java B] 园丁
## 题目描述

小明是一位尽职尽责的园丁。这天他负责维护一棵树，树上有 $n$ 个结点 $1, 2, \ldots, n$，根结点为 $1$，结点 $i$ 的权值为 $a_i$。他需要更改一些结点的权值为任意正整数，使得对于任意一个至少有 $2$ 个儿子结点的结点 $i$ 满足：任意两个 $i$ 的儿子结点的权值的乘积都不是完全平方数。请问小明至少需要修改多少个结点的权值？
## 输入格式

输入共 $n+1$ 行。

第一行为一个正整数 $n$。

第二行为 $n$ 个由空格分开的正整数 $a_1, a_2, \ldots, a_n$。

后面 $n-1$ 行，每行两个正整数表示树上的一条边。
## 输出格式

输出共 $1$ 行，一个整数表示答案。
## 样例

### 样例输入 #1
```
6
1 2 9 8 4 4
1 2
1 3
1 4
2 5
2 6
```
### 样例输出 #1
```
2
```
## 提示

### 样例说明

其中一种方案：将结点 $2, 5$ 的权值分别修改为 $3, 2$。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，保证 $n \leq 10^3$。
- 对于 $100\%$ 的评测用例，保证 $1\leq n \leq 10^5$，$1 \leq a_i \leq 10^9$。


---

---
title: "[GCJ 2015 #3] Fairland"
layout: "post"
diff: 普及+/提高
pid: P13228
tag: ['2015', '深度优先搜索 DFS', '树的遍历', 'Google Code Jam']
---
# [GCJ 2015 #3] Fairland
## 题目描述

The country of Fairland has very strict laws governing how companies organize and pay their employees:

1. Each company must have exactly one CEO, who has no manager.
2. Every employee except for the CEO must have exactly one manager. (This means that the org chart showing all of the employees in a company is a tree, without cycles.)
3. As long as an employee is working for the company, their manager must never change. This means that if a manager leaves, then all of the employees reporting to that manager must also leave.
4. The CEO must never leave the company.
5. Every employee receives a salary -- some amount of Fairland dollars per year. An employee's salary must never change.
6. Different employees may have different salaries, and an employee's salary is not necessarily correlated with where in the org chart that employee is.

The government of Fairland has just passed one additional law:

7. The difference between the largest salary and the smallest salary in the whole company must be at most $\mathbf{D}$ Fairland dollars.

Marie is the CEO of the Fairland General Stuff Corporation, and she has to ensure that her company complies with the new law. This may require laying off some employees. She has the list of the company's employees, their managers, and their salaries. What is the largest number of employees she can keep, including herself?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each case begins with one line containing two space-separated integers $\mathbf{N}$ (the number of employees) and $\mathbf{D}$ (the maximum allowed salary difference). This is followed by one line with four space-separated integers $\left(\mathbf{S}_{0}, \mathbf{A}_{\mathrm{S}}, \mathbf{C}_{\mathrm{S}}, \mathbf{R}_{\mathrm{S}}\right)$ and then another line with four more space-separated integers $\left(\mathbf{M}_{0}, \mathbf{A}_{\mathrm{m}}, \mathbf{C}_{\mathrm{m}}\right.$ and $\left.\mathbf{R}_{\mathrm{m}}\right)$. These last eight integers define the following sequences:

* $\mathbf{S}_{\mathrm{i}+1}=\left(\mathbf{S}_{\mathrm{i}}\times \mathbf{A}_{\mathrm{S}}+\mathbf{C}_{\mathrm{S}}\right) \bmod \mathbf{R}_{\mathrm{S}}$
* $\mathbf{M}_{\mathrm{i}+1}=\left(\mathbf{M}_{\mathrm{i}}\times \mathbf{A}_{\mathrm{m}}+\mathbf{C}_{\mathrm{m}}\right) \bmod \mathbf{R}_{\mathrm{m}}$

Marie's employee ID is 0, and all other employees have IDs from 1 to $\mathbf{N}-1$, inclusive. The salary of employee $\mathrm{i}$ is $\mathbf{S}_{\mathrm{i}}$. For every employee $\mathrm{i}$ other than Marie, the manager is $\mathbf{M}_{\mathrm{i}} \bmod \mathrm{i}$. (Note that this means that $\mathbf{M}_{0}$ does not affect Marie's manager -- she has none!)

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the largest number of employees Marie can keep at the company, including herself, such that all of laws 1-7 are obeyed.
## 样例

### 样例输入 #1
```
3
1 395
18 246 615815 60
73 228 14618 195
6 5
10 1 3 17
5 2 7 19
10 13
28 931 601463 36
231 539 556432 258
```
### 样例输出 #1
```
Case #1: 1
Case #2: 3
Case #3: 5
```
## 提示

**Sample Explanation**

In Case #1, the company has only a CEO and no other employees, but it does not violate any of the laws, so no changes need to be made.

Here is the org chart for Case #2:

![](https://cdn.luogu.com.cn/upload/image_hosting/9h2ae4xp.png)

The optimal strategy is to save employees $0,1,$ and $5$ (who have salaries of $10,13,$ and $8$, respectively). It is not possible to save employee $2$, for example, because her salary is more than $5$ away from employee 0's salary of $10$; since employee 0 cannot be laid off, employee $2$ must be laid off (along with all employees who report to her).

If you want to check your sequences for employees 1 through 5, they are:

- $\mathbf{S}: 13,16,2,5,8$
- $\mathbf{M}: 17,3,13,14,16$
- Manager numbers: $17 \bmod 1=0,3 \bmod 2=1,13 \bmod 3=1,14 \bmod 4=2,16 \bmod 5=1$

**Limits**

- $1 \leq \mathrm{T} \leq 100 .$
- $0 \leq \mathrm{S}_{0}<\mathrm{R}_{\mathrm{S}} .$
- $0 \leq \mathrm{M}_{0}<\mathrm{R}_{\mathrm{m}} .$
- $0 \leq \mathrm{A}_{\mathrm{S}}, \mathrm{A}_{\mathrm{m}} \leq 1000 .$
- $0 \leq \mathrm{C}_{\mathrm{S}}, \mathrm{C}_{\mathrm{m}} \leq 10^{9} .$

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq \mathrm{N} \leq 1000 .$
- $1 \leq \mathrm{D} \leq 1000 .$
- $1 \leq \mathrm{R}_{\mathrm{S}}, \mathrm{R}_{\mathrm{m}} \leq 1000 .$

**Large dataset**

- Time limit: ~~480~~ 20 seconds.
- $1 \leq \mathrm{N} \leq 10^{6} .$
- $1 \leq \mathrm{D} \leq 10^{6} .$
- $1 \leq \mathrm{R}_{\mathrm{S}}, \mathrm{R}_{\mathrm{m}} \leq 10^{6} .$


---

---
title: "「CZOI-R4」生长的树"
layout: "post"
diff: 普及+/提高
pid: P13279
tag: ['贪心', '洛谷原创', 'O2优化', '树的遍历', '树论', '洛谷月赛', 'Ad-hoc']
---
# 「CZOI-R4」生长的树
## 题目描述

你是小 J 的园丁，你需要帮他修剪他的一棵生长的树 $T_1$。

$T_1$ 是一棵 $k$ 叉树，在第 $0$ 个时刻，$T_1$ 只有**根节点**一个节点，编号为 $1$。

接下来从第 $1$ 个时刻开始，对于每 $1$ 个时刻将**依次**发生：
- 当前的 $T_1$ 中所有儿子数量**小于** $k$ 个的节点，将补充若干个子节点使其儿子数量为 $k$，补充的节点的编号可以**任意决定（无需小于等于 $n$）**，但不可以与 $T_1$ 的其他节点的编号相同。
- 你进行若干次操作（可以不进行），每次操作指定 $T_1$ 的一个**不为根节点**的节点，将**它的子树**从 $T_1$ 上删除。

小 J 会给定你一棵有 $n$ 个节点的树 $T_2$，$T_2$ 的**根节点**编号为 $1$，他希望某个时刻后满足以下条件：
- $T_1$ 有 $n$ 个节点，且节点的编号恰好为 $1\sim n$。
- 在 $T_1,T_2$ 中，除了根节点，所有**编号相同**的节点的父亲编号相同。

你需要求出最早可以在第几个时刻后满足条件，和在此基础上的**最小**操作次数。
## 输入格式

第一行输入 $2$ 个整数 $n,k$。

接下来 $n-1$ 行，每行输入 $2$ 个整数 $u,v$，描述小 J 给定的树 $T_2$，表示编号为 $u,v$ 的节点有边相连。
## 输出格式

第一行输出 $2$ 个整数 $p,q$，表示最早可以在第 $p$ 个时刻后满足条件，在此基础上**最少**操作次数为 $q$。
## 样例

### 样例输入 #1
```
6 3
1 2
1 5
2 3
2 4
5 6
```
### 样例输出 #1
```
2 4
```
## 提示

**【样例解释】**

如图，在第 $1,2$ 个时刻这样分配节点编号，并在 $2$ 个时刻时，删除编号为 $7,8,9,10$ 的节点的子树即可。可以证明不存在更优的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/hpjqzk0l.png)

**【数据范围】**

**本题采用捆绑测试**。

- Subtask #1（$10\text{ pts}$）：$k=1$。
- Subtask #2（$10\text{ pts}$）：$T_2$ 是一棵满 $k$ 叉树。
- Subtask #3（$20\text{ pts}$）：$n,k\le10$。
- Subtask #4（$20\text{ pts}$）：$k=2$。
- Subtask #5（$40\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le u,v\le n\le 5\times 10^5$，$1\le k\le 10^6$，$\max\limits_{1\le i\le n}\{\text{son}_i\}\le k$。其中 $\text{son}_i$ 指 $T_2$ 的第 $i$ 个节点的儿子**个数**。


---

---
title: "[SNCPC2019] Unrooted Trie"
layout: "post"
diff: 普及+/提高
pid: P9648
tag: ['2019', 'O2优化', '陕西', '树的遍历', 'XCPC']
---
# [SNCPC2019] Unrooted Trie
## 题目描述

Recall the definition of a trie:

- A trie of size $n$ is a rooted tree with $n$ vertices and $(n-1)$ edges, where each edge is marked with a character;
- Each vertex in a trie represents a string. Let $s(x)$ be the string vertex $x$ represents;
- The root of the trie represents an empty string. Let vertex $u$ be the parent of vertex $v$, and let $c$ be the character marked on the edge connecting vertex $u$ and $v$, we have $s(v)$ = $s(u) + c$. Here $+$ indicates string concatenation, not the normal addition operation.

We say a trie is valid, if the string each vertex represents is distinct.

Given an unrooted tree with $n$ vertices and $(n-1)$ edges, where each edge is marked with a character, how many different vertices can be selected as the root of the tree so that the tree becomes a valid trie?

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$), indicating the size of the tree.

For the following $(n-1)$ lines, the $i$-th line contains two integers $u_i$, $v_i$ ($1 \le u_i, v_i \le n$) and a character $c_i$ separated by a space, indicating that there is an edge marked with a character $c_i$ connecting vertex $u_i$ and $v_i$. It's guaranteed that $c_i$ will only be lower-case English letters.

It's guaranteed that the given graph is a tree, and the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer, indicating the number of different vertices that can be selected as the root of the tree to make it a valid trie.

## 样例

### 样例输入 #1
```
2
6
3 1 a
3 2 a
3 4 b
4 5 c
4 6 d
6
3 1 a
3 2 a
3 4 b
5 4 c
6 4 c

```
### 样例输出 #1
```
2
0

```
## 提示

For the first sample test case, we can only select vertex 1 or vertex 2 as the root, otherwise $s(1)$ and $s(2)$ will be the same.

For the second sample test case, no matter which vertex we select as the root, $s(1)$ and $s(2)$, or $s(5)$ and $s(6)$ will be the same.

## 题目翻译

### 题目背景

trie 的定义是这样的：

- 一棵大小为 $n$ 的 trie，是一棵有着 $n$ 个节点和 $(n-1)$ 条边的有根树，每一条边上都标有一个字符；

- 在 trie 中，从根结点到树上某一结点的路径代表一个字符串，节点 $x$ 代表的字符串记为 $s(x)$，特别地，根节点代表的字符串为空串。

- 若节点 $u$ 是节点 $v$ 的父节点，且 $c$ 是连接 $u$ 与 $v$ 的边上的字符，则有 $s(v) = s(u) + c$（这里的 $+$ 表示字符串的连接，而非普通的加法运算）。

当每一个节点代表的字符串互不相同时，该 trie 是合法的。

### 题目描述

给出一个无根的 trie，求其中有多少节点可作为该 trie 的根，使得该 trie 合法。

### 输入格式

**每个测试点由多组数据组成。**

输入的第一行包含一个正整数 $T$，代表测试数据的组数。

对于每组测试数据：

数据的第一行包含一个正整数 $n$，代表 trie 的大小。

接下来的 $(n-1)$ 行中，第 $i$ 行包含两个正整数 $u_i,v_i$ 以及一个字符 $c_i$，用空格隔开，表示有一条标有 $c_i$ 的边连接着 $u_i$ 和 $v_i$。

### 输出格式

对于每组测试数据，输出一行一个正整数，表示可以成为根后可以使该 trie 合法的节点的个数。

### 说明/提示

【样例解释】

对于第一组测试数据，只能选择节点 $1$ 或节点 $2$ 作为根，否则 $s(1)$ 和 $s(2)$ 相同。

对于第二组测试数据，无论如何选择节点作为根，$s(1)$ 和 $s(2)$ 或 $s(5)$ 和 $s(6)$ 相同。

【数据范围】

对于每组数据，$1 \le n \le 2 \times 10^5$，$1 \le u_i,v_i \le n$，$c_i$ 都是小写字母。

对于每个测试点，保证给出的图是一棵树，所有的 $n$ 之和不会超过 $10^6$。


---

