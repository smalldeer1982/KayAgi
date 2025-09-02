# 题目信息

# [USACO14JAN] Cow Curling G

## 题目描述

Cow curling is a popular cold-weather sport played in the Moolympics.

Like regular curling, the sport involves two teams, each of which slides N heavy stones (3 <= N <= 50,000) across a sheet of ice.  At the end of the game, there are 2N stones on the ice, each located at a distinct 2D point.

Scoring in the cow version of curling is a bit curious, however.  A stone is said to be "captured" if it is contained inside a triangle whose corners are stones owned by the opponent (a stone on the boundary of such a triangle also counts as being captured).  The score for a team is the number of opponent stones that are captured.

Please help compute the final score of a cow curling match, given the locations of all 2N stones.

有两支队伍在比赛，一队可以一次取出3个点来，所围成的三角形覆盖的区域可以“捕获”对方的点，问两支队伍各能够捕获对方多少个点。


## 说明/提示

Each team owns 4 stones.  Team A has stones at (0,0), (0,2), (2,0), and (2,2), and team B has stones at (1,1), (1,10), (-10,3), and (10,3).


Team A captures their opponent's stone at (1,1).  Team B captures their opponent's stones at (0,2) and (2,2).


## 样例 #1

### 输入

```
4 
0 0 
0 2 
2 0 
2 2 
1 1 
1 10 
-10 3 
10 3 
```

### 输出

```
1 2 
```

# AI分析结果



---

**唯一算法分类**：计算几何（凸包与点定位）

---

### 题解思路与核心难点

1. **关键思路**  
   - 题目本质是判断点是否被任意敌方三角形覆盖，等价于判断点是否在敌方点集的凸包内。  
   - 核心优化：敌方所有可能的三角形形成的覆盖区域，等价于其凸包覆盖的区域。  
   - 难点在于高效判断点是否在凸包内部（排除边界），且需处理大规模点集（N ≤ 5e4）。

2. **算法流程**  
   - **步骤1**：对双方点集分别计算凸包（Andrew算法，按坐标排序后构建上下凸壳）。  
   - **步骤2**：对每个敌方点，二分判断其在凸包的位置：  
     - 将凸包视为极角排序的多边形，选择一个基点（如最左点）。  
     - 通过叉积二分确定点可能所在的三角形扇区。  
     - 用叉积符号判断点是否严格在三角形内部。  
   - **步骤3**：统计所有被严格包含的点的数量。

3. **代码实现要点**  
   - 凸包构建需去重并排序。  
   - 叉积判断逻辑需严格处理等于零的情况（边界点不计入）。  
   - 若凸包点数不足3，则无法形成有效覆盖区域，直接返回0。

---

### 题解评分（≥4星）

1. **first_fan（★★★★☆）**  
   - **亮点**：  
     - 正确利用凸包性质简化问题，时间复杂度O(N log N)。  
     - 叉积判断逻辑清晰，处理边界条件严格。  
   - **优化空间**：  
     - 未显式处理凸包退化（如三点共线），但实际数据可通过叉积判断规避。  
     - 代码可读性一般，需注释辅助理解。

---

### 最优思路提炼

- **核心技巧**：将任意三角形覆盖问题转化为凸包含问题，极大降低计算量。  
- **叉积二分法**：利用极角排序后的凸包特性，通过二分快速定位可能包含点的扇区。  
- **边界处理**：叉积等于零时视为边界点，不计数，需在代码中严格判断。

---

### 相似题目与算法套路

- **通用解法**：点是否在凸包内、凸包构建、几何计算。  
- **同类题目**：  
  1. [P3829 [SHOI2012] 信用卡凸包](https://www.luogu.com.cn/problem/P3829)  
  2. [P2521 [HAOI2011] 防线修建](https://www.luogu.com.cn/problem/P2521)  
  3. [P3297 [SDOI2013] 逃考](https://www.luogu.com.cn/problem/P3297)

---

### 代码实现（核心片段）

```cpp
struct Point {
    ll x, y;
    Point operator-(const Point &b) const { return {x - b.x, y - b.y}; }
    ll operator*(const Point &b) const { return x * b.y - y * b.x; } // 叉积
    bool operator<(const Point &b) const { return x < b.x || (x == b.x && y < b.y); }
};

vector<Point> convexHull(vector<Point> &p) {
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    sort(p.begin(), p.end());
    vector<Point> res(n * 2);
    for (int i = 0; i < n; res[k++] = p[i++]) // 下凸壳
        while (k > 1 && (res[k - 1] - res[k - 2]) * (p[i] - res[k - 2]) <= 0) k--;
    for (int i = n - 2, t = k; i >= 0; res[k++] = p[i--]) // 上凸壳
        while (k > t && (res[k - 1] - res[k - 2]) * (p[i] - res[k - 2]) <= 0) k--;
    res.resize(k - 1);
    return res;
}

bool inConvex(const Point &p, const vector<Point> &hull) {
    int n = hull.size();
    if (n <= 2) return false;
    auto cross = [](const Point &a, const Point &b) { return a * b; };
    if (cross(hull[1] - hull[0], p - hull[0]) < 0) return false;
    if (cross(hull[n - 1] - hull[0], p - hull[0]) > 0) return false;
    int l = 1, r = n - 2;
    while (l <= r) { // 二分定位扇区
        int mid = (l + r) >> 1;
        if (cross(hull[mid] - hull[0], p - hull[0]) >= 0) l = mid + 1;
        else r = mid - 1;
    }
    return cross(hull[r + 1] - hull[r], p - hull[r]) > 0; // 严格内部
}
```

---

### 可视化设计

**算法流程动画（像素风格）**  
- **凸包构建**：  
  - 用绿色像素动态绘制点集排序过程，红色高亮当前处理的点。  
  - 上下凸壳用蓝色像素连线，每添加一个点播放“滴”音效。  
- **点定位判断**：  
  - 待判断点显示为黄色，遍历时用橙色射线扫描极角范围。  
  - 命中扇区时播放“咔”音效，最终结果用闪烁红/绿方块表示是否被捕获。  

**交互设计**  
- **速度控制**：滑动条调节动画速度（0.5x~3x）。  
- **单步执行**：按空格键逐帧播放凸包构建或点判断过程。  
- **音效**：背景音乐为8-bit循环旋律，关键操作伴随短促音效。

---

**总结**：通过凸包与叉积二分法高效解决大规模几何覆盖问题，结合像素动画与音效增强理解。

---
处理用时：108.80秒