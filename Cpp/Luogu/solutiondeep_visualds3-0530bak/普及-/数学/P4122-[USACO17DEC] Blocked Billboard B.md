# 题目信息

# [USACO17DEC] Blocked Billboard B

## 题目描述

在漫长的挤奶过程中，奶牛 Bessie 喜欢透过谷仓的窗户盯着街对面的两块巨大的矩形广告牌，上面分别写着“Farmer Alex 的美味苜蓿”和“Farmer Greg 的优质谷物”。广告牌上这两种奶牛饲料的图片对 Bessie 来说比她农场里的草看起来美味得多。

有一天，当 Bessie 正盯着窗外时，她惊讶地看到一辆巨大的矩形卡车停在街对面。卡车的侧面有一则广告，写着“Farmer Smith 的顶级牛排”，Bessie 不太理解这则广告，但她更担心的是卡车可能会挡住她最喜欢的两块广告牌的视线。

给定两块广告牌和卡车的位置，请计算两块广告牌仍然可见的总面积。卡车可能遮挡了其中一块、两块，或者没有遮挡任何一块广告牌。

## 说明/提示

在这个例子中，第一块广告牌有 $5$ 单位面积可见，第二块广告牌有 $12$ 单位面积可见。

题目来源：Brian Dean

## 样例 #1

### 输入

```
1 2 3 5
6 0 10 4
2 1 8 3```

### 输出

```
17```

# AI分析结果



# [USACO17DEC] Blocked Billboard B 题解分析

## 算法分类
**几何**

---

## 题解思路与核心难点

### 核心思路
所有题解均围绕**矩形相交面积计算**展开，关键公式为：  
**可见面积 = 广告牌面积 - 广告牌与卡车的相交面积**

### 解决难点对比
| 方法         | 关键点                                                                 | 时间复杂度 | 空间复杂度 |
|--------------|----------------------------------------------------------------------|------------|------------|
| **数学公式法** | 通过计算矩形交集的左下角max、右上角min，用max(0, ...)处理不相交情况 | O(1)       | O(1)       |
| **模拟标记法** | 二维数组标记广告牌区域，卡车覆盖区域置零                           | O(N²)      | O(N²)      |
| **离散化**    | 坐标排序后分割小块，逐个判断是否被遮挡                             | O(NlogN)   | O(N)       |

**关键公式推导**（数学方法）：
1. 广告牌面积：`(x2-x1)*(y2-y1)`
2. 相交区域宽：`max(0, min(ad.x2, truck.x2) - max(ad.x1, truck.x1))`
3. 相交区域高：`max(0, min(ad.y2, truck.y2) - max(ad.y1, truck.y1))`

---

## 高星题解推荐（≥4星）

### 1. [litianqi2529298200] ⭐⭐⭐⭐⭐
**核心亮点**：
- 结构体封装矩形属性，代码高度模块化
- 直接应用几何公式计算相交面积，效率最优
- 函数`intersect_area`处理所有相交逻辑，可读性强

**代码片段**：
```cpp
int intersect_area(Rect p, Rect q) {
    int x = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
    int y = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
    return x * y;
}
```

### 2. [Alex_Wei] ⭐⭐⭐⭐
**核心亮点**：
- 坐标偏移处理负数，避免数组越界
- 二维数组动态标记覆盖情况，直观易懂
- 边标记边统计，减少二次遍历开销

**代码片段**：
```cpp
for(int y=a+1000; y<d+1000; y++) 
    for(int z=s+1000; z<f+1000; z++) {
        if(x<3) m[y][z]++, ans++;
        if(m[y][j] && x==3) ans--;
    }
```

### 3. [info___tion] ⭐⭐⭐⭐
**核心亮点**：
- 离散化坐标处理大范围数据
- 分割不可再分的小矩形逐个判断
- 支持扩展至复杂覆盖场景

**代码片段**：
```cpp
sort(X+1,X+6+1); // 坐标排序
for(int i=1; i<6; i++) // 遍历所有小矩形
    if(!In(R,ad) && (In(R,cpp) || In(R,txt))) 
        ans += R.Area();
```

---

## 最优技巧提炼
1. **几何公式法**：直接计算相交区域宽高，`max(0, ...)`处理无交集情况
2. **坐标偏移法**：将负数坐标映射到正数区间，避免数组越界
3. **模块化设计**：将矩形属性和相交计算封装成独立函数

---

## 同类题目推荐
1. **P1885 Mosaic** - 矩形覆盖问题进阶版
2. **P1496 火烧赤壁** - 线段覆盖区间计算
3. **P2742 [USACO5.1]圈奶牛** - 计算几何基础

---

## 可视化设计（数学公式法）

### 动画步骤
1. **绘制阶段**：
   - 用蓝色/绿色绘制两个广告牌
   - 用红色半透明绘制卡车覆盖区域
2. **计算相交**：
   - 高亮广告牌与卡车的相交区域（黄色闪烁）
   - 实时显示相交区域宽高计算过程
3. **结果展示**：
   - 广告牌逐渐变为半透明，被遮挡部分变为灰色
   - 最终保留的可见区域用原色突出

### 复古像素风格实现
```javascript
// Canvas初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const COLOR_AD = ['#00F', '#0F0']; // 广告牌颜色
const COLOR_TRUCK = '#F0020';      // 卡车颜色

function drawRect(x1, y1, x2, y2, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x1, y1, x2-x1, y2-y1); // 像素块绘制
}

// 自动推导演示
function autoCalculate() {
    // 显示公式推导过程（8-bit字体）
    showFormula("相交宽 = max(0, min(a2,t2) - max(a1,t1))"); 
    // 逐步高亮关键坐标点
    highlightPoint(minX, minY); 
    highlightPoint(maxX, maxY);
}
```

---

## 关键代码（数学公式法）
```cpp
#include<iostream>
using namespace std;

struct Rect { int x1,y1,x2,y2; };

int area(Rect r) { 
    return (r.x2-r.x1)*(r.y2-r.y1); 
}

int overlap(Rect a, Rect b) {
    int dx = max(0, min(a.x2, b.x2) - max(a.x1, b.x1));
    int dy = max(0, min(a.y2, b.y2) - max(a.y1, b.y1));
    return dx * dy;
}

int main() {
    Rect ad1, ad2, truck;
    cin >> ad1.x1 >> ad1.y1 >> ad1.x2 >> ad1.y2;
    cin >> ad2.x1 >> ad2.y1 >> ad2.x2 >> ad2.y2;
    cin >> truck.x1 >> truck.y1 >> truck.x2 >> truck.y2;
    
    int total = area(ad1) + area(ad2);
    total -= overlap(ad1, truck) + overlap(ad2, truck);
    cout << total;
}
```

---
处理用时：86.68秒