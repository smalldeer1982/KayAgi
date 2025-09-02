# 题目信息

# Igor In the Museum

## 题目描述

Igor is in the museum and he wants to see as many pictures as possible.

Museum can be represented as a rectangular field of $ n×m $ cells. Each cell is either empty or impassable. Empty cells are marked with '.', impassable cells are marked with '\*'. Every two adjacent cells of different types (one empty and one impassable) are divided by a wall containing one picture.

At the beginning Igor is in some empty cell. At every moment he can move to any empty cell that share a side with the current one.

For several starting positions you should calculate the maximum number of pictures that Igor can see. Igor is able to see the picture only if he is in the cell adjacent to the wall with this picture. Igor have a lot of time, so he will examine every picture he can see.

## 样例 #1

### 输入

```
5 6 3
******
*..*.*
******
*....*
******
2 2
2 5
4 3
```

### 输出

```
6
4
10
```

## 样例 #2

### 输入

```
4 4 1
****
*..*
*.**
****
3 2
```

### 输出

```
8
```

# AI分析结果

### 题目内容
# Igor在博物馆

## 题目描述
Igor在博物馆，他想尽可能多地欣赏画作。

博物馆可以表示为一个 $n×m$ 的矩形区域，每个单元格要么为空，要么无法通行。空单元格用 '.' 表示，无法通行的单元格用 '*' 表示。每两个不同类型的相邻单元格（一个为空，一个无法通行）之间由一堵墙隔开，墙上挂着一幅画。

一开始Igor在某个空单元格中。在任何时刻，他都可以移动到与当前单元格共享一条边的任何空单元格。

对于几个起始位置，你需要计算Igor能看到的最大画作数量。只有当Igor位于与挂有这幅画的墙相邻的单元格中时，他才能看到这幅画。Igor有足够的时间，所以他会仔细欣赏他能看到的每一幅画。

## 样例 #1
### 输入
```
5 6 3
******
*..*.*
******
*....*
******
2 2
2 5
4 3
```
### 输出
```
6
4
10
```

## 样例 #2
### 输入
```
4 4 1
****
*..*
*.**
****
3 2
```
### 输出
```
8
```

### 算法分类
深度优先搜索 DFS、广度优先搜索 BFS

### 综合分析与结论
这些题解的核心思路都是围绕搜索展开，通过搜索找到询问点所在的连通块，并统计连通块内每个'.'周围'*'的数量。
- **思路方面**：大多题解采用深搜（DFS）或广搜（BFS）算法，从给定的起始点出发，遍历其所在的连通块。在遍历过程中，统计每个遍历到的'.'周围'*'的数量，累加得到最终答案。
- **算法要点**：需要使用合适的数据结构记录访问状态，避免重复访问，如使用二维数组标记已访问的单元格。同时，对于多次询问，部分题解利用时间戳或数组存储已计算的连通块答案，避免重复计算。
- **解决难点**：理解题意是关键难点，要明确是计算连通块内所有'.'周围'*'的数量，且'*'可以重复计算。

### 所选的题解
 - **作者：black_trees (5星)**
    - **关键亮点**：思路清晰，详细解读题目含义，代码注释详尽。通过深搜遍历连通块，用pre数组标记访问状态并区分不同询问，ans数组存储答案。
    - **个人心得**：强调读题的重要性，指出理解题意是本题难点。
    ```cpp
    void dfs(int x,int y){//深搜
        pre[x][y]=tmp;//tmp表示第tmp次询问（区分答案用的）
        for(register int i=1,nx,ny;i<=4;++i){
            nx=x+dx[i];
            ny=y+dy[i];
            if(nx<1||ny<1||nx>n||ny>m){
                continue;
            }//边界，搜出去就continue掉
            if(pre[nx][ny]){
                continue;
            }//如果pre数组被修改过了（已经有答案储存在ans数组了），那也continue掉
            if(d[nx][ny]=='*'){
                ans[tmp]++;//搜到*，计数器+（答案）+
            }
            else{
                dfs(nx,ny);//继续递归搜索
            }
        }
    }
    ```
 - **作者：durex_com (5星)**
    - **关键亮点**：运用时间戳存答案优化，代码简洁明了。通过深搜遍历连通块，vis数组标记访问状态，ans数组存储答案。
    ```cpp
    void dfs(int x,int y)
    {
        vis[x][y]=tro;
        for(int i=0;i<4;i++)
        {
            xx=x+dir1[i];
            yy=y+dir2[i];
            if (check(xx,yy)&&!vis[xx][yy])
            {
                if (map[xx][yy]==1) sum++;
                else {dfs(xx,yy);}
            }
        }
    }
    ```
 - **作者：Tyyyyyy (4星)**
    - **关键亮点**：指出翻译误导可能产生的错解，加深对题意的理解。通过深搜遍历连通块，vis数组标记访问状态，ans数组存储答案。
    ```cpp
    void dfs(int a,int b)//深搜
    {
        vis[a][b]=1;//已经搜过的‘.’做标记
        for(int i=0;i<4;i++)//向每个方向搜索
        {
            int na=a+dx[i],nb=b+dy[i];
            if(!vis[na][nb]&&can(na,nb))
            {
                if(mp[na][nb]==1)sum++;//如果是‘*’计数
                else dfs(na,nb);//若是‘.’继续搜索
            }
        }
    }
    ```

### 最优关键思路或技巧
- **状态标记**：使用二维数组（如vis、pre等）标记已访问的单元格，避免重复访问，提高搜索效率。
- **答案存储**：利用数组（如ans）存储已计算的连通块答案，对于重复询问可直接输出结果，减少重复计算。

### 可拓展之处
同类型题通常围绕连通块的搜索与统计，类似算法套路包括在不同地图结构（如三维地图）中搜索连通区域，或统计连通块内满足其他条件的元素数量。

### 洛谷相似题目
- [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：涉及图的搜索与最短路计算，与本题搜索思想相关。
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：通过搜索计算连通块大小，和本题搜索连通块思路类似。
- [P1314 聪明的质检员](https://www.luogu.com.cn/problem/P1314)：结合二分与搜索统计满足条件的元素，可锻炼搜索与其他算法结合的能力。

### 个人心得摘录与总结
多位作者提到读题的重要性，本题因翻译可能产生误解，需仔细研读英文原文明确题意，即计算连通块内所有'.'周围'*'的数量且可重复计算。 

---
处理用时：58.07秒