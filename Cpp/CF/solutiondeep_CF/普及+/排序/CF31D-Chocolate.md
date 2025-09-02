# 题目信息

# Chocolate

## 题目描述

Bob has a rectangular chocolate bar of the size $ W×H $ . He introduced a cartesian coordinate system so that the point $ (0,0) $ corresponds to the lower-left corner of the bar, and the point $ (W,H) $ corresponds to the upper-right corner. Bob decided to split the bar into pieces by breaking it. Each break is a segment parallel to one of the coordinate axes, which connects the edges of the bar. More formally, each break goes along the line $ x=x_{c} $ or $ y=y_{c} $ , where $ x_{c} $ and $ y_{c} $ are integers. It should divide one part of the bar into two non-empty parts. After Bob breaks some part into two parts, he breaks the resulting parts separately and independently from each other. Also he doesn't move the parts of the bar. Bob made $ n $ breaks and wrote them down in his notebook in arbitrary order. At the end he got $ n+1 $ parts. Now he wants to calculate their areas. Bob is lazy, so he asks you to do this task.

## 样例 #1

### 输入

```
2 2 2
1 0 1 2
0 1 1 1
```

### 输出

```
1 1 2 ```

## 样例 #2

### 输入

```
2 2 3
1 0 1 2
0 1 1 1
1 1 2 1
```

### 输出

```
1 1 1 1 ```

## 样例 #3

### 输入

```
2 4 2
0 1 2 1
0 3 2 3
```

### 输出

```
2 2 4 ```

# AI分析结果



# Chocolate 巧克力切割问题

## 题目重写
Bob有一块大小为$W \times H$的矩形巧克力，使用笛卡尔坐标系，左下角为$(0,0)$，右上角为$(W,H)$。每次切割为平行坐标轴的线段，将巧克力分为若干块。所有切割完成后，求每块的面积并按升序输出。

---

## 题解综合分析

### 关键思路总结
1. **切割标记法**：利用题目保证切割后均为矩形的特性，直接记录水平和垂直切割线，通过遍历确定每个矩形的边界。
2. **坐标映射技巧**：将切割线映射到二维网格中，通过放大坐标系处理切割线为障碍物，便于搜索连通块。
3. **位运算优化**：用位运算压缩四个方向的切割状态，节省空间并提升判断效率。

### 推荐题解
#### 1. CarroT1212（5星）
**亮点**：  
- 利用题目特性（切割后均为矩形）直接标记切割线，避免搜索  
- 通过行列遍历快速确定矩形边界，时间复杂度$O(WH)$  
- 代码简洁高效，逻辑清晰  

**核心代码**：
```cpp
// 标记水平和垂直切割线
if (r1==r3) { // 水平切割
    for (int i=r2+1; i<=r4; i++) hang[r1][i]=1;
} else if (r2==r4) { // 垂直切割
    for (int i=r1+1; i<=r3; i++) lie[i][r2]=1;
}

// 遍历未访问的格子，扩展矩形边界
while (lie[r1][r2]==0 && r2<m) r2++, r4++;
while (hang[r1][r2]==0 && r1<n) r1++, r3++;
```

#### 2. Tune_（4星）
**亮点**：  
- 位运算压缩四个方向的状态，节省内存  
- 洪水填充法直观处理连通块  
- 支持不规则切割的通用场景  

**核心代码**：
```cpp
// 用位运算标记切割方向
if (xs==xf) { // 水平切割
    for (int j=ys; j<yf; j++) 
        a[xs][j] += 1, a[xs-1][j] += 4;
} else { // 垂直切割
    for (int j=xs; j<xf; j++)
        a[j][ys] += 8, a[j][ys-1] += 2;
}

// DFS判断连通区域
if (!(a[x][y]&1)) dfs(x-1,y); // 上
if (!(a[x][y]&2)) dfs(x,y+1); // 右
```

#### 3. Empty_Dream（4星）
**亮点**：  
- 三维数组标记四个方向的连通性  
- 直接处理切割线对应的方格连接关系  
- 代码结构清晰易扩展  

**核心代码**：
```cpp
// 标记横向切割线
vis1[1][x1][j] = vis1[3][x1+1][j] = 1;

// 标记纵向切割线
vis1[0][j][y1] = vis1[2][j][y1+1] = 1;

// DFS遍历连通块
if (!vis1[i][x][y]) dfs(nx, ny);
```

---

## 拓展与应用
1. **同类问题**：棋盘分割、连通区域统计、障碍物路径规划  
2. **优化技巧**：  
   - 利用题目约束简化问题（如保证切割为矩形）  
   - 坐标映射处理切割线（放大坐标系）  
   - 状态压缩（位运算、三维数组）  

---

## 推荐练习
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182) - 分割序列求极值  
2. [P1505 国家的礼物](https://www.luogu.com.cn/problem/P1505) - 矩阵连通块染色  
3. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) - 闭合区域搜索  

---

## 调试心得摘录
- **坐标转换陷阱**：多位作者提到需注意切割线坐标与方格的映射关系，例如横向切割对应行坐标的+1偏移  
- **边界处理**：CrTsIr400强调要交换起始和结束坐标以保证遍历顺序正确  
- **切割方向判断**：A_small_WA通过画图验证切割线与方格的对应关系

---
处理用时：59.40秒