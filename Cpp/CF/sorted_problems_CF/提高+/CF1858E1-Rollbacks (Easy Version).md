---
title: "Rollbacks (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1858E1
tag: ['可持久化线段树']
---

# Rollbacks (Easy Version)

## 题目描述

This is an easy version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 输入格式

The first line contains an integer $ q $ ( $ 1 \leq q \leq 10^6 $ ) — the number of queries.

The next $ q $ lines contain the queries as described above.

It is guaranteed that

- in the queries of the first type, $ 1 \le x \le 10^6 $ ;
- in the queries of the second type, $ k \ge 1 $ and $ k $ does not exceed the current length of the array $ a $ ;
- at the moment of the queries of the third type, there is at least one query of the first or of the second type that can be rolled back.

It is also guaranteed that the number of queries of the fourth type (?) does not exceed $ 10^5 $ .

## 输出格式

For each query of the fourth type output one integer — the number of distinct elements in array $ a $ at the moment of query.

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?
```

### 输出

```
2
1
1
```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?
```

### 输出

```
2
0
```

