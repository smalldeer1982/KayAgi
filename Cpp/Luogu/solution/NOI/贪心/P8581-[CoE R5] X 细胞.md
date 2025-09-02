# [CoE R5] X 细胞

## 题目描述

**题意简述**

**有根树**为一个有向图，该有向图有一个特殊的顶点，称之为**根**，从根出发，存在唯一的有向路径到达图中的任意其他顶点。按照习惯，一般将有根树中的顶点称为**结点**。**子树**为有根树 $T$ 的一个子图且该子图是一棵以 $T$ 中某个结点为根的有根树。在有根树中，如果有一条边从结点 $i$ 出发，到达结点 $j$，则将结点 $i$ 称为结点 $j$ 的**父结点**，将结点 $j$ 称为结点 $i$ 的**子结点**。将有根树中不存在子结点的结点称为**叶结点**。

给定有根树 $T$，第 $i$ 个结点具有权值 $a_i \in \mathbb{Z^+}$ 和 $b_i \in \mathbb{Z^+}$。

令 $T'$ 为 $T$ 的一棵子树，$F_i$ 为 $T$ 中所有以结点 $i$ 为根的子树的集合。

- 定义 $r(T') = \frac {a(T')}{b(T')}$，其中 $a(T') = \sum \limits_{j \in T'}{a_j}$，$b(T') = \sum \limits_{j \in T'}{b_j}$。

- 定义 $T_i$ 为一棵以结点 $i$ 为根的子树，$T_i$ 满足 $r(T_i) = \min \limits_{T' \in F_i}r(T')$ 且具有最多的结点数量。

- 定义 $S(T')$：对于 $T$ 中的某个结点 $j$，令其父结点为 $i$，则 $j \in S(T')$ 当且仅当 $i \in T'$ 但 $j \notin T'$ 。

给定一棵具有 $n$ 个结点的有根树 $T$，令根结点为 $i$，对其执行以下操作：

（$1$）将根结点 $i$ 放入结点集合 $Q$，即初始时置 $Q \leftarrow \{i\}$；

（$2$）任取 $Q$ 中的一个元素，令其为 $j$，确定 $T_j$，对于结点 $k \in S(T_j)$，置 $a_k \leftarrow a_k + \lceil r(T_j) \rceil$；

（$3$）从集合 $Q$ 中删除元素 $j$，并置 $Q \leftarrow Q \cup S(T_j)$；

（$4$）若集合 $Q = \varnothing $，结束操作，否则转步骤（$2$）。

每执行一次步骤（$2$）就会确定一棵 $T$ 的子树，假设在结束操作时一共执行了  $m$ 次步骤（$2$）,令第 $i$ 次执行步骤（$2$）所确定的子树为 $K_i$，最小化以下 $W$ 值：

$$W = 1 \times \lceil r(K_1) \rceil + 2 \times \lceil r(K_2) \rceil + \cdots + m \times \lceil r(K_m) \rceil = \sum_{i = 1}^{m}i \times \lceil r(K_i) \rceil$$

$\mathbb{Z^+}$ 表示全体正整数，$\lceil x \rceil$ 表示不小于 $x$ 的最小整数。

------------

**原版题面**

$\text{X}$ 细胞是来自于仙女座星系 $\text{Gamma}$ 行星的一种古老生命形式。

初始时，只有 $1$ 个 $\text{X}$ 细胞，而 $\text{X}$ 细胞可以通过直接分裂来产生后代 $\text{X}$ 细胞。对于某个 $\text{X}$ 细胞 $i$ 来说，如果它产生了一个直接后代 $\text{X}$ 细胞 $j$，则将细胞 $i$ 称为细胞 $j$ 的**母细胞**，将细胞 $j$ 称为 $i$ 的**子细胞**。

注意，母细胞、子细胞的定义不具有传递性。假设细胞 $i$ 产生了一个直接后代细胞 $j$，细胞 $j$ 又产生了一个直接后代细胞 $k$，则将 $j$ 称为 $i$ 的子细胞，$k$ 称为 $j$ 的子细胞，但 $k$ 不是 $i$ 的子细胞。

每个 $\text{X}$ 细胞具有活力值 $h_x$ 和体积 $v_x$，为了研究的方便，人们为 $\text{X}$ 细胞定义了**变异指数**

$$d_x = \frac{h_x}{v_x}$$

该指数用于衡量 $\text{X}$ 细胞对环境的适应性，变异指数越低，细胞存活的概率越高。

人们发现，当 $\text{X}$ 细胞受到特定的外界刺激后，它会激活并开始一种被人们称为**同化**的过程来转变为一个 $\text{Z}$ 细胞。在同化过程开始前，激活的 $\text{X}$ 细胞会改变自身状态成为一个 $\text{Y}$ 细胞，$\text{Y}$ 细胞会不断吸收它的子细胞并进行融合，使得该子细胞成为 $\text{Y}$ 细胞的一部分。

在融合后，$\text{Y}$ 细胞的活力值和体积为融合前的细胞活力值和体积的加和。也就是说，假设有 $n$ 个细胞经过融合成为一个 $\text{Y}$ 细胞，这 $n$ 个细胞的活力值和体积分别为 $h_1$，$h_2$，…，$h_n$ 和 $v_1$，$v_2$，…，$v_n$，则融合完成后，该 $\text{Y}$ 细胞的活力值 $h_y = \sum_{i=1}^{n}h_i$，体积 $v_y = \sum_{i=1}^{n}v_i$，变异指数 $d_y = \frac{h_y}{v_y}$。

在同化过程中，$\text{Y}$ 细胞会遵循以下原则：

- 如果某个子细胞 $j$ 的母细胞 $i$ 尚未被同化，则该子细胞 $j$ 不会被同化。
- 能够使得 $\text{Y}$ 细胞变异指数尽可能地小且同化尽可能多的细胞。

当 $\text{Y}$ 细胞无法再同化更多的细胞时，它会停止同化过程，转变为一个 $\text{Z}$ 细胞并释放信息素（状态转变前后，细胞的活力值和体积不变）。该信息素会产生以下作用：令生成的 $\text{Z}$ 细胞的变异指数为 $d_z = \frac{h_z}{v_z}$，如果某个尚未被同化的子细胞 $j$ 的母细胞 $i$ 被该 $\text{Z}$ 细胞同化，则该子细胞 $j$ 的活力值 $h_j$ 增加 $\lceil d_z \rceil$（$\lceil x \rceil$ 表示不小于 $x$ 的最小整数）。

需要注意，在同化过程结束时，$\text{Y}$ 细胞的变异指数要求尽可能地小，但在同化过程中，$\text{Y}$ 细胞的变异指数并不要求时刻保持最小（参见输入 $\#1$）。

研究人员需要通过一种专用设备来产生激活 $\text{X}$ 细胞的特定外界刺激，每次使用该设备都会消耗一定数量的激活剂，消耗的激活剂数量 $c_t$ 使用以下公式进行计算：

$$c_t = t \times \lceil d_z \rceil $$

其中 $t$ 表示使用该设备的次数序号（初始时从 $1$ 开始计数），$d_z$ 表示该次激活最终生成的 $\text{Z}$ 细胞的变异指数。

由于母细胞会分泌信息素使得子细胞无法被激活，只能选择不存在母细胞或者母细胞已经被同化的 $\text{X}$ 细胞作为特定外界刺激的对象，以使其激活并开始同化过程。

给定所有 $\text{X}$ 细胞之间的相互关系及其活力值和体积，鉴于激活剂非常难以制造，现在需要你制定一个最优的 $\text{X}$ 细胞激活顺序方案，使得所有的 $\text{X}$ 细胞均转变为 $\text{Z}$ 细胞且消耗的激活剂数量最少。

你只需要输出该最少值即可。


## 说明/提示

**样例说明**

输入 $\#1$：

- 激活细胞 $1$，同化细胞 $2、3$，产生的 $\text{Z}$ 细胞活力值 $h_z = 24$，体积 $v_z = 12$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {24}{12} = 2$。

- $1$ 次激活总共最少需要消耗的激活剂数量为 $c_1 = t \times \lceil d_z \rceil = 1 \times \lceil \frac {24}{12} \rceil = 1 \times 2 = 2$。

- 初始时 $\text{Y}$ 细胞的变异指数为 $5$，当同化细胞 $2$ 后，变异指数为 $6$，当同化细胞 $3$ 后，变异指数变为 $2$。由此可见，在同化过程中，$\text{Y}$ 细胞的变异指数并不是时刻都保持最小，只需在最后停止同化转变为 $\text{Z}$ 细胞时为最小值即可。

输入 $\#2$：

- 激活细胞 $1$，同化细胞 $2$，产生的 $\text{Z}$ 细胞活力值 $h_z = 2 + 2 = 4$，体积 $v_z = 2 + 3 = 5$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {4}{5}$，该次激活消耗的激活剂数量 $c_1 = t \times \lceil d_z \rceil= 1 \times \lceil \frac {4}{5} \rceil = 1 \times 1 = 1$，该 $\text{Z}$ 细胞释放信息素使得细胞 $3$ 的活力值增加 $1$，则细胞 $3$ 的活力值变为 $13$；

- 激活细胞 $3$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 13$，体积 $v_z = 4$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {13}{4}$，该次激活消耗的激活剂数量 $c_2 = t \times \lceil d_z \rceil = 2 \times \lceil \frac {13}{4} \rceil= 2 \times 4 = 8$。

- $2$ 次激活总共最少需要消耗的激活剂数量为 $c_1 + c_2 = 1 + 8 = 9$。


输入 $\#3$：

- 激活细胞 $1$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 1$，体积 $v_z = 1$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {1}{1} = 1$。总共消耗的激活剂数量 $c_1 = t \times \lceil d_z \rceil = 1 \times \lceil 1 \rceil = 1$。$\text{Z}$ 细胞释放信息素，使得细胞 $2$、$5$ 的活力值各增加 $1$，细胞 $2$、$5$ 的活力值当前为 $8$、$10$。

- 激活细胞 $2$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 8$，体积 $v_z = 1$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {8}{1} = 8$。总共消耗的激活剂数量 $c_2 = t \times \lceil d_z \rceil = 2 \times \lceil 8 \rceil = 16$。$\text{Z}$ 细胞释放信息素，使得细胞 $3$、$4$ 的活力值各增加 $8$，细胞 $3$、$4$ 的活力值当前为 $18$、$28$。

- 激活细胞 $4$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 28$，体积 $v_z = 1$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {28}{1} = 28$。总共消耗的激活剂数量 $c_3 = t \times \lceil d_z \rceil = 3 \times \lceil 28 \rceil = 84$。

- 激活细胞 $3$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 18$，体积 $v_z = 1$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {18}{1} = 18$。总共消耗的激活剂数量 $c_4 = t \times \lceil d_z \rceil = 4 \times \lceil 18 \rceil = 72$。

- 激活细胞 $5$，未同化其他细胞，产生的 $\text{Z}$ 细胞活力值 $h_z = 10$，体积 $v_z = 1$，变异指数 $d_z = \frac {h_z}{v_z} = \frac {10}{1} = 10$。总共消耗的激活剂数量 $c_5 = t \times \lceil d_z \rceil = 5 \times \lceil 10 \rceil = 50$。

- $5$ 次激活总共最少需要消耗的激活剂数量为 $c_1 + c_2 + c_3 + c_4 + c_5 = 1 + 16 + 84 + 72 + 50 = 223$。

输入 $\#4$：

- 激活细胞 $1$，未同化其他细胞，产生的 $\text{Z}$ 细胞变异指数 $d_z = \frac {h_z}{v_z} = \frac {4}{1}$，释放信息素使得细胞 $2、5、9$ 的活力值增加 $4$，消耗激活剂 $c_1 = 1 \times \lceil \frac {4}{1} \rceil = 1 \times 4 = 4$。

- 激活细胞 $5$，同化细胞 $6、7、8$，产生的 $\text{Z}$ 细胞变异指数 $d_z = \frac {h_z}{v_z} = \frac {84}{4}$，消耗激活剂 $c_2 = 2 \times \lceil \frac {84}{4} \rceil = 2 \times 21 = 42$。

- 激活细胞 $9$，同化细胞 $10、11、12$，产生的 $\text{Z}$ 细胞变异指数 $d_z = \frac {h_z}{v_z} = \frac {71}{4}$，消耗激活剂 $c_3 = 3 \times \lceil \frac {71}{4} \rceil = 3 \times 18 = 54$。

- 激活细胞 $2$，同化细胞 $3、4$，产生的 $\text{Z}$ 细胞变异指数 $d_z = \frac {h_z}{v_z} = \frac {17}{3}$，消耗激活剂 $c_4 = 4 \times \lceil \frac {17}{3} \rceil = 4 \times 6 = 24$。

- $4$ 次激活总共最少需要消耗的激活剂数量为 $c_1 + c_2 + c_3 + c_4 = 4 + 42 + 54 + 24 = 124$。

------------

**数据范围**

**本题采用捆绑测试。某些子任务的输入文件较大，请使用合适的输入读取方式。**

| 子任务 | 分值 | $n \leq$ | 特殊性质 | 时间限制 | 内存限制 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $10$ | $20$ |   | $1 \text{ s}$ |  $256 \text{ MB}$ | |
| $2$ | $30$ | $10^3$ |   | $1 \text{ s}$ | $256 \text{ MB}$ | $1$ |
| $3$ | $10$ | $10^5$ |   | $1 \text{ s}$ | $256 \text{ MB}$ | $1 \sim 2$ |
| $4$ | $10$ | $10^6$ | $\text{A}$ | $3 \text{ s}$ | $256 \text{ MB}$ |  |
| $5$ | $20$ | $10^6$ | $\text{B}$ | $1 \text{ s}$ | $320 \text{ MB}$ |  |
| $6$ | $10$ | $10^6$ | $\text{C}$ | $1 \text{ s}$ | $256 \text{ MB}$ |  |
| $7$ | $10$ | $10^6$ |   | $3 \text{ s}$ | $320 \text{ MB}$ | $1 \sim 6$ |

- 特殊性质 $\text{A}$：即给定的有根树所对应的图是星形图。$\forall \  2 \leq i \leq n$，$f_i = 1$。
- 特殊性质 $\text{B}$：给定的有根树所对应的图是有向链。$\forall \ 2 \leq i \leq n$，$f_i = i - 1$。
- 特殊性质 $\text{C}$：数据随机生成。$\forall \ 2 \leq i \leq n$，$f_i$ 是 $[1, i - 1]$ 中随机选取的整数。$h_i, v_i$ 是 $[1, 10^6]$ 中随机选取的整数。


对于 $100 \%$ 的数据，$1 \leq n \leq 10^6$，$1 \leq h_i \leq 10^6$，$1 \leq v_i \leq 10^6$，答案不超过 $10^{18}$。

## 样例 #1

### 输入

```
3
1 2
5 7 12
1 1 10```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 1
2 2 12
2 3 4```

### 输出

```
9```

## 样例 #3

### 输入

```
5
1 2 2 1
1 7 10 20 9
1 1 1 1 1```

### 输出

```
223```

## 样例 #4

### 输入

```
12
1 2 3 1 5 6 7 1 9 10 11
4 10 2 1 50 1 20 9 40 2 15 10
1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
124```

# 题解

## 作者：metaphysis (赞：10)

### 题意简述

**有根树**为一个有向图，该有向图有一个特殊的顶点，称之为**根**，从根出发，存在唯一的有向路径到达图中的任意其他顶点。按照习惯，一般将有根树中的顶点称为**结点**。**子树**为有根树 $T$ 的一个子图且该子图是一棵以 $T$ 中某个结点为根的有根树。在有根树中，如果有一条边从结点 $i$ 出发，到达结点 $j$，则将结点 $i$ 称为结点 $j$ 的**父结点**，将结点 $j$ 称为结点 $i$ 的**子结点**。将有根树中不存在子结点的结点称为**叶结点**。

给定有根树 $T$，第 $i$ 个结点具有权值 $a_i \in \mathbb{Z^+}$ 和 $b_i \in \mathbb{Z^+}$。

令 $T'$ 为 $T$ 的一棵子树，$F_i$ 为 $T$ 中所有以结点 $i$ 为根的子树的集合。

- 定义 $r(T') = \frac {a(T')}{b(T')}$，其中 $a(T') = \sum \limits_{j \in T'}{a_j}$，$b(T') = \sum \limits_{j \in T'}{b_j}$。

- 定义 $T_i$ 为一棵以结点 $i$ 为根的子树，令 $r_i = r(T_i)$，$T_i$ 满足 $r_i = \min \limits_{T' \in F_i}r(T')$ 且具有最多的结点数量。

- 定义 $S(T')$：对于 $T$ 中的某个结点 $j$，令其父结点为 $i$，则 $j \in S(T')$ 当且仅当 $i \in T'$ 但 $j \notin T'$ 。

给定一棵具有 $n$ 个结点的有根树 $T$，令根结点为 $i$，对其执行以下操作：

（$1$）将根结点 $i$ 放入结点集合 $Q$，即初始时置 $Q \leftarrow \{i\}$；

（$2$）任取 $Q$ 中的一个元素，令其为 $j$，确定 $T_j$，对于结点 $k \in S(T_j)$，置 $a_k \leftarrow a_k + \lceil r(T_j) \rceil$；

（$3$）从集合 $Q$ 中删除元素 $j$，并置 $Q \leftarrow Q \cup S(T_j)$；

（$4$）若集合 $Q = \varnothing $，结束操作，否则转步骤（$2$）。

每执行一次步骤（$2$）就会确定一棵 $T$ 的子树，假设在结束操作时一共执行了  $m$ 次步骤（$2$）,令第 $i$ 次执行步骤（$2$）所确定的子树为 $K_i$，最小化以下 $W$ 值：

$$W = 1 \times \lceil r(K_1) \rceil + 2 \times \lceil r(K_2) \rceil + \cdots + m \times \lceil r(K_m) \rceil = \sum_{i = 1}^{m}i \times \lceil r(K_i) \rceil$$



------------

### 题解


为了便于说明，首先证明以下若干命题。


**命题1**：给定四个正整数 $a,b,c,d$，若有 $\frac{a}{b} \le \frac{c}{d}$，则有 $\frac{a+c}{b+d} \le \frac{c}{d}$。

**证明**：由于 $\frac{a}{b} \le \frac{c}{d}$，则有 $ad - bc \le 0$，而 $\frac{a+c}{b+d} - \frac{c}{d} = \frac{(a+c)d - (b+d)c}{(b+d)d} = \frac{ad -bc}{(b+d)d} \le 0$，故 $\frac{a+c}{b+d} \le \frac{c}{d}$。


根据 **命题1**，可以容易知道，如果子结点的 $r$ 值小于或者等于父结点的 $r$ 值，那么将子结点和父结点合并后父结点的 $r$ 值不会变大，反之，如果子结点的 $r$ 值大于或者等于父结点的 $r$ 值，将子结点和父结点合并后父结点的 $r$ 值不会变小。

**命题2**：若结点 $j \in S(T_i)$，则 $r_j \gt r_i$。


**证明**：假设 $r_j \le r_i$，根据 **命题1**，将 $T_i$ 与 $T_j$ 合并后，$r_i$ 不会变大且 $T_i$ 具有更多的结点数量，得出 $T_i$ 应该包含 $T_j$，因此 $j \in T_i$，而给定 $j \in S(T_i)$，得知 $j \notin T_i$，产生矛盾，故原假设不成立。



**命题3**：若结点 $j \in T_i$，则 $T_i$ 包含 $T_j$，即 $ \forall \  p \in T_j, \ p \in T_i$。

**证明**：假设 $\exists \ p \in T_j, \ p \notin T_i$，根据子树的定义，$T_i$ 包含的是 $T_j$ 的一棵以结点 $j$ 为根的子树 $T_j'$，而对于任意 $T_j$ 的子树 $T_j'$ 来说，均有 $r(T_j') \ge r(T_j)$（若不然，$T_j$ 的 $r_j$ 不是最优），则包含整个 $T_j$ 比包含 $T_j'$ 不会使得 $r_i$ 变大，但是能够具有更多的结点，因此原来的 $T_i$ 不是最优的，产生矛盾，故假设不成立。


**命题4**：$T_i$ 唯一。

**证明**：假设 $T_i$ 不唯一，对于结点 $i$ 来说，存在两棵以结点 $i$ 为根的子树 $T_i$ 和 $T_i'$，满足 $r(T_i) = r(T_i') = \min \limits_{T' \in F_i}r(T')$，令 $A = T_i \cap T_i'$，由于 $T_i$ 和 $T_i'$ 均是以结点 $i$ 为根的子树，故 $A \neq \varnothing$，而由于 $T_i$ 和 $T_i'$ 不同但具有相同的结点数量，肯定存在这样结点 $p$ 和 $q$，满足 $p$ 是 $q$ 的父结点，且 $p \in A, \ q \in T_i', \  q \notin T_i$（若不存在，则表明 $T_i$ 包含 $T_i'$，但由于 $T_i$ 和 $T_i'$ 不同，则 $T_i'$ 的所有结点均在 $T_i$ 内，且 $T_i$ 的结点数量比 $T_i'$ 多，与假设矛盾），进而可以得到 $q \in S(T_i)$，根据 **命题2**，有 $r_q > r(T_i)$，根据 **命题3**，$T_i'$ 包含 $T_q$，由于 $r_q > r(T_i) = r(T_i')$，根据 **命题1**， $T_i'$ 在合并 $T_q$ 之前应该具有更小的 $r$ 值，表明 $r(T_i')$ 不是最优的，产生矛盾，故原假设不成立，$T_i$ 唯一。



------------


先不考虑结点权值的改变，思考如何确定给定结点 $i$ 的 $r_i$ 和 $T_i$。

对于某个结点 $i$ 来说，我们在第一时间无法确定应该添加哪些结点来使得 $r_i$ 更小，因为在添加顺序上有限制，必须先添加父结点才能添加子结点，而有时会出现这样的一种情形：添加某个结点 $j$ 后，$r_i$ 是暂时变大的，而在继续添加结点 $j$ 的子结点 $k$ 后，$r_i$ 会变小。

根据 **命题2** 和 **命题3**，如果反过来，假设已经确定了结点 $i$ 的所有子结点 $i_1，i_2, \cdots,i_k$ 对应的 $r_{i_1}, r_{i_2}, \cdots, r_{i_k}$ 和 $T_{i_1}, T_{i_2}, \cdots, T_{i_k}$，那么对于某个子结点 $j$ 来说，如果 $r_{j}$ 是所有子结点中最小的，若 $r_{j}$ 大于 $\frac{a_i}{b_i}$，显然不应将结点 $i$ 与 $T_{j}$ 合并，因为这将使得 $r_i$ 变大，若 $r_{j}$ 小于或等于 $\frac{a_i}{b_i}$，那么应该将结点 $i$ 与 $T_{j}$ 合并，这样可以得到一棵以结点 $i$ 为根且具有更小 $r_i$ 值的子树。由于合并之后，$r_i$ 的最优值会发生改变且 $T_{j}$ 的后继结点 $S(T_{j})$ 也可能被合并以优化 $r_i$ 和 $T_i$，因此需要将其与原来未合并的子结点一并考虑。这提示我们应该考虑一种自底向上的方法来确定 $r_i$ 和 $T_i$，因此有以下的初步算法：

#### 算法1

（$1$）如果结点 $i$ 是叶结点，则 $T_i$ 为结点 $i$ 本身，$r_i = \frac{a_i}{b_i}$；

（$2$）如果结点 $i$ 不是叶结点，令其子结点为 $i_1，i_2, \cdots,i_k$，假设已经确定了所有子结点的 $r_{i_1}, r_{i_2}, \cdots, r_{i_k}$ 和 $T_{i_1}, T_{i_2}, \cdots, T_{i_k}$，置 $T_i \leftarrow \{i\}$，$r_i \leftarrow \frac{a_i}{b_i}$，将结点 $i$ 的所有子结点加入结点集合 $P$，即置 $P \leftarrow \{i_1，i_2, \cdots,i_k\}$；

（$2.1$）从 $P$ 中选择一个结点 $j$，使得 $r_j = \min \limits_{k \in P}r_k$；

（$2.2$）如果 $r_j \gt r_i$，算法结束；

（$2.3$）将 $T_j$ 与 $T_i$ 合并，即置 $T_i \leftarrow T_i \cup T_j$；

（$2.4$）将 $j$ 从 $P$ 中删除，并将 $S(T_j)$ 加入 $P$，即置 $P \leftarrow P \cup S(T_j) - \{j\}$；

（$2.5$）若 $P = \varnothing $，算法结束，否则转步骤（$2.1$）。

可以使用深度优先遍历来实现 **算法1**，如果在寻找最小值时使用朴素的线性扫描方法，则可以在 $O(n^2)$ 的时间内确定某个结点 $i$ 的 $r_i$ 和 $T_i$。


现在来尝试改进 **算法1** 的时间复杂度。注意到在 **算法1** 中，每次均需要从集合 $P$ 中选择一个具有最小 $r$ 值的结点，如果使用朴素的线性扫描，时间复杂度为 $O(n)$，如果使用可并堆（$\texttt{mergeable heap}$），则可以将该步骤的时间复杂度降低为 $O(\text{log}n)$，从而使得 **算法1** 的时间复杂度降低。

#### 算法2

令 $\ \widehat{a_i} = \sum \limits_{j \in T_i}a_j, \ \widehat{b_i} = \sum \limits_{j \in T_i}b_j$。

（$1$）如果结点 $i$ 是叶结点，则 $T_i$ 为结点 $i$ 本身，置 $r_i \leftarrow \frac{a_i}{b_i}, \widehat{a_i} \leftarrow a_i, \ \widehat{b_i} \leftarrow b_i, \ MH_i \leftarrow \varnothing$；

（$2$）如果结点 $i$ 不是叶结点，令其子结点为 $i_1, i_2, \cdots, i_k$，假设已经确定了所有子结点的 $r_{i_1}, r_{i_2}, \cdots, r_{i_k}$ 和 $T_{i_1}, T_{i_2}, \cdots, T_{i_k}$：

（$2.1$）置 $T_i \leftarrow \{i\}, r_i \leftarrow \frac{a_i}{b_i}, \widehat{a_i} \leftarrow a_i, \ \widehat{b_i} \leftarrow b_i, MH_i \leftarrow \{(i_1, r_{i_1}),(i_2, r_{i_2}),\cdots,(i_k, r_{i_k})\}$；

（$2.2$）若 $MH_i = \varnothing $，算法结束，否则选择 $MH_i$ 中的一个配对 $(j, r_j)$，该配对的第二个分量的值最小；

（$2.3$）若 $r_i \ge r_j$：

（$2.3.1$）置 $\widehat{a_i} \leftarrow \widehat{a_i} + \widehat{a_j}, \ \widehat{b_i} \leftarrow \widehat{b_i} + \widehat{b_j}, \ r_i = \frac{\widehat{a_i}}{\widehat{b_i}}$；

（$2.3.2$）置 $MH_i \leftarrow MH_i \cup MH_j - \{(j, r_j)\}$，转步骤（$2.2$）；

（$2.4$）否则，若 $r_i \lt r_j$，算法结束。

现在来分析 **算法2** 的时间复杂度。将配对插入可并堆的操作最多执行 $n$ 次，从可并堆中获取第二个分量值最小的操作执行的次数最多是可并堆合并次数的两倍，即 $2n$ 次，从可并堆中删除配对操作执行的次数是可并堆合并的次数，即 $n$ 次。由于可并堆的合并是在不相交集合之间的合并（因为 $MH_i \cap MH_j = \varnothing$），因此最多的合并次数为 $n$ 次。故在可并堆上的操作最多为 $5n$ 次，而每次可并堆的操作时间可以做到 $O(\text{log}n)$，因此总的时间复杂度为 $O(n\text{log}n)$。

由于题目要求在确定某个结点 $i$ 的 $r_i$ 和 $T_i$ 后，需要对所有结点 $j \in S(T_i)$ 执行操作：$a_j \leftarrow a_j + \lceil r_i \rceil$，可行的方法是反复调用 **算法1**，时间复杂度为 $O(n^3)$，如果反复调用 **算法2**，时间复杂度为 $O(n^2\text{log}n)$。

通过进一步的思考，可以发现以下事实：令根结点为 $i$，当使用 **算法2** 确定 $r_i$ 和 $T_i$ 后，由于是使用自底向上的方式来确定的，此时对于树中的所有结点 $j$，$r_j$ 和 $T_j$ 均已确定，接下来需要对在 $S(T_i)$ 中的结点进行权值更新的操作，考虑某个结点 $k \in S(T_i)$，当更新 $a_k = a_k + \lceil r_i \rceil$ 后，可能需要重新确定 $r_k$ 和 $T_k$，但由于 $k$ 的子结点和后代结点 $l$ 的 $r_l$ 和 $T_l$ 并未改变，此时并不需要再次调用 **算法2** 从头开始计算 $r_l$ 和 $T_l$，而只需要利用在确定 $r_i$ 和 $T_i$ 时所得到的结果。因此有以下优化的算法 （参考资料 $\texttt{[1]}$）：

#### 算法3

（$1$）设立队列 $Q$，初始时将根结点加入 $Q$；

（$2$）从队列 $Q$ 中取队首元素，令其为 $i$，使用 **算法2** 确定结点 $i$ 的 $r_i$ 和 $T_i$;

（$3$）对于结点 $j \in S(T_i)$ ，置 $a_j \leftarrow a_j + \lceil r_i \rceil, \ r_j \leftarrow \frac{a_j} {b_j}$，并将 $j$ 加入 $Q$；

（$4$）从 $Q$ 中删除 $i$，若队列为空，算法停止，否则转步骤（$2$）。

现在来分析 **算法3** 的时间复杂度。与 **算法2** 类似，除了在寻找具有最小第二分量值的配对时的操作次数最多为 $3n$ 次之外，其他的操作次数没有变化，而每次在可并堆上的操作时间复杂度可以做到 $O(\text{log}n)$，因此总的时间复杂度仍为 $O(n\text{log}n)$。

在 **算法3** 中，每执行一次步骤（$2$）就会生成一棵有根树，令第 $i$ 次生成的有根树为 $K_i$，将每棵有根树使用一个结点 $i$ 来表示，其权值为 $w_i = \lceil r(K_i) \rceil$，则可以得到一棵新的有根树 $T_w$，最小化 $W$ 值的问题可以转化为以下问题：从根结点开始，逐次删除结点，只有在删除父结点后才能删除子结点，第 $i$ 次删除结点的代价为结点权值与删除次数序号的乘积，如何最小化删除所有结点的代价之和。

根据 **命题4**，$T_i$ 是唯一的，因此生成的这棵新的有根树也是唯一的，根据 **命题2**，可知这棵新的有根树，从根结点出发，向着叶结点的任意一条路径走，所经过的结点的权值必定是递增的。根据这两个性质，似乎可以采用这样一种贪心的策略：在当前可删除的结点中选择一个权值最大的结点进行删除。依照这种思路，对于 **输入#3** 来说，激活细胞的最优顺序应该是：$5$、$1$、$2$、$3$、$4$，最终得到的最小删除代价为 $247$，并不是最优的。什么地方出问题了？关键还是在于删除具有先后顺序，如果删除不具有先后顺序，直接选择权值最大的结点进行删除肯定可以得到最小的删除代价，但是一旦具有先后顺序，只选取当前可删除的结点中的具有权值最大的结点可能无法做到最优。

通过手工构造简单的测试数据，我们可以很快发现，要使得删除代价 $W$ 最优，除了根结点以外，在树中具有最大权值的结点应该在父结点删除后立即删除。也就是说，可以证明（参考资料 $\texttt{[2]}$），以下贪心策略是正确的：为了最小化 $W$，树中除根结点外权值最大的结点，需要在它的父结点被删除后立即删除。

举个例子，假设有三个结点 $a,\ b, \ c$，结点 $b$ 是结点 $c$ 的父结点，从第 $t$ 次开始依次删除这三个结点，结点 $c$ 的权值最大，因此结点 $b$ 和 $c$ 要求连续删除，则有两种删除顺序，第一种顺序是 $a, \ b, \ c$，第二种顺序是 $b, \ c, \ a$，第一种顺序的删除代价为：

$$W_1 = t \times w_a + (t + 1)\times w_b + (t + 2)\times w_c$$

第二种删除顺序的代价是：

$$W_2 = t\times w_b + (t + 1)\times w_c + (t + 2)\times w_a$$

我们来比较两种顺序的删除代价：

$$W_1 - W_2 = w_b + w_c - 2w_a$$

需要判断 $w_b + w_c - 2w_a$ 的大小，将其转换一下，实际上就是要判断 $\frac{w_b + w_c}{2}$ 和 $w_a$ 的大小关系，也就是说，如果结点 $b$ 和 $c$ 的平均权值大于结点 $a$ 的权值，则应该选择第二种删除顺序，即先删除 $b$ 和 $c$，然后再删除 $a$，否则就应该先删除 $a$ ，再删除 $b$ 和 $c$。这提示我们，删除的优先顺序不是与单个结点的权值相关，而是与多个结点的平均权值有关。可以证明，由于删除的代价与删除的次序序号成线性关系，当结点数增多时，上述性质仍然成立（参考资料 $\texttt{[2]}$）。那么问题转化为以下的问题：对于有根树中的每个结点 $i$，确定以结点 $i$ 为根的具有最多结点的子树 $T_i$，该子树 $T_i$ 具有最大的平均权值。按照平均权值进行贪心选择来删除结点，能够获得最小化的删除代价。而这个问题，实际上就是将第一次调用 **算法3** 得到的新的有根树 $T_w$ 的结点权值设置为 $a_i = w_i = \lceil r(K_i) \rceil, \ b_i = 1$，从根结点开始再调用一次 **算法2**，只不过将 **算法2** 中的取最小值改成取最大值。

在确定了新的有根树 $T_w$ 中所有结点 $i$ 的 $r_i$ 和 $T_i$ 后，令 $W$ 表示总代价，$t$ 为当前的操作序号，则可以使用以下算法来确定 $W$ 的最小值：

#### 算法4

（$1$）初始时，置 $W \leftarrow 0, \ t \leftarrow 1$，将根结点的配对 $(i, \ r_i)$ 送入堆 $H$；

（$2$）若 $H = \varnothing$，算法停止，否则取 $H$ 中的一个配对 $(j, \ r_j)$，该配对的第二个分量值最大；

（$3$）置 $W \leftarrow W + t \times w_j, \ t \leftarrow t + 1$；

（$4$）从 $H$ 中删除配对 $(j, \ r_j)$，对于 $k \in S(T_j)$，将配对 $(k, \ r_k)$ 送入 $H$，转步骤（$2$）。


最后，**算法4** 所得到的值 $W$ 即为解。如果使用二叉堆来实现 **算法4**，易知其时间复杂度为 $O(n\text{log}n)$。

------------


#### 参考实现

```
#include <bits/stdc++.h>

using namespace std;

const int LENGTH = (1 << 20);

inline int nextChar()
{
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline bool nextInt(int &x)
{
    static char negative = 0, c = nextChar();
    negative = 0, x = 0;
    while ((c < '0' || c > '9') && c != '-') { if (c == EOF)  return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

const int MAXV = 1000010, MAXE = 2100010;

double ri[MAXV];
int n, visited[MAXV], MH[MAXV], head[MAXV], tot;
long long w[MAXV], ai[MAXV], bi[MAXV];

struct edge { int v, nxt; } edges[MAXE];
struct NODE { double ratio; int v, lc, rc, d; };

struct MH
{
    NODE nd[MAXV];
    int cnt = 0, maxHeap = 0;
    inline bool cmp(double &a, double &b) { return maxHeap ? a < b : a > b; }
    int merge(int x, int y)
    {
        if (!x || !y) return x | y;
        if (cmp(nd[x].ratio, nd[y].ratio)) swap(x, y);
        nd[x].rc = merge(nd[x].rc, y);
        if (nd[nd[x].lc].d < nd[nd[x].rc].d) swap(nd[x].lc, nd[x].rc);
        nd[x].d = nd[nd[x].rc].d + 1;
        return x;
    }
    int get(double ratio, int v)
    {
        ++cnt;
        nd[cnt].ratio = ratio;
        nd[cnt].v = v;
        nd[cnt].lc = nd[cnt].rc = nd[cnt].d = 0;
        return cnt;
    }
    int push(int x, int y) { return merge(x, y); }
    NODE top(int x) { return nd[x]; }
    int pop(int x) { return merge(nd[x].lc, nd[x].rc); }
}H;

void dfs(int u)
{
    visited[u] = 1;
    ri[u] = (double)ai[u] / bi[u];
    if (head[u] == -1) return;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].v;
        if (!visited[v])
        {
            dfs(v);
            int y = H.get(ri[v], v);
            if (!MH[u]) MH[u] = y;
            else MH[u] = H.push(MH[u], y);
        }
    }

    while (MH[u])
    {
        NODE lt = H.top(MH[u]);
        if (H.cmp(lt.ratio, ri[u])) break;
        MH[u] = H.pop(MH[u]);
        ai[u] += ai[lt.v], bi[u] += bi[lt.v];
        ri[u] = (double)ai[u] / bi[u];
        MH[u] = H.merge(MH[u], MH[lt.v]);
    }
}

void add(int u, int v)
{
    edges[tot].v = v;
    edges[tot].nxt = head[u];
    head[u] = tot++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    nextInt(n);

    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 2, u; i <= n; i++)
    {
        nextInt(u);
        add(u, i);
    }
    for (int i = 1, av; i <= n; i++)
    {
        nextInt(av);
        ai[i] = av;
    }
    for (int i = 1, bv; i <= n; i++)
    {
        nextInt(bv);
        bi[i] = bv;
    }

    int R = 1;

    queue<int> q;
    q.push(R);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        dfs(u);
        w[u] = ai[u] = ceil(ri[u]), bi[u] = 1;
        head[u] = -1;
        while (MH[u])
        {
            NODE lt = H.top(MH[u]);
            MH[u] = H.pop(MH[u]);
            ai[lt.v] += ai[u];
            add(u, lt.v);
            q.push(lt.v);
        }
    }

    H.cnt = 0;
    H.maxHeap = 1;
    for (int i = 1; i <= n; i++) visited[i] = 0;
    dfs(R);

    long long W = 0, t = 1;
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(ri[R], R));
    while (!pq.empty())
    {
        pair<double, int> gt = pq.top();
        pq.pop();
        W += t * w[gt.second];
        for (int i = head[gt.second]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].v;
            pq.push(make_pair(ri[v], v));
        }
        t++;
    }
    cout << W << '\n';

    return 0;
}
```
------------

#### 参考资料

$\texttt{[1] Galil Z. Applications of efficient mergeable heaps for optimization problems on trees [J]. }$

$\texttt{\ \ \ \ Acta Informatica, 1980, 13: 53-58.}$

$\texttt{[2] Horn W A. Single-machine job sequencing with treelike precedence ordering and linear delay penalties [J].}$

$\texttt{\ \ \ \ SIAM Journal on Applied Mathematics, 1972, 23(2): 189-202.}$

---

