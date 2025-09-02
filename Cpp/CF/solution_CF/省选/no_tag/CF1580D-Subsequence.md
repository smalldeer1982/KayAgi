# Subsequence

## 题目描述

Alice 有一个长度为 $n$ 的整数序列 $a$，所有元素都是不同的。她将选择一个长度为 $m$ 的 $a$ 的子序列，并将一个子序列 $a_{b1},a_{b2},...,a_{bm}$ 的价值定义为

$$\sum_{i = 1}^m (m \cdot a_{b_i}) - \sum_{i = 1}^m \sum_{j = 1}^m f(\min(b_i, b_j), \max(b_i, b_j))$$

其中 $f(i,j)$ 表示 $\min(a_i,a_{i+1},..., a_j)$。

Alice 希望你能帮助她将她所选择的子序列的价值最大化。

如果一个序列 $s$ 可以通过删除序列 $t$ 中几个元素（可以不删除任何元素或删除全部元素）得到，那么这个序列 $s$ 就是序列 $t$ 的一个子序列。

## 说明/提示

### 样例解释

在第一个例子中，Alice 可以选择子序列 $[15, 2, 18, 13]$ , 该子序列的值为 $4 \cdot (15 + 2 + 18 + 13) - (15 + 2 + 2 + 2) - (2 + 2 + 2 + 2) - (2 + 2 + 18 + 12) - (2 + 2 + 12 + 13) = 100$。

在第二个例子中，有多种价值为 $176$ 的子序列，其中一个是 $[9,7,12,20,18]$。

## 样例 #1

### 输入

```
6 4
15 2 18 12 13 4```

### 输出

```
100```

## 样例 #2

### 输入

```
11 5
9 3 7 1 8 12 10 20 15 18 5```

### 输出

```
176```

## 样例 #3

### 输入

```
1 1
114514```

### 输出

```
0```

## 样例 #4

### 输入

```
2 1
666 888```

### 输出

```
0```

# 题解

## 作者：meyi (赞：5)

2022/2/18 UPD: [$\text{\color{black}C\color{red}irno\_9}$](https://www.luogu.com.cn/user/78372) 指出时间复杂度应该是 $O(n^2)$ 而非 $O(n^2\log n)$，已修正。

首先简化一下题意，发现就是让你从 $n$ 个数中按顺序取 $m$ 个，定义它的权值为取的数的总和的 $m$ 倍减去它们**在原序列中**两两之间的最小值，答案就是所有取法的最大权值。

令 $dp_{l,r,k}$ 表示在 $[l,r]$ 内选 $k$ 个数能够得到的最大权值，$pos$ 表示 $[l,r]$ 内最小元素的下标，则有如下转移方程：

- $dp_{l,pos-1,x}+dp_{pos+1,r,k-x}-2\times x\times (k-x)\times a_{pos}\to dp_{l,r,k}$

- $dp_{l,pos-1,x}+dp_{pos+1,r,k-x}+m\times a_{pos}-(2\times (x+1)\times (k-x+1)-1)\times a_{pos}\to dp_{l,r,k+1}$

然后你会发现这是个裸的背包问题，于是上面两个式子的意义也就不难得出：

- 如果在 $[l,r]$ 内不选 $a_{pos}$ ，那么已选的在 $pos$ 左边的数有 $x$ 个，在 $pos$ 右边的数有 $k-x$ 个，它们的 $f$ 值均为 $pos$ ，故它们的贡献为 $-2\times x\times (k-x)\times a_{pos}$。

- 如果在 $[l,r]$ 内选了 $a_{pos}$，那么 $a_{pos}$ 首先作为被选的元素要贡献 $m\times a_{pos}$，已选的在 $pos$ 左边的数有 $x+1$ 个，在 $pos$ 右边的数有 $k-x+1$ 个，它们在原序列中之间的最小值均为 $a_{pos}$ ，但要注意 $pos$ 自己和自己只能贡献一次，故它们的总贡献为 $m\times a_{pos}-(2\times (x+1)\times (k-x+1)-1)\times a_{pos}$。

于是这题就做完了，递归分治求解即可。

时间复杂度 $O(n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=4010;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int a[maxn],m,n;
vector<ll>solve(int l,int r){
	vector<ll>ret(r-l+2,LLONG_MIN);
	ret[0]=0;
	if(l>r)return ret;
	ri pos=min_element(a+l,a+r+1)-a;
	vector<ll>ansL=solve(l,pos-1),ansR=solve(pos+1,r);
	for(ri i=0;i<ansL.size();++i)
		for(ri j=0;j<ansR.size();++j){
			ckmax(ret[i+j],ansL[i]+ansR[j]-2ll*i*j*a[pos]);
			ckmax(ret[i+j+1],ansL[i]+ansR[j]-(2ll*(i+1)*(j+1)-1)*a[pos]+1ll*m*a[pos]);
		}
	return ret;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;++i)scanf("%d",a+i);
	printf("%lld",solve(1,n)[m]);
	return 0;
}
```


---

## 作者：GIFBMP (赞：2)

#### 前言

这题真的是 \*2900 的题吗……，感觉只有 \*2300 左右。

#### 正题

首先我们观察一下题目的式子，发现涉及许多段区间最小值的和，遇到这种问题，我们考虑使用笛卡尔树解决。

首先建立笛卡尔树，我们利用笛卡尔树的一个性质：$[x,y]$ 中的最大/小值等于树上 $x$，$y$ 的 LCA 的点权。那么一个节点会在式子的后半部分只会被自己子树中的节点贡献到。我们发现合并儿子的过程其实就是 DP 的形式，于是我们设 $f_{i,j}$ 表示 $i$ 的子树中选了 $j$ 个节点的最大价值。那么显然有初值 $f_{i,1}=(m-1)\times a_i$。至于合并儿子的过程如下：

$$f_{x,i+j}\leftarrow f_{x,i}+f_{v,j}-2\times a_x\times i\times j$$

于是就做完了，时间复杂度 $\Theta(n^2)$。

Code:

```cpp
#include <cstdio>
#include <algorithm>
using namespace std ;
const int MAXN = 4e3 + 10 ;
int n , m , a[MAXN] , st[MAXN] , tp , lc[MAXN] , rc[MAXN] , vis[MAXN] , rt , sz[MAXN] ;
typedef long long ll ;
ll f[MAXN][MAXN] , g[MAXN] ;
void dfs (int x) {
	f[x][1] = (ll)(m - 1) * a[x] , sz[x] = 1 ; 
	if (lc[x]) {
		dfs (lc[x]) ;
		for (int i = 1 ; i <= sz[x] ; i++) g[i] = f[x][i] ;
		for (int i = 0 ; i <= sz[x] ; i++)
			for (int j = 0 ; j <= sz[lc[x]] ; j++)
				f[x][i + j] = max (f[x][i + j] , g[i] + f[lc[x]][j] - 2LL * i * j * a[x]) ;
		sz[x] += sz[lc[x]] ;
	}
	if (rc[x]) {
		dfs (rc[x]) ;
		for (int i = 1 ; i <= sz[x] ; i++) g[i] = f[x][i] ;
		for (int i = 0 ; i <= sz[x] ; i++)
			for (int j = 0 ; j <= sz[rc[x]] ; j++)
				f[x][i + j] = max (f[x][i + j] , g[i] + f[rc[x]][j] - 2LL * i * j * a[x]) ;
		sz[x] += sz[rc[x]] ;
	}
}
int main () {
	scanf ("%d%d" , &n , &m) ;
	for (int i = 1 ; i <= n ; i++) scanf ("%d" , &a[i]) ;
	st[tp = 1] = 1 ;
	for (int i = 2 ; i <= n ; i++) {
		for (; tp && a[i] < a[st[tp]] ; tp--) ;
		if (!tp) lc[i] = st[1] ;
		else lc[i] = rc[st[tp]] , rc[st[tp]] = i ;
		st[++tp] = i ; 
	}
	for (int i = 1 ; i <= n ; i++) vis[lc[i]] = vis[rc[i]] = 1 ;
	for (int i = 1 ; i <= n ; i++) if (!vis[i]) rt = i ;
	dfs (rt) ;
	printf ("%lld\n" , f[rt][m]) ;
	return 0 ;
}
```

---

## 作者：Little09 (赞：2)

稍作转化，题目就是要求：

$$\sum_{i=1}^n\sum_{j=i+1}^na_i+a_j-2\times f(i,j)$$

你也许会发现这和树上两点距离公式长得很像。于是把笛卡尔树建出来，每条边的权值是两个节点的权值差。于是就是选出 $m$ 个点使两两的距离和最大。

考虑 $O(n^2)$ 的树上 DP。定义 $dp[i][j]$ 表示在 $i$ 这个子树内选了 $j$ 个节点的最大代价，转移时只要算一条边被经过了几遍就行了。

```cpp
// By: Little09
// Problem: D. Subsequence
// Contest: Codeforces - Codeforces Round #745 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1580/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=1000000000000000000;
const int N=4005;
int n,m; 
ll a[N],dp[N][N];

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
int st[N],ls[N],rs[N],rt=1;
ll lw[N],rw[N],size[N];
void build()
{
	int top=0,tot=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]<a[rt]) rt=i;
		tot=top;
		while (tot&&a[st[tot]]>a[i]) tot--;
		if (tot) rs[st[tot]]=i,rw[st[tot]]=a[i]-a[st[tot]];
		if (tot<top) ls[i]=st[tot+1],lw[i]=a[st[tot+1]]-a[i];
		st[++tot]=i;
		top=tot;
	}
}
void dfs(int u)
{
	size[u]=1;
	if (ls[u])
	{
		dfs(ls[u]);
		for (int i=size[u];i>=0;i--)
		{
			for (ll j=size[ls[u]];j>=0;j--)
			{
				dp[u][i+j]=max(dp[u][i+j],dp[u][i]+dp[ls[u]][j]+j*(m-j)*lw[u]);
			}
		}
		size[u]+=size[ls[u]];
	}
	if (rs[u])
	{
		dfs(rs[u]);
		for (int i=size[u];i>=0;i--)
		{
			for (ll j=size[rs[u]];j>=0;j--)
			{
				dp[u][i+j]=max(dp[u][i+j],dp[u][i]+dp[rs[u]][j]+j*(m-j)*rw[u]);
			}
		}
		size[u]+=size[rs[u]];
	}
}
int main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	build();
	dfs(rt);
	cout << dp[rt][m];
	return 0;
}

```


---

## 作者：james1BadCreeper (赞：2)

先来看一下要求的这个东西：

$$
\begin{aligned}
\text{原式}&=\sum_{i = 1}^m (m \cdot a_{b_i}) - \sum_{i = 1}^m \sum_{j = 1}^m f(\min(b_i, b_j), \max(b_i, b_j))\\
&=(m-1)\sum_{i = 1}^m a_{b_i}-2\sum_{i=1}^m\sum_{j=i+1}^m \min\{a_{b_i},a_{b_i+1}\cdots,a_{b_j-1},a_{b_j}\}
\end{aligned}
$$

要求这个东西的最大值，后面这个区间最小值可以考虑放到笛卡尔树上，然后用树形 DP 求解这个问题。

由于 $\min\{a_x,\cdots,a_y\}=a_{\operatorname{LCA}(x,y)}$，因此式子最后那一坨就是 $\displaystyle2\sum_{i=1}^m\sum_{j=i+1}^m a_{\operatorname{LCA}(i,j)}$。

设 $f_{x,k}$ 代表 $x$ 中选择 $k$ 个节点的最大价值，初始 $f_{i,1}=(m-1)a_i$，然后转移是一个类似树形背包的过程：

$$
f_{x,i+j}=\max\{f_{x,i}+f_{y,j}-2\times a_x\times i\times j\}
$$

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
inline void ckmax(i64 &x, i64 t) { if (x < t) x = t; }

int n, m, rt; 
int a[4005], ls[4005], rs[4005], st[4005], siz[4005]; 
i64 f[4005][4005]; 
bool v[4005]; 

void dfs(int x) {
	f[x][1] = 1ll * (m - 1) * a[x]; siz[x] = 1; 
	function<void(int)> work = [&] (int y) {
		dfs(y); 
		for (int i = siz[x]; i >= 0; --i)
			for (int j = 0; j <= siz[y]; ++j)
				ckmax(f[x][i + j], f[x][i] + f[y][j] - 2ll * a[x] * i * j); 
		siz[x] += siz[y]; 
	}; 
	if (ls[x]) work(ls[x]); if (rs[x]) work(rs[x]); 
}

int main(void) {
	scanf("%d%d", &n, &m); 
	for (int i = 1, cur = 0, tot = 0; i <= n; ++i) {
		scanf("%d", a + i); cur = tot; 
		while (cur && a[st[cur]] > a[i]) --cur; 
		if (cur) rs[st[cur]] = i; 
		if (cur < tot) ls[i] = st[cur + 1]; 
		st[++cur] = i; tot = cur; 
	}
	for (int i = 1; i <= n; ++i) v[ls[i]] = v[rs[i]] = 1; 
	for (int i = 1; i <= n; ++i) if (!v[i]) dfs(i), printf("%lld\n", f[i][m]); 
	return 0;  
}
```

---

## 作者：SSerxhs (赞：1)

由于 $f$ 表示的是一段区间的 $\min$，考虑把问题放到笛卡尔树上。

把第二个贡献拆开，就相当于 $\sum (m-1)a_{b_i}-2\sum_{i<j}a_{lca(b_i,b_j)}$。设 $f_{i,j}$ 表示点 $i$ 子树选了 $j$ 个的最优解，树形 dp 即可。由树卷积相关理论容易证明复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4002;
ll g[N][N];
int st[N],c[N][2],f[N],siz[N],a[N];
int n,m,i,tp,rt;
void dfs(int x)
{
	int lc=c[x][0],rc=c[x][1];
	siz[x]=1;
	if (!lc&&!rc)
	{
		g[x][0]=0;
		g[x][1]=(ll)a[x]*(m-1);
		return;
	}
	if (!lc&&rc) swap(lc,rc);
	if (!rc)
	{
		dfs(lc);
		siz[x]+=siz[lc];
		memcpy(g[x],g[lc],(siz[lc]+1)*sizeof g[0][0]);
		for (int i=0;i<=siz[lc];i++) g[x][i+1]=max(g[x][i+1],g[lc][i]+(ll)(m-1)*a[x]-2ll*i*a[x]);
		return;
	}
	dfs(lc);dfs(rc);siz[x]+=siz[lc]+siz[rc];
	for (int i=0;i<=siz[lc];i++) for (int j=0;j<=siz[rc];j++) g[x][i+j]=max(g[x][i+j],g[lc][i]+g[rc][j]-2ll*i*j*a[x]);
	for (int i=0;i<=siz[lc];i++) for (int j=0;j<=siz[rc];j++) g[x][i+j+1]=max(g[x][i+j+1],g[lc][i]+g[rc][j]+(ll)(m-1)*a[x]-2ll*(i*j+i+j)*a[x]);
}
int main()
{
	memset(g,-0x3f,sizeof g);
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m;
	for (i=1;i<=n;i++)
	{
		cin>>a[i];st[tp+1]=0;
		while (tp&&a[st[tp]]>a[i]) --tp;
		c[st[tp]][1]=i;
		c[i][0]=st[tp+1];
		st[++tp]=i;
	}
	for (i=1;i<=n;i++) f[c[i][0]]=f[c[i][1]]=i;
	rt=min_element(f+1,f+n+1)-f;
	dfs(rt);cout<<g[rt][m]<<endl;
}
```

---

## 作者：vectorwyx (赞：1)

先把式子化成 $(m-1)\sum_{i=1}^{m}a_{b_i}+2\sum_{i=1}^{m}\sum_{j=i+1}^{m}f(b_i,b_j)$。直接从序列的角度考虑，如果最小值的位置为 $pos$，假设最小值的左边选 $x$ 个数，左边和右边就转为了两个规模更小的子问题，$(m-1)\sum_{i=1}^{m}a_{b_i}$ 可以由左边和右边合并上来，而 $2\sum_{i=1}^{m}\sum_{j=i+1}^{m}f(b_i,b_j)$ 在合并后只剩横跨最小值的区间没有计入答案，因此需要再加上 $x(m-x)a_{pos}$。记忆化一下，这等价于树上背包，复杂度看似是 $O(nm^2)$ 实则是 $O(nm)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define sml(x,y) x=min(x,y)
#define big(x,y) x=max(x,y)
#define mk make_pair
#define pb push_back
#define ll long long
#define db double
using namespace std;
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } return x*f; }

const int N=4005;
const ll inf=1e15;
int a[N],n,k,pos[N][N],tot;
short int mp[N][N];//卡空间
bool g[N][N];
ll f[N][N];

ll solve(int L,int R,int m){
	//printf("solve(%d,%d,%d)\n",L,R,m);
	if(m<0) return -inf;
	if(L>R){
		if(m==0) return 0;
		return -inf;
	}
	if(L==R){
		if(m==0) return 0;
		if(m==1) return a[L]*(k-1ll);
		return -inf;
	}
	if(!mp[L][R]) mp[L][R]=++tot;
	int x=mp[L][R];
	if(g[x][m]) return f[x][m];
	g[x][m]=1;
	int mid=pos[L][R];
	if(mid==L) return f[x][m]=max(solve(L+1,R,m),solve(L+1,R,m-1)+a[L]*(k-1ll)-2ll*a[L]*(m-1));
	if(mid==R) return f[x][m]=max(solve(L,R-1,m),solve(L,R-1,m-1)+a[R]*(k-1ll)-2ll*a[R]*(m-1));
	if(mid-L<R-mid) fo(i,0,min(m,mid-L+1)) big(f[x][m],solve(L,mid,i)+solve(mid+1,R,m-i)-2ll*i*(m-i)*a[mid]);
	else fo(i,0,min(m,R-mid+1)) big(f[x][m],solve(L,mid,m-i)+solve(mid+1,R,i)-2ll*i*(m-i)*a[mid]);
	return f[x][m];
}

int main(){
	cin>>n>>k;
	fo(i,1,n) a[i]=read(),pos[i][i]=i;
	fo(len,2,n)
		fo(i,1,n-len+1){
			int j=i+len-1;
			if(a[pos[i+1][j]]<a[i]) pos[i][j]=pos[i+1][j];
			else pos[i][j]=i;
		}
	cout<<solve(1,n,k);
	return 0;
}

```


---

## 作者：xukehg (赞：0)

一眼秒了。

首先转换式子为 

$\sum_{i = 1}^{m}c_{b_i} - \sum_{i = 1}^{m}\sum_{j = i + 1}^{m}f(\min(b_i,b_j),\max(b_i,b_j)) \times 2$，其中 $c_i = (m - 1) \times a_i$。

考虑如何计算 $f$ 函数。因为我们不可能通过区间去找点值，所以我们尝试用点值去确定区间，从而很自然的想到运用小根笛卡尔树。考虑在树上 dp，设 $dp_{i,j}$ 表示在以 $i$ 为根的子树内选了 $j$ 个数。合并的时候前面一部分可以直接加起来，后面一部分会多出 $-2 \times a_i \times k \times l$ 的贡献，树上背包即可，时间复杂度 $O(n ^ 2)$。

[记录。](https://codeforces.com/contest/1580/submission/307411893)

---

## 作者：Rainsleep (赞：0)

[cnblog](https://www.cnblogs.com/Rainsheep/p/18565029)

最值相关问题我们有常用的 最值分治/笛卡尔树/单调栈 的经典做法，即处理出每个点作为最值能覆盖的区间的左端点/右端点。

注意一个关键点：**在笛卡尔树上，任意两个点在原序列上最小值的下标，为两点在原树上的 LCA。**

>因为笛卡尔树是 BST，所以子树内的下标连续，又因为笛卡尔树是堆，所以根节点一定是最小值。

知道了这点之后，我们考虑枚举 LCA，并在 LCA 处统计贡献。我们有 $f_{u, j}$ 表示在 $u$ 的子树内选取了 $j$ 个位置的最大贡献。

转移考虑树形背包，根据经典结论复杂度为 $O(n^2)$。

```cpp
// 如果命运对你缄默, 那就活给他看。
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
// #define int LL
const int maxn = 4010;
int m, a[maxn];
int n;
LL f[maxn][maxn];
namespace tr {
  int s[maxn][2];
  int st[maxn], t = 0;
  inline void build() {
    for(int i = 1; i <= n; ++ i) {
      int k = t;
      while(k && a[st[k]] > a[i]) k -- ;
      if(k) s[st[k]][1] = i;
      if(k < t) s[i][0] = st[k + 1];
      st[t = (++ k)] = i;
    }
  }
  int sz[maxn];
  LL g[maxn];
  inline LL cmx(LL& x, LL y) {
    if(y > x) x = y; return x;
  }
  inline void solve(int u) {
    sz[u] = 1;
    f[u][1] = 1LL * m * a[u] - a[u];
    for(int v : {s[u][0], s[u][1]}) {
      if(!v) continue ;
      solve(v);
      for(int j = 0; j <= sz[u] + sz[v]; ++ j) g[j] = f[u][j];
      for(int j = 0; j <= sz[u]; ++ j) {
        for(int k = 0; k <= sz[v]; ++ k) {
          cmx(g[j + k], (LL)f[u][j] + f[v][k] - 2LL * j * k * a[u]);
        }
      }
      sz[u] += sz[v];
      for(int j = 0; j <= sz[u]; ++ j) f[u][j] = g[j];
    }
  }
}
signed main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  ios :: sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= n; ++ i) cin >> a[i];
  tr :: build();
  tr :: solve(tr :: st[1]);
  cout << f[tr :: st[1]][m] << '\n';
  return 0; 
}
```

---

## 作者：happybob (赞：0)

被套路题打败了。

区间最小值不是容易刻画的，考虑一个刻画方式是，区间 $[l,r]$ 的最小值等于笛卡尔树上 $l$ 和 $r$ 的 $\operatorname{LCA}$ 的点权。然后考虑树上背包。记 $f_{i,j}$ 表示子树 $i$ 内选了 $j$ 个点的答案，转移是简单的，总复杂度 $O(n^2)$。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <stack>
using namespace std;

using ll = long long;

const int N = 4005;

int n, m, rt;
array<int, N> ls, rs, sz, a;
array<array<ll, N>, N> f;
array<ll, N> g;
stack<int> st;

void dfs(int u)
{
	sz[u] = 1;
	f[u][0] = 0ll;
	f[u][1] = 1ll * (m - 1) * a[u];
	for (auto& j : { ls[u], rs[u] })
	{
		if (!j) continue;
		dfs(j);
		for (int x = 0; x <= sz[u]; x++) g[x] = f[u][x];
		for (int x = 0; x <= sz[j]; x++)
		{
			for (int y = 0; y <= sz[u] && x + y <= m; y++)
			{
				f[u][x + y] = max(f[u][x + y], g[y] + f[j][x] - 2ll * x * y * a[u]);
			}
		}
		sz[u] += sz[j];
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 0; i < N; i++) f[i].fill((ll)-1e18);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		while (st.size() && a[i] <= a[st.top()])
		{
			ls[i] = st.top();
			st.pop();
		}
		if (st.size()) rs[st.top()] = i;
		else rt = i;
		st.push(i);
	}
	dfs(rt);
	cout << f[rt][m] << "\n";
	return 0;
}
```

---

## 作者：intel_core (赞：0)

看到区间 $\min$ 的答案式，果断考虑笛卡尔树。

设 $f_{i,j}$ 为 $i$ 子树内选了 $j$ 个点的贡献。这里贡献的定义是所有正贡献和子树内的点两两负贡献的差。

转移直接枚举 $x,y$，然后将 $xy\times val_u$ 的负贡献算上，树形背包就行。

总复杂度 $O(n^2)$。

---

