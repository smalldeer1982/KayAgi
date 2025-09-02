# 题目信息

# [ARC177C] Routing

## 题目描述

有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

## 样例 #1

### 输入

```
5

RBRBB

RBRRR

RRRBR

RBBRB

BBRBR```

### 输出

```
3```

## 样例 #2

### 输入

```
5

RBBBB

BBBBB

BBBBB

BBBBB

BBBBR```

### 输出

```
7```

## 样例 #3

### 输入

```
10

RRBBBBBBBB

BRRBBBBBBB

BBRRBBBBBB

BBBRRBBBBB

BBBBRRBBBB

BBBBBRRBBB

BBBBBBRRBB

BBBBBBBRRB

BBBBBBBBRR

BBBBBBBBBR```

### 输出

```
2```

## 样例 #4

### 输入

```
17

RBBRRBRRRRRBBBBBB

BBRBRBRRBRRBRRBBR

BRBRBBBRBBRBBRBBB

RBRRBBBBBBRRBRRRR

RRRRRBRBRRRBBRBBR

RRRRRBRRBRBBRRRBB

BBBRRRBRBRBBRRRBB

BBRRRBRBBBRBRRRBR

RRBBBBBBBBBBBRBRR

RRRBRRBRBRBRBRBBB

RRBRRRRBRBRRBRBBR

RRRBBRBRBBBRBBRBR

BBRBBRRBRRRBBRBBB

BBBRBRRRRRRRBBRBB

RRRRRBRBRBBRRBRRR

BRRRRBBBRRRBRRBBB

BBRRBBRRRBBBRBBBR```

### 输出

```
8```

# AI分析结果

### 题目内容（已为中文，无需翻译）
有一个 $N$ 行 $N$ 列（用 $(i, j)$ 表示矩阵第 $i$ 行第 $j$ 列的元素）的矩阵被刷满了红色和蓝色。现在要矩阵的一些格子刷上紫色，使得矩阵**同时**满足以下两个条件：
- 从 $(1, 1)$ 走到 $(N, N)$，保证存在一条路径使其只经过红色和紫色；
- 从 $(1, N)$ 走到 $(N, 1)$，保证存在一条路径使其只经过蓝色和紫色

注意，**行动时他可以往任何一个方向前进。**

那么，问题来了，至少要将多少格子刷成紫色才能使以上两个条件成立呢？

### 综合分析与结论
这些题解的核心思路一致，均是将原问题拆分为两个子问题：一是计算从 $(1, 1)$ 到 $(N, N)$ 最少经过多少蓝色格子；二是计算从 $(1, N)$ 到 $(N, 1)$ 最少经过多少红色格子，最后将两个结果相加得到答案。

算法要点方面，多数题解采用图论方法，把网格中的相邻格子视为有向边相连的节点，若终点颜色不符合路径要求则边权设为 1，否则为 0，再通过最短路算法求解。部分题解运用 01 BFS 优化，利用边权仅为 0 和 1 的特性，将复杂度优化至 $O(n^2)$。

难点在于证明两个子问题的修改互不影响，即改变一个路径所需的颜色不会对另一个路径产生影响。所有题解都清晰阐述了这一关键结论。

### 所选题解
- __Floze3__（5 星）
    - 关键亮点：思路清晰，详细解释了为何两次 BFS 不会重复计算相交格子的颜色改变次数，还提出使用 01 BFS 优化复杂度至 $O(n^2)$。
    - 核心代码：使用 01 BFS 求从起点到每个点的最短路。
```cpp
// 代码省略，可参考原提交记录
```
- what_can_I_do（4 星）
    - 关键亮点：给出完整代码实现，采用 01 BFS 求解，注释清晰，易于理解。
    - 核心代码：
```cpp
inline void bfs(int sx,int sy,int ex,int ey,char ch)
{
    q.push_front(aaa{sx,sy,(mp[sx][sy]!=ch)});
    dis[sx][sy]=(mp[sx][sy]!=ch);
    while(!q.empty())
    {
        aaa now=q.front();
        q.pop_front();
        if(now.x==ex&&now.y==ey)
        {
            ans+=dis[ex][ey];
            while(!q.empty()) q.pop_front();
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    dis[i][j]=1e9;
            return;
        }
        for(int i=0;i<4;i++)
        {
            int x=now.x+dx[i],y=now.y+dy[i];
            if(x<1||x>n||y<1||y>n) continue;
            if(dis[now.x][now.y]+(ch!=mp[x][y])<dis[x][y])
            {
                dis[x][y]=dis[now.x][now.y]+(ch!=mp[x][y]);
                if(ch!=mp[x][y])
                    q.push_back(aaa{x,y,dis[x][y]});
                else
                    q.push_front(aaa{x,y,dis[x][y]});
            }
        }
    }
}
```
- 破壁人罗辑（4 星）
    - 关键亮点：详细推导状态转移方程，使用广度优先搜索求解，复杂度为 $O(n^2)$。
    - 核心代码：
```cpp
queue<pair<int,int> >q,qp;
int cnt=1;q.push(make_pair(1,1));vis[1][1][0]=1;
while(cnt<n*n){
    if(q.empty())swap(q,qp);
    pair<int,int>p=q.front();q.pop();
    // 四个方向扩展
    //...
}
```

### 最优关键思路或技巧
- 思维方式：将原问题拆分为两个独立的子问题，分别计算不同颜色路径所需的最少颜色改变次数。
- 算法优化：利用边权仅为 0 和 1 的特性，使用 01 BFS 优化最短路算法，将复杂度从带 $\log$ 优化至 $O(n^2)$。

### 拓展思路
同类型题目通常涉及网格图的路径规划和颜色修改问题，可采用类似的拆分问题、建图求最短路的思路。例如，改变起点和终点、增加颜色种类或修改移动规则等。

### 推荐洛谷题目
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)
3. [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)

### 个人心得
题解中未包含个人心得相关内容。

---
处理用时：34.69秒