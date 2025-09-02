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



## 算法分类
二分法

---

## 综合分析与结论

### 核心思路与难点
所有题解均基于几何推导与二分法。核心步骤为：
1. **几何建模**：通过相似三角形或勾股定理建立方程 $$\frac{1}{\sqrt{x^2-t^2}} + \frac{1}{\sqrt{y^2-t^2}} = \frac{1}{c}$$
2. **单调性分析**：方程左边关于街道宽度 t 单调递增，可二分求解
3. **二分实现**：初始区间 [0, min(x,y)]，通过判断函数值的正负调整区间

### 可视化设计思路
1. **动画流程**：
   - 初始化展示两梯子交叉的几何模型
   - 动态绘制当前二分区间 [l, r]，高亮中点 mid
   - 每次迭代显示计算出的交点高度 c' 与目标 c 的比较
   - 用颜色区分函数值大于/小于目标的情况（红色：c' > c，蓝色：c' < c）

2. **8位像素风格**：
   - 用 16 色调色板（类似 FC 红白机）绘制梯子、街道
   - 梯子长度变化时采用逐帧像素动画
   - 关键数值以复古字体显示在右侧面板

3. **音效设计**：
   - 步进时播放 "blip" 音效
   - 找到解时播放 "level-up" 音效
   - 背景循环 8-bit 风格 BGM

---

## 题解评分（≥4星）

### 1. Nepenthe（★★★★☆）
- **亮点**：推导最简洁，正确使用浮点精度处理（避免越界）
- **代码**：明确终止条件 `r-l>1e-5`，函数封装清晰
- **不足**：缺少几何图示说明

### 2. 追梦_Chen（★★★★☆）
- **亮点**：公式变形为乘法形式，判断条件直接对应几何意义
- **代码**：使用 100 次迭代确保收敛，适合极端精度场景
- **不足**：变量命名可优化（如 `w` 改为 `t`）

### 3. 0x00AC3375（★★★★☆）
- **亮点**：完整数学推导，正确分析函数单调性
- **代码**：使用 `1e-6` 安全偏移处理右边界
- **特色**：探讨牛顿法失败原因，体现深度思考

---

## 最优思路提炼
1. **几何关系转换**：通过相似三角形建立方程，避免复杂积分/微分
2. **二分条件优化**：将方程转换为 $$\frac{c}{\sqrt{x^2-t^2}} + \frac{c}{\sqrt{y^2-t^2}} > 1$$ 直接判断
3. **浮点处理技巧**：
   ```cpp
   while(r-l > 1e-5) { // 精度控制优于固定次数迭代
       mid = l + (r-l)/2; // 防溢出写法
       if(calc(mid)) r=mid; 
       else l=mid;
   }
   ```

---

## 同类题目推荐
1. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)
2. [P1902 刺杀大使](https://www.luogu.com.cn/problem/P1902)
3. [P1314 聪明的质监员](https://www.luogu.com.cn/problem/P1314)

---

## 核心代码实现
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

double x, y, c;

bool check(double t) {
    double a = sqrt(x*x - t*t);
    double b = sqrt(y*y - t*t);
    return (a*b) < c*(a + b); // 乘法形式避免除零风险
}

int main() {
    while(~scanf("%lf%lf%lf", &x, &y, &c)) {
        double l = 0, r = min(x, y);
        for(int i=0; i<100; ++i) { // 固定100次保证精度
            double mid = (l + r) / 2;
            check(mid) ? l = mid : r = mid;
        }
        printf("%.3f\n", l);
    }
    return 0;
}
```

---

## 可视化代码片段（JS）
```javascript
class LadderVisualizer {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.palette = ['#000', '#F00', '#0F0', '#00F', '#FF0', '#0FF', '#F0F', '#FFF'];
    }
    
    drawState(t, c_calc) {
        this.ctx.fillStyle = this.palette[7];
        this.ctx.fillRect(0, 0, 256, 192);
        
        // 绘制梯子
        this.ctx.strokeStyle = this.palette[1];
        this.ctx.beginPath();
        this.ctx.moveTo(10, 190);
        this.ctx.lineTo(10 + t*10, 190 - Math.sqrt(x*x - t*t)*10);
        this.ctx.stroke();
        
        // 显示数值
        this.ctx.fillStyle = this.palette[0];
        this.ctx.font = '8px "PixelFont"';
        this.ctx.fillText(`t:${t.toFixed(3)}`, 160, 20);
    }
}
```

---
处理用时：272.39秒