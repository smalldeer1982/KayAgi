---
title: "Hypercatapult Commute"
layout: "post"
diff: 提高+/省选-
pid: CF1912H
tag: []
---

# Hypercatapult Commute

## 题目描述

A revolutionary new transport system is currently operating in Byteland. This system requires neither roads nor sophisticated mechanisms, only giant catapults.

The system works as follows. There are $ n $ cities in Byteland. In every city there is a catapult, right in the city center. People who want to travel are put in a special capsule, and a catapult throws this capsule to the center of some other city. Every catapult is powerful enough to throw the capsule to any other city, with any number of passengers inside the capsule. The only problem is that it takes a long time to charge the catapult, so it is only possible to use it once a day.

The passenger may need to use the catapults multiple times. For example, if the passenger wants to travel from city A to city B, they can first use one catapult to move from A to C, and then transfer to another catapult to move from C to B.

Today there are $ m $ passengers. Passenger $ i $ wants to travel from city $ a_i $ to city $ b_i $ . Your task is to find the way to deliver all the passengers to their destinations in a single day, using the minimal possible number of catapults, or say that it is impossible.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq 1000 $ , $ 0 \leq m \leq 10^5 $ ) — the number of cities and the number of passengers. The next $ m $ lines contain pairs of numbers $ a_i $ and $ b_i $ ( $ 1 \leq a_i, b_i \leq n $ , $ a_i \neq b_i $ ).

## 输出格式

In the first line print the number $ k $ — the minimal number of catapults you need to use.

In the next $ k $ lines, print descriptions of each catapult launch, in the order they need to be performed. Each description should consist of two integers $ c_i $ , $ d_i $ , the index of the city to launch from, and the index of destination city.

Note that you don't need to print what passengers should be put into the capsule on each launch, but it should be possible for each passenger to reach their destination city using the plan you provide.

If it is impossible to deliver all passengers, print the single number $ -1 $ .

## 样例 #1

### 输入

```
5 6
1 3
1 2
2 3
4 2
1 5
5 1
```

### 输出

```
5
5 1
1 2
4 2
2 3
3 5
```

## 样例 #2

### 输入

```
3 6
1 2
1 3
2 1
2 3
3 1
3 2
```

### 输出

```
-1
```

