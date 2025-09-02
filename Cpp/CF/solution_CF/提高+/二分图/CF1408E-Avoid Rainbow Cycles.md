# Avoid Rainbow Cycles

## 题目描述

You are given $ m $ sets of integers $ A_1, A_2, \ldots, A_m $ ; elements of these sets are integers between $ 1 $ and $ n $ , inclusive.

There are two arrays of positive integers $ a_1, a_2, \ldots, a_m $ and $ b_1, b_2, \ldots, b_n $ .

In one operation you can delete an element $ j $ from the set $ A_i $ and pay $ a_i + b_j $ coins for that.

You can make several (maybe none) operations (some sets can become empty).

After that, you will make an edge-colored undirected graph consisting of $ n $ vertices. For each set $ A_i $ you will add an edge $ (x, y) $ with color $ i $ for all $ x, y \in A_i $ and $ x < y $ . Some pairs of vertices can be connected with more than one edge, but such edges have different colors.

You call a cycle $ i_1 \to e_1 \to i_2 \to e_2 \to \ldots \to i_k \to e_k \to i_1 $ ( $ e_j $ is some edge connecting vertices $ i_j $ and $ i_{j+1} $ in this graph) rainbow if all edges on it have different colors.

Find the minimum number of coins you should pay to get a graph without rainbow cycles.

## 说明/提示

In the first test, you can make such operations:

- Delete element $ 1 $ from set $ 1 $ . You should pay $ a_1 + b_1 = 5 $ coins for that.
- Delete element $ 1 $ from set $ 2 $ . You should pay $ a_2 + b_1 = 6 $ coins for that.

You pay $ 11 $ coins in total. After these operations, the first and the second sets will be equal to $ \{2\} $ and the third set will be equal to $ \{1, 2\} $ .

So, the graph will consist of one edge $ (1, 2) $ of color $ 3 $ .

In the second test, you can make such operations:

- Delete element $ 1 $ from set $ 1 $ . You should pay $ a_1 + b_1 = 11 $ coins for that.
- Delete element $ 4 $ from set $ 2 $ . You should pay $ a_2 + b_4 = 13 $ coins for that.
- Delete element $ 7 $ from set $ 3 $ . You should pay $ a_3 + b_7 = 13 $ coins for that.
- Delete element $ 4 $ from set $ 4 $ . You should pay $ a_4 + b_4 = 16 $ coins for that.
- Delete element $ 7 $ from set $ 6 $ . You should pay $ a_6 + b_7 = 13 $ coins for that.

You pay $ 66 $ coins in total.

After these operations, the sets will be:

- $ \{2, 3\} $ ;
- $ \{1\} $ ;
- $ \{1, 3\} $ ;
- $ \{3\} $ ;
- $ \{3, 4, 5, 6, 7\} $ ;
- $ \{5\} $ ;
- $ \{8\} $ .

We will get the graph:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1408E/bc13f574151b20fac566b7dcd07e8e83c002c42d.png)

There are no rainbow cycles in it.

## 样例 #1

### 输入

```
3 2
1 2 3
4 5
2 1 2
2 1 2
2 1 2```

### 输出

```
11```

## 样例 #2

### 输入

```
7 8
3 6 7 9 10 7 239
8 1 9 7 10 2 6 239
3 2 1 3
2 4 1
3 1 3 7
2 4 3
5 3 4 5 6 7
2 5 7
1 8```

### 输出

```
66```

# 题解

## 作者：Karry5307 (赞：15)

### 题意

这一场的都比较难写，就不说了。

$\texttt{Data Range:}1\leq n,m\leq 2\times 10^5$

### 题解

考虑重构一张图。

把元素和集合拆点，对于 $j\in A_i$ 的一个关系连从 $j$ 到 $A_i$ 边权为 $a_i+b_j$ 的边。

注意到原图中有一个彩虹环的话意味着这个图中也会有一个环。

这个结论的话，因为所有的无向边都是连接一个元素和一个集合。并且，如果两个元素 $i$ 和 $j$ 都连向一个集合 $S$ 的话，那么 $i$ 和 $j$ 在一个集合中，相当于在原图中 $i$ 到 $j$ 有边。

同时因为环上任意集合两两不等，任意元素两两不等，那就是说在原图中这些点也构成了一个环而且环上的颜色两两不同，所以不合法。

所以只需要最小化删除的代价让新的图中没有环，最大生成树即可。

### 代码

```cpp
// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
#define PY return (void)puts("Yes")
#define PN return (void)puts("No")
#define P0 return (void)puts("0")
#define P1 return (void)puts("-1")
using namespace std;
// Typedefs
typedef int ll;
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=2e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
struct Node{
	ll v,c,x;
	inline ll operator <(const Node &rhs)const
	{
		return this->v>rhs.v;
	}
};
Node u[MAXN];
ll n,m,tot,kk,p;
li res;
ll x[MAXN],y[MAXN],tag[MAXN],ffa[MAXN];
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
inline ll find(ll x)
{
	return ffa[x]==x?x:ffa[x]=find(ffa[x]);
}
inline ll merge(ll x,ll y)
{
	ffa[find(y)]=find(x);
}
int main()
{
	m=read(),n=read();
	for(register int i=1;i<=m;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		y[i]=read(),ffa[i]=i;
	}
	for(register int i=1;i<=m;i++)
	{
		kk=read();
		for(register int j=0;j<kk;j++)
		{
			p=read(),u[++tot]=(Node){x[i]+y[p],i,p},res+=u[tot].v;
		}
	}
	sort(u+1,u+tot+1);
	for(register int i=1;i<=tot;i++)
	{
		if(!tag[u[i].c])
		{
			tag[u[i].c]=find(u[i].x),res-=u[i].v;
		}
		else
		{
			if(find(tag[u[i].c])!=find(u[i].x))
			{
				merge(tag[u[i].c],u[i].x),res-=u[i].v;
			}
		}
	}
	printf("%lld\n",res);
}
```

---

## 作者：s_r_f (赞：6)

删掉的权值最小，考虑转化为保留的权值最大。

把集合和数字都看成点，集合里有数字就把这个数字往集合连边，求最大生成树即可。

不难发现这个最大生成树的权值可以达到，并且如果出现环，那么必然会有 $rainbow$ $cycle$ . 

证明 : 如果这张图上存在环，那么我们考虑一个环

$x->S_1->y->S_2->z \cdots -> x$ 。

如果这上面有相同的集合，那么就把它们缩起来，这个环显然还是存在的，并且因为有环，所以我们在缩边的时候**一定能保证环内仍然有 $\geq 2$ 个不同的集合.**

$Kruskal$ 即可。

$\Theta((n+m)\log (n+m))$


code :
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(LL x){if (x > 9) write(x/10); putchar(x%10+'0'); }
const int N = 100005;
struct Union_Find_Set{
	int fa[N<<1];
	inline void init(){ for (int i = 1; i <= 200000; ++i) fa[i] = i; }
	inline int Find(int x){ return x == fa[x] ? x : (fa[x] = Find(fa[x])); }
	inline bool Merge(int x,int y){ x = Find(x),y = Find(y); if (x == y) return 0; fa[x] = y;  return 1; }
}S;
int n,m,a[N],b[N]; LL ans;
struct Edge{ int x,y,z; bool operator < (const Edge w) const{ return z > w.z; } }e[N+N]; int le;
int main(){
	int i,t,x;
	S.init();
	read(m),read(n); 
	for (i = 1; i <= m; ++i) read(a[i]);
	for (i = 1; i <= n; ++i) read(b[i]);
	for (i = 1; i <= m; ++i){
		read(t);
		while (t--) ++le,read(x),e[le].x = x,e[le].y = i+n,e[le].z = a[i] + b[x],ans += e[le].z;
	}
	sort(e+1,e+le+1);
	for (i = 1; i <= le; ++i) if (S.Merge(e[i].x,e[i].y)) ans -= e[i].z;
	write(ans),putchar('\n');
	return 0;
}
```

---

## 作者：7KByte (赞：3)

二分图最小生成树。

观察后我们可以建立二分图模型，每个元素对应$X$集合的一个点，每个$A$对应$Y$集合的一个点。

对于集合$A_i$包含元素$x$，我们将元素$x$对应的点和集合$A_i$对应的点连边。这样我们就得到一个二分图。

这道题的关键在于建立这样一个模型。下面我将给出一个证明：对于二分图中的一个环对应原图的一个环。

注意：下文原图的环都是指彩虹环。

对于二分图中的环，一定可以写成$X_1\to Y_1 \to X_2\to Y_2\to \cdots\ X_k\to Y_k\to X_1$。

我们称$X_i\to Y_i\to X_{i+1}$为一步。一步的现实意义是两个集合有一个公共元素。

对于拥有一个公共元素的两个集合，如果存在另一个集合和他们的并集存在两个公共元素，则原图上成环。

显然画个图就能理解。

同时我们观察到如果有两个集合他们存在两个公共元素，原图上也成环。所以拥有一个公共元素的两个集合与它们并集构成的集合本质相同。

这样每一步我们可以将两个集合合并成一个新的集合。

但是如果成环了则发现在最后一步会出现两个集合有两个公共元素，所以在原图上成环。

由此得证在二分图上的环一定对应一个原图上的环。

我们要使得原图没有环，则要使得二分图没有环。我们跑一遍最大生成树，剩下的边一定没有环且权值和最小。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n,m,a[N],b[N],T,fa[N];long long ans;
struct edge{
	int u,v,val;
	bool operator<(const edge o)const{return val>o.val;}
}e[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int main(){
	scanf("%d%d",&m,&n);
	rep(i,1,m)scanf("%d",&a[i]);
	rep(i,1,n)scanf("%d",&b[i]);
	rep(i,1,m){
		int S;scanf("%d",&S);
		rep(j,1,S){
			int x;scanf("%d",&x);
			e[++T].u=i;e[T].v=m+x;e[T].val=a[i]+b[x];ans+=e[T].val;
		}
	}
	rep(i,1,n+m)fa[i]=i;
	sort(e+1,e+T+1);
	//cout<<ans<<endl;
	rep(i,1,T){
		//cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].val<<endl;
		int x=get(e[i].u),y=get(e[i].v);
		if(get(x)!=get(y))fa[x]=y,ans-=e[i].val;
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Lynkcat (赞：2)

如果两个点都在不同的两个集合中，一定是不合法的。

所以我们可以将每个 $a[i]+b[j]$ 类比成一条边，连通 $i$ 集合里其他的点。那么答案就是最大生成树外图中每条边边权之和，因为选大的就能保证剩下的是小的。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define int long long

using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int n,m,a[500005],b[500005],p,tp,tot,now,now1,dis,now2,ans,f[500005];

vector<int>p1[500005];

pair<int,int>c[500005];

bool Cmp(pair<int,int> x,pair<int,int>y)
{
	return a[x.first]+b[x.second]>a[y.first]+b[y.second];
}

int gf(int k)
{
	return (f[k]==k)?k:(f[k]=gf(f[k]));
}

void merge(int x,int y)
{
	f[f[x]]=f[y];
}

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=m;i++) b[i]=read(),f[i]=i;
	for (int i=1;i<=n;i++)
	{
		p=read();
		for (int j=1;j<=p;j++)
		  tp=read(),tot++,c[tot]=make_pair(i,tp);
	}
	sort(c+1,c+tot+1,Cmp);
	for (int i=1;i<=tot;i++)
	{
		now=c[i].first,now1=c[i].second;
		dis=a[now]+b[now1];
		//cout<<now<<" "<<now1<<" "<<dis<<" "<<gf(1)<<" "<<gf(2)<<endl;
		if (p1[now].size()>0)
		{
			now2=p1[now][p1[now].size()-1];
			if (gf(now2)==gf(now1))
			{
				ans+=dis;
			} else
			{
				merge(now2,now1);
				p1[now].push_back(now1);
			}
		} else p1[now].push_back(now1);
	}
	writeln(ans);
}
```

---

## 作者：tommymio (赞：1)

考虑到对于一个集合 $i$ 中 $x<y$ 的元素连边，其实就是在集合 $i$ 中将集合中任意两个数 $x,y$ 连颜色为 $i$ 的边，并且没有重边颜色为 $i$。这样连边的操作是 $O(n^2)$ 的。

由于我们只需要连通性，所以可以将集合 $i$ 中所有数与 $i$ 连颜色为 $i$ 的边，这样如果两个数 $x,y$ 同属一个集合，它们之间能够通过集合 $i$ 连出的边连通：$x\to i\to y$。这样构造出的图与原图连通性一定是一样的。在这个图上不存在环，在原图上也不存在各边颜色不相同的环。

构造出的新图点数为 $n+m$，边数为 $\sum s_i\leq 2\times 10^5$。

所以，我们用最小代价将我们构造出来的这个图变为树即可。总边权和一定，求构造出的新图的生成树边权之和最大即可。代码中使用 $\text{Kruskal}$ 求最大生成树。

```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
struct edge {int x,y,w;} e[200005];
int a[100005],b[100005],fa[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int find(int x) {return fa[x]==x? x:fa[x]=find(fa[x]);}
inline bool cmp(const edge &x,const edge &y) {return x.w>y.w;}
int main() {
	int m=read(),n=read(),tot=0; ll ans=0;
	for(register int i=1;i<=m;++i) a[i]=read();
	for(register int i=1;i<=n;++i) b[i]=read();
	for(register int i=1;i<=m;++i) {
		int s=read();
		for(register int j=1;j<=s;++j) {++tot; e[tot].x=read(); e[tot].y=i+n; ans+=(e[tot].w=a[i]+b[e[tot].x]);}
	}
	std::sort(e+1,e+1+tot,cmp);
	for(register int i=1;i<=n+m;++i) fa[i]=i; 
	for(register int i=1;i<=tot;++i) {
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx!=fy) {ans-=e[i].w; fa[fx]=fy;}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Soulist (赞：1)

我们可以考虑这样构图：

将每个元素作为点，集合作为点，如果元素在集合内那么连接这个元素和集合。

不难发现原图上有环等价于这张图上有环。

我们想要最小化删除的代价，等价于最大化保留的代价，跑最大生成树即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e6 + 5 ;  
int n, m, cnt, Ans, a[N], b[N], fa[N] ; 
struct E {
	int fr, to, w ; 
} e[N] ;
int fd(int x) {
	return (x == fa[x]) ? x : fa[x] = fd(fa[x]) ; 
}
bool cmp( E x, E y ) {
	return x.w > y.w ; 
} 
signed main()
{
	n = gi(), m = gi() ; 
	rep( i, 1, n ) a[i] = gi() ; 
	rep( i, 1, m ) b[i] = gi() ; 
	rep( i, 1, n ) {
		int z = gi(), x ; 
		rep( j, 1, z ) {
			x = gi() ; 
			e[++ cnt] = (E){ i, x + n, a[i] + b[x] } ;
			Ans += (a[i] + b[x]) ; 
		}
	}
	for(int i = 1; i <= n + m; ++ i) fa[i] = i ; 
	sort(e + 1, e + cnt + 1, cmp ) ;
	rep( i, 1, cnt ) {
		int x = e[i].fr, y = e[i].to ; 
		int u = fd(x), v = fd(y) ;
		if( u == v ) continue ; 
		fa[u] = v, Ans -= (e[i].w) ;
	}
	cout << Ans << endl ; 
	return 0 ;
}
```

---

## 作者：kouylan (赞：0)

我们要来重构一下这张图。

我们把点和集合都当做点。如果点 $x$ 在集合 $i$ 中，我们可以把点 $x$ 和集合 $i$ 之间连上 $a_i+b_x$ 的边。这样我们发现，原图上没有彩虹环，等价于重构出来的图上没有环。

我们来简要证明一下这件事。如果原图中有一条 $x$ 到 $y$ 颜色为 $i$ 的边，在重构图上就相当于从点 $x$ 走到集合 $i$ 再走到 $y$。那彩虹环就相当于重构图上用点和不同集合连成的简单环。

因此，我们要做的就是删边使得重构图上没有环。只要跑一遍最大生成树即可。

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,m,cnt,a[100005],b[100005],ans;
int dsu[200005],vis[400005];
struct edge{
	int x,y,z;
	bool operator < (const edge b)
	{
		return z>b.z;
	}
}e[400005];

int find_(int x)
{
	return x==dsu[x] ? x : dsu[x] = find_(dsu[x]);
}

void kruskal()
{
	for(int i=1;i<=n+m;i++)
		dsu[i] = i;
	sort(e+1,e+1+cnt);
	int sum=0;
	for(int i=1;i<=cnt;i++)
	{
		int x=find_(e[i].x),y=find_(e[i].y);
		if(x!=y)
		{
			dsu[y] = x;
			vis[i] = 1;
			if((++sum)==n+m-1)
				break;
		}
	}
}

signed main()
{
	cin>>m>>n;
	for(int i=1;i<=m;cin>>a[i++]);
	for(int i=1;i<=n;cin>>b[i++]);
	for(int i=1,s;i<=m&&cin>>s;i++)
	{
		for(int j=1,x;j<=s&&cin>>x;j++)
			e[++cnt] = (edge){x,i+n,a[i]+b[x]};
	}
	kruskal();
	for(int i=1;i<=cnt;i++)
		if(!vis[i])
			ans += e[i].z;
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：FjswYuzu (赞：0)

这种题做的太少了，想了半天。

将删除最少变成保留最多。暴力思路是将边建出来，保留最多即为求最大生成树边权和，用总权值减去，但边太多了。

我们还是没有好的解决方案，需要进一步对题目进行转化。

注意到元素和元素之间连边是非常不优秀的。考虑对集合建一个虚点，元素 $j$ 向集合虚点 $i$ 连边，边权即为 $a_i+b_j$。

这个转化和原问题是等价的，我们还是不想让其出现环。这个时候边权已经降到了 $O(\sum s_i)$ 的级别。保留最多即为求最大生成树边权和，套用上面的方法就过掉了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(LL x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
struct unionFindSet{
	LL fa[200005];
	void makeSet(LL up){for(LL i=0;i<=up;++i)	fa[i]=i;}
	LL findSet(LL x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	bool unionSetb(LL x,LL y)
	{
		LL xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return false;
		return fa[yy]=xx,true;
	}
}ufs;
struct Edge{
	LL u,v,w;
	Edge(){}
	Edge(LL U,LL V,LL W){u=U,v=V,w=W;}
	bool operator < (Edge ano) const {return w>ano.w;}
}ed[200005];
LL n,m,a[100005],b[100005],cnt;
LL Kruskal(LL p)
{
	ufs.makeSet(p);
	sort(ed+1,ed+1+cnt);
	LL ans=0;
	for(LL i=1;i<=cnt;++i)
	{
		LL u=ed[i].u,v=ed[i].v,w=ed[i].w;
		if(ufs.unionSetb(u,v))	ans+=w;
	}
	return ans;
}
int main(){
	n=read(),m=read();
	for(LL i=1;i<=n;++i)	a[i]=read();
	for(LL i=1;i<=m;++i)	b[i]=read();
	LL sum=0;
	for(LL i=1;i<=n;++i)
	{
		LL p=read();
		for(LL j=1;j<=p;++j)
		{
			LL x=read();
			sum+=a[i]+b[x];
			ed[++cnt]=Edge(i,n+x,a[i]+b[x]);
		}
	}
	write(sum-Kruskal(n+m));
	return 0;
}
```

---

## 作者：VenusM1nT (赞：0)

考虑从集合向集合中的元素连边，发现不合法情况必然包含环，因为此时成环的若干个元素点在不同集合中的颜色不同，所以最后一定会形成 rainbow。于是考虑以最小代价去掉这些环，因为原图不一定连通，可能由若干连通块组成，于是考虑跑最大生成树，用权值和减去最大保留即得到最小删除。

```cpp
#include<bits/stdc++.h>
#define N 500000
#define reg register
#define inl inline
using namespace std;
struct Edge
{
	int u,v,w;
	friend bool operator < (const Edge &x,const Edge &y)
	{
		return x.w>y.w;
	}
}e[N+5];
int m,n,a[N+5],b[N+5],tot,f[N+5],sum;
long long ans;
int Find(reg int x)
{
	return x==f[x]?x:f[x]=Find(f[x]);
}
inl void Kruskal()
{
	for(reg int i=1;i<=N;i++) f[i]=i;
	sort(e+1,e+tot+1);
	for(reg int i=1;i<=tot;i++)
	{
		reg int x=Find(e[i].u),y=Find(e[i].v);
		if(x^y)
		{
			ans-=1ll*e[i].w;
			f[x]=y;
		}
	}
}
int main()
{
	scanf("%d %d",&m,&n);
	for(reg int i=1;i<=m;i++) scanf("%d",&a[i]);
	for(reg int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(reg int i=1;i<=m;i++)
	{
		reg int x;
		scanf("%d",&x);
		while(x--)
		{
			reg int y;
			scanf("%d",&y);
			e[++tot]=((Edge){i,y+m,a[i]+b[y]});
			ans+=a[i]+b[y];
		}
	}
	Kruskal();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：RedLycoris (赞：0)

考虑构图。

对于集合 $i$，如果有 $j$ 的话，对$i$号节点向 $m+j$ 号节点连一条边权为 $a_i+b_j$的边。

由于题目要求说是无还，所以对这张新图跑最大生成树即可。（不是树必然有环）

最大生成树就是将最小生成树 Kruskal 中每次取出边权最小的边改为最大的边即可，

Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ld long double
using namespace std;
const int mxn=4e5+5;
vector<int>g[mxn];
int n,m;
int a[mxn],b[mxn];
vector<pair<ll,pair<int,int> > >edges;
int f[mxn];
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void uni(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)f[x]=y;
}
ll tot,ans;
inline void solve(){
	cin>>m>>n;
	for(int i=1;i<=n+m;++i)f[i]=i;
	for(int i=1;i<=m;++i)cin>>a[i];
	for(int i=1;i<=n;++i)cin>>b[i];
	for(int i=1;i<=m;++i){
		int x,u;cin>>x;
		for(;x--;){
			cin>>u;
			edges.push_back({a[i]+b[u],{i,m+u}});//建边
			tot+=a[i]+b[u];
		}
	}
	sort(edges.rbegin(),edges.rend());
	for(int tt=0;tt<edges.size();++tt){ //最大生成树（最大能保留的边的权值和）
		pair<ll,pair<int,int> >p=edges[tt];
		int x=p.second.first,y=p.second.second;
		if(find(x)==find(y))continue;
		uni(x,y);
		ans+=p.first;
	}
	cout<<tot-ans<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

