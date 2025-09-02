---
title: "Problem of offices"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF793E
tag: []
---

# Problem of offices

## 题目描述

Earlier, when there was no Internet, each bank had a lot of offices all around Bankopolis, and it caused a lot of problems. Namely, each day the bank had to collect cash from all the offices.

Once Oleg the bank client heard a dialogue of two cash collectors. Each day they traveled through all the departments and offices of the bank following the same route every day. The collectors started from the central department and moved between some departments or between some department and some office using special roads. Finally, they returned to the central department. The total number of departments and offices was $ n $ , the total number of roads was $ n-1 $ . In other words, the special roads system was a rooted tree in which the root was the central department, the leaves were offices, the internal vertices were departments. The collectors always followed the same route in which the number of roads was minimum possible, that is $ 2n-2 $ .

One of the collectors said that the number of offices they visited between their visits to offices $ a $ and then $ b $ (in the given order) is equal to the number of offices they visited between their visits to offices $ b $ and then $ a $ (in this order). The other collector said that the number of offices they visited between their visits to offices $ c $ and then $ d $ (in this order) is equal to the number of offices they visited between their visits to offices $ d $ and then $ c $ (in this order). The interesting part in this talk was that the shortest path (using special roads only) between any pair of offices among $ a $ , $ b $ , $ c $ and $ d $ passed through the central department.

Given the special roads map and the indexes of offices $ a $ , $ b $ , $ c $ and $ d $ , determine if the situation described by the collectors was possible, or not.

## 输入格式

The first line contains single integer $ n $ ( $ 5<=n<=5000 $ ) — the total number of offices and departments. The departments and offices are numbered from $ 1 $ to $ n $ , the central office has index $ 1 $ .

The second line contains four integers $ a $ , $ b $ , $ c $ and $ d $ ( $ 2<=a,b,c,d<=n $ ) — the indexes of the departments mentioned in collector's dialogue. It is guaranteed that these indexes are offices (i.e. leaves of the tree), not departments. It is guaranteed that the shortest path between any pair of these offices passes through the central department.

On the third line $ n-1 $ integers follow: $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ denotes that there is a special road between the $ i $ -th office or department and the $ p_{i} $ -th department.

Please note the joint enumeration of departments and offices.

It is guaranteed that the given graph is a tree. The offices are the leaves, the departments are the internal vertices.

## 输出格式

If the situation described by the cash collectors was possible, print "YES". Otherwise, print "NO".

## 说明/提示

In the first example the following collector's route was possible: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793E/8840cad45c05d45991434c10711314b6750790eb.png). We can note that between their visits to offices $ a $ and $ b $ the collectors visited the same number of offices as between visits to offices $ b $ and $ a $ ; the same holds for $ c $ and $ d $ (the collectors' route is infinite as they follow it each day).

In the second example there is no route such that between their visits to offices $ c $ and $ d $ the collectors visited the same number of offices as between visits to offices $ d $ and $ c $ . Thus, there situation is impossible.

In the third example one of the following routes is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793E/83a8837e7fd1905a94610e0b97183f842e9a48d3.png).

## 样例 #1

### 输入

```
5
2 3 4 5
1 1 1 1

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
10
3 8 9 10
1 2 2 2 2 2 1 1 1

```

### 输出

```
NO
```

## 样例 #3

### 输入

```
13
13 12 9 7
1 1 1 1 5 5 2 2 2 3 3 4

```

### 输出

```
YES
```

