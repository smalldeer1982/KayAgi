---
title: "Cutlet"
layout: "post"
diff: 提高+/省选-
pid: CF939F
tag: ['单调队列', '枚举', '队列']
---

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100000 $ , $ 1<=k<=100 $ ) — the number of seconds the cutlet should be cooked on each side and number of periods of time in which Arkady can flip it.

The next $ k $ lines contain descriptions of these intervals. Each line contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=2·n $ ), meaning that Arkady can flip the cutlet in any moment starting from $ l_{i} $ seconds after the beginning of cooking and finishing at $ r_{i} $ seconds after beginning of cooking. In particular, if $ l_{i}=r_{i} $ then Arkady can flip the cutlet only in the moment $ l_{i}=r_{i} $ . It's guaranteed that $ l_{i}>r_{i-1} $ for all $ 2<=i<=k $ .

## 输出格式

Output "Hungry" if Arkady won't be able to fry the cutlet for exactly $ n $ seconds on one side and exactly $ n $ seconds on the other side.

Otherwise, output "Full" in the first line, and the minimum number of times he should flip the cutlet in the second line.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13

```

### 输出

```
Full
2

```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13

```

### 输出

```
Full
1

```

## 样例 #3

### 输入

```
20 1
3 19

```

### 输出

```
Hungry

```

