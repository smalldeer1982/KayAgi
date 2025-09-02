---
title: "Labyrinth"
layout: "post"
diff: 提高+/省选-
pid: CF1578L
tag: ['Kruskal 重构树', '树形 DP']
---

# Labyrinth

## 题目描述

In a dream, Lucy found herself in a labyrinth. This labyrinth consists of $ n $ rooms, connected by $ m $ passages ( $ i $ -th passage is $ w_i $ cm wide). Each passage can be traversed in both directions. It is guaranteed that it is possible to get from any room to any other room. But this is not an ordinary labyrinth — each room in this labyrinth contains a magic candy. When Lucy eats this magic candy, she is getting wider. Specifically, if she eats candy from room $ i $ she becomes wider by $ c_i $ cm. Note that she is not obliged to eat candy the first time she visits a particular room, but she can eat each candy only once.

Unfortunately, passages in this labyrinth are pretty narrow, so after eating some candy, Lucy can get too wide and will not be able to traverse them — her width should not be greater than the width of the corresponding passage.

Lucy starts her journey in a room number $ 1 $ . She wants to eat all the candies. After that, she will just wake up, so she does not have to be able to return to the room $ 1 $ . She realizes that with her current width, she may not be able to do so, so she plans a workout before embarking on her journey. Lucy wants to know if it is possible to start with some positive width and still eat all the candies. If yes, then what is the maximal starting width with which it is possible.

## 输入格式

The first line contains two integers, $ n $ and $ m $ ( $ 2 \le n \le 10^5; n - 1 \le m \le 10^5 $ ) — the number of rooms and the number of passages.

The second line contains $ n $ integers — $ c_i $ ( $ 1 \le c_i \le 10^9 $ ).

Next $ m $ lines contain three integers each — $ a_i $ , $ b_i $ and $ w_i $ ( $ 1 \le a_i, b_i \le n; a_i \ne b_i; 1 \le w_i \le 10^9 $ ) describing passage that connects rooms $ a_i $ and $ b_i $ and is $ w_i $ cm wide. It is guaranteed that the resulting labyrinth is connected and there is at most one passage between any pair of rooms.

## 输出格式

If it is possible to eat all the candies, output the maximal possible starting width, otherwise output $ -1 $ .

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 4
1 3 4
2 3 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
1 1
1 2 1
```

### 输出

```
-1
```

