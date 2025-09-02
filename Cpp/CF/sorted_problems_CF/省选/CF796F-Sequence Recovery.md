---
title: "Sequence Recovery"
layout: "post"
diff: 省选/NOI-
pid: CF796F
tag: []
---

# Sequence Recovery

## 题目描述

Zane once had a good sequence $ a $ consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ — but he has lost it.

A sequence is said to be good if and only if all of its integers are non-negative and do not exceed $ 10^{9} $ in value.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796F/7c34d2981d5a0342e098e7b1d14d4ca5448e48f2.png)However, Zane remembers having played around with his sequence by applying $ m $ operations to it.

There are two types of operations:

1\. Find the maximum value of integers with indices $ i $ such that $ l<=i<=r $ , given $ l $ and $ r $ .

2\. Assign $ d $ as the value of the integer with index $ k $ , given $ k $ and $ d $ .

After he finished playing, he restored his sequence to the state it was before any operations were applied. That is, sequence $ a $ was no longer affected by the applied type 2 operations. Then, he lost his sequence at some time between now and then.

Fortunately, Zane remembers all the operations and the order he applied them to his sequence, along with the distinct results of all type 1 operations. Moreover, among all good sequences that would produce the same results when the same operations are applied in the same order, he knows that his sequence $ a $ has the greatest cuteness.

We define cuteness of a sequence as the bitwise OR result of all integers in such sequence. For example, the cuteness of Zane's sequence $ a $ is $ a_{1} $ OR $ a_{2} $ OR ... OR $ a_{n} $ .

Zane understands that it might not be possible to recover exactly the lost sequence given his information, so he would be happy to get any good sequence $ b $ consisting of $ n $ integers $ b_{1},b_{2},...,b_{n} $ that:

1\. would give the same results when the same operations are applied in the same order, and

2\. has the same cuteness as that of Zane's original sequence $ a $ .

If there is such a sequence, find it. Otherwise, it means that Zane must have remembered something incorrectly, which is possible.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of integers in Zane's original sequence and the number of operations that have been applied to the sequence, respectively.

The $ i $ -th of the following $ m $ lines starts with one integer $ t_{i} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796F/2b47eb89ee7b6063f7a48e9fc1ad20b107383eb0.png)) — the type of the $ i $ -th operation.

If the operation is type 1 ( $ t_{i}=1 $ ), then three integers $ l_{i} $ , $ r_{i} $ , and $ x_{i} $ follow ( $ 1<=l_{i}<=r_{i}<=n $ , $ 0<=x_{i}<=10^{9} $ ) — the leftmost index to be considered, the rightmost index to be considered, and the maximum value of all integers with indices between $ l_{i} $ and $ r_{i} $ , inclusive, respectively.

If the operation is type 2 ( $ t_{i}=2 $ ), then two integers $ k_{i} $ and $ d_{i} $ follow ( $ 1<=k_{i}<=n $ , $ 0<=d_{i}<=10^{9} $ ) — meaning that the integer with index $ k_{i} $ should become $ d_{i} $ after this operation.

It is guaranteed that $ x_{i}≠x_{j} $ for all pairs $ (i,j) $ where $ 1<=i&lt;j<=m $ and $ t_{i}=t_{j}=1 $ .

The operations are given in the same order they were applied. That is, the operation that is given first was applied first, the operation that is given second was applied second, and so on.

## 输出格式

If there does not exist a valid good sequence, print "NO" (without quotation marks) in the first line.

Otherwise, print "YES" (without quotation marks) in the first line, and print $ n $ space-separated integers $ b_{1},b_{2},...,b_{n} $ ( $ 0<=b_{i}<=10^{9} $ ) in the second line.

If there are multiple answers, print any of them.

## 说明/提示

In the first sample, it is easy to verify that this good sequence is valid. In particular, its cuteness is $ 19 $ OR $ 0 $ OR $ 0 $ OR $ 0 $ OR $ 1 $ $ = $ $ 19 $ .

In the second sample, the two operations clearly contradict, so there is no such good sequence.

## 样例 #1

### 输入

```
5 4
1 1 5 19
1 2 5 1
2 5 100
1 1 5 100

```

### 输出

```
YES
19 0 0 0 1

```

## 样例 #2

### 输入

```
5 2
1 1 5 0
1 1 5 100

```

### 输出

```
NO
```

