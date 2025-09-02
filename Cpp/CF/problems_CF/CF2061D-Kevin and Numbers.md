---
title: "Kevin and Numbers"
layout: "post"
diff: 普及/提高-
pid: CF2061D
tag: []
---

# Kevin and Numbers

## 题目描述

Kevin wrote an integer sequence $ a $ of length $ n $ on the blackboard.

Kevin can perform the following operation any number of times:

- Select two integers $ x, y $ on the blackboard such that $ |x - y| \leq 1 $ , erase them, and then write down an integer $ x + y $ instead.

Kevin wants to know if it is possible to transform these integers into an integer sequence $ b $ of length $ m $ through some sequence of operations.

Two sequences $ a $ and $ b $ are considered the same if and only if their multisets are identical. In other words, for any number $ x $ , the number of times it appears in $ a $ must be equal to the number of times it appears in $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\leq m \leq n \leq 2\cdot 10^5 $ ) — the length of $ a $ and the length of $ b $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1\leq a_i \leq 10^9 $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1\leq b_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output "Yes" if it is possible to transform $ a $ into $ b $ , and "No" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, you can erase $ 4, 5 $ , and write down $ 9 $ .

In the second test case, you can't erase $ 3, 6 $ .

In the third test case, one possible way could be:

- Erase $ 2, 2 $ , and write down $ 4 $ . The remaining numbers are $ 1, 2, 4 $ now.
- Erase $ 1, 2 $ , and write down $ 3 $ . The remaining numbers are $ 3, 4 $ now.

In the fourth test case, one possible way could be:

- Erase $ 1, 1 $ , and write down $ 2 $ . The remaining numbers are $ 2, 3, 3 $ now.
- Erase $ 2, 3 $ , and write down $ 5 $ . The remaining numbers are $ 3, 5 $ now.

## 样例 #1

### 输入

```
9
2 1
4 5
9
2 1
3 6
9
4 2
1 2 2 2
3 4
4 2
1 1 3 3
3 5
4 2
1 2 3 4
3 5
5 5
1 2 3 4 5
5 4 3 2 1
4 2
1 1 1 1
1 1
4 4
1 1 1 1
1 1 1 2
1 1
1
1000000000
```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
No
```

