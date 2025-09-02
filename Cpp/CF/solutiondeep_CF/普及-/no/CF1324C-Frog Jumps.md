# 题目信息

# Frog Jumps

## 题目描述

There is a frog staying to the left of the string $ s = s_1 s_2 \ldots s_n $ consisting of $ n $ characters (to be more precise, the frog initially stays at the cell $ 0 $ ). Each character of $ s $ is either 'L' or 'R'. It means that if the frog is staying at the $ i $ -th cell and the $ i $ -th character is 'L', the frog can jump only to the left. If the frog is staying at the $ i $ -th cell and the $ i $ -th character is 'R', the frog can jump only to the right. The frog can jump only to the right from the cell $ 0 $ .

Note that the frog can jump into the same cell twice and can perform as many jumps as it needs.

The frog wants to reach the $ n+1 $ -th cell. The frog chooses some positive integer value $ d $ before the first jump (and cannot change it later) and jumps by no more than $ d $ cells at once. I.e. if the $ i $ -th character is 'L' then the frog can jump to any cell in a range $ [max(0, i - d); i - 1] $ , and if the $ i $ -th character is 'R' then the frog can jump to any cell in a range $ [i + 1; min(n + 1; i + d)] $ .

The frog doesn't want to jump far, so your task is to find the minimum possible value of $ d $ such that the frog can reach the cell $ n+1 $ from the cell $ 0 $ if it can jump by no more than $ d $ cells at once. It is guaranteed that it is always possible to reach $ n+1 $ from $ 0 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

The picture describing the first test case of the example and one of the possible answers:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324C/662a540925813072330b737ce66b1eb08560ce29.png)

In the second test case of the example, the frog can only jump directly from $ 0 $ to $ n+1 $ .

In the third test case of the example, the frog can choose $ d=3 $ , jump to the cell $ 3 $ from the cell $ 0 $ and then to the cell $ 4 $ from the cell $ 3 $ .

In the fourth test case of the example, the frog can choose $ d=1 $ and jump $ 5 $ times to the right.

In the fifth test case of the example, the frog can only jump directly from $ 0 $ to $ n+1 $ .

In the sixth test case of the example, the frog can choose $ d=1 $ and jump $ 2 $ times to the right.

## 样例 #1

### 输入

```
6
LRLRRLL
L
LLR
RRRR
LLLLLL
R```

### 输出

```
3
2
3
1
7
1```

# AI分析结果

### 题目内容
# 青蛙跳跃

## 题目描述
有一只青蛙停留在由 $n$ 个字符组成的字符串 $s = s_1 s_2 \ldots s_n$ 的左边（更准确地说，青蛙最初停留在单元格 $0$ 处）。$s$ 的每个字符要么是 'L' 要么是 'R'。这意味着如果青蛙停留在第 $i$ 个单元格且第 $i$ 个字符是 'L'，青蛙只能向左跳。如果青蛙停留在第 $i$ 个单元格且第 $i$ 个字符是 'R'，青蛙只能向右跳。青蛙只能从单元格 $0$ 向右跳。

注意，青蛙可以两次跳入同一个单元格，并且可以根据需要进行多次跳跃。

青蛙想要到达第 $n + 1$ 个单元格。青蛙在第一次跳跃前选择某个正整数值 $d$（之后不能更改），并且每次跳跃不超过 $d$ 个单元格。即，如果第 $i$ 个字符是 'L'，那么青蛙可以跳到范围 $[max(0, i - d); i - 1]$ 中的任何单元格，如果第 $i$ 个字符是 'R'，那么青蛙可以跳到范围 $[i + 1; min(n + 1; i + d)]$ 中的任何单元格。

青蛙不想跳得太远，所以你的任务是找到最小的可能值 $d$，使得如果青蛙每次跳跃不超过 $d$ 个单元格，它可以从单元格 $0$ 到达单元格 $n + 1$。保证从 $0$ 总是可以到达 $n + 1$。

你必须回答 $t$ 个独立的测试用例。

## 说明/提示
描述示例中第一个测试用例及其中一个可能答案的图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324C/662a540925813072330b737ce66b1eb08560ce29.png)

在示例的第二个测试用例中，青蛙只能直接从 $0$ 跳到 $n + 1$。

在示例的第三个测试用例中，青蛙可以选择 $d = 3$，从单元格 $0$ 跳到单元格 $3$，然后从单元格 $3$ 跳到单元格 $4$。

在示例的第四个测试用例中，青蛙可以选择 $d = 1$ 并向右跳 $5$ 次。

在示例的第五个测试用例中，青蛙只能直接从 $0$ 跳到 $n + 1$。

在示例的第六个测试用例中，青蛙可以选择 $d = 1$ 并向右跳 $2$ 次。

## 样例 #1
### 输入
```
6
LRLRRLL
L
LLR
RRRR
LLLLLL
R
```
### 输出
```
3
2
3
1
7
1
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是贪心算法，即忽略向左跳的情况（因为向左跳会使距离终点更远，不是最优选择），只关注向右跳的情况，通过找出相邻 'R' 之间以及起点到第一个 'R'、最后一个 'R' 到终点的最大距离来确定最小的 $d$。
- **思路方面**：多数题解都明确指出向左跳不划算，只需考虑向右跳，重点关注 'R' 的位置关系。
- **算法要点**：遍历字符串，记录 'R' 的位置，计算相邻 'R' 之间的距离并取最大值，同时考虑起点和终点与 'R' 的距离。
- **解决难点**：理解向左跳无意义，将问题简化为求特定距离的最大值。部分题解通过证明（如数学归纳法、反证法）来严谨说明只考虑向右跳的合理性。

### 通用建议与扩展思路
对于此类贪心问题，关键在于分析题目条件，找出最优策略的方向。可以进一步拓展到更复杂的跳跃规则或地图场景，比如不同位置有不同的跳跃限制，或者地图存在多种类型的障碍等。解决这类问题时，要善于从简单情况入手，分析各种操作对目标的影响，从而确定贪心策略。

### 相似知识点洛谷题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
- **oimaster**：一开始思维混乱，想出正解后觉得自己之前思路有误。总结出应忽略向左跳，关注向右跳的“石头”（即 'R'），求出相关坐标差的最大值。心得强调了对题目深入理解后，转变思路找到正确解法的过程。 

---
处理用时：48.36秒