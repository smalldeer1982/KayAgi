---
title: "Two Avenues"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1648F
tag: []
---

# Two Avenues

## 题目描述

In order to make the capital of Berland a more attractive place for tourists, the great king came up with the following plan: choose two streets of the city and call them avenues. Certainly, these avenues will be proclaimed extremely important historical places, which should attract tourists from all over the world.

The capital of Berland can be represented as a graph, the vertices of which are crossroads, and the edges are streets connecting two crossroads. In total, there are $ n $ vertices and $ m $ edges in the graph, you can move in both directions along any street, you can get from any crossroad to any other by moving only along the streets, each street connects two different crossroads, and no two streets connect the same pair of crossroads.

In order to reduce the flow of ordinary citizens moving along the great avenues, it was decided to introduce a toll on each avenue in both directions. Now you need to pay $ 1 $ tugrik for one passage along the avenue. You don't have to pay for the rest of the streets.

Analysts have collected a sample of $ k $ citizens, $ i $ -th of them needs to go to work from the crossroad $ a_i $ to the crossroad $ b_i $ . After two avenues are chosen, each citizen will go to work along the path with minimal cost.

In order to earn as much money as possible, it was decided to choose two streets as two avenues, so that the total number of tugriks paid by these $ k $ citizens is maximized. Help the king: according to the given scheme of the city and a sample of citizens, find out which two streets should be made avenues, and how many tugriks the citizens will pay according to this choice.

## 输入格式

Each test consists of multiple test cases. The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3 \leq n \leq 500\,000 $ , $ n - 1 \leq m \leq 500\,000 $ , $ m \le \frac{n (n - 1)}{2} $ ) — the number of crossroads and streets, respectively.

The next $ m $ lines contain the description of streets, $ i $ -th line contains two integers $ s_i $ and $ f_i $ ( $ 1 \leq s_i, f_i \leq n $ , $ s_i \neq f_i $ ) — indexes of crossroads which are connected by $ i $ -th street. It is guaranteed that no two streets connect the same pair of crossroads, you can get from any crossroad to any other by moving only along the streets.

The next line contains a single integer $ k $ ( $ 1 \leq k \leq 500\,000 $ ) — the amount of citizens in the sample.

The next $ k $ lines contain the description of citizens, $ i $ -th line contains two integers $ a_i $ and $ b_i $ ( $ 1 \leq a_i, b_i \leq n $ , $ a_i \neq b_i $ ) — $ i $ -th citizen goes to work from crossroad $ a_i $ to crossroad $ b_i $ .

Let $ M $ be the sum of $ m $ over all test cases and $ K $ be the sum of $ k $ over all test cases. It is guaranteed that $ M, K \le 500\,000 $ .

## 输出格式

For each test case print the answer to the problem.

In the first line print the total amount of tugriks that will be paid by citizens.

In the second line print two integers $ x_1 $ and $ y_1 $ — the numbers of crossroads that will be connected by the first avenue.

In the third line print two integers $ x_2 $ and $ y_2 $ — the numbers of crossroads that will be connected by the second avenue.

The numbers of crossroads connected by an avenue can be printed in any order, each of the printed streets should be among $ m $ streets of the city, chosen streets should be different.

## 样例 #1

### 输入

```
3
6 5
1 2
2 3
2 4
4 5
4 6
3
1 6
5 3
2 5
5 5
1 2
2 3
3 4
4 5
5 1
6
1 5
1 3
1 3
2 4
2 5
5 3
8 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
7 1
1 8
3 6
4
2 5
3 7
2 5
7 8
```

### 输出

```
5
4 2
5 4
5
1 5
3 2
3
7 6
2 3
```

