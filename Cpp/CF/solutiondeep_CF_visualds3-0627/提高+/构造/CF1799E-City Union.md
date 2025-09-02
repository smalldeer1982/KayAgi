# 题目信息

# City Union

## 题目描述

You are given $ n \times m $ grid. Some cells are filled and some are empty.

A city is a maximal (by inclusion) set of filled cells such that it is possible to get from any cell in the set to any other cell in the set by moving to adjacent (by side) cells, without moving into any cells not in the set. In other words, a city is a connected component of filled cells with edges between adjacent (by side) cells.

Initially, there are two cities on the grid. You want to change some empty cells into filled cells so that both of the following are satisfied:

- There is one city on the resulting grid.
- The shortest path between any two filled cells, achievable only by moving onto filled cells, is equal to the Manhattan distance between them.

The Manhattan distance between two cells $ (a, b) $ and $ (c, d) $ is equal to $ |a - c| + |b - d| $ .

Find a way to add filled cells that satisfies these conditions and minimizes the total number of filled cells.

## 说明/提示

In the first test case, we can add a single filled cell between the two cities to connect them. We can verify that the second condition is satisfied.

In the second test case, we can also connect the cities with a single filled cell, while satisfying the second condition.

In the third test case, note that if we filled the 3 cells in the top left, the cities would be connected, but the second condition would not be satisfied for cells $ (4, 2) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
11
1 3
#.#
2 2
.#
#.
4 4
..##
...#
#...
##..
6 6
.##...
##....
......
....##
.....#
...###
6 5
.#..#
.#..#
.#..#
.#.##
.#...
##...
5 5
#####
#...#
#.#.#
#...#
#####
4 4
.##.
##.#
#.##
.##.
5 5
..###
....#
.....
#....
#....
5 6
.##...
##....
#....#
....##
...##.
6 5
..##.
...##
....#
#....
##...
.##..
5 4
..##
..#.
..#.
#...
#...```

### 输出

```
###

.#
##

..##
..##
###.
##..

.##...
###...
..#...
..####
...###
...###

.####
.####
.####
.####
.#...
##...

#####
#####
#####
#####
#####

.##.
####
####
.##.

..###
..###
..#..
###..
#....

.##...
###...
######
...###
...##.

..##.
..###
..###
###..
###..
.##..

..##
..#.
..#.
###.
#...```

# AI分析结果



## 算法分类选择  
**构造算法**  

## 题解思路、算法要点与解决难点  

### 核心思路  
题目要求将两个城市（连通块）合并为一个，并满足任意两点最短路径等于曼哈顿距离。关键条件要求每行每列的 `#` 必须连续。解决方案分为两步：  
1. **填充行/列形成连续块**：逐行逐列填充 `.`，使得每行每列的 `#` 连续。  
2. **连接两个城市**：找到两个城市的边界坐标，用最短路径连接。  

### 难点与解决  
- **行/列连续性的维护**：通过动态调整每行的左右边界，确保填充后的行和列无间隙。  
- **连通性处理**：连接两个城市时需选择最短路径，填充后再次检查行/列连续性。  

---

## 题解评分  

### 1. yimuhua（★★★★☆）  
- **亮点**：使用 `multiset` 动态维护列边界，逐行扩展填充区域。  
- **代码简练**，但时间复杂度较高。  

### 2. unputdownable（★★★★☆）  
- **亮点**：提出左侧/右侧 `.` 数量单调性条件，通过两次扫描优化填充。  
- **逻辑清晰**，但代码实现较复杂。  

### 3. wxzzzz（★★★★☆）  
- **亮点**：分四种情况讨论城市位置关系，用并查集维护连通性。  
- **详细处理连接路径**，但代码冗长。  

---

## 最优思路或技巧提炼  

### 关键步骤  
1. **行/列填充**：  
   - 对每行确定左边界 `l[i]` 和右边界 `r[i]`，填充 `l[i]` 到 `r[i]` 的所有格子。  
   - 上下行边界传递，确保行间连续性（如 `l[i] = min(l[i], l[i-1])`）。  

2. **路径连接**：  
   - 取城市A的右下角 `(maxx, maxy)` 和城市B的左上角 `(minx, miny)`。  
   - 沿右/下方向逐格填充，优先走已有 `#`，否则新增填充。  

### 代码片段（yimuhua 核心逻辑）  
```cpp  
multiset<int> s;  
for (int i = n; i; i--) {  
    if (l[i] < 51) {  
        for (int j = l[i]; j <= r[i]; j++)  
            if (c[i][j] == '.') c[i][j] = '#';  
        if (!s.empty()) {  
            l[i - 1] = min(l[i - 1], min(l[i], *s.begin()));  
            r[i - 1] = max(r[i - 1], max(r[i], *s.rbegin()));  
        }  
    }  
}  
```  

---

## 同类型题或类似算法套路  
- **矩阵填充问题**：如 [CF1799D] 或 [LeetCode 130. 被围绕的区域]。  
- **曼哈顿距离构造**：要求路径无绕行，类似棋盘最短路径填充。  

---

## 推荐题目  
1. **洛谷 P3958 奶酪**（三维连通性）  
2. **洛谷 P1137 旅行计划**（拓扑排序与路径构造）  
3. **CF 1799D Hot Start Up**（贪心构造）  

---

## 可视化与算法演示  

### 动画方案  
1. **网格绘制**：用 Canvas 绘制 `n×m` 网格，初始 `#` 为蓝色，填充区域为黄色。  
2. **行填充动画**：逐行高亮 `l[i]` 到 `r[i]`，填充时黄色方块渐显。  
3. **路径连接**：从起点到终点逐步绘制路径，优先沿已有 `#` 移动，新增填充时闪烁提示。  

### 复古像素风格  
- **调色板**：使用 8-bit 颜色（蓝、黄、绿、红）。  
- **音效**：填充时播放“哔”声，连接成功时播放胜利音效。  
- **自动演示**：按步执行填充和连接，用户可暂停/调速。  

---

## 代码实现（核心逻辑）  
```javascript  
// 示例：Canvas 绘制填充过程  
function drawGrid(grid) {  
    ctx.clearRect(0, 0, canvas.width, canvas.height);  
    for (let i = 0; i < n; i++) {  
        for (let j = 0; j < m; j++) {  
            if (grid[i][j] === '#') ctx.fillStyle = '#0000FF';  
            else if (grid[i][j] === 'filled') ctx.fillStyle = '#FFFF00';  
            else ctx.fillStyle = '#FFFFFF';  
            ctx.fillRect(j * 20, i * 20, 18, 18);  
        }  
    }  
}  
```  

---

## 总结  
通过构造行/列连续块并贪心连接路径，确保填充数最小。可视化可直观展示填充与连接过程，帮助理解核心逻辑。

---
处理用时：83.02秒