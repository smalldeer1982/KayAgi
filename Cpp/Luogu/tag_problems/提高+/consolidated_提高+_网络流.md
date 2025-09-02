---
title: "[ZJOI2007] 矩阵游戏"
layout: "post"
diff: 提高+/省选-
pid: P1129
tag: ['2007', '各省省选', '递归', '网络流', '浙江', '二分图']
---
# [ZJOI2007] 矩阵游戏
## 题目描述

小 Q 是一个非常聪明的孩子，除了国际象棋，他还很喜欢玩一个电脑益智游戏――矩阵游戏。矩阵游戏在一个 $n \times n$ 黑白方阵进行（如同国际象棋一般，只是颜色是随意的）。每次可以对该矩阵进行两种操作：

- 行交换操作：选择矩阵的任意两行，交换这两行（即交换对应格子的颜色）。
- 列交换操作：选择矩阵的任意两列，交换这两列（即交换对应格子的颜色）。

游戏的目标，即通过若干次操作，使得方阵的主对角线(左上角到右下角的连线)上的格子均为黑色。

对于某些关卡，小 Q 百思不得其解，以致他开始怀疑这些关卡是不是根本就是无解的！于是小 Q 决定写一个程序来判断这些关卡是否有解。

## 输入格式

**本题单测试点内有多组数据**。

第一行包含一个整数 $T$，表示数据的组数，对于每组数据，输入格式如下：

第一行为一个整数，代表方阵的大小 $n$。
接下来 $n$ 行，每行 $n$ 个非零即一的整数，代表该方阵。其中 $0$ 表示白色，$1$ 表示黑色。
## 输出格式

对于每组数据，输出一行一个字符串，若关卡有解则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
2
2
0 0
0 1
3
0 0 1
0 1 0
1 0 0

```
### 样例输出 #1
```
No
Yes

```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 7$。
- 对于 $50\%$ 的数据，保证 $n \leq 50$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 200$，$1 \leq T \leq 20$。



---

---
title: "[THUPC 2025 初赛] 检查站"
layout: "post"
diff: 提高+/省选-
pid: P11531
tag: ['2025', '网络流', '最小割', 'THUPC']
---
# [THUPC 2025 初赛] 检查站
## 题目描述

小 I 是一个巨大的铁路公司的主管，他管理着 $n$ 个火车站，用 $1$ 至 $n$ 的整数给它们编号。铁路公司有 $c$ 个分部，第 $i$ 个分部的办公室位于火车站 $p_i$。可能有火车站没有分部办公室，一个火车站也有可能有多个分部办公室。

$n$ 个火车站之间由 $m$ 条单向铁路连接，其中第 $i$ 条铁路由火车站 $u_i$ 连向 $v_i$，属于分部 $r_i$ 管辖。为了保证管理方便，分部 $r_i$ 的办公室要么在 $u_i$，要么在 $v_i$。

火车站 $1$（港口）和 $n$（首都）是公司管辖范围内最繁忙的车站。为了保障进口货物安全，根据交通运输部的要求，小 I 需要在一些铁路上设立检查站，使得从火车站 $1$ 到火车站 $n$ 的所有可能路线上都有一个有检查站的铁路。

小 I 可以通知一些分部（也可以不通知任何分部），要求这些分部在它们管理的所有铁路上设立检查站。小 I 想知道，最少需要通知多少个分部才可以达到要求。作为新上任的算法工程师，你准备给小 I 露一手。
## 输入格式

输入的第一行三个整数 $n,m,c (2 \le n, m, c \le 5\times 10^4)$，分别表示火车站数量、铁路数量和分部数量。

接下来一行 $c$ 个整数 $p_1, p_2, \cdots, p_c (1 \le p_i \le n)$，描述每个分部所在的火车站编号。

接下来 $m$ 行每行三个整数 $u_i, v_i, r_i (1 \le u_i, v_i \le n, 1 \le r_i \le c)$，描述一条铁路。保证 $p_{r_i} = u_i$ 或 $p_{r_i} = v_i$。
## 输出格式

输出一行一个整数表示最少需要通知的分部数量。
## 样例

### 样例输入 #1
```
5 10 3
3 1 4
1 3 1
4 3 1
3 2 1
3 5 1
1 2 2
2 1 2
1 4 2
5 1 2
1 4 3
4 5 3
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

该样例的铁路组织如下图所示，其中红色、绿色和黑色分别为 1、2、3 分部管辖的铁路。最优策略是通知分部 1 和 3。

![](https://cdn.luogu.com.cn/upload/image_hosting/yami1v28.png)

### 题目来源

题目来自 THUPC2025（2025年清华大学学生程序设计竞赛暨高校邀请赛）初赛，信息来源于 [THUSAAC 仓库](https://gitlink.org.cn/thusaa/thupc2025pre)。



---

---
title: "[USACO5.4] 奶牛的电信Telecowmunication"
layout: "post"
diff: 提高+/省选-
pid: P1345
tag: ['图论', 'USACO', '福建省历届夏令营', '网络流', '最小割']
---
# [USACO5.4] 奶牛的电信Telecowmunication
## 题目描述

农夫约翰的奶牛们喜欢通过电邮保持联系，于是她们建立了一个奶牛电脑网络，以便互相交流。这些机器用如下的方式发送电邮：如果存在一个由 $c$ 台电脑组成的序列$a_1,a_2,\cdots ,a_c$，且 $a_1$ 与 $a_2$ 相连，$a_2$ 与 $a_3$ 相连，等等。那么电脑 $a_1$ 和 $a_c$ 就可以互发电邮。

很不幸，有时候奶牛会不小心踩到电脑上，农夫约翰的车也可能碾过电脑，这台倒霉的电脑就会坏掉。这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？请注意，$c_1,c_2$ 不能被破坏。请编写一个程序为她们计算这个最小值。

以如下网络为例：

```plain
   1*
  /
 3 - 2*
```

这张图画的是有 $2$ 条连接的 $3$ 台电脑。我们想要在电脑 $1$ 和 $2$ 之间传送信息。电脑 $1$ 与 $3$，$2$ 与 $3$ 直接连通。如果电脑 $3$ 坏了，电脑 $1$ 与 $2$ 便不能互发信息了。
## 输入格式

第一行：四个由空格分隔的整数：$N,M,c_1,c_2$。$N$ 是电脑总数，电脑由 $1$ 到 $N$ 编号。$M$ 是电脑之间连接的总数。后面的两个整数 $c_1$ 和 $c_2$ 是上述两头奶牛使用的电脑编号。连接没有重复且均为双向的（即如果 $c_1$ 与 $c_2$ 相连，那么 $c_2$ 与 $c_1$ 也相连）。两台电脑之间至多有一条连接。电脑 $c_1$ 和 $c_2$ 不会直接相连。

第 $2$ 到 $M+1$ 行：接下来的 $M$ 行中，每行包含两台直接相连的电脑的编号。
## 输出格式

一行，一个整数，表示使电脑 $c_1$ 和 $c_2$ 不能互相通信需要坏掉的电脑数目的最小值。
## 样例

### 样例输入 #1
```
3 2 1 2
1 3
2 3
```
### 样例输出 #1
```
1

```
## 提示

对于 $100\%$ 的数据：$1\le N \le 100$，$1\le M \le 600$。


---

---
title: "[CERC 2021] Regional development"
layout: "post"
diff: 提高+/省选-
pid: P13771
tag: ['2021', '网络流', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2021] Regional development
## 题目描述

The King has received several complaints that certain regions of his kingdom are economically neglected. The citizens have not seen a single merchant travelling on certain roads between villages in a very long time. To fix this problem and return wealth and prosperity to his kingdom, the King has appointed his royal mathematician to come up with a viable plan of merchant's routes.

The plan will consist of a positive number of merchants travelling along each road in one of the directions. The number of merchants entering a village along the roads should be equal to the number of merchants exiting it. To ensure a somewhat even distribution of merchants throughout the kingdom, the King has requested that the number of merchants travelling along each road should be at least one and less than $M$.

The royal mathematician has been summoned by the King to present his findings. His future is uncertain as he has not been able to solve the problem. However, he did make some progress. He found a plan with a valid number of merchants travelling along each road. The only problem is that the incoming and outgoing merchants in the villages do not add up (at least not exactly). Their difference might not be zero for every village, but it is equal to zero modulo $M$. He is willing to share his findings with you, if you can write a program that finds a valid plan or reports that it doesn't exist.
## 输入格式

The first line contains $N$, the number of villages, $R$, the number of roads and the number $M$.

The following $R$ lines describe the roads with numbers $A_i$, $B_i$ and $C_i$ that indicate a road between villages $A_i$ and $B_i$ with $C_i$ merchants travelling from $A_i$ to $B_i$. Cities are numbered from 1 to $N$. There is at most one road between each pair of villages and no road connects a village with itself. The difference between incoming and outgoing merchants in each village is equal to 0 modulo $M$.
## 输出格式

Print the number of merchants travelling along each road. Print them in the same order as they were given in the input and on separate lines. If the merchants travel in the opposite direction with respect to the order of cities that defined a road in the input, indicate this with a negative value (e.g. if there are $X$ merchants travelling from $B_i$ to $A_i$, indicate this with $-X$ in the $i$-th line of output).

If there are multiple solutions, you can output any of them. If no solution exists, print the word "IMPOSSIBLE" in a single line (without the quotes).
## 样例

### 样例输入 #1
```
4 5 4
1 2 1
2 3 2
4 1 1
2 4 3
3 4 2
```
### 样例输出 #1
```
2
3
2
-1
3
```
## 提示

### Input limits

* $1 \leq N \leq 1000$
* $0 \leq R \leq 10\ 000$
* $2 \leq M \leq 1000$
* $1 \leq A_i, B_i \leq N$
* $0 < C_i < M$


---

---
title: "[CERC 2023] Cakes"
layout: "post"
diff: 提高+/省选-
pid: P13847
tag: ['2023', '网络流', 'ICPC', 'CERC']
---
# [CERC 2023] Cakes
## 题目描述

Your local cake shop is making a business plan for the next few months. The bakers have $C$ different recipes, each requiring their own set of ingredients and tools. During the baking, the ingredients are consumed, but the tools are not and can be reused for other recipes. Currently, the bakery has no ingredients or tools – they were all destroyed in the recent floods or taken away by the tax bureau.

The son of the main chef managed to convince everyone to only bake each type of cake once. Individuals on the internet are supposedly happy to pay extra to be the only owners of their own unique Nutty-Fudge Tart (NFT). In fact, the son has already gone ahead and estimated how much money they can earn for each type of cake. Now bakers are looking at each other, trying to figure out which types of cake to prepare for maximum profit. You are given the costs of all ingredients, tools, and prices of cakes. Your task is to determine how much profit the bakers can make.
## 输入格式

The first line contains three integers: $G$, $C$, and $T$, the number of ingredients, the number of recipes, and the number of different tools in them, respectively. The second line contains $C$ space-separated integers $c_1, \ldots, c_C$, the prices of each cake. The third line contains $G$ space-separated integers $g_1, \ldots, g_G$, representing the prices of each ingredient. The fourth line contains $T$ space-separated integers $t_1, \ldots, t_T$, representing the prices of all tools.

This is followed by $C$ lines, each containing $G$ space-separated integers $a_{i,j}$, corresponding to the amount of ingredient $j$ in cake $i$.

Finally, this is followed by $C$ lines of the following format: the $i$-th row starts with an integer $n_i$, the number of tools required for $i$-th cake. This is followed by $n_i$ space-separated integers $b_{i,k}$, indicating that we need tool $b_{i,k}$ to prepare cake $i$ (listed tools are distinct).
## 输出格式

Print a single number: the maximum profit that the cake shop can make.
## 样例

### 样例输入 #1
```
5 3 4
14 18 21
1 2 3 1 2
5 6 3 10
0 0 1 2 0
1 2 0 1 2
5 2 1 0 0
2 1 2
2 2 3
2 3 4
```
### 样例输出 #1
```
3
```
## 提示

### Comment

The maximum profit is made by baking cakes 1 and 2, but not cake 3.

### Input limits

- $1 \leq G, C, T \leq 200$
- $0 \leq c_i, t_i \leq 10^9$
- $0 \leq g_j, a_{i,j} \leq 10^8$
- $0 \leq n_i \leq T$
- $1 \leq b_{i,k} \leq T$


---

---
title: "[ZJOI2009] 假期的宿舍"
layout: "post"
diff: 提高+/省选-
pid: P2055
tag: ['2009', '各省省选', '网络流', '浙江', '二分图']
---
# [ZJOI2009] 假期的宿舍
## 题目描述

学校放假了……有些同学回家了，而有些同学则有以前的好朋友来探访，那么住宿就是一个问题。

比如 A 和 B 都是学校的学生，A 要回家，而 C 来看B，C 与 A 不认识。我们假设每个人只能睡和自己直接认识的人的床。那么一个解决方案就是 B 睡 A 的床而 C 睡 B 的床。而实际情况可能非常复杂，有的人可能认识好多在校学生，在校学生之间也不一定都互相认识。

我们已知一共有 $n$ 个人，并且知道其中每个人是不是本校学生，也知道每个本校学生是否回家。问是否存在一个方案使得所有不回家的本校学生和来看他们的其他人都有地方住。

## 输入格式

第一行一个数 $T$ 表示数据组数。接下来 $T$ 组数据，每组数据第一行一个数 $n$ 表示涉及到的总人数。

接下来一行 $n$ 个数，第 $i$ 个数表示第 $i$ 个人是否是在校学生 ($0$ 表示不是，$1$ 表示是)。再接下来一行 $n$ 个数，第 $i$ 个数表示第 $i$ 个人是否回家 ($0$ 表示不回家，$1$ 表示回家，注意如果第 $i$ 个人不是在校学生，那么这个位置上的数是一个随机的数，你应该在读入以后忽略它)。

接下来 $n$ 行每行 $n$ 个数，第 $i$ 行第 $j$ 个数表示 $i$ 和 $j$ 是否认识 ($1$ 表示认识，$0$ 表示不认识，第 $i$ 行 $i$ 个的值为 $0$，但是显然自己还是可以睡自己的床)，认识的关系是相互的。

## 输出格式

对于每组数据，如果存在一个方案则输出 `^_^`，否则输出`T_T`。（注意输出的都是半角字符，即三个符号的 ASCII 码分别为 $94,84,95$）

## 样例

### 样例输入 #1
```
1
3
1 1 0
0 1 0
0 1 1
1 0 0
1 0 0
```
### 样例输出 #1
```
^_^
```
## 提示

对于 $30\%$ 的数据满足 $1 \le n \le 12$。

对于 $100\%$ 的数据满足 $1 \le n \le 50$，$1 \le T \le 20$。



---

---
title: "[SHOI2007] 善意的投票 / [JLOI2010] 冠军调查"
layout: "post"
diff: 提高+/省选-
pid: P2057
tag: ['2007', '各省省选', '网络流', '上海']
---
# [SHOI2007] 善意的投票 / [JLOI2010] 冠军调查
## 题目描述

幼儿园里有 $n$ 个小朋友打算通过投票来决定睡不睡午觉。

对他们来说，这个问题并不是很重要，于是他们决定发扬谦让精神。

虽然每个人都有自己的主见，但是为了照顾一下自己朋友的想法，他们也可以投和自己本来意愿相反的票。

我们定义一次投票的冲突数为下面两者相加：

* 实际投票不同的好朋友对数。

* 自己实际投票和自己本来意愿不同的人数。

我们的问题就是，每位小朋友应该怎样投票，才能使冲突数最小？
## 输入格式

第一行两个整数 $n,m$。其中 $n$ 代表总人数，$m$ 代表好朋友的对数。

第二行 $n$ 个整数，第 $i$ 个整数代表第 $i$ 个小朋友的意愿：当它为 $1$ 时表示同意睡觉，当它为 $0$ 时表示反对睡觉。

接下来 $m$ 行，每行有两个整数 $i,j$，表示 $i,j$ 是一对好朋友，我们保证任何两对 $i,j$ 不会重复。

## 输出格式

一行一个整数，即可能的最小冲突数。
## 样例

### 样例输入 #1
```
3 3
1 0 0
1 2
1 3
3 2
```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，$2\le n\le300$，$1\le m \le \frac{n(n-1)}2$。


---

---
title: "[HNOI2001] 洗牌机"
layout: "post"
diff: 提高+/省选-
pid: P2227
tag: ['动态规划 DP', '2001', '各省省选', '网络流', '湖南', '图论建模']
---
# [HNOI2001] 洗牌机
## 题目描述

剀剀和凡凡有 $n$ 张牌（依次标号为 $1,2,\ldots,n$）和一台洗牌机。假设 $n$ 是奇数。洗牌机的功能是进行如下的操作：对所有位置 $i(1\le i\le n)$，如果位置 $i$ 上的牌是 $j$，而且位置 $j$ 上的牌是 $k$，那么通过洗牌机后位置 $i$ 上的牌将是 $k$。

剀剀首先写下数值 $1,2,\ldots,n$ 的一个随机排列：$a_1,a_2,\ldots,a_n$。然后他这样来排列牌的顺序：位置 $a_i$ 放置牌 $a_{i+1}$, （对于 $1\le i\le n-1$），而 $a_n$ 放置牌 $a_1$。这样排列后，牌的顺序就为 $x_1,x_2,\ldots ,x_n$。然后，他把这种顺序排列的牌放入洗牌机洗牌 $s$ 次，得到牌的顺序为 $p_1,p_2,\ldots,p_n$。现在，剀剀把牌的最后顺序和洗牌次数告诉凡凡，要凡凡猜出牌的最初顺序 $x_1,x_2,\ldots,x_n$。

## 输入格式

第一行为整数 $n$ 和 $s$。

第二行为牌的最终顺序  $p_1,p_2,\ldots,p_n$。
## 输出格式

为一行，即牌的最初顺序 $x_1,x_2,\ldots,x_n$。
## 样例

### 样例输入 #1
```
5 2          
4 1 5 3 2

```
### 样例输出 #1
```
2 5 4 1 3
```
## 提示

#### 数据规模与约定
对于 $100\%$ 的数据，保证 $1\le n,s\le 10^3$。

数据保证，从 $i=1$ 开始，设第 $i$ 张牌上数是 $j$，则赋值 $i=j$ 后继续此操作，最终会遍历所有牌。


---

---
title: "[ZJOI2009] 狼和羊的故事"
layout: "post"
diff: 提高+/省选-
pid: P2598
tag: ['2009', '各省省选', '网络流', '浙江', '最小割']
---
# [ZJOI2009] 狼和羊的故事
## 题目描述

“狼爱上羊啊爱的疯狂，谁让他们真爱了一场；狼爱上羊啊并不荒唐，他们说有爱就有方向……”Orez 听到这首歌，心想：狼和羊如此和谐，为什么不尝试羊狼合养呢？说干就干！

Orez 的羊狼圈可以看作一个 $n\times m$ 的矩阵格子，这个矩阵的边缘已经装上了篱笆。可是 Drake 很快发现狼再怎么也是狼，它们总是对羊垂涎三尺，那首歌只不过是一个动人的传说而已。所以 Orez 决定在羊狼圈中再加入一些篱笆，还是要将羊狼分开来养。

通过仔细观察，Orez 发现狼和羊都有属于自己领地，若狼和羊们不能呆在自己的领地，那它们就会变得非常暴躁，不利于他们的成长。

Orez 想要添加篱笆的尽可能的短。当然这个篱笆首先得保证不能改变狼羊的所属领地，再就是篱笆必须修筑完整，也就是说必须修建在单位格子的边界上并且不能只修建一部分。
## 输入格式

文件的第一行包含两个整数 $n$ 和 $m$。接下来 $n$ 行每行 $m$ 个整数，$1$ 表示该格子属于狼的领地，$2$ 表示属于羊的领地，$0$ 表示该格子不是任何一只动物的领地。
## 输出格式

文件中仅包含一个整数 $\mathit{ans}$，代表篱笆的最短长度。
## 样例

### 样例输入 #1
```
2 2

2 2 

1 1 
```
### 样例输出 #1
```
2


```
## 提示

对于 $10\%$ 的数据，$n, m \le 3$。  
对于 $30\%$ 的数据，$n, m \le 20$。  
对于 $100\%$ 的数据，$1 \le n, m \le 100$。


---

---
title: "[USACO4.2] 草地排水Drainage Ditches"
layout: "post"
diff: 提高+/省选-
pid: P2740
tag: ['USACO', '网络流']
---
# [USACO4.2] 草地排水Drainage Ditches
## 题目背景

在农夫约翰的农场上，每逢下雨，贝茜最喜欢的三叶草地就积聚了一潭水。这意味着草地被水淹没了，并且小草要继续生长还要花相当长一段时间。因此，农夫约翰修建了一套排水系统来使贝茜的草地免除被大水淹没的烦恼（不用担心，雨水会流向附近的一条小溪）。作为一名一流的技师，农夫约翰已经在每条排水沟的一端安上了控制器，这样他可以控制流入排水沟的水流量。
## 题目描述

农夫约翰知道每一条排水沟每分钟可以流过的水量，和排水系统的准确布局（起点为水潭而终点为小溪的一张网）。需要注意的是，有些时候从一处到另一处不只有一条排水沟。

根据这些信息，计算从水潭排水到小溪的最大流量。对于给出的每条排水沟，雨水只能沿着一个方向流动，注意可能会出现雨水环形流动的情形。
## 输入格式

第一行：两个用空格分开的整数 $N$（$0 \le N \le 200$）和 $M$（$2 \le M \le 200$）。$N$ 是农夫 John 已经挖好的排水沟的数量，$M$ 是排水沟交叉点的数量。交点 $1$ 是水潭，交点 $M$ 是小溪。

第二行到第 $N + 1$ 行：每行有三个整数，$S_i, E_i, C_i$。$S_i$ 和 $E_i$（$1 \le S_i, E_i \le M$）指明排水沟两端的交点，雨水从 $S_i$ 流向 $E_i$。$C_i$（$0 \le C_i \le {10}^7$）是这条排水沟的最大容量。
## 输出格式

输出一个整数，即排水的最大流量。
## 样例

### 样例输入 #1
```
5 4

1 2 40

1 4 20

2 4 20

2 3 30

3 4 10
```
### 样例输出 #1
```
50
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 4.2

**【数据范围】**

对于 $100 \%$ 的数据，$0 \le N, M \le 200$，$0 \le C_i \le {10}^7$。


---

---
title: "试题库问题"
layout: "post"
diff: 提高+/省选-
pid: P2763
tag: ['网络流', 'Special Judge', '网络流与线性规划 24 题']
---
# 试题库问题
## 题目描述

问题描述：

假设一个试题库中有 $n$ 道试题。每道试题都标明了所属类别。同一道题可能有多个类别属性。现要从题库中抽取 $m$ 道题组成试卷。并要求试卷包含指定类型的试题。试设计一个满足要求的组卷算法。

编程任务：

对于给定的组卷要求，计算满足要求的组卷方案。
## 输入格式

第一行有两个正整数 $k$ 和 $n$。$k$ 表示题库中试题类型总数，$n$ 表示题库中试题总数。

第二行有 $k$ 个正整数，第 $i$ 个正整数表示要选出的类型 $i$ 的题数。这 $k$ 个数相加就是要选出的总题数 $m$。

接下来的 $n$ 行给出了题库中每个试题的类型信息。每行的第一个正整数 $p$ 表明该题可以属于 $p$ 类，接着的 $p$ 个数是该题所属的类型号。
## 输出格式

输出共 $k$ 行，第 $i$ 行输出 `i: ` 后接类型 $i$ 的题号。  
如果有多个满足要求的方案，只要输出一个方案。  
如果问题无解，则输出`No Solution!`。
## 样例

### 样例输入 #1
```
3 15
3 3 4
2 1 2
1 3
1 3
1 3
1 3
3 1 2 3
2 2 3
2 1 3
1 2
1 2
2 1 2
2 1 3
2 1 2
1 1
3 1 2 3
```
### 样例输出 #1
```
1: 1 6 8
2: 7 9 10
3: 2 3 4 5
```
## 提示

$2\leq k \leq 20$，$k \leq n \leq 10^3$。

---

感谢 @PhoenixEclipse 提供 spj



---

---
title: "[USACO09JAN] Total Flow S"
layout: "post"
diff: 提高+/省选-
pid: P2936
tag: ['2009', 'USACO', '网络流']
---
# [USACO09JAN] Total Flow S
## 题目描述

Farmer John always wants his cows to have enough water and thus has made a map of the N (1 <= N <= 700) water pipes on the farm that connect the well to the barn. He was surprised to find a wild mess of different size pipes connected in an apparently haphazard way. He wants to calculate the flow through the pipes.

Two pipes connected in a row allow water flow that is the minimum of the values of the two pipe's flow values. The example of a pipe with flow capacity 5 connecting to a pipe of flow capacity 3 can be reduced logically to a single pipe of flow capacity 3:

```plain
+---5---+---3---+    ->    +---3---+
```

Similarly, pipes in parallel let through water that is the sum of their flow capacities:

```plain
   +---5---+
---+       +---    ->    +---8---+
   +---3---+
```

Finally, a pipe that connects to nothing else can be removed; it contributes no flow to the final overall capacity:

```plain
   +---5---+
---+               ->    +---3---+
   +---3---+--
```

All the pipes in the many mazes of plumbing can be reduced using these ideas into a single total flow capacity.

Given a map of the pipes, determine the flow capacity between the well (A) and the barn (Z).

Consider this example where node names are labeled with letters:

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +---3---+---5---+---4---+
                 C       D
```

Pipe BC and CD can be combined:

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +-----3-----+-----4-----+
                     D
```

Then BD and DZ can be combined: 

```plain
         +-----------6-----------+
A+---3---+B                      +Z
         +-----------3-----------+
```

Then two legs of BZ can be combined: 

```plain
         B
A+---3---+---9---+Z
```

Then AB and BZ can be combined to yield a net capacity of 3:

```plain
A+---3---+Z
```

Write a program to read in a set of pipes described as two endpoints and then calculate the net flow capacity from 'A' to 'Z'. All

networks in the test data can be reduced using the rules here.

Pipe i connects two different nodes a\_i and b\_i (a\_i in range

'A-Za-z'; b\_i in range 'A-Za-z') and has flow F\_i (1 <= F\_i <= 1,000). Note that lower- and upper-case node names are intended to be treated as different.

The system will provide extra test case feedback for your first 50 submissions.

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N + 1: Line i+1 describes pipe i with two letters and an integer, all space-separated: a\_i, b\_i, and F\_i

## 输出格式

\* Line 1: A single integer that the maximum flow from the well ('A') to the barn ('Z')

## 样例

### 样例输入 #1
```
5 
A B 3 
B C 3 
C D 5 
D Z 4 
B Z 6 

```
### 样例输出 #1
```
3 

```
## 题目翻译

约翰总希望他的奶牛有足够的水喝，因此他找来了农场的水管地图，想算算牛棚得到的水的总流量。农场里一共有 $N$ 根水管。约翰发现水管网络混乱不堪，他试图对其进行简化。他简化的方式是这样的：

- 两根水管串联，则可以用较小流量的那根水管代替总流量。
- 两根水管并联，则可以用流量为两根水管流量和的一根水管代替它们。

当然，如果存在一根水管一端什么也没有连接，可以将它移除 。

请写个程序算出从水井 $\verb!A!$ 到牛棚 $\verb!Z!$ 的总流量。数据保证所有输入的水管网络都可以用上述方法简化 。

**注意**：输入数据中每个顶点用大写字母**或者**小写字母表示。也就是说，输入里可能出现用小写字母命名的节点。


---

---
title: "圆桌问题"
layout: "post"
diff: 提高+/省选-
pid: P3254
tag: ['网络流', 'Special Judge', '网络流与线性规划 24 题']
---
# 圆桌问题
## 题目描述

有来自 $m$ 个不同单位的代表参加一次国际会议。第 $i$ 个单位派出了 $r_i$ 个代表。

会议的餐厅共有 $n$ 张餐桌，第 $i$ 张餐桌可容纳 $c_i$ 个代表就餐。

为了使代表们充分交流，希望从同一个单位来的代表不在同一个餐桌就餐。请给出一个满足要求的代表就餐方案。
## 输入格式

输入的第一行是用空格隔开的两个整数，分别代表单位的个数 $m$ 和餐桌的个数 $n$。  
第二行有 $m$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 个单位的代表人数 $r_i$。  
第三行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 张餐桌能容纳的人数 $c_i$。
## 输出格式

**本题存在 Special Judge**。  
请输出是否存在满足要求的就餐方案，若存在，请给出任意一种可行的方案。  
输出的第一行是一个非 $0$ 即 $1$ 的整数，若存在方案则输出 $1$，否则输出 $0$。  
若存在方案，则对于第 $2$ 到第 $(m + 1)$ 行，在第 $(i + 1)$ 行输出 $r_i$ 个整数，代表第 $i$ 个单位的代表就餐的餐桌编号。
## 样例

### 样例输入 #1
```
4 5
4 5 3 5
3 5 2 6 4

```
### 样例输出 #1
```
1
1 2 4 5
1 2 3 4 5
2 4 5
1 2 3 4 5

```
## 提示

**【数据规模与约定】**

- 对于 $100\%$ 的数据，保证 $1 \leq m \leq 150$，$1 \leq n \leq 270$，$1 \leq r_i, c_i \leq 10^3$。

**【提示】**

- 请注意输入的第一行先读入 $m$ 再读入 $n$。


---

---
title: "骑士共存问题"
layout: "post"
diff: 提高+/省选-
pid: P3355
tag: ['O2优化', '网络流与线性规划 24 题']
---
# 骑士共存问题
## 题目描述

在一个 $n \times n$ 个方格的国际象棋棋盘上，马（骑士）可以攻击的棋盘方格如图所示。棋盘上某些方格设置了障碍，骑士不得进入。

![](https://cdn.luogu.com.cn/upload/pic/2669.png)

对于给定的 $n \times n$ 个方格的国际象棋棋盘和障碍标志，计算棋盘上最多可以放置多少个骑士，使得它们彼此互不攻击。
## 输入格式

第一行有 $2$ 个正整数 $n$ 和 $m$ ，分别表示棋盘的大小和障碍数。接下来的 m 行给出障碍的位置。每行 $2$ 个正整数，表示障碍的方格坐标。
## 输出格式

将计算出的共存骑士数输出。
## 样例

### 样例输入 #1
```
3 2
1 1
3 3
```
### 样例输出 #1
```
5
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 200$，$0 \leq m \lt n^2$。


---

---
title: "【模板】网络最大流"
layout: "post"
diff: 提高+/省选-
pid: P3376
tag: ['网络流', 'O2优化']
---
# 【模板】网络最大流
## 题目描述

如题，给出一个网络图，以及其源点和汇点，求出其网络最大流。

## 输入格式

第一行包含四个正整数 $n,m,s,t$，分别表示点的个数、有向边的个数、源点序号、汇点序号。

接下来 $m$ 行每行包含三个正整数 $u_i,v_i,w_i$，表示第 $i$ 条有向边从 $u_i$ 出发，到达 $v_i$，边权为 $w_i$（即该边最大流量为 $w_i$）。
## 输出格式

一行，包含一个正整数，即为该网络的最大流。

## 样例

### 样例输入 #1
```
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30

```
### 样例输出 #1
```
50

```
## 提示

#### 样例输入输出 1 解释

 ![](https://cdn.luogu.com.cn/upload/pic/2262.png) 

题目中存在 $3$ 条路径：

- $4\to 2\to 3$，该路线可通过 $20$ 的流量。
- $4\to 3$，可通过 $20$ 的流量。
- $4\to 2\to 1\to 3$，可通过 $10$ 的流量（边 $4\to 2$ 之前已经耗费了 $20$ 的流量）。

故流量总计 $20+20+10=50$。输出 $50$。

---

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq10$，$m\leq25$。
- 对于 $100\%$ 的数据，保证 $1 \leq n\leq200$，$1 \leq m\leq 5000$，$0 \leq w\lt 2^{31}$。



---

---
title: "主主树"
layout: "post"
diff: 提高+/省选-
pid: P3701
tag: ['字符串', '网络流', '洛谷原创', '图论建模']
---
# 主主树
## 题目背景

byx 和诗乃酱都非常都非常喜欢种树。有一天，他们得到了两颗奇怪的树种，于是各自取了一颗回家种树，并约定几年后比一比谁种出来的树更加牛 X。
## 题目描述

很快，这棵树就开花结果了。byx 和诗乃酱惊讶的发现，这是一棵主主树，树上长满了主主和主主的朋友们。这棵树上一共有五种人，主主（$\verb!J!$），记记（$\verb!HK!$），高高（$\verb!W!$），王王（$\verb!E!$）和歪歪（$\verb!YYY!$）。他们发现，他们的主主树上的人数相同，都为 $N$。

 ![](https://cdn.luogu.com.cn/upload/image_hosting/0vklm8ow.png) 

研究发现，这五种人的输赢如上图所示（一样的人不能 PK），箭头指向输的人。至于为什么，留给同学们自己思考。

比赛如期进行。

byx 和诗乃酱要进行 $M$ 场比赛，每一场比赛他们会选出树上的两个人来比较看谁更牛 X。

第 $i$ 个人寿命为 $\text{Life}_i$ 秒，每次比完赛他们就会 $-1$s。当他们生命为 $0$s 时他们就不能再比赛了。

同时，当 $\verb!J!$ 的寿命为 $0$ 时，同一棵树上的 $\verb!YYY!$ 可以为他 $+1$s。每个 $\verb!YYY!$ 只能给每个 $\verb!J!$ 续一次。

那么问题来了：

现在给定 $N,M(1\le N\le 100,1\le M\le 1000)$，诗乃酱和 byx 每一个人所属种类（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$）以及每一个人的生命，生命不超过 $50$。请你算算 byx 最多能够赢得多少场比赛呢。

数据保证每一场一定都有人用。两个人之间只能比一场。
## 输入格式

第一行包含两个数 $N,M$，含义看上面。  

第二行 $N$ 个字串（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$），表示 byx 的人所属种类，用空格隔开。  

第三行 $N$ 个字串（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$），表示诗乃酱的人所属种类，用空格隔开。  

第四行 $N$ 个数，表示 byx 的人的生命。  

第五行 $N$ 个数，表示诗乃酱的人的生命。  
## 输出格式

一个数，byx 能赢的场次。
## 样例

### 样例输入 #1
```
3 3
J W YYY
J HK E
2 2 2
2 2 2

```
### 样例输出 #1
```
3

```
## 提示

第一场主主赢记记，第二场高高赢王王，第三场歪歪赢记记。



---

---
title: "孤岛营救问题"
layout: "post"
diff: 提高+/省选-
pid: P4011
tag: ['O2优化', '广度优先搜索 BFS', '图论建模', '进制', '网络流与线性规划 24 题', '状压 DP']
---
# 孤岛营救问题
## 题目描述

$1944$ 年，特种兵麦克接到国防部的命令，要求立即赶赴太平洋上的一个孤岛，营救被敌军俘虏的大兵瑞恩。瑞恩被关押在一个迷宫里，迷宫地形复杂，但幸好麦克得到了迷宫的地形图。迷宫的外形是一个长方形，其南北方向被划分为 $N$ 行，东西方向被划分为 $M$ 列，于是整个迷宫被划分为 $N\times M$ 个单元。每一个单元的位置可用一个有序数对(单元的行号，单元的列号)来表示。南北或东西方向相邻的 $2$ 个单元之间可能互通，也可能有一扇锁着的门，或者是一堵不可逾越的墙。迷宫中有一些单元存放着钥匙，并且所有的门被分成$P$ 类，打开同一类的门的钥匙相同，不同类门的钥匙不同。


大兵瑞恩被关押在迷宫的东南角，即 $(N,M)$ 单元里，并已经昏迷。迷宫只有一个入口，在西北角。也就是说，麦克可以直接进入 $(1,1)$ 单元。另外，麦克从一个单元移动到另一个相邻单元的时间为 $1$，拿取所在单元的钥匙的时间以及用钥匙开门的时间可忽略不计。


试设计一个算法，帮助麦克以最快的方式到达瑞恩所在单元，营救大兵瑞恩。

## 输入格式

第 $1$ 行有 $3$ 个整数，分别表示 $N,M,P$ 的值。

第 $2$ 行是 $1$ 个整数 $K$，表示迷宫中门和墙的总数。

第 $I+2$ 行$(1\leq I\leq K)$，有 $5$ 个整数，依次为$X_{i1},Y_{i1},X_{i2},Y_{i2},G_i$：

- 当 $G_i \geq 1$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一扇第 $G_i$ 类的门

- 当 $G_i=0$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一堵不可逾越的墙（其中，$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1$，$0\leq G_i\leq P$）。

第 $K+3$ 行是一个整数 $S$，表示迷宫中存放的钥匙总数。

第 $K+3+J$  行$(1\leq J\leq S)$，有 $3$ 个整数，依次为 $X_{i1},Y_{i1},Q_i$：表示第 $J$ 把钥匙存放在 $(X_{i1},Y_{i1})$单元里，并且第 $J$ 把钥匙是用来开启第 $Q_i$ 类门的。（其中$1\leq Q_i\leq P$）。

输入数据中同一行各相邻整数之间用一个空格分隔。

## 输出格式

将麦克营救到大兵瑞恩的最短时间的值输出。如果问题无解，则输出 $-1$。

## 样例

### 样例输入 #1
```
4 4 9
9
1 2 1 3 2
1 2 2 2 0
2 1 2 2 0
2 1 3 1 0
2 3 3 3 0
2 4 3 4 1
3 2 3 3 0
3 3 4 3 0
4 3 4 4 0
2
2 1 2
4 2 1
```
### 样例输出 #1
```
14
```
## 提示

$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1,0\leq G_i\leq P$

$1\leq Q_i\leq P$


$N,M,P\leq10, K<150,S\leq 14$



---

---
title: "分配问题"
layout: "post"
diff: 提高+/省选-
pid: P4014
tag: ['深度优先搜索 DFS', '二分图', '费用流', '网络流与线性规划 24 题']
---
# 分配问题
## 题目描述

有 $n$ 件工作要分配给 $n$ 个人做。第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$ 。试设计一个将 $n$ 件工作分配给 $n$ 个人做的分配方案，使产生的总效益最小或最大。

## 输入格式

文件的第一行有 $1$ 个正整数 $n$，表示有 $n$ 件工作要分配给 $n$ 个人做。

接下来的 $n$ 行中，每行有 $n$ 个整数 $c_{i,j}$，表示第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{i,j}$。

## 输出格式

两行分别输出最小总效益和最大总效益。

## 样例

### 样例输入 #1
```
5
2 2 2 1 2
2 3 1 2 4
2 0 1 1 1
2 3 4 3 3
3 2 1 2 1
```
### 样例输出 #1
```
5
14
```
## 提示

$1 \leq n \leq 50, 0 \le c _ {i, j} \le 100$。

一个人只能修一个工件。


---

---
title: "运输问题"
layout: "post"
diff: 提高+/省选-
pid: P4015
tag: ['O2优化', '费用流', '网络流与线性规划 24 题']
---
# 运输问题
## 题目描述

$W$ 公司有 $m$ 个仓库和 $n$ 个零售商店。第 $i$ 个仓库有 $a_i$ 个单位的货物；第 $j$ 个零售商店需要 $b_j$ 个单位的货物。


货物供需平衡，即$\sum\limits_{i=1}^{m}a_i=\sum\limits_{j=1}^{n}b_j$。


从第 $i$ 个仓库运送每单位货物到第 $j$ 个零售商店的费用为 $c_{ij}$​​ 。


试设计一个将仓库中所有货物运送到零售商店的运输方案，使总运输费用最少。

## 输入格式

第 $1$ 行有 $2$ 个正整数 $m$ 和 $n$，分别表示仓库数和零售商店数。


接下来的一行中有 $m$ 个正整数 $a_i$，表示第 $i$ 个仓库有 $a_i$个单位的货物。


再接下来的一行中有 $n$ 个正整数 $b_j$，表示第 $j$ 个零售商店需要 $b_j$ 个单位的货物。


接下来的 $m$ 行，每行有 $n$ 个整数，表示从第 $i$ 个仓库运送每单位货物到第 $j$ 个零售商店的费用 $c_{ij}$。

## 输出格式

两行分别输出最小运输费用和最大运输费用。

## 样例

### 样例输入 #1
```
2 3
220 280
170 120 210
77 39 105
150 186 122
```
### 样例输出 #1
```
48500
69140
```
## 提示

$1 \leq n, m \leq 100$



---

---
title: "[TJOI2013] 攻击装置"
layout: "post"
diff: 提高+/省选-
pid: P4304
tag: ['2013', '各省省选', '网络流', '二分图', '天津']
---
# [TJOI2013] 攻击装置
## 题目描述

给定一个 01 矩阵，其中你可以在 0 的位置放置攻击装置。每一个攻击装置 $(x,y)$ 都可以按照“日”字攻击其周围的 $8$ 个位置 $(x-1,y-2)$，$(x-2,y-1)$，$(x+1,y-2)$，$(x+2,y-1)$，$(x-1,y+2)$，$(x-2,y+1)$，$(x+1,y+2)$，$(x+2,y+1)$。

求在装置互不攻击的情况下，最多可以放置多少个装置。
## 输入格式

第一行一个整数 $N$，表示矩阵大小为 $N \times N$。

接下来 $N$ 行每一行一个长度 $N$ 的 01 串，表示矩阵。
## 输出格式

一个整数，表示在装置互不攻击的情况下最多可以放置多少个装置。
## 样例

### 样例输入 #1
```
3
010
000
100
```
### 样例输出 #1
```
4
```
## 提示

对于 $30\%$ 的数据，保证 $N \le 50$。

对于 $100\%$ 的数据，保证 $N \le 200$。


---

---
title: "[JSOI2013] 旅行时的困惑"
layout: "post"
diff: 提高+/省选-
pid: P5258
tag: ['贪心', '2013', '各省省选', '江苏', 'O2优化', '上下界网络流']
---
# [JSOI2013] 旅行时的困惑
## 题目描述

Waldives 有 $N$ 个小岛。目前的交通系统中包含 $N-1$ 条快艇专线，每条快艇专线连接两个岛。这 $N-1$ 条快艇专线恰好形成了一棵树。

由于特殊的原因，所有 $N-1$ 条快艇专线都是单向的。这导致了很多岛屿之间
不能相互到达。因此，Waldives 政府希望新建一些公交线路，使得建设完毕后，任意两个小岛都可以互相到达。为了节约开支，政府希望建设最少的公交线路。 

同时，出于规划考虑，每一条公交线路都有如下的要求：
> 1、每一条交通线路包含若干条连续的快艇专线，你可以认为一条公交线路
对应树上的一条路径，而其所包含的若干快艇专线则对应树上被这条路
径所覆盖的树边（也就是之前已经存在的某个快艇专线）；
>
> 2、显然一条交通线路只能覆盖树上任意一条边至多一次；
>
> 3、公交线路中所包含的每一个快艇专线都是有方向的，并且与其所覆盖的
树边的方向相反；
>
>4、不同的公交线路可以覆盖树上相同的点或者相同的边。

Waldives 的 $N$ 个岛屿分别从 $0$ 到 $N-1$ 编号。现在给出 Waldives 已有的快艇专线信息，请计算最少所需要新建的交通线路的数量。
## 输入格式

第一行包含一个整数 $N$。

接下来 $N-1$行，每行包含两个整数 $x,~y$。表示存在一条从岛屿 $x$ 开往岛屿 $y$ 的快艇专线。
## 输出格式

输出一行一个整数，表示需要建设的最少的交通线路数量。
## 样例

### 样例输入 #1
```
4
0 1
1 2
1 3
```
### 样例输出 #1
```
2
```
## 提示

$1~\leq~N~\leq~10^5$


---

---
title: "[SHOI2002] 舞会"
layout: "post"
diff: 提高+/省选-
pid: P6268
tag: ['2002', '各省省选', '网络流', '上海', '图论建模', '二分图']
---
# [SHOI2002] 舞会
## 题目描述

某学校要召开一个舞会。已知学校所有 $n$ 名学生中，有些学生曾经互相跳过舞。当然跳过舞的学生一定是一个男生和一个女生。在这个舞会上，要求被邀请的学生中的任何一对男生和女生互相都不能跳过舞。求这个舞会最多能邀请多少个学生参加。
## 输入格式

输入的第一行是 $n$ 和 $m$ 。其中 $n$ 是可选的学生的总数， $m$ 是已知跳过舞的学生的对数 ( $n \leq 1000$ ， $m \leq 2000$ ）。

然后有 $m$ 行，每行包括两个非负整数，表示这两个编号的学生曾经跳过舞。学生的编号从 $0$ 号到 $n - 1$ 号。
## 输出格式

输出文件仅一行，为一个数字，即能够邀请的最多的学生数。
## 样例

### 样例输入 #1
```
8 6
0 2
2 3
3 5
1 4
1 6
3 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
20 5
5 2
4 3
18 17
0 11
13 3

```
### 样例输出 #2
```
16
```


---

---
title: "[COCI 2015/2016 #3] DOMINO"
layout: "post"
diff: 提高+/省选-
pid: P7231
tag: ['2015', '网络流', '最短路', '费用流', '前缀和', 'COCI（克罗地亚）']
---
# [COCI 2015/2016 #3] DOMINO
## 题目背景

「誕生日おめでとう！!」

小 M 收到了他女朋友的生日祝福和一份礼物。
## 题目描述

小 M 的女朋友送小 M 了一张 $n \times n$ 的表格作为生日礼物，在表格的每个单元格中都写有一个非负整数。

不幸的是，有些单元格里数字太大了，小 M 不喜欢它们，所以他将在表格上面放置 $k$ 张骨牌，将覆盖那些数字太大的单元格。

更准确地说，小 M 按照以下规则放置骨牌。

- 骨牌为 $1\times 2$ 的矩形，不能拆开放置。
- 骨牌不重叠（但可以接触）。
- 所有可见（未覆盖）字段的总和需要尽可能的小。

您的任务是确定最小可见区域的数字的总和。数据保证可防止 $k$ 个骨牌且无重叠。
## 输入格式

第一行，$2$ 个正整数 $n,k$，$n$ 表示表格的尺寸， $k$ 表示骨牌的数量。

接下来 $n$ 行，每一行都有 $n$ 个整数 $a_i$。这些 $n \times n$ 的数字的数字描述了 Mirko 的表格。
## 输出格式

一行一个整数，最小可见区域的数字的总和。
## 样例

### 样例输入 #1
```
3 1
2 7 6
9 5 1
4 3 8

```
### 样例输出 #1
```
31
```
### 样例输入 #2
```
4 2
1 2 4 0
4 0 5 4
0 3 5 1
1 0 4 1

```
### 样例输出 #2
```
17
```
## 提示

#### 数据规模及约定
对于 $100\%$ 的数据，$1\le n \le 2 \times 10 ^ 3$，$1\le k \le 8$，$0 \le a_i \le 10 ^ 3$。

#### 说明
翻译自 [COCI 2015-2016 #3 F DOMINO](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 160。


---

---
title: "[USACO05NOV] Asteroids G"
layout: "post"
diff: 提高+/省选-
pid: P7368
tag: ['2005', 'USACO', '网络流', '二分图']
---
# [USACO05NOV] Asteroids G
## 题目描述

贝茜想在 $N\times N$ 的网格中驾驶她的宇宙飞船。网格中有 $K$ 个小行星。要使驾驶过程愉快，就必须把这些小行星全部消除。

贝茜有一个武器，可以以一个单位代价消除一行或一列的全部小行星。贝茜想问你，要把所有小行星都消除的最小代价是多少。
## 输入格式

第一行两个整数 $N,K$。

接下来 $K$ 行，每行输入 $x_i,y_i$，表示第 $i$ 个小行星在网格的坐标。
## 输出格式

一行一个整数，表示把所有小行星消除的最小代价。
## 样例

### 样例输入 #1
```
3 4
1 1
1 3
2 2
3 2


```
### 样例输出 #1
```
2
```
## 提示

#### 样例解释：

样例的图为（`X` 为小行星）：

```text
X.X
.X.
.X.
```

贝茜可以分别消除第一行和第二列的小行星。

---

#### 数据范围：

对于 $100\%$ 的数据，$1 \leq N \leq 500$，$1 \leq K \leq N \times N$。


---

---
title: "[USACO22JAN] Cereal 2 S"
layout: "post"
diff: 提高+/省选-
pid: P8095
tag: ['USACO', '2022', '网络流', 'Special Judge', '图论建模', '构造']
---
# [USACO22JAN] Cereal 2 S
## 题目描述

Farmer John 的奶牛们的早餐最爱当然是麦片了！事实上，奶牛们的胃口是如此之大，每头奶牛一顿饭可以吃掉整整一箱麦片。

最近农场收到了一份快递，内有 $M$ 种不同种类的麦片（$2\le M\le 10^5$）。不幸的是，每种麦片只有一箱！$N$ 头奶牛（$1\le N\le 10^5$）中的每头都有她最爱的麦片和第二喜爱的麦片。给定一些可选的麦片，奶牛会执行如下的过程：

- 如果她最爱的麦片还在，取走并离开。

- 否则，如果她第二喜爱的麦片还在，取走并离开。

- 否则，她会失望地哞叫一声然后不带走一片麦片地离开。

当你最优地排列这些奶牛时，求饥饿的奶牛的最小数量。同时，求出任意一个可以达到此最小值的 $N$ 头奶牛的排列。

## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $M$。

对于每一个 $1\le i\le N$，第 $i$ 行包含两个空格分隔的整数 $f_i$ 和 $s_i$（$1\le f_i,s_i\le M$，且 $f_i\neq s_i$），为第 $i$ 头奶牛最喜爱和第二喜爱的麦片。
## 输出格式

输出饥饿的奶牛的最小数量，并输出任意一个可以达到此最小值的 $1\ldots N$ 的排列。如果有多个符合要求的排列，输出任意一个。
## 样例

### 样例输入 #1
```
8 10
2 1
3 4
2 3
6 5
7 8
6 7
7 5
5 8
```
### 样例输出 #1
```
1
1
3
2
8
4
6
5
7
```
## 提示

【样例解释】

在这个例子中，有 $8$ 头奶牛和 $10$ 种麦片。

注意我们对前三头奶牛独立于后五头奶牛求解，因为她们没有共同喜欢的麦片。

如果前三头奶牛按顺序 $[1,2,3]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $2$ 会选择麦片 $3$，奶牛 $3$ 会饥饿。

如果前三头奶牛按顺序 $[1,3,2]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $3$ 会选择麦片 $3$，奶牛 $2$ 会选择麦片 $4$；没有奶牛会饥饿。

当然，还存在其他排列使得前三头奶牛均不饥饿。例如，如果前三头奶牛按顺序 $[3,1,2]$ 选择，则奶牛 $3$ 会选择麦片 $2$，奶牛 $1$ 会选择麦片 $1$，奶牛 $2$ 会选择麦片 $3$；同样，奶牛 $[1,2,3]$ 均不会饥饿。

可以证明在后五头奶牛中，至少一头会饥饿。

【数据范围】

- $14$ 个测试点中的 $4$ 个测试点满足 $N,M\le 100$。

- $14$ 个测试点中的 $10$ 个测试点没有额外限制。

【说明】

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/hi36jkwh)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或[发帖](https://www.luogu.com.cn/discuss/lists?forumname=P8095)。


---

---
title: "「SvR-2」1+2=3"
layout: "post"
diff: 提高+/省选-
pid: P9088
tag: ['贪心', '2023', '网络流', '洛谷原创', 'O2优化', '图论建模', '欧拉回路', '费用流', '洛谷月赛', 'Ad-hoc']
---
# 「SvR-2」1+2=3
## 题目描述

你有一些木棒，每个木棒左边有一个数，右边有一个数，数只有 $0,1,2$，你要将所有木棒拼起来，使相邻的数和为 $3$ 的对数最大。

例如，$1\text{ - }2$ 和 $1\text{ - }0$ 两个木棒，如果按 $1\text{ - }0,1\text{ - }2$ 这样拼，相邻的数和为 $3$ 的对数是 $0$；而按 $1\text{ - }{\underline\color{red}\textbf2},{\underline\color{red}\textbf1}\text{ - }0$ 这样拼相邻的数和为 $3$ 的对数是 $1$，因为 $2+1=3$。
## 输入格式

**本题有多组数据。**

输入的第一行一个正整数表示数据组数 $T$。

对于每组数据，一行 $9$ 个非负整数，分别表示 $0\text{ - }0,0\text{ - }1,0\text{ - }2,1\text{ - }0,1\text{ - }1,1\text{ - }2,2\text{ - }0,2\text{ - }1,2\text{ - }2$ 型木棒的个数。
## 输出格式

$T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
4 1 3 4 7 7 9 10 3
6 3 6 4 3 4 5 6 6
6 10 7 1 4 2 6 4 2

```
### 样例输出 #1
```
31
23
19

```
## 提示

#### 数据规模与约定

对于全部数据，保证 $1\le T\le 10^5$，记 $a_{i,j}$ 表示 $i\text-j$ 木棒的个数，保证 $0\le a_{i,j}\le 10^9$。

**本题自动开启捆绑测试和 O2 优化。**

记 $sum$ 表示一个测试点中所有数据的所有 $a_{i,j}$ 之和。

| Subtask | $T$ | $sum$ | 特殊性质 |分值 |
| :------: | :------: | :------: | :------: | :------: |
| $1$ | $1 \leq T \leq 10$ | $1\le sum\le 10$ |无| $10 \operatorname{pts}$ |
| $2$ | $1 \leq T \leq 50$ | $1\le sum\le 80$ | 无|$20 \operatorname{pts}$ |
| $3$ | 无特殊限制 | 无特殊限制 |A| $15\operatorname{pts}$ |
| $4$ | 无特殊限制 | 无特殊限制 |B| $20 \operatorname{pts}$ |
| $5$ | $1\le T\le 1000$ | 无特殊限制 |C| $20 \operatorname{pts}$ |
| $6$ | 无特殊限制 | 无特殊限制 |无| $15 \operatorname{pts}$ |

特殊性质 A：$a_{i,j}$ 在 $[0,10^9]$ 中均匀随机生成。

特殊性质 B：所有 $a_{i,j}>0$。

特殊性质 C：所有 $a_{i,j}\le 100$。


---

---
title: "[ICPC 2022 Xi'an R] Cells Coloring"
layout: "post"
diff: 提高+/省选-
pid: P9359
tag: ['2022', '网络流', 'O2优化', '二分图', 'ICPC']
---
# [ICPC 2022 Xi'an R] Cells Coloring
## 题目描述

You are given an $n \times m$ grid. Some of the cells are obstacles, the others are empty. Choose a non-negative integer $k$ and color all empty cells with $k+1$ colors $0, 1, 2, \ldots k$. You can not color two cells in the same row or same column with the same **non-zero** color. 

You are given two non-negative integers $c$ and $d$. For a coloring plan, define $z$ as the number of the cells with color $0$. Define the cost of the plan is $ck+dz$.

Find the minimum cost.
## 输入格式

The first line contains four integers $n$, $m$ ($1\leq n, m\leq 250$), $c$ and $d$ ($0\leq c, d\leq 10 ^ 9$).

The $i$-th line of the next $n$ lines contains a string of $m$ characters. The $j$-th character is `*` if the cell in the $i$-th row and the $j$-th column is an obstacle. The $j$-th character is `.` if the cell in the $i$-th row and the $j$-th column is empty.
## 输出格式

Output a line with a single number, representing the answer.
## 样例

### 样例输入 #1
```
3 4 2 1
.***
*..*
**..

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
3 4 1 2
.***
*..*
**..

```
### 样例输出 #2
```
2
```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem B.

**Author**: csy2005.
## 题目翻译

### 题目描述

给定一个 $n\times m$ 的网格。一些格子是障碍，其它格子是空的。选择一个非负整数 $k$，并用 $k + 1$ 种颜色 $0, 1, \ldots, k$ 给空格子染色。不能有同一行或同一列的两个格子被染成了相同的 **非零** 颜色。

给定两个非负整数 $c, d$。对于一组染色方案，定义 $z$ 表示染成颜色 $0$ 的格子数量，则该方案的代价为 $ck + dz$。

求出最小代价。

$1\leq n, m \leq 250$，$0\leq c, d\leq 10 ^ 9$。

### 输入格式

第一行四个整数 $n, m, c, d$。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串。字符串的第 $j$ 个字符为 `*` 表示第 $i$ 行第 $j$ 列的格子为障碍，为 `.` 表示为空。

### 输出格式

输出一行一个整数表示答案。




---

---
title: "「TFOI R1」Unknown Graph"
layout: "post"
diff: 提高+/省选-
pid: P9705
tag: ['网络流', 'Special Judge', 'O2优化', '图论建模']
---
# 「TFOI R1」Unknown Graph
## 题目背景

小 A 飘到了一个岛屿群里，这些岛屿都有单向桥相连接，没有两座桥连接的起始岛屿和终止岛屿都相同，更不会有桥连接一个岛屿。

但这里全是迷雾，小 A 在一个岛上只能看到这个岛与多少座桥相连。

小 A 想要知道整个岛屿群的形态，但是他并不会，所以找到了你。

如果有多种情况，你只需要告诉小 A 任意一种就行。
## 题目描述

有一张 $n$ 个节点的**无重边无自环的有向图**（可以不连通），每个节点的编号为 $1 \sim n$，你知道每个节点的入度和出度。

另外还有 $m$ 条限制，每条限制给定两个点 $x_{i}$ 和 $y_{i}$，表示图中不存在有向边 $(x_{i}, y_{i})$，请你求出一种满足要求的图的形态。

若有多种情况，输出任意一种即可，保证有解。
## 输入格式

第一行一个正整数 $n$ 表示节点数量。

第二行 $n$ 个整数 $a_{i}$，表示编号为 $i$ 的节点的入度为 $a_{i}$。

第三行 $n$ 个整数 $b_{i}$，表示编号为 $i$ 的节点的出度为 $b_{i}$。

第四行一个整数 $m$，表示限制个数。

对于接下来的 $m$ 行，每行两个正整数 $x_{i}, y_{i}$ 表示一组限制。
## 输出格式

第一行一个正整数 $k$ 表示满足限制的图有多少条边。

接下来 $k$ 行，每行两个正整数 $u_{i}$ 和 $v_{i}$ 表示编号为 $u_{i}$ 的结点和编号为 $v_{i}$ 的结点之间有一条有向边。
## 样例

### 样例输入 #1
```
4
2 3 2 3
2 3 2 3
1
1 3
```
### 样例输出 #1
```
10
1 2
2 1
2 3
3 2
2 4
4 2
4 1
1 4
4 3
3 4
```
## 提示

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leqslant 10$。
- Subtask 2（10 points）：$n = 10^3$，$a_{i} = b_{i} = 1$，$m = 0$。
- Subtask 3（20 points）：$n \leqslant 100$。
- Subtask 4（60 points）：无特殊限制。

对于所有数据，$2 \leqslant n \leqslant 10^{3}$，$0 \leqslant a_{i}, b_{i} < n$，$1\leqslant \sum{a_i} \leqslant 10^{5}$，$0 \leqslant m \leqslant 5 \times 10^4$，$1 \leqslant x_i,y_i \leqslant n$。


---

