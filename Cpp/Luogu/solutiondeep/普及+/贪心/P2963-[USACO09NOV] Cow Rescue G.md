# 题目信息

# [USACO09NOV] Cow Rescue G

## 题目描述

Bessie is trapped in a triangular maze with N rows (1 <= N <= 1,000,000). A three row maze is shown below:

The i'th row of the maze contains 2\*i-1 triangles. Numbering from the left, the triangles are named (i,1), (i,2), and so on.

Bessie can travel to the (often three) triangles which share an edge with her current triangle. For example, if she is at (3, 3), she can travel to (3, 2), (3, 4) and (4, 4). Bessie takes one minute to travel from one triangle to the next.

FJ has learned the Bessie is trapped and knows by tracking her iPhone that she starts her exit trek at triangle (Si,Sj). FJ's love for Bessie knows no bounds so he wants her back in the minimum possible time.

The maze has M (1 <= M <= 10,000) exits found in locations throughout the set of triangles. Any one of these will enable Bessie to escape. Once she enters an exit triangle, she leaves the maze in just one more minute.

Find the minimum time in minutes, T, required for Bessie to exit the maze and report the optimal exit location she uses, (OUTi, OUTj). If more than one location requires only T minutes, output the location with the smallest row. If two optimal rows are the same, output the one with smaller column.

贝希被困在一个三角形的迷宫之中。这个迷宫有 $N$ 行（$1 \le N \le 1000000$）。比如下图是一个 $3$ 行的迷宫。  迷宫的第 $i$ 行有 $2i-1$ 个三角形，从左到右分别编号为 $(i, 1)$、$(i, 2)$ 等等。

贝希每次可以从一个三角形走到任意一个一个跟当前的三角形有邻边的三角形。

比如说，如果她目前处于三角形 $(3, 3)$，那么，她可以走到三角形 $(3, 2)$、$(3, 4)$ 和 $(4, 4)$。贝希每次需要一分钟的时间来移动到下一个三角形。

农夫约翰发现贝希被困了！于是她跟踪贝希的iPhone手机（可怜的触摸屏～），得知贝希目前处于三角形 $(S_i, S_j)$。

因为约翰对贝希有著无穷无尽的浓浓爱意，所以他希望贝希能尽可能快地回到他的身边。 在迷宫的三角形之中，有 $M$（$1 \le M \le 10000$）个是出口。在任何一个出口都可以让贝希逃离迷宫。一旦贝希进入一个作为出口的三角形，她用多一分钟就可以逃离这个迷宫。 找到一个可以让贝希逃离迷宫最小时间 $T$，并输出她应该从哪一个出口逃离迷宫，这个出口记为 $(\text{OUT}_i, \text{OUT}_j)$。

如果有多个出口同时需要时间 $T$，输出那个行的编号小的出口，如果仍然有多个出口，输出那个列的编号小的。


## 样例 #1

### 输入

```
4 2 
2 1 
3 5 
4 4 
```

### 输出

```
4 4 
4 
```

# AI分析结果



### 综合分析与结论
本题核心在于快速计算两点在三角网格中的最短距离。各题解均摒弃了暴力的BFS，转而寻找数学规律或坐标转换方法。最优解法通过分析三角形结构特征，推导出垂直移动与非垂直移动的关系，达到O(1)时间复杂度计算距离。

---

### 高星题解推荐

#### 1. 题解作者：chenly8128（⭐⭐⭐⭐⭐）
**关键亮点**：
- 通过几何分析得出移动次数的数学公式  
- 引入"尖角朝向"判断优化非垂直移动次数  
- 代码简洁高效（O(m)时间复杂度）  
**个人心得**：发现三角网格中尖角朝向与奇偶性的关联，通过位运算快速判断朝向，极大简化计算。

```cpp
int sum = 0;
sum += abs(ex[j] - sx); // 纵坐标差
sum = max(sum, abs(-ex[j] + ey[j] + sx - sy)) // 横坐标差调整
sum += abs(ex[j]-sx) + 1; // 总距离+出口时间
```

#### 2. 题解作者：_Weslie_（⭐⭐⭐⭐）
**关键亮点**：
- 通过坐标映射将三角网格转换为规则网格  
- 利用直线分割平面简化区域判断  
- 引入交点计算处理特殊移动路径  
**核心代码**：
```cpp
// 坐标转换
sy = n - sx + sy; 
// 区域判断
if(hc <= zc) nans = hc + zc; 
else 计算交点路径
```

#### 3. 题解作者：Tracy_Loght（⭐⭐⭐）
**亮点**：  
- 图示辅助理解行间移动规律  
- 提出"破壁次数"的奇偶性影响  
**局限**：未完整处理所有边界情况，代码可读性较弱

---

### 最优解题技巧总结
1. **奇偶性判断**：利用坐标奇偶性确定三角形朝向，决定移动方向限制  
2. **坐标映射法**：将三角网格转换为二维直角坐标系，简化距离计算  
3. **分区域处理**：通过几何特征划分平面区域，不同区域采用不同计算策略  
4. **数学公式推导**：通过分析移动模式，建立纵移次数与非纵移次数的关系式

---

### 拓展建议
**同类问题套路**：  
- 网格路径问题可考虑坐标转换（如六边形→正方形）  
- 复杂移动规则可尝试分解为基本移动模式分析  
- 大规模数据下优先寻找数学规律而非暴力搜索  

**推荐练习题**：  
1. P2731 [USACO3.3] 骑马修栅栏（欧拉路径+坐标处理）  
2. P3958 [NOIP2017 提高组] 奶酪（三维空间距离计算）  
3. P1514 [NOIP2010 提高组] 引水入城（网格区域分割）

---
处理用时：48.18秒