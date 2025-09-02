# 题目信息

# [USACO16FEB] Milk Pails S

## 题目描述

Farmer John 接到了一份需要立即完成的订单，要求他提供恰好 $M$ 单位的牛奶（$1 \leq M \leq 200$）。不幸的是，他先进的挤奶机刚刚坏了，现在他只有两个容量为整数 $X$ 和 $Y$（$1 \leq X, Y \leq 100$）的牛奶桶可以用来量取牛奶。两个桶最初都是空的。使用这两个桶，他可以执行最多 $K$ 次以下类型的操作（$1 \leq K \leq 100$）：

- 他可以将任意一个桶完全装满。

- 他可以将任意一个桶完全倒空。

- 他可以将一个桶中的牛奶倒入另一个桶，直到前者被倒空或后者被装满（以先发生的情况为准）。

尽管 FJ 意识到他可能无法最终在两个桶中得到恰好 $M$ 单位的牛奶，但请帮助他计算 $M$ 与两个桶中牛奶总量之间的最小误差。也就是说，请计算 $|M-M'|$ 的最小值，其中 $M'$ 是 FJ 可以在两个桶中共同构造的牛奶量。

## 说明/提示

在两步操作中，FJ 可以在他的桶中留下以下数量的牛奶：

```
(0, 0) = 0 单位  
(14, 0) = 14 单位  
(0, 50) = 50 单位  
(0, 14) = 14 单位  
(14, 36) = 50 单位  
(14, 50) = 64 单位  
```

最接近 32 单位的是 14 单位，误差为 18。注意，要倒空第一个桶以得到 (0, 36) 需要额外的步骤。

## 样例 #1

### 输入

```
14 50 2 32```

### 输出

```
18```

# AI分析结果

### 综合分析与结论

本题的核心是通过有限的操作次数，找到两个桶中牛奶总量与目标值 $M$ 的最小误差。题解中主要采用了 **DFS**、**BFS** 和 **DP** 三种算法，其中 **BFS** 和 **DFS** 是最常见的解法，而 **DP** 则通过状态转移优化了空间复杂度。难点在于如何高效地剪枝和避免重复状态的计算。

### 所选高星题解

#### 1. 作者：SUNCHAOYI (4星)
- **关键亮点**：使用 **BFS** 进行状态搜索，通过 `vis` 数组避免重复状态，操作分类清晰，代码结构简洁。
- **个人心得**：注意递归边界条件，调试时发现 `if (num == k + 1)` 的边界问题，提醒了边界条件的设置重要性。

```cpp
void search (int num)
{
    queue <_pair> milk;
    if (num == k + 1) return ;
    while (!q.empty ())
    {
        _pair now = q.front (); q.pop ();
        ans = min (ans,abs (m - now.dx - now.dy));
        if (!vis[x][now.dy]) milk.push ({x,now.dy}),vis[x][now.dy] = 1;
        if (!vis[now.dx][y]) milk.push ({now.dx,y}),vis[now.dx][y] = 1;
        if (!vis[now.dx][0]) milk.push ({now.dx,0}),vis[now.dx][0] = 1;
        if (!vis[0][now.dy]) milk.push ({0,now.dy}),vis[0][now.dy] = 1;
        if (!vis[now.dx - min (now.dx,y - now.dy)][min (y,now.dy + now.dx)])
            milk.push ({now.dx - min (now.dx,y - now.dy),min (y,now.dy + now.dx)}),vis[now.dx - min (now.dx,y - now.dy)][min (y,now.dy + now.dx)] = 1;
        if (!vis[min (x,now.dx + now.dy)][now.dy - min (now.dy,x - now.dx)])
            milk.push ({min (x,now.dx + now.dy),now.dy - min (now.dy,x - now.dx)}),vis[min (x,now.dx + now.dy)][now.dy - min (now.dy,x - now.dx)] = 1;
    }
    while (!milk.empty ()) q.push (milk.front ()),milk.pop ();
    search (num + 1);
}
```

#### 2. 作者：SIGSEGV (4星)
- **关键亮点**：使用 **BFS** 并优化了状态扩展，通过 `vis` 数组记录状态，避免重复计算，代码简洁高效。
- **个人心得**：通过 `if(n.cnt == kk || n.x == 0 || n.y == 0)` 优化了状态扩展，减少了不必要的计算。

```cpp
void bfs()
{
    bool vis[101][101][101] = {}; memset(vis,0,sizeof(vis));
    queue<Node> q;
    q.push({0,0,0}); vis[0][0][0] = 1;
    while (!q.empty())
    {
        Node n = q.front(); q.pop();
        if(n.cnt == kk || n.x == 0 || n.y == 0)
        {
            ans = min(ans,abs(n.x + n.y - need));
            if (n.cnt == kk) continue;
        }
        int x = n.x, y = n.y, cnt = n.cnt + 1;
        if(!vis[b1][y][cnt]) q.push({b1,y,cnt}), vis[b1][y][cnt] = 1;
        if(!vis[x][b2][cnt]) q.push({x,b2,cnt}), vis[x][b2][cnt] = 1;
        if(!vis[0][y][cnt]) q.push({0,y,cnt}), vis[0][y][cnt] = 1;
        if(!vis[x][0][cnt]) q.push({x,0,cnt}), vis[x][0][cnt] = 1;
        int Y = x + y, X = 0;
        if(Y > b2) X = Y - b2, Y = b2;
        if(!vis[X][Y][cnt]) q.push({X,Y,cnt}), vis[X][Y][cnt] = 1;
        X = x + y, Y = 0;
        if(X > b1) Y = X - b1, X = b1;
        if(!vis[X][Y][cnt]) q.push({X,Y,cnt}), vis[X][Y][cnt] = 1;
    }
    printf("%d",ans);
}
```

#### 3. 作者：MuYC (4星)
- **关键亮点**：使用 **DFS** 并加入记忆化剪枝，通过 `D[S][L][R]` 记录状态，避免了重复搜索，代码逻辑清晰。
- **个人心得**：通过 `if(now > K) return ;` 和 `if(now >= D[S][L][R]) return ;` 两个剪枝条件，保证了搜索的高效性。

```cpp
void DFS(int S,int L,int R,int now)
{
    if(now > K) return ;
    if(now >= D[S][L][R]) return ;
    D[S][L][R] = now;
    if(L != X) DFS(X + R , X , R , now + 1);
    if(R != Y) DFS(L + Y , L , Y , now + 1);
    if(L != 0) DFS(R, 0 , R ,now + 1);
    if(R != 0) DFS(L, L , 0 , now + 1);
    if(R != 0 && L != X) DFS(S , L + min(X - L,R) , R - min(X - L,R), now + 1);
    if(L != 0 && R != Y) DFS(S , L - min(Y - R,L) , R + min(Y - R,L), now + 1);
    return ;
}
```

### 最优关键思路与技巧

1. **BFS 与 DFS 的选择**：BFS 适合求最短路径或最小操作次数，DFS 则适合状态空间较大的情况，结合记忆化剪枝可以大幅提升效率。
2. **状态记录与剪枝**：通过 `vis` 或 `D[S][L][R]` 记录状态，避免重复计算，是提升效率的关键。
3. **边界条件与优化**：合理设置边界条件（如操作次数限制）和优化状态扩展（如提前终止不必要的计算）可以显著减少计算量。

### 可拓展之处

本题的解法可以推广到类似的 **状态转移问题**，如 **倒水问题**、**拼图问题** 等，核心思想是通过有限的操作次数，找到最优解或最小误差。

### 推荐题目

1. **P1135 奇怪的电梯**：通过有限的操作次数，找到从起点到终点的最小步数。
2. **P1443 马的遍历**：通过有限的操作次数，找到从起点到终点的最短路径。
3. **P1219 八皇后问题**：通过有限的操作次数，找到所有合法的八皇后摆放方案。

### 个人心得总结

- **边界条件的重要性**：调试时发现边界条件设置错误，导致程序无法正确终止，提醒了边界条件的设置需要仔细检查。
- **剪枝的威力**：通过合理的剪枝条件，可以大幅减少搜索空间，提升程序效率。

---
处理用时：65.52秒