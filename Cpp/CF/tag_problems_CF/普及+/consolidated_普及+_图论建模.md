---
title: "We Need More Bosses"
layout: "post"
diff: 普及+/提高
pid: CF1000E
tag: ['图论建模', '强连通分量', '树的直径']
---

# We Need More Bosses

## 题目描述

**题目大意：**

给定一个 $n$ 个点 $m$ 条边的无向图，保证图连通。找到两个点$s,t$，使得$s$到$t$**必须**经过的边最多（一条边无论走哪条路线都经过ta，这条边就是必须经过的边），$2<=n<=3*10^5,1<=m<=3*10^5$

## 输入格式

第一行两个整数，$n,m$

以下m行，每行两个整数$x,y$，表示$xy$间有一条无向边相连

## 输出格式

一个整数，即最多的必须经过边数

感谢@守望 提供翻译

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 1
4 1
5 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
1 2
4 3
3 2

```

### 输出

```
3

```



---

---
title: "Military Problem"
layout: "post"
diff: 普及+/提高
pid: CF1006E
tag: ['深度优先搜索 DFS', '图论建模', '向量']
---

# Military Problem

## 题目描述

在这个问题中你需要帮助伯兰（？？我没找到有Berland这个国家）军队组织他们的指挥系统

伯兰军队中一共有n个军官。第一个官员是军队的指挥官，他并没有任何上级。其他的军官都有且只有一个直接的上级。如果一个军官a是军官b的上级，那么你也可以说军官b就是军官a的下属

如果满足下列条件，那么军官x就是军官y的下属（直接或非直接）：

1.y是x的直接上级 2.x的直接上级是y的下属

举个例子，下图的官员3的下属有:5,6,7,8,9

所以，在伯兰军队的结构中，除了指挥官，其他人都是指挥官的下属

形式上的，让我们把伯兰军队看成一棵拥有n个节点的树，树的节点u就代表了军官u。根（即一号节点）就相当于指挥官

伯兰战争部门命令你对q个查询给出答案。这q个查询会以（ui，ki）的形式给出，ui代表了某个军官，ki是正整数。你需要输出，编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

要处理第i个查询，想象一下ui的命令如何我下达到ui的下属。这里使用了典型的DFS（深度优先搜索）算法。

假设现在的军官是a，他要下达一个命令。a军官选择一个军官b——还没有收到这个命令的直接下属（即在树上的一个孩子）。如果有许多这样的直接下属，那么A选择编号最小的那一个。A军官向B军官发出命令。之后，B使用完全相同的方式将命令扩展到它的子树。在B完成命令后，军官A再次选择下一个直接下属（使用相同的策略）。当军官A不能选择任何还没有接到命令的直接下属时，军官A下达命令完成。

让我们看一下下面这个例子（看下面的图）：

如果军官1下达了命令，军官们收到命令的顺序是：1,2,3,5,6,8,7,9,4

如果军官3下达了命令，军官们收到命令的顺序是：3,5,6,8,7,9

如果军官7下达了命令，军官们收到命令的顺序是：7,9

如果军官9下达了命令，军官们收到命令的顺序是：9

你应当分开处理这些查询。一个查询不会影响其他查询的结果。

## 输入格式

第一行包括两个整数n,q，表示有n个军官和q个查询（2≤n≤2×10^5,1≤q≤2×10^5）

第二行包括n-1个整数,p2、p3……pn，(1≤p<i )表示编号为i的军官直接上级为pi。编号为1的为指挥官并且他没有上级，不在输入数据中。

接下来的q行是q个查询每行包含两个整数(ui,ki)（1≤ui,ki≤n）ui表示开始下达命令的军官，ki表示要输出的军官编号是第几个得知命令的

## 输出格式

一共q行，每行包含一个整数表示第i个查询的答案：编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

感谢@hicc0305 提供的翻译

## 样例 #1

### 输入

```
9 6
1 1 1 3 5 3 5 7
3 1
1 5
3 4
7 3
1 8
1 9

```

### 输出

```
3
6
8
-1
9
4

```



---

---
title: "Checkposts"
layout: "post"
diff: 普及+/提高
pid: CF427C
tag: ['图论', '图论建模', '强连通分量']
---

# Checkposts

## 题目描述

你的城市有 $n$ 个路口。路口之间有一条单程道路。作为城市的市长，你必须确保所有路口的安全。

为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。 如果有一个检查站在 $i$ 路口，保护 $j$ 的条件是：$i==j$ 或者警察巡逻车可以从 $i$ 走到 $j$，并且能回到 $i$。

建造检查站要花一些钱。 由于城市的某些地区比其他地区更昂贵，在某些路口修建检查站可能比其他路口花费更多的钱。

你需要找到使所有路口安全的最低花费，以及花费与最低价格相等的方案数。

如果其中任何一个路口包含其中一个检查点而不包含在另一个路口中，则两种方式是不同的。

方案数模 $10^9+7$。

## 输入格式

第一行输入一个整数 $n$ 表示路口数。

第二行输入 $n$ 个整数 $a_{i}$ 表示每个路口建检查站的花费。

第三行输入一个整数 $m$ 表示有向道路的数量。

接下来 $m$ 行，每行两个整数 $x,y$，表示一条从 $x$ 到 $y$ 的有向道路。

## 输出格式

一行用空格分割的两个数，分别表示最小花费和方案数

## 说明/提示

$1 \leq n \leq 10^5,0 \leq m \leq 3 \times 10^5,0 \leq a_{i} \leq 10^9$。

$1<=u_{i},v_{i}<=n,u≠v$。

**最小花费不需要取模，方案数需要取模。**

## 样例 #1

### 输入

```
3
1 2 3
3
1 2
2 3
3 2

```

### 输出

```
3 1

```

## 样例 #2

### 输入

```
5
2 8 0 6 0
6
1 4
1 3
2 4
3 4
4 5
5 1

```

### 输出

```
8 2

```

## 样例 #3

### 输入

```
10
1 3 2 2 1 3 1 4 10 10
12
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9

```

### 输出

```
15 6

```

## 样例 #4

### 输入

```
2
7 91
2
1 2
2 1

```

### 输出

```
7 1

```



---

---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```



---

