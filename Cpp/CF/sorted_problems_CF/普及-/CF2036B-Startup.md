---
title: "Startup"
layout: "post"
diff: 普及-
pid: CF2036B
tag: []
---

# Startup

## 题目描述

Arseniy came up with another business plan — to sell soda from a vending machine! For this, he purchased a machine with $ n $ shelves, as well as $ k $ bottles, where the $ i $ -th bottle is characterized by the brand index $ b_i $ and the cost $ c_i $ .

You can place any number of bottles on each shelf, but all bottles on the same shelf must be of the same brand.

Arseniy knows that all the bottles he puts on the shelves of the machine will be sold. Therefore, he asked you to calculate the maximum amount he can earn.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 2 \cdot 10^5 $ ), where $ n $ is the number of shelves in the machine, and $ k $ is the number of bottles available to Arseniy.

The next $ k $ lines contain two integers $ b_i $ and $ c_i $ ( $ 1 \le b_i \le k, 1 \le c_i \le 1000 $ ) — the brand and cost of the $ i $ -th bottle.

It is also guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ and that the sum of $ k $ across all test cases also does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the maximum amount that Arseniy can earn.

## 说明/提示

In the first test case, Arseniy has $ 3 $ shelves in the vending machine. He can place, for example, two bottles of the brand $ 2 $ on the first shelf and a bottle of the brand $ 1 $ on the second shelf. Then the total cost of the bottles would be $ 6 + 7 + 15 = 28 $ .

In the second test case, he has only one shelf. It is not difficult to show that the optimal option is to place a bottle of the brand $ 1 $ on it. Then the total cost will be $ 15 $ .

In the third test case, he has as many as $ 6 $ shelves, so he can place all available bottles with a total cost of $ 7 + 5 = 12 $ .

## 样例 #1

### 输入

```
4
3 3
2 6
2 7
1 15
1 3
2 6
2 7
1 15
6 2
1 7
2 5
190000 1
1 1000
```

### 输出

```
28
15
12
1000
```

