---
title: "Two Strings Swaps"
layout: "post"
diff: 普及+/提高
pid: CF1006D
tag: ['字符串']
---

# Two Strings Swaps

## 题目描述

**题目大意：**
有两个长度为$n$的字符串a,b，现有三种操作

- 交换$a_i,b_i$
- 交换$a_i,a_{n-i+1}$
- 交换$b_i,b_{n-i+1}$

可以发现$a$不一定能通过这些交换变成$b$

现在你还有一种操作，在交换字符之前，你可以把$a$中某个位置字符变成任意一个字符

问要使$a==b$最少要用**操作四**多少次

## 输入格式

第一行一个整数$n$

第二行字符串$a$，第三行字符串$b$

## 输出格式

一个整数，表示用操作四的最少次数

## 样例 #1

### 输入

```
7
abacaba
bacabaa

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
zcabd
dbacz

```

### 输出

```
0

```



---

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
title: "Palindrome Pairs"
layout: "post"
diff: 普及+/提高
pid: CF1045I
tag: ['字符串', '枚举', '进制']
---

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 输入格式

The first line contains a positive integer $ N $ ( $ 1 \le N \le 100\,000 $ ), representing the length of the input array.

Eacg of the next $ N $ lines contains a string (consisting of lowercase English letters from 'a' to 'z') — an element of the input array.

The total number of characters in the input array will be less than $ 1\,000\,000 $ .

## 输出格式

Output one number, representing how many palindrome pairs there are in the array.

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade

```

### 输出

```
6

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
title: "Palindrome Shuffle"
layout: "post"
diff: 普及+/提高
pid: CF2069D
tag: ['字符串', '贪心', '二分']
---

# Palindrome Shuffle

## 题目描述

给定一个由小写拉丁字母组成的字符串 $s$。

你可以对字符串 $s$ 执行以下操作：选择一个连续的（可能为空的）子串，并对其进行洗牌（即重新排列子串中的字符顺序）。

注意：回文是指正向和反向读取相同的字符串。例如，字符串 a、bab、acca、bcabcbacb 是回文，而 ab、abbbaa、cccb 则不是。

你的任务是确定为了将给定字符串 $s$ 转换为回文，必须进行操作的最小子串长度。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例仅包含一行字符串 $s$（$2 \le |s| \le 2 \cdot 10^5$），由小写拉丁字母组成。

输入额外约束：
- 字符串 $s$ 的长度为偶数；
- 字符串 $s$ 总能被转换为回文；
- 所有测试用例的 $s$ 长度总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了将字符串转换为回文必须进行操作的最小子串长度。


## 说明/提示

第一个示例中，可以按如下方式操作：baba → baab。

第二个示例中，字符串已经是回文，因此可以选择空子串进行操作。

第三个示例中，可以按如下方式操作：ddaa → adda。

第四个示例中，可以按如下方式操作：acbacddacbca → acbcaddacbca。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
baba
cc
ddaa
acbacddacbca
```

### 输出

```
2
0
3
2
```



---

---
title: "Mishkin Energizer"
layout: "post"
diff: 普及+/提高
pid: CF2092D
tag: ['字符串', '贪心']
---

# Mishkin Energizer

## 题目描述

为了准备与老朋友 Fernan 的决斗，Edmond 正在制作一种名为 "Mishkin Energizer" 的能量饮料。该饮料由一个长度为 $n$ 的字符串 $s$ 构成，仅包含字符 L、I 和 T，分别对应饮料中三种不同物质的含量。

当饮料中所有三种物质的数量相等时，我们称其为平衡的。为了增强气场并确保决斗胜利，Edmond 必须通过以下操作使初始字符串变为平衡状态：

1. 选择一个下标 $i$ 满足 $s_i \neq s_{i+1}$（此时 $i + 1$ 必须不超过字符串当前长度）。
2. 在它们之间插入一个字符 $x$（可以是 L、I 或 T），且满足 $x \neq s_i$ 和 $x \neq s_{i+1}$。

帮助 Edmond 通过不超过 $\textbf{2n}$ 次操作使饮料平衡并赢得决斗。若存在多种解，可输出任意一种。若不可能实现，需报告此情况。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \le t \le 100$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \le n \le 100$) —— 字符串 $s$ 的长度。

每个测试用例的第二行包含一个长度为 $n$ 的字符串 $s$，仅由字符 L、I 和 T 组成。

## 输出格式

对于每个测试用例，若无解则输出 $-1$。否则：

- 第一行输出一个整数 $m$ ($0 \le m \le 2n$) —— 执行的操作次数。
- 接下来的 $m$ 行中，第 $l$ 行输出一个整数 $i$ ($1 \le i < n + l - 1$)，表示在第 $i$ 和 $i + 1$ 个字符之间插入新字符。该操作必须满足 $s_i \neq s_{i+1}$。

若有多种解，可输出任意一种。注意本题不要求最小化操作次数。

## 说明/提示

第一个测试案例中，可执行以下操作序列：TILII $\rightarrow$ TLILII $\rightarrow$ TLTILII $\rightarrow$ TLTLILII $\rightarrow$ TLTLTILII。

第二个测试案例中无法进行任何操作，答案为 $-1$。

第三个测试案例中初始字符串已满足三种物质数量相等。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5
TILII
1
L
3
LIT
```

### 输出

```
4
1
2
3
4
-1
0
```



---

---
title: "Hackers and Neural Networks"
layout: "post"
diff: 普及+/提高
pid: CF2093F
tag: ['字符串', '贪心', '枚举']
---

# Hackers and Neural Networks

## 题目描述

黑客们再次尝试利用神经网络的输出来创造有趣的短语。这次，他们希望获得一个长度为 $n$ 的字符串数组 $a$。

最初，他们有一个长度为 $n$ 的数组 $c$，其中所有位置都是空白，用符号 $*$ 表示。例如，如果 $n=4$，那么初始时 $c=[*,*,*,*]$。

黑客们可以访问 $m$ 个神经网络，每个神经网络都有自己对请求的答案版本——一个长度为 $n$ 的字符串数组 $b_i$。

黑客们试图通过以下操作从数组 $c$ 得到数组 $a$：

1. 选择一个神经网络 $i$，它将执行对数组 $c$ 的下一个操作：随机选择一个空白位置（例如位置 $j$），并将 $c_j$ 替换为 $b_{i, j}$。例如，如果选择第一个神经网络且 $c = [*, \text{«like»}, *]$，而 $b_1 = [\text{«I»}, \text{«love»}, \text{«apples»}]$，那么经过第一个神经网络的操作后，$c$ 可能变为 $[\text{«I»}, \text{«like»}, *]$ 或 $[*, \text{«like»}, \text{«apples»}]$。
2. 选择一个位置 $j$，并将 $c_j$ 替换为空白。

不幸的是，由于黑客访问神经网络的方式，他们只能在所有操作完成后看到修改后的数组 $c$，因此他们必须提前指定完整的操作序列。

然而，神经网络的随机行为可能导致无法获得目标数组 $a$，或者需要过多的操作才能获得它。

因此，黑客们希望你能帮助他们选择一个操作序列，确保以最少的操作次数获得数组 $a$。

更正式地说，如果存在一个操作序列可以确保从数组 $c$ 得到数组 $a$，那么在所有这样的序列中，找出操作次数最少的序列，并输出其中的操作次数。

如果不存在将数组 $c$ 转换为数组 $a$ 的操作序列，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 500$）——原始数组 $a$ 的长度和神经网络的数量。

每个测试用例的第二行包含数组 $a$，由 $n$ 个字符串 $a_i$（$1 \le |a_i| \le 10$）组成，用空格分隔。

接下来的 $m$ 行，每行包含一个数组 $b_i$，由 $n$ 个字符串 $b_{i, j}$（$1 \le |b_{i,j}| \le 10$）组成，用空格分隔。

保证所有测试用例的 $|a_i|$ 和 $|b_{i, j}|$ 的总和不超过 $2 \cdot 10^5$，且所有测试用例的 $n \cdot m$ 总和也不超过 $2 \cdot 10^5$。

保证输入字符串仅由大小写拉丁字母组成。

注意，每个输入字符串的长度不超过 $10$。

## 输出格式

输出 $t$ 个数字——每个测试用例一个数字，每个数字单独占一行。

如果存在确保从第 $i$ 个测试用例的数组 $c$ 得到数组 $a$ 的操作序列，则第 $i$ 个数字是该序列的最小操作次数。

否则，对于第 $i$ 个数字，输出 $-1$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
I love apples
He likes apples
I love cats
They love dogs
3 2
Icy wake up
wake Icy up
wake up Icy
4 3
c o D E
c o D s
c O l S
c o m E
4 5
a s k A
d s D t
O R i A
a X b Y
b a k A
u s k J
```

### 输出

```
5
-1
6
8
```



---

---
title: "Queries for Number of Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF245H
tag: ['字符串', '动态规划 DP', '区间 DP', '前缀和']
---

# Queries for Number of Palindromes

## 题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

## 输入格式

第1行，给出s，s的长度小于5000
第2行给出q(1<=q<=10^6)
第2至2+q行 给出每组询问的l和r

## 输出格式

输出每组询问所问的数量。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5

```

### 输出

```
1
7
3
4
2

```



---

---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```



---

---
title: "Kids' Riddle"
layout: "post"
diff: 普及+/提高
pid: CF784B
tag: ['字符串', '进制']
---

# Kids' Riddle

## 题目描述

Programmers' kids solve this riddle in 5-10 minutes. How fast can you do it?

## 输入格式

The input contains a single integer $ n $ ( $ 0<=n<=2000000000 $ ).

## 输出格式

Output a single integer.

## 样例 #1

### 输入

```
11

```

### 输出

```
2

```

## 样例 #2

### 输入

```
14

```

### 输出

```
0

```

## 样例 #3

### 输入

```
61441

```

### 输出

```
2

```

## 样例 #4

### 输入

```
571576

```

### 输出

```
10

```

## 样例 #5

### 输入

```
2128506

```

### 输出

```
3

```



---

---
title: "Touchy-Feely Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF784D
tag: ['字符串']
---

# Touchy-Feely Palindromes

## 输入格式

The only line of the input contains a string of digits. The length of the string is between $ 1 $ and $ 10 $ , inclusive.

## 输出格式

Output "Yes" or "No".

## 样例 #1

### 输入

```
373

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
121

```

### 输出

```
No

```

## 样例 #3

### 输入

```
436

```

### 输出

```
Yes

```



---

---
title: "Palindrome Degree"
layout: "post"
diff: 普及+/提高
pid: CF7D
tag: ['字符串', '哈希 hashing', '构造']
---

# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 输入格式

The first line of the input data contains a non-empty string, consisting of Latin letters and digits. The length of the string does not exceed $ 5·10^{6} $ . The string is case-sensitive.

## 输出格式

Output the only number — the sum of the polindrome degrees of all the string's prefixes.

## 样例 #1

### 输入

```
a2A

```

### 输出

```
1
```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
6
```



---

---
title: "String Reconstruction"
layout: "post"
diff: 普及+/提高
pid: CF827A
tag: ['模拟', '字符串', '并查集']
---

# String Reconstruction

## 题目描述

Ivan有一个只包含小写英文字母的字符串s。然而他的朋友Julia为了捉弄他藏起了字符串s。

相比起找回原来的字符串，Ivan更倾向于造一个新的。

 

Ivan知道一些有关于字符串s的信息。这意味着他记得字符串$t_{i}$在字符串s中至少出现了$k_{i}$次，以及$k_{i}$个$t_{i}$在s中出现的位置--$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$。他记得n个这样的字符串$t_{i}$。



 你要重建出一个符合Ivan记得的所有信息的字符串，如果有多个答案符合要求，取字典序最小的一个。字符串$t_{i}$只包含小写字母。

## 输入格式

第一行包括一个整数n(1<=n<=$10^{5}$),代表了Ivan所记得的字符串数量。



下面的n行包括有关于这些字符串的信息。第i+1包括一个非空字符串$t_{i}$，一个正整数$k_{i}$(代表了$t_{i}$在字符串s中出现的次数)，然后是$k_{i}$个正整数$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$（升序输入），代表了$t_{i}$在字符串s中出现的起始位置。



保证字符串$t_{i}$的长度之和不超过$10^{6}$，1<=$x_{i,j}$<=$10^{6}$，1<=$k_{i}$<=$10^{6}$，且$k_{i}$的和不超过$10^{6}$。可能存在相同的$t_{i}$。



数据保证一定有解。

## 输出格式

输出满足条件的字典序最小的字符串。

## 样例 #1

### 输入

```
3
a 4 1 3 5 7
ab 2 1 5
ca 1 4

```

### 输出

```
abacaba

```

## 样例 #2

### 输入

```
1
a 1 3

```

### 输出

```
aaa

```

## 样例 #3

### 输入

```
3
ab 1 1
aba 1 3
ab 2 3 5

```

### 输出

```
ababab

```



---

---
title: "Balanced Substring"
layout: "post"
diff: 普及+/提高
pid: CF873B
tag: ['字符串', '前缀和']
---

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 输入格式

The first line contains $ n $ ( $ 1<=n<=100000 $ ) — the number of characters in $ s $ .

The second line contains a string $ s $ consisting of exactly $ n $ characters. Only characters 0 and 1 can appear in $ s $ .

## 输出格式

If there is no non-empty balanced substring in $ s $ , print 0. Otherwise, print the length of the longest balanced substring.

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
111

```

### 输出

```
0

```



---

---
title: "Nephren gives a riddle"
layout: "post"
diff: 普及+/提高
pid: CF896A
tag: ['字符串', '递归']
---

# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 输入格式

第一行一个正整数 $q$，表示询问的次数。

接下来 $q$ 行，每行两个整数 $n,k$。

## 输出格式

输出一行 $q$ 个字符。第 $i$ 个字符表示第 $i$ 组询问时 $f_{n,k}$ 的值。如果第 $i$ 组询问时 $\lvert f_n\rvert<k$，则第 $i$ 个字符输出 `.`。

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111

```

### 输出

```
Wh.
```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66

```

### 输出

```
abdef
```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474

```

### 输出

```
Areyoubusy
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

