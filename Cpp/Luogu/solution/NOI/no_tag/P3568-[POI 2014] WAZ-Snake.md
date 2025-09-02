# [POI 2014] WAZ-Snake

## 题目描述

A snake fills a ![](http://main.edu.pl/images/OI21/waz-en-tex.1.png) board completely.

Successive segments of the snake are numbered from ![](http://main.edu.pl/images/OI21/waz-en-tex.2.png) to ![](http://main.edu.pl/images/OI21/waz-en-tex.3.png).

The segments with successive numbers (i.e., 1 and 2, 2 and 3, 3 and 4...) occupy squares  that share an edge.

For example, a snake can fill a ![](http://main.edu.pl/images/OI21/waz-en-tex.4.png) board as follows:

The snake's segment numbers in some of the squares have been erased.

  Can you reconstruct the snake?

一只蛇被放在了一块3\*n的木板上（填充满了），蛇被分为多个小段，小段的编号是1到3n。比如说蛇可以填写一个3\*9的木板，如下所示：


部分木板上的蛇段已删遮挡。


你能重建蛇吗？


## 样例 #1

### 输入

```
9
0 0 5 0 17 0 0 0 21
8 0 0 3 16 0 0 25 0
0 0 0 0 0 0 0 0 23
```

### 输出

```
7 6 5 4 17 18 19 20 21
8 1 2 3 16 15 26 25 22
9 10 11 12 13 14 27 24 23
```

