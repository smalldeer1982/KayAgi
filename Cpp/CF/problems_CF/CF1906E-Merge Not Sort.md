---
title: "Merge Not Sort"
layout: "post"
diff: 普及+/提高
pid: CF1906E
tag: []
---

# Merge Not Sort

## 题目描述

You are currently researching the Merge Sort algorithm. Merge Sort is a sorting algorithm that is based on the principle of Divide and Conquer. It works by dividing an array into two subarrays of equal length, sorting each subarrays, then merging the sorted subarrays back together to form the final sorted array.

You are particularly interested in the merging routine. Common merge implementation will combine two subarrays by iteratively comparing their first elements, and move the smaller one to a new merged array. More precisely, the merge algorithm can be presented by the following pseudocode.

```
<pre class="verbatim"><br></br>    Merge(A[1..N], B[1..N]):<br></br>        C = []<br></br>        i = 1<br></br>        j = 1<br></br>        while i <= N AND j <= N:<br></br>            if A[i] < B[j]:<br></br>                append A[i] to C<br></br>                i = i + 1<br></br>            else:<br></br>                append B[j] to C<br></br>                j = j + 1 <br></br>        while i <= N:<br></br>            append A[i] to C<br></br>            i = i + 1 <br></br>        while j <= N:<br></br>            append B[j] to C<br></br>            j = j + 1 <br></br>        return C<br></br>
```

During your research, you are keen to understand the behaviour of the merge algorithm when arrays $ A $ and $ B $ are not necessarily sorted. For example, if $ A = [3, 1, 6] $ and $ B = [4, 5, 2] $ , then $ \text{Merge}(A, B) = [3, 1, 4, 5, 2, 6] $ .

To further increase the understanding of the merge algorithm, you decided to work on the following problem. You are given an array $ C $ of length $ 2 \cdot N $ such that it is a permutation of $ 1 $ to $ 2 \cdot N $ . Construct any two arrays $ A $ and $ B $ of the same length $ N $ , such that $ \text{Merge}(A, B) = C $ , or determine if it is impossible to do so.

## 输入格式

The first line consists of an integer $ N $ ( $ 1 \leq N \leq 1000 $ ).

The following line consists of $ 2 \cdot N $ integers $ C_i $ . The array $ C $ is a permutation of $ 1 $ to $ 2 \cdot N $ .

## 输出格式

If it is impossible to construct two arrays $ A $ and $ B $ of length $ N $ such that $ \text{Merge}(A, B) = C $ , then output -1.

Otherwise, output the arrays $ A $ and $ B $ in two lines. The first line consists of $ N $ integers $ A_i $ . The second line consists of $ N $ integers $ B_i $ . If there are several possible answers, output any of them.

## 说明/提示

Explanation for the sample input/output #1

The solution $ A = [3, 1, 4] $ and $ B = [5, 2, 6] $ is also correct.

Explanation for the sample input/output #2

The solution $ A = [1, 2, 3, 4] $ and $ B = [5, 6, 7, 8] $ is also correct.

## 样例 #1

### 输入

```
3
3 1 4 5 2 6
```

### 输出

```
3 1 6
4 5 2
```

## 样例 #2

### 输入

```
4
1 2 3 4 5 6 7 8
```

### 输出

```
2 3 5 7
1 4 6 8
```

## 样例 #3

### 输入

```
2
4 3 2 1
```

### 输出

```
-1
```

