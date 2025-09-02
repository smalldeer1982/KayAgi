# 题目信息

# k-Interesting Pairs Of Integers

## 题目描述

Vasya has the sequence consisting of $ n $ integers. Vasya consider the pair of integers $ x $ and $ y $ k-interesting, if their binary representation differs from each other exactly in $ k $ bits. For example, if $ k=2 $ , the pair of integers $ x=5 $ and $ y=3 $ is k-interesting, because their binary representation $ x $ =101 and $ y $ =011 differs exactly in two bits.

Vasya wants to know how many pairs of indexes ( $ i $ , $ j $ ) are in his sequence so that $ i&lt;j $ and the pair of integers $ a_{i} $ and $ a_{j} $ is k-interesting. Your task is to help Vasya and determine this number.

## 说明/提示

In the first test there are 4 k-interesting pairs:

- ( $ 1 $ , $ 3 $ ),
- ( $ 1 $ , $ 4 $ ),
- ( $ 2 $ , $ 3 $ ),
- ( $ 2 $ , $ 4 $ ).

In the second test $ k=0 $ . Consequently, integers in any k-interesting pair should be equal to themselves. Thus, for the second test there are 6 k-interesting pairs:

- ( $ 1 $ , $ 5 $ ),
- ( $ 1 $ , $ 6 $ ),
- ( $ 2 $ , $ 3 $ ),
- ( $ 2 $ , $ 4 $ ),
- ( $ 3 $ , $ 4 $ ),
- ( $ 5 $ , $ 6 $ ).

## 样例 #1

### 输入

```
4 1
0 3 2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 0
200 100 100 100 200 200
```

### 输出

```
6
```

# AI分析结果



# k-Interesting Pairs Of Integers

## 题目描述

Vasya 有一个包含 $n$ 个整数的序列。他认为两个整数 $x$ 和 $y$ 是 k-interesting 的，当且仅当它们的二进制表示在恰好 $k$ 个位上不同。例如，当 $k=2$ 时，$x=5$（二进制 101）和 $y=3$（二进制 011）是 k-interesting 的，因为它们在两个位上不同。

任务：计算序列中满足 $i<j$ 且 $a_i$ 与 $a_j$ 是 k-interesting 的所有索引对 $(i,j)$ 的数量。

## 算法分类
位运算、组合数学

---

## 题解对比与结论

### 核心思路
预处理所有二进制含 $k$ 个 1 的数值 $z$，利用异或性质 $x \oplus y = z \iff y = x \oplus z$。维护每个数值出现次数的哈希表，对于每个新数 $x$，累加所有满足 $x \oplus z$ 的已出现数值个数。

### 关键优化
1. **预处理有效异或值**：枚举 $0$ 到 $2^{14}$ 范围内二进制含 $k$ 个 1 的数，时间复杂度 $O(2^{14})$
2. **动态哈希统计**：对每个输入数 $x$，查询所有 $x \oplus z$ 的历史出现次数，时间复杂度 $O(n \cdot C_{14}^k)$

---

## 精选题解

### 题解1（作者：Lian_zy，5星）
**亮点**：
- 预处理与异或性质结合，时间复杂度最优
- 使用位运算快速统计二进制 1 的个数
- 代码简洁易懂，逻辑清晰

**核心代码**：
```cpp
for (int i = 0; i <= 16384; i++) {
    if (check(i) != k) continue;
    ok[++cnt] = i;
}
for (int i = 1; i <= n; i++) {
    scanf("%lld", &x);
    for (int j = 1; j <= cnt; j++) 
        ans += a[x ^ ok[j]];
    a[x]++;
}
```

### 题解2（作者：DPair，4星）
**亮点**：
- 使用 GCC 内置函数 `__builtin_popcount` 加速位计数
- 采用快读快写优化 IO
- 处理大范围数值的哈希表

**核心代码**：
```cpp
for (int i = 0; i <= (1 << 14); i++) {
    if(__builtin_popcount(i) == k)
        num[++tot] = i;
}
for (int xx : inputs) {
    for (int z : num) 
        ans += ct[xx ^ z];
    ct[xx]++;
}
```

### 题解3（作者：Robin_kool，4星）
**亮点**：
- 详细注释说明异或性质的应用
- 独立实现位计数函数，保证跨平台兼容性
- 显式处理 k=0 的特殊情况

**核心代码**：
```cpp
for (int i = 0; i <= (1 << 14); ++i) 
    if (check(i)) ok[++cnt] = i;
for (x : inputs) {
    for (z : ok) 
        ans += cnt_map[x ^ z];
    cnt_map[x]++;
}
```

---

## 总结与拓展

### 关键技巧
- **位运算与哈希结合**：利用异或的可逆性将配对查询转换为单点查询
- **预处理剪枝**：通过预计算有效异或值避免实时位运算
- **组合数学思想**：通过哈希统计将配对问题转化为组合计数

### 类似题目
1. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)（位运算优化）
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（哈希映射应用）
3. [P3067 Balanced Cow Subsets](https://www.luogu.com.cn/problem/P3067)（位运算与折半搜索）

### 心得摘录
> "注意当 k=0 时需特殊处理相同数对的组合数，通过异或性质巧妙转化为单值查询" —— Lian_zy  
> "使用 __builtin_popcount 时要注意数据范围，避免整数溢出" —— DPair  
> "预处理范围应根据题目数值上限确定，2^14 可覆盖 1e4 级数据" —— Robin_kool

---
处理用时：137.97秒