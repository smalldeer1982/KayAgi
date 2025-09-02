# JOI 公園 (JOI Park)

## 题目描述

# 「JOI 2014/2015 决赛」JOI 公园

**译自 [JOI 2014/2015 决赛](https://www.ioi-jp.org/joi/2014/2015-ho/index.html) T3「[JOI 公園](https://www.ioi-jp.org/joi/2014/2015-ho/2015-ho.pdf)」**

时值 $ 20\text{XX} $ 年， IOI 国为了给办奥赛做准备，将要修缮 IOI 国中的 JOI 公园。 JOI 公园里有 $ N $ 个广场，这些广场从 $ 1 $ 到 $ N $ 编号。有 $ M $ 条道路连接各个广场，这些道路从 $ 1 $ 到 $ M $ 编号。第 $ i(1 \leq i \leq M) $ 条道路是一条连接第 $ A_i $ 和第 $ B_i $ 个广场的双向边，长度为 $ D_i $ 。任意两个广场间一定有道路（直接或间接）相连。

修缮计划如下：首先，选择一个**自然数**  $ X $ ，将和第一个广场距离等于 $ X $ 或在 $ X $ 以下的所有广场（含第一个广场）相互之间连结一条地下通道。广场 $ i $ 和广场 $ j $ 的距离指，从广场 $ i $ 到广场 $ j $ 经过的道路长度总和的最小值。定义 $ C $ 为一个与修筑地下通道花费有关的量（ $ C $ 是整数）。修筑所有地下通道的花费为 $ C\times X $ 。

接下来，撤去已经通过地下通道连接的广场之间的道路。撤去道路的花费不计。

最后，将没有被撤去的道路进行修补，长为 $ d $ 的道路修补的花费为 $ d $ 。

修缮计划实施之前， JOI 公园没有地下通道。请求出 JOI 公园修缮花费总和的最小值。

#### 任务
给出 JOI 公园的广场间道路的情况和 $ C $ 的值，请编写程序求出修缮 JOI 公园的花费总和的最小值。

## 说明/提示

对于输入样例 $1$， $ X=3 $ 也就是说，和广场 $ 1 $ 的距离在 $ 3 $ 或以下的广场（广场 $ 1 $ ，广场 $ 2 $ ，广场 $ 3 $ ）互相之间连接一条地下通道。修缮总花费为 $ 2\times 3+3+5=14 $ 。这就是最小值。
#### 输入样例 2
```plain
5 4 10
1 2 3
2 3 4
3 4 3
4 5 5
```
#### 输出样例 2
```plain
15
```
对于输入样例 $ 2 $ ，$ X=0 $ 时修缮总花费最小。
#### 输入样例 3
```plain
6 5 2
1 2 2
1 3 4
1 4 3
1 5 1
1 6 5
```
#### 输出样例 3
```plain
10
```
对于输入样例 $3$，$ X=5 $ 时所有广场相互间都会连接一条地下通道，此时修缮的花费最小。

对于 $ 15\% $ 的分值：
- $ N \leq 100 $
- $ M \leq 200 $
- $ C \leq 100 $
- $ D_i \leq 10 (1 \leq i \leq M) $

对于另 $ 45\% $ 的分值：
- $ N \leq 100 $
- $ M \leq 4000 $

对于 $ 100\% $ 的分值，所以输入数据满足以下条件：
- $ 2 \leq N \leq 10^5 $
- $ 1 \leq M \leq 2\times 10^5 $
- $ 1 \leq C \leq 10^5 $
- $ 1 \leq A_i,B_i \leq N (1 \leq i \leq M) $
- $ A_i\not = B_i (1 \leq i \leq M) $
- $ (A_i,B_i)\not =(A_j,B_j) $ 而且 $ (A_i,B_i)\not =(B_j,A_j) (1 \leq i\lt j \leq M) $
- $ 1 \leq D_i \leq 10^5 (1 \leq i \leq M) $
- 输入数据保证任意两个广场之间一定有道路连接（直接或间接）。

感谢@ミク 提供的翻译

## 样例 #1

### 输入

```
5 5 2
2 3 1
3 1 2
2 4 3
1 2 4
2 5 5```

### 输出

```
14```

## 样例 #2

### 输入

```
5 4 10
1 2 3
2 3 4
3 4 3
4 5 5```

### 输出

```
15```

## 样例 #3

### 输入

```
6 5 2
1 2 2
1 3 4
1 4 3
1 5 1
1 6 5```

### 输出

```
10```

# 题解

## 作者：ZAGER (赞：12)

## 题解

### 又是最爱的[透彻](https://www.cnblogs.com/ZAGER/p/9817918.html)

## 我的歪解

我首先想的是分治，我想二分肯定不行，因为它是没有单调性的。

我想了一下感觉它的大部分数据应该是有凸性的（例如$y=x^2$的函数图像)，所以可以三分。

下面是我的三分代码（骗了不少分）

三分模板没过的我居然瞎歪歪了一个三分



### 歪解code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
#define ll long long
#define R register
#define N 400005
#define INF 0x7fffffffffffLL
using namespace std;
template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}
ll n,m,c,tot,h[N],vis[N],pd[N];
ll dist[N],sum,now_ans,now;
struct bian{
	int u,v;
	ll w;
}b[N];
struct node{
	int nex,to;
	ll dis;
}edge[N<<1];
inline void add(R int u,R int v,R ll w){
	edge[++tot].nex=h[u];
	edge[tot].to=v;
	edge[tot].dis=w;
	h[u]=tot;
}
inline void spfa(R int s){
	for(R int i=1;i<=n;i++)dist[i]=INF;
	queue<int> q;q.push(s);dist[s]=0;vis[s]=1;
	while(!q.empty()){
		R int x=q.front();q.pop();vis[x]=0;
		for(R int i=h[x];i;i=edge[i].nex){
			R int xx=edge[i].to;
			if(dist[xx]>dist[x]+edge[i].dis){
				dist[xx]=dist[x]+edge[i].dis;
				if(!vis[xx]){
					vis[xx]=1;
					q.push(xx);
				}
			}
		}	
	}
}
inline ll check(R ll mid){
	ll tot=0;
	for(R int i=1;i<=n;i++)pd[i]=0;
	for(R int i=1;i<=n;i++)
		if(dist[i]<=mid)pd[i]=1;
	for(R int i=1;i<=m;i++)
		if(pd[b[i].u]&&pd[b[i].v])
			tot+=b[i].w;
	return tot-mid*c;//这是你能节省的
}
int main(){ 
	read(n);read(m);read(c);
	for(R int i=1;i<=m;i++){
		read(b[i].u);read(b[i].v);read(b[i].w);
		add(b[i].u,b[i].v,b[i].w);add(b[i].v,b[i].u,b[i].w);sum+=b[i].w;
	}
	spfa(1);
	R ll l=0,r=sum;
	while(l<=r){
		R ll tmp=(r-l)/3;
		R ll mid1=l+tmp;
		R ll mid2=r-tmp;
		if(check(mid1)>check(mid2)) r=mid2-1;
		else l=mid1+1;
	}
	ll tmp=check(l),temp=check(r);
	if(tmp>temp)now=l,now_ans=tmp;
	else now=r,now_ans=temp;
	printf("%lld\n",sum-now_ans);
    return 0;
}
```

当然了，三分本来就是一个非常好的骗分算法（也会是正解），有些题在加一些暴力，一定会有神奇的效果；

讲课老师说加上暴力这道题应该可以$A$掉,但懒惰的我并没有去实践，有兴趣的可以试一试；



## 正解

这其实是一道经典的最短路的一种题型。

先跑一遍$SPFA$，处理出$dist$数组；

然后再利用$dist$数组处理出每一条边的$maxdis$;

将$maxdis$数组从小到大排序（结构体排序）；

![](https://i.loli.net/2018/10/21/5bcc587c46b71.png)



看完图应该都懂了吧。

### code:

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
#define ll long long
#define R register
#define N 800005
#define int long long
#define INF 9999999999999999LL
using namespace std;
template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}
ll n,m,c,tot,h[N],vis[N],pd[N],maxdis[N];
ll dist[N],sum,ans,maxsum;
struct bian{
	int u,v,w; 
}b[N];
struct node{
	int nex,to,dis;
}edge[N<<1];
struct MAX{
	int maxdis,id;
	friend bool operator < (const MAX &a,const MAX &b){
		return a.maxdis<b.maxdis;
	}
}md[N];
inline void add(R int u,R int v,R int w){
	edge[++tot].nex=h[u];
	edge[tot].to=v;
	edge[tot].dis=w;
	h[u]=tot;
}
inline void spfa(R int s){
	for(R int i=1;i<=n;i++)dist[i]=INF;
	queue<int> q;q.push(s);dist[s]=0;vis[s]=1;
	while(!q.empty()){
		R int x=q.front();q.pop();vis[x]=0;
		for(R int i=h[x];i;i=edge[i].nex){
			R int xx=edge[i].to;
			if(dist[xx]>dist[x]+edge[i].dis){
				dist[xx]=dist[x]+edge[i].dis;
				if(!vis[xx]){
					vis[xx]=1;
					q.push(xx);
				}
			}
		}	
	}
}
signed main(){ 
	read(n);read(m);read(c);
	for(R int i=1;i<=m;i++){
		read(b[i].u);read(b[i].v);read(b[i].w);
		add(b[i].u,b[i].v,b[i].w);add(b[i].v,b[i].u,b[i].w);sum+=b[i].w;
	}
	spfa(1);
	for(R int i=1;i<=m;i++)
		md[i].maxdis=max(dist[b[i].u],dist[b[i].v]),md[i].id=i;
	sort(md+1,md+1+m);
	ans=sum;
	for(R int i=1;i<=m;i++){
		sum-=b[md[i].id].w;
		ans=min(ans,1LL*md[i].maxdis*c+sum);
	}
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：bellmanford (赞：3)

作为学校模拟赛的第一题，这题十分简单

赛后搜了一下题，这题竟然是黑题

~~不会是恶意评分吧~~

好了说思路，先跑一遍 SPFA （由于数据水，并不卡 SPFA ，所以不用 Dijkstra+斐波那契堆优化）

得到每个点到 1 号点的距离后，从小到大排序一遍，这时便可以枚举每个点到 1 号点的距离修筑地下隧道，答案取最小值 

至于撤去的道路的花费，预处理一下就行了

代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

#define OPTIMIZE ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define In inline
#define Re register
#define db double
#define int long long
const int M=1e5+5;

int n,m,c,sum=0,ans=1e18;
int tot=0,first[M];
bool vis[M],book[M];
struct Edge{
	int nxt,to,val;
	bool bj;
}e[M<<2];
struct node{
	int num,dis,pre;
}d[M];
queue<int> Q;

int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}

int cmp(node x,node y){
	return x.dis<y.dis;
}

void add(int x,int y,int z){
	tot++;
	e[tot].nxt=first[x];
	first[x]=tot;
	e[tot].to=y;
	e[tot].val=z;
}

void spfa(){
	for(int i=1;i<=n;i++){
		d[i].num=i;
		d[i].dis=1e18;
		d[i].pre=0;
	}
	Q.push(1);
	d[1].dis=0;
	vis[1]=1;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		vis[u]=0;
		for(int i=first[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].val;
			if(d[v].dis>d[u].dis+w){
				d[v].dis=d[u].dis+w;
				if(!vis[v]){
					Q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}

signed main(){
	n=read(),m=read(),c=read();
	for(int i=1;i<=m;i++){
		int a=read(),b=read(),d=read();
		add(a,b,d);
		add(b,a,d);
		sum+=d;
	}
	spfa();
	sort(d+1,d+n+1,cmp);
	for(int i=1;i<=n;i++){
		d[i].pre=d[i-1].pre;
		book[d[i].num]=1;
		for(int j=first[d[i].num];j;j=e[j].nxt){
			int v=e[j].to,w=e[j].val;
			if(!e[j].bj&&book[v]){
				e[j].bj=1;
				d[i].pre+=w;
			}
		}
	}
	for(int i=1;i<=n;i++){
//		printf("%lld %lld %lld\n",d[i].num,d[i].dis,d[i].pre);
		ans=min(ans,d[i].dis*c+sum-d[i].pre);
	}
	printf("%lld\n",ans);
}
```


---

## 作者：Rusalka (赞：2)

原题链接：[AT2434 JOI 公園 (JOI Park)](https://www.luogu.com.cn/problem/AT2434)

~~写完之后看到题解区的三分吓了一跳~~

### 分析与解答

由于最终答案与边权有关，所以不妨考虑判断一条边是否会对答案有贡献。

记 $dis$ 表示以点 $1$ 为源点的最短路径长度，那么答案可以表示为 $X \times C + \sum\limits_{i=1}^{m} d_i\ [\max(dis_{a_i}, dis_{b_i}) \gt X]$，也就是说只有当一条道路两端点的最短路长度**均大于**当前 $X$ 时，这条道路的才会对答案有贡献。

这一点是可以根据题目描述得到的。

然后注意到一个事实：虽然题目中说 $X$ 可以取任意自然数，但是显然 $X$ 取以点 $1$ 为源点的一条最短路径长度时最优。~~显然易证·~~也就是说枚举 $X$ 的值时只需要枚举 $dis$ 数组即可。

所以我们只需要求出以点 $1$ 为源点的最短路径长度，然后求出每一条边想要被计入答案所需要的最小 $X$ 值，记为 $val$，即 $\max(dis_{a_i}, dis_{b_i})$，然后按照该值对边排序，最后按照枚举当前 $val$ 计算答案即可。

形象地说，就是在对边进行排序只后，选用一条边 $i$ 作为“分界点”，所有 $val_j \gt val_i$ 的边 $j$ 的边权都会计入答案，其他则不会。

记得开 `long long` 。

这里运用堆优化的 Dijkstra 算法求最短路，时间复杂度 $\Theta(n \log n)$

### Code

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<long long,int> pli;
const int MAXN = 100010;
const int MAXM = 200010;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, c;

struct edge1{
	int u, v, w;
	ll val; int ind;
	bool operator<(const edge1 &o)const{return val < o.val;} 
}a[MAXM];
struct edge{
	int ne, to, w;
	edge(int N=0,int T=0,int W=0):ne(N),to(T),w(W){}
}e[MAXM<<1];
int fir[MAXN], num = 0;
inline void join(int a, int b, int c)
{
	e[++num] = edge(fir[a], b, c);
	fir[a] = num;
}

ll dis[MAXN];
bool vis[MAXN];
priority_queue<pli,vector<pli>,greater<pli> > h;

inline void dijkstra(int s = 1)
{
	for(int i=1;i<=n;i++)
		dis[i] = INF, vis[i] = 0;
	dis[s] = 0;
	h.push(make_pair(dis[s], s));
	while(!h.empty())
	{
		int u = h.top().second;
		h.pop();
		vis[u] = 1;
		for(int i=fir[u];i;i=e[i].ne)
		{
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].w)
			{
				dis[v] = dis[u] + e[i].w;
				if(!vis[v]) h.push(make_pair(dis[v], v));
			}
		} 
	}
}

int main()
{
	ll sum = 0, ans = 0;
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].w);
		join(a[i].u, a[i].v, a[i].w);
		join(a[i].v, a[i].u, a[i].w);
		a[i].ind = i;
		sum += a[i].w;
	}
	ans = sum;
	dijkstra(1); // 求最短路
	for(int i=1;i<=m;i++)
		a[i].val = max(dis[a[i].u], dis[a[i].v]);
	sort(a+1, a+m+1);
	for(int i=1;i<=m;i++)
	{
		sum -= a[i].w;
		ans = min(ans, sum+1ll*a[i].val*c);
        // 枚举以一条边为分界点时的答案
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：iPhoneSX (赞：1)

# 题解
### 思路
很容易想到要先求最短路，我写的 SPFA，然后把存储每个节点到 $1$ 号节点距离的 dis 数组从小到大排序。显然题目中要求的 $x$ 只可能等于 $0$，或者是 dis 数组中的值。于是我们从小到大遍历排序后 dis 数组，每遍历到一个点就标记一下，表示这个点已经被连上地下通道了。设置一个变量 $sum$，初始值为所有的边权和，后面遍历时每到一个 $x$ 就让 $sum$ 加上 $c \times x$，再减去与当前节点相连的所有已经打上标记的点之间的边权。因为是按照到 $1$ 号节点的距离从小到大遍历，所以不会有边被减去多次。时间复杂度 $O(N+M)$。
### 代码
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f3f3f3f3f
#define mod 1000000007
#define N 400005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,m,c,x,y,z,head[N],ver[N],Next[N],w[N],vis[N],tot=-1;
ll dis[N],sum,ans;
struct node{
	int id;
	ll d;
}a[N];
bool cmp(node x,node y){
	return x.d<y.d;
}
void add(int x,int y,int z){
	ver[++tot]=y;
	w[tot]=z;
	Next[tot]=head[x];
	head[x]=tot;
}
void SPFA(int u){
	memset(vis,0,sizeof vis);
	memset(dis,inf,sizeof dis);
	vis[u]=1;
	dis[u]=0;
	queue<int> q;
	q.push(u);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i!=-1;i=Next[i]){
			int v=ver[i];
			if(dis[x]+w[i]<dis[v]){
				dis[v]=dis[x]+w[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	for(int i=2;i<=n;i++){
		a[i-1].d=dis[i];
		a[i-1].id=i;
	}
	sort(a+1,a+n,cmp);
	return;
}
signed main(){
	memset(head,-1,sizeof head);
	read(n,m,c);
	for(int i=1;i<=m;i++){
		read(x,y,z);
		add(x,y,z);
		add(y,x,z);
		sum=sum+z;
	}
	ans=sum;
	SPFA(1);
	vis[1]=1;
	for(int i=1;i<=n-1;i++){
		sum+=c*(a[i].d-a[i-1].d);
		vis[a[i].id]=1;
		for(int j=head[a[i].id];j!=-1;j=Next[j]){
			int v=ver[j];
			if(vis[v]){
				sum-=w[j];
			}
		}
		ans=min(ans,sum);
	}
	write(ans);
	putchar('\n');
	return 0;
}
`````

---

## 作者：Linge_Zzzz (赞：1)

题意不再赘述。

容易发现这题其实是让你选出一个距离 $X$ 来确定图上的一块区域，最小化 这个区域不包含的边的边权和 与 $X\times C$ 的和。

根据贪心，不难想到这个 $X$ 一定是某个节点到 $1$ 的距离。所以我们考虑从小到大枚举 $1$ 到每个节点的距离作为 $X$。

现在我们考虑如何对于一个 $X$ 计算这个区域不包含的边的边权和，我们可以使用所有边权的总和来减去这个区域完全包含的边的边权。

那么如何统计区域完全包含的边的边权呢？把这个值记为 $v$，开一个辅助数组 $d_u$，当我们把 $u$ 加入到这个区域里的时候，让 $v$ 减去 $d_u$，然后让所有与 $u$ 相连的边 $(u,v,w)$ 的 $d_v$ 加上 $w$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
const int INFL=0x3f3f3f3f3f3f3f3f;
struct edge{
	int v,w,nxt;
}e[N*2];
int head[N],cnt=2;
void add(int u,int v,int w){
	e[cnt].v=v,e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
}
int n,m,c;
int sm[N],sum,ans=INFL;
int dis[N];
bool vis[N];
typedef pair<int,int> pii;
#define fi first
#define se second
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pii> q;
	q.push(make_pair(0,1));
	dis[1]=0;
	while(q.size()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			if(dis[u]+e[i].w<dis[e[i].v]){
				dis[e[i].v]=dis[u]+e[i].w;
				q.push(make_pair(-dis[e[i].v],e[i].v));
			}
		}
	}
}
pii p[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>c;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
		sum+=w;
	}
	Dijkstra();
	for(int i=1;i<=n;i++)p[i].fi=dis[i],p[i].se=i;
	sort(p+1,p+1+n);
	int lst=0;
	for(int i=1;i<=n;i++){
		int u=p[i].se,d=p[i].fi;
		if(d!=lst||lst==0){
			ans=min(ans,sum+lst*c);
			lst=d;
		}
		sum-=sm[u];
		for(int i=head[u];i;i=e[i].nxt)sm[e[i].v]+=e[i].w;
	}
	ans=min(ans,sum+lst*c);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：cjh20090318 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_joi2015ho_c)。

## 题意

城市中有 $N$ 个公园，编号 $1\sim N$，有 $M$ 条双向道路将 $N$ 个公园连通，第 $i$ 条道路连接公园 $x_i,y_i$，长度为 $d_i$，使得任何两个公园之间都能直接或间接到达。

现在计划对公园的道路进行改造：

- 你可以选择一个自然数 $X$，将第 $1$ 个公园到其他公园最短路小于等于 $X$ 的都修建一条地下通道，费用为 $X\times C$，$C$ 是给定的一个整数。
- 接下来，将通过地下通道连接的公园之间的道路删除，即 $x,y$ 都和 $1$ 有地下通道，删除 $x,y$ 的道路。
- 对于剩下的道路，长度为 $k$ 的道路，维护的费用是 $k$。

初始时，没有地下通道，你需要输出改造的最小总费用。

## 分析

首先用优先队列优化的 Dijkstra 算法求出第 $1$ 个公园到其他所有公园的最短路。

直接枚举 $X$ 一定是不可行的，观察到 $X$ 一定是 $1$ 到其中一个点的最短路值，否则会产生多余的花费，因此枚举时间复杂度是 $O(N)$。

对于每一个 $X$ 单独删边的时间复杂度为 $O(NM)$，但是随着 $X$ 的增大，能修地下通道的点就越多，边就删除的越多，剩下维护的边权和就越小。

所以提前对可行的 $X$ 进行排序，每次新加入一个点就将其原来所有连了地下通道的边全部删掉，每条边至多访问两次，时间复杂度 $O(N+M)$。

总体时间复杂度 $O(M \log N)$，瓶颈在于单源最短路和对可行 $X$ 值的排序。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<utility>
#include<vector>
#define MAXN 100005
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,int> PLI;
int n,m,c;
vector<PII> G[MAXN];
LL dis[MAXN];
bool vis[MAXN];
void dj(const int S){//Dijkstra 算法求单源最短路。
	memset(dis,0x3f,sizeof(LL)*(n+1));
	priority_queue<PLI,vector<PLI>,greater<PLI> > Q;
	Q.emplace(dis[S]=0,S);
	for(int u;!Q.empty();){
		u=Q.top().second;Q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(const PII&V:G[u])if(dis[u]+V.second<dis[V.first])
			Q.emplace(dis[V.first]=dis[u]+V.second,V.first);
	}
}
int p[MAXN];
bool cmp(const int x,const int y){return dis[x]<dis[y];}//按照最短路大小排序。
bool S[MAXN];
int main(){
	scanf("%d%d%d",&n,&m,&c);
	LL ds=0;//边权和。
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),G[u].emplace_back(v,w),G[v].emplace_back(u,w),ds+=w;
	dj(1);
	for(int i=1;i<n;i++) p[i]=i+1;
	sort(p+1,p+n,cmp);
	LL ans=ds;//X=0，不需要建立任何地下通道，答案即为边权和。
	S[1]=1;
	for(int j=1;j<n;++j){
		LL s=dis[p[j]];
		for(const PII&V:G[p[j]])if(S[V.first]) ds-=V.second;//删去原来有地下通道的点的连边。
		S[p[j]]=1;//将当前点加入地下通道联通的点集合。
		ans=min(ans,ds+s*c);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：SmileMask (赞：1)


# 题意
- 给定无重边无自环有边权的无向连通图，可以选择自然数 $x$，与 1 号节点距离小于等于 $x$ 的节点，花费 $x \times c$ 互相建地道；其他的边要修缮，花费 $\Sigma_{e \subseteq E} e.w$（若边的两边的点都修了地道，则不加），最小化花费。

# 题解

首先我们先跑一遍最短路，然后每个点到 1 的距离排序，我们根据距离重新标号。

考虑枚举每一条边，令 $u,v$ 为边所连接的点，如果 $u$ 的新标号大于 $v$ 的新标号，那这条边的贡献就算到 $u$ 的新标号上，反之同理。
 
考虑令 $sum$ 为每个标号的贡献，做一遍后缀和，统计时枚举最短路距离，贡献为 $dis_u \times c+sum_{u+1}$。

# 代码

```
#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second
#define int long long
using namespace std;

inline int rd(){
	int num=0,sign=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-'){sign=-1;}ch=getchar();}
	while(isdigit(ch)) num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
	return num*sign;
}

const int N=1e5+10;
const int inf=3e10;

vector <PII> G[N];
int n,m,C,dis[N];
int idx[N];
bool vis[N];
PII vec[N];
int sum[N];

struct edge{
	int u,v,w;
};

vector <edge> E;

void Dij(){
	priority_queue <PII,vector<PII>,greater<PII>> q;
	memset(dis,0x3f,sizeof dis);
	dis[1]=0,q.push({0,1});
	while(q.size()){
		int u=q.top().se;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto e:G[u]){
			int v=e.fi,w=e.se;
			if(dis[v]>dis[u]+w)
				dis[v]=dis[u]+w,q.push({dis[v],v});
		}
	}
}

bool cmp(PII x,PII y){
	return x.fi<y.fi;
}

signed main(){
	// freopen("park.in","r",stdin);
	// freopen("park.out","w",stdout);
	n=rd(),m=rd(),C=rd();
	for(int i=1;i<=m;i++){
		int u=rd(),v=rd(),w=rd();
		G[u].push_back({v,w});
		G[v].push_back({u,w});
		E.push_back({u,v,w});
	}
	Dij();
	for(int i=1;i<=n;i++)
		vec[i]={dis[i],i};
	sort(vec+1,vec+n+1,cmp);
	for(int i=1;i<=n;i++)
		idx[vec[i].se]=i;
	for(auto e:E){
		int u=e.u,v=e.v,w=e.w;
		sum[max(idx[u],idx[v])]+=w;
	}
	for(int i=n;i>=1;i--)
		sum[i]+=sum[i+1];
	int ans=1e18;
	for(int i=1;i<=n;i++)
		ans=min(ans,C*vec[i].fi+sum[i+1]);	
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：vanueber (赞：0)

模拟赛签到题。

# 题目大意

给定 $n$ 个节点 $m$ 条边的无向图和一个值 $V$，可以选取一个值 $c$，代价是将所有 $1$ 为起点的单源最短路小于 $c$ 的点之间的边除外，所有边的权值和加上 $c\times V$，求最小代价。

# 分析

先 dijkstra 跑一遍最短路，然后直接模拟。

先枚举 $c$，不难发现不需要连续地枚举 $c$，只需要离散地枚举所有 $dis_i$ 即可，因为卡在中间只会有多余的贡献，下调 $c$ 值一定更优，故枚举复杂度是 $\Theta(n)$ 的。

接下来考虑如何计算每个 $c$ 值下的 $\sum w$，使用二元组记录所有 $(dis_v,v)$ 然后排序，然后按照顺序依次开放节点并枚举这个点能到的边，要是能到就移除该边的贡献，最后动态更新答案即可。

# Code


```cpp
#include <bits/stdc++.h>
#define int long long
#define umap unordered_map
#define vint vector<int>
#define ll long long
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
const int INF=0x3f3f3f3f3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=3e5+10,M=2e5+10;
int n,m,V;
struct node
{
    int v,w;
    node(int v=0,int w=0):v(v),w(w){}
    bool operator <(const node &b)const
    {
        return w>b.w;
    }
};
vector<node> G[N];
int dis[N],vis[N];
node pre[N];
int all_cost;
vint dist;
void dijkstra()
{
    priority_queue<node> Q;
    fill(dis,dis+n+1,INF);
    memset(dis,0x3f,sizeof dis);
    Q.push({1,0}),dis[1]=0;
    while(!Q.empty())
    {
        int u=Q.top().v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(node &k:G[u])
        {
            int v=k.v,w=k.w;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                pre[v]={u,w};
                Q.push({v,dis[v]});
            }
        }
    }
}
struct state
{
    int u,dis;
    bool operator <(const state &b)const
    {
        return dis<b.dis;
    }
};
int ans=INF;
vector<state> res;
map<pii,int> book;
unordered_map<int,int> tag,reach;
pii my_mp(int u,int v)
{
    return make_pair(min(u,v),max(u,v));
}
signed main()
{
    // freopen("in.txt","r",stdin);
    cin>>n>>m>>V;
    for(int i=1,u,v,w;i<=m;++i)
    {
        u=read(),v=read(),w=read();
        G[u].push_back({v,w});
        G[v].push_back({u,w});
        all_cost+=w;
    }
    dijkstra();
    for(int u=1;u<=n;++u)
    {
        res.push_back({u,dis[u]});
    }
    sort(all(res));
    ans=all_cost;
    for(auto i:res)
    {
        auto [u,dis]=i;
        reach[u]=1;
        for(auto k:G[u])
        {
            if(reach[k.v])
            {
                all_cost-=k.w;
            }
        }
        ans=min(ans,all_cost+dis*V);
    }
    cout<<ans<<endl;
    return 0;
}
/*
5 5 2
2 3 1
3 1 2
2 4 3
1 2 4
2 5 5
*/
/*
2 1 66
2 1 7

5 4 10
1 2 3
2 3 4
3 4 3
4 5 5

6 5 2
1 2 2
1 3 4
1 4 3
1 5 1
1 6 5
*/

```

---

## 作者：abensyl (赞：0)

原题：[AT_joi2015ho_c JOI 公園 (JOI Park)](https://www.luogu.com.cn/problem/AT_joi2015ho_c)。

## 思路

显然应该先把最短路径求出来。

按照最短路径从小到大排序，考虑最短路前 $i$ 小的使用地下通道相连，第 $i+1$ 小至第 $n$ 小进行道路修复。

不妨设 $cur_i$ 为前 $i$ 小的使用地下通道相连，第 $i+1$ 小至第 $n$ 小进行道路修复的花费。

最终答案即为 $\min\limits_{i\in[0,n]} cur_i$，具体实现方法简单。

一开始全部修复道路，$cur_0=\sum d_i$，然后依次枚举 $i$，$cur_i$ 就等于 $cur_{i-1}$ 减去最短路第 $i$ 小的点与最短路前 $i$ 小的点之间的所有边的边权。

时间复杂度 $O((n+m)\log n)$。

[代码 + 我的 AC 记录](https://atcoder.jp/contests/joi2015ho/submissions/60103724)。

---

## 作者：makerlife (赞：0)

[更好的阅读体验](https://blog.makerlife.top/post/uncategorized-problems/#AT-joi2015ho-c-JOI-Park) | [Problem Link](https://www.luogu.com.cn/problem/AT_joi2015ho_c)

题意略。

需要注意的是删除的道路不只是 $1\to u$，还包含 $1\to u\to v(dis_u<dis_v)$。

### Solution

首先注意到选择的 $X$ 一定是某一个点 $u$ 到 $1$ 节点的距离，所以先 Dijkstra 跑一遍预处理 $dis_u$，然后从小到大排序后枚举每个 $dis_u$ 来计算答案。比如样例中的遍历顺序为 $1, 3, 2, 4, 5$，可以发现，在枚举到靠后的节点时，它前面的所有点之间的路径都要被拆掉，这些点到当前节点的路径也要被拆掉（如果存在），所以当前拆掉的边可以由上一步拆掉的边转移而来，这也是从小到大的排序的意义。

一个例子，计算完 $2$ 后，$1\to 2$ 边会被删掉，按照上面的计算方法，下一步计算 $3$，此时应该拆掉 $1\to 3$ 和 $2\to 3$。

![joi2015ho_c-example.png](https://img.makerlife.top/data/qexo/2024-10-22-joi2015ho_c-example-e108701b4a3df6ede75535bfd4d554ff.png)

### Core Code

```cpp
#define int ll
int n, m, c;
struct node {
    int pos, dis;
    bool operator<(const node& x) const {
        return dis > x.dis;
    }
};
struct edge {
    int v, w;
};
vector<edge> e[N];
bitset<N> vis;
node dis[N];
int sum = 0ll;
void dij(int u) {
    for (int i = 1; i <= n; i++) {
        dis[i].dis = INF;
    }
    dis[1].dis = 0ll;
    priority_queue<node> q;
    q.push({1, 0});
    while (!q.empty()) {
        int u = q.top().pos;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1ll;
        for (auto x : e[u]) {
            int v = x.v, w = x.w;
            if (dis[v].dis > dis[u].dis + w) {
                dis[v].dis = dis[u].dis + w;
                if (!vis[v]) q.push({v, dis[v].dis});
            }
        }
    }
}
signed main() {
    n = read(); m = read(); c = read();
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        e[u].push_back({v, w});
        e[v].push_back({u, w});
        sum += w;
    }
    for (int i = 1; i <= n; i++) {
        dis[i].pos = i;
    }
    dij(1);
    sort(dis + 1, dis + n + 1);
    int minn = INF;
    int last = 0;
    vis.reset();
    for (int i = n; i >= 1; i--) {
        int ans = dis[i].dis * c;
        ans += sum;
        vis[dis[i].pos] = 1;
        for (auto x : e[dis[i].pos]) {
            int v = x.v, w = x.w;
            if (vis[v]) last += w;
        }
        minn = min(minn, ans - last);
    }
    cout << minn << endl;
    return 0;
}
```

---

## 作者：神秘番茄厂长 (赞：0)

##### 这题怎么会是黑题？

这题关键在于$ X $，我们该怎么选择这个$ X $？

首先可以想到求出单源最短路，用$dijkstra$即可。那么现在我们就有了一个$d$数组，其中 $d[i]$ 表示 $i$ 到 $1$ 的最短路，而 $X$ 就在这个数组里面取值，为什么？

用某个点到一的最短距离为$X$可以保证其为分界点：少一则有一些点取不到，多一(若取到的点数不变)答案就变大了。

计算答案方面：总花费等于$C\times X +$剩余路径总长度。第一段知道$X$就可以算，第二段我们可以设置一个变量$rest$，表示当前剩余的边的总长度，在枚举$X$的时候维护。

接下来（我是这么写的），用一个结构体存最短路，结构体内包含最短路和当前点的编号。按照最短路从小到大排序，再从小到大枚举$X$，将当前这个点标记上，再遍历这个点的每条边，如果一条边的两个端点都被标记过且这个边没有被标记过，打上边的标记，然后$rest$减去相应的值，计算答案:
$$ans=min(ans,C \times X+rest)$$

##### 总结一下思路：
1 .输入$n,m,C。$

2 .输入$m$条边，同时计算$rest$。

3 .$dijkstra$求最短路，并处理排序。

4 .枚举$X$，同时维护$rest$，同时计算答案。

##### 下面是一些代码实现上的细节：
1 .$dijkstra$ 要用堆优化。

2 .注意是双向边，边的编号要从$2$开始，标记第$i$条边的时候记得$(i$^$1)$也要标记。

3 .在枚举$X$的时候记得处理最短路相同的

4 .记得$long long $，还有，无限大不能开太小！！！$0x3f3f3f3f3f3f3f$就差不多。

# 代码：
```c++
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;

const int N=1e5+10,M=2e5+10;
struct node
{
	int val,idx;
}cc[N];
int n,m,C,idx=1,ne[M<<1],e[M<<1],to[M<<1],h[N<<1],d[N],ans,paans,X,rest;
bool vis[N],edge[M<<1];

void add(int a,int b,int c)
{
	ne[++idx]=h[a];
	to[idx]=b;
	e[idx]=c;
	h[a]=idx;
}

void dijkstra()
{
	memset(d,0x7f,sizeof(d)); d[1]=0;
	priority_queue<pair<int,int> >q;
	q.push(mp(0,1));
	while(q.size())
	{
		int x=q.top().second; q.pop();
		for(int i=h[x];i;i=ne[i])
		{
			int y=to[i],z=e[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(mp(-d[y],y));
			}
		}
	}
}

bool cmp(node a,node b)
{return a.val<b.val;}

signed main()
{
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	int a,b,c; cin>>n>>m>>C;
	for(int i=1;i<=m;++i)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		add(a,b,c); add(b,a,c); rest+=c;
	}
	dijkstra();
	for(int i=1;i<=n;++i)
	cc[i].idx=i,cc[i].val=d[i];
	sort(cc+1,cc+1+n,cmp);
	ans=0x3f3f3f3f3f3f3f;
	for(int i=1;i<=n;++i)
	{
		X=cc[i].val;
		int now=cc[i].idx;
		vis[now]=1;
		for(int j=h[now];j;j=ne[j])
		{
			if(edge[j]||!vis[to[j]]) continue;
			edge[j]=edge[j^1]=1;
			rest-=e[j];
		}
		ans=min(ans,X*C+rest);
	}
	cout<<ans<<"\n"; return 0;
}
```
##### 这题怎么会是黑题？

---

