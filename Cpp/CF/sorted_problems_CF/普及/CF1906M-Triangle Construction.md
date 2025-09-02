---
title: "Triangle Construction"
layout: "post"
diff: 普及/提高-
pid: CF1906M
tag: []
---

# Triangle Construction

## 题目描述

You are given a regular $ N $ -sided polygon. Label one arbitrary side as side $ 1 $ , then label the next sides in clockwise order as side $ 2 $ , $ 3 $ , $ \dots $ , $ N $ . There are $ A_i $ special points on side $ i $ . These points are positioned such that side $ i $ is divided into $ A_i + 1 $ segments with equal length.

For instance, suppose that you have a regular $ 4 $ -sided polygon, i.e., a square. The following illustration shows how the special points are located within each side when $ A = [3, 1, 4, 6] $ . The uppermost side is labelled as side $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/e59a9e9dcf5329e7eff8711f30517212fd26fdbd.png)You want to create as many non-degenerate triangles as possible while satisfying the following requirements. Each triangle consists of $ 3 $ distinct special points (not necessarily from different sides) as its corners. Each special point can only become the corner of at most $ 1 $ triangle. All triangles must not intersect with each other.

Determine the maximum number of non-degenerate triangles that you can create.

A triangle is non-degenerate if it has a positive area.

## 输入格式

The first line consists of an integer $ N $ ( $ 3 \leq N \leq 200\,000 $ ).

The following line consists of $ N $ integers $ A_i $ ( $ 1 \leq A_i \leq 2 \cdot 10^9 $ ).

## 输出格式

Output a single integer representing the maximum number of non-degenerate triangles that you can create.

## 说明/提示

Explanation for the sample input/output #1

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/42eede39a9359517d4b7c742aaa8551dfcdfbb8c.png)Explanation for the sample input/output #2

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/fc47dcb22d8f025c4d1e0997698a6023ed22d7f5.png)

## 样例 #1

### 输入

```
4
3 1 4 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
1
```

