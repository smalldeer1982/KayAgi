# Reboot from Blue

## 题目背景

YSGHYYDS

## 题目描述

数轴上有 $n$ 个加油站，第 $i$ 个位于 $x_i$，油价是每升 $c_i$ 元。

YSGH 和他的车一开始位于坐标 $s$，它想去坐标 $t$（$s < t$），车的油箱一开始是空的，保证坐标 $s$ 有加油站。

假设车的油箱容量无限大，一升油能走距离 $1$。

他想知道他需要花费的最小费用。

## 说明/提示

**【样例解释】**

最优方案是在第一个加油站加 $1$ 升油到第二个加油站。

在第二个加油站加 $3$ 升油到第三个加油站。

在第三个加油站加 $3$ 升油到终点。

答案是 $10 + 2 \times 3 + 1 \times 3 = 19$。

---

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$1 \le n \le {10}^5$，$-{10}^9 \le x_i, s, t \le {10}^9$，$1 \le c_i \le {10}^9$，$s < t$，保证坐标 $s$ 有加油站。

- Subtask 1（10 points）：$n \le 20$。
- Subtask 2（30 points）：$n \le 5000$。
- Subtask 3（20 points）：$c_i$ 在 $[1, {10}^9]$ 中等概率随机。
- Subtask 4（40 points）：无特殊限制。

## 样例 #1

### 输入

```
3 5 10
10 5
2 4
1 7```

### 输出

```
19
```

# 题解

## 作者：Alarm5854 (赞：11)

这道题目看上去好像直接贪心就可以了，但是，其实在某些情况下，是可以走回头路的，所以就不能直接贪心求解了。

那么，怎么做呢？有一条显而易见的性质，就是不管是否走回头路，一定是一口气走到一个比这个点油价低的地方或走到终点，那么令终点有一个虚拟的加油站，油价为 $0$，这样就可以把终点和加油站一起进行处理了。

同时，也一定是恰好走到这个方向上离它最近的加油站，这个也非常容易证明。

根据这条性质，就能想到图论中的最短路——对于所有点，找左右两边各一个离它最近的点，其中这两个点的油价都低于该点的油价，往这两个点连边，长度为从这个点正好到达另一个点的耗费，如果没有，就不连。最多连 $2n$ 条边，可以用单调栈做到 $O(n)$ 。由于建成的图是有向无环图，所以只需用拓扑排序即可。

思路是这样的，然而有些细节需要注意：起始点所在的加油站必须要保证入度为 $0$，即遇到起始点就不让它进栈。在拓扑排序的时候，必须使所有入度为 $0$ 的点全部进队列，而不仅仅为起始点，否则 $0$ 分，原因就是一些无关的点也可能会往必要的点连边，使得这些必要的点入度永远不会减为 $0$，导致出错。

这样做总时间复杂度为 $O(n\log n)$，瓶颈在于排序（输入的坐标不保证有序）。

代码如下：

```cpp
#include<ctime>
#include<queue>
#include<cstdio>
#include<cctype>
#include<algorithm>
#define ll long long
using namespace std;
const ll N=2e5+7;
ll read(){
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while(isdigit(c)){
		x=x*10+f*(c-48);
		c=getchar();
	}
	return x;
}
struct pos{
	ll x,c;
	pos(ll a=0,ll b=0){
		x=a;
		c=b;
	}
	friend bool operator <(pos a,pos b){
		return a.x<b.x;
	}
};
struct edge{
	ll to,val,nxt;
	edge(ll a=0,ll b=0,ll c=0){
		to=a;
		val=b;
		nxt=c;
	}
};
pos p[N];
edge e[N];
ll top,st[N];
ll tot,head[N];
ll n,s,t,x,c,sx,tx,in[N],f[N];
void add(ll u,ll v,ll w){
	++in[v];
	e[++tot]=edge(v,w,head[u]);
	head[u]=tot;
}
void topo(){
	queue<ll>q;
	for(ll i=1;i<=n;++i){
		if(!in[i])
			q.push(i);
	}
	for(ll i=1;i<=n;++i)
		f[i]=5e18;//最大值可能会达到2e18
	f[sx]=0;//只有起始点的f值为0，其他均为正无穷
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		for(ll i=head[u];i;i=e[i].nxt){
			ll v=e[i].to;
			ll w=e[i].val;
			if(f[v]>f[u]+w)
				f[v]=f[u]+w;
			if(!--in[v])
				q.push(v);
		}
	}
}
int main(){
	n=read();
	s=read();
	t=read();
	for(ll i=1;i<=n;++i){
		c=read();
		x=read();
		p[i]=pos(x,c);
	}
	++n;
	p[n]=pos(t);
	sort(p+1,p+n+1);
	for(ll i=1;i<=n;++i){
		if(p[i].x==s)
			sx=i;
		if(p[i].x==t&&!p[i].c)
			tx=i;
	}
	for(ll i=1;i<=n;++i){
		while(top&&p[st[top]].c>=p[i].c){
			st[top]=0;
			--top;
		}
		if(top)
			add(i,st[top],(p[i].x-p[st[top]].x)*p[i].c);
		if(i^sx){//如果不为起始点，那么就使它进栈
			++top;
			st[top]=i;
		}
	}
	while(top){
		st[top]=0;
		--top;
	}
	for(ll i=n;i;--i){
		while(top&&p[st[top]].c>=p[i].c){
			st[top]=0;
			--top;
		}
		if(top)
			add(i,st[top],(p[st[top]].x-p[i].x)*p[i].c);
		if(i^sx){
			++top;
			st[top]=i;
		}
	}
	topo();
	printf("%lld",f[tx]);
	return 0;
}
```



---

## 作者：加藤惠 (赞：6)

### Solution 1

---

注意到每次加油的加油站的油价肯定是单调不减的。

于是我们考虑按油价给加油站排序，然后进行 DP。

令 $f_i$ 表示从 $s$ 到加油站 $i$ 的最小费用。

转移考虑枚举上一个加油站就行：
$$
f_i=\min_{j} (f_j+|x_i-x_j|\times c_j)
$$
注意到在起点左边的加油站从左边的加油站转移过来肯定不优，因为我们在达到当前加油站后就会开始加当前加油站的油，多跑的部分显然是浪费的，起点右边也是同理。

于是我们可以去掉转移中的绝对值符号，此时转移是一个关于 $x_i$ 的一次函数，可以用李超树维护。

时间复杂度 $O(n\log n)$。

&nbsp;

### Solution 2

---

每个加油站往左右第一个比油价他小的加油站连边，然后跑最短路。

时间复杂度 $O(n\log n)$。

---

## 作者：一念之间、、 (赞：5)

这里提供一个不同一点的做法

发现如果要更换油价，则我们一定是往**小**的换

所以我们按照油价从小到大排序，可以列出以下dp方程

$f[i]=min(f[j]+c[i]*\left | x[i]-x[j] \right |)$

表示从$i$开车去$j$，然后换上$j$的油价，初始值就是在$s$坐标的那个$f$是0，最后转移到$t$这个坐标结束。

然后我们可以$O(n^2)$进行dp，考虑对这个式子优化，用 `cdq` 维护$x$递增和$x$递减，两个式子是

当$x[i]>x[j]$

$f[i]=min(f[j]-c[i]*x[j])+c[i]* x[i]$

当$x[i]<x[j]$

$f[i]=min(f[j]+c[i]*x[j])-c[i]*x[i]$

发现是斜率优化的式子，但是x不递增，两种解决办法：1开`set`维护凸壳，2用李超线段树维护dp。

这里使用的是cdq+李超线段树，复杂度$O(n\log^2n)$

代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
int n,s,tt;
const int xx=1e5+5;
struct node
{
	ll pos,hf;
	int id;
	bool operator<(const node&w)const{return hf<w.hf;}
}e[xx*20];
ll f[xx];
bool cmp1(node a,node b){return a.pos<b.pos;}
bool cmp2(node a,node b){return a.pos>b.pos;}
bool cmp3(node a,node b){return a.id<b.id;}
struct nod
{
	ll k,b;
	int l,r;
}t[xx];
int cst,root;
ll js(ll x,ll k,ll b){return k*x+b;}
void insert(int &k,int l,int r,ll a,ll b)
{
	if(!k)return k=++cst,t[k].k=a,t[k].b=b,t[k].l=t[k].r=0,void();
	int mid=l+r>>1;
	if(a<=t[k].k)//维护区间最小值 
	{
		if(js(mid,a,b)<=js(mid,t[k].k,t[k].b))((l!=r)?insert(t[k].l,l,mid,t[k].k,t[k].b):void()),t[k].k=a,t[k].b=b;
		else ((l!=r)?insert(t[k].r,mid+1,r,a,b):void());
	}
	else 
	{
		if(js(mid,a,b)<=js(mid,t[k].k,t[k].b))((l!=r)?insert(t[k].r,mid+1,r,t[k].k,t[k].b):void()),t[k].k=a,t[k].b=b;
		else ((l!=r)?insert(t[k].l,l,mid,a,b):void());
	}
}
ll ans;
void ask(int k,int l,int r,int x)
{
	if(!k)return;
	ans=min(ans,js(x,t[k].k,t[k].b));
	int mid=l+r>>1;
	if(x<=mid)ask(t[k].l,l,mid,x);
	else ask(t[k].r,mid+1,r,x);
}
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);//cmp1是pos小到大，2是相反，3是id小到大 
	sort(e+l,e+mid+1,cmp1);
	sort(e+mid+1,e+r+1,cmp1);//现在是左边小于右边 
	int lpos=l;
	root=0;cst=0;
	for(int i=mid+1;i<=r;i++)
	{
		while(lpos<=mid&&e[lpos].pos<=e[i].pos)insert(root,1,1e9,-e[lpos].pos,f[e[lpos].id]),lpos++;//c的范围 
		ans=1e18;
		ask(root,1,1e9,e[i].hf);
		f[e[i].id]=min(f[e[i].id],ans+e[i].hf*e[i].pos);
	}
	sort(e+l,e+mid+1,cmp2);
	sort(e+mid+1,e+r+1,cmp2);//现在是左边小于右边 
	lpos=l;
	root=0;cst=0;
	for(int i=mid+1;i<=r;i++)
	{
		while(lpos<=mid&&e[lpos].pos>=e[i].pos)insert(root,1,1e9,e[lpos].pos,f[e[lpos].id]),lpos++;//c的范围 
		ans=1e18;
		ask(root,1,1e9,e[i].hf);
		f[e[i].id]=min(f[e[i].id],ans-e[i].hf*e[i].pos);
	}
	sort(e+l,e+r+1,cmp3);//排序回来 
	cdq(mid+1,r);
}
signed main(){
	n=read();
	s=read();
	tt=read();
	for(int i=1;i<=n;i++)
	{
		e[i].hf=read();
		e[i].pos=read();
	}
	memset(f,0x3f,sizeof(f));
	sort(e+1,e+n+1);
	f[0]=0;
	e[0].pos=tt;
	for(int i=1;i<=n;i++)e[i].id=i;
	cdq(0,n);
	for(int i=1;i<=n;i++)
	{
		if(e[i].pos==s)
		{
			cout<<f[i]<<"\n";
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：meyi (赞：4)

个人觉得这道题的部分分设置的很合理，现在把赛时我的思路分享一下。

## Subtask 1:

将终点看做一个油价为 $INF$，坐标为 $t$ 的加油站，每个加油站都向其他 $n$ 个加油站连边，从 $i$ 号加油站 到 $j$ 号加油站的边权为 $|x_i-x_j|\times c_i$，跑一遍最短路即可。

关键代码：

```cpp
int main(){
	//...
	a[++n]={inf,t};
	for(ri i=1;i<n;++i)
		for(ri j=1;j<=n;++j)
			if(i!=j)
				addedge(i,j,1ll*abs(a[i].x-a[j].x)*a[i].c);
	dijkstra();
	printf("%lld",dis[n]);
	return 0;
}
```

## Subtask 2:

注意到油价高的加油站只会向油价比自己低的加油站转移，因为若需要到油价比现在高的加油站买油，那么直接在现在的加油站买必定更优，于是可以按油价排序，然后 $O(n^2)$ dp，从 $i$ 号加油站 到 $j$ 号加油站的边权依然为为 $|x_i-x_j|\times c_i$。

关键代码：

```cpp
const int maxn=1e5+10;
struct node{
	int c,x;
	inline bool operator<(const node &k)const{
		return c>k.c;
	}
}a[maxn];
int n,s,st,t;
ll ans,f[maxn];
int main(){
	//...
	for(ri i=1;i<=n;++i)
		if(a[i].x==s)
        ans=1ll*abs(s-t)*a[i].c,st=i;
	swap(a[1],a[st]);
	sort(a+2,a+n+1);
	memset(f,0x3f,sizeof f);
	f[1]=0;
	for(ri i=2;i<=n;++i){
		for(ri j=1;j<i;++j)f[i]=min(f[i],f[j]+1ll*abs(a[i].x-a[j].x)*a[j].c);
		ans=min(ans,f[i]+1ll*abs(a[i].x-t)*a[i].c);
	}
	printf("%lld",ans);
	return 0;
}
```

## Subtask 3:

$c_i$ 完全随机，那么必定有很多加油站是无用的，我们并不会在这些加油站加油，考虑把这些加油站删去。

具体来说，我们将加油站按 $x$ 排序，对于所有 $x_i\ge s$，若存在 $j$ 使得 $s < x_j < x_i$ 且 $c_j < c_i$，那么我们显然不会在 $i$ 加油。因为在 $j$ 加更便宜。同理，对于所有 $x_i\le s$，若存在 $j$ 使得 $s > x_j > x_i$ 且 $c_j < c_i$，那么我们显然不会在 $i$ 加油。

删去所有上述的 $i$ 后，我们的程序已经可以通过随机数据。

关键代码：

```cpp
const int maxn=1e5+10;
struct node{
	int c,x;
	inline bool operator<(const node &k)const{
		return c>k.c;
	}
}a[maxn];
int n,s,t,tmp;
ll ans=LLONG_MAX,f[maxn];
int main(){
	//...
	sort(a+1,a+n+1);
	for(ri i=n,pos1=INT_MAX,pos2=INT_MIN;i;--i)
		if(a[i].x>s){
			if(pos1<=a[i].x)a[i]={0,0},++tmp;
			else pos1=a[i].x;
		}
		else{
			if(pos2>=a[i].x)a[i]={0,0},++tmp;
			else pos2=a[i].x;
		}
	sort(a+1,a+n+1);
	n-=tmp;
	memset(f,0x3f,sizeof f);
	ri i=1;
	while(a[i].x!=s)++i;
	f[i]=0;
	for(;i<=n;++i){
		for(ri j=i+1;j<=n;++j)f[j]=min(f[j],f[i]+1ll*abs(a[i].x-a[j].x)*a[i].c);
		ans=min(ans,f[i]+1ll*abs(a[i].x-t)*a[i].c);
	}
	printf("%lld",ans);
	return 0;
}
```

## Subtask 4 算法1:

考虑 Subtask 2 的式子，发现可以用李超线段树优化，读者可自行学习，然后即可通过本题。

由于代码除了李超线段树外和 Subtask 2 已贴出的代码基本一致，因此略去。

## Subtask 4 算法2：

经过 Subtask 3 的处理，我们现在剩余的加油站必定满足对于任意 $s<x_j<x_i$，有  $j<i$ 且 $c_j>c_i$；对于任意 $x_i<x_j<s$，有 $j>i$ 且 $c_j>c_i$。通俗易懂地讲，如果我们以 $x$ 为横坐标，以 $c$ 为纵坐标，将这些点绘制到二维平面上并依次连线，我们会发现，连出来的图形形成了一座以 $s$ 为最高点的“山峰”。考虑每个点从哪些点转移可能最优，不难发现，若转移点为 $j$，则 $j$ 只有可能是以 $s$ 为分界线的两侧满足 $c_j>c_i$ 且在该侧不存在 $c_j>c_k>c_i$ 的点 $k$。

于是对于每个点，我们只从上述可能最优的点向其连边，然后按拓扑序遍历并统计答案即可。

关键代码：

```cpp
const int maxn=1e5+10;
struct edge{
	int to,nxt;
}e[maxn<<1];
int deg[maxn],hd[maxn],len;
inline void addedge(int fr,int to){
	++deg[to];
	e[++len]={to,hd[fr]};
	hd[fr]=len;
}
struct node{
	int c,x,id;
	inline bool operator<(const node &k)const{
		return c>k.c;
	}
}a[maxn],b[maxn];
inline bool cmp(const node &a,const node &b){
	return a.x<b.x;
}
int n,s,t,tmp;
ll ans=LLONG_MAX,f[maxn];
int main(){
	scanf("%d%d%d",&n,&s,&t);
	for(ri i=1;i<=n;++i)scanf("%d%d",&a[i].c,&a[i].x),a[i].id=i,b[i]=a[i];
	sort(a+1,a+n+1);
	for(ri i=n,pos1=INT_MAX,pos2=INT_MIN;i;--i){
		if(a[i].x>=s){
			if(pos1<=a[i].x){a[i]={0,0,0},++tmp;continue;}
			else pos1=a[i].x;
		}
		if(a[i].x<=s){
			if(pos2>=a[i].x)a[i]={0,0,0},++tmp;
			else pos2=a[i].x;
		}
	}
	sort(a+1,a+n+1);
	n-=tmp;
	sort(a+1,a+n+1,cmp);
	ri pos=1;
	while(a[pos].x!=s)++pos;
	for(ri i=pos-1,j=pos;i;--i){
		addedge(a[i+1].id,a[i].id);
		while(j<=n&&a[i].c<=a[j].c)++j;
		if(j<=n)addedge(a[i].id,a[j].id);
	}
	for(ri i=pos+1,j=pos;i<=n;++i){
		addedge(a[i-1].id,a[i].id);
		while(j>0&&a[i].c<=a[j].c)--j;
		if(j>0)addedge(a[i].id,a[j].id);
	}
	memset(f,0x3f,sizeof f);
	f[a[pos].id]=0;
	queue<int>q;
	q.push(a[pos].id);
	while(q.size()){
		ri now=q.front();q.pop();
		ans=min(ans,f[now]+1ll*abs(b[now].x-t)*b[now].c);
		for(ri i=hd[now];i;i=e[i].nxt){
			ri nxt=e[i].to;
			f[nxt]=min(f[nxt],f[now]+1ll*abs(b[now].x-b[nxt].x)*b[now].c);
			if(!--deg[nxt])q.push(nxt);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Mysterious_Cat (赞：2)

### 题目思路：

将终点看作$c=0,x=t$的点，对于每个点$i$，找到前后离其最近的点$j$连边，满足$c_i < c_j$，然后单调栈优化 + 按拓扑排序遍历 dp 即可

**状态：**$dp_i$为$s$到点$i$的最小距离  
**转移方程：**$dp_i=\min_{0<j<i}\{dp_j+dis_{i,j} \times {c_j}\}$  
**初始化：**$dp_s=0$

### Code：

切记要开 QWQ (long long)

```cpp
#include<bits/stdc++.h>
#define QwQ int 
#define QWQ long long
using namespace std;

const QwQ NR = 1e5 + 5;

stack<QwQ> stk;

QwQ n, s, t, m, tot = 0, h[NR];
QWQ dp[NR];

struct Point
{
	QWQ c, x, from, to;
}p[NR];

struct Edge
{
	QwQ u, v, next;
	QWQ w;
}e[NR * 2];

bool cmp(Point a, Point b)
{
	return a.x < b.x || (a.x == b.x && a.c < b.c);
}

void add(QwQ x, QwQ y, QWQ z)
{
	if(y == s || x == t) return;
	p[x].to++, p[y].from++;
	tot++;
	e[tot].u = x, e[tot].v = y, e[tot].w = z;
	e[tot].next = h[x], h[x] = tot;
}

void topo()
{
	for(int i = 1; i <= n; i++)
	    dp[i] = 1e18;
	dp[s] = 0;
	queue<QwQ> q;
	for(QwQ i = 1; i <= n; i++)
		if(p[i].from == 0) q.push(i);
	while(!q.empty())
	{
		QwQ u = q.front(); q.pop();
		for(QwQ i = h[u]; i; i = e[i].next)
		{
			QwQ v = e[i].v;
			QWQ w = e[i].w;
			if(dp[u] != 1e18) dp[v] = min(dp[v], dp[u] + w);
			p[v].from--;
			if(!p[v].from) q.push(v);
		}
	}
}

QwQ main()
{
	scanf("%d %d %d", &n, &s, &t);
	for(QwQ i = 1; i <= n; i++)
		scanf("%lld %lld", &p[i].c, &p[i].x);
	n++;
	p[n].c = 0, p[n].x = t;
	sort(p + 1, p + n + 1, cmp);
	for(QwQ i = 1; i <= n; i++)
		if(p[i].x != p[m].x) p[++m] = p[i];
	n = m;
	for(QwQ i = 1; i <= n; i++)
		if(p[i].x == s) {s = i; break;}
	for(QwQ i = 1; i <= n; i++)
		if(p[i].x == t) {t = i; break;}
	for(QWQ i = 1; i <= n; i++)
	{
		while(!stk.empty() && p[stk.top()].c >= p[i].c)
		{
			add(stk.top(), i, (p[i].x - p[stk.top()].x) * p[stk.top()].c);
			stk.pop(); 
		} 
		if(!stk.empty()) add(i, stk.top(), (p[i].x - p[stk.top()].x) * p[i].c);
		stk.push(i);
	}
	topo();
	cout << dp[t]; 
	
	return 0;
}
```
吐槽：这万恶的QwQ啊（调了$n$遍才过） 

[**提交记录**](https://www.luogu.com.cn/record/list?user=384035&page=1&pid=P7480)

---

## 作者：一Iris一 (赞：2)

发现题解里面没有纯$cdq$做法，这里提供一下

首先把所有加油站按$c$排序，容易得到

$$f[i] = min(f[j] + c[i] *  ∣x[i]-x[j]|) $$

表示从$j\rightarrow i$的一次转移

f[i]表示$i\rightarrow End$的最小花费

显然复杂度是$O(n^2)$的，考虑优化

我开这个题的时候最先想到的是贪心算法 ， 后来觉得贪心可能会处理挺多细节，就开始换成$dp$思考

显然对贪心来说，如果i要转移的话，一定是向左右两边油价更低的地方转移，然后步步逼近$End$。

我们将这个贪心思想用到$dp$优化里面，对上面的方程来说要求$c$有序，然后我们现在还需要找与当前点最接近的$x$

于是我们优化$dp$的目标就已经转化为了如何实现这个二维偏序。

接下来的就很好说了吧，$cdq$维护二维偏序、$set+lower$_$boun$d维护凸包、李超线段树维护一次函数(~~你随便挑~~

这里用的是$cdq$维护二维偏序

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define INF 1ll<<30

template<typename _T>
inline void read(_T &x)
{
	x=0;char s=getchar();int f=1;
	while(s<'0'||s>'9') {f=1;if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	x*=f;
}

const int p=1e5+5;

struct gas{
	int c,x,id;
	friend bool operator<(gas a,gas b)
	{
		return a.c < b.c;
	}
}pos[p];
int f[p];

inline int dis(int i,int j)
{
	return abs(pos[i].x - pos[j].x);
}

inline bool cmp(gas A,gas B)
{
	return A.x < B.x;
}

inline void cdq(int l,int r)
{
	if(l == r) return ;
	int mid = l+r>>1;
	cdq(l,mid);
	sort(pos+l,pos+mid+1,cmp);
	for(int i=mid+1;i<=r;i++)
	{
		int pl = upper_bound(pos + l ,pos+mid+1,pos[i],cmp) - pos;
		if(pl == mid + 1)
		{
			pl -- ;
			f[pos[i].id] = min(f[pos[pl].id] +  abs(pos[pl].x - pos[i].x) *pos[i].c  , f[pos[i].id]);
		 }
		else
		{
			f[pos[i].id] = min(f[pos[pl].id] +  abs(pos[pl].x - pos[i].x) *pos[i].c  , f[pos[i].id]);
		 } 
		if(pl != 1)pl--;
		f[pos[i].id] = min(f[pos[pl].id] +  abs(pos[pl].x - pos[i].x) *pos[i].c  , f[pos[i].id]);
	}
	sort(pos+l,pos+mid+1);
	cdq(mid+1,r);
	return;
}

signed  main()
{
	int n,s,t;
	
	read(n);
	read(s);
	read(t); 
	for(int i=1,c,x;i<=n;i++)
	{
		read(c);
		read(x);
		pos[i].c = c;
		pos[i].x = x;
		pos[i].id = i;
	}
	pos[n+1].c = 0;
	pos[n+1].x = t;
	pos[n+1].id = n+1;
	memset(f,0x3f,sizeof(f));
	f[n+1] = 0;
	sort(pos+1,pos+2+n);
	cdq(1,n + 1);
	for(int i=1;i<=n + 1;i++)
	{
		if(pos[i].x == s)
		{
			cout<<f[pos[i].id];
			return 0;
		}
	}
 }


```

---

## 作者：绝顶我为峰 (赞：1)

看到这一题，首先有一个非常 naive 的做法是在每两个点之间连单向边，代表从一个点到另一个点，然后跑最短路。但是边数会达到 $O(n^2)$，无法通过。

考虑减少边的数量，注意到当我们从点 $i$ 走到点 $j$ 时，如果其中出现了花费比 $i$ 点更低的点 $k$，那么我们大可以先跑到 $k$ 再跑到 $j$，由此想到单调队列优化。

以 $s$ 为界，在左边右边分别建立单调队列，只有这上面的点才能成为中转站。建图时显然同一个单调队列内相同的点连边，$s$ 向左右单调队列队头连边。接下来考虑左右单调队列之间怎样连边，我们发现从 $s$ 的一边 $i$开到另一边 $j$ 时，中间所有大于 $i$ 花费的值全部可以跳过，所以我们可以在单调队列上二分，找到可以开到最远的加油站，并连边。

这样边数降到 $O(n)$，可以通过。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
#define int long long
struct node
{
    int c,x;
    bool operator <(const node &other) const
    {
        return x^other.x? x<other.x:c<other.c;
    }
}a[100001];
struct edge
{
    int nxt,to,weight;
}e[100001<<2];
int n,s,t,p,dis[100001],cnt,tot,h[100001];
bool vis[100001];
vector<pair<int,int> > q1,q2;
map<pair<int,int>,int> mp;
inline void add(int x,int y,int w)
{
    e[++tot].nxt=h[x];
    h[x]=tot;
    e[tot].to=y;
    e[tot].weight=w;
}
inline void dijkstra()
{
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,mp[make_pair(a[p].c,a[p].x)]));
    while(!q.empty())
    {
        pair<int,int> k=q.top();
        q.pop();
        if(vis[k.second])
            continue;
        vis[k.second]=1;
        dis[k.second]=k.first;
        for(register int i=h[k.second];i;i=e[i].nxt)
            if(!vis[e[i].to])
                q.push(make_pair(k.first+e[i].weight,e[i].to));
    }
}
signed main()
{
    scanf("%lld%lld%lld",&n,&s,&t);
    for(register int i=1;i<=n;++i)
        scanf("%lld%lld",&a[i].c,&a[i].x);
    a[++n].x=t+1;
    a[n].c=1ll<<30;
    sort(a+1,a+n+1);
    for(register int i=1;i<=n;++i)
    {
        if(a[i].x<s)
            continue;
        if(a[i].x==s)
            p=i;
        if(a[i].x>t)
            break;
        if(q2.empty()||q2.back().first>a[i].c)
        {
            mp[make_pair(a[i].c,a[i].x)]=++cnt;
            if(!q2.empty())
                add(mp[q2.back()],mp[make_pair(a[i].c,a[i].x)],q2.back().first*(a[i].x-q2.back().second));
            q2.push_back(make_pair(a[i].c,a[i].x));
        }
    }
    for(register int i=p-1;i>=1;--i)
        if(q1.empty()||min(q1.back().first,a[p].c)>a[i].c)
        {
            mp[make_pair(a[i].c,a[i].x)]=++cnt;
            if(!q1.empty())
                add(mp[q1.back()],mp[make_pair(a[i].c,a[i].x)],q1.back().first*(q1.back().second-a[i].x));
            q1.push_back(make_pair(a[i].c,a[i].x));
        }
    mp[make_pair(0,t)]=++cnt;
    add(mp[q2.back()],mp[make_pair(0,t)],q2.back().first*(t-q2.back().second));
    q2.push_back(make_pair(0,t));
    reverse(q2.begin(),q2.end());
    reverse(q1.begin(),q1.end());
    for(register int i=0;i<(int)q1.size();++i)
    {
        int it=lower_bound(q2.begin(),q2.end(),make_pair(q1[i].first,1ll<<30))-q2.begin()-1;
        if(it>=0&&it<(int)(q2.size()))
            add(mp[q1[i]],mp[q2[it]],q1[i].first*(q2[it].second-q1[i].second));
    }
    for(register int i=0;i<(int)q2.size();++i)
    {
        int it=lower_bound(q1.begin(),q1.end(),make_pair(q2[i].first,1ll<<30))-q1.begin()-1;
        if(it>=0&&it<(int)(q1.size()))
            add(mp[q2[i]],mp[q1[it]],q2[i].first*(q2[i].second-q1[it].second));
    }
    dijkstra();
    printf("%lld\n",dis[mp[make_pair(0,t)]]);
    return 0;
}
```


---

## 作者：QQH08 (赞：0)

首先这题有一个很显然的策略：每个点只可能去比它油价低的点。我们加一个点，油价为 $0$，坐标为终点。这样就把终点加进来。

所以考虑每个点第一个左边油价比它低的点，和第一个右边油价比它低的点，是它有可能到的点（注意可以回头走）。我们用一个栈分别计算左边和右边，每次把 $i$ 这个点和栈里的点比较，如果油价符合要求，就更新栈顶元素的数组，弹出。然后把 $i$ 也压入栈。（左边和右边差不多，注意顺序不一样，具体实现看代码）

现在我们有了左边和右边最优的位置，考虑建图。对于每一个点 $i$，我们把它和算出来的左边，右边的点连边。边权就是用 $i$ 这个点的油价乘上距离，也就是 $i$ 走到左边或右边的需要的费用。

最后就直接跑最短路算答案就可以啦。（注意最大值要设大一点，$10^{18}$ 也不够）

下面就是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
struct node{
	ll v,x;
}a[N];
int n,p,edgenum,head[N],Next[N*2],vet[N*2],sta[N],Nex[N],pre[N];
ll ss,t,ans=1e15,d[N],val[N*2];
bool vis[N];
priority_queue<pair<ll,int> > q;
bool cmp(node a,node b){
	if(a.x==b.x)return a.v<b.v;
	else return a.x<b.x;
}
void add(int u,int v,ll w){
	edgenum++;
	Next[edgenum]=head[u];
	vet[edgenum]=v;
	val[edgenum]=w;
	head[u]=edgenum;
}
void dij(int s){
    for(int i=1;i<=n;i++)d[i]=5e18;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
        if(vis[u])continue;
		vis[u]=1;
		for(int e=head[u];e;e=Next[e]){
			int v=vet[e];
			if(d[v]>d[u]+val[e]){
				d[v]=d[u]+val[e];
				if(!vis[v])q.push(make_pair(-d[v],v));
			}
		}
	}
}
int main(){
	scanf("%d%lld%lld",&n,&ss,&t);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].v,&a[i].x);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(a[i].x==ss){
			p=i;
			break;
		}
	int top=1;
	sta[top]=1;
	a[++n].v=0,a[n].x=t;
	for(int i=2;i<=n;i++){
		while(top>=1&&(a[i].v<a[sta[top]].v||a[i].v==0)){
			Nex[sta[top--]]=i;
		}
		sta[++top]=i;
	}
	top=1;
	sta[top]=n-1;
	for(int i=n-2;i>=1;i--){
		while(top>=1&&(a[i].v<a[sta[top]].v||a[i].v==0))pre[sta[top--]]=i;
		sta[++top]=i;
	}
	for(int i=1;i<n;i++){
		if(Nex[i]!=0)add(i,Nex[i],a[i].v*(a[Nex[i]].x-a[i].x));
		if(pre[i]!=0)add(i,pre[i],a[i].v*(a[i].x-a[pre[i]].x));
		// cout<<Nex[i]<<" "<<pre[i]<<"\n";
	}
	dij(p);
	// for(int i=1;i<=n;i++)cout<<d[i]<<" ";
	printf("%lld",d[n]);
	return 0;
}
```


---

## 作者：VicXF_ (赞：0)

### 线段树做法

还是先讲讲思路 ~~（其实其他题解都挺清楚的应该不用我废话）~~

* 一看这道题，第一个想法：连 $n^2$ 条边，然后最短路。->

 $O(n^2)$ ，显然过不了。

* 然后考虑优化：如果我们走到一个比自己油价更大的点，那不如直接到终点来得舒服，所以所有比自己油价大的都没必要连。

再考虑连油价小的时，**只需连左边第一个最小和右边第一个最小的**，所以即使再往左/右 有更小的，也会因为这个规则被其他点连上。

* 据此规则，终点的油价可以设为 $-1$ 。 **特别注意有两个测试点终点是有加油站的，可能导致没有点连向终点而挂掉。** 所以只需连完边后再让每个点向终点连一次边即可~ ~~你就是懒~~ 

#### 重点在于 ：

连边时我完全没有想到用什么单调栈之类的 $O(n)$ ，而是因为最近~~中了线段树的毒~~用线段树维护了。

$O(nlog^2n)$ 。 ~~幸好能过不然要疯~~

### 思路

维护一颗线段树和每一段的 $min$ 值，代表这一段加油站中最小油价的值。对于每一个加油站，都分别向左和向右搜索最近的最小值（若没有则返回 $-1$ ）然后连边。

**说起来容易 做起来WA。** 

直接上代码+注释（非常好理解啊~~bushi~~ 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define NN 200005
#define R read()
using namespace std;
inline ll R{ //快读
	ll x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

struct Tree{ 
	int l,r,min;
}t[NN<<2];

struct Edge{ 
	int head,to;
	ll next,wei;
}e[NN<<2];ll tot;

struct Point{
	ll c;
	int num;
	bool operator < (const Point &mo) const
	{
		return num<mo.num;
	}
}a[NN];

struct dij{
	int num;
	ll des;
	bool operator < (const dij &mo) const
	{
		return des>mo.des;
	}
}c,d;
priority_queue <dij> Q;
int vis[NN<<2];
ll des[NN<<2];

int n,st,tl;
int st1,tl1;

void build(int x,int l,int r){
	t[x].l=l;t[x].r=r;
	if(l==r)
	{
		if(a[l].num==st)
		{
			t[x].min=1e9+100;
			return;
		}
		t[x].min=a[l].c;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x].min=min(t[x<<1].min,t[x<<1|1].min);
	return;
}

void add(int u,int v,ll w){
	tot++;
	e[tot].to=v;
	e[tot].next=e[u].head;
	e[tot].wei=w;
	e[u].head=tot;
	return;
}

int serl(int x,int l,int r,int zhi)
{
	if(t[x].l==t[x].r) 
	{
		if(t[x].min<zhi) return t[x].l;
		else return -1;
	}
	
	int mid=(t[x].l+t[x].r)>>1;
	int l1=x<<1,r1=x<<1|1;
	
	if(l<=t[x].l&&t[x].r<=r)
	{
		if(t[r1].min<zhi) return serl(r1,l,r,zhi); //先搜右，保证是最近的
		if(t[l1].min<zhi) return serl(l1,l,r,zhi);
		return -1;
	}
	
	if(r<=mid) return serl(l1,l,r,zhi);
	if(mid<l) return serl(r1,l,r,zhi);	//这里左右无区别
	
	int mo=serl(r1,l,r,zhi); //先搜右
	if(mo>0) return mo;
	mo=serl(l1,l,r,zhi);
	if(mo>0) return mo;
	
	return -1;
}

int serr(int x,int l,int r,int zhi) //这里相反，先搜左
{
	if(t[x].l==t[x].r) 
	{
		if(t[x].min<zhi) return t[x].l;
		else return -1;
	}
	
	int mid=(t[x].l+t[x].r)>>1;
	int l1=x<<1,r1=x<<1|1;
	
	if(l<=t[x].l&&t[x].r<=r)
	{
		if(t[l1].min<zhi) return serr(l1,l,r,zhi);
		if(t[r1].min<zhi) return serr(r1,l,r,zhi);	
		return -1;
	}
	
	if(mid<l) return serr(r1,l,r,zhi);
	if(r<=mid) return serr(l1,l,r,zhi);
	
	int mo=serr(l1,l,r,zhi);
	if(mo>0) return mo;
	mo=serr(r1,l,r,zhi);
	if(mo>0) return mo;
	
	return -1;
}


signed main()
{
	bool f=true;
	n=R;st=R;tl=R;
	for(int i=1;i<=n;i++)
	{
		a[i].c=R;a[i].num=R;
		des[i]=3e18; 
		if(a[i].num==tl) //终点是加油站的情况
		{
			a[i].c=-1;
			f=false;
		}
	}
	if(f)
	{
		n++;
		a[n].c=-1;a[n].num=tl;des[n]=3e18; //把终点加入
	}
	
	sort(a+1,a+1+n);
	build(1,1,n);
	
	for(int i=1;i<=n;i++)
	{
		if(a[i].num==st) st1=i;
		if(a[i].num==tl) {tl1=i;continue;} //st1和tl1分别代表s和t在数组中的下标
		
		int mo=serl(1,1,i,a[i].c); //向左搜最近
		if(mo>0)add(i,mo,a[i].c*abs(a[i].num-a[mo].num));
		mo=serr(1,i,n,a[i].c); //向右搜最近
		if(mo>0)add(i,mo,a[i].c*abs(a[i].num-a[mo].num));
	}
	for(int i=1;i<=n;i++) //每个加油站向终点连边
	{
		if(i==tl1) continue;
		add(i,tl1,a[i].c*abs(a[i].num-a[tl1].num));
	}
    
	des[st1]=0;
	c.des=0;c.num=st1;
	Q.push(c);
	while(!Q.empty()) //dij，不多说
	{
		c=Q.top();Q.pop();
		if(vis[c.num]) continue;
		
		vis[c.num]=1;
		for(int i=e[c.num].head;i;i=e[i].next)
		{
			if(des[e[i].to]>des[c.num]+e[i].wei)
			{
				des[e[i].to]=des[c.num]+e[i].wei;
				d.des=des[e[i].to];d.num=e[i].to;
				Q.push(d);
			}
		}	
	}
	cout<<des[tl1];
	return 0;
}
```

事实证明线段树还是好骗分的QWQWQ。





---

