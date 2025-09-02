# 题目信息

# Spotlights

## 题目描述

Theater stage is a rectangular field of size $ n×m $ . The director gave you the stage's plan which actors will follow. For each cell it is stated in the plan if there would be an actor in this cell or not.

You are to place a spotlight on the stage in some good position. The spotlight will project light in one of the four directions (if you look at the stage from above) — left, right, up or down. Thus, the spotlight's position is a cell it is placed to and a direction it shines.

A position is good if two conditions hold:

- there is no actor in the cell the spotlight is placed to;
- there is at least one actor in the direction the spotlight projects.

Count the number of good positions for placing the spotlight. Two positions of spotlight are considered to be different if the location cells or projection direction differ.

## 说明/提示

In the first example the following positions are good:

1. the (1, 1) cell and right direction;
2. the (1, 1) cell and down direction;
3. the (1, 3) cell and left direction;
4. the (1, 3) cell and down direction;
5. the (1, 4) cell and left direction;
6. the (2, 2) cell and left direction;
7. the (2, 2) cell and up direction;
8. the (2, 2) and right direction;
9. the (2, 4) cell and left direction.

Therefore, there are $ 9 $ good positions in this example.

## 样例 #1

### 输入

```
2 4
0 1 0 0
1 0 1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 4
0 0 0 0
1 0 0 1
0 1 1 0
0 1 0 0
```

### 输出

```
20
```

# AI分析结果



# 中文题目重写

## 题目名称：聚光灯

### 题目描述

舞台是一个 $n×m$ 的矩形区域。导演给出了演员站位图，每个单元格标记是否有演员。

需要计算聚光灯的"优质位置"数量。优质位置需满足：
1. 聚光灯所在单元格没有演员；
2. 聚光灯照射方向（左/右/上/下）上至少有一个演员。

两个位置不同当且仅当坐标或方向不同。

## 说明/提示

样例1的优质位置共9种，具体排列方式详见原题说明。

---

# 算法分类
前缀和 / 预处理

# 题解综合分析

**核心思路对比**：
1. **方向预处理**：记录每个点四个方向是否存在演员，通过行列遍历实现O(nm)预处理（Cute__yhb、过氧化氢）
2. **动态规划递推**：利用状态转移记录各方向是否可见演员（Zhuluoan）
3. **前缀和判定**：利用行列前缀和快速判断各方向是否有演员（GaryH、T_TLucas_Yin）
4. **辐射标记法**：每个演员标记其辐射区域内的所有可见空位（pengbubu）

**最优思路提炼**：
- **行/列极值预处理**（过氧化氢）：记录每行最左/右、每列最上/下的演员位置，每个空位只需四次极值比较即可判断四个方向是否存在演员。
- **布尔型方向标记**（Cute__yhb）：通过行列遍历构建四个布尔数组，分别表示每个点的上下左右方向是否至少存在一个演员。

# 高分题解推荐

## 1. Cute__yhb（⭐⭐⭐⭐⭐）
**亮点**：
- 四组方向数组清晰分离逻辑
- 通过位运算简化布尔标记
- 代码简洁易读（20行核心逻辑）

```cpp
// 预处理四个方向是否存在演员
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) 
        Left[i][j]  = a[i][j] | Left[i][j-1];    // 左方向
    for(int j=m;j;j--) 
        Right[i][j] = a[i][j] | Right[i][j+1];   // 右方向
}
for(int j=1;j<=m;j++){
    for(int i=1;i<=n;i++) 
        up[i][j]    = a[i][j] | up[i-1][j];      // 上方向
    for(int i=n;i;i--) 
        down[i][j]  = down[i+1][j] | a[i][j];    // 下方向
}

// 统计答案（每个空位累加四个布尔值）
if(a[i][j]==0) sum += Left[i][j] + Right[i][j] + up[i][j] + down[i][j];
```

## 2. 过氧化氢（⭐⭐⭐⭐）
**亮点**：
- 极值预处理思路新颖
- 避免复杂数据结构
- 空间复杂度优化（仅需存储行列极值）

```cpp
// 预处理行列极值
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(a[i][j]){
            s[i][0] = min(s[i][0],j);  // 行最左演员
            s[i][1] = max(s[i][1],j);  // 行最右演员
            c[j][0] = min(c[j][0],i);  // 列最上演员
            c[j][1] = max(c[j][1],i);  // 列最下演员
        }

// 判断逻辑（每个空位）
if(s[i][0] < j) ans++; // 左方向有演员
if(s[i][1] > j) ans++; // 右方向有演员
if(c[j][0] < i) ans++; // 上方向有演员
if(c[j][1] > i) ans++; // 下方向有演员
```

## 3. GaryH（⭐⭐⭐⭐）
**亮点**：
- 前缀和思路直观
- 利用类型转换简化判断
- 处理边界条件清晰

```cpp
// 预处理行列前缀和
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        ll[i][j][1] = ll[i-1][j][1] + a[i][j]; // 列前缀和

// 判断逻辑（示例：上方存在演员）
ans += bool(ll[i][j][1]); // 当前点上方前缀和>0则存在演员
```

# 关键优化技巧

1. **方向独立性**：将四个方向解耦处理，避免复杂的多维状态
2. **布尔标记替代计数**：使用位运算或逻辑运算代替数值计算，节省空间
3. **极值预处理**：通过记录行列极值将方向判断转化为比较运算

# 拓展应用

**同类问题特征**：
- 需要快速判断二维空间中的方向属性
- 涉及大量重复的方向查询操作
- 数据规模要求O(nm)时间复杂度

**推荐练习题目**：
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（一维前缀和极值）
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)（差分与前缀和综合应用）
3. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)（二维前缀和极值）

# 调试经验摘录

**GaryH**：  
_"开始误以为只需判断相邻格子，导致样例错误。通过重新审题发现方向可以延伸，改用前缀和后解决。bool转换技巧避免了复杂的if判断。"_

**过氧化氢**：  
_"最初尝试暴力辐射标记法导致TLE，后通过观察发现只需记录行列极值即可判断方向存在性，极大优化时间复杂度。"_

---
处理用时：83.96秒