# 题目信息

# [USACO04DEC] Cleaning Shifts S

## 题目描述

一天有 $T(1\le T\le 10^6)$ 个时段。约翰正打算安排他的 $N(1\le N\le 2.5\times 10^4)$ 只奶牛来值班，打扫打扫牛棚卫生。每只奶牛都有自己的空闲时间段 $ [S_i,E_i](1\le S_i\le E_i\le T)$，只能把空闲的奶牛安排出来值班。而且，每个时间段必需有奶牛在值班。

那么，最少需要动用多少奶牛参与值班呢？如果没有办法安排出合理的方案，就输出 $-1$。

## 说明/提示

$1\le T\le 10^6$，$N\le 2.5\times 10^4$，$1\le S_i\le E_i\le T$。

$\text{Update On 2023/08/08}$：添加了一组hack数据，详情见[这里](https://www.luogu.com.cn/discuss/613052)。叉掉了时间复杂度为 $\mathcal O(nt)$ 的错解。

## 样例 #1

### 输入

```
3 10
1 7
3 6
6 10```

### 输出

```
2```

# AI分析结果

### 综合分析与结论
这些题解主要采用了贪心、动态规划（DP）和最短路三种算法思路来解决区间覆盖问题。贪心算法通过排序和选择最优区间来逐步覆盖目标区间；DP 算法则通过定义状态和状态转移方程来求解最小覆盖区间数；最短路算法将问题转化为图的最短路问题进行求解。

### 所选题解
- **作者：Greenzhe（5星）**
    - **关键亮点**：思路清晰，贪心算法的正确性和最优性证明详细，代码简洁易懂，使用双指针实现算法，时间复杂度较低。
    - **核心代码**：
```cpp
struct segment{
    int l,r;
    bool operator<(const segment &x) const{
        return l<x.l;
    }
}range[25005];

int main(){
    int n,ed;
    scanf("%d%d",&n,&ed);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&range[i].l,&range[i].r);
    sort(range+1,range+n+1);
    int st=1,ans=0;
    for(int i=1,j=1;i<=n;){
        int r=0;
        while(j<=n&&range[j].l<=st){
            r=max(r,range[j].r);
            j++;
        }
        if(r<st) break;
        ans++;
        if(r>=ed){
            printf("%d\n",ans);
            return 0;
        }
        st=r+1;i=j;
    }
    printf("-1\n");
    return 0;
}
```
    - **核心实现思想**：先将所有区间按左端点从小到大排序，然后使用双指针，在能覆盖当前最靠左未覆盖点的区间中选择右端点最大的区间，更新未覆盖点，直到覆盖整个目标区间或无法继续覆盖。

- **作者：MoonCake2011（4星）**
    - **关键亮点**：详细展示了 DP 算法从暴力到优化的全过程，包括区间 DP 到线性 DP 再到线段树优化 DP，有助于理解 DP 算法的优化思路。
    - **核心代码（线段树优化 DP）**：
```cpp
void build(int root,int l,int r){
    if(l==r){
        dp[root]=1e9;
        return;
    }
    int mid=l+r>>1;
    build(root*2,l,mid);
    build(root*2+1,mid+1,r);
    dp[root]=min(dp[root*2],dp[root*2+1]);
}
void update(int x,int k,int root=1,int l=1,int r=t){
    if(l==r && l==x){
        dp[root]=k;
        return;
    }
    int mid=l+r>>1;
    if(x>=l && x<=mid) update(x,k,root*2,l,mid);
    else update(x,k,root*2+1,mid+1,r);
    dp[root]=min(dp[root*2],dp[root*2+1]);
}
int get_min(int l,int r,int root=1,int x=1,int y=t){
    if(x>=l && y<=r) return dp[root];
    int mid=x+y>>1;
    int tot=1e9;
    if(l<=mid) tot=min(get_min(l,r,root*2,x,mid),tot);
    if(r>mid) tot=min(get_min(l,r,root*2+1,mid+1,y),tot);
    return tot; 
}

int main() {
    cin>>n>>t;
    build(1,0,t);
    for(int i=1;i<=n;i++){
        cin>>a[i].l>>a[i].r;
        if(a[i].l==1) update(a[i].r,1);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        int p=min(get_min(a[i].r,a[i].r),get_min(a[i].l-1,a[i].r-1)+1);
        update(a[i].r,p);
    }
    int p=get_min(t,t);
    if(p==1e9) cout<<-1;
    else cout<<p;
    return 0;
}
```
    - **核心实现思想**：设 `dp[i]` 为 `[1,i]` 区间需要用的线段的数量，用线段树维护 `dp` 数组，通过线段树的区间查询和单点修改操作优化状态转移方程的求解。

- **作者：Southern_Dynasty（4星）**
    - **关键亮点**：提供了最短路和 DP 两种解法，并且考虑了数据范围增大时的离散化处理，代码实现完整。
    - **核心代码（最短路）**：
```cpp
inline void add_edge(int f,int t,int w){
    e[++cnt].to=t;
    e[cnt].w=w;
    e[cnt].nxt=head[f];
    head[f]=cnt;
}
inline void BFS_01(int s){
    memset(dis,0x3f3f3f3f,sizeof(dis));
    dis[s]=0;
    dq.push_back(s);
    while(dq.size()){
        int u=dq.front();
        dq.pop_front();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to,w=e[i].w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(w) dq.push_back(v);
                else dq.push_front(v);
            }
        }
    }
}

signed main(){
    read(n,T);
    for(int i=1;i<=T;++i) add_edge(i,i-1,0);
    for(int u,v,i=1;i<=n;++i){
        read(u,v);
        add_edge(u-1,v,1);
    }
    BFS_01(0);
    println(dis[T]==0x3f3f3f3f?-1:dis[T]);
    return 0;
}
```
    - **核心实现思想**：将问题转化为图的最短路问题，从 `l-1` 到 `r` 连一条长度为 1 的边，从 `i` 到 `i-1` 连一条长度为 0 的边，使用 01BFS 求解从 0 到 `T` 的最短路。

### 最优关键思路或技巧
- **贪心算法**：按左端点排序，在能覆盖当前未覆盖点的区间中选择右端点最大的区间，可保证覆盖的连续性和最优性。
- **DP 算法**：使用线段树优化 DP 数组的区间查询和单点修改操作，将时间复杂度从 $O(nt)$ 优化到 $O(n \log t)$。
- **最短路算法**：将区间覆盖问题转化为图的最短路问题，通过连边和最短路算法求解。

### 可拓展之处
- **同类型题**：区间选点问题、最大不相交区间问题等。
- **类似算法套路**：贪心算法常用于求解最优选择问题，DP 算法适用于有重叠子问题和最优子结构的问题，最短路算法可用于解决图的路径优化问题。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1250 种树](https://www.luogu.com.cn/problem/P1250)

### 个人心得摘录与总结
- **作者：Greenzhe**：第一次做证明，如有勘误，敬请指教。总结：在分享算法时，严谨的证明和开放的态度很重要。
- **作者：MoonCake2011**：尝试区间 DP 变成线性 DP，实际骗得 100 分，数据还是过于淼了。总结：在算法学习中，不断尝试优化算法，同时要注意数据的强度对结果的影响。
- **作者：HDZmessi**：这段代码直接提交会 TLE 一个点，开个 O2 就行了！总结：代码性能不足时，编译器优化有时可以解决问题，但仍需考虑算法本身的优化。

---
处理用时：54.00秒