# 题目信息

# [USACO13FEB] Tractor S

## 题目描述

FJ有块农田太崎岖了，他要买一辆新拖拉机才能在这里巡视。这块农田由N x N个格子的非负整数表示高度(1<=N<=500)。拖拉机从当前格子走到相邻格子（东、南、西、北四个方向）的代价为高度差D，则FJ驶过这两个格子的拖拉机最少也要值D块钱。

FJ愿意花足够的钱买一辆新的拖拉机使得他能以最小的高度差走遍所有格子的一半(如果格子总数是奇数，那么一半的值为四舍五入的值)。因为FJ很懒，所以他找到你帮他编程计算他最小需要花多少钱买到符合这些要求的拖拉机。

## 样例 #1

### 输入

```
5 
0 0 0 3 3 
0 0 0 0 3 
0 9 9 3 3 
9 9 9 3 3 
9 9 9 9 3 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕两种思路展开：并查集 + 最小生成树和二分答案 + DFS（或 BFS）。并查集 + 最小生成树思路是将每个格子看作节点，相邻格子连边，边权为高度差绝对值，按边权排序后用并查集合并，当连通块大小超过一半时输出当前边权。二分答案 + DFS（或 BFS）思路是二分高度差，用 DFS 或 BFS 搜索连通块，判断连通块大小是否超过一半。

### 所选题解
- **作者：daihang (赞：46)，4星**
    - **关键亮点**：思路清晰，代码注释详细，对建图、集合大小维护等关键步骤有明确解释，使用快读优化输入。
    - **个人心得**：无
- **作者：Rainbow_qwq (赞：5)，4星**
    - **关键亮点**：对二分答案思路解释清晰，给出时间复杂度分析，代码使用宏定义简化循环。
    - **个人心得**：无
- **作者：曹老师 (赞：2)，4星**
    - **关键亮点**：思路简洁明了，使用二分加广搜，详细解释了二分的原因和过程。
    - **个人心得**：无

### 重点代码及核心实现思想
#### 并查集 + 最小生成树（daihang）
```cpp
// 边的结构体
struct node{
    int u,v,w;
    node(){}
    node(int uu,int vv,int ww){
        u=uu;
        v=vv;
        w=ww;
    }
}edge[maxn*maxn*4];

// 并查集查找函数
int find(int x){
    if(x==fa[x]) return x;
    else return fa[x]=find(fa[x]);
}

// 主函数部分
for(int i=1;i<tp;i++){
    int x=edge[i].u;
    int y=edge[i].v;
    int w=edge[i].w;
    x=find(x);
    y=find(y);
    if(x!=y){
        fa[x]=y;
        siz[y]+=siz[x];
        if(siz[y]>=(n*n+1)/2){
            cout<<w<<endl;
            return 0;
        }
    }
}
```
核心思想：先建图，将每个格子向相邻格子连边，边权为高度差绝对值。然后对边按权值排序，使用并查集合并节点，当某个连通块大小超过一半时，输出当前边权。

#### 二分答案 + DFS（Rainbow_qwq）
```cpp
// DFS 函数
int dfs(int x,int y,int k)
{
    vis[x][y]=1;
    int res=1;
    For(i,0,3)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>0&&yy>0&&xx<=n&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=k)
            res+=dfs(xx,yy,k);
    }
    return res;
}

// 二分答案的 check 函数
bool check(int k)
{
    memset(vis,0,sizeof vis);
    For(i,1,n)
        For(j,1,n)
            if(!vis[i][j])
                if(dfs(i,j,k)*2>=n*n)
                    return 1;
    return 0;
}

// 二分答案部分
while(l<=r)
{
    int mid=(l+r)>>1;
    if(check(mid))r=mid-1,ans=mid;
    else l=mid+1;
}
```
核心思想：二分高度差，对于每个中间值，用 DFS 搜索连通块，判断连通块大小是否超过一半。如果超过，则缩小右边界，否则扩大左边界。

#### 二分答案 + BFS（曹老师）
```cpp
// BFS 函数
int bfs(int x , int y , int k) {
    int res = 1;
    vis[x][y] = 1;
    queue<Node>q; 
    q.push(Node(x , y));
    while(!q.empty()) {
        Node u = q.front();
        q.pop();
        if(u.x-1>=1 && !vis[u.x-1][u.y] && myabs(map[u.x-1][u.y]-map[u.x][u.y])<=k) {
            vis[u.x-1][u.y] = 1;
            res++;
            q.push(Node(u.x-1,u.y));
        }
        if(u.x+1<=n && !vis[u.x+1][u.y] && myabs(map[u.x+1][u.y]-map[u.x][u.y])<=k) {
            vis[u.x+1][u.y] = 1;
            res++;
            q.push(Node(u.x+1,u.y));
        }
        if(u.y-1>=1 && !vis[u.x][u.y-1] && myabs(map[u.x][u.y-1]-map[u.x][u.y])<=k) {
            vis[u.x][u.y-1] = 1;
            res++;
            q.push(Node(u.x,u.y-1));
        }
        if(u.y+1<=n && !vis[u.x][u.y+1] && myabs(map[u.x][u.y+1]-map[u.x][u.y])<=k) {
            vis[u.x][u.y+1] = 1;
            res++;
            q.push(Node(u.x,u.y+1));
        }
    }
    return res;
}

// 判断函数
int jud(int x) {
    int ans = 0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(!vis[i][j])
                ans = mymax(ans , bfs(i,j,x));
    if(ans >= K)
        return 1;
    return 0;
} 

// 二分答案部分
while(l <= r) {
    memset(vis , 0 , sizeof(vis)); 
    int mid = (l+r)>>1;
    if(jud(mid))
        r = mid - 1;
    else
        l = mid + 1;
} 
```
核心思想：二分高度差，对于每个中间值，用 BFS 搜索连通块，找出最大连通块大小。如果最大连通块大小超过一半，则缩小右边界，否则扩大左边界。

### 最优关键思路或技巧
- **节点编号转化**：将二维坐标的格子转化为一维编号，方便存储和处理，如 `(i - 1) * n + j`。
- **二分答案**：对于求最大值最小化或最小值最大化的问题，二分答案是一种常用且有效的方法，将最优化问题转化为可行性问题。
- **并查集维护连通块**：使用并查集可以高效地合并和查询连通块信息，在最小生成树和判断连通性问题中很有用。

### 可拓展之处
同类型题或类似算法套路：
- 求满足某种条件的最小（大）值问题，可考虑二分答案，如二分图的最大匹配、网络流的最小费用等。
- 图的连通性问题，可使用并查集或 DFS、BFS 解决，如最小生成树、连通分量计数等。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)

### 个人心得摘录与总结
- **endless_loop**：在使用并查集时，不能直接使用连通块的个数小于一半来判断，而应该用 `size[i]` 表示 $i$ 所在连通块的大小，合并时更新 `size`，判断合并后的连通块是否满足大于总数的一半。总结：在处理连通块问题时，要准确判断连通块的大小，避免错误的判断条件。

---
处理用时：61.76秒