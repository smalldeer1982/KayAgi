# Serval and Mocha's Array

## 题目描述

Mocha likes arrays, and Serval gave her an array consisting of positive integers as a gift.

Mocha thinks that for an array of positive integers $ a $ , it is good iff the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all the elements in $ a $ is no more than its length. And for an array of at least $ 2 $ positive integers, it is beautiful iff all of its prefixes whose length is no less than $ 2 $ are good.

For example:

- $ [3,6] $ is not good, because $ \gcd(3,6)=3 $ is greater than its length $ 2 $ .
- $ [1,2,4] $ is both good and beautiful, because all of its prefixes whose length is no less than $ 2 $ , which are $ [1,2] $ and $ [1,2,4] $ , are both good.
- $ [3,6,1] $ is good but not beautiful, because $ [3,6] $ is not good.

Now Mocha gives you the gift array $ a $ of $ n $ positive integers, and she wants to know whether array $ a $ could become beautiful by reordering the elements in $ a $ . It is allowed to keep the array $ a $ unchanged.

## 说明/提示

In the first test case, neither $ [3,6] $ nor $ [6,3] $ are beautiful, so it's impossible to obtain a beautiful array by reordering the elements in $ a $ .

In the second test case, $ [1,2,4] $ is already beautiful. Keeping the array $ a $ unchanged can obtain a beautiful array.

## 样例 #1

### 输入

```
6
2
3 6
3
1 2 4
3
3 6 1
3
15 35 21
4
35 10 35 14
5
1261 227821 143 4171 1941```

### 输出

```
No
Yes
Yes
No
Yes
Yes```

