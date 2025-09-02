---
title: "Valera and Plates"
layout: "post"
diff: 入门
pid: CF369A
tag: []
---

# Valera and Plates

## 题目描述

Valera is a lazy student. He has $ m $ clean bowls and $ k $ clean plates.

Valera has made an eating plan for the next $ n $ days. As Valera is lazy, he will eat exactly one dish per day. At that, in order to eat a dish, he needs exactly one clean plate or bowl. We know that Valera can cook only two types of dishes. He can eat dishes of the first type from bowls and dishes of the second type from either bowls or plates.

When Valera finishes eating, he leaves a dirty plate/bowl behind. His life philosophy doesn't let him eat from dirty kitchenware. So sometimes he needs to wash his plate/bowl before eating. Find the minimum number of times Valera will need to wash a plate/bowl, if he acts optimally.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m,k<=1000 $ ) — the number of the planned days, the number of clean bowls and the number of clean plates.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=2 $ ). If $ a_{i} $ equals one, then on day $ i $ Valera will eat a first type dish. If $ a_{i} $ equals two, then on day $ i $ Valera will eat a second type dish.

## 输出格式

Print a single integer — the minimum number of times Valera will need to wash a plate/bowl.

## 说明/提示

In the first sample Valera will wash a bowl only on the third day, so the answer is one.

In the second sample, Valera will have the first type of the dish during all four days, and since there are only three bowls, he will wash a bowl exactly once.

In the third sample, Valera will have the second type of dish for all three days, and as they can be eaten from either a plate or a bowl, he will never need to wash a plate/bowl.

## 样例 #1

### 输入

```
3 1 1
1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 3 1
1 1 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 2
2 2 2

```

### 输出

```
0

```

## 样例 #4

### 输入

```
8 2 2
1 2 1 2 1 2 1 2

```

### 输出

```
4

```

