---
title: "Great Vova Wall (Version 2)"
layout: "post"
diff: 提高+/省选-
pid: CF1092D2
tag: []
---

# Great Vova Wall (Version 2)

## 题目描述

Vova's family is building the Great Vova Wall (named by Vova himself). Vova's parents, grandparents, grand-grandparents contributed to it. Now it's totally up to Vova to put the finishing touches.

The current state of the wall can be respresented by a sequence $ a $ of $ n $ integers, with $ a_i $ being the height of the $ i $ -th part of the wall.

Vova can only use $ 2 \times 1 $ bricks to put in the wall (he has infinite supply of them, however).

Vova can put bricks only horizontally on the neighbouring parts of the wall of equal height. It means that if for some $ i $ the current height of part $ i $ is the same as for part $ i + 1 $ , then Vova can put a brick there and thus increase both heights by 1. Obviously, Vova can't put bricks in such a way that its parts turn out to be off the borders (to the left of part $ 1 $ of the wall or to the right of part $ n $ of it).

Note that Vova can't put bricks vertically.

Vova is a perfectionist, so he considers the wall completed when:

- all parts of the wall has the same height;
- the wall has no empty spaces inside it.

Can Vova complete the wall using any amount of bricks (possibly zero)?

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of parts in the wall.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the initial heights of the parts of the wall.

## 输出格式

Print "YES" if Vova can complete the wall using any amount of bricks (possibly zero).

Print "NO" otherwise.

## 说明/提示

In the first example Vova can put a brick on parts 2 and 3 to make the wall $ [2, 2, 2, 2, 5] $ and then put 3 bricks on parts 1 and 2 and 3 bricks on parts 3 and 4 to make it $ [5, 5, 5, 5, 5] $ .

In the second example Vova can put no bricks in the wall.

In the third example the wall is already complete.

## 样例 #1

### 输入

```
5
2 1 1 2 5

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
4 5 3

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
2
10 10

```

### 输出

```
YES

```

