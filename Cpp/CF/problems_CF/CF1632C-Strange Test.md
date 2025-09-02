---
title: "Strange Test"
layout: "post"
diff: 普及/提高-
pid: CF1632C
tag: []
---

# Strange Test

## 题目描述

Igor is in 11th grade. Tomorrow he will have to write an informatics test by the strictest teacher in the school, Pavel Denisovich.

Igor knows how the test will be conducted: first of all, the teacher will give each student two positive integers $ a $ and $ b $ ( $ a < b $ ). After that, the student can apply any of the following operations any number of times:

- $ a := a + 1 $ (increase $ a $ by $ 1 $ ),
- $ b := b + 1 $ (increase $ b $ by $ 1 $ ),
- $ a := a \ | \ b $ (replace $ a $ with the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of $ a $ and $ b $ ).

To get full marks on the test, the student has to tell the teacher the minimum required number of operations to make $ a $ and $ b $ equal.

Igor already knows which numbers the teacher will give him. Help him figure out what is the minimum number of operations needed to make $ a $ equal to $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The only line for each test case contains two integers $ a $ and $ b $ ( $ 1 \le a < b \le 10^6 $ ).

It is guaranteed that the sum of $ b $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case print one integer — the minimum required number of operations to make $ a $ and $ b $ equal.

## 说明/提示

In the first test case, it is optimal to apply the third operation.

In the second test case, it is optimal to apply the first operation three times.

In the third test case, it is optimal to apply the second operation and then the third operation.

## 样例 #1

### 输入

```
5
1 3
5 8
2 5
3 19
56678 164422
```

### 输出

```
1
3
2
1
23329
```

