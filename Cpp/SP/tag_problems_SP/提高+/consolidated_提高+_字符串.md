---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "SP263 - PERIOD - Period"
layout: "post"
diff: 提高+/省选-
pid: SP263
tag: ['字符串']
---

# SP263 - PERIOD - Period

## 题目描述

如果一个字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，则称 $T$ 是 $S$ 的循环元。使 $K$ 最大的字符串 $T$ 称为 $S$ 的最小循环元，此时的 $K$ 称为最大循环次数。

现给一个给定长度为 $N$ 的字符串 $S$，对 $S$ 的每一个前缀 $S[1\sim i]$，如果它的最大循环次数大于 $1$，则输出该前缀的长度和最大循环次数。

## 输入格式

第一行将仅包含测试用例的数量 $T (1 \le T \le 10)$。

每个测试用例包含两行。

第一行一个整数 $N (2 \le N \le 1\times 10^6)$ 表示字符串 $S$ 的长度，第二行一个字符串 $S$。

## 输出格式

对于每个测试用例，第一行输出 `Test case #` 和测试点编号。接下来对于每个长度为 $i$ 且 $K > 1$ 的前缀，输出前缀大小 $i$ 和循环次数 $K$，前缀大小按递增顺序排列。在每个测试点后打印一个空白行。

## 说明/提示

Translate by [@qifan_maker](/user/706607).

## 样例 #1

### 输入

```
2
3
aaa
12
aabaabaabaab
```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
```



---

---
title: "TRIP - Trip"
layout: "post"
diff: 提高+/省选-
pid: SP33
tag: ['字符串', '递归', '枚举']
---

# TRIP - Trip

## 题目描述

Alice and Bob want to go on holiday. Each of them has drawn up a list of cities to be visited in turn. A list may contain a city more than once. As they want to travel together, they have to agree upon a common route. No one wants to change the order of the cities on his list or add other cities. Therefore they have no choice but to remove some cities from the list. Of course the common route is to involve as much sight-seeing in cities as possible. There are exactly 26 cities in the region. Therefore they are encoded on the lists as lower case letters from 'a' to 'z'.

## 输入格式

The first line of input contains a number T <= 10 that indicates the number of test cases to follow. Each test case consists of two lines; the first line is the list of Alice, the second line is the list of Bob. Each list consists of 1 to 80 lower case letters.

## 输出格式

The output for each test case should contain all different trips exactly once that meet the conditions described above. There is at least one such trip, but never more than 1000 different ones. You should order the trips in lexicographic order. Print one blank line between the output of different test cases.

## 样例 #1

### 输入

```
1
abcabcaa
acbacba
```

### 输出

```
ababa
abaca
abcba
acaba
acaca
acbaa
acbca
```



---

---
title: "TWINSNOW - Snowflakes"
layout: "post"
diff: 提高+/省选-
pid: SP4354
tag: ['字符串']
---

# TWINSNOW - Snowflakes

## 题目描述

你可能听说过，没有两片雪花是相同的。你要写一个程序，判断这是不是真的。你的程序会读到一些有关于这些雪花的信息，找到一对完全相同的雪花。每片雪花有六个角。对于每个雪花，你的程序会获得每个角的长度。我们认为两片雪花相同，当且仅当它们各自从某一个角开始，逆时针或顺时针记录长度，能得到两个相同的六元组。

## 输入格式

-第一行只有一个数字n，代表雪花的数量。

-接下来会有n行，每一行描述了一片雪花。每片雪花会按逆时针或顺时针给出六个角的长度a1,a2...a6。我们认为两片雪花相同，当且仅当它们各自从某一个角开始，逆时针或顺时针记录长度，能得到两个相同的六元组。例如，同一片雪花可以被描述为1 2 3 4 5 6 或 4 3 2 1 6 5。

## 输出格式

如果没有两片雪花是相同的，请输出  :  
_No two snowflakes are alike. _

否则，请输出：

_Twin snowflakes found._

# 输入输出样例
暂无测试点



---

---
title: "CF25E - Test"
layout: "post"
diff: 提高+/省选-
pid: SP7155
tag: ['字符串', '枚举', 'KMP 算法']
---

# CF25E - Test

## 题目描述

### 题目翻译

Bob 出了一道字符串题，题目的输入是一个字符串。

毒瘤的 Bob 写了 $3$ 个程序，但他发现了一个悲剧：

1. 当输入的字符串有子串 $s_1$ 时，程序 $1$ 会 WA；

1. 当输入的字符串有子串 $s_2$ 时，程序 $2$ 会死循环；

1. 当输入的字符串有子串 $s_3$ 时，程序 $3$ 会 MLE。

当然，可以假定其他情况下程序不会出锅。

Bob 非常毒瘤，他想找一个最短的输入字符串 $ss$，使得 $3$ 个程序都过不了。请输出最小的长度。

## 输入格式

**多组数据**，每组数据 $3$ 行，每行一个字符串，分别代表 $s_1,s_2,s_3$，只含小写字母。

## 输出格式

对于每组数据，输出一个整数代表最小长度，然后换行。

#### 数据规模与约定

对于 $100\%$ 的数据， $1\leq |s_1|,|s_2|,|s_3|\leq 10^5$。

## 样例 #1

### 输入

```
ab
bc
cd
abacaba
abaaba
x

```

### 输出

```
4
11

```



---

