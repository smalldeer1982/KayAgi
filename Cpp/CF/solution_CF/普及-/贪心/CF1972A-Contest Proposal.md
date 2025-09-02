# Contest Proposal

## 题目描述

A contest contains $ n $ problems and the difficulty of the $ i $ -th problem is expected to be at most $ b_i $ . There are already $ n $ problem proposals and the difficulty of the $ i $ -th problem is $ a_i $ . Initially, both $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ are sorted in non-decreasing order.

Some of the problems may be more difficult than expected, so the writers must propose more problems. When a new problem with difficulty $ w $ is proposed, the most difficult problem will be deleted from the contest, and the problems will be sorted in a way that the difficulties are non-decreasing.

In other words, in each operation, you choose an integer $ w $ , insert it into the array $ a $ , sort array $ a $ in non-decreasing order, and remove the last element from it.

Find the minimum number of new problems to make $ a_i\le b_i $ for all $ i $ .

## 说明/提示

In the first test case:

- Propose a problem with difficulty $ w=800 $ and $ a $ becomes $ [800,1000,1400,2000,2000,2200] $ .
- Propose a problem with difficulty $ w=1800 $ and $ a $ becomes $ [800,1000,1400,1800,2000,2000] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

In the second test case:

- Propose a problem with difficulty $ w=1 $ and $ a $ becomes $ [1,4,5,6,7,8] $ .
- Propose a problem with difficulty $ w=2 $ and $ a $ becomes $ [1,2,4,5,6,7] $ .
- Propose a problem with difficulty $ w=3 $ and $ a $ becomes $ [1,2,3,4,5,6] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

## 样例 #1

### 输入

```
2
6
1000 1400 2000 2000 2200 2700
800 1200 1500 1800 2200 3000
6
4 5 6 7 8 9
1 2 3 4 5 6```

### 输出

```
2
3```

