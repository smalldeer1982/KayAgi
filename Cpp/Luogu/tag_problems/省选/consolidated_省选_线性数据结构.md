---
title: "火枪打怪"
layout: "post"
diff: 省选/NOI-
pid: P1485
tag: ['线性数据结构', '二分']
---
# 火枪打怪
## 题目描述

LXL 进入到了一片丛林,结果他发现有 $n$ 只怪物排成一排站在他面前。LXL 有一杆火枪能对付这些怪物。他知道从左至右数第 $i$ 只怪物的血量是 $m_i$。现在 LXL 可以将一些子弹射向某个怪物。LXL 可以控制他所发射的子弹数量及子弹的威力值。当某个子弹射到第 $i$ 个怪物，如果这个子弹的威力值为 $p$，除了这个怪物会掉 $p$ 点血以外，它左边的第 $j$ 个怪物 $(j<i)$，也会遭到 $\max(0, p - (i - j)^2)$ 的溅射伤害（好神奇的子弹）。当某只怪物的血量小于 $0$ 时，它就死了，但它的尸体还在，即怪物的位置永远不会改变。LXL 希望只用 $k$ 发子弹，请你求出一个最小的正整数 $p$，使 LXL 用 $k$ 发子弹且每发子弹的威力值为 $p$ 就可以消灭所有怪物。

## 输入格式

第一行，两个正整数 $n,k$。

第二行，$n$ 个正整数，第 $i$ 个正整数表示从左至右数第 $i$ 只怪物的血量 $m_i$。

## 输出格式

一个正整数，表示子弹的最小威力值 $p$。

## 样例

### 样例输入 #1
```
3 1
1 4 5

```
### 样例输出 #1
```
6
```
## 提示

对于 $30\%$ 的数据，$n\leq 300$。

对于 $100\%$ 的数据，$n\leq 5\times 10^5$，$k\leq 5\times 10^5$，$1\leq m_i\leq 10^{10}$。



---

---
title: "杀蚂蚁"
layout: "post"
diff: 省选/NOI-
pid: P2198
tag: ['动态规划 DP', '线性数据结构']
---
# 杀蚂蚁
## 题目背景

说“善有善报，恶有恶报，不是不报……”。小 FF 一心只顾自己企业的壮大而没顾及自己的采矿业对 Greed Island 上生态环境的破坏，Greed Island 的环境日益恶劣。终于，岛上的蚂蚁们变异了，它们决定对小 FF 的矿区进行攻击，欲将岛上的人类驱逐出去……面对蚂蚁们的进攻，人类节节败退。无奈之下，小 FF 请来了全宇宙最强的防御系统制造商派来的工程机器人——SCV，希望能够阻挡蚂蚁的攻势。


## 题目描述

经过小 FF 的研究，他发现蚂蚁们每次都走同一条长度为 $n$ 个单位的路线进攻，且蚂蚁们的经过一个单位长度所需的时间为 $T$ 秒。也就是说，只要小 FF 在条路线上布防且给蚂蚁造成沉痛伤害就能阻止蚂蚁的进军。

SCV 擅长制造的防御塔有三种，分别是激光塔，放射塔和干扰塔，他们可以在一个单位长度内修建一座防御塔。三种防御塔的作用如下：

激光塔：使用高能激光，当蚂蚁从塔前经过时每秒对蚂蚁造成 $r$ 点伤害。

放射塔：释放放射性元素，当蚂蚁经过这座塔后，每一秒受到 $g$ 点伤害。

干扰塔：干扰塔负责干扰蚂蚁们的信息素，使得蚂蚁在经过这座塔后，经过之后每一个单位长度的时间变成 $T+b$。

当然，放射塔和干扰塔的效果是可以叠加的，也就是说如果敌人经过 $x$ 座放射塔，那么敌人每秒钟会受到 $x \times g$ 点伤害；同理，如果敌人经过 $y$ 座干扰塔，那么敌人经过一个单位长度的时间将变为 $T + y \times b$。

现在距离蚂蚁的下一轮进攻还有足够长的时间，你这个“NewBe\_One”计划的首席工程师现在被任命为战略总参谋长，因此你必须设计一个给蚂蚁们造成最大伤害的布塔方案。
## 输入格式

输入数据仅一行，$5$ 个整数 $n,r,g,b,T$ 中间用一个空格隔开。它们分别表示你可以布防的总长度，激光塔的效果、放射塔的效果和干扰塔的效果。
## 输出格式

输出仅一个整数，代表你的方案给敌人带来的最大伤害值。
## 样例

### 样例输入 #1
```
5 4 3 2 1
```
### 样例输出 #1
```
82
```
## 提示

#### 样例解释

第 $1$ 号位置为放射塔，第 $2,3$ 号位置建造干扰塔，第 $4,5$ 号位置建造激光塔。

#### 数据范围

对于 $30\%$ 的数据：$1 \leq n \leq 20$；

对于 $60\%$ 的数据：$1 \leq n \leq 1024,0 \leq r,g,b \leq 65536,0 \leq T \leq 3$；

对于另外 $40\%$ 的数据：$1 \leq n \leq 400,0 \leq r,g,b \leq 2^{31}-1,0 \leq t \leq 1000$。


---

---
title: "不同子串个数"
layout: "post"
diff: 省选/NOI-
pid: P2408
tag: ['字符串', '动态规划 DP', '线性数据结构', '后缀自动机 SAM']
---
# 不同子串个数
## 题目背景

因为 NOI 被虐傻了，蒟蒻的 YJQ 准备来学习一下字符串，于是它碰到了这样一道题：

## 题目描述

给你一个长为 $n$ 的字符串，求不同的子串的个数。

我们定义两个子串不同，当且仅当有这两个子串长度不一样或者长度一样且有任意一位不一样。

子串的定义：原字符串中连续的一段字符组成的字符串。

## 输入格式

第一行一个整数 $n$。

接下来一行 $n$ 个字符表示给出的字符串。

## 输出格式

一行一个整数，表示不一样的子串个数。

## 样例

### 样例输入 #1
```
5
aabaa
```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
3
aba
```
### 样例输出 #2
```
5
```
## 提示

### 提示

请使用64位整数来进行输出。

### 数据规模与约定
- 对于 $30\%$ 的数据，保证 $n\le 1000$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \le 10^5$，字符串中只有小写英文字母。



---

---
title: "[POI 2014] PRZ-Criminals"
layout: "post"
diff: 省选/NOI-
pid: P3570
tag: ['2014', '线性数据结构', 'POI（波兰）', '枚举']
---
# [POI 2014] PRZ-Criminals
## 题目描述

Byteburg is a beautiful town by a river.

There are $n$ houses along the river, numbered downstream with successive integers from $1$ to $n$.

Byteburg used to be a nice quiet town in which everyone was happy.

Alas, this changed recently, as two dangerous criminals - Bitie and Bytie set up shop in it.

They did so many robberies already that the citizens are afraid to leave their houses.

Bitie and Bytie do no mere burglaries but rather whole raids: each time they leave their houses and walk towards each other, never turning back.

Bitie walks downstream (towards larger numbers) while Bytie walks upstream (towards smaller numbers).

Along the way, before they meet, each chooses several houses to break into and steal precious items    (and vital data).

After the robberies they meet in a house and divide their loot.

Byteburgers are sick of this already - they would all rather have their tranquility restored.

So they asked the detective Bythony for help.

The detective established that the bandits live in houses of the same color but he does not know which one.

Just a moment ago, an anonymous tip claimed that the robbers are on a raid.

Fearing for their own safety, the source did not say which houses will be broken into.

They did however specify their colors.

As it turns out, the bandits are quite superstitious - each of them will rob a house of each color at most once.

Bythony can wait no longer.

He intends to ambush the criminals at their meeting place.

Aid Bythony in his undertaking by writing a program to find all possible meeting places of the robbers.

## 输入格式

There are two integers in the first line of the standard input, $n$ and $k$ ($3\le n\le 1\ 000\ 000$, $1\le k\le 1\ 000\ 000$, $k\le n$),  separated by a single space, that specify the number of houses and the number of house colors  in Byteburg respectively.

The colors are number with successive integers from $1$ to $k$.

In the second line of input, there is a sequence of $n$ integers, $c_1,c_2,\cdots,c_n$ ($1\le c_i\le k$), separated by single spaces.

These are the colors of successive houses in Byteburg.

In the third line of input, there are two integers $m$ and $l$($1\le m,l\le n$,$m+l\le n-1$), separated by a single space, specifying the numbers of houses (to be) broken into by Bitie and Bytie respectively. In the fourth line of input, there are $m$ pairwise different integers $x_1,x_2,\cdots,x_m$($1\le x_i\le k$), separated by single spaces. These are the colors of houses robbed by Bitie in the order of being broken into (i.e., excluding Bitie's house). In the fifth, which is the last, line of input, there are $l$ pairwise different integers $y_1,y_2,\cdots,y_l$ ($1\le y_i\le k$), separated by single spaces. These are the colors of houses robbed by Bytie in the order of being broken into (again, these do not include Bytie's house). Moreover, $x_m=y_l$ is the color of the house in which the robbers will divide the plunder. (Clearly, they have to break into that one as well!)

## 输出格式

Your program it to print exactly two lines to the standard output.

The first of those should give the number of houses in which the criminals can meet  while respecting aforementioned constraints.

The second line should contain the increasing sequence of the numbers of those houses,  separated by single spaces.

If the robbers cannot meet at all, the first line should contain the number 0 while the second one should be empty.

## 样例

### 样例输入 #1
```
15 7
2 5 6 2 4 7 3 3 2 3 7 5 3 6 2
3 2
4 7 3
5 3

```
### 样例输出 #1
```
3
7 8 10

```
## 题目翻译

## 题目描述

两个罪犯 Bitie 和 Bytie 抢劫 $n$ 个房子，每个房子有一个颜色，Bitie 从低编号到高编号，Bytie 从高编号到低编号，直到相遇为止。已知罪犯开始时所在房子颜色相同（但不知道是什么颜色），并且知道罪犯依次抢劫的所有房子的颜色，且每个罪犯对每种颜色的房子分别最多抢劫一次，求所有可能的相遇点。

## 输入格式

第一行两个整数 $n,k$ ，分别表示房子的个数和不同的颜色数。颜色以从 $1$ 到 $k$ 的整数标号。

接下来一行有 $n$ 个整数 $c_1,c_2,...,c_n (1 \le c_i \le k)$，表示房子的颜色。

第三行有两个整数 $m,l (1 \le m,l \le n,m+l \le n-1)$，分别表示 Bitie 和 Bytie 抢劫房子的个数。

第四行有 $m$ 个两两不同的整数 $x_1, x_2, ..., x_m (1 \le x_i \le k)$，表示 Bitie 抢劫房子的颜色（不包括 Bitie 开始时所在房子的颜色）。

第五行有 $l$ 个两两不同的整数 $y_1, y_2, ..., y_l (1 \le y_i \le k)$，表示 Bytie 抢劫房子的颜色 （不包括 Bytie 开始时所在房子的颜色）。

保证 $x_m = y_l$。

## 输出格式

输出两行，第一行一个整数，表示可能相遇的房子个数，第二行升序输出可能相遇的房子编号。


---

