# Vulnerable Kerbals

## 题目描述

给出两个整数 $n, m$，在给出一个大小为 $n$ 的集合 $B$，且 $\forall y \in B$ 有 $0 \leq y < m$。现要求构造一个序列 $A$，满足以下条件：

- $\forall x \in A$ 有 $0 \leq x < m$。
- $\forall i, j, 1 \leq i, j \leq |A|$， 有 $\prod \limits _{k = 1}^{i}A_k \not\equiv \prod \limits _{k = 1}^{j}A_k \pmod m$
- $\forall i, y, 1 \leq i \leq |A|, y \in B$， 有 $\prod \limits _{k = 1}^{i}A_k \not\equiv y \pmod m$

在序列 $A$ 合法的条件下满足长度最大化，并给出一种构造方案。

## 说明/提示

$0 \leq n, m \leq 2 \times 10^5$。

## 样例 #1

### 输入

```
0 5
```

### 输出

```
5
1 2 4 3 0
```

## 样例 #2

### 输入

```
3 10
2 9 1
```

### 输出

```
6
3 9 2 9 8 0
```

# 题解

## 作者：Soulist (赞：5)


考虑固定前缀积，假设前缀积$\% m$互不相同且不重复出现，则有对于第$i$个前缀积，假设其值为$a$，$i+1$为$b$则有第$i+1$个数为：$\dfrac{b}{a}$

然而由于$m$不是一个质数，这个式子在$\% m$意义下总是没有意义的

考虑欧几里得算法，我们有：$a\times k\% m=b$，即：$ak+mx=b(x<0)$，其中$k$为第 $i+1$ 位填入的数

假设$gcd(a,m)$不整除$b$由裴蜀定理显然无解，否则存在一个方案填入一个数使得$a\to b$

于是对于一个数$a$，假设其与$m$不互质，则其可以前往任何一个数，否则假设其与$m$的$gcd$为$p$则其能前往且仅能前往$p$的倍数

考虑暴力连边，假设 $a$ 能前往 $b$ 则我们连一条$a\to b$的边，这样连边量为$O(n^2)$于是问题转化为：给定一张图，求其中不重复经过点的最长路，值得注意的是边权长度为$1$

考虑$gcd$的性质，假设$gcd(a,m)=k$则有$a|k$

考虑缩点，假设$e$个点$gcd(x,m)=w$则将其所至一点，显然这些点出边相同且彼此可达所以这样做不会影响正确性

容易发现缩完点后所有的连边必然是从$gcd$小的连向大的，所以图是一张$DAG$，问题变成给定一张DAG求图上带权最长路

显然可以dp了不是吗qwq，这样确定了前缀积之后，还原序列通过拓展欧几里得实现，整体复杂度$O(m\log m)$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ;
int n, m, cnt, top, vis[N], s[N], w[N] ;
int head[N], deg[N], a[N], dp[N], go[N] ; 
vector<int> f[N] ;
struct E {
	int to, next ; 
} e[N * 16] ;
int gcd( int a, int b ) {
	return ( a == 0 ) ? b : gcd( b % a, a ) ;
}
int ax, ay ; 
int exgcd( int a, int b ) {
	if( a == 0 ) {
		ax = 0, ay = 1 ; return b ; 
	}
	int k = exgcd( b % a, a ) ;
	int tx = ay - ( b / a ) * ax, ty = ax ;
	ax = tx, ay = ty ; return k ; 
}
void add( int x, int y ) {
	e[++ cnt] = (E){ y, head[x] }, head[x] = cnt ;
}
queue<int> q ; 
void dfs( int x ) {
	if( dp[x] ) return ; dp[x] = w[x] ; 
	Next( i, x ) {
		int v = e[i].to ; dfs(v) ;
		if( dp[x] < dp[v] + w[x] ) dp[x] = dp[v] + w[x], go[x] = v ; 
	}
}
signed main()
{	
	n = gi(), m = gi() ; int x ; 
	rep( i, 1, n ) x = gi(), vis[x] = 1 ; 
	for( re int i = 1; i < m; ++ i ) {
		if( vis[i] ) continue ;
		int k = gcd( i, m ) ; f[k].push_back(i), ++ w[k] ; 
		if( s[k] ) continue ; s[k] = 1 ; 
		for( re int j = 2 * k; j < m; j += k ) add( k, j ), ++ deg[j] ;
	}
	for( re int i = 1; i < m; ++ i ) if( s[i] && !deg[i] ) q.push(i) ;
	int Id = 0, ans = 0 ;
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ; dfs(u) ;
		if( ans < u ) ans = dp[u], Id = u ;
	}
	for( re int i = Id; i; i = go[i] )
	for( re int j = 0; j < f[i].size(); ++ j ) a[++ top] = f[i][j] ; 
	if( !vis[0] ) a[++ top] = 0 ; printf("%d\n", top ) ;
	if( top == 0 ) exit(0) ; printf("%d ", a[1] ) ;
	for( re int i = 2; i <= top; ++ i ) {
		if( a[i] == 0 ) printf("%d\n", a[i] ) ;
		else {
			int k = exgcd( a[i - 1], m ), dx = m / k, tp = a[i] / k ; 
			while( ax < 0 ) ax += dx ; ax %= dx ; 
			ax = ax * tp, printf("%d ", ax % m ) ;
		}
	}
	return 0 ;
}
```

---

## 作者：Lily_White (赞：4)

这是一道将数学和DP结合的很好的题目。

如果目前的乘积为$a$，且我们能够选择一个数$x$，按照
$$ax \equiv b(\text{mod } m)$$
得到下一个数，那么我们就在$a$ 和$b$之间连一条有向边。

如果
$$\exists x \Rightarrow ax \equiv b (\text{mod } m)$$

那么

$$\exists x,y \Rightarrow ax-my=b$$
利用[扩展欧几里得算法](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
我们可解出$a$和$b$.

但是直接这样做是不能进行DP的，因为a)点数太多，b)有环，因此需要考虑如何消去图中的环。

为了减少点的数量，首先我们证明一个引理。

**引理**:对于不定方程
$$ax+by=c$$
，如果$d=\gcd(a,b)\mid c$，那么这个不定方程有整数解，否则，这个不定方程无整数解

**证明**:假设$x,y\in \mathbf{Z}$，$\because d\mid a, d\mid b, \therefore d\mid c$.因此若$d$不整除$c$，那么方程无解。

否则，由贝祖定理知$\exists s,t \in \mathbf{Z}$，使
$$as+bt=d$$
$\because d \mid c,\therefore \exists q\Rightarrow c=dq.$

因此

$$a(sq)+b(tq)=c$$

则$x=sq,y=tq$是一组解。证毕。

因此，如果要这个不定方程有解，则必有$d=\gcd(a,m) \mid b$， 则
$$d\mid a, d\mid b, d\mid m$$
因此，
$$d\mid b, d\mid m$$
因此，
$$\gcd(b,m)=d$$
这就说明，在本题建图的意义下，
$$\gcd(i,m)\Leftrightarrow\gcd(j,m)$$
利用这一点，我们就可以大幅度减少点的数量，而下面就是DAG上的最长路的模板了。

需要注意的是，本题需要输出方案，因此在我的代码中使用了`std::vector`来记录方案，最后利用同余式和扩展欧几里得解出真正答案（实际上就是乘法逆元）。

代码如下，注意第$46-49$行有减少点数的操作过程。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
using LL = long long;
using ULL = unsigned long long;
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
#define until(x) while (!x)
#define int long long
#define fail(s) assert(!s)
const int INF = 0x3f3f3f3f;
const int EPS = 1e-6;
int m, n;
const int N = 200020;
int lim[N];
vector <int> G[N];
#define from first
#define to second
int vis[N], dp[N], path[N];
int exgcd(int a,int b, int &x, int &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return d;
}
signed main()
{
	ios::sync_with_stdio(false);
//	freopen("output.txt", "w", stdout);
	cin >> n >> m;
	if (n){
		rep(i, n) {
			int x;
			cin >> x;
			lim[x] = true;
		}
	}
	rep(u, m) {
		if (lim[u])continue;
		G[__gcd(u, m)].pb(u);
	}
	if (lim[0])G[m].pb(0);
	memset(dp, 0, sizeof(dp));
	rep(i, m + 1) {
		if (i == 0)continue;
		if (!G[i].empty()) {
			dp[i] = 0;
			path[i] = 0;
			rep (j, i) {
				if (j == 0)continue;
				if (i % j == 0 && dp[j] > 0) {
					if (dp[j] > dp[i]) {
						dp[i] = dp[j];
						path[i] = j;
					}
				}
			}
			dp[i] += G[i].size();
		}
	}
	vector <int> ans;
	int x = m;
	while (!G[x].empty()) {
		for (auto y:G[x])ans.pb(y);
		x = path[x];
	}
	reverse(ans.begin(), ans.end());
	if (lim[0])ans.pop_back();
	cout << ans.size() << endl;
	int cur = 1;
	for (auto i:ans) {
		int x, y;
	//	cur = i;
		int d = exgcd(cur, m, x, y);
		cout << ((x * i / d) % m + m) % m << ' ';
		cur = i;
	}
	return 0;
}
```

---

## 作者：木xx木大 (赞：3)

[CF772C Vulnerable Kerbals](https://www.luogu.com.cn/problem/CF772C)

如果 $i$，$j$ 在前缀积中连续出现，则有 $ix\mod m=j \rightarrow  ix+my=j$。根据裴蜀定理，这个方程有解当且仅当 $gcd(i, m) | j$。将前缀积看作点，$i$，$j$ 之间有一条边当且仅当 $gcd(i, m) | j$。这样连出来的边个数是 $O(n^2)$ 级别的，显然过不去。

容易发现两个值 $i$ , $j$ 若满足 $gcd (i, m) = gcd (j, m)$，则两个点在一个 SCC 中。我们把满足条件的 SCC 缩点，与$m$ 的 $gcd$ 相同的 $i$ 缩为一个点，可以用 vector 存有哪些数，那么整幅图变成了 DAG，一条边 $(i, j)$ 的连接方向是 $gcd(i, m) | gcd(j, m)$。题目变成求 DAG 的带权最长链（其中点权是 SCC 的大小），dp 的同时记一下路径即可。之后按照路径用 exgcd 还原每个点的值，复杂度 $O(m \log m)$。

具体实现时，并不需要把图建出来，只需要模拟 DAG 上 dp 的过程，用 $i$ 向 $i$ 的倍数 $j$ （$j|m$） 贡献即可。对于 $n$ 个不能出现的数，我们只需要在处理到它时直接 continue 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int n,m,w[N],vis[N],dp[N],pre[N],cnt;
vector<int> g[N];
ll exgcd(ll &x,ll &y,ll a,ll b)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	ll g=exgcd(x,y,b,a%b);
	ll t=x;
	x=y;
	y=t-a/b*y;
	return g;
}
ll getans(ll a,ll b)
{
	ll x,y;
	ll c=exgcd(x,y,a,m);
	ll tmp=m/c;
	x=(x*b/c%tmp+tmp)%tmp;
	return x;
}
int main()
{
	ll x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x);
		vis[x]=1;
	}
	for(int i=0;i<m;i++)
		if(!vis[i])g[exgcd(x,y,(ll)i,(ll)m)].push_back(i);
	for(int i=1;i<=m;i++)
	{
		if(m%i)continue;
		dp[i]+=g[i].size();
		for(int j=i+i;j<=m;j+=i)
		{
			if(m%j)continue;
			if(dp[j]<=dp[i])
			{
				dp[j]=dp[i];
				pre[j]=i;
			}
		}
	}
	int now=m;
	while(1)
	{
		for(int i=0;i<(int)g[now].size();i++)
			w[cnt++]=g[now][i];
		if(now==1)break;
		now=pre[now];
	}
	printf("%d\n",cnt);
	printf("%d ",w[cnt-1]);
	for(int i=cnt-1;i;i--)
		printf("%lld ",getans(w[i],w[i-1]));
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

题意：给一个m,n，再给你一个m个数的集合让你构造一个序列满足以下的条件：

1.这个序列的所有数都在0-m-1之间（含）

2.这个数列的所有前缀积都不同

3.所有的前缀积都不能出现在给你的集合中

4.最大化这个序列的长度

输出任意满足条件的序列。

首先，如果，目前的乘积为a,乘上一个数x模m后为下一个数b
即ax%m=b

要使这个方程有解，需要满足gcd(a,m)=gcd(b,m)解x=b/a%m

因为费马小定理要求m为质数，所以在本题中，逆元得这么求：

a^-1=a^(φ(m-1))

我们可以对于任何a,b满足gcd(a,m)|gcd(b,m)连一条有向边，然后就可以将此问题转化成一张图的最长路问题

但是最长路要求无环，但本题中有环，而且n<=2e5边数太多

我们发现，所有所有gcd(x,m)相同的数，连得边都是一模一样的，因此，我们可以缩点，缩点时把集合中的数删掉，缩完点后，图就变成了一个DAG(有向无环图)，直接进行dp即可,dp时要开一个数组记录路径。

（一道数论+图论题）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int w[N],chk[N],d[N],path[N],res[N],k,n,cnt,phi;
vector<int>g[N];
int Pow(int a,int b)
{
	int r=1;
	while(b)
	{
		if(b&1)
			r=1ll*r*a%n;
		a=1ll*a*a%n;
		b>>=1;
	}
	return r;
}
int Get(int a,int b)
{
	int g=__gcd(a,b);
	a/=g;
	b/=g;
	return 1ll*b*Pow(a,phi-1)%n;
}
int main()
{
	scanf("%d%d",&k,&n);
	phi=n;
	int tn=n;
	for(int i=2;i<=n;i++)
	{
		if(tn%i==0)
		{
			phi=phi/i*(i-1);
			while(tn%i==0)
				tn/=i;
		}
	}
	for(int i=1;i<=k;i++)
	{
		int a;
		scanf("%d",&a);
		chk[a]=1;
	}
	for(int i=0;i<n;i++)
		if(!chk[i])
			g[__gcd(i,n)].push_back(i);
	for(int i=1;i<=n;i++)
	{
		if(n%i)
			continue;
		d[i]+=g[i].size();
		for(int j=i+i;j<=n;j+=i)
		{
			if(n%j)
				continue;
			if(d[j]<=d[i])
			{
				d[j]=d[i];
				path[j]=i;
			}
		}
	}
	int a=n;
	while(1)
	{
		for(int i=0;i<g[a].size();i++)
			w[cnt++]=g[a][i];
		if(a==1)
			break;
		a=path[a]; 
	}
	printf("%d\n",cnt);
	printf("%d ",w[cnt-1]);
	for(int i=cnt-1;i>0;i--)
		printf("%d ",Get(w[i],w[i-1]));
	return 0;
}

```

---

