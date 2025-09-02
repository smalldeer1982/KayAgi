---
title: "Vlad and the Mountains"
layout: "post"
diff: 提高+/省选-
pid: CF1851G
tag: []
---

# Vlad and the Mountains

## 题目描述

Vlad decided to go on a trip to the mountains. He plans to move between $ n $ mountains, some of which are connected by roads. The $ i $ -th mountain has a height of $ h_i $ .

If there is a road between mountains $ i $ and $ j $ , Vlad can move from mountain $ i $ to mountain $ j $ by spending $ h_j - h_i $ units of energy. If his energy drops below zero during the transition, he will not be able to move from mountain $ i $ to mountain $ j $ . Note that $ h_j - h_i $ can be negative and then the energy will be restored.

Vlad wants to consider different route options, so he asks you to answer the following queries: is it possible to construct some route starting at mountain $ a $ and ending at mountain $ b $ , given that he initially has $ e $ units of energy?

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains two numbers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le \min(\frac{n\cdot(n - 1)}{2}, 2 \cdot 10^5) $ ) — the number of mountains and the number of roads between them, respectively.

The second line contains $ n $ integers $ h_1, h_2, h_3, \dots, h_n $ ( $ 1 \le h_i \le 10^9 $ ) — the heights of the mountains.

The next $ m $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \ne v $ ) — the numbers of the mountains connected by a road. It is guaranteed that no road appears twice.

The next line contains an integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of queries.

The following $ q $ lines contain three numbers $ a $ , $ b $ , and $ e $ ( $ 1 \le a, b \le n $ , $ 0 \le e \le 10^9 $ ) — the initial and final mountains of the route, and the amount of energy, respectively.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . The same guarantee applies to $ m $ and $ q $ .

## 输出格式

For each query, output "YES" if Vlad can construct a route from mountain $ a $ to mountain $ b $ , and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

In the examples below, the answers for different test cases are separated by an empty line, which you do not need to output.

## 样例 #1

### 输入

```
2
7 7
1 5 3 4 2 4 1
1 4
4 3
3 6
3 2
2 5
5 6
5 7
5
1 1 3
6 2 0
4 7 0
1 7 4
1 7 2
6 5
4 7 6 2 5 1
1 3
5 3
1 5
2 4
6 2
5
1 5 1
1 3 1
1 2 1000
6 2 6
6 2 5
```

### 输出

```
YES
NO
YES
YES
NO

YES
NO
NO
YES
NO
```

## 样例 #2

### 输入

```
2
3 2
1 3 9
1 2
2 3
5
1 1 1
3 2 2
1 1 2
3 3 0
1 2 1
3 3
1 4 1
1 2
2 3
1 3
5
3 3 9
1 3 6
1 1 2
3 3 6
3 3 4
```

### 输出

```
YES
YES
YES
YES
NO

YES
YES
YES
YES
YES
```

## 样例 #3

### 输入

```
1
6 10
7 9 2 10 8 6
4 2
6 1
4 5
3 5
6 4
1 3
2 6
6 5
1 2
3 6
5
4 4 8
3 3 1
5 5 9
2 1 7
6 6 10
```

### 输出

```
YES
YES
YES
YES
YES
```

