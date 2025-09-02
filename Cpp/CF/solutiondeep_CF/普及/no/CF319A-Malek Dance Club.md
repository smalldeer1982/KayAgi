# 题目信息

# Malek Dance Club

## 题目描述

As a tradition, every year before IOI all the members of Natalia Fan Club are invited to Malek Dance Club to have a fun night together. Malek Dance Club has $ 2^{n} $ members and coincidentally Natalia Fan Club also has $ 2^{n} $ members. Each member of MDC is assigned a unique id $ i $ from $ 0 $ to $ 2^{n}-1 $ . The same holds for each member of NFC.

One of the parts of this tradition is one by one dance, where each member of MDC dances with a member of NFC. A dance pair is a pair of numbers $ (a,b) $ such that member $ a $ from MDC dances with member $ b $ from NFC.

The complexity of a pairs' assignment is the number of pairs of dancing pairs $ (a,b) $ and $ (c,d) $ such that $ a&lt;c $ and $ b&gt;d $ .

You are given a binary number of length $ n $ named $ x $ . We know that member $ i $ from MDC dances with member ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/99db469180d6ab11deff381b4df066112345cbb1.png) from NFC. Your task is to calculate the complexity of this assignment modulo $ 1000000007 $ $ (10^{9}+7) $ .

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF319A/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) denotes applying «XOR» to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in C++ and Java it denotes as «^», in Pascal — «xor».

## 样例 #1

### 输入

```
11
```

### 输出

```
6
```

## 样例 #2

### 输入

```
01
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
```

### 输出

```
1
```

# AI分析结果



# Malek Dance Club

## 题目描述

作为传统，每年 IOI 前 Natalia Fan Club 的所有成员都被邀请到 Malek Dance Club 共度欢乐之夜。MDC 和 NFC 各有 $2^n$ 名成员，每个成员的编号均为 $0$ 到 $2^n-1$ 的唯一整数。

舞蹈配对 $(a,b)$ 表示 MDC 成员 $a$ 与 NFC 成员 $b$ 共舞。给定二进制数 $x$，已知 MDC 成员 $i$ 的舞伴是 $i \oplus x$。要求计算所有配对中逆序对的数量模 $10^9+7$ 的结果（逆序对定义为 $a < c$ 但 $b > d$ 的两个配对 $(a,b)$ 和 $(c,d)$）。

## 输入样例

样例 #1  
输入：`11`  
输出：`6`

样例 #2  
输入：`01`  
输出：`2`

样例 #3  
输入：`1`  
输出：`1`

## 算法分类
组合数学、位运算

---

## 题解分析与结论

### 关键思路
每位为 1 的二进制位会独立贡献逆序对数目。具体地，对于第 $i$ 位（高位到低位 1-based）：
- 贡献公式为 $2^{i-1} \times 4^{n-i} = 2^{2n-i-1}$  
- 总答案即所有 1 位的贡献之和

### 最优题解（评分：5⭐）

**作者：NusGhy**  
**亮点**：数学建模清晰，直接计算每位贡献，代码简洁高效  
**核心代码**：
```cpp
for(int i = 1; i <= n; ++i) {
    if(x[i] == '1') {
        ans += powmod(2, i-1) * powmod(4, n-i);
        ans %= mod;
    }
}
```

### 拓展思路
类似问题可通过拆解二进制位分析贡献，例如格雷码转换、数值变换后的排列性质分析等。

---

## 推荐相似题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
2. [P1965 转圈游戏](https://www.luogu.com.cn/problem/P1965)  
3. [P7078 棋盘游戏](https://www.luogu.com.cn/problem/P7078)

---
处理用时：93.38秒