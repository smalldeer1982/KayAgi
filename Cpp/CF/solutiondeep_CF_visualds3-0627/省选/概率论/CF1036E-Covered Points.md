# 题目信息

# Covered Points

## 题目描述

You are given $ n $ segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with integer coordinates, which are covered by at least one segment.

## 说明/提示

The image for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/328bc786470ca0c6c881c66bf4ab063a98d10f53.png)Several key points are marked blue, the answer contains some non-marked points as well.

The image for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/eec87126bd479256c1ebc7932fb835380371e1c1.png)

## 样例 #1

### 输入

```
9
0 0 4 4
-1 5 4 0
4 0 4 4
5 2 11 2
6 1 6 7
5 6 11 6
10 1 10 7
7 0 9 8
10 -1 11 -1
```

### 输出

```
42
```

## 样例 #2

### 输入

```
4
-1 2 1 2
-1 0 1 0
-1 0 0 3
0 3 1 0
```

### 输出

```
7
```

# AI分析结果



---

## **算法分类**
计算几何

---

## **题解思路与解决难点**

### **核心思路**
1. **整点计数**：每条线段的整点数为 `gcd(Δx, Δy) + 1`。
2. **交点去重**：两两线段求交，记录全局唯一交点。
3. **贡献计算**：每条线段贡献值为 `自身点数 - 交点数`，最后加上全局交点总数。

### **解决难点**
- **整数坐标交点**：避免浮点运算，通过参数方程联立求解整数解。
- **范围判断**：确保交点在线段有效范围内。
- **去重存储**：使用 `set<P>` 记录交点和全局唯一点。

### **对比分析**
- **nekko**：显式两两求交，全局去重，逻辑清晰但需 O(n²) 时间。
- **紊莫**：动态处理线段，可能减少重复计算但实现复杂。

---

## **题解评分 ≥4星**
1. **nekko（5星）**  
   - **亮点**：完整数学推导、整数参数化解法、高效去重。
   - **代码可读性**：结构清晰，注释详细。
   - **关键代码**：参数方程联立与范围检查。

---

## **最优思路提炼**
- **关键公式**：线段整点数 = gcd(Δx, Δy) + 1。
- **交点计算**：参数方程联立，扩展欧几里得求解。
- **去重技巧**：使用集合存储交点，避免重复。

---

## **类似题目**
1. **P2785** 物理穿透（线段交点统计）
2. **P1224** 向量内积（几何性质分析）
3. **P1356** 计算几何（覆盖区域统计）

---

## **个人心得摘录**
- **调试技巧**：将线段参数化为 `x = x0 + k*u` 避免浮点误差。
- **数学推导**：联立方程时需处理分母为 0 或整除问题。

---

## **可视化设计**
### **动画方案**
1. **线段绘制**：在 Canvas 上用不同颜色绘制所有线段。
2. **整点高亮**：用像素块标记线段上的所有整点（绿色）。
3. **交点闪烁**：两两求交时，交点变为红色并闪烁。
4. **全局统计**：右侧面板实时显示总点数。

### **复古风格**
- **8位调色板**：线段用 8 种基础色，整点用 2x2 像素块。
- **音效设计**：
  - 线段绘制：8-bit "哔"声。
  - 发现交点：短促上升音调。
  - 完成计算：经典 FC 过关音效。

### **交互功能**
- **步进控制**：按空格键单步执行两两求交过程。
- **自动模式**：AI 自动执行，速度可调（1x/2x/5x）。

---

## **核心代码实现**
```cpp
// 线段参数化解交点的核心逻辑
P get(LINE a, LINE b) {
    ll x0 = a.a.x, y0 = a.a.y;
    ll u0 = (a.b.x - x0) / a.d, v0 = (a.b.y - y0) / a.d;
    ll x1 = b.a.x, y1 = b.a.y;
    ll u1 = (b.b.x - x1) / b.d, v1 = (b.b.y - y1) / b.d;

    // 解联立方程：x0 + k0*u0 = x1 + k1*u1
    //             y0 + k0*v0 = y1 + k1*v1
    ll numerator = (y1 - y0)*u0 - (x1 - x0)*v0;
    ll denominator = u1*v0 - v1*u0;
    if (denominator == 0 || numerator % denominator != 0) 
        return fl; // 无解
    ll k1 = numerator / denominator;

    // 计算交点并检查范围
    ll x = x1 + k1*u1, y = y1 + k1*v1;
    if (in(x, a.a.x, a.b.x) && in(y, a.a.y, a.b.y) &&
        in(x, b.a.x, b.b.x) && in(y, b.a.y, b.b.y)) {
        return {x, y};
    }
    return fl;
}
```

---

## **结论**
通过数学推导与集合去重，高效解决整数点覆盖问题，可视化设计可直观展示算法流程。

---
处理用时：71.37秒