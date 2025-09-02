# 题目信息

# Powerful Ksenia

## 题目描述

Ksenia has an array $ a $ consisting of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

In one operation she can do the following:

- choose three distinct indices $ i $ , $ j $ , $ k $ , and then
- change all of $ a_i, a_j, a_k $ to $ a_i \oplus a_j \oplus a_k $ simultaneously, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

She wants to make all $ a_i $ equal in at most $ n $ operations, or to determine that it is impossible to do so. She wouldn't ask for your help, but please, help her!

## 说明/提示

In the first example, the array becomes $ [4 \oplus 1 \oplus 7, 2, 4 \oplus 1 \oplus 7, 4 \oplus 1 \oplus 7, 2] = [2, 2, 2, 2, 2] $ .

## 样例 #1

### 输入

```
5
4 2 1 7 2```

### 输出

```
YES
1
1 3 4```

## 样例 #2

### 输入

```
4
10 4 49 22```

### 输出

```
NO```

# AI分析结果

### 题目翻译
Ksenia 有一个由 $n$ 个正整数 $a_1, a_2, \ldots, a_n$ 组成的数组 $a$。

在一次操作中，她可以进行以下操作：
- 选择三个不同的索引 $i$、$j$、$k$。
- 同时将 $a_i$、$a_j$、$a_k$ 都变为 $a_i \oplus a_j \oplus a_k$，其中 $\oplus$ 表示按位异或运算。

她希望在最多 $n$ 次操作内使所有的 $a_i$ 相等，或者确定这是不可能的。请帮助她！

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕数组元素通过异或操作变得相等的构造方法展开，核心在于分奇偶情况讨论。
- **思路对比**：大部分题解先分析小情况，如 3、4、5 个数的情形，再推广到一般的奇偶情况。对于奇数情况，通过一系列操作将数组变为两两相等的小段，再用最后一个数把前面的小段推平；对于偶数情况，先判断异或和是否为 0，若为 0 则对前 $n - 1$ 个数用奇数的方法构造。
- **算法要点**：利用异或的性质，如相同数异或为 0，以及一次操作不改变序列的异或和。
- **解决难点**：偶数情况需要判断异或和是否为 0 来确定是否有解，这是一个关键的判断点。

### 所选题解
- **duyi（4星）**
    - **关键亮点**：思路清晰，先分别阐述奇数和偶数情况的构造方法，再总结解题技巧，即观察操作不变的量。
    - **个人心得**：提到 $n$ 是奇数的情况手玩一会能看出来，$n$ 是偶数时要观察操作不变的量，找到必要条件并思考其充分性。
- **Purslane（4星）**
    - **关键亮点**：从最小情况开始分析，逐步类比出大情况，提供了做构造题的好方法，且对操作次数有详细分析。
    - **个人心得**：强调从小情况起类比出大情况的解题思路，以及异或性质对解题的帮助。
- **do_while_true（4星）**
    - **关键亮点**：对操作的作用分析清晰，代码实现简洁，且对时间复杂度有说明。
    - **个人心得**：无。

### 重点代码
```cpp
// do_while_true的代码
#include<iostream>
#include<cstdio>
inline int read() {
    int r = 0; bool w = 0; char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') w = 1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        r = (r << 3) + (r << 1) + (ch ^ 48);
        ch = getchar();
    }
    return w ? ~r + 1 : r;
}
const int N = 100010; 
int n, a[N], sum;
signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), sum ^= a[i];
    if(!(n&1)) {
        --n;
        if(sum) {
            puts("NO");
            return 0;
        } 
    }
    puts("YES");
    printf("%d\n", n-2);
    for(int i = 1; i + 2 <= n; i += 2) printf("%d %d %d\n", i, i+1, i+2);
    for(int i = 1; i + 1 <= n - 3; i += 2) printf("%d %d %d\n", i, i+1, n);
    return 0;
}
```
**核心实现思想**：先读取数组并计算异或和，若 $n$ 为偶数且异或和不为 0 则输出 `NO`，否则输出 `YES` 并按奇数情况的构造方法输出操作步骤。

### 关键思路或技巧
- 观察操作过程中的不变量，如本题中的异或和，以此作为判断是否有解的依据。
- 从简单情况入手，逐步推导复杂情况，通过类比找到构造方法。

### 拓展思路
同类型的构造题通常需要观察操作的性质和不变量，利用数学性质进行构造。可以尝试解决一些涉及位运算和构造的题目，通过分析操作对数据的影响来找到解题方法。

### 推荐题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：涉及贪心和构造的思想。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：需要对数字进行构造和排序。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心和构造的结合。

---
处理用时：34.60秒