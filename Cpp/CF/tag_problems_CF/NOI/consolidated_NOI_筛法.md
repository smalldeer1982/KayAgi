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

