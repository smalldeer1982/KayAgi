---
title: "Chemistry Experiment"
layout: "post"
diff: 普及+/提高
pid: CF431E
tag: []
---

# Chemistry Experiment

## 题目描述

One day two students, Grisha and Diana, found themselves in the university chemistry lab. In the lab the students found $ n $ test tubes with mercury numbered from $ 1 $ to $ n $ and decided to conduct an experiment.

The experiment consists of $ q $ steps. On each step, one of the following actions occurs:

1. Diana pours all the contents from tube number $ p_{i} $ and then pours there exactly $ x_{i} $ liters of mercury.
2. Let's consider all the ways to add $ v_{i} $ liters of water into the tubes; for each way let's count the volume of liquid (water and mercury) in the tube with water with maximum amount of liquid; finally let's find the minimum among counted maximums. That is the number the students want to count. At that, the students don't actually pour the mercury. They perform calculations without changing the contents of the tubes.

Unfortunately, the calculations proved to be too complex and the students asked you to help them. Help them conduct the described experiment.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1<=n,q<=10^{5} $ ) — the number of tubes ans the number of experiment steps. The next line contains $ n $ space-separated integers: $ h_{1},h_{2},...,h_{n} $ ( $ 0<=h_{i}<=10^{9} $ ), where $ h_{i} $ is the volume of mercury in the $ і $ -th tube at the beginning of the experiment.

The next $ q $ lines contain the game actions in the following format:

- A line of form " $ 1 $ $ p_{i} $ $ x_{i} $ " means an action of the first type ( $ 1<=p_{i}<=n; 0<=x_{i}<=10^{9} $ ).
- A line of form " $ 2 $ $ v_{i} $ " means an action of the second type ( $ 1<=v_{i}<=10^{15} $ ).

It is guaranteed that there is at least one action of the second type. It is guaranteed that all numbers that describe the experiment are integers.

## 输出格式

For each action of the second type print the calculated value. The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
3 3
1 2 0
2 2
1 2 1
2 3

```

### 输出

```
1.50000
1.66667

```

## 样例 #2

### 输入

```
4 5
1 3 0 1
2 3
2 1
1 3 2
2 3
2 4

```

### 输出

```
1.66667
1.00000
2.33333
2.66667

```

