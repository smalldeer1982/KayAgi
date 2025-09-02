# 题目信息

# Line

## 题目描述

A line on the plane is described by an equation $ Ax+By+C=0 $ . You are to find any point on this line, whose coordinates are integer numbers from $ -5·10^{18} $ to $ 5·10^{18} $ inclusive, or to find out that such points do not exist.

## 样例 #1

### 输入

```
2 5 3
```

### 输出

```
6 -3
```

# AI分析结果



# 算法分类：扩展欧几里得算法

---

## 题解思路与核心难点
### 核心算法流程
1. **方程转换**：将直线方程 $Ax+By+C=0$ 转换为标准线性方程 $Ax+By=-C$
2. **裴蜀定理应用**：若 $\gcd(A,B) \nmid C$ 则无解
3. **扩展欧几里得求解**：
   - 求 $ax+by=\gcd(a,b)$ 的特解 $(x_0,y_0)$
   - 通过缩放得到原方程解：$x = x_0 \cdot (-C/d),\ y = y_0 \cdot (-C/d)$
4. **边界处理**：验证解的数值范围是否在 $[-5e^{18},5e^{18}]$

### 解决难点
- **负数处理**：需正确处理参数符号，如将 $-C$ 代入计算
- **数据溢出**：必须使用 `long long` 类型存储变量
- **递归推导**：理解 exgcd 递归过程中解的递推关系式

---

## 题解评分（≥4星）
### Crab_Dave（⭐⭐⭐⭐⭐）
- **亮点**：完整推导扩展欧几里得原理，包含斐蜀定理证明和通解公式
- **代码规范**：全局变量与递归实现清晰，注释强调 `long long` 必要性
- **实践指导**：通过 `c=-c` 明确处理符号问题

### Dog_Two（⭐⭐⭐⭐）
- **结构清晰**：分模块讲解算法定义、方程求解和代码实现
- **模板复用**：提供可复用的线性方程求解函数 `linear_Eqa`
- **不足**：未深入解释特解到通解的转换过程

### HoshiuZ（⭐⭐⭐⭐）
- **极简实现**：仅用 15 行代码完成核心逻辑
- **符号处理**：直接在输出阶段乘以 $-1$ 简化计算
- **缺点**：缺少对递归步骤的注释说明

---

## 最优思路提炼
### 关键技巧
```cpp
// 递归终止条件：b=0 时 x=1, y=0
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return; }
    exgcd(b, a % b, y, x); // 交换 x,y 简化计算
    y -= a / b * x;        // 递推修正系数
}

// 调用示例
ll d = exgcd(A, B, x, y);
if (-C % d) cout << -1;    // 无解判断
x *= (-C) / d; y *= (-C) / d;
```

### 思维突破点
- **逆向推导**：从欧几里得算法的终止状态反推初始解
- **缩放原理**：将 $\gcd$ 相关解线性缩放至目标方程
- **符号统一**：通过方程变形避免负数模运算问题

---

## 同类题目推荐
1. **P1082 [NOIP2012 提高组] 同余方程**  
   （求解 $ax \equiv 1 \pmod{b}$ 的逆元）
2. **P1516 青蛙的约会**  
   （线性同余方程应用，处理环形相遇问题）
3. **P5656 二元一次不定方程**  
   （求所有解并限制解的范围）

---

## 可视化与交互设计
### 动画设计
```html
<canvas id="exgcd-canvas" width="600" height="400"></canvas>
<script>
// 伪代码示例：展示递归步骤与系数变化
let steps = [
    { a: 20, b: 32, x: 1, y: 0, depth: 0 },
    { a: 32, b: 20, x: 0, y: 1, depth: 1 },
    // ... 递归过程数据
];

function drawStep(step) {
    ctx.fillStyle = "#8B0000"; // 暗红色复古像素
    ctx.fillText(`exgcd(${step.a}, ${step.b})`, 10, 20 + 30*step.depth);
    ctx.fillText(`x=${step.x}, y=${step.y}`, 200, 20 + 30*step.depth);
}
</script>
```

### 交互特性
- **像素风格**：16 色调色板，网格化显示递归深度
- **音效设计**：
  - **递归调用**：播放 8-bit 风格 "beep" 声
  - **解更新**：成功时播放上升音阶
- **自动演示**：按空格键逐步执行，ESC 重置

---

## 代码实现（C++）
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    ll a, b, c, x, y;
    cin >> a >> b >> c;
    ll d = exgcd(a, b, x, y);
    if ((-c) % d) cout << -1;
    else cout << x*(-c)/d << " " << y*(-c)/d;
    return 0;
}
```

---
处理用时：73.70秒