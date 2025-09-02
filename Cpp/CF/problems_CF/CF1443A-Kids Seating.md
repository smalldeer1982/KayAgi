---
title: "Kids Seating"
layout: "post"
diff: 普及-
pid: CF1443A
tag: []
---

# Kids Seating

## 题目描述

Today the kindergarten has a new group of $ n $ kids who need to be seated at the dinner table. The chairs at the table are numbered from $ 1 $ to $ 4n $ . Two kids can't sit on the same chair. It is known that two kids who sit on chairs with numbers $ a $ and $ b $ ( $ a \neq b $ ) will indulge if:

1. $ gcd(a, b) = 1 $ or,
2. $ a $ divides $ b $ or $ b $ divides $ a $ .

 $ gcd(a, b) $ — the maximum number $ x $ such that $ a $ is divisible by $ x $ and $ b $ is divisible by $ x $ .

For example, if $ n=3 $ and the kids sit on chairs with numbers $ 2 $ , $ 3 $ , $ 4 $ , then they will indulge since $ 4 $ is divided by $ 2 $ and $ gcd(2, 3) = 1 $ . If kids sit on chairs with numbers $ 4 $ , $ 6 $ , $ 10 $ , then they will not indulge.

The teacher really doesn't want the mess at the table, so she wants to seat the kids so there are no $ 2 $ of the kid that can indulge. More formally, she wants no pair of chairs $ a $ and $ b $ that the kids occupy to fulfill the condition above.

Since the teacher is very busy with the entertainment of the kids, she asked you to solve this problem.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case consists of one line containing an integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the number of kids.

## 输出格式

Output $ t $ lines, which contain $ n $ distinct integers from $ 1 $ to $ 4n $ — the numbers of chairs that the kids should occupy in the corresponding test case. If there are multiple answers, print any of them. You can print $ n $ numbers in any order.

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
6 4
4 6 10
14 10 12 8
```

