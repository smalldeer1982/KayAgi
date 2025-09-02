# MST Company

## 题目描述

The MST (Meaningless State Team) company won another tender for an important state reform in Berland.

There are $ n $ cities in Berland, some pairs of the cities are connected by roads. Each road has its price. One can move along any road in any direction. The MST team should carry out the repair works on some set of roads such that one can get from any city to any other one moving only along the repaired roads. Moreover, this set should contain exactly $ k $ capital roads (that is, the roads that start or finish in the capital). The number of the capital is 1.

As the budget has already been approved, the MST Company will profit by finding the set with minimum lengths of roads.

## 样例 #1

### 输入

```
4 5 2
1 2 1
2 3 1
3 4 1
1 3 3
1 4 2
```

### 输出

```
3
1 5 2 ```

# 题解

## 作者：EndSaH (赞：29)

[可能更好的阅读体验](https://endsah.cf/blog/CF125E-MST-Company/#more)

# Solution

## hack

强烈谴责题目数据太水...

首先大部分的凸优化（或者说 wqs/带权二分）的做法都错了。这样只能正确的得到最小生成树的权值，但是要以此为基础构造方案会错。比如下面两组数据：

```
5 8 3
1 2 7
1 4 8
1 5 7
1 3 3
2 3 1
3 5 1
3 4 10
4 5 3
```

```
7 9 3
1 2 8
1 7 4
1 4 3
1 5 6
3 6 1
3 4 4
4 7 1
4 6 3
5 6 1
```

上面的最小生成树的权值是 19，下面的是 20。绝大多数程序会输出 20 和 -1...

[可以证明](https://www.cnblogs.com/CreeperLKF/p/9045491.html) 在这种策略下做出的最小生成树即使度数超过 $k$，也必然可以通过换边来得到度数恰好为 $k$ 的生成树，并且权值一样（凸包上多点共线）。然而直接根据排序顺序并限制度数再去构造方案，很可能得到不连通或错误的结果。

## 破圈

不妨考虑一个暴力一点的思路（$n$ 的范围较小）：

首先去掉 1 号点跑最小生成森林。

现在加入 1 号点。设此时除 1 号点外的联通块个数为 $x$，若 $k < x$，必然无解。

否则对于每个联通块加入能联通这个联通块的最小的边，这样就得到了一棵强制 $x$ 度生成树。

现在依然考虑经典的破圈算法：

对于一条不在生成树上的与 1 相连的边，若将其加到最小生成树中，其可以替换所产生的环上的一条最大的边，会使权值变小 $maxEdge - w$，其中 $maxEdge$ 是最大边边权，$w$ 是这条边的边权。

在所有 $maxEdge - w$ 找到其最大值并替换，在所替换的最大边不与 1 相连的前提下，就能得到一棵强制 $x + 1$ 度生成树。

将这个过程进行 $k - x$ 次，就能得到题目所要求的强制 $k$ 度生成树。

找到不与 1 相连的最大边由于数据范围原因可以暴力算。设 $maxE _i$ 表示在当前生成树上从 1 出发到 $i$ 节点的路径上**忽略与 1 相连的边**的最大边，每次 DFS 一遍 $O(n)$ 算就行。

$O(m \log m + nk)$

## 二分

**虽然我本人感觉是对的，并且经过了上万组数据的对拍，但是因为数据湿度，这个做法依然可能会假，请谨慎阅读**。

现在这个构造法应该只能做这个题（强制 $k$ 度），另一道也需要二分的题（恰好有 $k$ 条白色边的最小生成树）无法用这个方法构造。

之前已经说了，二分最后得到的最小生成树中 1 的度数会大于等于 $k$。

先通过二分把这个生成树建出来，并固定 1 号点为根。

考虑枚举生成树之外的所有边用来替换那些与 1 相连的边，直到 1 号点度数为 $k$。假设当前边为 $(u, v)$，权值为 $w$，以及 $u$ 归属于 1 号点的儿子中 $p$ 的子树，$v$ 归属于 1 号点的儿子中 $q$ 的子树。

如果 $p = q$ 自然无可替换。否则，如果 $p, q$ 中任意一个点与 1 相连的边权是 $w$，那么这条边 $(1, p/q)$ 就可以被 $(u, v)$ 替换。不妨设可替换的边是 $(1, p)$，那么 $p$ 子树内的点需要全部接入 $q$（也即下一次查询 $p$ 子树内的点，得到结果应当为 $q$）。这是简单并查集操作。

另外边权**必须**恰好是 $w$，才可以替换。实际上因为已经是最小生成树了，不可能替换之后边权更小，证明中也提到了一定是边权相同的边导致了 1 的度数超出了 $k$，所以必须严格等于。

复杂度的话，二分部分为 $O(m \log m \log SIZE)$，其中 $SIZE$ 为值域大小。如果将与 1 相连的边与其他边每次归并排序或者桶排可以优化变为 $O(m \log SIZE)$。换边构树部分为 $O(m \log n)$。

# Code

## gen

```python
from random import randint
from cyaron import *
import os
n = 200
m = randint(n - 1, min(1e5, n * (n - 1) / 2))
k = randint(1, n - 1)
outs = "%d %d %d\n" % (n, m, k)
graph = Graph.UDAG(n, m, weight_limit = 1e2, self_loop=False, repeated_edges=False)
outs += graph.to_str();
print(outs, file = open("tmp.in", "w"))
```

## spj

需搭配 std 和 gen 食用

另外由于 python 玄学原因，每次只能运行 340 次...

```cpp
#include <cstdlib>
#include <iostream>

using namespace std;
using ptr = FILE*;

const int maxN = 5e3 + 5;
const int maxM = 1e5 + 5;

int n, m, _ans, num, k;
int fa[maxN], size[maxN];

struct Edge
{ int u, v, w; }
edge[maxM];

int Find(int x)
{ return fa[x] == x ? x : fa[x] = Find(fa[x]); }

inline bool Merge(int u, int v)
{
    int fu = Find(u), fv = Find(v);
    if (fu == fv)
        return false;
    if (size[fu] > size[fv])
        swap(fu, fv);
    fa[fu] = fv, size[fv] += size[fu];
    return true;
}

inline void Err(const char* str)
{ fprintf(stderr, "%s\n", str); exit(0); }

int main()
{
    for (int cnt = 1; ; ++cnt)
    {
        system("python3 gen.py && ./tmp && ./std");
        ptr in = fopen("tmp.in", "r"), out = fopen("tmp.out", "r"), ans = fopen("tmp.ans", "r");
        int tmp;
        fscanf(in, "%d %d %d", &n, &m, &k);
        for (int i = 1; i <= n; ++i)
            fa[i] = i, size[i] = 1;
        for (int i = 1; i <= m; ++i)
            fscanf(in, "%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
        if (fscanf(out, "%d", &_ans) != 1)
            Err("No ans.");
        if (fscanf(ans, "%d", &num) != 1)
            Err("Invalid output.");
        if (num == -1 and _ans != -1)
            Err("No solution.");
        if (num != -1 and _ans == -1)
            Err("Not.");
        if (num == -1 and _ans == -1)
        {
            printf("AC %d times!\n", cnt);
            continue;
        }
        if (num != n - 1)
            Err("edges' number wrong!");
        int curans = 0, c = 0;
        for (int i = 1; i <= num; ++i)
        {
            if (fscanf(ans, "%d", &tmp) != 1)
                Err("Invalid output.");
            if (!Merge(edge[tmp].u, edge[tmp].v))
                Err("Not tree.");
            curans += edge[tmp].w;
            if (edge[tmp].u == 1 or edge[tmp].v == 1)
                ++c;
        }
        if (curans != _ans)
            Err("Wrong answer!");
        if (c != k)
            Err("1's degree isn't k!");
        printf("AC %d times!\n", cnt);
    }
    return 0;
}
```

## std

### 破圈

```cpp
#include<bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int,int> pii;

template <typename T> inline T read()
{
    T sum=0, fl=1; char ch=getchar();
    for(; !isdigit(ch); ch=getchar()) if(ch=='-') fl=-1;
    for(; isdigit(ch); ch=getchar()) sum=(sum<<3)+(sum<<1)+ch-'0';
    return sum*fl;
}

const int maxn=5000+5;
const int maxm=1e5+5;

int n, m, k, c;
LL mx[maxn]; bool del[maxm<<1], no[maxm];
int fa[maxn], id[maxm<<1]; vector<int>vec, E;
int he[maxn], ne[maxm<<1], to[maxm<<1], w[maxm<<1];
struct EDGE { int u, v, w, id; } e[maxm];

bool operator<(const EDGE&a, const EDGE&b) { return a.w<b.w; }

void add_edge(int u, int v, int val)
{
    ne[++c]=he[u]; he[u]=c; to[c]=v; w[c]=val;
    ne[++c]=he[v]; he[v]=c; to[c]=u; w[c]=val;
}

int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }
void forest()
{
    for(int i=1; i<=n; ++i) fa[i]=i;
    sort(e+1, e+m+1); 
    for(int i=1; i<=m; ++i)
    {
        int u=find(e[i].u), v=find(e[i].v);
        if(u==v || u==1 || v==1) continue;
        fa[u]=v; E.pb(e[i].id);
        add_edge(e[i].u, e[i].v, e[i].w); id[c]=id[c-1]=e[i].id;
    }
}

void get_max(int p, int f)
{
    for(int i=he[p]; i; i=ne[i])
    {
        if(to[i]==f || del[i] || to[i]==1) continue;
        if(w[i]>=w[mx[p]]) mx[to[i]]=i;
        else mx[to[i]]=mx[p];
        get_max(to[i], p);
    }
}

void Solve()
{
    n=read<int>(), m=read<int>(), k=read<int>(); c=1;
    for(int i=1; i<=m; ++i) e[i]=(EDGE){read<int>(), read<int>(), read<int>(), i};
    forest(); 

    for(int i=1; i<=m; ++i) 
    {
        if(e[i].u!=1 && e[i].v!=1) continue;
        int u=find(e[i].u), v=find(e[i].v);
        if(u == v) vec.pb(i);
        else fa[u]=v, add_edge(e[i].u, e[i].v, e[i].w), E.pb(e[i].id), --k; 
    }

    for(int i=2; i<=n; ++i) if(find(i)!=find(i-1)) return (void) printf("-1");
    if(k<0) return (void) printf("-1");

    for(int i=1; i<=k; ++i)
    {
        if(!vec.size()) return (void) printf("-1"); /**/
        memset(mx, 0, sizeof(mx));
        for(int j=he[1]; j; j=ne[j]) get_max(to[j], 1);
        int now=-1, ans=2147483647;
        for(int j=vec.size()-1; j>=0; --j) 
        {
            int p=vec[j], var=max(e[p].u, e[p].v);
            if(e[p].w-w[mx[var]]<ans) ans=e[p].w-w[mx[var]], now=j;
        }
        int p=vec[now], var=e[p].u==1?e[p].v:e[p].u;
        add_edge(e[p].v, e[p].u, e[p].w); E.pb(e[p].id); 
        no[id[mx[var]]]=1; del[mx[var]]=del[mx[var]^1]=1;
        vec.erase(vec.begin()+now);
    }

    printf("%d\n", n-1);
    for(int i=E.size()-1; i>=0; --i) if(!no[E[i]]) printf("%d ", E[i]);
}

int main()
{

    //  freopen("125e.in","r",stdin);
    //  freopen("125e.out","w",stdout);

    Solve();

    return 0;
}
```

### 二分

```cpp
#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int maxN = 5e3 + 5;
const int maxM = 1e5 + 5;

int n, m, k, maxw, ans;
int fa[maxN], size[maxN], val[maxN], id[maxN];
set<int> out;
vector<struct Edge> G[maxN];
bitset<maxM> vis;

struct Edge
{
    int u, v, w, id;

    Edge() { }

    Edge(int _u, int _v, int _w, int _id) : u(_u), v(_v), w(_w), id(_id) { }
} edge[maxM];

bool operator<(const Edge& x, const Edge& y)
{ return x.w == y.w ? x.u < y.u : x.w < y.w; }

int Find(int x)
{ return fa[x] == x ? x : fa[x] = Find(fa[x]); }

inline bool Merge(int u, int v)
{
    int fu = Find(u), fv = Find(v);
    if (fu == fv)
        return false;
    if (size[fu] > size[fv])
        swap(fu, fv);
    fa[fu] = fv, size[fv] += size[fu];
    return true;
}

void Init()
{
    for (int i = 1; i <= n; ++i)
        fa[i] = i, size[i] = 1;
}

bool Check()
{
    Init();
    int deg = 0;
    for (int i = 1; i <= m; ++i)
        if (edge[i].u != 1)
            Merge(edge[i].u, edge[i].v);
        else
            ++deg;
    if (deg < k)
        return false;
    int cnt = 0;
    for (int i = 2; i <= n; ++i)
        if (Find(i) == i)
            ++cnt;
    if (cnt > k)
        return false;
    for (int i = 1; i <= m; ++i)
        if (edge[i].u == 1)
            Merge(edge[i].u, edge[i].v);
    cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (Find(i) == i)
            ++cnt;
    return cnt == 1;
}

void DFS(int u, int father)
{
    fa[u] = fa[father];
    for (const auto& v : G[u]) if (v.u != father)
        DFS(v.u, u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("tmp.in", "r", stdin);
    freopen("tmp.ans", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    if (n == 1)
    { cout << 0 << endl; return 0; }
    for (int i = 1; i <= m; ++i)
    {
        Edge& o = edge[i];
        cin >> o.u >> o.v >> o.w;
        o.id = i;
        if (o.u > o.v)
            swap(o.u, o.v);
        maxw = max(maxw, o.w);
    }
    if (!Check())
    {
        cout << "-1" << endl;
        return 0;
    }
    int l = -maxw, r = maxw, p, ecnt, cnt;
    while (l <= r)
    {
        p = (l + r) >> 1;
        ecnt = cnt = 0;
        Init();
        for (int i = 1; i <= m; ++i)
            if (edge[i].u == 1)
                edge[i].w += p;
        sort(edge + 1, edge + m + 1);
        for (int i = 1; i <= m; ++i)
            if (Merge(edge[i].u, edge[i].v))
            {
                ++ecnt;
                if (edge[i].u == 1)
                    ++cnt;
                if (ecnt == n - 1)
                    break;
            }
        for (int i = 1; i <= m; ++i)
            if (edge[i].u == 1)
                edge[i].w -= p;
        if (cnt >= k)
            ans = p, l = p + 1;
        else
            r = p - 1;
    }
    Init(), cnt = 0;
    for (int i = 1; i <= m; ++i)
        if (edge[i].u == 1)
            edge[i].w += ans;
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; ++i)
        if (Merge(edge[i].u, edge[i].v))
        {
            vis.set(i);
            if (edge[i].u == 1)
                ++cnt;
            out.insert(edge[i].id);
            G[edge[i].u].emplace_back(edge[i].v, 0, edge[i].w, edge[i].id);
            G[edge[i].v].emplace_back(edge[i].u, 0, edge[i].w, edge[i].id);
        }
    for (const auto& v : G[1])
    {
        val[v.u] = v.w, id[v.u] = v.id;
        fa[1] = v.u, DFS(v.u, 1);
    }
    for (int i = 1; i <= m and cnt > k; ++i) if (edge[i].u != 1 and !vis[i])
    {
        int fu = Find(edge[i].u), fv = Find(edge[i].v);
        if (fu == fv)
            continue;
        if (val[fu] == edge[i].w)
        {
            fa[fu] = fv, --cnt;
            out.insert(edge[i].id);
            out.erase(id[fu]);
            continue;
        }
        if (val[fv] == edge[i].w)
        {
            fa[fv] = fu, --cnt;
            out.insert(edge[i].id);
            out.erase(id[fv]);
            continue;
        }
    }
    if (cnt == k)
    {
        cout << n - 1 << endl;
        for (int i : out)
            cout << i << ' ';
        cout << endl;
    }
    else
        cout << "-1" << endl;
    return 0;
}
```

---

## 作者：jiqimao (赞：23)

关于基础的WQS二分我们在此不再赘述,关于蒟蒻对WQS的理解可以看蒟蒻的[博客](https://prutekoi.github.io/post/xue-xi-bi-ji-wqs-er-fen-tu-you-hua/)。

EndSaH大佬已经hack了显然不对的一些WQS二分,并给出了自己的一种构造方案,不过是利用了这题限制1的度数的一些性质。

我们现在可以给出这题的超集[P2619 [国家集训队2]Tree I ](https://www.luogu.com.cn/problem/P2619)的方案构造方式。

> 给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有need条白色边的生成树。

用WQS二分可以二分出一个斜率 $k$,已知need这个点也在这条直线上。于是把所有白边都加上权值 $k$。（注意WQS二分的过程已经结束了,下面是构造方案）

我们可以用最多白边和最少白边策略分别跑一遍克鲁斯卡尔。

首先通过拟阵的一些性质可以得出最小生成树中白边数量的可能情况是连续的。有了最大值和最小值之后我们就可以判是否无解了（区间不包含 $need$ 即无解）。那么接下来就是如何构造方案。

我们知道最小生成树边权相同的边之间才会互相替换,且同一边权的边用的数量是固定的。于是我们可以按照边权从小到大分批次地考虑这些边。不同批次之间的边相当于是独立的。

在上面求最少白边时我们可以顺带求出在每一批次中一定需要选的白边有哪些,那么我们构造时就先把这些边连上(不然构不成最小生成树)。

当前批次中剩下的边可以全都选黑边(但是有可能之后选最多数量的白边也凑不够 $need$ 条白边了)。如何抉择剩下的边怎么选呢?

我们之前求最多白边时可以对于每个边权 $x$,求出在满足最小生成树条件下边权大于 $x$ 的边最多选多少白边,设为 $R[x]$。

那么在构造时对于 $x$ 边权的不必要的白边只要加到 $now+R[x]==need$ 即可,然后这批次就可以只加黑边。

这样构造到所有批次都结束之后即可得到合法的解。

应该对于一般的WQS二分也可以套用这样的思路构造方案。

我的代码可以过掉所有的hack数据呦,请放心食用。

代码很丑...
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int n,m,need,n1,n2,x[N],y[N],z[N],c1[N],c2[N],f[N],s[N],R[N],ll,rr;bool flag;
bool cmp(int x,int y){return z[x]<z[y];}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
vector<int>v[N],Ans;
bool merge(int id){
    int fx=find(x[id]),fy=find(y[id]);
    if(fx==fy)return 0;
    if(flag)Ans.push_back(id);
    if(s[fx]>s[fy])swap(fx,fy);
    f[fx]=fy;s[fy]+=s[fx];return 1;
}
int main(){
    scanf("%d%d%d",&n,&m,&need);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x[i],&y[i],&z[i]);
        (x[i]==1||y[i]==1?c1[++n1]:c2[++n2])=i;
    }
    sort(c1+1,c1+n1+1,cmp);sort(c2+1,c2+n2+1,cmp);
    int l=-5e8,r=5e8,ans=-1e9;
    while(l<=r){
        int mid=(l+r)>>1,i=1,j=1,now=0;
        for(int k=1;k<=n;k++)f[k]=k,s[k]=1;
        while(i<=n1||j<=n2)
            if(i>n1||(j<=n2&&z[c2[j]]<z[c1[i]]+mid))merge(c2[j++]);
            else now+=merge(c1[i++]);
        if(now>=need)ans=mid,l=mid+1;
        else r=mid-1;
    }
    if(ans==-1e9)puts("-1");
    for(int i=1;i<=n1;i++)z[c1[i]]+=ans;
    int i=1,j=1,now=0;
    for(int k=1;k<=n;k++)f[k]=k,s[k]=1;
    for(int k=-1e9;i<=n1||j<=n2;){
        if(i>n1||(j<=n2&&z[c2[j]]<=z[c1[i]])){
            if(z[c2[j]]!=k)k=z[c2[j]];
            merge(c2[j++]);
        }
        else{
            if(z[c1[i]]!=k)k=z[c1[i]];
            if(merge(c1[i])){
                if(k>=1&&k<=1e5)v[k].push_back(c1[i]);
                now++;
            }
            i++;
        }
    }
    ll=now;now=0;i=j=1;if(ll>need)puts("-1"),exit(0);
    for(int k=1;k<=n;k++)f[k]=k,s[k]=1;
    for(int k=-1e9;i<=n1||j<=n2;){
        if(i>n1||(j<=n2&&z[c2[j]]<z[c1[i]])){
            if(z[c2[j]]!=k){
                if(k>=1&&k<=1e5)R[k]=now;
                k=z[c2[j]];if(k>=1&&k<=1e5)R[k]=1e9;
            }
            merge(c2[j++]);
        }
        else{
            if(z[c1[i]]!=k){
                if(k>=1&&k<=1e5)R[k]=now;
                k=z[c1[i]];if(k>=1&&k<=1e5)R[k]=1e9;
            }
            now+=merge(c1[i++]);
        }
    }
    rr=now;now=0;i=j=1;flag=1;
    for(int k=1;k<=1e5;k++)R[k]=max(0,rr-R[k]);
    for(int k=1;k<=n;k++)f[k]=k,s[k]=1;
    for(int k=-1e9;i<=n1&&j<=n2;){
        k=min(z[c1[i]],z[c2[j]]);
        if(k<1||k>1e5){
            while(i<=n1&&z[c1[i]]==k)
                now+=merge(c1[i++]);
        }
        else{
            for(int l=0;l<v[k].size();l++)now+=merge(v[k][l]);
            while(now+R[k]<need)now+=merge(c1[i++]);
            while(j<=n2&&z[c2[j]]==k)merge(c2[j++]);
            while(i<=n1&&z[c1[i]]==k)now+=merge(c1[i++]);
        }
    }
    while(i<=n1)now+=merge(c1[i++]);
    while(j<=n2)merge(c2[j++]);
    printf("%d\n",n-1);
    for(int i=0;i<Ans.size();i++)printf("%d ",Ans[i]);
    return 0;
}
```

---

## 作者：Leap_Frog (赞：10)

### P.S.
[安利自己的wqs二分学习笔记](https://www.luogu.com.cn/blog/daniu/wqs-er-fen)  
本着复习 wqs二分 的目的，我点开了这道题，结果呢。。。。。。  
![](https://cdn.luogu.com.cn/upload/image_hosting/5uqt0gom.png)  
为了纪念来之不易的 AC，我打算写一篇题解。  
不过看题解区吵地很厉害，我也不敢肯定这篇题解一定是对的，如果伪了还请原谅。  
### Description.
[此题](https://www.luogu.com.cn/problem/P5633) 输出方案。  

### Solution.
wqs 二分模板题。  
我们把和 1 连边的点当作特殊物品。  
然后按照套路二分斜率，每次判定对于和 1 相连的边跑一遍最短路。  
由上文，我们每次直接对和 1 相邻边的权值加上当前二分的 `mid`。  
判断有几条边和 1 相连，直接根据这个数量继续二分就好了。  
小 tips：每次二分需要求一个 `Kruskra`，但是我们并不需要对于每次二分重新排序边。  
我们只需要刚开始排序一遍，对于每次二分直接归并一下就好了。  
于是，成功把复杂度从 $O(n\log n\log V)$ 降至 $O(n(\log n+\log V))$  
UpDate: 笔者偷懒，懒得写归并，直接sort，复杂度两只 $\log$。  
然后以 904ms 的~~优异~~成绩通过了此题。  

主要还需要介绍一些笔者出错的地方。  
1. 注意二分精度，建议二分到 double
2. 开 long long
3. 数据范围，边数量和点数量不同 ~~不过没人和笔者这样sb吧~~
4. 二分也需要二分到 +/-，值域需要大一点

然后就做完了，具体可以看代码。  
~~有少量注释。~~

### Coding.
```cpp
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>59;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
struct node{int x,y;double w;int id;bool operator<(node b) {return w<b.w;}}e[100005],e1[100005],e2[100005];
int n,m,K,fa[10005],t1,t2;
inline int getf(int x) {return fa[x]==x?x:fa[x]=getf(fa[x]);}
inline char mrg(int x,int y) {x=getf(x),y=getf(y);if(x^y) return fa[x]=y,1;else return 0;}
//↑并查集
inline char check(ll w)
{
	for(int i=1;i<=t1;i++) e[i]=e1[i],e[i].w+=w/100000.0;
	int cnt=0;for(int i=1;i<=t2;i++) e[i+t1]=e2[i];
	sort(e+1,e+m+1);for(int i=1;i<=n;i++) fa[i]=i;//暴力排序
	for(int i=1;i<=m;i++) if(mrg(e[i].x,e[i].y)) cnt+=(e[i].x==1||e[i].y==1);
	return cnt<=K;//计算有多少个点与 1 相连
}//↑二分check函数
int main()
{
	read(n),read(m),read(K),assert(0);ll le=-1e16-7,ri=1e16+7,rs=1e16+7;//值域，尽量大 （assert(0)不解释
	for(int i=1,x,y,w;i<=m;i++) {read(x),read(y),read(w);if(x==1||y==1) e1[++t1]=(node){x,y,w,i};else e2[++t2]=(node){x,y,w,i};}
	//↑把边分类   ↓wqs二分主体（一行
	while(le<=ri) {ll md=(le+ri)/2;if(check(md)) rs=md,ri=md-1;else le=md+1;}
	if(!check(rs)) return puts("-1"),0;else printf("%d\n",n-1);
	for(int i=1;i<=t1;i++) e[i]=e1[i],e[i].w+=rs/100000.0;
	for(int i=1;i<=t2;i++) e[i+t1]=e2[i];
	sort(e+1,e+m+1);for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) if(mrg(e[i].x,e[i].y)) printf("%d ",e[i].id);
	return putchar('\n'),0;//↑输出方案，check 直接赋值一遍（
}
```

---

## 作者：JiaY19 (赞：6)

[**更好的阅读体验。**](https://www.cnblogs.com/mfeitveer/p/16852540.html)

代码写的可能比较繁琐，请见谅。

### 思路

首先考虑 $\text{wqs}$ 二分。

对所有连向 $s$ 的边进行定量偏移。

即所有连向 $s$ 的边的边权 $q$ 加上二分的定量 $\Delta$。

就可以将这一个问题变成一个可行性问题。

可能比较困难的一点就是当 $\Delta$ 一定时，可能拥有不同的 $k$ 的方案。

本篇主要讲述如何构造一个正确的方案。

首先判断一个无解的情况。

1. 从 $s$ 的出边不足 $k$。
2. 原图不联通。
3. 使原图联通 $s$ 必须连的出边超过 $k$。

除去上面三种情况，所有的情况必然会有一个解。

考虑对于一个偏移量如何构造出这样的一个解。

首先可以构造出一组 $s$ 出边最少的解。

考虑在此基础上将其增加至 $k$ 条出边。

对于相同权值的边，我们先将原方案中所连的出边进行连接。

然后如果不足 $k$ 条出边，再去考虑相同权值下的其他出边。

最后再去考虑相同权值下的其他边。

可以发现，原方案中所连的出边一定还会在新方案中被连。

这是由于虽然我们增加了一些边，但对于原方案中所连的出边所更改的联通性是不会进行改变的（不然就会出现在原方案中）。

容易发现这样也一定不会比原方案更劣（原理大致与朴素的 $\text{kruskal}$ 差不多），并且一定有解。

这样就有了一个大致的算法流程。

具体可以看代码。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1000010;

int n, m, k, s, kl, top, fa[N], vis[N], ans[N];

class Graph
{
    public:
        int cnt;
        struct edge { int to, nxt, val, id; }e[N];
        inline edge &operator[](int tmp) { return e[tmp]; }
        inline void init(int x) { for (int i = 1;i <= cnt;i++) e[i].val += x; }
        inline void add(int x , int y , int z , int i) { e[++cnt] = {x, y, z, i}; }
        inline void mySort() { sort(e + 1, e + cnt + 1, [](edge a, edge b) { return a.val < b.val; }); }
} graBlack, graWhite;

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

inline bool check(int x , int y) { return (x == s || y == s); }
inline int gf(int x) { return (fa[x] == x ? fa[x] : fa[x] = gf(fa[x])); }

inline bool merge(int x , int y) 
{ 
    int fx = gf(x), fy = gf(y); 
    if(fx == fy) return 0;
    fa[fx] = fy; return 1;
}

inline int kruskal()
{
    int num = 0; top = 0;
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1, l = 1, r = 1; i <= m; i++)
        if (l <= graBlack.cnt && graBlack[l].val < graWhite[r].val)
            merge(graBlack[l].to, graBlack[l].nxt) , l++;
        else num += merge(graWhite[r].to, graWhite[r].nxt), r++;
    return num;
}

inline void checkSol()
{
    int cnt = 0 , sum = 0;
    for (int i = 1; i <= graBlack.cnt;i++)
        cnt += merge(graBlack[i].to, graBlack[i].nxt);
    for (int i = 1; i <= graWhite.cnt; i++)
        if(merge(graWhite[i].to, graWhite[i].nxt)) cnt++, sum++;
    if (cnt != n - 1 || sum > k || graWhite.cnt < k)
        puts("-1"), exit(0);
}

inline void makeSol(int mid)
{
    graWhite.init(mid), top = 0;
    iota(fa + 1, fa + n + 1, 1);
    int sum = 0, l = 1, r = 1, i, j;
    for (i = 1; i <= m; i++)
        if (l <= graBlack.cnt && graBlack[l].val <= graWhite[r].val)
            merge(graBlack[l].to, graBlack[l].nxt), l++;
        else 
        {
            if (merge(graWhite[r].to, graWhite[r].nxt))
                vis[r] = 1, k--;
            r++;
        };
    l--, r--, top = 0;
    iota(fa + 1, fa + n + 1, 1);
    for (i = 1, j = 1; i <= graBlack.cnt;i++)
    {
        while(j <= r && graWhite[j].val <= graBlack[i].val)
        {
            int ls = j, rs = j;
            int x = graWhite[j].val;
            while(rs < r && graWhite[rs + 1].val == x)
                rs++;
            for (int j = ls; j <= rs;j++)
                if (vis[j] && merge(graWhite[j].to, graWhite[j].nxt))
                    sum += graWhite[j].val, ans[++top] = graWhite[j].id;
            for (int j = ls; j <= rs && k; j++)
                if(merge(graWhite[j].to, graWhite[j].nxt))
                    sum += graWhite[j].val, k--, ans[++top] = graWhite[j].id;
            j = rs + 1;
        }
        if(merge(graBlack[i].to, graBlack[i].nxt))
            sum += graBlack[i].val, ans[++top] = graBlack[i].id;
    }
    while (j <= r)
    {
        int ls = j, rs = j;
        int x = graWhite[j].val;
        while (rs < r && graWhite[rs + 1].val == x)
            rs++;
        for (int j = ls; j <= rs; j++)
            if (vis[j] && merge(graWhite[j].to, graWhite[j].nxt))
                sum += graWhite[j].val, ans[++top] = graWhite[j].id;
        for (int j = ls; j <= rs && k; j++)
            if (merge(graWhite[j].to, graWhite[j].nxt))
                sum += graWhite[j].val, k--, ans[++top] = graWhite[j].id;
        j = rs + 1;
    }
    cout << n - 1 << endl;
    for (i = 1; i <= top;i++)
        cout << ans[i] << " ";
    cout << endl;
}

inline void wqsDichotomous()
{
    int l = -1e9, r = 1e9;
    graBlack.mySort(), graWhite.mySort();
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        graWhite.init(mid);
        int x = kruskal();
        graWhite.init(-mid);
        if (x > k) l = mid + 1;
        if (x < k) r = mid - 1;
        if (x == k) break;
    }
    makeSol((l + r) >> 1);
}

signed main()
{
    n = read(), m = read(), s = 1, kl = k = read();
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= m; i++)
    {
        int x = read(), y = read(), z = read();
        if (check(x, y)) graWhite.add(x, y, z, i);
        else graBlack.add(x, y, z, i);
    }
    checkSol(), wqsDichotomous();
    return 0;
}
```


---

## 作者：Piwry (赞：6)

这里主要讲下 wqs 二分没法正好二分出需要的最小生成树方案时该如何构造方案

## 解析

题意以及前面基本的 wqs 二分部分就直接略过了

考虑为什么我们无法直接二分出需要的最小生成树方案：此时函数的最小值实际上不再是一个点，而是**一段区间**，设其为 $[l, r]$

这实际上就代表，在**当前**的图上（所有与 $1$ 相连的边的边权加上该次二分的 $C$ 值后的图），选择 $k, l\leq k\leq r$ 条与 $1$ 相连的边的最小生成树方案**都是存在的**

接着我们直接给出（也可以认为由生成树的性质而启发得到的...）构造的方法：

（下面为了方便，均将 “与 $1$ 结点相连的边” 称为 “特殊边”）

设要求构造的方案需要 $k$ 条特殊边，在 “当前图” 上的最小生成树的每种边权 $val$ 至少要用 $c_{val}$ 条特殊边（若要得到 $c_{val}$，只需在排序上动手脚：使相同边权的其它边排在特殊边前面，这样就**尽量避免**了选特殊边）

在做 Kruskal 时（尚不清楚是否有基于 prim 的构造方法...），我们记录已经选择的特殊边的数量 $\text{cnt}$（补充：在第二种方案中的定义可能有些不同...），并以相同边权的边为一组

一种方案是：在做每一组时，先尝试使用特殊边，如果可行，且 $k-\sum\limits_{val} c_{val}+c_{now}-(\text{cnt}-\sum\limits_{val\in Pre} c_{val})>0$（其中 $Pre$ 指已经处理过（不含当前）的组的边权集合，$c_{now}$ 指当前正处理的颜色的 $c$），就选择这条边。处理完特殊边后再尝试使用非特殊边

另一种方案是：先找出一种选择特殊边最少的最小生成树方案 $S$。在做每一组时，我们先将 $S$ 中存在的特殊边先连上（注意不要连非特殊边），并且**不计入** $\text{cnt}$，之后依然先尝试使用特殊边；如果可行，且 $k-\text{cnt}>0$，那么就选择这条边。处理完特殊边后再尝试使用非特殊边。这种构造方式应该会更好理解

最后考虑证明这种构造方式

事实上，我们可以发现这种构造方式和原来的 Kruskal 算法是没有本质区别的...；且目标的生成树方案已经保证存在，因此该构造方式一定有解

## CODE

代码里可能显式或隐式地将 与 $1$ 结点相连的边 称为 “白边”，将 除此以外的其它边 称为 “黑边”

另外代码里用的是后一种构造方式

仅供参考，~~有些地方的实现可能很烂~~

```cpp
#include <cstdio>
#include <algorithm>
using std::sort;

const int MAXN =5e3+20, MAXM =1e5+20;

/*------------------------------Disjoint Set------------------------------*/

int fa[MAXN], rank[MAXN];

int get_root(const int &x){
	if(fa[x] == x)
		return x;
	else
		return fa[x] =get_root(fa[x]);
}

inline void merge(int x, int y){
	x =get_root(x), y =get_root(y);
	if(rank[x] == rank[y])
		++rank[x];
	else if(rank[x] < rank[y])
		rank[y] ^=rank[x] ^=rank[y] ^=rank[x];
	fa[y] =x;
}

void clear_disjointSet(const int &n){
	for(int i =1; i <= n; ++i)
		fa[i] =i, rank[i] =0;
}

/*------------------------------Kruskal------------------------------*/

struct edge{
	int u, v, w, id;
	bool col;
}e_b[MAXM], e_w[MAXM], e_qaq[MAXM];
int totb, totw, tot;

bool cmp(const edge &A, const edge &B){
	return A.w < B.w;
}

int edge_chosen_id[MAXN];

#define e e_qaq

int debug_val;/*最小生成树权*/
int calc(const int &n, const int &C){
	debug_val =0;
	
	tot =0;
	for(int i =0, j =0; i < totb || j < totw;){
		if(i < totb && j < totw){
			if(e_b[i].w <= e_w[j].w+C)/*优先黑边 -> 尽可能少选白边 ( -> 最小值区间左端点 )*/
				e[tot++] =e_b[i++];
			else
				e[tot] =e_w[j++], e[tot++].w +=C;
		}
		else if(i < totb)
			e[tot++] =e_b[i++];
		else
			e[tot] =e_w[j++], e[tot++].w +=C;
	}
	
	clear_disjointSet(n);
	int cnt =0, ret =0;
	for(int i =0; cnt < n-1 && i < tot; ++i)
		if(get_root(e[i].u) != get_root(e[i].v)){
			debug_val +=e[i].w;
			if(e[i].col == 0)
				++ret;
			merge(e[i].u, e[i].v);
			edge_chosen_id[cnt] =e[i].id;
			++cnt;
		}
	
	return ret;
}

#undef e

/*------------------------------Wrok------------------------------*/

bool check_illegal(const int &n, const int &k){/*构造生成树时尽可能地不选白边*/
	clear_disjointSet(n);
	int cnt =0, cnt_w =0;
	for(int i =0; i < totb && cnt < n-1; ++i)
		if(get_root(e_b[i].u) != get_root(e_b[i].v)){
			merge(e_b[i].u, e_b[i].v);
			++cnt;
		}
	for(int i =0; i < totw && cnt < n-1; ++i)
		if(get_root(e_w[i].u) != get_root(e_w[i].v)){
			merge(e_w[i].u, e_w[i].v);
			++cnt_w;
			++cnt;
		}
	return (k < cnt_w || cnt != n-1);
}

edge e_backup[MAXM];
int tmp_backup, C_backup, debug_val_backup;

int cnt_l[MAXM], cnt_r[MAXM], tot_cnt;
bool e_chosen[MAXM];/*标记每种不同的边权中，选最少白边方案 ( 可能是多种方案中的一种 ) 中的白边*/

int e_ans[MAXN], tote_ans;

#define e e_backup

/*->>这里和 wqs 二分基本无关*/
/*解应当一定存在*/
void find_a_solution(const int &n, const int &m, const int &k){
	for(int i =0; i < m; ++i){
		if(i == 0){
			cnt_l[0] =0;
			++tot_cnt;
		}
		else if(e[i].w != e[i-1].w){
			cnt_r[tot_cnt-1] =i-1;
			cnt_l[tot_cnt] =i;
			++tot_cnt;
		}
		if(i == m-1)
			cnt_r[tot_cnt-1] =m-1;
	}
	
	/*找出一种最小生成树方案，使得白边最少*/
	clear_disjointSet(n);
	int cnt =0;
	for(int i =0; cnt < n-1; ++i){
		if(get_root(e[i].u) != get_root(e[i].v)){
			if(e[i].col == 0)
				e_chosen[i] =1;
			merge(e[i].u, e[i].v);
			++cnt;
		}
		++i;
	}
	
	clear_disjointSet(n);
	cnt =0;
	int delta_w =k-tmp_backup;/*还差多少白边*/
	for(int chunk =0; chunk < tot_cnt && cnt < n-1; ++chunk){/*注意只有同边权的边之间会 " 替换 " ( 影响 )*/
		for(int i =cnt_l[chunk]; i <= cnt_r[chunk]; ++i)/*先选 " 白边最少的方案 " 中的白边*/
			if(e_chosen[i]){
				merge(e[i].u, e[i].v);
				e_ans[tote_ans++] =e[i].id;
				++cnt;
			}
		if(delta_w > 0)/*还需要多选一些白边*/
			for(int i =cnt_l[chunk]; delta_w > 0 && i <= cnt_r[chunk]; ++i)
				if(!e_chosen[i] && e[i].col == 0){
					if(get_root(e[i].u) != get_root(e[i].v)){
						merge(e[i].u, e[i].v);
						e_ans[tote_ans++] =e[i].id;
						--delta_w;
						++cnt;
					}
				}
		for(int i =cnt_l[chunk]; i <= cnt_r[chunk]; ++i)/*最后选黑边*/
			if(e[i].col == 1){
				if(get_root(e[i].u) != get_root(e[i].v)){
					merge(e[i].u, e[i].v);
					e_ans[tote_ans++] =e[i].id;
					++cnt;
				}
			}
	}
}

#undef e

/*------------------------------Main------------------------------*/

int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return x;
}

int main(){
	int n =read(), m =read(), k =read();
	for(int i =0; i < m; ++i){
		int s =read(), t =read(), c =read();
		if(s == 1 || t == 1){
			e_w[totw].u =s;
			e_w[totw].v =t;
			e_w[totw].w =c;
			e_w[totw].col =0;
			e_w[totw].id =i+1;
			++totw;
		}
		else{
			e_b[totb].u =s;
			e_b[totb].v =t;
			e_b[totb].w =c;
			e_b[totb].col =1;
			e_b[totb].id =i+1;
			++totb;
		}
	}
	sort(e_b, e_b+totb, cmp);
	sort(e_w, e_w+totw, cmp);
	
	/*检查 k 是否合法 ( 函数取值在 k 是否不存在 )*/
	if(k > n-1 || k > totw){/*上界检查 - 边不足*/
		puts("-1");
		return 0;
	}
	else if(check_illegal(n, k)){/*下界检查 - 最少可选的白边过多；以及顺便检查是否联通*/
		puts("-1");
		return 0;
	}
	
	int l =-5e8, r =5e8;
	while(l <= r){/*wqs*/
		int mid =(l+r)>>1;
		int tmp =calc(n, mid);
		if(tmp < k){
			debug_val_backup =debug_val;
			tmp_backup =tmp;
			C_backup =mid;
			for(int i =0; i < tot; ++i)
				e_backup[i] =e_qaq[i];
		}
		if(tmp < k)
			r =mid-1;
		else if(tmp > k)
			l =mid+1;
		else
			break;
	}
	
	if(l <= r){/*直接找到了答案*/
		printf("%d\n", n-1);
		for(int i =0; i < n-1; ++i)
			printf("%d ", edge_chosen_id[i]);
		return 0;
	}
	else{/*需要构造方案*/
		find_a_solution(n, m, k);
	//	printf("%d\n", debug_val_backup-C_backup*k);/*最小生成树权*/
		printf("%d\n", n-1);
		for(int j =0; j < n-1; ++j)
			printf("%d ", e_ans[j]);
	}
}
```

## 一些话

原本是打算好好证明下这种构造方式的正确性的...

结果写着写着发现与其写这么一大段还不如直接归约到 Kruskal 上...（当然也没写完，因为时间等等原因 \fad）

如果有人想继续探索这种构造方案的性质的话，这里就放几个之前写在正文的引理：

---

引理 $1.$ 对于边权均不相等的无向图，其最小生成树唯一

证明只需考虑反证法即可（以下证明搬自维基）：

![证明1](https://cdn.luogu.com.cn/upload/image_hosting/yf9psj08.png)

引理 $2.$ 若无向图有多种最小生成树方案，则所有方案的每种边权的边数都是相等的

只需套用证明 引理 $1.$ 的模式即可

引理 $3.$ 在无向图的多种最小生成树方案之间，若一条边 $e_1$ 能 “替换” 另一条同边权的边 $e_2$，那么它们一定同时在某个环上

（“替换” 这个词可能有点不严谨...这样写感觉比较简洁，见谅X）

证明很显然。否则 “替换” 后的方案就不再是生成树了

---

希望有所帮助X

---

## 作者：frankchenfu (赞：4)

## 题意简述
这道题需要我们求一种特殊的最小生成树。给定一个有$n$个节点和$m$条边的图，找出一个生成树满足从根节点$1$直接连向其余节点的边要恰好是$k$条，在此条件下生成树的权值和最小。

## 分析
### 算法1
理论上好像拓展次小生成树的算法（$k$小生成树）是可以写出来的，但是复杂度大约是$O(n^3)$，所以不能通过。（如果有dalao用这种方法写出复杂度更低的，那么就当我这句话没说）。

### 算法2
我们考虑使用最小生成树的`Kruskal`算法作为基础。`Kruskal`需要对边进行排序，然后从小到大贪心选择。为了保证与根的连边数量符合条件，我们是不是可以考虑对这些边“动一些手脚”呢？

于是我们把所有的边分成两类，一类是与根有联系的边集$E_1$，另一类是其他普通边构成的边集$E_2$。然后我们可以尝试给$E_1$中的边全部加上一个或正或负值$p$，这样就可以改变这些边排序时原有的次序。

比如，如果我们给每一条边都加上$-100001$的权值，那么所有$E_1$中的边都排在$E_2$的边之前（数据范围$1\le w_i\le 10^5$）；如果加上$100001$的权值，那么所有$E_1$中的边都排在$E_2$的边之后。如果这个$p$的绝对值较小，那么就有可能使$E_1$中边的排名稍微靠前或靠后一点。

然后我们就可以考虑二分这个值$p$，使得它刚好与根的连边有$k$条。二分的单调性是显然的，因为如果同时给$E_1$中的边加上$p$之后，$E_1$内和$E_2$内各自的边相对顺序不变，并且把$E_1$边权变小之后排名不会变后。所以这个结果是具有单调性的。

于是我们就可以通过二分查找到一个合适的$p$是的根节点度限制恰好为$k$。但是注意到有的时候这个算法二分出的结果并不是恰好$k$条，而我们要优先保证有解。所以我们最好要特判一下，然后按照上面的算法选择，同时加入“如果已经大于$k$，那么就略过此边”。最后代码中特判一些特殊情况即可。代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int MAXN=5010;
const int MAXM=100010;

struct edge{
    int u,v;double w;
    void adde(int u,int v,double w){
        this->u=u;
        this->v=v;
        this->w=w;
    }
}e[MAXM];
struct vect{
    int val[MAXM],tp;
    vect(){
        tp=0;
    }
    void clear(){
        tp=0;
    }
    void push(int v){
        val[++tp]=v;
    }
}res;

int n,m,k,p,ans=2147483647;
int ord[MAXM],cap;

struct ufs{
    int father[MAXN],sz;
    void resize(int n){
        sz=n;
        for(int i=1;i<=n;i++)
            father[i]=i;
    }
    int getfather(int x){
        if(x==father[x])
            return father[x];
        return father[x]=getfather(father[x]);
    }
}sol;

double wet;//weight
bool cmp_wet(const int &l,const int &r){
    double lans=e[l].w,rans=e[r].w;
    if(e[l].u==1)
        lans+=wet;
    if(e[r].u==1)
        rans+=wet;
    return lans<rans;
}
void check(){//kruscal
    sol.resize(n);res.clear();cap=0;
    std::sort(ord+1,ord+m+1,cmp_wet);//按照权重排序.
    for(int i=1;i<=m;i++){
        int a=sol.getfather(e[ord[i]].u),b=sol.getfather(e[ord[i]].v);
        if(a==b)
            continue;
        sol.father[a]=b;
        if(e[ord[i]].u==1)
            cap++;
        res.push(ord[i]);
        if(--sol.sz==1)
            return;
    }
}
void calc(){
    sol.resize(n);res.clear();cap=0;
    std::sort(ord+1,ord+m+1,cmp_wet);//按照权重排序.
    for(int i=1;i<=m;i++){
        int a=sol.getfather(e[ord[i]].u),b=sol.getfather(e[ord[i]].v);
        if(a==b)
            continue;
        if(e[ord[i]].u==1)
            cap++;
        if(cap>k){
            cap--;
            continue;
        }
        sol.father[a]=b;
        res.push(ord[i]);
        if(--sol.sz==1)
            return;
    }
}

int main(){
//	freopen("test.in","r",stdin);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v;double w;scanf("%d%d%lf",&u,&v,&w);
        if(u>v)
            std::swap(u,v);
        e[i].adde(u,v,w);
        if(u==1)
            p++;
    }
    if(p<k||(n>1&&!k)){
        puts("-1");
        return 0;
    }
    for(int i=1;i<=m;i++)
        ord[i]=i;
        
    check();
    if(sol.sz>1)//不连通 
    {
        puts("-1");
        return 0;
    }
    double l=-1e5,r=1e5+0.5;
    for(;;)
    {
        if(cap==k)
            break;
        if(l+0.1>r&&cap>k)
            break;
        
        double mid=(l+r)/2.0;
        wet=mid;check();
        
        if(cap<k)
            r=mid;
        else
            l=mid;
    }
    if(cap!=k)
    	calc();
    printf("%d\n",res.tp);
    for(int i=1;i<=res.tp;i++)
    	printf("%d ",res.val[i]);
    return 0;
} 
```

---

## 作者：Hamer_sans (赞：3)

## CF125E 题解

给定一张 $n$ 个点 $m$ 条边的无向图，求一棵最小生成树，满足包含根节点 $1$ 的边恰好有 $k$ 条，给出一种构造方案，$n\leq 5000$，$m\leq10^5$。

这里给出一种和 [P2619](https://www.luogu.com.cn/problem/P2619) 类似的做法。我们令包含 $1$ 的边为白边，其余的边为黑边，那么问题就转化成了和上面那道题一样的问题，考虑二分一个权值，每次令所有的白边加上这个权值，然后跑一边最小生成树，可以得到使用了的白边的数量 $cnt$，这个 $cnt$ 可能会大于题目给出的 $k$，但是可能对于每一条多出的白边都可以替换成一条边权相等的黑边，也有可能白边只是单纯多了，我们就可以提高这个权值，反之降低这个权值，这样我们就可以求出最小的权值和。现在问题是如何求出方案，我们发现求出法案的瓶颈是可能会有边权相同的黑边和白边，导致所求出的 $cnt$ 是大于 $k$ 的，如何解决？考虑加入一个随机扰动的权值，干扰我们当权值相同时的排序结果，然后这样就可以解决方案的问题，为保证求出方案，我们可以改变随机的值，再求一遍最小生成树，重复上述的操作多次，以增大得到方案的概率。

```
#include<bits/stdc++.h>
using std::sort;
inline int read(){
	char ch=getchar();
	int sum=0,h=1;
	while(!isdigit(ch)){if(ch=='-') h=-1;ch=getchar();}
	while(isdigit(ch)) sum=sum*10+ch-'0',ch=getchar();
	return sum*h;
}
const int N=1e5+5;
int n,m,k;
int fa[N];
int sum,cnt,ans;
int res[N],e[N],tt;
bool flag;
struct node{
	int x,y,val,c,id;
	double dom;
	bool operator < (const node &w) const{
		if(val==w.val) return dom<w.dom;//随机扰动排序结果
		return val<w.val;
	}
}t[N];
template<typename T>inline T min(T x,T y){
	return x<y?x:y;
}
template<typename T>inline T max(T x,T y){
	return x>y?x:y;
}
int get(int x){
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
bool check(int mid){
	for(int i=1;i<=m;++i) if(t[i].c==0) t[i].val+=mid;//将白边加上权值
	for(int i=1;i<=n;++i) fa[i]=i;
	sum=cnt=tt=0;
	sort(t+1,t+1+m);
	for(int i=1;i<=m;++i){
		int x=get(t[i].x),y=get(t[i].y);
		if(x==y) continue;
		fa[x]=y;
		sum+=t[i].val;
		cnt+=(t[i].c==0);
		res[++tt]=t[i].id;
	}
	for(int i=1;i<=m;++i) if(t[i].c==0) t[i].val-=mid;//删除贡献
	if(cnt==k){
		flag=1;
		for(int i=1;i<n;++i) e[i]=res[i];//统计方案
	}
	return cnt>=k;
}
int main(){
	srand(time(0));
	int tmp=rand();
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;++i){
		t[i].id=i;
		t[i].x=read(),t[i].y=read(),t[i].val=read();
		if(t[i].x!=1 and t[i].y!=1) t[i].c=1;
		t[i].dom=(double)rand()/RAND_MAX;
	}
	int l=-100001,r=100001;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			for(int T=1;T<=10;++T){//随机 10 次
				for(int i=1;i<=m;++i) t[i].dom=(double)rand()/RAND_MAX;
				check(mid);
			}
			l=mid+1;
		}
		else r=mid-1;
	}
	if(!flag){
		puts("-1");
		return 0;
	}
	printf("%d\n",n-1);
	for(int i=1;i<n;++i) printf("%d ",e[i]);
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：3)

[CF125E MST Company](https://www.luogu.com.cn/problem/CF125E)

对于一类凸函数，有时我们寻找极值是简单的，但如果加上一维限制，问题就变成了函数在某个特定位置的值，这时问题不好处理

wqs 二分通过二分斜率后寻找极值，可以用复杂度加一只 $\log$ 的代价消去一维的限制。

具体来说，在本题中，设以 $1$ 为端点的边为特殊边，以特殊边选的个数横坐标，对于 MST 的权值作为纵坐标，可以得到一个下凸的函数（感性理解为什么是凸的即可，如果强制选太多权值会变大，选太少的话也不优秀），我们可以用 Kruskal 求出它的最小值。

然后进行对斜率的二分，即每次用一条斜率不同的直线去截这个函数，这样就能得到想要的函数值。

本题一个不太好处理的点是要求输出方案，这里其实有一个比较简单的处理方式。

我们在二分出斜率后，如果尽量不选特殊边一定会得到 $\leq need$ 的条数，如果尽量选特殊边一定会得到 $\geq need$ 的条数。

因此，我们先以尽量不选特殊边的策略跑一边 Kruskal，记下这时选了的特殊边，这些特殊边一定是必选的。

然后我们用必选的特殊边合并并查集后，再跑一遍 Kruskal，这时全选非特殊边是合法的，一定不会有特殊边比非特殊边，只有可能出现权值相等的情况。

所以我们考虑优先选一些权值相等的特殊边，具体的，我们此时的策略是：如果 $need - \text{已选的条数}>0$，那么优先选特殊边，否则优先选非特殊边。

注意优先选指的是权值相等的情况下优先选哪一类，如果选的特殊边数量还没有满足要求，但是此时有一条非特殊边比特殊边优秀，那么也要先选特殊边。

代码如下（真的十分丑陋）：

```cpp
int n,m,q,l,r,ans1,ans2,cnt1,cnt2,mid,n1,n2,vis[100001],fa[1001];
vector<int> ans;
struct Node{int x,y,z,id;}a[100001],b[100001];
bool cmp(Node nd1,Node nd2){return nd1.z<nd2.z;}
namespace DSU
{
	inline void init(){for(int i=1;i<=n;++i)fa[i]=i;}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
}
using namespace DSU;
inline void checkl(int val)
{
	cnt1=0,ans1=0,init();
	for(int i=1,j=1;i<=n1||j<=n2;)
	{
		int x=0,y=0;
		while(i<=n1&&find(a[i].x)==find(a[i].y))++i;
		while(j<=n2&&find(b[j].x)==find(b[j].y))++j;
		if(i>n1&&j>n2)break;
		if(i>n1)x=INF;else x=a[i].z+val;
		if(j>n2)y=INF;else y=b[j].z;
		x<y?++cnt1,ans1+=x,fa[find(a[i].x)]=find(a[i].y),++i:(ans1+=y,fa[find(b[j].x)]=find(b[j].y),++j);
	}
}
inline void checkr(int val)
{
	cnt2=0,ans2=0,init();
	for(int i=1,j=1;i<=n1||j<=n2;)
	{
		int x=0,y=0;
		while(i<=n1&&find(a[i].x)==find(a[i].y))++i;
		while(j<=n2&&find(b[j].x)==find(b[j].y))++j;
		if(i>n1&&j>n2)break;
		if(i>n1)x=INF;else x=a[i].z+val;
		if(j>n2)y=INF;else y=b[j].z;
		x<=y?++cnt2,ans2+=x,fa[find(a[i].x)]=find(a[i].y),++i:(ans2+=y,fa[find(b[j].x)]=find(b[j].y),++j);
	}
}
inline void mian()
{
	read(n,m,q);int x,y,z;
	for(int i=1;i<=m;++i)read(x,y,z),x==1||y==1?a[++n1]={x,y,z,i}:b[++n2]={x,y,z,i};
	sort(a+1,a+1+n1,cmp),sort(b+1,b+1+n2,cmp),l=-inf,r=inf;
	while(l<r)
	{
		mid=l+((r-l)>>1),checkl(mid),checkr(mid);
		if(cnt1<=q&&cnt2>=q)l=r=mid;
		else if(cnt1>q)l=mid+1;
		else r=mid-1;
	}
	if(l==inf||l==-inf)return puts("-1"),void();
	checkl(l),checkr(l),init(),write(n-1,'\n');
	vector<pii> now;
	for(int i=1,j=1;i<=n1||j<=n2;)
	{
		int x=0,y=0;
		while(i<=n1&&find(a[i].x)==find(a[i].y))++i;
		while(j<=n2&&find(b[j].x)==find(b[j].y))++j;
		if(i>n1&&j>n2)break;
		if(i>n1)x=INF;else x=a[i].z+l;
		if(j>n2)y=INF;else y=b[j].z;
		x<y?(--q,fa[find(a[i].x)]=find(a[i].y),vis[a[i].id]=1,now.eb(mp(a[i].x,a[i].y)),ans.eb(a[i++].id)):(fa[find(b[j].x)]=find(b[j].y),j++);
	}
	init();
	for(int j=0;j<(int)now.size();++j)fa[find(now[j].fi)]=find(now[j].se);
	for(int i=1,j=1;i<=n1||j<=n2;)
	{
		int x=0,y=0;
		while(i<=n1&&(find(a[i].x)==find(a[i].y)||vis[a[i].id]))++i;
		while(j<=n2&&find(b[j].x)==find(b[j].y))++j;
		if(i>n1&&j>n2)break;
		if(i>n1)x=INF;else x=a[i].z+l;
		if(j>n2)y=INF;else y=b[j].z;
		x<=y&&q?--q,fa[find(a[i].x)]=find(a[i].y),vis[a[i].id]=1,ans.eb(a[i++].id):(fa[find(b[j].x)]=find(b[j].y),ans.eb(b[j++].id));
	}
	for(int i=0;i<(int)ans.size();++i)write(ans[i]);
}
```

---

## 作者：Sky_Maths (赞：1)

# 前言

[原题链接](https://www.luogu.com.cn/problem/CF125E)

[博客链接](https://www.luogu.com.cn/blog/Burningstars/AlienTrick)

## 写在最前面
作者本人也并非 WQS 二分的高手，存在错误在所难免，或者有一些理解不够透彻的地方，还请各位指出。

## 背景
其实是写完这道题后，看到讨论区里有许多人在问如 WAon\#7\#14 是怎么回事，当然，我也曾经错过，而且是两个都错过……

而这道题又十分考验 WQS 二分写法的 strong 程度

也许错在这两个点的同学是没有理清自己的思路？

于是写一篇题解，浅谈 WQS 二分的写法。

## 引用
先放两组来自 @EndSaH 的数据，感谢。

```txt
test 1.in
5 8 3
1 2 7
1 4 8
1 5 7
1 3 3
2 3 1
3 5 1
3 4 10
4 5 3
```

```txt
test 2.in
7 9 3
1 2 8
1 7 4
1 4 3
1 5 6
3 6 1
3 4 4
4 7 1
4 6 3
5 6 1
```

输出（权值）：
```
test 1.out
20
test 2.out
19
```

# 正文

首先，WQS 二分由两个部分组成，主函数的二分和 check 函数。

其中主函数的二分有许多写法，我用的是 `while(l<r)` 的写法，因为这样最后 $l=r$，容易找解。

按照我的理解，check 函数返回的是选择的次数/个数，在相同的 mid 应该会有一个区间 $\max/\min$，而我们要根据题目选择合适的搭配。

那我们就题论题，以 CF125E 为例，在本道题中，我采用的是以下写法：
```
while(l<r) {
    int mid=(l+r+1)>>1;
    if(check(mid).second>=k) l=mid;
    else r=mid-1;
}
```
解释一下，mid 代表每选一条特殊边，价格 $+mid$ ，即每条特殊边权值 $+mid$。

且 check 函数返回的是k的最大值，一般而言，返回的 k 是最大值 or 最小值都无所谓，但这道题采用最大值方便最终输出方案，因为最终的方案需要选满k条边，用最大值只需加一个已选特殊边数的特判即可。

我们继续，首先，若 mid 变大，则 k 变小（或不变），因为选用特殊边的价格变高了。

所以若 k 偏大，则需要使 mid 变大，即 l=mid。

同理，若 k 偏小，则需要使 mid 变小。

但是，注意，这里有一个需要想清楚的点，就是是 `l=mid+1` 还是 `r=mid-1`。

因为 k 已经取了最小值，若 k 还偏大，则此时肯定不存在答案（想清楚再进行下一步！），即 `if(check(mid)_k>k_we_need) l=mid+1 or r=mid-1`，而且注意，一般来说，取等与 `l=mid+1/r=mid-1` 是不能共存的，所以最终二分就出现了。

所以这里有三个需要想清楚的点：
1. 你的 check 函数是返回的上界还是下界。
2. 你的范围是如何切的，即 check(mid) 的 mid 对返回值造成的影响。
3. 哪种情况能取等。

注意细节，如 `r=mid-1` 和 `mid=(l+r)/2` 放一起可能会出现死循环。

# 结语
还有什么，想到再加。

# 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i(l),i##end(r);i<=i##end;++i)
#define gc getchar
#define mp make_pair
#define fi first
#define se second
#define ci const int
#define cll const ll
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
int rd() {
    int x(0); char ch=gc(); bool f(0);
    while(ch<'0'||ch>'9') f|=ch=='-',ch=gc();
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return f?-x:x;
}
ci N = 5e3 + 9;
ci E = 1e5 + 9;
ci Maxw = 5e3 + 9;
cll INF = 1e13;
int n,e,s,k,cnt0,cnt1;
int pa[N];
int u[E],v[E],w[E],id[E],idt[E],id0[E],id1[E];
bool col[E];
bool cmp(int a,int b) {if(w[a]!=w[b]) return w[a]<w[b];return col[a]>col[b];}
int find(int i) {return pa[i]==i?i:pa[i]=find(pa[i]);}
pli check(int mid) {
    rep(i,1,e) if(col[i]) w[i]+=mid;
    cnt0=cnt1=0;
    rep(i,1,e) {
        if(col[idt[i]]==0) id0[++cnt0]=idt[i];
        else id1[++cnt1]=idt[i];
    }
    merge(id0+1,id0+cnt0+1,id1+1,id1+cnt1+1,id+1,cmp);
    rep(i,1,n) pa[i]=i;
    int nowk=0,cnt=0;
    ll ans(0LL);
    rep(i,1,e) {
        int ux=find(u[id[i]]),vx=find(v[id[i]]);
        if(ux==vx) continue;
        ++cnt;
        if(col[id[i]]) ++nowk;
        ans+=w[id[i]];
        pa[ux]=vx;
    }
    rep(i,1,e) if(col[i]) w[i]-=mid;
    if(cnt==n-1) return mp(ans,nowk);
    else return mp(0,-1);
}
main() {
    n=rd();
    e=rd();
    s=1;
    k=rd();
    rep(i,1,e) u[i]=rd(),v[i]=rd(),w[i]=rd();
    rep(i,1,e) col[i]=(u[i]==s||v[i]==s);
    rep(i,1,e) idt[i]=i;
    sort(idt+1,idt+e+1,cmp);
    if(check(-Maxw).se<k||check(Maxw).se>k)
        return printf("-1\n"),0;
    int l=-Maxw,r=Maxw;
    while(l<r) {
        int mid=(l+r+1)>>1;
        if(check(mid).se>=k) l=mid;
        else r=mid-1;
    }
    printf("%lld\n",check(l).fi-1LL*k*l);//这里多输出了一个权值
    rep(i,1,e) if(col[i]) w[i]+=l;
    rep(i,1,n) pa[i]=i;
    rep(i,1,e) id[i]=i;
    sort(id+1,id+e+1,cmp);
    printf("%d\n",n-1);
    rep(i,1,e) {
        int ux=find(pa[u[id[i]]]);
        int vx=find(pa[v[id[i]]]);
        if(ux==vx) continue;
        if(col[id[i]]) {
            if(k) --k;
            else continue;
        }
        pa[ux]=vx;
        printf("%d ",id[i]);
    }
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

怎么都是二分。

注意到它给了 8s，考虑暴力。我们不断地更新生成树，直到 $d_1 =k$。具体的，我们先构造一棵最小生成树，那么我们枚举新增一条 $(1,x)$ 的边，则我们需要断掉 $P(1,x)$ 中的最大 $w$。那么实际上多的代价就是 $(1,x)$ 这条边的边权与 $w$ 的差值。每次新增差值最小的就行了。时间复杂度最坏 $O(mk+nk)$。实际上只跑了 250ms，很快。

不太懂的可以看代码。

## 代码

```cpp
il int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
il void dfs(int u,int fa){
	for(auto x:E[u]){
		int v=x.x,w=x.y.x,id=x.y.y;
		if(v!=fa){
			mx[v]=mx[u];
			if(mx[v].x<w&&!(e[id].x==1||e[id].y==1)) mx[v]={w,id};
			dfs(v,u);
		}
	}
	return ;
}

il void solve(){
 	n=rd,m=rd,k=rd;int D=0;
 	for(re int i=1;i<=m;++i) e[i]={rd,rd,rd,i};
 	for(re int i=1;i<=m;++i) if(e[i].x==1||e[i].y==1) ++D;
 	if(D<k||(k==0&&n>1)) return printf("-1\n"),void(0);
 	sort(e+1,e+m+1);int d=0;
 	for(re int i=1;i<=n;++i) f[i]=i;
	for(re int i=1;i<=m;++i)
	if(find(e[i].x)!=find(e[i].y)){
		if(e[i].x==1||e[i].y==1){
			if(d<=0){
				d=1;
				vis[i]=1,f[find(e[i].x)]=find(e[i].y);
			}
		}
		else vis[i]=1,f[find(e[i].x)]=find(e[i].y);
	}
	while(d<k){
		for(re int i=1;i<=n;++i) E[i].clear();
		for(re int i=1;i<=m;++i) if(vis[i]) E[e[i].x].push_back({e[i].y,{e[i].w,i}}),E[e[i].y].push_back({e[i].x,{e[i].w,i}});
		dfs(1,0);
		int Min=1e9+7,i1=0,i2=0;
		for(re int i=1;i<=m;++i)
		if((e[i].x==1||e[i].y==1)&&(!vis[i])&&find(e[i].x)==find(e[i].y)){
			pii Max=mx[max(e[i].x,e[i].y)];
			if(Min>e[i].w-Max.x&&Max.y){
				Min=e[i].w-Max.x;
				i1=i,i2=Max.y;
			}
		}
		else if((e[i].x==1||e[i].y==1)&&(!vis[i])){
			if(Min>e[i].w){
				Min=e[i].w;Min=-1;
				i1=i,i2=0;
			}
		}
		++d;
		if(!i2){
			f[find(e[i1].x)]=find(e[i1].y);
			vis[i1]=1;
		}
		else vis[i2]=0,vis[i1]=1;
	}
	cout<<n-1<<"\n";
	for(re int i=1;i<=m;++i) if(vis[i]) res[e[i].id]=1;
	for(re int i=1;i<=m;++i) if(res[i]) cout<<i<<" ";
    return ;
}
```

---

## 作者：foreverlasting (赞：0)

[题面](https://www.luogu.org/problemnew/show/CF125E)

凸优化。（其实只是$wqs$二分）

这题与[这道题](https://www.luogu.org/problemnew/show/P2619)基本一致，所以直接上$wqs$二分就好了。不过这里要注意两个小细节，首先判断这条边的端点是否有$1$，这当然好解决，端点将小的编号放前面就行了。第二点，考虑一个贪心策略：边端点最小的编号越大越先考虑。这显然是对的，因为$1$号点是最小的编号，所以它最后放肯定没错。其他就是基本套路了。

code:
```
//2018.9.14 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int M=1e5+10;
const int N=5e3+10;
namespace MAIN{
    int n,m,k;
    struct E{
        int u,v,w,id;
        E() {}
        E(res u,res v,res w,res id):u(u),v(v),w(w),id(id) {}
        inline bool operator < (const E &b) const {
            return w!=b.w?w<b.w:u>b.u;
        }
    }edge[M],ed0[M];
    int fa[N];
    inline int find(res x){
        while(x!=fa[x])x=fa[x]=fa[fa[x]];
        return x;
    }
    int cnt;
    int ED[M],sum;
    inline void init(res lim){
        for(res i=1;i<=n;i++)fa[i]=i;
        cnt=sum=0;
        for(res i=1;i<=m;i++){
            res u=edge[i].u,v=edge[i].v,w=u==1?edge[i].w+lim:edge[i].w;
            ed0[i]=E(u,v,w,i);
        }
        sort(ed0+1,ed0+1+m);
    }
    inline void calc(res lim){
        init(lim);
        for(res i=1;i<=m;i++){
            res u=ed0[i].u,v=ed0[i].v,fu=find(u),fv=find(v);
            if(fu==fv||(u==1&&cnt==k))continue;
            fa[fu]=fv;
            ED[++sum]=ed0[i].id;
            if(u==1)cnt++;
            if(sum==n-1)break;
        }
    }
    inline void MAIN(){
        n=read(),m=read(),k=read();
        for(res i=1;i<=m;i++){
            res u=read(),v=read(),w=read();
            if(u>v)_swap(u,v);
            edge[i]=E(u,v,w,i);
        }
        res l=-m,r=m;
        while(l<r){
            res mid=(l+r+1)>>1;
            calc(mid);
            if(cnt>=k)l=mid;
            else r=mid-1;
        }
        calc(l);
        if(sum!=n-1||cnt<k)puts("-1");
        else {
            printf("%d\n",sum);
            for(res i=1;i<=sum;i++)printf("%d ",ED[i]);
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

