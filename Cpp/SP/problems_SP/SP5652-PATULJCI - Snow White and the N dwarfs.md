---
title: "PATULJCI - Snow White and the N dwarfs"
layout: "post"
diff: 提高+/省选-
pid: SP5652
tag: []
---

# PATULJCI - Snow White and the N dwarfs

## 题目描述

Snow White and the N dwarfs live in the forest. While the dwarfs mine away Snow White hangs around social networks.

Each morning the dwarfs form a long line and go whistling away to the mine. Snow White runs around them and snaps pictures to upload onto her favorite social network.

When dwarfs enter the mine, Snow White goes back to their house and goes through the pictures, selecting pretty ones. Each dwarf has a colored cap, and there are C different colors. A picture is pretty if more than half caps on it are of the same color. In other words, if there are K dwarfs on the picture, it is pretty if strictly more than K / 2 dwarfs have same colored caps.

Write a program that will check for a set of M pictures if they are pretty, and what color is dominating if they are.

## 输出格式

Output M lines. For each picture output “no” if Snow White doesn't think the picture is pretty, and “yes X”, where X is the color dominating on the picture, if she does.

## 样例 #1

### 输入

```
10 3
1 2 1 2 1 2 3 2 3 3
8
1 2
1 3
1 4
1 5
2 5
2 6
6 9
7 10
```

### 输出

```
no
yes 1
no
yes 1
no
yes 2
no
yes 3
```

