# 题目信息

# Crossed Ladders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1507

[PDF](https://uva.onlinejudge.org/external/105/p10566.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/04bd930627e82cc986e14b41bdaa0b69d1b37635.png)

## 样例 #1

### 输入

```
30 40 10
12.619429 8.163332 3
10 10 3
10 10 1```

### 输出

```
26.033
7.000
8.000
9.798```

# AI分析结果



## 唯一算法分类
**二分查找**

---

## 综合分析与结论

### 核心思路与难点
1. **数学建模**：通过相似三角形或勾股定理推导方程 $$\frac{1}{\sqrt{x^2-t^2}} + \frac{1}{\sqrt{y^2-t^2}} = \frac{1}{c}$$，其中 $t$ 为街道宽度。
2. **单调性分析**：方程左边关于 $t$ 单调递增，当 $t$ 增大时，分母 $\sqrt{x^2-t^2}$ 和 $\sqrt{y^2-t^2}$ 减小，导致两项的倒数之和增大。
3. **二分策略**：在 $t \in [0, \min(x,y)]$ 区间内进行二分，通过比较当前 $t$ 对应的计算结果与目标值 $c$ 调整边界。

### 可视化设计要点
- **动态二分演示**：显示当前 $t$（街道宽度）对应的梯子倾斜状态，用红色线段表示梯子，蓝色线表示交点高度。
- **关键变量高亮**：实时显示 $\sqrt{x^2-t^2}$ 和 $\sqrt{y^2-t^2}$ 的计算值，用不同颜色标注是否满足条件。
- **像素风格动画**：8位像素风格的梯子图形，使用绿色像素块表示当前 $t$ 值，黄色箭头指示二分方向（左/右移动）。
- **音效交互**：每次二分迭代时播放 "beep" 音效，找到解时播放 8-bit 胜利旋律。

---

## 题解清单 (≥4星)

### 1. Nepenthe (★★★★☆)
- **关键亮点**：通过倒数之和与 $1/c$ 直接比较，逻辑简洁；代码中采用防溢出的 `mid = l + (r - l)/2`。
- **代码片段**：
```cpp
double work(double t) {
    return 1 / sqrt(x*x - t*t) + 1 / sqrt(y*y - t*t);
}
if (work(mid) > (1/c)) r = mid;  // 单调递增时调整右边界
```

### 2. HUTEHE (★★★★☆)
- **关键亮点**：详细的数学推导配图，帮助理解几何关系；将方程转换为乘法形式避免精度问题。
- **代码片段**：
```cpp
bool check(double m) {
    double h1 = sqrt(x*x - m*m), h2 = sqrt(y*y - m*m);
    return (h1*h2) < (h1*c + h2*c);  // 等价于 1/h1 + 1/h2 > 1/c
}
```

### 3. 追梦_Chen (★★★★☆)
- **关键亮点**：通过变形方程简化判断条件，代码中直接比较 `a*b >= c*(a+b)`，减少浮点运算次数。
- **代码片段**：
```cpp
if (a*b >= c*(a+b)) return false;  // t 太小需要增大
```

---

## 最优思路提炼
1. **核心方程**：$$\frac{1}{\sqrt{x^2-t^2}} + \frac{1}{\sqrt{y^2-t^2}} = \frac{1}{c}$$
2. **单调性利用**：左边随 $t$ 单调递增 → 二分时若计算结果 > $1/c$，说明 $t$ 太大需减小右边界。
3. **精度处理**：采用固定迭代次数（如 100 次）或设定极小精度阈值（如 `1e-5`）终止循环。

---

## 类似题目推荐
1. **P1024** - 一元三次方程求解（二分求根）
2. **P3743** - kotori的设备（二分时间判断可行性）
3. **P4365** - [SDOI2016] 猜数游戏（二分策略与数学结合）

---

## 代码实现（核心逻辑）
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

double x, y, c;
bool check(double t) {
    double a = sqrt(x*x - t*t), b = sqrt(y*y - t*t);
    return (a * b) / (a + b) > c;  // 等价于 1/a + 1/b > 1/c
}

int main() {
    while (~scanf("%lf%lf%lf", &x, &y, &c)) {
        double l = 0, r = min(x, y);
        for (int i = 0; i < 100; ++i) {  // 固定100次迭代确保精度
            double mid = (l + r) / 2;
            check(mid) ? l = mid : r = mid;
        }
        printf("%.3lf\n", l);
    }
    return 0;
}
```

---

## 可视化算法演示（伪代码描述）
```javascript
// 在Canvas上绘制二分过程
function draw(t) {
    ctx.clearRect(0, 0, width, height);
    // 绘制梯子
    drawLine(0, height, t, 0, 'red');        // 左梯子
    drawLine(width, height, width - t, 0, 'blue'); // 右梯子
    // 计算交点高度
    let a = Math.sqrt(x*x - t*t), b = Math.sqrt(y*y - t*t);
    let intersectY = (a * b) / (a + b);
    // 绘制交点
    drawCircle(t/2, intersectY, 'yellow');
    // 更新显示当前t和误差
    updateDisplay(`t=${t.toFixed(3)}, Error=${Math.abs(intersectY - c).toFixed(6)}`);
}

// 二分循环（自动播放）
let l = 0, r = Math.min(x, y);
setInterval(() => {
    let mid = (l + r) / 2;
    check(mid) ? l = mid : r = mid;
    draw(mid);
    if (r - l < 1e-5) playVictorySound(); // 达到精度播放音效
}, 500);
```

**交互设计**：  
- 方向键←→手动调整 $t$ 观察变化  
- 空格键切换自动/手动模式  
- 8-bit音效：移动时"beep"，成功时播放《超级玛丽》过关旋律

---
处理用时：86.33秒