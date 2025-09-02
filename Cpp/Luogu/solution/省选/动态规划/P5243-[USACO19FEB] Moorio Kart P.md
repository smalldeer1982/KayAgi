# [USACO19FEB] Moorio Kart P

## 题目描述

Bessie 和 Farmer John 喜欢山羊卡丁车比赛。这个比赛非常类似于其他人喜欢的卡丁车比赛，除了卡丁车是由山羊拉动，以及赛道是由农田组成。农田由 $ N $ 个草地和 $ M $ 条道路组成，每条道路都连接着两个草地。

定义农场是两个或更多草地的一个集合，同一农场中的每个草地都可以沿着一系列**唯一**的道路到达农场中其他任意一个草地。

整个农田可能由多个农场组成，假设图中有 $ K $ 个农场。Bessie 希望通过添加长度为 $ X $ 的 $ K $ 条道路，连接所有 $ K $ 个农场来制作山羊卡丁车赛道。每个农场只应访问一次，并且每个农场内必须至少穿过一条道路。

为了让选手们对赛道更有兴趣，赛道的长度至少应该为 $ Y $ 。Bessie 希望知道所有这些有趣赛道的赛道长度总和。如果一个赛道中有两个农场直接相连，但另外一个赛道中这两个农场没有直接相连的话，这两个赛道就是不同的。

---

形式化题意：

给定 $K$ 个连通块的森林，边有边权。你需要加入 $K$ 条长为 $X$ 的边使得整张图变成一棵基环树。原来的每个连通块在环上至少有一条边，所有新加入的边都应该在环上。

求所有环长 $\ge Y$ 的合法方案的环长之和。

## 说明/提示

有 6 个合法的赛道方案：

- 1 --> 2 --> 4 --> 5 --> 1 (长度 11)
- 1 --> 2 --> 5 --> 4 --> 1 (长度 11)
- 2 --> 3 --> 4 --> 5 --> 2 (长度 12)
- 2 --> 3 --> 5 --> 4 --> 2 (长度 12)
- 1 --> 2 --> 3 --> 4 --> 5 --> 1 (长度 15)
- 1 --> 2 --> 3 --> 5 --> 4 --> 1 (长度 15)

其中后 4 条赛道满足了赛道总长不低于 12 的条件，这几条赛道的长度总和为 54。

子任务：对于 $ 70\% $ 的数据， $ N,Y \leq 1000 $ 。

## 样例 #1

### 输入

```
5 3 1 12
1 2 3
2 3 4
4 5 6
```

### 输出

```
54```

# 题解

## 作者：Great_Influence (赞：7)

暴力能 A 的迷之题目。

题意可以理解为给你几棵小树，然后将这几颗小树连成一个环，使得环长 $\ge Y$ ，求满足要求的树个数。

因为数据范围很小，考虑直接用 $dfs$ 将每棵小树内的所有路径都统计出来。然后就变成了问给你几个集合，从这些集合中每个集合选择一个数，问和 $\ge Y$ 的方案和。这是一个简单背包问题。求方案和可以顺便求出。

具体来说，设 $dp[i][0/1]$ 表示 和为 $i$ 的方案数/方案和， $g[i][0/1]$ 表示当前小树内长度为 $i$ 的路径数/长度和，则存在转移:

$$dp[i+j][0]\leftarrow dp[i][0]*g[j][0]$$

$$dp[i+j][1]\leftarrow dp[i][0]*g[j][1] + dp[i][1]*g[j][0]$$

直接转移即可。

注意我们并不关注这个长度具体是多少，只关注它是否比 $Y$ 大。并且长度大于等于 $Y$ 的方案之后再怎么变都是满足要求的。因此可以将长度 $\ge Y$ 的部分记在一起。还有个优化是可以直接从 $X*k$ 开始转移。还有就是只转移 $g$ 和 $dp$ 有值的位置。

时间复杂度为 $O(\sum n_i^2+\min\{Y,n_i^2\}(Y-XK))=O(NY\sqrt{Y})$ ， $n_i$ 为第 $i$ 棵小树的点数。复杂度证明为考虑子树贡献，当 $\forall i,Y=n_i^2$时复杂度取得最大值。



代码:
```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

void file(void)
{
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
}

const int MAXN=1500+7,MAXY=2500+7,mod=1e9+7;

static int n,m;

static struct edge
{
	int v,w,nxt;
}p[MAXN<<1];

static int head[MAXN],e;

inline void add(int u,int v,int w)
{p[++e]=(edge){v,w,head[u]},head[u]=e;}

namespace DSU
{
	static int fa[MAXN];

	inline void clear(){Rep(i,1,n)fa[i]=i;}

	inline int Find(int u){return u==fa[u]?u:fa[u]=Find(fa[u]);}
}

static int X,Y;

inline void init()
{
	read(n),read(m),read(X),read(Y);
	DSU::clear();
	static int u,v,w;
	Rep(i,1,m)read(u),read(v),read(w)
		,add(u,v,w),add(v,u,w),DSU::fa[DSU::Find(u)]=DSU::Find(v);
}

static int cn;

static int bel[MAXN],dst[MAXN][MAXY],sig[MAXN][MAXY];

void dftag(int u,int fr,int dir)
{
	bel[u]=dir;
	for(register int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(v^fr)dftag(v,u,dir);
	}
}

void dffix(int u,int fr,int len)
{
	if(fr)(sig[bel[u]][min(Y,len)]+=len)%=mod,++dst[bel[u]][min(Y,len)];
	for(register int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(v^fr)dffix(v,u,len+p[i].w);
	}
}

static int dp[MAXY][2],las[MAXY][2];

inline int fac(int u)
{
	register int sm=1;
	Rep(i,2,u)sm=(ll)sm*i%mod;
	return sm;
}

inline void solve()
{
	Rep(i,1,n)if(DSU::Find(i)==i)++cn,dftag(i,0,cn);
	Rep(i,1,n)dffix(i,0,0);
	static int st=min(Y,X*cn);
	dp[st][0]=1,dp[st][1]=X*cn;
	Rep(i,1,cn)
	{
		Rep(j,st,Y)las[j][0]=dp[j][0]
			,las[j][1]=dp[j][1],dp[j][0]=dp[j][1]=0;
		Rep(j,0,Y)if(dst[i][j])Rep(k,st,Y)if(las[k][0])
		{
			dp[min(j+k,Y)][0]=(dp[min(j+k,Y)][0]+
				(ll)las[k][0]*dst[i][j])%mod;

			dp[min(j+k,Y)][1]=(dp[min(j+k,Y)][1]+
				(ll)las[k][0]*sig[i][j]+(ll)las[k][1]*dst[i][j])%mod;
		}
	}
	cout<<(ll)dp[Y][1]*fac(cn-1)%mod*((mod+1)/2)%mod<<endl;
}

int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：asuldb (赞：3)

[题目](https://www.luogu.org/problemnew/show/P5243)

我们的神仙教练在考试里放了这道题，当时我非常惊讶啊

背包是$O(n^3)$的吧~~明明是带根号的好吧~~，那既然要优化的话

NTT！什么时候我们教练会在考试里放多项式了

模数$1e9+7$？

~~任意模数~~不存在的，我们开int128找一个大一点的$NTT$模数就可以了

还是说一下$NTT$的做法吧，发现我们要求长度大于$Y$的路径可能不太好求，于是我们正难则反一下，我们求出有多少种拼法可以使得路径长度小于$Y$就可以了

每一棵树里只能出一条路径，于是我们可以把一棵树的路径信息搞成一个多项式，系数代表这种长度的路径出现了多少次

我们把每棵树的多项式卷起来就是最后的答案了

并不保证随时能通过而且我们不怎么能看懂的代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define _LL __int128
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#pragma GCC optimize(3)
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("Ofast,no-stack-protector")
char BB[1<<18],*S=BB,*T=BB; 
const int maxn=1505;
inline int read() {
    char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
struct E{int v,nxt,w;}e[maxn<<1];
const LL mod=4222124650659841;
const LL P=1e9+7;
_LL G[2],t,og;
_LL mi[2][16];
int head[maxn],sum[maxn];
int n,m,X,Y,tot,num;
int rev[10000],len,fa[maxn],vis[maxn],pre[maxn];
int tax[1501][2501];LL tp[maxn];
_LL A[9000],B[9000];
LL tmp=1,k=0;
inline void add(int x,int y,int w) {
    e[++num].v=y;e[num].nxt=head[x];
    head[x]=num;e[num].w=w;
}
inline _LL ksm(_LL a,LL b) {
    _LL S=1;
    while(b) {if(b&1ll) S=S*a%mod;b>>=1ll;a=a*a%mod;}
    return S;
}
void exgcd(LL a,LL b,LL &x,LL &y) {
    if(!b) {x=1,y=0;return;}
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}
inline LL getInv(LL a) {
    LL x,y;exgcd(a,P,x,y);
    return (x%P+P)%P;
}
void write(LL x){
	if(x==0){putchar(48);return;}
	int len=0,dg[25];
	while(x>0){dg[++len]=x%10ll;x/=10ll;}
	for(int i=len;i>=1;i--)putchar(dg[i]+48);
}
inline void NTT(_LL *f,int o) {
    for(re int i=0;i<len;i++) if(i<rev[i]) std::swap(f[i],f[rev[i]]);
    for(re int i=2,k=0;i<=len;i<<=1,k++) {
        int ln=i>>1;
        LL og1;
        if(!mi[o][k]) {mi[o][k]=og1=ksm(G[o],(mod-1)/i);}
        else og1=mi[o][k];
        for(re int l=0;l<len;l+=i) {
        	og=1;
            for(re int x=l;x<ln+l;++x) {
                t=(f[ln+x]*og)%mod;
                f[ln+x]=(f[x]-t+mod)%mod;
                f[x]=(f[x]+t)%mod;
                og=(og*og1)%mod;
            }
        }
    }
    if(!o) return;
    _LL inv=ksm(len,mod-2);
    for(re int i=0;i<len;i++) f[i]=(f[i]*inv)%mod;
}
void dfs(int x,int Fa) {
    ++k;
    fa[x]=Fa;vis[x]=1;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(vis[e[i].v]) continue;
        dfs(e[i].v,Fa); 
    }
}
void Dfs(int x,int fa,int p) {
    for(re int i=head[x];i;i=e[i].nxt) {
        if(e[i].v==fa) continue;
        pre[e[i].v]=pre[x]+e[i].w;
        if(pre[e[i].v]<Y) tax[p][pre[e[i].v]]++;
            else tp[p]+=pre[e[i].v];
        Dfs(e[i].v,x,p);
    }
}
inline void mul() {
    NTT(A,0),NTT(B,0);
    for(re int i=0;i<len;i++) A[i]=(A[i]*B[i])%mod;
    NTT(A,1);
    for(re int i=0;i<Y;i++) A[i]%=P;
    //中间取模的简易版任意模数NTT
    for(re int i=Y;i<len;i++) A[i]=0;
}
int main() {
    G[0]=19ll,G[1]=ksm(19ll,mod-2);
    n=read(),m=read(),X=read(),Y=read();
    for(re int x,y,z,i=1;i<=m;i++)
        x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z);
    LL cnt=0,H=0,T=0;
    for(re int i=1;i<=n;i++)
    if(!vis[i]) {
        k=0;++tot,dfs(i,tot); 
        k=k*(k-1ll)/2ll;sum[tot]=k;
        tmp=(tmp*k)%P;
    }
    Y-=tot*X;
    for(re int i=1;i<=n;i++) pre[i]=0,Dfs(i,0,fa[i]);
    A[0]=1;len=1;while(len<Y+Y) len<<=1;
    for(re int i=0;i<len;i++) rev[i]=rev[i>>1]>>1|((i&1)?len>>1:0);
    for(re int i=1;i<=tot;i++) {
        for(re int j=0;j<len;j++) B[j]=0;
        LL inv=tmp*getInv(sum[i])%P;
        for(re int j=0;j<Y;j++) {
            B[j]=(tax[i][j]/2);
            H+=(inv*(LL)j%P*(LL)(tax[i][j]/2ll)%P);
            H%=P;
        }
        H+=inv*(tp[i]/2ll)%P;H%=P;
        mul();
    }
    //H是所有环的长度和，tmp是所有环的方案数
    //cnt是不满足条件的环的方案数，T是不满足条件的环的长度和
    for(re int i=1;i<Y;i++) 
        cnt=(cnt+A[i])%P,T=(T+A[i]*(LL)i%P)%P;
    H=(H-T+P)%P;
    tmp=(tmp-cnt+P)%P;
    H+=tmp*(LL)tot%P*(LL)X%P;H%=P;
    if(tot==1) {write(H);return 0;}
    if(tot==2) write(H*2ll%P);
    else {
        LL pw=2,now=4;tot-=2;
        for(re int i=1;i<=tot;i++)
            pw=(pw*now)%P,now=(now+2ll)%P;
        write(H*pw%P);
    }
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

首先先把每个连通块找出来。计算出每个连通块长度为 $t$ 的链的数量。

考虑简单问题：不对环的长度求和，只算方案数。

接下来考虑 $dp_{i,j}$ 表示看到第 $i$ 个环，目前整个的长度跟 $y$ 取 $\min$ 是 $j$ 的不同连接方案数。我们可以暂时不考虑顺序，在最后乘上 $\frac{cnt}{2}!$ 即可，其中 $cnt$ 为环数。

考虑转移，暴力转移就是对的。

证明：对于所有点数不超过 $\sqrt n$ 的连通块，其不同长度路径数至多为 $n\sqrt n$。而对于所有点数超过 $\sqrt n$ 的连通块，其不同长度路径数至多是 $y$。故总转移数是 $O((n+y)\sqrt n)$ 的。由于每次有 $y$ 个状态转移，总复杂度是 $O((n+y)y\sqrt n)$。

对于方案数，我们考虑 $f_{i,j}$，表示所有方案的环长度之和。每次 $f_{i,j}$ 既可以从 $f_{i-1,k}$ 转移，也可以从 $dp_{i-1,k}$ 通过长度的系数转移。复杂度一样。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
using namespace std;
const int mod=1e9+7,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005];
void init(){
	fac[0]=1; for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[1000000]=qp(fac[1000000],mod-2); for(int i=999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
vector<pair<int,int>> vc[100005];
int f[100005],siz[100005],cnt[3005][3005],val[3005][3005],rn[3005],cntt;
int dp2[3005][3005][2],y;
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
void dfs(int now,int fa,int rt,int dep){
	if(fa) cnt[rn[find(rt)]][min(dep,y)]++,(val[rn[find(rt)]][min(dep,y)]+=dep)%=mod;
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs(v.first,now,rt,dep+v.second);
	}
}
signed main(){
	init();
	int n,m,x,ans=0; cin>>n>>m>>x>>y;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
		vc[v].push_back(make_pair(u,w));
		f[find(u)]=find(v);
	}
	for(int i=1;i<=n;i++) if(find(i)==i) rn[i]=++cntt;
	for(int i=1;i<=n;i++) dfs(i,0,i,0);
	{
		int st=min(y,(n-m)*x);
		dp2[0][st][0]=1;dp2[0][st][1]=(n-m)*x;
		for(int i=1;i<=cntt;i++){
			for(int k=0;k<=y;k++){
				if(cnt[i][k]){
					for(int j=0;j<=y;j++){
						(dp2[i][min(j+k,y)][0]+=dp2[i-1][j][0]*cnt[i][k])%=mod;
						(dp2[i][min(j+k,y)][1]+=dp2[i-1][j][1]*cnt[i][k]+dp2[i-1][j][0]*val[i][k])%=mod;
					}
				}
			}
		}
		(ans+=dp2[cntt][y][1]*fac[n-m-1]%mod*inv2)%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：psoet (赞：1)

~~为啥全网都是奇怪复杂度做法。~~

一种直接的想法是，先求出每个连通块每种权值的路径数然后卷积。这样做看上去很劣，但是大家可以分析出来如果只转移非0的位置复杂度是 $O(\sum_{i}\sqrt{s_i^2Y}Y) = O(nY\sqrt Y)$。

事实上我们可以简单地规避掉卷积，只需每次加一条边即可。对于每个连通块，我们跑两次树形dp（一次往上，一次往下）求出方案数，加边相当于往01背包内加一个物品，同时开一个全局数组记录答案。每处理完一个连通块后，我们得到了在已处理过的所有连通块中各选一条路径的方案数。注意在 lca 处需要进行一些处理防止算重。这样就不用卷积，复杂度是 $O(nY)$ 的。

```cpp
#include <bits/stdc++.h>

#define For(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define rFor(i, b, a) for (int i = b, i##end = a; i >= i##end; --i)
#define eFor(i, u, v) for (int i = head[u], v = e[i].to; i; i = e[i].next, v = e[i].to)

typedef long long ll;

typedef std::pair<int, int> pii;
#define fi first
#define se second

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template<typename T> 
T myrand(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(rnd);
}

template<typename T, typename ...Args> 
void LOG(T str, Args ...args) {
#ifdef DEBUG
	fprintf(stderr, str, args...);
#endif
}

#define fre(s) freopen(#s ".in", "r", stdin), freopen(#s ".out", "w", stdout)

const int kN = 1505;
const int kM = 2505;
const int P = 1e9 + 7;

int n, m, X, Y, inv[kN], f[kN], head[kN], ecnt = 1;

inline int norm(int x) {
	return x >= P ? x - P : x;
}

struct Arc {
	int next, to, w;
} e[kN << 1];

void addEdge(int from, int to, int w) {
	e[ecnt] = (Arc) {
		head[from], to, w
	};
	head[from] = ecnt++;
}

int vid[kN], tot, up[kN][kM], dn[kN][kM], s[kN], fe[kN], d[kM], nd[kM], bsz[kN], sum[kN][kM];

void dfs1(int u) {
	vid[++tot] = u;
	For(i, 0, Y) up[u][i] = d[i];
	s[u] = 1;
	eFor(i, u, v) if (v != f[u]) {
		f[v] = u;
		fe[v] = e[i].w;
		dfs1(v);
		s[u] += s[v];
		rFor(j, Y, e[i].w) up[u][j] = norm(up[u][j] + up[v][j - e[i].w]);
	}
}

void dfs2(int u) {
	bsz[u] = tot;
	For(j, 0, Y) nd[j] = norm(nd[j] + dn[u][j]);
	eFor(i, u, v) if (v != f[u]) {
		rFor(j, Y, e[i].w) dn[v][j] = norm(dn[v][j] + dn[u][j - e[i].w]);
		dfs2(v);
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &X, &Y);
	For(i, 1, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w), addEdge(v, u, w);
	}
	inv[1] = 1;
	For(i, 2, n) inv[i] = P - (ll)inv[P % i] * (P / i) % P;
	d[0] = 1;
	int coe = 1, all = 1, ans = 0;
	For(u, 1, n) if (!f[u] && head[u]) {
		memset(nd, 0, sizeof(nd));
		tot = 0;
		dfs1(u);
		all = (ll)all * tot % P * (tot - 1) % P;
		For(i, 2, tot) {
			For(j, 0, Y - fe[vid[i]]) 
				sum[f[vid[i]]][j + fe[vid[i]]] = norm(sum[f[vid[i]]][j + fe[vid[i]]] + up[vid[i]][j]);
		}
		For(i, 1, tot) {
			For(j, 0, Y) {
				nd[j] = norm(nd[j] + sum[vid[i]][j]);
				sum[vid[i]][j] = norm(sum[vid[i]][j] + d[j]);
			}
			eFor(j, vid[i], v) if (v != f[vid[i]]) {
				rFor(k, Y, e[j].w) {
					dn[v][k] = norm(sum[vid[i]][k - e[j].w] + P - (k >= e[j].w * 2 ? up[v][k - 2 * e[j].w] : 0));
				}
			}
		}
		dfs2(u);
		std::copy(nd, nd + Y + 1, d);
	}
	For(i, 2, n - m - 1) coe = (ll)coe * i % P;
	For(i, 1, n) if (f[i]) {
		ans = (ans + (ll)fe[i] * s[i] % P * (bsz[i] - s[i]) % P * coe % P * all % P * inv[bsz[i]] % P * inv[bsz[i] - 1]) % P;
	}
	ans = (ans + (ll)all * coe % P * inv[2] % P * (n - m) % P * X) % P;
	For(i, 1, Y - X * (n - m) - 1) {
		ans = norm(ans + P - (ll)d[i] * coe % P * inv[2] % P * (i + (ll)(n - m) * X % P) % P);
	}
	printf("%d", ans);
	return 0;
}
/* PAY ATTENTION TO: */
/* 1. Memory Limit, Array Size */
/* 2. Integer Overflow */
/* 3. Multi-test */
/* 4. Potential Constant-speedup */
/* Stay organized and write things down. */

```

---

## 作者：muller (赞：0)

觉得xyx讲的非常好

就用一下他的写法吧

考虑用所有的路径减去不合法的路径的长度。

所有路径的长度是容易计算的，只需要考虑每一条边被统计了多少次。

不合法的路径即长度不足 Y 的路径，可以通过每一个联通块内路径的数组卷积得到。

注意到当且仅当联通块大小达到 的级别，

不足 Y 的所有路径长度才有可能被全部取到，

因此在卷积时特判数组中为 0的位置跳过即可。

所以我们暴力枚举即可

复杂度多一个根号：

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1e9 + 7;
const int N = 2505;
int to[N << 1], nxt[N << 1], len[N << 1], fir[N], bel[N], fa[N], ecnt, cnt, x, y;
ll tot[N][N], f[N][2], g[N][2], sum[N][N], ans;
template <typename T> inline void upd(T &a, T b) {a = (a + b) % p;}
int find(int u) {return fa[u] = fa[u] == u ? u : find(fa[u]);}
void ae(int u, int v, int w) {to[++ecnt] = v; nxt[ecnt] = fir[u]; len[ecnt] = w; fir[u] = ecnt;}
void build(int u, int f, int id) {
    int v, i;
    bel[u] = id;
    for (i = fir[u]; i; i = nxt[i]) {
        v = to[i];
        if (v != f) build(v, u, id);
    }
}
void dfs(int u, int f, int l) {
    int v, w, i;
    if (f) {upd(sum[bel[u]][min(l, y)], 1ll * l); ++tot[bel[u]][min(l, y)];}
    for (i = fir[u]; i; i = nxt[i]) {
        v = to[i]; w = len[i];
        if (v != f) dfs(v, u, l + w);
    }
}
int main() {
    int n, m, now, u, v, w, i, j, k;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (i = 1; i <= n; ++i) fa[i] = i;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        ae(u, v, w); ae(v, u, w);
        fa[find(u)] = find(v);
    }
    for (i = 1; i <= n; ++i) if (i == find(i)) build(i, 0, ++cnt);
    for (i = 1; i <= n; ++i) dfs(i, 0, 0);
    now = min(cnt * x, y); f[now][0] = 1; f[now][1] = cnt * x;
    for (i = 1; i <= cnt; ++i) {
        for (j = now; j <= y; ++j) {g[j][0] = f[j][0]; g[j][1] = f[j][1]; f[j][0] = f[j][1] = 0;}
        for (j = 0; j <= y; ++j)
            if (tot[i][j])
                for (k = now; k <= y; ++k)
                    if (g[k][0]) {
                        upd(f[min(j + k, y)][0], 1ll * g[k][0] * tot[i][j]);
            			upd(f[min(j + k, y)][1], 1ll * g[k][0] * sum[i][j] + 1ll * g[k][1] * tot[i][j]);
                    }
    }
    ans = f[y][1];
    for (i = 1; i < cnt; ++i) ans = ans * i % p;
    printf("%lld\n", ans * 500000004 % p);
    return 0;
}

```


---

## 作者：DerrickLo (赞：0)

我们发现这个环一定经过了这 $K$ 条新加的边，然后对于每一颗树，这个环恰好会经过一条路径。那么我们先考虑无序的情况，然后再乘上围成一个环的情况数，即 $\frac{(K-1)!}{2}$ 。

那么我们考虑先求出所有方案的环长之和，然后减去 $<Y$ 的环长之和就是答案了。

设 $sz_i$ 表示第 $i$ 个连通块的大小，$v_i$ 表示第 $i$ 个连通块所有点组成的集合。显然所有方案有 $\displaystyle{\prod_{i=1}^{K}2\dbinom{sz_i}{2}}$ 种，其中 $sz_i$ 表示第 $i$ 个连通块的大小。对于新加的边可以直接算贡献，而原来的边的贡献就是 $\displaystyle{\sum_{i=1}^{K}((\sum_{j\ne k,j,k\in v_i}\operatorname{dist}(i,j))\prod_{j=1}^{K}[j\ne i]2\dbinom{sz_i}{2})}$，这可以直接 $\mathcal O(n^2)$ 计算。

然后先将 $Y$ 减去 $KX$，考虑对于每个连通块 $x$，先预处理出对于 $0\le k \le p$，$\operatorname{dist}(i,j)=k$ 的点对 $(i,j)$ 的数量 $cnt_{x,k}$，然后记 $f_{i,j}$ 表示考虑完前 $i$ 个连通块，总长度是 $j$ 的方案数，转移很简单：

$$f_{i,j}=\sum_{k=0}^{j}cnt_{i,k}\times f_{i-1,j-k}$$

但是这样复杂度不对。考虑只枚举 $cnt_{i,k}\neq 0$ 的 $k$，我们发现这样做就能做到 $\mathcal O(Y(N+Y)\sqrt N)$。

  为什么呢？可以类似根号分治地证明。考虑对于 $sz_i<\sqrt n$，转移次数是 $\displaystyle{\sum sz_i^2\le (\sum sz_i)sz_i\le n\sqrt n}$ 的；而对于 $sz_i\ge \sqrt n$，注意到路径长度至多为 $Y$，所以转移次数是 $Y\sqrt n$ 的。合起来就是 $(N+Y)\sqrt n$，而每次转移都会执行 $\mathcal O(Y)$ 次，所以总复杂度就是 $\mathcal O(Y(N+Y)\sqrt N)$的。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int n,m,k,x,y,u,v,w,cnt,sz[1505],fr[1505],dis[1505][1505],a[1505][2505],f[1505][2505],cntt=1,ans,inv2,fac[1505];
vector<pair<int,int>>ve[1505];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
void dfs(int u,int fa){
	fr[u]=cnt,sz[cnt]++;
	for(auto v:ve[u]){
		if(v.first==fa)continue;
		dfs(v.first,u);
	}
}
void dfs1(int u,int fa,int s){
	for(auto v:ve[u]){
		if(v.first==fa)continue;
		dis[s][v.first]=dis[s][u]+v.second;
		dfs1(v.first,u,s);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>x>>y,k=n-m,inv2=ksm(2,mod-2),fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=m;i++)cin>>u>>v>>w,ve[u].emplace_back(v,w),ve[v].emplace_back(u,w);
	for(int i=1;i<=n;i++)if(!fr[i]){
		cnt++;
		dfs(i,0);
		for(int j=1;j<=n;j++)if(fr[j]==cnt)dfs1(j,0,j);
	}
	for(int i=1;i<=cnt;i++)cntt*=sz[i]*(sz[i]-1)%mod,cntt%=mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans+=dis[i][j]*cntt%mod*ksm(sz[fr[i]]*(sz[fr[i]]-1)%mod,mod-2)%mod,ans%=mod;
	ans+=k*x%mod*cntt%mod,ans%=mod;
	if(y<=k*x)cout<<ans*fac[cnt-1]%mod*inv2%mod,exit(0);
	y-=k*x;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&fr[i]==fr[j]&&dis[i][j]<y)a[fr[i]][dis[i][j]]++;
	f[0][0]=1;
	for(int i=1;i<=cnt;i++)for(int j=0;j<=y;j++)if(a[i][j])for(int k=j;k<=y;k++)f[i][k]+=f[i-1][k-j]*a[i][j]%mod,f[i][k]%=mod;
	for(int i=0;i<y;i++)ans-=f[cnt][i]*(i+k*x)%mod,ans+=mod,ans%=mod;
	cout<<ans*fac[cnt-1]%mod*inv2%mod;
	return 0;
}
```

---

