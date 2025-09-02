# A Wide, Wide Graph

## 题目描述

给定一棵 $n$（$2\leq n\leq 10^5$）个节点的无根树，对于每个 $k$（$1\leq k \leq n$），定义一个无向图 $G_k$，其中由边连接的两个节点 $u$ 和 $v$ 的距离至少为 $k$。请你计算 $G_k$ 的连通块个数。

## 说明/提示

$2\leq n\leq 10^5$


第一个样例中，当$k=1$时，所有的点都连通；当$k=4$时，只有$(4,6)$和$(5,6)$两条边连通，所以连通块个数为4。

第二个样例中，当$k=3$时，节点1、4、5构成一个连通块，其余两个节点分别为一个连通块。

## 样例 #1

### 输入

```
6
1 2
1 3
2 4
2 5
3 6```

### 输出

```
1 1 2 4 6 6```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
3 5```

### 输出

```
1 1 3 5 5```

# 题解

## 作者：lihongqian__int128 (赞：12)

# CF1805D A Wide, Wide Graph题解
一道思维题。

若一个点与其他点之间没有连线，则称其为孤点。

则会有以下几条信息：

1. 若点 $x$ 到最远的点的距离 $<k$，说明 $x$ 孤点；

2. 点 $x$ 到树的直径的两个端点的较大值一定为最远距离；

3. 若点 $x$ 到直径端点的距离 $\ge k$，则 $x$ 与端点共联通块；

4. 因此，每一个点要么单独成联通块，要么与直径端点共联通块；

所以，我们处理出树的直径的两个端点与每个点到这两个端点的距离，最后统计答案即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 5e5 + 5 ;
int n , u , v , w , x , y , dis , dis1[N] , dis2[N] , s[N] ;
vector <int> g[N] ;
bool vis[N] ;
void dfs(int cur , int cnt)
{
	if(cnt > dis)	x = cur , dis = cnt ;
	for(int to : g[cur])
	{
		if(vis[to])	continue ;
		vis[to] = 1 ;
		dfs(to , cnt + 1) ;
	}
	return ;
}
void dfs2(int cur , int cnt)
{
	if(cnt > dis)	y = cur , dis = cnt ;
	for(int to : g[cur])
	{
		if(vis[to])	continue ;
		vis[to] = 1 ;
		dis1[to] = cnt + 1 ;
		dfs2(to , cnt + 1) ;
	}
	return ;
}
void dfs3(int cur , int cnt)
{
	for(int to : g[cur])
	{
		if(vis[to])	continue ;
		vis[to] = 1 ;
		dis2[to] = cnt + 1 ;
		dfs3(to , cnt + 1) ;
	}
	return ;
}
int main()
{
	cin >> n ;
	for(int i = 1 ; i < n ; i++)
	{
		cin >> u >> v ;
		g[u].push_back(v) ;
		g[v].push_back(u) ;
	}
	vis[1] = 1 ;
	dfs(1 , 0) ;//找出树的直径的第1个端点
	memset(vis , 0 , sizeof vis) ;
	vis[x] = 1 ;
	dis = 0 ;
	dfs2(x , 0) ;//找出树的直径的第2个端点，并维护每个点到树的直径的第1个端点的距离
	memset(vis , 0 , sizeof vis) ;
	vis[y] = 1 ;
	dfs3(y , 0) ;//维护每个点到树的直径的第2个端点的距离
	for(int i = 1 ; i <= n ; i++)	if(i != y)	s[max(dis1[i] , dis2[i]) + 1]++ ;//处理
	s[0] = 1 ;
	for(int i = 1 ; i <= n ; i++)	s[i] += s[i - 1] , cout << s[i] << ' ' ;//输出答案
	return 0 ;
}
```

---

## 作者：六楼溜刘 (赞：12)

## 题意
- 给你一棵有 $n$ 个结点的树，定义 $G_k$ 为将在原树中所有距离大于等于 $k$ 的点对间连一条无向边所构成的无向图（距离定义为简单路径中边的数量）。
- 对于所有 $1 \le k \le n$，求 $G_k$ 中连通块的数量。
- $2 \le n \le 10^5$

## 题解

首先我们思考一下若 $G_k$ 是一个连通块，最大的 $k$ 是多少。

由于这道题需要距离大于等于 $k$，我们考虑往直径方面想。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/fbluj03j.png)

以这张图举例（在此图中加粗的那条就是直径），令直径长度为 $d$，容易发现，$G_k$ 为连通块当且仅当 $k \le \left\lceil\frac{d}{2}\right\rceil$ 自己推一下 $d$ 为奇数的情况就知道为什么上取整了）。

遗憾的是，这个结论本身并没有什么用，但我们再思考一个问题：为什么 $k \le \left\lceil\frac{d}{2}\right\rceil$ 时它就是一个连通块。

我们发现此时所有点和直径两端点中某一个的距离都大于等于 $k$（包括一个端点与另一个的距离）。为方便叙述，我们暂定点 $i$ 与直径两端点的距离中较大的一个为 $D_i$。容易发现，所有 $D_i \le k$ 的点都在 $G_{k+1}$ 中不与其他点连通。另外，根据直径的性质可知，$D_i$ 应是由 $i$ 开始的最长的一条路径，也能证明这个结论。

这个性质就很有用了，显然，$G_1=1$，而我们便可以用这个性质由 $G_k$ 在 $O(1)$ 的时间内算出 $G_{k+1}$（预处理每个 $D$ 对应的节点数），那么这道题就做完了。预处理直径与距离复杂度 $O(n)$，最后推答案复杂度也是 $O(n)$，完全能通过此题。

## code
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#include<stack>
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define pbk(a) emplace_back(a)
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=1e5+5,inf=0x3f3f3f3f;
int n,cntt[N],rt,dpt[N],dpt1[N];
vector<int> e[N];
void dfs(int x,int fa){//用来求直径的 dfs。
	dpt[x]=dpt[fa]+1;
	if(dpt[x]>dpt[rt]) rt=x;
	for(auto i:e[x]){
		if(i==fa) continue;
		dfs(i,x);
	}
}
void dfs1(int x,int fa){//用来求和另一个端点的距离的 dfs。
	dpt1[x]=dpt1[fa]+1;
	for(auto i:e[x]){
		if(i==fa) continue;
		dfs1(i,x);
	}
}
signed main(){
	n=read();
	forup(i,1,n-1){
		int u=read(),v=read();
		e[u].pbk(v);e[v].pbk(u);
	}
	dfs(1,0);
	dfs(rt,0);//两次 dfs 求直径。
	dfs1(rt,0);//此时 rt 是另一个端点。
	forup(i,1,n){//预处理数量。
		if(i!=rt) cntt[max(dpt[i],dpt1[i])-1]++;
	}
	int ans=1;
	forup(i,1,n){
		ans+=cntt[i-1];
		printf("%d ",ans);//输出答案。
	}
}


```


---

## 作者：Xy_top (赞：8)

一道显然的诈骗题。

边数一定会很多，我们要减少这个数量。

每个点之和离他最远的点连一条边就行了，如果有一条边低于阀值了，那么答案减一。

有一个 OI 常用结论：树上任意一点，离他最远的点一定是直径两端的点之一。所以倍增一下就好了，敲了巨长时间。

时空复杂度为 $O(n\log n)$。

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int n, ret, ma;
int a, b, f[100005][17], dep[100005];
vector <int> v[100005];
int tt[100005];
void dfs (int x, int y, int f){
	if (y > ma) {
		ret = x;
		ma = y;
	}
	for (int i = 0; i < v[x].size (); i ++) {
		if (v[x][i] != f) dfs (v[x][i], y + 1, x);
	}
}
void dfs1 (int x, int y) {
	dep[x] = dep[y] + 1;
	f[x][0] = y;
	for (int i = 0; i < v[x].size (); i ++) {
		if (v[x][i] != y) dfs1 (v[x][i], x);
	}
}
int dis (int x, int y) {
	int tx = x, ty = y;
	if (dep[x] < dep[y]) swap (x, y);
	if (dep[x] != dep[y]) {
		for (int i = 16; i >= 0; i --) {
			if (dep[f[x][i] ] >= dep[y]) x = f[x][i];
		}
	}
	if (x == y) return dep[tx] + dep[ty] - 2 * dep[x];
	for (int i = 16; i >= 0; i --) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return dep[tx] + dep[ty] - 2 * dep[f[x][0] ];
}
void query (int x) {
	if (dis (x, a) >= dis (x, b) ) tt[x] = dis (x, a);
	else tt[x] = dis (x, b);
}
int main () {
	cin >> n;
	int x, y;
	for (int i = 1; i < n; i ++) {
		cin >> x >> y;
		v[x].push_back (y);
		v[y].push_back (x);
	}
	dfs (1, 0, 0);
	a = ret, ma = 0;
	dfs (ret, 0, 0);
	b = ret;
	dfs1 (1, 0);
	for (int j = 1; j <= 16; j ++) {
		for (int i = 1; i <= n; i ++) f[i][j] = f[f[i][j - 1] ][j - 1];
	}
	for (int i = 1; i <= n; i ++) query (i);
	sort (tt + 1, tt + n + 1);
	int l = 1;
	for (int i = 1; i <= n; i ++) {
		while (l < n && tt[l] < i) ++ l;
		cout << l << " ";
	}
	return 0;
}
```


---

## 作者：Demeanor_Roy (赞：4)

- [原题链接](https://www.luogu.com.cn/problem/CF1805D)

------------

挺不错的题。

- **断言一：仅考虑连通性，只需保留每个点与其相距最远点连边的可能性。**

证明：对于任意点 $u$，若其与点 $v$ 可连边但点 $v$ 不是距其最远的点。若距其最远的点 $w$ 不在 $v$ 这棵子树内，显然 $w$ 也是离 $v$ 最远的点， $u$ 和 $v$ 依旧会连通；否则 $w$ 一定在 $v$ 这棵子树内，此时离 $v$ 最远的点一定为点 $u$。故此边可以不连。

- **断言二：对于树上任意一点，距其最远的点一定是任意一直径某端点。**

典，证明略。

- **断言三：不考虑直径两端点所连重复边，生成图又构成了一棵树。**

这是因为一共 $n-1$ 条边，每个点都有边与之相连。

综上所述，从小到大枚举 $k$，由生成树所删边数即可推出连通块数。时间复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,x,y,mx,dis[N],cnt[N];
int h[N],e[N<<1],ne[N<<1],idx;
bool ex[N];
inline void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
inline void dfs(int u,int val)
{
	dis[u]=-1;
	for(int i=h[u];~i;i=ne[i]) if(~dis[e[i]]) dfs(e[i],val+1);
	if(val>mx) mx=val,x=u;
}
inline void Dfs(int u,int val)
{
	dis[u]=0;
	for(int i=h[u];~i;i=ne[i]) if(dis[e[i]]==-1) Dfs(e[i],val+1);
	if(val>mx) mx=val,y=u;
	if(val>dis[u]) dis[u]=val;
}
inline void DFS(int u,int val)
{
	ex[u]=true;
	for(int i=h[u];~i;i=ne[i]) if(!ex[e[i]]) DFS(e[i],val+1);
	if(val>dis[u]) dis[u]=val;
}
int main()
{
	memset(h,-1,sizeof h);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);Dfs(x,mx=0);DFS(y,0);
	for(int i=1;i<=n;i++) cnt[dis[i]]++;
	int ans=1+cnt[0];
	for(int i=1;i<=n;i++) printf("%d ",min(n,ans)),ans+=cnt[i];
	return 0;
}
```


---

## 作者：RainySoul (赞：1)

只有当一个点没有任何一条连边的时候它才会被孤立出来成为一个单独的连通块。而如果距离它最远的点和它都无法连边了，一定没有其他点可以和它连边了。

我们知道，在一棵树上拎出来一个点，**距离它最远的点一定是直径的两个端点之一**。

预处理出直径的两个端点与这两个端点到每个点的距离，然后对每个点判断它什么时候被第一次孤立出来，此后 $k$ 不断增大，它一定是一直被孤立着的。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500010;
int n,rt1,rt2,maxn,dep[N],dis1[N],dis2[N],ans[N];
vector<int> e[N];
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar(); 
    }
    return x*f;
}
void dfs1(int now,int fa){
    dep[now]=dep[fa]+1;
    for(int i=0;i<e[now].size();i++){
        int to=e[now][i];
        if(to!=fa)dfs1(to,now);
    }
}
void dfs2(int now,int fa){
    dis1[now]=dis1[fa]+1;
    for(int i=0;i<e[now].size();i++){
        int to=e[now][i];
        if(to!=fa)dfs2(to,now);
    }
}
void dfs3(int now,int fa){
    dis2[now]=dis2[fa]+1;
    for(int i=0;i<e[now].size();i++){
        int to=e[now][i];
        if(to!=fa)dfs3(to,now);
    }
}
int main(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++)
        if(dep[i]>maxn)maxn=dep[i],rt1=i;
    dis1[0]=dis2[0]=-1;
    dfs2(rt1,0);
    maxn=0;
    for(int i=1;i<=n;i++)
        if(dis1[i]>maxn)maxn=dis1[i],rt2=i;
    dfs3(rt2,0);
    for(int i=1;i<=n;i++)ans[max(dis1[i],dis2[i])+1]++;
    ans[0]=1;
    for(int i=1;i<=n;i++){
        ans[i]+=ans[i-1];
        cout<<min(ans[i],n)<<' ';
    }
    return 0;
}
```

---

## 作者：Kketchup (赞：1)

## CF1805D A Wide, Wide Graph 题解

[题目传送门](https://codeforces.com/problemset/problem/1805/D)

- 树的直径

### 【题目描述】

给定一棵 $n$（$2\leq n\leq 10^5$）个节点的无根树。

给定参数 $k$，对于每个 $k$（$1\leq k \leq n$），定义无向图 $G_k$，图中有 $n$ 个节点，点 $u,v$ 有边当且仅当树上两个节点的距离至少为 $k$。

对于 $k\in[1,n]$，计算 $G_k$ 的连通块个数。

### 【题目解析】

手玩样例可以发现，当 $k$ 大于直径时，$G_k$ 中没有边，连通块数量为 $n$。

这启示我们，直径的两个端点在 $k$ 小于等于直径时依旧联通。

可以发现，当一个点 $x$ 到最远点的距离小于 $k$ 时，这个点变成孤点。而树上最远点一定是直径两端点中的一个，所以一个点变成孤点当且仅当其到两直径端点距离最大值小于 $k$。在此之前，这个点一定与直径端点联通。

记 $ans_i$ 表示 $k=i$ 时新增多少点变成孤点，前缀和统计即可。时间复杂度 $O(n)$。

注意 $ans_0=1$，表示一开始有一个连通块；$i$ 大于直径时 $ans_i=n$。

附上超短好写代码，两次 dfs 找直径端点后再一次 dfs 统计每个点到第二个端点的距离。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N=1e5+10;
int n;
vector<int> e[N];
int d[N][2],d2[N],dis,rt;
int ans[N];
void dfs(int u,int fa,int p){
    d[u][p]=d[fa][p]+1;
    if(d[u][p]>d[rt][p]) rt=u,dis=d[u][p]; 
    for(int v:e[u]) if(v!=fa) dfs(v,u,p);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1,x,y;i<n;++i){
        cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    d[0][0]=d[0][1]=-1;
    dfs(1,0,0),dfs(rt,0,0),dfs(rt,0,1);
    for(int i=1;i<=n;++i) ans[max(d[i][0],d[i][1])+1]++;
    ans[0]=1;
    for(int i=1;i<=n;++i){
        ans[i]+=ans[i-1];
        if(i>dis) cout<<n<<" ";
        else cout<<ans[i]<<" ";
    }
    return 0;
}
```

---

## 作者：wxzzzz (赞：1)

### 思路

两个性质：

1. 若 $x$ 到所有点的距离都 $\le k$，那么 $x$ 为一个联通块。

1. 设树的直径端点为 $pl,pr$，若 $\max\big((\operatorname{dis}(x,pl),\operatorname{dis}(x,pr)\big)\le k$，则 $x$ 到所有点的距离都 $\le k$。

因此，所有满足 $\max\big((\operatorname{dis}(x,pl),\operatorname{dis}(x,pr)\big)<k$ 的点都单独为一个联通块，其余点都和 $pl$ 或 $pr$ 连了边，共一个联通块。

故 $ans_i=\min\bigg(\displaystyle\sum_{j=1}^n [\max\big((\operatorname{dis}(x,pl),\operatorname{dis}(x,pr)\big)<k]+1,n\bigg)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ts, pl, pr, pos, idx, len, w[500005], s[500005], d[500005], f[500005], v[500005], h[500005], e[500005],
    ne[500005], to[500005], dfn[500005], son[500005], top[500005];
void add(int x, int y) {
    v[++idx] = y, ne[idx] = h[x], h[x] = idx;
}
void dfs1(int x) {
    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == f[x])
            continue;

        f[y] = x, d[y] = d[x] + 1;
        dfs1(y), s[x] += s[y];

        if (s[y] > s[son[x]])
            son[x] = y;
    }
}
void dfs2(int x, int tp) {
    dfn[x] = ++ts, to[ts] = x, top[x] = tp;

    if (son[x])
        dfs2(son[x], tp);

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y != f[x] && y != son[x])
            dfs2(y, y);
    }
}
int LCA(int x, int y) {
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (d[fx] >= d[fy])
            x = f[fx], fx = top[x];
        else
            y = f[fy], fy = top[y];
    }

    if (d[x] > d[y])
        swap(x, y);

    return x;
}
void dfs(int x, int F, int dis) {
    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == F)
            continue;

        if (len < dis + 1)
            len = dis + 1, pos = y;

        dfs(y, x, dis + 1);
    }
}
int dis(int x, int y) {
    return d[x] + d[y] - d[LCA(x, y)] * 2;
}
int get(int x) {
    int l = 1, r = n, mid, ret = 0;

    while (l <= r) {
        mid = l + r >> 1;

        if (w[mid] < x)
            ret = mid, l = mid + 1;
        else
            r = mid - 1;
    }

    return ret;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n;

    for (int i = 1; i <= n; i++)
        s[i] = 1;

    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    dfs1(1), dfs2(1, 1);
    dfs(1, 0, 0), pl = pos, len = 0;
    dfs(pos, 0, 0), pr = pos;

    for (int i = 1; i <= n; i++)
        w[i] = max(dis(i, pl), dis(i, pr));

    sort(w + 1, w + n + 1);

    for (int i = 1; i <= n; i++)
        cout << min(get(i) + 1, n) << ' ';

    return 0;
}
```

---

## 作者：Cheerimy (赞：1)

## 题意解释
* 给你一棵有 $n$ 个结点的树，定义 $G_k$ 为树中所有边数大于等于 $k$ 的点；
* 对于所有的 $1 \le k \le n$，求 $G_k$ 中连通块的数量 $(2 \le n \le 10^5)$；

## 题目思路
对于每个点，只需要保存 $k$ 最大的连边可能性；

其对应的点又一定是树的直径的一端；

注：其他的连边均可以省略；

综合上面结论，我们发现对于每个点与直径的端点中任意一个的距离一定大于等于 $k$，所以 $G_k$ 可以通过 $G_{k-1}$ 推得结果；
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<long long> num[100010];
long long big,ans[100010],xuma[100010],xumb[100010];
void cmp(long long x,long long last)
{
	xuma[x]=xuma[last]+1;
	if(xuma[x]>xuma[big])
	{
		big=x;
	}
	for(long long i=num[x].size()-1;i>=0;i--)
	{
		if(num[x][i]==last)continue;
		cmp(num[x][i],x);
	}
	return;
}
void cmp_ans(long long x,long long last)
{
	xumb[x]=xumb[last]+1;
	for(long long i=num[x].size()-1;i>=0;i--)
	{
		if(num[x][i]==last)continue;
		cmp_ans(num[x][i],x);
	}
	return;
}
int main()
{
	long long n;
	cin>>n;
	for(long long i=1;i<n;i++)
	{
		long long u,v;
		cin>>u>>v;
		num[u].push_back(v);
		num[v].push_back(u);
	}
	cmp(1,0);
	cmp(big,0);
	cmp_ans(big,0);
	for(long long i=1;i<=n;i++)
		if(i!=big)
			ans[max(xuma[i],xumb[i])]++;
	long long sum=0;
	for(long long i=1;i<=n;i++)
	{
		sum+=ans[i];
		cout<<sum+1<<" ";
	}
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### solution

模拟赛题，场切了。

找到一条直径，最后断开的肯定为直径两端的点。

考虑长度为 $k$ 是另外的点是否与直径所在的集合联通，助理出树上每个点到选出的直径端点的距离的最大值，距离 $k$ 大于这个距离时，这个点就从大块上分离成为一个新连通块，随便做就行。

### code

```cpp
int n;

int head[maxn],tot;
struct edge{
	int to,nxt,w;
}e[maxn<<2];

void add(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	e[tot].w=1;
	head[u]=tot;
}

int dis[maxn];

int dfs1(int u,int f,int w){
	dis[u]=dis[f]+w;
	int ans=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		int tmp=dfs1(v,u,e[i].w);
		if(dis[tmp]>dis[ans]){
			ans=tmp;
		}
	}
	return ans;
}

void dfs2(int u,int fa,int w){
	dis[u]=max(dis[u],w);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs2(v,u,w+e[i].w);
		}
	}
}

int mp[maxn];

void solve(){
	n=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add(u,v);
		add(v,u); 
	}
	int s=dfs1(1,0,0);
	int t=dfs1(s,0,0);
	memset(dis,-0x3f,sizeof dis);
	dfs2(s,0,0);
	dfs2(t,0,0);
	for(int i=1;i<=n;i++){
		mp[dis[i]]++;
	}
	int res=1;
	for(int i=1;i<=n;i++){
		write(res),putchar(' ');
		res=min(res+mp[i],n);
	}
	return ;
}
```

---

## 作者：bluewindde (赞：0)

对于点 $u$，其一定被到它距离最远的点 $v$ 并入连通块。

考虑找到这个最远距离。

类比 CF2033G，钦定点 $1$ 作为根，设 $g_u$ 表示 $u$ 子树内的最大深度，$h_u$ 表示 $u$ 子树内的次大深度。规定 $g_u$ 和 $h_u$ 不能处于 $u$ 的同一棵子树内。转移是容易的，计算答案也是容易的。

处理出 $g$ 和 $h$ 后再进行一次 dfs 即可处理出最远距离。

然后差分即可。

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> vec[500005];

int g[500005];
int h[500005];
static inline int calc(int u, int v) {
    if (g[u] == g[v])
        return h[u];
    return g[u];
}

int f[500005];
int w[500005];
int c[500005];
int dep[500005];
static inline void dfs(int u, int fa) {
    f[u] = fa;
    g[u] = dep[u] = dep[fa] + 1;
    for (auto v : vec[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
        if (g[v] >= g[u]) {
            h[u] = g[u];
            g[u] = g[v];
        } else if (g[v] > h[u])
            h[u] = g[v];
    }
}
static inline void dfs2(int u, int val) {
    c[u] = max(val, g[u] - dep[u]);
    for (auto v : vec[u]) {
        if (v == f[u])
            continue;
        dfs2(v, max(val, calc(u, v) - dep[u]) + 1);
    }
}

int fin[500005];

static inline void solve() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i)
        ++fin[c[i]];
    for (int i = n; i; --i)
        fin[i] += fin[i + 1];
    for (int i = 1; i <= n; ++i)
        if (!fin[i])
            cout << n << ' ';
        else
            cout << n - fin[i] + 1 << ' ';
}

signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

## 作者：postpone (赞：0)

题面乍一看好像没什么头绪，不妨先按题意模拟一下过程。

刚开始 $k = 1$，$G_k$ 里任意两点之间都相连，此时整个图就是一个 SCC。

$k$ 增大到 $2$，长度为 $1$ 的边断了，剩下的边还保留着。这时候可能有一些点脱离“大部队”，SCC 数量可能会增加。$k$ 不断增大，一直到 $k = n$ 时，显然所有边都断了，每个点都是孤立的 SCC。

可以看出，$k$ 从 $1$ 到 $n$ 的整个过程，整个图逐渐在断边，有越来越多的点脱离“大部队”，SCC 的数量逐渐增加，直到每个点都是一个 SCC。

现在假如我们知道这个“大部队”是什么，对于每个点，它是怎么脱离“大部队”的呢？可以发现，当 $k$ 比它到“大部队”的最远距离还要大，那么这个点到“大部队”的所有边全断，也就脱离出来了。

题目给出的是一棵树，联想到一条和最远距离相关的性质：对于树上任意一点，其余点中离这个点距离最远的点，一定是树的直径的端点。

由此可以发现，这个“大部队”其实就是树的一条直径（可用归纳法证明），那么这题就做出来了：找到一条直径的两端，和其余点到两个端点距离的最大值，当 $k$ 大于这个值，SCC 数量增加 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> adj;
vector<int> dep1, dep2;

void dfs1(int u, int fa) {
    for (auto v : adj[u]) {
        if (v != fa) {
            dep1[v] = dep1[u] + 1;
            dfs1(v, u);
        }
    }
}

void dfs2(int u, int fa) {
    for (auto v : adj[u]) {
        if (v != fa) {
            dep2[v] = dep2[u] + 1;
            dfs2(v, u);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    cin >> n;

    adj.assign(n, {});
    dep1.resize(n, 0);
    dep2.resize(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(0, -1);
    int U = max_element(dep1.begin(), dep1.end()) - dep1.begin();

    dep1[U] = 0;
    dfs1(U, -1);

    int V = max_element(dep1.begin(), dep1.end()) - dep1.begin();
    dfs2(V, -1);

    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        if (i == U) {
            continue;
        }
        int d = std::max(dep1[i], dep2[i]);
        res[d]++;
    }

    res[0]++;
    for (int i = 1; i < n; i++) {
        res[i] += res[i - 1];
    }
    for (auto i : res) {
        cout << i << " ";
    }

    return 0;
}
```

[提交记录](https://codeforces.com/contest/1805/submission/281537789)

---

## 作者：kimi0705 (赞：0)

### 题解：CF1805D A Wide, Wide Graph
关键词：**树的直径**。

众所周知，$a_i=\max\{d(i,x),d(i,y)\}$，其中 $d(x,y)$ 指树上 $x,$ 和 $y$ 的距离， $x$ 和 $y$ 分别是树直径的两端，$a_i$ 为点 $i$ 到最远的点的距离。

- 当 $k\le n-1$，$x$ 和 $y$ 相连，所在联通块记为联通块 $L$。
- 当 $a_i\ge k$ 时，$a_i$ 与 $L$ 相连。
- 当 $a_i<l$ 时，$a_i$ 独自为一个联通块。

综上，只需判断有多少个大小为 $1$ 的连通块即可。

---

## 作者：COsm0s (赞：0)

贪心地思考，既然需要边 $\geq k$，且要让 $k$ 尽量大的情况下，显然每个点需要连其距离最远的点。

一个常用树上结论：树上任意一点 $g$，一定有 $g$ 的最远点为树的直径的两端点之一。

那么也就是说任一点都和直径两端之一相连，且两端点之间也有连边，那么原树变成了新一棵树（除去直径间边的其中一条）。

那么枚举 $k$，预处理生成树删边数量即可。

复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define REP(i, a, b) for(int i = (a); i <= (b); ++ i)
#define DOW(i, a, b) for(int i = (a); i >= (b); -- i)
using namespace std;
namespace COsm0s {
	const int N = 2e5 + 5, mod = 998244353;
	int n, rt, dis[N], dus[N], x, y, cnt[N];
	vector<int> edge[N];
	void dfs(int u, int fa) {
		dis[u] = dis[fa] + 1;
		if (dis[u] > dis[rt]) rt = u;
		for (auto& v : edge[u]) {
			if (v == fa) continue;
			dfs(v, u);
		}
	}
	void DFS(int u, int fa) {
		dus[u] = dus[fa] + 1;
		for (auto& v : edge[u]) {
			if (v == fa) continue;
			DFS(v, u);
		}
	}
	int main() {
		cin >> n;
		REP(i, 2, n) cin >> x >> y, edge[x].emplace_back(y), edge[y].emplace_back(x);
		dfs(1, 0), dfs(rt, 0), DFS(rt, 0);
		REP(i, 1, n) if(i != rt) cnt[max(dis[i], dus[i])] ++;
		int ans = 1;
		REP(i, 1, n) cout << (ans += cnt[i]) << ' ';
		cout << '\n';
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) COsm0s::main();
	return 0;
}
```


---

## 作者：LYY_yyyy (赞：0)

有一个不太好想的结论：每个点只有与自己最远点的连边是有贡献的。证明倒是比较简单。我们有一个经典结论，就是每个点的最远点一定是直径的一个端点。假设现在有两个点 $A$ 和 $B$。$A$ 和 $B$ 都为直径两个端点时正确性显然。假设 $A$ 和 $B$ 不同时在直径上，若他们最远点是同一个端点，设这个点为 $C$。那么由于 $C$ 是最远点，所以 $AC \ge AB$，$BC \ge AB$，故不连 $AB$ 不影响连通性。若他们最远点为两个不同的端点，设为 $C$ 和 $D$。我们可以发现 $AC,CD,DB$ 均大于等于 $AB$。于是 $AB$ 同样不影响连通性，原结论得证。接下来就很好做了：处理出直径的两个端点，之后从这两个端点进行DFS，将两个端点的 $dis$ 取一个 $\max$，就能处理出最远点。之后开一个桶记一下边权就行了。我们发现总共只有 $n-1$ 条边，因为直径会算两遍，直接特判删掉一遍就好了。所以每次删除一条边意味着多出来一个连通块，于是本题就做完了。时间复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;vector<int> g[100010];
int cnt[100010];int x,y; 
int dis[100010][2];int nowans=1;
void dfs(int now,int fa,int d,int use)
{
	dis[now][use]=d;
	for(auto to:g[now])
	{
		if(to==fa) continue;
		dfs(to,now,d+1,use);
	}
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;int u,v;for(int i=1;i<n;i++) cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs(1,0,0,0);for(int i=1;i<=n;i++) if(dis[i][0]>dis[x][0]) x=i;
	dfs(x,0,0,0);for(int i=1;i<=n;i++) if(dis[i][0]>dis[y][0]) y=i;
	dfs(y,0,0,1);for(int i=1;i<=n;i++) if(i!=x&&i!=y) cnt[max(dis[i][0],dis[i][1])]++;
	cnt[dis[y][0]]++;for(int i=1;i<=n;i++) nowans+=cnt[i-1],cout<<nowans<<" ";
	return 0;
}
```

---

