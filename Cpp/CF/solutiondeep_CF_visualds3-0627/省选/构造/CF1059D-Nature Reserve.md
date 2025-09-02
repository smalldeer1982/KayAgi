# 题目信息

# Nature Reserve

## 题目描述

There is a forest that we model as a plane and live $ n $ rare animals. Animal number $ i $ has its lair in the point $ (x_{i}, y_{i}) $ . In order to protect them, a decision to build a nature reserve has been made.

The reserve must have a form of a circle containing all lairs. There is also a straight river flowing through the forest. All animals drink from this river, therefore it must have at least one common point with the reserve. On the other hand, ships constantly sail along the river, so the reserve must not have more than one common point with the river.

For convenience, scientists have made a transformation of coordinates so that the river is defined by $ y = 0 $ . Check whether it is possible to build a reserve, and if possible, find the minimum possible radius of such a reserve.

## 说明/提示

In the first sample it is optimal to build the reserve with the radius equal to $ 0.5 $ and the center in $ (0,\ 0.5) $ .

In the second sample it is impossible to build a reserve.

In the third sample it is optimal to build the reserve with the radius equal to $ \frac{5}{8} $ and the center in $ (\frac{1}{2},\ \frac{5}{8}) $ .

## 样例 #1

### 输入

```
1
0 1
```

### 输出

```
0.5```

## 样例 #2

### 输入

```
3
0 1
0 2
0 -3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2
0 1
1 1
```

### 输出

```
0.625```

# AI分析结果



# 算法分类  
**几何 + 二分查找**

---

## 题解思路与核心难点  
### 核心逻辑  
1. **问题转化**：所有点必须位于x轴同一侧，否则无解。  
2. **二分半径**：半径越大越容易满足条件，具有单调性。  
3. **区间交集检查**：对于每个候选半径r，计算每个点对应的圆心x坐标允许范围，取所有区间的交集。  

### 解决难点  
- **圆心范围推导**：利用勾股定理，圆心在直线y=r上，每个点约束圆心x坐标的范围为：  
  `x_i ± sqrt(r^2 - (r - y_i)^2)`  
  化简为：  
  `x_i ± sqrt(y_i * (2r - y_i))`  
- **精度处理**：通过足够次数的二分迭代（如500次）避免浮点误差，部分题解采用sqrt分解技巧优化精度。  
- **高效区间合并**：只需维护所有左端点最大值和右端点最小值，判断是否有交集。  

---

## 题解评分 (≥4星)  
### 1. 作者：Grisses（4.5星）  
- **亮点**：代码结构清晰，处理点坐标转换简洁，采用预处理绝对值统一处理点位置。  
- **优化**：通过 `sqrt(x*x - (a[i].y-x)*(a[i].y-x))` 分解计算避免精度损失。  

### 2. 作者：Mihari（4.5星）  
- **亮点**：数学推导简洁，直接使用 `sqrt(y[i]*(2r - y[i]))` 计算区间，避免中间误差。  
- **代码**：通过1000次二分迭代确保精度，逻辑紧凑。  

### 3. 作者：piuke（4星）  
- **亮点**：详细注释和调试经验分享，适合初学者理解。  
- **技巧**：预处理点坐标后直接二分，代码可读性强。  

---

## 最优思路提炼  
1. **二分半径框架**：通过二分答案将几何问题转化为可行性检查问题。  
2. **区间交集判定**：每个点约束圆心x坐标的范围，合并所有区间判断是否存在交集。  
3. **数学化简**：将圆心坐标约束公式化简为 `sqrt(y_i*(2r - y_i))`，减少浮点运算误差。  

---

## 同类题目推荐  
1. **P2113 最小圆覆盖**（几何+随机增量法）  
2. **CF1661D Maximum And Queries**（二分答案+贪心）  
3. **P2600 瞭望塔**（几何+半平面交）  

---

## 代码片段（核心逻辑）  
```cpp
bool check(double r) {
    double L = -1e18, R = 1e18;
    for (int i = 1; i <= n; ++i) {
        if (2 * r < y[i]) return false; // 点高于直径
        double dis = sqrt(y[i] * (2 * r - y[i])); // 关键公式
        L = max(L, x[i] - dis);
        R = min(R, x[i] + dis);
    }
    return L <= R;
}
```

---

## 可视化设计  
### 动画方案  
1. **像素化坐标系**：使用8-bit风格绘制x轴（绿色像素线）和候选圆（蓝色像素环）。  
2. **动态区间展示**：每个点显示其约束的x区间（红色线段），交集区域高亮为黄色。  
3. **音效反馈**：  
   - 成功找到解时播放8-bit胜利音效（短促上升音阶）。  
   - 区间无交集时播放低音提示。  

### 交互控制  
- **速度调节**：滑动条控制二分迭代速度（0.5x~5x）。  
- **单步执行**：按空格键逐次观察二分过程。  
- **自动演示**：AI模式自动完成二分流程，展示最终最小圆。  

### 复古效果  
- **Canvas绘制**：使用16色调色板，圆环用8x8像素块拼接。  
- **背景音乐**：循环播放FC风格的轻快芯片音乐。  

---

## 核心算法演示  
![Algorithm Demo](https://cdn.luogu.com.cn/upload/image_hosting/xjeu00ed.png)  
*动态展示二分过程中候选半径对应的圆心区间交集变化，最终收敛至最小半径。*

---
处理用时：53.13秒