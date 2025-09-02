---
title: "Palindromes Coloring"
layout: "post"
diff: 普及/提高-
pid: CF1624D
tag: []
---

# Palindromes Coloring

## 题目描述

You have a string $ s $ consisting of lowercase Latin alphabet letters.

You can color some letters in colors from $ 1 $ to $ k $ . It is not necessary to paint all the letters. But for each color, there must be a letter painted in that color.

Then you can swap any two symbols painted in the same color as many times as you want.

After that, $ k $ strings will be created, $ i $ -th of them will contain all the characters colored in the color $ i $ , written in the order of their sequence in the string $ s $ .

Your task is to color the characters of the string so that all the resulting $ k $ strings are palindromes, and the length of the shortest of these $ k $ strings is as large as possible.

Read the note for the first test case of the example if you need a clarification.

Recall that a string is a palindrome if it reads the same way both from left to right and from right to left. For example, the strings abacaba, cccc, z and dxd are palindromes, but the strings abab and aaabaa — are not.

## 输入格式

The first line of input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input data sets in the test.

The descriptions of the input data sets follow.

The first line of the description of each input data set contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ) — the length of the string and the number of colors in which its letters can be painted. The second line of the description of each input data set contains a string $ s $ of length $ n $ consisting of lowercase letters of the Latin alphabet.

It is guaranteed that the sum of n over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each set of input data, output a single integer — the maximum length of the shortest palindrome string that can be obtained.

## 说明/提示

- In the first test case, $ s $ ="bxyaxzay", $ k=2 $ . We use indices in the string from $ 1 $ to $ 8 $ . The following coloring will work: $ \mathtt{\mathbf{\color{red}{b}\color{blue}{xy}\color{red}{a}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ (the letter z remained uncolored). After painting:
  - swap two red characters (with the indices $ 1 $ and $ 4 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ ;
  - swap two blue characters (with the indices $ 5 $ and $ 8 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{y}z\color{red}{a}\color{blue}{x}}} $ .
  
  Now, for each of the two colors we write out the corresponding characters from left to right, we get two strings $ \mathtt{\mathbf{\color{red}{aba}}} $ and $ \mathtt{\mathbf{\color{blue}{xyyx}}} $ . Both of them are palindromes, the length of the shortest is $ 3 $ . It can be shown that the greatest length of the shortest palindrome cannot be achieved.
- In the second set of input data, the following coloring is suitable: $ [1, 1, 2, 2, 3, 3] $ . There is no need to swap characters. Both received strings are equal to aa, they are palindromes and their length is $ 2 $ .
- In the third set of input data, you can color any character and take it into a string.
- In the fourth set of input data, you can color the $ i $ th character in the color $ i $ .
- In the fifth set of input data can be colored in each of the colors of one character.
- In the sixth set of input data, the following coloring is suitable: $ [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0] $ . Rearrange the characters so as to get the palindromes abcba and acbca.

## 样例 #1

### 输入

```
10
8 2
bxyaxzay
6 3
aaaaaa
6 1
abcdef
6 6
abcdef
3 2
dxd
11 2
abcabcabcac
6 6
sipkic
7 2
eatoohd
3 1
llw
6 2
bfvfbv
```

### 输出

```
3
2
1
1
1
5
1
1
3
3
```

