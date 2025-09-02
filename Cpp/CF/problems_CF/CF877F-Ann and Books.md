---
title: "Ann and Books"
layout: "post"
diff: 提高+/省选-
pid: CF877F
tag: []
---

# Ann and Books

## 题目描述

In Ann's favorite book shop are as many as $ n $ books on math and economics. Books are numbered from $ 1 $ to $ n $ . Each of them contains non-negative number of problems.

Today there is a sale: any subsegment of a segment from $ l $ to $ r $ can be bought at a fixed price.

Ann decided that she wants to buy such non-empty subsegment that the sale operates on it and the number of math problems is greater than the number of economics problems exactly by $ k $ . Note that $ k $ may be positive, negative or zero.

Unfortunately, Ann is not sure on which segment the sale operates, but she has $ q $ assumptions. For each of them she wants to know the number of options to buy a subsegment satisfying the condition (because the time she spends on choosing depends on that).

Currently Ann is too busy solving other problems, she asks you for help. For each her assumption determine the number of subsegments of the given segment such that the number of math problems is greaten than the number of economics problems on that subsegment exactly by $ k $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100000 $ , $ -10^{9}<=k<=10^{9} $ ) — the number of books and the needed difference between the number of math problems and the number of economics problems.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=2 $ ), where $ t_{i} $ is $ 1 $ if the $ i $ -th book is on math or $ 2 $ if the $ i $ -th is on economics.

The third line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the number of problems in the $ i $ -th book.

The fourth line contains a single integer $ q $ ( $ 1<=q<=100000 $ ) — the number of assumptions.

Each of the next $ q $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) describing the $ i $ -th Ann's assumption.

## 输出格式

Print $ q $ lines, in the $ i $ -th of them print the number of subsegments for the $ i $ -th Ann's assumption.

## 说明/提示

In the first sample Ann can buy subsegments $ [1;1],[2;2],[3;3],[2;4] $ if they fall into the sales segment, because the number of math problems is greater by $ 1 $ on them that the number of economics problems. So we should count for each assumption the number of these subsegments that are subsegments of the given segment.

Segments $ [1;1] $ and $ [2;2] $ are subsegments of $ [1;2] $ .

Segments $ [1;1],[2;2] $ and $ [3;3] $ are subsegments of $ [1;3] $ .

Segments $ [1;1],[2;2],[3;3],[2;4] $ are subsegments of $ [1;4] $ .

Segment $ [3;3] $ is subsegment of $ [3;4] $ .

## 样例 #1

### 输入

```
4 1
1 1 1 2
1 1 1 1
4
1 2
1 3
1 4
3 4

```

### 输出

```
2
3
4
1

```

## 样例 #2

### 输入

```
4 0
1 2 1 2
0 0 0 0
1
1 4

```

### 输出

```
10

```

