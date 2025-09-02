---
title: "Cubes for Masha"
layout: "post"
diff: 普及-
pid: CF887B
tag: ['枚举']
---

# Cubes for Masha

## 题目描述

Absent-minded Masha got set of $ n $ cubes for her birthday.

At each of 6 faces of each cube, there is exactly one digit from 0 to 9. Masha became interested what is the largest natural $ x $ such she can make using her new cubes all integers from 1 to $ x $ .

To make a number Masha can rotate her cubes and put them in a row. After that, she looks at upper faces of cubes from left to right and reads the number.

The number can't contain leading zeros. It's not required to use all cubes to build a number.

Pay attention: Masha can't make digit 6 from digit 9 and vice-versa using cube rotations.

## 输入格式

In first line integer $ n $ is given ( $ 1<=n<=3 $ ) — the number of cubes, Masha got for her birthday.

Each of next $ n $ lines contains 6 integers $ a_{i}_{j} $ ( $ 0<=a_{i}_{j}<=9 $ ) — number on $ j $ -th face of $ i $ -th cube.

## 输出格式

Print single integer — maximum number $ x $ such Masha can make any integers from 1 to $ x $ using her cubes or 0 if Masha can't make even 1.

## 说明/提示

In the first test case, Masha can build all numbers from 1 to 87, but she can't make 88 because there are no two cubes with digit 8.

## 样例 #1

### 输入

```
3
0 1 2 3 4 5
6 7 8 9 0 1
2 3 4 5 6 7

```

### 输出

```
87
```

## 样例 #2

### 输入

```
3
0 1 3 5 6 8
1 2 4 5 7 8
2 3 4 6 7 9

```

### 输出

```
98
```

