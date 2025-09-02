# Shaass the Great

## 题目描述

The great Shaass is the new king of the Drakht empire. The empire has $ n $ cities which are connected by $ n-1 $ bidirectional roads. Each road has an specific length and connects a pair of cities. There's a unique simple path connecting each pair of cities.

His majesty the great Shaass has decided to tear down one of the roads and build another road with the same length between some pair of cities. He should build such road that it's still possible to travel from each city to any other city. He might build the same road again.

You as his advisor should help him to find a way to make the described action. You should find the way that minimize the total sum of pairwise distances between cities after the action. So calculate the minimum sum.

## 样例 #1

### 输入

```
3
1 2 2
1 3 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
6
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
```

### 输出

```
29
```

## 样例 #3

### 输入

```
6
1 3 1
2 3 1
3 4 100
4 5 2
4 6 1
```

### 输出

```
825
```

# 题解

## 作者：MyukiyoMekya (赞：7)

发现 $n$ 很小，意味着我们可以枚举边：我们枚举断掉 $(u,v,w)$ 这条边，然后这棵树就变成了两棵，

然后因为两棵树的点个数不变，所以这条边无论连在哪两个点之间贡献都一样，

所以现在只要考虑如何最小化跨立这条边的路径的贡献，

很容易发现就是分别求两个树的“重心“：所有点到根节点的带权路径的和的和的最小值的这个根。

~~盲猜这个“重心”就是重心。~~，我们对单棵树考虑一下。

随便选一个根为 $u$ ，那么选一个儿子 $v$ （通过边 $(u,v,w)$），把重心从 $u$ 变成 $v$ 会发生什么事：

发现只有 $(u,v,w)$ 这条边的贡献的系数从 $siz_v$ 变为了 $(n-siz_v)$，

这就意味着，只要有一个 $v$ 使得 $siz_v>n-siz_v$ ，我们就可以贪心把重心改为 $v$，

直到所有 $v$ 都有 $siz_v\le n-siz_v$ ，那么为什么这个 $u$ 是唯一的，或者说即使有多个但和是一样的。

把式子改一下 $2\times siz_v\le n$ 。。。这不就是重心定义么。。。，时间复杂度 $\mathcal O(n^2)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
const int MaxN=5050;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
template <class t>inline bool checkmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
struct Edge{int nxt,to,w;}E[MaxN<<2];
struct edge{int u,v,w;}e[MaxN];
int hd[MaxN],en,n;
inline void adde(int u,int v,int w){E[++en]=(Edge){hd[u],v,w},hd[u]=en;}
namespace BG
{
	int siz[MaxN],sum;
	inline void dfs(int u,int fa)
	{
		siz[u]=1;
		for(int i=hd[u];~i;i=E[i].nxt)
		{
			reg int v=E[i].to;
			if(v==fa)
				continue;
			dfs(v,u),siz[u]+=siz[v];
			sum+=siz[u]*(n-siz[u])*E[i].w;
		}
	}
}
struct Getroot
{
	int siz[MaxN],allsiz,mnsiz,root,locked,sum,cur;
	inline void dfs(int u,int fa)
	{
		siz[u]=1;
		reg int mx=0;
		for(int i=hd[u];~i;i=E[i].nxt)
		{
			reg int v=E[i].to;
			if(v==fa||v==locked)
				continue;
			dfs(v,u);
			siz[u]+=siz[v],checkmax(mx,siz[v]);
			sum+=siz[v]*(allsiz-siz[v])*E[i].w,cur+=siz[v]*E[i].w;
		}
		checkmax(mx,allsiz-siz[u]);
		if(checkmin(mnsiz,mx))root=u;
	}
	inline void init(int u,int fa,int S)
	{
		allsiz=S,mnsiz=1e9,locked=fa,root=0,sum=0;
		dfs(u,0),sum=cur=0,dfs(root,0);
	}
}tr1,tr2;
signed main(void)
{
	std::mem(hd,-1);
	read(n);
	reg int u,v,w;
	for(int i=1;i<n;++i)
		read(u,v,w),e[i]=(edge){u,v,w},adde(u,v,w),adde(v,u,w);
	BG::dfs(1,0);
	reg int ans=1e18;
	for(int i=1;i<n;++i)
	{
		u=e[i].u,v=e[i].v,w=e[i].w;
		if(BG::siz[u]>BG::siz[v])std::swap(u,v);
		tr1.init(u,v,BG::siz[u]),tr2.init(v,u,n-BG::siz[u]);
		checkmin(ans,tr1.sum+tr2.sum+
				(tr1.cur+BG::siz[u]*w)*(n-BG::siz[u])+tr2.cur*(BG::siz[u]));
	}
	write(ans),ln;
	return 0;
}
```



---

## 作者：leoair (赞：6)

### 题意：

有一棵 $n$ 个点的树，从 $n-1$ 条边中去掉一条边，再构建一条相同长度的边重新构成一棵树（去掉的边和构造的边可以相同），问新的树中任意两点之间距离的总和最小是多少。

$n \leq 5000$

### 分析：

设去掉的是长度为 $w$ 的边 $u\rightarrow v$，并在点 $x,y$ 间连一条长度为 $w$ 的边，则 $ans=sz_u\cdot sz_v\cdot w+sum_u+sum_v+\min\limits_{i\in u所在树的节点集合}\{sum_i\}\cdot sz_v+\min\limits_{i\in v所在树的节点集合}\{sum_v\}\cdot sz_u$，其中 $sz_i$ 表示去掉一条边后以 $i$ 为根的子树大小， $sum_i$ 表示相同情况下以 $i$ 为根时，其它树上节点到它的距离总和。

对于 $sz_u$ 和 $sz_v$，我们可以分别做一次 `dfs` 来求；至于 $sum_i$ 则可以通过 `换根dp` 来求。对于每棵树的最小值，可以在换根时自底向上更新。复杂度为 $O(n)$。

所以我们可以每次枚举一条边，每次在不经过这条边做 `换根dp` ，复杂度为 $O(n^2)$，可以接受。

对于 `换根dp` 时的求值，设 $d_x$ 为以 $x$ 为根的子树中 $x$ 与子树内节点的距离总和，$f_x$ 为以 $x$ 为根的树中 $x$ 与其它节点的距离总和。假设 $f_x$ 已经求出，且 $y\in son_x$，边 $x\rightarrow y$ 的值为 $z$，则 $f_y=d_y+(f_x-d_y)+[(sz_{root}-sz_y)-sz_y]\cdot z=f_x+(sz_{root}-2sz_y)z$。

具体实现见代码。

### Code：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5010;

int n, ans = 2e18, cnt, d[N], f[N], U[N], V[N], W[N], sz[N], fa[N], mn[N], head[N];

struct xcj{
	int to, nxt, value;
} e[N << 1];

inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
	return s * w;
}

void add(int u, int v, int w){e[++cnt] = {v, head[u], w}, head[u] = cnt;}

void dfs(int x){
	sz[x] = 1, d[x] = 0;
	for (int i = head[x]; i; i = e[i].nxt){
		int y = e[i].to, z = e[i].value;
		if (y == fa[x]) continue;
		fa[y] = x, dfs(y), sz[x] += sz[y], d[x] += d[y] + sz[y] * z;
	}
}

void dp(int x, int root){
	mn[x] = f[x];
	for (int i = head[x]; i; i = e[i].nxt){
		int y = e[i].to, z = e[i].value;
		if (y == fa[x]) continue;
		f[y] = f[x] + (sz[root] - 2 * sz[y]) * z, dp(y, root), mn[x] = min(mn[x], mn[y]);
	}
}

signed main(){
	n = read();
	for (int i = 1; i < n; ++i) U[i] = read(), V[i] = read(), W[i] = read(), add(U[i], V[i], W[i]), add(V[i], U[i], W[i]);
	for (int i = 1, u, v, w, res; i < n; ++i){
		memset(mn, 0x3f, sizeof(mn));
		u = U[i], v = V[i], w = W[i], fa[u] = v, fa[v] = u, dfs(u), f[u] = d[u], dp(u, u), dfs(v), f[v] = d[v], dp(v, v), res = 0;
		for (int j = 1; j <= n; ++j) res += f[j];
		ans = min(ans, res / 2 + sz[u] * sz[v] * w + mn[u] * sz[v] + mn[v] * sz[u]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：觞羰涙 (赞：6)

# 题意：
## 一棵树拆一个边重连，边长不变，求所得新树两两节点路径总和最小值
# 思路
### 拆成两棵树后两树内部两两距离和不变，再加上u（一树节点数）乘v（另一树节点数）乘w（重连的边的长度）+两书间节点路径和
### 以上皆可dfs处理
### 枚举拆的边，反证法可得新连的两书节点分别是两树重心，求出重心再算即可
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<iomanip>
#define maxn 200005
typedef long long ll;
const int inf = 0x3f3f3f3f;
ll ans=-1,sum,tol;
int sig1,sig2;//rua掉的路 
int n,cnt;//拆出的两棵树连接两个的重心路径和一定最小 
int emp,pos;//求重心的 
int head[maxn],son[maxn];
using namespace std;
struct fuck
{
	int from,to,next;ll w;
}e[maxn*2];
void add(int u,int v,ll w)
{
	/*加边*/
}
void init()
{
	/*初始化*/
}
void erzi(int u,int dad)
{
	/*求儿子数*/
}
void zhongxin(int u,int dad,int tol)
{
	int maxm=0;
	for(int i=head[u];~i;i=e[i].next)
	{
		int j=e[i].to;
		if(j==dad||i==sig1||i==sig2)continue;
		zhongxin(j,u,tol);
		maxm=max(maxm,son[j]);
	}
	maxm=max(maxm,tol-son[u]);
	if(maxm<emp)
	{
		emp=maxm;pos=u;
	}
}
void dfs(int u,int dad)
{
	son[u]=1;
	for(int i=head[u];~i;i=e[i].next)
	{
		int j=e[i].to;
		if(j==dad||i==sig1||i==sig2)continue;
		dfs(j,u);son[u]+=son[j];
		sum+=e[i].w*son[j]*(n-son[j]);
	}
}
int main()
{
	int u,v;ll w;
	read(n);init();
	for(int i=1;i<n;i++)
	{
		read(u);read(v);read(w);
		add(u,v,w);add(v,u,w);
	}
	for(int i=0;i<cnt;i+=2)
	{
		int x=e[i].from,y=e[i].to;
		sig1=i;sig2=i+1;sum=0;
		erzi(x,-1);u=son[x];//v=n-u;
		erzi(y,-1);v=son[y];
		emp=inf;zhongxin(x,-1,u);
		dfs(pos,-1);
		emp=inf;zhongxin(y,-1,v);
		dfs(pos,-1);
		//cout<<u<<" "<<v<<endl;
		if(ans==-1)ans=sum+e[i].w*u*v;
		else ans=min(ans,sum+e[i].w*u*v);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：hgzxHZR (赞：1)

## 题意分析

本题是一个比较综合的题，由于 $n\le5000$，可以考虑 $O(n^2)$ 的算法，即考虑深搜。

枚举每条断开的边，断开后原树就分裂为了两个子树，计算两个子树的任意两点距离和（记作 $sum\_dis$），那么根据乘法原理（反正我是这样思考的），我们可以知道，对于原树（记根为零，断开的边连接的节点为 $u,v$），有
$$
{sum\_dis[0]=sum\_dis[u]+sum\_dis[v]+siz[u]\times siz[v]\times E[i].W+dis[u_1]\times siz[v]+dis[v_1]\times siz[u];}
$$
其中 $dis[i]$ 表示子树中所有点到 $i$ 点的距离之和，这是很简单就能求得的。$u_1$ 属于子树 $u$，$v_1$ 属于子树 $v$。上面式子中 $dis[v_1],dis[u_1]$ 为变量，只需求一下最小值就行了。

要用重儿子优化，详见代码。

## code

```cpp
#include<bits/stdc++.h>

#define int long long
using namespace std;
const int MAXN=5e3+5,inf=0x7f7f7f7f7f7f7f7f;

inline int read()
{
	int n=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n;
}

int head[MAXN];
struct tEdge{
int Next,From,To;
int W;
	void ADD(const int &u,const int &v,const int &dis,const int &pos)
	{
		Next=head[u],From=u,To=v;W=dis;
		head[u]=pos;
		return ;
	}
}E[MAXN<<1];//链式前向星，建双向边
int n,u,v,w,ans[MAXN];

bool duankai[MAXN];
int siz[MAxN],centerl,center2,center；//siz[i]是子树i的大小，断开的边两边子树的重心
int dis [MAXN],sum_dis[MAXN],ROOT,son[MAXN];
int tran(const int &x){return x>=n?x-n:x;}
void DFS1(const int &r,const int &fa)
{
	siz[r]=1;dis[r]=0;sum_dis[r]=0;
	int MAX=-1;
	for(int i=head[r];i;i=E[i].Next)
	{
		int v=E[i].To;
		if(v==fa) continue;//父节点不用重复搜 
		if(duankai[tran(i)]) continue;//断开的边不用搜下去 
		DFS1(v,r);
		sum_dis[r]+=sum_dis[v]+siz[r]*dis[v]+siz[v]*dis[r]+siz[v]*siz[r]*E[i].W;
		siz[r]+=siz[v];dis[r]+=dis[v]+siz[v]*E[i].W;
		if(MAX<siz[v]) {MAX=siz[v];son[r]=i;}//记录最重儿子的边号
	}
	return ;
}
void DFS2(const int &r,const int &fa)
{
	if(dis[r]<dis[Center]) Center=r;
	if(son[r])//优化后沿重儿子递推 
	{
		int i=son[r];
		int v=E[i].To;
		dis[v]=dis[r]+(siz[ROOT]-2*siz[v])*E[i].W;
		DFS2(v,r);
	}
	return ;
}

void Work()
{
	int u,v;ans[0]=inf;
	for(int i=1;i<n;++i)
	{
		u=E[i].From,v=E[i].To;
		duankai[i]=true;//断开第i条边 
		ROOT=u,Center=0,dis[Center]=inf;DFS1(ROOT,0);DFS2(ROOT,0);Center1=Center;
		ROOT=v,Center=0;dis[Center]=inf;DFS1(ROOT,0);DFS2(ROOT,0);Center2=Center;//搜索断开的边两边的子树 
		duankai[i]=false;
		ans[i]=sum_dis[u]+sum_dis[v]+siz[u]*siz[v]*E[i].W+dis[Center1]*siz[v]+dis[Center2]*siz[u];
		//同上述递推式
		if(ans[0]>ans[i]) ans[0]=ans[i];
	}
	return ;
}

signed main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		u=read();v=read();w=read();
		E[i].ADD(u,v,w,i);E[i+n].ADD(v,u,w,i+n);
	}
	
	Work();
	cout<<ans[0];
	
	return 0;
}
```



---

## 作者：lilong (赞：0)

考虑 dp。设 $f_u$ 表示以 $u$ 为根的子树中每个点到 $u$ 的距离之和，则有 $f_u=\sum_{v\in son_u}f_v+w_{u,v}\times size_v$。通过换根操作即可以 $O(n)$ 的复杂度求出路径和（注意要除以 $2$）。

接下来枚举断掉哪条边，那么遍历时分别从这条边的两个端点 $u,v$ 出发，不经过这条边，分别做一遍上文中的 dp 以及换根，求出两棵子树**内部路径和** $s_1,s_2$ 以及**到某一点的最小距离和** $m_1,m_2$。新的边应该建在取最小距离和的两点 $x,y$ 间，则总路径和为

$$s_1+s_2+m_1\times size_v+m_2 \times siz_u+w_{u,v}\times size_u \times size_v$$

时间复杂度 $O(n^2)$。


```cpp
//
#include<iostream>
#include<cstdio>
#include<vector>
#define N 5010
#define int long long
using namespace std;
struct E{
    int v,w,id;
};
struct Edge{
    int u,v,w;
}e[N];
int n,f[N],siz[N],mi[3],ss[3],ans,eid,nw,rt;
vector<E> G[N];
void dfs0(int u,int ff){
    // cout<<u<<' ';
    f[u]=0;
    siz[u]=1;
    for(auto it:G[u]){
        int v=it.v,w=it.w,id=it.id;
        if(id==eid)continue;
        if(v==ff)continue;
        dfs0(v,u);
        siz[u]+=siz[v];
        f[u]+=f[v]+siz[v]*w;
    }
    return;
}
void dfs1(int u,int ff){
    // cout<<u<<' '<<f[u]<<'\n';
    mi[nw]=min(mi[nw],f[u]);
    ss[nw]+=f[u];
    for(auto it:G[u]){
        int v=it.v,w=it.w,id=it.id;
        if(id==eid)continue;
        if(v==ff)continue;
        int lstu=f[u],lstv=f[v];
        f[u]=f[u]-(f[v]+siz[v]*w);
        f[v]=f[v]+f[u]+(siz[rt]-siz[v])*w;
        dfs1(v,u);
        f[u]=lstu,f[v]=lstv;
    }
    return;
}
void solve(int x){
    eid=x;
    ss[1]=ss[2]=0,mi[1]=mi[2]=1e18;
    nw=1;
    rt=e[eid].u;dfs0(e[eid].u,0);dfs1(e[eid].u,0);//cout<<'\n';
    nw=2;
    rt=e[eid].v;dfs0(e[eid].v,0);dfs1(e[eid].v,0);//cout<<'\n';
    ss[1]/=2;ss[2]/=2;
    // cout<<x<<' '<<ss[1]<<' '<<ss[2]<<' '<<mi[1]<<' '<<mi[2]<<' '<<ss[1]+ss[2]+mi[1]*siz[e[eid].v]+mi[2]*siz[e[eid].u]+e[eid].w*siz[e[eid].u]*siz[e[eid].v]<<'\n';
    ans=min(ans,ss[1]+ss[2]+mi[1]*siz[e[eid].v]+mi[2]*siz[e[eid].u]+e[eid].w*siz[e[eid].u]*siz[e[eid].v]);
    return;
}
signed main(){
    int u,v,w;
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v>>w;
        e[i]={u,v,w};
        G[u].push_back({v,w,i});
        G[v].push_back({u,w,i});
    }
    rt=1;
    dfs0(1,0);//cout<<f[1]<<'\n';
    dfs1(1,0);//cout<<'\n';
    ans=ss[0]/2;
    // cout<<ans<<endl;
    for(int i=1;i<n;i++)
        solve(i);
    cout<<ans;
    return 0;
}
```

---

## 作者：Kingna (赞：0)

### 题面翻译

树中有 $n$ 个点，从 $n-1$ 条边中去除一条边，再构建一条相同长度的边重新构成一棵树（去除的边和构造的边可能相同），问新树中任意两点之间距离的总和最小是多少。

$n \leq 5000$。

### 思路

先从 $n-1$ 条边中枚举断掉哪些边，然后就把原树分成了两个部分。

然后现在只需要从两个部分中，选择两个点连边，重新构成一个树的总和最小。考虑取 $u,v$ 两个点，将其连接，则可以知道贡献为：$s_1+s_2+sz_1\times sz_2\times w+\min_{i∈u}{sum_{1_i}}\times sz_2+\min_{i∈v}{sum_{2_i}}\times sz_1$。其中 $sum_1$ 数组代表在左部分选择第 $i$ 个点时，其它树上节点到它的距离总和。 $sum_2$ 数组代表在右部分选择第 $i$ 个点时，其它树上节点到它的距离总和。


很容易发现就是分别求两个树的重心：**所有点到根节点的带权路径的和的和的最小值的这个根。** 且这个重心就是树的重心。

代码：https://pastebin.com/6etQTXxp

---

## 作者：AzusidNya (赞：0)

## CF294E Shaass the Great

随机跳到，并感觉 Clist 的 $\textcolor{red}{2498}$ 是虚高的。

注意到 $n$ 很小，考虑枚举拆掉的边。

然后树会被拆成两个不同的连通块，而因为连边后图应该还是一棵树，所以一定是在两个连通块之间连边。

把点对分为两类，在同一连通块中的点对和不在同一连通块中的点对。因为连通块内部形态没变所以在同一连通块中的点对的距离和不会改变，并且这是很容易树形 dp 求的。所以只用考虑怎么最小化不在同一连通块的点对的距离和。

假设最终连上的边是 $(u, v)$。考虑钦定 $u$ 为连接后的树的根节点，那么所有原本不在同一个连通块的点对的 $\operatorname{lca}$ 都在 $u$ 节点上。

考虑固定 $u$ 去选 $v$ 节点。令 $u$ 节点的深度为 $0$，那么这类点对的距离和就是 $v$ 子树内的深度和乘上 $u$ 所在的连通块的大小加上 $u$ 所在的子树的深度和乘上 $v$ 所在连通块的大小再加上连通块大小之积乘上拆掉的边的边权。而 $v$ 所在子树的大小是固定的，所以选择的 $v$ 一定满足在 $v$ 的连通块中以 $v$ 为根，所有节点的深度和最小。

同理，$u$ 也应该选择在 $u$ 的连通块中以 $u$ 为根所有节点深度和最小的点。

换根 dp 即可。设 $g(u)$ 表示以 $u$ 为根时连通块的深度和。用 $u$ 转移到一个儿子节点 $x$ 时，$x$ 子树内的节点深度都减少 $(u, x)$ 的边权，不在 $x$ 子树内的节点的深度都增加 $(u, v)$ 的边权，预处理子树大小和子树深度后很好 dp。

枚举所有边后将两个连通块的信息合并即可。时间复杂度 $O(n ^ 2)$。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
// #define int long long
#define eb emplace_back
#define mp make_pair
// #define DEBUG
using namespace std;
const int P = 998244353;
using pii = pair<int, int>;
using piii = pair<int, pii>;
using piiii = pair<pii, pii>;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
namespace azus{
	int n;
	vector<pair<int, i64> > edge[5005];
	i64 f[5005], s[5005], ret, g[5005], dep[5005];
	int siz[5005];
	int dfs(int u, int fa){
		siz[u] = 1; s[u] = dep[u];
		g[u] = 0;
		for(auto [v, w] : edge[u]){
			if(v == fa) continue;
			dep[v] = dep[u] + w;
			dfs(v, u);
			g[u] += g[v];
			i64 depsum = s[v] - 1ll * dep[u] * siz[v];
			i64 dsu = s[u] - 1ll * dep[u] * siz[u];
			g[u] += (1ll * dsu * siz[v] + 1ll * depsum * siz[u]);
			siz[u] += siz[v];
			s[u] += s[v];
		}
		return 0;
	}
	int dfs2(int u, int fa, int Siz){
		ret = min(ret, f[u]);
		for(auto [v, w] : edge[u]){
			if(v == fa) continue;
			f[v] = f[u] - 1ll * siz[v] * w + 1ll * (Siz - siz[v]) * w;
			dfs2(v, u, Siz);
		}
		return 0;
	}
	i64 solve(int u, int fa){
		ret = inf;
		dep[u] = 0;
		dfs(u, fa);
		f[u] = s[u];
		dfs2(u, fa, siz[u]);
		return ret;
	}
	int main(){
		cin >> n;
		i64 w;
		for(int i = 1, u, v; i < n; i ++){
			cin >> u >> v >> w;
			edge[u].eb(mp(v, w)), edge[v].eb(mp(u, w));
		}
		i64 ans = inf;
		for(int u = 1; u <= n; u ++){
			for(auto [v, w] : edge[u]){
				i64 x = solve(u, v), y = solve(v, u);
				int szx = siz[u], szy = siz[v];
				ans = min(ans, g[u] + g[v] + 1ll * szx * y + 1ll * szy * x + 1ll * szx * szy * w);
			}
		}
		cout << ans << "\n";
		return 0;
	}
}
signed main(){
#ifndef DEBUG
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#endif
	int T = 1;
	while(T --)
		azus::main();
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

枚举删除的边$(u,v)$ ,可以分别得到以$u$,$v$为根的两棵树。

显然删除掉的两条边贡献为$sz_u\times sz_v\times w(u,v)$

接下来暴力计算新连接的边让两个树贡献最小。

$dp[u][0]=$新的边连接v子树时这个子树的贡献

$dp[u][1]=$新的边连接u子树时这个子树的贡献

具体见代码
```
#include<bits/stdc++.h>
#define ld long double
#define test puts("QAQ");
#define int long long
#define pb push_back
#define pii pair<int,int> 
#define mp make_pair
#define Max(a,b) (a>b)?a:b
using namespace std;
const long long inf=0x7f7f7f7f7f7f7f;

const int MAXN=10000000;
inline char gc(){
    static char In[MAXN],*at=In,*en=In;
    return at==en&&(en=(at=In)+fread(In,1,MAXN,stdin)),at==en?EOF:*at++;
}
template<class tp>
void read(tp &x){
    x=0;
    char c=gc();
    bool sgn=0;
    while((c<'0'||c>'9')&&c!='-')c=gc();
    if(c=='-')sgn=1,c=gc();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^'0'),c=gc();
    if(sgn)x=-x;
}
char _In[MAXN],*_at=_In;
inline void flush(){fwrite(_In,1,_at-_In,stdout),_at=_In;}
struct _init{~_init(){flush();}}__init;
inline void pc(char c){if(_at==_In+MAXN)flush();*_at++=c;}
template<class tp>
void write(tp x){
    if(!x){pc('0');return;}
    static char buf[43],*at;
    at=buf;
    if(x<0)pc('-'),x=-x;
    while(x)*at++=x%10+'0',x/=10;
    do pc(*--at); while(at!=buf);
}

const int N=5010;
int n;
int head[N],cnt;
int sz[N];
long long dp[N][2];
struct edge
{
    int frm,nxt,to,val;
}e[N<<2];
void add_edge(int u,int v,int d)
{
    e[++cnt].nxt=head[u];
    e[cnt].frm=u;
    e[cnt].to=v;
    e[cnt].val=d;
    head[u]=cnt;
}
void dfs1(int u,int f)//size
{
    sz[u]=1;
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
    }
}
void dfs2(int u,int f,int rt)
{    
    dp[u][0]=0;
    dp[u][1]=inf;
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f) continue;
        dfs2(v,u,rt);
        dp[u][0]+=dp[v][0]+1ll*e[i].val*sz[v]*(n-sz[v]);
    }
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f) continue;
        dp[u][1]=min(dp[u][1],dp[u][0]-dp[v][0]-1ll*e[i].val*sz[v]*(n-sz[v])+min(dp[v][0],dp[v][1])+1ll*e[i].val*(sz[rt]-sz[v])*(n-sz[rt]+sz[v]));
    }
}   
signed main()
{
    for(int i=1;i<N;i++) head[i]=-1;
    read(n);
    for(int i=1,u,v,w;i<n;i++)
    {
        read(u);read(v);read(w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    long long res=inf;
    for(int i=1;i<=cnt;i+=2)//一条边不用删两次
    {
        int u=e[i].frm,v=e[i].to;
        dfs1(u,v),dfs1(v,u);
        dfs2(u,v,u),dfs2(v,u,v);
        res=min(res,min(dp[u][0],dp[u][1])+min(dp[v][0],dp[v][1])+1ll*e[i].val*sz[u]*sz[v]);
    }
    printf("%lld\n",res);
}
```


---

