---
title: "JZPLIT - Turn on the lights"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP9534
tag: []
---

# JZPLIT - Turn on the lights

## 题目描述

Recently Zippy received a puzzle. It is an n\*m matrix. In each cell of the matrix, there is a switch and a light. Once he flips the switch in a cell, lights in the same column or the same row as the cell (including itself) change to its opposite state (which means: on->off off->on). Zippy wants to turn on all the lights. Please help him to solve the puzzle.

## 输入格式

First line, n, m.

The following n lines, each line is a m-length string, represting the original state. (0 means on and 1 means off)

1<=n,m<=1000

First line, n, m.

## 输出格式

n lines, each line is a m-length string. It's obvious that if a valid solution exists, there exists a solution that every switch is flipped no more than once. So 1 means the switch is flipped once and 0 means the swtich remains unflipped.

It's guaranteed that there always exists a solution. If there are multiple solutions, output any of them.

## 样例 #1

### 输入

```
2 3
010
010
```

### 输出

```
010
101
```

