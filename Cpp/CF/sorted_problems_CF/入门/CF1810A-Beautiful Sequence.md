---
title: "Beautiful Sequence"
layout: "post"
diff: 入门
pid: CF1810A
tag: []
---

# Beautiful Sequence

## 题目描述

A sequence of $ m $ integers $ a_{1}, a_{2}, \ldots, a_{m} $ is good, if and only if there exists at least one $ i $ ( $ 1 \le i \le m $ ) such that $ a_{i} = i $ . For example, $ [3,2,3] $ is a good sequence, since $ a_{2} = 2 $ , $ a_{3} = 3 $ , while $ [3,1,1] $ is not a good sequence, since there is no $ i $ such that $ a_{i} = i $ .

A sequence $ a $ is beautiful, if and only if there exists at least one subsequence of $ a $ satisfying that this subsequence is good. For example, $ [4,3,2] $ is a beautiful sequence, since its subsequence $ [4,2] $ is good, while $ [5,3,4] $ is not a beautiful sequence.

A sequence $ b $ is a subsequence of a sequence $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements.

Now you are given a sequence, check whether it is beautiful or not.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. Their description follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the given sequence.

The second line of each test case contains $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ ( $ 1 \le a_{i} \le 10^9 $ ), representing the sequence.

## 输出格式

For each test case, output "YES" or "NO"(without quotes) in one line, representing whether the given sequence is beautiful.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, the good subsequence is $ b=[3,2] $ , where $ b_{2} = 2 $ .

In the second test case, the good subsequence is $ b=[2,4,3] $ , where $ b_{3} = 3 $ .

In the fourth test case, the good subsequence is $ b=[1] $ , where $ b_{1} = 1 $ .

In the fifth test case, the good subsequence is $ b=[2,2] $ , where $ b_{2} = 2 $ .

## 样例 #1

### 输入

```
7
3
3 2 1
4
2 4 3 5
5
2 3 5 5 6
2
3 1
5
2 4 5 2 3
4
5 6 7 8
6
6 5 4 3 2 1
```

### 输出

```
YES
YES
NO
YES
YES
NO
YES
```

