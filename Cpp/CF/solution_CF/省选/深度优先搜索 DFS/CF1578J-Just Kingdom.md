# Just Kingdom

## 题目描述

有一棵 $n + 1$ 个点，以 $0$ 号点为根的树，每个节点需要 $m_i$ 的钱。任何一个节点 **在任何时候** 得到总共为 $v$ 的钱的时候，进行以下过程：

1. 查看所有儿子，若还有 $cnt$ 个儿子没有得到足够的钱，那么给每个这样的儿子分发 $\frac{v}{cnt}$ 的钱。

2. 若 $cnt = 0$，则利用 $v$ 的钱尽量满足自己的需要。

3. 如果在 2 中仍然剩下了 $w$ 的钱，全部分给父亲。

注意，当上述儿子或者父亲得到钱的时候，会再次进行这个过程，直到最终全局停止钱的转移。

现在，我们需要对每个 $1\leq i\leq n$，求出 $0$ 号节点一开始获得最少多少的钱，能在上述过程结束之后，满足 $i$ 号节点的需要，这里我们对其他节点不作限制。

## 样例 #1

### 输入

```
5
0 2
1 2
0 1
1 1
0 5```

### 输出

```
11
7
3
5
11```

# 题解

## 作者：do_while_true (赞：12)

从底向上考虑，如果当前节点 $u$ 需要 $x$ 块钱，它的兄弟（拥有相同父亲的其他节点）为 $v$，那么它的父亲需要 $x+\sum \min(size_v,x)$ 块钱才能保证 $u$ 拿到 $x$ 块钱，其中 $size_v$ 是 $v$ 的子树点权和。

对于每一个节点，暴力往上跳是很完蛋的，树剖或者倍增跳也很难，因为跳很多级父亲后 $x$ 的增量根据 $x$ 大小的不同也会不一样。

考虑一次跳跃，如果有 $\min(size_v,x)=x$，那么 $x$ 至少翻倍，称这个点为倍增点。注意到一个点 $u$ 跳到根的过程中至多有 $\mathcal{O}(\log \sum m)$ 个倍增点，而在跳到倍增点之前的路径，其对 $x$ 的增量是很好预处理出然后快速求得的。

那么考虑一个倍增，$f_{u,i}$ 代表从 $u$ 跳到 $u$ 的 $2^i$ 级父亲，要求 $x\leq ?$ 才能保证不会遇到倍增点，这个是很好预处理的，那么处理一个点的答案的时候倍增找倍增点，然后跳到倍增点上，在倍增点上 $x$ 的增量统计可以提前给这个节点的儿子点权和排序然后二分来快速求得。

时间复杂度为 $\mathcal{O}(n\log n(\log n+\log m))$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;
typedef std::pair<ll, ll> pll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 300010;
int n, fa[N][20];
ll su[N][20], val[N], f[N][20];
vi eg[N];
vll s[N], va[N];
void dfs1(int x) {
	for(auto v : eg[x]) {
		dfs1(v);
		val[x] += val[v];
	}
}
void dfs2(int x) {
	for(int i = 1; i <= 19; ++i) fa[x][i] = fa[fa[x][i-1]][i-1];
	if(x) {
		if(va[fa[x][0]].size() == 1) f[x][0] = 0;
		else f[x][0] = va[fa[x][0]][(int)va[fa[x][0]].size()-1-(va[fa[x][0]][(int)va[fa[x][0]].size()-1] == val[x])];
		su[x][0] = s[fa[x][0]][(int)s[fa[x][0]].size()-1] - val[x];
		for(int i = 1; i <= 19; ++i)
			su[x][i] = su[x][i-1] + su[fa[x][i-1]][i-1],
			f[x][i] = Max(f[x][i-1], f[fa[x][i-1]][i-1] - su[x][i-1]);
	}
	for(auto v : eg[x]) dfs2(v);
}
signed main() {
//	freopen("data.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(fa[i][0]); read(val[i]);
		eg[fa[i][0]].pb(i);
	}
	dfs1(0);
	for(int i = 1; i <= n; ++i) va[fa[i][0]].pb(val[i]), s[fa[i][0]].pb(0);
	for(int i = 0; i <= n; ++i) {
		std::sort(va[i].begin(), va[i].end());
		for(int j = 0; j < (int)va[i].size(); ++j)
			s[i][j] = s[i][j-1+(j==0)] + va[i][j];
	}
	dfs2(0);
	for(int i = 1; i <= n; ++i) {
		int x = i; ll t = val[x];
		while(x) {
			for(int j = 19; ~j; --j)
				if(x && t >= f[x][j]) {
					t += su[x][j];
					x = fa[x][j];
				}
			if(x) {
				int p = std::upper_bound(va[fa[x][0]].begin(), va[fa[x][0]].end(), t) - va[fa[x][0]].begin() - 1;
				ll lt = t;
				if(p<0) {
					t += lt * s[fa[x][0]].size();
					t -= Min(val[x], lt);
				}
				else {
					t += lt * (s[fa[x][0]].size()-p-1);
					t += s[fa[x][0]][p];
					t -= Min(val[x], lt);
				}
				x = fa[x][0];
			}
		}
		printf("%lld\n", t);
	}
	return 0;
}
```

---

## 作者：Refined_heart (赞：7)

调了一下午……写一篇题解。

$\text{Solution:}$

首先考虑传送的过程，容易得到，传递过程的本质就是从小到大填儿子，如果这个填不满了，剩下的就平均分配。

那么，一个子树所需的流量显然就是 $siz[x].$ 如果一个点上面有 $w$ 的流量，那么它父亲的其他孩子也必然都有一个 $\min\{siz[v],w\}$ 的流量。

从上到下不好做，我们考虑能不能自底向上去推。由上述可以知道，一个点向上走，其父亲所需的流量对应会变为 $\sum _{v\in fa} \min\{w,siz[v]\}$

那么就可以模拟这个向上跳的过程了。

暴力？显然不太行，考虑继续发现性质。

首先对于所有 $siz[x]>w$ 的节点， $w$ 到其父亲上，就会至少加倍。因为 $\min\{w,siz[x]\}=w,$ 对应到其父亲上面 $w'\ge 2w.$

所以，一个点向上倍增变大的次数一定不超过 $\log v$ 次，也就是说，一个点跳到其父亲，不是将其父亲的所有孩子的 $siz$ 全部加起来的次数，不超过 $\log v$ 次。

那么，这个 “将所有兄弟的值全部加起来” 就可以启发我们做一点什么了，比如倍增优化。

而我们现在的任务就是处理哪些点是需要停下计算答案的。我们可以考虑一个倍增 $dp.$

设 $t[i][j]$ 表示节点 $i$ 向上跳 $2^j$ 步，节点 $i$ 的流量至少多大，才**不会被倍增。**

首先把上面说的一路加的数组求出来，设为 $s[i][j],$ 那么对应 $t$ 的转移式就应该是：

$$t[i][j]=\max\{t[i][j-1],t[fa[i][j-1]][j-1]-s[i][j-1]\}$$

意思就是要减去跳到 $f[i][j-1]$ 处增加的增量。

那么对于特殊计算的答案，把一个点的儿子按照 $siz$ 排序就可以二分处理答案了。

复杂度 $O(n\log v\log n)$

注意 $t$ 的细节（就是因为这个改了一下午） $t[i][0]$ 赋值的时候注意看看是不是恰好赋值成了他自己，如果是的话需要改为次大。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double db;
//#define int long long
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
#define poly vector<int>
#define Bt(a) bitset<a>
#define bc __builtin_popcount
#define pc putchar
#define ci const int&
#define DEBUG(x) printf("%d :",x),puts("--------------------------------------")
const int mod = 1e9 + 7;
const db eps = 1e-10;
const int inf = (1 << 30);
inline int Max(ci x, ci y) {return x > y ? x : y;}
inline int Min(ci x, ci y) {return x < y ? x : y;}
inline db Max(db x, db y) {return x - y > eps ? x : y;}
inline db Min(db x, db y) {return x - y < eps ? x : y;}
inline int Add(ci x, ci y, ci M = mod) {return (x + y) % M;}
inline int Mul(ci x, ci y, ci M = mod) {return 1ll * x * y % M;}
inline int Dec(ci x, ci y, ci M = mod) {return (x - y + M) % M;}
typedef pair<int, int> pii;
inline int Abs(int x) {return x < 0 ? -x : x;}
//char buf[1<<22],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char Obuf[105000],*O=Obuf;//Siz shoule be the size of Out File
int pst[30],ptop;
inline void Fprint(){fwrite(Obuf,1,O-Obuf,stdout);}
inline void Fwrite(long long x){
  if(x==0){*O++='0';return;}
  if(x<0)*O++='-',x=-x;ptop=0;
  while(x)pst[++ptop]=x%10,x/=10;
  while(ptop)*O++=pst[ptop--]+'0';
  if(O-Obuf>100000)Fprint(),O=Obuf;
}
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') w = -1;ch = getchar();}
    while (isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
    return s * w;
}
inline void write(long long x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
	pc(x % 10 + '0');
}
inline int qpow(int x, int y) {
    int res = 1;
    while (y) {if (y & 1)res = Mul(res, x);x = Mul(x, x);y >>= 1;}
    return res;
}
inline void cadd(int &x, int y) {x += y;}
inline void cmul(int &x, int y) {x *= y;}
inline void cmax(int &x, int y) {x = Max(x, y);}
inline void cmin(int &x, int y) {x = Min(x, y);}
const int N = 3e5+10;
const int SN = 20;
namespace Refined_heart{
	int pa[N],n,f[N][SN];
	long long s[N][SN],val[N],t[N][SN],mxv[N];
	int head[N],tot;
	struct E{int nxt,to;}e[N];
	inline void link(int x,int y){
		e[++tot]=(E){head[x],y};
		head[x]=tot;
	}
	vector<long long>G[N],pre[N];
	long long siz[N];
	void dfs1(int x){
		siz[x]=val[x];mxv[x]=0;f[x][0]=pa[x];
		for(int i=head[x];i;i=e[i].nxt){
			dfs1(e[i].to);
			siz[x]+=siz[e[i].to];
			G[x].pb(siz[e[i].to]);
		}
	}
	void dfs2(int x){
		for(int i=1;i<SN;++i)f[x][i]=f[f[x][i-1]][i-1];
		if(x){
			t[x][0]=mxv[pa[x]];
			if(siz[x]==t[x][0]&&G[pa[x]].size()>1)t[x][0]=G[pa[x]][(int)G[pa[x]].size()-2];
			else if(siz[x]==t[x][0])t[x][0]=0;
//			if(G[f[x][0]].size() == 1)t[x][0] = 0;
//			else t[x][0]=G[f[x][0]][(int)G[f[x][0]].size()-1-(G[f[x][0]][(int)G[f[x][0]].size()-1] == siz[x])];
			long long v=siz[pa[x]]-val[pa[x]];
			v-=siz[x];
			s[x][0]=v;
			for(int i=1;i<SN;++i)s[x][i]=s[x][i-1]+s[f[x][i-1]][i-1];
			for(int i=1;i<SN;++i)t[x][i]=max(t[x][i-1],t[f[x][i-1]][i-1]-s[x][i-1]);
		}
		for(int i=head[x];i;i=e[i].nxt){dfs2(e[i].to);}
	}
	void solve(){
		n=read();
		for(int i=1;i<=n;++i)pa[i]=read(),val[i]=read();
		for(int i=1;i<=n;++i){
			if(pa[i]==i)pa[i]=0;
			link(pa[i],i);
		}
		dfs1(0);
		for(int i=0;i<=n;++i)sort(G[i].begin(),G[i].end());
		for(int i=0;i<=n;++i){
			if(G[i].empty())continue;
			mxv[i]=G[i].back();
			pre[i].pb(G[i][0]);
			for(int j=1;j<(int)G[i].size();++j){
				long long v=pre[i].back();
				v+=G[i][j];
				pre[i].pb(v);
			}
		}
		dfs2(0);
		for(int i=1;i<=n;++i){
			int x=i;
			long long now=siz[i];
			while(x){
				for(int ii=SN-1;~ii;--ii){
					if(x&&now>=t[x][ii]){
						now+=s[x][ii];
						x=f[x][ii];
					}
				}
				if(!x)break;
				x=pa[x];
				int pos=upper_bound(G[x].begin(),G[x].end(),now)-G[x].begin();
				long long sn=now;
				if(pos>0)now+=pre[x][pos-1];
				now+=1ll*((int)G[x].size()-pos-1)*sn;
			}
			Fwrite(now);*O++='\n';
		}
		Fprint();
	}
}
signed main(){
// 	freopen("in.txt","r",stdin);
// 	freopen("My.out","w",stdout);
	Refined_heart::solve();
	return 0;
}

```


---

## 作者：Carotrl (赞：5)

来点好想好写的做法！

先考虑对一个单点 $x$ 算答案。假设 $i$ 子树内价值和为 $sum_i$。首先，为了让 $x$ 填满，我们肯定要把 $x$ 子树填满，花费 $y=sum_x$。接着考虑 $x$ 的父亲 $u$，因为一个点向儿子是平分，所以 $u$ 的每个儿子 $v$ 应该都被分到 $y$。但是因为多了的钱会返还父亲，所以就等于一个点 $v$ 最多向子树内传 $sum_v$，多了就不需要了。于是 $x$ 向父亲 $u$ 跳一步，花费会从 $y$ 变为 $\sum\limits_{v}\min(y,sum_v)$。不停向上跳到根，我们就得到了 $x$ 的答案。

现在我们希望能自底向上维护所有答案。到 $u$ 时维护一个答案集合 $S_u$，每个元素是一个二元组 $(x,y)$，表示 $y$ 跳上来到 $u$ 时的答案为 $x$。我们在 $k$ 处需要进行的操作是合并所有儿子集合，令所有二元组的 $x \gets \sum\limits_{v \in son_u}\min(x,sum_v)$。最后再插入 $(sum_u,u)$。

考虑如何快速维护。将所有 $sum_v$ 排序，我们发现操作实际上是对一个值域区间内的所有 $x$，令 $x \gets kx+b$。有一个很好的性质就是一个 $x$ 只会进行不超过 $\log nm$ 次 $k \ge 2$ 的操作。于是我们可以用 set 维护集合 $S_u$，暴力进行所有 $k \ge 2$ 的操作，并对 $k=1$ 的操作直接打一个加法 tag。合并的时候启发式合并就行。

总复杂度 $O(n \log n \log nm)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define vec vector<int>
#define pb push_back
#define int long long
#define M 1000000007
void in(int &x){
    int f=1;x=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-')c=getchar();
    if(c=='-')f=-1,c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    x*=f;
}
int t,n,m,k,x,y,a[300005],pa[300005],res[300005];
vector<int>g[300005];
multiset<pi>s[300005];
int ad[300005],sum[300005],d[300005],e;
void dfs(int k){
	sum[k]=a[k];
	for(int v:g[k]){
		dfs(v);sum[k]+=sum[v];
		if(s[k].size()<s[v].size())swap(s[v],s[k]),swap(ad[k],ad[v]);
		for(pi x:s[v])s[k].insert({x.first+ad[v]-ad[k],x.second});
	}
	e=0;for(int v:g[k])d[++e]=sum[v];
	sort(d+1,d+1+e);vector<pi>f;int c=0;
	for(int i=1;i<e;c+=d[i],i++){
		while(s[k].size()){
		    int x=(*s[k].begin()).first+ad[k];
		    int y=(*s[k].begin()).second;
			if(x<d[i]){
			    s[k].erase(s[k].begin());
				f.pb({(e-i+1)*x+c,y});
			}
			else break;
		}
	}
	ad[k]+=c;for(auto [x,y]:f)s[k].insert({x-ad[k],y});
	s[k].insert({sum[k]-ad[k],k});
}
signed main(){
	in(n);
	for(int i=1;i<=n;i++){
		in(pa[i]);in(a[i]);
		g[pa[i]].pb(i);
	}
	dfs(0);
	for(auto [x,y]:s[0])res[y]=x;
	for(int i=1;i<=n;i++)printf("%lld\n",res[i]+ad[0]);
}
```

---

## 作者：Prean (赞：4)

容易发现分配给一个子树的钱只要够了就会移除

具体来讲，如果一个结点被分配到了 $x$ 块钱，那么有两种情况：

> 1. 子树全部都拿到了该拿的钱，自己拿到了一部分或者全部拿到了
> 2. 对于每个儿子，其子树拿到的钱均不超过某个值

对于情况 1 容易构造使其不发生，对于情况 2 可以每次二分。

$O(n^2\log V)$ 的算法就是每次跳父亲，然后计算当前节点应该拿多少钱。

考虑对于一个节点 $u$ 维护一颗平衡树，平衡树上存着子树内所有节点在当前节点的答案。

对于 $u$ 的某个儿子应该拿到 $x$ 块钱，那么跳了父亲之后他应该拿到 $x+\sum\min(sum_v,x)$ 的钱。

容易发现对于 $u$ 平衡树中每个元素更新后的相对大小是不变的，所以可以更新之后与兄弟的平衡树进行启发式合并。但是更新的复杂度过高。

假设对于 $x$ 在 $u$ 的兄弟中满足 $x>sum$ 比其小的 $sum$ 之和为 $S$，满足 $x\leq sum$ 的节点数量为 $k$（包括 $u$），那么更新后其值为 $x\times k+S$。

可以发现先进行启发式合并后再更新元素的值与先更新再启发式合并是相同的，这样一来复杂度就降低到了 $O(n\log^2n)$。
```cpp
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<ctime>
typedef long long ll;
const int M=3e5+5;
int n,dfe,h[M],f[M],rt[M],siz[M];ll S[M];
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s^48),isdigit(s=getchar()));return n;
}
inline void write(ll n){
	static char s[20];int top(0);while(s[++top]=n%10^48,n/=10);while(putchar(s[top]),--top);
}
struct line{
	ll k,b;
	line(const ll&k=1,const ll&b=0):k(k),b(b){}
	inline line operator()(const line&it){
		return line(k*it.k,k*it.b+b);
	}
	inline ll operator()(const ll&x){
		return k*x+b;
	}
};
namespace fhq{
	int rnd[M],chi[M][2];ll w[M];line tag[M];
	inline void nnd(const int&u,const ll&V){
		rnd[u]=rand()*rand();chi[u][0]=chi[u][1]=0;tag[u]=line();w[u]=V;
	} 
	inline void pushdown(const int&u){
		const int&ls=chi[u][0],&rs=chi[u][1];
		if(ls)w[ls]=tag[u](w[ls]),tag[ls]=tag[u](tag[ls]);
		if(rs)w[rs]=tag[u](w[rs]),tag[rs]=tag[u](tag[rs]);
		tag[u]=line();
	}
	inline void split(const int u,const ll&V,int&x,int&y){
		if(!u)return void(x=y=0);pushdown(u);
		if(w[u]<=V)split(chi[x=u][1],V,chi[u][1],y);
		else split(chi[y=u][0],V,x,chi[u][0]);
	}
	inline int merge(const int q,const int p){
		if(!q||!p)return q|p;pushdown(q);pushdown(p);
		if(rnd[q]<rnd[p])return chi[q][1]=merge(chi[q][1],p),q;
		else return chi[p][0]=merge(q,chi[p][0]),p;
	}
	inline void ins(const int u,int&rt){
		int x(0),y(0);split(rt,w[u],x,y);rt=merge(merge(x,u),y);
	}
	inline void Mrg(int u,int&rt){
		if(!u)return;pushdown(u);Mrg(chi[u][0],rt);Mrg(chi[u][1],rt);chi[u][0]=chi[u][1]=0;ins(u,rt);
	}
}
using namespace fhq;
struct Edge{
	int v,nx;
}e[M];
inline void Add(const int&u,const int&v){
	e[++dfe]=(Edge){v,h[u]};h[u]=dfe;
}
inline void DFS(const int&u){
	static int m,s[M];ll sum(0);int r(0);
	for(int E=h[u];E;E=e[E].nx){
		const int&v=e[E].v;DFS(v);S[u]+=S[v];
		int x=rt[u],y=rt[v];if(siz[u]>siz[v])x^=y^=x^=y;Mrg(x,rt[u]=y);siz[u]+=siz[v];
	}
	for(int E=h[u];E;E=e[E].nx)s[++m]=e[E].v;std::sort(s+1,s+m+1,[](int x,int y){return S[x]<S[y];});
	for(int i=1;i<=m;sum+=S[s[i++]]){
		int x(0),y(0);line f(m-i+1,sum);split(rt[u],S[s[i]],x,y);rt[u]=y;
		w[x]=f(w[x]);tag[x]=f(tag[x]);r=merge(r,x);
	}
	rt[u]=r;m=0;if(u)nnd(u,S[u]),rt[u]=merge(rt[u],u),++siz[u];
}
inline void dfs(const int&u){
	if(!u)return;pushdown(u);dfs(chi[u][0]);dfs(chi[u][1]);
}
signed main(){
	srand(time(NULL));n=read();for(int i=1;i<=n;++i)Add(f[i]=read(),i),S[i]=read();DFS(0);dfs(rt[0]);
	for(int u=1;u<=n;++u)write(w[u]),putchar('\n');
}
```

---

## 作者：lfxxx (赞：1)

我们考虑挖掘一些性质以一下简化这个题目中过程的运行方式。

1. 一个子树中只会吃掉等价于子树内 $m$ 和的权值。

这是显然的，权值不会凭空消失，多了会回到父亲。

2. 对于一个父亲 $u$ 以及其所有儿子 $v_1,v_2,\dots,v_k$ 而言，假若父亲得到了极小量的权值，那么所有没有被填满的儿子会得到相同的权值，填满的儿子不会得到权值。

这也是显然的。

3. 对于一个父亲 $u$ 以及其所有儿子 $v_1,v_2,\dots,v_k$ 而言，不断往父亲加入极小量的权值，每个儿子的权值分配比发生变化当且仅当一个儿子发生了被填满。

由性质 $2$ 不难得到性质 $3$。

4. 对于一个父亲 $u$ 以及其所有儿子 $v_1,v_2,\dots,v_k$ 而言，一开始就往 $u$ 加入 $a$ 的权值等价于不断地往 $u$ 加入总和为 $a$ 的权值。

证明考虑假若权值 $a$ 不会使得一个子树被填满，则显然成立，否则被填满的子树会把权值返还到 $u$，此时等价于一点点加加到 $u$ 还剩下返还的权值，后面的过程自然也是一样的。

至此我们可以很好的简化题目中过程的运行方式，当点 $u$ 得到了 $x$ 的权值时，一点点将权值按照没有被填满的儿子数分之一的比例分给所有没有被填满的儿子，直到至少一个儿子被填满。

接下来考虑快速维护每个点被填满需要的代价，不妨设计状态 $dp_u$ 表示点 $u$ 被填满需要的代价，我们在树上 dfs 的过程中来动态的维护 $dp_u$ 的变化，也就是 dfs 到点 $u$ 时动态的维护 $v \in sub_u$ 的 $dp_v$ 表示至少要往点 $u$ 放多少权值才能把 $v$ 填满，注意到将 $w \in sub_v,v \in son_u$ 的 $dp_w$ 合并上来时，新的 $dp_w$ 等价于要往点 $u$ 放多少权值，点 $u$ 的儿子 $v$ 才会获得等于原来的 $dp_w$ 的权值，你发现合并关乎其来自哪个儿子，不是很牛，但是我们深入思考可以再发现一个性质：

6. $dp_w$ 的值与 $v$ 无关。

原因考虑一点点往 $u$ 加入权值时，对于某个时刻任意一个未被填满的子树而言，其与其他未被填满的均是等价的，而当 $dp_w$ 一定小于等于填满子树 $v$ 需要的权值，且就算刚刚好填满也可以视作子树 $v$ 未被填满，再深入的分析点 $u$ 将权值传下去的过程，你发现 $dp_w$ 的变化是一个只与 $u$ 的所有子树权值之和排序后的结果有关的一次分段单调递增函数，所以可以用 fhq treap 来维护，具体而言就是以 $dp$ 值同时为键值与权值，由于是一个单调递增函数的缘故，在将 fhq treap 分类为若干段并打上标记后其内所有节点的键值相对大小关系不变，故可以直接合并回来，合并两个子树的 fhq treap 可以考虑启发式合并，那么就做到了 $O(n \log^2 n)$。


```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
#define int long long
const int maxn = 3e5+114;
struct node{
    int rk,v;
    int k,b;
    int ls,rs;
    node(){
        rk=v=b=ls=rs=0;
        k=1;
    }
}tr[maxn];
int n;
int sz[maxn],siz[maxn];
int fa[maxn];
int root[maxn];
vector<int> son[maxn];
mt19937 rd(time(0));
void pushdown(int cur){
    if(tr[cur].k!=1||tr[cur].b!=0){
        if(tr[cur].ls!=0){
            tr[tr[cur].ls].v=tr[tr[cur].ls].v*tr[cur].k+tr[cur].b;
            tr[tr[cur].ls].k*=tr[cur].k;
            tr[tr[cur].ls].b=tr[tr[cur].ls].b*tr[cur].k+tr[cur].b;
        }
        if(tr[cur].rs!=0){
            tr[tr[cur].rs].v=tr[tr[cur].rs].v*tr[cur].k+tr[cur].b;
            tr[tr[cur].rs].k*=tr[cur].k;
            tr[tr[cur].rs].b=tr[tr[cur].rs].b*tr[cur].k+tr[cur].b;
        }
        tr[cur].k=1,tr[cur].b=0;
    }
}
int merge(int u,int v){
    if(u==0||v==0) return u+v;
    pushdown(u),pushdown(v);
    if(tr[u].rk>tr[v].rk){
        tr[u].rs=merge(tr[u].rs,v);
        return u;
    }else{
        tr[v].ls=merge(u,tr[v].ls);
        return v;
    }
}
void split(int cur,int &l,int &r,int k){//<=k
    if(cur==0){
        l=r=0;
        return ;
    }
    pushdown(cur);
    if(tr[cur].v<=k){
        l=cur;
        split(tr[l].rs,tr[l].rs,r,k);
    }else{
        r=cur;
        split(tr[r].ls,l,tr[r].ls,k);
    }
}
void dfs(int u){
    siz[u]=1;
    if(son[u].size()==0){
        root[u]=u;
        tr[u]=node();
        tr[u].rk=rd();
        tr[u].v=sz[u];
        return ;
    }
    vector<int> val;
    for(int v:son[u]){
        dfs(v);
        sz[u]+=sz[v];
        int x=root[u],y=root[v];
        if(siz[u]<siz[v]) swap(x,y);
        siz[u]+=siz[v];
        queue<int> q;
        q.push(y);
        while(q.size()>0){
            int tp=q.front();
            q.pop();
            pushdown(tp);
            if(tr[tp].ls!=0) q.push(tr[tp].ls);
            if(tr[tp].rs!=0) q.push(tr[tp].rs);
            tr[tp].ls=tr[tp].rs=0;
            tr[tp].rk=rd();
            int L=0,R=0;
            split(x,L,R,tr[tp].v);
            x=merge(merge(L,tp),R);            
        }
        root[u]=x;
        val.push_back(sz[v]);
    }
    sort(val.begin(),val.end());
    vector< pair< pair<int,int>, pair<int,int> > > seq;//(l,r) (k,b) l<x<=r x<-kx+b
    int cst=0;
    int lst=0;
    for(int i=1;i<val.size();i++){
        if(val[i]!=val[i-1]){
            //x<-cst+(x-val[lst-1])*(son[u].size()-lst) val[lst-1]<x<=val[lst]
            seq.push_back(make_pair(make_pair(lst==0?0:val[lst-1],val[lst]),make_pair(son[u].size()-lst,cst-(lst==0?0:val[lst-1])*(son[u].size()-lst))));
            cst+=(val[i-1]-(lst==0?0:val[lst-1]))*(son[u].size()-lst);
            lst=i;
        }
    }
    seq.push_back(make_pair(make_pair(lst==0?0:val[lst-1],val[lst]),make_pair(son[u].size()-lst,cst-(lst==0?0:val[lst-1])*(son[u].size()-lst))));
    vector<int> tree;
    for(pair< pair<int,int>, pair<int,int> > now:seq){
        int x=0,y=0,z=0;
        split(root[u],x,y,now.first.first-1);
        split(y,y,z,now.first.second);
        tr[y].v=tr[y].v*now.second.first+now.second.second;
        tr[y].k*=now.second.first;
        tr[y].b=tr[y].b*now.second.first+now.second.second;
        tree.push_back(y);
        root[u]=merge(x,z);
    }
    tr[u]=node();
    tr[u].rk=rd();
    tr[u].v=sz[u];
    tree.push_back(u);
    for(int x:tree) root[u]=merge(root[u],x);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    n++;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        fa[i]++;
        cin>>sz[i];
        son[fa[i]].push_back(i);
    }
    dfs(1);
    queue<int> q;
    q.push(root[1]);
    while(q.size()>0){
        int u=q.front();
        q.pop();
        pushdown(u);
        if(tr[u].ls!=0) q.push(tr[u].ls);
        if(tr[u].rs!=0) q.push(tr[u].rs);
    }
    for(int i=2;i<=n;i++) cout<<tr[i].v<<'\n';
    return 0;
}
```

---

## 作者：xxr___ (赞：0)

#### 来一篇尽量详细的题解。
首先明确几点：
- 假如想让 $x$ 满足条件，那么 $x$ 子树必须都满足条件，不然会优先满足子树。
- 若存在一个点 $u$ 满足 $fa_u→u$ 的流量是 $w$ 那么 $fa_u→v,v\in son_{fa_u}∧v\ne u$ 均满足 $fa_u→v$ 的流量是大于等于 $\min(m_v,w)$ 的，定义得。
- 如果满足存在 $v$ 满足 $\min(m_v,w)=w$ 那么 $fa_u$ 的总流量至少是 $u$ 的总流量的两倍，也就是大于等于 $2\times w$。
- 实际上 $w$ 变成 $w→k\times w,k\ge 2$ 最多进行 $\log(\sum w)$ 次的。

然后知道了这些，因为有指数增长的趋势，自然往倍增上去靠，我们设 $fa_{i,j}$ 表示 $i$ 的 $2^j$ 级别祖先，设 $vl_i$ 表示 $fa_{i,0}$ 中不包含 $i$ 这个子树最大的子树大小，设 $res_i$ 表示 $fa_{i,0}$ 中不包含 $i$ 这个子树其他子树的子树大小之和，然后 $mx_{i,j}$ 表示 $i$ 到 $i$ 的 $2^j$ 路径上最大的 $vl_x$ 然后 $sum_{i,j}$ 表示 $i$ 到 $i$ 的 $2^j$ 祖先路径上 $res_x$ 的和，这些都是好求的，直接倍增即可。

知道了这些，我们考虑答案，显然就是如果每次找到第一个 $v$ 满足 $vl_v>x'$ 其中 $x'$ 表示当前的 $x$。把 $v$ 子树拿出来单独计算贡献，可以使用前缀和来计算，这里有个细节，为了防止溢出，可以先加入一个很小的值，最后再加回去即可。

时间复杂度的话，我们刚刚说的性质，最多会单独计算 $\log(\sum w)$ 次，每次可以二分查找，总的复杂度是 $O(n\log n\log V)$ 的，常数较小跑的很快。

[代码](https://codeforces.com/problemset/submission/1578/311625349)

---

## 作者：rainygame (赞：0)

首先思考钱到底会怎么分配，一个子树只会吃掉和它自己权值和相等的钱，因为多余的钱会回到父亲。对于一个点 $x$，如果它被填满，那么它的子树也一定会被填满，这需要 $sum_x$ 的钱，其次因为钱是从父亲那里平分的，所以每个子树都会得到 $sum_x$ 的钱，但因为其它子树的钱也可能会返还给父亲，所以对于一个在 $v$ 处需要 $y$ 才能填满的 $x$ 点，其实在 $v$ 的父亲 $u$ 处只需要 $\sum\limits_{w\in son_u}\min\{y,sum_w\}$。

直接做是 $O(n^2)$ 的。如果自下而上的维护所有答案，设到 $u$ 是维护了二元组集合 $S_u$，每个元素形如 $(x,y)$ 表示 $x$ 到 $u$ 时的答案为 $y$，那么需要的操作就是对于所有元素，令 $y\leftarrow\sum\limits_{w\in son_u}\min\{y,sum_w\}$，最后记得插入 $(sum_u,u)$。

现在的问题是如何快速做 $y\leftarrow\sum\limits_{w\in son_u}\min\{y,sum_w\}$ 的操作，设儿子序列按 $sum$ 升序排序后为 $b$，那么对于一个满足 $sum_{b_{i-1}}<y\le sum_{b_i}$ 的 $y$，它最后的结果就是 $(k-i+1)y+\sum\limits_{j=1}^{i-1}sum_{b_j}$（$k$ 表示儿子个数）。但是对于每个 $(x,y)$ 这样做复杂度也不会更优。

注意到当给出 $\sum m_i$ 的钱时，所有点必定被填满，且对于一次 $k-i+1>1$ 的变化，$y$ 必定翻倍，所以 $k-i+1>1$ 的情况对于每个 $y$ 只有 $O(\log \sum m_i)$ 次，那么对于 $k-i+1>1$ 的情况，可以暴力做。对于 $k-i+1=1$ 的情况，相当于所有的节点都被加上了一次，维护一个加 tag 即可。注意将子树合并到父亲需要启发式合并。

时间复杂度 $O(n \log \sum m_i)$。

[submission](https://codeforces.com/contest/1578/submission/302221309)

---

## 作者：mskqwq (赞：0)

正着做不太好做，考虑倒推。设 $u$ 子树内 $m$ 的和为 $s_u$，如果要满足 $u$ 的需求，那么 $u$ 必须得到 $s_u$ 的钱，$u$ 的父亲至少需要 $\sum \min(s_v,s_u)$ 的钱，其中 $v$ 是 $fa_u$ 的所有儿子。

下文的 $v$ 省略 $v$ 为 $u$ 的兄弟节点且 $v\neq u$ 这一条件。 

于是有了一个暴力做法：令 $x$ 初始为 $s_u$，让 $u$ 不断跳父亲，然后让 $x$ 变为 $\sum \min(s_v,x)$。接着考虑分讨 $\min$ 取到了哪，若全取到了 $s_v$ 是好做的，若有一个取到了 $x$，那么 $x$ 至少变成 $2x$，也就是说这样的位置只有 $\log$ 个。

考虑如何找到所有这样的位置，记 $a_u=\sum s_v$，$b_u$ 为所有 $u$ 到根所有 $a_v$ 的和，$mx_u=\max s_v$。假如 $u$ 在跳到 $p$ 时会让 $\min$ 取到 $x$，那么就有 $mx_p+b_p > x+b_u$，可以倍增维护左边的最大值。最后对每个点将它的儿子按 $s$ 排序后求一个前缀和，当找到一个 $p$ 的时候就在它的儿子里二分第一个 $>x$ 的位置就行。

注意代码中的变量名与文中意义不同。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<ll,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=3e5+10,mod=998244353;
int n,fa[N][20];ll a[N],b[N],f[N][20],s[N];
vector<ll> g[N],G[N];
void dfs(int u){for(int v:g[u])dfs(v),a[u]+=a[v];}
void misaka(){
    n=read()+1;
    rep(i,2,n){
        fa[i][0]=read()+1;a[i]=read();
        g[fa[i][0]].eb(i);
    }
    dfs(1);
    rep(i,1,n){
        ll sum=0;
        for(int j:g[i]) sum+=a[j];
        for(int j:g[i]) s[j]=sum-a[j];
    }
    rep(i,1,n) s[i]+=s[fa[i][0]];
    rep(i,1,n){
        int lst=0;
        sort(rg(g[i]),[](int x,int y){return a[x]<a[y];});
        for(int j:g[i]){
            G[i].eb(a[j]);
            f[j][0]=s[j];
            if(j^g[i].back()) f[j][0]+=a[g[i].back()];
            else if(g[i].size()>1) f[j][0]+=a[g[i][g[i].size()-2]];
            b[j]=a[j]+b[lst],lst=j;
        }
    }
    rep(j,1,19)rep(i,1,n){
        fa[i][j]=fa[fa[i][j-1]][j-1];
        f[i][j]=max(f[i][j-1],f[fa[i][j-1]][j-1]);
    }
    rep(i,2,n){
        int x=i;ll nw=a[x];
        while(f[x][19]>nw+s[x]){
            _rep(j,19,0)if(f[x][j]<=nw+s[x]){
                int F=fa[x][j];
                nw+=s[x]-s[F],x=F;
            }
            int F=fa[x][0];
            int p=upper_bound(rg(G[F]),nw)-G[F].begin();
            nw+=(p>0?b[g[F][p-1]]:0)+nw*(g[F].size()-p-1);
            x=F;
        }
        printf("%lld\n",nw+s[x]);
    }
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

