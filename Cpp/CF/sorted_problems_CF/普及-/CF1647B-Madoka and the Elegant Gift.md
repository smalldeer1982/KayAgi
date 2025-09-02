---
title: "Madoka and the Elegant Gift"
layout: "post"
diff: 普及-
pid: CF1647B
tag: []
---

# Madoka and the Elegant Gift

## 题目描述

Madoka's father just reached $ 1 $ million subscribers on Mathub! So the website decided to send him a personalized award — The Mathhub's Bit Button!

The Bit Button is a rectangular table with $ n $ rows and $ m $ columns with $ 0 $ or $ 1 $ in each cell. After exploring the table Madoka found out that:

- A subrectangle $ A $ is contained in a subrectangle $ B $ if there's no cell contained in $ A $ but not contained in $ B $ .
- Two subrectangles intersect if there is a cell contained in both of them.
- A subrectangle is called black if there's no cell with value $ 0 $ inside it.
- A subrectangle is called nice if it's black and it's not contained in another black subrectangle.
- The table is called elegant if there are no two nice intersecting subrectangles.

For example, in the first illustration the red subrectangle is nice, but in the second one it's not, because it's contained in the purple subrectangle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/527c997c3730172d58419587c380220df58d0b35.png)Help Madoka to determine whether the table is elegant.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 200 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two positive integers $ n, m $ ( $ 1 \le n, m \le 100 $ ).

The next $ n $ lines contain strings of length $ m $ consisting of zeros and ones — the description of the table.

It is guaranteed that the sum of the values of $ n $ and the sum of the values of $ m $ for all test cases do not exceed $ 777 $ .

## 输出格式

For each test case print "YES" if its table is elegant or print "NO" otherwise.

You may print each letter in any case (for example, "YES", "Yes", "yes", "yEs" will all be recognized as positive answer).

## 说明/提示

In the second test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/274bbf1f30d832fb82dd64034e57adcb4cd9b242.png)In the fourth test case the table is not elegant, because the red and the purple subrectangles are nice and intersect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647B/6dc815ec1b802f77b63db126c6131ed14481d644.png)

## 样例 #1

### 输入

```
5
3 3
100
011
011
3 3
110
111
110
1 5
01111
4 5
11111
01010
01000
01000
3 2
11
00
11
```

### 输出

```
YES
NO
YES
NO
YES
```

