---
title: "osu!mania"
layout: "post"
diff: 入门
pid: CF2009B
tag: ['模拟']
---

# osu!mania

## 题目描述

You are playing your favorite rhythm game, osu!mania. The layout of your beatmap consists of $ n $ rows and $ 4 $ columns. Because notes at the bottom are closer, you will process the bottommost row first and the topmost row last. Each row will contain exactly one note, represented as a '#'.

For each note $ 1, 2, \dots, n $ , in the order of processing, output the column in which the note appears.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

For each test case, the first line contains $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of rows of the beatmap.

The following $ n $ lines contain $ 4 $ characters. The $ i $ -th line represents the $ i $ -th row of the beatmap from the top. It is guaranteed that the characters are either '.' or '#', and exactly one of the characters is '#'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n $ integers on a new line, the column that the $ i $ -th note appears in for all $ i $ from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
3
4
#...
.#..
..#.
...#
2
.#..
.#..
1
...#
```

### 输出

```
4 3 2 1 
2 2 
4
```

