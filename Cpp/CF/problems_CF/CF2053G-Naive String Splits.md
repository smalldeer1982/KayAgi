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

