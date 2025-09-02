---
title: "Dr. Evil Underscores"
layout: "post"
diff: 普及+/提高
pid: CF1285D
tag: ['字符串', '树形 DP', '字典树 Trie']
---

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 输入格式

The first line contains integer $ n $ ( $ 1\le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ).

## 输出格式

Print one integer — the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 5
```

### 输出

```
4
```



---

---
title: "Xor Tree"
layout: "post"
diff: 普及+/提高
pid: CF1446C
tag: ['动态规划 DP', '字典树 Trie']
---

# Xor Tree

## 题目描述

For a given sequence of distinct non-negative integers $ (b_1, b_2, \dots, b_k) $ we determine if it is good in the following way:

- Consider a graph on $ k $ nodes, with numbers from $ b_1 $ to $ b_k $ written on them.
- For every $ i $ from $ 1 $ to $ k $ : find such $ j $ ( $ 1 \le j \le k $ , $ j\neq i $ ), for which $ (b_i \oplus b_j) $ is the smallest among all such $ j $ , where $ \oplus $ denotes the operation of bitwise XOR ([https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Next, draw an undirected edge between vertices with numbers $ b_i $ and $ b_j $ in this graph.
- We say that the sequence is good if and only if the resulting graph forms a tree (is connected and doesn't have any simple cycles).

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

You can find an example below (the picture corresponding to the first test case).

Sequence $ (0, 1, 5, 2, 6) $ is not good as we cannot reach $ 1 $ from $ 5 $ .

However, sequence $ (0, 1, 5, 2) $ is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446C/787661480e10ca394e5bb0097a1db13aac775e6e.png)You are given a sequence $ (a_1, a_2, \dots, a_n) $ of distinct non-negative integers. You would like to remove some of the elements (possibly none) to make the remaining sequence good. What is the minimum possible number of removals required to achieve this goal?

It can be shown that for any sequence, we can remove some number of elements, leaving at least $ 2 $ , so that the remaining sequence is good.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 200,000 $ ) — length of the sequence.

The second line contains $ n $ distinct non-negative integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the elements of the sequence.

## 输出格式

You should output exactly one integer — the minimum possible number of elements to remove in order to make the remaining sequence good.

## 说明/提示

Note that numbers which you remove don't impact the procedure of telling whether the resulting sequence is good.

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

## 样例 #1

### 输入

```
5
0 1 5 2 6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
6 9 8 7 3 5 2
```

### 输出

```
2
```



---

---
title: "Shorten the Array"
layout: "post"
diff: 普及+/提高
pid: CF2093G
tag: ['贪心', '字典树 Trie']
---

# Shorten the Array

## 题目描述

一个长度为 $m$ 的数组 $b$ 的美观度定义为所有可能数对 $1 \le i \le j \le m$ 中 $b_i \oplus b_j$ 的最大值，其中 $x \oplus y$ 表示数字 $x$ 和 $y$ 的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。我们将数组 $b$ 的美观度记为 $f(b)$。

如果一个数组 $b$ 满足 $f(b) \ge k$，则称该数组是美观的。

最近，Kostya 从商店购买了一个长度为 $n$ 的数组 $a$。他认为这个数组太长了，因此计划从中截取一个美观的子数组。也就是说，他需要选择两个数字 $l$ 和 $r$（$1 \le l \le r \le n$），使得子数组 $a_{l \dots r}$ 是美观的。这样的子数组的长度为 $r - l + 1$。整个数组 $a$ 也被视为一个子数组（此时 $l = 1$ 且 $r = n$）。

你的任务是找出数组 $a$ 中最短美观子数组的长度。如果不存在美观的子数组，则输出 $-1$。

## 输入格式

第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。

接下来是 $t$ 个由两行组成的测试块：

每个测试块的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 2 \cdot 10^5$，$0 \le k \le 10^9$）。

每个测试块的第二行包含数组 $a$，由 $n$ 个整数组成（$0 \le a_i \le 10^9$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个整数——满足 $f(a_{l \dots r}) \ge k$ 的最短子数组 $(l, r)$ 的长度。如果不存在这样的子数组，则输出 $-1$。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 0
1 2 3 4 5
5 7
1 2 3 4 5
5 8
1 2 3 4 5
5 7
3 5 1 4 2
5 3
3 5 1 4 2
6 71
26 56 12 45 60 27
```

### 输出

```
1
2
-1
4
2
-1
```



---

---
title: "Amr and Chemistry"
layout: "post"
diff: 普及+/提高
pid: CF558C
tag: ['动态规划 DP', '贪心', '枚举', '进制', '字典树 Trie']
---

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the number of chemicals.

The second line contains $ n $ space separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{5} $ ), representing the initial volume of the $ i $ -th chemical in liters.

## 输出格式

Output one integer the minimum number of operations required to make all the chemicals volumes equal.

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 5 6

```

### 输出

```
5
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
title: "Phone Numbers"
layout: "post"
diff: 普及+/提高
pid: CF898C
tag: ['字符串', '字典树 Trie']
---

# Phone Numbers

## 题目描述

Vasya有几本电话簿，他记录了他的朋友的电话号码。他的每个朋友可以有一个或几个电话号码。
Vasya决定组织有关朋友电话号码的信息。您将获得n个字符串 - 来自Vasya电话簿的所有条目。每个条目都以朋友的名字开头。然后跟随当前条目中的电话号码数量，然后是电话号码本身。有可能几部相同的电话被记录在同一记录中。
Vasya还认为，如果电话号码a是电话号码b的后缀（即，电话号码b以a结尾），并且两个电话号码都由Vasya写成同一个人的电话号码，则记录a并且没有城市代码，它是不被考虑在内的。
任务是输出有关Vasya朋友电话号码的组织信息。两个不同的人可能有相同的号码。如果一个人有两个数字x和y，并且x是y的后缀（即y以x结尾），那么您不应该输出数字x。如果Vasya电话簿中的朋友的号码以相同的格式记录多次，则有必要将其记录一次。
阅读样例以更好地理解输出的语句和格式。

## 输入格式

第一行包含整数n（1<=n<=20） 表示Vasya电话簿中的条目数。
下面的n行后面是描述声明中描述的格式的记录。 Vasya的朋友的名字是非空字符串，其长度不超过10，只包含小写英文字母。 一个条目中的电话号码不少于1不超过10。电话号码只包含数字。如果您将电话号码表示为字符串，则其长度将在1到10的范围内。电话号码可以包含前导零。

## 输出格式

输出出有关Vasya朋友电话号码的订购信息。 首先输出m表示在Vasya电话簿中找到的朋友的数量。
下列m行必须包含以下格式的条目“姓名 电话号码的个数 电话号码”。电话号码应该用空格隔开。每个记录必须包含当前朋友的所有电话号码。
条目可以以任意顺序显示，一个记录的电话号码也可以以任意顺序打印。

## 样例 #1

### 输入

```
2
ivan 1 00123
masha 1 00123

```

### 输出

```
2
masha 1 00123 
ivan 1 00123 

```

## 样例 #2

### 输入

```
3
karl 2 612 12
petr 1 12
katya 1 612

```

### 输出

```
3
katya 1 612 
petr 1 12 
karl 1 612 

```

## 样例 #3

### 输入

```
4
ivan 3 123 123 456
ivan 2 456 456
ivan 8 789 3 23 6 56 9 89 2
dasha 2 23 789

```

### 输出

```
2
dasha 2 23 789 
ivan 4 789 123 2 456 

```



---

