# 题目信息

# [ICPC 2014 WF] Crane Balancing

## 题目描述

无论在哪里进行大规模的建筑施工，你都会看到起重机在进行吊装。人们很少会想到起重机是多么奇妙的工程范例：一个（相对）重量较轻的结构可以举起更重的负载。但即使是建造得最好的起重机也可能对它们能举起的重量有一个限制。

起重机制造商协会（ACM）需要一个程序来计算起重机可以举起的重量范围。由于起重机是对称的，ACM 工程师决定只考虑每个起重机的截面，可以视为一个位于 $x$ 轴上的多边形。

图 1 显示了第一个样例输入中起重机的截面。假设每 $1 \\times 1$ 单位的起重机截面重 1 千克，所要举起的重量将附着在多边形的一个顶点（图 1 中箭头所示）。编写一个程序来确定起重机不会向左或向右倾覆的重量范围。

## 说明/提示

时间限制：1000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
50 50
0 50
0 0
30 0
30 30
40 40
50 40
```

### 输出

```
0 .. 1017
```

## 样例 #2

### 输入

```
7
50 50
0 50
0 0
10 0
10 30
20 40
50 40
```

### 输出

```
unstable
```

# AI分析结果



---

## 算法分类
几何

---

## 题解思路与算法分析

### 核心思路
1. **几何性质分析**：将多边形分解为三角形计算质心位置
2. **物理平衡条件**：通过力矩平衡方程求解重量范围
3. **分类讨论**：根据质心与支撑点的位置关系分6种情况处理

### 关键公式推导
多边形质心公式：  
$$\overrightarrow{OG} = \frac{\sum (\overrightarrow{OA_i} + \overrightarrow{OA_{i+1}} + \overrightarrow{OA_n}) \cdot m_i}{3\sum m_i}$$  
其中 $m_i$ 为三角形面积（通过叉积计算）

重量范围方程（示例情况）：  
当原质心在支撑区间左侧时，最小重量满足：  
$$(r-x)m_{min} = (x_0-r)M$$

---

## 题解评分（≥4星）

### FangZeLi 题解（★★★★☆）
- **亮点**：代码结构清晰，叉积计算优化，边界处理完善
- **不足**：公式推导部分不够详细

### wangyizhi 题解（★★★★☆）
- **亮点**：完整推导重心公式，物理模型解释透彻
- **不足**：缺少完整代码实现

---

## 最优技巧提炼

1. **叉积快速计算面积**：  
   用 `(A-B) × (C-B)` 计算三角形面积，避免浮点误差

2. **质心合成公式**：  
   通过加权平均将三角形质心合并为多边形质心

3. **平衡条件转化**：  
   将几何稳定性问题转化为不等式约束的数学问题

---

## 同类题目推荐
1. P1359 计算几何（多边形面积）
2. CF598C 向量极角排序
3. UVA1111 多边形重心计算

---

## 可视化设计

### 像素化动画方案
```javascript
// 初始化Canvas（400x300 像素画布）
const canvas = document.getElementById('crane-canvas');
const ctx = canvas.getContext('2d');

// 颜色方案（16色复古调色板）
const COLORS = {
  base: '#3C3C3C',    // 起重机主体
  support: '#FF5555', // 支撑区间
  centroid: '#55FF55',// 质心
  load: '#5555FF'     // 挂载点
};

function drawPolygon(points) {
  ctx.fillStyle = COLORS.base;
  ctx.beginPath();
  points.forEach((p,i) => {
    const x = p.x * 4, y = 200 - p.y * 4; // 缩放坐标
    if(i === 0) ctx.moveTo(x, y);
    else ctx.lineTo(x, y);
  });
  ctx.fill();
}

function updateAnimation(loadMass) {
  // 计算当前质心位置
  const newCentroid = calculateNewCentroid(loadMass);
  
  // 绘制支撑区间
  ctx.fillStyle = COLORS.support;
  ctx.fillRect(l*4, 196, (r-l)*4, 4);
  
  // 绘制动态质心
  ctx.fillStyle = COLORS.centroid;
  ctx.fillRect(newCentroid.x*4-2, newCentroid.y*4-2, 4, 4);
}
```

### 交互功能
1. **滑块控制**：实时调节负载质量观察质心移动
2. **音效反馈**：质心超出支撑区间时播放警报音
3. **自动推导模式**：逐步显示叉积计算、质心合成过程

---

## 核心代码实现
```cpp
// 计算多边形质心核心片段
for (int i = 1; i <= n - 2; i++) {
    double area = (poly[i] - poly[n]) % (poly[i + 1] - poly[n]);
    total_area += area;
    centroid += (poly[i] + poly[i + 1] + poly[n]) * area;
}
centroid = centroid / total_area / 3.0;
total_mass = fabs(total_area / 2);

// 平衡条件判断
if (centroid.x < l) {
    double min_w = (l - centroid.x) * total_mass / (load_point.x - l);
    // ...其他条件处理
}
```

---

## 个人心得
调试时发现浮点精度处理至关重要，需引入EPS进行容错比较。例如当挂载点与支撑端点重合时，必须通过sgn函数判断符号而非直接比较大小。

---
处理用时：60.14秒