---
title: "Conference"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1965F
tag: []
---

# Conference

## 题目描述

You have been asked to organize a very important art conference. The first step is to choose the dates.

The conference must last for a certain number of consecutive days. Each day, one lecturer must perform, and the same lecturer cannot perform more than once.

You asked $ n $ potential lecturers if they could participate in the conference. Lecturer $ i $ indicated that they could perform on any day from $ l_i $ to $ r_i $ inclusive.

A certain segment of days can be chosen as the conference dates if there is a way to assign an available lecturer to each day of the segment, assigning each lecturer to no more than one day.

For each $ k $ from $ 1 $ to $ n $ , find how many ways there are to choose a segment of $ k $ consecutive days as the conference dates.

## 输入格式

The first line of input contains one integer $ n $ — the number of potential lecturers ( $ 1 \le n \le 2 \cdot 10^5 $ ).

Each of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ — the segment of available days for the $ i $ th lecturer ( $ 1 \le l_i \le r_i \le 2 \cdot 10^5 $ ).

## 输出格式

Print $ n $ integers, where the $ k $ th number denotes the number of ways to select a segment of $ k $ consecutive days as conference dates.

## 说明/提示

In the first testcase, a one-day conference can be organized on any of the days from $ 1 $ to $ 6 $ . A two-day conference can be organized from day $ 2 $ to day $ 3 $ , as well as from day $ 4 $ to day $ 5 $ .

In the second testcase, five lecturers can perform only from day $ 1 $ to day $ 3 $ , so it will not be possible to organize a conference longer than three days.

## 样例 #1

### 输入

```
3
1 2
3 4
5 6
```

### 输出

```
6
2
0
```

## 样例 #2

### 输入

```
5
1 3
1 3
1 3
1 3
1 3
```

### 输出

```
3
2
1
0
0
```

