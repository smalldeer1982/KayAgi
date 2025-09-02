# 题目信息

# Gosha is hunting

## 题目描述

Gosha is hunting. His goal is to catch as many Pokemons as possible. Gosha has $ a $ Poke Balls and $ b $ Ultra Balls. There are $ n $ Pokemons. They are numbered $ 1 $ through $ n $ . Gosha knows that if he throws a Poke Ball at the $ i $ -th Pokemon he catches it with probability $ p_{i} $ . If he throws an Ultra Ball at the $ i $ -th Pokemon he catches it with probability $ u_{i} $ . He can throw at most one Ball of each type at any Pokemon.

The hunting proceeds as follows: at first, Gosha chooses no more than $ a $ Pokemons at which he will throw Poke Balls and no more than $ b $ Pokemons at which he will throw Ultra Balls. After that, he throws the chosen Balls at the chosen Pokemons. If he throws both Ultra Ball and Poke Ball at some Pokemon, he is caught if and only if he is caught by any of these Balls. The outcome of a throw doesn't depend on the other throws.

Gosha would like to know what is the expected number of the Pokemons he catches if he acts in an optimal way. In other words, he would like to know the maximum possible expected number of Pokemons can catch.

## 样例 #1

### 输入

```
3 2 2
1.000 0.000 0.500
0.000 1.000 0.500
```

### 输出

```
2.75
```

## 样例 #2

### 输入

```
4 1 3
0.100 0.500 0.500 0.600
0.100 0.500 0.900 0.400
```

### 输出

```
2.16
```

## 样例 #3

### 输入

```
3 2 0
0.412 0.198 0.599
0.612 0.987 0.443
```

### 输出

```
1.011```

# AI分析结果



### 唯一算法分类  
**二分**

---

### 综合分析与结论  
题目要求在双重限制（最多用 `a` 个 A 球和 `b` 个 B 球）下最大化期望捕捉数。核心思路是将双重限制转化为单限制问题，通过 **二分法（WQS 二分）** 优化。  

#### 二分过程解析  
1. **搜索区间**：初始设为 `[0, 1]`，因概率范围为 [0,1]。  
2. **二分条件**：检查当前斜率 `k` 下的最优解是否满足 B 球使用数 ≤ `b`。若满足，说明 `k` 过大需减小右边界，反之增大左边界。  
3. **收缩逻辑**：通过调整 `k`，将 B 球的使用代价动态嵌入目标函数，使得最终解恰好满足 B 球数量限制。  
4. **退出条件**：固定迭代次数（如 77 次）或足够小的精度差。  

#### 可视化设计思路  
- **动画方案**：  
  - **区间展示**：Canvas 绘制区间 `[l, r]`，高亮当前 `mid`。  
  - **颜色标记**：绿色表示当前 `mid`，红色标记收缩后的新区间。  
  - **步进控制**：允许单步执行观察区间收缩。  
- **复古风格**：  
  - **像素效果**：用 8-bit 风格显示区间数值，每次更新播放经典音效。  
  - **自动模式**：模拟贪吃蛇 AI 的自动收缩流程，逐帧展示。  

---

### 题解清单（≥4星）  
1. **panyf（5星）**  
   - **亮点**：简洁的二分 + 贪心排序，代码清晰，通过斜率调整巧妙处理双重限制。  
2. **2018ljw（4星）**  
   - **亮点**：模拟费用流 + 堆优化，复杂度低至 `O(n log n)`，分类讨论增广路径。  
3. **0x3F（4星）**  
   - **亮点**：提出 WQS 三分法，解决凸包共线问题，思路新颖。  

---

### 核心代码实现（panyf 解法）  
```cpp
bool chk(double k) {
    int i, c = 0;
    ans = 0;
    for (i = 1; i <= n; ++i) {
        // 计算每种选择的最优贡献
        if (p[i] > p[i] + u[i] - p[i]*u[i] - k) {
            t[i].a1 = 0, t[i].x = p[i];
        } else {
            t[i].a1 = 1, t[i].x = p[i] + u[i] - p[i]*u[i] - k;
        }
        if (0 > u[i] - k) t[i].a0 = 0;
        else t[i].a0 = 1, t[i].x -= u[i] - k, ans += u[i] - k;
    }
    sort(t + 1, t + n + 1, [](T a, T b) { return a.x > b.x; });
    for (i = 1; i <= a; ++i) c += t[i].a1, ans += t[i].x;
    for (; i <= n; ++i) c += t[i].a0;
    return c < b; // 判断 B 球使用是否足够
}
```

---

### 同类型题推荐  
1. **P1484 种树**（WQS 二分经典）  
2. **P4383 [八省联考2018]林克卡特树**（双重限制 + 凸优化）  
3. **CF321E Ciel and Gondolas**（二分答案 + 费用流）  

---

### 个人心得摘录  
- **panyf**：通过调整斜率将问题转化为贪心排序，避免复杂 DP。  
- **wrpwrp**：WQS 二分需注意精度，需在判断时减去 `eps` 避免误判。  

---

### 可视化与复古效果  
- **Canvas 绘制**：  
  ```javascript
  function drawInterval(l, r, mid) {
      ctx.fillStyle = "#8B0000"; // 暗红色背景
      ctx.fillRect(0, 0, canvas.width, canvas.height);
      ctx.fillStyle = "#00FF00"; // 绿色 mid
      ctx.fillRect(mid * canvas.width, 0, 2, canvas.height);
      // 绘制 l, r 边界...
  }
  ```
- **音效触发**：  
  - **mid 更新**：播放 8-bit “哔”声。  
  - **找到解**：播放胜利音效（16-bit 上升音阶）。  

---

**答案**  
```plaintext
唯一算法分类：二分
```

---
处理用时：81.61秒