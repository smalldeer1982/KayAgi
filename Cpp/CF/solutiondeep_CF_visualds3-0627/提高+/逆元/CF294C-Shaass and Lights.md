# 题目信息

# Shaass and Lights

## 题目描述

There are $ n $ lights aligned in a row. These lights are numbered $ 1 $ to $ n $ from left to right. Initially some of the lights are switched on. Shaass wants to switch all the lights on. At each step he can switch a light on (this light should be switched off at that moment) if there's at least one adjacent light which is already switched on.

He knows the initial state of lights and he's wondering how many different ways there exist to switch all the lights on. Please find the required number of ways modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
1 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
11 2
4 8
```

### 输出

```
6720
```

# AI分析结果



## 算法分类
组合数学/乘法原理与排列组合

---

## 题解思路与算法要点

### 核心思路
1. **区间划分**：将初始已点亮的灯排序后，分割成多个连续未点亮的区间。
2. **内部方案计算**：
   - **中间区间**：可双向扩展（左或右），方案数为 $2^{\text{len}-1}$（len为区间长度）。
   - **首尾区间**：只能单向扩展，方案数为1。
3. **顺序组合**：不同区间的操作顺序可交错，使用多重排列公式 $\frac{(n-m)!}{\prod \text{len}_i!}$ 计算总排列数，再乘以各区间内部方案数。

### 解决难点
- **组合数模运算**：预处理阶乘和逆元数组，利用费马小定理快速计算组合数。
- **边界处理**：首尾区间的单向扩展需单独处理，中间区间长度为0时跳过。

---

## 题解评分（≥4星）

### RedreamMer（5星）
- **亮点**：代码结构清晰，组合数预处理高效，注释详细。
- **关键代码**：
  ```cpp
  for(int i=1;i<=b;i++) s[i]=read();
  sort(s+1,s+b+1);
  for(int i=1;i<=b;i++) {
      x=s[i];
      sum += x-pre-1;
      if(pre!=0 && pre<x-1) 
          ans = ans * C(sum, x-pre-1) % mod * power[x-pre-2] % mod;
      pre=x;
  }
  ```

### StillEmpty（4.5星）
- **亮点**：公式推导详细，代码可读性强，逆元处理优化。
- **关键公式**：
  $$ \text{答案} = \frac{(n-m)!}{\prod \text{len}_i!} \prod_{i=1}^{m+1} 2^{\text{len}_i-1} $$

### RockYue（4星）
- **亮点**：分步注释明确，代码简短但逻辑完整。
- **关键逻辑**：
  ```cpp
  for(int i=2, len; i<=m; i++) {
      len = a[i] - a[i-1] -1;
      if(len) res = res * C(k, len) % P * qpow(2, len-1) % P;
      k -= len;
  }
  ```

---

## 最优思路提炼
1. **区间分割与预处理**：排序初始亮灯位置，分割出各未点亮区间。
2. **组合数快速计算**：预处理阶乘和逆元数组，实现 $O(1)$ 组合数查询。
3. **分治乘法原理**：将总方案拆解为各区间的组合数、内部方案数乘积。
4. **边界特殊处理**：首尾区间无双向扩展，直接乘组合数。

---

## 类似算法套路
- **多重排列问题**：如 [CF888D](https://codeforces.com/problemset/problem/888/D)（求错位排列数）。
- **分治组合数学**：如 [洛谷P4071](https://www.luogu.com.cn/problem/P4071)（排列组合与容斥结合）。

---

## 推荐题目
1. [CF888D](https://codeforces.com/problemset/problem/888/D)（多重排列与容斥）
2. [洛谷P1350](https://www.luogu.com.cn/problem/P1350)（组合数递推）
3. [洛谷P3223](https://www.luogu.com.cn/problem/P3223)（高精度组合数）

---

## 代码实现片段（RedreamMer版）
```cpp
// 预处理阶乘、逆元、2的幂次
void init() {
    fac[0] = 1;
    for(int i=1; i<=N; i++) fac[i] = fac[i-1] * i % mod;
    inv[N] = qpow(fac[N], mod-2); // 费马小定理求逆元
    for(int i=N-1; i>=0; i--) inv[i] = inv[i+1] * (i+1) % mod;
    power[0] = 1;
    for(int i=1; i<=N; i++) power[i] = power[i-1] * 2 % mod;
}

// 组合数计算
int C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}

// 主逻辑
int ans = 1, sum = 0;
for(int i=1; i<=m; i++) {
    int x = s[i];
    int len = x - pre - 1;
    sum += len;
    if (pre != 0 && len > 0) {
        ans = ans * C(sum, len) % mod;
        ans = ans * power[len-1] % mod; // 中间段乘2^(len-1)
    }
    pre = x;
}
ans = ans * C(sum, a - pre) % mod; // 处理最后一段
```

---

## 可视化设计思路

### 动画方案
1. **网格绘制**：用Canvas绘制灯排，已亮灯为绿色，未亮为灰色。
2. **区间高亮**：不同区间用不同颜色框选，动态展示扩展过程。
3. **操作步进**：点击按钮单步执行，显示当前选择的区间及点亮方向（左/右箭头）。
4. **数据面板**：实时显示剩余未点亮数、当前组合数值、总方案数。

### 复古像素风格
- **调色板**：8位风格，绿（#00FF00）表已亮，红（#FF0000）表操作高亮。
- **音效**：点亮时播放短促“哔”声，错误操作时播放低音“嗡”声。
- **自动演示**：AI模式按最优路径自动点亮，速度可调。

### 交互功能
- **拖拽调整**：允许用户拖拽初始亮灯位置，实时重新计算方案。
- **历史回放**：记录操作序列，支持回退到任意步骤。

---

通过上述设计，学习者可直观理解组合数与分治思想的结合，同时通过交互操作深化对排列组合原理的掌握。

---
处理用时：123.80秒