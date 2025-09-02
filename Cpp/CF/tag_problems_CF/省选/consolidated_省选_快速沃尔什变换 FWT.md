---
title: "Illumination"
layout: "post"
diff: 省选/NOI-
pid: CF1728G
tag: ['动态规划 DP', '状态合并', '组合数学', '容斥原理', '快速沃尔什变换 FWT']
---

# Illumination

## 题目描述

Consider a segment $ [0, d] $ of the coordinate line. There are $ n $ lanterns and $ m $ points of interest in this segment.

For each lantern, you can choose its power — an integer between $ 0 $ and $ d $ (inclusive). A lantern with coordinate $ x $ illuminates the point of interest with coordinate $ y $ if $ |x - y| $ is less than or equal to the power of the lantern.

A way to choose the power values for all lanterns is considered valid if every point of interest is illuminated by at least one lantern.

You have to process $ q $ queries. Each query is represented by one integer $ f_i $ . To answer the $ i $ -th query, you have to:

- add a lantern on coordinate $ f_i $ ;
- calculate the number of valid ways to assign power values to all lanterns, and print it modulo $ 998244353 $ ;
- remove the lantern you just added.

## 输入格式

The first line contains three integers $ d $ , $ n $ and $ m $ ( $ 4 \le d \le 3 \cdot 10^5 $ ; $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le m \le 16 $ ) — the size of the segment, the number of lanterns and the number of points of interest, respectively.

The second line contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \le l_i \le d - 1 $ ), where $ l_i $ is the coordinate of the $ i $ -th lantern.

The third line contains $ m $ integers $ p_1, p_2, \dots, p_m $ ( $ 1 \le p_i \le d - 1 $ ), where $ p_i $ is the coordinate of the $ i $ -th point of interest.

The fourth line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

The fifth line contains $ q $ integers $ f_1, f_2, \dots, f_q $ ( $ 1 \le f_i \le d - 1 $ ), where $ f_i $ is the integer representing the $ i $ -th query.

Additional constraint on the input: during the processing of each query, no coordinate contains more than one object (i. e. there cannot be two or more lanterns with the same coordinate, two or more points of interest with the same coordinate, or a lantern and a point of interest with the same coordinate).

## 输出格式

For each query, print one integer — the answer to it, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5
```

### 输出

```
48
47
47
```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3
```

### 输出

```
44
46
```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8
```

### 输出

```
413
```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9
```

### 输出

```
190431
187503
188085
189903
189708
```



---

---
title: "Algebra Flash"
layout: "post"
diff: 省选/NOI-
pid: CF1767E
tag: ['状态合并', '图论建模', '快速沃尔什变换 FWT', '折半搜索 meet in the middle']
---

# Algebra Flash

## 题目描述

### 题目背景

Algebra Flash 2.2 刚刚发布！

更新日志：

- 全新游戏模式！

感谢您一直以来对游戏的支持！

就这？你略带失望地启动游戏，点进新的游戏模式，上面写着 "彩色平台"。


有 $n$ 个平台排成一列，编号从 $1$ 到 $n$。平台有 $m$ 种颜色，编号从 $1$ 到 $m$。第 $i$ 个平台的颜色是 $c_i$。

你从 $1$ 号平台开始，想要跳到 $n$ 号平台。在一次移动中，你可以从某个平台 $i$ 跳到平台 $i + 1$ 或 $i + 2$。

所有平台最初都未激活（包括平台 $1$ 和 $n$）。对于每种颜色 $j$，你可以支付 $x_j$ 枚金币来激活所有颜色为 $j$ 的平台。

你希望激活一些平台，然后从已激活的平台 $1$ 开始，跳过一些已激活的平台，到达已激活的平台 $n$。

要实现这个目标，你最少花费多少金币？

## 输入格式

第一行两个整数 $n$ 和 $m$（$2 \le n \le 3 \times 10^5$ ; $1 \le m \le 40$），分别表示平台数和颜色数。

第二行 $n$ 个整数 $c_1, c_2, \dots, c_n$（$1 \le c_i \le m$）表示平台的颜色。

第三行 $m$ 个整数 $x_1, x_2, \dots, x_m$（$1 \le x_i \le 10^7$）表示激活每种颜色的所有平台花费的金币数量。

## 输出格式

一行一个整数，表示从激活的平台 $1$ 开始，跳过一些激活的平台，到达激活的平台 $n$ 需要花费的最小金币数量。

Translated by UID 781046.

## 样例 #1

### 输入

```
5 3
1 3 2 3 1
1 10 100
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 3
1 3 2 3 1
1 200 20
```

### 输出

```
21
```

## 样例 #3

### 输入

```
4 2
2 2 1 1
5 5
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 10
3 8 6 2 10 5 2 3 7 3
9 7 4 2 1 8 2 6 2 2
```

### 输出

```
15
```



---

---
title: "Deck-Building Game"
layout: "post"
diff: 省选/NOI-
pid: CF1906K
tag: ['快速沃尔什变换 FWT']
---

# Deck-Building Game

## 题目描述

You are playing a deck-building game with your friend. There are $ N $ cards, numbered from $ 1 $ to $ N $ . Card $ i $ has the value of $ A_i $ .

You want to build two decks; one for you and one for your friend. A card cannot be inside both decks, and it is allowed to not use all $ N $ cards. It is also allowed for a deck to be empty, i.e. does not contain any cards.

The power of a deck is represented as the bitwise XOR of the value of the cards in the deck. The power of an empty deck is $ 0 $ .

The game is balanced if both decks have the same power.

Determine the number of ways to build two decks such that the game is balanced. Two ways are considered different if one of the decks contains at least one different card. Since the answer can be very large, calculate the answer modulo $ 998\,244\,353 $ .

## 输入格式

The first line consists of an integer $ N $ ( $ 2 \le N \le 100\,000 $ ).

The following line consists of $ N $ integers $ A_i $ ( $ 1 \le A_i \le 100\,000 $ ).

## 输出格式

Output an integer representing the number of ways to build two decks such that the game is balanced. Output the answer modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation for the sample input/output #1

Denote $ S $ and $ T $ as the set of cards in your deck and your friend's deck, respectively. There are $ 9 $ ways to build the decks such that the game is balanced.

- $ S = \{\} $ and $ T = \{\} $ . Both decks have the power of $ 0 $ .
- $ S = \{2, 3, 4\} $ and $ T = \{\} $ . Both decks have the power of $ 0 $ .
- $ S = \{\} $ and $ T = \{2, 3, 4\} $ . Both decks have the power of $ 0 $ .
- $ S = \{2, 4\} $ and $ T = \{3\} $ . Both decks have the power of $ 4 $ .
- $ S = \{3\} $ and $ T = \{2, 4\} $ . Both decks have the power of $ 4 $ .
- $ S = \{2, 3\} $ and $ T = \{4\} $ . Both decks have the power of $ 8 $ .
- $ S = \{4\} $ and $ T = \{2, 3\} $ . Both decks have the power of $ 8 $ .
- $ S = \{3, 4\} $ and $ T = \{2\} $ . Both decks have the power of $ 12 $ .
- $ S = \{2\} $ and $ T = \{3, 4\} $ . Both decks have the power of $ 12 $ .

Explanation for the sample input/output #2

The only way to make the game balanced is to have both decks empty.

Explanation for the sample input/output #3

There are $ 5 $ ways to build the decks such that the game is balanced.

- $ S = \{\} $ and $ T = \{\} $ . Both decks have the power of $ 0 $ .
- $ S = \{1, 2\} $ and $ T = \{\} $ . Both decks have the power of $ 0 $ .
- $ S = \{\} $ and $ T = \{1, 2\} $ . Both decks have the power of $ 0 $ .
- $ S = \{1\} $ and $ T = \{2\} $ . Both decks have the power of $ 1 $ .
- $ S = \{2\} $ and $ T = \{1\} $ . Both decks have the power of $ 1 $ .

## 样例 #1

### 输入

```
4
16 12 4 8
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4
1 2 4 8
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
1 1
```

### 输出

```
5
```

## 样例 #4

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
169
```



---

---
title: "Friends and Pizza"
layout: "post"
diff: 省选/NOI-
pid: CF2070F
tag: ['快速沃尔什变换 FWT', '标签464']
---

# Friends and Pizza

## 题目描述

Monocarp 有 $n$ 个披萨，第 $i$ 个披萨包含 $a_i$ 片。披萨用从 A 开始的拉丁字母大写字符表示（第 $n$ 个披萨对应第 $n$ 个拉丁字母）。

Monocarp 还有 $m$ 个朋友，他想要邀请其中恰好两人来吃披萨。对于每个朋友，Monocarp 知道该朋友喜欢哪些披萨。

当朋友到达 Monocarp 家后，每个披萨的处理方式如下：

- 如果该披萨不被任何被邀请的朋友喜欢，Monocarp 将吃掉它；
- 如果该披萨恰好被一位被邀请的朋友喜欢，该朋友将吃掉它；
- 如果该披萨被两位朋友都喜欢，他们将尝试分食。若披萨包含偶数片，两人各吃一半；若包含奇数片，他们会因争夺额外一片而发生争吵——Monocarp 不喜欢这种情况。

对于每个 $k$ 从 $0$ 到 $\sum a_i$，计算选择两个朋友的方式数，使得朋友不会争吵且 Monocarp 恰好吃掉 $k$ 片。

## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \le n \le 20$；$2 \le m \le 5 \cdot 10^5$）——分别表示披萨数量和朋友数量。

第二行包含 $m$ 个字符串 $s_1, s_2, \dots, s_m$（$1 \le |s_i| \le n$），其中 $s_i$ 由互不重复的 A 到第 $n$ 个拉丁字母组成，表示第 $i$ 个朋友喜欢的披萨。每个 $s_i$ 中的字符按字典序（字母顺序）排列。

第三行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 2 \cdot 10^4$）——各披萨的片数。

## 输出格式

输出 $\sum a_i + 1$ 个整数，其中第 $k$ 个整数（从 $0$ 开始）表示满足条件（朋友不争吵且 Monocarp 吃 $k$ 片）的选法数目。

## 说明/提示

以第一个示例的所有朋友对为例：

- 邀请朋友 $1$ 和 $2$：他们将吃掉披萨 $1$ 和 $2$，Monocarp 吃披萨 $3$；
- 邀请朋友 $1$ 和 $3$：他们将吃掉所有披萨；
- 邀请朋友 $1$ 和 $4$：他们将吃披萨 $1$ 和 $2$，Monocarp 吃披萨 $3$；
- 邀请朋友 $1$ 和 $5$：他们将吃掉所有披萨；
- 邀请朋友 $1$ 和 $6$：他们将吃披萨 $1$ 和 $3$，Monocarp 吃披萨 $2$；
- 邀请朋友 $2$ 和 $3$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $4$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $2$ 和 $6$：他们将吃掉所有披萨；
- 邀请朋友 $3$ 和 $4$：因披萨 $2$ 发生争吵；
- 邀请朋友 $3$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $3$ 和 $6$：因披萨 $3$ 发生争吵；
- 邀请朋友 $4$ 和 $5$：因披萨 $2$ 发生争吵；
- 邀请朋友 $4$ 和 $6$：他们将吃掉所有披萨；
- 邀请朋友 $5$ 和 $6$：因披萨 $3$ 发生争吵。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 6
A AB ABC AB BC C
2 3 5
```

### 输出

```
4 0 0 1 0 2 0 0 0 0 0
```



---

---
title: "Binary Table"
layout: "post"
diff: 省选/NOI-
pid: CF662C
tag: ['快速沃尔什变换 FWT']
---

# Binary Table

## 题目描述

有一个 $n$ 行 $m$ 列的表格，每个元素都是 $0/1$ ，每次操作可以选择一行或一列，把 $0/1$ 翻转，即把 $0$ 换为 $1$ ，把 $1$ 换为 $0$ 。请问经过若干次操作后，表格中最少有多少个 $1$ 。

## 输入格式

第一行是两个整数 $n$ 和 $m$ （ $1\leqslant n\leqslant 20,1\leqslant m\leqslant 10^5$ ）之后 $n$ 行，每行 $m$ 个数字 $0/1$ ，注意数字间无空格。

## 输出格式

一行，一个整数，表示答案。

感谢@AThousandMoon  提供翻译

## 样例 #1

### 输入

```
3 4
0110
1010
0111

```

### 输出

```
2

```



---

