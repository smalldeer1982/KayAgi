---
title: "TRIOMINO - Triomino Game"
layout: "post"
diff: 难度0
pid: SP2961
tag: []
---

# TRIOMINO - Triomino Game

## 题目描述

X 和 Y 在一个 $2\times$$N$ 的空棋盘玩游戏，以 X -> Y -> X -> Y -> X -> Y 的顺序交替移动。在每一次移动中，X 或 Y 必须在棋盘上的 $4$ 个可能方向中往棋盘放置一个 L 状的图形(如下图所示)：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2961/42133d51c84789475195b5ab5cf4df9dd7aaec92.png)![](https://cdn.luogu.com.cn/upload/image_hosting/2lmw8ugc.png)![](https://cdn.luogu.com.cn/upload/image_hosting/ttw2zb5h.png)![](https://cdn.luogu.com.cn/upload/image_hosting/gzv4uwoa.png)

放置的物品不能重叠。无法做出有效移动的玩家将会失败。  

当 X 和 Y 都是最优的情况下，找出谁会赢。

$Translate$ $by$ $linyuhuai$

## 输入格式

第 $1$ 行：一个整数 $T$ ，表示测试数据的组数。

第 $1+T$ 行：一个整数 $N$，表示棋盘的大小。

## 输出格式

输出 X 或 Y 以表示谁赢了游戏。输出之后请注意换行。

## 说明/提示

对于 $100\%$ 的数据 $T\leq50,T\leq800$。

## 样例 #1

### 输入

```
2
3
4
```

### 输出

```
X
Y
```

