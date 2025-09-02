---
title: "[GCJ 2022 #3] Win As Second	"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13000
tag: ['2022', '交互题', 'Special Judge', '构造', 'SG 函数', 'Google Code Jam']
---
# [GCJ 2022 #3] Win As Second	
## 题目描述

Ueli and Vreni are playing a game. The game's board is a tree with $\mathbf{N}$ vertices, all initially colored blue. They alternate turns, with Ueli going first. In each turn, a player must choose a blue vertex, together with any subset (possibly none or all) of its blue neighbors, and color all those vertices red. If at the start of a players' turn, all vertices are red, then that player loses the game and the other player wins the game.

In the example game below, Ueli colored vertex 3 red in their first turn. Then, Vreni chose vertex 2 for their turn and colored both it and its neighbor (vertex 1) red. Because all vertices are now red, Ueli loses and Vreni wins.

![](https://cdn.luogu.com.cn/upload/image_hosting/xw0xc7is.png)

Ueli and Vreni have noticed that it is much easier for Ueli to win this game because he has the first turn. Therefore they have adopted the following procedure: first, Ueli chooses an integer $\mathbf{N}$. Then, Vreni chooses any tree with $\mathbf{N}$ vertices. And then they start playing as described above, with Ueli taking the first turn.

Vreni is hopeful that being able to choose the tree can help her overcome the disadvantage of going second. Can you demonstrate how Vreni can win games in this setup?

### Interactive Protocol

This is an interactive problem. You should make sure you have read the information in the Interactive Problems section of our FAQ.

Initially, your program should read a single line containing an integer, $\mathbf{T}$, the number of test cases. Then, $\mathbf{T}$ test cases must be processed.

For each test case, your program must first read a line containing a single integer $\mathbf{N}$, the number of vertices that Ueli has chosen. Then, your program must output $\mathbf{N}-1$ lines describing the edges of the tree Vreni should choose. The nodes of the tree are numbered 1 through $\mathbf{N}$. Each line must represent a distinct edge of the tree with 2 integers between 1 and $\mathbf{N}$: the two vertices the edge connects. The edges must represent a tree. The two integers within a line may be in either order, and the $\mathbf{N}-1$ lines themselves may be in any order.

After that, your program must read a line containing a single integer $\mathbf{M}$, the number of games that you need to play on this tree. These games are played independently; in other words, all vertices of the tree are blue at the start of each game.

For each of the $\mathbf{M}$ games, you need to process some number of exchanges until the game is over. Each exchange consists of a turn from each player.

For each exchange, your program must read two lines describing Ueli's turn first. The first of those lines will contain an integer $\mathbf{K}$, denoting the number of blue vertices to be colored red. The second of those lines will contain $\mathbf{K}$ distinct integers $\mathbf{A}_1, \mathbf{A}_2, \ldots, \mathbf{A}_\mathbf{K}$ describing the blue vertices to be colored red. $\mathbf{K}$ will be at least 1, and each $\mathbf{A}_i$ will be between 1 and $\mathbf{N}$, inclusive. Vertices $\mathbf{A}_2, \mathbf{A}_3, \ldots, \mathbf{A}_\mathbf{K}$ will all be neighbors of vertex $\mathbf{A}_1$.

After that, your program must output Vreni's choice for their turn in the same format: the first line with the number of blue vertices to be colored red, followed by the second line with the numbers of those vertices, in such an order that all vertices except the first one are neighbors of the first one.

If all vertices are red after Vreni's turn, it means that Vreni has won and this game is over. The next game starts immediately if there is one. If this was the last game for this test case, then the next test case starts immediately if there is one. If this was the last test case, the judge will send no further input to your program, and the program must send no further output.

On the other hand, if all vertices are red after Ueli's move, it means that Vreni has lost and therefore your program did not pass the test case. In this case, instead of starting a new exchange by printing the last move that colors all remaining blue vertices red, the judge will print a single number -1 and will not print any further output, and will not process any further games or test cases.

If the judge receives an invalidly formatted or invalid line (like outputting an unexpected number of integers, or integers out of range, or outputting a set of edges that do not form a tree, or trying to color a vertex that is already red, or trying to color a vertex that is not a neighbor of the first vertex colored in this turn) from your program at any moment, the judge will also print a single number -1 and will not print any further output. If your program continues to wait for the judge after receiving a -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.

The judge is deterministic. In other words, if you make two attempts that print the same numbers, you will get the same inputs from the judge. However, of course the judge can make different moves in different games on the same tree.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
2
3



1
1
3


4



2
3
2 1 3


2
2 3


-1
```
### 样例输出 #1
```



1 2
1 3



2
1 2

1 2
2 3
2 4



1
4


1
1
```
## 提示

Note that the sample interaction does not satisfy the constraints of either test set, as its $\mathbf{N}$ values are too small. It is only presented to clarify the input and output format.

Below is an illustration of Case #2, Game #1 at the beginning and after each turn:

![](https://cdn.luogu.com.cn/upload/image_hosting/cccz3vlj.png)

Below is an illustration of Case #2, Game #2 at the beginning and after each turn:

![](https://cdn.luogu.com.cn/upload/image_hosting/0b2qkj8q.png)

**Limits**

- $1 \leq \mathbf{M} \leq 50.$

**Test Set 1 (13 Pts, Visible Verdict)**

- $\mathbf{T}=1$.
- $\mathbf{N}=30$.

**Test Set 2 (Hidden Verdict)**

- $1 \leq \mathbf{T} \leq 10.$
- $31 \leq \mathbf{N} \leq 40.$
- No two test cases use the same value of $\mathbf{N}$.


---

---
title: "[HAOI2015] 数组游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3179
tag: ['动态规划 DP', '博弈论', '2015', '河南', '各省省选', 'SG 函数']
---
# [HAOI2015] 数组游戏
## 题目描述

有一个长度为 $n$ 的数组，甲乙两人在上面进行这样一个游戏：首先，数组上有一些格子是白的，有一些是黑的。然后两人轮流进行操作。

每次操作选择一个白色的格子，假设它的下标为 $x$。接着，选择一个大小在 $1\ldots \dfrac{n}{x}$ 之间的整数 $k$，然后将下标为 $x,2\times x,\ldots ,k\times x$ 的格子都进行颜色翻转。不能操作的人输。

现在甲（先手）有一些询问。每次他会给你一个数组的初始状态，你要求出对于这种初始状态他是否有必胜策略。
## 输入格式

第一行包含一个整数 $n$，表示数组的长度。

第二行包含一个整数 $k$，表示询问的个数。

接下来 $2\times k$ 行，每两行表示一次询问。

在这两行中，第一行一个正整数 $w$，表示数组中有多少个格子是白色的，第二行则有 $w$ 个 $1$ 到 $n$ 之间的正整数，表示白色格子的对应下标。
## 输出格式

对于每个询问，输出一行一个字符串，若先手必胜输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
3
2
2
1 2
2
2 3
```
### 样例输出 #1
```
Yes
No
```
## 提示

#### 样例输入输出 1 解释

在第一个询问中，甲选择点 $1$，然后将格子 $1\times 1$ 和 $2\times 1$ 翻过来即可。

第二个询问中，无论甲选择哪个点，都只能翻掉一个格子。乙只需翻掉另一个格子就行了。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^9$， $1\leq k, w \leq 100$ ，不会有格子在同一次询问中多次出现。


---

---
title: "[HNOI2014] 江南乐"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3235
tag: ['递推', '2014', '湖南', 'O2优化', 'SG 函数']
---
# [HNOI2014] 江南乐
## 题目描述

小A是一个名副其实的狂热的回合制游戏玩家。在获得了许多回合制游戏的世界级奖项之后，小A有一天突然想起了他小时候在江南玩过的一个回合制游戏。

游戏的规则是这样的，首先给定一个数F，然后游戏系统会产生T组游戏。每一组游戏包含N堆石子，小A和他的对手轮流操作。每次操作时，操作者先选定一个不小于2的正整数M (M是操作者自行选定的，而且每次操作时可不一样)，然后将任意一堆数量不小于F的石子分成M堆，并且满足这M堆石子中石子数最多的一堆至多比石子数最少的一堆多1（即分的尽量平均，事实上按照这样的分石子万法，选定M和一堆石子后，它分出来的状态是固定的）。当一个玩家不能操作的时候，也就是当每一堆石子的数量都严格小于F时，他就输掉。(补充：先手从N堆石子中选择一堆数量不小于F的石子分成M堆后，此时共有N+M-1)堆石子，接下来小A从这N+M-1堆石子中选择一堆数量不小于F的石子，依此类推。

小A从小就是个有风度的男生，他邀请他的对手作为先手。小A现在想要知道，面对给定的一组游戏，而且他的对手也和他一样聪明绝顶的话，究竟谁能够获得胜利？

## 输入格式

输入第一行包含两个正整数T和F，分别表示游戏组数与给定的数。    接下来T行，每行第一个数N表示该组游戏初始状态下有多少堆石子。之后N个正整数，表示这N堆石子分别有多少个。

## 输出格式

输出一行，包含T个用空格隔开的0或1的数，其中0代表此时小A（后手）会胜利，而1代表小A的对手（先手）会胜利。

## 样例

### 样例输入 #1
```
4 3
1 1
1 2
1 3
1 5
```
### 样例输出 #1
```
0 0 1 1
```
## 提示

对于100%的数据，T<100，N<100，F<100000，每堆石子数量<100000。

以上所有数均为正整数。



---

