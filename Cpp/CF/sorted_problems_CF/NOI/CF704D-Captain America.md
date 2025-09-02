---
title: "Captain America"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF704D
tag: []
---

# Captain America

## 题目描述

Steve Rogers is fascinated with new vibranium shields S.H.I.E.L.D gave him. They're all uncolored. There are $ n $ shields in total, the $ i $ -th shield is located at point $ (x_{i},y_{i}) $ of the coordinate plane. It's possible that two or more shields share the same location.

Steve wants to paint all these shields. He paints each shield in either red or blue. Painting a shield in red costs $ r $ dollars while painting it in blue costs $ b $ dollars.

Additionally, there are $ m $ constraints Steve wants to be satisfied. The $ i $ -th constraint is provided by three integers $ t_{i} $ , $ l_{i} $ and $ d_{i} $ :

- If $ t_{i}=1 $ , then the absolute difference between the number of red and blue shields on line $ x=l_{i} $ should not exceed $ d_{i} $ .
- If $ t_{i}=2 $ , then the absolute difference between the number of red and blue shields on line $ y=l_{i} $ should not exceed $ d_{i} $ .

Steve gave you the task of finding the painting that satisfies all the condition and the total cost is minimum.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100000 $ ) — the number of shields and the number of constraints respectively.

The second line contains two integers $ r $ and $ b $ ( $ 1<=r,b<=10^{9} $ ).

The next $ n $ lines contain the shields coordinates. The $ i $ -th of these lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{9} $ ).

The next $ m $ lines contain the constrains. The $ j $ -th of these lines contains three integers $ t_{j} $ , $ l_{j} $ and $ d_{j} $ ( $ 1<=t_{j}<=2,1<=l_{j}<=10^{9},0<=d_{j}<=n $ ).

## 输出格式

If satisfying all the constraints is impossible print -1 in first and only line of the output.

Otherwise, print the minimum total cost in the first line of output. In the second line print a string of length $ n $ consisting of letters 'r' and 'b' only. The $ i $ -th character should be 'r' if the $ i $ -th shield should be painted red in the optimal answer and 'b' if it should be painted blue. The cost of painting shields in these colors should be equal the minimum cost you printed on the first line.

If there exist more than one optimal solution, print any of them.

## 样例 #1

### 输入

```
5 6
8 3
2 10
1 5
9 10
9 10
2 8
1 9 1
1 2 1
2 10 3
2 10 2
1 1 1
2 5 2

```

### 输出

```
25
rbrbb

```

## 样例 #2

### 输入

```
4 4
7 3
10 3
9 8
10 3
2 8
2 8 0
2 8 0
1 2 0
1 9 0

```

### 输出

```
-1

```

