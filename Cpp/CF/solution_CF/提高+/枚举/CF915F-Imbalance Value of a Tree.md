# Imbalance Value of a Tree

## 题目描述

给定一棵树，每个顶点都被写上了一个数，第 $i$ 个顶点写上的数是 $a_i$。定义一个函数 $I(x,y)$ 表示从顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值和最小值的差。

你要求出 $\sum_{i=1}^{n}\sum_{j=i}^{n}I(i,j)$。

## 样例 #1

### 输入

```
4
2 2 3 1
1 2
1 3
1 4
```

### 输出

```
6
```

# 题解

## 作者：lottle1212 (赞：20)

# [原题传送门](https://www.luogu.com.cn/problem/CF915F)
## Part0：
首先解读一下题目。

- 给出一颗 $N(1 \leq N \leq 10^{6})$ 个节点的树。
- 定义 $\operatorname{I}(x, y)$ 表示顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值和最小值的差。
- 求出 $\sum_{i = 1}^{n}\sum_{j = 1}^{n} \operatorname{I}(i, j)$。

## Part1：
这是一道**并查集**模板题。

首先，对于式子 $\sum_{i = 1}^{n}\sum_{j = 1}^{n} \operatorname{I}(i, j)$，我们可以分解成：

$$\sum_{i = 1}^{n}\sum_{j = 1}^{n}\max(i, j) - \sum_{i = 1}^{n}\sum_{j = 1}^{n}\min(i, j)$$

其中，$\max(x, y)$ 表示顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值，$\min(x, y)$ 表示其中的最小值。

对于 $\sum_{i = 1}^{n}\sum_{j = 1}^{n}\max(i, j)$，我们首先要明白当 $a_k$ 作为 $\max(i, j)$ 时，$a_k$ 必须是 $i$ 到 $j$ 的路径中所有节点权值的最大值。由此，我们可以想到按照边权大小对边进行升序排序，从低到高对每一条边的两边 $x, y$ 进行合并，并求出通过此边的路径数量 $(sz_x \times sz_y)$，累计贡献 $(sz_x \times sz_y \times \max(a_x, a_y))$。注意，这里边的权值**为边两端节点权值的较大值**。

**最小值**求法同上。

**AC Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,fx,fy,ans,w[1000010],sz[1000010],f[1000010];
struct node{long long x,y,w;}e[1000010];
bool cmp0(node x,node y){return x.w<y.w;}
bool cmp1(node x,node y){return x.w>y.w;}
long long get_fa(long long x){
	if(x==f[x]) return x;
	return f[x]=get_fa(f[x]);
}//并查集求祖先
void init(bool op){
	long long i;
	for(i=1;i<=n;i++) f[i]=i,sz[i]=1;//并查集初始化
	for(i=1;i<n;i++) e[i].w=(op?min(w[e[i].x],w[e[i].y]):max(w[e[i].x],w[e[i].y]));//求出边权
	sort(e+1,e+n,(op?cmp1:cmp0));//进行排序
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++) cin>>w[i];
	for(i=1;i<n;i++) cin>>e[i].x>>e[i].y;
	init(0);//初始化，对边进行升序排序
	for(i=1;i<n;i++){
		fx=get_fa(e[i].x),fy=get_fa(e[i].y); //边的左右部分
		ans+=sz[fx]*sz[fy]*e[i].w,sz[fx]+=sz[fy],f[fy]=fx;//计算贡献，并合并边的左右部分
	}
	init(1);//降序
	for(i=1;i<n;i++){
		fx=get_fa(e[i].x),fy=get_fa(e[i].y);
		ans-=sz[fx]*sz[fy]*e[i].w,sz[fx]+=sz[fy],f[fy]=fx;
	}//同上
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：Karry5307 (赞：19)

### 题意

给一棵 $n$ 个点的树，点有点权，设 $\max(x,y)$ 表示 $x$ 到 $y$ 路径中所有点的点权最大值，$\min(x,y)$ 表示路径上点权的最小值，求：

$$\sum\limits_{i=1}^{n}\sum
\limits_{j=i+1}^{n}(\max(i,j)-\min(i,j))$$

$\texttt{Data Range:}1\leq n\leq 10^6$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13862710.html)

简单题。

将这个式子拆成两个，一个是所有的 $\max$，另一个是所有的 $\min$，然后分开求解。首先讨论 $\max$。

如果是边权的话可以按照边权从小到大加边合并联通块。对于一条边 $(u,v,w)$ 来说，它对答案的贡献是 $w\times sz_u\times sz_v$，用并查集维护连通块的大小即可 $O(n\log n)$ 完成。

但是因为这个题是点权就不行，需要转化成边权。一个常见的 trick（但是我今天第一次接触到）是将连接 $u$ 和 $v$ 的边的边权变成 $u,v$ 两点点权的最大值，因为与一个数多次取 $\max$ 并不会改变最终结果。

对于 $\min$ 来说也是一样的，于是这个题就做完了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e6+51;
struct Edge{
	ll from,to,mn,mx;
	inline bool operator <(const Edge &rhs)const
	{
		return mn>rhs.mn;
	}
	inline bool operator >(const Edge &rhs)const
	{
		return mx<rhs.mx;
	}
};
Edge ed[MAXN];
ll n,from,to;
li mx,mn;
ll x[MAXN],ffa[MAXN],sz[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
    	neg=-1;
    	ch=getchar();
	}
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll find(ll x)
{
	return x==ffa[x]?x:ffa[x]=find(ffa[x]);
}
inline void merge(ll x,ll y)
{
	ll fx=find(x),fy=find(y);
	fx!=fy?ffa[fy]=fx,sz[fx]+=sz[fy],sz[fy]=0:1;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),ffa[i]=i,sz[i]=1;
	}
	for(register int i=1;i<n;i++)
	{
		from=read(),to=read();
		ed[i]=(Edge){from,to,min(x[from],x[to]),max(x[from],x[to])};
	}
	sort(ed+1,ed+n);
	for(register int i=1;i<n;i++)
	{
		mn+=(li)sz[find(ed[i].from)]*sz[find(ed[i].to)]*ed[i].mn;
		merge(ed[i].from,ed[i].to);
	}
	sort(ed+1,ed+n,greater<Edge>());
	for(register int i=1;i<=n;i++)
	{
		ffa[i]=i,sz[i]=1;
	}
	for(register int i=1;i<n;i++)
	{
		mx+=(li)sz[find(ed[i].from)]*sz[find(ed[i].to)]*ed[i].mx;
		merge(ed[i].from,ed[i].to);
	}
	printf("%lld\n",mx-mn);
}
```

---

## 作者：RainFestival (赞：8)

我们首先~~显然的套路的~~，$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n} I(i,j)$

$=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n} \max(i,j)-\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n} \min(i,j)$

则我们可以分别求出两部分内容。

假设我们现在是边权，不是点权，那么我们可以使用并查集 $\tt{dsu}$。

具体这么做:

假设我们正在求最大值，我们可以算出每一条边的贡献 $=w\times\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n} f(i,j)$

$w$ 是边权，$f(i,j)$ 是一个 $01$ 变量，**代表** $i$ **到** $j$ **的路径上的最大值是否是这一条边贡献的。**

我们考虑从小到大加入每一条边，设当前加入的边是 $(x,y,w)$ ,那么原先加入的每一条边都没有它大，所以我们合并 $x$ 与 $y$ 所在的连通块，**并加入** $w\times s_x\times s_y$ **的贡献**，其中 $s_i$ 表示 $i$ 所在的连通块大小。

为什么呢？

因为在 $x$ 的连通块内任选一个点 $p$ , 在 $y$ 的连通块内任选一个点 $q$ ,则 $p,q$ 之间的**唯一路径一定经过这一条边**，而这一条边是当前全图中最大的。

回到题目，现在我们是点权，所以我们可以**化点为边**，边 $(x,y)$ 的权值 $=\max(w_x,w_y)$ , 其中 $w_i$ 表示 $i$ 点点权。

最小值类似，只不过边权变成两点点权最小值，并且要从大到小加入每一条边。

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
struct edge
{
	int x,y,m1,m2;
};
std::vector<int> a[1000005];
int n,fa[1000005],sz[1000005],val[1000005];
long long ans=0;
edge f[1000005];
int cmp1(edge x,edge y){return x.m2>y.m2;}
int cmp2(edge x,edge y){return x.m1<y.m1;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	fa[fx]=fy;sz[fy]=sz[fy]+sz[fx];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&val[i]);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&f[i].x,&f[i].y);
		f[i].m1=std::max(val[f[i].x],val[f[i].y]);
		f[i].m2=std::min(val[f[i].x],val[f[i].y]);
	}
	std::sort(f+1,f+n,cmp1);
	for (int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	for (int i=1;i<n;i++)
	{
		int x=f[i].x,y=f[i].y;
		ans=ans-1ll*f[i].m2*sz[find(x)]*sz[find(y)];
		merge(x,y);
	}
	std::sort(f+1,f+n,cmp2);
	for (int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	for (int i=1;i<n;i++)
	{
		int x=f[i].x,y=f[i].y;
		ans=ans+1ll*f[i].m1*sz[find(x)]*sz[find(y)];
		merge(x,y);
	}
	printf("%lld\n",ans);
	return 0;
}
```

然后就可以通过这一道题目了!

upd on 2020.8.10 修改了一些错误

upd on 2021.7.28 修改了一些错误，感谢 [U367991](https://www.luogu.com.cn/user/367991)

---

## 作者：Cry_For_theMoon (赞：7)

ABC D题重题人报道 /cy

所以赛场上九分钟切了 D，四舍五入九分钟切 Edu F？？

题意就不说了。

我们记 $a(i,j)$ 代表点对 $i,j$ 路径上最大值，$b(i,j)$ 为 $i,j$ 路径上最小值。

考虑 $(i,i)$ 点对都是无意义的。所以原题目实际上求的是 $\sum_{i=1}^{n}\sum_{j=i+1}^{n}(a(i,j)-b(i,j))=\sum_{i=1}^{n}\sum_{j=i+1}^n a(i,j) - \sum_{i=1}^n\sum_{j=i+1}^n b(i,j)$。

即求出所有 $a$ 的和，减去 $b$ 的和。考虑 $a$ 和 $b$ 是类似的。我们仅考虑 $a$ 怎么做。

显然套路是从小到大按点权排序，这样，任何两个之前加入的点 $i,j$，同时经过 $u$ 会被统计到贡献，同时 $u$ 和它能到达的任何一个之前加入的点 $v$ ，也能统计到贡献。

所以考虑并查集。多维护一个 $size$ 表示集合大小，多维护一个 $tag$ 表示是否之前被加入。每次加入一个点 $u$ 的时候，遍历所有和 $u$ 相连且 $tag$ 为 $1$ 的点$v$，计算完后合并 $v$ 集合到 $u$ 上。最后把 $u$ 集合的 $tag$ 置为 $1$ 即可。

那么 $b$ 的计算是类似，你甚至根本不需要修改边权。

所以你发现其实根本不用点权转边权。可是题解里没有人说（）

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=1e6+10;
struct Edge{
	ll u,v;
}edge[MAXN*2];
ll first[MAXN],next[MAXN*2],tot;
ll n,ans,fa[MAXN],sz[MAXN],tag[MAXN];
pair<ll,ll>a[MAXN];
il void addedge(ll u,ll v){
	edge[++tot]=(Edge){u,v};
	next[tot]=first[u];first[u]=tot;
}
void clear(){
	rep(i,1,n){
		fa[i]=i;
		sz[i]=1;
		tag[i]=0;
	}
}
int Find(int x){
	if(fa[x]==x)return x;
	return fa[x]=Find(fa[x]);
}
int main(){
	scanf("%lld",&n);
	rep(i,1,n){
		scanf("%lld",&a[i].fr);
		a[i].se=i;
	}
	rep(i,1,n-1){
		ll u,v;
		scanf("%lld%lld",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	sort(a+1,a+1+n);
	clear();
	rep(i,1,n){
		int u=a[i].se;
		ll cnt=0,w=a[i].fr;
		for(int j=first[u];j;j=next[j]){
			ll v=edge[j].v;
			if(tag[Find(v)]==0)continue;
			ans+=w*sz[Find(v)];
			ans+=w*cnt*sz[Find(v)];
			cnt+=sz[Find(v)];
			sz[Find(u)]+=sz[Find(v)];
			fa[Find(v)]=Find(u);
		}
		tag[Find(u)]=1;
	}
	clear();
	per(i,n,1){
		int u=a[i].se;
		ll w=a[i].fr,cnt=0;
		for(int j=first[u];j;j=next[j]){
			ll v=edge[j].v;
			if(tag[Find(v)]==0)continue;
			ans-=w*sz[Find(v)];
			ans-=w*cnt*sz[Find(v)];
			cnt+=sz[Find(v)];
			sz[Find(u)]+=sz[Find(v)];
			fa[Find(v)]=Find(u);
		}
		tag[Find(u)]=1;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：DengDuck (赞：7)

首先 $I(i,j)$ 不好求，将式子拆开

$$
\sum_{i=1}^n \sum_{j=i}^n \max(i,j)-\sum_{i=1}^n \sum_{j=i}^n \min(i,j)
$$

因为自己到自己不需要走边，也就是最大边为 0，所以可以再化简

$$
\sum_{i=1}^n \sum_{j=i+1}^n \max(i,j)-\sum_{i=1}^n \sum_{j=i+1}^n \min(i,j)
$$

现在看起来好做多了,两边分开求解

这里只讲 $\sum\limits_{i=1}^n \sum\limits_{j=i+1}^n \max(i,j)$ 的求法，因为两者做法差不多

容易想到计算每一条边的贡献，一条边的贡献只和比自己小的边有关

容易想到排序

接下来只和连通块大小有关了，容易想到使用并查集

容易想到边 $(u,v,w)$ 的贡献的计算方式 $w\times sz_u\times sz_v$

- $u,v$ 表示边上两点
- $w$ 表示边权
- $sz_x$ 表示 $x$ 所在连通块的大小

看起来没问题了......欸？边权？题目给的不是点权吗？

这个并不难，无论发生了什么，这里要感谢 某位有实力的 HN OIer ,他的想法很好

容易发现边权可以是相连两点点权最大值

以上为 $\sum\limits_{i=1}^n \sum\limits_{j=i+1}^n \max(i,j)$ 的做法， $\sum\limits_{i=1}^n \sum\limits_{j=i+1}^n \min(i,j)$ 的做法差不多，容易求出

容易打出以下代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
    ll u,v,w;
}a[5000005];
bool cmp(node x,node y)
{
    return x.w<y.w;
}
bool cmp2(node x,node y)
{
    return x.w>y.w;
}
ll n,fa[5000005],sz[5000005],ans,w[5000005];
ll find(ll x)
{
    if(fa[x]==0)return x;
    return fa[x]=find(fa[x]);
}
inline ll read() {
    char c = getchar();
    int f = 1;
    ll sum = 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') {
        f = -1;
        c = getchar();
    }
    do {
        sum = (sum << 3) + (sum << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    return sum * f;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        sz[i]=1;
        w[i]=read();
    }
    for(int i=1;i<=n-1;i++)
    {
        a[i].u=read(),a[i].v=read();
        a[i].w=max(w[a[i].u],w[a[i].v]);
    }
    sort(a+1,a+n,cmp);
    for(int i=1;i<=n-1;i++)
    {
        ll fx=find(a[i].u),fy=find(a[i].v);
        if(fx!=fy)
        {

            ans+=a[i].w*sz[fx]*sz[fy];
            fa[fy]=fx;
            sz[fx]+=sz[fy];
        }
    }
    memset(fa,0,sizeof(fa));
    for(int i=1;i<=n;i++) sz[i]=1;
    for(int i=1;i<=n-1;i++)
    {
        a[i].w=min(w[a[i].u],w[a[i].v]);
    }
    sort(a+1,a+n,cmp2);
    for(int i=1;i<=n-1;i++)
    {
        ll fx=find(a[i].u),fy=find(a[i].v);
        if(fx!=fy)
        {

            ans-=a[i].w*sz[fx]*sz[fy];
            fa[fy]=fx;
            sz[fx]+=sz[fy];
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：tommymio (赞：5)

拆柿子。

设 $f(i,j)$ 为 $i\to j$ 路径上的点权最大值，$g(i,j)$ 为 $i\to j$ 路径上的点权最小值。则 $I(i,j)$ 显然可以被拆成 $f(i,j)-g(i,j)$。

于是有：

$$ 
\sum_{i=1}^n\sum_{j=i}^n I(i,j)=\sum_{i=1}^n\sum_{j=i}^nf(i,j)-\sum_{i=1}^{n}\sum_{j=i}^ng(i,j)
$$

分别求出 $\sum\sum f(i,j)$ 和 $\sum\sum g(i,j)$ 即可。这两部分的求解思路非常类似，所以我们只需要给出一种求 $\sum\sum f(i,j)$ 的方法就可以解决此题。

如果求解的是路径上的边权最大值似乎很好解决。将树上所有边从小到大排序，每次并查集合并时统计当前这条边 $(x,y,w)$ 对答案的贡献为 $w\times size_{fx}\times size_{fy}$。那我们可以想想如何把点权转化为边权。

利用树上连通性即可。上述并查集的正确性建立在，经过当前这条边 $(x,y,w)$，必然经过它的两个端点，那么这条边对这条路径的贡献一定是它的两个端点的点权之一，即 $\max(a_x,a_y)$。这在点权转边权的题目中是一个非常常见的 $\text{trick}$。

代码实现中使用了一些 $\text{trivial}$ 的 $\text{tricks}$ 减少码量，可读性不是很好（

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
int n,a[1000005],size[1000005],fa[1000005]; ll ans[2];
struct edge {int x,y,w;} e[1000005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline bool cmp(const edge &x,const edge &y) {return x.w<y.w;}
inline void work(int id) {
    for(register int i=1;i<n;++i) {
        if(id==0) e[i].w=max(a[e[i].x],a[e[i].y]);
        else e[i].w=-min(a[e[i].x],a[e[i].y]);
    }
    for(register int i=1;i<=n;++i) fa[i]=i,size[i]=1; std::sort(e+1,e+1+n-1,cmp);
    for(register int i=1,fx,fy;i<n;++i) {
        if((fx=find(e[i].x))!=(fy=find(e[i].y))) {
            ans[id]+=e[i].w*1ll*size[fx]*size[fy]; fa[fx]=fy; size[fy]+=size[fx]; 
        }
    }
}
int main() {
    n=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<n;++i) {e[i].x=read();e[i].y=read();}
    work(0); work(1); printf("%lld",ans[0]+ans[1]); 
    return 0;
}
```

---

## 作者：xuyiyang (赞：4)

#### 题意
给你一棵带点权的树，定义二元函数 $\operatorname I(x,y)$ 表示树上 $x \sim y$ 路径上的点权最大值和最小值的差，让你求 $\sum \limits _ {i = 1} ^ n \sum \limits _ {j = i} ^ n \operatorname I(x,y)$。

#### 分析
首先把式子整理下，首先因为 $\operatorname I(i,i) = 0$，所以可以将其舍去。

因为二元函数 $\operatorname I(x,y)$ 表示树上 $x \sim y$ 路径上的点权最大值和最小值的差。所以可以把  $\operatorname I(x,y)$ 拆成 $\max(x,y) - \min(x,y)$，其中 $\max(x,y)$ 表示 $x \sim y$ 路径上的点权最大值，$\min(x,y)$ 同理为最小值。
那么就可以把式子拆成： $\sum \limits _ {i = 1} ^ n \sum \limits _ {j = i + 1} ^ n \max(x,y) - \sum \limits _ {i = 1} ^ n \sum \limits _ {j = i + 1} ^ n \min(x,y)$。
这就是一个并查集维护全局路径的板子了。

以最大值为例，把 $a \sim b$ 的点权设为 $a,b$ 两点的较大权值，将边权从小到大排序，一次枚举当前边为最大值时的路径条数，为 $\text{Size} \ a \times \text{Size} \ b$。 对答案的贡献就是 $\text{Size} \ a \times \text{Size} \ b \times w_i$，$w_i$ 就是当前边的边权。然后将两个集合合并，计算下一条边。

最小值同理，最后两者相减即答案。

#### Code
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

typedef long long LL;

struct Edge
{
	int a, b, w;
	
	bool operator < (const Edge& t) const
	{
		return w < t.w;
	}
}e[N];

int n, w[N];
int p[N], Size[N];
LL res;

int find(int x) //并查集
{
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
	for (int i = 1; i < n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		e[i] = {a, b};
	}
	
	for (int i = 1; i < n; i ++ ) e[i].w = max(w[e[i].a], w[e[i].b]);
	sort(e + 1, e + n);
	for (int i = 1; i <= n; i ++ ) p[i] = i, Size[i] = 1;
	for (int i = 1; i < n; i ++ )
	{
		int pa = find(e[i].a), pb = find(e[i].b);
		
		if (pa != pb)
		{
			res += (LL)e[i].w * Size[pa] * Size[pb];
			p[pa] = pb; //合并
			Size[pb] += Size[pa];
		}
	}
	
	for (int i = 1; i < n; i ++ ) e[i].w = min(w[e[i].a], w[e[i].b]);
	sort(e + 1, e + n);
	reverse(e + 1, e + n); //从大到小排序
	
	for (int i = 1; i <= n; i ++ ) p[i] = i, Size[i] = 1;
	for (int i = 1; i < n; i ++ )
	{
		int pa = find(e[i].a), pb = find(e[i].b);
		
		if (pa != pb)
		{
			res -= (LL)e[i].w * Size[pa] * Size[pb];
			p[pa] = pb;
			Size[pb] += Size[pa];
		}
	}
	
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

简单题。

$I(x,y) = \max - \min$。

然后单独计算即可。


我们考虑 $\max$ 怎么计算。

这玩意显然可以枚举当前最大值吧。

我们直接枚举一条边，定义这条边的权值是两个的较大的那个。

然后按边权排序从小到大。

从小到大加入边，然后查一下 $x,y$ 这两个连通块的大小，乘法原理即可。因为你加入这条边之后带来的贡献显然就是这俩。

$\min$ 的话就反一下，边权为两者较小，从大到小排序，从大到小加入即可。

---

## 作者：zhaotiensn (赞：4)

首先这题的数据范围是10^6，显然直接用给出的式子暴力跑是不行的，算法复杂度为O（n）或O（n log n）。

因为这题中的I（i，j）表示i到j的简单路径上的最大值减最小值，从原来的式子易得ΣΣ(max()-min())=ΣΣmax()-ΣΣmin(),最大值总和和最小值总和的求法是一样的，所以底下都描述求最小值的算法。

一共有n个点，可以考虑枚举点，统计以这个点为最小节点的路径数量。

先考虑当前边为全图的最短边的情况，显然以这条点为最小节点的为经过它的路径数量，也就是删掉这个点之后的两颗树的节点数量相乘。

给个图会意一下：
![](https://cdn.luogu.com.cn/upload/pic/17537.png )

显然当红色点为最小节点时，所有蓝色的点到达绿色的点的路径都是以红色的点为最小节点。

然后考虑对于每一个点的求出以它为最小节点的子图。于是不难想出正解：

按节点的权值从大到小依次加入图中，以这个节点为最小节点的图就是它所连接的图（因为所以比它小的节点都没有加入，所以只要它能连接到的都是以它为最小的），用并查集维护图中的节点数，每次对答案加上这个节点相连的两张图的节点数之积。时间复杂度为O(n log n)，于是就能水过了。

AC代码：
```
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
    ll x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(ll x){
    write(x);puts("");
}//豪华版快读
#include <cstring>
#include <algorithm>
#define Max 1000005
struct Edge{
    ll v,to;
}e[Max*4];//领接表存边
struct Num{
    ll id,num;
}a[Max];
ll n,l,r,Size,root,minn,maxn,deg[Max],Fa[Max],fa[Max],num[Max],size[Max],head[Max];
bool vis[Max];

inline void add(ll u,ll v){
    e[++Size].v=v;e[Size].to=head[u];head[u]=Size;
}

inline bool cmp(Num x,Num y){
    if(x.num!=y.num)return x.num<y.num;
    else return x.id>y.id;
}//正反跑两遍，一个求最大值之和，一个求最小值之和（好像可以合并成跑一遍）

inline bool cmp2(Num x,Num y){
    if(x.num!=y.num)return x.num>y.num;
    else return x.id>y.id;
}

inline ll find(ll x){
    return fa[x]!=x?fa[x]=find(fa[x]):x;
}//并查集

inline void dfs(ll u){//深搜来建树
    for(ll i=head[u];i;i=e[i].to){
        ll v=e[i].v;
        if(!vis[v]){
            Fa[v]=u;
            vis[v]=true;
            dfs(v);
        }
    }
}

int main(){
    n=read();
    for(ll i=1;i<=n;i++){
        a[i].num=num[i]=read();
        a[i].id=i;
    }
    for(ll i=1;i<n;i++){
        l=read();r=read();
        add(l,r);add(r,l);
        deg[l]++;deg[r]++;
    }
    for(ll i=1;i<=n;i++){
        if(deg[i]==1){
            root=i;
            break;
        }
    }
    Fa[root]=root;vis[root]=true;
    dfs(root);
    sort(a+1,a+n+1,cmp);
    memset(vis,0,sizeof vis);//初始化
    for(ll i=1;i<=n;i++){
        fa[i]=i;
        size[i]=1;
    }
    for(ll i=1;i<=n;i++){//排序后依次加入
        int u=a[i].id;
        vis[u]=true;
        for(ll j=head[u];j;j=e[j].to){
            int v=e[j].v;
            if(vis[v]){
                maxn+=size[u]*size[find(v)]*a[i].num;
                size[u]+=size[find(v)];//并查集维护集合大小
                fa[find(v)]=u;//合并集合
            }
        }
    }
    sort(a+1,a+n+1,cmp2);
    memset(vis,0,sizeof vis);//倒着跑一遍
    for(ll i=1;i<=n;i++){
        fa[i]=i;
        size[i]=1;
    }
    for(ll i=1;i<=n;i++){
        int u=a[i].id;
        vis[u]=true;
        for(ll j=head[u];j;j=e[j].to){
            int v=e[j].v;
            if(vis[v]){
                maxn-=size[u]*size[find(v)]*a[i].num;
                size[u]+=size[find(v)];
                fa[find(v)]=u;
            }
        }
    }
    writeln(maxn);
    return 0;
}
```

---

## 作者：肖然 (赞：1)



```
d1(i,j) = "i->j路径上最大点权"
d0(i,j) = "i->j路径上最小点权"
I(i,j) = d1(i,j) - d0(i,j)

Ans = sum(d1(i,j)) - sum{d0(i,j)}
```

先求sum(d1(i,j))，设边权w(i,j) = max(a[i], a[j])，从小到大加入边，若加入边w时合并了2个联通块，则这条边对sum1的贡献 = w×sz[i]×sz[j]，排序后并查集维护联通和联通块大小sz[]即可。

sum(d0(i,j))同理。

```
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAXN 1000005
#define LL long long
#define INF (1ll<<50)
using namespace std;

int N,M,K;

struct Edge{
    int u,v,w0,w1;
    Edge(int u=0, int v=0, int w0=0, int w1=0):u(u),v(v),w0(w0),w1(w1){}
} eList[MAXN];

int a[MAXN];

bool cmp0(const Edge& e1, const Edge& e2){
    return e1.w0 > e2.w0;
}

bool cmp1(const Edge& e1, const Edge& e2){
    return e1.w1 < e2.w1;
}

int p[MAXN];
LL size[MAXN];

int findR(int x){
    if(p[x]==x) return x;
    else return p[x] = findR(p[x]);
}

int main(){
    ios::sync_with_stdio(0);
    cin>>N;
    for(int i=1;i<=N;i++) cin>>a[i];
    int u,v,w;
    for(int i=1;i<N;i++){
        cin>>u>>v;
        int	w0 = min(a[u], a[v]);
        int w1 = max(a[u], a[v]);
        eList[i] = Edge(u,v,w0,w1);
    }
    
    //
    LL ans1 = 0;
    sort(eList+1, eList+1+(N-1), cmp1);
    for(int i=1;i<=N;i++){
        p[i] = i;
        size[i] = 1;
    }
    
    int ru,rv;
    for(int i=1;i<N;i++){
        u = eList[i].u; v = eList[i].v;
        w = eList[i].w1;
        
        ru = findR(u); rv = findR(v);
        if(ru == rv) continue;
        
        p[ru] = rv;
        ans1 += w*size[rv]*size[ru];
        size[rv] += size[ru];
    }
    
    //
    LL ans0 = 0;
    sort(eList+1, eList+1+(N-1), cmp0);
    for(int i=1;i<=N;i++){
        p[i] = i;
        size[i] = 1;
    }
    
    for(int i=1;i<N;i++){
        u = eList[i].u; v = eList[i].v;
        w = eList[i].w0;
        
        ru = findR(u); rv = findR(v);
        if(ru == rv) continue;
        
        p[ru] = rv;
        ans0 += w*size[rv]*size[ru];
        size[rv] += size[ru];
    }
    cout<<ans1 - ans0;
    return 0;
} 

```

---

## 作者：Forever1507 (赞：0)

%尼塞考了，这个菜鸡不开 long long 见祖宗（）

显然很少有人会真的按题目一条边一条边地算最大最小值，我们可以先统一把最大值算出来减去最小值。

怎么做呢？我们可以参考最小生成树的思路。

以最大值为例，先把边（边权是两端的点权较大者）从小到大排序，再依次插入，确保当前插入的边是目前图中边权最大的。不难发现，当前边的两段分别是两棵树，且左树和右树中任意各取一点的简单路径最大的边就是这条（因为简单路径唯一且当前边最大），那么，设 $siz_u$ 和 $siz_v$ 分别表示边 $i$ 的两段分别所在子树的大小（可以并查集），$w_i$ 是边权，那么贡献就是三者相乘（简单的乘法原理）。

最小值用类似方法求出，相减即可。

**记得开 long long**

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005];
struct node{
	int u,v,w;
}e[1000005];
bool cmp(node a,node b){
	return a.w<b.w;
}
bool _cmp(node a,node b){
	return a.w>b.w;
}
int fa[1000005],siz[1000005];
int find(int x){//并查集 
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void  unionn(int x,int y){
	int _x=find(x),_y=find(y);
	fa[_x]=_y;
	siz[_y]+=siz[_x];
}
signed main(){
	freopen("imbalance.in","r",stdin);
	freopen("imbalance.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>n;
	long long maxn=0,mini=0;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<n;++i){
		cin>>e[i].u>>e[i].v;
		e[i].w=max(a[e[i].u],a[e[i].v]);
	}
	sort(e+1,e+n,cmp);
	for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
	for(int i=1;i<n;++i){
		if(find(e[i].u)==find(e[i].v))continue;
		maxn+=siz[find(e[i].u)]*siz[find(e[i].v)]*e[i].w;
		unionn(e[i].u,e[i].v);
	}
	for(int i=1;i<n;++i){
		e[i].w=min(a[e[i].u],a[e[i].v]);//求最小值，边权也要取小 
	}
	sort(e+1,e+n,_cmp);//从大到小 
	for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;//重置 
	for(int i=1;i<n;++i){
		if(find(e[i].u)==find(e[i].v))continue;
		mini+=siz[find(e[i].u)]*siz[find(e[i].v)]*e[i].w;
		unionn(e[i].u,e[i].v);
	}
	cout<<maxn-mini;
	return 0;
}

```


---

## 作者：raincity (赞：0)

## 分析

模拟赛考了这题，并成功写挂倍增 $\texttt{LCA}$。

步入正题。

首先分析这道题的极差是什么东西，发现就是要求树上每一条简单路径上的点权 $\max-$ 树上每一条简单路径上的点权 $\min$。

显然 $\max$ 和 $\min$ 是对称的，先解决 $\max$，$\min$ 类似。

考虑点的话逃不掉 $\texttt{LCA}$，考虑点权转边权。

对于边 $(u,v)$ ，设它的权值为 $\max(a_u,a_v)$。

按照权值从小到大排序，类似 $\texttt{Kruskal}$ 的想法，并查集维护 $fa$ 和 $siz$。

依次考虑每一条边，假如这条边为 $(u,v,w)$，$su,sv$ 分别为 $u$ 和 $v$ 所在集合的 $siz$，因为到一条边的时候之前的边的权值都不大于当前边的权值，所以这条边贡献 $su\times sv\times w$。然后把 $u$ 和 $v$ 合并即可。

时间复杂度 $O(n\log n)$。
## 解决
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 5;
int n, a[N], fa[N], siz[N];
long long ans, Ans;

struct Edge {
	int u, v, w;
	bool operator <(const Edge &nxt) const { return w < nxt.w; }
}emn[N], emx[N];

static inline int getfa(int x) {
	int px = x, tmp;
	while (fa[x] ^ x) x = fa[x];
	while (px ^ x) tmp = px, px = fa[px], fa[tmp] = x;
	return x;
}

static inline void merge(int x, int y, int w) {
	int fx = getfa(x), fy = getfa(y);
	ans += 1LL * w * siz[fx] * siz[fy];
	if (siz[fx] < siz[fy])
		fa[fx] = fy, siz[fy] += siz[fx];
	else
		fa[fy] = fx, siz[fx] += siz[fy];
}

static inline void read(int &ret) {
	ret = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}

int main() {
	read(n);
	for (register int i = 1; i <= n; i++) read(a[i]);
	for (register int i = 1; i < n; i++) {
		read(emx[i].u), read(emx[i].v);
		emn[i] = emx[i], emx[i].w = max(a[emx[i].u], a[emx[i].v]), emn[i].w = min(a[emn[i].u], a[emn[i].v]);
	}
	sort(emx + 1, emx + n);
	sort(emn + 1, emn + n);
	for (register int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for (register int i = 1; i < n; i++) merge(emx[i].u, emx[i].v, emx[i].w);
	Ans = ans, ans = 0;
    for (register int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for (register int i = n - 1; i; i--) merge(emn[i].u, emn[i].v, emn[i].w);
	cout << Ans - ans << endl;
	return 0;
}

```

---

## 作者：ModestCoder_ (赞：0)

$\sum_{i=1}^{n}\sum_{j=1}^{n}I(i,j)$
$=\sum_{i=1}^{n}\sum_{j=1}^{n}Max(i,j)-\sum_{i=1}^{n}\sum_{j=1}^{n}Min(i,j)$

分别算出两部分的值，考虑并查集合并

对于一条边，这条边连着两个点拥有两个权值，如果我们要计算$Max(i,j)$，那么这条边的权值是两个点中大的那个权值，按照边的权值从小到大排序，然后并查集合并，同时记录两个连通块分别各有多少点

对于求$Max(i,j)$的情况，因为从小到大枚举，保证这条即将连上去的边是当前最大的，所以当前所有有关的路径上的最大值都是自身，所以直接用乘法原理计算就好了

$Min(i,j)$同理，边的权值是两个点中权值较小的那个，然后从大到小排序，差不多的再做一遍

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1000010
#define LL long long
using namespace std;
struct Line{
	int x, y;
	LL l1, l2;
}line[maxn];
LL num[maxn];
int f[maxn], n, a[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp1(Line x, Line y){ return x.l2 < y.l2; }
bool cmp2(Line x, Line y){ return x.l1 > y.l1; }
int getfa(int k){ return f[k] == k ? k : f[k] = getfa(f[k]); }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i < n; ++i){
		int x = read(), y = read();
		line[i].x = x, line[i].y = y;
		line[i].l1 = min(a[x], a[y]), line[i].l2 = max(a[x], a[y]);
	}
	LL ans = 0;
	sort(line + 1, line + n, cmp1);
	for (int i = 1; i <= n; ++i) f[i] = i, num[i] = 1;
	for (int i = 1; i < n; ++i){
		int x = line[i].x, y = line[i].y, s1 = getfa(x), s2 = getfa(y);
	//	printf("%d %d %lld\n", x, y, line[i].l2);
		if (s1 == s2) continue;
		ans += num[s1] * num[s2] * line[i].l2;
		f[s2] = s1, num[s1] += num[s2];
	}
	sort(line + 1, line + n, cmp2);
	for (int i = 1; i <= n; ++i) f[i] = i, num[i] = 1;
	for (int i = 1; i < n; ++i){
		int x = line[i].x, y = line[i].y, s1 = getfa(x), s2 = getfa(y);
	//	printf("%d %d %lld\n", x, y, line[i].l1);
		if (s1 == s2) continue;
		ans -= num[s1] * num[s2] * line[i].l1;
		f[s2] = s1, num[s1] += num[s2];
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

