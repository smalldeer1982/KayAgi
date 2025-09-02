---
title: "Masha and Bears"
layout: "post"
diff: 普及-
pid: CF907A
tag: []
---

# Masha and Bears

## 题目描述

A family consisting of father bear, mother bear and son bear owns three cars. Father bear can climb into the largest car and he likes it. Also, mother bear can climb into the middle car and she likes it. Moreover, son bear can climb into the smallest car and he likes it. It's known that the largest car is strictly larger than the middle car, and the middle car is strictly larger than the smallest car.

Masha came to test these cars. She could climb into all cars, but she liked only the smallest car.

It's known that a character with size $ a $ can climb into some car with size $ b $ if and only if $ a<=b $ , he or she likes it if and only if he can climb into this car and $ 2a>=b $ .

You are given sizes of bears and Masha. Find out some possible integer non-negative sizes of cars.

## 输入格式

You are given four integers $ V_{1} $ , $ V_{2} $ , $ V_{3} $ , $ V_{m} $ ( $ 1<=V_{i}<=100 $ ) — sizes of father bear, mother bear, son bear and Masha, respectively. It's guaranteed that $ V_{1}>V_{2}>V_{3} $ .

## 输出格式

Output three integers — sizes of father bear's car, mother bear's car and son bear's car, respectively.

If there are multiple possible solutions, print any.

If there is no solution, print "-1" (without quotes).

## 说明/提示

In first test case all conditions for cars' sizes are satisfied.

In second test case there is no answer, because Masha should be able to climb into smallest car (so size of smallest car in not less than 21), but son bear should like it, so maximum possible size of it is 20.

## 样例 #1

### 输入

```
50 30 10 10

```

### 输出

```
50
30
10

```

## 样例 #2

### 输入

```
100 50 10 21

```

### 输出

```
-1

```

