---
title: "Editorial for Two"
layout: "post"
diff: 提高+/省选-
pid: CF1837F
tag: []
---

# Editorial for Two

## 题目描述

Berland Intercollegiate Contest has just finished. Monocarp and Polycarp, as the jury, are going to conduct an editorial. Unfortunately, the time is limited, since they have to finish before the closing ceremony.

There were $ n $ problems in the contest. The problems are numbered from $ 1 $ to $ n $ . The editorial for the $ i $ -th problem takes $ a_i $ minutes. Monocarp and Polycarp are going to conduct an editorial for exactly $ k $ of the problems.

The editorial goes as follows. They have a full problemset of $ n $ problems before them, in order. They remove $ n - k $ problems without changing the order of the remaining $ k $ problems. Then, Monocarp takes some prefix of these $ k $ problems (possibly, an empty one or all problems). Polycarp takes the remaining suffix of them. After that, they go to different rooms and conduct editorials for their problems in parallel. So, the editorial takes as much time as the longer of these two does.

Please, help Monocarp and Polycarp to choose the problems and the split in such a way that the editorial finishes as early as possible. Print the duration of the editorial.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 3 \cdot 10^5 $ ) — the number of problems in the full problemset and the number of problems Monocarp and Polycarp are going to conduct an editorial for.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the time each editorial takes.

The sum of $ n $ over all testcases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the smallest amount of time the editorial takes, if Monocarp and Polycarp can choose which $ k $ of $ n $ problems to conduct an editorial for and how to split them among themselves.

## 样例 #1

### 输入

```
6
5 4
1 10 1 1 1
5 3
1 20 5 15 3
5 3
1 20 3 15 5
10 6
10 8 20 14 3 8 6 4 16 11
10 5
9 9 2 13 15 19 4 9 13 12
1 1
1
```

### 输出

```
2
6
5
21
18
1
```

