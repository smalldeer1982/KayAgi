---
title: "2..3...4.... Wonderful! Wonderful!"
layout: "post"
diff: 省选/NOI-
pid: CF1930E
tag: ['组合数学', '排列组合']
---

# 2..3...4.... Wonderful! Wonderful!

## 题目描述

Stack has an array $ a $ of length $ n $ such that $ a_i = i $ for all $ i $ ( $ 1 \leq i \leq n $ ). He will select a positive integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ) and do the following operation on $ a $ any number (possibly $ 0 $ ) of times.

- Select a subsequence $ ^\dagger $ $ s $ of length $ 2 \cdot k + 1 $ from $ a $ . Now, he will delete the first $ k $ elements of $ s $ from $ a $ . To keep things perfectly balanced (as all things should be), he will also delete the last $ k $ elements of $ s $ from $ a $ .

Stack wonders how many arrays $ a $ can he end up with for each $ k $ ( $ 1 \leq k \leq \lfloor \frac{n-1}{2} \rfloor $ ). As Stack is weak at counting problems, he needs your help.

Since the number of arrays might be too large, please print it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements. For example, $ [1, 3] $ , $ [1, 2, 3] $ and $ [2, 3] $ are subsequences of $ [1, 2, 3] $ . On the other hand, $ [3, 1] $ and $ [2, 1, 3] $ are not subsequences of $ [1, 2, 3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^6 $ ) — the length of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test, on a new line, print $ \lfloor \frac{n-1}{2} \rfloor $ space-separated integers — the $ i $ -th integer representing the number of arrays modulo $ 998\,244\,353 $ that Stack can get if he selects $ k=i $ .

## 说明/提示

In the first test case, two $ a $ are possible for $ k=1 $ :

- $ [1,2,3] $ ;
- $ [2] $ .

In the second test case, four $ a $ are possible for $ k=1 $ :

- $ [1,2,3,4] $ ;
- $ [1,3] $ ;
- $ [2,3] $ ;
- $ [2,4] $ .

In the third test case, two $ a $ are possible for $ k=2 $ :

- $ [1,2,3,4,5] $ ;
- $ [3] $ .

## 样例 #1

### 输入

```
4
3
4
5
10
```

### 输出

```
2 
4 
10 2 
487 162 85 10
```



---

---
title: "The Destruction of the Universe (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G1
tag: ['组合数学', '排列组合']
---

# The Destruction of the Universe (Easy Version)

## 题目描述

这是问题的简单版本，满足 $ n \leq 5000 $。如果两个版本的问题都被解决，才可以进行挑战。

猩猩是强大的生物，它们只需要 $1$ 个单位时间就能摧毁宇宙中每一个脆弱的星球！

宇宙中有 $n$ 个星球。每个星球在一个区间 $[l, r]$ 内是脆弱的，期间随时可能被猩猩摧毁。猩猩可以把任意一个星球的脆弱区间扩展 $1$ 个单位。

具体来说，如果对某个星球 $p$ 的脆弱区间 $[l_p, r_p]$ 进行扩展，结果可以是 $[l_p - 1, r_p]$ 或 $[l_p, r_p + 1]$ 中的任一个。

给定一组星球，如果它们的所有脆弱区间中至少有一个共同点，那么这组星球就能被摧毁。我们把这样一组星球的“得分”定义为实现摧毁所需的最小扩展次数。

猩猩关注的是宇宙中所有非空星球子集的得分之和。由于可能结果非常大，请输出答案对 $998\,244\,353$ 取模后的结果。

## 输入格式

第一行是一个整数 $t$（$1 \leq t \leq 1000$）——测试用例的数量。

每个测试用例的第一行有一个整数 $n$（$1 \leq n \leq 5000$）——星球的数量。

接下来的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq n$），表示第 $i$ 个星球的初始脆弱区间。

保证所有测试用例中，星球数量的总和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——所有非空星球子集的得分之和，对 $998\,244\,353$ 取模。

## 说明/提示

以第一个测试用例为例，需考虑以下七个非空子集：

- 对于子集 $\{[1,1]\}, \{[2,3]\}, \{[3,3]\}$，得分为 $0$。
- 对于子集 $\{[2,3], [3,3]\}$，得分为 $0$，因为点 $3$ 已经位于这两个星球的脆弱区间之内。
- 对于子集 $\{[1,1], [2,3]\}$，得分为 $1$。通过一次操作，将第二个星球的脆弱区间改为 $[1,3]$，这样两个星球的脆弱区间都包含点 $1$。
- 对于子集 $\{[1,1], [3,3]\}$，得分为 $2$。通过两次操作，将第一个星球的脆弱区间改为 $[1,3]$，使得两个星球的区间都包含点 $3$。
- 对于子集 $\{[1,1], [2,3], [3,3]\}$，得分为 $2$。通过一次操作把第一个星球的区间改为 $[1,2]$，再用一次操作把第三个星球的区间改为 $[2,3]$，这样三个星球都包含点 $2$。

所以，第一个测试用例中，所有非空子集的得分之和为 $0 \times 4 + 1 \times 1 + 2 \times 2 = 5$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "The Destruction of the Universe (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G2
tag: ['组合数学', '排列组合', '前缀和']
---

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of planets in the universe.

The following $ n $ lines contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ) — the initial interval of vulnerability of the $ i $ -th planet.

It is guaranteed that the sum of $ n $ does not exceed $ 10^6 $ over all test cases.

## 输出格式

For each test case, output an integer — the sum of scores to destroy all non-empty subsets of the planets in the universe, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

