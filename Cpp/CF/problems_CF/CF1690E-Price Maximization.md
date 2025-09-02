---
title: "Price Maximization"
layout: "post"
diff: 普及/提高-
pid: CF1690E
tag: []
---

# Price Maximization

## 题目描述

A batch of $ n $ goods ( $ n $ — an even number) is brought to the store, $ i $ -th of which has weight $ a_i $ . Before selling the goods, they must be packed into packages. After packing, the following will be done:

- There will be $ \frac{n}{2} $ packages, each package contains exactly two goods;
- The weight of the package that contains goods with indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ) is $ a_i + a_j $ .

With this, the cost of a package of weight $ x $ is always $ \left \lfloor\frac{x}{k}\right\rfloor $ burles (rounded down), where $ k $ — a fixed and given value.

Pack the goods to the packages so that the revenue from their sale is maximized. In other words, make such $ \frac{n}{2} $ pairs of given goods that the sum of the values $ \left \lfloor\frac{x_i}{k} \right \rfloor $ , where $ x_i $ is the weight of the package number $ i $ ( $ 1 \le i \le \frac{n}{2} $ ), is maximal.

For example, let $ n = 6, k = 3 $ , weights of goods $ a = [3, 2, 7, 1, 4, 8] $ . Let's pack them into the following packages.

- In the first package we will put the third and sixth goods. Its weight will be $ a_3 + a_6 = 7 + 8 = 15 $ . The cost of the package will be $ \left \lfloor\frac{15}{3}\right\rfloor = 5 $ burles.
- In the second package put the first and fifth goods, the weight is $ a_1 + a_5 = 3 + 4 = 7 $ . The cost of the package is $ \left \lfloor\frac{7}{3}\right\rfloor = 2 $ burles.
- In the third package put the second and fourth goods, the weight is $ a_2 + a_4 = 2 + 1 = 3 $ . The cost of the package is $ \left \lfloor\frac{3}{3}\right\rfloor = 1 $ burle.

With this packing, the total cost of all packs would be $ 5 + 2 + 1 = 8 $ burles.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases in the test.

The descriptions of the test cases follow.

The first line of each test case contains two integers $ n $ ( $ 2 \le n \le 2\cdot10^5 $ ) and $ k $ ( $ 1 \le k \le 1000 $ ). The number $ n $ — is even.

The second line of each test case contains exactly $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all the test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, print on a separate line a single number — the maximum possible total cost of all the packages.

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, you can get a total value equal to $ 4 $ if you put the first and second goods in the first package and the third and fourth goods in the second package.

In the third test case, the cost of each item is $ 0 $ , so the total cost will also be $ 0 $ .

## 样例 #1

### 输入

```
6
6 3
3 2 7 1 4 8
4 3
2 1 5 6
4 12
0 0 0 0
2 1
1 1
6 10
2 0 0 5 9 4
6 5
5 3 8 6 3 2
```

### 输出

```
8
4
0
2
1
5
```

