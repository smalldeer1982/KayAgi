---
title: "Polycarp and Div 3"
layout: "post"
diff: 普及/提高-
pid: CF1005D
tag: ['字符串', '贪心', '前缀和']
---

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 输入格式

The first line of the input contains a positive integer $ s $ . The number of digits of the number $ s $ is between $ 1 $ and $ 2\cdot10^5 $ , inclusive. The first (leftmost) digit is not equal to 0.

## 输出格式

Print the maximum number of numbers divisible by $ 3 $ that Polycarp can get by making vertical cuts in the given number $ s $ .

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1000000000000000000000000000000000

```

### 输出

```
33

```

## 样例 #4

### 输入

```
201920181

```

### 输出

```
4

```



---

---
title: "Minimum Ternary String"
layout: "post"
diff: 普及/提高-
pid: CF1009B
tag: ['字符串', '贪心', '概率论']
---

# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 输入格式

字符串  $S$

## 输出格式

转化后字典序最小的字符串

Translated by @ZCDHJ

## 样例 #1

### 输入

```
100210

```

### 输出

```
001120

```

## 样例 #2

### 输入

```
11222121

```

### 输出

```
11112222

```

## 样例 #3

### 输入

```
20

```

### 输出

```
20

```



---

---
title: "Single Wildcard Pattern Matching"
layout: "post"
diff: 普及/提高-
pid: CF1023A
tag: ['模拟', '字符串']
---

# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 输入格式

第一行输入两个整数 $n,m$，分别表示 $s$ 和 $t$ 的长度。

第二行输入字符串 $s$，保证 $s$ 中只含有小写字母和不多于一个的 `*`。

第三行输入字符串 $t$，保证 $t$ 中只含有小写字母。

## 输出格式

如果 $s$ 与 $t$ 是匹配的，那么输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1 1
v
k

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf

```

### 输出

```
NO

```



---

---
title: "Bracket Subsequence"
layout: "post"
diff: 普及/提高-
pid: CF1023C
tag: ['字符串', '贪心', '枚举']
---

# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le k \le n \le 2 \cdot 10^5 $ , both $ n $ and $ k $ are even) — the length of $ s $ and the length of the sequence you are asked to find.

The second line is a string $ s $ — regular bracket sequence of length $ n $ .

## 输出格式

Print a single string — a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())

```

### 输出

```
()()

```

## 样例 #2

### 输入

```
8 8
(()(()))

```

### 输出

```
(()(()))

```



---

---
title: "Plasticine zebra"
layout: "post"
diff: 普及/提高-
pid: CF1025C
tag: ['字符串']
---

# Plasticine zebra

## 题目描述

Is there anything better than going to the zoo after a tiresome week at work? No wonder Grisha feels the same while spending the entire weekend accompanied by pretty striped zebras.

Inspired by this adventure and an accidentally found plasticine pack (represented as a sequence of black and white stripes), Grisha now wants to select several consequent (contiguous) pieces of alternating colors to create a zebra. Let's call the number of selected pieces the length of the zebra.

Before assembling the zebra Grisha can make the following operation $ 0 $ or more times. He splits the sequence in some place into two parts, then reverses each of them and sticks them together again. For example, if Grisha has pieces in the order "bwbbw" (here 'b' denotes a black strip, and 'w' denotes a white strip), then he can split the sequence as bw|bbw (here the vertical bar represents the cut), reverse both parts and obtain "wbwbb".

Determine the maximum possible length of the zebra that Grisha can produce.

## 输入格式

The only line contains a string $ s $ ( $ 1 \le |s| \le 10^5 $ , where $ |s| $ denotes the length of the string $ s $ ) comprised of lowercase English letters 'b' and 'w' only, where 'w' denotes a white piece and 'b' denotes a black piece.

## 输出格式

Print a single integer — the maximum possible zebra length.

## 说明/提示

In the first example one of the possible sequence of operations is bwwwbww|bw $ \to $ w|wbwwwbwb $ \to $ wbwbwwwbw, that gives the answer equal to $ 5 $ .

In the second example no operation can increase the answer.

## 样例 #1

### 输入

```
bwwwbwwbw

```

### 输出

```
5

```

## 样例 #2

### 输入

```
bwwbwwb

```

### 输出

```
3

```



---

---
title: "Smallest Word"
layout: "post"
diff: 普及/提高-
pid: CF1043C
tag: ['模拟', '字符串']
---

# Smallest Word

## 题目描述

IA has so many colorful magnets on her fridge! Exactly one letter is written on each magnet, 'a' or 'b'. She loves to play with them, placing all magnets in a row. However, the girl is quickly bored and usually thinks how to make her entertainment more interesting.

Today, when IA looked at the fridge, she noticed that the word formed by magnets is really messy. "It would look much better when I'll swap some of them!" — thought the girl — "but how to do it?". After a while, she got an idea. IA will look at all prefixes with lengths from $ 1 $ to the length of the word and for each prefix she will either reverse this prefix or leave it as it is. She will consider the prefixes in the fixed order: from the shortest to the largest. She wants to get the lexicographically smallest possible word after she considers all prefixes. Can you help her, telling which prefixes should be chosen for reversing?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first and the only line contains a string $ s $ ( $ 1 \le |s| \le 1000 $ ), describing the initial string formed by magnets. The string $ s $ consists only of characters 'a' and 'b'.

## 输出格式

Output exactly $ |s| $ integers. If IA should reverse the $ i $ -th prefix (that is, the substring from $ 1 $ to $ i $ ), the $ i $ -th integer should be equal to $ 1 $ , and it should be equal to $ 0 $ otherwise.

If there are multiple possible sequences leading to the optimal answer, print any of them.

## 说明/提示

In the first example, IA can reverse the second and the third prefix and get a string "abbb". She cannot get better result, since it is also lexicographically smallest string obtainable by permuting characters of the initial string.

In the second example, she can reverse any subset of prefixes — all letters are 'a'.

## 样例 #1

### 输入

```
bbab

```

### 输出

```
0 1 1 0

```

## 样例 #2

### 输入

```
aaaaa

```

### 输出

```
1 0 0 0 1

```



---

---
title: "BerOS File Suggestion"
layout: "post"
diff: 普及/提高-
pid: CF1070H
tag: ['字符串']
---

# BerOS File Suggestion

## 题目描述

Polycarp is working on a new operating system called BerOS. He asks you to help with implementation of a file suggestion feature.

There are $ n $ files on hard drive and their names are $ f_1, f_2, \dots, f_n $ . Any file name contains between $ 1 $ and $ 8 $ characters, inclusive. All file names are unique.

The file suggestion feature handles queries, each represented by a string $ s $ . For each query $ s $ it should count number of files containing $ s $ as a substring (i.e. some continuous segment of characters in a file name equals $ s $ ) and suggest any such file name.

For example, if file names are "read.me", "hosts", "ops", and "beros.18", and the query is "os", the number of matched files is $ 2 $ (two file names contain "os" as a substring) and suggested file name can be either "hosts" or "beros.18".

## 输入格式

The first line of the input contains integer $ n $ ( $ 1 \le n \le 10000 $ ) — the total number of files.

The following $ n $ lines contain file names, one per line. The $ i $ -th line contains $ f_i $ — the name of the $ i $ -th file. Each file name contains between $ 1 $ and $ 8 $ characters, inclusive. File names contain only lowercase Latin letters, digits and dot characters ('.'). Any sequence of valid characters can be a file name (for example, in BerOS ".", ".." and "..." are valid file names). All file names are unique.

The following line contains integer $ q $ ( $ 1 \le q \le 50000 $ ) — the total number of queries.

The following $ q $ lines contain queries $ s_1, s_2, \dots, s_q $ , one per line. Each $ s_j $ has length between $ 1 $ and $ 8 $ characters, inclusive. It contains only lowercase Latin letters, digits and dot characters ('.').

## 输出格式

Print $ q $ lines, one per query. The $ j $ -th line should contain the response on the $ j $ -th query — two values $ c_j $ and $ t_j $ , where

- $ c_j $ is the number of matched files for the $ j $ -th query,
- $ t_j $ is the name of any file matched by the $ j $ -th query. If there is no such file, print a single character '-' instead. If there are multiple matched files, print any.

## 样例 #1

### 输入

```
4
test
contests
test.
.test
6
ts
.
st.
.test
contes.
st

```

### 输出

```
1 contests
2 .test
1 test.
1 .test
0 -
4 test.

```



---

---
title: "Prime Permutation"
layout: "post"
diff: 普及/提高-
pid: CF123A
tag: ['字符串', '素数判断,质数,筛法', '构造']
---

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 输入格式

The only line contains the initial string $ s $ , consisting of small Latin letters ( $ 1<=|s|<=1000 $ ).

## 输出格式

If it is possible to rearrange the characters in the string so that the above-mentioned conditions were fulfilled, then print in the first line "YES" (without the quotes) and print on the second line one of the possible resulting strings. If such permutation is impossible to perform, then print the single string "NO".

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc

```

### 输出

```
YES
abc

```

## 样例 #2

### 输入

```
abcd

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
xxxyxxx

```

### 输出

```
YES
xxxxxxy

```



---

---
title: "STL"
layout: "post"
diff: 普及/提高-
pid: CF190C
tag: ['字符串', '递归']
---

# STL

## 题目描述

Vasya used to be an accountant before the war began and he is one of the few who knows how to operate a computer, so he was assigned as the programmer.

We all know that programs often store sets of integers. For example, if we have a problem about a weighted directed graph, its edge can be represented by three integers: the number of the starting vertex, the number of the final vertex and the edge's weight. So, as Vasya was trying to represent characteristics of a recently invented robot in his program, he faced the following problem.

Vasya is not a programmer, so he asked his friend Gena, what the convenient way to store $ n $ integers is. Gena used to code in language X-- and so he can use only the types that occur in this language. Let's define, what a "type" is in language X--:

- First, a type is a string "int".
- Second, a type is a string that starts with "pair", then followed by angle brackets listing exactly two comma-separated other types of language X--. This record contains no spaces.
- No other strings can be regarded as types.

More formally: type := int | pair<type,type>. For example, Gena uses the following type for graph edges: pair<int,pair<int,int>>.

Gena was pleased to help Vasya, he dictated to Vasya a type of language X--, that stores $ n $ integers. Unfortunately, Gena was in a hurry, so he omitted the punctuation. Now Gena has already left and Vasya can't find the correct punctuation, resulting in a type of language X--, however hard he tries.

Help Vasya and add the punctuation marks so as to receive the valid type of language X--. Otherwise say that the task is impossible to perform.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ , showing how many numbers the type dictated by Gena contains.

The second line contains space-separated words, said by Gena. Each of them is either "pair" or "int" (without the quotes).

It is guaranteed that the total number of words does not exceed $ 10^{5} $ and that among all the words that Gena said, there are exactly $ n $ words "int".

## 输出格式

If it is possible to add the punctuation marks so as to get a correct type of language X-- as a result, print a single line that represents the resulting type. Otherwise, print "Error occurred" (without the quotes). Inside the record of a type should not be any extra spaces and other characters.

It is guaranteed that if such type exists, then it is unique.

Note that you should print the type dictated by Gena (if such type exists) and not any type that can contain $ n $ values.

## 样例 #1

### 输入

```
3
pair pair int int int

```

### 输出

```
pair<pair<int,int>,int>
```

## 样例 #2

### 输入

```
1
pair int

```

### 输出

```
Error occurred
```



---

---
title: "Message Transmission Error (hard version)"
layout: "post"
diff: 普及/提高-
pid: CF2010C2
tag: ['字符串', '哈希 hashing', 'KMP 算法']
---

# Message Transmission Error (hard version)

## 题目描述

这是一个难度较高的问题。它与简单版的区别仅在于约束条件不同。

在伯兰州立大学，服务器之间的本地网络并非总是运行无误。当连续传输两条相同的信息时，可能会发生错误，导致两条信息合并为一条。在这种合并中，第一条信息的结尾与第二条信息的开头重合。当然，合并只能发生在相同字符处。合并的长度必须是一个小于信息文本长度的正数。

例如，当连续传送两条信息```abrakadabra```时，可能会出现所述类型的错误、导致出现类似```abrakadabrakadabra```或```abrakadabrakadabra```的信息(前者在一个字符处发生合并，后者在四个字符处发生合并)。

给定接收到的报文 ```t``` ，判断这是否可能是本地网络运行中出现所述类型错误的结果，如果是，请确定可能的值 ```s``` 。

两个报文完全重叠的情况不应视为错误。例如，如果收到的报文是```abcd```，则应认为其中没有错误。同样，简单地在一条信息后附加另一条信息也不是错误的标志。例如，如果收到的信息是 ```abcabc```，也应认为其中没有错误。

## 输入格式

一个非空字符串 ```t``` ，该字符串由拉丁字母的小写字母组成。字符串 ```t``` 的长度不超过 ```4×10⁵``` 个字符。

## 输出格式

如果信息 ```t``` 不能包含错误，则在单行输出中输出 ```NO``` (不带引号)。
否则，在第一行输出```YES```(不带引号)，在下一行输出字符串``` s ```(可能导致错误的信息)。如果有多个可能的答案，可以输出任意一个。

## 样例 #1

### 输入

```
abrakadabrabrakadabra
```

### 输出

```
YES
abrakadabra
```

## 样例 #2

### 输入

```
acacacaca
```

### 输出

```
YES
acacaca
```

## 样例 #3

### 输入

```
abcabc
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
abababab
```

### 输出

```
YES
ababab
```

## 样例 #5

### 输入

```
tatbt
```

### 输出

```
NO
```



---

---
title: "Saraga"
layout: "post"
diff: 普及/提高-
pid: CF2045C
tag: ['字符串']
---

# Saraga

## 题目描述

在印尼语中，"sarana olahraga" 是体育设施的意思，缩写为 "saraga"。这个缩写可以通过两种不同的方式组合而成：一种是取 "sarana" 的前缀 "sara" 和 "olahraga" 的后缀 "ga"；另一种是取 "sarana" 的前缀 "sa" 和 "olahraga" 的后缀 "raga"。

如果一个字符串 $S$ 和 $T$ 的缩写有至少两种不同的分割方法，且这些分割能得到一个字符串，使得第一个部分是 $S$ 的前缀，第二个部分是 $T$ 的后缀，我们就称这个缩写是有趣的。

现在，给定两个字符串 $S$ 和 $T$，你需要找出一个最短的有趣缩写，或者判断是否无法构造这样的缩写。

## 输入格式

第一行是一个字符串 $S$（长度满足 $1 \leq |S| \leq 200\,000$）。

第二行是一个字符串 $T$（长度满足 $1 \leq |T| \leq 200\,000$）。

两个字符串仅包含小写字母。

## 输出格式

如果无法构造有趣的缩写，请输出 -1。

否则，请输出一个最短的有趣缩写。如果存在多个最短解，输出任意一个即可。

## 说明/提示

样例 1 的解释：

字符串 "saga" 可以分割为 "s" 和 "aga"，或者 "sa" 和 "ga"。因此，"saraga" 和 "saga" 都是有趣的缩写，但 "saga" 更短。

样例 2 的解释：

缩写 "belhijau" 也是一个最短的有趣缩写，所以这个解也是有效的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
sarana
olahraga
```

### 输出

```
saga
```

## 样例 #2

### 输入

```
berhiber
wortelhijau
```

### 输出

```
berhijau
```

## 样例 #3

### 输入

```
icpc
icpc
```

### 输出

```
icpc
```

## 样例 #4

### 输入

```
icpc
jakarta
```

### 输出

```
-1
```



---

---
title: "Dubstep"
layout: "post"
diff: 普及/提高-
pid: CF208A
tag: ['模拟', '字符串', '枚举']
---

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 输入格式

输入包括一个非空字符串SSS，其中SSS仅由大写字母组成并且的长度不超过200
保证原来的字符串不含有"WUB"并且至少有一个单词

## 输出格式

输出转变前的字符串，每个单词用空格分隔

## 样例 #1

### 输入

```
WUBWUBABCWUB

```

### 输出

```
ABC 
```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB

```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND 
```



---

---
title: "k-String"
layout: "post"
diff: 普及/提高-
pid: CF219A
tag: ['字符串', '构造']
---

# k-String

## 题目描述

- **题面翻译如下**

如果一个字符串可以被划分为 $k$ 个相同的子串，则称这个字符串为 $k$-string。例如，字符串“aabaabaabaab”同时是 $1$-string, $2$-string和 $4$-string，但它不是 $3$-string, $5$-string 或 $6$-string 等。显然，任何字符串都是 $1$-string。

给你一个由小写英文字母组成的字符串 $s$ 和一个正整数 $k$。你需要将字符串 $s$ 重新排列成一个 $k$-string。

## 输入格式

第一行，一个正整数 $ k $ ($ 1\le k \le 1000 $)。  
第二行，一个由小写英文字母组成的字符串 $ s $，（$ 1<=|s|<=1000 $， $ |s| $ 表示字符串 $s$ 的长度）。

## 输出格式

- 共一行，一个经过重新排列后的字符串。如果存在多种排列方案，输出其中任意一种即可。  
- 如果不存在解决方案，则输出“-1”（不含双引号）。

## 样例 #1

### 输入

```
2
aazz

```

### 输出

```
azaz

```

## 样例 #2

### 输入

```
3
abcabcabz

```

### 输出

```
-1

```



---

---
title: "Winner"
layout: "post"
diff: 普及/提高-
pid: CF2A
tag: ['模拟', '字符串', '概率论', '栈']
---

# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 输入格式

第一行包含整数 $n$，表示是游戏进行的的回合数。

第 $2 \sim n + 1$ 行，按照时间顺序输入 `名称和得分` 行的信息，其中名称是长度不大于 $32$ 的小写字母组成的字符串，分数的绝对值不大于 $1000$。

## 输出格式

输出获胜者的名称。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2

```

### 输出

```
andrew

```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5

```

### 输出

```
andrew

```



---

---
title: "Sysadmin Bob"
layout: "post"
diff: 普及/提高-
pid: CF31B
tag: ['模拟', '字符串']
---

# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 输入格式

The first line contains the list of addresses without separators. The length of this string is between $ 1 $ and $ 200 $ , inclusive. The string consists only from small Latin letters and characters «@».

## 输出格式

If there is no list of the valid (according to the Berland rules) email addresses such that after removing all commas it coincides with the given string, output No solution. In the other case, output the list. The same address can be written in this list more than once. If there are several solutions, output any of them.

## 样例 #1

### 输入

```
a@aa@a

```

### 输出

```
a@a,a@a

```

## 样例 #2

### 输入

```
a@a@a

```

### 输出

```
No solution

```

## 样例 #3

### 输入

```
@aa@a

```

### 输出

```
No solution

```



---

---
title: "Chewbaсca and Number"
layout: "post"
diff: 普及/提高-
pid: CF514A
tag: ['模拟', '字符串']
---

# Chewbaсca and Number

## 题目描述

Luke Skywalker gave Chewbacca an integer number $ x $ . Chewbacca isn't good at numbers but he loves inverting digits in them. Inverting digit $ t $ means replacing it with digit $ 9-t $ .

Help Chewbacca to transform the initial number $ x $ to the minimum possible positive number by inverting some (possibly, zero) digits. The decimal representation of the final number shouldn't start with a zero.

## 输入格式

The first line contains a single integer $ x $ $ (1<=x<=10^{18}) $ — the number that Luke Skywalker gave to Chewbacca.

## 输出格式

Print the minimum possible positive number that Chewbacca can obtain after inverting some digits. The number shouldn't contain leading zeroes.

## 样例 #1

### 输入

```
27

```

### 输出

```
22

```

## 样例 #2

### 输入

```
4545

```

### 输出

```
4444

```



---

---
title: "Vitaly and Strings"
layout: "post"
diff: 普及/提高-
pid: CF518A
tag: ['字符串']
---

# Vitaly and Strings

## 题目描述

Vitaly is a diligent student who never missed a lesson in his five years of studying in the university. He always does his homework on time and passes his exams in time.

During the last lesson the teacher has provided two strings $ s $ and $ t $ to Vitaly. The strings have the same length, they consist of lowercase English letters, string $ s $ is lexicographically smaller than string $ t $ . Vitaly wondered if there is such string that is lexicographically larger than string $ s $ and at the same is lexicographically smaller than string $ t $ . This string should also consist of lowercase English letters and have the length equal to the lengths of strings $ s $ and $ t $ .

Let's help Vitaly solve this easy problem!

## 输入格式

The first line contains string $ s $ ( $ 1<=|s|<=100 $ ), consisting of lowercase English letters. Here, $ |s| $ denotes the length of the string.

The second line contains string $ t $ ( $ |t|=|s| $ ), consisting of lowercase English letters.

It is guaranteed that the lengths of strings $ s $ and $ t $ are the same and string $ s $ is lexicographically less than string $ t $ .

## 输出格式

If the string that meets the given requirements doesn't exist, print a single string "No such string" (without the quotes).

If such string exists, print it. If there are multiple valid strings, you may print any of them.

## 说明/提示

String $ s=s_{1}s_{2}...\ s_{n} $ is said to be lexicographically smaller than $ t=t_{1}t_{2}...\ t_{n} $ , if there exists such $ i $ , that $ s_{1}=t_{1},s_{2}=t_{2},...\ s_{i-1}=t_{i-1},s_{i}<t_{i} $ .

## 样例 #1

### 输入

```
a
c

```

### 输出

```
b

```

## 样例 #2

### 输入

```
aaa
zzz

```

### 输出

```
kkk

```

## 样例 #3

### 输入

```
abcdefg
abcdefh

```

### 输出

```
No such string

```



---

---
title: "Reposts"
layout: "post"
diff: 普及/提高-
pid: CF522A
tag: ['字符串']
---

# Reposts

## 题目描述

One day Polycarp published a funny picture in a social network making a poll about the color of his handle. Many of his friends started reposting Polycarp's joke to their news feed. Some of them reposted the reposts and so on.

These events are given as a sequence of strings "name1 reposted name2", where name1 is the name of the person who reposted the joke, and name2 is the name of the person from whose news feed the joke was reposted. It is guaranteed that for each string "name1 reposted name2" user "name1" didn't have the joke in his feed yet, and "name2" already had it in his feed by the moment of repost. Polycarp was registered as "Polycarp" and initially the joke was only in his feed.

Polycarp measures the popularity of the joke as the length of the largest repost chain. Print the popularity of Polycarp's joke.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=200 $ ) — the number of reposts. Next follow the reposts in the order they were made. Each of them is written on a single line and looks as "name1 reposted name2". All the names in the input consist of lowercase or uppercase English letters and/or digits and have lengths from 2 to 24 characters, inclusive.

We know that the user names are case-insensitive, that is, two names that only differ in the letter case correspond to the same social network user.

## 输出格式

Print a single integer — the maximum length of a repost chain.

## 样例 #1

### 输入

```
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya

```

### 输出

```
6

```

## 样例 #2

### 输入

```
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1
SoMeStRaNgEgUe reposted PoLyCaRp

```

### 输出

```
2

```



---

---
title: "Rotate, Flip and Zoom"
layout: "post"
diff: 普及/提高-
pid: CF523A
tag: ['模拟', '字符串']
---

# Rotate, Flip and Zoom

## 题目描述

Polycarp is writing the prototype of a graphic editor. He has already made up his mind that the basic image transformations in his editor will be: rotate the image 90 degrees clockwise, flip the image horizontally (symmetry relative to the vertical line, that is, the right part of the image moves to the left, and vice versa) and zooming on the image. He is sure that that there is a large number of transformations that can be expressed through these three.

He has recently stopped implementing all three transformations for monochrome images. To test this feature, he asked you to write a code that will consecutively perform three actions with a monochrome image: first it will rotate the image 90 degrees clockwise, then it will flip the image horizontally and finally, it will zoom in twice on the image (that is, it will double all the linear sizes).

Implement this feature to help Polycarp test his editor.

## 输入格式

The first line contains two integers, $ w $ and $ h $ ( $ 1<=w,h<=100 $ ) — the width and height of an image in pixels. The picture is given in $ h $ lines, each line contains $ w $ characters — each character encodes the color of the corresponding pixel of the image. The line consists only of characters "." and "\*", as the image is monochrome.

## 输出格式

Print $ 2w $ lines, each containing $ 2h $ characters — the result of consecutive implementing of the three transformations, described above.

## 样例 #1

### 输入

```
3 2
.*.
.*.

```

### 输出

```
....
....
****
****
....
....

```

## 样例 #2

### 输入

```
9 20
**.......
****.....
******...
*******..
..******.
....****.
......***
*.....***
*********
*********
*********
*********
....**...
...****..
..******.
.********
****..***
***...***
**.....**
*.......*

```

### 输出

```
********......**********........********
********......**********........********
********........********......********..
********........********......********..
..********......********....********....
..********......********....********....
..********......********..********......
..********......********..********......
....********....****************........
....********....****************........
....********....****************........
....********....****************........
......******************..**********....
......******************..**********....
........****************....**********..
........****************....**********..
............************......**********
............************......**********

```



---

---
title: "Pasha and String"
layout: "post"
diff: 普及/提高-
pid: CF525B
tag: ['字符串', '线段树']
---

# Pasha and String

## 题目描述

Pasha got a very beautiful string $ s $ for his birthday, the string consists of lowercase Latin letters. The letters in the string are numbered from 1 to $ |s| $ from left to right, where $ |s| $ is the length of the given string.

Pasha didn't like his present very much so he decided to change it. After his birthday Pasha spent $ m $ days performing the following transformations on his string — each day he chose integer $ a_{i} $ and reversed a piece of string (a segment) from position $ a_{i} $ to position $ |s|-a_{i}+1 $ . It is guaranteed that $ 2·a_{i}<=|s| $ .

You face the following task: determine what Pasha's string will look like after $ m $ days.

## 输入格式

The first line of the input contains Pasha's string $ s $ of length from $ 2 $ to $ 2·10^{5} $ characters, consisting of lowercase Latin letters.

The second line contains a single integer $ m $ ( $ 1<=m<=10^{5} $ ) — the number of days when Pasha changed his string.

The third line contains $ m $ space-separated elements $ a_{i} $ ( $ 1<=a_{i} $ ; $ 2·a_{i}<=|s| $ ) — the position from which Pasha started transforming the string on the $ i $ -th day.

## 输出格式

In the first line of the output print what Pasha's string $ s $ will look like after $ m $ days.

## 样例 #1

### 输入

```
abcdef
1
2

```

### 输出

```
aedcbf

```

## 样例 #2

### 输入

```
vwxyz
2
2 2

```

### 输出

```
vwxyz

```

## 样例 #3

### 输入

```
abcdef
3
1 2 3

```

### 输出

```
fbdcea

```



---

---
title: "Longest Regular Bracket Sequence"
layout: "post"
diff: 普及/提高-
pid: CF5C
tag: ['字符串', '动态规划 DP', '栈']
---

# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 输入格式

The first line of the input file contains a non-empty string, consisting of «(» and «)» characters. Its length does not exceed $ 10^{6} $ .

## 输出格式

Print the length of the longest substring that is a regular bracket sequence, and the number of such substrings. If there are no such substrings, write the only line containing "0 1".

## 样例 #1

### 输入

```
)((())))(()())

```

### 输出

```
6 2

```

## 样例 #2

### 输入

```
))(

```

### 输出

```
0 1

```



---

---
title: "Dasha and friends"
layout: "post"
diff: 普及/提高-
pid: CF761B
tag: ['字符串', '枚举']
---

# Dasha and friends

## 题目描述

小A和小B参加障碍跑，跑道可能有多个，所有跑道是环形的，按逆时针方向跑，长度都是是L，都有n个障碍。 小A从起点A开始跑，沿途记录下经过的障碍物离开起点A的距离，如2,4,6；小B从起点B开始跑，沿途记录下经过的障碍物离开起点B的距离，如1,5,7。距离均为整数。 现在请你判断，小A和小B的使用的是否是同一个跑道。

## 输入格式

第一行，两个整数n和L (1 ≤ n ≤ 50, n ≤ L ≤ 100)，分别表示障碍物的数量和跑道的长度。 第二行，n个升序的整数，表示小A记录的障碍物离起点的距离，范围为0到L-1。 第三行，n个升序的整数，表示小B记录的障碍物离起点的距离，范围为0到L-1。

## 输出格式

输出一个字符串，“YES”表示跑道相同，“NO”表示跑道不同。

## 输入输出样例

### 输入 #1

```

3 8

2 4 6

1 5 7

```

### 输出 #1

```

YES

```

### 输入 #2

```

4 9

2 3 5 8

0 1 3 6

```

### 输出 #2

```

YES

```

### 输入 #3

```

2 4

1 3

1 2

```

### 输出 #3

```

NO

```

## 样例 #1

### 输入

```
3 8
2 4 6
1 5 7

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 9
2 3 5 8
0 1 3 6

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
2 4
1 3
1 2

```

### 输出

```
NO

```



---

---
title: "String Game"
layout: "post"
diff: 普及/提高-
pid: CF778A
tag: ['字符串', '排序']
---

# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 输入格式

The first and second lines of the input contain the words $ t $ and $ p $ , respectively. Words are composed of lowercase letters of the Latin alphabet ( $ 1<=|p|&lt;|t|<=200000 $ ). It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

Next line contains a permutation $ a_{1},a_{2},...,a_{|t|} $ of letter indices that specifies the order in which Nastya removes letters of $ t $ ( $ 1<=a_{i}<=|t| $ , all $ a_{i} $ are distinct).

## 输出格式

Print a single integer number, the maximum number of letters that Nastya can remove.

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2

```

### 输出

```
3
```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5

```

### 输出

```
4
```



---

---
title: "Mike and strings"
layout: "post"
diff: 普及/提高-
pid: CF798B
tag: ['模拟', '字符串']
---

# Mike and strings

## 题目描述

Mike有n个字符串s1,s2,……，sn，每个字符串均由小写字母构成。 每次移动你可以选择一个字符串si, 第1个字符移动最后，比如字符串 "coolmikecoolmike", 移动1次变成字符串 "oolmikecoolmikec"。

请计算至少需要移动多少次，可以使得n个字符串都变成相同。

## 输入格式

第一行，一个整数n(1≤n≤50)。 接下来n行，每行一个字符串，每个字符串的长度相当，且长度不超过50。

## 输出格式

输出最小移动次数，无解则输出-1.

## 样例 #1

### 输入

```
4
xzzwo
zwoxz
zzwox
xzzwo

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
molzv
lzvmo

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
kc
kc
kc

```

### 输出

```
0

```

## 样例 #4

### 输入

```
3
aa
aa
ab

```

### 输出

```
-1

```



---

---
title: "Position in Fraction"
layout: "post"
diff: 普及/提高-
pid: CF900B
tag: ['模拟', '字符串', '高精度']
---

# Position in Fraction

## 题目描述

给你三个整数 $a,b,c$，问 $\dfrac{a}{b}$ 的小数部分第几位是 $c$，如果无法找到，请输出 `-1`。

## 输入格式

共一行，三个整数 $a,b,c$。

## 输出格式

共一行，输出一个整数，表示 $c$ 的位置或 `-1`。

## 说明/提示

对于 $100\%$ 的数据：$1\le a<b\le 10^5,0\le c\le 9$。

## 样例 #1

### 输入

```
1 2 0

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 7

```

### 输出

```
-1
```



---

---
title: "Phone Numbers"
layout: "post"
diff: 普及/提高-
pid: CF940C
tag: ['字符串']
---

# Phone Numbers

## 题目描述

And where the are the phone numbers?

You are given a string $ s $ consisting of lowercase English letters and an integer $ k $ . Find the lexicographically smallest string $ t $ of length $ k $ , such that its set of letters is a subset of the set of letters of $ s $ and $ s $ is lexicographically smaller than $ t $ .

It's guaranteed that the answer exists.

Note that the set of letters is a set, not a multiset. For example, the set of letters of abadaba is $ {a,b,d} $ .

String $ p $ is lexicographically smaller than string $ q $ , if $ p $ is a prefix of $ q $ , is not equal to $ q $ or there exists $ i $ , such that $ p_{i}<q_{i} $ and for all $ j<i $ it is satisfied that $ p_{j}=q_{j} $ . For example, abc is lexicographically smaller than abcd , abd is lexicographically smaller than abec, afa is not lexicographically smaller than ab and a is not lexicographically smaller than a.

## 输入格式

The first line of input contains two space separated integers $ n $ and $ k $ ( $ 1<=n,k<=100000 $ ) — the length of $ s $ and the required length of $ t $ .

The second line of input contains the string $ s $ consisting of $ n $ lowercase English letters.

## 输出格式

Output the string $ t $ conforming to the requirements above.

It's guaranteed that the answer exists.

## 说明/提示

In the first example the list of strings $ t $ of length 3, such that the set of letters of $ t $ is a subset of letters of $ s $ is as follows: aaa, aab, aac, aba, abb, abc, aca, acb, $ ... $ . Among them, those are lexicographically greater than abc: aca, acb, $ ... $ . Out of those the lexicographically smallest is aca.

## 样例 #1

### 输入

```
3 3
abc

```

### 输出

```
aca

```

## 样例 #2

### 输入

```
3 2
abc

```

### 输出

```
ac

```

## 样例 #3

### 输入

```
3 3
ayy

```

### 输出

```
yaa

```

## 样例 #4

### 输入

```
2 3
ba

```

### 输出

```
baa

```



---

---
title: "Treasure Hunt"
layout: "post"
diff: 普及/提高-
pid: CF979B
tag: ['字符串']
---

# Treasure Hunt

## 题目描述

After the big birthday party, Katie still wanted Shiro to have some more fun. Later, she came up with a game called treasure hunt. Of course, she invited her best friends Kuro and Shiro to play with her.

The three friends are very smart so they passed all the challenges very quickly and finally reached the destination. But the treasure can only belong to one cat so they started to think of something which can determine who is worthy of the treasure. Instantly, Kuro came up with some ribbons.

A random colorful ribbon is given to each of the cats. Each color of the ribbon can be represented as an uppercase or lowercase Latin letter. Let's call a consecutive subsequence of colors that appears in the ribbon a subribbon. The beauty of a ribbon is defined as the maximum number of times one of its subribbon appears in the ribbon. The more the subribbon appears, the more beautiful is the ribbon. For example, the ribbon aaaaaaa has the beauty of $ 7 $ because its subribbon a appears $ 7 $ times, and the ribbon abcdabc has the beauty of $ 2 $ because its subribbon abc appears twice.

The rules are simple. The game will have $ n $ turns. Every turn, each of the cats must change strictly one color (at one position) in his/her ribbon to an arbitrary color which is different from the unchanged one. For example, a ribbon aaab can be changed into acab in one turn. The one having the most beautiful ribbon after $ n $ turns wins the treasure.

Could you find out who is going to be the winner if they all play optimally?

## 输入格式

The first line contains an integer $ n $ ( $ 0 \leq n \leq 10^{9} $ ) — the number of turns.

Next 3 lines contain 3 ribbons of Kuro, Shiro and Katie one per line, respectively. Each ribbon is a string which contains no more than $ 10^{5} $ uppercase and lowercase Latin letters and is not empty. It is guaranteed that the length of all ribbons are equal for the purpose of fairness. Note that uppercase and lowercase letters are considered different colors.

## 输出格式

Print the name of the winner ("Kuro", "Shiro" or "Katie"). If there are at least two cats that share the maximum beauty, print "Draw".

## 说明/提示

In the first example, after $ 3 $ turns, Kuro can change his ribbon into ooooo, which has the beauty of $ 5 $ , while reaching such beauty for Shiro and Katie is impossible (both Shiro and Katie can reach the beauty of at most $ 4 $ , for example by changing Shiro's ribbon into SSiSS and changing Katie's ribbon into Kaaaa). Therefore, the winner is Kuro.

In the fourth example, since the length of each of the string is $ 9 $ and the number of turn is $ 15 $ , everyone can change their ribbons in some way to reach the maximal beauty of $ 9 $ by changing their strings into zzzzzzzzz after 9 turns, and repeatedly change their strings into azzzzzzzz and then into zzzzzzzzz thrice. Therefore, the game ends in a draw.

## 样例 #1

### 输入

```
3
Kuroo
Shiro
Katie

```

### 输出

```
Kuro

```

## 样例 #2

### 输入

```
7
treasurehunt
threefriends
hiCodeforces

```

### 输出

```
Shiro

```

## 样例 #3

### 输入

```
1
abcabc
cbabac
ababca

```

### 输出

```
Katie

```

## 样例 #4

### 输入

```
15
foPaErcvJ
mZaxowpbt
mkuOlaHRE

```

### 输出

```
Draw

```



---

---
title: "Row"
layout: "post"
diff: 普及/提高-
pid: CF982A
tag: ['字符串']
---

# Row

## 题目描述

### 读入一个字符串，只含有$01$两种字符，合法则输出"$Yes$",否则输出"$No$"。
### 不合法情况  
$1$.一个为$0$的字符两旁没有$1$。   
$2$.一个为$1$的字符两旁还有$1$。

## 输入格式

共两行。第一行为一个正整数$n$，表示字符串的长度。第二行为一个字符串。

## 样例 #1

### 输入

```
3
101

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
4
1011

```

### 输出

```
No

```

## 样例 #3

### 输入

```
5
10001

```

### 输出

```
No

```



---

