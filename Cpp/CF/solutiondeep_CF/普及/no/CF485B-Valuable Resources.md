# 题目信息

# Valuable Resources

## 题目描述

Many computer strategy games require building cities, recruiting army, conquering tribes, collecting resources. Sometimes it leads to interesting problems.

Let's suppose that your task is to build a square city. The world map uses the Cartesian coordinates. The sides of the city should be parallel to coordinate axes. The map contains mines with valuable resources, located at some points with integer coordinates. The sizes of mines are relatively small, i.e. they can be treated as points. The city should be built in such a way that all the mines are inside or on the border of the city square.

Building a city takes large amount of money depending on the size of the city, so you have to build the city with the minimum area. Given the positions of the mines find the minimum possible area of the city.

## 样例 #1

### 输入

```
2
0 0
2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
0 0
0 3
```

### 输出

```
9
```

# AI分析结果



# 重写中文题目

## 题目描述

许多计算机策略游戏需要建造城市、招募军队、征服部落、收集资源。这有时会导致有趣的问题。

假设你的任务是建造一个正方形城市。世界地图使用笛卡尔坐标系。城市的边必须与坐标轴平行。地图中包含一些位于整数坐标点的资源矿，这些矿可视为点。城市必须将所有矿点包含在其内部或边界上。

建造城市的成本取决于其尺寸，因此需要找到面积最小的可行正方形。给定矿点的位置，求城市的最小可能面积。

## 样例 #1

### 输入

```
2
0 0
2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
0 0
0 3
```

### 输出

```
9
```

---

**算法分类**：数学

---

## 题解分析与结论

所有题解均基于同一核心思路：
1. **极值计算**：遍历所有点，记录x和y坐标的极大/极小值
2. **边长相较**：取横向跨度(`max_x - min_x`)和纵向跨度(`max_y - min_y`)的最大值作为正方形边长
3. **面积计算**：输出边长的平方

关键优化点：
- **数据范围处理**：使用`long long`避免溢出
- **实时更新极值**：输入时直接更新极值，无需存储所有点
- **避免浮点运算**：直接取整型差值的平方

---

## 高分题解推荐

### 1. MuLinnnnn（⭐⭐⭐⭐⭐）
**亮点**：
- 变量命名清晰（`p1-p4`对应各极值）
- 初始化合理（用`1e18`确保首次比较正确）
- 显式处理数据类型，避免溢出
**核心代码**：
```cpp
long long p1 = 1e18, p2 = 1e18; // min_x, min_y
long long p3 = -1e18, p4 = -1e18; // max_x, max_y
// 输入时更新极值
printf("%lld", max(p3-p1,p4-p2) * max(p3-p1,p4-p2));
```

### 2. VitrelosTia（⭐⭐⭐⭐）
**亮点**：
- 极值初始化为`INF`确保正确性
- 代码简洁，无冗余操作
**核心代码**：
```cpp
ll lu=INF, ld=-INF, ru=INF, rd=-INF; // 四向极值
// 输入时更新极值
cout<<max(ld-lu, rd-ru)*max(ld-lu, rd-ru);
```

### 3. N_z_（⭐⭐⭐）
**亮点**：
- 动态处理首点输入
- 代码简短高效
**注意点**：
- 使用`#define int long long`可能影响可读性
**核心代码**：
```cpp
int q,w,e,r; // q=min_x, w=max_x, e=min_y, r=max_y
cin>>q>>e; 
w=q; r=e; // 初始化首点
// 后续输入更新极值
cout<<max(w-q,r-e)*max(w-q,r-e);
```

---

## 最优思路总结
1. **极值动态更新**：在输入时实时维护`min_x, max_x, min_y, max_y`
2. **差值比较**：取横向/纵向跨度的最大值作为边长
3. **平方直接计算**：避免使用`pow`函数，直接相乘保证精度

---

## 拓展练习
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059) - 极值统计与去重
2. [P2249 寻找平面上的极大点](https://www.luogu.com.cn/problem/P2249) - 极值点分析
3. [P1885 Moo](https://www.luogu.com.cn/problem/P1885) - 几何覆盖问题变形

---

## 题解中的个人心得
1. **数据范围意识**：多位作者强调`long long`的必要性（如："开int会爆，开long long解决"）
2. **函数选择**：指出`pow`函数可能导致精度问题（如："用pow会爆，还是用乘法"）
3. **初始化技巧**：使用极大值/极小值初始化确保首次比较正确（如："打擂赋大值"）

---
处理用时：60.53秒