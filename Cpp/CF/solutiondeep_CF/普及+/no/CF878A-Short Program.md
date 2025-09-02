# 题目信息

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

# AI分析结果

### 题目内容
# 简短程序

## 题目描述
Petya 学习了一种新的编程语言 CALPAS。该语言中的程序始终接受一个非负整数，并返回一个非负整数。

在该语言中，只有三个命令：对当前整数应用按位与（AND）、按位或（OR）或按位异或（XOR）操作，并与给定的常量进行运算。一个程序可以包含任意顺序的这些操作，且常量取值范围为 $0$ 到 $1023$。当程序运行时，所有操作按照给定顺序应用于参数，最后返回结果整数。

Petya 编写了一个该语言的程序，但结果发现它太长了。请编写一个 CALPAS 程序，其功能与 Petya 的程序相同，且行数不超过 $5$ 行。对于所有 $0$ 到 $1023$ 的参数，你的程序应返回与 Petya 的程序相同的整数。

## 说明/提示
你可以在 [https://en.wikipedia.org/wiki/Bitwise_operation](https://en.wikipedia.org/wiki/Bitwise_operation) 阅读有关按位运算的内容。

第二个样例：

设 $x$ 是 Petya 程序的输入。其输出为 $((x\&1)\&3)\&5 = x\&(1\&3\&5)=x\&1$。所以这两个程序总是给出相同的输出。

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

### 算法分类
构造

### 综合分析与结论
两题解思路核心都是对二进制位分别分析。james1BadCreeper 题解通过模拟每一位最终状态，用三个常量分别表示设为0、设为1、反转的情况，最后用三个操作实现功能。denominator 题解先分析每一位变化的三种情况，得出三行解决的方法，又提出两种优化思路实现两行解决。从优化程度和思路清晰度看，denominator 题解更优。

### 所选的题解
- **denominator（5星）**
    - **关键亮点**：不仅给出三行解决问题的常规思路，还提出两种优化思路实现两行解决，对问题分析深入且全面。
    - **核心代码实现思想**：
        - **三行解法**：对每一位设置标志位表示是否更改、是否翻转、设为0还是1 ，根据不同操作更新标志位，最后用 | 操作设0 ，& 操作设1 ，^ 操作反转。
        - **两行解法优化思路1**：将设1操作合到 | 操作内，反转操作合到 ^ 操作内。
        - **两行解法优化思路2**：通过计算输入0和1023时的结果，利用 & 和 ^ 操作实现功能。
```cpp
// 伪代码示意三行解法
// 假设已有对每一位的处理结果，分别用v1设0，v2设1，v3反转
printf("3\n");
printf("& %d\n", 1023 ^ v1);
printf("| %d\n", v2);
printf("^ %d\n", v3);
```
```cpp
// 伪代码示意两行解法优化思路2
// 假设S0为输入0的结果，S1023为输入1023的结果
printf("2\n");
printf("& %d\n", S0 ^ S1023);
printf("^ %d\n", S0);
```
- **james1BadCreeper（4星）**
    - **关键亮点**：思路清晰，通过对每一位最终状态的模拟，用简洁的代码实现功能。
    - **核心代码实现思想**：用长度为2的二进制数表示每一位状态，根据不同操作更新状态，最后根据状态得出三个常量用于实现功能。
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

### 最优关键思路或技巧
对二进制位分别分析，利用按位运算的性质，通过设置标志位或模拟每一位状态来构造简洁的程序。

### 拓展
同类型题常围绕按位运算的性质与构造展开，类似套路是对二进制位分别考虑其变化情况，通过不同按位操作组合实现目标。

### 洛谷题目推荐
- [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：涉及位运算相关的构造问题。
- [P1876 开灯](https://www.luogu.com.cn/problem/P1876)：通过位运算性质解决实际问题。
- [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：利用位运算优化枚举过程。 

---
处理用时：45.25秒