---
title: "Odd Federalization"
layout: "post"
diff: 省选/NOI-
pid: CF1070L
tag: ['高斯消元', '构造']
---

# Odd Federalization

## 题目描述

Berland has $ n $ cities, some of which are connected by roads. Each road is bidirectional, connects two distinct cities and for each two cities there's at most one road connecting them.

The president of Berland decided to split country into $ r $ states in such a way that each city will belong to exactly one of these $ r $ states.

After this split each road will connect either cities of the same state or cities of the different states. Let's call roads that connect two cities of the same state "inner" roads.

The president doesn't like odd people, odd cities and odd numbers, so he wants this split to be done in such a way that each city would have even number of "inner" roads connected to it.

Please help president to find smallest possible $ r $ for which such a split exists.

## 输入格式

The input contains one or several test cases. The first input line contains a single integer number $ t $ — number of test cases. Then, $ t $ test cases follow. Solve test cases separately, test cases are completely independent and do not affect each other.

Then $ t $ blocks of input data follow. Each block starts from empty line which separates it from the remaining input data. The second line of each block contains two space-separated integers $ n $ , $ m $ ( $ 1 \le n \le 2000 $ , $ 0 \le m \le 10000 $ ) — the number of cities and number of roads in the Berland. Each of the next $ m $ lines contains two space-separated integers — $ x_i $ , $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ), which denotes that the $ i $ -th road connects cities $ x_i $ and $ y_i $ . Each pair of cities are connected by at most one road.

Sum of values $ n $ across all test cases doesn't exceed $ 2000 $ . Sum of values $ m $ across all test cases doesn't exceed $ 10000 $ .

## 输出格式

For each test case first print a line containing a single integer $ r $ — smallest possible number of states for which required split is possible. In the next line print $ n $ space-separated integers in range from $ 1 $ to $ r $ , inclusive, where the $ j $ -th number denotes number of state for the $ j $ -th city. If there are multiple solutions, print any.

## 样例 #1

### 输入

```
2
 
5 3
1 2
2 5
1 5
 
6 5
1 2
2 3
3 4
4 2
4 1

```

### 输出

```
1
1 1 1 1 1 
2
2 1 1 1 1 1

```



---

---
title: "Homework"
layout: "post"
diff: 省选/NOI-
pid: CF2097D
tag: ['数学', '线性代数', '高斯消元', '标签465']
---

# Homework

## 题目描述

有些老师在"天狼星"教育中心工作的同时还在大学学习。这种情况下，出差并不能免除他们完成作业的义务，因此他们直接在飞机上做作业。Artem 就是这样一位老师，他在大学被布置了以下作业。

对于任意长度为偶数 $m$ 的字符串 $a$，他可以执行以下操作。Artem 将字符串 $a$ 分成两个长度相等的部分 $x$ 和 $y$，然后执行以下三种操作之一：

- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $x_i = (x_i + y_i) \bmod 2$；
- 对于每个 $i \in \left\{ 1, 2, \ldots, \frac{m}{2}\right\}$，令 $y_i = (x_i + y_i) \bmod 2$；
- 对字符串 $x$ 和 $y$ 分别执行任意次数的上述操作（递归应用），注意此时 $x$ 和 $y$ 的长度必须为偶数。

操作完成后，字符串 $a$ 将被替换为按原顺序连接的 $x$ 和 $y$。不幸的是，Artem 在飞机上睡着了，所以你需要替他完成作业。Artem 有两个长度为 $n$ 的二进制字符串 $s$ 和 $t$，每个字符串都由 $n$ 个字符 0 或 1 组成。请判断是否可以通过任意次数的操作使字符串 $s$ 等于字符串 $t$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^5$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^6$）——字符串 $s$ 和 $t$ 的长度。

每个测试用例的第二行包含长度为 $n$ 的字符串 $s$，仅由字符 0 和 1 组成。

每个测试用例的第三行包含长度为 $n$ 的字符串 $t$，仅由字符 0 和 1 组成。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，如果可以使字符串 $s$ 等于字符串 $t$，则输出 "Yes"（不带引号），否则输出 "No"。

答案大小写不敏感。例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被接受为肯定回答。


## 说明/提示

在第一个测试用例中，字符串 00001001 可以通过两次操作转换为 10101001。操作序列如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2097D/168d2d9e52ff66afe40aa42de1043dc65663a285.png)

在第二个测试用例中，字符串 00000000 无法转换为除自身外的任何其他字符串，因为在任何操作中都无法产生非零元素。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
8
00001001
10101001
8
00000000
00001001
6
010110
100010
```

### 输出

```
Yes
No
Yes
```



---

---
title: "Broken robot"
layout: "post"
diff: 省选/NOI-
pid: CF24D
tag: ['动态规划 DP', '期望', '高斯消元']
---

# Broken robot

## 题目描述

## 题意翻译
$n$ 行 $m$ 列的矩阵，现在在 $(x,y)$，每次等概率向左，右，下走或原地不动，但不能走出去，问走到最后一行期望的步数。

注意，$(1,1)$ 是木板的左上角，$(n,m)$ 是木板的右下角。

## 输入格式

第一行为两个整数 $n,m$。

第二行为两个整数 $x,y$。

## 输出格式

一行，输出所需移动步数的数学期望值，至少保留 $4$ 位小数的值。

## 说明/提示

$1\le n,m\le 10^3$，$1\le x\le n$，$1\le y\le m$。

## 样例 #1

### 输入

```
10 10
10 4

```

### 输出

```
0.0000000000

```

## 样例 #2

### 输入

```
10 14
5 14

```

### 输出

```
18.0038068653

```



---

