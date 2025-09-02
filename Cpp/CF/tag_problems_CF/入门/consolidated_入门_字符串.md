---
title: "Nearly Lucky Number"
layout: "post"
diff: 入门
pid: CF110A
tag: ['字符串', '概率论', '位运算']
---

# Nearly Lucky Number

## 题目描述

### 题目要求
如果一个数仅包含4和7，那么它就是一个"幸运数字"。
如果一个数**本身不是**幸运数，但是它所含有的数字4和7的个数之和为一个"幸运数字"，那么它就是一个"类幸运数字"。
给您一个数，请编程判断它是不是"类幸运数字"。

## 输入格式

一行一个整数N(N在64位整数(long long / int64)范围内)。

## 输出格式

一行一个字符串，如果N是"类幸运数字"则输出"YES"，否则输出"NO"。

感谢@PC_DOS 提供翻译

## 样例 #1

### 输入

```
40047

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
7747774

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1000000000000000000

```

### 输出

```
NO

```



---

---
title: "Petya and Strings"
layout: "post"
diff: 入门
pid: CF112A
tag: ['字符串']
---

# Petya and Strings

## 题目描述

输入两个字符串，大小写无关紧要，比较它们的大小。

## 输入格式

两个字符串（保证长度相等）

## 输出格式

如果第一个字符串小于第二个字符串，则输出“-1”。如果第二个字符串小于第一个字符串，则输出“1”。如果字符串相同，则打印“0”。请注意，比较字符串时不考虑字母的大小写。

## 样例 #1

### 输入

```
aaaa
aaaA

```

### 输出

```
0

```

## 样例 #2

### 输入

```
abs
Abz

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
abcdefg
AbCdEfF

```

### 输出

```
1

```



---

---
title: "String Task"
layout: "post"
diff: 入门
pid: CF118A
tag: ['模拟', '字符串', '枚举']
---

# String Task

## 题目描述

Petya started to attend programming lessons. On the first lesson his task was to write a simple program. The program was supposed to do the following: in the given string, consisting if uppercase and lowercase Latin letters, it:

- deletes all the vowels,
- inserts a character "." before each consonant,
- replaces all uppercase consonants with corresponding lowercase ones.

Vowels are letters "A", "O", "Y", "E", "U", "I", and the rest are consonants. The program's input is exactly one string, it should return the output as a single string, resulting after the program's processing the initial string.

Help Petya cope with this easy task.

## 输入格式

The first line represents input string of Petya's program. This string only consists of uppercase and lowercase Latin letters and its length is from $ 1 $ to $ 100 $ , inclusive.

## 输出格式

Print the resulting string. It is guaranteed that this string is not empty.

## 样例 #1

### 输入

```
tour

```

### 输出

```
.t.r

```

## 样例 #2

### 输入

```
Codeforces

```

### 输出

```
.c.d.f.r.c.s

```

## 样例 #3

### 输入

```
aBAcAba

```

### 输出

```
.b.c.b

```



---

---
title: "Cookies"
layout: "post"
diff: 入门
pid: CF129A
tag: ['字符串', '数学', '概率论']
---

# Cookies

## 输出格式

感谢@面瘫者 提供的翻译

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10
1 2 2 3 4 4 4 2 2 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
11
2 2 2 2 2 2 2 2 2 2 99

```

### 输出

```
1

```



---

---
title: "Super Agent"
layout: "post"
diff: 入门
pid: CF12A
tag: ['模拟', '字符串', '枚举']
---

# Super Agent

## 题目描述

There is a very secret base in Potatoland where potato mash is made according to a special recipe. The neighbours from Porridgia decided to seize this recipe and to sell it to Pilauland. For this mission they have been preparing special agent Pearlo for many years. When, finally, Pearlo learned all secrets of espionage, he penetrated into the Potatoland territory and reached the secret base.

Now he is standing at the entrance, but to get inside he need to pass combination lock. Minute ago one of the workers entered the password on the terminal and opened the door. The terminal is a square digital keyboard $ 3×3 $ with digits from $ 1 $ to $ 9 $ .

Pearlo knows that the password consists from distinct digits and is probably symmetric with respect to the central button of the terminal. He has heat sensor which allowed him to detect the digits which the worker pressed. Now he wants to check whether the password entered by the worker is symmetric with respect to the central button of the terminal. This fact can Help Pearlo to reduce the number of different possible password combinations.

## 输入格式

Input contains the matrix of three rows of three symbols each. Symbol «X» means that the corresponding button was pressed, and «.» means that is was not pressed. The matrix may contain no «X», also it may contain no «.».

## 输出格式

Print YES if the password is symmetric with respect to the central button of the terminal and NO otherwise.

## 说明/提示

If you are not familiar with the term «central symmetry», you may look into http://en.wikipedia.org/wiki/Central\_symmetry

## 样例 #1

### 输入

```
XX.
...
.XX

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
X.X
X..
...

```

### 输出

```
NO

```



---

---
title: "cAPS lOCK"
layout: "post"
diff: 入门
pid: CF131A
tag: ['字符串', '概率论']
---

# cAPS lOCK

## 题目描述

wHAT DO WE NEED cAPS LOCK FOR?

Caps lock is a computer keyboard key. Pressing it sets an input mode in which typed letters are capital by default. If it is pressed by accident, it leads to accidents like the one we had in the first passage.

Let's consider that a word has been typed with the Caps lock key accidentally switched on, if:

- either it only contains uppercase letters;
- or all letters except for the first one are uppercase.

In this case we should automatically change the case of all letters. For example, the case of the letters that form words "hELLO", "HTTP", "z" should be changed.

Write a program that applies the rule mentioned above. If the rule cannot be applied, the program should leave the word unchanged.

## 输入格式

The first line of the input data contains a word consisting of uppercase and lowercase Latin letters. The word's length is from 1 to 100 characters, inclusive.

## 输出格式

Print the result of the given word's processing.

## 样例 #1

### 输入

```
cAPS

```

### 输出

```
Caps
```

## 样例 #2

### 输入

```
Lock

```

### 输出

```
Lock

```



---

---
title: "HQ9+"
layout: "post"
diff: 入门
pid: CF133A
tag: ['字符串', '枚举']
---

# HQ9+

## 题目描述

HQ9+是一种搞笑的编程语言，只有4种指令，都是单个字符的：
"H"输出"Hello, World!"；
"Q"输出这个程序本身的源代码；
"9"输出歌曲"99 Bottles of Beer"的歌词（你可以自己上网搜这首歌）；
"+"增加内部储存中的数值

注意"H"和"Q"指令是区分大小写的，必须使用大写。程序中不属于这些指令的字符请忽略。

给你一个用HQ9+写的程序，问这个程序是否会有任何输出。

## 输入格式

输入有一行，p是这个HQ9+的程序。字符串p的长度在1和100之间，包括1和100。字符串p中每一个字符的ASCII码在33('!'感叹号)和126('~'波浪)之间，包括33和126。

## 输出格式

如果这个程序有输出，输出"YES"，否则输出"NO"。

## 说明/提示

第一个样例中只有一个指令"H"，输出了"Hello, World!"。

第二个样例中没有任何一个字符是这个程序的指令。
翻译贡献者UID：68708

## 样例 #1

### 输入

```
Hi!

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
Codeforces

```

### 输出

```
NO

```



---

---
title: "Last Year's Substring"
layout: "post"
diff: 入门
pid: CF1462B
tag: ['字符串']
---

# Last Year's Substring

## 题目描述

本题给你一个字符串，问删去其中一个可以为空的字串后，能否使其变为"$2020$"。

## 输入格式

第一行一个整数，为测试数据数量。

对于每个数据，第一行一个整数，为字符串长度。第二行输入字符串。

## 输出格式

对于每个数据点，如果可以，输出$YES$，否则输出$NO$。

## 样例 #1

### 输入

```
6
8
20192020
8
22019020
4
2020
5
20002
6
729040
6
200200
```

### 输出

```
YES
YES
YES
NO
NO
NO
```



---

---
title: "Letter"
layout: "post"
diff: 入门
pid: CF14A
tag: ['模拟', '字符串']
---

# Letter

## 题目描述

给定一 $N \times M$ 规模的矩阵，输出最小的包含所有 `*` 的矩阵。

## 输入格式

一行两个整数， $N$ 和 $M$ 。

然后一个 $N \times M$ 大小的矩阵。

## 输出格式

输出最小的包含所有 `*` 的矩阵。

## 说明/提示

$1 \leq N,M \leq 50$。

## 样例 #1

### 输入

```
6 7
.......
..***..
..*....
..***..
..*....
..***..

```

### 输出

```
***
*..
***
*..
***

```

## 样例 #2

### 输入

```
3 3
***
*.*
***

```

### 输出

```
***
*.*
***

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
title: "Reverse and Concatenate"
layout: "post"
diff: 入门
pid: CF1634A
tag: ['字符串']
---

# Reverse and Concatenate

## 题目描述

Real stupidity beats artificial intelligence every time.

— Terry Pratchett, Hogfather, Discworld



You are given a string $ s $ of length $ n $ and a number $ k $ . Let's denote by $ rev(s) $ the reversed string $ s $ (i.e. $ rev(s) = s_n s_{n-1} ... s_1 $ ). You can apply one of the two kinds of operations to the string:

- replace the string $ s $ with $ s + rev(s) $
- replace the string $ s $ with $ rev(s) + s $

How many different strings can you get as a result of performing exactly $ k $ operations (possibly of different kinds) on the original string $ s $ ?

In this statement we denoted the concatenation of strings $ s $ and $ t $ as $ s + t $ . In other words, $ s + t = s_1 s_2 ... s_n t_1 t_2 ... t_m $ , where $ n $ and $ m $ are the lengths of strings $ s $ and $ t $ respectively.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — number of test cases. Next $ 2 \cdot t $ lines contain $ t $ test cases:

The first line of a test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100 $ , $ 0 \le k \le 1000 $ ) — the length of the string and the number of operations respectively.

The second string of a test case contains one string $ s $ of length $ n $ consisting of lowercase Latin letters.

## 输出格式

For each test case, print the answer (that is, the number of different strings that you can get after exactly $ k $ operations) on a separate line.

It can be shown that the answer does not exceed $ 10^9 $ under the given constraints.

## 说明/提示

In the first test case of the example:

After the first operation the string $ s $ can become either aabbaa or baaaab. After the second operation there are 2 possibilities for $ s $ : aabbaaaabbaa and baaaabbaaaab.

## 样例 #1

### 输入

```
4
3 2
aab
3 3
aab
7 1
abacaba
2 0
ab
```

### 输出

```
2
2
1
1
```



---

---
title: "Doors and Keys"
layout: "post"
diff: 入门
pid: CF1644A
tag: ['模拟', '字符串', '栈']
---

# Doors and Keys

## 题目描述

The knight is standing in front of a long and narrow hallway. A princess is waiting at the end of it.

In a hallway there are three doors: a red door, a green door and a blue door. The doors are placed one after another, however, possibly in a different order. To proceed to the next door, the knight must first open the door before.

Each door can be only opened with a key of the corresponding color. So three keys: a red key, a green key and a blue key — are also placed somewhere in the hallway. To open the door, the knight should first pick up the key of its color.

The knight has a map of the hallway. It can be transcribed as a string, consisting of six characters:

- R, G, B — denoting red, green and blue doors, respectively;
- r, g, b — denoting red, green and blue keys, respectively.

Each of these six characters appears in the string exactly once.

The knight is standing at the beginning of the hallway — on the left on the map.

Given a map of the hallway, determine if the knight can open all doors and meet the princess at the end of the hallway.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 720 $ ) — the number of testcases.

Each testcase consists of a single string. Each character is one of R, G, B (for the doors), r, g, b (for the keys), and each of them appears exactly once.

## 输出格式

For each testcase, print YES if the knight can open all doors. Otherwise, print NO.

## 说明/提示

In the first testcase, the knight first collects all keys, then opens all doors with them.

In the second testcase, there is a red door right in front of the knight, but he doesn't have a key for it.

In the third testcase, the key to each door is in front of each respective door, so the knight collects the key and uses it immediately three times.

In the fourth testcase, the knight can't open the blue door.

## 样例 #1

### 输入

```
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "Flag"
layout: "post"
diff: 入门
pid: CF16A
tag: ['模拟', '字符串', '枚举']
---

# Flag

## 题目描述

根据一项新的 ISO 标准，每一个国家的国旗应该是一个 $n\times m$ 的格子场，其中每个格子最多有 $10$ 种不同的颜色。并且国旗应该有条纹：旗帜的每一行应包含相同颜色的方块，相邻的行的颜色应该是不同的。Berland 政府要求你找出他们的国旗是否符合新的 ISO 标准。

## 输入格式

输入的第一行包含数 $n$ 和 $m$，其中 $n$ 为行数，$m$ 为列数。

接下来是对旗的描述：以下 $n$ 行中的每一行包含 $m$ 个字符。每个字符是 $0$ 到 $9$ 之间的数字，代表相应正方形的颜色。

## 输出格式

如果国旗符合标准就输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
3 3
000
111
222

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 3
000
000
111

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3 3
000
111
002

```

### 输出

```
NO

```



---

---
title: "Yes-Yes?"
layout: "post"
diff: 入门
pid: CF1759A
tag: ['字符串']
---

# Yes-Yes?

## 题目描述

You talked to Polycarp and asked him a question. You know that when he wants to answer "yes", he repeats Yes many times in a row.

Because of the noise, you only heard part of the answer — some substring of it. That is, if he answered YesYes, then you could hear esY, YesYes, sYes, e, but you couldn't Yess, YES or se.

Determine if it is true that the given string $ s $ is a substring of YesYesYes... (Yes repeated many times in a row).

## 输入格式

The first line of input data contains the singular $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases in the test.

Each test case is described by a single string of Latin letters $ s $ ( $ 1 \le |s| \le 50 $ ) — the part of Polycarp's answer that you heard, where $ |s| $ — is the length of the string $ s $ .

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if the specified string $ s $ is a substring of the string YesYesYes...Yes (the number of words Yes is arbitrary), and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 输入

```
12
YES
esYes
codeforces
es
se
YesY
esYesYesYesYesYesYe
seY
Yess
sY
o
Yes
```

### 输出

```
NO
YES
NO
YES
NO
YES
YES
NO
NO
YES
NO
YES
```



---

---
title: "Creating Words"
layout: "post"
diff: 入门
pid: CF1985A
tag: ['模拟', '字符串']
---

# Creating Words

## 题目描述

Matthew is given two strings $ a $ and $ b $ , both of length $ 3 $ . He thinks it's particularly funny to create two new words by swapping the first character of $ a $ with the first character of $ b $ . He wants you to output $ a $ and $ b $ after the swap.

Note that the new words may not necessarily be different.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated strings, $ a $ and $ b $ , both of length $ 3 $ . The strings only contain lowercase Latin letters.

## 输出格式

For each test case, after the swap, output $ a $ and $ b $ , separated by a space.

## 样例 #1

### 输入

```
6
bit set
cat dog
hot dog
uwu owo
cat cat
zzz zzz
```

### 输出

```
sit bet
dat cog
dot hog
owu uwo
cat cat
zzz zzz
```



---

---
title: "Message Transmission Error (easy version)"
layout: "post"
diff: 入门
pid: CF2010C1
tag: ['模拟', '字符串']
---

# Message Transmission Error (easy version)

## 题目描述

This is a simplified version of the problem. It differs from the difficult one only in its constraints.

At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.

For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).

Given the received message $ t $ , determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of $ s $ .

A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

## 输入格式

The input consists of a single non-empty string $ t $ , consisting of lowercase letters of the Latin alphabet. The length of the string $ t $ does not exceed $ 100 $ characters.

## 输出格式

If the message $ t $ cannot contain an error, output "NO" (without quotes) in a single line of output.

Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string $ s $ — a possible message that could have led to the error. If there are multiple possible answers, any of them is acceptable.

## 说明/提示

In the second example, a suitable answer could also be the string "acacaca".

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
acaca
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
title: "Skibidus and Amog'u"
layout: "post"
diff: 入门
pid: CF2065A
tag: ['字符串']
---

# Skibidus and Amog'u

## 题目描述

Skibidus 降落到一颗陌生的星球，当地的 Amog 部落讲着 Amog'u 语言。在 Amog'u 语言中，名词有两种形式：单数和复数。

设名词的词根为 $ S $，则这两种形式分别转写为：

- **单数形式**：$ S $ $ + $ "us"
- **复数形式**：$ S $ $ + $ "i"

其中，$ + $ 表示 [字符串拼接](https://zh.wikipedia.org/wiki/%E4%B8%B2%E6%8E%A5)。例如，abc $ + $ def $ = $ abcdef。

例如，当 $ S $ 被转写为 "amog" 时，单数形式为 "amogus"，复数形式为 "amogi"。请注意，Amog'u 语言中的名词可以具有空的词根 —— 具体来说，"us" 是空词根对应的单数形式，而 "i" 则是复数形式（顺便提一句，这两个词分别意为 “imposter”（冒充者）和 “imposters”（冒充者们））。

给定一个转写为单数形式的 Amog'u 名词，请将其转换为相应复数形式的转写。

## 输入格式

每个测试点包含多个测试数据。

第一行是一个整数 $ t $ ( $ 1 \le t \le 100 $ )，表示测试数据的数量。随后给出各个测试数据的描述。

每个测试数据仅包含一行，一个字符串 $ W $，它是转写为单数形式的 Amog'u 名词。保证 $ W $ 只由小写英文字母组成，长度最多为 $ 10 $，并且以 "us" 结尾。

## 输出格式

对于每个测试数据，输出相应复数形式的 Amog'u 名词，每个结果单独占一行。

## 样例 #1

### 输入

```
9
us
sus
fungus
cactus
sussus
amogus
chungus
ntarsus
skibidus
```

### 输出

```
i
si
fungi
cacti
sussi
amogi
chungi
ntarsi
skibidi
```



---

---
title: "Skibidus and Ohio"
layout: "post"
diff: 入门
pid: CF2065B
tag: ['字符串']
---

# Skibidus and Ohio

## 题目描述

斯基比德斯得到一个由小写拉丁字母组成的字符串 $s$ 。如果 $s$ 包含的字母多于 $1$ ，他就可以：

- 选择一个索引 $i$ ( $1 \leq i \leq |s| - 1$ ， $|s|$ 表示 $s$ 的当前长度)，使得 $s_i = s_{i+1}$ .用任意一个小写拉丁字母替换 $s_i$ 。从字符串中删除 $s _{i+1}$。

斯基比达斯必须确定他通过任意操作所能达到的最小长度。

## 输入格式

第一行包含一个整数 $t$ ( $1 \leq t \leq 100$ ) - 测试用例的数量。

每个测试用例的唯一一行包含一个字符串 $s$ ( $1 \leq |s| \leq 100$ )。保证 $s$ 只包含小写拉丁字母。

## 输出格式

对于每个测试用例，在新行中输出一个整数，最小可达到的长度为 $s$ 。

## 说明/提示

在第一个测试案例中，Skibidus 可以

- 对 $i = 2$ 执行操作。他将 $s_2$ 替换为 b，并从字符串中删除 $s_3$ 。然后， $s$ 就变成了 bb。
- 对 $i = 1$ 进行操作。他将 $s_1$ 替换为 b，并从字符串中删除 $s_2$ 。然后， $s$ 就变成了 b。
- 因为 $s$ 只包含 $1$ 个字母，所以斯基比达斯无法进行更多运算。

因此，第一个测试用例的答案是 $1$ 。

在第二个测试案例中，他无法对任何索引进行操作。因此，答案仍然是初始字符串的长度 $8$ 。

## 样例 #1

### 输入

```
4
baa
skibidus
cc
ohio
```

### 输出

```
1
8
1
4
```



---

---
title: "Olympiad Date"
layout: "post"
diff: 入门
pid: CF2091A
tag: ['模拟', '字符串']
---

# Olympiad Date

## 题目描述

第一届 IT Campus "NEIMARK" 奥林匹克的决赛定于 2025 年 3 月 1 日举行。一位无名实习生被要求用数字组成奥林匹克的日期——01.03.2025。

为了完成这个任务，实习生拿了一大袋数字并开始逐个抽取。他一共抽取了 $n$ 个数字——在第 $i$ 次抽取时抽到了数字 $a_i$。

你怀疑实习生做了多余的工作。请确定实习生在第几步时首次能够用已抽取的数字组成奥林匹克的日期（分隔的点可以忽略），或者报告无法用这些数字组成该日期。注意前导零必须显示。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^4$)。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \le n \le 20$)。

每个测试用例的第二行包含 $n$ 个整数 $a_i$ ($0 \leq a_i \leq 9$)——实习生按时间顺序抽取的数字。

## 输出格式

对于每个测试用例，输出实习生可能抽取的最小数字数量（即最早满足条件的步数）。如果所有数字都无法组成日期，则输出数字 $0$。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
10
2 0 1 2 3 2 5 0 0 1
8
2 0 1 2 3 2 5 0
8
2 0 1 0 3 2 5 0
16
2 3 1 2 3 0 1 9 2 1 0 3 5 4 0 3
```

### 输出

```
9
0
8
15
```



---

---
title: "Trippi Troppi"
layout: "post"
diff: 入门
pid: CF2094A
tag: ['字符串']
---

# Trippi Troppi

## 题目描述

Trippi Troppi 居住在一个奇异的世界里。每个国家的古代名称由三个字符串组成，将每个字符串的首字母连接起来就形成了该国家的现代名称。

给定一个国家的古代名称，请输出其现代名称。

## 输入格式

第一行包含一个整数 $t$ —— 独立测试用例的数量（$1 \leq t \leq 100$）。

接下来的 $t$ 行，每行包含三个用空格分隔的字符串。每个字符串的长度不超过 $10$，且仅包含小写拉丁字母。

## 输出格式

对于每个测试用例，输出由每个单词的首字母连接而成的字符串。

## 样例 #1

### 输入

```
7
united states america
oh my god
i cant lie
binary indexed tree
believe in yourself
skibidi slay sigma
god bless america
```

### 输出

```
usa
omg
icl
bit
biy
sss
gba
```



---

---
title: "BerOS file system"
layout: "post"
diff: 入门
pid: CF20A
tag: ['模拟', '字符串']
---

# BerOS file system

## 题目描述

新的操作系统BerOS有一个很好的特性。可以在路径中使用任意数量的字符“/”作为分隔符，而不是使用一个传统的“/”。例如，字符串`//usr///local//nginx/sbin//`和`/usr/local/nginx///sbin//`是等效的。只有根目录的路径可以表示为单个字符“/”，才需要路径末尾的字符“/”（或此类字符的某些序列）。
如果路径包含尽可能少的字符数“/”，则称为normalized的路径。

您的任务是将给定路径转换为规范化形式。

## 输入格式

一行，仅包含小写字母和`/`的字符串，保证路径至少含有一个`/`，不超过 $100$ 个字符。

## 输出格式

一行，一个字符串，表示简化后的路径。

## 样例 #1

### 输入

```
//usr///local//nginx/sbin

```

### 输出

```
/usr/local/nginx/sbin

```



---

---
title: "Is your horseshoe on the other hoof?"
layout: "post"
diff: 入门
pid: CF228A
tag: ['字符串']
---

# Is your horseshoe on the other hoof?

## 题目描述

有匹叫Valera的马要和朋友一起去参加聚会。

他一直关注时尚，知道穿不同颜色的马蹄铁非常流行。

去年Valera有四个马蹄铁留下来了，但也许有些颜色相同。在这种情况下，他需要去商店买更多的马蹄铁，让他不在他时髦的同志面前丢脸。

幸运的是，有家商店出售各种颜色的马蹄铁，且Valera有足够的钱购买四种。然而，为了省钱，他想花尽可能少的钱，所以你需要帮助Valera，并确定他至少需要买多少马蹄铁来保证他有四种不同颜色的马蹄铁去参加派对。

## 输入格式

一行，四个数，即四个马蹄铁的颜色

## 输出格式

一行，表示他最少要花多少钱

感谢@引领天下 提供的翻译

## 样例 #1

### 输入

```
1 7 3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
7 7 7 7

```

### 输出

```
3

```



---

---
title: "Boy or Girl"
layout: "post"
diff: 入门
pid: CF236A
tag: ['模拟', '字符串']
---

# Boy or Girl

## 题目描述

Those days, many boys use beautiful girls' photos as avatars in forums. So it is pretty hard to tell the gender of a user at the first glance. Last year, our hero went to a forum and had a nice chat with a beauty (he thought so). After that they talked very often and eventually they became a couple in the network.

But yesterday, he came to see "her" in the real world and found out "she" is actually a very strong man! Our hero is very sad and he is too tired to love again now. So he came up with a way to recognize users' genders by their user names.

This is his method: if the number of distinct characters in one's user name is odd, then he is a male, otherwise she is a female. You are given the string that denotes the user name, please help our hero to determine the gender of this user by his method.

## 输入格式

The first line contains a non-empty string, that contains only lowercase English letters — the user name. This string contains at most 100 letters.

## 输出格式

If it is a female by our hero's method, print "CHAT WITH HER!" (without the quotes), otherwise, print "IGNORE HIM!" (without the quotes).

## 说明/提示

For the first example. There are 6 distinct characters in "wjmzbmr". These characters are: "w", "j", "m", "z", "b", "r". So wjmzbmr is a female and you should print "CHAT WITH HER!".

## 样例 #1

### 输入

```
wjmzbmr

```

### 输出

```
CHAT WITH HER!

```

## 样例 #2

### 输入

```
xiaodao

```

### 输出

```
IGNORE HIM!

```

## 样例 #3

### 输入

```
sevenkplus

```

### 输出

```
CHAT WITH HER!

```



---

---
title: "You're Given a String..."
layout: "post"
diff: 入门
pid: CF23A
tag: ['字符串', '枚举']
---

# You're Given a String...

## 题目描述

You're given a string of lower-case Latin letters. Your task is to find the length of its longest substring that can be met in the string at least twice. These occurrences can overlap (see sample test 2).

## 输入格式

The first input line contains the string. It's guaranteed, that the string is non-empty, consists of lower-case Latin letters, and its length doesn't exceed 100.

## 输出格式

Output one number — length of the longest substring that can be met in the string at least twice.

## 样例 #1

### 输入

```
abcd

```

### 输出

```
0
```

## 样例 #2

### 输入

```
ababa

```

### 输出

```
3
```

## 样例 #3

### 输入

```
zzz

```

### 输出

```
2
```



---

---
title: "Phone numbers"
layout: "post"
diff: 入门
pid: CF25B
tag: ['模拟', '字符串']
---

# Phone numbers

## 题目描述

Phone number in Berland is a sequence of $ n $ digits. Often, to make it easier to memorize the number, it is divided into groups of two or three digits. For example, the phone number 1198733 is easier to remember as 11-987-33. Your task is to find for a given phone number any of its divisions into groups of two or three digits.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=100 $ ) — amount of digits in the phone number. The second line contains $ n $ digits — the phone number to divide into groups.

## 输出格式

Output any of divisions of the given phone number into groups of two or three digits. Separate groups by single character -. If the answer is not unique, output any.

## 样例 #1

### 输入

```
6
549871

```

### 输出

```
54-98-71
```

## 样例 #2

### 输入

```
7
1198733

```

### 输出

```
11-987-33

```



---

---
title: "Colorful Stones (Simplified Edition)"
layout: "post"
diff: 入门
pid: CF265A
tag: ['模拟', '字符串']
---

# Colorful Stones (Simplified Edition)

## 题目描述

There is a sequence of colorful stones. The color of each stone is one of red, green, or blue. You are given a string $ s $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone. You perform instructions one or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , if Liss is standing on a stone whose colors is $ c $ , Liss will move one stone forward, else she will not move.

You are given a string $ t $ . The number of instructions is equal to the length of $ t $ , and the $ i $ -th character of $ t $ represents the $ i $ -th instruction.

Calculate the final position of Liss (the number of the stone she is going to stand on in the end) after performing all the instructions, and print its 1-based position. It is guaranteed that Liss don't move out of the sequence.

## 输入格式

The input contains two lines. The first line contains the string $ s $ ( $ 1<=|s|<=50 $ ). The second line contains the string $ t $ ( $ 1<=|t|<=50 $ ). The characters of each string will be one of "R", "G", or "B". It is guaranteed that Liss don't move out of the sequence.

## 输出格式

Print the final 1-based position of Liss in a single line.

## 样例 #1

### 输入

```
RGB
RRR

```

### 输出

```
2

```

## 样例 #2

### 输入

```
RRRBGBRBBB
BBBRR

```

### 输出

```
3

```

## 样例 #3

### 输入

```
BRRBGBRGRBGRGRRGGBGBGBRGBRGRGGGRBRRRBRBBBGRRRGGBBB
BBRBGGRGRGBBBRBGRBRBBBBRBRRRBGBBGBBRRBBGGRBRRBRGRB

```

### 输出

```
15

```



---

---
title: "Stones on the Table"
layout: "post"
diff: 入门
pid: CF266A
tag: ['字符串']
---

# Stones on the Table

## 题目描述

桌子上有N个石头，每一块都可以是红的、绿的或蓝的。计算从桌子上取下的石头的最小数量，以便任何两块相邻的石头都有不同的颜色。如果没有其他石头，一排石头被认为是相邻的。

## 输入格式

第一行是一个整数n（1<=n<=50）--桌上石头的数量

第二行是一个字符串s，代表着石头的颜色，石头的排法为从1到n，从左到右。s中的第i个字母如果是"R",那么第i个石头就是红色，"G"是绿色，"B"是蓝色

## 输出格式

输出一个整数——这个问题的答案

感谢U91783提供的翻译

## 样例 #1

### 输入

```
3
RRG

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
RRRRR

```

### 输出

```
4

```

## 样例 #3

### 输入

```
4
BRBG

```

### 输出

```
0

```



---

---
title: "Beautiful Year"
layout: "post"
diff: 入门
pid: CF271A
tag: ['模拟', '字符串', '枚举']
---

# Beautiful Year

## 题目描述

It seems like the year of 2013 came only yesterday. Do you know a curious fact? The year of 2013 is the first year after the old 1987 with only distinct digits.

Now you are suggested to solve the following problem: given a year number, find the minimum year number which is strictly larger than the given one and has only distinct digits.

## 输入格式

The single line contains integer $ y $ $ (1000<=y<=9000) $ — the year number.

## 输出格式

Print a single integer — the minimum year number that is strictly larger than $ y $ and all it's digits are distinct. It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
1987

```

### 输出

```
2013

```

## 样例 #2

### 输入

```
2013

```

### 输出

```
2014

```



---

---
title: "Word Capitalization"
layout: "post"
diff: 入门
pid: CF281A
tag: ['字符串']
---

# Word Capitalization

## 题目描述

Capitalization is writing a word with its first letter as a capital letter. Your task is to capitalize the given word.

Note, that during capitalization all the letters except the first one remains unchanged.

## 输入格式

A single line contains a non-empty word. This word consists of lowercase and uppercase English letters. The length of the word will not exceed $ 10^{3} $ .

## 输出格式

Output the given word after capitalization.

## 样例 #1

### 输入

```
ApPLe

```

### 输出

```
ApPLe

```

## 样例 #2

### 输入

```
konjac

```

### 输出

```
Konjac

```



---

---
title: "Bit++"
layout: "post"
diff: 入门
pid: CF282A
tag: ['模拟', '字符串']
---

# Bit++

## 题目描述

The classic programming language of Bitland is Bit++. This language is so peculiar and complicated.

The language is that peculiar as it has exactly one variable, called $ x $ . Also, there are two operations:

- Operation ++ increases the value of variable $ x $ by 1.
- Operation -- decreases the value of variable $ x $ by 1.

A statement in language Bit++ is a sequence, consisting of exactly one operation and one variable $ x $ . The statement is written without spaces, that is, it can only contain characters "+", "-", "X". Executing a statement means applying the operation it contains.

A programme in Bit++ is a sequence of statements, each of them needs to be executed. Executing a programme means executing all the statements it contains.

You're given a programme in language Bit++. The initial value of $ x $ is $ 0 $ . Execute the programme and find its final value (the value of the variable when this programme is executed).

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=150) $ — the number of statements in the programme.

Next $ n $ lines contain a statement each. Each statement contains exactly one operation (++ or --) and exactly one variable $ x $ (denoted as letter «X»). Thus, there are no empty statements. The operation and the variable can be written in any order.

## 输出格式

Print a single integer — the final value of $ x $ .

## 样例 #1

### 输入

```
1
++X

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
X++
--X

```

### 输出

```
0

```



---

---
title: "Borze"
layout: "post"
diff: 入门
pid: CF32B
tag: ['模拟', '字符串']
---

# Borze

## 题目描述

### 题面描述

三进制数字符号在Berland很受欢迎。如果用borze编码表示电报的三进制数。数字 $0,1,2$ 分别被作为`.`，`-.`和`--`。你需要为borze编码解码。（把borze编码转换为三进制数）。

## 输入格式

第一行包含在Borze编码。字符串的长度介于 $1$ 到 $200$ 个字符之间。这是保证给定的字符串是一个有效的一些三元数borze编码（这个数可能有前导零）。

## 输出格式

一个三进制数（如果有前导零要输出）。

## 样例 #1

### 输入

```
.-.--

```

### 输出

```
012
```

## 样例 #2

### 输入

```
--.

```

### 输出

```
20
```

## 样例 #3

### 输入

```
-..-.--

```

### 输出

```
1012
```



---

---
title: "Helpful Maths"
layout: "post"
diff: 入门
pid: CF339A
tag: ['字符串', '排序', '概率论']
---

# Helpful Maths

## 题目描述

Xenia the beginner mathematician is a third year student at elementary school. She is now learning the addition operation.

The teacher has written down the sum of multiple numbers. Pupils should calculate the sum. To make the calculation easier, the sum only contains numbers 1, 2 and 3. Still, that isn't enough for Xenia. She is only beginning to count, so she can calculate a sum only if the summands follow in non-decreasing order. For example, she can't calculate sum 1+3+2+1 but she can calculate sums 1+1+2 and 3+3.

You've got the sum that was written on the board. Rearrange the summans and print the sum in such a way that Xenia can calculate the sum.

## 输入格式

The first line contains a non-empty string $ s $ — the sum Xenia needs to count. String $ s $ contains no spaces. It only contains digits and characters "+". Besides, string $ s $ is a correct sum of numbers 1, 2 and 3. String $ s $ is at most 100 characters long.

## 输出格式

Print the new sum that Xenia can count.

## 样例 #1

### 输入

```
3+2+1

```

### 输出

```
1+2+3

```

## 样例 #2

### 输入

```
1+1+3+1+3

```

### 输出

```
1+1+1+3+3

```

## 样例 #3

### 输入

```
2

```

### 输出

```
2

```



---

---
title: "Extra-terrestrial Intelligence"
layout: "post"
diff: 入门
pid: CF36A
tag: ['模拟', '字符串']
---

# Extra-terrestrial Intelligence

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Recently Vasya got interested in finding extra-terrestrial intelligence. He made a simple extra-terrestrial signals’ receiver and was keeping a record of the signals for $ n $ days in a row. Each of those $ n $ days Vasya wrote a 1 in his notebook if he had received a signal that day and a 0 if he hadn’t. Vasya thinks that he has found extra-terrestrial intelligence if there is a system in the way the signals has been received, i.e. if all the intervals between successive signals are equal. Otherwise, Vasya thinks that the signals were sent by some stupid aliens no one cares about. Help Vasya to deduce from the information given by the receiver if he has found extra-terrestrial intelligence or not.

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=100 $ ) — amount of days during which Vasya checked if there were any signals. The second line contains $ n $ characters 1 or 0 — the record Vasya kept each of those $ n $ days. It’s guaranteed that the given record sequence contains at least three 1s.

## 输出格式

If Vasya has found extra-terrestrial intelligence, output YES, otherwise output NO.

## 样例 #1

### 输入

```
8
00111000

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
7
1001011

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7
1010100

```

### 输出

```
YES

```



---

---
title: "Translation"
layout: "post"
diff: 入门
pid: CF41A
tag: ['模拟', '字符串']
---

# Translation

## 题目描述

### 题面描述

Berland 和 Birland 两地均有各自的语言，Berlandish 和 Birlandish。V 是一个翻译员，负责将 Berlandish 翻译成 Birlandish。将 Berlandish 翻译成 Birlandish 其实非常简单，只需把这个单词倒过来。比如单词`code`翻译过来就是`edoc`。但是粗心的 V 还是会犯一些错误。现在请你帮她判断一下他翻译的是否正确。

## 输入格式

两行，分别是一个 Berlandish 单词和 V 翻译的 Birlandish 单词。单词中所有字母均为小写拉丁字母（其实就是英文字母）;单词长度均不超过 $100$ 字符，单词中不包含任何多余空格。

## 输出格式

一行，如果 V 的翻译是正确的，输出`YES`。否则输出`NO`。

## 样例 #1

### 输入

```
code
edoc

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abb
aba

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
code
code

```

### 输出

```
NO

```



---

---
title: "Football"
layout: "post"
diff: 入门
pid: CF43A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

One day Vasya decided to have a look at the results of Berland 1910 Football Championship’s finals. Unfortunately he didn't find the overall score of the match; however, he got hold of a profound description of the match's process. On the whole there are $ n $ lines in that description each of which described one goal. Every goal was marked with the name of the team that had scored it. Help Vasya, learn the name of the team that won the finals. It is guaranteed that the match did not end in a tie.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ) — the number of lines in the description. Then follow $ n $ lines — for each goal the names of the teams that scored it. The names are non-empty lines consisting of uppercase Latin letters whose lengths do not exceed 10 symbols. It is guaranteed that the match did not end in a tie and the description contains no more than two different teams.

## 输出格式

Print the name of the winning team. We remind you that in football the team that scores more goals is considered the winner.

## 样例 #1

### 输入

```
1
ABC

```

### 输出

```
ABC

```

## 样例 #2

### 输入

```
5
A
ABA
ABA
A
A

```

### 输出

```
A

```



---

---
title: "Letter"
layout: "post"
diff: 入门
pid: CF43B
tag: ['模拟', '字符串', '概率论']
---

# Letter

## 题目描述

### 题面描述

Vasya 决定利用报纸上的一段文字写一封匿名信。他可以从报纸上剪下一段文字（或字母），把他们粘贴到匿名信上去。已经剪下的文字不可重复使用。当然，匿名信中的空格不需要剪——他只要在空格处作出标记即可。现在，他知道报纸上的文字 $s1$ 和他即将写下的匿名信的内容 $s2$，请你帮他看看，他能否完成匿名信的书写。

## 输入格式

两行，分别是 $s1$ 和 $s2$（无空行），长度不超过 $200$，英文字母区分大小写，信中空格不作处理。

## 输出格式

写的出来就输出`YES`，否则输出`NO`。

## 样例 #1

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
where is your dog

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
Instead of dogging your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
abcdefg hijk
k j i h g f e d c b a

```

### 输出

```
YES

```



---

---
title: "Little Pony and Crystal Mine"
layout: "post"
diff: 入门
pid: CF454A
tag: ['模拟', '字符串']
---

# Little Pony and Crystal Mine

## 题目描述

Twilight Sparkle once got a crystal from the Crystal Mine. A crystal of size $ n $ ( $ n $ is odd; $ n>1 $ ) is an $ n×n $ matrix with a diamond inscribed into it.

You are given an odd integer $ n $ . You need to draw a crystal of size $ n $ . The diamond cells of the matrix should be represented by character "D". All other cells of the matrix should be represented by character "\*". Look at the examples to understand what you need to draw.

## 输入格式

The only line contains an integer $ n $ ( $ 3<=n<=101 $ ; $ n $ is odd).

## 输出格式

Output a crystal of size $ n $ .

## 样例 #1

### 输入

```
3

```

### 输出

```
*D*
DDD
*D*

```

## 样例 #2

### 输入

```
5

```

### 输出

```
**D**
*DDD*
DDDDD
*DDD*
**D**

```

## 样例 #3

### 输入

```
7

```

### 输出

```
***D***
**DDD**
*DDDDD*
DDDDDDD
*DDDDD*
**DDD**
***D***

```



---

---
title: "Codecraft III"
layout: "post"
diff: 入门
pid: CF45A
tag: ['字符串']
---

# Codecraft III

## 题目描述

给你一个月份，问你 $k$ 个月后的月份。

月份列表：

January, February, March, April, May, June, July, August, September, October, November, December

## 输入格式

输入第一行一个字符串 $s$（保证字符串是像列表中那样第一个字母大写，后面小写），第二行一个整数 $k$（$1 \leq k \leq 100$）。

## 输出格式

输出一个字符串，表示 $k$ 个月后的月份。

## 样例 #1

### 输入

```
November
3

```

### 输出

```
February

```

## 样例 #2

### 输入

```
May
24

```

### 输出

```
May

```



---

---
title: "Rock-paper-scissors"
layout: "post"
diff: 入门
pid: CF48A
tag: ['字符串', '枚举']
---

# Rock-paper-scissors

## 题目描述

### 题面描述

三个人玩石头剪刀布，问谁赢了。

## 输入格式

输入三行，每行一个字符串（`rock`(石头)，`scissors`(剪刀)，`paper`(布)），分别表示这三个人出的手势。

石头打破剪刀，剪刀剪纸，纸裹在石头上。

当有一个人同时赢过其他两人时，他获胜，否则胜负不分。

## 输出格式

如果第一个人赢了输出`F`，第二个人赢了输出`M`，第三个人赢了输出`S`，胜负不分输出`?`。
Translated by Khassar

## 样例 #1

### 输入

```
rock
rock
rock

```

### 输出

```
?

```

## 样例 #2

### 输入

```
paper
rock
rock

```

### 输出

```
F

```

## 样例 #3

### 输入

```
scissors
rock
rock

```

### 输出

```
?

```

## 样例 #4

### 输入

```
scissors
paper
rock

```

### 输出

```
?

```



---

---
title: "Sleuth"
layout: "post"
diff: 入门
pid: CF49A
tag: ['模拟', '字符串']
---

# Sleuth

## 题目描述

Vasya plays the sleuth with his friends. The rules of the game are as follows: those who play for the first time, that is Vasya is the sleuth, he should investigate a "crime" and find out what is happening. He can ask any questions whatsoever that can be answered with "Yes" or "No". All the rest agree beforehand to answer the questions like that: if the question’s last letter is a vowel, they answer "Yes" and if the last letter is a consonant, they answer "No". Of course, the sleuth knows nothing about it and his task is to understand that.

Unfortunately, Vasya is not very smart. After 5 hours of endless stupid questions everybody except Vasya got bored. That’s why Vasya’s friends ask you to write a program that would give answers instead of them.

The English alphabet vowels are: A, E, I, O, U, Y

The English alphabet consonants are: B, C, D, F, G, H, J, K, L, M, N, P, Q, R, S, T, V, W, X, Z



## 输入格式

The single line contains a question represented by a non-empty line consisting of large and small Latin letters, spaces and a question mark. The line length does not exceed 100. It is guaranteed that the question mark occurs exactly once in the line — as the last symbol and that the line contains at least one letter.

## 输出格式

Print answer for the question in a single line: YES if the answer is "Yes", NO if the answer is "No".

Remember that in the reply to the question the last letter, not the last character counts. I. e. the spaces and the question mark do not count as letters.

## 样例 #1

### 输入

```
Is it a melon?

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
Is it an apple?

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
  Is     it a banana ?

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
Is   it an apple  and a  banana   simultaneouSLY?

```

### 输出

```
YES

```



---

---
title: "A and B and Chess"
layout: "post"
diff: 入门
pid: CF519A
tag: ['模拟', '字符串', '概率论']
---

# A and B and Chess

## 题目描述

A和B正在准备参加编程比赛。

为了锻炼他们的逻辑思维能力从而更好地解决问题，A和B决定来下棋。在游戏期间，A突然想要知道哪位玩家占得了优势。

对于每个棋子我们知道它们的权势值：

皇后的值是9；
车的值是5；
象（相）的值是3；
骑士的值也是3；
卒（兵）的值是1；
国王的值不考虑在优势评估中.
一个玩家的优势值是他在棋盘上所有棋子权势值的总和。

因为A不喜欢算数，所以他请求你告诉他哪位玩家的占有优势？（即优势值更大）

## 输入格式

输入一共八行，八列，描述这个棋盘。

白方的棋子如要表示均用大写字母，黑方则用的是小写字母。

白方棋子规定如下：皇后用Q表示，车用R表示，象用B表示，骑士用N表示，卒用P表示，国王用K表示。

黑方棋子则相反，用小写字母：q,r,b,n,p,k。

一个空的棋盘格子用"."（一个点）表示

无需考虑棋盘上的情况能否在真实的游戏中实现，只需计算出优势总值再比较即可。

## 输出格式

如果白方的优势总值更大，则输出"White",如果黑方的优势总值更大，则输出"Black"。如果总值相等，那么请输出"Draw"。

## 说明/提示

对于样例一，白方总值为9，黑方总值为5，所以输出"White"。

对于样例二，两方总值均为39，输出"Draw"。

对于样例三，白方总值为9，黑方总值为16，输出"Black"。

Translated by @lonelysir

## 样例 #1

### 输入

```
...QK...
........
........
........
........
........
........
...rk...

```

### 输出

```
White

```

## 样例 #2

### 输入

```
rnbqkbnr
pppppppp
........
........
........
........
PPPPPPPP
RNBQKBNR

```

### 输出

```
Draw

```

## 样例 #3

### 输入

```
rppppppr
...k....
........
........
........
........
K...Q...
........

```

### 输出

```
Black

```



---

---
title: "Pangram"
layout: "post"
diff: 入门
pid: CF520A
tag: ['模拟', '字符串', '二分', '枚举']
---

# Pangram

## 题目描述

A word or a sentence in some language is called a pangram if all the characters of the alphabet of this language appear in it at least once. Pangrams are often used to demonstrate fonts in printing or test the output devices.

You are given a string consisting of lowercase and uppercase Latin letters. Check whether this string is a pangram. We say that the string contains a letter of the Latin alphabet if this letter occurs in the string in uppercase or lowercase.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of characters in the string.

The second line contains the string. The string consists only of uppercase and lowercase Latin letters.

## 输出格式

Output "YES", if the string is a pangram and "NO" otherwise.

## 样例 #1

### 输入

```
12
toosmallword

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog

```

### 输出

```
YES

```



---

---
title: "Autocomplete"
layout: "post"
diff: 入门
pid: CF53A
tag: ['模拟', '字符串']
---

# Autocomplete

## 题目描述

Autocomplete is a program function that enables inputting the text (in editors, command line shells, browsers etc.) completing the text by its inputted part. Vasya is busy working on a new browser called 'BERowser'. He happens to be working on the autocomplete function in the address line at this very moment. A list consisting of $ n $ last visited by the user pages and the inputted part $ s $ are known. Your task is to complete $ s $ to make it an address of one of the pages from the list. You have to find the lexicographically smallest address having a prefix $ s $ .

## 输入格式

The first line contains the $ s $ line which is the inputted part. The second line contains an integer $ n $ ( $ 1<=n<=100 $ ) which is the number of visited pages. Then follow $ n $ lines which are the visited pages, one on each line. All the lines have lengths of from $ 1 $ to $ 100 $ symbols inclusively and consist of lowercase Latin letters only.

## 输出格式

If $ s $ is not the beginning of any of $ n $ addresses of the visited pages, print $ s $ . Otherwise, print the lexicographically minimal address of one of the visited pages starting from $ s $ .

The lexicographical order is the order of words in a dictionary. The lexicographical comparison of lines is realized by the '<' operator in the modern programming languages.

## 样例 #1

### 输入

```
next
2
nextpermutation
nextelement

```

### 输出

```
nextelement

```

## 样例 #2

### 输入

```
find
4
find
findfirstof
findit
fand

```

### 输出

```
find

```

## 样例 #3

### 输入

```
find
4
fondfind
fondfirstof
fondit
fand

```

### 输出

```
find

```



---

---
title: "Soldier and Bananas"
layout: "post"
diff: 入门
pid: CF546A
tag: ['字符串', '数学', '概率论']
---

# Soldier and Bananas

## 题目描述

A soldier wants to buy $ w $ bananas in the shop. He has to pay $ k $ dollars for the first banana, $ 2k $ dollars for the second one and so on (in other words, he has to pay $ i·k $ dollars for the $ i $ -th banana).

He has $ n $ dollars. How many dollars does he have to borrow from his friend soldier to buy $ w $ bananas?

## 输入格式

The first line contains three positive integers $ k,n,w $ ( $ 1<=k,w<=1000 $ , $ 0<=n<=10^{9} $ ), the cost of the first banana, initial number of dollars the soldier has and number of bananas he wants.

## 输出格式

Output one integer — the amount of dollars that the soldier must borrow from his friend. If he doesn't have to borrow money, output $ 0 $ .

## 样例 #1

### 输入

```
3 17 4

```

### 输出

```
13
```



---

---
title: "Chat room"
layout: "post"
diff: 入门
pid: CF58A
tag: ['模拟', '字符串', '枚举', '队列']
---

# Chat room

## 题目描述

Vasya has recently learned to type and log on to the Internet. He immediately entered a chat room and decided to say hello to everybody. Vasya typed the word $ s $ . It is considered that Vasya managed to say hello if several letters can be deleted from the typed word so that it resulted in the word "hello". For example, if Vasya types the word "ahhellllloou", it will be considered that he said hello, and if he types "hlelo", it will be considered that Vasya got misunderstood and he didn't manage to say hello. Determine whether Vasya managed to say hello by the given word $ s $ .

## 输入格式

The first and only line contains the word $ s $ , which Vasya typed. This word consisits of small Latin letters, its length is no less that 1 and no more than 100 letters.

## 输出格式

If Vasya managed to say hello, print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
ahhellllloou

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
hlelo

```

### 输出

```
NO

```



---

---
title: "Word"
layout: "post"
diff: 入门
pid: CF59A
tag: ['模拟', '字符串', '概率论']
---

# Word

## 题目描述

Vasya is very upset that many people on the Net mix uppercase and lowercase letters in one word. That's why he decided to invent an extension for his favorite browser that would change the letters' register in every word so that it either only consisted of lowercase letters or, vice versa, only of uppercase ones. At that as little as possible letters should be changed in the word. For example, the word HoUse must be replaced with house, and the word ViP — with VIP. If a word contains an equal number of uppercase and lowercase letters, you should replace all the letters with lowercase ones. For example, maTRIx should be replaced by matrix. Your task is to use the given method on one given word.

## 输入格式

The first line contains a word $ s $ — it consists of uppercase and lowercase Latin letters and possesses the length from $ 1 $ to $ 100 $ .

## 输出格式

Print the corrected word $ s $ . If the given word $ s $ has strictly more uppercase letters, make the word written in the uppercase register, otherwise - in the lowercase one.

## 样例 #1

### 输入

```
HoUse

```

### 输出

```
house

```

## 样例 #2

### 输入

```
ViP

```

### 输出

```
VIP

```

## 样例 #3

### 输入

```
maTRIx

```

### 输出

```
matrix

```



---

---
title: "Chat Server's Outgoing Traffic"
layout: "post"
diff: 入门
pid: CF5A
tag: ['模拟', '字符串']
---

# Chat Server's Outgoing Traffic

## 题目描述

Polycarp正在开发一个名为“Polychat”的新项目。按照IT的现代倾向，他决定，这个项目也应该包含聊天。为了实现这一目标，Polycarp在笔记本电脑前花费了几个小时，实现了一个可以处理三种命令的聊天服务器：

将一个人加入聊天（“添加”命令）。

从聊天中删除一个人（“删除”命令）。

向所有正在聊天的人发送消息，包括发送消息的人（“发送”命令）。

现在，Polycarp希望了解处理特定命令集时服务器将产生的传出流量。

Polycarp知道聊天服务器不会为“添加”和“删除”命令发送流量。当处理“发送”命令时，服务器向聊天的每个参与者(当前在线的人)发送l个字节，其中l是消息的长度。

由于Polycarp没有时间，他在寻求帮助来解决这个问题。

## 输入格式

输入文件将包含不超过100个命令，每个命令都在自己的行中。每行不超过100个字符。命令的格式如下：

+<名称>为“添加”命令。
-<名称>为“删除”命令。
<SENDER_NAME>：<MESSAGE_TEXT>为'发送'命令。

<name>(名字)和<sender_name>是拉丁字母和数字的非空序列。<message_text>可以包含字母，数字和空格，但不能以空格开始或结束<message_text>是一个空行。

保证输入数据是正确的，即不会有“添加”命令，如果人用这样的名字已经在聊天，不会有“删除”命令，如果没有人跟在这样的名字聊天等

所有的名字都是区分大小写的。

## 输出格式

输出流量

Translated by @liyifeng

## 样例 #1

### 输入

```
+Mike
Mike:hello
+Kate
+Dmitry
-Dmitry
Kate:hi
-Kate

```

### 输出

```
9

```

## 样例 #2

### 输入

```
+Mike
-Mike
+Mike
Mike:Hi   I am here
-Mike
+Kate
-Kate

```

### 输出

```
14

```



---

---
title: "Ultra-Fast Mathematician"
layout: "post"
diff: 入门
pid: CF61A
tag: ['模拟', '字符串']
---

# Ultra-Fast Mathematician

## 题目描述

Shapur was an extremely gifted student. He was great at everything including Combinatorics, Algebra, Number Theory, Geometry, Calculus, etc. He was not only smart but extraordinarily fast! He could manage to sum $ 10^{18} $ numbers in a single second.

One day in 230 AD Shapur was trying to find out if any one can possibly do calculations faster than him. As a result he made a very great contest and asked every one to come and take part.

In his contest he gave the contestants many different pairs of numbers. Each number is made from digits $ 0 $ or $ 1 $ . The contestants should write a new number corresponding to the given pair of numbers. The rule is simple: The $ i $ -th digit of the answer is $ 1 $ if and only if the $ i $ -th digit of the two given numbers differ. In the other case the $ i $ -th digit of the answer is $ 0 $ .

Shapur made many numbers and first tried his own speed. He saw that he can perform these operations on numbers of length $ ∞ $ (length of a number is number of digits in it) in a glance! He always gives correct answers so he expects the contestants to give correct answers, too. He is a good fellow so he won't give anyone very big numbers and he always gives one person numbers of same length.

Now you are going to take part in Shapur's contest. See if you are faster and more accurate.

## 输入格式

There are two lines in each input. Each of them contains a single number. It is guaranteed that the numbers are made from $ 0 $ and $ 1 $ only and that their length is same. The numbers may start with $ 0 $ . The length of each number doesn't exceed 100.

## 输出格式

Write one line — the corresponding answer. Do not omit the leading $ 0 $ s.

## 样例 #1

### 输入

```
1010100
0100101

```

### 输出

```
1110001

```

## 样例 #2

### 输入

```
000
111

```

### 输出

```
111

```

## 样例 #3

### 输入

```
1110
1010

```

### 输出

```
0100

```

## 样例 #4

### 输入

```
01110
01100

```

### 输出

```
00010

```



---

---
title: "Summer Camp"
layout: "post"
diff: 入门
pid: CF672A
tag: ['字符串', '枚举']
---

# Summer Camp

## 题目描述

Every year, hundreds of people come to summer camps, they learn new algorithms and solve hard problems.

This is your first year at summer camp, and you are asked to solve the following problem. All integers starting with $ 1 $ are written in one line. The prefix of these line is "123456789101112131415...". Your task is to print the $ n $ -th digit of this string (digits are numbered starting with $ 1 $ .

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the position of the digit you need to print.

## 输出格式

Print the $ n $ -th digit of the line.

## 说明/提示

In the first sample the digit at position $ 3 $ is '3', as both integers $ 1 $ and $ 2 $ consist on one digit.

In the second sample, the digit at position $ 11 $ is '0', it belongs to the integer $ 10 $ .

## 样例 #1

### 输入

```
3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
11

```

### 输出

```
0

```



---

---
title: "Irrational problem"
layout: "post"
diff: 入门
pid: CF68A
tag: ['字符串', '枚举']
---

# Irrational problem

## 题目描述

Little Petya was given this problem for homework:

You are given function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/8b7b3ed792043adfb79a0ac45ad9dbf53894718f.png) (here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) represents the operation of taking the remainder). His task is to count the number of integers $ x $ in range $ [a;b] $ with property $ f(x)=x $ .

It is a pity that Petya forgot the order in which the remainders should be taken and wrote down only 4 numbers. Each of 24 possible orders of taking the remainder has equal probability of being chosen. For example, if Petya has numbers 1, 2, 3, 4 then he can take remainders in that order or first take remainder modulo 4, then modulo 2, 3, 1. There also are 22 other permutations of these numbers that represent orders in which remainder can be taken. In this problem 4 numbers wrote down by Petya will be pairwise distinct.

Now it is impossible for Petya to complete the task given by teacher but just for fun he decided to find the number of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/5fea0bb6257453a51324f60c43779399607ff809.png) with property that probability that $ f(x)=x $ is not less than $ 31.4159265352718281828459045% $ . In other words, Petya will pick up the number $ x $ if there exist at least $ 7 $ permutations of numbers $ p_{1},p_{2},p_{3},p_{4} $ , for which $ f(x)=x $ .

## 输入格式

First line of the input will contain 6 integers, separated by spaces: $ p_{1},p_{2},p_{3},p_{4},a,b $ ( $ 1<=p_{1},p_{2},p_{3},p_{4}<=1000,0<=a<=b<=31415 $ ).

It is guaranteed that numbers $ p_{1},p_{2},p_{3},p_{4} $ will be pairwise distinct.

## 输出格式

Output the number of integers in the given range that have the given property.

## 样例 #1

### 输入

```
2 7 1 8 2 8

```

### 输出

```
0

```

## 样例 #2

### 输入

```
20 30 40 50 0 100

```

### 输出

```
20

```

## 样例 #3

### 输入

```
31 41 59 26 17 43

```

### 输出

```
9

```



---

---
title: "King Moves"
layout: "post"
diff: 入门
pid: CF710A
tag: ['模拟', '字符串']
---

# King Moves

## 题目描述

The only king stands on the standard chess board. You are given his position in format "cd", where $ c $ is the column from 'a' to 'h' and $ d $ is the row from '1' to '8'. Find the number of moves permitted for the king.

Check the king's moves here <a>https://en.wikipedia.org/wiki/King\_(chess)</a>.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF710A/c293477e407dd29c222477fd35652e45e6890a3c.png)King moves from the position e4

## 输入格式

The only line contains the king's position in the format "cd", where 'c' is the column from 'a' to 'h' and 'd' is the row from '1' to '8'.

## 输出格式

Print the only integer $ x $ — the number of moves permitted for the king.

## 样例 #1

### 输入

```
e4

```

### 输出

```
8

```



---

---
title: "Way Too Long Words"
layout: "post"
diff: 入门
pid: CF71A
tag: ['模拟', '字符串']
---

# Way Too Long Words

## 题目描述

有时候，像“localization”或“internationalization”这样的词汇如此之长，以至于在一篇文章中多次写下这些词语令人厌烦。

让我们考虑一个词太长，如果它的长度严格超过 10个字符。太长的单词应该用一个特殊的缩写代替。

这个缩写是这样写的：我们写下一个单词的第一个和最后一个字母，并在它们之间写出第一个和最后一个字母之间的字母数。该数字是十进制系统，不包含任何前导零。

因此，“localization”将拼写为“l10n”，而“internationalization”将拼写为”i18n”。

建议您使用缩写来自动更改单词的过程。因为所有太长的单词应该用缩写代替，不太长的单词不应该经历任何改变。

## 输入格式

第一行包含一个整数 n（ 1 <= N <= 100 1 < = n < = 1 0 0）。以下各项 n 行包含一个词。所有的单词由小写拉丁字母组成， 并且拥有从1到100个字符的长度。 _ _

## 输出格式

输出n行。第i行应包含来自输入数据的第 i个字替换的结果。

## 样例 #1

### 输入

```
4
word
localization
internationalization
pneumonoultramicroscopicsilicovolcanoconiosis

```

### 输出

```
word
l10n
i18n
p43s

```



---

---
title: "One-dimensional Japanese Crossword"
layout: "post"
diff: 入门
pid: CF721A
tag: ['模拟', '字符串']
---

# One-dimensional Japanese Crossword

## 题目描述

最近，阿德蒂克发现了日语填字游戏。日语填字游戏是一幅图片，表示为一张桌子大小的a×b正方形，每个方格都是白色或黑色的。
行的左边和列的顶部都有整数，对相应的行或列进行加密。整数的数量表示对应的行或列中有多少组黑色方块，整数本身表示相应组中连续的黑色方块的数量(您可以在维基百科[https://en.wikipedia.org/wiki/Japanese_crossword](https://en.wikipedia.org/wiki/Japanese_crossword)）_纵横字谜中找到更详细的解释)。

阿德蒂克认为日语填字的一般情况太复杂，画了n个正方形(例如1×n1×n)的一行，他想用和日语填字一样的方式加密。

对一行日文横线进行加密的例子。帮助阿德蒂克找到对他画的行进行加密的数字。

## 输入格式

输入的第一行包含单个整数n n(1<=n<=100 1<=n<=100)-行的长度。输入的第二行包含一个由n个字符‘B’或‘W’组成的字符串(‘B’对应于黑色方格，‘W’-与Adtemk绘制的行中的白色方格对应)。

## 输出格式

第一行应该包含一个整数k-加密行的整数，例如行中的黑方格组数。第二行应该包含k个整数，对行进行加密，例如，按照从左到右的顺序对应连续黑色方块的大小。

## 样例 #1

### 输入

```
3
BBW

```

### 输出

```
1
2 
```

## 样例 #2

### 输入

```
5
BWBWB

```

### 输出

```
3
1 1 1 
```

## 样例 #3

### 输入

```
4
WWWW

```

### 输出

```
0

```

## 样例 #4

### 输入

```
4
BBBB

```

### 输出

```
1
4 
```

## 样例 #5

### 输入

```
13
WBBBBWWBWBBBW

```

### 输出

```
3
4 1 3 
```



---

---
title: "Grasshopper And the String"
layout: "post"
diff: 入门
pid: CF733A
tag: ['模拟', '字符串']
---

# Grasshopper And the String

## 题目描述

## 题意描述

一天，有一只蚱蜢正在草地上跳跃，它发现了一张纸，上面有一个字符串。蚱蜢感兴趣的是，它所需要的最小的跳跃能力是多少，才能跳到纸的另一端，它只会跳到元音字母上(为'A','E','I','O','U','Y')。

形式上，蚱蜢从字符串的最左边一个字符的左侧开始跳，目标是跳到最右边一个字符的右侧。蚱蜢的跳跃能力的值就是它跳跃的距离。跳跃能力最小为 $1$ 。

![](https://cdn.luogu.org/upload/vjudge_pic/CF733A/3d6ef82d52bf3bf3e745680bd25bf47489d98417.png)

如图，样例1中蚱蜢所需的最小跳跃能力为4。

## 输入格式

输入的第一行是由大写字母组成的一个字符串，保证该字符串不为空，字符串的长度不超过100。

## 输出格式

输出一个整数 $a$ ，为蚱蜢在这张纸条上所需的最小跳跃能力。

Translated by @dblark

## 样例 #1

### 输入

```
ABABBBACFEYUKOTT

```

### 输出

```
4
```

## 样例 #2

### 输入

```
AAA

```

### 输出

```
1
```



---

---
title: "Mahmoud and Longest Uncommon Subsequence"
layout: "post"
diff: 入门
pid: CF766A
tag: ['字符串']
---

# Mahmoud and Longest Uncommon Subsequence

## 题目描述

While Mahmoud and Ehab were practicing for IOI, they found a problem which name was Longest common subsequence. They solved it, and then Ehab challenged Mahmoud with another problem.

Given two strings $ a $ and $ b $ , find the length of their longest uncommon subsequence, which is the longest string that is a subsequence of one of them and not a subsequence of the other.

A subsequence of some string is a sequence of characters that appears in the same order in the string, The appearances don't have to be consecutive, for example, strings "ac", "bc", "abc" and "a" are subsequences of string "abc" while strings "abbc" and "acb" are not. The empty string is a subsequence of any string. Any string is a subsequence of itself.

## 输入格式

The first line contains string $ a $ , and the second line — string $ b $ . Both of these strings are non-empty and consist of lowercase letters of English alphabet. The length of each string is not bigger than $ 10^{5} $ characters.

## 输出格式

If there's no uncommon subsequence, print "-1". Otherwise print the length of the longest uncommon subsequence of $ a $ and $ b $ .

## 说明/提示

In the first example: you can choose "defgh" from string $ b $ as it is the longest subsequence of string $ b $ that doesn't appear as a subsequence of string $ a $ .

## 样例 #1

### 输入

```
abcd
defgh

```

### 输出

```
5

```

## 样例 #2

### 输入

```
a
a

```

### 输出

```
-1

```



---

---
title: "A Serial Killer"
layout: "post"
diff: 入门
pid: CF776A
tag: ['模拟', '字符串']
---

# A Serial Killer

## 题目描述

我们所深爱的侦探夏洛克，目前正试图抓住一个每天都要杀死一个人的强迫症杀手。通过运用其自身高超的推理能力，夏洛克目前对于凶手挑选下一位受害者的策略了然于心。
当第一天降临，杀手首先从两位潜在的受害者中随机挑选一位脸黑人士进行暗杀，并且每当一位潜在的受害者倒下，都会有另一人取代该受害者之位置，成为新的潜在受害者（幸免于难的那位仍然留在潜在受害者名单上）。可以确定这位杀手每天都会重复这一过程，这样一来，杀手每天都有两个潜在的受害者可供选择进行暗杀。好在夏洛克知道最初的两个潜在受害者是谁，并且，夏洛克知道发生杀人事件的当天的死者是谁以及新的潜在受害者是谁。
显然，好心的你需要每天帮助夏洛克列出每天的的潜在受害者名单，这样一来夏洛克就能从中观察到一些奇妙的规律。

## 输入格式

输入的第一行包含两个名字(每个名字的长度不超过10)，这是最初的两个潜在受害者。下一行包含整数天数n (1<=n<=1000)。
接下来的n行每行包含两个名字(每个名字的长度不超过10)，第一个是当天被谋杀的人（死者），第二个是取代死者成为新的潜在受害者的人。

## 输出格式

输出n+1行，每行输出当天的两位潜在受害者的名字（这两个名字的输出顺序可以随意）

## 说明/提示

如样例1所示，杀手从ross和rachel开始杀起。
第一天结束后，ross不幸被杀而joey接替。
第二天结束后，rachel不幸被杀而phoebe接替。
第三天结束后，phoebe不幸被杀而monica接替。
第四天结束后，monica不幸被杀而chandler接替。

## 样例 #1

### 输入

```
ross rachel
4
ross joey
rachel phoebe
phoebe monica
monica chandler

```

### 输出

```
ross rachel
joey rachel
joey phoebe
joey monica
joey chandler

```

## 样例 #2

### 输入

```
icm codeforces
1
codeforces technex

```

### 输出

```
icm codeforces
icm technex

```



---

---
title: "Fake News (easy)"
layout: "post"
diff: 入门
pid: CF802G
tag: ['模拟', '字符串', '枚举', '队列']
---

# Fake News (easy)

## 题目描述

As it's the first of April, Heidi is suspecting that the news she reads today are fake, and she does not want to look silly in front of all the contestants. She knows that a newspiece is fake if it contains heidi as a subsequence. Help Heidi assess whether the given piece is true, but please be discreet about it...

## 输入格式

The first and only line of input contains a single nonempty string $ s $ of length at most $ 1000 $ composed of lowercase letters (a-z).

## 输出格式

Output YES if the string $ s $ contains heidi as a subsequence and NO otherwise.

## 说明/提示

A string $ s $ contains another string $ p $ as a subsequence if it is possible to delete some characters from $ s $ and obtain $ p $ .

## 样例 #1

### 输入

```
abcheaibcdi

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hiedi

```

### 输出

```
NO
```



---

---
title: "Text Volume"
layout: "post"
diff: 入门
pid: CF837A
tag: ['字符串', '概率论']
---

# Text Volume

## 题目描述

You are given a text of single-space separated words, consisting of small and capital Latin letters.

Volume of the word is number of capital letters in the word. Volume of the text is maximum volume of all words in the text.

Calculate the volume of the given text.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=200 $ ) — length of the text.

The second line contains text of single-space separated words $ s_{1},s_{2},...,s_{i} $ , consisting only of small and capital Latin letters.

## 输出格式

Print one integer number — volume of text.

## 说明/提示

In the first example there is only one word, there are 5 capital letters in it.

In the second example all of the words contain 0 capital letters.

## 样例 #1

### 输入

```
7
NonZERO

```

### 输出

```
5

```

## 样例 #2

### 输入

```
24
this is zero answer text

```

### 输出

```
0

```

## 样例 #3

### 输入

```
24
Harbour Space University

```

### 输出

```
1

```



---

---
title: "Quasi-palindrome"
layout: "post"
diff: 入门
pid: CF863A
tag: ['模拟', '字符串', '概率论']
---

# Quasi-palindrome

## 题目描述

Let quasi-palindromic number be such number that adding some leading zeros (possible none) to it produces a palindromic string.

String $ t $ is called a palindrome, if it reads the same from left to right and from right to left.

For example, numbers $ 131 $ and $ 2010200 $ are quasi-palindromic, they can be transformed to strings " $ 131 $ " and " $ 002010200 $ ", respectively, which are palindromes.

You are given some integer number $ x $ . Check if it's a quasi-palindromic number.

## 输入格式

The first line contains one integer number $ x $ ( $ 1<=x<=10^{9} $ ). This number is given without any leading zeroes.

## 输出格式

Print "YES" if number $ x $ is quasi-palindromic. Otherwise, print "NO" (without quotes).

## 样例 #1

### 输入

```
131

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
320

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
2010200

```

### 输出

```
YES

```



---

---
title: "Polycarp and Letters"
layout: "post"
diff: 入门
pid: CF864B
tag: ['模拟', '字符串', '搜索']
---

# Polycarp and Letters

## 题目描述

Polycarp loves lowercase letters and dislikes uppercase ones. Once he got a string $ s $ consisting only of lowercase and uppercase Latin letters.

Let $ A $ be a set of positions in the string. Let's call it pretty if following conditions are met:

- letters on positions from $ A $ in the string are all distinct and lowercase;
- there are no uppercase letters in the string which are situated between positions from $ A $ (i.e. there is no such $ j $ that $ s[j] $ is an uppercase letter, and $ a_{1}<j<a_{2} $ for some $ a_{1} $ and $ a_{2} $ from $ A $ ).

Write a program that will determine the maximum number of elements in a pretty set of positions.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200 $ ) — length of string $ s $ .

The second line contains a string $ s $ consisting of lowercase and uppercase Latin letters.

## 输出格式

Print maximum number of elements in pretty set of positions for string $ s $ .

## 说明/提示

In the first example the desired positions might be $ 6 $ and $ 8 $ or $ 7 $ and $ 8 $ . Positions $ 6 $ and $ 7 $ contain letters 'a', position $ 8 $ contains letter 'b'. The pair of positions $ 1 $ and $ 8 $ is not suitable because there is an uppercase letter 'B' between these position.

In the second example desired positions can be $ 7 $ , $ 8 $ and $ 11 $ . There are other ways to choose pretty set consisting of three elements.

In the third example the given string $ s $ does not contain any lowercase letters, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
aaaaBaabAbA

```

### 输出

```
2

```

## 样例 #2

### 输入

```
12
zACaAbbaazzC

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3
ABC

```

### 输出

```
0

```



---

---
title: "Between the Offices"
layout: "post"
diff: 入门
pid: CF867A
tag: ['模拟', '字符串']
---

# Between the Offices

## 题目描述

As you may know, MemSQL has American offices in both San Francisco and Seattle. Being a manager in the company, you travel a lot between the two cities, always by plane.

You prefer flying from Seattle to San Francisco than in the other direction, because it's warmer in San Francisco. You are so busy that you don't remember the number of flights you have made in either direction. However, for each of the last $ n $ days you know whether you were in San Francisco office or in Seattle office. You always fly at nights, so you never were at both offices on the same day. Given this information, determine if you flew more times from Seattle to San Francisco during the last $ n $ days, or not.

## 输入格式

The first line of input contains single integer $ n $ ( $ 2<=n<=100 $ ) — the number of days.

The second line contains a string of length $ n $ consisting of only capital 'S' and 'F' letters. If the $ i $ -th letter is 'S', then you were in Seattle office on that day. Otherwise you were in San Francisco. The days are given in chronological order, i.e. today is the last day in this sequence.

## 输出格式

Print "YES" if you flew more times from Seattle to San Francisco, and "NO" otherwise.

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example you were initially at San Francisco, then flew to Seattle, were there for two days and returned to San Francisco. You made one flight in each direction, so the answer is "NO".

In the second example you just flew from Seattle to San Francisco, so the answer is "YES".

In the third example you stayed the whole period in San Francisco, so the answer is "NO".

In the fourth example if you replace 'S' with ones, and 'F' with zeros, you'll get the first few digits of $ π $ in binary representation. Not very useful information though.

## 样例 #1

### 输入

```
4
FSSF

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2
SF

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
10
FFFFFFFFFF

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
10
SSFFSFFSFF

```

### 输出

```
YES

```



---

---
title: "Bark to Unlock"
layout: "post"
diff: 入门
pid: CF868A
tag: ['模拟', '字符串', '枚举']
---

# Bark to Unlock

## 题目描述

As technologies develop, manufacturers are making the process of unlocking a phone as user-friendly as possible. To unlock its new phone, Arkady's pet dog Mu-mu has to bark the password once. The phone represents a password as a string of two lowercase English letters.

Mu-mu's enemy Kashtanka wants to unlock Mu-mu's phone to steal some sensible information, but it can only bark $ n $ distinct words, each of which can be represented as a string of two lowercase English letters. Kashtanka wants to bark several words (not necessarily distinct) one after another to pronounce a string containing the password as a substring. Tell if it's possible to unlock the phone in this way, or not.

## 输入格式

The first line contains two lowercase English letters — the password on the phone.

The second line contains single integer $ n $ ( $ 1<=n<=100 $ ) — the number of words Kashtanka knows.

The next $ n $ lines contain two lowercase English letters each, representing the words Kashtanka knows. The words are guaranteed to be distinct.

## 输出格式

Print "YES" if Kashtanka can bark several words in a line forming a string containing the password, and "NO" otherwise.

You can print each letter in arbitrary case (upper or lower).

## 说明/提示

In the first example the password is "ya", and Kashtanka can bark "oy" and then "ah", and then "ha" to form the string "oyahha" which contains the password. So, the answer is "YES".

In the second example Kashtanka can't produce a string containing password as a substring. Note that it can bark "ht" and then "tp" producing "http", but it doesn't contain the password "hp" as a substring.

In the third example the string "hahahaha" contains "ah" as a substring.

## 样例 #1

### 输入

```
ya
4
ah
oy
to
ha

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
hp
2
ht
tp

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
ah
1
ha

```

### 输出

```
YES

```



---

---
title: "Div. 64"
layout: "post"
diff: 入门
pid: CF887A
tag: ['字符串', '数学', '进制']
---

# Div. 64

## 题目描述

超模$Izabella$ 参加了比赛。她想要给评委留下深刻的印象并且展示她的数学技能。

她的问题如下：对于一个只由$0$ 和$1$ 组成的字符串，判断是否能删掉一些数字，使得得到的二进制数能被$64$ 整除。

## 输入格式

一行，为一个长度不超过$100$ 的$01$ 字符串。

## 输出格式

如果可以，输出$yes$ ，否则输出$no$ 。

感谢@M_sea 提供的翻译

## 样例 #1

### 输入

```
100010001

```

### 输出

```
yes
```

## 样例 #2

### 输入

```
100

```

### 输出

```
no
```



---

---
title: "QAQ"
layout: "post"
diff: 入门
pid: CF894A
tag: ['字符串', '递归', '枚举']
---

# QAQ

## 题目描述

"QAQ" is a word to denote an expression of crying. Imagine "Q" as eyes with tears and "A" as a mouth.

Now Diamond has given Bort a string consisting of only uppercase English letters of length $ n $ . There is a great number of "QAQ" in the string (Diamond is so cute!).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF894A/333c4dadce3b03c143ff500b3cc7457c4f2b76a3.png)illustration by 猫屋 https://twitter.com/nekoyaliuBort wants to know how many subsequences "QAQ" are in the string Diamond has given. Note that the letters "QAQ" don't have to be consecutive, but the order of letters should be exact.

## 输入格式

The only line contains a string of length $ n $ ( $ 1<=n<=100 $ ). It's guaranteed that the string only contains uppercase English letters.

## 输出格式

Print a single integer — the number of subsequences "QAQ" in the string.

## 说明/提示

In the first example there are $ 4 $ subsequences "QAQ": "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN".

## 样例 #1

### 输入

```
QAQAQYSYIOIWIN

```

### 输出

```
4

```

## 样例 #2

### 输入

```
QAQQQZZYNOIWIN

```

### 输出

```
3

```



---

---
title: "Scarborough Fair"
layout: "post"
diff: 入门
pid: CF897A
tag: ['模拟', '字符串']
---

# Scarborough Fair

## 题目描述

Are you going to Scarborough Fair?Parsley, sage, rosemary and thyme.

Remember me to one who lives there.

He once was the true love of mine.





Willem is taking the girl to the highest building in island No.28, however, neither of them knows how to get there.

Willem asks his friend, Grick for directions, Grick helped them, and gave them a task.

Although the girl wants to help, Willem insists on doing it by himself.

Grick gave Willem a string of length $ n $ .

Willem needs to do $ m $ operations, each operation has four parameters $ l,r,c_{1},c_{2} $ , which means that all symbols $ c_{1} $ in range $ [l,r] $ (from $ l $ -th to $ r $ -th, including $ l $ and $ r $ ) are changed into $ c_{2} $ . String is 1-indexed.

Grick wants to know the final string after all the $ m $ operations.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=100) $ .

The second line contains a string $ s $ of length $ n $ , consisting of lowercase English letters.

Each of the next $ m $ lines contains four parameters $ l,r,c_{1},c_{2} $ ( $ 1<=l<=r<=n $ , $ c_{1},c_{2} $ are lowercase English letters), separated by space.

## 输出格式

Output string $ s $ after performing $ m $ operations described above.

## 说明/提示

For the second example:

After the first operation, the string is wxxak.

After the second operation, the string is waaak.

After the third operation, the string is gaaak.

## 样例 #1

### 输入

```
3 1
ioi
1 1 i n

```

### 输出

```
noi
```

## 样例 #2

### 输入

```
5 3
wxhak
3 3 h x
1 5 x a
1 3 w g

```

### 输出

```
gaaak
```



---

---
title: "Rounding"
layout: "post"
diff: 入门
pid: CF898A
tag: ['模拟', '字符串', '枚举']
---

# Rounding

## 题目描述

Vasya has a non-negative integer $ n $ . He wants to round it to nearest integer, which ends up with $ 0 $ . If $ n $ already ends up with $ 0 $ , Vasya considers it already rounded.

For example, if $ n=4722 $ answer is $ 4720 $ . If $ n=5 $ Vasya can round it to $ 0 $ or to $ 10 $ . Both ways are correct.

For given $ n $ find out to which integer will Vasya round it.

## 输入格式

The first line contains single integer $ n $ ( $ 0<=n<=10^{9} $ ) — number that Vasya has.

## 输出格式

Print result of rounding $ n $ . Pay attention that in some cases answer isn't unique. In that case print any correct answer.

## 说明/提示

In the first example $ n=5 $ . Nearest integers, that ends up with zero are $ 0 $ and $ 10 $ . Any of these answers is correct, so you can print $ 0 $ or $ 10 $ .

## 样例 #1

### 输入

```
5

```

### 输出

```
0

```

## 样例 #2

### 输入

```
113

```

### 输出

```
110

```

## 样例 #3

### 输入

```
1000000000

```

### 输出

```
1000000000

```

## 样例 #4

### 输入

```
5432359

```

### 输出

```
5432360

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
title: "Palindromic Supersequence"
layout: "post"
diff: 入门
pid: CF932A
tag: ['字符串']
---

# Palindromic Supersequence

## 题目描述

You are given a string $ A $ . Find a string $ B $ , where $ B $ is a palindrome and $ A $ is a subsequence of $ B $ .

A subsequence of a string is a string that can be derived from it by deleting some (not necessarily consecutive) characters without changing the order of the remaining characters. For example, "cotst" is a subsequence of "contest".

A palindrome is a string that reads the same forward or backward.

The length of string $ B $ should be at most $ 10^{4} $ . It is guaranteed that there always exists such string.

You do not need to find the shortest answer, the only restriction is that the length of string $ B $ should not exceed $ 10^{4} $ .

## 输入格式

First line contains a string $ A $ ( $ 1<=|A|<=10^{3} $ ) consisting of lowercase Latin letters, where $ |A| $ is a length of $ A $ .

## 输出格式

Output single line containing $ B $ consisting of only lowercase Latin letters. You do not need to find the shortest answer, the only restriction is that the length of string $ B $ should not exceed $ 10^{4} $ . If there are many possible $ B $ , print any of them.

## 说明/提示

In the first example, "aba" is a subsequence of "aba" which is a palindrome.

In the second example, "ab" is a subsequence of "aabaa" which is a palindrome.

## 样例 #1

### 输入

```
aba

```

### 输出

```
aba
```

## 样例 #2

### 输入

```
ab

```

### 输出

```
aabaa
```



---

---
title: "Football"
layout: "post"
diff: 入门
pid: CF96A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

Petya loves football very much. One day, as he was watching a football match, he was writing the players' current positions on a piece of paper. To simplify the situation he depicted it as a string consisting of zeroes and ones. A zero corresponds to players of one team; a one corresponds to players of another team. If there are at least $ 7 $ players of some team standing one after another, then the situation is considered dangerous. For example, the situation $ 00100110111111101 $ is dangerous and $ 11110111011101 $ is not. You are given the current situation. Determine whether it is dangerous or not.

## 输入格式

The first input line contains a non-empty string consisting of characters "0" and "1", which represents players. The length of the string does not exceed $ 100 $ characters. There's at least one player from each team present on the field.

## 输出格式

Print "YES" if the situation is dangerous. Otherwise, print "NO".

## 样例 #1

### 输入

```
001001

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
1000000001

```

### 输出

```
YES

```



---

---
title: "Minimum Binary Number"
layout: "post"
diff: 入门
pid: CF976A
tag: ['字符串', '概率论']
---

# Minimum Binary Number

## 题目描述

给定一个二进制数（没有多余前导0），可以对这个二进制数执行两种操作：

1. 交换相邻数位的数字；
2. 用 1 代替 11（例如 110 变成 10）。

输出执行任意操作（或者不操作）后这些二进制数中最小的二进制数。

## 输入格式

第一行，一个数 n，表示这个二进制数的长度；

第二行，一个二进制数 s。

## 输出格式

执行任意操作后最小的二进制数；

## 样例解释

样例一解释：1001->1010->1100->100

样例二解释：不用操作

## 样例 #1

### 输入

```
4
1001

```

### 输出

```
100

```

## 样例 #2

### 输入

```
1
1

```

### 输出

```
1

```



---

---
title: "Wrong Subtraction"
layout: "post"
diff: 入门
pid: CF977A
tag: ['模拟', '字符串', '栈']
---

# Wrong Subtraction

## 题目描述

Little girl Tanya is learning how to decrease a number by one, but she does it wrong with a number consisting of two or more digits. Tanya subtracts one from a number by the following algorithm:

- if the last digit of the number is non-zero, she decreases the number by one;
- if the last digit of the number is zero, she divides the number by 10 (i.e. removes the last digit).

You are given an integer number $ n $ . Tanya will subtract one from it $ k $ times. Your task is to print the result after all $ k $ subtractions.

It is guaranteed that the result will be positive integer number.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ , $ 1 \le k \le 50 $ ) — the number from which Tanya will subtract and the number of subtractions correspondingly.

## 输出格式

Print one integer number — the result of the decreasing $ n $ by one $ k $ times.

It is guaranteed that the result will be positive integer number.

## 说明/提示

The first example corresponds to the following sequence: $ 512 \rightarrow 511 \rightarrow 510 \rightarrow 51 \rightarrow 50 $ .

## 样例 #1

### 输入

```
512 4

```

### 输出

```
50

```

## 样例 #2

### 输入

```
1000000000 9

```

### 输出

```
1

```



---

---
title: "Antipalindrome"
layout: "post"
diff: 入门
pid: CF981A
tag: ['字符串', '枚举']
---

# Antipalindrome

## 题目描述

A string is a palindrome if it reads the same from the left to the right and from the right to the left. For example, the strings "kek", "abacaba", "r" and "papicipap" are palindromes, while the strings "abb" and "iq" are not.

A substring $ s[l \ldots r] $ ( $ 1 \leq l \leq r \leq |s| $ ) of a string $ s = s_{1}s_{2} \ldots s_{|s|} $ is the string $ s_{l}s_{l + 1} \ldots s_{r} $ .

Anna does not like palindromes, so she makes her friends call her Ann. She also changes all the words she reads in a similar way. Namely, each word $ s $ is changed into its longest substring that is not a palindrome. If all the substrings of $ s $ are palindromes, she skips the word at all.

Some time ago Ann read the word $ s $ . What is the word she changed it into?

## 输入格式

The first line contains a non-empty string $ s $ with length at most $ 50 $ characters, containing lowercase English letters only.

## 输出格式

If there is such a substring in $ s $ that is not a palindrome, print the maximum length of such a substring. Otherwise print $ 0 $ .

Note that there can be multiple longest substrings that are not palindromes, but their length is unique.

## 说明/提示

"mew" is not a palindrome, so the longest substring of it that is not a palindrome, is the string "mew" itself. Thus, the answer for the first example is $ 3 $ .

The string "uffuw" is one of the longest non-palindrome substrings (of length $ 5 $ ) of the string "wuffuw", so the answer for the second example is $ 5 $ .

All substrings of the string "qqqqqqqq" consist of equal characters so they are palindromes. This way, there are no non-palindrome substrings. Thus, the answer for the third example is $ 0 $ .

## 样例 #1

### 输入

```
mew

```

### 输出

```
3

```

## 样例 #2

### 输入

```
wuffuw

```

### 输出

```
5

```

## 样例 #3

### 输入

```
qqqqqqqq

```

### 输出

```
0

```



---

---
title: "Infinity Gauntlet"
layout: "post"
diff: 入门
pid: CF987A
tag: ['字符串', '概率论']
---

# Infinity Gauntlet

## 题目描述

# 题目大意
你偷看了Thanos的无尽手套，手套上有6颗无限宝石：
- the **Power** Gem of **purple** color, 紫色的力量宝石
- the **Time** Gem of **green** color, 绿色的时间宝石
- the **Space** Gem of **blue** color, 蓝色的空间宝石
- the **Soul** Gem of **orange** color, 橙色的灵魂宝石
- the **Reality** Gem of **red** color, 红色的现实宝石
- the **Mind** Gem of **yellow** color. 黄色的心灵宝石

现在给出你偷看到的宝石的**颜色**，请你确定缺少了哪些宝石（**名称**）

## 输入格式

第一行一个整数 $n(0≤n≤6)$ ,表示你看到的宝石数量

下面 $n$ 行，每行一个字符串，表示你看到宝石的颜色，所有字符串都是小写的。

## 输出格式

第一行一个整数 $m(0≤m≤6)$ ，表示缺少的宝石的个数

下面 $m$ 行，每行一个宝石的**名字**，顺序随意，**名字首字母要记得大写，其他小写**。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
4
red
purple
yellow
orange

```

### 输出

```
2
Space
Time

```

## 样例 #2

### 输入

```
0

```

### 输出

```
6
Time
Space
Power
Reality
Mind
Soul

```



---

