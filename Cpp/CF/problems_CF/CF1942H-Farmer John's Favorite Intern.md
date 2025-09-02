---
title: "Farmer John's Favorite Intern"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1942H
tag: []
---

# Farmer John's Favorite Intern

## 题目描述

[Peaches...](https://soundcloud.com/jackblack-sc/peaches)

⠀



Ruby just won an internship position at Farmer John's farm by winning a coding competition! As the newly recruited intern, Ruby is tasked with maintaining Farmer John's peach tree, a tree consisting of $ n $ nodes rooted at node $ 1 $ . Each node initially contains $ a_i = 0 $ peaches, and there are two types of events that can happen:

1. Growth event at some node $ x $ : Ruby must choose either the parent of $ x $ or any node in the subtree of $ x $ and increase the amount of peaches it contains by one.
2. Harvest event at some node $ x $ : Ruby must choose a single node that is in the subtree of $ x $ and decrease the amount of peaches it contains by one. Note that this is not the same set of nodes as the growth event.

 Note that the subtree of $ x $ includes the node $ x $ as well.Ruby is also given an array $ b $ of length $ n $ . The peach tree is deemed healthy if $ a_i \ge b_i $ for every node $ i $ .

Ruby is asked to perform $ q $ operations of two types:

- 1 x v — Perform $ v $ growth events on node $ x $ . Ruby does not have to choose the same node to increase in every growth event.
- 2 x v — Perform $ v $ harvest events on node $ x $ . Ruby does not have to choose the same node to decrease in every harvest event.

For every prefix of operations, Ruby asks you to find if she can perform these operations in some order such that the resulting peach tree (at the end of these operations) is healthy. Note that Ruby can't perform a harvest event that makes any $ a_i $ negative.

Every prefix is independent, meaning that for a given operation, Ruby may choose different nodes to perform events on for every prefix that contains that operation.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the size of the tree and the number of operations.

The second line contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \le p_i < i $ ) — the parent of each node.

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i \le 10^6 $ ) — the minimum number of peaches each node needs for the peach tree to be considered healthy.

The next $ q $ lines describe the operations Ruby will perform. Each line contains three integers $ t $ , $ x $ , and $ v $ ( $ 1 \le t \le 2 $ , $ 1 \le x \le n $ , $ 1 \le v \le 10^6 $ ). If $ t = 1 $ , this denotes that Ruby must perform $ v $ growth events on node $ x $ . If $ t = 2 $ , this denotes that Ruby must perform $ v $ harvest events on node $ x $ .

It is guaranteed that the sum of $ n $ does not exceed $ 2 \cdot 10^5 $ and the sum of $ q $ does not exceed $ 2 \cdot 10^5 $

## 输出格式

For each test case, output $ q $ lines. The $ i $ -th line should contain "YES" if Ruby can make the peach tree healthy after performing operations $ 1, 2, \ldots, i $ in some order. Otherwise, it should contain "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

For the prefix containing operations $ 1, 2, \ldots, 5 $ in the first test case, Ruby may perform the operations in the following order:

1. Ruby performs operation $ 2 $ and chooses to increase $ a_4 $ by $ 9 $ and $ a_5 $ by $ 8 $ .
2. Ruby performs operation $ 1 $ and chooses to increase $ a_1 $ by $ 5 $ , $ a_3 $ by $ 2 $ , $ a_6 $ by $ 4 $ , and $ a_8 $ by $ 3 $ .
3. Ruby performs operation $ 3 $ and chooses to increase $ a_2 $ by $ 7 $ .
4. Ruby performs operation $ 4 $ and chooses to decrease $ a_2 $ by $ 1 $ .
5. Ruby performs operation $ 5 $ and chooses to increase $ a_7 $ by $ 1 $ .

## 样例 #1

### 输入

```
2
8 8
1 1 1 4 3 6 6
5 6 2 9 8 4 1 3
1 3 14
1 4 17
1 2 7
2 2 1
1 6 1
2 1 1000000
1 4 999999
1 3 1
10 20
1 1 1 2 5 2 4 7 2
311353 270334 74853 385085 315501 183346 234819 417314 103862 429437
1 1 837541
1 10 933876
1 1 565958
1 4 791455
2 3 85054
2 3 440978
1 4 981040
1 5 68522
2 1 858305
2 4 184308
1 4 905081
2 8 519626
2 2 269090
1 1 43016
2 2 517644
1 5 355792
1 9 319241
2 10 125447
2 10 523890
1 10 241045
```

### 输出

```
NO
NO
YES
NO
YES
NO
NO
YES
NO
NO
NO
YES
YES
NO
NO
YES
YES
NO
YES
YES
NO
YES
NO
NO
YES
YES
NO
NO
```

