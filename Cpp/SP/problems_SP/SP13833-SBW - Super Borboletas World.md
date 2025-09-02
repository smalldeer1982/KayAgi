---
title: "SBW - Super Borboletas World"
layout: "post"
diff: 难度0
pid: SP13833
tag: []
---

# SBW - Super Borboletas World

## 题目描述

超级蝴蝶世界

经过修复，输入/输出模块现已正常，并对所有提交进行了重新评审。

著名程序员 Raphaell 创建了全球最大的游戏开发公司 BGM（Boboleta's GameMaker）。最近，他的一款游戏——S.B.W（超级蝴蝶世界）变得非常受欢迎，因此他决定推出 S.B.W 的在线版本。为此，Raphaell 将公开该游戏的源代码和机制，任何人都可以对其进行改进。

起初，这个游戏由三个主要操作组成，用户可以根据需要多次调用这些操作。游戏由 K 个数组列表组成，每个列表最多包含 N 个整数。三种操作描述如下：

- 操作 `2 x y`：在第 `x` 个列表的末尾插入整数 `y`。
- 操作 `1 x y`：清空从 `x` 到 `y` 范围内的所有列表，包括 `x` 和 `y`。
- 操作 `0 x y`：计算索引从 `x` 到 `y` 范围内各个列表中所有可能的连续异或和，并返回最大值。异或运算是指 "Exclusive OR" 操作。

Raphaell 有一个原始伪代码用于实现这些功能：

```plaintext
m <- array( array() )

def insert(x, y):
    insert y to m[x]

def clear(x, y):
    for i <- x to y:
        clear m[i]

def max_xor(x, y):
    best <- 0
    for i <- 0 to sizeOf m[x]:
        sum_xor <- 0
        for j <- i to sizeOf m[x]:
            sum_xor <- sum_xor (xor) m[x][j]
            best <- max(best, sum_xor)
    if x < y:
        best <- max(best, max_xor(x + 1, y))
    return best
```

这种实现方法对于游戏的离线版本是高效的。然而，由于线上版本可能同时接入数千名玩家，因此需要进行大量优化以确保流畅运行。尽管他的朋友极力尝试提高性能，但仍未取得良好的结果。

### 输入格式

输入包含多个测试用例。每个测试用例以一个整数 $Q$（$1 \le Q \le 10^5$）开始，表示要执行的操作次数。接下来的 $Q$ 行描述具体的操作：

- `0 x y`：在范围 `x` 到 `y` 之间的每个列表中计算所有可能的连续异或和，并返回最大值。
- `1 x y`：清空范围 `x` 到 `y` 之间的所有列表，包括 `x` 和 `y`。
- `2 x y`：在第 `x` 个列表的末尾插入整数 `y`。

输入的最后用一行单独的 `0` 结束。

### 输出格式

对于每个请求 `0 x y`，输出其最大可能的异或和，结果以一个整数形式输出在一行中。

### 示例

**输入**

```
14
2 2 1
2 2 2
2 2 1
2 2 1
2 2 2
2 3 1
2 3 2
2 3 7
0 1 2
0 2 3
1 3 3
0 1 3
1 1 3
0 1 3
0
```

**输出**

```
3
7
3
0
```

 **本翻译由 AI 自动生成**

