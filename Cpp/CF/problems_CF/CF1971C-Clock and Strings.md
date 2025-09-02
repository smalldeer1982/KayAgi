---
title: "Clock and Strings"
layout: "post"
diff: 普及-
pid: CF1971C
tag: ['枚举']
---

# Clock and Strings

## 题目描述

There is a clock labeled with the numbers $ 1 $ through $ 12 $ in clockwise order, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)In this example, $ (a,b,c,d)=(2,9,10,6) $ , and the strings intersect.

Alice and Bob have four distinct integers $ a $ , $ b $ , $ c $ , $ d $ not more than $ 12 $ . Alice ties a red string connecting $ a $ and $ b $ , and Bob ties a blue string connecting $ c $ and $ d $ . Do the strings intersect? (The strings are straight line segments.)

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5940 $ ) — the number of test cases.

The only line of each test case contains four distinct integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 1 \leq a, b, c, d \leq 12 $ ).

## 输出格式

For each test case, output "YES" (without quotes) if the strings intersect, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the strings do not intersect, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

## 样例 #1

### 输入

```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5
```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES
```

