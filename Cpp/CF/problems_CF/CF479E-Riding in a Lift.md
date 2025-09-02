---
title: "Riding in a Lift"
layout: "post"
diff: 普及+/提高
pid: CF479E
tag: ['动态规划 DP', '前缀和']
---

# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line of the input contains four space-separated integers $ n $ , $ a $ , $ b $ , $ k $ ( $ 2<=n<=5000 $ , $ 1<=k<=5000 $ , $ 1<=a,b<=n $ , $ a≠b $ ).

## 输出格式

Print a single integer — the remainder after dividing the sought number of sequences by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 4 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 3 4 1

```

### 输出

```
0

```

