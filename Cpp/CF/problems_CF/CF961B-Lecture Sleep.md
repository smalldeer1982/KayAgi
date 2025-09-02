---
title: "Lecture Sleep"
layout: "post"
diff: 普及-
pid: CF961B
tag: []
---

# Lecture Sleep

## 题目描述

Your friend Mishka and you attend a calculus lecture. Lecture lasts $ n $ minutes. Lecturer tells $ a_{i} $ theorems during the $ i $ -th minute.

Mishka is really interested in calculus, though it is so hard to stay awake for all the time of lecture. You are given an array $ t $ of Mishka's behavior. If Mishka is asleep during the $ i $ -th minute of the lecture then $ t_{i} $ will be equal to $ 0 $ , otherwise it will be equal to $ 1 $ . When Mishka is awake he writes down all the theorems he is being told — $ a_{i} $ during the $ i $ -th minute. Otherwise he writes nothing.

You know some secret technique to keep Mishka awake for $ k $ minutes straight. However you can use it only once. You can start using it at the beginning of any minute between $ 1 $ and $ n-k+1 $ . If you use it on some minute $ i $ then Mishka will be awake during minutes $ j $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961B/74a70105e36a7144196883409708a1b859a35796.png) and will write down all the theorems lecturer tells.

You task is to calculate the maximum number of theorems Mishka will be able to write down if you use your technique only once to wake him up.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ k $ ( $ 1<=k<=n<=10^{5} $ ) — the duration of the lecture in minutes and the number of minutes you can keep Mishka awake.

The second line of the input contains $ n $ integer numbers $ a_{1},a_{2},...\ a_{n} $ ( $ 1<=a_{i}<=10^{4} $ ) — the number of theorems lecturer tells during the $ i $ -th minute.

The third line of the input contains $ n $ integer numbers $ t_{1},t_{2},...\ t_{n} $ ( $ 0<=t_{i}<=1 $ ) — type of Mishka's behavior at the $ i $ -th minute of the lecture.

## 输出格式

Print only one integer — the maximum number of theorems Mishka will be able to write down if you use your technique only once to wake him up.

## 说明/提示

In the sample case the better way is to use the secret technique at the beginning of the third minute. Then the number of theorems Mishka will be able to write down will be equal to $ 16 $ .

## 样例 #1

### 输入

```
6 3
1 3 5 2 5 4
1 1 0 1 0 0

```

### 输出

```
16

```

