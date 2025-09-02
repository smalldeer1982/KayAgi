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

**题目描述**

L形图案是指在网格纸上看起来像下面前四张图片的图形。一个L形图案恰好包含三个被标记的单元格（用`*`表示），并且可以以任何方式旋转。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)

给定一个矩形网格，判断它是否仅包含L形图案，且这些L形图案不能通过边或角接触。更正式地说：

- 网格中的每个被标记的单元格必须属于且仅属于一个L形图案；
- 任意两个L形图案不能通过边或角相邻。

例如，上面图片中的最后两个网格不满足条件，因为两个L形图案分别通过角和边接触。

### 题解分析与结论

这些题解主要围绕如何判断网格中的`*`是否仅组成L形图案，并且这些L形图案之间没有边或角的接触。以下是各题解的要点和难点对比：

1. **Binary_Lee**的题解通过枚举所有可能的L形图案，并检查其周围是否有其他`*`，最后判断是否有剩余的`*`。这种方法简单直接，但代码较长且重复较多。
2. **lihanwen12**的题解通过扫描每个格子，判断其是否能作为L形的一角，并检查四周是否有其他`*`。这种方法逻辑清晰，但代码复杂度较高。
3. **CodingShark**的题解使用BFS来检查连通块的大小，并进一步判断是否形成L形。这种方法较为通用，但实现较为复杂。
4. **Lantrol**的题解通过枚举所有2x2的区域，判断是否形成L形，并检查四周是否有其他`*`。这种方法较为直观，但代码较长。
5. **zsseg**的题解使用并查集来维护连通块，并检查连通块的大小和形状。这种方法较为高效，但实现较为复杂。
6. **include_BM**的题解通过判断是否有相邻的L形，并删除已找到的L形，最后检查是否有剩余的`*`。这种方法较为简洁，但逻辑较为复杂。
7. **Micnation_AFO**的题解通过判断是否有连续三个`*`在一行或一列，并检查是否形成L形。这种方法较为直观，但实现较为复杂。

### 评分较高的题解

1. **Binary_Lee**（4星）
   - **关键亮点**：通过枚举所有可能的L形图案，并检查其周围是否有其他`*`，最后判断是否有剩余的`*`。思路清晰，代码实现较为直接。
   - **核心代码**：
     ```cpp
     void search(int i,int j){
         if(a[i+1][j]&&a[i+1][j+1]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
            !a[i][j-1]&&!a[i][j+1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j+2]&&
            !a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]&&!a[i+2][j+2]){
             a[i][j]=a[i+1][j]=a[i+1][j+1]=0;
             return ;
         }
         // 其他三种情况的判断
     }
     ```

2. **lihanwen12**（4星）
   - **关键亮点**：通过扫描每个格子，判断其是否能作为L形的一角，并检查四周是否有其他`*`。逻辑清晰，代码复杂度较高但易于理解。
   - **核心代码**：
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

3. **include_BM**（4星）
   - **关键亮点**：通过判断是否有相邻的L形，并删除已找到的L形，最后检查是否有剩余的`*`。方法简洁，逻辑较为复杂但高效。
   - **核心代码**：
     ```cpp
     for(int i=1;i<n;++i)
         for(int j=1;j<m;++j){
             int num=(s[i][j]=='*')+(s[i+1][j]=='*')+(s[i][j+1]=='*')+(s[i+1][j+1]=='*');
             if(num==3) s[i][j]=s[i+1][j]=s[i][j+1]=s[i+1][j+1]='.';
         }
     ```

### 最优关键思路与技巧

- **枚举与标记**：通过枚举所有可能的L形图案，并标记已找到的L形，最后检查是否有剩余的`*`。这种方法简单直接，适用于大多数情况。
- **连通块检查**：使用BFS或并查集来检查连通块的大小和形状，确保每个连通块都是一个L形图案。这种方法较为通用，但实现较为复杂。
- **边界检查**：在找到L形图案后，检查其四周是否有其他`*`，确保L形图案之间没有边或角的接触。这种方法逻辑清晰，但代码复杂度较高。

### 可拓展之处

- **类似题目**：可以扩展到其他形状的图案判断，如T形、十字形等。
- **优化思路**：可以通过预处理或剪枝来减少枚举的次数，提高算法效率。

### 推荐题目

1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)

### 个人心得摘录

- **Binary_Lee**：通过耐心枚举所有可能的L形图案，虽然代码较长，但思路清晰，易于理解。
- **lihanwen12**：通过扫描每个格子，判断其是否能作为L形的一角，虽然代码复杂度较高，但逻辑清晰，易于调试。
- **include_BM**：通过判断是否有相邻的L形，并删除已找到的L形，最后检查是否有剩余的`*`，方法简洁高效，但逻辑较为复杂。

---
处理用时：50.33秒