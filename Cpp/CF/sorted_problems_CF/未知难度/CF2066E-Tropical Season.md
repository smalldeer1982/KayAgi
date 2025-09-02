---
title: "Tropical Season"
layout: "post"
diff: 难度0
pid: CF2066E
tag: []
---

# Tropical Season

## 题目描述

You have $ n $ barrels of infinite capacity. The $ i $ -th barrel initially contains $ a_i $ kilograms of water. In this problem, we assume that all barrels weigh the same.

You know that exactly one of the barrels has a small amount of tropical poison distributed on its surface, with a total weight of $ 0.179 $ kilograms. However, you do not know which barrel contains the poison. Your task is to identify this poisonous barrel.

All the barrels are on scales. Unfortunately, the scales do not show the exact weight of each barrel. Instead, for each pair of barrels, they show the result of a comparison between the weights of those barrels. Thus, for any two barrels, you can determine whether their weights are equal, and if not, which barrel is heavier. The poison and water are included in the weight of the barrel.

The scales are always turned on, and the information from them can be used an unlimited number of times.

You also have the ability to pour water. You can pour water from any barrel into any other barrel in any amounts.

However, to pour water, you must physically handle the barrel from which you are pouring, so if that happens to be the poisonous barrel, you will die. This outcome must be avoided.

However, you can pour water into the poisonous barrel without touching it.

In other words, you can choose the numbers $ i, j, x $ ( $ i \neq j, 1 \leq i, j \leq n, 0 < x \leq a_i $ , the barrel numbered $ i $ is not poisonous) and execute $ a_i := a_i - x $ , $ a_j := a_j + x $ . Where $ x $ is not necessarily an integer.

Is it possible to guarantee the identification of which barrel contains the poison and remain alive using pouring and the information from the scales? You know that the poison is located on exactly one of the barrels.

Additionally, we ask you to process $ q $ queries. In each query, either one of the existing barrels is removed, or an additional barrel with a certain amount of water is added. After each query, you need to answer whether it is possible to guarantee the identification of the poisonous barrel, given that there is exactly one.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the volumes of water in the existing barrels.

The next $ q $ lines contain queries, one per line. Each query is either of the form + x or - x, which means, respectively, adding and removing a barrel with $ x $ kilograms of water. It is guaranteed that when the query - x is made, one of the existing barrels has a volume of $ x $ , and that there is always at least one barrel remaining throughout the queries. In all queries, $ 1 \leq x \leq 10^6 $ .

## 输出格式

Output $ q+1 $ lines, the answer to the problem before all queries, and after each query. If it is possible to identify the poisonous barrel, output "Yes"; otherwise, output "No". You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test, before any queries, the weights of the barrels are $ [2, 2, 4, 11] $ . You can compare the values of the first and second barrels. If the result is not equal, you can definitively conclude that the barrel with the greater weight is poisonous. If the result is equal, both barrels are non-poisonous. Then you can pour all the contents of the first barrel into the second. After that, both the second and third barrels will contain $ 4 $ kilograms of water. Now let's compare the values of the second and third barrels. If the result is not equal, the barrel with the greater weight is poisonous. Otherwise, both barrels are non-poisonous. The only barrel that could be poisonous is barrel 4. Thus, with this strategy, we can safely determine the poisonous barrel.

## 样例 #1

### 输入

```
4 7
2 2 4 11
- 2
+ 4
+ 30
+ 40
- 4
+ 2
+ 2
```

### 输出

```
Yes
No
Yes
No
Yes
No
No
Yes
```

## 样例 #2

### 输入

```
6 7
5000 1000 400 400 100 99
+ 1
- 5000
- 1
- 400
- 400
- 100
- 99
```

### 输出

```
No
Yes
Yes
Yes
No
No
No
Yes
```

