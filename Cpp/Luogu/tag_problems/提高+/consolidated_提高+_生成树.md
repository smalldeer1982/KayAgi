---
title: "「CROI · R2」落月摇情"
layout: "post"
diff: 提高+/省选-
pid: P10768
tag: ['贪心', '二分', '堆', '洛谷原创', 'Special Judge', 'O2优化', '生成树', '构造', '洛谷月赛']
---
# 「CROI · R2」落月摇情
## 题目背景


>昨夜闲潭梦落花，\
可怜春半不还家。\
>江水流春去欲尽，\
江潭落月复西斜。
>
>斜月沉沉藏海雾，\
碣石潇湘无限路。\
>不知乘月几人归，\
落月摇情满江树。

## 题目描述

小烟是住在月亮上的仙女。为了和人间保持联系，小烟在江边种了一棵树。每当月光透过枝叶洒在江面上，形成特定的图案时，小烟就能与那个人产生心灵感应。为了让形成的图案更加美观，小烟用魔法让树的枝条互相交错成他喜欢的样子。你可以认为这棵树是一个**有 $n$ 个节点、$m$ 条边且无重边、无自环的无向连通图**。

某次小烟出差回到月亮上，发现这棵树上所有的枝条都被破坏了。为了快速恢复和人间的联系，小烟需要施加魔法将 $n$ 个节点重新连接起来。施加魔法生成一条边的代价与这条边对月光投影的影响程度有关。由于小烟忘记了原本树的形态，所以她希望花费最小的代价将这棵树恢复到任意一个可能的原先形态。也就是说，她需要这 $n$ 个节点之间形成一张有 $m$ 条边且无重边、无自环的无向连通图。

考虑到你不是仙女，很难计算每条边对投影的影响程度，善良的小烟给出了一个简单的计算方法：给你每个点的影响程度 $a_i$，则用魔法生成一条边 $(u,v)$ 的代价为 $a_u\times a_v$。请你帮小烟找到一组花费代价最小的施加魔法的方案。

**形式化地**，给出 $n$ 个点，每个点有点权 $a_i$，你需要构造一张有 $m$ 条边，且无重边、无自环的无向图，使得这 $n$ 个点连通。设边 $(u,v)$ 的权值为 $a_u\times a_v$，你需要最小化图中所有边的权值和。
## 输入格式

输入共两行。

第一行两个非负整数 $n,m$。

第二行 $n$ 个由空格隔开的整数 $a_i$。
## 输出格式

输出 $m+1$ 行。

第一行一个整数 $ans$，表示你构造的图中，所有边的权值和。

接下来的 $m$ 行每行两个正整数 $u,v$，表示你构造的图中存在一条边 $u,v$。你需要保证 $u\neq v$，且不存在两个无序二元组 $(u,v)$ 相同，且所有输出能表示一张 $n$ 个点的连通图。**如有多解，输出任意一组合法解即可**。
## 样例

### 样例输入 #1
```
4 5
1 2 -2 -3
```
### 样例输出 #1
```
-13
1 2
1 3
1 4
2 3
2 4
```
### 样例输入 #2
```
6 5
1 2 4 5 0 -3
```
### 样例输出 #2
```
-36
1 6
2 6
3 6
4 6
5 6
```
## 提示

**【Special Judge】**

本题采用 Special Judge。只要你输出的图满足无重边、无自环且连通，同时其边权和与你输出的答案一致且输出的答案与标准答案一致，你就可以通过对应的测试点。

需要注意的是，请确保你的输出符合输出格式中的要求，否则你得到的结果可能不确定。

本题开启子任务依赖。你可以得到一个子任务对应的分数，当且仅当你通过了当前子任务，同时你也通过了当前子任务依赖的所有子任务。具体的依赖情况见“数据范围”部分的表格。

**【数据范围】**

对于所有数据，满足 $1\leq n\leq 10^6$，$n-1\leq m\leq \min(10^6,\frac{n(n-1)}{2})$，$0\leq |a_i|\leq 10^6$。

本题开启捆绑测试、开启子任务依赖。

|  子任务编号  | $n \le$ | $m \le$ | 特殊性质 | 分值 |子任务依赖|
| :----------: | :-----: | :--------------: | :------------: | :-----: | :-----: |
|$1$ |$7$ | $21$ | 无 |$10$| 无 |
| $2$ | $16$ |  $120$ | 无 |$15$| $1$ |
|  $3$  | $1000$ | $3\times 10^5$| 无 |$15$|$1,2$|
| $4$ | $2\times 10^5$ | $3\times 10^5$ | 保证 $a_i$ 为非负整数 |$15$|无|
| $5$ | $2\times 10^5$ | $3\times 10^5$ | 保证 $m=n-1$ |$10$|无|
| $6$ | $2\times 10^5$ | $3\times 10^5$ |  无  | $15$|$1,2,3$|
| $7$ | $10^6$ | $10^6$ |  无  | $20$|$1,2,3,6$|

**【样例解释】**

- 对于样例一，构造出的图如下图所示。边权和为 $2+-2+-4+-3+-6=-13$。该样例的构图方式是唯一的。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/nd1clogk.png)

- 对于样例二，构造出的图如下图所示。边权和为 $-3+-6+-12+-15+0=-36$。该样例还存在其它正确的构图方式，比如你可以把边 $(5,6)$ 改为边 $(5,3)$。
  
   ![](https://cdn.luogu.com.cn/upload/image_hosting/6fm944rj.png)


---

---
title: "[JOI 2025 Final] 缆车 / Mi Teleférico"
layout: "post"
diff: 提高+/省选-
pid: P11664
tag: ['并查集', '树状数组', '2025', '生成树', '扫描线', 'JOI（日本）']
---
# [JOI 2025 Final] 缆车 / Mi Teleférico
## 题目背景


译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T3。

Mi Teleférico 指的是连接玻利维亚拉巴斯市（La Paz）及埃尔阿尔托市（El Alto）的缆车系统。

## 题目描述


给定一张 $N$ 个点 $M$ 条边的有向无环图。这张有向图的边是由 $P$ 个公司（编号 $1\sim N$）修建的，每条边恰好被一个公司修建。

节点标号 $1\sim N$，第 $i$（$1\le i\le M$）条边由节点 $A_i$ 指向节点 $B_i$，且是公司 $C_i$ 修建的。这里，保证 $A_i\lt B_i$。

有 $Q$ 个询问，每个询问给定区间 $[L,R]$（$1\le L\le R\le P$）和钱数 $X$。目标是从 $1$ 号点只经过编号 $\in [L,R]$ 的公司修建的边，可以到达其他任意一个节点。

为此，可以选择一个新的区间 $[l',r']$（$1\le l'\le r'\le P$），将 $[L,R]$ 变为 $[l',r']$。这会花费 $|L'-l'|+|R-r'|$ 的代价，这个操作**至多只能执行一次**。操作的代价必须不大于钱数 $X$。

对于每个询问，判断是否能够达成目标。
## 输入格式


如下所示：


> $N$ $M$ $P$\
> $A_1$ $B_1$ $C_1$\
> $A_2$ $B_2$ $C_2$\
> $\vdots$\
> $A_M$ $B_M$ $C_M$\
> $Q$\
> $L_1$ $R_1$ $X_1$\
> $L_2$ $R_2$ $X_2$\
> $\vdots$\
> $L_Q$ $R_Q$ $X_Q$
## 输出格式


对于第 $i$ 个询问，如果可以达成，输出一行一个 $\texttt{Yes}$；否则输出一行一个 $\texttt{No}$。

## 样例

### 样例输入 #1
```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
4
3 7 0
5 6 0
3 4 0
1 9 0
```
### 样例输出 #1
```
Yes
No
No
Yes
```
### 样例输入 #2
```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
3
5 6 10
3 4 1
7 8 3
```
### 样例输出 #2
```
Yes
No
Yes
```
### 样例输入 #3
```
3 1 1000000000
1 2 6
1
1 1000000000 1000000000
```
### 样例输出 #3
```
No
```
### 样例输入 #4
```
5 9 2000
2 3 1814
2 3 457
1 2 1226
3 4 1354
1 5 1050
1 2 1725
2 3 1383
1 5 1626
1 4 1795
5
850 1872 128
82 428 1217
487 924 573
1639 1926 202
202 420 25
```
### 样例输出 #4
```
Yes
Yes
Yes
Yes
No
```
## 提示


### 样例解释

#### 样例 $1$ 解释

第 $1$ 个询问中，$[3,7]$ 已经可以满足条件，无需进行操作。

第 $2$ 个询问中，$[5,6]$ 不满足条件，然后无法进行任何操作，所以无法达成目标。


该样例满足所有子任务的限制。


#### 样例 $2$ 解释

第 $1$ 个询问中，选择 $l'=1,r'=5$，花费 $5$ 的代价可以达成目标。

该样例满足子任务 $2,3,5\sim 7$ 的限制。


#### 样例 $3$ 解释
该样例满足子任务 $6,7$ 的限制。



#### 样例 $4$ 解释

该样例满足子任务 $5\sim 7$ 的限制。



### 数据范围

- $2\le N\le 3\times 10^5$。
- $1\le M\le 3\times 10^5$。
- $1\le P\le 10^9$。
- $1\le A_i\lt B_i\le N$（$1\le i\le M$）。
- $1\le C_i\le P$（$1\le i\le M$）。
- $1\le Q\le 4\times 10^5$。
- $1\le L_i\le R_i\le P$（$1\le i\le Q$）。
- $0\le X_i\le 10^9$（$1\le i\le Q$）。
- 输入的都是整数。

### 子任务

1. （7pts）$N,M,Q\le 50$，$X_i=0$（$1\le i\le Q$）。
2. （8pts）$P\le 10$。
3. （11pts）$P\le 100$。
4. （23pts）$P\le 3\times 10^5$，$X_i=0$（$1\le i\le Q$）。
5. （9pts）$P\le 3\times 10^5$。
6. （22pts）$N,M\le 8,000$。
7. （20pts）无额外限制。


---

---
title: "[TOIP2024] 棲息地分配"
layout: "post"
diff: 提高+/省选-
pid: P11829
tag: ['2024', 'Special Judge', '生成树', '台湾']
---
# [TOIP2024] 棲息地分配
## 题目描述

有 $n$ 隻貓活動於某個地區，每隻貓各有其棲息地，編號為 $1$ 到 $n$。棲息地之間有 $m$ 條道路連接，道路總數不超過 $2n-4$。第 $i$ 條道路連接第 $a_i$ 個棲息地和第 $b_i$ 個棲息地，貓可以沿著這些道路在棲息地之間**雙向**移動，且不會有兩條不同的道路連接著同一對棲息地。有 $3$ 個動保團體要接管此地區，請你協助將這 $n$ 個棲息地分配給這 $3$ 個團體，滿足以下要求：

- 每個棲息地僅由 $1$ 個團體管理，且每個團體需要管理至少 $1$ 個棲息地。每個團體所屬的棲息地之間不一定要連通。
- 為了方便管理，每個團體會移除由該團體負責的棲息地之間的道路。換句話說，若有一條道路連接的兩個棲息地被分配到同一個團體，該道路會被移除。
- 這些道路移除後，剩餘的道路不可以形成「環」，以免貓可能會繞著環奔跑，讓工作人員難以捉捕。也就是說，不可以存在一個兩兩相異的棲息地序列 $v_1,v_2,\ldots, v_k$​，滿足 $k \ge 3$，且對於所有 $1\le i < k$，棲息地 $v_i$​ 和棲息地 $v_{i+1}$​ 都有一條未被移除的道路連接、同時 $v_k$​ 和 $v_1$​ 也有一條未被移除的道路連接。

舉例，有 $5$ 個棲息地，道路連接如下圖所示
## 样例

### 样例输入 #1
```
1
5 6
1 2
2 3
3 4
4 5
5 3
4 2
```
### 样例输出 #1
```
3 3 4 5
1 1
1 2
```
### 样例输入 #2
```
2
5 4
1 2
1 3
3 4
3 5
5 4
1 2
2 3
1 3
4 5
```
### 样例输出 #2
```
2 1 2
1 3
2 4 5
3 1 2 3
1 4
1 5
```


---

---
title: "[GCJ 2017 #3] Good News and Bad News"
layout: "post"
diff: 提高+/省选-
pid: P13176
tag: ['搜索', '图论', '2017', 'Special Judge', '生成树', 'Google Code Jam']
---
# [GCJ 2017 #3] Good News and Bad News
## 题目描述

You would like to get your $F$ friends to share some news. You know your friends well, so you know which of your friends can talk to which of your other friends. There are $P$ such one-way relationships, each of which is an ordered pair $(A_i, B_i)$ that means that friend $A_i$ can talk to friend $B_i$. It does not imply that friend $B_i$ can talk to friend $A_i$; however, another of the ordered pairs might make that true.

For every such existing ordered pair $(A_i, B_i)$, you want friend $A_i$ to deliver some news to friend $B_i$. In each case, this news will be represented by an integer value; the magnitude of the news is given by the absolute value, and the type of news (good or bad) is given by the sign. The integer cannot be 0 (or else there would be no news!), and its absolute value cannot be larger than $F^2$ (or else the news would be just *too* exciting!). These integer values may be different for different ordered pairs.

Because you are considerate of your friends' feelings, for each friend, the sum of the values of all news given *by* that friend must equal the sum of values of all news given *to* that friend. If no news is given by a friend, that sum is considered to be 0; if no news is given to a friend, that sum is considered to be 0.

Can you find a set of news values for your friends to communicate such that these rules are obeyed, or determine that it is impossible?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line with two integers $F$ and $P$: the number of friends, and the number of different ordered pairs of friends. Then, $P$ more lines follow; the $i$-th of these lines has two different integers $A_i$ and $B_i$ representing that friend $A_i$ can talk to friend $B_i$. Friends are numbered from 1 to $F$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is either IMPOSSIBLE if there is no arrangement satisfying the rules above, or, if there is such an arrangement, $P$ integers, each of which is nonzero and lies inside $[-F^2, F^2]$. The $i$-th of those integers corresponds to the $i$-th ordered pair from the input, and represents the news value that the first friend in the ordered pair will communicate to the second. The full set of values must satisfy the conditions in the problem statement.

If there are multiple possible answers, you may output any of them.
## 样例

### 样例输入 #1
```
5
2 2
1 2
2 1
2 1
1 2
4 3
1 2
2 3
3 1
3 4
1 2
2 3
3 1
2 1
3 3
1 3
2 3
1 2
```
### 样例输出 #1
```
Case #1: 1 1
Case #2: IMPOSSIBLE
Case #3: -1 -1 -1
Case #4: 4 -4 -4 8
Case #5: -1 1 1
```
## 提示

**Sample Explanation**

The sample output shows one possible set of valid answers. Other valid answers are possible.

In Sample Case #1, one acceptable arrangement is to have friend $1$ deliver news with value $1$ to friend $2$, and vice versa.

In Sample Case #2, whatever value of news friend $1$ gives to friend $2$, it must be nonzero. So, the sum of news values given to friend $2$ is not equal to zero. However, friend $2$ cannot give any news and so that value is $0$. Therefore, the sums of given and received news for friend $2$ cannot match, and the case is IMPOSSIBLE.

In Sample Case #3, each of friends $1, 2$, and $3$ can deliver news with value $-1$ to the one other friend they can talk to — an unfortunate circle of bad news! Note that there is a friend 4 who does not give or receive any news; this still obeys the rules.

In Sample Case #4, note that $-5\ 5\ 5\ -10$ would not have been an acceptable answer, because there are $3$ friends, and $|-10| > 3^2$.

In Sample Case #5, note that the case cannot be solved without using at least one negative value.

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq A_i \leq F$, for all $i$.
- $1 \leq B_i \leq F$, for all $i$.
- $A_i \neq B_i$, for all $i$. (A friend does not self-communicate.)
- $(A_i, B_i) \neq (A_j, B_j)$, for all $i \neq j$. (No pair of friends is repeated within a test case in the same order.)

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~20~~ 5 seconds.
- $2 \leq F \leq 4$.
- $1 \leq P \leq 12$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~40~~ 10 seconds.
- $2 \leq F \leq 1000$.
- $1 \leq P \leq 2000$.


---

---
title: "[GCJ 2008 Finals] Bridge Builders"
layout: "post"
diff: 提高+/省选-
pid: P13489
tag: ['2008', '生成树', 'Google Code Jam']
---
# [GCJ 2008 Finals] Bridge Builders
## 题目描述

The king wants bridges built and he wants them built as quickly as possible. The king owns an $N$ by $M$ grid of land with each cell separated from its adjacent cells by a river running between them and he wants you to figure out how many man-hours of work it will take to build enough bridges to connect every island. Some cells are actually lakes and need not have a bridge built to them.

Some of the islands are forests where trees are abundant. Located in the top left corner is the base camp, which is always a forest.

A bridge can only be built between two islands if they are vertically or horizontally adjacent, and one of the islands is accessible from the base camp through the bridges that are already built.

The number of man-hours it takes to build a bridge is the number of bridges the builders have to cross to get from the nearest forest to the island you're building to, including the bridge being built. Builders can only walk between two islands if there is already a bridge between them.

The king has already ensured that there is at least one way to connect all the islands.

Write a program that, given a map of the islands, will output the minimum number of man-hours required to connect all islands.

Consider this example. A green tile indicates a forest, gray indicates an empty island, and blue indicates water.

![](https://cdn.luogu.com.cn/upload/image_hosting/9sul5t7c.png)

One optimal solution starts out by building the following bridges from the base camp forest.

![](https://cdn.luogu.com.cn/upload/image_hosting/7m79cx0m.png)

This has a cost of $1 + 2 + 1 + 2 + 3 + 4 = 13$

Now since the forest at row $3$, column $3$ is connected to base camp, we can build bridges from there. One optimal solution connects the rest of the islands with bridges built from this forest.

![](https://cdn.luogu.com.cn/upload/image_hosting/1b4rn4fo.png)

This has a cost of $2 + 1 + 2 + 1 + 2 + 3 = 11$. This brings the total cost to $24$ which is the optimal solution.
## 输入格式

The first line of the input contains an integer $T$, the number of test cases. $T$ test cases follow. Each test case will begin with $N$, the number of rows, and $M$, the number of columns, on one line separated by a space. $N$ rows follow that contain exactly $M$ characters each. A 'T' indicates an island with a forest, a '#' indicates an island, and a '.' indicates water.

## 输出格式

A single line containing "Case #$X$: $Y$", where $X$ is the 1-based case number, and $Y$ is the minimum number of man-hours needed to connect all islands.
## 样例

### 样例输入 #1
```
3
2 2
T.
T#
4 4
T##.
##.#
.#T#
####
5 5
T#T.#
..#.#
#.###
###.#
T###T
```
### 样例输出 #1
```
Case #1: 2
Case #2: 24
Case #3: 49
```
## 提示

**Limits**

- $1 \leq T \leq 50$
- $2 \leq N \leq 30$
- $2 \leq M \leq 30$
- The top left cell will always be a 'T'
- It will be possible to connect all islands through bridges

**Small dataset (8 Pts, Test set 1 - Visible)**

- There will be at most 2 forests in the grid including the base camp.

**Large dataset (17 Pts, Test set 2 - Hidden)**

- There will be no limit on the number of forests in the grid.



---

---
title: "Charlie的云笔记序列"
layout: "post"
diff: 提高+/省选-
pid: P1370
tag: ['动态规划 DP', '递推', '生成树']
---
# Charlie的云笔记序列
## 题目背景

Charlie 是 oiinhand 的忠实粉丝。他有使用 oih 云笔记记录自己的题解的习惯。只有一点一滴的积累才能留下自己的足迹。

oih 云笔记有什么特点吗？

oih 的站长 soha 表示，目前 oih2 的云笔记功能比较简陋，但是正在开发 oih3 中的新版云笔记功能将是世界上最适合 oier 的储藏笔记的工具。

首先，新版云笔记支持 markdown 功能，并且可以实时预览，插入公式图片都不是问题。实时自动保存，不用担心突然断电啊文档消失，而且不管在哪里都可以看！

其次，可以一键生成题解模板摘要，不用各种复制粘贴了，超省事！

再者，云笔记可以给其他同学分享自己的笔记，共同进步。写完了笔记，还可以一键向洛谷投稿呢！

然而 Charlie 最喜欢的功能是 oih 的题目收藏。现在他收藏了一系列题目，但是觉得不过瘾所以正在玩弄这个功能。
## 题目描述

某天，Charlie 将收藏的题目抽象为一个序列。$a=[a_1,a_2,a_3,\cdots,a_{n-1},a_n]$。

设 $a[l:r]$ 表示序列 ${a_i}$ 第 $l$ 个数到第 $r$ 个数之间的子串，其中 $1 \le l \le r \le n$。形式化地，$a[l:r]={a_l,a_{l+1},a_{l+2},\cdots,a_{r-1},a_r}$。比如说，$a=[9,8,0,3,2,1]$，那么 $a[2:5]=[8,0,3,2]$。

Charlie 对序列 $[a_i]$ 定义了一个函数 $F(l,r)$，表示序列 $a[l:r]$ 的本质不同的子序列个数。特别地，一个空序列也被当作一个本质不同的子序列。

序列 $a[l:r]$ 的子序列定义为 $[a_{i_1},a_{i_2},a_{i_3},\cdots,a_{i_{k-1}},a_{i_k}]$，其中 $l \le i_1<i_2<i3<\cdots<i_{k-1}<i_k \le r$。比如说，$a=[9,8,0,3,2,1]$，那么 $[8,3,2]$ 是 $a[2:5]=[8,0,3,2]$ 的一个子序列。

长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$ 被称作本质不同的，当且仅当 $n\neq m$，或存在 $i$，使得 $a_i \neq b_i$。反之，则称这 $2$ 个序列是本质相同的。比如说，$[9,8]$ 和 $[9,7]$ 是本质不同的，$[9,8]$ 和 $[9,8,7]$ 也是本质不同的，而 $[9,8]$ 和 $[9,8]$ 是本质相同的。

举个例子，设 $a=[1,9,9,8,0,3,2,1]$，那么 $F(1,3)=6$，因为 $a[1:3]=[1,9,9]$ 有 $6$ 个子序列：$[],[1],[9],[1,9],[9,9],[1,9,9]$。

现在 Charlie 想知道，$\sum _{1\le l\le r\le n} F(l,r)$ 的值是多少。由于这个数可能很大，请输出它对 $998244353$（$7\times 17\times 2^23+1$，一个质数）取模后的结果。
## 输入格式

第一行一个整数 $n$，表示序列 $a$ 的长度。

第二行包括 $n$ 个整数，表示 $a_1,a_2,a_3,\cdots a_{n-1},a_n$。
## 输出格式

一行，一个整数表示 $\sum _{1\le l\le r\le n} F(l,r)$ 的值对 $998244353$ 取模后的结果。

## 样例

### 样例输入 #1
```
8

1 9 9 8 0 3 2 1
```
### 样例输出 #1
```
814
```
## 提示

- 对于 $10\%$ 的数据，$1\le n \le 10$；
- 对于 $30\%$ 的数据，$1 \le n \le 100$；
- 对于 $50\%$ 的数据，$1\le n \le 1000$，$0 \le a_i \le 10^5$；
- 对于 $100\%$ 的数据，$1 \le n \le 10^5$，$|a_i| \le 10^9$。

oiinhand 3.0 正在开发中。

这将是 oiers 都需要的工具，它不仅集合了全网所有大型 OJ 的资源（题目、题解）而且针对用户还可以将自己在其他 OJ 评测过的代码储存下来，并且有超贴心的云笔记功能，帮助大家最大效率练习。

soha 借此地征求意见，有奖哦！<http://www.wenjuan.com/s/M7fqIv/>


---

---
title: "[NOIP 2013 提高组] 货车运输"
layout: "post"
diff: 提高+/省选-
pid: P1967
tag: ['图论', '贪心', '2013', '倍增', '并查集', 'NOIP 提高组', '生成树', '最近公共祖先 LCA']
---
# [NOIP 2013 提高组] 货车运输
## 题目背景

NOIP2013 提高组 D1T3
## 题目描述

A 国有 $n$ 座城市，编号从 $1$ 到 $n$，城市之间有 $m$ 条双向道路。每一条道路对车辆都有重量限制，简称限重。  

现在有 $q$ 辆货车在运输货物， 司机们想知道每辆车在不超过车辆限重的情况下，最多能运多重的货物。

## 输入格式

第一行有两个用一个空格隔开的整数 $ n,m$，表示 A 国有 $ n$ 座城市和 $m$ 条道路。  

接下来 $m$ 行每行三个整数 $x, y, z$，每两个整数之间用一个空格隔开，表示从 $x $ 号城市到 $ y $ 号城市有一条限重为 $z$ 的道路。    
注意： $x \neq y$，两座城市之间可能有多条道路 。

接下来一行有一个整数 $q$，表示有 $q$ 辆货车需要运货。

接下来 $q$ 行，每行两个整数 $x,y$，之间用一个空格隔开，表示一辆货车需要从 $x$ 城市运输货物到 $y$ 城市，保证 $x \neq y$

## 输出格式

共有 $q$ 行，每行一个整数，表示对于每一辆货车，它的最大载重是多少。  
如果货车不能到达目的地，输出 $-1$。

## 样例

### 样例输入 #1
```
4 3
1 2 4
2 3 3
3 1 1
3
1 3
1 4
1 3
```
### 样例输出 #1
```
3
-1
3
```
## 提示

对于 $30\%$ 的数据，$1 \le n < 1000$，$1 \le m < 10,000$，$1\le q< 1000$；

对于 $60\%$ 的数据，$1 \le n < 1000$，$1 \le m < 5\times 10^4$，$1 \le q< 1000$；

对于 $100\%$ 的数据，$1 \le n < 10^4$，$1 \le m < 5\times 10^4$，$1 \le q< 3\times 10^4 $，$0 \le z \le 10^5$。



---

---
title: "曼哈顿距离最小生成树"
layout: "post"
diff: 提高+/省选-
pid: P2076
tag: ['线段树', '树状数组', 'Special Judge', '生成树']
---
# 曼哈顿距离最小生成树
## 题目背景

题目修改自 [Library Checker](https://judge.yosupo.jp/problem/manhattanmst)，及[数据生成器 / 校验器来源](https://github.com/yosupo06/library-checker-problems/tree/master/geo/manhattanmst)。

请注意原题所有下标从 $0$ 开始（$0$-indexed），本题所有下标从 $1$ 开始（$1$-indexed）。
## 题目描述

给定平面上的 $n$ 个点 $(x_1,y_1),(x_2,y_2),\ldots,(x_n,y_n)$。

考虑一个有 $n$ 个结点的完全图，对于 $1\le u,v\le n(u\ne v)$，结点 $u,v$ 之间有一条权值为 $|x_u-x_v|+|y_u-y_v|$ 的边。

请求出该图的最小生成树。
## 输入格式

第一行输入一个整数 $n$ 表示点的个数。

接下来 $n$ 行，第 $i$ 行输入两个整数 $(x_i,y_i)$，表示第 $i$ 个点的坐标。
## 输出格式

第一行包含一个整数 $x$ 表示最小生成树的边权之和。

接下来 $(n-1)$ 行，第 $i$ 行包含两个整数 $(u_i,v_i)$，表示最小生成树中的一条边。

**如果有多解，你可以输出任意一种。**
## 样例

### 样例输入 #1
```
6
3 8
4 9
2 1
10 5
4 9
2 0
```
### 样例输出 #1
```
21
5 2
6 3
1 2
3 1
4 1
```
## 提示

对于 $20\%$ 的数据，$1\le n\le 1000$。

对于 $100\%$ 的数据，$1\le n\le 2\times 10^5$，$0\le x_i,y_i\le 10^9$。


---

---
title: "[USACO14MAR] Sabotage G"
layout: "post"
diff: 提高+/省选-
pid: P2115
tag: ['2014', '二分', 'USACO', '生成树']
---
# [USACO14MAR] Sabotage G
## 题目描述

Farmer John's arch-nemesis, Farmer Paul, has decided to sabotage Farmer John's milking equipment!

The milking equipment consists of a row of N (3 <= N <= 100,000) milking machines, where the ith machine produces M\_i units of milk (1 <= M\_i <= 10,000).  Farmer Paul plans to disconnect a contiguous block of these machines -- from the ith machine up to the jth machine (2 <= i <= j <= N-1); note that Farmer Paul does not want to disconnect either the first or the last machine, since this will make his plot too easy to discover.  Farmer Paul's goal is to minimize the average milk production of the remaining machines.  Farmer Paul plans to remove at least 1 cow, even if it would be better for him to avoid sabotage entirely.

Fortunately, Farmer John has learned of Farmer Paul's evil plot, and he is wondering how bad his milk production will suffer if the plot succeeds.  Please help Farmer John figure out the minimum average milk production of the remaining machines if Farmer Paul does succeed.

农夫约翰的头号敌人保罗决定破坏农民约翰的挤奶设备。挤奶设备排成一行，共N（3<= N <=100000）台挤奶机，其中第i个台挤奶机生产M\_i单位（1 <= M\_i<=10,000）的牛奶。


保罗计划切断一段连续的挤奶机，从第i台挤奶机到第j台挤奶机（2<= i<= j<= N-1）。注意，他不希望断开第一台或最后一台挤奶机，因为这将会使他的计划太容易被发现。保罗的目标是让其余机器的平均产奶量最小。保罗计划除去至少1台挤奶机。

请计算剩余机器的最小平均产奶量。

## 输入格式

第 1 行：一个整数 N。

第 2 到 N+1 行：第 i+1 行包含一个整数 M\_i。

## 输出格式

第 1 行： 一个实数， 表示平均牛奶产量的最小值， 保留三位小数 （四舍五入）。

## 样例

### 样例输入 #1
```
5
5
1
7
8
2
```
### 样例输出 #1
```
2.667
```
## 提示

【样例说明】

移去 7 和 8，剩下 5, 1, 2，平均值为 8/3。

【数据规模和约定】

对于 30%的数据，N <= 1,000。

对于 50%的数据，N <= 10,000。

对于 100%的数据，3 <= N <= 100,000，1 <= M\_i <= 10,000。

【时空限制】

0.2s/128M



---

---
title: "[SCOI2012] 滑雪"
layout: "post"
diff: 提高+/省选-
pid: P2573
tag: ['图论', '2012', '四川', '各省省选', '排序', '生成树']
---
# [SCOI2012] 滑雪
## 题目描述

a180285 非常喜欢滑雪。他来到一座雪山，这里分布着 $m$ 条供滑行的轨道和 $n$ 个轨道之间的交点（同时也是景点），而且每个景点都有一编号 $i\space (1 \le i \le n)$ 和一高度 $h_i$。  

a180285 能从景点 $i$ 滑到景点 $j$ 当且仅当存在一条 $i$ 和 $j$ 之间的边，且 $i$ 的高度**不小于** $j$。与其他滑雪爱好者不同，a180285 喜欢用最短的滑行路径去访问尽量多的景点。如果仅仅访问一条路径上的景点，他会觉得数量太少。

于是 a18028 5拿出了他随身携带的时间胶囊。这是一种很神奇的药物，吃下之后可以立即回到上个经过的景点（不用移动也不被认为是 a180285 滑行的距离）。  

请注意，这种神奇的药物是可以连续食用的，即能够回到较长时间之前到过的景点（比如上上个经过的景点和上上上个经过的景点）。 现在，a180285站在 $1$ 号景点望着山下的目标，心潮澎湃。他十分想知道在不考虑时间胶囊消耗的情况下，以最短滑行距离滑到尽量多的景点的方案（即满足经过景点数最大的前提下使得滑行总距离最小）。你能帮他求出最短距离和景点数吗？

## 输入格式

输入的第一行是两个整数 $n,m$。
接下来一行有 $n$ 个整数 $h_i$，分别表示每个景点的高度。

接下来 $m$ 行，表示各个景点之间轨道分布的情况。每行三个整数 $u,v,k$，表示编号为 $u$ 的景点和编号为 $v$ 的景点之间有一条长度为 $k$ 的轨道。

## 输出格式

输出一行，表示 a180285 最多能到达多少个景点，以及此时最短的滑行距离总和。

## 样例

### 样例输入 #1
```
3 3 
3 2 1 
1 2 1 
2 3 1 
1 3 10 
```
### 样例输出 #1
```
3 2
```
## 提示

【数据范围】   
对于 $ 30\% $ 的数据，$ 1 \le n \le 2000 $；   
对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $。


对于所有的数据，保证 $ 1 \le m \le 10^6 $ , $ 1 \le h_i \le 10^9 $ ，$ 1 \le k_i \le 10^9 $。



---

---
title: "Explorer"
layout: "post"
diff: 提高+/省选-
pid: P2632
tag: ['图论', '生成树']
---
# Explorer
## 题目背景

提示：本题数据较水，通过本题不代表程序/做法完全正确。
## 题目描述

给出两条直线，上面分别有 $n,m$ 个点，求这 $n+m$ 个点组成的最小生成树。

## 输入格式

输入包括 $5$ 行。 

第一行为 $n$ 和 $m$。

第二行为四个整数 $AX,AY,BX,BY$。

第三行为四个整数 $CX,CY,DX,DY$。 

第四行为 $n$ 个实数，代表在第一条直线上的n个点。对于某个点，用一个实数 $t$ 来表示该点的坐标为 $(AX\times t + BX \times (1 - t), AY \times t + BY \times (1 - t))$。 

第五行为 $m$ 个实数，代表第二条直线上的 $m$ 个点，表示方法同上。

## 输出格式

一行一个实数，为其最小生成树长度，四舍五入至三位小数。

## 样例

### 样例输入 #1
```
4 4 
0 0 10 10 
0 10 10 0 
0.1 0.3 0.6 0.8 
0.1 0.3 0.6 0.8
```
### 样例输出 #1
```
19.638
```
## 提示

$n,m \le 100000$，$AX,AY,BX,BY,CX,CY,DX,DY$ 的绝对值均小于等于 $10^5$，$0 \le t \le 1$。


------------
2024/2/8 添加一组 hack 数据。


---

---
title: "[USACO14MAR] Counting Friends G"
layout: "post"
diff: 提高+/省选-
pid: P3104
tag: ['图论', '2014', '二分', 'USACO', '生成树']
---
# [USACO14MAR] Counting Friends G
## 题目描述

Farmer John's N cows (2 <= N <= 500) have joined the social network "MooBook".

Each cow has one or more friends with whom they interact on MooBook.  Just for fun, Farmer John makes a list of the number of friends for each of his cows, but during the process of writing the list he becomes distracted, and he includes one extra number by mistake (so his list contains N+1 numbers, instead of N numbers as he intended).

Please help Farmer John figure out which numbers on his list could have been the erroneous extra number.

FJ又有n(1<=n<=500)头奶牛都有一个或一个以上的朋友。FJ记录每头牛的朋友数，但他傻不小心混入了一个错的数字，请找出。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..2+N: Line i+1 contains the number of friends for one of FJ's cows, or possibly the extra erroneous number.

## 输出格式

\* Line 1: An integer K giving the number of entries in FJ's list that could be the extra number (or, K=0 means that there is no number on the list whose removal yields a feasible pairing of friends).

\* Lines 2..1+K: Each line contains the index (1..N+1) within the input ordering of a number of FJ's list that could potentially be the extra number -- that is, a number that can be removed such that the remaining N numbers admit a feasible set of

friendships among the cows.  These lines should be in sorted order.

## 样例

### 样例输入 #1
```
4 
1 
2 
2 
1 
3 

```
### 样例输出 #1
```
3 
1 
4 
5 

```
## 提示

Farmer John has 4 cows.  Two cows have only 1 friend each, two cows have 2 friends each, and 1 cow has 3 friends (of course, one of these numbers is extra and does not belong on the list).


Removal of the first number in FJ's list (the number 1) gives a remaining list of 2,2,1,3, which does lead to a feasible friendship pairing -- for example, if we name the cows A..D, then the pairings (A,B), (A,C), (A,D), and (B,C) suffice, since A has 3 friends, B and C have 2 friends, and D has 1 friend.  Similarly, removing the other "1" from FJ's list also works, and so does removing the "3" from FJ's list.  Removal of either "2" from FJ's list does not work -- we can see this by the fact that the sum of the remaining numbers is odd, which clearly prohibits us from finding a feasible pairing.



---

---
title: "[USACO16FEB] Fenced In P"
layout: "post"
diff: 提高+/省选-
pid: P3141
tag: ['贪心', '2016', 'USACO', '生成树']
---
# [USACO16FEB] Fenced In P
## 题目背景

*本题和 [金组同名题目](/problem/P6171) 在题意上一致，唯一的不同是数据范围。*
## 题目描述

Farmer John 意识到他的奶牛最近患上了一种恐惧症（害怕过于开阔的空间）。为了减少放牧的恐惧，FJ 决定在牧场中建一些水平和竖直方向的栅栏来将牧场分成若干个小区域。

整个牧场是一个矩形，两个角的坐标分别为 $(0,0)$ 和 $(A,B)$。FJ 在 $a_1,\ldots ,a_n$ 这 $n$ 个两两不同的位置建造了竖直方向的栅栏，每个栅栏从 $(a_i,0)$ 到 $(a_i,B)$；FJ 在 $b_1,\ldots ,b_m$ 这 $m$ 个两两不同的位置建造了水平方向的栅栏，每个栅栏从 $(0,b_i)$ 到 $(A,b_i)$。竖直方向的栅栏和水平方向的栅栏两两相交，将整个牧场分割成 $(n+1)(m+1)$ 个区域。

不幸的是，FJ 忘记了在栅栏上开门，奶牛都只能被困在一个个的小区域里！他想通过去掉一些栅栏来解决这个问题。他一次可以选择两个相邻的区域，将隔离这两个区域的栅栏去掉。FJ 的目标是让奶牛能够抵达牧场的任意一个地方。

这是一个例子：

```plain
+---+--+
|   |  |
+---+--+
|   |  |
|   |  |
+---+--+
```

去掉一些栅栏后的效果是这样的：

```plain
+---+--+
|      |
+---+  +
|      |
|      |
+---+--+
```

为了降低工程量，FJ 当然希望拆除的栅栏长度最短。
## 输入格式

第一行四个整数 $A,B,n,m$，保证 $1 \leq n,m \leq 2.5 \times 10^5$，$1 \leq A,B \leq 10^9$。

接下来 $n$ 行，第 $i$ 行一个整数 $a_i$，保证 $0 \lt a_i \lt A$。

接下来 $m$ 行，第 $i$ 行一个整数 $b_i$，保证 $0 \lt b_i \lt B$。
## 输出格式

输出拆除栅栏的最小长度。**答案需要用 64 位带符号整数存储。**
## 样例

### 样例输入 #1
```
15 15 5 2
2
5
10
6
4
11
3
```
### 样例输出 #1
```
44
```


---

---
title: "小猴打架"
layout: "post"
diff: 提高+/省选-
pid: P4430
tag: ['数学', '生成树', '线性代数']
---
# 小猴打架
## 题目描述

一开始森林里面有 $N$ 只互不相识的小猴子，它们经常打架，但打架的双方都必须不是好朋友。每次打完架后，打架的双方以及它们的好朋友就会互相认识，成为好朋友。经过 $N-1$ 次打架之后，整个森林的小猴都会成为好朋友。   
现在的问题是，总共有多少种不同的打架过程。   
比如当 $N=3$ 时，就有 $\{1-2,1-3\}\{1-2,2-3\}\{1-3,1-2\}\{1-3,2-3\}\{2-3,1-2\}\{2-3,1-3\}$ 六种不同的打架过程。 

## 输入格式

一个整数 $N$。 
## 输出格式

一行，方案数 $\bmod 9999991$。 
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
96
```
## 提示

$50\%$ 的数据 $N\le 10^3$。  
$100\%$ 的数据 $N\le10^6$。 


---

---
title: "[USACO01OPEN] Earthquake"
layout: "post"
diff: 提高+/省选-
pid: P4951
tag: ['2001', 'USACO', '生成树']
---
# [USACO01OPEN] Earthquake
## 题目描述

一场地震把约翰家的牧场摧毁了， 坚强的约翰决心重建家园。 约翰已经重建了 $n$ 个牧场，现在他希望能修建一些道路把它们连接起来。研究地形之后，约翰发现可供修建的道路有 $m$ 条。碰巧的是，奶牛们最近也成立一个工程队，专门从事修复道路。而然，奶牛们很有经济头脑，如果无利可图，它们是不会干的。

奶牛们关注的是挣钱速度，即总利润和总施工时间的比值。约翰和奶牛达成了协议，奶牛负责修建道路，将所有牧场连通，而约翰需要支付 $f$ 元。每条道路都有自己的施工时间和建造成本。连接两个相同的牧场的道路可能有多条。保证所有的牧场必定是可连通的，不过也有可能一些道路的建造成本之和会超过 $f$。  

请帮助奶牛们选择修复哪些道路，才能使单位时间的利润最大？

## 输入格式

第一行三个整数 $n,m,f$。

第二行到第 $m+1$ 行，第 $i+1$ 行表示第 $i$ 条道路的信息。每行有四个整数 $u_i,v_i,c_i,t_i$， $u_i$ 和 $v_i$ 表示这条道路连接的牧场编号，$c_i$ 表示修建道路的成本，$t_i$ 表示道路修建所需要的时间。
## 输出格式

第一行，一个保留四位小数的浮点数，表示奶牛们能挣到的最大单位时间利润，如果奶牛们无钱可赚，则输出`0.0000`。
## 样例

### 样例输入 #1
```
5 5 100
1 2 20 5
1 3 20 5
1 4 20 5
1 5 20 5
2 3 23 1
```
### 样例输出 #1
```
1.0625
```
## 提示

#### 样例输入输出 1 解释

奶牛们可以选择连通最后四条道路，则总时间为 $16$，总成本为 $83$，所以单位利润为 $\dfrac{17}{16}=1.0625$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证
- $1 \leq n \leq 400$，$1 \leq m \leq 10000$，$1 \leq f \leq 2 \times 10^9$。
- $1 \leq u_i,v_i \leq n$，$1 \leq c_i,t_i \leq 2 \times 10^9$。


---

---
title: "[USACO21OPEN] Portals G"
layout: "post"
diff: 提高+/省选-
pid: P7528
tag: ['USACO', '2021', '图论建模', '生成树']
---
# [USACO21OPEN] Portals G
## 题目描述

Bessie 位于一个由 $N$ 个编号为 $1\dots N$ 的结点以及 $2N$ 个编号为 $1\cdots 2N$ 的传送门所组成的网络中。每个传送门连接两个不同的结点 $u$ 和 $v$（$u≠v$）。可能有多个传送门连接同一对结点。

每个结点 $v$ 与四个不同的传送门相连。与 $v$ 相连的传送门列表由 $p_v=[p_{v,1},p_{v,2},p_{v,3},p_{v,4}]$ 给出。

你的当前位置可以用有序对（当前结点，当前传送门）表示；即一个有序对 $(v,p_{v,i})$
，其中 $1\le v\le N$ 以及 $1\le i\le 4$。你可以使用以下任一操作来改变你的当前位置：

- 1. 由穿过当前传送门来改变当前结点。
- 2. 改变当前传送门。在每一个结点上，列表的前两个传送门是配对的，后两个传送门也是配对的。也就是说，如果你的当前位置是 $(v,p_{v,2})$，你可以转而使用传送门 $(v,p_{v,1})$，反之亦然。类似地，如果你的当前位置是 $(v,p_{v,3})$，你可以转而使用传送门 $(v,p_{v,4})$，反之亦然。没有其他改变传送门的方式（例如，你**不能**从传送门 $p_{v,2}$ 转去传送门 $p_{v,4}$ ）。

总共有 $4N$ 个不同的位置。不幸的是，并不一定每一个位置都可以从另外的每一个位置经过一系列操作而到达。所以，以 $c_v$ 哞尼的代价，你可以以任意顺序重新排列与 $v$ 相邻的传送门列表。在此之后，列表中的前两个传送门互相配对，同时后两个传送门也互相配对。

例如，如果你将与 $v$ 相邻的传送门以 $[p_{v,3},p_{v,1},p_{v,2},p_{v,4}]$ 的顺序重新排列，这意味着如果你位于结点 $v$ ，
- 如果你当前位于传送门 $p_{v,1}$ ，你可以转而使用传送门 $p_{v,3}$，反之亦然。
- 如果你当前位于传送门 $p_{v,2}$ ，你可以转而使用传送门 $p_{v,4}$，反之亦然。
你不再能够从传送门 $p_{v,1}$
转至传送门 $p_{v,2}$，或从传送门 $p_{v,3}$ 转至 $p_{v,4}$ ，反之亦然。

计算修改这一网络使得每一个位置都可以从另外的每一个位置到达所需要花费的哞尼的最小数量。输入保证存在至少一种修改网络的合法方式。 
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行每行描述一个结点。第 $v+1$ 行包含五个空格分隔的整数 $c_v,p_{v,1},p_{v,2},p_{v,3},p_{v,4}$。

输入保证对于每一个 $v$ ，$p_{v,1},p_{v,2},p_{v,3},p_{v,4}$ 各不相同，且每个传送门出现在**恰好两个结点**的邻接表中。 
## 输出格式

输出一行，包含修改这一网络使得每一个位置都可以从另外的每一个位置到达所需要花费的哞尼的最小数量。 
## 样例

### 样例输入 #1
```
5
10 1 4 8 9
11 1 2 5 6
12 9 10 2 3
3 4 3 6 7
15 10 8 7 5
```
### 样例输出 #1
```
13
```
## 提示

#### 样例解释

重新排列结点 $1$ 和 $4$ 的邻接表就已足够。这需要总计 $c_1+c_4=13$ 哞尼。我们可以使 $p_1=[1,9,4,8]$ 以及 $p_4=[7,4,6,3]$。 

#### 数据范围与约定

$2\le N\le 10^5$，$1\le c_v\le 10^3$。


---

---
title: "[THUPC 2022 初赛] 最小公倍树"
layout: "post"
diff: 提高+/省选-
pid: P8207
tag: ['2022', 'O2优化', '图论建模', '生成树', 'THUPC']
---
# [THUPC 2022 初赛] 最小公倍树
## 题目背景

听说有人嫌题面描述都太长了。
## 题目描述

对于任意 $V\subset\mathbb{N}^*$，$|V|<+\infty$，构造一张无向完全图 $G=(V,E)$，其中 $(u, v)$ 的边权为 $u,v$ 的最小公倍数 $\mathrm{lcm}(u, v)$。称 $G$ 的最小生成树为 $V$ 的最小公倍树（LCT, Lowest Common Tree）。

现在给出 $L, R$，请你求出 $V={L, L+1, \cdots, R}$ 的最小公倍树 $LCT(V)$。
## 输入格式

输入仅一行，包括两个正整数 $L, R$。
## 输出格式

输出一个正整数，表示 $LCT(V)$ 的边权和。
## 样例

### 样例输入 #1
```
3 12
```
### 样例输出 #1
```
126
```
### 样例输入 #2
```
6022 14076
```
### 样例输出 #2
```
66140507445
```
### 样例输入 #3
```
13063 77883
```
### 样例输出 #3
```
3692727018161
```
### 样例输入 #4
```
325735 425533
```
### 样例输出 #4
```
1483175252352926
```
## 提示

【样例解释】

其中一种最小公倍树上的边为 $(3, 4), (3, 5), (3, 6), (3, 7), (4, 8), (3, 9), (5, 10), (3, 11), (3, 12)$。

【数据范围】

对于 $100%$ 的数据，保证 $1\le L\le R\le 10^6$，且 $R-L\le 10^5$。


---

---
title: "[蓝桥杯 2023 省 A] 网络稳定性"
layout: "post"
diff: 提高+/省选-
pid: P9235
tag: ['图论', '贪心', '并查集', '2023', '生成树', '最近公共祖先 LCA', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 A] 网络稳定性
## 题目描述

有一个局域网，由 $n$ 个设备和 $m$ 条物理连接组成，第 $i$ 条连接的稳定性为 $w_i$。

对于从设备 $A$ 到设备 $B$ 的一条经过了若干个物理连接的路径，我们记这条路径的稳定性为其经过所有连接中稳定性最低的那个。

我们记设备 $A$ 到设备 $B$ 之间通信的稳定性为 $A$ 至 $B$ 的所有可行路径的稳定性中最高的那一条。

给定局域网中的设备的物理连接情况，求出若干组设备 $x_i$ 和 $y_i$ 之间的通信稳定性。如果两台设备之间不存在任何路径，请输出 $-1$。
## 输入格式

输入的第一行包含三个整数 $n,m,q$，分别表示设备数、物理连接数和询问数。

接下来 $m$ 行，每行包含三个整数 $u_i,v_i,w_i$，分别表示 $u_i$ 和 $v_i$ 之间有一条稳定性为 $w_i$ 的物理连接。

接下来 $q$ 行，每行包含两个整数 $x_i,y_i$，表示查询 $x_i$ 和 $y_i$ 之间的通信稳定性。
## 输出格式

输出 $q$ 行，每行包含一个整数依次表示每个询问的答案。
## 样例

### 样例输入 #1
```
5 4 3
1 2 5
2 3 6
3 4 1
1 4 3
1 5
2 4
1 3
```
### 样例输出 #1
```
-1
3
5
```
## 提示

【评测用例规模与约定】

对于 $30 \%$ 的评测用例，$n,q \leq 500$，$m \leq 1000$；

对于 $60 \%$ 的评测用例，$n,q \leq 5000$，$m \leq 10000$；

对于所有评测用例，$2 \leq n,q \leq 10^5$，$1 \leq m \leq 3 \times 10^5$，$1 \leq u_i,v_i,x_i,y_i \leq n$，$
1 \leq w_i \leq 10^6$，$u_i \neq v_i$，$x_i \neq y_i$。


---

---
title: "「yyOI R1」youyou 的军训"
layout: "post"
diff: 提高+/省选-
pid: P9638
tag: ['并查集', 'Kruskal 重构树', 'O2优化', '生成树']
---
# 「yyOI R1」youyou 的军训
## 题目背景

在 youyou 的班上，身高可能是一个敏感的话题。
## 题目描述

youyou 的班上一共有 $n$ 位同学，$m$ 对朋友，第 $i$ 对朋友关系对于身高有一个敏感值 $k_i$，敏感值可能会改变。

我们定义两位同学如果互为**朋友**，那么必然存在某对关系，将两位同学**直接**相连。

我们定义两位同学如果互为**好友**，那么必然存在直接或间接的关系，将两位同学相连。

例如存在关系 $(1,2)$ 和 $(2,3)$，那么，$1$ 与 $2$ 是朋友，但 $1$ 与 $3$ 就是好友。

现在，马上就要军训了，同学们要去领军训的服装，如果一位同学领到了尺码为 $p$ 的服装，所有同学会与朋友关系敏感值小于 $p$ 的朋友断交。即对于所有的朋友关系，若其敏感值小于 $p$，那么该朋友关系就会断开。不过在下一位同学领到服装时，所有**之前**的断开的朋友关系会恢复。

由于军训领服装是一个复杂的过程，而 youyou 对此十分感兴趣，所以给出 $q$ 次操作，且一共有三种操作:

- 操作 $1$，形如 `1 x`，表示有一位同学领到尺码为 $x$ 的服装。

- 操作 $2$，形如 `2 x`，表示询问第 $x$ 位同学还有多少位好友（包括自己）。

- 操作 $3$，形如 `3 x y`，表示第 $x$ 对朋友的敏感值变为 $y$，特别地，**敏感值的相对大小不会变化$^*$**（详情见下方），同时原来已经断开的关系不会恢复。

**注意：好友跟朋友是两个概念，朋友一定是好友，但好友不一定是朋友。**

$^*$：相对大小不会变化，指对于当前所有的敏感值而言，修改后的敏感值与原来的敏感值**排名相同**。

例如，若原来所有对朋友之间敏感值是 $\{1,2,3,5,6\}$，$3$ 的排名为 $3$，因此 $3$ 只能修改为 $3,4$ 中的一个，这样才能保证排名不变，即相对大小位置不会变换。
## 输入格式

第一行，输入三个正整数 $n,m,q$。

后面 $m$ 行，给定 $m$ 对朋友关系，对于第 $i$ 行给定三个正整数 $x_i,y_i,k_i$。

最后 $q$ 行，给定 $q$ 次操作。对于每次操作，给定一个正整数为 $op$，即操作类型。

当 $op=1$ 时，再给定一个正整数 $x$，表示有一位同学领到尺码为 $x$ 的服装；

当 $op=2$ 时，再给定一个正整数 $x$，表示一次询问；

当 $op=3$ 时，再给定两个正整数 $x,y$，表示一次修改。
## 输出格式

对于每次询问操作，输出一个 $x$ 表示询问的同学还有几位**好友**（**包括自己**）。保证对于每一个测试点，都会有一个询问操作。
## 样例

### 样例输入 #1
```
4 3 3
1 2 156
1 4 42
2 3 0
1 26963
3 3 40
2 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
7 6 7
1 2 292
1 3 274
1 4 221
1 5 156
3 4 42
3 6 40
1 30
3 4 50
2 6
3 3 250
3 1 298
1 280
2 1
```
### 样例输出 #2
```
6
2
```
## 提示


## 样例解释 #1

如图所示，这是初始的关系图。

![](https://cdn.luogu.com.cn/upload/image_hosting/68hzm5mr.png)

第一次操作为：有一位同学领到尺码为 $26963$ 的服装，这样，图中所有的边都会断开。

下一次操作：第三对朋友即边 $(2,3)$ 的权变为 $40$。

下一次操作：询问同学 $4$ 的好友数量，因为没有任何存在的边，因此答案为 $1$。
 
## 数据范围
| 测试点编号 | $n$ | $q$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1,2$ | $\le 10$ | $\le 4 \times 10^5$ | 无 |
| $3$ | $\le 10^3$ | $\le 10^3$ | 无 |
| $4$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $3$ |
| $5,6$ | $\le 10^5$ | $\le 10^3$ | 无 |
| $7$ | $\le 10^5$ | $\le 4 \times 10^5$ | 没有操作 $1$ |
| $8,9,10$ | $\le 4 \times 10^5$ | $\le 4 \times 10^5$ | 无 |

用 $c_i$ 表示询问中同学领到服装尺码的大小，$e_i$ 表示修改后敏感值的大小。

对于 $100\%$ 的数据，$1 \le n,m,q,x_i,y_i \le 4  \times  10^5$，$1 \le k_i,c_i,e_i \le 1 \times 10^9$，$m\le \min\{\frac{n(n-1)}{2},4 \times 10^5\}$。

同时数据保证在任何时刻，所有对朋友关系之间的敏感值**互不相同**。

**请注意常数因子对时间和空间产生的影响。**


---

