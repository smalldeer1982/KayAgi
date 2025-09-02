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
本题要求从 $n$ 个区间中选择最少的区间覆盖 $[1, T]$，题解主要涉及贪心、动态规划（DP）和最短路三种思路。
- **贪心思路**：将区间按左端点排序，每次在能覆盖当前最靠左未覆盖点的区间中选右端点最大的，更新未覆盖点，若找不到能覆盖的区间则无解。实现简单，时间复杂度较低。
- **DP思路**：设 $dp_i$ 表示覆盖 $[1, i]$ 的最小区间数，状态转移时需枚举区间，朴素 DP 复杂度高，可借助线段树优化到 $O(N\log T)$。
- **最短路思路**：将问题转化为图的最短路问题，从 $l - 1$ 到 $r$ 连边权为 1 的边，$i$ 到 $i - 1$ 连边权为 0 的边，求 0 到 $T$ 的最短路，可使用 01BFS 或 Dijkstra 算法，涉及离散化处理可应对大数据范围。

### 所选题解
- **作者：Greenzhe（5星）**
    - **关键亮点**：思路清晰，详细阐述贪心算法流程并给出严格证明，代码简洁易懂，双指针实现高效。
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
- **作者：MoonCake2011（4星）**
    - **关键亮点**：循序渐进展示 DP 优化过程，从区间 DP 到线性 DP 再到线段树优化，详细推导状态转移方程，对理解 DP 优化有很大帮助。
    - **核心代码（线段树优化部分）**：
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
```
- **作者：Southern_Dynasty（4星）**
    - **关键亮点**：提供最短路和 DP 两种解法，对最短路建图思路解释清晰，还考虑了数据范围增大时的离散化处理，代码规范，注释详细。
    - **核心代码（最短路离散化部分）**：
```cpp
int n,T,dis[N],lsh[N<<1],tot,u[N],v[N];
deque<int>dq;
// 离散化
lsh[++tot]=S;
for(int i=1;i<=n;++i){
    read(u[i],v[i]);
    lsh[++tot]=u[i]-1,lsh[++tot]=v[i];
}
lsh[++tot]=T;
sort(lsh+1,lsh+tot+1);
tot=unique(lsh+1,lsh+tot+1)-(lsh+1);
for(int i=1;i<=n;++i){
    u[i]=lower_bound(lsh+1,lsh+tot+1,u[i]-1)-lsh;
    v[i]=lower_bound(lsh+1,lsh+tot+1,v[i])-lsh; 
    add_edge(u[i],v[i],1);
}
S=lower_bound(lsh+1,lsh+tot+1,S)-lsh;
T=lower_bound(lsh+1,lsh+tot+1,T)-lsh;
for(int i=S+1;i<=T;++i) add_edge(i,i-1,0);
BFS_01(S);
```

### 最优关键思路或技巧
- **贪心策略**：按左端点排序后，每次选右端点最大的区间，保证覆盖范围最大且区间数最少。
- **线段树优化 DP**：将状态转移中的区间最小值查询问题用线段树解决，把时间复杂度从 $O(NT)$ 优化到 $O(N\log T)$。
- **最短路建图**：通过合理建图将区间覆盖问题转化为最短路问题，边权设置体现区间选择代价，可使用 01BFS 或 Dijkstra 求解。

### 拓展思路
同类型题或类似算法套路：
- **区间覆盖问题**：如给定多个区间，求最少区间覆盖指定区间，可使用贪心或 DP 解决。
- **最短路建模**：将实际问题抽象为图的最短路问题，通过合理建图和选择合适的最短路算法求解。
- **DP 优化**：当 DP 状态转移涉及区间最值查询时，可考虑用线段树、树状数组等数据结构优化。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：区间覆盖问题，可使用贪心算法。
- [P2880 [USACO07JAN] Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)：涉及区间最值查询，可使用线段树解决。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：最短路模板题，可练习 Dijkstra 或 Bellman - Ford 算法。

### 个人心得摘录与总结
- **HDZmessi**：代码直接提交会 TLE 一个点，开 O2 可解决，提醒注意代码复杂度和优化手段。
- **Wangjunhao2011**：未排序时复杂度高会 TLE，排序后可减少不必要枚举，虽复杂度未变但常数变小，说明合理排序可优化代码性能。
- **ICU152_lowa_IS8**：未添加 $start \geq T$ 跳出循环的判断会导致错误，强调处理边界条件和特殊情况的重要性。
- **_k_e_v_i_n_**：最短路建图时直接建图会出错，将 $E_i$ 加 1 可解决，提示建图时要考虑图的连通性和正确性。 

---
处理用时：53.91秒