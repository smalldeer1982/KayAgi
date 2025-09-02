---
title: "Pythagorean Triples"
layout: "post"
diff: 普及/提高-
pid: CF707C
tag: []
---

# Pythagorean Triples

## 题目描述

Katya studies in a fifth grade. Recently her class studied right triangles and the Pythagorean theorem. It appeared, that there are triples of positive integers such that you can construct a right triangle with segments of lengths corresponding to triple. Such triples are called Pythagorean triples.

For example, triples $ (3,4,5) $ , $ (5,12,13) $ and $ (6,8,10) $ are Pythagorean triples.

Here Katya wondered if she can specify the length of some side of right triangle and find any Pythagorean triple corresponding to such length? Note that the side which length is specified can be a cathetus as well as hypotenuse.

Katya had no problems with completing this task. Will you do the same?

## 输入格式

The only line of the input contains single integer $ n $ ( $ 1<=n<=10^{9} $ ) — the length of some side of a right triangle.

## 输出格式

Print two integers $ m $ and $ k $ ( $ 1<=m,k<=10^{18} $ ), such that $ n $ , $ m $ and $ k $ form a Pythagorean triple, in the only line.

In case if there is no any Pythagorean triple containing integer $ n $ , print $ -1 $ in the only line. If there are many answers, print any of them.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707C/80a087cda42609e729836c8476c6d8655d41a6b9.png)Illustration for the first sample.

## 样例 #1

### 输入

```
3

```

### 输出

```
4 5
```

## 样例 #2

### 输入

```
6

```

### 输出

```
8 10
```

## 样例 #3

### 输入

```
1

```

### 输出

```
-1
```

## 样例 #4

### 输入

```
17

```

### 输出

```
144 145
```

## 样例 #5

### 输入

```
67

```

### 输出

```
2244 2245
```

