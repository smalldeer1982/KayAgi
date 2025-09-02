---
title: "Mirror, Mirror"
layout: "post"
diff: 难度0
pid: UVA466
tag: []
---

# Mirror, Mirror

## 题目描述

输入一个包含黑白格的正方形图案及其经若干次“变换”后的状态。请写一个程序输出满足条件的变换。一次变换**有且仅有**一下形式：

- 90度旋转：顺时针旋转90度
- 180度旋转：顺时针旋转180度
- 270度旋转：顺时针旋转270度
- 垂直翻转：图案被置于其上的水平镜子反射（即垂直翻转）
- 组合：先旋转，随后再翻转
- 保留：不进行任何修改，新图形与旧图形**完全一致**
- 其他：不适用于以上的任意一条


每一组输出应以英文句号结尾。具体的格式见样例输出。

## 输入格式

输入包含若干组数据（以EOF作结尾），对于每一组，会先输入图案的边长 $N$ ($1 \le N \le 10$)，接下来每行会包括原图案和经变换后的图案的对应一行，以空格分隔。（具体见样例）黑格由 `X` 标识，白格由 `.` 标识。

## 输出格式

对于每一组数据，你需要输出一个描述变换过程的英文句子。每一个句子由数据的ID开头（ID从 1 开始），由最“小”的变换的描述结束 **（具体格式见样例）**。比较变换“大小”时，旋转操作比反射操作更“小”，而度数小的旋转操作比度数大的更“小”。注意，保留操作是**最小的**。

## 样例 #1

### 输入

```
5
X...X ....X
.X... ...X.
...X. .X...
..X.X ..X..
....X XX..X
6
....XX X....X
...X.. X.X...
XX..X. .X..X.
..X... ...X.X
...X.. ..X...
..X..X ..X...
2
X. X.
.X .X
4
..X. ...X
XX.. ....
.... XX..
...X ..X.
5
X.... .X...
.X... ..X..
.X... ..X..
...X. ....X
....X X....
4
.X.. ..X.
.X.X X...
.... ..XX
..X. ....
2
.. XX
XX ..
```

### 输出

```
Pattern 1 was rotated 90 degrees.
Pattern 2 was rotated 270 degrees.
Pattern 3 was preserved.
Pattern 4 was reflected vertically.
Pattern 5 was improperly transformed.
Pattern 6 was reflected vertically and rotated 270 degrees.
Pattern 7 was rotated 180 degrees.
```

