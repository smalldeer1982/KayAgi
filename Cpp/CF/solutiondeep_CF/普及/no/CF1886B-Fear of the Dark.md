# 题目信息

# Fear of the Dark

## 题目描述

Monocarp tries to get home from work. He is currently at the point $ O = (0, 0) $ of a two-dimensional plane; his house is at the point $ P = (P_x, P_y) $ .

Unfortunately, it is late in the evening, so it is very dark. Monocarp is afraid of the darkness. He would like to go home along a path illuminated by something.

Thankfully, there are two lanterns, located in the points $ A = (A_x, A_y) $ and $ B = (B_x, B_y) $ . You can choose any non-negative number $ w $ and set the power of both lanterns to $ w $ . If a lantern's power is set to $ w $ , it illuminates a circle of radius $ w $ centered at the lantern location (including the borders of the circle).

You have to choose the minimum non-negative value $ w $ for the power of the lanterns in such a way that there is a path from the point $ O $ to the point $ P $ which is completely illuminated. You may assume that the lanterns don't interfere with Monocarp's movement.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1886B/e2035d6f1a8a294e1d7b18148024db80f9680a4a.png) The picture for the first two test cases

## 样例 #1

### 输入

```
2
3 3
1 0
-1 6
3 3
-1 -1
4 3```

### 输出

```
3.6055512755
3.2015621187```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

Monocarp 试图从工作地点回家。他目前位于二维平面的点 $O = (0, 0)$，他的家位于点 $P = (P_x, P_y)$。

不幸的是，天色已晚，非常黑暗。Monocarp 害怕黑暗。他希望沿着被照亮的路径回家。

幸运的是，有两个灯笼，分别位于点 $A = (A_x, A_y)$ 和 $B = (B_x, B_y)$。你可以选择任意非负数 $w$，并将两个灯笼的功率设置为 $w$。如果灯笼的功率设置为 $w$，它会照亮以灯笼位置为中心、半径为 $w$ 的圆（包括圆的边界）。

你需要选择最小的非负数 $w$ 作为灯笼的功率，使得存在一条从点 $O$ 到点 $P$ 的路径，且该路径完全被照亮。你可以假设灯笼不会干扰 Monocarp 的移动。

### 算法分类
**数学**

### 题解分析与结论

该题的核心在于通过几何计算找到最小的 $w$，使得从起点 $O$ 到终点 $P$ 的路径完全被两个灯笼的照亮范围覆盖。题解主要分为两类思路：

1. **分类讨论法**：通过讨论不同情况（如一个圆覆盖两个点、两个圆相交等）来计算最小 $w$。
2. **二分法**：通过二分搜索确定最小的 $w$，并结合几何条件进行验证。

### 评分较高的题解

#### 题解1：SDLTF_凌亭风
**评分：4星**
**关键亮点**：
- 通过分类讨论，明确了几种可能的情况，并分别计算了最小 $w$。
- 代码简洁，逻辑清晰，使用了宏定义简化距离计算。

**核心代码**：
```cpp
long double AO = disAO, BP = disBP, AP = disAP, BO = disBO, d = disAB / 2.0;
r1 = min(max(AO, AP), max(BO, BP));
r2 = max(max(AO, d), BP);
r3 = max(max(BO, d), AP);
cout << min(r1, min(r2, r3)) << '\n';
```

#### 题解2：Jerrycyx
**评分：4星**
**关键亮点**：
- 使用直观的几何距离计算，通过枚举所有可能的灯笼组合，找到最小的 $w$。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
double ans = 1e18;
for(int i=0;i<=1;i++)
    for(int j=0;j<=1;j++) {
        double w = max({
            dis(0,0,lx[i],ly[i]),
            dis(px,py,lx[j],ly[j]),
            dis(lx[i],ly[i],lx[j],ly[j])/2.0
        });
        ans = min(ans, w);
    }
printf("%.10lf\n", ans);
```

#### 题解3：Super_Builder
**评分：4星**
**关键亮点**：
- 采用二分法，结合几何条件进行验证，确保路径被完全照亮。
- 代码实现较为严谨，考虑了多种走法。

**核心代码**：
```cpp
bool check(double r){
    if(diss(0,0,ax,ay)<=r){
        if(diss(ax,ay,px,py)<=r)return true;
        if(diss(ax,ay,bx,by)<=2*r){
            if(diss(bx,by,px,py)<=r)return true;
        }
    }
    if(diss(0,0,bx,by)<=r){
        if(diss(bx,by,px,py)<=r)return true;
        if(diss(ax,ay,bx,by)<=2*r){
            if(diss(ax,ay,px,py)<=r)return true;
        }
    }
    return false;
}
```

### 最优关键思路或技巧
- **分类讨论**：通过明确不同情况（如一个圆覆盖两个点、两个圆相交等），分别计算最小 $w$。
- **二分法**：通过二分搜索确定最小的 $w$，并结合几何条件进行验证。

### 可拓展之处
- 类似问题可以扩展到三维空间，或者考虑多个光源的情况。
- 可以结合图论中的最短路径算法，进一步优化路径选择。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1887 乘积最大](https://www.luogu.com.cn/problem/P1887)
3. [P1888 最短路径](https://www.luogu.com.cn/problem/P1888)

### 个人心得摘录
- **SDLTF_凌亭风**：通过分类讨论，明确了几种可能的情况，并分别计算了最小 $w$，代码简洁，逻辑清晰。
- **Jerrycyx**：使用直观的几何距离计算，通过枚举所有可能的灯笼组合，找到最小的 $w$，代码结构清晰，易于理解。
- **Super_Builder**：采用二分法，结合几何条件进行验证，确保路径被完全照亮，代码实现较为严谨，考虑了多种走法。

---
处理用时：32.03秒