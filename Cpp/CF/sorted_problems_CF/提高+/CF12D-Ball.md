---
title: "Ball"
layout: "post"
diff: 提高+/省选-
pid: CF12D
tag: ['树状数组', '排序']
---

# Ball

## 题目描述

 $ N $ ladies attend the ball in the King's palace. Every lady can be described with three values: beauty, intellect and richness. King's Master of Ceremonies knows that ladies are very special creatures. If some lady understands that there is other lady at the ball which is more beautiful, smarter and more rich, she can jump out of the window. He knows values of all ladies and wants to find out how many probable self-murderers will be on the ball. Lets denote beauty of the $ i $ -th lady by $ B_{i} $ , her intellect by $ I_{i} $ and her richness by $ R_{i} $ . Then $ i $ -th lady is a probable self-murderer if there is some $ j $ -th lady that $ B_{i}<B_{j},I_{i}<I_{j},R_{i}<R_{j} $ . Find the number of probable self-murderers.

## 输入格式

The first line contains one integer $ N $ ( $ 1<=N<=500000 $ ). The second line contains $ N $ integer numbers $ B_{i} $ , separated by single spaces. The third and the fourth lines contain sequences $ I_{i} $ and $ R_{i} $ in the same format. It is guaranteed that $ 0<=B_{i},I_{i},R_{i}<=10^{9} $ .

## 输出格式

Output the answer to the problem.

## 样例 #1

### 输入

```
3
1 4 2
4 3 2
2 5 3

```

### 输出

```
1

```

