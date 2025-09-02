---
title: "Definitely a Geometry Problem"
layout: "post"
diff: 难度0
pid: CF2095G
tag: []
---

# Definitely a Geometry Problem

## 题目描述

Megumin is a wizard who can cast powerful magic spells that affect large areas. She is obsessed with the extremely devastating Explosion spell that can destroy everything around its target.

There are currently $ n $ slimes in the wild. Each slime's location can be described in 2D Cartesian coordinates. Megumin wishes to kill at least $ k $ slimes so she can earn more experience points to level up her Explosion. To do that, she can choose any circle on the plane and cast an Explosion spell which kills every slime inside or on the border of the circle.

However, the Explosion magic requires a large amount of mana to cast, and Megumin can only use it once per day. The amount of mana used is equal to the area inside the circle she chooses. What is the minimum amount of mana she needs to spend to kill $ k $ slimes with a single Explosion?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^5 $ ) — the number of slimes and how many slimes Megumin needs to defeat.

Each of the next $ n $ lines contains two integers $ x $ and $ y $ ( $ -10^9 \le x, y \le 10^9 $ ), denoting the coordinates $ (x, y) $ of a slime's location. It is guaranteed that all locations are distinct and that no three slimes lie on the same circle.

## 输出格式

Print one real number — the answer.

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a-b|}{\max(1,|b|)} \le 10^{-6} $ .

## 说明/提示

In the first example, Megumin can hit the slime with a circle centered at $ (0, 0) $ with radius $ 0 $ .

In the second example, Megumin can hit the first and last slimes with a circle centered at $ (1, 0) $ with radius $ 1 $ .

## 样例 #1

### 输入

```
1 1
0 0
```

### 输出

```
0.000000000000000
```

## 样例 #2

### 输入

```
3 2
0 0
100 0
2 0
```

### 输出

```
3.141592653589793
```

