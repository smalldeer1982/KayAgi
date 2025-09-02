---
title: "Vanya and Computer Game"
layout: "post"
diff: 提高+/省选-
pid: CF492D
tag: []
---

# Vanya and Computer Game

## 题目描述

Vanya and his friend Vova play a computer game where they need to destroy $ n $ monsters to pass a level. Vanya's character performs attack with frequency $ x $ hits per second and Vova's character performs attack with frequency $ y $ hits per second. Each character spends fixed time to raise a weapon and then he hits (the time to raise the weapon is $ 1/x $ seconds for the first character and $ 1/y $ seconds for the second one). The $ i $ -th monster dies after he receives $ a_{i} $ hits.

Vanya and Vova wonder who makes the last hit on each monster. If Vanya and Vova make the last hit at the same time, we assume that both of them have made the last hit.

## 输入格式

Vanya and his friend Vova play a computer game where they need to destroy $ n $ monsters to pass a level. Vanya's character performs attack with frequency $ x $ hits per second and Vova's character performs attack with frequency $ y $ hits per second. Each character spends fixed time to raise a weapon and then he hits (the time to raise the weapon is $ 1/x $ seconds for the first character and $ 1/y $ seconds for the second one). The $ i $ -th monster dies after he receives $ a_{i} $ hits.

Vanya and Vova wonder who makes the last hit on each monster. If Vanya and Vova make the last hit at the same time, we assume that both of them have made the last hit.

## 输出格式

Print $ n $ lines. In the $ i $ -th line print word "Vanya", if the last hit on the $ i $ -th monster was performed by Vanya, "Vova", if Vova performed the last hit, or "Both", if both boys performed it at the same time.

## 说明/提示

In the first sample Vanya makes the first hit at time $ 1/3 $ , Vova makes the second hit at time $ 1/2 $ , Vanya makes the third hit at time $ 2/3 $ , and both boys make the fourth and fifth hit simultaneously at the time $ 1 $ .

In the second sample Vanya and Vova make the first and second hit simultaneously at time $ 1 $ .

## 样例 #1

### 输入

```
4 3 2
1
2
3
4

```

### 输出

```
Vanya
Vova
Vanya
Both

```

## 样例 #2

### 输入

```
2 1 1
1
2

```

### 输出

```
Both
Both

```

