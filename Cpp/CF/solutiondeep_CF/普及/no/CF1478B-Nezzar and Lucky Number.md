# 题目信息

# Nezzar and Lucky Number

## 题目描述

Nezzar's favorite digit among $ 1,\ldots,9 $ is $ d $ . He calls a positive integer lucky if $ d $ occurs at least once in its decimal representation.

Given $ q $ integers $ a_1,a_2,\ldots,a_q $ , for each $ 1 \le i \le q $ Nezzar would like to know if $ a_i $ can be equal to a sum of several (one or more) lucky numbers.

## 说明/提示

In the first test case, $ 24 = 17 + 7 $ , $ 27 $ itself is a lucky number, $ 25 $ cannot be equal to a sum of lucky numbers.

## 样例 #1

### 输入

```
2
3 7
24 25 27
10 7
51 52 53 54 55 56 57 58 59 60```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
YES
YES
NO```

# AI分析结果

### 中文题目重写
#### 题目描述
Nezzar 最喜欢的数字是 $d$（$1 \leq d \leq 9$）。他称一个正整数为“幸运数”，如果该数的十进制表示中至少包含一个数字 $d$。

给定 $q$ 个整数 $a_1, a_2, \ldots, a_q$，对于每个 $1 \leq i \leq q$，Nezzar 想知道 $a_i$ 是否可以表示为若干个（一个或多个）幸运数的和。

#### 说明/提示
在第一个测试用例中，$24 = 17 + 7$，$27$ 本身是幸运数，而 $25$ 不能表示为幸运数的和。

#### 样例 #1
##### 输入
```
2
3 7
24 25 27
10 7
51 52 53 54 55 56 57 58 59 60
```

##### 输出
```
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
YES
YES
NO
```

### 算法分类
数学

### 题解分析与结论
本题的核心在于判断一个数是否可以表示为若干个包含数字 $d$ 的数的和。大多数题解都基于以下两个关键观察：
1. 当 $a_i \geq 10d$ 时，$a_i$ 一定可以表示为幸运数的和。
2. 当 $a_i < 10d$ 时，可以通过枚举或暴力判断 $a_i$ 是否可以表示为若干个幸运数的和。

### 精选题解
#### 题解1：作者：Loser_King (赞：6)
**星级：4.5**
**关键亮点：**
- 通过数学推导证明了当 $a_i \geq 10d$ 时，$a_i$ 一定可以表示为幸运数的和。
- 对于 $a_i < 10d$ 的情况，通过枚举 $b$ 来判断 $a_i$ 是否可以表示为 $10k + bd$ 的形式。

**代码实现：**
```cpp
int check(int x, int k) {
    if (x >= 10 * k) return 1;
    while (x >= 0) if (x % 10 != k) x -= k; else return 1;
    return 0;
}
```
**核心思想：** 通过不断减去 $k$ 来判断 $x$ 是否可以表示为幸运数的和。

#### 题解2：作者：Zzzzzzzm (赞：3)
**星级：4**
**关键亮点：**
- 详细分析了幸运数的构成，特别是当 $a_i < 10d$ 时，通过减去 $10$ 的倍数来判断是否可以表示为幸运数的和。
- 代码简洁，逻辑清晰。

**代码实现：**
```cpp
bool flag = 0;
while (a >= 0) {
    a -= num;
    if (a % 10 == 0) {
        flag = 1;
        printf("YES\n");
        break;
    }
}
```
**核心思想：** 通过不断减去 $num$ 并检查 $a$ 是否能被 $10$ 整除来判断是否可以表示为幸运数的和。

#### 题解3：作者：33aaron (赞：1)
**星级：4**
**关键亮点：**
- 提出了三个结论，分别处理 $a_i \geq 10d$、$a_i$ 是 $d$ 的倍数、以及 $a_i$ 是 $d$ 的倍数加上 $10$ 的倍数的情况。
- 代码结构清晰，逻辑严谨。

**代码实现：**
```cpp
if (in >= d * 10) cout << "YES\n";
else {
    if (in % d == 0) cout << "YES\n";
    else {
        int flag = 0;
        for (int i = 10; i <= in / 10 * 10; i += 10)
            if ((in - i) % d == 0) { cout << "YES\n"; flag = 1; break; }
        if (!flag) cout << "NO\n";
    }
}
```
**核心思想：** 通过枚举 $10$ 的倍数来判断 $in$ 是否可以表示为幸运数的和。

### 最优关键思路
1. **数学推导**：当 $a_i \geq 10d$ 时，$a_i$ 一定可以表示为幸运数的和。
2. **枚举与暴力**：对于 $a_i < 10d$ 的情况，通过枚举或暴力判断 $a_i$ 是否可以表示为幸运数的和。

### 可拓展之处
类似的问题可以扩展到其他进制或更复杂的数字组合问题。例如，判断一个数是否可以表示为若干个包含特定数字的数的和，或者在不同进制下的类似问题。

### 推荐题目
1. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

### 个人心得
- **调试经历**：在处理 $a_i < 10d$ 的情况时，容易忽略边界条件，如 $a_i = 0$ 或 $a_i = d$。
- **顿悟感想**：通过数学推导可以大大简化问题，减少不必要的枚举和暴力判断。

---
处理用时：37.49秒