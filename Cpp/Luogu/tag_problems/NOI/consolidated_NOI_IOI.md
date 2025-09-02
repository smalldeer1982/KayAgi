---
title: "[IOI 2024] 消息篡改者"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11050
tag: ['2024', 'IOI', '交互题', 'Special Judge', '通信题']
---
# [IOI 2024] 消息篡改者
## 题目背景

不要 $\texttt{\#include "message.h"}$。

请使用 C++ 20 提交，并在文件头粘贴如下的内容：

```cpp
#include <vector>

std::vector<bool> send_packet(std::vector<bool>);
void send_message(std::vector<bool>, std::vector<bool>);
std::vector<bool> receive_message(std::vector<std::vector<bool>>);
```
## 题目描述

## 任务描述

Aisha 和 Basma 是两位互相通信的朋友。Aisha 有一条消息 $M$ 想要发给 Basma，该消息是由 $S$ 个比特（即若干 0 或 1）组成的序列。Aisha 通过发送**数据包**来跟 Basma 通信。一个数据包是由 $31$ 个比特组成的序列，对应的位置从 $0$ 到 $30$ 编号。Aisha 想向 Basma 发送消息 $M$ 时，会发送若干数据包。

然而第三个人 Cleopatra 在破坏 Aisha 和 Basma 之间的通信，能够**篡改**发送的数据包。在每个数据包中，Cleopatra 可以修改恰好 $15$ 个位置的比特。具体来说，给定长度为 $31$ 的数组 $C$，其中每个元素为 $0$ 或 $1$，含义如下：

* $C[i] = 1$ 表示位置为 $i$ 的比特可以被 Cleopatra 修改。我们称此类位置是被 Cleopatra **控制**的。
* $C[i] = 0$ 表示位置为 $i$ 的比特不能被 Cleopatra 修改。

数组 $C$ 恰好包含 $15$ 个 $1$ 和 $16$ 个 $0$。当发送消息 $M$ 时，Cleopatra 控制的位置集合对于所有数据包都是相同的。Aisha 清楚地知道哪 $15$ 个位置被 Cleopatra 控制。Basma 只知道有 $15$ 个位置被 Cleopatra 控制，但不知道是哪些位置。

令 $A$ 为 Aisha 决定要发送的数据包（称之为**原始数据包**）。令 $B$ 为 Basma 收到的数据包（称之为**篡改数据包**）。对每个在 $0 \leq i < 31$ 的 $i$ 都有：

* 如果 Cleopatra 不能控制位置为 $i$ 的比特（$C[i]=0$），那么 Basma 将能收到 Aisha 发送的第 $i$ 个比特（$B[i]=A[i]$），
* 否则，如果 Cleopatra 控制了位置为 $i$ 的比特（$C[i]=1$），那么 $B[i]$ 的值由 Cleopatra 决定。

每个数据包发送后，Aisha 会立刻知道被篡改后的数据包内容。

当 Aisha 发送完所有数据包后，Basma **按照发送顺序**接收到所有被篡改的数据包，她必须重建原始消息 $M$。

你的任务是制定并实现某种策略，使得 Aisha 给 Basma 发送消息 $M$ 时，Basma 能够从篡改数据包中恢复 $M$。具体来说，你要实现两个函数，第一个函数进行 Aisha 的动作：给定消息 $M$ 和数组 $C$，给 Basma 发送若干数据包来传输消息。第二个函数进行 Basma 的动作：给定若干篡改数据包，恢复原始消息 $M$。

## 实现细节

你要实现的第一个函数是：

```
void send_message(std::vector<bool> M, std::vector<bool> C)
```

* $M$：长度为 $S$ 的数组，描述 Aisha 想要发给 Basma 的消息。
* $C$：长度为 $31$ 的数组，标记 Cleopatra 控制的数据包中的位置。
* 每个测试用例中，该函数**最多**可被调用**2100次**。

该函数调用以下函数来发送数据包：

```
std::vector<bool> send_packet(std::vector<bool> A)
```

* $A$：原始数据包（长度为 $31$ 的数组），表示 Aisha 发送的比特。
* 此函数返回篡改数据包 $B$，表示 Basma 接收到的比特。
* 此函数在 `send_message` 的一次调用过程中最多被调用 $100$ 次。

你要实现的第二个函数是：

```
std::vector<bool> receive_message(std::vector<std::vector<bool>> R)
```

* $R$：描述若干篡改数据包的数组。这些数据包源自 Aisha 在一次 `send_message` 调用时发送的若干数据包，且按照 Aisha 的发送顺序排列。$R$ 的每个元素是长度为 $31$ 的数组，表示一个篡改数据包。
* 该函数应返回包含 $S$ 个比特的数组，且与原始消息 $M$ 相同。
* 每个测试用例中，该函数可能被调用**多次**。对于每次 `send_message` 的调用，对应地该函数要有**恰好一次**调用。函数 `receive_message` 的**调用顺序**不必与对应的 `send_message` 调用顺序一致。

注意在评测系统中，`send_message` 和 `receive_message` 两个函数是在**不同的程序**中来调用的。
## 提示

## 约束条件

* $1 \leq S \leq 1024$
* $C$ 恰好有 $31$ 个元素，且其中 $16$ 个为 $0$，$15$ 个为 $1$。

## 子任务与评分

如果在任意的测试用例中，函数 ``send_packet`` 的调用不符合上述规则，或者某个函数 `receive_message` 的调用的返回值不正确，你的解答在该测试用例上得 $0$ 分。

否则，令 $Q$ 为所有测试用例中，每次 `send_message` 调用时调用函数 `send_packet` 的次数的最大值。令 $X$ 等于：

- $1$，如果 $Q \leq 66$
- $0.95 ^ {Q - 66}$，如果 $66 < Q \leq 100$
- $0$，如果 $100 < Q$

那么，得分将由以下式子计算获得：

| 子任务 |     分数     | 额外的约束条件       |
| :----: | :----------: | -------------------- |
|   1    | $10 \cdot X$ | $S \leq 64$          |
|   2    | $90 \cdot X$ | 没有额外的约束条件。 |

注意在某些测试用例中，评测程序的行为是**自适应的**。这意味着 `send_packet` 的返回值可能取决于它的输入参数和以前调用该函数的返回值。

## 例子

考虑以下调用。

```
send_message([0, 1, 1, 0],
             [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
```

Aisha 试图发给 Basma 的消息是 $[0, 1, 1, 0]$。数据包的第 $0$ 至第 $15$ 个比特不能被 Cleopatra 修改，而第 $16$ 至第 $30$ 个比特可以被 Cleopatra 修改。

为便于解释这个例子，我们假设 Cleopatra 的行为是确定性的：她交替地用 $0$ 和 $1$ 填充所控制的比特，也就是她把她控制的第一个位置赋 $0$（例子中的第 $16$ 位），把她控制的第二个位置赋 $1$（第 $17$ 位），把她控制的第三个位置赋 $0$（第 $18$ 位），以此类推。

Aisha 可以做出的一种决定是在一个数据包中发送原始消息中的两个比特，例如她是这样做的：通过她控制的前 $8$ 个位置来发送第一个比特，通过她控制的接下来 $8$ 个位置来发送第二个比特。

于是 Aisha 发送以下数据包：

```
send_packet([0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
```

由于 Cleopatra 可以更改最后 $15$ 个比特，所以 Aisha 决定随意设置它们，因为它们可能会被覆盖。使用前面假定的 Cleopatra 的策略，该函数返回：

$[0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]$。

Aisha 决定在第二个数据包中发送 $M$ 的最后两个比特，与之前类似：

```
send_packet([1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
```

根据假定的 Cleopatra 的策略，该函数返回：

$[1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]$。

Aisha 还可以发送更多的数据包，但她没有这样做。

然后评测程序进行以下函数调用：

```
receive_message([[0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0],
                 [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]])
```

Basma 按照如下方式恢复消息 $M$。她从每个数据包中提取出第一个连续出现两次的比特，以及最后一个连续出现两次的比特。也就是说，她从第一个数据包提取出两个比特 $[0, 1]$ ，从第二个数据包中提取出两个比特 $[1, 0]$。把它们放在一起，她恢复了消息 $[0, 1, 1, 0]$，这是对 `receive_message` 调用的正确返回值。

可以证明，在假设的 Cleopatra 的策略下，对于长度为 $4$ 的消息，不管 $C$ 的值是多少，Basma 这样做能够正确恢复 $M$。然而，一般情况下这并不正确。

## 评测程序示例

评测程序示例不具备自适应性，Cleopatra 的行为是确定性的，她交替地用 $0$ 和 $1$ 来填充她控制的比特，就像她在例子中所做的那样。

输入格式：**输入第一行包含一个整数 $T$，指定测试用例的数量。**接下来有 $T$ 组测试用例，每组测试用例都按以下格式描述：

```
S
M[0]  M[1]  ...  M[S-1]
C[0]  C[1]  ...  C[30]
```

输出格式：评测程序示例按照输入的顺序，用以下格式输出 $T$ 组测试用例的结果：

```
K L
D[0]  D[1]  ...  D[L-1]
```

这里， $K$ 是 `send_packet` 的调用次数，$D$ 是 `receive_message` 返回的消息，$L$ 是它的长度。


---

---
title: "[IOI 2024] 树上代价"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11051
tag: ['2024', 'IOI', '交互题']
---
# [IOI 2024] 树上代价
## 题目背景

提交时请不要引用 `tree.h`。

请不要使用 C++14 (GCC 9) 提交。
## 题目描述

有一棵包括 $N$ 个**结点**的**树**，结点从 $0$ 到 $N-1$ 编号。结点 $0$ 是树的**根**。除根以外的每个结点都有唯一的**父结点**。对所有满足 $1 \leq i < N$ 的 $i$，结点 $i$ 的父结点为 $P[i]$，这里有 $P[i] < i$。我们约定 $P[0] = -1$。

对所有结点 $i$（$0 \leq i < N$），$i$ 的**子树**是如下结点组成的集合：
 * $i$，以及
 * 所有父结点为 $i$ 的结点，以及
 * 所有父结点的父结点为 $i$ 的结点，以及
 * 所有父结点的父结点的父结点为 $i$ 的结点，以及
 * 以此类推。

下图给出了一个包含 $N = 6$ 个结点的树的例子。每个箭头都从某个结点连向它的父结点（根结点除外，因为它没有父结点）。结点 $2$ 的子树包括结点 $2, 3, 4$ 和 $5$。结点 $0$ 的子树包括树中的全部 $6$ 个结点，而结点 $4$ 的子树仅包括结点 $4$ 自己。

![](https://cdn.luogu.com.cn/upload/image_hosting/vg5uaueo.png "150")

每个结点都被赋以非负整数的**权重**。我们将结点 $i$（$0 \leq i < N$）的权重记为 $W[i]$。

你的任务是写一个程序来回答 $Q$ 个询问，其中每个询问都用一对正整数 $(L, R)$ 来表示。对于询问的回答，应按照如下要求进行计算。

对树中的每个结点，都指派一个整数，称为**系数**。这样的指派结果被描述成一个序列 $C[0], \ldots, C[N-1]$，这里 $C[i]$（$0 \leq i < N$）是指派给结点 $i$ 的系数。我们称该序列为一个**系数序列**。注意，系数序列中的元素可以取负值、$0$ 或正值。

对某个询问 $(L, R)$，一个系数序列被称为是**有效的**，如果对于每个结点 $i$（$0 \leq i < N$）都有如下条件成立：结点 $i$ 的子树中的系数之和不小于 $L$ 且不大于 $R$。

对于一个给定的系数序列 $C[0], \ldots, C[N-1]$，结点 $i$ 的**代价**为 $|C[i]| \cdot W[i]$，这里 $|C[i]|$ 表示 $C[i]$ 的绝对值。最后，**总体代价**为所有结点的代价之和。你的任务是，对于每个询问，计算出可以由某个有效系数序列达到的**最小总体代价**。

可以证明，对于任意询问，都至少存在一个有效的系数序列。

### 实现细节

你需要实现如下两个函数：

```
void init(std::vector<int> P, std::vector<int> W)
```

* $P$，$W$：两个长度为 $N$ 的整数数组，记录了结点的父结点和权重。
* 对于每个测试样例，在评测程序与你的程序开始交互时，该函数将被恰好调用一次。

```
long long query(int L, int R)
```
* $L$，$R$：两个整数，描述一次询问。
* 对于每个测试样例，在 `init` 被调用后，该函数将被调用 $Q$ 次。
* 该函数应该返回对给定询问的答案。
## 输入格式

评测程序示例读取如下格式的输入：

```
N
P[1]  P[2] ...  P[N-1]
W[0]  W[1] ...  W[N-2] W[N-1]
Q
L[0]  R[0]
L[1]  R[1]
...
L[Q-1]  R[Q-1]
```

这里的 $L[j]$ 和 $R[j]$（$0 \leq j < Q$），是对 `query` 的第 $j$ 次调用的输入参数。注意，输入数据中的第二行中**仅包括 $N-1$ 个整数**，因为评测程序示例并不读取 $P[0]$ 的值。
## 输出格式

评测程序示例按照如下格式打印你的答案：

```
A[0]
A[1]
...
A[Q-1]
```

这里的 $A[j]$（$0 \leq j < Q$），是第 $j$ 次调用 `query` 时返回的值。
## 样例

### 样例输入 #1
```
3
0 0
1 1 1
2
1 1
1 2

```
### 样例输出 #1
```
3
2

```
## 提示

考虑如下调用：

```
init([-1, 0, 0], [1, 1, 1])
```
这棵树包含 $3$ 个结点：根结点以及它的 $2$ 个子结点。所有结点的权重均为 $1$。

```
query(1, 1)
```

本次询问有 $L = R = 1$，这意味着每个子树中的系数之和都必须等于 $1$。考虑系数序列 $[-1, 1, 1]$。这棵树以及相应的系数（在阴影矩形中）图示如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/fg1hjoze.png "150")

对每个结点 $i$（$0 \leq i < 3$），$i$ 的子树中全部结点的系数之和均为 $1$。因此，系数序列是有效的。总体代价的计算如下：


| 结点 | 权重 | 系数 |            代价            |
| :----: | :----: | :---------: | :------------------------: |
|   $0$    |   $1$    |     $-1$      | $\mid -1 \mid \cdot 1 = 1$ |
|   $1$    |   $1$    |      $1$      | $\mid 1 \mid \cdot 1 = 1$  |
|   $2$    |   $1$    |      $1$      | $\mid 1 \mid \cdot 1 = 1$  |

因此总体代价为 $3$。这是唯一的有效系数序列，因此调用应该返回 $3$。

```
query(1, 2)
```
对于该询问的最小总体代价为 $2$，可以在系数序列为 $[0, 1, 1]$ 时达到。

### 约束条件

* $1 \leq N \leq 200\,000$
* $1 \leq Q \leq 100\,000$
* $P[0] = -1$
* 对所有满足 $1 \leq i < N$ 的 $i$，都有 $0 \leq P[i] < i$
* 对所有满足 $0 \leq i < N$ 的 $i$，都有 $0 \leq W[i] \leq 1\,000\,000$
* 在每次询问中，都有 $1 \leq L \leq R \leq 1\,000\,000$

| 子任务 | 分数 | 额外的约束条件                                     |
| :-----: | :---: | ------------------------------------------------------------ |
|    1    | $10$  | $Q \leq 10$；对所有满足 $1 \leq i < N$ 的 $i$，都有 $W[P[i]] \leq W[i]$ |
|    2    | $13$  | $Q \leq 10$；$N \leq 2\,000$                                 |
|    3    | $18$  | $Q \leq 10$；$N \leq 60\,000$                                |
|    4    |  $7$  | 对所有满足 $0 \leq i < N$ 的 $i$，都有 $W[i] = 1$              |
|    5    | $11$  | 对所有满足 $0 \leq i < N$ 的 $i$，都有 $W[i] \leq 1$           |
|    6    | $22$  | $L = 1$                                                      |
|    7    | $19$  | 没有额外的约束条件。                                   |


---

---
title: "[IOI 2024] 象形文字序列"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11052
tag: ['2024', 'IOI', '交互题']
---
# [IOI 2024] 象形文字序列
## 题目背景

请在提交时不要引用 `hieroglyphs.h`。

请勿用 C++14 (GCC 9) 提交。
## 题目描述

一个研究团队正在研究象形文字序列之间的相似性。他们将每个象形文字表示成一个非负整数。为了开展研究，他们采用了关于序列的如下概念。

对于一个给定的序列 $A$，某个序列 $S$ 被称为是 $A$ 的**子序列**，当且仅当 $S$ 能够通过移除 $A$ 中的某些（也可能零个）元素而得到。

下表给出了序列 $A = [3, 2, 1, 2]$ 的子序列的一部分例子。

| 子序列  | 由 $A$ 得到子序列的方式                          |
| ------------ | -------------------------------------------------------- |
| [3, 2, 1, 2] | 不移除任何元素。                                 |
| [2, 1, 2]    | [~~3~~, 2, 1, 2]                                      |
| [3, 2, 2]    | [3, 2, ~~1~~, 2]                                      |
| [3, 2]       | [3, ~~2~~, ~~1~~, 2] 或者 [3, 2, ~~1~~, ~~2~~] |
| [3]          | [3, ~~2~~, ~~1~~, ~~2~~]                        |
| [ ]          | [~~3~~, ~~2~~, ~~1~~, ~~2~~]                 |

另一方面，$[3, 3]$ 或 $[1, 3]$ 不是 $A$ 的子序列。

考虑有两个象形文字序列 $A$ 和 $B$。某个序列 $S$ 被称为是 $A$ 和 $B$ 的**公共子序列**，当且仅当 $S$ 同时是 $A$ 和 $B$ 的子序列。此外，我们说某个序列 $U$ 是 $A$ 和 $B$ 的一个**最全公共子序列**，当且仅当如下两个条件成立：
* $U$ 是 $A$ 和 $B$ 的一个公共子序列。
* $A$ 和 $B$ 的任意公共子序列，都是 $U$ 的一个子序列。

可以证明，任意两个序列 $A$ 和 $B$ 都至多有一个最全公共子序列。

研究人员发现了两个象形文字序列 $A$ 和  $B$。序列 $A$ 包含 $N$ 个象形文字，而序列 $B$ 包含 $M$ 个象形文字。请帮助研究人员为序列 $A$ 和 $B$ 找到一个最全公共子序列，或者判定这样的序列并不存在。
## 输入格式

```
N  M
A[0]  A[1]  ...  A[N-1]
B[0]  B[1]  ...  B[M-1]
```
## 输出格式

```
T
R[0]  R[1]  ...  R[T-1]
```

这里 $R$ 是 `ucs` 所返回的数组，而 $T$ 为其长度。
## 样例

### 样例输入 #1
```
6 5
0 0 1 0 1 2
2 0 1 0 2

```
### 样例输出 #1
```
4
0 1 0 2

```
### 样例输入 #2
```
3 2
0 0 2
1 1

```
### 样例输出 #2
```
0


```
### 样例输入 #3
```
3 3
0 1 0
1 0 1

```
### 样例输出 #3
```
1
-1

```
## 提示

## 实现细节

你要实现以下函数。

```
std::vector<int> ucs(std::vector<int> A, std::vector<int> B)
```

* $A$：长度为 $N$ 的数组，给出第一个序列。
* $B$：长度为 $M$ 的数组，给出第二个序列。
* 如果 $A$ 和 $B$ 有一个最全公共子序列，该函数应当返回一个包含该序列的数组。否则，该函数应当返回 $[-1]$（一个长度为 $1$ 的数组，其唯一元素为 $-1$）。
* 对每个测试用例，该函数恰好被调用一次。

## 约束条件

* $1 \leq N \leq 100\,000$
* $1 \leq M \leq 100\,000$
* 对所有满足 $0 \leq i < N$ 的 $i$，都有 $0 \leq A[i] \leq 200\,000$
* 对所有满足 $0 \leq j < M$ 的 $j$，都有 $0 \leq B[j] \leq 200\,000$

## 子任务

| 子任务 | 分数 | 额外的约束条件                                       |
| :-----: | :---: | ------------------------------------------------------------ |
|    1    |  $3$  | $N = M$；$A$ 和 $B$ 均由 $N$ 个**不同的**整数构成，取自 $0$ 到 $N-1$（包括这两个值） |
|    2    | $15$  | 对任意整数 $k$，$k$ 在 $A$ 和 $B$ 中的出现次数，加起来至多等于 $3$。 |
|    3    | $10$  | 对所有满足 $0 \leq i < N$ 的 $i$，都有 $A[i] \leq 1$；对所有满足 $0 \leq j < M$ 的 $j$，都有 $B[j] \leq 1$ |
|    4    | $16$  | $A$ 和 $B$ 存在最全公共子序列。  |
|    5    | $14$  | $N \leq 3000$；$M \leq 3000$                                 |
|    6    | $42$  | 没有额外的约束条件。                                   |

## 例子

### 例 1

考虑以下函数调用。

```
ucs([0, 0, 1, 0, 1, 2], [2, 0, 1, 0, 2])
```

此时，$A$ 和 $B$ 的公共子序列为：$[\ ]$，$[0]$，$[1]$，$[2]$，$[0, 0]$，$[0, 1]$，$[0, 2]$，$[1, 0]$，$[1, 2]$，$[0, 0, 2]$，$[0, 1, 0]$，$[0, 1, 2]$，$[1, 0, 2]$ 和 $[0, 1, 0, 2]$。

由于 $[0, 1, 0, 2]$ 是 $A$ 和 $B$ 的一个公共子序列，而 $A$ 和 $B$ 的所有公共子序列又都是 $[0, 1, 0, 2]$ 的子序列，因此函数应该返回 $[0, 1, 0, 2]$。

### 例 2

考虑以下函数调用。

```
ucs([0, 0, 2], [1, 1])
```

此时，$A$ 和 $B$ 唯一的公共子序列为空序列 $[\ ]$。因此函数应该返回一个空数组 $[\ ]$。

### 例 3

考虑以下函数调用。

```
ucs([0, 1, 0], [1, 0, 1])
```

此时，$A$ 和 $B$ 的公共子序列为 $[\ ]$，$[0]$，$[1]$，$[0, 1]$ 和 $[1, 0]$，可以看出两者并不存在最全公共子序列。因此，函数应该返回 $[-1]$。


---

---
title: "[IOI 2024] 斯芬克斯的谜题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11054
tag: ['2024', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2024] 斯芬克斯的谜题
## 题目背景

请在提交时不要引用 `sphinx.h`，并在代码开头加入如下内容：

```cpp
#include <vector>
int perform_experiment(std::vector<int> E);
```

请勿用 C++14 (GCC 9) 提交。
## 题目描述

斯芬克斯为你准备了一个谜题。给定 $N$ 个顶点的图，顶点从 $0$ 到 $N-1$ 编号。图中有 $M$ 条边，从 $0$ 到 $M-1$ 编号。每条边连接两个不同的顶点，且边是双向的。具体来说，对从 $0$ 到 $M-1$ 的每个 $j$，边 $j$ 连接顶点 $X[j]$ 和 $Y[j]$。任意两个顶点之间最多有一条边。若两个顶点被一条边连接，则它们是**相邻的**。

对顶点序列 $v_0, v_1, \ldots, v_k$（对 $k \ge 0$），若每两个连续顶点 $v_l$ 和 $v_{l+1}$（对所有满足 $0 \le l \lt k$ 的 $l$）是相邻的，则称其为一条**路径**。路径 $v_0, v_1, \ldots, v_k$ **连接**顶点 $v_0$ 和 $v_k$。在给定的图中，每对顶点被某条路径连接。

现在有 $N + 1$ 种颜色，从 $0$ 到 $N$ 编号。其中，颜色 $N$ 是特殊的，称为**斯芬克斯之色**。一开始每个顶点都有一种颜色，顶点 $i$（$0 \le i \lt N$）的颜色是 $C[i]$。多个顶点可以是同一种颜色的，有的颜色可能没有对应的顶点，且不会有顶点的颜色是斯芬克斯之色。也就是说，$0 \le C[i] \lt N$（$0 \le i \lt N$）。

若一条路径 $v_0, v_1, \ldots, v_k$（对 $k \ge 0$）上的所有顶点都是相同颜色的，则称其是**单色**的。也就是说，满足 $C[v_l] = C[v_{l+1}]$（对所有满足 $0 \le l \lt k$ 的 $l$）。此外，两个顶点 $p$ 和 $q$（$0 \le p \lt N$，$0 \le q \lt N$）在同一个**单色分支**中，当且仅当它们被某条单色路径连接。

你知道图中顶点和边的关系，但是你不知道每个顶点的颜色。你希望通过**重新着色实验**来弄清楚顶点的颜色。

在一次重新着色实验中，你可以对任意多的顶点进行重新着色。具体来说，在一次重新着色实验中，你先给出一个长度为 $N$ 的数组 $E$，对每个 $i$（$0 \le i \lt N$），$E[i]$ 的值在 $-1$ 和 $N$ 之间（**包括** $-1$ 和 $N$）。重新着色后，每个顶点 $i$ 的颜色变成了 $S[i]$，其中 $S[i]$ 的值：
* 若 $E[i] = -1$，则是 $C[i]$，也就是重新着色前顶点 $i$ 的颜色；
* 否则，是 $E[i]$。

注意：你可以在重新着色的过程中使用斯芬克斯之色。

在将每个顶点 $i$ 的颜色设为 $S[i]$（$0 \le i \lt N$）之后，斯芬克斯会宣布图中单色分支的数量。新的着色情况仅在本次重新着色实验中有效，因此**当本次实验结束后，所有顶点的颜色会恢复成最初的情况**。

你的任务是至多通过 $2\,750$ 次重新着色实验来确定图中顶点的颜色。如果正确给出了每对相邻顶点是否具有相同颜色，那么也会获得部分分数。

### 实现细节

你要实现以下函数。

```
std::vector<int> find_colours(int N,
    std::vector<int> X, std::vector<int> Y)
```

* $N$：图中顶点的数量。
* $X$，$Y$：两个长度为 $M$ 的数组，描述图中的边。
* 该函数应该返回一个长度为 $N$ 的数组 $G$，表示图中顶点的颜色。
* 对每个测试用例，该函数恰好被调用一次。

以上函数可以通过调用下面的函数来进行重新着色实验：

```
int perform_experiment(std::vector<int> E)
```

* $E$：长度为 $N$ 的数组，指定顶点重新着色的方式。
* 该函数返回根据 $E$ 所给出的方式进行重新着色后单色分支的数量。
* 该函数至多只能调用 $2\,750$ 次。

评测程序**不是自适应的**。也就是说，顶点的颜色在调用 `find_colours` 之前就已经固定下来了。
## 输入格式

评测程序示例读取如下格式的输入：

```
N  M
C[0]  C[1] ... C[N-1]
X[0]  Y[0]
X[1]  Y[1]
...
X[M-1]  Y[M-1]
```
## 输出格式

评测程序示例按照如下格式打印你的答案：

```
L  Q
G[0]  G[1] ... G[L-1]
```

这里，$L$ 是 `find_colours` 返回的数组 $G$ 的长度，$Q$ 是调用 `perform_experiment` 的次数。
## 样例

### 样例输入 #1
```
4 4
2 0 0 0
0 1
1 2
0 2
0 3
```
### 样例输出 #1
```
4 3
2 0 0 0

```
## 提示

考虑以下函数调用。

```
find_colours(4, [0, 1, 0, 0], [1, 2, 2, 3])
```

在这个例子中，假设顶点的（隐藏的）颜色是 $C = [2, 0, 0, 0]$，如下图所示。顶点的颜色同时也用数字标注在顶点右上角的标签里。

![](https://cdn.luogu.com.cn/upload/image_hosting/ih99ftw2.png "230")

假设该函数以下列方式调用 `perform_experiment`。

```
perform_experiment([-1, -1, -1, -1])
```

这次调用没有重新着色任何顶点，因此所有顶点都保持它们原来的颜色。

顶点 $1$ 和顶点 $2$ 都是颜色 $0$ 的。因此路径 $1, 2$ 是单色路径，从而顶点 $1$ 和顶点 $2$ 在同一个单色分支中。

顶点 $1$ 和顶点 $3$ 都是颜色 $0$ 的。但是由于不存在连接它们的单色路径，因此它们在不同的单色分支中。

总共有 $3$ 个单色分支，分别是顶点集合 $\{0\}$、$\{1, 2\}$ 和 $\{3\}$。因此，本次函数调用返回 $3$。

再假设该函数以下列方式调用 `perform_experiment`。

```
perform_experiment([0, -1, -1, -1])
```

这次调用只把顶点 $0$ 重新着色成颜色 $0$，结果如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/n0qub0o1.png "230")

此时所有顶点都属于同一个单色分支，因此本次函数调用返回 $1$。由此可以推断顶点 $1$、$2$ 和 $3$ 都是颜色 $0$ 的。

假设该函数还以下列方式调用 `perform_experiment`。

```
perform_experiment([-1, -1, -1, 2])
```

这次调用把顶点 $3$ 重新着色成颜色 $2$，结果如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ds6xl13a.png "230")

这时有 $2$ 个单色分支，分别是顶点集合 $\{0, 3\}$ 和 $\{1, 2\}$，因此本次函数调用返回 $2$。由此可以推断顶点 $0$ 是颜色 $2$ 的。

然后函数 `find_colours` 返回数组 $[2, 0, 0, 0]$。由于 $C = [2, 0, 0, 0]$，因此可以获得满分。

此外，也还有多种返回值，例如 $[1, 2, 2, 2]$ 或 $[1, 2, 2, 3]$，可以获得 $50\%$ 的分数。

### 约束条件

* $2 \le N \le 250$
* $N - 1 \le M \le \frac{N \cdot (N - 1)}{2}$
* 对所有满足 $0 \le j \lt M$ 的 $j$，都有 $0 \le X[j] \lt Y[j] \lt N$。
* 对所有满足 $0 \le j \lt k \lt M$ 的 $j$ 和 $k$，都有 $X[j] \neq X[k]$ 或 $Y[j] \neq Y[k]$。
* 每对顶点被某条路径连接。
* 对所有满足 $0 \le i \lt N$ 的 $i$，都有 $0 \le C[i] \lt N$。

| 子任务 | 分数  | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1       | $3$    | $N = 2$|
| 2       | $7$    | $N \le 50$|
| 3       | $33$   | 给定的图是一条路径：$M = N - 1$，且顶点 $j$ 和 $j+1$ 是相邻的（$0 \leq j < M$）。 |
| 4       | $21$   | 给定的图是完全图：$M = \frac{N \cdot (N - 1)}{2}$，且任意两个顶点是相邻的。 |
| 5       | $36$   | 没有额外的约束条件。 |

在每个子任务中，如果你的程序正确给出了每对相邻顶点是否具有相同颜色，那么也会获得部分分数。

更准确地说，如果在所有测试用例中 `find_colours` 返回的数组 $G$ 与数组 $C$ 完全一样（也就是对所有满足 $0 \le i \lt N$ 的 $i$，都有 $G[i] = C[i]$），你会获得该子任务的全部分数。否则，如果在某个子任务的所有测试样例中满足下列条件，你会获得该子任务 $50\%$ 的分数：

* 对所有满足 $0 \le i \lt N$ 的 $i$，都有 $0 \le G[i] \lt N$；
* 对所有满足 $0 \le j \lt M$ 的 $j$，都有：
  * $G[X[j]] = G[Y[j]]$ 当且仅当 $C[X[j]] = C[Y[j]]$。


---

---
title: "[IOI 2025] World Map"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13537
tag: ['2025', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2025] World Map
## 题目描述

Mr. Pacha, a Bolivian archeologist, discovered an ancient document near Tiwanaku that describes the world during the Tiwanaku Period (300-1000 CE). At that time, there were $N$ countries, numbered from 1 to $N$.

In the document, there is a list of $M$ different pairs of adjacent countries:

$$\begin{aligned}(A[0], B[0]), (A[1], B[1]), \ldots, (A[M - 1], B[M - 1]).\end{aligned}$$

For each $i$ ($0 \leq i < M$), the document states that country $A[i]$ was adjacent to country $B[i]$ and vice versa. Pairs of countries not listed were not adjacent.

Mr. Pacha wants to create a map of the world such that all adjacencies between countries are exactly as they were during the Tiwanaku Period. For this purpose, he first chooses a positive integer $K$. Then, he draws the map as a grid of $K \times K$ square cells, with rows numbered from 0 to $K - 1$ (top to bottom) and columns numbered from 0 to $K - 1$ (left to right).

He wants to color each cell of the map using one of $N$ colors. The colors are numbered from 1 to $N$, and country $j$ ($1 \leq j \leq N$) is represented by color $j$. The coloring must satisfy all of the following **conditions**:

- For each $j$ ($1 \leq j \leq N$), there is at least one cell with color $j$.
- For each pair of adjacent countries $(A[i], B[i])$, there is at least one pair of adjacent cells such that one of them is colored $A[i]$ and the other is colored $B[i]$. Two cells are adjacent if they share a side.
- For each pair of adjacent cells with different colors, the countries represented by these two colors were adjacent during the Tiwanaku Period.

For example, if $N = 3$, $M = 2$ and the pairs of adjacent countries are $(1, 2)$ and $(2, 3)$, then the pair $(1, 3)$ was not adjacent, and the following map of dimension $K = 3$ satisfies all the conditions.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6zn2x2ar.png)
:::

In particular, a country does **not** need to form a connected region on the map. In the map above, country 3 forms a connected region, while countries 1 and 2 form disconnected regions.

Your task is to help Mr. Pacha choose a value of $K$ and create a map. The document guarantees that such a map exists. Since Mr. Pacha prefers smaller maps, in the last subtask your score depends on the value of $K$, and lower values of $K$ may result in a better score. However, finding the minimum possible value of $K$ is not required.

### Implementation Details

You should implement the following procedure:

```cpp
std::vector<std::vector<int>> create_map(int N, int M, std::vector<int> A, std::vector<i
```

* $N$: the number of countries.
* $M$: the number of pairs of adjacent countries.
* $A$ and $B$: arrays of length $M$ describing adjacent countries.
* This procedure is called **up to $50$ times** for each test case.

The procedure should return an array $C$ that represents the map. Let $K$ be the length of $C$.
* Each element of $C$ must be an array of length $K$, containing integers between $1$ and $N$ inclusive.
* $C[i][j]$ is the color of the cell at row $i$ and column $j$ (for each $i$ and $j$ such that $0 \leq i, j < K$).
* $K$ must be less than or equal to $240$.
## 输入格式

The first line of the input should contain a single integer $T$, the number of scenarios. A description of $T$ scenarios should follow, each in the format specified below.

```
N M
A[0] B[0]
:
A[M-1] B[M-1]
```
## 输出格式

```
P
Q[0] Q[1] ... Q[P-1]

C[0][0] ... C[0][Q[0]-1]
:
C[P-1][0] ... C[P-1][Q[P-1]-1]
```

Here, $P$ is the length of the array $C$ returned by create_map, and $Q[i]$ ($0 \leq i < P$) is the length of $C[i]$. Note that line 3 in the output format is intentionally left blank.
## 样例

### 样例输入 #1
```
2
3 2
1 2
2 3
4 4
1 2
1 3
2 4
3 4
```
### 样例输出 #1
```
3
3 3 3
2 3 3
2 3 2
1 2 1
7
7 7 7 7 7 7 7
2 1 3 3 4 3 4
2 1 3 3 3 3 3
2 1 1 1 3 4 4
2 2 2 1 3 4 3
1 1 1 2 4 4 4
2 2 1 2 2 4 3
2 2 1 2 2 4 4

```
## 提示

### Example 1

Consider the following call:

```
create_map(3, 2, [1, 2], [2, 3])
```

This is the example from the task description, so the procedure can return the following map.

```
[
[2, 3, 3],
[2, 3, 2],
[1, 2, 1]
]
```

### Example 2

Consider the following call:

```
create_map(4, 4, [1, 1, 2, 3], [2, 3, 4, 4])
```

In this example, $N = 4$, $M = 4$ and the country pairs $(1, 2)$, $(1, 3)$, $(2, 4)$, and $(3, 4)$ are adjacent. Consequently, the pairs $(1, 4)$ and $(2, 3)$ are not adjacent.

The procedure can return the following map of dimension $K = 7$, which satisfies all the conditions.

```
[
[2, 1, 3, 3, 4, 3, 4],
[2, 1, 3, 3, 3, 3, 3],
[2, 1, 1, 1, 3, 4, 4],
[2, 2, 2, 1, 3, 4, 3],
[1, 1, 1, 2, 4, 4, 4],
[2, 2, 1, 2, 2, 4, 3],
[2, 2, 1, 2, 2, 4, 4]
]
```

The map could be smaller; for example, the procedure can return the following map of dimension $K = 2$.

```
[
[3, 1],
[4, 2]
]
```

Note that both maps satisfy $K / N \leq 2$.

### Constraints

* $1 \leq N \leq 40$
* $0 \leq M \leq \frac{N \cdot (N-1)}{2}$
* $1 \leq A[i] < B[i] \leq N$ for each $i$ such that $0 \leq i < M$.
* The pairs $(A[0], B[0]), \ldots, (A[M-1], B[M-1])$ are distinct.
* There exists at least one map which satisfies all the conditions.

### Subtasks and Scoring

| Subtask | Score | Additional Constraints |
| :-: | :-: | :-: |
| 1 | 5 | $M = N - 1$, $A[i] = i + 1$, $B[i] = i + 2$ for each $0 \leq i < M$. |
| 2 | 10 | $M = N - 1$ |
| 3 | 7 | $M = \frac{N \cdot (N - 1)}{2}$ |
| 4 | 8 | Country 1 is adjacent to all other countries. Some other pairs of countries may also be adjacent. |
| 5 | 14 | $N \leq 15$ |
| 6 | 56 | No additional constraints. |

In subtask 6, your score depends on the value of $K$.

- If any map returned by create_map does not satisfy all the conditions, your score for the subtask will be $0$.
- Otherwise, let $R$ be the **maximum** value of $K/N$ over all calls to `create_map`. Then, you receive a **partial score** according to the following table:

| Limits | Score |
| :-: | :-: |
| $6 < R$ | $0$ |
| $4 < R \leq 6$ | $14$ |
| $3 < R \leq 4$ | $28$ |
| $2.5 < R \leq 3$ | $42$ |
| $2 < R \leq 2.5$ | $49$ |
| $R \leq 2$ | $56$ |


---

---
title: "[IOI 2025] Festival"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13538
tag: ['动态规划 DP', '二分', '2025', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2025] Festival
## 题目描述

Nayra is at a festival playing a game where the grand prize is a trip to Laguna Colorado. The game consists of using tokens to buy coupons. Buying a coupon may result in additional tokens. The goal is to get as many coupons as possible.

She starts the game with $A$ tokens. There are $N$ coupons, numbered from $0$ to $N - 1$. Nayra has to pay $P[i]$ tokens ($0 \leq i < N$) to buy coupon $i$ (and she must have at least $P[i]$ tokens before the purchase). She can buy each coupon at most once.

Moreover, each coupon $i$ ($0 \leq i < N$) is assigned a **type**, denoted by $T[i]$, which is an integer **between $1$ and $4$**, inclusive. After Nayra buys coupon $i$, the remaining number of tokens she has gets multiplied by $T[i]$. Formally, if she has $X$ tokens at some point of the game, and buys coupon $i$ (which requires $X \geq P[i]$), then she will have $(X - P[i]) \cdot T[i]$ tokens after the purchase.

Your task is to determine which coupons Nayra should buy and in what order, to maximize the total number of **coupons** she has at the end. If there is more than one sequence of purchases that achieves this, you may report any one of them.

### Implementation Details

You should implement the following procedure:

```cpp
std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T)
```

- $A$: the initial number of tokens Nayra has.
- $P$: an array of length $N$ specifying the prices of the coupons.
- $T$: an array of length $N$ specifying the types of the coupons.
- This procedure is called exactly once for each test case.

The procedure should return an array $R$, which specifies Nayra's purchases as follows:

- The length of $R$ should be the maximum number of coupons she can buy.
- The elements of the array are the indices of the coupons she should buy, in chronological order. That is, she buys coupon $R[0]$ first, coupon $R[1]$ second, and so on.
- All elements of $R$ must be unique.

If no coupons can be bought, $R$ should be an empty array.
## 输入格式

Input format:

```
N A
P[0] T[0]
P[1] T[1]
...
P[N-1] T[N-1]
```
## 输出格式

Output format:

```
S
R[0] R[1] ... R[S-1]
```

Here, $S$ is the length of the array $R$ returned by `max_coupons`.
## 样例

### 样例输入 #1
```
4 13
4 1
500 3
8 3
14 4
```
### 样例输出 #1
```
3
2 3 0
```
### 样例输入 #2
```
2 9
6 2
5 3
```
### 样例输出 #2
```
2
0 1
```
### 样例输入 #3
```
3 1
2 4
5 3
7 1
```
### 样例输出 #3
```
0


```
## 提示

### Example 1

Consider the following call.

```cpp
max_coupons(13, [4, 500, 8, 14], [1, 3, 3, 4])
```

Nayra initially has $A = 13$ tokens. She can buy 3 coupons in the order shown below:

| Coupon bought | Coupon price | Coupon type | Number of tokens after the purchase |
| :-: | :-: | :-: | :-: |
| 2 | 8 | 3 | $(13 - 8) \cdot 3 = 15$ |
| 3 | 14 | 4 | $(15 - 14) \cdot 4 = 4$ |
| 0 | 4 | 1 | $(4 - 4) \cdot 1 = 0$ |

In this example, it is not possible for Nayra to buy more than 3 coupons, and the sequence of purchases described above is the only way in which she can buy 3 of them. Hence, the procedure should return $[2, 3, 0]$.

### Example 2

Consider the following call.

```cpp
max_coupons(9, [6, 5], [2, 3])
```

In this example, Nayra can buy both coupons in any order. Hence, the procedure should return either $[0, 1]$ or $[1, 0]$.

### Example 3

Consider the following call.

```cpp
max_coupons(1, [2, 5, 7], [4, 3, 1])
```

In this example, Nayra has one token, which is not enough to buy any coupons. Hence, the
procedure should return $[]$  (an empty array).

### Constraints

- $1 \leq N \leq 200000$
- $1 \leq A \leq 10^9$
- $1 \leq P[i] \leq 10^9$ for each $i$ such that $0 \leq i < N$.
- $1 \leq T[i] \leq 4$ for each $i$ such that $0 \leq i < N$.

### Subtasks

| Subtask | Score | Additional Constraints |
| :-: | :-: | :-: |
| 1 | 5 | $T[i] = 1$ for each $i$ such that $0 \leq i < N$. |
| 2 | 7 | $N \leq 3000; T[i] \leq 2$ for each $i$ such that $0 \leq i < N$. |
| 3 | 12 | $T[i] \leq 2$ for each $i$ such that $0 \leq i < N$. |
| 4 | 15 | $N \leq 70$ |
| 5 | 27 | Nayra can buy all $N$ coupons (in some order). |
| 6 | 16 | $(A - P[i]) \cdot T[i] < A$ for each $i$ such that $0 \leq i < N$. |
| 7 | 18 | No additional constraints. |


---

---
title: "[IOI 2025] Migrations"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13539
tag: ['2025', 'IOI', '交互题', 'Special Judge', '通信题']
---
# [IOI 2025] Migrations
## 题目描述

The Natural History Museum is investigating the migration patterns of dinosaurs in Bolivia. Paleontologists have discovered dinosaur footprints at $N$ different sites, numbered from $0$ to $N - 1$ in order of decreasing age: site $0$ contains the oldest footprints, while site $N - 1$ holds the youngest.

The dinosaurs migrated to each site (except site $0$) from a specific, older site. For every site $i$ such that $1 \leq i \leq N - 1$, there exists exactly one older site $P[i]$ (with $P[i] < i$) such that some dinosaurs migrated directly from site $P[i]$ to site $i$. A single older site may have been the source of migrations to multiple younger sites.

The paleontologists model each migration as an **undirected connection** between sites $i$ and $P[i]$. Note that for any two distinct sites $x$ and $y$, it is possible to travel from $x$ to $y$ by traversing a sequence of connections. The **distance** between sites $x$ and $y$ is defined as the minimum number of connections required to travel from $x$ to $y$.

For example, the following image displays a case with $N = 5$ sites, where $P[1] = 0$, $P[2] = 1$, $P[3] = 2$, and $P[4] = 2$. One can travel from site $3$ to site $4$ through $2$ connections, so the distance between them is $2$.

![](https://cdn.luogu.com.cn/upload/image_hosting/g4mdke4x.png)

The Museum aims to identify a pair of sites with the maximum possible distance.

Note that the pair is not necessarily unique: for instance, in the example above, both pairs $(0, 3)$ and $(0, 4)$ have a distance of $3$, which is the maximum. In such cases, any of the pairs attaining the maximum distance is considered valid.

Initially, the values of $P[i]$ are not known. The Museum sends a research team to visit the sites $1, 2, \ldots, N - 1$, in order. Upon reaching each site $i$ ($1 \leq i \leq N - 1$), the team performs both of the following actions:

- Determines the value of $P[i]$, that is, the source of migration to site $i$.
- Decides whether to send **one** message to the Museum or not to send any message from this site, based on the previously gathered information.

Messages are transmitted via an expensive satellite communication system, so each message must be an integer between $1$ and $20000$, inclusive. Additionally, the team is allowed to send **at most $50$ messages** in total.

Your task is to implement a strategy, through which:

- The research team selects the sites from which messages are sent, along with the value of each message.
- The Museum can determine a pair of sites with the maximum distance, based solely on the messages received from each site, knowing from which sites these messages were sent.

Sending large numbers through the satellite is costly. Your score will depend on both the highest integer sent and the total number of messages transmitted.

### Implementation Details

You need to implement two procedures; one for the research team, and another one for the
Museum.

The procedure you should implement for the **research team** is:

```cpp
int send_message(int N, int i, int Pi)
```

- $N$: the number of sites with footprints.
- $i$: the index of the site the team is currently visiting.
- $P[i]$: the value of $P[i]$.
- This procedure is called $N - 1$ times for each test case, in the order of $i = 1, 2, ..., N - 1$.

This procedure should return $S[i]$ specifying the action taken by the research team at site $i$:

- $S[i] = 0$: the research team decides not to send a message from site $i$.
- $1 \leq S[i] \leq 20000$: the research team sends the integer $S[i]$ as the message from site $i$.

The procedure you should implement for the **Museum** is:

```cpp
std::pair<int,int> longest_path(std::vector<int> S)
```

- $S$: an array of length $N$ such that:
    - $S[0] = 0$.
    - For each $1 \leq i \leq N - 1$, $S[i]$ is the integer returned by `send_message(N, i, Pi)`.
- This procedure is called exactly once for each test case.

This procedure should return a pair of sites $(U, V)$ with the maximum distance.

In the actual grading, a program that calls the above procedures is run **exactly two times**.

- During the first run of the program:
    - send_message is called exactly $N - 1$ times.
    - **Your program can store and retain information across successive calls.**
    - The returned values (array $S$) are stored by the grading system.
    - In some cases the behavior of the grader is **adaptive**. This means that the value of $P[i]$ in a call to `send_message` may depend on the actions taken by the research team during the previous calls.
- During the second run of the program:
    - `longest_path` is called exactly once. The only information available to `longest_path` from the first run is the array $S$.
## 输入格式

The sample grader calls both `send_message` and `longest_path` in the same run, which is
different from the actual grader.

Input format:

```
N
P[1] P[2] ... P[N-1]
```
## 输出格式

Output format:

```
S[1] S[2] ... S[N-1]
U V
```

Note that you can use the sample grader with any value of $N$.
## 提示

### Example

Let $N = 10000$. Consider the situation in which $P[1] = 0$, $P[2] = 1$, $P[3] = 2$, $P[4] = 2$, and $P[i] = 1$ for $i > 4$.

![](https://cdn.luogu.com.cn/upload/image_hosting/0636ikup.png)

Assume that the research team's strategy is to send the message $10 \cdot V + U$ whenever the pair of sites $(U, V)$ with the maximum distance changes as a result of a send_message call.

Initially, the pair with the maximum distance is $(U, V) = (0, 0)$. Consider the following sequence of calls during the first run of the program:

| Procedure call | $(U, V)$ | Return value $(S[i])$ |
| :-: | :-: | :-: |
| `send_message(10000, 1, 0)` | $(0,1)$ | $10$ |
| `send_message(10000, 2, 1)` | $(0,2)$ | $20$ |
| `send_message(10000, 3, 2)` | $(0,3)$ | $30$ |
| `send_message(10000, 4, 2)` | $(0,3)$ | $0$ |

Note that in all the remaining calls the value of $P[i]$ is $1$. This means that the pair with the maximum distance does not change, and the team does not send any more messages.

Then, in the second run of the program, the following call is made:

```
longest_path([0, 10, 20, 30, 0, ...])
```

The Museum reads the last message sent by the research team, which is $S[3] = 30$, and deduces that $(0, 3)$ is the pair of sites with the maximum distance. Therefore, the call returns $(0, 3)$.

Note that this approach does not always make it possible for the Museum to determine the pair with the maximum distance correctly.

### Subtasks and Scoring

| Subtask | Score | Additional Constraints |
| :-: | :-: | :-: |
| 1 | 30 | Site 0 and some other site have a maximum distance among all pairs of sites. |
| 2 | 70 | No additional constraints. |

Let $Z$ be the maximum integer appearing in the array $S$, and let $M$ be the number of messages sent by the research team.

In any of the test cases, if at least one of the following conditions hold, then the score of your solution for that test case will be 0 (reported as Output isn't correct in CMS):

- At least one element in $S$ is invalid.
- $Z > 20\,000$ or $M > 50$.
- The return value of the call to procedure longest_path is incorrect.

Otherwise, your score for subtask 1 is calculated as follows:

| Condition | Score |
| :-: | :-: |
| $9998 \leq Z \leq 20000$ | 10 |
| $102 \leq Z \leq 9997$ | 16 |
| $5 \leq Z \leq 101$ | 23 |
| $Z \leq 4$ | 30 |

Your score for subtask 2 is calculated as follows:

| Condition | Score |
| :-: | :-: |
| $5 \leq Z \leq 20000$ and $M \leq 50$ | $35 - 25 \log_{4000} \left(\frac{Z}{5}\right)$ |
| $Z \leq 4$ and $32 \leq M \leq 50$ | 40 |
| $Z \leq 4$ and $9 \leq M \leq 31$ | $70 - 30 \log_{4} \left(\frac{M}{8}\right)$ |
| $Z \leq 4$ and $M \leq 8$ | 70 |


---

---
title: "[IOI 2025] Obstacles for a Llama"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13540
tag: ['2025', 'IOI', '交互题']
---
# [IOI 2025] Obstacles for a Llama
## 题目描述

A llama wants to travel through the Andean Plateau. It has a map of the plateau in the form of a grid of $N \times M$ square cells. The rows of the map are numbered from $0$ to $N-1$ from top to bottom, and the columns are numbered from $0$ to $M-1$ from left to right. The cell of the map in row $i$ and column $j$ ($0 \leq i < N$, $0 \leq j < M$) is denoted by $(i, j)$.

The llama has studied the climate of the plateau and discovered that all cells in each row of the map have the same **temperature** and all cells in each column of the map have the same **humidity**. The llama has given you two integer arrays $T$ and $H$ of length $N$ and $M$ respectively. Here $T[i]$ ($0 \leq i < N$) indicates the temperature of the cells in row $i$, and $H[j]$ ($0 \leq j < M$) indicates the humidity of the cells in column $j$.

The llama has also studied the flora of the plateau and noticed that a cell $(i, j)$ is **free of vegetation** if and only if its temperature is greater than its humidity, formally $T[i] > H[j]$.

The llama can travel across the plateau only by following **valid paths**. A valid path is a sequence of distinct cells that satisfy the following conditions:

- Each pair of consecutive cells in the path shares a common side.
- All cells in the path are free of vegetation.

Your task is to answer $Q$ questions. For each question, you are given four integers: $L$, $R$, $S$, and $D$. You must determine whether there exists a valid path such that:
- The path starts at cell $(0, S)$ and ends at cell $(0, D)$.
- All cells in the path lie within columns $L$ to $R$, inclusive.

It is guaranteed that both $(0, S)$ and $(0, D)$ are free of vegetation.

### Implementation Details

The first procedure you should implement is:

```cpp
void initialize(std::vector<int> T, std::vector<int> H)
```

- $T$: an array of length $N$ specifying the temperature in each row.
- $H$: an array of length $M$ specifying the humidity in each column.
- This procedure is called exactly once for each test case, before any calls to `can_reach`.

The second procedure you should implement is:

```cpp
bool can_reach(int L, int R, int S, int D)
```

- $L, R, S, D$: integers describing a question.
- This procedure is called $Q$ times for each test case.

This procedure should return `true` if and only if there exists a valid path from cell $(0, S)$ to cell $(0, D)$, such that all cells in the path lie within columns $L$ to $R$, inclusive.

## 输入格式

Input format:

```
N M
T[0] T[1] ... T[N-1]
H[0] H[1] ... H[M-1]
Q
L[0] R[0] S[0] D[0]
L[1] R[1] S[1] D[1]
...
L[Q-1] R[Q-1] S[Q-1] D[Q-1]
```

Here, $L[k]$, $R[k]$, $S[k]$ and $D[k]$ ($0 \leq k < Q$) specify the parameters for each call to `can_reach`.

## 输出格式

Output format:

```
A[0]
A[1]
...
A[Q-1]
```

Here, $A[k]$ ($0 \leq k < Q$) is $1$ if the call `can_reach(L[k], R[k], S[k], D[k])` returned true, and $0$ otherwise.

## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

### Example

Consider the following call:

```cpp
initialize([2, 1, 3], [0, 1, 2, 0])
```

This corresponds to the map in the following image, where white cells are free of vegetation:

![](https://cdn.luogu.com.cn/upload/image_hosting/99d0tson.png)

As the first question, consider the following call:

```
can_reach(0, 3, 1, 3)
```

This corresponds to the scenario in the following image, where the thick vertical lines indicate the range of columns from $L = 0$ to $R = 3$, and the black disks indicate the starting and ending cells:

![](https://cdn.luogu.com.cn/upload/image_hosting/ze89ex77.png)

In this case, the llama can reach from cell $(0, 1)$ to cell $(0, 3)$ through the following valid path:


$$(0, 1), (0, 0), (1, 0), (2, 0), (2, 1), (2, 2), (2, 3), (1, 3), (0, 3)$$

Therefore, this call should return true.

As the second question, consider the following call:

```
can_reach(1, 3, 1, 3)
```

This corresponds to the scenario in the following image:

![](https://cdn.luogu.com.cn/upload/image_hosting/ci9ill1r.png)

In this case, there is no valid path from cell $(0,1)$ to cell $(0,3)$, such that all cells in the path lie within columns $1$ to $3$, inclusive. Therefore, this call should return false.

### Constraints

- $1 \leq N, M, Q \leq 200000$
- $0 \leq T[i] \leq 10^9$ for each $i$ such that $0 \leq i < N$.
- $0 \leq H[j] \leq 10^9$ for each $j$ such that $0 \leq j < M$.
- $0 \leq L \leq R < M$
- $L \leq S \leq R$
- $L \leq D \leq R$
- Both cells $(0, S)$ and $(0, D)$ are free of vegetation.

### Subtasks

| Subtask | Score | Additional Constraints |
| :-: | :-: | :-: |
| 1 | 10 | $L = 0, R = M - 1$ for each question. $N = 1$. |
| 2 | 14 | $L = 0, R = M - 1$ for each question. $T[i - 1] \leq T[i]$ for each $i$ such that $1 \leq i < N$. |
| 3 | 13 | $L = 0, R = M - 1$ for each question. $N = 3$ and $T = [2, 1, 3]$. |
| 4 | 21 | $L = 0, R = M - 1$ for each question. $Q \leq 10$. |
| 5 | 25 | $L = 0, R = M - 1$ for each question. |
| 6 | 17 | No additional constraints. |



---

---
title: "[IOI 2025] 神话三峰（triples）（Part 2）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13553
tag: ['2025', 'IOI', '交互题', '提交答案', 'Special Judge']
---
# [IOI 2025] 神话三峰（triples）（Part 2）
## 题目背景


本题目前可以评测子问题 2。可在 [P13536](https://www.luogu.com.cn/problem/P13536) 评测子问题 1。
## 题目描述


东科迪勒拉山脉是安第斯山脉跨越玻利维亚的部分。它由连续的 $N$ 座山峰组成，从 $0$ 到 $N - 1$编号。山峰 $i$（$0 \leq i < N$）的**高度** $H[i]$  是 $1$ 到 $N - 1$ 之间的整数。

对任意两座山峰 $i$ 和 $j$（其中 $0 \le i < j < N$），它们的**距离**定义为 $d(i, j) = j - i$。根据古老的印加传说，三座山峰是**神话**三峰的条件是：它们的高度与两两之间的距离在**忽略顺序**后**匹配**。

形式化地， $(i, j, k)$ 是神话三峰的条件为：
* $0 \leq i < j < k < N$，
* 山峰高度 $(H[i], H[j], H[k])$ 与两两之间的距离 $(d(i,j), d(i,k), d(j,k))$ 在忽略顺序后匹配。例如，对山峰 $0, 1, 2$，其两两之间的距离是 $(1, 2, 1)$，所以山峰高度 $(H[0],H[1],H[2]) = (1,1,2)$， $(H[0],H[1],H[2]) = (1,2,1)$ 和 $(H[0],H[1],H[2]) = (2,1,1)$ 都匹配，但山峰高度 $(1,2,2)$ 则不匹配。

该问题分为两个部分，分别对应**子问题一**或者**子问题二**。你可以按任意顺序解决这些子问题。特别地，你**无需**先完成子问题一再尝试子问题二。

### 子问题一

给定山脉的描述，你的任务是计算神话三峰的数量。

#### 实现细节

你要实现以下函数：

```
long long count_triples(std::vector<int> H)
``` 

* $H$: 长度为 $N$ 的数组，表示每座山峰的高度。
* 对每个测试用例，该函数恰好被调用一次。

该函数返回一个整数 $T$，表示山脉中神话三峰的数量。

### 子问题二

你的任务是构造包含尽量多神话三峰的山脉。该子问题包含 $6$ 个有**部分得分**的**提交答案**的子任务。

对每个子任务，你将获得两个正整数 $M$ 和 $K$，需要构造一个**最多包含** $M$ 座山峰的山脉。如果你的答案中包含**至少** $K$ 个神话三峰，你将获得该子任务的满分。否则，你的得分将与你的答案中所包含的神话三峰的数量成正比。

注意，你的答案必须是一个有效的山脉。具体来说，假设你的答案包含 $N$ 座山峰（$N$ 必须满足 $3 \leq N \leq M$）。那么，山峰 $i$ 的高度 $H[i]$（$0 \leq i < N$）必须是一个 $1$ 到 $N - 1$ 之间的整数。

#### 实现细节

有两种提交解答的方法，你可以为每个子任务选择其中一种：
* **输出文件**
* **函数调用**

通过**输出文件**提交解答时，请创建并提交一个格式如下的文本文件：
```
N
H[0] H[1] ... H[N-1]
```

通过**函数调用**提交解答时，你需要实现以下函数。

```
std::vector<int> construct_range(int M, int K)
```

* $M$: 最多允许的山峰数量。
* $K$: 期望的神话三峰数量。
* 对每个测试用例，该函数恰好被调用一次。

该函数应返回一个长度为 $N$ 的数组 $H$，表示每座山峰的高度。

## 输入格式


子问题一和二使用相同的评测程序示例，两个子问题的区别由输入的第一行确定。

子问题一的输入格式：

```
1
N
H[0] H[1] ... H[N-1]
```

子问题二的输入格式：

```
2
M K
```

## 输出格式


子问题一的输出格式：
```
T
```

子问题二的输出格式：

```
N
H[0] H[1] ... H[N-1]
```

注意，评测程序示例的输出格式与子问题二输出文件所需的格式一致。
## 样例

### 样例输入 #1
```
1
7
4 1 4 3 2 6 1
```
### 样例输出 #1
```
3
```
## 提示


### 子问题 1 例子

考虑以下调用。

```
count_triples([4, 1, 4, 3, 2, 6, 1])
```

该山脉中包含 $3$ 个神话三峰：

* 对 $(i,j,k)=(1,3,4)$，高度 $(1,3,2)$ 与两两之间的距离 $(2,3,1)$ 匹配。
* 对 $(i,j,k)=(2,3,6)$，高度 $(4,3,1)$ 与两两之间的距离 $(1,4,3)$ 匹配。
* 对 $(i,j,k)=(3,4,6)$，高度 $(3,2,1)$ 与两两之间的距离 $(1,3,2)$ 匹配。

因此，该函数应该返回 $3$。

注意，$(0, 2, 4)$ 不构成神话三峰，因为其高度 $(4,4,2)$ 与两两之间的距离 $(2,4,2)$ 并不匹配。

### 子问题 1 数据范围

- $3 \leq N \leq 200\,000$。
- 对每个满足 $0 \le i < N$ 的 $i$，都有 $1 \leq H[i] \leq N-1$。

### 子任务与得分规则

子问题一总共 $70$ 分。

| 子任务 | 分数 | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1       | $8$    | $N \leq 100$
| 2       | $6$    | 对每个满足 $0 \leq i < N$ 的 $i$，都有 $H[i] \leq 10$。
| 3       | $10$   | $N \leq 2000$
| 4       | $11$   | 山峰的高度是单调不下降的。  也就是说，对每个满足 $1 \leq i < N$ 的 $i$ 都有 $H[i - 1] \leq H[i]$。
| 5       | $16$   | $N \leq 50\,000$
| 6       | $19$   | 没有额外的约束条件。

子问题二总共 $30$ 分。
每个子任务的 $M$ 和 $K$ 值是固定的，如下表所示：


| 子任务 | 分数 | $M$        | $K$             |
| :-----: | :---: | :--------: | :-------------: |
| 7       | $5$   | $20$       | $30$
| 8       | $5$   | $500$      | $2000$
| 9       | $5$   | $5000$     | $50\,000$
| 10      | $5$   | $30\,000$  | $700\,000$
| 11      | $5$   | $100\,000$ | $2\,000\,000$
| 12      | $5$   | $200\,000$ | $12\,000\,000$

对每个子任务，如果你的答案不构成有效的山脉，你的得分将为 $0$（在 CMS 中被报告为 `Output isn't correct`）。否则，设 $T$ 表示答案中的神话三峰数量。
则你在该子任务中的得分为：
$$5 \cdot \min\left(1,\frac{T}{K}\right)$$


---

---
title: "[IOI 2018] doll 机械娃娃"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13613
tag: ['2018', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2018] doll 机械娃娃
## 题目描述

所谓机械娃娃，是能够自动地重复特定运动序列的娃娃。在日本，很多机械娃娃在古代就造出来了。

机械娃娃的运动被一个由多个器件组成的**管路**所控制。这些器件通过管道连在一起。每个器件都有一个或两个出口，而且可以有任意多的（也可以为零）的入口。每个管道都从某个器件的出口连到同一器件或其他器件的入口。每个入口都连接恰好一个管道，而每个出口也都连接恰好一个管道。

为了描述娃娃是如何运动的，设想有一个球放在这些器件之一的上面。这个球在管路中穿行。在穿行的每一步，它从所在器件的一个出口离开该器件，沿着连接该出口的管道，进入管道另一头所连接的器件。

器件有三种类型：起点、触发器和开关。总共有恰好一个起点，$M$ 个触发器和 $S$ 个开关（$S$ 可以为零）。开关的数量 $S$ 要由你来定。每个器件都有唯一的序列号。

起点是球最初所在的那个器件。它有一个出口。它的序列号是 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cnmnkflu.png)

一旦球进入某个触发器，就会让娃娃做某个特定运动。每个触发器都有一个出口。触发器的序列号是从 $1$ 到 $M$。

![](https://cdn.luogu.com.cn/upload/image_hosting/uwqtlkfh.png)

每个开关都有两个出口，被记为 `X` 和 `Y`。开关的状态或者为 `X`，或者为 `Y`。在球进入某个开关后，它会从开关的当前状态所对应的出口离开。此后开关将切换为另一状态。最初，所有开关的状态都是 `X`。开关的序列号是从 $-1$ 到 $-S$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4lq84q7s.png)

告诉你触发器的数量 $M$。再给你一个长度为 $N$ 的序列 $A$，序列的每个元素都是某个触发器的序列号。每个触发器会在序列 $A$ 中出现若干次（也可能是零次）。你的任务是设计一个管路，以满足如下条件：

- 球在若干步之后返回到起点。
- 当球首次返回到起点时，所有开关的状态都是 `X`。
- 在球首次返回到起点时，此前它进入所有触发器的总次数恰好为 $N$。这些被进入过的触发器，其序列号按照被球经过的顺序依次为 $A_0,A_1,\ldots ,A_{N-1}$。
- 设 $P$ 为球首次返回到起点时，球所引起的所有开关状态切换的总次数。$P$ 不能超过 $2\times 10^7$。

同时，你不想用太多的开关。

### 实现细节
~~你需要包含 `doll.h` 库文件，并实现下面的过程。~~

你的程序无需包含 `doll.h` 库文件。你需要将 `void answer(vector<int> C, vector<int> X, vector<int> Y);` 放在程序开头，并且请选择 C++20/C++23 提交。

```cpp
create_circuit(vector<int> M, vector<int> A)
```
- `M`：触发器数量。
- `A`：长度为 $N$ 的数组，其中按照球进入的顺序，给出了被进入的触发器的序列号。
- 该过程将被调用恰好一次。
- 注意，$N$ 的值是数组 `A` 的长度，你可以按照注意事项中的有关内容来取得。

你的程序需要调用下面的过程来作答。

```cpp
answer(vector<int> C, vector<int> X, vector<int> Y)
```
- `C`：长度为 的数组。器件 $i\ (0\le i\le M)$ 的出口被连到器件 `C[i]`。
- `X, Y`：长度相同的两个数组。这些数组的长度 $S$ 为开关的数量。对于开关 $-j\ (1\le j\le S)$ 来说，其出口 `X` 被连到器件 `X[j - 1]`，而出口 `Y` 被连到器件 `Y[j - 1]`。
- `C`、`X` 和 `Y` 中的任一元素必须是 $-S$ 到 $M$ 的整数（包括 $-S$ 和 $M$）。
- $S$ 最多只能是 $4\times 10^5$。
- 必须调用该过程恰好一次。
- 由 `C`、`X` 和 `Y` 所表示的管路必须满足题面中的限制条件。

如果上述条件不满足，你的程序将被判为 `Wrong Answer`。否则，你的程序将被判为 `Accepted`，而你的得分将根据 $S$ 来计算（参见子任务）。
## 输入格式

评测程序示例按照以下格式从标准输入中读入输入：
- 第一行：$M\ N$
- 第二行：$A_0\ A_1\ldots \ A_{N-1}$


## 输出格式

评测程序示例产生三个输出。

首先，评测程序示例把你的答案以下列格式输出到文件 `out.txt`。
- 第一行：$S$
- 第 $2+i$ 行（$0\le i\le M$）：`C[i]`
- 第 $2+M+j$ 行（$1\le j\le S$）：`X[j - 1] Y[j - 1]`

其次，评测程序示例模拟球的移动。它把该球经过的器件的序列号，按照经过顺序输出到文件 `log.txt`。

第三，评测程序示例将在标准输出中打印对你的答案的评价

- 如果你的程序被判为 `Accepted`，评测程序示例按照以下格式打印 $S$ 和 $P$：`Accepted: S P`；
- 如果你的程序被判为 `Wrong Answer`，它打印 `Wrong Answer: MSG`。各类 `MSG` 的含义如下：
  - `answered not exactly once`：过程 `answer` 不是恰好被调用一次。
  - `wrong array length`：`C` 的长度不是 $M+1$，或者 `X` 和 `Y` 的长度不一样。
  - `over 400000 switches`：$S$ 大于 $4\times 10^5$。
  - `wrong serial number`：`C`、`X` 或者 `Y` 的某个元素比 $-S$ 小或者比 $M$ 大。
  - `over 20000000 inversions`：球没有在所有开关的状态变化总数超过 $2\times 10^7$ 之前返回到起点。
  - `state 'Y'`：当球首次返回到起点时，某个开关的状态为 `Y`。
  - `wrong motion`：触发运动的触发器和序列 $A$ 所列的不一致。

注意，当你的程序被判为 `Wrong Answer` 时，评测程序示例可能并不创建 `out.txt` 和/或 `log.txt`。
## 样例

### 样例输入 #1
```
4 4
1 2 1 3

```
### 样例输出 #1
```

```
## 提示

### 例子

![](https://cdn.luogu.com.cn/upload/image_hosting/hk346f75.png)

假设 $M = 4$, $N = 4$ 和 $A = [1, 2, 1, 3]$。评测程序调用 `create_circuit(4, [1, 2, 1, 3])`。

上图展示了函数调用 `answer([1, -1, -2, 0, 2], [2, -2], [3, 1])` 所对应的管路图。图中的数字是器件的序列号。

图中使用了两个开关。所以 $S = 2$。

开关 $-1$ 和 $-2$ 的初始状态都是“X”。

球的穿行轨迹如下:

$$0 \rightarrow 1 \rightarrow -1 \xrightarrow{\text{X}} 2 \rightarrow -2 \xrightarrow{\text{X}} -2 \xrightarrow{\text{Y}} 1 \rightarrow -1 \xrightarrow{\text{Y}} 3 \rightarrow 0$$

当球首次进入开关 $-1$ 时，该开关的状态为“X”。所以，该球走到触发器 2。然后开关 $-1$ 的状态变成“Y”。

当球第二次进入开关 $-1$ 时，该开关的状态为“Y”。所以，该球走到触发器 3。然后开关 $-1$ 的状态变为“X”。

球在经过触发器 $1, 2, 1, 3$ 后首次返回到起点。开关 $-1$ 和 $-2$ 的状态都是“X”。$P$ 的值是 。所以，这个管路是满足条件的。

在压缩附件包中，有一个文件 `sample-01-in.txt` 对应于本例。其他输入样例也可以在压缩附件包中找到。

在样例数据下载中的文件 `ex_doll1.in` 对应于本例。其他的输入样例在样例包中还可找到。注意：样例包中的输出没有任何意义。

### 限制条件

对于全部数据，$1\le M\le 10^5,1\le N\le 2\times 10^5,1\le A_k\le M\ (0\le k\le N-1)$。

### 子任务

每个测试样例的分数和限制条件如下：
1. （2 分）对每个 $i\ (1\le i\le M)$，整数 $i$ 在序列 $A_0,A_1,\ldots ,A_{N-1}$ 中最多出现 $1$ 次。
2. （4 分）对每个 $i\ (1\le i\le M)$，整数 $i$ 在序列 $A_0,A_1,\ldots ,A_{N-1}$ 中最多出现 $2$ 次。
3. （10 分）对每个 $i\ (1\le i\le M)$，整数 $i$ 在序列 $A_0,A_1,\ldots ,A_{N-1}$ 中最多出现 $4$ 次。
4. （10 分）$N=16$
5. （18 分）$M=1$
6. （56 分）无附加限制

对每个测试样例，如果你的程序被判定为 `Accepted`, 你的得分将根据 $S$ 的值来计算：
- 如果 $S\le N+\log_2 N$，你将获得该测试样例的满分。
- 对于子任务 $5$ 和 $6$ 的每个测试样例，如果 $N+\log_2 N\le S\le 2N$，你将获得部分分。该测试样例上的得分为 $0.5+0.4\times(\frac{2N-S}{N-\log_2 N})^2$，再乘以该子任务的满分分数。
- 否则，得分为 $0$。

注意，你在每个子任务上的得分是该子任务中所有测试样例上的最低得分。


---

---
title: "[IOI 2018] highway 高速公路收费"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13614
tag: ['2018', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2018] highway 高速公路收费
## 题目描述

在日本，城市是用一个高速公路网络连接起来的。这个网络包含 $N$ 个城市和 $M$ 条高速公路。每条高速公路都连接着两个不同的城市。不会有两条高速公路连接相同的两个城市。城市的编号是从 $0$ 到 $N-1$，高速公路的编号则是从 $0$ 到 $M-1$。每条高速公路都可以双向行驶。你可以从任何一个城市出发，通过这些高速公路到达其他任何一个城市。

使用每条高速公路都要收费。每条高速公路的收费都会取决于它的**交通状况**。交通状况或者为**顺畅**，或者为**繁忙**。当一条高速公路的交通状况为顺畅时，费用为 $A$ 日元（日本货币），而当交通状况为繁忙时，费用为 $B$ 日元。这里必有 $A\lt B$。注意，$A$ 和 $B$ 的值对你是已知的。

你有一部机器，当给定所有高速公路的交通状况后，它就能计算出在给定的交通状况下，在两个城市 $S$ 和 $T$（$S\neq T$）之间旅行所需要的最小的高速总费用。

然而，这台机器只是一个原型。所以 $S$ 和 $T$ 的值是固定的（即它已经被硬编码到机器中），但是你并不知道它们的值是什么。你的任务就是去找出 $S$ 和 $T$ 的值。为了找出答案，你打算先给机器设定几种交通状况，然后利用它输出的高速费用来推断出 $S$ 和 $T$。由于设定高速公路交通状况的代价很大，所以你并不想使用这台机器很多次。

### 实现细节
~~你需要在开始包含 `highway.h` 库文件，并实现下面的过程：~~

你的程序无需包含 `highway.h`，但是你应当在程序的开头加上 `long long ask(const vector<int> &w);` 和 `void answer(int s, int t);`。

你应当实现下面的过程：
```cpp
find_pair(int N, int[] U, int[] V, int A, int B)
```
- `N`：城市的数量。
- `U` 及 `V`：长度为 $M$ 的数组，其中 $M$ 为连接城市的高速公路的数量。对于每个 $i$（$0\le i\le M-1$），高速公路 $i$ 连接城市 `U[i]` 和 `V[i]`。
- `A`：交通状况顺畅时高速公路的收费。
- `B`：交通状况繁忙时高速公路的收费。
- 对于每个测试样例，该过程会被调用恰好一次。
- 注意，$M$ 为数组的长度，所有数组均为 `vector`。

过程 `find_pair` 可以调用以下函数：
```cpp
int64 ask(int[] w)
```
- `w` 的长度必须为 $M$。 数组 `w` 描述高速公路的交通状况。
- 对于每个 $i$（$0\le i\le M-1$），`w[i]` 表示高速公路 $i$ 的交通状况。`w[i]` 的值必须为 $0$ 或 $1$。
  - `w[i] = 0` 表示高速公路 $i$ 的交通状况为顺畅。
  - `w[i] = 1` 表示高速公路 $i$ 的交通状况为繁忙。
- 该函数返回的是，在 `w` 所描述的交通状况下，在城市 $S$ 和 $T$ 之间旅行所需的最少总费用。
- 该函数最多只能被调用 $100$ 次（对于每个测试样例）。

`find_pair` 应调用以下过程来报告答案：
```cpp
answer(int s, int t)
```
- `s` 和 `t` 的值必须为城市 $S$ 和 $T$（两者的先后次序并不重要）。
- 该过程必须被调用恰好一次。

如果不满足上面的条件，你的程序将被判为 `Wrong Answer`。否则，你的程序将被判为 `Accepted`，而你的得分将根据 `ask` 的调用次数来计算（参见子任务）。
## 输入格式

评测程序示例将读取如下格式的输入：
- 第一行：$N\ M\ A\ B\ S\ T$
- 第 $2+i$ 行（$0\le i\le M-1$）：$U[i]\ V[i]$
## 输出格式

如果你的程序被判为 `Accepted`，评测程序示例将打印出 `Accepted: q`，这里的 `q` 为函数 `ask` 被调用的次数。

如果你的程序被判为 `Wrong Answer`，它打印出 `Wrong Answer: MSG`。各类 `MSG` 的含义如下：
- `answered not exactly once`：过程 `answer` 没有被调用恰好一次。
- `w is invalid`：传给函数 `ask` 的 `w` 的长度不是 $M$，或者某个 $i$（$0\le i\le M-1$）上的 `w[i]` 既不是 $0$ 也不是 $1$。
- `more than 100 calls to ask`：函数 `ask` 的调用次数超过 $100$ 次。
- `{s, t} is wrong`：调用 `answer` 时的 `s` 和 `t` 是错的。
## 样例

### 样例输入 #1
```
4 4 1 3 1 3
0 1
0 2
0 3
1 2
```
### 样例输出 #1
```

```
## 提示

### 限制条件

对于全部数据：
- $2\le N\le 9\times 10^4,1\le M\le 1.3\times 10^5,1\le A\lt B\le 10^9$
- 对于每一个 $0\le i\le M-1$
  - $0\le U[i],V[i]\le N-1$
  - $U[i]\neq V[i]$
- 保证数据无重边。
- 你可以从任何一个城市出发，通过高速公路到达其他任何一个城市。
- $0\le S,T\le N-1,S\neq T$

在本题中，评测程序不是适应性的。意思是说，在评测程序开始运行的时候 $S$ 和 $T$ 就固定下来，而且不依赖于你的程序所做的询问。

### 子任务
1. (5 分) $S$ 或 $T$ 有一个是 $0$，$N\le 100,M=N-1$
2. (7 分) $S$ 或 $T$ 有一个是 $0$，$M=N-1$
3. (6 分) $M=N-1,U[i]=i,V[i]=i+1\ (0\le i\le M-1)$
4. (33 分) $M=N-1$
5. (18 分) $A=1,B=2$
6. (31 分) 没有附加限制。
 
假设你的程序被判为 `Accepted`，而且函数 `ask` 调用了 $X$ 次。你在该测试样例上的得分 $P$，取决于对应子任务的编号，其计算如下：
- 子任务 1：$P=5$
- 子任务 2：如果 $X\le 60$，$P=7$。否则 $P=0$。
- 子任务 3：如果 $X\le 60$，$P=6$。否则 $P=0$。
- 子任务 4：如果 $X\le 60$，$P=33$。否则 $P=0$。
- 子任务 5：如果 $X\le 52$，$P=18$。否则 $P=0$。
- 子任务 6：
  - 如果 $X\le 50$，$P=31$。
  - 如果 $51\le X\le 52$，$P=21$。
  - 如果 $53\le X$，$P=0$。

注意，你在每个子任务上的得分，等于你在该子任务中所有测试样例上的最低得分。


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
title: "[IOI 2017] Toy Train"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3838
tag: ['2017', 'IOI', '交互题']
---
# [IOI 2017] Toy Train
## 题目背景

# 滥用本题评测将被封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。
## 题目描述

Arezou 和她的兄弟 Borzou 是双胞胎。他们收到的生日礼物是一套好玩的玩具火车。他们用它建了一下 $n$ 个车站和 $m$ 段单向轨道的铁路系统。这些车站的编号是从 $0$ 到 $n-1$。每段轨道都始于某一车站，然后终于同一车站或其他车站。每个车站至少会有一段轨道以它为起点。

其中有些车站是充电车站。无论何时，如果火车抵达某个充电车站。无论何时，如果火车抵达某个充电车站，它都会被充到满电。满电火车拥有足够的动力连续地试过 $n$ 段轨道，但是如果不再充电的话，在即将进入第 $n+1$ 段轨道时它就会因电已用光而停车。

每个车站都有一个轨道开关，可以扳向任一以该车站为起点的轨道。火车从某个车站驶出时，驶向的正是该车站的开关所扳向的轨道。

这对双胞胎打算用他们的火车玩个游戏。他们已经分完了所有的车站：每个车站要么归 Arezou，要么归 Borzou。游戏里面只有一列火车。游戏开始时，这列火车停在车站 $s$ ，并且充满了电。为启动游戏，车站 $s$ 的拥有者把车站 $s$ 的开关扳向某个以 $s$ 为起点的轨道。随后他们启动火车，火车也就开始沿着轨道行驶。无论何时，在火车首次进入某一车站时，该车站的拥有者都要扳定车站开关。开关一旦扳定，它就会保持状态不变直到游戏结束。因此，火车如果开到了一个曾经进过的车站，就会沿着与之前相同的轨道开出该车站。

由于车站数量是有限的，火车的行驶最终都会落入某个环路。环路是指一系列**不同**的车站 $c_0,c_1,\cdots ,c_{k-1}$，其中火车在离开车站 $c_i\ \ (0\leqslant i < k-1)$ 后驶上连向车站 $c_{i+1}$ 的轨道，在离开车站 $c_{k-1}$ 后驶上连向车站 $c_0$ 的轨道。一个环路可能只包括一个车站（此时 $k=1$），即火车从车站 $c_0$ 驶出后又驶上了连向车站 $c_0$ 的轨道。

如果火车能够连续行驶跑完，Arezou 就赢了。否则火车最后会把电用光而停车，这样 Borzou 就赢了。换句话说，如果 $c_0,c_1,\cdots ,c_{k-1}$中至少有一个充电车站，且使得火车能够不断地充电而沿着环路跑个没完，Arezou 赢。否则，它就会最终把电用光（有可能是在沿着环路跑好几圈后），Borzou 赢。

现在给你一个这样的铁路系统。Arezou 和 Borzou将会玩 $n$ 轮游戏。其中在第 $s$ 轮游戏中（$0\leqslant s \leqslant n-1$），火车最初停在车站 $s$ 上。你的任务是，对每一轮游戏，判断是否无论 Borzou 怎么玩，Arezou 都必胜。

## 实现细节

你需要实现下面的函数

(C++) `std::vector who_wins(std::vector<int> a, std::vector<int> r, std::vector<int> u, std::vector<int> v)`

(Java) `int[] who_wins(int[] a, int[] r, int[] u, int[] v)`

- $a$：长度为 $n$ 的数组。如果 Arezou 拥有车站 $i$，则 $a_i=1$；否则 Borzou 拥有车站 $i$，且 $a_i=0$。

- $r$：长度为$n$的数组。如果车站$i$是充电车站，则$r[i]=1$。否则$r[i]=0$。

- $u$ 和 $v$：长度为 $m$ 的数组。对于所有 $0\leqslant i \leqslant m-1$，存在某一单向轨道，其起点为 $u_i$，终点为 $v_i$。

- 该函数需要返回一个长度为 $n$ 的数组  $w$。对于每个 $0\leqslant i \leqslant n-1$，如果在火车最初停在车站 $i$ 的游戏中，不管 Borzou 怎么玩，Arezou 都能赢，则 $w_i$ 的值应为 $1$。否则 $w_i$ 的值应为 $0$。

## 输入格式

你需要实现上述子程序。

## 输出格式

你的子程序需要返回一个合法的结果。

## 样例

### 样例输入 #1
```
a = [0, 1]
r = [1, 0]
u = [0, 0, 1, 1]
v = [0, 1, 0, 1]
```
### 样例输出 #1
```
who_wins = [1, 1]
```
## 提示

 ![](https://cdn.luogu.com.cn/upload/pic/6727.png) 

- 这里有 $2$ 个车站。Borzou 拥有充电车站 $1$。Arezou拥有充电车站 $1$，但是它不是充电车站。

- 这里有 $4$ 段轨道 $(0,0),(0,1),(1,0)$ 和 $(1,1)$，其中 $(i,j)$ 表示一个以车站 $i$ 为起点、车站$j$为终点的单向轨道。

- 考虑火车最初停在车站 $0$ 的游戏。如果 Borzou 将车站 $0$ 的开关扳向轨道 $(0,0)$，那么火车就会沿着这个环形轨道绕个没完（注意，车站 $0$ 是一个充电车站）。在这种情况下，Arezou 赢。否则，如果 Borzou 把车站 $0$ 的开关扳向轨道 $(0,1)$，Arezou 可以把车站 $1$ 的开关扳向轨道 $(1,0)$。这样的话，火车将会在两个车站之间绕个不停。Arezou 还是会赢，因为车站$0$是充电车站，火车将跑个没完。因此，无论 Borzou 怎么玩，Arezou 都会赢。

- 根据类似的逻辑，在火车最初停在车站 $1$ 的游戏中，无论 Borzou 怎么玩，Arezou 也都会赢。因此，函数应当返回 $[1,1]$。


## 数据范围和限制

- $1\leqslant n \leqslant 5000$
- $n \leqslant m \leqslant 20000$
- 至少会有一个充电车站。
- 每个车站至少会有一段轨道以它为起点。
- 可能会有某个轨道的起点和终点是相同的（即 $u_i=v_i$）。
- 所有轨道两两不同。也就是说，不存在这样的两个下标 $i$ 和 $j$（$0\leqslant i < j \leqslant m-1$），使得 $u_i=u_j$ 且 $v_i=v_j$。
- 对于所有 $0\leqslant i \leqslant m-1$，都有 $0\leqslant u_i,v_i \leqslant n-1$。

## 子任务

1. ($5$ 分) 对于所有 $0 \leqslant i \leqslant m-1$，都有 $v_i=u_i$ 或者 $v_i=u_i+1$。
2. ($10$ 分) $n\leqslant 15$。
3. ($11$ 分) Arezou 拥有所有车站。
4. ($11$ 分) Borzou 拥有所有车站。
5. ($12$ 分) 充电车站的数量为 $1$。
6. ($51$ 分) 无任何限制。



---

---
title: "[IOI 2008] Teleporters"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4686
tag: ['2008', 'IOI']
---
# [IOI 2008] Teleporters
## 题目描述

你正在参加一项沿着直线路线自西向东横穿埃及的比赛。开始时你位于这条直线路线的最西端。根据比赛规则，你必须要沿着这条直线路线始终向东行进。

在这条直线路线上有 $N$ 个传送器。每个传送器都有两个端点。每当你到达某个传送器的两个端点之一时，传送器都会立即将你传送到该传送器的另一个端点（注意，根据你所在的端点位置，传送器能够将你从当前位置向东或者向西传送）。当你被传送到另一个端点之后，你必须继续沿这条直线路线向东行进；你无法避开你前进路上的任何传送器端点。绝不会出现两个端点在同一位置的情形。所有端点都严格位于这条直线路线的起点和终点之间。

每当你被传送一次，你就会获得 $1$ 分。比赛的目标就是获取尽可能多的分数。为使获得的分数最多，允许你在比赛开始前在这条路线上增设 $M$ 个新的传送器。使用这些新的传送器你也同样可以获得分数。

你可以将这些新传送器的端点设在任何位置上（甚至是非整数坐标点也可以），只要这些坐标点并不出现在已经被另一个端点占用的位置上即可。换句话说，所有传送器的端点位置必须是唯一的。同样，新传送器的端点都必须严格位于这条直线路线的起点和终点之间。

题目可以保证，不管你如何增设这些传送器，你一定可以到达比赛路线的终点。

试编写一个程序，对于给定的 $N$ 个传送器的端点位置和你可以增设的新传送器的数目 $M$，计算你能获得的最高分数。
## 输入格式

你的程序必须从标准输入中读入下列数据： 
- 第 $1$行包含一个整数 $N$，表示开始时在路线上的传送器数目；
- 第 $2$行包含一个整数 $M$，表示你可以增设的新传送器的最大数目；
- 随后的 $N$ 行每行描述一个传送器。第 $i$ 行描述第 $i$ 个传送器。每行有两个整数 $W_i$ 和 $E_i$，这两个整数分别描述从路线起点到该传送器的两个端点的距离。

对于给定的这些传送器，没有任何两个端点在同一位置上。比赛路线的起点为位置 $0$，而终点则在位置 $2\,000\,001$ 上。 
## 输出格式

你的程序必须向标准输出写一行数据，这行数据只包含一个整数，表示你找到的能获得的最高分数。
## 样例

### 样例输入 #1
```
3
1
10 11
1 4
2 3
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 3 5 7 6 10 1999999 2000000
```
### 样例输出 #2
```
12
```
## 提示

### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/pic/20908.png )

上面左图表示一条初始有 $3$ 个传送器的比赛路线的情形。右图表示在增设一个端点分别为 $0.5$ 和 $1.5$ 的新传送器之后的同一比赛路线。

在增设上图所示的新的传送器之后，你的比赛路途如下：
- 你从位置 $0$ 出发，向东行进。
- 你到达位于 $0.5$ 的传送器端点，并且被传送到另一端点 $1.5$（你获得 $1$ 分）。
- 你继续向东行进，并且到达位于 $2$ 的传送器端点；你被传送到位于 $3$ 的另一端点（这时你共获得 $2$ 分）。
- 你到达位于 $4$ 的传送器端点，并且被传送到位于 $1$ 的另一端点（这时你共获得 $3$ 分）。
- 你到达位于 $1.5$ 的传送器端点，并且被传送到位于 $0.5$ 的另一端点（这时你共获得 $4$ 分）。
- 你到达位于 $1$ 的传送器端点，并且被传送到位于 $4$ 的另一端点（这时你共获得 $5$ 分）。
- 你到达位于 $10$ 的传送器端点，并且被传送到位于 $11$ 的另一端点（这时你共获得 $6$ 分）。
- 你继续行进直到到达比赛的终点，以获得总分为 $6$ 分结束。

### 数据范围

- 对于 $30\%$ 的数据，$N \leq 500$ 并且 $M \leq 500$。 
- 对于所有数据，$1 \leq N \leq 1,000,000$，$1 \leq M \leq 1,000,000$，$1 \leq W_X < E_X \leq 2,000,000$。


---

---
title: "[IOI 2008] Pyramid Base"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4687
tag: ['2008', 'IOI']
---
# [IOI 2008] Pyramid Base
## 题目描述

你要在自己财力许可的范围内寻找一个尽可能大的地方，以便兴建一个新的金字塔。为帮助你作出决定，为你提供了土地测绘图。为方便起见，该地块被划分为由$M\times N$个小正方形构成的网格。金字塔的地基部份必须是正方形，而且各边要与这些方格平行。

测绘图中标出了$P$个有可能重叠的障碍物，这些障碍物是上述网格上的长方形，其各边与方格平行。为了建造金字塔，任何塔基所占方格中的障碍物必须被移走。移除障碍物$i$需要付出成本$C_i$。当移除一个障碍物时，需要将障碍物整个地移除，即不能只移除障碍物的一部份。同时，移除一个障碍物对与其重叠的其他障碍物无任何影响。

已知测绘图中$M$和$N$的大小，对$P$个障碍物的描述，移走每个障碍物的成本以及你的预算$B$。编写程序，找出在移走障碍物总成本不超过$B$的前提下金字塔地基的最大边长。 


## 输入格式

你的程序需要从标准输入上读入以下数据： 
- 第一行包含两个以单个空格分隔的整数，分别表示$M$及$N$。 
- 第二行包含整数$B$，是你可付出的最大成本（即你的预算）。 
- 第三行包含整数$P$，是测绘图中标出的障碍物数量。 
- 以下$P$行的每一行表示一个障碍物。其中第$i$ 行表示第$i$个障碍物。每一行包含$5$个以单个空格分隔的整数$X_{i1}, Y_{i1}, X_{i2}, Y_{i2}$和$C_i$，分别表示障碍物左下角小正方形的座标，右上角小正方形的座标，以及移除这个障碍物的成本。网格左下角的小正方形座标为$(1,1)$，而其右上角小正方形为$(M, N)$。 
## 输出格式

你的程序必须向标准输出写出一行，该行只含一个整数，即金字塔基可能的最大边长。如果无法建造任何金字塔，程序应输出0。 
## 样例

### 样例输入 #1
```
6 9
42
5
4 1 6 3 12
3 6 5 6 9
1 3 3 8 24
3 8 6 9 21
5 1 6 2 20
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
13 5
0
8
8 4 10 4 1
4 3 4 4 1
10 2 12 2 2
8 2 8 4 3
2 4 6 4 5
10 3 10 4 8
12 3 12 4 13
2 2 4 2 21
```
### 样例输出 #2
```
3
```
## 提示

### 样例说明

样例1：

![](https://cdn.luogu.com.cn/upload/pic/20909.png )

样例2：

![](https://cdn.luogu.com.cn/upload/pic/20910.png )

### 数据范围

程序用三组不相交的数据进行评测。以下限制适用于所有的测试数据： $1 \leq M, N \leq 1,000,000$ 网格的尺寸。 $1 \leq Ci \leq 7,000$ 移除障碍物i的成本。 对每个障碍物$i$均有 $1 \leq X_{i1} \leq X_{i2} \leq M$ 并且 $1 \leq Y_{i1} \leq Y_{i2}\leq N$。 

第一组测试总分值35分： 

- $B = 0$ ——可以付出的最大成本。（不可移除任何障碍物）
- $1\leq P \leq 1,000$ ——网格中障碍物的数目。

第二组测试总分值35分：

- $0 < B \leq 2,000,000,000$ ——你的预算。

- $1\leq P \leq 30,000$ ——网格中障碍物的数目。 

第三组测试值30分：

- $B = 0$ ——你的预算。（不可以移除任何障碍物）

- $1\leq P \leq 400,000$ ——网格中障碍物的数目。 


---

---
title: "[IOI 2018] seats 排座位"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4898
tag: ['2018', '线段树', 'IOI', 'O2优化', '连通块']
---
# [IOI 2018] seats 排座位
## 题目背景

本题为交互题，但在此请提交**完整程序**。
## 题目描述

你要在一个长方形大厅里举办国际编程比赛，该大厅共有 $HW$ 个座位（$H$ 行 $W$ 列）。行的编号是从 $0$ 到 $H-1$，列的编号是从 $0$ 到 $W-1$。位于 $r$ 行 $c$ 列的座位用 $(r,c)$ 表示。一共邀请了 $HW$ 位参赛者，编号是从 $0$ 到 $HW-1$。你制定好了一个座位表，第 $i(0 \leq i \leq HW - 1)$ 个参赛者被安排到座位 $(R_i,C_i)$。座位表中参赛者和座位是一一对应的。

大厅中一个座位集合 $S$ 被称为是**长方形的**，如果存在整数 $r_1, r_2, c_1$ 和 $c_2$ 满足下列条件：

- $0 \leq r_1 \leq r_2 \leq H - 1$。
- $0 \leq c_1 \leq c_2 \leq W - 1$。
- $S$ 正好是所有满足 $r_1 \leq r \leq r_2$ 和 $c_1 \leq c \leq c_2$ 的座位 $(r, c)$ 的集合。

如果一个长方形座位集合包含 $k(1 \leq k \leq HW)$ 个座位，并且被分配到这个集合的参赛者的编号恰好是从 $0$ 到 $k-1$，那么该集合是**美妙的**。一个座位表的**美妙度**定义为这个表中美妙的长方形座位集合的个数。

在准备好座位表后，你会收到一些交换两个参赛者座位的请求。具体来说，有 $Q$ 个这样的请求，按时间顺序编号为 $0$ 到 $Q-1$。第 $j(0 \leq j \leq Q - 1)$ 个请求希望交换参赛者 $A_j$ 和 $B_j$ 的座位。你立即接受每个请求并更新座位表。每次更新后，你的目标是计算当前座位表的美妙度。
## 输入格式

输入的第一行包含三个正整数 $H, W, Q$，其意义见题目描述。

接下来 $HW$ 行，每行包含两个非负整数。在这 $HW$ 行中，第 $i$ 行的两个整数分别表示 $R_{i - 1}, C_{i - 1}$，即编号为 $i - 1$ 的参赛者初始座位的行和列。

接下来 $Q$ 行，每行包含两个非负整数。在这 $Q$ 行中，第 $j$ 行的两个整数分别表示 $A_{j - 1}, B_{j - 1}$，即在编号为 $j - 1$ 的请求中希望被交换座位的两位参赛者的编号。
## 输出格式

输出共 $Q$ 行，每行包含一个整数，第 $i$ 行的整数表示按时间顺序处理完编号为 $i - 1$ 的交换请求之后当前座位表的美妙度。
## 样例

### 样例输入 #1
```
2 3 2
0 0
1 0
1 1
0 1
0 2
1 2
0 5
0 5

```
### 样例输出 #1
```
3
4

```
### 样例输入 #2
```
1 5 3
0 0
0 1
0 2
0 3
0 4
0 1
0 3
4 0

```
### 样例输出 #2
```
5
3
2

```
## 提示

**限制条件**

- $1 \leq H$
- $1 \leq W$
- $HW \leq 1, 000, 000$
- $0 \leq R_i \leq H - 1(0 \leq i \leq HW - 1)$
- $0 \leq C_i \leq W - 1(0 \leq i \leq HW - 1)$
- $(R_i, C_i) \neq (R_j, C_j)(0 \leq i < j \leq HW - 1)$
- $1 \leq Q \leq 50, 000$
- $0 \leq A_j \leq HW - 1(0 \leq j \leq Q - 1)$
- $0 \leq B_j \leq HW - 1(0 \leq j \leq Q - 1)$
- $A_j \neq B_j(0 \leq j \leq Q - 1)$

**子任务**

- 1.（5 分） $HW \leq 100$，$Q \leq 5, 000$
- 2.（6 分） $HW \leq 10, 000$，$Q \leq 5, 000$
- 3.（20 分） $H \leq 1, 000$，$W \leq 1, 000$，$Q \leq 5, 000$
- 4.（6 分） $Q \leq 5, 000$，$|A_j - B_j| \leq 10, 000(0 \leq j \leq Q - 1)$
- 5.（33 分） $H = 1$
- 6.（30 分） 无附加限制条件


---

---
title: "[IOI 2018] meetings 会议"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5044
tag: ['2018', 'IOI', 'O2优化']
---
# [IOI 2018] meetings 会议
## 题目背景

本题为交互题，但在此请提交**完整程序**。

本题因为测试点过多，文件过大，只选择了33个测试点进行测评（涵盖了所有子任务）。剩余11组数据可下载数据自行测评。

https://ioi2018.jp/wp-content/tasks/contest2/meetings.zip
## 题目描述

有 $N$ 座山横着排成一行，从左到右编号为从 $0$ 到 $N-1$。山的高度为 $H_i$（$0\leq i\leq N-1$）。每座山的顶上恰好住着一个人。

你打算举行 $Q$ 个会议，编号为从 $0$ 到 $Q-1$。会议 $j$（$0\leq j\leq Q-1$） 的参加者为住在从山 $L_j$ 到山 $R_j$（包括 $L_j$ 和 $R_j$）上的人（$0\leq L_j\leq R_j\leq N-1$）。对于该会议，你必须选择某个山 $x$ 做为会议举办地（$L_j\leq x\leq R_j$）。举办该会议的成本与你的选择有关，其计算方式如下：

- 来自每座山 $y$（$L_j\leq y\leq R_j$） 的参会者的成本，等于在山 $x$ 和 $y$ 之间（包含 $x$ 和 $y$）的所有山的最大高度。特别地，来自山 $x$ 的参会者的成本是 $H_x$，也就是山 $x$ 的高度。

- 会议的成本等于其所有参会者的成本之和。

你想要用最低的成本来举办每个会议。

注意，所有的参会者将在每次会议后回到他们自己的山；所以一个会议的成本不会受到先前会议的影响。
## 输入格式

输入的第一行包含两个正整数 $N$ 和 $Q$，其意义见题目描述。

第二行包含 $N$ 个正整数 $H_0,H_1,\cdots, H_{N-1}$，表示这些山的高度。

第 $3+j$ 行（$0\leq j\leq Q-1$），每行两个整数 $L_j, R_j$，表示这些会议的参会者的范围。
## 输出格式

共 $Q$ 行，第 $1+j$ 行（$0\leq j\leq Q-1$）一个整数 $C_j$，表示举办会议 $j $ 的最低的可能成本。
## 样例

### 样例输入 #1
```
4 2
2 4 3 5
0 2
1 3

```
### 样例输出 #1
```
10
12

```
### 样例输入 #2
```
3 3
2 1 2
0 0
0 1
0 2

```
### 样例输出 #2
```
2
3
5

```
### 样例输入 #3
```
5 1
1000000000 1000000000 1 1000000000 1000000000
0 4

```
### 样例输出 #3
```
4000000001

```
### 样例输入 #4
```
15 10
10 71 84 33 6 47 23 25 52 64 70 31 22 31 2
5 10
3 7
0 13
8 12
0 0
1 3
7 13
1 13
10 12
1 1

```
### 样例输出 #4
```
281
180
828
263
10
201
364
744
123
71

```
## 提示

### 样例#1解释

会议$j=0$有$L_j=0$和$R_j=2$，所以将由住在山$0$、$1$和$2$上的人参加。如果山$0$被选做举办地，会议$0$的成本计算如下：

- 住在山$0$上的参会者的成本是$\max\lbrace H_0\rbrace=2$。
- 住在山$1$上的参会者的成本是$\max\lbrace H_0,H_1\rbrace=4$。
- 住在山$2$上的参会者的成本是$\max\lbrace H_0,H_1,H_2\rbrace=4$。
- 因此，会议$0$的成本是$2+4+4=10$。

不可能以更低的成本来举办会议$0$了，因此会议$0$的最低成本是$10$。

会议$j=1$有$L_j=1$和$R_j=3$，因此将由住在山$1$、$2$和$3$上的人参加。如果山$2$被选做举办地，会议$1$的成本计算如下：

- 住在山$1$上的参会者的成本是$\max\lbrace H_1,H_2\rbrace=4$。
- 住在山$2$上的参会者的成本是$\max\lbrace H_2\rbrace=3$。
- 住在山$3$上的参会者的成本是$\max\lbrace H_1,H_2,H_3\rbrace=5$。
- 因此，会议$1$的成本是$4+3+5=12$。

不可能以更低的成本来举办会议$1$了，所以会议$1$的最低成本是$12$。

### 限制条件

- $1\leq N\leq 750\space000$
- $1\leq Q\leq 750\space000$
- $1\leq H_i\leq1\space000\space000\space000$
- $0\leq L_j\leq R_j\leq R-1(0\leq j\leq Q-1)$
- $(L_j,R_j)\neq(L_k,R_k)(0\leq j<k\leq Q-1)$

### 子任务

1. (4分) $N\leq3000,Q\leq10$
2. (15分) $N\leq5000,Q\leq5000$
3. (17分) $N\leq100\space000,Q\leq100\space000,H_i\leq2(0\leq i\leq N-1)$
4. (24分) $N\leq100\space000,Q\leq100\space000,H_i\leq20(0\leq i\leq N-1)$
5. (40分) 没有附加限制

### Author

Riku Kawasaki (Japan)

### Source

IOI 2018 D2T3


---

---
title: "[IOI 2019] 景点划分"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5811
tag: ['2019', 'IOI', 'Special Judge']
---
# [IOI 2019] 景点划分
## 题目背景

# 滥用本题评测将封号

注：本题按照传统题方式进行评测，即，你的程序**需要包含 `main` 函数**。
## 题目描述

巴库有 $n$ 处景点，从 $0$ 到 $n-1$ 编号。另外还有 $m$ 条双向道路，从 $0$ 到 $m-1$ 编号。每条道路连接两个不同的景点。经由这些道路，可以在任意两处景点之间往来。

Fatima 打算在三天之内参观完所有这些景点。她已经决定要在第一天参观 $a$ 处景点，第二天参观 $b$ 处景点，第三天参观 $c$ 处景点。因此，她要将 $n$ 处景点划分为三个集合 $A$、$B$ 和 $C$，其规模分别为 $a$、$b$ 和 $c$。每处景点恰好属于其中一个集合，因此有 $a+b+c=n$。

Fatima 想要找到这样的景点划分 $A$、$B$ 和 $C$，使得这三个集合中的至少两个是联通的。一个景点集合 $S$ 被称为是联通的，如果能够经由这些道路在 $S$ 中的任意两处景点之间往来，且不需要经过不在 $S$ 中的景点。如果满足上述要求，则景点的一个划分 $A$、$B$ 和 $C$ 被称为是合法的。

请帮助 Fatima 找到一个合法的景点划分 （给定 $a$、$b$ 和 $c$），或者判断合法的划分不存在。如果存在多个合法的划分，你可以给出其中的任何一个。

**实现细节**

你需要实现下述函数：
`int [] find_split（int n,int a,int b,int c,int [] p,int [] q）`
- $n$：景点的数量。
- $a$、$b$ 和 $c$：集合$A$、$B$ 和 $C$ 的期望规模。
- $p$ 和 $q$：长度为 $m$ 的数组，包含道路的端点。对每个 $i$ （$ 0 \le i \le m-1 $），$p[i]$ 和 $q[i]$ 是由道路 $i$ 连接的两处景点。
- 该函数需要返回一个长度为 $n$ 的数组。记该数组为 $s$。如果不存在合法的划分，$s$ 应当包含 $n$ 个零。否则，对于 $0 \le i \le n-1$，$s[i]$ 应为 $1$、$2$ 或 $3$ 中的一个。以分别表示景点 $i$ 被归到集合 $A$、$B$ 或 $C$

## 输入格式

第一行，两个正整数 $n$、$m$。

第二行，三个正整数 $a$、$b$ 和 $c$。

第 $3+i$ 行 （对于 $ 0 \le i \le m-1 $） 两个正整数 $p[i]$、$q[i]$。

意义见题目描述
## 输出格式

共一行，内容为 `find_split` 所返回的数组。
## 样例

### 样例输入 #1
```
9 10
4 2 3
0 1
0 2
0 3
0 4
0 6
0 8
1 7
3 7
4 5
5 6

```
### 样例输出 #1
```
1 1 3 1 2 2 3 1 3

```
## 提示

**样例说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/sltz4zao.png)

一个可能解为 $[1,1,3,1,2,2,3,1,3]$。这个解刻画了这样的划分：$A=\{0,1,3,7\}$，$B=\{4,5\}$，$C=\{2,6,8\}$。集合 $A$ 和 $B$ 是联通的。

**数据范围**

对于 $100\%$ 的数据，
- $3 \le n \le 10^5$。
- $2 \le m \le 2 \times 10^5$。
- $1 \le a,b,c \le n$。
- $a+b+c=n$。
- 每一对景点之间至多有一条道路。
- 经由这些道路，可以在任何两处景点之间往来。
- 对于 $0 \le i \le m-1$，有 $0 \le p[i],q[i] \le n-1$ 和 $p[i] ≠ q[i] $。

**子任务**
1. （$7$ 分） 每处景点至多可做两条道路的端点。
2. （$11$ 分） $a=1$
3. （$22$ 分） $m=n-1$
4. （$24$ 分） $n \le 2500$，$m \le 5000$。
5. （$36$ 分） 没有任何附加限制。


---

---
title: "[IOI 2019] 天桥"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5812
tag: ['2019', 'IOI', 'Special Judge']
---
# [IOI 2019] 天桥
## 题目背景

# 滥用本题评测将封号

注：本题按照传统题方式进行评测，即，你的程序**需要包含 `main` 函数**。
## 题目描述

Kenan 为沿着巴库大街某一侧的建筑和天桥绘制了一张规划图。规划图中有 $n$ 栋建筑，从 $0$ 到 $n-1$ 编号。还有 $m$ 座天桥，从 $0$ 到 $m-1$ 编号。这张规划图绘制在一张二维平面上，其中建筑和天桥分别是垂直和水平的线段。

第 $i$（$0 \le i \le n-1$） 栋建筑的底部坐落在坐标 （$x[i],0$） 上，建筑的高度为 $h[i]$。因此，它对应一条连接点 （$x[i],0$） 和 （$x[i],h[i]$） 的线段。

第 $j$（$0 \le j \le m-1$） 座天桥的两端分别在第 $l[j]$ 栋建筑和第 $r[j]$ 栋建筑上，并具有正的 $y$ 坐标 $y[j]$。因此，它对应一条连接点 （$x[l[j]],y[j]$） 和 （$x[r[j]],y[j]$） 的线段。

称某座天桥和某栋建筑相交，如果它们有某个公共的点。因此，一座天桥在它的两个端点处与两栋建筑相交，同时还可能在中间和其他建筑相交。

Kenan 想要找出从第 $s$ 栋建筑的底部到第 $g$ 栋建筑的底部的最短路径长度，或者确认这样的路径不存在。在这里行人只能沿着建筑和天桥行走，并且不允许在地面上行走，也就是说不允许沿着 $y$ 坐标为 $0$ 的水平线行走。

行人能够在任意交点从某座天桥走进某栋建筑，或者从某栋建筑走上某座天桥。如果两座天桥的端点之一在同一点上，行人也可以从其中一座天桥走上另一座天桥。

你的任务是帮助 Kenan 回答他的问题。

**实现细节**

你需要实现下列函数。
`int64 min_distance(int[] x,int[] h,int[] l,int[] r,int[] y,int s,int g)`

- $x$ 和 $h$：长度为 $n$ 的整数数组。
- $l$、$r$ 和 $y$：长度为 $m$ 的整数数组。
- $s$ 和 $g$：两个整数。
- 如果从第 $s$ 栋建筑的底部到第 $g$ 栋建筑的底部的最短路径存在，则该函数应该返回最短路径的长度。否则，该函数应该返回`-1`。
## 输入格式

- 第 $1$ 行：$n$，$m$。
- 第 $2+i$ 行（$0 \le i \le n-1$）：$x[i]$，$h[i]$。
- 第 $n+2+j$ 行（$0 \le j \le m-1$）：$l[j]$，$r[j]$，$y[j]$。
- 第 $n+m+2$ 行：$s$，$g$。
## 输出格式

共一行，为函数 `min_distance` 的返回值。
## 样例

### 样例输入 #1
```
7 7
0 8
3 7
5 9
7 7
10 6
12 6
14 9
0 1 1
0 2 6
0 6 8
2 3 1
2 6 7
3 4 2
4 6 5
1 5
```
### 样例输出 #1
```
27

```
## 提示

**样例说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/t0lihb5c.png)

**限制条件**

- $1 \le n,m \le 10^5$。
- $0 \le x[0] < x[1] < \cdots < x[n-1] \le 10^9$。
- $1 \le h[i] \le 10^9$（对于所有 $0 \le i \le n-1$）。
- $0 \le l[j] \le r[j] \le n-1$（对于所有 $0 \le j \le m-1$）。
- $1 \le y[j] \le \min(h[l[j]],h[r[j]])$（对于所有 $0 \le j \le m-1$）。
- $0 \le s,g \le n-1$。
- $s ≠ g$。
- 除在端点处外，任意两座天桥不会有其他公共的点。

**子任务**

1. （$10$ 分）$n,m \le 50$。
2. （$14$ 分）每座天桥最多与 $10$ 栋建筑相交。
3. （$15$ 分）$s=0$，$g=n-1$，且所有建筑的高度相等。
4. （$18$ 分）$s=0$，$g=n-1$。
5. （$43$ 分）没有任何附加限制。


---

---
title: "[IOI 2015] teams"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5861
tag: ['2015', 'IOI']
---
# [IOI 2015] teams
## 题目描述

班里有 $N$ 个学生,他们的编号为从 $0$ 到 $N-1$。每天，老师都有一些项目需要学生去完成。每个项目都需要由一组学生在一天内完成。项目的难度可能不同。对于每个项目，老师知道应该选择由多少学生组成的小组去完成。

不同的学生对小组的规模有不同的喜好。更准确地说, 对学生 $i$ 而言, 他只愿意在小组规模介于 $A[i]$ 和 $B[i]$ 之间（含 $A[i]$ 和 $B[i]$）的小组工作。每一天，一个学生最多只能被分配到一个小组工作。有些学生可能未被分配到任何小组中。每个小组只负责一个项目。

老师已选择好接下来 $Q$ 天中每一天的项目。对于每一天, 现需要判断是否有一种分配学生的方案，使得每个项目都有一个小组负责。
## 输入格式

- 第 $1$ 行有一个正整数 $N$，表示班内学生的数量；
- 第 $2$ 到 $N+1$ 行有两个 $A[i]$，$B[i]$；
- 第 $N+2$ 行有一个正整数 $Q$；
- 第 $N+3$ 到 $N+Q+2$ 行，包含一个正整数 $M$，表示当天要完成的项目数， 后有一个长度为 $M$ 的序列 $K$。$K[i]$ （$1\le i\le M$） 表示项目 $i$ 所需的小组规模。
## 输出格式

共 $Q$ 行，对于每一个问题, 你的程序必须输出是否存在一种小组分配的方案，可以完成当天的所有项目。若可以完成分组去完成当天所有的项目，输出 `1`, 否则，应输出 `0`。
## 样例

### 样例输入 #1
```
4
2 4
1 2
2 3
2 3
2
2 1 3
2 1 1

```
### 样例输出 #1
```
1
0

```
## 提示

对于 $100\%$ 的数据，$1\le N\le 5 \times 10^5$，$1\le Q\le 2 \times 10^5$， $\sum M \leq 2\times 10^5$。


---

---
title: "[IOI 2016] aliens"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5896
tag: ['2016', 'IOI', 'Special Judge']
---
# [IOI 2016] aliens
## 题目描述

我们的卫星刚刚通过观测一个遥远的星球发现了外星文明。我们也已经获得了该星球的一个正方形区域的低分辨率照片。这个照片上有许多智能生命的迹象。专家们也已经确定了照片上的 $n$ 个兴趣点。这些兴趣点被编号为 $0$ 到 $n−1$。现在我们希望拍摄一些能包含全部 $n$ 个兴趣点的高分辨率照片。

卫星已将低分辨率照片的区域划分成由 $m \times m$ 个单位正方形的小方格组成的网络。网格的行和列被连续地编号为 $0$ 到 $m−1$（从上到下和从左到右）。我们用坐标 $(s,t)$ 来表示第 $s$ 行与第 $t$ 列上的小方格。第 $i$ 个兴趣点位于小方格 $(r_i,c_i)$ 上，每个小方格子上可以包含任意多个兴趣点。

卫星在一个固定的轨道上运行，而它刚好也直接经过这个网格的主对角线的上方。主对角线就是指在网络中连接左上角和右下角的那条线段。卫星能够在任意的区域上拍摄高分辨率的照片，但必须满足以下条件：

- 拍摄的区域必须是正方形。
- 这个正方形的两个对角（注：变通理解为主对角线）全部包含在网格的主对角线中。
- 网格中的每个小方格或者完全在拍摄范围内，或者完全在拍摄范围外。
卫星最多只能拍摄 $k$ 张高分辨率照片。

一旦卫星拍摄完成，它将把每个拍摄区域的高分辨率照片传送到地面基站（无论这些区域是否包含兴趣点）。尽管一个小方格可能会被多次拍摄，但每个被拍摄到的小方格上的数据只会被传送一次。

因此，我们必须选择最多 $k$ 个正方形区域进行拍摄，而且要保证：

- 每个包含至少一个兴趣点的小方格必须被至少拍摄到一次
- 被拍摄到至少一次的小方格数目必须是最小的。

你的任务就是去找出被拍摄到的小方格有可能的最小值。
## 输入格式

- 第 $1$ 行：整数 $n$ 代表兴趣点的数目，$m$ 代表网格中的行数（也是列数） 和 $k$ 代表卫星能够拍摄高分辨率照片的最大次数；
- 第 $2+i$ （$0 \le i \le n−1$） 行：整数 $r_i$ 和 $c_i$。$r$ 和 $c$ 为两个长度为 $n$ 的数组，描述网格中包含兴趣点的那些小方格的坐标。对于 $0\le i\le n−1$，第 $i$ 个兴趣点位于坐标为 $(r_i,c_i)$ 的小方格。
## 输出格式

- 共一行，被至少拍摄一次的小方格的总数的最小值（这些照片必须覆盖所有兴趣点）。
## 样例

### 样例输入 #1
```
5 7 2
0 3
4 4
4 6
4 5
4 6

```
### 样例输出 #1
```
25

```
### 样例输入 #2
```
2 6 2
1 4
4 1

```
### 样例输出 #2
```
16

```
## 提示

**子任务**

在全部子任务中， $1\le k\le n$。

| 子任务 | 分数 | $n\le$ | $m\le$ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $4$ | $5$ | $100$ |  $k=n$|
| $2$ | $12$ | $500$ | $10^3$ | $r_i=c_i$ |
|  $3$| $9$ | $500$ | $10^3$ | 无 |
|$4$  |$16$  | $4 \times 10^3$ | $10^6$ | 无 |
| $5$ | $19$ | $5\times 10^4$ | $10^6$ | $k \le 100$ |
| $6$ |  $40$| $10^5$ | $10^6$ | 无 |



---

---
title: "[IOI 2013] wombats"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5897
tag: ['2013', 'IOI', 'O2优化']
---
# [IOI 2013] wombats
## 题目描述

布里斯班被变异的袋熊占领，你必须带领大家去安全的地方。

布里斯班的道路像一个大网格，有 $R$ 条东西向的横向道路，从北向南依次编号为 $0,\cdots, (R - 1) $，有 $C$ 条南北向的纵向道路，从西向同东依次编号为 $0,\cdots, (C- 1)$ ，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/xyvkmhhp.png)

袋熊从北方入侵，人们逃向南方。人们可以在横向道路上双方向移动，但是在纵向道路上只能往南面安全的地方走。

横向道路 $P$ 和纵向道路 $Q$ 的交点表示为 $(P, Q)$ 。相邻 $2$ 个交点之间的道路线段上
有一些袋熊，且数目是随时间变化的。 你的任务是引导每个人从最北边（在横向道路 $0$ 上）的指定交点逃到最南端（在横向道路 $R - 1$ 上）的指定交点，路上经过
的袋熊最少。

首先会告诉你网格的规模以及每条道路线段上的袋熊的数量。然后给你一系列 $E$ 事件，每个事件是下列两者之一：
- 变化，表示有些道路线段上的袋熊数量发生变化；
- 逃离, 表示有些人已到达横向道路 $0$ 上指定交点，你必须给他们指出一条路，通往横向道路 $R - 1$ 上指定交点且路上遇到的袋熊最少。

**举例**

![](https://cdn.luogu.com.cn/upload/image_hosting/zn27laze.png)

上图所示的初始地图中有 $3$ 条横向道路 （$ R = 3$ ）和 $4$ 条纵向道路（$ C = 4$ ），每
条道路线段上的袋熊数目如线段上的标记所示。考虑下列事件：
- 一个人到达交点 $A = (0, 2)$ ,希望逃到交点 $B = (2, 1)$ 。如图上虚线所示，他最少需要经过 $2$ 只袋熊。
- 又一个人到达交点 $X = (0, 3)$ ，希望逃到交点 $Y = (2, 3)$ 。如图上虚线所示，他最少需要经过 $7$ 只袋熊。
- 发生 $2$ 个变化事件：纵向道路 $0$ 上最上面那条道路线段上的袋熊数目变为 $5 $，横向道路 $1$ 上中间那条道路线段上的袋熊数目变为 $6 $，见下图中圈出来的两个数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/agnx5ol9.png)

- 第3个人到达交点 $A = (0, 2)$ ，希望逃到交点 $B = (2, 1)$ ，现在他最少需要经过 $5$ 只袋熊，如图中虚线所示。
## 输入格式

- 第 $1$ 行： $R$ 表示横向道路的数目，$C$ 表示纵向道路的数目。
- 第 $2$ 行： $H[0][0],\cdots,H[0][C-2]$。
- $\cdots$
- 第 $(R + 1)$ 行： $H[R-1][0],\cdots,H[R-1][C-2]$。
- 第 $(R + 2)$ 行： $V[0][0],\cdots,V[0][C-1]$。
- $H$: 二维数组 $R × (C - 1)$ ，其中 $H[P][Q]$ 表示交点 $(P, Q)$ 和交点 $(P, Q +1)$ 之间的横向道路线段上的袋熊数目。
- $\cdots$
- 第 $(2R)$ 行： $V[R-2][0],\cdots,V[R-2][C-1]$。
- $V$: 二维数组 $(R - 1) × C$ ，其中 $V[P][Q]$ 表示交点 $(P, Q)$ 和交点 $(P + 1,Q)$ 之间的纵向道路线段上的袋熊数目。
- 下一行: $E$。
- 下 $E$ 行：每行一个事件，按照事件发生的顺序给出。

如果 $C = 1$ ，表示横向道路上每条道路线段上的袋熊数目的若干空行(第 $2$ 到 $R +1$ 行)将会被省略。

表示每个事件的那一行格式如下：

- `1 P Q W` 表示 将交点 $(P, Q)$ 和交点 $(P, Q + 1)$ 之间的横向道路线段上的袋熊数目改为 $W$。
- `2 P Q W` 表示 将交点 $(P, Q)$ 和交点 $(P + 1, Q)$ 之间的纵向道路线段上的袋熊数目改为 $W$。
- `3 V1 V2` 表示 计算一个人从交点 $(0, V1)$ 逃到交点 $(R-1, V2)$ 最少需要经过多少只袋熊。

例如：题目中的例子应该表示为以下格式

```
3 4
0 2 5
7 1 1
0 4 0
0 0 0 2
0 3 4 7
5
3 2 1
3 3 3
2 0 0 5
1 1 1 6
3 2 1

```
## 输出格式

对于每一次询问，给出最少经过袋熊数。
## 样例

### 样例输入 #1
```
3 4
0 2 5
7 1 1
0 4 0
0 0 0 2
0 3 4 7
5
3 2 1
3 3 3
2 0 0 5
1 1 1 6
3 2 1

```
### 样例输出 #1
```
2
7
5

```
## 提示

对于 $100\%$ 的数据，$2 \le R \le 5 \times 10^3$，$1 \le C \le 200$，最多 $500$ 个变化，最多 $2 \times 10^5$ 次询问，任意时刻一条道路上最多 $10^3$ 只袋熊。


---

---
title: "[IOI 2016] shortcut"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6167
tag: ['2016', 'IOI', 'Special Judge', 'O2优化']
---
# [IOI 2016] shortcut
## 题目描述

Pavel 有一个非常简单的铁路玩具。 它有一条含有 $n$ 个车站的主干线并且连续编号为 $0$ 到 $n-1$。车站 $0$ 和车站 $n-1$ 就在这条主干线的两端。其中车站 $i$ 和车站 $i+1$ 之间的距离为 $l_i$ 厘米（$ 0 \le i<n-1$）。

除了这条主干线之外，这个铁路也许会有些支线。每条支线都是由主干线中的一个车站和主干线 外的一个新车站之间的一条新铁路构成（这些新的车站不会被编号）。在主干线中的一个车站最多只能有一条支线。以主干线中的车站 $i$ 为起点的支线的长度为 $d_i$ 厘米。我们用 $d_i=0$ 来表示车站 $i$ 没有支线。

![](https://cdn.luogu.com.cn/upload/image_hosting/h21s6cjy.png)

Pavel 现正规划一条快捷方式：一条在主干线中两个不相同的车站之间（它们可能相邻）的快速干线。这条快速干线无论是连接哪两个车站，它的长度都将会恰好是 $c$ 厘米。

铁路中的每一段，包括那条新的快速干线，都能够双向行驶。任意两个车站的距离就是它们之间沿着铁路由一个车站到另一个车站之间最短路径的长度。所有车站组合中最大的距离就叫做整个铁路网络的直径。换句话说，存在一个最小值 $t$ 使任意两个车站之间的距离都不会超过 $t$。

Pavel 就是想建造一条快速干线，使得有了这条快速干线后新的铁路网络的直径能达到最小值。

### 样例一

```
4 10
10 20 20
0 40 0 30
```

最优解是在车站 $1$ 和车站 $3$ 之间建造一条快速干线，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/a31c6opk.png)

这个新铁路网络的直径是 $80$ 厘米，所以应该输出数值 $80$。

### 样例二

```
9 30
10 10 10 10 10 10 10 10
20 0 30 0 0 40 0 40 0
```

最优解是连接车站 $2$ 和车站 $7$，这个解的直径是 $110$。

### 样例三

```
4 1
2 2 2
1 10 10 1
```
最优解是连接车站 $1$ 和车站 $2$，这样直径将被缩短到 $21$。

### 样例四

```
3 3
1 1 
1 1 1
```
在任意两个车站中建立长度为 $3$ 的快速干线都不会改进整个铁路网络的直径，因此其直径仍为初始值 $4$。


## 输入格式

- 第一行：两个整数 $n$ 和 $c$，

- 第二行：整数 $l_0,l_1,\cdots,l_{n-2}$，

- 第三行：整数 $d_0,d_1,\cdots,d_{n-1}$。
## 输出格式

共一行，加入新快速干线后铁路网络直径的最小可能值。
## 样例

### 样例输入 #1
```
4 10
10 20 20
0 40 0 30

```
### 样例输出 #1
```
80

```
## 提示

对于 $100\%$ 的数据，$2\le n\le 10^6$，$1\le l_i\le 10^9$，$0\le d_i\le 10^9$，$1\le c\le 10^9$。




---

---
title: "[IOI 2000] 邮局 加强版 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6246
tag: ['2000', '二分', 'IOI', 'O2优化', '凸完全单调性（wqs 二分）', '栈']
---
# [IOI 2000] 邮局 加强版 加强版
## 题目背景

> 看到你时总是感觉清风徐徐,
>
> 本以为和你相识不会是偶遇,
>
> 奈何你犹如过客、化作秋雨,  
>
> 只是经过我生命的一瓢柳絮,
>
> 从不会真正有童话似的结局.
>
> 我静静地写尽这些躁言丑句,
> 
> 本以为可以稍稍地缓解抑郁.
>
> 却是徒增一场悲伤的脑补剧.
>
> 你问我为什么说这么多?
>
> 因为这题是加强版的 [IOI2000]邮局.
## 题目描述

高速公路旁边有 $n$ 个村庄。高速公路表示为整数轴，每个村庄的位置用单个整数坐标标识。两个位置之间的距离是其整数坐标差的绝对值。

现在要建立  $m$ 个邮局，邮局将建在一些，但不一定是所有的村庄中。为了建立邮局，应选择他们建造的位置，使每个村庄与其最近的邮局之间的距离总和最小。

你要编写一个程序，已知村庄的位置和邮局的数量，计算每个村庄和最近的邮局之间所有距离的最小可能的总和。
## 输入格式

第一行包含两个整数，分别表示村庄的数量 $n$ 和邮局的数量 $m$。

第二行共 $n$ 个整数，表示每个村庄的坐标，第 $i$ 个整数表示第 $i$ 个村庄的坐标 $a_i$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 2
0 1 2 3 4
```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

本题共五个测试点，各测试点信息如下：

| 测试点编号 | $n = $ | $a_i \leq $ |
| :----------: | :-------: | :----: |
| 1 | $50000$ | $6 \times 10^4$ |
| 2 | $150000$ | $2 \times 10^5$ |
| 3 | $299998$ | $5 \times 10^5$ |
| 4 | $499998$ | $10^6$ |
| 5 | $499999$ | $2\times 10^6$ |

对于全部的测试点，保证 $1 \leq m \leq n \leq 5 \times 10^5$，$0 \leq a_i \leq 2\times 10^6$，且 $a_i$ 的值在对应范围内均匀随机。

保证最终答案不超过 $10^9$。



---

---
title: "[IOI 2020] 植物比较"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6829
tag: ['2020', '线段树', '倍增', 'IOI', '交互题']
---
# [IOI 2020] 植物比较
## 题目背景

**这是一道交互题**。

本题仅支持 C++ 系列语言，提交时不需要包含 `plant.h` 头文件。
## 题目描述

植物学家 Hazel 参观过新加坡植物园的一个特别展览。在这次展览中，有 $n$ 棵 **高度互不相同** 的植物，它们排成了一个圆。这些植物按顺时针方向从 $0$ 到 $n-1$ 编号，植物 $n-1 $ 与植物 $0$ 是相邻的。

对于每棵植物 $i\ (0 \le i \le n-1$)，Hazel 将它与顺时针方向的后 $k-1$ 棵植物进行比较，记录下数值 $r[i]$ 以表示这 $k-1$ 棵植物中有多少棵的高度大于植物 $i$。因此，每个 $r[i]$ 的数值是由某段连续 $k$ 棵植物的相对高度决定的。

例如，假设 $n=5$，$k=3$，$i=3$。植物 $3$ 顺时针方向的后 $k-1=2$ 棵植物是植物 $4$ 和植物 $0$。如果植物 $4$ 比植物 $3$ 高，且植物 $0$ 比植物 $3$ 矮，那么 Hazel 将会记录 $r[3]=1$。

你可以假设 Hazel 记录的数值 $r[i]$ 都是正确的。也就是说，这些植物至少存在一组互不相同的高度符合 Hazel 所记录的数值。

本题要求你比较 $q$ 对植物的高度。由于你没有机会参观这次展览，你仅有的信息来源是 Hazel 的笔记本，其中记录了 $k$ 和序列 $r[0],\ldots, r[n-1]$ 的值。

对于每对需要比较的植物 $x$ 和 $y$（$x$ 和 $y$ 不同），判定它们符合以下哪种情况：

- 植物 $x$ 一定比植物 $y$ 高：对于任意一组符合数组 $r$ 且互不相同的高度 $h[0],\ldots h[n-1]$，都有 $h[x] > h[y]$。
- 植物 $x$ 一定比植物 $y$ 矮：对于任意一组符合数组 $r$ 且互不相同的高度 $h[0],\ldots h[n-1]$，都有 $h[x]<h[y]$。
- 该比较没有定论：以上两种情况都不成立。

#### 实现细节

要求你实现以下函数：
```cpp
void init(int k, std::vector<int> r)
```
- $k$：决定每个 $r[i]$ 数值的连续植物的棵数。
- $r$：一个大小为 $n$ 的数组，其中 $r[i]$ 是植物 $i$ 顺时针方向的后 $k-1$ 棵植物中比它高的棵数。
- 该函数恰好被调用一次，且在对 `compare_plants` 的任何调用前。
```cpp
int compare_plants(int x, int y)
```
- $x,y$ ：待比较的植物的编号。
- 该函数应该返回：
	- $1$，如果植物 $x$ 一定比植物 $y$ 高，
	- $-1$，如果植物 $x$ 一定比植物 $y$ 矮，
	- $0$，如果该比较没有定论。
- 该函数恰好被调用 $q$ 次。
## 提示

#### 样例说明

#### 例 1

考虑以下调用：
```cpp
init(3, [0, 1, 1, 2])
```
假设评测程序调用了 `compare_plants(0, 2)`。由 $r[0]=0$ 可以推断植物 $2$ 不比植物 $0$ 高，因此该调用应该返回 $1$。

假设评测程序接下来调用了 `compare_plants(1, 2)`。由于对每组符合以上条件的植物高度，都有植物 $1$ 比物 $2$ 矮，因此该调用应该返回 $-1$。

#### 例 2

考虑以下调用：
```cpp
init(2, [0, 1, 0, 1])
```
假设评测程序调用了 `compare_plants(0, 3)`。由 $r[3]=1$ 可以推断植物 $0$ 比植物 $3$ 高，因此该调用应该返回 $1$。

假设评测程序接下来调用了 `compare_plants(1, 3)`。两组高度 $[3,1,4,2]$ 和 $[3,2,4,1]$ 都符合 Hazel 的观测记录，由于在第一种情况中植物 $1$ 比植物 $3$ 矮，而在第二种情况中它比植物 $3$ 高，因此该调用应该返回 $0$。

#### 约束条件

- $2\le k\le n\le 200\ 000$
- $1\le q\le 200\ 000$
- $0 \le r[i]\le k-1$（对所有 $0 \le i \le n-1$）
- $0\le x<y\le n-1$
- 存在一组或多组 **互不相同的高度** 符合数组 $r$ 记录的情况

#### 子任务

1. （5 分）$k=2$
2. （14 分）$n \le 5000,2 \cdot k > n$
3. （13 分）$2 \cdot k > n$
4. （17 分）每次 `compare_plants` 调用的正确答案是 $1$ 或 $-1$
5. （11 分）$n\le 300, q\le \frac{n\cdot (n-1)}{2}$
6. （15 分）每次调用 `compare_plants` 时有 $x=0$
7. （25 分）没有附加约束条件

#### 评测程序示例

评测程序示例以如下格式读取输⼊数据：

第 $1$ 行：$n\ k\ q$     
第 $2$ 行：$r[0]\ r[1]\ \cdots\ r[n-1]$        
第 $3+i\ (0\le i\le q-1)$ 行：$x\ y$，表⽰第 $i$ 次调用 `compare_plants` 时的参数

评测程序示例以如下格式打印你的答案：

第 $1+i\ (0\le i\le q-1)$ 行：第 $i$ 次调用 `compare_plants` 的返回值


---

---
title: "[IOI 2020] 数蘑菇"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6837
tag: ['2020', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2020] 数蘑菇
## 题目描述

研究蘑菇的专家安德鲁在研究新加坡的本地蘑菇。

作为研究的一部分，安德鲁采集了 $n$ 个蘑菇，编号为 $0$ 到 $n-1$。每个蘑菇均为两种蘑菇种类之⼀，称为 $A$ 或 $B$。

安德鲁知道 **蘑菇 $0$ 属于种类 $A$**, 但是由于这两种蘑菇看起来很相似，他不知道蘑菇 $1$ 到 $n-1$ 属于哪一种。

幸运的是，安德鲁的实验室里有一台机器可以帮助他。在使用这台机器时，需要将两个或者多个蘑菇放到机器里，并摆成一排（以任意顺序），然后打开机器。接下来，这台机器会计算所有不属于同一种类的 **相邻** 蘑菇对的个数。例如，如果你把种类为 $[A,B,B,A]$ 的蘑菇（按照这个顺序）放到机器中，结果应该是 $2$。

但是，因为机器操作非常昂贵，机器只能使用有限的次数。此外，在机器的所有使用中，放置到机器中的蘑菇总数不能超过 $10^5$。请使用这台机器帮助安德鲁来数一数他采集了多少个种类为 $A$ 的蘑菇。

#### 实现细节

你需要实现以下函数：

```cpp
int count_mushrooms(int n)
```

- $n$: 安德鲁采集到的蘑菇数量。
- 该函数应该被调用恰好一次，而且要返回种类为 $A$ 的蘑菇的个数。

以上函数可以调用以下函数：

```cpp
int use_machine(int[] x)
```

- $x$: 一个长度介于 $2$ 和 $n$ 的数组（包括 $2$ 和 $n$)，按顺序给出放在机器中的蘑菇的编号。
- $x$ 的元素必须是在 $0$ 到 $n-1$ 之间（包括 $0$ 和 $n-1$) **互不相同** 的整数。
- 假设数组 $x$ 的长度为 $d$。那么，此函数返回不同的下标 $j$ 的个数，满足 $0 \le j \le d-2$ 并且 $x[j]$ 和 $x[j+1]$ 属于不同种类。
- 该函数最多可以被调用 $2 \times 10^4$ 次。
- 在对函数 `use_machine` 的所有调用中，所有被传到该函数 `use_machine` 的 $x$ 的总长度不能超过 $10^5$。
## 提示

#### 样例说明

#### 例 1

考虑以下场景：有 $3$ 个蘑菇，种类依次为 $[A,B,B]$。函数 `count_mushrooms` 用以下方式调用

```cpp
count_mushrooms(3)
```

该函数可以调用 `use_machine([0, 1, 2])`，在该场景下调用返回 $1$。 函数接着调用 `use_machine([2, 1])`，该调用返回 $0$。

此时，已经有足够的信息来推出只有 $1$ 个 $A$ 类蘑菇。所以，函数 `count_mushrooms` 应该返回 $1$。

#### 例 2

考虑一个例子：有 $4$ 个蘑菇，种类依次为 $[A,B,A,A]$。函数 `count_mushrooms` 被调用如下：
```cpp
count_mushrooms(4)
```

该函数可以调用 `use_machine([0, 2, 1, 3])`，该调用返回 $2$。接着调用 `use_machine([1,2])`，该调用返回 $1$。

此时，已有足够的信息推出：有 $3$ 个 $A$ 类蘑菇。因此，函数 `count_mushrooms` 应该返回 $3$。

#### 约束条件

- $2 \le n \le 2 \times 10^4$

#### 计分

在所有测试用例中，如果对函数 `use_machine` 的调用不符合上面所述的要求，或者 `count_mushrooms` 的返回值不正确，你的解答得分将为 $0$。否则，令 $Q$ 为所有测试样例中对函数 `use_machine` 的最大调用次数。那么，得分将按照以下表格进行计算：

|条件|得分|
|:-:|:-:|
|$2 \times 10^4 \le Q$|$0$|
|$10010 < Q \le 2 \times 10^4$|$10$|
|$904 < Q \le 10010$|$25$|
|$226 < Q \le 904$|$\frac{226}{Q} \cdot 100$|
|$Q \le 226$|$100$|

在有些测试用例上，评测程序的行为是自适应的。也就是说，在这些测试用例中，评测程序并没有一个固定的蘑菇种类序列。相反，评测程序中所给出的回答可能依赖于此前对 `use_machine` 的调用。

但是可以保证，评测程序中所给出的回答满足：在每次交互之后，至少存在一个蘑菇种类序列，它能够与当前所给出过的所有回答都相符。

#### 评测程序示例

评测程序示例读入一个整数数组 $s$，该数组给出了蘑菇的种类。对于所有 $0 \le i \le n-1$，$s[i]=0$ 表示蘑菇 $i$ 的种类是 $A$，$s[i]=1$ 表示蘑菇 $i$ 的种类是 $B$。评测程序示例读取如下格式的输入数据：

第 $1$ 行: $n$       
第 $2$ 行: $s[0]\ s[1]\ \ldots\ s[n-1]$

评测程序示例的输出为如下格式：

第 $1$ 行: `count_mushrooms` 的返回值。     
第 $2$ 行: 调用 `use_machine` 的次数。

注意评测程序示例不是自适应的。


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
title: "[IOI 2019] 折线"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7195
tag: ['2019', 'IOI', '提交答案', 'Special Judge']
---
# [IOI 2019] 折线
## 题目背景

您可以在此处下载[输入文件](https://cowtransfer.com/s/9b9c30ef6dc74d)。
## 题目描述

阿塞拜疆因地毯而闻名。作为一位地毯设计大师，你在做新设计时想画一条**折线**。一条折线是二维平面上包含 $t$ 条线段的线段序列，而这些线段由包含 $t+1$ 个点 $p_0,\ldots,p_t$ 的点序列按照下述规则定义给出：对所有的 $0\le j\le t- 1$，都有一条线段连接点 $p_j$ 和 $p_{j+1}$。

为完成这个新设计，你已经标出了二维平面中的 $n$ 个**小圆点**。小圆点 $i$（$1 < i < n$）的坐标为 $(x_i,y_i)$。**不存在 $x$ 坐标或 $y$ 坐标相同的两个小圆点**。

现在你想要找到一个点序列 $(sx_0,sy_0),(sx_1, sy_1)\ldots (sx_k, sy_k)$，由该点序列定义给出的折线需满足：
- 该折线从 $(0,0)$ 开始（即 $sx_0=0$ 且 $sy_0=0$），
- 该折线经过所有的小圆点（它们不必是线段的端点），以及
- 该折线仅包括水平线段和竖直线段（对于定义该折线的连续两个点，其 $x$ 坐标或 $y$ 坐标相等）。

折线可以以任意的方式自相交或自重叠。正式地来说，平面上的每个点可以属于折线中任意数量的线段。

本题是一个有部分分的提交答案型题目。将会给你 $10$ 个输入文件， 这些文件给出了小圆点的位置。对每个输入文件，你需要提交一个答案文件，描述满足要求的折线。对每个给出合法折线的输出文件，你的得分将依赖于折线中的**线段数量**（参见下面的计分方式一节）。

你不需要为本题提交任何源代码。
## 输入格式

每个输入文件的格式如下：
- 第 $1$ 行：$n$。
- 第 $1+i$ 行（这里 $1<i\le n$）：$x_i\ y_i$。
## 输出格式

每个输出文件必须按照如下格式：
- 第 $1$ 行： $k$。
- 第 $1+j$ 行（这里 $1\le j\le k$）： $sx_j\ sy_j$。

注意，第二行应包含 $sx_1$ 和 $sy_1$ （也就是说，输出**不应当**包含 $sx_0$ 和 $sy_0$）。所有的 $sx_j$ 和 $sy_j$ 均应为整数。
## 样例

### 样例输入 #1
```
4
2 1 
3 3
4 4
5 2
```
### 样例输出 #1
```
6
2 0
2 3
5 3
5 2
4 2
4 4
```
## 提示


#### 样例解释
这个样例并不是任何一个数据，仅仅只是为了帮助您理解题意。

输出也仅仅是一个可能的输出。

![](https://cdn.luogu.com.cn/upload/image_hosting/6deg8n18.png)

#### 限制条件
- $1\le n\le 10^5$。
- $1\le x_i,y_i\le 10^9$。
- 所有 $x_i$ 和 $y_i$ 的值都是整数。
- 不存在 $x$ 坐标或 $y$ 坐标相同的两个小圆点，也就是说，对于所有的 $i_1\not=i_2$，都有 $x_{i_1}\not=x_{i_2}$ 且 $y_{i_1}\not=y_{i_2}$。
- $-2\times 10^9\le sx_i,sy_j\le 2\times 10^9$。
- 提交的每个文件（无论是输出文件还是压缩文件）的大小均不能超过 $\text{15MB}$。

#### 计分方式
对每个测试点，你最多能够得到 $10$ 分，如果给出一条非法的折线，你将得到 $0$ 分。否则，得分将根据一个递减序列 $c_1, \cdots, c_{10}$ 来计算。

假设你的解答是一条包含 $k$ 条线段的合法折线。那么，你将得到
- $i$ 分，如果 $k=c_i$（$1 \le i \le 10$）
- $i+\dfrac{c_i-k}{c_i-c_{i+1}}$ 分，如果 $c_{i+1} < k < c_i$（$1 \le i \le 9$）
- $0$ 分，如果 $k > c_1$
- $10$ 分，如果 $k < c_{10}$。

可以这样理解：在 $k \in (c_{i+1}, c_i)$ 这个区间上，你的得分是随着 $k$ 减小线性增大的。一旦得分，得分一定在 $[1, 10]$ 区间内。

以下是每个测试点 $n$ 与 $c_i$ 的信息：

|测试点|$n$|$c_1$|$c_2$|$c_3$|$c_4$|$c_5$|$c_6$|$c_7$|$c_8$|$c_9$|$c_{10}$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$50$|$45$|$40$|$37$|$35$|$33$|$28$|$26$|$25$|$23$|
|$2$|$600$|$1\ 200$|$937$|$674$|$651$|$640$|$628$|$616$|$610$|$607$|$603$|
|$3$|$5\ 000$|$10\ 000$|$7\ 607$|$5\ 213$|$5\ 125$|$5\ 081$|$5\ 037$|$5\ 020$|$5\ 012$|$5\ 008$|$5\ 003$|
|$4$|$50\ 000$|$100 \ 000$|$75\ 336$|$50\ 671$|$50\ 359$|$50\ 203$|$50\ 047$|$50\ 025$|$50\ 014$|$50\ 009$|$50\ 003$|
|$5$|$72\ 018$|$144\ 036$|$108\ 430$|$72\ 824$|$72\ 446$|$72\ 257$|$72\ 067$|$72\ 044$|$72\ 033$|$72\ 027$|$72\ 021$|
|$6$|$91\ 891$|$183\ 782$|$138\ 292$|$92\ 801$|$92\ 371$|$92\ 156$|$91\ 941$|$91\ 918$|$91\ 906$|$91\ 900$|$91\ 894$|
|$7$|$100\ 000$|$200\ 000$|$150\ 475$|$100\ 949$|$100\ 500$|$100\ 275$|$100\ 050$|$100\ 027$|$100\ 015$|$100\ 009$|$100\ 003$|

#### 可视化工具
在本题的附加文件中有一个脚本，能让你对输入文件和输出文件进行可视化。

在对输入文件做可视化时，使用如下命令：
```plain
python vis.py [input file]
```

对于某个输入数据，你还可以使用下面的命令对你的解答进行可视化，由于技术方面的限制，所提供的可视化工具仅显示输出文件中的**前 $1000$ 条线段**。
```plain
python vis.py [input file] --solution [output file]
```

例如：
```plain
python vis.py examples/00.in --solution examples/00.out
```


---

---
title: "[IOI 2022] 囚徒挑战"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8491
tag: ['2022', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2022] 囚徒挑战
## 题目背景

# 滥用评测资源者封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 main 函数。

原题时间限制 1s，为了节约评测资源，时间限制修改为 0.5s
## 题目描述

一个监狱里关着 $500$ 名囚徒。
有一天，监狱长给了他们一个重获自由的机会。
他把装钱的两个袋子 A 和 B 放在一个房间里。
每个袋子装有若干枚硬币，数量的范围在 $1$ 到 $N$ 之间（包含 $1$ 和 $N$）。
两个袋子里硬币的数量**不同**。
监狱长给囚徒们提出了挑战，目标是指出硬币数量较少的那个袋子。

房间里除了袋子还有一块白板。
任意时刻白板上写着一个数，一开始写的是 $0$。

监狱长让囚徒一个接一个地进入房间。
每个进入房间的囚徒不知道他之前进入过房间的囚徒有多少人，也不知道是哪些人。
每次一个囚徒进入房间时，他看一眼白板上目前写的这个数。
看完之后，他必须在袋子 A 和 B 之间做出选择。
接着，他**检查**自己选的那个袋子，知道了里面有多少枚硬币。
然后，这名囚徒必须选择做以下两种**行动**之一：

* 将白板上的数改写成一个非负整数，并离开房间。
注意他可以改变成新的数，也可以保留当前的数。
然后挑战继续进行（除非所有 $500$ 名囚徒都已经进过房间）。
* 指出硬币数量较少的那个袋子。这会立即结束挑战。

对于已经进过房间的囚徒，监狱长不会让他再次进入房间。

如果某个囚徒正确地指出硬币较少的袋子，则囚徒们获得挑战的胜利。
如果指出的袋子不正确，或者所有 $500$ 人进过房间之后还没有人尝试指出硬币较少的袋子，则囚徒们失败。

挑战开始之前，囚徒们集合在监狱大厅商量应对挑战的共同**策略**，分以下三个步骤：
* 他们挑选一个非负整数 $x$，作为他们可能会写在白板上的最大的数。
* 他们决定对任意一个数 $i$ ($0 \le i \le x$)，如果某个囚徒进入房间后看到白板上写着数 $i$，那么他应该去检查哪个袋子。
* 他们决定当某个囚徒得知选中的袋子里的硬币数量后要采取的行动。具体来说，对任意写在白板上的数 $i$ ($0 \le i \le x$) 和检查选中的袋子里的硬币数量 $j$ ($1 \le j \le N$)，他们要决定做出以下两种行动之一：
  - 白板上应该要写一个 $0$ 到 $x$ 之间（包含 $0$ 和 $x$）的什么数；
  - 指出哪个袋子是硬币较少的。

如果赢得挑战，监狱长会在囚徒们继续服刑 $x$ 天后释放他们。

你的任务是提出能够确保囚徒们赢得挑战的策略（不管袋子 A 和 B 中的硬币数量是多少）。
你的得分取决于 $x$ 的值（详见子任务一节）。
## 输入格式

你要实现以下函数：

```go
int[][] devise_strategy(int N)
```

- $N$：每个袋子里硬币最多可能的数量。
- 该函数需要返回一个数组 $s$，它的每个元素是长度为 $N + 1$ 的整数数组，表示你给出的策略。$x$ 的值是数组 $s$ 的长度减一。对满足 $0 \le i \le x$ 的每个 $i$，数组 $s_i$ 表示囚徒在进入房间看到白板上写着数 $i$ 时要做的事情：
  1. 如果囚徒应该检查袋子 A，则 $s_{i, 0}$ 的值是 $0$；如果囚徒应该检查袋子 B，则该值是 $1$。
  2. 令 $j$ 为所选袋子中的硬币数量，囚徒应该进行以下行动：
     - 如果 $s_{i, j}$ 的值是 $-1$，则囚徒应该指出袋子 A 是硬币较少的袋子。
     - 如果 $s_{i, j}$ 的值是 $-2$，则囚徒应该指出袋子 B 是硬币较少的袋子。
     - 如果 $s_{i, j}$ 的值是非负整数，则囚徒应该把这个数写到白板上。注意 $s_{i, j}$ 至多只能是 $x$。
- 该函数恰好被调用一次。
## 输出格式

考虑以下调⽤：

```go
devise_strategy(3)
```

令 $v$ 表示囚徒进入房间时看到白板上写着的数。以下是一种正确的策略：

- 如果 $v = 0$（也包括开始时的数），则检查袋子 A。
  - 如果它装了 $1$ 个硬币，则指出袋子 A 是硬币较少的袋子。
  - 如果它装了 $3$ 个硬币，则指出袋子 B 是硬币较少的袋子。
  - 如果它装了 $2$ 个硬币，则在白板上写上 $1$（覆盖之前的 $0$）。
- 如果 $v = 1$，则检查袋子 B。
  - 如果它装了 $1$ 个硬币，则指出袋子 B 是硬币较少的袋子。
  - 如果它装了 $3$ 个硬币，则指出袋子 A 是硬币较少的袋子。
  - 如果它装了 $2$ 个硬币，则在白板上写上 $0$（覆盖之前的 $1$）。注意，这种情况其实不可能发生，因为此时两个袋子都装有 $2$ 枚硬币，是不允许的。

要产生以上策略，函数应该返回 `[[0, -1, 1, -2], [1, -2, 0, -1]]`。
返回的数组长度是 $2$，此时 $x$ 的值是 $2 - 1 = 1$。
## 提示

### 约束条件

- $2 \leq N \leq 5000$。

### 子任务

1. （5 分）$N \le 500$，$x$ 的值不能超过 $500$。
1. （5 分）$N \le 500$，$x$ 的值不能超过 $70$。
1. （90分）$x$ 的值不能超过 $60$。

对于任何测试用例，如果 `devise_strategy` 返回的数组是不合法的，则你在该子任务上的得分为 $0$。

子任务 3 有部分分。
令 $m$ 为该子任务中所有测试用例返回数组对应的 $x$ 的最大值，你的得分将根据下表计算：

| 条件 | 得分 |
| :-: | :-: |
| $40 \leq m \leq 60$ | $20$ |
| $26 \leq m \leq 39$ | $25 + 1.5 \times (40 − m)$ |
| $m = 25$ | $50$ |
| $m = 24$ | $55$ |
| $m = 23$ | $62$ |
| $m = 22$ | $70$ |
| $m = 21$ | $80$ |
| $m \leq 20$ | $90$ |

### 评测程序示例

评测程序示例按以下格式读取输入：

* 第 $1$ 行：$N$
* 第 $2 + k$ 行 ($0 \le k$)：$A_k \; B_k$
* 最后一行：$-1$

除第一行和最后一行外，每行表示一个场景。
将第 $2 + k$ 行对应的场景称为场景 $k$。
场景 $k$ 中，袋子 A 装有 $A[k]$ 枚硬币，袋子 B 装有 $B[k]$ 枚硬币。

评测程序示例首先调用 `devise_strategy(N)`。
$x$ 的值是返回数组的长度减一。
如果评测程序示例检测到 `devise_strategy` 返回的数组不符合实现细节中描述的约束，它会打印如下错误信息并退出：

* `s is an empty array`：$s$ 是空的数组（表示不合法的策略）。
* `s[i] contains incorrect length`：存在一个下标 $i$ ($0 \le i \le x$) 满足 $s_i$ 的长度不是 $N + 1$。
* `First element of s[i] is non-binary`：存在一个下标 $i$ ($0 \le i \le x$) 满足 $s_{i,0}$ 既不是 $0$，也不是$1$。
* `s[i][j] contains incorrect value`：存在下标 $i, j$ ($0 \le i \le x, 1 \le j \le N$) 满足 $s_{i, j}$ 的值不在 $-2$ 和 $x$ 之间。

否则，评测程序示例产生两项输出内容。

首先，评测程序示例以如下格式打印你的策略的输出：

* 第 $1 + k$ 行 ($0 \le k$)：场景 $k$ 下你的策略的输出。
如果用该策略导致某个囚徒指出袋子 A 是硬币较少的，则输出字符 `A`。
如果用该策略导致某个囚徒指出袋子 B 是硬币较少的，则输出字符 `B`。
如果用该策略后没有囚徒指出哪个袋子的硬币较少，则输出字符 `X`。

其次，评测程序示例以如下格式在当前目录下写一个文件 `log.txt`：

* 第 $1 + k$ 行 ($0 \le k$)：$w_{k,0} \; w_{k,1} \; \ldots$

第 $1 + k$ 行的序列对应于场景 $k$，描述了写在白板上的数。
具体来说，$w[k][l]$ 是第 $l + 1$ 个囚徒进入房间后写的数。

### 约定

题面在给出函数接口时，会使用一般性的类型名称 `void`、`int`、`int64`、`int[]`（数组）和 `int[][]`（数组的数组）。

在 C++ 中，评测程序会采用适当的数据类型或实现，如下表所示：

| `void ` | `int` | `int64`     | `int[]`            |
| ------- | ----- | ----------- | ------------------ |
| `void ` | `int` | `long long` | `std::vector<int>` |

| `int[][]`                       | 数组 `a` 的长度 |
| ------------------------------- | ------------------- |
| `std::vector<std::vector<int>>` | `a.size()`          |



---

---
title: "[IOI 2022] 无线电信号塔"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8492
tag: ['2022', 'IOI', '交互题']
---
# [IOI 2022] 无线电信号塔
## 题目背景

# 滥用评测资源者封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 main 函数。

由于本题数据点过多，结合洛谷评测技术实现情况，本题将以 ACM mode 进行评分。
## 题目描述

雅加达有 $N$ 个无线电信号塔。这些信号塔排布成一条直线，并且从左到右依次编号为从 $0$ 到 $N - 1$。
对于每个满足 $0 \le i \le N - 1$ 的 $i$，信号塔 $i$ 的高度为 $H_i$ 米。
所有塔的高度都是**不同的**。

对于某个为正数的信号干扰参数 $\delta$，一对信号塔 $i$ 和 $j$ ($0 \le i \lt j \le N - 1$) 之间能够互相通信，当且仅当存在一个中间信号塔 $k$ 满足如下条件：

* 塔 $i$ 在塔 $k$ 的左边，并且塔 $j$ 在塔 $k$ 的右边，即 $i \lt k \lt j$；
* 塔 $i$ 和塔 $j$ 的高度都至多为 $H[k] - \delta$ 米。

Pak Dengklek 想租一些信号塔来组建他的新无线电网络。
你的任务是回答 Pak Dengklek 提出的 $Q$ 个询问。这些询问的形式如下：
给定参数 $L, R$ 和 $D$ ($0 \le L \le R \le N - 1$ 且 $D > 0$)，在满足下述所有条件时，Pak Dengklek 最多能够租多少个信号塔：

 * Pak Dengklek 只能租编号在 $L$ 和 $R$ 之间的信号塔（包括 $L$和 $R$）；
 * 信号干扰参数 $\delta$ 的值为 $D$；
 * Pak Dengklek 租的信号塔两两之间必须能够进行通信。

注意，无论中间信号塔 $k$ 是否被租，两个已租的信号塔都可以借助信号塔 $k$ 进行通信。
## 输入格式

你需要实现以下函数：

```go
void init(int N, int[] H)
```

* $N$： 信号塔的数量。
* $H$： 一个长度为 $N$ 的数组，给出信号塔的高度。
* 这个函数恰好被调用一次，且在函数 `max_towers` 的所有调用之前。

```go
int max_towers(int L, int R, int D)
```

* $L$, $R$：信号塔编号区间的边界。
* $D$：信号干扰参数 $\delta$ 的值。
* 该函数应返回 Pak Dengklek 最多能租的信号塔数量（用于组建信号网络），这里 Pak Dengklek 只能租 $L$ 和 $R$之间（包含 $L$ 和 $R$）的信号塔，且信号干扰参数 $\delta$ 的值是 $D$。
* 该函数将被调用恰好 $Q$ 次。
## 输出格式

考虑如下函数调⽤序列：

```go
init(7, [10, 20, 60, 40, 50, 30, 70])
```

```go
max_towers(1, 5, 10)
```

Pak Dengklek 可以租编号为 $1$, $3$ 和 $5$ 的信号塔。
下面给出了这个例子的示意图，其中的灰色梯形表示被租的信号塔。

![](https://img.loj.ac.cn/2022/08/10/a52f5b077031b.png)

信号塔 $3$ 和 $5$ 可以借助信号塔 $4$ 进行通信，这是因为 $40 \le 50 - 10$ 且 $30 \le 50 - 10$。
信号塔 $1$ 和 $3$ 可以借助信号塔 $2$ 进行通信。
信号塔 $1$ 和 $5$ 可以借助信号塔 $3$ 进行通信。
无法租超过 $3$ 个信号塔，因此函数应返回 $3$。

```go
max_towers(2, 2, 100)
```

在这个区间里只有 $1$ 个信号塔，所以 Pak Dengklek 只能租借 $1$ 个信号塔。
因此函数应返回 $1$。

```go
max_towers(0, 6, 17)
```

Pak Dengklek 可以租信号塔$1$ 和 $3$ 。
信号塔  $1$ 和 $3$ 可以借助信号塔 $2$进行通信，这是因为 $20 \le 60 - 17$ 且 $40 \le 60 - 17$。
无法租赁超过 $2$ 个信号塔，因此函数应返回 $2$。
## 提示

### 约束条件

* $1 \le N \le 100\;000$
* $1 \le Q \le 100\;000$
* $1 \le H_i \le 10^9$ (对于所有满足 $0 \le i \le N - 1$ 的 $i$ )
* $H_i \ne H_j$ (对于所有满足 $0 \le i \lt j \le N - 1$  的 $i$ 和 $j$ )
* $0 \le L \le R \le N - 1$
* $1 \le D \le 10^9$

### 子任务

1. (4 分) 存在一个满足下述所有条件的信号塔 $k$ ($0 \le k \le N - 1$) 
   * 对于 $0 \le i \le k - 1$ 的每个 $i$：$H_i \lt H_{i + 1}$ 
   * 对于 $k \le i \le N - 2$ 的每个 $i$：$H_i \gt H_{i + 1}$ 
2. (11 分) $Q = 1$，$N \le 2000$
3. (12 分) $Q = 1$
4. (14 分) $D = 1$
5. (17 分) $L = 0$，$R = N - 1$
6. (19 分)  $D$ 的值在 `max_towers` 的所有调用中都是相同的
7. (23 分) 没有额外的限制

### 评测程序示例

评测程序示例读取如下格式的输入：

* 第 $1$ 行：$N \; Q$
* 第 $2$ 行：$H_{0} \; H_{1} \; \ldots \; H_{N - 1}$
* 第 $3 + j$ 行（$0 \le j \le Q - 1$）：$L \; R \; D$（对应第 $j$ 次询问）

评测程序示例按照如下的格式打印你的答案：

* 第 $1 + j$ 行（$0 \le j \le Q - 1$）：`max_towers` 对第 $j$ 次询问的返回值

### 约定

题面在给出函数接口时，会使用一般性的类型名称 `void`、`int`、`int64`、`int[]`（数组）和 `int[][]`（数组的数组）。

在 C++ 中，评测程序会采用适当的数据类型或实现，如下表所示：

| `void ` | `int` | `int64`     | `int[]`            |
| ------- | ----- | ----------- | ------------------ |
| `void ` | `int` | `long long` | `std::vector<int>` |

| `int[][]`                       | 数组 `a` 的长度 |
| ------------------------------- | ------------------- |
| `std::vector<std::vector<int>>` | `a.size()`          |



---

---
title: "[IOI 2021] 分糖果"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8518
tag: ['2021', 'IOI', '交互题']
---
# [IOI 2021] 分糖果
## 题目背景

# 滥用本题评测将被封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。
## 题目描述

Khong 阿姨正在给附近一所学校的学生准备 $n$ 盒糖果。盒子的编号分别为 $0$ 到 $n - 1$，开始时盒子都为空。第 $i$ 个盒子 $(0 \leq i \leq n - 1)$ 至多可以容纳 $c[i]$ 块糖果（容量为 $c[i]$）。

Khong 阿姨花了 $q$ 天时间准备糖果盒。在第 $j$ 天 $(0 \leq j \leq q - 1)$，她根据三个整数 $l[j]$、 $r[j]$ 和 $v[j]$ 执行操作，其中 $0 \leq l[j] \leq r[j] \leq n - 1$ 且 $v[j] \neq 0$。对于每个编号满足 $l[j] \leq k \leq r[j]$ 的盒子 $k$：

- 如果 $v[j] > 0$，Khong 阿姨将糖果一块接一块地放入第 $k$ 个盒子，直到她正好放了 $v[j]$ 块糖果或者该盒子已满。也就是说，如果该盒子在这次操作之前已有 $p$ 块糖果，那么在这次操作之后盒子将有 $\min(c[k], p + v[j])$ 块糖果。

- 如果 $v[j] < 0$，Khong 阿姨将糖果一块接一块地从第 $k$ 个盒子取出，直到她正好从盒子中取出 $-v[j]$ 块糖果或者该盒子已空。也就是说，如果该盒子在这次操作之前已有 $p$ 块糖果，那么在这次操作之后盒子将有 $\max(0, p + v[j])$ 块糖果。

你的任务是求出 $q$ 天之后每个盒子中糖果的数量。
## 输入格式

**实现细节**

你要实现以下函数：

```cpp
std::vector<int> distribute_candies(
  	std::vector<int> c, std::vector<int> l, 
  	std::vector<int> r, std::vector<int> v)
```

- $c$：一个长度为 $n$ 的数组。 对于 $0 \leq i \leq n - 1$, $c[i]$ 表示盒子 $i$ 的容量。

- $l$、 $r$ 和 $v$：三个长度为 $q$ 的数组。 在第 $j$ 天, 对于 $0 \leq j \leq q - 1$，Khong 阿姨执行由整数 $l[j]$、 $r[j]$ 和 $v[j]$ 决定的操作，如题面所述。
## 输出格式

- 该函数应该返回一个长度为 $n$ 的数组。用 $s$ 表示这个数组。 对于 $0 \leq i \leq n - 1$， $s[i]$ 应为 $q$ 天以后盒子 $i$ 中的糖果数量。
## 样例

### 样例输入 #1
```
3
10 15 13
2
0 2 20
0 1 -11

```
### 样例输出 #1
```
0 4 13

```
## 提示

**例 1**

考虑如下调⽤：
`distribute_candies([10, 15, 13], [0, 0], [2, 1], [20, -11])`

这表示盒子 $0$ 的容量为 $10$ 块糖果，盒子 $1$ 的容量为 $15$ 块糖果，盒子 $2$ 的容量为 $13$ 块糖果。

在第 $0$ 天结束时，盒子 $0$ 有 $\min(c[0], 0 + v[0]) = 10$ 块糖果，盒子 $1$ 有 $\min(c[1], 0 + v[0]) = 15$ 块糖果，盒子 2 有 $\min(c[2], 0 + v[0]) = 13$ 块糖果。

在第 $1$ 天结束时，盒子 $0$ 有 $\max(0, 10 + v[1]) = 0$ 块糖果，盒子 $1$ 有 $\max(0, 15 + v[1]) = 4$ 块糖果。因为 $2 > r[1]$，盒子 $2$ 中的糖果数量没有变化。每一天结束时糖果的数量总结如下：

| 天 | 盒子 $0$ | 盒子 $1$ | 盒子 $2$ |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $10$ | $15$ | $13$ |
| $1$ | $0$ | $4$ | $13$ |

就此情况，函数应该返回 $[0, 4, 13]$。

**约束条件**

- $1 \le n \le 200 000$

- $1 \le q \le 200 000$
- $1 \le c[i] \le 10 ^ 9$ （对所有 $0 \le i \le n - 1$）
- $0 \le l[j] \le r[j] \le n - 1$（对所有 $0 \le j \le q - 1$）

- $−10 ^ 9 \le v[j] \le 10 ^ 9$ , $v[j] ≠ 0$（对所有 $0 \le j \le q - 1$）

**子任务**

1. （$3$ 分） $n, q \leq 2000$
2. （$8$ 分） $v[j] > 0$（对所有 $0 \le j \le q - 1$）
3. （$27$ 分） $c[0] = c[1] = \cdots = c[n - 1]$
4. （$29$ 分） $l[j] = 0$ 和 $r[j] = n - 1$（对所有 $0 \leq j \leq q - 1$）
5. （$33$ 分） 没有额外的约束条件。

**评测程序示例**

评测程序示例读入如下格式的输入：

- 第 $1$ 行: $n$
- 第 $2$ 行: $c[0] ~ c[1] ~ \cdots ~ c[n - 1]$
- 第 $3$ 行: $q$
- 第 $4 + j$ 行 ( $0 \leq j \leq q - 1$): $l[j] ~ r[j] ~ v[j]$

评测程序示例按照以下格式打印你的答案：

第 $1$ 行: $s[0] ~ s[1] ~ \cdots ~ s[n - 1]$


---

---
title: "[IOI 2021] 钥匙"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8519
tag: ['2021', 'IOI', '交互题', 'O2优化']
---
# [IOI 2021] 钥匙
## 题目背景

# 滥用本题评测将被封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。
## 题目描述

建筑师 Timothy 设计了一个新的密室逃脱游戏。

这个游戏里有 $n$ 个房间，房间从 $0$ 到 $n - 1$ 编号。最开始的时候，每个房间里都恰好有一把钥匙。每把钥匙都有一个类型，钥匙的类型是一个 $0$ 到 $n - 1$ 区间内的整数。第 $i$ 个房间里的钥匙类型是 $r[i]$。注意多个房间里可能会包含相同类型的钥匙，即$r[i]$ 的值不一定是两两不同的。 

游戏里还有 $m$ 条**双向**的通道，通道从 $0$ 到 $m - 1$ 编号。第 $j$ 条通道连接了一对编号不同的房间 $u[j]$ 和 $v[j]$。同一对房间之间可能存在多条通道。

参与游戏的玩家需要收集钥匙和在不同的房间之间通过通道进行移动。 当玩家使用通道 $j$ 从房间 $u[j]$ 移动到 $v[j]$ ，或者反过来从 $v[j]$ 移动到 $u[j]$ 时，我们说玩家**通过**了通道 $j$。 只有当玩家收集到类型为 $c[j]$ 的钥匙时，玩家才可以通过通道 $j$。 

在游戏的任意时刻，玩家可以在某个房间 $x$ 里执行以下两种操作： 

- 收集房间 $x$ 里面的钥匙，钥匙的类型是 $r[x]$（除⾮对应类型的钥匙已经被收集过）。
- 通过通道 $j$，需要满足 $u[j] = x$ 或 $v[j] = x$，且玩家已经获得 $c[j]$ 类型的钥匙。 

注意玩家收集过的钥匙可以一直使用，**永远不会被丢弃**。 

最初玩家会在某个房间 $s$ **开始**游戏，不带任何钥匙。 如果玩家从房间 $s$ 开始，通过一系列上述描述的两种操作，能够到达房间 $t$，那么称房间 $t$ 是**从房间 $s$ 开始可以到达的**。 

对于每一个房间 $i ~ ( 0 \le i \le n − 1)$，定义从房间 $i$ 出发能够到达的房间数为 $p[i]$。Timothy 想要知道满⾜ $p[i]$ 值最小的下标 $i$ 的集合。
## 输入格式

你要实现以下函数：

```cpp
std::vector<int> find_reachable(
	std::vector<int> r, std::vector<int> u, 
	std::vector<int> v, std::vector<int> c
)
```

- $r$：⼀个⻓度为 $n$ 的序列。对于每⼀个 $i ~ ( 0 \leq i \leq n − 1)$，第 $i$ 个房间⾥的钥匙类型是 $r[i]$。
- $u, v$：两个⻓度为 $m$ 的序列。 对于每⼀个 $j ~ ( 0 \leq j \leq m − 1)$，第 $j$ 条通道连接了房间 $u[j]$ 和 $v[j]$。
- $c$：⼀个⻓度为 $m$ 的序列。对于每⼀个 $j ~ ( 0 \leq j \leq m − 1)$，通过通道 $j$ 需要⽤到的钥匙类型是 $c[j]$.

## 输出格式

- 这个函数应该返回⼀个⻓度为 $n$ 的序列 $a$。对于 $0 \leq i \leq n − 1$ 中的 $i$，如果满⾜ $p[i] \leq p[j] ~ (0 \leq j \leq n − 1)$ 那么 $a[i]$ 的值为 $1$，否则 $a[i]$ 的值为 $0$。
## 样例

### 样例输入 #1
```
4 5
0 1 1 2
0 1 0
0 2 0
1 2 1
1 3 0
3 1 2

```
### 样例输出 #1
```
0 1 1 0

```
### 样例输入 #2
```
7 10
0 1 1 2 2 1 2
0 1 0
0 2 0
1 2 1
1 3 0
2 3 0
3 4 1
3 5 2
4 5 0
4 6 2
5 6 1

```
### 样例输出 #2
```
0 1 1 0 1 0 1

```
### 样例输入 #3
```
3 1
0 0 0
0 1 0

```
### 样例输出 #3
```
0 0 1

```
## 提示

**样例解释**

对于例 $1$，考虑以下调用：

```cpp
find_reachable([0, 1, 1, 2],
[0, 0, 1, 1, 3], [1, 2, 2, 3, 1], [0, 0, 1, 0, 2])
```

如果玩家从房间 $0$ 开始游戏，可以执⾏以下的操作序列：

| 当前房间 | 操作 |
| :----------: | :----------: |
| $0$ | 收集钥匙类型 $0$ |
| $0$ | 通过通道 $0$ 到房间 $1$ |
| $1$ | 收集钥匙类型 $1$ |
| $1$ | 通过通道 $2$ 到房间 $2$ |
| $2$ | 通过通道 $2$ 到房间 $1$ |
| $1$ | 通过通道 $3$ 到房间 $3$ |

因此从房间 $0$ 出发可以到达房间 $3$。 类似地，我们可以构造出操作序列表明所有 $4$ 个房间都是从房间 $0$ 出发可达的，所以 $p[0] = 4$。 下表展⽰了从各个房间出发可以到达的房间集合：

| 开始房间 $i$ | 可以到达的房间 | $p[i]$ |
| :----------: | :------------: | :----: |
|     $0$      | $[0, 1, 2, 3]$ |  $4$   |
|     $1$      |    $[1, 2]$    |  $2$   |
|     $2$      |    $[1, 2]$    |  $2$   |
|     $3$      |  $[1, 2, 3]$   |  $3$   |

所有房间中 $p[i]$ 的最小值是 $2$，这可以在 $i = 1$ 或 $i = 2$ 处取得。所以这次函数调⽤的返回值是 $[0, 1, 1, 0]$。

对于例 $2$：所有房间中 $p[i]$ 的最小值是 $2$，这可以在 $i \in \{1, 2, 4, 6\}$ 处取得。所以这次函数调⽤的返回值是
$[0, 1, 1, 0, 1, 0, 1]$。

对于例 $3$：所有房间中 $p[i]$ 的最小值是 $1$，这可以在 $i = 2$ 处取得。所以这次函数调⽤的返回值是 $[0, 0, 1]$。

**约束条件**

- $2 \leq n \leq 3 \times 10 ^ 5$
- $1 \leq m \leq 3 \times 10 ^ 5$
- $0 \leq r[i] \leq n - 1$ （对于所有的 $0 \leq i \leq n - 1$）
- $0 \leq u[j], v[j] \leq n - 1$ 且 $u[j] \neq v[j]$ （对于所有的 $0 \leq j \leq m - 1$）
- $0 \leq c[j] \leq n - 1$（对于所有的 $0 \leq j \leq m - 1$）

**子任务**

1. （$9$ 分） $c[j] = 0$（对于所有的 $0 \leq j \leq m − 1$）且 $n, m \leq 200$  
2. （$11$ 分） $n, m \leq 20$
3. （$17$ 分） $n, m \leq 2000$ 
4. （$30$ 分） $c[j] \leq 29$（对于所有的 $0 \leq j \leq m − 1$）且 $r[i] \leq 29$（对于所有的 $0 \leq i \leq n − 1$） 
5. （$33$ 分）没有额外的约束条件。

**样例评分程序**

评测程序⽰例以如下格式读取输⼊数据：

- 第 $1$ ⾏：$n ~ m$
- 第 $2$ ⾏： $r[0] ~ r[1] ~ \cdots ~ r[n − 1]$
- 第 $3 + j$ ⾏ $( 0 \leq j \leq m − 1)$： $u[j] ~ v[j] ~ c[j]$

样例评分程序按照以下格式打印 `find_reachable` 函数的返回值：

第 $1$ ⾏： $s[0] ~ s[1] \cdots ~ s[n − 1]$


---

---
title: "[IOI 2021] 喷泉公园"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8520
tag: ['2021', 'IOI', '交互题', 'Special Judge', 'O2优化']
---
# [IOI 2021] 喷泉公园
## 题目背景

# 滥用本题评测将被封号

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。但是你的代码需要声明 `void build(std::vector<int> u, std::vector<int> v, std::vector<int> a, std::vector<int> b)` 函数。

具体的，以下是一种模板：
```cpp
#include <vector>

void build(std::vector<int> u, std::vector<int> v, std::vector<int> a, std::vector<int> b);

int construct_roads(std::vector<int> x, std::vector<int> y) {
    // Code here...
}
```

由于洛谷技术限制，本题仅包含 IOI 官方数据的部分测试点。
## 题目描述

在附近的一个公园里，有 $n$ 座**喷泉**，编号为从 $0$ 到 $n - 1$。我们把喷泉看成是二维平面上的点。也就是说，喷泉 $i ~ (0 \leq i \leq n - 1)$ 是一个点 $(x _ i, y _ i)$，这里 $x _ i$ 和 $y _ i$ 是**偶数**。喷泉的位置各不相同。

建筑师 Timothy 受雇来规划一些**道路**的建设，以及每条道路对应的长椅的摆放。每条道路都是一个长度为 $2$ 的**横向**或**纵向**的线段，其端点是两座不同的喷泉。游客应该能够沿着它们即可在任意两座喷泉之间互相抵达。在最开始时，公园里没有任何道路。

对于每条道路，都要在公园里摆放恰好一个长椅，并将其**分配给**（也就是面朝）这条道路。每个长椅必须摆放在某个点 $(a, ~ b)$ 上，这里 $a$ 和 $b$ 都是**奇数**。所有长椅的位置必须都是**不同的**。在 $(a, ~ b)$ 处的长椅，只能分配给两个断电均为 $(a - 1, ~ b - 1), (a - 1, ~ b + 1), (a + 1, ~ b - 1)$ 和 $(a + 1, ~ b + 1)$ 其中之一的道路。举例来说，在 $(3, ~ 3)$ 处的长椅只能分配给下面四条线段所表示的道路之一：$(2, ~ 2), - (2, ~ 4), ~ (2 , ~ 4) - (4, ~ 4), ~ (4, ~ 4) - (4, ~ 2), ~ (4, ~ 2) - (2, ~ 2)$。

请帮助 Timothy 判断一下，能否在满足上述所有要求的前提下，造出所有道路，并摆放和分配长椅。如果这能做到，请给他一个可行的解决方案。如果有多个满足所有要求的方案，你可以报告其中的任意方案。
## 输入格式

你要实现以下函数：

```cpp
int construct_roads(std::vector<int> x, std::vector<int> y)
```
- $x, ~ y$: 长度为 $n$ 的两个数组。对所有 $i ~ (0 \leq i \leq n - 1)$，喷泉 $i$ 是一个点 $(x[i], y[i]$，这里 $(x[i], y[i])$ 都是偶数。
- 如果存在某个建设方案，函数应当调用 `build`（参见下文）恰好一次来报告建设方案，并紧接着返回 $1$。
- 否则，函数应当返回 $0$，并且不做 `build` 的任何调用。
- 该函数将被调用恰好一次。

你实现的函数可以调用下面的函数，以提供一个可行的道路建设与长椅摆放方案。
```cpp
void build(std::vector<int> u, std::vector<int> v, std::vector<int> a, std::vector<int> b)
```

- 设 $m$ 为建设方案中道路的个数。
- $u, v$: 长度为 $m$ 的两个数组，表示要建设的道路。这些道路的编号为从 $0$ 到 $m - 1$。对所有的 $j ~ (0 \leq j \leq m - 1)$，道路 $j$ 要连接喷泉 $u[j]$ 和 $v[j]$。每条道路必须是长度为 $2$ 的横向或纵向线段。任意两条不同的道路，最多只能有一个公共端点（某个喷泉）。这些道路在建成之后，必须能够沿着它们就可以在任意两个喷泉之间相互抵达。
- $a, b$: 长度为 $m$ 的两个数组，表示长椅。对所有的 $j ~ (0 \leq j \leq m - 1)$，将在 $(a[j], b[j])$ 处摆放一个长椅，并且分配给道路 $j$。不同的长椅不能摆放在同一位置。
## 样例

### 样例输入 #1
```
5
4 4
4 6
6 4
4 2
2 4

```
### 样例输出 #1
```
1
4
0 2 5 5
0 1 3 5
3 0 5 3
4 0 3 3

```
### 样例输入 #2
```
2
2 2
4 6

```
### 样例输出 #2
```
0

```
## 提示

**例 1**

考虑如下调用：
```cpp
construct_roads([4, 4, 6, 4, 2], [4, 6, 4, 2, 4])
```

这意味着总共有 $5$ 座喷泉：

- 喷泉 $0$ 坐落在 $(4, 4)$ 处。
- 喷泉 $1$ 坐落在 $(4, 6)$ 处。
- 喷泉 $2$ 坐落在 $(6, 4)$ 处。
- 喷泉 $3$ 坐落在 $(4, 2)$ 处。
- 喷泉 $4$ 坐落在 $(2, 4)$ 处。

可以建造下面这样 $4$ 条道路，其中每条道路连接两座喷泉，并且摆放着对应的长椅。

| 道路编号 | 道路所连接的喷泉编号 | 所分配的长椅的位置 |
| :----------: | :----------: | :----------: |
| $0$ | $0, 2$ | $(5, 5)$ |
| $1$ | $0, 1$ | $(3, 5)$ |
| $2$ | $3, 0$ | $(5, 3)$ |
| $3$ | $4, 0$ | $(3, 3)$ |

该方案对应下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s7vv14bj.png)

为报告此方案，`construct_roads` 应做如下调用：

```cpp
build([0, 0, 3, 4], [2, 1, 0, 0], [5, 3, 5, 3], [5, 5, 3, 3])
```

随后它应当返回 $1$，

注意，在这个例子中，有多个满足要求的方案，它们都被视为正确。

**例 2**

考虑如下调用：

```cpp
construct_roads([2, 4], [2, 6])
```

喷泉 $0$ 坐落在 $(2, 2)$ 处，而喷泉 $1$ 坐落在 $(4, 6)$ 处。由于不可能建造出满⾜要求的道路，
`construct_roads` 应当返回 $0$，并且不做 `build` 的任何调⽤。

**约束条件**

- $1 \leq n \leq 2 \times 10 ^ 5$
- $2 \leq x[i], y[i] \leq 2 \times 10 ^ 5$
- $x[i], y[i]$ 都是偶数。
- 任意两座喷泉的位置都不相同。

**子任务**

1. （$5$ 分）$x[i] = 2$
2. （$10$ 分）$2 \leq x[i] \leq 4$
3. （$15$ 分）$2 \leq x[i] \leq 6$
4. （$20$ 分）至多只有一种道路建设方案，能够让游客在任意两座喷泉之间沿着这些道路即可抵达。
5. （$20$ 分）任意四座喷泉都不会构成某一个 $2 \times 2$ 正方形的四个顶点。
6. （$30$ 分）没有额外的约束条件。


---

---
title: "[IOI 2021] 地牢游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8522
tag: ['倍增', '2021', 'IOI', '交互题']
---
# [IOI 2021] 地牢游戏
## 题目背景

**滥用本题评测将被封号**

**由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。**

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。
## 题目描述

Robert 正在设计一款新的电脑游戏。游戏中有一位英雄、$n$ 个敌人和 $n + 1$ 个地牢。敌人从 $0$ 到 $n - 1$ 编号，地牢从 $0$ 到 $n$ 编号。敌人 $i$（$0 \le i \le n - 1$）处在地牢 $i$，其能力值为 $s[i]$。地牢 $n$ 里没有敌人。

英雄一开始进入地牢 $x$，初始能力值为 $z$。每次英雄进入地牢 $i$（$0 \le i \le n - 1$）时，都需要面对敌人 $i$，且会发生以下情况中的一种：

如果英雄的能力值大于等于敌人 $i$ 的能力值 $s[i]$，那么英雄会胜出。这使得英雄的能力值增加 $s[i]$（$s[i] \ge 1$）。这种情况下，下一步英雄将会进入地牢 $w[i]$（$w[i] > i$）。

否则英雄会战败，这使得英雄的能力值增加 $p[i]$（$p[i] \ge 1$）。在这种情况下，下一步英雄将会进入地牢 $l[i]$。

注意 $p[i]$ 可能会小于、等于、大于 $s[i]$，$l[i]$ 可能会小于、等于、大于 $i$。无论对战结果如何，敌人 $i$ 始终处在地牢 $i$，且能力值为 $s[i]$。

当英雄进入地牢 $n$ 的时候，游戏结束。可以看出无论英雄的起始地牢和初始能力值如何，游戏一定会在有限次对战之后结束。

Robert 希望你通过 $q$ 次模拟来对游戏进行测试。对于每次模拟，Robert 输入英雄的起始地牢 $x$ 和初始能力值 $z$。你需要做的是对于每次模拟给出游戏结束时英雄的能力值。
## 输入格式

你要实现以下函数：
```cpp
void init(int n, int[] s, int[] p, int[] w, int[] l)
```
- $n$：敌人的数量。
$s$、$p$、$w$、$l$：长度为 $n$ 的序列。对于每一个 $i$（$0 \le i \le n - 1$）：
  + $s[i]$ 是敌人 $i$ 的能力值，也是击败敌人 $i$ 后英雄增加的能力值。
  + $p[i]$ 是英雄被敌人 $i$ 击败后增加的能力值。
  + $w[i]$ 是英雄击败敌人 $i$ 后进入的下一个地牢的编号。
  + $l[i]$ 是英雄被敌人 $i$ 击败后进入的下一个地牢的编号。
- 恰好调用此函数一次，且发生在任何对如下的 simulate 函数的调用之前。
```cpp
int64 simulate(int x, int z)
```
- $x$：英雄的起始地牢编号。
- $z$：英雄的初始能力值。
- 假设英雄的起始地牢编号为 $x$，初始能力值为 $z$，函数的返回值是相应情况下游戏结束时英雄的能力值。
- 恰好调用此函数 $q$ 次。
## 样例

### 样例输入 #1
```
3 2
2 6 9
3 1 2
2 2 3
1 0 1
0 1
2 3
```
### 样例输出 #1
```
24
25
```
## 提示

对于所有数据：

- $1 \le n \le 400 \, 000$
- $1 \le q \le 50 \, 000$
- $1 \le s[i], p[i] \le {10}^7$（对于所有的 $0 \le i \le n - 1$）
- $0 \le l[i], w[i] \le n$（对于所有的 $0 \le i \le n - 1$）
- $w[i] > i$（对于所有的 $0 \le i \le n - 1$）
- $0 \le x \le n - 1$
- $1 \le z \le {10}^7$

子任务	|分值|特殊限制
:-:|:-:|:-:
$0$|$0$|样例
$1$|	$11$|	$n \le 50 \, 000$，$q \le 100$，$s[i], p[i] \le 10 \, 000$（对于所有的 $0 \le i \le n - 1$）
$2$|	$26$|	$s[i] = p[i]$（对于所有的 $0 \le i \le n - 1$）
$3$|	$13$|	$n \le 50 \, 000$，所有的敌人拥有相同的能力值，即 $s[i] = s[j]$，对于所有的 $0 \le i, j \le n - 1$
$4$|	$12$|	$n \le 50 \, 000$，所有的 $s[i]$ 至多有 $5$ 种不同的数值
$5$|	$27$|	$n \le 50 \, 000$
$6$|	$11$|	没有额外的约束条件


---

---
title: "[IOI 2021] 位移寄存器"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8523
tag: ['2021', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2021] 位移寄存器
## 题目背景

**滥用本题评测将被封号**

**由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。**

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。

你的代码需要在开头添加以下代码：

```cpp
#include<vector>
void append_move(int t, int y);
void append_store(int t, std::vector<bool> v);
void append_and(int t, int x, int y);
void append_or(int t, int x, int y);
void append_xor(int t, int x, int y);
void append_not(int t, int x);
void append_left(int t, int x, int p);
void append_right(int t, int x, int p);
void append_add(int t, int x, int y);
void append_print(int t);
```
## 题目描述

工程师 Christopher 在开发一款新的计算机处理器。

这个处理器可以访问 $m$ 个不同的 $b$ 位存储单元（本题中 $m = 100$ 且 $b = 2000$）。它们被称作寄存器，编号从 $0 $ 到 $m - 1$。我们把这些寄存器记为 $r[0], r[1], \ldots , r[m - 1]$。每个寄存器都是 $b$ 个比特的数组，这些比特从 $0$（最右的比特）到 $b - 1$（最左的比特）编号。对所有的 $i$（$0 \le i \le m - 1$）和 $j$（$0 \le j \le b - 1$），我们将寄存器 $i$ 的第 $j$ 个比特记为 $r[i][j]$。

对所有的比特序列 $d_0, d_1, \ldots , d_{l - 1}$（具有某个长度 $l$），该序列的整数值等于 $2^0 \cdot d_0 + 2^1 \cdot d_1 + \cdots + 2^{l - 1} \cdot d_{l - 1}$。我们说存储在某个寄存器中的整数值就是寄存器中比特序列的整数值，也就是说，该整数值为 $2^0 \cdot r[i][0] + 2^1 \cdot r[i][1] + \cdots + 2^{b - 1} \cdot r[i][b - 1]$。

该处理器有 $9$ 种类型的指令，可以用来修改寄存器中的比特。每条指令操作一个或多个寄存器，并将其输出存储到其中的一个寄存器。下面我们用 $x := y$ 表示一个修改 $x$ 的值并将其变成 $y$ 的操作。每种类型的指令所做的操作描述如下：

$\operatorname{\mathit{move}}(t, y)$：将寄存器 $y$ 中的比特数组拷贝到寄存器 $t$。对所有的 $j$（$0 \le j \le b - 1$），设置 $r[t][j] := r[y][j]$。

$\operatorname{\mathit{store}}(t, v)$：设置寄存器 t 等于 $v$，这里 $v$ 是某个 $b$ 个比特的数组。对于所有的 $j$（$0 \le j \le b - 1$），设置 $r[t][j] := v[j]$。

$\operatorname{\mathit{and}}(t, x, y)$：取寄存器 $x$ 和 $y$ 的按位与，并将结果存到寄存器 $t$ 中。对于所有的 $j$（$0 \le j \le b - 1$），如果 $r[x][j]$ 和 $r[y][j]$ 同时为 $1$ 则设置 $r[t][j] := 1$，否则设置 $r[t][j] := 0$。

$\operatorname{\mathit{or}}(t, x, y)$：取寄存器 $x$ 和 $y$ 的按位或，并将结果存到寄存器 $t$ 中。对于所有的 $j$（$0 \le j \le b - 1$），如果 $r[x][j]$ 和 $r[y][j]$ 至少有一个为 1 则设置 $r[t][j] := 1$，否则设置 $r[t][j] := 0$。

$\operatorname{\mathit{xor}}(t, x, y)$：取寄存器 $x$ 和 $y$ 的按位异或，并将结果存到寄存器 $t$ 中。对于所有的 $j$（$0 \le j \le b - 1$），如果 $r[x][j]$ 和 $r[y][j]$ 恰好有一个为 1 则设置 $r[t][j] := 1$，否则设置 $r[t][j] := 0$。

$\operatorname{\mathit{not}}(t, x)$：取寄存器 $x$ 的按位非，并将结果存到寄存器 $t$ 中。对于所有的 $j$（$0 \le j \le b - 1$），设置 $r[t][j] := 1 - r[x][j]$。

$\operatorname{\mathit{left}}(t, x, p)$：左移寄存器 $x$ 中的所有比特 $p$ 位，并将结果存到寄存器 $t$ 中。将寄存器 $x$ 中的比特左移 $p$ 位的结果，是一个包含 $b$ 个比特的数组 $v$。对于所有的 $j$（$0 \le j \le b - 1$），如果 $j \ge p$ 则 $v[j] = r[x][j - p]$，否则 $v[j] = 0$。对所有的 $j$（$0 \le j \le b - 1$），设置 $r[t][j] := v[j]$。

$\operatorname{\mathit{right}}(t, x, p)$：右移寄存器 $x$ 中的所有比特 $p$ 位，并将结果存到寄存器 $t$ 中。将寄存器 $x$ 中的比特右移 $p$ 位的结果，是一个包含 $b$ 个比特的数组 $v$。对于所有的 $j$（$0 \le j \le b - 1$），如果 $j \le b - 1 - p$ 则 $v[j] = r[x][j + p]$，否则 $v[j] = 0$。对所有的 $j$（$0 \le j \le b - 1$），设置 $r[t][j] := v[j]$。

$\operatorname{\mathit{add}}(t, x, y)$：将寄存器 $x$ 和 $y$ 中的整数值加起来，并将结果存到寄存器 $t$ 中。加法是在模 $2^b$ 下做的。正式一些来说，设 $X$ 是操作前存在寄存器 $x$ 中的整数值，而 $Y$ 是操作前存在寄存器 $y$ 中的整数值。设 $T$ 为操作后存在寄存器 $t$ 中的整数值。如果 $X + Y < 2^b$，设置 $t$ 中的比特使得 $T = X + Y$。否则，设置 $t$ 中的比特使得 $T = X + Y - 2^b$。

Christopher 希望你用这个新处理器解决两种任务。任务的类型用整数 $s$ 来表示。对所有类型的任务，你需要创建一个程序，其为上文所定义的指令构成的序列。

程序的输入包括 $n$ 个整数 $a[0], a[1], \ldots , a[n - 1]$，而每个整数都有 $k$ 个比特，也就是说，$a[i] < 2^k$（$0 \le i \le n - 1$）。在程序执行前，输入的所有的数都依次存储在寄存器 $0$ 中，使得对所有的 $i$（$0 \le i \le n - 1$），$k$ 比特序列 $r[0][i \cdot k], r[0][i \cdot k + 1], \ldots , r[0][(i + 1) \cdot k - 1]$ 的整数值等于 $a[i]$。注意 $n \cdot k \le b$。寄存器 $0$ 中所有其他的比特（其下标在 $n \cdot k$ 和 $b - 1$ 之间，包括 $n \cdot k$ 和 $b - 1$），以及其他所有寄存器中的所有比特，都初始化为 $0$。

执行某个程序就是按序执行其所包含的指令。在最后一条指令执行完毕后，程序的输出将根据寄存器 $0$ 中比特最终的值计算出来。具体来说，输出是 $n$ 个整数 $c[0], c[1], \ldots , c[n - 1]$ 的序列，这里对所有 $i$（$0 \le i \le n - 1$）来说，$c[i]$ 都是寄存器 $0$ 中比特 $i \cdot k$ 到 $(i + 1) \cdot k - 1$ 所构成的序列的整数值。注意，在程序运行结束后，寄存器 $0$ 中其余的比特（下标不小于 $n \cdot k$），以及其他寄存器中的所有比特，可能是任意值。

第一个任务（$s = 0$）是要找出输入整数 $a[0], a[1], \ldots , a[n - 1]$ 中的最小值。 具体来说，$c[0]$ 必须是 $a[0], a[1], \ldots , a[n - 1]$ 中的最小值。$c[1], c[2], \ldots , c[n - 1]$ 的值可以是任意的。

第二个任务（$s = 1$）是要将输入整数 $a[0], a[1], \ldots , a[n - 1]$ 进行非降序排序。具体来说，对于所有的 $i$（$0 \le i \le n - 1$），$c[i]$ 应当等于 $a[0], a[1], \ldots , a[n - 1]$ 中第 $1 + i$ 小的整数（也就是说，$c[0]$ 是输入整数中的最小整数）。

请帮 Christopher 写一下解决这些任务的程序。每个程序至多只能包含 $q$ 条指令。
## 输入格式

你要实现如下函数：

```cpp
void construct_instructions(int s, int n, int k, int q)
 ```
- $s$：任务类型。
- $n$：输入中的整数的数量。
- $k$：输入中的每个整数的比特数。
- $q$：允许的最大的指令数。
该函数将被恰好调用一次，并应当为所要解决的任务创建一个指令序列。

该函数应当调用以下函数中的一或多个，以创建指令序列：

```cpp
void append_move(int t, int y)
void append_store(int t, std::vector<bool> v)
void append_and(int t, int x, int y)
void append_or(int t, int x, int y)
void append_xor(int t, int x, int y)
void append_not(int t, int x)
void append_left(int t, int x, int p)
void append_right(int t, int x, int p)
void append_add(int t, int x, int y)
```
- 每个函数分别往程序追加一条 $\operatorname{\mathit{move}}(t, y)$、$\operatorname{\mathit{store}}(t, v)$、$\operatorname{\mathit{and}}(t, x, y)$、$\operatorname{\mathit{or}}(t, x, y)$、$\operatorname{\mathit{xor}}(t, x, y)$、$\operatorname{\mathit{not}}(t, x)$、$\operatorname{\mathit{left}}(t, x, p)$、$\operatorname{\mathit{right}}(t, x, p)$ 或 $\operatorname{\mathit{add}}(t, x, y)$ 指令。
- 对于所有相关的指令，$t$、$x$、$y$ 必须至少为 $0$ 且至多为 $m - 1$。
- 对于所有相关的指令，$t$、$x$、$y$ 不必是两两之间不同的。
- 对于指令 `left` 和 `right`，$p$ 必须至少为 $0$ 且至多为 b。
- 对于指令 `store`，$v$ 的长度必须为 $b$。

你还可以调用以下函数，以帮助测试你的答案：

```cpp
void append_print(int t)
```
- 在评测你的答案时，对该函数的所有调用都将被忽略。
- 在评测程序示例中，该函数将往程序追加一个 $\operatorname{\mathit{print}}(t)$ 操作。
- 当评测程序示例在执行某个程序过程中遇到一个 $\operatorname{\mathit{print}}(t)$ 操作时，它会打印出由寄存器 $t$ 中前 $n \cdot k$ 比特构成的 $n$ 个 $k$-比特整数。
- $t$ 必须满足 $0 \le t \le m - 1$。
- 对该函数的任何调用，都不会算到你所创建的指令的数量里面。

在追加最后一条指令之后，`construct_instructions` 应当返回。随后你创建的程序将在一定数量的测试用例上评测，其中每个测试用例给出的输入数据为 $n$ 个 $k$-比特整数 $a[0], a[1], \ldots , a[n - 1]$。如果程序对给定输入数据的输出结果 $c[0], c[1], \ldots , c[n - 1]$ 满足如下条件，你的答案就将被视为通过了对应的样例：

- 如果 $s = 0$，$c[0]$ 应当为 $a[0], a[1], \ldots , a[n - 1]$ 中的最小值。
- 如果 $s = 1$，对所有 $i$（$0 \le i \le n - 1$）来说，$c[i]$ 应当是 $a[0], a[1], \ldots , a[n - 1]$ 中第 $1 + i$ 小的整数。

在评测你的答案时，可能会给出下面的错误信息之一：

- `Invalid index`：在调用某些函数时的参数 $t$、$x$ 或 $y$ 所给出的寄存器下标是不正确的（可能是负数）。
- `Value to store is not b bits long`：提供给 `append_store` 的 $v$ 的长度不等于 $b$。
- `Invalid shift value`：提供给 `append_left` 或 `append_right` 的 $p$ 的值不在 $0$ 和 $b$ 之间（包括 $0$ 和 $b$）。
- `Too many instructions`：你的函数试图追加超过 $q$ 条指令。
## 样例

### 样例输入 #1
```
0 2 1 1000
0 0
0 1
1 0
1 1
-1
```
### 样例输出 #1
```
move 1 0
right 1 1 1
and 0 0 1
0
0
0
1
```
### 样例输入 #2
```
1 2 1 1000
0 0
0 1
1 0
1 1
-1

```
### 样例输出 #2
```
move 1 0
right 1 1 1
and 2 0 1
or 3 0 1
left 3 3 1
or 0 2 3
0 0
0 1
0 1
1 1

```
## 提示

对于所有数据：

- $m = 100$
- $b = 2000$
- $0 \le s \le 1$
- $2 \le n \le 100$
- $1 \le k \le 10$
- $q \le 4000$
- $0 \le a[i] \le 2^k - 1$（对于所有 $0 \le i \le n - 1$）

子任务|	分值|	特殊限制
:-:|:-:|:-:
$1$	|$10$|	$s = 0$，$n = 2$，$k \le 2$，$q = 1000$
$2$|	$11$|	$s = 0$，$n = 2$，$k \le 2$，$q = 20$
$3$	|$12$	|$s = 0$，$q = 4000$
$4$	|$25$|	$s = 0$，$q = 150$
$5$	|$13$	|$s = 1$，$n \le 10$，$q = 4000$
$6$	|$29$|	$s = 1$，$q=4000$

感谢 @[Bingxiu](https://www.luogu.com.cn/user/676498) 提供交互库。附件中的交互库可用于本地测试，与实际评测用的交互库有所不同。


---

---
title: "[IOI 2009] Archery"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9112
tag: ['2009', 'IOI', 'O2优化']
---
# [IOI 2009] Archery
## 题目背景

IOI2009 D1T1
## 题目描述

一场箭术比赛正在举行。一条直线上排着 $N$ 个靶子，靶子从左到右依次标号为从 $1$ 到 $N$。有 $2N$ 个选手，在比赛的任何时刻，同一个靶位上都有两个选手。比赛的每一轮按照如下规则进行：

- 在同一个靶位的两位选手比赛一场决出胜者，然后所有选手按照如下规则移动：

  - 在 $2$ 到 $N$ 号靶位上的胜者移动到他们的左侧的靶位（即分别移动到 $1\sim N - 1$ 号靶位）。
  - 在 $2$ 到 $N$ 号靶位上的负者，以及 $1$ 号靶位上的胜者，停留在同一个靶位。
  - $1$ 号靶位上的负者移动到 $N$ 号靶位。

比赛一共持续 $R$ 轮，轮数至少为参赛选手的数量，即 $R\geq 2N$。

你是唯一一个准时到达的选手。其它 $2N - 1$ 个选手已经提前到达并站成了一排，你现在要做的就是插入这个队伍。在你进入队伍后，队列中前两个选手（最左侧的两个选手）将对应一号靶位，接下来两个选手将对应二号靶位，以此类推，最右侧的两个选手对应 $N$ 号靶位。

所有 $2N$ 个选手（包括你）都用一个数值衡量技术水平，没有两个选手的技术水平相同。在同一个靶位上，数值较小的选手会成为胜者。

在了解了所有选手的技术水平之后，你需要找到一个位置插入使得你最终对应的靶位序号尽量小，在此前提下，你希望你初始时对应的靶位序号尽量大。

**任务**：编写一个程序，给定所有选手的技术水平（包括你自己）和你的对手们的排列顺序，计算出你的初始靶位编号，以满足你的上述目标。
## 输入格式

第一行包含两个由空格隔开的整数 $N, R$，分别表示靶位数和比赛轮数。

接下来 $2N$ 行给出选手的排列 $S_1, S_2, \cdots,  S_{2N}$。$S_1$ 表示你的排名，$S_2, S_3, \cdots, S_{2N}$ 表示其他选手的排名，依照他们已经排列好的顺序（由左至右）。$S_k$ 是 $1\sim 2N$ 的整数，排名 $1$ 表示最好，排名 $2N$ 表示最差。没有两位选手的排名相同。
## 输出格式

输出一个 $1\sim N$ 的整数，表示开始的箭靶编号。
## 样例

### 样例输入 #1
```
4 8
7
4
2
6
5
8
1
3

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
4 9
2
1
5
8
3
4
7
6

```
### 样例输出 #2
```
2

```
## 提示

### 样例解释

- 样例 1：你是排名倒数第二的选手。如果你从靶 $1$ 开始比赛，接下来你将移动到靶 $4$ 而且一直留在靶 $4$ 直到最后。如果你从靶 $2$ 或靶 $4$ 开始，你将会一直留到最后。如果你从靶 $3$ 开始，你将会击败最差的选手，然后移到靶 $2$ 并留在那里。

- 样例 2：你是排名第二的选手。排名第一的选手在靶 $1$ 并一直留在那里。因此，无论你从哪里出发，你永远会按 $4\to 3\to 2\to 1\to 4$ 的顺序循环移动。为了最终留在靶 $1$，你应该从靶 $2$ 开始。

### 数据范围与约定

- 对于 $20\%$ 的数据，$N\leq 200$。
- 对于 $60\%$ 的数据，$N\leq 5000$。
- 对于 $100\%$ 的数据，$1\leq N\leq 2\times 10 ^ 5$，$2N\leq R\leq 10 ^ 9$，$1\leq S_k\leq 2N$ 且 $S_k$ 互不相同。

另有三组 @[asmend](https://www.luogu.com.cn/user/21658) 提供的 hack 数据，不计分。


---

---
title: "[IOI 2023] 最长路程"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9601
tag: ['2023', 'IOI', '交互题', 'Special Judge', 'O2优化']
---
# [IOI 2023] 最长路程
## 题目背景

IOI2023 D1T2

**特别提醒，由于洛谷交互机制的特殊性，你不能在程序中引入头文件，而需要把头文件的内容加入文件的开头。即，在程序开头加入以下几行语句：**

```
#include <vector>

std::vector<int> longest_trip(int N, int D);

bool are_connected(std::vector<int> A, std::vector<int> B);
```
## 题目描述

IOI 2023 组委会有大麻烦了！他们忘记计划即将到来的 Ópusztaszer 之旅了。然而，或许一切尚未为晚 ......

在 Ópusztaszer 有 $N$ 个地标，编号为从 $0$ 到 $N-1$。某些地标之间连有**双向**的**道路**。任意一对地标之间至多连有一条道路。组委会**不知道**哪些地标之间有道路相连。

如果对于每三个不同的地标，它们之间都至少连有 $\delta$ 条道路，我们就称 Ópusztaszer 的路网**密度**是**至少**为 $\delta$ 的。换言之，对所有满足 $0 \le u \lt v \lt w \lt N$ 的地标三元组 $(u, v, w)$，配对 $(u,v)$，$(v,w)$ 和 $(u,w)$ 中至少有 $\delta$ 个配对中的地标有道路相连。

组委会**已知**有某个正整数 $D$，满足路网密度至少为 $D$。注意， $D$ 的值不会大于 $3$。

组委会可以**询问** Ópusztaszer 的电话接线员，以获取关于某些地标之间的道路连接信息。在每次询问时，必须给出两个非空的地标数组 $[A[0], \ldots, A[P-1]]$ 和 $[B[0], \ldots, B[R-1]]$。地标之间必须是两两不同的，即，

* 对于满足 $0 \le i \lt j \lt P$ 的所有 $i$ 和 $j$，有 $A[i] \neq A[j]$；
* 对于满足 $0 \le i \lt j \lt R$ 的所有 $i$ 和 $j$，有 $B[i] \neq B[j]$；
* 对于满足 $0 \le i \lt P$ 且 $0\le j \lt R$ 的所有 $i$ 和 $j$，有 $A[i] \neq B[j]$。

对每次询问，接线员都会报告是否存在 $A$ 中的某个地标和 $B$ 中的某个地标有道路相连。更准确地说，接线员会对满足 $0 \le i \lt P$ 和 $0\le j \lt R$ 的所有配对 $i$ 和 $j$ 进行尝试。如果其中某对地标 $A[i]$ 与 $B[j]$ 之间连有道路，接线员将报告 `true`。否则，接线员将报告 `false`。

一条长度为 $l$ 的**路程**，被定义为由**不同**地标 $t[0], t[1], \ldots, t[l-1]$ 构成的序列，其中对从 $0$ 到 $l-2$（包括 $0$ 和 $l-2$）的所有 $i$，地标 $t[i]$ 和 $t[i+1]$ 之间都有道路相连。如果不存在长度至少为 $l+1$ 的路程，则长度为 $l$ 的某条路程被称为是**最长路程**。

你的任务是通过询问接线员，帮助组委会在 Ópusztaszer 找一条最长路程。

---

**【实现细节】**

你需要实现如下函数：

```
int[] longest_trip(int N, int D)
```

* $N$：Ópusztaszer 的地标数量。
* $D$：可以保证的路网密度最小值。
* 该函数需要返回一个表示某条最长路程的数组 $t = [t[0], t[1], \ldots, t[l-1]]$。
* 对于每个测试用例，该函数都可能会被调用 **多次**。

上述函数可以调用如下函数：

```
bool are_connected(int[] A, int[] B)
```

* $A$：一个非空、且元素两两不同的地标数组。
* $B$：一个非空、且元素两两不同的地标数组。
* $A$ 和 $B$ 之间应无交集。
* 如果存在连接 $A$ 中某个地标以及 $B$ 中某个地标的道路，该函数返回 `true`。否则该函数返回 `false`。
* 在每次 `longest_trip` 调用中，该函数可以被至多调用 $32\,640$ 次。该函数的累计调用总数至多为 $150\,000$ 次。
* 对历次调用该函数时传递的数组 $A$ 和 $B$ 长度进行累计，两个数组累计长度加起来不能超过 $1\,500\,000$。

评测程序是**非适应性的**。每次提交都将在同一组测试用例上进行评测。换言之，在每个测试用例中，$N$ 和 $D$ 的值，以及道路所连接的地标配对，对于每次 `longest_trip` 调用都保持不变。
## 提示

**【例子】**

**样例一**

考虑某个 $N = 5$, $D = 1$ 的场景，其中道路连接情形如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/h4q6u936.png)

函数 `longest_trip` 被调用如下：

```
longest_trip(5, 1)
```

该函数可以调用 `are_connected` 如下。

|                调用                |  有道路连接的配对  | 返回值  |
| :--------------------------------: | :----------------: | :-----: |
| `are_connected([0], [1, 2, 4, 3])` | $(0,1)$ 和 $(0,2)$ | `true`  |
|     `are_connected([2], [0])`      |      $(2,0)$       | `true`  |
|     `are_connected([2], [3])`      |      $(2,3)$       | `true`  |
|  `are_connected([1, 0], [4, 3])`   |         无         | `false` |

在第四次调用后，可知 $(1,4)$，$(0,4)$，$(1,3)$ 和 $(0,3)$ 中**没有**哪个配对中的地标之间连有道路。由于路网的密度至少是 $D = 1$，我们由三元组 $(0, 3, 4)$ 可知，配对 $(3,4)$ 的地标之间必须连有道路。与此相似，地标 $0$ 和 $1$ 之间必须是相连的。

至此，可以总结出 $t = [1, 0, 2, 3, 4]$ 是一条长度为 $5$ 的路程，而且不存在长度超过 $5$ 的路程。因此，函数 `longest_trip` 可以返回 $[1, 0, 2, 3, 4]$。

考虑另一个场景， 其中 $N = 4$, $D = 1$，且地标之间的道路如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/6kk0r3y9.png)

函数 `longest_trip` 被调用如下：

```
longest_trip(4, 1)
```

在这个场景中，最长路程的长度为 $2$。因此，在对函数 `are_connected` 进行少量调用后，函数 `longest_trip` 可以返回 $[0, 1]$, $[1, 0]$, $[2, 3]$ 和 $[3, 2]$ 中的任意一个.

**样例 2**

子任务 0 包含另一个测试用例用作示例，其中有 $N=256$ 个地标。

**【数据范围】**

* $3 \le N \le 256$
* 对于每个测试用例，函数 `longest_trip` 的所有调用中 $N$ 的累计总和不超过 $1\,024$。
* $1 \le D \le 3$

**【子任务】**

1. （5 分）$D = 3$
1. （10 分）$D = 2$
1. （25 分）$D = 1$。令 $l^\star$ 表示最长路程的长度。函数 `longest_trip` 不必返回长度为 $l^\star$ 的某条路程，而应返回长度至少为 $\left\lceil \frac{l^\star}{2} \right\rceil$ 的某条路程。
1. （60 分）$D = 1$

在子任务 4 中，你的得分将根据 `longest_trip` 的单次调用中对函数 `are_connected` 的调用数量而定。对该子任务的所有测试用例调用 `longest_trip`，令 $q$ 为各次调用产生的函数 `are_connected` 调用次数的最大值。
你在该子任务上的得分将按照下表进行计算：

|            条件            | 得分 |
| :------------------------: | :--: |
| $2\,750 \lt q \le 32\,640$ | $20$ |
|   $550 \lt q \le 2\,750$   | $30$ |
|    $400 \lt q \le 550$     | $45$ |
|        $q \le 400$         | $60$ |

如果在某个测试用例上，对函数 `are_connected` 的调用没有遵守实现细节部分给出的限制条件，或者 `longest_trip` 返回的数组是错误的，你的解答在该子任务上的得分将为 $0$。

**【评测程序示例】**

令 $C$ 为场景数量，即调用 `longest_trip` 的次数。
评测程序示例读取如下格式的输入数据：

* 第 $1$ 行：$C$

接下来是这 $C$ 个场景的描述数据。

评测程序示例读取每个场景如下格式的描述数据：

* 第 $1$ 行：$N \; D$
* 第 $1 + i$ 行（$1 \le i \lt N$）：$U_i[0] \; U_i[1] \; \ldots \; U_i[i-1]$

这里每个 $U_i$（$1 \le i \lt N$）均为长度为 $i$ 的数组，以给出那些有道路相连的地标配对。对于满足 $1 \le i \lt N$ 且 $0 \le j \lt i$ 的所有 $i$ 和 $j$：

* 如果地标 $j$ 和 $i$ 之间有道路相连，则 $U_i[j]$ 的值应为 $1$；
* 如果地标 $j$ 和 $i$ 之间没有道路相连，则 $U_i[j]$ 的值应为 $0$。

在每个场景中，在调用 `longest_trip` 之前，评测程序示例检查路网的密度是否至少为 $D$。如果不满足该条件，评测程序示例将输出信息 `Insufficient Density` 并中止。

如果检查出违反规则的行为，评测程序示例的输出为 `Protocol Violation: <MSG>`，这里 `<MSG>` 为如下错误信息之一：

* `invalid array`：在 `are_connected` 的某次调用中，数组 $A$ 和 $B$ 中至少其一
  - 为空，或
  - 有元素不是 $0$ 到 $N-1$ 之间（包含 $0$ 和 $N-1$）的整数，或
  - 有重复元素。
* `non-disjoint arrays`：在 `are_connected` 的某次调用中，数组 $A$ 和 $B$ 的交集不空。
* `too many calls`：函数 `are_connected` 在 `longest trip` 的当前调用中的被调用次数超过了 $32\,640$，或者其累计调用次数超过了 $150\,000$。
* `too many elements`：在 `are_connected` 的全部调用中，所传递的地标的累计数量超过了 $1\,500\,000$。

否则，令 `longest_trip` 函数在某个场景中的返回数组为 $t[0], t[1], \ldots, t[l - 1]$，这里 $l$ 为某个非负整数。评测程序示例将对该场景按照如下格式输出三行：

* 第 $1$ 行：$l$
* 第 $2$ 行：$t[0] \; t[1] \; \ldots \; t[l-1]$
* 第 $3$ 行：在该场景中调用 `are_connected` 的次数

最后，评测程序示例输出：

* 第 $1 + 3 \cdot C$ 行：在 `longest_trip` 的所有调用中，函数 `are_connected` 被调用的最多次数


---

---
title: "[IOI 2023] 足球场"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9602
tag: ['2023', 'IOI', '交互题', 'Special Judge', 'O2优化']
---
# [IOI 2023] 足球场
## 题目背景

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。

本题仅支持 C++ 语言提交。
## 题目描述

Debrecen 市有一片正方形的森林名叫 Nagyerdő，可以看作是 $N \times N$ 的方格。
方格的行由北向南从 $0$ 到 $N - 1$ 编号，列由西向东从 $0$ 到 $N - 1$ 编号。
方格中第 $r$ 行第 $c$ 列的格子被称为单元格 $(r, c)$。

森林里的每个单元格要么是**空**的，要么是**有树**的。
森林里至少有一个空单元格。

DVSC 是这个城市最著名的体育俱乐部，目前正计划在森林里修建一座新的足球场。
大小为 $s$ 的球场（这里 $s \ge 1$）是 $s$ 个**互不相同的空**单元格 $(r_0, c_0), \ldots, (r_{s - 1}, c_{s - 1})$ 的集合。
形式化地说，这意味着：

- 对于从 $0$ 到 $s - 1$（包含两端）的每个 $i$，单元格 $(r_i, c_i)$ 是空的；
- 对于满足 $0 \le i \lt j \lt s$ 的每组 $i$ 和 $j$，$r_i \neq r_j$ 和 $c_i \neq c_j$ 二者中至少有一个成立。

踢球时足球在球场的单元格之间传递。
**直传**是以下两种动作之一：

* 球场包含第 $r$ 行中单元格 $(r,a)$ 和 $(r,b)$ 之间的**全部**单元格，球从单元格 $(r,a)$ 传递到单元格 $(r,b)$（$0 \le r,a,b \lt N, a \ne b$）。包含关系的形式化定义为：
  - 若 $a \lt b$，则球场应包含满足 $a \le k \le b$ 的每个单元格 $(r,k)$；
  - 若 $a \gt b$，则球场应包含满足 $b \le k \le a$ 的每个单元格 $(r,k)$。
* 球场包含第 $c$ 列中单元格 $(a,c)$ 和 $(b,c)$ 之间的**全部**单元格，球从单元格 $(a,c)$ 传递到单元格 $(b,c)$（$0 \le c,a,b \lt N, a \ne b$）。包含关系的形式化定义为：
  - 若 $a \lt b$，则球场应包含满足 $a \le k \le b$ 的每个单元格 $(k, c)$；
  - 若 $a \gt b$，则球场应包含满足 $b \le k \le a$ 的每个单元格 $(k, c)$。

如果可以通过至多 $2$ 次直传将球从球场的任意单元格传递到另外的任意单元格，那么称这样的球场是**规则**的。
注意，任何大小为 $1$ 的球场都是规则的。

例如，考虑一片大小为 $N = 5$ 的森林，其中单元格 $(1,0)$ 和 $(4,2)$ 有树，其余单元格均为空。
下图显示了三个可能的球场。有树的单元格用深色表示，组成球场的单元格划有斜线。

![](https://cdn.luogu.com.cn/upload/image_hosting/rhrk04xf.png)

左边的球场是规则的。然而，中间的球场不是规则的，原因是把球从单元格 $(4,1)$ 传递到单元格 $(4,3)$ 至少需要 $3$ 次直传。右边的球场也不是规则的，原因是无法通过直传将球从单元格 $(3,0)$ 传递到单元格 $(1,3)$。

体育俱乐部希望建造尽可能大的规则球场。
你的任务是找出最大的 $s$ 值，使得森林里可以建造大小为 $s$ 的规则球场。
## 输入格式

你要实现以下函数：

```
int biggest_stadium(int N, int[][] F)
```

* $N$：森林的大小。
* $F$：一个长度为 $N$ 的数组，每个元素都是长度为 $N$ 的数组，用于描述森林里的单元格。对于每组满足 $0 \le r \lt N$ 且 $0 \le c \lt N$ 的 $r$ 和 $c$，$F[r][c] = 0$ 表示单元格 $(r, c)$ 是空的，$F[r][c] = 1$ 表示该单元格是有树的。
* 这个函数应该返回森林里可以建造的规则球场的最大大小。
* 对于每个测试用例，这个函数恰好被调用一次。
## 输出格式

考虑以下调用：

```
biggest_stadium(5, [[0, 0, 0, 0, 0],  
                    [1, 0, 0, 0, 0], 
                    [0, 0, 0, 0, 0], 
                    [0, 0, 0, 0, 0], 
                    [0, 0, 1, 0, 0]])
```

这个例子描述的森林显示在下图的左边，一个大小为 $20$ 的规则球场显示在下图的右边：

![](https://cdn.luogu.com.cn/upload/image_hosting/c928srlk.png)

由于不存在大小为 $21$ 或更大的规则球场，函数应该返回 $20$。
## 提示

## 约束条件

* $1 \le N \le  2\,000$
* $0 \le F[i][j] \le 1$（对满足 $0 \le i \lt N$ 且 $0 \le j \lt N$ 的所有 $i$ 和 $j$）
* 森林里至少存在一个空单元格。也就是说，对于某组满足 $0 \le i \lt N$ 且 $0 \le j \lt N$ 的 $i$ 和 $j$，有 $F[i][j] = 0$。

## 子任务

1. （6 分）至多只有一个单元格有树。
2. （8 分）$N \le 3$
3. （22 分）$N \le 7$ 
4. （18 分）$N \le 30$ 
5. （16 分）$N \le 500$
6. （30 分）没有额外的约束条件。

在每个子任务中，如果你的程序能够正确判定**全部**空单元格组成的集合能否构成一个规则球场，那么你将在该子任务获得 25% 的部分分。

更准确地讲，对于所有空单元格组成的集合是一个规则球场的测试用例，你的解答的得分情况如下：

* 如果返回正确答案（也就是所有空单元格的数量），则得满分；
* 否则得 0 分。

对于所有空单元格组成的集合**不是**一个规则球场的测试用例，你的解答的得分情况如下：

* 如果返回正确答案，则得满分；
* 如果返回所有空单元格的数量，则得 0 分；
* 如果返回其他值，则得 25% 的分数。

每个子任务的得分是这个子任务中所有测试用例得分的最低值。

## 评测程序示例

评测程序示例按以下格式读取输入：

* 第 $1$ 行：$N$
* 第 $2 + i$ 行（$0 \le i \lt N$）：$F[i][0] \; F[i][1] \; \ldots \; F[i][N - 1]$

评测程序示例按以下格式打印你的答案：

* 第 $1$ 行：函数 `biggest_stadium` 的返回值


---

---
title: "[IOI 2023] 山毛榉树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9603
tag: ['2023', 'IOI', '交互题', 'Special Judge', 'O2优化']
---
# [IOI 2023] 山毛榉树
## 题目背景

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 main 函数。

本题仅支持 C++ 语言提交。
## 题目描述

Vétyem Woods 是一片著名的缤纷多彩的森林。其中最老最高的一棵山毛榉树叫 Ős Vezér。

树 Ős Vezér 可以被建模成 $N$ 个**结点**和 $N-1$ 条**边**的集合。结点的编号为从 $0$ 到 $N-1$，边的编号为从 $1$ 到 $N-1$。每条边均连接树上两个不同的结点。具体地说，边 $i$（$1 \le i \lt N$）从结点 $i$ 连接到结点 $P[i]$，这里 $0 \le P[i] \lt i$。结点 $P[i]$ 被称为是结点 $i$ 的**父结点**，而结点 $i$ 被称为是结点 $P[i]$ 的一个**子结点**。

每条边都有某种颜色。一共有 $M$ 种可能的颜色，编号为从 $1$ 到 $M$。边 $i$ 的颜色为 $C[i]$。不同的边可能有相同的颜色。

注意，在上面的定义中，$i = 0$ 的情形并不对应树上的边。方便起见，我们令 $P[0] = -1$ 和 $C[0] = 0$。

例如，假定 Ős Vezér 有 $N = 18$ 个结点和 $M = 3$ 种可能的颜色，以及 $17$ 条边。边的描述为 $P = [-1, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 10, 11, 11]$，边的颜色为 $C = [0, 1, 2, 3, 1, 2, 3, 1, 3, 3, 2, 1, 1, 2, 2, 1, 2, 3]$。这棵树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/xnxdhpz1.png)

Árpád 是一位才华横溢的护林人，他喜欢研究树上被称为**子树**的部分。
对所有满足 $0 \le r \lt N$ 的  $r$，结点 $r$ 的子树是一个满足以下性质的结点集合 $T(r)$：

* 结点 $r$ 属于 $T(r)$。
* 如果某个结点 $x$ 属于 $T(r)$，则 $x$ 的所有子结点都属于$T(r)$。
* 除了上述情况以外，其他结点都不属于 $T(r)$。

集合 $T(r)$ 的大小记作 $|T(r)|$。

Árpád 最近发现了一个复杂但有趣的子树性质。Árpád 的发现需要用到大量的纸和笔做演算，他认为你需要做同样的事情才能完成理解。他还会给你几个例子，让你能够对它们做详细的分析。

假设我们有某个给定的 $r$，以及子树 $T(r)$ 中结点的某个置换 $v_0, v_1, \ldots, v_{|T(r)|-1}$。

对于所有满足 $1 \le i \lt |T(r)|$ 的 $i$，令 $f(i)$ 为颜色 $C[v_i]$ 在长为 $i-1$ 的颜色序列 $C[v_1], C[v_2], \ldots, C[v_{i-1}]$ 中的出现次数。

（注意，$f(1)$ 必定为 $0$，原因是其定义中要考察的颜色序列是空的。）

置换 $v_0, v_1, \ldots, v_{|T(r)|-1}$ 被称为是一个**绝妙置换**，当且仅当以下性质成立：

* $v_0 = r$。
* 对于所有满足 $1 \le i \lt |T(r)|$ 的 $i$，结点 $v_i$ 的父结点是 $v_{f(i)}$。

对于所有满足 $0 \le r \lt N$ 的 $r$，子树 $T(r)$ 是一棵**绝妙子树**，当且仅当 $T(r)$ 中结点存在某个绝妙置换。注意，根据定义，仅包含单独一个结点的子树都是绝妙的。

考虑上面给出的树的例子。可以看到，子树 $T(0)$ 和 $T(3)$ 不是绝妙的。子树 $T(14)$ 是绝妙的，因为它仅包含一个结点。接下来，我们将要说明子树 $T(1)$ 也是绝妙的。

考虑一个由不同整数构成的序列 $[v_0, v_1, v_2, v_3, v_4, v_5, v_6] = [1, 4, 5, 12, 13, 6, 14]$。这个序列是 $T(1)$ 中结点的一个置换。下图给出了这个置换。序列中每个结点旁边的数字，是该结点在置换中的索引。

![](https://cdn.luogu.com.cn/upload/image_hosting/ziecuezc.png)

我们将要验证，这是一个**绝妙置换**。

* $v_0 = 1$。
* $f(1) = 0$，原因是 $C[v_1] = C[4] = 1$ 在序列 $[\,]$ 中出现了 $0$ 次。
 * 相应地，$v_1$ 的父结点是 $v_0$。也就是说，$4$ 的父结点是 $1$。（形式化地，$P[4] = 1$。）
* $f(2) = 0$，原因是 $C[v_2] = C[5] = 2$ 在序列 $[1]$ 中出现了 $0$ 次。
 * 相应地，$v_2$ 的父结点是 $v_0$。也就是说，$5$ 的父结点是 $1$。
* $f(3) = 1$，原因是 $C[v_3] = C[12] = 1$ 在序列 $[1, 2]$ 中出现了 $1$ 次。
 * 相应地，$v_3$ 的父结点是 $v_1$。也就是说，$12$ 的父结点是 $4$。
* $f(4) = 1$，原因是 $C[v_4] = C[13] = 2$ 在序列 $[1, 2, 1]$ 中出现了 $1$ 次。
 * 相应地，$v_4$ 的父结点是 $v_1$。也就是说，$13$ 的父结点是 4。
* $f(5) = 0$，原因是 $C[v_5] = C[6] = 3$ 在序列 $[1, 2, 1, 2]$ 中出现了 $0$ 次。
 * 相应地，$v_5$ 的父结点是 $v_0$。也就是说，$6$ 的父结点是 $1$。
* $f(6) = 2$，原因是 $C[v_6] = C[14] = 2$ 在序列 $[1, 2, 1, 2, 3]$ 中出现了  $2$ 次。
 * 相应地，$v_6$ 的父结点是 $v_2$。也就是说，$14$ 的父结点是 $5$。

由于我们能为 $T(1)$ 中的结点找到一个**绝妙置换**，子树 $T(1)$ 因此是一棵**绝妙子树**。

你的任务是，帮助 Árpád 确定 Ős Vezér 的每棵子树是否是绝妙的。
## 输入格式

你需要实现以下函数。

```
int[] beechtree(int N, int M, int[] P, int[] C)
```

* $N$：树中的结点数量。
* $M$：树中边的可能颜色的数量。
* $P$，$C$：长度为 $N$ 的两个数组，以描述树中的边。
* 该函数应当返回长度为 $N$ 的某个数组 $b$。 
  对所有满足 $0 \le r \lt N$ 的 $r$，如果 $T(r)$ 是绝妙的，则 $b[r]$ 应为 $1$，否则应为 $0$。
* 该函数在每个测试用例上恰好被调用一次。
## 提示



### 样例

#### 样例 1

考虑如下调用：

```
beechtree(4, 2, [-1, 0, 0, 0], [0, 1, 1, 2])
```

这棵树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/bcv1naft.png)

$T(1)$，$T(2)$ 和 $T(3)$ 均各自包含单独一个结点，因此都是绝妙的。
$T(0)$ 不是绝妙的。
因此，函数应当返回 $[0, 1, 1, 1]$。

#### 样例 2

考虑如下调用：

```
beechtree(18, 3, 
          [-1, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5, 10, 11, 11],
          [0, 1, 2, 3, 1, 2, 3, 1, 3, 3, 2, 1, 1, 2, 2, 1, 2, 3])
```

这个例子在题面中已经给出。

函数应当返回 $[0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]$。

#### 样例 3

考虑如下调用：

```
beechtree(7, 2, [-1, 0, 1, 1, 0, 4, 5], [0, 1, 1, 2, 2, 1, 1])
```

该例子如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/cv6ljl13.png)

$T(0)$ 是唯一不是绝妙的子树。函数应当返回 $[0, 1, 1, 1, 1, 1, 1]$。

### 约束条件

* $3 \le N \le 200\,000$
* $2 \le M \le 200\,000$
* $0 \le P[i] \lt i$（对于所有满足 $1 \le i \lt N$ 的 $i$）
* $1 \le C[i] \le M$（对于所有满足 $1 \le i \lt N$ 的 $i$）
* $P[0] = -1$ 且 $C[0] = 0$

### 子任务

1. （9 分）$N \le 8$ 且 $M \le 500$
1. （5 分）边 $i$ 从结点 $i$ 连接到结点 $i-1$。也就是说，对所有满足 $1 \le i \lt N$ 的 $i$，都有 $P[i] = i-1$。
1. （9 分）除了结点 $0$ 以外，其他结点要么连接到结点 $0$，要么连接到某个连接到结点 $0$ 的结点。
    也就是说，对于所有满足 $1 \le i \lt N$ 的 $i$，要么有 $P[i]=0$，要么有 $P[P[i]]=0$。
1. （8 分）对于所有满足 $1 \le c \le M$ 的 $c$，至多有两条边的颜色为 $c$。
1. （14 分） $N \le 200$ 且 $M \le 500$
1. （14 分） $N \le 2\,000$ 且 $M = 2$
1. （12 分） $N \le 2\,000$
1. （17 分） $M = 2$
1. （12 分） 没有额外的约束条件。

### 评测程序示例

评测程序示例按以下格式读取输入：

* 第 $1$ 行：$N \; M$
* 第 $2$ 行：$P[0] \; P[1] \; \ldots \; P[N-1]$
* 第 $3$ 行：$C[0] \; C[1] \; \ldots \; C[N-1]$

令 $b[0], \; b[1], \; \ldots$ 表示 `beechtree` 所返回的数组中的元素。评测程序示例以如下格式，在单行中输出你的答案：
* 第 $1$ 行：$b[0] \; b[1] \; \ldots$


---

---
title: "[IOI 2023] 机器人比赛"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9605
tag: ['2023', 'IOI', '交互题', 'Special Judge', 'O2优化']
---
# [IOI 2023] 机器人比赛
## 题目背景

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。

本题仅支持 C++ 语言提交。

---

由于某些技术原因，你可能需要在源代码的开头加入以下内容：

```cpp
#include <vector>

void program_pulibot();
void set_instruction(std::vector<int> S, int Z, char A);
```
## 题目描述

塞格德大学的人工智能研究人员正在举办一场机器人编程竞赛。
你的朋友 Hanga 决定参加比赛。由于著名的匈牙利牧羊犬品种 Puli 非常聪明，所以该比赛的目标定为编程实现顶级的 Pulibot。

Pulibot 将在由 $(H+2) \times (W+2)$ 网格组成的迷宫中进行测试。
网格的行从北到南编号为 $-1$ 到 $H$，网格的列从西到东编号为 $-1$ 到 $W$。
我们将位于网格的第 $r$ 行和第 $c$ 列的单元格（$-1 \le r \le H$, $-1 \le c \le W$）称为单元格 $(r,c)$。

考虑一个单元格 $(r,c)$ （$0 \le r \lt H$，$0 \le c \lt W$），和它**相邻**的有 $4$ 个单元格。

* 单元格 $(r,c-1)$ 被称为单元格 $(r,c)$ 的**西邻**；
* 单元格 $(r+1,c)$ 被称为单元格 $(r,c)$ 的**南邻**；
* 单元格 $(r,c+1)$ 被称为单元格 $(r,c)$ 的**东邻**；
* 单元格 $(r-1,c)$ 被称为单元格 $(r,c)$ 的**北邻**。

如果 $r=-1$ 或 $r=H$ 或 $c=-1$ 或 $c=W$ 成立，则单元格 $(r,c)$ 称为迷宫的**边界**。每个不是迷宫边界的单元格要么是**障碍**，要么是**空的**。
此外，每个空单元格都有一个**颜色**，由 $0$ 和 $Z_{\text{MAX}}$ 之间的非负整数表示，包括 $0$ 和 $Z_{\text{MAX}}$。最初，每个空单元格的颜色为 $0$。

例如，考虑一个迷宫，$H=4$， $W=5$， 包含一个障碍单元格 $(1,3)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/h649yqfv.png)

唯一的障碍单元格用 $\times$ 表示。迷宫的边界单元格被阴影覆盖。
每个空单元格中的数字表示它的颜色。

从单元格 $(r_0, c_0)$ 到单元格 $(r_\ell, c_\ell)$ 的长度为 $\ell$（$\ell\gt 0$）的**路径**
是一个**空**单元格序列 $(r_0,c_0), (r_1, c_1), \ldots, (r_\ell, c_\ell)$，序列中的空单元格两两不同。其中对于每个 $i$（$0\le i\lt\ell$），单元格 $(r_i, c_i)$ 和 $(r_{i+1}, c_{i+1})$ 是相邻的。

注意长度为 $\ell$ 的路径正好包含 $\ell+1$ 个单元格。

在比赛中，研究人员设置了一个迷宫，其中至少有一条从单元格 $(0,0)$ 到单元格 $(H-1, W-1)$ 的路径。注意，这意味着单元格 $(0, 0)$ 和 $(H-1, W-1)$ 保证为空。

Hanga 不知道迷宫中哪些单元格是空的，哪些单元格是障碍。

你的任务是帮助 Hanga 对 Pulibot 进行编程，使其能够在研究人员设置的未知迷宫中找到从单元格 $(0,0)$ 到单元格 $(H-1, W-1)$ 的**最短路径**（即长度最小的路径）。
Pulibot 的说明和比赛规则如下所述。 

注意，在题面的最后一部分描述了一个显示工具，该工具可以用于可视化 Pulibot。

### Pulibot 说明

对每个单元格 $(r,c)$（$-1 \le r \le H$ ，$-1 \le c \le W$），其**状态**定义为一个整数，具体如下：
* 如果单元格 $(r,c)$ 是边界，则其状态为 $-2$；
* 如果单元格 $(r,c)$ 是障碍，则其状态为 $-1$；
* 如果单元格 $(r,c)$ 是空的，那么它的状态就是单元格的颜色。

Pulibot 的程序是按一系列步骤执行的。在每一步中，Pulibot 都会识别附近单元格的状态，然后执行一条指令。它执行的指令由识别的状态决定。以下是更准确的描述。

假设在当前步骤开始时，Pulibot位于单元格 $(r,c)$，这是一个空单元格。该步骤执行如下：

1. 首先，Pulibot 识别当前**状态数组**，即数组 $S = [S[0], S[1], S[2], S[3], S[4]]$， 它包含单元格 $(r,c)$ 及其所有相邻单元格的状态：
    * $S[0]$ 表示单元格 $(r,c)$ 的状态。
    * $S[1]$ 表示西邻的状态。
    * $S[2]$ 表示南邻的状态。
    * $S[3]$ 表示东邻的状态。
    * $S[4]$ 表示北邻的状态。
1. 然后，Pulibot 确定与所识别的状态数组相对应的**指令** $(Z, A)$。
1. 最后，Pulibot 执行这条指令：它将单元格 $(r,c)$ 的颜色设置为 $Z$，然后它执行动作 $A$, $A$ 是以下动作之一：
    * **停留** 在单元格 $(r,c)$；
    * **移动** 到 $4$ 个邻居之一；
    * **终止程序**。

例如，考虑下图左侧显示的场景。Pulibot 当前位于单元格$(0,0)$，颜色为$0$。
Pulibot 识别出状态数组 $S=[0, -2, 2, 2, -2]$。Pulibot 可能有一个程序，该程序根据所识别的数组，将当前单元格的颜色设置为 $Z=1$，然后向东移动，如图的中间和右侧所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/pg2mek5q.png)

### 机器人比赛规则

* 在开始时，Pulibot 被放置在单元格 $(0,0)$ 并开始执行其程序。
* 不允许 Pulibot 移动到非空单元格。
* Pulibot 的程序必须在最多 $500\,000$ 步后终止。
* 在 Pulibot 的程序终止后，迷宫中的空单元格的着色满足以下要求：
  - 存在从 $(0,0)$ 到 $(H-1, W-1)$ 的最短路径，路径中包括的每个单元格的颜色为 $1$。
  - 所有其他空单元格的颜色为 $0$。
* Pulibot 可以在任何空单元格终止其程序。 
  

例如，下图显示了一个可能的迷宫，其中$H=W=6$。左侧显示了初始配置，右侧显示了程序终止后空单元格的一种可以接受的着色：

![](https://cdn.luogu.com.cn/upload/image_hosting/ry81lf6s.png)
## 输入格式

你要实现以下函数：

```
void program_pulibot()
```

* 这个函数应该产生 Pulibot 的程序。对于所有 $H$ 和 $W$ 的取值以及满足题目约束条件的任何迷宫，该程序应该都能正确工作。
* 对于每个测试用例，此函数只调用一次。

此函数可以调用以下函数来生成 Pulibot 的程序：

```
void set_instruction(int[] S, int Z, char A)
```

* $S$: 长度为 $5$ 的数组，用来描述状态数组
* $Z$: 表示颜色的非负整数
* $A$: 表示 Pulibot 动作的单个字符，具体如下:
    - `H`: 停留;
    - `W`: 移动到西邻;
    - `S`: 移动到南邻;
    - `E`: 移动到东邻;
    - `N`: 移动到北邻;
    - `T`: 终止程序。
* 调用此函数指示 Pulibot 在识别状态数组 $S$ 时应执行指令 $(Z, A)$。  

用相同的状态数组 $S$ 多次调用该函数将导致  `Output isn't correct` 的判定结果。

不需要对每个可能的状态数组 $S$ 调用 `set_instruction`。 但是，如果 Pulibot 后来识别出未设置指令的状态数组，你将得到 `Output isn't correct` 的判定结果。

`program_pulibot` 完成后，评测程序会在一个或多个迷宫上调用 Pulibot 的程序。
这些调用**不**计入解决方案的时间限制。
评测程序**不**是自适应的，也就是说，每个测试用例的迷宫集合都是预先确定的。

如果 Pulibot 在终止程序之前违反了任何机器人比赛规则，你将得到 `Output isn't correct` 的判定结果。
## 输出格式

函数 `program_pulibot` 可以调用 `set_instruction` 如下：

调用                             | 对应状态数组 $S$ 的指令
:-------------------------------------------:|:---------------------------------------:
`set_instruction([0, -2, -1, 0, -2], 1, E)`  | 着色 $1$ 并且东移
`set_instruction([0, 1, -1, 0, -2], 1, E)`   | 着色 $1$ 并且东移
`set_instruction([0, 1, 0, -2, -2], 1, S)`   | 着色 $1$ 并且南移
`set_instruction([0, -1, -2, -2, 1], 1, T)`  | 着色 $1$ 并且终止程序

考虑一个场景，$H=2$， $W=3$，迷宫如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/q5lifqvx.png)

对于这个特定的迷宫，Pulibot 的程序分四个步骤运行。 Pulibot 识别的状态数组和它执行的指令正好依次对应上述对“set_instruction”的四次调用。 这些指令的最后一条指令终止程序。

下图展示了四个步骤每一步之前的迷宫以及终止后的最终颜色。

![](https://cdn.luogu.com.cn/upload/image_hosting/n236hrg7.png)

但是，注意这个由 $4$ 条指令构成的程序有可能在其他合法的迷宫中找不到最短路径。
所以，如果这个程序被提交，它会收到 `Output isn't correct` 的判定结果。
## 提示

## 约束条件

$Z_{\text{MAX}} = 19$。因此，Pulibot 可以使用 0 到 19 的颜色，包含 0 和 19。

对于每个用来测试Pulibot的迷宫：
* $2 \le H, W \le 15$
* 至少有一条从单元格 $(0,0)$ 到 $(H-1, W-1)$ 的路径。

## 子任务

1. （6 分）迷宫中没有障碍单元格。
1. （10 分）$H = 2$
1. （18 分）任意两个空单元格之间恰好有一条路径。
1. （20 分）从单元格 $(0,0)$ 到 $(H-1, W-1)$ 的最短路径的长度为 $H + W - 2$。
1. （46 分）无额外约束条件。

如果在任何测试用例中，对函数 `set_instruction` 的调用或 Pulibot 程序的执行不符合“实现细节”中所描述的限制条件，则该子任务的解决方案得分将为 $0$。

在每个子任务中，你可以通过生成几乎正确的着色来获得部分分数。

形式化地说：

* 如果空单元格的最终颜色满足机器人竞赛规则，则测试用例的解决方案是**完整**的。
* 如果最终着色如下所示，则测试用例的解决方案是**部分**的：
   - 存在一条从 $(0,0)$ 到 $(H-1, W-1)$ 的最短路径，路径中包含的每个单元格的颜色为 $1$。
   - 网格中没有其他颜色为 $1$ 的空单元格。
   - 网格中的某些空单元格的颜色既不是 $0$ 也不是 $1$。
   

如果你对某个测试用例的解决方案既不完整也不部分，则该测试用例的得分将为 $0$。

在子任务 1-4 中，对每个测试用例来说，完整解决方案的计分为该子任务分数的 100%，部分解决方案的计分为该子任务分数的 50%。

在子任务 5 中，你的分数取决于 Pulibot 程序中所使用颜色的数量。
更准确地说，用 $Z^\star$ 表示对 `set_instruction` 进行的所有调用中 $Z$ 的最大值。
测试用例上的得分按下表计算：

| 条件            | 分数 (完整)      | 分数 (部分)       |
|:-----------------------:|:---------------------:|:---------------------:|
| $11 \le Z^\star \le 19$ | $20 + (19 - Z^\star)$ | $12 + (19 - Z^\star)$ |
| $Z^\star = 10$          | $31$                  | $23$                  |
| $Z^\star = 9$           | $34$                  | $26$                  |
| $Z^\star = 8$           | $38$                  | $29$                  |
| $Z^\star = 7$           | $42$                  | $32$                  |
| $Z^\star \le 6$         | $46$                  | $36$                  |


每个子任务的得分是该子任务中所有测试用例上计分的最小值。

## 评测程序示例

评测程序示例按照以下格式读取输入：
* 第 $1$ 行: $H \; W$
* 第 $2 + r$ 行 ($0 \le r \lt H$): $m[r][0] \; m[r][1] \; \ldots \; m[r][W-1]$

其中，$m$ 是一个 $H$ 行 $W$ 列的二维整数数组，描述迷宫中非边界单元格。
如果单元格 $(r, c)$ 是空的，$m[r][c] = 0$；如果单元格 $(r, c)$ 是障碍， $m[r][c] = 1$。



评测程序示例首先调用 `program_pulibot()`。如果评测程序示例检测到违反规则的行为，则会打印 `Protocol Violation: <MSG>` 并终止，其中 `<MSG>` 是以下错误消息之一：

* `Invalid array`：$-2 \le S[i] \le Z_{\text{MAX}}$ 对某些 $i$ 不成立或者 $S$ 的长度不是 $5$。
* `Invalid color`：$0 \le Z \le Z_{\text{MAX}}$ 不成立。
* `Invalid action`：字符 $A$ 不是 `H`, `W`, `S`, `E`, `N` 或 `T`。
* `Same state array`：用相同的 $S$ 调用 `set_instruction` 两次或以上。

否则，当 `program_pulibot` 完成时，评测程序示例将在输入所描述的迷宫中执行 Pulibot 的程序。

评测程序示例产生两个输出。首先，评测程序示例将 Pulibot 动作记录写入工作目录中的文件 `robot.bin` 。
该文件用作下一节中描述的可视化工具的输入。

其次，如果 Pulibot 的程序未成功终止，评测程序示例将打印以下错误消息之一：

* `Unexpected state`：Pulibot 识别出一个无法调用“set_instruction”的状态数组。
* `Invalid move`：执行一个动作，导致 Pulibot 移动到一个非空单元格。
* `Too many steps`：Pulibot 执行了 $500\,000$ 步没有终止程序。

否则，令 $e[r][c]$ 为 Pulibot 程序终止后单元格 $(r, c)$ 的状态。
评测程序示例按以下格式打印 $H$ 行：
* 第 $1 + r$ 行 ($0 \le r \lt H$)：$e[r][0] \; e[r][1] \; \ldots \; e[r][W-1]$

## 显示工具

此任务的附件包含有一个名为 `display.py` 的文件。
调用时，此 Python 脚本会显示 Pulibot 在由评测程序示例的输入所描述的迷宫中的操作。
为此，工作目录中要有二进制文件 `robot.bin`。

要调用该脚本，请执行以下命令。

```
python3 display.py
```

一个简单的图形界面将会出现，主要特性如下：

* 你可以观察整个迷宫的状态。 Pulibot 的当前位置以矩形突出显示。
* 你可以通过单击箭头按钮或按热键来浏览 Pulibot 的步骤。 你还可以跳转到特定步骤。
* Pulibot 程序中即将进行的步骤显示在底部。
它显示当前状态数组及将要执行的指令。
在最后一步之后，它或者会显示评测程序的错误消息之一，或者在程序成功终止时显示 `Terminated`。
* 对于代表颜色的每个数字，你可以指定视觉背景颜色以及显示的文本。 显示的文本是一个短字符串，应出现在每个具有那个颜色的单元格。你可以通过以下任一方式指定背景颜色和显示的文本：
   - 单击 `Colors` 按钮后在对话框窗口中设置它们。
   - 编辑 `colors.txt` 文件的内容。
* 要重新加载 `robot.bin`，请使用 `Reload` 按钮。 这可以用来处理 `robot.bin` 的内容发生更改的情况。


---

