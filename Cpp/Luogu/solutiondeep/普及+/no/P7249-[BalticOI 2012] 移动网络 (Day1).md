# 题目信息

# [BalticOI 2012] 移动网络 (Day1)

## 题目描述

有一条线段与若干个点，求线段上的点离最近的点最远的距离。

## 说明/提示

**【样例解释】** 

距离最远的点在两个点的中垂线与线段的交点处。

**【数据范围】**

- 对于 25% 的数据，满足 $n \leq 5000$
- 对于 50% 的数据，满足 $n \leq 10^5$
- 对于 100% 的数据，满足 $1\leq n \leq 10^6$，$1 \leq l \leq 10^9$，$-10^9 \leq x_i,y_i \leq 10^9$

**【说明】**

译自 [BalticOI 2012 Day1 T2. Mobile](http://www.boi2012.lv/data/day1/eng/mobile.pdf)

## 样例 #1

### 输入

```
2 10
0 0
11 1```

### 输出

```
5.545455```

# AI分析结果

### 算法分类
二分

### 综合分析与结论
题目要求在线段上找到一个点，使其到最近点的距离最大，典型的二分答案问题。所有题解都采用了二分法来求解，核心思路是通过二分距离，判断以每个点为圆心、该距离为半径的圆是否能完全覆盖线段。难点在于如何高效地判断线段是否被完全覆盖，以及如何避免排序带来的额外时间复杂度。

### 所选高分题解
#### 1. 作者：Raymondzll (4星)
**关键亮点**：
- 详细解释了二分法的单调性及其正确性。
- 通过几何分析优化了覆盖区间的更新策略，避免了排序，时间复杂度降为 $O(n \times \log(\frac{10^9}{eps}))$。
- 代码清晰，注释详细，解释了关键参数的设置（如 `eps` 和 `rig` 的取值）。

**核心代码**：
```cpp
bool check(double mid){
    double maxx_covered_right=0;
    for(int i=1;i<=n;i++){
        double del=sqrt(mid*mid-1.0*y[i]*y[i]);
        if(x[i]-del<=maxx_covered_right&&x[i]+del>=maxx_covered_right)
            maxx_covered_right=x[i]+del;
    }
    return maxx_covered_right<l;
}
```

#### 2. 作者：Azazеl (4星)
**关键亮点**：
- 修正了二分上界的问题，提出应为 $\sqrt{5}l$ 及以上。
- 通过几何性质优化了覆盖区间的更新，避免了排序，时间复杂度为 $O(n \log \frac{\sqrt{5}l}{eps})$。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
bool check(double r){
    double x=0,From,To;
    for(int i=1;i<=n;i++){
        From=-sqrt(1.0*r*r-1.0*Y[i]*Y[i])+X[i];
        To=sqrt(1.0*r*r-1.0*Y[i]*Y[i])+X[i];
        if(From<=x&&x<=To) x=To;
    }
    return x>=L;
}
```

#### 3. 作者：Link_Cut_Y (4星)
**关键亮点**：
- 详细推导了圆与直线交点的计算方法，增强了题解的可读性。
- 通过几何性质优化了覆盖区间的更新，避免了排序，时间复杂度为 $O(n \log \frac{w}{eps})$。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
bool check(double r) {
    double last = 0;
    rep(i, 1, n) {
        double x0 = p[i].x - sqrt(r * r - p[i].y * p[i].y), x1 = -x0 + 2 * p[i].x;
        if (x0 < last && x1 > last) last = x1;
    }
    return last >= m;
}
```

### 最优关键思路或技巧
- **二分答案**：通过二分距离来求解最小距离的最大值，利用单调性保证正确性。
- **几何优化**：通过几何性质（如圆的覆盖范围）优化覆盖区间的更新，避免排序，降低时间复杂度。
- **参数设置**：合理设置二分精度（如 `eps`）和上界（如 `rig`），避免超时或精度不足。

### 可拓展之处
- 类似问题：如求平面上点到线段的最小距离、最大覆盖范围等问题，均可采用二分法结合几何性质进行优化。
- 算法套路：二分答案结合几何性质，适用于求解最小距离的最大值或最大距离的最小值等问题。

### 推荐题目
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
2. [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)

### 个人心得摘录
- **Raymondzll**：提到 `eps` 的设置需要折中，过大或过小都会影响结果，强调了参数设置的重要性。
- **Azazеl**：修正了二分上界的问题，强调了细节对算法正确性的影响。
- **Link_Cut_Y**：详细推导了圆与直线交点的计算方法，增强了题解的可读性，强调了数学推导在算法优化中的重要性。

---
处理用时：28.15秒