---
title: "Trees and XOR Queries Again"
layout: "post"
diff: 省选/NOI-
pid: CF1902F
tag: []
---

# Trees and XOR Queries Again

## 题目描述

You are given a tree consisting of $ n $ vertices. There is an integer written on each vertex; the $ i $ -th vertex has integer $ a_i $ written on it.

You have to process $ q $ queries. The $ i $ -th query consists of three integers $ x_i $ , $ y_i $ and $ k_i $ . For this query, you have to answer if it is possible to choose a set of vertices $ v_1, v_2, \dots, v_m $ (possibly empty) such that:

- every vertex $ v_j $ is on the simple path between $ x_i $ and $ y_i $ (endpoints can be used as well);
- $ a_{v_1} \oplus a_{v_2} \oplus \dots \oplus a_{v_m} = k_i $ , where $ \oplus $ denotes the bitwise XOR operator.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{20} - 1 $ ).

Then $ n-1 $ lines follow. Each of them contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ ; $ u \ne v $ ) denoting an edge of the tree.

The next line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of queries.

Then $ q $ lines follow. The $ i $ -th of them contains three integers $ x_i $ , $ y_i $ and $ k_i $ ( $ 1 \le x_i, y_i \le n $ ; $ 0 \le k_i \le 2^{20} - 1 $ ).

## 输出格式

For each query, print YES if it is possible to form a set of vertices meeting the constraints. Otherwise, print NO.

You can print each letter in any case.

## 样例 #1

### 输入

```
4
0 1 2 10
2 1
3 2
4 2
8
3 3 0
3 4 1
3 4 7
1 3 1
1 3 2
1 3 10
1 4 10
1 4 11
```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
YES
```

