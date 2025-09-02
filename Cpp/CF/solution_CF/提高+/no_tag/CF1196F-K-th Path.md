# K-th Path

## 题目描述

给定一个无向带权连通图，求子节点两两之间最短路径长度从小到大排序之后第 $k$ 条路径长度。

## 说明/提示

对于 $100\%$ 的数据，$ 2 \le n \le 2 \cdot 10^5 $ , $ n - 1 \le m \le \min\Big(\frac{n(n-1)}{2}, 2 \cdot 10^5\Big) $ , $ 1 \le k \le \min\Big(\frac{n(n-1)}{2}, 400\Big),1\le w\le 10^9$。

## 样例 #1

### 输入

```
6 10 5
2 5 1
5 3 9
6 2 2
1 3 1
5 1 8
6 5 10
1 6 5
6 4 6
3 6 2
3 4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7 15 18
2 6 3
5 7 4
6 5 4
3 6 9
6 7 7
1 6 4
7 1 6
7 2 1
4 3 2
3 2 8
5 3 6
2 5 5
3 7 9
4 1 8
2 1 1
```

### 输出

```
9
```

# 题解

## 作者：Ynoi (赞：13)

注意到k很小。

我们知道，可以产生最小值的，只可能是
长度最短的$k$条边相连的点所产生的，同时边也只可能是最短的k条边

然后我们就可以处理出这些点(最多$2k$个)

然后跑Floyd即可

时间复杂度$k^3$，是能跑得过的

如果想再快一点，可以对每个点为原点跑一遍dijkstra，时间复杂度就是$k^2logk$的了

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 805
#define MAXM 200005
#define LL long long

int n,m,nn,k;
struct bian
{
	int x,y,l;
}b[MAXM];
int c[MAXM],a[MAXN];
long long dis[MAXN][MAXN];
long long d[MAXN*MAXN];

inline int read()
{
    register int x = 0 , ch = getchar();
    while( !isdigit( ch ) ) ch = getchar();
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
    return x;
}

bool cmp(bian a,bian b) {
	return a.l < b.l;
}
void rd()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1; i <= m; i ++) {
		b[i].x = read();
		b[i].y = read();
		b[i].l = read();
	}
	sort(b+1,b+m+1,cmp);
}

signed main()
{
	rd();
	memset(dis,0x3f,sizeof(dis));
	for(int i = 1; i <= k; i ++) {
		c[b[i].x] = 1;
		c[b[i].y] = 1;
	}
	for(int i = 1; i <= n; i ++) 
		a[i] = a[i-1] + c[i];
	nn = a[n];
	for(int i = 1; i <= k; i ++) {
		dis[ a[b[i].x] ][ a[b[i].y] ] = b[i].l;
		dis[ a[b[i].y] ][ a[b[i].x] ] = b[i].l;
		
	}
	n = nn;
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
			if(dis[i][j] > dis[i][k] + dis[k][j])
				dis[i][j] = dis[i][k] + dis[k][j];
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < i; j ++)
		{
			cnt ++;
			d[cnt] = dis[i][j];
		}
	sort(d+1,d+cnt+1);
	cout<<d[k];
	return 0;
}

```

---

## 作者：Mortidesperatslav (赞：7)

好题。

因为要求第 $k$ 小，所以路径肯定由前 $k$ 小的边构成。因为如果第 $k+1$ 小的边在路径上，就至少有 $k$ 条路径（一条边也算一条路径）比该路径小，那么就与这条路径是第 $k$
小路径矛盾。于是得证。

那么把前 $k$ 小的边拎出来，**然后离散化**，因为 $k$ 那么小，跑个 $O(k^3)$ 的 floyd 就能过了，要优化当然是跑 spfa，最短路部分最坏是 $O(k^2)$，排序可能会 $O(k^2 \log k)$。

我写了个 floyd。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct ed{
	int u,v,c;
	bool operator <(ed b){
		return this->c < b.c;
	}
}a[200005];
long long f[805][805];
int cnt=0;
map<int,int>mp;
priority_queue<long long,vector<long long>,greater<long long> >q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	memset(f,-1,sizeof(f));
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)cin>>a[i].u>>a[i].v>>a[i].c;
	sort(a+1,a+1+m);//对边进行排序
	for(int i=1;i<=k;i++){//离散化
		if(!mp[a[i].u])mp[a[i].u]=++cnt;
		if(!mp[a[i].v])mp[a[i].v]=++cnt;
		f[mp[a[i].u]][mp[a[i].v]]=a[i].c;
		f[mp[a[i].v]][mp[a[i].u]]=a[i].c;
	}
	for(int k=1;k<=cnt;k++)//floyd
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++){
				if(f[i][k]==-1||f[k][j]==-1)continue;
				if(f[i][j]==-1||f[i][k]+f[k][j]<f[i][j])
					f[i][j]=f[i][k]+f[k][j];
			}
	for(int i=1;i<=cnt;i++)
		for(int j=i+1;j<=cnt;j++)
			if(f[i][j]!=-1)q.push(f[i][j]);//堆排求第 k 小路径
	for(int i=1;i<k;i++)q.pop();
	cout<<q.top();
}
```

---

## 作者：小明小红 (赞：4)

诈骗题，注意到要求第 $k$ 小的边，且 $k$ 很小，我们可以想到第 $k$ 小路径一定不小于第 $k$ 小边，因此我们推理出第 $k$ 小路径是由前 $k$ 小边组成的也就是由前 $k$ 小边的点构成的，所以我们将构成这 $k$ 条边的至多 $2k$ 个点离散化后进行 Floyd 就好了。

---

## 作者：Querainy (赞：4)

来一个乱搞方法，大概是题解区里唯一一个复杂度带$km$的?

直接在图上跑$n$遍Dij显然正确但复杂度爆炸，我们尝试优化。

考虑单源最短路中，Dij从堆中取出点来的顺序就是距离从小到大的。如果我们可以把这些东西归并一下，那么就可以求出第$k$小了。至于怎么归并，当然是使用堆。开个堆维护堆看起来有点麻烦，那么我们开一个全局的堆，同时对这些点跑Dij，堆中每个节点记录 : 起点编号，这个点的编号，起点到这个点的距离。因为开不下距离数组，我们使用`map`。因为每个点和自己的路径不算数，而且每条路径会跑两次，所以我们一共跑$n+2k$轮。

接下来你发现你MLE on test21，打开一看发现是菊花图，这是因为前$n$次的时候每个点(除了中间的点)把中间的点扔进了堆，接下来$2k$次中间的点一口气扔了大约$2\times 400\times 200000=160000000$个点进堆和`map`，这玩意显然爆炸。

但是发现既然一共只跑$n+2k$轮，那么距离排名超过$n+2k$的点永远不会被用到，所以我们可以把堆大小限制在$n+2k$以内。堆满了的时候，如果一个点的距离更新后仍然比堆底要大，那么我们直接跳过对它的堆和`map`操作，这样空间复杂度是$O(k+n)$，时间复杂度是$O((k+m)\log n+km)$，这里认为$m$不比$n$低阶。

实现需要注意，`set`没有重复元素，所以使用`set`作为双端堆的话，需要把起点编号，这个点编号，距离都比一下，否则可能把两个不同的点视为相同的。另外我的实现没有回收`map`的空间，空间复杂度可能是错的，但是我写了写挂了，感觉比较麻烦就没再管（

经测试可以通过本题。使用64位的C++17，用时为857ms。

```
#include<stdio.h>
#include<set>
#include<map>
using std::map;
using std::set;

struct Edge
{
	int v,w,next;
}e[400002];

int ecnt,h[200002];

inline void add_edge(int u,int v,int w)
{
	e[++ecnt]={v,w,h[u]};
	h[u]=ecnt;
	e[++ecnt]={u,w,h[v]};
	h[v]=ecnt;
}

struct Node
{
	int s,u;
	long long dis;
	inline bool operator < (Node x) const
	{
		return dis==x.dis?u==x.u?s<x.s:u<x.u:dis<x.dis;
	}
};

set<Node> q;
map<int,long long> d[200002];

int n,m,k;

inline Node front(){ return *q.begin(); }
inline void pop(){ q.erase(q.begin()); }
#define push(x) q.insert(x)
inline Node back(){ auto temp=q.end();temp--;return *temp; }
inline void pop_back(){ auto temp=q.end();temp--;q.erase(temp); }

inline long long Dij()
{
	for(int i=1;i<=n;i++)
		q.insert(Node{i,i,0}),d[i][i]=0;
	int t=n+(k<<1)-1;
	while(t>0)
	{
		Node now=front();pop();
		int s=now.s,u=now.u;
		long long du=d[s][u];
		if(du!=now.dis) continue;
		t--;
		for(int i=h[u];i;i=e[i].next)
		{
			if(q.size()>=n+(k<<1)&&du+e[i].w>=back().dis) continue;
			auto it=d[s].find(e[i].v);
			if(it==d[s].end())
				d[s][e[i].v]=du+e[i].w,q.insert(Node{s,e[i].v,du+e[i].w});
			else if(du+e[i].w<it->second)
				it->second=du+e[i].w,q.insert(Node{s,e[i].v,du+e[i].w});
			if(q.size()>n+(k<<1)) pop_back();
		}
	}
	return front().dis;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),add_edge(u,v,w);
	printf("%I64d",Dij());
	return 0;
}
```

---

## 作者：两年打铁 (赞：4)

题意：求第K大路径（注意是路径，不是K短路）

首先，如果只考虑边，那么最多有k条边会对答案产生影响，也就是说答案一定小于等于第k小的那条边。

既然如此，对答案有影响的路径肯定也是由k条路径相互组合产生的（很显然，如果比第K小的边大不肯能更新答案）

那么我们就知道了对答案有影响的点最多只有k级别的。

那我们就只加前K小的边，然后对所有的被加过边的点跑最短路，然后用这个点到其他点的最短路去更新答案

跑最短路我用的是Dj，复杂度$O(k^2logk)$


```

 #include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long 
using namespace std;
 
const int big=1e16;
 
inline void read(int &x)
{
	x=0;char ch=getchar();int pd=1;
	while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=pd;
}
inline void write(const int &x)
{
	char ggg[10001];int s=0;int tmp=x;
	if(tmp==0){putchar('0');return;}
	if(tmp<0){tmp=-tmp;putchar('-');}
	while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
	while(s>0){putchar(ggg[--s]);}
}
 
const int N=2e5+233;
 
struct dd
{
	int end,nt,v;
}e[N<<1];
 
int t,h[N],cnt,b[N],dis[N],n,m,k;
 
bool vis[N];
 
 
inline void add(int begin,int end,int v)
{
	++t;
	e[t].end=end;
	e[t].nt=h[begin];
	h[begin]=t;
	e[t].v=v;
}
 
struct dian
{
	int pos,val;
	inline bool operator < (const dian &nt) const 
	{
		return val>nt.val;
	}
};
 
priority_queue<dian>q;
priority_queue<int ,vector <int > ,greater<int> > qu;
 
void dj(int s)
{
	for(register int i=1;i<=cnt;++i)
	{
		dis[b[i]]=big;
		vis[b[i]]=0;
	}
	dis[s]=0;
	q.push((dian){s,0});
	while(!q.empty())
	{
		int x=q.top().pos;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(register int i=h[x];i;i=e[i].nt)
		{
			int u=e[i].end;
			if(dis[x]+e[i].v<dis[u])
			{
				dis[u]=dis[x]+e[i].v;
				if(!vis[u])q.push((dian){u,dis[u]});
			}
		}
	}
}
struct edge
{
	int x,y,z;
}z[N];
 
inline bool cmp(const edge &x,const edge &y)
{
	return x.z<y.z;
}
int in[N];
signed main()
{
	read(n);
	read(m);
	read(k);
	for(register int i=1;i<=m;++i)
	{
		read(z[i].x);
		read(z[i].y);
		read(z[i].z);
	}
	sort(z+1,z+m+1,cmp);
	for(register int i=1;i<=min(m,k);++i)
	{
		add(z[i].x,z[i].y,z[i].z);
		add(z[i].y,z[i].x,z[i].z);
		if(!in[z[i].x])b[++cnt]=z[i].x,in[z[i].x]=1;
		if(!in[z[i].y])b[++cnt]=z[i].y,in[z[i].y]=1;
	}
	for(register int i=1;i<=cnt;++i)
	{
		dj(b[i]);
		for(register int j=i+1;j<=cnt;++j)
		{
			qu.push(dis[b[j]]);
		}
	}
	for(register int i=1;i<k;++i)qu.pop();
	cout<<qu.top()<<endl;
	return 0;
}
```


---

## 作者：liuenyin (赞：2)

前 $k$ 条最短路只能由长度前 $k$ 短的边构成，而 $k\leq 400$，这 $k$ 条边最多连接 $2k$ 个点，因为可以任选两点所以可以将这 $k$ 条边排序后找到这些点，用这些点和边跑一遍全源最短路，将每一条路径都从大到小排序取出第 $k$ 大即可。

时间复杂度 $O(k^3 + m \log m)$，可以通过本题。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
const int N=2e5+5;
//只会用到前k短边
namespace fastio{
    struct reader{
    	template<typename T>reader&operator>>(T&x){
    		char c=getchar();short f=1;
    		while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
    		x=0;while(c>='0'&&c<='9'){
    			x=(x<<1)+(x<<3)+(c^48);
    			c=getchar();
    		}x*=f;return *this;
    	}
    }cin;
    struct writer{
        template<typename T>writer&operator<<(T x){
    		if(x==0)return putchar('0'),*this;
    		if(x<0)putchar('-'),x=-x;
    		static int sta[45];int top=0;
    		while(x)sta[++top]=x%10,x/=10;
    		while(top)putchar(sta[top]+'0'),--top;
    		return*this;
    	}
    }cout;
};
#define cin fastio::cin
#define cout fastio::cout
int n,m,k;
struct edge{
    int u,v,w;
    bool operator<(const edge &A)const{
        return this->w<A.w;
    }
}es[N];
int cf[N],id[N],cnt;
ll dis[1005][1005];
ll ans[1000005];
int main(){
    cin>>n>>m>>k;
    for(register int i=1;i<=m;i++)
        cin>>es[i].u>>es[i].v>>es[i].w;
    std::sort(es+1,es+1+m);
    for(register int i=1;i<=k;i++)
        cf[es[i].u]=cf[es[i].v]=1;
    for(register int i=1;i<=n;i++)id[i]=id[i-1]+cf[i];
    memset(dis,0x3f,sizeof dis);
    for(register int i=1;i<=k;i++)dis[id[es[i].u]][id[es[i].v]]=dis[id[es[i].v]][id[es[i].u]]=es[i].w;
    for(register int p=1;p<=id[n];p++){
        for(register int i=1;i<=id[n];i++){
            for(register int j=1;j<=id[n];j++){
                dis[i][j]=std::min(dis[i][j],dis[i][p]+dis[p][j]);
            }
        }
    }
    for(register int i=1;i<=id[n];i++){
        for(register int j=i+1;j<=id[n];j++){
            ans[++cnt]=dis[i][j];
        }
    }
    std::sort(ans+1,ans+1+cnt);
    cout<<ans[k];
    return 0;
}
```

---

## 作者：开始新的记忆 (赞：2)

题目大意：n个点，m条边，求第k短路。

大致思路：

1.请出门左转模板——K短路。

2.我们注意到，k是很小的，只有400的大小，于是我们就发现我们可以列举出最k条的最小的边然后进行Floyd，复杂度O（k^3），最后再sort一下即可。如果每条边都不互相联通，那么第k小的就是题目所求，如果有联通，那么就会有多余的边出现，那么就选其中第k短的路径长度即可。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f3f3f3f3f
long long dp[810][810],dis[500010];
int n,m,k,b[500010],tot=0,cnt=0;

struct node{
    int u,v,w;
} a[500010];

bool cmp(node x,node y)
{
	return x.w<y.w; 
}

int main()
{	memset(dp,0x3f,sizeof(dp));
	cin>>n>>m>>k;
    for(int i=1;i<=m;++i) 
		cin>>a[i].u>>a[i].v>>a[i].w;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=min(k,m);i++) 
		b[++cnt]=a[i].u,b[++cnt]=a[i].v;
    sort(b+1,b+cnt+1);
	n=unique(b+1,b+cnt+1)-b-1;
    for(int i=1;i<=min(k,m);++i) 
	{
        int from=lower_bound(b+1,b+n+1,a[i].u)-b;
		int to=lower_bound(b+1,b+n+1,a[i].v)-b;
        dp[from][to]=a[i].w;
		dp[to][from]=a[i].w;
    }
    for(int kk=1;kk<=n;++kk) 
		for(int i=1;i<=n;++i) 
			for(int j=1;j<=n;++j)
				if(dp[i][kk]+dp[kk][j]<dp[i][j]) 
					dp[i][j]=dp[i][kk]+dp[kk][j];
    for(int i=1;i<=n;++i) 
		for(int j=i+1;j<=n;++j) 
			if(dp[i][j]!=inf) 
				dis[++tot]=dp[i][j];
    sort(dis+1,dis+tot+1);
    cout<<dis[k]<<endl;
	return 0;   
}
```


---

## 作者：_Supernova (赞：1)

# 一、思路分析。

首先，我们注意到数据范围较大，正常算法无法通过。

此时，我们需要观察题目性质，舍弃一些明显无法对答案产生贡献的事物。

容易发现，对边从小到大进行排序，从第 $k+1$ 条边开始往后，是不可能成为第 $k$ 条最短路长度的，因为前面已经有 $k$ 条路径比他小了，这是答案的上界。

于是选取前 $k$ 条边重新建图，注意离散化，记剩下来的节点数为 $cnt$。

因为 $k\leq400$，故 $cnt\leq800$，成功缩小数据范围。

此时我们使用 Floyd 算法，求出任意两点间的最短路，记为数组 $dis$。我们用一个堆，维护 $dis$ 的一个升序排列，其中第 $k$ 个值便是答案。

还有不懂的，欢迎私信讨论！

# 二、代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, M = 2e5 + 5, N_ = 900;
ll n, m, k, dis[N_][N_];
ll cnt;
struct edge {
	ll u, v, w;
} e[M];
bool cmp(edge x, edge y) {
	return (x.w < y.w);
}
map <ll, ll> mp;
priority_queue <ll, vector <ll>, greater <ll> > pq;
void init(void) {
	memset(dis, 0x3f, sizeof dis);
	for (ll i = 1; i < N_; ++i) dis[i][i] = 0;
	return ;
}
void Floyd(void) {
	for (ll l = 1; l <= cnt; ++l) {
		for (ll i = 1; i <= cnt; ++i) {
			for (ll j = 1; j <= cnt; ++j) {
				dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
			}
		}
	}
	return ;
}
int main(void) {
	scanf("%lld %lld %lld", &n, &m, &k);
	init();
	for (ll i = 1; i <= m; ++i) {
		scanf("%lld %lld %lld", &e[i].u, &e[i].v, &e[i].w);
	}
	sort(e + 1, e + m + 1, cmp);
	for (ll i = 1; i <= k; ++i) {
		if (!mp[e[i].u]) mp[e[i].u] = ++cnt;
		if (!mp[e[i].v]) mp[e[i].v] = ++cnt;
		dis[mp[e[i].u]][mp[e[i].v]] = dis[mp[e[i].v]][mp[e[i].u]] = e[i].w;
	}
	Floyd();
	for (ll i = 1; i <= cnt; ++i) {
		for (ll j = 1; j < i; ++j) {
			if (i != j) {
				pq.push(dis[i][j]);
			}
		}
	}
	for (ll i = 1; i < k; ++i) pq.pop();
	printf("%lld", pq.top());
    return 0;
}
```

谢谢大家与审核员！

---

## 作者：FlyPancake (赞：1)

## [CF1196F K-th Path](https://www.luogu.com.cn/problem/CF1196F) 题解

第一眼：$k$ 短路！

但是注意到此题并不是模板题，观察发现 $k \le 400$，而节点两两之间第 $k$ 长的路肯定由不大于 $k$ 的边数组成。也就是说有用的边最多只有 400 条，有用的点最多只有 800 个。

记录前 $k$ 条边，并将波及的点**离散化**，建新图跑 Floyd 即可。

时间复杂度为 $O(k^3)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5;

struct Edge{
    int u, v, w;
}e[N];

struct node{
    int v, w;
};
ll dis[805][805], d[650000], cnt;
unordered_map<int, int> M;

void floyd(){
    for(int k=1; k<=cnt; k++)
        for(int i=1; i<=cnt; i++)
            for(int j=1; j<=cnt; j++)
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, k; cin>>n>>m>>k;
    for(int i=1; i<=m; i++)
        cin>>e[i].u>>e[i].v>>e[i].w;
    sort(e+1, e+1+m, [&](Edge a, Edge b){ return a.w < b.w; });
    memset(dis, 0x3f, sizeof(dis));
    for(int i=1; i<=k; i++){
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(!M.count(u)) M[u] = ++cnt;
        if(!M.count(v)) M[v] = ++cnt;
        dis[M[u]][M[v]] = dis[M[v]][M[u]] = w;
    }
    floyd();
    int tot = 0;
	for(int i=1; i<=cnt; i++)
		for(int j=1; j<i; j++)
			d[++tot] = dis[i][j];
	sort(d+1,d+tot+1);
	cout<<d[k];
    return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

~~认真看看数组开多大是很有必要的。~~

其实这题只要注意到**一条边也是一条路径**就基本解决了。

我们只需要选出前 $k$ 小的边，剩下的由多条边组成的前 $k$ 小的路径也一定是由这些边组成的，因为我们如果选了一条大于第 $k$ 小的还不如直接选一条边。

注意到 $k\le 400$，所以离散化之后跑 Floyd 就好了，最后直接排序输出答案即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
int n ,m ,k ,dis[807][807] ,tot ;
struct point {
	int u ,v ,w ;
	bool operator < (const point &cmp) const { return w < cmp.w ; }
} p[200007] ;
vector < int > v ;
unordered_map < int ,int > ma ;
signed main () {
	memset (dis ,-1 ,sizeof dis) ;
	read (n) ,read (m) ,read (k) ;
	f (i ,1 ,m ,1) {
		read (p[i].u) ,read (p[i].v) ,read (p[i].w) ;
	}
	sort (p + 1 ,p + m + 1) ;
	f (i ,1 ,k ,1) {
		if (! ma[p[i].u]) ma[p[i].u] = ++ tot ;
		if (! ma[p[i].v]) ma[p[i].v] = ++ tot ;
		dis[ma[p[i].u]][ma[p[i].v]] = dis[ma[p[i].v]][ma[p[i].u]] = p[i].w ;
	}
	f (k ,1 ,tot ,1) {
		f (i ,1 ,tot ,1) {
			if (dis[i][k] == -1) continue ;
			f (j ,1 ,tot ,1) {
				if (dis[k][j] == -1) continue ;
				if (dis[i][j] == -1) dis[i][j] = dis[i][k] + dis[k][j] ;
				else dis[i][j] = min (dis[i][j] ,dis[i][k] + dis[k][j]) ;
			}
		}
	}
	f (i ,1 ,tot ,1) {
		f (j ,i + 1 ,tot ,1) {
			if (dis[i][j] != -1) v.push_back (dis[i][j]) ;
		}
	}
	sort (v.begin () ,v.end ()) ;
	cout << v[k - 1] << '\n' ;
	return 0 ;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 题意简述
给定一个无向带权连通图，求子节点两两之间最短路径长度从小到大排序之后第 $k$ 长的路径长度。
# 思路解析
这个问题可以通过 Floyd 算法或者 Dijkstra 算法来解决，但是考虑到题目中给出的数据规模（ $k \le 400$ ），使用  Floyd 算法可能会因为时间复杂度较高而险些超时（ $O(k^3)$ ）。因此，我们选择使用 Dijkstra 算法来解决这个问题。

如果只考虑边，最多有 $k$ 条边会影响最终答案，因为任何大于第 $k$ 小边的边都不会影响答案。

只考虑前 $k$ 小的边，因为这些边是可能影响最终答案的关键边。

对所有被加过边的点运行 Dijkstra 算法，计算到其他所有点的最短路径。


# 代码实现
1. 将所有的边按照权重从小到大排序，以便于我们从最短的边开始考虑。

2. Dijkstra 算法：从排序后的边中选择前 $k$ 条边构建子图，然后对子图中的每个顶点运行 Dijkstra 算法，计算到其他所有顶点的最短路径。

3. 最短路径集合：将所有顶点对的最短路径长度存入一个集合中，并保持集合的有序性。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, inf = 1e18;
struct edge {
    int v, w;
};
struct node {
    int dis, u;
    bool operator>(const node& a) const {
        return dis > a.dis;
    }
};
struct side {
    int u, v, w;
    bool operator<(const side& a) const {
        return w < a.w;
    }
} sid[N];
bool vis[N], in[N];
int n, m, k, nn, dis[N], point[N];
vector<edge> e[N];
priority_queue<node, vector<node>, greater<node> > q;
priority_queue<int, vector<int>, greater<int> > qu;
inline void dijkstra(int s) {
    for (int i = 1; i <= nn; i++) {
        dis[point[i]] = inf;
        vis[point[i]] = false;
    }
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        if (!vis[u]) {
            vis[u] = true;
            for (auto ed : e[u]) {
                int v = ed.v, w = ed.w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.push({dis[v], v});
                }
            }
        }
    }
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> sid[i].u >> sid[i].v >> sid[i].w;
    }
    sort(sid + 1, sid + 1 + m);
    for (int i = 1; i <= min(m, k); i++) {
        e[sid[i].u].push_back({sid[i].v, sid[i].w});
        e[sid[i].v].push_back({sid[i].u, sid[i].w});
        if (!in[sid[i].u]) {
            point[++nn] = sid[i].u;
            in[sid[i].u] = true;
        }
        if (!in[sid[i].v]) {
            point[++nn] = sid[i].v;
            in[sid[i].v] = true;
        }
    }
    for (int i = 1; i <= nn; i++) {
        dijkstra(point[i]);
        for (int j = i + 1; j <= nn; j++) {
            qu.push(dis[point[j]]);
        }
    }
    for (int i = 1; i < k; i++) {
        qu.pop();
    }
    cout << qu.top() << endl;
    return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
观察到 $k$ 很小，考虑通过 $k$ 来解题。

题目中要求第 $k$ 长的路径长度，那么根据贪心策略，将所有边权从小到大排序后，第 $k+1$ 长的边权一直到第 $m$ 长的边权全部都是废边了，不可能组合出答案。

那么接下来就很好做了，$k$ 条边最多 $2k$ 个顶点，用 floyd 跑最短路绰绰有余，最后把所有可能的答案记录，排个序取第 $k$ 大即可。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define N 200005
#define M 805 
using namespace std; 
ll n,m,k;
struct node{
	int u,v,w;
}e[N];
bool cmp(node x,node y){
	return x.w<y.w;
}
ll dis[M][M],cnt,id[N];
ll b[N],tot;
bool vis[N];
int main(){
	memset(dis,0x3f,sizeof dis);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e+1,e+m+1,cmp);
	m=k;
	for(int i=1;i<=m;i++){
		if(!vis[e[i].u]) vis[e[i].u]=1,id[e[i].u]=++cnt;
		if(!vis[e[i].v]) vis[e[i].v]=1,id[e[i].v]=++cnt;
	}
	for(int i=1;i<=m;i++){
		dis[id[e[i].u]][id[e[i].v]]=e[i].w;
		dis[id[e[i].v]][id[e[i].u]]=e[i].w;
	}
	for(int k=1;k<=cnt;k++){
		for(int i=1;i<=cnt;i++){
			for(int j=1;j<=cnt;j++){
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=i+1;j<=cnt;j++){
			b[++tot]=dis[j][i];
		}
	}
	sort(b+1,b+tot+1);
	cout<<b[k];
	return 0;
}
```

---

## 作者：chenhouyuan (赞：0)

~~k 小于等于 400 和 n、m 格格不入~~

我们先对边按边权从小到大排序，显然有 $ans\le w_k$，因为最坏情况下节点两两之间第 $k$ 短的路径长度即为 $w_k$。因此我们将前 $k$ 短的边对应的之多 $2k$ 个点找出来对他们跑 dijkstra 即可。时间复杂度 $m\log m+k^2 \log k$。
#### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k,dis[200010];
struct edge{
	ll from,to,w;
}b[200010];
vector<edge>a[200010];
bool cmp(edge c,edge d){
	return c.w<d.w;
}
set<ll>us;
struct node{
	ll id,d;
	bool operator<(const node &other)const{
		return d>other.d;
	}
};
priority_queue<node>q;
priority_queue<ll>pq;
int main(){
	cin>>n>>m>>k;
	for(ll i=0;i<m;i++){
		cin>>b[i].from>>b[i].to>>b[i].w;
		a[b[i].from].push_back({0,b[i].to,b[i].w});
		a[b[i].to].push_back({0,b[i].from,b[i].w});
	}
	sort(b,b+m,cmp);
	for(ll i=0;i<k;i++){
		us.insert(b[i].from);
		us.insert(b[i].to);
	}
	for(ll i:us){
		memset(dis,0x3f,sizeof(dis));
		while(!q.empty())q.pop();
		q.push({i,0});
		dis[i]=0;
		while(!q.empty()){
			ll x=q.top().id,di=q.top().d;
			q.pop();
			if(dis[x]!=di)continue;
			if(x>i){
				pq.push(dis[x]);
			}
			for(edge it:a[x]){
				if(us.find(it.to)!=us.end()&&dis[x]+it.w<dis[it.to]){
					dis[it.to]=dis[x]+it.w;
					q.push({it.to,dis[it.to]});
				}
			}
		}
	}
	while(pq.size()>k)pq.pop();
	cout<<pq.top();
	return 0;
}
```

---

## 作者：Not_defined (赞：0)

我们知道，$k$ 短路肯定是由长度最短的$k$条边中产生的，所以 $k$ 条边最多有 $2k$ 个点。由于 $k \le 400$，所以我们可以考虑先离散化点，然后 Floyd 求最短路，并排序，最后取出第 $k$ 短的边即可。
### code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=2e5+10;
struct node
{
	int x,y,wei;
}e[M];
bool cmp(node s1,node s2)
{
	return s1.wei<s2.wei;
}
int n,m,k,rcnt,cnt,a[810][810],d[810*810],c[M],p[M];
signed main()
{
	cin>>n>>m>>k;
	memset(a,0x3f,sizeof a);
	for(int i=1;i<=m;i++)cin>>e[i].x>>e[i].y>>e[i].wei;
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=k;i++)c[e[i].x]=c[e[i].y]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]+c[i];
	cnt=p[n];
	for(int i=1;i<=k;i++)a[p[e[i].x]][p[e[i].y]]=a[p[e[i].y]][p[e[i].x]]=e[i].wei;
	for(int u=1;u<=cnt;u++)
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
                a[i][j]=min(a[i][j],a[i][u]+a[u][j]);
    for(int i=1;i<=cnt;i++)
    	for(int j=i+1;j<=cnt;j++)
            d[++rcnt]=a[i][j];
    sort(d+1,d+1+rcnt);
    //for(int i=1;i<=rcnt;i++)cout<<d[i]<<" ";
    cout<<d[k];
	return 0;
}
```


---

## 作者：Alexandra (赞：0)

## 前言
模拟赛时的第四题，经大佬帮助找到了原题。  

## 题目大意
给出一张 $n$ 个点，$m$ 条边的图，求出第 $k$ 条最短路的大小。  

## 题目分析  
由于可以任选两点，所以是求全源最短路。我们可以选用 Floyd 或者 $n$ 遍 Dijkstra，时间复杂度分别是 $O(n^3)$ 和 $O(n^2 \log n)$。而 $n$ 最大取到 $2 \times 10^5$，所以显然是会炸掉的。  
深入思考一下，前 $k$ 条最短路只有可能由长度前 $k$ 小的边构成，所以我们找出前 $k$ 条边跑全源最短路即可。  

$k$ 最大为 $400$，你甚至可以用 Floyd 过掉这个题。  

## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 4000010
long long n,m,p,ans,f[1010][1010],ww[N],cnt,b[N],tot;
struct fun
{
	long long u,v,Next,w;
}edge[N];
inline long long read()
{
	long long wjl=0,jia=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')jia*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		wjl=(wjl<<1)+(wjl<<3)+(ch^48);
		ch=getchar();
	}
	return wjl*jia;
}
bool cmp(fun a,fun b)
{
	return a.w<b.w;
}
int main ()
{
	n=read(),m=read(),p=read();
	for(long long i=1;i<=m;i++)edge[i].u=read(),edge[i].v=read(),edge[i].w=read();
	sort(edge+1,edge+1+m,cmp);
	memset(f,0x3f,sizeof(f));
	for(long long i=1;i<=p;i++)
	{
		long long uu,vv;
		if(b[edge[i].u])uu=b[edge[i].u];
		else uu=++tot,b[edge[i].u]=tot;
		if(b[edge[i].v])vv=b[edge[i].v];
		else vv=++tot,b[edge[i].v]=vv;
		f[uu][vv]=f[vv][uu]=min(edge[i].w,f[uu][vv]);
	}
	for(long long k=1;k<=tot;k++)
	{
		for(long long i=1;i<=tot;i++)
		{
			for(long long j=1;j<=tot;j++)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		}
	}
	for(long long i=1;i<=tot;i++)
	{
		for(long long j=1;j<i;j++)ww[++cnt]=f[i][j];
	}
	sort(ww+1,ww+1+cnt);
	for(int i=1;i<=p;i++)ans+=ww[i];
	printf("%lld\n",ww[p]);
	return 0;
}
```


---

## 作者：RoyWu1207 (赞：0)

# Description

一看题目顿时觉得~~完了~~。

$k$ 很小？可以以此为突破口。

注意到 $k$ 短路径一定不超过 $k$ 短边。

即对于前 $k$ 小的边的所有端点跑一遍多源最短路即可。

注意到 $k \leq 400$，则点数最多为 $2k \leq 800$，时间复杂度 $O(n^3)$ 的 Floyd 完全可行。

PS：记得看数据范围 qwq

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int book[1001][1001], vis[200001], dfn[200001], e[640001];
int n, m, k, cnt;

struct edge {
    int u, v, w;
} ed[200001];

bool cmp(edge a, edge b) {
    return a.w < b.w;
}

signed main() {
    cin >> n >> m >> k;
    memset(book, 0x7f, sizeof(book));
    for (int i = 1; i <= m; i++) cin >> ed[i].u >> ed[i].v >> ed[i].w;
    sort(ed + 1, ed + m + 1, cmp);
    for (int i = 1; i <= min(m, k); i++) {
        if (!vis[ed[i].u]) cnt++, vis[ed[i].u] = 1;
        if (!vis[ed[i].v]) cnt++, vis[ed[i].v] = 1;
    } for (int i = 1, j = 0; i <= n; i++)
        if (vis[i]) dfn[i] = ++j;
    for (int i = 1; i <= min(m, k); i++)
        book[dfn[ed[i].u]][dfn[ed[i].v]] = book[dfn[ed[i].v]][dfn[ed[i].u]] = ed[i].w;
    for (int i = 1; i <= cnt; i++) book[i][i] = 0;
    for (int l = 1; l <= cnt; l++)
        for (int i = 1; i <= cnt; i++)
            for (int j = 1; j <= cnt; j++)
                if ((unsigned long long)book[i][l] + book[l][j] < book[i][j])
                    book[i][j] = book[i][l] + book[l][j];
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++) e[(i - 1) * cnt + j] = book[i][j];
    sort(e + 1, e + cnt * cnt + 1);
    cout << e[2 * k + cnt];
    return 0;
}
```


---

