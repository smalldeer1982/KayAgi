# [ONTAK2015] Bajtman i Okrągły Robin

## 题目背景

**警告：滥用本题评测将被封号！**

## 题目描述

有 $n$ 个强盗，其中第 $i$ 个强盗会在 $[a_i, a_i + 1], [a_i + 1, a_i + 2], \cdots, [b_i - 1, b_i]$ 这么多段长度为 $1$ 的时间中选出一个时间进行抢劫，并计划抢走 $c_i$ 元。作为保安，你在每一段长度为 $1$ 的时间内最多只能制止一个强盗，那么你最多可以挽回多少损失呢？

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^3$，$1 \leq a_i < b_i \leq 5 \times 10^3$，$1 \leq c_i \leq 10^4$。

## 样例 #1

### 输入

```
4
1 4 40
2 4 10
2 3 30
1 3 20```

### 输出

```
90```

# 题解

## 作者：Dream__Sky (赞：10)

### 前置知识：
带权二分图最大匹配，链式前向星，不会的请自行百度。



------------


这道题难度虚高，其实就是带权二分图最大匹配模版。

因为警卫在一个时间段只能拦截一个人，这就相当于二分图左右两个点集每个点的度最大为 $1$，因此我们可以用最大匹配来做，不需要线段树等高级算法。

我们可以把一个点集看成每个小偷，另一个点集看做每一个时间段，在套上带权二分图最大匹配模版。为了让挽回的钱越多越好，我们可以用贪心的思想，先对每个小偷按照偷的钱（边权）排序，优先满足那些偷得最多的人，这样就能满足挽回的钱越多越好。

在每次二分匹配的过程中，我们可以加一个优化，每次搜索不必从头开始，可以从上一次搜到的点开始，这样可以节约时间，~~甚至能抢到最优解~~。

思路其实很简单，代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=2e7+5e6+10,N=5e3+10;
int n;
int h[M],nt[M],w[M],g[M],id=1;
struct ll{
	int x;
	int y;
	int z;
}a[N];
pair<int,int> match[N];
int st[N];
int ans;
inline void add(int a,int b,int c){
	g[id]=b;
	w[id]=c;
	nt[id]=h[a];
	h[a]=id++;
}//链式前向星建边
int s[N];
inline bool dfs(int num,int c){
	for(register int i=s[num];~i;i=nt[i]){
		int j=g[i];
		if(!st[j]){
			st[j]=1;
			if(!match[j].first||dfs(match[j].first,match[j].second)){
				match[j]={num,c};
				s[num]=i;
				return 1;
			}
		}
	}
	return 0;
}//带权二分图最大匹配,不会的请自行学习，这里不过多解释
int mi,mx;
inline int cmp(ll a,ll b){
	return a.z>b.z;
}
inline int read() {
	register int x=0;
	register char ch=getchar();
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	return x;
}
signed main()
{
	cin>>n;
	memset(h,-1,sizeof h);	
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
	}
	sort(a+1,a+n+1,cmp);//利用了贪心的思想，排序
	for(register int i=1;i<=n;i++){
		for(register int j=a[i].x;j<a[i].y;j++){
			add(i,j,a[i].z);//建边
		}
	}
	for(register int i=1;i<=n;i++){
		s[i]=h[i];//优化
	}
	for(register int i=1;i<=n;i++){
		memset(st,0,sizeof st);
		dfs(i,a[i].z);//对每个点进行匹配
	}
	for(register int i=1;i<=n;i++){
		ans+=match[i].second;//加上选上的边权
	}
	cout<<ans;
	return 0;
}
```
这里要感谢 @[yushucheng123](https://www.luogu.com.cn/user/728522) 大佬提供的思路。

---

## 作者：DarkClever (赞：7)

题意很清楚了 ( •̀ ω •́ )✧，但是有一点需要注意，这里的强盗活动的是时间段而非时间点。

容易发现，有每个时间段只能拦截一个强盗的限制，所以我们为了尽可能的拦截强盗，我们应该让强盗尽可能的在不同的时间段出现，因为如果多个强盗在同一个时间段出现，保安就只能拦截一个强盗了 `(*>﹏<*)′。

强盗应该尽可能的在不同时间段出现，并且每个强盗都有抢走的钱数 $c_i$，不难想到二分图最大权匹配，这时，在匈牙利算法和费用流中，我们肯定会选择时间上更加优秀的后者 o((>ω< ))o。

进行网络流建图时，我们可以使用较为经典的方法。即从原点向每个强盗连一条流量为 $1$，费用为 $0$ 的边，强盗向他回去抢劫的时间段连一条流量为 $1$，费用为 $c_i$ 的边，每个时间段向汇点连一条流量为 $1$，费用为 $0$ 的边，然后跑一遍最大费用最大流即可( •̀ ω •́ )✧。

然鹅 Σ(っ °Д °;)っ，这种方法会连出 $n\times m$ 条边（此处的 $m$ 表示 $a_i,b_i$ 的值域），显然是时间空间双开花的（＞人＜；），考虑优化建图。

注意到我们是进行区间连边，而我们恰好有一个处理区间问题的好手，线段树╰(*°▽°*)╯！

首先，介是刚刚那幅图的右半部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/quxp2u39.png)

我们将要对那排代表时间段的点点建一颗线段树。

那怎么建呢？我们可以考虑以这几个节点为叶子节点，建一颗线段树，其中，每个父节点会向子节点连一条流量为 $+\infty$，费用为 $0$ 的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/cut2l75r.png)

然后，我们就建好了一颗线段树╰(*°▽°*)╯，如图，绿色的为代表单个时间段的叶子节点，红色的为线段树上其他的点。

那么，假设我们此时有一个强盗连向时间段 $[1,4]$ 的话，我们就要这样连，就跟线段树上的操作一样，就可以啦。

![](https://cdn.luogu.com.cn/upload/image_hosting/ovosm9bp.png)

这样，每个强盗最多会多出 $O(\log m)$ 条边，然后，我们会发现自己的程序跑的飞起，就能愉快的 A 了这道题 ( •̀ ω •́ )！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 320000;
const int M = 320000;
const int INF = 0x3f3f3f3f;

int n,m,ds,s,t;
struct wll{//网络流模板
    int tot = 1, lnk[N], cur[N], ter[M], nxt[M], cap[M];
	int dis[N];
    int cost[M], ret; 
    bool vis[N];

    void add(int u, int v, int w, int c) { 
        ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
    }

    void addedge(int u, int v, int w, int c) { 
		// cerr<<u<<" "<<v<<" "<<"“"<<to_string(w)+"-"+to_string(c)<<"”"<<endl;
        add(u, v, w, c), add(v, u, 0, -c);
    }

    bool spfa(int s, int t) {
        memset(dis, 0x3f, sizeof(dis));
        memcpy(cur, lnk, sizeof(lnk));
        std::queue<int> q;
        q.push(s), dis[s] = 0, vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop(), vis[u] = false;
            for (int i = lnk[u]; i; i = nxt[i]) {
                int v = ter[i];
                if (cap[i] && dis[v] > dis[u] + cost[i]) { 
                    dis[v] = dis[u] + cost[i];
                    if (!vis[v]) q.push(v), vis[v] = true;
                }
            }
        }
        return dis[t] != INF;
    }

    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        vis[u] = true;
        int ans = 0;
        for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
            int v = ter[i];
            if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
                int x = dfs(v, t, std::min(cap[i], flow - ans));
                if (x) {
                    ret += (int)x * cost[i];
                    cap[i] -= x, cap[i ^ 1] += x, ans += x;
                }
            }
        }
        vis[u] = false;
        return ans;
    }

    int mcmf(int s, int t) {
        int ans = 0;
        while (spfa(s, t)) {
            int x;
            while ((x = dfs(s, t, INF))) ans += x;
        }
        return ans;
    }
} dc;
struct xds{
	struct node{
		int l,r;
		int lson,rson;
	}a[N*4];
	int build(int l,int r){//如同线段树的建树过程
		if(l == r){//如果 l = r 时，是叶子节点，此时这个点可以直接返回原来时间段所对应的点，不需要建更多的点
			a[l].l = l,a[l].r = r;
			return l;
		}
		int wAi = ++ds;//新增一个点
		int mid = (l+r)/2;
		a[wAi].l = l,a[wAi].r = r;
		a[wAi].lson = build(l,mid),a[wAi].rson = build(mid+1,r);
		dc.addedge(wAi,a[wAi].lson,INF,0);
		dc.addedge(wAi,a[wAi].rson,INF,0);
		return wAi;
	}
	inline void addfrom(int u,int v,ll w,int l,int r){
		if(l<=a[v].l && a[v].r<=r){//如果在区间内，直接挂到节点上
			dc.addedge(u,v,1,-w);//由于直接套的模板，懒得写最大费用，所以可以取负数
			return;
		}else if(l>a[v].r || r<a[v].l){
			return;
		}else{
			addfrom(u,a[v].lson,w,l,r);
			addfrom(u,a[v].rson,w,l,r);
			return;
		}
	}
}out;

int rt_out;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	int tims = 5001;//时间段的个数（这里直接设置到O(max(bi))）
	s = tims+1;//源点
	t = tims+2;//汇点
	ds = tims+2;//当前点的数量（方便建树）
	for(int i=1;i<=tims;i++){
		dc.addedge(i,t,1,0);
	}
	rt_out = out.build(1,n);
	for(int i=1;i<=n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		ds++;
		dc.addedge(s,ds,1,0);
		out.addfrom(ds,rt_out,c,a,b-1);//因为是时间段，所以要 -1
	}
	dc.mcmf(s,t);
	cout<<-dc.ret<<endl;//如果写的最小费用，记得取反:)
	return 0;
}
```

---

## 作者：mqmhaaaa1 (赞：2)

一道没什么太大难度的建模题，不过对于线段树优化建图不熟悉的可能会一开始想不到。

# 题面解释

意思是你可以任意安排小偷在 ta 出现时间范围中的任意时间段出现（黑社会警察），每个时间段最多只能拦住一个小偷，第 $i$ 个小偷拦截后可以保住 $c_i$ 的钱，问你最多保住多少钱。（神经）

# part1 暴力建图

相信学过网络流的都看得出来，我们可以把每个小偷看成一个流量，也就是源点 $s$ 向 ta 连 $1$ 容量的边，每个时间段向汇点 $t$ 连容量为 $1$ 的边，每个小偷在向他出现时间段内的所有时间段连边。

我们再把 $s$ 到小偷 $i$ 的边费用设为 $c_i$，这样的话，流量能流到 $t$ 的小偷就相当于自投罗网，被捕获，获得 $c_i$ 的费用，流不到 $t$ 就是漏网之鱼，不管了（根据流量守恒定律，跑不到 $t$ 会自己回来）。跑个最大费用最大流就行了。

以上暴力建图太过简单，不解释。但这么建图有一个问题，边数是 $n^2$ 的，就算在二分图上 dinic $O( \sqrt{n}m)$ 的复杂度下也会爆。那有什么方法减少连边数呢？

# part2 线段树优化

线段树优化建图基本上是在处理所有对连续区间建边的通法，本题也一样。

回到对出现时间区间建图这一步，我们先将整个时间段序列（$1 \sim 5000$），处理成一颗线段树，线段树叶子结点向 $t$ 连容量为 $1$ 的边，父亲节点向儿子节点连容量为 $inf$ 的边。

在向区间建边时，我们就像在普通线段树上查找区间一样，向满足 $ql \le l \land r \le qr$（$ql,qr$ 为查找区间，$l,r$ 为当前节点代表的区间）的节点连边。

我们都知道，线段树查找区间过程中至多查到 $\log n$ 级别的节点数，也就是说原本 $n^2$ 级别的边数缩减为 $n \log n$，可以通过本题。

下面给不熟悉线段树优化建图的 oier 解释下。我们向一个节点建边后，这个节点的流量可以顺着这个节点往下，一直到叶子节点，可以想象成一个线段树 pushdown 的过程，把流量传下去。到叶子节点后，因为每个叶子向 $t$ 连 $1$ 容量的边，代表每个叶子所代表的时间段可以抓一个小偷。在这颗线段树上跑最大流的过程就相当于从上面到叶子节点的流量不停地找没满流的叶子结点到 $t$ 的边，这样既保证本来只能在区间内的流量不跑出去，也保证了边数缩减为 $n \log n$ 级别。

细节：这里我们用的是**时间段**，并非**时间点**，所以我们可以把所有小偷出现时间点区间的 $r$ 减去 $1$ 来代表时间段。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define i8 __int128
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
inline ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=5e4+10,M=2e6+10,inf=0x3f3f3f3f,fz=2e4+10;
ll to[M<<1],nxt[M<<1],w[M<<1],c[M<<1],bh[N],tot=1;
ll head[N],dis[N];
bool vis[N];
inline void add(ll u,ll v,ll flow,ll cost){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=flow;
	c[tot]=cost;
	bh[u]=tot;

	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	c[tot]=-cost;
	bh[v]=tot;
}
ll s,t;
inline bool spaf(){
	for(ll i=0;i<=t;i++){
		vis[i]=0;head[i]=bh[i];
		dis[i]=inf;
	}
	queue<ll>q;
	vis[s]=1;dis[s]=0;
	q.push(s);
	while(q.size()){
		ll u=q.front();q.pop();
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&dis[u]+c[i]<dis[v]){
				dis[v]=dis[u]+c[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[t]!=inf;
}
ll ans,mxf;
ll dic(ll u,ll flow){
	vis[u]=1;
	if(u==t){
		mxf+=flow;
		return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&(!vis[v]||v==t)&&dis[v]==dis[u]+c[i]){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb;w[i^1]+=jb;
			zy+=jb;flow-=jb;
			ans+=jb*c[i];
			if(!flow)break;
		}
	}
	vis[u]=0;
	return zy;
}//普通dinic 
ll n;
struct segatree{
	#define ls(u) (u<<1)
	#define rs(u) (u<<1|1)
	void build(ll u,ll l,ll r){
		if(l==r){
			add(u,t,1,0);
			return;
		}
		ll mid=(l+r)>>1;
		add(u,ls(u),inf,0),add(u,rs(u),inf,0);
		build(ls(u),l,mid);build(rs(u),mid+1,r);
	}
	void find(ll u,ll l,ll r,ll ql,ll qr,ll id){
		if(ql<=l&&r<=qr){
			add(fz+id,u,1,0);return;
		}
		ll mid=(l+r)>>1;
		if(ql<=mid)find(ls(u),l,mid,ql,qr,id);
		if(qr>mid)find(rs(u),mid+1,r,ql,qr,id);
	}
}jb;//普通segatree 
int main(){
	n=read();
	s=0;t=fz+n+1;
	jb.build(1,1,4999);//r-1
	for(ll i=1;i<=n;i++){
		ll l=read(),r=read(),val=read();
		add(s,i+fz,1,-val);//最大费用最大流取反 
		jb.find(1,1,4999,l,r-1,i);//r-1
	}
	while(spaf()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inf);
		}
	}
	cout<<-ans;//取反 
}
```


代码

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

有 $n$ 个区间，每个区间带权,在每个单位段时间可以得到一个覆盖其的区间的权值，但每个区间只能被选择一次，求获得最大权值。

## 题目分析

显然，把区间和时间段当成点，然后由区间向其包含的时间段连边，这就成了二分图最大带权匹配的裸题。但边数高达 $O(n^2)$，无法接受。注意到每次连边都是时间段的一段连续区间，可以用线段树优化建边，边数复杂度降为 $O(n\log n)$。跑费用流即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L (x<<1)
#define R (x<<1|1)
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =6e4+5,M=1e7+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7,bas=131;
const ui base=13331;
const double eps=1e-9;
using namespace std;
int m,n,cst,s,t,h[N],nxt[M],to[M],d[N],cnt=1,pre[N],c[M],w[M],dis[N],ans;
bool vis[N];
inline void add(int a,int b,int C,int cost){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=C,c[cnt]=cost;
	to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt,w[cnt]=0,c[cnt]=-cost;
}
inline bool spfa(){
	for(int i=0;i<=t;i++)dis[i]=1000000000,vis[i]=0;
	dis[t]=0,vis[t]=1;
	deque<int>q;
	q.push_back(t);
	while(!q.empty()){
		int x=q.front();q.pop_front();
		for(int i=h[x];i;i=nxt[i]){
			int y=to[i];
			if(w[i^1]&&dis[y]>dis[x]-c[i]){
				dis[y]=dis[x]-c[i];
				if(!vis[y]){
					vis[y]=1;
					if(!q.empty()&&dis[y]<dis[q.front()])q.push_front(y);else q.push_back(y);
				}
			}
		}
		vis[x]=0;
	}
	return dis[s]^1000000000;
}
inline int dfs(int x,int lim){
	vis[x]=1;
	if(x==t)return lim;
	int k,tmp=0;
	for(int i=h[x];i;i=nxt[i]){
		int y=to[i];
		if(!vis[y]&&w[i]&&dis[x]-c[i]==dis[y]){
			k=dfs(y,min(w[i],lim-tmp));
			if(k)cst+=k*c[i],w[i]-=k,w[i^1]+=k,tmp+=k;
			if(tmp==lim)break;
		}
	}
	return tmp;
}
inline void build(int x,int l,int r){
	if(l==r)return add(x,t,1,0),void();
	build(lc),build(rc),add(x,L,inf,0),add(x,R,inf,0);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int fr){
	if(OK)return add(fr,x,1,0),void();
	if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr,fr);
	if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr,fr);
}
int tot,sum;
int main(){
	n=read(),s=0,t=25000+1,tot=20000;
	for(int i=1,l,r,k;i<=n;i++)l=read(),r=read()-1,k=read(),tot++,modify(1,1,5000,l,r,tot),add(s,tot,1,-k);
	build(1,1,5000);
	while(spfa())ans+=dfs(s,inf);
	pf(-cst);
	return 0;
}
```


---

## 作者：南阳刘子骥 (赞：2)

我们考虑这样想：

假如商店每个长度为 1 的时间段内只能够被抢劫一次，那么你就只需要站在商店门口盯着就可以了，而把问题抛给了强盗们去解决了——而强盗们的问题是，如何规划抢劫时间才能使被抢劫的财物价值总和最大。

对于这样的问题，我们可以想到带权二分图最大匹配，然后就转化成为了最大费用最大流问题。

我们将每一个强盗和每一个长度为 1 的时间段都设为一个点，然后让每一个强盗向其可以抢劫的时间段区间内的每一个时间段连一条容量为 1、费用为 $c_i$ 的边。
然后每一个强盗向源点连边，每一个时间段向汇点连边，这两次连边都是容量为 1、费用为 0。

然后我们会发现，这样连边的话边的数量是 $O(n^2)$ 级别的，无法达到我们的要求。

于是我们就引入了线段树优化建图这样一种节约边数的方式，使得边的数量减小为 $O(\log{n})$ 级别的。

线段树优化建图的大意就是将线段树的区间作为一个中转点，由其向其子节点连边，而不是直接连边。

我们建立线段树的时候，与正常情况下建立线段树的方式是一样的，只不过这里不需要维护任何信息，只需要将每一个叶子节点连向汇点，同时将一个节点与其左右子节点（如果有的话）连边即可。

这道题里因为每一个时间段只能够被抢劫一次（上面说了），所以代表其的点向汇点连的边容量为 1、费用为 0。

但是线段树中父亲节点向子节点连的边的容量就不能是 1 了，必须是 $+\infty$ 才能保证其覆盖的区间都可以被抢劫。

这里写的时候不是特别放心，在结构体里面存了一个节点编号，其实在线段树节点有序的情况下不需要存。

``` cpp
void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].id = ++cnt;
	if(l == r)
	{
		add(tr[p].id, T, 1, 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	add(tr[p].id, tr[p << 1].id, INF, 0);
	add(tr[p].id, tr[p << 1 | 1].id, INF, 0);
	return;
}
```

然后就是区间连边。

我们其实只需要向线段树区间加那样，向每一个最长的完全被覆盖的区间连一条容量为 1、费用为 $c_i$ 的边即可。

``` cpp
void seglnk(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		add(k + 1, tr[p].id, 1, -c[k]);
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)seglnk(p << 1, l, r, k);
	if(r > mid)seglnk(p << 1 | 1, l, r, k);
	return;
}
```

最后注意一个小细节：线段树内的叶子结点代表的区间是 $[a,a]$，而这里要求的最小区间是 $[a,a+1]$，所以我们可以将右端点自减一来替代一下。

最后放总的代码：

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2000010, M = 2000010, INF = 1e8;
int n, m, S, T;
int a[N], b[N], c[N];
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

struct SegTree
{
	int l, r;
	int id;
}tr[N << 3];
int cnt;

void build(int p, int l, int r)
{
	tr[p].l = l, tr[p].r = r;
	tr[p].id = ++cnt;
	if(l == r)
	{
		add(tr[p].id, T, 1, 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	add(tr[p].id, tr[p << 1].id, INF, 0);
	add(tr[p].id, tr[p << 1 | 1].id, INF, 0);
	return;
}
void seglnk(int p, int l, int r, int k)
{
	if(tr[p].l >= l && tr[p].r <= r)
	{
		add(k + 1, tr[p].id, 1, -c[k]);
		return;
	}
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid)seglnk(p << 1, l, r, k);
	if(r > mid)seglnk(p << 1 | 1, l, r, k);
	return;
}

bool spfa()
{
	int hh = 0, tt = 1;
	memset(d, 0x3f, sizeof(d));
	memset(incf, 0, sizeof(incf));
	q[0] = S, d[S] = 0, incf[S] = INF;
	while(hh != tt)
	{
		int t = q[hh++];
		if(hh == N) hh = 0;
		st[t] = false;

		for(int i = h[t]; ~i; i = ne[i])
		{
			int ver = e[i];
			if(f[i] && d[ver] > d[t] + w[i])
			{
				d[ver] = d[t] + w[i];
				pre[ver] = i;
				incf[ver] = min(f[i], incf[t]);
				if(!st[ver])
				{
					q[tt++] = ver;
					if(tt == N) tt = 0;
					st[ver] = true;
				}
			}
		}
	}

	return incf[T] > 0;
}

void EK(int &flow, int &cost)
{
	flow = cost = 0;
	while(spfa())
	{
		int t = incf[T];
		flow += t, cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	S = 0, T = 1;
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		add(S, i + 1, 1, 0);
		maxn = max(maxn, b[i]);
	}
	cnt = n + 1;
	build(1, 1, maxn + 1);
	for(int i = 1; i <= n; i++)
		seglnk(1, a[i], b[i] - 1, i);
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", -cost);
	return 0;
}
```

感谢阅读~qwq



---

## 作者：jockbutt (赞：2)

## 前言

这道题非常卡常，注意优化常数！

## 解法

第一眼看上去，感觉有点数据结构，当然，正解其中也有数据结构——费用流和线段树优化建图。

### 朴素の建图

引入超级源和超级汇，每个时间点都向源点连一条流量为 $ 1 $，费用为 $  0 $ 的边，每个强盗也向汇点连一条流量为 $ 1 $，费用为 $0$ 的边。最后再将时间段和第 $ i $ 个强盗之间连接一条流量为 $ 1 $,费用为 $ c_i $ 的边，跑一遍最大费用最大流。

### 线段树の优化

上面建图的方式会有 $ n^2 $ 条边，跑网络流直接起飞，于是我们必须想一些办法来减少边数。

建一棵线段树来维护每个时间点，变成若干个时间段，再和强盗们连边，这样边数直接从 $ n^2 $ 缩减至 $ n \times log {n}$，**冲！**

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
int n,m,s,t,S,T,N;
const int maxn=2e6+10;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int to[maxn],cap[maxn],cost[maxn],nt[maxn],head[maxn],cnt=1;
int dis[maxn],vis[maxn],pre[maxn],incf[maxn],mincost,maxflow;
inline void addedge(int u,int v,int w,int c)
{
    to[++cnt]=v,cap[cnt]=w,cost[cnt]=c,nt[cnt]=head[u],head[u]=cnt;
    to[++cnt]=u,cap[cnt]=0,cost[cnt]=-c,nt[cnt]=head[v],head[v]=cnt;
}
inline int spfa()
{
    queue <int> que;
    for(int i=0;i<=t;++i)   dis[i]=INF,vis[i]=0;
    que.push(s),incf[s]=INF,dis[s]=0,vis[s]=1;
    while(!que.empty())
    {
        int u=que.front(),v;
        que.pop(),vis[u]=0;
        for(int i=head[u];i;i=nt[i])
        {
            v=to[i];
            if(dis[v]<=dis[u]+cost[i]||!cap[i]) continue;
            dis[v]=dis[u]+cost[i],incf[v]=min(incf[u],cap[i]),pre[v]=i;
            if(!vis[v]) vis[v]=1,que.push(v);
        }
    }
    return dis[t]<INF;
}
inline void mcmf()
{
    while(spfa())
    {
        int x=t,i;
        maxflow+=incf[t];
        mincost+=incf[t]*dis[t];
        while(x!=s)
        {
            i=pre[x];
            cap[i]-=incf[t],cap[i^1]+=incf[t];
            x=to[i^1];
        }
    }
}
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
int co;
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		addedge(s,rt,1,0);
		co=max(co,rt);
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	addedge(ls,rt,mid-l+1,0);
	addedge(rs,rt,r-mid,0);
}
inline void update(int rt,int l,int r,int L,int R,int c,int x)
{
	if(L<=l&&r<=R)
	{
		addedge(rt,x,1,-c);
		return ;
	}
	if(L<=mid)	update(ls,l,mid,L,R,c,x);
	if(mid<R)	update(rs,mid+1,r,L,R,c,x);
}
struct node
{
	int a,b,c;
}p[maxn];
signed main()
{
	n=read(),s=0,t=30000;
	for(int i=1;i<=n;++i)
	{
		p[i].a=read(),p[i].b=read()-1,p[i].c=read();
		N=max(N,p[i].b);
	}
	build(1,1,N);
	for(int i=1;i<=n;++i)
	{
		update(1,1,N,p[i].a,p[i].b,p[i].c,co+i);
		addedge(co+i,t,1,0);
	}
	mcmf();
	printf("%d\n",-mincost);
	return 0;
}
```



---

## 作者：DAMDAM (赞：0)

一眼费用流（二分图最大权匹配）。

强盗看成左部，抢劫时间看成右部，对应抢走的钱看成（负）边权从源点连向强盗流量上限 $1$ 的边，强盗向每个对应抢劫时间点连流量上限为 $1$ 边权为 $0$ 的边，最后每个抢劫时间点向汇点连流量上限为 $1$ 边权为 $0$ 的边。然后跑最大费用最大流即可。

额额太棒了。

仔细想想这个建图是【数据已删除】的 $\Theta(nV)$ 的（$V$ 为时间值域）。我怒了。

考虑 DS 优化建图。用线段树优化建图，具体地说我们建一棵入树，使得我们可以快速从点向区间连边。

建树：我们每个非叶子节点向其儿子连流量上限 $\infin$，边权 $0$ 的边，叶子节点代表每个抢劫事件点，还要向汇点连流量上限 $1$，边权 $0$ 的边。

点向区间连边：拆分为区间后直接连边即可。

这样建树后边的瓶颈转在点向区间连边上，为 $\Theta(n\log V)$。

然后稍微写一下这道题就过了。

```cpp
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
const int maxV = 5e3 + 5, maxn = 4 * maxV, maxm = 17 * maxV;
const ll inf = 0x3f3f3f3f3f3f3f3f;
struct Vertex {
	int num;
	ll dis;
	bool operator<(const Vertex &b) const & {
		return dis > b.dis;
	}
};

struct Edge {
	int to;
	ll dis, flow;
	int next;
} edge[maxm << 1];

int head[maxn];
void insert(const int &u, const int &v, const ll &w, const ll &c) {
	static int len = 1;
	edge[++len] = {v, w, c, head[u]}, head[u] = len;
}

void emplace(const int &u, const int &v, const ll &w, const ll &c) {
	insert(u, v, w, c), insert(v, u, -w, 0);
}

int s, t, cur[maxn];
ll w[maxn], dis[maxn], reply;
bitset<maxn> vis;
queue<int> q;
void Bellman_Ford() {
	q.push(s), memset(w, 63, sizeof w), w[s] = 0, vis[s] = 1;
	for (int u, v; !q.empty(); ) {
		u = q.front(), q.pop(), vis[u] = 0;
		for (int i = head[u]; i; i = edge[i].next)
			if (edge[i].flow && w[v = edge[i].to] > w[u] + edge[i].dis)	
				w[v] = w[u] + edge[i].dis, vis[v] || (q.push(v), vis[v] = 1);
	}
}

__gnu_pbds::priority_queue<Vertex> h;
bool Dijkstra() {
	memset(dis, 63, sizeof dis), h.push({s, dis[s] = 0});
	ll d;
	for (int u, v; !h.empty(); ) {
		u = h.top().num, h.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].next) {
			v = edge[i].to;
			if (edge[i].flow && dis[v] > (d = dis[u] + edge[i].dis + w[u] - w[v]))
				h.push({v, dis[v] = d});
		}
	}
	return dis[t] != inf;
}

ll Dfs(const int &u, const ll &flow) {
	if (u == t || !flow) return flow;
	ll ans = 0, d;
	vis[u] = 1;
	for (int &i = cur[u], v; i; i = edge[i].next) {
		v = edge[i].to;
		if (!vis[v] && dis[v] == dis[u] + edge[i].dis + w[u] - w[v] && (d = Dfs(v, min(flow - ans, edge[i].flow)))) {
			edge[i].flow -= d, edge[i ^ 1].flow += d, reply += d * edge[i].dis;
			if ((ans += d) == flow) break;
		}
	}
	return vis[u] = 0, ans;
}

void init() { for (int i = 0; i < maxn; ++i) w[i] += dis[i]; }

ll Dinic() {
	ll flow = reply = 0;
	for (Bellman_Ford(); Dijkstra(); vis.reset(), memcpy(cur, head, sizeof cur), flow += Dfs(s, inf), init()) ;
	return flow;
}

int n, len, ls[maxV << 1], rs[maxV << 1], rtIn;
void Build(const int &l = 1, const int &r = 5e3, int &p = rtIn) {
	p || (p = ++len);
	if (l == r) return emplace(p, t, 0, 1);
	int mid = l + ((r - l) >> 1);
	Build(l, mid, ls[p]), Build(mid + 1, r, rs[p]);
	emplace(p, ls[p], 0, inf), emplace(p, rs[p], 0, inf);
}

void PointToRange(const int &l, const int &r, const int &u, const ll &w, const ll &c, const int &s = 1, const int &t = 5e3, const int &p = rtIn) {
	if (l <= s && t <= r) return emplace(u, p, w, c);
	int mid = s + ((t - s) >> 1);
	if (l <= mid) PointToRange(l, r, u, w, c, s, mid, ls[p]);
	if (r > mid) PointToRange(l, r, u, w, c, mid + 1, t, rs[p]);
}

int main() {
	scanf("%d", &n), s = ++len, t = ++len, Build();
	for (int a, b, c, u; n; --n) u = ++len, scanf("%d%d%d", &a, &b, &c), emplace(s, u, -c, 1), PointToRange(a, b - 1, u, 0, 1);
	Dinic(), printf("%lld", -reply);
	return 0;
}
```

---

## 作者：Drind (赞：0)

被线段树优化建图折磨了一下午，又卡了一下午常。

### 题目解析

二分图最大权匹配，但是左边的每个点会连接右边的 $l_i$ 到 $r_i$ 的点。

因为网络流算法从不屈服于和 KM 的淫威之下，所以我们放弃神秘 KM 科技，使用费用流算法解决。

首先我们依照题目模拟建图的话，边数是 $O(n^2)$ 的。看一眼我们费用流 $O(nmf)$ 的复杂度，再看一眼 $n\le 5\times 10^3$ 的数据范围，显然不能过。所以我们需要一个线段树优化建图，所以打上了之后交一发，喜提 33pts，原来这题这么卡常。

我们想到了一个费用流算法就是 zkw 费用流，但是这个东西是基于 KM 的重标号做的，而且没法处理负权边，非常的不美丽，于是我们手动魔改 zkw 费用流。

首先多路增广是必须的，所以把 spfa 倒着跑。

然后对着这个 spfa 一顿卡常，具体地就是加上 slf 和 lll 优化。

slf 其实很简单，就是每次入队的时候，如果这个点的 dis 比队头的 dis 大，就把他塞到队头，不然就塞到队尾。

lll 其实也很简单，存储整个队列所有的 dis 总和，每次出队的时候，如果队列 dis 平均值小于现在出队的队头，就把这个队头扔到队尾去。

但是这题的图没有恶意构造，所以不加优化也可以，最主要的是要倒着跑 spfa 多路增广，当前弧也可以不加，因为反正多路增广，跑这个 dfs 的次数很少，当前弧还会增加常数，不如不加了。

然后跑一个最大费用最大流即可，把所有费用取反就行。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f;
int s,t,mncos=0;
struct node{
	int to,nxt,flow,cost;
}edge[N*2]; int head[N],cnt=-1;
inline void add(int u,int v,int w,int c){
	edge[++cnt].to=v;
	edge[cnt].flow=w;
	edge[cnt].cost=c;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
inline void adde(int u,int v,int w,int c){
	add(u,v,w,c); add(v,u,0,-c);
}

bitset<N>vis; int dis[N];
inline bool spfa(){
	vis=0; memset(dis,0x3f,sizeof dis);
	dis[t]=0; vis[t]=1; int sum=dis[s],num=1;
	deque<int>q; q.push_front(t);
	while(!q.empty()){
		int u=q.front(); 
		while(dis[u]*num>sum){//lll
			q.pop_front();
			q.push_back(u);
			u=q.front();
		}
		q.pop_front();
		sum-=dis[u];
		num--;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i^1].flow&&dis[v]>dis[u]-edge[i].cost){//倒着跑 spfa
				dis[v]=dis[u]-edge[i].cost;
				if(!vis[v]){
					vis[v]=1;//slf
					if(!q.empty()&&dis[v]<dis[q.front()]) q.push_front(v);
					else q.push_back(v);
				} 
			}
		}
		vis[u]=0;
	}
	return dis[s]<inf;
}

inline int dfs(int u,int f){
	if(u==t){
		vis[t]=1; return f;
	}
	vis[u]=1;int r=f;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to; if(!vis[v]&&edge[i].flow&&dis[u]-edge[i].cost==dis[v]){//这边也要倒着枚举
			int tmp=dfs(v,min(edge[i].flow,r));
			if(tmp){
				mncos+=tmp*edge[i].cost;
				edge[i].flow-=tmp;
				edge[i^1].flow+=tmp;
				r-=tmp;
			}
			if(r==0) break;
		}
	}
	return f-r;
}

inline int zkw(){
	int mxflo=0;
	while(spfa()){
		vis[t]=1;
		while(vis[t]){
			vis=0;
			mxflo+=dfs(s,inf);
		}
	}
	return mxflo;
}

void build(int x,int l,int r){//线段树优化建图，只需要一个入树就行。
	if(l==r){
		adde(x,t,1,0);
		return;
	} int mid=(l+r)/2;
	build(x*2,l,mid); build(x*2+1,mid+1,r);
	adde(x,x*2,inf,0); adde(x,x*2+1,inf,0);
}

void modify(int x,int l,int r,int L,int R,int f){//从 f 连到 [l,r] 区间，[L,R] 是当前节点 x 的负责区间
	if(l<=L&&R<=r){
		adde(f,x,inf,0);
		return;
	}
	if(L>r||R<l) return;
	int mid=(L+R)/2;
	modify(x*2,l,r,L,mid,f);
	modify(x*2+1,l,r,mid+1,R,f);
}

void fake_main(){
	memset(head,-1,sizeof head);
	int n; cin>>n; s=N-1,t=s-1; n--;//注意读题，每个人对应的是区间不是点。
	build(1,1,n);
	for(int i=1;i<=n+1;i++){
		int l,r,w; cin>>l>>r>>w; r--;
		modify(1,l,r,1,n,n*4+i);
		adde(s,n*4+i,1,-w);
	}
	zkw();
	cout<<-mncos<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

跑了个总用时 6.6s 左右的成绩，被 KM 拉爆了，只是勉强能过，哭了。

---

