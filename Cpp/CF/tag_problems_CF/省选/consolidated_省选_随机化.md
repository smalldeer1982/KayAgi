---
title: "GCD Groups 2"
layout: "post"
diff: 省选/NOI-
pid: CF1198F
tag: ['动态规划 DP', '状态合并', '随机化']
---

# GCD Groups 2

## 题目描述

You are given an array of $ n $ integers. You need to split all integers into two groups so that the GCD of all integers in the first group is equal to one and the GCD of all integers in the second group is equal to one.

The GCD of a group of integers is the largest non-negative integer that divides all the integers in the group.

Both groups have to be non-empty.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array.

## 输出格式

In the first line print "YES" (without quotes), if it is possible to split the integers into two groups as required, and "NO" (without quotes) otherwise.

If it is possible to split the integers, in the second line print $ n $ integers, where the $ i $ -th integer is equal to $ 1 $ if the integer $ a_i $ should be in the first group, and $ 2 $ otherwise.

If there are multiple solutions, print any.

## 样例 #1

### 输入

```
4
2 3 6 7

```

### 输出

```
YES
2 2 1 1 

```

## 样例 #2

### 输入

```
5
6 15 35 77 22

```

### 输出

```
YES
2 1 2 1 1 

```

## 样例 #3

### 输入

```
5
6 10 15 1000 75

```

### 输出

```
NO

```



---

---
title: "James and the Chase"
layout: "post"
diff: 省选/NOI-
pid: CF1361E
tag: ['Tarjan', '随机化']
---

# James and the Chase

## 题目描述

James Bond has a new plan for catching his enemy. There are some cities and directed roads between them, such that it is possible to travel between any two cities using these roads. When the enemy appears in some city, Bond knows her next destination but has no idea which path she will choose to move there.

The city $ a $ is called interesting, if for each city $ b $ , there is exactly one simple path from $ a $ to $ b $ . By a simple path, we understand a sequence of distinct cities, such that for every two neighboring cities, there exists a directed road from the first to the second city.

Bond's enemy is the mistress of escapes, so only the chase started in an interesting city gives the possibility of catching her. James wants to arrange his people in such cities. However, if there are not enough interesting cities, the whole action doesn't make sense since Bond's people may wait too long for the enemy.

You are responsible for finding all the interesting cities or saying that there is not enough of them. By not enough, James means strictly less than $ 20\% $ of all cities.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 2\,000 $ ) — the number of test cases. Each test case is described as follows:

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n \le 10^5 $ , $ 0 \leq m \le 2 \cdot 10^5 $ ) — the number of cities and roads between them. Each of the following $ m $ lines contains two integers $ u $ , $ v $ ( $ u \neq v $ ; $ 1 \leq u, v \leq n $ ), which denote that there is a directed road from $ u $ to $ v $ .

You can assume that between each ordered pair of cities there is at most one road. The sum of $ n $ over all test cases doesn't exceed $ 10^5 $ , and the sum of $ m $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

If strictly less than $ 20\% $ of all cities are interesting, print $ -1 $ . Otherwise, let $ k $ be the number of interesting cities. Print $ k $ distinct integers in increasing order — the indices of interesting cities.

## 说明/提示

In all drawings, if a city is colored green, then it is interesting; otherwise, it is colored red.

In the first sample, each city is interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/ea02130aaa657158e02932dc79202b09c65411df.png)In the second sample, no city is interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/9f70c6807b725116da2e28994dd20c33629e3f31.png)In the third sample, cities $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ are interesting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/f1d050ad3537d17cb3725772a1afecd8c2c46f32.png)In the last sample, only the city $ 1 $ is interesting. It is strictly less than $ 20\% $ of all cities, so the answer is $ -1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/d74f523bcab5b0c943643c6309e1f1139462efcb.png)

## 样例 #1

### 输入

```
4
3 3
1 2
2 3
3 1
3 6
1 2
2 1
2 3
3 2
1 3
3 1
7 10
1 2
2 3
3 1
1 4
4 5
5 1
4 6
6 7
7 4
6 1
6 8
1 2
2 3
3 4
4 5
5 6
6 1
6 2
5 1
```

### 输出

```
1 2 3 
-1
1 2 3 5 
-1
```



---

---
title: "Johnny and New Toy"
layout: "post"
diff: 省选/NOI-
pid: CF1361F
tag: ['随机化']
---

# Johnny and New Toy

## 题目描述

Johnny has a new toy. As you may guess, it is a little bit extraordinary. The toy is a permutation $ P $ of numbers from $ 1 $ to $ n $ , written in one row next to each other.

For each $ i $ from $ 1 $ to $ n - 1 $ between $ P_i $ and $ P_{i + 1} $ there is a weight $ W_i $ written, and those weights form a permutation of numbers from $ 1 $ to $ n - 1 $ . There are also extra weights $ W_0 = W_n = 0 $ .

The instruction defines subsegment $ [L, R] $ as good if $ W_{L - 1} < W_i $ and $ W_R < W_i $ for any $ i $ in $ \{L, L + 1, \ldots, R - 1\} $ . For such subsegment it also defines $ W_M $ as minimum of set $ \{W_L, W_{L + 1}, \ldots, W_{R - 1}\} $ .

Now the fun begins. In one move, the player can choose one of the good subsegments, cut it into $ [L, M] $ and $ [M + 1, R] $ and swap the two parts. More precisely, before one move the chosen subsegment of our toy looks like: $ $$$W_{L - 1}, P_L, W_L, \ldots, W_{M - 1}, P_M, W_M, P_{M + 1}, W_{M + 1}, \ldots, W_{R - 1}, P_R, W_R $ $  and afterwards it looks like this:  $ $ W_{L - 1}, P_{M + 1}, W_{M + 1}, \ldots, W_{R - 1}, P_R, W_M, P_L, W_L, \ldots, W_{M - 1}, P_M, W_R $ $  Such a move can be performed multiple times (possibly zero), and the goal is to achieve the minimum number of inversions in  $ P $ . </p><p>Johnny's younger sister Megan thinks that the rules are too complicated, so she wants to test her brother by choosing some pair of indices  $ X $  and  $ Y $ , and swapping  $ P\_X $  and  $ P\_Y $  ( $ X $  might be equal  $ Y $ ). After each sister's swap, Johnny wonders, what is the minimal number of inversions that he can achieve, starting with current  $ P $  and making legal moves?</p><p>You can assume that the input is generated <span class="tex-font-style-bf">randomly</span>.  $ P $  and  $ W$$$ were chosen independently and equiprobably over all permutations; also, Megan's requests were chosen independently and equiprobably over all pairs of indices.

## 输入格式

The first line contains single integer $ n $ $ (2 \leq n \leq 2 \cdot 10^5) $ denoting the length of the toy.

The second line contains $ n $ distinct integers $ P_1, P_2, \ldots, P_n $ $ (1 \leq P_i \leq n) $ denoting the initial permutation $ P $ . The third line contains $ n - 1 $ distinct integers $ W_1, W_2, \ldots, W_{n - 1} $ $ (1 \leq W_i \leq n - 1) $ denoting the weights.

The fourth line contains single integer $ q $ $ (1 \leq q \leq 5 \cdot 10^4) $ — the number of Megan's swaps. The following $ q $ lines contain two integers $ X $ and $ Y $ $ (1 \leq X, Y \leq n) $ — the indices of elements of $ P $ to swap. The queries aren't independent; after each of them, the permutation is changed.

## 输出格式

Output $ q $ lines. The $ i $ -th line should contain exactly one integer — the minimum number of inversions in permutation, which can be obtained by starting with the $ P $ after first $ i $ queries and making moves described in the game's instruction.

## 说明/提示

Consider the first sample. After the first query, $ P $ is sorted, so we already achieved a permutation with no inversions.

After the second query, $ P $ is equal to \[ $ 1 $ , $ 3 $ , $ 2 $ \], it has one inversion, it can be proven that it is impossible to achieve $ 0 $ inversions.

In the end, $ P $ is equal to \[ $ 2 $ , $ 3 $ , $ 1 $ \]; we can make a move on the whole permutation, as it is a good subsegment itself, which results in $ P $ equal to \[ $ 1 $ , $ 2 $ , $ 3 $ \], which has $ 0 $ inversions.

## 样例 #1

### 输入

```
3
3 2 1
2 1
3
1 3
3 2
3 1
```

### 输出

```
0
1
0
```

## 样例 #2

### 输入

```
5
4 3 2 5 1
3 2 1 4
7
5 4
5 2
1 5
2 4
2 4
4 3
3 3
```

### 输出

```
3
1
2
1
2
3
3
```



---

---
title: "Arithmancy (Medium)"
layout: "post"
diff: 省选/NOI-
pid: CF1970D2
tag: ['随机化']
---

# Arithmancy (Medium)

## 题目描述

本题不同版本的区别仅在于 $n$ 的最大值。

Vector 教授在为她的算术课做准备，她需要准备 $n$ 个独特的魔法单词。每一个魔法单词都是由字符 X 和 O 组成的字符串。学生需要将两个魔法单词拼接在一起组成一个咒语，而咒语的力量（Power）定义为其所有不同的非空子串的数量。例如，咒语 XOXO 的力量为 7，因为它包括 7 个不同的子串：X, O, XO, OX, XOX, OXO 和 XOXO。

每位学生将独立随机地从 Vector 教授提供的 $n$ 个单词中挑选两个单词拼接形成自己的咒语，这意味着可能选择到两个完全相同的单词。然后学生计算出他们咒语的力量，并报告给 Vector 教授。为了检查学生们的计算结果并展示她的能力，Vector 教授需要知道每位学生拼接的具体是哪两个魔法单词以及它们的顺序。

你的任务就是扮演 Vector 教授：首先，创建 $n$ 个互不相同的魔法单词；接着，根据多次请求，通过已知的咒语力量来确定学生使用的两个单词索引及其顺序。

## 输入格式

对于这个交互式问题，你的程序应先读取一个整数 $n$（$1 \le n \le 30$），表示需要准备的魔法单词数量。接着，输出 $n$ 个不同的魔法单词，每个单词占一行。这些单词必须彼此不同，每个单词长度在 1 到 $30 \cdot n$ 之间，每个字符必须是 X 或 O。第 $i$ 个输出的魔法单词记作 $w_i$（$1 \le i \le n$）。

然后，程序应读取一个整数 $q$（$1 \le q \le 1000$），表示学生人数。接下来，程序需要重复执行以下过程 $q$ 次，每次对应一个学生。

对于第 $j$ 个学生，程序首先读取一个整数 $p_j$，表示他们的咒语的力量。这个力量是通过随机独立选择两个索引 $u_j$ 和 $v_j$（它们在 1 到 $n$ 之间），将魔法单词 $w_{u_j}$ 和 $w_{v_j}$ 拼接后计算不同非空子串数量得到的。接着，程序需输出 $u_j$ 和 $v_j$，确保顺序正确（$1 \le u_j, v_j \le n$）。

请注意，你不仅需要找到两个能够产生给定力量的魔法单词，还必须精确找到学生实际选择的那两个单词及其顺序。

每次输出所有魔法单词以及每次输出 $u_j$ 和 $v_j$ 后，记得刷新输出流。

## 说明/提示

- 1 ≤ n ≤ 30
- 1 ≤ q ≤ 1000
- 魔法单词长度在 1 到 $30 \cdot n$ 之间。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2


2
15

11
```

### 输出

```
XOXO
X


1 1

2 1
```



---

---
title: "Turtle and Three Sequences"
layout: "post"
diff: 省选/NOI-
pid: CF2003F
tag: ['状态合并', '随机化']
---

# Turtle and Three Sequences

## 题目描述

小猪给了小乌龟 3 个长度为 $n \ (1 \le n\le3000)$ 的序列 $a,b,c$，乌龟要在 $1\sim n$ 中选出 $m \ (1 \le m ≤ 5)$ 个下标 $p_1 \sim p_m$，满足如下条件：

* $p$ 是 $1\sim n$ 的子序列。

* $\forall 1\le i\le n, a\large_{p_i} \small \normalsize\le a\large_{p_i + 1} $，即得到的 $a$ 序列严格不降。
* $\forall 1\le i, j\le n \ (i\ne j), b\large_{p_i}\normalsize \ne b\large_{p_j}$ ，即得到的 $b$ 序列两两不同。

你需要帮助小乌龟求出可能的 $\sum\limits^m_{i=1} c\large_{p_i}$ 的最大值，或者告诉他满足以上条件的子序列 $p$ 不存在 。

其中子序列的定义是，从原序列中删去若干 $(0\sim n)$ 个元素，则新的序列是原序列的子序列。

## 输入格式

第一行两个正整数 $n,m$ ，表示三个序列的长度和选出的子序列 $p$ 的长度。

第二、三、四行 $n$ 个正整数 分别表示 $a,b,c$ 三个序列，其中 $c_i\le 10^4$。

## 输出格式

输出一行一个正整数表示答案，如果不存在满足条件的子序列，输出 $-1$。

## 说明/提示

在第一个样例中，我们可以选择 $p=[1,2]$，则答案为 $1+4=5$。我们不能选择 $p=[2,4]$ 因为 $a_2>a_4$ ，不满足第一个条件。我们也不能选择 $p=[2,3]$ 因为 $b_2=b_3$ ，不满足第二个条件。我们可以选择 $p=[1,4]$，但答案为 $4$ ，不是最大的。

在第二个样例中 我们可以选择 $p=[4,6,7]$。

在第三个样例中，我们选不到满足条件的 $p$ 。

## 样例 #1

### 输入

```
4 2
2 3 4 2
1 3 3 2
1 4 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 3
1 4 5 2 3 6 7
1 2 2 1 1 3 2
1 5 6 7 3 2 4
```

### 输出

```
13
```

## 样例 #3

### 输入

```
5 3
1 2 3 4 5
1 1 2 1 2
5 4 3 2 1
```

### 输出

```
-1
```



---

---
title: "Penchick and Even Medians"
layout: "post"
diff: 省选/NOI-
pid: CF2031F
tag: ['随机化', '构造']
---

# Penchick and Even Medians

## 题目描述

这是一个交互式的问题。

Penchick 刚从澳大利亚的黄金海岸度假回家，却遗忘给他的宠物鸭 Duong Canh 带礼物！或许经过海滩上的深思熟虑设计出的一道有趣题目，是最好的纪念品。

你面临的任务是找出一个长度为 $n$ 的隐藏排列 $p$，其中 $n$ 是偶数。你可以通过以下方式进行查询：

- 选择排列 $p$ 的一个长度为 $4 \le k \le n$ 的子序列（子序列中的元素不必连续）。交互系统会返回该子序列中的两个中位数。

你的任务是在不超过 80 次查询的条件下，找出排列 $p$ 中这两个中位数的索引。

注意：交互系统是固定的，即排列 $p$ 在开始时就已经确定，并不会根据你的查询而改变。

## 输入格式

每个测例包含多个测试用例。第一行包含测例数量 $t$ （$1 \le t \le 1000$）。接下来是每个测试用例的描述。

在每个测试用例中，首先是一个整数 $n$ （$6 \le n \le 100$，且为偶数），即隐藏排列 $p$ 的长度。

读取整数 $n$ 后，你应开始与系统进行交互，直到猜出答案，然后再处理下一个测试用例。

保证所有测试用例中 $n$ 的总和不超过 $10^4$。

## 输出格式

要进行一次查询，按以下格式输出：

- `? k x_1 x_2 ... x_{k-1} x_k` （$4 \le k \le n$，$k$ 是偶数，$1 \le x_i \le n$，所有 $x_i$ 互不相同），其中 $k$ 是选择的子序列长度，后面跟随子序列元素的索引。

每次查询后，你会收到一个包含两个整数 $m_1$ 和 $m_2$ 的响应（$1 \le m_1 < m_2 \le n$），表示这个子序列的两个中位数的值。

每个测试用例中可以进行的查询次数最多为 80。

输出最终答案时，请按以下格式：

- `! i_1 i_2` （$1 \le i_1, i_2 \le n$）——这两个数表示两个中位数的索引。

注意，输出的顺序不重要，即满足 $p_{i_1} = \frac{n}{2}$ 和 $p_{i_2} = \frac{n}{2}+1$，或反之亦可。

在每次查询后，记得输出换行符并刷新输出，否则程序可能由于“空闲限制”而失败。

如果在任何交互步骤中读取到 $-1$ 而不是有效数据，说明出现了无效查询或其他错误，你的程序必须立即退出继续执行会导致程序异常。

### 示例

在第一个测试用例中，隐藏的排列是 $p = [6, 2, 3, 5, 1, 4]$。

1. 第一次查询选择了整个排列，此时的两个中位数是 $3$ 和 $4$。
2. 第二次查询选择了子序列 $3, 6, 1, 5$，返回的中位数是 $3$ 和 $4$。
3. 第三次查询选择了子序列 $3, 6, 2, 5$，返回的中位数是 $2$ 和 $3$。

答案“! 3 6”是有效的，因为 $p_3 = 3$ 且 $p_6 = 4$。

在第二个测试用例中，隐藏的排列是 $p = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]$。

1. 第一次查询选择了子序列 $1, 3, 7, 8, 9, 10$，返回的中位数是 $3$ 和 $4$。
2. 第二次查询选择了子序列 $1, 2, 3, 4, 5, 6, 7, 8$，返回的中位数是 $6$ 和 $7$。

答案“! 5 6”是有效的，因为 $p_5 = 6$ 和 $p_6 = 5$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
6

3 4

3 4

2 3

10

3 4

6 7
```

### 输出

```
? 6 1 2 3 4 5 6

? 4 3 6 1 5

? 4 3 6 2 5

! 3 6

? 6 1 3 7 8 9 10

? 8 1 2 3 4 5 6 7 8

! 6 5
```



---

