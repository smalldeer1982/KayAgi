# 题目信息

# Vasilije Loves Number Theory

## 题目描述

Vasilije is a smart student and his discrete mathematics teacher Sonja taught him number theory very well.

He gave Ognjen a positive integer $ n $ .

Denote $ d(n) $ as the number of positive integer divisors of $ n $ , and denote $ gcd(a, b) $ as the largest integer $ g $ such that $ a $ is divisible by $ g $ and $ b $ is divisible by $ g $ .

After that, he gave Ognjen $ q $ queries, and there are $ 2 $ types of queries.

- $ 1 $ , $ x $ — set $ n $ to $ n \cdot x $ , and then answer the following question: does there exist a positive integer $ a $ such that $ gcd(a, n) = 1 $ , and $ d(n \cdot a) = n $ ?
- $ 2 $ — reset $ n $ to its initial value (before any queries).

Note that $ n $ does not get back to its initial value after the type 1 query.

Since Ognjen is afraid of number theory, Vasilije promised him that after each query, $ d(n) \le 10^9 $ , however, even with that constraint, he still needs your help with this problem.

## 说明/提示

In the first test case, we initially have $ n=1 $ .

After the first query: $ n=1 $ , $ d(n)=1 $ , so by taking $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the second query: $ n=2 $ , $ d(n)=2 $ , we can, again, take $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the third query $ n=1 $ , and this is a type $ 2 $ query so we don't answer it.

After the fourth query: $ n=8 $ , and by taking $ a=3 $ , $ d(n \cdot a) = d(24) = 8 = n $ , so the answer is "YES".

After the fifth query: $ n=72 $ , now we can take $ a=637 $ to get $ n \cdot a = 45864 $ , and $ d(n \cdot a) = 72 = n $ , so the answer is "YES".

In the second test case, we initially have $ n=20 $ .

After the first query: $ n=60 $ , and the answer is "YES".

After the second query: $ n=20 $ , this is a type $ 2 $ query, so we don't answer it.

After the third query: $ n=140 $ , and it can be proven that no matter which positive integer $ a $ we take, $ d(n \cdot a) $ will never be equal to $ n $ , so the answer to this query is "NO".

After the fourth query: $ n=1680 $ . It can be proven that there exists a positive integer $ a $ , such that $ d(n \cdot a) = n $ , so the answer is "YES".

## 样例 #1

### 输入

```
7
1 5
1 1
1 2
2
1 8
1 9
20 4
1 3
2
1 7
1 12
16 10
1 6
1 6
1 10
1 9
1 1
1 9
1 7
1 3
1 2
1 10
9 1
1 3
8 1
1 2
8 3
1 5
1 8
1 10
11 5
1 8
1 2
1 1
1 3
1 1```

### 输出

```
YES
YES
YES
YES

YES
NO
YES

YES
NO
YES
YES
YES
NO
YES
NO
YES
YES

NO

NO

YES
NO
NO

YES
NO
NO
NO
NO```

# AI分析结果



---

## 算法分类
**数论（质因数分解与因数统计）**

---

## 综合分析与结论
### 核心思路与难点
- **问题转化**：通过数论推导得出核心条件 `d(n) | n`（d(n) 是 n 的因数）
- **质因数维护**：动态维护 n 的质因数分解形式，每次乘法操作只需分解新乘数 x 的质因数
- **动态计算 d(n)**：基于质因数分解快速计算当前 d(n) = ∏(k_i+1)
- **整除判断**：将 d(n) 分解质因数，检查其所有质因数的指数是否 ≤ n 对应质因数的指数

### 可视化设计思路
1. **像素风格展示**：
   - 左侧显示当前 n 的质因数分解式（如 2^3 × 3^1）
   - 右侧显示 d(n) 的质因数分解式（如 (3+1)(1+1) = 8 → 2^3）
   - 用不同颜色高亮新增的质因数（如红色表示新乘数 x 分解出的质因数）
2. **关键步骤动画**：
   - 分解 x 的质因数时，动态展示质因数的指数增长
   - 计算 d(n) 时，逐步展示每个质因数的 (k_i+1) 项相乘过程
   - 判断整除时，逐个对比 d(n) 质因数的指数与 n 的指数
3. **音效与交互**：
   - 正确时播放上扬音效（8-bit 风格）
   - 错误时播放低音短促音效
   - 支持步进控制观察质因数分解与指数对比过程

---

## 题解清单（评分 ≥4★）
### 1. 作者：ran_qwq（★★★★★）
- **亮点**：数学证明完整，给出核心结论的严格推导，代码通过分解质因数快速判断整除性
- **关键代码**：
  ```cpp
  for (auto v : now) ans *= v.snd + 1;  // 计算 d(n)
  for (auto v : now) (mod *= qpow(v.fst, v.snd, ans)) %= ans;  // 计算 n mod d(n)
  ```

### 2. 作者：StayAlone（★★★★☆）
- **亮点**：代码简洁高效，使用快速幂优化模运算，复杂度分析清晰
- **核心优化**：
  ```cpp
  int qpow(ll a, int b, int mod) {  // 快速幂计算 a^b mod mod
    ll ans = 1;
    while (b) {
        if (b & 1) (ans *= a) %= mod;
        (a *= a) %= mod; b >>= 1;
    } return ans;
  }
  ```

### 3. 作者：Kedit2007（★★★★☆）
- **亮点**：使用线性筛预处理最小质因数，质因数分解效率优化
- **关键实现**：
  ```cpp
  void func(int x) {  // 分解 x 并更新质因数表
    for (const auto& p : primes) {
        if (p > x) break;
        while (x % p == 0) x /= p, ++mp[p];
    }
    if (x > 1) ++mp[x];
  }
  ```

---

## 最优思路与技巧
### 核心算法流程
1. **初始化**：分解初始 n 的质因数，存储到 map 中
2. **处理查询**：
   - 类型1：分解 x 的质因数，更新当前质因数表
   - 计算当前 d(n) = ∏(k_i+1)
   - 分解 d(n) 的质因数，检查是否每个质因数的指数 ≤ n 对应指数
3. **重置操作**：恢复初始质因数表

### 关键优化点
- **质因数分解优化**：预处理素数表或最小质因数加速分解
- **模运算优化**：通过质因数指数直接计算模值，避免存储大数
- **状态恢复**：存储初始质因数表的拷贝实现 O(1) 重置

---

## 同类型题目推荐
1. **P1495 曹冲养猪**（中国剩余定理与模运算）
2. **P2043 质因数分解**（静态质因数分解练习）
3. **P1069 细胞分裂**（质因数分解与指数对比）

---

## 可视化代码片段（JS Canvas）
```javascript
// 绘制质因数分解式
function drawFactors(ctx, factors, x, y, color) {
  let text = "";
  factors.forEach((exp, prime) => {
    text += `${prime}<sup>${exp}</sup> × `;
  });
  text = text.slice(0, -3); // 移除末尾的"× "
  ctx.fillStyle = color;
  ctx.fillText(text, x, y);
}

// 更新动画帧
function updateAnimation() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  // 绘制当前 n 的质因数
  drawFactors(ctx, currentFactors, 50, 100, "#00FF00");
  // 绘制 d(n) 的质因数
  let dFactors = calcDFactors(currentFactors);
  drawFactors(ctx, dFactors, 50, 200, "#FF0000");
  // 高亮不满足条件的质因数
  dFactors.forEach((exp, prime) => {
    if (currentFactors.get(prime) < exp) {
      ctx.fillStyle = "#FFFF00";
      ctx.fillRect(...getPrimePosition(prime), 20, 20);
    }
  });
}
```

---

## 复古游戏化设计
1. **像素风格**：使用 16 色调色板，质因数显示为 16×16 像素块
2. **音效设计**：
   - 正确答案：播放 [NES 过关音效](https://sfxr.me/#34T0PmQkZEjqBq4W7Wg3H6iHcY7J6)
   - 错误答案：播放 [FC 爆炸音效](https://sfxr.me/#34T0PmQkZkkjqBq4W7Wg3H6iHcY7J6)
3. **自动演示模式**：
   - 按空格键逐步执行操作
   - 按 'A' 键自动播放，速度可调
4. **积分系统**：
   - 正确判断 +100 分
   - 连续正确触发 2x 连击倍率
   - 最高分记录存储于 localStorage

---

通过上述分析与设计，学习者可以深入理解质因数分解在动态数论问题中的应用，并通过交互式可视化直观观察算法执行过程。

---
处理用时：83.50秒