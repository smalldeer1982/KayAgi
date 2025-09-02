---
title: "Gabriel and Caterpillar"
layout: "post"
diff: 普及/提高-
pid: CF652A
tag: []
---

# Gabriel and Caterpillar

## 题目描述

The $ 9 $ -th grade student Gabriel noticed a caterpillar on a tree when walking around in a forest after the classes. The caterpillar was on the height $ h_{1} $ cm from the ground. On the height $ h_{2} $ cm ( $ h_{2}&gt;h_{1} $ ) on the same tree hung an apple and the caterpillar was crawling to the apple.

Gabriel is interested when the caterpillar gets the apple. He noted that the caterpillar goes up by $ a $ cm per hour by day and slips down by $ b $ cm per hour by night.

In how many days Gabriel should return to the forest to see the caterpillar get the apple. You can consider that the day starts at $ 10 $ am and finishes at $ 10 $ pm. Gabriel's classes finish at $ 2 $ pm. You can consider that Gabriel noticed the caterpillar just after the classes at $ 2 $ pm.

Note that the forest is magic so the caterpillar can slip down under the ground and then lift to the apple.

## 输入格式

The first line contains two integers $ h_{1},h_{2} $ ( $ 1<=h_{1}&lt;h_{2}<=10^{5} $ ) — the heights of the position of the caterpillar and the apple in centimeters.

The second line contains two integers $ a,b $ ( $ 1<=a,b<=10^{5} $ ) — the distance the caterpillar goes up by day and slips down by night, in centimeters per hour.

## 输出格式

Print the only integer $ k $ — the number of days Gabriel should wait to return to the forest and see the caterpillar getting the apple.

If the caterpillar can't get the apple print the only integer $ -1 $ .

## 说明/提示

In the first example at $ 10 $ pm of the first day the caterpillar gets the height $ 26 $ . At $ 10 $ am of the next day it slips down to the height $ 14 $ . And finally at $ 6 $ pm of the same day the caterpillar gets the apple.

Note that in the last example the caterpillar was slipping down under the ground and getting the apple on the next day.

## 样例 #1

### 输入

```
10 30
2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 13
1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
10 19
1 2

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
1 50
5 4

```

### 输出

```
1

```

