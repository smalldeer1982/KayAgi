# [JDWOI-1] 蜀道难

## 题目背景

蜀道难，难于上青天…… 

蜀道之所以难，就是因为山路崎岖不平。

## 题目描述

小 K 和小 M 也模拟了蜀道难。在蜀道难中，有 $n$ 座山，每座山高度为 $h_i$。小 K 和小 M 有 $m$ 种魔法，每一次膜法可以把连续 $l_i$ 座山的高度抬高或压低 $1$，同时消耗 $c_i$ 点体力。

现在，小 K 和小 M 想让蜀道难的 $n$ 座山的高度不下降，这样蜀道就不难了。请问他们最少需消耗多少体力？

**注**：所有时候山的高度都不能为负。

## 说明/提示

### 样例解释

使用 $1$ 体力值将第三座山升高 $1$。

### 数据范围

- 对于 $10\%$ 的数据，$1\leq n,m \leq 10$；
- 对于另外 $30\%$ 的数据，$1\leq n,m \leq 20$；
- 对于另外 $10\%$ 的数据，$m=1$；
- 对于所有的数据，$1\leq n, m \leq 200$，$1\leq l_i \leq n$，$1\leq h_i, c_i \leq 10^3$。

## 样例 #1

### 输入

```
3 3
1 3 2
- 1 10
- 2 3
+ 1 1```

### 输出

```
1```

# 题解

## 作者：FxorG (赞：10)

为什么这题还不错却没人写题解啊。

考虑序列不降时有什么性质：$a_i-a_{i-1}\ge0,i\in(1,n]$

考虑操作是区间同时加减，想到差分。

记 $d_1=a_1,d_i=a_i-a_{i-1},i\in(1,n]$，那么我们要让 $d_i\ge0,i\in[1,n]$

每次操作即 

```cpp
di--,dj++
di++,dj--
```

那么对于 $d_i>0$ 的，可以最多减 $d_i$ 次，提供 $d_i$ 次加的机会，对于 $d_i<0$ 的，至少被加 $|d_i|$ 次，需要 $d_i$ 次被加。显然转化为二分图之后最小费用最大流。

但是假如只规定正权点向负权点提供流量是不够的，因为可能长度无法匹配导致我们对于 $i,j,d_i>0,d_j<0$ 需要 $k$ 来先让 $i,k$ 操作，再让 $k,j$ 操作来实现。

所以我们要对于每个区间，无论左右是什么点，都连。

代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int rd() {
    int f=1,sum=0; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return sum*f;
}

#define N (int)(5e4+5)
#define inf (int)(2e9)
struct edge {
	int nex,to,w,c;
}e[N<<1];
int hea[N],cnt=1;
int mic[2][N],bian[N];
int n,m,S,T,tot,a[N],b[N],ans;

void add_edge(int x,int y,int z,int c) {
	e[++cnt].nex=hea[x]; e[cnt].to=y; e[cnt].w=z; e[cnt].c=c; hea[x]=cnt;
}

void add(int x,int y,int z,int c) {
	add_edge(x,y,z,c); add_edge(y,x,0,-c);
}

deque<int>q;
bool vis[N];
int dis[N];
bool spfa() {
	for(int i=0;i<N;i++) dis[i]=inf,vis[i]=0;
	q.push_back(S); dis[S]=0;
	while(!q.empty()) {
		int x=q.front(); q.pop_front();
		vis[x]=0;
		for(int i=hea[x];i;i=e[i].nex) {
			int y=e[i].to;
			if(e[i].w&&dis[y]>dis[x]+e[i].c) {
				dis[y]=dis[x]+e[i].c;
				if(!vis[y]) {
					vis[y]=1;
					if(!q.empty()&&dis[y]<dis[q.front()]) q.push_front(y);
					else q.push_back(y);
				}
			}
		}
	}
	return dis[T]<inf;
}

int dfs(int x,int lim) {
	if(x==T||!lim) return lim;
	int flow=0,fl;
	vis[x]=1;
	for(int i=hea[x];i&&lim;i=e[i].nex) {
		int y=e[i].to;
		if(e[i].w&&!vis[y]&&dis[y]==dis[x]+e[i].c) {
			fl=dfs(y,min(lim,e[i].w));
			if(!fl) continue;
			flow+=fl; lim-=fl; e[i].w-=fl; e[i^1].w+=fl;
		//	cout<<e[i].c<<" "<<fl<<endl;
			ans+=e[i].c*fl;
		}
	}
	if(!flow) dis[x]=inf;
	vis[x]=0;
	return flow;
}

void dinic() {
	while(spfa()) {
		memset(vis,0,sizeof(vis));
		dfs(S,inf);
	}
}

int main() {
	n=rd(); m=rd(); S=0; T=n+2;
	for(int i=1;i<=n;i++) b[i]=rd();
	for(int i=1;i<=n;i++) a[i]=b[i]-b[i-1];
	for(int i=0;i<=n+1;i++) mic[0][i]=mic[1][i]=inf;
	char op; int x,y;
	for(int i=1;i<=m;i++) {
		cin>>op; x=rd(); y=rd();
		if(op=='+') op=0; else op=1;
		mic[op][x]=min(mic[op][x],y);
	}
	add(S,n+1,inf,0);
	for(int i=1;i<=n;i++) {
		if(a[i]>0) {
			add(S,i,a[i],0);
		} else {
			add(i,T,-a[i],0); bian[++tot]=cnt-1;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int l=1,r=l+i;r<=n+1;l++,r=l+i) {
			if(mic[0][i]<inf) add(r,l,inf,mic[0][i]);
			if(mic[1][i]<inf) add(l,r,inf,mic[1][i]);
		}
	}
	dinic();
	for(int i=1;i<=tot;i++) {
		if(e[bian[i]].w) {
			printf("-1"); return 0;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：sky_landscape (赞：4)

首先，区间增加定值并且要求单调不降，很容易想到差分。

于是先把 $h$ 数组差分一下，题目的要求即为最小代价使得 $h$ 均为非负数。

观察一下两种操作，发现 $n$ 的范围很小，可以枚举操作的起点 $i$，然后如果操作是压低，相当于 $h[i]$ 减小 $1$，$h[i+l[i]]$ 增大 $1$。

图片放不出来。

而如果操作是抬高，相当于 $h[i]$ 增大 $1$，$h[i+l[i]]$ 减小 $1$。

显然差分数组的总和是一定的（边界有点小问题下文会提及），那么可以把压低当成一条 $i$ 到 $i+l[i]$ 的流，抬高也是同理。

注意当 $i+l[i]-1$ 恰好为 $n$ 时 $i+l[i]$ 为 $n+1$ 但是这个操作显然是合法的，所以要增加一个 $n+1$ 号点，$h[n+1]$ 设为 $h$ 的上限。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;
const int INF=1000000000;
int increase[N],to[N],head[N];
int flow[N],cost[N],nxt[N];
int pre[N];
int maxflow,tot;
bool vis[N];
int dis[N];
int n,m,s,t,ans,a,b;
int h[N];
 
void add(int x,int y,int z,int c){
	to[++tot]=y;
	flow[tot]=z;
	cost[tot]=c;
	nxt[tot]=head[x];
	head[x]=tot;
	to[++tot]=x;
	flow[tot]=0;
	cost[tot]=-c;
	nxt[tot]=head[y];
	head[y]=tot;
}

bool spfa(){
	memset(increase,0x3f,sizeof(increase));
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	int kep=dis[t];
	dis[s]=0;
	queue<int> q;
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=nxt[i]){
			int y=to[i];
			if(flow[i] && dis[y]>dis[x]+cost[i]){
				dis[y]=dis[x]+cost[i];
				increase[y]=min(increase[x],flow[i]);
				pre[y]=i;
				if(!vis[y]){
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	return dis[t]<kep;
}

void update(){
	int cur=t;
	while(cur!=s){
		int last=pre[cur];
		flow[last]-=increase[t];
		flow[last^1]+=increase[t];
		cur=to[last^1];
	}
	maxflow+=increase[t];
	ans+=(increase[t]*dis[t]);
}

inline int read(){
    char ch;int x=0;bool f=false;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    if(f) x=-x;
    return x;
}

signed main(){
	cin>>n>>m;
	s=0,t=n+2;
	h[n+1]=10000;
	tot=1;
	for(int i=1;i<=n;i++){
	    h[i]=read();
    }
    for(int i=n;i>=1;i--){
        h[i]-=h[i-1];
    }
    char c;
    for(int i=1;i<=m;i++){
        cin>>c;
        a=read(),b=read();
        for(int j=1;j<=n-a+1;j++){
            int k=j+a;
            if(c=='-') add(j,k,INF,b);
            else add(k,j,INF,b);
        }
    }
    for(int i=1;i<=n+1;i++){
        //cout<<"h[i]: "<<i<<" "<<h[i]<<"\n";
        add(s,i,h[i]+1001,0),add(i,t,1001,0);
    }
	while(spfa()){
		update();
	}
	if(maxflow!=1001*(n+1)) cout<<-1;
	else cout<<ans;
	return 0;
}
```

---

## 作者：htlhtlhtl (赞：1)

# P7730 蜀道难 题解

## 题意简述
给定一个长度为 $n$ 的正整数数列 $h_1,h_2,...h_n$，以及 $m$ 种操作，第 $i$ 种操作可以将连续的 $l_i$ 个数字同时加上 $o_i$（$o_i\in\{1,-1\}$），同时消耗 $c_i$ 的费用。\
求让整个数列单调不减所需要消耗的最小费用。
## 正文部分
作为网络流的一枚初学者，在做这道题还是产生了一些疑惑的，所以个人觉得有必要将一些细节讲得更清楚一些。

首先，看到区间加减，很容易联想到**差分**。

把数组转成差分数组 $d_i$ 后，为了让序列单调不减，我们需要让所有负数提升到至少 $0$。\
如何实现呢？\
我们的魔法是 $i$ ~ $i+l-1$ 这段数字的区间加减，在差分上的代码操作不用多说，就是`d[i]++,d[i+l]--`或反之。

现在，请把原数组以及原题全部抛之脑后，将题目看做：每次可以用魔法，将某些成对的点一加一减，并消耗一定费用，需要让所有负数不小于 $0$。

然后根据 ~~题目难度和算法标签~~ 数据范围和题意，联想到了**最小费用最大流**算法。

费用流算法，有时会这样出题：\
某些点刚开始，或者必然会带有一定的某种资源，源点就向这些点提供资源（即“流”），也就是源点分别向这些点中的每个点，连一条容量为各自具有的资源量的边。\
而某些点需要资源，各自向汇点连一条容量刚好等于自己需要的资源量的边，这样就能控制最大流不超过这几条边都流满时的流量（如果流不满的话，就是无法提供足够的资源，也就无解）。**这里给出一个不错的理解方式：它们之所以需要资源，就是因为要向汇点交差。**\
以上这两种边的费用通常都是 $0$。\
题中会提供几种要消耗费用的操作，让资源可以在点和点之间传送，也就是点和点之间连边。他们的容量就是这种操作在这两个点之间可以使用的次数，不过一般是无限的。而费用就是这种操作的费用。

本题也是如此。\
我们看，差分数组中，一个点 $+1$，另一个点就 $-1$，像不像是前者有一个 $1$ 传送到了后者？\
如果差分数组中的一个元素本身就 $>0$，那么它本身就持有这么多资源，并且在保持它 $≥0$ 的前提下，可以把它身上的资源传送到别处去，最多可以传送自己持有的全部资源。\
如果差分数组中的一个元素本身就 $<0$，那么它需要资源，这些资源来自那些有资源的点。当然，等到他们的资源充裕了，也可以在保持它 $≥0$ 的前提下资助需要资源的点。

本身持有资源的，它们的资源来自源点，所以从源点连一条容量为持有资源量（实际上因为从源点到它们的边容量已经是这个大小，所以这条边容量也可以是 $\infty$），费用为 $0$ 的边。\
需要资源的，它们要向汇点交差，所以向汇点连一条容量为需要资源量，费用为 $0$ 的边。\
对于每一种魔法，就是每个点都可以往左边（$o_i=1$）或往右边（$o_i=-1$）某个点传送资源，操作次数不限，所以可以提供的资源量任意，但每传送 $1$ 的资源需要花一定费用 $c_i$，所以两者间连一条容量为 $\infty$，费用为这种魔法需要的费用 $c_i$ 的边。

注意：可以将末尾的连续点进行加减，而差分数组中的操作就得再往后推一位，所以存在第 $n+1$ 个点。因为对它没有任何要求，所以他可以持有的资源无限多，也不用交差。从源点连一条容量为 $\infty$，费用为 $0$ 的边即可。

最大流小于差分数组中的所有负数的绝对值（需要交差的资源总和）时就无解。

码风一般。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s,t;
int head[205];
struct edge{
	int to;int nxt;int w;int c;
}e[50005];
int o=1;
void add(int u,int v,int w,int c){
	e[++o]={v,head[u],w,c};
	head[u]=o;
	swap(u,v);
	e[++o]={v,head[u],0,-c};
	head[u]=o;
}
int dis[205];
int vis[205];
int pre[205];
int f[205];
bool bfs(){
	for(int i=1;i<=t;++i) vis[i]=0,f[i]=3e9,dis[i]=3e9;
	pre[t]=0;
	queue<int> q;
	dis[s]=0,vis[s]=0;
	q.push(s);
	while(!q.empty()){
		int k=q.front();q.pop();
		vis[k]=0;
		for(int i=head[k];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[k]+e[i].c){
				dis[v]=dis[k]+e[i].c;
				f[v]=min(f[k],e[i].w);
				pre[v]=i;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return pre[t];
}
signed main(){
	cin>>n>>m;
	s=n+2,t=s+1;
	int sum=0;
	for(int i=1,x=0;i<=n;++i){
		int lx=x;
		cin>>x;
		x-=lx;
		if(x>0) add(s,i,x,0);
		if(x<0){
			add(i,t,-x,0);
			sum-=x;
		}
		x+=lx;
	}
	add(s,n+1,3e9,0);
	while(m--){
		char op;
		int l,c;
		cin>>op>>l>>c;
		if(op=='+'){
			for(int i=1;i<=n+1-l;++i) add(i+l,i,3e9,c);
		}
		else{
			for(int i=1;i<=n+1-l;++i) add(i,i+l,3e9,c);
		}
	}
	int ans1=0,ans2=0;
	while(bfs()){
		for(int x=t,i=pre[t];x!=s;x=e[i^1].to,i=pre[x]){
			e[i].w-=f[t],e[i^1].w+=f[t];
		}
		ans1+=f[t],ans2+=dis[t]*f[t];
	}
	if(ans1<sum) cout<<"-1";
	else cout<<ans2;
	return 0;
}
```

---

## 作者：mqmhaaaa1 (赞：1)

典型的建图思维题 ~~（确信~~

# 题意简化
给你 $m$ 个操作和一个序列，每个操作代价为 $$c_i$$，效果为将长度为 $$w_i$$ 的区间里的数增加或减少 $1$，求最少的代价让序列变成不降序列


---


# 解析
首先能想到差分，也就是说我们可以利用差分把这个序列转化一下，把每个操作变成把差分数组中一个数 $-1$，另一个数 $+1$，目标为让整个差分数组全非负

自然而然的，我们可以把 _一个数 $-1$，另一个数 $+1$_ 这种操作看为一种转移，正是流量的转移

所以我们可以利用无敌的、勇敢的、性感的、神秘的、迷人的、神气的、勤勉的、强势的、华丽的、激情的、可怕的、漂亮的、强大的算法——网络流来解决


---


# 具体实现
先预处理一个差分数组 $g$

如果 $g_i>0$，则源点（下称 $s$）向 $i$ 连一条流量为 $g_i$，费用为 $0$ 的边

反之，如果 $g_i<0$，则向汇点（下称$t$）连一条流量为 $-g_i$  ，费用为 $0$ 的边

之后用每一个操作连边（$u$->$v$,$u$ 为传出流量（$-1$）的那一个，$v$ 为接收流量（$+1$）的那一个），因为每种操作可以用无限次，所以连流量为 $inf$，费用为 $c_i$ 的边，用来进行流量的转移

最后跑费用流，剩下细节看注释

无解情况就是最大流小于连向t所有边流量上界之和的情况

# 为什么对
本人感性理解，欢迎大佬指正

首先 $s$ 向 $g_i>0$ 连是因为这一位最多可以贡献 $g_i$ 的流量且不为负，了解差分性质的都知道正确性显然

而 $g_i<0$ 向t连是因为这一位至少要 $-g_i$ 的流量才不为负，而根据最大流性质，当有解时，这些边一定最后都满流

其他边便是把每个操作变成流量的转移，这个总能理解吧

当t的入边没全部满流（也就是最大流小于连向t所有边流量上界之和，那必然无解

时间复杂度 $O(n^3m)$ 加一点点常数，稳过

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=600,inf=0x7f7f7f7f;
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
ll n,m;
ll a[N];
ll cfsz[N];//差分数组 
ll to[N*N],nxt[N*N],w[N*N],c[N*N],bh[N*N],tot=1;
ll head[N*N]; 
ll realflow,maxflow;
ll s=0,t=N;
void add(ll u,ll v,ll z,ll cost){
	  to[++tot]=v;
	  nxt[tot]=bh[u];
	  w[tot]=z;
	  c[tot]=cost;
	  bh[u]=tot;
	  if(v==t)realflow+=z;
//	  cout<<u<<" "<<v<<" "<<z<<" "<<cost<<endl;
	  to[++tot]=u;
	  nxt[tot]=bh[v];
	  w[tot]=0;
	  c[tot]=-cost;
	  bh[v]=tot;
}

ll dis[N<<1];
bool vis[N<<1];
bool spaf(){
	for(ll i=0;i<=t;i++){
		dis[i]=inf;vis[i]=0;
		head[i]=bh[i];
	}
	queue<ll>q;
	q.push(s);
	dis[s]=0;vis[s]=1;
	while(q.size()){
		ll u=q.front();
		q.pop();vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&dis[v]>dis[u]+c[i]){
				dis[v]=dis[u]+c[i];
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
ll ans=0;
ll dinic(ll u,ll flow){
	vis[u]=1;
	if(u==t)return flow;
	ll zy=0;
	for(ll i=head[u];i&&zy<=flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&dis[v]==dis[u]+c[i]&&(v==t||!vis[v])){
			ll jb=dinic(v,min(flow-zy,w[i]));
			w[i]-=jb;w[i^1]+=jb;
			zy+=jb;ans+=jb*c[i];
		}
	}
	vis[u]=0;
	return zy;
}
int main(){
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		cfsz[i]=a[i]-a[i-1];
		if(cfsz[i]>=0)add(s,i,cfsz[i],0);
		else add(i,t,-cfsz[i],0);
	}
	add(s,n+1,inf,0);//小细节，因为加有费用边时，可能会加出界（u==n+1），但很明显也可以转移 ，所以要加这条边 
	for(ll i=1;i<=m;i++){
		char fh;ll fw,cost;
		cin>>fh>>fw>>cost;
		for(ll i=1;i+fw-1<=n;i++){
			if(fh=='+'){
				add(i+fw,i,inf,cost);
			}else add(i,i+fw,inf,cost);
		}
	}
	//加费用边 
	while(spaf()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			maxflow+=dinic(s,inf);
		}
	}
	if(maxflow==realflow)cout<<ans;//记得判无解 
	else cout<<-1;
	return 0;
}

```
还有，这是萌新第一篇网络流题解，julao们点个赞吧，谢谢

---

## 作者：Basori_Tiara (赞：1)

还愿，两年半之后终于会了这个题。

区间加一减一使得区间有序看着就很差分，我们把他差分之后这个问题就变成了我们有若干种操作，第 $i$ 种操作可以拿出两个距离为 $x_i$ 的数，给其中一个 $+1$ 给另一个 $-1$。

然后这个过程可以抽象成网络流上流量的转移，相当于是在其中一个地方把一点流量输送到另外一个地方去了。

考虑我们的目标是让所有差分数组非负也就是说差分为负数的数都是需要他的绝对值这么多流量灌注他才行，而差分为正数的相当于就是有这么多流量要通过“操作”的桥梁去灌注差分为负数的点，而这也就是这个题中流量的意义。

然后这个题的建模就直接出来了，源点连差分为正的数，差分为负的数连汇点，流量为差分数组的绝对值，费用为 $0$，然后对于每个操作在满足这个操作限制的点对中连 $(\inf,c_i)$ 的边表示流量如果通过这个操作传输要从哪里到哪里，以及代价是多少。

对着这个跑费用流答案就出来了。

无解的判断就是看与汇点相连的边是否全部满流，如果是的话那就有解否则就无解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int diff[205];
class LTDZ{
	public:
	int dep[1000005];
	int E[1000005];
	int nxt[1000005];
	int head[1000005];
	int flow[1000005];
	bool in[1000005];
	int pos[1000005];
	int cost[1000005];
	int cnt=1;
	int s,t,n;
   void clear(){
      for(int i=2;i<=cnt;i++){
         E[i]=0,nxt[i]=0,flow[i]=0,cost[i]=0;
      }
      for(int i=1;i<=n;i++){
         head[i]=0;
      }
      cnt=1;
      s=t=n=0;
      anscost=ansflow=0;
      return;
   }
	void addedge(int u,int v,int fl,int co){
		cnt++;
		E[cnt]=v;
		flow[cnt]=fl;
		cost[cnt]=co;
		nxt[cnt]=head[u];
		head[u]=cnt;
		return;
	}
	void Add(int u,int v,int fl,int co){
		// printf("%lld %lld (%lld,%lld)\n",u,v,fl,co);
		addedge(u,v,fl,co);
		addedge(v,u,0,-co);
		return;
	}
	bool SPFA(){
		queue<int> q;
		q.push(s);
		for(int i=1;i<=n;i++){
			dep[i]=1e16;
		}
		dep[s]=0;
		in[s]=true;
		while(!q.empty()){
			int t=q.front();
			q.pop();
			in[t]=false;
			for(int i=head[t];i;i=nxt[i]){
				int v=E[i];
				int fl=flow[i];
				int co=cost[i];
				if(fl&&dep[t]+co<dep[v]){
					dep[v]=dep[t]+co;
					if(!in[v]){
						q.push(v);
						in[v]=true;
					}
				}
			}
		}
		return dep[t]<10000000000000000;
	}
	bool vis[1000005];
	int ansflow,anscost;
	int dfs(int cur,int mini,int Pre){
		vis[cur]=true;
		if(cur==t){
			ansflow+=mini;
			return mini;
		}
		int fl=0;
		for(int i=pos[cur];i;i=nxt[i]){
			pos[cur]=i;
			if(i==Pre)continue;
			int v=E[i];
			int F=flow[i];
			int C=cost[i];
			if(F&&dep[cur]+C==dep[v]&&(v==t||!vis[v])){
				int tmp=dfs(v,min(mini-fl,F),i^1);
				if(tmp){
					flow[i]-=tmp;
					flow[i^1]+=tmp;
					fl+=tmp;
					anscost+=tmp*C;
					if(fl==mini){
						break;
					}
				}
			}
		}
		vis[cur]=false;
		return fl;
	}
	void dinic(){
		while(SPFA()){
			do{
				for(int i=1;i<=n;i++){
					vis[i]=false;
					pos[i]=head[i];
				}
				dfs(s,1e16,0);
			}while(vis[t]);
		}
		return;
	}
}G;

signed main(){
   scanf("%lld%lld",&n,&m);
   for(int i=1;i<=n;i++){
      scanf("%lld",&diff[i]);
   }
   G.s=n+2;
   G.t=n+3;
   G.n=n+3;
   for(int i=n;i>=1;i--){
      diff[i]-=diff[i-1];
      if(diff[i]>0){
         G.Add(G.s,i,diff[i],0);
      }
      else{
         G.Add(i,G.t,-diff[i],0);
      }
   }
   G.Add(G.s,n+1,1e9,0);
   for(int i=1;i<=m;i++){
      char opt;
      int len,cost;
      cin>>opt;
      scanf("%lld%lld",&len,&cost);
      if(opt=='+'){
         for(int st=1;st+len<=n+1;st++){
            int ed=st+len;
            G.Add(ed,st,1e9,cost);
         }
      }
      else{
         for(int st=1;st+len<=n+1;st++){
            int ed=st+len;
            G.Add(st,ed,1e9,cost);
         }
      }
   }
   G.dinic();
   for(int i=G.head[G.t];i;i=G.nxt[i]){
      int v=G.E[i];
      int flow=G.flow[i^1];
      if(flow){
         puts("-1");
         return 0;
      }
   }
   printf("%lld\n",G.anscost);
   return 0;
}
/*

*/
```

---

## 作者：orz_z (赞：1)

有 $n$ 座山，每座山高度为 $h_i$。

有 $m$ 种操作，每一次操作可以把连续 $l_i$ 座山的高度抬高或压低 $1$，费用为 $c_i$。

问，让 $n$ 座山的高度不下降，最少需多少费用？

如果无解，输出 `-1`。

$1 \leq n,m\leq 200,1 \leq l_i\leq n,1 \leq h_i,c_i \leq 10^3$，时限 $1\text{s}$，空限 $128\text{MB}$。

#### std

「蜀道难，难于上青天」。

考虑到，当 $n$ 座山的高度不下降时，有：$\forall i \in(1,n],a_i \geq a_{i-1}$，即 $\forall i \in(1,n],a_i-a_{i-1} \geq 0$。

但是这里修改一个数的话，对它后面的数都有影响，不太好弄。

考虑差分维护，记 $d_i=a_i-a_{i-1}$，（这时点之间就互不影响了）。

每次对区间 $[l,r]$ 的操作即 $d_l+1,d_{r+1}-1$（加） 或 $d_l-1,d_{r+1}+1$（减）。

那么我们要让 $\forall i \in[1,n],d_i \geq 0$。

考虑到，我们不会让某一座山先抬高再压低或先压低抬高再抬高。

那么对于 $d_i > 0$，最多被减 $d_i$ 次，即最多为其他点提供 $d_i$ 次加；$d_i <0$，至少需要被加 $d_i$ 次。

总结一下，模型如下：

* 如果 $d_i >0$，连一条从 $s$ 到 $i$，容量为 $d_i$，费用为 $0$ 的边（表示这个点有 $d_i$ 次给其他点加的机会）。
* 如果 $d_i \leq 0$，连一条从 $i$ 到 $t$，容量为 $-d_i$，费用为 $0$ 的边（表示这个点需要被加 $d_i$ 次）。
* 对于区间 $[l,r]$ 的加法操作，连一条从 $r+1$ 到 $l$，容量为 $inf$，费用为 $c_i$ 的边（表示加机会的转移）。
* 对于区间 $[l,r]$ 的减法操作，连一条从 $l$ 到 $r+1$，容量为 $inf$，费用为 $c_i$ 的边（表示加机会的转移）。

最后就是跑最小费用最大流了。

记最大流为 $g$，则无解的情况即为 $g < \sum\limits_{i=1}^{n}[d_i<0]-d_i$。

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

typedef int tp;

const int _ = 6e5 + 10, inf = 947483647;

int n, m, a[_], b[_], s, t, lv[_], cur[_];

tp maxflow, mincost;

int tot = 1, head[_], to[_ << 1], nxt[_ << 1];

tp dis[_], w[_ << 1], fl[_ << 1];

int mc[2][_];

inline void add(int u, int v, tp dis, tp c)
{
	to[++tot] = v;
	nxt[tot] = head[u];
	fl[tot] = dis;
	w[tot] = c;
	head[u] = tot;
}

inline void Add(int u, int v, tp dis, tp c)
{
	add(u, v, dis, c);
	add(v, u, 0, -c);
}

inline bool bfs()
{
	memset(lv, 0, sizeof(lv));
	for (int i = 0; i < _; ++i)
		dis[i] = inf;
	lv[s] = 1;
	dis[s] = 0;
	memcpy(cur, head, sizeof(head));
	queue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int p = q.front();
		q.pop();
		lv[p] = 0;
		for (int eg = head[p]; eg; eg = nxt[eg])
		{
			int v = to[eg];
			tp vol = fl[eg];
			if (vol > 0 && dis[v] > dis[p] + w[eg])
			{
				dis[v] = dis[p] + w[eg];
				if (!lv[v])
				{
					q.push(v);
					lv[v] = 1;
				}
			}
		}
	}
	return dis[t] != inf;
}

tp dfs(int p = s, tp flow = inf)
{
	if (p == t)
		return flow;
	lv[p] = 1;
	tp rmn = flow;
	for (int eg = cur[p]; eg && rmn; eg = nxt[eg])
	{
		cur[p] = eg;
		int v = to[eg];
		tp vol = fl[eg];
		if (vol > 0 && !lv[v] && dis[v] == dis[p] + w[eg])
		{
			tp c = dfs(v, min(vol, rmn));
			rmn -= c;
			fl[eg] -= c;
			fl[eg ^ 1] += c;
		}
	}
	lv[p] = 0;
	return flow - rmn;
}

inline void dinic()
{
	while (bfs())
	{
		tp flow = dfs();
		maxflow += flow;
		mincost += dis[t] * flow;
	}
}

int d1[_], d2[_];

signed main()
{
	char op;
	int x, y, sum = 0;
	n = read(), m = read();
	s = 0, t = _ - 1;
	for (int i = 1; i <= n; ++i)
	{
		b[i] = read();
		a[i] = b[i] - b[i - 1];
	}
	for (int i = 0; i <= n + 1; ++i)
		d1[i] = d2[i] = inf;
	for (int i = 1; i <= m; ++i)
	{
		cin >> op;
		x = read(), y = read();
		if (op == '+')
			d1[x] = min(d1[x], y);
		else
			d2[x] = min(d2[x], y);
	}
	Add(s, n + 1, inf, 0);
	for (int i = 1; i <= n; ++i)
		if (a[i] > 0)
			Add(s, i, a[i], 0);
		else
		{
			Add(i, t, -a[i], 0);
			sum -= a[i];
		}
	for (int i = 1; i <= n; ++i)
		for (int l = 1, r = l + i; r <= n + 1; ++l, r = l + i)
		{
			if (d1[i] < inf)
				Add(r, l, inf, d1[i]);
			if (d2[i] < inf)
				Add(l, r, inf, d2[i]);
		}
	dinic();
	if(maxflow < sum)
	{
		puts("-1");
		return 0;
	}
	write(mincost), putchar('\n');
	return 0;
}
```



---

## 作者：lalaouye (赞：0)

感觉每一步都挺自然的。

首先连续加减让我们不难想到差分，每次给 $d_i$ 加一或减一，每次给 $d_{i+l}$ 减一或加一。

然后要求单调不降就是要求每个 $d_i$ 大于等于 $0$。

然后注意到我们每次操作相当于是 $i$ 向 $i+l$ 贡献 $1$ 或者 $i+l$ 向 $i$ 贡献 $1$，结合数据范围让我们想到网络流。

具体的，我们可以从起点给每个 $i$ 连一条流量为 $V+d_i$，然后每个 $i$ 向终点连一条流量为 $V$ 的边，就能让每个 $d_i$ 尽可能大于等于 $0$ 了，然后刚刚的贡献转移我们在网络上直接连边即可，再将费用变成代价 $c$，就可以跑费用流啦！

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define inf 1000000000
#define id(x, y) m * (x - 1) + y
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 1e6 + 5, M = 105, P = 998244353;
constexpr double PI = acos (-1.0);
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int n, m, k, s, t;
vector <int> vec;
int tot, cnt = 1;
int h[N], to[N], cap[N], nxt[N], cost[N];
int a[N];
void add (int u, int v, int w, int c) {
  to[++ cnt] = v;
  cap[cnt] = w;
  cost[cnt] = c;
  nxt[cnt] = h[u];
  h[u] = cnt;
  to[++ cnt] = u;
  cap[cnt] = 0;
  nxt[cnt] = h[v];
  cost[cnt] = - c;
  h[v] = cnt;
}
int incf[N], dis[N], pre[N];
bool vis[N];
queue <int> q;
int spfa () {
  q.push (s);
  rep (i, s, t) incf[i] = 0, dis[i] = inf;
  dis[s] = 0, incf[s] = inf;
  while (! q.empty ()) {
    int u = q.front ();
    q.pop ();
    for (int i = h[u]; i; i = nxt[i]) {
      int v = to[i], w = cap[i], c = cost[i];
      if (! w) continue;
      if (dis[u] + c < dis[v]) {
        dis[v] = dis[u] + c;
        pre[v] = i;
        incf[v] = min (w, incf[u]);
        q.push (v);
      }
    }
  }
  return incf[t];
}
int MCMF () {
  int mincost = 0, maxflow = 0;
  while (spfa ()) {
    maxflow += incf[t];
    mincost += incf[t] * dis[t];
    int u = t;
    while (u != s) {
      int i = pre[u];
      cap[i] -= incf[t];
      cap[i ^ 1] += incf[t];
      u = to[i ^ 1];
    }
  }
  if (maxflow != (n + 1) * 1000) return -1;//一定要记得判无解
  return mincost;
}
int main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  cin >> n >> m;
  rep (i, 1, n) cin >> a[i];
  rrp (i, 2, n) a[i] -= a[i - 1];
  t = n + 2;
  a[n + 1] = 1000000;
  rep (i, 1, n + 1) add (s, i, a[i] + 1000, 0), add (i, t, 1000, 0);
  rep (i, 1, m) {
    char ch;
    int l, c;
    cin >> ch >> l >> c;
    rep (j, 1, n - l + 1) {
      if (ch == '+') add (j + l, j, inf, c);
      else add (j, j + l, inf, c);
    }
  }
  
  cout << MCMF ();
}
```

---

## 作者：win114514 (赞：0)

### 思路

考虑费用流。

发现区间操作与单调不降。

考虑差分。

令 $a_i=h_i-h_{i-1}$。

那么我们需要让所有的 $a_i$ 全部都变为自然数。

考虑一次区间操作的影响。

对于 $(+,l,r)$，我们会让 $a_l$ 加一，$a_{r+1}$ 减一。

对于 $(-,l,r)$，我们会让 $a_l$ 减一，$a_{r+1}$ 加一。

那么我们可以建出以下费用流模型。

对于 $a_i>0$，连 $(s,i,a_i,0)$，表示可以减 $a_i$ 次。

对于 $a_i<0$，连 $(i,t,-a_i,0)$，表示必须加 $-a_i$ 次。

可以连 $(s,n+1,inf,0)$ 补充流量。

对于 $(+,l,c)$，每一个点连 $(i,i-l,inf,c)$。

对于 $(-,l,c)$，每一个点连 $(i,i+l,inf,c)$。

然后跑费用流即可。

当然，值得一提的是，**注：所有时候山的高度都不能为负**，所以 $h_0=0$。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/03 14:23:49
*/
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

struct NetWork {
  using i64 = long long;
  struct edge { int to, nxt; i64 v, c; };
  int ct, n, s, t; i64 mf, mc;
  vector<int> dp, cr, hd, vs;
  vector<i64> ds;
  vector<edge> e;
  inline NetWork(int N) {
    vs.resize(N + 5), n = N, ct = 1;
    dp.resize(N + 5), ds.resize(N + 5);
    cr.resize(N + 5), hd.resize(N + 5);
    e.push_back({}), e.push_back({});
  }
  inline void add(int x, int y, int z, int u) {
    e.push_back({y, hd[x], z, u}), hd[x] = ++ct;
    e.push_back({x, hd[y], 0,-u}), hd[y] = ++ct;
  }
  inline bool bfs() {
    queue<int> q;
    fro(i, 1, n) dp[i] = 0, ds[i] = 1e18, cr[i] = hd[i];
    q.push(s), ds[s] = 0;
    while (q.empty() == 0) {
      int x = q.front(); q.pop(), vs[x] = 0;
      for (int i = hd[x]; i; i = e[i].nxt) {
        if (e[i].v == 0) continue;
        if (ds[e[i].to] > ds[x] + e[i].c) {
          ds[e[i].to] = ds[x] + e[i].c;
          dp[e[i].to] = dp[x] + 1;
          if (!vs[e[i].to]) q.push(e[i].to), vs[e[i].to] = 1;
        }
      }
    }
    return ds[t] != 1e18;
  }
  inline i64 dfs(int now, i64 flow) {
    if (now == t) return mf += flow, flow;
    i64 used = 0;
    for (int&i = cr[now]; i; i = e[i].nxt) {
      if (ds[now] + e[i].c == ds[e[i].to] && dp[now] + 1 == dp[e[i].to] && e[i].v) {
        int x = dfs(e[i].to, min(e[i].v, flow - used));
        e[i].v -= x, e[i ^ 1].v += x, used += x, mc += x * e[i].c;
        if (used == flow) return used;
      }
    }
    return used;
  }
  inline pair<i64, i64> zkw(int S, int T) {
    s = S, t = T, mf = mc = 0;
    while (bfs()) while (dfs(s, 1e18));
    return {mf, mc};
  }
};

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> h(n + 1);
  NetWork sol(n + 3);
  int s = n + 2, t = n + 3;
  fro(i, 1, n) {
    cin >> h[i];
  }
  fro(i, 1, m) {
    char w; int l, c;
    cin >> w >> l >> c;
    if (w == '+') fro(i, 1 + l, n + 1) sol.add(i, i - l, 1e9, c);
    if (w == '-') fro(i, 1 + 0, n - l) sol.add(i, i + l, 1e9, c);
  }
  sol.add(s, n + 1, 1e9, 0);
  pre(i, n, 1) {
    h[i] = h[i] - h[i - 1];
    if (h[i] > 0) sol.add(s, i, h[i], 0);
    if (h[i] < 0) sol.add(i, t,-h[i], 0);
  }
  auto ans = sol.zkw(s, t);
  fro(i, 2, n) if (h[i] < 0) ans.first += h[i];
  cout << (ans.first == 0 ? ans.second : -1) << "\n";
  return 0;
}
```

---

## 作者：Drind (赞：0)

## 题目解析

题目给定 $m$ 个操作，每个操作可以选定长度为 $l_i$ 的区间消耗 $c_i$ 费用把区间加或减去 1（单个操作只能进行加或减）。求使得整个序列变得不减所花费最小费用。

首先我们考虑差分，现在我们的目标变成让差分数组变成全部变成非负的。

我们在看操作，变成了从差分数组上一个点上取 1 的值给到差分数组另一个点上。那么我们就想到了费用流模型。

我们设流量为差分数组的值，那么我们从源点向序列里每个正的点连一条流量为他的权值的边，意味着它拥有这么多流量可以分给别人，同理每个负的点向汇点连流量为他的相反数的边，意味着它需要这么多流量保证序列不减。

对于每个长度为 $l_i$ 的区间，我们暴力给他的 $n-l_i$ 种可能全部连上边，流量为无限大，费用为 $c_i$。

对于差分数组的第一个数，因为序列里的数不能小于 0，所以处理方法和其他一样。

对于差分数组里的最后一个数，他想取啥值都可以，所以从源点向他连一条流量为无穷大的边。

去掉费用流板子后代码如下：

```cpp
int E[2][N];
int a[N],del[N];

inline void fake_main(){
	memset(head,-1,sizeof head); mncos=0;
	int n,m; cin>>n>>m; int tot=0;
	for(int i=1;i<=n;i++) cin>>a[i]; a[n+1]=0;
	for(int i=1;i<=n;i++) del[i]=a[i]-a[i-1];
	
	s=n+2,t=s+1;
	adde(s,n+1,inf,0);
	for(int i=1;i<=n;i++){
		if(del[i]>0) adde(s,i,del[i],0);
		else{
			adde(i,t,-del[i],0); tot-=del[i]; 
		}
	}
	
	memset(E,0x3f,sizeof E);
	for(int i=1;i<=m;i++){
		char ch; int l,c; cin>>ch>>l>>c;
		if(ch=='+') ch=1; else ch=0;
		E[ch][l]=min(E[ch][l],c);
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j+i<=n+1;j++){
			if(E[0][i]!=inf) adde(j,j+i,inf,E[0][i]);
			if(E[1][i]!=inf) adde(j+i,j,inf,E[1][i]);
		}
	}
	
	int tmp=mcmf();
	if(tmp>=tot) cout<<mncos<<"\n";
	else cout<<"-1\n";
}
```

---

