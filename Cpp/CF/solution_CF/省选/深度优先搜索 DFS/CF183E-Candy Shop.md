# Candy Shop

## 题目描述

The prestigious Codeforces kindergarten consists of $ n $ kids, numbered $ 1 $ through $ n $ . Each of them are given allowance in rubles by their parents.

Today, they are going to the most famous candy shop in the town. The shop sells candies in packages: for all $ i $ between $ 1 $ and $ m $ , inclusive, it sells a package containing exactly $ i $ candies. A candy costs one ruble, so a package containing $ x $ candies costs $ x $ rubles.

The kids will purchase candies in turns, starting from kid 1. In a single turn, kid $ i $ will purchase one candy package. Due to the highly competitive nature of Codeforces kindergarten, during a turn, the number of candies contained in the package purchased by the kid will always be strictly greater than the number of candies contained in the package purchased by the kid in the preceding turn (an exception is in the first turn: the first kid may purchase any package). Then, the turn proceeds to kid $ i+1 $ , or to kid $ 1 $ if it was kid $ n $ 's turn. This process can be ended at any time, but at the end of the purchase process, all the kids must have the same number of candy packages. Of course, the amount spent by each kid on the candies cannot exceed their allowance.

You work at the candy shop and would like to prepare the candies for the kids. Print the maximum number of candies that can be sold by the candy shop to the kids. If the kids cannot purchase any candy (due to insufficient allowance), print $ 0 $ .

## 说明/提示

For the first example, one of the scenarios that will result in $ 13 $ purchased candies is as follows.

- Turn 1. Kid 1 purchases 1 candy.
- Turn 2. Kid 2 purchases 3 candies.
- Turn 3. Kid 1 purchases 4 candies.
- Turn 4. Kid 2 purchases 5 candies.

## 样例 #1

### 输入

```
2 5
5
10
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3 8
8
16
13
```

### 输出

```
32
```

## 样例 #3

### 输入

```
2 5000000
12500002500000
12500002500000
```

### 输出

```
12500002500000
```

