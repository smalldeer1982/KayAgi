# [ABC361G] Go Territory

## 题目描述

在二维平面上有 $N$ 个石头。第 $i$ 个石头位于坐标 $(X_i, Y_i)$。所有石头都位于第一象限（包括坐标轴上的）格点上。

请你求出有多少个没有石头的格点 $(x, y)$，满足无法通过不断向上下左右移动 $1$ 的方式，不经过任何石头，最终到达 $(-1, -1)$。

更准确地说，求有多少个没有石头的格点 $(x, y)$，不存在满足以下 $4$ 个条件的有限整数序列 $(x_0, y_0), \ldots, (x_k, y_k)$：

- $(x_0, y_0) = (x, y)$
- $(x_k, y_k) = (-1, -1)$
- 对于所有 $0 \leq i < k$，都有 $|x_i - x_{i+1}| + |y_i - y_{i+1}| = 1$
- 对于所有 $0 \leq i \leq k$，$(x_i, y_i)$ 上都没有石头

## 说明/提示

## 限制条件

- $0 \leq N \leq 2 \times 10^5$
- $0 \leq X_i, Y_i \leq 2 \times 10^5$
- $(X_i, Y_i)$ 互不相同
- 所有输入均为整数

## 样例解释 1

从 $(1,1)$ 无法到达 $(-1,-1)$。  
![](https://img.atcoder.jp/abc361/77ce335c7ebd31af0860ce2aa43ae32a.png)

## 样例解释 2

也可能没有任何石头。

## 样例解释 3

$(6,1),(6,2),(6,3),(7,1),(7,2),(7,3)$ 这 $6$ 个格点满足条件。  
![](https://img.atcoder.jp/abc361/95ffd845cfab71f0cd6b3c8122eb1ac9.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 0
0 1
2 3
1 2
2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
0```

### 输出

```
0```

## 样例 #3

### 输入

```
22
0 1
0 2
0 3
1 0
1 4
2 0
2 2
2 4
3 0
3 1
3 2
3 4
5 1
5 2
5 3
6 0
6 4
7 0
7 4
8 1
8 2
8 3```

### 输出

```
6```

# 题解

## 作者：MisaYuzuki (赞：9)

似乎是极其常见的经典 trick 了呢！场上切 G 的那么少似乎有些奇怪。

题目大意即给定一个值域为 $[-1,2\times 10^5+1]$ 的二维平面，给出 $n$ 个黑点的坐标（保证互不相同，且坐标均在 $[0,2\times 10^5]$ 内），求剩下白点构成的不包含 $(-1,-1)$ 的四联通块的大小总和。

令 $V=2\times 10^5+3$。联通块很容易想到并查集。考虑暴力咋做。只需要在边界范围为 $[-1,2\times 10^5+1]$ 的这个二维平面内的每个点暴力判断连边即可。复杂度是 $\Theta(V^2\alpha(V^2))$ 的。很显然过不去。

观察到对于第 $i$ 行而言，有很多挨在一起的白点，若这些白点均往第 $i+1$ 行连边时间复杂度是 $\Theta(V)$ 的。这些挨在一起的白点本身构成一个联通块，我们希望第 $i$ 行的形如 $(i,l),(i,l+1)\dots(i,r)$ 的序列所构成的一整个联通块只向第 $i+1$ 行像这样的联通块只连一次边。

处理相对简单，拎出第 $i$ 行所有的黑点，排序后暴力判断第 $k$ 和第 $k+1$ 个节点之间的空间是否能构成一个联通块。例如 $(i,a_k=j),(i,a_{k+1}=j+1)$ 之间就无法构成联通块。由于每多一个黑点，相应行的联通块个数最多会增加 $1$，所以这样的联通块个数最多是 $V+n$。

至于连边，由于同行之间已经视为一个联通块，则只需考虑同列之间的连边。假设当前第 $k$ 行和第 $k+1$ 行所形成的联通块序列分别为 $a_1,a_2,\dots,a_p$ 和 $b_1,b_2,\dots b_q$，那么若存在边 $(a_i,b_j)$ ，则 $\forall u\gt0,v\ge 0$，边 $(a_{i+u},b_{j-v})$ 不存在。这个很好理解。也就是边对应的指针 $i,j$ 单调。由于是单调的，所以最多连 $i+j-1$ 条边。想要准确找到每条边可以使用双指针技术做到线性。

排序 $\Theta(n\log n)$，联通块个数最多为 $V+n$，边个数最多为 $V+2n$，所以本做法总时间复杂度为 $\Theta(n\log n+(V+n)\alpha(V+n))$。

[code](https://atcoder.jp/contests/abc361/submissions/55423642)

---

## 作者：zac2010 (赞：4)

### 解题思路

这类数据范围较大的平面图问题的一个基本思路就是扫描线。

* 一个最初的想法是把连续的障碍点看成一个平面上的木条，然后求相对于 $(-1,-1)$ 来说，被围起来的非障碍点有多少个。

  但是我们发现扫描线很难维护的是——当前这些木条能围住多少个非障碍点。

于是我们考虑反过来，直接去维护非障碍点的连续段。因为一行里的连续段具有不交的良好性质，所以对于相邻的两行，双指针维护连边即可。

### 代码实现


```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define Sz(v) ((int)v.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int N = 2e5 + 10, V = 2e5 + 3;
int n, sp, totp;
ll ans;
pii p[N * 2];
vi v[N], now, lst;
namespace DSU{
    int fa[N * 2];
    int Find(int u){
        return fa[u] == u? u : fa[u] = Find(fa[u]);
    }
    void Union(int u, int v){
        fa[Find(u)] = Find(v);
    }
}
using namespace DSU;
int NewP(int l, int r){
    p[++totp] = {l, r};
    return fa[totp] = totp;
}
void Input(){
    scanf("%d", &n);
    FL(i, 1, n){
        int x, y;
        scanf("%d%d", &x, &y);
        v[++x].eb(++y);
    }
}
void Build(){
    lst.eb(sp = NewP(0, V - 1));
    FL(x, 1, V){
        now.clear(), v[x].eb(V);
        sort(v[x].begin(), v[x].end());
        int ly = -1;
        for(int y: v[x]){
            if(y - ly > 1){
                now.eb(NewP(ly + 1, y - 1));
            }
            ly = y;
        }
        int i = 0, j = 0;
        while(i < Sz(now) && j < Sz(lst)){
            if(p[now[i]].se < p[lst[j]].se){
                if(p[now[i]].se >= p[lst[j]].fi){
                    Union(now[i], lst[j]);
                }
                ++i;
            }
            else{
                if(p[lst[j]].se >= p[now[i]].fi){
                    Union(now[i], lst[j]);
                }
                ++j;
            }
        }
        for(int i: now){
            for(; j < Sz(lst) && p[lst[j]].se <= p[i].se; ++j){
                if(p[i].fi <= p[lst[j]].se){
                    Union(i, lst[j]);
                }
            }
        }
        lst.swap(now);
    }
}
void CalcAns(){
    FL(i, 1, totp){
        if(Find(i) != Find(sp)){
            ans += p[i].se - p[i].fi + 1;
        }
    }
}
void Output(){
    printf("%lld\n", ans);
}
int main(){
    Input();
    Build();
    CalcAns();
    Output();
    return 0;
}
```

---

## 作者：DrAlfred (赞：4)

摘要：并查集，双指针

[传送门：https://www.luogu.com.cn/problem/AT_abc361_g](https://www.luogu.com.cn/problem/AT_abc361_g)

## 题意

平面上有 $n$ 个障碍点 $(x_1, y_1), (x_2, y_2), \dots (x_n, y_n)$。如果从一个**非障碍点**出发，经历若干次上、下、左、右移动而不经过障碍点无法到达 $(-1, -1)$，那么称这个点是不自由的。求出平面上不自由的点的个数。

## 分析思路

如果我们将每一行没有被障碍覆盖的点的连续段预处理出来，容易发现这些连续段上的所有点是否自由是一定的，且上下临接的连续段的关系可以构成一张图。考虑对第 $-1$ 行单独建立一个点 $0$。则某个连续段是否自由等价于在图上是是否能到达 $0$。即最终的答案是非自由的连续段的长度之和。

第一步，我们先处理出每一行的连续段。考虑用 $(x, y_a, y_b)$ 描述在第 $x$ 行，纵坐标从 $y_a$ 到 $y_b$ 的一个连续段。使用 `map<int, vector<int>>` 记录每一行分别有哪些障碍点纵坐标。对于每一行，先对其横坐标进行排序。随后对于横坐标差距大于 $1$ 的两个相邻的点记录连续段。特别地我们插入 $(x, -inf, y_0 - 1)$ 与 $(x, y_{last} + 1, inf)$，方便后续图论建模。同时对于输入的每个障碍点，需要预留它的上一行和下一行为空 `vector`（这样才能更方便连接到点 $0$），在处理线段时若仍然为空视作 $(x, -inf, inf)$。时间复杂度 $O\left(n \log n\right)$。

第二步，考虑建图。首先对于 $y_a = -inf$ 或 $y_b = inf$ 的连续段，一定能先向左右移动到非常远的列，随后往下移动到第 $-1$ 行，最终移动到 $(-1, -1)$。所以对于这些线段，直接与点 $0$ 相连。然后要处理临接的连续段。考虑使用双指针算法求出在 $(x, y_a, y_b)$ 的上一行（即第 $x + 1$ 行），且就纵坐标来说，与 $(y_a, y_b)$ 有交的那些线段。容易发现符合条件的线段的编号不减。时间复杂度 $O\left(n\right)$。

最终统计出答案即可。总时间复杂度 $O\left(n \log n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct DSU {
    std::vector<int> fa, siz;
    DSU(int n) : fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] < siz[fy]) swap(fx, fy);
        fa[fy] = fx, siz[fx] += siz[fy], siz[fy] = 0;
        return true;
    }
};
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int n, x, y;
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n;
    map<int, vector<int>> mp;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y, mp[x].push_back(y);
        mp[x - 1], mp[x + 1]; // 为空行预留，map 访问下标就会创建新对象。
    }
    const int inf = 1e9;
    vector<array<int, 3>> segs;
    // 非障碍点构成的连续段。以 (x, ya, yb) 描述，至多 3n 个。
    for (auto &[x, ys] : mp) {
        if (ys.empty()) {
            segs.push_back({x, -inf, inf});
        } else {
            const int sz = ys.size();
            std::sort(ys.begin(), ys.end());
            segs.push_back({x, -inf, ys[0] - 1});
            for (int i = 0; i < sz - 1; i++) {
                if (ys[i + 1] - ys[i] > 1) {
                    segs.push_back({x, ys[i] + 1, ys[i + 1] - 1});
                }
            }
            segs.push_back({x, ys.back() + 1, inf});
        }
    }
    DSU D(segs.size());
    const int siz = segs.size();
    // 用点 0 代表自由。我们可以知道 segs[0] = {-1, -inf, inf}，因为 -1 一定是空行。
    for (int i = 0; i < siz; i++) {
        auto [x, ya, yb] = segs[i];
        if (ya == -inf || yb == inf) {
            D.merge(0, i); // 如果某个段左侧或右侧没有任何障碍点，那它一定自由。
        }
    }
    // 双指针
    for (int i = 0, j = 0; i < siz; i++) {
        // 找到 segs[i] 的上一行中，就 y 坐标而言与 segs[i] 有交的 segs[j]。
        while (j < siz && (segs[j][0] < segs[i][0] + 1 || segs[j][2] < segs[i][1])) j++;
        while (j < siz && segs[j][0] == segs[i][0] + 1 && segs[j][1] <= segs[i][2]) {
            D.merge(i, j++);
        }
        j--; // 最后一个 j 不满足，需要撤回以保证下次还能用到这个 j。
    }
    i64 ans = 0;
    for (int i = 0; i < siz; i++) {
        if (D.find(i) != D.find(0)) {
            // 对于非自由连续段，答案加上它们的长度。
            ans += segs[i][2] - segs[i][1] + 1;
        }
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：lingziyi2025 (赞：4)

# [ABC361G] Go Territory 题解

### 题意

平面内给 $n$ 个障碍，每个点只能上下左右、不经过障碍走。

求不能到达 $(-1,-1)$ 的点的个数。$n,x,y\le 2\times 10^5$。

### 题解

暴力地，可以对每个点使用并查集。

但是点数过大，考虑针对题目优化。

我们发现，很多点都是连成一大片的，能被那 $2\times10^5$ 分割的点很少，考虑缩点，去除冗余。

对于 $y$ 相同、$x$ 连续的点，可以将它们缩成一个长方形的大点；可以证明这样的大点有 $O(n)$ 个。

于是对大点使用双指针连边，并查集判断即可。

### Code

```c++
#include<bits/stdc++.h>
#define rg register int
#define fo(i,l,r) for(rg i=l;i<=r;i++)
#define dfo(i,r,l) for(rg i=r;i>=l;i--)
#define frein freopen("in.txt","r",stdin);
#define freout freopen("out.txt","w",stdout);
#define fre(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define outa(l,r,a) {fo(i,l,r)cout<<a[i]<<" ";cout<<"\n";}
#define outm(l1,r1,l2,r2,a) {fo(i,l1,r1){fo(j,l2,r2)cout<<a[i][j]<<" ";cout<<"\n";}cout<<"\n";}
#define BZ cout<<"----------------\n";
#define int long long
using namespace std;
const int N=5e5+5;
int n,mx=2e5+2,la,p,l[N],r[N],ans;
struct pt{int x,y;}a[N];
bool cmp(pt a,pt b){return a.y==b.y?a.x<b.x:a.y<b.y;}
struct L{int y,l,r;}b[N];int cnt;
int f[N];
int find(int x){
	if(x==f[x])return x;
	else return f[x]=find(f[x]);
}
signed main(){
	frein;
	cin>>n;
	fo(i,1,n)cin>>a[i].x>>a[i].y,a[i].x++,a[i].y++;
	sort(a+1,a+1+n,cmp);p=1;
	fo(y,0,mx){
		l[y]=cnt+1,la=0;
		while(p<=n&&a[p].y==y){
			if(la<=a[p].x-1)b[++cnt]={y,la,a[p].x-1};
			la=a[p].x+1,p++;
		}
		b[++cnt]={y,la,mx},r[y]=cnt;
	}
	fo(i,1,cnt)f[i]=i;
	fo(y,0,mx-1){
		p=l[y+1];
		fo(i,l[y],r[y]){
			while(p<=r[y+1]&&b[p].r<b[i].l)p++;
			while(p<=r[y+1]&&b[i].l<=b[p].r&&b[p].r<=b[i].r)f[find(i)]=find(p),p++;
			while(p<=r[y+1]&&b[p].l<=b[i].r&&b[i].r<=b[p].r)f[find(i)]=find(p),p++;
			p--;
		}
	}
	fo(i,2,cnt)if(find(1)!=find(i))ans+=(b[i].r-b[i].l+1);
	cout<<ans;
	return 0;
}
```

---

## 作者：__Floze3__ (赞：2)

（温馨提示：本篇题解是在测试员 yuto1115 的做法上加以自己的理解写成）

我们可以对于每一行分别处理，对于这一行内被石子分割出来的几条线段，我们将其看作一个元素，记录下它在哪一行，它的左端点，它的右端点。如图（这是官方题解的图）：
![](https://cdn.luogu.com.cn/upload/image_hosting/uykz06gx.png)

那么，我们可以从下到上，根据线段的左右端点，将上下联通的两个线段合并起来，用并查集可以很方便的做到这一点。最后我们遍历每条线段，统计未与最左下角的线段联通的线段长度之和即可，时间复杂度为 $O(N \log N)$，瓶颈在于对于每一行端点的排序。

## 代码

[提交记录](https://atcoder.jp/contests/abc361/submissions/55341197)

---

## 作者：int_R (赞：2)

首先肯定要找一个切入点，很自然的想法是扫描一维。然后维护连续段，即在当前行没有被棋子隔开的为同一个连续段。但是不同连续段可能是同一个连通块，所以维护连续段之间的连通性。

大体意思就是扫描到新的一行时，先把所有棋子放进去，然后每个棋子的位置都是一个新的连通块，然后扫一遍连续段，把连通块合并，然后把连通块的大小加上当前行属于该连通块的位置的个数。

一个连通块被围起来相当于是不会到达最后一行，所以累加所有没有在最后一行出现的连通块的大小即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int MAXN=2e5+10;
struct node{int l,r,c;};vector <node> s,now;
vector <int> v[MAXN];ll sum[MAXN],ans;
int n,tot,fa[MAXN];bool vis[MAXN];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;for(int i=1,x,y;i<=n;++i)
        cin>>x>>y,v[y].push_back(x);
    for(int i=0;i<=n;++i) fa[i]=i;
    s.push_back({-MAXN,MAXN,0});
    for(int y=0;y<=2e5;++y)
    {
        sort(v[y].begin(),v[y].end());
        now.clear();
        int i=0;for(node p:s)
        {
            int pre=p.l;
            for(;i<v[y].size()&&v[y][i]<=p.r;++i)
            {
                if(pre<v[y][i]) now.push_back({pre,v[y][i]-1,p.c});
                now.push_back({v[y][i],v[y][i],-1}),pre=v[y][i]+1;
            }
            if(pre<=p.r) now.push_back({pre,p.r,p.c});
        }
        s.clear();int pre=-MAXN;
        for(int i=0;i<now.size();++i)
        {
            if(now[i].c==-1)
            {
                if(i&&now[i-1].c!=-1)
                {
                    sum[find(now[i-1].c)]+=(now[i-1].r-pre+1);
                    s.push_back({pre,now[i-1].r,now[i-1].c});
                }
                s.push_back({now[i].l,now[i].r,++tot});
                pre=now[i].r+1;continue;
            }
            if(!i||now[i-1].c==-1) continue;
            int u=find(now[i-1].c),v=find(now[i].c);
            if(u==v) continue;sum[v]+=sum[u],fa[u]=v;
        }
        s.push_back({pre,now.back().r,now.back().c});
    }
    for(node p:s) vis[find(p.c)]=true;
    for(int i=0;i<=n;++i)
        if(!vis[find(i)]) ans+=sum[fa[i]],sum[fa[i]]=0;
    cout<<ans<<'\n';return 0;
}
```

---

## 作者：Starrykiller (赞：1)

考虑每一个横坐标 $x$。

每一个 $x$ 会被黑棋分割成若干个区间。对于相邻的 $x$ 坐标的两个区间 $[l,r]$，$[L,R]$，这两个区间内的点能够相互到达当且仅当 $[l,r]\cap [L,R]\neq \varnothing$。显然这样的区间只有 $\Theta(n)$ 个。

这些区间可以容易地用平衡树来维护。我们给每个区间分配一个编号。（按端点）从小到大枚举 $x$ 内的每一个区间 $[l,r]$，发现 $x-1$ 内与 $[l,r]$ 有交的区间（端点）是单调递增的，于是可以双指针。双指针后利用并查集维护连通性就可以了。

需要注意的是，答案可能大于 $2^{31}-1$（稍微算一下就可以知道了）。[代码](https://atcoder.jp/contests/abc361/submissions/55419062)。

时间复杂度 $\Theta(n\log n)$。

---

## 作者：封禁用户 (赞：1)

一个类似于珂朵莉树的做法。在相同的 $y$ 坐标上，用石头将 $[-1,200001]$ 整区间分成若干段在图上各建一个点，记录点上对应的整点数量。然后靠左/右两段与超级源点连一条边，$y$ 坐标最小/大上的所有点也与源点连边。

$y$ 坐标相差 $1$ 的地方用指针来回扫，将之间点对应的整段 $x$ 坐标有重叠的点之间连一条边（容易证明改时间复杂度是线性）。

然后从超级源点遍历联通的所有点，将非联通的所有点记录权值加起来即为答案。时间复杂度只看排序 $O(n\log n)$。

以下是代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
	int xx,yy;
}vert[200005];

int n,pt,tans,val[400005],bi[200015][2];
vector<pair<int,int> >cothol[400005];
vector<int>mp[400055];bool is_visited[400055];

int nw(){
	return++pt;
}

bool cmp(node fst,node scd){
	return fst.yy!=scd.yy?fst.yy<scd.yy:fst.xx<scd.xx;
}

void dfs(int now){
	if(is_visited[now])return;
	is_visited[now]=1;tans-=val[now];
	for(int o=0;o<mp[now].size();o++)dfs(mp[now][o]);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>vert[i].xx>>vert[i].yy;
		vert[i].xx++;vert[i].yy++;
	}
	sort(vert+1,vert+n+1,cmp);
	for(int i=1,j=1;i<=200001;i++){
		int lstair=0;
		while(j<=n&&vert[j].yy==i){
			if(lstair<vert[j].xx)cothol[i].push_back(make_pair(lstair,vert[j].xx-1));
			lstair=vert[j].xx+1;j++;
		}
		cothol[i].push_back(make_pair(lstair,200002));
	}
	nw();
	for(int i=1;i<=200001;i++){
		for(int o=0;o<cothol[i].size();o++){
			bi[o][1]=nw();val[bi[o][1]]=cothol[i][o].second-cothol[i][o].first+1;tans+=val[bi[o][1]];
			if(i==1||i==200001||o==0||o==cothol[i].size()-1){
				mp[bi[o][1]].push_back(1);mp[1].push_back(bi[o][1]);
			}
		}
		if(i==1)continue;
		for(int o1=0,o2=0;o1<cothol[i].size();o1++){
			while(o2<cothol[i-1].size()&&cothol[i-1][o2].second<cothol[i][o1].first)o2++;
			while(o2<cothol[i-1].size()&&cothol[i-1][o2].second<=cothol[i][o1].second){
				mp[bi[o1][1]].push_back(bi[o2][0]);mp[bi[o2][0]].push_back(bi[o1][1]);o2++;
			}
		}
		for(int o2=0,o1=0;o2<cothol[i-1].size();o2++){
			while(o1<cothol[i].size()&&cothol[i][o1].second<cothol[i-1][o2].first)o1++;
			while(o1<cothol[i].size()&&cothol[i][o1].second<=cothol[i-1][o2].second){
				mp[bi[o1][1]].push_back(bi[o2][0]);mp[bi[o2][0]].push_back(bi[o1][1]);o1++;
			}
		}
		for(int o=0;o<cothol[i].size();o++){
			bi[o][0]=bi[o][1];
		}
	}
	dfs(1);cout<<tans;return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

注意到点的个数有限，考虑分块算贡献。

即对于 $y=a$ 这条直线上的点，可以将 $[0,+\infty]$ 这个区间根据横坐标分为多个块。

然后建一个源点，先对于整个平面周长上的块连边（因为都可以绕路到达）。

之后考虑块与块之间的连边，注意到只要两个块的区间范围有交，且两个块上下相邻，就可以互相到达连边。

且因为同一个纵坐标上的块，互相之间没有重叠，故可以用走指针的方法 $O(W)$ 实现。

最后跑一遍 bfs，源点没有遍历到的块就是在封闭图形内的点，将长度加入贡献即可。

时间复杂度为 $O(N+W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=5e6+10,M=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
bool Begin;
struct Seg{
	ll l,r;
	ll id;
}H[N];
ll n,ans,s=1,cnt=1;
ll a[N],b[N],len[N];
bool f[N];
vector<ll> E[N],T[N],G[N];
bool End;
void add(ll u,ll v){
	T[u].push_back(v);
	T[v].push_back(u);
}
void bfs(ll s){
	queue<ll> Q;
	Q.push(s);
	while(!Q.empty()){
		ll u=Q.front();
		Q.pop();
		if(f[u])
		  continue;
		f[u]=1;
		for(auto v:T[u]){
			if(f[v])
			  continue;
			Q.push(v);
		}
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
		E[b[i]].push_back(a[i]);
	}
	for(int x,y,i=0;i<M;i++){
		x=0,y=M-1;
		sort(E[i].begin(),E[i].end());
		for(auto v:E[i]){
			if(v-1>=x){
				++cnt;
				H[cnt]={x,v-1,cnt};
				G[i].push_back(cnt);
				len[cnt]=v-x;
			}
			x=v+1;
		}
		++cnt;
		H[cnt]={x,y,cnt};
		G[i].push_back(cnt);
		len[cnt]=y-x+1;
	}
	for(int i=0;i<M;i++){
		if(!i||i==M-1){
			for(auto v:G[i])
			  add(s,H[v].id);
			continue;
		}
		if(!H[G[i][0]].l)
		  add(s,H[G[i][0]].id);
		if(G[i].size()!=1)
		  add(s,H[G[i][G[i].size()-1]].id);
	}
	for(int i=1;i<M;i++){
		ll x=0;
		for(auto v:G[i]){
			while(H[G[i-1][x]].l<H[v].l){
				if(x+1==G[i-1].size())
				  break;
				x++;
			}
			if(x&&H[G[i-1][x-1]].r>=H[v].l)
			  add(H[v].id,H[G[i-1][x-1]].id);
			while(H[G[i-1][x]].l<=H[v].r){
				add(H[v].id,H[G[i-1][x]].id);
				if(x+1==G[i-1].size())
				  break;
				x++;
			}
		}
	}
	bfs(s);
	for(int i=2;i<=cnt;i++)
	  if(!f[i])
	    ans+=len[i];
	write(ans);
	cerr<<"\n"<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：larsr (赞：1)

数学课无聊的时候想出来的……

题意简化：给你一个网格和几个障碍，求被障碍围住的格子有多少个。

明显直接把网格设定为 $M\times M$ 的，其中 $M=2\times10^5+1$。如果一个点可以到达网格之外就不贡献答案，那么直接计算可以到达网格外的格子即可。

考虑用并查集计算，但格子数量太多了，那么就提前把一些合并。对于同一行内两个相邻障碍之间的格子合并成一个，然后再对于它们进行合并即可。明显格子数量为 $O(M+n)$，其他的合并次数也为 $O(M+n)$。

Code:
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 1000010
#define M 200002
#define ll long long
using namespace std;
int n;
vector<int>e[N], id[N];
int tot = 0, f[N];
ll siz[N];
int getfa(int x)
{
	if(f[x] == x)return x;
	return f[x] = getfa(f[x]);
}
void unio(int x, int y)
{
	if(!siz[x] || !siz[y])return;
	x = getfa(x);
	y = getfa(y);
	if(x == y)return;
	f[y] = x;
	siz[x] += siz[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		e[y].push_back(x);
	}
	siz[0] = 1;
	for(int i = 1; i < N; i++)f[i] = i;
	for(int i = 0; i <= M; i++)
	{
		e[i].push_back(M);
		sort(e[i].begin(), e[i].end());
		int las = -1, now = 0;
		for(int j = 0; j < e[i].size(); j++)
		{
			tot++;
			id[i].push_back(tot);
			siz[tot] = e[i][j] - las - 1;
			if(i)
			{
				while(e[i - 1][now] - 1 <= las)now++;
				while(e[i - 1][now] < e[i][j])
				{
					unio(id[i - 1][now], tot);
					now++;
				}
				int x;
				if(now == 0)x = -1;
				else x = e[i - 1][now - 1];
				if(x < e[i][j] - 1) unio(id[i - 1][now], tot);
			}
			if(!i || i == M || !j || j == e[i].size() - 1) unio(0, tot);
			las = e[i][j];
		}
	}
	printf("%lld\n", 1ll * (M + 1) * M - siz[getfa(0)] - n + 1);
	return 0;
}

```

---

## 作者：Forg1weN (赞：0)

题意转化为求有多少点被围住了。

对于横坐标为 $x$ 的一列来看，放入一个点 $(x,y)$ 相当于把原来这一列内可以互相到达的点分成了 $(-\infty,y-1],[y+1,+\infty)$ 两部分，启示我们可以通过并查集来维护是否可以互相通达的信息。

对于坐标系里面相邻的两列，利用双指针来判断两列里面的段落是否能够互相通达。可以在点集的前后添加一段无论如何都会联通的段落来保证三面围住一面敞开的点集能够与 $(-1,-1)$ 联通。

考虑放入一个棋子会多一个段落，段落数量是 $O(n)$ 的，双指针维护并查集复杂度为 $O(n)$，瓶颈在于排序，所以总复杂度是 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
const int inf =1e9;
const int lim =2e5+2;

int n,cnt;
ll ans;
int fa[maxn];
ll sz[maxn];
struct node { int x,y; }a[maxn];
struct line { int l,r,id; };
vector<line>seg[maxn];

bool cmp(node a,node b) {
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
int find(int x) { return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int u,int v) {
	u=find(u),v=find(v);
	sz[u]+=sz[v],fa[v]=u;
}
bool pd(line a,line b) {
	int L=max(a.l,b.l),R=min(a.r,b.r);
	return (L<=R?1:0);
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].x++,a[i].y++;
	}
	sort(a+1,a+1+n,cmp);
	seg[0].push_back({0,lim,++cnt});
	for(int i=1;i<=n;i++) {
		if(a[i].x!=a[i-1].x) seg[a[i].x].push_back({0,a[i].y-1,++cnt});
		if(a[i].x!=a[i+1].x) seg[a[i].x].push_back({a[i].y+1,lim,++cnt});
		else seg[a[i].x].push_back({a[i].y+1,a[i+1].y-1,++cnt});
	}
	int mx=a[n].x;
	for(int i=1;i<=mx+1;i++) if(seg[i].empty()) seg[i].push_back({0,lim,++cnt});
	for(int i=0;i<=mx+1;i++)
		for(auto j:seg[i])
			fa[j.id]=j.id,sz[j.id]=j.r-j.l+1;
	
	for(int i=1;i<=mx+1;i++) {
		int p1=0,p2=0,l1=seg[i-1].size(),l2=seg[i].size();
		while(p1<l1&&p2<l2) {
			if(pd(seg[i-1][p1],seg[i][p2]))
				merge(seg[i-1][p1].id,seg[i][p2].id);
			if(seg[i-1][p1].r<seg[i][p2].r&&p1<l1)p1++;
			else p2++;
		}
	}
	merge(1,cnt);
	for(int i=0;i<=mx+1;i++)
		for(auto j:seg[i])
			if(find(j.id)!=find(1))
				ans+=j.r-j.l+1;
	printf("%lld",ans);
	return 0;
}
```

---

