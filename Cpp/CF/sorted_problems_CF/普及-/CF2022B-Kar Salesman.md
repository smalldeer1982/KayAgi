---
title: "Kar Salesman"
layout: "post"
diff: 普及-
pid: CF2022B
tag: ['数学', '贪心']
---

# Kar Salesman

## 题目描述

Karel is a salesman in a car dealership. The dealership has $ n $ different models of cars. There are $ a_i $ cars of the $ i $ -th model. Karel is an excellent salesperson and can convince customers to buy up to $ x $ cars (of Karel's choice), as long as the cars are from different models.

Determine the minimum number of customers Karel has to bring in to sell all the cars.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 5 \cdot 10^5 $ ; $ 1 \le x \le 10 $ ) — the number of different models of cars and the maximum number of cars Karel can convince a customer to buy.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the number of cars of each model.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output the minimum possible number of customers needed to sell all the cars.

## 说明/提示

For the first case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 2 $ cars with model $ 1 $ and $ 2 $ .
- Customer $ 3 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .

For the second case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 3 $ cars with model $ 1 $ , $ 2 $ and $ 3 $ .
- Customer $ 3 $ buys $ 1 $ car with model $ 3 $ .

## 样例 #1

### 输入

```
4
3 2
3 1 2
3 3
2 1 3
5 3
2 2 1 9 2
7 4
2 5 3 3 5 2 5
```

### 输出

```
3
3
9
7
```

