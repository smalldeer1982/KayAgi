# 题目信息

# A Problem about Polyline

## 题目描述

There is a polyline going through points $ (0,0)–(x,x)–(2x,0)–(3x,x)–(4x,0)–...-(2kx,0)–(2kx+x,x)–... $ .

We know that the polyline passes through the point $ (a,b) $ . Find minimum positive value $ x $ such that it is true or determine that there is no such $ x $ .

## 说明/提示

You can see following graphs for sample 1 and sample 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/abf33c2e979ad11f626e45babf5d2a8a224a3964.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/567201d8db120e4f8136d5be265b91eca027e0d4.png)

## 样例 #1

### 输入

```
3 1
```

### 输出

```
1.000000000000
```

## 样例 #2

### 输入

```
1 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 1
```

### 输出

```
1.250000000000
```

# AI分析结果



# 算法分类
几何

# 题解思路与难点分析
题目要求找到使折线经过点 $(a,b)$ 的最小正数 $x$。核心思路为：

1. **无解条件**：当 $a < b$ 时无解，因为折线最高点纵坐标为 $x$，必须满足 $b \leq x$。
2. **两种情况分析**：
   - **下降段**：点 $(a,b)$ 位于斜率为 $-1$ 的线段上，对应直线方程为 $x+y=a+b$，与 $x$ 轴交点为 $(a+b, 0)$。
   - **上升段**：点位于斜率为 $1$ 的线段上，对应直线方程为 $x-y=a-b$，交点为 $(a-b, 0)$。
3. **数学推导**：
   - 交点横坐标必须为 $2kx$，其中 $k$ 为周期数。
   - $x$ 的最小值为 $\frac{y}{2k}$，需满足 $x \geq b$，解得 $k \leq \left\lfloor \frac{y}{2b} \right\rfloor$。
   - **关键优化**：下降段对应的解 $\frac{a+b}{2k}$ 总是小于或等于上升段的解，因此只需计算下降段的情况。

# 题解评分（≥4星）
1. **作者 XL4453（5星）**  
   - 思路清晰，通过数学证明得出下降段解最优，代码简洁高效。
   - 代码直接计算 $\frac{a+b}{2\left\lfloor \frac{a+b}{2b} \right\rfloor}$，避免冗余计算。
   ```cpp
   printf("%.12lf", (a+b)/(2.0*((a+b)/(2*b))));
   ```

2. **作者 czh___（4星）**  
   - 代码简洁，正确实现核心逻辑，但未明确说明数学优化。
   ```cpp
   printf("%.9lf", (a+b)/(2.0*((a+b)/(2*b))));
   ```

# 最优思路提炼
- **核心公式**：$x = \frac{a+b}{2k}$，其中 $k = \left\lfloor \frac{a+b}{2b} \right\rfloor$。
- **优化关键**：下降段解 $\frac{a+b}{2k}$ 始终最优，无需考虑上升段。

# 同类型题思路
几何问题中，常通过分析点所在的线段方程与周期性结构，结合极值推导求解参数。类似题目通常涉及：
1. 直线方程与交点计算。
2. 周期性结构的数学建模。
3. 极值条件的最优化处理。

# 推荐题目
1. **P1357 盒子**（几何，周期性结构）
2. **CF1025C**（几何变换与周期性）
3. **P1492 分形之城**（坐标变换与递归几何）

# 可视化算法分析
**动画设计**：
1. **折线绘制**：展示折线从原点出发，交替上升和下降。
2. **目标点标记**：高亮点 $(a,b)$，显示其所在的下降段。
3. **交点计算**：动态绘制与 $x$ 轴交点 $(a+b, 0)$，标出周期数 $k$。
4. **公式推导**：逐步显示 $k = \left\lfloor \frac{a+b}{2b} \right\rfloor$ 和 $x = \frac{a+b}{2k}$ 的计算过程。

**复古像素风格**：
- **Canvas 绘制**：8-bit 像素风格折线，目标点用闪烁方块表示。
- **音效**：计算完成时播放“通关”音效，错误时播放“失败”音效。
- **自动演示**：模拟折线延伸，自动暂停在关键步骤并高亮公式。

# 代码片段（核心逻辑）
```cpp
#include <cstdio>
int main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    if (a < b) printf("-1");
    else printf("%.12lf", (a + b) / (2.0 * ((a + b) / (2 * b))));
    return 0;
}
```

---
处理用时：279.84秒