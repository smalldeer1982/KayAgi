---
title: "HACK14 - The Hack"
layout: "post"
diff: 难度0
pid: SP21597
tag: []
---

# HACK14 - The Hack

## 题目描述

Aiden Pearce is one of the most famous hackers of all time, just recently he acquired a new powerful teleport that can be used exactly K times before it self-destructs.

So he decided to rob as many banks as he can from Linearland. Linearland consists of N cities on a 1-Dimensional plane which Aiden can visit, after he’s teleported to some city of Linearland he can begin robbing banks, each city i has a bank that contains G[i] dollars.

The teleportation device is also expensive to use; inn order to teleport to some city i he has to pay T[i] dollars but teleportation isn’t his only means of transport he can also visit cities by helicopter which costs W dollars per meter. Aidens initial position is outside Linearland, so, the first city he visits can only be reached by teleportaion.

Each city i is situated in position X[i] (which means it’s X[i] meters far from the beginning of Linearland). Aiden isn’t sure that robbing Linearland banks is profitable so he asked you to calculate the maximum amount of money he can earn.

(Aiden can have a negative amount of money at any time).

Please note that Aiden doesn't need to use all K teleports, and since he is very greedy he will never go to Linearland if his net profit is negative (i.e if he can't get a positive profit he will settle with a good old 0)

## 输入格式

First T the number of test cases,

For each test case:

3 integers separated by space representing (1 <= N <= 10^3), (1 <= K <= N) and (W <= 10^9).

Then N lines each line consists of 3 integers (0 <= X\[i\] <= 10^9), (1 <= T\[i\] <= 10^9), (1 <= G\[i\] <= 10^9).

## 输出格式

One line per test case, each with a single integer which is the maximum amount of money.

 ```
Input:
1
4 1 1
1 1000 100
3 0 10
4 20 3
10 90 0

Output:
109
```

