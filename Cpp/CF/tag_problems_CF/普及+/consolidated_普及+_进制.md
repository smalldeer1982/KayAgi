---
title: "Vasya and Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF1030E
tag: ['动态规划 DP', '枚举', '进制']
---

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — length of the sequence.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{18} $ ) — the sequence $ a $ .

## 输出格式

Print one integer — the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and the sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
1 2 1 16

```

### 输出

```
4

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
title: "Divisibility Test"
layout: "post"
diff: 普及+/提高
pid: CF1912D
tag: ['数论', '进制']
---

# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 输入格式

There are several tests in the input. The first line of the input contains an integer $ t $ — the number of tests. The next $ t $ lines describe the tests.

Each test consists of a line with two integers $ b $ and $ n $ — the base and the modulo ( $ b, n \ge 2 $ ). The sum of all $ b $ values in the input does not exceed $ 10^6 $ , and the sum of all $ n $ values in the input does not exceed $ 10^6 $ .

## 输出格式

Write $ t $ lines — a line for each test in the input. On a line for a test write a single integer $ 0 $ if the divisibility test for a given $ b $ and $ n $ does not exist. Otherwise, write two integers $ a $ and $ k $ , where $ a $ is the kind of the divisibility test (1, 2, or 3) and $ k $ is the number of digits in a group for the test, such that $ k $ is the lowest among all possible divisiblity tests for the given $ b $ and $ n $ .

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6
```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0
```



---

---
title: "XOR on Segment"
layout: "post"
diff: 普及+/提高
pid: CF242E
tag: ['线段树', '进制', '位运算']
---

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the size of the array. The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{6} $ ) — the original array.

The third line contains integer $ m $ ( $ 1<=m<=5·10^{4} $ ) — the number of operations with the array. The $ i $ -th of the following $ m $ lines first contains an integer $ t_{i} $ ( $ 1<=t_{i}<=2 $ ) — the type of the $ i $ -th query. If $ t_{i}=1 $ , then this is the query of the sum, if $ t_{i}=2 $ , then this is the query to change array elements. If the $ i $ -th operation is of type $ 1 $ , then next follow two integers $ l_{i},r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ). If the $ i $ -th operation is of type $ 2 $ , then next follow three integers $ l_{i},r_{i},x_{i} $ ( $ 1<=l_{i}<=r_{i}<=n,1<=x_{i}<=10^{6} $ ). The numbers on the lines are separated by single spaces.

## 输出格式

For each query of type $ 1 $ print in a single line the sum of numbers on the given segment. Print the answers to the queries in the order in which the queries go in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams, or the %I64d specifier.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3

```

### 输出

```
26
22
0
34
11

```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3

```

### 输出

```
38
28

```



---

---
title: "Vasily the Bear and Sequence"
layout: "post"
diff: 普及+/提高
pid: CF336C
tag: ['贪心', '枚举', '进制']
---

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ). The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{1}&lt;a_{2}&lt;...&lt;a_{n}<=10^{9}) $ .

## 输出格式

In the first line print a single integer $ k $ $ (k&gt;0) $ , showing how many numbers to write out. In the second line print $ k $ integers $ b_{1},b_{2},...,b_{k} $ — the numbers to write out. You are allowed to print numbers $ b_{1},b_{2},...,b_{k} $ in any order, but all of them must be distinct. If there are multiple ways to write out the numbers, choose the one with the maximum number of numbers to write out. If there still are multiple ways, you are allowed to print any of them.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
2
4 5

```

## 样例 #2

### 输入

```
3
1 2 4

```

### 输出

```
1
4

```



---

---
title: "A Lot of Games"
layout: "post"
diff: 普及+/提高
pid: CF455B
tag: ['博弈论', '递归', '进制']
---

# A Lot of Games

## 题目描述

Andrew, Fedor and Alex are inventive guys. Now they invent the game with strings for two players.

Given a group of $ n $ non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game $ k $ times. The player who is the loser of the $ i $ -th game makes the first move in the $ (i+1) $ -th game. Guys decided that the winner of all games is the player who wins the last ( $ k $ -th) game. Andrew and Alex already started the game. Fedor wants to know who wins the game if both players will play optimally. Help him.

## 输入格式

The first line contains two integers, $ n $ and $ k $ ( $ 1<=n<=10^{5} $ ; $ 1<=k<=10^{9} $ ).

Each of the next $ n $ lines contains a single non-empty string from the given group. The total length of all strings from the group doesn't exceed $ 10^{5} $ . Each string of the group consists only of lowercase English letters.

## 输出格式

If the player who moves first wins, print "First", otherwise print "Second" (without the quotes).

## 样例 #1

### 输入

```
2 3
a
b

```

### 输出

```
First

```

## 样例 #2

### 输入

```
3 1
a
b
c

```

### 输出

```
First

```

## 样例 #3

### 输入

```
1 2
ab

```

### 输出

```
Second

```



---

---
title: "Bits"
layout: "post"
diff: 普及+/提高
pid: CF484A
tag: ['贪心', '进制', '位运算']
---

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输入格式

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输出格式

For each query print the answer in a separate line.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10

```

### 输出

```
1
3
7

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
title: "Ability To Convert"
layout: "post"
diff: 普及+/提高
pid: CF758D
tag: ['贪心', '进制']
---

# Ability To Convert

## 题目描述

亚历山大正在学习如何把十进制数字转换成其他进制，但是他不懂英文字母，所以他只是把数值按照十进制数字的方式写出来。这意味着他会用 10 代替英文字母 A。这样，他就会把十进制的 475 转换成十六进制的 11311（475=1·16^2+13·16^1+11·16^0）。亚历山大平静的生活着，直到有一天他试着把这些数字转换回十进制数字。

亚历山大记着他总是用较小的数字工作，所以他需要找到在 n 进制的基础下，用他的转换系统得出数字 k 的最小十进制数。

## 输入格式

第一行是一个正整数 n ( 2<=n<=10^9)，第二行有一个正整数 k ，满足数字 k中包含不超过 60 个数值。第二行整数中的没每一个数字都严格小于 n。

亚历山大保证答案存在且不超过 10^18，数字 k 不含前导 0.

## 输出格式

输出一个数字 x —— 问题的答案。

## 样例 #1

### 输入

```
13
12

```

### 输出

```
12
```

## 样例 #2

### 输入

```
16
11311

```

### 输出

```
475
```

## 样例 #3

### 输入

```
20
999

```

### 输出

```
3789
```

## 样例 #4

### 输入

```
17
2016

```

### 输出

```
594
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
title: "Travelling Salesman and Special Numbers"
layout: "post"
diff: 普及+/提高
pid: CF914C
tag: ['递推', '数位 DP', '进制']
---

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<2^{1000} $ ).

The second line contains integer $ k $ ( $ 0<=k<=1000 $ ).

Note that $ n $ is given in its binary representation without any leading zeros.

## 输出格式

Output a single integer — the number of special numbers not greater than $ n $ , modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
111111011
2

```

### 输出

```
169

```



---

---
title: "A Leapfrog in the Array"
layout: "post"
diff: 普及+/提高
pid: CF949B
tag: ['数学', '树状数组', '进制']
---

# A Leapfrog in the Array

## 题目描述

## 题意:
Dima是一名初级程序员。 在他的工作中，他经常不断地重复以下操作：从数组中删除每个第二个元素。 有一天，他对这个问题的解决方案感到厌倦，他提出了以下华丽的算法。

假设有一长度为2n的数组，最初的数组包含从1到n的n个数字，数字i位于序号为2i - 1的单元格中（序号从1开始编号），并且数组的其他单元格为空。每个步骤你需要选择一个最大序号的非空单元格，并将其中的数字移动到它左边最近的空单元格。一直循环该过程，直到所有n个数字出现在数组的前n个单元格中。例如，如果n = 4，则数组更改如下：
![这里写图片描述](http://codeforces.com/predownloaded/1e/83/1e838f4fb99d933b7259fbfe5b8722990c08d718.png)
您必须编写一个程序，输出在该算法完成后，序号为x（1≤x≤n）的单元格中的数字。

## 输入格式

第一行包含两个整数n和q（1≤n≤1e18，1≤q≤200 000），数组中元素的数量以及查询数量。

接下来的q行包含一个整数xi（1≤xi≤n），xi为算法完成后，第xi个单元格。

## 输出格式

对于q个查询中的每一个，输出一个整数，即相应数组单元格中的值。

## 样例:
```
inputCopy
4 3
2
3
4
outputCopy
3
2
4
```
```
inputCopy
13 4
10
5
4
8
outputCopy
13
3
8
9
```
翻译提供者：xjdx

## 样例 #1

### 输入

```
4 3
2
3
4

```

### 输出

```
3
2
4

```

## 样例 #2

### 输入

```
13 4
10
5
4
8

```

### 输出

```
13
3
8
9

```



---

