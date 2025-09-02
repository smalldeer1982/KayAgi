---
title: "Business trip"
layout: "post"
diff: 入门
pid: CF149A
tag: ['贪心', '排序', '概率论']
---

# Business trip

## 题目描述

多么令人开心啊！Petya的父母去了一个长达一年的商业旅行并且把这个爱玩的孩子独自留下了。Petya高兴到了极点。他跳上床并扔了一整天的枕头，直到...
（这和做题有什么关系，汗）

今天Petya打开橱柜发现了一个吓人的字条。他的父母给他留了家务：他应该给他们最喜爱的花浇一整年的水，每一天，无论早上，下午，还是晚上。“等一下”——Petya想。他明白一个事实，如果他在一年中的第$i$月（$1\leq i\leq12$）完成父母的任务，这个花就会生长$a_i$厘米，并且如果他在第$i$月不给花浇水，花在这个月就不会长。他的父母不会相信他给花浇过水了，如果这花生长的严格少于$k$厘米。

帮助Petya选择最少的月数浇花，使得这花能够长得不少于$k$厘米。

## 输入格式

第一行正好包含一个整数$k$（$0\leq k\leq100$）。下一行包含十二个整数：第$i$个数代表$a_i$（$0\leq a_i\leq100$）

## 输出格式

输出的仅仅一个整数，表示Petya给花浇水的最少月数，使得花生长不少于$k$厘米。如果花一年不能生长$k$厘米，输出$-1$。

## 说明/提示

让我们考虑第一个样例。在第七个月和第九个月给花浇水。然后花长五厘米。

第二样例Petya的父母会相信他，即使花不生长（$k=0$ ）。所以，Petya可能根本不浇花。

Translated by @Khassar

## 样例 #1

### 输入

```
5
1 1 1 1 2 2 3 2 2 1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
0
0 0 0 0 0 0 0 1 1 2 3 0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
11
1 1 4 1 1 5 1 1 4 1 1 1

```

### 输出

```
3

```



---

---
title: "Arithmetic Array"
layout: "post"
diff: 入门
pid: CF1537A
tag: ['贪心']
---

# Arithmetic Array

## 题目描述

An array $ b $ of length $ k $ is called good if its arithmetic mean is equal to $ 1 $ . More formally, if $ $$$\frac{b_1 + \cdots + b_k}{k}=1. $ $ </p><p>Note that the value  $ \\frac{b\_1+\\cdots+b\_k}{k} $  is not rounded up or down. For example, the array  $ \[1,1,1,2\] $  has an arithmetic mean of  $ 1.25 $ , which is not equal to  $ 1 $ .</p><p>You are given an integer array  $ a $  of length  $ n$$$. In an operation, you can append a non-negative integer to the end of the array. What's the minimum number of operations required to make the array good?

We have a proof that it is always possible with finitely many operations.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the length of the initial array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,\ldots,a_n $ ( $ -10^4\leq a_i \leq 10^4 $ ), the elements of the array.

## 输出格式

For each test case, output a single integer — the minimum number of non-negative integers you have to append to the array so that the arithmetic mean of the array will be exactly $ 1 $ .

## 说明/提示

In the first test case, we don't need to add any element because the arithmetic mean of the array is already $ 1 $ , so the answer is $ 0 $ .

In the second test case, the arithmetic mean is not $ 1 $ initially so we need to add at least one more number. If we add $ 0 $ then the arithmetic mean of the whole array becomes $ 1 $ , so the answer is $ 1 $ .

In the third test case, the minimum number of elements that need to be added is $ 16 $ since only non-negative integers can be added.

In the fourth test case, we can add a single integer $ 4 $ . The arithmetic mean becomes $ \frac{-2+4}{2} $ which is equal to $ 1 $ .

## 样例 #1

### 输入

```
4
3
1 1 1
2
1 2
4
8 4 6 2
1
-2
```

### 输出

```
0
1
16
1
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
title: "Two Subsequences"
layout: "post"
diff: 入门
pid: CF1602A
tag: ['贪心']
---

# Two Subsequences

## 题目描述

#### 题意翻译
给你一个字符串 $s$。你需要两个非空字符串 $a$ 和 $b$ 并且满足下面的条件：
1. 字符串 $a$ 和 $b$ 都是 $s$ 的子串。
2. 对于原字符串的每一个字符，必须属于 $a$ 和 $b$ 之一。
3. $a$ 是所有满足条件的字符串中字典序最小的。
给你 $s$，输出 $a$ 和 $b$。

注意：

如果可以通过删除几个(可能为零)元素从 $s$ 获得 a(b)，那么字符串 a(b) 是字符串s的子序列。例如，“Dores”、“cf”和“for”是“codeforces”的子序列，而“Decor”和“fork”则不是。

字符串 $x$ 比字符串 $y$ 字典序小当且仅当 
- $x$ 是 $y$ 的前缀，但 $x\ne y$ 
- 在 $x$ 和 $y$ 不同的第一个位置，$x$ 中的相应字母在字母表中出现的位置早于 $y$ 中的相应字母。

## 输入格式

多组数据。
第一行一个整数 $T$，表示数据组数。对于每组数据，第一行一个字符串 $s$，意义如上文所示。

## 输出格式

对于每组数据，输出满足要求的字符串 $a$，$b$。如果有多个答案，任意输出一个即可。

## 说明/提示

$1\le t\le 1000, 2\le |s| \le 100$
$|s|$ 表示 $s$ 的长度。

译者：@smyslenny

## 样例 #1

### 输入

```
3
fc
aaaa
thebrightboiler
```

### 输出

```
c f
a aaa
b therightboiler
```



---

---
title: "Forbidden Subsequence"
layout: "post"
diff: 入门
pid: CF1617A
tag: ['字符串', '贪心']
---

# Forbidden Subsequence

## 题目描述

You are given strings $ S $ and $ T $ , consisting of lowercase English letters. It is guaranteed that $ T $ is a permutation of the string abc.

Find string $ S' $ , the lexicographically smallest permutation of $ S $ such that $ T $ is not a subsequence of $ S' $ .

String $ a $ is a permutation of string $ b $ if the number of occurrences of each distinct character is the same in both strings.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a string $ S $ ( $ 1 \le |S| \le 100 $ ), consisting of lowercase English letters.

The second line of each test case contains a string $ T $ that is a permutation of the string abc. (Hence, $ |T| = 3 $ ).

Note that there is no limit on the sum of $ |S| $ across all test cases.

## 输出格式

For each test case, output a single string $ S' $ , the lexicographically smallest permutation of $ S $ such that $ T $ is not a subsequence of $ S' $ .

## 说明/提示

In the first test case, both aaaabbc and aaaabcb are lexicographically smaller than aaaacbb, but they contain abc as a subsequence.

In the second test case, abccc is the smallest permutation of cccba and does not contain acb as a subsequence.

In the third test case, bcdis is the smallest permutation of dbsic and does not contain bac as a subsequence.

## 样例 #1

### 输入

```
7
abacaba
abc
cccba
acb
dbsic
bac
abracadabra
abc
dddddddddddd
cba
bbc
abc
ac
abc
```

### 输出

```
aaaacbb
abccc
bcdis
aaaaacbbdrr
dddddddddddd
bbc
ac
```



---

---
title: "Download More RAM"
layout: "post"
diff: 入门
pid: CF1629A
tag: ['贪心', '排序']
---

# Download More RAM

## 题目描述

有一家商店有 $n$ 种不同的软件，可以增加你的内存。第 $i$ 个内存增加软件需要 $a_i$ GB 的内存来运行（这是暂时的。一旦程序运行完毕，您就可以恢复内存），并**永久**提供额外的 $b_i$ GB 内存。**每个软件只能使用一次**。您的电脑当前有 $k$ GB 内存。请注意，如果需要使用比当前更多 GB 的内存，则不能使用内存增加软件。

因为内存是世界上最重要的东西，你想知道，能运行的软件全部运行完后，可以达到的最大内存量是多少？

## 输入格式

输入的第一行包含一个整数 $t$ $(1 \leq t \leq 100)$，为测试用例的数量。测试用例的描述如下：

每个测试用例的第一行包含两个整数 $n$ 和 $k$ $(1 \leq n \leq 100,1 \leq K \leq 1000)$。接下来是两行，每行包含 $n$ 个整数，为数组 $a$ 和 $b$ $(1 \leq a_i,b_i \leq 1000)$。

## 输出格式

对于每个测试用例，输出一行一个整数，为可以达到的最大内存量。

## 样例 #1

### 输入

```
4
3 10
20 30 10
9 100 10
5 1
1 1 5 1 1
1 1 1 1 1
5 1
2 2 2 2 2
100 100 100 100 100
5 8
128 64 32 16 8
128 64 32 16 8
```

### 输出

```
29
6
1
256
```



---

---
title: "GCD Arrays"
layout: "post"
diff: 入门
pid: CF1629B
tag: ['贪心', '最大公约数 gcd']
---

# GCD Arrays

## 题目描述

考虑一下数组 $a$，范围是 $[l,r]$。例如，$[3,7]$，数组 $a$ 就是 $[3,4,5,6,7]$。   
给出 $l,r,k$，询问 $gcd(a)$ 是否能在最多 $k$ 次如下 操作以后比 1 大？
* 在 $a$ 数组中选择两个数。
* 删除这两个数。
* 将这两个数的乘积放回数组 $a$。    

其中，$gcd(b)$ 意思就是 $b$ 数组中数字的[最大公因数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fromtitle=%E6%9C%80%E5%A4%A7%E5%85%AC%E5%9B%A0%E6%95%B0&fromid=869104&fr=aladdin)

## 输入格式

第一行包含一个整数 $t (1 \le t \le 10^5)$，表示数据组数。    

接下来 $t$ 行，每行三个正整数 $l,r,k (1 \le l,r \le 10^9;0 \le k \le r - l)$，含义如题。

## 输出格式

对于每组数据，如果能在 1 到 $k$ 步求出日题意的最大公因数，那么输出
`YES`，否则输出
`NO`。

## 说明/提示

对于样例输入的第 1 组测试数据，$a = [1]$，所以输出
`NO`，因为 1 是数组 $a$ 的唯一元素。   
对于样例输入的第 2 组数据，数组 $a = [3,4,5]$，现在我们有 1 次操作机会。不难发现，无论如何操作，结果只会有 3 个：$[3,20],[4,15],[5,12]$，他们的最大公因数都是 1，没有其他的数，所以输出
`NO`。    

对于样例输入的第 3 组测试数据，$a = [13]$，所以输出
`YES`，因为唯一的元素就是 13，一个质数。

对于样例输入的第 4 组数据，$a = [4]$，输出
`YES`，因为 4 是唯一的元素。

## 样例 #1

### 输入

```
9
1 1 0
3 5 1
13 13 0
4 4 0
3 7 4
4 10 3
2 4 0
1 7 3
1 5 3
```

### 输出

```
NO
NO
YES
YES
YES
YES
NO
NO
YES
```



---

---
title: "Food for Animals"
layout: "post"
diff: 入门
pid: CF1675A
tag: ['贪心']
---

# Food for Animals

## 题目描述

在宠物店出售的商品中有：

- $a$ 包狗粮；

- $b$ 包猫粮；

- $c$ 包通用食物（这种食物既适合狗也适合猫）。

Polycarp 有 $x$ 只狗和 $y$ 只猫。他能从宠物店里为他所有的动物买食物吗？他的每只狗和每只猫都应该得到一包合适的食物。

## 输入格式

输入的第一行包含一个整数 $t$（$ 1 \le t \le 10^4 $）—— 输入中的测试组数。

然后给出 $t$ 行，每行包含一组测试的描述。每组测试由五个整数 $a, b, c, x$ 和 $y$ 组成（$ 0 \le a,b,c,x,y \le 10^8 $）。

## 输出格式

对于每组测试，输出：

- `YES`，如果可以为 $x$ 只狗和 $y$ 只猫购买合适的食物；

- `NO`，不可以。

## 样例 #1

### 输入

```
7
1 1 4 2 3
0 0 0 0 0
5 5 0 4 6
1 1 1 1 1
50000000 50000000 100000000 100000000 100000000
0 0 0 100000000 100000000
1 3 2 2 5
```

### 输出

```
YES
YES
NO
YES
YES
NO
NO
```



---

---
title: "Remove Prefix"
layout: "post"
diff: 入门
pid: CF1714B
tag: ['贪心', '未知标签231']
---

# Remove Prefix

## 题目描述

Polycarp是由一些长度为n的a整数序列组成的（1≤ai≤n）。只有当序列由不同的数字（即不同的数字）组成时，它才能使Polycarp高兴。

为了使他的序列像这样，Polycarp将进行一些移动（可能为零）。

在一个动作中，他可以：

**删除**序列的**第一个（最左侧）元素。**

例如，在一次移动中，序列[3,1,4,3]，将产生由不同数字组成的序列[1,4.3]。

确定他需要移动的最小次数，以便在剩余序列中所有元素都不同。**换句话说，在删除序列中的所有值后，查找给定序列的最小前缀的长度**。

## 输入格式

第一行输入t（1 $\le t \le 10^4$）——测试组数

每个测试输入两行

第一行输入n（1 $\le n \le 2·10^5$）——序列的长度

第二行输入长度为n的a数组$a_1,a_2,…,a_n$（1$ \le a_i \le n$）——序列内容

保证$n$不超过$2·10^5$.

## 输出格式

一行一个当前测试数据变成Polycarp高兴的序列所需的最小步数

## 样例 #1

### 输入

```
5
4
3 1 4 3
5
1 1 1 1 1
1
1
6
6 5 4 3 2 1
7
1 2 1 7 1 2 1
```

### 输出

```
1
4
0
0
5
```



---

---
title: "Joey Takes Money"
layout: "post"
diff: 入门
pid: CF1731A
tag: ['数学', '贪心']
---

# Joey Takes Money

## 题目描述

- **题目翻译如下**

Joey 很穷，因此他的朋友 Chandler 想要借给他一些钱。但是 Joey 的自尊心很强，为了不让他的自尊心受挫又能给他钱，Chandler 打算和他玩一个游戏。   

在这个游戏中，Chandler 会给 Joey 一个数组 $a_1,a_2,\dots,a_n(n\ge 2,a_i \in \mathbb{Z^+})$。Joey 可以对这个数组进行如下的操作任意次：

1. 选择一对 $ i $ 和 $ j $ ( $ 1 \le i < j \le n) $ .
2. 选择两个整数 $ x $ 和 $ y $ ( $ x, y \ge 1 $ ) 使得 $ x \cdot y = a_i \cdot a_j $ .
3. 将 $a_i, a_j$ 分别替换为 $x, y$.

最后， Joey 将得到的钱就是 $a$ 数组中所有值的和。即 Joey 所得的钱 $= \sum^{n}_{i=1}a_{i}$ .

你需要求出一个整数 $ans$，即 Joey 最多可以得到的钱，并输出 $2022 \cdot ans$ 。为什么要乘以 $2022$ 呢？因为我们再也见不到它了！（悲）

输入数据保证 $a$ 数组内所有数的乘积不超过 $10^{12}$，即 $\prod^{n}_{i=1}a_{i} \le 10^{12}$.

## 输入格式

输入包含多组测试数据。  
- 第一行，一个整数 $T$，代表测试数据组数。  
- 对于每一组测试数据，第一行为一个整数 $n(2 \leq n \leq 50)$，表示数组 $a$ 的长度。第二行为 $n$ 个整数 $a_1,a_2,\dots,a_n( 1 \leq a_i \leq 10^6 )$，表示 $a$ 数组。保证 $a$ 数组内所有数的乘积不超过 $10^{12}$，即 $\prod^{n}_{i=1}a_{i} \le 10^{12}$.

## 输出格式

共一行，一个整数，表示 Joey 最多可以得到的钱乘以 2022 后的值。

## 说明/提示

在测试样例的第一组测试数据中，Joey 可以这么做：

- 他选择 $ i = 1 , j = 2 $ (可得 $ a[i] \cdot a[j] = 6 $ ), 使 $ x = 6, y = 1 $ ，然后改变原数组使 $ a[i] = x = 6 , a[j] = y = 1 $ . 即原数组发生如下变化：
$$[2, 3, 2] \xrightarrow[x = 6,\; y = 1]{i = 1,\; j = 2} [6, 1, 2] $$        
- 他选择 $i = 1 , j = 3 $  (可得  $ a[i] \cdot a[j] = 12 $ ), 使 $ x = 12 , y = 1 $  然后改变原数组使 $ a[i] = x = 12 , a[j] = y = 1 $ . 即原数组发生如下变化： 
$$ [6, 1, 2] \xrightarrow[x = 12,; y = 1]{i = 1,\; j = 3} [12, 1, 1] $$

综上所述， Joey 可以得到的最多的钱即为 $12+1+1=14$ 元，所以输出应为 $14\times 2022 = 28308$.

## 样例 #1

### 输入

```
3
3
2 3 2
2
1 3
3
1000000 1000000 1
```

### 输出

```
28308
8088
2022000000004044
```



---

---
title: "Two Groups"
layout: "post"
diff: 入门
pid: CF1747A
tag: ['数学', '贪心']
---

# Two Groups

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You want to distribute these $ n $ integers into two groups $ s_1 $ and $ s_2 $ (groups can be empty) so that the following conditions are satisfied:

- For each $ i $ $ (1 \leq i \leq n) $ , $ a_i $ goes into exactly one group.
- The value $ |sum(s_1)| - |sum(s_2)| $ is the maximum possible among all such ways to distribute the integers.Here $ sum(s_1) $ denotes the sum of the numbers in the group $ s_1 $ , and $ sum(s_2) $ denotes the sum of the numbers in the group $ s_2 $ .

Determine the maximum possible value of $ |sum(s_1)| - |sum(s_2)| $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 2 \cdot 10^4) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 10^5) $ — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2 \ldots a_n $ $ (-10^9 \leq a_i \leq 10^9) $ — elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible value of $ |sum(s_1)| - |sum(s_2)| $ .

## 说明/提示

In the first testcase, we can distribute as $ s_1 = \{10\} $ , $ s_2 = \{-10\} $ . Then the value will be $ |10| - |-10| = 0 $ .

In the second testcase, we can distribute as $ s_1 = \{0, 11, -1\} $ , $ s_2 = \{-2\} $ . Then the value will be $ |0 + 11 - 1| - |-2| = 10 - 2 = 8 $ .

In the third testcase, we can distribute as $ s_1 = \{2, 3, 2\} $ , $ s_2 = \{\} $ . Then the value will be $ |2 + 3 + 2| - |0| = 7 $ .

In the fourth testcase, we can distribute as $ s_1 = \{-9, -4, 0\} $ , $ s_2 = \{2, 0\} $ . Then the value will be $ |-9 - 4 + 0| - |2 + 0| = 13 - 2 = 11 $ .

## 样例 #1

### 输入

```
4
2
10 -10
4
-2 -1 11 0
3
2 3 2
5
-9 2 0 0 -4
```

### 输出

```
0
8
7
11
```



---

---
title: "Indirect Sort"
layout: "post"
diff: 入门
pid: CF1750A
tag: ['贪心']
---

# Indirect Sort

## 题目描述

You are given a permutation $ a_1, a_2, \ldots, a_n $ of size $ n $ , where each integer from $ 1 $ to $ n $ appears exactly once.

You can do the following operation any number of times (possibly, zero):

- Choose any three indices $ i, j, k $ ( $ 1 \le i < j < k \le n $ ).
- If $ a_i > a_k $ , replace $ a_i $ with $ a_i + a_j $ . Otherwise, swap $ a_j $ and $ a_k $ .

Determine whether you can make the array $ a $ sorted in non-descending order.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 10 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1 \le a_i \le n $ , $ a_i \neq a_j $ if $ i \neq j $ ) — the elements of the array $ a $ .

## 输出格式

For each test case, output "Yes" (without quotes) if the array can be sorted in non-descending order, and "No" (without quotes) otherwise.

You can output "Yes" and "No" in any case (for example, strings "YES", "yEs" and "yes" will be recognized as a positive response).

## 说明/提示

In the first test case, $ [1,2,3] $ is already sorted in non-descending order.

In the second test case, we can choose $ i = 1,j = 2,k = 3 $ . Since $ a_1 \le a_3 $ , swap $ a_2 $ and $ a_3 $ , the array then becomes $ [1,2,3] $ , which is sorted in non-descending order.

In the seventh test case, we can do the following operations successively:

- Choose $ i = 5,j = 6,k = 7 $ . Since $ a_5 \le a_7 $ , swap $ a_6 $ and $ a_7 $ , the array then becomes $ [1,2,6,7,4,5,3] $ .
- Choose $ i = 5,j = 6,k = 7 $ . Since $ a_5 > a_7 $ , replace $ a_5 $ with $ a_5+a_6=9 $ , the array then becomes $ [1,2,6,7,9,5,3] $ .
- Choose $ i = 2,j = 5,k = 7 $ . Since $ a_2 \le a_7 $ , swap $ a_5 $ and $ a_7 $ , the array then becomes $ [1,2,6,7,3,5,9] $ .
- Choose $ i = 2,j = 4,k = 6 $ . Since $ a_2 \le a_6 $ , swap $ a_4 $ and $ a_6 $ , the array then becomes $ [1,2,6,5,3,7,9] $ .
- Choose $ i = 1,j = 3,k = 5 $ . Since $ a_1 \le a_5 $ , swap $ a_3 $ and $ a_5 $ , the array then becomes $ [1,2,3,5,6,7,9] $ , which is sorted in non-descending order.

In the third, the fourth, the fifth and the sixth test cases, it can be shown that the array cannot be sorted in non-descending order.

## 样例 #1

### 输入

```
7
3
1 2 3
3
1 3 2
7
5 3 4 7 6 2 1
7
7 6 5 4 3 2 1
5
2 1 4 5 3
5
2 1 3 4 5
7
1 2 6 7 4 3 5
```

### 输出

```
Yes
Yes
No
No
No
No
Yes
```



---

---
title: "Doremy's Paint"
layout: "post"
diff: 入门
pid: CF1764A
tag: ['贪心']
---

# Doremy's Paint

## 题目描述

Doremy has $ n $ buckets of paint which is represented by an array $ a $ of length $ n $ . Bucket $ i $ contains paint with color $ a_i $ .

Let $ c(l,r) $ be the number of distinct elements in the subarray $ [a_l,a_{l+1},\ldots,a_r] $ . Choose $ 2 $ integers $ l $ and $ r $ such that $ l \leq r $ and $ r-l-c(l,r) $ is maximized.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ).

It is guaranteed that the sum of $ n $ does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ l $ and $ r $ such that $ l \leq r $ and $ r-l-c(l,r) $ is maximized.

If there are multiple solutions, you may output any.

## 说明/提示

In the first test case, $ a=[1,3,2,2,4] $ .

- When $ l=1 $ and $ r=3 $ , $ c(l,r)=3 $ (there are $ 3 $ distinct elements in $ [1,3,2] $ ).
- When $ l=2 $ and $ r=4 $ , $ c(l,r)=2 $ (there are $ 2 $ distinct elements in $ [3,2,2] $ ).

It can be shown that choosing $ l=2 $ and $ r=4 $ maximizes the value of $ r-l-c(l,r) $ at $ 0 $ .

For the second test case, $ a=[1,2,3,4,5] $ .

- When $ l=1 $ and $ r=5 $ , $ c(l,r)=5 $ (there are $ 5 $ distinct elements in $ [1,2,3,4,5] $ ).
- When $ l=3 $ and $ r=3 $ , $ c(l,r)=1 $ (there is $ 1 $ distinct element in $ [3] $ ).

It can be shown that choosing $ l=1 $ and $ r=5 $ maximizes the value of $ r-l-c(l,r) $ at $ -1 $ . Choosing $ l=3 $ and $ r=3 $ is also acceptable.

## 样例 #1

### 输入

```
7
5
1 3 2 2 4
5
1 2 3 4 5
4
2 1 2 1
3
2 3 3
2
2 2
1
1
9
9 8 5 2 1 1 2 3 3
```

### 输出

```
2 4
1 5
1 4
2 3
1 2
1 1
3 9
```



---

---
title: "Yet Another Promotion"
layout: "post"
diff: 入门
pid: CF1793A
tag: ['数学', '贪心']
---

# Yet Another Promotion

## 题目描述

The famous store "Second Food" sells groceries only two days a month. And the prices in each of days differ. You wanted to buy $ n $ kilos of potatoes for a month. You know that on the first day of the month $ 1 $ kilo of potatoes costs $ a $ coins, and on the second day $ b $ coins. In "Second Food" you can buy any integer kilograms of potatoes.

Fortunately, "Second Food" has announced a promotion for potatoes, which is valid only on the first day of the month — for each $ m $ kilos of potatoes you buy, you get $ 1 $ kilo as a gift! In other words, you can get $ m + 1 $ kilograms by paying for $ m $ kilograms.

Find the minimum number of coins that you have to spend to buy at least $ n $ kilos of potatoes.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10\,000 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ a $ and $ b $ $ (1 \leq a, b \leq 10^9) $ — the prices of $ 1 $ kilo of potatoes on the first and second days, respectively.

The second line contains two integers $ n $ and $ m $ $ (1 \leq n, m \leq 10^9) $ — the required amount of potatoes to buy and the amount of potatoes to use the promotion.

## 输出格式

For each test case print one integer — the minimum number of coins that you have to pay to buy at least $ n $ kilos of potatoes.

## 说明/提示

In the first test case, on the first day you buy $ 1 $ kilo and get $ 1 $ more for a promotion. On the second day, you can buy $ 1 $ kilo of potatoes. Thus, you will spend $ 5+4=9 $ coins in total.

In the second test case, on the first day you buy $ 2 $ kilo and get another $ 1 $ more for a promotion. This way you will spend $ 2 \cdot 5 = 10 $ coins.

## 样例 #1

### 输入

```
5
5 4
3 1
5 4
3 2
3 4
3 5
20 15
10 2
1000000000 900000000
1000000000 8
```

### 输出

```
9
10
9
135
888888888900000000
```



---

---
title: "Moving Chips"
layout: "post"
diff: 入门
pid: CF1923A
tag: ['贪心']
---

# Moving Chips

## 题目描述

There is a ribbon divided into $ n $ cells, numbered from $ 1 $ to $ n $ from left to right. Each cell either contains a chip or is free.

You can perform the following operation any number of times (possibly zero): choose a chip and move it to the closest free cell to the left. You can choose any chip that you want, provided that there is at least one free cell to the left of it. When you move the chip, the cell where it was before the operation becomes free.

Your goal is to move the chips in such a way that they form a single block, without any free cells between them. What is the minimum number of operations you have to perform?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains one integer $ n $ ( $ 2 \le n \le 50 $ ) — the number of cells;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 1 $ ); $ a_i = 0 $ means that the $ i $ -th cell is free; $ a_i = 1 $ means that the $ i $ -th cell contains a chip.

Additional constraint on the input: in each test case, at least one cell contains a chip.

## 输出格式

For each test case, print one integer — the minimum number of operations you have to perform so that all chips form a single block without any free cells between them.

## 说明/提示

In the first example, you can perform the operation on the chip in the $ 7 $ -th cell. The closest free cell to the left is the $ 5 $ -th cell, so it moves there. After that, all chips form a single block.

In the second example, all chips are already in a single block. Same for the third example.

## 样例 #1

### 输入

```
5
8
0 1 1 1 0 1 1 0
6
0 1 0 0 0 0
6
1 1 1 1 1 1
5
1 0 1 0 1
9
0 1 1 0 0 0 1 1 0
```

### 输出

```
1
0
0
2
3
```



---

---
title: "Turtle Puzzle: Rearrange and Negate"
layout: "post"
diff: 入门
pid: CF1933A
tag: ['贪心']
---

# Turtle Puzzle: Rearrange and Negate

## 题目描述

You are given an array $ a $ of $ n $ integers. You must perform the following two operations on the array (the first, then the second):

1. Arbitrarily rearrange the elements of the array or leave the order of its elements unchanged.
2. Choose at most one contiguous segment of elements and replace the signs of all elements in this segment with their opposites. Formally, you can choose a pair of indices $ l, r $ such that $ 1 \le l \le r \le n $ and assign $ a_i = -a_i $ for all $ l \le i \le r $ (negate elements). Note that you may choose not to select a pair of indices and leave all the signs of the elements unchanged.

What is the maximum sum of the array elements after performing these two operations (the first, then the second)?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ) — the number of elements in array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -100 \le a_i \le 100 $ ) — elements of the array.

## 输出格式

For each test case, output the maximum sum of the array elements after sequentially performing the two given operations.

## 说明/提示

In the first test case, you can first rearrange the array to get $ [3,-2,-3] $ (operation 1), then choose $ l = 2, r = 3 $ and get the sum $ 3 + -((-2) + (-3)) = 8 $ (operation 2).

In the second test case, you can do nothing in both operations and get the sum $ 0 $ .

In the third test case, you can do nothing in both operations and get the sum $ 0 + 1 = 1 $ .

In the fourth test case, you can first leave the order unchanged (operation 1), then choose $ l = 1, r = 1 $ and get the sum $ -(-99) = 99 $ (operation 2).

In the fifth test case, you can first leave the order unchanged (operation 1), then choose $ l = 2, r = 3 $ and get the sum $ 10 + -((-2) + (-3)) + 7 = 22 $ (operation 2).

In the sixth test case, you can first leave the order unchanged (operation 1), then choose $ l = 1, r = 5 $ and get the sum $ -((-1)+(-2)+(-3)+(-4)+(-5))=15 $ (operation 2).

## 样例 #1

### 输入

```
8
3
-2 3 -3
1
0
2
0 1
1
-99
4
10 -2 -3 7
5
-1 -2 -3 -4 -5
6
-41 22 -69 73 -15 -50
12
1 2 3 4 5 6 7 8 9 10 11 12
```

### 输出

```
8
0
1
99
22
15
270
78
```



---

---
title: "Alice and Books"
layout: "post"
diff: 入门
pid: CF1978A
tag: ['贪心', '排序']
---

# Alice and Books

## 题目描述

### 题意翻译
Alice有n本书，第一本书有
$a_1$页，序号为1，第二本书有$a_2$页,序号为2， …… , 第n本书有$a_n$页，序号为n。Alice将把所有书分成两堆，并阅读每一堆中序号最大的一本书。

Alice喜欢读书，请你告诉她，她最多可以读多少页的书。

## 输入格式

一个正整数t（$ 1 \le t\le500$),表示数据组数。

每组数据的第一行一个正整数n（$2 \le n \le 100$)，表示书本的数量.

每组数据的第二行包含n个数，$a_1,a_2,...,a_n$,表示每本书的页数。

## 输出格式

对于每组数据，输出一个正整数,表示Alice可以阅读的最大页数。

## 样例 #1

### 输入

```
5
2
1 1
4
2 3 3 1
5
2 2 3 2 2
2
10 3
3
1 2 3
```

### 输出

```
2
4
5
13
5
```



---

---
title: "Maximize the Last Element"
layout: "post"
diff: 入门
pid: CF1991A
tag: ['贪心']
---

# Maximize the Last Element

## 题目描述

### 题目翻译
你有一个包含 $n$ 个整数的数组 $a$，其中 $n$ 是奇数。

在一次操作中，你将移除数组 $a$ 中的两个相邻元素，然后将数组的剩余部分拼接起来。例如，给定数组 $[4, 7, 4, 2, 9]$，通过操作 $[\underline{4, 7}, 4, 2, 9] \to [4, 2, 9]$ 和 $[4, 7, \underline{4, 2}, 9] \to [4, 7, 9]$，可以分别得到数组 $[4, 2, 9]$ 和 $[4, 7, 9]$。但是，无法通过删除非相邻元素来获得数组 $[7, 2, 9]$，如 $[\underline{4}, 7, \underline{4}, 2, 9]$。

你将重复进行此操作，直到数组 $a$ 中只剩下一个元素。

求剩下的那个元素的最大可能值。

## 输入格式

每个输入包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 99$；$n$ 是奇数）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 100$）——数组 $a$ 的元素。

注意，所有测试用例的 $n$ 总和没有上限。

## 输出格式

对于每个测试用例，输出一个整数，表示数组 $a$ 中剩下的那个元素的最大可能值。

## 说明/提示

在第一个测试用例中，数组 $a$ 是 $[6]$。由于只有一个元素，不需要进行操作。剩下的元素最大可能值是 $6$。
在第二个测试用例中，数组 $a$ 是 $[1, 3, 2]$。我们可以移除前两个元素 $[\underline{1, 3}, 2] \to [2]$，或者移除最后两个元素 $[1, \underline{3, 2}] \to [1]$。因此，剩下的元素最大可能值是 $2$。
在第三个测试用例中，数组 $a$ 是 $[4, 7, 4, 2, 9]$。一种最大化剩下元素的方法是 $[4, \underline{7, 4}, 2, 9] \to [\underline{4, 2}, 9] \to [9]$。因此，剩下的元素最大可能值是 $9$。
在第四个测试用例中，数组 $a$ 是 $[3, 1, 4, 1, 5, 9, 2]$。可以证明剩下的元素最大可能值是 $5$。

## 样例 #1

### 输入

```
4
1
6
3
1 3 2
5
4 7 4 2 9
7
3 1 4 1 5 9 2
```

### 输出

```
6
2
9
5
```



---

---
title: "Turtle and Good Strings"
layout: "post"
diff: 入门
pid: CF2003A
tag: ['贪心']
---

# Turtle and Good Strings

## 题目描述

乌龟认为一个字符串 $ s $ 是一个优良字符串，当且仅当存在一个字符串序列 $ t_1, t_2, \ldots, t_k $ （$ k $ 是任意整数）使满足以下条件：

$ k \ge 2 $ 。
$ s = t_1 + t_2 + \ldots + t_k $，其中 $ + $ 表示连接操作。例如，$\texttt{abc} =texttt{a} + \texttt{bc} $。
对于所有 $ 1 \le i < j \le k ， t_i $ 的首字符不等于 $ t_j $ 的末字符。
乌龟给定了一个由小写拉丁字母组成的字符串 $ s $。请告诉他这个字符串 $ s $ 是否是一个优良字符串！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $ （$ 1 \le t \le 500 $）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $ n $ （$ 2 \le n \le 100 $） — 字符串的长度。

每个测试用例的第二行包含一个长度为 $ n $ 的字符串 $ s $，由小写拉丁字母组成。

## 输出格式

对于每个测试用例，输出 “YES” 如果字符串 $ s $ 是一个优良字符串， 否则输出 “NO”。

你可以以任意形式（大小写）输出答案。例如，字符串 “yEs”, “yes”, “Yes”, 和 “YES” 都会被认为是正面回答。

## 说明/提示

在第一个测试用例中，字符串序列 $\texttt{a}, \texttt{a} $ 满足条件 $ s = t_1 + t_2 + \ldots + t_k $，但 $ t_1 $ 的首字符等于 $ t_2 $ 的末字符。因此可以看出不存在满足所有条件的字符串序列，答案是 “NO”。

在第三个测试用例中，字符串序列 $\texttt{ab}, \texttt{cb} $ 满足所有条件。

在第四个测试用例中，字符串序列 $\texttt{abca}, \texttt{bcab}, \texttt{cabc} $ 满足所有条件。

## 样例 #1

### 输入

```
4
2
aa
3
aba
4
abcb
12
abcabcabcabc
```

### 输出

```
No
nO
Yes
YES
```



---

---
title: "Sakurako's Exam"
layout: "post"
diff: 入门
pid: CF2008A
tag: ['贪心']
---

# Sakurako's Exam

## 题目描述

Sakurako有一场数学考试，老师给了她由$\textbf{a}$个1和$\textbf{b}$个2组成的数组，

在数组中，她**必须**在每一个元素前放置一个'+'或'-'，以便所有元素的总和为$\textbf{0}$。

Sakurako不确定是否有可能解决这个问题，请你确定是否有办法分配符号，使所有元素的总和为0。

## 输入格式

**本题有多组数据**。
第一行一个整数 $T$，表示数据组数。
对于每组数据：
输入一行两个整数a, b，表示数组中1和2的数量。

## 输出格式

对于每组数据，如果你能使和为0输出"Yes"，否则输出"No"。

您可以以任意大小写输出每个字母（小写或大写）。例如，字符串 "yEs"、"yes"、"Yes" 和 "YES" 都将被接受为肯定答案。

## 说明/提示

1. $ a=0 $ , $ b=1 $ : 这意味这数组是 $ [2] $ — 不可能通过添加 '+' 或 '-' 符号得到结果为0；
2. $ a=0 $ , $ b=3 $ : 这意味这数组是 $ [2, 2, 2] $ — 不可能通过添加 '+' 或 '-' 符号得到结果为0；
3. $ a=2 $ , $ b=0 $ : 这意味这数组是 $ [1, 1] $ — 可以通过添加 '+' 或 '-' 符号得到结果为0 (即 $ +1-1=0 $ )；
4. $ a=2 $ , $ b=3 $ : 这意味这数组是 is $ [1, 1, 2, 2, 2] $ — 可以通过添加 '+' 或 '-' 符号得到结果为0 ( 即$ +1+1-2-2+2=0 $ );

## 样例 #1

### 输入

```
5
0 1
0 3
2 0
2 3
3 1
```

### 输出

```
NO
NO
YES
YES
NO
```



---

---
title: "Max Plus Size"
layout: "post"
diff: 入门
pid: CF2019A
tag: ['贪心']
---

# Max Plus Size

## 题目描述

给你一个正整数数组 $a_1,a_2,\cdots,a_n$。

你可以将数组中的一些元素涂成红色，但不能有两个相邻的红色元素（即，对于 $1≤i≤n-1$ ，$a_i$ 和 $a_{i+1}$ 中至少有一个不能是红色的）。

你的分数是红色元素的最大值加上红色元素的数量。求出你能得到的最高分数。

## 输入格式

第一行，一个整数 $t$ ($1 \le t \le 500$)，表示有 $t$ 组数据。

对于每组数据，第一行为一个整数 $n$ ($1 \le n \le 100$)，表示有 $n$ 个整数。

第二行为 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，表示数组。

## 输出格式

共 $t$ 行：对于每组数据，输出你能得到的最大分数。

translate by @[Ekin123](/user/1235038)

## 样例 #1

### 输入

```
4
3
5 4 5
3
4 5 4
10
3 3 3 3 4 1 2 3 4 5
9
17 89 92 42 29 92 14 70 45
```

### 输出

```
7
6
10
97
```



---

---
title: "Profitable Interest Rate"
layout: "post"
diff: 入门
pid: CF2024A
tag: ['数学', '贪心']
---

# Profitable Interest Rate

## 题目描述

Alice 有 $a$ 个硬币。她可以开设一个名为“有利”的银行存款账户，但开设该账户的最低金额要求是 $b$ 个硬币。

还有一种名为“无利”的存款账户，可以用任意数量的硬币开设。Alice 注意到，如果她使用 $x$ 个硬币开设“无利”账户，开设“有利”账户所需的最低金额会减少 $2x$ 个硬币。然而，这些硬币之后不能再存入“有利”账户。

请帮助 Alice 确定她在先向“无利”账户存入一些硬币（可能为 $0$ ）后，最多能向“有利”账户存入多少硬币。如果 Alice 永远无法开设“有利”账户，则输出 $0$。

## 输入格式

**本题有多组测试数据。**

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——表示测试用例的数量。接下来的每个测试用例描述如下。

每个测试用例包含一行，由两个整数 $a$ 和 $b$ 组成（$1 \leq a, b \leq 10^9$）——分别表示 Alice 拥有的硬币数和开设“有利”账户的初始最低要求。

## 输出格式

对于每个测试用例，输出一个整数——Alice 最多能向“有利”账户存入的硬币数。如果 Alice 永远无法开设“有利”账户，则输出 $0$。

## 说明/提示

在第一个测试用例中，$a \geq b$，所以 Alice 可以直接用全部的 10 个硬币开设“有利”账户。

在第二个测试用例中，Alice 可以用 2 个硬币开设“无利”账户。然后她剩下 5 个硬币，而开设“有利”账户的最低要求将减少 4 个硬币，变为 5 个硬币。因此，Alice 将能够用 5 个硬币开设“有利”账户。

在第三个测试用例中，Alice 无法开设“有利”账户。

## 样例 #1

### 输入

```
5
10 5
7 9
5 100
1 1
1 2
```

### 输出

```
10
5
0
1
0
```



---

---
title: "Coin Transformation"
layout: "post"
diff: 入门
pid: CF2043A
tag: ['数学', '贪心']
---

# Coin Transformation

## 题目描述

最开始，你有一枚价值为 $n$ 的硬币。你可以任意多次地执行以下操作：

- 将一枚价值为 $x$ 的硬币（其中 $x > 3$）转换成两枚价值为 $\lfloor \frac{x}{4} \rfloor$ 的硬币。

经过一系列操作后，你最多能得到多少枚硬币？

## 输入格式

第一行输入一个整数 $t$ ($1 \le t \le 10^4$)，表示测试用例的数量。

接下来每个测试用例占一行，包含一个整数 $n$ ($1 \le n \le 10^{18}$)。

## 输出格式

对于每个测试用例，输出一个整数，表示通过任意次数的操作后，你能获得的最大硬币数量。

## 说明/提示

例如，在第一个例子中，你只有一枚价值为 $1$ 的硬币，无法进行任何转换。所以，答案是 $1$。

在第二个例子中，你可以把一枚价值为 $5$ 的硬币转化为两枚价值为 $1$ 的硬币。

在第三个例子中，你可以把一枚价值为 $16$ 的硬币转化为两枚价值为 $4$ 的硬币。然后，每枚价值为 $4$ 的硬币可以继续转化成两枚价值为 $1$ 的硬币。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
5
16
1000000000000000000
```

### 输出

```
1
2
4
536870912
```



---

---
title: "Gellyfish and Tricolor Pansy"
layout: "post"
diff: 入门
pid: CF2116A
tag: ['贪心']
---

# Gellyfish and Tricolor Pansy

## 题目描述

Gellyfish and Flower are playing a game called "Duel".

Gellyfish has $ a $ HP, while Flower has $ b $ HP.

Each of them has a knight. Gellyfish's knight has $ c $ HP, while Flower's knight has $ d $ HP.

They will play a game in rounds until one of the players wins. For $ k = 1, 2, \ldots $ in this order, they will perform the following actions:

- If $ k $ is odd and Gellyfish's knight is alive:
  - Gellyfish's knight can attack Flower and reduce $ b $ by $ 1 $ . If $ b \leq 0 $ , Gellyfish wins. Or,
  - Gellyfish's knight can attack Flower's knight and reduce $ d $ by $ 1 $ . If $ d \leq 0 $ , Flower's knight dies.
- If $ k $ is even and Flower's knight is alive:
  - Flower's knight can attack Gellyfish and reduce $ a $ by $ 1 $ . If $ a \leq 0 $ , Flower wins. Or,
  - Flower's knight can attack Gellyfish's knight and reduce $ c $ by $ 1 $ . If $ c \leq 0 $ , Gellyfish's knight dies.

As one of the smartest people in the world, you want to tell them who will win before the game. Assume both players play optimally.

It can be proven that the game will never end in a draw. That is, one player has a strategy to end the game in a finite number of moves.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 1 \leq a, b, c, d \leq 10^9 $ ) — the HP of Gellyfish, the HP of Flower, the HP of Gellyfish's knight, and the HP of Flower's knight, respectively.

## 输出格式

For each test case, if Flower will win, output "Flower", otherwise output "Gellyfish".

## 说明/提示

In the first test case, Gellyfish has only $ 1 $ HP. Therefore, no matter what Gellyfish does in the first round, Flower's knight will attack Gellyfish in the second round, allowing Flower to win.

In the second test case, Flower's knight has only $ 1 $ HP. Gellyfish will attack Flower's knight in the first round. Then Flower's knight will no longer be able to attack, allowing Gellyfish to win.

## 样例 #1

### 输入

```
5
1 2 3 4
100 999 1 1
10 20 10 30
12 14 13 11
998 244 353 107
```

### 输出

```
Flower
Gellyfish
Flower
Gellyfish
Gellyfish
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

---
title: "Dragons"
layout: "post"
diff: 入门
pid: CF230A
tag: ['贪心', '排序']
---

# Dragons

## 题目描述

小方在跟龙进行比赛，他要是想进入下一层级，就必须要击败在这一层级上的所有的n条龙。 小方和每一条龙都有一个可以用整数表示的力量值，在每一次战斗中，该次战斗的结果由战斗的双方的力量值所决定。在一开始，小方的力量值是s。

在任意一次战斗中，如果小方的力量值比第i条龙（1<=i<=n）的力量值大，那么小方可以击败这头龙并且获得额外的力量值y(i)，如果小方的力量值不大于这头龙的力量值，那么小方将在这场战斗中死亡。

小方可以以任意的一个顺序和龙进行战斗。请编写程序确定小方是否可以继续进入下一层级的比赛，即击败所有的龙族并且自己没有任何损失。

## 输入格式

第一行包括2个用空格分隔的整数s,n,（1<=s<=10000,1<=n<=1000）表示小方初始的力量值和龙的总个数

接下来n行包含2个用空格分开的整数x(i),y(i) 表示第i头龙的力量值以及击败第i头龙可以获得的额外力量值

## 输出格式

一行，如果小方可以进入下一层级，则输出“YES”（不包含引号），否则输出“NO”（不包含引号）。

## 说明/提示

在第一个样例中，小方力量初始值为2，第一条龙的力量值小于2，那么小方将击败他并获得额外的力量值99，此时小方的力量值为2+99=101，大于第二条龙的力量值，小方将击败他，因此小方可以进入下个层级。

在第二个样例中，小方力量初始值为10，小于唯一的一条龙的力量值100，那么小方将无法击败这条龙，因此无法进入下一层级。

感谢@wcy1056935201 提供翻译

## 样例 #1

### 输入

```
2 2
1 99
100 0

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
10 1
100 100

```

### 输出

```
NO

```



---

---
title: "Laptops"
layout: "post"
diff: 入门
pid: CF456A
tag: ['贪心', '枚举', '排序']
---

# Laptops

## 题目描述

有一天Dima和Alex正在讨论关于 $n$ 台笔记本电脑的价格与质量。Dima认为价格高的笔记本质量也高，而Alex认为笔记本是物美价廉，价格低的笔记本质量反而高。

正当他们争（吵）论得不可开交之时，您过来了。现在您需要写出一个程序去确认谁是谁非。

## 输入格式

第一行输入笔记本个数 $n$ $(n \leqslant 10^5)$ 。

接下来的 $n$ 行输入两个数,分别是第 $n$ 个笔记本的价值 $a_i$ 与质量 $b_i$。

保证所有的 $a_i$ 与 $b_i$ 不同，且属于 $int$ 范围。

## 输出格式

如果存在符合Alex的要求的两台笔记本电脑（即一台的价格比另一台低且质量比另一台高），则输出"Happy Alex"，否则输出"Poor Alex"。

翻译提供者：Black_white_tony

## 样例 #1

### 输入

```
2
1 2
2 1

```

### 输出

```
Happy Alex

```



---

---
title: "123-sequence"
layout: "post"
diff: 入门
pid: CF52A
tag: ['数学', '贪心', '概率论']
---

# 123-sequence

## 题目描述

There is a given sequence of integers $ a_{1},a_{2},...,a_{n} $ , where every number is from 1 to 3 inclusively. You have to replace the minimum number of numbers in it so that all the numbers in the sequence are equal to each other.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ). The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=3 $ ).

## 输出格式

Print the minimum number of replacements needed to be performed to make all the numbers in the sequence equal.

## 说明/提示

In the example all the numbers equal to 1 and 3 should be replaced by 2.

## 样例 #1

### 输入

```
9
1 3 2 2 2 1 1 2 3

```

### 输出

```
5

```



---

---
title: "USB Flash Drives"
layout: "post"
diff: 入门
pid: CF609A
tag: ['模拟', '贪心', '排序']
---

# USB Flash Drives

## 题目描述

Sean正在把一个大文件考到n个U盘里。这个文件足有m MB那么大。第i个U盘的容量是a[i]。
假设Sean能把文件分装到多个U盘中，请求出他最少需要用多少个U盘来考这个文件。

## 输入格式

第一行包括一个整数n(1<=n<=100)-U盘的个数。

第二行包含一个整数m(1<=m<=10^5)-文件的大小。

以下n行每一行包括一个整数a[i] (1<=a[i]<=1000)-第i个U盘的大小。

确定答案出现-也就是说所有a[i]的总和不小于m。

## 输出格式

输出至少要多少U盘。

翻译提供者：sunhaina061031

## 样例 #1

### 输入

```
3
5
2
1
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
6
2
3
2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
5
5
10

```

### 输出

```
1

```



---

---
title: "A Student's Dream"
layout: "post"
diff: 入门
pid: CF62A
tag: ['数学', '贪心']
---

# A Student's Dream

## 题目描述

**题目大意：**

有两个人要握手，女孩左手有 $a_l$ 个手指，右手有 $a_r$ 个手指；男孩左手有 $b_l$ 个手指，右手有 $b_r$ 个手指。握手规则为：男孩可以用左手握女孩的右手，也可以用右手握女孩的左手。在女孩的两根手指中间必须有男孩的一根手指，并且男孩的三根手指之间必须有女孩的一根手指。

现在要判断如果可以握手输出 `YES`，不能输出 `NO`。

## 样例 #1

### 输入

```
5 1
10 5

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
3 3

```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 2
11 6

```

### 输出

```
NO
```



---

---
title: "Joysticks"
layout: "post"
diff: 入门
pid: CF651A
tag: ['模拟', '贪心', '递归']
---

# Joysticks

## 题目描述

朋友们正要去玩游戏机。他们有两个游戏机，却只有一个充电器。最开始第一个游戏机有a1%的电，第二个游戏机有a2%的电。你只能在每分钟的最开始将一个游戏机接上充电器。每一分钟每个游戏机会消耗2%的电（如果没有接上充电器）或者充上1%的电（如果接上了充电器）。

当两个游戏机都有电时游戏才能继续。因此，如果在某一分钟的开始某个游戏机只有1%的电，它必须接上充电器，否则游戏会停止。如果某个游戏机完全没电（它的电量变为0），游戏也会停下。

试确定该游戏能够持续的最长时间。禁止暂停游戏，即在每一分钟两个游戏机都应该在使用。允许将游戏机充电到超过100%的电量。

## 输入格式

输入的第一行包括两个正整数a1、a2（1 <= a1、a2 <= 100），分别表示第一个游戏机和第二个游戏机的初始电量。

## 输出格式

输出一个整数，游戏能够持续的最长时间。在某一个游戏机没电之前游戏继续。

感谢@蒟蒻的PSJ 提供的翻译

## 样例 #1

### 输入

```
3 5

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
5

```



---

---
title: "An abandoned sentiment from past"
layout: "post"
diff: 入门
pid: CF814A
tag: ['模拟', '贪心']
---

# An abandoned sentiment from past

## 题目描述

A few years ago, Hitagi encountered a giant crab, who stole the whole of her body weight. Ever since, she tried to avoid contact with others, for fear that this secret might be noticed.

To get rid of the oddity and recover her weight, a special integer sequence is needed. Hitagi's sequence has been broken for a long time, but now Kaiki provides an opportunity.

Hitagi's sequence $ a $ has a length of $ n $ . Lost elements in it are denoted by zeros. Kaiki provides another sequence $ b $ , whose length $ k $ equals the number of lost elements in $ a $ (i.e. the number of zeros). Hitagi is to replace each zero in $ a $ with an element from $ b $ so that each element in $ b $ should be used exactly once. Hitagi knows, however, that, apart from $ 0 $ , no integer occurs in $ a $ and $ b $ more than once in total.

If the resulting sequence is not an increasing sequence, then it has the power to recover Hitagi from the oddity. You are to determine whether this is possible, or Kaiki's sequence is just another fake. In other words, you should detect whether it is possible to replace each zero in $ a $ with an integer from $ b $ so that each integer from $ b $ is used exactly once, and the resulting sequence is not increasing.

## 输入格式

The first line of input contains two space-separated positive integers $ n $ ( $ 2<=n<=100 $ ) and $ k $ ( $ 1<=k<=n $ ) — the lengths of sequence $ a $ and $ b $ respectively.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=200 $ ) — Hitagi's broken sequence with exactly $ k $ zero elements.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{i}<=200 $ ) — the elements to fill into Hitagi's sequence.

Input guarantees that apart from $ 0 $ , no integer occurs in $ a $ and $ b $ more than once in total.

## 输出格式

Output "Yes" if it's possible to replace zeros in $ a $ with elements in $ b $ and make the resulting sequence not increasing, and "No" otherwise.

## 说明/提示

In the first sample:

- Sequence $ a $ is $ 11,0,0,14 $ .
- Two of the elements are lost, and the candidates in $ b $ are $ 5 $ and $ 4 $ .
- There are two possible resulting sequences: $ 11,5,4,14 $ and $ 11,4,5,14 $ , both of which fulfill the requirements. Thus the answer is "Yes".

In the second sample, the only possible resulting sequence is $ 2,3,5,8,9,10 $ , which is an increasing sequence and therefore invalid.

## 样例 #1

### 输入

```
4 2
11 0 0 14
5 4

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
6 1
2 3 0 8 9 10
5

```

### 输出

```
No

```

## 样例 #3

### 输入

```
4 1
8 94 0 4
89

```

### 输出

```
Yes

```

## 样例 #4

### 输入

```
7 7
0 0 0 0 0 0 0
1 2 3 4 5 6 7

```

### 输出

```
Yes

```



---

---
title: "Generate Login"
layout: "post"
diff: 入门
pid: CF909A
tag: ['字符串', '搜索', '贪心', '枚举']
---

# Generate Login

## 题目描述

The preferred way to generate user login in Polygon is to concatenate a prefix of the user's first name and a prefix of their last name, in that order. Each prefix must be non-empty, and any of the prefixes can be the full name. Typically there are multiple possible logins for each person.

You are given the first and the last name of a user. Return the alphabetically earliest login they can get (regardless of other potential Polygon users).

As a reminder, a prefix of a string $ s $ is its substring which occurs at the beginning of $ s $ : "a", "ab", "abc" etc. are prefixes of string "{abcdef}" but "b" and 'bc" are not. A string $ a $ is alphabetically earlier than a string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ and $ b $ coincide up to some position, and then $ a $ has a letter that is alphabetically earlier than the corresponding letter in $ b $ : "a" and "ab" are alphabetically earlier than "ac" but "b" and "ba" are alphabetically later than "ac".

## 输入格式

The input consists of a single line containing two space-separated strings: the first and the last names. Each character of each string is a lowercase English letter. The length of each string is between 1 and 10, inclusive.

## 输出格式

Output a single string — alphabetically earliest possible login formed from these names. The output should be given in lowercase as well.

## 样例 #1

### 输入

```
harry potter

```

### 输出

```
hap

```

## 样例 #2

### 输入

```
tom riddle

```

### 输出

```
tomr

```



---

---
title: "Supermarket"
layout: "post"
diff: 入门
pid: CF919A
tag: ['数学', '贪心', '排序']
---

# Supermarket

## 题目描述

We often go to supermarkets to buy some fruits or vegetables, and on the tag there prints the price for a kilo. But in some supermarkets, when asked how much the items are, the clerk will say that $ a $ yuan for $ b $ kilos (You don't need to care about what "yuan" is), the same as $ a/b $ yuan for a kilo.

Now imagine you'd like to buy $ m $ kilos of apples. You've asked $ n $ supermarkets and got the prices. Find the minimum cost for those apples.

You can assume that there are enough apples in all supermarkets.

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=5000 $ , $ 1<=m<=100 $ ), denoting that there are $ n $ supermarkets and you want to buy $ m $ kilos of apples.

The following $ n $ lines describe the information of the supermarkets. Each line contains two positive integers $ a,b $ ( $ 1<=a,b<=100 $ ), denoting that in this supermarket, you are supposed to pay $ a $ yuan for $ b $ kilos of apples.

## 输出格式

The only line, denoting the minimum cost for $ m $ kilos of apples. Please make sure that the absolute or relative error between your answer and the correct answer won't exceed $ 10^{-6} $ .

Formally, let your answer be $ x $ , and the jury's answer be $ y $ . Your answer is considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919A/9c418c1ac059184ac2ec8107da47a63db7a44091.png).

## 说明/提示

In the first sample, you are supposed to buy $ 5 $ kilos of apples in supermarket $ 3 $ . The cost is $ 5/3 $ yuan.

In the second sample, you are supposed to buy $ 1 $ kilo of apples in supermarket $ 2 $ . The cost is $ 98/99 $ yuan.

## 样例 #1

### 输入

```
3 5
1 2
3 4
1 3

```

### 输出

```
1.66666667

```

## 样例 #2

### 输入

```
2 1
99 100
98 99

```

### 输出

```
0.98989899

```



---

---
title: "Diverse Team"
layout: "post"
diff: 入门
pid: CF988A
tag: ['模拟', '贪心', '概率论']
---

# Diverse Team

## 题目描述

给定n和k和n个元素的数列，请在这个数列中找k个不同的元素。
如果可行，则输出“YES”和其中一个答案（可能有多个答案）的元素编号。
否则输出“NO”。


感谢@南方不败 提供翻译

## 输入格式

第一行n和k，第二行n个数。

## 样例 #1

### 输入

```
5 3
15 13 15 15 12

```

### 输出

```
YES
1 2 5 

```

## 样例 #2

### 输入

```
5 4
15 13 15 15 12

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4 4
20 10 40 30

```

### 输出

```
YES
1 2 3 4 

```



---

