---
title: "Many Equal Substrings"
layout: "post"
diff: 普及+/提高
pid: CF1029A
tag: ['字符串', 'KMP 算法', '构造']
---

# Many Equal Substrings

## 题目描述

You are given a string $ t $ consisting of $ n $ lowercase Latin letters and an integer number $ k $ .

Let's define a substring of some string $ s $ with indices from $ l $ to $ r $ as $ s[l \dots r] $ .

Your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ positions $ i $ such that $ s[i \dots i + n - 1] = t $ . In other words, your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 50 $ ) — the length of the string $ t $ and the number of substrings.

The second line of the input contains the string $ t $ consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

Print such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 样例 #1

### 输入

```
3 4
aba

```

### 输出

```
ababababa

```

## 样例 #2

### 输入

```
3 2
cat

```

### 输出

```
catcat

```



---

---
title: "Password"
layout: "post"
diff: 普及+/提高
pid: CF126B
tag: ['字符串', '枚举', 'KMP 算法', '标签474']
---

# Password

## 题目描述

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

## 输入格式

一行一个只包含小写字母的字符串 $S$。

## 输出格式

输出子串 $T$，如果 $T$ 不存在，输出 `Just a legend`。

## 样例 #1

### 输入

```
fixprefixsuffix

```

### 输出

```
fix
```

## 样例 #2

### 输入

```
abcdabc

```

### 输出

```
Just a legend
```



---

---
title: "Word Cut"
layout: "post"
diff: 普及+/提高
pid: CF176B
tag: ['字符串', '递推', 'KMP 算法']
---

# Word Cut

## 题目描述

Let's consider one interesting word game. In this game you should transform one word into another through special operations.

Let's say we have word $ w $ , let's split this word into two non-empty parts $ x $ and $ y $ so, that $ w=xy $ . A split operation is transforming word $ w=xy $ into word $ u=yx $ . For example, a split operation can transform word "wordcut" into word "cutword".

You are given two words $ start $ and $ end $ . Count in how many ways we can transform word $ start $ into word $ end $ , if we apply exactly $ k $ split operations consecutively to word $ start $ .

Two ways are considered different if the sequences of applied operations differ. Two operation sequences are different if exists such number $ i $ ( $ 1<=i<=k $ ), that in the $ i $ -th operation of the first sequence the word splits into parts $ x $ and $ y $ , in the $ i $ -th operation of the second sequence the word splits into parts $ a $ and $ b $ , and additionally $ x≠a $ holds.

## 输入格式

The first line contains a non-empty word $ start $ , the second line contains a non-empty word $ end $ . The words consist of lowercase Latin letters. The number of letters in word $ start $ equals the number of letters in word $ end $ and is at least $ 2 $ and doesn't exceed $ 1000 $ letters.

The third line contains integer $ k $ ( $ 0<=k<=10^{5} $ ) — the required number of operations.

## 输出格式

Print a single number — the answer to the problem. As this number can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

The sought way in the first sample is:

ab $ → $ a|b $ → $ ba $ → $ b|a $ → $ ab

In the second sample the two sought ways are:

- ababab $ → $ abab|ab $ → $ ababab
- ababab $ → $ ab|abab $ → $ ababab

## 样例 #1

### 输入

```
ab
ab
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
ababab
ababab
1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
ab
ba
2

```

### 输出

```
0

```



---

---
title: "Writing a Song"
layout: "post"
diff: 普及+/提高
pid: CF54D
tag: ['深度优先搜索 DFS', 'KMP 算法']
---

# Writing a Song

## 题目描述

**题目大意**

求一个字符串s，满足该串长度为n，只出现字母表中前k个字母，并且在指定位置必须出现指定字符串p

## 输入格式

第一行 n，k。(n为所需字符串的长度 n<=100，k为相应的字母大小 2<=k<=26)

第二行 p。（一个长度小于n，只包含字母表中前k个字母的字符串）

第三行 01串。（在第i个位置的数字1表示p的出现应该从s的第i个位置开始，而0表示从这里开始没有出现。）

## 输出格式

输出任意一个符合题意的字符串s

若无，输出“No solution”

## 样例 #1

### 输入

```
5 2
aba
101

```

### 输出

```
ababa
```

## 样例 #2

### 输入

```
5 2
a
10001

```

### 输出

```
abbba
```

## 样例 #3

### 输入

```
6 2
abba
101

```

### 输出

```
No solution
```



---

