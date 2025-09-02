---
title: "Monster"
layout: "post"
diff: 提高+/省选-
pid: CF2035E
tag: ['动态规划 DP', '模拟退火', '根号分治']
---

# Monster

## 题目描述

Man, this Genshin boss is so hard. Good thing they have a top-up of $ 6 $ coins for only $  \$4.99 $ . I should be careful and spend no more than I need to, lest my mom catches me...



You are fighting a monster with $ z $ health using a weapon with $ d $ damage. Initially, $ d=0 $ . You can perform the following operations.

- Increase $ d $ — the damage of your weapon by $ 1 $ , costing $ x $ coins.
- Attack the monster, dealing $ d $ damage and costing $ y $ coins.

You cannot perform the first operation for more than $ k $ times in a row.

Find the minimum number of coins needed to defeat the monster by dealing at least $ z $ damage.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases.

The only line of each test case contains 4 integers $ x $ , $ y $ , $ z $ , and $ k $ ( $ 1\leq x, y, z, k\leq 10^8 $ ) — the first operation's cost, the second operation's cost, the monster's health, and the limitation on the first operation.

## 输出格式

For each test case, output the minimum number of coins needed to defeat the monster.

## 说明/提示

In the first test case, $ x = 2 $ , $ y = 3 $ , $ z = 5 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 12 $ coins:

- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.

You deal a total of $ 3 + 3 = 6 $ damage, defeating the monster who has $ 5 $ health. The total number of coins you use is $ 2 + 2 + 2 + 3 + 3 = 12 $ coins.

In the second test case, $ x = 10 $ , $ y = 20 $ , $ z = 40 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 190 $ coins:

- Increase damage by $ 5 $ , costing $ 5\cdot x $ = $ 50 $ coins.
- Attack the monster once, dealing $ 5 $ damage, costing $ 20 $ coins.
- Increase damage by $ 2 $ , costing $ 2\cdot x $ = $ 20 $ coins.
- Attack the monster $ 5 $ times, dealing $ 5\cdot 7 = 35 $ damage, costing $ 5\cdot y $ = $ 100 $ coins.

You deal a total of $ 5 + 35 = 40 $ damage, defeating the monster who has exactly $ 40 $ health. The total number of coins you use is $ 50 + 20 + 20 + 100 = 190 $ coins.

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10
```

### 输出

```
12
190
280
160
```



---

---
title: "Commentator problem"
layout: "post"
diff: 提高+/省选-
pid: CF2C
tag: ['模拟', '搜索', '模拟退火']
---

# Commentator problem

## 题目描述

The Olympic Games in Bercouver are in full swing now. Here everyone has their own objectives: sportsmen compete for medals, and sport commentators compete for more convenient positions to give a running commentary. Today the main sport events take place at three round stadiums, and the commentator's objective is to choose the best point of observation, that is to say the point from where all the three stadiums can be observed. As all the sport competitions are of the same importance, the stadiums should be observed at the same angle. If the number of points meeting the conditions is more than one, the point with the maximum angle of observation is prefered.

Would you, please, help the famous Berland commentator G. Berniev to find the best point of observation. It should be noted, that the stadiums do not hide each other, the commentator can easily see one stadium through the other.

## 输入格式

The input data consists of three lines, each of them describes the position of one stadium. The lines have the format $ x,y,r $ , where ( $ x,y $ ) are the coordinates of the stadium's center ( $ -10^{3}<=x,y<=10^{3} $ ), and $ r $ ( $ 1<=r<=10^{3} $ ) is its radius. All the numbers in the input data are integer, stadiums do not have common points, and their centers are not on the same line.

## 输出格式

Print the coordinates of the required point with five digits after the decimal point. If there is no answer meeting the conditions, the program shouldn't print anything. The output data should be left blank.

## 样例 #1

### 输入

```
0 0 10
60 0 10
30 30 10

```

### 输出

```
30.00000 0.00000

```



---

