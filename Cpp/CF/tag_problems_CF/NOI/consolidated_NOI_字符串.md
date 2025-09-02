---
title: "Speckled Band"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1043G
tag: ['字符串']
---

# Speckled Band

## 题目描述

Ildar took a band (a thin strip of cloth) and colored it. Formally, the band has $ n $ cells, each of them is colored into one of $ 26 $ colors, so we can denote each color with one of the lowercase letters of English alphabet.

Ildar decided to take some segment of the band $ [l, r] $ ( $ 1 \le l \le r \le n $ ) he likes and cut it from the band. So he will create a new band that can be represented as a string $ t = s_l s_{l+1} \ldots s_r $ .

After that Ildar will play the following game: he cuts the band $ t $ into some new bands and counts the number of different bands among them. Formally, Ildar chooses $ 1 \le k \le |t| $ indexes $ 1 \le i_1 < i_2 < \ldots < i_k = |t| $ and cuts $ t $ to $ k $ bands-strings $ t_1 t_2 \ldots t_{i_1}, t_{i_1 + 1} \ldots t_{i_2}, \ldots, {t_{i_{k-1} + 1}} \ldots t_{i_k} $ and counts the number of different bands among them. He wants to know the minimal possible number of different bands he can get under the constraint that at least one band repeats at least two times. The result of the game is this number. If it is impossible to cut $ t $ in such a way, the result of the game is -1.

Unfortunately Ildar hasn't yet decided which segment he likes, but he has $ q $ segments-candidates $ [l_1, r_1] $ , $ [l_2, r_2] $ , ..., $ [l_q, r_q] $ . Your task is to calculate the result of the game for each of them.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — the length of the band Ildar has.

The second line contains a string $ s $ consisting of $ n $ lowercase English letters — the band Ildar has.

The third line contains a single integer $ q $ ( $ 1 \le q \le 200\,000 $ ) — the number of segments Ildar has chosen as candidates.

Each of the next $ q $ lines contains two integer integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) denoting the ends of the $ i $ -th segment.

## 输出格式

Output $ q $ lines, where the $ i $ -th of them should contain the result of the game on the segment $ [l_i, r_i] $ .

## 说明/提示

Consider the first example.

If Ildar chooses the segment $ [1, 6] $ , he cuts a string $ t = abcabc $ . If he cuts $ t $ into two bands $ abc $ and $ abc $ , the band $ abc $ repeats two times and the number of different tapes is $ 1 $ . So, the result of this game is $ 1 $ .

If Ildar chooses the segment $ [4, 7] $ , he cuts a string $ t = abcd $ . It is impossible to cut this band in such a way that there is at least one band repeating at least two times. So, the result of this game is $ -1 $ .

If Ildar chooses the segment $ [3, 6] $ , he cuts a string $ t = cabc $ . If he cuts $ t $ into three bands $ c $ , $ ab $ and $ c $ , the band $ c $ repeats two times and the number of different bands is $ 2 $ . So, the result of this game is $ 2 $ .

## 样例 #1

### 输入

```
9
abcabcdce
7
1 6
4 7
5 9
6 9
1 9
3 6
4 4

```

### 输出

```
1
-1
4
3
2
2
-1

```



---

---
title: "Pumping Lemma"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1909G
tag: ['字符串']
---

# Pumping Lemma

## 题目描述

有两个只含小写字母的字符串 $s$ 和 $t$，长度分别为 $n$ 和 $m$。

请计算满足下列要求的字符串三元组 $(x,y,z)$ 有几个：

- $s=x+y+z$ （$+$ 代表连接）；

- $t = x+\underbrace{ y+\dots+y }_{k \text{ 个}} + z$，其中 $k$ 为整数。

## 输入格式

第一行两个整数 $n,m(1 \le n < m \le 10^7)$。

第二行一个字符串 $s$。

第三行一个字符串 $t$。

## 输出格式

一行，一个整数表示答案。

## 样例 #1

### 输入

```
4 8
abcd
abcbcbcd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 5
aaa
aaaaa
```

### 输出

```
5
```

## 样例 #3

### 输入

```
12 16
abbababacaab
abbababababacaab
```

### 输出

```
8
```



---

---
title: "Mr. Kitayuta's Gift"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF506E
tag: ['字符串', '矩阵乘法']
---

# Mr. Kitayuta's Gift

## 题目描述

Mr. Kitayuta has kindly given you a string $ s $ consisting of lowercase English letters. You are asked to insert exactly $ n $ lowercase English letters into $ s $ to make it a palindrome. (A palindrome is a string that reads the same forward and backward. For example, "noon", "testset" and "a" are all palindromes, while "test" and "kitayuta" are not.) You can choose any $ n $ lowercase English letters, and insert each of them to any position of $ s $ , possibly to the beginning or the end of $ s $ . You have to insert exactly $ n $ letters even if it is possible to turn $ s $ into a palindrome by inserting less than $ n $ letters.

Find the number of the palindromes that can be obtained in this way, modulo $ 10007 $ .

## 输入格式

The first line contains a string $ s $ ( $ 1<=|s|<=200 $ ). Each character in $ s $ is a lowercase English letter.

The second line contains an integer $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Print the number of the palindromes that can be obtained, modulo $ 10007 $ .

## 说明/提示

For the first sample, you can obtain the palindrome "reviver" by inserting 'r' to the end of "revive".

For the second sample, the following 28 palindromes can be obtained: "adada", "adbda", ..., "adzda", "dadad" and "ddadd".

## 样例 #1

### 输入

```
revive
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
add
2

```

### 输出

```
28

```



---

