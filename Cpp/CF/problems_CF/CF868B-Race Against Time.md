---
title: "Race Against Time"
layout: "post"
diff: 普及-
pid: CF868B
tag: []
---

# Race Against Time

## 题目描述

Have you ever tried to explain to the coordinator, why it is eight hours to the contest and not a single problem has been prepared yet? Misha had. And this time he has a really strong excuse: he faced a space-time paradox! Space and time replaced each other.

The entire universe turned into an enormous clock face with three hands — hour, minute, and second. Time froze, and clocks now show the time $ h $ hours, $ m $ minutes, $ s $ seconds.

Last time Misha talked with the coordinator at $ t_{1} $ o'clock, so now he stands on the number $ t_{1} $ on the clock face. The contest should be ready by $ t_{2} $ o'clock. In the terms of paradox it means that Misha has to go to number $ t_{2} $ somehow. Note that he doesn't have to move forward only: in these circumstances time has no direction.

Clock hands are very long, and Misha cannot get round them. He also cannot step over as it leads to the collapse of space-time. That is, if hour clock points 12 and Misha stands at 11 then he cannot move to 1 along the top arc. He has to follow all the way round the clock center (of course, if there are no other hands on his way).

Given the hands' positions, $ t_{1} $ , and $ t_{2} $ , find if Misha can prepare the contest on time (or should we say on space?). That is, find if he can move from $ t_{1} $ to $ t_{2} $ by the clock face.

## 输入格式

Five integers $ h $ , $ m $ , $ s $ , $ t_{1} $ , $ t_{2} $ ( $ 1<=h<=12 $ , $ 0<=m,s<=59 $ , $ 1<=t_{1},t_{2}<=12 $ , $ t_{1}≠t_{2} $ ).

Misha's position and the target time do not coincide with the position of any hand.

## 输出格式

Print "YES" (quotes for clarity), if Misha can prepare the contest on time, and "NO" otherwise.

You can print each character either upper- or lowercase ("YeS" and "yes" are valid when the answer is "YES").

## 说明/提示

The three examples are shown on the pictures below from left to right. The starting position of Misha is shown with green, the ending position is shown with pink. Note that the positions of the hands on the pictures are not exact, but are close to the exact and the answer is the same.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF868B/a67db32a4530841b7d57b21ea225d21a83f385f3.png)

## 样例 #1

### 输入

```
12 30 45 3 11

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
12 0 1 12 1

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
3 47 0 4 9

```

### 输出

```
YES

```

