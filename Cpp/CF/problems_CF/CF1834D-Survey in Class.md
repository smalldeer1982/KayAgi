---
title: "Survey in Class"
layout: "post"
diff: 提高+/省选-
pid: CF1834D
tag: []
---

# Survey in Class

## 题目描述

Zinaida Viktorovna has $ n $ students in her history class. The homework for today included $ m $ topics, but the students had little time to prepare, so $ i $ -th student learned only topics from $ l_i $ to $ r_i $ inclusive.

At the beginning of the lesson, each student holds their hand at $ 0 $ . The teacher wants to ask some topics. It goes like this:

- The teacher asks the topic $ k $ .
- If the student has learned topic $ k $ , then he raises his hand by $ 1 $ , otherwise he lower it by $ 1 $ .

Each topic Zinaida Viktorovna can ask no more than one time.

Find the maximum difference of the heights of the highest and the lowest hand that can be in class after the survey.

Note that the student's hand can go below $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 10^5, 1 \le m \le 10^9 $ ) — the number of students and the number of topics, respectively.

Each of the next $ n $ lines of each test case contain two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le m $ ) — the endpoints of the segment of topics that $ i $ -th student has learned.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print one integer — the maximum difference of the heights of the highest and the lowest hand that can be in the class after the survey.

## 说明/提示

In the first test case, Zinaida Viktorovna can ask the topics $ 5, 6, 7, 8 $ . Then the hand of the $ 2 $ -nd student will be at the height of $ 4 $ , and the hand of the $ 4 $ -th will be at the height of $ -2 $ , that is, the difference will be equal to $ 6 $ .

In the second test case, you can ask about the topics $ 1 $ and $ 3 $ . Then the hand of the $ 1 $ -st student will be at the height of $ 2 $ and the hand of the $ 3 $ -rd student will be at the height of $ -2 $ . So the difference will be $ 4 $ .

In the third test case, the difference between the highest and lowest hand will be $ 0 $ for any set of topics asked.

In the fifth test case, you can ask all topics. Then the difference between the heights of the $ 1 $ -st and $ 3 $ -rd students' hands will be $ 12 $ .

## 样例 #1

### 输入

```
6
4 8
2 6
4 8
2 7
1 5
3 3
1 3
2 3
2 2
3 5
1 5
1 5
1 5
3 5
1 1
3 3
5 5
4 7
1 7
1 3
3 3
4 5
2 4
1 3
2 4
```

### 输出

```
6
4
0
2
12
2
```

