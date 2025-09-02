---
title: "Creating a Schedule"
layout: "post"
diff: 难度0
pid: CF2111D
tag: []
---

# Creating a Schedule

## 题目描述

A new semester is about to begin, and it is necessary to create a schedule for the first day. There are a total of $ n $ groups and $ m $ classrooms in the faculty. It is also known that each group has exactly $ 6 $ classes on the first day, and the $ k $ -th class of each group takes place at the same time. Each class must be held in a classroom, and at the same time, there cannot be classes for more than one group in the same classroom.

Each classroom has its own index (at least three digits), and all digits of this index, except for the last two, indicate the floor on which the classroom is located. For example, classroom $ 479 $ is located on the $ 4 $ -th floor, while classroom $ 31415 $ is on the $ 314 $ -th floor. Between floors, one can move by stairs; for any floor $ x > 1 $ , one can either go down to floor $ x - 1 $ or go up to floor $ x + 1 $ ; from the first floor, one can only go up to the second; from the floor $ 10^7 $ (which is the last one), it is possible to go only to the floor $ 9999999 $ .

The faculty's dean's office has decided to create the schedule in such a way that students move as much as possible between floors, meaning that the total number of movements between floors across all groups should be maximized. When the students move from one floor to another floor, they take the shortest path.

For example, if there are $ n = 2 $ groups and $ m = 4 $ classrooms $ [479, 290, 478, 293] $ , the schedule can be arranged as follows:

 Class No.Group 1Group 2 $ 1 $  $ 290 $  $ 293 $  $ 2 $  $ 478 $  $ 479 $  $ 3 $  $ 293 $  $ 290 $  $ 4 $  $ 479 $  $ 478 $  $ 5 $  $ 293 $  $ 290 $  $ 6 $  $ 479 $  $ 478 $ In such a schedule, the groups will move between the $ 2 $ nd and $ 4 $ th floors each time, resulting in a total of $ 20 $ movements between floors.

Help the dean's office create any suitable schedule!

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^{3} $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le m \le 10^{5} $ ) — the number of groups and the number of available classrooms.

The second line of each test case contains $ m $ integers $ a_{i} $ ( $ 100 \le a_{i} < 10^{9} $ ) — the indices of the available classrooms.

Additional constraints on the input:

- the numbers of all classrooms are pairwise distinct;
- the sum of $ m $ across all test cases does not exceed $ 10^{5} $ .

## 输出格式

For each test case, output $ n $ lines, where the $ i $ -th line should contain $ 6 $ integers — the indices of the classrooms where the classes for the $ i $ -th group will be held.

Each classroom must be occupied by at most one group during the $ k $ -th class.

## 说明/提示

In the third test case, the maximum number of moves between classrooms is $ 50 $ .

## 样例 #1

### 输入

```
3
2 4
479 290 478 293
1 1
31415
6 10
479 385 290 293 384 383 297 478 291 382
```

### 输出

```
290 478 293 479 293 479
293 479 290 478 290 478
31415 31415 31415 31415 31415 31415
479 290 479 290 479 290
290 479 290 479 290 479
293 478 293 478 293 478
297 385 297 385 297 385
478 293 478 293 478 293
291 384 291 384 291 384
```

