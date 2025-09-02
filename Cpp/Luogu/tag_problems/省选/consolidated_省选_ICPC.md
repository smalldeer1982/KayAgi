---
title: "[ICPC 2024 Xi'an I] The Last Cumulonimbus Cloud"
layout: "post"
diff: 省选/NOI-
pid: P10559
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] The Last Cumulonimbus Cloud
## 题目描述

Every April, the city is always shrouded under cumulonimbus clouds.

This city is connected by $n$ buildings and $m$ two-way streets. In order to facilitate people's travel, any two buildings can directly or indirectly reach each other through the streets. At the same time, no street connects the same building, and there is at most one street that connects each pair of buildings.

The pace of life in this city is very slow because the city layout is not very bulky.

Specifically,if we consider this city as an undirected graph $G$ ,it is guaranteed that for any non empty subgraph in this graph,there is at least one building inside it that connects up to 10 streets within the subgraph.

The rain is not stopping, and the number of cumulonimbus clouds is constantly increasing. At the beginning, there are $a_i$ cumulonimbus clouds above the $i$ -th building, but in the following $q$ days, one of the following two events will occur every day:

- $\text{1 x v}$ $v$ cumulonimbus clouds have been added over the $x$ -th building.
- $\text{2 x}$ you need to report how many cumulonimbus clouds are in total over all buildings directly connected to building $x$.
## 输入格式

The first line contains three integers $n,m,q(1\le n\le 3\times 10^5,1\leq m\leq 3\times 10^6, 1\leq q\leq 2\times 10^6)$.

Each of the next $m$ lines contains two integers $x,y(1\leq x,y\leq n,x\neq y)$, which represents a street connecting the $x$ -th and $y$ -th buildings.

Each of the next $n$ lines contains an integer $a_i(0\leq a_i\leq 100)$.

Each of the next $q$ lines contains two or three integers, if the first integer is $1$, it represents a first type of event, and the next two integers represent $x,v(0\leq v\leq 100)$. If the first integer is $2$, it represents a second type of event, the next integer represents $x$.
## 输出格式

Several rows, each representing a query result for a second type of event.
## 样例

### 样例输入 #1
```
4 6 10
2 4
2 3
4 3
3 1
4 1
2 1
0
7
1
6
2 4
2 2
1 3 3
2 1
1 1 9
2 4
2 2
1 3 6
2 4
2 2
```
### 样例输出 #1
```
8
7
17
20
19
26
25
```
## 题目翻译

你有一个 $n(1\le n\le 3\times 10^5)$ 个点，$m(1\le m\le 3\times 10^6)$ 条边的无向图。

保证这个图的任意一个非空子图都至少有一个点的度数小于等于 $10$。

每个点初时有一个权值 $a_i$。

现在要执行 $q(1\le q\le 2\times 10^6)$ 次操作：

- $\text{1 x v}$ 给第 $x$ 个点的权值加 $v$。
- $\text{2 x}$ 询问第 $x$ 个点所有相邻的点的权值之和（不包括自己）。


---

---
title: "[ICPC 2024 Xi'an I] Holes and Balls"
layout: "post"
diff: 省选/NOI-
pid: P10560
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Holes and Balls
## 题目描述

You are given $n$ balls, the $i$ -th ball's value is $p_i$. It's guaranteed that $p_1,p_2,\dots,p_n$ is a permutation of $1,2,3\dots,n$.
    
    
    
There is also a rooted tree of $n$ vertices, each of the vertices is a hole, and each hole can only hold one ball.
    
    
    
The tree's root is the first vertex.
    
    
    
Now you need to fill the holes with the balls.
    
You need to throw each ball in order of $1$ to $n$ in the following steps:

1. Throw the ball into vertex $1$.
2. Let the vertex where the ball is be $p$.
3. If the $p$ -th vertex has already been filled with other balls, you need to choose a vertex $x$ and throw the ball into the $x$ -th vertex, then return to step $2$. You need to guarantee that the $x$ -th vertex is the $p$ -th vertex's son and at least one vertex in the subtree of the $x$ -th vertex is not filled.
4. Otherwise, the ball will fill the $p$ -th vertex.

After throwing all the balls, let $a_i$ express the value of the ball in the $i$ -th vertex.
    
    
    
You need to find the minimum lexicographical order of $\{a_n\}$.
    
    
    
We define $dep_i$ as the number of vertices on the path from the $i$ -th vertex to the tree's root(the first vertex).
    
    
    
Specially, for any two vertices $x<y$, it's guaranteed that $dep_x\le dep_y$.

## 输入格式

    
The first line contains a single integer $n(1\le n\le 5\times 10^5)$ - the number of vertices in this tree.
    
    
    
The next line contains $n$ numbers, the $i$ -th number is $p_i(1\le p_i\le n)$. It's guaranteed that $p_1,p_2,\dots,p_n$ is a permutation of $1,2,3\dots,n$.
    
    
    
The next $n-1$ lines contain a description of the tree's edges. The $i$ -th of these lines contains two integers $u_i$ and $v_i(1\le u_i,v_i\le n) $ - the numbers of vertices connected by the $i$ -th edge.
    
    
    
It is guaranteed that the given edges form a tree.
    
    
    
And for any vertices $x<y$, it's guaranteed that $dep_x\le dep_y$.
## 输出格式


Output $n$ integers, the minimum lexicographical order of $\{a_n\}$.
## 样例

### 样例输入 #1
```
5
3 1 5 4 2
1 2
2 3
3 4
4 5

```
### 样例输出 #1
```
3 1 5 4 2
```
### 样例输入 #2
```
9
9 2 6 3 5 7 1 4 8
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9

```
### 样例输出 #2
```
9 2 1 3 6 4 8 5 7
```


---

---
title: "[ICPC 2013 WF] Hey, Better Bettor"
layout: "post"
diff: 省选/NOI-
pid: P10616
tag: ['2013', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2013 WF] Hey, Better Bettor
## 题目背景

> “In the casino, the cardinal rule is to keep them playing and to keep them coming back. The
longer they play, the more they lose, and in the end, we get it all.”  
> (from the 1995 film *Casino*)
## 题目描述

Recent recessions have not been kind to entertainment venues, including the gambling industry. Competition is fierce among casinos to attract players with lots of money, and some have begun to offer especially sweet deals. One casino is offering the following: you can gamble as much as you want at the casino. After you are finished, if you are down by any amount from when you started, the casino will refund $x\%$ of your losses to you. Obviously, if you are ahead, you can keep all of your winnings. There is no time limit or money limit on this offer, but you can redeem it only once.

For simplicity, assume all bets cost $1$ dollar and pay out $2$ dollars. Now suppose $x$ is $20$. If you make $10$ bets in total before quitting and only $3$ of them pay out, your total loss is $3.2$ dollars. If $6$ of them pay out, you have gained $2$ dollars.

Given $x$ and the percentage probability $p$ of winning any individual bet, write a program to determine the maximum expected profit you can make from betting at this casino, using any gambling strategy.
## 输入格式

The input consists of a single test case. A test case consists of the refund percentage $x (0 \leq x < 100)$ followed by the winning probability percentage $p (0 \leq p < 50)$. Both $x$ and $p$ have at most two digits after the decimal point.
## 输出格式

Display the maximum expected profit with an absolute error of at most $10^{-3}$.
## 样例

### 样例输入 #1
```
0 49.9
```
### 样例输出 #1
```
0.0
```
### 样例输入 #2
```
50 49.85
```
### 样例输出 #2
```
7.10178453
```
## 题目翻译

**【题目描述】**

> “在赌场里，首要规则是让他们继续玩，让他们不断回来。他们玩得越久，输得越多，最终，我们会赢得一切。”  
> （摘自 1995 年电影《赌场》）

最近的经济衰退对包括赌博业在内的娱乐场所并不友好。赌场之间竞争激烈，以吸引有钱的玩家，一些赌场开始提供特别优厚的优惠。其中一个赌场提供以下优惠：你可以在赌场里随意赌博。当你结束时，如果你比开始时输了任何金额，赌场将退还你损失的 $x\%$。显然，如果你赢钱了，你可以保留所有的奖金。此优惠没有时间限制或金额限制，但你只能兑现一次。

为了简化，假设所有赌注的成本为 $1$ 美元，并支付 $2$ 美元。现在假设 $x$ 是 $20$。如果你在退出前总共下注 $10$ 次，只有 $3$ 次获胜，你的总损失是 $3.2$ 美元。如果 $6$ 次获胜，你就赚了 $2$ 美元。

给定 $x$ 和赢得任何单个赌注的概率百分比 $p$，编写一个程序来确定你在这个赌场下注所能获得的最大期望利润，使用任何赌博策略。

输入由一个单一的测试用例组成。测试用例包含退款百分比 $x (0 \leq x < 100)$，随后是赢得概率百分比 $p (0 \leq p < 50)$。$x$ 和 $p$ 的小数点后最多有两位数字。

显示最大期望利润，绝对误差不超过 $10^{-3}$。

**【输入格式】**

输入由一个单一的测试用例组成。测试用例包含退款百分比 $x (0 \leq x < 100)$，随后是赢得概率百分比 $p (0 \leq p < 50)$。$x$ 和 $p$ 的小数点后最多有两位数字。

**【输出格式】**

输出最大期望利润，绝对误差不超过 $10^{-3}$。

翻译来自于：[ChatGPT](https://chatgpt.com/)。



---

---
title: "[ICPC 2013 WF] Matryoshka"
layout: "post"
diff: 省选/NOI-
pid: P10622
tag: ['2013', 'O2优化', 'ICPC']
---
# [ICPC 2013 WF] Matryoshka
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/tsc2hi05.png)
## 题目描述

Matryoshkas are sets of traditional Russian wooden dolls of decreasing size placed one inside the other. A matryoshka doll can be opened to reveal a smaller figure of the same sort inside, which has, in turn, another figure inside, and so on.

The Russian Matryoshka Museum recently exhibited a collection of similarly designed matryoshka sets, differing only in the number of nested dolls in each set. Unfortunately, some over-zealous (and obviously unsupervised) children separated these sets, placing all the individual dolls in a row. There are $n$ dolls in the row, each with an integer size. You need to reassemble the matryoshka sets, knowing neither the number of sets nor the number of dolls in each set. You know only that every complete set consists of dolls with consecutive sizes from $1$ to some number $m$, which may vary between the different sets.

When reassembling the sets, you must follow these rules:
- You can put a doll or a nested group of dolls only inside a larger doll.
- You can combine two groups of dolls only if they are adjacent in the row.
- Once a doll becomes a member of a group, it cannot be transferred to another group or permanently separated from the group. It can be temporarily separated only when combining two groups.

Your time is valuable, and you want to do this reassembly process as quickly as possible. The only time-consuming part of this task is opening and subsequently closing a doll, so you want to minimize how often you do this. For example, the minimum number of openings (and subsequent closings) when combining group $[1, 2, 6]$ with the group $[4]$ is two, since you have to open the dolls with sizes $6$ and $4$. When combining group $[1, 2, 5]$ with the group $[3, 4]$, you need to perform three openings.

Write a program to calculate the minimum number of openings required to combine all disassembled matryoshka sets.
## 输入格式

The input consists of a single test case. A test case consists of two lines. The first line contains one integer $n (1 \leq n \leq 500)$ representing the number of individual dolls in the row. The second line contains $n$ positive integers specifying the sizes of the dolls in the order they appear in the row. Each size is between $1$ and $500$ inclusive.
## 输出格式

Display the minimum number of openings required when reassembling the matryoshka sets. If reassembling cannot be done (some of the kids might have been excessively zealous and taken some dolls), display the word `Impossible`.
## 样例

### 样例输入 #1
```
7
1 2 1 2 4 3 3
```
### 样例输出 #1
```
Impossible
```
### 样例输入 #2
```
7
1 2 3 2 4 1 3

```
### 样例输出 #2
```
7
```
## 题目翻译

**【题目描述】**

套娃是俄罗斯传统木制玩具，由一组逐渐变小的娃娃组成，依次放置在另一个娃娃内部。一个套娃可以打开，露出一个更小的类似玩偶，而这个玩偶内部又有另一个玩偶，以此类推。

俄罗斯套娃博物馆最近展出了一系列设计相似的套娃，不同之处仅在于每套娃娃中嵌套的数量不同。不幸的是，一些过于热心（显然没有得到监督）的孩子把这些套娃拆散了，并将所有的单个娃娃排成一行。现在这一行中有 $n$ 个娃娃，每个都有一个整数大小。你需要重新组装这些套娃，既不知道套娃的数量，也不知道每套娃娃中娃娃的数量。你只知道每套完整的套娃由大小从 $1$ 到某个数字 $m$ 的连续大小的娃娃组成，而这个数字 $m$ 在不同的套娃中可能有所不同。

在重新组装套娃时，你必须遵循以下规则：
- 你只能将一个娃娃或一个嵌套的娃娃组放入一个更大的娃娃中。
- 你只能合并两个在行中相邻的娃娃组。
- 一旦一个娃娃成为一个组的成员，它不能被转移到另一个组或永久地从组中分离。它只能在合并两个组时暂时分离。

你的时间非常宝贵，你希望尽快完成这个重新组装过程。这个任务中唯一耗时的部分是打开和随后关闭一个娃娃，因此你希望尽量减少这样的操作次数。例如，当将组 $[1, 2, 6]$ 与组 $[4]$ 合并时，最少需要进行两次开关操作，因为你必须打开大小为 $6$ 和 $4$ 的娃娃。而当将组 $[1, 2, 5]$ 与组 $[3, 4]$ 合并时，需要进行三次开关操作。

编写一个程序计算重新组装所有拆散的套娃所需的最少开关次数。

**【输入格式】**

输入包含一个测试用例。测试用例由两行组成。第一行包含一个整数 $n (1 \leq n \leq 500)$，表示行中单个娃娃的数量。第二行包含 $n$ 个正整数，按照它们在行中出现的顺序指定娃娃的大小。每个大小在 $1$ 到 $500$ 之间（包括 $1$ 和 $500$）。

**【输出格式】**

输出重新组装套娃所需的最少开关次数。如果重新组装无法完成（可能有些孩子过于热心，带走了一些娃娃），则输出 `Impossible`。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[SEERC 2020] Archeologists"
layout: "post"
diff: 省选/NOI-
pid: P10736
tag: ['贪心', '2020', 'ICPC']
---
# [SEERC 2020] Archeologists
## 题目描述

你在玩一个寻宝类游戏，一共有 $n$ 个格子，编号为 $1 \sim n$，你每在 $i$ 号格子上下挖一层便会获得 $p_i$ 的价值，其中你需要保证每个格子相邻的两个格子都与其下挖的深度的差值不超过 $1$（注意此时 $1$ 和 $n$ 号点最多只能挖一层），请最大化总价值。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 2.5 \times 10^5)$。

接下来一行 $n$ 个整数 $p_i\ (-10^6 \leq p_i \leq 10^6)$。
## 输出格式

输出最大价值。
## 样例

### 样例输入 #1
```
5
1 3 -4 2 1

```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4
1 1 -2 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
5
-1 -3 0 -5 -4

```
### 样例输出 #3
```
0
```
## 提示

样例一解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/jalyemdz.png)


---

---
title: "[SEERC 2020] 3-colorings"
layout: "post"
diff: 省选/NOI-
pid: P10738
tag: ['2020', 'Special Judge', 'ICPC']
---
# [SEERC 2020] 3-colorings
## 题目描述

**这是一道仅有输出的题。**

定义一个图的有效“三色”染色为：

- 每个点的颜色只能属于 $\{1,2,3\}$。

- 对于每个有边相连的顶点 $(u,v)$，$u$ 的颜色需要与 $v$ 不同。

可以证明，一个图最多的“三色”染色总数为 $3^n$ 种。

现在你需构造一个图，一开始它存在 $n \ (1 \leq n \leq 19)$ 个顶点 $m \ (1 \leq m \leq \frac{n(n-1)}{2})$ 条无向边，然后对于每个 $1 \leq k \leq 500$ 的 $k$，你可以添加至多 $17$ 条无向边使得此图的“三色”染色总数为 $6k$ 种。
## 输入格式

无。
## 输出格式

第一行 $n,m$，表示你构造图的点数和边数。

然后 $m$ 行，一行两个整数 $u,v$，表示 $(u,v)$ 存在一条无向边。

然后 $k$ 从 $1$ 到 $500$，每个 $k$ 输出你要添加的边数，然后再是对应行添加的边 $(u,v)$。
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```
3 2
1 2
2 3
1
1 3
0
```
## 提示

样例仅给出 $k=1$ 和 $k=2$ 的示例。


---

---
title: "[SEERC 2020] Simple Hull"
layout: "post"
diff: 省选/NOI-
pid: P10742
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Simple Hull
## 题目描述

Gary 创造了一个含有 $n$ 个点的多边形，每个点的坐标形如 $(x,y)$。

你需要进行一些连边，保证包含所有的点，同时连出来的图是一条“多边形链”（即任何一个点只能连向或被连向 $2$ 个点，且连出来的边可以在图中与其他边相交）。

你还需要保证每两个存在连边的点 $i$ 和 $j$，这两个点形成的边在图中是垂直或水平的。

输出连出来的图的最小面积。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 10^5)$，表示点的个数。

然后 $n$ 行，每行两个整数 $x_i,y_i\ (1 \leq x_i,y_i \leq 10^6)$。
## 输出格式

输出连出的 $n$ 边形的面积。
## 样例

### 样例输入 #1
```
6
1 1
6 1
6 11
11 11
11 6
1 6
```
### 样例输出 #1
```
50
```
### 样例输入 #2
```
8
2 4
2 1
4 1
4 3
1 3
1 2
3 2
3 4
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
10
1 1
1 5
4 5
4 3
2 3
2 4
1 4
1 2
4 2
4 1
```
### 样例输出 #3
```
8
```
## 提示

三个样例画出的图依次为：

![](https://cdn.luogu.com.cn/upload/image_hosting/r9x5s5zy.png)

（上述图未按比例画图）


---

---
title: "[SEERC 2020] AND = OR"
layout: "post"
diff: 省选/NOI-
pid: P10743
tag: ['2020', 'ICPC']
---
# [SEERC 2020] AND = OR
## 题目描述

一个数组 $b$ 被称为“好的数组”当且仅当可以将 $b$ 划分为两个非空的子数组，这两个子数组中第一个子数组的 $\mathtt{OR}$ 结果与第二个子数组的 $\mathtt{AND}$ 结果相等，例如 $\{1,7,3,11\}$，将其划分为 $\{1,3\}$ 与 $\{7,11\}$，$1\ \mathtt{OR}\ 3 = 3$，$7\ \mathtt{AND}\ 11 = 3$，所以它是一个好的数组。

现在给定一个长度为 $n$ 的数组 $a$，$q$ 组询问，每次给定 $[l,r]$，为 $\{a_l, a_{l+1},\ldots,a_{r-1},a_{r}\}$ 是不是一个好的数组。
## 输入格式

第一行两个整数 $n\ (1 \leq n \leq 10^5)$ 和 $q\ (1 \leq q \leq 10^5)$。

然后一行 $n$ 个整数表示序列 $a\ (0\leq a_i \leq 2^{30}-1)$。

接下来 $q$ 行，一行两个整数 $l,r\ (1 \leq l \leq r \leq n)$，表示一组询问。
## 输出格式

对于每个询问，如果该子数组是好的输出 `YES`，否则输出 `NO`。
## 样例

### 样例输入 #1
```
5 15
0 1 1 3 2
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5
```
### 样例输出 #1
```
NO
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
NO
NO
NO
```


---

---
title: "[SEERC 2020] One Piece"
layout: "post"
diff: 省选/NOI-
pid: P10745
tag: ['2020', 'ICPC']
---
# [SEERC 2020] One Piece
## 题目描述

有一个图，它是一个 $n$ 个点的树，每条边都是形如 $(u,v)$ 的边长为 $1$ 的无向边。

你有一个寻宝器，当你在点 $i$ 时，它会返回一个最远距离 $x$，表示存在宝藏的位置距 $i$ 点最远长度为 $x$，一个图可能存在多个宝藏。

现在你知道了对于 $1 \leq i \leq n$ 时的寻宝器返回结果，问你确定每个点是否存在宝藏的概率从大到小依次排序后的数组。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 2.5 \times 10^5)$，表示点数。

接下来 $n-1$ 行，每行两个整数 $u,v$，表示一条边。

再一行 $n$ 个数，表示在 $i$ 点调用寻宝器的返回值。
## 输出格式

输出每个点是否存在宝藏的概率从大到小依次排序后的数组。

同概率下标升序排序。
## 样例

### 样例输入 #1
```
5
1 2
1 3
2 4
2 5
2 2 3 3 3
```
### 样例输出 #1
```
3 4 5 1 2
```
### 样例输入 #2
```
4
2 1
3 2
3 4
1 0 1 2
```
### 样例输出 #2
```
2 1 3 4
```


---

---
title: "[SEERC 2020] Codenames"
layout: "post"
diff: 省选/NOI-
pid: P10746
tag: ['2020', 'Special Judge', 'ICPC']
---
# [SEERC 2020] Codenames
## 题目描述

有 $q$ 个 $5 \times 5$ 的图表，给出每个点的颜色（只可能是 `r`、`b`、`n`、`x`），具体颜色分配为：$9$ 个 `r`，$8$ 个 `b`，$5$ 个 `n`，一个 `x`。

图表中每个点对应的字符始终确定，分别为：

```
abcde
fghij
klmno
pqrst
uvwxy
```

图表中某些颜色已经翻开来了（用其颜色的大写字母表示已显示），然后你需要从一个 $n$ 个字符串的列表内选择一个字符串 $w$ 和一个数字 $g$，按下述规则进行操作 $g$ 次。

- 如果当前 $w_i$ 字符代表的格子颜色已经被公示，不进行操作，令 $i \gets i + 1$。
- 否则，翻开 $w_i$ 代表的格子，如果 $w_i$ 的颜色为 `n`、`b` 或 `x`，就输了。然后再令 $i \gets i+1$。
- 当 $g$ 次操作完成或所有 `r` 色块都翻出来时结束操作。

你想要使得所有 `r` 色块都翻出来，求一组满足条件的 $w$ 与 $g$。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 10^5)$。

然后 $n$ 行，每行一个字符串，描述了一整个字符串列表。

第 $n+2$ 行，整数 $q\ (1 \leq q \leq 10^5)$，表示表格个数。

然后 $q$ 组图表，每个图表占据 $5 \times 5$ 的大小，描述了第 $i$ 个图表的颜色。
## 输出格式

对于每个图表，如果有解，输出一组合法的 $w$ 和 $g\ (1 \leq g \leq 9)$，无解输出 `IMPOSSIBLE`。
## 样例

### 样例输入 #1
```
3
actor
cheat
zeta
1
rBBnR
NRnbB
nRRnR
NRxBr
nBRbB
```
### 样例输出 #1
```
actor 2
```
## 提示

答案还可能是 `actor 4`，`zeta 2` 等。


---

---
title: "[SEERC 2020] Neo-Robin Hood"
layout: "post"
diff: 省选/NOI-
pid: P10747
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Neo-Robin Hood
## 题目描述

你是一个大盗，镇上一共有 $n$ 户人家，对于每户人家 $i$，你在如下的选择里选一样。

- 盗窃他的 $m_i$ 元钱，他会对你起仇恨。

- 给他 $p_i$ 元钱，他会让你盗窃的一个人取消对你的仇恨。

- 什么也不做。

初始时你没有钱，你想知道，在没人对你有仇恨且你手中的钱非负的情况下，你最多能盗窃多少户人家。

注：你可以按任意顺序依次访问每户人家。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 10^5)$。

第二行一个长度为 $n$ 的序列 $m\ (1 \leq m_i \leq 10^9)$。

第三行一个长度为 $n$ 的序列 $p\ (1 \leq p_i \leq 10^9)$。
## 输出格式

输出最多能盗窃的人家数。
## 样例

### 样例输入 #1
```
5
2 3 4 5 6
1 2 3 4 5
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
4
1 2 4 2
5 6 9 7

```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4
9 19 6 5
20 3 16 19

```
### 样例输出 #3
```
1
```


---

---
title: "[EC Final 2020] Random Shuffle"
layout: "post"
diff: 省选/NOI-
pid: P10818
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2020] Random Shuffle
## 题目描述

Prof. Pang is selecting teams that advance to the world final contest. As the regionals are cancelled, he uses random shuffle to rank the teams. There are $n$ teams in total. His code is as follows: 

```cpp
uint64_t x;//uint64_t represents 64-bit unsigned integer
int n;
uint64_t rand() {//this is a xor-shift random generator
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
int main() {
    cin >> n;
    cin >> x;
    for (int i = 1; i <= n; i++) {//random shuffle [1, 2,..., n]
        a[i] = i;
        swap(a[i], a[rand() % i + 1]);
    }
    for (int i = 1; i <= n; i++) {//print the result
        cout << a[i] << (i == n ? '\n' : ' ');
    }
}
```


He compiled and ran his code and then entered $n$ and some special nonnegative integer $x$. He printed the result on paper.

One day later, Prof. Pang forgot his choice for $x$. You are given the result of the code and the integer $n$. Please recover the number $x$ that Prof. Pang had entered. 
## 输入格式

The first line contains a single integer $n$ ($50\le n\le 100000$) -- the number of teams. 

The next line contains $n$ integers -- the result printed by Prof. Pang's code. It is guaranteed that the result is correct, i.e., there exists an integer $x$ ($0\le x\le 2^{64}-1$) that leads to the result. 
## 输出格式

Output the integer $x$ ($0\le x\le 2^{64}-1$) Prof. Pang had entered. If there are multiple possible $x$'s, print any one.
## 样例

### 样例输入 #1
```
50
36 22 24 21 27 50 28 14 25 34 18 43 47
13 30 7 10 48 20 16 29 9 8 15 3 31 12
38 19 49 37 1 46 32 4 44 11 35 6 33 26
5 45 17 39 40 2 23 42 41
```
### 样例输出 #1
```
16659580358178468547
```
## 提示

Note that the second line of the sample input is wrapped to fit in the width of page.


---

---
title: "[EC Final 2020] Prof. Pang's sequence"
layout: "post"
diff: 省选/NOI-
pid: P10822
tag: ['2020', 'O2优化', 'ICPC']
---
# [EC Final 2020] Prof. Pang's sequence
## 题目描述

Prof. Pang is given a fixed sequence $a_1, \ldots, a_n$ and $m$ queries.

Each query is specified by two integers $l$ and $r$ satisfying $1\le l\le r\le n$. For each query, you should answer the number of pairs of integers $(i, j)$ such that $l\le i\le j\le r$ and the number of distinct integers in $a_i, \ldots, a_j$ is odd.
## 输入格式

The first line contains a single integer $n$ ($1\le n\le 5\times 10^5$).

The next line contains $n$ integers $a_1, \ldots, a_n$ ($1\le a_i\le n$ for all $1\le i\le n$) separated by single spaces.

The next line contains a single integer $m$ ($1\le m\le 5\times 10^5$).

Each of the next $m$ lines contains two integers $l$ and $r$ ($1\le l\le r\le n$) separated by a single space denoting a query.
## 输出格式

For each query, output one line containing the answer to that query.
## 样例

### 样例输入 #1
```
5
1 2 3 2 1
5
1 5
2 4
1 3
2 5
4 4
```
### 样例输出 #1
```
10
3
4
6
1
```
### 样例输入 #2
```
5
2 3 5 1 5
5
2 3
1 1
1 3
2 5
2 4
```
### 样例输出 #2
```
2
1
4
6
4
```
### 样例输入 #3
```
10
2 8 5 1 10 5 9 9 3 5
10
6 8
1 2
3 5
5 7
1 7
3 9
4 9
1 4
3 7
2 5
```
### 样例输出 #3
```
4
2
4
4
16
16
12
6
9
6
```


---

---
title: "[NERC2024] Geometric Balance"
layout: "post"
diff: 省选/NOI-
pid: P12098
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Geometric Balance
## 样例

### 样例输入 #1
```
1
draw 10
```
### 样例输出 #1
```
180
```
### 样例输入 #2
```
7
draw 1
rotate 90
draw 1
rotate 90
draw 1
rotate 90
draw 1
```
### 样例输出 #2
```
90
```
### 样例输入 #3
```
3
draw 1
move 1
draw 2
```
### 样例输出 #3
```
360
```


---

---
title: "[NERC2024] Incompetent Delivery Guy"
layout: "post"
diff: 省选/NOI-
pid: P12100
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Incompetent Delivery Guy
## 样例

### 样例输入 #1
```
5 7
1 3 5
4 5 2
3 4 3
1 5 9
4 2 8
5 2 11
3 5 5
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 6
1 2 5
2 3 9
1 4 11
2 1 1000000
5 3 15
5 6 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
4 7
1 2 5
1 1 30
3 2 9
1 4 11
1 4 16
2 1 1000000
1 4 11
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
2 0
```
### 样例输出 #4
```
-1
```
### 样例输入 #5
```
6 7
1 2 5
2 3 9
1 6 11
2 1 1000000
1 5 9
5 6 2
5 4 4
```
### 样例输出 #5
```
1
```
### 样例输入 #6
```
4 4
1 4 6
1 3 2
3 2 3
3 4 4
```
### 样例输出 #6
```
1
```
### 样例输入 #7
```
3 2
1 2 1
1 3 1
```
### 样例输出 #7
```
0
```


---

---
title: "[NERC2024] Knowns and Unknowns"
layout: "post"
diff: 省选/NOI-
pid: P12102
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Knowns and Unknowns
## 题目描述

Two math professors have office hours on the same day. Students visit each professor to present their assignment solutions, one by one. For the whole semester, both professors established some fixed order of the students in which they should visit the professor. There are $n$ students denoted with integers from $1$ to $n$. Each professor's order of students is a permutation of numbers from $1$ to $n$.

Today only some of the students visited the university; let $A$ be the set of numbers that denote the students that were at the university today. All of the students from the set $A$ have visited both professors, and all of the students outside of the set $A$ haven't visited any professor.

Each of the professors made a list of the students they have talked with, in the same order the students have visited. Note that the list has to correspond to the order the professor has established, with the only difference that the students outside of the set $A$ are missing in it. It is the beginning of the year, so the professors didn't have a chance to get to know every student. So for the students that a professor knows, the list contains their identifier, but for those that the professor doesn't know, the list contains $-1$.

Consider an example: the first professor's order is $[1, 2, 3, 4]$, and the second professor's --- $[3, 2, 4, 1]$. The list made by the first professor today is $[1, -1, -1]$, and the list made by the second professor is $[3, -1, 1]$. Based on the lists, we can immediately see that three students have visited the university today. We can infer that the set $A$ was either $\{1, 2, 3\}$ or $\{1, 3, 4\}$.

You are given two permutations --- the orders established by each professor; you are also given two lists that professors made today. Your task is to help the professors. Based on the provided data, determine for each student whether they definitely visited the university, definitely did not, or whether this cannot be determined. Note that professors could have confused the students, so there is a possibility that the given data is inconsistent.
## 输入格式

The first line contains a single integer $T$ ($T \ge 1$) --- the number of test cases to solve.

Then the description of test cases follows.

The first line of the test case contains a single integer $n$ --- the number of students ($1 \le n \le 2000$).

The second line of the test case contains $n$ distinct integers $p_{1, 1}, p_{1, 2}, \ldots, p_{1, n}$ --- the order established by the first professor, meaning that student $p_{1, 1}$ comes first, and $p_{1, n}$ comes last ($1 \le p_{1, i} \le n$).

The third line of the test case contains $n$ distinct integers $p_{2, 1}, p_{2, 2}, \ldots, p_{2, n}$ --- the order established by the second professor in the same format ($1 \le p_{2, i} \le n$).

The fourth line of the test case contains an integer $k$ --- the number of students that visited the university today ($1 \le k \le n$).

The fifth line of the test case contains $k$ integers $s_{1, 1}, s_{1, 2}, \ldots, s_{1, k}$ --- the first professor's list. Each student appears in the list at most once ($s_{1, i} = -1$ or $1 \le s_{1, i} \le n$).

The sixth line of the test case contains $k$ integers $s_{2, 1}, s_{2, 2}, \ldots, s_{2, k}$ --- the second professor's list in the same format ($s_{2, i} = -1$ or $1 \le s_{2, i} \le n$).

The total sum of $n$ in all $T$ test cases doesn't exceed 2000.
## 输出格式

For each test case, output a single string. If the given data is inconsistent, print a single word $\tt{Inconsistent}$. Otherwise, print a string consisting of $n$ characters, the $i$-th of which is $\tt{Y}$ if the $i$-th student visited the university today, $\tt{N}$ if the $i$-th student didn't visit the university today, or $\tt{?}$ if it cannot be determined.
## 样例

### 样例输入 #1
```
2
4
1 2 3 4
3 2 4 1
3
1 -1 -1
3 -1 1
4
1 2 3 4
3 2 4 1
3
1 -1 2
3 -1 1
```
### 样例输出 #1
```
Y?Y?
Inconsistent
```
### 样例输入 #2
```
2
3
1 2 3
2 1 3
2
-1 2
-1 -1
3
1 2 3
3 2 1
2
1 3
2 -1
```
### 样例输出 #2
```
YYN
Inconsistent
```


---

---
title: "[NERC2024] Managing Cluster"
layout: "post"
diff: 省选/NOI-
pid: P12104
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Managing Cluster
## 题目描述

You want to write a cluster manager extension that will improve your product performance. Your product has $n$ services (numbered from $1$ to $n$) and is hosted on a cluster with $2n$ machines (numbered from $1$ to $2n$). Each service is running in exactly two replicas. Each replica is run on some machine. Each machine runs exactly one replica of some service.

One of the key factors of this cluster's performance is the network. Some pairs of machines are connected directly and can transfer data between them very efficiently. There are exactly $2n-1$ direct connections, and it is possible to transfer data between any two machines using direct connections. In other words, direct connections form a tree.

During the deployment, all $2n$ replicas were assigned to machines. Your extension gets the direct connections list and the sequence $a_1, a_2, \ldots, a_{2n}$, where $a_i$ is the number of the service that will be running on machine $i$. Your extension can swap some replicas between machines. The swap operation takes two machines $i$, $j$ and swaps values $a_i$ and $a_j$. Each machine is allowed to participate in at most one swap operation. Your extension should make some swap operations that maximize the cluster performance.

Due to the fact that most data will be transferred between two replicas of the same service, the cluster performance is measured as the number of services that have two replicas running on machines connected directly. Help to write the extension that will maximize the cluster performance.
## 输入格式

The first line contains a single integer $T$ ($1 \leq T \leq 10^5$) --- the number of test cases. Descriptions of test cases follow.

The first line of each test case contains a single integer $n$ ($1 \leq n \leq 10^5$).

The second line contains $2n$ integers $a_1, a_2, \ldots, a_{2n}$ ($1 \leq a_i \leq n$). It is guaranteed that each value from $1$ to $n$ appears exactly twice in this sequence.

Each of the next $2n-1$ lines contains two integers $u$ and $v$ ($1 \leq u, v \leq 2n$, $u \neq v$), meaning that machines $u$ and $v$ are connected directly. Direct connections are guaranteed to form a tree.

It is guaranteed that the sum of $n$ for all test cases does not exceed $10^5$.
## 输出格式

For each test case on the first line print a single integer $k$ ($0 \leq k \leq n$) --- the number of swap operations the extension wants to make.

Each of the next $k$ lines should contain two integers $i$, $j$ ($1 \leq i, j \leq 2n$, $i \neq j$) --- swap operations. Each number from $1$ to $2n$ should appear at most once.

Note that the order of operations is not important. After applying swap operations, the cluster performance should be the maximum possible. You can print any answer that satisfies the requirements.
## 样例

### 样例输入 #1
```
3
2
1 2 2 1
1 2
2 3
3 4
4
4 3 1 3 2 4 1 2
1 2
3 1
3 4
5 1
5 6
2 7
2 8
3
1 1 2 2 3 3
1 2
1 3
1 4
1 5
1 6
```
### 样例输出 #1
```
1
1 3
3
1 5
8 3
4 7
0
```
## 提示

In the first test case only replicas of service 2 run on directly connected machines, so the performance is 1. The performance can be increased to 2 by swapping replicas between machines 1 and 3.

In the second test case no two replicas run on directly connected machines, so the performance is zero. The performance can be increased to 3 by performing swaps $1-5$, $8-3$, and $4-7$ so that replicas of services 2, 3, and 4 run on directly connected machines. It can be shown that it is impossible to get performance 4 here. 

In the third test case only replicas of service 1 run on directly connected machines, so the performance is 1. It is obvious that here the performance cannot be made any bigger.


---

---
title: "[NWRRC2024] Capybara Cozy Carnival"
layout: "post"
diff: 省选/NOI-
pid: P12107
tag: ['动态规划 DP', '2024', '分治', '矩阵加速', '组合数学', 'ICPC', '俄罗斯西北']
---
# [NWRRC2024] Capybara Cozy Carnival
## 题目描述

Chilling capybaras celebrate Capybara Cozy Carnival. Chairman capybara cuts convex cake. Cake contains $n$ colorful corners. Countless colors comprise $k$ choices. Creating $m$ continuous crossing-free corner-to-corner cuts, chairman cuts cake chunks, catering $m + 1$ comrades. Curiously, consecutive cake chunks corners contain contrasting colors. 

Calculate cake corners color combinations, considering cuts conditions.

In other words, you are given a cake in the shape of a regular $n$-sided polygon and $m$ non-intersecting diagonal cuts, which divide it into $m + 1$ slices.

Calculate the number of ways to color each corner of the original cake with one of the $k$ colors, such that no two neighboring corners of the resulting slices have the same color. Two corners are considered neighboring if they are either consecutive in the original cake, or they are the endpoints of the same cut. It is not necessary to use all the colors. As the number of ways might be large, find it modulo $998\,244\,353$.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains three integers $n$, $m$, and $k$, denoting the number of cake corners, the number of cuts, and the number of available colors ($3 \le n \le 10^9$; $0 \le m \le 2\cdot 10^5$; $2 \le k \le 10^6$).

The $i$-th of the following $m$ lines contains two integers $u_i$ and $v_i$, denoting the corners connected by the $i$-th cut ($1 \le u_i < v_i \le n$). No two cuts may coincide or intersect except at the ends of the cuts. All cuts are straight, going strictly inside the cake.

It is guaranteed that the sum of $m$ over all test cases does not exceed $2\cdot 10^5$.
## 输出格式

For each test case, print the number of ways to color the cake corners such that no two neighboring corners have the same color, modulo $998\,244\,353$. Remember that you don't have to use all the colors.
## 样例

### 样例输入 #1
```
4
4 1 3
1 3
5 0 2
9 4 3
1 3
1 6
4 6
6 8
3 0 1001
```
### 样例输出 #1
```
6
0
54
1754647
```


---

---
title: "[NWRRC2024] Longest Common Substring"
layout: "post"
diff: 省选/NOI-
pid: P12116
tag: ['动态规划 DP', '2024', '快速莫比乌斯变换 FMT', 'ICPC', '状压 DP', '俄罗斯西北']
---
# [NWRRC2024] Longest Common Substring
## 样例

### 样例输入 #1
```
2 2 1
1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 4 2
01
```
### 样例输出 #2
```
28
```
### 样例输入 #3
```
7 5 3
110
```
### 样例输出 #3
```
399
```
### 样例输入 #4
```
23 42 3
000
```
### 样例输出 #4
```
174497840
```


---

---
title: "[ICPC 2023 WF] Schedule"
layout: "post"
diff: 省选/NOI-
pid: P12296
tag: ['2023', 'ICPC']
---
# [ICPC 2023 WF] Schedule
## 题目描述

The Institute for Creative Product Combinations (ICPC) tries to find unusual and innovative ways to unite seemingly unrelated products or technologies, opening up new markets and creating new jobs. (For instance, their most recent success was the "hairbachi," a hair-dryer with a hibachi grill top attachment for preparing on-the-go hot meals.) The company employs $n$ teams of size $2$ to research individual products, then members of the different teams get together to explore ways of combining products.

During the pandemic, the ICPC management organized everyone's schedule in such a way that there were never more than $n$ people in the office at the same time, and things ran so smoothly that they continued the process once things began to return to normal. Here is the scheme they used. Label the teams with integers $1$ through $n$ and the two people on the $i^\text{th}$ team as $(i, 1)$ and $(i, 2)$ for each $i$ from $1$ to $n$. Each week, exactly one person from each team is allowed in the office, while the other has to stay away. The employees $(i, 1)$ and $(i, 2)$ know each other well and collaborate productively regardless of being isolated from each other, so members of the same team do not need to meet in person in the office. However, isolation between members from different teams is still a concern.

Each pair of teams $i$ and $j$ for $i \neq j$ has to collaborate occasionally. For a given number $w$ of weeks and for fixed team members $(i, a)$ and $(j, b)$, let $w_1 < w_2 < \ldots < w_k$ be the weeks in which these two team members meet in the office. The isolation of those two people is the maximum of

$$
\{w_1,w_2-w_1,w_3-w_2,\ldots,w_k-w_{k-1},w+1-w_k\}
$$

or infinity if those two people never meet. The isolation of the whole company is the maximum isolation across all choices of $i$, $j$, $a$, and $b$.

You have been tasked to find a weekly schedule that minimizes the isolation of the whole company over a given number $w$ of weeks.
## 输入格式

The input consists of a single line containing two integers $n$ ($2 \le n \le 10^4$) and $w$ ($1 \le w \le 52$), where $n$ is the number of teams and $w$ is the number of weeks that need to be scheduled.
## 输出格式

Output a line containing either an integer representing the minimum isolation achievable for $n$ teams or the word `infinity` if no schedule guarantees that every pair of individuals on different teams can meet. If the isolation is finite, it is followed by $w$ lines representing a schedule that achieves this isolation. The $j^\text{th}$ line of the schedule is a string of length $n$ containing only the symbols `1` and `2`, where the $i^\text{th}$ symbol indicates which of the two members from team $i$ comes into the office on week $j$.
## 样例

### 样例输入 #1
```
2 6

```
### 样例输出 #1
```
4
11
12
21
22
11
12

```
### 样例输入 #2
```
2 1

```
### 样例输出 #2
```
infinity

```


---

---
title: "[ICPC 2022/2023 WF] Three Kinds of Dice"
layout: "post"
diff: 省选/NOI-
pid: P12297
tag: ['2022', '2023', 'Special Judge', 'ICPC']
---
# [ICPC 2022/2023 WF] Three Kinds of Dice
## 样例

### 样例输入 #1
```
6 1 1 6 6 8 8
3 2 4 9

```
### 样例输出 #1
```
0.291666667 0.750000000

```
### 样例输入 #2
```
4 9 3 7 5
3 4 2 3

```
### 样例输出 #2
```
0.500000000 0.500000000

```


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
title: "[ICPC 2023 WF] Tilting Tiles"
layout: "post"
diff: 省选/NOI-
pid: P12300
tag: ['2023', 'ICPC']
---
# [ICPC 2023 WF] Tilting Tiles
## 样例

### 样例输入 #1
```
4 4
.r..
rgyb
.b..
.yr.

yrbr
..yr
...g
...b

```
### 样例输出 #1
```
yes

```
### 样例输入 #2
```
1 7
....x..

..x....

```
### 样例输出 #2
```
no

```
### 样例输入 #3
```
4 3
yr.
..b
ry.
b..

...
..b
.ry
byb
```
### 样例输出 #3
```
no

```


---

---
title: "[ICPC 2023 WF] Waterworld"
layout: "post"
diff: 省选/NOI-
pid: P12303
tag: ['2023', 'Special Judge', 'ICPC']
---
# [ICPC 2023 WF] Waterworld
## 样例

### 样例输入 #1
```
3 7
63 61 55 54 77 87 89
73 60 38 5 16 56 91
75 43 11 3 16 20 95

```
### 样例输出 #1
```
51.809523810

```
### 样例输入 #2
```
4 3
10 10 10
10 10 10
10 10 10
10 10 10

```
### 样例输出 #2
```
10.000000000

```


---

---
title: "[ICPC 2023 WF] Alea Iacta Est"
layout: "post"
diff: 省选/NOI-
pid: P12305
tag: ['2023', 'Special Judge', 'ICPC']
---
# [ICPC 2023 WF] Alea Iacta Est
## 样例

### 样例输入 #1
```
5 8
ABCDEP
AEHOXU
AISOLR
ABCDEF
ABCSCC
PARSE
PAUSE
PHASE
POISE
PROSE
PULSE
PURSE
PEACE

```
### 样例输出 #1
```
9.677887141

```
### 样例输入 #2
```
2 1
AAAAAA
BBBBBB
AB

```
### 样例输出 #2
```
1.0

```
### 样例输入 #3
```
3 1
123456
123456
123456
666

```
### 样例输出 #3
```
10.555444555

```
### 样例输入 #4
```
2 1
ABCDEF
GHI234
AB

```
### 样例输出 #4
```
impossible

```


---

---
title: "[ICPC 2022 WF] Zoo Management"
layout: "post"
diff: 省选/NOI-
pid: P12307
tag: ['2022', 'ICPC']
---
# [ICPC 2022 WF] Zoo Management
## 题目描述

When managing a zoo, you sometimes want to move the animals between enclosures. You might figure out that the zebras will enjoy the spacier enclosure currently occupied by the penguins, while the penguins might want to move to the colder enclosure where the koalas currently live; and koalas will move to an empty enclosure that can be filled up with eucalyptus. So, you would move the koalas first, to free up the colder enclosure, then move the penguins there, and finally move the zebras.

The way you move animals is by using special tunnels that connect the enclosures — you do not want the animals to move outside, both because of the risk that they will be scared, and because of the risk that they might run away and hurt themselves.

Unfortunately, you have acquired more animals recently, and all the enclosures are now full, which makes moving animals around much harder. Imagine, for instance, that the koalas were to move to the former zebra enclosure — you cannot move any set of animals first. Instead, what you learned to do, is to move the animals at the same time — the zebras, koalas and penguins start moving down different tunnels at the same time, and arrive at their new enclosures at the same time — and thus they never meet. Note that you cannot just swap the animals in two connected enclosures this way (because they would meet in the tunnel and become scared).

So, now you have a puzzle. You have a list of enclosures, each with an animal type inside; some of those enclosures are connected by tunnels. You can, any number of times, choose some set of animals and move each one to an enclosure adjacent by tunnel, as long as the animal in that enclosure is also moved as the part of the same move, and no tunnel is used more than once as a part of the same move. You also have your vision of the perfect way to position the animals. Is it possible to do so, in a series of moves?
## 输入格式

The first line of the input consists of two integers $n$ ($1 \le n \le 4\cdot 10^5$) and $m$ ($0 \le m \le 4\cdot 10^5$), indicating the number of enclosures and tunnels. Then follow $n$ lines, the $i^\text{th}$ of which contains two integers $b_i$ ($1 \le b_i \le 10^6$) and $e_i$ ($1 \le e \le 10^6$), indicating the type of animal that is in enclosure $i$ at the beginning, and the type of animal that you want to be in enclosure $i$ after all the moves. You may assume that $e_1, \ldots , e_n$ is a permutation of $b_1, \ldots , b_n$.

Then follow $m$ lines describing the tunnels. Each line contains two integers $x$ and $y$ ($1 \le x < y \le n$), indicating that enclosures $x$ and $y$ are connected by a two-way tunnel. No two enclosures are connected by more than one tunnel.
## 输出格式

If it is possible to move the animals so that every enclosure contains the desired animal type, output `possible`. Otherwise, output `impossible`.
## 样例

### 样例输入 #1
```
3 3
1 4
4 7
7 1
1 2
2 3
1 3

```
### 样例输出 #1
```
possible

```
### 样例输入 #2
```
2 1
1 2
2 1
1 2

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
5 6
10 40
20 30
30 50
40 20
50 10
1 2
2 3
1 3
3 4
3 5
4 5

```
### 样例输出 #3
```
possible

```
### 样例输入 #4
```
4 4
10 10
10 20
20 10
20 20
1 2
2 3
3 4
1 4

```
### 样例输出 #4
```
impossible

```


---

---
title: "[ICPC 2022 WF] Quartets"
layout: "post"
diff: 省选/NOI-
pid: P12309
tag: ['2022', 'ICPC']
---
# [ICPC 2022 WF] Quartets
## 样例

### 样例输入 #1
```
4
1 A 2 3C no
2 A 3 3A yes
2 A 4 3D yes
2 A 1 3C no

```
### 样例输出 #1
```
no
4

```
### 样例输入 #2
```
6
1 A 2 3C no
2 A 3 3A yes
2 A 4 3D yes
2 A 1 3B no
1 A 4 5B yes
1 Q 5

```
### 样例输出 #2
```
yes

```


---

---
title: "[NAC 2025] Entrapment [Can't Judge Yet]"
layout: "post"
diff: 省选/NOI-
pid: P12622
tag: ['搜索', '2025', '交互题', 'Special Judge', '记忆化搜索', 'ICPC', 'NAC']
---
# [NAC 2025] Entrapment [Can't Judge Yet]
## 题目描述

 _Entrapment_  is an asymmetric two-player game that is played on a $3\times 3$ square grid. The two players are called the Runner and the Trapper. The grid squares are numbered from $1$ to $9$ as depicted below:

$$\begin{array}{|c|c|c|}
    \hline
    1 & 2 & 3 \\
    \hline
    4 & 5 & 6 \\
    \hline
    7 & 8 & 9 \\
    \hline
\end{array}$$

Before starting the game, the players agree on the number of rounds that the game will last, and on the starting state of the game board. Up to $8$ of the grid squares can be marked as _unavailable_. The players also choose who will be the Runner and who will be the Trapper. The Runner then secretly chooses a starting square from among those that are available (i.e., are not marked as unavailable) but does not tell the Trapper their choice.

Each of the game rounds consists of the following steps, in order:

- The Trapper publicly chooses some subset of the available squares (the empty set is allowed) and asks the Runner, "Are you currently in any of these squares?"
- The Runner answers truthfully whether or not they are in any of the chosen squares.
- The Trapper publicly chooses exactly one available square. That square becomes unavailable for the rest of the game. (The Runner might currently reside in that square; if so, nothing special happens.)
- The Runner secretly moves from their current square to an available orthogonally-adjacent square. If no such square exists, the Runner announces that they are trapped and the Trapper wins the game.

If the Runner has not been trapped by the end of the last round, they prove to the Trapper that they answered all questions truthfully by revealing their choice of starting square and the move that they made during each round. The Runner then wins the game.

Because the Runner's initial choice of square is secret, as are all of their subsequent moves, the Runner is allowed to "cheat" by not truly committing to a square.  At the end of the game, if the Runner can produce a choice of starting square and subsequent moves that do not result in being trapped and are consistent with the answers to the Trapper's questions during each round, that is enough for the Runner to win the game.
## 输入格式

### Interaction

This is an interactive problem. Given the number of game rounds and the set of squares that are initially marked unavailable, determine whether the
Runner or the Trapper would win assuming optimal play, and then prove it by
playing as that role against the judge. The judge will obey all game rules, but may or may not play optimally.

Interaction starts by reading a line of $2$ space-separated integers $R$ and $U$
($1 \leq R \leq 9$, $0 \leq U \leq 8$, $R + U \leq 9$): the
number of rounds in the game and the number of squares that are unavailable at the start of the game.

Next, if $U>0$, read a line of $U$ space-separated integers $s$ ($1 \leq s \leq 9$): the labels of the squares that are unavailable at the start of the game. Please refer to the diagram above for how the squares in the grid are labeled. The $U$ labels are guaranteed to be distinct.

Determine whether the Runner or Trapper would win the game with optimal play, given the starting board and number of game rounds. Print a line of output with the string $\texttt{Runner}$ if the runner wins with optimal play, and the string $\texttt{Trapper}$ otherwise. You will play as that role for the rest of the game; please see the appropriate section below for further instructions on how to interact with the judge in that role.

**For the Runner**, repeat the following steps $R$ times:

- Read a line of input with a single integer $N$: the size of the subset of available squares that the Trapper has chosen to ask about. $N$ is guaranteed to be between $0$ and the number of available squares left on the board, inclusive.
- If $N>0$, read a line of $N$ space-separated integers $\ell$ ($1 \leq \ell \leq 9$) listing the labels of the squares in the Trapper's chosen subset. The labels are guaranteed to be distinct and all of the chosen squares are guaranteed to be available.
- Print a line of output containing either the string $\texttt{Yes}$ or the string $\texttt{No}$. The former informs the trapper that you are currently in one of the chosen squares; the latter informs the trapper that you are not.
- Read a line with a single integer $i$ ($1 \leq i \leq 9$),  the label of the square that the Trapper marks as unavailable. It is guaranteed that square $i$ is a formerly-available square.
- Print a line with the string $\texttt{Free}$ to inform the Trapper that you have secretly moved to an orthogonally-adjacent available square and are ready to proceed to the next round. If there are no orthogonally-adjacent squares available, you must print $\texttt{Trapped}$ instead and exit; your submission will be judged incorrect for having failed to elude the Trapper.

After you have played $R$ rounds of the game according to the protocol above, print a line with $R+1$ space-separated integers. The first integer is the label of your chosen starting square; each of the next $R$ integers are the labels of the squares onto which you moved at the end of each of the $R$ rounds. Your moves must be legal and must be consistent with the answers you gave to the Trapper's queries during each round of play. After printing this line, your program must exit.

**For the Trapper**, repeat the following steps $R$ times:

- Print a line with a single integer $N$: the size of the subset of available squares that you would like to ask the Runner about.
- If $N>0$, print a line of $N$ space-separated integers listing the available squares to ask the Runner about. You may list the labels in any order, but the labels must be distinct and must refer to available squares.
- Read a line of input containing a single string: $\texttt{Yes}$ if the Runner is in one of your chosen squares, or $\texttt{No}$ otherwise.
- Print a line with a single integer $i$: the square that you are marking unavailable. The label $i$ must be a valid currently-available square.
- Read a line with a single string: $\texttt{Free}$ if the Runner has moved to an available square, or $\texttt{Trapped}$ if they were unable to do so. After reading the word $\texttt{Trapped}$, you have won the game, and your program must exit. If you read the word $\texttt{Free}$ at the end of the $R$th round, your program must also exit, though your submission will be judged incorrect since you have failed to trap the Runner.

The judge is guaranteed to answer all questions truthfully.

**Do not forget to flush the output stream after each line that you print** and to cleanly exit after the interaction is done. Please also make sure that you follow the above interaction protocol exactly regarding what information to print on which line of output: for example, if the protocol requires you to print a list of space-separated integers on a single line, the judge **will not** accept each integer on its own line.

If the judge receives invalid or unexpected input, it will print $-1$ and then immediately exit. Your program must detect this error report and cleanly exit in order to receive a Wrong Answer verdict. If your program blocks waiting for further interaction from the judge, or tries to interpret the $-1$ as a game move, you may receive a different rejected verdict (such as Time Limit Exceeded or Runtime Error) instead of Wrong Answer.

You have been provided with a command-line tool for local testing. The tool has comments at the top to explain its use.
## 输出格式

See Interaction.
## 样例

### 样例输入 #1
```
3 6
1 2 3 7 8 9



Yes

Free

No

Trapped
```
### 样例输出 #1
```


Trapper
2
4 5

5

0

6
```
### 样例输入 #2
```
2 0

7
3 1 2 8 9 4 5

5

4
4 6 7 8

7
```
### 样例输出 #2
```

Runner


Yes

Free


Yes

Free
5 4 1
```


---

---
title: "[NAC 2025] Humans vs AI"
layout: "post"
diff: 省选/NOI-
pid: P12624
tag: ['线段树', '树状数组', '2025', '分治', 'ST 表', 'ICPC', 'NAC']
---
# [NAC 2025] Humans vs AI
## 题目描述

In the world of rising AI, James is scared of losing his job. So, when his boss asks him to evaluate a new AI model to see how well it performs compared to humans, he wants to make it look as bad as possible.

To test the AI, James conducts a sequence of $N$ trials where a human and an AI are
given the same task and then scored based on their performance on the task. 
He is then going to send the results of some non-empty contiguous subsequence of these trials to his boss and quietly delete the rest.

Let $a_i$ and $h_i$ be the performance of the AI and human on trial $i$, respectively. James's boss evaluates the AI on a sequence of trials by calculating two total scores: one for the humans, and one for the AI. Both scores are initially $0$. For each trial $i$ where $h_i \geq a_i$, the boss awards the humans $h_i-a_i$ points. For each trial where $h_i < a_i$, the AI earns $a_i-h_i$ points.
If the humans' total score is greater than or equal to the AI's total score times some constant $k$ (to account for humans needing food, water, and a desk), James's boss declares that the humans outperform the AI.

James plans to send his chosen subsequence of test results through email to his boss. There is, however, one complication: since AI is already all-knowing and all-pervasive, it intercepts this email and may swap the value of $h_i$ and $a_i$ for one trial $i$ of its choice. (It doesn't want to swap more than one trial result---James might notice!)

Count how many non-empty contiguous subsequences of trial results James could send his boss with the guarantee that humans will be declared to outperform the AI, even if the AI swaps the result of up to one trial.
## 输入格式

The first line of input contains two space-separate integers: $N$ ($1 \leq N \leq 2 \cdot 10^5$), the total number of trials James conducted, and $k$ ($1 \leq k \leq 100$), the multiplier James's boss will apply to the AI's total score to determine whether humans outperform AI.

The second line contains $N$ space-separated integers $h_1, h_2, \ldots, h_N$ ($0 \leq h_i \leq 10^6$), the performance of the humans on each of the $N$ trials.

The third line contains $N$ space-separated integers $a_1, a_2, \ldots, a_N$ ($0 \leq a_i \leq 10^6$), the performance of the AI on the $N$ trials.
## 输出格式

Print the number of non-empty contiguous trial subsequences for which James's boss would declare that humans outperform AI, even if the AI swaps the result of up to one trial.
## 样例

### 样例输入 #1
```
10 2
3 5 7 6 8 6 4 5 2 6
2 4 6 5 4 3 3 6 3 4
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
7 1
4 3 2 1 7 6 5
4 2 3 1 7 6 5
```
### 样例输出 #2
```
11
```


---

---
title: "[NAC 2025] Polygon Partition"
layout: "post"
diff: 省选/NOI-
pid: P12628
tag: ['2025', 'Special Judge', 'ICPC', 'NAC']
---
# [NAC 2025] Polygon Partition
## 题目描述

A simple polygon is a polygon that is not self-intersecting and does not contain any holes. You are given the $N$ vertices of a simple polygon, $v_1$, $v_2$, $\ldots$, $v_N$, where $v_i = (x_i, y_i)$, and $x_i$ and $y_i$ are the $x$-coordinate and $y$-coordinate of the $i^{\textrm{th}}$ vertex, respectively. The vertices are distinct and given in counterclockwise order (so there is an edge between each pair of consecutive vertices; there is also an edge from $v_N$ back to $v_1$).

The polygon's boundary does not pass through any **lattice points** (a lattice point is a point where both coordinates are integers). In addition, none of the $x_i$ or $y_i$ values are exactly an integer.

A **semi-integer point** is a point where exactly one of its coordinates is an integer. Let $\mathcal{P} = \left\{p_1, p_2, \ldots, p_k\right\}$ be all of the semi-integer points that lie on the boundary of the polygon.
For each semi-integer point $p_i$ in $\mathcal{P}$, let $n_i$ be the floor of the non-integer coordinate of $p_i$. For a subset $\mathcal{S}$ of $\mathcal{P}$, let $\sigma(\mathcal{S})$ be the sum of the $n_i$ of the points in $\mathcal{S}$ (with $\sigma(\emptyset) = 0$). Does there exist a partition of $\mathcal{P}$ into two subsets $\mathcal{S}_1$ and $\mathcal{S}_2$ so that the $\sigma(\mathcal{S}_1) = \sigma(\mathcal{S}_2)$?

(Two sets $\mathcal{S}_1$ and $\mathcal{S}_2$ are a partition of $\mathcal{P}$ if $\mathcal{P} = \mathcal{S}_1 \cup \mathcal{S}_2$ and $\mathcal{S}_1 \cap \mathcal{S}_2 = \emptyset$. There are no other restrictions on $\mathcal{S}_1$ and $\mathcal{S}_2$ so long as these two conditions hold and $\sigma(\mathcal{S}_1) = \sigma(\mathcal{S}_2)$. In particular, empty sets are allowed, and the semi-integer points in each set **do not** have to be contiguous around the polygon boundary.)
## 输入格式

The first line of input contains one integer $N$ ($3 \leq N \leq 500$), the number of vertices of the polygon.

Each of the next $N$ lines contains two space-separated real numbers $x_i$ and $y_i$ ($-500 < x_i, y_i < 500$): the coordinates of the polygon vertices, in counterclockwise order. Each coordinate will have exactly $6$ digits after the decimal point and will not be exactly an integer.

It is guaranteed that the polygon does not self-intersect, that the vertices are distinct, and that the polygon boundary does not pass through any lattice points.
## 输出格式

If there is no solution, print $-1$ and no further output. 

Otherwise, print a single integer $M$ on its own line: the number of semi-integer points in one of the two subsets in a valid partition of $\mathcal{P}$.
On the next $M$ lines of output, print the values $n_i$ for the points in that subset, one per line. 

If there are multiple valid partitions, you may choose any of them. You may print either of its two subsets, and you may list the subset's $n_i$ values in any order.
## 样例

### 样例输入 #1
```
4
-0.950000 -0.850000
-0.100000 0.999999
0.111000 0.555000
-0.200000 1.600000
```
### 样例输出 #1
```
3
0
-1
-1
```
### 样例输入 #2
```
3
0.500000 0.700000
0.100000 0.200000
0.800000 0.900000
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4
-360.000001 -24.000001
-359.999999 -24.000001
-359.999999 -23.999999
-360.000001 -23.999999
```
### 样例输出 #3
```
2
-25
-360
```
## 提示

Sample Input 1 is shown in the image below:

![](https://cdn.luogu.com.cn/upload/image_hosting/qx8pxc9s.png)

The points of the vertices are labeled $A,B,C,D$.
The semi-integer points are marked in orange and labeled $p_i$ going counterclockwise around the perimeter starting from $A$. The values $n_i$ of the semi-integer points are, in the same order, $-1, 0, 0, -1, -1, -1$.
Any subset of those values that sum to $-2$ would be accepted as correct. Sample Output 1 shows one possible correct answer.

The boundary of the polygon in Sample Input 2 does not intersect any semi-integer points, so $\mathcal{P}$ is empty, and it can be partitioned into two empty sets each with $n_i$ sum of zero.


---

---
title: "[NAC 2025] Popping Balloons"
layout: "post"
diff: 省选/NOI-
pid: P12629
tag: ['2025', '多项式', '分治', '快速傅里叶变换 FFT', 'ICPC', 'NAC']
---
# [NAC 2025] Popping Balloons
## 题目描述

The ICPC logo has three colors: blue, yellow, and red. The NAC volunteers have just inflated a huge number of balloons in these
colors and arranged them in a line. They next need to sort the balloons by color before they can give them out to contestants. 

Unfortunately, due to the Orlando heat, the balloons begin to randomly pop: each second, a random remaining balloon
pops (and the volunteers remove the debris from the line). This isn't all bad: maybe if the NAC volunteers wait long enough, the balloons will become sorted by chance? Compute the expected number of seconds until the first time that all blue balloons come before all yellow and red balloons, and all yellow balloons come before all red balloons. (These conditions are satisfied even if they are vacuously true: for example, if there are no blue balloons at all remaining, then it is true that all blue balloons come before all yellow and red balloons.)
## 输入格式

The input has one line: a string $s$ ($1\le |s|\le 2\cdot 10^5$) where each character is one of $\texttt{B}$, $\texttt{Y}$, or $\texttt{R}$ representing blue, yellow, and red respectively ---the colors of the initial balloons in the line.
## 输出格式

Print the expected number of seconds that elapse before the first time that all blue balloons come before all yellow
and red balloons, and all yellow balloons come before all red balloons. Since this number might not be an integer, print
 it modulo $998\, 244\, 353$.

Formally, let $p = 998\,244\,353$. It can be shown that the answer can be expressed as an irreducible fraction $\frac{a}{b}$, where $a$ and $b$ are non-negative integers and $b \not \equiv 0 \pmod{p}$. Print the integer $x$ with $0 \leq x < p$ and $x \equiv a \cdot b^{-1} \bmod p$.
## 样例

### 样例输入 #1
```
RYBB
```
### 样例输出 #1
```
831870297
```
### 样例输入 #2
```
YRBBR
```
### 样例输出 #2
```
598946615
```
## 提示

In Sample Input 1, the expected time until the balloon colors first become sorted in the correct order is $\frac {17}{6} = 2\cdot \frac{1}{6} + 3 \cdot \frac{5}{6}$ seconds:
the only way for the balloon colors to be sorted correctly after $2$ seconds is if the first two balloons to pop are the yellow and red balloon (in either order). The probability that these balloons pop before either blue balloon is $\frac{1}{6}$. Otherwise (with probability $\frac{5}{6}$) the balloon colors will automatically be sorted after $3$ seconds, when there is only one balloon left.
Since $6^{-1} \equiv 166\,374\,059\pmod {p}$, the answer is $17\cdot
166\,374\,059\equiv 831\,870\,297\pmod{p}$.


---

---
title: "[NAC 2025] This Is Sparta!"
layout: "post"
diff: 省选/NOI-
pid: P12632
tag: ['2025', 'ICPC', 'NAC']
---
# [NAC 2025] This Is Sparta!
## 题目描述

King Primonidas is putting together a tournament to find the strongest gladiator in all the lands. In total $N$ gladiators have made their way to the Coliseum to bring back honor and glory to their hometowns. Each gladiator starts with a certain amount of vitality. Vitality is similar to health points in that it reflects the amount of damage a gladiator can take, but it also represents the amount of damage they can deal (since energy is needed for strong blows).

The tournament consists of $K$ rounds. Every round, the king arranges the gladiators in a line from least to most remaining vitality, breaking ties randomly. King Primonidas believes that the true strength of a gladiator lies in their ability to take a beating, so he orders the first gladiator (the one with the lowest remaining vitality) to deal their strongest blow to the second gladiator. This blow subtracts the first gladiator's vitality from the second gladiator's vitality. After the second gladiator takes the hit, they deal their strongest blow (using their new, lowered vitality) to the third gladiator, and so on. This process repeats until the second-to-last gladiator deals their strongest blow to the last gladiator (who doesn't get to attack anybody).

Notice that in the above process, a gladiator's vitality can never go below zero. (A gladiator with zero vitality deals a feeble blow of no damage to the next gladiator.)

Print the vitality of each gladiator after $K$ tournament rounds, in order from the first to the last gladiator in line.
## 输入格式

The first line of input contains two space-separated integers $N$ ($2 \leq N \leq 10^5$) and $K$ ($1 \leq K \leq 10^{18}$): the number of gladiators and the number of rounds in the tournament.

The next line of input contains $N$ space-separated integers $v_1 \; v_2 \; \ldots v_N$ ($0 \leq v_i \leq 10^{18}$): the starting vitality of the gladiators.
## 输出格式

Print $N$ space-separated integers: the vitality of the gladiators at the end of the $K$th round of the tournament, in the order that the gladiators currently stand in line.
## 样例

### 样例输入 #1
```
6 3
21 28 24 23 1 12
```
### 样例输出 #1
```
1 1 3 6 3 10

```
### 样例输入 #2
```
3 1000
8 2 10

```
### 样例输出 #2
```
0 0 2
```


---

---
title: "[ICPC 2024 Yokohama R] Beyond the Former Explorer"
layout: "post"
diff: 省选/NOI-
pid: P12784
tag: ['2024', '交互题', 'Special Judge', 'ICPC']
---
# [ICPC 2024 Yokohama R] Beyond the Former Explorer
## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。
## 题目描述

**这是一道交互题。**

你正站在一片区域的正中心，该区域被划分为南北走向和东西走向的网格单元。一份巨大的宝藏隐藏在其中一个单元内。  

John Belzoni——著名的宝藏猎人 Giovanni Battista Belzoni 的后裔——实际上已发现了这份宝藏。不幸的是，他在成功挖出宝藏前因中暑去世；他似乎花了过长的时间在这片区域徘徊。  

John 的探索从你当前站立的区域中心单元出发。他通向宝藏的所有足迹都留在了这片区域，但只有抵达某个单元才能识别该单元上的足迹。某一单元上的足迹指示了他下一步前往四个相邻网格单元中的哪一个。 已知 John 不会重复访问同一网格单元。你在中心单元看到一个足迹，表明 **John 的第一步是向北**。

区域中存在恰好一个宝藏单元，只有站在该单元时你才能识别它。  

下图展示了区域的一种可能情形。John 的足迹在单元中以箭头标识。宝藏单元标记为 $\texttt{G}$。阴影单元是你的初始位置。  

![](https://cdn.luogu.com.cn/upload/image_hosting/bakj14ug.png)

你的任务是在有限**步**内找到宝藏。每一步中，你需决定朝北、西、南、东四个方向之一移动，并进入该方向的相邻单元。当你移动到该单元时，可能发现宝藏、John 的足迹，或者空无一物。你无需追随 John 的足迹。与 John 的路线不同，你可以重复访问同一单元。无论你如何探索，John 的足迹始终保持不变。  


### 实现细节

交互开始时，你需从标准输入读取一个整数 $n$（$1 \leq n \leq 2000$），后接换行符。整数 $n$ 表示区域被划分为 $(2n + 1) \times (2n + 1)$ 的网格单元。你的初始位置从西向东第 $n+1$ 列、从北向南第 $n+1$ 行的单元。读入整数 $n$ 后，你即可开始探索。  

每步，你向标准输出发送表示移动方向的单个字符：  
- `^`（插入符）表示向北；
- `<`（小于号）表示向西；
- `v`（小写字母 $\texttt{v}$）表示向南；
- `>`（大于号）表示向东。

字符后需附加换行符。  

作为回答，你将收到一个表示抵达单元内容的字符，后接换行符：  

- `G`：该单元有宝藏；
- `^`, `<`, `v`, `>`：John 的足迹分别指示北、西、南、东；
- `.`（点号）：既无宝藏也无足迹。

当你发现宝藏（即收到 `G`）时，交互立即终止，你的程序必须退出。 **你需在 $\bf{30000}$ 步内抵达宝藏单元**。尽管追随 John 的足迹必能找到宝藏，但步数可能超过 $30000$。 

以下情况将被判为 $\text{Wrong Answer}$：  

- 程序输出格式无效；
- 指定了移出网格的方向；
- 找到宝藏后仍有额外输出；
- 未在 $30000$ 步内抵达宝藏单元。

区域的布局（宝藏位置与 John 的足迹）在交互前已固定，在交互过程中不会改变。  

**在每次移动后，你都需要换行并刷新缓冲区**。例如：

- $\texttt{C++}$ 中的 `cout.flush()`。

## 输入格式

见「实现细节」。
## 输出格式

见「实现细节」。
## 样例

### 样例输入 #1
```
2

^

.

<

^

G
```
### 样例输出 #1
```

^

<

v

<

^
```
## 提示

样例如「题目描述」中的图所示。


---

---
title: "[ICPC 2024 Yokohama R] Peculiar Protocol"
layout: "post"
diff: 省选/NOI-
pid: P12789
tag: ['2024', 'ICPC']
---
# [ICPC 2024 Yokohama R] Peculiar Protocol
## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。
## 题目描述

_Icpca_ 王国在婚礼仪式上有一个特殊的规矩：礼金的数额必须是某个固定数量的倍数加上一个固定的额外数额。当固定数量是 $d$ 且固定额外数额是 $r$ 时，合规的礼金数额是 $k \times d + r$，其中 $k$ 是任意非负整数乘数。

最初，你有一叠 $n$ 张钞票。每次你参加婚礼仪式时，你会从当前钞票堆中取出一部分连续的钞票作为礼物，其总和为一个合规的数额，即 $d$ 的倍数加上额外的 $r$。如果没有连续的一段的钞票总和合规，你就不能再参加婚礼仪式了。取出后，剩余的钞票会被挤压形成一叠，并保持它们的相对顺序。形成的钞票堆中可能仍有总和达到该数额的部分，这允许你参加更多的仪式。

你的礼金预计会提升你的社会声誉。由于额外数额 $r$ 被认为是强制性的，乘数 $k$ 被认为是重要的。你在参加的每次仪式中，声誉都会按 $k$ 的比例提升。
例如，假设 $d = 5$ 且 $r = 1$，你拥有的钞票面值按顺序堆叠为 $2,2,2,4,4$。当你参加婚礼仪式时，有两种可能的方式可以给出合规的礼金。
- 给出由最上面三张钞票组成的礼金，总计为 $2 + 2 + 2 = 6 = 1 \times d + r$。取出它们后，你剩下两张面值为 4 和 4 的钞票。你剩余的钞票堆中没有连续的部分总和达到合规的数额。因此，你不能再参加婚礼仪式了。
- 给出由第三张和第四张钞票组成的礼金，总计为 $2 + 4 = 6 = 1 \times d + r$。取出它们后，你剩下三张面值依次为 $2,2,4$ 的钞票。你可以参加另一场婚礼仪式，因为第二张和第三张钞票的总和为 $2 + 4 = 6 = 1 \times d + r$，这是合规的。

在这个例子中，第二种方式可以通过参加两次仪式来最大化你的社会声誉，因为乘数总和为 $1 + 1 = 2$，这达到了最大可能值。

相比之下，如果第一张钞票的面值是 12，在一次仪式中给出前三张钞票后，你就无法参加更多仪式了。然而，这会最大化你的社会声誉，因为乘数总和为 $3$，这达到了最大可能值。

计算你在婚礼仪式上礼金乘数的最大可能总和。你可以假设你有很多未婚的亲戚和朋友，只要你能给出合规的礼金，你就可以参加任意数量的婚礼仪式。
## 输入格式


仅一组数据，格式如下所示：

> $n$ $d$ $r$\
> $a_1$ $\cdots$ $a_n$

第一行，三个整数 $n,d,r$。整数 $n$（$1 \le n \le 500$）是你拥有的钞票数量。整数 $d$ 和 $r$（$2 \le d \le 10^8$，$0 \le r < d$）表示特殊规矩的参数。第二行有 $n$ 个整数， $a_1, \ldots, a_n$。其中，$a_i$（$0 \le a_i \le 10^8$）表示从顶部数第 $i$ 张钞票的面值。
## 输出格式



输出一行，包含你在婚礼仪式上礼金乘数的最大可能总和。


## 样例

### 样例输入 #1
```
5 5 1
2 2 2 4 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5 5 1
12 2 2 4 4
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
5 20000 10000
5000 10000 15000 5000 25000
```
### 样例输出 #3
```
2
```
### 样例输入 #4
```
9 5 3
4 2 2 1 1 4 3 2 1
```
### 样例输出 #4
```
2
```


---

---
title: "[NERC 2022] Dominoes"
layout: "post"
diff: 省选/NOI-
pid: P12793
tag: ['2022', '二分图', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Dominoes
## 题目描述

Dora likes to play with dominoes. She takes $n \times m$ table, marks some cells as occupied, and then tries to fill all unoccupied cells with $2 \times 1$ dominoes.

![](https://cdn.luogu.com.cn/upload/image_hosting/izci2rsk.png)

Her little brother Dani loves to play pranks on his older sister. So when she is away, he marks two more unoccupied cells as occupied. He wants to do it in such a way that it will be impossible to fill all unoccupied cells with dominoes.

Help Dani to count the number of ways he can select these two cells. Since Dani can only count to one million, if this number of ways is $x$, output $\min(x, 10^6)$.
## 输入格式

The first line contains integers $n$ and $m$ ($1\le n, m\le 1000$). Next $n$ lines contain $m$ characters each --- the initial state of the table. Character $\tt{\#}$ corresponds to an occupied cell, and character $\tt{.}$ corresponds to an unoccupied cell. It is guaranteed that there are at least two unoccupied cells, and that it is possible to fill all unoccupied cells with dominoes.
## 输出格式

Let $x$ be the number of ways Dani can mark two cells in such a way that it will be impossible to fill all unoccupied cells with dominoes. 

Print one integer $\min(x, 10^6)$.
## 样例

### 样例输入 #1
```
3 6
...#..
......
#...##
```
### 样例输出 #1
```
52
```
### 样例输入 #2
```
2 2
..
..
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
2 2
#.
#.
```
### 样例输出 #3
```
0
```


---

---
title: "[NERC 2022] Game of Questions"
layout: "post"
diff: 省选/NOI-
pid: P12796
tag: ['2022', 'Special Judge', '快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', 'ICPC', '状压 DP', 'NERC/NEERC']
---
# [NERC 2022] Game of Questions
## 题目描述

Genie is taking part in an intellectual game. The game consists of $n$ questions, and there are $m$ participants numbered from $1$ to $m$. Genie is the participant number $1$.

For each question $i$ and participant $j$, it is known whether the participant will answer the question correctly or not.

The goal of the game is to be the last participant staying in the game.

The game is conducted as follows. First, all $n$ questions get shuffled uniformly at random (all $n!$ permutations are equally likely). Then, the questions are asked one by one. Each participant answers the question. If all participants still in the game answer the question correctly, or if all of them answer the question incorrectly, nothing happens. Otherwise, those participants who answer the question incorrectly lose and leave the game.

After all $n$ questions are asked, all participants who are still in the game are declared to be the winners.

What is the probability that Genie will win the game?
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of questions and the number of participants ($1 \le n \le 2 \cdot 10^5$; $2 \le m \le 17$).

The $i$-th of the next $n$ lines contains $m$ characters $s_{i, 1}, s_{i, 2}, \ldots, s_{i, m}$. Character $s_{i, j}$ is $\tt{1}$ if participant $j$ answers question $i$ correctly or $\tt{0}$ otherwise.
## 输出格式

Print the probability that Genie will win the game. Your answer will be considered correct if its absolute or relative error does not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
1 5
11010
```
### 样例输出 #1
```
1.0000000000000000
```
### 样例输入 #2
```
3 3
011
101
110
```
### 样例输出 #2
```
0.3333333333333333
```
### 样例输入 #3
```
6 4
1011
0110
1111
0110
0000
1101
```
### 样例输出 #3
```
0.1666666666666667
```
## 提示

In the first example, there is a single question and Genie will answer it correctly, thus winning the game (along with participants $2$ and $4$).

In the second example, one participant will leave after the first asked question, and another participant will leave after the second asked question. Each participant will win with probability $\frac{1}{3}$.


---

---
title: "[NERC 2022] Hot and Cold"
layout: "post"
diff: 省选/NOI-
pid: P12797
tag: ['2022', '交互题', 'Special Judge', '构造', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Hot and Cold
## 题目描述

This is an interactive problem.

After emigrating to another country, little Hanna came across the fact that playing "Hot and cold" became more difficult: she does not understand the hint phrases! You are to write a helping program for her.

The playground where the game happens is a rectangle, and the treasure is hidden in some point with integer coordinates between 0 and $10^6$, inclusive. Hanna visits several points with valid coordinates. If the visited point contains the hidden treasure, she receives the phrase "Found!" in the local language. Fortunately, the intonations allow her to recognize this phrase --- in this problem it will be denoted by an exclamation mark.

Otherwise, for each visited point except for the first one, Hanna receives a phrase in the local language stating whether she is now "Closer", "Further", or "At the same distance" from the treasure, compared to the previous point. The distances are measured in Euclidean metric. After the first visited point, in case of no treasure there, Hanna receives the phrase "Not found" in the local language.

Your program must help Hanna find the treasure by visiting $\textbf{at most 64 points}$.

### Interactive Protocol

Your program should print each visited point in a line with two coordinates between 0 and $10^6$, inclusive, and flush the output after each one.

For each visited point, the testing system writes one of the phrases: "Found!", "Closer", "Further", "At the same distance", or "Not found" in some language, consistent throughout the game. The first phrase ends with an exclamation mark, all other phrases do not contain exclamation marks. All phrases contain only Latin letters, spaces and exclamation marks, have lengths between 2 and 30, inclusive, don't start or end with a space, and are pairwise distinct. The phrases are not necessarily coming from any real human language. 

After receiving a phrase with an exclamation mark, your program must halt without printing anything else. Visiting points more than once is allowed, and each such visit counts towards the limit of 64 queries.
## 输入格式

See interactive protocol.
## 输出格式

See interactive protocol.
## 样例

### 样例输入 #1
```

Tabilmadi

Daha yakin

Daha yakin

Sama distanco

Dalej

Znaydeno!
```
### 样例输出 #1
```
500 200

560 230

566 240

566 238

30 239

566 239
```
### 样例输入 #2
```

You are lucky today!
```
### 样例输出 #2
```
777777 777777
```


---

---
title: "[NERC 2022] Interactive Factorial Guessing"
layout: "post"
diff: 省选/NOI-
pid: P12798
tag: ['2022', '交互题', 'Special Judge', '构造', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Interactive Factorial Guessing
## 题目描述

Oh no, this wicked jury hides something from you again, and you need to guess it interactively. 

This time, you need to find an integer $n$. To do that, you can make at most 10 queries of the form "What is the $k$-th decimal digit of the product of all integers from 1 to $n$ (also known as factorial and denoted as $n!$)?". 

### Interactive Protocol

In the first line, there is an integer $t$ ($1 \le t \le 100$) --- the number of tests you shall process. 

For each test, the integer $n$ is chosen in advance. The length of $n!$ is at most $20\,000$, so $1 \le n \le 5982$.

You can make $\textbf{at most 10 queries}$ of the form "$\tt{? }$ $k$" ($0 \le k < 20\,000$). In response to the query, you will get a single digit --- the $k$-th decimal digit of $n!$ (the response is between 0 and 9 inclusive). Digits are numbered from 0, starting with the least significant digit. If $n!$ is too short, and there is no $k$-th digit, then 0 is returned. 

After your program finds the value of $n$ it shall answer with "$\tt{! }$ $n$". If the answer is correct, then you will receive "$\tt{YES}$" and should proceed to the next test or terminate if it was the last one. If the answer is not correct, or you are trying to guess, and there are several possible answers consistent with the information you have received, you will get "$\tt{NO}$". In that case, your submission will receive "$\tt{Wrong\ answer}$" verdict and your code shall terminate immediately. 
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2

1

YES

0

2

YES
```
### 样例输出 #1
```

? 0

! 1

? 0

? 19997

! 5982
```


---

---
title: "[NERC 2020] ASCII Automata Art"
layout: "post"
diff: 省选/NOI-
pid: P12900
tag: ['2020', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] ASCII Automata Art
## 题目描述

This problem statement is quite wordy by itself and does not need a legend. You are given a regular expression and your task is to render its corresponding automaton as an ASCII art text drawing following the specification in the problem statement. Please, see examples.

A regular expression in this problem consists of uppercase letters from `A` to `Z`, special characters `+`, `?`, `*`, and parenthesis that are used for grouping. An input to the problem is given by an `<input>` non-terminal of the following BNF grammar:

```
<input> ::= <expr>

<expr> ::= <term> | <term> `|' <expr>

<term> ::= <atom> | <atom><term> | <term><atom>

<atom> ::= <letter> | `(' <expr> `)' | <atom> `+' | <atom> `?' | <atom> `*'

<letter> ::= `A' | `B' | ... | `Z'
```

A regular expression is rendered as an ASCII art picture using the precise rules that are given below. They recursively define a unique representation for each regular expression as a rectangular *box* of characters with the specified number of rows and columns. Empty characters of the representation, including trailing ones, must be filled with spaces.

A `<term>` that consists of a sequence of $n$ uppercase letters is rendered as a box of 3 rows and $4 + n$ columns using `+` and `-` characters to render a border on the first and the last rows and columns as shown in the example. The production rule for the `<term>` non-terminal in the grammar is intentionally ambiguous. The longest possible sequence of adjacent `<letter>` non-terminals in the regular expression must be grouped into a `<term>` and rendered as a single box. 
For example, a `<term>` of `NERC` 
is rendered as the following $3 \times 8$ box:

```
+------+
+ NERC +
+------+
```

A `<term>` that consists of a sequence of `<atom>` non-terminals and `<term>` non-terminals with letters (as described above) is rendered by laying out the constituent boxes left-to-right, aligned vertically to the top, with 2 columns separating adjacent boxes. The height of the resulting box is equal to the maximum height of the constituent boxes.
Each pair of adjacent boxes is joined by rendering `->` characters on the 2nd row in the columns between them. 
For example, a `<term>` of `N(E)RC` (consisting of a sequence: `<atom>` of `A`, `<atom>` of `(E)`, and a letters-only `<term>` of `RC`)
is rendered as the following $3 \times 20$ box:

```
+---+  +---+  +----+
+ N +->+ E +->+ RC +
+---+  +---+  +----+
```

An `<expr>` that consists of a single `<term>` is rendered as its `<term>`.

An `<expr>` that consists of a `|`-separated sequence of `<term>` non-literals is rendered by laying out the corresponding `<term>` boxes top-to-bottom, aligned to the left, with a single row separating adjacent `<term>` boxes. The width of the resulting box is equal to the maximum width of the `<term>` boxes plus 6. There are 3 additional columns on the left, and 3 on the right. The first column and the last column use `+` and `|` characters to join the 2nd rows of all the `<term>` boxes from the top to the bottom one, with `+` placed on the 2nd row of each `<term>` box. The 2nd and the 3rd columns on the left and the 3rd-to-last and the 2nd-to-last columns on the right have `->` characters on the 2nd rows of the corresponding `<term>` boxes. Additionally, shorter `<term>` boxes are connected on the right with extra `-` characters on their 2nd rows. 
For example, an `<expr>` of `C|ON|TEST`
is rendered as the following $11 \times 14$ box:

```
   +---+         
+->+ C +---->+
|  +---+     |   
|            |   
|  +----+    |   
+->+ ON +--->+   
|  +----+    |   
|            |   
|  +------+  |   
+->+ TEST +->+   
   +------+      
```

An `<atom>` of `(` `<expr>` `)` is rendered as its `<expr>`.

An `<atom>` of `<atom>` `+` is rendered as a box of its source `<atom>` with 2 additional rows at the bottom and 6 additional columns (3 on the left and 3 on the right). The first and the last columns, starting with the 2nd row, and the last row are filled with the connecting characters as shown in the example. 

- The 2nd row starts with `+->` and ends with `->+` to connect to the 2nd row of the source `<atom>` box. 
- The last row starts with `+<-` to represent a backwards edge in the automaton. 

For example, an `<atom>` of `A+`
is rendered as the following $5 \times 11$ box. 

```
   +---+      
+->+ A +->+
|  +---+  |   
|         |   
+<--------+   
```

An `<atom>` of `<atom>` `?` is rendered as a box of its source `<atom>` with 3 additional rows at the top and 6 additional columns (3 on the left and 3 on the right). The first and the last columns (from the 2nd to the 5th row) and the 2nd row are filled with the connecting characters as shown in the example. 

- The first row of `<atom>` `?` is always empty (filled with spaces).
- The 2nd row ends with `->+` to represent an epsilon-edge in the corresponding automaton.
- The 5th row starts with `+->` and ends with `->+` to connect to the 2nd row of the source `<atom>` box.

For example, an `<atom>` of `B?`
is rendered as the following $6 \times 11$ box. 

```
                 
+-------->+
|         |   
|  +---+  |   
+->+ B +->+   
   +---+       
```

An `<atom>` of `<atom>` `*` is rendered as a box of its source `<atom>` with 5 additional rows (3 at the top and 2 at the bottom) and 6 additional columns (3 on the left and 3 on the right). The first and the last columns, with the 2nd and the last row, are filled with the connecting characters as shown in the example. 

- The first row of `<atom>` `*` is always empty (filled with spaces).
- The 2nd row ends with `->+` to represent an epsilon-edge in the corresponding automaton.
- The 5th row starts with `+->` and ends with `->+` to connect to the 2nd row of the source `<atom>` box.
- The last row starts with `+<-` to represent a backwards edge in the automata. 

For example, an `<atom>` of `C*`
is rendered as the following $8 \times 11$ box. 

```
                 
+-------->+
|         |   
|  +---+  |   
+->+ C +->+   
|  +---+  |   
|         |   
+<--------+   
```

An `<input>` is rendered as a box that has 6 more columns than the corresponding box of the `<expr>`, with 3 additional columns on the left, and 3 on the right. The 2nd row starts with `S->` to represent the starting state of the automaton and ends with `->F` to represent the final state of the automaton. See the example output.
## 输入格式

The input consists of a single line that corresponds to the $\langle input \rangle$ non-terminal of the grammar given the problem statement and has at most 100 characters in length.
## 输出格式

On the first line of the output, write two integers $h$ and $w$ --- the height and the width, correspondingly, of the $h \times w$ box that corresponds to the given $\langle input \rangle$. On each of the next $h$ lines, write $w$ characters of the corresponding ASCII art rendering.
## 样例

### 样例输入 #1
```
NE?(ER)C++|(IS)*?|(CHA((LL))ENGING)
```
### 样例输出 #1
```
23 57
      +---+               +----+        +---+            
S->+->+ N +->+-------->+->+ ER +->+->+->+ C +->+->+->+->F
   |  +---+  |         |  +----+  |  |  +---+  |  |  |   
   |         |  +---+  |          |  |         |  |  |   
   |         +->+ E +->+          |  +<--------+  |  |   
   |            +---+             |               |  |   
   |                              +<--------------+  |   
   |                                                 |   
   |                                                 |   
   +->+--------------->+---------------------------->+   
   |  |                |                             |   
   |  |                |                             |   
   |  +->+--------->+->+                             |   
   |     |          |                                |   
   |     |  +----+  |                                |   
   |     +->+ IS +->+                                |   
   |     |  +----+  |                                |   
   |     |          |                                |   
   |     +<---------+                                |   
   |                                                 |   
   |  +-----+  +----+  +--------+                    |   
   +->+ CHA +->+ LL +->+ ENGING +------------------->+   
      +-----+  +----+  +--------+                        
```


---

---
title: "[NERC 2020] Button Lock"
layout: "post"
diff: 省选/NOI-
pid: P12901
tag: ['2020', '网络流', 'Special Judge', '费用流', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Button Lock
## 题目描述

You are standing in front of the room with great treasures. The only thing stopping you is the door with a push-button combination lock. This lock has $d$ buttons with digits from $0$ to $d - 1$. Whenever you press a button, it stays pushed down. You can not pop back up just one button, but there is a "RESET" button --- pressing it pops up all other buttons. Initially, no buttons are pushed down.

The door instantly opens when some specific set of digits is pushed down. Sadly, you don't know the password for it. Having read the documentation for this specific lock, you found out that there are $n$ possible passwords for this particular lock.  

Find the shortest sequence of button presses, such that all possible passwords appear at least once during its execution. Any shortest correct sequence of button presses will be accepted.
## 输入格式

The first line contains two integers $d$ and $n$ ($1 \le d \le 10$; $1 \le n \le 2^d - 1$).
Next $n$ lines describe possible passwords. Each line contains a string $s_i$ of $d$ zeros and ones: for all $j$ from $1$ to $d$ the $j$-th character is $\tt{1}$ iff the button with the digit $j - 1$ must be pushed down.

All strings $s_i$ are different, and each string contains at least one $\tt{1}$.
## 输出格式

On the first line, print the number $k$ --- the minimum number of button presses.
On the second line, print $k$ tokens, describing the sequence. Whenever you press a button with a digit, print that digit. Whenever you press "RESET", print $\tt{R}$.
## 样例

### 样例输入 #1
```
2 2
10
11
```
### 样例输出 #1
```
2
0 1
```
### 样例输入 #2
```
3 4
001
111
101
011
```
### 样例输出 #2
```
6
2 0 R 1 2 0
```
## 提示

In the second example, the sequence $\tt{1 2 R 2 0 1}$ is also possible.


---

---
title: "[NERC 2020] Cactus Not Enough"
layout: "post"
diff: 省选/NOI-
pid: P12902
tag: ['2020', 'Special Judge', '树形 DP', '仙人掌', 'ICPC', '圆方树', 'NERC/NEERC']
---
# [NERC 2020] Cactus Not Enough
## 题目描述

There was no problem about a cactus at the NERC 2020 online round. That's a bad mistake, 
so judges decided to fix it. You shall not pass to the World Finals 2021 without solving
a problem about a cactus!

A $\emph{cactus}$ is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively, a cactus is a generalization of a tree where some cycles are allowed. Multiedges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus. 

Cher has got a cactus. She calls cactus $\emph{strong}$ if it is impossible to add an edge to it in such a way that it still remains a cactus. But Cher thinks her cactus is not strong enough. She wants to add the smallest possible number of edges to it to make it strong, i.e. to create a new cactus with the same vertices, so that the original cactus is a subgraph of the new one, and it is impossible to add another edge to it so that the graph remains a cactus. Cher hired you to do this job for her. So $\ldots$ it's on you!
## 输入格式

The input consists of one or more independent test cases.

The first line of each test case contains two integers $n$ and $m$ 
($1 \le n \le 10^5$, $0 \le m \le 10^5$), where $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$. Edges of the graph are represented by a set of edge-distinct paths, where $m$ is the number of such paths. 

Each of the following $m$ lines contains a path in the graph. A path starts
with an integer number $s_i$ ($2 \le s_i \le 1000$) followed by $s_i$ integers
from $1$ to $n$. These $s_i$ integers represent vertices of a path. Adjacent vertices in a path are distinct. The path can go through the same vertex multiple times, but every edge is traversed exactly once in the whole test case. There are no multiedges in the graph (there is at most one edge between any two vertices).

The last line of the input after all test cases always contains two zeros. It does $\textbf{not}$ define a test case. It just marks the end of the input and does not require any output.

All graphs in the input are cacti. The total sum of all values of $n$ and
the total sum of all values of $m$ throughout the input both do not exceed $10^5$.
## 输出格式

For each test case, first output the line with the minimal possible number of additional edges $A$. 
Then output $A$ lines, each describing one edge as $u_i$ $v_i$, where $u_i$ and $v_i$
are the numbers of vertices to connect. After adding these edges, the resulting graph must be a strong cactus.
## 样例

### 样例输入 #1
```
6 1
7 1 2 5 6 2 3 4
3 1
4 1 2 3 1
5 2
3 1 3 5
3 1 2 4
7 2
6 1 2 3 4 5 3
3 6 5 7
0 0
```
### 样例输出 #1
```
1
1 4
0
1
5 4
2
1 3
6 7
```


---

---
title: "[NERC 2020] Is It Rated?"
layout: "post"
diff: 省选/NOI-
pid: P12908
tag: ['2020', '交互题', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Is It Rated?
## 题目描述

The popular improv website $\emph{Interpretation Impetus}$ hosts regular improv
contests and maintains a rating of the best performers. However, since improv can often go horribly wrong, the website is notorious for declaring improv contests $\emph{unrated}$. It now holds a wager before each improv contest where the participants try to predict whether it will be rated or unrated, and they are now more popular than the improv itself.

Izzy and $n$ other participants take part in each wager. First, they each make
their prediction, expressed as $\texttt{1}$ ("rated") or $\texttt{0}$ ("unrated"). Izzy
always goes last, so she knows the predictions of the other participants when making
her own. Then, the actual competition takes place and it is declared either rated
or unrated.

You need to write a program that will interactively play as Izzy. There will be $m$ wagers held in 2021, and Izzy's goal is to have at most
$1.3\cdot b + 100$ wrong predictions after all those wagers, where $b$ is the $\emph{smallest}$
number of wrong predictions that any other wager participant will have after all those wagers. 

The number $b$ is not known in advance. Izzy also knows nothing about
the other participants --- they might somehow always guess correctly, or their predictions might be correlated. Izzy's predictions, though, do not affect the predictions of the other participants and the decision on the contest being rated or not --- in other words, in each test case, your program always receives the same inputs, no matter what it outputs.

### Interactive Protocol

First, a solution must read two integers $n$ ($1 \le n \le 1000$) and $m$ ($1 \le m \le 10\,000$). Then, the solution must process $m$ wagers. For each of them, the solution must first read a string consisting of $n$ $\texttt{0}$s and $\texttt{1}$s, in which the $i$-th character denotes the guess of the $i$-th participant. Then, the solution must print Izzy's guess as $\texttt{0}$ or $\texttt{1}$.
Don't forget to flush the output after printing it! Then, the solution must read the actual outcome, also as $\texttt{0}$ or $\texttt{1}$, and then proceed to the next wager, if this wasn't the last one. 

Your solution will be considered correct if it makes at most $1.3\cdot b + 100$ mistakes, where $b$ is the smallest number of mistakes made by any other participant. Note that if a solution outputs anything except $\texttt{0}$ or $\texttt{1}$ for a wager, it will be considered incorrect even if it made no other mistakes. 

There are 200 test cases in this problem.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
3 4
000

1
100

1
001

0
111

1
```
### 样例输出 #1
```


0


0


1


1


```
## 提示

In the example, the participants made 1, 2, and 3 mistakes respectively, therefore $b=1$ (the smallest of these numbers). Izzy made 3 mistakes, which were not more than $1.3\cdot b + 100=101.3$, so these outputs are good enough to pass this test case (as are any other valid outputs).


---

---
title: "[NERC 2020] Japanese Game"
layout: "post"
diff: 省选/NOI-
pid: P12909
tag: ['贪心', '2020', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Japanese Game
## 题目描述

Joseph really likes the culture of Japan. Last year he learned Japanese traditional clothes and visual arts and now he is trying to find out the secret of the Japanese game called Nonogram.

In the one-dimensional version of the game, there is a row of $n$ empty cells, some of which are to be filled with a pen. There is a description of a solution called a $\emph{profile}$ --- a sequence of positive integers denoting the lengths of consecutive sets of filled cells. For example, the profile of $[4, 3, 1]$ means that there are sets of four, three, and one filled cell, in that order, with at least one empty cell between successive sets.

![](https://cdn.luogu.com.cn/upload/image_hosting/7vyfivv3.png)

A suitable solution for $n = 12$ and $p = [4, 3, 1]$.

![](https://cdn.luogu.com.cn/upload/image_hosting/8lednxrh.png)

A wrong solution: the first four filled cells should be consecutive.

![](https://cdn.luogu.com.cn/upload/image_hosting/r2jcjjbb.png)

A wrong solution: there should be at least one empty cell before the last filled cell.

Joseph found out that for some numbers $n$ and profiles $p$ there are lots of ways to fill the cells to satisfy the profile. Now he is in the process of solving a nonogram consisting of $n$ cells and a profile $p$. He has already created a $\emph{mask}$ of $p$ --- he has filled all the cells that must be filled in every solution of the nonogram.

![](https://cdn.luogu.com.cn/upload/image_hosting/io9ajtcp.png)

The mask for $n = 12$ and $p = [4, 3, 1]$: all the filled cells above are filled in every solution.

After a break, he lost the source profile $p$. He only has $n$ and the mask $m$. Help Joseph find any profile $p'$ with the mask $m$ or say that there is no such profile and Joseph has made a mistake.
## 输入格式

The only line contains a string $m$ --- the mask of the source profile $p$.
The length of $m$ is $n$ ($1 \le n \le 100\,000$).
The string $m$ consists of symbols $\texttt{\#}$ and $\texttt{\_}$ --- denoting filled and empty cells respectively.
## 输出格式

If there is no profile with the mask $m$, output the number $-1$.
Otherwise, on the first line, output an integer $k$--- the number of integers in the profile $p'$. 
On the second line, output $k$ integers of the profile $p'$.
## 样例

### 样例输入 #1
```
__#_____ 
```
### 样例输出 #1
```
2
3 2
```
### 样例输入 #2
```
_#
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
___ 
```
### 样例输出 #3
```
0
```


---

---
title: "[NERC 2019] DevOps Best Practices"
layout: "post"
diff: 省选/NOI-
pid: P12937
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] DevOps Best Practices
## 题目描述

Daisy is a senior software engineer at RainyDay, LLC. She has just implemented three new features in their product: the first feature makes their product work, the second one makes their product fast, and the third one makes their product correct.
The company encourages at least some testing of new features, so Daisy appointed her intern Demid to write some tests for the new features.

Interestingly enough, these three features pass all the tests on Demid's development server, which has index 1, but might fail the tests on some other servers.

After Demid has completed this task, Daisy appointed you to deploy these three features to all $n$~servers of your company. For every feature $f$ and every server $s$, Daisy told you whether she wants the feature $f$ to be deployed on the server $s$. If she wants it to be deployed, it must be done even if the feature $f$ fails the tests on the server $s$. If she does not want it to be deployed, you may not deploy it there.

Your company has two important instruments for the deployment of new features to servers: Continuous Deployment (CD) and Continuous Testing (CT). CD can be established between several pairs of servers, forming a directed graph. CT can be set up on some set of servers.

If CD is configured from the server $s_1$ to the server $s_2$ then every time $s_1$ receives a new feature $f$ the system starts the following deployment process of $f$ to $s_2$:

- If the feature $f$ is already deployed on the server $s_2$, then nothing is done.
- Otherwise, if CT is not set up on the server $s_1$, then the server $s_1$ just deploys the feature $f$ to the server $s_2$ without any testing.
- Otherwise, the server $s_1$ runs tests for the feature $f$. If the tests fail on the server $s_1$, nothing is done. If the tests pass, then the server $s_1$ deploys the feature $f$ to the server $s_2$. 

You are to configure the CD/CT system, and after that Demid will deploy all three features on his development server. Your CD/CT system must deploy each feature exactly to the set of servers that Daisy wants.

Your company does not have a lot of computing resources, so you can establish CD from one server to another at most $264$ times.
## 输入格式

The first line contains integer $n$ ($2 \le n \le 256$) --- the number of servers in your company.

Next $n$ lines contain three integers each. The $j$-th integer in the $i$-th line is $1$ if Daisy wants the $j$-th feature to be deployed to the $i$-th server, or $0$ otherwise.

Next $n$ lines contain three integers each. The $j$-th integer in the $i$-th line is $1$ if tests pass for the $j$-th feature on the $i$-th server, or $0$ otherwise.

Demid's development server has index $1$. It is guaranteed that Daisy wants all three features to be deployed to the server number 1, and all three features pass their tests on the server number 1.
## 输出格式

If it is impossible to configure CD/CT system with CD being set up between at most $264$ pairs of servers, then output the single line  $\texttt{Impossible}$.

Otherwise, the first line of the output must contain the line $\texttt{Possible}$.

Next line must contain $n$ space-separated integers --- the configuration of CT. The $i$-th integer should be $1$ if you set up CT on the $i$-th server, or $0$ otherwise.

Next line must contain the integer $m$ ($0 \le m \le 264$) --- the number of CD pairs you want to set up.

Each of the next $m$ lines must describe CD configuration, each line with two integers $s_i$ and $t_i$ ($1 \le s_i, t_i \le n$; $s_i \ne t_i$), establishing automated deployment of new features from the server $s_i$ to the server $t_i$.
## 样例

### 样例输入 #1
```
3
1 1 1
1 0 1
1 1 1
1 1 1
0 0 0
1 0 1
```
### 样例输出 #1
```
Possible
1 1 1
2
3 2
1 3
```
### 样例输入 #2
```
2
1 1 1
0 0 1
1 1 1
1 1 0
```
### 样例输出 #2
```
Impossible
```
## 提示

CD/CT system for the first sample test is shown below.

![](https://cdn.luogu.com.cn/upload/image_hosting/stnjo553.png)


---

---
title: "[NERC 2019] Foolprüf Security"
layout: "post"
diff: 省选/NOI-
pid: P12939
tag: ['2019', 'Special Judge', 'ICPC', 'Prüfer 序列', 'NERC/NEERC']
---
# [NERC 2019] Foolprüf Security
## 题目描述

Alice and Bob obtained a map of the secret underground facility. The facility consists of $n$ $\emph{security units}$ and $m$ $\emph{chemical labs}$, connected by bidirectional tunnels. The map of this facility forms a $\emph{tree}$: there are exactly $n + m - 1$ tunnels, and there are no cycles. Vertices corresponding to security units have numbers from $1$ to $n$, chemical labs have numbers from $n+1$ to $n+m$. Each tunnel connects a security unit to a chemical lab; there are no tunnels between two security units or two chemical labs.

In case Alice or Bob gets captured, they decided to split the map into two pieces. To do that, they calculated the $\emph{Prüfer code}$ of the tree. Alice then saved some of the numbers between $1$ and $n$ to her data storage in the same order as they go in the original code, and Bob saved some of the numbers from $n+1$ to $n+m$ to his storage in the same way.

A Prüfer code of a tree on $k$ vertices is a sequence of $k - 2$ integers from $1$ to $k$, constructed as follows. Find the leaf (a vertex with degree one) with the smallest label, remove it from the tree, then print the label of its only neighbor. Repeat this $k - 3$ more times, until only one edge remains. The printed sequence of $k - 2$ vertex labels is the Prüfer code.

Alice and Bob safely returned and they are ready to combine their data to restore the original map. They could make a mistake during the backup, meaning no such map exists. Alice and Bob need your help to restore any possible map of the facility consistent with the collected data, so that both Alice's and Bob's parts are subsequences of the Prüfer code of the map.
## 输入格式

The first line of the input contains four integers $n$, $m$, $k_a$, and $k_b$ ($2 \le n, m \le 10^5$; $1 \le k_a, k_b$; $k_a + k_b \le n + m - 2$).
The second line contains $k_a$ integers $a_1, a_2, \ldots, a_{k_a}$ ($1 \le a_i \le n$) --- Alice's part of the map.
The third line contains $k_b$ integers $b_1, b_2, \ldots, b_{k_b}$ ($n + 1 \le b_i \le n + m$) --- Bob's part of the map.
## 输出格式

If there's no such map, print $\tt{No}$.

Otherwise, print $\tt{Yes}$ on the first line, followed by $n + m - 1$ lines describing the possible facility map. Each line should contain two integers $u_i$ and $v_i$ --- the security unit and the chemical lab connected by the $i$-th tunnel of the facility.
## 样例

### 样例输入 #1
```
4 5 4 2
1 3 3 4
7 8
```
### 样例输出 #1
```
Yes
1 5
1 6
2 7
6 3
3 7
9 4
3 8
4 8
```
### 样例输入 #2
```
4 3 3 1
3 2 2
6
```
### 样例输出 #2
```
No
```
## 提示

The Prüfer code of the tree in the first example is $(\underline{7}, \mathbf{1}, 6, \mathbf{3}, \mathbf{3}, \underline{8}, \mathbf{4})$.

![](https://cdn.luogu.com.cn/upload/image_hosting/6z6yk20m.png)


---

---
title: "[NERC 2019] Intriguing Selection"
layout: "post"
diff: 省选/NOI-
pid: P12942
tag: ['2019', '交互题', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Intriguing Selection
## 题目描述

$\emph{This is an interactive problem.}$

You are the head coach of a chess club. The club has $2n$ players, each player has some $\emph{strength}$ which can be represented by a number, and all those numbers are distinct. The strengths of the players are not known to you.

You need to select $n$ players who would represent your club in the upcoming championship. Naturally, you want to select $n$ players with the highest strengths.

You can organize matches between the players to do that. In every match, you pick two players, they play some games, and you learn which one of the two has higher strength. You can wait for the outcome of a match before deciding who will participate in the next one.

However, you do not want to know $\emph{exactly}$ how those $n$ players compare between themselves, as that would make the championship itself less $\emph{intriguing}$. More formally, you must reach a state where there is exactly one way to choose $n$ players with the highest strengths that is consistent with the outcomes of the matches you organized, but there must be at least two possible orderings of those $n$ players by strength that are consistent with the outcomes of the matches you organized.

### Interaction Protocol

Your program has to process multiple test cases in one run. First, it should read the integer $t$ ($t \ge 1$) --- the number of test cases. Then, it should process the test cases one by one.

In each test case, your program should start by reading the integer $n$ ($3 \le n \le 100$) --- the number of players to select out of $2n$ players. The sum of squares of the values of $n$ over all test cases does not exceed $10\,000$.

Then your program can organize matches zero or more times. To organize a match, your program should print a match description formatted as $\tt{?\ i\ j}$ --- a question mark followed by two distinct numbers of players participating in the match. The players are numbered from 1 to $2n$, inclusive. Remember to flush the output after printing the match description. Then your program should read the match outcome --- it will be either the greater-than character ($\tt{>}$), if the first player in the match description has higher strength, or the less-than character ($\tt{<}$), if the second player in the match description has higher strength.

Your program can organize at most $4n^2$ matches. After it is done organizing matches, it should print the exclamation mark ($\tt{!}$) and continue to the next test case, or exit gracefully if this was the last test case. Remember to flush the output after printing the exclamation mark.

There must be exactly one way to choose $n$ players with the highest strength that is consistent with the outcomes of the matches you organized, but there must be at least two possible orderings of those $n$ players by their strength that are consistent with the outcomes of the matches you organized.

The judging program picks some distinct numbers as the strengths of all players before your program starts organizing matches and uses them to answer the requests.
## 输入格式

See Interaction Protocol
## 输出格式

See Interaction Protocol
## 样例

### 样例输入 #1
```
2
3

>

<

>

<

>

>

3

<

<

<

>

>

```
### 样例输出 #1
```


? 1 3

? 4 2

? 4 5

? 6 5

? 3 4

? 5 6

!

? 3 4

? 4 2

? 5 3

? 6 4

? 3 1

!
```
## 提示

In the example, the players in the first test case are sorted by strength in decreasing order. From the matches in the example output, we can deduce that players 1, 2, and 3 have the highest strength, but we do not know how the player 1 compares to the player 2.


---

---
title: "[NWRRC 2023] Colorful Village"
layout: "post"
diff: 省选/NOI-
pid: P13583
tag: ['2023', 'Special Judge', '2-SAT', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Colorful Village
## 题目描述

Colorful Village is a popular tourist destination. It has $2n$ houses, numbered from $1$ to $2n$. Every house has one of $n$ colors, numbered from $1$ to $n$. Coincidentally, for each of the $n$ colors, exactly two houses are colored into it.

There are $2n-1$ bidirectional roads in Colorful Village. Each road connects two different houses, and it is possible to reach any house from any other house using these roads.

Catherine is planning a trip to Colorful Village. Her time is limited, so she wants to choose a set $S$ of $n$ houses to visit, with exactly one house of each color. However, since Catherine also needs to move between houses, the set of houses she is going to visit must be connected. In other words, it must be possible to reach any house in $S$ from any other house in $S$ using the roads, and only visiting houses in $S$ on the way.

Help Catherine to find a connected set $S$ of $n$ houses, one of each color, or report that no such set exists.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 10^5$).

The second line contains $2n$ integers $c_1, c_2, \ldots, c_{2n}$, denoting the colors of the houses in Colorful Village ($1 \le c_i \le n$). Every integer from $1$ to $n$ appears exactly twice in this line.

The $i$-th of the following $2n-1$ lines contains two integers $u_i$ and $v_i$, denoting the houses connected by the $i$-th road ($1 \le u_i, v_i \le 2n$; $u_i \ne v_i$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.
## 输出格式

For each test case, print a single integer $-1$ if the required set of houses does not exist.

Otherwise, print $n$ distinct integers $s_1, s_2, \ldots, s_n$ in any order, denoting a connected set $S$ of $n$ houses, one of each color ($1 \le s_i \le 2n$). If there are multiple answers, print any of them.

## 样例

### 样例输入 #1
```
2
4
1 3 1 3 4 4 2 2
1 6
5 3
2 4
7 1
7 5
5 8
2 5
3
1 1 2 2 3 3
1 2
2 3
3 4
4 5
5 6
```
### 样例输出 #1
```
2 3 5 7
-1
```


---

---
title: "[NWRRC 2023] First Solved, Last Coded"
layout: "post"
diff: 省选/NOI-
pid: P13586
tag: ['模拟', '动态规划 DP', '2023', 'Special Judge', '区间 DP', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] First Solved, Last Coded
## 题目描述

In ICPC, teamwork is everything. That's why everyone on your team has a well-defined role: Sol the Solver can solve any problem in the problem set, Codie the Coder can implement any solution that Sol comes up with, and you... are the glue that holds everything together. Sol and Codie are very picky about the order of problems they would solve/code, and your job is to satisfy their preferences.

There will be $n$ problems in the upcoming contest, and you know the general topic of each problem: greedy, geometry, graphs, etc. For simplicity, we will represent each topic with an integer from $1$ to $n$. These integers don't have to be distinct, that is, multiple problems in the contest can have the same topic.

Sol wants to solve problems in a specific order of topics: first, the problem with the topic $a_1$, after that, the problem with the topic $a_2$, $\ldots$, and finally, the problem with the topic $a_n$. Codie also has a preference list: $b_1, b_2, \ldots, b_n$, only willing to code problems in that order of topics.

Your job during the contest will be to take solution sheets from Sol and hand them to Codie in the correct order. As your team only has one table to work with, you don't have enough space to arrange all the solutions neatly. Thus, you came up with the following workflow: you will ask Sol for solutions (who will hand them to you in order $a_1, a_2, \ldots, a_n$), store them in a stack on your part of the table, and hand them to Codie to code (in order $b_1, b_2, \ldots, b_n$).

More formally, at any moment during the contest, you have (at most) two actions you can make:

- If there are still any unsolved problems remaining, ask Sol for another solution and put it on top of your stack of solution sheets. This action is denoted by the character $\tt{S}$.
- If your stack is not empty, take the solution sheet from the top of your stack and give it to Codie to implement. This action is denoted by the character $\tt{C}$.

For the given lists of Sol's and Codie's preferences, find a sequence of actions that ensures that all problems are solved and coded in the correct order. Consider all solving and coding times insignificant --- managing solution sheets is a much harder and more important job anyway.
## 输入格式

The first line contains a single integer $n$, denoting the number of problems in the contest ($1 \le n \le 100$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$, denoting Sol's preferred order of topics ($1 \le a_i \le n$).

The third line contains $n$ integers $b_1, b_2, \ldots, b_n$, denoting Codie's preferred order of topics ($1 \le b_i \le n$).

The given lists are equal as multisets: every integer occurs the same number of times in $A$ and in $B$.
## 输出格式

If your task is impossible, print $\tt{NO}$. Otherwise, print $\texttt{YES}$ on the first line, followed by the sequence of actions on the second line: a string consisting of $2n$ characters $\tt{S}$ or $\tt{C}$ ($n$ of each), describing your actions in order.

You are not allowed to ask Sol for more solutions if all $n$ problems have already been solved, or give Codie a solution with the wrong topic. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
4
4 1 2 2
1 2 4 2
```
### 样例输出 #1
```
YES
SSCSCCSC
```
### 样例输入 #2
```
3
2 3 1
1 2 3
```
### 样例输出 #2
```
NO
```


---

---
title: "[NWRRC 2023] Loops"
layout: "post"
diff: 省选/NOI-
pid: P13592
tag: ['平衡树', '2023', 'Special Judge', '排序', '构造', 'ICPC', 'Ad-hoc', 'NWRRC']
---
# [NWRRC 2023] Loops
## 题目描述

Consider four integers $A$, $B$, $C$, and $D$, such that $A < B < C < D$. Let's put them in the corners of a square in some order and draw a loop $A - B - C - D - A$. Depending on the arrangement of the integers, we can get different loop shapes, but some arrangements produce the same shape:

![](https://cdn.luogu.com.cn/upload/image_hosting/8hyu6a9v.png)

There are three possible loop shapes we can get:

![](https://cdn.luogu.com.cn/upload/image_hosting/ikan9lhl.png)

Now consider an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive. Each $2\times 2$ square in this matrix can be seen as a square with integers in its corners. Let's build a loop for each of these squares like we did before:

![](https://cdn.luogu.com.cn/upload/image_hosting/y3rml1pm.png)

Your task is to perform the inverse operation. You are given the shape types for all $(n-1)(m-1)$ loops, and you need to build an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive, that produces these shapes.
## 输入格式

The first line contains two integers $n$ and $m$ ($2\le n, m\le 500$).

Each of the next $n-1$ lines contains a string of $m-1$ characters without spaces. Each character is a digit from $1$ to $3$, denoting the type of the shape of the corresponding loop.
## 输出格式

Print an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive, that produces the shapes of the loops in the input.

It can be shown that such a matrix always exists. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
3 4
113
231
```
### 样例输出 #1
```
9 11 7 12
4 6 1 8
2 10 5 3
```


---

---
title: "[ICPC 2025 APC]  Attraction Score"
layout: "post"
diff: 省选/NOI-
pid: P13616
tag: ['2024', 'ICPC']
---
# [ICPC 2025 APC]  Attraction Score
## 题目描述

在虚构的国家 Manteiv，有 $n$ 个城市，编号从 $1$ 到 $n$。我们可以将这些城市视为在一个二维坐标系的平面上，其中城市 $i$ 的坐标为 $(x_i, y_i)$。没有两个城市位于相同的位置。

这里有 $m$ 条高速公路，编号从 $1$ 到 $m$，每条高速公路都是以两个不同的城市为其端点的线段，并且沿线设有一定数量的景点。具体来说，高速公路 $j$ 有 $a_j$ 个景点，并连接城市 $u_j$ 和 $v_j$ 作为其端点。由于高速公路上的交叉路口会导致交通堵塞，且在另一条高速公路上方建造新的高速公路成本高昂，因此题目保证：
* 任意两条高速公路除了在城市作为端点外，不会在任何其他点相交。
* 任意一条高速公路除了其两个端点城市外，不会穿过任何其他城市。
* 每对城市之间最多只有一条高速公路相连。

Manteiv 旅游部希望选择一个城市子集作为旅游景点。直观地说，旅游部希望所选城市中有许多对城市由景点众多的高速公路相连。形式上，一个非空城市子集 $S$ 的吸引力分数定义如下：

* 对于每一对整数 $(a, b)$，如果 $a < b$，城市 $a$ 和城市 $b$ 都在 $S$ 中，并且它们之间有高速公路相连，则将该高速公路的景点数加到分数中。
* 令 $f(S)$ 为满足 $a < b$ 的整数对 $(a, b)$ 的数量，其中城市 $a$ 和城市 $b$ 都在 $S$ 中，但它们之间没有高速公路相连。分数会产生一个惩罚（负）分数，大小为 $10^6$ 乘以 $f(S)$ 的平方。换句话说，从分数中减去 $10^6 \times f(S)^2$。

例如，假设 $n=3$，城市 $1$ 和 $2$ 由一条有 $10$ 个景点的高速公路连接，城市 $2$ 和 $3$ 由一条有 $20$ 个景点的高速公路连接，而城市 $1$ 和 $3$ 之间没有高速公路。
- 城市子集 $\{1\}$ 的吸引力分数为 $0$。
- 城市子集 $\{1,2\}$ 的吸引力分数为 $10 - 10^6 \times 0^2 = 10$。
- 城市子集 $\{2,3\}$ 的吸引力分数为 $20 - 10^6 \times 0^2 = 20$。
- 城市子集 $\{1,2,3\}$ 的吸引力分数为 $10 + 20 - 10^6 \times 1^2 = -999970$。

作为旅游部的顾问，您需要找到所有可能的非空城市子集 $S$ 中最大的吸引力分数。
## 输入格式

输入的第一行包含两个整数 $n$ 和 $m$ ($1 \le n \le 100,000; 0 \le m \le 300,000$)。

接下来的 $n$ 行，每行包含两个整数。第 $i$ 行包含 $x_i$ 和 $y_i$ $(0 \le x_i, y_i \le 10^9)$。

再接下来的 $m$ 行，每行包含三个整数。第 $j$ 行包含 $u_j$，$v_j$ 和 $a_j$ $(1 \le u_j < v_j \le n; 0 \le a_j \le 10^6)$。

保证所有高速公路都满足题目描述中的条件。
## 输出格式

输出一个整数，代表所有可能的非空城市子集 $S$ 中最大的吸引力分数。
## 样例

### 样例输入 #1
```
3 2
0 0
0 1
1 0
1 2 10
2 3 20
```
### 样例输出 #1
```
20
```
### 样例输入 #2
```
3 3
0 0
0 1
1 0
1 2 10
2 3 20
1 3 30
```
### 样例输出 #2
```
60
```
## 提示

**样例解释 #1**

该样例即为题目描述中给出的例子。城市子集 $\{2,3\}$ 得到了最高的吸引力分数 $20$。

**样例解释 #2**

城市和高速公路如图 B.1 所示。通过在 $S$ 中选择城市 $1, 2, 3$，吸引力分数为 $10 + 20 + 30 - 10^6 \times 0^2 = 60$。

![](https://cdn.luogu.com.cn/upload/image_hosting/8hds9s7r.png)



---

---
title: "[ICPC 2025 APC] Tree Quiz"
layout: "post"
diff: 省选/NOI-
pid: P13625
tag: ['线段树', '2024', '可持久化线段树', 'ICPC']
---
# [ICPC 2025 APC] Tree Quiz
## 题目描述

你的朋友想考考你。给你一棵有 $n$ 个节点的有根树，节点编号从 $1$ 到 $n$。对于每个节点 $i$，它的父节点是 $p_i$，除了根节点（没有父节点的节点）的 $p_i=0$。如果节点 $u=v$，或者节点 $u$ 是节点 $v$ 的父节点（如果存在）的祖先，那么我们说节点 $u$ 是节点 $v$ 的一个祖先。

如果节点 $z$ 同时是节点 $x$ 和节点 $y$ 的祖先，我们称节点 $z$ 是节点 $x$ 和 $y$ 的一个共同祖先。如果节点 $z$ 是节点 $x$ 和 $y$ 的一个共同祖先，并且节点 $x$ 和 $y$ 的任何一个共同祖先也都是节点 $z$ 的祖先，那么我们称节点 $z$ 是节点 $x$ 和 $y$ 的最近共同祖先。我们将节点 $x$ 和 $y$ 的最近共同祖先表示为 $\operatorname{LCA}(x,y)$。特别地，$\operatorname{LCA}(x,x)=x$。

你的朋友想要运行以下伪代码：

```
let L be an empty array
for x = 1 to n
  for y = 1 to n
    append ((x-1)*n*n + (LCA(x,y)-1)*n + (y-1)) to L
sort L in non-decreasing order
```

你的朋友有 $q$ 个问题，编号从 $1$ 到 $q$。在第 $j$ 个问题中，会给你一个整数 $k_j$，并要求你找出数组 $L$ 中的第 $k_j$ 个元素。请注意，$L$ 是以 $1$ 为起始下标的，所以其下标范围从 $1$ 到 $n^2$。为了通过测试，你必须回答所有问题。
## 输入格式

输入的第一行包含两个整数 $n$ 和 $q$（$1 \le n \le 100,000$；$1 \le q \le 100,000$）。第二行包含 $n$ 个整数 $p_1, p_2, \dots, p_n$（对于所有的 $i$，$0 \le p_i \le n$）。保证给定的值代表一棵有根树。接下来的 $q$ 行每行包含一个整数。第 $j$ 行包含 $k_j$（$1 \le k_j \le n^2$）。
## 输出格式

对于每个问题，按顺序输出一个整数作为问题的答案。
## 样例

### 样例输入 #1
```
5 3
3 0 2 2 3
1
18
25
```
### 样例输出 #1
```
0
82
124
```
## 提示

输入中的树如图 K.1 所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xe1w5tx.png)

$L$ 的元素为 $(0, 6, 8, 12, 14, 30, 31, 32, 33, 34, 56, 58, 60, 62, 64, 80, 81, 82, 84, 93, 106, 108, 110, 112, 124)$。


---

---
title: "[ICPC 2025 APC] XOR Operations"
layout: "post"
diff: 省选/NOI-
pid: P13626
tag: ['2024', 'ICPC']
---
# [ICPC 2025 APC] XOR Operations
## 题目描述

给定 $n$ 个整数 $a_1, a_2, \dots, a_n$。你有一个包含 $n$ 个整数的序列 $B=(b_1, b_2, \dots, b_n)$，初始时所有元素均为零。

在一次操作中，你选择两个不同的下标 $i$ 和 $j$，然后同时
* 将 $b_i$ 替换为 $b_i \oplus a_i \oplus a_j$，并且
* 将 $b_j$ 替换为 $b_j \oplus a_i \oplus a_j$。

注意，$\oplus$ 代表按位异或（bitwise XOR）操作。对于两个整数，其操作结果整数的每个二进制位，当且仅当两个操作数对应的二进制位有且仅有一个为 $1$ 时，该位为 $1$。例如，$3 \oplus 10 = 9$，因为 $(0011)_2 \oplus (1010)_2 = (1001)_2$。

你想要计算通过零次或多次操作可以得到的不同序列 $B$ 的数量。由于这个数字可能非常大，请计算结果对 $998,244,353$ 取模。

两个长度为 $n$ 的序列被认为是不同的，当且仅当存在一个下标 $i$ ($1 \le i \le n$)，使得一个序列的第 $i$ 个元素与另一个序列的第 $i$ 个元素不同。
## 输入格式

输入的第一行包含一个整数 $n$ ($2 \le n \le 200,000$)。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$ ($0 \le a_i < 2^{30}$)。
## 输出格式

输出一个整数，代表可以得到的不同序列 $B$ 的数量，结果对 $998,244,353$ 取模。
## 样例

### 样例输入 #1
```
3
1 2 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4
852415 852415 852415 852415
```
### 样例输出 #2
```
1
```
## 提示

**样例解释 #1**

从 $B=(0,0,0)$ 开始，我们可以得到以下两个序列 $B$：
* 对 $i=1$ 和 $j=2$ 执行操作。我们将得到 $B=(3,3,0)$。
* 在此之后，对 $i=2$ 和 $j=3$ 执行操作。我们将得到 $B=(3,0,3)$。

从 $B=(0,0,0)$ 开始，我们也可以得到以下序列 $B$：
* 对 $i=2$ 和 $j=3$ 执行操作。我们将得到 $B=(0,3,3)$。

可以证明，$(0,0,0)$, $(3,3,0)$, $(3,0,3)$ 和 $(0,3,3)$ 是唯一可能得到的序列 $B$。因此，答案是 $4$。


---

---
title: "[NWRRC 2021] Day Streak"
layout: "post"
diff: 省选/NOI-
pid: P13631
tag: ['线段树', '2021', 'Special Judge', 'ICPC', '双指针 two-pointer', 'NWRRC']
---
# [NWRRC 2021] Day Streak
## 题目描述

Recently Deltaforces, a famous competitive programming website, added a lot of new visual information to user profiles. In particular, there is a maximum day streak --- the maximum number of days in a row with at least one problem solved. You decided that the maximum day streak in your profile does not accurately represent your training efforts. So you came up with a thought --- what if you could change the time zone in your profile to increase the maximum day streak?

Let's formalize this setting as follows. Suppose you have solved $n$ problems, and the $i$-th problem was solved at time $a_i$. There are $m$ time zones, numbered from $0$ to $m - 1$. The default time zone is $0$. If you decide to change your time zone to $t$, all solutions' timestamps increase by $t$: the problem solved at time $a_i$ is now considered to be solved at time $a_i + t$, for all $i$ simultaneously.

The problem solved at time $x$ is considered to be solved on day number $\lfloor \frac{x}{m} \rfloor$. Here $\lfloor v \rfloor$ means $v$ rounded down to the greatest integer less than or equal to $v$.

To display the maximum day streak, Deltaforces finds such $l$ and $r$ that you have solved at least one problem on each of days $l, l+1, \ldots, r$, and $r - l + 1$ is as large as possible. Then your maximum day streak is shown as $r - l + 1$.

Find the maximum day streak you can achieve by selecting a time zone.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2 \cdot 10^5$). Description of the test cases follows.

The first line of each test case contains two integers $n$ and $m$ --- the number of solved problems and the number of time zones ($1 \le n \le 2 \cdot 10^5$; $1 \le m \le 10^9$). The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ --- distinct timestamps of your solutions, in chronological order ($0 \le a_1 < a_2 < \dotsb < a_n \le 10^9$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print two integers $s$ and $t$ --- the maximum day streak and any time zone that achieves it ($1 \le s \le n$; $0 \le t < m$).
## 样例

### 样例输入 #1
```
5
4 10
0 3 8 24
2 10
32 35
10 1
0 1 3 4 5 6 7 10 11 12
10 24
0 1 3 4 5 6 7 10 11 12
8 24
26 71 101 147 181 201 244 268
```
### 样例输出 #1
```
3 2
2 5
5 0
2 12
4 15
```
## 提示

In the first example test case, when you select time zone $2$, the timestamps of your solutions change to $2$, $5$, $10$, and $26$. It means the problems are now considered to be solved on days $0$, $0$, $1$, and $2$; that is a~$3$-day streak. Time zones $3$, $4$, and $5$ yield the same answer.

In the second example test case, timestamps of your solutions are $37$ and $40$ in time zone $5$, which corresponds to days $3$ and $4$. Time zones $6$ and $7$ also work.

In the third example test case, only one time zone exists, and your maximum day streak is $5$.

In the fourth example test case, you have solved many problems but in a short period of time, and you can't obtain more than a $2$-day streak.


---

---
title: "[CERC 2020] Bank Robbery"
layout: "post"
diff: 省选/NOI-
pid: P13652
tag: ['2020', '交互题', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2020] Bank Robbery
## 题目描述

Each day, robbers plan to rob exactly one bank in a region. Due to undercover informers' work, the detectives get to know which particular bank is being targeted by the robbers on each day just before $6$ AM. The presence of a single detective in a bank is enough to deter the robbers, so the detectives want to plan their positions intelligently. Robbing is planned to happen during the daylight after $8$ AM, when the banks open, and is always successful when there is no detective in the bank. Unfortunately, though, the number of detectives is not very big so there may not be enough of them to keep the banks safe. To ensure they are effective, there can be at most one detective in any bank at any time. A detective can leave a bank and travel to another bank only between $6$ AM and $8$ AM.

Given enough days, any detective would be able to move from any of the banks to any other via the $2$-hour transits. Due to the travel restrictions (mainly time), they are not able to move freely but are restricted to move only between banks that are close to each other. The region is quite specific because there is a minimum number of bank pairs that are close that conform to the above restrictions. Additionally, no bank is close to exactly two other banks.

Now, there is a quest for a computer simulation: determining if the robbers can succeed in at least one robbery during one year. The simulation is run against the preprogrammed judge as a kind of computer game, with strong consequences in real life. In the game, the attacker represents the robbers, the defender manages the detectives.

In the beginning, the simulation is given the system of connections between close banks and the number of detectives available. Then, the simulation chooses whether it plays as an attacker or as a defender. The judge automatically adopts the opposite role. Next, the defender places the given number of detectives in banks according to its own choice.

Next, the game proceeds in turns. In one turn, the attacker announces a bank and then the defender moves each detective over at most one connection. The defender's aim is to choose the movements in such a way the announced bank is occupied by a detective at the end of the turn. If there is no detective in the announced bank after all movements in the turn, the attacker immediately wins the game. Otherwise, the defender defends the turn and the next turn ensues. If the defender can successfully defend for one year ($365$ turns), they win the game. During the game, the location of each detective is known to both the attacker and the defender.

The goal of the simulation you have to write is to choose a role smartly so that you are able to win the game.

### Interactive Mode

The simulation is evaluated in so-called _interactive_ mode, which means that the input received depends on the output produced so far. The output of the judge is the input of the simulation and vice versa. If you have no previous experience with such problems, just do not be afraid — you are still reading from the standard input and printing to the standard output. There are just a few things to pay attention to.

After printing each response to the input from the judge, the simulation has to flush the output buffer. For example, it may use fflush(stdout) or cout.flush() in C++, System.out.flush() in Java, or stdout.flush() in Python. Also, it should never try to read more data than what is guaranteed to be ready in the input, because that may cause it to hang indefinitely. In particular, be careful to _not_ invoke anything like scanf("%d ") or scanf("%d\n"), as such formats try to scan forward for any further whitespace. Instead, use just scanf("%d") without trailing whitespace.

After you choose a role and print a corresponding output, the following exchange is repeated for up to 365 times: The attacker outputs the bank index $0 \leq v \leq B-1$ which they choose to attack. Then, the defender outputs an integer $k$ and then $k$ pairs $b_i, c_i$ ($0 \leq b_i, c_i \leq B-1$), each of which represents a detective move from bank $b_i$ to bank $c_i$. The detectives may only move along connections between close banks. The attacker ends the sequence of attacks by outputting $-1$. The defender may give up by ending the program.

In this exchange, the output of one player is always the input of the other player.
## 输入格式

The first input line contains values $B$ and $D$ ($4 \leq B \leq 100, 0 \leq D \leq B$), the number of banks and the number of detectives. The banks are labeled by integers $0, 1, \ldots, B-1$. Each of the next $B-1$ lines contains a pair of integers $b_i$ and $c_i$ ($0 \leq b_i, c_i \leq B-1$) representing a connection between two close banks $b_i$ and $c_i$.

## 输出格式

After reading the input, if you choose to attack, then prints a line with string ATTACK. Otherwise, print a line with string DEFEND and on the next line it print $D$ different indices, in arbitrary order, of all the banks where a detective is initially located. The remainder of the exchange happens interactively.

## 样例

### 样例输入 #1
```
4 3
0 1
0 2
0 3


2

3

-1
```
### 样例输出 #1
```




DEFEND
0 1 2

0

2 1 0 0 3
```
### 样例输入 #2
```
4 1
0 1
0 2
0 3

0

1 0 1
```
### 样例输出 #2
```




ATTACK

1

2
```
## 提示

For clarity, the above data are interleaved to illustrate the order of interaction between the simulation and the judge. Note that there will be no empty lines in real data and there must not be any empty lines in the simulation output.


---

---
title: "[CERC 2020] Roof Escape"
layout: "post"
diff: 省选/NOI-
pid: P13660
tag: ['计算几何', '2020', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2020] Roof Escape
## 题目描述

Escaping from the police over city roofs is often tricky and the gangsters have to be trained properly. To keep up with current AI trends in criminality, they are developing a general computerized model of escape paths.

In the model, the city area where the escape happens is modeled as a 3D grid made of rectangular cuboids with square bases forming a 2D grid on flat ground. Each cuboid represents a block of houses. Top face of a cuboid is called a roof. In the model, all distances between adjacent blocks are reduced to 0. The path of escaping gangsters is modeled as a polyline – a sequence of straight horizontal and vertical segments where the end point of one segment is the start point of the next segment. The basic path properties are:

- Each point on the path is on the surface of at least one block.
- No part of the path is in the interior of any block.
- The height of any point on the path is bigger than or equal to the lowest height of roofs of all blocks to which surface the point belongs.
- The path starts and ends in the center of a block roof.
- The sum over the lengths of horizontal segments of the path is minimum possible.

It may happen that two consecutive segments on the path share common points. This stems from the fact that the path models a real behavior of a person moving over physical obstacles. Thus an additional path rule also holds:

- Let $P$ be a point on the path. If there is a point $Q$ directly above $P$, and $Q$ belongs to at least two blocks, then the point $Q$ is on the path.

The total length of the escape path should be carefully calculated in the model.

![](https://cdn.luogu.com.cn/upload/image_hosting/4r0xxwq5.png)
## 输入格式

The first line of the input contains six positive integers $W, H, S_x, S_y, E_x, E_y$ ($1 \leq W \cdot H \leq 10^5$, $1 \leq S_x, E_x \leq W$, $1 \leq S_y, E_y \leq H$). $W$ and $H$ are even integers representing the dimensions of the grid base in meters, integers $S_x, S_y$ denote starting coordinates of the escape path and $E_x, E_y$ denote coordinates of the end.

Each of the next $H/2$ lines contains $W/2$ integers, the $i$-th integer on $j$-th line is the height of the corresponding block $T_{i,j}$ in meters ($0 \leq T_{i,j} \leq 10^3$).

Each grid block base is a square with dimensions of $2 \times 2$ meters in the model.
## 输出格式

Print the length of the escape path. The difference between the printed length and the exact length must be less than $10^{-4}$.
## 样例

### 样例输入 #1
```
8 8 1 7 7 1
2 3 2 0
2 1 1 2
1 2 0 0
0 0 0 1
```
### 样例输出 #1
```
14.485281374238
```
## 提示

The sample input with its solution is shown on the picture above.


---

---
title: "[CERC 2020] Screamers"
layout: "post"
diff: 省选/NOI-
pid: P13661
tag: ['2020', '动态树 LCT', 'ICPC', 'CERC']
---
# [CERC 2020] Screamers
## 题目描述

The police is preparing a huge sting in which they hope to jail most of the prominent criminal figures in the city. The flow of information on the side of the police has to be as tight as possible to prevent any leaks. Each detective officer (DO) taking part in the sting is under a strict regulation.

The information shared among DOs is in the form of so-called drops. A drop is always spoken, it must not be recorded on any medium, electronics, paper, etc. Any DO can share a drop only with selected DOs with which he shares a bidirectional connection. Each DO is obliged to pass the drop, as soon as possible and without any change, to all his buddies with which he shares a connection, except for the DO from which he received the drop.

The Chieft Inspector (CI) has to choose which pairs of DOs will share a connection. This final set of connections is called the final group. In this final group (FG) an additional FG-rule holds: A situation when a drop returns to a DO who passed it to his buddies some time ago must not happen. It would mean there are too many unnecessary connections in the FG network.

There is a stack of folders, each folder describing one connection between a particular pair of DOs. The selection of FG is done in two steps. First, CI chooses two integer values $S$ and $T$, which may be sometimes the same, and removes from the stack all folders above the $S$-th folder and all folders below the $T$-th folder.

Next, with the reduced folders, CI repeats the operation. He chooses two integer values $U$ and $V$, which may be sometimes the same, and removes from the reduced stack all folders above the $U$-th folder and all folders below the $V$-th folder.

CI wants to use all the connections in the remaining folders in the FG. However, it is not guaranteed that connections can form FG, due to the additional FG-rule. CI tends to forget this rule quite often.

One cannot change the professional habits of CI. His assistant tries to address the issue diplomatically by employing a programmer who would gradually computerize the process. His first task is to compute the number of different FGs that may be selected by CI after he has chosen the first two values $S$ and $T$. This computation must be efficient for many different values of $S$ and $T$.
## 输入格式

The first input line contains two numbers, $N$ and $M$ ($1 \leq N, M \leq 10^5$), the number of DOs and the number of folders in the CI’s stack respectively. The DOs are identified by integers $1 \ldots N$. Next, there are $M$ lines, each represents one folder and it contains two integers $A$ and $B$ ($1 \leq A < B \leq N$), pair of DOs whose connection is described in the folder. The order of lines corresponds to the order of folders in the stack from top to bottom.

The next line contains one number $Q$ ($1 \leq Q \leq 10^5$), the number of queries. Next, there are $Q$ lines, each represents one query and it contains two positive integers $S$ and $T$ ($1 \leq S \leq T \leq M$), the numbers chosen by CI in the first step of FG selection.

## 输出格式

For each of the $Q$ query input lines print the number of different FGs which can be formed in the second step of the selection process.
## 样例

### 样例输入 #1
```
4 6
1 2
2 3
1 3
1 4
3 4
2 4
4
1 1
1 3
2 4
1 6
```
### 样例输出 #1
```
1
5
6
13
```


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
title: "[GCPC 2023] Japanese Lottery"
layout: "post"
diff: 省选/NOI-
pid: P13675
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Japanese Lottery
## 题目描述

Amida-kuji is a lottery popular in Japan, which can be used to assign $w$ prizes to $w$ people.
The game consists of $w$ vertical lines, called *legs*, and some horizontal bars that connect adjacent legs.
The tops of the legs are the starting positions of the $w$ people, and the prizes are at the bottom of the legs.
To determine the prize of the $i$th person, one has to move down on the $i$th leg, starting at the top, and switch the leg whenever a horizontal bar is encountered.
You can see such a game and how to trace a path in Figure J.1.

![](https://cdn.luogu.com.cn/upload/image_hosting/2xrlg1j9.png)

:::align{center}
Strawberry picking game, photo by [Nanao Wagatsuma](https://commons.wikimedia.org/wiki/File:%E3%82%A4%E3%83%81%E3%82%B4%E3%81%A4%E3%81%BF%E3%82%B2%E3%83%BC%E3%83%A0%E3%81%A8%E3%81%84%E3%81%86%E5%90%8D%E3%81%AE%E3%81%9F%E3%81%A0%E3%81%AE%E3%81%82%E3%81%BF%E3%81%A0%E3%81%8F%E3%81%98.jpg)
:::

You want to manipulate the lottery in such a way that the $i$th person gets the $i$th prize,
for every $i$, by removing some horizontal bars.
Since you do not want to get caught, you want to remove as few bars as possible.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/jce88dsz.png)

Figure J.1: Visualization of an Amida-kuji game. The first person is connected to the third prize. This is also Sample Input 2 after all connections are added and before any connection is removed. To connect the ith person to the ith prize, it suffices to remove both horizontal bars between legs 2 and 3 and the topmost horizontal bar between legs 3 and 4. This is the only minimal solution.
:::

For this problem, the initial game configuration has no horizontal bars.
Then, horizontal bars are added one by one or are removed again.
After each change, you want to know the minimum number of horizontal bars that need to be removed such that the $i$th prize is assigned to the $i$th person for each $i$.
Note that this is always possible by removing all horizontal bars.
## 输入格式

The input consists of:
- One line with three integers $w, h$ and $q$ ($2 \leq w \leq 20$, $1\leq h,q \leq 2\cdot10^5$), the number of legs, the height of the legs, and the number of changes.
- $q$ lines, each containing three integers $y, x_{1}$ and $x_{2}$ ($1\leq y \leq h$, $1\leq x_{1}, x_{2} \leq w$), describing a change where a horizontal bar is added or removed at height $y$ between legs $x_1$ and $x_2$. If there is already a horizontal bar at this position, it will be removed. Otherwise the bar will be added. It is guaranteed that the two legs are adjacent, i.e. $|x_{1}-x_{2}|=1$.

It is guaranteed that all horizontal bars have different heights at every moment.
## 输出格式

After each change, output a single integer, the minimum number of horizontal bars that need to be removed in the game with the currently existing bars such that the $i$th prize is assigned to the $i$th person for each $i$.
## 样例

### 样例输入 #1
```
4 6 7
1 1 2
2 3 4
4 3 4
5 1 2
6 3 4
3 2 3
6 3 4
```
### 样例输出 #1
```
1
2
1
0
1
2
1
```
### 样例输入 #2
```
5 9 12
1 3 4
2 1 2
3 2 3
4 4 5
5 2 1
6 4 3
7 2 3
8 4 3
9 4 5
6 4 3
7 2 3
1 3 4
```
### 样例输出 #2
```
1
2
3
4
3
2
3
4
3
4
3
2
```


---

---
title: "[NWERC 2023] Brickwork"
layout: "post"
diff: 省选/NOI-
pid: P13701
tag: ['2023', 'Special Judge', 'ICPC']
---
# [NWERC 2023] Brickwork
## 题目描述

Bob the Builder is tired of building tiny houses and paving narrow roads, and he strives for something bigger.
The new job given to him by a very eccentric client is exactly what he needs:
He is tasked with building a wall of a certain width that is infinitely high!
His client assured him that he does not need to worry about the building material, and that an infinite supply of various kinds of bricks has already been ordered for him.
Of course, building a stable wall takes very careful planning, especially if it is supposed to be infinitely high. 
In particular, a wall is only stable if no two gaps between bricks in consecutive rows end up directly above each other, as shown in Figure B.1.
Bob knows from his long-time experience that if it is possible to build such a wall, then it can be done by alternating just two row configurations.

|![](https://cdn.luogu.com.cn/upload/image_hosting/o4893qhb.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/o4893qhb.png)|
|:---:|:---:|

:::align{center}
Figure B.1: On the left, we see an unstable wall using the brick types of Sample Input 1. On the right, we see a stable wall using the same brick types. Note that even though only two rows of the wall are shown, it is possible to build an infinitely high wall by repeating these two row configurations.
:::

Bob is terribly excited about the new job and quickly goes to work.
Given the types of bricks available, is it possible to build a stable wall of
width exactly $w$ and infinite height?
If yes, how should Bob build it using only two alternating row configurations?
## 输入格式

The input consists of:
- One line with two integers $n$ and $w$ $(1\leq n,w\leq3\cdot10^5)$, the number of brick types and the width of the wall.
- One line with $n$ integers $b$ ($1\leq b\leq w$), the widths of the brick types.

Note that Bob has an infinite supply of all brick types.
## 输出格式

If it is possible to build a wall, then output "$\texttt{possible}$".
Otherwise, output "$\texttt{impossible}$".

If a wall can be built, provide two row configurations that can be used in an alternating fashion.
For both rows, first output the number of bricks needed for that row, followed by the lengths of the bricks in the order you want to use them.
Your solution is considered valid if alternating the two rows infinitely would result in a stable wall.

If there are multiple valid solutions, you may output any one of them.
## 样例

### 样例输入 #1
```
4 12
3 2 7 2
```
### 样例输出 #1
```
possible
5
2 2 3 2 3
3
3 2 7
```
### 样例输入 #2
```
3 11
6 7 8
```
### 样例输出 #2
```
impossible
```


---

---
title: "[NWERC 2023] Chair Dance"
layout: "post"
diff: 省选/NOI-
pid: P13702
tag: ['2023', 'ICPC']
---
# [NWERC 2023] Chair Dance
## 题目描述

In a deterministic version of *Musical Chairs*$^1$, there are $n$ chairs placed in a circle.
The chairs are numbered from $1$ to $n$ in clockwise order.
Initially, the $i$th player sits on the $i$th chair.
During the game, the game master gives commands to all players at once.

![](https://cdn.luogu.com.cn/upload/image_hosting/wa3c6p9l.png)

:::align{center}
A family playing Musical Chairs. CC BY-SA 3.0 by Artaxerxes on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Musical_chairs_Lawn_Jam_Our_Community_Place_Harrisonburg_VA_June_2008.jpg)
:::


The first type of command tells each player to move $x$ chairs farther in clockwise order,
so they must move from chair $i$ to chair $i+x$.

The second type of command tells each player to move from chair $i$ to chair $i\cdot{}x$.
Both these calculations are done modulo $n$, where a remainder of $0$ corresponds to chair $n$.

If two or more people want to move to the same chair,
then the player needing to travel the least in clockwise direction to reach the chair gets to take the seat,
and the other players trying to reach the same chair are out of the game.
This is illustrated in Figure C.1,
where the larger circles represent the chairs and their numbers are written on their inside.
The smaller circles represent the players.
The next command ($\texttt{* 10}$) tells player $10$ (now on seat $11$) and player $4$ (now on seat $5$) to move to chair $2$.
However, since player $10$ needs to travel less, this player gets to take the seat.
Note that the other $10$ players will also move to some other chairs,
but this is omitted from the figure for the sake of readability.

![](https://cdn.luogu.com.cn/upload/image_hosting/sxh9l4m0.png)

:::align{center}
Figure C.1: Illustration of Sample Input 1 at the fourth command, where players $4$ and $10$ need to move to chair $2$. Because player $10$ needs to travel less in clockwise direction, this player gets to take the seat.
:::

The jury wasted most of their free time designing this game and now need to go back to work.
Fortunately, the game is deterministic, so you can play the game without the help of the jury.

---

$^1$You do not need to know the original game, but you can try to play it after the contest is over.


## 输入格式

The input consists of:
- One line with two integers $n$ and $q$ ($2\leq n,q\leq5\cdot10^5$), the number of chairs and the number of commands.
- $q$ lines, each containing one of three command types:
  - "$\texttt{+ x}$": The player on chair $i$ moves to chair $i+x$.
  - "$\texttt{* x}$": The player on chair $i$ moves to chair $i\cdot{}x$.
  - "$\texttt{? x}$": Tell us the number of the player on chair $x$.

  All of the values $x$ will satisfy $1 \leq x \leq n$.

## 输出格式

For each command of type '$\texttt{?}$', output the number of the player on the requested chair. If the chair is currently empty, output $-1$ instead.
## 样例

### 样例输入 #1
```
12 10
? 12
+ 1
? 12
* 10
? 2
* 5
? 2
* 6
? 1
? 12
```
### 样例输出 #1
```
12
11
10
6
-1
11
```
### 样例输入 #2
```
32 11
* 6
? 8
* 6
+ 31
* 28
? 4
+ 1
* 2
+ 1
* 3
? 1
```
### 样例输出 #2
```
28
32
32
```


---

---
title: "[NWERC 2023] Exponentiation"
layout: "post"
diff: 省选/NOI-
pid: P13704
tag: ['2023', 'ICPC']
---
# [NWERC 2023] Exponentiation
## 题目描述

In her spare time, Zoe develops an online calculator.
Unfortunately, the calculator was targeted by a denial-of-service attack last week.
The attacker created a lot of integer variables, exponentiated them with each other,
and tried to do a bunch of comparisons. The huge integers were too much for the server to handle, so it
crashed. Before Zoe fixes the issue, she decides to actually perform the calculations that the attacker
requested.

![图片太大了传不上洛谷](https://img.freepik.com/free-vector/year-2023-logo-fireworks-with-text-space-vector-illustration-celebrating-new-year_8130-1168.jpg?t=st=1754811651~exp=1754815251~hmac=433ff45e8eeb4dbfe54c3c97b3fac5d2a82fb55b335a23cd097eb5d8395e35ba&w=2000)

:::align{center}
Image by callmetak on [Freepik](https://www.freepik.com/free-vector/year-2023-logo-fireworks-with-text-space-vector-illustration-celebrating-new-year_29660812.htm)
:::

There are $n$ integer variables $x_1, x_2, \dots, x_n$. At the start, each variable is set to $2023$.
You have to perform $m$ instructions of the following two types:
- *Operations*, of the form "$\texttt{! i j}$", where $i \neq j$.
    This means that $x_i$ gets set to $x_i^{x_j}$.
- *Queries*, of the form "$\texttt{? i j}$", where $i \neq j$.
    This means that you should print '$\verb|>|$' if $x_i$ is greater than $x_j$, '$\verb|=|$' if $x_i$ is equal to
    $x_j$, and '$\verb|<|$' if $x_i$ is smaller than $x_j$.


Consider the first sample. After the $5$ operations, the values of the variables are:
$$
\begin{align*}
x_1&=\left({2023}^{2023}\right)^{{2023}^{2023}},&
x_2&=\left({2023}^{{2023}^{2023}}\right)^{2023},&
x_3&={2023},&
x_4&={2023}^{2023}.
\end{align*}
$$
## 输入格式

The input consists of:
- One line with two integers $n$ and $m$ ($2 \leq n \leq 1000$, $1 \leq m \leq 1000$), the number of variables and the number of instructions.
- $m$ lines, each containing a character $c$ (either '$\texttt{!}$' or '$\texttt{?}$') and two integers $i$ and $j$ ($1 \leq i, j \leq n$, $i \neq j$), describing the instructions.
## 输出格式

For every query in the input, output its answer.
## 样例

### 样例输入 #1
```
4 8
! 1 4
! 2 1
! 4 3
! 1 4
! 2 3
? 3 4
? 2 4
? 2 1
```
### 样例输出 #1
```
<
>
=

```
### 样例输入 #2
```
4 9
! 2 4
! 1 2
? 3 1
? 1 2
! 2 3
? 1 2
! 1 3
! 3 2
? 1 3
```
### 样例输出 #2
```
<
>
>
<
```


---

---
title: "[NWERC 2023] Galaxy Quest"
layout: "post"
diff: 省选/NOI-
pid: P13706
tag: ['数学', '2023', 'Special Judge', '最短路', 'ICPC', '拉格朗日乘数法']
---
# [NWERC 2023] Galaxy Quest
## 题目描述

You are travelling through the galaxy in your spaceship.
There are $n$ planets in the galaxy, numbered from $1$ to $n$ and modelled as points in $3$-dimensional space.

You can travel between these planets along $m$ space highways, where each highway connects two planets along the straight line between them.
Your engine can accelerate (or decelerate) at ${1}\,\text{m}/\text{s}^2$, while using fuel at a rate of $1$ litre per second.
There is no limit to how fast you can go, but you must always come to a complete
standstill whenever you arrive at the planet at the end of a highway.

It is possible for a highway to pass through planets other than the ones it connects.
However, as your spaceship is equipped with special hyperspace technology, it simply phases through these obstacles without any need of stopping.
Another consequence of using this technology is that it is impossible to jump from one highway to another midway through: highways must always be travelled in full.

![](https://cdn.luogu.com.cn/upload/image_hosting/qe10l8cm.png)

:::align{center}
Figure G.1: Illustration of Sample Input 1, showing highways in blue, and a route from planet $1$ to planet $3$. The green start of a highway indicates acceleration, and the red end indicates deceleration.
:::

You need to fly several missions, in which you start at your home planet (with number $1$) and need to reach a given target planet within a given time limit.
For each mission, determine whether it can be completed, and if so, find the
least amount of fuel required to do so.
As an example, Figure G.1 shows the optimal route for the second mission of the first sample.
## 输入格式

The input consists of:
- One line with three integers $n$, $m$, and $q$ ($1 \le n,m,q \le 10^5$, $n \ge 2$), where $n$ is the number of planets, $m$ is the number of space highways, and $q$ is the number of missions.
- $n$ lines, each with three integers $x_i$, $y_i$, and $z_i$ ($\left|x_i\right|,\left|y_i\right|,\left|z_i\right| \le 10^3$, $1 \le i \le n$), the coordinates of planet $i$.
- $m$ lines, each with two integers $a$ and $b$ ($1 \le a,b \le n$, $a \neq b$), describing a space highway that connects planets $a$ and $b$. It can be traversed in either direction.
- $q$ lines, each with two integers $c$ and $t$ ($2 \le c \le n$, $1 \le t \le 10^3$), the target planet and time limit for each mission.


The $n$ planets are in distinct locations. Their coordinates are given in metres, and the time limits of the missions are given in seconds. No two highways connect the same pair of planets. For each mission, both the absolute and relative differences between the given time limit and the shortest possible completion time are at least $10^{-6}$.

## 输出格式

For each mission, output the least amount of fuel in litres required to reach the target location within the time limit. If the target location cannot be reached within the time limit, output "$\texttt{impossible}$".

  Your answers should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
4 4 3
-30 0 0
0 0 0
50 0 0
-30 10 0
1 2
2 3
3 4
4 1
2 10
3 25
4 7
```
### 样例输出 #1
```
impossible
19.0538441903
4.0000000000
```
### 样例输入 #2
```
4 2 5
-3 0 2
7 -9 -3
4 4 -6
8 -1 8
1 2
2 3
2 1000
2 100
3 1000
3 100
4 1000
```
### 样例输出 #2
```
0.0287058122
0.2874671888
0.1120998619
1.1272896971
impossible
```


---

---
title: "[NWERC 2023] Isolated Island"
layout: "post"
diff: 省选/NOI-
pid: P13708
tag: ['图论', '计算几何', '2023', '平面图', '二分图', 'ICPC', 'Ad-hoc']
---
# [NWERC 2023] Isolated Island
## 题目描述

On a small island far far away, a handful of old men live isolated from the rest of the world.
The entire island is divided into plots of land by fences, and each old man owns
a single plot of land bounded by fences on all sides. (The region
outside all fences is the ocean.)
Each of the inhabitants needs fish to survive and the only place where they can fish is the ocean surrounding them.
Since not every plot of land is connected to the ocean,
some of the men might need to pass through the land of others before being able to fish.
The men can cross a single fence at a time, but cannot go through fenceposts or
locations where fences intersect.

Unfortunately, the old men are greedy.
They demand one fish each time a person wants to enter their land.
Since they do not want to lose too much fish to the others,
every old man chooses a route that minimizes the number of fish he has to pay to get to the ocean.

Over the years, this has led to rivalry between the old men.
Each man hates all other men who have to pay less than him to reach the ocean.
Two men only *like* each other if they have to pay the same amount of fish to reach the ocean.

|![](https://cdn.luogu.com.cn/upload/image_hosting/e253y5sb.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/8aukzter.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/ea4htdic.png)|
|:---:|:---:|:---:|

:::align{center}
Figure I.1: Illustrations of the first three Sample Inputs. In Sample Input 1, every man has direct access to the ocean, so they all like each other. In Sample Input 2, there does not exist a pair of neighbours who like each other, because the man living in the middle needs to pay one fish, whereas all of his neighbours do not have to pay any fish to reach the ocean. In Sample Input 3, there are six men, some of whom are friendly neighbours.
:::

The natural question which now occurs is:
are there some old men on this island who are neighbours (owning land on
opposite sides of a single fence) and like each other?
See Figure I.1 for two islands with opposite answers to this question.
## 输入格式

The input consists of:
- One line with an integer $n$ ($3 \le n \le 1000$), the number of fences.
- $n$ lines, each with four integers $x_1$, $y_1$, $x_2$, and $y_2$ ($\left|x_1\right|, \left|y_1\right|, \left|x_2\right|, \left|y_2\right|\leq 10^6$, $(x_1,y_1)\neq(x_2,y_2)$), indicating a straight fence between fenceposts at $(x_1,y_1)$ and $(x_2, y_2)$.

Note that fences may intersect internally, and that three or more fences may intersect in the same location.

It is guaranteed that any two fences intersect only in at most one point.
Furthermore, after crossing a single fence, one always ends up in a different region.
All regions together form a single island, where any region can be reached from any other region.

## 输出格式

If there exists a pair of neighbours who like each other, then output "$\texttt{yes}$". Otherwise, output "$\texttt{no}$".
## 样例

### 样例输入 #1
```
6
-3 -3 0 3
-3 -3 0 0
-3 -3 3 -3
0 0 0 3
0 0 3 -3
0 3 3 -3
```
### 样例输出 #1
```
yes
```
### 样例输入 #2
```
 6
-6 -3 0 3
0 3 6 -3
6 -3 -6 -3
-3 0 3 0
3 0 0 -3
0 -3 -3 0
```
### 样例输出 #2
```
no
```
### 样例输入 #3
```
8
0 1 2 1
2 2 0 0
1 2 1 0
1 0 2 1
0 0 2 0
1 2 2 2
0 1 0 0
2 2 2 0
```
### 样例输出 #3
```
yes
```
### 样例输入 #4
```
4
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0
```
### 样例输出 #4
```
no
```


---

---
title: "[GCPC 2024] Headline Heat"
layout: "post"
diff: 省选/NOI-
pid: P13723
tag: ['2024', '哈希 hashing', 'AC 自动机', 'ICPC']
---
# [GCPC 2024] Headline Heat
## 题目描述

The German ICPC scene is widely considered one of the most competitive.
At least, that's what we tell our students.
Countless rivalries form a complex web of envy, despair, glory, and triumph woven around and manifested in the unrelenting echoes of two scoreboards -- Winter Contest and GCPC.
While generations of participants tend to forget the grudges of their predecessors, we coaches, acting as timeless beacons of continuity, preserve these petty conflicts between long forgotten teams.
Striving for perfect balance, we express our dedication to our coaching duties in a furious outcry on social media against every unfair news article.
That is, a coach gets mad if a news article is published that contains a rival university name more often than their own.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/81caxzmt.png)

Top 10 scoreboard of Winter Contest 2024.
:::


To smoothen the waves of conflict in this ocean of rage, a newly appointed authority is tasked with proofreading media coverage of GCPC and Winter Contest to prevent uneven coverage.
## 输入格式

The input consists of:
- One line with the number of universities $n$, rivalries $m$, and articles $k$. \\
    ($1\leq n,m,k\leq 10^5$)
- $n$ lines containing the name of a university $p_i$.
- $m$ lines containing two integers $u,v$, meaning that universities $u$ and $v$ are rivals. \\
    ($1\leq u,v \leq n, u\neq v$)
- $k$ lines containing a news article $t_i$.

If a university $u$ is a rival of university $v$, then $v$ is also a rival of $u$. Moreover, there are no duplicate rivalries.

Names and articles are strings of lowercase Latin letters and spaces.
The first and last character of a name or article are never a space.
Names can overlap and be contained in other names.

The summed length of all names and articles is at most $10^6$, i.e. $\sum_{i=1}^{n} |p_i| + \sum_{i=1}^{k} |t_i| \leq 10^6$.
## 输出格式

For each article, output "$\texttt{no}$" if it will draw the wrath of at least one coach and "$\texttt{yes}$" otherwise.
## 样例

### 样例输入 #1
```
3 1 4
hpi
fau
kit
1 3
kit destroys hpi at wintercontest
gcpc is great
team moshpit from hpi beats kit teams
whats the abbreviation for university of erlangen nuremberg
```
### 样例输出 #1
```
yes
yes
no
yes
```
### 样例输入 #2
```
6 3 5
uds
cu
tum
rwth
uni ulm
uni
4 1
2 5
1 3
last gcpc rwth had a team in top ten two places behind tum
who is team debuilding from constructor university bremen
top ten teams last year are from kit cu uds hpi tum and rwth
uni ulm cu uni ulm
sunday alright lets go
```
### 样例输出 #2
```
no
yes
no
no
yes
```


---

---
title: "[GCPC 2024] Jigsaw Present"
layout: "post"
diff: 省选/NOI-
pid: P13725
tag: ['2024', 'Special Judge', 'ICPC', '折半搜索 meet in the middle']
---
# [GCPC 2024] Jigsaw Present
## 题目描述

Julia is preparing a present for James. She will give him some of her $n$ jigsaw puzzles, where puzzle $i$ ($1 \leq i \leq n$) consists of $x_i$ pieces and has a difficulty $y_i$ (can be negative if the puzzle is very easy).

![](https://cdn.luogu.com.cn/upload/image_hosting/okr7isdn.png)

James is already very excited and would like to know in advance what he will get. Therefore, he used some of his criminal energy to gather information about the gift. In particular, he has managed to obtain an encrypted message containing the total difficulty and total number of pieces of all the puzzles that he will receive. 

Now he wonders whether it is worth spending some more time to decrypt the message. After all, it might be that this information is not enough to uniquely determine his gift. Since he was never good at these computer thingies, James asked for your assistance. Help him find out whether it is worth decrypting the message or not. If the answer is negative, you have to find two distinct gifts that result in the same encrypted message.

## 输入格式

The input consists of
- One line with an integer $n$ ($2 \leq n \leq 4\,096$), the number of puzzles that Julia owns.
- $n$ lines, the $i$th of which contains two integers $x_i$ and $y_i$ ($1 \leq x_i \leq 4\,096$, $\left|y_i\right| \leq 4\,096$), the number of pieces of puzzle $i$ and the difficulty of puzzle $i$.
## 输出格式

If James can uniquely determine his gift, then print "$\texttt{yes}$". Otherwise, you should print "$\texttt{no}$" followed by two lines,
  where each line contains the description of a present. The description of a present should start with an
  integer $k$, the number of puzzles, followed by $k$ distinct integers, the indices of the puzzles. 

  Note that the two presents have to be distinct, meaning that there should be at least one puzzle that is contained 
  in one present but not the other.

  If there are multiple presents that result in the same encrypted message, you can print any of them.
## 样例

### 样例输入 #1
```
5
2 -1
3 2
3 1
1 -3
1 1
```
### 样例输出 #1
```
no
3 2 4 5
2 1 3
```
### 样例输入 #2
```
4
2 -1
3 2
3 1
1 -3
```
### 样例输出 #2
```
yes
```
## 提示

In the first sample case, the first present consists of puzzles $2$, $4$, and $5$. The total number of pieces is $3 + 1 + 1 = 5$ and the total difficulty is $2 + (-3) + 1 = 0$. 
The second present consists of puzzles $1$ and $3$. The total number of pieces is $2 + 3 = 5$ and the total difficulty is $(-1) + 1 = 0$.
Thus, if James only knows the total number of pieces and the total difficulty, he cannot recover his present. So it is not worth to decode the message.

In the second sample case, no matter what gift Julia prepares, if James knows the total number of pieces and the total difficulty, he can recover his present. So he should decode the message.


---

---
title: "[CERC 2021] DJ Darko"
layout: "post"
diff: 省选/NOI-
pid: P13766
tag: ['2021', '颜色段均摊（珂朵莉树 ODT）', 'ICPC', '均摊分析', 'CERC']
---
# [CERC 2021] DJ Darko
## 题目描述

A new DJ is in town. DJ Darko needs to set up his speakers. He has $N$ speakers in a row with the $i$-th speaker volume set to $A_i$. Changing the volume is rather difficult so the $i$-th speaker requires $B_i$ units of energy to increase or decrease the volume by the value of 1.

Unfortunately, Darko's evil twin brother Karko likes to mess with him. There are $Q$ events that will be happening.

`1 l r x`

`2 l r`

In an event of type 1, Karko changes the volume of all speakers from the $l$-th to the $r$-th by $x$. In an event of type 2, Darko sets all the speakers from the $l$-th to the $r$-th to the same volume in a way that uses up the minimal amount of energy. If there are multiple ways of doing that, he chooses the one which minimizes the final volume.

As a bystander, you would like to know the volume that Darko set for each event of type 2.

## 输入格式

The first line contains the number of speakers $N$ and the number of events $Q$. In the second line, there are $N$ numbers $A_i$ indicating the current volume of the speakers. In the third line, there are $N$ numbers $B_i$, indicating the energy needed to change the volume of the $i$-th speaker by one. In the next $Q$ lines there are $Q$ events, formatted in the way described above. All numbers in the input are integers.

## 输出格式

For each event of type 2, output the volume to which Darko set the speakers.
## 样例

### 样例输入 #1
```
5 5
8 1 6 4 9
3 6 4 1 7
2 2 4
1 1 4 -8
2 1 1
2 1 3
2 4 5
```
### 样例输出 #1
```
1
0
-7
9
```
### 样例输入 #2
```
8 3
4 3 9 3 7 6 4 8
9 5 8 5 2 2 1 8
1 1 7 -10
2 5 5
2 4 7
```
### 样例输出 #2
```
-3
-7
```
## 提示

### Input limits

* $1 \leq N, Q \leq 200\,000$
* $0 \leq A_i, B_i \leq 10^9$
* $1 \leq l \leq r \leq N$
* $-10^9 \leq x \leq 10^9$


---

---
title: "[CERC 2021] Lines in a grid"
layout: "post"
diff: 省选/NOI-
pid: P13769
tag: ['数学', '2021', 'ICPC', 'CERC']
---
# [CERC 2021] Lines in a grid
## 题目描述

Suppose that we are given a $n \times n$ integer grid, e.g. $\{(i, j)\}_{i=0, j=0}^{n-1, n-1}$. Let $l_n$ be the number of different lines that intersect with at least two points on the grid.

For $n = 3$, there are exactly 20 such lines, as drawn on the image below.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/hs3oswsp.png)
:::

Compute $l_n$ for all given $n$.
## 输入格式

First line contains an integer $Q$ – the number of queries. The second line contains $Q$ space-separated integers $n_1, \ldots, n_Q$.

## 输出格式

Print $Q$ numbers $l_{n_1}, \ldots, l_{n_Q}$, each in its own line. Since $l_k$ can be large, print them modulo $10^6 + 3$.
## 样例

### 样例输入 #1
```
3
1 3 2
```
### 样例输出 #1
```
0
20
6
```
## 提示

### Input limits

* $1 \leq Q \leq 1000$
* $1 \leq n_i \leq 10^7$


---

---
title: "[CERC 2021] Repetitions"
layout: "post"
diff: 省选/NOI-
pid: P13772
tag: ['2021', '后缀数组 SA', 'ICPC', 'Z 函数', 'CERC']
---
# [CERC 2021] Repetitions
## 题目描述

Bob is an aspiring avant-garde writer. He disdains the use of spaces, punctuation, capital letters and the like; hence, his stories are nothing but long strings of lowercase letters of the English alphabet. Critics have also noted that his style is marked by a certain fondness for repetitions, in the sense that it sometimes happens that two instances of the same substring appear in his story twice in a row, without any other intervening characters.

Bob has submitted his latest masterpiece, a string which happens to be $n$ characters long, to $q$ different literary magazines in the hopes that at least one of them might be willing to publish it. The response was more favourable than he had dared to hope. The editors of all $q$ magazines have expressed willingness to publish some part (i.e. a substring) of his story, but on the condition that he identify the longest repetition (i.e. a shorter substring appearing twice in a row) within that part of the story. The editors intend to remove that part to prevent the story from being too boring. Now Bob needs your help to answer these queries from the editors.

Write a program that, given a string of $n$ letters, $s[1]s[2] \ldots s[n]$, answers $q$ queries of the form "given $a_i$ and $b_i$, how long is the longest string $t$ for which $tt$ appears as a substring of $s[a_i]s[a_i + 1] \ldots s[b_i - 1]s[b_i]$, and where does the leftmost such occurrence begin?"

## 输入格式

The first line contains two integers, $n$ and $q$. The second line contains the string $s$, which is $n$ characters long; all these characters are lowercase letters of the English alphabet. The remaining $q$ lines describe the queries; the $i$-th of these lines contains the integers $a_i$ and $b_i$, separated by a space.

## 输出格式

Output $q$ lines; the $i$-th of these lines must contain two space-separated integers $\ell_i$ and $c_i$. $\ell_i$ should be the length of the longest string $t$ for which $tt$ appears as a substring in $s[a_i]s[a_i + 1] \ldots s[b_i - 1]s[b_i]$, and $c_i$ should be the index at which the leftmost repetition of this length begins, i.e. the smallest integer such that $a_i \leq c_i$, $c_i + 2\ell_i - 1 \leq b_i$ and $s[c_i] \ldots s[c_i + \ell_i - 1] = s[c_i + \ell_i] \ldots s[c_i + 2\ell_i - 1]$. (If $\ell_i = 0$, then $c_i = a_i$ by definition.)
## 样例

### 样例输入 #1
```
10 4
cabaabaaca
4 8
1 9
5 9
8 10
```
### 样例输出 #1
```
1 4
3 2
1 7
0 8

```
## 提示

### Comment

The four queries in the above example refer to the substrings $\textbf{\underline{a}abaa}$, $\textbf{c\underline{aba}abaac}$, $\textbf{ab\underline{a}ac}$, and $\textbf{aca}$; the part shown in bold is the substring referred to by the result of that query (a substring of length $\ell_i$, beginning at index $c_i$). In the last query there is no repetition, so $\ell_4 = 0$.

### Input limits

* $1 \leq n \leq 10^6$
* $1 \leq q \leq 100$
* $1 \leq a_i \leq b_i \leq n$ for each $i = 1, 2, \ldots, q$


---

---
title: "[CERC 2021] Systematic salesman"
layout: "post"
diff: 省选/NOI-
pid: P13774
tag: ['2021', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2021] Systematic salesman
## 题目描述

A travelling salesman has received a list of cities that he must visit in a single journey. He may start and end his tour in any city as long as he visits each city at least once. He doesn't have to start and finish in the same city. The travelling salesman noticed that his fellow travelling salesmen are spending way too much time planning and finding an optimal route. Therefore, he has decided to take a different, more systematic approach to planning his route.

He will first split all the cities into the left half and the right half. If the number of cities is odd, the right half will contain one city more than the left. He will then pick one of the halves and visit all the cities in that half before visiting any of the cities in the other half.

To visit the cities in the selected left/right half, he will split this set of cities into the lower and upper half. In case of an odd number of cities in this set, the upper half will contain an extra city. Again, he will first visit all cities in one of these halves before visiting any of the cities in the other half.

He will continue applying the same logic of alternately splitting the cities in half horizontally and vertically until he obtains the complete path of the journey. Compute the shortest path that visits all cities that the salesman can obtain in this way.

## 输入格式

The first line contains the number of cities $N$ that the salesman wants to visit. Locations of these cities are given in the $N$ lines that follow. The location of each city is defined by a space-separated pair of integer coordinates $X_i$ and $Y_i$, which describe its location on a plane. It is guaranteed that $X_i$ coordinates of all cities are distinct. The same holds for all $Y_i$ coordinates.
## 输出格式

In the first line, print the minimum length of the salesman's path. The length will be considered correct if it differs from the official solution by at most $10^{-4}$. In the second line output a space-separated list of cities as visited by the salesman. The cities are numbered from 1 to $N$ in order as given in the input. If there are several solutions, you can output any of them.
## 样例

### 样例输入 #1
```
6
5 1
9 6
2 5
3 3
10 4
7 2
```
### 样例输出 #1
```
13.142182
3 4 1 6 5 2
```
## 提示

### Comment

The salesman first visits the left half (cities 1, 3 and 4) and then the right half (cities 2, 5 and 6).

To visit cities 1, 3 and 4, he first visits the upper half (cities 3 and 4) before the lower half (city 1). The cities in the upper half are split into the left half (city 3), visited first, and the right half (city 4), visited afterwards.

Cities 2, 5 and 6 are split into the lower half (city 6) and the upper half (cities 2 and 5). Here, the salesman first visits the lower half. He continues his route with the upper half, where he first visits the right half (city 5) and concludes with the left half (city 2).


### Input limits

* $1 \leq N \leq 1000$
* $0 \leq X_i, Y_i \leq 10^6$


---

---
title: "[SWERC 2023] Metro quiz"
layout: "post"
diff: 省选/NOI-
pid: P13794
tag: ['2023', 'Special Judge', 'ICPC', '状压 DP']
---
# [SWERC 2023] Metro quiz
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/e0ebc847de3240cb0f9ab37c5b03c9a185630d06.png)

:::


Two Olympics spectators are waiting in a queue. They each hold a copy of the metro map of Paris, and they devised a little game to kill time. First, player A thinks of a metro line (chosen uniformly at random among all metro lines) that player B will need to guess. In order to guess, player B repeatedly asks whether the line stops at a metro station of her choice, and player A answers truthfully. After enough questions, player B will typically know with certainty which metro line player A had in mind. Of course, player B wants to minimise the number of questions she needs to ask.


You are given the map of the $M$ metro lines (numbered from 1 to $M$), featuring a total of $N$ metro stations (numbered from 0 to $N-1$) and indicating, for each line, those stations at which the line stops. Please compute the expected number of questions that player B needs to ask to find the answer, in the optimal strategy.


In other words, given a strategy $S$, note $Q_{S,j}$ the number of questions asked by the strategy if the metro line in the solution is line $j$. Then, note
$$ E_S = \mathbb{E} \left[ Q_S \right] = \frac{1}{M} \sum_{j = 1}^M Q_{S, j} $$
the expected value of $Q_{S,j}$ assuming that $j$ is uniformly chosen from the set of all metro lines. Your task is to compute $\min_S E_S$.


If it is not always possible for player B to know which line player A had in mind with certainty, output $\texttt{not possible}$.
## 输入格式

The first line contains the number $N$. The second line contains the number $M$. Then follow $M$ lines: the $k^\text{th}$ such line contains first a positive integer $n \leq N$, then a space, and then $n$ space-separated integers $s_1 , s_2 , \dots, s_n$ ; these are the metro stations at which line $k$ stops. A line stops at a given station at most once.


**Limits**
	
- $1 \leq N \leq 18$;
- $1 \leq M \leq 50$.
## 输出格式

The output should contain a single line, consisting of a single number: the minimum expected number of questions that player B must ask in order to find the correct metro line, or \texttt{not possible} (in lowercase characters). Answers within $10^{-4}$ of the correct answer will be accepted.
## 样例

### 样例输入 #1
```
5
4
3 0 3 4
3 0 2 3
3 2 3 4
2 1 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
3
1 0
1 1
1 2
```
### 样例输出 #2
```
1.66666666666667
```
## 提示

**Sample Explanation 2**

Ask the first question about station 0: this is optimal by symmetry of the problem. This lets us distinguish between line 1, which stops at station 0, and lines 2 and 3, which do not. If needed, ask a second question to distinguish between lines 2 and 3. Player B asks one question if the answer is line 1, and two questions otherwise. Thus, the expected number of questions she will ask is $(1 + 2 \times 2)/3$.


---

---
title: "[SWERC 2023] Favourite dish"
layout: "post"
diff: 省选/NOI-
pid: P13798
tag: ['计算几何', '2023', '凸包', 'ICPC', '李超线段树']
---
# [SWERC 2023] Favourite dish
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/f4e13fe8cb3692d86fceaeba9e38456b9c240bed.png)

:::

France is a country of gastronomy. For a dish, both the taste and plating are important. Nevertheless, when different people evaluate a dish, some focus more on taste and some focus more on plating. At the Olympic Village dining hall, there are $N$ dishes, numbered from 1 to $N$; each dish has a score on its taste and a score on its plating. There are also $M$ persons, numbered from 1 to $M$; each person has a weight on taste and a weight on plating. One person's final score of a dish is the weighted average of the dish's scores on taste and plating.


The chefs at the Olympics want to provide everyone with their favourite dish on the evening of the closing ceremony. Your task is to calculate everyone's favourite dish. If multiple dishes tie for the highest score as a person's favourite, choose the one with the smallest number.


## 输入格式

Each line contains two space-separated integers. The first line contains the numbers $N$ and $M$. Then follow $N$ lines; the $k^\text{th}$ such line contains two integers $t_k$ and $p_k$, which are the scores of the dish $k$ on taste and on plating. Then come $M$ more lines; the $l^\text{th}$ such line contains two integers $T_l$ and $P_l$, which are the weights of person $l$ on taste and on plating.

**Limits**

- $1 \leq N \leq 500~000$;
- $1 \leq M \leq 500~000$;
- $0 \leq t_k \leq 1~000~000, 0 \leq p_k \leq 1~000~000$, and $(t_k, p_k) \neq (0, 0)$ for all $k \leq N$;
- $0 \leq T_l \leq 1~000~000, 0 \leq P_l \leq 1~000~000$, and $(T_l, P_l) \neq (0, 0)$ for all $l \leq M$;
- the $N$ pairs $(t_k, p_k)$ are pairwise distinct;
- the $M$ pairs $(T_l, T_l)$ are pairwise distinct.
## 输出格式

The output should contain $M$ lines. The $l^\text{th}$ such line should contain one number: the number of the favourite dish of person $l$.
## 样例

### 样例输入 #1
```
4 3
2 5
3 4
4 2
1 6
6 4
2 8
5 5
```
### 样例输出 #1
```
2
4
1
```
### 样例输入 #2
```
3 4
1 0
0 2
0 1
1 1
2 2
2 1
1 0
```
### 样例输出 #2
```
2
2
1
1
```
## 提示

**Sample Explanation 1**

Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$; person 3 has three tied favourite dishes, so we chose the first one.

|   | Dish | < | < | < |
|:-:|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 | 4 |
| 1 | $3.2$ | $3.4^\ast$ | $3.2$ | $3$ |
| 2 | $4.4$ | $3.8$ | $2.4$ | $5^\ast$ |
| 3 | $3.5^\ast$ | $3.5$ | $3$ | $3.5$ |

**Sample Explanation 2**


Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$.

|   | Dish | < | < |
|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 |
| 1 | $0.5$ | $1^\ast$ | $0.5$ |
| 2 | $0.5$ | $1^\ast$ | $0.5$ |
| 3 | $2/3^\ast$ | $2/3$ | $1/3$ |
| 4 | $1^\ast$ | $0$ | $0$ |



---

---
title: "[CERC 2022] Bandits"
layout: "post"
diff: 省选/NOI-
pid: P13805
tag: ['点分治', '2022', 'ICPC', 'CERC']
---
# [CERC 2022] Bandits
## 题目描述

There is a kingdom with $N$ villages and $N - 1$ bidirectional roads that allow the citizens to travel between any pair of villages following a path consisting of one or more roads. The $i$-th road connects villages $A_i$ and $B_i$ and has length $C_i$.

The king has noticed an increasing number of complaints about bandits attacking the merchants travelling along the roads in the kingdom. He has tasked his advisor with solving this problem by hiring loyal groups of thugs that will act as security agencies. Each such security contract guarantees security of all roads in a radius of $R_j$ from the village $X_j$ with the group’s headquarters. A road is protected by the contract if it is part of a path of length at most $R_j$ from $X_j$ to some other village. Some roads may be protected by several contracts and are therefore more secure.

Write a program that will process queries about new contracts and answer queries about the security of individual roads, that is the number of contracts currently securing that road.
## 输入格式

The first line contains the number of villages $N$. The roads connecting these villages are described in the following $N - 1$ lines. The description of each road consists of space-separated integers $A_i$, $B_i$ and $C_i$, which represent a road of length $C_i$ between villages $A_i$ and $B_i$. The villages are numbered from 1 to $N$.

Next line contains the number of queries $Q$. The following $Q$ lines describe the queries. The query that represents a new security contract starts with character '+' and is followed by the headquarters village $X_j$ and security radius $R_j$. The query about the security of some road starts with character '?' and is followed by the number $Y_j$ of that road. The roads are numbered from 1 to $N - 1$ in order in which they are given in the input.
## 输出格式

Process the queries in the given order and for every query of type '?' output one line with the current number of contracts securing the road $Y_j$.
## 样例

### 样例输入 #1
```
7
1 2 4
4 2 7
5 1 3
3 6 4
1 6 9
2 7 1
7
+ 2 6
? 3
? 1
+ 6 14
? 1
? 2
? 3
```
### 样例输出 #1
```
0
1
2
0
1
```
## 提示

### Input limits

* $1 \leq N, Q \leq 10^5$
* $0 \leq C_i, R_j \leq 10^9$


---

---
title: "[CERC 2022] Insertions"
layout: "post"
diff: 省选/NOI-
pid: P13812
tag: ['树状数组', '2022', 'KMP 算法', 'ICPC', 'CERC']
---
# [CERC 2022] Insertions
## 题目描述

We are given three strings, $s$, $t$ and $p$. We will denote the length of a string by vertical bars, thus $|s|$ is the length of $s$ and so on. If we insert $t$ into $s$ at position $k$, where $0 \leq k \leq |s|$, the result is a new string consisting of the first $k$ characters of $s$, followed by the entirety of $t$, and finally followed by the remaining $|s| - k$ characters of $s$. We would like to select $k$ so that the resulting new string will contain the largest possible number of occurrences of $p$ as a substring.

Thus, for example, inserting $t = \text{aba}$ into $s = \text{ab}$ at position $k = 0$ results in the string $\text{abaab}$; at $k = 1$, in the string $\text{aabab}$; and at $k = 2$, in the string $\text{ababa}$. If we are interested in occurrences of $p = \text{aba}$, then the best position to insert $t$ into $s$ is $k = 2$, where we get two occurrences: $\text{ababa}$ and $\text{ababa}$ (as this example shows, occurrences of $p$ are allowed to overlap). If, on the other hand, we were interested in occurrences of $p = \text{aa}$, then the best choices of $k$ would be $k = 0$ and $k = 1$, which result in one occurrence of $p$, whereas $k = 2$ results in 0 occurrences of $p$.

## 输入格式

The first line contains the string $s$, the second line the string $t$, and the third line the string $p$.
## 输出格式

Output one line containing the following four integers, separated by spaces:

1. The maximum number of occurrences of $p$ we can get after inserting $t$ into $s$ at position $k$, if we choose the position $k$ wisely.
2. The number of different $k$'s (from the range $0, 1, \ldots, |s|$) where this maximum number of occurrences of $p$ is attained.
3. The minimum value of $k$ where the maximum number of occurrences of $p$ is attained.
4. The maximum value of $k$ where the maximum number of occurrences of $p$ is attained.
## 样例

### 样例输入 #1
```
ab
aba
aba
```
### 样例输出 #1
```
2 1 2 2
```
### 样例输入 #2
```
abaab
aba
ababa
```
### 样例输出 #2
```
1 3 1 5
```
### 样例输入 #3
```
eeoeo
eoe
eeo
```
### 样例输出 #3
```
2 3 1 4
```
## 提示

### Comment

The first of these three examples is the one discussed earlier in the problem statement

### Input limits

- $1 \leq |s| \leq 10^5$
- $1 \leq |t| \leq 10^5$
- $1 \leq |p| \leq 10^5$
- All the strings consist only of lowercase letters of the English alphabet.


---

---
title: "[CERC 2022] Money Laundering"
layout: "post"
diff: 省选/NOI-
pid: P13813
tag: ['2022', 'Special Judge', 'Tarjan', '高斯消元', 'ICPC', 'CERC']
---
# [CERC 2022] Money Laundering
## 题目描述

Consider a company $A$ that made a $100 \, \text{€}$ of profit this year. The company's owners are Ivan with $52.8\%$ ownership share and Robi with a $47.2\%$ ownership share. Naturally, the profits are shared proportionally to the shares with Ivan receiving $52.8 \, \text{€}$ and Robi $47.2 \, \text{€}$.

They will have to pay tax on the received profits, but would like to avoid doing so, if at all possible. Sadly, the ownership structure of their company is too simple and it's easily discoverable how much profits each of them received.

For the next year, they prepare a plan. They make a shell company $B$ and change the ownership shares. Ivan now only owns $1\%$ of company $A$, Robi only $2\%$, the company $B$ owns a $49\%$ share of $A$ and $A$ owns $48\%$ of itself. Company $B$ has a similar ownership structure: $70\%$ ownership share belongs to $B$ itself, $25\%$ to $A$, $3\%$ to Ivan and $2\%$ to Robi.

Looking naively, Ivan and Robi have very small ownership shares. However, we are interested in the ownership shares of ultimate beneficial owners, the persons who will ultimately profit, which are Ivan and Robi in our case. We wish to determine their ultimate ownership shares, which turn out to be approximately equal to what they were before the introduction of $B$.

Ultimate ownership shares can be determined as follows: let the company $A$ have $100 \, \text{€}$ of profit and $B$ have $0 \, \text{€}$. The profits are paid out to all direct owners in proportion to their ownership share. However, since $A$ and $B$ are partial owners of themselves, they receive a part of the profit. To determine the ultimate share of the ultimate beneficial owners, we repeat the procedure – any profits that $A$ and $B$ receive are paid out again, with Ivan and Robi getting a share, as well as $A$ and $B$. This is repeated ad infinitum until (theoretically, after an infinite number of steps) all money is paid out to the ultimate beneficial owners, and the ratio of the final sums received by Ivan and Robi is by definition equal to their ultimate share of $A$.

For a given structure of companies, determine the shares of the ultimate beneficial owners. However, the companies do not form a random network of ownership, but are structured in industrial sectors. Companies within sectors may form arbitrary ownership structures, but this is not true for companies in different sectors. If companies $P$ and $Q$ belong to different sectors, it cannot happen that

- $P$ would own a (potentially indirect) share of $Q$ and
- $Q$ would own a (potentially indirect) share of $P$.

One or none of these statements could be true, but not both.
## 输入格式

The first line contains two space-separated integers $c$ and $p$, representing the number of companies and number of persons, respectively. Then $c$ lines follow, and $i$-th of them contains the description of $i$-th company. The line contains an integer $k_i$, the number of owners, and then $k_i$ entries of the form $o_{i,j} : p_{i,j}$, where $o_{i,j}$ is the designation of the $j$-th owner (person or company) and $p_{i,j}$ is their share in percentages. The share will have exactly one decimal place.
## 输出格式

Output the ultimate ownership shares of all persons in all companies. The $i$-th line should include shares of all persons in the $i$-th company, including persons with no share. The share is between 0 and 1. Shares in a line should be separated by a space. The answer will be considered correct if its absolute or relative error is less than $10^{-4}$.
## 样例

### 样例输入 #1
```
2 2
2 P1:50.1 P2:49.9
2 P1:23.4 P2:76.6
```
### 样例输出 #1
```
0.501000 0.499000
0.234000 0.766000
```
### 样例输入 #2
```
2 2
2 P1:50.0 P2:50.0
3 P1:20.0 P2:30.0 C1:50.0
```
### 样例输出 #2
```
0.500000 0.500000
0.450000 0.550000
```
### 样例输入 #3
```
2 2
4 P1:1.0 P2:2.0 C2:49.0 C1:48.0
4 C2:70.0 C1:25.0 P1:3.0 P2:2.0
```
### 样例输出 #3
```
0.528358 0.471642
0.540299 0.459701
```
### 样例输入 #4
```
3 2
5 P1:1.0 P2:2.0 C2:49.0 C1:38.0 C3:10.0
4 C2:70.0 C1:25.0 P1:3.0 P2:2.0
2 P1:20.0 P2:80.0
```
### 样例输出 #4
```
0.373228 0.626772
0.411024 0.588976
0.2 0.8
```
## 提示

### Input limits

- $1 \leq c, p \leq 10^3$
- $1 \leq \sum_{i=1}^{n} k_i \leq 10^4$
- $o_{i,j}$ can have two forms: $\text{Px}$ or $\text{Cy}$, indicating that the owner is the $x$-th person or $y$-th company, respectively. It is guaranteed that $1 \leq x \leq p$, and $1 \leq y \leq c$ holds.
- $k_i \geq 1$
- $0 < p_{i,j} \leq 100$
- $\sum_{j=1}^{k_i} p_{i,j} = 100$
- The identifiers $\{o_{i,j}\}_{j=1}^{k_i}$ are unique, i.e. each owner is listed at most once.
- The number of companies belonging to each sector is less than 10.
- Each company has at least one ultimate beneficial owner. For example, a scheme where $A$ would own a $100\%$ of $B$ and $B$ a $100\%$ of $A$ is forbidden.



---

---
title: "[CERC 2022] Mortgage"
layout: "post"
diff: 省选/NOI-
pid: P13814
tag: ['线段树', '2022', '凸包', 'ICPC', 'CERC']
---
# [CERC 2022] Mortgage
## 题目描述

Andrej is a typical modern student, dreaming to buy a house one day. Since buying real property is no piece of cake, he is planning out his life and trying to figure out exactly how and when he will be able to afford one. To buy a house, he aims to take a mortgage loan that will then need to be paid back in multiple payments over the course of several months. For each of the next $n$ months of his life, he will earn the income $a_i$ that can be spent on the mortgage (other costs have already been accounted for, hence $a_i$ can be negative). He is now looking at a list of various properties and mortgage loans and is trying to figure out which of them he can afford.

Suppose that he takes a mortgage that involves paying $x$ units of money over the course of $k$ months, starting in month $i$, and ending in month $i + k - 1$. Each of these months, he needs to be able to pay $x$ units of money. If he has any leftover income in month $i$, i.e. $a_i > x$, he can save the rest and use it towards some of the future payments (same for any leftover money in months $i + 1$ to $i + k - 1$). However, he cannot count on saving any money prior to month $i$, regardless of the income in those months. He will spend it all on his current rent and avocado toast.

You are given the list of Andrej's income for the next $n$ months and a list of $m$ different time intervals. The $i$-th time interval is defined by two numbers, $s_i$, and $k_i$. The mortgage loan starts on the month $s_i$ and lasts for $k_i$ months, i.e. the last payment is done on the month $s_i + k_i - 1$. For each of the time intervals, determine what the largest monthly payment that Andrej can afford is.
## 输入格式

The first line contains two integers, $n$ and $m$, the number of months, and the number of different time intervals, respectively. The second line contains $n$ space-separated integers, $a_1, \ldots, a_n$, Andrej's income over the next $n$ months. This is followed by $m$ lines describing different time intervals, each line containing two space-separated integers $s_i$ and $k_i$.
## 输出格式

Print out $m$ lines, one for each time interval. Print out the largest integer amount of monthly payment that Andrej can afford to pay for the $i$-th mortgage. If the number is strictly smaller than 0, print "stay with parents" (without quotation marks).
## 样例

### 样例输入 #1
```
9 5
6 1 10 9 5 -2 3 1 -1
3 6
1 4
3 3
6 1
8 2
```
### 样例输出 #1
```
4
3
8
stay with parents
0
```
## 提示

### Comment

For the first interval, a monthly payment of $4$ units is the largest Andrej can afford. For a monthly payment of $5$, he would run out of money for his final payment. Negative income on month $6$ means that Andrej cannot afford any mortgage for interval $4$, regardless of its size.

### Input limits

- $1 \leq n, m \leq 2 \cdot 10^5$
- $-10^9 \leq a_i \leq 10^9$
- $1 \leq s_i \leq n; \forall i$
- $1 \leq k_i$ and $s_i + k_i - 1 \leq n; \forall i$


---

---
title: "[CERC 2023] Labelled Paths"
layout: "post"
diff: 省选/NOI-
pid: P13856
tag: ['2023', 'Special Judge', '后缀数组 SA', 'ICPC', 'CERC']
---
# [CERC 2023] Labelled Paths
## 题目描述

We are given a directed acyclic graph with $n$ vertices and $m$ edges. Each edge has a label (a string of lowercase letters; possibly even an empty string). We can now extend the concept of labels from edges to paths by defining the label of a path as the concatenation of the labels of the edges that constitute this path (in the same order in which they appear in the path). The smallest path from a start vertex $s$ to a destination vertex $t$ is the path (from $s$ to $t$) whose label is lexicographically smallest (i.e. the earliest in lexicographical order) amongst all the paths from $s$ to $t$. Write a program that, for a given $s$, outputs the smallest paths from $s$ to $t$ for all vertices $t$ of the graph.

## 输入格式

The first line contains four space-separated integers: $n$ (the number of vertices), $m$ (the number of edges), $d$ (the length of the string $A$, on which see below) and $s$ (the number of the start vertex). The vertices are numbered by integers from $1$ to $n$.

The second line contains a string $A$, which is exactly $d$ characters long; all these characters are lowercase letters of the English alphabet. All the edge labels in our graph are substrings of the string $A$.

The remaining $m$ lines describe the edges of the graph. The $i$-th of these lines describes the $i$-th edge and contains four space-separated integers: $u_i$ (the start vertex of this edge), $v_i$ (the end vertex of this edge), $p_i$ and $\ell_i$. The last two of these integers indicate that the label of this edge is the substring of $A$ that begins with the $p_i$-th character of $A$ and is $\ell_i$ characters long. For this purpose we consider the characters of $A$ to be indexed by integers from $1$ to $d$.
## 输出格式

Output $n$ lines, where the $t$-th line (for $t = 1, \dots, n$) describes the smallest path from $s$ to $t$. If there is no path from $s$ to $t$, the line should contain only the integer $0$ and nothing else. Otherwise the line should start with the number of vertices on the path (including vertices $s$ and $t$), followed by the list of those vertices, separated by spaces. If there are several possible solutions, you may output any of them.
## 样例

### 样例输入 #1
```
5 7 6 3
abcbca
3 2 1 1
2 1 5 1
2 5 4 2
3 1 1 2
3 4 3 2
1 4 6 1
5 4 5 2
```
### 样例输出 #1
```
2 3 1
2 3 2
1 3
3 3 1 4
3 3 2 5
```
## 提示

### Comment

In this example, the edge $3 \rightarrow 1$ has the label ab; the edge $1 \rightarrow 4$ has the label a; the smallest path from $3$ to $4$ is $3 \rightarrow 1 \rightarrow 4$, whose label is aba.

### Input limits

- $1 \leq s \leq n \leq 600$
- $1 \leq m \leq 2000$
- $1 \leq d \leq 10^6$
- $1 \leq u_i \leq n$, $1 \leq v_i \leq n$, $u_i \neq v_i$ (for all $i = 1, \dots, m$)
- $1 \leq p_i$, $0 \leq \ell_i$, $p_i + \ell_i - 1 \leq d$ (for all $i = 1, \dots, m$)
- The graph is acyclic and has no parallel edges (i.e. from $i \neq j$ it follows that $u_i \neq u_j$ and/or $v_i \neq v_j$).



---

---
title: "[CERC2016] Easy Equation"
layout: "post"
diff: 省选/NOI-
pid: P1400
tag: ['2016', 'Special Judge', 'ICPC']
---
# [CERC2016] Easy Equation
## 题目描述

Given an integer $k$ greater than $1$, it is possible to prove that there are infinitely many triples of positive integers $(a, b, c)$ that satisfy the following equation:

$$a^2+b^2+c^2=k(ab+bc+ca)+1$$

Given positive integers $n$ and $k$, find $n$ arbitrary triples $(a_1, b_1, c_1), (a_2, b_2, c_2), \cdots , (a_n, b_n, c_n)$ that all
satisfy the equation. Furthermore, all $3n$ integers $(a_1, b_1, c_1), (a_2, b_2, c_2), \cdots , (a_n, b_n, c_n)$ should be different positive integers with at most $100$ decimal digits each.
## 输入格式

The first line contains two integers $k$ and $n\;(2 \leq k \leq 1000, 1 \leq n \leq 1000)$ — the constant k in the
equation and the target number of triples.
## 输出格式

Output $n$ lines. The $i$-th line should contain three space separated integers $a_i$, $b_i$ and $c_i$ with at most $100$ digits each — the $i$-th of the solutions you found.
## 样例

### 样例输入 #1
```
2 8
```
### 样例输出 #1
```
1 2 6
3 10 24
12 35 88
15 28 84
4 5 18
14 33 90
40 104 273
21 60 152
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
1 3 12
8 21 87
44 165 615
```
## 题目翻译

### 题目描述：
假设 $k$ 大于 $1$，
可以证明有无穷多个正整数三元组 $(a, b, c)$ 满足以下方程:

   $a^2 + b^2 + c^2 = k(ab + bc + ca) + 1$
    
给定正整数 $n$ 和 $k$，找出 $n$ 个三元组 $(a_1, b_1, c_1), (a_2, b_2, c_2), ⋯ ,(a_n, b_n, c_n)$ 使它们都满足方程。另外，这 $3n$ 个正整数 $(a_1, b_1, c_1), (a_2, b_2, c_2), ⋯ ,(a_n, b_n, c_n)$ 应该是不同的，每个数最多有 $100$ 位。

### 输入格式：
第一行包含两个整数：
方程中的常数 $k$ 和 
所求三元组的数量 $n$ $(2 ≤ k ≤ 1000, 1 ≤ n ≤ 1000)$;

### 输出格式：
输出有 $n$ 行。第 $i$ 行应该包含三个空格分隔的正整数 $ai$, $bi$ 和 $ci$，
为你找到的第 $i$ 个解。每个数最多 $100$ 位。


---

---
title: "[ICPC 2016 WF] Oil"
layout: "post"
diff: 省选/NOI-
pid: P1691
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Oil
## 题目描述

A large part of the world economy depends on oil, which is why research into new methods for finding
and extracting oil is still active. Profits of oil companies depend in part on how efficiently they can
drill for oil. The International Crude Petroleum Consortium (ICPC) hopes that extensive computer
simulations will make it easier to determine how to drill oil wells in the best possible way.

Drilling oil wells optimally is getting harder each day – the newly discovered oil deposits often do
not form a single body, but are split into many parts. The ICPC is currently concerned with stratified deposits, as illustrated in Figure G.1.

To simplify its analysis, the ICPC considers only the 2-dimensional case, where oil deposits are modeled
as horizontal line segments parallel to the earth’s surface. The ICPC wants to know how to place a single
oil well to extract the maximum amount of oil. The oil well is drilled from the surface along a straight
line and can extract oil from all deposits that it intersects on its way down, even if the intersection is at
an endpoint of a deposit. One such well is shown as a dashed line in Figure G.1, hitting three deposits.
In this simple model the amount of oil contained in a deposit is equal to the width of the deposit. Can
you help the ICPC determine the maximum amount of oil that can be extracted by a single well?
## 输入格式

The first line of input contains a single integer n ($1 ≤ n ≤ 2 000$), which is the number of oil deposits.

This is followed by $n$ lines, each describing a single deposit. These lines contain three integers $x_0$,
$x_1$, and y giving the deposit’s position as the line segment with endpoints $(x_0, y)$ and $(x_1, y)$. These
numbers satisfy $|x_0|, |x_1| ≤ 10^6$
and $1 ≤ y ≤ 10^6$
. No two deposits will intersect, not even at a point.

## 输出格式

Display the maximum amount of oil that can be extracted by a single oil well.
## 样例

### 样例输入 #1
```
5
100 180 20
30 60 30
70 110 40
10 40 50
0 80 70
```
### 样例输出 #1
```
200
```
### 样例输入 #2
```
3
50 60 10
-42 -42 20
25 0 10
```
### 样例输出 #2
```
25
```
## 题目翻译

### 题目描述
世界经济的很大一部分依赖于石油，这就是为什么对发现和开采石油的新方法的研究仍然活跃。石油公司的利润在一定程度上取决于他们能够多么有效地钻探石油。国际原油石油联盟（ICPC）希望通过广泛的计算机模拟来更容易地确定如何以最佳方式钻探油井。

每天钻探油井变得越来越困难，因为新发现的油藏通常不是一个整体，而是分裂成许多部分。ICPC目前关注的是分层沉积物。

为了简化其分析，ICPC只考虑二维情况，其中油藏被建模为与地球表面平行的水平线段。ICPC想知道如何放置一个单独的油井以提取最大量的石油。油井沿着一条直线从地面钻井，并可以从其下降的路径上相交的所有沉积物中提取石油，即使相交点位于沉积物的端点处。图G.1中显示了一个这样的井，击中三个沉积物。在这个简单的模型中，一个沉积物中含有的石油量等于该沉积物的宽度。你能帮助ICPC确定通过一个单井可以提取的最大石油量吗？

### 输入格式
输入的第一行包含一个整数 $n (1\le n\le 2000)$，表示油田的数量。

接下来的 $n$ 行，每行描述一个沉积物。这些行包含三个整数 $x_0、x_1$ 和 $y$，表示沉积物的位置为线段，其端点为 $(x_0,y)$ 和 $(x_1,y)$。这些数字满足 $|x_0|,|x_1|≤10^6$。没有两个沉积物会相交，甚至不会在一点相交。

### 输出格式
输出一个整数，表示单个油井可以提取的最大石油量。



---

---
title: "[CERC2016] Lost Logic"
layout: "post"
diff: 省选/NOI-
pid: P1745
tag: ['2016', 'Special Judge', 'ICPC']
---
# [CERC2016] Lost Logic
## 题目描述

Gustav is reading about *2-satisfiability*, a well known problem of assigning truth values to boolean
variables in order to satisfy a list of *constraints* — simple logical formulas involving two variables each.

We are using $n$ variables $x_1, x_2, \cdots , x_n$ that can take on values $0$ (false) and $1$ (true). A constraint is a
formula of the form $a\to b$ where both $a$ and $b$ are possibly negated variables. As usual, $\to$ denotes
logical implication: $a \to b$ is $0$ only when $a$ is $1$ and $b$ is $0$. The negation of variable $a$ is denoted by $!a$.

Given an assignment of values to variables, we say that the constraint is *satisfied* if it evaluates to $1$.
Gustav has constructed a list of constraints and correctly concluded that there are *exactly three* different
assignments of values to variables that satisfy all the constraints. Gustav has wrote down all three
assignments but has, unfortunately, lost the list of constraints.
Given three assignments of $n$ values to variables, find any list consisting of at most $500$ constrains such
that the three given assignments are the *only* assignments that satisfy all the constraints.


## 输入格式

The first line contains an integer $n (2 \leq n \leq 50)$ — the number of variables. Three lines follow, each
describing one assignment. The $k$-th line contains $n$ space-separated integers $v_1^k,v_2^k,\cdots,v_n^k$, where each $v_i^k$ is either $0$ or $1$ and denotes the value of the variable $x_i$ in the $k$-th assignment. All three assignments will be different.
## 输出格式

If there is no solution output a single line containing the integer $−1$.
Otherwise, the first line should contain an integer $m$ where $1 \leq m \leq 500$ — the number of constraints
in your solution. The $k$-th of the following $m$ lines should contain the $k$-th constraint. Each constraint
should be a string constructed according to the following rules:

- A *variable* is a string of the form “$\texttt{x}i$” where $i$ is an integer between $1$ and $n$ inclusive written
  without leading zeros.
- A *literal* is a string consisting of a variable possibly preceded by the “$\texttt{!}$” character.
- A *constraint* is a string of the form “$a\texttt{ -> }b$” where both $a$ and $b$ are literals. The implication sign
  consists of the “minus” character and the “greater-than” character and there is a single space
  character both before and after the implication sign.


## 样例

### 样例输入 #1
```
3
0 0 0
0 1 0
1 0 0
```
### 样例输出 #1
```
3
x1 -> !x2
x3 -> x1
x3 -> x2
```
### 样例输入 #2
```
4
0 0 1 0
1 0 0 0
1 0 1 1
```
### 样例输出 #2
```
-1
```
## 题目翻译

给定 $3$ 组随机布尔变量 $v_{i,1},...,v_{i,n}(1\leq i\leq 3)$，每组均为 $n$ 个。你需要构造关于布尔变量 $x_1,...,x_n$ 的若干组**条件**，使得满足全部条件的布尔变量赋值**有且仅有** $(v_{i,1},...,v_{i,n})(1\leq i\leq 3)$ 这 $3$ 组。

由于机器限制，你所构造每组条件的形式均应为：$A\rightarrow B$。这组条件的限制了：当 $A$ 为 $1$ 时 $B$ 一定为 $1$。其中，$A,B$ 可能形如：

- $x_i$：表示第 $i$ 个变量的值。
- $!x_i$：表示第 $i$ 个变量取反后的值。

例如，如果你构造了 $x_1\rightarrow x_2$，那么表示你规定 $x_1=1$ 时必有 $x_2=1$；如果你构造了 $!x_1\rightarrow x_2$，那么你规定了 $x_1=0$ 时必有 $x_2=1$。你需要找到一种使用不超过 $500$ 组条件来满足题意的方法，或者判定这样的条件组合不可能存在。如果有多组解，输出任意一组均可。

数据保证 $2\leq n\leq 50,v_{i,j}\in\{0,1\}(1\leq i\leq 3,1\leq j\leq n)$。


---

---
title: "[ICPC-Beijing 2006] 狼抓兔子"
layout: "post"
diff: 省选/NOI-
pid: P4001
tag: ['2006', '网络流', '北京', '最小割', 'ICPC']
---
# [ICPC-Beijing 2006] 狼抓兔子
## 题目描述

现在小朋友们最喜欢的"喜羊羊与灰太狼"。话说灰太狼抓羊不到，但抓兔子还是比较在行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：

 ![](https://cdn.luogu.com.cn/upload/pic/11942.png) 

左上角点为 $(1,1)$，右下角点为 $(N,M)$（上图中 $N=3$，$M=4$）。有以下三种类型的道路：

1. $(x,y)\rightleftharpoons(x+1,y)$

2. $(x,y)\rightleftharpoons(x,y+1)$

3. $(x,y)\rightleftharpoons(x+1,y+1)$

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的。左上角和右下角为兔子的两个窝，开始时所有的兔子都聚集在左上角 $(1,1)$ 的窝里，现在它们要跑到右下角 $(N,M)$ 的窝中去，狼王开始伏击这些兔子。当然为了保险起见，如果一条道路上最多通过的兔子数为 $K$，狼王需要安排同样数量的 $K$ 只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。因为狼还要去找喜羊羊麻烦。

## 输入格式

第一行两个整数 $N,M$，表示网格的大小。

接下来分三部分。

第一部分共 $N$ 行，每行 $M-1$ 个数，表示横向道路的权值。

第二部分共 $N-1$ 行，每行 $M$ 个数，表示纵向道路的权值。

第三部分共 $N-1$ 行，每行 $M-1$ 个数，表示斜向道路的权值。
## 输出格式

输出一个整数，表示参与伏击的狼的最小数量。

## 样例

### 样例输入 #1
```
3 4
5 6 4
4 3 1
7 5 3
5 6 7 8
8 7 6 5
5 5 5
6 6 6
```
### 样例输出 #1
```
14
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $3 \leq N,M \leq 1000$，所有道路的权值均为不超过 $10^6$ 的正整数。


---

---
title: "[SEERC 2019] Tree Permutations"
layout: "post"
diff: 省选/NOI-
pid: P5803
tag: ['2019', 'ICPC']
---
# [SEERC 2019] Tree Permutations
## 题目描述

有一天，Cool 先生建了一棵 $n$ 个点的树（没有环的无向连通图），他给任一编号 $i > 1$ 的点规定了两个值：$p_i < i$ 代表点 $i$ 的父节点，与 $w_i$ 代表 $i$ 与 $p_i$ 之间的边的边权。点 $1$ 是树根，所以它没有父节点。

你想知道 Cool 先生建的树长啥样，但是 Cool 先生拒绝告诉你，但他给了你一些提示：

他把所有的 $p_i$ 和 $w_i$ 值写成一列，得到了长为 $2 \cdot n - 2$ 的数列 $b$。

$$ b=[p_2, w_2, p_3, w_3, \dots, p_{n-1}, w_{n-1}, p_n, w_n] $$

然后他将其随机打乱，得到了数列 $a$，并将 $a$ 告诉你。

然而只知道数列 $a$ 是无法还原那棵树的，你决定解决一个更难的问题。

定义一个树是 *$k$ 长*的，当且仅当点 $1$ 到点 $n$ 的路径上有恰好 $k$ 条边。

定义一个树是 *$k$ 完美*的，当且仅当这棵树是 *$k$ 长*的且点 $1$ 到点 $n$ 的路径上的边的边权之和是所有 *$k$ 长*的树中最大的。

你的任务是计算出每个 $k$ 值对应的 *$k$ 完美*的树中，点 $1$ 到点 $n$ 的路径上的边的边权之和。如果某个 $k$ 值不存在 *$k$ 完美*的树，则在该位置输出 $-1$。
## 输入格式

第一行包含一个整数 $n \ (2 \leq n \leq 10^5)$，代表树上的节点数。

第二行包含 $2 \cdot n -2$ 个整数 $a_1, a_2, \dots, a_{2n-2} \ (1 \leq a_i \leq n-1)$，代表数列 $a$ 中的数字。
## 输出格式

输出一行，共 $n-1$ 个空格隔开的整数 $w_1, w_2, w_3, \dots, w_{n-1}$，其中 $w_k$ 代表 *$k$ 完美*的树中点 $1$ 到点 $n$ 的路径上的边的边权之和。如果不存在 *$i$ 长*的树，则 $w_i=-1$。
## 样例

### 样例输入 #1
```
3
1 1 2 2
```
### 样例输出 #1
```
2 3
```
### 样例输入 #2
```
3
2 2 2 2
```
### 样例输出 #2
```
-1 -1
```
### 样例输入 #3
```
6
1 4 5 4 4 4 3 4 4 2
```
### 样例输出 #3
```
-1 -1 -1 17 20
```
## 提示

第一个样例中，*$1$ 完美*的树由数列 $[1, 2, 1, 2]$ 构成（即，$p_2=1, w_2=2, p_3=1, w_3=2$），*$2$ 完美*的树由数列 $[1, 2, 2, 1]$ 构成（即，$p_2=1, w_2=2, p_3=2, w_3=1$）。以下是这两棵树的图形（点 $1$ 到点 $n$ 的路径上的边都为粗线）。

![样例1](https://cdn.luogu.com.cn/upload/image_hosting/lgpg0jne.png)

第二个样例中，不存在能通过重排 $a$ 构造出的 *$k$ 完美*的树。

第三个样例中，只有 *$4$ 完美*的和 *$5$ 完美*的树可以被构造出。它们分别由数列 $[1, 4, 2, 4, 3, 4, 4, 4, 4, 5]$ 和 $[1, 4,2, 4, 3, 4, 4, 4, 5, 4]$ 构成。以下是这两棵树的图形。

![样例3](https://cdn.luogu.com.cn/upload/image_hosting/rz04b4ro.png)


---

---
title: "[SEERC 2018] Inversion"
layout: "post"
diff: 省选/NOI-
pid: P5871
tag: ['2018', 'ICPC']
---
# [SEERC 2018] Inversion
## 题目描述

定义一个长为 $n$ 的*排列*为一个序列 $p_1, p_2, \dots, p_n$，其中 $[1, n]$ 范围内的整数都恰好在这个序列中出现一次。定义排列中的一个*逆序对*为一对整数 $(i, j)$，其中 $i, j \in [1,n]$，且满足 $i<j, p_i>p_j$。

定义一个*逆序对图*为一个有 $n$ 个点的图，图中存在一条 $(i, j)$ 的边当且仅当 $(i,j)$ 是一个逆序对。

定义一个图中的*独立集*为一个图中点的集合，满足集合中的点两两之间没有边相连。定义一个图中的*支配集*为一个图中点的集合，满足不在这个集合中的点都与集合中的某个点有边相连。定义一个图中的*独立支配集*为一个图中点的集合，这个集合既是独立集又是支配集。

给定某一个长为 $n$ 的排列的逆序对图，请计算出这个图中独立支配集的数量。

数据保证答案不会超过 $10^{18}$。
## 输入格式

第一行包含两个整数 $n$ 和 $m \ (1 \leq n \leq 100, 0 \leq m \leq \frac{n \times (n-1)}{2})$，代表图中的点数和边数。

接下来 $m$ 行每行包含两个整数 $u_i$ 和 $v_i \ (1 \leq u_i, v_i \leq n)$，代表图中点 $u_i$ 和 $v_i$ 之间有一条边相连。

数据保证图一定对应某一个排列。
## 输出格式

输出图中独立支配集的数量。

数据保证答案不会超过 $10^{18}$。
## 样例

### 样例输入 #1
```
4 2
2 3
2 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5 7
2 5
1 5
3 5
2 3
4 1
4 3
4 2
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
7 7
5 6
2 3
6 7
2 7
3 1
7 5
7 4
```
### 样例输出 #3
```
6
```
### 样例输入 #4
```
5 6
1 3
4 5
1 4
2 3
1 2
1 5
```
### 样例输出 #4
```
5
```
## 提示

第一个样例中，图对应排列 $[1,4,2,3]$，独立支配集有 $(1,3,4)$ 和 $(1,2)$。

第二个样例中，图对应排列 $[3,5,4,1,2]$，独立支配集有 $(1,2),(1,3),(4,5)$。

第三个样例中，图对应排列 $[2,4,1,5,7,6,3]$。

第四个样例中，图对应排列 $[5,2,1,4,3]$。


---

---
title: "[NEERC 2016] Mole Tunnels"
layout: "post"
diff: 省选/NOI-
pid: P6122
tag: ['2016', 'ICPC', '模拟费用流']
---
# [NEERC 2016] Mole Tunnels
## 题目描述

鼹鼠们在底下开凿了 $n$ 个洞，由 $n-1$ 条隧道连接，对于任意的 $i>1$，第 $i$ 个洞都会和第 $\frac{i}{2}$（取下整）个洞间有一条隧道，第 $i$ 个洞内还有 $c_i$ 个食物能供最多 $c_i$ 只鼹鼠吃。一共有 $m$ 只鼹鼠，第 $i$ 只鼹鼠住在第 $p_i$ 个洞内。

一天早晨，前 $k$ 只鼹鼠醒来了，而后 $m-k$ 只鼹鼠均在睡觉，前 $k$ 只鼹鼠就开始觅食，最终他们都会到达某一个洞，使得所有洞的 $c_i$ 均大于等于该洞内醒着的鼹鼠个数，而且要求鼹鼠行动路径总长度最小。现对于所有的 $1 \le k \le m$，输出最小的鼹鼠行动路径的总长度，保证一定存在某种合法方案。
## 输入格式

第一行两个数 $n,m$，表示有 $n$ 个洞，$m$ 只鼹鼠。
第二行 $n$ 个整数 $c_i$ 表示第 $i$个洞的食物数。
第三行 $m$ 个整数 $p_i$ 表示第 $i$只鼹鼠所在洞 $p_i$。
## 输出格式

输出一行 $m$ 个整数，第 $i$ 个整数表示当 $k=i$ 时最小的鼹鼠行动路径总长度。

## 样例

### 样例输入 #1
```
5 4
0 0 4 1 1
2 4 5 2
```
### 样例输出 #1
```
1 1 2 4
```
## 提示

$1 \le n,m \le 10^5$，$0 \le c_i \le m$，$1 \le p_i \le n$。


---

---
title: "[NEERC 2015] Binary vs Decimal"
layout: "post"
diff: 省选/NOI-
pid: P6124
tag: ['高精度', '2015', '广度优先搜索 BFS', 'ICPC']
---
# [NEERC 2015] Binary vs Decimal
## 题目描述

一个正数 $A$，如果它只包含 `0` 或 `1`，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数。
## 输入格式

一行一个数 $N$。
## 输出格式

一行一个数，第 $N$ 个数。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
10
```
### 样例输出 #2
```
1100
```
## 提示

$1 \le N \le 10^4$。

|原数|二进制|评论|
| :-----------: | :-----------: | :-----------: |
|$1$|$1$|√|
|$10$|$1010$|√|
|$11$|$1011$|√|
|$100$|$1100100$|√|
|$101$|$1100101$|√|
|$110$|$1101110$|√|
|$111$|$1101111$|√|
|$1000$|$1111101000$|√|
|$1001$|$1111101001$|√|
|$1010$|$1111110010$|×|
|$1011$|$1111110011$|×|
|$1100$|$10001001100$|√| 


---

---
title: "[ICPC 2019 WF] Checks Post Facto"
layout: "post"
diff: 省选/NOI-
pid: P6253
tag: ['2019', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Checks Post Facto
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

Your university's board game club just hosted a Checkers tournament, and you were assigned to take notes on the games. Unfortunately, while walking home, you dropped all of your papers into a puddle! Disaster! Much of what you wrote is now unreadable; all you have left are some lists of moves played in the middle of various games. Is there some way you can reconstruct what happened in those games? You had better fix things fast, or they will demote you to Tic-Tac-Toe recordkeeper!

Checkers (or English Draughts) is a well-known board game with simple rules. It is played on the dark squares of an $8 \times 8$ checkerboard. There are two players, Black and White, who alternate turns moving their pieces (all of Black's pieces are black and all of White's pieces are white). Each piece occupies a single dark square, and can be either a normal $man$ or a promoted $king$. A turn consists of choosing one piece and moving it in one of two ways:

1. Shifting it diagonally to an unoccupied adjacent dark square, as shown in Figure C.1(a). This is called a $simple~move$. If the piece is a man, it can move only in the two diagonal directions towards the opposing side of the board (towards the bottom for Black, the top for White). If the piece is a king, it can move in all four diagonal directions.

2. Jumping over an adjacent enemy piece to an unoccupied square immediately on the other side, then removing ($capturing$) that piece. Men can jump only in the two directions described above, while kings can jump in all four. The player can then repeat this step, continuing to jump with the same piece as long as there are properly-positioned enemy pieces to capture. Such a sequence of one or more jumps is called a $jump~move$. Figure C.1(b) shows a jump move comprising three
jumps.

![](https://cdn.luogu.com.cn/upload/image_hosting/onoiijvu.png)

In Checkers, captures are forced moves. If a jump move is available at the start of a player's turn, they must jump, and cannot stop jumping with that piece until it has no more possible jumps. They are free to choose which piece to jump with, and where, if there are multiple possibilities. In Figure C.1(b), Black could not have made any other move.

If a man reaches the farthest row from its player (that is, a black man reaches the bottom row or a white man reaches the top row), it is removed from the board and replaced by a king of the same color (it is said to be $promoted$), and the turn ends. A piece cannot be promoted and then jump backwards as a new king in the same turn.


Given a list of moves, find a setup of pieces such that the moves can be legally played in sequence starting from that setup. This setup may not have black men on the bottom row or white men on the top row, since they would have been promoted to kings already. You need only ensure that the rules above are obeyed; you do not need to ensure that this setup is reachable in a real game of Checkers.
## 输入格式

The first line of input contains a character $c$ and an integer $n$, where $c$ is either `B` or `W`, indicates which player makes the first move (Black or White respectively) and $n$ ($1 \leq n \leq 100$) is the number of moves in the list. Then follow $n$ lines, each of which describes a move in the standard Checkers notation defined below.


The dark squares are identified by numbers $1 \sim 32$, as shown in Figure C.1(c). A simple move from square $a$ to square $b$ is written as `a-b`. A jump move starting at $a$ and jumping to $b_1, b_2, \dots , b_k$ is written as $a\text{x}b_1\text{x}b_2\text{x} \dots \text{x}b_k$.

There is always a valid solution for the given set of moves.
## 输出格式

Output two boards side-by-side (separated by a space), giving the positions of all pieces on the board before (on the left) and after (on the right) the given moves. Use  `-` for light squares,  `.` for empty dark squares, lowercase `b` and `w` for black and white men, and uppercase `B` and `W` for black and white kings. If there is more than one valid solution, any one is acceptable.
## 样例

### 样例输入 #1
```
W 3
21-17
13x22x31x24
19x28
```
### 样例输出 #1
```
-b-.-.-. -b-.-.-.
.-.-.-.- .-.-.-.-
-.-.-.-. -.-.-.-.
B-.-w-.- .-.-w-.-
-.-.-W-. -.-.-.-.
w-.-.-.- .-.-.-.-
-.-w-w-. -.-.-.-W
.-.-.-.- .-.-.-.-
```
### 样例输入 #2
```
B 5
2-7
9x2
32-27
2x11x18
5-9
```
### 样例输出 #2
```
-.-b-.-W -.-.-.-W
b-b-.-.- .-.-.-.-
-w-.-.-. -b-.-.-.
B-w-b-.- B-w-.-.-
-.-.-.-. -.-W-.-.
.-.-.-.- .-.-.-.-
-.-.-.-. -.-.-B-.
.-.-.-B- .-.-.-.-
```
## 提示

Source: ICPC World Finals 2019.
## 题目翻译

游戏在一个 $8 \times 8$ 的方格棋盘的深色方格上进行。有两名玩家，黑方和白方，他们轮流移动他们的棋子（所有黑方的棋子都是黑色的，所有白方的棋子都是白色的）。每个棋子占据一个单独的深色方格，可以是**兵**或**王**。一个回合包括选择一个棋子并以以下两种方式之一移动它：

1. 将其**斜着**移动到一个相邻的未占用的深色方格，如图 (a) 所示。这被称为**简单移动**。兵只能沿向前的两种方向移动（对于黑方是朝下，对于白方是朝上）。如果棋子是王，它可以在所有四个斜方向移动。

2. 跳过对方的棋子到达空地，并吃掉对方的子。允许移动的方向与第一条相同。然后，玩家可以重复此步骤，继续使用相同的棋子跳。这样一个或多个跳的序列称为**跳跃移动**。图 (b) 展示了由三个跳跃组成的跳跃移动。

如果在玩家回合开始时有一个跳跃移动可用，他们必须进行跳跃，并且不能停止使用该棋子跳跃，直到它没有更多可能的跳跃。他们可以自由选择使用哪个棋子进行跳跃，以及在有多个可能性的情况下选择在哪里跳跃。在图 (b) 中，黑方不能进行任何其他移动。

如果一个兵达到其玩家的最远一行（即，一个黑子达到底行或一个白子达到顶行），它将变成同色的王（称为**晋升**），然后**回合结束**。这意味着一个兵不能在同一回合中被晋升然后以王的身份继续倒退跳跃。

给定一系列移动，请找到一个初始棋局，使得可以从该棋局开始按顺序合法进行这些移动。此棋局可能不能在底行有黑子或在顶行有白子，因为它们可能已经被晋升为王。你只需要确保上述规则被遵守；不需要确保这个棋局在实际跳棋游戏中是可达的。

### 输入格式

输入的第一行包含一个字符 $c$ 和一个整数 $n$，其中 $c$ 是 B 或 W，表示哪个玩家首先移动（分别为黑方或白方），$n$（$1 \leq n \leq 100$）是移动列表中的移动次数。然后是 $n$ 行，每行描述标准跳棋符号中定义的一步移动。

深色方格用数字 $1 \sim 32$ 标识，如图 (c) 所示。从方格 $a$ 到方格 $b$ 的简单移动写作 a-b。从 $a$ 开始跳到 $b_1, b_2, \dots , b_k$ 的跳跃移动写作 $a\text{x}b_1\text{x}b_2\text{x} \dots \text{x}b_k$。

对于给定的移动集合，总是存在至少一个答案。

### 输出格式

所有棋子在棋盘上的位置以两个并排的棋盘输出（用空格分隔），分别表示在给定的移动之前（左边）和之后（右边）的棋盘。

使用`-`表示浅色方格，`.`表示空的深色方格，小写的`b`和`w`表示黑色和白色兵，大写的`B`和`W`表示黑色和白色王。如果存在多个答案，则任何一个都可以接受。


---

---
title: "[ICPC 2019 WF] First of Her Name"
layout: "post"
diff: 省选/NOI-
pid: P6257
tag: ['2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] First of Her Name
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

In the Royal Family, names are very important! As the Royal Historian you have been charged with analyzing the patterns in the names of the Royal Ladies in the realm.

There have been n Royal Ladies, for convenience numbered from 1 to $n$. The name of each Lady is anuppercase letter concatenated with the name of her mother. The exception is the Lady numbered 1, the
founder of the Royal Family, whose name is just a single uppercase letter.

For example, ENERYS could be the mother of AENERYS (as the name AENERYS consists of the single uppercase letter 'A' concatenated with ENERYS, which is her mother's name). Similarly, AENERYS could be the mother of DAENERYS and YAENERYS.

You are given the description of all the Royal Ladies. Your task is to determine, for certain interesting strings $s$, the number of Royal Ladies for whom s is a prefix of their name.

For example, consider Sample Input 1 below, with a Royal Line that goes straight from the founder S to AENERYS (through YS, RYS, ERYS, NERYS and ENERYS), with each Lady having exactly one daughter. Then AENERYS has two daughters—DAENERYS and YAENERYS, with the latter havingone daughter, RYAENERYS.

In such a family, RY is a prefix of the names of two ladies: RYS and RYAENERYS. E is a prefix of the names of ERYS and ENERYS. N is a prefix only of NERYS's name, while S is a prefix only of the nameof the founder, S. AY is not a prefix of any Royal Lady's name.

## 输入格式

The first line of input contains two integers $n$ and $k$, where $n$ $(1 \leq n \leq 10^6)$ is the total number of Royal Ladies and $k$ $(1 \leq k \leq 10^6)$ is the number of query strings.

Then follow n lines describing the Royal Ladies. The $i^{th}$ of these lines describes the Royal Lady numbered $i$, and contains an uppercase letter $c_i$ ('A'–'Z') and an integer $p_i$, where $c_i$ is the first letter of the name of Lady $i$, and $p_i$ $(p1 = 0$ and $1 \leq pi \lt i$ for $i \gt 1)$ is the number of her mother (or $0$, in the case
of the First Lady). All the names are unique.

The remaining $k$ lines each contain one nonempty query string, consisting only of uppercase letters. The sum of the lengths of the query strings is at most $10^6$.
## 输出格式

Output $k$ lines, with the $i^{th}$ line containing the number of Royal Ladies who have the $i^{th}$ query string as a prefix of their name.
## 样例

### 样例输入 #1
```
10 5
S 0
Y 1
R 2
E 3
N 4
E 5
A 6
D 7
Y 7
R 9
RY
E
N
S
AY
```
### 样例输出 #1
```
2
2
1
1
0
```
## 提示

Source: ICPC World Finals 2019.
## 题目翻译

**题目描述**



众所周知，皇室家族的名字非常有讲究。而作为研究皇室的历史学家的你，最近接到了一个艰巨的任务——分析王国历史中所有皇室夫人的名字。



王国历史上有 $n$ 位皇室夫人，方便起见，我们将其从 $1$ 至 $n$ 编号。除了 $1$ 号夫人外，其余夫人的名字均为一个大写字母连接着她母亲的名字。而 $1$ 号夫人作为王国的首任王后，她的名字只有一个大写字母。



例如，由于 `AENERYS` 由 `A` 与 `ENERYS` 组成，因此 `ENERYS` 是 `AENERYS` 的母亲。相似地，`AENERYS` 是 `DAENERYS` 与 `YAENERYS` 的母亲。



你知道王国历史上所有皇室夫人的姓名与关系，而你需要完成的任务是，对于其他历史学家感兴趣的名字串 $s$，总共有多少位夫人的名字是以 $s$ 起始的。



例如在样例的皇室族谱中，`S` 至 `AENERYS` 的这一支（包含 `YS`、`RYS`、`ERYS`、`NERYS` 与 `ENERYS` 这几位夫人）均只有一位女儿。接下来 `AENERYS` 有两位女儿，分别是 `DAENERYS`，以及女儿是 `RYAENERYS` 的 `YAENERYS`。



在这个皇室家族内，有两位夫人的名字以 `RY` 起始，她们是 `RYS` 与 `RYAENERYS`。而 `ERYS` 与 `ENERYS` 均以 `E` 起始。名字以 `N` 起始的仅有一位夫人 `NERYS`。同样地，以 `S` 起始的仅有首位王后 `S`。而没有任何一位夫人的名字以 `AY` 起始。



**输入格式**



第一行有两个整数 $n,k$，分别代表王国历史上皇室夫人总数，以及其他历史学家感兴趣的名字串的个数。



接下来 $n$ 行描述所有皇室夫人的姓名与关系。第 $i+1$ 行描述第 $i$ 位夫人的资料 $c_i$ 与 $p_i$，其中字符 $c_i$ 表示她名字的首位字母，$p_i$ 为她母亲的编号。对于编号为 $1$ 的首位王后，$p_1=0$。所有夫人的名字均不重复。



接下来 $k$ 行，每行为一个大写字母构成的非空串，代表一个其他历史学家感兴趣的名字串。



**输出格式**



输出 $k$ 行，第 $i$ 行为一个整数，代表总共有多少位夫人的名字是以第 $i$ 个感兴趣的名字串起始的。



**数据范围**



$1\leq n\leq 10^6$，$1\leq k\leq 10^6$，$p_1=0$，特别地，对于 $1\lt i\leq n$，保证有 $1\leq p_i\lt i$。感兴趣的名字串总长不超过 $10^6$。


---

---
title: "[ICPC 2019 WF] Miniature Golf"
layout: "post"
diff: 省选/NOI-
pid: P6260
tag: ['2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Miniature Golf
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

A group of friends has just played a round of miniature golf. Miniature golf courses consist of a number of holes. Each player takes a turn to play each hole by hitting a ball repeatedly until it drops into the hole.
A player's score on that hole is the number of times they hit the ball. 
To prevent incompetent players slowing down the game too much, there is also an upper limit $l$ (a positive integer) on the score: if a player has hit the ball $l$ times without the ball dropping into the hole, the score for that hole is recorded as $l$ and that player's turn is over. The total score of each player is simply the sum of their scores on all the holes. Naturally, a lower score is considered better.

There is only one problem: none of the players can remember the value of the integer $l$. They decide that they will not apply any upper limit while playing, allowing each player to keep playing until the ball
drops into the hole. After the game they intend to look up the value of $l$ and adjust the scores, replacing any score on a hole that is larger than $l$ with $l$.

The game has just finished, but the players have not yet looked up $l$. They wonder what their best possible ranks are. For this problem, the rank of a player is the number of players who achieved an equal or lower total score after the scores are adjusted with $l$. For example, if the adjusted scores of the players are $3, 5, 5, 4,$ and $3$, then their ranks are $2, 5, 5, 3$ and $2$ respectively.

Given the scores of the players on each hole, determine the smallest possible rank for each player.
## 输入格式

The first line of input contains two integers $p$ and $h$, where $p$ $(2 \leq p \leq 500)$ is the number of players and $h$ $(1 \leq h \leq 50)$ is the number of holes. The next $p$ lines each contain $h$ positive integers. The $j^{th}$ number on the $i^{th}$ of these lines is the score for player $i$ on hole $j$, and does not exceed $10^9$.

## 输出格式

Output a line with the minimum possible rank for each player, in the same order as players are listed in the input.
## 样例

### 样例输入 #1
```
3 3
2 2 2
4 2 1
4 4 1
```
### 样例输出 #1
```
1
2
2
```
### 样例输入 #2
```
6 4
3 1 2 2
4 3 2 2
6 6 3 2
7 3 4 3
3 4 2 4
2 3 3 5
```
### 样例输出 #2
```
1
2
5
5
4
3

```
## 提示

Source: ICPC World Finals 2019 Problem J: Miniature Golf.
## 题目翻译

### 题目描述
几个朋友玩了一场小型的高尔夫。这种小型的高尔夫是由若干个洞组成的。每个玩家轮流玩这个游戏，不停地击球直到球落到每个洞里。玩家在一个洞上的得分是他击球的次数。为了防止捣乱的玩家把游戏速度放慢太多，游戏规则中也会给一个上限$l$（一个正整数）来控制分数：如果一个玩家在一个洞上已经击球$l$次，但是球还没有落到洞里，那么这个玩家在这个洞上的得分就是$l$，并且这个玩家的回合就结束了。一个玩家的总得分就是他在各个洞上的得分之和。自然地，在这个游戏中，分越低越好。

但是有一个问题：没有玩家记得$l$的值。玩家们决定在玩的时候不设置$l$的值，允许每个玩家不断击球，直到球掉到洞里。玩完游戏，他们准备设置$l$的值，并更改那些在洞上的分数大于$l$的值。

游戏结束了，但他们还没有设置$l$。他们想知道自己的最佳排名是什么。一个人的排名是在所有人中，得分比这个人低或和这个人相等的人数（包含自己）。比如，当五个人的得分分别是 $3,5,5,4,3$，那么他们的排名就是 $2,5,5,3,2$。

给你每个玩家在每个洞上的得分，为每一个玩家求出最小的可能的排名。

### 输入格式

第一行：两个整数 $p$ 和 $h$，$p$（$2 \le p \le 500$）是玩家个数，$h$（$1 \le h \le 50$）是洞的个数。

接下来$p$行，每行$h$个正整数，第$i$行第$j$列的数表示第$i$个玩家在第$j$个洞上的得分，这些数都不会超过$10^9$。

### 输出格式

输出 $p$ 行，每行一个正整数，第 $i$ 行表示第 $i$ 个玩家的最小排名。

### 说明/提示

来源：ICPC World Finals 2019 Problem J 

题目名称：Miniature Golf


---

---
title: "[ICPC 2014 WF] Buffed Buffet"
layout: "post"
diff: 省选/NOI-
pid: P6893
tag: ['动态规划 DP', '2014', 'Special Judge', '背包 DP', 'ICPC']
---
# [ICPC 2014 WF] Buffed Buffet
## 题目描述

You are buying lunch at a buffet. A number of different dishes are available, and you can mix and match them to your heart’s desire. Some of the dishes, such as dumplings and roasted potatoes, consist of pieces of roughly equal size, and you can pick an integral number of such pieces (no splitting is allowed). Refer to these as “discrete dishes.” Other dishes, such as tzatziki or mashed potatoes, are fluid and you can pick an arbitrary real-valued amount of them. Refer to this second type as “continuous dishes.”

Of course, you like some of the dishes more than others, but how much you like a dish also depends on how much of it you have already eaten. For instance, even if you generally prefer dumplings to potatoes, you might prefer a potato over a dumpling if you have already eaten ten dumplings. To model this, each dish $i$ has an initial tastiness $t_ i$, and a rate of decay of the tastiness $\Delta t_ i$. For discrete dishes, the tastiness you experience when eating the $n^{th}$ item of the dish is $t_ i - (n-1)\Delta t_ i$. For continuous dishes, the tastiness you experience when eating an infinitesimal amount $d x$ grams of the dish after already having eaten $x$ grams is $(t_ i - x \Delta t_ i) d x$. In other words, the respective total amounts of tastiness you experience when eating $N$ items of a discrete dish or $X$ grams of a continuous dish are as follows:

$$\begin{aligned} \sum _{n=1}^{N} (t_ i - (n-1)\Delta t_ i) & &  \text {and} & & \int _{0}^ X (t_ i - x\Delta t_ i) dx  \end{aligned} $$

For simplicity, do not take into account that different dishes may or may not go well together, so define the total tastiness that you experience from a meal as the sum of the total tastinesses of the individual dishes in the meal (and the same goes for the weight of a meal – there are no food antiparticles in the buffet!).

You have spent days of painstaking research determining the numbers $t_ i$ and $\Delta t_ i$ for each of the dishes in the buffet. All that remains is to compute the maximum possible total tastiness that can be achieved in a meal of weight $w$. Better hurry up, lunch is going to be served soon!
## 输入格式

The input consists of a single test case. The first line of input consists of two integers $d$ and $w$ ($1 \le d \le {250}$ and $1 \le w \le {10\, 000}$), where $d$ is the number of different dishes at the buffet and $w$ is the desired total weight of your meal in grams.

Then follow $d$ lines, the $i^{th}$ of which describes the $i^{th}$ dish. Each dish description is in one of the following two forms:

A description of the form “D $w_ i$ $t_ i$ $\Delta t_ i$” indicates that this is a discrete dish where each item weighs $w_ i$ grams, with initial tastiness $t_ i$ and decay of tastiness $\Delta t_ i$.

A description of the form “C $t_ i$ $\Delta t_ i$” indicates that this is a continuous dish with initial tastiness $t_ i$ and decay of tastiness $\Delta t_ i$.

The numbers $w_ i$, $t_ i$, and $\Delta t_ i$ are integers satisfying $1 \le w_ i \le {10\, 000}$ and $0 \le t_ i, \Delta t_ i \le {10\, 000}$.
## 输出格式

Display the maximum possible total tastiness of a meal of weight $w$ based on the available dishes. Give the answer with a relative or absolute error of at most $10^{-6}$. If it is impossible to make a meal of total weight exactly $w$ based on the available dishes, display impossible.
## 样例

### 样例输入 #1
```
2 15
D 4 10 1
C 6 1

```
### 样例输出 #1
```
40.500000000

```
### 样例输入 #2
```
3 15
D 4 10 1
C 6 1
C 9 3

```
### 样例输出 #2
```
49.000000000

```
### 样例输入 #3
```
2 19
D 4 5 1
D 6 3 2

```
### 样例输出 #3
```
impossible

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

### 题目描述

自助餐厅里有 $n$ 种食物，分为两大类，为 “离散食物”和“连续食物”。你可以通过吃食物来获得收益。

离散食物用 $(w,t_0,\Delta t)$ 描述。对于这种食物，你只能吃整数个，每个重为 $w$。吃的第一个收益为 $t_0$，后面每吃一个收益减少 $\Delta t$。具体的，吃的第 $i$ 个这种食物 （从 $1$ 开始标号），收益为 $t_0-(i-1)\Delta t$。

连续食物用 $(t_0,\Delta t)$ 描述。对于这种食物，你可以吃任意食物的重量。如果你吃的重量为 $w$，获得的收益是 $t_0w-\dfrac{1}{2}\Delta t w^2$。

你现在要吃重量和 **恰好** 为 $W$ 的食物。最大化你的收益。

### 数据范围

$n\le 250,W\le 10000$。

对于离散食物，满足 $1\le w\le 10000$。

对于所有食物，满足 $0\le t_0,t\le 10000$。

### 输入格式

第一行是 $n,W$，接下来每行先来一个字母，如果是 C 表示连续食物，后面跟两个数表示 $t_0,\Delta t$；如果是 D 表示离散食物，后面跟三个数，表示 $w,t_0,\Delta t$。

### 输出格式

一行一个数表示答案。相对或绝对误差不超过 $1e-6$。


---

---
title: "[ICPC 2014 WF] Maze Reduction"
layout: "post"
diff: 省选/NOI-
pid: P6896
tag: ['2014', '哈希 hashing', 'ICPC']
---
# [ICPC 2014 WF] Maze Reduction
## 题目描述

Jay runs a small carnival that has various rides and attractions. Unfortunately, times are tough. A recent roller coaster accident, flooding in the restrooms, and an unfortunate clown incident have given Jay’s carnival a bad reputation with the public. With fewer paying customers and reduced revenue, he will need to cut some costs to stay in business.

One of the biggest carnival attractions is a large, confusing maze. It consists of a variety of circular rooms connected by narrow, twisting corridors. Visitors love getting lost in it and trying to map it out. It has come to Jay’s attention that some of the rooms might be effectively identical to each other. If that’s the case, he will be able to reduce its size without anyone noticing.

Two rooms $A$ and $B$ are effectively identical if, when you are dropped into either room $A$ or $B$ (and you know the map of the maze), you cannot tell whether you began in $A$ or $B$ just by exploring the maze. The corridor exits are evenly spaced around each room, and you cannot mark or leave anything in a room (in particular, you cannot tell whether you have previously visited it). The only identifying feature that rooms have is their number of exits. Corridors are also twisty enough to be indistinguishable from each other, but when you enter a room you know which corridor you came from, so you can navigate a little by using the order they appear around the room.

Jay has appealed to the Association for Carnival Mazery for help. That’s you! Write a program to determine all the sets of effectively identical rooms in the maze.
## 输入格式

The input consists of a single test case. The first line contains an integer $n$, the number of rooms in the maze ($1 \leq n \leq 100$). Rooms are numbered from 1 to $n$. Following this are $n$ lines, describing each room in order. Each line consists of an integer $k$, indicating that this room has $k$ corridors ($0 \leq k < 100$), and then $k$ distinct integers listing the rooms each corridor connects to (in clockwise order, from an arbitrary starting point). Rooms do not connect to themselves.
## 输出格式

Display one line for each maximal set of effectively identical rooms (ignoring sets of size 1) containing the room numbers in the set in increasing order. Order the sets by their smallest room numbers. If there are no such sets, display none instead.
## 样例

### 样例输入 #1
```
13
2 2 4
3 1 3 5
2 2 4
3 1 3 6
2 2 6
2 4 5
2 8 9
2 7 9
2 7 8
2 11 13
2 10 12
2 11 13
2 10 12

```
### 样例输出 #1
```
2 4
5 6
7 8 9 10 11 12 13

```
### 样例输入 #2
```
6
3 3 4 5
0
1 1
1 1
2 1 6
1 5

```
### 样例输出 #2
```
none

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

Jay经营着一家小型游乐场，其中有各种游乐设施和景点。不幸的是，由于顾客和收入的锐减，他将需要削减成本以维持业务。

一个大型迷宫是最大的景点之一，它由不同的圆形房间组成。这些房间通过狭窄且扭曲的走廊相连，而某些游客喜欢迷失在迷宫中并试图将其绘制出来。Jay已经注意到，有些房间可能一模一样。如果出现这样的情况，他就能减小迷宫的尺寸而不会被任何人发现。

当您进入AA或是BB房间（并且您知道迷宫的地图）时，两个房间AA和BB是相同的，那么您仅通过探索迷宫就无法分辨是从AA还是BB开始行动。走廊出口在每个房间周围均等分布，您不能在房间内标记或留下任何东西（您无法判断是否进入过该房间）。房间唯一的标识是出口数量。走廊很曲折，彼此之间无法区分，但是当您进入一个房间时，您会知道您来自哪个走廊，因此您可以通过它们在房间周围出现的顺序来指引方向。

Jay向你寻求帮助，请编写程序以找出迷宫中所有相同房间的集合。

Translated by EndlIa


---

---
title: "[ICPC 2014 WF] Sensor Network"
layout: "post"
diff: 省选/NOI-
pid: P6900
tag: ['2014', 'Special Judge', '随机化', 'ICPC']
---
# [ICPC 2014 WF] Sensor Network
## 题目描述


A wireless sensor network consists of autonomous sensors scattered in an environment where they monitor conditions such as temperature, sound, and pressure. 

Samantha is a researcher working on the Amazon Carbon-dioxide Measurement (ACM) project. In this project, a wireless sensor network in the Amazon rainforest gathers environmental information. The Amazon rainforest stores an amount of carbon equivalent to a decade of global fossil fuel emissions, and it plays a crucial role in the world’s oxygen-transfer processes. Because of the huge size of this forest, changes in the forest affect not only the local environment but also global climate by altering wind and ocean current patterns. The goal of the ACM project is to help scientists better understand earth’s complex ecosystems and the impact of human activities.

Samantha has an important hypothesis and to test her hypothesis, she needs to find a subset of sensors in which each pair of sensors can communicate directly with each other. A sensor can communicate directly with any other sensor having distance at most $d$ from it. In order for her experiments to be as accurate as possible, Samantha wants to choose as many sensors as possible.

As one does not simply walk into the Amazon, Samantha cannot add new sensors or move those that are currently in place. So given the current locations of the sensors, she needs your help to find the largest subset satisfying her criteria. For simplicity, represent the location of each sensor as a point in a two-dimensional plane with the distance between two points being the usual Euclidean distance.
## 输入格式

The input consists of a single test case. The first line contains two integers $n$ and $d$ ($1 \le n \le 100$ and $1 \le d \le 10\, 000$), where $n$ is the number of sensors available and $d$ is the maximum distance between sensors that can communicate directly. Sensors are numbered $1$ to $n$. Each of the next $n$ lines contains two integers $x$ and $y$ ($-10\, 000\le x, y \le 10\, 000$) indicating the sensor coordinates, starting with the first sensor.
## 输出格式

Display a maximum subset of sensors in which each pair of sensors can communicate directly. The first line of output should be the size of the subset. The second line of output should be the (one-based) indices of the sensors in the subset. If there are multiple such subsets, any one of them will be accepted.
## 样例

### 样例输入 #1
```
4 1
0 0
0 1
1 0
1 1

```
### 样例输出 #1
```
2
1 2

```
### 样例输入 #2
```
5 20
0 0
0 2
100 100
100 110
100 120

```
### 样例输出 #2
```
3
4 3 5

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

无线传感器网络由分散在环境中的自主传感器组成，它们监控温度、声音和压力等条件。

萨曼莎是亚马逊二氧化碳测量 (Amazon Carbon-dioxide Measurement, ACM) 项目的研究员。在这个项目中，亚马逊雨林的无线传感器网络收集环境信息。亚马逊雨林储存了相当于十年全球化石燃料排放量的碳，它在世界的氧气转移过程中扮演着至关重要的角色。由于这片森林面积巨大，森林的变化不仅会影响当地环境，还会通过改变风和洋流模式来影响全球气候。ACM 项目的目标是帮助科学家更好地了解地球复杂的生态系统和人类活动的影响。

萨曼莎有一个重要的猜想，为了验证她的猜想，她需要找到传感器的一个子集，在这些传感器中，每对传感器都可以直接相互通信。传感器可以与距离它不超过 $d$ 的任何其他传感器直接通信。为了让她的实验尽可能准确，萨曼莎希望选择尽可能多的传感器。

因为人们不能简单地走进亚马逊，萨曼莎不能添加新的传感器，也不能移动那些目前设置好的传感器。因此，给出传感器目前的位置，她需要你的帮助来找到满足她标准的最大子集。为简单起见，每个传感器的位置被表示为二维平面中的一个点，两点之间的距离为通常的欧几里德距离。


#### 输入

第一行两个整数 $n$ 和 $d$ ($1\le n\le 100$, $1\le d\le 10\,000$)，其中 $n$ 表示传感器的个数，$d$ 表示传感器能直接通信的最大距离。传感器从 $1$ 到 $n$ 编号。接下来的 $n$ 行，每行两个整数 $x$, $y$ ($-10\,000\le x,y\le 10\,000$)，表示每个传感器的坐标，从第一个传感器开始。

#### 输出

输出满足要求的一个最大子集。第一行输出子集的大小。第二行输出子集中传感器的编号 (从 $1$ 开始编号)。如果有多个满足要求的最大子集，输出任意一个均可。


---

---
title: "[ICPC 2015 WF] Catering"
layout: "post"
diff: 省选/NOI-
pid: P6906
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Catering
## 题目描述

 ![](https://vj.z180.cn/c3c77c406a120e9e6c632a7a3d0cfeac?v=1603344926)  

Paul owns a catering company and business is booming. The company has $k$ catering teams, each in charge of one set of catering equipment. Every week, the company accepts $n$ catering requests for various events. For every request, they send a catering team with their equipment to the event location. The team delivers the food, sets up the equipment, and instructs the host on how to use the equipment and serve the food. After the event, the host is responsible for returning the equipment back to Paul’s company. 

Unfortunately, in some weeks the number of catering teams is less than the number of requests, so some teams may have to be used for more than one event. In these cases, the company cannot wait for the host to return the equipment and must keep the team on-site to move the equipment to another location. The company has an accurate estimate of the cost to move a set of equipment from any location to any other location. Given these costs, Paul wants to prepare an Advance Catering Map to service the requests while minimizing the total moving cost of equipment (including the cost of the first move), even if that means not using all the available teams. Paul needs your help to write a program to accomplish this task. The requests are sorted in ascending order of their event times and they are chosen in such a way that for any $i < j$, there is enough time to transport the equipment used in the $i^{th}$ request to the location of the $j^{th}$ request.
## 输入格式

The first line of input contains two integers $n$ ($1 \le n \le 100$) and $k$ ($1 \le k \le 100$) which are the number of requests and the number of catering teams, respectively. Following that are $n$ lines, where the $i^{th}$ line contains $n-i+1$ integers between $0$ and $1\, 000\, 000$ inclusive. The $j^{th}$ number in the $i^{th}$ line is the cost of moving a set of equipment from location $i$ to location $i+j$. The company is at location $1$ and the $n$ requests are at locations $2$ to $n+1$.
## 输出格式

Display the minimum moving cost to service all requests. (This amount does not include the cost of moving the equipment back to the catering company.)
## 样例

### 样例输入 #1
```
3 2
40 30 40
50 10
50

```
### 样例输出 #1
```
80

```
### 样例输入 #2
```
3 2
10 10 10
20 21
21

```
### 样例输出 #2
```
40

```
## 提示

Time limit: 4000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

有一家装备出租公司收到了按照时间顺序排列的 $n$ 个请求。

这家公司有 $k$ 个搬运工。每个搬运工可以搬着一套装备**按时间顺序**去满足一些请求。

一个搬运工从第 $i$ 个请求的位置把东西搬到第 $j$ 个请求的位置需要一些费用。公司的编号是 1，请求的编号是 $2\sim n+1$。所有搬运工必须从公司出发。

求满足所有请求所需的最小搬运费用.


---

---
title: "[ICPC 2015 WF] Tile Cutting"
layout: "post"
diff: 省选/NOI-
pid: P6913
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Tile Cutting
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/f8fpcjx7.png) 

Youssef is a Moroccan tile installer who specializes in mosaics like the one shown on the right. He has rectangular tiles of many dimensions at his disposal, and the dimensions of all his tiles are integer numbers of centimeters. When Youssef needs parallelogram-shaped tiles, he cuts them from his supply on hand. To make this work easier, he invented a tile cutting machine that superimposes a centimeter grid on the cutting surface to guide the cuts on the tiles. Due to machine limitations, aesthetic sensibilities, and Youssef’s dislike of wasted tiles, the following rules determine the possible cuts. 

The rectangular tile to be cut must be positioned in the bottom left corner of the cutting surface and the edges must be aligned with the grid lines.

The cutting blade can cut along any line connecting two different grid points on the tile boundary as long as the points are on adjacent boundary edges.

The four corners of the resulting parallelogram tile must lie on the four sides of the original rectangular tile.

No edge of the parallelogram tile can lie along an edge of the rectangular tile.

Figure 1 shows the eight different ways in which a parallelogram tile of area $4$ square centimeters can be cut out of a rectangular tile, subject to these restrictions.

![](https://cdn.luogu.com.cn/upload/image_hosting/figekxdx.png)

   Figure 1: The eight different ways for cutting a parallelogram of area 4. 

Youssef needs to cut tiles of every area between $a_{\text {lo}}$ and $a_{\text {hi}}$. Now he wonders, for which area $a$ in this range can he cut the maximum number of different tiles?
## 输入格式

The input consists of multiple test cases. The first line of input contains an integer $n$ ($1 \le n \le 500$), the number of test cases. The next $n$ lines each contain two integers $a_{\text {lo}}, a_{\text {hi}}$ ($1 \le a_{\text {lo}} \le a_{\text {hi}} \le 500\, 000$), the range of areas of the tiles.
## 输出格式

For each test case $a_{\text {lo}}$, $a_{\text {hi}}$, display the value $a$ between $a_{\text {lo}}$ and $a_{\text {hi}}$ such that the number of possible ways to cut a parallelogram of area $a$ is maximized as well as the number of different ways $w$ in which such a parallelogram can be cut. If there are multiple possible values of $a$ display the smallest one.
## 样例

### 样例输入 #1
```
2
4 4
2 6

```
### 样例输出 #1
```
4 8
6 20

```
## 提示

Time limit: 11000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

Youssef是一名专业贴瓷砖的修墙工，并且擅长用瓷砖贴出马赛克图案（如上图所示）。所有的瓷砖的尺寸长度均为整数，单位为$cm$。在马赛克图案中，平行四边形是不可或缺的。因此，Youssef会使用切割机，将矩形的瓷砖进行切割。在切割过程中，Youssef选择使用网格辅助切割机进行切割（在瓷砖上布上$cm$的网格方便切割）。

	切割过程有以下要求：
1.	可以从两个不同端点的连线切割（可以斜着切割）
2.	新平行四边形的四个角必须在矩形瓷砖的最外侧边上
3.	平行四边形的边不能与矩形的任意一条边边重叠

现在给出切割的面积的两个边界值$a_{lo}$和$a_{hi}$，求出Youssef能够最多切割掉的小矩形瓷砖数量。

**输入格式：**

给出测试样例数量$n$($1≤n≤500$)。下面$n$行给出切割面积的两个边界值$a_{lo}$和$a_{hi}$（$1≤a_{lo}≤a_{hi}≤500 000$）

**输出格式：**

每行先输出平行四边形面积$a$，再输出小矩形最多切割数量$w$。如果$a$有不同值的时候，输出最小的即可。


---

---
title: "[ICPC 2015 WF] Weather Report"
layout: "post"
diff: 省选/NOI-
pid: P6915
tag: ['2015', 'Special Judge', '霍夫曼树', 'ICPC']
---
# [ICPC 2015 WF] Weather Report
## 题目描述

 ![](https://cdn.luogu.com.cn/upload/image_hosting/xqo70y6n.png)

You have been hired by the Association for Climatological Measurement, a scientific organization interested in tracking global weather trends over a long period of time. Of course, this is no easy task. They have deployed many small devices around the world, designed to take periodic measurements of the local weather conditions. These are cheap devices with somewhat restricted capabilities. Every day they observe which of the four standard kinds of weather occurred: Sunny, Cloudy, Rainy, or Frogs. After every $n$ of these observations have been made, the results are reported to the main server for analysis. However, the massive number of devices has caused the available communication bandwidth to be overloaded. The Association needs your help to come up with a method of compressing these reports into fewer bits. 

For a particular device’s location, you may assume that the weather each day is an independent random event, and you are given the predicted probabilities of the four possible weather types. Each of the $4^ n$ possible weather reports for a device must be encoded as a unique sequence of bits, such that no sequence is a prefix of any other sequence (an important property, or else the server would not know when each sequence ends). The goal is to use an encoding that minimizes the expected number of transmitted bits.
## 输入格式

The first line of input contains an integer $1 \le n \le 20$, the number of observations that go into each report. The second line contains four positive floating-point numbers, $p_{\text {sunny}}$, $p_{\text {cloudy}}$, $p_{\text {rainy}}$, and $p_{\text {frogs}}$, representing the respective weather probabilities. These probabilities have at most 6 digits after the decimal point and sum to 1.
## 输出格式

Display the minimum expected number of bits in the encoding of a report, with an absolute or relative error of at most $10^{-4}$.
## 样例

### 样例输入 #1
```
2
0.9 0.049999 0.05 0.000001

```
### 样例输出 #1
```
1.457510

```
### 样例输入 #2
```
20
0.25 0.25 0.25 0.25

```
### 样例输出 #2
```
40.000000

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

给定4种天气情况出现的概率，你需要将n天的所有可能的 $4^{n}$ 种情况已某种方式编码为01串，使得：
- 编码长度的期望最短
- 任何一个编码不是另一个编码的前缀

求期望长度。


---

---
title: "[ICPC 2015 WF] Window Manager"
layout: "post"
diff: 省选/NOI-
pid: P6916
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Window Manager
## 题目描述

The past few years have seen a revolution in user interface technology. For many years, keyboards and mice were the tools used to interact with computers. But with the introduction of smart phones and tablets, people are increasingly using their computers by tapping and moving their fingers on the screen. Naturally this has led to new paradigms in user interface design. One important principle is that objects on the display obey “physical” laws. In this problem, you will see an example of this.

You have been hired to build a simulator for the window manager to be used in the next generation of smart phones from Advanced Cellular Manufacturers (ACM). Each phone they produce will have a rectangular screen that fully displays zero or more rectangular windows. That is, no window exceeds the boundaries of the screen or overlaps any other window. The simulator must support the following commands.

OPEN $x$ $y$ $w$ $h$ — open a new window with top-left corner coordinates $(x,y)$, width $w$ pixels and height $h$ pixels.

CLOSE $x$ $y$ — close an open window that includes the pixel at $(x,y)$. This allows a user to tap anywhere on a window to close it.

RESIZE $x$ $y$ $w$ $h$ — set the dimensions of the window that includes the pixel at $(x,y)$ to width $w$ and height $h$. The top-left corner of the window does not move.

MOVE $x$ $y$ $d_ x$ $d_ y$ — move the window that includes the pixel at $(x,y)$. The movement is either $d_ x$ pixels in the horizontal direction or $d_ y$ pixels in the vertical direction. At most one of $d_ x$ and $d_ y$ will be non-zero.

The OPEN and RESIZE commands succeed only if the resulting window does not overlap any other windows and does not extend beyond the screen boundaries. The MOVE command will move the window by as many of the requested pixels as possible. For example, if $d_ x$ is 30 but the window can move only 15 pixels to the right, then it will move 15 pixels.

![](https://cdn.luogu.com.cn/upload/image_hosting/3zw4uj2x.png)

   Figure 1: MOVE example 

ACM is particularly proud of the MOVE command. A window being moved might “bump into” another window. In this case, the first window will push the second window in the same direction as far as appropriate, exactly as if the windows were physical objects. This behavior can cascade – a moving window might encounter additional windows which are also pushed along as necessary. Figure 1 shows an example with three windows, where window A is moved to the right, pushing the other two along.
## 输入格式

The first line of input contains two positive integers $x_{\max }$ and $y_{\max }$, the horizontal and vertical dimensions of the screen, measured in pixels. Each is at most $10^9$ (ACM is planning on building displays with very high resolution). The top-left pixel of the screen has coordinates $(0,0)$. Each of the following lines contains a command as described above. One or more spaces separate the command name and the parameters from each other. The command parameters are integers that satisfy these conditions: $0 \leq x < x_{\max }$, $0 \leq y < y_{\max }$, $1 \leq w,h \leq 10^9$, and $|d_ x|,|d_ y| \leq 10^9$. There will be at most 256 commands.
## 输出格式

The output must follow the format illustrated in the sample output below.

Simulate the commands in the order they appear in the input. If any errors are detected during a command’s simulation, display the command number, command name, and the first appropriate message from the following list, and ignore the results of simulating that command (except as noted).

no window at given position — for the CLOSE, RESIZE, and MOVE commands — if there is no window that includes the pixel at the specified position.

window does not fit — for the OPEN and RESIZE commands — if the resulting window would overlap another window or extend beyond the screen boundaries.

moved $d’$ instead of $d$ — for the MOVE command — if the command asked to move a window $d$ pixels, but it could only move $d’$ pixels before requiring a window to move beyond the screen boundaries. The values $d$ and $d’$ are the absolute number of pixels requested and moved, respectively. The window is still moved in this case, but only for the smaller distance.

After all commands have been simulated and any error messages have been displayed, indicate the number of windows that are still open. Then for each open window, in the same order that they were opened, display the coordinates of the top-left corner $(x,y)$, the width, and the height.
## 样例

### 样例输入 #1
```
320 200
OPEN 50 50 10 10
OPEN 70 55 10 10
OPEN 90 50 10 10
RESIZE 55 55 40 40
RESIZE 55 55 15 15
MOVE 55 55 40 0
CLOSE 55 55
CLOSE 110 60
MOVE 95 55 0 -100

```
### 样例输出 #1
```
Command 4: RESIZE - window does not fit
Command 7: CLOSE - no window at given position
Command 9: MOVE - moved 50 instead of 100
2 window(s):
90 0 15 15
115 50 10 10

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

过去几年，用户界面技术发生了一场革命。多年来，键盘和鼠标一直是与计算机交互的工具。但随着智能手机和平板电脑的推出，人们越来越多地通过在屏幕上敲击和移动手指来使用电脑。这自然导致了用户界面设计的新范式。一个重要的原则是显示器上的对象遵守“物理”定律。在这个问题中，您将看到一个例子。

您已被聘请为window manager构建一个模拟器，用于高级手机制造商（ACM）的下一代智能手机。他们生产的每款手机都有一个矩形屏幕，可以完全显示零个或多个矩形窗口。也就是说，没有窗口超出屏幕边界或与任何其他窗口重叠。模拟器必须支持以下命令。

OPEN x y w h——打开一个具有左上角坐标（x，y）、宽度w像素和高度h像素的新窗口

CLOSE x y——关闭一个打开的窗口，其中包括（x，y）处的像素。这允许用户点击窗口上的任意位置以关闭窗口。

RESIZE x y w h——将包含（x，y）处像素的窗口尺寸设置为宽度w和高度h。窗口的左上角不移动。

MOVE x y dx dy——移动包含（x，y）处像素的窗口。移动是水平方向上的dx像素或垂直方向上的dy像素。dx和dy中最多有一个为非零。

![](https://cdn.luogu.com.cn/upload/image_hosting/3zw4uj2x.png)

图1：移动示例

ACM对MOVE命令特别自豪。正在移动的窗口可能会“撞上”另一个窗口。在这种情况下，第一个窗口将以相同的方向尽可能远地推动第二个窗口，就像这些窗口是物理对象一样。此行为可能会层叠–移动的窗口可能会遇到其他窗口，这些窗口也会根据需要被推送。图1显示了一个有三个窗口的示例，其中窗口A向右移动，推动其他两个窗口。

输入格式

第一行输入包含两个正整数x_max和y_max，即屏幕的水平和垂直尺寸，以像素为单位。每个显示器的最大分辨率为10^9（ACM正计划建造具有极高分辨率的显示器）。屏幕左上角的像素具有坐标（0,0）。下面的每一行都包含一个如上所述的命令。命令名和参数之间用一个或多个空格分隔。命令参数是满足这些条件的整数：0≤x<x_max，0≤y<y_max，1≤w，h≤10^9，|d_x|、|d_y|≤10^9。最多有256条命令。

输出格式

输出必须遵循以下示例输出中所示的格式。

按照命令在输入中出现的顺序模拟命令。如果在命令模拟过程中检测到任何错误，请显示命令编号、命令名称和下表中的第一条适当消息，并忽略模拟该命令的结果（除非另有说明）。

如果在指定位置没有包含像素的窗口，则在给定位置没有窗口（用于关闭、调整大小和移动命令）。

如果生成的窗口与另一个窗口重叠或超出屏幕边界，则窗口不适用于“打开”和“调整大小”命令。

如果命令要求移动窗口d个像素，则移动d'而不是d-对于MOVE命令，但在要求窗口移动到屏幕边界之外之前，它只能移动d'个像素。值d和d’分别是请求和移动的像素的绝对数量。在这种情况下，窗口仍会移动，但仅移动较小的距离。

模拟所有命令并显示任何错误消息后，指示仍打开的窗口数。然后，对于每个打开的窗口，按照打开的顺序显示左上角（x，y）的坐标、宽度和高度。

输入输出样例

输入 #1

320 200

OPEN 50 50 10 10

OPEN 70 55 10 10

OPEN 90 50 10 10

RESIZE 55 55 40 40

RESIZE 55 55 15 15

MOVE 55 55 40 0

CLOSE 55 55

CLOSE 110 60

MOVE 95 55 0 -100

输出 #1

Command 4: RESIZE - window does not fit

Command 7: CLOSE - no window at given position

Command 9: MOVE - moved 50 instead of 100

2 window(s):

90 0 15 15

115 50 10 10

说明/提示

时间限制：1000毫秒，内存限制：1048576 kB。

该题出自：2015年国际大学生编程大赛（ACM-ICPC）世界总决赛


---

---
title: "[ICPC 2016 WF] Branch Assignment"
layout: "post"
diff: 省选/NOI-
pid: P6918
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Branch Assignment
## 题目描述

The Innovative Consumer Products Company (ICPC) is planning to start a top-secret project. This project consists of $s$ subprojects. There will be $b \ge s$ branches of ICPC involved in this project and ICPC wants to assign each branch to one of the subprojects. In other words, the branches will form $s$ disjoint groups, with each group in charge of a subproject.

At the end of each month, each branch will send a message to every other branch in its group (a different message to each branch). ICPC has a particular protocol for its communications. Each branch $i$ has a secret key $k_ i$ known only to the branch and the ICPC headquarters. Assume branch $i$ wants to send a message to branch $j$. Branch $i$ encrypts its message with its key $k_ i$. A trusted courier picks up this message from this branch and delivers it to the ICPC headquarters. Headquarters decrypts the message with key $k_ i$ and re-encrypts it with key $k_ j$. The courier then delivers this newly encrypted message to branch $j$, which decrypts it with its own key $k_ j$. For security reasons, a courier can carry only one message at a time.

Given a road network and the locations of branches and the headquarters in this network, your task is to determine the minimum total distance that the couriers will need to travel to deliver all the end-of-month messages, over all possible assignments of branches to subprojects.
## 输入格式

The first line of input contains four integers $n$, $b$, $s$, and $r$, where $n$ ($2 \le n \le 5\, 000$) is the number of intersections, $b$ ($1 \le b \le n-1$) is the number of branches, $s$ ($1 \le s \le b$) is the number of subprojects, and $r$ ($1 \le r \le 50\, 000$) is the number of roads. The intersections are numbered from $1$ through $n$. The branches are at intersections $1$ through $b$, and the headquarters is at intersection $b + 1$. Each of the next $r$ lines contains three integers $u$, $v$, and $\ell $, indicating a one-way road from intersection $u$ to a different intersection $v$ ($1 \leq u,v \leq n$) of length $\ell $ ($0 \leq \ell \leq 10\, 000$). No ordered pair $(u,v)$ appears more than once, and from any intersection it is possible to reach every other intersection.
## 输出格式

Display the minimum total distance that the couriers will need to travel.
## 样例

### 样例输入 #1
```
5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 0
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2

```
### 样例输出 #1
```
13

```
### 样例输入 #2
```
5 4 2 10
5 2 1
2 5 1
3 5 5
4 5 10
1 5 1
2 3 1
3 2 5
2 4 5
2 1 1
3 4 2

```
### 样例输出 #2
```
24

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

题目描述

给定一个 $n$ 个点，$r$ 条边的有向强连通图，正整数 $s,b$ 满足 $1\le s\le b \le n-1$。第 $b+1$ 个点称为总部。点 $x$ 向点 $y$ 发送信息的代价是 $dis(x,b+1)+dis(b+1,y)$。  
现将点集 $\{1,2,\cdots,b\}$ 划分为 $s$ 个不相交的子集 $S_1,S_2,\cdots,S_s$。同一个子集内的点两两之间会互相发送信息。求最小化总代价。

数据范围

$2\le n \le 5000$，$1\le s\le b\le n-1$，$1\le r\le 50000$，边权非负且不大于 $10000$。


---

---
title: "[ICPC 2016 WF] Longest Rivers"
layout: "post"
diff: 省选/NOI-
pid: P6922
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Longest Rivers
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/4ul9evsl.png)

The Chao Phraya River System is the main river system of Thailand. Its six longest rivers listed by decreasing length are:

Tha Chin ($765$ km)

Nan ($740$ km)

Yom ($700$ km)

Ping ($658$ km)

Pa Sak ($513$ km)

Wang ($335$ km)

A simplified model of this river system is shown in Figure 1, where the smaller red numbers indicate the lengths of various sections of each river. The point where two or more rivers meet as they flow downstream is called a confluence. Confluences are labeled with the larger black numbers. In this model, each river either ends at a confluence or flows into the sea, which is labeled with the special confluence number $0$. When two or more rivers meet at a confluence (other than confluence $0$), the resulting merged river takes the name of one of those rivers. For example, the Ping and the Wang meet at confluence $1$ with the resulting merged river retaining the name Ping. With this naming, the Ping has length $658$ km while the Wang is only $335$ km. If instead the merged river had been named Wang, then the length of the Wang would be $688$ km while the length of the Ping would be only $305$ km.

![](https://cdn.luogu.com.cn/upload/image_hosting/n8uvzv81.png)

   Figure 1: The river system in Sample Input 1. Same-colored edges indicate a river. 

The raised awareness of this phenomenon causes bitter rivalries among the towns along the rivers. For example, the townspeople along the Wang protest that maybe with a proper naming scheme, their river could actually be the longest, or maybe the second longest (or at least not last!). To end all the guessing, your task is to validate all such claims.

The rank of a river is its position in a list of all rivers ordered by decreasing length, where the best rank is $1$ for the longest river. For each river, determine its best possible rank over all naming schemes. At any confluence, the name of a new, larger river in any naming scheme must be one of the names of the smaller rivers which join at that confluence. If two or more rivers have equal lengths in a naming scheme, all the tied rivers are considered to have the best possible ranking. For example, if one river is the longest and all other rivers are equal, those rivers all have rank $2$.
## 输入格式

The first line of input contains two integers $n$ $(1 \le n \le 500\, 000)$, which is the number of river sources in the system, and $m$ $(0 \le m \le n - 1)$, which is the number of confluences with positive labels. These confluences are numbered from $1$ to $m$.

The next $n$ lines describe the rivers. Each of these lines consists of a string, which is the name of the river at the source, and two integers $c$ $(0 \leq c \leq m)$ and $d$ $(1 \leq d \leq 10^9)$, where $c$ is the identifier of the nearest confluence downstream, and $d$ is the distance from the source to that confluence in kilometers. River names use only lowercase and uppercase letters a–z, and consist of between $1$ and $10$ characters, inclusive.

The final $m$ lines describe confluences $1$ to $m$ in a similar fashion. The $k^\text {th}$ of these lines describes the confluence with identifier $k$ and contains two integers: the identifier of the nearest confluence downstream and the distance from confluence $k$ to this confluence in kilometers.

It is guaranteed that each confluence $1$ through $m$ appears as “the nearest downstream” at least twice, confluence $0$ appears at least once, and all sources are connected to confluence $0$.
## 输出格式

Display one river per line in the same order as in the input. On that line, display the name of the river and its best possible rank.
## 样例

### 样例输入 #1
```
6 2
PaSak 0 513
Nan 2 675
Yom 2 700
Wang 1 335
Ping 1 305
ThaChin 0 765
0 353
0 65

```
### 样例输出 #1
```
PaSak 5
Nan 2
Yom 1
Wang 3
Ping 4
ThaChin 1

```
## 提示

Time limit: 9000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

有 $n$ 条河和 $m+1$ 个交汇处构成一棵以 $0$ 号点（即大海） 为根的树。

每条河有各自的名称。对于一个交汇处，从它流出的干流的名称是流入这个交汇处的各个支流的名称之一。一条河流的长度是以它为名称的河流的长度之和。对于一个可能的命名方案，一条河流的排名等于长度大于它的河流数 $+1$ 。

对于每条河，求出它在所有命名方案中，最小的排名。


---

---
title: "[ICPC 2016 WF] What Really Happened on Mars?"
layout: "post"
diff: 省选/NOI-
pid: P6928
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] What Really Happened on Mars?
## 题目描述

Real-time software in the Mars Pathfinder spacecraft suffered from an issue known as priority inversion. One technique to address this issue is to use the Priority Ceiling Protocol.

In this problem, you will simulate the execution of multiple tasks according to this protocol. The tasks share a collection of resources, each of which can be used by only one task at a time. To ensure this, resources must be locked before use and unlocked after use. Each task is defined by a start time, a unique base priority, and a sequence of instructions. Each task also has a current priority, which may change during execution. Instructions come in three types:

compute – perform a computation for one microsecond

lock $k$ – lock resource $k$ (which takes no processor time)

unlock $k$ – unlock resource $k$ (which takes no processor time)

After locking a resource, a task is said to own the resource until the task unlocks it. A task will unlock only the owned resource it most recently locked, will not lock a resource it already owns, and will complete with no owned resources.

Each resource has a fixed priority ceiling, which is the highest base priority of any task that contains an instruction to lock that resource.

There is a single processor that executes the tasks. When the processor starts, it initializes its clock to zero and then runs an infinite loop with the following steps:

  Step 1.

Identify running tasks. A task is running if its start time is less than or equal to the current processor clock and not all of its instructions have been executed.

  Step 2.

Determine the current priorities of the running tasks and which of the running tasks are blocked. A running task $T$ is blocked if the next instruction in $T$ is to lock resource $k$ and either resource $k$ is already owned or at least one other task owns a resource $\ell $ whose priority ceiling is greater than or equal to the current priority of $T$. If $T$ is blocked, it is said to be blocked by every task owning such $k$ or $\ell $. The current priority of a task $T$ is the maximum of $T$’s base priority and the current priorities of all tasks that $T$ blocks.

  Step 3.

Execute the next instruction of the non-blocked running task (if any) with the highest current priority. If there was no such task or if a compute instruction was executed, increment the processor clock by one microsecond. If a lock or unlock instruction was executed, do not increment the clock.

The Priority Ceiling Protocol defined above has the following properties:

Current priority is defined in terms of current priority and blocking, and blocking is defined in terms of current priority. While this may appear circular, there will always be a unique set of current priorities that satisfy the definitions.

All tasks will eventually complete.

There will never be a tie in step 3.
## 输入格式

The first line of the input contains two integers $t$ $(1 \leq t \leq 20)$, which is the number of tasks, and $r$ ($1 \leq r \leq 20$), which is the number of resources. This is followed by $t$ lines, where the $i^\text {th}$ of these lines describes task $i$. The description of a task begins with three integers: the task’s start time $s$ ($1 \leq s \leq 10\, 000$), its base priority $b$ ($1 \leq b \leq t$), and an integer $a$ ($1 \leq a \leq 100$). A task description is concluded by a sequence of $a$ strings describing the instructions. Each string is a letter (C or L or U) followed by an integer. The string C$n$ ($1 \leq n \leq 100$) indicates a sequence of $n$ compute instructions. The strings L$k$ and U$k$ ($1 \leq k \leq r$) indicate instructions locking and unlocking resource $k$ respectively.

No two tasks have the same base priority.
## 输出格式

For each task, display the time it completes execution, in the same order that the tasks are given in the input.
## 样例

### 样例输入 #1
```
3 1
50 2 5 C1 L1 C1 U1 C1
1 1 5 C1 L1 C100 U1 C1
70 3 1 C1

```
### 样例输出 #1
```
106
107
71

```
### 样例输入 #2
```
3 3
5 3 5 C1 L1 C1 U1 C1
3 2 9 C1 L2 C1 L3 C1 U3 C1 U2 C1
1 1 9 C1 L3 C3 L2 C1 U2 C1 U3 C1

```
### 样例输出 #2
```
8
15
16

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

你有 $t$ 个进程和 $r$ 个资源，每个进程包含其起始时间与**基础优先级**（保证两两不同），以及若干条指令。指令有以下三种：

- `compute`：进行计算，消耗 $1$ 微秒。
- `lock k`：锁定编号为 $k$ 的资源，不耗时。
- `unlock k`：解锁编号为 $k$ 的资源，不耗时。

在进程锁定资源后，这个进程就拥有了这个资源直到这个进程将它解锁。保证任意进程只会解锁最近锁定的资源，不会锁定自身拥有的资源，且在进程结束时不会拥有任何资源。

每个资源有一个固定的属性**最高优先级**，即包含锁定该资源指令的所有进程的最高**基础优先级**。

有一个处理器处理这些进程。处理器有一个时钟初始为 $0$，然后重复执行下列步骤：

1. 找出所有正在运行的进程。如果进程开始的时间不大于处理器的时钟且该进程的指令未运行完毕，那么称这个进程正在运行。

2. 决定当前所有正在运行的进程的优先级，以及哪些正在运行的进程会被阻塞。进程 $T$ 会被阻塞当且仅当：

   - 进程 $T$ 的下一条指令是锁定资源 $k$。
   - 资源 $k$ 已经被其他进程拥有，或存在另一个进程拥有某个资源 $\ell$，$\ell$ 的**最高优先级**大于 $T$ 的**当前优先级**。

   此时我们称进程 $T$ 被所有拥有资源 $k$ 或满足条件的资源 $\ell$ 的进程阻塞。定义 $T$ 的**当前优先级**为所有阻塞它的进程的**当前优先级**与它本身的**基础优先级**的最大值。

3. 执行**当前优先级**最高且没有被阻塞的进程的下一条指令。如果不存在这样的进程或者执行的指令是 `compute`，则将时钟加 $1$ 微秒。

你需要求所有进程的结束时间。可以证明所有进程一定会结束。

输入格式：

第一行两个整数 $t,r$ 表示进程和资源个数。

接下来 $t$ 行每行描述一个进程，格式如下：

- 三个整数 $s,b,a$，表示进程起始时间、基础优先级、指令条数。
- 接下来 $a$ 个字符串，每个字符串表示一条指令。字符串形如 `Cn` 表示连续 $n$ 个 `compute` 指令（**相互独立**），`Lk` 表示锁定资源 $k$，`Rk` 表示解锁资源 `k`。

输出格式：

$t$ 行每行一个整数表示进程执行完毕的时间。

数据范围：$1 \le t,r \le 20,s \le 10^4,1 \le b \le t$ 且互不相同，$a \le 100$，`Cn` 中 $n \le 100$，`Lk,Rk` 中 $1 \le k \le r$。

Translated by pokefunc (uid=188716)


---

---
title: "[ICPC 2017 WF] Airport Construction"
layout: "post"
diff: 省选/NOI-
pid: P6929
tag: ['2017', 'Special Judge', 'ICPC']
---
# [ICPC 2017 WF] Airport Construction
## 题目描述



The tropical island nation of Piconesia is famous for its beautiful beaches, lush vegetation, cocoa and coffee plantations, and wonderful weather all year round. This paradise is being considered as a future location for the World Finals of the ACM International Collegiate Programming Contest (or at the very least a vacation spot for the executive council). There is only one small problem: the island is really hard to reach.

Currently, the fastest way to reach the island takes three days from the nearest airport, and uses a combination of fishing boat, oil tanker, kayak, and submarine. To make attending the ICPC World Finals slightly easier and to jump-start the island's tourism business, Piconesia is planning to build its first airport.

Since longer landing strips can accommodate larger airplanes, Piconesia has decided to build the longest possible landing strip on their island. Unfortunately, they have been unable to determine where this landing strip should be located. Maybe you can help?

For this problem we model the boundary of Piconesia as a polygon. Given this polygon, you need to compute the length of the longest landing strip (i.e., straight line segment) that can be built on the island. The landing strip must not intersect the sea, but it may touch or run along the boundary of the island. Figure A.1 shows an example corresponding to the first sample input.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14633/1.png)

Figure A.1 : The island modeled as a polygon. The longest possible landing strip is shown as a thick line.


## 输入格式



The input starts with a line containing an integer $n (3 \le n \le 200)$ specifying the number of vertices of the polygon. This is followed by $n$ lines, each containing two integers $x$ and $y (|x|, |y| \le 10^{6})$ that give the coordinates $(x , y)$ of the vertices of the polygon in counter-clockwise order. The polygon is simple, i.e., its vertices are distinct and no two edges of the polygon intersect or touch, except that consecutive edges touch at their common vertex. In addition, no two consecutive edges are collinear.


## 输出格式



Display the length of the longest straight line segment that fits inside the polygon, with an absolute or relative error of at most $10^{−6}.$


## 样例

### 样例输入 #1
```
7
0 20
40 0
40 20
70 50
50 70
30 50
0 50

```
### 样例输出 #1
```
76.157731059

```
### 样例输入 #2
```
3
0 2017
-2017 -2017
2017 0

```
### 样例输出 #2
```
4510.149110617

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

给定一个 $n$ 边形，第 $i$ 个点为 $(x_i,y_i)$，并且保证顺时针给出。求一条在 $n$ 边形内的最长线段。

$3 \le n \le 200$，$|x|,|y| \le 10^6$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Get a Clue!"
layout: "post"
diff: 省选/NOI-
pid: P6930
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Get a Clue!
## 题目描述



Developed in the $1940s$ in the United Kingdom, the game of Cluedo is one of the most popular board games in the world. The object of the game is to determine who murdered Mr. Body, which weapon was used to murder him, and where the murder took place. The game uses a set of cards representing six persons (labeled A , $B$ , . . . , $F)$ , six weapons (labeled $G , H$ , . . . , $L)$ and nine rooms (labeled $M , N$ , . . . , $U)$ . At the start of the game, one person card, one weapon card, and one room card are selected at random and removed from the deck so no one can see them $-$ they represent the murderer, the murder weapon, and the murder location. The remaining $18$ cards are shuffled and dealt to the players, starting with player $1$ , then to her right player $2$ , and so on. Some players may end up with one more card than others. For the purposes of this problem there are four players, so the person to the right of player $4$ is player $1$ .

The rest of the game is spent searching for clues. Players take turns, starting with player $1$ and moving to the right. A turn consists of making a suggestion (consisting of a murder suspect, a weapon, and a room) and asking other players if they have any evidence that refutes the suggestion. For example, you might say to another player `I believe the murderer was person A , using weapon $L$ , in room $T$ . $`$ If the other player is holding exactly one of these cards, that player must show you (and only you) that card. If they have more than one such card, they can show you any one of them.

When making a suggestion, you must first ask the person to your right for any evidence. If they have none, you continue with the person on their right, and so on, until someone has evidence, or no one has any of the cards in your suggestion.

Many times you can gain information even if you are not the person making the suggestion. Suppose, in the above example, you are the third player and have cards A and $T$ . If someone else shows evidence to the suggester, you know that it must be weapon card $L$ . Keeping track of suggestions and who gave evidence at each turn is an important strategy when playing the game.

To win the game, you must make an accusation, where you state your final guess of the murderer, weapon, and room. After stating your accusation, you check the three cards that were set aside at the start of the game $-$ if they match your accusation, you win! Needless to say, you want to be absolutely sure of your accusation before you make it.

Here is your problem. You are player $1$ . Given a set of cards dealt to you and a history of suggestions and evidence, you need to decide how close you are to being able to make an accusation.


## 输入格式



The input starts with an integer $n (1 \le n \le 50)$ , the number of suggestions made during the game. Following this is a line containing the five cards you are dealt, all uppercase letters in the range $‘A'.$ . . $‘U'.$ The remaining $n$ lines contain one suggestion per line. Each of these lines starts with three characters representing the suggestion (in the order person, weapon, room), followed by the responses of up to three players, beginning with the player to the right of the player making the suggestion. If a player presents no evidence, a $‘-'$ (dash) is listed; otherwise an `evidence character` is listed. If the specific evidence card is seen by you (either because you provided it or you were the person receiving the evidence) then the evidence $character identifies$ that card; otherwise the evidence character is $‘ \times '.$ Note that only the last response can be an evidence character. All characters are separated by single spaces. Only valid $suggestio_n/response$ sequences appear in the input.


## 输出格式



Display a three character string identifying the murderer, the murder weapon, and the room. If the murderer can be identified, use the appropriate letter for that person; otherwise use $‘?'.$ Do the same for the murder weapon and the room.


## 样例

### 样例输入 #1
```
1
B I P C F
A G M - - -

```
### 样例输出 #1
```
AGM

```
### 样例输入 #2
```
2
A B C D H
F G M M
F H M - *

```
### 样例输出 #2
```
E??

```
### 样例输入 #3
```
3
A C M S D
B G S - G
A H S - - S
C J S *

```
### 样例输出 #3
```
???

```
## 提示

Time limit: 4 s, Memory limit: 512 MB. 


## 题目翻译

翻译者吐槽：这个 Cluedo 不就是弹丸论破的学级裁判嘛（

---

Cluedo 是一个盛行的游戏，游戏目的是找出一场谋杀案的凶手。这个游戏是一个卡牌游戏，一共有 $21$ 张卡牌，分类为：A $\sim $ F 是嫌疑人卡牌，G $\sim $ L 是凶器卡牌，M $\sim $ U 是犯罪现场卡牌，在游戏的开始，会在三种卡牌中分别抽出一张，代表真正的凶手，凶器和犯罪现场。

今天，你和你的 $3$ 个小伙伴也来玩 Cluedo 了，你们坐成一个环，你是玩家 $1$，你的小伙伴分别为玩家 $2,3,4$，按照 $1 \to 2 \to 3 \to 4 \to 1 \to 2 \cdots$ 的顺序进行游戏。每一次会从剩下的卡堆中抽出任意一张卡给玩家，直到分完为止。

分完牌后，从玩家 $1$ 开始，还是按照环的顺序，依次提出意见，格式示例为「我认为嫌疑人 A 是凶手，凶器为 L，作案现场是 T」，然后从这个玩家的右手位开始提反对意见，如果要提反对意见的玩家手里有表明意见的玩家要说的牌（因为凶手，凶器和犯罪现场都已经拿出了，所以所有玩家手里都应该没有真正的牌，有的话说明意见错误），那么他就可以成功的提反对意见。如果他不提反对意见，那么反对意见权交给他的右手位，直到有人提出或者没有反对意见。注意，如果 A 对 B 提出反对意见，那么他进行反对的那一张卡牌只有 A 和 B 能看到。

你作为类似于学级裁判中的主侦探一位，你要说明最终意见，即你对凶手，凶器和犯罪现场的最终猜测。在进行猜测后，如果你的猜测与正确结果符合，那么你就赢了。因为你有脑子，所以你只会在得到准确证据后才会进行最终猜测。

现在给定意见数 $n$，你手中的初始卡牌，以及每一次意见，求你能推理出的最终猜测。如果你无法得到完整的最终猜测，请把你尚未得到结论的地方用 $\texttt ?$ 输出。

备注：意见如下描述：

- 首先三个字符代表这个意见所提出的凶手，凶器和犯罪现场。
- 接下来一个或两个或三个字符代表反对意见情况，从他的右手位开始表示，如果这个玩家没有反对意见，那么 $\texttt -$，如果这个玩家有反对意见，且你是提出意见的人或者是进行反对的人，那么输出反驳的是哪张卡牌。如果你不是提出意见的人或者进行反对的人，那么输出 $\texttt *$。当输出了反驳情况时，就可以换行进行下一个意见的反对意见判断了。否则，一直进行到三名玩家的反对意见都判断完。

$1 \le n \le 50$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Mission Improbable"
layout: "post"
diff: 省选/NOI-
pid: P6931
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Mission Improbable
## 题目描述



It is a sunny day in spring and you are about to meet Patrick, a close friend and former partner in crime. Patrick lost most of his money betting on programming contests, so he needs to pull off another job. For this he needs your help, even though you have retired from a life of crime. You are reluctant at first, as you have no desire to return to your old criminal ways, but you figure there is no harm in listening to his plan.

There is a shipment of expensive consumer widgets in a nearby warehouse and Patrick intends to steal as much of it as he can. This entails finding a way into the building, incapacitating security guards, passing through various arrays of laser beams $-$ you know, the usual heist techniques. However, the heart of the warehouse has been equipped with a security system that Patrick cannot disable. This is where he needs your help.

The shipment is stored in large cubical crates, all of which have the same dimensions. The crates are stacked in neat piles, forming a three-dimensional grid. The security system takes pictures of the piles once per hour using three cameras: a front camera, a side camera and a top camera. The image from the front camera shows the height of the tallest pile in each column, the image from the side camera shows the height of the tallest pile in each row, and the image from the top camera shows whether or not each pile is empty. If the security system detects a change in any of the images, it sounds an alarm.

Once Patrick is inside, he will determine the heights of the piles and send them to you. Figure C.1 shows a possible layout of the grid and the view from each of the cameras.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14635/1.png)

Figure C.1 : Grid of heights and the corresponding camera views.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14635/2.png)

Figure C.2 : Possible grid of heights after the heist

Patrick wants to steal as many crates as possible. Since he cannot disable the security system, he plans to fool it by arranging the remaining crates into piles so that the next set of camera images are the same. In the above example, it is possible to steal nine crates. Figure C.2 shows one possible post-heist configuration that appears identical to the security system.

Patrick asks you to help him determine the maximum number of crates that can be stolen while leaving a configuration of crates that will fool the security system. Will you help him pull off this final job?


## 输入格式



The first line of input contains two integers $r (1 \le r \le 100)$ and $c (1 \le c \le 100)$ , the number of rows and columns in the grid, respectively. Each of the following $r$ lines contains $c$ integers, the heights (in crates) of the piles in the corresponding row. All heights are between $0$ and $10^{9}$ inclusive.


## 输出格式



Display the maximum number of crates that can be stolen without being detected.


## 样例

### 样例输入 #1
```
5 5
1 4 0 5 2
2 1 2 0 1
0 2 3 4 4
0 3 0 3 1
1 2 2 1 1

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
2 3
50 20 3
20 10 3

```
### 样例输出 #2
```
30

```
## 提示

Time limit: 1 s, Memory limit: 512 MB. 


## 题目翻译

给定一个 $r \times c$ 的平面，在上面摆有一些箱子。我们可以得到他的三视图（如下图，左边矩阵上的值为平面上每一位摆放的箱子个数，右边三个视图为正视图，俯视图，左视图）：

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14635/1.png)

你可以拿走一些箱子，和重新排列这些箱子的位置，你想知道，最多能拿走多少个箱子，使得这些箱子重新排列后正视图，俯视图，左视图不变？

比如上面这个例子，下面这种拿走 $9$ 个箱子后的重新排列方式也是可以的：

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14635/2.png)

$1 \le r,c \le 100$，平面上每一个位置的箱子个数在 $[0,10^9]$ 内。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Money for Nothing"
layout: "post"
diff: 省选/NOI-
pid: P6932
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Money for Nothing
## 题目描述



In this problem you will be solving one of the most profound challenges of humans across the world since the beginning of time $-$ how to make lots of money.

You are a middleman in the widget market. Your job is to buy widgets from widget producer companies and sell them to widget consumer companies. Each widget consumer company has an open request for one widget per day, until some end date, and a price at which it is willing to buy the widgets. On the other hand, each widget producer company has a start date at which it can start delivering widgets and a price at which it will deliver each widget.

Due to fair competition laws, you can sign a contract with only one producer company and only one consumer company. You will buy widgets from the producer company, one per day, starting on the day it can start delivering, and ending on the date specified by the consumer company. On each of those days you earn the difference between the producer's selling price and the consumer's buying price.

Your goal is to choose the consumer company and the producer company that will maximize your profits.


## 输入格式



The first line of input contains two integers $m$ and $n (1 \le m , n \le 500 000)$ denoting the number of producer and consumer companies in the market, respectively. It is followed by $m$ lines, the $i$ th of which contains two integers $p_{i}$ and $d_{i} (1 \le p_{i}, d_{i} \le 10^{9}),$ the price (in dollars) at which the $i$ th producer sells one widget and the day on which the first widget will be available from this company. Then follow $n$ lines, the $j$ th of which contains two integers $q_{j}$ and $e_{j} (1 \le q_{j}, e_{j} \le 10^{9}),$ the price (in dollars) at which the $j$ th consumer is willing to buy widgets and the day immediately after the day on which the last widget has to be delivered to this company.


## 输出格式



Display the maximum total number of dollars you can earn. If there is no way to sign contracts that gives you any profit, display $0$ .


## 样例

### 样例输入 #1
```
2 2
1 3
2 1
3 5
7 2

```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
1 2
10 10
9 11
11 9

```
### 样例输出 #2
```
0

```
## 提示

Time limit: 5 s, Memory limit: 512 MB. 


## 题目翻译

一共有 $m$ 个生产商和 $n$ 个消费商。第 $i$ 个生产商从第 $d_i$ 个时刻开始销售物品，每个物品卖 $p_i$ 元。第 $i$ 个消费商从第 $1$ 个时刻开始需要消费，他的消费欲望一直到第 $e_i-1$ 的时刻，每个物品出价 $q_i$ 元。你作为中间商，只能与一间生产商和一间消费商签订合约，可以选择在生产商那里买下一些物品，也可以选择卖向消费商，你的目的就是赚中间的差价。

你想知道最多能赚到多少差价。

$1 \le m,n \le 5\times 10^5$，$1 \le p_i,d_i,q_i,e_i \le 10^9$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Replicate Replicate Rfplicbte"
layout: "post"
diff: 省选/NOI-
pid: P6935
tag: ['2017', 'Special Judge', 'ICPC']
---
# [ICPC 2017 WF] Replicate Replicate Rfplicbte
## 题目描述



The owner of the Automatic Cellular Manufacturing corporation has just patented a new process for the mass production of identical parts. Her approach uses a two-dimensional lattice of two-state cells, each of which is either `empty` or `filled. ` The exact details are, of course, proprietary.

Initially, a set of cells in the lattice is filled with a copy of the part that is to be reproduced. In a sequence of discrete steps, each cell in the lattice simultaneously updates its state by examining its own state and those of its eight surrounding neighbors. If an odd number of these nine cells are filled, the cell's state in the next time step will be filled, otherwise it will be empty. Figure G.1 shows several steps in the replication process for a simple pattern consisting of three filled cells.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14639/1.png)

Figure G.1 : The replication process.

However, a bug has crept into the process. After each update step, one cell in the lattice might spontaneously flip its state. For instance, Figure G.2 shows what might happen if a cell flipped its state after the first time step and another flipped its state after the third time step.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14639/2.png)

Figure G.2 : Errors in the replication process. This figure corresponds to Sample Input $1$ .

Unfortunately, the original patterns were lost, and only the (possibly corrupted) results of the replication remain. Can you write a program to determine a smallest possible nonempty initial pattern that could have resulted in a given final pattern?


## 输入格式



The first line of input contains two integers $w (1 \le w \le 300)$ and $h (1 \le h \le 300)$ , where $w$ and $h$ are the width and height of the bounding box of the final pattern. Following that are $h$ lines, each containing $w$ characters, giving the final pattern. Each character is either $‘. '$ (representing an empty cell) or $‘#'$ (representing a filled cell). There is at least one filled cell in the first row, in the last row, in the first column, and in the last column.


## 输出格式



Display a minimum-size nonempty pattern that could have resulted in the given pattern, assuming that at each stage of the replication process at most one cell spontaneously changed state. The size of a pattern is the area of its bounding box. If there is more than one possible minimum-size nonempty starting pattern, any one will be accepted. Use the character $‘. '$ for empty cells and $‘#'$ for filled cells. Use the minimum number of rows and columns needed to display the pattern.


## 样例

### 样例输入 #1
```
10 10
.#...#...#
##..##..##
##.#.##...
##.#.##...
.#...#####
...##..#.#
......###.
##.#.##...
#..#..#..#
##..##..##

```
### 样例输出 #1
```
.#
##

```
### 样例输入 #2
```
8 8
##..#.##
#.####.#
.#.#.#..
.##.#.##
.#.#.#..
.##.#.##
#..#.###
##.#.##.

```
### 样例输出 #2
```
####
#..#
#.##
###.

```
### 样例输入 #3
```
5 4
#....
..###
..###
..###

```
### 样例输出 #3
```
#

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

定义一个黑白复制过程，每一次枚举所有格子初始时自身和周围 $8$ 个格子这 $9$ 个格子的黑白情况，如果有奇数个位置为黑，那么这个格子变为黑，否则变为白。但不幸的是，复制过程有 bug，每一次进行复制后，都会有任意一个格子从黑变为白，或者从白变为黑，当然也可以不变。现在给定一份包含 bug 的复制最终结果，包含 $w$ 行 $h$ 列，求行列数最小的初始黑白格子，使得能通过复制过程和 bug 变为最终结果。

$\texttt \#$ 为黑，$\texttt .$ 为白。

注意，如果有多余的白色格子请省掉，比如左边这个黑白格子情况可以变为右边的：

```
...........   .....##..#
......##..#   #........#
.#........#   #..#...#..
.#..#...#..   .#.......#
..#.......#
...........
...........
```

$1 \le w,h \le 300$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Tarot Sham Boast"
layout: "post"
diff: 省选/NOI-
pid: P6939
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Tarot Sham Boast
## 题目描述



Curse your rival! Every year at the annual Rock Paper Scissors tournament, you have made it to the final match. (Your Rock technique is unmatched, and your Paper cuts to the bone! Your Scissors need a little work, though. ) But every year, he defeats you, even though his moves appear entirely random! And he claims to the press that he simply cannot be beaten. What is his secret?

Fortunately, you think you have figured it out. This year, just before the tournament, you caught him visiting various shamans around town. Aha! He is using the supernatural against you! You figured two can play at this game. So you went and visited a set of fortune-tellers, who have each used a Tarot deck to predict a sequence that your rival will end up using, sometime during the match.

However, your initial excitement has passed, and now you are feeling a little silly. This cannot possibly work, right? In the end it feels like you have paid good money for a fraudulent, random set of predictions. Oh well; you might as well keep an eye out for some of them during the match. But which predictions will you use?

In the final match, you and your rival will play $n$ rounds of Rock Paper Scissors. In each round, your rival and you will both choose one of the three options (Rock, Paper, or Scissors). Based on your selections, a winner of the round will be determined (exactly how is irrelevant to this problem).

Given the length of the final match and the various predictions, sort them in order of how likely they are to appear sometime during the match as a contiguous sequence of options chosen by your rival, assuming he is choosing his symbol in each round independently and uniformly at random.


## 输入格式



The first line of input contains two integers $n (1 \le n \le 10^{6}),$ the number of rounds in the final match, and $s (1 \le s \le 10)$ , the number of sequences. The remaining $s$ lines each describe a prediction, consisting of a string of characters $‘R', ‘P',$ and $‘S'.$ All predictions have the same length, which is between $1$ and $n$ characters long, inclusive, and no longer than $10^{5}.$


## 输出格式



Display all of the predictions, sorted by decreasing likelihood of appearance sometime during the final match. In the case of tied predictions, display them in the same order as in the input.


## 样例

### 样例输入 #1
```
3 4
PP
RR
PS
SS

```
### 样例输出 #1
```
PS
PP
RR
SS

```
### 样例输入 #2
```
20 3
PRSPS
SSSSS
PPSPP

```
### 样例输出 #2
```
PRSPS
PPSPP
SSSSS

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

定义某字符串  $s$ 的出现概率为：随机敲  $n$ 个 `R,P,S`， $s$ 作为其子串出现的概率。

给出  $s$ 个长度为  $l$ 的只含 `R,P,S` 的字符串，请你按这  $l$ 个字符串的出现概率从大到小排序。若概率相等则按输入顺序排序。

 $n\le 10^6,s\le 10,l\le 10^5$。


---

---
title: "[ICPC 2018 WF] Gem Island"
layout: "post"
diff: 省选/NOI-
pid: P6944
tag: ['2018', 'Special Judge', 'ICPC']
---
# [ICPC 2018 WF] Gem Island
## 题目描述



Gem Island is a tiny island in the middle of the Pacific Ocean. Until recently, it was known as one of the poorest, but also most peaceful, places on Earth. Today, it is neither poor nor peaceful. What happened?

One sunny morning, not too long ago, all inhabitants of Gem Island woke up to a surprise. That morning, each of them suddenly held one sparkling gem in their hand. The gems had magically appeared overnight. This was cause for much rejoicing $-$ everybody was suddenly rich, they could finally afford all the things they had ever dreamed of, and the name of their island made so much more sense now.

The next morning, one of the inhabitants woke up to another surprise $-$ her gem had magically split into two gems! The same thing happened on each of the following nights, when exactly one of the gems (apparently uniformly at random among all the gems on the island) would split into two.

After a while, the inhabitants of Gem Island possessed a widely varying number of gems. Some had a lot and many had only a few. How come some inhabitants had more gems than others? Did they cheat, were they just lucky, or was something else at work?

The island elders have asked for your help. They want you to determine if the uneven distribution of gems is explained by pure chance. If so, that would greatly reduce tensions on the island.

The island has $n$ inhabitants. You are to determine the gem distribution after $d$ nights of gem splitting. In particular, you are interested in the expected number of gems collectively held by the $r$ people with the largest numbers of gems. More formally, suppose that after $d$ nights the numbers of gems held by the $n$ inhabitants are listed in non-increasing order as $a_{1} \ge a_{2} \ge $ . . . $ \ge a_{n}.$ What is the expected value of $a_{1} + · · · + a_{r}?$


## 输入格式



The input consists of a single line containing the three integers $n , d$ , and $r (1 \le n , d \le 500 , 1 \le r \le n)$ , as described in the problem statement above.


## 输出格式



Display the expected number of gems that the top $r$ inhabitants hold after $d$ nights, with an absolute or relative error of at most $10^{−6}.$


## 样例

### 样例输入 #1
```
2 3 1

```
### 样例输出 #1
```
3.5

```
### 样例输入 #2
```
3 3 2

```
### 样例输出 #2
```
4.9

```
### 样例输入 #3
```
5 10 3

```
### 样例输出 #3
```
12.2567433

```
## 提示

Time limit: 3 s, Memory limit: 1024 MB. 


## 题目翻译

有 $n$ 个人，最开始每个人手中有 $1$ 颗绿宝石，每天晚上，会随机选一个绿宝石分裂为两个。

求 $d$ 个晚上后绿宝石数量最多的 $r$ 个人的绿宝石数和的期望值。

$1 \le n,d \le 500$，$1 \le r\le n$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2018 WF] Getting a Jump on Crime"
layout: "post"
diff: 省选/NOI-
pid: P6945
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Getting a Jump on Crime
## 题目描述



Your friend Robin is a superhero. When you first found out about this, you figured `everybody needs a hobby, and this seems more exciting than stamp collecting,` but now you are really thankful that somebody is doing something about the crime in your hometown.

Every night, Robin patrols the city by jumping from roof to roof and watching what goes on below. Naturally, superheroes need to respond to crises immediately, so Robin asked you for help in figuring out how to get around your hometown quickly.

Your hometown is built on a square grid, where each block is $w \times w$ meters. Each block is filled by a single building. The buildings may have different heights (see Figure E.1) . To get from one building to another (not necessarily adjacent) building, Robin makes a single jump from the center of the roof of the first building to the center of the roof of the second building. Robin cannot change direction while in the air, but can choose the angle at which to lift off.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15693/1.png)

Figure E.1 : Cross-section of buildings corresponding to the first sample input. Buildings are shown in black, and the jump from the roof at $(1 , 1)$ to the roof at $(4 , 1)$ is shown with a green line.

Of course, Robin only wants to perform jumps without colliding with any buildings. Such collisions do little damage to a superhero, but building owners tend to get irritated when someone crashes through their windows. You explain the physics to Robin: `All your jumps are done with the same initial velocity $v$ , which has a horizontal component $v_{d}$ towards the destination and vertical component $v_{h}$ upwards, so $v_{d}^{2} + v_{h}^{2} = v^{2}$ . As you travel, your horizontal velocity stays constant $(v_{d}(t) = v_{d}),$ but your vertical velocity is affected by gravity $(v_{h}(t) = v_{h} − t · g)$ , where $g = 9$ . $80665 m/s^{2}$ in your hometown. Naturally, your cape allows you to ignore the effects of air resistance. This allows you to determine your flight path and $ \cdots `$ at which point you notice that Robin has nodded off $-$ less math, more super-heroing!

So it falls to you: given a layout of the city and the location of Robin's secret hideout, you need to determine which building roofs Robin can reach, and the minimum number of jumps it takes to get to each roof.

Note that if Robin's jump passes over the corner of a building (where four buildings meet), then the jump needs to be higher than all four adjacent buildings.

$ $


## 输入格式



The input starts with a line containing six integers $d_{x}, d_{y}, w , v , ℓ_{x}, ℓ_{y}.$ These represent the size $d_{x} \times d_{y}$ of the city grid $(1 \le d_{x}, d_{y} \le 20)$ in blocks, the width of each building $(1 \le w \le 10^{3})$ in meters, Robin's takeoff velocity $(1 \le v \le 10^{3})$ in meters per second, and the coordinates $(ℓ_{x}, ℓ_{y})$ of Robin's secret hideout $(1 \le ℓ_{x} \le d_{x}, 1 \le ℓ_{y} \le d_{y}).$

The first line is followed by a description of the heights of the buildings in the city grid. The description consists of $d_{y}$ lines, each containing $d_{x}$ non-negative integers. The $j^{th}$ line contains the heights for buildings $(1 , j),(2 , j)$ , . . . $,(d_{x}, j)$ . All heights are given in meters and are at most $10^{3}.$


## 输出格式



Display the minimum number of jumps Robin needs to get from the secret hideout to the roof of each building. If there is no way to reach a building's roof, display $X$ instead of the number of jumps. Display the buildings in the same order as given in the input file, split into $d_{y}$ lines, each containing $d_{x}$ values.

You may assume that changing the height of any building by up to $10^{−6}$ would not change the answers.


## 样例

### 样例输入 #1
```
4 1 100 55 1 1
10 40 60 10

```
### 样例输出 #1
```
0 1 1 1

```
### 样例输入 #2
```
4 4 100 55 1 1
0 10 20 30
10 20 30 40
20 30 200 50
30 40 50 60

```
### 样例输出 #2
```
0 1 1 2
1 1 1 2
1 1 X 2
2 2 2 3

```
## 提示

Time limit: 2 s, Memory limit: 1024 MB. 


## 题目翻译

## 题目描述
你的朋友罗宾（Robin）是一位超级英雄。当你第一次发现这个事时，你认为“每个人都需要有爱好，这个看起来比收集邮票有意思多了”，但是现在你十分感谢那些在你的家乡胡作非为的人。

每个晚上， 罗宾（Robin）用在房顶上跳跃的方式巡逻整座城市，并且看下面发生了什么。自然，超级英雄需要立即应对危机，所以罗宾（Robin）寻求你的帮助，帮他找出如何迅速走遍你的家乡。

你的家乡建立在一个方形的格子上，其中每个区块有 $w\times w$ 米。每个区块是一个独立的建筑，建筑有可能有不同的高度,为了从一个建筑到另一个（不一定相邻的）建筑，罗宾（Robin）从第一个房屋屋顶的中间跳到第二个房屋屋顶的中间。不能在空中改变方向，但可以选择起飞的角度。

当然，罗宾（Robin）不想撞到任何一个建筑。一些碰撞很难对超级英雄造成伤害，但是当有人击穿房屋主人的窗户时，他们容易感到生气。你向罗宾（Robin）解释物理学：“你的每次跳都有一个初速度$v$，可以被分解成一个向前的水平分力$v_d$和一个向上的竖直分力$v_h$，且$v_{d}^{2} + v_{h}^{2} = v^{2}$.当你行动时，你的水平分力保持不变$(v_{dt} = v_{d}),$，但是竖直分力受到重力的影响$(v_{h}(t) = v_{h} − t · g)$，设在你的家乡重力加速度$g=9.80665$。自然，你的斗篷可以让你忽略空气阻力的影响。这可以让你确定你的飞行路线和……”这是你注意到罗宾（Robin）已经睡着了-少一点数学，多一点超级英雄！

所以现在轮到你了：已经给出城市的布局和罗宾（Robin）秘密藏身处的位置，你需要确定罗宾（Robin）能到达哪些屋顶并给出最少跳跃次数。

请注意，如果罗宾（Robin）的跳跃经过一栋建筑的角落（四栋建筑交汇的地方），那么跳跃需要比所有四栋相邻建筑都高。

## 输入格式
输入的第一行包含六个整数$d_x$,$d_y$,$w$,$v$,$l_x$,$l_x$.这些代表了 $d_x\times d_y$ 的城市面积（单位：区块）$(1 \le d_{x}, d_{y} \le 20)$，每座建筑的宽度$(1 \le w \le 10^{3})$，罗宾（Robin）的起跳速度$(1 \le v \le 10^{3})$（单位：米每秒），和罗宾（Robin）藏身处的坐标$(1 \le ℓ_{x} \le d_{x}, 1 \le ℓ_{y} \le d_{y}).$。

第一行后面是对城市网格中建筑高度的描述。描述由$d_y$行组成，每个行包含$d_{x}$个非负整数。第j行包含建筑物$(1 , j),(2 , j)$ , . . . $,(d_{x}, j)$ 的高度（单位：米）。高度最高不超过$10^3$米。

## 输出格式
输出罗宾从秘密藏身处跳到每栋建筑屋顶所需的最小跳跃次数。如果无法到达建筑物的屋顶，则显示$X$而不是跳跃次数。按输入文件中给定的顺序显示建筑，分为$d_{y}$行，每行包含$d_{x}$个值。


---

---
title: "[ICPC 2018 WF] Triangles"
layout: "post"
diff: 省选/NOI-
pid: P6949
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Triangles
## 题目描述



For your trip to Beijing, you have brought plenty of puzzle books, many of them containing challenges like the following: how many triangles can be found in Figure I.1 ?

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15697/1.png)

Figure I.1 : Illustration of Sample Input $2$ .

While these puzzles keep your interest for a while, you quickly get bored with them and instead start thinking about how you might solve them algorithmically. Who knows, maybe a problem like that will actually be used in this year's contest. Well, guess what? Today is your lucky day!


## 输入格式



The first line of input contains two integers $r$ and $c (1 \le r \le 3 000 , 1 \le c \le 6 000)$ , specifying the picture size, where $r$ is the number of rows of vertices and $c$ is the number of columns. Following this are 2r $− 1$ lines, each of them having at most 2c $− 1$ characters. Odd lines contain grid vertices (represented as lowercase $x$ characters) and zero or more horizontal edges, while even lines contain zero or more diagonal edges. Specifically, picture lines with numbers 4k $+ 1$ have vertices in positions $1 , 5 , 9 , 13$ , . . . while lines with numbers 4k $+ 3$ have vertices in positions $3 , 7 , 11 , 15$ , . . . . All possible vertices are represented in the input (for example, see how Figure I.1 is represented in Sample Input $2$) . Horizontal edges connecting neighboring vertices are represented by three dashes. Diagonal edges are represented by a single forward slash $(‘/')$ or backslash $(‘\')$ character. The edge characters will be placed exactly between the corresponding vertices. All other characters will be space characters. Note that if any input line could contain trailing whitespace, that whitespace may be omitted.


## 输出格式



Display the number of triangles (of any size) formed by grid edges in the input picture.


## 样例

### 样例输入 #1
```
3 3
x---x
 \ /
  x
 / \
x   x

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
4 10
x   x---x---x   x
     \ /   / \
  x   x---x   x   x
     / \ / \   \
x   x---x---x---x
   /   / \   \ / \
  x---x---x---x---x

```
### 样例输出 #2
```
12

```
## 提示

Time limit: 6 s, Memory limit: 1024 MB. 


## 题目翻译

**简要题意：** 输入 $r$ 行顶点，每行有 $c$ 列，顶点用 $x$ 表示，每个顶点用水平边（`-`）和对角边（用 `/` 和 `\` 表示）**精确连接**。总共 $2 r - 1$ 行，每行最多有 $2 c - 1$ 个字符，除上述字符外均为空白字符；行末可能存在可忽略的空格。你需要输出所输入的图中由网格边构成了多少个三角形（无论大小）。配图为样例 $2$。

对于所有数据，$1 \le r \le 3000$，$1 \le c \le 6000$。


---

---
title: "[NEERC 2017] Archery Tournament"
layout: "post"
diff: 省选/NOI-
pid: P6952
tag: ['2017', 'ICPC']
---
# [NEERC 2017] Archery Tournament
## 题目描述



You were invited to the annual archery tournament. You are going to compete against the best archers from all of the Northern Eurasia. This year, a new type of competition is introduced, where a shooting range is dynamic and new targets might appear at any second.

As the shooting range is far enough from you, it can be represented as a 2D plane, where $y = 0$ is the ground level. There are some targets in a shape of a circle, and all the targets are standing on the ground. That means, if a target's center is $(x , y) (y > 0)$ , then its radius is equal to $y$ , so that it touches the line $y = 0$ . No two targets simultaneously present at the range at any given time intersect (but they may touch).

Initially, the shooting range is empty. Your participation in this competition can be described as $n$ events: either a new target appears at the range, or you shoot an arrow at some point at the range. To hit a target, you must shoot strictly inside the circle (hitting the border does not count). If you shoot and hit some target, then the target is removed from the range and you are awarded one point.


## 输入格式



The first line of the input contains integer $n (1 \le n \le 2·10^{5}).$ Next $n$ lines describe the events happening at the tournament. The i-th line contains three integers $t_{i}, x_{i},$ and $y_{i} (t_{i} = 1 , 2$ ; $−10^{9} \le x_{i}, y_{i} \le 10^{9}$ ; $y_{i} > 0)$ .

If $t_{i} = 1$ , then a new target with center $(x_{i}, y_{i})$ and radius $y_{i}$ appears at the range.

If $t_{i} = 2$ , then you perform a shot, which hits the range at $(x_{i}, y_{i}).$


## 输出格式



For each of your shots, output a separate line with the single integer. If the shot did not hit any target, print `-1`. If the shot hit a target, print the number of event when that target was added to the range. Events are numbered starting from $1$ .


## 样例

### 样例输入 #1
```
8
1 0 12
2 -11 22
1 24 10
1 12 3
2 12 12
2 16 14
1 28 15
2 3 6

```
### 样例输出 #1
```
-1
-1
3
1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

给出一些圆，这些圆圆心在 $x$ 轴上方，且与 $x$ 轴相切，任意时刻，不存在图上的圆相交，给出两种操作：增加一个圆；向图中发送一颗子弹，如果击中某个圆，输出该圆编号并且删掉这个圆。如果未击中，则输出 `-1`。


---

---
title: "[NEERC 2017] The Final Level"
layout: "post"
diff: 省选/NOI-
pid: P6957
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NEERC 2017] The Final Level
## 题目描述



Fiora is a game designer. Now she is designing the final level for her new game.

A level for this game is a labyrinth on a rectangular grid with lots of enemies. Player starts her game at the square $(0 , 0)$ and her purpose is to get to the square $(a , b)$ . Fiora has lots of ideas on how to put enemies, but she does not like designing labyrinths. She needs your help here.

Fiora is drawing levels in a special level editor which supports one basic block to design a labyrinth. This block is an L-shaped corner, consisting of two perpendicular rectangles $1 \times n$ squares in size intersecting at $1 \times 1$ square. It is possible to rotate this block in four ways. Blocks cannot intersect, but they can touch each other. Player can move through all the squares lying in any block. She can move between two squares if they are sharing a side, even if they are in different blocks.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15288/1.png)

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15288/2.png)

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15288/3.png)

Blocks with $n = 3$

The first example

The second example

Fiora wants to design the final level with the minimal possible number of blocks. Of course, it should be possible to move from square $(0 , 0)$ to square $(a , b)$ .


## 输入格式



The first line of the input consists of a single integer $m (1 \le m \le 100)$ -- the number of test cases. It is followed by $m$ test cases. Each test case is on a separate line and consists of three integers a , $b$ , and $n (−10^{8} \le $ a , $b \le 10^{8}; 2 \le n \le 10^{8})$ -- a is the coordinate of the final point along the horizontal axis, $b$ is the coordinate of the final point along the vertical axis, and $n$ is the size of the block. The final point is not same as the starting one (either a $≠ 0$ or $b ≠ 0)$ .


## 输出格式



For each test case, in the first line print the minimal number $k$ of blocks you need. In the following $k$ lines print description of these blocks. Each L-shaped corner block is described by coordinates of two cells. Print coordinates of the end of its vertical rectangle, followed by coordinates of the end of its horizontal rectangle. Specify the coordinates of the ends that are opposite to the intersection of the rectangles. Note that the order of cells in the block description matters, since a change of the order results in a reflected block. Coordinates of each end should be printed with the coordinate along the horizontal axis first, followed by the coordinate along the vertical axis.

All coordinates in the output should not exceed $10^{9}$ by absolute value.

It is guaranteed that the total number of blocks in the correct output does not exceed $10^{5}$ for all test cases combined.


## 样例

### 样例输入 #1
```
2
2 3 2
4 -1 3

```
### 样例输出 #1
```
2
1 1 0 0
1 2 2 3
2
0 0 2 -2
3 -3 5 -1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

用长度为 $n$ 的 L 型方块摆在二维网格平面上，仅通过方块从 $(0,0)$ 走到 $(a,b)$。

### 输入格式

第一行一个正整数 $m$ ，下面 $m$ 行每行 $3$ 个正整数 $a, b, n$。

### 输出格式

对于每组数据，输出最小 L 型块数 $k$，下面 $k$ 行每行按先横坐标后纵坐标的顺序输出每个 L 型块两端的坐标。

### 数据范围

对于 $100\%$ 的数据，$1 \le m \le 100, -10^8 \le a, b  \le 10^8, 2 \le n \le 10^8$。


---

---
title: "[NEERC 2017] The Great Wall"
layout: "post"
diff: 省选/NOI-
pid: P6958
tag: ['2017', 'ICPC']
---
# [NEERC 2017] The Great Wall
## 题目描述



Recently you had become an emperor of a small country of Sinai. You had decided to build a big wall at the border to save your country from barbarian raids. You had contacted `W Corp`, the only company in the world that builds non-penetrable walls.

`W Corp` builds each wall using the same pattern. The length of the wall is $n$ meters. Each one-meter piece of the wall is numbered by an integer from $1$ to $n$ along its length and may have a different height. The height pattern is based on three fixed arrays a , $b$ , and $c$ of $n$ elements each, such that $a_{i} < b_{i} < c_{i}$ for all $1 \le i \le n$ , and an integer $r (1 \le r < n)$ . These arrays and $r$ are the same for any wall that is built by `W Corp`.

The choice of the specific wall design is determined by two distinct integers $x$ and $y (1 \le x < y \le n−r+1)$ in the following way. Take two ranges of integers: [x , $x+r−1]$ and [y , $y+r−1]$ (these ranges are inclusive of their ends). Then the height of the wall at one meter piece $i$ for all $1 \le i \le n$ is equal to:

$a_{i}$ if $i$ does not belong to any of the chosen ranges;

$b_{i}$ if $i$ belongs to exactly one chosen range;

$c_{i}$ if $i$ belongs to both chosen ranges.

A strength of a wall is defined as the sum of all heights of its $n$ one meter pieces.

The arrays a , $b , c$ , and an integer $r$ are the same for any wall built by `W Corp`, so the company provides a price list with all the possible wall designs, sorted in non-decreasing order of their strength. You choose the k-th wall design from the list. The task is to find the strength of the chosen wall.


## 输入格式



The first line of the input contains three integers $n , r$ and $k (2 \le n \le 30 000 , 1 \le r < n , 1 \le k \le (n−r)(n−r+1)/2)$ -- the length of the wall, the length of the segments to choose, and the position of the wall in the price list.

The second line of the input contains the elements of the array a $(1 \le a_{i} \le 10^{6}).$

The third line of the input contains the elements of the array $b (a_{i} < b_{i} \le 10^{6}).$

The fourth line of the input contains the elements of the array $c (b_{i} < c_{i} \le 10^{6}).$


## 输出格式



Print one integer -- the strength of the k-th wall from `W Corp` price list.


## 样例

### 样例输入 #1
```
4 2 1
1 2 3 4
3 3 5 5
7 7 7 7

```
### 样例输出 #1
```
16

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

最近你成为了西奈一个小国家的皇帝。你决定在边界建造一座长城保护你的国家不被野蛮人抢劫。你联系了“W Corp”——世界上唯一的建造坚不可摧的墙的公司。

“W Corp”用相同的格式建造所有墙。墙的长度是 $n$ 米，每一米墙按顺序从 $1$ 到 $n$ 编号，它们可能有不同的高度。高度的格式取决于三个固定的数组 $a,b,c$，它们各有 $n$ 个元素，对于任意 $1\le i\le n$ 满足 $a_i < b_i < c_i$，还有一个整数 $r\ (1\le r < n)$。三个数组和 $r$ 对于“W Corp”建造的任何墙都是相同的。

按照如下方式，具体的墙体设计的选择取决于两个不同的整数 $x,y\ (1\le x < y\le n-r+1)$。取两个整数区间：$[x,x+r-1]$ 和 $[y,y+r-1]$（区间包括端点）。那么第 $i$ 米墙的高度是：

- $a_i$，当 $i$ 不属于这两个区间
- $b_i$，当 $i$ 属于这两个区间中的恰好一个
- $c_i$，当 $i$ 属于这两个区间中的两个

墙的**强度**定义为每一米墙高度的和。

在“W Corp”建造的所有墙中，数组 $a,b,c$ 和整数 $r$ 都是固定的。公司提供了一份所有可能的墙体设计的列表，按照强度单调不减排序。你选择了其中第 $k$ 种墙体设计。你的任务是，求出你选择的墙的强度。

### 输入格式

第一行包括三个整数 $n,r,k\ (2\le n\le 30000,\ 1\le r < n,\ 1\le k\le \frac{(n-r)(n-r+1)}{2}\ \ )$，分别代表墙的长度，取的区间的长度，你的选择在列表中的位置。

第二行包括了数组 $a$ 的元素，$1\le a_i\le 10^6$。

第三行包括了数组 $b$ 的元素，$1\le b_i\le 10^6$。

第四行包括了数组 $c$ 的元素，$1\le c_i\le 10^6$。

### 输出格式

输出一个整数，“W Corp”的列表中第 $k$ 种墙的强度

### 样例解释

在样例中，能建造出的不同的墙有三种：

- 选择 $x=1,y=2$，墙的高度是 $[3,7,5,4]$，强度是 $19$。
- 选择 $x=1,y=3$，墙的高度是 $[3,3,5,5]$，强度是 $16$。
- 选择 $x=2,y=3$，墙的高度是 $[1,3,7,5]$，强度是 $16$。


---

---
title: "[NEERC 2017] Interactive Sort"
layout: "post"
diff: 省选/NOI-
pid: P6960
tag: ['2017', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2017] Interactive Sort
## 题目背景

这是一道 IO 交互题。
## 题目描述

Ivan wants to play a game with you. He took all integers from $1$ to $n$ inclusive, shuffled them and then put all even numbers into array $e$ and all odd numbers into array $o$ .

Your task is to find arrays $e$ and $o$ .

You can ask Ivan questions of certain kind. Each question consists of two integers $i$ and $j$ . For each question Ivan says whether $e[i] < o[j]$ or not.

You can ask at most $300 000$ questions.

# Interaction Protocol

First, the testing system writes the integer $n (1 \le n \le 10 000)$ -- the number of integers Ivan used.

Your solution shall print requests of two types:

• “? i j”. $1 \le i \le ⌊n/2⌋, 1 \le j \le ⌈n/2⌉$. The testing system responds with the symbol $“<”$ if $e[i] < o[j]$ or with the symbol $“>”$ otherwise.

• “!\ $e_1\ e_2\ \cdots e_{⌊n/2⌋}\ o_1\ o_2 \cdots o_{⌈n/2⌉}$” tells the values of $e$ and $o$ that your program has determined.

Don't forget to flush the output after each request!

Your solution must issue exactly one request of the second type, which must be the last request, and thesolution must terminate gracefully after issuing it.

Your solution is allowed to issue at most $300 000$ requests of the first type.

For each test case the number $n$ is fixed and the numbers are shuffled using Java built-in shuffle functionwith fixed seed.



## 样例

### 样例输入 #1
```
5
>
>
<
>
<
<

```
### 样例输出 #1
```
? 1 1
? 1 2
? 1 3
? 2 1
? 2 2
? 2 3
! 4 2 1 3 5
```
## 题目翻译

有一个长度为 $n(n\le 10000)$ 的排列，所有奇数组成的序列设为 $o$，所有偶数组成的序列设为 $e$。

你可以进行不超过 $300000$ 次询问 `? i j`，每次交互库会返回一个 `<` 或 `>` 表示 $e_i$ 和 $o_j$ 的大小关系，最后你需要求出 $e,o$ 并输出，格式为 `! e o`。

保证数据随机。


---

---
title: "[NEERC 2017] Journey from Petersburg to Moscow"
layout: "post"
diff: 省选/NOI-
pid: P6961
tag: ['2017', 'ICPC']
---
# [NEERC 2017] Journey from Petersburg to Moscow
## 题目描述



To conduct The World Programming Cup $2112$ a network of wonderful toll roads was build in European part of Russia. This network consists of $m$ bidirectional roads that connect $n$ cities. Each road connects exactly two distinct cities, no two roads connect the same pair of cities, and it is possible to travel from any city to any other city using only this road network. Moreover, to ease the process of charging, no two roads intersect outside of the cities.

Each road is assigned some individual positive cost. Normally, if a driver makes a trip using some of these toll roads, at the end of his journey he would be charged the total cost equal to the sum of individual costs of all roads he has used. To increase the popularity of car travels between two capitals, the operator company Radishchev Inc introduced a special offer: make a journey from Saint Petersburg to Moscow and pay for only $k$ most expensive roads along your path.

Formally, let some path consists of $l$ roads. Denote as $c_{1}$ the cost of the most expensive road along this path, as $c_{2}$ the second most expensive and so on. Thus, we have a sequence $c_{1} \ge c_{2} \ge c_{3} \ge $ . . . $ \ge c_{l}$ of individual costs of all roads along the chosen path. If $l \le k$ , then the path is too short and the driver pays the sum of all individual costs as usual, i.e . $Σ^{l}_{i=1}c_{i}.$ If $l > k$ , then the driver only pays for $k$ most expensive roads, that is $Σ^{k}_{i=1}c_{i}.$

As the chief analyst of Radishchev Inc you were assigned a task to compute the cheapest possible journey from Saint Petersburg to Moscow.


## 输入格式



The first line of the input contains three integers $n , m$ and $k (2 \le n \le 3000 , 1 \le m \le 3000 , 1 \le k < n)$ -- the number of cities, the number of roads in the road network, and the maximum number of roads that one should pay for in a single journey.

Next $m$ lines contain description of roads. Each road description contains three integers $u_{i}, v_{i},$ and $w_{i} (1 \le u_{i}, v_{i} \le n , u_{i} ≠ v_{i}, 1 \le w_{i} \le 10^{9})$ -- the i-th bidirectional road that connects cities $u_{i}$ and $v_{i}$ with the cost of $w_{i}$ for any direction. It is guaranteed that there is at most one road between each pair of cities and it is possible to get from any city to any other city using only these roads.


## 输出格式



Print one integer equal to the minimum possible cost of travel from the city number $1$ (Saint Petersburg) to the city number $n (Moscow).$


## 样例

### 样例输入 #1
```
6 7 2
1 2 6
2 3 1
2 4 3
2 5 5
3 6 10
4 6 9
5 6 8

```
### 样例输出 #1
```
14

```
### 样例输入 #2
```
5 5 3
2 1 1
3 2 1
4 3 1
4 5 1
1 5 2

```
### 样例输出 #2
```
2

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

有 $n$ 座城市 $m$ 条道路，每条道路连接两座城市，每条道路都需要过路费。

$\mathsf{\color{black}{K}\color{red}{arry5307}}$ 想从城市 $1$ 出发前往城市 $n$。根据相关法律法规，对于一条经过 $c$ 条边的路径，$\mathsf{\color{black}{K}\color{red}{arry5307}}$ 只需要支付路径上前 $k$ 大的过路费（当 $c<k$ 时需要支付路径上全部的过路费）。

现在 $\mathsf{\color{black}{K}\color{red}{arry5307}}$ 想要求出从 $1$ 到达 $n$ 的最小花费。因为 $\mathsf{\color{black}{K}\color{red}{arry5307}}$ 忙着写神仙题，所以这个任务交给了你。

$2\leq n\leq 3000,1\leq m\leq 3000,1\leq k<n$。


---

---
title: "[NEERC 2017] Laminar Family"
layout: "post"
diff: 省选/NOI-
pid: P6963
tag: ['2017', 'ICPC']
---
# [NEERC 2017] Laminar Family
## 题目描述



While studying combinatorial optimization, Lucas came across the notion of `laminar set family`. A subset family $F$ of some set $Ω$ is called laminar if and only if it does not contain an empty set and for any two distinct sets A , $B ∈ F$ it is correct that either $A ⊂ B$ or $B ⊂ A$ or $A ∩ B = ∅$.

As an experienced problem setter Lucas always tries to apply each new piece of knowledge he gets as an idea for a programming competition problem. An area of his scientific interests covers recognition problems that usually sound like `Given some weird combinatorial property, check if the given structure satisfies it`.

Lucas believes that the perfect programming competition problem should contain a cactus a tree in it. Trying to put together laminar sets and trees into a recognition problem, he finally came up with the following problem: given an undirected tree on $n$ vertices and a family $F = {F_{1}, . . . , F_{k}}$ of sets, where $F_{i}$ consists of all vertices belonging to the simple path between some two vertices $a_{i}$ and $b_{i}$ of the tree, check if the family $F$ is a laminar family. Note that in this case $Ω = V$ , and each $F_{i} ⊆ V$ .

As you can see, Lucas had succeeded in suggesting this problem to the programming contest. Now it is up to you to solve it.


## 输入格式



The first line of the input contains two integers $n$ and $f (1 \le n , f \le 100 000)$ -- the number of vertices in the tree and the number of elements in a family $F$ .

Next $n−1$ lines describe the tree structure. In the i-th line there are two integers $u_{i}$ and $v_{i} (1 \le u_{i}, v_{i} \le n , u_{i} ≠ v_{i})$ -- the indices of the vertices that are connected by the i-th edge of the tree.

Next $f$ lines describe the sets forming the family $F$ . In the i-th line there are two integers $a_{i}$ and $b_{i} (1 \le a_{i}, b_{i} \le n)$ , such that $F_{i}$ consists of all vertices belonging to the simple path between vertices $a_{i}$ and $b_{i}$ in the tree (including $a_{i}$ and $b_{i}).$


## 输出格式



Output the only word `Yes` or `No` depending on whether or not the given set family is laminar.


## 样例

### 样例输入 #1
```
4 2
1 2
2 3
2 4
1 2
4 2

```
### 样例输出 #1
```
No

```
### 样例输入 #2
```
6 5
1 2
2 3
3 4
5 6
5 2
2 1
6 6
1 4
3 4
4 1

```
### 样例输出 #2
```
Yes

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

- 给定一棵 $n$ 个节点的树，给出 $f$ 条树上的路径，试判断下面的命题是否成立：
- $f$ 条路径中，任意两条路径的点集的交集为空，或者一个是另一个的子集。
- 成立输出 `Yes`，不成立输出 `No`。
- $1 \leq n,f \leq 10^5$


---

---
title: "[NEERC 2016] Cactus Construction"
layout: "post"
diff: 省选/NOI-
pid: P6966
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NEERC 2016] Cactus Construction
## 题目描述



Let us consider the following way of constructing graphs. Pick the number of colors $ˆc$ . Let $n$ be the number of vertices in a graph. To build a graph, we use a workspace with several graphs in it. Each vertex of each graph has a color. Colors are denoted by integers from $1$ to $ˆc$ . Initially, we have $n$ graphs in a workspace with one vertex in each graph, all colored with color $1$ , and no edges. The only vertex of i-th graph has number $i$ .

The following operations are permitted:

join a $b$ : join graphs containing vertices a and $b$ into one graph. No edges are added. Vertices a and $b$ must be in different graphs.

recolor a $c_{1 }c_{2}:$ in graph containing vertex a recolor all vertices of color $c_{1}$ with color $c_{2}.$

connect a $c_{1 }c_{2}:$ in graph containing vertex a create edges between all pairs of vertices where one vertex has color $c_{1}$ and the other has color $c_{2}.$ If $c_{1} = c_{2}$ loops are not created. If such an edge already exists, then the second parallel edge is created. Multi-edges are not allowed in this problem, so this case must not occur.

At the end we should have a single graph and colors of its vertices do not matter.

The minimal number of colors $ˆc$ , that can be used to construct a graph, is called a clique width of a graph. Clique width is one of the characteristics of graph complexity. Many NP-hard problems can be solved in polynomial time on graphs with bounded clique width, using dynamic programming on this process of building a graph. For a general graph, calculating the exact value of a clique width is known to be NP-hard. However, for some graph classes bounds on a clique width are known.

Cactus is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively cactus is a generalization of a tree where some cycles are allowed. Multi-edges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus. It is known that a clique width of a cactus does not exceed $4$ .

You are given a cactus. Find out how to build it in the described way using at most $ˆc = 4$ colors.

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13991/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-12-22%20%EC%98%A4%ED%9B%84%207.31.10.png)

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13991/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-12-22%20%EC%98%A4%ED%9B%84%207.31.21.png)


## 输入格式



The first line of the input file contains two integers $n$ and $m (1 \le n \le 50 000$ ; $0 \le m \le 50 000)$ . Here $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$ . Edges of the graph are represented by a set of edge-distinct paths, where $m$ is the number of such paths.

Each of the following $m$ lines contains a path in the graph. A path starts with an integer $k_{i} (2 \le k_{i } \le 1000)$ followed by $k_{i}$ integers from $1$ to $n$ . These $k_{i}$ integers represent vertices of a path. Adjacent vertices in the path are distinct. The path can go to the same vertex multiple times, but every edge is traversed exactly once in the whole input file.

The graph in the input file is a cactus.


## 输出格式



In the first line print one integer $q$ -- the number of operations you need. This number should not be greater than $10^{6}$ . In the next $q$ lines print operations. Each operation is denoted by its first letter (`j` for join, `r` for recolor and `c` for connect) and its arguments in the order they are described in the problem statement.

At the end, after applying all these operations, one should have one graph, which is equal to the cactus in the input. This means that there should be exactly one edge between each pair of vertices connected in the input graph, and no edges between vertices not connected in the input graph.


## 样例

### 样例输入 #1
```
8 2
5 1 2 3 4 7
5 4 5 6 1 8

```
### 样例输出 #1
```
17
r 2 1 2
j 2 3
c 2 1 2
r 6 1 2
j 5 6
c 6 1 2
r 4 1 3
j 4 3
j 4 6
j 4 7
c 4 3 1
r 4 3 1
r 8 1 2
r 1 1 3
j 1 8
j 1 4
c 1 3 2

```
### 样例输入 #2
```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10

```
### 样例输出 #2
```
39
r 7 1 2
r 5 1 2
j 7 8
c 7 1 2
j 5 4
c 5 1 2
r 6 1 3
j 6 7
j 6 5
c 6 3 2
r 3 1 4
j 6 3
c 6 4 1
r 11 1 2
r 13 1 2
j 12 11
j 12 13
c 11 1 2
r 10 1 3
j 12 10
c 10 2 3
r 10 1 2
r 10 4 2
r 15 1 3
j 15 10
c 15 3 3
j 9 10
c 9 1 3
r 9 3 2
r 9 1 4
r 14 1 4
j 9 14
c 9 4 4
r 1 1 4
r 3 1 2
j 2 1
j 2 14
j 2 3
c 2 1 4

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

有 $n$ 个集合，初始第 $i$ 个集合只包含第 $i$ 个点，每个点的初始颜色都为 $1$。要求使用下列 $3$ 种操作构建出给定的仙人掌。输出方案，操作数不得多于 $10^6$。

- $j\ a\ b$，将 $a$ 所在的集合和 $b$ 所在的集合合并成一个集合。

- $r\ a\ c_1\ c_2$（$c_1,c_2\in[1,2,3,4]$），将 $a$ 所在的集合中，所有颜色为 $c_1$ 的点的颜色改为 $c_2$。

- $c\ a\ c_1\ c_2$，将 $a$ 所在的集合中，每一个颜色为 $c_1$ 的点连向每一个  颜色为 $c_2$ 的点，**不允许出现重边**。

输入第一行为点数 $n$ 和 $m$ 条（$n,m\leq 50000$）边不重复的路径，每条边**恰好**会出现一次。接下来每行第一个数字 $k_i$($2\leq k_i\leq1000$) 代表路径的点数，后面 $k_i$ 个数字表示一条路径。


---

---
title: "[NEERC 2016] Game on Graph"
layout: "post"
diff: 省选/NOI-
pid: P6970
tag: ['2016', 'ICPC']
---
# [NEERC 2016] Game on Graph
## 题目描述



Gennady and Georgiy are playing interesting game on a directed graph. The graph has $n$ vertices and $m$ arcs, loops are allowed. Gennady and Georgiy have a token placed in one of the graph vertices. Players take turns moving the token along one of the arcs that starts in the vertex the token is currently in. When there is no such arc, then this player loses the game.

For each initial position of the token and the player who is moving first, your task is to determine what kind of result the game is going to have. Does it seem to be easy? Not so much.

On one side, Gennady is having a lot of fun playing this game, so he wants to play as long as possible. He even prefers a strategy that leads to infinite game to a strategy that makes him a winner. But if he cannot make the game infinite, then he obviously prefers winning to losing.

On the other side, Georgiy has a lot of other work, so he does not want to play the game infinitely. Georgiy wants to win the game, but if he cannot win, then he prefers losing game to making it infinite.

Both players are playing optimally. Both players know preferences of the other player.


## 输入格式



In the first line there are two integers -- the number of vertices $n (1 \le n \le 100 000)$ and the number of arcs $m (1 \le m \le 200 000)$ . In the next $m$ lines there are two integers a and $b$ on each line, denoting an arc from vertex a to vertex $b$ . Vertices are numbered from $1$ to $n$ . Each $(a , b)$ tuple appears at most once.


## 输出格式



In the first line print $n$ characters -- i-th character should denote the result of the game if Gennady starts in vertex $i$ . In the second line print $n$ characters -- i-th character should denote the result of the game if Georgiy starts in vertex $i$ . The result of the game is denoted by `W` if the starting player wins the game, `L` if the starting player loses the game, and `D` (draw) if the game runs infinitely.


## 样例

### 样例输入 #1
```
6 7
1 2
2 1
2 3
1 4
4 1
4 5
5 6

```
### 样例输出 #1
```
WDLDWL
DWLLWL 

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

Gennady 和 Georgiy 在玩一个有向图上的游戏。这个图有 $n$ 个点 $m$ 条边，两人轮流操作，每次可以将棋子沿着其中一条边移动，不能移动者输。

你要对于每个点，分别求出以这个店为起点开始游戏，两人分别作为先手，最终会输，赢，还是平局（游戏无限循环）。

其中，Gennady 因为玩得很开心，所以他更期望将游戏变为平局；Georgiy 还有很多其他事，所以他更期望游戏不要平局。当然，在不平局的基础上，两人都更希望赢。

### 输入格式 

第一行两个数 $n$，$m$ 表示有 $n$ 个点 $m$ 条边。  
接下来 $m$ 行每行两个数 $a,b$ 表示一条由 $a$ 至 $b$ 的边。

### 输出格式
两行，第一行表示分别以每一个点为起点 Gennady 先手的胜负情况；第二行表示分别以每一个点为起点 Georgiy 先手的胜负情况。`W` 表示赢，`L` 表示输，`D` 表示平局。

by a___


---

---
title: "[NEERC 2016] List of Primes"
layout: "post"
diff: 省选/NOI-
pid: P6973
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NEERC 2016] List of Primes
## 题目描述

Lidia likes sets of prime numbers. When she is bored, she starts writing them down into the Extremely Long Notebook for Prime Sets.

Elements of each set are written down in ascending order. Each set of prime numbers appears in her notebook eventually. A set with a smaller sum always appears before a set with a larger sum. Sets with the same sum are sorted in ascending lexicographical order: they are compared by the first element, if the first elements are equal, then by second element, and so on.

Just in case someone decides to parse her notebook, she writes down her sets in a machine-readable JSON format. Of course, she puts a space after each comma. Here's the beginning of her notebook:

$[2], [3], [2 , 3], [5], [2 , 5], [7], [3 , 5], [2 , 7], [2 , 3 , 5], [3 , 7], [11], [2 , 3 , 7], [5 , 7], [2 , 11], [13], [2 , 5 , 7],$

Lidia wants to double-check her work, so here is her request for you: given two integers, $a$ and $b$ , output a substring of her notebook from the position $a$ to the position $b$ (inclusive, counting from $1$) .


## 输入格式



The first line contains two integers, $a$ and $b$ ($1 \le a \le b \le 10^{18}; b - a \le 10^{5}$).


## 输出格式



Output the substring of the notebook described in the problem statement from the position $a$ to the position $b$ . You must write a line with exactly $b - a + 1$ characters, including any leading or trailing spaces.


## 样例

### 样例输入 #1
```
1 35

```
### 样例输出 #1
```
[2], [3], [2, 3], [5], [2, 5], [7],

```
### 样例输入 #2
```
36 41

```
### 样例输出 #2
```
 [3, 5

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

Lidia 喜欢素数集。当她无聊时，她就把它们写进她的「素数集的超长笔记本」。

集合中的元素按升序排列。每个集合都会在她的笔记本里出现，且以元素和为第一关键字，字典序为第二关键字排列。

为了预防有人决定解析她的笔记本，她把她的集合写成了机器可读的 JSON 格式。当然，她在每个逗号后面都加了空格。以下是她的笔记本的开头：

$$
[2], [3], [2 , 3], [5], [2 , 5], [7], [3 , 5], [2 , 7], [2 , 3 , 5], [3 , 7], [11], [2 , 3 , 7], [5 , 7], [2 , 11], [13], [2 , 5 , 7],
$$

Lidia 想仔细检查她的工作，所以她给了你两个整数 $a$ 和 $b$，要你输出她的笔记本中第 $a$ 到 $b$ 个字符（含两端，从 $1$ 开始）的内容。


---

---
title: "[NEERC 2015] Cactus Jubilee"
layout: "post"
diff: 省选/NOI-
pid: P6975
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Cactus Jubilee
## 题目描述



This is the $20-th$ Northeastern European Regional Contest $(NEERC).$ Cactus problems had become a NEERC tradition. The first Cactus problem was given in $2005$ , so there is a jubilee -- $10$ years of Cactus.

Cactus is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively cactus is a generalization of a tree where some cycles are allowed. Multiedges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus.

You are given a cactus. Let's move an edge -- remove one of graph's edges, but connect a different pair of vertices with an edge, so that a graph still remains a cactus. How many ways are there to perform such a move?

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11737/1.png)

For example, in the left cactus above (given in the first sample), there are $42$ ways to perform an edge move. In the right cactus (given in the second sample), which is the classical NEERC cactus since the original problem in $2005$ , there are $216$ ways to perform a move.


## 输入格式



The first line of the input file contains two integers $n$ and $m (1 \le n \le 50 000 , 0 \le m \le 50 000)$ . Here $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$ . Edges of the graph are represented by a set of edge-distinct paths, where $m$ is the number of such paths.

Each of the following $m$ lines contains a path in the graph. A path starts with an integer $k_{i} (2 \le k_{i} \le 1000)$ followed by $k_{i}$ integers from $1$ to $n$ . These $k_{i}$ integers represent vertices of a path. Adjacent vertices in a path are distinct. Path can go to the same vertex multiple times, but every edge is traversed exactly once in the whole input file.

The graph in the input file is a cactus.


## 输出格式



Write to the output file a single integer -- the number of ways to move an edge in the cactus.


## 样例

### 样例输入 #1
```
6 1
7 1 2 5 6 2 3 4

```
### 样例输出 #1
```
42

```
### 样例输入 #2
```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10

```
### 样例输出 #2
```
216

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

题目描述

定义一种无向连通图叫`仙人掌图（Cactus图）`。仙人掌图中没有重边和自环，并且其中的每一条边至多位于一个简单环上。简单地说，`仙人掌图`是树的一种泛化形式，其中允许出现一些环。

现在有一个`仙人掌图`，你每次可以移动一条边（移除图的一条边，并将另一对顶点用一条边连接起来）。问如果要让后来得到的新图仍然是`仙人掌图`，有多少种移动边的办法？

输入格式

第一行包含两个整数n和m，分别表示图中的顶点数（顶点的编号分别为${1,2,3,...,n}$）和边的数目，且满足
$$1≤n≤50000,0≤m≤50000$$

第2~m+1行，每一行表示一条路径（从一个顶点出发一直往后走，直到当前所在的顶点没有任何未走过一条边）。

（译者注：虽然应该都能看出来了，但是还是用一个递归函数更浅显易懂）

设路径的开始点为$q_1$，$E_i$表示第$i$个点的边,$vis$数组中存储已经走过了的边，则整条路径可定义为：
```
1.x←q1
2.f(x)
	1.add(vis[],x)
	2.for i∈Ex do
	1.if i not in vis[] then
		1.call f(i->to)
3.print(vis[])
```
即：每一行的开始有一个整数$k_i$，满足
$2≤k_i≤1000$，紧接着有$k_i$个整数，表示这条路径所经过的顶点$q_i$，满足$q_i∈[1,n]$。

数据保证路径中的相邻顶点是不同的。

在路径中可以多次到达同一个顶点，但在整个输入文件中，每条边只遍历一次。

数据保证输入文件中的图形是仙人掌。

输出格式

输出文件中只有一个整数，即移动`仙人掌图`中一条边的方法数。

数据范围
$$1≤n≤50000,0≤m≤50000,2≤k_i≤1000,q_i∈[1,n]$$


---

---
title: "[NEERC 2015] Distance on Triangulation"
layout: "post"
diff: 省选/NOI-
pid: P6976
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Distance on Triangulation
## 题目描述



You have a convex polygon. The vertices of the polygon are successively numbered from $1$ to $n$ . You also have a triangulation of this polygon, given as a list of $n − 3$ diagonals.

You are also given $q$ queries. Each query consists of two vertex indices. For each query, find the shortest distance between these two vertices, provided that you can move by the sides and by the given diagonals of the polygon, and the distance is measured as the total number of sides and diagonals you have traversed.


## 输入格式



The first line of the input file contains an integer $n$ -- the number of vertices of the polygon $(4 \le n \le 50 000)$ .

Each of the following $n−3$ lines contains two integers $a_{i}, b_{i}$ -- the ends of the i-th diagonal $(1 \le a_{i}, b_{i} \le n , a_{i} ≠ b_{i}).$

The next line contains an integer $q$ -- the number of queries $(1 \le q \le 100 000)$ .

Each of the following $q$ lines contains two integers $x_{i}, y_{i}$ -- the vertices in the i-th query $(1 \le x_{i}, y_{i} \le n)$ .

It is guaranteed that no diagonal coincides with a side of the polygon, and that no two diagonals coincide or intersect.


## 输出格式



For each query output a line containing the shortest distance.


## 样例

### 样例输入 #1
```
6
1 5
2 4
5 2
5
1 3
2 5
3 4
6 3
6 6

```
### 样例输出 #1
```
2
1
1
3
0

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给定一个正 $n$ 边形及其三角剖分, 共 $2n−3$ 条边 ($n$ 条多边形的边和 $n−3$ 条对角线), 每条边的长度为 $1$。

共 $q$ 次询问, 每次询问给定两个点, 求它们的最短距离。

Translated by Eason_AC  
2020.11.19


---

---
title: "[NEERC 2015] Hypercube"
layout: "post"
diff: 省选/NOI-
pid: P6980
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Hypercube
## 题目描述



Consider a $4-hypercube$ also known as tesseract. A unit solid tesseract is a 4D figure that is equal to the convex hull of $16$ points with Cartesian coordinates $(±½, ±½, ±½, ±½)$ -- its vertices. It has $32$ edges $(1D), 24$ square faces $(2D),$ and $8$ cubic $3-faces$ (3D) also known as cells. We study hollow tesseracts and define a tesseract as a boundary of a solid tesseract. Thus, a tesseract is a connected union of $8$ solid cubes (its cells) that intersect between each other at $24$ tesseract's square faces, $32$ edges, and $16$ vertices.

Let's cut a tesseract along $17$ of its $24$ faces, so that it still remains connected via $7$ faces that were left intact. Unfold the tesseract into a 3D hyperplane by rotating its constituting cubes along the faces that were left intact until all its cells lie in the same 3D hyperplane. The result is called a $3-net$ of a tesseract. This process is a natural generalization of how a 3D cube is cut and unfolded onto a 2D plane to produce a $2-net$ of a cube that consists of $6$ squares.

In this problem you are given a tree-like $8-polycube$ in 3D space also known as octocube. An octocube is a collection of $8$ unit cubical cells joined face-to-face. More formally, intersection of each pair of cubical cells constituting an octocube is either empty, a point, a unit line $(1D),$ or a unit square $(2D).$ The given octocube is tree-like in the following sense. Consider an adjacency graph of the octocube -- a graph with $8$ vertices corresponding to its $8$ cells. There is an edge in the adjacency graph between pairs of adjacent cells. Two cells of an octocube are called adjacent when their intersection is a square. Cells that intersect at a point or a line are not considered adjacent. An octocube is called tree-like when its adjacency graph is a tree.

Your task is to determine whether the given tree-like octocube constitutes a $3-net$ of a tesseract. That is, whether this octocube being put onto a hyperplane in 4D space can be folded in 4D space along the squares of intersection between its cells into a tesseract.

For example, look at the leftmost picture below. It shows a wire-frame of the tree-like octocube. Rotate cell $GHLKG_{1}H_{1}L_{1}K_{1}$ around a plane GHLK and cell $FGKJF_{2}G_{2}K_{2}J_{2}$ around a plane FGKJ at angle $90$ degrees in $4-th$ dimension outside of the original hyperplane. As a result, point $G_{1}$ joins with $G_{2}$ and $K_{1}$ joins with $K_{2}.$ The face $GKK_{2}G_{2}$ is glued to face $GKK_{1}G_{1}.$ The result is shown on the right. The $4-th$ dimension is orthographically projected onto the $3$ shown in perspective. The points that have moved out of the original hyperplane are marked with hollow dots.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11742/1.png)

Rotate $EFJIE_{1}F_{1}J_{1}I_{1}$ around EFJI and $EHLIE_{2}H_{2}L_{2}I_{2}$ around EHLI. The result is shown on the following picture on the left. The remaining steps are as follows. Rotate MNOPQRST around MNOP, then rotate both MNOPQRST and IJKLMNOP around IJKL and rotate ABCDEFGH around EFGH. The last step is to glue all faces that meet together to get a tesseract that is shown on the right.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11742/2.png)


## 输入格式



The first line of the input file contains there integers $m , n , k$ -- the width, the depth, and the height of the box that contains the given octocube $(1 \le m , n , k \le 8)$ . The following $k$ groups of lines describe rectangular slices of the box from top to bottom. Each slice is described by $n$ rows with $m$ characters each. The characters on a line are either $‘. ',$ denoting an empty space, or $‘x',$ denoting a unit cube. The input file is guaranteed to describe a tree-like octocube.


## 输出格式



Write to the output file a single word `Yes` if the given octocube can be folded into a tesseract or `No` otherwise.


## 样例

### 样例输入 #1
```
3 3 4
...
.x.
...
.x.
xxx
.x.
...
.x.
...
...
.x.
...

```
### 样例输出 #1
```
Yes

```
### 样例输入 #2
```
8 1 1
xxxxxxxx

```
### 样例输出 #2
```
No

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

给定一个三维图形，保证相邻小方格之间构成树形结构，判断它是否是4维超立方体的一个三维展开。


---

---
title: "[NEERC 2015] Iceberg Orders"
layout: "post"
diff: 省选/NOI-
pid: P6981
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Iceberg Orders
## 题目描述



You are working for Metagonia stock exchange. Recently traders in Metagonia had heard about Iceberg orders traded on London stock exchange and asked your employer to add such functionality as well. A stock exchange is an engine that receives orders and generates trades.

An iceberg order is a quintuple of integers (ID, $T , P , V$ , TV). Each order has an identifier ID (unique among all orders), type $T$ (which is equal to either BUY $= 1$ or SELL $= 2)$ , price $P$ , total remaining volume $V$ and tip volume TV. For each order, exchange additionally keeps track of its current volume CV and priority PR. There is also a global priority counter of the exchange GP. An order book of the exchange is a set of orders.

Trades that are generated by the exchange are quadruples of integers (BUY ID, SELL ID, $P , V)$ . Each trade has BUY ID and SELL ID -- identifiers of matching BUY and SELL orders, trade price $P$ , and trade volume $V$ .

When an order is received by the exchange it is matched against orders currently on the order book. This is done as follows. Suppose an order a is received with $T_{a} =$ SELL. Among all orders currently on the order book we look for an order $b$ such that $T_{b} =$ BUY and $P_{b} \ge P_{a}.$ We select such an order $b$ with the largest price, and if there are several -- one with the smallest priority. If there is such an order $b$ , then a trade $t$ is generated with BUY $ID_{t} = ID_{b}$ and SELL $ID_{t} = ID_{a}$ at trade price $P_{t} = P_{b}$ with trade volume $V_{t} = mi_n(V_{a}, CV_{b}). V_{a}, V_{b},$ and $CV_{b}$ are all decreased by trade volume. If $V_{b} = 0$ after this, then the order $b$ is removed from the order book. If $CV_{b} = 0$ (but $V_{b} > 0)$ then we set current volume of order $b$ to $CV_{b} = mi_n(V_{b}, TV_{b}),$ set $PR_{b} =$ GP, and increment GP. We continue these operations of selecting $b$ and generating trades until either $V_{a} = 0$ or there are no more orders $b$ on the order book which satisfy the condition. In the latter case, we add order a to the order book with $CV_{a} = mi_n(V_{a}, TV_{a})$ and $PR_{a} =$ GP, and then increment GP. When the process of matching the order a is finished with several trades between the same pair of orders a and $b$ (and there can be lots of them!), they are all united into a single trade with the volume equal to the sum of individual trade volumes.

If $T_{a} =$ BUY we are looking for an order $b$ with $T_{b} =$ SELL and $P_{b} \le P_{a}$ and select such an order $b$ with the smallest price and the smallest priority among those. The rest of the matching process is as described above, with trades having BUY $ID_{t} = ID_{a},$ SELL $ID_{t} = ID_{b}, P_{t} = P_{b},$ and $V_{t} = mi_n(V_{a}, CV_{b}).$

Initially the order book is empty. You are presented with several orders that are received by the exchange one by one. You need to print generated trades and the order book state after all orders are processed.

Hint: The priority and GP are introduced in the problem statement only for the purpose of a formal description of the algorithm. The actual implementation does not have to keep track of priority. Typically, an exchange simply keeps a priority-ordered list of orders of each type at each price in its order book.


## 输入格式



The first line of the input contains the number of orders $n (1 \le n \le 50 000)$ . Each of the following $n$ lines represent an order. Each order is given by a space-separated quintuple ID $T P V$ TV , where $1 \le $ ID $ \le 1 000 000 , T = 1$ for BUY and $T = 2$ for SELL, $1 \le P \le 100 000$ and $1 \le $ TV $ \le V \le 1 000 000 000$ .


## 输出格式



For each order print all trades generated by processing this order, in ascending order of pairs (BUY ID, SELL ID), each trade on its own line. Each trade shall be printed as a space-separated quadruple of integers BUY ID SELL ID $P V$ . It is guaranteed that the total number of trades would not exceed $100 000$ . Print a blank line after all trades, followed by the order book. Each order that is still on the book shall be printed as a space-separated sextuple ID $T P V$ TV CV, sorted first by $P$ and then by PR.


## 样例

### 样例输入 #1
```
7
42 1 100 200 20
239 1 100 50 50
1111 1 101 30 15
1234 1 100 300 15
4321 2 99 125 25
5678 1 101 30 30
8765 2 101 100 20

```
### 样例输出 #1
```
42 4321 100 30
239 4321 100 50
1111 4321 101 30
1234 4321 100 15
5678 8765 101 30

42 1 100 170 20 10
1234 1 100 285 15 15
8765 2 101 70 20 20

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 




---

---
title: "[NEERC 2015] Jump"
layout: "post"
diff: 省选/NOI-
pid: P6982
tag: ['2015', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2015] Jump
## 题目背景

这是一道 IO 交互题。
## 题目描述

暂无英文题面。
## 样例

### 样例输入 #1
```
2
1
0
1
2
```
### 样例输出 #1
```
01
11
10
00
```
## 题目翻译

给定长度为 $n$（$n$ 为偶数） 的 01 字符串 $S$。

你可以向交互库进行询问。你可以向交互库输出一个长度为 $n$ 的 01 字符串 $Q$。设 $S$ 和 $Q$ 有 $k$ 个对应的位置上的字符相同。若 $k=n$ 或 $k=\frac n 2$，则交互库将返回 $k$，否则交互库将返回 $0$。

你最多向交互库询问 $n+500$ 次，要求求出 $S$。你只需要使最后一次询问的返回值为 $n$ 即可。此时你应立即结束程序，否则将得到不可预料的结果。

若你的字符串长度不为 $n$ 或出现 01 以外的字符，或者你的询问次数超过上限，则交互库会返回 $-1$。此时你应立即结束程序，否则将得到不可预料的结果。

$1\leq n\leq 1000$。


---

---
title: "[NEERC 2015] King’s Inspection"
layout: "post"
diff: 省选/NOI-
pid: P6983
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NEERC 2015] King’s Inspection
## 题目描述



King Karl is a responsible and diligent ruler. Each year he travels across his country to make certain that all cities are doing well.

There are $n$ cities in his country and $m$ roads. In order to control the travelers, each road is unidirectional, that is a road from city a to city $b$ can not be passed from $b$ to a .

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11745/1.png)

Karl wants to travel along the roads in such a way that he starts in the capital, visits every non-capital city exactly once, and finishes in the capital again.

As a transport minister, you are obliged to find such a route, or to determine that such a route doesn't exist.


## 输入格式



The first line contains two integers $n$ and $m (2 \le n \le 100 000 , 0 \le m \le n + 20)$ -- the number of cities and the number of roads in the country.

Each of the next $m$ lines contains two integers $a_{i}$ and $b_{i} (1 \le a_{i}, b_{i} \le n)$ , meaning that there is a one-way road from city $a_{i}$ to city $b_{i}.$ Cities are numbered from $1$ to $n$ . The capital is numbered as $1$ .


## 输出格式



If there is a route that passes through each non-capital city exactly once, starting and finishing in the capital, then output $n + 1$ space-separated integers -- a list of cities along the route. Do output the capital city both in the beginning and in the end of the route.

If there is no desired route, output `There is no route, Karl!` (without quotation marks).


## 样例

### 样例输入 #1
```
4 6
1 4
4 1
4 2
2 1
3 4
1 3

```
### 样例输出 #1
```
1 3 4 2 1

```
### 样例输入 #2
```
4 3
1 4
1 4
2 2

```
### 样例输出 #2
```
There is no route, Karl!

```
## 提示

Time limit: 10 s, Memory limit: 512 MB. 


## 题目翻译

国王 Karl 是一个负责并且勤奋的统治者。每年他都会游览并视察他的国家来保证每个城市都欣欣向荣。

他的国家有$n$个城市$m$条道路。每条道路是单向的，一条$a$到$b$的道路不能由$b$到$a$
经过。

Karl 想要游览他的国家，并且路线为由首都开始，经过每个非首都城市恰好一次，最终回到首都。

作为运输大臣，你有义务找到这样的一条路线，或者确定其不存在。


---

---
title: "[NEERC 2015] Landscape Improved"
layout: "post"
diff: 省选/NOI-
pid: P6984
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Landscape Improved
## 题目描述



Louis $L$ Le Roi-Univers has ordered to improve the landscape that is seen from the royal palace. His Majesty prefers to see a high mountain.

The Chief Landscape Manager is going to raise a mountain for Louis. He represents a landscape as a flat picture on a grid of unit squares. Some of the squares are already filled with rock, while others are empty. This greatly simplifies the design. Unit squares are small enough, and the landscape seems to be smooth from the royal palace.

The Chief Landscape Manager has a plan of the landscape -- the heights of all rock-filled columns for each unit of width. He is going to add at most $n$ square units of stones atop of the existing landscape to make a mountain with as high peak as possible. Unfortunately, piles of stones are quite unstable. A unit square of stones may be placed only exactly on top of the other filled square of stones or rock, moreover the squares immediately to the bottom-left and to bottom-right of it should be already filled.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11746/1.png)

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11746/2.png)

Existing landscape

Improved landscape

Your task is to help The Chief Landscape Manager to determine the maximum height of the highest mountain he can build.


## 输入格式



The first line of the input file contains two integers $w$ -- the width of the existing landscape and $n$ -- the maximum number of squares of stones to add $(1 \le w \le 100 000 , 0 \le n \le 10^{18}).$

Each of the following $w$ lines contains a single integer $h_{i}$ -- the height of the existing landscape column $(1 \le h_{i} \le 10^{9}).$


## 输出格式



The output file shall contain the single integer -- the maximum possible landscape height after at most $n$ unit squares of stones are added in a stable way.


## 样例

### 样例输入 #1
```
8 4
3
4
2
1
3
3
2
4

```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
3 100
3
3
3

```
### 样例输出 #2
```
4

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

给定序列 $\{h_i\}(i\in[1,w])$ 和常数 $n$。

$\forall i\in(1,w)$ ，仅当 $h_{i-1} \geq h_i$ 且 $h_{i+1} \geq h_i$ 时可使 $h_i$ 变为 $h_i+1$ ，且操作次数不能多于 $n$ 次。

求所有合法方案下，$\max\{h_i\}$ 的最大值。

$1\leq w\leq 10^5,1\leq h_i \leq 10^9,1\leq n\leq 10^{18}.$


---

---
title: "[NEERC 2014] Cactus Generator（征集SPJ）"
layout: "post"
diff: 省选/NOI-
pid: P6987
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Cactus Generator（征集SPJ）
## 题目描述



NEERC featured a number of problems about cactuses -- connected undirected graphs in which every edge belongs to at most one simple cycle. Intuitively, cactus is a generalization of a tree where some cycles are allowed.

In $2005$ , the first year where a problem about cactuses appeared, the problem was called simply `Cactus`. In $2007$ it was `Cactus Reloaded`, in $2010$ it was called `Cactus Revolution`, and in $2013$ it was called `Cactus Automorphisms`. Here is an example of cactus that was used in those problems:

![](/upload/images2/cactus.png)

For four years judges had to generate test files for cactuses with thousands of vertices. Of course, a number of test generators of ever-increasing complexity were built, culminating with a domain-specific language called CGL -- Cactus Generator Language. CGL can compactly define a big cactus for purposes of a test. In this problem you have to parse a simplified version of this language, which we call SCGL -- Simple Cactus Generator Language, and output a resulting cactus.

A cactus has to be output by listing the minimal set of edge-distinct paths that cover the whole graph.

The syntax of SCGL cactus definition is represented by the graph non-terminal in the grammar that is given below using the Extended Backus-Naur Form:

graph $=$ `c`

$|$ `c(` list `)`

$|$ `loop(` list `)`

$|$ `t(` list `)`

list $=$ graph ${$ `,` graph $}$

$|$ (number $|$ range $|$ variable ) $[$ `,` graph $]$

number $=$ nzdig ${$ `0` $|$ nzdig $}$

nzdig $=$ `1` $|$ `2` $| \cdots |$ `8` $|$ `9`

range $=$ `range(` variable `,` numvar `,` numvar `)`

variable $=$ `A` $|$ `B` $| \cdots |$ `Y` $|$ `Z`

numvar $=$ number $|$ variable

A graph production rule denotes a graph with two labeled vertices -- the first and the last. Graphs definition rules have the following semantics:

The basic building block $c$ denotes a graph with just two vertices (one is the first and the other one is the last) and one edge.

The $c(σ)$ rule connects a specified list of graphs $σ$ from left to right into a chain, merging the last vertex of the first graph in the list with the first vertex of the second graph in the list, the last vertex of the second graph with the first of the third one, and so on. The resulting graph's first vertex is the first vertex of the first graph in the list, and the resulting graph's last vertex is the last vertex of the last graph in the list.

The $loo_p(σ)$ rule connects a specified list of graphs $σ$ from left to right, merging the last vertex of the first graph in the list with the first vertex of the second graph in the list, and so on like in $c(σ),$ while the last vertex of the last graph in the list is merged with the first vertex of the first graph in the list to form a loop. The resulting graph's first and last vertices are the first and the last vertices of the first graph in the list. Loop can be applied only to lists with more than one graph.

The $t(σ)$ rule connects a specified list of graphs $σ,$ merging their first vertices. The resulting graph's first and last vertices are the first and the last vertices of the first graph in the list.

The list of graphs is either specified explicitly, by a comma-separated list, or using a list repetition with a number, a range, or a variable, optionally followed by a comma and a graph. When a graph is not explicitly specified in a list repetition, then the given graph is assumed to be $c$ .

The simplest list repetition is defined using a number non-terminal. It denotes a list of graphs with the specified integer number of copies of the given graph.

A range list repetition is defined by $range(ν, α, β)$ rule which has three components -- a variable $ν,$ and numbers $α$ and $β.$ If $ξ$ character sequence is a graph, then $c|loo_p|t(range(ν, α, β), ξ)$ are called rangeenabled rules and the variable $ν$ is called a bound variable in $ξ.$ In the context of a range-enabled rule, $ξ$ is repeated $|β − α| + 1$ times to form a list. Every occurrence of variable $ν$ in $ξ$ is replaced by consecutive integer numbers between $α$ and $β$ inclusive in ascending order. That produces a list of $|β −α|+ 1$ graphs, which are then connected according the specification of the corresponding range-enabled rule. The $α$ and $β$ themselves might refer to variables that are bound in the outer range-enabled rule.

In a well-formed graph:

each variable non-terminal (a letter from A to $Z)$ occurs at most once as $ν$ in $range(ν, α, β)$ rules;

all other occurrences of variable non-terminal that are allowed by the grammar are bound.

Note, that if a character sequence $ξ$ is a graph, then $ξ, c(ξ),$ c(1 , $ξ), t(ξ),$ and t(1 , $ξ)$ all denote the same graph. On the other hand, neither $loo_p(ξ)$ nor loop(1 , $ξ)$ are allowed.

The following examples illustrate these basic rules. The graphs have their first and last vertices marked with letters $F$ and $L$ correspondingly.

![](/upload/images2/cactus1.png)

![](/upload/images2/cactus2.png)


## 输入格式



The input file contains a single line with a well-formed cactus definition in SCGL. While the syntax and semantics of SCGL themselves do not guarantee that the resulting graph is a cactus, the input file for this problem always defines a cactus -- every edge belongs to at most one simple cycle and there are no multiple edges between vertices. For example, neither loop(3 , $loo_p(3))$ nor $loo_p(2)$ are possible.

The line in the input file is at most $1000$ characters long and defines a cactus with at most $50 000$ vertices. Integer numbers represented by number non-terminals do not exceed $50 000$ .


## 输出格式



The first line of the output file must contain two integer numbers $n$ and $m$ . Here $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$ , where $1$ is the number of the first vertex of the graph and $n$ is the number of the last vertex of the graph. The other vertices can be numbered arbitrarily. Edges of the graph are represented by a set of edge-distinct paths, where $m$ is the minimal number of such paths.

Each of the following $m$ lines must contain a path in the graph. A path starts with an integer number $k_{i} (k_{i} \ge 2)$ followed by $k_{i}$ integers from $1$ to $n$ . These $k_{i}$ integers represent vertices of a path. A path can go to the same vertex multiple times, but every edge must be traversed exactly once in the whole output file.


## 样例

### 样例输入 #1
```
c(c,t(loop(3),c(c,loop(6))),loop(c,c,t(c,loop(4))))

```
### 样例输出 #1
```
15 1
19 1 2 9 10 11 12 13 10 15 9 14 2 3 4 5 6 7 8 3

```
### 样例输入 #2
```
c

```
### 样例输出 #2
```
2 1
2 1 2

```
### 样例输入 #3
```
c(2)

```
### 样例输出 #3
```
3 1
3 1 2 3

```
### 样例输入 #4
```
c(3)

```
### 样例输出 #4
```
4 1
4 1 2 3 4

```
### 样例输入 #5
```
t(c(3),c,c)

```
### 样例输出 #5
```
6 2
2 1 2
5 3 1 4 5 6

```
### 样例输入 #6
```
c(2,t(c(2),c,c))

```
### 样例输出 #6
```
9 3
3 2 1 3
3 4 5 6
5 1 7 5 8 9

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述

NEERC 以大量关于仙人掌的题目为特色——每条边属于至多一个简单环连通的无向图。直观的说，仙人掌是一种一些环被允许的广义树。

2005年，第一个有关仙人掌的问题出现，这个问题被简单的叫做[“仙人掌”](https://codeforces.com/gym/101334)。在2007年是[“仙人掌再来”](https://codeforces.com/gym/100273)，在2010年叫做[“仙人掌变革”](https://codeforces.com/gym/101309)，以及2013年是[“仙人掌自同构”](https://codeforces.com/gym/100307)。以下是这些问题中使用的仙人掌例子：

![](/upload/images2/cactus.png)

四年来评测必须为顶点以千数的仙人掌生成测试文件。当然，复杂性日益增加的大量数据发生器被建立，最终有一个被称为 CGL（Cactus Generator Language，仙人掌发生器语言）的领域特定语言。CGL 可以为测试的目的简洁地定义一个大仙人掌。本题中你要解析该语言的我们称为 SCGL（Simple Cactus Generator Language，简单仙人掌发生器语言）的一个简化版本，输出一个仙人掌作结果。

一个仙人掌要以列出边的极小集（覆盖全图的不同路径）输出。

SCGL 仙人掌定义的语法由语法中的指定的用下面的扩展巴科斯-诺尔范式的非终止图表示：

$$
\begin{aligned}
graph &= “\texttt{\textup{c}}”&&&&&&&&&&&&&&&&&&&&&&&&&&&\\
&| “\texttt{\textup{c(}}” list “\texttt{\textup{)}}”\\
&| “\texttt{\textup{loop(}}” list “\texttt{\textup{)}}”\\
&| “\texttt{\textup{t(}}” list “\texttt{\textup{)}}”\\
\end{aligned}
$$

$$
\begin{aligned}
list &= graph \{ “\texttt{\textup{,}}” graph \}&&&&&&&&&&&&\\
&|(number | range | variable ) [ “\texttt{\textup{,}}” graph ]\\
\end{aligned}
$$

$$
\begin{aligned}
&number = nzdig \{ “\texttt{\textup{0}}” | nzdig \}\\
&nzdig = “\texttt{\textup{1}}” | “\texttt{\textup{2}}” | \cdots | “\texttt{\textup{8}}” | “\texttt{\textup{9}}”\\
&range = “\texttt{\textup{range(}}” variable “\texttt{\textup{,}}” numvar “\texttt{\textup{,}}” numvar “\texttt{\textup{)}}”\\
&variable = “\texttt{\textup{A}}” | “\texttt{\textup{B}}” | \cdots | “\texttt{\textup{Y}}” | “\texttt{\textup{Z}}”\\
&numvar = number | variable
\end{aligned}
$$

一个图的制造规则表示一个有两个点标记的图——首和尾。图定义规则有以下语义：

- 基本建立块 $c$ 列表示一个仅有两个点（一首一尾）标记与一边的图。

- $c(σ)$ 规则对于含有 $n$ 个图的指定图列表 $σ$ 将第 $i$ 图尾顶点与第 $i+1$ 图首顶点合并，加入列表。（$i\in\mathbb{N}^*,1\le i< n$）结果图的首顶点为第一图首顶点，尾顶点为第 $n$ 图尾顶点。

- $loop(σ)$ 规则与 $c(σ)$相似，但第 $n$ 图尾顶点与第一图首顶点合并,加入列表。结果图的首尾顶点为列表中第一图首尾顶点。环仅可被应用于一图以上的列表。

- $t(σ)$ 规则连接一个指定图列表 $σ$，合并他们的首顶点。结果图的首尾顶点为列表中第一图首尾顶点。

图列表不是以一逗号分隔列表明确指定，就是用一个有一个数字、范围或变量的选择性地跟随一个逗号或图的可重列表指定。当一图非于一可重列表中明确指定，则该指定图被假定为 $c$。

最简单的可重列表用一个非终止数定义。它表示一个有指定整数个指定图的副本的列表。

一个可重范围列表由有三个组件（变量 $ν$，数字 $α$ 与 $β$）的 $range(ν, α, β)$ 规则定义。若 $ξ$ 字符序列为一图，则 $c|loop|t(range(ν, α, β), ξ)$ 被称为范围启用规则，变量 $ν$ 被称为 $ξ$ 中的一个约束变量。在一个范围启用规则的语境中，$ξ$ 被重复 $|β − α| + 1$ 次以建立列表。变量 $ν$ 于 $ξ$ 中的每次出现按升序由连续的 $α$ 与 $β$ 之间的整数（包括 $α$ 与 $β$）取代。 那产出一个包括 $|β −α|+ 1$ 个图的列表，通过相应的范围启用规则的规范连接。$α$ 与 $β$ 自身可能指被约束于外范围启用规则的变量。

在一个语法正确的图中：

- 每一个非终止变量（一个从 A 到 Z 的字母）作为 $range(ν, α, β)$ 规则中的 $ν$ 至多存在一次；

- 非终止变量的语法允许的所有其他事件被绑定。

注意，若一字符序列 $ξ$ 为一图，那么 $ξ, c(ξ), c(1 , ξ), t(ξ),$ 与 $t(1 , ξ)$ 都指此一图。另一方面，不论 $loop(ξ)$ 还是 $loop(1 , ξ)$ 都不被允许。

下列例子说明这些基本规则。这些图有以 F 与 L 相应标记的始末点。

![](/upload/images2/cactus1.png)

![](/upload/images2/cactus2.png)

### 输入格式

输入文件包含一行，含有一个 SCGL 定义。定义格式正确，总描述一仙人掌，每条边属于至多一个简单环，无重边。比如，$loop(3 , loop(3))$ 与 $loop(2)$ 都不可能。

输入文件中该行至多长 $1000$ 字符，定义的仙人掌至多 $50000$ 个顶点。由非终止数代列表的整数不超过 $50000$。
### 输出格式

输出文件第一行必须包含两个整数 $n$ 与 $m$。$n$ 为图顶点数。顶点由 $1$ 到 $n$ 编号，$1$ 为首点编号，$n$ 为图尾点编号。其他点可随意编号。图中边由一个边不重路径集代表，$m$为该集合最小路径数。

后 $m$ 行，每行必须包含图中一条路径。一条路径以一个整数 $k_{i} (k_{i} \ge 2)$ 开始，后随 $k_{i}$ 个整数从 $1$ 到 $n$。这 $k_{i}$ 个整数代列表一条路径的顶点。一条路径可经过同一顶点多次，但每条边必须在整个输出文件中刚好经过一次。

### 注释
此题中出现的的EBNF：

非终端符号为被定义的语言的句法部分。

终端符号为由一个或多个字符组成的序列，是构成语言的不可约元素。

本题中一条语法规则形如$元标识符=定义列表$

定义列表形如$主要句法|主要句法|\cdots$。

其中主要句法为可选序列、重复序列、分组序列、元标识符、终端字符串、空序列之一。

可选序列形如[定义列表]，重复序列形如{定义列表}，分组序列形如(定义列表)。

元标识符是以字母开头的字母数字序列，即非终端符号的名称。

由语法定义的语言的终端符号由终端字符串表示，终端字符串形如“一个或多个除该引号符号以外的任何终端字符的序列” 。

EBNF的终端符号称为终端字符，是字母、数字, 与`=|{}“()[]`字符之一。

需要注意的是，这里给出的EBNF不完整，但足以解决题目。


---

---
title: "[NEERC 2014] Damage Assessment"
layout: "post"
diff: 省选/NOI-
pid: P6988
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Damage Assessment
## 题目描述



A tank car that transports gasoline via rail road has a shape of cylinder with two spherical caps at the sides. The cylinder has a diameter $\(d\)$ and a length $\(l\).$ The spherical caps have a radius $\(r\) (\(2r\) \ge \(d\)).$ There was the rail road accident and the tank car had derailed. It now lies on the ground and some of the stored gasoline had flown out. The damage assessment must be performed. The location of the tank on the ground was established by measuring its tilt as the height difference $\(t\)$ from the bottom points of the cylinder on its left and right sides $(0 \le \(t\) \le \(l\)).$ The level of gasoline in the tank was established by measuring the height difference $\(h\)$ from the bottom point of the cylinder and the top level of gasoline. For the purpose of this problem, the top level of gasoline always intersects the cylinder part of the tank $(0 \le \(h\) \le \(t + d \sqrt{1 - (t/l)^2}).$

Your task is to figure out how much gasoline was left in the tank.

![](/upload/images2/dmaage.png)


## 输入格式



The input file consists of a single line with five integer numbers -- $\(d\), \(l\), \(r\), \(t\)$ and $\(h\),$ which represent the diameter and the length of the tank's cylinder part, the radius of its spherical caps, tilt and gasoline level measurements. They are all expressed in millimeters ($1$ millimeter $= 10^{−3}$ meters), they satisfy all constraints expressed in the problem statement and $\(d\), \(l\) \ge 100 , \(d\), \(l\), \(r\) \le 10 000$ .


## 输出格式



Write a single real number to the output file -- the volume of gasoline in the tank in liters ($1$ liter $= 10^{−3}$ cubic meters). The absolute error of the answer must not exceed $0$ . $1$ liters.


## 样例

### 样例输入 #1
```
3000 6000 1600 0 3000

```
### 样例输出 #1
```
50974.56

```
### 样例输入 #2
```
3000 6000 1600 3441 4228

```
### 样例输出 #2
```
40728.90

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

有一个由一个长度为 $l$，底面直径为 $d$ 的圆柱和两个半径均为 $r\ (2r\ge d)$ 的球形盖组成的油箱。由于一个交通事故，该油箱现在倾斜了一个角度，有一些汽油被洒了出来。现在给定圆柱底部的左右两个端点的高度差 $t\ (0\le t\le l)$ 以及剩余汽油的水平面到圆柱底端的距离 $h$，保证汽油的水平面一定与油箱的圆柱部分有交，即 $(0\le h\le t+d\sqrt {1-(t/l)^2})$。所有长度单位均用毫米给出。

求还剩下多少汽油（升），精确到 $0.1$。

$d,l\ge 100$，$d,l,r\le 10^4$。

下图为原题图。

![](https://cdn.luogu.com.cn/upload/image_hosting/465n22d6.png)


---

---
title: "[NEERC 2014] Epic Win!"
layout: "post"
diff: 省选/NOI-
pid: P6989
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Epic Win!
## 题目描述



A game of rock-paper-scissors is played by two players who simultaneously show out their moves: Rock, Paper , or Scissors. If their moves are the same, it's a draw. Otherwise, Rock beats Scissors, Paper beats Rock, and Scissors beat Paper .

The described procedure can be repeated many times. In this problem, two Finite State Machines (FSMs) will compete in a series of rounds. (Formally speaking, by FSMs we mean Moore machines in this problem. )

An FSM for playing rock-paper-scissors has finitely many states. Each state is described by the following: what move the FSM will make in the upcoming round, and what will be the new state in case of its opponent playing Rock, Paper , and Scissors.

![](/upload/images2/epic.png)

Fortunately, you know your opponent FSM -- the entire scheme except for one thing: you do not know the initial state of that FSM.

Your task is to design your own FSM to fight the given one. Your FSM must beat the opponent in at least $99\%$ of the first $1$ billion rounds. That's what we call an epic win!


## 输入格式



The input file contains a description of the opponent FSM in the following format.

The first line contains an integer $n (1 \le n \le 100)$ -- the number of states in the FSM. States are numbered from $1$ to $n$ . Each of the following $n$ lines contains a description of the state: a character $c_{i}$ denoting the move made by FSM and integers $r_{i}, p_{i}, s_{i}$ denoting the next state in case of seeing Rock, Paper, or Scissors respectively $(c_{i}$ can be `R`, `P`, or `S`; $1 \le r_{i}, p_{i}, s_{i} \le n$


## 输出格式



Write to the output the description of your FSM in the same format.

The initial state of your FSM is the first state.

The number of states may not exceed $50 000$ .


## 样例

### 样例输入 #1
```
2
R 1 1 2
P 2 2 1

```
### 样例输出 #1
```
2
P 1 2 1
S 1 1 1

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

**【题目描述】**

在游戏「石头、剪子、布」中，两名玩家分别同时出示自己的行动：*石头*、*剪子*、或*布*。如果两人的行动一致，则平局。否则*石头*打败*剪子*、*布*打败*石头*、*剪子*打败*布*。

上述过程可以重复多次。在本题中，两台有限状态自动机（Finite State Machines，FSM）将游玩多轮「石头、剪子、布」（准确地说，本题中的 FSM 特指 Moore 状态机）。

一台被设计用来游玩「石头、剪子、布」的 FSM 有着有限的状态。每个状态由以下信息描述：下一轮中本台自动机将会出示怎样的行动，以及当下一轮中对手出示了*石头*、*剪子*、或*布*时应该转移到的新状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/j121iya3.png)

幸运的是，你知道对手的 FSM：你知道它所有的结构，但唯独不知道它的初始状态。

你的任务是设计一台你自己的 FSM 去和对手的进行对战。你的 FSM 必须在前十亿（${10}^9$）轮中打败对手至少 $99 \%$ 轮。这就是所谓的史诗般的胜利（epic win）！

**【输入格式】**

从标准输入中读入对对手的 FSM 的描述，按如下格式：

第一行一个正整数 $n$，表示 FSM 中的状态数。所有状态从 $1$ 到 $n$ 编号。

接下来 $n$ 行，每行描述一个状态：一个字符 $c_i$ 以及三个正整数 $r_i, p_i, s_i$，分别表示该状态的行动、以及当对手出示了*石头*、*布*、或*剪子*后应该转移到的新状态的编号，其中 $c_i$ 只可能为 $\{\texttt{R}, \texttt{P}, \texttt{S}\}$ 之一，如果为 $\texttt{R}$ 则意味着行动为出示*石头*，如果为 $\texttt{P}$ 则意味着行动为出示*布*，如果为 $\texttt{S}$ 行动为出示*剪子*。

**【输出格式】**

将你设计的 FSM 以相同格式输出到标准输出中。

你的 FSM 的初始状态是 $1$ 号状态。

你的 FSM 的状态数量不应超过 $50000$。

**【样例解释】**

题目描述中的图片显示了样例输入中给出的对手的 FSM，以及样例输出中给出的一个你的 FSM。

对手的 FSM 持续出示*石头*或*布*（取决于初始状态）直到它接收到*剪子*：接收到*剪子*将导致它的行为改变。

一种打败这样的 FSM 的方法是出示*布*。如果对手持续出示*石头*，只需继续出示*布*即可胜利。如果对手出示了*布*，通过出示一次*剪子*让它的行为改变，接下来它就会持续出示*石头*，然后你就可以用*布*打败它了。

**【数据范围】**

对于全部数据，$1 \le n \le 100$，$c_i \in \{\texttt{R}, \texttt{P}, \texttt{S}\}$，$1 \le r_i, p_i, s_i \le n$。

**翻译来源**：IOI 2021 集训队第一部分作业，PinkRabbit。


---

---
title: "[NEERC 2014] Gomoku"
layout: "post"
diff: 省选/NOI-
pid: P6991
tag: ['2014', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Gomoku
## 题目背景

这是一道 IO 交互题。
## 题目描述



This is an interactive problem.

Gomoku is a two-player game on a two-dimensional grid. Each cell of the grid can be either empty, contain the first player's mark $(black),$ or contain the second player's mark $(white),$ but not both. Initially the entire grid is empty. Two players make alternating moves, starting with the first player. At each move, a player can put her mark into exactly one empty cell. The first player to have her five adjacent marks in a single row wins. The winning row can be either vertical, horizontal or diagonal.

![](https://upload.acmicpc.net/23c94254-2783-405a-907b-7b66bea5514b/-/preview/)

Position where the second player (white marks) had won.

The players use a $19 \times 19$ grid in this problem. If the entire grid gets filled with marks but no player has won, the game is declared a draw.

The first player uses the following strategy: as the first move, she puts her mark into the center cell of the grid. At every other move, she picks such a move that maximizes the score of the resulting position.

In order to find the score of a position, the first player considers all possible places where the winning combination might eventually form -- in other words, all horizonal, vertical and diagonal rows of five consecutive cells on the board (of course, they may overlap each other). If such a row contains both the first player's marks and the second player's marks, it is disregarded. If such a row contains no marks, it is disregarded as well. For each row with exactly $k (1 \le k \le 5)$ marks of the first player and no marks of the second player, add $50^{2k−1}$ to the score of the position. For each row with exactly $k$ marks of the second player and no marks of the first player, subtract $50^{2k}$ from the score of the position. Finally, add a random integer number between $0$ and $50^{2} − 1$ to the score. This random number is chosen uniformly.

In case when several moves of the first player have equal scores (such ties are quite rare because of the random addition mentioned above), the first player picks the one with the smallest x-coordinate, and in case of equal x-coordinates, the one with the smallest y-coordinate.

Your task is to write a program that plays the second player and beats this strategy.

Your program will play $100$ games against the strategy described above, with different seeds of random generator. Your program must win all these games.


## 输入格式




## 输出格式




## 样例

### 样例输入 #1
```
10 10
10 11
10 12
10 13
9 10
9 11
9 9
11 13
-1 -1

```
### 样例输出 #1
```
11 10
11 11
10 9
10 14
8 9
11 9
11 12
11 8

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

这是一道交互题。

五子棋是一种两个人在二维棋盘上玩的游戏。棋盘上的每个格子可以为空，放有第一名玩家的棋子（黑），或者放有第二名玩家的棋子（白），但是不能都有。初始时所有的格子都是空的。两个玩家轮流操作，从第一名玩家开始。每次操作，一名玩家可以把他的棋子放进恰好一个空格子里。首先在一行中放下五个相邻棋子的玩家获胜。一行可以是横行、竖行或对角线。

![1.png](https://upload.acmicpc.net/23c94254-2783-405a-907b-7b66bea5514b/-/preview/)

*第二名玩家（白子）获胜的一种情况。*

在这个问题中，玩家们使用 $19 \times 19$ 的棋盘。如果整个棋盘都放满了棋子但无人获胜，游戏平局。

第一名玩家将会使用下面的策略：第一次操作时，她会把她的棋子放到棋盘的正中间。在后面的每次操作中，她会选择一个下子后局面分数最大的位置下子。

为了计算一个局面的分数，第一名玩家会考虑能组成胜利组合的所有地方——换句话说，棋盘上所有横行、竖行、对角线上五个连续的格子（当然，它们会互相重叠）。如果这一行同时包括了第一名玩家的棋子和第二名玩家的棋子，就无视它。如果这一行包括了恰好 $k\ (1\le k\le 5)$ 个第一名玩家的棋子而没有第二名玩家的棋子，给该局面的分数加上 $50^{2k-1}$。如果这一行包括了恰好 $k$ 个第二名玩家的棋子而没有第一名玩家的棋子，给该局面的分数减去 $50^{2k}$。最后，给分数加上一个 $0$ 到 $50^2-1$ 的随机数。随机数是均匀分布的。

如果第一名玩家有多个分数相同的格子可选（因为上面提到的随机分数的原因，这是非常罕见的），第一名玩家选择 X 坐标最小的位置，如果仍有多个格子有相同的 X 坐标，就选择 Y 坐标最小的位置。

你的任务是，写一个程序扮演第二名玩家，并打败上述的策略。

你的程序将会与上述策略对局 $100$ 局，每局的随机数种子不同。你的程序必须在每局中都获胜。

### 交互格式

每一步你的程序需要做：

1. 从标准输入读入两个整数 $x,y$。
2. 如果都是 $-1$，那么游戏结束，你的程序必须退出。
3. 否则这两个整数描述了第一名玩家下子的坐标，$1\le x,y\le 19$。
4. 输出第二名玩家下子的坐标，然后换行。别忘了清空缓冲区。

### 样例

在下面的样例中，第一名玩家**没有**使用题目描述中所述的策略。这个样例只是为了说明交互格式。

![2.png](https://s1.ax1x.com/2020/10/29/B8voct.png)

*样例最终的棋盘状态。*

### 说明

世界上有很多种不同的五子棋规则。请只考虑题目描述中说明的这一种规则。


---

---
title: "[NEERC 2014] Hidden Maze"
layout: "post"
diff: 省选/NOI-
pid: P6992
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Hidden Maze
## 题目描述



Helen and Henry are fans of the TV show `Hidden Maze`, which is very popular in Hiddenland. During this show two participants (usually a married couple) are rushing through the maze consisting of $n$ halls connected by some tunnels. Each tunnel connects two different halls and there can't be more than one tunnel connecting any pair of halls.

In the beginning of the show, two participants are placed in two different halls. Then they need to move very quickly to meet each other before the time runs out. To pass through each tunnel, the participant needs to find a clue which is some positive integer number written on a small piece of paper.

If the participants finally meet in some tunnel before the time runs out, and successfully find a clue contained in the tunnel where they met, they are considered winners. The value of their prize is calculated by sorting all the clues found by them and taking the median value. The game is always set up in such a way, that the number of clues they find is odd.

Helen and Henry saw a large number of episodes of the show, and now they understand a lot about the mechanics of it. They noticed that the maze doesn't change between episodes, and they drew a complete map of the maze. Shortly after, Helen and Henry have discovered that the maze is built in such a manner that if you visit any tunnel at most once, then there is exactly one path between any two halls.

Helen and Henry have been wondering how this great maze is created, and not so long time ago they have seen an interview with Hillary, who worked for the company which had built the maze. Hillary has told that to make the show fair, the maze had been created using the following randomized algorithm:

Pick the number of halls $n$ . Build $n$ halls enumerated from $1$ to $n$ .

Choose at random two integers $i$ and $j$ , each of them uniformly distributed between $1$ and $n$ .

If halls $i$ and $j$ are the same or are already connected with some path of tunnels, then go to step $2$ .

Build the tunnel between $i$ and $j$ . If there is a path of tunnels from any hall to any other one, stop the process, otherwise go to step $2$ .

Helen and Henry have also noticed that each tunnel contains exactly one clue and its value never changes from episode to episode. However, they don't know what algorithm was used to generate clue values. Helen and Henry have written on their map the value of the clue for each tunnel.

It always takes $1$ minute to find a clue and to run through the tunnel from one hall to another. It takes half a minute to run from the hall to the center of the tunnel when the participants meet in the center of the tunnel at the end. The time given to participants is only enough to meet each other if they act optimally, that is they just run to each other via the shortest possible path, never make mistakes when finding clues, and never turn into any other tunnels that do not belong to the shortest path. To make the participants meet in the center of some tunnel, they are placed in the beginning of the show in such a way that the length of the shortest path between the halls where they are placed is odd.

Helen and Henry want to participate in the show. They know the maze by heart and they are pretty sure that they will succeed in moving optimally to each other and finding all clues in time. Provided that the pair of initial halls is selected uniformly from all pairs with an odd-length shortest path between them, they need to know the expected value of the prize they win. Your task is to help them find this expected value.


## 输入格式



The first line of the input contains an integer number $n (2 \le n \le 30 000)$ -- the number of halls. Each of the following $n − 1$ lines contains three integers: $u_{i}, v_{i}, c_{i} (1 \le u_{i}, v_{i} \le n , 1 \le c_{i} \le 10^{6}),$ describing the i-th tunnel connecting the halls $u_{i}$ and $v_{i},$ containing the clue with the value $c_{i}.$ The maze is always created by the randomized algorithm that is specified in the problem statement.


## 输出格式



Write to the output file a single real number -- the expected value of the prize. The absolute or relative error of the answer must not exceed $10^{−9}.$


## 样例

### 样例输入 #1
```
2
2 1 1

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
5
2 4 4
1 2 5
5 4 2
5 3 3

```
### 样例输出 #2
```
3.50

```
### 样例输入 #3
```
5
4 1 2
5 3 2
4 2 3
5 4 7

```
### 样例输出 #3
```
3.1666666667

```
## 题目翻译

给定一个 $n$ 个点的随机生成的无根树，每条边有正整数边权。每次随机两个最短路径边数为奇数的点，将这两点间路径上边权的中位数作为贡献。求这个贡献的期望。  

by a___


---

---
title: "[NEERC 2014] Improvements"
layout: "post"
diff: 省选/NOI-
pid: P6993
tag: ['2014', 'ICPC']
---
# [NEERC 2014] Improvements
## 题目描述



Son Halo owns $n$ spaceships numbered from $1$ to $n$ and a space station. They are initially placed on one line with the space station so the spaceship $i$ is positioned $x_i$ meters from the station and all ships are on the same side from the station $(x_i > 0)$ . All $x_i$ are distinct. Station is considered to have number $0$ and $x_0$ is considered to be equal to $0$ .

Every two spaceships with consequent numbers are connected by a rope, and the first one is connected to the station. The rope number $i$ (for $1 \le i \le n)$ connects ships $i$ and $i-1.$ Note, that the rope number $1$ connects the first ship to the station.

Son Halo considers that the rope $i$ and the rope $j$ intersect when the segments $[x_{i}^{min}, x_{i}^{max}]$ and $[x_{j}^{min}, x_{j}^{max}]$ have common internal point but neither one of them is completely contained in the other, where $x_{k}^{min} = \min(x_{k−1}, x_k)$, $x_{k}^{max} = max(x_{k−1}, x_k).$ That is:

$$\begin{cases} x_{i}^{min} < x_{j}^{min} \sim \& \sim x_{j}^{min} < x_{i}^{max} \sim \& \sim x_{i}^{max} < x_{j}^{max} \\ x_{j}^{min} < x_{i}^{min} \sim \& \sim x_{i}^{min} < x_{j}^{max} \sim \& \sim x_{j}^{max} < x_{i}^{max}  \end{cases}$$

Son Halo wants to rearrange spaceships in such a way, that there are no rope intersections. Because he is lazy, he wants to rearrange the ships in such a way, that the total number of ships that remain at their original position $x_i$ is maximal. All the ships must stay on the same side of the station and at different positions $x_i$ after rearrangement. However, ships can occupy any real positions $x_i$ after rearrangement.

Your task is to figure out what is the maximal number of ships that can remain at their initial positions.


## 输入格式



The first line of the input file contains $\(n\) (1 \le \(n\) \le 200 000)$ -- the number of ships. The following line contains $\(n\)$ distinct integers $\(x_i\) (1 \le \(x_i\) \le \(n\))$ -- the initial positions of the spaceships.


## 输出格式



The output file must contain one integer -- the maximal number of ships that can remain at their initial positions in the solution of this problem.


## 样例

### 样例输入 #1
```
4
1 3 2 4

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
4
1 4 2 3

```
### 样例输出 #2
```
4

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

一个数轴上有 $n$ 个位置互异的点，第 $i$ 个点的坐标为 $x_i\ (x_i \gt 0)$，第 $i$ 个点和第 $i - 1$ 个点连了一根绳子（第 $1$ 个点和原点连了根绳子）定义两根绳子有交当且仅当它们跨越的区间有交且不是包含关系。你可以改变若干个点的坐标到一个任意的正实数位置，使得最后不存在任何两根绳子有交。最大化不动的点的个数。

$n\le 2\times 10^5$，$x_i$ 构成一个 $1,2,\cdots,n$ 的排列。


---

---
title: "[NEERC 2013] Cactus Automorphisms"
layout: "post"
diff: 省选/NOI-
pid: P6998
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Cactus Automorphisms
## 题目描述



NEERC had featured a number of problems in previous years about cactuses -- connected undirected graphs in which every edge belongs to at most one simple cycle. Intuitively, cactus is a generalization of a tree where some cycles are allowed.

In $2005$ , the first year where problems about cactuses had appeared, the problem was called simply `Cactus`. In $2007$ it was `Cactus Reloaded` and in $2010$ it was called `Cactus Revolution`. An example of cactus from NEERC $2007$ problem is given on the picture below.

![](/upload/images2/cac.png)

The challenge that judges face when preparing test cases for those problems is that some wrong solutions may depend on the numbering of vertices in the input file. So, for the most interesting test cases judges typically include several inputs with the same graph, but having a different numbering of vertices. However, some graphs are so regular that the graph remains the same even if you renumber its vertices. Judges need some metric about the graph that tells how regular the given graph is in order to make an objective decision about the number of test cases that need to be created for this graph.

The metric you have to compute is the number of graph automorphisms. Given an undirected graph $(V , E)$ , where $V$ is a set of vertices and $E$ is a set of edges, where each edge is a set of two distinct vertices ${v_{1}, v_{2}} (v_{1}, v_{2} ∈ V ),$ graph automorphism is a bijection $m$ from $V$ onto $V$ , such that for each pair of vertices $v_{1}$ and $v_{2}$ that are connected by an edge (so ${v_{1}, v_{2}} ∈ E)$ the following condition holds: ${m(v_{1}), m(v_{2})} ∈ E$ .

Each graph has at least one automorphism (one where $m$ is an identity function) and may have up to $n$ ! automorphisms for a graph with $n$ vertices. Because the number of automorphisms may be a very big number, the answer must be presented as a prime factorization $∏^{k}_{i=1} p_{i}^{q_{i}},$ where $p_{i}$ are prime numbers in ascending order $(p_{i} \ge 2 , p_{i} 0)$ .


## 输入格式



The first line of the input file contains two integer numbers $n$ and $m (1 \le n \le 50 000 , 0 \le m \le 50 000)$ . Here $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$ . Edges of the graph are represented by a set of edge-distinct paths, where $m$ is the number of such paths.

Each of the following $m$ lines contains a path in the graph. A path starts with an integer number $k_{i} (2 \le k_{i} \le 1000)$ followed by $k_{i}$ integers from $1$ to $n$ . These $k_{i}$ integers represent vertices of a path. Adjacent vertices in a path are distinct. Path can go to the same vertex multiple times, but every edge is traversed exactly once in the whole input file. There are no multiedges in the graph (there is at most one edge between any two vertices).

The graph in the input file is a cactus.


## 输出格式



On the first line of the output file write number $k$ -- the number of prime factors in the factorization of the number of graph automorphisms. Write $0$ if the number of graph automorphisms is $1$ . On the following $k$ lines write prime numbers $p_{i}$ and their powers $q_i$ separated by a space. Prime numbers must be given in ascending order.


## 样例

### 样例输入 #1
```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10

```
### 样例输出 #1
```
1
2 2

```
### 样例输入 #2
```
2 1
2 1 2

```
### 样例输出 #2
```
1
2 1

```
### 样例输入 #3
```
15 7
3 1 2 3
3 4 2 5
3 6 2 7
3 8 2 9
3 10 2 11
3 12 2 13
3 14 2 15

```
### 样例输出 #3
```
6
2 11
3 5
5 2
7 2
11 1
13 1

```
## 提示

Time limit: 5 s, Memory limit: 256 MB. 


## 题目翻译

- **仙人掌**是满足如下条件的无向简单连通图：每条边被包含于至多一个简单环中。
- 设有无向图 $G=(V,E)$。称双射 $f:V\rightarrow V$ 是 $G$ 的**自同构**，当且仅当 $\forall v_1,v_2\in V$，都有 $(v_1,v_2)\in E\Leftrightarrow (f(v_1),f(v_2))\in E$。称两个自同构 $f_1,f_2$ 相同，当且仅当 $\forall v\in V$ 均有 $f_1(v)=f_2(v)$。
- 给定有 $n$ 个节点的仙人掌，求它的不同的自同构数。由于结果可能很大，你需要输出它的质因子分解的结果。
- 输入仙人掌的方式为：给定 $m$ 条路径，这些路径所覆盖的边即为仙人掌的全部边。保证这些路径不会重复经过一条边两次，且输入的图是仙人掌。
- $n,m\leq 5\times 10^4$。


---

---
title: "[NEERC 2013] Dictionary"
layout: "post"
diff: 省选/NOI-
pid: P6999
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Dictionary
## 题目描述



Petr and Dmitry are working on a novel data compression scheme. Their task is to compress a given set of words. To compress a given set of words they have to build a rooted tree. Each edge of the tree is marked with exactly one letter.

Let us define a dictionary that is produced by this kind of tree as a set of words that can be constructed by concatenating letters on edges on any path from any vertex in the tree (not necessarily root) and going away from root down to the leaves (but not necessarily finishing on a leaf).

Boys have to construct such a tree with a dictionary that is a superset of the set of words that they are given to compress. This tree should have the smallest number of vertices between trees that satisfy the above condition. Any tree with the same number of vertices will do. Your task is to help them.

![](/upload/images2/dict.png)

For example, in a tree on the picture above with the root marked as $1$ , a path from $7$ to $5$ reads `north`, a path from $16$ to $12$ reads `eastern`, a path from $29$ to $2$ reads `european`, a path from $3$ to $25$ reads `regional`, and a path from $1$ to $31$ reads `contest`.


## 输入格式



The first line of the input file contains the number of words in a given set $n (1 \le n \le 50)$ . The following $n$ lines contain different non-empty words, one word per line, consisting of lowercase English letters. The length of each word is at most $10$ characters.


## 输出格式



On the first line output the number of vertices in the tree $m$ . The following $m$ lines shall contain descriptions of tree vertices, one description per line. Vertices are indexed from $1$ to $n$ in the order of their corresponding description lines. If the corresponding vertex is a tree root, then its description line shall contain a single integer number $0$ , otherwise its description line shall contain an index of its parent node and a letter on the edge to its parent node, separated by a space.


## 样例

### 样例输入 #1
```
5
north
eastern
european
regional
contest

```
### 样例输出 #1
```
31
0
7 n
2 o
18 t
4 h
29 e
17 a
7 s
8 t
9 e
10 r
11 n
6 u
13 r
14 o
15 p
16 e
3 r
18 e
19 g
20 i
21 o
22 n
23 a
24 l
1 c
26 o
27 n
28 t
6 s
30 t

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

## 题目描述

Petr和Dmitry正在研究一种新的数据压缩方案。他们的任务是压缩一组给定的单词。为了压缩给定的一组单词，他们必须建立一个有根的树。这棵树的每一个边缘都有一个字母。

让我们定义一个由这种树生成的字典，它是一组单词，可以通过在树的任何顶点（不一定是根节点）的任何路径上的边上连接字母，从根向下到叶子（但不一定在叶节点上完成）来构造。

男孩们必须用字典来构造这样一棵树，字典是一组单词的超集，他们被给予压缩。满足上述条件的树之间的顶点数应该最小。任何具有相同顶点数的树都可以。你的任务是帮助他们。

例如，上图中的一棵树的根标记为1，从7到5的路径表示north，从16到12的路径表示eastern，从29到22的路径表示european，从3到25的路径表示regional，从1到31的路径表示contest。

## 输入格式
第一行是一个数字n（0<n<50）
接下来n行都是一个长度小于10的字符串

## 输出格式
在第一行输出树中的顶点数m。每行树应包含一行描述的顶点。顶点按其相应描述行的顺序从1索引到n。如果对应的顶点是树根，则其描述行应包含单个整数0，否则其描述行应包含其父节点的索引和父节点边缘上的字母，用空格隔开。


---

---
title: "[NEERC 2013] Easy Geometry"
layout: "post"
diff: 省选/NOI-
pid: P7000
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Easy Geometry
## 题目描述



Eva studies geometry. The current topic is about convex polygons, but Eva prefers rectangles. Eva's workbook contains drawings of several convex polygons and she is curious what is the area of the maximum rectangle that fits inside each of them.

![](/upload/images2/eg.png)

Help Eva! Given the convex polygon, find the rectangle of the maximum possible area that fits inside this polygon. Sides of the rectangle must be parallel to the coordinate axes.


## 输入格式



The first line contains a single integer $n$ -- the number of sides of the polygon $(3 \le n \le 100 000)$ . The following $n$ lines contain Cartesian coordinates of the polygon's vertices -- two integers $x_{i}$ and $y_{i} (-10^{9} \le x_{i}, y_{i} \le 10^{9})$ per line. Vertices are given in the clockwise order.

The polygon is convex.


## 输出格式



Output four real numbers $x_{mi_n}, y_{mi_n}, x_{max}$ and $y_{max}$ -- the coordinates of two rectangle's corners $(x_{mi_n} < x_{max}, y_{mi_n} < y_{max}).$ The rectangle must fit into the polygon and have the maximum possible area.

The absolute precision of the coordinates should be at least $10-^{5}.$

The absolute or relative precision of the rectangle area should be at least $10^{-5}.$ That is, if $A'$ ; is the actual maximum possible area, the following must hold: $mi_n(|A-A'|,|A−A'|/A') ) \le 10^{-5}.$


## 样例

### 样例输入 #1
```
4
5 1
2 4
3 7
7 3

```
### 样例输出 #1
```
3.5 2.5 5.5 4.5

```
### 样例输入 #2
```
5
1 1
1 4
4 7
7 4
7 1

```
### 样例输出 #2
```
1 1 7 4

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

**一句话题意：** 

给你一个凸 $n$ 边形，并按顺时针给出每一个顶点的坐标，求出在这个凸 $n$ 边形之内的面积最大的一个边平行坐标轴的矩形的四个顶点。

**输入格式：**

第一行是一个正整数 $n$ ，且 $3\le n \le 100000$ 。

接下来 $n$ 行，每行两个整数 $x$ ， $y$ ，代表一个顶点的 $x$ 坐标和 $y$ 坐标。 $-10^9 \le x,y \le 10^9$ 。

**输出格式：**

输出四个整数 $x_{min},y_{min},x_{max},y_{max}$ ，代表你给出的这个面积最大的矩形。其中 $x_{min} \le x_{max} $ ， $y_{min} \le y_{max} $ 。

精度要求：如果 $A$ 是你算出的值， $A'$ 是真实的最大面积，那么你需要保证 $min( |A-A'|,|A-A'|/A') \le10^{-5}$ 。


---

---
title: "[NEERC 2013] Interactive Interception"
layout: "post"
diff: 省选/NOI-
pid: P7004
tag: ['2013', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Interactive Interception
## 题目描述

This is an interactive problem.

North Eastern Emergency Rocket Control agency (NEERC) has developed a new radar control system that is designed to better control ballistic rocket interception. To test the new system NEERC agency had developed a mathematical model that is intended to show this system’s abilities.

Let us represent a rocket as a point on a line. Initially the point is at some unknown integer location between $0$ and $p$, inclusive. It has some unknown speed of $q$ which is an integer between $0$ and $v$, inclusive.

Each second the following happens. First, the control system makes a query to the radar of a form “`check L R`” and gets an answer whether the point is currently between $L$ and $R$, inclusive, or not.

After that, the point’s coordinate increases by $q$.

The goal of the radar control system is to learn the exact location of the point at the beginning of some second. When it does learn the point’s location, then instead of making a query to the radar, it gives a command to intercept the point at that location.

You have to implement the control system that locates and intercepts the point while making at most $100$ queries to the radar.

### Interaction protocol
Interaction starts with your program reading two integers — the values of $p$ and $v$ from the standard input($1\leq p\leq 10^5$,$1\leq v\leq 10^5$).

After that your program must print commands to the standard output. Each command must be one of the following two.

- “`check L R`” — make a query to the radar to get an answer whether the point is currently between $L$ and $R$, inclusive, or not. The answer must be read from the standard input and is either “`Yes`” or “`No`”. After that the point’s coordinate is increased by $q$. $L$ and $R$ must be integers.
- “`answer x`” — the exact coordinate $x$ of the point is known, and you order to intercept the point. After printing this command your program must exit.

Your program must write end-of-line sequence and flush the standard output after each command, including the last command “`answer x`” (end-of-line must be written and flushed before exiting).


## 样例

### 样例输入 #1
```
2 2
Yes
No
Yes
Yes
```
### 样例输出 #1
```
check 1 3
check 3 5
check 2 4
check 4 5
answer 5
```
## 提示

In the given example the point was initially at location $1$ and is moving at a speed $q = 1$.
## 题目翻译

**这是一道交互题**。

平面上有一个点，初始位置 $x\in[0,p]$，速度 $q\in[0,v]$，其中 $p,v$ 是给定的。

你可以进行不超过 $100$ 次询问，形如 ``check L R``，满足 $0\le L\le R\le 10^9$，交互库会告诉你是否有 $x\in[L,R]$，每次询问之后，交互库会令 $x\gets x+q$。你需要在某个询问后确定此时的 $x$，并告诉交互库，格式形如 ``answer x``。

$1\le p,v\le 10^5$。


---

---
title: "[CERC2013] Rubik's Rectangle"
layout: "post"
diff: 省选/NOI-
pid: P7007
tag: ['2013', 'Special Judge', 'ICPC']
---
# [CERC2013] Rubik's Rectangle
## 题目描述

A new puzzle which aims to conquer the game market is a fusion of Rubik's Cube and Fifteen. The board is an $H \times W$ frame with tiles with all numbers from $1$ to $H · W$ printed on them.

![](/upload/images2/rubik1.png)

The only type of move that is allowed is flipping either one of the rows or one of the columns. Flipping reverses the order of the row's (or column's) elements. Below the third row is flipped:

![](/upload/images2/rubik2.png)

You are given a board with tiles numbered in some arbitrary order. Determine a sequence of flips that brings the board to the nicely sorted position, if possible.

![](/upload/images2/rubik3.png)


## 输入格式

The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

The description of each test case starts with an empty line. The next line contains two space-separated integers $W$ and $H (1 \leq W,H \leq 100) -$ the width and height of the puzzle, respectively. Each of the next $H$ lines contains $W$ space-separated integers $-$ the numbers printed on consecutive tiles.


## 输出格式

Print the answers to the test cases in the order in which they appear in the input. Start the output for each test case with the word POSSIBLE or IMPOSSIBLE, depending on whether it is possible to solve the puzzle. If a solution exists, print (in the same line) first the number of moves (possibly $0$) and then their descriptions, each consisting of a single letter $R$ or $C$ specifying whether we are to flip a row or a column, concatenated with the index of the row or column to flip.

Any solution will be accepted as long as it does not use more than $10 · W · H$ moves. Each test case is either solvable within this limit, or not solvable at all.


## 样例

### 样例输入 #1
```
4

3 3
1 2 3
4 5 6
9 8 7

4 2
1 2 3 4
5 6 7 8

4 4
1 2 15 4
8 7 11 5
12 6 10 9
13 14 3 16

3 4
1 2 4
3 5 6
7 8 9
10 11 12

```
### 样例输出 #1
```
POSSIBLE 1 R3
POSSIBLE 0
POSSIBLE 3 R3 C3 R2
IMPOSSIBLE

```
## 提示

Time limit: 6 s, Memory limit: 128 MB. 


## 题目翻译

有一个 $h\times w$ 的棋盘，每个位置上有一个在 $[1,h\times w]$ 的整数，且没有重复。每次操作可以翻转一行或一列（顺序上翻转）。

每个测试点共有 $T$ 组数据，每组数据都有 $h,w$ ，以及给定的 $h$ 行 $w$ 列的矩阵，要求对于每组数据，输出一行一个操作序列，使得操作后矩阵满足从上到下，从左到右递增。

如果无解，输出 `IMPOSSIBLE`。

如果有解，先输出 `POSSIBLE`，再输出操作序列的长度，然后输出操作序列。如果翻转第 $i$ 行，输出 `Ri`。如果翻转第 $i$ 列，输出 `Ci`，用空格隔开，中间不换行。

本题有 Special Judge, 操作序列长度不能超过 $10hw$。

$h,w \le 100$。


---

---
title: "[CERC2013] Escape"
layout: "post"
diff: 省选/NOI-
pid: P7011
tag: ['2013', 'ICPC']
---
# [CERC2013] Escape
## 题目描述



You hit the emperor lich with full force and slay it. There is a stair leading upwards here. You climb upstairs. You drink from the pool. You feel much better. The karmic lizard punches through your armor and hits you. You die...

After an epic fight with the emperor lich, the hero struggles to escape the dungeon consisting of $n$ chambers and $n − 1$ corridors connecting them. He starts in chamber number $1$ and must reach chamber number $t$ , moving only along the corridors. All chambers are reachable from chamber number $1$ . Bruised after the last fight, the hero starts the journey with $0$ hit-points $(HP).$ These points represent his health $-$ if ever they fall below zero, the hero's story ends there as a tragic one.

In some chambers there are monsters $-$ a monster must be fought, and it always manages to take some of the hero's HP. In some other chambers there are magic pools $-$ every pool restores some number of the hit-points. There is no upper limit on the hero's health. Every chamber can be visited multiple times, but the gain or loss of HP happens only once, on the very first visit.

Determine whether the hero can escape the dungeon alive.


## 输入格式



The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

The first line of each test case contains two integers: the number of chambers $n , 2 \le n \le 200 000$ , and the number of the exit chamber $t , 2 \le t \le n$ . The second line contains $n$ space separated integers between $-10^{6}$ and $10^{6} -$ the i-th of them denotes the HP gain in the i-th chamber (negative denotes a monster, positive $-$ a pool, and zero means that the chamber is empty). The first chamber does not contain a monster, but a pool is possible there. The exit chamber may contain a pool or a monster, and the monster will have to be fought before escaping.

The next $n−1$ lines contain the descriptions of corridors. Each one contains a pair of integers $-$ the ends of a corridor.


## 输出格式



For each test case print a single line containing the word escaped if escape is possible, or trapped otherwise.


## 样例

### 样例输入 #1
```
2
7 7
0 -3 2 2 3 -4 0
1 2
2 3
2 4
1 5
5 6
6 7
3 2
3 3 -4
1 3
2 3

```
### 样例输出 #1
```
escaped
trapped

```
## 提示

Time limit: 8 s, Memory limit: 128 MB. 


## 题目翻译

### 题目背景

在经历和巫妖王史诗级别的战斗后，英雄们想要从地牢中逃走。

### 题目描述

这个地牢是由 $n$ 个房间和 $n-1$ 条走廊连接组成的树状结构，英雄一开始在 $1$ 号房间，而且他只有抵达 $t$ 号房间才能逃离这个地牢。从 $1$ 号房间出发可以抵达任何一个其它的房间，可惜的是，在经历激烈的战斗后，英雄的精力使用完了，所以一开始该英雄的精力为 $0$，并且一旦英雄的精力低于 $0$，那么英雄就会当场逝世，以悲剧结束。在这些房间中，里面暗藏玄机，里面可能有怪兽，也有可能是可以补充精力的魔泉，当然也可能什么也没有，如果是怪兽，那么英雄就必须与它战斗从而消耗一些精力，如果是魔泉，那么英雄可以补充自己的精力。所有的怪兽只会战斗一次，所有的魔泉只能使用一次。（换句话说就是所有的精力的上升或者下降只会发生在第一次访问这个房间的时候）

英雄的精力没有上限，每一个房间都可以反复走多次。

### 输入格式

输入包括多组数据，第一行表示测试的数据的组数 $T$。

每一个测试用例的第 $1$ 行都包括两个整数 $n$ $(2 \le n \le 200000 )$ 和 $t$ $(2 \le t \le n)$，分别表示地牢的房间的数量和英雄必须到达的房间号。第二行是 $n$ 个整数，代表了 $n$ 个房间的情况，其中第 $i$ 个数代表了第 $i$ 个房间情况，所有的数的绝对值都不大于 $10^{6}$。如果该数是负数，表明该房间里面有怪兽，精力会减少，如果是正数，表明房间里面有魔泉，可以补充精力，如果是 $0$，表明房间里面空空如也。注意 $1$ 号房间不会有怪兽，但是有可能会有魔泉，$t$ 号房间可能怪兽或者魔泉，如果是怪兽，那么英雄必须要击败怪兽才能逃离。

在接下来的 $n-1$ 行中，每行两个整数 $a$ 和 $b$ ，表示房间 $a, b$ 之间有一条走廊连接。

### 输出格式

对于每一个测试用例都单行输出：

如果英雄能够逃脱，那么输出 `escaped`，否则输出 `trapped`。


---

---
title: "[CERC2013] History course"
layout: "post"
diff: 省选/NOI-
pid: P7013
tag: ['2013', 'Special Judge', 'ICPC']
---
# [CERC2013] History course
## 题目描述

You are to give a series of lectures on important historical events, one event per lecture, in some order. Each event lasted for some time interval $[a_i, b_i].$ We say that two events are related if their intervals have a common point. It would be convenient to schedule lectures on related events close to each other. Moreover, lectures on unrelated events should be given in the order in which the events have taken place (if an event A preceded an unrelated event $B$ , then the lecture on A should precede the lecture on $B)$ .

Find the minimum integer $k \ge 0$ and an order of the lectures such that any two related events are scheduled at most $k$ lectures apart from each other (lectures number $i$ and $j$ are considered to be $|i−j|$ lectures apart).
## 输入格式


The first line of input contains the number of test cases $t$ . The descriptions of the test cases follow:

The first line of each test case contains the number $n (1 \le n \le 50000)$ . Each of the next $n$ lines contains two integers $a_i$ and $b_i (-10^9  \le a_i \le b_i \le 10^9) $ - the ends of the i-th interval. The intervals are pairwise different.
## 输出格式


Print the answers to the test cases in the order in which they appear in the input. The first line of the answer to each test case should contain the minimum value of $k$ . The next $n$ lines should list the intervals (in the same format as in the input) in an order such that any two related events are scheduled at most $k$ lectures apart. Remember to put any unrelated intervals in the proper order! 
## 样例

### 样例输入 #1
```
1
3
1 6
2 3
4 5

```
### 样例输出 #1
```
1
2 3
1 6
4 5

```
## 提示

Time limit: 10 s, Memory limit: 128 MB. 

感谢 [hht2006](/user/175829) 提供的 Special Judge。
## 题目翻译

给定 $n$ 个区间，第 $i$ 个区间为 $[a_i,b_i]$。你需要把这些区间按某种顺序排列，使得两个区间如果没有交点，则左端点更小的区间需要排在前面。

设第 $i$ 个区间排在第 $p_i$ 个位置，定义区间 $i$ 与 $j$ 之间的距离为 $|p_i-p_j|$。令 $k$ 为任意两个相交的区间之间的最大距离，你需要最小化 $k$，并输出一组对应的合法顺序。

对于 $100\%$ 的数据，满足 $1\leq n\leq 5\times 10^4$，$0\leq|a_i|,|b_i|\leq10^9$。


---

---
title: "[CERC2013] Chain & Co."
layout: "post"
diff: 省选/NOI-
pid: P7014
tag: ['2013', 'ICPC']
---
# [CERC2013] Chain & Co.
## 题目描述



Chain $&$ Co. specializes in producing infinitely strong chains. Because of their high quality products, they are quickly gaining market share. This leads to new challenges, some of which they could have never imagined before. Like, for example, automatic verification of link endurance with a computer program, which you are supposed to write.

The company produces links of equal size. Each link is an infinitely thin square frame in three dimensions (made of four infinitely thin segments).

During tests all links are $axis-aligned^{1}$ and placed so that no two frames touch. To make a proper strength test, two sets of links A and $B$ are forged so that every link of A is inseparable from every link of $B$ (being inseparable means that they cannot be moved apart without breaking one of them).

You stumble upon some links (axis-aligned, pairwise disjoint). Are they in proper testing position? In other words, can they be divided into two non-empty sets A and $B$ with the desired property?

$^{1}Axis-aligned$ means that all segments are parallel to either $X , Y$ , or $Z$ axis.


## 输入格式



The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

The description of each test case starts with an empty line. The next line contains an integer $n , 1 \le n \le 10^{6} -$ the number of links in the chain. Each of the next $n$ lines contains $6$ space separated integers $x_{i}, y_{i}, z_{i}, x_{i}', y_{i}', z_{i}',$ all between $-10^{9}$ and $10^{9} -$ the coordinates of two opposite corners of the i-th link.


## 输出格式



For each test case, print a single line containing the word YES if the set is in proper testing position, or NO otherwise.


## 样例

### 样例输入 #1
```
3

2
0 0 0 0 10 10
-5 5 15 5 5 25

5
0 0 0 0 10 10
-5 5 6 5 5 16
-5 5 -6 5 5 4
-5 6 5 5 16 5
-5 -6 5 5 4 5

3
0 0 0 3 0 -3
1 -1 -1 1 2 -4
-1 -2 -2 2 1 -2

```
### 样例输出 #1
```
NO
YES
YES

```
## 提示

Time limit: 10 s, Memory limit: 128 MB. 


## 题目翻译

给定三维空间中 $n$ 个平行于坐标轴的空心 **正方形**，请判断是否有一种划分方案，使得所有矩形被划分为两个 **非空** 集合 $A,B$，且对于 $\forall i\in A,\forall j\in B$，矩形 $i,j$ 可以扣起来。

这里对“扣起来”的定义是：矩形 $A,B$ 各有一条边穿过另一个矩形，而它的对边则在另一个矩形外。可以尝试想象锁链环环相扣的样子。

不同矩形的边互不相交。多组数据，$n\le 10^6$。


---

---
title: "[CERC2013] Captain Obvious and the Rabbit-Man"
layout: "post"
diff: 省选/NOI-
pid: P7016
tag: ['2013', 'ICPC']
---
# [CERC2013] Captain Obvious and the Rabbit-Man
## 题目描述



It's you, Captain Obvious! - cried the evil Rabbit-Man - you came here to foil my evil plans!

Yes, it's me.  - said Captain Obvious.

But... how did you know that $I$ would be here, on $625$ Sunflower Street?! Did you crack my evil code?

I did. Three days ago, you robbed a bank on $5$ Sunflower Street, the next day you blew up $25$ Sunflower Street, and yesterday you left quite a mess under number $125$ . These are all powers of $5$ . And last year you pulled a similar stunt with powers of $13$ . You seem to have a knack for Fibonacci numbers, Rabbit-Man. 

That's not over! $I$ will learn... arithmetics! - Rabbit-Man screamed as he was dragged into custody - You will never know what to expect... Owww! Not my ears, you morons!

Maybe, but right now you are being arrested.  - Captain added proudly.

Unfortunately, Rabbit-Man has now indeed learned some more advanced arithmetics. To understand it, let us define the sequence $F_n$ (being not completely unlike the Fibonacci sequence):

$F_{1} = 1$ ,

$F_{2} = 2$ ,

$F_{n} = F_{n-1} + F_{n-2}$ for $n \ge 3$ .

Rabbit-Man has combined all his previous evil ideas into one master plan. On the i-th day, he does a malicious act on the spot number $p(i)$ , defined as follows:

$p(i) = a_{1}·F_{1}^{i} + a_{2}·F_{2}^{i} + \cdots + a_{k}·F_{k}^{i}.$

The number $k$ and the integer coefficients $a_1 , \cdots $ , ak are fixed. Captain Obvious learned $k$ , but does not know the coefficients. Given $p(1) , p(2) , \cdots , p(k)$ , help him to determine p(k $+ 1)$ . To avoid overwhelmingly large numbers, do all the calculations modulo a fixed prime number $M$ . You may assume that $F_1 , F_2 , \cdots , F_n$ are pairwise distinct modulo $M$ . You may also assume that there always exists a unique solution for the given input.


## 输入格式



The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

The first line of each test case contains two integers $k$ and $M , 1 \le k \le 4000 , 3 \le M \le 10^{9}.$ The second line contains $k$ space-separated integers $-$ the values of $p(1) , p(2) , \cdots , p(k)$ modulo $M$ .


## 输出格式



Print the answers to the test cases in the order in which they appear in the input. For each test case print a single line containing one integer: the value of $p(k + 1)$ modulo $M$ .


## 样例

### 样例输入 #1
```
2
4 619
5 25 125 6
3 101
5 11 29

```
### 样例输出 #1
```
30
83

```
## 提示

Time limit: 6 s, Memory limit: 128 MB. 


## 题目翻译

众所周知，斐波那契数列的公式如下：

$$F_i=\begin{cases}1&i=1\\2&i=2\\F_{i-1}+F_{i-2}&i\geqslant 3\end{cases}$$

定义 $p_i=\sum\limits_{j=1}^ka_j\times F_j^i$。现在给定 $k,m$ 以及 $\{p_i\}_{i=1}^k$，请求出 $p_{k+1}\bmod m$。

Translated by Eason_AC  
2020.11.19


---

---
title: "[NWRRC 2017] Dividing Marbles"
layout: "post"
diff: 省选/NOI-
pid: P7022
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NWRRC 2017] Dividing Marbles
## 题目描述



Debbie, Debby, Debra and Deborah are going to play a game with marbles together. Debbie has brought $2^{d_{1}}$ marbles, Debby -- $2^{d_{2}}$ marbles, Debra -- $2^{d3}$ marbles, while Deborah -- $2^{d4}$ marbles. The kids have gathered their marbles into a single pile containing $2^{d_{1}} + 2^{d_{2}} + 2^{d_{3}} + 2^{d_{4}}$ marbles, and the game is starting.

The game consists of turns. Each turn consists of two steps:

The kids choose any of their piles with more than one marble and divide it into two non-empty piles. That is, if the chosen pile contains $m \ge 2$ marbles, the new piles must contain $m_{1}$ and $m_{2}$ marbles where $m_1$ and $m_2$ are positive integers, and $m_{1} + m_{2} = m$ .

If there are several piles with the same number of marbles, only one of these piles is kept, while all the others with this number of marbles are discarded (thrown away).

The game ends when only one pile is left, and this pile contains a single marble. The goal of the game is to end it in the least possible number of turns. Note that the game is cooperative, that is, the kids aren't playing against each other, but trying to reach a common goal together.

Help the kids and find the best way to play.


## 输入格式



The first line of the input contains a single integer $T$ -- the number of test cases $(1 \le T \le 500)$ .

Each of the next $T$ lines describes one test case and contains four non-negative integers $d_{1}, d_{2}, d_{3}, d_{4} (0 \le d_{i} \le 20)$ .


## 输出格式



For each test case, output an integer $t$ -- the smallest number of turns required to end the game.

Then, output $t$ turn descriptions, in the order the turns should be made. Each description should consist of three integers $m , m_{1}, m_{2}$ -- the size of the divided pile and the sizes of the new piles, respectively $(m \ge 2$ ; $m_{1} > 0$ ; $m_{2} > 0$ ; $m_{1} + m_{2} = m)$ . Note that a pile of size $m$ must exist at that moment, and at the end of the game there should be only one pile left and that pile should contain a single marble.


## 样例

### 样例输入 #1
```
2
1 0 1 0
0 1 2 3

```
### 样例输出 #1
```
3
6 2 4
4 2 2
2 1 1
5
15 10 5
10 5 5
5 1 4
4 2 2
2 1 1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

**题目描述**

Debbie, Debby, Debra 和 Deborah要一起玩一个关于弹珠的游戏。Debbie 带来了  $2^{d_{1}}$ 颗弹珠, Debby 带来了  $2^{d_{2}}$ 颗弹珠, Debra 带来了  $2^{d3}$ 颗弹珠, 而 Deborah 带来了  $2^{d4}$ 颗弹珠。这些孩子们把他们的弹珠放在一起，总共有 $2^{d_{1}} + 2^{d_{2}} + 2^{d_{3}} + 2^{d_{4}}$ 颗, 游戏开始了。

游戏是多回合制。每一个回合包括两个步骤：

这些孩子们选择他们的任意一堆大于1个的弹珠然后分入两个大于0个的堆中。相当于，如果选中的那堆有 $m \ge 2$ 颗弹珠, 新的一堆必须要有 $m_{1}$ 和 $m_{2}$ 颗弹珠且 $m_1$ 和 $m_2$ 为正整数, 且 $m_{1} + m_{2} = m$.

如果有许多堆拥有同样数目的弹珠，只有一堆会被保留，其他的都会被丢弃。

当只有一堆弹珠被留下且这堆弹珠只有一颗时，游戏就结束了。游戏的目标就是用尽量少的回合让游戏结束。注意这个游戏是合作性质的，那就是，这些孩子不是互相争斗的，而是一起尝试达成同一个目标。

请帮助这些孩子找到游戏的最佳方案。

**输入格式**

第一行包括一个单独的整数，T 即测试用例的数量$(1≤T≤500)$ .

下面的每一行都描述一个测试用例且包含四个非负整数 $d_{1}, d_{2}, d_{3}, d_{4} (0 \le d_{i} \le 20)$

**输出格式**

对于每一个测试用例，输出一个整数t，即游戏结束所需的最少次数。

然后，按照回合的顺序，输出这些回合的说明。每一行说明都要包括三个整数 $ m , m_{1}, m_{2}$ 即是被分的堆和新堆的弹珠数量，依次为$(m≥2 ; m_{1} > 0; m_{2} > 0 ;  m_{1} + m_{2} = m)$ 

请注意大小为m的弹珠堆一定要存在，且在游戏结束时应该只剩下一堆且那一堆应该只有一颗弹珠。

**说明/提示**

时间限制: 3 s, 内存限制: 512 MB.


---

---
title: "[NWRRC 2017] Fygon 2.0"
layout: "post"
diff: 省选/NOI-
pid: P7024
tag: ['2017', 'ICPC']
---
# [NWRRC 2017] Fygon 2.0
## 题目描述



The new version of beloved programming language Fygon has been released! The brand new Fygon $2$ . $0$ still has only two statements. The first statement is lag. It substitutes almost any other statement. Second statement is a for loop:

```
for <variable> in range(<from>, <to>):
    <body>
```

The for loop makes iterate from to , both inclusive.

If is greater than , is not executed at all.

is a lowercase letter from a to $z$ , except for $n$ , which is a variable that is defined prior to the given code snippet.

and can be equal to any variable defined in outer loop. In addition to that, can be $1$ and can be $n$ .

The of the loop is indented by four spaces and contains at least one statement.

If you are familiar with Fygon $1$ . $0$ , you can notice that, in the spirit of the best programming practices, Fygon $2$ . $0$ is not backwards compatible, since the range function now requires two parameters.

The performance of the new version is significantly improved, so you can write more nested for loops. That is why we are no longer interested in the exact number of operations, but in the asymptotic complexity of the program instead. For simplicity, all for loops are nested in a single chain and there is exactly one lag statement that is inside all for loops. All loop variables are different and are not equal to $n$ .

Let's define $f(n)$ as the number of lag operations exectuted by a given Fygon program as the function of $n$ . For non-negative integer $k$ and positive rational number $C$ we say that $C · n^{k}$ is the asymptotic complexity of the program if

$$\lim_{n \to \infty}{\frac{f(n)}{C \cdot n^k}} = 1$$

Given a Fygon $2$ . $0$ program, find its asymptotic complexity.


## 输入格式



The first line of the input contains single integer $m$ -- the number of lines in Fygon $2$ . $0$ program. Next $m$ lines contain the program itself. The program has at least $1$ and at most $20$ for statements. Each for statement contains either single nested for statement or lag statement.


## 输出格式



Output numbers $k$ and $C$ . $C$ should be output in the form of irreducible fraction $p/q$ , where $p$ and $q$ are coprime.


## 样例

### 样例输入 #1
```
4
for i in range(1, n):
    for j in range(1, i):
        for k in range(j, n):
            lag
```
### 样例输出 #1
```
3 1/3

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

卡老师新发明了一种语言：Fygon 2.0。这种语言只有两种语句：`lag` 和 `for`。其中 `for` 的格式如下：

```
for <variable> in range(<from>, <to>):
    <body>
```

- `<variable>` 是一个 `a` 到 `z` 之间的字符，但是不包括 `n`。
- `<from>` 和 `<to>` 是外面的循环中定义的变量。特别的,`<from>` 还可以是 `1`，`<to>` 还可以是 `n`。
- 这个语句表示 `<variable>` 从 `<from>` 循环到 `<to>`，两端均包含。
- 如果 `<from>` 大于 `<to>`，则该语句不会执行。
- 这里的 `<body>` 一定是一个 `for` 语句或者 `lag`，前面一定有 4 个空格的缩进。

卡老师随手写出了一个 Fygon 2.0 程序。因为他忙着去托老师的精神世界中写神题，所以这个程序的 `for` 语句数不超过 $20$ 个。

现在他想要计算这个程序的渐进时间复杂度。渐进时间复杂度定义如下：

> 定义 $f(n)$ 为 `lag` 的执行次数，若非负整数 $k$ 和正有理数 $C$ 满足
> 
> $$\lim_{n\to\infty}\frac{f(n)}{C\cdot n^k}=1$$
> 
> 则该程序的渐进时间复杂度为 $C\cdot n^k$。

卡老师看了一眼就算出来了，但是他想考考你，请你帮他求出这个程序的渐进时间复杂度。


---

---
title: "[NWRRC 2017] Grand Test"
layout: "post"
diff: 省选/NOI-
pid: P7025
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NWRRC 2017] Grand Test
## 题目描述



Jeremy, Richard and James like to test cars. It is always hard for them to decide where they should do it. Usually car test looks like this. They choose a country and examine its cities and two-way roads that connect them. To perform a test, they need to choose two different cities $S$ and $F$ , such that there exist three routes between them. Moreover, each city except $S$ and $F$ should be visited by at most one route, and none of the roads may be used twice.

Then each of them takes a car in city $S$ , drives along one of those routes and tries to get to city $F$ faster than others.

You are given a description of multiple countries. For each country you should decide if it is possible to choose two cities and three routes between them in a way described above.


## 输入格式



The first line of the input contains a single integer $T$ -- number of countries $(1 \le T \le 100 000)$ . It is followed by $T$ country descriptions.

The first line of each country description contains two integers $n$ and $m$ -- the number of its cities and roads $(1 \le n , m \le 100 000)$ . The following $m$ lines contain two integer numbers each: $u_{i}$ and $v_{i}$ -- the cities at the ends of the road $(1 \le u_{i} < v_{i} \le n)$ . All roads are two-way. Each pair of cities is connected by at most one road.

Both the total number of cities and roads in all countries does not exceed $100 000$ .


## 输出格式



Output the answer for each country in the order they are given in the input.

If it is not possible to test cars in this country, the answer is $−1$ . Otherwise the first line of the answer should contain two integers $S$ and $F$ -- start and finish cities. The next three lines should contain three distinct routes. Each route is described by an integer $k$ -- the number of cities it visits, and $k$ numbers $v_{1}, v_{2}, \cdots , v_{k}$ -- the cities, where $v_{1} = S , v_{k} = F$ , and there is a road between cities $v_{i}$ and $v_{i+1}$ for all $1 \le i \le k − 1$ .


## 样例

### 样例输入 #1
```
2
6 6
3 6
3 4
1 4
1 2
1 3
2 3
3 1
1 2

```
### 样例输出 #1
```
1 3
3 1 2 3
2 1 3
3 1 4 3
-1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

**题目描述**  
给定一张 $n$ 个节点 $m$ 条边的无向图，请在图中找出两个点 $S$ 和 $F$，使得这两点间至少存在三条不相交的路径。

**输入格式**   
输入的第一行包数据组数 $T(1 \leq T \leq 100000)$。对于每组数据，第一行为两个整数 $n$ 和 $m$。接下来 $m$ 行每行包含两个整数 $u$ 和 $v(1 \leq u < v \leq n)$，表示节点 $u$ 和 $v$ 之间有一条边。每对节点至多被一条边连接。保证 $\sum n$ 及 $\sum m$ 不超过 $100000$。

**输出格式**  
对于每组数据，若不存在，则输出`-1`。若存在，则第一行输出 $S$ 和 $F$。接下来三行输出三条路径。每行先输出路径路径包含的点数，然后依次输出由 $S$ 到 $F$ 的路径上各点。


---

---
title: "[NWRRC 2017] Hidden Supervisors"
layout: "post"
diff: 省选/NOI-
pid: P7026
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NWRRC 2017] Hidden Supervisors
## 题目描述



Helena works in a big company as a psychologist. Her task is to organize a team building game to enhance social relations between employees. Each employee except the Big boss has a single supervisor. So, employees of the company form a tree where each employee is a node, and the parent of that node is their supervisor. The root of the tree is the Big boss.

A team building game requires teams of two people. Every team should consist of an employee and their supervisor.

Helena asked every employee except the Big boss to send their supervisor ID. Some of them didn't reply. She is going to assign a fake supervisor to every employee that didn't reply, so that she could arrange as many teams as possible. And, of course, fake and real supervisors must form a tree.

Helena had a difficult, but a successful day organizing the event. Will you be able to assign fake supervisors?


## 输入格式



The first line of the input contains a single integer $n$ -- the number of employees in the company $(2 \le n \le 100 000)$ .

The following line contains $n − 1$ integers $p_{2}, p_{3},$ . . . , $p_{n},$ where $p_{i}$ is the supervisor of employee $i (0 \le p_{i} \le n)$ . If employee $i$ didn't reply to Helena, $p_{i}$ equals zero, and she needs to assign a fake supervisor to that employee. The Big boss has the number $1$ .

It's possible to assign a fake supervisor to each employee that didn't reply to Helena so that all employees will form a tree having the Big boss as a root.


## 输出格式



In the first line output a single integer $m$ -- the maximum possible number of arranged teams.

The next line should contain supervisors: $n−1$ integers, i-th of which denoting the supervisor of employee $i + 1$ (either fake or real). Of course, all real supervisors should be preserved, and employees must form a tree. It should be possible to arrange $m$ teams using specified supervisors.


## 样例

### 样例输入 #1
```
6
3 1 0 4 4

```
### 样例输出 #1
```
2
3 1 2 4 4

```
### 样例输入 #2
```
6
3 1 0 6 4

```
### 样例输出 #2
```
3
3 1 1 6 4

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

## 题目简述

有一棵大小为 $n$ 的有根树，根为 $1$，其中若干结点的父亲没有确定。试求出所有可能构成的以 $1$ 为根的有根树中，最大匹配的最大值是多少，并输出构造方案。保证数据有解。

## 输入格式

第一行输入一个整数 $n$。

第二行输入 $n-1$ 个整数 $p_2,p_3,\cdots,p_n$，分别表示 $2,3,\cdots,n$ 的父亲。其中 $p_i = 0$ 表示点 $i$ 的父亲未确定，$p_i \neq 0$ 表示点 $i$ 的父亲已确定。

## 输出格式

第一行输出一个整数表示最大匹配的最大值。

第二行输出 $n-1$ 个整数 $p'_2,p'_3,\cdots,p'_n$，分别表示 $2,3,\cdots,n$ 的父亲。


---

---
title: "[NWRRC 2017] Joker"
layout: "post"
diff: 省选/NOI-
pid: P7028
tag: ['2017', '分块', '凸包', 'ICPC']
---
# [NWRRC 2017] Joker
## 题目描述



Joker prepares a new card trick with a strong mathematical background. You are asked to help Joker with calculations.

There is a row of $n$ cards with non-zero numbers $a_{i}$ written on them. Let's call the sum of all positive numbers $P$ and the sum of all negative numbers $N$ . Every card $i$ has a weight $w_{i} = a_{i}/P$ if $a_{i} > 0$ and $a_{i}/|N|$ otherwise.

Let's denote $s_{i} = ( \sum_{j=1}^{j \le i}{w_j})$. Joker needs to know positive $i$ with the largest $s_{i}.$ If there is more than one such $i$ , he is interested in the smallest one.

But static tricks are boring, so Joker wants to change numbers on some cards, and after each change he needs to known where is the largest $s_{i}$ is.


## 输入格式



The first line of the input contains two integers $n$ and $m$ -- the number of cards and the number of changes $(1 \le n , m \le 50 000)$ .

The second line consists of $n$ integers $a_{i}$ -- numbers written on cards at the beginning $(−10^{9} \le a_{i} \le 10^{9}; a_{i} ≠ 0)$ .

The following $m$ lines contain two integers each: $p_{i}$ and $v_{i},$ that means value of card at position $p_{i}$ is changed to $v_{i} (1 \le p_{i} \le n$ ; $−10^{9} \le v_{i} \le 10^{9}; v_{i} ≠ 0)$ .

It is guaranteed that at each moment there is at least one card with positive number and at least one card with negative number. The sum of all positive cards will never exceed $10^{9}$ and the sum of all negative cards will never exceed $−10^{9}.$


## 输出格式



You should output $m+1$ integers. The first integer is the position of the largest $s_{i}$ for the initial numbers. Next $m$ numbers are positions of the largest $s_{i}$ after each change.


## 样例

### 样例输入 #1
```
4 7
1 -5 3 -5
4 -1
2 -1
3 10
4 10
1 -1
2 1
3 -1

```
### 样例输出 #1
```
3
1
3
3
1
4
4
4

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

有一个长度为 $n$ 的数列，第 $i$ 个元素的值为 $a_i$，定义 $P$ 为数列中所有正整数的和，$N$ 为所有负整数的和。定义一个元素的重要值 $w_i=\begin{cases}\dfrac{a_i}{P}&a_i>0\\\dfrac{a_i}{|N|}&\text{otherwise}\end{cases}$，并定义 $s_i$ 为前 $i$ 个元素的重要值之和，即 $\sum\limits_{j=1}^iw_j$。

请先求出当前数列中使 $s_i$ 最大的 $i$。然后有 $m$ 次操作，每次操作将某个元素改成一个给定的值，请在每次操作后求出当数列中使 $s_i$ 最大的 $i$。

如果有多个满足要求的 $i$，则答案取最小的。

Translated by Eason_AC  
2020.11.15


---

---
title: "[NWRRC 2016] Boys and Girls"
layout: "post"
diff: 省选/NOI-
pid: P7032
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Boys and Girls
## 题目描述



Bob found a nice task in his old math book for children. It says:

There are $10$ children standing in a circle, $5$ of them stand next to a boy, and $7$ of them stand next to a girl. How is it possible?

Here is the solution to the task. If $4$ boys and $6$ girls stand like this: BGBGBGBGGG, there are $5$ children who stand next to a boy (here they are underlined: BGBGBGBGGG), and $7$ children who stand next to a girl $(BGBGBGBGGG).$

Now Bob wants to solve a generalized version of this task:

There are $n$ children standing in a circle, $x$ of them stand next to a boy, and $y$ of them stand next to a girl. How is it possible?

Help Bob by writing a program that solves the generalized task.


## 输入格式



The single line of the input contains three integers $n , x$ and $y (2 \le n \le 100 000$ ; $0 \le x , y \le n)$ .


## 输出格式



If there is a solution, output a string of length $n$ , describing the order of children in the circle. $Character ‘G'$ corresponds to a girl, character $‘B'$ corresponds to a boy. If there are several solutions, output any $of the_m.$

If there is no solution, output `Impossible`.


## 样例

### 样例输入 #1
```
10 5 7

```
### 样例输出 #1
```
BGBGBGBGGG

```
### 样例输入 #2
```
10 3 8

```
### 样例输出 #2
```
Impossible

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述

Bob在他那本给孩子们的旧数学书中找到了一个好任务。上面写着：

有 $10$ 个孩子站成一个圆圈，其中 $5$ 个站在一个男孩旁边， $7$ 个站在一个女孩旁边。如何解决这个任务？

这个任务的解决方案如下：如果 $4$ 个男孩和 $6$ 个女孩像这样站着：$bgbgbbggg$，那么有 555 个孩子站在一个男孩旁边（用粗体字标记：b**g**b**g**b**g**b**g**g**g**）， 777 个孩子站在一个女孩旁边（用粗体字标记：**b**g**b**g**b**g**bggg**）。

现在Bob想解决这个任务的广义版本：

有 $n$ 个孩子站在一个圆圈里，其中 $x$ 个孩子站在一个男孩旁边， $y$ 个孩子站在一个女孩旁边。如何解决这个任务？

请编写一个程序来帮助Bob解决这个任务。

### 输入格式
一行，包括三个整数 $n$ , $x$ , $y$ 。($2≤n≤100000$; $0≤x,y≤n$) 

### 输出格式
若有解，输出一个长度为 $n$ 的字符串，描述圆中元素的顺序。每个字符 $G$ 对应一个女孩，字符 $B$ 对应一个男孩。如果有多个解决方案，则输出其中任意一种。
如果没有解决方案，输出```'Impossible'```
。（不包括引号）



---

---
title: "[NWRRC 2016] Easy Reading"
layout: "post"
diff: 省选/NOI-
pid: P7035
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Easy Reading
## 题目描述



Eugene is reading a boring book. To make this process interesting he is drawing a picture at the  same time.  He has a piece of graph paper that is divided into square cells. All the cells are empty at  the beginning. 

Eugene starts by painting over one cell. Then he opens the book at a random page and starts reading.   Whenever  he sees the letter  `u`  in the text, he moves his pen one cell up and then paints over the  cell under  his pen. Whenever he sees the letter  `d`,  he does the same but moves his pen one cell down  instead of  up. For letters  `l`  and  `r`  he moves to the left and to the right, respectively. If he wants to paint  a cell  that was already painted, he paints it again.

You have found a piece of paper and the text of the book. Now you want to understand if the picture  o_n the  paper could be drawn by Eugene at some point of his book reading. Remember that Eugene  could use  some substring of the text.


## 输入格式



The first line of the input contains an integer $l$ -- the length of the text $(1 \le l \le 100 000)$ . The $second line$ contains a string of length $l$ -- the text. It contains only lowercase English letters, spaces, commas and periods. The text neither begins nor ends with a space.

The third line contains two positive integers $n$ and $m$ -- the picture dimensions $(2 \le n \times m \le 100 000)$ .

Each of the following $n$ lines contains a string of length $m$ . Painted cells are denoted by `X`, while empty cells -- by `.` . It is guaranteed that there are at least two painted cells in the picture.

The first of these $n$ lines corresponds to the top of the picture and the last one corresponds to the bottom of it.


## 输出格式



If the picture could be painted by Eugene, output `YES` on the first line. On the second line print two integers b and $e$ such that if Eugene read all letters from $b$ to $e$ , inclusive, he would draw exactly $the same$ picture as described in the input $(1 \le b \le e \le l)$ . If there are several solutions, output any of them.

If the picture couldn't be drawn by Eugene, output `NO`.


## 样例

### 样例输入 #1
```
43
you should read statement really carefully.
3 6
...XX.
..XXX.
...XXX

```
### 样例输出 #1
```
YES
3 42

```
### 样例输入 #2
```
43
you should read statement really carefully.
3 2
XX
XX
XX

```
### 样例输出 #2
```
NO

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 

## 题目翻译

## 题目描述

Eugene正在读一本无聊的书。为了使阅读更有趣，他在阅读的同时同时作画。 他有一张方格纸。 所有的方格一开始都是空的。

Eugene一开始在一个方格上作画。让后他随机翻开一页并开始阅读。当他遇到字母 `u`  时, 他把笔向上移动一格并在这格上画画。 当他看到 `d`时, 他会做同样的操作，但是向下移动一格而不是向上移动一格。 `l` ,`r`分别是向左和向右一格。 如果这个单元格已经画过了他会再画一次。

现在你有一张纸与这本书中的内容。 现在你想知道这张纸上的图片是否可能被Eugene在某一时刻画过。 记住：Eugene可以只使用用这个内容的子字符串。

## 输入格式

第一行是一个整数$l(1 \le l \le 10^5)$--表示这个内容的长度。 

第二行是一个长度为$l$的字符串$a$。它只包含小写英文字母、空格、逗号和句号。$a$既不会以空格开头也不会以空格结尾。

第三行是两个整数$n$ 与 $m$--图的大小$(2 \le n \times m \le 10^5)$ 。

第$4$~$3+n$行，每行一个长度为$m$的字符串。画过的格子用`x`表示，没画过的用`.`表示。保证一幅图中至少有两个格子已被涂色。

这 $n$ 行字符串中的第一行对应于图片的顶部，最后一行对应于图片的底部。

## 输出格式

如果可能被绘制，第一行输出`YES`，第二行输出用空格隔开的两个整数$b$和$e$,表示Eugene从第$b$个字母开始读，到第$e$个字母结束(包含$b$和$e$)。

如果不能，输出`NO`。

## 样例 #1

### 样例输入 #1

```
43
you should read statement really carefully.
3 6
...XX.
..XXX.
...XXX
```

### 样例输出 #1

```
YES
3 42
```

## 样例 #2

### 样例输入 #2

```
43
you should read statement really carefully.
3 2
XX
XX
XX
```

### 样例输出 #2

```
NO
```

## 说明/提示

时限: 2 s, 内存限制: 256 MB.


---

---
title: "[NWRRC 2016] Gangsters in Central City"
layout: "post"
diff: 省选/NOI-
pid: P7037
tag: ['2016', 'ICPC']
---
# [NWRRC 2016] Gangsters in Central City
## 题目描述



For a long time, there were no problems with water in Central City. The sewage of the city has a form of a rooted tree: the central reservoir is situated at the root and the houses are at the leaves. The water flows from the central reservoir to the houses by the pipes that runs along the edges of the tree. Each house has an access to water.

Suddenly, gangsters captured some of the houses. As a mayor of the city you are very concerned, and you want to kick out the gangsters. So you want to stop the water flow to houses captured by the gangsters.  To do that you could clog some pipes of the sewage system. If the path from the reservoir to a house contains at least one clogged pipe, the house does not have an access to water.

You are very afraid of the gangsters, so you decided to clog up the minimal number of pipes, that it could look like an accident. At the same time, you care about the citizens, so for the chosen number of clogged pipes, you want to minimize the number of houses without gangsters and access to water.

Unfortunately, the gangsters could appear and disappear from some houses. So, you are asking the scientists about the minimum required number of clogged pipes and the minimum required number of houses without gangsters and access to water after each change in the gangsters' location.


## 输入格式



The first line of the input contains two integers $n$ and $q$ -- the number of vertices in the tree which represents the sewage and the number of changes in the location of the gangsters $(2 \le n \le 100 000$ ; $1 \le q \le 100 000)$ .

The second line contains the description of the sewage: a sequence of $n − 1$ integers $p_{2}, p_{3},$ . . . , $p_{n}$, where $p_{i} is$ the parent of the vertex $i (1 \le p_{i} < i)$ . The central reservoir is located at the vertex $1$ .

The next $q$ lines represent the changes in the location of the gangsters. Each change could be one of two different types: 

- `+ v` -- the gangsters capture the house at vertex $v$ ; 
- `- v` -- the gangsters leave the house at vertex $v$ .

At the beginning all the houses are free of gangsters. All the changes form the correct sequence: the gangsters cannot capture the house if it is already captured and the gangsters could not leave the house if it is not captured.


## 输出格式



The output should contain 2q integers, two in each line: $c_{i}$ -- the minimum number of clogged pipes and $h_{i}$ -- the minimum number of houses without gangsters and have no access to water for the chosen $c_{i}$

.


## 样例

### 样例输入 #1
```
7 6
1 2 1 3 3 3
+ 4
+ 5
+ 6
+ 7
- 6
- 5

```
### 样例输出 #1
```
1 0
2 0
2 1
2 0
2 1
2 0

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给出一棵含有 $n$ 个节点的，且 $1$ 为根节点的树，叶子节点都是房屋，让你在一个集合里面进行添加房屋和移除房屋的操作。

每一次添加和移除后，你将要回答下面两个问题：

1.  最少需要砍多少条边，才能使已选房屋都不能从根节点到达。

2.  在第 $1$ 问的条件下，如何砍边使从根节点点开始走不能到达的非已选房屋数目最小，输出最小值。


---

---
title: "[NWRRC 2016] Integral Polygons"
layout: "post"
diff: 省选/NOI-
pid: P7039
tag: ['计算几何', '2016', '叉积', 'ICPC', '状压 DP']
---
# [NWRRC 2016] Integral Polygons
## 题目描述



Ingrid holds a polygon shop in a far away country. She sells only convex polygons with integer coordinates. Her customers prefer polygons that can be cut into two halves in a proper way, that is the cut should be straight  with starting and ending points in the polygon vertices and both halves should be non-empty and have integer areas. The more ways to cut the polygon in the proper way are -- the more expensive the polygon is.

For example, there are three ways to cut the left polygon in the proper way, and two ways for the right polygon.

![](https://cdn.luogu.com.cn/upload/image_hosting/fei0xc33.png)

The polygons in the shop are always of excellent quality, so the business is expanding. Now Ingrid needs some automatic tool to determine the number of ways to cut the polygon in the proper way. This is very important for her shop, since otherwise you will spend a lot of time on setting prices -- just imagine how much time would it take to set prices for a medium-sized van with polygons. Could you help Ingrid and write the tool for her?


## 输入格式



The first line of the input contains an integer $n$ -- the number of polygon vertices $(4 \le n \le 200 000)$ . $ Each$ of the following $n$ lines contains vertex coordinates: a pair of integers $x_{i}$ and $y_{i}$ per line $(-10^{9} \le x_{i}, y_{i} \le 10^{9}).  The$ specified polygon is convex and its vertices are specified in the order of traversal.


## 输出格式



Output a single integer $w$ -- the number of ways to cut the polygon in the proper way.


## 样例

### 样例输入 #1
```
5
7 3
3 5
1 4
2 1
5 0

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
4
1 1
3 1
5 5
1 3

```
### 样例输出 #2
```
2

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

按顺序给定一个凸多边形的  $n$ 个定点  $(x_i,y_i)$ ， $x_i,y_i\in[-10^9,10^9]$ 且为整数。

求满足条件的对角线数量，使得该对角线将多边形分成的两个部分的面积皆为整数。


---

---
title: "[NWRRC 2014] Combinator Expression"
layout: "post"
diff: 省选/NOI-
pid: P7062
tag: ['2014', 'ICPC']
---
# [NWRRC 2014] Combinator Expression
## 题目描述

Combinatory logic may be thought as one of computational models allowing to express any computable function as a composition of functions from a small finite basis. In this problem we consider a restricted variant of BCKW basis, BCKI.

Combinator expression in BCKI basis is a string, corresponding to the following grammar:

```plain
⟨Expression⟩ ::= ⟨Expression⟩ ⟨Term⟩ | ⟨Term⟩
⟨Term⟩ ::= ‘(’⟨Expression⟩‘)’ | ‘B’ | ‘C’ | ‘K’ | ‘I’
```

As we can see from the grammar, the expression is a tree of applications where leafs are combinators $B, C, K$ and $I$. The application is left-associative. For example $BIC$ is equivalent to $(BI)C,$ but not to $B(IC)$.

For the sake of the explanation we will use lowercase English letters $(a \cdots z)$ to represent sub-expressions. These lowercase letters will not appear in real data. For example, $BIC$ can be represented by $BxC$ (that is, $B\underbrace { I }_{ x }C)$, $x(\underbrace {BIC}_{ x })$, $xy(\underbrace {BI}_{ x } \underbrace { C }_{ y })$, $Bxy (B\underbrace { I }_{ x }\underbrace { C }_{ y })$, but not by $Bx$.

We say that in expression $pq$ we apply $p$ to $q$. We can employ our intuition by saying that $p$ is a function and $q$ is its parameter. However, the evaluation process is quite different from traditional computation — instead of passing values over fixed expression tree, we evaluate by altering that tree so that the result is also some combinator expression.

To evaluate an expression, we need to select some sub-expression, corresponding to one of the patterns specified in the table below — that is, there should exist such $x$ (and maybe $y$ and $z$) that the pattern from the table becomes equal to the sub-expression. Then we need to replace the sub-expression with the reduction result from the table.

| Pattern | Reduction result |                   Description                   |
| :-----: | :--------------: | :---------------------------------------------: |
| $Bxyz$  |     $x(yz)$      | Composition function (Zusammensetzungsfunktion) |
| $Cxyz$  |     $(xz)y$      |    Exchange function (Vertauschungsfunktion)    |
|  $Kxy$  |       $x$        |      Constant function (Konstanzfunktion)       |
|  $Ix$   |       $x$        |     Identity function (Identitätsfunktion)      |

After the replacement took place we must repeat the process, until there remains no suitable subexpressions. This final expression is normal form of the original one. For example, in expression $CIC(CB)I$ we can make the following letter assignment

$$\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace {(CB)}_{ z }I$$

and see that $CIC(CB)I ≡ (((CI)C)(CB))I ≡ (((Cx)y)z)I$ contains $C$ combinator pattern and thus reduces to $((xz)y)I ≡ I(CB)CI:$

$$(\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace { (CB) }_{ Z })I \rightarrow (\underbrace { I }_{ x } \underbrace {(CB)}_{ z }\underbrace { C }_{ y })I$$

One more example: $B((CK)I)IC$ expression. Let us first reduce combinator $B:$

$$(\underbrace { B }_{ B }\underbrace { ((CK)I) }_{ x }\underbrace { I }_{ y }\underbrace { C }_{ z } \rightarrow \underbrace { ((CK)I) }_{ x } (\underbrace { I }_{ y }\underbrace { C }_{ z })$$

Now, let's reduce the last $I:$

$$((CK)I)(\underbrace { I }_{ I } \underbrace { C }_{ x }) \rightarrow ((CK)I)C$$

And now we finish evaluation with two more reductions:

$$((\underbrace { C }_{ C }\underbrace { K }_{ x }) \underbrace { I }_{ y }) \underbrace { C }_{ z } \rightarrow (\underbrace { K }_{ K }\underbrace { C }_{ x }) \underbrace { I }_{ y } \rightarrow C$$

It is possible to show that the normal form remains the same irrespectable to the order of evaluation. For example, the following evaluation order:

$$C(K(II)(\underbrace { I }_{ I }\underbrace { C }_{ x })) \rightarrow C(K(\underbrace { I }_{ I }\underbrace {  I}_{ x })(C)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x }) \underbrace { C }_{ y }) \rightarrow CI$$

leads to the same result as 

$$C(K(\underbrace {I}_{ I }\underbrace { I }_{ x })(IC)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x })\underbrace { (IC)}_{ y }) \rightarrow CI$$

However, as you see, the number of reductions is different: $3$ in the first case and $2$ in the second. This poses an interesting problem -- to find an evaluation order with the minimal number of reductions for a given formula.

Your task is to write a program which finds the minimal number of reductions required for a given combinator expression to be evaluated to its normal form.
## 输入格式



The only line of the input file contains a combinator expression corresponding to the grammar above. The length of the expression does not exceed $30 000$ . The expression contains no whitespaces or symbols not specified in the grammar.


## 输出格式



Output a single integer — the minimal number of reductions required for the given formula to evaluate it to normal form.


## 样例

### 样例输入 #1
```
C(K(II)(IC))

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
CIBI

```
### 样例输出 #2
```
3

```
### 样例输入 #3
```
BBBBBCCCCCKKKKKIIIII

```
### 样例输出 #3
```
15

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

## 题目背景

## 题目描述
组合逻辑可以看作是一种计算模型，允许将任何可计算函数表示为从小的有限基底中选取的函数的组合。在这个问题中，我们考虑 BCKW 基底的一个受限变体，即 BCKI。

BCKI 基底中的组合表达式是一个字符串，对应于以下文法：

```plain
⟨表达式⟩ ::= ⟨表达式⟩ ⟨项⟩ | ⟨项⟩
⟨项⟩ ::= ‘(’⟨表达式⟩‘)’ | ‘B’ | ‘C’ | ‘K’ | ‘I’
```

从文法可以看出，表达式是应用树，叶子是组合子 $B, C, K$ 和 $I$。应用是左结合的。例如，$BIC$ 等价于 $(BI)C$，但不等价于 $B(IC)$。

为了便于解释，我们将使用小写英文字母 $(a \cdots z)$ 来表示子表达式。这些小写字母不会出现在实际数据中。例如，$BIC$ 可以表示为 $BxC$（即 $B\underbrace { I }_{ x }C$），$x(\underbrace {BIC}_{ x })$，$xy(\underbrace {BI}_{ x } \underbrace { C }_{ y })$，$Bxy (B\underbrace { I }_{ x }\underbrace { C }_{ y })$，但不能表示为 $Bx$。

在表达式 $pq$ 中，我们说将 $p$ 应用于 $q$。我们可以用直觉来理解，$p$ 是一个函数，而 $q$ 是它的参数。然而，求值过程与传统的计算非常不同——不是通过固定表达式树传递值，而是通过改变树结构，使得结果也是一个组合表达式。

为了求值一个表达式，我们需要选择一个子表达式，该子表达式应符合下表中的某个模式——也就是说，应该存在这样的 $x$（可能还有 $y$ 和 $z$），使得表中的模式与子表达式相等。然后我们需要将子表达式替换为表中的简化结果。

| 模式  | 简化结果 | 描述                           |
| :---: | :-------: | :-----------------------------: |
| $Bxyz$ | $x(yz)$  | 组合函数（Zusammensetzungsfunktion） |
| $Cxyz$ | $(xz)y$  | 交换函数（Vertauschungsfunktion）   |
| $Kxy$  | $x$      | 常数函数（Konstanzfunktion）       |
| $Ix$   | $x$      | 恒等函数（Identitätsfunktion）     |

替换完成后，我们必须重复这个过程，直到没有合适的子表达式为止。这个最终表达式就是原始表达式的规范形式。例如，在表达式 $CIC(CB)I$ 中，我们可以进行如下字母分配

$$\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace {(CB)}_{ z }I$$

并看到 $CIC(CB)I ≡ (((CI)C)(CB))I ≡ (((Cx)y)z)I$ 包含了 $C$ 组合子模式，因此简化为 $((xz)y)I ≡ I(CB)CI:$

$$(\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace { (CB) }_{ Z })I \rightarrow (\underbrace { I }_{ x } \underbrace {(CB)}_{ z }\underbrace { C }_{ y })I$$

另一个例子：$B((CK)I)IC$ 表达式。让我们先简化组合子 $B:$

$$(\underbrace { B }_{ B }\underbrace { ((CK)I) }_{ x }\underbrace { I }_{ y }\underbrace { C }_{ z } \rightarrow \underbrace { ((CK)I) }_{ x } (\underbrace { I }_{ y }\underbrace { C }_{ z }))$$

现在，让我们简化最后一个 $I:$

$$((CK)I)(\underbrace { I }_{ I } \underbrace { C }_{ x }) \rightarrow ((CK)I)C$$

最后，我们通过两次更多的简化完成求值：

$$((\underbrace { C }_{ C }\underbrace { K }_{ x }) \underbrace { I }_{ y }) \underbrace { C }_{ z } \rightarrow (\underbrace { K }_{ K }\underbrace { C }_{ x }) \underbrace { I }_{ y } \rightarrow C$$

可以证明，无论求值顺序如何，规范形式都是一样的。例如，以下求值顺序：

$$C(K(II)(\underbrace { I }_{ I }\underbrace { C }_{ x })) \rightarrow C(K(\underbrace { I }_{ I }\underbrace {  I}_{ x })(C)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x }) \underbrace { C }_{ y }) \rightarrow CI$$

和

$$C(K(\underbrace {I}_{ I }\underbrace { I }_{ x })(IC)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x })\underbrace { (IC)}_{ y }) \rightarrow CI$$

得到的结果相同。然而，如你所见，简化的次数不同：第一个情况下为 $3$ 次，第二个情况下为 $2$ 次。这提出了一个有趣的问题——找到一个给定公式所需的最小简化次数。

你的任务是编写一个程序，找到给定组合表达式求值到其规范形式所需的最小简化次数。

## 输入格式
输入文件只有一行，包含一个符合上述文法的组合表达式。表达式的长度不超过 $30 000$。表达式中不含空格或文法未指定的符号。

## 输出格式
输出一个整数——给定公式求值到规范形式所需的最小简化次数。

## 数据范围与提示
时间限制：1 秒，内存限制：256 MB。


---

---
title: "[NWRRC 2014] Fragmentation"
layout: "post"
diff: 省选/NOI-
pid: P7065
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NWRRC 2014] Fragmentation
## 题目描述



Felix is working on a startup project in his garage. He has already found a great name for his project: SuperFastZilla. By now he is not sure what SuperFastZilla should do, but he is pretty sure it should do it fast, super fast.

Once he noticed that SuperFastZilla is working too slow, inspite of the fast algorithms used in it. Felix thinks that the problem may be caused by storage fragmentation.

The storage used by SuperFastZilla consists of $n$ blocks of memory. SuperFastZilla performs some operations on this storage. Each block is used in one operation only, the i-th block is used in the $a_{i}$-th operation.

Felix wants to sort these blocks by the index of the operation they are used. To make it faster, Felix wants to split the storage into minimal number of segments of consecutive blocks, and then rearrange these segments to get the sorted array of blocks. After this rearrangement the order of block's indices of operations must be non-decreasing.

Help Felix to find the way to split the storage that minimizes the number of segments.

For example, if $a = [2 , 3 , 1 , 1 , 2 , 2 , 1],$ it can be split into three parts: $[2 , 3], [1 , 1 , 2 , 2]$ and $[1].$ These parts can be rearranged to make the sorted array: $[1], [1 , 1 , 2 , 2], [2 , 3].$


## 输入格式



The first line of input file contains an integer $n (1 \le n \le 10^{5}).$ The next line contains $n$ integers $a_{i} (1 \le a_{i} \le 10^{5}).$


## 输出格式



The first line of the output file must contain an integer number $m$ — the minimal number of segments.

The next line must contains $m$ integers, the lengths of the segments, from left to right.


## 样例

### 样例输入 #1
```
7
2 3 1 1 2 2 1

```
### 样例输出 #1
```
3
2 4 1

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给定一个长度为 $n$ 的数组，你需要把它分成尽量少的段，使得你可以排列这些段令整个数组有序。


$n,a_i \le 10^5$


---

---
title: "[NWRRC 2013] Correcting Curiosity"
layout: "post"
diff: 省选/NOI-
pid: P7081
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NWRRC 2013] Correcting Curiosity
## 题目描述



Curiosity is the rover that explores the Gale Crater on Mars. Recently it found an evidence of water in Martian soil, which will make it easier to plan the future manned missions. $ $

Curiosity can communicate with Earth directly at speeds up to $32 Kbit/s$ , but on average $14$ minutes and $6$ seconds will be required for signals to travel between Earth and Mars.

`You have just seen a stone and applied brakes, but you know that the rover is already passing that stone` -- Matt Heverly, the rover's driver, explains. `So we just plan the route, then write down a list of simple textual commands: move one meter ahead, turn left, make a photo and so on`.

Sometimes it is necessary to react very fast to some unexpected events. For example, if the cameras have seen something interesting, then you might want to change the route of the rover to make an additional photo. To do that, you send a substitution command of the form $s/〈string〉/〈replacement〉/g$ . This replaces all occurrences of $〈string〉,$ starting with the leftmost one, to $〈replacement〉.$

More formally, if A is a non-empty string and $B$ is a string, then to apply the substitution command $s/A/B/g$ to a string $S$ , you should do the following:

Find the leftmost occurrence of A in $S$ , such that $S =$ SL $+$ A $+$ SR.

If there is no such occurrence, stop. Then, $S$ is the answer.

Let $R$ be the result of applying $s/A/B/g$ to SR.

The answer is SL $+ B + R$ .

This means that:

If there are two overlapping occurrences of A in $S$ , only the leftmost one is replaced. For example, applying $`s/aba/c/g`$ to `abababa` yields `cbc`: after replacing the first occurrence of `aba` the string turns to `cbaba`, and only the last occurrence of `aba` can be replaced after that.

No substitution uses the results of previous substitutions. For example, applying $`s/a/ab/g`$ to `a` yields `ab`, applying $`s/a/ba/g`$ to `a` yields `ba`.

You know that the longer is the command, the bigger is the time necessary to transmit it. So, you have to write a program that finds shortest command that transforms the initial string to the final string.


## 输入格式



The first line contains the initial and the final strings. Both strings are non-empty and their lengths do not exceed $2000$ characters. The strings contain only English letters, spaces and punctuation signs (commas, colons, semicolons and hyphens: $‘,', ‘:', ‘;', ‘-').$ The given strings are not equal.


## 输出格式



Output the substitution command that transforms initial string to final string and has the minimum length. If there are several shortest substitution commands, output any of them.


## 样例

### 样例输入 #1
```
move left, move right; move up
move left, move down, move up

```
### 样例输出 #1
```
s/right;/down,/g

```
### 样例输入 #2
```
If not found: move x; else move -x
If found: move x; else move -x

```
### 样例输出 #2
```
s/ not//g

```
### 样例输入 #3
```
abababa
cbc

```
### 样例输出 #3
```
s/aba/c/g

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

# [NWRRC2013] Correcting Curiosity

## 题目描述

“好奇号”是探索火星上盖尔陨石坑的火星车。最近，它在火星土壤中发现了水存在的证据，这将使未来的火星登陆任务变得更加容易。$ $

“好奇号”可以用高达$32 Kbit/s$的速度与地球直接通信 ，但在地球和火星之间传输信号分别平均需要$14$秒和$6$秒。

`你刚刚看到一块石头并踩下了刹车，但你知道火星车已经经过那块石头了` -- 火星车司机Matt Heverly解释道。`所以我们需要规划路线，然后写下一个简单的命令列表：如向前移动一米，左转，拍照等等`.

有时你有必要对一些突发事件做出非常迅速的反应。例如，当相机看到了一些有趣的东西，那么你可能会想改变火星车的路线来拍摄的照片。为此，您需要发送一个形式为 $s/〈string〉/〈replacement〉/g$ . 这将替换所有出现的 $〈string〉,$ 从最左边的开始, 到 $〈replacement〉.$

更确切地说，如果A是非空字符串，而$B$是字符串, 则要将替换命令$s/A/B/g$应用于字符串$s$，执行以下操作：

在$S$中查找最左边出现的A，这样$S=$SL$+$A$+$SR。

如果没有A，请停止操作。$S$就是答案。

让$R$成为对SR应用$s/A/B/g$的结果。

那么答案是SL$+B+R$。

这就说明:

如果在$S$中有两个重叠的A，那么只替换最左边的一个。例如，将$`s/aba/c/g`$应用于`abababa`会产生`cbc`：在替换第一个`aba `之后，字符串将变为`cbaba `，在此之后只能替换最后一个出现的` aba `。

如果没有替换就使用先前替换的结果。例如，将$`s/a/ab/g`$应用于`a`产生`ab`，将$`s/s/a/ba/g`$应用于`a`产生`ba`。

命令越长，传输它所需的时间就越长。因此，需要你编写一个程序，找到最短的命令，将初始字符串转换为最终字符串。

## 输入格式

第一行输入包含初始字符串和最终字符串。这两个字符串都不是空的，并且它们的长度不超过$2000$。字符串仅包含英文字母、空格和标点符号（逗号、冒号、分号和连字符：$'，'，'：'，'；'，'-'）。$给定的字符串不相同。

## 输出格式

输出将初始字符串转换为最终字符串并最短的替换命令。如果有多个最短的替换命令，请输出其中任何一个。

## 样例 #1

### 样例输入 #1

```
move left, move right; move up
move left, move down, move up
```

### 样例输出 #1

```
s/right;/down,/g
```

## 样例 #2

### 样例输入 #2

```
If not found: move x; else move -x
If found: move x; else move -x
```

### 样例输出 #2

```
s/ not//g
```

## 样例 #3

### 样例输入 #3

```
abababa
cbc
```

### 样例输出 #3

```
s/aba/c/g
```

## 提示

时间限制: 2 s, 内存限制: 256 MB.


---

---
title: "[NWRRC 2013] Heavy Chain Clusterization"
layout: "post"
diff: 省选/NOI-
pid: P7086
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NWRRC 2013] Heavy Chain Clusterization
## 题目描述



A group of biologists is trying to find a cure for a viral disease. They have tried many antibodies of various origins that could potentially fight the viral antigens, and have selected $n$ antibodies that seem to work best during experiments.

Each antibody is identified by its heavy chain -- a sequence of amino acids.

The set of antibodies form a similarity cluster, if at least one of the following holds:

k-prefixes (first $k$ amino acids) of all their heavy chains are equal;

k-suffixes (last $k$ amino acids) of all their heavy chains are equal.

In order to simplify the future research, biologists want to group antibodies to similarity clusters.

You need to split the given antibodies to a minimum number of similarity clusters.


## 输入格式



The first line contains two integers $n$ and $k$ -- the number of heavy chains and the length of sequence of amino acids to coincide $(1 \le n \le 5 000 , 1 \le k \le 550)$ .

The following $n$ lines contain sequences of amino acids that form heavy chains of antibodies. Each amino acid described with an uppercase English letter. Each heavy chain contains at least $k$ and no more than $550$ amino acids.


## 输出格式



The first line of output must contain a single integer -- the minimum number of similarity clusters. The following lines must contain descriptions of clusters, one per line.

Each description starts with $m_i$ -- the number of antibodies in the cluster and is followed by $m_i$ integers -- numbers of these antibodies. Antibodies are numbered in the order of appearance in the input starting from one.

Each antibody must be present in exactly one cluster.


## 样例

### 样例输入 #1
```
4 1
AA
AB
BB
BA

```
### 样例输出 #1
```
2
2 1 2
2 3 4

```
### 样例输入 #2
```
3 2
ABA
BAB
XY

```
### 样例输出 #2
```
3
1 1
1 2
1 3

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

现有$n$个抗生素，每一个抗生素都可以通过它的一个氨基酸序列被辨认。

如果有一组抗生素满足以下任意一个条件，这些抗生素才可以形成一个“相似群体”：

1. 组内所有抗生素的氨基酸序列的前$k$个氨基酸元素组成的序列全部相同

2. 组内所有抗生素的氨基酸序列的后$k$个氨基酸元素组成的序列全部相同

特别的，一种抗生素可以成为一个相似群体。

为了简化后续研究，生物学家们想要给抗生素分类，使得这$n$个抗生素被分成若干个相似群体。你需要找出一种方案，使得分类后的相似群体数量最少。

------

第一行包含两个正整数，$n$和$k$，含义如题意描述。（$1≤n≤5000，1≤k≤550$）

接下来有$n$行，每行包含一个氨基酸序列。氨基酸序列被描述为由大写英语字母组成的字符串，每个序列包含不少于$k$个，不多于$550$个英文字符。每个英文字符代表一种不同的氨基酸。

------

第一行包含一个正整数$ans$，表示被分成的相似群体最小可能的数目。

接下来有$ans$行，每行第一个数为$m_i$，表示第$i$个相似群体有$m_i$个元素。接下来有$m_i$个数，第$j$个数表示这个相似群体包含输入中的第$j$个抗生素。（编号从$1$开始。）

每一个抗生素必须恰好出现一次。


---

---
title: "[NWRRC 2013] Intellectual Property"
layout: "post"
diff: 省选/NOI-
pid: P7087
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NWRRC 2013] Intellectual Property
## 题目描述



Erast Kopi is famous Sudoku puzzle designer. Resounding success of his puzzle compilations caused a number of imitations and plagiarisms. Prior to sending a lawsuit he decided to get more evidence.

Sudoku puzzle is a table $9 \times 9$ , divided into $3 \times 3$ subtables of $3 \times 3$ cells each. Each cell may contain a digit from $1$ to $9$ . The task is to fill empty cells with digits in a way that each row, each column and each of the $9$ subtables $3 \times 3$ contains each digit from $1$ to $9$ exactly once.

Kopi has a database of Sudoku puzzles and he wants to check if it contains similar puzzles. The puzzle $P$ is similar to the puzzle $Q$ , if it is possible to transform the puzzle $P$ into the puzzle $Q$ using a sequence of the following operations:

choose two digits $x$ and $y$ and replace all digits $x$ with $y$ and vice versa;

swap two triples of rows: $(1 , 2 , 3) , (4 , 5 , 6) , (7 , 8 , 9)$ ;

swap two rows in one triple of rows;

swap two triples of columns: $(1 , 2 , 3) , (4 , 5 , 6) , (7 , 8 , 9)$ ;

swap two columns in one triple of columns;

flip along top-left -- bottom-right axis. After this operation columns become rows and vice versa.

![](/upload/images2/ip.png)

Help Kopi to find similar puzzles in his database.


## 输入格式



The first line of the input contains single integer $n$ -- the number of puzzles in the database $(1 \le n \le 20)$ .

The rest of the input contains description of $n$ puzzles: $P_1 , P_2$ , . . . , Pn. Each puzzle is described by nine lines that contain nine characters each. Each character is either a digit from $1$ to $9$ , or a dot $(‘. ')$ denoting an empty cell. An empty line separates consecutive puzzles in the database.

There are no spaces in the input file.

The puzzles are not guaranteed to be solvable.


## 输出格式



Check if the puzzle $P_1$ is similar to puzzles $P_2$ , P3 , . . . , $P_n$ (in this order), than check if the puzzle $P_2$ is similar to puzzles P3 , P4 , . . . , $P_n$ (in this order) and so on.

If the puzzle $P_i$ is similar to the puzzle $Pj (1 \le i < j \le n)$ output `Yes`, otherwise output `No`. If the answer is positive, the next line should contain an integer qij -- the number of operations required to transform the puzzle $P_i$ to the puzzle $Pj$ . The number of operations is not required to be minimal, however it must not exceed $1000$ . In the following qij lines write the operations that transform the puzzle $P_i$ to the puzzle $Pj$ , one per line.

Operations are encoded in the following way:

`D $x$ y` for swapping digits $x$ and $y$ ;

`R a b` for swapping triples of rows (3a $− 2$ , 3a $− 1 , 3a)$ and (3b $− 2$ , 3b $− 1 , 3b);$

`r a b` for swapping rows a and $b$ , rows must belong to same triple of rows;

`C a b` for swapping triples of columns (3a $− 2$ , 3a $− 1 , 3a)$ and (3b $− 2$ , 3b $− 1 , 3b);$

`c a b` for swapping columns a and $b$ , columns must belong to same triple of columns;

`F` for flipping along top-left -- bottom-right axis.

The columns are numbered from left to right and the rows are numbered from top to bottom as they are given in the input file, starting from one.


## 样例

### 样例输入 #1
```
4
.....1...
1........
.2.....8.
.........
8....9...
.........
....7....
...2...1.
2...4....

....2....
...7.4...
8.......9
.8...2..1
..2......
.........
.........
..1.8....
.........

1........
.........
.........
.........
.........
.........
.........
.........
.........

.....1...
1........
.2.....8.
.........
8....9...
.........
....7....
...2...1.
2...4....

```
### 样例输出 #1
```
Yes
7
C 1 2
D 5 3
F
r 7 9
c 6 5
C 2 3
D 1 8
No
Yes
0
No
Yes
8
R 1 2
C 2 3
c 4 5
F
r 5 6
c 7 9
D 1 8
D 3 5
No

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

对于两个 $9\times9$ 数独谜题（不管是否有解）$A,B$，定义 $A$ 和 $B$ 等价当且仅当 $A$ 可以通过下列操作进行若干次变换后成为 $B$。
- 选择两个数字 $x,y$，将所有 $x$ 变成 $y$，所有 $y$ 变成 $x$。
- 在 $(1,2,3),(4,5,6),(7,8,9)$ 三个三元组中，选择两个，作为整体交换以它为下标的行。
- 选择在同一个三元组中的两个数 $x,y$，交换谜题的第 $x$ 行和第 $y$ 行。
- 在 $(1,2,3),(4,5,6),(7,8,9)$ 三个三元组中，选择两个，作为整体交换以它为下标的列。
- 选择在同一个三元组中的两个数 $x,y$，交换谜题的第 $x$ 列和第 $y$ 列。
- 把 $A$ 转置。

现在给定 $n(n\le20)$ 个数独谜题，判断它们两两是否等价。若等价，还需要输出一种变换的方法。`D x y` 表示将两个数字交换，`R a b` 表示整体交换三元组 $(3a-2,3a-1,3a),(3b-2,3b-1,3b)$ 对应的行，`r a b` 表示交换两个行，同理有 `C a b` 和 `c a b` 作为列操作。`F` 表示取转置。

translated by @Starlight237


---

---
title: "[NWRRC 2013] Lonely Mountain"
layout: "post"
diff: 省选/NOI-
pid: P7090
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NWRRC 2013] Lonely Mountain
## 题目描述



"This was made by Thror, your grandfather, Thorin", he said in answer to the dwarves' excited questions. "It is a plan of the Mountain. "

---

J. R. R. Tolkien. The Hobbit, or There and Back Again

The plan of the Lonely Mountain consists of two parallel projections of the mountain to two projection planes. Both planes are perpendicular to the ground and each other. Each projection has a mountain-like shape.

![](https://www.acmicpc.net/upload/images2/lonely.png)

Since Bilbo Baggins has never seen the mountain, he tries to imagine it. Is it really the Lonely Mountain or some ridges and other mountains surround it? In any case, it must be tremendous to hold the whole dwarves' kingdom!

Bilbo decided to estimate the maximum possible volume of the Lonely Mountain and nearby mountains (if any) based on the plan provided by Gandalf.


## 输入格式



The first line contains single integer number $n_{x}$ -- the number of points in the parallel projection of the mountain to the plane Oxz $(2 \le n_{x} \le 100 000)$ . The second line contains $n_{x}$ pairs of integer numbers $x_{i}, z_{i}$ -- the coordinates of the polygonal chain, representing the projection $(−10^{9} \le x_{1} < x_{2} <$ x3 $< · · · < x_{n_{x}} \le 10^{9}; 0 \le z_{i} \le 10^{9}; z_{1} = z_{n_{x}} = 0)$ .

The following two lines contain projection to the Oyz plane in the same format.


## 输出格式



The only line of the output file must contain a single number $V$ -- the maximum possible volume of the Lonely Mountain.

The absolute or relative precision of you answer should be at least $10^{−6}.$ E.g . if $V′is$ the actual maximum possible volume, the following must hold: $mi_n(|V−V′|,|V−V′|/V′) \le 10^{−6}.$

If there are no mountains corresponding to the given projections, output a single line `Invalid plan`.


## 样例

### 样例输入 #1
```
6
0 0 1 1 2 0 3 3 4 4 6 0
5
0 0 1 1 2 1 3 4 4 0

```
### 样例输出 #1
```
21.824074074074074073

```
### 样例输入 #2
```
3
-1 0 0 1 2 0
4
0 0 1 1 2 2 3 0

```
### 样例输出 #2
```
Invalid plan

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给定一个几何体的正视图和侧视图，求其最大体积。

### 输入格式

第一行一个整数 $n_x$ 表示正视图中点的数量。

第二行按 $x_i$ 递增的顺序给出 $n_x$ 个点对 $(x_i,z_i)$ 描述其正视图，保证 $z_1=z_{n_x}=0$

第三、四行同理，描述其侧视图。

所有的输入都是整数。

### 输出格式

若不存在一个合法方案，输出 ```Invalid plan```，否则输出最大体积。

你的答案与正确答案的绝对误差不应超过 $10^{-6}$.


---

---
title: "[CERC2014] Can't stop playing"
layout: "post"
diff: 省选/NOI-
pid: P7093
tag: ['2014', 'Special Judge', 'ICPC']
---
# [CERC2014] Can't stop playing
## 题目描述

Some computer games are extremely fun and this problem may be about one of these.

You are given a sequence of one dimensional blocks, each of length that is a power of two.
The goal of the game is to merge all the blocks into one big block. The blocks are presented
one by one, and for each one you have to decide whether to stick it immediately to the left or
immediately to the right of the previous blocks.

Every time two blocks of the same size are adjacent, they merge into one block that is twice
as long as each of them. Note that, as long as possible, the resulting blocks immediately merge
with adjacent ones. For example, if the current sequence of blocks is $2, 4, 16$, then sticking $2$ on
the left side leads to $8, 16$, while sticking it on the right side gives $2, 4, 16, 2$. Note that at any
moment there is at most one mergeable pair of blocks.

You have lost the game (again!) and you are wondering whether there was any way to win at all. Analyze the sequence to find out.
## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

Each test case consists of two lines. The first one contains a positive integer $n \leq 1 000$ – the
length of the sequence. The next line contains a sequence of $n$ block lengths, each a power of two. The sum of all the lengths does not exceed $2^{13}$.
## 输出格式

For each test case, output one line containing the word $\texttt{no}$ if winning the game is not possible. Otherwise, output a word consisting of $n$ letters $\texttt{l}$ and $\texttt{r}$, denoting whether the corresponding block should be stuck to the left or to the right. Note that for the first block it does not matter.
## 样例

### 样例输入 #1
```
3
9
2 8 4 1 1 4 4 4 4
5
2 16 4 8 2
3
2 2 2
```
### 样例输出 #1
```
rrrlllrrr
no
no
```
## 题目翻译

### 题目描述
你有一个双端队列，同时给定一个长度为 $n$ 的序列 $a$ ，满足序列中的元素为 2 的非负整数幂  

从前到后遍历整个序列，每次对于 $a_i$ 可以选择将它放入双端队列的队头或者队尾，如果队列中存在相邻两个元素大小相同，那么它们将合并为一个新的元素，元素大小为先前两个元素之和

求是否存在一个合法的方案使得队列最后只剩下一个元素，若存在，输出方案，不存在输出 $no$

多组数据

### 读入格式

首先读入一个 $t$ 表示数据组数

对于每一组数据第一行读入一个 $n$ 表示序列长度，下一行读入 $n$ 个元素，$a_1$ 到 $a_n$ 

### 输出格式

若存在合法方案输出一个字符串，其中第 $i$ 个字符若为 $l$ 表示放入队头，$r$ 表示放入队尾,其中第一个元素 $l,r$ 任意

若不存在合法方案，输出 `no`


---

---
title: "[CERC2018] The ABCD Murderer"
layout: "post"
diff: 省选/NOI-
pid: P7456
tag: ['字符串', '2018', '哈希 hashing', 'AC 自动机', 'KMP 算法', '后缀数组 SA', 'ICPC']
---
# [CERC2018] The ABCD Murderer
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The ABCD Murderer](https://contest.felk.cvut.cz/18cerc/solved/abcd.pdf)**

Oscar 特别喜欢看犯罪电影。他钦佩那些罪犯，因为他们富有创造力。他也想展示他的创造力。但很可惜的是，他没什么经验，也想不出来什么原创伎俩。所以他想从已有的招数中寻找灵感。他一直喜欢看罪犯从报纸上剪下字母，然后用这些字母拼勒索信的桥段。然而 Oscar 根本不想抄袭，所以他自己想了一个这种方法的变体。他觉得把字母一个一个拼成文本既无聊又费时间。所以他决定通过剪下一整个单词的方式拼出自己的勒索信。

Oscar 买来一些主流报纸，这样他几乎就有了无限的单词库。他可以多次剪出任意特定的单词。然而，他还是被报纸中出现的的单词集限制。问题是一些单词根本没在报纸中出现。为了让这项工作更简单，他决定去除勒索信中所有的标点符号和空格并且忽略字母的大小写。他同时允许剪出的单词互相重叠，只需要重叠部分相同。现在 Oscar 想知道他至少要剪下多少次单词才能拼成他想要的勒索信。
## 输入格式

第一行包含一个整数 $L$，表示在报纸中发现的单词数；

下一行包含勒索信的内容 $s$。保证内容非空并且只包含小写英文字母。

接下来 $L$ 行，每行包含一个在报纸中出现的单词 $a_i$，保证只出现小写英文字母。这些单词中没有空串，也没有比勒索信长的单词。所有报纸中单词在输入中出现至少一次。
## 输出格式

输出 Oscar 最少要从报纸中剪下多少次单词才能组成勒索信、如果不能组成，输出 $-1$ 。每个单词都要被记实际从报纸剪下那么多次。
## 样例

### 样例输入 #1
```
3
aaaaa
a
aa
aaa
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
abecedadabra
abec
ab
ceda
dad
ra
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
9
icpcontesticpc
international
collegiate
programming
contest
central
europe
regional
contest
icpc
```
### 样例输出 #3
```
3
```
## 提示

$1≤L,|s|,∑|a_i|≤3×10^5$


---

---
title: "[CERC2018] The Bridge on the River Kawaii"
layout: "post"
diff: 省选/NOI-
pid: P7457
tag: ['2018', 'ICPC']
---
# [CERC2018] The Bridge on the River Kawaii
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/)[ The Bridge on the River Kawaii](https://contest.felk.cvut.cz/18cerc/solved/bridge.pdf)**

在一个遥远的，叫做 Midsommer 的地方，有一条叫做 delta 的小河。河里流的是深紫色的酸，所以不可能在那里游泳。这条河周围有一些小岛，并且有桥连接它们。每座桥都有一个危险系数，表示通过这座桥有多危险。危险系数越高，通过这座桥就越危险。

一位叫做 Richard Hradecki 的侦探兼悬疑小说作家经常需要通过这些桥来追查案件。在所有可能的路径中，他更倾向于选择最安全的一条，也就是这条路径上经过桥的最大危险系数越低越好。

为了规划路线，Richard 经常让你为他找从一个岛到他要调查的岛的最安全路线。为了满足他的需求，你需要连续处理以下三种事件：

- 当地人在两座岛屿之间建了一座新桥；
- 一只酸性的并且毛茸茸的大粉熊 Lug 出现了，并摧毁了一座桥；
- Richard 要求你找两个岛屿之间的最安全路线。
## 输入格式

第一行包含两个整数 $N,Q$。$N$  是岛屿数（岛屿用 $0…N-1$ 标号），$Q$ 是需要处理的事件数。

接下来 $Q$ 行，每行表示一个事件，包含三或四个整数，说明如下：

- $0XYV$：在 $X$ 岛与 $Y$ 岛之间刚建成一座危险系数为 $V$ 的桥；
- $1XY$：连接 $X,Y$ 两岛的桥刚被摧毁；
- $2XY$：Richard 询问从 $X$ 到 $Y$ 的最安全路径。

对于所有类型的询问，$X,Y$ 表示一对合法的岛屿。保证任意两个岛屿之间最多只存在一座直达的桥，要被摧毁的桥在那一刻是存在的。
## 输出格式

对于每个种类为 $2$ 的事件，输出 $X$ 到 $Y$ 最安全路径上经过的最危险的桥的危险系数。如果 $X$ 与 $Y$ 之间没有路径，输出 $-1$。
## 样例

### 样例输入 #1
```
6 15
0 1 2 1
2 1 4
2 1 5
0 2 3 2
2 1 4
2 1 5
0 3 4 3
2 1 4
2 1 5
0 4 5 4
2 1 4
2 1 5
1 4 5
2 1 4
2 1 5
```
### 样例输出 #1
```
-1
-1
-1
-1
3
-1
3
4
3
-1
```
### 样例输入 #2
```
6 6
0 2 0 4
0 3 4 3
0 0 4 1
0 2 5 4
2 3 2
2 4 2
```
### 样例输出 #2
```
4
4
```
## 提示

$2≤N≤10^5,1≤Q≤10^5,0≤V≤10,0≤X,Y<N,X≠Y$


---

---
title: "[CERC2018] The Lord of the Kings"
layout: "post"
diff: 省选/NOI-
pid: P7463
tag: ['2018', 'ICPC']
---
# [CERC2018] The Lord of the Kings
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The Lord of the Kings](https://contest.felk.cvut.cz/18cerc/solved/king.pdf)**

在多年与海外国家的战争后，我们的国家终于成功去除了大多数反动势力和敌人。如此光辉的胜利应该被长时间记住并庆祝。因此，我们的国王宣布将胜利日这一天定为一个公共节日，并且要举行胜利游行。在游行中，军队会跟着国王从他的宫殿出发，访问国家里的每个城市。

国王和他的随从将一种环保的电动直升机作为交通工具。这种直升机有一个缺点，就是它的航程较短。国王让你和你的顾问在一些农场和所有城市中修建停机坪，使得从他的宫殿出发，经过一些停机坪后都可以到达任何城市。然而，建停机坪和基础设施都很费钱。所以要最小化最小化停机坪的修建数量。

此外，由于直升机特殊的设计，国王和他的士兵需要以特殊的方式移动，这就会影响停机坪的数量和位置。

给你一张这个国家的矩形网格地图，其中包含代表村庄，城市和宫殿的网格。同时，也给你了直升机的移动方式——与国际象棋中「车（Rook）」、「后（Queen）」、「象（Bishop）」、「马（Knight）」或「王（King）」之一的移动方式一样（每种棋子的详细移动方式见「数据范围与提示」）。你的任务是求出最少需要在多少农场或城市修停机坪才能够满足国王的需求。国王的宫殿中已经修建了停机坪，因此不需要修一个新的了。
## 输入格式

第一行包含两个整数 $N,M$，表示我们的国家有 $N$ 行 $M$ 列；

第二行两个整数 $X,Y$，表示国王宫殿的位置，接着一个字符，表示移动方式（R——车，Q——后，B——象，N——马，K——王）；

第三行包含一个整数 $T$，表示国家里的城市数；

接下来 $T$ 行，每行包含两个整数 $W,Z$，表示一个城市的位置。所有城市都在不同的网格中，没有城市和宫殿位于同一格。所有既不代表城市也不代表宫殿的格子都是农场。
## 输出格式

输出一行一个整数，表示至少要修建多少停机坪。如果不可能使得国王和他的士兵能够到达每一个城市，输出 $-1$。
## 样例

### 样例输入 #1
```
3 3
3 1 K
2
1 1
1 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 3
3 1 Q
2
1 1
1 3
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
5 5
4 4 R
4
1 2
2 1
2 5
5 1
```
### 样例输出 #3
```
6
```
## 提示

$1 ≤ N, M ≤ 15,1 ≤ T ≤ 10, 1 ≤ X ,W ≤ N,1≤Y, Z≤M$

下图为直升机的运输方式（同国际象棋对应棋子的行棋规则）：
![#1](https://cdn.luogu.com.cn/upload/image_hosting/ip5cnfsa.png)


---

---
title: "[ICPC 2020 WF] Ley Lines"
layout: "post"
diff: 省选/NOI-
pid: P8133
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Ley Lines
## 题目背景

ICPC2020 WF F
## 题目描述

In 1921, the amateur archaeologist Alfred Watkins coined the term
"ley lines" to refer to straight lines between numerous places of
geographical and historical interest. These lines have often been
associated with mysterious and mystical theories, many of which still
persist.

One of the common criticisms of ley lines is that lines one draws on a
map are actually of non-zero width, and finding "lines" that connect
multiple places is trivial, given a sufficient density of points and a
sufficiently thick pencil. In this problem you will explore that
criticism.

For simplicity, we will ignore the curvature of the earth, and just assume
we are dealing with a set of points on a plane, each of which has a
unique $(x, y)$ coordinate, and no three of which lie on a single
straight line. Given such a set, and the thickness of your pencil,
what is the largest number of points through which you can draw a
single line?
## 输入格式

The first line of input consists of two integers $n$ and $t$, where
$n$ ($3 \le n \le 3\,000$) is the number of points in the set
and $t$ ($0 \le t \le 10^9$) is the thickness of the pencil.
Then follow $n$ lines,
each containing two integers $x$ and $y$ ($-10^9 \le x, y \le 10^9$),
indicating the coordinates of a point in the set.

You may assume that the input is such that the answer would not change
if the thickness $t$ was increased or decreased by $10^{-2}$, and that no
three input points are collinear.
## 输出格式

Output the maximum number of points that lie on a single "line" of
thickness $t$.
## 样例

### 样例输入 #1
```
4 2
0 0
2 4
4 9
3 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 1
0 10
2000 10
1000 12
```
### 样例输出 #2
```
2
```
## 题目翻译

1921 年，业余考古学家 Alfred Watkins 提出了 _Ley lines_ 的概念，指的是连接众多地理和历史名胜的直线。这些线常常与神秘的理论联系在一起，其中许多至今仍在流传。

对 _Ley lines_ 的一个常见争议是，人们在地图上绘制的线的宽度实际上并非为 $0$，考虑到足够密集的点和足够宽的铅笔，找到连接多个地方的“线”是很容易的。为了探讨这种争议，你决定亲自在一个二维平面上亲自实践。

现在，这个二维平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，并且没有三个点在同一条直线上。你有一个宽度为 $t$ 的铅笔，你想知道你用这支铅笔画一条线，最多能够连接多少个不同的点。你可以假设在 $t$ 增加或减少 $10^{-2}$ 的情况下，答案是不会改变的。

数据范围：

- $3\leqslant n\leqslant 3000$，$0\leqslant t\leqslant 10^9$。
- $-10^9\leqslant x_i,y_i\leqslant 10^9$。

Translated by Eason_AC


---

---
title: "[ICPC 2020 WF] Quests"
layout: "post"
diff: 省选/NOI-
pid: P8136
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Quests
## 题目背景

ICPC2020 WF I
## 题目描述

To relax before competing in the ICPC World Finals, you have decided to play a
computer game called *Quests*. You have played it a
number of times already, and now you want to achieve a perfect
playthrough---to prepare for your perfect playthrough of the finals!

In the game, you have to complete a number
of quests, and you earn experience points (XPs) for completing each one. The
total number of XPs you have earned at any time determines your current level. You
reach a new level for every $v$ XPs that you earn. Formally, your level at
any time is the largest integer $L$ such that you have at least $L \cdot v$
XPs.

Each quest is assigned a number $x$ of XPs and a target
difficulty level $d$. If you complete the quest when your level is at least
$d$, you earn $x$ XPs. However, if you complete the quest when your level is
less than $d$, you will earn $c \cdot x$ XPs. The constant  $c$ is an XP multiplier
that results in a bonus for completing a
quest when you are at a lower level than the recommended level $d$.

You know all the $n$ quests and their respective $x$ and $d$ numbers by heart
(and you know the numbers $v$ and $c$ as well---you have played this game a lot).
You are also skilled enough to
complete any quest, regardless of its target difficulty level and your level.
You want to complete all the quests in an order that will allow you
to earn the largest possible number of XPs.

For example in the sample input, the maximum XPs you can earn is 43, which
is done as follows. First complete the second quest (you earn $4$ XPs,
because you are at level $0$, and you completed a quest with target difficulty
level $2$). Then complete the first quest (you earn $30$ XPs, because you are
still at level $0$, and the target difficulty level is $1$). With $34$ XPs, you
are now level $3$. Finally, complete the third quest (for which you earn $9$
XPs, without the multiplier, since you are already at level $3$).
## 输入格式

The first line of input contains three integers $n$, $v$, and $c$, where
$n$ $(1 \leq n \leq 2\,000)$ is the number of quests in the game, $v$
$(1 \leq v \leq 2\,000)$ is the number of XPs required to reach each level,
and $c$ $(2 \leq c \leq 2\,000)$ is the XP multiplier for completing a quest
before reaching its target difficulty level.

Following that are $n$ lines, each of which contains two integers $x$ and $d$
describing one quest, where $x$ $(1 \leq x \leq 2\,000)$ is the number of XPs
you earn for completing that quest if you are at or above its target difficulty
level and $d$ $(1 \leq d_i \leq 10^6)$ is the target difficulty level for that
quest.
## 输出格式

Output the maximum possible number of XPs you could earn by finishing all the
quests.
## 样例

### 样例输入 #1
```
3 10 2
15 1
2 2
9 1
```
### 样例输出 #1
```
43
```
## 题目翻译

为了在 ICPC 之前放松，小 A 决定玩一个名叫 _Quests_ 的游戏。你之前已经玩了很多次，因此这次你决定打一盘最完美的游戏——为你在决赛中的完美表现作准备！

游戏中你需要完成若干个任务，完成每一个任务都可以积攒经验值。你在某一时刻积攒的在总经验值决定了你的游戏等级，具体地，每次达到一个新的等级需要 $v$ 点经验值，也就是说，假设你在某一时刻积攒的总经验值为 $X$，那么你在该时刻的等级就是最大的满足 $L\cdot v\leqslant X$ 的整数 $L$。

游戏中的第 $i$ 个任务的设定经验值为 $x_i$，参考难度为 $d_i$。如果你在等级 $\geqslant d_i$ 的情况下完成了第 $i$ 个任务，那么你将获得 $x_i$ 点经验值。然而，如果你在等级 $<d_i$ 的情况下完成了第 $i$ 个任务，那么你将获得 $c\cdot x_i$ 点经验值。

现在，你已经知道了 $v,c$ 的值以及所有任务的设定经验值 $x_i$ 和参考难度 $d_i$，你想知道在按照某一特定顺序依次完成任务的情况下，能够攒到的总经验值最大是多少。

数据范围：

- $1\leqslant n,v\leqslant 2000$，$2\leqslant c\leqslant 2000$。
- $1\leqslant x_i\leqslant 2000$，$1\leqslant d\leqslant 10^6$。

Translated by Eason_AC


---

---
title: "[ICPC 2020 WF] Trailing Digits"
layout: "post"
diff: 省选/NOI-
pid: P8140
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Trailing Digits
## 题目背景

ICPC2020 WF M
## 题目描述

A large shipment of doodads has just arrived, and each doodad has a suggested retail price of $b$ cents. You've noticed that consumers are much more likely to purchase goods when most of the trailing digits are the same. For example, items are more likely to be priced at $99$ cents rather than $57$ cents. So to make your goods more appealing, you've decided to sell your goods in bundles. To make a bundle, you choose a positive integer $k$, and sell $k$ doodads for $k \times b$ cents. With an appropriate choice of $k$ you can have a more pleasing price. For example, selling $57$-cent doodads in bundles of size $7$ means that each bundle sells for $399$ cents, which has two trailing $9$s, rather than no trailing $9$s of $57$. This idea of trailing $9$s can be generalized to any other trailing digit: bundles of $692$ $57$-cent doodads sell for $39\,444$ cents (three trailing $4$s) and bundles of one million doodads sell for $57\,000\,000$ cents (six trailing $0$s).

After a little thought, you realize that you do not want to make your bundles too large---not only can the price be excessive, but who really needs several million doodads? For any type of doodad, your marketing department has a maximum bundle price of $a$.

Given the price of a doodad, the desired trailing digit, and the maximum price of a bundle, write a program that optimizes the trailing digits.
## 输入格式

Input consists of a single line containing three integers $b$, $d$, and $a$, where $b$ ($1 \leq b < 10^{6}$) is the price of a doodad in cents, $d$ ($0 \leq d \leq 9$) is the desired trailing digit, and $a$ ($b \leq a < 10^{10\,000}$) is the maximum price of a bundle.
## 输出格式

Output the maximum number of consecutive occurrences of $d$ that can appear at the end of a bundle price, given that the price of the bundle cannot exceed $a$.
## 样例

### 样例输入 #1
```
57 9 1000
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
57 4 40000
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
57 4 39000
```
### 样例输出 #3
```
2
```
## 题目翻译

## 题目描述
有一批货，每个价值 $b$ 元，可以把 $n$ 个货打包出售，价格是 $b \times n$ 元（前提是$b \times n\le a$），使末尾含有尽可能多的数字 $d$ ，求最多的 $d$ 数量。
## 输入格式
一行三个整数，$b$ , $d$ 和 $a$。
## 输出格式
一个整数，最多的 $d$ 数量。
## 说明/提示
对于全部数据，有 $1 \le b < 10^6$ , $0 \le d \le 9$ , $b \le a < 10^{10000}$


---

---
title: "[ICPC 2022 Xi'an R] Bridge"
layout: "post"
diff: 省选/NOI-
pid: P9358
tag: ['平衡树', '2022', 'O2优化', '动态树 LCT', 'ICPC']
---
# [ICPC 2022 Xi'an R] Bridge
## 题目描述

There are $n$ countries numbered from $1$ to $n$ in Erathia. Each country can be regarded as a chain with $m+1$ nodes numbered from $1$ to $m+1$. Initially, node $(a, b)$ is connected with node $(a, b + 1)$ by a street where node $(a, b)$ denotes the $b$-th node of the $a$-th country. There are no bridges between any two countries at first. 

You need to process $q$ queries of the following two types.

- $1\ a\ b$ ($1\leq a < n, 1\leq b\leq m$). Build a bridge between node $(a, b)$ and node $(a + 1, b)$. It is guranteed that at any time, **each node is connected with at most one bridge**.
- $2\ a$ ($1\leq a\leq n$). A hero will walk through Erathia. This hero starts from $(a, 1)$. If the hero is at $(x, y)$ and there is a unvisited bridge connected to him, he passes it, or he goes to $(x, y + 1)$. Once he arrived the $(m+1)$-th node of any conutry, he stops. Please note that 'unvisited bridge' is **independently** judged for each query. 

Your task is to print which country the hero is in at last for the second kind of query. It can be proved that the hero's route is always unique under these constraints.

## 输入格式

The first line contains three integers $n$, $m$ and $q$ ($1 \leq n, m, q \leq 10 ^ 5$).

Each of the following $q$ lines represents a query with format described above.
## 输出格式

For each query of type $2$, output a line with an integer representing the answer.

## 样例

### 样例输入 #1
```
3 4 13
2 2
1 1 3
2 1
2 2
2 3
1 2 4
2 1
2 2
2 3
1 2 1
2 1
2 2
2 3

```
### 样例输出 #1
```
2
2
1
3
3
1
2
3
2
1

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem A.

**Author**: MonkeyKing.
## 题目翻译

### 题目描述

Erathia 大陆上有 $n$ 个国家，从 $1$ 到 $n$ 编号。每个国家可以看成由 $m + 1$ 个结点组成的链，结点从 $1$ 到 $m + 1$ 编号。结点 $(a, b)$ 和 $(a, b + 1)$ 由一条街道连接，其中 $(a, b)$ 表示国家 $a$ 的第 $b$ 个结点。一开始，国家之间没有桥。

你需要处理 $q$ 个操作：

- $1\ a\ b$（$1\leq a < n$，$1\leq b\leq m$）：在 $(a, b)$ 和 $(a + 1, b)$ 之间建造一座桥。**保证每个结点最多和一座桥相连**。
- $2\ a$（$1\leq a\leq n$）：一名英雄走过 Erathia 大陆。他从 $(a, 1)$ 出发。如果这名英雄当前在结点 $(x, y)$ 且有一座未被访问过的桥与之连接，那么他会走过这个桥到达桥的另一端，否则他会走到 $(x, y + 1)$。一旦他到达某个国家的第 $m + 1$ 个结点，他就会停下来。注意两个询问之间的 “未被访问过的桥” 是独立的。

你的任务是对每个操作 $2$ 求出英雄最终所在的国家。

$1\leq n, m, q\leq 10 ^ 5$。

### 输入格式

第一行三个整数 $n, m, q$。

接下来 $q$ 行，每行若干个整数表示一组询问。格式见题目描述。

### 输出格式

对于每个操作 $2$，输出一行一个整数表示答案。




---

---
title: "[ICPC 2022 Xi'an R] Contests"
layout: "post"
diff: 省选/NOI-
pid: P9361
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Contests
## 题目描述

There are $n$ contestants and they take part in $m$ contests. You are given the ranklist of each contest. The ranklist of the $k$-th contest is a sequence $a_k$, indicating that the $a_{k, i}$-th contestant's rank is $i$.

SolarPea and PolarSea are two of the $n$ contestants. SolarPea wants to prove that he is stronger than PolarSea.

Define $x$ is $l$-stronger than $y$, if and only if there exists a sequence $b$ of length $l + 1$, such that $b_1 = x$, $b_{l + 1} = y$, and for all $1\leq i\leq l$, $b_i$ has a smaller rank than $b_{i + 1}$ in at least one contest.

There are $q$ queries. In the $i$-th query, SolarPea is contestant $x$ and PolarSea is contestant $y$. Please find the minimum positive number $l$ such that SolarPea is $l$-stronger than PolarSea.
## 输入格式

The first line contains two integers $n$ ($2\leq n\leq 10 ^ 5$) and $m$ ($1\leq m\leq 5$).

The $i$-th of the next $m$ lines contains $n$ intergers $a_{i, 1}, a_{i, 2}, \ldots, a_{i, n}$. It is guaranteed that $a_i$ is a permutaion of $1,2,\ldots,n$.

The next line contains an integer $q$ ($1\leq q\leq 10 ^ 5$).

Each of the next $q$ lines contains two integers $x$ and $y$ ($1 \le x,y \le n, x \neq y$), representing a query.
## 输出格式

For each query, output a number $l$ representing the answer. If there is no legal $l$, output $-1$.
## 样例

### 样例输入 #1
```
6 2
1 3 2 5 4 6
2 1 4 3 6 5
4
1 4
5 3
6 1
5 2

```
### 样例输出 #1
```
1
2
5
3

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem D.

**Author**: csy2005.
## 题目翻译

### 题目描述

$n$ 个选手参加了 $m$ 场比赛。给出每场比赛的排行榜。第 $k$ 场比赛的排行榜是一个 $n$ 阶排列 $a_k$，表示选手 $a_{k, i}$ 的排名为 $i$。

SolarPea 和 PolarSea 也是选手。SolarPea 想要证明他比 PolarSea 更强。

定义选手 $x$「$l$ - 强于」选手 $y$，当且仅当存在长度为 $l + 1$ 的序列，满足 $b_1 = x$，$b_{l + 1} = y$，且对于所有 $1\leq i\leq l$，均有 $b_i$ 在至少一场比赛中排名小于 $b_{i + 1}$。

给出 $q$ 组询问。在第 $i$ 组询问中，SolarPea 是选手 $x$，PolarSea 是选手 $y$。求出最小的正整数 $l$，使得 $x$「$l$ - 强于」$y$。

$2\leq n\leq 10 ^ 5$，$1\leq q\leq 10 ^ 5$，$1\leq m\leq 5$，$1\leq x, y\leq n$，$x\neq y$。

### 输入格式

第一行两个整数 $n, m$。

接下来 $m$ 行，每行 $n$ 个整数，表示第 $i$ 场比赛的排行榜。保证 $a_i$ 是 $1, 2, \ldots, n$ 的排列。

接下来一行一个整数 $q$。

接下来 $q$ 行，每行两个整数 $x, y$ 表示一组询问。

### 输出格式

对于每组询问，输出一行一个整数表示答案。若不存在这样的 $l$，输出 $-1$。




---

---
title: "[ICPC 2022 Xi'an R] Power of Two"
layout: "post"
diff: 省选/NOI-
pid: P9365
tag: ['2022', 'Special Judge', 'O2优化', '构造', 'ICPC', '分类讨论']
---
# [ICPC 2022 Xi'an R] Power of Two
## 题目描述

$$
2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2}}}}}}}}}
$$

SolarPea likes blowing up PolarSea's blog by sending power tower of $2$. As the tower is too high, the stack of the web page overflows. So the blog no longer works.

Now SolarPea has $n$ powers of two $a_1, a_2, \ldots, a_n$, $x$ bitwise AND operators, $y$ bitwise OR operators and $z$ bitwise XOR operators. It is guaranteed that $n = x + y + z$.

Solarpea wants to construct an arithmetic expression with these numbers and operators. Formally, define $x_0 = 0$ and $x_i = x_{i - 1}\ \mathrm{op}_i\ b_i$, where $b$ is a permutation of $a$, which means we can rearrange $a$ to get $b$, and $\mathrm{op}_i$ is one of the three types of bitwise operators above. Then $x_n$ is the result of the expresstion.

The larger the expression, the more likely it is to make PolarSea's blog unable to work. SolarPea wants you to help him to find the largest $x_n$ and construct such an expression. If there are multiple solutions, output any of them.

You need to process $T$ test cases independently.
## 输入格式

The first line contains a single integer $T$ ($1\leq T \leq 10 ^ 5$), denoting the number of test cases.

For each test case, the first line contains four integers $n$, $x$, $y$ and $z$ ($0\leq x, y, z\leq n \leq 65\,536, n = x + y + z$). The next line contains $n$ integers $c_1, c_2, \ldots, c_n$ ($0\leq c_i < n$), where $a_i = 2 ^ {c_i}$.

It is guaranteed that the sum of $n$ over all test cases is no more than $1\,048\,576$.
## 输出格式

For each test case, output three lines.

The first line contains a $01$-string of length $n$, representing the binary form of the largest $x_n$.

The next line contains a single $1$-indexed string $\mathrm{op}$ of length $n$, where $\mathrm{op}_i$ represents the $i$-th operator. Here, we denote AND as `&` (ASCII 38), OR as `|` (ASCII 124), and XOR as `^` (ASCII 94). You should guarantee that there is exactly $x$ AND operators, $y$ OR operators and $z$ XOR operators.

The third line contains $n$ integers $d_1, d_2, \ldots, d_n$, the $i$-th of which representing the logarithm of $b_i$ with base $2$. That is, $d$ is a permutaion of $c$.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
4
4 3 0 1
1 0 1 0
4 1 0 3
1 0 1 0
8 0 2 6
1 5 5 7 1 5 5 7
8 0 0 8
1 5 5 7 1 5 5 7

```
### 样例输出 #1
```
0010
&&^&
0 0 1 1
0011
^^&^
0 1 0 1
10100000
^^|^^^^|
1 5 5 7 1 5 5 7
00000000
^^^^^^^^
1 5 5 7 1 5 5 7

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem H.

**Author**: Alex_Wei.

![](https://cdn.luogu.com.cn/upload/image_hosting/g2frgx9s.png)
## 题目翻译

## 题目描述
SolarPea 喜欢通过发送电力塔来炸毁 PolarSea 的博客 $2$。由于塔太高，网页的堆栈溢出。所以博客已经不能用了。  

现在 SolarPea 拥有两个 $a_1、a_2、ldots、a_n$、$x$ 位 AND 运算符、$y$ 位 OR 运算符和 $z$ 位 XOR 运算符的 $n$ 次方。保证 $n = x + y + z$。  

Solarpea 希望使用这些数字和运算符构造一个算术表达式。正式地定义 $x_0 = 0$ 和 $x_i = x_{i - 1}\ \mathrm{op}_i\ b_i$，其中 $b$ 是 $a$ 的排列，这意味着我们可以重新排列 $a$ 来得到 $b$，而 $\mathrm{op}_i$ 是上述三种类型的按位运算符之一。那么 $x_n$ 就是表达式的结果。

表达式越大，就越有可能使 PolarSea 的博客无法工作。SolarPea 希望你帮他找到最大的 $x_n$ 并构造这样的表达式。如果有多个解决方案，则输出其中任何一个。

您需要独立处理 $T$ 个测试用例。
## 输入格式
第一行包含一个整数 $T $ （$1\leq T \leq 10 ^ 5$），表示测试用例的数量。  

对于每个测试用例，第一行包含四个整数 $n$， $x$， $y$ 和 $z$ （$0\leq x, y, z\leq n \leq 65\,536, n = x + y + z$）。下一行包含 $n$ 个整数 $c_1, c_2, \ldots, c_n$ ($0\leq c_i < n$)，其中 $a_i = 2 ^ {c_i}$。

保证所有测试用例的 $n $ 之和不超过 $1\,048\,576$。  
## 输出格式
对于每个测试用例，输出 3 行。  

第一行包含一个长度为 $n$ 的 $01$ 字符串，表示最大 $x_n$ 的二进制形式。  

下一行包含一个长度为 $n$ 的 $1$ 索引字符串 $\mathrm{op}$，其中 $\mathrm{op}_i$表示第 $i$ 个运算符。在这里，我们将 AND 表示为 `&` （ASCII 38），OR 表示为 `|` （ASCII 124），将 XOR 表示为 `^` （ASCII 94）。您应该保证正好有 $x $ AND 运算符、$y$ OR 运算符和 $z$ XOR 运算符。

第三行包含 $n$ 个整数 $d_1, d_2, \ldots, d_n$，其中第 $i$ 个代表 $b_i$ 的对数，以 $2$ 为底。也就是说，$d$ 是 $c$ 的排列。

如果有多个解决方案，则输出其中任何一个。

## 输入输出样例
无
## 提示
**来源**：2022 ICPC 亚洲习安区域赛问题 H.  
**作者**： Alex_Wei.


---

---
title: "[ICPC 2022 Xi'an R] Streets"
layout: "post"
diff: 省选/NOI-
pid: P9368
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Streets
## 题目描述

You are given $n$ vertical lines with x-coordinates $x_1, x_2, \ldots, x_n$ and weights $a_1, a_2, \ldots, a_n$ and $m$ horizontal lines with y-coordinates $y_1, y_2, \ldots, y_m$ and weights $b_1, b_2, \ldots, b_m$.

Call a rectangle good if and only if all of its four edges lie on the given lines. On this basis, define the cost of a good rectangle as the sum of the costs of its four segments. The cost of a segment is the product of its length and the weight of the line it belongs.

Find the maximum area of good rectangles with cost no more than $c$. Note that the length and the width of the rectangle can be zero, so the answer always exists.

You need to answer $T$ queries with different $c$.
## 输入格式

The first line contains three integers $n$, $m$ ($2\leq n, m\leq 5\,000$) and $T$ ($1\leq T\leq 100$).

The second line contains $n$ integers $x_1, x_2, \ldots, x_n$ ($1\leq x_1 < x_2 < \ldots < x_n \leq 10 ^ 5$).

The third line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1\leq a_i\leq 10 ^ 7$).

The fourth line contains $m$ integers $y_1, y_2, \ldots, y_m$ ($1\leq y_1 < y_2 < \ldots < y_m \leq 10 ^ 5$).

The fifth line contains $m$ integers $b_1, b_2, \ldots, b_m$ ($1\leq b_i\leq 10 ^ 7$).

Each of the next $T$ lines contains a single integer $c$ ($1\leq c\leq 4\times 10 ^ {12}$), representing a query.
## 输出格式

For each query, output one line representing the answer.
## 样例

### 样例输入 #1
```
3 4 20
1 3 4
3 1 2
1 3 4 7
4 2 1 2
1
5
6
7
9
10
11
12
15
16
17
22
23
28
30
35
43
47
49
57

```
### 样例输出 #1
```
0
0
1
1
1
2
2
3
3
4
4
6
6
9
9
12
12
12
18
18

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem K.

**Author**: Alex_Wei.
## 题目翻译

### 题目描述：
给定 $n$ 条垂直的线和 $m$ 条水平线，每条线有重量。定义一个矩形是好的，当且仅当矩形的四个边都落在这些线上，好矩形的代价等于其内部四条边的长度与对应线重量的乘积之和。请找出最大面积的好矩形，使得其代价不超过 $c$。注意，矩形的长度和宽度可以为零。

### 输入格式：
第一行三个正整数 $n,m,T(2 \leq n, m \leq 5 \times 10^3, 1 \leq T \leq 100)$，依次表示垂直线、水平线的数量以及查询的次数。

第二行 $n$ 个正整数 $x_1,x_2,\cdots,x_n(1 \leq x_1 < x_2 < \cdots < x_n \leq 10^5)$，其中 $x_i$ 表示第 $i$ 条垂直线的位置。

第三行 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，其中 $a_i$ 表示第 $i$ 条垂直线的重量。

第四行 $m$ 个正整数 $y_1,y_2,\cdots,y_m(1 \leq y_1 < y_2 < \cdots < y_m \leq 10^5)$，其中 $y_i$ 表示第 $i$ 条水平线的位置。

第五行 $m$ 个正整数 $b_1,b_2,\cdots,b_m(1 \leq b_i \leq 10^7)$，其中 $b_i$ 表示第 $i$ 条水平线的重量。

接下来 $T$ 行，每行一个正整数 $c(1 \leq c \leq 4\times 10^{12})$，表示一次查询。

### 输出格式：
对于每次查询，输出一个整数表示最小代价不超过 $c$ 的最大好矩形的面积。

translated by @[cff_0102](/user/542457)


---

---
title: "[ICPC 2021 WF] Dungeon Crawler"
layout: "post"
diff: 省选/NOI-
pid: P9440
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Dungeon Crawler
## 题目描述

Alice and Bob are in charge of testing a new escape room! In this escape room, customers are trapped in a dungeon and have to explore the entire area. The dungeon consists of $n$ rooms connected by exactly $n-1$ corridors. It is possible to travel between any pair of rooms using these corridors.

Two of the dungeon rooms are special. One of these rooms contains a protective idol known as the "helix key´´. A different room contains a nasty "dome trap´´, which prevents the player from moving once activated. Entering the room with the trap before acquiring the key will result in the player being trapped in the dungeon forever. The player cannot start in the same room as the key or the trap.

There are $q$ different scenarios that Alice and Bob wish to examine. In the $i^{th}$ scenario, the player starts in room $s_i$, the key is in room $k_i$, and the trap is in room $t_i$. For each scenario, compute the minimum amount of time needed to explore the entire dungeon without getting trapped.
## 输入格式

The first line of input contains two integers $n$ and $q$, where $n$ ($3 \leq n \leq 2000$) is the number of rooms and $q$ ($1 \leq q \leq 200000$) is the number of scenarios to consider. Rooms are numbered from $1$ to $n$. The next $n-1$ lines each contain three integers $u$, $v$, and $w$ indicating that there is a corridor between rooms $u$ and $v$ ($1 \leq u, v \leq n, u \neq v$) that takes time $w$ ($1 \leq w \leq 10^9$) to traverse.

Then follow $q$ lines: the $i^{th}$ of these lines contains three distinct integers $s_i$, $k_i$, and $t_i$ ($1 \leq s_i, k_i, t_i \leq n$) indicating the room where the player starts, the room with the key, and the room with the trap, respectively.
## 输出格式

For each scenario, output the minimum amount of time needed to visit every room at least once. If it is impossible to visit every room at least once, output $\texttt{impossible}$.
## 样例

### 样例输入 #1
```
5 4
1 2 3
1 3 1
3 4 4
3 5 2
1 2 4
1 4 2
5 2 1
4 3 1

```
### 样例输出 #1
```
15
17
impossible
12

```
### 样例输入 #2
```
7 4
1 2 1
1 3 1
1 4 1
1 5 1
1 6 1
1 7 1
1 2 3
5 4 1
3 1 4
2 4 5

```
### 样例输出 #2
```
11
impossible
10
10

```
## 题目翻译

### 题目描述
有一棵 $n$ 个结点的树，边带权。你可以从一个结点通过边移动到一个相邻的结点，花费等同于边权的时间。

其中，有两个特殊结点，一个结点里有钥匙，一个结点里有陷阱。你只有先获得钥匙，才能进入陷阱所在的结点。

现有 $q$ 组询问，在第 $i$ 组询问中，你要从第 $s_i$ 号结点出发，钥匙在第 $k_i$ 号结点，陷阱在第 $t_i$ 号结点。你需要对于每组询问回答遍历整棵树所需的最短时间。题目保证你不会在钥匙所在的结点或者陷阱所在的结点出发。如果不可能遍历整棵树，输出 `impossible`。


### 输入格式
第一行两个整数 $n,q$，含义如题目所述。

接下来 $n-1$ 行，每行三个整数 $u,v,w$，表示有一条连接结点 $u,v$，权值为 $w$ 的边。

接下来 $q$ 行，每行三个整数 $s_i,k_i,t_i$，含义如题目所述。

$3\le n\le 2000$，$1\le q \le 2\times10^5$，$1\le u,v\le n,u\ne v$，$1\le w\le 10^9$，$1\le s_i,k_i,t_i\le n$。

### 输出格式
对于每组询问，输出一行，包含一个整数表示答案，或者输出 `impossible` 表示无解。


---

---
title: "[ICPC 2021 WF] Hand of the Free Marked"
layout: "post"
diff: 省选/NOI-
pid: P9443
tag: ['2021', 'Special Judge', 'ICPC']
---
# [ICPC 2021 WF] Hand of the Free Marked
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/kdojyok4.png)

Example placement of cards for $k = 5$

There is a fairly well-known mentalism trick known as the Fitch Cheney trick. From a deck of $n$ playing cards, $k$ are selected uniformly at random and given to an assistant while the magician is out of the room. The assistant places $k-1$ of the selected cards on a table, face up, and the single remaining card face down. The cards are placed in a single row with the face-down card at the end (see the picture for an example). The magician enters the room, looks at the cards on the table, and announces what the $k^{th}$ card is, although its face is hidden. The trick is typically done with $n=52$ and $k=5$.

The assistant uses two ways of passing information to the magician. First, they can pick which one of the $k$ cards to keep hidden. Second, they can rearrange the other $k-1$ cards in a specific way. For the case $n=52$ and $k=5$ both techniques are needed, since there are only $24$ ways of rearranging four cards, which is not enough to reliably signal the fifth card. It is an interesting exercise to come up with a simple, easy-to-remember strategy for executing this trick, but right now you have another concern.

You were planning to perform this trick today, but just now you have learned that the deck has more cards than you expected. The trick may be impossible! In desperation, you have decided to cheat a little. You have $m$ distinguishable ways of marking the backs of the playing cards. You have marked the backs of all $n$ cards, allowing you to narrow down the possibilities for the $k^{th}$ card. For example, if there are $6$ cards marked with a particular method, and you see that the back of the $k^{th}$ card is marked with that method, you know it must be one of those $6$ cards.

Determine the probability that you will successfully guess the $k^{th}$ card, assuming you and the assistant execute an optimal (but likely very complicated!) strategy.
## 输入格式

The input contains one line with several integers. The first integer gives $k$ ($2 \leq k \leq 10$), the number of cards that will be selected. The second integer gives $m$ ($1 \leq m \leq 10$), the number of ways of marking the cards. The line is completed by $m$ positive integers, giving the number of cards marked with each distinct method. The sum of these $m$ integers is $n$ ($k \leq n \leq 10^9$), which is the size of the deck.
## 输出格式

Output the highest possible probability of guessing the $k^{th}$ card correctly, accurate up to an absolute error of $10^{-9}$.
## 样例

### 样例输入 #1
```
4 1 28

```
### 样例输出 #1
```
0.960000000000

```
### 样例输入 #2
```
3 3 5 12 3

```
### 样例输出 #2
```
0.854385964912

```
## 题目翻译

#### 简要题意
两个人 $A, B$ 玩一个游戏。规则如下 :

$A$ 有 $n$ 张互不相同的牌. 它们的**背面**有 $m$ 种不同的样式, 第 $i$ 种牌有 $a_i$ 张. 二人都对这套牌非常了解. 保证 $\sum\limits^{m}_{i=1}{a_i} = n$.

$B$ 在 $A$ 不在场的情况下从中随机抽出 $k$ 张, 然后选择一张牌倒置在桌面上. 然后 $B$ 可以以任意顺序重新排列其他牌并在桌面上依次排开, 并将倒置的牌放在序列的末尾. $A$ 和 $B$ 可以在游戏之前约定通过其他牌的排列顺序传递的信息.

随后 $A$ 需要根据桌面上牌的排列和倒置牌的背面说出倒置的牌具体是哪一张. 双方的目标都是使 $A$ 说出正确的牌。

现在给定 $m, a_i$ 和 $k$, 求二人均采取最佳策略的情况下, $A$ 的成功率是多少.

#### 输入格式
输入仅一行, 首先是两个整数 $k, m$, 然后是 $m$ 个整数 $a_i$.

#### 输出格式
一行, 一个实数, 表示答案. 答案与标准答案的差不超过 $10^{-9}$ 即判为正确.


---

---
title: "[ICPC 2021 WF] Islands from the Sky"
layout: "post"
diff: 省选/NOI-
pid: P9444
tag: ['2021', 'Special Judge', 'ICPC']
---
# [ICPC 2021 WF] Islands from the Sky
## 题目描述

You might never have heard of the island group of Iceepeecee, but that suits their inhabitants just fine. Located in a remote part of the South Pacific, they are truly off the beaten track, without any regular air or sea traffic, and they have remained a tropical paradise with unspoiled local fauna and flora.

Being off the map is great when you don't want to be overrun by hordes of tourists, but not so ideal when you actually do need a map for some reason. One such reason came up recently: Iceepeecee's central government needs an exact map of the islands to apportion government funds. Even tropical paradises need money, so Iceepeecee needs a map!

The easiest way to create a map would be an aerial survey. After dismissing chartering planes as too expensive, building an air balloon as too dangerous, and fitting carrier pigeons with cameras as too cruel to animals, they had a brilliant idea. Even with its remote location, there are still plenty of commercial airplanes crossing the skies above Iceepeecee. What if one mounted cameras on flights that are already scheduled to fly anyway? That would be a cheap solution to the problem!

Iceepeecee's plan is to install line-scan cameras on the planes. These cameras point straight downwards and collect images one line segment at a time, orthogonal to the flight path. The photographed line segment will be determined by the altitude that the plane is flying at, and the camera's aperture angle $\theta$ (see Figure F.1). Greater angles $\theta$ mean that the camera can see more, but also that the camera is more expensive.

Moreover, Iceepeecee wants to make sure that each island is observed in its entirety by at least one flight. That means it is not sufficient that an island is only partially photographed by multiple flights, even if the combination of the photographs covers the whole island.

![](https://cdn.luogu.com.cn/upload/image_hosting/99wwtofi.png)

Figure F.1: A view of the plane, shown head-on. Its camera points downward and can see the part of the ground underneath the plane that is shown in green. How much is visible depends on the aperture angle $\theta$.
  
Flight paths follow straight line segments in three-dimensional space, that is, ($x_1, y_1, z_1$) $-$ ($x_2, y_2, z_2$) (see Figure F.2), where the $z$-coordinates give the altitude of the plane. Photographs are taken only along these line segments.

Given the location of their islands and flights, Iceepeecee wants to find the smallest aperture angle $\theta$ that allows for a successful survey. Can you help?

![](https://cdn.luogu.com.cn/upload/image_hosting/3pdn3q1b.png)

Figure F.2: Three islands (shown in black) and two flight paths (red and green). Altitudes are not shown. The shaded areas represent the ground visible on the two flight paths for an optimally chosen $\theta$. This corresponds to the first sample input.Three islands (shown in black) and two flight paths (red and green). Altitudes are not shown. The shaded areas represent the ground visible on the two flight paths for an optimally chosen $\theta$. This corresponds to the first sample input.
## 输入格式

The input describes a set of islands and flight paths. It starts with a line containing two integers $n$ and $m$, the number $n$ of islands, and the number $m$ of flight paths, respectively ($1 \leq n,m \leq 100$). This is followed by descriptions of the $n$ islands. Each island description starts with a line containing a single integer $n_i$, the number of vertices of the polygon describing the $i^{th}$ island ($3 \leq n_i \leq 100$). It is followed by $n_i$ lines, each containing two integers $x_{ij}$, $y_{ij}$ ($|x_{ij}|, |y_{ij}| \leq 10^6$), specifying the vertices for the $i^{th}$ island in counterclockwise order. Each island's polygon is simple, that is, its vertices are distinct and no two edges of the polygon intersect or touch, other than consecutive edges which touch at their common vertex. Different islands do not intersect or touch.

The input concludes with another $m$ lines, each describing a flight path. Each such line contains six integers $x_1$, $y_1$, $z_1$, $x_2$, $y_2$, $z_2$ ($|x_i|, |y_i|, |z_i| \leq 10^6$, $z_i &gt; 0$ and ($x_1, y_1$) $\neq$ ($x_2, y_2$)). They specify that a flight takes place from ($x_1, y_1, z_1$) to ($x_2, y_2, z_2$).
## 输出格式

Output the smallest angle $\theta$ (in degrees) that allows for a complete survey of the islands with the given flights. The answer should be exact to an absolute or relative error of $10^{-6}$. If there is no such angle, then output $\texttt{impossible}$. The input is chosen such that if the coordinates of the island vertices are changed by at most $\pm 10^{-8}$, then the answer will not change more than the allowed rounding error.
## 样例

### 样例输入 #1
```
3 2
3
20 30
50 50
10 50
4
40 20
60 10
75 20
60 30
4
45 60
55 55
60 60
55 65
0 30 20 78 70 5
55 0 20 70 60 10

```
### 样例输出 #1
```
48.031693036

```
### 样例输入 #2
```
1 1
4
0 0
10 0
10 10
0 10
5 5 10 15 5 10

```
### 样例输出 #2
```
impossible

```
## 题目翻译

有一个空间直角坐标系 $O-xyz$，在坐标平面 $xOy$ 上有 $n$ 个岛，每个岛是一个简单多边形。保证岛屿之间不重叠。

坐标系中有 $m$ 条飞机航线，航线是一条线段，两个端点的坐标分别是 $(x_1,y_1,z_1)$ 和 $(x_2,y_2,z_2)$。飞机可以沿任意一条飞机航线飞行。

现在要在飞机上装扫描相机。扫描相机的能扫描的范围取决于角度 $\theta$。

飞机位于一点 $(x,y,z)$ 时，我们可以以 $(x,y,z)$ 为顶点做一个顶角为 $2\theta$ 的等腰三角形，这个等腰三角形所在的面和坐标平面 $xOy$ 垂直，同时也和这架飞机所在的飞机航线到坐标平面 $xOy$的投影垂直。
将飞机位于 $(x,y,z)$ 时，能扫描到的线段定义为这个等腰三角形的底边。

对于一条航线，其覆盖的范围定义为当飞机在这条航线上运动时，所有能扫描到的线段组成的四边形。

求最小的 $\theta$（角度制），使得每个岛都至少完全位于一条航线的覆盖范围内。如果无论 $\theta$ 取何值都不能满足条件，输出 `impossible`。

$1\le n,m\le 100$，多边形的边数不超过 $100$，所有给出的坐标绝对值不超过 $10^6$。


---

---
title: "[ICPC 2021 WF] Mosaic Browsing"
layout: "post"
diff: 省选/NOI-
pid: P9445
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Mosaic Browsing
## 题目描述

The International Center for the Preservation of Ceramics (ICPC) is searching for motifs in some ancient mosaics. According to the ICPC's definition, a $\textit{mosaic}$ is a rectangular grid where each grid square contains a colored tile. A $\textit{motif}$ is similar to a mosaic but some of the grid squares can be empty. Figure G.1 shows an example motif and mosaic.

The rows of an $r_q \times c_q$ mosaic are numbered $1$ to $r_q$ from top to bottom, and the columns are numbered $1$ to $c_q$ from left to right.

A contiguous rectangular subgrid of the mosaic matches the motif if every tile of the motif matches the color of the corresponding tile of the subgrid. Formally, an $r_p \times c_p$ motif appears in an $r_q \times c_q$ mosaic at position ($r$, $c$) if for all $1 \leq i \leq r_p$, $1 \leq j \leq c_p$, the tile ($r+i-1$, $c+j-1$) exists in the mosaic and either the square ($i$, $j$) in the motif is empty or the tile at ($i$, $j$) in the motif has the same color as the tile at ($r+i-1$, $c+j-1$) in the mosaic.

Given the full motif and mosaic, find all occurrences of the motif in the mosaic.

![](https://cdn.luogu.com.cn/upload/image_hosting/0n7urywk.png)

Figure G.1: Motif (left) and mosaic (right) of Sample Input 1.
## 输入格式

The first line of input contains two integers $r_p$ and $c_p$, where $r_p$ and $c_p$ ($1 \leq r_p, c_p \leq 1000$) are the number of rows and columns in the motif. Then $r_p$ lines follow, each with $c_p$ integers in the range $[0, 100]$, denoting the color of the motif at that position. A value of $0$ denotes an empty square.

The next line of input contains two integers $r_q$ and $c_q$ where $r_q$ and $c_q$ ($1 \leq r_q, c_q \leq 1000$) are the number of rows and columns in the mosaic. Then $r_q$ lines follow, each with $c_q$ integers in the range $[1, 100]$, denoting the color of the mosaic at that position.
## 输出格式

On the first line, output $k$, the total number of matches. Then output $k$ lines, each of the form $r c$ where $r$ is the row and $c$ is the column of the top left tile of the match. Sort matches by increasing $r$, breaking ties by increasing $c$.
## 样例

### 样例输入 #1
```
2 2
1 0
0 1
3 4
1 2 1 2
2 1 1 1
2 2 1 3

```
### 样例输出 #1
```
3
1 1
1 3
2 2

```
## 题目翻译

#### 简要题意
给出两个矩阵, 其中第二个矩阵所有元素非 $0$.

定义第一个矩阵在第二个矩阵中的坐标 $(l, r)$ 处「出现」, 当且仅当存在一种方式任意修改第一个矩阵所有为 $0$ 的元素后, 第一个矩阵的左上角在第二个矩阵的对应位置坐标为 $(l, r)$ 时可以与第二个矩阵的一部分完全重合.

求第一个矩阵在第二个矩阵中所有「出现」的位置和总「出现」次数。

#### 输入格式
第一行, 两个整数 $r_p, c_p$, 表示第一个矩阵的行数和列数.

接下来 $r_p$ 行, 每行 $c_p$ 个整数, 描述第一个矩阵.

接下来一行, 两个整数 $r_q, c_q$, 表示第二个矩阵的行数和列数.

接下来 $r_q$ 行，每行 $c_q$ 个整数, 描述第二个矩阵.

#### 输出格式
第一行, 一个整数 $k$, 表示「出现」的总次数.

接下来 $k$ 行, 每行两个整数 $x, y$, 表示每一次「出现」的坐标. 如果有多个, 请以 $x$ 为第一关键字, $y$ 为第二关键字升序排序后输出。


---

---
title: "[ICPC 2021 WF] Spider Walk"
layout: "post"
diff: 省选/NOI-
pid: P9447
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Spider Walk
## 题目描述

Charlotte the spider sits at the center of her spiderweb, which consists of a series of silken straight strands that go from the center to the outer boundary of the web. Charlotte's web also has bridges, each of which connects two adjacent strands. The two endpoints of a bridge always have the same distance to the center of the spiderweb.

When Charlotte has finished a late-night feasting in the center and wants to retreat to some corner, she walks to the edge on autopilot. To do this, she picks a starting strand, and walks along it until she meets the first bridge on that strand. She will cross the bridge and go to the other strand, and then keeps walking outwards until she meets another bridge. Then she will cross that bridge, and repeat this process, until there are no more bridges on the current strand, and then she will walk to the end of the current strand. Note that Charlotte must cross all the bridges that she meets. Figure I.1 illustrates one path Charlotte could take.

Charlotte's favorite corner to sleep in during the daytime is at the end of strand $s$. For each possible starting strand, she wants to know the minimum number of bridges to add to the original web in order to end at $s$. Charlotte can add a bridge at any point along the strand, as long as the added bridge does not touch any other bridge. The two endpoints of any added bridge must have the same distance to the center of the spiderweb, and the bridge must connect two adjacent strands.

![](https://cdn.luogu.com.cn/upload/image_hosting/7nb4cy7c.png)

Figure I.1: The path starting from strand 4 on the spiderweb in Sample Input 1.
## 输入格式

The first line of input has three integers $n$, $m$, and $s$, where $n$ ($3 \leq n \leq 200000$) is the number of strands, m ($0 \leq m \leq 500000$) is the number of bridges, and $s$ ($1 \leq s \leq n$) is Charlotte's favorite strand. Strands are labeled from $1$ to $n$ in counterclockwise order. Each of the remaining $m$ lines contains two integers $d$ and $t$ describing a bridge, where $d$ ($1 \leq d \leq 10^9$) is the bridge's distance from the center of the spiderweb and $t$ ($1 \leq t \leq n$) is the first strand of the bridge in counterclockwise order. Specifically, if $1 \leq t &lt; n$, then the bridge connects strands $t$ and $t+1$. If $t = n$, then the bridge connects strands $1$ and $n$. All bridge distances $d$ are distinct.
## 输出格式

Output $n$ lines, where the $i^{th}$ line is the minimum number of bridges Charlotte needs to add in order to end at strand $s$ after walking on autopilot from strand $i$.
## 样例

### 样例输入 #1
```
7 5 6
2 1
4 3
6 3
8 7
10 5

```
### 样例输出 #1
```
2
1
1
1
0
1
2

```
### 样例输入 #2
```
4 4 2
1 1
2 2
3 3
4 4

```
### 样例输出 #2
```
1
1
0
1

```
## 题目翻译

有一个蜘蛛网，蜘蛛网包含一个中心点，从中心点放射出的 $n$ 条射线，按逆时针方向从 $1$ 到 $n$ 编号，以及 $m$ 条线段，称为“桥”，每条“桥”连接相邻的两条射线。每一条“桥”都和其连接的两条射线构成以中心点为顶点的等腰三角形。

现有一只蜘蛛从某一条射线的无穷远方向出发向中心点移动。如果在路上遇到了“桥” 的一个端点，蜘蛛会沿桥前往另一个端点到达另一条射线，然后继续往中心点移动。

现在蜘蛛会从 $1-n$ 号的每一条射线出发，并且希望最终经由 $s$ 号射线到达中心点。为了这一目的，可以在任两条射线之间的任意位置添加若干个“桥”。你需要对于 $1-n$ 的每一个出发位置计算最少添加“桥”的数量。注意各个询问之间是独立的，在一个询问中添加的“桥”不会对后续询问造成影响。

$3\le n\le200000$，$0\le n\le 500000$，$1\le s\le n$。


---

---
title: "[CERC2019] Be Geeks!"
layout: "post"
diff: 省选/NOI-
pid: P9607
tag: ['2019', '线段树', '倍增', 'ST 表', 'ICPC', '笛卡尔树', '单调栈']
---
# [CERC2019] Be Geeks!
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Be Geeks!](https://contest.felk.cvut.cz/19cerc/solved/begeeks.pdf)」**
## 题目描述

音乐乐队 Be Geeks! 的名字并非偶然，因为所有成员都是真正的数学怪才。除此之外，他们喜欢研究数列的各种性质。下面是他们感兴趣的一个例子：
- 设 $A$ 是一个非空正整数序列，$A=(a_1, a_2, \dots, a_N)$。
- $G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N$。
- $F(A)=\sum P(i, j)[1\le i\le j\le N]$。

给出一个序列 $A$，你需要求出 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 2\times 10^5)$，代表序列 $A$ 的长度。

第二行包含 $N$ 个整数 $a_1, a_2, \dots, a_N\ (1\le a_i\le 10^9)$，代表序列 $A$。
## 输出格式

输出一个整数，代表 $F(A)\bmod 1\,000\,000\,007$ 的值。
## 样例

### 样例输入 #1
```
4
1 2 3 4

```
### 样例输出 #1
```
50

```
### 样例输入 #2
```
5
2 4 6 12 3

```
### 样例输出 #2
```
457

```


---

---
title: "[CERC2019] K==S"
layout: "post"
diff: 省选/NOI-
pid: P9613
tag: ['动态规划 DP', '2019', '矩阵乘法', 'AC 自动机', 'ICPC']
---
# [CERC2019] K==S
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[K==S](https://contest.felk.cvut.cz/19cerc/solved/kequalss.pdf)」**
## 题目描述

渐进式硬八度摇滚曲调（所谓的“phorts”）是使用特定的音符创作的。这种摇滚风格只建立在 $13$ 个不同的音符音高上，其他音高（在其他八度中）被认为是过时的音乐基石。每个音符可以是长的，也可以是短的。因此，摇滚中正好有 $26$ 个不同的音符。

你将在你朋友的生日之际创作一首 phort 曲调，并与你的乐队在主要的城市广场上表演。在创作词缀时，你需要避免使用某些音乐短语，这些短语由于大型唱片公司赞助的长期研究而受到版权保护。已经证实，这些短语非常朗朗上口，易于记忆，可以用来将听众下意识地与某个特定的音乐公司联系起来，该公司会在他们的制作中使用这些短语。

曲调是一连串的音符。一个音乐短语也是一个音符序列，如果它的音符形成曲调的连续子序列，则它被认为包含在曲调中，这意味着相同的音符以相同的顺序出现在曲调中。

幸运的是，到目前为止，只有少数禁用短语获得了专利。因此，你可以相对自由地创作自己的曲调。特别是，您对某些长度的可接受的曲调的数量感兴趣。可接受的曲调是指任何不包含禁用短语的曲调。曲调的长度等于它所包含的音符数。
## 输入格式

第一行包含两个整数 $N, Q\ (1\le N\le 10^9, 1\le Q\le 100)$。$N$ 是曲调的长度，$Q$ 是禁用音乐短语的数量。

接下来 $Q$ 行，每行都描述了一个禁用短语。禁用短语的描述以一个表示其长度的正整数 $L$ 开头，后跟一个由 $L$ 个小写英文字母组成的字符串。每个字母代表一个摇滚音符，不同的字母代表不同的音符。

所有禁用短语的长度总和不超过 $100$。
## 输出格式

输出长度为 $N$ 的不同可接受曲调的数量对 $1\,000\,000\,007$ 取模的值。
## 样例

### 样例输入 #1
```
2 3
1 a
1 b
1 c

```
### 样例输出 #1
```
529

```
### 样例输入 #2
```
3 3
2 aa
1 a
1 a

```
### 样例输出 #2
```
15625

```
### 样例输入 #3
```
3 1
2 ab

```
### 样例输出 #3
```
17524

```


---

---
title: "[ICPC 2020 Nanjing R] Ah, It's Yesterday Once More"
layout: "post"
diff: 省选/NOI-
pid: P9622
tag: ['2020', 'Special Judge', 'O2优化', '构造', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Ah, It's Yesterday Once More
## 题目描述

In 2018, hosted by Nanjing University of Aeronautics and Astronautics (NUAA), the $\textit{International Collegiate Programming Contest}$ (ICPC) regional was held in Nanjing again after a few years' gap. There were over $400$ teams in the contest and team $\textit{Power of Two}$ from Tsinghua University won the champion.

Two years have passed and after the great success in 2018 and 2019, NUAA continues to hold the ICPC Nanjing Regional in 2020. Although we can't gather in Nanjing this time due to the pandemic, we should still be grateful for the hard work done by all staff and volunteers for this contest. Thank you all for your great contribution to this contest!

![](https://cdn.luogu.com.cn/upload/image_hosting/z82ge8hi.png)

In the 2018 contest, problem K, $\textit{Kangaroo Puzzle}$, requires the contestants to construct an operation sequence for the game. Let's first recall the content of that problem:

> The puzzle is a grid with $n$ rows and $m$ columns ($1 \le n, m \le 20$) and there are some (at least $2$) kangaroos standing in the puzzle. The player's goal is to control them to get together. There are some walls in some cells and the kangaroos cannot enter the cells with walls. The other cells are empty. The kangaroos can move from an empty cell to an adjacent empty cell in four directions: up, down, left, and right. It's guaranteed that kangaroos can reach from any empty cell to any other empty cells by going through adjacent empty cells. It is also guaranteed that there is no cycle in the puzzle -- that is, it's impossible that one kangaroo can move from an empty cell, pass by several distinct empty cells, and then back to the original cell.
>
> There is exactly one kangaroo in every empty cell in the beginning and the player can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press. For instance, if you press the button R, a kangaroo would move one cell to the right if it exists and is empty, and will stay still if it does not exist or is not empty.
>
> In this problem, the contestant needs to construct an operating sequence of at most $5 \times 10^4$ steps consisting of U, D, L, R only. If after operating these steps in order there are still two kangaroos standing in different cells, the contestant will be given a `Wrong Answer` verdict.

Our dear friend, Kotori, also took part in the contest and submitted a code of randomized algorithm. To her surprise, this simple solution is judged as a correct answer. We now present her solution as follows:

```cpp
#include <bits/stdc++.h>
using namespace std;
string s = "UDLR";
int main()
{
  srand(time(NULL));
  for (int i = 1; i <= 50000; i++) putchar(s[rand() % 4]);
  return 0;
}
```

For contestants who are not familiar with C and C++: the above code will output a random string of length $5 \times 10^4$ consisting only of characters `U`, `D`, `L` and `R`, where each character has equal probability to appear in each position in the string.

Kotori suspects that things might not be that simple for this problem, so right now, in this $\textit{2020 ICPC Nanjing Regional}$ contest, you need to construct an input data to hack her solution. Due to the randomness, your input data only needs to satisfy a successful hacking rate of at least $25\%$. 

Formally speaking, we've prepared $500$ randomly generated strings that each character has equal probability to appear in each position and will use them as the controlling sequence against your answer. For your answer to be accepted, there should be at least $125$ times that after using your answer as the map of cells and the whole controlling sequence is executed, there are still kangaroos in different cells.

Note that your input data should be completely legal. That is to say:

- The map in your answer should not be larger than $20 \times 20$;
- Your answer should contain at least two empty cells;
- All empty cells in your answer should be reachable starting from any empty cell;
- No cycles consisting of empty cells are allowed.
## 输入格式

There is no input for this problem. You're on your own!
## 输出格式

You should first output one line containing two integers $n$ and $m$ ($1 \le n, m \le 20$) separated by a space, indicating the number of rows and columns of the map in your answer.

You should then output $n$ lines where the $i$-th line contains a binary string $s_{i,1}s_{i,2}\cdots s_{i,m}$ ($s_{i,j} \in \{\text{`0'}, \text{`1'}\}$) of length $m$. If $s_{i,j} = \text{`1'}$ then the cell in the $i$-th row and the $j$-th column is empty; Otherwise that corresponding cell contains a wall and cannot be entered.

Note again that your answer only need to achieve a successful hacking rate of at least $25\%$. Not that hard isn't it?
## 样例

### 样例输入 #1
```
(No input)
```
### 样例输出 #1
```
3 4
1111
1010
1100

```
## 提示

### Note
The sample output we provide you is (obviously) incorrect. It only serves the purpose of showing you the output format. This is a $3 \times 4$ map with $4$ walls, so there will be $8$ kangaroos in the empty cells at the beginning.
## 题目翻译

### 题目描述
2018 年，由南京航空航天大学主办的 $\textit{国际大学生程序设计竞赛}$（ICPC）地区赛时隔数年再次在南京举行。来自清华大学的 $\textit{Power of Two}$ 队获得了冠军。

两年过去了，在 2018 年和 2019 年取得巨大成功后，南京航空航天大学继续在 2020 年举办 ICPC 南京赛区的比赛。虽然这次由于疫情的影响，我们不能齐聚南京，但我们仍然应该感谢所有工作人员和志愿者为这次比赛付出的辛勤劳动。感谢你们为本次比赛做出的巨大贡献！

![](https://cdn.luogu.com.cn/upload/image_hosting/z82ge8hi.png)

在 2018 年的竞赛中 K 题 $\textit{Kangaroo Puzzle}$ 中，要求参赛者为游戏构建一个操作序列。让我们先回顾一下该问题的内容：

> The puzzle is a grid with $n$ rows and $m$ columns ($1 \le n, m \le 20$) and there are some (at least $2$) kangaroos standing in the puzzle. The player's goal is to control them to get together. There are some walls in some cells and the kangaroos cannot enter the cells with walls. The other cells are empty. The kangaroos can move from an empty cell to an adjacent empty cell in four directions: up, down, left, and right. It's guaranteed that kangaroos can reach from any empty cell to any other empty cells by going through adjacent empty cells. It is also guaranteed that there is no cycle in the puzzle -- that is, it's impossible that one kangaroo can move from an empty cell, pass by several distinct empty cells, and then back to the original cell.
>
> There is exactly one kangaroo in every empty cell in the beginning and the player can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press. For instance, if you press the button R, a kangaroo would move one cell to the right if it exists and is empty, and will stay still if it does not exist or is not empty.
>
> In this problem, the contestant needs to construct an operating sequence of at most $5 \times 10^4$ steps consisting of U, D, L, R only. If after operating these steps in order there are still two kangaroos standing in different cells, the contestant will be given a ``Wrong Answer'' verdict.

我们的好友 Kotori 也参加了比赛，并提交了随机算法代码。令她惊讶的是，这个简单的解决方案竟然被评为正确答案。现将她的解决方案介绍如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s = "UDLR";
int main()
{
  srand(time(NULL));
  for (int i = 1; i <= 50000; i++) putchar(s[rand() % 4]);
  return 0;
}
```

对于不熟悉 C 和 C++ 的参赛者：上述代码将输出一个长度为 $5 \times 10^4$ 的随机字符串，该字符串仅由字符 `U`、`D`、`L` 和 `R` 组成，其中每个字符在字符串中每个位置出现的概率相等。

Kotori 怀疑这个问题可能没那么简单，所以现在，在这个 $\textit{2020 ICPC 南京赛区}$ 竞赛中，你需要构建一个输入数据来破解她的解决方案。由于随机性，你的输入数据只需满足至少 $25\%$ 的 hack 成功率即可。 

从形式上讲，我们准备了 $500$ 个随机生成的字符串，每个字符在每个位置出现的概率相等，并将它们用作对您的答案的控制序列。为了使您的答案被接受，在使用您的答案作为单元格映射并执行整个控制序列后，至少应该有 $125$ 个的不同单元格中有袋鼠。

请注意，您的输入数据必须完全合法。也就是说:

- 答案中的地图不应大于 $20 × 20$；
- 您的答案应至少包含两个空单元格；
- 答案中的所有空单元格都应可以从任意空单元格出发到达；
- 不允许包含空单元格的环（也就是说，空单元格组成一棵树）。


---

---
title: "[ICPC 2020 Nanjing R] Certain Scientific Railgun"
layout: "post"
diff: 省选/NOI-
pid: P9624
tag: ['2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Certain Scientific Railgun
## 题目描述

Misaka Mikoto is the third-ranked Level 5 esper in $\textit{Academy City}$ and has been nicknamed $\textit{Railgun}$ due to her signature move. One day, several evil robots invade Academy City and Misaka is planning to terminate all of them.

Consider Academy City as a 2-dimensional plane. There are $n$ robots in total and the position of the $i$-th robot is $(x_i, y_i)$. Misaka will start moving from $(0, 0)$ and her railgun ability will terminate all robots sharing the same $x$- or $y$-coordinate with her. More formally, if Misaka is now located at $(x_m, y_m)$, all robots whose $x_i = x_m$ or $y_i = y_m$ will be terminated.

As Misaka hates decimals and Euclidean geometry, she will only move from one integer point to another integer point and can only move horizontally (parallel to the $x$-axis) or vertically (parallel to the $y$-axis). As moving among the city is quite tiresome, Misaka asks you to calculate the minimum distance she has to move to terminate all robots.

Recall that an integer point is a point whose $x$-coordinate and $y$-coordinate are both integers.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \leq n \leq 10^5)$ indicating the number of robots.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$) indicating the position of the $i$-th robot.

It is guaranteed that the sum of $n$ of all test cases will not exceed $10^5$.
## 输出格式

For each test case output one line containing one integer indicating the minimum distance Misaka needs to move to terminate all robots.
## 样例

### 样例输入 #1
```
3
2
0 1
1 0
4
1 1
-3 -3
4 -4
-2 2
4
1 100
3 100
-100 1
3 -100

```
### 样例输出 #1
```
0
8
4

```
## 提示

### Note

For the second sample test case, Misaka should first go to $(0, 1)$, then to $(0, 2)$, then to $(0, -3)$, then to $(0, -4)$.

For the third sample test case, Misaka should first go to $(1, 0)$, then to $(1, 1)$, then to $(3, 1)$.
## 题目翻译

平面上有 $n$ 个点。御坂美琴初始位于 $(0,0)$。她可以随意平行于 $x$ 轴或 $y$ 轴移动，并可以在任意位置使用电磁炮消灭所有 $x$ 或 $y$ 坐标与她相同的点。要消灭所有点，求她最小的移动距离。

$T$ 组数据，$n,\sum n\le 10^5$，$|x_i|,|y_i|\le 10^9$。


---

---
title: "[ICPC 2020 Nanjing R] Degree of Spanning Tree"
layout: "post"
diff: 省选/NOI-
pid: P9625
tag: ['图论', '2020', 'Special Judge', 'O2优化', '构造', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Degree of Spanning Tree
## 题目描述

Given an undirected connected graph with $n$ vertices and $m$ edges, your task is to find a spanning tree of the graph such that for every vertex in the spanning tree its degree is not larger than $\frac{n}{2}$.

Recall that the degree of a vertex is the number of edges it is connected to.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($2 \le n \le 10^5$, $n-1 \le m \le 2 \times 10^5$) indicating the number of vertices and edges in the graph.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating that there is an edge connecting vertex $u_i$ and $v_i$. Please note that there might be self loops or multiple edges.

It's guaranteed that the given graph is connected. It's also guaranteed that the sum of $n$ of all test cases will not exceed $5 \times 10^5$, also the sum of $m$ of all test cases will not exceed $10^6$.

## 输出格式

For each test case, if such spanning tree exists first output ``Yes`` in one line, then for the following $(n-1)$ lines print two integers $p_i$ and $q_i$ on the $i$-th line separated by one space, indicating that there is an edge connecting vertex $p_i$ and $q_i$ in the spanning tree. If no valid spanning tree exists just output ``No`` in one line.

## 样例

### 样例输入 #1
```
2
6 9
1 2
1 3
1 4
2 3
2 4
3 4
4 5
4 6
4 6
3 4
1 3
2 3
3 3
1 2

```
### 样例输出 #1
```
Yes
1 2
1 3
1 4
4 5
4 6
No

```
## 提示

### Note

For the first sample test case, the maximum degree among all vertices in the spanning tree is 3 (both vertex 1 and vertex 4 has a degree of 3). As $3 \le \frac{6}{2}$ this is a valid answer.

For the second sample test case, it's obvious that any spanning tree will have a vertex with degree of 2, as $2 > \frac{3}{2}$ no valid answer exists.

## 题目翻译

### 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图，求一个生成树满足每个点的度数都不大于 $\frac{n}{2}$。

### 输入格式

多组数据，第一行，一个整数 $t$ 代表数据组数。

对于每组数据：

- 第一行两个整数 $n$, $m$，代表边数和点数；
- 接下来 $m$ 行，输入 $u_i,v_i$ 代表一条边（可能有重边和自环）。

### 输出格式

对于每组数据：

第一行输出 `Yes` 或 `No` 代表是否可行。

若可行，接下来 $n - 1$ 行输出每条生成树的边，顺序随意。

### 数据范围

$2 \leq n \leq 10^5$，$n - 1\leq m \leq 2\times10^5$，$\sum n\leq5\times10^5$，$\sum m\leq10^6$。

保证图连通。


---

---
title: "[ICPC 2020 Nanjing R] Go"
layout: "post"
diff: 省选/NOI-
pid: P9628
tag: ['模拟', '图论', '2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Go
## 题目描述

$\textit{Go}$ is an adversarial game with the objective of surrounding a larger total area of the board with one's stones than the opponent's. The core idea of the game is the concept of $\textit{liberty}$, which is an open point, or rather, an intersection of vertical and horizontal lines on the chessboard with no stones on it, bordering the group.

A stone, white or black, is called $\textit{alive}$ if it has at least one liberty directly orthogonally adjacent (up, down, left, or right), or must be in the same connected group with a stone of the same color which is alive. We say two stones of the same color are directly connected if they're orthogonally adjacent. We say two stones $s_1$ and $s_k$ of the same color are in the same connected group if there exists a sequence of stones $s_1, s_2,\cdots, s_k$ such that for all $1 \le i < k$, $s_{i-1}$ and $s_i$ are of the same color and are directly connected.

For example, in the left part of the below figure, neither of the two white stones is alive, as they're captured by the surrounding black stones; While in the right part, the rightmost white stone is also not alive, even if the leftmost black stone is also not alive.

![](https://cdn.luogu.com.cn/upload/image_hosting/zjm3icu0.png)

Given a chessboard with $n$ vertical and $n$ horizontal lines where some stones might be lying on, please calculate the number of white stones captured by the black ones (that is to say, calcaulate the number of white stones not alive). The results for the above examples are $2$ and $1$, respectively.

However, our dear friend Kotori thinks that this problem is too simple for our clever contestants to solve, so she would like to heat things up by instead asking you to flip the color of each stone (that is to say, change a black stone to a white one, or vice versa$^1$) independently and find out the corresponding answer after each flip.

By flipping independently we mean that before flipping the color of a stone, the other stones should change back to their original color. Also note that the data in this problem is not from the real world, which means that the size of the chessboard is not necesssarily $19 \times 19$, and the number of white and black stones can be any integer.

$^1$ Vice versa: The reverse is also true. Here it can be replaced with ``change a white stone to a black one``. This is a very common phrase in modern English especially in academic writing, so please bear it in mind.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $n$ ($2\le n \le 10^3$) indicating the length of the board side.

For the next $n$ lines, the $i$-th line contains a string $s_{i,1},s_{i,2},\cdots,s_{i,n}$ ($s_{i,j}$ $\in$ $\{\text{`x' (ascii: 120)}$, $\text{`o' (ascii: 111)}$, $\text{`.' (ascii: 46)}\}$), where $s_{i,j} = \text{`x'}$ indicates that the intersection on the $i$-th row and the $j$-th column contains a black stone. Similarly $s_{i, j} = \text{`o'}$ for a white stone and $s_{i,j} = \text{`.'}$ for an empty intersection.

It's guaranteed that the sum of $n$ over all test cases does not exceed $5 \times 10^3$.
## 输出格式

For each test case output an integer $E$ modulo $(10^9 + 7)$ which is the answer encoded as follows:
- Sort all the stones with their row number (from top to bottom) as the primary sort key and their column number (from left to right) as the secondary sort key;
- $E=\sum \limits_{i=1}^m (10^6 + 7)^{m-i}a_i$, where $m$ is the number of stones and $a_i$ is the number of white stones not alive after flipping the color of the $i$-th stone.

$\underline{\text{NOTE that the MODULUS and the BASE are} \textbf{ DIFFERENT}}$. (We're begging you to notice this sentence. If this is not a pdf file I would rather it flashes and twinkles like crazy.)

## 样例

### 样例输入 #1
```
3
2
.o
..
3
.x.
xoo
ox.
2
oo
oo
```
### 样例输出 #1
```
0
870527216
485539347
```
## 提示

For the second sample test case, after flipping the stones in the order of $(1,2)$, $(2,1)$, $(2,2)$, $(2,3)$, $(3,1)$, $(3,2)$, the number of dead white stones are $1$, $0$, $1$, $2$, $0$, $0$, repectively.

For the third sample test case all stones on the chessboard, black or white, are not alive.
## 题目翻译

### 题目描述

**围棋**是一种对抗性游戏，目的是用自己的石头比对手的石头包围更大的棋盘总面积。游戏的核心理念是**自由**，即一个开放点，或者更确切地说，是棋盘上垂直线和水平线的交叉点，上面没有石头，与群体接壤。

一个白色或黑色的石头，如果它至少有一个直接正交相邻的自由（上、下、左或右），或者必须与一块有生命的相同颜色的石头在同一个连接组中，那么它是有生命的，被称为**活着**。我们说，如果两块颜色相同的石头正交相邻，它们就直接相连。如果存在一系列石头 $s_1,s_2,…,s_k$ ，对于所有 $1\leq i<k$ ， $s_{i-1}$ 和 $s_i$ 颜色相同且正交相邻，则相同颜色的两块石头 $s_1$ 和 $s_k$ 属于同一连通组。

例如，在下图的左侧，两块白色的石头都没有活着，因为它们被周围的黑色石头捕获了；而在右边的部分，最右边的白色石头也没有生命，即使最左边的黑色石头也没有。

![Go](https://cdn.luogu.com.cn/upload/image_hosting/zjm3icu0.png)

给定一个有 $n$ 条垂直线和 $n$ 条水平线的棋盘，其中可能有一些石头躺在上面，请计算黑色石头捕获的白色石头的数量（也就是说，计算没有生命的白色石头数量）。上述例子的结果分别为 $2$ 和 $1$ 。

然而，我们亲爱的朋友 Kotori 认为这个问题让我们聪明的参赛者解决太简单了，所以她想让你独立翻转每块石头的颜色（也就是说，把黑色的石头变成白色的石头，反之亦然$^1$），并在每次翻转后找到相应的答案。

独立翻转的意思是，在翻转石头的颜色之前，其他石头应该变回原来的颜色。还要注意，这个问题中的数据不是来自真实世界，这意味着棋盘的大小不一定是 $19×19$ ，黑白石头的数量可以是任意整数。

$^1$反之亦然：在这里，它可以用 ```把白色的石头变成黑色的石头``` 来代替。这是现代英语中非常常见的短语，尤其是在学术写作中，所以请记住。

### 输入格式

有多个测试样例。输入的第一行包含一个整数 $T$ 表示测试样例的数量。对于每个测试样例：

第一行包含一个整数 $n$ ($2\leq n\leq 10^3$)，表示棋盘的边长。

对于接下来 $n$ 行，第 $i$ 行包含一个字符串 $s_{i,1},s_{i,2},…,s_{i,n}$ 。其中 $s_{i,j}=‘x’$ 表示第 $i$ 行第 $j$ 列有一个黑石头，$s_{i,j}=‘o’$ 表示第 $i$ 行第 $j$ 列有一个白石头，$s_{i,j}=‘.’$ 表示第 $i$ 行第 $j$ 列是空的。

保证所有测试样例的 $n$ 之和不超过 $5×10^3$ 。

### 输出格式

对于每个测试用例输出一个整数 $E\bmod10^9+7$ 作为如下编码的答案：

- 对所有石头进行排序，以其行号（从上到下）为第一关键字，以其列号（从左到右）为第二关键字；
- $E=\sum\limits_{i=1}^m(10^6+7)^{m-i}a_i$ ，其中 $m$ 是石头的数量， $a_i$ 是翻转第 $i$ 次颜色后没有生命的白色石头的数量。

$\underline{\textbf{注意}\text{：\textsf{模数}和\textsf{基数}是}\textbf{不同}{的}}$ 。（我们恳求你注意这句话。如果这不是 pdf 文件，我宁愿它像疯了一样闪烁。）

### 说明/提示

对于第二个测试样例，按照 $(1,2),(2,1),(2,2),(2,3),(3,1),(3,2)$ 的顺序翻转石头后，死亡的白色石头数量分别为 $1,0,1,2,0,0$ 。

对于第三个测试样例，棋盘上的所有石头，无论是黑色还是白色，都不是活着的。


---

---
title: "[ICPC 2020 Nanjing R] Interested in Skiing"
layout: "post"
diff: 省选/NOI-
pid: P9630
tag: ['计算几何', '2020', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Interested in Skiing
## 题目描述

Kotori is interested in skiing. The skiing field is an infinite strip going along $y$-axis on the 2-dimensional plane where all points $(x, y)$ in the field satisfies $-m \le x \le m$. When skiing, Kotori cannot move out of the field, which means that the absolute value of his $x$-coordinate should always be no more than $m$. There are also $n$ segments on the ground which are the obstacles and Kotori cannot move across the obstacles either.

Kotori will start skiing from $(0, -10^{10^{10^{10^{10}}}})$ (you can regard this $y$-coordinate as a negative infinity) and moves towards the positive direction of the $y$-axis. Her vertical (parallel to the $y$-axis) speed is always $v_y$ which cannot be changed, however she can control her horizontal (parallel to the $x$-axis) speed in the interval of $[-v_x, v_x]$. The time that Kotori changes her velocity can be neglected.

Your task is to help Kotori calculate the minimum value of $v_x^*$ that once $v_x>v_x^*$ she can safely ski through the skiing field without running into the obstacles.
## 输入格式

There is only one test case in each test file.

The first line of the input contains three positive integers $n$, $m$ and $v_y$ ($1 \le n \le 100$, $1 \le m \le 10^4$, $1 \le v_y \le 10$), indicating the number of obstacles, the half width of the skiing field and the vertical speed.

For the following $n$ lines, the $i$-th line contains four integers $x_1$, $y_1$, $x_2$ and $y_2$ ($-m \le x_1, x_2 \le m$, $-10^4 \le y_1, y_2 \le 10^4$, $x_1 \ne x_2$ or $y_1 \ne y_2$) indicating the $i$-th obstacle which is a segment connecting point $(x_1, y_1)$ and $(x_2, y_2)$, both inclusive (that is to say, these two points are also parts of the obstacle and cannot be touched). It's guaranteed that no two obstacles intersect with each other.
## 输出格式

Output one line containing one number indicating the minimum value of $v_x^*$. If it is impossible for Kotori to pass through the skiing field, output ``-1`` (without quotes) instead.

Your answer will be considered correct if and only if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
3 2 1
-2 0 1 0
-1 4 2 4
0 1 0 3
```
### 样例输出 #1
```
1.000000000000000
```
### 样例输入 #2
```
2 1 2
-1 0 1 0
1 1 0 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
2 3 7
-3 0 2 2
3 1 -2 17
```
### 样例输出 #3
```
1.866666666666666
```
### 样例输入 #4
```
1 100 1
-100 0 99 0

```
### 样例输出 #4
```
0.000000000000000
```
## 题目翻译

### 题目描述
Kotori 对滑雪很感兴趣。滑雪场是在二维平面上沿着 $y$ 轴无限延伸的直线，其中场中的所有点 $(x,y)$ 满足 $-m\le x\le m$。滑雪时，Kotori 不能离开场地，这意味着他的 $x$ 坐标的绝对值应该始终不超过 $m$。地面上也有 $n$ 个路段是障碍，Kotori 无法越过障碍。

Kotori 将从 $(0, -10^{10^{10^{10^{10}}}})$  开始滑雪（你可以将此 $y$ 坐标视为负无穷大），并朝着 $y$ 轴的正方向移动。她的垂直（平行于 $y$ 轴）速度始终是 $v_y$，此值不变，但是她可以在 $[-v_x, v_x]$ 的间隔内控制她的水平（平行于 $x$ 轴的）速度。Kotori 改变速度的时间可以忽略不计。

你的任务是帮助 Kotori 计算 $v_x^*$ 的最小值，即一旦 $v_x>v_x^*$，她就可以安全地穿过滑雪场而不会遇到障碍物。

### 输入格式

每个测试文件中只有一个测试用例。

输入的第一行包含三个正整数 $n, m$ 和 $v_y$（$1\le n\le 100$，$1\le m\le 10^4$，$1\le v_y\le 10$），分别表示障碍物的数量、滑雪场的半宽和垂直速度。

对于下面的 $n$ 行，第 $i$ 行包含四个整数 $x_1, y_1, x_2$ 和 $y_2$（$-m\le x_1, x_2\le m$，$-10^4\le y_1, y_2\le 10^4$，$x_1\ne x_2$ 或 $y_1\ne y_2$），这四个整数表示第 $i$ 个障碍物，该障碍物是连接点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 的线段，两者都包括在内（也就是说，这两个点也是障碍物的一部分，不能触摸）。保证没有两个障碍物相互交叉。

### 输出格式

输出一行，其中包含一个数字，表示 $v_x^*$ 的最小值。如果 Kotori 无法通过滑雪场，请输出 `-1`（不带引号）。

当且仅当其绝对或相对误差不超过 $10^{-6}$ 时，您的答案才会被认为是正确的。

------------

翻译来自 [fire_wolf](https://www.luogu.com.cn/user/690669)。


---

---
title: "[ICPC 2020 Nanjing R] Just Another Game of Stones"
layout: "post"
diff: 省选/NOI-
pid: P9631
tag: ['2020', '线段树', 'O2优化', 'ICPC', '吉司机线段树 segment tree beats', '南京']
---
# [ICPC 2020 Nanjing R] Just Another Game of Stones
## 题目描述

Kotori and Umi are playing games of stones, which is hosted by Honoka. The rule is the same as the classic one: There are some piles of stones and the players take turns to remove any positive number of stones from one pile. The one who can't make a legal move loses the game.

This time however, things will be a little different. As the host, Honoka will prepare the games from $n$ candidate piles of stones, where the $i$-th pile initially has $a_i$ stones. Honoka will perform $q$ operations of the following two types:

- Given three integers $l$, $r$ and $x$, for all $l \le i \le r$ change the number of stones in the $i$-th candidate pile to $\max(b_i, x)$, where $b_i$ is the current number of stones in the $i$-th candidate pile.
- Given three integers $l$, $r$ and $x$, start a game of stones consisting of $(r-l+2)$ piles where the $i$-th pile contains $b_{l-1+i}$ stones for all $1 \le i < (r-l+2)$, and the $(r-l+2)$-th pile contains $x$ stones. Note that this operation is only querying for answer and will not affect the state of the $n$ candidate piles of stones.

Kotori is always the first to move. As a big fan of Kotori, you would like to know, for each game of stones, the number of ways Kotori can play in the first step to ensure her victory if both players use the best strategy. We consider two ways different if Kotori is taking stones from different piles, or from the same pile but is taking different number of stones.
## 输入格式

There is only one test case in each test file.

The first line of the input contains two integers $n$ and $q$ ($1 \le n, q \le 2 \times 10^5$) indicating the number of candidate piles and the number of operations.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($0 \le a_i \le 2^{30}-1$) where $a_i$ indicates the initial number of stones in the $i$-th pile.

For the following $q$ lines, the $i$-th line contains four integers $op_i$, $l_i$, $r_i$ and $x_i$ ($op_i \in \{1, 2\}$, $1 \le l_i \le r_i \le n$, $0 \le x_i \le 2^{30}-1$) indicating the $i$-th operation, where $op_i$ is the type of operation and the others are the parameters of the operation. Operations are given in the order they're performed.
## 输出格式

For each operation of the second type output one line containing one integer indicating the answer.

## 样例

### 样例输入 #1
```
5 4
1 2 1 4 1
2 1 3 1
1 2 4 3
2 2 4 4
2 1 4 4
```
### 样例输出 #1
```
1
0
3
```
## 提示

For the first operation the players will play a game of stones consisting of $1$, $2$, $1$ and $1$ stone(s) in each pile respectively. The only winning play for Kotori is reduce the pile with $2$ stones to $1$ stone.

After the second operation, number of stones in the candidate piles changes to $1$, $3$, $3$, $4$ and $1$ respectively.

For the fourth operation the players will play a game of stones consisting of $1$, $3$, $3$, $4$ and $4$ stone(s) in each pile respectively. The winning plays for Kotori is to reduce the pile with $1$ stone to $0$ stone, or to reduce any pile with $3$ stones to $2$ stones.
## 题目翻译

给定 $n$ 个石堆，第 $i$ 个石堆的石子数为 $a_i$，有 $q$ 次操作：

`1 l r x` 表示将所有满足 $l \leq i \leq r$ 的 $a_i$ 赋值为 $\max(a_i,x)$。

`2 l r x` 表示用石堆 $[l,r]$ 和一个石子数为 $x$ 的石堆进行 Nim 游戏，求出第一次先手取完石子后游戏变为后手必败局面的可操作总方案数。

（如果你还不了解 Nim 游戏，[点这里](https://oi-wiki.org//math/game-theory/impartial-game/)）。

对于 $100\%$ 的数据保证 $1 \le q,n \le 2 \times 10^5$，$0 \le a_i,x_i \le 2^{30}-1$，$op \in \{1,2\}$，$1 \le l_i,r_i \le n$。


---

---
title: "[ICPC 2021 Macao R] Shortest Path Fast Algorithm"
layout: "post"
diff: 省选/NOI-
pid: P9659
tag: ['2021', '提交答案', 'Special Judge', 'O2优化', '构造', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Shortest Path Fast Algorithm
## 题目描述

Recently, BaoBao has learned the Shortest Path Fast Algorithm (SPFA, or more formally, Bellman-Ford-Moore Algorithm) to solve the shortest path problem efficiently. He realizes that the algorithm looks so similar to the Dijkstra's algorithm after replacing the FIFO queue with priority queue, and shows you the below pseudo code.

![](https://cdn.luogu.com.cn/upload/image_hosting/yunmac9g.png)

By picking the best vertex from $Q$ we mean picking the vertex with the smallest priority value (in case that multiple vertices have the smallest priority value, pick the vertex with the largest index among them).

You, the future computer scientist, find the BaoBao-modified SPFA algorithm works so slow in some carefully construted graph. However, BaoBao is sure that his algorithm works well, unless you show him a simple undirected graph that makes the variable $\tt{cnt}$ in the SPFA function no less than a certain $k$ $\textbf{at some time}$. For convenience, the source vertex of the SPFA function is specified to be vertex $1$.

Just teach him a lesson!
## 输入格式

There is only one test case in each test file.

The first and only line of the input contains a single integer $k$ where $k = 1$ for the sample test case and $k = 10^5$ for the only secret test case.
## 输出格式

Output several lines in the following format to describe the input data of a simple undirected graph that makes the variable $\tt{cnt}$ in the SPFA function no less than $k$ $\textbf{at some time}$.

The first line contains two integers $n$ ($1 \le n \le 100$) and $m$ ($0 \le m \le 10^3$), indicating the number of vertices and edges in the graph.

Then $m$ lines follow, the $i$-th of which contains three integers $u_i$, $v_i$ ($1 \le u_i, v_i \le n$) and $w_i$ ($1 \le w_i \le 10^6$), indicating that the $i$-th edge in the graph has a weight of $w_i$ and connects the $u_i$-th and the $v_i$-th vertices.

Note that a simple graph contains no self-loops and no multiple edges.
## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
4 6
1 2 1
2 3 2
3 4 3
4 1 4
1 3 5
2 4 6
```
## 提示

For your convenience, you can copy the $\tt{C++}$ code, which corresponds to the given pseudo code, from the contest website. Save the code as $\tt{spfa.cpp}$, use $\text{g++ spfa.cpp -O2 -o spfa}$ to compile it and you will get an executable file named $\tt{spfa}$. Run $\tt{spfa}$, feed your output to its standard input and it will print out the $\textbf{final}$ value of $\tt{cnt}$. Given the sample output it will print out $4$, which means the sample output is not sufficient to pass the secret test case.

Note that the given code does not check the validity of your output (for example it does not check if your output is really a simple graph). You might still fail the test if your output is invalid, even if the executable prints out a large value.
## 题目翻译

**【题目描述】**

最近，宝宝学习了最短路径快速算法（SPFA，或更正式地说，贝尔曼-福特-摩尔算法）以有效地解决最短路径问题。他意识到，如果用优先队列代替先进先出队列，该算法看起来与 Dijkstra 算法非常相似，并向你展示了下面的伪代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/yunmac9g.png)

选择 $Q$ 中最佳顶点意味着选择具有最小优先级值的顶点（如果有多个顶点具有最小优先级值，则选择其中索引最大的顶点）。

作为未来的计算机科学家，你发现宝宝修改后的 SPFA 算法在某些精心构造的图中运行速度非常慢。然而，宝宝确信他的算法很好，除非你向他展示一个简单的无向图，在该图中，SPFA 函数中的变量 $\tt{cnt}$ 在某个时刻不少于某个 $k$。为方便起见，SPFA 函数的源顶点被指定为顶点 $1$。

就给他个教训吧！

**【输入格式】**

每个测试文件中只有一个测试用例。

输入的第一行包含一个整数 $k$，其中 $k = 1$ 为示例测试用例，$k = 10^5$ 为唯一的秘密测试用例。

**【输出格式】**

输出几行以以下格式描述简单无向图的输入数据，使得 SPFA 函数中的变量 $\tt{cnt}$ 在某个时刻不少于 $k$。

第一行包含两个整数 $n$（$1 \le n \le 100$）和 $m$（$0 \le m \le 10^3$），表示图中的顶点数和边数。

然后，跟着 $m$ 行，第 $i$ 行包含三个整数 $u_i$、$v_i$（$1 \le u_i, v_i \le n$）和 $w_i$（$1 \le w_i \le 10^6$），表示图中的第 $i$ 条边的权重为 $w_i$，连接了第 $u_i$ 个和第 $v_i$ 个顶点。

注意，简单图不包含自环和重边。

**【提示说明】**

为方便起见，你可以从比赛网站上复制与给定伪代码对应的 $\tt{C++}$ 代码。将代码保存为 $\tt{spfa.cpp}$，使用 $\text{g++ spfa.cpp -O2 -o spfa}$ 进行编译，你将得到一个名为 $\tt{spfa}$ 的可执行文件。运行 $\tt{spfa}$，将你的输出提供给它的标准输入，它将打印出 $\tt{cnt}$ 的 $\textbf{最终}$ 值。给出示例输出后，它将打印出 $4$，这意味着示例输出不足以通过秘密测试用例。

注意，给定的代码不会检查你的输出的有效性（例如，它不会检查你的输出是否真的是一个简单图）。即使可执行文件打印出一个很大的值，如果你的输出无效，你仍然可能失败测试。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


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

---
title: "[ICPC 2021 Macao R] Permutation on Tree"
layout: "post"
diff: 省选/NOI-
pid: P9663
tag: ['动态规划 DP', '2021', 'O2优化', '树形 DP', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Permutation on Tree
## 题目描述

Given a tree with $n$ vertices where vertex $r$ is the root, we say a permutation $p_1, p_2, \cdots, p_n$ of $n$ is good if it satisfies the following constraint:

- Let $a_x$ be the index of $x$ in the permutation (That is, $p_{a_x} = x$). For all $1 \le u, v \le n$, if vertex $u$ is an ancestor of vertex $v$ in the tree, then $a_u < a_v$.

Define the score of a permutation to be $\sum\limits_{i=1}^{n-1} |p_i - p_{i+1}|$ where $|x|$ is the absolute value of $x$. Calculate the sum of scores of all different good permutations.
## 输入格式

There is only one test case in each test file.

The first line contains two integers $n$ and $r$ ($2 \le n \le 200$, $1 \le r \le n$) indicating the size of the tree and the root.

For the following $(n - 1)$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating an edge connecting vertex $u_i$ and $v_i$ in the tree.
## 输出格式

For each test case output one line containing one integer indicating the sum of scores of all different good permutations. As the answer may be large, output the answer modulo $(10^9 + 7)$.
## 样例

### 样例输入 #1
```
4 2
1 2
2 3
1 4
```
### 样例输出 #1
```
15
```
### 样例输入 #2
```
3 1
1 2
2 3
```
### 样例输出 #2
```
2
```
## 提示

For the first sample test case, there are three good permutations: $\{2, 1, 3, 4\}$, $\{2, 1, 4, 3\}$ and $\{2, 3, 1, 4\}$. Their scores are $4$, $5$ and $6$ respectively so the answer is $4 + 5 + 6 = 15$.

For the second sample test case, there is only one good permutation: $\{1, 2, 3\}$. It's score is $2$.
## 题目翻译

**【题目描述】**

给定一个有 $n$ 个顶点的树，其中顶点 $r$ 是根，如果一个排列 $p_1, p_2, \cdots, p_n$ 满足以下约束条件，我们称其为好排列：

- 设 $a_x$ 是排列中 $x$ 的索引（即 $p_{a_x} = x$）。对于所有 $1 \le u, v \le n$，如果顶点 $u$ 是树中顶点 $v$ 的祖先，则 $a_u < a_v$。

定义排列的分数为 $\sum\limits_{i=1}^{n-1} |p_i - p_{i+1}|$，其中 $|x|$ 表示 $x$ 的绝对值。计算所有不同好排列的分数之和。

**【输入格式】**

每个测试文件中包含一个测试用例。输入的第一行包含两个整数 $n$ 和 $r$ ($2 \le n \le 200$, $1 \le r \le n$)，表示树的大小和根。

接下来的 $(n - 1)$ 行，第 $i$ 行包含两个整数 $u_i$ 和 $v_i$ ($1 \le u_i, v_i \le n$)，表示树中连接顶点 $u_i$ 和 $v_i$ 的边。

**【输出格式】**

对于每个测试用例，输出一行，包含一个整数，表示所有不同好排列的分数之和。由于答案可能很大，输出答案对 $(10^9 + 7)$ 取模的结果。

**【样例解释】**

对于第一个样例测试用例，有三个好排列：$\{2, 1, 3, 4\}$、$\{2, 1, 4, 3\}$ 和 $\{2, 3, 1, 4\}$。它们的分数分别为 $4$、$5$ 和 $6$，因此答案为 $4 + 5 + 6 = 15$。

对于第二个样例测试用例，只有一个好排列：$\{1, 2, 3\}$。它的分数为 $2$。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[ICPC 2021 Macao R] LCS Spanning Tree"
layout: "post"
diff: 省选/NOI-
pid: P9664
tag: ['2021', '后缀自动机 SAM', 'O2优化', '生成树', '后缀数组 SA', '后缀树', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] LCS Spanning Tree
## 题目描述

Given a complete undirected graph of $n$ vertices and $n$ strings $s_1, s_2, \cdots, s_n$, the weight of edge connecting vertices $i$ and $j$ is equal to the length of the longest common substring (LCS) between $s_i$ and $s_j$. Compute the maximum total weight of any spanning tree on this graph.

A substring of a string can be obtained by removing some (possibly zero) characters from the beginning and/or the end of that string. For example, ``maca``, ``aca`` and ``cau`` are all substrings of ``macau``, while ``acu`` is not.
## 输入格式

There is only one test case in each test file.

The first line of the input contains one integer $n$ ($1 \leq n \leq 2 \times 10^6$) indicating the number of vertices and strings.

For the following $n$ lines, the $i$-th line contains one string $s_i$ ($1 \le |s_i| \le 2 \times 10^6$) consisting only of lowercase English letters.

It's guaranteed that the sum of lengths of all strings will not exceed $2 \times 10^6$.
## 输出格式

Output one line containing one integer indicating the answer.
## 样例

### 样例输入 #1
```
4
icpc
macau
regional
contest
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
ababa
babab
aba
```
### 样例输出 #2
```
7
```
## 题目翻译

**【题目描述】**

给定一个有 $n$ 个顶点的完全无向图和 $n$ 个字符串 $s_1, s_2, \cdots, s_n$，连接顶点 $i$ 和 $j$ 的边的权重等于字符串 $s_i$ 和 $s_j$ 的最长公共子串（LCS）的长度。计算此图上任意生成树的最大总权重。

一个字符串的子串可以通过从该字符串的开头和/或结尾删除一些（可能为零）字符来获得。例如，“maca”、“aca” 和“cau”都是“macau”的子串，而“acu”不是。

**【输入格式】**

每个测试文件中包含一个测试用例。

输入的第一行包含一个整数 $n$ ($1 \leq n \leq 2 \times 10^6$)，表示顶点和字符串的数量。

接下来的 $n$ 行，第 $i$ 行包含一个字符串 $s_i$ ($1 \le |s_i| \le 2 \times 10^6$)，由小写英文字母组成。

保证所有字符串的长度之和不超过 $2 \times 10^6$。

**【输出格式】**

输出一行，包含一个整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[ICPC 2022 Jinan R] Torch"
layout: "post"
diff: 省选/NOI-
pid: P9668
tag: ['2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Torch
## 题目描述

Prof. Pang and Prof. Shou go to explore a cave together. Prof. Pang walks ahead of Prof. Shou. 

Each of them has a torch for illumination. The torches need fuel to burn. Prof. Pang's torch can burn for $a_1$ seconds once it has been refilled, and it takes $b_1$ seconds to refuel the torch after it burns out. Prof. Shou's torch can burn for $a_2$ seconds once it has been refilled, and it takes $b_2$ seconds to refuel the torch after it burns out. The person who is refueling the torch cannot walk simultaneously. For safety reasons, they cannot refuel the torch until the fuel runs out. 

Because Prof. Pang is too fat and the cave is too narrow, Prof. Shou cannot surpass Prof. Pang during the exploration, which means that Prof. Shou is at least 1 unit behind Prof. Pang. 

Each of them can walk forward a distance of 1 unit per second when his torch is burning. Every second, Prof. Pang moves first, then Prof. Shou does. In order to get to their destination earlier, they will move as long as they can walk forward. 

Now Prof. Shou has $n$ questions, and for the $i$-th question, he wants to know that at time $q_i$, how many units of the distance he has moved forward from the starting point? Prof. Shou starts 1 unit behind Prof. Pang. The initial time is 0. Both Prof. Pang and Prof. Shou refueled the torch before the initial time.
## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the first line contains 5 integers $a_1, b_1, a_2, b_2, n~(1 \le a_1, b_1, a_2, b_2, n \le 10^6)$ denoting the time Prof. Pang's torch can burn, the time for Prof. Pang to refuel his torch, the time Prof. Shou's torch can burn, the time for Prof. Shou to refuel his torch, and the number of Prof. Shou's queries. Each of the next $n$ lines describes a query. Query $i$ is denoted by one integer $q_i~(1 \le q_i \le 10^{16})$.

It is guaranteed that over all test cases, each of the following numbers is no more than $10^6$:

- the sum of $a_1$, 
- the sum of $a_2$, 
- the sum of $b_1$, 
- the sum of $b_2$, 
- and the sum of $n$.
## 输出格式

For each query, print one line containing the answer -- the number of units that Prof. Shou has walked forward from the starting point.
## 样例

### 样例输入 #1
```
3
2 3 2 4 2
7
8
1 1 1 1 2
3
4
9 7 10 3 5
5
10
20
30
50
```
### 样例输出 #1
```
3
4
2
2
5
9
13
18
28
```
## 题目翻译

## 题目描述

胖子和瘦子在一个山洞里行走，胖子在瘦子前面。每个人都有一支火把。

胖子的火把填满燃料后可以燃烧 $a_1$ 秒，在熄灭后需要花费 $b_1$ 秒填充燃料。

瘦子的火把填满燃料后可以燃烧 $a_2$ 秒，在熄灭后需要花费 $b_2$ 秒填充燃料。

每个人只能在自己的火把燃烧时前进，速度为 $1\operatorname{m/s}$。

因为胖子太胖，所以瘦子只能跟在胖子后面而不能超过胖子。

每一秒胖子先移动，之后瘦子再移动。

初始时两个人的火把都已经填满了燃料，瘦子在胖子后面 $1 \operatorname{m}$。

给定 $n$ 个询问，每次给一个正整数 $q_i$，表示查询第 $q_i$ 秒后，瘦子的移动距离。

## 输入格式

**本题包含多组测试数据**

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

第一行五个正整数 $a_1, b_1, a_2, b_2, n$，含义见题目描述。

接下来 $n$ 行，每行一个正整数 $q_i$，表示询问。

## 输出格式

每组数据输出 $n$ 行，表示每个询问的答案，即第 $q_i$ 秒后瘦子的移动距离。

## 数据范围

下面 $\sum n$ 表示所有数据的 $n$ 之和，$\sum a_1, \sum b_1, \sum a_2, \sum b_2$ 同理。

$1 \le T \le 10^5$，$1 \le a_1, b_1, a_2, b_2 \le 10^6$，$\sum a_1, \sum b_1, \sum a_2, \sum b_2, \sum n \le 10^6$，$1 \le q_i \le 10^{16}$。


---

---
title: "[ICPC 2022 Jinan R] DFS Order 2"
layout: "post"
diff: 省选/NOI-
pid: P9669
tag: ['2022', 'O2优化', '背包 DP', '树形 DP', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] DFS Order 2
## 题目描述

Prof. Pang has a rooted tree that is rooted at vertex $1$ and has $n$ nodes. These $n$ nodes are numbered from $1$ to $n$.

Now he wants to start the depth-first search at the root. He wonders for each node $v$, how many ways it can appear in the $j$-th position of $\textbf{depth-first search order}$. The depth-first search order is the order of nodes visited during the depth-first search. A node appears in the $j$-th ($1\le j\le n$) position in this order means it is visited after $j-1$ other nodes. Because sons of a node can be iterated in arbitrary order, multiple possible depth-first orders exist. 

Prof. Pang wants to know for each node $v$, how many different $\textbf{depth-first search order}$s such that $v$ appears in the $j$-th position. For each $v, j~(1 \le v, j \le n)$, compute the answer. Because the answer can be very large, output it modulo $998244353$.

Following is a pseudo-code for the depth-first search on a rooted tree. After calling $\textbf{main}$(), $\texttt{dfs\_order}$ is the depth-first search order.

![](https://cdn.luogu.com.cn/upload/image_hosting/l3gjstn0.png)
## 输入格式

The first line contains one integer $n~(1\le n \le 500)$, the number of vertices in the tree.

Each of the next $n-1$ lines describes an edge of the tree. Edge $i$ is denoted by two integers $u_i$ and $v_i$, the labels of vertices it connects $(1\le u_i,v_i\le n, u_i\neq v_i)$.

It is guaranteed that the given edges form a tree.
## 输出格式

For each vertex $v$ from $1$ to $n$, output one line containing $n$ integers modulo $998244353$. The $j$-th integer in the $v$-th line should be the number of different depth-first search orders such that $v$ appears in the $j$-th position.
## 样例

### 样例输入 #1
```
5
1 2
1 3
3 4
3 5
```
### 样例输出 #1
```
4 0 0 0 0
0 2 0 0 2
0 2 2 0 0
0 0 1 2 1
0 0 1 2 1
```
## 题目翻译

### 题目描述

P有一棵树，根节点是$1$，总共有$n$个节点，从$1$到$n$编号。

他想从根节点开始进行深度优先搜索。他想知道对于每个节点$v$，在深度优先搜索中，它出现在第$j$个位置的方式有多少种。深度优先搜索的顺序是在搜索过程中访问节点的顺序。节点出现在第$j（1 \le j \le n $）个位置表示它在访问了$j - 1$个其他节点之后才被访问。因为节点的子节点可以以任意顺序访问，所以有多种可能的深度优先搜索顺序。

P想知道对于每个节点$v$，有多少种不同的深度优先搜索顺序，使得$v$出现在第$j$个位置。对于每个$v$和$j（i \le v,j \le n）$，计算答案。答案可能很大，所以输出时要取模$998244353$。以下是深度优先搜索的伪代码，用于处理树。在调用$main()$函数后， dfs_order将会包含深度优先搜索的顺序。



------------
#### 算法 $1$ 深度优先搜索的实现
```
1. 过程 DFS(节点 x)

2.	将x添加到dfs_order的末尾

3.	对于x的每个子节点y do               ·子节点可以以任意顺序遍历。

4.		DFS(y)

5.	结束循环

6. 结束过程

7. 过程 MAIN()

8.	将dfs_order设为全局变量

9.	dfs_order ← 空列表

10.	DFS(1)

11. 结束过程
```
------------

### 输入格式

第一行包含一个整数$n（1\le n\le 500）$，表示树中的节点数量。

接下来的n-1行描述了树的边。第i行包含两个整数$u_i$和$v_i$，表示连接的两个节点的标签$（1\le u_i,v_i\le n,u_i\not=v_i）$。

保证给定的边构成一棵树。

### 输出格式

对于每个从$1$到$n$的节点$v$，输出一行，包含$n$个整数，取模$998244353$。在第$v$行中，第$j$个整数表示不同的深度优先搜索顺序中，节点$v$出现在第$j$个位置的数量。

 	翻译由@ayf2192538031提供


---

---
title: "[ICPC 2022 Jinan R] Set of Intervals"
layout: "post"
diff: 省选/NOI-
pid: P9674
tag: ['2022', 'O2优化', 'ICPC', 'Ad-hoc', '分类讨论', '济南']
---
# [ICPC 2022 Jinan R] Set of Intervals
## 题目描述

Prof. Pang has a multi-set of intervals $S=\{[l_i,r_i]\}$($l_i<r_i$).

Prof. Pang will perform the following operation for $|S|-1$ times:

- Select two intervals $[a,b]$ and $[c,d]$ from $S$, and then choose two integers $x,y$ satisfying $x\in [a,b], y\in [c,d], x<y$. After that, delete $[a,b]$ and $[c,d]$ from $S$, and add $[x,y]$ to $S$.

It's easy to find that $S$ contains exactly one interval after the operations, and Prof. Pang will get the interval as a gift.

Now Prof. Pang wants you to calculate how many different intervals he can get.
## 输入格式

The first line contains one integer $T~$($1\le T \le 10^4$), the number of test cases.

For each test case, the first line contains one integer $n~$($1\le n\le 10^5$) --- the size of $S$. Each of the following $n$ lines contains two integers $l_i$ and $r_i~$($1\le l_i<r_i\le 10^9$), describing the $i$-th interval in $S$.

It is guaranteed that the sum of $n$ over all test cases is no more than $10^5$.
## 输出格式

For each test case, output one line containing the answer to Prof. Pang's question.
## 样例

### 样例输入 #1
```
4
1
1 1000000000
2
1 1000000000
1 1000000000
4
1 2
3 4
5 6
7 8
4
1 3
2 4
5 8
6 7
```
### 样例输出 #1
```
1
499999999500000000
26
28
```
## 题目翻译

蓝蓝有一个元素全为闭区间的可重集 $S=\{[l_i,r_i]\}$($l_i<r_i$)。

蓝蓝将会执行以下操作 $n-1$ 次：
- 从 $S$ 内选择两个闭区间 $[a,b]$ 和 $[c,d]$，再选择两个整数 $x,y$ 满足 $x\in [a,b], y\in [c,d], x<y$，然后从 $S$ 中删去 $[a,b]$ 和 $[c,d]$，并把 $[x,y]$ 添加进 $S$。

显然最终 $S$ 中有且仅有一个区间。现在蓝蓝想知道她可以获得多少不同的区间。


---

---
title: "[ICPC 2022 Jinan R]  Skills"
layout: "post"
diff: 省选/NOI-
pid: P9676
tag: ['动态规划 DP', '2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R]  Skills
## 题目描述


Prof. Pang has $3$ different skills to practice, including soda drinking, fox hunting, and stock investing. We call them Skill $1$, Skill $2$, and Skill $3$. In each of the following $n$ days, Prof. Pang can choose one of the three skills to practice. In the $i$-th day ($1\le i\le n$), if Prof. Pang chooses Skill $j$ ($1\le j\le 3$) to practice, his level of Skill $j$ will increase by $a_{i,j}$. Initially, Prof. Pang's levels of all skills are $0$.

Prof. Pang forgets skills if he does not practice. At the end of each day, if he has not practiced Skill $j$ for $k$ days, his level of Skill $j$ will decrease by $k$. For example, if he practices Skill $1$ on day $1$ and Skill $2$ on day $2$, at the end of day $2$, he has not practiced Skill $1$ for $1$ day and has not practiced Skill $3$ for $2$ days. Then his levels of Skill $1$ and Skill $3$ will decrease by $1$ and $2$, respectively. His level of Skill $2$ does not decrease at the end of day $2$ because he practices Skill $2$ on that day. In this example, we also know that his levels of Skill $2$ and Skill $3$ both decrease by $1$ at the end of day $1$.

Prof. Pang's level of any skill will not decrease below $0$. For example, if his level of some skill is $3$ and at the end of some day, this level is decreased by $4$, it will become $0$ instead of $-1$.

Prof. Pang values all skills equally. Thus, he wants to maximize the sum of his three skill levels after the end of day $n$. 

Given $a_{i,j}$ ($1\le i\le n, 1\le j\le 3$), find the maximum sum.

## 输入格式

The first line contains a single integer $T~(1 \le T \le 1000)$ denoting the number of test cases.

For each test case, the first line contains an integer $n~(1 \le n \le 1000)$. The $(i+1)$-th line contains three integers $a_{i,1}, a_{i,2}, a_{i,3}$ ($0\le a_{i,j}\le 10000$ for any $1\le i\le n, 1\le j\le 3$).

It is guaranteed that the sum of $n$ over all test cases is no more than $1000$.
## 输出格式

For each test case, output the maximum possible sum of skill levels in one line. 
## 样例

### 样例输入 #1
```
2
3
1 1 10
1 10 1
10 1 1
5
1 2 3
6 5 4
7 8 9
12 11 10
13 14 15

```
### 样例输出 #1
```
26
41
```
## 题目翻译

#### 题目描述。
庞博士有 $3$ 项技能：喝汽水、猎狐和炒股，编号分别为 $1,2,3$。初始时，每项技能的熟练度为 $0$。

接下来有 $n$ 天。在第 $i$ 天，庞博士可以选择一项技能（假设是第 $j$ 项）进行练习，然后在这天结束时让这项技能的熟练度增加 $a_{i,j}$。同时，如果某一项技能（假设是第 $k$ 项）已经有 $x$ 天没有练习，那么在这天结束时，这项技能的熟练度会减少 $x$。当然，任何一项技能的熟练度都不可能小于 $0$。

现在，庞博士想知道：在第 $n$ 天结束后，这 $3$ 项技能的熟练度之和最大为多少。由于他非常忙，而且他的日程和对习惯的适应程度可能有变，所以庞博士把这 $T$ 个问题交给了你——每个问题的内容都一样，只是给出的数据可能有所不同而已。
#### 输入格式
第一行，一个正整数 $T~(1 \leq T \leq 1000)$，表示数据组数。

对于每组数据，输入 $(n + 1)$ 行。

* 第一行，一个正整数 $n~(1 \leq n \leq 1000)$，表示天数。

* 接下来 $n$ 行，每行 $3$ 个非负整数，表示题目描述中的 $a_{i,j}~(1 \leq i \leq n,1 \leq j \leq 3,0 \leq a_{i,j} \leq 10000)$。
#### 输出格式
对于每组数据，输出 $1$ 行 $1$ 个数，表示答案。


---

---
title: "[EC Final 2022] Coloring"
layout: "post"
diff: 省选/NOI-
pid: P9716
tag: ['动态规划 DP', '2022', 'O2优化', '基环树', 'ICPC']
---
# [EC Final 2022] Coloring
## 题目描述

You are given $n$ elements numbered from $1$ to $n$. Element $i$ has value $w_i$ and color $c_i$. Each element also has a pointer $a_i$ to some other element.

Initially, the color of element $s$ is $1$, while the color of all the other elements is $0$. More formally, $c_s=1$ and $c_i=0$ for all $i\neq s$ $(1 \le i \le n)$.

You can perform the following operation for any number of times:

- Assign $c_i\leftarrow c_{a_i}$ at a cost of $p_i$.

Your score is equal to the sum of values of all the elements with color $1$ after the operations minus the sum of costs of the operations.

Find the maximum possible score you can obtain.
## 输入格式

The first line contains two integers $n,s$ ($1 \leq s\le n \leq 5\times 10^3$) $-$ the number of elements and the element with color $1$ initially.

The second line contains $n$ integers $w_1,w_2,\dots,w_n$ ($-10^9\le w_i\le 10^9$) $-$ the value of the elements.

The third line contains $n$ integers $p_1,p_2,\dots,p_n$ ($0\le p_i\le 10^9$) $-$ the cost of changing the color of each element.

The fourth line contains $n$ integers $a_1,a_2,\dots,a_n$ ($1\le a_i\le n$, $a_i\neq i$).
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
3 1
-1 -1 2
1 0 0
3 1 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10 8
36175808 53666444 14885614 -14507677 
-92588511 52375931 -87106420 -7180697 
-158326918 98234152
17550389 45695943 55459378 18577244 
93218347 64719200 84319188 34410268 
20911746 49221094
8 1 2 2 8 8 4 7 8 4
```
### 样例输出 #2
```
35343360
```
## 提示

(There won’t be extra line breakers 
in the actual test cases.)

In the first sample, you can successively perform the following operations:

- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[1,1,0]$;
- Assign $c_1\leftarrow c_{a_1}$ at a cost of $p_1$, then $c=[0,1,0]$;
- Assign $c_3\leftarrow c_{a_3}$ at a cost of $p_3$, then $c=[0,1,1]$;
- Assign $c_2\leftarrow c_{a_2}$ at a cost of $p_2$, then $c=[0,0,1]$.

After the operations, only the color of element $3$ is $1$, so your score is equal to $w_3-(p_2+p_1+p_3+p_2)=1$. It can be shown that it is impossible to obtain a score greater than $1$.
## 题目翻译

**【题目描述】**

给定 $n$ 个元素，编号从 $1$ 到 $n$。元素 $i$ 的值为 $w_i$，颜色为 $c_i$。每个元素还有一个指针 $a_i$ 指向另一个元素。

最初，元素 $s$ 的颜色为 $1$，而所有其他元素的颜色都为 $0$。更正式地说，对于所有 $i\neq s$ $(1 \le i \le n)$，有 $c_s=1$ 和 $c_i=0$。

你可以任意多次执行以下操作：

- 以代价 $p_i$ 将 $c_i\leftarrow c_{a_i}$。

你的得分等于所有颜色为 $1$ 的元素值的总和减去操作的总代价。

找出你能够获得的最大可能得分。

**【输入格式】**

第一行包含两个整数 $n$ 和 $s$（$1 \leq s\le n \leq 5\times 10^3$）$-$ 元素数量以及初始颜色为 $1$ 的元素。

第二行包含 $n$ 个整数 $w_1,w_2,\dots,w_n$（$-10^9\le w_i\le 10^9$）$-$ 元素的值。

第三行包含 $n$ 个整数 $p_1,p_2,\dots,p_n$（$0\le p_i\le 10^9$）$-$ 改变每个元素颜色的代价。

第四行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le n$, $a_i\neq i$）。

**【输出格式】**

输出一行一个整数，表示答案。

**【样例解释】**

在第一个样例中，你可以依次执行以下操作：

- 以代价 $p_2$ 将 $c_2\leftarrow c_{a_2}$，然后 $c=[1,1,0]$；
- 以代价 $p_1$ 将 $c_1\leftarrow c_{a_1}$，然后 $c=[0,1,0]$；
- 以代价 $p_3$ 将 $c_3\leftarrow c_{a_3}$，然后 $c=[0,1,1]$；
- 以代价 $p_2$ 将 $c_2\leftarrow c_{a_2}$，然后 $c=[0,0,1]$。

操作后，只有元素 $3$ 的颜色为 $1$，因此你的得分等于 $w_3-(p_2+p_1+p_3+p_2)=1$。可以证明无法获得大于 $1$ 的得分。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[EC Final 2022] Binary String"
layout: "post"
diff: 省选/NOI-
pid: P9717
tag: ['2022', 'O2优化', 'KMP 算法', 'ICPC']
---
# [EC Final 2022] Binary String
## 题目描述

You are given a binary string $a_0a_1a_2\dots a_{n-1}$ arranged on a cycle. Each second, you will change every $01$ to $10$ simultaneously. In other words, if $a_i = 0$ and $a_{(i+1) \bmod n} = 1$, you swap $a_i$ and $a_{(i+1)\bmod n}$. For example, we will change $\texttt{100101110}$ to $\texttt{001010111}$.

You need to answer how many different strings will occur in infinite seconds, modulo $998244353$.

Note: Two strings $a_0a_1\dots a_{n-1}$ and $b_0b_1\dots b_{n-1}$ are different if there exists an integer $i\in \{0,1,\ldots, n-1\}$ such that $a_i\neq b_i$. Thus, the cyclic shifts of a string may be different from the original string.
## 输入格式

The first line contains an integer $T$ $(1\leq T\leq 10^6)$ $-$ the number of test cases.

For each test case, the first line contains a binary string $a_0 a_1 \dots a_{n-1}$ $(a_i \in \{0, 1\})$.

It is guaranteed that the sum of lengths of strings over all test cases does not exceed $10^7$.
## 输出格式

For each test case, output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
3
1
001001
0001111
```
### 样例输出 #1
```
1
3
9
```
## 题目翻译

**【题目描述】**

给定一个排列在环上的二进制字符串 $a_0a_1a_2\dots a_{n-1}$。每一秒钟，你会同时将每个 $01$ 变为 $10$。换句话说，如果 $a_i = 0$ 且 $a_{(i+1) \bmod n} = 1$，则交换 $a_i$ 和 $a_{(i+1)\bmod n}$。例如，我们将 $\texttt{100101110}$ 变为 $\texttt{001010111}$。

你需要回答在无限秒内会出现多少种不同的字符串，取模 $998244353$。

注意：如果存在整数 $i\in \{0,1,\ldots, n-1\}$ 使得 $a_i\neq b_i$，则两个字符串 $a_0a_1\dots a_{n-1}$ 和 $b_0b_1\dots b_{n-1}$ 是不同的。因此，字符串的循环移位可能与原始字符串不同。

**【输入格式】**

第一行包含一个整数 $T$ $(1\leq T\leq 10^6)$ $-$ 测试用例的数量。

对于每个测试用例，第一行包含一个二进制字符串 $a_0 a_1 \dots a_{n-1}$ $(a_i \in \{0, 1\})$。

保证所有测试用例中字符串长度的总和不超过 $10^7$。

**【输出格式】**

对于每个测试用例，输出一行一个整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[EC Final 2022] Map"
layout: "post"
diff: 省选/NOI-
pid: P9720
tag: ['数学', '2022', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2022] Map
## 题目描述

It is a famous math fact that if you drop a map of a park completely inside the park, then there exists a point on the map which overlays with the point it represents.

Mio likes this fact a lot so she drops a map of her favorite park completely inside the park. The park $P$ can be represented by a rectangle. A map of the park is just a smaller (or equal) version of the park printed on paper. The map is similar to the original rectangle. Each point on the map corresponds to a point in the park by the similarity transformation.

We can define a map formally: A map is a rectangle $M$ (of smaller or equal size) together with a positive real number $r$ and a bijective function $f:M \rightarrow P$ satisfying 

- For every pair of different points $a, b\in M$, $|f(a)-f(b)|/|a-b|=r$.

$|x-y|$ represents the Euclidean distance between points $x$ and $y$. 

Like in many games, Mio can teleport using the map. Precisely, when Mio is at some point $x$ on the map (including the boundary), she may teleport to the corresponding point $f(x)$ in the park. She may also choose not to teleport. The reverse is also true. When she is at point $y$ in the park (including the boundary), she may teleport to the point $f^{-1}(y)$ on the map representing her current location. And she may also choose not to teleport.

Mio can teleport at most $n$ (and at least $0$) times. Each teleport takes $k$ seconds. Mio can also walk on her foot at a speed of $1$ unit per second. 

Given two points $s$ and $t$, find the minimum time Mio needs to reach $t$ from $s$.

Each teleport can be in any direction (from the map to the park, or from the park to the map). The map may be placed upside down. Since the map is inside the park, it is possible that Mio is on the map and in the park simultaneously. In this case, she may teleport in either direction. 

For example, in the following figure, the park is $ABCD$, and the map is $A'B'C'D'$. When Mio is inside the map, she is on the map and in the park simultaneously. When she is at point $D'$, she can teleport from the map to the park (reaching $D$), and from the park to the map (reaching $D^{\prime\prime}$).

![](https://cdn.luogu.com.cn/upload/image_hosting/hz6nq09e.png)
## 输入格式

The first line contains a single integer $T$ ($1\le T\le 100$) denoting the number of test cases.

For each test case, the first line contains the $4$ corners of the rectangle representing the park. The corners are given in clockwise or counterclockwise order. It is guaranteed that the $4$ corners are distinct.

The second line contains the $4$ corners of the rectangle representing the map. The $i$-th corner of the map corresponds to the $i$-th corner of the park for all $1\le i\le 4$. Note that you can figure out whether the map is placed upside down or not by the order of the corners. The corners are given in clockwise or counterclockwise order. It is guaranteed that the map is inside the park. (The boundary of the map may intersect with the boundary of the park at $1$ or more points.) It is guaranteed that the map is valid, i.e., there is a positive real number and a bijective function from the map to the park satisfying the definition above.

The third line contains two points $s$ and $t$. It is guaranteed that $s$ and $t$ are inside (or on the boundary of) the park.

The fourth line contains two integers $k, n$ ($0\le k\le 2\times 10^6, 0\le n\le 100$), the time each teleport needs, and the maximum number of teleports. 

Each point in the input is represented by a pair of integers whose absolute values are no more than $2\times 10^6$. Integers are separated by single spaces.
## 输出格式

For each test case, output one number representing the answer in one line. Your answer is considered correct if its absolute or relative error does not exceed $10^{-9}$.  
## 样例

### 样例输入 #1
```
2
0 0 0 2 4 2 4 0
0 0 0 1 2 1 2 0
2 1 4 2
1 1
0 0 0 3 6 3 6 0
0 1 1 0 3 2 2 3
0 0 4 2
0 3
```
### 样例输出 #1
```
1.0000000000
1.2272623352
```
## 题目翻译

**【题目描述】**

有一个著名的数学定理，如果你把一张公园的地图完全放在公园里，那么地图上存在一个点与它所代表的点重合。

Mio 非常喜欢这个定理，所以她把她最喜欢的公园的地图完全放在了公园里。公园 $P$ 可以用一个矩形表示。公园的地图只是一个较小（或相等）版本的公园在纸上的打印。地图与原始矩形相似。地图上的每个点都通过相似变换对应于公园中的一个点。

我们可以正式定义地图：地图是一个矩形 $M$（大小较小或相等），加上一个正实数 $r$ 和一个双射函数 $f:M \rightarrow P$，满足以下条件：

- 对于 $M$ 中的每对不同的点 $a, b$，$|f(a)-f(b)|/|a-b|=r$。

这里 $|x-y|$ 表示点 $x$ 和点 $y$ 之间的欧几里德距离。

就像许多游戏一样，Mio 可以使用地图进行传送。准确地说，当 Mio 在地图上的某个点 $x$（包括边界）时，她可以传送到公园中相应的点 $f(x)$。她也可以选择不传送。反之亦然。当她在公园中的点 $y$（包括边界）时，她可以传送到代表她当前位置的地图上的点 $f^{-1}(y)$。她也可以选择不传送。

Mio 最多可以传送 $n$ 次（最少为 $0$ 次）。每次传送需要 $k$ 秒。Mio 还可以以每秒 $1$ 个单位的速度步行。

给定两个点 $s$ 和 $t$，找出 Mio 从 $s$ 到 $t$ 需要的最短时间。

每次传送可以是任意方向（从地图到公园，或从公园到地图）。地图可以倒置放置。由于地图位于公园内部，所以 Mio 可能同时在地图上和在公园中。在这种情况下，她可以选择传送的方向。

例如，在下图中，公园是 $ABCD$，地图是 $A'B'C'D'$。当 Mio 在地图上时，她同时在地图上和在公园中。当她在点 $D'$ 时，她可以从地图传送到公园（到达 $D$），并从公园传送到地图（到达 $D^{\prime\prime}$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/hz6nq09e.png)

**【输入格式】**

第一行包含一个整数 $T$（$1\le T\le 100$），表示测试用例的数量。

对于每个测试用例，第一行包含表示公园矩形的 $4$ 个角点。角点按顺时针或逆时针顺序给出。保证 $4$ 个角点不相同。

第二行包含表示地图矩形的 $4$ 个角点。地图的第 $i$ 个角点对应于公园的第 $i$ 个角点，对于所有 $1\le i\le 4$。请注意，您可以通过角点的顺序确定地图是否倒置放置。角点按顺时针或逆时针顺序给出。保证地图位于公园内部。（地图的边界可能与公园的边界在 $1$ 个或多个点相交。）保证地图是有效的，即存在一个正实数和一个从地图到公园的双射函数，满足上述的定义。

第三行包含两个点 $s$ 和 $t$。保证 $s$ 和 $t$ 在公园内部（或在公园的边界上）。

第四行包含两个整数 $k, n$（$0\le k\le 2\times 10^6, 0\le n\le 100$），表示每次传送所需的时间，以及最大传送次数。

输入中的每个点由一对整数表示，其绝对值不超过 $2\times 10^6$。整数之间用单个空格分隔。

**【输出格式】**

对于每个测试用例，输出一行数字表示答案。如果没有解决方案，则输出 $-1$。否则，输出最小的时间。您的答案被认为是正确的，如果其绝对或相对误差不超过 $10^{-9}$。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[EC Final 2022] Aqre"
layout: "post"
diff: 省选/NOI-
pid: P9727
tag: ['2022', 'Special Judge', 'O2优化', '构造', 'ICPC']
---
# [EC Final 2022] Aqre
## 题目描述

Given an $n \times m$ matrix, you need to fill it with $0$ and $1$, such that:

- There cannot be **four** consecutive horizontal or vertical cells filled with the same number.
- The cells filled with $1$ form a connected area. (Two cells are adjacent if they share an edge. A group of cells is said to be connected if for every pair of cells it is possible to find a path connecting the two cells which lies completely within the group, and which only travels from one cell to an adjacent cell in each step.)

Please construct a matrix satisfying the conditions above and has as many $1$s as possible. Output the maximum number of $1$s, and the matrix.
## 输入格式

The first line contains an integer $T~(1\leq T\leq 10^3)$ -- the number of test cases.

For each test case, the first line contains two integers $n, m~(2\leq n, m\leq 10^3)$.

### It is guaranteed that the sum of $n\cdot m$ over all test cases does not exceed $10^6$.
## 输出格式

For each test case, output the maximum number of $1$s in the first line. Then output the matrix in the following $n$ lines. If there are multiple solution, output any.
## 样例

### 样例输入 #1
```
3
2 2
3 4
3 8

```
### 样例输出 #1
```
4
11
11
9
1110
1110
1110
18
11101110
10111011
11011011

```
## 题目翻译

**【题目描述】**

给定一个 $n \times m$ 矩阵，你需要用 $0$ 和 $1$ 填充它，使得满足以下条件：

- 不能有**四个**连续的水平或垂直单元格填有相同的数字。
- 填有 $1$ 的单元格形成一个连通区域。（如果它们共享一个边，则两个单元格是相邻的。如果对于每对单元格，可以找到一条完全位于该区域内的连接两个单元格的路径，并且每一步只能从一个单元格移动到相邻的单元格，则一组单元格被称为连通的。）

请构造一个满足上述条件且具有尽可能多的 $1$ 的矩阵。输出 $1$ 的最大数量以及该矩阵。

**【输入格式】**

第一行包含一个整数 $T~(1\leq T\leq 10^3)$，表示测试用例的数量。

对于每个测试用例，第一行包含两个整数 $n, m~(2\leq n, m\leq 10^3)$。

保证所有测试用例中 $n\cdot m$ 的总和不超过 $10^6$。

**【输出格式】**

对于每个测试用例，输出第一行中 $1$ 的最大数量。然后在接下来的 $n$ 行中输出矩阵。如果有多种解决方案，则输出任意一个。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[NERC 2018] Alice the Fan"
layout: "post"
diff: 省选/NOI-
pid: P9791
tag: ['2018', 'Special Judge', 'ICPC']
---
# [NERC 2018] Alice the Fan
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) A 题。
## 题目描述

Alice 喜欢看排球比赛，她尤其喜欢看 A 队打球，排球比赛的规则如下：

- 一场比赛最多有 $5$ 局。

- 前面 $4$ 均需获得至少 $25$ 分方可获胜，第 $5$ 局仅需获得 $15$ 分。

- 如果单局内其中一方满足获胜条件**但是**双方比分之差不满 $2$，不算获胜。

- 有一方比分达到 $3$ 即为获胜，此时立刻结束比赛。

现在分别给你 A 队和 B 队赢球的个数，请你帮忙确定 A 队最好的比分是多少，或者确定这场球赛还没有结束。

（注：本题定义最好的比分为，如果 A 队可以赢，要使得它们两队的比分差尽可能大，反之尽可能小。）
## 输入格式

第一行一个整数 $m(1 \leq m \leq 50000)$，表示 A 队打过 $m$ 场不同的比赛。

接下来 $m$ 行，每行两个整数 $a(1 \leq a \leq 200)$ 和 $b(1 \leq b \leq 200)$，分别表示该场比赛 A 队和 B 队的得分。
## 输出格式

对于每场比赛，输出 A 队最好的比分情况和一种符合条件的**每场**的比分，或者确定这是不可能的，输出 `Impossible`。
## 样例

### 样例输入 #1
```
6
75 0
90 90
20 0
0 75
78 50
80 100
```
### 样例输出 #1
```
3:0
25:0 25:0 25:0
3:1
25:22 25:22 15:25 25:21
Impossible
0:3
0:25 0:25 0:25
3:0
25:11 28:26 25:13
3:2
25:17 0:25 25:22 15:25 15:11
```
## 提示

测试数据保证 $1 \leq m \leq 50000$，$1 \leq a,b \leq 200$。

注：由于技术原因，SPJ 在评测时出现 UKE 是因为您的代码存在谬误，造成了 SPJ 读取字符时多/少读取到了，后面便无法正常评测。


---

---
title: "[NERC 2018]  Bimatching"
layout: "post"
diff: 省选/NOI-
pid: P9792
tag: ['2018', 'ICPC']
---
# [NERC 2018]  Bimatching
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) B 题。
## 题目描述

你与一些好友一起举办了一个舞会！

在这个舞会上，有 $n$ 位男性和 $m$ 位女性，本来舞蹈的形式是一男一女跳的，但是由于男性紧缺，你并不能让所有女性都有一个男性舞伴，于是你发明了一种新的舞蹈形式：一个男性，搭配两个女舞伴。

当然，每个女性在挑选舞伴时，都会对那些男性舞伴做出评价，如果评价是 $1$，说明这位女性愿意和这位男性一起跳舞，只有当两位女性都愿意和那位男性跳舞时，才能成为一对舞伴。

你作为一个组织者，自然要为大家着想，你需要求出能凑出的最多的舞伴对数，**每个舞伴不能重叠**。
## 输入格式

第一行一个数 $t (1 \leq t \leq 20)$，表示数据组数。

接下来 $t$ 组数据，每组第一行两个整数 $n$ 和 $m$，此处我们保证 $1 \leq n,m$ 且 $n + m \leq 150$。

然后一个 $n \times m$ 的矩阵，$a_{i,j}$ 表示 $j$ 号女士是否愿意和 $i$ 号男士一起跳舞。
## 输出格式

对于每组测试数据，输出一行，表示最多能凑出的舞伴对数。
## 样例

### 样例输入 #1
```
2
2 3
111
111
3 4
0110
1100
0011
```
### 样例输出 #1
```
1
2
```
### 样例输入 #2
```
1
3 6
001100
111111
001100
```
### 样例输出 #2
```
2
```
## 提示

数据保证 $1 \leq t \leq 20$，$1 \leq n, m$ 且 $n + m \leq 150$。

下图是对样例一和样例二的解释，其中加粗部分表示其中的一种可行方案。

样例一：

![](https://cdn.luogu.com.cn/upload/image_hosting/9dfwv4dr.png)

样例二：

![](https://cdn.luogu.com.cn/upload/image_hosting/woscpjcn.png)


---

---
title: "[NERC 2018]  Distance Sum"
layout: "post"
diff: 省选/NOI-
pid: P9794
tag: ['2018', 'ICPC']
---
# [NERC 2018]  Distance Sum
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) D 题。
## 题目描述

给你一个 $n$ 个顶点 $m$ 条边的连通无向图，定义 $u$ 与 $v$ 的距离 $d(u, v)$ 为从 $u$ 到 $v$ 最短路径上经过的边数。

现在请你求出 $\sum_{u=1}^n \sum_{v=u+1}^n d(u,v)$。
## 输入格式

第一行给定两个整数 $n(1 \leq n \leq 10^5)$，$m(n - 1 \leq m \leq n + 42)$，分别表示点数和边数。

接下来 $m$ 行，每行 $2$ 个整数 $x_i$ 和 $y_i(1 \leq x_i,y_i \leq n, x_i \neq y_i)$，表示 $x_i$ 和 $y_i$ 之间有一条边。

保证没有重边和自环。
## 输出格式

输出 $\sum_{u=1}^n \sum_{v=u+1}^n d(u,v)$。
## 样例

### 样例输入 #1
```
4 4
1 2
2 3
3 1
3 4
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
7 10
1 2
2 6
5 3
5 4
5 7
3 6
1 7
5 1
7 4
4 1
```
### 样例输出 #2
```
34
```
## 提示

对于所有数据保证 $1 \leq n \leq 10^5$，$n-1 \leq m \leq n + 42$，$1 \leq x_i, y_i \leq n$ 且 $x_i \neq y_i$。

样例一的图是：

![](https://cdn.luogu.com.cn/upload/image_hosting/39wue8qr.png)

其中 $d(1,2) = 1$，$d(1,3) = 1$，$d(1,4) = 2$，$d(2,3) = 1$，$d(2,3) = 2$，$d(3,4) = 1$，总和为 $1 + 1 + 2 + 1 + 2 + 1 = 8$。

样例二为：

![](https://cdn.luogu.com.cn/upload/image_hosting/89k279bd.png)


---

---
title: "[NERC 2018]  Interval-Free Permutations"
layout: "post"
diff: 省选/NOI-
pid: P9799
tag: ['2018', 'ICPC']
---
# [NERC 2018]  Interval-Free Permutations
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) I 题。
## 题目描述

我们定义一个从 $1 \sim n$ 的排列是“间隔排列”的情况是，在这个排列中存在连续的一段长度为 $2 \sim n-1$ 的子区间使得这段子区间在排序后是一串连续的自然数。比如，$\{6,7,1,8,5,3,2,4\}$ 是一个“间隔排列”，因为 $\{6,7\}$，$\{5,3,2,4\}$，$\{3,2\}$ 经过排序后都是一段连续的自然数。

现在已知 $n$，请你输出**不是**“间隔排列”的排列总数，由于输出可能很大，请对 $p$ 取模。
## 输入格式

第一行两个整数 $t (1 \leq t \leq 400)$ 和 $p (10^8 \leq p \leq 10^9)$，分别表示数据组数和模数。

接下来 $t$ 行，一行一个整数 $n (1 \leq n \leq 400)$。
## 输出格式

对于每组数据输出 $1 \sim n$ 的所有排列中**不是**“间隔排列”的排列总数对 $p$ 取模的值。
## 样例

### 样例输入 #1
```
4 998244353
1
4
5
9
```
### 样例输出 #1
```
1
2
6
28146
```
### 样例输入 #2
```
1 437122297
20
```
### 样例输出 #2
```
67777575
```
## 提示

数据保证 $1 \leq t \leq 400$，$10^8 \leq p \leq 10^9$，$1 \leq n \leq 400$。

对于样例一的解释：

第二组数据存在 $\{2,4,1,3\}$ 和 $\{3,1,4,2\}$ 符合要求。

第三组数据存在 $\{2,4,1,5,3\}$，$\{2,5,3,1,4\}$，$\{3,1,5,2,4\}$，$\{3,5,1,4,2\}$，$\{4,1,3,5,2\}$ 和 $\{4,2,5,1,3\}$ 满足要求。

对于样例二，一共有 $264111424634864638$ 种可能。


---

---
title: "[NERC 2018] JS Minification"
layout: "post"
diff: 省选/NOI-
pid: P9800
tag: ['2018', 'ICPC']
---
# [NERC 2018] JS Minification
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) J 题。
## 题目描述

你有一个程序，其中每行包含 $0$ 个或多个可以用空格分隔的标记，你需要将其按下列方法“压行”。

- 在每一行中，如果存在 `#` 开头的部分，说明这是一个注释，其与其同一行后面的东西一起不被执行。

- 通过重复跳过空格并从当前解析位置开始查找可能最长的标识符，将每一行从左到右解析为标识符序列，从而将源代码转换为标识符序列。下面列出了所有可能的标识符：

> - 保留标识符：缩小过程中应保留的任何类型的运算符、分隔符、文字、保留字或库函数的名称。保留标记是不包含 `#` 的非空格 ASCII 字符的固定字符串。
> - 数字标识符：有数字组成的一连串数字字符串。
> - 单词标识符：由以下集合中的一系列字符组成：小写字母、大写字母、数字、`_`、`$` 且不以数字开头。

请注意，在压缩过程中，满足数字或单词定义，但出现在保留标记列表中的**最长字符序列**被视为保留标识符。

在压缩过程中，使用以下算法以系统的方式重命名单词：

- 定义 $s$ 为若干个由小写字母组成的字符串按长度为第一关键词，字典序为第二关键词进行排序后的序列。

- 将标识符序列中遇到的第一个单词重命名为目标单词列表中的第一个词，并将标识符顺序中出现的所有相同单词重命名成第一个词。然后将标识符序列中遇到的第二个新词重命名为目标单词列表中的第二单词，依此类推。

此外，你可以删除原本某些不必要的空格与换行符。但是注意，你删除后并不可以使原本不是标识符的某些字符串变成了标识符，或是原本是标识符的变成了不是标识符的。
## 输入格式

输入的第一行包含一个整数 $n \ (1 \leq n \leq 40)$，代表标识符的数量。

输入的第二行包含由空格分隔的保留标识符的列表，该列表中没有重复，长度不小于 $1$，不大于 $20$。

输入的第三行包含单个整数 $m \ (1 \leq m \leq 40)$，代表输入代码中的行数。

接下来 $m$ 行一行一串代码（可能包含前导空格）。
## 输出格式

输出一行，是对输入代码进行压缩处理的结果。输出解析后的与具有相应重命名后的标识符序列，并且应包含尽可能少的空格。如果有多种方法，那请输出空格最少且长度最小的。
## 样例

### 样例输入 #1
```
16
fun while return var { } ( ) , ; > = + ++ - --
9
fun fib(num) { # compute fibs
  var return_value = 1, prev = 0, temp;
  while (num > 0) {
    temp = return_value; return_value = return_value + prev;
    prev = temp;
    num--;
  }
  return return_value;
}

```
### 样例输出 #1
```
fun a(b){var c=1,d=0,e;while(b>0){e=c;c=c+d;d=e;b--;}return c;}

```
### 样例输入 #2
```
10
( ) + ++ : -> >> >>: b c)
2
($val1++ + +4 kb) >> :out
b-> + 10 >>: t # using >>: 

```
### 样例输出 #2
```
(a+++ +4c )>> :d b->+10>>:e

```
## 提示

保证数据范围 $1 \leq n \leq 40$，$1 \leq m \leq 40$。


---

---
title: "[NERC 2018] King Kog’s Reception"
layout: "post"
diff: 省选/NOI-
pid: P9801
tag: ['2018', 'ICPC']
---
# [NERC 2018] King Kog’s Reception
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) K 题。
## 题目描述

有些骑士想要拜访国王，但是由于这里的骑士都很遵守礼节，他们都会提前预约好他要来拜访的时刻和拜访将持续的时间。骑士按照接待处记录的时刻顺序依次拜访国王，每个骑士必须等前面的骑士结束拜访。

很不幸，公主也准备要来拜访国王，但善良的公主并不会为此而打乱骑士们拜访的顺序，而她会等待骑士们拜访完了再来拜访，请你计算公主要等多长时间。
## 输入格式

共 $q+1$ 行。

第一行一个整数 $q (1 \leq q \leq 3 \times 10^5)$。

然后 $q$ 行，先是一个字符。

- 如果字符是 `+`，紧跟在后面两个数字，表示骑士 $i$ 要于 $t (1 \leq t \leq 10^6)$ 时刻到达，拜访时间 $d(1 \leq d \leq 10^6)$ 时间单位。

- 如果字符是 `-`，后面一个数字 $i(1 \leq i \leq q)$，表示骑士 $i$ 暂时取消了他的预约。

- 如果字符是 `?`，后面一个数字 $t (1 \leq t \leq 10^6)$，表示公主将于 $t$ 时刻拜访。
## 输出格式

对于每个 `?`，输出一行，表示公主要等待多长时间。注意此处公主拜访时骑士的预约记录只有前面的几个，并不包含后面加进来的。
## 样例

### 样例输入 #1
```
19
? 3
+ 2 2
? 3
? 4
+ 5 2
? 5
? 6
+ 1 2
? 2
? 3
? 4
? 5
? 6
? 7
? 9
- 8
? 2
? 3
? 6
```
### 样例输出 #1
```
0
1
0
2
1
3
2
1
2
1
0
0
2
1
1
```
## 提示

对于所有数据，保证 $1 \leq q \leq 3 \times 10^5$，$1 \leq t \leq 10^6$，$1 \leq d \leq 10^6$。


---

---
title: "[ICPC 2020 Shanghai R] Fountains"
layout: "post"
diff: 省选/NOI-
pid: P9824
tag: ['动态规划 DP', '2020', '上海', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Fountains
## 题目描述

Suppose you and your teammate Mixsx will attend the Namomo Camp. The Namomo Camp will happen in $n$ consecutive days. We name the $i$-th day as day $i$ ($1\le i\le n$). The cost of day $i$ is $s_i$. 

Unfortunately, the schedule of the Namomo Camp conflicts with Mixsx's final exams. Mixsx has final exams every day between day $L$ and day $R$. The exact value of $L$ and $R$ have not been announced by his college so we assume that every pair of integers $L$ and $R$ satisfying $1\le L\le R\le n$ will be chosen with probability $1/(n(n+1)/2)$. He decides to take all the exams and thus be absent from the Namomo Camp from day $L$ to day $R$. His $\textit{loss}$ will be $\sum_{i=L}^R s_i$ in this case. 

As Mixsx's teammate, you want Mixsx to give up his final exams and come back to the Namomo Camp. You can prepare $k$ plans before $L$ and $R$ are announced. In the $i$-th plan ($1\le i\le k$), you shut the electricity off to his college every day from day $l_i$ to day $r_i$. You can choose the values of $l_i$ and $r_i$ as long as they are two integers satisfying $1\le l_i\le r_i\le n$.

Once $L$ and $R$ are announced, you can choose a plan $x$ ($1\le x\le k$) such that $L\le l_x\le r_x\le R$. Then Mixsx will come back to the Namomo Camp on every day from day $l_x$ to day $r_x$. His loss becomes $\sum_{i=L}^R s_i-\sum_{i=l_x}^{r_x} s_i$ in this case. You will choose a plan that minimizes Mixsx's loss. If no plan $x$ satisfies $L\le l_x\le r_x\le R$, Mixsx will attend his final exams normally and his loss is $\sum_{i=L}^R s_i$.

Please calculate the minimum possible expected loss $ans_k$ of Mixsx if you choose the $k$ plans optimally. Output $ans_k\cdot n(n+1)/2$ for every $k$ from $1$ to $n(n+1)/2$.

Formally, given a list of $n$ numbers $s_i$ $(1 \leq i \leq n)$, define a loss function $C(L, R) = \sum_{i=L}^R s_i$. Given an integer $k$ ($1 \leq k \leq n (n + 1) / 2$), you should select $2k$ integers $l_1, \ldots, l_k, r_1,\ldots, r_k$ satisfying $1\le l_i\le r_i\le n$ for all $1 \leq i \leq k$, such that

$$\sum_{1\leq L\leq  R\leq n} \left[C(L, R) - \max_{1\le i\le k, L \leq l_i \leq r_i \leq R} C(l_i, r_i) \right]$$

 is minimized. ($\max_{1\le i\le k, L \leq l_i \leq r_i \leq R} C(l_i, r_i)$ is defined as $0$ if no $i$ satisfies $1\le i\le k$ and $L \leq l_i \leq r_i \leq R$.) Output the minimized value for every integer $k$ in $[1, n(n + 1) / 2]$. 
## 输入格式

The first line contains an integer $n~(1 \leq n \leq 9)$. The second line contains $n$ space separated integers $s_i~(1 \leq s_i \leq 10^9)$.
## 输出格式

The output contains $n (n + 1) / 2$ integers in their own lines, the expectations when $k = 1, \ldots, n (n + 1) / 2$ multiplied by $n (n + 1) / 2$. It can be shown that the results are always integers.
## 样例

### 样例输入 #1
```
1
1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
2
13 24
```
### 样例输出 #2
```
26
13
0
```
### 样例输入 #3
```
3
6 4 7
```
### 样例输出 #3
```
33
21
12
8
4
0
```
## 提示

For the first test case, we only need to consider the case $k = 1$. We can only choose $l_1=r_1=1$. Then the expected loss is $C(1, 1) - C(1, 1) = 0$ and the result is $0 \times 1 \times (2) / 2 = 0$.

For the third test case, consider the case when $k = 3$. We choose $l_1=r_1=1$, $l_2=r_2=3$ and $l_3=1, r_3=3$. The expected loss is $2$. And the result is $2 \times 6 = 12$.
## 题目翻译

给出一个长度为 $n$ 的序列 $s$，定义 $C(l,r)=\sum\limits_{i=l}^r s_i$。

对于每个 $1 \le k \le n(n+1)/2$，找出 $k$ 个二元组 $(l_1,r_1),\dots,(l_k,r_k)$，满足 $1 \le l_i \le r_i \le n$，最小化：

$$\sum_{1\leq L\leq  R\leq n} \left[C(L, R) - \max_{1\le i\le k, L \leq l_i \leq r_i \leq R} C(l_i, r_i) \right]$$

您只需要对于每个 $k$ 输出对应的值，不需要输出方案。


---

---
title: "[ICPC 2020 Shanghai R] Traveling Merchant"
layout: "post"
diff: 省选/NOI-
pid: P9829
tag: ['2020', '上海', 'O2优化', '双连通分量', '最近公共祖先 LCA', 'ICPC']
---
# [ICPC 2020 Shanghai R] Traveling Merchant
## 题目描述

Mr. Lawrence is a traveling merchant who travels between cities and resells products. Basically, to earn from it, he needs to buy products at a very low price and sell them at a higher price. Your task is to tell him whether there exists an endless traveling path that can earn money all the time.

To make things simple, suppose there are $n$ cities named from $0$ to $n-1$ and $m$ undirected roads each of which connecting two cities. Mr. Lawrence can travel between cities along the roads. Initially he is located at city $0$ and each of the city $i$ has a starting price $c_i$, either $\text{Low}$ or $\text{High}$. Due to the law of markets, the price status at city $i$ will change (i.e. $\text{High}$ price will become $\text{Low}$ price, or vice versa) after he departs for a neighboring city $j$ from $i$. (City $j$ is a neighboring city of city $i$ when one of the $m$ roads connects city $i$ and city $j$.) For some reasons (e.g. product freshness, traveling fee, tax), he $\textbf{must}$:

- Start at city $0$ and buy products at city $0$. It is guaranteed that $c_0$ is $\text{Low}$.
- When he arrives some city, he either sells products or buys products. It is not allowed for him to do nothing before he leaves the city.
- After buying products at some city $i$, he must travel to some neighboring city $j$ whose price $c_j$ is $\text{High}$ and sell the products at city $j$.
- After selling products at some city $i$, he must travel to some neighboring city $j$ whose price $c_j$ is $\text{Low}$ and buy the products at city $j$.

As a result, the path will look like an alternation between ``buy at low price'' and ``sell at high price''.

An endless earning path is defined as a path consisting of an endless sequence of cities $p_0, p_1,\dots$ where city $p_i$ and city $p_{i+1}$ has a road, $p_0=0$, and the price alternates, in other words $c_{p_{2k}}=\text{Low}$ (indicates a buy-in) and $c_{p_{2k+1}}=\text{High}$ (indicates a sell-out) for $k\geq0$. Please note here $c_{p_i}$ is the price when $\textbf{arriving}$ city $p_i$ and this value may be different when he arrives the second time.

Your task is to determine whether there exists any such path.
## 输入格式

There are several test cases. The first line contains a positive integer $T$ indicating the number of test cases. Each test case begins with two positive integers $n$ and $m$ indicating the number of cities and the number of roads. 

The next line is a string $c$ of length $n$ containing `H' or `L'. The $i$-th ($0\le i<n$) charactor of $c$ is $H$ if the starting price $c_i$ at city $i$ is $\text{High}$. The $i$-th ($0\le i<n$) charactor of $c$ is $L$ if the starting price $c_i$ at city $i$ is $\text{Low}$. 

The $i$-th line ($1\le i\le m$) of the following $m$ lines contains two different cities $u_i$ and $v_i$, indicating a road between $u_i$ and $v_i$.

The sum of the values of $n$ over all test cases is no more than $200,000$. The sum of the values of $m$ over all test cases is no more than $200,000$. For each test case, $c_i\in\{\text{H},\text{L}\}$ holds for each $i\in \{0, \ldots, n-1\}$. $c_0$ is always $L$. $0\leq u_i,v_i<n$ and $u_i\neq v_i$ hold for each $i\in \{1,\ldots, m\}$. No two roads connect the same pair of cities.
## 输出格式

For each test case, output a line of ``yes`` or ``no``, indicating whether there exists an endless earning path.
## 样例

### 样例输入 #1
```
2
4 4
LHLH
0 1
1 2
1 3
2 3
3 3
LHH
0 1
0 2
1 2
```
### 样例输出 #1
```
yes
no
```
## 提示

In the first sample test case, the endless earning path is $0\rightarrow 1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2\rightarrow 3\rightarrow \dots$. In the illustration, cities with $\text{Low}$ price are filled with stripe.

![](https://cdn.luogu.com.cn/upload/image_hosting/2ohq2wfi.png)

In the second sample test case, Mr. Lawrence can only make one move from city $0$ and after that all cities will have $\text{High}$ price. Thus, no further moves can be made.

![](https://cdn.luogu.com.cn/upload/image_hosting/fcv1tw87.png)

## 题目翻译

### 题目描述

劳伦斯先生是一位在不同城市转售商品的旅行商人。基本地，为了赚钱，他需要以低价买进商品，再以高价卖出。现在请你为他规划一条可以一直盈利的旅行路线。

简单地说，假设有 $n$ 座城市，标号为 $0$ 到 $n-1$ ，以及 $m$ 条连接特定两座城市的路，劳伦斯先生可以通过这些路到访每座城市。最初劳伦斯先生位于第 $0$ 座城市，并且对于城市 $i$ 都有一个起始价格 $c_i$ 。根据市场规律，当他从城市 $i$ 来到相邻的城市 $j$ 时（当且仅当城市 $i$ 与城市 $j$ 之间有路径相连时，才称 $i$ 与 $j$ 为相邻城市），城市 $i$ 的价格状况会发生变化（高价会变成低价，低价也可能变成高价）。而因为一些原因（比如商品的新鲜程度，旅行费用，税务等），他**必须**：

- 从城市 $0$ 出发并在城市 $0$ 购买一些商品。保证城市 $0$ 的起始价格很**低**。
- 每当他到达一座城市后，他**必须**售卖**或**购买一些商品。
- 若他在城市 $i$ 购买了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **高于** $c_i$ 的城市 $j$ ，并在那里卖掉手中来自城市 $i$ 的商品。
- 若他在城市 $i$ 售卖了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **低于** $c_i$ 的城市 $j$，并在那里购买一些商品。


因此，最终路径会始终重复 ``低价购入`` 和 ``高价卖出`` 。

一条无尽的盈利路线由无尽的城市序列 $p_0,p_1 \dots$ 组成。其中，城市 $p_i$ 与城市 $p_{p+1}$ 之间有路径相连，$p_0 = 0$，且价格高低是交替循环的，也就是说当 $k \ge 0$ 时，城市 $p_{2k}$ 的价格 $c_{p_{2k}} = \text{Low}$ (要在这个城市购买商品) 而相邻城市 $p_{2k+1}$ 的价格 $c_{p_{2k+1}} = \text{Hign}$ (要在这个城市卖出商品)。

**注意**：$c_{p_i}$ 是 **到达** 城市 $p_i$ 时的价格，而当他第二次到达城市 $p_i$ 时，这个价格可能会因为市场规律而变化。

你需要写一个程序，判断是否有这样一条永远盈利的路径存在。
### 输入格式

输入有多组数据。所有数据的第一行是一个整型 $T$ 表示数据组数。每组数据的第一行是两个整型 $n$ 和 $m$，表示城市的数量和道路的数量。

每组数据的第二行是一个长度为 $n$ ，由 $H$ 或 $L$ 组成的字符串 $c$ 。字符串 $c$ 的第 $i$ 个字符若为 $H$，则表示城市 $i$ 的起始价格 $c_i$ **高**，反之若为 $L$ 则表示城市 $i$ 的起始价格 $c_i$ **低**。

接下来 $m$ 行，每行输入一组 $u_i$ 和 $v_i$ ，表示一条连接城市 $u_i$ 和城市 $v_i$ 的双向路径。

所有数据中 $n$ 的总和不超过 $200,000$ ，$m$ 的总和也不超过 $200,000$ 。对于每组数据，$c_i\in\{\text{H}, \text{L}\}$ 对应每个 $i\in\{0, \dots, n-1\}$ ，保证 $c_0$ 总为 $L$ 。保证对于每个 $i\in\{1,\dots,m\}$ ，都有 $0 \leq u_i,v_i < n$ 且 $u_i \neq v_i$ 。保证每两座城市之间只有一条路径相连。

### 输出格式
对于每组数据，输出一行 ``yes`` 或者 ``no`` ，表示是否存在一条无尽的盈利路径。


---

---
title: "[ICPC 2021 Nanjing R] Puzzle in Inazuma"
layout: "post"
diff: 省选/NOI-
pid: P9841
tag: ['2021', 'Special Judge', 'O2优化', '构造', 'ICPC', '分类讨论', '南京']
---
# [ICPC 2021 Nanjing R] Puzzle in Inazuma
## 题目描述

Every traveler knows that they'll be rewarded with a treasure box after solving the puzzles in Inazuma, but few know that these puzzles are designed by Yae Miko, the Guuji of the Grand Narukami Shrine, to test whether the traveler is strong enough to save her friend Raiden Shogun and people of Inazuma.

![](https://cdn.luogu.com.cn/upload/image_hosting/p50zu2m6.png)

After a traveler passes the test Yae will have to reset the puzzles to the initial state. But this time she has some troubles and even doubts that whether some of them are already broken.

Yae's puzzle can be considered as a weighted undirected complete graph $G$ before resetting. We also denote the initial state as another weighted undirected complete graph $H$. Both $G$ and $H$ have exactly $n$ vertices, and these vertices are labeled from $1$ to $n$.

To reset graph $G$ to $H$ Yae can perform the following operation any number of times:
- First select four distinct vertices $a$, $b$, $c$, $d$ and an integer $x$. Note that she can select a different set of $a$, $b$, $c$, $d$ and $x$ each time.
- Let $(i, j)$ be the edge between vertices $i$ and $j$. Increase the weight of $(a, b)$, $(a, c)$ and $(a, d)$ by $x$ and also decrease the weight of $(b, c)$, $(b, d)$ and $(c, d)$ by $x$.

Please help Yae determine whether she can change graph $G$ to graph $H$. If yes you also shall tell her the detailed steps.
## 输入格式

There is only one test case in each test file.

The first line of the input contains an integer $n$ ($4 \leq n \leq 100$) indicating the number of vertices in graph $G$ and $H$.

For the following $(n - 1)$ lines, the $i$-th line contains $(n - i)$ integers $w_{i, i + 1}, w_{i, i + 2}, \cdots, w_{i, n}$ ($-100 \le w_{i, j} \le 100$) where $w_{i, j}$ indicates the weight of the edge connecting vertices $i$ and $j$ in graph $G$.

For the following $(n - 1)$ lines, the $i$-th line contains $(n - i)$ integers $v_{i, i + 1}, v_{i, i + 2}, \cdots, v_{i, n}$ ($-100 \le v_{i, j} \le 100$) where $v_{i, j}$ indicates the weight of the edge connecting vertices $i$ and $j$ in graph $H$.
## 输出格式

If Yae cannot change $G$ to $H$, output `-1`.

Otherwise first output an integer $m$ ($0 \le m \le 10^5$) in one line indicating the number of operations Yae needs.

For the following $m$ lines, output five integers $a_i$, $b_i$, $c_i$, $d_i$ and $x_i$ in the $i$-th line separated by a space, indicating that for the $i$-th operation Yae choose vertices $a_i$, $b_i$, $c_i$, $d_i$ and integer $x_i$. Note that $a_i$, $b_i$, $c_i$, $d_i$ must be distinct and $-10^9 \le x_i \le 10^9$.

It can be proved that if graph $G$ can be changed to graph $H$ there exists a solution with no more than $10^5$ operations.

Note that you don't have to minimize $m$. If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
4
0 1 1
0 0
1
1 0 0
1 1
0

```
### 样例输出 #1
```
1
2 1 3 4 1

```
### 样例输入 #2
```
4
3 3 3
0 0
0
0 0 0
3 3
3

```
### 样例输出 #2
```
1
1 2 3 4 -3

```
### 样例输入 #3
```
5
-12 15 -12 1
37 14 7
7 9
-11
12 5 1 13
-1 -4 -7
-5 -9
18

```
### 样例输出 #3
```
-1

```
## 题目翻译

给定一个 $n$ 个点的带权完全图 $G$，现在你可以对这个图做至多 $10^5$ 次如下操作，使其变成另一张带权完全图 $H$：
- 选取四个点 $a,b,c,d$ 与权值 $x$，使得边 $(a,b),(a,c),(a,d)$ 加上 $x$，边 $(b,c),(b,d),(c,d)$ 减去 $x$。

构造一组方案或判断无解。  
$4\le n\le 100$，边权在 $-100\sim 100$ 之间。


---

---
title: "[ICPC 2021 Nanjing R] Paimon's Tree"
layout: "post"
diff: 省选/NOI-
pid: P9846
tag: ['动态规划 DP', '2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon's Tree
## 题目描述

Paimon has found a tree with $(n + 1)$ initially white vertices in her left pocket and decides to play with it. A tree with $(n + 1)$ nodes is an undirected connected graph with $n$ edges.

Paimon will give you an integer sequence $a_1, a_2, \cdots, a_n$ of length $n$. We first need to select a vertex in the tree and paint it black. Then we perform the following operation $n$ times.

During the $i$-th operation, we select a white vertex $x_i$ which is directly connected with a black vertex $y_i$ by an edge, set the weight of that edge to $a_i$ and also paint $x_i$ in black. After these $n$ operations we get a tree whose edges are all weighted.

What's the maximum length of the diameter of the weighted tree if we select the vertices optimally? The diameter of a weighted tree is the longest simple path in that tree. The length of a simple path is the sum of the weights of all edges in that path.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 5 \times 10^3$) indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 150$) indicating the length of the sequence.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le 10^9$) indicating the sequence.

For the following $n$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n + 1$) indicating that there is an edge connecting vertex $u_i$ and $v_i$ in the tree.

It's guaranteed that there is at most $10$ test cases satisfying $n > 20$.
## 输出格式

For each test case output one line containing one integer indicating the maximum length of the diameter of the tree.
## 样例

### 样例输入 #1
```
2
5
1 7 3 5 4
1 3
2 3
3 4
4 5
4 6
1
1000000000
1 2

```
### 样例输出 #1
```
16
1000000000

```
## 提示

For the first sample test case, we select the vertices in the order of $1, 3, 4, 5, 2, 6$, resulting in the weighted tree of the following image. It's obvious that the longest simple path is of length $16$.

![](https://cdn.luogu.com.cn/upload/image_hosting/vamukdcv.png)
## 题目翻译

# Paimon's Tree

## Translation

### 题目描述

派蒙在她的左口袋中找到了一颗有 $(n+1)$ 个白色节点的树。一颗有 $(n+1)$ 个节点的树是一个有 $n$ 条边的无向连通图。

派蒙会给你一个长度为 $n$ 的整数序列 $a_1,a_2,...,a_n$ 。我们首先需要选择这棵树中的一个节点并将它涂黑。接下来进行以下操作 $n$ 次。

> 在第 $i$ 次操作中，我们选择一个与一个黑色节点 $y_i$ 直连的白色节点 $x_i$ ，将这条边的权值设为 $a_i$ ，并且将节点 $x_i$ 涂黑。

进行上述的 $n$ 次操作后，我们会得到一棵每条边都有权值的树。

在最优的选择节点策略下，这颗树的直径最大是多少？一棵树的直径是这棵树中的最长简单路径的长度。一条简单路径的长度是这条路径中所有边的权值之和。

### 输入格式

一次运行将会给出多个测试数据。输入的第一行包含一个整数 $T$ ，表示测试数据的组数。

对于每个测试数据：

> 第一行包括一个整数 $n$ ，表示序列 $a$ 的长度。
>
> 第二行包括 $n$ 个整数 $a_1,a_2,...,a_n$ ，表示序列 $a$ 的内容。
>
> 在接下来的 $n$ 行中，第 $i$ 行包括两个整数 $u_i$ 与 $v_i$ ，表示在这棵树上 $u_i$ 与 $v_i$ 有一条连边。

### 输出格式

对于每个测试数据，输出一行，表示这棵树在最优操作下的直径长度。

### 数据范围

* $1\le T\le 5\times 10^3$
* $1\le n\le 150$
* $1\le a_i\le 10^9$
* $1\le u_i,v_i\le n+1$
* 保证每个样例中最多有 $10$ 组测试数据满足 $n>20$ 。


---

---
title: "[ICPC 2021 Nanjing R] Secret of Tianqiu Valley"
layout: "post"
diff: 省选/NOI-
pid: P9851
tag: ['2021', 'Special Judge', 'O2优化', '构造', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Secret of Tianqiu Valley
## 题目描述

In the north tower of Tianqiu Valley's ruins, there are some flame torch puzzles and Lumine the traveler is facing the last and the hardest one.

![](https://cdn.luogu.com.cn/upload/image_hosting/sihi5us5.png)

There are $n$ torches in a circle and some torches have been ignited initially. The $i$-th and the $(i \bmod n +1)$-th are adjacent for all $1 \le i \le n$.

To solve the puzzle, all the torches should be ignited. In each move, Lumine can ignite an extinguished torch, and the status of the adjacent torches will be reversed affected by the supernatural. That is, each of the adjacent torches will be ignited if it is currently extinguished, or be extinguished if it is currently ignited.

Time is money, Lumine wants to solve the puzzle in $2n$ moves or determine that the puzzle is unsolvable.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line of the input contains an integer $n$ ($3 \le n \le 10^5$) indicating the number of torches in the circle.

The second line contains a binary string $s_1s_2\cdots s_n$ of length $n$ ($s_i \in \{\text{`0'}, \text{`1'}\}$). If $s_i = \text{`0'}$ the $i$-th torch is extinguished initially; If $s_i = \text{`1'}$ the $i$-th torch is ignited initially. It is guaranteed that not all the torches have been ignited initially.

It is also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

If the puzzle is unsolvable, output `0`.

Otherwise, output an integer $k$ $(1 \le k \le 2n)$ in the first line indicating the number of moves Lumine needs to solve the puzzle. Then output a line containing $k$ integers $t_1, t_2, \cdots, t_k$ separated by a space, where $t_i$ indicating that Lumine will ignite the $t_i$-th torch in the $i$-th move. If there are multiple answers print any of them.

Please, DO NOT output extra spaces at the end of each line or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
2
5
00000
3
001

```
### 样例输出 #1
```
7
2 5 1 2 3 4 2
0

```
## 提示

For the first sample test case, the status of the torch will change like this: $00000$ $\to$ $11100$ $\to$ $01111$ $\to$ $10110$ $\to$ $01010$ $\to$ $00100$ $\to$ $00011$ $\to$ $11111$.
## 题目翻译

有 $n$ 个火炬排成一个环，编号为 $1,2,3,...,n$，输入一个长度为 $n$ 的二进制字符串 $s$，表示这 $n$ 个火炬是否已经被点燃（初始状态）。

你可以点燃一个**熄灭的**火炬 $s_i$，但两侧火炬的状态也会随之逆转（即 $s_{{i-1}}$、$s_{i}$、$s_{i+1}$（在取模条件下）同时取反）。请问，最多逆转 $2n$ 次，能否使所有火炬全部被点燃。如果能，输出对应的逆转次数，否则输出`0`。

- 小提示：$t$ 组数据。


---

---
title: "[EC Final 2021] String-dle Count"
layout: "post"
diff: 省选/NOI-
pid: P9874
tag: ['动态规划 DP', '2021', 'O2优化', 'ICPC']
---
# [EC Final 2021] String-dle Count
## 题目描述

While most people love to play Wordle these days, Prof. Pang has become addicted to String-dle.

String-dle is an interesting string-guessing game where the player tries to guess a string of $k$ capital letters through several rounds. In each round, the player submits a string of length $k$ as his guess, and the system grades the guess through the following pseudo-code:

```
def grading(answer, guess):
  let count be a hash map
  for i = 1 to k:
    if answer[i] not in count:
      count[answer[i]] = 1
    else:
      count[answer[i]] = count[answer[i]] + 1
  let grade be an array of length k
  for i = 1 to k:
    if answer[i] == guess[i]:
      grade[i] = 'O'
      count[guess[i]] = count[guess[i]] - 1
  for i = 1 to k:
    if answer[i] != guess[i]:
      if count[guess[i]] > 0:
        grade[i] = '-'
        count[guess[i]] = count[guess[i]] - 1
      else:
        grade[i] = 'x'
  return grade
```

The grade consisting of $\tt{O}$ (capital letter O), $\tt{-}$ (dash), and $\tt{x}$ (small letter x) is then returned to the player, and the player may base his next guess on the previous grades. The following is an example of one game Prof. Pang played:

```
G: CRANE
A: xx--x
G: UTTER
A: xxOxx
G: NASAL
A: OOxOO
G: NATAL
A: OOOOO
```

Strings after $\tt{G}$ are Prof. Pang's guesses and strings after $\tt{A}$ are the grades of the guesses. 

Prof. Pang really enjoys the game. He believes that he has developed a perfect strategy for it. However, today he goes mad because he thinks the grading system is bugged! He wants to have someone write an analysis program to figure out the number of possible strings that can be the answer to the puzzle based on his list of guesses and grades.

Since the grading system might be bugged, it might not conform to the pseudo-code given above. So specifically, the task is to find how many strings that are consistent with the input. A string s is consistent with the input if for any guess g in the input and its corresponding grade d, grading(s, g)=d.

And of course, you will be doing the programming.
## 输入格式

The first line consists of two integers $n$ and $k$ $(1 \le n \le 10^4, 1 \le k \le 19)$, which are the number of guesses and the length of the string, respectively.

The following lines consist of the guesses and the grades, one per line, correspondingly.
## 输出格式

An integer, denoting how many possible answers there are, modulo $10^9+7$.
## 样例

### 样例输入 #1
```
2 5
CRANE
xx--x
NASAL
OOxOO
```
### 样例输出 #1
```
21
```
### 样例输入 #2
```
1 5
BBBAA
xxxx-
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
2 5
ABCDE
-xxxx
ABCDE
xxxxx
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
1 3
ABC
---
```
### 样例输出 #4
```
2
```
### 样例输入 #5
```
1 15
AAAAAAAAAAAAAAB
-xxxxxxxxxxxxxx
```
### 样例输出 #5
```
918547951
```
### 样例输入 #6
```
1 15
AAAAAAAAAAAAAAA
-xxxxxxxxxxxxxx
```
### 样例输出 #6
```
0
```
### 样例输入 #7
```
1 1
K
x
```
### 样例输出 #7
```
25
```
## 提示

For the second example:

If the answer is $\tt{ACDEF}$, the guess $\tt{BBBAA}$ will produce a grade of $\tt{xxx-x}$.
## 题目翻译

### 题目描述
当大多数人都沉迷于玩 Wordle 的时候，庞教授却已经沉迷于玩 String-dle 了。

String-dle 是一个有趣的猜字符串的游戏，玩家在玩的时候要通过几轮尝试，猜出一个长度为 $k$ 的字符串。并且在每轮尝试中，玩家要提交一个长度为 $k$ 的字符串来作为他的猜测，而系统通过以下伪代码来为提交的猜测评级：
```
def grading(answer, guess):
  let count be a hash map
  for i = 1 to k:
    if answer[i] not in count:
      count[answer[i]] = 1
    else:
      count[answer[i]] = count[answer[i]] + 1
  let grade be an array of length k
  for i = 1 to k:
    if answer[i] == guess[i]:
      grade[i] = 'O'
      count[guess[i]] = count[guess[i]] - 1
  for i = 1 to k:
    if answer[i] != guess[i]:
      if count[guess[i]] > 0:
        grade[i] = '-'
        count[guess[i]] = count[guess[i]] - 1
      else:
        grade[i] = 'x'
  return grade
```
返回的评级包括 $\tt{O}$（大写字母 O）、$\tt{-}$（破折号）和 $\tt{x}$（小写字母 x），且玩家可以基于先前的评级进行下一次猜测。下面是庞教授玩的一局游戏示例：
```
G: CRANE
A: xx--x
G: UTTER
A: xxOxx
G: NASAL
A: OOxOO
G: NATAL
A: OOOOO
```
在字符串 $\tt{G}$ 后面的是庞教授的猜测，以及在字符串 $\tt{A}$ 后面的是该次猜测的评级。

庞教授非常喜欢这个游戏。他确信他已经知道了这个游戏的完美策略。然而，今天他很生气，因为他认为评级系统出了问题！他想让人写一个分析程序，根据他的猜测与评级找出所有可能的可以作为答案的字符串。

由于评级系统可能出了问题，所以它可能不再符合上面给出的伪代码。具体来说，你需要找到所有符合输入的字符串。一个符合输入的字符串是指，对于输入中任意一个猜测  $g$ 和它的正确评级 $d$，都符合  `grading(s, g)=d`。

当然，你接受了这个任务。

### 输入格式

第一行是两个整数 $n$、$k$ $(1 \le n \le 10^4, 1 \le k \le 19)$，分别是猜测的次数和字符串的长度。

下面共有 $2n$ 行，每两行都对应一个猜测和它对应的评级。

### 输出格式

一个整数，表示有多少种可能的答案，并模 $10^9+7$.

### 样例 #1

#### 样例输入 #1

```
2 5
CRANE
xx--x
NASAL
OOxOO
```

#### 样例输出 #1

```
21
```

### 样例 #2

#### 样例输入 #2

```
1 5
BBBAA
xxxx-
```

#### 样例输出 #2

```
0
```

### 样例 #3

#### 样例输入 #3

```
2 5
ABCDE
-xxxx
ABCDE
xxxxx
```

#### 样例输出 #3

```
0
```

### 样例 #4

#### 样例输入 #4

```
1 3
ABC
---
```

#### 样例输出 #4

```
2
```

### 样例 #5

#### 样例输入 #5

```
1 15
AAAAAAAAAAAAAAB
-xxxxxxxxxxxxxx
```

#### 样例输出 #5

```
918547951
```

## 样例 #6

#### 样例输入 #6

```
1 15
AAAAAAAAAAAAAAA
-xxxxxxxxxxxxxx
```

#### 样例输出 #6

```
0
```

### 样例 #7

#### 样例输入 #7

```
1 1
K
x
```

#### 样例输出 #7

```
25
```

### 提示

对于第二个样例:

如果答案是 $\tt{ACDEF}$，则 $\tt{BBBAA}$ 的评级为 $\tt{xxx-x}$.


---

---
title: "[EC Final 2021] Two Walls"
layout: "post"
diff: 省选/NOI-
pid: P9875
tag: ['计算几何', '2021', 'O2优化', 'ICPC']
---
# [EC Final 2021] Two Walls
## 题目描述

Prof. Pang has bought a humanoid cleaning robot to clean his yard. The robot is not very sophisticated. It can either move forward or change its direction at a time, all controlled by Prof. Pang's controller.

Prof. Pang's yard is a 2D plane. The robot needs to move from its current location $A$ to the destination $B$ to fulfill some ``cleaning`` needs of Prof. Pang. However, there are two straight walls $CD$ and $EF$ in Prof. Pang's yard. Since the robot is clumsy, it will fall over if it touches any of the walls (even at endpoints).

Now that Prof. Pang is lazy, he wants to minimize the number of times the robot changes its direction. Can you help him?
## 输入格式

The first line contains a single integer $T$ ($1 \le T \le 10^5$) denoting the number of test cases.

For each test case, the first line contains two integers $x_A, y_A$, the coordinates of point $A$. The second line contains two integers $x_B, y_B$, the coordinates of point $B$.
The third line contains four integers $x_C, y_C, x_D, y_D$, the coordinates of point $C$ and $D$ which are the endpoints of the first wall. The fourth line contains four integers $x_E, y_E, x_F, y_F$, the coordinates of point $E$ and $F$ which are the endpoints of the second wall.

It is guaranteed that neither the current location $A$ nor the destination $B$ of the robot are on any of the walls. A wall may degenerate to a point. It can be proved that the robot can always move from $A$ to $B$ without touching any of the walls. All values lie within $[-10^9, 10^9]$.
## 输出格式

For each test case, print one number $d$ in one line, denoting the minimum number of turns.
## 样例

### 样例输入 #1
```
3
0 0
1 1
2 2 3 3
4 4 5 5
0 0
1 1
2 2 3 3
2 2 3 3
0 0
10 10
10 0 0 10
1 1 2 2
```
### 样例输出 #1
```
0
0
1
```
## 提示

The following are illustrations for the first sample and the third sample.

![](https://cdn.luogu.com.cn/upload/image_hosting/nuyvzg7a.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/diy78yex.png)
## 题目翻译

平面直角坐标系上有两点 $A$ 与 $B$，以及两面墙 $CD,EF$，墙可以视作线段。

请问从 $A$ 到 $B$ 在不碰到墙（端点也不可碰到）的情况下最少要转几次弯（转弯的度数可以任意决定）？


---

---
title: "[EC Final 2021] Check Pattern is Good"
layout: "post"
diff: 省选/NOI-
pid: P9879
tag: ['2021', '网络流', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Check Pattern is Good
## 题目描述

Prof. Shou is given an $n\times m$ board. Some cells are colored black, some cells are colored white, and others are uncolored.

Prof. Shou likes **check patterns**, so he wants to color all uncolored cells and maximizes the number of check patterns on the board.

$4$ cells forming a $2\times 2$ square are said to have the check pattern if they are colored in one of the following ways:

```plain
BW
WB
```

```plain
WB
BW
```

Here `W` ("wakuda" in Chewa language) means the cell is colored black and `B` ("biancu" in Corsican language) means the cell is colored white.
## 输入格式

The first line contains a single integer $T$ $(1\leq T \leq 10^4)$ denoting the number of test cases.

The first line of each test case contains two integers $n$ and $m$ ($1\le n, m\le 100$) denoting the dimensions of the board.

Each of the next $n$ lines contains $m$ characters. The $j$-th character of the $i$-th line represents the status of the cell on the $i$-th row and $j$-th column of the board. The character is `W` if the cell is colored black, `B` if the cell is colored white, and `?` if the cell is uncolored. 

It is guaranteed that the sum of $nm$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, output a line containing the maximum number of check patterns on the board.

In the next $n$ lines, output the colored board in the same format as the input. The output board should satisfy the following conditions.

- It consists of only `B` and `W`.
- If a cell is already colored in the input, its color cannot be changed in the output.
- The number of check patterns equals the answer you print.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?

```
### 样例输出 #1
```
1
WB
BW
1
BWB
WWB
BBW
4
BWB
WBW
BWB

```
## 题目翻译

#### 题目描述

教授 Shou 得到了一个 $(n \times m)$ 的棋盘。一些格子被涂成了黑色，一些被涂成了白色，还有一些没有上色。

教授 Shou 喜欢**棋盘图案**，所以他想给所有未上色的格子涂色，并最大化棋盘上的棋盘图案数量。

如果四个形成一个 $(2 \times 2)$ 方格的单元格以以下任一种方式上色，则说它们形成了一个棋盘图案：

`BW `

`WB`

或者

`WB `

`BW`

这里的 `W`（在奇瓦语中是“wakuda”，意为黑色）表示格子被涂成了黑色，而 `B`（在科西嘉语中是“biancu”，意为白色）表示格子被涂成了白色。

#### 输入格式

第一行包含一个整数 $T (1 \leq T \leq 10^4)$，表示测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $ m$ $(1 \leq n, m \leq 100)$，表示棋盘的尺寸。

接下来的 $n$ 行每行包含 $m$ 个字符。第 $i$ 行的第 $j$ 个字符表示棋盘上第 $i$ 行和第 $j$ 列的格子的状态。如果格子被涂成了黑色，则字符为 `W`；如果格子被涂成了白色，则字符为 `B`；如果格子未上色，则字符为 `?`。

保证所有测试用例中 $ n \times m $ 的总和不超过 $10^6$。

#### 输出格式

对于每个测试用例，输出一行，包含棋盘上的最大棋盘图案数量。

在接下来的 (n) 行中，以输入格式相同的方式输出上色后的棋盘。输出的棋盘应满足以下条件：

* 只包含 `B` 和 `W`。
* 如果输入中的格子已经上色，则在输出中不能改变其颜色。
* 棋盘图案的数量等于你打印的答案。

如果有多种解决方案，输出其中任何一种。


---

---
title: "[ICPC 2018 Qingdao R] Kawa Exam"
layout: "post"
diff: 省选/NOI-
pid: P9886
tag: ['2018', '树上启发式合并', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Kawa Exam
## 题目描述

BaoBao is taking an online exam of the Kawa programming language, which consists of $n$ multiple choice questions. The exam is not easy, as for each question, BaoBao needs to select the one and only one correct answer from $10^5$ available choices! But don't worry, as an active committer of the famous \textit{open-kdk}, BaoBao obviously knows all the correct answers.

Although BaoBao is an expert in Kawa, the developers of the exam system are definitely not experts in software engineering. There are $m$ bugs in the exam system, and the $i$-th bug can be described as $(u_i, v_i)$, which means that BaoBao must select the same choice for question $u_i$ and $v_i$ (even if the choice he selects is incorrect!).

Time is limited, and the exam must go on. The developers only have time to fix one bug. Now the developers are wondering, for all $1 \le i \le m$, what's the maximum possible number of questions BaoBao can correctly answer if they fix the $i$-th bug. Please write a program to solve this problem so that the developers can select a proper bug to fix.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 10^5$, $1 \le m \le 10^5$), indicating the number of questions and the number of bugs.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^5$), where $a_i$ indicates the correct answer for question $i$.

For the following $m$ lines, the $i$-th line has two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$), indicating the $i$-th bug.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ over all test cases will exceed $10^6$.
## 输出格式

For each test case output one line containing $m$ integers $c_1, c_2, \dots, c_m$ separated by a space, where $c_i$ indicates the maximum possible number of questions BaoBao can correctly answer if the $i$-th bug is fixed.

Please, DO NOT output extra spaces at the end of each line, or your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
3
7 5
1 2 1 2 1 2 1
1 2
1 3
2 4
5 6
5 7
3 3
1 2 3
1 2
1 3
2 3
2 3
12345 54321
1 2
1 2
1 1
```
### 样例输出 #1
```
6 5 5 5 4
1 1 1
1 1 1
```
## 提示

The following table explains the first sample test case.

- The ``possible choices`` column indicates a possible set of choices to each question BaoBao can select, leading to a maximum possible number of correctly answered questions;
- The ``correct`` column indicates the number of correctly answered questions using the set of choices provided in the ``possible choices`` column.

$$\begin{array}{|c|c|c|c|}
\hline
\textbf{Bug No.} & \textbf{Possible Choices} & \textbf{Correct} \\
\hline
1 & (1, 2, 1, 2, 1, 1, 1) & 6 \\
\hline
2 & (2, 2, 1, 2, 1, 1, 1) & 5 \\
\hline
3 & (1, 1, 1, 2, 1, 1, 1) & 5 \\
\hline
4 & (1, 1, 1, 1, 1, 2, 1) & 5 \\
\hline
5 & (1, 1, 1, 1, 1, 1, 1) & 4 \\
\hline
\end{array}$$

For the second sample test case, no matter which bug is fixed, BaoBao has to select the same choice for all the three questions. As the correct answer for each question is different, BaoBao can only correctly answer 1 question.

For the third sample test case, note that even if the developers fix the first bug, the second bug is still taking effect and BaoBao still has to select the same choice for the two problems. It's the same if the second bug is fixed.
## 题目翻译

BaoBao 正在参加 Kawa 编程语言的在线考试，该考试由 $n$ 个多项选择题组成。考试并不容易，对于每一道题，BaoBao 都需要从 $10^5$ 个可用选项中选择唯一一个正确答案！但别担心，作为著名的 $\text{open-kdk}$ 的积极参与者，BaoBao 显然知道所有正确的答案。

虽然 BaoBao 是 Kawa 方面的专家，但考试系统的开发人员绝对不是软件工程方面的专家。考试系统中有 $m$ 个错误，第 $i$ 个错误可以描述为 $(u_i,v_i)$，这意味着 BaoBao 必须为第 $u_i$ 和 $v_i$ 个问题选择相同的选项（即使他选择的选项不正确！）。

但是考试必须继续，这就意味着开发人员只有时间修复一个错误。现在，开发人员想知道，对于所有的 $1\le i\le m$，如果他们修复 $i$，BaoBao 可以正确回答的最大问题数量是多少。

## 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个整数 $n$ 和 $m$（$1\le n\le 10^5$，$1\le m\le 10^5$），表示问题数量和错误数量。

第二行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le 10^5$），其中 $a_i$ 表示问题 $i$ 的正确答案。

对于以下 $m$ 行，第 $i$ 行有两个整数 $u_i$ 和 $v_i$（$1\le u_i,v_i\le n$），表示第 $i$ 个错误。

保证所有测试用例的 $n$ 和 $m$ 的总和都不会超过 $10^6$。

## 输出格式

对于每个测试用例的输出，一行包含由空格分隔的 $m$ 个整数 $c_1,c_2,\dots,c_m$，其中 $c_i$ 表示如果修复了第 $i$ 个错误，BaoBao 可以正确回答的最大问题数。

请不要在每行末尾输出多余的空格，否则您的答案可能会被认为是错误的！

## 提示

下表解释了第一个示例测试用例。

- “可能的选择”列表示 BaoBao 可以选择的每个问题的一组可能的选择，从而导致正确回答的问题的最大可能数量；

- “正确”列表示使用“可能的选择”列中提供的一组选择正确回答的问题的数量。

$$\begin{array}{|c|c|c|c|}
\hline
\textbf{Bug 编号} & \textbf{可能的选择} & \textbf{正确} \\
\hline
1 & (1, 2, 1, 2, 1, 1, 1) & 6 \\
\hline
2 & (2, 2, 1, 2, 1, 1, 1) & 5 \\
\hline
3 & (1, 1, 1, 2, 1, 1, 1) & 5 \\
\hline
4 & (1, 1, 1, 1, 1, 2, 1) & 5 \\
\hline
5 & (1, 1, 1, 1, 1, 1, 1) & 4 \\
\hline
\end{array}$$

对于第二个样本测试用例，无论哪个 bug 被修复，BaoBao 都必须为所有三个问题选择相同的选项。由于每个问题的正确答案不同，BaoBao 只能正确回答一个问题。

对于第三个示例测试用例，请注意，即使开发人员修复了第一个错误，第二个错误仍然有效，BaoBao 仍然必须为这两个问题选择相同的选项。如果第二个错误被修复，情况也是一样的。


---

---
title: "[ICPC 2018 Qingdao R] Repair the Artwork"
layout: "post"
diff: 省选/NOI-
pid: P9891
tag: ['动态规划 DP', '2018', 'O2优化', '容斥原理', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Repair the Artwork
## 题目描述

DreamGrid has a paper strip with $n$ grids in a line and he has drawn some beautiful patterns in some grids. Unfortunately, his naughty roommate BaoBao drew some other patterns in some other grids when he wasn't at home. Now DreamGrid has to erase BaoBao's patterns without destroying his own patterns.

Let's number the grids from 1 to $n$ from left to right. Each grid either contains DreamGrid's pattern, or contains BaoBao's pattern, or is empty.

Each time, DreamGrid can select two integers $l$ and $r$ (these two integers can be different each time) such that

- $1 \le l \le r \le n$, and
- for all $l \le i \le r$, the $i$-th grid either contains BaoBao's pattern, or is empty,

and change the $i$-th grid to an empty grid for all $l \le i \le r$.

How many ways can DreamGrid change all the grids containing BaoBao's pattern to empty grids by performing the above operation exactly $m$ times? As the answer may be large, please print the answer modulo $10^9 + 7$.

Let $\{(a_1, b_1), (a_2, b_2), \dots (a_m, b_m)\}$ be a valid erasing sequence ($1 \le a_i \le b_i \le n$), where $(a_i, b_i)$ indicates that DreamGrid selects integers $a_i$ and $b_i$ in the $i$-th operation. Let $\{(c_1, d_1), (c_2, d_2), \dots, (c_m, d_m)\}$ be another valid erasing sequence ($1 \le c_i \le d_i \le n$), where $(c_i, d_i)$ indicates that DreamGrid selects integers $c_i$ and $d_i$ in the $i$-th operation. These two sequences are considered different, if there exists an integer $k$ ($1 \le k \le m$) such that $a_k \ne c_k$ or $b_k \ne d_k$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 1000$), indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 100$, $1 \le m \le 10^9$), indicating the number of grids and the number of times to perform the operation.

The second line contains $n$ integers $a_i$ ($a_i \in \{0, 1, 2\}$).

- If $a_i = 0$, the $i$-th grid is empty.
- If $a_i = 1$, the $i$-th grid contains DreamGrid's pattern.
- If $a_i = 2$, the $i$-th grid contains BaoBao's pattern.

It's guaranteed that at most 50 test cases have $n > 50$.
## 输出格式

For each test case, output one line containing the number of ways modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
3
2 2
2 0
3 2
2 1 0
3 1
2 1 0
```
### 样例输出 #1
```
8
3
1
```
## 题目翻译

给定整数 $T(1\le T\le100)$. 对于每组数据 :

给定整数 $n, m(n\le 100, m\le10^9)$. 接下来给出一个长度为 $n$ 的数组 $a$, 保证 $a_i\in \{0, 1, 2\}$.

你需要执行下面的操作恰好 $m$ 次：

- 指定正整数 $l, r \le n$, 满足 $\forall i\in \mathbf{N}$ 且 $i\in[l, r]$, 有 $a_i \ne 1$.
- 将所有满足 $i \in [l, r]$ 的 $a_i$ 赋值为 $0$.

求有多少种不同的操作方式, 使得进行所有 $m$ 次操作后, $\forall i\in[l, r], a_i \ne 2$. 由于答案可能很大，请输出答案对 $10^9 + 7$ 取模的值.

**注意 : 对于每个数据点, 至多有 50 组数据满足 $n>50$.**

Translated by @[Ja50nY0un9](/user/363302).


---

---
title: "[ICPC 2018 Qingdao R] Soldier Game"
layout: "post"
diff: 省选/NOI-
pid: P9893
tag: ['2018', '线段树', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Soldier Game
## 题目描述

DreamGrid and BaoBao are playing a game.  There are $n$ soldiers in the game, numbered from $1$ to $n$. The $i$-th soldier has a power value of $a_i$. DreamGrid and BaoBao are going to divide the soldiers into several teams according to the rules below:

- A team must consist of 1 or 2 soldiers.
- Every soldier must belong to exactly 1 team.
- If a team consists of two soldiers (let's say they are the $i$-th and the $j$-th soldier), there must be $|i - j| = 1$.

The power value of a team is defined as the sum of the team members' power values. For the sake of fairness, they want to minimize the difference between the maximum team power value and the minimum team power value after the division. You are asked to find the minimum difference.


## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$), indicating the number of soldiers.

The second line contains $n$ integers $a_1, a_2, ... , a_n$ ($-10^9 \le a_i \le 10^9$), where $a_i$ indicates the power value of the $i$-th soldier.

It's guaranteed that the sum of $n$ in all test cases will not exceed $10^6$.

## 输出格式

For each test case output one line containing one integer, indicating the minimum difference between the maximum team power value and the minimum team power value.

## 样例

### 样例输入 #1
```
3
5
-1 4 2 1 1
4
1 3 2 4
1
7
```
### 样例输出 #1
```
1
2
0
```
## 提示

We now explain the first sample test case. All possible divisions are listed below.

| Division | Difference | Division | Difference |
| :-: | :-: | :-: | :-:|
|[-1], [4], [2], [1], [1] | 4 - (-1) = 5| [-1, 4], [2], [1], [1] | 3 - 1 = 2 |
| [-1], [4], [2], [1, 1] | 4 - (-1) = 5 | [-1], [4, 2], [1, 1] | 6 - (-1) = 7 |
| [-1], [4], [2, 1], [1] | 4 - (-1) = 5 |  [-1, 4], [2], [1, 1] | 3 - 2 = 1 |
| [-1], [4, 2], [1], [1] | 6 - (-1) = 7 | [-1, 4], [2, 1], [1] | 3 - 1 = 2 |


So the answer is $\min(5, 5, 5, 7, 2, 7, 1, 2) = 1$.
## 题目翻译

**DreamGrid** 和 **BaoBao** 在玩游戏。游戏中有 $n$ 个士兵，编号为 $1\sim n$。第 $i$ 名士兵的权利值为 $a_i$。**DreamGrid** 和 **BaoBao** 将按照以下规则将士兵分成几个小组:

- 一个队伍必须由 $1$ 或 $2$ 名士兵组成。

- 每个士兵必须只属于一个队伍。

- 如果一个团队由两名士兵 $i,j$ 组成，则必须有 $|i - j| = 1$。

团队的权力值被定义为队内士兵权力值的总和。

为了公平起见，他们希望最小化分区后的**最大团队力量值**与**最小团队力量值**之间的**差值**。你被要求找出最小的差值。

有多测。

$1\leq n\leq 10 ^ 5$，$|a_i|\leq 10 ^ 9$，$\sum n\leq 10 ^ 6$。


---

---
title: "[ICPC 2018 Qingdao R] Airdrop"
layout: "post"
diff: 省选/NOI-
pid: P9895
tag: ['2018', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Airdrop
## 题目描述

PUBG is a multiplayer online battle royale video game. In the game, up to one hundred players parachute onto an island and scavenge for weapons and equipment to kill others while avoiding getting killed themselves. Airdrop in this game is a key element, as airdrops often carry with them strong weapons or numerous supplies, helping players to survive.

![](https://cdn.luogu.com.cn/upload/image_hosting/qv9hzuoe.png)
textit{Airdrop in the game(?)

Consider the battle field of the game to be a two-dimensional plane. An airdrop has just landed at point $(x_0, y_0)$ (both $x_0$ and $y_0$ are integers), and all the $n$ players on the battle field, where $(x_i, y_i)$ (both $x_i$ and $y_i$ are integers) indicates the initial position of the $i$-th player, start moving towards the airdrop with the following pattern:


- If the position of a living player at the beginning of this time unit is not equal to $(x_0, y_0)$, he will begin his next move.
- + Let's say he is currently at point $(x, y)$. For his next move, he will consider four points $(x, y - 1)$, $(x, y + 1)$, $(x - 1, y)$ and $(x + 1, y)$.
- + He will select one of the four points whose Manhattan distance to the airdrop $(x_0, y_0)$ is the smallest to be the destination of his next move. Recall that the Manhattan distance between two points $(x_a, y_a)$ and $(x_b, y_b)$ is defined as $|x_a - x_b| + |y_a - y_b|$.
- + If two or more points whose Manhattan distance to the airdrop is the same, he will use the following priority rule to break the tie: $(x, y - 1)$ has the highest priority to be selected, $(x, y + 1)$ has the second highest priority, $(x - 1, y)$ has the third highest priority, and $(x + 1, y)$ has the lowest priority.
- + At the end of this time unit, he arrives at his destination.
- If the position of a living player at the beginning of this time unit is equal to $(x_0, y_0)$, he will continue to fatten his backpack with the supplies in the airdrop and stays at $(x_0, y_0)$.


But the battle is tough and it's almost impossible for all the players to arrive at the airdrop safely. If two or more players meet at point $(x', y')$ other than $(x_0, y_0)$, where both $x'$ and $y'$ are integers, they will fight and kill each other and none of them survive.

BaoBao is a big fan of the game and is interested in the number of players successfully arriving at the position of the airdrop, but he doesn't know the value of $x_0$. Given the value of $y_0$ and the initial position of each player, please help BaoBao calculate the minimum and maximum possible number of players successfully arriving at the position of the airdrop for all $x_0 \in \mathbb{Z}$, where $\mathbb{Z}$ is the set of all integers (note that $x_0$ can be positive, zero or negative).

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $y_0$ ($1 \le n \le 10^5$, $1 \le y_0 \le 10^5$), indicating the number of players and the $y$ value of the airdrop.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($1 \le x_i, y_i \le 10^5$), indicating the initial position of the $i$-th player.

It's guaranteed that the sum of $n$ in all test cases will not exceed $10^6$, and in each test case no two players share the same initial position.

## 输出格式

For each test case output one line containing two integers $p_\text{min}$ and $p_\text{max}$ separated by one space. $p_\text{min}$ indicates the minimum possible number of players successfully arriving at the position of the airdrop, while $p_\text{max}$ indicates the maximum possible number.

## 样例

### 样例输入 #1
```
3
3 2
1 2
2 1
3 5
3 3
2 1
2 5
4 3
2 3
1 3
4 3
```
### 样例输出 #1
```
1 3
0 3
2 2
```
## 提示

We now explain the first sample test case.

To obtain the answer of $p_\text{min} = 1$, one should consider $x_0 = 3$. The following table shows the position of each player at the end of each time unit when $x_0 = 3$.

![](https://cdn.luogu.com.cn/upload/image_hosting/itsnfe48.png)

To obtain the answer of $p_\text{max} = 3$, one should consider $x_0 = 2$. The following table shows the position of each player at the end of each time unit when $x_0 = 2$.

![](https://cdn.luogu.com.cn/upload/image_hosting/hvseoyfc.png)
## 题目翻译

### 题目描述
有 $n$ 个玩家在一个平面直角坐标系中打 PUBG. 此时一个空投落在了 $(x_0, y_0)$ 处.

现在场上还剩 $n$ 个「存活」的玩家. 从空投落地的时刻起, 每一个时刻执行如下操作 :

1. 移动阶段

对于每个「存活」的玩家 :
- 如果其不在 $(x_0, y_0)$ :
  - 向空投方向沿 $x$ 轴**或** $y$ 轴方向移动 $1$ 个单位距离, 使得移动后位置与 $(x_0, y_0)$ 的曼哈顿距离尽可能小. 
  - 在上一条规则的基础上, 如果有多种符合要求的移动方式, 则优先沿 $y$ 轴移动.
- 如果其在 $(x_0, y_0)$, 则不进行操作.

2. 战斗阶段

移动阶段结束后, 如果**除 $(x_0, y_0)$ 外**任意一点存在超过 $1$ 名玩家, 则将这一点所有玩家判定为「死亡」并移出游戏.

---

可以证明, 经过足够多次操作后, 所有仍「存活」的玩家都会处在 $(x_0, y_0)$ 位置.

给定 $y_0$, 求 $x_0$ 取任意整数值时, 最终「存活」玩家数的最大值与最小值.

### 输入输出格式与数据范围
首先给出一个整数 $T$, 表示数据组数. 接下来对于每组数据 :

第一行给出两个正整数 $n, y_0$, 意义如题所述.

接下来 $n$ 行, 每行两个正整数 $x, y$, 表示 $n$ 个玩家的坐标.

$n$ 和所有点的坐标值都不超过 $10^5$, 且保证不存在两名玩家初始处在同一位置. 单个测试点的 $\sum n \le 10^6$.

**注意 : $x_0$ 可以取 $0$ 或负值, 且不受坐标值不超过 $10^5$ 的限制.**

对于每组数据, 输出一行 2 个空格分开的整数, 分别表示最终「存活」玩家数的最大值和最小值.

Translated by @[Ja50nY0un9](/user/363302).


---

---
title: "[ICPC 2018 Qingdao R]  Sub-cycle Graph"
layout: "post"
diff: 省选/NOI-
pid: P9896
tag: ['图论', '2018', 'O2优化', '组合数学', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R]  Sub-cycle Graph
## 题目描述

Given an undirected simple graph with $n$ ($n \ge 3$) vertices and $m$ edges where the vertices are numbered from 1 to $n$, we call it a ``sub-cycle`` graph if it's possible to add a non-negative number of edges to it and turn the graph into exactly one simple cycle of $n$ vertices.

Given two integers $n$ and $m$, your task is to calculate the number of different sub-cycle graphs with $n$ vertices and $m$ edges. As the answer may be quite large, please output the answer modulo $10^9+7$.

Recall that

- A simple graph is a graph with no self loops or multiple edges;
- A simple cycle of $n$ ($n \ge 3$) vertices is a connected undirected simple graph with $n$ vertices and $n$ edges, where the degree of each vertex equals to 2;
- Two undirected simple graphs with $n$ vertices and $m$ edges are different, if they have different sets of edges;
- Let $u < v$, we denote $(u, v)$ as an undirected edge connecting vertices $u$ and $v$. Two undirected edges $(u_1, v_1)$ and $(u_2, v_2)$ are different, if $u_1 \ne u_2$ or $v_1 \ne v_2$.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ (about $2 \times 10^4$), indicating the number of test cases. For each test case:

The first and only line contains two integers $n$ and $m$ ($3 \le n \le 10^5$, $0 \le m \le \frac{n(n-1)}{2}$), indicating the number of vertices and the number of edges in the graph.

It's guaranteed that the sum of $n$ in all test cases will not exceed $3 \times 10^7$.

## 输出格式

For each test case output one line containing one integer, indicating the number of different sub-cycle graphs with $n$ vertices and $m$ edges modulo $10^9+7$.

## 样例

### 样例输入 #1
```
3
4 2
4 3
5 3
```
### 样例输出 #1
```
15
12
90
```
## 提示

The 12 sub-cycle graphs of the second sample test case are illustrated below.

![](https://cdn.luogu.com.cn/upload/image_hosting/636hie1e.png)
## 题目翻译

### 题目描述

对于一个有 $n(n\ge3)$ 个点和 $m$ 条边的无向简单图，其中点的编号为 $1$ 到 $n$。如果加非负整数条边能使这个图是变为 $n$ 个点的简单环，我们称这个是一个 “半环” 图。

给定两个整数 $n$ 和 $m$，你的任务是计算有多少个**不同的** $n$ 个点，$m$ 条边的 “半环” 图。考虑到答案会很大，请将答案模 $10^{9} + 7$ 的结果输出。

定义

- 一个简单图是指一个没有自环和重边的图；
- $n$ 个点的 “简单环” 是指任意一个有 $n$ 个点和 $n$ 条边的无向简单连通图，其中所有点的度均为 $2$；
- 如果两个有着 $n$ 个点和 $m$ 条边的无向简单图是不同的，那么它们具有着不同的边集；
- 现在有两个点 $u$ 和 $v(u < v)$，记 $(u,v)$ 表示连接 $u,v$ 两点的无向边。两条无向边 $(u_1,v_1)$ 和 $(u_2,v_2)$ 如果是不同的，那么 $u_1\ne u_2$ 或 $v_1\ne v_2$。

### 输入格式

此题有多组数据。

第一行有一个整数 $T$（约为 $2\times 10^{4}$），指测试用例的数量。对于每组数据：

一组数据只有一行，两个整数 $n$ 和 $m$（$3 \le n \le 10^{5}$，$0\le m \le \frac{n(n-1)}{2}$），表示图的点数和边数。

$n$ 的总和不超过 $3\times 10^{7}$。

### 输出格式

对于每组数据，你只需要输出一行表示答案。


---

