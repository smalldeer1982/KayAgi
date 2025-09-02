# 题目信息

# Inna and Dima

## 题目描述

Inna and Dima bought a table of size $ n×m $ in the shop. Each cell of the table contains a single letter: "D", "I", "M", "A".

Inna loves Dima, so she wants to go through his name as many times as possible as she moves through the table. For that, Inna acts as follows:

1. initially, Inna chooses some cell of the table where letter "D" is written;
2. then Inna can move to some side-adjacent table cell that contains letter "I"; then from this cell she can go to one of the side-adjacent table cells that contains the written letter "M"; then she can go to a side-adjacent cell that contains letter "A". Then Inna assumes that she has gone through her sweetheart's name;
3. Inna's next move can be going to one of the side-adjacent table cells that contains letter "D" and then walk on through name DIMA in the similar manner. Inna never skips a letter. So, from the letter "D" she always goes to the letter "I", from the letter "I" she always goes the to letter "M", from the letter "M" she always goes to the letter "A", and from the letter "A" she always goes to the letter "D".

Depending on the choice of the initial table cell, Inna can go through name DIMA either an infinite number of times or some positive finite number of times or she can't go through his name once. Help Inna find out what maximum number of times she can go through name DIMA.

## 说明/提示

Notes to the samples:

In the first test sample, Inna cannot go through name DIMA a single time.

In the second test sample, Inna can go through the infinite number of words DIMA. For that, she should move in the clockwise direction starting from the lower right corner.

In the third test sample the best strategy is to start from the cell in the upper left corner of the table. Starting from this cell, Inna can go through name DIMA four times.

## 样例 #1

### 输入

```
1 2
DI
```

### 输出

```
Poor Dima!
```

## 样例 #2

### 输入

```
2 2
MA
ID
```

### 输出

```
Poor Inna!
```

## 样例 #3

### 输入

```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
```

### 输出

```
4
```

# AI分析结果

### 题目翻译
#### Inna和Dima

### 题目描述
Inna和Dima在商店买了一张大小为 $n×m$ 的桌子。桌子的每个单元格都包含一个字母：“D”、“I”、“M”、“A”。

Inna爱Dima，所以她想在遍历桌子时尽可能多地走过他的名字。为此，Inna的行动如下：
1. 最初，Inna选择桌子上写有字母“D”的某个单元格；
2. 然后Inna可以移动到相邻的包含字母“I”的单元格；接着从这个单元格，她可以移动到相邻的包含字母“M”的单元格；然后她可以移动到相邻的包含字母“A”的单元格。这时Inna认为她已经走过了她爱人的名字；
3. Inna的下一步行动可以是移动到相邻的包含字母“D”的单元格，然后以类似的方式继续走过名字DIMA。Inna从不跳过字母。所以，从字母“D”她总是移动到字母“I”，从字母“I”她总是移动到字母“M”，从字母“M”她总是移动到字母“A”，从字母“A”她总是移动到字母“D”。

根据初始单元格的选择，Inna可以无限次地走过名字DIMA，或者走过有限的正整数次，或者一次都走不过。帮助Inna找出她最多能走过名字DIMA的次数。

### 说明/提示
示例说明：
- 在第一个测试示例中，Inna一次都不能走过名字DIMA。
- 在第二个测试示例中，Inna可以无限次地走过名字DIMA。为此，她应该从右下角开始按顺时针方向移动。
- 在第三个测试示例中，最佳策略是从桌子的左上角单元格开始。从这个单元格开始，Inna可以走过名字DIMA四次。

### 样例 #1
#### 输入
```
1 2
DI
```
#### 输出
```
Poor Dima!
```

### 样例 #2
#### 输入
```
2 2
MA
ID
```
#### 输出
```
Poor Inna!
```

### 样例 #3
#### 输入
```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
```
#### 输出
```
4
```

### 综合分析与结论
- **思路对比**：所有题解核心思路都是以 `D` 为起点，按 `D -> I -> M -> A -> D` 顺序遍历，用 DFS 找最长路，判断是否有环。不同在于建图方式，有的用邻接表，有的用 `vector` 存图。
- **算法要点**：
    - 建图：对每个格子判断相邻格子是否符合行走顺序，符合则建边。
    - DFS：记录最长路，用 `vis` 数组判环。
    - 结果处理：有环输出 `Poor Inna!`，无环计算走过 `DIMA` 次数，次数为 0 输出 `Poor Dima!`，否则输出次数。
- **解决难点**：
    - 建图：要正确处理每个格子的相邻关系，保证边的连接符合行走规则。
    - 判环：用 `vis` 数组标记当前路径上的点，若再次访问则有环。
    - 最长路记录：用数组记录每个点出发的最长路，避免重复计算。

### 所选题解
- **作者：Komorebi_03（5星）**
    - **关键亮点**：思路清晰，代码注释详细，建图和 DFS 过程实现规范，对判环和最长路记录处理得当。
    - **个人心得**：作者表示这道题看似简单，但调试了半个下午，说明实际实现中可能会遇到一些细节问题。
```cpp
// 建图
void build_mp()
{
    int js=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            mp[i][j]=++js;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            for (int k=0;k<4;k++)
            {
                int x=i+nx[k];
                int y=j+ny[k];
                if(x<1 || x>n || y<1 || y>m)
                    continue;
                if(s[i][j]=='D' && s[x][y]=='I')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='I' && s[x][y]=='M')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='M' && s[x][y]=='A')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='A' && s[x][y]=='D')
                    add(mp[i][j],mp[x][y]);
            }
        }
    }
}
// DFS
void DFS(int u)
{
    if(dis[u])
        return ;
    dis[u]=1;
    vis[u]=true;
    for (int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].v;
        if(vis[v])
        {
            flag=true;
            vis[u]=false;
            return ;
        }
        DFS(v);
        if(flag)
        {
            vis[u]=false;
            return ;
        }
        dis[u]=max(dis[u],dis[v]+1);
    }
    vis[u]=false;
}
```
- **作者：Constant（4星）**
    - **关键亮点**：详细阐述思路，提出用 `SPFA` 跑最长路但因复杂度问题改用 DFS，对编号技巧说明清晰。
```cpp
// 建图
void Add(int s,int e)
{
    nex[++num]=first[s];
    first[s]=num;
    v[num]=e;
}
// DFS
void dfs(int s) 
{
    if(path[s]) return;
    vis[s]=1;
    path[s]=1;
    for(int i=first[s];i!=-1;i=nex[i]) 
    {
        int j=v[i];
        if(vis[j]) 
        {
            bj=1;
            vis[s]=0;
            return;
        }
        dfs(j);
        if(bj==1)
        {
            vis[s]=0;
            return;
        }
        path[s]=max(path[s],path[j]+1);
    }
    vis[s]=0;
}
```
- **作者：_Sonnet（4星）**
    - **关键亮点**：思路简洁，对建边和判环说明清晰，代码结构清晰。
```cpp
// 建图
void build()
{
    int cnt = 0;
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++)
        {
            a[i][j] = ++ cnt;
        }
    }
    for(int i = 1 ; i <= n; i ++)
    {
        for(int j = 1 ; j <= m; j ++)
        {
            for(int k = 0 ; k < 4; k ++) 
            {
                int dx = i + xx[k], dy = j + yy[k];
                if(dx < 1 || dy < 1 || dx > n || dy > m) 
                    continue;
                if(s[i][j] == 'D' && s[dx][dy] == 'I') 
                    add(a[i][j], a[dx][dy]);
                if(s[i][j] == 'I' && s[dx][dy] == 'M') 
                    add(a[i][j], a[dx][dy]);
                if(s[i][j] == 'M' && s[dx][dy] == 'A') 
                    add(a[i][j], a[dx][dy]);
                if(s[i][j] == 'A' && s[dx][dy] == 'D') 
                    add(a[i][j], a[dx][dy]);
            }
        }
    }
}
// DFS
void dfs(int s) {
    if(dis[s]) 
        return;
    vis[s] = 1;
    dis[s] = 1;
    for(int i = head[s]; ~ i; i = ne[i]) 
    {
        int v = to[i];
        if(vis[v]) 
        {
            flag = 1;
            vis[s] = 0;
            return;
        }
        dfs(v);
        if(flag) 
        {
            vis[s] = 0;
            return;
        }
        dis[s] = max(dis[s], dis[v] + 1);
    }
    vis[s] = 0;
}
```

### 最优关键思路或技巧
- **建图**：用编号将二维坐标转为一维，方便处理和存储边。
- **DFS判环**：用 `vis` 数组标记当前路径上的点，再次访问则有环。
- **记忆化搜索**：用数组记录每个点出发的最长路，避免重复计算。

### 可拓展之处
同类型题如在网格图中按特定规则行走求最长路径或判断是否有环，可使用类似建图和 DFS 方法。类似算法套路有拓扑排序判环、BFS 求最短路径等。

### 推荐题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：在电梯中按特定规则移动，求最短步数。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：在迷宫中按规则行走，求路径数量。
- [P2895 [USACO08FEB]Meteor Shower S](https://www.luogu.com.cn/problem/P2895)：在网格图中躲避流星，求最短逃生时间。

### 个人心得摘录与总结
- **Komorebi_03**：这道题看似很水但让我调了半个下午，说明实际实现中可能会遇到一些细节问题，需要仔细调试。
- **PDAST**：空间一定要开够，要利用 STL 合理优化，节省空间，判环时一定要仔细检查，因判环导致死循环，空间炸了，调了半小时没调出来，强调了空间使用和判环的重要性。 

---
处理用时：50.15秒