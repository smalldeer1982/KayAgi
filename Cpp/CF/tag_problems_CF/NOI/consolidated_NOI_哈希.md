---
title: "AmShZ Wins a Bet"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1610G
tag: ['倍增', '哈希 hashing']
---

# AmShZ Wins a Bet

## 题目描述

Right before the UEFA Euro 2020, AmShZ and Safar placed bets on who'd be the champion, AmShZ betting on Italy, and Safar betting on France.

Of course, AmShZ won. Hence, Safar gave him a bracket sequence $ S $ . Note that a bracket sequence is a string made of '(' and ')' characters.

AmShZ can perform the following operation any number of times:

- First, he cuts his string $ S $ into three (possibly empty) contiguous substrings $ A, B $ and $ C $ . Then, he glues them back by using a '(' and a ')' characters, resulting in a new string $ S $ = $ A $ + "(" + $ B $ + ")" + $ C $ .For example, if $ S $ = "))((" and AmShZ cuts it into $ A $ = "", $ B $ = "))", and $ C $ = "((", He will obtain $ S $ = "()))((" as a new string.

After performing some (possibly none) operations, AmShZ gives his string to Keshi and asks him to find the initial string. Of course, Keshi might be able to come up with more than one possible initial string. Keshi is interested in finding the lexicographically smallest possible initial string.

Your task is to help Keshi in achieving his goal.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The only line of input contains a single string $ S $ — the string after the operations $ (1\le |S|\le 3 \cdot 10^5) $ .

It is guaranteed that the first character of $ S $ is ')'.

## 输出格式

Print the lexicographically smallest possible initial string before operations.

## 说明/提示

In the first sample, you can transform ")((())))" into ")(()(())))" by splitting it into ")(", empty string, and "(())))". It can be shown that this is the lexicographically smallest possible initial string

## 样例 #1

### 输入

```
)(()(())))
```

### 输出

```
)((())))
```



---

---
title: "Fortnite"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1994H
tag: ['哈希 hashing', '进制', 'Ad-hoc']
---

# Fortnite

## 题目描述

This is an interactive problem!

Timofey is writing a competition called Capture the Flag (or CTF for short). He has one task left, which involves hacking a security system. The entire system is based on polynomial hashes $ ^{\text{∗}} $ .

Timofey can input a string consisting of lowercase Latin letters into the system, and the system will return its polynomial hash. To hack the system, Timofey needs to find the polynomial hash parameters ( $ p $ and $ m $ ) that the system uses.

Timofey doesn't have much time left, so he will only be able to make $ 3 $ queries. Help him solve the task.

 $ ^{\text{∗}} $ The polynomial hash of a string $ s $ , consisting of lowercase Latin letters of length $ n $ , based on $ p $ and modulo $ m $ is $ (\mathrm{ord}(s_1) \cdot p ^ 0 + \mathrm{ord}(s_2) \cdot p ^ 1 + \mathrm{ord}(s_3) \cdot p ^ 2 + \ldots + \mathrm{ord}(s_n) \cdot p ^ {n - 1}) \bmod m $ . Where $ s_i $ denotes the $ i $ -th character of the string $ s $ , $ \mathrm{ord}(\mathrm{chr}) $ denotes the ordinal number of the character $ \mathrm{chr} $ in the English alphabet, and $ x \bmod m $ is the remainder of $ x $ when divided by $ m $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

It is guaranteed that the $ p $ and $ m $ used by the system satisfy the conditions: $ 26 < p \leq 50 $ and $ p + 1 < m \leq 2 \cdot 10^9 $ .

## 输出格式

To make a query to the system, output ? $ s $ , where $ s $ is a string of no more than $ 50 $ characters in length, the hash of which you want to know. In response to this query, you will receive the polynomial hash of the string $ s $ .

To output the answer, output ! $ p $ $ m $ , where $ p $ is the base of the hash, and $ m $ is the modulus. After that, immediately proceed to the next test case.

You have to make not more than $ 3 $ queries ?, otherwise you will get verdict Wrong Answer.

After outputting a query, do not forget to output a newline and flush the output buffer. Otherwise, you will receive the verdict Idleness limit exceeded. To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

## 说明/提示

Answer for the first query is $ (ord(a) \cdot 31^0 + ord(a) \cdot 31^1) \mod 59 = (1 + 1 \cdot 31) \mod 59 = 32 $ .

Answer for the second query is $ (ord(y) \cdot 31^0 + ord(b) \cdot 31^1) \mod 59 = (25 + 2 \cdot 31) \mod 59 = 28 $ .

## 样例 #1

### 输入

```
1

32

28
```

### 输出

```
? aa

? yb

! 31 59
```



---

---
title: "Naive String Splits"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2053G
tag: ['贪心', '哈希 hashing']
---

# Naive String Splits

## 题目描述

Cocoly 有一个长度为 $m$ 的字符串 $t$，全部由小写字母组成。他希望可以把这个字符串拆分成多个部分。若存在一个字符串序列 $a_1, a_2, \ldots, a_k$，满足：

- $t = a_1 + a_2 + \ldots + a_k$，其中 $+$ 表示字符串的连接。
- 对于每个 $1 \leq i \leq k$，至少满足 $a_i = x$ 或 $a_i = y$。

那么就称字符串对 $(x, y)$ 是美丽的。

Cocoly 还有一个长度为 $n$ 的字符串 $s$，同样由小写字母构成。现在，对于每一个位置 $1 \leq i < n$，Cocoly 需要你来判断字符串对 $(s_1s_2 \ldots s_i, \, s_{i+1}s_{i+2} \ldots s_n)$ 是否美丽。

注意：由于数据量较大，输入输出需要进行优化，例如在 C++ 中，可以在 `main` 函数的开头加入以下代码，以提高效率：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
}
```

## 输入格式

输入包含多个测试用例。第一行包含一个整数 $T$（$1 \leq T \leq 10^5$），表示测试用例的数量。接下来是每个测试用例的具体描述。

每个测试用例的第一行是两个整数 $n$ 和 $m$（$2 \leq n \leq m \leq 5 \times 10^6$），分别表示字符串 $s$ 和 $t$ 的长度。

接下来的两行中，第二行是长度为 $n$ 的字符串 $s$，第三行是长度为 $m$ 的字符串 $t$，这两个字符串均由小写字母组成。

保证所有测试用例中 $m$ 的总和不超过 $10^7$。

## 输出格式

对于每个测试用例，输出一个长度为 $n-1$ 的二进制字符串 $r$：每个 $1 \leq i < n$，如果第 $i$ 个字符串对是美丽的则 $r_i=\texttt{1}$，否则 $r_i=\texttt{0}$。输出时不要每两位之间加空格。

## 说明/提示

举例来说，第一个测试用例中，$s = \tt aba$，$t = \tt ababa$。

- 当 $i = 1$：Cocoly 可以将 $t$ 分割为 $\texttt{a} + \texttt{ba} + \texttt{ba}$，因此字符串对 $(\texttt{a}, \texttt{ba})$ 是美丽的。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{ab} + \texttt{ab} + \texttt{a}$，因此字符串对 $(\texttt{ab}, \texttt{a})$ 也是美丽的。

在第二个测试用例中，$s = \tt czzz$，$t = \tt czzzzzczzz$。

- 当 $i = 1$：可以证明无法通过字符串 $\texttt{c}$ 和 $\texttt{zzz}$ 将 $t$ 进行美丽的分割。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{cz} + \texttt{zz} + \texttt{zz} + \texttt{cz} + \texttt{zz}$。
- 当 $i = 3$：Cocoly 可以将 $t$ 分割为 $\texttt{czz} + \texttt{z} + \texttt{z} + \texttt{z} + \texttt{czz} + \texttt{z}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 5
aba
ababa
4 10
czzz
czzzzzczzz
5 14
dream
dredreamamamam
5 18
tcccc
tcctccccctccctcccc
7 11
abababc
abababababc
7 26
aaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaa
19 29
bbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbbbbbbbbb
```

### 输出

```
11
011
0010
0000
010100
111111
110010001100010011
```



---

---
title: "The Classic Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF464E
tag: ['最短路', '可持久化线段树', '哈希 hashing']
---

# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 输入格式

The first line of the input contains two space-separated integers — $ n $ and $ m $ ( $ 1<=n<=10^{5} $ ; $ 0<=m<=10^{5} $ ).

Next $ m $ lines contain the description of the graph edges. The $ i $ -th line contains three space-separated integers — $ u_{i} $ , $ v_{i} $ , $ x_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ 0<=x_{i}<=10^{5} $ ). That means that vertices with numbers $ u_{i} $ and $ v_{i} $ are connected by edge of length $ 2^{x_{i}} $ (2 to the power of $ x_{i} $ ).

The last line contains two space-separated integers — the numbers of vertices $ s $ and $ t $ .

The vertices are numbered from $ 1 $ to $ n $ . The graph contains no multiple edges and self-loops.

## 输出格式

In the first line print the remainder after dividing the length of the shortest path by $ 1000000007 (10^{9}+7) $ if the path exists, and -1 if the path doesn't exist.

If the path exists print in the second line integer $ k $ — the number of vertices in the shortest path from vertex $ s $ to vertex $ t $ ; in the third line print $ k $ space-separated integers — the vertices of the shortest path in the visiting order. The first vertex should be vertex $ s $ , the last vertex should be vertex $ t $ . If there are multiple shortest paths, print any of them.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4

```

### 输出

```
3
4
1 2 3 4 

```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4

```

### 输出

```
112
4
1 2 3 4 

```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4

```

### 输出

```
-1

```



---

