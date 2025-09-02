---
title: "Vasya And The Mushrooms"
layout: "post"
diff: 普及+/提高
pid: CF1016C
tag: ['模拟', '递推', '前缀和']
---

# Vasya And The Mushrooms

## 题目描述

Vasya 住在森林里，附近有一个会长蘑菇的空地。这个空地被分成两行，每行分为 $n$ 个连续的格子。Vasya 知道每分钟每个格子里能长多少个蘑菇。他要花一分钟从一个格子走到相邻的格子上，并且他不能离开空地。（我们称两个格子相邻，当且仅当它们有公共边。）当 Vasya 进入一个格子时，他会马上收集那个格子里的所有蘑菇。

Vasya 从左上角的格子开始收集蘑菇。因为他等不及蘑菇生长了，所以每分钟内他必须移动到一个相邻格子。他想每个格子都恰好走一遍并且最大化他所收集的蘑菇数量。一开始所有格子都没有蘑菇。Vasya也不一定要回到开始的格子。
帮帮 Vasya！计算出他能收集到的最大蘑菇数量。

## 输入格式

第一行包含数字 $n(1 \le n \le 3 \cdot 10 ^ {5})$ —— 空地的长度。

第二行包含 $n$ 个数字 $a_ {1}, a_ {2}, \ldots, a_{n}$（$1 \le a_{i} \le 10^{6}$） —— 在空地第一行的蘑菇的生长速度。

第三行包含 $n$ 个数字 $b_ {1}, b_ {2}, \ldots, b_{n}$（$1 \le b_ {i} \le 10 ^ {6}$） —— 在空地第二行的蘑菇的生长速度。

## 输出格式

输出一个数字—— Vasya 通过选择最佳路线可以收集的最大蘑菇总重量。 

请注意，Vasya 必须将空地中的每个单元都访问一次。

## 说明/提示

#### 样例1:

在第一个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/fbb0db02f46ac40c8f18dc6a212852df14543f5e.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·2 + 2·3 + 3·4 + 4·5 + 5·6 =70$。

#### 样例2:

在第二个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/0853812a60511dc1127814cc7d3f93535736820f.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·10 + 2·100 + 3·1000 + 4·10000 + 5·100000 =543210$

## 样例 #1

### 输入

```
3
1 2 3
6 5 4

```

### 输出

```
70

```

## 样例 #2

### 输入

```
3
1 1000 10000
10 100 100000

```

### 输出

```
543210

```



---

---
title: "Petya and Array"
layout: "post"
diff: 普及+/提高
pid: CF1042D
tag: ['线段树', '树状数组', '前缀和']
---

# Petya and Array

## 题目描述

Petya has an array $ a $ consisting of $ n $ integers. He has learned partial sums recently, and now he can calculate the sum of elements on any segment of the array really fast. The segment is a non-empty sequence of elements standing one next to another in the array.

Now he wonders what is the number of segments in his array with the sum less than $ t $ . Help Petya to calculate this number.

More formally, you are required to calculate the number of pairs $ l, r $ ( $ l \le r $ ) such that $ a_l + a_{l+1} + \dots + a_{r-1} + a_r < t $ .

## 输入格式

The first line contains two integers $ n $ and $ t $ ( $ 1 \le n \le 200\,000, |t| \le 2\cdot10^{14} $ ).

The second line contains a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ |a_{i}| \le 10^{9} $ ) — the description of Petya's array. Note that there might be negative, zero and positive elements.

## 输出格式

Print the number of segments in Petya's array with the sum of elements less than $ t $ .

## 说明/提示

In the first example the following segments have sum less than $ 4 $ :

- $ [2, 2] $ , sum of elements is $ -1 $
- $ [2, 3] $ , sum of elements is $ 2 $
- $ [3, 3] $ , sum of elements is $ 3 $
- $ [4, 5] $ , sum of elements is $ 3 $
- $ [5, 5] $ , sum of elements is $ -1 $

## 样例 #1

### 输入

```
5 4
5 -1 3 4 -1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 0
-1 2 -3

```

### 输出

```
4

```

## 样例 #3

### 输入

```
4 -1
-2 1 -2 3

```

### 输出

```
3

```



---

---
title: "Changing Array"
layout: "post"
diff: 普及+/提高
pid: CF1054D
tag: ['贪心', '前缀和', '位运算']
---

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 200\,000 $ , $ 1 \leq k \leq 30 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 2^k - 1 $ ), separated by spaces — the array of $ k $ -bit integers.

## 输出格式

Print one integer — the maximum possible number of segments with XOR not equal to $ 0 $ that can be obtained by making several (possibly $ 0 $ ) operations described in the statement.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0

```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4

```

### 输出

```
19
```



---

---
title: "Maximum Subrectangle"
layout: "post"
diff: 普及+/提高
pid: CF1060C
tag: ['枚举', '前缀和']
---

# Maximum Subrectangle

## 题目描述

You are given two arrays $ a $ and $ b $ of positive integers, with length $ n $ and $ m $ respectively.

Let $ c $ be an $ n \times m $ matrix, where $ c_{i,j} = a_i \cdot b_j $ .

You need to find a subrectangle of the matrix $ c $ such that the sum of its elements is at most $ x $ , and its area (the total number of elements) is the largest possible.

Formally, you need to find the largest number $ s $ such that it is possible to choose integers $ x_1, x_2, y_1, y_2 $ subject to $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s $ , and $ $$ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x. $ $$

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 2000 $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \leq b_i \leq 2000 $ ).

The fourth line contains a single integer $ x $ ( $ 1 \leq x \leq 2 \cdot 10^{9} $ ).

## 输出格式

If it is possible to choose four integers $ x_1, x_2, y_1, y_2 $ such that $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , and $ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x $ , output the largest value of $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) $ among all such quadruplets, otherwise output $ 0 $ .

## 说明/提示

Matrix from the first sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)Matrix from the second sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 3
9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 1
5 4 2 4 5
2
5

```

### 输出

```
1

```



---

---
title: "Vasya and Robot"
layout: "post"
diff: 普及+/提高
pid: CF1073C
tag: ['二分', '枚举', '前缀和']
---

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 输入格式

The first line contains one integer number $ n~(1 \le n \le 2 \cdot 10^5) $ — the number of operations.

The second line contains the sequence of operations — a string of $ n $ characters. Each character is either U, D, L or R.

The third line contains two integers $ x, y~(-10^9 \le x, y \le 10^9) $ — the coordinates of the cell where the robot should end its path.

## 输出格式

Print one integer — the minimum possible length of subsegment that can be changed so the resulting sequence of operations moves the robot from $ (0, 0) $ to $ (x, y) $ . If this change is impossible, print $ -1 $ .

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
RULR
1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
UUU
100 100

```

### 输出

```
-1

```



---

---
title: "LCIS"
layout: "post"
diff: 普及+/提高
pid: CF10D
tag: ['动态规划 DP', '树状数组', '前缀和']
---

# LCIS

## 题目描述

This problem differs from one which was on the online contest.

The sequence $ a_{1},a_{2},...,a_{n} $ is called increasing, if $ a_{i}<a_{i+1} $ for $ i<n $ .

The sequence $ s_{1},s_{2},...,s_{k} $ is called the subsequence of the sequence $ a_{1},a_{2},...,a_{n} $ , if there exist such a set of indexes $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ that $ a_{ij}=s_{j} $ . In other words, the sequence $ s $ can be derived from the sequence $ a $ by crossing out some elements.

You are given two sequences of integer numbers. You are to find their longest common increasing subsequence, i.e. an increasing sequence of maximum length that is the subsequence of both sequences.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=500 $ ) — the length of the first sequence. The second line contains $ n $ space-separated integers from the range $ [0,10^{9}] $ — elements of the first sequence. The third line contains an integer $ m $ ( $ 1<=m<=500 $ ) — the length of the second sequence. The fourth line contains $ m $ space-separated integers from the range $ [0,10^{9}] $ — elements of the second sequence.

## 输出格式

In the first line output $ k $ — the length of the longest common increasing subsequence. In the second line output the subsequence itself. Separate the elements with a space. If there are several solutions, output any.

## 样例 #1

### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6

```

### 输出

```
3
3 5 6 

```

## 样例 #2

### 输入

```
5
1 2 0 2 1
3
1 0 1

```

### 输出

```
2
0 1 

```



---

---
title: "Porcelain"
layout: "post"
diff: 普及+/提高
pid: CF148E
tag: ['枚举', '背包 DP', '前缀和']
---

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 输入格式

The first line of input data contains two integers $ n $ ( $ 1<=n<=100 $ ) and $ m $ ( $ 1<=m<=10000 $ ). The next $ n $ lines contain the values of the items on the shelves: the first number gives the number of items on this shelf (an integer between $ 1 $ and $ 100 $ , inclusive), followed by the values of the items (integers between $ 1 $ and $ 100 $ , inclusive), in the order in which they appear on the shelf (the first number corresponds to the leftmost item, the last one — to the rightmost one). The total number of items is guaranteed to be at least $ m $ .

## 输出格式

Output the maximal total value of a tantrum of $ m $ shrieks.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5

```

### 输出

```
15

```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2

```

### 输出

```
9

```



---

---
title: "Even Subarrays"
layout: "post"
diff: 普及+/提高
pid: CF1731C
tag: ['动态规划 DP', '数学', '前缀和']
---

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the number of subarrays, whose $ \operatorname{XOR} $ has an even number of divisors.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3
```

### 输出

```
4
11
0
20
```



---

---
title: "Valiant's New Map"
layout: "post"
diff: 普及+/提高
pid: CF1731D
tag: ['二分', '前缀和']
---

# Valiant's New Map

## 题目描述

Game studio "DbZ Games" wants to introduce another map in their popular game "Valiant". This time, the map named "Panvel" will be based on the city of Mumbai.

Mumbai can be represented as $ n \times m $ cellular grid. Each cell $ (i, j) $ ( $ 1 \le i \le n $ ; $ 1 \le j \le m $ ) of the grid is occupied by a cuboid building of height $ a_{i,j} $ .

This time, DbZ Games want to make a map that has perfect vertical gameplay. That's why they want to choose an $ l \times l $ square inside Mumbai, such that each building inside the square has a height of at least $ l $ .

Can you help DbZ Games find such a square of the maximum possible size $ l $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). Description of the test cases follows.

The first line of each test case contains two positive integers $ n $ and $ m $ ( $ 1 \le n \le m $ ; $ 1 \leq n \cdot m \leq 10^6 $ ).

The $ i $ -th of next $ n $ lines contains $ m $ integers $ a_{i,1}, a_{i,2}, \dots, a_{i,m} $ ( $ 1 \leq a_{i,j} \leq 10^6 $ ) — heights of buildings on the $ i $ -th row.

It's guaranteed that the sum of $ n \cdot m $ over all test cases doesn't exceed $ 10^6 $ .

## 输出格式

For each test case, print the maximum side length $ l $ of the square DbZ Games can choose.

## 说明/提示

In the first test case, we can choose the square of side $ l = 2 $ (i. e. the whole grid) since the heights of all buildings are greater than or equal to $ 2 $ .

In the second test case, we can only choose the side as $ 1 $ , so the answer is $ 1 $ .

In the third test case, there are no squares of size $ 2 $ that have all buildings of height at least $ 2 $ , so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
2 2
2 3
4 5
1 3
1 2 3
2 3
4 4 3
2 1 4
5 6
1 9 4 6 5 8
10 9 5 8 11 6
24 42 32 8 11 1
23 1 9 69 13 3
13 22 60 12 14 17
```

### 输出

```
2
1
1
3
```



---

---
title: "Zero-Sum Prefixes"
layout: "post"
diff: 普及+/提高
pid: CF1748C
tag: ['贪心', '前缀和']
---

# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the maximum possible score of the array $ a $ after performing a sequence of operations.

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1
```

### 输出

```
3
1
4
4
5
```



---

---
title: "Range = √Sum"
layout: "post"
diff: 普及+/提高
pid: CF1758D
tag: ['前缀和', '构造']
---

# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the length of the sequence you have to find.

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ space-separated distinct integers $ a_1, a_2, \dots, a_n $ satisfying the conditions in the statement.

If there are several possible answers, you can output any of them. Please remember that your integers must be distinct!

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4
```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31
```



---

---
title: "Mischievous Shooter"
layout: "post"
diff: 普及+/提高
pid: CF1921G
tag: ['枚举', '前缀和', '差分']
---

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains field dimensions $ n $ , $ m $ , and the constant for the shotgun's power $ k $ ( $ 1 \le n, m, k \le 10^5, 1 \le n \cdot m \le 10^5 $ ).

Each of the next $ n $ lines contains $ m $ characters — the description of the next field row, where the character '.' means the cell is empty, and the character '\#' indicates the presence of a target.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer on a separate line, which is equal to the maximum possible number of hit targets with one shot.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#
```

### 输出

```
3
4
5
2
```



---

---
title: "Slimes"
layout: "post"
diff: 普及+/提高
pid: CF1923D
tag: ['二分', '前缀和']
---

# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the number of slimes.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers. The $ i $ -th integer should be equal to the minimum number of seconds it takes for the $ i $ -th slime to be eaten by another slime or -1 if it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8
```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4
```



---

---
title: "A BIT of an Inequality"
layout: "post"
diff: 普及+/提高
pid: CF1957D
tag: ['前缀和', '位运算']
---

# A BIT of an Inequality

## 题目描述

给定序列 $a_n$，求满足以下条件的三元组 $(x,y,z)$ 的数量：

* $1\le x\le y\le z\le n$.

* $f(x,y)\oplus f(y,z)>f(x,z)$.

我们规定 $f(l,r)$ 表示 $a_l\oplus a_{l+1}\oplus\dots\oplus a_{r-1}\oplus a_{r}$，$\oplus$ 表示[异或和](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行一个整数 $n$。

接下来 $n$ 个整数，表示 $a_i$。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le10^5$，$1\le a_i\le10^9$，$\sum n\le10^5$。

## 样例 #1

### 输入

```
3
3
6 2 4
1
3
5
7 3 7 2 1
```

### 输出

```
4
0
16
```



---

---
title: "Beauty of the mountains"
layout: "post"
diff: 普及+/提高
pid: CF1982D
tag: ['数论', '前缀和']
---

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. This is followed by a description of test cases.

The first line of each test case contains three integers $ n, m, k $ ( $ 1 \le n, m \le 500, 1 \le k \le min(n, m) $ ).

The next $ n $ lines of each test case contain $ m $ integers $ a_{i j} $ ( $ 0 \le a_{i j} \le 10^{9} $ ) — the initial heights of the mountains.

The next $ n $ binary strings of length $ m $ for each test case determine the type of mountain, ' $ 0 $ ' — with snowy caps, ' $ 1 $ ' — without them.

It is guaranteed that the sum of $ n \cdot m $ for all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each test case, output "YES" without quotes if it is possible to equalize the sums of the mountain heights, otherwise output "NO" without quotes. You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES
```



---

---
title: "Sakurako's Test"
layout: "post"
diff: 普及+/提高
pid: CF2008H
tag: ['数学', '二分', '前缀和']
---

# Sakurako's Test

## 题目描述

Sakurako 即将参加一场考试，这场考试可用一个整数数组 $n$ 和一个相关任务来描述：

对于给定的整数 $x$，Sakurako 可以多次执行以下操作：

- 选择一个整数 $i$，其中 $1 \le i \le n$，且满足 $a_i \ge x$；
- 将 $a_i$ 的值减少 $x$，即改为 $a_i - x$。

通过这样的操作，她需要找到数组 $a$ 的最小可能中位数 $^{\text{∗}}$。

Sakurako 已知数组的内容，但不清楚整数 $x$ 的值。不过，有人透露在接下来的考试中，$x$ 的值会是给定的 $q$ 个值之一，因此她希望你能帮忙找出每一个可能的 $x$ 所对应的最小中位数。

$^{\text{∗}}$ 对于一个长度为 $n$ 的数组，若 $n$ 是偶数，则中位数是排序后数组中第 $\frac{n+2}{2}$ 个位置的元素；若 $n$ 是奇数，则为第 $\frac{n+1}{2}$ 个位置的元素。

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来，每个测试用例的第一行包括两个整数 $n$ 和 $q$，分别表示数组的元素数量和查询数量（$1 \le n, q \le 10^5$）。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，表示数组的内容（$1 \le a_i \le n$）。

接下来的 $q$ 行每行给出一个整数 $x$，表示一个查询（$1 \le x \le n$）。

保证所有测试用例中 $n$ 和 $q$ 的总和均不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 $q$ 个整数，代表每个查询下计算出的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
2
3
4
5
6 3
1 2 6 4 1 3
2
1
5
```

### 输出

```
0 1 1 1 2 
1 0 2
```



---

---
title: "Minimize the Difference"
layout: "post"
diff: 普及+/提高
pid: CF2013D
tag: ['二分', '前缀和']
---

# Minimize the Difference

## 题目描述

给你一个长度为 $n$ 的数 $a_1,a_2,…,a_n$ 我们可以对数组进行任意数量(可能是零)的运算。

在每次操作中，我们选择一个位置 $i$ ( $1 \le i \le n−1 $
 ) ，使 $a_i-1,a_{i+1}+1$

求 $max(a_1,a_2,…,a_n)−min(a_1,a_2,…,a_n)$ 的最小可能值。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^5$ ) 。测试用例说明如下:

每个测试用例的第一行都包含一个整数 $n$ ( $1 \le n \le 2 \times 10^{5}$ ) 。

每个测试用例的第二行包含 $n$ 个整数 $a_1,a_2,…,a_n$ ( $1 \le a_i \le 10^{12}$ ) 。

所有测试用例中 $n$
 的总和不超过 $2 \times 10^{5}$ 。

## 输出格式

对于每个测试用例，输出一个整数 $ans$ 表示 $max(a_1,a_2,…,a_n)−min(a_1,a_2,…,a_n)$
 的最小可能值。

## 说明/提示

在第三个测试案例中，您可以使用 $i=1$
 执行两次操作。
之后，数组为 $[2,3,2,3]$
 所以 $ans=max(2,3,2,3)−min(2,3,2,3)=3−2=1$
 。

## 样例 #1

### 输入

```
5
1
1
3
1 2 3
4
4 1 2 3
4
4 2 3 1
5
5 14 4 10 2
```

### 输出

```
0
2
1
1
3
```



---

---
title: "Fragile Bridges"
layout: "post"
diff: 普及+/提高
pid: CF201C
tag: ['动态规划 DP', '枚举', '前缀和']
---

# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of platforms on the bonus level. The second line contains ( $ n-1 $ ) integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ , $ 1<=i&lt;n $ ) — the number of transitions from one end to the other that the bridge between platforms $ i $ and $ i+1 $ can bear.

## 输出格式

Print a single integer — the maximum number of points a player can get on the bonus level.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1

```

### 输出

```
5

```



---

---
title: "Sums of Segments"
layout: "post"
diff: 普及+/提高
pid: CF2026D
tag: ['二分', '前缀和']
---

# Sums of Segments

## 题目描述

You are given a sequence of integers $ [a_1, a_2, \dots, a_n] $ . Let $ s(l,r) $ be the sum of elements from $ a_l $ to $ a_r $ (i. e. $ s(l,r) = \sum\limits_{i=l}^{r} a_i $ ).

Let's construct another sequence $ b $ of size $ \frac{n(n+1)}{2} $ as follows: $ b = [s(1,1), s(1,2), \dots, s(1,n), s(2,2), s(2,3), \dots, s(2,n), s(3,3), \dots, s(n,n)] $ .

For example, if $ a = [1, 2, 5, 10] $ , then $ b = [1, 3, 8, 18, 2, 7, 17, 5, 15, 10] $ .

You are given $ q $ queries. During the $ i $ -th query, you are given two integers $ l_i $ and $ r_i $ , and you have to calculate $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10 \le a_i \le 10 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ).

Then $ q $ lines follow, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le \frac{n(n+1)}{2} $ ).

## 输出格式

Print $ q $ integers, the $ i $ -th of which should be equal to $ \sum \limits_{j=l_i}^{r_i} b_j $ .

## 样例 #1

### 输入

```
4
1 2 5 10
15
1 1
1 2
1 3
1 4
1 5
1 10
5 10
6 10
2 8
3 4
3 10
3 8
5 6
5 5
1 8
```

### 输出

```
1
4
12
30
32
86
56
54
60
26
82
57
9
2
61
```



---

---
title: "Igor and Mountain"
layout: "post"
diff: 普及+/提高
pid: CF2091F
tag: ['动态规划 DP', '前缀和']
---

# Igor and Mountain

## 题目描述

IT Campus "NEIMARK" 的访客不仅是优秀的程序员，更是体魄强健的运动爱好者！有人练习游泳，有人划船，还有人进行攀岩！

Igor 大师是当地攀岩界的知名人物。某天，他前往山区攀登一座山峰。作为经验丰富的攀岩者，Igor 决定不沿既有路线，而是利用自己的技巧严格垂直攀登。

Igor 找到了一块垂直的矩形山体区域，并将其在脑海中划分为 $n$ 个水平层。随后他将每层用垂直隔板分割为 $m$ 个区段。观察这些区段时，Igor 发现了可供抓握的凸起（以下称为支点）。因此，所选山体区域可表示为 $n \times m$ 的矩形，其中某些单元格包含支点。

作为资深程序员，Igor 决定计算有效路线的数量。路线被定义为由不同支点组成的序列。当满足以下条件时，路线被视为有效：

- 路线中第一个支点位于最底层（第 $n$ 行）；
- 路线中最后一个支点位于最顶层（第 $1$ 行）；
- 每个后续支点不低于前一个支点；
- 每层（即矩形的每一行）至少使用一个支点；
- 每层最多使用两个支点（因 Igor 只有双手）；
- 当相邻支点对应区段中心点的欧氏距离不超过 Igor 的臂展时，才能从当前支点移动到下一个支点。

Igor 的臂展为 $d$，这意味着当两个支点对应区段中心点的欧氏距离不超过 $d$ 时可进行移动。区段 $(i_1, j_1)$ 与 $(i_2, j_2)$ 之间的距离计算公式为 $\sqrt{(i_1 - i_2)^2 + (j_1 - j_2)^2}$。

请计算不同有效路线的数量。若两条路线使用的支点列表或访问顺序不同，则视为不同的路线。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$ ($1 \leq t \leq 10^3$)。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n$、$m$、$d$ ($2 \leq n \leq 2000$, $1 \leq m, d \leq 2000$)。

接下来的 $n$ 行每行包含 $m$ 个字符 —— 描述山体各层情况。字符 '#' 表示空区段，'X' 表示含支点的区段。层数描述顺序为从上到下。

保证所有测试用例的 $n \cdot m$ 之和不超过 $4 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出不同路线数量对 $998244353$ 取模后的结果。


## 说明/提示

第一个样例中的可能路线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/e87023b4f4a219144271b82b78cb035704abe051.png)  
第二个样例中 Igor 的臂展增大，因此新路线可用，例如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/af93e08d9fa412dbf0403f4084f2c8743d449017.png)  
第三个样例中底层没有支点，因此不存在有效路线。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3 4 1
XX#X
#XX#
#X#X
3 4 2
XX#X
#XX#
#X#X
3 1 3
X
X
#
```

### 输出

```
2
60
0
```



---

---
title: "Goblin"
layout: "post"
diff: 普及+/提高
pid: CF2106F
tag: ['并查集', '前缀和']
---

# Goblin

## 题目描述

TC 博士有一位新病人叫哥布林。他想测试哥布林的智力，但对标准测试感到厌倦了，于是决定增加难度。

首先，他创建一个长度为 $n$ 的二进制字符串$^{\text{∗}}$ $s$。然后，他创建 $n$ 个二进制字符串 $a_1, a_2, \ldots, a_n$。已知 $a_i$ 是通过先复制 $s$，再翻转第 $i$ 个字符（$\texttt{1}$ 变为 $\texttt{0}$，反之亦然）得到的。创建完所有 $n$ 个字符串后，他将它们排列成一个 $n \times n$ 的网格 $g$，其中 $g_{i, j} = a_{i_j}$。

一个大小为 $k$ 的集合 $S$ 被认为是好的，如果它满足以下条件：

1. 对于所有 $1 \leq i \leq k$，有 $1 \leq x_i, y_i \leq n$；
2. 对于所有 $1 \leq i \leq k$，有 $g_{x_i, y_i} = \texttt{0}$；
3. 对于任意两个整数 $i$ 和 $j$（$1 \leq i, j \leq k$），坐标 $(x_i, y_i)$ 可以通过一系列相邻的（共享一条边的）值为 $\texttt{0}$ 的单元格到达 $(x_j, y_j)$。

哥布林的任务是找出一个好的集合 $S$ 的最大可能大小。由于 TC 博士很慷慨，这次给了他两秒而不是一秒来找出答案。哥布林以不诚实著称，所以他请你帮他作弊。

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\texttt{1}$ 和 $\texttt{0}$ 组成的字符串。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 10^3$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——二进制字符串 $s$ 的长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串 $s$。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个数字，表示网格中好的单元格集合的最大可能大小。


## 说明/提示

在第一个示例中，网格如下：

```
1 0 0
0 1 0
0 0 1
```

由单元格 $(1, 2)$ 和 $(1, 3)$ 组成的集合是好的。由单元格 $(1, 1)$ 和 $(1, 2)$ 组成的集合不是好的，因为单元格 $(1, 1)$ 的值不是 $\texttt{0}$。由单元格 $(1, 2)$、$(1, 3)$ 和 $(2, 3)$ 组成的集合是好的，且最大大小为 $3$。注意，由单元格 $(2, 1)$、$(3, 1)$ 和 $(3, 2)$ 组成的集合也是好的，最大大小同样为 $3$。

在第二个示例中，网格如下：

```
1 0 1 0
0 1 1 0
0 0 0 0
0 0 1 1
```

好的集合的最大可能大小为 $9$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3
000
4
0010
7
1011001
4
0001
2
11
1
0
```

### 输出

```
3
9
10
7
1
0
```



---

---
title: "Queries for Number of Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF245H
tag: ['字符串', '动态规划 DP', '区间 DP', '前缀和']
---

# Queries for Number of Palindromes

## 题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

## 输入格式

第1行，给出s，s的长度小于5000
第2行给出q(1<=q<=10^6)
第2至2+q行 给出每组询问的l和r

## 输出格式

输出每组询问所问的数量。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5

```

### 输出

```
1
7
3
4
2

```



---

---
title: "Wonderful Randomized Sum"
layout: "post"
diff: 普及+/提高
pid: CF33C
tag: ['数学', '贪心', '前缀和']
---

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of elements in the sequence. The second line contains $ n $ integers $ a_{i} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ) — the sequence itself.

## 输出格式

The first and the only line of the output should contain the answer to the problem.

## 样例 #1

### 输入

```
3
-1 -2 -3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
-4 2 0 5 0

```

### 输出

```
11

```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2

```

### 输出

```
18

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
title: "Flowers"
layout: "post"
diff: 普及+/提高
pid: CF474D
tag: ['动态规划 DP', '前缀和']
---

# Flowers

## 题目描述

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输出格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

- For $ K $ = $ 2 $ and length $ 1 $ Marmot can eat ( $ R $ ).
- For $ K $ = $ 2 $ and length $ 2 $ Marmot can eat ( $ RR $ ) and ( $ WW $ ).
- For $ K $ = $ 2 $ and length $ 3 $ Marmot can eat ( $ RRR $ ), ( $ RWW $ ) and ( $ WWR $ ).
- For $ K $ = $ 2 $ and length $ 4 $ Marmot can eat, for example, ( $ WWWW $ ) or ( $ RWWR $ ), but for example he can't eat ( $ WWWR $ ).

## 样例 #1

### 输入

```
3 2
1 3
2 3
4 4

```

### 输出

```
6
5
5

```



---

---
title: "Riding in a Lift"
layout: "post"
diff: 普及+/提高
pid: CF479E
tag: ['动态规划 DP', '前缀和']
---

# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line of the input contains four space-separated integers $ n $ , $ a $ , $ b $ , $ k $ ( $ 2<=n<=5000 $ , $ 1<=k<=5000 $ , $ 1<=a,b<=n $ , $ a≠b $ ).

## 输出格式

Print a single integer — the remainder after dividing the sought number of sequences by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 4 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 3 4 1

```

### 输出

```
0

```



---

---
title: "Weakness and Poorness"
layout: "post"
diff: 普及+/提高
pid: CF578C
tag: ['前缀和']
---

# Weakness and Poorness

## 题目描述

You are given a sequence of n integers $ a_{1},a_{2},...,a_{n} $ .

Determine a real number $ x $ such that the weakness of the sequence $ a_{1}-x,a_{2}-x,...,a_{n}-x $ is as small as possible.

The weakness of a sequence is defined as the maximum value of the poorness over all segments (contiguous subsequences) of a sequence.

The poorness of a segment is defined as the absolute value of sum of the elements of segment.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ), the length of a sequence.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10000 $ ).

## 输出格式

Output a real number denoting the minimum possible weakness of $ a_{1}-x,a_{2}-x,...,a_{n}-x $ . Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 说明/提示

For the first case, the optimal value of $ x $ is $ 2 $ so the sequence becomes $ -1 $ , $ 0 $ , $ 1 $ and the max poorness occurs at the segment "-1" or segment "1". The poorness value (answer) equals to $ 1 $ in this case.

For the second sample the optimal value of $ x $ is $ 2.5 $ so the sequence becomes $ -1.5,-0.5,0.5,1.5 $ and the max poorness occurs on segment "-1.5 -0.5" or "0.5 1.5". The poorness value (answer) equals to $ 2 $ in this case.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
1.000000000000000

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
2.000000000000000

```

## 样例 #3

### 输入

```
10
1 10 2 9 3 8 4 7 5 6

```

### 输出

```
4.500000000000000

```



---

---
title: "Beautiful Subarrays"
layout: "post"
diff: 普及+/提高
pid: CF665E
tag: ['前缀和', '字典树 Trie']
---

# Beautiful Subarrays

## 题目描述

One day, ZS the Coder wrote down an array of integers $ a $ with elements $ a_{1},a_{2},...,a_{n} $ .

A subarray of the array $ a $ is a sequence $ a_{l},a_{l+1},...,a_{r} $ for some integers $ (l,r) $ such that $ 1<=l<=r<=n $ . ZS the Coder thinks that a subarray of $ a $ is beautiful if the bitwise xor of all the elements in the subarray is at least $ k $ .

Help ZS the Coder find the number of beautiful subarrays of $ a $ !

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{6},1<=k<=10^{9} $ ) — the number of elements in the array $ a $ and the value of the parameter $ k $ .

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{9} $ ) — the elements of the array $ a $ .

## 输出格式

Print the only integer $ c $ — the number of beautiful subarrays of the array $ a $ .

## 样例 #1

### 输入

```
3 1
1 2 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 2
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3 3
1 2 3

```

### 输出

```
2

```



---

---
title: "Balanced Substring"
layout: "post"
diff: 普及+/提高
pid: CF873B
tag: ['字符串', '前缀和']
---

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 输入格式

The first line contains $ n $ ( $ 1<=n<=100000 $ ) — the number of characters in $ s $ .

The second line contains a string $ s $ consisting of exactly $ n $ characters. Only characters 0 and 1 can appear in $ s $ .

## 输出格式

If there is no non-empty balanced substring in $ s $ , print 0. Otherwise, print the length of the longest balanced substring.

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
111

```

### 输出

```
0

```



---

