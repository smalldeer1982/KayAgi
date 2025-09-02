# Big Problems for Organizers

## 题目描述

The Finals of the "Russian Code Cup" 2214 will be held in $ n $ hotels. Two hotels (let's assume that they are the main hotels), will host all sorts of events, and the remaining hotels will accommodate the participants. The hotels are connected by $ n-1 $ roads, you can get from any hotel to any other one.

The organizers wonder what is the minimum time all the participants need to get to the main hotels, if each participant goes to the main hotel that is nearest to him and moving between two hotels connected by a road takes one unit of time.

The hosts consider various options for the location of the main hotels. For each option help the organizers to find minimal time.

## 样例 #1

### 输入

```
3
2 3
3 1
3
2 1
2 3
3 1
```

### 输出

```
1
1
1
```

## 样例 #2

### 输入

```
4
1 4
1 2
2 3
3
1 4
1 3
2 3
```

### 输出

```
2
1
2
```

# 题解

## 作者：Erusel (赞：6)

我们考虑先预处理出直径，然后倍增维护直径上区间 $w_i$ 的最大值，

$w_i$ 表示该点子树内的点到直径两端点的最大值

可以用RMQ预处理，做到单次查询$O(1)$

然后我们考虑查询，对于每次查询

最远点只有可能是两种情况，一种是到两个主旅馆距离差不超过$1$的点

或者是直径端点，所以我们可以大力分类讨论 $u,v$ 的情况

时间复杂度 $O(nlogn+m)$ 

**Code:**

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define inf 1e9

#define N 100005

using namespace std;

int n,m;
vector<int>e[N],rec;
const int B=17;
int fa[N],tp[N],f[N],vis[N];
int maxlen,pos,dep[N];
int st[2][18][N],lg[N];
const int base=2333,p=19260817;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

inline void addEdge(int u,int v){e[u].push_back(v);}

void dfs(int u,int faa,int dis,int flg)
{
	if(maxlen<dis)maxlen=dis,pos=u;
	if(flg)fa[u]=faa;
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==faa)continue;
		dfs(v,u,dis+1,flg);
	}
}//求直径长度 

void dfss(int u,int fa,int top)
{
	f[top]=max(f[top],dep[u]),tp[u]=top;//tp[i]表示i所在链的最顶端 
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==fa)continue;
		if(vis[v])continue;
		dep[v]=dep[u]+1,dfss(v,u,top);
	}
}

inline int query(int k,int l,int r)
{
	if(l>r)return -inf;int t=lg[r-l+1];
	return max(st[k][t][l],st[k][t][r-(1<<t)+1]);
}//O(1)查询 

inline int Hash(string s)
{
	long long ans=0;
	for(int i=0;i<s.length();i++)ans=(ans*base+s[i])%p;
	return (int)ans;
}

int ans;

signed main()
{
	rd(n),lg[1]=0;for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;//预处理log2 
	for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);
	rd(m),dfs(1,0,0,0),maxlen=0,dfs(pos,0,0,1);int u=pos;rec.push_back(Hash("I AK IOI"));
	while(u)vis[u]=1,rec.push_back(u),u=fa[u];int tot=rec.size()-1;
	for(int i=1;i<=tot;i++)dfss(rec[i],0,i);
	for(int i=1;i<=tot;i++)st[0][0][i]=i+f[i],st[1][0][i]=f[i]-i;//初始化 
	for(int k=0;k<=1;k++)
		for(int i=1;i<=B;i++)
			for(int j=1;j+(1<<i)-1<=tot;j++)
				st[k][i][j]=max(st[k][i-1][j],st[k][i-1][j+(1<<(i-1))]);//预处理ST表 
	while(m--)
	{
		int x,y,ans=0;rd(x),rd(y);
		if(tp[x]>tp[y])swap(x,y);
		if(tp[x]==tp[y]){ans=min(dep[x],dep[y])+max(tot-tp[x],tp[x]-1);printf("%d\n",ans);continue;}
		int mid=(tp[x]+tp[y]-dep[x]+dep[y]);
		if((tp[x]<<1)>=mid)ans=dep[y]+max(tot-tp[y],tp[y]-1);
		else if((tp[y]<<1)<=mid)ans=dep[x]+max(tot-tp[x],tp[x]-1);
		else ans=max(max(query(0,tp[x]+1,mid>>1)-tp[x],tp[x]-1)+dep[x],max(tot-tp[y],query(1,(mid>>1)+1,tp[y]-1)+tp[y])+dep[y]);//根据中点分类讨论 
		printf("%d\n",ans);
	}
	

    return 0;
}
```

---

## 作者：LinkyChristian (赞：2)

受不了，假题解害人不浅。

> 给定一棵树，每次询问两个点 $x,y$，找出一个点 $u$ 使得 $\min(dis(u,x),dis(u,y))$ 最大。

将直径上的点从 $1$ 到 $tn$ 标号，则由于任意一条链长度不能超过直径，直径上第 $i$ 个点子树中的最长链长度 $mx_i$ 最多为 $\min(i-1,tn-i)$。

回到题目，设 $x,y$ 对应的直径上的点为 $tx,ty$。设 $tx \le ty$，直径上点 $1\sim tx$ 的任意点 $i$ 的最长链 $mx_i$ 到 $x$ 的距离 $mx_i+tx-i+dep_x \le tx-1+dep_x$（这里的 $dep_x$ 指 $x$ 到直径任意点的最短距离），而后者是直径端点 $1$ 到 $x$ 的距离。同理可得，直径上 $ty\sim tn$ 的任意点的最长链到 $y$ 的距离都小于等于 $tn$ 到 $y$ 的距离。

因此我们可以得出结论：可能成为答案的点只有可能是直径端点或是给定两点对应的直径上的点之间的直径某一点的最长链。我们采用 st表 维护 $mx_i$，处理出离 $x$ 更近与离 $y$ 更近的分界点后查询即可。

```cpp
#include<bits/stdc++.h>
#define N 100010
#define pb push_back
using namespace std;
int n,m,d1,d2,mx,mxl,fa[N],vis[N],t1[22][N],t2[22][N],mp[N];
vector<int> to[N];
void dfs(int now,int ff,int dis) {
    if(dis>mxl) mxl=dis,mx=now;fa[now]=ff;
    for(int v:to[now]) if(v!=ff&&!vis[v]) dfs(v,now,dis+1);
}
int query1(int l,int r) {if(l>r) return -1e9;int k=log2(r-l+1); return max(t1[k][l],t1[k][r-(1<<k)+1]);}
int query2(int l,int r) {if(l>r) return -1e9;int k=log2(r-l+1); return max(t2[k][l],t2[k][r-(1<<k)+1]);}
int a[N],an;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1; i<n; i++) {
        int u,v;cin>>u>>v;
        to[u].pb(v),to[v].pb(u);
    }
    dfs(1,0,0),d1=mx,mxl=0;
    dfs(d1,0,0),d2=mx;int tmp=d2;
    while(tmp!=d1) vis[tmp]=1,a[++an]=tmp,tmp=fa[tmp];
    vis[d1]=1,a[++an]=d1;
    for(int i=1; i<=an; i++) mxl=0,dfs(a[i],0,0),t1[0][i]=mxl+i,t2[0][i]=mxl+an-i,mp[a[i]]=i;
    for(int k=1; k<20; k++)
        for(int i=1; i+(1<<k)-1<=an; i++) 
			t1[k][i]=max(t1[k-1][i],t1[k-1][i+(1<<(k-1))]),
			t2[k][i]=max(t2[k-1][i],t2[k-1][i+(1<<(k-1))]);
    cin>>m;
    while(m--) {
        int x,y,xl=0,yl=0; cin>>x>>y;
        while(!vis[x]) x=fa[x],xl++;x=mp[x];
        while(!vis[y]) y=fa[y],yl++;y=mp[y];
        if(x>y) swap(x,y),swap(xl,yl);
        if(x==y) xl=yl=min(xl,yl);
        int ans=max(min(xl+x-1,yl+y-1),min(yl+an-y,xl+an-x));
        int res=(x+y+yl-xl)/2;
        ans=max(ans,max(xl+query1(x+1,res)-x,yl+query2(res+1,y-1)-(an-y)));
        printf("%d\n",ans);
    }
}
```


---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF418D *2800}$

> - 给定 $n$ 个点的树（边无权）和 $m$ 次询问，每次给定 $u,v$，求 $\max \limits_{i=1}^n \{\min(dis(u,i),dis(v,i))\}$。
> - $1 \le n,m \le 10^5$。

找到 $u,v \; (dep_u \ge dep_v)$ 的路径中点 $k$，显然 $k$ 子树内的点离 $u$ 近，子树外离 $v$ 近。

然后我们有经典结论，一棵树上距离定点 $u$ 最远的点 $v$ 一定是树的直径的一端。

因此 st 表维护 dfn 序的区间直径即可，时间复杂度 $\mathcal O((n+m) \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 06.05.2024 17:55:11
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,u,v,dfn[N],ta[N],tot,fa[N][20],dep[N],siz[N]; vector<int> g[N];
int op(int a,int b){return (dfn[a] < dfn[b] ? a : b);}
template <class S,S (*op)(S,S)> struct stb{
    S st[20][N];
    void init(S *h){
        for(int i = 1;i <= n;i ++) st[0][i] = h[i];
        for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
            st[j][i] = op(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }S qry(int l,int r){
        int k = __lg(r - l + 1);
        return op(st[k][l],st[k][r-(1<<k)+1]);
    }
};stb<int,op> st;
struct S{int u,v;}tb[N];
int lca(int u,int v){
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
    return st.qry(u+1,v);
}int dis(int u,int v){return dep[u] + dep[v] - 2 * dep[lca(u,v)];}
S op(S a,S b){
    if(!a.u) return b; if(!b.u) return a;
    vector<int> acc = {a.u,a.v,b.u,b.v}; int mx = -1; S ans = {0,0};
    for(int i : acc) for(int j : acc) if(int x = dis(i,j); x > mx) mx = x,ans = {i,j};
    return ans;
}stb<S,op> ts;
void dfs(int u,int f){
    ta[dfn[u] = ++tot] = fa[u][0] = f,dep[u] = dep[f] + 1,tb[dfn[u]] = {u,u},siz[u] = 1;
    for(int i = 1;i <= 18;i ++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}int kfa(int u,int k){for(int i = 18;i >= 0;i --) if((k >> i) & 1) u = fa[u][i];return u;}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    dfs(1,0),st.init(ta),ts.init(tb),cin >> m;
    while(m --){
        cin >> u >> v; int d = lca(u,v),x = dis(u,v),ans = 0;
        if(dep[u] < dep[v]) swap(u,v);
        int k = kfa(u,(x - 1) >> 1);
        auto qry = [&](int u,int l,int r){
            if(l > r || r < 1 || l > n) return 0;
            auto [x,y] = ts.qry(l,r);
            return max(dis(u,x),dis(u,y));
        };  cout << max(qry(u,dfn[k],dfn[k]+siz[k]-1),max(qry(v,1,dfn[k]-1),qry(v,dfn[k]+siz[k],n))) << "\n";

    }
}
```

---

## 作者：comcopy (赞：0)

通过链的部分分，很自然发现以下性质：

对于点对 $(u,v)$ 的询问，一个点其子树内的点必然是到这个点上的。

对于 $(u,lca,v)$ 这条路径上的点，我们需要从中挑出一个最中间的点并拎出来，但很显然我们的时间并不支持我们将其重新拎出来跑一遍。

令 $x$ 表示其中间点，我们分类讨论为四部分:

从 $u$ 到 $x$ 上的所有点及其子树都是到 $u$ 的。

从 $x$ 到 $lca$ 上的所有点及其子树需要先经过 $lca$ 再到 $v$。

从 $v$ 到 $lca$ 上的所有点及其子树都是到 $v$ 的。

从 $lca$ 到 $rt$ 上的所有点及其子树都是先到 $lca$ 再到距离 $lca$ 最近的那个点。

考虑对 1,3,4 三种情况的讨论，我们都是维护一个链及其子树内的点到链底的最大值。

易得公式：

$$
dis(u,v) = dp_u+dp_v-2\times dp_{\operatorname{lca}(u,v)}
$$

很显然对于链底是常量，我们提出来以后把公式放进线段树维护最大值就行了。

对于第 2 种情况很显然是求到链顶的最大距离，直接求深度最大值就行了。

这里我们需要额外考虑对于 $lca$ 的维护，因为对于 $lca$ 来说 $u,v$ 可能会在它的最深点，次深点所在的子树内，所以我们需要额外维护一个次次深得点。

看到这里，你会想这不是倍增秒了吗？三个倍增解决所有事情！

但是，我要对倍增说不！

~~考试的时候一眼长链剖分但是挂了。~~

没错，掏出我们的长链剖分。

由于长链剖分的特性，我们跳链的时候就不用像倍增一样考虑是不是重儿子的情况。

很显然对于一条重链来说，除了刚跳上这个重链的这个点需要查一下最大值，其上面的所有点都是查次大值，因为其最大值的那个点必然会经过其重链以下的儿子。

线段树维护一下四个值，跳就行了。

然后我们跳的时候特意避开 $lca$，在外面额外进行分类讨论就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool _u(char x){return x>='0'&&x<='9';}
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!_u(ch);ch=='-'&&(f=-f),ch=getchar());
	for(;_u(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	return x*f;
}
inline void write(int num,bool flag=0){
	static int st[39],tp=0;
	num<0&&(putchar('-'),num=-num);
	do st[++tp]=num%10;while(num/=10);
	while(tp) putchar(st[tp--]|48);
	putchar(flag?'\n':' ');
	return;
}
template <typename... Args>
inline void write(int t, Args... args) {
	write(t),write(args...);
}
const int N=1e5+10,inf=1e9;
vector<int>e[N];
int n,m;
int in[N];
pair<int,int>q[N];
namespace point4{
	bool flag=true;
	int dfn[N],tot;
	inline void dfs(int u,int f){
		dfn[u]=++tot;
		for(int to:e[u])
			if(to!=f) dfs(to,u);
		return;
	}
	inline void solve(){
		for(int i=1;i<=n;++i)
			if(in[i]==1){
				dfs(i,0);
				break;
			}
		for(int u,v,i=1;i<=m;++i){
			u=dfn[q[i].first],v=dfn[q[i].second];
			if(u>v)swap(u,v);
			write(max(max(u-1,n-v),(v-u)/2),true);
		}
		return;
	}
}
namespace pts100{
	bool flag=true;
	int dp[N][3];//dp[i][0] 表示 i 的子树内的最大dep,dp[i][1] 表示去掉最大的所在子树的次大,dp[i][2]次次大 
	int fa[N],dep[N],sz[N],hev[N];
	int fy[N][20];
	inline void update(int x,int val){
		for(int i=0;i<3;++i) if(val>dp[x][i])swap(val,dp[x][i]);
		return;
	}
	inline void dfs(int u,int f){
		dp[u][0]=dep[u]=dep[fy[u][0]=fa[u]=f]+1,hev[u]=0,sz[u]=1;
		for(int i=1;i<20;++i) fy[u][i]=fy[fy[u][i-1]][i-1];
		for(int to:e[u])
			if(to!=f) dfs(to,u),sz[u]+=sz[to],hev[u]=(!hev[u]||dp[to][0]>dp[hev[u]][0]?to:hev[u]),update(u,dp[to][0]);
		return;
	}
	int top[N],dfn[N],tot,rnk[N];
	inline void dfs1(int u,int tp){
		top[rnk[dfn[u]=++tot]=u]=tp;
		if(hev[u]) dfs1(hev[u],tp);
		for(int to:e[u])
			if(to!=fa[u]&&to!=hev[u]) 
				dfs1(to,to);
		return;
	}
	struct fffffyn{
		struct fynnode{
			int a,b,c,d;
			fynnode(int k=-inf,int x=-inf,int y=-inf,int z=-inf):a(k),b(x),c(y),d(z){}
			inline friend fynnode operator+(fynnode x,fynnode y){
				return fynnode(max(x.a,y.a),max(x.b,y.b),max(x.c,y.c),max(x.d,y.d));
			} 
		}b[N<<2];
		#define MID(l,r) (((r-l)>>1)+l)
		#define ls (now<<1)
		#define rs (now<<1|1)
		inline void pushup(int now){
			return void(b[now]=b[ls]+b[rs]);
		}
		inline void build(int l,int r,int now){
			if(l==r) return void(b[now]=fynnode(dp[rnk[l]][0]-2*dep[rnk[l]],dp[rnk[l]][1]-2*dep[rnk[l]],dp[rnk[l]][0],dp[rnk[l]][1]));
			int mid(MID(l,r));
			build(l,mid,ls),build(mid+1,r,rs);
			return pushup(now);
		}
		inline fynnode query(int l,int r,int nl,int nr,int now){
			if(l<=nl && nr<=r) return b[now];
			int mid(MID(nl,nr));
			return (l<=mid?query(l,r,nl,mid,ls):fynnode())+(mid<r?query(l,r,mid+1,nr,rs):fynnode());
		}
	}tre;
	inline int getson(int u,int d){
		if(!d) return u;
		for(int i=19;~i;--i)
			if(d>(1<<i)) d-=(1<<i),u=fy[u][i];
		return fy[u][0];
	}
	inline int LCA(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]>dep[v]?v:u;
	}
	
	inline int get(int u,int v,bool flag,bool tags=0){
		if(dep[u]<dep[v])swap(u,v);
		int nu=dep[u];
		int ans=0;
		for(;top[u]!=top[v];){
			auto x=tre.query(dfn[top[u]],dfn[u],1,tot,1);
			int res=x.b;
			ans=max(ans,res+nu);
			u=fa[top[u]];
			if(u!=v||!tags)ans=max(ans,tre.query(dfn[u],dfn[u],1,tot,1).a+nu);
		}
		if(u==v && tags)return ans;
		auto x=tre.query(dfn[v]+tags,dfn[u],1,tot,1);
		int res=x.b;
		ans=max(ans,res+nu);
		return ans;
	}
	inline int get1(int u,int v,bool flag,bool tags=0){
		if(dep[u]<dep[v])swap(u,v);
		int nu=0;
		int ans=0;
		for(;top[u]!=top[v];){
			auto x=tre.query(dfn[top[u]],dfn[u],1,tot,1);
			int res=x.d;
			ans=max(ans,res+nu);
			u=fa[top[u]];
			if(u!=v||!tags)ans=max(ans,tre.query(dfn[u],dfn[u],1,tot,1).c+nu);
		}
		if(u==v && tags)return ans;
		auto x=tre.query(dfn[v]+tags,dfn[u],1,tot,1);
		int res=x.d;
		ans=max(ans,res+nu);
		return ans;
	} 
	
	inline bool in(int x,int y){//x in y
		return dfn[y]<=dfn[x] && dfn[x]<=dfn[y]+sz[y]-1;
	}
	
	inline int query(int u,int v){
		int lca=LCA(u,v);
		if(dep[u]<dep[v])swap(u,v); 
		int x=getson(u,floor((dep[u]+dep[v]-dep[lca]*2)>>1));
		int ans=-inf;
		ans=max(ans,max(dp[v][in(u,v)]-dep[v],dp[u][0]-dep[u]));//子树内情况，考虑 u 在 v 内的时候需要特判 
		ans=max(ans,get(v,lca,1,1)-dep[v]*in(u,v));//求 v 到 lca，其实对于 u 在 v 内时这条式子是不会有贡献所以特判与否无所谓 
		ans=max(ans,get(u,x,1,x==lca));//求 u 到 x 
		x=((dep[u]+dep[v]-dep[lca]*2)%2?fa[x]:x);//当路径条数为奇数时 x 是到 u 的但是 fa[x] 是到 v 的，为偶数时 x 可以到 u 或 v 
		ans=max(ans,get1(x,lca,in(u,hev[x]),1)-dep[lca]+dep[v]-dep[lca]);//x到lca 
		if(x!=lca && !in(u,hev[x])) ans=max(ans,tre.query(dfn[x],dfn[x],1,tot,1).c-dep[lca]+dep[v]-dep[lca]);//特判 x 的重链，因为分类在外面所以跳的时候没考虑 
		if(lca!=1) { //lca到根 
			ans=max(ans,get(fa[lca],1,1)+min(dep[u],dep[v])-dep[fa[lca]]);
			if(hev[fa[lca]]!=lca) ans=max(ans,tre.query(dfn[fa[lca]],dfn[fa[lca]],1,tot,1).a+min(dep[u],dep[v]));//同上 
		}
		int fv=getson(v,dep[v]-dep[lca]-1);
		if((in(u,hev[lca]) && dp[getson(v,dep[v]-dep[lca]-1)][0]==dp[lca][1]) ||
			(in(v,hev[lca]) && dp[getson(u,dep[u]-dep[lca]-1)][0]==dp[lca][1])) 
				ans=max(ans,dp[lca][2]-dep[lca]+min(dep[u],dep[v])-dep[lca]);  //对 lca 进行分类讨论。 
		else if(in(u,hev[lca]) || in(v,hev[lca])) ans=max(ans,dp[lca][1]-dep[lca]+min(dep[u],dep[v])-dep[lca]);
		else ans=max(ans,dp[lca][0]-dep[lca]+min(dep[u],dep[v])-dep[lca]);
		return ans;
	}
	
	inline void solve(){
		dep[0]=-1;
		dfs(1,0),dfs1(1,1);
		tre.build(1,tot,1);
		for(int i=1,u,v,lca;i<=m;++i)
			write(query(q[i].first,q[i].second),true);
	}
	
} 

signed main(){
	n=read();
	for(int i=1,u,v;i<n;++i)
		u=read(),v=read(),++in[u],++in[v],point4::flag&=(in[u]<=2&&in[v]<=2),e[u].push_back(v),e[v].push_back(u);
	m=read();
	for(int i=1;i<=m;++i) q[i].first=read(),q[i].second=read();
	if(point4::flag) return point4::solve(),(0-0);
	return pts100::solve(),(0-0);
	return(0-0);
}

```


---

