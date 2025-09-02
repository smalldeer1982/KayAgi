---
title: "Boris and His Amazing Haircut"
layout: "post"
diff: 普及+/提高
pid: CF1779D
tag: []
---

# Boris and His Amazing Haircut

## 题目描述

Boris thinks that chess is a tedious game. So he left his tournament early and went to a barber shop as his hair was a bit messy.

His current hair can be described by an array $ a_1,a_2,\ldots, a_n $ , where $ a_i $ is the height of the hair standing at position $ i $ . His desired haircut can be described by an array $ b_1,b_2,\ldots, b_n $ in a similar fashion.

The barber has $ m $ razors. Each has its own size and can be used at most once. In one operation, he chooses a razor and cuts a segment of Boris's hair. More formally, an operation is:

- Choose any razor which hasn't been used before, let its size be $ x $ ;
- Choose a segment $ [l,r] $ ( $ 1\leq l \leq r \leq n $ );
- Set $ a_i := \min (a_i,x) $ for each $ l\leq i \leq r $ ;

Notice that some razors might have equal sizes — the barber can choose some size $ x $ only as many times as the number of razors with size $ x $ .

He may perform as many operations as he wants, as long as any razor is used at most once and $ a_i = b_i $ for each $ 1 \leq i \leq n $ at the end. He does not have to use all razors.

Can you determine whether the barber can give Boris his desired haircut?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 20\,000 $ ). The description of the test cases follows.

The first line of each test case contains a positive integer $ n $ ( $ 3\leq n\leq 2\cdot 10^5 $ ) — the length of arrays $ a $ and $ b $ .

The second line of each test case contains $ n $ positive integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — Boris's current hair.

The third line of each test case contains $ n $ positive integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 10^9 $ ) — Boris's desired hair.

The fourth line of each test case contains a positive integer $ m $ ( $ 1 \leq m \leq 2\cdot 10^5 $ ) — the number of razors.

The fifth line of each test case contains $ m $ positive integers $ x_1,x_2, \ldots, x_m $ ( $ 1 \leq x_i \leq 10^9 $ ) — the sizes of the razors.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print "YES" if the barber can cut Boris's hair as desired. Otherwise, print "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, Boris's hair is initially $ [3,3,3] $ . Let us describe a sequence of $ 2 $ operations the barber can perform:

- The barber uses the razor with size $ 1 $ on the segment $ [2,2] $ ; hence Boris's hair becomes $ [3,1,3] $ .
- The barber uses the razor with size $ 2 $ on the segment $ [1,3] $ ; hence Boris's hair becomes $ [2,1,2] $ which is the desired haircut.

In the third test case, no operation has to be done since Boris's hair is already as desired.

In the fourth test case, no cuts will be able to increase the third element in $ [1,1,1] $ in a way that the array becomes $ [1,1,2] $ .

## 样例 #1

### 输入

```
7
3
3 3 3
2 1 2
2
1 2
6
3 4 4 6 3 4
3 1 2 3 2 3
3
3 2 3
10
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
10
1 2 3 4 5 6 7 8 9 10
3
1 1 1
1 1 2
12
4 2 4 3 1 5 6 3 5 6 2 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
8
1 5 3 5 4 2 3 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
7
1 5 3 4 2 3 1
3
19747843 2736467 938578397
2039844 2039844 2039844
1
2039844
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
```

