---
title: "BOXSCHOC - Boxes of Chocolate"
layout: "post"
diff: 难度0
pid: SP15994
tag: []
---

# BOXSCHOC - Boxes of Chocolate

## 题目描述

Choco-moo 去超市为朋友们购买巧克力。他在店里看到货架上整齐地摆放着许多盒巧克力，总共有 $N$（$0 < N \leq 100000$）盒。每一个编号为 $i$ 的巧克力盒里装有 $A_i$（$0 < A_i \leq 100000$）块巧克力。Choco-moo 非常喜欢巧克力，虽然很想把所有盒子都买下来，但最终决定只买那些巧克力数目能被 $K$（$0 < K \leq 100000$）整除的盒子，因为他想要巧克力可以平均分给他 $K$ 个朋友，确保没有多余的巧克力。

现在，你会得到一个整数 $N$，接着是 $N$ 个数字，表示每个盒子里的巧克力数量。接下来，你需要回答 $Q$（$0 < Q \leq 100000$）个关于选购的信息。

在每个查询中，Choco-moo 会给你三个整数 $A$、$B$（$0 < A \leq B \leq N$）和 $K$。这里 $A$ 和 $B$ 是巧克力盒的起始和结束编号，$K$ 是他的朋友数量。你的任务是找出从第 $A$ 个盒子到第 $B$ 个盒子（包含两端）之间，有多少盒巧克力是可以被 Choco-moo 买下的。

## 输入格式

第一行是一个整数 $T$（$T \leq 2$），代表测试用例的数量。

每个测试用例的第一行是一个整数 $N$，表示巧克力盒的数量。接下来的一行包含 $N$ 个正整数，代表每个盒子里的巧克力数。然后是一行整数 $Q$，表示需要回答的查询数量。接下来的 $Q$ 行中，每行包含三个整数 $A$、$B$ 和 $K$。

## 输出格式

对于每个测试用例，先输出“Case #x:”（其中 x 是测试用例编号，从 1 开始）。然后针对每个查询输出一个结果，每行一个，表示从第 $A$ 个盒子到第 $B$ 个盒子之间，Choco-moo 能买到的符合分配条件的巧克力盒数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5
1 2 3 4 5
2
1 5 1
1 5 2
5
12 32 5 12 9
3
1 5 2
3 5 3
2 5 2
```

### 输出

```
&nbsp;
Case 1:
5
2
Case 2:
3
2
2
&nbsp;
Explanation: In Case 1: Query 1 Choco-moo buys all the boxes since all boxes are divisible by 1. In query 2 he buys second and fourth box since they are divisible by 2 ( 2 and 4 ).
Note: Let me know if you think the judge data is weak or there is ambigutiy/mistake in the problem statment.&nbsp;
```

