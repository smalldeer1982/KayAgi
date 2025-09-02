# Game of Division

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ and an integer $ k $ .

Two players are playing a game. The first player chooses an index $ 1 \le i \le n $ . Then the second player chooses a different index $ 1 \le j \le n, i \neq j $ . The first player wins if $ |a_i - a_j| $ is not divisible by $ k $ . Otherwise, the second player wins.

We play as the first player. Determine whether it is possible to win, and if so, which index $ i $ should be chosen.

The absolute value of a number $ x $ is denoted by $ |x| $ and is equal to $ x $ if $ x \ge 0 $ , and $ -x $ otherwise.

## 说明/提示

In the first test case, the first player can choose $ a_2 = 2 $ . Then:

- If the second player chooses $ a_1 = 1 $ , the resulting difference is $ |2 - 1| = 1 $ which is not divisible by $ k = 2 $ .
- If the second player chooses $ a_3 = 3 $ , the resulting difference is $ |2 - 3| = 1 $ which is not divisible by $ k = 2 $ .

In the second test case:

- If the first player chooses $ a_1 = 1 $ and then the second player chooses $ a_4 = 5 $ , the resulting difference is $ |1 - 5| = 4 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_2 = 2 $ and then the second player chooses $ a_3 = 4 $ , the resulting difference is $ |2 - 4| = 2 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_3 = 4 $ and then the second player chooses $ a_2 = 2 $ , the resulting difference is $ |4 - 2| = 2 $ which is divisible by $ k = 2 $ .
- If the first player chooses $ a_4 = 5 $ and then the second player chooses $ a_1 = 1 $ , the resulting difference is $ |5 - 1| = 4 $ which is divisible by $ k = 2 $ .

 In any case, the second player wins.

## 样例 #1

### 输入

```
7
3 2
1 2 3
4 2
1 2 4 5
5 3
10 7 3 4 5
5 3
1 31 15 55 36
2 1
17 17
2 2
17 18
1 3
6```

### 输出

```
YES
2
NO
YES
3
NO
NO
YES
2
YES
1```

