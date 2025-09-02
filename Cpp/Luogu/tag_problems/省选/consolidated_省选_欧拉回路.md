---
title: "BZOJ3706 反色刷"
layout: "post"
diff: 省选/NOI-
pid: P10777
tag: ['欧拉回路']
---
# BZOJ3706 反色刷
## 题目描述

给定 $n$ 个点，$m$ 条边的无向图，边有黑白两种颜色。现在你可以进行若干次回路反色操作，每次操作从任意点出发，每经过一条边，将其颜色反转，最后回到起点。判断能否通过若干次操作，使这张图所有边都变成白色。

因为某种原因，边的颜色是会改变的，即你相当于需要支持以下两种操作：
- `1 x` 将第 $x$ 条边反色（边的编号为 $0\sim m-1$）；
- `2` 求出最少操作次数；
## 输入格式

第一行两个整数 $n,m$ 表示这张图有 $n$ 个点 $m$ 条边。

接下来 $m$ 行，每行 $3$ 个整数 $u,v,c$ 表示一条无向边和这条边的颜色，其中 $0$ 为白色，$1$ 为黑色。

接下来一个整数 $q$，表示有 $q$ 个操作。接下来 $q$ 行操作，描述如上。
## 输出格式

对于每个询问，输出一行一个整数，表示最少需要的反色操作次数。如果没有合法方案输出 $-1$。
## 样例

### 样例输入 #1
```
6 6
1 2 1
2 3 1
1 3 1
4 5 1
5 6 1
4 6 1
14
2
1 0
2
1 1
1 2
2
1 3
1 4
1 5
2
1 3
1 4
1 5
2
```
### 样例输出 #1
```
2
-1
1
0
1
```
## 提示

数据保证，$1\leq n,m,q \leq 1000000$，$c < 2$，没有重边自环。


---

---
title: "[COTS 2022] 帽子 Šeširi"
layout: "post"
diff: 省选/NOI-
pid: P10873
tag: ['2022', 'Special Judge', 'O2优化', '欧拉回路', '构造', 'COCI（克罗地亚）', 'Ad-hoc']
---
# [COTS 2022] 帽子 Šeširi
## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D1T3。$\texttt{3s,0.5G}$。

喜欢小圆！


## 题目描述

$N$ 个 OIer 头上戴着红色或者白色的帽子。每个人只能看到别人的帽子颜色，他们会根据别人的帽子颜色猜测自己头上帽子的颜色。

他们想要构造一组猜测策略，满足以下条件：

- 设有 $b$ 人戴了白色帽子，其中**至少**有 $\lfloor\frac{b}{2}\rfloor$ 人猜对自己帽子的颜色。
- 设有 $c$ 人戴了红色帽子，其中**至少**有 $\lfloor\frac{c}{2}\rfloor$ 人猜对自己帽子的颜色。

请帮助他们找到一种策略，使得在 $2^N$ 种可能的情况中都满足条件。
## 输入格式

一行一个整数 $N$。
## 输出格式

输出 $N$ 行，每行一个长度为 $2^{N-1}$ 的字符串，由 $\texttt{B},\texttt{C}$ 组成。

第 $i$ 行的字符串描述了第 $i$ 个 OIer 的策略。具体地说：

- 定义 $f(S)$ 为：将所有长度为 $(N-1)$ 的由 $\texttt{B},\texttt{C}$ 组成的字符串按照字典序排序后，$S$ 的排名。
- 记 $x$ 为第 $i$ 行输出的字符串，$s_i\in \{\texttt{B},\texttt{C}\}$ 为第 $i$ 个 OIer 头上戴的帽子颜色。其中 $\texttt{B}$ 是白色（克罗地亚语「bijela」），$\texttt{C}$ 是红色（克罗地亚语「crvena」）。
- 记 $y=\overline{s_1s_{2}\cdots s_{i-1}s_{i+1}\cdots s_n}$。注意左边是高位。
- 第 $i$ 个 OIer 会猜测的颜色为 $x_{f(y)}$。

可参阅【样例解释】。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
BC
CC
```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
BBCC
BCBC
BBCC
```
## 提示


#### 样例解释

以样例 $2$ 为例。

当 $s=\texttt{CCC}$ 时，对于第 $1$ 个 OIer，$x=\texttt{BBCC}$，$y=\texttt{CC}$。显然 $f(y)=4$，所以他会猜测 $x_4=\texttt{C}$。

#### 计分方式

| 测试点编号 | $N=$ | 分值 |
|:-----:|:------:|:-------:|
| $1$  | $4$  | $7$  |
| $2$  | $5$  | $7$  |
| $3$  | $6$  | $7$  |
| $4$  | $7$  | $7$  |
| $5$  | $8$  | $7$  |
| $6$  | $9$  | $7$  |
| $7$  | $10$  | $7$  |
| $8$  | $11$  | $7$  |
| $9$  | $12$  | $7$  |
| $10$  | $13$  | $7$  |
| $11$  | $14$  | $6$  |
| $12$  | $15$  | $6$  |
| $13$  | $16$  | $6$  |
| $14$  | $17$  | $6$  |
| $15$  | $18$  | $6$  |




---

---
title: "[GCJ 2022 Finals] Slide Parade"
layout: "post"
diff: 省选/NOI-
pid: P13003
tag: ['2022', '网络流', 'Special Judge', '欧拉回路', '二分图', 'Google Code Jam']
---
# [GCJ 2022 Finals] Slide Parade
## 题目描述

Gooli is a huge company that owns $\mathbf{B}$ buildings in a hilly area, numbered 1 through $\mathbf{B}$. Six years ago, Gooli built slides that allowed employees to go from one building to another. Each slide allows anyone to go from the slide's origin building to the slide's destination building, but not the other way around. Gooli's CEO is very proud of their slides and wants to organize a parade through the slides. She has tasked Melek, Gooli's Head of Transportation and a problem-solving enthusiast, with designing the parade's route.

![](https://cdn.luogu.com.cn/upload/image_hosting/njzcunb7.png)

She has some requirements for the parade route in mind:

* It must start and end at building 1, where her office is located.
* It must visit each building the same number of times. Being in building 1 at the start of the route does not count as a visit.
* It must use each slide at least once.
* It must have at most $10^6$ steps.

Given the layout of buildings and slides, help Melek find a route that satisfies all of the CEO's requirements, if one exists.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{B}$ and $\mathbf{S}$: the number of buildings and slides, respectively. Then, $\mathbf{S}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{U}_i$ and $\mathbf{V}_i$, indicating that the $i$-th slide goes from building $\mathbf{U}_i$ to building $\mathbf{V}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1). If there is no route that fulfills all the requirements, $y$ must be `IMPOSSIBLE`. If there is, $y$ must be an integer between $\mathbf{S} + 1$ and $10^6 + 1$, inclusive, representing the length of one such route you want to exhibit. In that case, output another line containing $y$ integers $z_1$ $z_2$ $\dots$ $z_y$, where $z_j$ is the $j$-th building in your proposed route. Notice that $z_1 = z_y = 1$ and that each building must appear the same number of times among the $z_j$, except for building 1, which appears exactly one extra time.
## 样例

### 样例输入 #1
```
5
2 2
2 1
1 2
3 4
2 3
1 2
3 2
1 3
3 6
1 2
1 3
2 1
2 3
3 1
3 2
3 4
1 2
2 1
1 3
3 1
4 6
1 2
1 4
2 3
3 2
3 4
4 1
```
### 样例输出 #1
```
Case #1: 7
1 2 1 2 1 2 1
Case #2: IMPOSSIBLE
Case #3: 7
1 2 3 1 3 2 1
Case #4: IMPOSSIBLE
Case #5: 9
1 4 1 2 3 2 3 4 1
```
## 提示

**Sample Explanation**

In Sample Case #1, another acceptable parade route is one that goes from building 1 to building 2 and then back for a total of 2 steps.

![](https://cdn.luogu.com.cn/upload/image_hosting/udzlxptm.png)

In Sample Case #2, there are no slides leading to building 1, so no valid parade can exist.

![](https://cdn.luogu.com.cn/upload/image_hosting/pp27u0fj.png)

In Sample Case #3, the parade route the sample output exhibits goes through each building twice.

![](https://cdn.luogu.com.cn/upload/image_hosting/e7pjon34.png)

Sample Case #4 is pictured below.

![](https://cdn.luogu.com.cn/upload/image_hosting/ff4gi295.png)

Sample Case #5 is the one illustrated in the problem statement. In the parade route in the sample output, the slides from 2 to 3 and from 4 to 1 are used twice, but the rest of the slides are used only once each.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{U}_i \leq \mathbf{B}$, for all $i$.
- $1 \leq \mathbf{V}_i \leq \mathbf{B}$, for all $i$.
- $\mathbf{U}_i \neq \mathbf{V}_i$, for all $i$.
- $(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{U}_j, \mathbf{V}_j)$, for all $i \neq j$.

**Test Set 1 (11 Pts, Visible Verdict)**

- Time limit: 10 seconds.
- $2 \leq \mathbf{B} \leq 10$.
- $2 \leq \mathbf{S} \leq 10$.

**Test Set 2 (24 Pts, Hidden Verdict)**

- Time limit: 20 seconds.
- $2 \leq \mathbf{B} \leq 200$.
- $2 \leq \mathbf{S} \leq 5000$.



---

---
title: "[GCJ 2013 Qualification] Treasure"
layout: "post"
diff: 省选/NOI-
pid: P13284
tag: ['图论', '2013', '欧拉回路', 'Google Code Jam']
---
# [GCJ 2013 Qualification] Treasure
## 题目描述

Following an old map, you have stumbled upon the Dread Pirate Larry's secret treasure trove!

The treasure trove consists of $N$ locked chests, each of which can only be opened by a key of a specific type. Furthermore, once a key is used to open a chest, it can never be used again. Inside every chest, you will of course find lots of treasure, and you might also find one or more keys that you can use to open other chests. A chest may contain multiple keys of the same type, and you may hold any number of keys.

You already have at least one key and your map says what other keys can be found inside the various chests. With all this information, can you figure out how to unlock all the chests?

For example, suppose the treasure trove consists of four chests as described below, and you began with exactly one key of type $1$:

| Chest Number | Key Type To Open Chest | Key Types Inside |
| :---: | :---: | :---: |
| 1 | 1 | None |
| 2 | 1 | 1, 3 |
| 3 | 2 | None |
| 4 | 3 | 2 |

You can open all the chests in this example if you do them in the order $2$, $1$, $4$, $3$. If you start by opening chest #1 first, then you will have used up your only key, and you will be stuck.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a single line containing two positive integers $K$ and $N$, representing the number of keys you start with and the number of chests you need to open.

This is followed by a line containing $K$ integers, representing the types of the keys that you start with.

After that, there will be $N$ lines, each representing a single chest. Each line will begin with integers $T_i$ and $K_i$, indicating the key type needed to open the chest and the number of keys inside the chest. These two integers will be followed by $K_i$ more integers, indicating the types of the keys contained within the chest.
## 输出格式

For each test case, output one line containing "Case #x: $C_1$ $C_2$ ... $C_N$", where $x$ is the case number (starting from $1$), and where $C_i$ represents the index (starting from $1$) of the $i^{th}$ chest that you should open.

If there are multiple ways of opening all the chests, choose the "lexicographically smallest" way. In other words, you should choose to make $C_1$ as small as possible, and if there are multiple ways of making $C_1$ as small as possible, choose the one that makes $C_2$ as small as possible, and so on.

If there is no way to open all the chests, you should instead output one line containing "Case #x: IMPOSSIBLE".
## 样例

### 样例输入 #1
```
3
1 4
1
1 0
1 2 1 3
2 0
3 1 2
3 3
1 1 1
1 0
1 0
1 0
1 1
2
1 1 1
```
### 样例输出 #1
```
Case #1: 2 1 4 3
Case #2: 1 2 3
Case #3: IMPOSSIBLE
```
## 提示

**Limits**

- $1 \leq T \leq 25.$
- $1 \leq K.$
- All key types will be integers between $1$ and $200$ inclusive.

**Small dataset (20 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 20.$
- In each test case, there will be at most $40$ keys altogether.

**Large dataset (60 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 200.$
- In each test case, there will be at most $400$ keys altogether.


---

---
title: "[POI 2006] LIS-The Postman"
layout: "post"
diff: 省选/NOI-
pid: P3443
tag: ['2006', 'POI（波兰）', 'Special Judge', '欧拉回路']
---
# [POI 2006] LIS-The Postman
## 题目描述

每天早上，忙碌的邮递员需要经过城市的所有街道，完成投递邮件的任务。城市内的所有道路都是单向的，并通过一些路口连接起来。两个路口 $u,v$ 最多只有两条道路直接相连：一条 $u \to v$，一条 $v \to u$（也即不存在两条 $u \to v$ 的街道）。所有路口从 $1$ 到 $n$ 编号。

在路口 $1$，邮递员可以开始他的行程，或是结束他的行程。很长的一段时间里，邮递员可以随意选择他的路线，但最近新出的一条规定打乱了他的计划：每个邮递员得到了若干组路口序列，现在邮递员的路线必须满足如下要求：

- 路线必须从路口 $1$ 开始，在路口 $1$ 结束。
- 路线必须经过每条街道**恰好**一次。
- 规定的每个路口序列都必须在路线中**连续**出现。例如：`1 2 1` 这个序列在 `1 2 1 3` 中出现了，而在 `1 2 3 1` 中没有出现（不是连续的）。

现在邮递员找到了你，希望你能告诉他是否存在满足上述条件的路线，如果有的话，也请告诉他一条满足要求的路线。
## 输入格式

输入第一行两个整数 $n,m$，分别为路口数和街道数。

接下来 $m$ 行，每行两个整数 $a,b$，表示存在一条 $a \to b$ 的街道。保证相同的街道不会重复给出，也不会有自环。

下一行一个整数 $t$，代表规定的路口序列数。

接下来 $t$ 行，每行第一个整数 $k$，接下来 $k$ 个数，代表一个规定的路口序列。
## 输出格式

如果存在一个满足条件的路线，输出 `TAK`，否则输出 `NIE`。

如果答案是 `TAK` 的话，请在接下来每行输出一个整数，代表一个满足条件的路线。

设你输出了 $m+1$ 个数，输出的第 $i$ 个数为 $v_i$，你的输出需要满足如下条件：

- $v_1=v_{m+1}=1$。
- $\forall 1 \leq i \leq m$，都存在 $v_i$ 到 $v_{i+1}$ 的街道。
- 城市中的每条街道**恰好**出现一次。
- 规定的每个路口序列都必须在路线中**连续**出现。
## 样例

### 样例输入 #1
```
6 10
1 5
1 3
4 1
6 4
3 6
3 4
4 3
5 6
6 2
2 1
4
3 1 5 6
3 3 4 3
4 4 3 6 4
3 5 6 2
```
### 样例输出 #1
```
TAK
1
3
4
3
6
4
1
5
6
2
1
```
## 提示

所有数据均满足：$2 \leq n \leq 5 \times 10^4$，$1 \leq m \leq 2 \times 10^5$，$1 \leq a,b \leq n$，$a \neq b$，$0 \leq t \leq 10^4$，$2 \leq k \leq 10^5$，$\sum k \leq 10^5$。


---

---
title: "[POI 2010] MOS-Bridges"
layout: "post"
diff: 省选/NOI-
pid: P3511
tag: ['2010', '二分', 'POI（波兰）', '网络流', 'Special Judge', '欧拉回路']
---
# [POI 2010] MOS-Bridges
## 题目描述

San Bytecisco is a beautifully situated coastal town.

It consists of ![](http://main.edu.pl/images/OI17/mos-en-tex.1.png) small, yet densely populated islands,  numbered from ![](http://main.edu.pl/images/OI17/mos-en-tex.2.png) to ![](http://main.edu.pl/images/OI17/mos-en-tex.3.png).

Certain islands are connected with bridges, used for (bidirectional)  road traffic.

Each pair of islands can be connected with at most one bridge.

The islands are connected in such a way that every island can be reached  from every other by using the bridges only.

Byteasar and Bytie are going for a bike trip in San Bytecisco.

The will start their ride at the island no. 1.

They intend to visit every island, while passing along every bridge once  and ending the trip where it began, i.e., the island no. 1.

Being quite seasoned riders, they expect some serious trouble from... the wind!

After all, it is very windy along the coast, and especially so on the bridges between  the islands. Obviously, depending on its speed and direction, the wind makes it  hard to cross the bridge in different extent for either direction.

For simplicity we will assume for every bridge and direction of crossing,  the opposing wind speed is constant.

Help Byteasar and Bytie to find a route as they desire that will in addition  be the least tiresome. Byteasar and Bytie agreed on the maximum opposing wind speed as  a measure of a route's tiresomeness.



## 输入格式

In the first line of the standard input there are two integers separated by a single space: $n$ and $m$ ($2 \le n \le 1000$, $1 \le m \le 2000$), denoting the number of islands and the number of bridges in San Bytecisco respectively. The islands are numbered from 1 to n, while the bridges from 1 to m. The following  lines specify the bridges. The line no.($n+1$)  contains four integers $a_i,b_i,l_i,p_i$ ($1\le l_i,p_i \le 1000$), separated by single spaces. These denote that the bridge no. $i$ connects the islands no. $a$ and $b$. The opposing wind speeds are  when one goes moves from  to , and  if one goes from $a$ to $b$.
## 输出格式

If there is no route satisfying the requirements of the daring two riders,   the first and only line of the standard output should hold the word NIE   (no in Polish).

Otherwise, the output should have two lines, specifying the least tiresome route   over San Bytecisco.

The first line should hold the maximum opposing wind speed for that route, i.e.,   the number we wish to minimize.

The second line should hold ![](http://main.edu.pl/images/OI17/mos-en-tex.28.png) integers, separated by single spaces, giving   the numbers of successive bridges one crosses on the least tiresome route.

Should there be more than one least tiresome route, your program can pick one   arbitrarily.

## 样例

### 样例输入 #1
```
4 4
1 2 2 4
2 3 3 4
3 4 4 4
4 1 5 4
```
### 样例输出 #1
```
4
4 3 2 1
```
## 提示

$2 \le n \le 1000$，$1 \le m \le 2000$，$1 \le a_i,b_i \le n$，$a_i \neq b_i$，$1 \le l_i,p_i \le 1000$

## 题目翻译

给定一个图，边有权值且正着走和逆着走有不同权值，在这个图上求一条最大边权最小的欧拉回路，从点  $1$ 出发，要求输出方案。

第一行包括两个整数  $n$ 和  $m$，分别代表点的个数和边的个数。接下来  $m$ 行每行包括  $4$ 个整数  $a,b,l,p$，分别代表边的两个端点和正着走的权值和逆着走的权值。

如果没有符合要求的路径输出 `NIE`，否则输出两行。第一行一个整数表示最小的权值，第二行  $m$ 个整数表示依次经过的边的编号。

Translated by @Schwarzkopf_Henkal 


---

---
title: "[省选联考 2020 B 卷] 丁香之路"
layout: "post"
diff: 省选/NOI-
pid: P6628
tag: ['贪心', '2020', '并查集', '各省省选', '生成树', '欧拉回路']
---
# [省选联考 2020 B 卷] 丁香之路
## 题目描述

春暖花开，万物复苏，随着疫情的逐渐过去，Yazid 带着他的 $n$ 个好朋友来到 T 大校园参观游览。方便起见，我们将他们从 $1$ 至 $n$ 编号。

T 大校园的版图可以抽象成一张 $n$ 个顶点的无向图（顶点编号从 $1$ 至 $n$）。且对于任意两个不同顶点，设它们的编号分别为 $i, j(i\neq j)$，则它们之间有一条需要花费 $|i - j|$ 单位时间通过的无向边。

丁香花是 T 大的校花之一。时下正值丁香花盛开之际，校园内的 $m$ 条道路上都开有丁香花。Yazid 的朋友们对丁香花十分感兴趣，因此他们都希望遍历**所有**开有丁香花的 $m$ 条道路。

Yazid 的朋友们从顶点 $s$ 出发。其中，第 $i$ 个朋友希望以顶点 $i$ 为终点终止他的参观。与此同时，如上面所述，每个朋友都必须经过开着丁香花的 $m$ 条道路各至少一次。

Yazid 的朋友不想太过疲累，因此他们希望花尽可能少的时间来完成他们的目标。

请你计算 Yazid 的朋友们分别需要花费多少单位时间完成他们的目标。
## 输入格式

第一行 $3$ 个非负整数 $n, m, s$。保证 $1\le s\le n$；保证 $m\le \frac {n(n-1)}2$。

第 $2$ 行至第 $m+1$ 行，每行 $2$ 个整数 $u, v$，描述一条开有丁香花的，连接顶点 $u, v$ 的无向边。保证 $1\le u, v\le n$ 且 $u\neq v$；保证每条无向边至多被描述一次。

对于输入的所有行，用单个空格将行内的多个整数隔开。
## 输出格式

输出一行 $n$ 个用单个空格隔开的整数，其中第 $i$ 个整数描述 Yazid 的第 $i$ 个朋友完成目标所需花费的最少时间。

## 样例

### 样例输入 #1
```
4 3 1
1 2
4 2
3 1
```
### 样例输出 #1
```
6 7 8 7
```
### 样例输入 #2
```
6 0 2
```
### 样例输出 #2
```
1 0 1 2 3 4
```
### 样例输入 #3
```
5 4 1
1 2
3 4
4 5
3 5
```
### 样例输出 #3
```
8 7 6 7 8
```
## 提示

**样例解释 1**

第 $1$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 3$，最终回到 $1$，消耗 $|1-2|+|2-4|+|4-3|+|3-1| = 6$ 单位时间。

第 $2$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 3, 1$，最终来到 $2$，消耗 $7$ 单位时间。

第 $3$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 1$，最终来到 $3$，消耗 $8$ 单位时间。

第 $4$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $3, 1, 2$，最终来到 $4$，消耗 $7$ 单位时间。

**样例解释 2**

由于 $m = 0$，没有必经之路，因此每个朋友直接通过一条边直达目的地即可。


**数据范围与约定**

| 测试点编号  |  $n=$  | 其他特殊限制 |
| --------- | ---- | ---------- |
|  $1\sim 3$  |  $50$  |    $m=9$     |
|  $4\sim 6$  |  $50$  |    $m=15$    |
|  $7\sim 8$  |  $50$  |              |
| $9\sim 10$  | $300$  |              |
|    $11$     | $1600$ |    $m=0$     |
| $12\sim 14$ | $1600$ |    $m=1$     |
| $15\sim 17$ | $1600$ |              |
| $18\sim 20$ | $2500$ |              |


---

---
title: "[CEOI 2005] Depot Rearrangement"
layout: "post"
diff: 省选/NOI-
pid: P7684
tag: ['图论', '2005', 'Special Judge', 'CEOI（中欧）', '欧拉回路', '二分图', '构造']
---
# [CEOI 2005] Depot Rearrangement
## 题目描述

一家公司经营着 $N$ 个店铺，每个店铺都销售 $M$ 种不同的产品。该公司有一个大型仓库，产品在运送到商店之前在都会那里进行包装。每家商店将会收到相同数量的每种产品。因此，该公司将一定数量的相应产品分别包装到一个集装箱中，并用产品标识符标记该集装箱。产品由 $1$ 到 $M$ 的数字标识。因此，在包装结束后，仓库中将会有 $N×M$ 个集装箱，并且正好 $N$ 个集装箱贴有每个产品的对应标签。由于该仓库位于一个狭窄的建筑物内，所以集装箱排成了一排。但为了加快配送速度，仓库经理想要重新排列集装箱。由于将产品配送到商店是通过向每个商店发出一辆卡车来实现的，并且每辆卡车运载每种产品的一个集装箱，其合适的安排如下。该行最前部分 $M$ 个集装箱必须贴有不同的产品标签，该行的第二部分 $M$ 个集装箱必须贴有不同的产品标签，依此类推。不幸的是，在这一行的尽头只有一个空闲的地方可以放置一个集装箱。因此，必须通过依次拿起集装箱并将其移动到空闲位置来进行重新排列。重新排列后，空闲位置也必须在行的末尾。  
目标是通过最少的移动以实现所需的重新排列。  
现请您编写一个程序来计算需要最少移动多少次使得达成目标重排。
## 输入格式

第一行包含两个整数 $N$ 和 $M$。$N$ 是商店的数量，$M$ 是产品的数量。第二行包含 $N×M$ 个整数，即按初始顺序排列的集装箱标签。每个产品标识符 $x$ 在行中恰好出现 $N$ 次。
## 输出格式

第一行包含一个整数 $S$，这是达成集装箱所需排列所需的最小移动次数。以下 $S$ 行描述了重新排列。每行包含一对整数 $x$，$y$。一对 $x$，$y$ 描述了一个移动：位于 $x$ 位置的集装箱将移动到位置 $y$。位置由从 $1$ 到 $N×M+1$ 的数字标识；最初位置 $N×M+1$ 是空闲的（没有集装箱）。只有在移动之前位置 $y$ 是空闲的，从 $x$ 到 $y$ 的移动才是合法的。从 $x$ 移动到 $y$ 后，位置 $x$ 将是空闲的。
## 样例

### 样例输入 #1
```
5  6
4 1 3 1 6 5 2 3 2 3 5 6 2 1 4 5 6 4 1 3 2 4 5 5 1 2 3 4 6 6
```
### 样例输出 #1
```
8
9 31
18 9
10 18 
4 10
31 4
30 31
24 30
31 24
```
## 提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq N \leq 400$，$1 \leq M \leq 400$，$1 \leq x \leq M$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Depot Rearrangement。  
由 @[求学的企鹅](/user/271784) 翻译整理。  
Special Judge 感谢 @[abruce](/user/104324)。


---

---
title: "「Stoi2029」以父之名"
layout: "post"
diff: 省选/NOI-
pid: P7816
tag: ['搜索', '图论', 'Special Judge', 'O2优化', '深度优先搜索 DFS', '图遍历', '欧拉回路', '构造', '2029']
---
# 「Stoi2029」以父之名
## 题目背景

> 以父之名判决  
> 那感觉没有适合字汇  
> 就像边笑边掉泪  
> 凝视着完全的黑  
> 阻挡悲剧蔓延的悲剧会让我沉醉  
> ——《[以父之名](https://www.bilibili.com/video/BV1fx411N7bU?p=36)》
## 题目描述

地狱里有 $n$ 个罪人在等待判决，编号为 $1$ 至 $n$。罪人们之间有 $m$ 条罪的联系，编号为 $1$ 至 $m$，每条联系 的值为 $1$ 或 $2$ 且恰好连接两个罪人。

称一个罪人的自负度为他和其他所有罪人之间联系的值之和。两个罪人之间可能不止有一条联系，此时这些联系的值都应该被计算。由于这些罪人承受了太多的罪恶，他们变得不和谐。具体地，每个罪人的自负度都是奇数。

现在，神明将要对他们进行判决。判决的具体方式为：将每条联系都进行定向，使得这条联系所连接的两个罪人中的一个受到惩罚，另一个受到救赎，它们的值均为这条联系的值。

由于神明秉承父的仁慈，希望罪人们更加均等地接受惩罚和救赎，于是他规定判决后每个罪人所受到的惩罚和救赎值总和之差的绝对值必须恰好为 $1$。

由于神明工作繁忙，因此他以父之名要求你为他找到一种判决的方法。由于父的指示不会有错，所以一定存在一种这样的方法。

---

#### 题意简述

给定一个 $n$ 个点 $m$ 条边的无向图，边权均为 $1$ 或 $2$。保证每个点所相连的边权值之和均为奇数。你需要将这些边定向，使每个点的入边权值和与出边权值和之差的绝对值恰为 $1$。保证有解。输出任意一种方案。
## 输入格式

第一行两个正整数：$n,m$，表示有 $n$ 个罪人和 $m$ 条罪的联系。

接下来 $m$ 行，第 $i+1$ 行为三个正整数：$u_i,v_i,w_i$，表示第 $i$ 条联系连接 $u_i$ 与 $v_i$ 且值为 $w_i$。
## 输出格式

共一行 $m$ 个数字，第 $i$ 个数字为 $0$ 表示使 $u_i$ 受到惩罚，使 $v_i$ 受到救赎；为 $1$ 表示使 $v_i$ 受到惩罚，使 $u_i$ 受到救赎。
## 样例

### 样例输入 #1
```
4 5
1 2 1
1 3 2
2 3 1
2 4 1
4 1 2

```
### 样例输出 #1
```
00100

```
## 提示

#### 样例解释

定向后的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/uhz96nbm.png)

更多样例详见题目附件 `trial_sample.zip`。

------

#### 数据范围

**本题采用捆绑测试。**

- 特殊性质 A：边权均为 $1$，且任意两点之间只存在一条简单路径，且没有重边。
- 特殊性质 B：同一个点至多只有一条边权为 $1$ 和一条边权为 $2$ 的边相连。

| Subtask | 分值 | $1\le n \le$ | $1\le m \le$ | 特殊性质 | 
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $7$ | $10$ | $15$ | 无 | 
| $2$ |  $20$ |$10^3$ | $3\times10^3$ | 无 |
| $3$ |  $20$ |$3 \times 10^5$ | $3 \times 10^5$ | A |
| $4$ | $20$ |$3 \times 10^5$ | $3 \times 10^5$ | B | 
| $5$ |  $33$ |$10^6$ | $3 \times 10^6$ | 无 |

对于 $100\%$ 的数据，$1 \le u_i,v_i \le n \le 10^6$，$1 \le m \le 3 \times 10^6$，$w_i \in \{1,2\}$。

在题目附件 `trial_sample.zip` 中：

- `trial_sample1.in` 即为样例 #1。
- `trial_sample2.in` 满足特殊性质 A。
- `trial_sample3.in` 满足特殊性质 B。
- `trial_sample4.in` 不满足特殊性质。

另外该目录下还有 `checker.exe`。

------

#### 提示

**本题输入输出量较大，请使用较快的输入输出方式。**

本题提供 [Special Judge 源码](https://www.luogu.com.cn/paste/7albhubs)和 `checker.exe`，供选手调试。Windows 下使用方法为:  
命令行在目标文件夹输入指令：
```
checker.exe data.in data.out data.out
```
其中 `data.in` 是输入数据文件，`data.out` 是程序运行结果文件。观察评判结果即可。

- `Perfect answer.` 表示答案正确。
-  `Wrong answer on node x, and the difference is d.` 表示答案错误，其中节点 $x$ 的入边权值和与出边权值和之差的绝对值为 $d$ 而不为 $1$。
- `Invalid answer.` 表示输出的字符串长度不正确或输出非法字符。

请务必保证**输出格式正确**，否则 Special Judge 可能会返回 Unknown Error 等不可预估的结果。


---

---
title: "「SvR-2」1+2=3（加强版）"
layout: "post"
diff: 省选/NOI-
pid: P9153
tag: ['欧拉回路']
---
# 「SvR-2」1+2=3（加强版）
## 题目描述

你有一些木棒，每个木棒左边有一个数，右边有一个数，数是 $[0,c)$ 的自然数，你要将所有木棒拼起来，使相邻的数和为 $c$ 的对数最大。

例如，$c=3$，$1\text{ - }2$ 和 $1\text{ - }0$ 两个木棒，如果按 $1\text{ - }0,1\text{ - }2$ 这样拼，相邻的数和为 $3$ 的对数是 $0$；而按 $1\text{ - }{\underline\color{red}\textbf2},{\underline\color{red}\textbf1}\text{ - }0$ 这样拼相邻的数和为 $3$ 的对数是 $1$，因为 $2+1=3$。

## 输入格式

**本题有多组数据。**

输入的第一行一个正整数表示数据组数 $T$。

对于每组数据，第一行输入一个正整数 $c$，之后 $c$ 行，每行 $c$ 个整数，第 $i$ 行第 $j$ 个整数 $a_{i,j}$ 为 $(i-1)\text{ - }(j-1)$ 型木棒的个数。
## 输出格式

$T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
1
3
4 1 3
4 7 7
9 10 3

```
### 样例输出 #1
```
31

```
## 提示

对于 $100\%$ 数据，$\sum c^2\le5\times10^6$，$T\le10^5$，$1\le a_{i,j}\le10^9$，$3\le c\le10^3$。

**注：本题数据较弱，如有 hack 欢迎告知出题人。**


---

