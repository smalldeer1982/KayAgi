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
这些题解主要围绕如何用最少的奶牛区间覆盖给定的时间段展开，提供了贪心、动态规划（DP）、最短路等多种解法。贪心算法通过排序和选择右端点最大的区间来逐步覆盖；DP 则通过状态转移方程计算最小覆盖数，可结合线段树优化；最短路算法通过建图将问题转化为求最短路径。不同解法各有优劣，贪心算法简单直观，时间复杂度较低；DP 适合解决有状态转移的问题，线段树优化可提升效率；最短路算法将问题转化为图论问题，思路巧妙。

### 所选题解
- **作者：Greenzhe（5星）**
  - **关键亮点**：思路清晰，对贪心算法的流程和正确性证明详细，代码简洁且注释清晰。
  - **个人心得**：作者首次做证明，欢迎勘误，体现了严谨的态度。
- **作者：MoonCake2011（4星）**
  - **关键亮点**：详细展示了从暴力区间 DP 到线性 DP 再到线段树优化 DP 的优化过程，有助于理解 DP 优化的思路。
  - **个人心得**：提到数据水，线性 DP 本应 60 分却能 100 分，提醒注意数据对结果的影响。
- **作者：Southern_Dynasty（4星）**
  - **关键亮点**：提供了最短路和 DP 两种解法，且对最短路解法考虑了数据加强后的离散化处理，思路全面。
  - **个人心得**：无

### 重点代码
#### Greenzhe 的贪心解法
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
**核心思想**：将区间按左端点排序，每次选择能覆盖当前最靠左未覆盖点且右端点最大的区间，更新未覆盖点，若找不到则无解。

#### MoonCake2011 的线段树优化 DP 解法
```cpp
int n,t;
int dp[int(4e6)+10];
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
struct node{
    int l,r;
}a[25010];
bool cmp(node x,node y){
    if(x.r!=y.r) return x.r<y.r;
    return x.l<y.l;
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
**核心思想**：设 `dp[i]` 为 `[1,i]` 区间需要用的线段的数量，用线段树维护 `dp` 数组的区间最小值，按右端点排序后进行状态转移。

#### Southern_Dynasty 的最短路解法
```cpp
struct edge{
    int to,nxt,w;
}e[N<<1];
int head[N],cnt,n,T,dis[N];
deque<int>dq;
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
**核心思想**：从 `l - 1` 到 `r` 连一条长度为 1 的边，从 `i` 到 `i - 1` 连一条长度为 0 的边，用 01BFS 求 0 到 `T` 的最短路。

### 最优关键思路或技巧
- **贪心算法**：按左端点排序，每次选择右端点最大的区间，可保证覆盖更多点且区间连续。
- **DP 优化**：用线段树维护 DP 数组的区间最小值，将时间复杂度从 $O(nt)$ 优化到 $O(n \log t)$。
- **最短路建图**：将问题转化为图论问题，通过建图和求最短路解决，边权只有 0 和 1 时可使用 01BFS 优化。

### 拓展思路
同类型题可考虑区间覆盖、区间选择等问题，类似算法套路有贪心策略选择、DP 状态设计与转移、图论建图与最短路求解等。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1107 繁忙的都市](https://www.luogu.com.cn/problem/P1107)

### 个人心得总结
- Greenzhe 首次做证明，体现严谨态度，提醒我们在算法学习中要注重证明的严谨性。
- MoonCake2011 提到数据水对结果的影响，提醒我们在做题时不能仅依赖数据，要确保算法的正确性和复杂度。

---
处理用时：61.50秒