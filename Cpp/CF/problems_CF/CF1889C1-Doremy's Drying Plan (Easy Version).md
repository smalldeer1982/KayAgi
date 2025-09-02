---
title: "Doremy's Drying Plan (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1889C1
tag: []
---

# Doremy's Drying Plan (Easy Version)

## 题目描述

The only differences between the two versions of this problem are the constraint on $ k $ , the time limit and the memory limit. You can make hacks only if all versions of the problem are solved.

Doremy lives in a rainy country consisting of $ n $ cities numbered from $ 1 $ to $ n $ .

The weather broadcast predicted the distribution of rain in the next $ m $ days. In the $ i $ -th day, it will rain in the cities in the interval $ [l_i, r_i] $ . A city is called dry if it will never rain in that city in the next $ m $ days.

It turns out that Doremy has a special power. She can choose $ k $ days (in the easy version, $ k = 2 $ ), and during these days it will not rain. Doremy wants to calculate the maximum number of dry cities after using the special power.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1\le n\le 2\cdot 10^5 $ , $ 2 \le m \le 2\cdot 10^5 $ , $ k = 2 $ ) — the number of cities, the number of days, and the number of days of rain that Doremy can prevent.

Then, $ m $ lines follow. The $ i $ -th line contains two integers $ l_i $ , $ r_i $ ( $ 1\le l_i\le r_i\le n $ ) — the rain coverage on day $ i $ .

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the maximum number of dry cities.

## 说明/提示

In the first test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 2 $ will be dry;
- rain $ 2,3 $ , then no city will be dry;
- rain $ 1,3 $ , then no city will be dry;

So there is at most $ 1 $ dry city.

In the second test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 1,2 $ will be dry;
- rain $ 2,3 $ , then city $ 4,5 $ will be dry;
- rain $ 1,3 $ , then city $ 1,5 $ will be dry.

So there are at most $ 2 $ dry cities.

In the third test case, it is optimal to prevent rain $ 2,5 $ .

In the forth test case, there is always $ 4 $ days of rain that wets all the cities and cannot be prevented.

## 样例 #1

### 输入

```
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 2
1 5
6 10
2 2
3 7
5 8
1 4
100 6 2
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 2
9 20
3 3
10 11
11 13
6 18
```

### 输出

```
1
2
3
0
1000
15
```

