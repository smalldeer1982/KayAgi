---
title: "Three Activities"
layout: "post"
diff: 普及/提高-
pid: CF1914D
tag: ['枚举']
---

# Three Activities

## 题目描述

Winter holidays are coming up. They are going to last for $ n $ days.

During the holidays, Monocarp wants to try all of these activities exactly once with his friends:

- go skiing;
- watch a movie in a cinema;
- play board games.

Monocarp knows that, on the $ i $ -th day, exactly $ a_i $ friends will join him for skiing, $ b_i $ friends will join him for a movie and $ c_i $ friends will join him for board games.

Monocarp also knows that he can't try more than one activity in a single day.

Thus, he asks you to help him choose three distinct days $ x, y, z $ in such a way that the total number of friends to join him for the activities ( $ a_x + b_y + c_z $ ) is maximized.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the duration of the winter holidays in days.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^8 $ ) — the number of friends that will join Monocarp for skiing on the $ i $ -th day.

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^8 $ ) — the number of friends that will join Monocarp for a movie on the $ i $ -th day.

The fourth line contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^8 $ ) — the number of friends that will join Monocarp for board games on the $ i $ -th day.

The sum of $ n $ over all testcases doesn't exceed $ 10^5 $ .

## 输出格式

For each testcase, print a single integer — the maximum total number of friends that can join Monocarp for the activities on three distinct days.

## 说明/提示

In the first testcase, Monocarp can choose day $ 2 $ for skiing, day $ 1 $ for a movie and day $ 3 $ for board games. This way, $ a_2 = 10 $ friends will join him for skiing, $ b_1 = 10 $ friends will join him for a movie and $ c_3 = 10 $ friends will join him for board games. The total number of friends is $ 30 $ .

In the second testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 2 $ for board games. $ 30 + 20 + 25 = 75 $ friends in total. Note that Monocarp can't choose day $ 1 $ for all activities, because he can't try more than one activity in a single day.

In the third testcase, Monocarp can choose day $ 2 $ for skiing, day $ 3 $ for a movie and day $ 7 $ for board games. $ 19 + 19 + 17 = 55 $ friends in total.

In the fourth testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 9 $ for board games. $ 17 + 19 + 20 = 56 $ friends in total.

## 样例 #1

### 输入

```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3
```

### 输出

```
30
75
55
56
```

