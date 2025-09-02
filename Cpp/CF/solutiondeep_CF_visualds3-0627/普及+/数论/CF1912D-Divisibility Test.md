# 题目信息

# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0```

# AI分析结果



---

**唯一算法分类**: 数论（模运算、同余性质）

---

### 综合分析与结论

#### 核心思路与解决难点
**核心算法流程**：  
- **数学本质**：寻找满足以下同余式的最小 k：
  - Kind1：`b^k ≡ 0 (mod n)`
  - Kind2：`b^k ≡ 1 (mod n)`
  - Kind3：`b^k ≡ -1 (mod n)`（等价于 `b^k ≡ n-1 (mod n)`）
- **实现步骤**：
  1. 初始化 `c = 1` 用于累积计算 `b^k mod n`
  2. 枚举 k 从 1 到 n：
     - `c = (c * b) % n`
     - 若 c=0 输出 Kind1
     - 若 c=1 输出 Kind2
     - 若 c=n-1 输出 Kind3
  3. 若遍历完未找到则无解

**关键难点**：  
- **数学证明**：需理解三种规则对应的同余式推导（如分组求和等价于 `b^k ≡ 1` 时的系数累积）
- **循环检测**：当 `b^k` 的余数进入循环时停止（部分题解用 bitset 记录）

---

### 题解清单（≥4星）

1. **FFTotoro（★★★★☆）**  
   **亮点**：代码最简洁，直接枚举 k 并累乘模算，清晰体现核心逻辑  
   **优化**：通过 `k<=n` 约束循环次数，无需额外存储空间

2. **Vitamin_B（★★★★☆）**  
   **亮点**：引入 bitset 检测余数循环，避免无限循环（如 `n=1` 时）  
   **注意点**：`vis[x]` 标记已出现余数，确保时间复杂度稳定为 O(n)

3. **OIer_Hhy（★★★★☆）**  
   **亮点**：详细数学推导与代码注释，突出三种情况的同余证明  
   **可读性**：变量命名清晰，逻辑分块明确

---

### 代码核心逻辑

#### FFTotoro 实现片段
```cpp
long long c=1; bool f=false;
for(int k=1; k<=n && !f; k++){
    c = (c * b) % n;  // 累积计算 b^k mod n
    if(c == 0) cout<<"1 "<<k<<'\n', f=true;
    else if(c == 1) cout<<"2 "<<k<<'\n', f=true;
    else if(c == n-1) cout<<"3 "<<k<<'\n', f=true;
}
if(!f) cout<<"0\n";
```

#### Vitamin_B 循环检测优化
```cpp
bitset<1000005> vis;
// ...
for(int k=1; !vis[x = x*(ll)m%n]; ++k) {
    if(x == 0) { /* Kind1 */ }
    else if(x == 1) { /* Kind2 */ }
    else if(x == n-1) { /* Kind3 */ }
    vis[x] = 1;
}
```

---

### 可视化与算法演示

#### 动画方案设计
1. **像素化数值展示**：  
   - 用 8x8 像素块动态显示当前 `k` 和 `c = b^k mod n` 的值
   - **颜色标记**：
     - 红色框：当前计算的 `k`
     - 绿色：`c=0`（Kind1）
     - 蓝色：`c=1`（Kind2）
     - 黄色：`c=n-1`（Kind3）

2. **音效触发**：  
   - 每次计算播放 "blip" 音效（类似 FC 游戏按键音）
   - 发现解时播放 "胜利" 音效（不同音调区分三种情况）
   - 无解时播放低沉音效

3. **Canvas 动画流程**：  
   ```plaintext
   [初始化] → [k=1, c=1] → 计算 c = (c*b)%n → 检测条件 → 高亮结果 → 循环或终止
   ```

#### 复古游戏化设计
- **背景**：16色像素风格，模仿 FC 计算器界面  
- **控制面板**：  
  - 按钮：Start / Pause / Step  
  - 速度滑块：调整计算步频（1x/2x/4x）  
- **积分系统**：  
  - 每步消耗 1 点能量，找到解奖励 100 分  
  - 连击奖励：连续快速解题获得倍率加成  

---

### 同类型题与推荐

1. **快速幂模算**  
   - 洛谷 P1226 【模板】快速幂 | 取余运算

2. **同余方程求解**  
   - 洛谷 P1061 [NOIP2012 提高组] 同余方程

3. **数位分组处理**  
   - 洛谷 P1516 [NOIP2010 提高组] 青蛙的约会

---

### 个人心得摘录

> **FFTotoro 调试经历**：  
> 最初未考虑 `c` 溢出问题，改用 `long long` 后通过。  
> **教训**：模算中每一步都需取模，避免数值过大。

> **Vitamin_B 顿悟**：  
> 发现当 `b` 和 `n` 不互质时，Kind2 和 Kind3 可能不存在解，但 Kind1 仍可能有效。  
> **启发**：优先检测 Kind1 可加速某些案例。

---

**可视化示例代码（JS 伪代码）**：
```javascript
// 绘制像素化数值
function drawPixelValue(ctx, value, x, y, color) {
    const pixels = digitPixels[value]; // 预定义 0-9 的像素矩阵
    for(let i=0; i<8; i++) {
        for(let j=0; j<8; j++) {
            if(pixels[i][j]) ctx.fillStyle = color;
            else ctx.fillStyle = '#000';
            ctx.fillRect(x+j*4, y+i*4, 4, 4);
        }
    }
}
```

---
处理用时：85.79秒