---
title: "Views Matter"
layout: "post"
diff: 普及/提高-
pid: CF1061B
tag: []
---

# Views Matter

## 题目描述

You came to the exhibition and one exhibit has drawn your attention. It consists of $ n $ stacks of blocks, where the $ i $ -th stack consists of $ a_i $ blocks resting on the surface.

The height of the exhibit is equal to $ m $ . Consequently, the number of blocks in each stack is less than or equal to $ m $ .

There is a camera on the ceiling that sees the top view of the blocks and a camera on the right wall that sees the side view of the blocks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/f0bac26a304f5339f8800747dc3cc95aa0eba485.png)Find the maximum number of blocks you can remove such that the views for both the cameras would not change.

Note, that while originally all blocks are stacked on the floor, it is not required for them to stay connected to the floor after some blocks are removed. There is no gravity in the whole exhibition, so no block would fall down, even if the block underneath is removed. It is not allowed to move blocks by hand either.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 100\,000 $ , $ 1 \le m \le 10^9 $ ) — the number of stacks and the height of the exhibit.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le m $ ) — the number of blocks in each stack from left to right.

## 输出格式

Print exactly one integer — the maximum number of blocks that can be removed.

## 说明/提示

The following pictures illustrate the first example and its possible solution.

Blue cells indicate removed blocks. There are $ 10 $ blue cells, so the answer is $ 10 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/5c39371a94179ca28ceb7e2172bc3ac014dca01f.png)

## 样例 #1

### 输入

```
5 6
3 3 3 3 3

```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 5
1 2 4

```

### 输出

```
3
```

## 样例 #3

### 输入

```
5 5
2 3 1 4 4

```

### 输出

```
9
```

## 样例 #4

### 输入

```
1 1000
548

```

### 输出

```
0
```

## 样例 #5

### 输入

```
3 3
3 1 1

```

### 输出

```
1
```

