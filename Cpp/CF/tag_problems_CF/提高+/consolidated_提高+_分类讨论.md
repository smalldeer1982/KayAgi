---
title: "Permutations Harmony"
layout: "post"
diff: 提高+/省选-
pid: CF2034E
tag: ['贪心', '分类讨论']
---

# Permutations Harmony

## 题目描述

Rayan wants to present a gift to Reyhaneh to win her heart. However, Reyhaneh is particular and will only accept a k-harmonic set of permutations.

We define a k-harmonic set of permutations as a set of $ k $ pairwise distinct permutations $ p_1, p_2, \ldots, p_k $ of size $ n $ such that for every pair of indices $ i $ and $ j $ (where $ 1 \leq i, j \leq n $ ), the following condition holds:

 $ $$$ p_1[i] + p_2[i] + \ldots + p_k[i] = p_1[j] + p_2[j] + \ldots + p_k[j]  $ $ </p><p>Your task is to help Rayan by either providing a valid <span class="tex-font-style-it">k-harmonic set of permutations</span> for given values of  $ n $  and  $ k $  or by determining that such a set does not exist.</p><p>We call a sequence of length  $ n $  a permutation if it contains every integer from  $ 1 $  to  $ n$$$ exactly once.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ), the number of test cases.

Each test case consists of two integers $ n $ and $ k $ ( $ 1 \leq n, k \leq 10^5 $ ). The sum of $ n \cdot k $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, if a k-harmonic set of permutations exists, print YES on the first line. Then, print $ k $ lines, each containing a distinct permutation of the integers from $ 1 $ to $ n $ .

If no such set exists, print NO on the first line.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).

If multiple answers are possible, you can output any of them.

## 说明/提示

In example 1, we have $ p_1 = [1, 2, 3] $ , $ p_2 = [2, 3, 1] $ , and $ p_3 = [3, 1, 2] $ . It's easy to see that $ p_1[1] + p_2[1] + p_3[1] = p_1[2] + p_2[2] + p_3[2] = p_1[3] + p_2[3] + p_3[3] = 6 $ .

In example 2, we have $ p_1 = [1, 2, 3, 4] $ and $ p_2 = [4, 3, 2, 1] $ . It's easy to see that $ p_1[1] + p_2[1] = p_1[2] + p_2[2] = p_1[3] + p_2[3] = p_1[4] + p_2[4] = 5 $ .

In example 3, as there are five distinct elements in $ p_1 $ , it's obvious that the answer is "No".

## 样例 #1

### 输入

```
4
3 3
4 2
5 1
3 2
```

### 输出

```
YES
1 2 3
2 3 1
3 1 2
YES
1 2 3 4
4 3 2 1
NO
YES
1 2 3
3 2 1
```



---

---
title: "Broken Queries"
layout: "post"
diff: 提高+/省选-
pid: CF2049E
tag: ['二分', '分类讨论']
---

# Broken Queries

## 题目描述

你是一位魔法师，你的作品被一条龙摧毁了，于是你决心用一台神奇的范围追踪器来追捕这条龙。然而，那条龙似乎在捉弄你。

这是一个交互式问题。

有一个隐藏的二进制数组 $a$，长度为 $n$（$n$ 是 2 的幂），以及一个隐藏的整数 $k$（$2 \le k \le n - 1$）。数组 $a$ 中仅有一个元素是 1，其余元素都是 0。对于两个整数 $l$ 和 $r$（$1 \le l \le r \le n$），定义区间和为 $s(l, r) = a_l + a_{l+1} + \cdots + a_r$。

你持有一个魔法装置，它能接收区间并返回区间和，但如果区间的长度至少是 $k$，则装置返回结果的相反值。具体来说，每次你可以提交一对整数 $[l, r]$ 进行查询（$1 \le l \le r \le n$），装置会按照下述规则返回 0 或 1：

- 如果 $r - l + 1 < k$，则返回 $s(l, r)$ 的实际值。
- 如果 $r - l + 1 \ge k$，则返回 $1 - s(l, r)$。

你需要用不超过 33 次查询找到隐藏的 $k$。

请注意，这个装置对于不同的测试用例始终固定不变，即隐藏的数组 $a$ 和整数 $k$ 在游戏开始前就已经确定，并在整个过程中不变。

## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \le t \le 500$）表示测试用例的数量。接下来就是每个测试用例的详细描述。

每个测试用例的第一行包含一个正整数 $n$（$4 \le n \le 2^{30}$），表示隐藏数组的长度。保证 $n$ 是 2 的幂，即 $n = 2^m$，这里 $m$ 是非负整数。

你可以通过输出一行形如 “`? l r`” 的指令进行查询，这里的 $1 \le l \le r \le n$。之后，你会读取一个整数：0 或 1，来获取结果。

如果要输出答案 $k$，则请输出 “`! k`”。输出答案后，程序将进入下一个测试用例。

每次输出查询时，请确保在最后输出换行符并刷新输出，否则可能会因此超时。

如果在任何一步中收到 $-1$ 作为反馈，你的程序必须立即终止，这意味着你的查询有误或已犯下其他错误，未能及时退出可能导致随意判定。

## 说明/提示

在第一个测试用例中，给出隐藏整数 $k = 6$ 且数组中唯一的 1 位于索引 6 上，因此数组 $a = [0, 0, 0, 0, 0, 1, 0, 0]$。

- 对于查询 (3, 5)，因为 $5 - 3 + 1 = 3 < k$，装置返回实际结果。因为 6 不在区间 $\[3, 5\]$ 内，返回 0。
- 对于查询 (1, 8)，因为 $8 - 1 + 1 = 8 \ge k$，装置返回相反结果，返回 0。
- 对于查询 (4, 8)，因为 $8 - 4 + 1 = 5 < k$，装置返回实际结果，返回 1。
- 对于查询 (3, 8)，因为 $8 - 3 + 1 = 6 \ge k$，装置返回相反结果，返回 0。

示例解决方案输出 $k=6$，这也是正确的答案。

在第二个测试用例中，$k = 2$，数组中的 1 位于索引 3，因此 $a = [0, 0, 1, 0]$。

注意，示例解决方案在某些情况下可能无法充分确定 $k$，这仅仅是作为示例来提供参考。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
8

0

0

1

0

4

1

0
```

### 输出

```
? 3 5

? 1 8

? 4 8

? 3 8

! 6

? 3 3

? 3 4

! 2
```



---

---
title: "Needle in a Numstack"
layout: "post"
diff: 提高+/省选-
pid: CF2108D
tag: ['二分', '分类讨论']
---

# Needle in a Numstack

## 题目描述

这是一个交互式问题。

你在阁楼中发现了数字 $k$ 和 $n$，但丢失了两个数组 $A$ 和 $B$。

你记得以下信息：
- $|A| + |B| = n$，即两个数组的总长度为 $n$。
- $|A| \geq k$ 且 $|B| \geq k$，即每个数组的长度至少为 $k$。
- 数组中的元素只包含 $1$ 到 $k$ 的数字。
- 如果从数组 $A$ 中任取 $k$ 个连续元素，它们都互不相同。同样，如果从数组 $B$ 中任取 $k$ 个连续元素，它们也互不相同。

幸运的是，阁楼里的一个善良精灵找到了这两个数组，并将它们连接成一个长度为 $n$ 的数组 $C$。也就是说，数组 $C$ 的前半部分是 $A$ 的元素，后半部分是 $B$ 的元素。

你可以向精灵最多提出 $250$ 次询问。每次询问提供一个索引 $i$（$1 \leq i \leq n$），精灵会返回数组 $C$ 的第 $i$ 个元素。

你的任务是确定数组 $A$ 和 $B$ 的长度，或者报告无法唯一确定它们的长度。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 300$）。接下来是测试用例的描述。

每个测试用例仅包含一行，包含两个整数 $n$ 和 $k$（$1 \leq k \leq 50$，$2k \leq n \leq 10^6$）。

注意，所有测试用例的 $n$ 之和没有限制。

## 输出格式

对于每个测试用例，交互开始时需要读取整数 $n$。

然后你可以进行最多 $250$ 次查询。

每次查询时，输出一个格式为 "? x"（不带引号）的字符串（$1 \leq x \leq n$）。每次查询后，读取一个整数——查询的答案。

如果你进行了过多的查询，将会得到 Wrong answer 的结果。

当你确定答案时，输出一个格式为 "! a b"（不带引号）的字符串，其中 $a$ 和 $b$ 分别是你找到的数组 $A$ 和 $B$ 的长度。这个回答不计入查询次数。

如果无法唯一确定数组的长度，输出 "! -1"（不带引号）。注意，如果存在不超过 $250$ 次查询即可唯一确定数组长度的情况下你回答 $-1$，将会得到 Wrong answer 的结果。

题目保证存在符合题目描述的数组 $A$ 和 $B$，且交互器的输出是正确的。

交互器是非自适应的，这意味着答案在参与者进行查询之前就已经确定，并且不会受到参与者查询的影响。

如果你的程序进行了超过 $250$ 次查询，应立即终止以避免 Wrong answer。否则，你的程序可能会因为继续读取已关闭的流而得到任意结果。

每次输出查询后，不要忘记换行并刷新输出缓冲区。否则，你可能会得到 "IL"（Idleness limit exceeded）的结果。刷新缓冲区的方法如下：
- C++：使用 `fflush(stdout)` 或 `cout.flush()`；
- Java：使用 `System.out.flush()`；
- Pascal：使用 `flush(output)`；
- Python：使用 `stdout.flush()`；
- 其他语言请参考相关文档。

## 说明/提示

考虑第一个例子。我们查询了数组 $C$ 的前 $3$ 个元素（共 $5$ 个）。现在我们知道了数组 $C$ 的前三个元素为 $[1, 2, 2, ?, ?]$。根据条件，数组 $A$ 中的任意 $k$（$k=2$）个连续元素必须互不相同，因此第三个元素 $2$ 不可能属于数组 $A$，它必定属于数组 $B$。由此可以确定数组 $A$ 的长度为 $2$，数组 $B$ 的长度为 $3$。

图中展示了所有测试用例的数组。被查询的元素用黄色标记。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108D/3a898b9f4f0ed20651c865ecf957d0078f46a581.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 2

1

2

2

18 4

2

4

1

1

4

3 1

10 5

9 3

3

3

2

12 4

1

3

1

3

1

3
```

### 输出

```
? 1

? 2

? 3

! 2 3

? 9

? 13

? 10

? 14

? 6

! 9 9

! -1

! 5 5

? 3

? 6

? 9

! 6 3

? 1

? 2

? 5

? 6

? 9

? 10

! -1
```



---

