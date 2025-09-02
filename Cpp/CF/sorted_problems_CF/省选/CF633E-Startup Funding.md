---
title: "Startup Funding"
layout: "post"
diff: 省选/NOI-
pid: CF633E
tag: []
---

# Startup Funding

## 题目描述

An e-commerce startup pitches to the investors to get funding. They have been functional for $ n $ weeks now and also have a website!

For each week they know the number of unique visitors during this week $ v_{i} $ and the revenue $ c_{i} $ . To evaluate the potential of the startup at some range of weeks from $ l $ to $ r $ inclusive investors use the minimum among the maximum number of visitors multiplied by $ 100 $ and the minimum revenue during this period, that is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633E/d4c95097082aa3764e2e11310a38092f1681fe02.png)The truth is that investors have no idea how to efficiently evaluate the startup, so they are going to pick some $ k $ random distinct weeks $ l_{i} $ and give them to managers of the startup. For each $ l_{i} $ they should pick some $ r_{i}>=l_{i} $ and report maximum number of visitors and minimum revenue during this period.

Then, investors will calculate the potential of the startup for each of these ranges and take minimum value of $ p(l_{i},r_{i}) $ as the total evaluation grade of the startup. Assuming that managers of the startup always report the optimal values of $ r_{i} $ for some particular $ l_{i} $ , i.e., the value such that the resulting grade of the startup is maximized, what is the expected resulting grade of the startup?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=1000000 $ ).

The second line contains $ n $ integers $ v_{i} $ ( $ 1<=v_{i}<=10^{7} $ ) — the number of unique visitors during each week.

The third line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=10^{7} $ ) —the revenue for each week.

## 输出格式

Print a single real value — the expected grade of the startup. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633E/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

Consider the first sample.

If the investors ask for $ l_{i}=1 $ onwards, startup will choose $ r_{i}=1 $ , such that max number of visitors is $ 3 $ and minimum revenue is $ 300 $ . Thus, potential in this case is $ min(3·100,300)=300 $ .

If the investors ask for $ l_{i}=2 $ onwards, startup will choose $ r_{i}=3 $ , such that max number of visitors is $ 2 $ and minimum revenue is $ 200 $ . Thus, potential in this case is $ min(2·100,200)=200 $ .

If the investors ask for $ l_{i}=3 $ onwards, startup will choose $ r_{i}=3 $ , such that max number of visitors is $ 1 $ and minimum revenue is $ 300 $ . Thus, potential in this case is $ min(1·100,300)=100 $ .

We have to choose a set of size $ 2 $ equi-probably and take minimum of each. The possible sets here are : $ {200,300} $ , $ {100,300} $ , $ {100,200} $ , effectively the set of possible values as perceived by investors equi-probably: $ {200,100,100} $ . Thus, the expected value is $ (100+200+100)/3=133.(3) $ .

## 样例 #1

### 输入

```
3 2
3 2 1
300 200 300

```

### 输出

```
133.3333333

```

