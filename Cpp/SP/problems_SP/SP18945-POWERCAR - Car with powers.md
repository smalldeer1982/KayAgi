---
title: "POWERCAR - Car with powers"
layout: "post"
diff: 难度0
pid: SP18945
tag: []
---

# POWERCAR - Car with powers

## 题目描述

在一个直线赛道上，起点位于 Track[0]，终点位于 Track[n-1]。汽车起始位置在 Track[0]。

如果 Track[i] 是 '#'，则表示那里有一堵墙。

汽车可以从 Track[i] 移动到 Track[i+1]，前提是 Track[i+1] 不是墙。从 Track[i] 移至 Track[i+1] 需要 1 个时间单位。

如果 Track[i+1] 是墙，并且你有足够的子弹，可以从 Track[i] 向其射击破坏墙壁。每次射击会消耗 1 颗子弹，射击不需要任何时间。

汽车允许驶出赛道，即可以从 Track[i] 移动到 offTrack[i]，再从 offTrack[i] 移动到 offTrack[i+1]，也可以从 offTrack[i] 回到非墙的 Track[i]。此类移动每一步都需要 2 个时间单位。

请找出完成比赛所需的最短时间。如果无法完成比赛，输出 "Impossible"。

**输入格式：**

第一行是一个整数 t，表示测试用例的数量。每个测试用例的第一行包含两个整数 n 和 bullets，分别表示赛道的长度和可用的子弹数量。接下来的行是一个字符串，描述赛道的布局。

**输出格式：**

对于每个测试用例，输出完成比赛的最短时间，或根据要求输出结果。

**数据范围与提示：**

$1 \le t \le 100$

$2 \le n \le 1000$

$0 \le \text{bullets} \le 1000$

$\text{Track}[i] \in \{'S', 'E', '0', '#'\}$

$\text{Track}[0]='S$, $\text{Track}[n-1]='E'$

**样例输入：**

```
10
7 3
S00000E
2 2
SE
4 1
S00E
8 1
S0000##E
8 3
S0#00#0E
7 2
S0#0##E
10 4
S00#0#0##E
5 2
S000E
7 1
S0##00E
9 0
S0000##0E
```

**样例输出：**

```
6
1
3
13
7
12
9
4
12
15
```

 **本翻译由 AI 自动生成**

