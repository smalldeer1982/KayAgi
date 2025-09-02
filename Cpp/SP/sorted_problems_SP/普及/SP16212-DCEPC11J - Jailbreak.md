---
title: "DCEPC11J - Jailbreak"
layout: "post"
diff: 普及/提高-
pid: SP16212
tag: ['动态规划 DP']
---

# DCEPC11J - Jailbreak

## 题目描述

The great King Kapish has prisoned Pushap, for he loves the princess Padmavati. To make sure that Pushap and Padmavati never meet again, King Kapish has kept Pushap in his most mysterious of jail.

This jail is built in a 2D rectangular grid fashion, containing M\*N prison cells. The entrance gate for jail is at bottom left corner (0,0). The mysteriousness of this jail comes from the fact that once a prisoner is taken from entrance gate (0,0) to any prison cell, then that prisoner can escape only if he comes back to the entrance visiting the cells used on his way from entrance to his prison cell. Note that in the escape, it is not required for the prisoner to trace the exact path or visit all the cells used on his way up, rather the condition is to use/visit only those prison cells used on his way up. Additionally, when the prisoner is taken from entrance (0,0) to a prison cell, they can fathom upto 2 cells in a single move/step in either upward direction or right direction. And when the prisoner is escaping, he can fathom upto 2 cells in a single move/step in either downward or left direction.

King Kapish orders to jail prisoner Pushap in cell (M-1,N-1).

You, being a common friend to Pushap and Padmavati, have to help Pushap escape the prison. **Tell him the number of ways in which he can go up to cell (M-1,N-1) and then come back following the procedure described above. Please refer explanation part to know more.**

## 输入格式

First line contains T, the number of test cases.

Each test case contains 2 space separated integers, M and N.

## 输出格式

Output exactly T lines, each containing the required answer modulo 10^9 + 7.

## 说明/提示

**【样例解释】**

对于第二组数据，一种可能的路径如下：

$(0,0) \to (0,1) \to (0,2) \to (1,2) \to (0,2) \to (0,0)$。

## 样例 #1

### 输入

```
3
2 2
2 3
3 4

```

### 输出

```
2
7
66

```

