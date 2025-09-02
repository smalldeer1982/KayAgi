---
title: "Stardew Valley"
layout: "post"
diff: 提高+/省选-
pid: CF1994F
tag: ['欧拉回路']
---

# Stardew Valley

## 题目描述

Pelican Town represents $ n $ houses connected by $ m $ bidirectional roads. Some roads have NPCs standing on them. Farmer Buba needs to walk on each road with an NPC and talk to them.

Help the farmer find a route satisfying the following properties:

- The route starts at some house, follows the roads, and ends at the same house.
- The route does not follow any road more than once (in both directions together).
- The route follows each road with an NPC exactly once.

 Note that the route can follow roads without NPCs, and you do not need to minimize the length of the route.It is guaranteed that you can reach any house from any other by walking on the roads with NPCs only.

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 5 \cdot 10^5, 1 \leq m \leq 5 \cdot 10^5 $ ) — the number of houses and roads in Pelican Town respectively.

In each of the next $ m $ lines, three integers $ u $ , $ v $ , and $ c $ ( $ 1 \leq u, v \leq n, c = 0/1 $ ) are given — the ends of the road and whether an NPC is on this road. If $ c = 1 $ , then the road has an NPC. If $ c = 0 $ , then the road has no NPC.

The graph may contain multiple edges and loops, and if there are multiple edges with NPCs standing on them, the route must follow each of these roads.

It is guaranteed that you can reach any house from any other by walking on the roads with NPCs only.

It is guaranteed that the sum of $ n $ and $ m $ for all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, if there is no solution, then output "No" (without quotes).

Otherwise, output "Yes" (without quotes), and then output $ k $ — the number of roads in the route. In the next line, output $ k + 1 $ numbers — the houses of the route in the order of traversal. Note that the first house should match the last one, as the route is cyclic.

If there are multiple answers, you can print any of them.

You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

Note that in the third test case, there are multiple edges $ (5, 2) $ . You must walk on two of them.

## 样例 #1

### 输入

```
3
3 2
1 2 1
2 3 1
3 3
1 2 1
1 3 1
2 3 0
5 9
1 2 0
5 2 1
5 4 1
5 1 1
2 3 1
5 2 1
4 1 0
4 3 0
5 2 0
```

### 输出

```
NO
YES
3
1 2 3 1 
YES
7
1 2 5 4 3 2 5 1
```

