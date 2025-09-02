---
title: "Kuzya and Homework"
layout: "post"
diff: 提高+/省选-
pid: CF1582G
tag: ['单调队列', '素数判断,质数,筛法']
---

# Kuzya and Homework

## 题目描述

Kuzya started going to school. He was given math homework in which he was given an array $ a $ of length $ n $ and an array of symbols $ b $ of length $ n $ , consisting of symbols '\*' and '/'.

Let's denote a path of calculations for a segment $ [l; r] $ ( $ 1 \le l \le r \le n $ ) in the following way:

- Let $ x=1 $ initially. For every $ i $ from $ l $ to $ r $ we will consequently do the following: if $ b_i= $ '\*', $ x=x*a_i $ , and if $ b_i= $ '/', then $ x=\frac{x}{a_i} $ . Let's call a path of calculations for the segment $ [l; r] $ a list of all $ x $ that we got during the calculations (the number of them is exactly $ r - l + 1 $ ).

For example, let $ a=[7, $ $ 12, $ $ 3, $ $ 5, $ $ 4, $ $ 10, $ $ 9] $ , $ b=[/, $ $ *, $ $ /, $ $ /, $ $ /, $ $ *, $ $ *] $ , $ l=2 $ , $ r=6 $ , then the path of calculations for that segment is $ [12, $ $ 4, $ $ 0.8, $ $ 0.2, $ $ 2] $ .

Let's call a segment $ [l;r] $ simple if the path of calculations for it contains only integer numbers.

Kuzya needs to find the number of simple segments $ [l;r] $ ( $ 1 \le l \le r \le n $ ). Since he obviously has no time and no interest to do the calculations for each option, he asked you to write a program to get to find that number!

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

The third line contains $ n $ symbols without spaces between them — the array $ b_1, b_2 \ldots b_n $ ( $ b_i= $ '/' or $ b_i= $ '\*' for every $ 1 \le i \le n $ ).

## 输出格式

Print a single integer — the number of simple segments $ [l;r] $ .

## 样例 #1

### 输入

```
3
1 2 3
*/*
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
6 4 10 1 2 15 1
*/*/*//
```

### 输出

```
8
```



---

---
title: "Non-equal Neighbours"
layout: "post"
diff: 提高+/省选-
pid: CF1585F
tag: ['动态规划 DP', '单调队列', '容斥原理']
---

# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print the answer modulo $ 998\,244\,353 $ in a single line.

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
0
```



---

---
title: "Canteen (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2089B2
tag: ['贪心', '二分', '单调队列']
---

# Canteen (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中，对 $$$k$$$ 没有额外限制。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$0 \le k \le 2 \cdot 10^{14}$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a_0, a_1, \ldots, a_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b_0, b_1, \ldots, b_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。


## 说明/提示

在第五个测试用例中，$$$a$$$ 的所有元素在恰好 $$$6$$$ 次修改后变为 $$$0$$$。

在第六个测试用例中，Ecrade 可以对 $$$a_3$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[1,2,2,4]$$$：
- 第一轮操作后，$$a=[3,0,0,0]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,1,0,0]$$。

在第七个测试用例中，Ecrade 可以对 $$$a_4$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[2,1,1,1]$$$：
- 第一轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,1,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,1,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
3 6
1 1 4
5 1 4
4 1
1 2 3 4
4 3 2 1
4 1
2 1 1 2
1 2 2 1
4 2
2 1 1 2
1 2 2 1
```

### 输出

```
1
4
4
8
0
2
2
1
```



---

---
title: "Exposition"
layout: "post"
diff: 提高+/省选-
pid: CF6E
tag: ['单调队列', '枚举', '期望', '队列']
---

# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 输入格式

The first line of the input data contains two integer numbers separated by a space $ n $ ( $ 1<=n<=10^{5} $ ) and $ k $ ( $ 0<=k<=10^{6} $ ) — the amount of books by Berlbury in the library, and the maximum allowed height difference between the lowest and the highest books. The second line contains $ n $ integer numbers separated by a space. Each number $ h_{i} $ ( $ 1<=h_{i}<=10^{6} $ ) is the height of the $ i $ -th book in millimeters.

## 输出格式

In the first line of the output data print two numbers $ a $ and $ b $ (separate them by a space), where $ a $ is the maximum amount of books the organizers can include into the exposition, and $ b $ — the amount of the time periods, during which Berlbury published $ a $ books, and the height difference between the lowest and the highest among these books is not more than $ k $ milllimeters.

In each of the following $ b $ lines print two integer numbers separated by a space — indexes of the first and the last volumes from each of the required time periods of Berlbury's creative work.

## 样例 #1

### 输入

```
3 3
14 12 10

```

### 输出

```
2 2
1 2
2 3

```

## 样例 #2

### 输入

```
2 0
10 10

```

### 输出

```
2 1
1 2

```

## 样例 #3

### 输入

```
4 5
8 19 10 13

```

### 输出

```
2 1
3 4

```



---

---
title: "Cutlet"
layout: "post"
diff: 提高+/省选-
pid: CF939F
tag: ['单调队列', '枚举', '队列']
---

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100000 $ , $ 1<=k<=100 $ ) — the number of seconds the cutlet should be cooked on each side and number of periods of time in which Arkady can flip it.

The next $ k $ lines contain descriptions of these intervals. Each line contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=2·n $ ), meaning that Arkady can flip the cutlet in any moment starting from $ l_{i} $ seconds after the beginning of cooking and finishing at $ r_{i} $ seconds after beginning of cooking. In particular, if $ l_{i}=r_{i} $ then Arkady can flip the cutlet only in the moment $ l_{i}=r_{i} $ . It's guaranteed that $ l_{i}>r_{i-1} $ for all $ 2<=i<=k $ .

## 输出格式

Output "Hungry" if Arkady won't be able to fry the cutlet for exactly $ n $ seconds on one side and exactly $ n $ seconds on the other side.

Otherwise, output "Full" in the first line, and the minimum number of times he should flip the cutlet in the second line.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13

```

### 输出

```
Full
2

```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13

```

### 输出

```
Full
1

```

## 样例 #3

### 输入

```
20 1
3 19

```

### 输出

```
Hungry

```



---

---
title: "Cashback"
layout: "post"
diff: 提高+/省选-
pid: CF940E
tag: ['动态规划 DP', '单调队列', '队列']
---

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 输入格式

The first line contains integers $ n $ and $ c $ ( $ 1<=n,c<=100000 $ ).

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of $ a $ .

## 输出格式

Output a single integer — the smallest possible sum of values of these subarrays of some partition of $ a $ .

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10

```

### 输出

```
92

```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1

```

### 输出

```
17

```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1

```

### 输出

```
23

```



---

