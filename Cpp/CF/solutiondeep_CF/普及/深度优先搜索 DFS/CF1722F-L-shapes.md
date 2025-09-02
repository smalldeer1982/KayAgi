# 题目信息

# L-shapes

## 题目描述

An L-shape is a figure on gridded paper that looks like the first four pictures below. An L-shape contains exactly three shaded cells (denoted by \*), which can be rotated in any way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)You are given a rectangular grid. Determine if it contains L-shapes only, where L-shapes can't touch an edge or corner. More formally:

- Each shaded cell in the grid is part of exactly one L-shape, and
- no two L-shapes are adjacent by edge or corner.

For example, the last two grids in the picture above do not satisfy the condition because the two L-shapes touch by corner and edge, respectively.

## 样例 #1

### 输入

```
10
6 10
........**
.**......*
..*..*....
.....**...
...*.....*
..**....**
6 10
....*...**
.**......*
..*..*....
.....**...
...*.....*
..**....**
3 3
...
***
...
4 4
.*..
**..
..**
..*.
5 4
.*..
**..
....
..**
..*.
3 2
.*
**
*.
2 3
*..
.**
3 2
..
**
*.
3 3
.**
*.*
**.
3 3
..*
.**
..*```

### 输出

```
YES
NO
NO
NO
YES
NO
NO
YES
NO
NO```

# AI分析结果

### 题目内容重写

#### L形图案

##### 题目描述

L形图案是指在网格纸上看起来像下面前四张图的形状。一个L形图案恰好包含三个被标记为`*`的格子，这些格子可以以任何方式旋转。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)

给定一个矩形网格，判断它是否仅包含L形图案，且这些L形图案不能通过边或角接触。更正式地说：

- 网格中的每个被标记为`*`的格子必须恰好属于一个L形图案。
- 任意两个L形图案不能通过边或角相邻。

例如，上图中的最后两个网格不满足条件，因为两个L形图案分别通过角和边接触。

### 题解分析与结论

#### 综合分析

本题的核心在于判断网格中的`*`是否仅由L形图案组成，且这些L形图案之间没有边或角的接触。题解中主要采用了以下几种思路：

1. **枚举L形图案的四种可能形态**：通过枚举L形图案的四种可能形态，检查每个`*`是否属于某个L形图案，并确保L形图案之间没有接触。
2. **连通块分析**：通过BFS或并查集维护`*`的连通块，判断每个连通块的大小是否为3，并检查是否形成L形图案。
3. **直接扫描与标记**：通过扫描网格，直接标记L形图案，并检查是否有未标记的`*`或L形图案之间的接触。

#### 最优关键思路

1. **枚举L形图案的四种形态**：这是最直接且易于实现的方法。通过枚举L形图案的四种可能形态，逐个检查每个`*`是否属于某个L形图案，并确保L形图案之间没有接触。这种方法思路清晰，代码实现也较为简洁。
2. **连通块分析**：通过BFS或并查集维护`*`的连通块，判断每个连通块的大小是否为3，并检查是否形成L形图案。这种方法在处理复杂网格时较为高效，但实现起来相对复杂。

#### 推荐题解

1. **Binary_Lee的题解（4星）**
   - **关键亮点**：通过枚举L形图案的四种形态，逐个检查每个`*`是否属于某个L形图案，并确保L形图案之间没有接触。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     void search(int i,int j){
         if(a[i+1][j]&&a[i+1][j+1]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
            !a[i][j-1]&&!a[i][j+1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j+2]&&
            !a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]&&!a[i+2][j+2]){
             a[i][j]=a[i+1][j]=a[i+1][j+1]=0;
             return ;
         }
         // 其他三种形态的检查
     }
     ```

2. **lihanwen12的题解（4星）**
   - **关键亮点**：通过扫描每个格子，判断其是否能作为L形图案的一角，并检查L形图案四周是否有其他`*`。思路清晰，代码实现较为详细。
   - **代码核心**：
     ```cpp
     if(leixing==1){
         for(int x=i-2;x<=i+1;x++)
             for(int y=j-1;y<=j+2;y++){
                 if(x==i-2 && y==j+2)continue;
                 if(x==i && y==j)continue;
                 if(x==i-1 && y==j)continue;
                 if(x==i && y==j+1)continue;
                 if(x>=1 && x<=n && y>=1 && y<=m)
                     if(ch[x][y]=='*')ans=false;
             }
     }
     ```

3. **CodingShark的题解（4星）**
   - **关键亮点**：通过BFS维护`*`的连通块，判断每个连通块的大小是否为3，并检查是否形成L形图案。方法高效，适合处理复杂网格。
   - **代码核心**：
     ```cpp
     int bfs(int sx, int sy){
         int res = 0;
         queue<pair<int, int>> q;
         q.push({sx, sy}), vis[sx][sy] = true;
         while (q.size()){
             auto cur = q.front();
             q.pop(), res++;
             for (int i = 0; i < 8; i++){
                 int tx = cur.first + dir[i][0], ty = cur.second + dir[i][1];
                 if (1 <= tx && tx <= n && 1 <= ty && ty <= m && !vis[tx][ty])
                     vis[tx][ty] = true, q.push({tx, ty});
             }
         }
         return res;
     }
     ```

### 推荐题目

1. **P1162 填涂颜色**（https://www.luogu.com.cn/problem/P1162）
2. **P1141 01迷宫**（https://www.luogu.com.cn/problem/P1141）
3. **P1443 马的遍历**（https://www.luogu.com.cn/problem/P1443）

这些题目都涉及到网格的遍历与连通块分析，与本题的解题思路有相似之处。

---
处理用时：45.30秒