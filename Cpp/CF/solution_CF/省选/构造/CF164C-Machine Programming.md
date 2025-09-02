# Machine Programming

## 题目描述

有一家公司有 $k$ 台机器，并且有 $n$ 个任务需要完成，对于每一个任务我们知道它的开始时间 $s_i$ 和持续时间 $t_i$ ,并且完成这个任务后这家公司可以获利 $c_i$ 。每一台机器都可以处理任何任务，但不能同时处理多个任务，在处理某个任务时也不能切换到其他任务（即当某个机器处理任务 $i$ 时，在 $s_i$ 至 $s_i+t_i-1$ 时间段内就只能处理这个任务）。你需要选择一些任务来完成，使得总利润最大。

## 样例 #1

### 输入

```
3 1
2 7 5
1 3 3
4 1 3
```

### 输出

```
0 1 1
```

## 样例 #2

### 输入

```
5 2
1 5 4
1 4 5
1 3 2
4 1 2
5 6 1
```

### 输出

```
1 1 0 0 1
```

# 题解

## 作者：pythoner713 (赞：4)

网络流是解决此类任务分配问题的利器，一般会有如下套路：

1. 时间作为结点。

2. 资源量（本题机器数）作为容量。

3. 利润/消耗作为费用。

在本题中，对于每个任务，我们新建两个时间节点 $s_i$ 和 $s_i+t_i$ 代表起始时刻与终止时刻，并连一条容量为 $1$，费用为 $c_i$ 的单向边。这类边限制了每个任务最多只能交给一台机器做，并且做了可以得到 $c_i$ 的利润（对了，考虑到值域很大，$s_i,s_i+t_i$ 要离散化）。

除此之外，还要按照时间顺序，将所有相邻的时间节点连接起来。将这些边的容量都设置为 $k$，费用为 $0$。也就是说每时每刻机器数量不能超过 $k$，且闲置机器可以留到后面用，但不会得到利润。

现在我们把源点连向初始时间，最终时间连向汇点，跑最大费用最大流就可以了。输出方案时，只需要检查任务 $i$ 对应的边有没有流量流经，有的话说明该任务被选择了。

![](https://cdn.luogu.com.cn/upload/image_hosting/vuzme1xv.png)

上图是由样例 2 构建的网络，标注的 $(v,c)$ 代表此边容量为 $v$，费用为 $c$（但是还没离散化）。

```cpp
#include<bits/stdc++.h>
#define nb 2010
#define mb 10000
#define inf 1e9
using namespace std;

bool vis[nb];
int n, k, s[nb], t[nb], c[nb];
int S, T, cnt = 1, ans, money, tot, head[mb], _[mb], dis[nb];
struct edge{int to, next, val, cost, id;}e[mb];

void add_edge(int u, int v, int w, int c, int x){
	e[++cnt].to = v, e[cnt].val = w, e[cnt].cost =  c, e[cnt].next = head[u], head[u] = cnt, e[cnt].id = x;
	e[++cnt].to = u, e[cnt].val = 0, e[cnt].cost = -c, e[cnt].next = head[v], head[v] = cnt;
}

bool SPFA(){
	memset(dis, -1, sizeof(dis));
	dis[S] = 0, vis[S] = 1;
	queue<int> q;
	q.push(S);
	while(!q.empty()){
		int u = q.front();
		q.pop(), vis[u] = 0;
		for(int i = head[u]; i; i = e[i].next){
			int v = e[i].to;
			if(e[i].val && dis[v] < dis[u] + e[i].cost){
				dis[v] = dis[u] + e[i].cost;
				if(!vis[v]) q.push(v), vis[v] = 1;
			}
		}
	}
	return ~dis[T];
}

int DFS(int u, int in){
	if(u == T) return in;
	vis[u] = 1;
	int out = 0;
	for(int i = head[u]; i && out < in; i = e[i].next){
		int v = e[i].to;
		if(!vis[v] && e[i].val && dis[v] == dis[u] + e[i].cost){
			int res = DFS(v, min(e[i].val, in - out));
			if(res) money += res * e[i].cost, e[i].val -= res, e[i ^ 1].val += res, out += res;
		}
	}
	vis[u] = 0;
	return out;
}

int main(){
	ios::sync_with_stdio(0), cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> s[i] >> t[i] >> c[i];
		_[++tot] = s[i], _[++tot] = s[i] + t[i];
	}
	sort(_ + 1, _ + tot + 1);
	tot = unique(_ + 1, _ + tot + 1) - _ - 1, T = tot + 1;
	for(int i = 1; i <= n; i++){
		t[i] = lower_bound(_ + 1, _ + tot + 1, s[i] + t[i]) - _;
		s[i] = lower_bound(_ + 1, _ + tot + 1, s[i]) - _;
	}
	add_edge(S, 1, k, 0, -1), add_edge(tot, T, k, 0, -1);
	for(int i = 1; i < tot; i++) add_edge(i, i + 1, k, 0, -1);
	for(int i = 1; i <= n; i++) add_edge(s[i], t[i], 1, c[i], i);
	while(SPFA()) ans += DFS(S, inf);
	for(int i = 1; i <= n; i++){
		int u = s[i], v = t[i];
		for(int j = head[u]; j; j = e[j].next){
			if(e[j].id == i) cout << !e[j].val << " ";
		}
	}
	return 0;
}
```


---

## 作者：TanX_1e18 (赞：1)

对于这种数据范围小，限制多的题，大多都是网络流。

观察到要求获利最大，考虑费用流。

对于每个时间点，向下一个时间点连一条流量为 $k$，费用为 $0$ 的边，从源点向第一个时间点连流量为 $k$，费用为 $0$ 的边，最后一个点向汇点连流量为 $k$，费用为 $0$ 的边。

接下来对于每个任务，由起始时间到结束后的第一秒连一条流量为 $1$，费用为 $-c_i$ 的边，然后再跑费用流即可，输出方案时，一个任务对应的边流满了则选上。

注意，本题时间范围极大，需要离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
const int inf=1e9;
struct bian
{
    int to,lt,c,f,v;
}b[N*10];
int head[N*3],cur[N*3],top=1;
void mkb(int l,int r,int c,int v)
{
    b[++top]={r,head[l],c,0,v};
    head[l]=top;
    b[++top]={l,head[r],0,0,-v};
    head[r]=top;
}
int time_[N*3],tot;
int st[N],ed[N],val[N];
int n,k,ans;
int hao[N];
int S,T;
int dis[N*3],vis[N*3],dep[N*3];
queue<int>q;
bool SPFA()
{
    memset(dep,0,sizeof(dep));
    memcpy(cur,head,sizeof(head));
    memset(dis,0x3f,sizeof(dis));
    q.push(S);
    dis[S]=0;
    dep[S]=0;
    vis[S]=1;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        vis[x]=0;
        for(int t=head[x];t;t=b[t].lt)
        {
            int y=b[t].to;
            if(dis[y]>dis[x]+b[t].v&&b[t].c>b[t].f)
            {
                dep[y]=dep[x]+1;//由于边有费用为0的，一定要处理这个
                dis[y]=dis[x]+b[t].v;
                if(!vis[y])
                {
                    vis[y]=1;
                    q.push(y);
                }
            }
        }
    }
    return dis[T]<1e9;
}
int dfs(int x,int flow)
{
    if(x==T||flow==0)
    return flow;
    int now=0;
    for(int &t=cur[x];t;t=b[t].lt)
    {
        int y=b[t].to;
        if(dis[y]==dis[x]+b[t].v&&dep[y]==dep[x]+1&&b[t].c>b[t].f)
        {
            int d=dfs(y,min(flow-now,b[t].c-b[t].f));
            b[t].f+=d;
            b[t^1].f-=d;
            now+=d;
            if(now==flow)
            return now;
        }
    }
    return now;
}
void dinic()
{
    while(SPFA())while(dfs(S,inf));
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        int len;
        cin>>st[i]>>len>>val[i];
        ed[i]=st[i]+len;
        time_[++tot]=st[i];
        time_[++tot]=ed[i];
    }
    sort(time_+1,time_+tot+1);
    tot=unique(time_+1,time_+tot+1)-time_-1;
    S=tot+1;
    T=tot+2;
    mkb(S,0,k,0);
    for(int i=0;i<tot;i++)
    {
        mkb(i,i+1,k,0);
    }
    mkb(tot,T,k,0);
    for(int i=1;i<=n;i++)
    {
        hao[i]=top+1;
        mkb(lower_bound(time_+1,time_+tot+1,st[i])-time_,lower_bound(time_+1,time_+tot+1,ed[i])-time_,1,-val[i]);
    }
    dinic();
    for(int i=1;i<=n;i++)
    {
        cout<<((b[hao[i]].c-b[hao[i]].f)^1)<<' ';
    }//如果这条边流满了，则已选上。
    return 0;
}
```


---

## 作者：yuzhechuan (赞：1)

本题是网络流24题之一的[最长k可重区间集问题](https://www.luogu.com.cn/problem/P3358)的数据加强版，需要在那题的基础上优化建图复杂度

---

### 题解：

先考虑原先那题的建图方式，即拆点后两两暴力枚举区间$u$和$v$看看能否满足前后条件，能就连边$u'->v$，而拆开的两点之间的容量为区间长度

这样做边数是$n^2$级别的，$n=1000$时dinic很可能会爆炸

考虑优化

套路地，我们**先将区间按左端点排序**

因为我们知道如果现在用老方法连边的话肯定会连接编号为$[x,n]$的所有区间

由于都是向后拓展的，在两两暴力枚举时，我们只向满足条件的，且$l$最小的一个$x$连边

为了让后面的也都被连到，在预处理时需要额外连$n-1$条边，每条边$i$连接区间$i$和区间$i+1$

最后再像原来那题一样跑一边费用流后从残量网络上获知具体选择情况即可

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=2005,M=5e5+5;
int en=1,h[N],dis[N],mc,mf,n,k,show[N];
bool v[N];

struct seg{
	int l,r,w,i;
	inline bool operator < (const seg &nt) const {
		return l<nt.l;
	}
}a[N];

struct edge{
	int n,v,f,w;
}e[M<<1];

struct fafafa{
	int fa,id;
}pre[N];

void add(int x,int y,int f,int w){
	e[++en]=(edge){h[x],y,f,w};
	h[x]=en;
}

bool spfa(int s,int t){
	memset(v,0,sizeof v);
	memset(pre,0,sizeof pre);
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	v[s]=1;
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(e[i].f&&dis[x]+e[i].w<dis[y]){
				dis[y]=dis[x]+e[i].w;
				pre[y]=(fafafa){x,i};
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
		v[x]=0;
	}
	return dis[t]^0x3f3f3f3f;
}

void mcmf(int s,int t){
	while(spfa(s,t)){
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		mf+=flow;
		mc+=flow*dis[t];
	}
}

void exadd(int x,int y,int f,int w){
	add(x,y,f,w);
	add(y,x,0,-w);
}
//上面是模板
signed main(){
	read(n);read(k);
	for(int i=1;i<=n;i++){
		read(a[i].l);read(a[i].r);a[i].r=a[i].l+a[i].r-1;
		read(a[i].w);a[i].i=i; //基本信息
	}
	sort(a+1,a+1+n); //按左端点排序
	for(int i=1;i<=n;i++){
		exadd(i,i+n,1,-a[i].w); //拆点
		show[a[i].i]=en; //记录拆点中间连的是哪条边
		exadd(i+n,n*2+1,INT_MAX,0); //向汇点连表示这台机器工作结束
		if(i<n) exadd(i,i+1,INT_MAX,0); //向后连条边
		for(int j=i+1;j<=n;j++) if(a[i].r<a[j].l){ //找出第一个能与它连的区间
			exadd(i+n,j,INT_MAX,0);
			break;
		}
	}
	exadd(0,1,k,0); //给第一个点流量
	mcmf(0,n*2+1);
	for(int i=1;i<=n;i++) write(e[show[i]].f),putchar(' '); //看看是否被取
}
```

---

