# Another Exercise on Graphs (Easy Version)

## 题目描述

这是该问题的简单版本。不同版本间的区别在于此版本对 $m$ 有额外约束。只有在你解决了该问题的所有版本后，才能进行 hack。

最近，"T-generation" 的导师需要筹备一场训练赛。他们发现缺少一道题目，且整场比赛中没有图论相关的问题，于是设计了如下题目。

给定一个包含 $n$ 个顶点和 $m$ 条边的连通带权无向图，图中无自环和重边。

处理 $q$ 次形如 $(a, b, k)$ 的查询：在从顶点 $a$ 到顶点 $b$ 的所有路径中，找出路径上边权的第 $k$ 小最大值$^{\dagger}$。

导师们认为这个问题非常有趣，但存在一个问题：他们不知道如何解决它。请帮助他们解决这个问题，因为距离比赛开始仅剩几小时。

$^{\dagger}$ 设 $w_1 \ge w_2 \ge \ldots \ge w_{h}$ 为某条路径中所有边权按非递增顺序排列后的结果。该路径边权的第 $k$ 大值即为 $w_{k}$。


## 说明/提示

在第一个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 3 \rightarrow 4$，该路径边权的第 $2$ 大值为 $1$。第二次查询的最优路径之一是 $2 \rightarrow 4 \rightarrow 3$，边权的第 $1$ 大值为 $2$。

在第二个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 6$，该路径边权的第 $3$ 大值为 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 4 2
1 2 2
2 4 2
1 3 4
3 4 1
1 4 2
2 3 1
6 7 3
1 2 10
2 3 3
3 4 9
4 5 2
5 6 1
2 4 10
4 6 10
1 6 3
1 6 2
2 4 1
11 17 10
1 4 5
1 3 19
1 2 10
3 2 13
4 5 1
4 6 11
3 5 9
3 6 18
2 7 17
5 8 15
5 10 8
6 9 4
7 10 20
7 8 16
8 11 3
9 11 6
10 11 14
3 11 1
3 11 3
1 11 1
1 11 4
1 11 3
8 2 2
10 4 1
3 9 2
3 9 1
6 7 3```

### 输出

```
1 2
2 9 9
11 3 11 1 3 10 8 4 11 4```

# 题解

## 作者：DerrickLo (赞：3)

### E1

先将所有边按照边权排序，考虑在询问时二分答案。

设现在二分到了第 $x$ 条边，那么我们将边权 $\le w_{x}$ 的边的边权改为 $0$，$>w_x$ 的改为 $1$，那么我们只需要判断此时 $a$ 到 $b$ 的最短路是否 $<k$ 即可。

那么考虑预处理出 $f_{i,j,k}$ 表示若边权 $\le w_i$ 的边权改为 $0$，其余边的边权是 $1$，$j$ 到 $k$ 的最短路，我们不难发现由 $f_{i-1}$ 到 $f_i$ 的变化就是将一条边的边权由 $1$ 改为 $0$，那么直接 $\mathcal O(n^2)$ 更新即可。$f_0$ 可以使用 floyd 求。时间复杂度 $\mathcal O(n^2m)$。

### E2

因为这个图的边权只有 $0/1$，所以我们考虑将边权为 $0$ 的边的两个端点缩在一起，只有在这些新点之间的边才是有用的，显然如果将一条两个端点已经是属于同一个新点的边的边权由 $1$ 改为 $0$，这个操作显然是不会改变答案的，所以只有将两个新点合并的操作才是有用的，我们不难发现这种操作只有 $n-1$ 个，所以时间复杂度降为 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,q,a,b,k,f[405][405][405],fa[405],g[405][405];
struct ee{
	int u,v,w;
	friend bool operator<(const ee&a,const ee&b){
		return a.w<b.w;
	}
}e[160005],ed[405];
int find(int x){
	return(fa[x]==x)?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++)fa[i]=i;
		memset(g,0x3f,sizeof g);
		for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w,g[e[i].u][e[i].v]=g[e[i].v][e[i].u]=1;
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
		sort(e+1,e+m+1);
		int cnt=0;
		for(int i=1;i<=n;i++)g[i][i]=0;
		for(int i=0;i<=n-1;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)f[i][j][k]=g[j][k];
		for(int i=1;i<=m;i++){
			int fx=find(e[i].u),fy=find(e[i].v);
			if(fx==fy)continue;cnt++;
			ed[cnt]=e[i],fa[fx]=fy;
			for(int x=1;x<=n;x++)for(int y=1;y<=n;y++){
				f[cnt][x][y]=min({f[cnt-1][x][y],f[cnt-1][x][e[i].u]+f[cnt-1][y][e[i].v],f[cnt-1][x][e[i].v]+f[cnt-1][y][e[i].u]});
			}
		}
		while(q--){
			cin>>a>>b>>k;
			int l=1,r=cnt,ans=0;
			while(l<=r){
				int mid=l+r>>1;
				if(f[mid][a][b]<k)ans=mid,r=mid-1;
				else l=mid+1;
			}
			cout<<ed[ans].w<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：littlebug (赞：1)

## Solution

首先，在 $u \leadsto v$ 的最短路中若 $w_i$ 可以为第 $k$ 大边权，那么 $> w_i$ 的边一定 $< k$，进而可以转化一下，把 $> w_i$ 的边权都设为 $1$，$\le w_i$ 都设为 $0$，于是只要 $u \leadsto v$ 的最短路 $\le k$ 就可以了（我也不知道怎么想到的，神仙思路/bx ）。

发现题目符合「最\*值最\*」的模型，于是想到二分答案，每次需要判断 $u \leadsto v$ 的最短路是否 $<k$。因为这个状态有点多，不好直接算，于是可以想到预处理一个 dp，设 $f_{k,i,j}$ 为将前 $k$ 条边设为 $0$，其它设为 $1$（这里的 $k$ 跟前面没有任何关系），$i \leadsto j$ 的最短路，这个东西还是比较容易的，可以想到先跑个 floyd 把 $f_{0,i,j}$ 算出来，然后从小到大依次删边（即将边权设为 $0$），还是类似于 floyd，考虑将刚删的边作为中转点去更新所有的 $i,j$，设删的边为 $(u,v)$，则得到方程：

$$
f_{k,i,j} = \min (f_{k-1,i,j} , f_{k-1,i,u} + f_{k-1,v,j} , f_{k-1,i,v} + f_{k-1,u,j})
$$

floyd 是 $O(n^3)$ 的，上面 dp 是 $O(n^2m)$ 的，询问和二分是 $O(q \log m)$ 的。

## Code

```cpp
int n,m,q;
struct edge{int u,v,w;} e[MAXN];
int f[MAXN][MAXN][MAXN];

il void floyd()
{
	rep(k,0,m+1) rep(i,0,n+1) rep(j,0,n+1) f[k][i][j]=inf;
	rep(i,1,n) f[0][i][i]=0;
    rep(i,1,m) f[0][e[i].u][e[i].v]=f[0][e[i].v][e[i].u]=1;
    rep(k,1,n) rep(i,1,n) rep(j,1,n) f[0][i][j]=min(f[0][i][j],f[0][i][k]+f[0][k][j]);
}

il void solve(int __Ti)
{
    read(n,m,q);
    rep(i,1,m) read(e[i].u,e[i].v,e[i].w);
    sort(e+1,e+m+1,[](const auto a,const auto b){return a.w<b.w;});

    floyd();
    rep(k,1,m) rep(i,1,n) rep(j,1,n) f[k][i][j]=min({f[k-1][i][j],f[k-1][i][e[k].u]+f[k-1][e[k].v][j],f[k-1][i][e[k].v]+f[k-1][e[k].u][j]});

    int u,v,k,l,r,mid;
    while(q--)
    {
        read(u,v,k);

        l=1,r=m,mid=0x66CCFF;
        while(l<r)
        {
            mid=l+r>>1;
            f[mid][u][v]<k ? (r=mid) : (l=mid+1);
        }
        write(e[r].w,' ');
    }
    
    fast_io::pc('\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：What__can__I__say (赞：1)

DP。

$m$ 为 $400$，启发复杂度与 $m$ 有关。

先考虑如何判定两个点 $u$，$v$ 之间边权为 $w$ 的值能否成为答案：即 $u$，$v$ 两点间边权比 $w$ 大的边的数量是否小于 $k$。若是，边权为 $w$ 的边即可成为第 $k$ 大值。

快速判断这个条件，可以考虑重新赋权后最短路。发现上述条件等价于将边权小于等于 $w$ 的边重新赋权为 $0$，大于 $w$ 的边重新赋权为 $1$，然后判断 $u$，$v$ 两点间最短路是否小于 $k$。因为此时最短路的长度即为 $u$，$v$ 两点间路径至少经过几条边权大于 $w$ 的边。

考虑用类似弗洛伊德的方式。设 $f_{k,i,j}$ 表示将边权小于等于 $w_k$ 的边重新赋权为 $0$，其余为 $1$ 时 $u$，$v$ 两点间最短路。初始所有边都是 $1$。

先将所有边按边权升序排序。用一遍弗洛伊德预处理出所有 $f_{0,i,j}$。枚举每条边，取出一条后将其边权设为 $0$，随后以这条边为中转点暴力跑一遍更新所有 $f$ 值。设这条边是第 $k$ 条边，连结 $u$，$v$ 两顶点。枚举所有点对 $i$，$j$，这两点间最短路可以是先从 $i$ 到 $u$ 再到 $v$，也可以是先从 $i$ 到 $v$ 再到 $u$，最后到 $j$。当然也可以是原本的最短路。由于此时 $u$，$v$ 间边权是 $0$，有转移：

$$f_{k,i,j}=\min(f_{k-1,i,j},f_{k-1,i,u}+f_{k-1,v,j},f_{k-1,i,v}+f_{k-1,u,j})$$

最后处理询问时，我们只需二分答案，判 $f_{mid,u,v}$ 是否小于 $k$ 即可。

复杂度为 $O(mn^2+q\log m)$，可以通过本题。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
#define pb emplace_back
#define mod 1000000007
#define put putchar
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
const int JYAAKIOI=1e18,N=4e2+86,M=4e2+86;
struct node{
	int u,v,w;
}a[M];
int T,n,m,q,f[M][N][N],s;
il bool cmp(node x,node y){
	return x.w<y.w;
}
signed main(){
	//freopen("csnm.in","r",stdin);
	//freopen("csnm.out","w",stdout);
	T=rd();
	while(T--){
		n=rd();m=rd();q=rd();
		for(int i=1;i<=m;++i)a[i].u=rd(),a[i].v=rd(),a[i].w=rd();
		sort(a+1,a+1+m,cmp);
		for(int i=0;i<=m;++i){
			for(int j=1;j<=n;++j){
				for(int k=1;k<=n;++k){
					f[i][j][k]=JYAAKIOI;
				}
			}
		}
		for(int i=0;i<=n;++i)f[0][i][i]=0;
		for(int i=1;i<=m;++i)f[0][a[i].u][a[i].v]=f[0][a[i].v][a[i].u]=1;
		for(int k=1;k<=n;++k){
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					f[0][i][j]=min(f[0][i][j],f[0][i][k]+f[0][k][j]);
				}
			}
		}
		for(int k=1;k<=m;++k){
			int u=a[k].u,v=a[k].v;
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					f[k][i][j]=min(f[k-1][i][j],min(f[k-1][i][u]+f[k-1][v][j],f[k-1][i][v]+f[k-1][u][j]));
				}
			}
		}
		while(q--){
			int u=rd(),v=rd(),k=rd();
			int l=1,r=M,res=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(f[mid][u][v]<k){
					r=mid-1;
					res=mid;
				}
				else l=mid+1;
			}
			wr(a[res].w),put(' ');
		}
		put('\n');
	}
    return 0;
}
```

---

## 作者：yvbf (赞：1)

![](bilibili:BV1dkruY8ETZ?t=2152)

---

## 作者：ax_by_c (赞：0)

## E1

考虑枚举答案，将小于 $val$ 的边权看作 0，否则看作 1，那么只要 $dis(u,v)<k$ 就说明 $ans<val$。

一开始先跑一次 floyd，然后按照边权从小到大枚举，每次使用枚举边的端点去松弛即可。

时间复杂度 $O(n^3+mn^2+mq)$。

## E2

发现如果不是 MST 上的边，那么松弛到它的时候两端已经出现长度为零的路径了，所以不需要松弛。

所以只需松弛 MST 上的边，时间复杂度 $O(n^3+nq)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,l,r) for(int i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int inf=1e9;
const int N=405;
const int Q=3e5+5;
int n,m,q;
struct E{
	int u,v,w;
};
bool cmp(E x,E y){
	return x.w<y.w;
}
vector<E>es;
int f[N][N];
int x[Q],y[Q],kk[Q],ans[Q];
struct DSU{
	int fa[N];
	void Init(int n){
		rep(i,1,n)fa[i]=i;
	}
	int find(int x){
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	bool meg(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return 0;
		fa[x]=y;
		return 1;
	}
}dsu;
void slv(){
	scanf("%d %d %d",&n,&m,&q);
	dsu.Init(n);
	rep(i,1,n)rep(j,1,n)f[i][j]=inf;
	rep(i,1,n)f[i][i]=0;
	es.clr();
	rep(i,1,m){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		es.push_back({u,v,w});
		if(u!=v){
			f[u][v]=1;
			f[v][u]=1;
		}
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	sort(es.begin(),es.end(),cmp);
	rep(i,1,q){
		scanf("%d %d %d",&x[i],&y[i],&kk[i]);
		ans[i]=inf;
	}
	int lst=-inf;
	for(auto it:es){
		if(!dsu.meg(it.u,it.v))continue;
		rep(i,1,q)if(f[x[i]][y[i]]<kk[i])ans[i]=min(ans[i],lst);
		lst=it.w;
		rep(i,1,n)rep(j,1,n)f[i][j]=min({f[i][j],f[i][it.u]+f[it.v][j],f[i][it.v]+f[it.u][j]});
	}
	rep(i,1,q)printf("%d ",min(ans[i],lst));
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Wuming_Shi (赞：0)

# CF2057E1

## 题意
给定一个 $n$ 个点 $m$ 条边的无向图，边有边权。共 $q$ 次询问，每次询问给定 $a,b,k$，求 $a$ 到 $b$ 的所有路径中，第 $k$ 大的权值最小是多少。

$n\le400,m\le400,q\le3\times10^5$

## 思路
首先要离线。容易想到按边权从小到大加边。由于 $m$ 很小，所以可以每加一条边就处理一遍询问。

具体地，设当前加的边的边权为 $w$。遍历当前**未得出答案**的询问。对于每个询问的 $a, b$，设 $d$ 为 $a$ 所在连通块和 $b$ 所在连通块通过**未**加入的边的最短路（这里一条边算 $1$ 的距离）。换句话说：$a$ 和 $b$ 在不计入已连接的边的贡献的情况下，它们的最短路。

那么，若 $d$ 大于询问的 $k$，则说明该询问的答案大于 $w$。因为 $a$ 到 $b$ 的任何一条路径都要经过至少 $k$ 条大于 $w$ 的边。否则，当前询问的答案就为 $w$。

现在问题变成了如何在加边时处理好连通块间的最短路。

考虑使用 Floyd。首先预处理出每两个点间的最短路，复杂度 $O(n^3)$。在每次加边的时候，用并查集找出两端点的代表元 $a,b$。把 $a$ 合并到 $b$ 上，并将 $b$ 到每个点的最短路对 $a$ 到该点的最短路取 $\min$，单次复杂度 $O(n)$。

这样我们就维护好了 $a,b$ 这个大连通块到每个点的距离。然后再将 $b$ 作为中心点去更新每两个点的距离即可。单次复杂度 $O(n^2)$，正确性显然。

那么这一部分总的时间复杂度为 $O(mn^2)$。整个程序的时间复杂度为 $O(mn^2+mq)$，可以通过。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510, MAXQ = 3e5 + 10;
int n, m, q;
struct Edge {
    int u, v, w;
}edge[MAXN * MAXN];
struct Que {
    int a, b, k;
}que[MAXQ];
int fa[MAXN];
int dis[MAXN][MAXN];
int ans[MAXQ];

int getf(int pos) {return fa[pos] == pos ? pos : fa[pos] = getf(fa[pos]);}
inline void merge(int a, int b) {
    a = getf(a); b = getf(b);
    if (a == b) return;
    fa[a] = b;
    for (int i = 1; i <= n; i++) {
        dis[b][i] = dis[i][b] = min(dis[a][i], dis[b][i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dis[i][j] = dis[j][i] = min(dis[i][j], dis[i][b] + dis[b][j]);
        }
    }
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = {u, v, w};
        dis[u][v] = dis[v][u] = 1;
    }

    sort(edge + 1, edge + m + 1, [&](Edge &a, Edge &b) {
        return a.w < b.w;
    });

    for (int i = 1; i <= q; i++) {
        cin >> que[i].a >> que[i].b >> que[i].k;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) fa[i] = i;

    for (int i = 1; i <= m; i++) {
        merge(edge[i].u, edge[i].v);
        for (int j = 1; j <= q; j++) {
            if (ans[j]) continue;
            int a = getf(que[j].a);
            int b = getf(que[j].b);
            if (dis[a][b] < que[j].k) {
                ans[j] = edge[i].w;
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

void init() {
    for (int i = 1; i <= q; i++) {
        ans[i] = 0;
    }
}

int main() {
    int t; cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
        init();
    }

    return 0;
}
```

---

