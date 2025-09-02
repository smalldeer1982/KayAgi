# 题目信息

# Hexagons

## 题目描述

Ayrat is looking for the perfect code. He decided to start his search from an infinite field tiled by hexagons. For convenience the coordinate system is introduced, take a look at the picture to see how the coordinates of hexagon are defined:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615E/7260dcf1ee40fd1194e895987c69d1d7c92f50b5.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615E/91f722e14e3f2875c1cec2e05543b6613c3b2f75.png) Ayrat is searching through the field. He started at point $ (0,0) $ and is moving along the spiral (see second picture). Sometimes he forgets where he is now. Help Ayrat determine his location after $ n $ moves.

## 样例 #1

### 输入

```
3
```

### 输出

```
-2 0
```

## 样例 #2

### 输入

```
7
```

### 输出

```
3 2
```

# AI分析结果


### 💡 Kay的C++算法解析：Hexagons 深入学习指南 💡  
**引言**  
今天我们来分析六边形网格螺旋移动问题。本题要求计算从原点(0,0)出发沿六边形螺旋路径移动n步后的坐标。我们将通过数学建模和坐标变换技巧解决该问题。

---

## 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`数学建模与坐标变换`  

🗣️ **初步分析**：  
> 解决本题的关键在于发现螺旋移动的周期性规律。想象六边形螺旋像洋葱一样层层包裹——每层步数呈等差数列增长（6,12,18...）。通过**二分搜索**快速定位当前层数后，再根据剩余步数在6个方向分段计算坐标偏移。  
> - **核心难点**：准确推导6个移动方向的坐标变换公式及边界条件  
> - **可视化设计**：采用8位像素网格动画，用不同颜色箭头表示移动方向。每步移动时触发方向音效，层数切换时播放"升级"音效，坐标实时显示在像素屏幕顶部  

---

## 2. 精选优质题解参考  
**题解 (来源：OIer_ACMer)**  
* **点评**：该解法通过二分搜索高效确定螺旋层数（时间复杂度O(log n)），避免逐步模拟。亮点在于完整推导了6个移动方向的坐标变换规则。但变量命名（如yi, er, san）可读性较差，边界处理可通过枚举类型优化。  

---

## 3. 核心难点辨析与解题策略  
1. **层数定位的数学建模**  
   * **分析**：螺旋第k层总步数=3k(k-1)，需用二分搜索求解满足 ∑step ≤ n 的最大k值  
   * 💡 **学习笔记**：等差数列求和公式是处理环形增长模型的核心工具  

2. **方向分段计算**  
   * **分析**：将每层6条边编号（右上→左上→左→左下→右下→右），每条边移动规则不同：  
     - 右上：x+1, y+2  
     - 左：x-2, y不变  
     * 💡 **学习笔记**：方向编号需严格对应坐标轴变化  

3. **剩余步数映射**  
   * **分析**：计算res = n - 前(k-1)层总步数后，需判断res落在当前层哪条边上  
   * 💡 **学习笔记**：通过余数范围判定方向比角度计算更高效  

### ✨ 解题技巧总结  
- **数学优化**：用二分替代模拟降低O(n)→O(log n)  
- **方向封装**：建议用enum{UP_RIGHT, LEFT,...}取代魔数  
- **边界测试**：重点验证层切换点（如n=1,7,19）  

---

## 4. C++核心代码实现赏析  
**本题通用核心实现**  
```cpp
#include <iostream>
using namespace std;
typedef long long LL;

int main() {
    LL n; cin >> n;
    if(n == 0) { cout << "0 0"; return 0; }

    // 二分搜索层数k (满足 3k(k-1) < n)
    LL k = 1;
    for(LL l=0, r=1e9; l<=r; ){
        LL mid = (l+r)/2;
        if(3*mid*(mid+1) < n) { k=mid+1; l=mid+1; }
        else r=mid-1;
    }

    LL res = n - 3*k*(k-1);  // 当前层剩余步数
    LL x = 2*(k-1), y = 0;   // 当前层起点坐标

    // 方向分段计算
    const int dirs[6][2] = {{1,2},{-1,2},{-2,0},{-1,-2},{1,-2},{2,0}};
    int step_limit[6] = {1, k, k, k, k, k}; // 各方向最大步数

    for(int i=0; i<6; i++){
        if(res <= step_limit[i]) {
            x += dirs[i][0] * res;
            y += dirs[i][1] * res;
            break;
        }
        x += dirs[i][0] * step_limit[i];
        y += dirs[i][1] * step_limit[i];
        res -= step_limit[i];
    }
    cout << x << " " << y;
}
```
**代码解读概要**：  
1. 二分搜索确定螺旋层数k  
2. 计算当前层起点坐标(2(k-1), 0)  
3. 按6个方向顺序处理剩余步数，每个方向有特定坐标偏移量  
4. 方向数组`dirs`封装坐标变换规则，增强可读性  

---

## 5. 算法可视化：像素动画演示  
* **主题**：8位机风格《六边形探险者》  
* **核心演示**：  
  ![像素动画示意图](https://via.placeholder.com/400x200/36393f/ffffff?text=六边形螺旋动画)  
  **动画流程**：  
  1. 初始化黄色像素块表示起点(0,0)，网格线为灰色  
  2. 每移动一步：  
     - 当前格闪烁绿色 → 播放"滴"声  
     - 生成方向箭头(红色) → 播放对应方向音效  
     - 顶部LCD屏更新坐标：(x,y)  
  3. 层数切换时：  
     - 屏幕边缘亮蓝色波纹 → 播放"升级"音效  
     - 显示当前层数k  
* **交互控制**：  
  - 速度滑块：调节步进速度（0.1x~5x）  
  - 单步/自动模式切换  
  - 复位按钮：重置到起点  

---

## 6. 拓展练习与相似问题  
1. **洛谷 P1002** - 过河卒  
   * 推荐理由：训练二维坐标移动的路径规划能力  
2. **洛谷 P1217** - 回文质数  
   * 推荐理由：强化数学优化与边界处理技巧  
3. **洛谷 P1378** - 油滴扩展  
   * 推荐理由：提升几何坐标计算与模拟能力  

---

**结语**  
通过本指南，我们掌握了六边形螺旋移动的数学本质与坐标变换技巧。记住：复杂路径问题往往存在周期性规律，善用数学工具能大幅简化代码！下次挑战见！🚀

---
处理用时：79.89秒