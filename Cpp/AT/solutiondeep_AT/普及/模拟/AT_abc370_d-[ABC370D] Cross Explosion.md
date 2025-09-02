# 题目信息

# [ABC370D] Cross Explosion

## 题目描述

有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i, j)$ 表示从上往下第 $i$ 行，从左往上第 $j$ 列的单元格。  
最初，每个单元格中都有一面墙。  
按照下面给出的顺序处理 $Q$ 个查询后，求剩余墙的数量。

在第 $q$ 次查询中，我们给出了两个整数 $R_q$ 和 $C_q$ 。  
您在 $(R_q, C_q)$ 处放置了一枚炸弹来摧毁墙壁。结果会发生以下过程。

- 如果在 $(R_q, C_q)$ 处有一堵墙，则摧毁这堵墙并结束进程。
- 如果 $(R_q, C_q)$ 处没有墙壁，则摧毁从 $(R_q, C_q)$ 向上、向下、向左、向右观察时出现的第一面墙壁。更确切地说，以下四个过程是同时进行的：
    - 如果存在一个 $i \lt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $i \lt k \lt R_q$ 的 $(k, C_q)$ 处都没有墙，则摧毁 $(i, C_q)$ 处的墙。
    - 如果存在一个 $i \gt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $R_q \lt k \lt i$ 的 $(k, C_q)$ 处都没有墙，则破坏 $(i, C_q)$ 处的墙。
    - 如果存在一个 $j \lt C_q$ ，使得在所有 $j \lt k \lt C_q$ 中， $(R_q, j)$ 处有一堵墙，而 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。
    - 如果存在一个 $j \gt C_q$ ，使得在 $(R_q, j)$ 处有一堵墙，而在所有 $C_q \lt k \lt j$ 的 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。

## 说明/提示

- $1 \leq H, W$
- $H \times W \leq 4 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq R_q \leq H$
- $1 \leq C_q \leq W$
- 所有输入值均为整数。

Translate by DeepL,Manually verified.

## 样例 #1

### 输入

```
2 4 3
1 2
1 2
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5 5
3 3
3 3
3 2
2 2
1 2```

### 输出

```
10```

## 样例 #3

### 输入

```
4 3 10
2 2
4 1
1 1
4 2
2 1
3 1
1 3
1 2
4 3
4 2```

### 输出

```
2```

# AI分析结果

### 题目中文重写
有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i, j)$ 表示从上往下第 $i$ 行，从左往右第 $j$ 列的单元格。  
最初，每个单元格中都有一面墙。  
按照下面给出的顺序处理 $Q$ 个查询后，求剩余墙的数量。

在第 $q$ 次查询中，我们给出了两个整数 $R_q$ 和 $C_q$ 。  
您在 $(R_q, C_q)$ 处放置了一枚炸弹来摧毁墙壁。结果会发生以下过程。

- 如果在 $(R_q, C_q)$ 处有一堵墙，则摧毁这堵墙并结束进程。
- 如果 $(R_q, C_q)$ 处没有墙壁，则摧毁从 $(R_q, C_q)$ 向上、向下、向左、向右观察时出现的第一面墙壁。更确切地说，以下四个过程是同时进行的：
    - 如果存在一个 $i \lt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $i \lt k \lt R_q$ 的 $(k, C_q)$ 处都没有墙，则摧毁 $(i, C_q)$ 处的墙。
    - 如果存在一个 $i \gt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $R_q \lt k \lt i$ 的 $(k, C_q)$ 处都没有墙，则破坏 $(i, C_q)$ 处的墙。
    - 如果存在一个 $j \lt C_q$ ，使得在所有 $j \lt k \lt C_q$ 中， $(R_q, j)$ 处有一堵墙，而 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。
    - 如果存在一个 $j \gt C_q$ ，使得在 $(R_q, j)$ 处有一堵墙，而在所有 $C_q \lt k \lt j$ 的 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。

### 综合分析与结论
这些题解主要围绕如何高效模拟炸弹摧毁墙壁的过程展开，核心在于优化查找和删除墙壁的操作，以避免暴力方法带来的高时间复杂度。

#### 思路对比
- **`std::set` 维护行列法**：多数题解采用此思路，通过 `std::set` 分别维护每行和每列剩余墙的位置，利用 `upper_bound` 或 `lower_bound` 函数快速定位要删除的墙，时间复杂度为 $O(Q\log (HW))$。
- **并查集路径压缩法**：部分题解使用并查集，为每个点维护四个方向的并查集，存储对应方向离其最近的未删除点坐标，利用路径压缩优化查找过程，时间复杂度也能控制在可接受范围。
- **树状数组二分法**：通过树状数组维护同一行或列两点间的实心格子数，利用二分查找“最后一个与 $(R_i,C_i)$ 之间没有实心格子的点”。

#### 算法要点
- **`std::set` 法**：插入初始墙的位置，每次操作时，先判断目标位置是否有墙，有则直接删除，没有则在 `set` 中查找并删除上下左右最近的墙。
- **并查集法**：初始化每个点的四个方向并查集指向自身，删除点时更新并查集，查找时进行路径压缩。
- **树状数组二分法**：用树状数组存储网格，每次操作时通过二分查找确定要删除的墙，更新树状数组。

#### 难点解决
- 暴力查找时间复杂度高，通过 `std::set` 的二分查找、并查集的路径压缩和树状数组的二分查找优化。
- 处理边界情况和迭代器合法性，避免越界错误。

### 高评分题解
1. **作者：沉石鱼惊旋（5星）**
    - **关键亮点**：提供了 `std::set` 和并查集两种思路及完整代码，思路清晰，代码注释详细，对两种方法的解释和示例都很到位。
    - **核心代码（`std::set` 法）**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int h, w, q;
set<int> sr[400020];
set<int> sc[400020];
void del(int r, int c)
{
    sr[r].erase(c);
    sc[c].erase(r);
}
int ans;
int main()
{
    cin >> h >> w >> q;
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            sr[i].insert(j);
            sc[j].insert(i);
        }
    }
    while (q--)
    {
        int r, c;
        cin >> r >> c;
        if (sr[r].count(c))
        {
            del(r, c);
            continue;
        }
        if (!sr[r].empty())
        {
            auto it = sr[r].upper_bound(c);
            if (it!= sr[r].end())
                del(r, *it);
            if (!sr[r].empty())
            {
                it = sr[r].upper_bound(c);
                if (it!= sr[r].begin())
                    it--, del(r, *it);
            }
        }
        if (!sc[c].empty())
        {
            auto it = sc[c].upper_bound(r);
            if (it!= sc[c].end())
                del(*it, c);
            if (!sc[c].empty())
            {
                it = sc[c].upper_bound(r);
                if (it!= sc[c].begin())
                    it--, del(*it, c);
            }
        }
    }
    for (int i = 1; i <= h; i++)
        ans += sr[i].size();
    cout << ans << endl;
    return 0;
}
```
核心实现思想：用 `sr` 数组存储每行剩余列的集合，`sc` 数组存储每列剩余行的集合。每次操作时，先判断目标位置是否有墙，有则直接删除，没有则在对应行和列的 `set` 中查找并删除上下左右最近的墙，最后统计剩余墙的数量。

2. **作者：PineappleSummer（4星）**
    - **关键亮点**：思路简洁明了，代码实现清晰，对 `std::set` 的使用和操作过程解释清晰。
    - **核心代码**：
```cpp
set <int> h[N], w[N];
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            h[i].insert (j), w[j].insert (i);
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (h[x].find (y)!= h[x].end ()) {
            h[x].erase (y);
            w[y].erase (x);
        }
        else {
            auto i = h[x].lower_bound (y);
            vector <int> v;
            if (i!= h[x].end ()) v.push_back (*i);
            if (i!= h[x].begin ()) v.push_back (*(--i));
            for (auto j : v) h[x].erase (j), w[j].erase (x);

            v.clear ();
            i = w[y].lower_bound (x);
            if (i!= w[y].end ()) v.push_back (*i);
            if (i!= w[y].begin ()) v.push_back (*(--i));
            for (auto j : v) w[y].erase (j), h[j].erase (y);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += h[i].size ();
    cout << ans;
    return 0;
}
```
核心实现思想：用 `h` 数组存储每行剩余列的集合，`w` 数组存储每列剩余行的集合。每次操作时，先判断目标位置是否有墙，有则直接删除，没有则在对应行和列的 `set` 中查找并删除上下左右最近的墙，最后统计剩余墙的数量。

3. **作者：zhouzihang1（4星）**
    - **关键亮点**：采用并查集路径压缩的思路，对如何使用并查集快速查找上下左右第一堵墙的解释清晰，代码实现规范。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,q,ans;
vector<pair<int,int> > init_;
vector<bool> init__;
vector<vector<bool> > vis;
vector<vector<pair<int,int> > > t[4];
bool check(pair<int,int> pos)
{
    int x=pos.first,y=pos.second;
    return x>=1&&x<=n&&y>=1&&y<=m;
}
pair<int,int> find(int d,int x,int y)
{
    if(!vis[x][y]||!check({x,y})) return {x,y};
    int nx=t[d][x][y].first,ny=t[d][x][y].second;
    return t[d][x][y]=find(d,nx,ny);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    ans=n*m;
    for(int i=0;i<=m+1;i++) init__.push_back(0),init_.push_back({0,0});
    for(int i=0;i<=n+1;i++)
        vis.push_back(init__);
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<4;j++)
            t[j].push_back(init_);
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=m+1;j++)
        {
            if(1<=i&&i<=n&&1<=j&&j<=m)
            {
                t[0][i][j]={i-1,j};
                t[1][i][j]={i+1,j};
                t[2][i][j]={i,j-1};
                t[3][i][j]={i,j+1};
                continue;
            }
            for(int k=0;k<4;k++)
                t[k][i][j]={i,j};
        }
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(!vis[x][y])
        {
            vis[x][y]=1;
            ans--;
            continue;
        }
        pair<int,int> pos0=find(0,x,y);
        pair<int,int> pos1=find(1,x,y);
        pair<int,int> pos2=find(2,x,y);
        pair<int,int> pos3=find(3,x,y);
        if(check(pos0)) ans--,vis[pos0.first][pos0.second]=1;
        if(check(pos1)) ans--,vis[pos1.first][pos1.second]=1;
        if(check(pos2)) ans--,vis[pos2.first][pos2.second]=1;
        if(check(pos3)) ans--,vis[pos3.first][pos3.second]=1;
    }
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：用 `t` 数组存储每个点四个方向的并查集，`vis` 数组标记点是否被拆除。每次操作时，先判断目标位置是否有墙，有则直接拆除，没有则通过 `find` 函数查找四个方向的第一堵墙并拆除，使用路径压缩优化查找过程。

### 最优关键思路或技巧
- 使用 `std::set` 维护每行和每列剩余墙的位置，利用其 $O(\log n)$ 的二分查找和删除操作，高效定位和删除墙。
- 并查集路径压缩，避免在查找过程中多次遍历已删除的点，将查找复杂度优化到接近常数级别。

### 拓展思路
同类型题可能涉及二维网格上的其他操作，如移动、连通性判断等。类似算法套路包括使用数据结构（如线段树、树状数组）优化查找和更新操作，利用并查集处理连通性问题。

### 洛谷相似题目推荐
1. [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：涉及并查集和逆向思维，与本题的并查集思路有一定相似性。
2. [P2078 朋友](https://www.luogu.com.cn/problem/P2078)：经典的并查集应用，可加深对并查集的理解。
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)：使用 `std::set` 或其他平衡树数据结构解决问题，与本题的 `std::set` 思路类似。

### 个人心得摘录与总结
- **作者：天使宝贝**：吐槽很多大佬说题目卡常，但自己觉得不卡。总结：不同人对题目复杂度和卡常的感受可能不同，要根据实际情况分析。
- **作者：_H17_**：最初使用链表维护，但更新复杂度高，后通过路径压缩优化，控制住时间复杂度。总结：在算法实现过程中，可能会遇到复杂度高的问题，可通过优化技巧（如路径压缩）解决。 

---
处理用时：73.89秒