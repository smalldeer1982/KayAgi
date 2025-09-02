# 题目信息

# MinOr Tree

## 题目描述

Recently, Vlad has been carried away by spanning trees, so his friends, without hesitation, gave him a connected weighted undirected graph of $ n $ vertices and $ m $ edges for his birthday.

Vlad defined the ority of a spanning tree as the [bitwise OR](https://tiny.cc/bitwise_or) of all its weights, and now he is interested in what is the minimum possible ority that can be achieved by choosing a certain spanning tree. A spanning tree is a connected subgraph of a given graph that does not contain cycles.

In other words, you want to keep $ n-1 $ edges so that the graph remains connected and the bitwise OR weights of the edges are as small as possible. You have to find the minimum bitwise OR itself.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/b7f5b7382b2cbd80980c576ea1b925aa7c500ed8.png)Graph from the first test case.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/43a768dfee0ade0f80ced3a4660bcaac868cc17b.png)Ority of this tree equals to 2 or 2 = 2 and it's minimal.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/c7716ab52b41700a181dd76536e0574654ad531d.png)Without excluding edge with weight $ 1 $ ority is 1 or 2 = 3.

## 样例 #1

### 输入

```
3

3 3
1 2 1
2 3 2
1 3 2

5 7
4 2 7
2 5 8
3 4 2
3 2 1
2 4 2
4 1 2
1 2 2

3 4
1 2 1
2 3 2
1 3 3
3 1 4```

### 输出

```
2
10
3```

# AI分析结果

### 题目内容（中文重写）
# 最小或树

## 题目描述
最近，弗拉德被生成树吸引住了，所以他的朋友们毫不犹豫地在他生日时送给他一个包含 $n$ 个顶点和 $m$ 条边的连通加权无向图。

弗拉德将生成树的“或值”定义为其所有边权的[按位或](https://tiny.cc/bitwise_or)，现在他想知道通过选择某棵生成树所能达到的最小“或值”是多少。生成树是给定图的一个连通子图，且不包含环。

换句话说，你需要保留 $n - 1$ 条边，使得图保持连通，并且边权的按位或尽可能小。你需要找出这个最小的按位或值。

## 说明/提示
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/b7f5b7382b2cbd80980c576ea1b925aa7c500ed8.png) 第一个测试用例的图。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/43a768dfee0ade0f80ced3a4660bcaac868cc17b.png) 这棵树的“或值”等于 $2$ 或 $2 = 2$，并且是最小的。  
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1624G/c7716ab52b41700a181dd76536e0574654ad531d.png) 如果不排除权值为 $1$ 的边，“或值”为 $1$ 或 $2 = 3$。

## 样例 #1
### 输入
```
3

3 3
1 2 1
2 3 2
1 3 2

5 7
4 2 7
2 5 8
3 4 2
3 2 1
2 4 2
4 1 2
1 2 2

3 4
1 2 1
2 3 2
1 3 3
3 1 4
```

### 输出
```
2
10
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法，从二进制的高位到低位进行枚举，判断每一位是否可以为 $0$。若去掉该位为 $1$ 的边后图仍然连通，则该位可以为 $0$，否则该位必须为 $1$。判断图的连通性时，大部分题解使用并查集，部分使用深度优先搜索（DFS）。

### 所选题解
- **AFewSuns（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了贪心的过程和判断连通性的方法，时间复杂度分析准确。
    - **核心代码**：
```cpp
ll find(ll x){
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
bool solve(ll x,ll k){
    for(ll i=1;i<=n;i++) fa[i]=i;
    for(ll i=1;i<=m;i++){
        if((e[i].w|x)>=(x+(1ll<<(k+1)))) continue;
        if((e[i].w>>k)&1) continue;
        ll fax=find(e[i].u),fay=find(e[i].v);
        if(fax==fay) continue;
        fa[fax]=fay;
    }
    bool ck=1;
    for(ll i=2;i<=n;i++) if(find(1)!=find(i)) ck=0;
    return ck;
}
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld %lld",&n,&m);
        for(ll i=1;i<=m;i++) scanf("%lld %lld %lld",&e[i].u,&e[i].v,&e[i].w);
        ll ans=0;
        for(ll i=31;i>=0;i--) if(!solve(ans,i)) ans|=1ll<<i;
        printf("%lld\n",ans);
    }
}
```
    - **核心实现思想**：`find` 函数用于查找节点的祖先，`solve` 函数用于判断在当前答案 `x` 的基础上，第 `k` 位是否可以为 $0$。在 `main` 函数中，从高位到低位枚举每一位，若该位不能为 $0$，则将该位加入答案。

- **Xdl_rp（4星）**
    - **关键亮点**：思路简洁明了，代码结构清晰，对并查集的使用和贪心过程的描述较为清晰。
    - **核心代码**：
```cpp
void init(int x) {
    for (int i = 1; i <= x; i++) f[i] = i;
}
int getfa(int x) {
    return f[x] == x ? f[x] : f[x] = getfa(f[x]);
}
void join(int x, int y, int &k) {
    x = getfa(x), y = getfa(y);
    if (x == y) return;
    else f[x] = y, k--;
}
signed main() {
    int T;
    scanf("%lld", &T);
    while (T--) {
        int n, m;
        scanf("%lld %lld", &n, &m);
        init(n);
        for (int i = 1; i <= m; i++) vis[i] = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%lld %lld %lld", &ed[i].fr, &ed[i].to, &ed[i].len);
        }
        int ans = 0;
        for (int i = 30; i >= 0; i--) {
            int cnt = n;
            for (int j = 1; j <= m; j++) {
                if (vis[j] == 1) continue;
                if (!(ed[j].len & (1 << i))) {
                    join(ed[j].fr, ed[j].to, cnt);
                }
            }
            if (cnt == 1) {
                for (int j = 1; j <= m; j++) {
                    if (ed[j].len & (1 << i)) {
                        vis[j] = 1;
                    }
                }
            }
            else {
                ans += (1 << i);
            }
            init(n);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```
    - **核心实现思想**：`init` 函数用于初始化并查集，`getfa` 函数用于查找节点的祖先，`join` 函数用于合并两个连通块。在 `main` 函数中，从高位到低位枚举每一位，若去掉该位为 $1$ 的边后图仍然连通，则标记这些边不再使用，否则将该位加入答案。

- **luan341502（4星）**
    - **关键亮点**：思路清晰，代码简洁，对贪心过程和并查集的使用描述准确。
    - **核心代码**：
```cpp
int find(int k){
    if(fa[k]==k) return k;
    return fa[k]=find(fa[k]);
}
void calc(int k){
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        if(e[i].p||((e[i].w>>k)&1)) continue;
        int fu=find(e[i].u),fv=find(e[i].v);
        if(fu^fv) fa[fu]=fv;
    }
    int x=find(1);
    for(int i=2;i<=n;i++)
        if(find(i)!=x){ans+=1<<k;return;}
    for(int i=1;i<=m;i++) if((e[i].w>>k)&1) e[i].p=true;
}
void solve(){
    cin>>n>>m;ans=0;
    for(int i=1;i<=m;i++){cin>>e[i].u>>e[i].v>>e[i].w;e[i].p=false;}
    for(int bit=31;bit>=0;bit--) calc(bit);
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int tt;cin>>tt;while(tt--)solve();
    return 0;
}
```
    - **核心实现思想**：`find` 函数用于查找节点的祖先，`calc` 函数用于判断第 `k` 位是否可以为 $0$。在 `solve` 函数中，从高位到低位枚举每一位，调用 `calc` 函数进行判断。

### 最优关键思路或技巧
- **贪心策略**：从二进制的高位到低位进行枚举，优先让高位为 $0$，因为高位为 $0$ 比低位为 $0$ 更优。
- **并查集**：用于判断图的连通性，时间复杂度较低。

### 拓展思路
同类型题目通常涉及位运算和贪心算法，例如在其他图论问题中，可能会要求计算按位与、按位异或等运算下的最优解。解题的关键在于根据运算的性质，从高位到低位进行贪心枚举，并使用合适的数据结构（如并查集、DFS 等）判断是否满足条件。

### 推荐题目
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)：涉及最小生成树的基本应用。
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)：结合了最小生成树和图的连通性判断。
- [P4047 [JSOI2010]部落划分](https://www.luogu.com.cn/problem/P4047)：需要运用贪心和图论的知识解决问题。

### 个人心得摘录与总结
部分题解作者提到这是一道比较妙的二进制题目，需要结合贪心和图论的知识。在解题过程中，关键在于理解按位贪心的思想，即从高位到低位依次判断每一位是否可以为 $0$。同时，使用并查集或 DFS 等方法判断图的连通性也是解题的重要步骤。

---
处理用时：70.27秒