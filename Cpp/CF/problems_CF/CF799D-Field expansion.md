---
title: "Field expansion"
layout: "post"
diff: 提高+/省选-
pid: CF799D
tag: []
---

# Field expansion

## 题目描述

In one of the games Arkady is fond of the game process happens on a rectangular field. In the game process Arkady can buy extensions for his field, each extension enlarges one of the field sizes in a particular number of times. Formally, there are $ n $ extensions, the $ i $ -th of them multiplies the width or the length (by Arkady's choice) by $ a_{i} $ . Each extension can't be used more than once, the extensions can be used in any order.

Now Arkady's field has size $ h×w $ . He wants to enlarge it so that it is possible to place a rectangle of size $ a×b $ on it (along the width or along the length, with sides parallel to the field sides). Find the minimum number of extensions needed to reach Arkady's goal.

## 输入格式

The first line contains five integers $ a $ , $ b $ , $ h $ , $ w $ and $ n $ ( $ 1<=a,b,h,w,n<=100000 $ ) — the sizes of the rectangle needed to be placed, the initial sizes of the field and the number of available extensions.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 2<=a_{i}<=100000 $ ), where $ a_{i} $ equals the integer a side multiplies by when the $ i $ -th extension is applied.

## 输出格式

Print the minimum number of extensions needed to reach Arkady's goal. If it is not possible to place the rectangle on the field with all extensions, print -1. If the rectangle can be placed on the initial field, print 0.

## 说明/提示

In the first example it is enough to use any of the extensions available. For example, we can enlarge $ h $ in $ 5 $ times using the second extension. Then $ h $ becomes equal $ 10 $ and it is now possible to place the rectangle on the field.

## 样例 #1

### 输入

```
3 3 2 4 4
2 5 4 10

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3 3 3 5
2 3 5 4 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 5 1 2 3
2 2 3

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
3 4 1 1 3
2 3 2

```

### 输出

```
3

```

