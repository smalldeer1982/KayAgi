---
title: "Maximize the Remaining String"
layout: "post"
diff: 普及+/提高
pid: CF1506G
tag: ['贪心', '单调队列']
---

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 输入格式

多测
第一行一个正整数 $T$（$1\le T\le 10^4$）表示数据组数。  
接下来 $T$ 行，每行一个由小写字母组成的字符串 $s$（$\sum|s|\le 2\times 10^5$）。

## 输出格式

输出 $T$ 行  
对于每组输入的 $s$，输出一行一个字符串表示满足要求且字典序最大的 $t$。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz
```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz
```



---

---
title: "Max GEQ Sum"
layout: "post"
diff: 普及+/提高
pid: CF1691D
tag: ['线段树', '单调队列']
---

# Max GEQ Sum

## 题目描述

现在你有一个由 $n$ 个整数组成的数组 $a$，$(i,j)$ 满足条件当且仅当 $\max (a_i,a_{i+1},\cdots,a_j)\ge a_i+a_{i+1}+\cdots+a_j$，其中 $1\le i\le j\le n$。问是否所有 $(i,j)$ 都满足要求。

## 输入格式

第一行包括一个整数 $t$，表示数据的组数。

每组数据的第一行包括一个整数 $n$，表示数组的长度。

每组数据的第二行为 $n$ 个整数，即为所给出的数组。

保证所有数据的 $n$ 之和不超过 $2\times 10^5$。

## 输出格式

对于每组数据，所有 $(i,j)$ 都符合条件则输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
3
4
-1 1 -1 2
5
-1 2 -3 2 -1
3
2 3 -1
```

### 输出

```
YES
YES
NO
```



---

---
title: "Rudolf and k Bridges"
layout: "post"
diff: 普及+/提高
pid: CF1941E
tag: ['动态规划 DP', '单调队列']
---

# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^3) $ — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ , and $ d $ ( $ 1 \le k \le n \le 100 $ , $ 3 \le m \le 2 \cdot 10^5 $ , $ 1 \le d \le m $ ) — the number of rows and columns of the field, the number of bridges, and the maximum distance between supports.

Then follow $ n $ lines, $ i $ -th line contains $ m $ positive integers $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^6 $ , $ a_{i, 1} = a_{i, m} = 0 $ ) — the depths of the river cells.

It is guaranteed that the sum of $ n \cdot m $ for all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum total cost of supports installation.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0
```

### 输出

```
4
8
4
15
14
```



---

---
title: "Canteen (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2089B1
tag: ['贪心', '单调队列']
---

# Canteen (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中，$$k=0$$。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a\_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$k = 0$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a\_0, a\_1, \ldots, a\_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b\_0, b\_1, \ldots, b\_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$0$$ 所需的最小轮数。


## 说明/提示

在此版本中，Ecrade 不能对 $$$a$$$ 进行修改。

在第一个测试用例中：
- 第一轮操作后，$$a=[0,0,0]$$，$$b=[4,0,0]$$。

在第二个测试用例中：
- 第一轮操作后，$$a=[3,0,0,1]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[1,0,0,0]$$，$$b=[0,1,0,0]$$；
- 第三轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,0,0]$$；
- 第四轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,0,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
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
```

### 输出

```
1
4
4
8
```



---

