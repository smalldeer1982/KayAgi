# Short Program

## 题目描述

Petya learned a new programming language CALPAS. A program in this language always takes one non-negative integer and returns one non-negative integer as well.

In the language, there are only three commands: apply a bitwise operation AND, OR or XOR with a given constant to the current integer. A program can contain an arbitrary sequence of these operations with arbitrary constants from $ 0 $ to $ 1023 $ . When the program is run, all operations are applied (in the given order) to the argument and in the end the result integer is returned.

Petya wrote a program in this language, but it turned out to be too long. Write a program in CALPAS that does the same thing as the Petya's program, and consists of no more than $ 5 $ lines. Your program should return the same integer as Petya's program for all arguments from $ 0 $ to $ 1023 $ .

## 说明/提示

You can read about bitwise operations in [https://en.wikipedia.org/wiki/Bitwise\_operation](https://en.wikipedia.org/wiki/Bitwise_operation).

Second sample:

Let $ x $ be an input of the Petya's program. It's output is $ ((x&amp;1)&amp;3)&amp;5=x&amp;(1&amp;3&amp;5)=x&amp;1 $ . So these two programs always give the same outputs.

## 样例 #1

### 输入

```
3
| 3
^ 2
| 1
```

### 输出

```
2
| 3
^ 2
```

## 样例 #2

### 输入

```
3
& 1
& 3
& 5
```

### 输出

```
1
& 1
```

## 样例 #3

### 输入

```
3
^ 1
^ 2
^ 3
```

### 输出

```
0
```

# 题解

## 作者：james1BadCreeper (赞：1)

按照每一位去考虑，每一位只有三种情况：

1. 最终变成 $1$；
2. 最终变成 $0$；
3. 最终变成与原来相反的东西。

那么每一位都用一个长度为 $2$ 的二进制数表示，第一位表示是否和原来的值有关，第二位表示变成的值。模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n; 
int v[10]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n; 
    for (int i = 0; i < 10; ++i) v[i] = 2;
    while (n--) {
        char c[2]; int t; cin >> c >> t; 

        if (c[0] == '|') for (int i = 0; i < 10; ++i) if (t >> i & 1) v[i] = 1; 
        if (c[0] == '&') for (int i = 0; i < 10; ++i) if (!(t >> i & 1)) v[i] = 0; 
        if (c[0] == '^') for (int i = 0; i < 10; ++i) if (t >> i & 1) v[i] ^= 1; 
    }

    int v1 = 0, v2 = 0, v3 = 0;
    for (int i = 0; i < 10; ++i) {
        if (v[i] == 0) v1 |= 1 << i;
        if (v[i] == 1) v2 |= 1 << i;
        if (v[i] == 3) v3 |= 1 << i;
    }
    printf("3\n");
    printf("& %d\n", 1023 ^ v1);
    printf("| %d\n", v2);
    printf("^ %d\n", v3);
    return 0;
}
```

---

## 作者：denominator (赞：1)

# 「CF878A Short Program」题解

以前做的 constructive 没写题解，看没有人就补一下吧。

## Part \#1 三行

首先考虑每一行代码都是位运算，对于每一位分开讨论。

不难发现，每一位的变化情况只有三种：

1. 无论这一位原来是 $0$ 还是 $1$，经过程序始终为 $0$；
2. 无论这一位原来是 $0$ 还是 $1$，经过程序始终为 $1$；
3. 无论这一位原来是 $0$ 还是 $1$，经过程序始终反转（$0$ 变 $1$，$1$ 变 $0$）；

所以，我们对于输出的的第 $i$ 个二进制位设置一个 $c_i$，$r_i$ 与 $s_i$，表示该位是否更改，是否翻转，设为 $0$（$s_i=0$） 还是设为 $1$（$s_i=1$）。当一个操作的参数第 $i$ 位为 $1$：

1. 若此操作为 &amp;，那么 $c_i\gets1$，$r_i\gets0$，$s_i\gets1$；
2. 若此操作为 |，那么 $c_i\gets1$，$r_i\gets0$，$s_i\gets0$；
3. 否则：
	- 若 $c_i=0$，则 $c_i\gets1$，$r_i\gets1$；
    - 若 $r_i=0$，则 $c_i\gets0$，$r_i\gets0$
    - 否则 $s_i\gets\lnot s_i$（即将 $s_i$ 的值 $0$ 变 $1$，$1$ 变 $0$）
    
这样子我们用 | 操作将二进制位设 $0$，&amp; 操作将二进制位设 $0$，^ 操作将二进制位反转，这样可以三行解决。

代码不难写，但是 tutorial 给了一个 bonus：两行解决问题。

## Part \#2 两行

**优化思路 1** 其实我们的设 $0$ 非常浪费，可以通过设 $1$ 后反转，那么我们直接将设 $1$ 合到 | 操作内，反转合到 ^ 操作，这样只需两行。注意顺序。

**优化思路 2** CF 评论区的大佬给出了一个强强的做法：

设 $S_0$ 为输入 $0$ 时的结果，$S_{1\ 023}$ 为输入 $1\ 023$ 时的结果，那么即可进行下面操作：&amp; $(S_0\oplus S_{1\ 023})$，^ $S_0$，其中 $\oplus$ 表示异或。

证明？同样是对于每一位考虑：

- 若这一位被设为 $1$，那么 $S_0$ 与 $S_{1\ 023}$（即当这一位为 $0$ 或 $1$ 时）在这一位都为 $1$，这样 `& 0` 使得它变为 $0$，再 `^ 1` 反转过来。同理对于设为 $0$ 的情况，只是通过 `^ 0` 不让其反转。
- 若这一位未被改动，那么通过 `& 1` 后不变，通过 `^ 0` 后依然不变。同样的，若这一位被反转，那么只需通过 `^ 1` 将其反转。
- 找规律发现就是上述结论。

所以本题代码非常短，相信所有人都写得出来，就不贴了。

---

