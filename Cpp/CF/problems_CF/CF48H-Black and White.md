---
title: "Black and White"
layout: "post"
diff: 省选/NOI-
pid: CF48H
tag: []
---

# Black and White

## 题目描述

题目大意：用如下图的a（全黑），b（全白），c（一个角黑，一个角白）三种1×1大小瓷砖铺一个N×M大小的地板，要求一条地板内部格子边的两边必须同黑或同白。

![](www.luogu.org/upload/pic/16880.png)

瓷砖的输出方法：

全黑：
```
##
##
```
全白：
```
..
..
```
半黑半白：
```
\#
.\

./
/#

\.
#\

#/
/.
```

（依次对应图片中的从左至右6个图案）

## 输入格式

第一行：两个数，表示地面的长和宽。

第二行：三个数，表示a,b,c三种瓷砖的个数。

## 输出格式

按要求方法将整个地板输出。

感谢@JXPGSWT_54088 提供的翻译

## 样例 #1

### 输入

```
2 2
0 0 4

```

### 输出

```
<span class="tex-span">\</span>../
#<span class="tex-span">\</span>/#
<span class="tex-span">\</span>##/
.<span class="tex-span">\</span>/.

```

## 样例 #2

### 输入

```
2 3
1 2 3

```

### 输出

```
###/<span class="tex-span">\</span>#
##/..<span class="tex-span">\</span>
#/....
/.....

```

