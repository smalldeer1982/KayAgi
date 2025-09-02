---
title: "Urban Planning"
layout: "post"
diff: 省选/NOI-
pid: CF2068B
tag: []
---

# Urban Planning

## 题目描述

你负责规划一座新城市！该城市将用一个矩形网格表示，其中每个单元格要么是公园，要么是建筑区。

居民自然希望在城市的公园中散步。具体来说，一个矩形散步区域是指满足以下条件的矩形网格区域：
- 在水平和垂直方向上都至少有 2 个单元格
- 矩形边界上的所有单元格都是公园
- 矩形内部的单元格可以是任意类型

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/650c150729643ceb8f9e562a8913c8a60e9dc725.png) 示例矩形散步区域（深色背景单元格）。你最喜欢的数字是 $k$。为了留下永恒的印记，你需要设计一个恰好包含 $k$ 个矩形散步区域的城市。


## 输入格式

输入包含单个整数 $k$（$0 \le k \le 4.194 \times 10^{12}$）。

## 输出格式

第一行输出两个整数 $h$ 和 $w$（$1 \le h, w \le 2025$），表示网格的高度和宽度。接下来输出 $h$ 行，每行包含 $w$ 个字符，其中 \# 表示公园，. 表示建筑区。

保证对于给定范围内的任意 $k$ 值，都存在符合尺寸限制的解。任何在给定尺寸范围内且恰好包含 $k$ 个矩形散步区域的方案都将被接受。


## 说明/提示

在样例中，以下是五个可能的矩形散步区域：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/b694d5d43c1db4ce1affb71fd91eaaed1c603a15.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/c0a42475b8538edc0aa9b0c24e8955d114133a0f.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/3749b31d2137b1ef71c23fc5617c6194a72b29cb.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/63f27f79f27b688ddc9ce6f1ac0e857ca91dc99e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068B/e7cc09f62ba9dcdd869e9d3cff8988b91b93cc46.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
```

### 输出

```
3 4
####
#.##
####
```

