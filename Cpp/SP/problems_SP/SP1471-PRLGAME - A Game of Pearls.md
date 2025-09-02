---
title: "PRLGAME - A Game of Pearls"
layout: "post"
diff: 难度0
pid: SP1471
tag: []
---

# PRLGAME - A Game of Pearls

## 题目描述

珍珠游戏的目标是利用以下 12 种珍珠设计图案各一次，组合成一个大的珍珠图案。这些图案可以任意旋转或翻转。请参考下图。

```
                   空白格子



                  一个大的珍珠设计示例



使用字符代替颜色的珍珠设计示例



          图案 A



          图案 B



          图案 C



          图案 D



          图案 E



          图案 F



          图案 G



          图案 H



          图案 I



          图案 J



          图案 K



          图案 L
```

## 输入格式

输入由十个测试用例组成（依次提供，你需要处理所有用例）。每个测试用例包含一个大图案，'A'-'L'表示填充的格子，'.'表示空白格子。可以假设所有珍珠设计图案完全放置在空白格子中。

## 输出格式

输出一个没有任何空白格子的大图案，每个珍珠设计图案只使用一次。如果不存在这样的组合，则输出 `No solution`（不带引号）。如果存在多个解，可以输出任意一个解。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
.
..
...
....
.....
.....C
...CCC.
EEEHH...
E.HHH....
E.........
[and 9 test cases more]
```

### 输出

```
B
BK
BKK
BJKK
JJJDD
GJGDDC
GGGCCCI
EEEHHIIA
ELHHHIAAF
ELLLLIFFFF
[and 9 test cases more]
```

