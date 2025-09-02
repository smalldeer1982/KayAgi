---
title: "BZOJ2989 数列/BZOJ4170 极光"
layout: "post"
diff: 提高+/省选-
pid: P10633
tag: ['树状数组', 'cdq 分治', 'O2优化']
---
# BZOJ2989 数列/BZOJ4170 极光
## 题目描述

给定一个长度为 $n$ 的正整数数列 $a_i$，两个位置的 $\text{graze}$ 值为两者位置差与数值差的和：$\text{graze}(x,y)=|x-y|+|a_x-a_y|$。

你必须支持两种操作（$k$ 都是正整数）：
- `Modify x k`，表示将第 $x$ 个数的值修改为 $k$；
- `Query x k`，表示询问有几个 $i$ 满足 $\text{graze}(x,i) \leq k$；

询问不仅要考虑当前数列，还要考虑任意历史版本，即统计任意位置上出现过的任意数值与当前的 $a_x$ 的 $\text{graze}$ 值 $\leq k$ 的对数。（某位置多次修改为同样的数值，按多次统计。）
## 输入格式

第一行两个整数 $n,q$，表示数列长度与操作数；

第二行 $n$ 个正整数，代表初始数列。

第 $3\sim q+2$ 行，每行一个操作。
## 输出格式

对于每次询问操作，输出一个非负整数表示答案。
## 样例

### 样例输入 #1
```
3 5
2 4 3
Query 2 2
Modify 1 3
Query 2 2
Modify 1 2
Query 1 1
```
### 样例输出 #1
```
2
3
3
```
## 提示

对于所有数据，保证 $1\leq n\leq 6\times 10^4$，$1\leq$ 修改操作数 $\leq 5\times 10^4$，$1\leq$ 询问次数 $\leq 6\times 10^4$，$1\leq a_i$ 的所有历史版本的最大值 $\leq 10^5$。


---

---
title: "[国家集训队] 排队 加强版"
layout: "post"
diff: 提高+/省选-
pid: P12685
tag: ['线段树', '平衡树', '集训队互测', '树状数组', 'cdq 分治', '树套树', '分块']
---
# [国家集训队] 排队 加强版
## 题目背景

[P1975](https://www.luogu.com.cn/problem/P1975) 的加强版，两题中仅数据范围不同。
## 题目描述

排排坐，吃果果，生果甜嗦嗦，大家笑呵呵。你一个，我一个，大的分给你，小的留给我，吃完果果唱支歌，大家乐和和。

红星幼儿园的小朋友们排起了长长地队伍，准备吃果果。不过因为小朋友们的身高有所区别，排成的队伍高低错乱，极不美观。设第 $i$ 个小朋友的身高为 $h_i$。

幼儿园阿姨每次会选出两个小朋友，交换他们的位置，请你帮忙计算出每次交换后，序列的逆序对数。为方便幼儿园阿姨统计，在未进行任何交换操作时，你也应该输出该序列的逆序对数。
## 输入格式

第一行为一个正整数 $n$，表示小朋友的数量；

第二行包含 $n$ 个由空格分隔的正整数 $h_1,h_2,\dots,h_n$，依次表示初始队列中小朋友的身高；

第三行为一个正整数 $m$，表示交换操作的次数；

以下m行每行包含两个正整数 $a_i,b_i$，表示交换位置 $a_i$ 和 $b_i$ 的小朋友。
## 输出格式

输出文件共 $m+1$ 行，第 $i$ 行一个正整数表示交换操作 $i$ 结束后，序列的逆序对数。
## 样例

### 样例输入 #1
```
3
130 150 140
2
2 3
1 3
```
### 样例输出 #1
```
1
0
3
```
## 提示

### 样例说明 

未进行任何操作时，$(2,3)$ 为逆序对；  
操作一结束后，序列为 $130 \ 140 \ 150$，不存在逆序对；  
操作二结束后，序列为 $150 \ 140 \ 130$，$(1,2),(1,3),(2,3)$ 共 $3$ 个逆序对。

### 数据范围

对于所有数据，保证：

- $1\le n\le 2\times10^5$
- $1\le m\le 2\times10^5$
- $1\le h_i\le 10^9$
- $1\le a_i,b_i\le n,a_i\neq b_i$


---

---
title: "[SHOI2007] 园丁的烦恼"
layout: "post"
diff: 提高+/省选-
pid: P2163
tag: ['2007', '各省省选', '树状数组', '离散化', '上海', 'cdq 分治']
---
# [SHOI2007] 园丁的烦恼
## 题目背景

很久很久以前，在遥远的大陆上有一个美丽的国家。统治着这个美丽国家的国王是一个园艺爱好者，在他的皇家花园里种植着各种奇花异草。

有一天国王漫步在花园里，若有所思，他问一个园丁道： “最近我在思索一个问题，如果我们把花坛摆成六个六角形，那么……”

“那么本质上它是一个深度优先搜索，陛下。”园丁深深地向国王鞠了一躬。

“嗯……我听说有一种怪物叫九头蛇，它非常贪吃苹果树……”

“是的，显然这是一道经典的动态规划题，早在 N 元 $4002$ 年我们就已经发现了其中的奥秘了，陛下。”

“该死的，你究竟是什么来头？”

“陛下息怒，干我们的这行经常莫名其妙地被问到和 OI 有关的题目，我也是为了预防万一啊！” 王者的尊严受到了伤害，这是不可容忍的。
## 题目描述

看来一般的难题是难不倒这位园丁的，国王最后打算用车轮战来消耗他的实力： “年轻人，在我的花园里有 $n$ 棵树，每一棵树可以用一个整数坐标来表示，一会儿，我的 $m$ 个骑士们会来轮番询问你某一个矩阵内有多少树，如果你不能立即答对，你就准备走人吧！”说完，国王气呼呼地先走了。

这下轮到园丁傻眼了，他没有准备过这样的问题。所幸的是，作为“全国园丁保护联盟”的会长——你，可以成为他的最后一根救命稻草。
## 输入格式

第一行有两个整数 $n, m$，分别表示树木个数和询问次数。

接下来 $n$ 行，每行两个整数 $x, y$，表示存在一棵坐标为 $(x, y)$ 的树。有可能存在两棵树位于同一坐标。

接下来 $m$ 行，每行四个整数 $a, b, c, d$，表示查询以 $(a, b)$ 为左下角，$(c, d)$ 为右上角的矩形内部（包括边界）有多少棵树。

## 输出格式

对于每个查询，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 1
0 0 
0 1
1 0
0 0 1 1

```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n, m \leq 10$。
- 对于 $100\%$ 的数据，保证 $0 \leq n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq x, y, a, b, c, d \leq 10^7$，$a \leq c$，$b \leq d$。


---

---
title: "任务安排"
layout: "post"
diff: 提高+/省选-
pid: P2365
tag: ['动态规划 DP', 'cdq 分治', '斜率优化']
---
# 任务安排
## 题目描述

$n$ 个任务排成一个序列在一台机器上等待完成（顺序不得改变），这 $n$ 个任务被分成若干批，每批包含相邻的若干任务。  

从零时刻开始，这些任务被分批加工，第 $i$ 个任务单独完成所需的时间为 $t_i$。在每批任务开始前，机器需要启动时间 $s$，而完成这批任务所需的时间是各个任务需要时间的总和（同一批任务将在同一时刻完成）。  

每个任务的费用是它的完成时刻乘以一个费用系数 $f_i$。请确定一个分组方案，使得总费用最小。

## 输入格式

第一行一个正整数 $n$。  
第二行是一个整数 $s$。

下面 $n$ 行每行有一对数，分别为 $t_i$ 和 $f_i$，表示第 $i$ 个任务单独完成所需的时间是 $t_i$ 及其费用系数 $f_i$。

## 输出格式

一个数，最小的总费用。

## 样例

### 样例输入 #1
```
5
1
1 3
3 2
4 3
2 3
1 4
```
### 样例输出 #1
```
153
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 5000$，$0 \le s \le 50$，$1\le t_i,f_i \le 100$。

【样例解释】   
如果分组方案是 $\{1,2\},\{3\},\{4,5\}$，则完成时间分别为 $\{5,5,10,14,14\}$，费用 $C=15+10+30+42+56$，总费用就是 $153$。


---

---
title: "[USACO15FEB] Cow Hopscotch G"
layout: "post"
diff: 提高+/省选-
pid: P3120
tag: ['动态规划 DP', '2015', '线段树', 'USACO', 'cdq 分治', '前缀和']
---
# [USACO15FEB] Cow Hopscotch G
## 题目描述

Just like humans enjoy playing the game of Hopscotch, Farmer John's cows have invented a variant of the game for themselves to play.  Being played by clumsy animals weighing nearly a ton, Cow Hopscotch almost always ends in disaster, but this has surprisingly not deterred the cows from attempting to play nearly every afternoon.

The game is played on an R by C grid (2 <= R <= 750, 2 <= C <= 750), where each square is labeled with an integer in the range 1..K (1 <= K <= R\*C).  Cows start in the top-left square and move to the bottom-right square by a sequence of jumps, where a jump is valid if and only if

1) You are jumping to a square labeled with a different integer than your current square,

2) The square that you are jumping to is at least one row below the current square that you are on, and

3) The square that you are jumping to is at least one column to the right of the current square that you are on.

Please help the cows compute the number of different possible sequences of valid jumps that will take them from the top-left square to the bottom-right square.
## 输入格式

The first line contains the integers R, C, and K.

The next R lines will each contain C integers, each in the range 1..K.
## 输出格式

Output the number of different ways one can jump from the top-left square to the bottom-right square, mod 1000000007.
## 样例

### 样例输入 #1
```
4 4 4 
1 1 1 1 
1 3 2 1 
1 2 4 1 
1 1 1 1 

```
### 样例输出 #1
```
5 

```
## 题目翻译

### 题目描述

与人类喜欢玩跳格子游戏类似，Farmer John 的奶牛们也发明了自己的游戏版本。尽管体重接近一吨的笨拙动物玩这个游戏几乎总会以灾难收场，但这意料之外地没有阻止奶牛们每天下午尝试玩耍的热情。

游戏在一个 $R$ 行 $C$ 列的网格上进行（$2 \leq R, C \leq 750$），每个格子标有 $1$ 到 $K$ 的整数（$1 \leq K \leq R \times C$）。奶牛从左上角的格子出发，通过一系列合法跳跃到达右下角的格子。一次跳跃被定义为合法当且仅当满足以下条件：

1. 目标格子的标签数字与当前格子不同；
2. 目标格子所在行至少比当前格子多一行；
3. 目标格子所在列至少比当前格子多一列。

请帮助奶牛计算从左上角到右下角的不同合法跳跃序列总数。

### 输入格式

第一行包含三个整数 $R$, $C$, $K$。

接下来 $R$ 行，每行包含 $C$ 个整数，表示网格的标签（范围 $1$ 到 $K$）。

### 输出格式

输出从左上角到右下角的不同跳跃路径数量，结果对 $1000000007$ 取模。


---

---
title: "[USACO16JAN] Mowing the Field P"
layout: "post"
diff: 提高+/省选-
pid: P3136
tag: ['2016', 'USACO', 'cdq 分治']
---
# [USACO16JAN] Mowing the Field P
## 题目描述

Farmer John is quite reliable in all aspects of managing his farm, except one: he is terrible at mowing the grass in a timely fashion.   He only manages to move the mowing machine once per day, in fact. On day 1, he starts at position $(x_1, y_1)$ and on day $d$ he mows along a straight segment to the position $(x_d, y_d)$, moving either horizontally or vertically on the 2D map of his farm; that is, either  $x_d = x_{d-1}$, or $y_d = y_{d-1}$.  FJ alternates between horizontal and vertical moves on successive days.


So slow is FJ's progress that some of the grass he mows might grow back before he is finished with all his mowing. Any section of grass that is cut in day $d$ will reappear on day $d + T$, so if FJ's mowing path crosses a path he cut at least $T$ days earlier, he will end up cutting grass at the same point again.  In an effort to try and reform his poor mowing strategy, FJ would like to count the number of times this happens.

Please count the number of times FJ's mowing path crosses over an earlier segment on which grass has already grown back.  You should only count "perpendicular" crossings, defined as a point in common between a horizontal and a vertical segment that is an endpoint of neither.
## 输入格式

The first line of input contains $N$ ($2 \leq N \leq 100,000$) and $T$ ($1 \leq T \leq N$, $T$ even).

The next $N$ lines describe the position of the mower on days $1 \ldots N$.  The $i$-th of these lines contains integers $x_i$ and $y_i$ (nonnegative integers each at most 1,000,000,000).

## 输出格式

Please output a count of the number of crossing points described above, where FJ re-cuts a point of grass that had grown back after being cut earlier.

## 样例

### 样例输入 #1
```
7 4
0 10
10 10
10 5
3 5
3 12
6 12
6 3
```
### 样例输出 #1
```
1
```
## 提示

Here, FJ crosses on day 7 a segment of grass he cut on day 2, which counts. The other intersections do not count.

Note: This problem has expanded limits: 5 seconds per test case (10 for Python and Java), and 512 MB of memory.

## 题目翻译

### 题目描述

Farmer John 在管理农场的各个方面都相当可靠，除了一件事：他非常不擅长及时修剪草地。事实上，他每天只能移动一次割草机。在第 1 天，他从位置 $(x_1, y_1)$ 开始，在第 $d$ 天，他沿着一条直线段移动到位置 $(x_d, y_d)$，在农场的二维地图上，他要么水平移动，要么垂直移动；也就是说，要么 $x_d = x_{d-1}$，要么 $y_d = y_{d-1}$。FJ 在连续的日子里交替进行水平和垂直移动。

FJ 的进展非常缓慢，以至于在他完成所有修剪之前，一些被他修剪过的草可能会重新长出来。任何在第 $d$ 天被修剪的草会在第 $d + T$ 天重新长出来，因此如果 FJ 的修剪路径与至少 $T$ 天前修剪过的路径交叉，他将再次在同一位置修剪草地。为了尝试改进他糟糕的修剪策略，FJ 想要计算这种情况发生的次数。

请计算 FJ 的修剪路径与之前已经重新长草的路径交叉的次数。你只需计算“垂直”交叉，定义为水平线段和垂直线段之间的共同点，且该点不是任何线段的端点。

### 输入格式

输入的第一行包含 $N$（$2 \leq N \leq 100,000$）和 $T$（$1 \leq T \leq N$，$T$ 为偶数）。

接下来的 $N$ 行描述了割草机在第 $1$ 到第 $N$ 天的位置。第 $i$ 行包含整数 $x_i$ 和 $y_i$（每个为非负整数，且不超过 $1,000,000,000$）。

### 输出格式

请输出上述交叉点的数量，即 FJ 重新修剪已经重新长草的点的次数。

### 说明/提示

在这里，FJ 在第 7 天与他在第 2 天修剪的草地路径交叉，这算作一次。其他交叉点不算。

注意：本题有扩展的限制：每个测试用例 5 秒（Python 和 Java 为 10 秒），内存限制为 512 MB。


---

