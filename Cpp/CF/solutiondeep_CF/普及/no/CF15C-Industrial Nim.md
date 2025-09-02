# 题目信息

# Industrial Nim

## 题目描述

There are $ n $ stone quarries in Petrograd.

Each quarry owns $ m_{i} $ dumpers ( $ 1<=i<=n $ ). It is known that the first dumper of the $ i $ -th quarry has $ x_{i} $ stones in it, the second dumper has $ x_{i}+1 $ stones in it, the third has $ x_{i}+2 $ , and the $ m_{i} $ -th dumper (the last for the $ i $ -th quarry) has $ x_{i}+m_{i}-1 $ stones in it.

Two oligarchs play a well-known game Nim. Players take turns removing stones from dumpers. On each turn, a player can select any dumper and remove any non-zero amount of stones from it. The player who cannot take a stone loses.

Your task is to find out which oligarch will win, provided that both of them play optimally. The oligarchs asked you not to reveal their names. So, let's call the one who takes the first stone «tolik» and the other one «bolik».

## 样例 #1

### 输入

```
2
2 1
3 2
```

### 输出

```
tolik
```

## 样例 #2

### 输入

```
4
1 1
1 1
1 1
1 1
```

### 输出

```
bolik
```

# AI分析结果



# Industrial Nim 题解中文翻译

## 题目描述

彼得格勒有 $n$ 个采石场。  
每个采石场有 $m_i$ 辆运输车（$1 \le i \le n$）。已知第 $i$ 个采石场的第一辆运输车有 $x_i$ 块石头，第二辆有 $x_i + 1$ 块，第三辆有 $x_i + 2$ 块，以此类推，最后一辆（第 $m_i$ 辆）有 $x_i + m_i - 1$ 块石头。  

两位寡头玩经典的 Nim 游戏：轮流从任意运输车中取任意正数量的石头。无法取石者输。判断先手（tolik）和后手（bolik）的胜负。

## 样例 #1

### 输入
```
2
2 1
3 2
```

### 输出
```
tolik
```

## 样例 #2

### 输入
```
4
1 1
1 1
1 1
1 1
```

### 输出
```
bolik
```

---

**算法分类**: 数学/位运算

---

## 题解综合分析

各题解核心思路一致：利用异或运算性质快速计算连续自然数异或和。关键技巧为：  
1. 定义前缀异或函数 $f(x) = 0 \oplus 1 \oplus ... \oplus x$  
2. 发现 $f(x)$ 的周期性规律：$x \bmod 4$ 决定结果  
3. 区间异和 $[l, r] = f(r) \oplus f(l-1)$

### 高星题解精选（评分4~5星）

#### 1. Heartlessly（5星）
**亮点**：  
- 完整数学推导，明确四种模4情况的证明  
- 代码结构清晰，封装求解函数  
- 处理输入输出高效  

**核心代码**：
```cpp
inline LL solve(LL x) {
    switch (x % 4) {
        case 0: return x;
        case 1: return 1;
        case 2: return x + 1;
        case 3: return 0;
    }
}
// 调用方式：ans ^= solve(r) ^ solve(l-1);
```

#### 2. OldVagrant（4.5星）
**亮点**：  
- 详细分步说明规律发现过程  
- 代码注释清晰，适合教学  
- 包含测试用例验证思路  

**实现要点**：
```cpp
ll work(ll x) {
    if(x%4==0) return x;
    if(x%4==1) return 1;
    if(x%4==2) return x+1;
    else return 0;
}
// 异或区间 [a, a+m-1] 的结果为 work(a+m-1) ^ work(a-1)
```

#### 3. IceKylin（4星）
**亮点**：  
- 代码简洁高效  
- 异或性质总结到位  
- 使用快速读写优化  

**代码片段**：
```cpp
il ll f(ll x) {
    if(x%4==0) return x;
    if(x%4==1) return 1;
    if(x%4==2) return x+1;
    return 0;
}
ans ^= f(x-1) ^ f(x+m-1);
```

---

## 关键思路总结

**核心技巧**：  
- **周期规律**：连续自然数异或和的模4规律，将 $O(n)$ 计算优化为 $O(1)$  
- **区间转换**：利用前缀异或差计算任意区间异或和 $[l, r] = f(r) \oplus f(l-1)$  
- **位运算优化**：避免逐项计算，直接处理整组奇偶对（偶-奇对异或结果为1）

**同类拓展**：  
- 类似需要利用数论规律的博弈问题  
- 涉及大范围位运算性质的问题  
- 前缀思想在区间查询中的应用

---

## 相似题目推荐

1. [P2197 Nim游戏](https://www.luogu.com.cn/problem/P2197)  
   - 基础Nim博弈，异或和判断胜负
   
2. [P4301 新Nim游戏](https://www.luogu.com.cn/problem/P4301)  
   - 需要构造初始取石子方案的最优策略

3. [P5652 基础博弈练习题](https://www.luogu.com.cn/problem/P5652)  
   - 结合区间查询的博弈问题

---

## 题解心得摘录

1. **午夜飘雪**：  
   > "一开始忘记开long long然而依然AC" → 大数据范围必须注意数据类型

2. **jijidawang**：  
   > "相邻两数的异或肯定是1" → 发现这一性质是解题突破口

3. **Cutler**：  
   > 分组处理奇偶对的思想 → 将复杂问题分解为可处理的单元

---
处理用时：55.03秒