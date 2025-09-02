---
title: "NAPTIME - Naptime"
layout: "post"
diff: 普及+/提高
pid: SP283
tag: ['动态规划 DP']
---

# NAPTIME - Naptime

## 题目描述

在某个星球上，一天由 $n$ 小时构成。我们称 $0 \sim 1$ 点为第一个小时，$1 \sim 2$ 点为第二个小时，以此类推。在第 $i$ 个小时睡觉能恢复 $U_i$ 点体力。在这座星球上住着一头牛，它每天要休息 $B$ 个小时，它休息的这 $B$ 个小时可以不连续，可以分成若干段，但是在每一段的第一个小时不能恢复体力，从第二个小时开始才可以恢复体力。
为了身体健康，这头牛希望遵循生物钟，每天采用相同的睡觉计划。另外，因为时间是连续的，每天的第 $n$ 个小时与下一天的第一个小时是相连的，这头牛只需要在 $n$ 个小时内休息 $B$ 个小时就够了。
请你给这头牛安排一个任务计划，使得它每天恢复的体力最多。

## 输入格式

第一行一个整数 $T$ 表示有 $T$ 组测试数据
对于每一组测试数据，第一行为两个整数 $n$ 与 $B$，接下来 $n$ 行每行一个整数 $U_i$。$2 \le B < N \le 3830 , 0 \le Ui \le 2 \times 10^5$。

## 输出格式

对于每组输入数据，对应一行输出一个整数，表示答案。（注意：两组输出之间没有空行）

## 样例 #1

### 输入

```
1
5 3
2
0
3
1
4
```

### 输出

```
6

Input/Output details:
The day is divided into 5 periods, with utilities 2, 0, 3, 1, 4 in that 
order. Goneril must pick 3 periods.

Goneril can get total utility 6 by being in bed during periods 4,
5, and 1, with utilities 0 [getting to sleep], 4, and 2
respectively.
```

