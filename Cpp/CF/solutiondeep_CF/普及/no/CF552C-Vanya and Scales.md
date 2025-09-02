# 题目信息

# Vanya and Scales

## 题目描述

Vanya has a scales for weighing loads and weights of masses $ w^{0},w^{1},w^{2},...,w^{100} $ grams where $ w $ is some integer not less than $ 2 $ (exactly one weight of each nominal value). Vanya wonders whether he can weight an item with mass $ m $ using the given weights, if the weights can be put on both pans of the scales. Formally speaking, your task is to determine whether it is possible to place an item of mass $ m $ and some weights on the left pan of the scales, and some weights on the right pan of the scales so that the pans of the scales were in balance.

## 说明/提示

Note to the first sample test. One pan can have an item of mass $ 7 $ and a weight of mass $ 3 $ , and the second pan can have two weights of masses $ 9 $ and $ 1 $ , correspondingly. Then $ 7+3=9+1 $ .

Note to the second sample test. One pan of the scales can have an item of mass $ 99 $ and the weight of mass $ 1 $ , and the second pan can have the weight of mass $ 100 $ .

Note to the third sample test. It is impossible to measure the weight of the item in the manner described in the input.

## 样例 #1

### 输入

```
3 7
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
100 99
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
100 50
```

### 输出

```
NO
```

# AI分析结果



### 中文题目重写
#### 题目名称：Vanya 和天平

**题目描述**  
Vanya 有一个用于称重的天平和一系列砝码，砝码的质量分别为 $w^0, w^1, w^2, \dots, w^{100}$ 克，其中 $w$ 是不小于 2 的整数（每种砝码只有一个）。Vanya 想知道是否可以通过将砝码放在天平的两侧来称量质量为 $m$ 的物品。具体来说，判断是否存在一种放置方式，使得物品和一些砝码放在左盘，另一些砝码放在右盘，使得天平平衡。

**输入格式**  
输入两个整数 $w$ 和 $m$，表示砝码基数和物品质量。  
**输出格式**  
若可以称量，输出 `YES`；否则输出 `NO`。  

**样例说明**  
- 样例 1 中，左盘放物品（7 克）和 $3^1=3$ 克砝码，右盘放 $3^2=9$ 克和 $3^0=1$ 克砝码，满足 $7+3=9+1$。  
- 样例 2 中，左盘放物品（99 克）和 $100^0=1$ 克砝码，右盘放 $100^1=100$ 克砝码，满足 $99+1=100$。  

---

### 算法分类  
**数学（进制分解）**

---

### 题解分析与结论  
**核心思路**：将问题转化为将 $m$ 表示为 $w$ 进制数，且每个数位只能是 $-1,0,1$。通过逐位调整余数，若某位无法调整（余数不在 $-1,0,1$ 范围内），则无解。  
**解决难点**：如何确保每一步调整后的余数合法，并通过不断除以 $w$ 验证高位是否满足条件。

---

### 高质量题解精选（评分≥4星）

#### 1. **作者：细数繁星（5星）**  
**关键亮点**  
- 详细数学推导：将问题分解为等式 $m = \sum p_i w^i$，并证明每一步余数必须满足 $m \pm 1$ 或 $m$ 能被 $w$ 整除。  
- 洋葱式分解：通过循环将 $m$ 分解为 $w$ 进制，每一步调整余数后除以 $w$，逻辑清晰。  
**代码核心**  
```cpp
while (m) {
    m = (m % w == 0) ? m / w : 
        ((m - 1) % w == 0) ? (m - 1) / w : 
        ((m + 1) % w == 0) ? (m + 1) / w : -114514;
    if (m == -114514) { cout << "NO"; return; }
}
cout << "YES";
```

#### 2. **作者：GaoKui（4星）**  
**关键亮点**  
- 进制转换视角：将 $m$ 转为 $w$ 进制后，处理进位使每位数位合法。  
- 进位处理技巧：若某位为 $w-1$，则视为 $-1$ 并进位，避免无效分支。  
**代码核心**  
```cpp
vector<ll> v;
while (m) { v.push_back(m % w); m /= w; }
for (int i = 0; i < v.size(); i++) {
    if (v[i] == w-1) { v[i] = 0; v[i+1]++; } // 进位处理
    else if (v[i] > 1) { cout << "NO"; return; }
}
```

#### 3. **作者：封禁用户（4星）**  
**关键亮点**  
- 简洁的贪心策略：直接通过模运算调整余数，代码极简且高效。  
- 示例辅助理解：通过具体例子（如 $m=27, w=2$）演示分解过程。  
**代码核心**  
```cpp
while(m) {
    if ((m % w != 0) && (m-1) % w != 0 && (m+1) % w != 0) {
        printf("NO"); return;
    }
    m = (m % w == 0) ? m/w : ((m-1) % w == 0) ? (m-1)/w : (m+1)/w;
}
printf("YES");
```

---

### 最优关键思路总结  
1. **进制分解法**：将 $m$ 逐步分解为 $w$ 进制，每一步确保余数为 $-1,0,1$。  
2. **贪心调整余数**：若当前余数非法，则尝试 $m \pm 1$ 后继续分解，若无法调整则无解。  
3. **数学等价性**：问题等价于验证 $m$ 的 $w$ 进制表示中，每位数位绝对值不超过 1。

---

### 类似题目推荐  
1. **P1143 进制转换**（进制分解基础）  
2. **CF679B Bear and Tower of Cubes**（类似贪心分解）  
3. **P1866 [COCI2012-2013#3] SAHOVNICA**（砝码称重变式）

---
处理用时：74.53秒