---
title: "New Year Table"
layout: "post"
diff: 普及/提高-
pid: CF140A
tag: []
---

# New Year Table

## 题目描述

Gerald is setting the New Year table. The table has the form of a circle; its radius equals $ R $ . Gerald invited many guests and is concerned whether the table has enough space for plates for all those guests. Consider all plates to be round and have the same radii that equal $ r $ . Each plate must be completely inside the table and must touch the edge of the table. Of course, the plates must not intersect, but they can touch each other. Help Gerald determine whether the table is large enough for $ n $ plates.

## 输入格式

The first line contains three integers $ n $ , $ R $ and $ r $ ( $ 1<=n<=100 $ , $ 1<=r,R<=1000 $ ) — the number of plates, the radius of the table and the plates' radius.

## 输出格式

Print "YES" (without the quotes) if it is possible to place $ n $ plates on the table by the rules given above. If it is impossible, print "NO".

Remember, that each plate must touch the edge of the table.

## 说明/提示

The possible arrangement of the plates for the first sample is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140A/89a963dd60d2b50871a138411d49010a4f94431a.png)

## 样例 #1

### 输入

```
4 10 4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 10 4

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
1 10 10

```

### 输出

```
YES

```

