# 题目信息

# Polycarp and Hay

## 题目描述

The farmer Polycarp has a warehouse with hay, which can be represented as an $ n×m $ rectangular table, where $ n $ is the number of rows, and $ m $ is the number of columns in the table. Each cell of the table contains a haystack. The height in meters of the hay located in the $ i $ -th row and the $ j $ -th column is equal to an integer $ a_{i,j} $ and coincides with the number of cubic meters of hay in the haystack, because all cells have the size of the base $ 1×1 $ . Polycarp has decided to tidy up in the warehouse by removing an arbitrary integer amount of cubic meters of hay from the top of each stack. You can take different amounts of hay from different haystacks. Besides, it is allowed not to touch a stack at all, or, on the contrary, to remove it completely. If a stack is completely removed, the corresponding cell becomes empty and no longer contains the stack.

Polycarp wants the following requirements to hold after the reorganization:

- the total amount of hay remaining in the warehouse must be equal to $ k $ ,
- the heights of all stacks (i.e., cells containing a non-zero amount of hay) should be the same,
- the height of at least one stack must remain the same as it was,
- for the stability of the remaining structure all the stacks should form one connected region.

The two stacks are considered adjacent if they share a side in the table. The area is called connected if from any of the stack in the area you can get to any other stack in this area, moving only to adjacent stacks. In this case two adjacent stacks necessarily belong to the same area.

Help Polycarp complete this challenging task or inform that it is impossible.

## 说明/提示

In the first sample non-zero values make up a connected area, their values do not exceed the initial heights of hay stacks. All the non-zero values equal $ 7 $ , and their number is $ 5 $ , so the total volume of the remaining hay equals the required value $ k=7·5=35 $ . At that the stack that is on the second line and third row remained unaltered.

## 样例 #1

### 输入

```
2 3 35
10 4 9
9 9 7
```

### 输出

```
YES
7 0 7 
7 7 7 
```

## 样例 #2

### 输入

```
4 4 50
5 9 1 1
5 1 1 5
5 1 5 5
5 5 7 1
```

### 输出

```
YES
5 5 0 0 
5 0 0 5 
5 0 5 5 
5 5 5 0 
```

## 样例 #3

### 输入

```
2 4 12
1 1 3 1
1 6 2 4
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# Polycarp和干草
## 题目描述
农民Polycarp有一个干草仓库，可以将其表示为一个 $n×m$ 的矩形表格，其中 $n$ 是行数，$m$ 是表格中的列数。表格的每个单元格都包含一个干草堆。位于第 $i$ 行和第 $j$ 列的干草高度（单位：米）等于整数 $a_{i,j}$，并且与干草堆中的立方米数一致，因为所有单元格的底部面积均为 $1×1$。Polycarp决定整理仓库，从每个干草堆的顶部移除任意整数立方米的干草。你可以从不同的干草堆中取出不同数量的干草。此外，允许完全不碰某个干草堆，或者相反，将其完全移除。如果一个干草堆被完全移除，相应的单元格将变为空，不再包含干草堆。

Polycarp希望在重新整理后满足以下要求：
 - 仓库中剩余的干草总量必须等于 $k$。
 - 所有干草堆（即包含非零数量干草的单元格）的高度应该相同。
 - 至少有一个干草堆的高度必须保持不变。
 - 为了剩余结构的稳定性，所有干草堆应形成一个连通区域。

如果两个干草堆在表格中共享一条边，则认为它们是相邻的。如果从该区域内的任何一个干草堆出发，仅通过移动到相邻的干草堆，就可以到达该区域内的任何其他干草堆，则称该区域是连通的。在这种情况下，两个相邻的干草堆必然属于同一区域。

请帮助Polycarp完成这项具有挑战性的任务，或者告知他这是不可能的。
## 说明/提示
在第一个示例中，非零值构成一个连通区域，它们的值不超过干草堆的初始高度。所有非零值都等于 $7$，其数量为 $5$，因此剩余干草的总体积等于所需值 $k = 7·5 = 35$。此时，位于第二行第三列的干草堆保持不变。
## 样例 #1
### 输入
```
2 3 35
10 4 9
9 9 7
```
### 输出
```
YES
7 0 7 
7 7 7 
```
## 样例 #2
### 输入
```
4 4 50
5 9 1 1
5 1 1 5
5 1 5 5
5 5 7 1
```
### 输出
```
YES
5 5 0 0 
5 0 0 5 
5 0 5 5 
5 5 5 0 
```
## 样例 #3
### 输入
```
2 4 12
1 1 3 1
1 6 2 4
```
### 输出
```
NO
```
### 算法分类
搜索（结合并查集优化）
### 题解综合分析与结论
这两道题解均围绕如何满足题目中关于干草堆整理的一系列条件展开。
 - **Crazyouth的题解**：核心思路是对于每个点 $(i, j)$，若其值能整除 $k$ 且通过特定路径能到达的点数足够，就可完成目标。通过将相邻点按点权较小值连边，利用kruskal重构树解决仅经过特定边能到达点数的问题，最后通过bfs找到符合要求的点。时空复杂度为 $O(nm \log (nm))$。
 - **_edge_的题解**：先分析题目条件，发现可钦定一个 $a_{i,j}$ 不变并统计相邻的点。暴力做法是 $O(n^2m^2)$，通过将权值从大到小排序，利用并查集维护连通性，优化寻找相邻点的过程。
二者主要区别在于解决寻找满足条件的连通区域内点数的方法不同，Crazyouth采用kruskal重构树，_edge_采用并查集优化。

### 题解
 - **Crazyouth的题解**（3星）
   - **关键亮点**：利用kruskal重构树解决图上特定路径可达点数问题，思路较为新颖。
   - **核心代码片段**：
```cpp
// 建边
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=m;j++)
    {
        for(int l=0;l<2;l++)
        {
            int x=i+dx[l],y=j+dy[l];
            if(x<1||x>n||y<1||y>m) continue;
            e[++cnt]={hs(i,j),hs(x,y),min(a[i][j],a[x][y])};
        }
    }
}
// kruskal重构树
sort(e+1,e+cnt+1,[](edge a,edge b){return a.w>b.w;});
for(int i=1;i<2*n*m;i++) fa[i]=i;
ncnt=n*m;
for(int i=1;i<=cnt;i++)
{
    int u=e[i].u,v=e[i].v,w=e[i].w;
    int fu=find(u),fv=find(v);
    if(fu==fv) continue;
    ncnt++;
    ch[ncnt][0]=fu;ch[ncnt][1]=fv;W[ncnt]=w;
    fa[fu]=fa[fv]=ncnt;
}
// 后续通过重构树信息判断是否满足条件并输出结果
```
核心实现思想是先构建边集，通过kruskal算法构建重构树，后续利用重构树的信息判断是否存在满足条件的点，并找到这些点输出结果。
 - **_edge_的题解**（3星）
   - **关键亮点**：巧妙利用并查集优化暴力搜索过程，通过权值排序和并查集快速维护连通性。
   - **核心代码片段**：
```cpp
// 权值排序
sort(b+1,b+1+tot,cmp);
// 利用并查集维护连通性
for (int i=1;i<=tot;i++) {
    int xx=b[i].x,yy=b[i].y;A[xx][yy]=1;
    for (int j=0;j<4;j++) {
        int gx=xx+fx[j],gy=yy+fy[j];
        if (gx<1 || gy<1 || gx>n || gy>m) continue;
        if (A[gx][gy]==0) continue;
        int X=ys(xx,yy),Y=ys(gx,gy);
        mer(X,Y);
    }
    int X=ys(xx,yy);X=find_set(X);
    // 判断是否满足条件
    if (num[X]*b[i].v<k) continue; 
    if (k%b[i].v) continue;
    cout<<"YES\n";
    solve(xx,yy,k/b[i].v,b[i].v);
    return 0;
}
```
核心实现思想是先对权值排序，遍历过程中利用并查集合并相邻点维护连通性，同时判断当前连通块是否满足题目条件，满足则输出结果。

### 最优关键思路或技巧
二者都采用了优化搜索过程的技巧。_edge_通过权值排序结合并查集维护连通性，能快速判断当前连通块是否满足条件；Crazyouth利用kruskal重构树解决特定路径可达点数问题，为解决此类连通性和数值判断结合的问题提供了新思路。

### 可拓展之处
此类题目属于连通性与数值条件结合的问题，类似套路有通过图论算法（如并查集、最小生成树相关变形等）维护连通性，结合数值判断条件（整除、总和等）解决问题。同类型题可考虑一些在网格上进行操作，同时满足连通性和数值限制的题目。

### 洛谷相似题目推荐
 - [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：经典并查集题目，用于熟悉并查集基础操作。
 - [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：并查集模板题，巩固并查集的使用。
 - [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：结合图论和并查集，在动态过程中维护连通性，与本题利用并查集维护连通性有相似之处。

### 个人心得摘录与总结
本题解中未包含个人心得。 

---
处理用时：70.14秒