---
title: "LOL Lovers"
layout: "post"
diff: 入门
pid: CF1912L
tag: ['枚举', '前缀和']
---

# LOL Lovers

## 题目描述

There are $ n $ food items lying in a row on a long table. Each of these items is either a loaf of bread (denoted as a capital Latin letter 'L' with ASCII code 76) or an onion (denoted as a capital Latin letter 'O' with ASCII code 79). There is at least one loaf of bread and at least one onion on the table.

You and your friend want to divide the food on the table: you will take a prefix of this row (several leftmost items), and the friend will take the rest. However, there are several restrictions:

1. Each person should have at least one item.
2. The number of your loaves should differ from the number of your friend's loaves.
3. The number of your onions should differ from the number of your friend's onions.

 Find any correct division and print the number of items you take or report that there is no answer.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 200 $ ) — the number of food items on the table. The second line contains a string of length $ n $ consisting of letters 'L' and 'O'. $ i $ -th symbol represents the type of the $ i $ -th food item on the table: 'L' stands for a loaf of bread, and 'O' stands for an onion. It is guaranteed that this string contains at least one letter 'L' and at least one letter 'O'.

## 输出格式

Print one integer — a number $ k $ such that, if you take $ k $ leftmost items and your friend takes the remaining $ n - k $ items, each of you and your friend get at least one item, your number of loaves is different from your friend's, and your number of onions is different from your friend's. If there are several possible answers, print any of them. If there are no possible answers, print the number $ -1 $ .

## 说明/提示

In the first example, in any division the left and the right part contain one loaf of bread.

In the second example, the division is 'L' and 'O', and in these two strings the number of loaves is different (1 and 0) and the number of onions is different (0 and 1).

In the third example, any number 1, 2 or 3 is a correct answer.

## 样例 #1

### 输入

```
3
LOL
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
LO
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
LLLO
```

### 输出

```
1
```

## 样例 #4

### 输入

```
4
OLOL
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
10
LLOOOOLLLO
```

### 输出

```
5
```



---

