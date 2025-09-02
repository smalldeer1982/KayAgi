---
title: "Selection Sort"
layout: "post"
diff: 普及+/提高
pid: CF2041M
tag: ['贪心', '优先队列']
---

# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 输入格式

The first line contains exactly one integer $ n $ which indicates the number of integers in the array $ s $ . The second line contains the $ n $ integers in $ s=[s_0, s_1, \ldots, s_{n-1}] $ .

- $ 1 \le n \le 10^6 $
- For all $ i $ ( $ 0\le i < n $ ), $ 0\le s_i < 2^{31}-1 $ .

## 输出格式

Output an integer on a line, indicating the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

## 样例 #1

### 输入

```
6
3 2 5 5 4 1
```

### 输出

```
25
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
16
```



---

---
title: "George and Job"
layout: "post"
diff: 普及+/提高
pid: CF467C
tag: ['动态规划 DP', '优先队列', '前缀和']
---

# George and Job

## 题目描述

新款手机 iTone6 近期上市，George 很想买一只。不幸地，George 没有足够的钱，所以 George 打算当一名程序猿去打工。现在George遇到了一个问题。
给出一组有 $n$ 个整数的数列 $p_1,p_2,...,p_n$ ,你需要挑出 $k$ 组长度为 $m$ 的数，要求这些数互不重叠
即$ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{k},r_{k}] (1<=l_{1}<=r_{1}<l_{2}<=r_{2}<...<l_{k}<=r_{k}<=n; r_{i}-l_{i}+1=m)$
使选出的数的和值最大，请你帮助George码出这份代码

## 输入格式

第1行读入3个整数 $n , m , k(1\leq(m×k)\leq n\leq5000) (1\leq(m×k)\leq n\leq5000)$,
第2行读入 $n$ 个数 $p_1,p_2,...,p_n$

## 输出格式

输出1个整数，代表可以取到的最大值
# 输入输出样例
如原版
translated by @Venus

## 样例 #1

### 输入

```
5 2 1
1 2 3 4 5

```

### 输出

```
9

```

## 样例 #2

### 输入

```
7 1 3
2 10 7 18 5 33 0

```

### 输出

```
61

```



---

---
title: "Crunching Numbers Just for You"
layout: "post"
diff: 普及+/提高
pid: CF784F
tag: ['排序', '优先队列', '队列']
---

# Crunching Numbers Just for You

## 题目描述

你正在为销售机票的网站开发一项新功能：按能够对价格进行票分类照片你已经提取了票价，所以只有最后一步要做...

## 输出格式

记住，这是一个非常重要的功能，你必须确保顾客欣赏它！

Translated by @zhrzhrzhr

## 样例 #1

### 输入

```
3 3 1 2

```

### 输出

```
1 2 3 

```



---

---
title: "Segments Removal"
layout: "post"
diff: 普及+/提高
pid: CF899E
tag: ['线段树', '优先队列', '队列']
---

# Segments Removal

## 题目描述

Vasya has an array of integers of length $ n $ .

Vasya performs the following operations on the array: on each step he finds the longest segment of consecutive equal integers (the leftmost, if there are several such segments) and removes it. For example, if Vasya's array is $ [13,13,7,7,7,2,2,2] $ , then after one operation it becomes $ [13,13,2,2,2] $ .

Compute the number of operations Vasya should make until the array becomes empty, i.e. Vasya removes all elements from it.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the array.

The second line contains a sequence $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — Vasya's array.

## 输出格式

Print the number of operations Vasya should make to remove all elements from the array.

## 说明/提示

In the first example, at first Vasya removes two fives at the second and third positions. The array becomes $ [2,2] $ . In the second operation Vasya removes two twos at the first and second positions. After that the array becomes empty.

In the second example Vasya has to perform five operations to make the array empty. In each of them he removes the first element from the array.

In the third example Vasya needs three operations. In the first operation he removes all integers $ 4 $ , in the second — all integers $ 100 $ , in the third — all integers $ 2 $ .

In the fourth example in the first operation Vasya removes the first two integers $ 10 $ . After that the array becomes $ [50,10,50,50] $ . Then in the second operation Vasya removes the two rightmost integers $ 50 $ , so that the array becomes $ [50,10] $ . In the third operation he removes the remaining $ 50 $ , and the array becomes $ [10] $ after that. In the last, fourth operation he removes the only remaining $ 10 $ . The array is empty after that.

## 样例 #1

### 输入

```
4
2 5 5 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
6 3 4 1 5

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8
4 4 4 2 2 100 100 100

```

### 输出

```
3

```

## 样例 #4

### 输入

```
6
10 10 50 10 50 50

```

### 输出

```
4

```



---

