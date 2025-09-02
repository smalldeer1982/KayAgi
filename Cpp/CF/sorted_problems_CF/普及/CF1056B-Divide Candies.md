---
title: "Divide Candies"
layout: "post"
diff: 普及/提高-
pid: CF1056B
tag: []
---

# Divide Candies

## 题目描述

Arkady and his friends love playing checkers on an $ n \times n $ field. The rows and the columns of the field are enumerated from $ 1 $ to $ n $ .

The friends have recently won a championship, so Arkady wants to please them with some candies. Remembering an old parable (but not its moral), Arkady wants to give to his friends one set of candies per each cell of the field: the set of candies for cell $ (i, j) $ will have exactly $ (i^2 + j^2) $ candies of unique type.

There are $ m $ friends who deserve the present. How many of these $ n \times n $ sets of candies can be split equally into $ m $ parts without cutting a candy into pieces? Note that each set has to be split independently since the types of candies in different sets are different.

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10^9 $ , $ 1 \le m \le 1000 $ ) — the size of the field and the number of parts to split the sets into.

## 输出格式

Print a single integer — the number of sets that can be split equally.

## 说明/提示

In the first example, only the set for cell $ (3, 3) $ can be split equally ( $ 3^2 + 3^2 = 18 $ , which is divisible by $ m=3 $ ).

In the second example, the sets for the following cells can be divided equally:

- $ (1, 2) $ and $ (2, 1) $ , since $ 1^2 + 2^2 = 5 $ , which is divisible by $ 5 $ ;
- $ (1, 3) $ and $ (3, 1) $ ;
- $ (2, 4) $ and $ (4, 2) $ ;
- $ (2, 6) $ and $ (6, 2) $ ;
- $ (3, 4) $ and $ (4, 3) $ ;
- $ (3, 6) $ and $ (6, 3) $ ;
- $ (5, 5) $ .

In the third example, sets in all cells can be divided equally, since $ m = 1 $ .

## 样例 #1

### 输入

```
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6 5

```

### 输出

```
13

```

## 样例 #3

### 输入

```
1000000000 1

```

### 输出

```
1000000000000000000

```

