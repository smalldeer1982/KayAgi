# 题目信息

# Balls of Steel

## 题目描述

You have $ n $ distinct points $ (x_1, y_1),\ldots,(x_n,y_n) $ on the plane and a non-negative integer parameter $ k $ . Each point is a microscopic steel ball and $ k $ is the attract power of a ball when it's charged. The attract power is the same for all balls.

In one operation, you can select a ball $ i $ to charge it. Once charged, all balls with Manhattan distance at most $ k $ from ball $ i $ move to the position of ball $ i $ . Many balls may have the same coordinate after an operation.

More formally, for all balls $ j $ such that $ |x_i - x_j| + |y_i - y_j| \le k $ , we assign $ x_j:=x_i $ and $ y_j:=y_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450B/bd476820b8f47c8050ef448d8375a731892e001a.png) An example of an operation. After charging the ball in the center, two other balls move to its position. On the right side, the red dot in the center is the common position of those balls. Your task is to find the minimum number of operations to move all balls to the same position, or report that this is impossible.

## 说明/提示

In the first test case, there are three balls at $ (0, 0) $ , $ (3, 3) $ , and $ (1, 1) $ and the attract power is $ 2 $ . It is possible to move two balls together with one operation, but not all three balls together with any number of operations.

In the second test case, there are three balls at $ (6, 7) $ , $ (8, 8) $ , and $ (6, 9) $ and the attract power is $ 3 $ . If we charge any ball, the other two will move to the same position, so we only require one operation.

In the third test case, there are four balls at $ (0, 0) $ , $ (0, 1) $ , $ (0, 2) $ , and $ (0, 3) $ , and the attract power is $ 1 $ . We can show that it is impossible to move all balls to the same position with a sequence of operations.

## 样例 #1

### 输入

```
3
3 2
0 0
3 3
1 1
3 3
6 7
8 8
6 9
4 1
0 0
0 1
0 2
0 3```

### 输出

```
-1
1
-1```

# AI分析结果

### 题目内容
# 钢铁之球

## 题目描述
在平面上，你有 $n$ 个不同的点 $(x_1, y_1),\ldots,(x_n,y_n)$ 以及一个非负整数参数 $k$ 。每个点都是一个微观的钢球，而 $k$ 是一个球充电时的吸引力。所有球的吸引力是相同的。

在一次操作中，你可以选择给一个球 $i$ 充电。一旦充电，所有与球 $i$ 的曼哈顿距离至多为 $k$ 的球都会移动到球 $i$ 的位置。一次操作后，许多球可能会处于相同的坐标位置。

更正式地说，对于所有满足 $|x_i - x_j| + |y_i - y_j| \leq k$ 的球 $j$ ，我们将 $x_j$ 赋值为 $x_i$ ，$y_j$ 赋值为 $y_i$ 。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450B/bd476820b8f47c8050ef448d8375a731892e001a.png) 一次操作的示例。给中心的球充电后，另外两个球移动到它的位置。在右侧，中心的红点是这些球的共同位置。你的任务是找出将所有球移动到同一位置所需的最少操作次数，如果不可能做到，则报告这一点。

## 说明/提示
在第一个测试用例中，有三个球分别位于 $(0, 0)$ 、$(3, 3)$ 和 $(1, 1)$ ，吸引力为 $2$ 。可以通过一次操作将两个球移动到一起，但无论进行多少次操作，都无法将三个球移动到一起。

在第二个测试用例中，有三个球分别位于 $(6, 7)$ 、$(8, 8)$ 和 $(6, 9)$ ，吸引力为 $3$ 。如果我们给任何一个球充电，另外两个球都会移动到相同的位置，所以我们只需要一次操作。

在第三个测试用例中，有四个球分别位于 $(0, 0)$ 、$(0, 1)$ 、$(0, 2)$ 和 $(0, 3)$ ，吸引力为 $1$ 。我们可以证明，通过一系列操作无法将所有球移动到同一位置。

## 样例 #1
### 输入
```
3
3 2
0 0
3 3
1 1
3 3
6 7
8 8
6 9
4 1
0 0
0 1
0 2
0 3
```
### 输出
```
-1
1
-1
```

### 算法分类
枚举

### 综合分析与结论
这几道题解思路基本一致，都基于答案只能是 $-1$ 或 $1$ 这个结论展开。通过枚举每一个点，计算该点与其他所有点的曼哈顿距离，判断是否存在一个点能将所有点吸引到同一位置。如果存在，则答案为 $1$ ；否则为 $-1$ 。不同题解在代码实现细节上略有差异，如数据结构的使用、距离计算方式等。

### 通用建议与扩展思路
通用建议：在实现过程中，要注意曼哈顿距离的正确计算，以及循环边界和条件判断的准确性。对于这类结论较为明确的题目，要注重证明结论的正确性，再基于结论进行算法设计。
扩展思路：同类型题目可能会改变距离的定义（如欧几里得距离），或者改变点的分布空间（如三维空间），解题思路可类比本题，先分析可能的答案情况，再进行针对性枚举判断。

### 推荐题目
1. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)
2. [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)

---
处理用时：31.65秒