---
title: "The Strict Teacher (Hard Version)"
layout: "post"
diff: 普及/提高-
pid: CF2005B2
tag: ['数学', '二分', '分类讨论']
---

# The Strict Teacher (Hard Version)

## 题目描述

**这是本题的困难版，它和本题的简单版的唯一差距是 $m$ 和 $q$ 的数据范围**。在此版本中，$m,q\le10^5$。你在解决两个版本之后才可以去提交 hack 数据。

Narek 和 Tsovak 正在热火朝天地准备这场比赛，所以他们没时间去做作业了，因此，他们决定去偷 David 的作业。

严厉的老师发现 David 的作业没了非常生气，打算狠狠地惩罚他，于是她雇佣了别的老师帮她一起抓捕 David。

现在有 $m$ 个老师正在一起追 David。幸运的是，教室非常的大，所以 David 有充足的躲藏空间。

教室可以被表示为一条一维直线，上面有 $n$ 个单元格编号从 $1$ 到 $n$，**包含边界。**

最初，David 和这 $m$ 个老师**在不同的单元格中**。然后他们将会进行若干次行动。每次行动中：
- 首先，David 可以移动到一个**相邻的**单元格中，**也可以不动。**
- 然后，每位老师也进行这样的一次移动。

行动将一直持续知道 David 被抓住，即有任何一个老师和 David 位于同一个单元格中。**所有人都看得见其它人的行动。**

你的任务是计算**在所有人按照最优方案行动的前提下，多少次行动后 David 会被抓住。**

> 按照最优方案行动，是指：
> - David 采取一种方案，使得老师抓住他所需的行动次数最大。
> - 老师之间相互配合并采用一种方案，使得他们能够用最少的行动次数抓住 David。

Narek 和 Tsovak 认为这个任务太简单了，于是他们决定给你 $q$ 次询问。

## 输入格式

**每个测试点有多组数据。**

第一行有一个正整数 $t(1\le t\le10^5)$，表示数据的组数。

每组数据的第一行有三个正整数 $n,m,q(3\le n\le10^9,1\le m,q\le10^5)$，分别表示单元格个数，老师个数，和询问次数。

每组数据的第二行有 $m$ 个**不同的**正整数 $b_1,b_2,\dots,b_m(1\le b_i\le n)$，代表每个老师初始的位置。

每组数据的第三行有 $q$ 个正整数 $a_1,a_2,\dots,a_q(1\le a_i\le n)$，代表每次询问中 David 的初始位置。

保证 $\forall i\in[1,m],j\in[1,q],b_i\ne a_j$。

保证 $\sum m,\sum q\le2\cdot10^5$。

## 输出格式

对于每组数据，输出 $q$ 行，第 $i$ 行是这组数据中的第 $i$ 次询问的答案。

### 样例解释翻译

在样例 $1$ 的唯一一次询问中，David 可以跑到 $1$ 号单元格。老师需要 $5$ 步来从 $6$ 号单元格跑到 $1$ 号单元格，所以答案为 $5$。

在样例 $2$ 的第二次讯问中，David 可以一直呆在 $3$ 号单元格。初始位于 $4$ 号单元格的老师一步就可以走到 $3$ 号单元格。因此答案为 $1$。

## 样例 #1

### 输入

```
2
8 1 1
6
3
10 3 3
1 4 8
2 3 10
```

### 输出

```
5
1
1
2
```



---

---
title: "Alice's Adventures in Permuting"
layout: "post"
diff: 普及/提高-
pid: CF2028B
tag: ['数学', '分类讨论']
---

# Alice's Adventures in Permuting

## 题目描述

Alice mixed up the words transmutation and permutation! She has an array $ a $ specified via three integers $ n $ , $ b $ , $ c $ : the array $ a $ has length $ n $ and is given via $ a_i = b\cdot (i - 1) + c $ for $ 1\le i\le n $ . For example, if $ n=3 $ , $ b=2 $ , and $ c=1 $ , then $ a=[2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5] $ .

Now, Alice really enjoys permutations of $ [0, \ldots, n-1] $ $ ^{\text{∗}} $ and would like to transform $ a $ into a permutation. In one operation, Alice replaces the maximum element of $ a $ with the $ \operatorname{MEX} $ $ ^{\text{†}} $ of $ a $ . If there are multiple maximum elements in $ a $ , Alice chooses the leftmost one to replace.

Can you help Alice figure out how many operations she has to do for $ a $ to become a permutation for the first time? If it is impossible, you should report it.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. Please note, this is slightly different from the usual definition of a permutation. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

 $ ^{\text{†}} $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, the $ \operatorname{MEX} $ of $ [0, 3, 1, 3] $ is $ 2 $ and the $ \operatorname{MEX} $ of $ [5] $ is $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The only line of each test case contains three integers $ n $ , $ b $ , $ c $ ( $ 1\le n\le 10^{18} $ ; $ 0\le b $ , $ c\le 10^{18} $ ) — the parameters of the array.

## 输出格式

For each test case, if the array can never become a permutation, output $ -1 $ . Otherwise, output the minimum number of operations for the array to become a permutation.

## 说明/提示

In the first test case, the array is already $ [0, 1, \ldots, 9] $ , so no operations are required.

In the third test case, the starting array is $ [1, 3, 5, \ldots, 199] $ . After the first operation, the $ 199 $ gets transformed into a $ 0 $ . In the second operation, the $ 197 $ gets transformed into a $ 2 $ . If we continue this, it will take exactly $ 50 $ operations to get the array $ [0, 1, 2, 3, \ldots, 99] $ .

In the fourth test case, two operations are needed: $ [1,1,1] \to [0,1,1] \to [0,2,1] $ .

In the fifth test case, the process is $ [0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0] $ . This process repeats forever, so the array is never a permutation and the answer is $ -1 $ .

## 样例 #1

### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000
```

### 输出

```
0
1
50
2
-1
-1
1000000000000000000
```



---

---
title: "Sakurako's Field Trip"
layout: "post"
diff: 普及/提高-
pid: CF2033C
tag: ['动态规划 DP', '双指针 two-pointer', '分类讨论']
---

# Sakurako's Field Trip

## 题目描述

Even in university, students need to relax. That is why Sakurakos teacher decided to go on a field trip. It is known that all of the students will be walking in one line. The student with index $ i $ has some topic of interest which is described as $ a_i $ . As a teacher, you want to minimise the disturbance of the line of students.

The disturbance of the line is defined as the number of neighbouring people with the same topic of interest. In other words, disturbance is the number of indices $ j $ ( $ 1 \le j < n $ ) such that $ a_j = a_{j + 1} $ .

In order to do this, you can choose index $ i $ ( $ 1\le i\le n $ ) and swap students at positions $ i $ and $ n-i+1 $ . You can perform any number of swaps.

Your task is to determine the minimal amount of disturbance that you can achieve by doing the operation described above any number of times.

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described by two lines.

- The first line contains one integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the length of the line of students.
- The second line contains $ n $ integers $ a_i $ ( $ 1\le a_i\le n $ ) — the topics of interest of students in line.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimal possible disturbance of the line that you can achieve.

## 说明/提示

In the first example, it is necessary to apply the operation to $ i=2 $ , thus the array will become $ [1, \textbf{2}, 1, \textbf{1}, 3] $ , with the bold elements indicating those that have swapped places. The disturbance of this array is equal to $ 1 $ .

In the fourth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [2, 1, \textbf{2}, \textbf{1}, 2, 4] $ . The disturbance of this array is equal to $ 0 $ .

In the eighth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [1, 4, \textbf{1}, 5, \textbf{3}, 1, 3] $ . The disturbance of this array is equal to $ 0 $ .

## 样例 #1

### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3
```

### 输出

```
1
2
1
0
0
1
1
0
2
```



---

---
title: "I Love 1543"
layout: "post"
diff: 普及/提高-
pid: CF2036D
tag: ['分类讨论']
---

# I Love 1543

## 题目描述

One morning, Polycarp woke up and realized that $ 1543 $ is the most favorite number in his life.

The first thing that Polycarp saw that day as soon as he opened his eyes was a large wall carpet of size $ n $ by $ m $ cells; $ n $ and $ m $ are even integers. Each cell contains one of the digits from $ 0 $ to $ 9 $ .

Polycarp became curious about how many times the number $ 1543 $ would appear in all layers $ ^{\text{∗}} $ of the carpet when traversed clockwise.

 $ ^{\text{∗}} $ The first layer of a carpet of size $ n \times m $ is defined as a closed strip of length $ 2 \cdot (n+m-2) $ and thickness of $ 1 $ element, surrounding its outer part. Each subsequent layer is defined as the first layer of the carpet obtained by removing all previous layers from the original carpet.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The following lines describe the test cases.

The first line of each test case contains a pair of numbers $ n $ and $ m $ ( $ 2 \leq n, m \leq 10^3 $ , $ n, m $ — even integers).

This is followed by $ n $ lines of length $ m $ , consisting of digits from $ 0 $ to $ 9 $ — the description of the carpet.

It is guaranteed that the sum of $ n \cdot m $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single number — the total number of times $ 1543 $ appears in all layers of the carpet in the order of traversal clockwise.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036D/997bfe25a98d4cf2f508d78ff1490796ddf33705.png) Occurrences of $ 1543 $ in the seventh example. Different layers are colored in different colors.

## 样例 #1

### 输入

```
8
2 4
1543
7777
2 4
7154
8903
2 4
3451
8888
2 2
54
13
2 2
51
43
2 6
432015
512034
4 4
5431
1435
5518
7634
6 4
5432
1152
4542
2432
2302
5942
```

### 输出

```
1
1
0
1
0
2
2
2
```



---

---
title: "MEX Cycle"
layout: "post"
diff: 普及/提高-
pid: CF2049C
tag: ['构造', '分类讨论']
---

# MEX Cycle

## 题目描述

Evirir 这只龙有很多朋友。它有 **3** 个朋友！这比普通龙多一个。

你得到了三个整数 $ n $ , $ x $ 和 $ y $ 。有 $ n $ 只龙围成一个圈坐着。龙从 $ 1 $ 到 $ n $ 编号。对于每个 $ i $ ( $ 1 \le i \le n $ )，龙 $ i $ 与龙 $ i - 1 $ 和 $ i + 1 $ 是朋友，其中龙 $ 0 $ 被定义为龙 $ n $ ，龙 $ n + 1 $ 被定义为龙 $ 1 $ 。此外，龙 $ x $ 和龙 $ y $ 也是朋友（如果它们已经是朋友了，这不会改变任何东西）。请注意，所有的友谊都是相互的。

你需要输出 $ n $ 个非负整数 $ a_1, a_2, \ldots, a_n $ ，使得对于每只龙 $ i $ ( $ 1 \le i \le n $ )，以下条件成立：

- 设 $ f_1, f_2, \ldots, f_k $ 是龙 $ i $ 的朋友。那么 $ a_i = \operatorname{mex}(a_{f_1}, a_{f_2}, \ldots, a_{f_k}) $ 。 $ ^{\text{∗}} $

 $ ^{\text{∗}} $ 集合 $ c_1, c_2, \ldots, c_m $ 的最小排除值 (MEX) 被定义为最小的非负整数 $ t $ ，它不在集合 $ c $ 中出现。

## 输入格式

每个测试用例包含多个测试用例。第一行包含测试用例的数量 $ t $ ( $ 1 \le t \le 10^4 $ )。测试用例的描述如下。

每个测试用例的第一行也是唯一的一行，包含三个整数 $ n $ , $ x $ , $ y $ ( $ 3 \le n \le 2 \cdot 10^5 $ , $ 1 \le x < y \le n $ )。

保证所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。

## 输出格式

对于每个测试用例，输出一行包含 $ n $ 个空格分隔的非负整数 $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ )，满足题目中的条件。如果有多个解，输出任意一个。可以证明，在问题约束下，存在满足 $ 0 \le a_i \le 10^9 $ 的解。

## 说明/提示

对于第一个测试用例：

- $ i = 1 $ : 龙 $ 1 $ 的朋友是龙 $ 2, 3, 5 $  $ \operatorname{mex}(a_2, a_3, a_5) = \operatorname{mex}(2, 1, 1) = 0 = a_1 $ ，所以龙 $ 1 $ 的条件满足
- $ i = 2 $ : 龙 $ 2 $ 的朋友是龙 $ 1, 3 $  $ \operatorname{mex}(a_1, a_3) = \operatorname{mex}(0, 1) = 2 = a_2 $ 
- $ i = 3 $ : 龙 $ 3 $ 的朋友是龙 $ 1, 2, 4 $  $ \operatorname{mex}(a_1, a_2, a_4) = \operatorname{mex}(0, 2, 0) = 1 = a_3 $ 
- $ i = 4 $ : 龙 $ 4 $ 的朋友是龙 $ 3, 5 $  $ \operatorname{mex}(a_3, a_5) = \operatorname{mex}(1, 1) = 0 = a_4 $ 
- $ i = 5 $ : 龙 $ 5 $ 的朋友是龙 $ 1, 4 $  $ \operatorname{mex}(a_1, a_4) = \operatorname{mex}(0, 0) = 1 = a_5 $

## 样例 #1

### 输入

```
7
5 1 3
4 2 4
6 3 5
7 3 6
3 2 3
5 1 5
6 2 5
```

### 输出

```
0 2 1 0 1
1 2 1 0
1 2 0 1 2 0
0 1 2 0 1 0 1
2 0 1
1 0 2 1 0
0 1 2 0 2 1
```



---

---
title: "Trulimero Trulicina"
layout: "post"
diff: 普及/提高-
pid: CF2094F
tag: ['构造', '分类讨论']
---

# Trulimero Trulicina

## 题目描述

Trulicina 给你三个整数 $n$、$m$ 和 $k$。题目保证 $k \geq 2$ 且 $n \cdot m \equiv 0 \pmod{k}$。

请输出一个 $n \times m$ 的整数网格，满足以下所有条件：
- 网格中的每个整数都在 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）。
- 从 $1$ 到 $k$ 的每个整数出现的次数相同。
- 共享一条边的两个单元格不能包含相同的整数。

可以证明这样的网格总是存在。如果存在多个解，输出任意一个即可。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$2 \leq n \cdot m \leq 2 \cdot 10^5$，$2 \leq k \leq n \cdot m$，$n \cdot m \equiv 0 \pmod{k}$）。

保证所有测试用例的 $n \cdot m$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 行，每行包含 $m$ 个满足条件的整数。如果存在多个解，输出任意一个即可。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
2 2 2
3 4 6
5 5 25
```

### 输出

```
1 2
2 1
1 6 1 6
2 5 2 5
3 4 3 4
17 2 12 25 14
3 1 6 19 11
8 20 23 24 4
9 10 5 13 21
22 7 15 18 16
```



---

---
title: "SUMdamental Decomposition"
layout: "post"
diff: 普及/提高-
pid: CF2108B
tag: ['位运算', '分类讨论']
---

# SUMdamental Decomposition

## 题目描述

在最近的一次生日中，你最好的朋友 Maurice 给了你一对数字 $n$ 和 $x$，并要求你构造一个长度为 $n$ 的正数数组 $a$，使得 $a_1 \oplus a_2 \oplus \cdots \oplus a_n = x$ $^{\text{∗}}$。

这个任务对你来说太简单了，因此你决定给 Maurice 一个回礼：在所有满足条件的数组中，构造一个元素和最小的数组。你立刻想到了一个合适的数组；然而，由于把它写下来太费时间，Maurice 只能得到它的元素和。

$^{\text{∗}}$ $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例由一行组成，包含两个数字 $n$ 和 $x$（$1 \le n \le 10^9$，$0 \le x \le 10^9$）——Maurice 给你的数字。

## 输出格式

对于每个测试用例，输出你给 Maurice 的礼物——满足所有描述性质的数组的元素和。如果不存在这样的数组，输出 $-1$。

## 说明/提示

在第一个测试用例中，一个合适的数组是 $[2, 3]$。可以证明无法获得更小的数组元素和。

在第二个测试用例中，一个合适的数组是 $[1, 3, 4]$。同样可以证明这是最优的和。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 1
3 6
1 0
2 0
5 0
2 27
15 43
12345678 9101112
```

### 输出

```
5
8
-1
2
8
27
55
21446778
```



---

