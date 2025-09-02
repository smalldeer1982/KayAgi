---
title: "Trails (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970E2
tag: ['动态规划 DP', '矩阵加速']
---

# Trails (Medium)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains the integers $ m $ and $ n $ .

The second line contains $ m $ integers, $ s_1, \dots, s_m $ , where $ s_i $ is the number of short trails between cabin $ i $ and Lake Geneva.

The third and last line contains $ m $ integers, $ l_1, \dots, l_m $ , where $ l_i $ is the number of long trails between cabin $ i $ and Lake Geneva.

We have the following constraints:

 $ 0 \le s_i, l_i \le 10^3 $ .

 $ 1 \le m \le 10^2 $ .

 $ 1 \le n \le 10^9 $ .

## 输出格式

The number of possible combinations of trails, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1
```

### 输出

```
18
```



---

