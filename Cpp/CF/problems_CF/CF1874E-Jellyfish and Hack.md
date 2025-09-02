---
title: "Jellyfish and Hack"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1874E
tag: []
---

# Jellyfish and Hack

## 题目描述

It is well known that quick sort works by randomly selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. But Jellyfish thinks that choosing a random element is just a waste of time, so she always chooses the first element to be the pivot. The time her code needs to run can be calculated by the following pseudocode:

```
<pre class="verbatim"><br></br>function fun(A)<br></br>    if A.length > 0<br></br>        let L[1 ... L.length] and R[1 ... R.length] be new arrays<br></br>        L.length = R.length = 0<br></br>        for i = 2 to A.length<br></br>            if A[i] < A[1]<br></br>                L.length = L.length + 1<br></br>                L[L.length] = A[i]<br></br>            else<br></br>                R.length = R.length + 1<br></br>                R[R.length] = A[i]<br></br>        return A.length + fun(L) + fun(R)<br></br>    else<br></br>        return 0<br></br>
```

Now you want to show her that her code is slow. When the function $ \mathrm{fun(A)} $ is greater than or equal to $ lim $ , her code will get $ \text{Time Limit Exceeded} $ . You want to know how many distinct permutations $ P $ of $ [1, 2, \dots, n] $ satisfies $ \mathrm{fun(P)} \geq lim $ . Because the answer may be large, you will only need to find the answer modulo $ 10^9+7 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ lim $ ( $ 1 \leq n \leq 200 $ , $ 1 \leq lim \leq 10^9 $ ).

## 输出格式

Output the number of different permutations that satisfy the condition modulo $ 10^9+7 $ .

## 说明/提示

In the first example, $ P = [1, 4, 2, 3] $ satisfies the condition, because: $ \mathrm{fun(4, [1, 4, 2, 3]) = 4 + fun(3, [4, 2, 3]) = 7 + fun(2, [2, 3]) = 9 + fun(1, [3]) = 10} $

Do remember to output the answer modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4 10
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8 32
```

### 输出

```
1280
```

