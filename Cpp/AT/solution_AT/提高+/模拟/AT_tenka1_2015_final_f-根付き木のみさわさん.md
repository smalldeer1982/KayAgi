# 根付き木のみさわさん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2015-final/tasks/tenka1_2015_final_f

高橋君の家の庭には、頂点 $ 1 $ を根とする一本の根付き木である、みさわさんが生えています。

$ i $ 日目の朝、みさわさんは $ M_i $ 個の頂点 $ v_{i,1},\ …,\ v_{i,M_i} $ に実をつけます。

しかし、同じ日の晩には鳥がやってきて、残っているすべての実を食べてしまいます。

高橋君は、一日に一回、みさわさんの頂点をひとつ選んでゆさぶることができます。

頂点 $ w $ をゆさぶると、$ w $ の子孫 ($ w $ 自身も含む) である頂点についている実をすべて得られます。

高橋君は、 $ i $ 日目に、みさわさんから $ K_i $ 個以上の実を取りたいです。

高いところが好きな高橋君のために、ゆさぶることで $ K_i $ 個以上の実を得ることができる頂点のうち、根からもっとも遠いものをもとめ、その根からの距離を教えてください。

ただし、各頂点に対し、根からの距離とは、根からその頂点への唯一の単純なパスに含まれる辺の数を表します。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1≦N≦100 $ を満たすデータセットに正解した場合は $ 20 $ 点が得られる。
- 全てのデータセットに正解した場合はさらに $ 110 $ 点が得られる。合計で $ 130 $ 点となる。

### Sample Explanation 1

\- $ 1 $ つ目のクエリでは、みさわさんは $ 2 $ つの頂点 $ 4,5 $ に実をつけます。このうち $ 2 $ つの実を得られる頂点のうち、もっとも根から遠い頂点は $ 3 $ であり、この頂点の根からの距離は $ 2 $ です。 - $ 2 $ つ目のクエリでは、みさわさんは $ 1 $ つの頂点 $ 1 $ に実をつけます。このうち $ 1 $ つの実を得られる頂点のうち、もっとも根から遠い頂点は $ 1 $ であり、この頂点の根からの距離は $ 0 $ です。 - $ 3 $ つ目のクエリでは、みさわさんは $ 2 $ つの頂点 $ 2,1 $ に実をつけます。このうち $ 1 $ つの実を得られる頂点のうち、もっとも根から遠い頂点は $ 2 $ であり、この頂点の根からの距離は $ 1 $ です。

## 样例 #1

### 输入

```
5
3 5
1 2
2 3
3 4
3
2 2
4 5
1 1
1
2 1
2 1```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
10
4 10
2 3
1 4
1 2
3 5
1 8
4 6
8 9
2 7
5
10 4
9 7 3 1 5 10 4 6 2 8
2 2
8 2
10 9
6 2 10 4 7 1 5 8 9 3
2 2
10 2
5 1
1 7 2 3 9```

### 输出

```
1
0
0
0
2```

## 样例 #3

### 输入

```
15
3 4
4 6
11 13
2 6
4 8
7 13
4 7
8 9
1 8
5 9
8 15
9 14
8 12
9 10
5
14 5
5 1 13 8 14 3 2 9 7 10 11 4 12 15
5 5
6 8 12 2 11
1 1
12
12 8
2 13 1 10 12 3 8 9 6 4 7 15
10 8
8 14 13 12 15 10 7 5 2 4```

### 输出

```
2
1
2
1
1```

# 题解

## 作者：sunkuangzheng (赞：4)

看着就很像虚树的题。下称点集 $M$ 内的点为关键点。首先容易发现，只有关键点和若干个关键点的 LCA 是有用的，其它点一定更劣。考虑把点按 dfn 序排序，我们有结论相邻点的 LCA 包括了任意关键点集的 LCA，根据 dfn 序性质证明不难。

考虑维护每个点子树里关键点的数量，可以大力树剖路径加，但没必要。直接用树状数组做单点改子树求和即可。时间复杂度 $\mathcal O((n+m) \log n)$。

注意多组询问清空要采用抵消贡献的办法，不能暴力 memset。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 05.01.2024 09:00:39
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,st[N][22],t[N],re,u,v,dfn[N],dep[N],siz[N],tot,m,k,a[N],x;vector<int> g[N];
int cmp(int u,int v){return dfn[u] < dfn[v] ? u : v;}
void upd(int x,int p){for(;x <= n;x += x & -x) t[x] += p;}
int qry(int x){for(re = 0;x;x -= x & -x) re += t[x];return re;}
void dfs(int u,int f){
    st[dfn[u] = ++tot][0] = f,dep[u] = dep[f] + 1,siz[u] = 1;
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}int lca(int u,int v){
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
    int k = __lg(v - u);
    return cmp(st[u+1][k],st[v-(1<<k)+1][k]);
}void los(){
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);dfs(1,0);
    for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
        st[i][j] = cmp(st[i][j-1],st[i+(1<<j-1)][j-1]);
    for(cin >> m;m --;){
        cin >> k >> x;vector<int> acc;int ans = 0;
        for(int i = 1;i <= k;i ++) cin >> a[i],upd(dfn[a[i]],1),acc.push_back(a[i]);
        sort(a+1,a+k+1,[&](int x,int y){return dfn[x] < dfn[y];});
        for(int i = 1;i < k;i ++) acc.push_back(lca(a[i],a[i+1]));
        for(int i : acc) if(qry(dfn[i] + siz[i] - 1) - qry(dfn[i] - 1) >= x) ans = max(ans,dep[i]);
        cout << ans - 1 << "\n";
        for(int i = 1;i <= k;i ++) upd(dfn[a[i]],-1);
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：george0929 (赞：2)

虚树？树剖？不用那么麻烦。

其实只需要会二维数点，就可以解决本题。

首先我们选出是一颗子树，一共只有 $n$ 种选法，考虑转 DFS 序，那么选出的子树可以看作一个区间，将第 $i$ 个区间的信息记作 $(x_i,y_i,d_i)$，表示子树 DFS 序的区间左右端点和子树深度。

对于询问，把每个点转成 DFS 序，问题转化为选一个区间 $i$，覆盖至少 $k$ 个点，最大化区间的 $d_i$。

容易发现，覆盖到的点一定是连续的，因此对于每个询问，将点集按 DFS 序排序，那么覆盖其中 $k$ 个点就有 $m-k+1$ 种情况，分别计算这些情况并取最大值即可。

对于要覆盖的 $k$ 个点 $qr_1,qr_2,\cdots qr_k$，其中 $qr_1<qr_2<\cdots <qr_k$，那么我们选出的区间 $i$ 要满足 $(x_i\le qr_1)\wedge (y_i\ge qr_k)$，在此基础上最大化 $d_i$。这是一个经典的二维数点问题，可以用离线 + 树状数组解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
vector<int> V[100005];
int dfn[100005],out[100005],dep[100005],tot;
void dfs(int u,int fa){
	dfn[u]=++tot;
	for(int v:V[u]){
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
	out[u]=tot;
}
struct point{
	int x,y,d;
}a[100005];
int qr[100005];
struct qry{
	int x,y,id;
}l[100005];int cnt;
struct _bit{
	int c[100005];
	void add(int p,int v){
		for(int i=p;i<=n;i+=i&-i) c[i]=max(c[i],v);
	}
	int mx(int p){
		int res=0;
		for(int i=p;i>=1;i-=i&-i) res=max(res,c[i]);
		return res;
	}
}bit;
bool cmpp(point x,point y){
	return x.y>y.y;
}
bool cmpq(qry x,qry y){
	return x.y>y.y;
}
int ans[100005];
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		a[i]={dfn[i],out[i],dep[i]};
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int m,k;
		cin>>m>>k;
		for(int j=1;j<=m;j++){
			cin>>qr[j];
			qr[j]=dfn[qr[j]];
		}
		sort(qr+1,qr+1+m);
		for(int j=1;j+k-1<=m;j++){//分别考虑 m-k+1 种情况。
			l[++cnt]={qr[j],qr[j+k-1],i};
		}
	}
	sort(a+1,a+1+n,cmpp);
	sort(l+1,l+1+cnt,cmpq);
	int pos=1;
	for(int i=1;i<=cnt;i++){//二维数点。
		while(pos<=n&&a[pos].y>=l[i].y){
			bit.add(a[pos].x,a[pos].d);
			pos++;
		}
		ans[l[i].id]=max(ans[l[i].id],bit.mx(l[i].x));
	}
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

一眼题。

对所有关键点建虚树，定义 $siz_x$ 表示点 $x$ 在虚树上的子树中关键点的数量。那么我们就需要找到深度最大的一个 $x$，使得 $siz_x \ge k_i$。直接 DFS 一遍就行了，复杂度是 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=4e5+10;
int n,q;
int ne[N],e[N],h[N],idx;
int dfn[N],cnt;
int dep[N],f[N][25];
int k,m,a[N],b[N];
vector<int> v[N];
bool vis[N];
int Max,siz[N];

il bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
il void add(int a,int b){
	ne[++idx]=h[a],e[idx]=b,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,h[b]=idx;
}
il void dfs(int now,int fa){
	dfn[now]=++cnt;
	dep[now]=dep[fa]+1,f[now][0]=fa;
	for(re int i=1;i<25;++i) f[now][i]=f[f[now][i-1]][i-1];
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);
	}
	return ;
}
il int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re int i=24;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re int i=24;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
il void work(int now,int fa){
	siz[now]=vis[now];
	for(auto j:v[now])
		work(j,now),siz[now]+=siz[j];
	if(siz[now]>=k) Max=max(Max,dep[now]);
	return ;
}

il void solve(){
	n=rd;
	for(re int i=1;i<n;++i) add(rd,rd);
	dfs(1,0);
	q=rd;
	while(q--){
		m=rd,k=rd,Max=0;
		for(re int i=1;i<=m;++i) a[i]=rd,vis[a[i]]=1;
		sort(a+1,a+m+1,cmp);
		int cnt=0;
		b[++cnt]=1,b[++cnt]=a[1];
		for(re int i=2;i<=m;++i) b[++cnt]=lca(a[i],a[i-1]),b[++cnt]=a[i];
		sort(b+1,b+cnt+1,cmp),cnt=unique(b+1,b+cnt+1)-(b+1);
		for(re int i=1;i<=cnt;++i) v[b[i]].clear();
		for(re int i=2;i<=cnt;++i) v[lca(b[i-1],b[i])].push_back(b[i]);		
		work(1,0),printf("%lld\n",Max-1);
		for(re int i=1;i<=cnt;++i) vis[b[i]]=0;
		for(re int i=2;i<=cnt;++i) siz[lca(b[i-1],b[i])]=siz[b[i]]=0;
	}
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

## 作者：LEE114514 (赞：0)

## 思路

首先有一个结论，是用虚树证明的，也就是对于 $a_1,a_2,a_3,\cdots,a_n$ 这 $n$ 个树上的点，按照 dfn 排序后为 $b_1,b_2,b_3,\cdots,b_n$，那么这些点的 LCA 就是 $\operatorname{LCA}(b_1,b_n)$。

然后就问题就被简化成，子树内要至少存在 $k$ 个点，那就排序后搞一个长度为 $k$ 的滑动窗口取 LCA，最后取深度最大值。

## Code

```
#include <bits/stdc++.h>
using namespace std;
int n,q,u,v,m,k;
const int maxn=1e5+5;
int arr[maxn];
vector<int> G[maxn];
int dep[maxn],dfn[maxn],dfncnt;
int fa[maxn],sz[maxn],top[maxn],hson[maxn];
void dfs(int u,int f){
	dep[u]=dep[fa[u]=f]+1;
	sz[u]=1;
	for(int v:G[u]){
		if(v==f) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[hson[u]]) hson[u]=v;
	}
}
void dfs2(int u,int tp){
	dfn[u]=++dfncnt;
	top[u]=tp;
	if(hson[u]) dfs2(hson[u],tp);
	for(int v:G[u]){
		if(dfn[v]) continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i) scanf("%d%d",&u,&v),G[u].emplace_back(v),G[v].emplace_back(u);
	dfs(1,0);
	dfs2(1,1);
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&m,&k);
		for(int i=1;i<=m;++i) scanf("%d",arr+i);
		sort(arr+1,arr+m+1,[](int x,int y){return dfn[x]<dfn[y];});
		ans=0;
		for(int i=k;i<=m;++i) ans=max(ans,dep[LCA(arr[i-k+1],arr[i])]);
		printf("%d\n",ans-1);
	}
}
```

---

## 作者：AC_love (赞：0)

考虑暴力做法，设关键点权值为 $1$，其他点权值为 $0$，把整棵树 dfs 一遍，过程中记录权值大于等于 $k$ 的点的最大深度即可。

做一遍的复杂度是 $O(n)$，$q$ 次询问复杂度 $O(nq)$，太劣了，显然不行。

不难发现在 dfs 过程中搜了很多没用的点，我们考虑只保留有用的点来减少我们的搜索量。不难想到对关键点建虚树，然后直接在虚树上 dfs 即可。

虚树的具体建法是：先将所有关键点按照 dfn 排序，然后添加相邻点的 lca。最后虚树上的点就是所有关键点和所有添加进来的 lca。

为什么这么建虚树是对的？证明比较繁琐，感兴趣的可以去 OI-wiki 上看：[link](https://oi-wiki.org/graph/virtual-tree/#%E7%AC%AC%E4%B8%80%E7%A7%8D%E6%9E%84%E9%80%A0%E8%BF%87%E7%A8%8B%E4%BA%8C%E6%AC%A1%E6%8E%92%E5%BA%8F--lca-%E8%BF%9E%E8%BE%B9)

[code](https://atcoder.jp/contests/tenka1-2015-final/submissions/59049600)

---

