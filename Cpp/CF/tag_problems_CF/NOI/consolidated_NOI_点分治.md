---
title: "Freezing with Style"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF150E
tag: ['点分治', '单调队列', '分治']
---

# Freezing with Style

## 题目描述

This winter is so... well, you've got the idea :-) The Nvodsk road system can be represented as $ n $ junctions connected with $ n-1 $ bidirectional roads so that there is a path between any two junctions. The organizers of some event want to choose a place to accommodate the participants (junction $ v $ ), and the place to set up the contests (junction $ u $ ). Besides, at the one hand, they want the participants to walk about the city and see the neighbourhood (that's why the distance between $ v $ and $ u $ should be no less than $ l $ ). On the other hand, they don't want the participants to freeze (so the distance between $ v $ and $ u $ should be no more than $ r $ ). Besides, for every street we know its beauty — some integer from $ 0 $ to $ 10^{9} $ . Your task is to choose the path that fits in the length limits and has the largest average beauty. We shall define the average beauty as a median of sequence of the beauties of all roads along the path.

We can put it more formally like that: let there be a path with the length $ k $ . Let $ a_{i} $ be a non-decreasing sequence that contains exactly $ k $ elements. Each number occurs there exactly the number of times a road with such beauty occurs along on path. We will represent the path median as number $ a_{⌊k/2⌋} $ , assuming that indexation starting from zero is used. $ ⌊x⌋ $ — is number $ х $ , rounded down to the nearest integer.

For example, if $ a={0,5,12} $ , then the median equals to $ 5 $ , and if $ a={0,5,7,12} $ , then the median is number $ 7 $ .

It is guaranteed that there will be at least one path with the suitable quantity of roads.

## 输入格式

The first line contains three integers $ n $ , $ l $ , $ r $ ( $ 1\le l\le r,n\le 10^{5} $ ).

Next $ n-1 $ lines contain descriptions of roads of the Nvodsk, each line contains three integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ 0<=c_{i}<=10^{9} $ , $ a_{i}≠b_{i} $ ) — junctions $ a_{i} $ and $ b_{i} $ are connected with a street whose beauty equals $ c_{i} $ .

## 输出格式

Print two integers — numbers of the junctions, where to accommodate the participants and set up the contests, correspondingly. If there are multiple optimal variants, print any of them.

## 说明/提示

In the first sample all roads have the same beauty. That means that all paths of the positive length have the same median. Thus, any path with length from $ 3 $ to $ 4 $ , inclusive will be valid for us.

In the second sample the city looks like that: 1 - 2 - 3 - 4 - 5 - 6. Two last roads are more valuable and we should choose any path that contains both of them and has the suitable length. It is either the path between $ 2 $ and $ 6 $ or the path between $ 3 $ and $ 6 $ .

## 样例 #1

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1

```

### 输出

```
4 1

```

## 样例 #2

### 输入

```
6 3 4
1 2 1
2 3 1
3 4 1
4 5 2
5 6 2

```

### 输出

```
6 3

```

## 样例 #3

### 输入

```
5 1 4
1 2 1
1 3 4
3 4 7
3 5 2

```

### 输出

```
4 3

```

## 样例 #4

### 输入

```
8 3 6
1 2 9
2 3 7
3 4 7
4 5 8
5 8 2
3 6 3
2 7 4

```

### 输出

```
5 1

```



---

---
title: "Optimizations From Chelsu"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1916G
tag: ['点分治']
---

# Optimizations From Chelsu

## 题目描述

You are given a tree with $ n $ vertices, whose vertices are numbered from $ 1 $ to $ n $ . Each edge is labeled with some integer $ w_i $ .

Define $ len(u, v) $ as the number of edges in the simple path between vertices $ u $ and $ v $ , and $ gcd(u, v) $ as the Greatest Common Divisor of all numbers written on the edges of the simple path between vertices $ u $ and $ v $ . For example, $ len(u, u) = 0 $ and $ gcd(u, u) = 0 $ for any $ 1 \leq u \leq n $ .

You need to find the maximum value of $ len(u, v) \cdot gcd(u, v) $ over all pairs of vertices in the tree.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. This is followed by their description.

The first line of each test case contains the number $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The next $ n-1 $ lines specify the edges in the format $ u $ , $ v $ , $ w $ ( $ 1 \leq u, v \leq n $ , $ 1 \leq w \leq 10^{12} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number equal to the maximum value of $ len(u, v) \cdot gcd(u, v) $ over all pairs of vertices in the tree.

## 样例 #1

### 输入

```
4
2
1 2 1000000000000
4
3 2 6
2 1 10
2 4 6
8
1 2 12
2 3 9
3 4 9
4 5 6
5 6 12
6 7 4
7 8 9
12
1 2 12
2 3 12
2 4 6
2 5 9
5 6 6
1 7 4
4 8 12
8 9 4
8 10 12
2 11 9
7 12 9
```

### 输出

```
1000000000000
12
18
24
```



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

