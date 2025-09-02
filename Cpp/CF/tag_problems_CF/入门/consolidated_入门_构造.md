---
title: "Little C Loves 3 I"
layout: "post"
diff: 入门
pid: CF1047A
tag: ['构造']
---

# Little C Loves 3 I

## 题目描述

**题目大意：**
找三个数$a,b,c$，使得$a+b+c==n$且$a,b,c$都不能被$3$整除

## 输入格式

一行一个正整数$n$

## 输出格式

三个正整数$a,b,c$，输出任意一组即可

## 样例 #1

### 输入

```
3

```

### 输出

```
1 1 1
```

## 样例 #2

### 输入

```
233
```

### 输出

```
77 77 79

```



---

---
title: "Bad Boy"
layout: "post"
diff: 入门
pid: CF1537B
tag: ['贪心', '构造']
---

# Bad Boy

## 题目描述

Riley is a very bad boy, but at the same time, he is a yo-yo master. So, he decided to use his yo-yo skills to annoy his friend Anton.

Anton's room can be represented as a grid with $ n $ rows and $ m $ columns. Let $ (i, j) $ denote the cell in row $ i $ and column $ j $ . Anton is currently standing at position $ (i, j) $ in his room. To annoy Anton, Riley decided to throw exactly two yo-yos in cells of the room (they can be in the same cell).

Because Anton doesn't like yo-yos thrown on the floor, he has to pick up both of them and return back to the initial position. The distance travelled by Anton is the shortest path that goes through the positions of both yo-yos and returns back to $ (i, j) $ by travelling only to adjacent by side cells. That is, if he is in cell $ (x, y) $ then he can travel to the cells $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ and $ (x, y - 1) $ in one step (if a cell with those coordinates exists).

Riley is wondering where he should throw these two yo-yos so that the distance travelled by Anton is maximized. But because he is very busy, he asked you to tell him.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The only line of each test case contains four integers $ n $ , $ m $ , $ i $ , $ j $ ( $ 1 \leq n, m \leq 10^9 $ , $ 1\le i\le n $ , $ 1\le j\le m $ ) — the dimensions of the room, and the cell at which Anton is currently standing.

## 输出格式

For each test case, print four integers $ x_1 $ , $ y_1 $ , $ x_2 $ , $ y_2 $ ( $ 1 \leq x_1, x_2 \leq n $ , $ 1\le y_1, y_2\le m $ ) — the coordinates of where the two yo-yos should be thrown. They will be thrown at coordinates $ (x_1,y_1) $ and $ (x_2,y_2) $ .

If there are multiple answers, you may print any.

## 说明/提示

Here is a visualization of the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1537B/55dd7a7a8828547b72bc3be325a8a8e51cf757fa.png)

## 样例 #1

### 输入

```
7
2 3 1 1
4 4 1 2
3 5 2 2
5 1 2 1
3 1 3 1
1 1 1 1
1000000000 1000000000 1000000000 50
```

### 输出

```
1 2 2 3
4 1 4 4
3 1 1 5
5 1 1 1
1 1 2 1
1 1 1 1
50 1 1 1000000000
```



---

---
title: "Hayato and School"
layout: "post"
diff: 入门
pid: CF1780A
tag: ['构造']
---

# Hayato and School

## 题目描述

Today Hayato came home from school with homework.

In the assignment, Hayato was given an array $ a $ of length $ n $ . The task was to find $ 3 $ numbers in this array whose sum is odd. At school, he claimed that there are such $ 3 $ numbers, but Hayato was not sure, so he asked you for help.

Answer if there are such three numbers, and if so, output indices $ i $ , $ j $ , and $ k $ such that $ a_i + a_j + a_k $ is odd.

The odd numbers are integers that are not divisible by $ 2 $ : $ 1 $ , $ 3 $ , $ 5 $ , and so on.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

For each test case, the first line contains one integer $ n $ ( $ 3 \le n \le 300 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, in the first line print one word "YES" (without quotes) if there are $ 3 $ numbers with an odd sum or "NO" (without quotes) if there are no such $ 3 $ numbers.

If the answer exists, then on the second line print $ 3 $ distinct integers $ i, j, k $ ( $ 1 \le i, j, k \le n $ ) — the indices of the numbers. If there are several answers, output any.

## 说明/提示

In the first test case, there is one way to choose $ 3 $ numbers, and since $ 1 + 1 + 1 = 3 $ , this triple is fine for us.

In the second test case, you need to choose the numbers $ 1, 2, 2 $ , since $ 1 + 2 + 2 = 5 $ .

In the third test case, there is one way to choose three numbers, but $ 1 + 2 + 3 = 6 $ is an even number, so the required triple does not exist.

In the fifth test case, no matter what three numbers we choose, their sum is even.

## 样例 #1

### 输入

```
6
3
1 1 1
4
1 1 2 2
3
1 2 3
5
1 4 5 1 2
4
2 6 2 4
5
5 6 3 2 1
```

### 输出

```
YES
1 2 3
YES
3 4 1
NO
YES
1 3 4
NO
YES
1 3 5
```



---

---
title: "Preparing for the Contest"
layout: "post"
diff: 入门
pid: CF1914B
tag: ['构造']
---

# Preparing for the Contest

## 题目描述

Monocarp is practicing for a big contest. He plans to solve $ n $ problems to make sure he's prepared. Each of these problems has a difficulty level: the first problem has a difficulty level of $ 1 $ , the second problem has a difficulty level of $ 2 $ , and so on, until the last ( $ n $ -th) problem, which has a difficulty level of $ n $ .

Monocarp will choose some order in which he is going to solve all $ n $ problems. Whenever he solves a problem which is more difficult than the last problem he solved, he gets excited because he feels like he's progressing. He doesn't get excited when he solves the first problem in his chosen order.

For example, if Monocarp solves the problems in the order $ [3, \underline{5}, 4, 1, \underline{6}, 2] $ , he gets excited twice (the corresponding problems are underlined).

Monocarp wants to get excited exactly $ k $ times during his practicing session. Help him to choose the order in which he has to solve the problems!

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 50 $ ; $ 0 \le k \le n - 1 $ ).

## 输出格式

For each test case, print $ n $ distinct integers from $ 1 $ to $ n $ , denoting the order in which Monocarp should solve the problems. If there are multiple answers, print any of them.

It can be shown that under the constraints of the problem, the answer always exists.

## 样例 #1

### 输入

```
3
6 2
5 4
5 0
```

### 输出

```
3 5 4 1 6 2
1 2 3 4 5
5 4 3 2 1
```



---

---
title: "Shrink"
layout: "post"
diff: 入门
pid: CF2117B
tag: ['贪心', '构造']
---

# Shrink

## 题目描述

对一个大小为 $ m $ 的数组 $ a $ 进行“缩小操作”的定义如下：

- 选择一个索引 $ i $（$ 2 \le i \le m - 1 $），使得 $ a_i \gt a_{i - 1} $ 且 $ a_i \gt a_{i + 1} $。
- 将 $ a_i $ 从数组中移除。

定义一个排列 $ ^{\text{∗}} $ $ p $ 的“分数”为可以对 $ p $ 执行的最大缩小操作次数。

鸭鸭给你一个整数 $ n $。构造一个长度为 $ n $ 的排列 $ p $，使其分数尽可能大。如果有多个答案，输出任意一个即可。

$ ^{\text{∗}} $ 一个长度为 $ n $ 的排列是指由 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数按任意顺序组成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（因为 $ 2 $ 出现了两次），$ [1,3,4] $ 也不是排列（因为 $ n=3 $ 但数组中出现了 $ 4 $）。

## 输入格式

输入的第一行包含一个整数 $ t $（$ 1 \le t \le 10^3 $）——测试用例的数量。

每个测试用例包含一个整数 $ n $（$ 3 \le n \le 2 \cdot 10^5 $）——排列的大小。

保证所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出任意一个能够最大化缩小操作次数的排列 $ p_1, p_2, \dots, p_n $。

## 说明/提示

在第一个测试用例中：

- 我们选择 $ p = [1, 3, 2] $。
- 选择索引 $ 2 $，并移除 $ p_2 $。数组变为 $ p = [1, 2] $。

可以证明，我们能执行的最大操作次数是 $ 1 $。另一个有效答案是 $ p = [2, 3, 1] $。

在第二个测试用例中：

- 我们选择 $ p = [2, 3, 6, 4, 5, 1] $。
- 选择索引 $ 5 $，并移除 $ p_5 $。数组变为 $ p = [2, 3, 6, 4, 1] $。
- 选择索引 $ 3 $，并移除 $ p_3 $。数组变为 $ p = [2, 3, 4, 1] $。
- 选择索引 $ 3 $，并移除 $ p_3 $。数组变为 $ p = [2, 3, 1] $。
- 选择索引 $ 2 $，并移除 $ p_2 $。数组变为 $ p = [2, 1] $。

我们能执行的最大操作次数是 $ 4 $。任何分数为 $ 4 $ 的排列都是有效的。

## 样例 #1

### 输入

```
2
3
6
```

### 输出

```
1 3 2
2 3 6 4 5 1
```



---

