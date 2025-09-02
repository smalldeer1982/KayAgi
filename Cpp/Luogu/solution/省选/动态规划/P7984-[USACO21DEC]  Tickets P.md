# [USACO21DEC]  Tickets P

## 题目描述

Bessie 正在参加远足旅行！她当前正在旅行的路线由编号为 $1\ldots N$（$1\le N\le 10^5$）的 $N$ 个检查点组成。

有 $K$（$1\le K\le 10^5$）张票可供购买。第 $i$ 张票可以在检查站 $c_i$（$1\le c_i\le N$）以 $p_i$（$1\le p_i\le 10^9$）的价格购得，并且可以用其进入所有检查站 $[a_i,b_i]$（$1\le a_i\le b_i\le N$）。在进入任何检查站之前，Bessie 必须已购买一张允许其进入该检查站的票。一旦 Bessie 可以前往某一检查站，她就可以在未来的任何时候回到该检查站。

对于每一个 $i\in [1,N]$，如果 Bessie 最初只能进入检查点 $i$，输出使得可以进入检查点 $1$ 和 $N$ 所需的最低总价。如果无法这样做，输出 $-1$。


## 说明/提示

【样例解释】

如果 Bessie 从检查点 $i=4$ 开始，那么一种购得进入检查点 $1$ 和 $N$ 的方法如下：

在检查点 $4$ 购买第一张票，使 Bessie 可以进入检查点 $2$ 和 $3$。

在检查点 $2$ 购买第三张票，使 Bessie 可以进入检查点 $7$。

回到检查点 $4$ 购买第二张票，使 Bessie 可以进入检查点 $5$ 和 $6$。

在检查点 $6$ 购买第四张票，使 Bessie 可以进入检查点 $1$。

【数据范围】

- 测试点 1-7 满足 $N,K\le 1000$。
- 测试点 8-19 没有额外限制。


## 样例 #1

### 输入

```
7 6
4 1 2 3
4 10 5 6
2 100 7 7
6 1000 1 1
5 10000 1 4
6 100000 5 6```

### 输出

```
-1
-1
-1
1111
10100
110100
-1```

# 题解

## 作者：ETHANK (赞：14)

>  题目难度：USACO P/省选

先想暴力做法。注意到一个人不会重复买票，所以我们可以把每种票看作虚拟节点，买票看作从 $c_i$ 到 $i$ 号票边权为 $p_i$ 的边，同时 $i$ 号票向区间 $[a_i,b_i]$ 中的所有点连边权为 $0$ 的边。题目希望求出每个点到达 $1$ 和 $n$ 所需的最小代价，不妨建反图以 $1$ 和 $n$ 为原点分别跑一遍最短路。

然而这样会喜提 WA 。因为仍然没有解决重复买票的问题，两条最短路的交集中的所有边被算了两遍。怎么解决？先记当前答案为 $dis_i=d1_i+dn_i$ ，若节点 $u$ 的两条最短路均经过它的邻居 $v$ ，不难发现 $dis_u=dis_v+w$ 。这和单源最短路的松弛本质相同，我们对答案数组重新跑一遍最短路即可。

时间复杂度：$O(NK\log(NK))$

下面提供两种优化的思路，第一种是考场第一眼看出的线段树优化建图，具体知识可以参考这个博客 [DS优化建图](https://www.luogu.com.cn/blog/forever-captain/DS-optimize-graph) 。

对区间中的每个点暴力连边是不好的！我们用线段树建图的方式连边，时间复杂度为 $O(N\log^2 N)$ 。USACO评测机或洛谷开 O2 均可通过本题。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e6+5,M=7e6+5;
const ll inf=1e16;
int head[N],cnt;
struct Edge{
    int to,nxt,w;
}e[M];
inline void add(int u,int v,int w){e[++cnt]={v,head[u],w};head[u]=cnt;}
int n,q,s;
struct Node{int l,r;}t[N];
#define ls (p<<1)
#define rs (ls|1)
inline void build(int p,int l,int r){
    t[p].l=l,t[p].r=r;
    if(l==r){//叶子节点与原图加边
        add(l+8*n,p,0);add(p+4*n,l+8*n,0);
        add(p,l+8*n,0);add(l+8*n,p+4*n,0);
        return;
    }
    //向儿子连边
    add(p,ls,0);add((ls)+4*n,p+4*n,0);
    add(p,rs,0);add((rs)+4*n,p+4*n,0);
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
inline void upd(int p,int L,int R,int u,int w){
    int l=t[p].l,r=t[p].r,mid=(l+r)>>1;
    if(l==L&&r==R){//当前节点覆盖区间
        add(p+4*n,u+8*n,w);
        return;
    }
    if(R<=mid)upd(ls,L,R,u,w);
    else if(L>mid)upd(rs,L,R,u,w);
    else{
        upd(ls,L,mid,u,w);upd(rs,mid+1,R,u,w);
    }
}
ll dis[N],d[N];
struct node{
    ll dis;int pos;
    bool operator <( const node &x )const{
        return x.dis < dis;
    }
};
bool vis[N];
priority_queue <node> pq;
inline void dijkstra(bool op=0){
    if(!op){
        memset(dis,0x3f,sizeof(dis));
        dis[s]=0;pq.push({0,s});
    }else{
        rep(i,1,9*n+q)pq.push({dis[i],i});
    }
    memset(vis,0,sizeof(vis));
    while(!pq.empty()){
        node tmp=pq.top();pq.pop();
        int x=tmp.pos;
        if(vis[x])continue;
        vis[x]=1;
        for(int i=head[x];i;i=e[i].nxt){
            int y=e[i].to;
            if(dis[y]>dis[x]+e[i].w){
                dis[y]=dis[x]+e[i].w;
                pq.push({dis[y],y});
            }
        }
    }
}
int main(){
    n=read(),q=read();
    build(1,1,n);
    rep(i,1,q){
        int a=read(),w=read(),b=read(),c=read();
        upd(1,b,c,i+n,0);
        add(9*n+i,a+8*n,w);
    }
    s=8*n+1;
    dijkstra();
    memcpy(d,dis,sizeof(d));
    //rep(i,1,n)cout<<dis[i+8*n]<<' ';
    s=9*n;
    dijkstra();
    rep(i,1,9*n+q)dis[i]+=d[i];
    dijkstra(1);
    rep(i,1,n){
        if(dis[i+8*n]>inf)puts("-1");
        else printf("%lld\n",dis[i+8*n]);
    }
    return 0;
}
```

如何优化？考虑 dijkstra 时实际上在做什么。原图中的节点会影响将它包含的票的虚拟节点，然后这个虚拟节点仅影响其所对应的一个原图节点 $(i\to c_i)$ 。其次，我们知道堆优化 dijkstra 后每个票仅会被更新一次。于是并不需要建出图，在线段树上转移并且对更新完的区间打上标记就可以做到 $O(N\log N)$ （代码咕咕咕）。

第二种做法来自 Benq 的题解。同样利用上面的性质，对所有票按左端点升序排列，注意到每个门票最多入队一次，建一棵势能线段树维护一段区间的所有票右端点的最大值即可。在每个票入队后打上标记，均摊分析可以得出复杂度为 $O(N\log N)$ 。目前在洛谷上是最优解。

时间复杂度：$O(N\log N)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=2e5+5;
const ll inf = 1e18;
struct ticket{int c,p,a,b;};
bool cmp(ticket x,ticket y){return x.a<y.a;}
struct SegTree{
    int n,sz;
    vector <int> mx;
    vector <ticket> tickets;
#define ls (p<<1)
#define rs (ls|1)
    void pushup(int p){mx[p]=max(mx[ls],mx[rs]);}
    SegTree(vector <ticket> tickets) : tickets(tickets){//初始化
        n = 1;
        sz = sz(tickets);
        while(n < sz)n<<=1;
        mx.assign(2*n,0);
        rep(i,0,n-1){
            if(i < sz){
                mx[i+n] = tickets[i].b;
            }else mx[i+n] = -1;
        }
        per(i,n-1,1)pushup(i);
    }
    //找到所有可能转移的门票并移除
    void remove(vector <int> &v,int x,int p=1,int L=0,int R=-1){
        if(R==-1)R+=n;
        if(L>=sz||tickets[L].a>x||mx[p]<x)return;
        if(L==R){
            mx[p] = -1;
            v.pb(L);
            return;
        }
        int mid = (L+R)>>1;
        remove(v,x,ls,L,mid),remove(v,x,rs,mid+1,R);
        pushup(p);
    }
};
void Min(ll &a,const ll b){if(a>b)a=b;}
int main(){
    int n=read(),k=read();
    vector <ticket> tickets(k);
    for(auto &t: tickets){
        t.c=read()-1,t.p=read(),t.a=read()-1,t.b=read()-1;
    }
    sort(ALL(tickets),cmp);
    auto Dij = [&](vector<ll> &dis){//Dijkstra
        priority_queue <pair<ll,int>> pq;
        rep(i,0,k-1){
            Min(dis[tickets[i].c],dis[i+n]+tickets[i].p);
        }
        rep(i,0,n-1){
            if(dis[i]<inf)pq.push({-dis[i],i});
        }
        SegTree seg(tickets);
        while(!pq.empty()){
            pii x = pq.top();
            pq.pop();
            if(-x.fi>dis[x.se])continue;
            vector <int> vec;
            seg.remove(vec,x.se);//找到转移的门票
            for(int t : vec){
                if(dis[t+n] > dis[x.se]){
                    dis[t+n] = dis[x.se];
                    if(dis[tickets[t].c] > dis[x.se] + tickets[t].p){
                        dis[tickets[t].c] = dis[x.se] + tickets[t].p;
                        pq.push({-dis[tickets[t].c],tickets[t].c});
                    }
                }
            }
        }
    };
    //三次最短路
    vector <ll> L(n+k,inf),R(n+k,inf),dis(n+k);
    L[0]=0,R[n-1]=0;
    Dij(L),Dij(R);
    rep(i,0,n+k-1)dis[i] = L[i] + R[i];
    Dij(dis);
    rep(i,0,n-1){
        if(dis[i]<inf)printf("%lld\n",dis[i]);
        else puts("-1");
    }
    return 0;
}
```

## 

---

## 作者：vectorwyx (赞：6)

令 $f_i$ 表示从 $i$ 出发的答案，则 $f_i=\min_{i\to j}(f_j+val(i\to j))$ 。初始值 $f_i=dis_{i,1}+dis_{i,n}$。

注意到这就是一个最短路更新 dp 的形式，线段树优化建出反图后跑 dijkstra 即可。时间复杂度 $O(n\log^2 n)$。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<ll,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=4e6+5;
const ll inf=1e17;
struct Edge{
	int to,next,val;
}e[N];
ll dis[N],a[N];
int vis[N],ti,tot,head[N],n,m,qwq;

struct Node{
	int l,r,lt=0,rt=0;
}tree[N];
int num,root;

void connect(int x,int y,int v){
	//printf("connect(%d,%d,%d)\n",x,y,v);
	e[++tot]=(Edge){y,head[x],v};
	head[x]=tot;
}

void dij(int s,int o){
	//printf("dij(%d)\n",s);
	priority_queue<pii> q;
	if(o){
		fo(i,1,num+qwq) dis[i]=inf;
		dis[s]=0;q.push(mk(0,s));		
	}else fo(i,1,num+qwq) dis[i]=a[i],q.push(mk(-dis[i],i));
	++ti;
	while(!q.empty()){
		while(!q.empty()&&vis[q.top().se]==ti) q.pop();
		if(q.empty()) break;
		int x=q.top().se;q.pop();
		vis[x]=ti;
		for(int i=head[x];i;i=e[i].next){
			int p=e[i].to;
			if(dis[p]>dis[x]+e[i].val){
				dis[p]=dis[x]+e[i].val;
				q.push(mk(-dis[p],p));
			}
		}
	}
//	fo(i,1,n) cout<<dis[i]<<" ";puts("");
}
//线段树优化，建反图，先以 1 为源点跑最短路，再以 n 为源点跑最短路，然后把每个结点的初始 dis 赋为 (1,i)+(n,i)，全扔进堆里跑 dij 


#define ls(x) x<<1
#define rs(x) x<<1|1

int build(int l,int r){
	//printf("build(%d,%d)\n",l,r);
	if(l==r){
		tree[l].l=l,tree[l].r=r;
		return l;
	}
	int mid=l+r>>1;int x=++num;
	//printf("num=%d,[%d,%d]\n",num,l,r);
	tree[x].l=l,tree[x].r=r;
	tree[x].lt=build(l,mid);
	tree[x].rt=build(mid+1,r);
	connect(tree[x].lt,x,0);
	connect(tree[x].rt,x,0);
	return x;
}

void update(int x,int l,int r,int aim){
	//printf("update(%d,%d,%d,%d,%d)\n",x,l,r,aim,val);//system("Pause");
	if(tree[x].l>=l&&tree[x].r<=r){
		connect(x,aim,0);//建反边 
		return;
	}
	int mid=(tree[x].l+tree[x].r)>>1;//,lt=tree[x].lt,rt=tree[x].rt;
	if(l<=mid) update(tree[x].lt,l,r,aim);
	if(r>mid) update(tree[x].rt,l,r,aim);
}

signed main(){
	cin>>n>>m;num=n;
	root=build(1,n);
	fo(i,1,m){
		int c=read(),p=read(),l=read(),r=read();
		++qwq;
		update(root,l,r,qwq+num);
		connect(qwq+num,c,p);
	}
	dij(1,1);fo(i,1,num+qwq) a[i]+=dis[i];
	dij(n,1);fo(i,1,num+qwq) a[i]+=dis[i];
	dij(0,0);
	fo(i,1,n){
		if(dis[i]<=inf/2) cout<<dis[i]<<'\n';
		else cout<<"-1\n";
	}
	return 0;
}
/*
7 6
4 1 2 3
4 10 5 6
2 100 7 7
6 1000 1 1
5 10000 1 4
6 100000 5 6
-------------------------------------------------
-1
-1
-1
1111
10100
110100
-1
*/
```

---

## 作者：cmll02 (赞：3)

这个东西一脸可以 DS 优化建图。

对于一张票，连边 $(u,ticket,w),(ticket,P,0)$，$P$ 是线段树上所有对应的区间。

考虑倒着跑，分别求出 $1,n$ 到每个点的最短路。

那现在要同时访问到 $1,n$。。

对每个点（包括线段树的那些虚点和表示票的点）执行加边 $(S,i,dis1_i+disn_i)$，

然后再跑 $S$ 开始的最短路。

这个东西为什么是对的？其实就类似于最短路。

相当于 $1$ 和 $n$ 同时先走到一个点，然后剩下的路程可以合走。

同时到一个点就是距离相加，合走就是在原来的图上转移。

---

## 作者：Foreverxxx (赞：3)

首先考虑如何建图。

对于暴力的建图方式，很明显空间复杂度会达到 $O(n^2)$，明显会超时。

那么我们可以使用线段树建图优化的建图方式将空间复杂度降低为 $O(n\log n)$，具体不会的话请右转 [CF786B Legacy](https://www.luogu.com.cn/problem/CF786B) 学习。

好的我们已经成功建出了图，那我们又如何统计每个点的答案呢？

暴力的做法显然是每个点都进行枚举，不过很明显会超时。

那么我们考虑从 $1$ 和 $n$ 分别跑一次最短路，统计出所有点到达这两个点的距离（注意要建反图）。

但是现在又有一个问题：假设 $n=4$，我们从 $3$ 出发，经过 $2$ 到达了 $1$ ，又从 $3$ 出发，经过 $2$ 到达了 $4$ ，很明显 $2$ 经过了两次，在统计答案时会被重复计算。

那我们又如何解决第二次到达不需要重复计算的问题呢？

统计每个点分别到 $1$ 和到 $n$ 点的距离和，然后将所有点压入队列中再跑一次最短路即可。

为什么是正确的呢？

由最短路的三角形不等式 $dist_u \ge dist_x +v$ 可知，如果这条边被重复走，新的 $dist_u$ 是由原来 $x$ 点到达 $1$ 和 $n$ 的路径和加上连接两点的边权得到，图中并不存在负环，**所以某个点不会被连出去的同一条边更新两次**，即重复计算问题被解决。

Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int sss=0;
	char chh=getchar();
	while(chh<'0'||chh>'9') chh=getchar();
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss;
}
int n,m,N,root,tmp;
struct Tree{
	int l,r,lson,rson;
}tree[3000005];
int dist[3000005],vis[3000005];
int anss[3000005];
int head[3000005],to[3000005],val[3000005],nxt[3000005],tot=0;
struct node{
	int dis,pos;
	bool operator<(const node& x)const{
		return x.dis<dis;
	} 
};
void add(int u,int v,int w){
	to[++tot]=v;
	val[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}
int build(int l,int r){
	if(l==r){
		tree[l].l=l;
		tree[l].r=r;
		return l;
	}
	int mid=(l+r)>>1;
	int tmp_pos=++N;
	tree[tmp_pos].l=l;
	tree[tmp_pos].r=r;
	tree[tmp_pos].lson=build(l,mid);
	tree[tmp_pos].rson=build(mid+1,r);
	add(tree[tmp_pos].lson,tmp_pos,0);
	add(tree[tmp_pos].rson,tmp_pos,0);
	return tmp_pos;//返回编号 
}
void update(int now,int l,int r,int pos){
	if(tree[now].l>=l&&tree[now].r<=r){
		add(now,pos,0);
		return;
	}
	int mid=(tree[now].l+tree[now].r)>>1;
	if(l<=mid) update(tree[now].lson,l,r,pos);
	if(r>mid) update(tree[now].rson,l,r,pos);
}
void Dijkstra(int sta){//正常的最短路 
	priority_queue<node> q;
	memset(dist,0x3f,sizeof dist);
	memset(vis,false,sizeof vis);
	dist[sta]=0;
	q.push((node){0,sta});		
	while(!q.empty()){
		int x=q.top().pos; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i],v=val[i];
			if(dist[u]>dist[x]+v){
				dist[u]=dist[x]+v;
				if(!vis[u]) q.push((node){dist[u],u});
			}
		}
	}
}
void DP(){
	priority_queue<node> q;
	memset(vis,false,sizeof vis);
	int len=tmp+N;
	for(register int i=1;i<=len;i++){
		dist[i]=anss[i];
		q.push((node){dist[i],i});//现将所有点压入优先队列中，然后跑最短路 
	}
	while(!q.empty()){
		int x=q.top().pos; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i],v=val[i];
			if(dist[u]>dist[x]+v){
				dist[u]=dist[x]+v;
				if(!vis[u]) q.push((node){dist[u],u});
			}
		}
	}
}
signed main(){
	N=n=read(),m=read();
	root=build(1,n);
	int from,value,l,r;
	for(register int i=1;i<=m;i++){
		from=read(),value=read(),l=read(),r=read();
		tmp++;
		update(root,l,r,tmp+N);
		add(tmp+N,from,value);
	}
	Dijkstra(1);
	int len=N+tmp;
	for(register int i=1;i<=len;i++){
		anss[i]+=dist[i];
	}
	Dijkstra(n);
	len=N+tmp;
	for(register int i=1;i<=len;i++){
		anss[i]+=dist[i];//统计出所有点分别到1和n的最短路和 
	}
	DP();//进行DP处理 
	for(register int i=1;i<=n;i++){
		if(dist[i]<=1e15) printf("%lld\n",dist[i]);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：Tmbcan (赞：2)

## [P7984 [USACO21DEC] Tickets P](https://www.luogu.com.cn/problem/P7984)

### 思路

把每张票都看作一个节点，能买到票的检查站 $c_i$ 向票连权值为 $p_i$ 的边，票向能到达的检查站 $[a_i,b_i]$ 连权值为 0 的边。 

现在统计答案，需要求对于每个节点 $i$ 的最短路 $dis_{1,i}$ 和 $dis_{i,n}$，我们可以建反边分别跑以 1 和 $n$ 为起点的最短路。

然后考虑如何合并答案。由于路径上重复经过的边只会累加一次代价，所以此时 $dis_{1,i}+dis_{i,n}$ 并不是最终答案，因为可能存在重复计算了代价的边。

令 $g_i$ 表示点 $i$ 的最终答案，则 $g_i\le dis_{1,i}+dis_{i,n}$。  
设 $S_i$ 为点 $i$ 答案中重复统计了的点的点集。  
当 $S_i=\varnothing$ 时，$g_i=dis_{1,i}+dis_{i,n}$。  
当 $S_i\ne\varnothing$ 时，总存在 $u\in S_i$ 使得 $S_u=\varnothing$，此时 $g_u=dis_{1,u}+dis_{u,n}$。对于边 $u\to v$，当确定了 $g_u$ 后，$g_v=\min(g_v,g_u+w_{u\to v})$。  
我们发现这个转移和最短路的转移一模一样。  
所以我们初始时假设每个点都没有重复计算的代价，令 $g_i=dis_{1,i}+dis_{i,n}$，最后再跑一遍最短路求 $g$。


由于要对连续的区间连边，所以用 DS 优化建图。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<queue>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T>
inline void read(T&x){//快读
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') w=1;
		ch = getchar();
	}
	while(ch>='0' && ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 1e5+10,LG = 17;
const ll INF = 1e17;
int n,m;
struct{
	int to,nex; ll w;
}edge[N*LG*2];
int head[N*LG*2],edge_num;
inline void add(int x,int y,ll w){
	edge[++edge_num].to = y;
	edge[edge_num].nex = head[x];
	head[x] = edge_num;
	edge[edge_num].w = w;
}
int P=1,DEP=0,NOW;
ll dis[N*4],tmp[N*4];bool vis[N*4];
struct node{
	ll w; int p;
	bool operator < (const node&G) const{
		return w > G.w;
	}
};
priority_queue <node> q;
inline void dijkstra(){//最短路
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		node now = q.top();
		q.pop();
		vis[now.p] = 1;
		for(int i=head[now.p];i;i=edge[i].nex){
			int tto = edge[i].to;
			if(dis[tto]>dis[now.p]+edge[i].w){
				dis[tto] = dis[now.p]+edge[i].w;
				if(!vis[tto]) q.push({dis[tto],tto});
			}
		}
	}
}
int main(){
// 	freopen("in.in","r",stdin);
// 	freopen("out.out","w",stdout);

	read(n,m);//注意都建成反边
	while(P<=n+1) P<<=1,++DEP; NOW = (P<<1)-1;//zkw 优化建图
	for(int i=P-1;i;--i) add(i<<1,i,0),add(i<<1|1,i,0);
	for(int i=1,v,k,l,r;i<=m;++i){
		read(v,k,l,r);
		add(++NOW,v+P,1ll*k);//检查站向票的边
		// update
		l += P-1; r += P+1;
		while(l^1^r){
			if(~l&1) add(l^1,NOW,0);//票向检查站的边
			if(r&1) add(r^1,NOW,0);
			l>>=1;r>>=1;
		}
	}
	//1为起点的最短路
	for(int i=1;i<=NOW;++i) dis[i] = INF;
	dis[1+P] = 0; q.push({0,1+P}); dijkstra();
	//n为起点的最短路
	for(int i=1;i<=NOW;++i) tmp[i] = dis[i],dis[i] = INF;
	dis[n+P] = 0; q.push({0,n+P}); dijkstra();
	//再跑一遍最短路求最终答案
	for(int i=1;i<=NOW;++i){
		dis[i] += tmp[i];
		q.push({dis[i],i});
	}
	dijkstra();
	for(int i=1;i<=n;++i) printf("%lld\n",(dis[i+P]<INF)?dis[i+P]:-1);

//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```

---

## 作者：Acoipp (赞：1)

首先考虑终点只有 $1$ 的情况，那么我们使用线段树优化建图即可完成。

具体来说，我们把每一张票看作一个节点，票向其能够到达的点连边，然后能够买到票的点向票连边。

注意：只有**向票连的边**有边权，边权就是买票的花费，剩下的边边权为 $0$，最后相当于要对每个节点 $i$ 找到到 $1$ 节点的最短路，于是建反图直接 Dijkstra 即可。

这么做肯定是对的，因为我们一旦买了一张票之后，在最优解中一定不会重复买这一张票，如果重复买了一张票，那么一定可以舍弃其中的一张。

接下来考虑终点有 $1$ 和 $n$ 的情况，直观的想法就是找到一个点到 $1$ 和 $n$ 节点各自的最短路加起来即可，但是这样做显然是错的，因为重复经过一条边会被计算多次。

考虑避免这种情况，我们发现，对于任意一个点 $i$ 的到 $1$ 和 $n$ 的最优路径上一定存在一个点 $p$，满足 $p \to 1$ 和 $p \to n$ 的最短路不交，然后剩下 $i \to p$ 这一条路径。

于是从 $p$ 开始扩展即可。做法即把所有点的 $dis1_i+dis2_i$ 放到堆里面重新跑一遍 Dijkstra 即可，边权不变。

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
using namespace std;
inline char nc(){
	static char buf[1000000],*p=buf,*q=buf;
	return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
}
inline ll read(){
	ll res = 0,w = 1;
	char c = nc();
	while(c<'0'||c>'9')w=(c=='-'?-1:w),c=nc();
	while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
	return res*w;
}
char obuf[1<<21],*p3=obuf; 
inline void pc(char c){ 
	p3-obuf<=(1<<20)?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c); 
} 
inline void write(ll x){ 
	if(x<0) pc('-'),x=-x; 
	if(x>9) write(x/10); 
	pc(x%10+'0'); 
}
struct node{
	ll id,x;
	bool operator<(const node& a)const{
		return a.x<x;
	}
};
priority_queue<node> que;
ll n,k,c,p,a,b,dis[N],tr_tot,tr[N],ne[N],la[N],to[N],val[N],i,et,dis1[N],dis2[N];
inline void merge(ll x,ll y,ll z){et++,ne[et]=la[x],la[x]=et,to[et]=y,val[et]=z;}
inline void build(ll s,ll t,ll p){
	if(s==t){
		tr[p] = s;
		return ;
	}
	tr[p] = ++tr_tot;
	build(s,(s+t)/2,2*p),build((s+t)/2+1,t,2*p+1);
	merge(tr[2*p],tr[p],0),merge(tr[2*p+1],tr[p],0);
}
inline void modify(ll l,ll r,ll c,ll s,ll t,ll p){
	if(l<=s&&t<=r) return merge(tr[p],c,0);
	if(l<=(s+t)/2) modify(l,r,c,s,(s+t)/2,2*p);
	if(r>(s+t)/2) modify(l,r,c,(s+t)/2+1,t,2*p+1);
}
inline void dijkstra(ll *dis,ll s,ll vals){
	if(s==-1) for(ll i=1;i<=tr_tot;i++) que.push((node){i,dis[i]});
	else dis[s] = vals,que.push((node){s,vals});
	while(que.size()){
		node tmp = que.top();
		que.pop();
		if(dis[tmp.id]!=tmp.x) continue;
		for(ll i=la[tmp.id];i;i=ne[i]){
			if(dis[to[i]]>tmp.x+val[i]){
				dis[to[i]]=tmp.x+val[i];
				que.push((node){to[i],dis[to[i]]});
			}
		}
	}
}
int main(){
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	memset(dis,0x3f,sizeof(dis));
	n=read(),k=read(),tr_tot=n+k;
	build(1,n,1);
	for(i=1;i<=k;i++){
		c=read(),p=read(),a=read(),b=read();
		merge(i+n,c,p),modify(a,b,i+n,1,n,1);
	}
	dijkstra(dis1,1,0),dijkstra(dis2,n,0);
	for(i=1;i<=tr_tot;i++) dis[i]=min(dis[i],dis1[i]+dis2[i]);
	dijkstra(dis,-1,-1);
	for(i=1;i<=n;i++){
		if(dis[i]<=1e18) write(dis[i]),pc('\n');
		else write(-1),pc('\n');
	}
	return fwrite(obuf,p3-obuf,1,stdout),0;
} 
```

---

## 作者：Anonymely (赞：1)

首先考虑建图，$[a,b]$ 向 $p$ 连长度为 $c$ 边，即可求出到 $1/n$ 的最短路。

但是题目要求同时能扩展到两个点的花费，如果两个点路径上有重合就寄了。

注意到跑出 $dis_{1 \to i},dis_{n \to i}$ 后设 $f_{i} = dis_{1 \to i} + dis_{n \to i}$，之后的转移是 $f_i + val(i \to j) \to j$，发现还是最短路转移，所以跑三遍最短路即可，问题转化为如何跑最短路。

暴力一点直接线段树优化建图，默认 $n,m$ 同阶，复杂度 $O(n \log^2 n)$。

考虑这样一个事实：对于每张票，能从 $[a,b]$ 转移过来且转移来的边权都为 $0$，故跑 dijkstra 时第一次松弛即为最终答案，也就是只会被松弛一边。

对于每条线段，我们将它挂到线段树上 $\log$ 个区间，扩展点 $u$ 时直接找出所有覆盖它的区间拓展并删掉，复杂度 $O(n \log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define debug(x) cerr << #x << " = " << x << '\n'
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 2e5 + 5;
int n, m, c[N], p[N];
bool vis[N], ok[N], clr[N << 2];
vector <int> t[N << 2];
ll dis[2][N * 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void ins(int p, int l, int r, int L, int R, int i) {
	if (L <= l && r <= R) return t[p].push_back(i), void();
	int mid = (l + r) / 2;
	if (L <= mid) ins(ls, l, mid, L, R, i);
	if (mid < R) ins(rs, mid + 1, r, L, R, i);
}
vector <int> pos;
void query(int p, int l, int r, int x) {
	if (!clr[p]) {
		for (auto i : t[p]) if (!ok[i]) pos.push_back(i), ok[i] = 1;
		clr[p] = 1;
	}
	if (l == r) return ;
	int mid = (l + r) / 2;
	x <= mid ? query(ls, l, mid, x) : query(rs, mid + 1, r, x);
}
void dijkstra(ll *dis) {
	for (int i = 1; i <= m; i++) ok[i] = 0;
	memset(clr, 0, sizeof(clr));
	priority_queue < pair <ll, int> > q;
	for (int i = 1; i <= m; i++) ckmin(dis[p[i]], dis[i + n] + c[i]);
	for (int i = 1; i <= n + m; i++) {
		vis[i] = 0;
		if (i <= n) q.push({-dis[i], i});
	}
	while (!q.empty()) {
		auto [d, u] = q.top();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		pos.clear();
		query(1, 1, n, u);
		for (auto i : pos) {
			if (dis[i + n] > dis[u]) {
				dis[i + n] = dis[u];
				if (dis[p[i]] > dis[i + n] + c[i]) {
					dis[p[i]] = dis[i + n] + c[i];
					q.push({-dis[p[i]], p[i]});
				}
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1, l, r; i <= m; i++) {
		cin >> p[i] >> c[i] >> l >> r;
		ins(1, 1, n, l, r, i);
	}
	for (int i = 1; i <= n + m; i++) dis[0][i] = dis[1][i] = 1e18;
	dis[0][1] = 0, dis[1][n] = 0;
	dijkstra(dis[0]), dijkstra(dis[1]);
	for (int i = 1; i <= n + m; i++) dis[0][i] += dis[1][i];
	dijkstra(dis[0]);
	for (int i = 1; i <= n; i++) {
		if (dis[0][i] >= 1e18) cout << -1 << '\n';
		else cout << dis[0][i] << '\n';
	}
	QwQ01AwA;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

## [[USACO21DEC] Tickets P](https://www.luogu.com.cn/problem/P7984)

首先我们思考暴力的 $O(n^2)$ 怎么做。显然比起每次以 $i$ 为起点跑 $n$ 遍最短路，建反图后分别以 $1$ 和 $n$ 为起点跑两遍最短路是更加经济的方式。然后你可能会以为 $\text{dis}(1,i)+\text{dis}(n,i)$ 就是答案了，之后你就会发现连样例都过不去。

为什么呢？假如说 $n=4$，$i=3$，此时 $\text{path}(1,3)=1\to2\to3$，而 $\text{path}(3,4)=3\to2\to4$，那么 $(2,3)$ 这条边就算重了。

如何解决？方法是将 $(\forall i)~\text{dis}(1,i)+\text{dis}(n,i)$ 作为每个点的初始 $\text{dis}$，然后再跑一遍最短路，此时得到的 $\text{dis}_i$ 就是每个点的答案了。然后你又会发现一个问题，就是某些点它转移不到。所以建边的时候**一定是先把当前点和一个虚点连一条有花费的边，再把虚点和区间上的所有点连边权为 0 的边**。这样跑出来的就是正确的。

37pts 就有了。

怎么优化到 100pts？线段树优化建图即可。

```cpp
#include<bits/stdc++.h>
#define fw fwrite(obuf,p3-obuf,1,stdout)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define putchar(x) (p3-obuf<1<<20?(*p3++=(x)):(fw,p3=obuf,*p3++=(x)))
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;

char buf[1<<20],obuf[1<<20],*p1=buf,*p2=buf,*p3=obuf,str[20<<2];
int read(){
	int x=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}
template<typename T>
void write(T x,char sf='\n'){
	if(x<0)putchar('-'),x=~x+1;
	int top=0;
	do str[top++]=x%10,x/=10;while(x);
	while(top)putchar(str[--top]+48);
	if(sf^'#')putchar(sf);
}
using ll=long long;
using pli=pair<ll,int>;
constexpr int MAXN=4e5+5;
int n,k,tn;
struct Tik{
	int c,p,a,b;
}t[MAXN];
int head[MAXN],tot;
struct{
	int v,to,w;
}e[5000005];
void addedge(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
ll dis[MAXN],d[MAXN];
bool vis[MAXN];
priority_queue<pli>q;
void dijkstra(int s,bool sh=0){
	memset(vis,0,sizeof(bool)*(tn+k+5));
	if(!sh){
		memset(dis,0x3f,sizeof(ll)*(tn+k+5));
		dis[s]=0;
		q.emplace(0,s);
	}else{
		memcpy(dis,d,sizeof(ll)*(tn+k+5));
		for(int i=1;i<=tn+k;++i)
			q.emplace(-dis[i],i);
	}
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].to)
			if(dis[e[i].v]>dis[u]+e[i].w){
				dis[e[i].v]=dis[u]+e[i].w;
				q.emplace(-dis[e[i].v],e[i].v);
			}
	}
}

#define lp p<<1
#define rp p<<1|1
struct{
	struct SegTree{
		int l,r,ls,rs;
	}st[MAXN];
	int build(int s,int t){
		if(s==t) return st[s]={s,t,0,0},s;
		int mid=(s+t)>>1,x=++tn;
		st[x]={s,t,build(s,mid),build(mid+1,t)};
		addedge(st[x].ls,x,0);
		addedge(st[x].rs,x,0);
		return x;
	}
	void update(int l,int r,int x,int p){
		if(l<=st[p].l&&st[p].r<=r) return addedge(p,x,0);
		int mid=(st[p].l+st[p].r)>>1;
		if(l<=mid) update(l,r,x,st[p].ls);
		if(mid<r) update(l,r,x,st[p].rs);
	}
}T;

int main(){
	n=tn=read(),k=read();
	int rt=T.build(1,n);
	for(int i=1;i<=k;++i){
		t[i]={read(),read(),read(),read()};
		addedge(tn+i,t[i].c,t[i].p);
		T.update(t[i].a,t[i].b,tn+i,rt);
	}
	dijkstra(1);
	memcpy(d,dis,sizeof(ll)*(tn+k+5));
	dijkstra(n);
	for(int i=1;i<=tn+k;++i) d[i]+=dis[i];
	dijkstra(1,1);
	for(int i=1;i<=n;++i) write(d[i]>=INF?-1:dis[i]);
	return fw,0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个景点和 $k$ 种门票，第 $i$ 种门票在景点 $c_i$ 内以 $p_i$ 元的价格售卖，可以进入 $[l_i,r_i]$ 的景点。输出从每一个景点内部出发，游玩第 $1$ 个景点和第 $n$ 个景点的最小费用。

$1\leq n,k\leq 10^5$。

## 思路

虽然是 trick 拼合题但是感觉还是挺有趣的。

首先考虑一个弱化版的问题，给出一个无向图，询问从一个点出发，走到 $1$ 和 $n$ 的最小代价，重复走过的代价只计算一次。

关于这类题目，有一个非常经典的 trick（[CF543B Destroying Roads](https://www.luogu.com.cn/problem/CF543B)），我们考虑求出每个点 $i$ 到 $1,n$ 两点的最短路（这个可以通过建立反图然后跑两遍最短路来实现），则一定存在一个点 $p$，使得 $i$ 至 $1$ 的最短路恰好由 $i$ 至 $p$ 的最短路和 $p$ 至 $1$ 的最短路构成，$i$ 至 $n$ 的最短路恰好由 $i$ 至 $p$ 的最短路和 $p$ 至 $n$ 的最短路构成，且 $p$ 至 $n$ 与 $p$ 至 $1$ 的最短路是无交的。

对于本题而言，可以考虑建立一个超级汇点 $T$，对于每一个点 $i$，建边 $(i,T,\mathrm{dis}(1,i)+\mathrm{dis}(n,i))$。答案就是每个点到 $T$ 的最短路（同样是建立反图）。原因也很简单，我们选择走到 $T$ 代表后面的路径无交了，之前的路径都是重合的。

回到本题。我们自然有一种暴力建边的方法，对于一种门票，建立一个点，将位置点向这个点连边，边权为费用，然后再将这个点向区间内的每个点连边，边权为 $0$。当然这种建图方法是难以通过的。

由于我们是将一个点连向区间的所有点，可以考虑线段树优化建图（[CF786B Legacy](https://www.luogu.com.cn/problem/CF786B)）。

时间复杂度 $O(n\log^2 n)$，假设 $m,n$ 同级。

最后放一张建出来的图吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/9uav98jn.png)

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

using i64 = long long;
const int N = 1e5 + 5;
int n, m;
struct ticket{
    int c, p, l, r;
} a[N];

vector<pair<int,i64> > g[N << 4];
int bel[N];

void add(int u, int v, i64 w){ g[v].emplace_back(u, w); }

void build(int i, int l, int r){
    if(l == r) return (bel[l] = i), void();
    build(ls, l, mid), build(rs, mid + 1, r);
    add(i, ls, 0), add(i, rs, 0);
}

void update(int ql, int qr, int v, int i, int l, int r){
    if(ql <= l && r <= qr) return add(v, i, 0);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(mid < qr) update(ql, qr, v, rs, mid + 1, r);
}

i64 dis[N << 4][3];
priority_queue<pair<i64,int>,vector<pair<i64,int>>,greater<pair<i64,int>>> q;
bool vis[N << 4];

void dijkstra(int s, int tag, int pt){
    for(int i=1;i<=pt;i++) dis[i][tag] = 1e18, vis[i] = false;
    q.emplace(dis[s][tag] = 0, s);
    while(!q.empty()){
        auto [d, u] = q.top(); q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : g[u]){
            if(dis[v][tag] > d + w){
                dis[v][tag] = d + w;
                q.emplace(dis[v][tag] ,v);
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=m;i++) cin >> a[i].c >> a[i].p >> a[i].l >> a[i].r;
    build(1, 1, n); int pt = *max_element(bel + 1, bel + n + 1);
    for(int i=1;i<=m;i++){
        add(bel[a[i].c], ++pt, a[i].p);
        update(a[i].l, a[i].r, pt, 1, 1, n);
    }
    dijkstra(bel[1], 0, pt);
    dijkstra(bel[n], 1, pt); pt++;
    for(int i=1;i<pt;i++) add(i, pt, dis[i][0] + dis[i][1]);
    dijkstra(pt, 2, pt);
    for(int i=1;i<=n;i++) cout << (dis[bel[i]][2] >= 1e18 ? -1ll : dis[bel[i]][2]) << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：strcmp (赞：0)

发现是联合省选 2023 火车站，但是带权，而且 $c_i$ 还不一定在 $[a_i,\,b_i]$ 内。显然贪不了心了。于是只能考虑线段树建图优化跑最短路。

显然的连接 $[a_i,\,b_i] \to c_i$，边权为 $p_i$，依次从 $1$ 开始和从 $n$ 开始求出最短路序列 $d,\,d'$。同时设 $f$ 是我们的答案。

发现 $i$ 的最小代价不一定是 $d_i + d_i'$，因为 $i$ 走出去的过程中，$i \to 1$ 和 $i \to n$ 的部分可能有重复，导致我们算重贡献。

考虑算重的部分，发现它一定存在一种最优方案：先走到某个共同的一个结点打开局面，然后两条最短路分道扬镳。那么代价就是到达共同结点所需要的代价，加上共同结点到 $1$ 和 $n$ 的代价。

因此 $f_i \le f_j + w_{i \leadsto j}$，$w$ 是 $i \leadsto j$ 的代价，发现也是最短路，把 $d_{i} + d_{i}'$ 压进优先队列里面再跑一次 dijkstra 即可。

时间复杂度 $\Theta(n \log^2 n)$，可以通过。

注意线段树上结点也需要跟超级源点连边，且每次区间连边应该是取出来的线段树结点连向一个新建的结点，新建结点连 $c_i$。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
using ld = double;
constexpr int maxn = 2e5 + 10, mx = 1e5, mod = 998244353;
priority_queue<pli, vector<pli>, greater<pli>> q; 
int t[maxn << 3], cnt = 0, n, k; vector<pli> g[maxn << 3];
int a[maxn], b[maxn], c[maxn]; ll p[maxn];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mid (l + r >> 1)
void bd(int l, int r, int x) {
	if (!t[x]) t[x] = ++cnt;
	if (l == r) return g[l].pb({ 0, t[x]});
	bd(l, mid, ls(x)), bd(mid + 1, r, rs(x));
	g[t[ls(x)]].pb({0, t[x]}), g[t[rs(x)]].pb({0, t[x]});
}
void add(int l, int r, int ml, int mr, int u, int x) {
	if (ml <= l && r <= mr) return g[t[x]].pb({ 0, u });
	ml <= mid && (add(l, mid, ml, mr, u, ls(x)), 1), mr > mid && (add(mid + 1, r, ml, mr, u, rs(x)), 1);
}
void dij(int s, ll* d) {
	memset(d, 0x3f, (cnt + 1) * sizeof(ll)); d[s] = 0; q.push({ 0LL, s });
	while (q.size()) {
		int u = q.top().Y; ll k = q.top().X; q.pop();
		if (k > d[u]) continue;
		for (pli v : g[u]) if (d[v.Y] > d[u] + v.X) d[v.Y] = d[u] + v.X, q.push({ d[v.Y], v.Y });
	}
}
ll d[3][maxn << 3];
int main() {
	scanf("%d%d", &n, &k); cnt = n; bd(1, n, 1);
	rep(i, 1, k) scanf("%d%lld%d%d", &c[i], &p[i], &a[i], &b[i]), g[++cnt].pb({ p[i], c[i] }), add(1, n, a[i], b[i], cnt, 1);
	dij(1, d[0]), dij(n, d[1]);
	rep(i, 1, cnt) g[cnt + 1].pb({ d[0][i] + d[1][i], i}); dij(cnt + 1, d[2]);
	rep(i, 1, n) printf("%lld\n", d[2][i] > 1e15 ? -1LL : d[2][i]);
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定 $n$ 个点，每个点有激活和未激活两种状态。你有 $k$ 种操作，第 $i$ 种操作有 $4$ 个参数 $c_i,p_i,l_i,r_i$，当编号为 $c_i$ 的点激活时，你可以花费 $p_i$ 的代价使得编号在 $[l_i,r_i]$ 区间内的点全部激活。对于每个 $i$，求一开始只有 $i$ 被激活的情况下，激活 $1$ 和 $n$ 两个点的最小代价。
>
> $1\le n,k\le 10^5$，$1\le p_i\le 10^9$。

## 解法

对于点 $u$，若按照题意建出一张图，那么最优路径就是从 $u$ 出发走到某个点 $v$，然后从 $v$ 出发分别走向 $1$ 和 $n$，且后面两条路径没有相交。若算出 $u$ 到 $1$ 和 $n$ 两条最短路的长度之和，那么从 $u\to v$ 这段代价会被计算两次，考虑怎么去掉这个代价。设 $\operatorname{dis}(u,v)$ 表示 $u$ 到 $v$ 的最短路，$f(u)$ 表示点 $u$ 的答案；那我们令 $f(u)=\operatorname{dis}(u,1)+\operatorname{dis}(u,n)$，即开始认为 $u\to 1$  和 $u\to n$ 两条最短路没有相交。那么对于本来两条路径就无交的点，这就是答案，记这些点点集为 $S$；对于有交的点，总是可以走若干条边代表有交的段，然后走到一个属于 $S$ 的点 $v$ 上，后面没有相交的路径答案就取 $f(v)$。再转化一下，对于边 $u\to v$，假设已经确定了 $v$ 的答案，那么就有 $f(u)\gets \min(f(u),f(v)+w(u\to v))$，就是考虑把 $u\to v$ 作为 $u$ 相交路径的一条边，然后取 $v$ 的答案路径接在 $u\to v$ 后面。发现这个可以建出反图后 Dijkstra 算。我们把图变成反图，线段树优化建边，算出 $f(u)=\operatorname{dis}(u,1)+\operatorname{dis}(u,n)$，然后把所有点压进优先队列里，算出最终的 $f$ 即可。时间复杂度 $O(n\log^2n)$​。

一个细节：区间向点连边时，建一个虚点，区间向虚点连边权为 $0$ 的边，虚点再向点连有边权的边。不然会出现从 $u$ 出发时分别去了两个点但是代价算了两次的情况。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
namespace Graph {
	struct Edge { int to, nxt, val; } e[maxn << 3];
	int head[maxn << 2], ecnt = 0;
	void addEdge(int u, int v, int w) {
		e[++ ecnt] = Edge { v, head[u], w };
		head[u] = ecnt;
	}
} using namespace Graph;
#define ll long long
int n, m; ll dis[maxn << 2][3]; priority_queue<pair<ll, int> >q;
namespace SegmentTree {
	#define lson l, mid, rt << 1
	#define rson mid + 1, r, rt << 1 | 1
	int N = 0;
	void build(int l, int r, int rt) {
		N = max(N, rt + n);
		if (l == r) return addEdge(l, rt + n, 0);
		int mid = (l + r) >> 1;
		build(lson), build(rson);
		addEdge((rt << 1) + n, rt + n, 0), addEdge((rt << 1 | 1) + n, rt + n, 0); 
	}
	void modify(int l, int r, int rt, int nowl, int nowr, int frm, int val) {
		if (nowl <= l && r <= nowr) return addEdge(rt + n, frm, val);
		int mid = (l + r) >> 1;
		if (nowl <= mid) modify(lson, nowl, nowr, frm, val);
		if (mid < nowr) modify(rson, nowl, nowr, frm, val);
	}
} using namespace SegmentTree;
bool vis[maxn << 2];
void Dijkstra(int id) {
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) {
		int u = q.top().second; q.pop();
		if (vis[u]) continue;
		vis[u] = 1
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to, w = e[i].val;
			if (dis[v][id] > dis[u][id] + w) {
				dis[v][id] = dis[u][id] + w;
				if (!vis[v]) q.push({-dis[v][id], v});
			}
		}
	}
} const ll inf = 1e18;
int main() {
	scanf("%d %d", &n, &m), build(1, n, 1);
	for (int i = 1, c, p, L, R; i <= m; i ++)
		scanf("%d %d %d %d", &c, &p, &L, &R), addEdge(++ N, c, p), modify(1, n, 1, L, R, N, 0);
	for (int i = 1; i <= N; i ++)
		dis[i][0] = dis[i][1] = inf;
	dis[1][0] = 0, q.push({0, 1}), Dijkstra(0);
	dis[n][1] = 0, q.push({0, n}), Dijkstra(1);
	for (int i = 1; i <= N; i ++)
		q.push({-(dis[i][2] = dis[i][0] + dis[i][1]), i});
	Dijkstra(2);
	for (int i = 1; i <= n; i ++)
		printf("%lld\n", dis[i][2] >= inf ? -1ll : dis[i][2]);
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7984)

# 前置知识

[线段树优化建图](https://oi-wiki.org/ds/seg/#%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%BC%98%E5%8C%96%E5%BB%BA%E5%9B%BE) | [最短路](https://oi-wiki.org/graph/shortest-path/)

# 解法

考虑对票建虚点，从 $c_{i}$ 向 $i+n$ 连一条权值为 $p_{i}$ 的边，然后从 $i+n$ 向 $[a_{i},b_{i}]$ 连一条权值为 $0$ 的边。

建出反图后 $1 \to i$ 和 $n \to i$ 的路径集合会有重复统计的部分，不妨以 $dis_{1,i}+dis_{n,i}$ 作为初始值然后再进行一遍松弛操作（若没有重复部分就不需要松弛了）。

然后就是线段树优化建图板子了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct SMT_Q_BG
{
	ll id[900010],dis[2][900010],d[900010],vis[900010];
	vector<pair<ll,ll> >e[900010];
	ll lson(ll x)
	{
		return x*2;
	}
	ll rson(ll x)
	{
		return x*2+1;
	}
	void build(ll rt,ll l,ll r,ll n)
	{
		e[rt+n*4].push_back(make_pair(rt,0));
		if(l==r)
		{
			id[l]=rt;
			return;
		}
		e[lson(rt)].push_back(make_pair(rt,0));
		e[rson(rt)].push_back(make_pair(rt,0));
		e[rt+n*4].push_back(make_pair(lson(rt)+n*4,0));
		e[rt+n*4].push_back(make_pair(rson(rt)+n*4,0));
		ll mid=(l+r)/2;
		build(lson(rt),l,mid,n);
		build(rson(rt),mid+1,r,n);
	}
	void update(ll rt,ll l,ll r,ll x,ll y,ll pos,ll w,ll n)
	{
		if(x<=l&&r<=y)
		{
			e[rt].push_back(make_pair(pos+n*8,w));
			return;
		}
		ll mid=(l+r)/2;
		if(x<=mid)
		{
			update(lson(rt),l,mid,x,y,pos,w,n);
		}
		if(y>mid)
		{
			update(rson(rt),mid+1,r,x,y,pos,w,n);
		}
	}
	void dijkstra1(ll s,ll id)
	{
		memset(vis,0,sizeof(vis));
		memset(dis[id],0x3f,sizeof(dis[id]));
		priority_queue<pair<ll,ll> >q;
		dis[id][s]=0;
		q.push(make_pair(-dis[id][s],s));
		while(q.empty()==0)
		{
			ll x=q.top().second;
			q.pop();
			if(vis[x]==0)
			{
				vis[x]=1;
				for(ll i=0;i<e[x].size();i++)
				{
					if(dis[id][e[x][i].first]>dis[id][x]+e[x][i].second)
					{
						dis[id][e[x][i].first]=dis[id][x]+e[x][i].second;
						q.push(make_pair(-dis[id][e[x][i].first],e[x][i].first));
					}
				}
			}
		}
	}
	void dijkstra2(ll n,ll k)
	{
		memset(vis,0,sizeof(vis));
		priority_queue<pair<ll,ll> >q;
		for(ll i=1;i<=8*n+k;i++)
		{
			d[i]=dis[0][i]+dis[1][i];
			q.push(make_pair(-d[i],i));
		}
		while(q.empty()==0)
		{
			ll x=q.top().second;
			q.pop();
			if(vis[x]==0)
			{
				vis[x]=1;
				for(ll i=0;i<e[x].size();i++)
				{
					if(d[e[x][i].first]>d[x]+e[x][i].second)
					{
						d[e[x][i].first]=d[x]+e[x][i].second;
						q.push(make_pair(-d[e[x][i].first],e[x][i].first));
					}
				}
			}
		}
	}
}T;
int main()
{
	ll n,k,c,p,a,b,i;
	cin>>n>>k;
	T.build(1,1,n,n);
	for(i=1;i<=k;i++)
	{
		cin>>c>>p>>a>>b;
		T.e[i+n*8].push_back(make_pair(T.id[c]+n*4,p));
		T.update(1,1,n,a,b,i,0,n);
	}
	T.dijkstra1(T.id[1],0);
	T.dijkstra1(T.id[n],1);
	T.dijkstra2(n,k);
	for(i=1;i<=n;i++)
	{
		cout<<(T.d[T.id[i]]<1e15?T.d[T.id[i]]:-1)<<endl;
	}
	return 0;
}
```

---

