# Red-Black Cobweb

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833D/02351dacdd2e3ec0c6e1873274a6e20cc219ce83.png)Slastyona likes to watch life of nearby grove's dwellers. This time she watches a strange red-black spider sitting at the center of a huge cobweb.

The cobweb is a set of $ n $ nodes connected by threads, each of the treads is either red of black. Using these threads, the spider can move between nodes. No thread connects a node to itself, and between any two nodes there is a unique sequence of threads connecting them.

Slastyona decided to study some special qualities of the cobweb. She noticed that each of the threads has a value of clamminess $ x $ .

However, Slastyona is mostly interested in jelliness of the cobweb. Consider those of the shortest paths between each pair of nodes on which the numbers of red and black threads differ at most twice. For each such path compute the product of the clamminess of threads on the path.The jelliness of the cobweb is the product of all obtained values among all paths. Those paths that differ by direction only are counted only once.

Of course, this number can be huge, so Slastyona asks you to compute the jelliness of the given cobweb and print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example there are $ 4 $ pairs of nodes such that the numbers of threads of both colors on them differ at most twice. There pairs are $ (1,3) $ with product of clamminess equal to $ 45 $ , $ (1,5) $ with product of clamminess equal to $ 45 $ , $ (3,4) $ with product of clamminess equal to $ 25 $ and $ (4,5) $ with product of clamminess equal to $ 25 $ . The jelliness of the cobweb is equal to 1265625.

## 样例 #1

### 输入

```
5
1 2 9 0
2 3 5 1
2 4 5 0
2 5 5 1
```

### 输出

```
1265625
```

## 样例 #2

### 输入

```
8
1 2 7 1
2 3 4 1
3 4 19 1
5 1 2 0
6 2 3 0
7 3 3 0
8 4 4 0
```

### 输出

```
452841614
```

# 题解

## 作者：p_b_p_b (赞：10)

[$$\large \color{purple} My \; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10499952.html)

-------------------------

## 思路

看到树上路径的统计，容易想到点分治。

虽然只有一个限制，但这个限制比较麻烦，我们把它拆成两个。

设黑边有$a$条，白边有$b$条，那么有

$$2a\geq b$$
$$2b\geq a$$

合并两条边时，设原有的是$(a,b)$，要加入的是$(A,B)$，那么有

$$2(a+A)\geq b+B \Leftrightarrow 2A-B\geq b-2a$$
$$2(b+B)\geq a+A \Leftrightarrow 2B-A\geq a-2b \Leftrightarrow A-2B\leq 2b-a$$

但现在有两个限制，似乎还要CDQ分治，非常麻烦。

注意到一个性质：只要不满足第一条，必然满足第二条，反之亦然。

那么可以用两个树状数组维护前缀积，每次用满足第一条的除以不满足第二条的即可。

复杂度$O(n\log ^2 n)$？$O(n\log ^3 n)$？反正比那些CDQ分治的要快就对了。

------------------------------

## 代码

```cpp
#include<bits/stdc++.h>
clock_t t=clock();
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 101100
    #define mod 1000000007ll
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    char __sr[1<<21],__z[20];int __C=-1,__Z=0;
    inline void __Ot(){fwrite(__sr,1,__C+1,stdout),__C=-1;}
    inline void print(register int x)
    {
    	if (__C>1<<20) __Ot(); if (x<0) __sr[++__C]='-',x=-x;
    	while (__z[++__Z]=x%10+48,x/=10);
    	while (__sr[++__C]=__z[__Z],--__Z);__sr[++__C]='\n';
    }
    void file()
    {
        #ifndef ONLINE_JUDGE
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime()
    {
        #ifndef ONLINE_JUDGE
        cout<<(clock()-t)/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n;
struct hh{int t;ll w;int nxt;int col;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t,ll w,int col)
{
	edge[++ecnt]=(hh){t,w,head[f],col};
	head[f]=ecnt;
	edge[++ecnt]=(hh){f,w,head[t],col};
	head[t]=ecnt;
}

int T;
struct BIT
{
	ll prod[sz<<2];
	int size[sz<<2];
	int mark[sz<<2];
	void mul(int x,ll w)
	{
		x+=n*2;
		while (x<=n*4) 
		{
			if (mark[x]!=T) size[x]=0,prod[x]=1;
			++size[x],prod[x]=prod[x]*w%mod;mark[x]=T;
			x+=(x&(-x));
		}
	}
	void query(int x,ll &w1,int &w2)
	{
		w1=1,w2=0;x+=n*2;
		while (x) 
		{
			if (mark[x]==T) w1=w1*prod[x]%mod,w2+=size[x];
			x-=(x&(-x));
		}
	}
}T1,T2;

ll ans=1;
#define v edge[i].t
bool vis[sz];
int size[sz],mn,root,tot;
void findroot(int x,int fa)
{
	size[x]=1;
	int S=-1;
	go(x) if (v!=fa&&!vis[v])
	{
		findroot(v,x);
		size[x]+=size[v];
		chkmax(S,size[v]);
	}
	chkmax(S,tot-size[x]);
	if (chkmin(mn,S)) root=x;
}
struct hhh{int aa,bb;ll w;};
hhh s[sz];int cnt;
void dfs(int x,int fa,int a,int b,ll w)
{
	s[++cnt]=(hhh){2*a-b,2*b-a,w};
	go(x) if (v!=fa&&!vis[v])
	{
		if (edge[i].col) dfs(v,x,a,b+1,w*edge[i].w%mod);
		else dfs(v,x,a+1,b,w*edge[i].w%mod);
	}
}
void calc(int x)
{
	++T;T1.mul(0,1);T2.mul(0,1);
	go(x) if (!vis[v])
	{
		cnt=0;
		if (edge[i].col) dfs(v,0,0,1,edge[i].w);
		else dfs(v,0,1,0,edge[i].w);
		rep(i,1,cnt)
		{
			ll w1;int w2;
			T1.query(s[i].aa,w1,w2);
			ans=ans*w1%mod*ksm(s[i].w,w2)%mod;
			T2.query(-s[i].bb-1,w1,w2);
			ans=ans*inv(w1*ksm(s[i].w,w2)%mod)%mod;
		}
		rep(i,1,cnt) T1.mul(-s[i].aa,s[i].w),T2.mul(s[i].bb,s[i].w);
	}
}
void solve(int x)
{
	vis[x]=1;
	calc(x);
	int all=tot;
	go(x) if (!vis[v])
	{
		tot=size[v];if (size[v]>size[x]) tot=all-size[x];mn=1e9;
		findroot(v,0);
		solve(root);
	}
}
#undef v

int main()
{
	file();
	int x,y,z,c;
	read(n);
	rep(i,1,n-1) read(x,y,z,c),make_edge(x,y,z,c);
	tot=n;mn=1e9;findroot(1,0);
	solve(root);
	cout<<ans;
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：4)

点分治，主要注意到限制可以前缀和差分，用树状数组维护前缀和与前缀积。

做法的可行性：w/b<1/2和w/b>2的路径没有交

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
#define lowbit(x) x&(-x)
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int INF=1e9,N=2e5+5,mod=1e9+7;
struct edge{
	int link,next,val,col;
}e[N<<1];
bool vis[N];
int ans,tot,T,Fa[N],size[N],All,mn,n,rt,head[N];
inline void add_edge(int u,int v,int w,int c){
	e[++tot]=(edge){v,head[u],w,c}; head[u]=tot;
}
inline void insert(int u,int v,int w,int c){
	add_edge(u,v,w,c); add_edge(v,u,w,c);
}
inline void init(){
	n=read();
	for (int i=1;i<n;i++) {
		int u=read(),v=read(),w=read(),c=read();
		insert(u,v,w,c);
	}
}
struct tree{
	int mark[N<<2],bit1[N<<2],bit2[N<<2];
	void update(int x,int v){
		x+=n*2;
		for (;x<=n*4;x+=lowbit(x)){
			if (mark[x]!=T){
				mark[x]=T; bit1[x]=0; bit2[x]=1;
			}
			bit1[x]++; bit2[x]=1ll*bit2[x]*v%mod;
		}
	} 
	void query(int x,int &v1,int &v2){
		x+=n*2;
		for (;x;x-=lowbit(x)){
			if (mark[x]==T){
				v2+=bit1[x];
				v1=1ll*v1*bit2[x]%mod;
			}
		}
	}
}T0,T1;
void getroot(int u,int fa){
	size[u]=1; int mx=0; Fa[u]=fa;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=fa&&!vis[v]){
			getroot(v,u); size[u]+=size[v];
			mx=max(mx,size[v]);
		}
	} 
	mx=max(All-size[u],mx);
	if (mx<mn) mn=mx,rt=u;
}
struct node{
	int a,b,v;
}q[N];
void dfs(int u,int fa,int a,int b,int v){
	q[++tot]=(node){a*2-b,b*2-a,v};
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!vis[v]&&v!=fa){
			dfs(v,u,a+(e[i].col),b+(!e[i].col),1ll*v*e[i].val%mod);
		} 
	} 
}
inline int pow(int x,int k){
	int y=1;
	for (;k;k>>=1,x=1ll*x*x%mod){
		if (k&1) y=1ll*y*x%mod;
	}
	return y;
}
inline void calc(int u){
	T++; T0.update(0,1); T1.update(0,1);
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link; 
		if (!vis[v]){
			tot=0; dfs(v,u,e[i].col,!e[i].col,e[i].val);
			for (int j=1;j<=tot;j++){
				int s=0,t=0,tmp=1;
				T0.query(q[j].a,ans,s);
				T1.query(-q[j].b-1,tmp,t);
				ans=1ll*ans*pow(tmp,mod-2)%mod;
				ans=1ll*ans*pow(q[j].v,s-t)%mod;
			}
			for (int j=1;j<=tot;j++){
				T0.update(-q[j].a,q[j].v);
				T1.update(q[j].b,q[j].v);
			}
		} 
	}
}
void divide(int u){
	vis[u]=1; calc(u); int tmp=All;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!vis[v]){
			All=(v==Fa[u])?tmp-size[u]:size[v];
			mn=INF; getroot(v,u); divide(rt);
		}
	}
}
inline void solve(){
	mn=INF; All=n; ans=1;
	getroot(1,0); divide(rt);
	writeln(ans);
}
signed main(){
	init(); solve();
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

点分治题。

对于边占比的信息不太好直接合并出来，于是我们考虑维护 $a-kb$ 形式的信息使得合并之后可以快速查看是否满足比例约束。

具体来说我们设黑边个数为 $a$，白边个数为 $b$，那么我们维护四个信息 $(A,B,C,D)=(a-2b,2b-a,b-2a，2a-b)$。

于是 $(u,v)$ 点对可以产生贡献必须满足，$A_u\le B_v$ 且 $C_u\le D_v$。这是一个二维数点的形式。

直接排序 $+$ 树状数组统计即可。如果去除同一子树内贡献呢，我们对于当前分治重心下同一子树的信息单独跑一边上述计算减去贡献即可。但是这么做感觉有点问题，就同一点对会产生重复贡献，由于是乘法需要开根号，这就需要取模意义下的开根号也就是二次剩余有点麻烦。

为了防止点对产生重复贡献，我们可以赋一个顺序，也就是子树顺序，然后直接 CDQ 即可。

时间复杂度 $O(n\log^3 n)$。


```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb emplace_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
const int mod=1e9+7;
void chkmax(int &x,int y){ x=x>y?x:y; }
pair<int,int> operator + (pair<int,int> f,pair<int,int> g){ return mp(1ll*f.fi*g.fi%mod,f.se+g.se); }
struct edge{
	int to,Next,w,c;
}edges[maxn<<1];
struct node{
	int A,B,C,D,E,val;
	node (int aa=0,int bb=0,int cc=0,int dd=0,int ee=0,int vv=0){ A=aa; B=bb; C=cc; D=dd; E=ee; val=vv; }
};
struct Q{
	int x,y,z,val,type;
	Q (int xx=0,int yy=0,int zz=0,int vv=0,int tt=0){ x=xx; y=yy; z=zz; val=vv; type=tt; }
}q[maxn<<1];
bool cmp(Q s,Q t){
	if(s.x==t.x){
		if(s.type==t.type) return (s.y<t.y)||(s.y==t.y&&s.z<t.z);
		else return s.type<t.type;
	}else return s.x<t.x;
}
bool cmp2(Q s,Q t){ return s.y<t.y||(s.y==t.y&&s.z<t.z); }
int head[maxn],vis[maxn],tot,n,C,sz;
vector<node> a; ll ans=1,Ans; 
struct BIT{
	pair<int,int> c[maxn<<2];
	int lowbit(int x){ return x&-x; }
	void init(){ for(int i=0;i<=4*n;i++) c[i]=mp(1,0); }
	void modify(int x,int v){ x+=2*n; for(;x<=4*n;x+=lowbit(x)) c[x]=c[x]+mp(v,1); }
	void clear(int x){ x+=2*n; for(;x<=4*n;x+=lowbit(x)) c[x]=mp(1,0); }
	pair<int,int> query(int x){
		pair<int,int> res=mp(1,0); x+=2*n;
		for(;x;x-=lowbit(x)) res=res+c[x];
		return res;
	}
}t;
int qpow(int x,int k){
	int res=1;
	for(;k;k>>=1){
		if(k&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
	}
	return res;
}
int inv(int x){ return qpow(x,mod-2); }
void add(int u,int v,int w,int c){
	edges[++tot]=(edge){v,head[u],w,c};
	head[u]=tot;
}
int calc(int u,int fa){
	int su=1,mx=0;
	for(int i=head[u];i;i=edges[i].Next){
		int v=edges[i].to; if(vis[v]||v==fa) continue;
		int z=calc(v,u); chkmax(mx,z); su+=z;
	}
	chkmax(mx,sz-su); if(mx<=sz/2) C=u;
	return su;
}
int find(int u,int fa){ sz=calc(u,fa); calc(u,fa); return C; }
void dfs(int u,int fa,int A,int B,int C,int D,int mul,int anc){
	a.pb(node(A,B,C,D,anc,mul));
	for(int i=head[u];i;i=edges[i].Next){
		int v=edges[i].to; if(vis[v]||v==fa) continue;
		int ca=0,cb=0; edges[i].c?ca++:cb++;
		dfs(v,u,A+ca-2*cb,B+2*cb-ca,C+cb-2*ca,D+2*ca-cb,1ll*mul*edges[i].w%mod,anc);
	}
}
void cdq(int l,int r){
	if(l>=r) return ;
	int mid=(l+r)>>1;
	cdq(l,mid); cdq(mid+1,r);
	sort(q+l,q+1+mid,cmp2); sort(q+mid+1,q+1+r,cmp2);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&q[j].y<=q[i].y){
			if(q[j].type){
				t.modify(q[j].z,q[j].val);
			}
			j++;
		}
		if(!q[i].type){
			pair<int,int> z=t.query(q[i].z);
			Ans=1ll*Ans*qpow(q[i].val,z.se)%mod*z.fi%mod;
		}
	}
	for(int i=l;i<j;i++) t.clear(q[i].z); 
}
ll work(){
	tot=0; Ans=1;
	for(auto v:a){
		q[++tot]=Q(v.E,v.A,v.C,v.val,1);
		q[++tot]=Q(v.E,v.B,v.D,v.val,0);
	}
	sort(q+1,q+1+tot,cmp);
	cdq(1,tot); return Ans;
}
void solve(int u){
	for(int i=head[u];i;i=edges[i].Next){
		int v=edges[i].to; if(vis[v]) continue;
		int ca=0,cb=0; edges[i].c?ca++:cb++;
		dfs(v,u,ca-2*cb,2*cb-ca,cb-2*ca,2*ca-cb,edges[i].w,v);
	}
	a.pb(node(0,0,0,0,0,1)); vis[u]=1;
	ans=ans*work()%mod; a.clear();
	for(int i=head[u];i;i=edges[i].Next){
		int v=edges[i].to; if(vis[v]) continue;
		solve(find(v,u));
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; t.init();
	for(int i=1;i<=n-1;i++){
		int u,v,w,c; cin>>u>>v>>w>>c;
		add(u,v,w,c); add(v,u,w,c);
	}
	solve(find(1,0)); cout<<ans;
	return 0;
}
```

---

## 作者：Rainybunny (赞：1)

# 题目
&emsp;&emsp;[$luogu$](https://www.luogu.com.cn/problem/CF833D).
# 题解
&emsp;&emsp;点分治？点分治是拿不了最快速度的。/xyx
## 边分治
&emsp;&emsp;（基础算法讲解，会的跳过吧qwq。）
### 概念
&emsp;&emsp;顾名思义，在点分治的思想上，边分治每次以一条树边为分治中心，把原树分割正两块，统计经过分治中心边的答案，将其删去，并递归剩余部分。  
&emsp;&emsp;如何取分治中心呢？类比点分治，当然是要让**边两侧较大联通块最小**啦。
### 寻找分治中心边
&emsp;&emsp;根据上文，就有这样一个和找中心差不多的代码...
```cpp
// s: 当前联通块大小；mxs: 分治中心两侧较大联通块大小；rte: 分治中心边id。
inline void FindCent ( const int u, const int f, const int s, int& mxs, int& rte ) {
	Siz[u] = 1;
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ! Vis[i >> 1] && ( v = Graph[i].To ) ^ f ) {
			FindCent ( v, u, s, mxs, rte ), Siz[u] += Siz[v];
			if ( mxs > Max ( Siz[v], s - Siz[v] ) ) {
				rte = i, mxs = Max ( Siz[v], s - Siz[v] );
			}
		}
	}
}
```
### 重建树
&emsp;&emsp;然后，仔细一想，事情并不简单...  
&emsp;&emsp;假设原树是一朵（？）菊花，那么每次较大块最小值只能-1，这样递归层数就达到 $O(n)$ 了！  
&emsp;&emsp;于是，我们用空间换时间，尝试插入一些虚拟结点，在**保证树上信息（点权，距离等）不被破坏**的情况下，使原树变为一颗优美的**二叉树**。也即是**多叉转二叉**操作。  
&emsp;&emsp;怎样转换呢？口胡一下算法流程...  
1. 任取一点确定原树父子关系。  

1. 对于结点 $u$ （不论其是否是虚拟结点），若孩子不多于 $2$ 个，直接向孩子们连边；否则，令 $u$ 连向两个新建的虚拟结点，并把孩子们按奇偶性分配给这两个虚拟结点。  

1. 循环进行，直到处理完所有（虚拟或实际）结点。  

&emsp;&emsp;~~别着急，我知道我语文不好，看代码：~~
```cpp
inline void Prepare ( const int u, const int f ) {
	Siz[u] = 1;
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ( v = Graph[i].To ) ^ f ) {
        	// 注意：只在G上连出外向树。
			G[u].push_back ( { v, Graph[i].Cost, Graph[i].Color } );
			Prepare ( v, u ), Siz[u] += Siz[v];
            // 下面这句别着急w，与建树算法无关。
			Ans1 = 1LL * Ans1 * qkpow ( Graph[i].Cost, 1LL * Siz[v] * ( n - Siz[v] ) % ( MOD - 1 ) ) % MOD;
		}
	}
}
```

```cpp
inline void Rebuild () {
// 首先清空原树信息。
	Cnte = 1;
	for ( Int i = 1; i <= n; ++ i ) Head[i] = 0;
// 循环进行。
	for ( Int i = 1; i <= n; ++ i ) {
		if ( G[i].size () <= 2u ) {
			for ( VecE adj: G[i] ) AddEdge ( i, adj.To, adj.Cost, adj.Color );
		} else {
        	// 新建两个虚拟结点（左右儿子）。
			int lc = ++ n, rc = ++ n;
            // 连边，权设为1，不影响路径乘积信息；颜色为-1，不影响颜色统计。
			AddEdge ( i, lc, 1, -1 ), AddEdge ( i, rc, 1, -1 );
            		// 分配孩子。
			for ( Int j = 0; j ^ G[i].size (); ++ j ) {
				if ( j & 1 ) G[lc].push_back ( G[i][j] );
				else G[rc].push_back ( G[i][j] );
			}
		}
	}
}
```
&emsp;&emsp;类比线段树的树形，可以发现这样重建树的空间是原树的至多 $4$ 倍。在这颗树上，我们就能保证分治层数在 $O(n\log n)$ 级别啦。
### 分治过程
&emsp;&emsp;还是跟点分治差不多...不过注意在用链式前向星存图时，下标要从偶数开始，这样对于一条边 $i$，就能轻易找到它的反向边 $i\oplus1$。（‘$\oplus$’为异或运算。）
```cpp
inline void Solve ( const int u, const int s ) {
	int mxs = s + 5, rte;
	FindCent ( u, 0, s, mxs, rte );
	if ( mxs == s + 5 ) return ;
	Vis[rte >> 1] = true;
	int x = Graph[rte].To, y = Graph[rte ^ 1].To;
    /*** 这里处理经过<x,y>的路径的贡献。 ***/
	int t = Siz[x];
	Solve ( x, t ), Solve ( y, s - t );
}
```
&emsp;&emsp;其中，处理路径信息的部分就和点分治差不多了。不过由于只有两部分信息，就不用考虑如何合并信息了。  
&emsp;&emsp;赠送板子：[$bzoj2870$（传送门到dark）](https://darkbzoj.tk/problem/2870).
## 本题分析
&emsp;&emsp;考虑容斥，先求出所有路径边权积的积，再减去不合法方案。  
&emsp;&emsp;对于前者，一条权为 $w$，左右点数分别为 $a,b$ 的边的贡献是 $w^{ab}$。也即是左右任取一对点，都会产生一次贡献。注意到指数可以用费马小定理 $\bmod~(10^9+6)$。（不过没什么必要。）上文 `Prepare` 函数的 `Ans1` 就是在计算这个东西。  
&emsp;&emsp;对于后者，分红多于黑，黑多于红两种情况讨论。假设两段路径的红黑数量为 $(r_1,b_1),(r_2,b_2)$， 第一种情况有：
$$
r_1+r_2>2(b_1+b_2)
$$
&emsp;&emsp;分离：
$$
r_2-2b_2>2b_1-r_1
$$
&emsp;&emsp;把分治中心边一侧的所有 $2b_1-r_1$ 和其对应路径的积收集起来并按 $2b_1-r_1$ 从小到大排序，再枚举另一侧的 $(r_2,b_2)$，二分出可以对其贡献最大 $2b_1-r_1$ 的位置，那么该位置的前缀积就是当前分治中心边的答案。  
&emsp;&emsp;另一种情况同理。  
&emsp;&emsp;所以...就这样咯。
```cpp
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define Int register int

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5, MAXND = MAXN << 2, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
int n, m, Ans1 = 1, Ans2 = 1, Cnte = 1, Head[MAXND + 5], Siz[MAXND + 5];
bool Vis[MAXND + 5];
vector<pii> R, B; // less than the other one.

struct VecE { int To, Cost, Color; };
vector<VecE> G[MAXND + 5];

struct Edge { int To, Cost, Color, nxt; } Graph[MAXND * 2 + 5];

inline int Max ( const int a, const int b ) { return a > b ? a : b; }

inline int qkpow ( int a, int b, const int p = MOD ) {
	int ret = 1;
	for ( ; b; a = 1LL * a * a % p, b >>= 1 ) ret = 1LL * ret * ( b & 1 ? a : 1 ) % p;
	return ret;
}

inline void Link ( const int s, const int t, const int w, const int c ) {
	Graph[++ Cnte] = { t, w, c, Head[s] };
	Head[s] = Cnte;
}

inline void AddEdge ( const int u, const int v, const int w, const int c ) {
	Link ( u, v, w, c ), Link ( v, u, w, c );
}

inline void Prepare ( const int u, const int f ) {
	Siz[u] = 1;
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ( v = Graph[i].To ) ^ f ) {
			G[u].push_back ( { v, Graph[i].Cost, Graph[i].Color } );
			Prepare ( v, u ), Siz[u] += Siz[v];
			Ans1 = 1LL * Ans1 * qkpow ( Graph[i].Cost, 1LL * Siz[v] * ( n - Siz[v] ) % ( MOD - 1 ) ) % MOD;
		}
	}
}

inline void Rebuild () {
	Cnte = 1;
	for ( Int i = 1; i <= n; ++ i ) Head[i] = 0;
	for ( Int i = 1; i <= n; ++ i ) {
		if ( G[i].size () <= 2u ) {
			for ( VecE adj: G[i] ) AddEdge ( i, adj.To, adj.Cost, adj.Color );
		} else {
			int lc = ++ n, rc = ++ n;
			AddEdge ( i, lc, 1, -1 ), AddEdge ( i, rc, 1, -1 );
			for ( Int j = 0; j ^ G[i].size (); ++ j ) {
				if ( j & 1 ) G[lc].push_back ( G[i][j] );
				else G[rc].push_back ( G[i][j] );
			}
		}
	}
}

inline void FindCent ( const int u, const int f, const int s, int& mxs, int& rte ) {
	Siz[u] = 1;
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ! Vis[i >> 1] && ( v = Graph[i].To ) ^ f ) {
			FindCent ( v, u, s, mxs, rte ), Siz[u] += Siz[v];
			if ( mxs > Max ( Siz[v], s - Siz[v] ) ) {
				rte = i, mxs = Max ( Siz[v], s - Siz[v] );
			}
		}
	}
}

inline void CollectDist ( const int u, const int f, const int cr, const int cb, const int ds ) {
	if ( u <= m ) R.push_back ( { 2 * cr - cb, ds } ), B.push_back ( { 2 * cb - cr, ds } );
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ! Vis[i >> 1] && ( v = Graph[i].To ) ^ f ) {
			CollectDist ( v, u, cr + ( Graph[i].Color == 0 ), cb + ( Graph[i].Color == 1 ), 1LL * ds * Graph[i].Cost % MOD );
		}
	}
}

inline void Calc ( const int u, const int f, const int cr, const int cb, const int ds ) {
	if ( u <= m ) {
		int t = lower_bound ( R.begin (), R.end (), pii { cb - 2 * cr, 0 } ) - R.begin ();
		Ans2 = 1LL * Ans2 * qkpow ( ds, t ) % MOD * ( t ? R[t - 1].second : 1 ) % MOD;
		t = lower_bound ( B.begin (), B.end (), pii { cr - 2 * cb, 0 } ) - B.begin ();
		Ans2 = 1LL * Ans2 * qkpow ( ds, t ) % MOD * ( t ? B[t - 1].second : 1 ) % MOD;
	}
	for ( Int i = Head[u], v; i; i = Graph[i].nxt ) {
		if ( ! Vis[i >> 1] && ( v = Graph[i].To ) ^ f ) {
			Calc ( v, u, cr + ( Graph[i].Color == 0 ), cb + ( Graph[i].Color == 1 ), 1LL * ds * Graph[i].Cost % MOD );
		}
	}
}

inline void Solve ( const int u, const int s ) {
	int mxs = s + 5, rte;
	FindCent ( u, 0, s, mxs, rte );
	if ( mxs == s + 5 ) return ;
	Vis[rte >> 1] = true;
	int x = Graph[rte].To, y = Graph[rte ^ 1].To;
	R.clear (), B.clear (), R.clear (), B.clear ();
	CollectDist ( x, 0, 0, 0, 1 );
	sort ( R.begin (), R.end () ), sort ( B.begin (), B.end () );
	if ( R.size () ) for ( Int i = 1; i ^ R.size (); ++ i ) R[i].second = 1LL * R[i - 1].second * R[i].second % MOD;
	if ( B.size () ) for ( Int i = 1; i ^ B.size (); ++ i ) B[i].second = 1LL * B[i - 1].second * B[i].second % MOD;
	Calc ( y, 0, Graph[rte].Color == 0, Graph[rte].Color == 1, Graph[rte].Cost );
	int t = Siz[x];
	Solve ( x, t ), Solve ( y, s - t );
}

inline void Work () {
	scanf ( "%d", &n ), m = n;
	for ( Int i = 1, u, v, w, c; i ^ n; ++ i ) {
		scanf ( "%d %d %d %d", &u, &v, &w, &c );
		AddEdge ( u, v, w, c );
	}
	Prepare ( 1, 0 );
	Rebuild ();
#ifdef __DEBUG
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = Head[i]; j; j = Graph[j].nxt ) {
			printf ( "%d %d (%d,%d)\n", i, Graph[j].To, Graph[j].Cost, Graph[j].Color );
		}
	}
#endif
	Solve ( 1, n );
	printf ( "%d\n", int ( 1LL * Ans1 * qkpow ( Ans2, MOD - 2 ) % MOD ) );
}

int main () {
	Work ();
	return 0;
}
```
&emsp;&emsp;截止提交时，最优解 rk1，比楼下快近 5s。/xyx

---

## 作者：何俞均 (赞：0)

广告：食用[$blog$](https://www.cnblogs.com/heyujun/p/10199924.html)体验更佳

## 题解

看到这种统计路径的题目当然是淀粉质啦。

考虑转化一下信息，设一条路径上有红点$a$个，黑点$b$个

则$2min(a,b)\geq max(a,b)$

$\Leftrightarrow 2*a\geq b$且$2*b\geq a$

现在我们需要将过一个点的两条路径合并

设第一条为红$a_1$，黑$b_1$，第二条为红$a_2$，黑$b_2$

则有

$2(a_1+a_2)\geq b_1+b_2$ 

$2(b_1+b_2)\geq a_1+a_2  $

将一个下标的放一边以便维护

$2a_2-b_2\geq b_1-2a_1$

$2b_2-a_2\geq a_1-2b_1$


每次遍历完一颗子树，按时间加入所有的路径，将不等式左边看作查询二维平面，

右边看作插入坐标，就是一个$cdq$分治

复杂度是$nlog^4$(因为中间还有快速幂),但常数很小

代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <cmath> 
#include <algorithm>
using namespace std;
inline int gi() {
	register int data = 0, w = 1;
	register char ch = 0;
	while (!isdigit(ch) && ch != '-') ch = getchar(); 
	if (ch == '-') w = -1, ch = getchar();
	while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar();
	return w * data; 
} 
const int MAX_N = 1e5 + 5; 
const int Mod = 1e9 + 7;
int fpow(int x, int y) {
	int res = 1; 
	while (y) {
		if (y & 1) res = 1ll * res * x % Mod;
		x = 1ll * x * x % Mod;
		y >>= 1; 
	} 
	return res; 
} 
struct Point { int x, y, op, v; } ; 
bool operator < (const Point &l, const Point &r) { return (l.x == r.x) ? (l.y < r.y) : (l.x < r.x); } 
struct Graph { int to, cost, col, next; } e[MAX_N << 1]; int fir[MAX_N], e_cnt = 0; 
void clearGraph() { memset(fir, -1, sizeof(fir)); e_cnt = 0; } 
void Add_Edge(int u, int v, int w, int c) {
	e[e_cnt].to = v, e[e_cnt].cost = w, e[e_cnt].col = c, e[e_cnt].next = fir[u];
	fir[u] = e_cnt++;
} 
int N, ans = 1, size[MAX_N]; 
bool used[MAX_N]; 
int centroid, sz, rmx, c1[MAX_N << 2], c2[MAX_N << 2]; 
Point stk[MAX_N], q[MAX_N << 2]; 
int top, cnt; 
inline int lb(int x) { return x & -x; }
void add(int x, int v) { while (x <= N * 4 + 1) c1[x] = 1ll * c1[x] * v % Mod, c2[x]++, x += lb(x); } 
int Sum(int x) { int res = 1; while (x > 0) res = 1ll * c1[x] * res % Mod, x -= lb(x); return res; } 
int Cnt(int x) { int res = 0; while (x > 0) res += c2[x], x -= lb(x); return res; } 
void Set(int x) { while (x <= N * 4 + 1) c1[x] = 1, c2[x] = 0, x += lb(x); } 
void search_centroid(int x, int fa) { 
    size[x] = 1; int mx = 0; 
	for (int i = fir[x]; ~i; i = e[i].next) { 
		int v = e[i].to; 
		if (v == fa || used[v]) continue; 
		search_centroid(v, x); 
		size[x] += size[v]; 
		mx = max(mx, size[v]); 
	} 
	mx = max(mx, sz - size[x]); 
	if (mx < rmx) rmx = mx, centroid = x; 
} 
void dfs(int x, int fa, int R, int B, int val) {
	stk[++top] = (Point){R, B, 0, val}; 
	for (int i = fir[x]; ~i; i = e[i].next) { 
		int v = e[i].to; 
		if (v == fa || used[v]) continue; 
		if (e[i].col == 0) dfs(v, x, R + 1, B, 1ll * val * e[i].cost % Mod); 
		else if (e[i].col != 0) dfs(v, x, R, B + 1, 1ll * val * e[i].cost % Mod); 
	} 
} 
void Div(int l, int r) { 
	if (l >= r) return ; 
	int mid = (l + r) >> 1; 
	Div(l, mid); Div(mid + 1, r);
	int j = l; 
	for (int i = mid + 1; i <= r; i++) { 
		if (!q[i].op) continue; 
		while (q[j].x <= q[i].x && j <= mid) { if (!q[j].op) add(q[j].y, q[j].v); ++j; } 
		ans = 1ll * ans * Sum(q[i].y) % Mod * fpow(q[i].v, Cnt(q[i].y)) % Mod; 
	}
	for (int i = l; i < j; i++) if (!q[i].op) Set(q[i].y); 
	inplace_merge(&q[l], &q[mid + 1], &q[r + 1]); 
} 
void solve(int x) {
	used[x] = 1;
	cnt = 0; int Pls = 2 * N + 1; 
	for (int i = fir[x]; ~i; i = e[i].next) { 
		int v = e[i].to; 
		if (used[v]) continue; 
		top = 0; 
		if (e[i].col == 0) dfs(v, x, 1, 0, e[i].cost); 
		else if (e[i].col == 1) dfs(v, x, 0, 1, e[i].cost); 
		for (int j = 1; j <= top; j++) {
			int a = stk[j].x, b = stk[j].y;
            q[++cnt] = (Point){2 * a - b + Pls, 2 * b - a + Pls, 1, stk[j].v}; 
		} 
		for (int j = 1; j <= top; j++) {
			int a = stk[j].x, b = stk[j].y; 
			q[++cnt] = (Point){b - 2 * a + Pls, a - 2 * b + Pls, 0, stk[j].v};
			if (2 * min(a, b) >= max(a, b)) ans = 1ll * ans * stk[j].v % Mod; 
		} 
	} 
	Div(1, cnt); 
	for (int i = fir[x]; ~i; i = e[i].next) { 
		int v = e[i].to;
		if (used[v]) continue; 
		sz = rmx = size[v];
		search_centroid(v, x); 
		solve(centroid); 
	} 
} 
int main () { 
	clearGraph(); 
	N = gi();
	for (int i = 1; i < N; i++) {
		int u = gi(), v = gi(), w = gi(), c = gi();
		Add_Edge(u, v, w, c); 
		Add_Edge(v, u, w, c); 
	}
	for (int i = 1; i <= 4 * N + 1; i++) c1[i] = 1, c2[i] = 0; 
	sz = rmx = N; 
	search_centroid(1, 0); 
	solve(centroid);
	printf("%d\n", ans); 
	return 0; 
} 
```

---

## 作者：xgzc (赞：0)

### [题面](http://codeforces.com/problemset/problem/833/D)

### 题解

点分治大火题。。。

设白边数量为$a$，黑边为$b$，则$2min(a,b)\geq max(a,b)$

即$2a\geq b\;\&\&2b\geq a$

考虑点分治时如何统计答案：

$2(a_1 +a_2) \geq b_1 + b_2$

$\therefore 2a_1-b_1\geq b_2-2a_2$

另外一边同理

于是我们可以愉快地用$sort+BIT$统计答案了

但是路径有可能重复计算，可以套一个$CDQ$分治什么的来搞一下

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define RG register
#define clear(x, y) memset(x, y, sizeof(x));

namespace IO
{
	const int BUFSIZE = 1 << 20;
	char ibuf[BUFSIZE], *is = ibuf, *it = ibuf;
	inline char getchar() { if (is == it) it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin); return *is++; }
}

inline int read()
{
	int data = 0, w = 1;
	char ch = IO::getchar();
	while(ch != '-' && (ch < '0' || ch > '9')) ch = IO::getchar();
	if(ch == '-') w = -1, ch = IO::getchar();
	while(ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = IO::getchar();
	return data*w;
}

const int maxn(1e5 + 10), Mod(1e9 + 7);
inline int fastpow(int x, int y)
{
	int ans = 1;
	while(y)
	{
		if(y & 1) ans = 1ll * ans * x % Mod;
		x = 1ll * x * x % Mod, y >>= 1;
	}
	return ans;
}

struct edge { int next, to, val, col; } e[maxn << 1];
int n, head[maxn], e_num, size[maxn], Size, min, root;
struct qry { int r, b, v, o; } stk[maxn], q[maxn << 2];
int top, cntq, cntup, csum[maxn << 2], cmul[maxn << 2], vis[maxn];
inline bool cmpr(const qry &a, const qry &b)
	{ return a.r == b.r ? a.b < b.b : a.r < b.r; }

void clean(int x)
{
	while(x <= (n << 2 | 1)) csum[x] = 0, cmul[x] = 1, x += x & -x;
}

void add(int x, int v)
{
	while(x <= (n << 2 | 1))
		++csum[x], cmul[x] = 1ll * cmul[x] * v % Mod, x += x & -x;
}

int query_sum(int x)
{
	int ans = 0;
	while(x) ans += csum[x], x -= x & -x;
	return ans;
}

int query_mul(int x)
{
	int ans = 1;
	while(x) ans = 1ll * ans * cmul[x] % Mod, x -= x & -x;
	return ans;
}

inline void add_edge(int from, int to, int val, int col)
{
	e[++e_num] = (edge) {head[from], to, val, col};
	head[from] = e_num;
}

void getRoot(int x, int fa)
{
	size[x] = 1; int tot = 0;
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to; if(vis[to] || to == fa) continue;
		getRoot(to, x); tot = std::max(tot, size[to]);
		size[x] += size[to];
	}
	tot = std::max(tot, Size - size[x]);
	if(tot < min) min = tot, root = x;
}

void getVal(int x, int fa, int r, int b, int v)
{
	stk[++top] = (qry) {r, b, v, 0};
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to; if(vis[to] || to == fa) continue;
		getVal(to, x, r + (!e[i].col), b + e[i].col, 1ll * v * e[i].val % Mod);
	}
}

int ans = 1;
void CDQ(int l, int r)
{
	if(l >= r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid); CDQ(mid + 1, r);
	int j = l;
	for(RG int i = mid + 1; i <= r; i++)
	{
		if(!q[i].o) continue;
		while(q[j].r <= q[i].r && j <= mid)
		{
			if(!q[j].o) add(q[j].b, q[j].v);
			++j;
		}
		ans = 1ll * ans * query_mul(q[i].b) % Mod *
			fastpow(q[i].v, query_sum(q[i].b)) % Mod;
	}
	for(RG int i = l; i < j; i++) if(!q[i].o) clean(q[i].b);
	std::inplace_merge(q + l, q + mid + 1, q + r + 1, cmpr);
}

void calc(int x)
{
	int PLUS = n << 1 | 1;
	cntq = cntup = 0;
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to; if(vis[to]) continue;
		top = 0; getVal(to, x, !e[i].col, e[i].col, e[i].val);
		for(RG int j = 1; j <= top; j++)
		{
			int a = stk[j].r, b = stk[j].b, c = 2 * a - b, d = 2 * b - a;
			q[++cntq] = (qry) {c + PLUS, d + PLUS, stk[j].v, 1};
		}
		for(RG int j = 1; j <= top; j++)
		{
			int a = stk[j].r, b = stk[j].b, c = 2 * a - b, d = 2 * b - a;
			q[++cntq] = (qry) {-c + PLUS, -d + PLUS, stk[j].v, 0};
			if(2 * std::min(a, b) >= std::max(a, b))
				ans = 1ll * ans * stk[j].v % Mod;
		}
	}
	CDQ(1, cntq);
}

void dfs(int x)
{
	vis[x] = 1; calc(x);
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to; if(vis[to]) continue;
		Size = min = size[to]; getRoot(to, x); dfs(root);
	}
}

int main()
{
	Size = min = n = read();
	for(int i = 1, a, b, c, d; i < n; i++)
		a = read(), b = read(), c = read(), d = read(),
		add_edge(a, b, c, d), add_edge(b, a, c, d);
	for(RG int i = 1; i <= (n << 2 | 1); i++) csum[i] = 0, cmul[i] = 1;
	getRoot(1, 0); dfs(root);
	printf("%d\n", ans);
	return 0;
}
```



---

