---
title: "Cook and Porridge"
layout: "post"
diff: 普及+/提高
pid: CF1945G
tag: ['模拟', '堆']
---

# Cook and Porridge

## 题目描述

Finally, lunchtime!

 $ n $ schoolchildren have lined up in a long queue at the cook's tent for porridge. The cook will be serving porridge for $ D $ minutes. The schoolchild standing in the $ i $ -th position in the queue has a priority of $ k_i $ and eats one portion of porridge in $ s_i $ minutes.

At the beginning of each minute of the break, the cook serves the first schoolchild in the queue one portion of porridge, after which the schoolchild goes to eat their portion. If the $ i $ -th schoolchild is served a portion at the beginning of the $ x $ -th minute, then they will return to the queue at the end of the $ (x + s_i) $ -th minute.

When the $ i $ -th schoolchild returns to the queue, the schoolchildren at the end of the queue whose priority is strictly lower than that of the $ i $ -th schoolchild must let them pass. Thus, they will stand in the queue behind the last schoolchild whose priority is not lower than their own. That is, behind the last schoolchild $ j $ with $ k_j \ge k_i $ . If there is no such schoolchild in the queue, the $ i $ -th schoolchild will stand at the front of the queue.

If several schoolchildren return at the same time, they will return to the queue in ascending order of their $ s_i $ .

For example, if $ n = 3 $ , $ D = 3 $ , $ k = [2, 3, 2] $ , and $ s = [2, 1, 3] $ , the serving will occur as follows:

- At the beginning of minute $ 1 $ , the students in the queue are $ [1, 2, 3] $ , and student $ 1 $ is served porridge;
- at the beginning of minute $ 2 $ , the students in the queue are $ [2, 3] $ , and student $ 2 $ is served porridge;
- at the beginning of minute $ 3 $ , the student in the queue is $ [3] $ , and student $ 3 $ is served porridge;
- at the end of minute $ 3 $ , student $ 2 $ returns to the queue, and the queue becomes $ [2] $ ;
- at the end of minute $ 3 $ , student $ 1 $ returns to the queue, and the queue becomes $ [2, 1] $ , as his priority is lower.

Determine the minimum number of minutes after the start of the break that each schoolchild will receive porridge at least once, or report that this will not happen within $ D $ minutes.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains two integers $ n $ and $ D $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le D \le 3\cdot 10^5 $ ) — the number of schoolchildren in the queue and the break time, respectively.

The next $ n $ lines contain two integers $ k_i $ and $ s_i $ ( $ 1 \le k_i, s_i, \le 10^9 $ ) — the priority and the time to eat one portion of porridge for the respective schoolchild. The schoolchildren are given in the order they stand in the queue (from the front to the end).

It is guaranteed that the sum of the values of $ n $ for all input data sets does not exceed $ 2\cdot 10^5 $ . Similarly, it is guaranteed that the sum of the values of $ D $ for all input data sets does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of minutes after which each schoolchild will receive porridge at least once. If this does not happen within the break time, output $ -1 $ .

## 样例 #1

### 输入

```
7
3 3
2 2
3 1
2 3
5 10
10 3
7 1
11 3
5 1
6 1
5 20
4 2
7 2
8 5
1 5
3 1
5 17
1 3
8 2
8 3
2 2
1 1
5 14
8 2
4 2
1 3
8 3
6 4
1 11
4 5
5 14
8 2
4 2
1 3
8 3
6 4
```

### 输出

```
3
-1
12
6
6
1
6
```

