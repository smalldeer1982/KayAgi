---
title: "Functions again"
layout: "post"
diff: 普及/提高-
pid: CF788A
tag: []
---

# Functions again

## 题目描述

Something happened in Uzhlyandia again... There are riots on the streets... Famous Uzhlyandian superheroes Shean the Sheep and Stas the Giraffe were called in order to save the situation. Upon the arriving, they found that citizens are worried about maximum values of the Main Uzhlyandian Function $ f $ , which is defined as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788A/3dafed09a51e28ade00bc9bec53248a85d7ce6d3.png)In the above formula, $ 1<=l&lt;r<=n $ must hold, where $ n $ is the size of the Main Uzhlyandian Array $ a $ , and $ |x| $ means absolute value of $ x $ . But the heroes skipped their math lessons in school, so they asked you for help. Help them calculate the maximum value of $ f $ among all possible values of $ l $ and $ r $ for the given array $ a $ .

## 输入格式

The first line contains single integer $ n $ ( $ 2<=n<=10^{5} $ ) — the size of the array $ a $ .

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ (- $ 10^{9}<=a_{i}<=10^{9} $ ) — the array elements.

## 输出格式

Print the only integer — the maximum value of $ f $ .

## 说明/提示

In the first sample case, the optimal value of $ f $ is reached on intervals $ [1,2] $ and $ [2,5] $ .

In the second case maximal value of $ f $ is reachable only on the whole array.

## 样例 #1

### 输入

```
5
1 4 2 3 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 5 4 7

```

### 输出

```
6
```

