---
title: "Sophisticated Device"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1060H
tag: ['数学', '高斯消元', '逆元']
---

# Sophisticated Device

## 题目描述

给你两个正整数 $d$ 和 $p$，$p$ 是质数。

你还有一个神奇的机器，有很多个格子，每个格子有一个 0 到 $p-1$ 的整数。它还支持两种操作：求和与求 $d$ 次幂。 **结果都对 $p$ 取模。**

这些格子编号分别为 $1,2,3,\ldots,5000$，一开始第一、二个格子分别存储 $x,y(0\leq x,y\leq p-1)$，其余格子存储 1。

你不能直接访问格子里面的变量，你也**不知道** $x,y$ 为多少（但你知道它们分别存在前两格）。你应该使用给定的指令编写程序，让一个格子里面出现 $xy\mod p$。你的程序必须可以应对任何可能的 $x,y$。

加法指令把两个格子里面的数之和放进第三个格子。这个指令形如 `+ e1 e2 to`，用途是将第 $e1$ 格与第 $e2$ 格之和放入第 $to$ 格。$e1,e2,to$ 可以相等。

第二个指令将一个格子里的数的 $d$ 次幂放进另一个格子。这个指令形如 `^ e to`，用途是将第 $e$ 格数字的 $d$ 次幂放入第 $to$ 格。$e,to$可以相等，这时第 $e$ 格的数字将被覆盖。

最后一个指令返回答案。这个指令形如 `f target`，用途是表示第 $target$ 格就是所求的 $xy\mod p$。这之后不应有任何指令。

编写程序求出 $xy\mod p$。指令总数不应超过 5000 条，包括返回答案的指令在内。

保证有解。

## 输入格式

第一行两个正整数 $d,p$，用空格隔开。（$2\leq d\leq 10,d<p,3 \leq p \leq 10^9 + 9$，$p$ 为质数）

## 说明/提示

本题**没有样例**。下面是个例子。注意这不是任何一个数据的解，仅仅为了说明格式。

```text
+ 1 1 3
^ 3 3
+ 3 2 2
+ 3 2 3
^ 3 1
f 1
```


|步骤  |格1  |格2  |格3  |
| :-----------: | :-----------: | :-----------: | :-----------: |
|最初  |$x$  |$y$  |$1$  |
|`+ 1 1 3`|$x$  |$y$  |$2x$  |
|`^3 3`  |$x$  |$y$  |$(2x)^d$  |
|`+3 2 2`  |$x$  |$y+(2x)^d$  |$(2x)^d$  |
|`+ 3 2 3`  |$x$  |$y+(2x)^d$  |$y+2*(2x)^d$  |
|`^ 3 1`  |$(y+2*(2x)^d)^d$  |$y+(2x)^d$  |$y+2*(2x)^d$  |



---

---
title: "Furukawa Nagisa's Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF434E
tag: ['点分治', '素数判断,质数,筛法', '逆元']
---

# Furukawa Nagisa's Tree

## 题目背景

有一天冈崎朋也和送给古河渚一棵树作为渚的生日礼物。（因为渚的生日是 12.24 啊~）。这是一棵奇奇怪怪的树，每一个节点都有一个权值 $v_i$。现在渚和朋也想在这棵树上玩一个游戏。


设 $ (s,e) $ 为从节点  $s$ 到节点 $e$ 的路径，我们可以写下路径 $ (s,e) $ 上的节点值序列，并将此序列表示为 $ S(s,e) $。  
可爱的渚这样定义了一个序列的权值： $G(S(s,e)) $。假设这个序列是 $ z_{0},z_{1}...z_{l-1} $，此处 $ l $ 是序列长度，定义 $ G(S(s,e))=z_{0}\times k^{0}+z_{1}\times k^{1} + \cdots + z_{l-1} \times k^{l-1} $。  
如果这条序列满足 $G(S(s, e)) \equiv x \pmod y$，那么这条路径 $ (s,e) $ 属于古河渚，反之属于冈崎朋也。


渚觉得计算谁拥有更多的路径实在是太简单了，所以她想要尝试一些难一点的。渚认为如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于她，那么$ (p_{1},p_{3}) $ 的路径也会属于她。同理，如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于朋也，那么路径 $ (p_{1},p_{3}) $ 也属于朋也。但是实际上，渚的这一结论并不是一直都是正确的。渚现在想知道有多少三元组 $ (p_{1},p_{2},p_{3}) $ 满足她的结论，这就是你的任务啦！


翻译者：永远喜欢 Furukawa Nagisa 的 zcysky。

## 题目描述

One day, Okazaki Tomoya has bought a tree for Furukawa Nagisa's birthday. The tree is so strange that every node of the tree has a value. The value of the $ i $ -th node is $ v_{i} $ . Now Furukawa Nagisa and Okazaki Tomoya want to play a game on the tree.

Let $ (s,e) $ be the path from node $ s $ to node $ e $ , we can write down the sequence of the values of nodes on path $ (s,e) $ , and denote this sequence as $ S(s,e) $ . We define the value of the sequence $ G(S(s,e)) $ as follows. Suppose that the sequence is $ z_{0},z_{1}...z_{l-1} $ , where $ l $ is the length of the sequence. We define $ G(S(s,e))=z_{0}×k^{0}+z_{1}×k^{1}+...+z_{l-1}×k^{l-1} $ . If the path $ (s,e) $ satisfies ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF434E/90c086b3cd66d72f064774200cc642323d3ee403.png), then the path $ (s,e) $ belongs to Furukawa Nagisa, otherwise it belongs to Okazaki Tomoya.

Calculating who has more paths is too easy, so they want to play something more difficult. Furukawa Nagisa thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to her, then path $ (p_{1},p_{3}) $ belongs to her as well. Also, she thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to Okazaki Tomoya, then path $ (p_{1},p_{3}) $ belongs to Okazaki Tomoya as well. But in fact, this conclusion isn't always right. So now Furukawa Nagisa wants to know how many triplets $ (p_{1},p_{2},p_{3}) $ are correct for the conclusion, and this is your task.

## 输入格式

The first line contains four integers $ n $ , $ y $ , $ k $ and $ x (1<=n<=10^{5}; 2<=y<=10^{9}; 1<=k&lt;y; 0<=x&lt;y) $ — $ n $ being the number of nodes on the tree. It is guaranteed that $ y $ is a prime number.

The second line contains $ n $ integers, the $ i $ -th integer is $ v_{i} (0<=v_{i}&lt;y) $ .

Then follow $ n-1 $ lines, each line contains two integers, denoting an edge of the tree. The nodes of the tree are numbered from 1 to $ n $ .

## 输出格式

Output a single integer — the number of triplets that are correct for Furukawa Nagisa's conclusion.

## 样例 #1

### 输入

```
1 2 1 0
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 5 2 1
4 3 1
1 2
2 3

```

### 输出

```
14

```

## 样例 #3

### 输入

```
8 13 8 12
0 12 7 4 12 0 8 12
1 8
8 4
4 6
6 2
2 3
8 5
2 7

```

### 输出

```
341

```



---

