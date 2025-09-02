# 题目信息

# Megacity

## 题目描述

The administration of the Tomsk Region firmly believes that it's time to become a megacity (that is, get population of one million). Instead of improving the demographic situation, they decided to achieve its goal by expanding the boundaries of the city.

The city of Tomsk can be represented as point on the plane with coordinates ( $ 0 $ ; $ 0 $ ). The city is surrounded with $ n $ other locations, the $ i $ -th one has coordinates ( $ x_{i} $ , $ y_{i} $ ) with the population of $ k_{i} $ people. You can widen the city boundaries to a circle of radius $ r $ . In such case all locations inside the circle and on its border are included into the city.

Your goal is to write a program that will determine the minimum radius $ r $ , to which is necessary to expand the boundaries of Tomsk, so that it becomes a megacity.

## 样例 #1

### 输入

```
4 999998
1 1 1
2 2 1
3 3 1
2 -2 1
```

### 输出

```
2.8284271
```

## 样例 #2

### 输入

```
4 999998
1 1 2
2 2 1
3 3 1
2 -2 1
```

### 输出

```
1.4142136
```

## 样例 #3

### 输入

```
2 1
1 1 999997
2 2 1
```

### 输出

```
-1```

# AI分析结果



以下内容已将题目翻译为中文，并保持格式与原始描述一致：

# 特大城市

## 题目描述

托木斯克地区的政府坚信现在是时候成为特大城市（即人口达到一百万）。他们没有通过改善人口状况来实现目标，而是决定通过扩展城市边界来达成目的。

托木斯克市可以表示为平面坐标系中的点 ( $ 0 $ , $ 0 $ )。该市周围有 $ n $ 个聚居点，第 $ i $ 个聚居点坐标为 ( $ x_{i} $ , $ y_{i} $ )，人口为 $ k_{i} $ 人。你可以将城市边界扩展到半径为 $ r $ 的圆形区域。所有位于圆内或边界上的聚居点都将被纳入城市。

你的任务是编写程序确定使托木斯克成为特大城市所需的最小半径 $ r $。

---

**算法分类**：贪心

**综合分析**：
所有题解均采用贪心策略，核心思路为将聚居点按到原点的距离排序后累加人口。当初始人口与累加人口之和首次达到百万时，此时的距离即为最小半径。若遍历完所有点仍未达标则输出-1。关键点在于距离排序的正确性和浮点数精度处理。

---

### 精选题解

#### 1. 作者：___define___ （★★★★★）
**关键亮点**：
- 代码简洁高效，直接使用结构体存储距离和人口
- 严格遵循贪心策略，排序后线性扫描
- 输出格式正确处理保留7位小数

**核心代码**：
```cpp
struct c{ int t; double z; }a[N];
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
    k += a[i].t;
    if(k >= 1e6) printf("%.7lf",a[i].z);
}
```

#### 2. 作者：Halberd_Cease （★★★★☆）
**关键亮点**：
- 包含正确性证明，强调排序后人数单调递增的特性
- 使用显式的距离计算函数增强可读性
- 输出保留12位小数避免精度问题

**正确性证明**：
> "按距离升序排序后，距离小的在前，这样枚举就不会出现加一个点后人数达标但是有比它更优的解，因为所有比它小的点都已经加入"

#### 3. 作者：ztxtjz （★★★★☆）
**特殊处理**：
- 单独处理初始人口已达标的边界情况
- 使用pair结构简化数据存储

**代码亮点**：
```cpp
if(ans>=1e6){ // 初始检查
    printf("0");
    return 0;
}
sort(a+1,a+n+1,cmp); // 显式排序
```

---

**最优策略总结**：
1. **距离排序**：通过 $\sqrt{x_i^2 + y_i^2}$ 计算距离并排序，确保每次扩展都是最小半径增长
2. **贪心累加**：按距离由近及远累加人口，首次达标时的距离即为最优解
3. **精度控制**：输出保留7位以上小数，使用double类型存储距离

---

**拓展应用**：
- 类似贪心问题：区间覆盖（选择最少点覆盖所有区间）、背包问题的部分贪心策略
- 距离相关题目可联想极角排序、最近点对等几何问题

---

**推荐练习题**：
1. P1223 [排队接水](https://www.luogu.com.cn/problem/P1223)（贪心+排序）
2. P1803 [活动安排问题](https://www.luogu.com.cn/problem/P1803)（区间贪心）
3. P1094 [纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针+贪心）

---
处理用时：53.37秒