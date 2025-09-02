---
title: "Gardener and the Array"
layout: "post"
diff: 普及/提高-
pid: CF1775B
tag: ['位运算', '构造']
---

# Gardener and the Array

## 题目描述

The gardener Kazimir Kazimirovich has an array of $ n $ integers $ c_1, c_2, \dots, c_n $ .

He wants to check if there are two different subsequences $ a $ and $ b $ of the original array, for which $ f(a) = f(b) $ , where $ f(x) $ is the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all of the numbers in the sequence $ x $ .

A sequence $ q $ is a subsequence of $ p $ if $ q $ can be obtained from $ p $ by deleting several (possibly none or all) elements.

Two subsequences are considered different if the sets of indexes of their elements in the original sequence are different, that is, the values of the elements are not considered when comparing the subsequences.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775B/01e7b88f6704ebb4d7f093f81e886f156c238509.png)

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array $ c $ .

The description of the array $ c $ in this problem is given implicitly to speed up input.

The $ (i + 1) $ -st of the following $ n $ lines of the test case begins with an integer $ k_i $ ( $ 1 \le k_i \le 10^5 $ ) — the number of set bits in the number $ c_i $ . Next follow $ k_i $ distinct integers $ p_{i, 1}, p_{i, 2}, \dots, p_{i, k_i} $ ( $ 1 \le p_i \le 2 \cdot 10^5 $ ) —the numbers of bits that are set to one in number $ c_i $ . In other words, $ c_i = 2^{p_{i, 1}} + 2^{p_{i, 2}} + \ldots + 2^{p_{i, k_i}} $ .

It is guaranteed that the total sum of $ k_i $ in all tests does not exceed $ 10^5 $ .

## 输出格式

For each set of input, print "Yes" if there exist two different subsequences for which $ f(a) = f(b) $ , and "No" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

It can be proven that in the first test case there are no two different subsequences $ a $ and $ b $ for which $ f(a) = f(b) $ .

In the second test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by the element at position $ 1 $ , and the subsequence $ b $ formed by the elements at positions $ 1 $ and $ 2 $ .

In the third test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by elements at positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , and the subsequence $ b $ formed by elements at positions $ 2 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2
```

### 输出

```
No
Yes
Yes
Yes
No
```

