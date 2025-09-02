---
title: "Tea Queue"
layout: "post"
diff: 普及-
pid: CF920B
tag: ['模拟', '枚举', '队列']
---

# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=1000 $ ).

Then $ t $ test cases follow. The first line of each test case contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of students.

Then $ n $ lines follow. Each line contains two integer $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=5000 $ ) — the second $ i $ -th student comes to the end of the queue, and the second he leaves the queue if he still cannot get his tea.

It is guaranteed that for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920B/748ee9e1ae91d0e555bb85d14ee499f01d330017.png) condition $ l_{i-1}<=l_{i} $ holds.

The sum of $ n $ over all test cases doesn't exceed $ 1000 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print $ n $ integers. $ i $ -th of them must be equal to the second when $ i $ -th student gets his tea, or $ 0 $ if he leaves without tea.

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3

```

### 输出

```
1 2 
1 0 2 

```

