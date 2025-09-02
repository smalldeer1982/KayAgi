# Polo the Penguin and Trees 

## 题目描述

Little penguin Polo has got a tree — a non-directed connected acyclic graph, containing $ n $ nodes and $ n-1 $ edges. We will consider the tree nodes numbered by integers from 1 to $ n $ .

Today Polo wonders, how to find the number of pairs of paths that don't have common nodes. More formally, he should find the number of groups of four integers $ a,b,c $ and $ d $ such that:

- $ 1<=a&lt;b<=n $ ;
- $ 1<=c&lt;d<=n $ ;
- there's no such node that lies on both the shortest path from node $ a $ to node $ b $ and from node $ c $ to node $ d $ .

The shortest path betweem two nodes is the path that is shortest in the number of edges.

Help Polo solve this problem.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
2
```

# 题解

## 作者：MCAdam (赞：10)

[题目](https://www.luogu.com.cn/problem/CF288D)

题意：给定$n$个节点的树，求满足条件的四元组$(a,b,c,d)$的数量：

- $1\leq a< b\leq n\quad 1\leq c< d\leq n$

- $a$到$b$和$c$到$d$的路径没有交点

$n\leq 8\times 10^4$

先容斥以下，所有的四元组数量：$\binom{n}{2}^2$

现在要求有交点的四元组数量

不妨考虑以$p$为交点中深度最浅的点的方案数：

有两种情况：两条路径都在$p$的子树内；一条路径在$p$子树内，另外一条端点在子树$p$内外

- 在子树$p$内的路径

此时，路径一定要经过$p$，也就是两端点要在$p$不同儿子的子树中

这个同样可以容斥：$\displaystyle ans1=\binom{size[p]}{2}-\sum_{q\in son(p)}\binom{size[q]}{2}$

- 两端点在子树$p$内外的

在子树内外各选一个点就行了

$\displaystyle ans2=size[p]\times (n-size[p])$

所以最后的答案就为：

$\displaystyle \binom{n}{2}^2-\sum ans1\times ans1+ans1\times ans2\times 2$

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=8e4+10;
int n,tot;
ll sum;
int fir[N],size[N];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
inline ll cal(int x)
{
	return 1ll*x*(x-1)/2;
}
inline void dfs(int p,int fa)
{
	size[p]=1;
	ll ans1=0,ans2=0;
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa) continue;
		dfs(q,p);
		size[p]+=size[q];
		ans1-=cal(size[q]);
	}
	ans1+=cal(size[p]),ans2+=1ll*size[p]*(n-size[p]);
	sum+=ans1*ans1+ans1*ans2*2;
}
int main()
{
	int a,b;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	dfs(1,0);
	printf("%lld\n",cal(n)*cal(n)-sum);
	return 0;
}
```


---

## 作者：ziyistudy (赞：6)

## 前言

>模拟赛没有做出来。
>
>老师：我口胡了一种全新的方法，但是没有写，大家可以去尝试一下。
>
>于是：

## 正言

一个重要的性质是“边-点=$1$”，这时候你就会问了：树上点不是比边多 $1$ 吗？
看一下下图（~~有点丑~~）：
![](https://cdn.luogu.com.cn/upload/image_hosting/o9cfvbsz.png)

蓝色是树。我们注意到，对任意两条不相交的路径（红色），它们之间的边一定比点多 $1$。

所以，我们可以计算出所有边的贡献减去所有点的贡献即可，这样，每条路径刚好都会被算到一次。

边的贡献：设一条边左右两点的子树大小分别为 $szl,szr$。那路径数量为：$\frac{szl\times (szl-1)}{2}\times \frac{szr\times (szr-1)}{2}$。

点的贡献：设与这个点相连的点的子树大小分别为 $sz_1\sim sz_r$。记 $cnt_i=\frac{sz_i\times (sz_i-1)}{2}$，$sum=\sum cnt_i$。那路径数量为：$\sum cnt_i\times(sum-cnt_i)$。

实现可以用树上 dp（甚至不用换根）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=2e5+5;
int a[N];
vector<vector<int>> G(N);
int n;
int siz[N];
void dfs(int now,int fa)
{
    siz[now]=1;
    for(auto it:G[now]){
        if(it!=fa) {
            dfs(it,now);
            siz[now]+=siz[it];
        }
    }
}
int ans;
void dfs2(int now,int fa)
{
    vector<int> V;int sum=0;
    if(now!=fa) V.pb((n-siz[now])*(n-siz[now]-1)/2),sum+=(n-siz[now])*(n-siz[now]-1)/2;
    for(auto it:G[now]){
        if(it!=fa){
            if(siz[it]>1) V.pb(siz[it]*(siz[it]-1)/2),sum+=siz[it]*(siz[it]-1)/2;
            ans+=siz[it]*(siz[it]-1)*(n-siz[it])*(n-siz[it]-1)/2;
            dfs2(it,now);
        }
    }
    int cnt=0;
    for(auto it:V) cnt+=it*(sum-it);
    ans=ans-cnt;
}
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(1,1);
    ans=0;
    dfs2(1,1);
    cout<<ans<<endl;
}
```

---

## 作者：Drind (赞：2)

### 题目解析
求点不相交的两条路径的个数。

总路径个数是好求的，就是 $\frac{n^2(n-1)^2}{4}$。

所以我们正难则反，考虑算点相交的路径个数，那么就是对于任意一条路径，有两个点的 lca 在这个路径上，我们设 $f_i$ 为 lca 为 $i$ 的点数，很容易得到以下式子：

$$f_i=\frac{1}{2}\sum_{u\in son_i}\sum_{v\in son_i}[u\neq v]\left(\left(siz_u+1\right)\times \left(siz_v+1\right)-1\right)$$

意思是对于两个子树求积，减去的 $1$ 代表两个子树都选中了 $i$ 的情况，在本题中两个顶点重合不算路径。

但是这么算我们的复杂度就喜提 $n^2$，看着不像可以过的样子，我们考虑对上面的式子提取公因数一下。

$$f_i=\frac{1}{2}\left(\left(\sum_{u\in son_i}siz_u\right)^2-\left(\sum_{u\in son_i}{siz_u}^2\right)\right)+ \left(\sum_{u\in son_i}siz_u\right)$$

在里面没有算包括 $i$ 为端点的路径，而是移到了外面一起加。

所以点相交的路径个数就是以下这个东西了：

$$\sum_{i=1}^n\sum_{j=i+1}^n\sum_{u\in dis_{i,j}}f_u$$

吗？这个式子只算了一条路径的 lca 大于等于另一条路径的情况，如果我们要算完要把他乘二再减去两条路径 lca 相等的情况，也就是 $\sum_{i=1}^n{f_i}^2$。

所以就是：

$$2\sum_{i=1}^n\sum_{j=i+1}^n\sum_{u\in dis_{i,j}}f_u-\sum_{i=1}^n{f_i}^2$$

但是要计算这个式子复杂度是 $n^3$ 的，太恐怖了，我们考虑对于每个点拆贡献（也就是算有多少条路径经过某个点，然后乘上 $f_u$ 即可）。

这个计算过程和计算 $f$ 类似，只需要把式子里的 $\left(\sum_{u\in son_i}siz_u\right)$ 加上一个 $n-siz_u+1$ 就行了。

注意这个做法貌似要开 __int128，所以选择语言的时候要选 C++20，不然会 CE。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=2e5+10;

struct node{
	int to,nxt;
}edge[N*2]; int head[N],cnt;
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

int siz[N],sqr[N],tot[N];
void dfs(int u,int f){
	siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		dfs(v,u); siz[u]+=siz[v]; sqr[u]+=siz[v]*siz[v]; tot[u]+=siz[v];
	}
}

int read(){
	int x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while('0'<=ch&&ch<='9'){
		x=(x<<1)+(x<<3); x=x+ch-'0'; 
		ch=getchar();
	}
	return x;
}

inline void fake_main(){
	int n; n=read();
	for(int i=1;i<n;i++){
		int u,v; u=read(); v=read();
		adde(u,v);
	}
	dfs(1,0);
	
	int ans=n*n*(n-1)*(n-1)/4; int t1=0,t2=0;
	for(int i=1;i<=n;i++){
		
		
		//f 就是拆贡献，跟题解里的f不是同一个东西
		int f=(((tot[i]+n-siz[i])*(tot[i]+n-siz[i])-(sqr[i]+(n-siz[i])*(n-siz[i])))/2+(tot[i]+n-siz[i]));
		t1+=f*((tot[i]*tot[i]-sqr[i])/2+tot[i]);
      	//后面乘的这一部分是题解里的 f，也就是 lca 为 i 的路径数。
	}
	for(int i=1;i<=n;i++){
		t2+=((tot[i]*tot[i]-sqr[i])/2+tot[i])*((tot[i]*tot[i]-sqr[i])/2+tot[i]);
	}
	
	cout<<(long long)(ans-t1*2+t2)<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：Dtw_ (赞：1)

# 思路
首先因为无交点，所以这两条链没有任何关系，所以考虑容斥，这样就转化为求有交点的两条链的数量。

因为要求有交点的，容易想到枚举交点，那对于每个交点如何计算贡献呢？

首先考虑当交点为 $u$ 时这两条链以什么形式出现。

在子树内指链的两个端点都在子树内，在子树外指链的一个端点在子树内，另一个在子树外。

1. 两条都在 $u$ 的子树内。
2. 一条在 $u$ 的子树内，一条在子树外。
3. 两条都在子树外。

注意，两条都在子树外由于这是一棵树，一个点只有唯一的父亲，所以交点会在父亲那在算一遍，这样就重了，所以第 $3$ 种情况不管。

首先考虑第 $1$ 种情况：总共的方案为 $\binom{sz_u}{2}$，但是注意如果说两个点都在 $u$ 的儿子 $v$ 的子树中，那么交点就不是 $u$ 了，所以不能在 $v$ 的子树中，所以答案就是 $\binom{sz_u}{2} - \binom{sz_{v_1}}{2} - \binom{sz_{v_2}}{2} - \dots-\binom{sz_{v_k}}{2}$。但由于是两条，所以平方一下就好。

考虑第二种：首先在子树内的直接把情况 $1$ 抄下来，那子树内有 $sz_u$ 个点，子树外一共有 $n - sz_u$ 个点，所以方案数为 $sz_u\times (n-sz_u)$。但是因为第一条边和第二条边不一定，就是说可以互换，所以最终的方案数还要乘 $2$。所以答案为 $sz_u\times (n-sz_u)\times \binom{sz_u}{2} - \binom{sz_{v_1}}{2} - \binom{sz_{v_2}}{2} - \dots-\binom{sz_{v_k}}{2} \times 2$。

情况一加情况二就是答案。

然后跑遍 DFS 处理 $sz_u$ 的同时记录答案就行。最后应该用 $\binom{n}{2}^2$ 减掉记录的答案就行了。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 8e4 + 10;

inline int C(int n)
{
	return n * (n - 1) / 2;
}

int n, res, sz[N];

vector<int> G[N];

void dfs(int u, int fa)
{
	int cur = 0;
	for (auto v : G[u])
	{
		if (v == fa) continue;
		dfs (v, u);
		sz[u] += sz[v];
		cur -= C(sz[v]);
	}
	sz[u]++;
	cur += C(sz[u]);
	res += cur * cur;
	res += sz[u] * (n - sz[u]) * cur * 2;
}

signed main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, 0);
	int ans = C(n) * C(n) - res;
	cout << ans;
	return 0;
}

```

---

## 作者：wflhx2011 (赞：0)

这道题要求没有交点的路径数量，但我不知道要怎么快速判断两条路径有无交点。

所谓正难则反，考虑从总情况中减掉有交点的情况。

总情况是任选两个不相同的 $a$，$b$ 的方案，再任选两个不相同的 $c$，$d$ 的方案，两个相乘。即 $C_n^2*C_n^2=\frac{n^2(n-1)^2}{4}$。

求有交点的路径数量，因为 $n$ 很小所以可以枚举。

设交点为 $x$，这时两条路径有几种情况：

1. 两条路径都在 $x$ 子树内。

为了不重复计算，让两条路径位于两个不同的 $x$ 的儿子节点子树内。

避免枚举造成时间复杂度过大，也考虑容斥，答案 $ans1$ 就是 $(C_{siz_x}^2-\sum_{u\in son_x} C_{siz_u}^2)^2$。

2. 一条路径在子树内，另一条在子树外。

子树内就是 $ans1$，子树外是 $siz_x \times (n-siz_x)$，把这两个乘起来。

3. 两条都在子树外。但因为是一棵树，所以他们会在 $x$ 的祖先上也产生交点，重复了不管。

减一下就是答案。


```cpp
#include<bits/stdc++.h> 
using namespace std;
long long n,tot;
long long sum,head[200005],siz[200005];
struct edge
{
	long long f,t;
}e[200005];
void add(long long x,long long y)
{
	e[++tot].t=y;
	e[tot].f=head[x];
	head[x]=tot;
}
void dfs(long long u,long long fa)
{
	siz[u]=1;
	long long ans1=0,ans2=0;
	for(long long i=head[u];i;i=e[i].f)
	{
		if(e[i].t==fa)
			continue;
		dfs(e[i].t,u);
		siz[u]+=siz[e[i].t];
		ans1-=1ll*siz[e[i].t]*(siz[e[i].t]-1)/2ll;
	}
	ans1+=(long long)(1ll*siz[u]*(siz[u]-1)/2ll);
	ans2+=(long long)(1ll*siz[u]*(n-siz[u]));
//	cout<<ans1<<" "<<ans2<<endl;
	sum+=(long long)(1ll*ans1*ans1+ans1*ans2*2ll); 
}
int main()
{
	cin>>n;
	for(long long i=1;i<n;i++)	
	{
		long long u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
//	cout<<sum<<endl;
	cout<<(long long)((long long)(1ll*n*1ll*(n-1)/2ll)*(long long)(1ll*n*1ll*(n-1)/2ll)-sum);
	return 0;
}
```

---

## 作者：Frictional (赞：0)

## 题意
任选树上两条没有交点的路径，求有多少种选法。

## 做法
这道题一眼是容斥，但我一开始想去直接求没有交点的路径，但是没有想出来，那既然正着做不好做，我们就反过来做（正难则反），即我们不去考虑有多少条没有交点的选法，我们去找有交点的，再用总个数减掉。

首先，显然，四元组的总个数有 $\dbinom{n}{2}^2$   个，即在树上任选两条路径。

之后我们再去考虑有交的路径个数。为了防止统计重复，所以我们对于树上一个点 $P$ 只考虑 $P$ 为交点的情况。显然，经过点 $P$ 的树上路径只有两种情况：

一种是两个端点都在以 $P$ 为根的子树内。那就是在子树中任选两个点当端点吧！但并不是，因为我们要求的是经过点 $P$ 的，所以我们还要减掉在以 $P$ 的儿子为根的子树中任选的两个端点。所以就有 
 $\dbinom{size_p}{2}- \sum\limits_{q \in  son(p)}\dbinom{size_q}{2}$ 种。记为 $N$。

一种是通过点 $P$ 穿过这棵树，即一个端点在子树外，一个在子树内。所以有 $size_p \times (n-size_p)$  种可能。记为 $M$。

那这样的话，选两条路径的情况也可以列出来了。

1. 两条路径都在子树内。
   那不就是 $N \times N$。

2.两条路径一条在子树内，一条穿过子树
  那不就是 $N \times M$。
  
3.两条路径都穿过子树 
  这种情况我们考虑一下就会发现，因为这是一棵树，两条穿过子树的路径一定也会交与 $P$ 的父亲，会算重，所以不考虑。

综上所述，答案就是 $\dbinom{n}{2}^2-N^2-N\times M$。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P pair<int,int>
#define int long long
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define gc getchar()
#define pc putchar
using namespace std;
inline int rd(){
    int x=0,f=1;
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
const int N=8e4+5;
int n;
vector<int>ng[N];
int u,v;
int mo[N];
int c[N][4];
void init(){
    int i,j;
    c[0][0]=1;
    FOR(i,1,80000){
        c[i][0]=1;
        FOR(j,1,2) c[i][j]=(c[i-1][j]+c[i-1][j-1]);
    }
}
int tmp;
int ans1[N],ans2;
int dfs(int now,int fa){
    for(auto x:ng[now]){
        if(x!=fa){
            tmp=dfs(x,now);
            mo[now]+=tmp;
            ans1[now]+=c[tmp][2];
        }
    }
    mo[now]++;
    return mo[now];
}
int ans;
signed main(){
    n=rd();
    FOR(i,1,n-1){
        u=rd(),v=rd();
        ng[u].pb(v);
        ng[v].pb(u);
    } 
    init();
    dfs(1,-1);
    FOR(i,1,n){
        if(mo[i]!=1){
            ans1[i]-=c[mo[i]][2];
            ans1[i]=0-ans1[i];
        }
        ans2=(mo[i])*(n-mo[i]);
        ans+=ans1[i]*ans1[i]+ans1[i]*ans2*2;
    }
    cout<<c[n][2]*c[n][2]-ans;
    return 0;
}
```

---

## 作者：C_Pos_Princess (赞：0)

# 题解：CF288D Polo the Penguin and Trees 

题意：求树上满足 $a,b,c,d$ 四个点满足 $a$ 到 $b$ 和 $c$ 到 $d$ 之间路径没有交点的路径数量。

其中 $1 \le a < b \le n,1\le c<d\le n$。

经过思考，我们发现直接求并不好求，于是**正难则反**，我们求两条路径有交点的数量。

首先要知道，从 $n$ 个点里选出不相同两个点有 $C^2_n$ 种选法。

以 $p$ 节点考虑两条路径经过 $p$ 点的方案数。

- 两条路径端点均在子树 $p$ 内。

	此时两个端点不能在同一子树内，则令：
    $$
    ans1 = C^2_{size_p}-\sum_{q\in son_p} C^2_{size_q}
    $$

- 一条路径一个端点在 $p$ 内，一个在 $p$ 外，另一条路径在子树内。
	那么在子树内选一点，在子树外选一点就行了。
    $$
    ans2 = size_p \times (n-size_p)
    $$
	这种情况的答案为 $ans1 \times ans2 \times 2$，为什么呢，因为 $ab$ 和 $cd$ 之间具有对称性啊。
 
注意：

为什么我们不考虑两条路径的端点均是一条在子树内，一条在子树外呢。

答:  如果存在这种情况，又由于这是一棵树，两条路径必定在当前节点的父节点相交，那么在父节点统计的时候就统计多了一次，所以排除这种情况。

那么最终答案为：

$$
ans = C^2_n - \sum (ans1\times ans1+ans1\times ans2\times 2)
$$

代码奉上。
```
#include<bits/stdc++.h>
using namespace std;

int n;
const int N = 80010;
vector<int> edg[N];


typedef long long ll;
ll num(ll x){
	return x*(x-1)/2;
}
ll siz[N];
ll ans;
void dfs(int u,int fa){
	siz[u] = 1;
	ll ans1= 0,ans2 = 0;
	for(auto v:edg[u]){
		if(v == fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		ans1-=num(siz[v]);
	}
	ans1+=num(siz[u]);
	ans2+=siz[u]*(n-siz[u]);
	ans+=ans1*ans1+ans1*ans2*2;
}



int main(){
	cin>>n;
	for(int i = 1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		edg[u].push_back(v);
		edg[v].push_back(u);
	}	
	dfs(1,-1);
	cout<<num(n)*num(n)-ans;
	
	
	return 0;
}
```

---

## 作者：時空 (赞：0)

### $\texttt{CF288D Polo the Penguin and Trees}$

[In Luogu](https://www.luogu.com.cn/problem/CF288D)

题意：给定 $n$ 个节点的树，求满足条件的四元组 $(a,b,c,d)$ 的数量：

1. $a$ 到 $b$ 和 $c$ 到 $d$ 的路径没有交点。
2. $1 \le a < b \le n$，$1 \le c < d \le n$。

$n \le 8 \times 10^4$。

解：分讨题。

考虑所有四元组的数量，为 $(C_n^2)^2$。

正难则反，我们考虑计算有交点的路径数量。

考虑以 $p$ 为交点的路径数量。$p \in \{1 ... n \}$。

两种情况，一种为两条路径都在 $p$ 的子树内，另一种为一条在 $p$ 子树内，一条在 $p$ 子树外。

下文记 $size_p$ 表示 $p$ 子树的大小，这个东西可以边计算边维护。

1. 两条都在 $p$ 的子树内。

先考虑选择一条路径。首先在 $p$ 子树中选择两点的方案数为 $(C_{size_p}^2) ^ 2$。

对于 $q \in son_p$，因为路径必须经过 $p$，故不可能路径的两端都在 $q$ 子树内。容斥一下，方案数需要减去 $(C_{size_q}^2) ^ 2$。

故在 $p$ 子树中选择两点的方案数为 $f = (C_{size_p}^2) ^ 2 - \displaystyle \sum_{q \in son_p} (C_{size_q}^2) ^ 2$。

那么选择两条路径的方案数即为 $f^2$。

2. 一条在 $p$ 子树内，一条在 $p$ 子树外。

在 $p$ 子树内选出一条路径的方案数上文已求出，即 $f$。

考虑在 $p$ 子树外选出一条路径。

容易想到即为 $k=size_p \times (n - size_p)$。

总和即为 $2 \times f \times k$。

故答案为 $(C_n^2)^2 - f^2 - 2 \times f \times k$。

正常维护计算即可，代码过于简单，不放。

---

