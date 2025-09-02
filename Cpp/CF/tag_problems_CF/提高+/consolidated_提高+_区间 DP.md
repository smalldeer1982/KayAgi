---
title: "Clear the String"
layout: "post"
diff: 提高+/省选-
pid: CF1132F
tag: ['动态规划 DP', '区间 DP']
---

# Clear the String

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin letters. You may apply some operations to this string: in one operation you can delete some contiguous substring of this string, if all letters in the substring you delete are equal. For example, after deleting substring bbbb from string abbbbaccdd we get the string aaccdd.

Calculate the minimum number of operations to delete the whole string $ s $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 500 $ ) — the length of string $ s $ .

The second line contains the string $ s $ ( $ |s| = n $ ) consisting of lowercase Latin letters.

## 输出格式

Output a single integer — the minimal number of operation to delete string $ s $ .

## 样例 #1

### 输入

```
5
abaca

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8
abcddcba

```

### 输出

```
4

```



---

---
title: "Coloring Brackets"
layout: "post"
diff: 提高+/省选-
pid: CF149D
tag: ['搜索', '记忆化搜索', '区间 DP']
---

# Coloring Brackets

## 题目描述

### 题意描述

给出一个配对的括号序列（如 “$\texttt{(())()}$”、“$\texttt{()}$” 等，“$\texttt{)()}$”、“$\texttt{(()}$”是不符合要求的），对该序列按照以下方法染色。

1. 一个括号可以染成红色、蓝色或者不染色。
2. 一对匹配的括号需要且只能将其中一个染色。
3. 相邻两个括号颜色不能相同（但都可以不染色）。

求符合条件的染色方案数，对 $1000000007$ 取模。

## 输入格式

一行一个字符串 $s$，表示括号序列（$2 \leqslant |s| \leqslant 700$）。

## 输出格式

一个数字，表示染色的方案数（对 $1000000007$ 取模）。

## 样例 #1

### 输入

```
(())

```

### 输出

```
12

```

## 样例 #2

### 输入

```
(()())

```

### 输出

```
40

```

## 样例 #3

### 输入

```
()

```

### 输出

```
4

```



---

---
title: "Phoenix and Computers"
layout: "post"
diff: 提高+/省选-
pid: CF1515E
tag: ['动态规划 DP', '区间 DP', '生成函数']
---

# Phoenix and Computers

## 题目描述

There are $ n $ computers in a row, all originally off, and Phoenix wants to turn all of them on. He will manually turn on computers one at a time. At any point, if computer $ i-1 $ and computer $ i+1 $ are both on, computer $ i $ $ (2 \le i \le n-1) $ will turn on automatically if it is not already on. Note that Phoenix cannot manually turn on a computer that already turned on automatically.

If we only consider the sequence of computers that Phoenix turns on manually, how many ways can he turn on all the computers? Two sequences are distinct if either the set of computers turned on manually is distinct, or the order of computers turned on manually is distinct. Since this number may be large, please print it modulo $ M $ .

## 输入格式

The first line contains two integers $ n $ and $ M $ ( $ 3 \le n \le 400 $ ; $ 10^8 \le M \le 10^9 $ ) — the number of computers and the modulo. It is guaranteed that $ M $ is prime.

## 输出格式

Print one integer — the number of ways to turn on the computers modulo $ M $ .

## 说明/提示

In the first example, these are the $ 6 $ orders in which Phoenix can turn on all computers:

- $ [1,3] $ . Turn on computer $ 1 $ , then $ 3 $ . Note that computer $ 2 $ turns on automatically after computer $ 3 $ is turned on manually, but we only consider the sequence of computers that are turned on manually.
- $ [3,1] $ . Turn on computer $ 3 $ , then $ 1 $ .
- $ [1,2,3] $ . Turn on computer $ 1 $ , $ 2 $ , then $ 3 $ .
- $ [2,1,3] $
- $ [2,3,1] $
- $ [3,2,1] $

## 样例 #1

### 输入

```
3 100000007
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 100000007
```

### 输出

```
20
```

## 样例 #3

### 输入

```
400 234567899
```

### 输出

```
20914007
```



---

---
title: "Almost Triple Deletions"
layout: "post"
diff: 提高+/省选-
pid: CF1699D
tag: ['贪心', '区间 DP']
---

# Almost Triple Deletions

## 题目描述

You are given an integer $ n $ and an array $ a_1,a_2,\ldots,a_n $ .

In one operation, you can choose an index $ i $ ( $ 1 \le i \lt n $ ) for which $ a_i \neq a_{i+1} $ and delete both $ a_i $ and $ a_{i+1} $ from the array. After deleting $ a_i $ and $ a_{i+1} $ , the remaining parts of the array are concatenated.

For example, if $ a=[1,4,3,3,6,2] $ , then after performing an operation with $ i=2 $ , the resulting array will be $ [1,3,6,2] $ .

What is the maximum possible length of an array of equal elements obtainable from $ a $ by performing several (perhaps none) of the aforementioned operations?

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10\,000 $ .

## 输出格式

For each testcase, print a single integer, the maximum possible length of an array of equal elements obtainable from $ a $ by performing a sequence of operations.

## 说明/提示

For the first testcase, an optimal sequence of operations would be: $ [1,2,3,2,1,3,3] \rightarrow [3,2,1,3,3] \rightarrow [3,3,3] $ .

For the second testcase, all elements in the array are already equal.

For the third testcase, the only possible sequence of operations is: $ [1,1,1,2,2,2] \rightarrow [1,1,2,2] \rightarrow [1,2] \rightarrow [] $ . Note that, according to the statement, the elements deleted at each step must be different.

For the fourth testcase, the optimal sequence of operations is: $ [1,1,2,2,3,3,1,1] \rightarrow [1,1,2,3,1,1] \rightarrow [1,1,1,1] $ .

For the fifth testcase, one possible reachable array of two equal elements is $ [4,4] $ .

## 样例 #1

### 输入

```
5
7
1 2 3 2 1 3 3
1
1
6
1 1 1 2 2 2
8
1 1 2 2 3 3 1 1
12
1 5 2 3 3 3 4 4 4 4 3 3
```

### 输出

```
3
1
0
4
2
```



---

---
title: "Hossam and (sub-)palindromic tree"
layout: "post"
diff: 提高+/省选-
pid: CF1771D
tag: ['树形数据结构', '区间 DP']
---

# Hossam and (sub-)palindromic tree

## 题目描述

Hossam has an unweighted tree $ G $ with letters in vertices.

Hossam defines $ s(v, \, u) $ as a string that is obtained by writing down all the letters on the unique simple path from the vertex $ v $ to the vertex $ u $ in the tree $ G $ .

A string $ a $ is a subsequence of a string $ s $ if $ a $ can be obtained from $ s $ by deletion of several (possibly, zero) letters. For example, "dores", "cf", and "for" are subsequences of "codeforces", while "decor" and "fork" are not.

A palindrome is a string that reads the same from left to right and from right to left. For example, "abacaba" is a palindrome, but "abac" is not.

Hossam defines a sub-palindrome of a string $ s $ as a subsequence of $ s $ , that is a palindrome. For example, "k", "abba" and "abhba" are sub-palindromes of the string "abhbka", but "abka" and "cat" are not.

Hossam defines a maximal sub-palindrome of a string $ s $ as a sub-palindrome of $ s $ , which has the maximal length among all sub-palindromes of $ s $ . For example, "abhbka" has only one maximal sub-palindrome — "abhba". But it may also be that the string has several maximum sub-palindromes: the string "abcd" has $ 4 $ maximum sub-palindromes.

Help Hossam find the length of the longest maximal sub-palindrome among all $ s(v, \, u) $ in the tree $ G $ .

Note that the sub-palindrome is a subsequence, not a substring.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 200 $ ) — the number of test cases.

The first line of each test case has one integer number $ n $ ( $ 1 \le n \le 2 \cdot 10^3 $ ) — the number of vertices in the graph.

The second line contains a string $ s $ of length $ n $ , the $ i $ -th symbol of which denotes the letter on the vertex $ i $ . It is guaranteed that all characters in this string are lowercase English letters.

The next $ n - 1 $ lines describe the edges of the tree. Each edge is given by two integers $ v $ and $ u $ ( $ 1 \le v, \, u \le n $ , $ v \neq u $ ). These two numbers mean that there is an edge $ (v, \, u) $ in the tree. It is guaranteed that the given edges form a tree.

It is guaranteed that sum of all $ n $ doesn't exceed $ 2 \cdot 10^3 $ .

## 输出格式

For each test case output one integer — the length of the longest maximal sub-palindrome among all $ s(v, \, u) $ .

## 说明/提示

In the first example the maximal subpalindromes are "aaa" with letters in vertices $ 1, \, 3, \, 5 $ , or "aca" with letters in vertices $ 1, \, 4, \, 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/2a7d49fbfdc47b629dbea5a5d05163d26e820257.png) The tree from the first example.In the second example there is only one maximal palindrome "bacab" with letters in vertices $ 4, \, 2, \, 1, \, 5, \, 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/1a3ef86962248c5a486bd8acba156707a2fa8aec.png) The tree from the second example.

## 样例 #1

### 输入

```
2
5
abaca
1 2
1 3
3 4
4 5
9
caabadedb
1 2
2 3
2 4
1 5
5 6
5 7
5 8
8 9
```

### 输出

```
3
5
```



---

---
title: "Game With Triangles: Season 2"
layout: "post"
diff: 提高+/省选-
pid: CF2074G
tag: ['区间 DP']
---

# Game With Triangles: Season 2

## 题目描述

Frontman 欢迎你来到这场生存游戏的最终回合。给定一个具有 $n$ 条边的正则多边形（$n \ge 3$），其顶点按顺时针顺序编号为 $1,2,\ldots,n$。每个顶点 $i$ 上被粉色士兵写有一个正整数 $a_i$。你需要基于这个正则多边形进行如下定义的游戏。

初始时你的得分为 $0$。你可以通过以下操作任意次来增加得分：

- 选择三个未被选择过的不同顶点 $i$、$j$、$k$，并绘制这三个顶点形成的三角形。
  - 此时你的得分增加 $a_i \cdot a_j \cdot a_k$。
  - 但若该三角形与之前绘制的任意三角形存在正面积的公共区域，则不能执行此操作。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074G/55083de687b4289529b3eb64dfe6b29a4f1f6e75.png)  

左图为两次操作后的合法状态，右图状态不合法，因为两个三角形存在正面积的公共区域。  
你的目标是最大化得分。请计算你在这场游戏中能获得的最大得分。


## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$ —— 顶点数量（$3 \le n \le 400$）。

每个测试用例的第二行包含 $a_1,a_2,\ldots,a_n$ —— 顶点上的整数（$1 \le a_i \le 1000$）。

保证所有测试用例的 $n^3$ 之和不超过 $400^3$。

## 输出格式

对于每个测试用例，在单独一行中输出可获得的最大得分。

## 说明/提示

第一个测试用例中，只能绘制一个三角形。选择 $i=1$、$j=2$、$k=3$ 的三角形可得最大得分 $6$。

第二个测试用例中，只能绘制一个三角形。选择 $i=1$、$j=3$、$k=4$ 的三角形可得最大得分 $24$。

第三个测试用例中，可以绘制两个三角形。通过两次操作可得最大得分 $5$。

第四个测试用例中，可以绘制两个三角形。但绘制两次得分可能为 $6+5=11$、$15+2=17$ 或 $10+3=13$。选择仅绘制 $i=2$、$j=4$、$k=6$ 的三角形可得最大得分 $30$。

第五个测试用例中，可以绘制三个三角形。通过以下方式绘制三个三角形可得最大得分 $732$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074G/51aa3904604e991d60da4548ed36f974e23a2cf2.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3
1 2 3
4
2 1 3 4
6
2 1 2 1 1 1
6
1 2 1 3 1 5
9
9 9 8 2 4 4 3 5 3
9
9 9 3 2 4 4 8 5 3
```

### 输出

```
6
24
5
30
732
696
```



---

---
title: "Zuma"
layout: "post"
diff: 提高+/省选-
pid: CF607B
tag: ['字符串', '搜索', '记忆化搜索', '区间 DP']
---

# Zuma

## 题目描述

$\texttt{Genos}$ 最近在他的手机上下载了祖玛游戏。在祖玛游戏里，存在 $n$ 个一行的宝石，第 $i$ 个宝石的颜色是 $C_i$。这个游戏的目标是尽快的消灭一行中所有的宝石。

在一秒钟，$\texttt{Genos}$ 能很快的挑选出这些有颜色的宝石中的一个回文的、连续的子串，并将这个子串移除。每当一个子串被删除后，剩余的宝石将连接在一起，形成一个新的行列。

你的任务是：求出把整个宝石串都移除的最短时间。

## 输入格式

第一行包含一个整数 $n(1 \le n \le 500)$，表示宝石串的长度。第二行包含 $n$ 个被空格分开的整数，第 $i(1 \le i \le n)$ 个表示这行中第 $i$ 个珠子的颜色。

## 输出格式

输出一个整数，把这行珠子移除的最短时间。

## 说明/提示

在第一个例子中，$\texttt{Genos}$ 可以在一秒钟就把这行珠子全部移走。在第二个例子中，$\texttt{Genos}$ 一次只能移走一个珠子，所以移走三个珠子花费他三秒。在第三个例子中，为了达到 $2$ 秒的最快时间，先移除回文串 $\texttt{4 4}$,再移除回文串 $\texttt{1 2 3 2 1}$。

感谢 @Administrator2004 提供的翻译

## 样例 #1

### 输入

```
3
1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
1 4 4 2 3 2 1

```

### 输出

```
2

```



---

