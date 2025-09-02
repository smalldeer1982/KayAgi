---
title: "Eating Soup"
layout: "post"
diff: 普及-
pid: CF1163A
tag: []
---

# Eating Soup

## 题目描述

The three friends, Kuro, Shiro, and Katie, met up again! It's time for a party...

What the cats do when they unite? Right, they have a party. Since they wanted to have as much fun as possible, they invited all their friends. Now $ n $ cats are at the party, sitting in a circle and eating soup. The rules are simple: anyone having finished their soup leaves the circle.

Katie suddenly notices that whenever a cat leaves, the place where she was sitting becomes an empty space, which means the circle is divided into smaller continuous groups of cats sitting next to each other. At the moment Katie observes, there are $ m $ cats who left the circle. This raises a question for Katie: what is the maximum possible number of groups the circle is divided into at the moment?

Could you help her with this curiosity?

You can see the examples and their descriptions with pictures in the "Note" section.

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 1000 $ , $ 0 \leq m \leq n $ ) — the initial number of cats at the party and the number of cats who left the circle at the moment Katie observes, respectively.

## 输出格式

Print a single integer — the maximum number of groups of cats at the moment Katie observes.

## 说明/提示

In the first example, originally there are $ 7 $ cats sitting as shown below, creating a single group:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/582841c5dfb385439eea8c43d7ec4b1600b2e8bf.png)At the observed moment, $ 4 $ cats have left the table. Suppose the cats $ 2 $ , $ 3 $ , $ 5 $ and $ 7 $ have left, then there are $ 3 $ groups remaining. It is possible to show that it is the maximum possible number of groups remaining.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/b09fab4219f78478e7216cc25f298db91c1649f6.png)In the second example, there are $ 6 $ cats sitting as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/44c3b731251174253272f06b55bec85d62ac7660.png)At the observed moment, $ 2 $ cats have left the table. Suppose the cats numbered $ 3 $ and $ 6 $ left, then there will be $ 2 $ groups remaining ( $ \{1, 2\} $ and $ \{4, 5\} $ ). It is impossible to have more than $ 2 $ groups of cats remaining.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/b113b3b66afa92745963d53380bedced5a41e1a8.png)In the third example, no cats have left, so there is $ 1 $ group consisting of all cats.

In the fourth example, all cats have left the circle, so there are $ 0 $ groups.

## 样例 #1

### 输入

```
7 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 0

```

### 输出

```
1

```

## 样例 #4

### 输入

```
2 2

```

### 输出

```
0

```

