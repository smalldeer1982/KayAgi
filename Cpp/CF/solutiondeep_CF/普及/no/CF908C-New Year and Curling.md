# 题目信息

# New Year and Curling

## 题目描述

Carol is currently curling.

She has $ n $ disks each with radius $ r $ on the 2D plane.

Initially she has all these disks above the line $ y=10^{100} $ .

She then will slide the disks towards the line $ y=0 $ one by one in order from $ 1 $ to $ n $ .

When she slides the $ i $ -th disk, she will place its center at the point $ (x_{i},10^{100}) $ . She will then push it so the disk’s $ y $ coordinate continuously decreases, and $ x $ coordinate stays constant. The disk stops once it touches the line $ y=0 $ or it touches any previous disk. Note that once a disk stops moving, it will not move again, even if hit by another disk.

Compute the $ y $ -coordinates of centers of all the disks after all disks have been pushed.

## 说明/提示

The final positions of the disks will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908C/d83c8ae09a1afba1002e3c764e58c1e7ac4abfee.png)In particular, note the position of the last disk.

## 样例 #1

### 输入

```
6 2
5 5 6 8 3 12
```

### 输出

```
2 6.0 9.87298334621 13.3370849613 12.5187346573 13.3370849613
```

# AI分析结果



# New Year and Curling

## 题目描述

Carol 正在进行冰壶比赛。

她在二维平面上有 $n$ 个半径为 $r$ 的冰壶盘。

初始时，所有冰壶盘都位于直线 $y=10^{100}$ 上方。

她将按顺序从第 $1$ 到第 $n$ 个冰壶盘，逐个沿直线 $y=0$ 方向滑动。

当滑动第 $i$ 个冰壶盘时，她会将其中心放置在 $(x_i, 10^{100})$ 点，然后向下推动使其 $y$ 坐标持续减小，$x$ 坐标保持不变。冰壶盘会在接触到直线 $y=0$ 或与之前停下的任意冰壶盘接触时停止运动。一旦停止，即使被其他冰壶盘撞击也不会再移动。

请计算所有冰壶盘停止后各圆心的 $y$ 坐标。

## 算法分类
数学

---

### 题解分析与结论
所有题解均采用数学模拟思路，核心在于利用勾股定理计算冰壶盘碰撞时的竖直高度差。关键步骤如下：
1. **几何关系判断**：当两圆相切时，圆心水平距离 $|x_i - x_j| \leq 2r$
2. **高度差计算**：通过 $\sqrt{(2r)^2 - (x_i - x_j)^2}$ 求得竖直方向增量
3. **贪心取最大值**：每个冰壶盘最终高度取所有可能碰撞情况中的最大值

---

### 高星题解推荐
1. **作者：_xbn（★★★★）**
   - **亮点**：详细图解辅助理解几何关系，代码完整处理边界条件
   - **核心代码**：
     ```cpp
     for(int i=1; i<=n; i++) {
         // 处理每个冰壶盘
         for(int j=1; j<i; j++) {
             if(abs(x[j] - x[i]) > 2*r) continue;
             double delta = sqrt(4*r*r - pow(x[j]-x[i],2));
             y[i] = max(y[i], y[j] + delta);
         }
     }
     ```

2. **作者：OIerZhang（★★★★）**
   - **亮点**：代码简洁高效，变量命名清晰易懂
   - **核心代码**：
     ```cpp
     for(int i=1; i<=n; i++) {
         y[i] = r; // 初始可能的最低高度
         for(int j=1; j<i; j++) {
             if(abs(x[j]-x[i]) > 2*r) continue;
             double delta = sqrt(4*r*r - (x[j]-x[i])*(x[j]-x[i]));
             y[i] = max(y[i], y[j] + delta);
         }
     }
     ```

---

### 关键思路总结
1. **几何建模**：将碰撞问题转化为圆心坐标的几何关系问题
2. **暴力枚举**：通过 $O(n^2)$ 遍历处理所有可能碰撞情况
3. **浮点精度处理**：使用 `sqrt` 和 `max` 确保计算精度与正确性

---

### 拓展与相似题目
1. [P1652 圆](https://www.luogu.com.cn/problem/P1652) - 判断点与圆的位置关系
2. [P1515 天堂的馈赠](https://www.luogu.com.cn/problem/P1515) - 几何形状的覆盖问题
3. [P2559 [AHOI2002]网络传输](https://www.luogu.com.cn/problem/P2559) - 几何应用与最优化问题

---

### 心得体会摘录
> "_xbn：看似复杂的物理运动，本质是初二几何的勾股定理应用。关键是将三维运动简化为二维几何问题"  
> "OIerZhang：注意浮点数比较时设置合理的精度容差，避免因精度丢失导致错误判断"

---
处理用时：157.67秒