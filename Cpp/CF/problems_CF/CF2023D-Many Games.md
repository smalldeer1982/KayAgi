---
title: "Many Games"
layout: "post"
diff: 省选/NOI-
pid: CF2023D
tag: ['动态规划 DP', '数学', '剪枝', '概率论']
---

# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of games offered to play.

The $ i $ -th of the following $ n $ lines contains two integers $ p_i $ and $ w_i $ ( $ 1 \leq p_i \leq 100 $ , $ 1 \leq w_i, p_i \cdot w_i \leq 2 \cdot 10^5 $ ) — the probability of winning and the size of the winnings in the $ i $ -th game.

## 输出格式

Output a single number — the maximum expected value of winnings in the casino that can be obtained by choosing some subset of games.

Your answer will be accepted if the relative or absolute error does not exceed $ 10^{-6} $ . Formally, if $ a $ is your answer and $ b $ is the jury's answer, it will be accepted if $ \frac{|a-b|}{\max(b, 1)} \le 10^{-6} $ .

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200
```

### 输出

```
112.00000000
```

## 样例 #2

### 输入

```
2
100 1
100 1
```

### 输出

```
2.00000000
```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1
```

### 输出

```
20.00000000
```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79
```

### 输出

```
395.20423800
```

