---
title: "Club of Young Aircraft Builders (hard version)"
layout: "post"
diff: 难度0
pid: CF2066D2
tag: []
---

# Club of Young Aircraft Builders (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, not necessary $ a_i = 0 $ . You can hack only if you solved all versions of this problem.

There is a building with $ n $ floors, numbered from $ 1 $ to $ n $ from bottom to top. There is exactly one person living on each floor.

All the residents of the building have an important goal today: to launch at least $ c $ paper airplanes collectively. The residents will launch the airplanes in turn. When a person from the $ i $ -th floor launches an airplane, all residents on floors from $ 1 $ to $ i $ can see it as it descends to the ground. If, from the perspective of the resident on the $ i $ -th floor, at least $ c $ airplanes have already been launched, they will no longer launch airplanes themselves. It is also known that by the end of the day, from the perspective of each resident in the building, at least $ c $ airplanes have been launched, and a total of $ m $ airplanes were thrown.

You have been carefully monitoring this flash mob, and for each airplane, you recorded which resident from which floor threw it. Unfortunately, the information about who exactly threw some of the airplanes has been lost. Find the number of ways to fill in the gaps so that the information could be credible. Since the answer could be quite large, output it modulo $ 10^9 + 7 $ .

It is also possible that you made a mistake in your records, and there is no possible way to restore the gaps. In that case, the answer is considered to be $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n, c, m $ ( $ 1 \le n \le 100 $ , $ 1 \le c \le 100 $ , $ c \le m \le n \cdot c $ ) — the number of floors in the building, the minimum required number of airplanes, and the number of airplanes actually launched.

The second line of each test case contains $ m $ integers $ a_1, a_2, \ldots, a_m $ ( $ 0 \le a_i \le n $ ) — $ a_i $ indicates the resident from which floor launched the $ i $ -th airplane; $ a_i = 0 $ indicates a gap.

It is guaranteed that the sum of the values of $ m $ across all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, output the number of ways to fill in the gaps with numbers from $ 1 $ to $ n $ , so that the chronology of the airplane launches could be credible, modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test example, all six possible ways to fill in the gaps are as follows:

1. $ [1, 1, 3, 3] $
2. $ [1, 2, 3, 3] $
3. $ [1, 3, 2, 3] $
4. $ [2, 1, 3, 3] $
5. $ [2, 2, 3, 3] $
6. $ [3, 1, 2, 3] $

Note that the array $ [2, 3, 1, 3] $ is not a valid way to fill in the gaps, as the third airplane could not have been launched by the person on the $ 1 $ st floor, since from their perspective, $ c = 2 $ airplanes had already been launched.

Also, the array $ [1, 1, 2, 3] $ is not a valid way to fill in the gaps, as from the perspective of the person on the $ 3 $ rd floor, only $ 1 $ airplane has been launched, while $ c = 2 $ .

## 样例 #1

### 输入

```
8
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0
6 1 3
2 0 0
2 3 5
0 0 1 0 2
3 3 4
3 3 3 0
2 1 2
0 1
2 1 2
0 2
5 3 12
0 0 1 0 2 4 0 0 0 5 0 5
```

### 输出

```
6
190
3
2
0
0
1
14
```

