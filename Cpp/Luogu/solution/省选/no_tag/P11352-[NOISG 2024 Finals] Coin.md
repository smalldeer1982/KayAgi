# [NOISG 2024 Finals] Coin

## 题目描述

Benson 有 $n$ 枚不同重量的硬币和一个天平。每次将硬币 $x$ 和 $y$ 放在天平上，可以知道它们的相对重量，即 $x$ 是否比 $y$ 更重。

硬币 $x$ 的排名（rank）定义为不比它更重的硬币数量（包括自身）。例如，最轻的硬币的排名是 $1$，次轻的是 $2$，最重的是 $n$。

对于每个硬币，当且仅当基于已有的称量结果可以唯一确定其排名时，称其排名被“确定”（determined）。

你的任务是帮助 Benson 找出每个硬币首次确定排名的称量序号，或者判断它的排名永远无法确定。

## 说明/提示

【样例解释】

对于样例 #1：
- 硬币 $1$ 的排名在第 $3$ 次称量后确定，输出 $3$。
- 硬币 $2$ 的排名在第 $4$ 次称量后确定，输出 $4$。
- 硬币 $3$ 和 $4$ 的排名无法确定，输出 $-1$。

对于样例 #2：
- 每个硬币的排名确定的时间点分别是 $8$，$8$，$5$，$5$，$5$ 和 $6$。

【数据范围】

- $2 \leq n \leq 200,000$
- $1 \leq m \leq 800,000$
- $1 \leq x, y \leq n$
- 硬币之间的所有称量关系形成一个有效的偏序。

| 子任务编号 | 分值 | 限制条件                     |
|:---:|:---:|:---:|
| $0$ | $0$  | 样例测试用例                     |
| $1$ | $6$  | $1 \leq n \leq 7, 1 \leq m \leq 20$ |
| $2$ | $16$ | $1 \leq n \leq 100, 1 \leq m \leq 400$ |
| $3$ | $10$ | $1 \leq n \leq 1000, 1 \leq m \leq 4000$ |
| $4$ | $68$ | 无额外限制                       |

## 样例 #1

### 输入

```
4 4
2 4
3 1
4 1
2 3```

### 输出

```
3 4 -1 -1```

## 样例 #2

### 输入

```
6 8
1 5
5 4
6 2
2 5
4 3
6 1
6 5
2 1```

### 输出

```
8 8 5 5 5 6```

# 题解

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P11352)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的 DAG，对于每个 $u$ 求最小的 $i$ 使得保留前 $i$ 条边后 $u$ 的拓扑序唯一。
>
> 数据范围：$n\le 2\times 10^5,m\le 8\times 10^5$。

**思路分析**

首先考虑什么样的 $u$ 拓扑序唯一，即拓扑序小于 $u$ 的点都能到达 $u$，大于 $u$ 的点都能被 $u$ 到达。

考虑第一个条件，只保留拓扑序小等于 $u$ 的点，那么我们要求 $u$ 是唯一一个无出度的点。

同理保留拓扑序大于等于 $u$ 的点，$u$ 是唯一一个无入度的点，这两个条件显然是充要的。

那么动态维护前缀或后缀的导出子图上每个点的最小出边，用堆维护答案即可。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,MAXM=8e5+5;
int n,m,a[MAXN],deg[MAXN];
struct Edge { int v,w; };
vector <Edge> L[MAXN],R[MAXN];
int f[MAXN],g[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;++i) {
		cin>>u>>v,++deg[v],L[u].push_back({v,i}),R[v].push_back({u,i});
	}
	queue <int> Q;
	for(int i=1;i<=n;++i) if(!deg[i]) Q.push(i);
	for(int i=1;i<=n;++i) {
		int u=a[i]=Q.front(); Q.pop();
		for(auto e:L[u]) if(!--deg[e.v]) Q.push(e.v);
	}
	priority_queue <array<int,2>> S;
	for(int i=n;i>=1;--i) {
		int u=a[i];
		for(auto e:L[u]) if(e.w<g[e.v]) S.push({g[e.v]=e.w,e.v});
		while(S.size()) {
			auto it=S.top();
			if(it[0]!=g[it[1]]) S.pop();
			else { f[u]=max(f[u],it[0]); break; }
		}
		S.push({g[u]=m+1,u});
	}
	priority_queue<array<int,2>>().swap(S);
	for(int i=1;i<=n;++i) {
		int u=a[i];
		for(auto e:R[u]) if(e.w<g[e.v]) S.push({g[e.v]=e.w,e.v});
		while(S.size()) {
			auto it=S.top();
			if(it[0]!=g[it[1]]) S.pop();
			else { f[u]=max(f[u],it[0]); break; }
		}
		S.push({g[u]=m+1,u});
	}
	for(int i=1;i<=n;++i) cout<<(f[i]>m?-1:f[i])<<" \n"[i==n];
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

如果你写过 CF1062F ，这道题就是送分题。

将问题略加转化：对于每个 $u$，求最小的 $t$ 使得保留所有出现时间 $\le t$ 的边，$\forall v \neq u$，存在 $u \to v$ 的路径或 $v \to u$ 的路径。

考虑求出一个拓扑序。显然我们要求当前点出队列时，队列里没有其他元素。剩下所有未入队列的点都可以由当前节点到达。

对于每个点，保留**所有未被遍历过的入边中出现时间最小的那一条**，显然不改变连通性。求这些边时间的最大值即可。

正反跑两遍上述流程，即可求得答案。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10;
int n,m,tot,rnk[MAXN],rev[MAXN],ans[MAXN],flg[MAXN],deg[MAXN];
multiset<int> zt,ot[MAXN];
vector<pair<int,int>> G[MAXN],g[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {
		int x,y;
		cin>>x>>y,G[x].push_back({y,i}),g[y].push_back({x,i});	
	}
	ffor(i,1,n) deg[i]=g[i].size();
	queue<int> qq;
	ffor(i,1,n) if(!deg[i]) qq.push(i);
	while(!qq.empty()) {
		int u=qq.front();
		qq.pop();
		rnk[u]=++tot,rev[tot]=u;
		for(auto pr:G[u]) {
			int u=pr.first;
			if(!(--deg[u])) qq.push(u);
		}
	}
	priority_queue<int> q;
	ffor(i,1,n) {
		for(auto pr:g[i]) ot[i].insert(pr.second);
		if(!ot[i].empty()) zt.insert(*ot[i].begin());	
	}
	int sze=0;
	ffor(i,1,n) deg[i]=g[i].size();
	ffor(i,1,n) if(!deg[i]) q.push(-rnk[i]),sze++;
	while(!q.empty()) {
		int u=rev[-q.top()];
		q.pop();
		sze--;
		if(!sze) {if(!zt.empty()) ans[u]=max(ans[u],*(--zt.end()));}
		else flg[u]=1;
		for(auto pr:G[u]) {
			int v=pr.first,w=pr.second,ori=*ot[v].begin();
			zt.erase(zt.find(ori)),ot[v].erase(ot[v].find(w));
			if(!ot[v].empty()) zt.insert(*ot[v].begin());
			if(!(--deg[v])) q.push(-rnk[v]),sze++;	
		}
	}
	zt.clear();
	ffor(i,1,n) {
		ot[i].clear();
		for(auto pr:G[i]) ot[i].insert(pr.second);
		if(!ot[i].empty()) zt.insert(*ot[i].begin());	
	}
	sze=0;
	ffor(i,1,n) deg[i]=G[i].size();
	ffor(i,1,n) if(!deg[i]) q.push(rnk[i]),sze++;
	while(!q.empty()) {
		int u=rev[q.top()];
		q.pop();
		sze--;
		if(!sze) {if(!zt.empty()) ans[u]=max(ans[u],*(--zt.end()));}
		else flg[u]=1;
		for(auto pr:g[u]) {
			int v=pr.first,w=pr.second,ori=*ot[v].begin();
			zt.erase(zt.find(ori)),ot[v].erase(ot[v].find(w));
			if(!ot[v].empty()) zt.insert(*ot[v].begin());
			if(!(--deg[v])) q.push(rnk[v]),sze++;	
		}
	}
	
	ffor(i,1,n) if(flg[i]) cout<<-1<<' '; else cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：AsiraeM (赞：2)

一个简单一点的做法。  
若在一次称量中得知 $x$ 比 $y$ 轻，则由 $x$ 向 $y$ 连一条有向边（称这条边的编号为此次称量的序号），构成一个 DAG。在某一时刻，$x$ 与 $y$ 的大小关系是确定的，当且仅当有一条从 $x$ 到 $y$ 的路径或有一条从 $y$ 到 $x$ 的路径。  
于是可以得出一个硬币 $x$ 的排名被唯一确定的条件：当前时刻每个拓扑序小于 $x$ 的点都有一条到 $x$ 的路径；每个拓扑序大于 $x$ 的点，都有一条从 $x$ 到它的路径。  
**接下来只考虑拓扑序小于 $x$ 的部分，另一部分是对称的。**  
发现仅保留拓扑序小于等于 $x$ 的点时，若除 $x$ 以外每个点都有至少一条出边，那么每个点必定有一条到 $x$ 的路径。根据拓扑序从小到大扫描线，扫到一个点时加入这个点与其所有入边（具体地，设 $f_x$ 表示 $x$ 出边的编号的最小值，则用数据结构维护 $f_x$，加入一条边时更新这条边起点的 $f_x$），此时若除这个点以外所有点都有出边，则答案为所有 $f_x$ 的最大值，否则它的排名无法确定。  

---

代码：
```cpp
#include<bits/stdc++.h>
namespace xcy{
const int MAXN=200005;
typedef long long ll;
typedef std::pair<ll,ll> sp;
const ll INF=0x3f3f3f3f3f3f3f3f;
ll nxt[MAXN],ans[MAXN],deg[MAXN],q[MAXN],h,t,n,m,i,j,k,l;
std::vector<sp>g[MAXN],rv[MAXN];std::set<ll>s;

namespace FIO{char B[1<<20],*S=B,*T=B;}
#define getchar() (FIO::S==FIO::T&&(FIO::T=(FIO::S=FIO::B)+fread(FIO::B,1,1<<20,stdin),FIO::S==FIO::T)?EOF:*FIO::S++)
inline void fread(ll &X){ll A=1;X=0;char C=getchar();while(!isdigit(C)&&C!='-')C=getchar();if(C=='-')A=-1,C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();X*=A;}
inline void fout(ll X,char Ch=' '){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(Ch);return;}char C[25]{};int Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(Ch);}

int mian()
{
    fread(n);fread(m);for(i=1;i<=m;++i)fread(j),fread(k),
        g[j].push_back({k,i}),rv[k].push_back({j,i}),++deg[k];
    for(i=1;i<=n;++i)if(!deg[i])q[++t]=i;
    for(h=1;h<=n;++h)
    {
        i=q[h];for(auto I:g[i])if(!(--deg[j=I.first]))q[++t]=j;
        for(auto I:rv[i])j=I.first,s.erase(nxt[j]),
            nxt[j]=std::min(nxt[j],I.second),s.insert(nxt[j]);
        if(s.size())ans[i]=*s.rbegin();s.insert(nxt[i]=INF+i);
    }
    for(h=n,s.clear();h;--h)
    {
        i=q[h];for(auto I:g[i])j=I.first,s.erase(nxt[j]),
            nxt[j]=std::min(nxt[j],I.second),s.insert(nxt[j]);
        if(s.size())ans[i]=std::max(ans[i],*s.rbegin());s.insert(nxt[i]=INF+i);
    }
    for(i=1;i<=n;++i)if(ans[i]<=m)fout(ans[i]);else fout(-1);putchar('\n');
    return 0;
}}
int main(){return xcy::mian();}
```

---

## 作者：nullqtr_pwp (赞：2)

考虑对于一张给定的 DAG，怎么判 $-1$。注意到一个点 $x$ 的权值可以确定当且仅当对于所有 $y\ne x$，都有 $y$ 可以到达 $x$ 或者 $x$ 可以到达 $y$，表示权值可以确定。首先原图如果不是弱连通的一定全部为 $-1$，否则考虑求出原图的拓扑序。注意到拓扑序大的一定无法到达拓扑序小的。那么按照拓扑序倒序加点，当前加入 $x$ 时如果存在至少两个点的入度为 $0$（包含 $x$），那么 $x$ 就一定无法抵达拓扑序大于 $x$ 的所有点（比如另一个零入度的点）。可以简单做一遍 $O(n+m)$ 的拓扑排序求出。正反图各自跑一遍，表示判定拓扑序大于以及小于它的检查可达性。

考虑拓展到求权值，令边权为操作编号，对于正常图倒序加点的过程中，如果出现了一个零入度点，那么必须要求其通过一个前驱被消掉。容易对于所有前驱按照拓扑序排序，就是若干段分段函数，每个取 $\max$，容易线段树维护。

时间复杂度 $O(n\log n)$。

```cpp
// 私は猫です

#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define rep(i,a,b,c) for(int i=(a);i<=(b);i+=(c))
#define per(i,a,b,c) for(int i=(a);i>=(b);i-=(c))
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define dF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define cmh(sjy) while(sjy--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define poly vector<int>
using namespace std;
ll read(){
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
namespace Fastio{struct Reader{template<typename T>Reader&operator>>(T&x){x=0;short f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();x*=f;return*this;}Reader&operator>>(double&x){x=0;double t=0;short f=1,s=0;char c=getchar();while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else{x*=f;return*this;}while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}Reader&operator>>(long double&x){x=0;long double t=0;short f=1,s=0;char c=getchar();while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else{x*=f;return*this;}while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}Reader&operator>>(__float128&x){x=0;__float128 t=0;short f=1,s=0;char c=getchar();while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else{x*=f;return*this;}while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}Reader&operator>>(char&c){c=getchar();while(c==' '||c=='\n'||c=='\r')c=getchar();return*this;}Reader&operator>>(char*str){int len=0;char c=getchar();while(c==' '||c=='\n'||c=='\r')c=getchar();while(c!=' '&&c!='\n'&&c!='\r')str[len++]=c,c=getchar();str[len]='\0';return*this;}Reader&operator>>(string&str){str.clear();char c=getchar();while(c==' '||c=='\n'||c=='\r')c=getchar();while(c!=' '&&c!='\n'&&c!='\r')str.push_back(c),c=getchar();return*this;}Reader(){}}cin;const char endl='\n';struct Writer{const int Setprecision=6;typedef int mxdouble;template<typename T>Writer&operator<<(T x){if(x==0){putchar('0');return*this;}if(x<0)putchar('-'),x=-x;static short sta[40];short top=0;while(x>0)sta[++top]=x%10,x/=10;while(top>0)putchar(sta[top]+'0'),top--;return*this;}Writer&operator<<(double x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(double)_;static short sta[40];short top=0;while(_>0)sta[++top]=_%10,_/=10;if(top==0)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;putchar('.');for(int i=0;i<Setprecision;i++)x*=10;_=x;while(_>0)sta[++top]=_%10,_/=10;for(int i=0;i<Setprecision-top;i++)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;return*this;}Writer&operator<<(long double x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(long double)_;static short sta[40];short top=0;while(_>0)sta[++top]=_%10,_/=10;if(top==0)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;putchar('.');for(int i=0;i<Setprecision;i++)x*=10;_=x;while(_>0)sta[++top]=_%10,_/=10;for(int i=0;i<Setprecision-top;i++)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;return*this;}Writer&operator<<(__float128 x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(__float128)_;static short sta[40];short top=0;while(_>0)sta[++top]=_%10,_/=10;if(top==0)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;putchar('.');for(int i=0;i<Setprecision;i++)x*=10;_=x;while(_>0)sta[++top]=_%10,_/=10;for(int i=0;i<Setprecision-top;i++)putchar('0');while(top>0)putchar(sta[top]+'0'),top--;return*this;}Writer&operator<<(char c){putchar(c);return*this;}Writer&operator<<(char*str){int cur=0;while(str[cur])putchar(str[cur++]);return*this;}Writer&operator<<(const char*str){int cur=0;while(str[cur])putchar(str[cur++]);return*this;}Writer&operator<<(string str){int st=0,ed=str.size();while(st<ed)putchar(str[st++]);return*this;}Writer(){}}cout;}using namespace Fastio;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
template<typename T>inline void chkmax(T &x,const T &y){ x=std::max(x,y); }
template<typename T>inline void chkmin(T &x,const T &y){ x=std::min(x,y); }
const int mod=998244353,maxn=200005;
int dsu[maxn],compnum;
int find(int x){ return dsu[x]==x?x:dsu[x]=find(dsu[x]); }
void merge(int x,int y){ x=find(x),y=find(y); if(x==y)return; dsu[x]=y,--compnum; }
int t1[maxn],t2[maxn],n,m,in[maxn],tag[maxn],q[maxn],ans[maxn];
int a[maxn],b[maxn],c[maxn];
vector<pii>g[maxn],e[maxn];
namespace seg{
	#define ls (o<<1)
	#define rs (o<<1|1)
	int t[maxn<<2];
	void init(){ memset(t,0,sizeof t); }
	void update(int o,int l,int r,int ql,int qr,int val){
		if(ql<=l&&qr>=r)return chkmax(t[o],val),void();
		int mid=(l+r)>>1;
		if(ql<=mid)update(ls,l,mid,ql,qr,val);
		if(qr>mid)update(rs,mid+1,r,ql,qr,val);
	}
	int query(int o,int l,int r,int pos){
		if(l==r)return t[o];
		int mid=(l+r)>>1;
		return max((pos<=mid)?query(ls,l,mid,pos):query(rs,mid+1,r,pos),t[o]);
	}
}
int id[maxn];
void Part1(){
	memset(in,0,sizeof in);
    F(u,1,n)for(auto it:g[u])++in[it.fi];
    int qL=1,qR=0;
    F(i,1,n)if(!in[i])q[++qR]=i;
    vector<int>vec;
    int tot=0;
    while(qL<=qR){
    	const int u=q[qL++];
    	vec.push_back(u);
    	id[u]=++tot;
    	for(auto it:g[u]){
    		const int v=it.fi;
    		if(!--in[v])q[++qR]=v;
    	}
    }
    seg::init();
    dF(i,n,1){
    	const int u=vec[i-1];
    	vector<pii>vec;
    	vec.push_back(mkp(0,0));
    	for(auto it:e[u]){
    		const int v=it.fi,w=it.se;
 			if(id[v]<id[u])vec.push_back(mkp(id[v],w));
    	}
    	sort(vec.begin(),vec.end());
    	const int siz=vec.size();
    	dF(j,siz-2,0)chkmin(vec[j].se,vec[j+1].se);
    	F(j,1,siz-1)seg::update(1,1,n,vec[j-1].fi+1,vec[j].fi,vec[j].se);
    }
    F(i,1,n)a[i]=seg::query(1,1,n,id[i]);
}
void Part2(){
	memset(in,0,sizeof in);
    F(u,1,n)for(auto it:e[u])++in[it.fi];
    int qL=1,qR=0;
    F(i,1,n)if(!in[i])q[++qR]=i;
    vector<int>vec;
    int tot=0;
    while(qL<=qR){
    	const int u=q[qL++];
    	vec.push_back(u);
    	id[u]=++tot;
    	for(auto it:e[u]){
    		const int v=it.fi;
    		if(!--in[v])q[++qR]=v;
    	}
    }
    seg::init();
    dF(i,n,1){
    	const int u=vec[i-1];
    	vector<pii>vec;
    	vec.push_back(mkp(0,0));
    	for(auto it:g[u]){
    		const int v=it.fi,w=it.se;
 			if(id[v]<id[u])vec.push_back(mkp(id[v],w));
    	}
    	sort(vec.begin(),vec.end());
    	const int siz=vec.size();
    	dF(j,siz-2,0)chkmin(vec[j].se,vec[j+1].se);
    	F(j,1,siz-1)seg::update(1,1,n,vec[j-1].fi+1,vec[j].fi,vec[j].se);
    }
    F(i,1,n)b[i]=seg::query(1,1,n,id[i]);
}
void solve(){
	cin>>n>>m,compnum=n;
	F(i,1,n)dsu[i]=i;
	int mntim=0;
	F(i,1,m){
		int u,v; cin>>u>>v;
		g[u].push_back(mkp(v,i));
		e[v].push_back(mkp(u,i));
		merge(u,v);
		if(!mntim&&compnum==1)mntim=i;
	}
	if(!mntim){
		F(i,1,n)cout<<"-1 ";
		return;
	}
	memset(in,0,sizeof in);
    F(u,1,n)for(auto it:g[u])++in[it.fi];
    int qL=1,qR=0;
    F(i,1,n)if(!in[i])q[++qR]=i;
    vector<int>vec;
    while(qL<=qR){
    	const int u=q[qL++];
    	vec.push_back(u);
    	for(auto it:g[u]){
    		const int v=it.fi;
    		if(!--in[v])q[++qR]=v;
    	}
    }
    int siz=0;
    vector<int>qwq=vec;
    reverse(vec.begin(),vec.end()),memset(in,0,sizeof in);
    for(int u:vec){
    	for(auto it:g[u]){
    		const int v=it.fi;
    		if(!in[v]++)--siz;
    	}
    	if(!siz++)t1[u]=1;
    }
    siz=0,memset(in,0,sizeof in),reverse(vec.begin(),vec.end());
    for(int u:vec){
    	for(auto it:e[u]){
    		const int v=it.fi;
    		if(!in[v]++)--siz;
    	}
    	if(!siz++)t2[u]=1;
    }
    F(i,1,n)if(t1[i]&&t2[i])tag[i]=1;
    F(i,1,n)if(!tag[i])ans[i]=-1;
    Part1(),Part2();
    F(i,1,n)if(tag[i])ans[i]=max(a[i],b[i]);
    F(i,1,n)cout<<ans[i]<<' ';
}
signed main(){
	const int zsy=1;
	F(____,1,zsy)solve();
}
```

---

## 作者：快斗游鹿 (赞：0)

先建图，如果 $x<y$ 就连边 $x\to y$。

首先考察一个点能唯一确定的充要条件，显然是比该点小的所有点到它都有路，它到比它大的所有点也都有路。容易联想到拓扑排序，事实上随便跑一个拓扑序后，你可以认为拓扑序小的就是更轻的，因为并不会出现无解判成有解的情况。

要判断的条件还不够直观，不过可以发现在只加入比某点小的点的情况下，如果除它外所有点都有出度，那么一定合法，这也是充要的。按拓扑序从小到大处理，只需要维护 $f_i$ 表示点 $i$ 拥有出度的最早时间即可快速求答案。可以使用可删堆等数据结构，时间复杂度单 $\log$。处理比某点大的点就按拓扑序从大到小处理即可。

---

