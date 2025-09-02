---
title: "Attribute Checks"
layout: "post"
diff: 普及+/提高
pid: CF2025D
tag: ['动态规划 DP']
---

# Attribute Checks

## 题目描述

Imagine a game where you play as a character that has two attributes: "Strength" and "Intelligence", that are at zero level initially.

During the game, you'll acquire $ m $ attribute points that allow you to increase your attribute levels — one point will increase one of the attributes by one level. But sometimes, you'll encounter a so-called "Attribute Checks": if your corresponding attribute is high enough, you'll pass it; otherwise, you'll fail it.

Spending some time, you finally prepared a list which contains records of all points you got and all checks you've met. And now you're wondering: what is the maximum number of attribute checks you can pass in a single run if you'd spend points wisely?

Note that you can't change the order of records.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le m \le 5000 $ ; $ m < n \le 2 \cdot 10^6 $ ) — the number of records in the list and the total number of points you'll get during the game.

The second line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ -m \le r_i \le m $ ), where $ r_i $ encodes the $ i $ -th record:

- If $ r_i = 0 $ , then the $ i $ -th record is an acquiring one attribute point. You can spend to level up either Strength or Intelligence;
- If $ r_i > 0 $ , then it's an Intelligence check: if your Intelligence level is greater than or equal to $ |r_i| $ , you pass.
- If $ r_i < 0 $ , then it's a Strength check: if your Strength level is greater than or equal to $ |r_i| $ , you pass.

Additional constraint on the input: the sequence $ r_1, r_2, \dots, r_n $ contains exactly $ m $ elements equal to $ 0 $ .

## 输出格式

Print one integer — the maximum number of checks you can pass.

## 说明/提示

In the first test, it's optimal to spend each point in Strength, so you'll fail $ 2 $ Intelligence checks but pass $ 3 $ Strength checks.

In the second test, you'll fail both checks, since the first point you get comes after the checks.

In the third test, one of the optimal strategies is:

1. spend the first point on Intelligence;
2. spend the second point on Strength;
3. spend the third point on Strength;

 As a result, you'll pass $ 2 $ Intelligence checks $ r_3 $ and $ r_9 $ and $ 2 $ Strength checks $ r_7 $ and $ r_8 $ .

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 1
1 -1 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
9 3
0 0 1 0 2 -3 -2 -2 1
```

### 输出

```
4
```

