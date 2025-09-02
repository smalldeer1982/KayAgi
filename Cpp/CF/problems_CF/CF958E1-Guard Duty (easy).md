---
title: "Guard Duty (easy)"
layout: "post"
diff: 普及+/提高
pid: CF958E1
tag: []
---

# Guard Duty (easy)

## 题目描述

The Rebel fleet is afraid that the Empire might want to strike back again. Princess Heidi needs to know if it is possible to assign $ R $ Rebel spaceships to guard $ B $ bases so that every base has exactly one guardian and each spaceship has exactly one assigned base (in other words, the assignment is a perfect matching). Since she knows how reckless her pilots are, she wants to be sure that any two (straight) paths – from a base to its assigned spaceship – do not intersect in the galaxy plane (that is, in 2D), and so there is no risk of collision.

## 输入格式

The first line contains two space-separated integers $ R,B(1<=R,B<=10) $ . For $ 1<=i<=R $ , the $ i+1 $ -th line contains two space-separated integers $ x_{i} $ and $ y_{i} $ ( $ |x_{i}|,|y_{i}|<=10000 $ ) denoting the coordinates of the $ i $ -th Rebel spaceship. The following $ B $ lines have the same format, denoting the position of bases. It is guaranteed that no two points coincide and that no three points are on the same line.

## 输出格式

If it is possible to connect Rebel spaceships and bases so as satisfy the constraint, output Yes, otherwise output No (without quote).

## 说明/提示

For the first example, one possible way is to connect the Rebels and bases in order.

For the second example, there is no perfect matching between Rebels and bases.

## 样例 #1

### 输入

```
3 3
0 0
2 0
3 1
-2 1
0 3
2 2

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2 1
1 0
2 2
3 1

```

### 输出

```
No

```

