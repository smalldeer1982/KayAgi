---
title: "Is This a Zebra?"
layout: "post"
diff: 普及-
pid: CF926C
tag: []
---

# Is This a Zebra?

## 题目描述

A camera you have accidentally left in a desert has taken an interesting photo. The photo has a resolution of $ n $ pixels width, and each column of this photo is all white or all black. Thus, we can represent the photo as a sequence of $ n $ zeros and ones, where $ 0 $ means that the corresponding column is all white, and $ 1 $ means that the corresponding column is black.

You think that this photo can contain a zebra. In this case the whole photo should consist of several (possibly, only one) alternating black and white stripes of equal width. For example, the photo $ [0,0,0,1,1,1,0,0,0] $ can be a photo of zebra, while the photo $ [0,0,0,1,1,1,1] $ can not, because the width of the black stripe is $ 3 $ , while the width of the white stripe is $ 4 $ . Can the given photo be a photo of zebra or not?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the width of the photo.

The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=1 $ ) — the description of the photo. If $ a_{i} $ is zero, the $ i $ -th column is all black. If $ a_{i} $ is one, then the $ i $ -th column is all white.

## 输出格式

If the photo can be a photo of zebra, print "YES" (without quotes). Otherwise, print "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

The first two examples are described in the statements.

In the third example all pixels are white, so the photo can be a photo of zebra.

In the fourth example the width of the first stripe is equal to three (white color), the width of the second stripe is equal to three (black), and the width of the third stripe is equal to two (white). Thus, not all stripes have equal length, so this photo is not a photo of zebra.

## 样例 #1

### 输入

```
9
0 0 0 1 1 1 0 0 0

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
7
0 0 0 1 1 1 1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
1 1 1 1 1

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
8
1 1 1 0 0 0 1 1

```

### 输出

```
NO

```

## 样例 #5

### 输入

```
9
1 1 0 1 1 0 1 1 0

```

### 输出

```
NO

```

