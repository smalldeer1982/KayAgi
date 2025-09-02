---
title: "Baby Ehab Plays with Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF1516E
tag: []
---

# Baby Ehab Plays with Permutations

## 题目描述

This time around, Baby Ehab will play with permutations. He has $ n $ cubes arranged in a row, with numbers from $ 1 $ to $ n $ written on them. He'll make exactly $ j $ operations. In each operation, he'll pick up $ 2 $ cubes and switch their positions.

He's wondering: how many different sequences of cubes can I have at the end? Since Baby Ehab is a turbulent person, he doesn't know how many operations he'll make, so he wants the answer for every possible $ j $ between $ 1 $ and $ k $ .

## 输入格式

The only line contains $ 2 $ integers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ , $ 1 \le k \le 200 $ ) — the number of cubes Baby Ehab has, and the parameter $ k $ from the statement.

## 输出格式

Print $ k $ space-separated integers. The $ i $ -th of them is the number of possible sequences you can end up with if you do exactly $ i $ operations. Since this number can be very large, print the remainder when it's divided by $ 10^9+7 $ .

## 说明/提示

In the second example, there are $ 3 $ sequences he can get after $ 1 $ swap, because there are $ 3 $ pairs of cubes he can swap. Also, there are $ 3 $ sequences he can get after $ 2 $ swaps:

- $ [1,2,3] $ ,
- $ [3,1,2] $ ,
- $ [2,3,1] $ .

## 样例 #1

### 输入

```
2 3
```

### 输出

```
1 1 1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
3 3
```

## 样例 #3

### 输入

```
4 2
```

### 输出

```
6 12
```

