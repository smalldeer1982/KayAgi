# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

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

# AI分析结果



# Vasily the Bear and Sequence

## 题目描述

Vasily熊有一个正整数序列 $a_1,a_2,...,a_n$。他需要选出若干数，使得这些数的按位与的美丽值最大。美丽值 $v$ 是最大的非负整数，使得按位与的结果能被 $2^v$ 整除。若不存在这样的 $v$，则美丽值为 -1。若有多个方案，需选数量最多的。

---

## 题解综合分析

### 关键思路总结
1. **高位优先枚举**：从最高位（如30）向低位枚举可能的 $v$。由于高位决定更大的幂次，优先选择高位能满足条件的解。
2. **筛选候选数**：对于每个 $v$，筛选所有二进制第 $v$ 位为1的数。这些数的按位与结果的第 $v$ 位必须为1，且低 $v$ 位全为0。
3. **快速验证**：通过计算这些候选数的按位与结果，判断其是否能被 $2^v$ 整除（即低 $v$ 位全为0）。若满足条件，立即输出当前解。

### 最优解法技巧
- **位掩码优化**：使用位掩码 $(2^v-1)$ 快速判断低 $v$ 位是否全为0。若候选数的按位与结果与掩码按位与为0，则满足条件。
- **贪心选择最多数**：在满足条件的前提下，尽可能多选数以保证解的规模最大。

---

## 精选题解

### 题解一（Graphcity，4星）
**亮点**：  
- 直接枚举 $v$，通过逐个按位与计算最终结果。
- 代码清晰，逻辑直接。

**核心代码**：
```cpp
for(int i=30; i>=0; --i) {
    vector<int> tmp;
    int res = -1;
    for(int x : a) {
        if(x & (1<<i)) {
            tmp.push_back(x);
            res = (res == -1) ? x : res & x;
        }
    }
    if(res != -1 && (res % (1<<i)) == 0) {
        cout << tmp.size() << endl;
        for(int x : tmp) cout << x << " ";
        return 0;
    }
}
```
**实现思想**：  
收集所有第 $i$ 位为1的数，计算它们的按位与。若结果能被 $2^i$ 整除，则输出。

---

### 题解二（Rye_Catcher，4星）
**亮点**：  
- 使用位掩码快速验证低 $v$ 位是否为0。
- 代码简洁，效率较高。

**核心代码**：
```cpp
for(int k=30; k>=0; --k) {
    int mask = (1<<k) -1;
    vector<int> tmp;
    int y = mask;
    for(int x : a) {
        if(x & (1<<k)) {
            tmp.push_back(x);
            y &= x;
        }
    }
    if(y == 0 && !tmp.empty()) {
        cout << tmp.size() << endl;
        for(int x : tmp) cout << x << " ";
        return 0;
    }
}
```
**实现思想**：  
通过掩码 $2^k-1$ 逐位与候选数进行按位与操作，最终若掩码为0，说明低 $k$ 位全为0。

---

## 拓展与总结
**同类问题**：  
1. **按位贪心**：如最大异或值（CF276D）、子集按位或的最值（LOJ 1012）。
2. **位运算性质**：如判断二进制中1的个数（LeetCode 191）、二进制翻转（LeetCode 190）。

**推荐题目**：  
1. [P2114 最大异或和路径](https://www.luogu.com.cn/problem/P2114)  
2. [P4310 异或粽子](https://www.luogu.com.cn/problem/P4310)  
3. [P1582 倒水问题](https://www.luogu.com.cn/problem/P1582)

---
处理用时：277.05秒