---
title: "Robot Program"
layout: "post"
diff: 普及-
pid: CF2070B
tag: ['模拟', '数学']
---

# Robot Program

## 题目描述

在坐标轴上有一个机器人。初始时，机器人位于点 $x$（$x \ne 0$）。机器人有一个长度为 $n$ 的命令序列，由字符组成，其中 L 表示向左移动一个单位（从点 $p$ 移动到点 $(p-1)$），R 表示向右移动一个单位（从点 $p$ 移动到点 $(p+1)$）。

机器人开始执行这个命令序列（每秒执行一个命令，按顺序执行）。然而，每当机器人到达点 0 时，已执行命令的计数器会被重置（即它会从头开始重新执行整个命令序列）。如果机器人完成了所有命令且未处于 0 点，它将停止运行。

你的任务是计算在接下来的 $k$ 秒内，机器人会进入点 0 多少次。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$x$ 和 $k$（$1 \le n \le 2 \cdot 10^5$；$-n \le x \le n$；$n \le k \le 10^{18}$）。

每个测试用例的第二行包含一个由 $n$ 个字符 L 和/或 R 组成的字符串 $s$。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——在接下来的 $k$ 秒内机器人进入点 0 的次数。

## 说明/提示

第一个示例中，机器人移动路径为：$2 \rightarrow 1 \rightarrow \underline{0} \rightarrow -1 \rightarrow -2 \rightarrow -1$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，点 0 被进入 1 次。

第二个示例中，机器人移动路径为：$-1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1$。机器人运行了 8 秒，点 0 被进入 4 次。

第三个示例中，机器人移动路径为：$-2 \rightarrow -3 \rightarrow -2 \rightarrow -1 \rightarrow \underline{0} \rightarrow -1$。机器人运行了 5 秒，点 0 被进入 1 次。

第四个示例中，机器人移动路径为：$3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 3 \rightarrow 2$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，未到达点 0。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2 6
LLR
2 -1 8
RL
4 -2 5
LRRR
5 3 7
LRRLL
1 1 1
L
3 -1 4846549234412827
RLR
```

### 输出

```
1
4
1
0
1
2423274617206414
```

