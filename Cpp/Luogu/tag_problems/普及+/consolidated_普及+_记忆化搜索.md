---
title: "[蓝桥杯 2023 国 Java A] 连续数组"
layout: "post"
diff: 普及+/提高
pid: P12236
tag: ['2023', '记忆化搜索', '蓝桥杯国赛', '状压 DP']
---
# [蓝桥杯 2023 国 Java A] 连续数组
## 题目描述

小蓝对连续数组很感兴趣，对于一个长度为 $N$ 的连续数组 $nums$，$nums$ 中的元素取值范围为 $1 \sim N$，且 $nums$ 中不存在重复元素，每两个相邻的数组元素 $nums[i]$、$nums[i + 1]$ 之间都存在关系($1 \leq i \leq N - 1$)，且只可能是以下两种关系中的一种:

1. 连续，此时 $nums[i + 1]$ 等于 $nums[i] + 1$;
2. 不连续，此时 $nums[i + 1]$ 不等于 $nums[i] + 1$。

现在给出一个长度为 $N$ 的数组中任意相邻的数组元素之间的关系，请问共有多少种满足条件的连续数组？
## 输入格式

输入的第一行包含一个整数 $N$ 表示数组长度。

第二行包含 $N - 1$ 个整数，相邻的整数之间使用一个空格分隔，表示连续数组中相邻元素之间的关系，取值只能是 $0$ (表示不连续关系)或 $1$ (表示连续关系)。其中第 $i$ ($1 \leq i \leq N - 1$)个整数表示 $nums[i]$ 和 $nums[i + 1]$ 之间的关系。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5
0 0 1 1
```
### 样例输出 #1
```
3
```
## 提示

### 样例说明

符合条件的连续数组有：$[1, 5, 2, 3, 4]$、$[2, 1, 3, 4, 5]$、$[5, 4, 1, 2, 3]$。

### 评测用例规模与约定

对于 $30\%$ 的评测用例，$1 \leq N \leq 10$；

对于所有评测用例，$1 \leq N \leq 15$。


---

---
title: "[GCJ 2018 #2] Graceful Chainsaw Jugglers"
layout: "post"
diff: 普及+/提高
pid: P13146
tag: ['动态规划 DP', '2018', '记忆化搜索', 'Google Code Jam']
---
# [GCJ 2018 #2] Graceful Chainsaw Jugglers
## 题目描述

You are the manager of the Graceful Chainsaw Jugglers performance group, and you are trying to succeed in the very competitive chainsaw juggling business. You have an unlimited number of identical talented jugglers, and each of them knows how to juggle any number of chainsaws. To run a show, you will choose some number of jugglers, and then distribute your red chainsaws and blue chainsaws among them, so that each juggler gets at least one chainsaw. For example, one juggler might juggle two red chainsaws and three blue chainsaws, and another juggler might juggle just one red chainsaw. During the show, each chainsaw is used by only one juggler; the jugglers do not pass chainsaws around, because it is already hard enough just to juggle them!

According to your market research, your audience is happiest when the show uses as many jugglers and chainsaws as possible, but the audience also demands variety: no two jugglers in the show can use both the same number of red chainsaws and the same number of blue chainsaws.

You have $R$ red chainsaws and $B$ blue chainsaws, and you must use all of them in the show. What is the largest number of jugglers that you can use in the show while satisfying the audience's demands?

## 输入格式

The first line of the input gives the number of test cases, $T$; $T$ test cases follow. Each test case consists of one line with two integers $R$ and $B$: the numbers of red and blue chainsaws that you must use in the show.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the largest number of jugglers that you can use in the show while satisfying the audience's demands, as described above.
## 样例

### 样例输入 #1
```
2
2 0
4 5
```
### 样例输出 #1
```
Case #1: 1
Case #2: 5
```
## 提示

**Sample Explanation**

In Sample Case #1, the only possible strategy is to give both red chainsaws to one juggler.

In Sample Case #2, one optimal strategy is to have:

- one juggler with one red chainsaw
- one juggler with two red chainsaws
- one juggler with one blue chainsaw
- one juggler with three blue chainsaws
- one juggler with one red chainsaw and one blue chainsaw

**Limits**

- $1 \leq T \leq 100$.
- $R + B > 0$.

**Test set 1 (7 Pts, Visible)**

- $0 \leq R \leq 50$.
- $0 \leq B \leq 50$.

**Test set 2 (17 Pts, Hidden)**

- $0 \leq R \leq 500$.
- $0 \leq B \leq 500$.


---

---
title: "[GCJ 2011 #1A] The Killer Word"
layout: "post"
diff: 普及+/提高
pid: P13366
tag: ['模拟', '2011', '递归', '记忆化搜索', 'Google Code Jam']
---
# [GCJ 2011 #1A] The Killer Word
## 题目描述

You are playing Hangman with your friend Sean. And while you have heard that Sean is very good at taking candy from a baby, he is not as good at this game. Can you take advantage of Sean's imperfect strategy, and make him lose as badly as possible?

```
 +--+
 |  O
 | /|\       Mystery word: _ a _ a _ a _
 | / \
 |
+-+---+
```

Hangman is played as follows:

* There is a dictionary $D$ of all valid words, which both you and Sean know. A word consists only of the characters a - z. In particular, there are no spaces.
* You begin by choosing any word from $D$, and writing it down on a blackboard with each letter replaced by a blank: _.
* On his turn, Sean can choose any letter and ask you if it is in the word. If it is, you reveal all locations of that letter. Otherwise, Sean loses a point.
* Once all letters in the word have been revealed, the round ends.
* The round never ends early, no matter how many points Sean loses.

Sean uses a very simple strategy. He makes a list $L$ of the 26 letters in some order, and goes through the list one letter at a time. If there is at least one word in $D$ that (a) has the letter he is thinking of, and (b) is consistent with what you have written down so far and the result of all of Sean's previous guesses, then Sean guesses that letter. Otherwise, he skips it. No matter what, Sean then moves on to the next letter in his list.

Given Sean's list, what word should you choose to make Sean lose as many as points as possible? If several choices are equally good, you should choose the one that appears first in $D$.

**Example**

Suppose Sean decides to guess the letters in alphabetical order (i.e., $L = $ "abcdefghijklmnopqrstuvwxyz"), and $D$ contains the words banana, caravan, and pajamas. If you choose pajamas, the game would play out as follows:

* You begin by writing 7 blanks _ _ _ _ _ _ _ on the blackboard. Based on the number of blanks, Sean knows immediately that the word is either caravan or pajamas.
* Sean begins by guessing a since it is first in $L$, and you reveal all locations of the letter a on the blackboard: _ a _ a _ a _.
* Sean skips b even though it is used in banana. Sean already knows that is not your word.
* He then guesses c because it appears in caravan. It does not appear in the word you actually chose though, so Sean loses a point and nothing more is revealed.
* By process of elimination, Sean now knows your word has to be pajamas, so he proceeds to guess j, m, p, and s in order, without losing any more points.

So Sean loses one point if you choose pajamas. He would have gotten either of the other words without losing any points.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing integers $N$ and $M$, representing the number of words in the dictionary and the number of lists to consider.

The next $N$ lines contain the words in the dictionary, one per line: $D_1$, $D_2$, ..., $D_N$. Each word is an arbitrary sequence of characters a - z.

The final $M$ lines contain all of the lists Sean will use, one per line: $L_1$, $L_2$, ..., $L_M$. Each list is exactly 26 letters long, containing each letter exactly once. Sean will use these lists to guess letters as described above.

## 输出格式

For each test case, output one line containing "Case #x: $w_1$ $w_2$ ... $w_M$", where $x$ is the case number (starting from 1) and $w_i$ is the word you should choose if Sean guesses the letters in order $L_i$. If multiple words cause Sean to lose the same number of points, you should choose the option that appears first in the dictionary.
## 样例

### 样例输入 #1
```
2
3 2
banana
caravan
pajamas
abcdefghijklmnopqrstuvwxyz
etaoisnhrdlcumwfgypbvkjxqz
4 1
potato
tomato
garlic
pepper
zyxwvutsrqponmlkjihgfedcba
```
### 样例输出 #1
```
Case #1: pajamas caravan
Case #2: garlic
```
## 提示

**Limits**

- $1 \leq T \leq 10$.
- Each word in $D$ will have between $1$ and $10$ characters inclusive.
- No two words in $D$ will be the same within a single test case.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 100$.
- $1 \leq M \leq 10$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 10000$.
- $1 \leq M \leq 100$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2009 #1A] Multi-base happiness"
layout: "post"
diff: 普及+/提高
pid: P13431
tag: ['模拟', '2009', '记忆化搜索', 'Google Code Jam']
---
# [GCJ 2009 #1A] Multi-base happiness
## 题目描述

Given an integer $N$, replace it by the sum of the squares of its digits. A happy number is a number where, if you apply this process repeatedly, it eventually results in the number $1$. For example, if you start with $82$:

```
8*8 + 2*2       = 64 + 4    = 68,  repeat:
6*6 + 8*8       = 36 + 64   = 100, repeat:
1*1 + 0*0 + 0*0 = 1 + 0 + 0 = 1 (happy! :)
```

Since this process resulted in $1$, $82$ is a happy number.

Notice that a number might be happy in some bases, but not happy in others. For instance, the base $10$ number $82$ is not a happy number when written in base $3$ (as $10001$).

You are one of the world's top number detectives. Some of the bases got together (yes, they are organized!) and hired you for an important task: find out what's the smallest integer number that's greater than $1$ and is happy in all the given bases.
## 输入格式

The first line of input gives the number of cases $T$. $T$ test cases follow. Each case consists of a single line. Each line contains a space separated list of distinct integers, representing the bases. The list of bases is always in increasing order.

## 输出格式

For each test case, output:

Case #$X$: $K$

where $X$ is the test case number, starting from 1, and $K$ is the decimal representation of the smallest integer (greater than 1) which is happy in all of the given bases.
## 样例

### 样例输入 #1
```
3
2 3
2 3 7
9 10
```
### 样例输出 #1
```
Case #1: 3
Case #2: 143
Case #3: 91
```
## 提示

**Limits**

- $2 \leq \text{all possible input bases} \leq 10$

**Small dataset(9 Pts)**

- $1 \leq T \leq 42$
- $2 \leq \text{number of bases on each test case} \leq 3$

**Large dataset(18 Pts)**

- $1 \leq T \leq 500$
- $2 \leq \text{number of bases on each test case} \leq 9$



---

---
title: "伊甸园日历游戏"
layout: "post"
diff: 普及+/提高
pid: P1512
tag: ['搜索', '博弈论', '记忆化搜索']
---
# 伊甸园日历游戏
## 题目描述

Adam 和 Eve 玩一个游戏，他们先从 $1900.1.1$ 到 $2006.11.3$ 这个日期之间随意抽取一个日期出来。然后他们轮流对这个日期进行操作：

1. 把日期的天数加 $1$，例如 $1900.1.1$ 变到 $1900.1.2$；
2. 把月份加 $1$，例如：$1900.1.1$ 变到 $1900.2.1$。

其中如果天数超过应有天数则日期变更到下个月的第 $1$ 天。月份超过 $12$ 则变到下一年的 $1$ 月。而且进行操作二的时候，如果有这样的日期：$1900.1.31$，则变成了 $1900.2.31$，这样的操作是非法的，我们不允许这样做。而且所有的操作均要考虑历法和闰年的规定。

谁先将日期变到 $2006.11.4$ 谁就赢了。如果超越了指定日期不算获胜。

每次游戏都是 Adam 先操作，问他有没有必胜策略？
## 输入格式

第一行一个整数，为数据组数。

接下来一行 $X,Y,Z$ 表示 $X$ 年 $Y$ 月 $Z$ 日。
## 输出格式

输出 `YES` 或者 `NO` 表示 Adam 是否有必胜策略。
## 样例

### 样例输入 #1
```
3
2001 11 3
2001 11 2
2001 10 3

```
### 样例输出 #1
```
YES
NO
NO

```
## 提示



------------
2024/1/31 添加一组 hack 数据。


---

---
title: "[SCOI2008] 着色方案"
layout: "post"
diff: 普及+/提高
pid: P2476
tag: ['动态规划 DP', '搜索', '2008', '四川', '各省省选', '记忆化搜索']
---
# [SCOI2008] 着色方案
## 题目描述

有 $n$ 个木块排成一行，从左到右依次编号为 $1$ 至 $n$。

你有 $k$ 种颜色的油漆，第 $i$ 种颜色的油漆足够涂 $c_i$ 个木块。

所有油漆刚好足够涂满所有木块，即 $\sum_{i=1}^kc_i=n$。

由于相邻两个木块涂相同色显得很难看，所以你希望统计任意两个相邻木块颜色不同的着色方案。

由于答案可能很大，请输出对 $10^9+7$ 取模的结果。
## 输入格式

第一行，一个整数 $k$，表示颜色数量。

第二行 $k$ 个整数 $c_1,c_2,\dots,c_k$，表示每种颜色能够涂木块的个数。
## 输出格式

一行一个整数，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5
2 2 2 2 2
```
### 样例输出 #2
```
39480
```
### 样例输入 #3
```
10
1 1 2 2 3 3 4 4 5 5

```
### 样例输出 #3
```
85937576
```
## 提示

- 对于 $50\%$ 的数据，$1 \leq k \leq 5$，$1 \leq c_i \leq 3$；
- 对于 $100\%$ 的数据，$1 \leq k \leq 15$，$1 \leq c_i \leq 5$。


---

---
title: "[USACO08DEC] Trick or Treat on the Farm G"
layout: "post"
diff: 普及+/提高
pid: P2921
tag: ['动态规划 DP', '搜索', '2008', 'USACO', '记忆化搜索']
---
# [USACO08DEC] Trick or Treat on the Farm G
## 题目描述

Every year in Wisconsin the cows celebrate the USA autumn holiday of Halloween by dressing up in costumes and collecting candy that Farmer John leaves in the N (1 <= N <= 100,000) stalls conveniently numbered 1..N.

Because the barn is not so large, FJ makes sure the cows extend their fun by specifying a traversal route the cows must follow.  To implement this scheme for traveling back and forth through the barn, FJ has posted a 'next stall number' next\_i (1 <= next\_i <= N) on stall i that tells the cows which stall to visit next; the cows thus might travel the length of the barn many times in order to collect their candy.

FJ mandates that cow i should start collecting candy at stall i. A cow stops her candy collection if she arrives back at any stall she has already visited.

Calculate the number of unique stalls each cow visits before being forced to stop her candy collection.

POINTS: 100
## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains a single integer: next\_i

## 输出格式

\* Lines 1..N: Line i contains a single integer that is the total number of unique stalls visited by cow i before she returns to a stall  she has previously visited.

## 样例

### 样例输入 #1
```
4 
1 
3 
2 
3 

```
### 样例输出 #1
```
1 
2 
2 
3 

```
## 提示

Four stalls.

\* Stall 1 directs the cow back to stall 1.

\* Stall 2 directs the cow to stall 3

\* Stall 3 directs the cow to stall 2

\* Stall 4 directs the cow to stall 3


Cow 1:  Start at 1, next is 1.  Total stalls visited: 1.

Cow 2:  Start at 2, next is 3, next is 2.  Total stalls visited: 2. Cow 3:  Start at 3, next is 2, next is 3.  Total stalls visited: 2. Cow 4:  Start at 4, next is 3, next is 2, next is 3. Total stalls visited: 3.

## 题目翻译

#### 题目描述

每年，在威斯康星州，奶牛们都会穿上衣服，收集农夫约翰在 $N(1\le N\le 100,000)$ 个牛棚隔间中留下的糖果，以此来庆祝美国秋天的万圣节。

由于牛棚不太大，FJ 通过指定奶牛必须遵循的穿越路线来确保奶牛的乐趣。为了实现这个让奶牛在牛棚里来回穿梭的方案，FJ 在第 $i$ 号隔间上张贴了一个 “下一个隔间：$next_i(1\le next_i\le N)$” 的标语，告诉奶牛要去的下一个隔间。这样，为了收集它们的糖果，奶牛就会在牛棚里来回穿梭了。

FJ 命令奶牛 $i$ 应该从 $i$ 号隔间开始收集糖果。如果一只奶牛回到某一个她已经去过的隔间，她就会停止收集糖果。

在被迫停止收集糖果之前，计算一下每头奶牛要前往的隔间数（包含起点）。

#### 输入格式

第一行一个整数 $n$，表示牛棚隔间的数量。

第 $2$ 至 $n+1$ 行，每行包含一个整数 $next_i$，表示 $i$ 号隔间的下一个隔间。

#### 输出格式

输出共 $n$ 行，第 $i$ 行包含一个整数，表示第 $i$ 只奶牛要前往的隔间数。

#### 样例解释

有 $4$ 个隔间。

- 隔间 $1$ 要求牛到隔间 $1$，

- 隔间 $2$ 要求牛到隔间 $3$，

- 隔间 $3$ 要求牛到隔间 $2$，

- 隔间 $4$ 要求牛到隔间 $3$。

牛 $1$：从 $1\rightarrow 1$，总共访问 $1$ 个隔间；

牛 $2$：$2\rightarrow 3\rightarrow 2$，总共访问 $2$ 个隔间；

牛 $3$：$3\rightarrow 2\rightarrow 3$，总共访问 $2$ 个隔间；

牛 $4$：$4\rightarrow 3\rightarrow 2\rightarrow 3$，总共访问 $3$ 个隔间。

翻译提供者：[busy_programmer](https://www.luogu.com.cn/user/649315)。


---

---
title: "[USACO17JAN] Hoof, Paper, Scissor G"
layout: "post"
diff: 普及+/提高
pid: P3609
tag: ['模拟', '搜索', '2017', 'USACO', '枚举', '记忆化搜索']
---
# [USACO17JAN] Hoof, Paper, Scissor G
## 题目背景

*本题与 [银组同名题目](/problem/P6120) 在题意上一致，唯一的差别在于对变手势次数的限制。*

## 题目描述

你可能玩过“石头，剪刀，布”，这个游戏在奶牛中同样流行，不过它的名字变成了“蹄子，剪刀，布”。

“蹄子，剪刀，布”和“石头，剪刀，布”的规则十分类似，两只奶牛数到三，然后出一个代表蹄子，剪刀或布的手势。蹄子胜过剪刀，剪刀胜过布，布胜过蹄子。特别地，如果两只奶牛的手势相同，则视为平局。

现在 FJ 和 Bassie 要进行 $N$ 轮对抗。Bassie 已经预测了 FJ 每一轮要出的手势。然而 Bassie 很懒，她最多只想变换 $K$ 次手势。

现在请你帮 Bassie 求出她最多能赢多少轮。
## 输入格式

第一行输入两个整数 $N,K$（$1 \leq N \leq 10^5$，$0 \leq K \leq 20$）。

接下来 $N$ 行，每行一个字母，代表 FJ 这一轮出的手势。`H` 代表蹄子（Hoof），`S` 代表剪刀（Scissors），`P` 代表布（Paper）。
## 输出格式

输出一个整数，代表 Bassie 在最多变换 $K$ 次手势的前提下最多赢多少轮。
## 样例

### 样例输入 #1
```
5 1
P
P
H
P
S
```
### 样例输出 #1
```
4

```


---

---
title: "游走"
layout: "post"
diff: 普及+/提高
pid: P6154
tag: ['2020', '记忆化搜索', '拓扑排序', '期望']
---
# 游走
## 题目背景

zbw 在 B 城游走。
## 题目描述

B 城可以看作一个有 $n$ 个点 $m$ 条边的**有向无环图**。**可能存在重边**。

zbw 在 B 城随机游走，他会在所有路径中随机选择一条路径，选择所有路径的概率相等。路径的起点和终点可以相同。

定义一条路径的长度为经过的边数，你需要求出 zbw 走的路径长度的期望，答案对 $998244353$ 取模。
## 输入格式

第一行两个整数 $n,m$。

接下来 $m$ 行，每行两个整数 $x,y$，表示存在一条从 $x$ 到 $y$ 的有向边。
## 输出格式

一行一个整数，表示答案对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
3 2
1 2
3 2
```
### 样例输出 #1
```
199648871
```
### 样例输入 #2
```
6 5
1 3
2 3
3 4
4 5
4 6
```
### 样例输出 #2
```
630470119
```
### 样例输入 #3
```
5 6
1 2
1 3
4 5
3 4
3 5
2 4
```
### 样例输出 #3
```
887328315
```
## 提示

样例说明：样例的答案分别为 $\dfrac{2}{5}$，$\dfrac{25}{19}$ 和 $\dfrac{11}{9}$。

| 测试点编号 | $n$ | $m$ | 特殊性质 | 每测试点分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1,2$ | $\le 10$ | $\le 10$ | 无 | $2$ |
| $3,4,5$ | $\le 15$ | $\le 100$ | 无 | $2$ |
| $6,7,8$ | $\le 100$ | $\le 10^3$ | 无 | $2$ |
| $9,10$ | $\le 10^3$ | $\le 10^4$ | 无 | $2$ |
| $11,12$ | $\le 10^4$ | $\le 10^5$ | 无 | $5$ |
| $13,14$ | $\le 10^5$ | $\le 2\times10^5$ | 无 | $5$ |
| $15,16$ | $\le 10^5$ | $\le 7\times10^5$ | 无 | $10$ |
| $17$ | $\le 10$ | $=n-1$ | 有向树 | $10$ |
| $18$ | $\le 10^3$ | $=n-1$ | 有向树 | $10$ |
| $19$ | $\le 10^4$ | $=n-1$ | 有向树 | $10$ |
| $20$ | $\le 10^5$ | $=n-1$ | 有向树 | $10$ |

其中，“有向树”的定义是：若把图视为无向图，则为一棵树（如样例 $1,2$）。

保证所有数据均按照某种方式随机，这意味着你可以认为算法执行过程中，你可以放心执行模意义下除法操作而不用担心除以零。


---

---
title: "[USACO21OPEN] Maze Tac Toe S"
layout: "post"
diff: 普及+/提高
pid: P7555
tag: ['USACO', '2021', '记忆化搜索', '进制']
---
# [USACO21OPEN] Maze Tac Toe S
## 题目描述

奶牛 Bessie 喜欢玩走迷宫。她同样喜欢玩井字棋（更准确地说，奶牛版的井字棋，马上会进行介绍）。Farmer John 找到了一种全新的方式，可以使她同时玩到这两种游戏！

首先，奶牛井字棋：与在 $3 \times 3$ 棋盘内放置 `X` 和 `O` 不同，奶牛当然是在 $3 \times 3$ 棋盘内放置 `M` 和 `O`。在一方的回合内，玩家可以选择将一个 `M` 或一个 `O` 放在任意一个空格内（这是另一个与标准井字棋的不同之处，标准的井字棋中一名玩家始终放 `X` 而另一名玩家始终放 `O`）。奶牛井字棋的胜利方是首位拼出 `MOO` 的玩家，可以是同行、同列或对角线。倒着拼出也是可以的，例如一名玩家在棋盘的一行内拼出 `OOM` 也可以获胜。如同标准井字棋一样，有可能最后没有玩家取得胜利。奶牛井字棋的一次行动通常用 3 个字符表示，`Mij` 或 `Oij`，其中 $i$ 和 $j$ 在范围 $1 \ldots 3$ 之间，表示放置 `M` 或 `O` 的行与列。

为了给 Bessie 增加一些挑战，Farmer John 设计了一个由 $N \times N$ 个方格组成的正方形迷宫（$3 \leq N \leq 25$）。某些方格，包括所有的边界方格，有巨大的草堆，使得 Bessie 不能移动到这些方格。Bessie 可以沿东南西北四个方向在迷宫内的所有其他方格内自由行动。某些方格内有一张纸，上面写有奶牛井字棋的一次行动。当 Bessie 在迷宫中移动时，任何时刻她停留在这样的方格上，她都必须于迷宫中移动之时在同时进行的奶牛井字棋游戏内做出对应的行动（除非奶牛井字棋中对应的方格已经被填上了，在这种情况下她不进行行动）。在奶牛井字棋游戏内没有与她对阵的玩家，但迷宫中的某些方格可能会不利于她最终拼出 `MOO`。

如果 Bessie 在获胜之时就会立刻停止奶牛井字棋，请求出她可以通过适当的方式在迷宫中移动而完成的不同的胜利状态棋盘数量。
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行，每行包含 $3N$ 个字符，描述迷宫。每个方格用 3 个字符表示，`###` 代表墙，`...` 代表空格，`BBB` 代表 Bessie 所在的一个非墙方格，或者一个奶牛井字棋的行动，表示 Bessie 必须进行对应行动的一个非墙方格。恰好一个方格为 `BBB`。
## 输出格式

输出 Bessie 可以通过在迷宫中行动并在获胜时立刻停止而产生的不同的胜利状态下的奶牛井字棋盘数量（可能为 $0$）。
## 样例

### 样例输入 #1
```
7
#####################
###O11###...###M13###
###......O22......###
###...######M22######
###BBB###M31###M11###
###...O32...M33O31###
#####################
```
### 样例输出 #1
```
8
```
## 提示

#### 样例说明

在这个样例中，Bessie 最终可能达成 $8$ 种胜利的棋盘状态：

```plain
O.M
.O.
MOM

O..
.O.
.OM

O.M
.O.
.OM

O..
.O.
MOM

O..
...
OOM

..M
.O.
OOM

...
.O.
OOM

...
...
OOM
```

对其中一种情况进行说明：

```plain
O..
...
OOM
```

在这里，Bessie 可以先移动到 `O11` 方格，然后移动到下方并通过 `O32`、`M33` 和 `O31`。此时游戏结束，因为她获得了胜利（例如她不能再前往位于她当前所在的 `O31` 方格北面的 `M11` 方格）。

#### 说明

供题：Brian Dean


---

---
title: "[蓝桥杯 2017 国 A] 填字母游戏"
layout: "post"
diff: 普及+/提高
pid: P8658
tag: ['2017', '记忆化搜索', '蓝桥杯国赛']
---
# [蓝桥杯 2017 国 A] 填字母游戏
## 题目描述

小明经常玩 LOL 游戏上瘾，一次他想挑战 K 大师，不料 K 大师说：

“我们先来玩个空格填字母的游戏，要是你不能赢我，就再别玩 LOL 了”。

K 大师在纸上画了一行 $n$ 个格子，要小明和他交替往其中填入字母。

并且：

1. 轮到某人填的时候，只能在某个空格中填入 `L` 或 `O`。

2. 谁先让字母组成了 `LOL` 的字样，谁获胜。

3. 如果所有格子都填满了，仍无法组成 `LOL`，则平局。

小明试验了几次都输了，他很惭愧，希望你能用计算机帮他解开这个谜。
## 输入格式

本题的输入格式为：

第一行，数字 $n$（$n<10$），表示下面有 $n$ 个初始局面。

接下来，$n$ 行，每行一个串（长度 $<20)$，表示开始的局面。

比如：`******`，表示有 $6$ 个空格。

`L****`，表示左边是一个字母 $L$，它的右边是 $4$ 个空格。
## 输出格式

要求输出 $n$ 个数字，表示对每个局面，如果小明先填，当 K 大师总是用最强着法的时候，小明的最好结果。

`1` 表示能赢。

`-1` 表示必输。

`0` 表示可以逼平。
## 样例

### 样例输入 #1
```
4
***
L**L
L**L***L
L*****L
```
### 样例输出 #1
```
0
-1
1
1
```
## 提示

时限 1 秒, 256M。蓝桥杯 2017 年第八届国赛


---

