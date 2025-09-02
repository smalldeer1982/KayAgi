---
title: "Reindeer Games"
layout: "post"
diff: 省选/NOI-
pid: CF1615H
tag: []
---

# Reindeer Games

## 题目描述

There are $ n $ reindeer at the North Pole, all battling for the highest spot on the "Top Reindeer" leaderboard on the front page of CodeNorses (a popular competitive reindeer gaming website). Interestingly, the "Top Reindeer" title is just a measure of upvotes and has nothing to do with their skill level in the reindeer games, but they still give it the utmost importance.

Currently, the $ i $ -th reindeer has a score of $ a_i $ . You would like to influence the leaderboard with some operations. In an operation, you can choose a reindeer, and either increase or decrease his score by $ 1 $ unit. Negative scores are allowed.

You have $ m $ requirements for the resulting scores. Each requirement is given by an ordered pair $ (u, v) $ , meaning that after all operations, the score of reindeer $ u $ must be less than or equal to the score of reindeer $ v $ .

Your task is to perform the minimum number of operations so that all requirements will be satisfied.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2\le n\le 1000 $ ; $ 1\le m\le 1000 $ ) — the number of reindeer and requirements, respectively.

The second line contains $ n $ integers $ a_1,\ldots, a_n $ ( $ 1\le a_i\le 10^9 $ ), where $ a_i $ is the current score of reindeer $ i $ .

The next $ m $ lines describe the requirements.

The $ i $ -th of these lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ ; $ u_i\ne v_i $ ) — the two reindeer of the $ i $ -th requirement.

## 输出格式

Print $ n $ integers $ b_1,\ldots, b_n $ ( $ -10^{15}\le b_i\le 10^{15} $ ), where $ b_i $ is the score of the $ i $ -th reindeer after all operations.

If there are multiple solutions achieving the minimum number of operations, you may output any.

We can prove that there is always an optimal solution such that $ |b_i|\le 10^{15} $ for all $ i $ .

## 样例 #1

### 输入

```
7 6
3 1 4 9 2 5 6
1 2
2 3
3 4
4 5
5 6
6 7
```

### 输出

```
1 1 4 4 4 5 6
```

## 样例 #2

### 输入

```
4 6
6 5 8 2
3 1
4 1
3 2
1 2
2 3
3 1
```

### 输出

```
6 6 6 2
```

## 样例 #3

### 输入

```
10 18
214 204 195 182 180 176 176 172 169 167
1 2
3 2
4 2
5 2
6 2
7 2
8 2
9 2
10 2
6 1
6 2
6 3
6 4
6 5
6 7
6 8
6 9
6 10
```

### 输出

```
204 204 195 182 180 167 176 172 169 167
```

