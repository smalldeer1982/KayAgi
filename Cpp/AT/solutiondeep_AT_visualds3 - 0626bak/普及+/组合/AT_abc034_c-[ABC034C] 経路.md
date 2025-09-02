# 题目信息

# [ABC034C] 経路

## 题目描述

有一个 $W$ 行 $H$ 列的网格图（$2 \leq W,H \leq 10^5$），其中第 $i$ 行第 $j$ 列的坐标为 $(i,j)$。

现在有一个人想从起点 $(1,1)$ 走到终点 $(W,H)$，已知他每次可以从网格 $(i,j)$ 走向 $(i+1,j)$ 或 $(i,j+1)$。现在请你求出，他从起点走到终点的路线个数为多少。

由于这个数可能很大，因此你只要输出路线个数对 $10^9 + 7$ 取模的结果即可。

## 样例 #1

### 输入

```
4 3```

### 输出

```
10```

## 样例 #2

### 输入

```
123 456```

### 输出

```
210368064```

# AI分析结果



---

## 唯一算法分类
组合数学

---

## 综合分析与结论

### 核心思路与难点
所有题解均基于组合数学公式：  
总路径数 = $C(W+H-2, W-1) \mod 10^9+7$  
**关键难点**在于：  
1. 组合数的快速计算（直接计算阶乘会溢出）  
2. 模运算下的除法处理（需用逆元转换为乘法）  

### 算法实现要点
所有题解均采用**预处理阶乘与逆元阶乘**的优化方法：  
1. 预处理阶乘数组 `fact[]` 和逆元阶乘数组 `inv_fact[]`  
2. 组合数公式转换为：  
   $$ C(n,k) = fact[n] \times inv\_fact[k] \times inv\_fact[n-k] \mod MOD $$  
3. 逆元计算采用递推法（复杂度 $O(n)$）或费马小定理（复杂度 $O(n \log MOD)$）  

### 题解对比亮点
- **残阳如血**：最清晰的逆元预处理过程，代码可读性极佳  
- **jzjr**：使用费马小定理求逆元，适合理解逆元基础概念  
- **qfy123**：代码结构简洁，预处理与计算分离明确  

---

## 题解清单（4星以上）

1. **残阳如血（5星）**  
   - **亮点**：逆元递推预处理、变量命名规范、代码模块化  
   - **关键代码**：  
     ```cpp
     inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;  // 递推逆元
     fact[i] = fact[i-1] * i % MOD;              // 递推阶乘
     inv_fact[i] = inv_fact[i-1] * inv[i] % MOD;  // 递推逆元阶乘
     ```

2. **jzjr（4星）**  
   - **亮点**：费马小定理推导详细，适合数学基础较弱的读者  
   - **关键代码**：  
     ```cpp
     ni[tot] = ksm(jc[tot], mod-2, mod);  // 费马小定理求逆元
     ```

3. **qfy123（4星）**  
   - **亮点**：代码精简，预处理与计算逻辑明确  
   - **关键代码**：  
     ```cpp
     return f[x] * ksm(f[y], mod-2) % mod * ksm(f[x-y], mod-2) % mod;
     ```

---

## 最优思路与技巧

### 核心代码实现
```cpp
// 预处理逆元与阶乘
void init() {
    inv[0] = inv[1] = 1;
    for(int i=2; i<MAXN; ++i) 
        inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
    
    fact[0] = inv_fact[0] = 1;
    for(int i=1; i<MAXN; ++i) {
        fact[i] = fact[i-1] * i % MOD;
        inv_fact[i] = inv_fact[i-1] * inv[i] % MOD;
    }
}

// 计算组合数
lint C(int n, int m) {
    return fact[n] * inv_fact[m] % MOD * inv_fact[n-m] % MOD;
}
```

### 关键技巧
1. **逆元递推公式**：  
   $$ inv[i] = -\left\lfloor \frac{MOD}{i} \right\rfloor \times inv[MOD\%i] \mod MOD $$  
   避免递归计算，复杂度 $O(n)$  
2. **阶乘逆元预处理**：  
   通过 `inv_fact[i] = inv_fact[i-1] * inv[i]` 实现线性计算  

---

## 相似题目推荐

1. **P3807 【模板】卢卡斯定理**  
   - 组合数取模的扩展，需处理更大的数值范围  
2. **AT_abc145_d Knight**  
   - 二维路径计数变种，需排除非法移动  
3. **CF1288C Two Arrays**  
   - 组合数应用变形，涉及非降序列计数  

---

## 可视化设计

### 动画方案（Canvas 实现）
```html
<canvas id="grid" width="600" height="400"></canvas>
<script>
const W = 4, H = 3; // 样例输入 4x3
const ctx = document.getElementById('grid').getContext('2d');
let path = [];

function drawGrid() {
    // 绘制网格线
    ctx.strokeStyle = '#888';
    for(let i=0; i<=W; i++) {
        ctx.beginPath();
        ctx.moveTo(i*100, 0);
        ctx.lineTo(i*100, 300);
        ctx.stroke();
    }
    for(let j=0; j<=H; j++) {
        ctx.beginPath();
        ctx.moveTo(0, j*100);
        ctx.lineTo(400, j*100);
        ctx.stroke();
    }
}

function drawPath(steps) {
    // 高亮当前路径
    let x = 0, y = 0;
    ctx.fillStyle = 'rgba(255,0,0,0.3)';
    steps.forEach(step => {
        if(step === 'R') x++;
        else y++;
        ctx.fillRect(x*100, (H-1-y)*100, 100, 100);
    });
}

// 自动演示所有路径（简化版）
let combo = 0;
function autoPlay() {
    const total = C(W+H-2, W-1);
    for(let i=0; i<total; i++) {
        setTimeout(() => {
            ctx.clearRect(0, 0, 600, 400);
            drawGrid();
            // 生成第i种路径（伪代码）
            const steps = generateSteps(i); 
            drawPath(steps);
            playSound('move'); // 移动音效
            combo++;
            if(combo % 5 === 0) playSound('combo');
        }, i*500);
    }
}
</script>
```

### 复古风格设计
- **像素色板**：红（#FF0000）、蓝（#0000FF）、灰（#808080）  
- **音效设计**：  
  - 移动：8-bit 短促 "beep"（Web Audio 合成）  
  - 连击：上升音阶序列  
  - 完成：经典 FC 过关音效  
- **积分系统**：每显示 5 条路径获得 +10 分连击奖励  

---

## 核心算法演示（GIF 动态图）
![组合数路径动画](https://via.placeholder.com/600x400/FF8888/000000?text=Dynamic+Path+Visualization)  
- **红色方块**：当前路径覆盖的网格  
- **绿色边框**：当前移动方向（右/下）  
- **右下角计数器**：已生成路径数 / 总路径数  

--- 

通过此设计，学习者可直观理解组合数的几何意义，同时通过音效与积分增强学习趣味性。

---
处理用时：107.25秒