---
title: "Go Learn! (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G1
tag: ['动态规划 DP', '二分']
---

# Go Learn! (Easy Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3000 $ and the sum of $ n $ does not exceed $ 10^4 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3000 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
2
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
```

### 输出

```
3 78
3 839271911
```

