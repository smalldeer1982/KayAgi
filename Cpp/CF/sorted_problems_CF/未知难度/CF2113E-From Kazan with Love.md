---
title: "From Kazan with Love"
layout: "post"
diff: 难度0
pid: CF2113E
tag: []
---

# From Kazan with Love

## 题目描述

Marat is a native of Kazan. Kazan can be represented as an undirected tree consisting of $ n $ vertices. In his youth, Marat often got into street fights, and now he has $ m $ enemies, numbered from $ 1 $ to $ m $ , living in Kazan along with him.

Every day, all the people living in the city go to work. Marat knows that the $ i $ -th of his enemies lives at vertex $ a_i $ and works at vertex $ b_i $ . He himself lives at vertex $ x $ and works at vertex $ y $ . It is guaranteed that $ a_i \ne x $ .

All enemies go to work via the shortest path and leave their homes at time $ 1 $ . That is, if we represent the shortest path between vertices $ a_i $ and $ b_i $ as $ c_1, c_2, c_3, \ldots, c_k $ (where $ c_1 = a_i $ and $ c_k = b_i $ ), then at the moment $ p $ ( $ 1 \le p \le k $ ), the enemy numbered $ i $ will be at vertex $ c_p $ .

Marat really does not want to meet any of his enemies at the same vertex at the same time, as this would create an awkward situation, but they can meet on an edge. Marat also leaves his home at time $ 1 $ , and at each subsequent moment in time, he can either move to an adjacent vertex or stay at his current one.

Note that Marat can only meet the $ i $ -th enemy at the moments $ 2, 3, \ldots, k $ (where $ c_1, c_2, \ldots, c_k $ is the shortest path between vertices $ a_i $ and $ b_i $ ). In other words, starting from the moment after the enemy reaches work, Marat can no longer meet him.

Help Marat find the earliest moment in time when he can reach work without encountering any enemies along the way, or determine that it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains four integers $ n $ , $ m $ , $ x $ , and $ y $ ( $ 2 \le n \le 10^5 $ , $ 1 \le m \le 200 $ , $ 1 \le x, y \le n $ , $ x \neq y $ ) — the number of vertices in the tree, the number of enemies, and the vertex numbers from which Marat starts his journey and where he needs to arrive, respectively.

The $ j $ -th of the following $ n - 1 $ lines contains two integers $ v_j $ and $ u_j $ ( $ 1 \le v_j, u_j \le n $ , $ v_j \neq u_j $ ) — the endpoints of the $ j $ -th edge of the tree.

The $ i $ -th of the following $ m $ lines contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i, b_i \le n $ , $ a_i \neq b_i $ , $ a_i \ne x $ ) — the description of the routes of Marat's enemies.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum moment in time when Marat can reach work, or $ -1 $ if it is impossible.

## 说明/提示

In the first test case, it is possible to reach vertex number $ 4 $ from vertex number $ 1 $ via the shortest path. Note that Marat will meet a single enemy on an edge, not at a vertex.

In the second test case, the optimal strategy is to wait for one moment in time at the starting vertex and then go along the shortest path from vertex $ 1 $ to vertex $ 5 $ . If he does not stop at the beginning, Marat will meet his enemy at a vertex, not on an edge.

In the third test case, it is beneficial to go from vertex $ 1 $ to vertex $ 4 $ . After that, he should not move anywhere for one moment in time, and then go along the shortest path from vertex $ 4 $ to vertex $ 9 $ .

## 样例 #1

### 输入

```
5
4 1 1 4
1 2
2 3
3 4
4 1
5 1 1 5
1 2
2 3
3 4
4 5
5 1
9 2 1 9
1 2
2 3
3 4
3 5
5 6
6 7
6 8
8 9
9 1
7 1
9 2 7 2
1 4
2 5
3 6
4 5
5 6
4 7
5 8
6 9
2 8
3 7
3 2 1 3
1 2
2 3
2 1
3 1
```

### 输出

```
4
6
10
5
-1
```

