---
title: "Delete from the Left"
layout: "post"
diff: 普及-
pid: CF1005B
tag: ['字符串']
---

# Delete from the Left

## 题目描述

You are given two strings $ s $ and $ t $ . In a single move, you can choose any of two strings and delete the first (that is, the leftmost) character. After a move, the length of the string decreases by $ 1 $ . You can't choose a string if it is empty.

For example:

- by applying a move to the string "where", the result is the string "here",
- by applying a move to the string "a", the result is an empty string "".

You are required to make two given strings equal using the fewest number of moves. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the initial strings.

Write a program that finds the minimum number of moves to make two given strings $ s $ and $ t $ equal.

## 输入格式

The first line of the input contains $ s $ . In the second line of the input contains $ t $ . Both strings consist only of lowercase Latin letters. The number of letters in each string is between 1 and $ 2\cdot10^5 $ , inclusive.

## 输出格式

Output the fewest number of moves required. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the given strings.

## 说明/提示

In the first example, you should apply the move once to the first string and apply the move once to the second string. As a result, both strings will be equal to "est".

In the second example, the move should be applied to the string "codeforces" $ 8 $ times. As a result, the string becomes "codeforces" $ \to $ "es". The move should be applied to the string "yes" once. The result is the same string "yes" $ \to $ "es".

In the third example, you can make the strings equal only by completely deleting them. That is, in the end, both strings will be empty.

In the fourth example, the first character of the second string should be deleted.

## 样例 #1

### 输入

```
test
west

```

### 输出

```
2

```

## 样例 #2

### 输入

```
codeforces
yes

```

### 输出

```
9

```

## 样例 #3

### 输入

```
test
yes

```

### 输出

```
7

```

## 样例 #4

### 输入

```
b
ab

```

### 输出

```
1

```



---

---
title: "Romaji"
layout: "post"
diff: 普及-
pid: CF1008A
tag: ['字符串']
---

# Romaji

## 题目描述

Vitya has just started learning Berlanese language. It is known that Berlanese uses the Latin alphabet. Vowel letters are "a", "o", "u", "i", and "e". Other letters are consonant.

In Berlanese, there has to be a vowel after every consonant, but there can be any letter after any vowel. The only exception is a consonant "n"; after this letter, there can be any letter (not only a vowel) or there can be no letter at all. For example, the words "harakiri", "yupie", "man", and "nbo" are Berlanese while the words "horse", "king", "my", and "nz" are not.

Help Vitya find out if a word $ s $ is Berlanese.

## 输入格式

The first line of the input contains the string $ s $ consisting of $ |s| $ ( $ 1\leq |s|\leq 100 $ ) lowercase Latin letters.

## 输出格式

Print "YES" (without quotes) if there is a vowel after every consonant except "n", otherwise print "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first and second samples, a vowel goes after each consonant except "n", so the word is Berlanese.

In the third sample, the consonant "c" goes after the consonant "r", and the consonant "s" stands on the end, so the word is not Berlanese.

## 样例 #1

### 输入

```
sumimasen

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
ninja

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
codeforces

```

### 输出

```
NO

```



---

---
title: "Obtaining the String"
layout: "post"
diff: 普及-
pid: CF1015B
tag: ['字符串', '贪心']
---

# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 50 $ ) — the length of strings $ s $ and $ t $ .

The second line of the input contains the string $ s $ consisting of $ n $ lowercase Latin letters.

The third line of the input contains the string $ t $ consisting of $ n $ lowercase Latin letters.

## 输出格式

If it is impossible to obtain the string $ t $ using moves, print "-1".

Otherwise in the first line print one integer $ k $ — the number of moves to transform $ s $ to $ t $ . Note that $ k $ must be an integer number between $ 0 $ and $ 10^4 $ inclusive.

In the second line print $ k $ integers $ c_j $ ( $ 1 \le c_j < n $ ), where $ c_j $ means that on the $ j $ -th move you swap characters $ s_{c_j} $ and $ s_{c_j + 1} $ .

If you do not need to apply any moves, print a single integer $ 0 $ in the first line and either leave the second line empty or do not print it at all.

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec

```

### 输出

```
4
3 5 4 5 

```

## 样例 #2

### 输入

```
4
abcd
accd

```

### 输出

```
-1

```



---

---
title: "Equality"
layout: "post"
diff: 普及-
pid: CF1038A
tag: ['字符串']
---

# Equality

## 题目描述

### 题目大意：
给定一个长度为$n$的字符串和$k$，问这个字符串包含字母表前$k$个大写字母并且数量相同的子序列最长是多少

## 输入格式

第一行两个整数$n,k$

第二行一个长度为$n$的字符串

第一行两个整数$n,k$

第二行一个长度为$n$的字符串

## 输出格式

一个整数，表示最小长度

```
### 题目大意：
给定一个长度为$n$的字符串和$k$，问这个字符串包含字母表前$k$个大写字母并且数量相同的子序列最长是多少

一个整数，表示最小长度
```

## 样例 #1

### 输入

```
9 3
ACAABCCAB

```

### 输出

```
6
```

## 样例 #2

### 输入

```
9 4
ABCABCABC

```

### 输出

```
0
```



---

---
title: "Oh Those Palindromes"
layout: "post"
diff: 普及-
pid: CF1063A
tag: ['字符串', '概率论', '构造']
---

# Oh Those Palindromes

## 题目描述

一个非空字符串叫做回文串。如果它从左到右，从右到左读相同，那么它就是回文串。
例如，“ABCBA”,“A”和“ABBA”都是回文串，而“ABAB”和“XY”则不是。




如果可以通过从字符串的开头和结尾删除一些（可能为零）字符来从该字符串获得新字符串，
则新字符串叫做另一个字符串的子字符串。
例如，“ABC”、“AB”和“C”是字符串“ABC”的子串，而“AC”和“D”不是。


我们把字符串的“回文计数”定义为回文的子串个数。
例如，字符串“aaa”的回文计数是6，因为它的所有子字符串都是回文，
而字符串“abc”的回文计数是3，因为只有长度为1的子字符串是回文。


给你一个字符串S。你可以任意地重新排列它的字符，求它的回文计数最大值。

## 输入格式

第一行包含整数n（1≤n≤100000）表示字符串s的长度。




第二行包含字符串S，它由n个小写字母组成。

## 输出格式

输出字符串t，（它是字符串s的一种排列）
此外，t应该具有最大回文计数的可能值。




如果有多个这样的字符串，输出它们中的任何一个。

## 输入输出样例：
#### 输入样例#1：
```
5
oolol
```
#### 输出样例#1：
```
ololo
```

#### 输入样例#2：
```
16
gagadbcgghhchbdf
```
#### 输出样例#2：
```
16
gagadbcgghhchbdf
```

## 说明/提示

在第一个例子中，字符串“ololo”有9个9回文子串：
"o","l","o","l","o","olo","lol","olo","oloo"

注意，即使某些子串重合，它们也会在生成的字符串中计入多次。




在第二个例子中，字符串“abccbaghghghgdfd”的回文计数为29。

## 样例 #1

### 输入

```
5
oolol

```

### 输出

```
ololo

```

## 样例 #2

### 输入

```
16
gagadbcgghhchbdf

```

### 输出

```
abccbaghghghgdfd

```



---

---
title: "Diverse Substring"
layout: "post"
diff: 普及-
pid: CF1073A
tag: ['字符串', '枚举', '概率论']
---

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the length of string $ s $ .

The second line is the string $ s $ , consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

Print "NO" if there is no diverse substring in the string $ s $ .

Otherwise the first line should contain "YES". The second line should contain any diverse substring of string $ s $ .

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces

```

### 输出

```
YES
code

```

## 样例 #2

### 输入

```
5
aaaaa

```

### 输出

```
NO

```



---

---
title: "Lucky Sum of Digits"
layout: "post"
diff: 普及-
pid: CF109A
tag: ['字符串', '贪心', '枚举']
---

# Lucky Sum of Digits

## 题目描述

Petya喜欢幸运数字。我们都知道幸运数字是只含有$4$ 和$7$ 的正整数。例如数字$47$ ，$744$ ，$4$ 是幸运数字，而$5$ ，$17$ ，$467$ 不是。

Petya急切的想知道各个数位上数字的和为$n$ 的最小幸运数字是多少。帮助他完成这个任务。

## 输入格式

一行一个整数$n$ （$1\leq n\leq 10^6$ ） — 要求的幸运数字各个数位上数字的和。

## 输出格式

输出仅一行为这个结果 — 这个最小的各数位上和为$n$ 的幸运数。如果这个数不存在输出-1。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
11

```

### 输出

```
47

```

## 样例 #2

### 输入

```
10

```

### 输出

```
-1

```



---

---
title: "Lucky String"
layout: "post"
diff: 普及-
pid: CF110B
tag: ['字符串', '贪心']
---

# Lucky String

## 题目描述

Petya loves lucky numbers. We all know that lucky numbers are the positive integers whose decimal representations contain only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya recently learned to determine whether a string of lowercase Latin letters is lucky. For each individual letter all its positions in the string are written out in the increasing order. This results in $ 26 $ lists of numbers; some of them can be empty. A string is considered lucky if and only if in each list the absolute difference of any two adjacent numbers is a lucky number.

For example, let's consider string "zbcdzefdzc". The lists of positions of equal letters are:

- b: $ 2 $
- c: $ 3,10 $
- d: $ 4,8 $
- e: $ 6 $
- f: $ 7 $
- z: $ 1,5,9 $
- Lists of positions of letters a, g, h, ..., y are empty.

This string is lucky as all differences are lucky numbers. For letters z: $ 5-1=4 $ , $ 9-5=4 $ , for letters c: $ 10-3=7 $ , for letters d: $ 8-4=4 $ .

Note that if some letter occurs only once in a string, it doesn't influence the string's luckiness after building the lists of positions of equal letters. The string where all the letters are distinct is considered lucky.

Find the lexicographically minimal lucky string whose length equals $ n $ .

## 输入格式

The single line contains a positive integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the sought string.

## 输出格式

Print on the single line the lexicographically minimal lucky string whose length equals $ n $ .

## 说明/提示

The lexical comparison of strings is performed by the < operator in modern programming languages. String $ a $ is lexicographically less than string $ b $ if exists such $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ .

## 样例 #1

### 输入

```
5

```

### 输出

```
abcda

```

## 样例 #2

### 输入

```
3

```

### 输出

```
abc

```



---

---
title: "Strings Equalization"
layout: "post"
diff: 普及-
pid: CF1223B
tag: ['字符串']
---

# Strings Equalization

## 题目描述

You are given two strings of equal length $ s $ and $ t $ consisting of lowercase Latin letters. You may perform any number (possibly, zero) operations on these strings.

During each operation you choose two adjacent characters in any string and assign the value of the first character to the value of the second or vice versa.

For example, if $ s $ is "acbc" you can get the following strings in one operation:

- "aabc" (if you perform $ s_2 = s_1 $ );
- "ccbc" (if you perform $ s_1 = s_2 $ );
- "accc" (if you perform $ s_3 = s_2 $ or $ s_3 = s_4 $ );
- "abbc" (if you perform $ s_2 = s_3 $ );
- "acbb" (if you perform $ s_4 = s_3 $ );

Note that you can also apply this operation to the string $ t $ .

Please determine whether it is possible to transform $ s $ into $ t $ , applying the operation above any number of times.

Note that you have to answer $ q $ independent queries.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 100 $ ) — the number of queries. Each query is represented by two consecutive lines.

The first line of each query contains the string $ s $ ( $ 1 \le |s| \le 100 $ ) consisting of lowercase Latin letters.

The second line of each query contains the string $ t $ ( $ 1 \le |t| \leq 100 $ , $ |t| = |s| $ ) consisting of lowercase Latin letters.

## 输出格式

For each query, print "YES" if it is possible to make $ s $ equal to $ t $ , and "NO" otherwise.

You may print every letter in any case you want (so, for example, the strings "yEs", "yes", "Yes", and "YES" will all be recognized as positive answer).

## 说明/提示

In the first query, you can perform two operations $ s_1 = s_2 $ (after it $ s $ turns into "aabb") and $ t_4 = t_3 $ (after it $ t $ turns into "aabb").

In the second query, the strings are equal initially, so the answer is "YES".

In the third query, you can not make strings $ s $ and $ t $ equal. Therefore, the answer is "NO".

## 样例 #1

### 输入

```
3
xabb
aabx
technocup
technocup
a
z

```

### 输出

```
YES
YES
NO

```



---

---
title: "Correct Solution?"
layout: "post"
diff: 普及-
pid: CF12B
tag: ['字符串', '排序']
---

# Correct Solution?

## 题目描述

在一个寒冷的冬夜，Alice 和她的哥哥 Bob 正坐在家中的壁炉旁，玩一个有趣的游戏。

Alice 给出了一个数 $n$，并让 Bob 找到满足以下条件的数：

- 通过将这个数的数位打乱，得到一个没有前导零的最小的新数。

“没问题！“ Bob 立刻给出了答案。因为 Alice 并不知道哥哥的答案是否正确，所以她将 $n$ 和哥哥给出的答案给了你，希望你能帮她判断这个答案是否正确。

## 输入格式

第一行，一个正整数 $n\,(0 \le n \le 10^9)$，保证没有前导零。

第二行，一个正整数 $m\,(0 \le m \le 10^9)$，表示 Bob 给出的答案，可能有前导零。

## 输出格式

如果 Bob 的答案正确，输出 `OK`，否则输出 `WRONG_ANSWER`。

-----

翻译 By @[Eason_cyx](https://luogu.com.cn/user/741244)。

## 样例 #1

### 输入

```
3310
1033

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
4
5

```

### 输出

```
WRONG_ANSWER

```



---

---
title: "Make Even"
layout: "post"
diff: 普及-
pid: CF1611A
tag: ['字符串', '数学', '构造']
---

# Make Even

## 题目描述

Polycarp 有一个不包含数字 $0$ 的整数 $n$。他可以使用他的数字执行以下操作数次（可能为零）：

将 $n$ 的长度 $l\ (1 \leq l \leq |n|$，这里 $|n|$ 指 $n$ 的十进制长度 $)$ 的前缀反转，即反转 $n$ 的 前 $l$ 位数字。那么，第 $1$ 个数位（默认从左向右数，下文同理）将与第 $l$ 个数位交换，第 $2$ 个数位与第 $(l-1)$ 个交换......以此类推。

例如，如果 $n=123456789$ 且 $l=5$，则 $n$ 变换后的值将为 $543216789$。

对于不同的操作，$l$ 的值可能不同。

Polycarp 喜欢偶数，并且非常不耐烦。因此，他想用最少的操作次数使他的数字 $n$ 变成偶数。

**本题有多组数据。**

## 输入格式

第一行，一个整数 $t\ (1 \leq t \leq 10^4)$，表示数据的组数。

接下来 $t$ 行，每行一个数 $n\ (1 \leq n \leq 10^9)$。可以保证该数中各数位没有 $0$。

## 输出格式

共 $t$ 行，每行一个整数，表示将该数字变成偶数的最小操作次数。如果无论如何操作，都无法变为偶数，则输出 `-1`。

## 样例 #1

### 输入

```
4
3876
387
4489
3
```

### 输出

```
0
2
1
-1
```



---

---
title: "Spreadsheets"
layout: "post"
diff: 普及-
pid: CF1B
tag: ['模拟', '字符串', '进制']
---

# Spreadsheets

## 题目描述

In the popular spreadsheets systems (for example, in Excel) the following numeration of columns is used. The first column has number A, the second — number B, etc. till column 26 that is marked by Z. Then there are two-letter numbers: column 27 has number AA, 28 — AB, column 52 is marked by AZ. After ZZ there follow three-letter numbers, etc.

The rows are marked by integer numbers starting with 1. The cell name is the concatenation of the column and the row numbers. For example, BC23 is the name for the cell that is in column 55, row 23.

Sometimes another numeration system is used: RXCY, where X and Y are integer numbers, showing the column and the row numbers respectfully. For instance, R23C55 is the cell from the previous example.

Your task is to write a program that reads the given sequence of cell coordinates and produce each item written according to the rules of another numeration system.


## 输入格式

The first line of the input contains integer number $ n $ ( $ 1<=n<=10^{5} $ ), the number of coordinates in the test. Then there follow $ n $ lines, each of them contains coordinates. All the coordinates are correct, there are no cells with the column and/or the row numbers larger than $ 10^{6} $ .


## 输出格式

Write $ n $ lines, each line should contain a cell coordinates in the other numeration system.


## 样例 #1

### 输入

```
2
R23C55
BC23

```

### 输出

```
BC23
R23C55

```



---

---
title: "Shohag Loves Strings"
layout: "post"
diff: 普及-
pid: CF2039B
tag: ['字符串', '贪心']
---

# Shohag Loves Strings

## 题目描述

# Shohag Loves Strings

## 问题描述

给定一个字符串 $s$，定义 $f(p)$ 为字符串 $p$ 的所有不同的非空子字符串的数量。从字符串 $s$ 中找到一个非空子字符串 $p$，使得 $f(p)$ 为偶数。如果找不到这样的子字符串，则输出 $-1$。

## 输入格式

- 第一行包含一个整数 $t$，表示测试数量 $(1 \le t \le 10^4)$。
- 接下来 $t$ 行，每行一个字符串 $s$，表示每次测试中的字符串 $s$。$(1 \le |s| \le 10^5)$，且所有字符串的总长度不超过 $3 \times 10^5$。

## 输出格式

- 对于每次测试，输出一个非空子字符串 $p$，使得 $f(p)$ 为偶数，如果不存在这样的子字符串，则输出 $-1$ 。若存在多个解，输出任意一个即可。

## 样例 #1

### 输入

```
5
dcabaac
a
youknowwho
codeforces
bangladesh
```

### 输出

```
abaa
-1
youknowwho
eforce
bang
```



---

---
title: "Serval and String Theory"
layout: "post"
diff: 普及-
pid: CF2085A
tag: ['字符串', '分类讨论']
---

# Serval and String Theory

## 题目描述

仅由小写拉丁字母组成的字符串 $r$ 被称为**通用字符串**，当且仅当 $r$ 在字典序上小于$^{\text{∗}}$其反转$^{\text{†}}$后的字符串。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。你需要通过最多 $k$ 次操作使 $s$ 成为通用字符串。每次操作可执行以下步骤：
- 选择两个下标 $i$ 和 $j$（$1 \le i, j \le n$），交换 $s_i$ 和 $s_j$。注意若 $i = j$，则不进行任何操作。

请判断是否能在最多 $k$ 次操作内使 $s$ 成为通用字符串。

$^{\text{∗}}$当两个长度相同的字符串 $a$ 和 $b$ 满足以下条件时，称 $a$ 的字典序小于 $b$：
- 在第一个不同的位置上，$a$ 的字符在字母表中出现的时间早于 $b$ 对应位置的字符。

$^{\text{†}}$字符串 $r$ 的反转是指将 $r$ 从右向左书写得到的新字符串。例如，字符串 $\texttt{abcad}$ 的反转为 $\texttt{dacba}$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 500$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 100$，$0 \le k \le 10^4$）——字符串 $s$ 的长度及允许的最大操作次数。

第二行输入一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

## 输出格式

对于每个测试用例，若能在最多 $k$ 次操作内使 $s$ 成为通用字符串，输出 "YES"，否则输出 "NO"。

答案可以任意大小写形式输出（例如 "yEs"、"yes"、"Yes" 和 "YES" 均视为肯定回答）。


## 说明/提示

第一个测试案例中，任何操作后 $s$ 均保持不变。但 $\texttt{a}$ 的反转仍为 $\texttt{a}$，因此无法使其成为通用字符串。

第二个测试案例中，字符串 $\texttt{rev}$ 的字典序小于其反转 $\texttt{ver}$，因此 $s$ 已经是通用字符串。

第五个测试案例中，可按以下步骤操作：
1. 交换 $s_4$ 和 $s_7$，此时 $s$ 变为 $\texttt{uniserval}$；
2. 交换 $s_1$ 和 $s_3$，此时 $s$ 变为 $\texttt{inuserval}$。

字符串 $\texttt{inuserval}$ 是通用字符串。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
1 10000
a
3 3
rev
6 0
string
6 0
theory
9 2
universal
19 0
codeforcesecrofedoc
19 1
codeforcesecrofedoc
3 1
zzz
```

### 输出

```
NO
YES
NO
YES
YES
NO
YES
NO
```



---

---
title: "Tung Tung Sahur"
layout: "post"
diff: 普及-
pid: CF2094D
tag: ['模拟', '字符串']
---

# Tung Tung Sahur

## 题目描述

你面前有两个鼓：一个左鼓和一个右鼓。敲击左鼓可以记录为 "L"，敲击右鼓可以记录为 "R"。

这个世界的奇怪力量变幻莫测：有时一次敲击会发出一声响，有时会发出两声响。因此，敲击左鼓可能会发出 "L" 或 "LL"，敲击右鼓可能会发出 "R" 或 "RR"。

敲击的序列记录在字符串 $p$ 中，而实际听到的声音记录在字符串 $s$ 中。给定 $p$ 和 $s$，判断字符串 $s$ 是否可能是由 $p$ 的敲击产生的结果。

例如，如果 $p=$ "LR"，那么敲击产生的结果可能是 "LR"、"LRR"、"LLR" 或 "LLRR"，但不可能是 "LLLR" 或 "LRL"。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——独立测试用例的数量。

每个测试用例的第一行包含字符串 $p$（$1 \le |p| \le 2 \cdot 10^5$），仅由字符 "R" 和 "L" 组成，其中 $|p|$ 表示字符串 $p$ 的长度。

每个测试用例的第二行包含字符串 $s$（$1 \le |p| \le |s| \le 2 \cdot 10^5$），同样仅由字符 "R" 和 "L" 组成。

保证所有测试用例的 $|s|$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每组输入数据，如果 $s$ 可能是听到的声音，输出 "YES"，否则输出 "NO"。输出不区分大小写。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
R
RR
LRLR
LRLR
LR
LLLR
LLLLLRL
LLLLRRLL
LLRLRLRRL
LLLRLRRLLRRRL
```

### 输出

```
YES
YES
NO
NO
YES
```



---

---
title: "Down with Brackets"
layout: "post"
diff: 普及-
pid: CF2110B
tag: ['字符串']
---

# Down with Brackets

## 题目描述

在 2077 年，机器人决定一劳永逸地摆脱平衡括号序列！

一个括号序列被称为**平衡的**，如果它可以通过以下形式文法构造：

1. 空序列 $\varnothing$ 是平衡的。
2. 如果括号序列 $A$ 是平衡的，那么 $\mathtt{(}A\mathtt{)}$ 也是平衡的。
3. 如果括号序列 $A$ 和 $B$ 是平衡的，那么拼接序列 $A B$ 也是平衡的。

你是对抗平衡括号序列部门的负责人，你的主要任务是确定哪些括号可以被销毁，哪些不能。

给定一个由字符串 $s$ 表示的平衡括号序列，仅包含字符 `(` 和 `)`。由于机器人的能力有限，它们只能从字符串中**恰好删除一个左括号和一个右括号**。

你的任务是判断机器人是否能删除这样两个括号，使得字符串 $s$ **不再**是一个平衡括号序列。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例由一个字符串 $s$（$2 \leq |s| \leq 2 \cdot 10^5$）组成——仅由 `(` 和 `)` 构成的序列。

保证 $s$ 是一个平衡括号序列。  
同时保证所有测试用例的 $|s|$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果机器人可以使字符串不再是平衡括号序列，输出 "YES"；否则输出 "NO"。

输出字母大小写不敏感（如 "yEs"、"yes"、"Yes" 或 "YES" 均被视为肯定答案）。

## 说明/提示

在第一个测试用例中，可以证明机器人无法破坏正确的括号序列。

在第二个测试用例中，一种可行的括号删除方式如下：  
$\texttt{(())}{\color{red}\texttt{(}}\texttt{)(}{\color{red}\texttt{)}} \rightarrow \texttt{(()))(}$，结果不是一个正确的括号序列。

在第四个测试用例中，一种可行的删除方式如下：  
$\texttt{(}{\color{red}\texttt{(}}\texttt{))((}{\color{red}\texttt{)}}\texttt{)}\rightarrow \texttt{())(()}$，结果不是一个正确的括号序列。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
(())
(())()()
()
(())(())
```

### 输出

```
NO
YES
NO
YES
```



---

---
title: "Jabber ID"
layout: "post"
diff: 普及-
pid: CF21A
tag: ['模拟', '字符串']
---

# Jabber ID

## 题目描述

一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。


给出一个地址，询问是否合法。

## 输入格式

一行，一个字符串，表示一个地址（保证地址的字符的 ASCII 在 $33$ 到 $127$ 间），地址长度不超过 $100$ 字符。

## 输出格式

一行，如果合法输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
mike@codeforces.com

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
john.smith@codeforces.ru/contest.icpc/12

```

### 输出

```
NO

```



---

---
title: "Queue at the School"
layout: "post"
diff: 普及-
pid: CF266B
tag: ['字符串', '搜索', '队列']
---

# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 输入格式

The first line contains two integers $ n $ and $ t $ $ (1<=n,t<=50) $ , which represent the number of children in the queue and the time after which the queue will transform into the arrangement you need to find.

The next line contains string $ s $ , which represents the schoolchildren's initial arrangement. If the $ i $ -th position in the queue contains a boy, then the $ i $ -th character of string $ s $ equals "B", otherwise the $ i $ -th character equals "G".

## 输出格式

Print string $ a $ , which describes the arrangement after $ t $ seconds. If the $ i $ -th position has a boy after the needed time, then the $ i $ -th character $ a $ must equal "B", otherwise it must equal "G".

## 样例 #1

### 输入

```
5 1
BGGBG

```

### 输出

```
GBGGB

```

## 样例 #2

### 输入

```
5 2
BGGBG

```

### 输出

```
GGBGB

```

## 样例 #3

### 输入

```
4 1
GGGB

```

### 输出

```
GGGB

```



---

---
title: "DZY Loves Chessboard"
layout: "post"
diff: 普及-
pid: CF445A
tag: ['模拟', '字符串', '搜索', '深度优先搜索 DFS']
---

# DZY Loves Chessboard

## 题目描述

一个棋盘上有一些格子是坏的，另一些是正常的。对于每一个正常的格子，都要在上面放上棋子。
请找到一组解使没有两个相同颜色的棋子相邻(两个格子相邻为它们存在共同的边)

## 输入格式

第一行为两个数n,m。(1<=n,m<=100)
下面n行，每个格子上的字符为'-'或'.','-'表示坏掉的格子,'.'表示正常的格子。

## 输出格式

输出n行，每行m个字符。第i个字符串的第j个字符应为“W”，“B”或“ - ”。字符“W”是指在格子上放白色的棋子，“B”意味着放黑色的棋子，“ - ”表示坏掉的格子。
如果有多组答案，输出其中的一个

感谢@zhaotiensn 提供的翻译

## 样例 #1

### 输入

```
1 1
.

```

### 输出

```
B

```

## 样例 #2

### 输入

```
2 2
..
..

```

### 输出

```
BW
WB

```

## 样例 #3

### 输入

```
3 3
.-.
---
--.
```

### 输出

```
B-B
---
--B
```



---

---
title: "Sum"
layout: "post"
diff: 普及-
pid: CF49B
tag: ['字符串', '进制', '位运算']
---

# Sum

## 题目描述

Vasya终于学会了进位制，但他经常忘记写算式的基数。有一次，他看到他的笔记本上写着a+b=？，但是没有写明基数。现在Vasya认为算式的基数为p。他知道算式在不同的基数下，会有不同的结果，甚至在有些基数下是没有意义的。算式78+87的值在十六进制下为FF，在十五进制下为110，十进制下为165，九进制下为176，更小的基数下就没有意义了。现在，Vasya想要知道算式结果的最大长度。
我们定义数字的长度为数字的字符个数，在不同的进制下，同一个数字有不同的数字长度。

## 输入格式

共一行，包含两个数a，b。

## 输出格式

共一行，输出算式的最大长度。

Translated by @handahao

## 样例 #1

### 输入

```
78 87

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
2

```



---

---
title: "Registration system"
layout: "post"
diff: 普及-
pid: CF4C
tag: ['字符串', '哈希 hashing']
---

# Registration system

## 题目描述

### 题目背景

一个名为 "Berlanddesk" 的电子邮件系统即将在 Berland 上线运营。该电子邮件系统的管理员希望整个系统的建设可以尽早完成，因此他们找到了资深程序员您，希望您能够为他们开发一个用户注册系统的原型产品。

该系统的运行遵循以下原则:

新用户注册时，他将向系统发送一则内容为其用户名的请求，如果该用户名尚未存在于系统数据库内，则将该用户名插入数据库，同时用户得到回应信息 ```OK``` 表示其已经成功注册。如果用户请求的用户名已经存在于数据库内，那么系统将产生一个新的用户名并将其加入数据库。新用户名由用户请求的用户名与正整数 $i$ 构成，$i$ 为使 "用户名i" 尚未存在于数据库内的最小的 $i$。

## 输入格式

第一行一个整数 $n(1 \le n \le 10^5)$。接下来 $n$ 行，每行表示用户向系统发出的一则请求。每行内容均非空且均为由至多 $32$ 个小写拉丁字母组成的字符串。

## 输出格式

$n$ 行，每行表示系统对一则请求做出的回应。如果该用户名尚未存在于系统数据库内，则输出 ```OK``` 。如果用户请求的用户名已经被注册，则输出依照规则生成的新用户名。

## 样例 #1

### 输入

```
4
abacaba
acaba
abacaba
acab

```

### 输出

```
OK
OK
abacaba1
OK

```

## 样例 #2

### 输入

```
6
first
first
second
second
third
third

```

### 输出

```
OK
first1
OK
second1
OK
third1

```



---

---
title: "Center Alignment"
layout: "post"
diff: 普及-
pid: CF5B
tag: ['字符串']
---

# Center Alignment

## 题目描述

几乎每一个文本编辑器都有文字居中对齐的功能，因此Berland的著名文本编辑器Textpad的开发者们希望在产品的第四次更新中加入此功能。

您的任务是尽快编写一个文本居中对齐的原型程序，祝您好运!

## 输入格式

输入包含一行或者多行文本，每行均由拉丁字母、数字和/或空格组成，每一行都不会以空格开始或者结束，保证至少有一行长度大于等于1。每行的长度和总行数都不会超过1000。

## 输出格式

将文本居中对齐，用星号'\*'框起整个文本。

如果无法实现完美的居中对齐，请将这一行文本向左或者向右微调(您应该在第一次遇到此类情况时将该行文本向左微调，下一次向右，在下一次向左...依此类推)。

## 样例 #1

### 输入

```
This  is

Codeforces
Beta
Round
5

```

### 输出

```
************
* This  is *
*          *
*Codeforces*
*   Beta   *
*  Round   *
*     5    *
************

```

## 样例 #2

### 输入

```
welcome to the
Codeforces
Beta
Round 5

and
good luck

```

### 输出

```
****************
*welcome to the*
*  Codeforces  *
*     Beta     *
*   Round 5    *
*              *
*      and     *
*  good luck   *
****************

```



---

---
title: "Petya and Java"
layout: "post"
diff: 普及-
pid: CF66A
tag: ['模拟', '字符串', '枚举']
---

# Petya and Java

## 题目描述

Little Petya has recently started attending a programming club. Naturally he is facing the problem of choosing a programming language. After long considerations he realized that Java is the best choice. The main argument in favor of choosing Java was that it has a very large integer data type, called BigInteger.

But having attended several classes of the club, Petya realized that not all tasks require using the BigInteger type. It turned out that in some tasks it is much easier to use small data types. That's why a question arises: "Which integer type to use if one wants to store a positive integer $ n $ ?"

Petya knows only 5 integer types:

1\) byte occupies 1 byte and allows you to store numbers from $ -128 $ to $ 127 $

2\) short occupies 2 bytes and allows you to store numbers from $ -32768 $ to $ 32767 $

3\) int occupies 4 bytes and allows you to store numbers from $ -2147483648 $ to $ 2147483647 $

4\) long occupies 8 bytes and allows you to store numbers from $ -9223372036854775808 $ to $ 9223372036854775807 $

5\) BigInteger can store any integer number, but at that it is not a primitive type, and operations with it are much slower.

For all the types given above the boundary values are included in the value range.

From this list, Petya wants to choose the smallest type that can store a positive integer $ n $ . Since BigInteger works much slower, Peter regards it last. Help him.

## 输入格式

The first line contains a positive number $ n $ . It consists of no more than $ 100 $ digits and doesn't contain any leading zeros. The number $ n $ can't be represented as an empty string.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 输出格式

Print the first type from the list "byte, short, int, long, BigInteger", that can store the natural number $ n $ , in accordance with the data given above.

## 样例 #1

### 输入

```
127

```

### 输出

```
byte

```

## 样例 #2

### 输入

```
130

```

### 输出

```
short

```

## 样例 #3

### 输入

```
123456789101112131415161718192021222324

```

### 输出

```
BigInteger

```



---

---
title: "Letters Cyclic Shift"
layout: "post"
diff: 普及-
pid: CF708A
tag: ['字符串']
---

# Letters Cyclic Shift

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase English letters. You have to pick exactly one non-empty substring of $ s $ and shift all its letters 'z' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'y' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'x' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/23d27bb9cf2cd76a0555d2babeb08bc9315530bc.png) 'b' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'a' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'z'. In other words, each character is replaced with the previous character of English alphabet and 'a' is replaced with 'z'.

What is the lexicographically minimum string that can be obtained from $ s $ by performing this shift exactly once?

## 输入格式

The only line of the input contains the string $ s $ ( $ 1<=|s|<=100000 $ ) consisting of lowercase English letters.

## 输出格式

Print the lexicographically minimum string that can be obtained from $ s $ by shifting letters of exactly one non-empty substring.

## 说明/提示

String $ s $ is lexicographically smaller than some other string $ t $ of the same length if there exists some $ 1<=i<=|s| $ , such that $ s_{1}=t_{1},s_{2}=t_{2},...,s_{i-1}=t_{i-1} $ , and $ s_{i}&lt;t_{i} $ .

## 样例 #1

### 输入

```
codeforces

```

### 输出

```
bncdenqbdr

```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
aaacaba

```



---

---
title: "Verse Pattern"
layout: "post"
diff: 普及-
pid: CF722B
tag: ['字符串']
---

# Verse Pattern

## 题目描述

You are given a text consisting of $ n $ lines. Each line contains some space-separated words, consisting of lowercase English letters.

We define a syllable as a string that contains exactly one vowel and any arbitrary number (possibly none) of consonants. In English alphabet following letters are considered to be vowels: 'a', 'e', 'i', 'o', 'u' and 'y'.

Each word of the text that contains at least one vowel can be divided into syllables. Each character should be a part of exactly one syllable. For example, the word "mamma" can be divided into syllables as "ma" and "mma", "mam" and "ma", and "mamm" and "a". Words that consist of only consonants should be ignored.

The verse patterns for the given text is a sequence of $ n $ integers $ p_{1},p_{2},...,p_{n} $ . Text matches the given verse pattern if for each $ i $ from $ 1 $ to $ n $ one can divide words of the $ i $ -th line in syllables in such a way that the total number of syllables is equal to $ p_{i} $ .

You are given the text and the verse pattern. Check, if the given text matches the given verse pattern.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of lines in the text.

The second line contains integers $ p_{1},...,p_{n} $ ( $ 0<=p_{i}<=100 $ ) — the verse pattern.

Next $ n $ lines contain the text itself. Text consists of lowercase English letters and spaces. It's guaranteed that all lines are non-empty, each line starts and ends with a letter and words are separated by exactly one space. The length of each line doesn't exceed $ 100 $ characters.

## 输出格式

If the given text matches the given verse pattern, then print "YES" (without quotes) in the only line of the output. Otherwise, print "NO" (without quotes).

## 说明/提示

In the first sample, one can split words into syllables in the following way:

`in-tel<br></br>co-de<br></br>ch al-len-ge<br></br>`Since the word "ch" in the third line doesn't contain vowels, we can ignore it. As the result we get $ 2 $ syllabels in first two lines and $ 3 $ syllables in the third one.

## 样例 #1

### 输入

```
3
2 2 3
intel
code
ch allenge

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
1 2 3 1
a
bcdefghi
jklmnopqrstu
vwxyz

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4
13 11 15 15
to be or not to be that is the question
whether tis nobler in the mind to suffer
the slings and arrows of outrageous fortune
or to take arms against a sea of troubles

```

### 输出

```
YES

```



---

---
title: "Gotta Catch Em' All!"
layout: "post"
diff: 普及-
pid: CF757A
tag: ['字符串', '概率论']
---

# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 输入格式

Input contains a single line containing a string $ s $ ( $ 1<=|s|<=10^{5} $ ) — the text on the front page of the newspaper without spaces and punctuation marks. $ |s| $ is the length of the string $ s $ .

The string $ s $ contains lowercase and uppercase English letters, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757A/5a3118f39129b2a74b924e2ddab1fc42162a4073.png).

## 输出格式

Output a single integer, the answer to the problem.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur

```

### 输出

```
1

```

## 样例 #2

### 输入

```
F

```

### 输出

```
0

```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb

```

### 输出

```
2

```



---

---
title: "Mike and palindrome"
layout: "post"
diff: 普及-
pid: CF798A
tag: ['模拟', '字符串', '概率论']
---

# Mike and palindrome

## 题目描述

麦克有一个只有小写英文字母的字符串 _s_ 。他想通过改变一个字符 的方式来让整个字符串成为回文字符串。

回文字符串是一个正着读和反着读都一样的字符串。比如说"z"， "aaa"，"aba"， "abccba"是回文字符串，而"codeforces"， "reality"和"ab"不是回文字符串。

## 输入格式

一行，包括一个字符串 _s_ (1<=|s|<=15)。

## 输出格式

如果麦克能通过只改变一个字符就使整个字符串成回文字符串的话就输出"YES"(不包括双引号)，不然的话就输出"NO"(同样不包括双引号)

感谢@deadpool123  提供的翻译

## 样例 #1

### 输入

```
abccaa

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abbcca

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
abcda

```

### 输出

```
YES

```



---

---
title: "3-palindrome"
layout: "post"
diff: 普及-
pid: CF805B
tag: ['字符串', '构造']
---

# 3-palindrome

## 题目描述

题意
给定n，求长度为n的以'a','b'或'c'构成的字符串，使得其中不存在长为3的回文子串（如"abc","abca"均符合，但"aba"不符），并使'c'的个数尽可能少

## 输入格式

第一行输入一个整数n（1<=n<=2*10^5）为字符串长度

## 输出格式

输出一个满足要求的字符串，若有多个任选一个输出
翻译提供者：mxy1

## 样例 #1

### 输入

```
2

```

### 输出

```
aa

```

## 样例 #2

### 输入

```
3

```

### 输出

```
bba

```



---

---
title: "Karen and Morning"
layout: "post"
diff: 普及-
pid: CF816A
tag: ['模拟', '字符串']
---

# Karen and Morning

## 题目描述

可怜已经准备好迎接在学校的新的一天。

现在是hh:mm，一个被以24小时制给与的时间。正如你所知道的，可怜喜欢回文，并且她相信如果在她醒来时的时间是回文的话会给她带来好运。

当她醒来时时间是回文的话，她最少应当睡多长时间？

记住，一个回文数是一个从前读和从后读相同的字符串。例如，05:39是不是回文数，因为05:39倒着读是93:50。另一方面，05:50是回文，因为05:50倒着读是05:50。

## 输入格式

仅有一行，包含一个格式为hh:mm的字符串（$00\leq hh\leq23,00\leq mm\leq59$ ）。

## 输出格式

仅输出一行一个整数，表示要使她醒来时的时间是回文，她所睡的最少时间。

## 说明/提示

在第一个样例中，可怜最少应睡的时间为$11$ ，这样她可以在05:50时醒来，这是一个回文时间。

在第二个样例中，可怜可以立刻起来，当前时间13:31就是一个回文。

在第三个样例中，可怜最少应睡的时间为$1$ 分钟。她可以在00:00醒来，这是一个回文时间。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
05:39

```

### 输出

```
11

```

## 样例 #2

### 输入

```
13:31

```

### 输出

```
0

```

## 样例 #3

### 输入

```
23:59

```

### 输出

```
1

```



---

---
title: "The number on the board"
layout: "post"
diff: 普及-
pid: CF835B
tag: ['字符串', '贪心', '排序']
---

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 输入格式

The first line contains integer $ k $ ( $ 1<=k<=10^{9} $ ).

The second line contains integer $ n $ ( $ 1<=n&lt;10^{100000} $ ).

There are no leading zeros in $ n $ . It's guaranteed that this situation is possible.

## 输出格式

Print the minimum number of digits in which the initial number and $ n $ can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
99

```

### 输出

```
0

```



---

---
title: "Train and Peter"
layout: "post"
diff: 普及-
pid: CF8A
tag: ['模拟', '字符串']
---

# Train and Peter

## 题目描述

Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

## 输入格式

输入共有三行。第一行包括一个连续的，不为空且只有小写字母的字符串 $s_0$，表示从 A 到 B 依次每个站的彩旗的颜色（A 站和 B 站没有彩旗）。列车从 B 到 A 也会经过同样的车站——以相反的顺序而已。

第二行和第三行分别为 Peter 两次看到的序列 $s_1$ 和 $s_2$。两个序列都包括连续的小写字母且不为空。

## 输出格式

一行，输出以下四种单词之一（不包括引号）：

`forward`：Peter 只可能在从 A 到 B 的旅途中看到这样的序列。

`backward`：Peter 只可能在从 B 到 A 的旅途中看到这样的序列。

`both`：Peter 既可能在从 A 到 B 的旅途中看到，也可能在从 B 到 A 的旅途中看到这样的序列。

`fantasy`：Peter 不可能看到这样的序列。

## 说明/提示

列车一直都在移动，所以一面同样的旗子不可能被看到两次。

## 样例 #1

### 输入

```
atob
a
b

```

### 输出

```
forward

```

## 样例 #2

### 输入

```
aaacaaa
aca
aa

```

### 输出

```
both

```



---

---
title: "Word Correction"
layout: "post"
diff: 普及-
pid: CF938A
tag: ['字符串', '枚举']
---

# Word Correction

## 题目背景

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

## 题目描述

Victor tries to write his own text editor, with word correction included. However, the rules of word correction are really strange.

Victor thinks that if a word contains two consecutive vowels, then it's kinda weird and it needs to be replaced. So the word corrector works in such a way: as long as there are two consecutive vowels in the word, it deletes the first vowel in a word such that there is another vowel right before it. If there are no two consecutive vowels in the word, it is considered to be correct.

You are given a word $ s $ . Can you predict what will it become after correction?

In this problem letters a, e, i, o, u and y are considered to be vowels.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the number of letters in word $ s $ before the correction.

The second line contains a string $ s $ consisting of exactly $ n $ lowercase Latin letters — the word before the correction.

## 输出格式

Output the word $ s $ after the correction.

## 说明/提示

Explanations of the examples:

1. There is only one replace: weird ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) werd;
2. No replace needed since there are no two consecutive vowels;
3. aaeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) a.

## 样例 #1

### 输入

```
5
weird

```

### 输出

```
werd

```

## 样例 #2

### 输入

```
4
word

```

### 输出

```
word

```

## 样例 #3

### 输入

```
5
aaeaa

```

### 输出

```
a

```



---

---
title: "String Typing"
layout: "post"
diff: 普及-
pid: CF954B
tag: ['字符串']
---

# String Typing

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. You have to type this string using your keyboard.

Initially, you have an empty string. Until you type the whole string, you may perform the following operation:

- add a character to the end of the string.

Besides, at most once you may perform one additional operation: copy the string and append it to itself.

For example, if you have to type string abcabca, you can type it in $ 7 $ operations if you type all the characters one by one. However, you can type it in $ 5 $ operations if you type the string abc first and then copy it and type the last character.

If you have to type string aaaaaaaaa, the best option is to type $ 4 $ characters one by one, then copy the string, and then type the remaining character.

Print the minimum number of operations you need to type the given string.

## 输入格式

The first line of the input containing only one integer number $ n $ ( $ 1<=n<=100 $ ) — the length of the string you have to type. The second line containing the string $ s $ consisting of $ n $ lowercase Latin letters.

## 输出格式

Print one integer number — the minimum number of operations you need to type the given string.

## 说明/提示

The first test described in the problem statement.

In the second test you can only type all the characters one by one.

## 样例 #1

### 输入

```
7
abcabca

```

### 输出

```
5

```

## 样例 #2

### 输入

```
8
abcdefgh

```

### 输出

```
8

```



---

---
title: "Two-gram"
layout: "post"
diff: 普及-
pid: CF977B
tag: ['字符串', '枚举']
---

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 输入格式

The first line of the input contains integer number $ n $ ( $ 2 \le n \le 100 $ ) — the length of string $ s $ . The second line of the input contains the string $ s $ consisting of $ n $ capital Latin letters.

## 输出格式

Print the only line containing exactly two capital Latin letters — any two-gram contained in the given string $ s $ as a substring (i.e. two consecutive characters of the string) maximal number of times.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA

```

### 输出

```
AB

```

## 样例 #2

### 输入

```
5
ZZZAA

```

### 输出

```
ZZ

```



---

---
title: "Reversing Encryption"
layout: "post"
diff: 普及-
pid: CF999B
tag: ['字符串']
---

# Reversing Encryption

## 题目描述

A string $ s $ of length $ n $ can be encrypted by the following algorithm:

- iterate over all divisors of $ n $ in decreasing order (i.e. from $ n $ to $ 1 $ ),
- for each divisor $ d $ , reverse the substring $ s[1 \dots d] $ (i.e. the substring which starts at position $ 1 $ and ends at position $ d $ ).

For example, the above algorithm applied to the string $ s $ ="codeforces" leads to the following changes: "codeforces" $ \to $ "secrofedoc" $ \to $ "orcesfedoc" $ \to $ "rocesfedoc" $ \to $ "rocesfedoc" (obviously, the last reverse operation doesn't change the string because $ d=1 $ ).

You are given the encrypted string $ t $ . Your task is to decrypt this string, i.e., to find a string $ s $ such that the above algorithm results in string $ t $ . It can be proven that this string $ s $ always exists and is unique.

## 输入格式

The first line of input consists of a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the string $ t $ . The second line of input consists of the string $ t $ . The length of $ t $ is $ n $ , and it consists only of lowercase Latin letters.

## 输出格式

Print a string $ s $ such that the above algorithm results in $ t $ .

## 说明/提示

The first example is described in the problem statement.

## 样例 #1

### 输入

```
10
rocesfedoc

```

### 输出

```
codeforces

```

## 样例 #2

### 输入

```
16
plmaetwoxesisiht

```

### 输出

```
thisisexampletwo

```

## 样例 #3

### 输入

```
1
z

```

### 输出

```
z

```



---

