# Fake Plastic Trees

## 题目描述

We are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is the vertex $ 1 $ and the parent of the vertex $ v $ is $ p_v $ .

There is a number written on each vertex, initially all numbers are equal to $ 0 $ . Let's denote the number written on the vertex $ v $ as $ a_v $ .

For each $ v $ , we want $ a_v $ to be between $ l_v $ and $ r_v $ $ (l_v \leq a_v \leq r_v) $ .

In a single operation we do the following:

- Choose some vertex $ v $ . Let $ b_1, b_2, \ldots, b_k $ be vertices on the path from the vertex $ 1 $ to vertex $ v $ (meaning $ b_1 = 1 $ , $ b_k = v $ and $ b_i = p_{b_{i + 1}} $ ).
- Choose a non-decreasing array $ c $ of length $ k $ of nonnegative integers: $ 0 \leq c_1 \leq c_2 \leq \ldots \leq c_k $ .
- For each $ i $ $ (1 \leq i \leq k) $ , increase $ a_{b_i} $ by $ c_i $ .

What's the minimum number of operations needed to achieve our goal?

## 说明/提示

In the first test case, we can achieve the goal with a single operation: choose $ v = 2 $ and $ c = [1, 2] $ , resulting in $ a_1 = 1, a_2 = 2 $ .

In the second test case, we can achieve the goal with two operations: first, choose $ v = 2 $ and $ c = [3, 3] $ , resulting in $ a_1 = 3, a_2 = 3, a_3 = 0 $ . Then, choose $ v = 3, c = [2, 7] $ , resulting in $ a_1 = 5, a_2 = 3, a_3 = 7 $ .

## 样例 #1

### 输入

```
4
2
1
1 5
2 9
3
1 1
4 5
2 4
6 10
4
1 2 1
6 9
5 6
4 5
2 4
5
1 2 3 4
5 5
4 4
3 3
2 2
1 1```

### 输出

```
1
2
2
5```

# 题解

## 作者：hsfzLZH1 (赞：7)

### 题目大意

$t$ 组数据，每组给定一个 $n$ 个结点的树， **根为 $1$** ，给定 $2,3,\ldots ,n$ 的父结点 $p_2,p_3,\ldots ,p_n$ 。再给出每个点权值 $a_i$ 的范围 $[l_i,r_i]$ 。

初始每个点的权值均为 $0$ 。每次操作可以选择从 $1$ 开始的树上路径 $b_1,b_2,\ldots,b_k$ （不一定要在叶子处结束），将 $a_{b_i}$ 加上 $c_i$ ，其中 $\{c_i\}$ 是一个 **非负单调非减** 的 **整数** 数列。

问至少多少次操作，可以令所有点点权均在 $[l_i,r_i]$ 范围内。

$1\le t\le 1000,2\le n\le 2\times 10^5,\sum n\le 2\times 10^5,1\le p_i<i,1\le l_i\le r_i\le 10^9$

### 解题思路

考虑对一组特定的最终点权 $a_i$ ，如何计算最小操作数。

对于叶子结点，一定可以一次操作将 $0$ 变为 $a_i$ 。将过一个点 $i$ 的所有操作整合起来，满足加上的数之和等于 $a_i$ ，且其父亲加上的数为 $[0,a_i]$ 中的一个整数值。

对于一个点 $i$ ，设其子结点为 $son$ ，若有 $a_i>\sum a_{son}$ ，则必须有一次操作以该点为终点，反之可以从以其子孙为终点的操作中将该点点权减为 $0$ 。

接下来是确定最终点权的最优值 $a_i$ 。应用贪心思想，对于子结点，我们希望其 $a_i$ 尽量大，这样其父亲更不容易占用一次操作。从叶子向根，对叶子结点 $i$ ，我们将其点权赋值为 $r_i$ ；对非叶子结点 $x$ ，若 $\sum a_{son}>l_x$ ，则将该点赋值为 $\operatorname{max}\{r_x,\sum a_{son}\}$ ，不会增加操作且对后续影响最优；若 $\sum a_{son}\le l_x$ ，则该点必将占用一次操作，将点权赋值为 $r_x$ ，后续最优。

时间复杂度 $O(n)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=4200010;
#define int long long
int T,n,fa[maxn],l[maxn],r[maxn],a[maxn],ans;
int cur,h[maxn],nxt[maxn],p[maxn];
void add_edge(int x,int y){cur++;nxt[cur]=h[x];p[cur]=y;h[x]=cur;}
void dfs(int x)
{
	int sum=0;
	for(int j=h[x];j;j=nxt[j])dfs(p[j]),sum+=a[p[j]];
	if(l[x]>sum)ans++,a[x]=r[x];
	else a[x]=min(r[x],sum);
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		cur=0;for(int i=1;i<=n;i++)h[i]=0;
		for(int i=2;i<=n;i++)scanf("%lld",fa+i),add_edge(fa[i],i);
		for(int i=1;i<=n;i++)scanf("%lld%lld",l+i,r+i);
		ans=0;dfs(1);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：7)

显然是树形 DP（其实类似贪心）。

设 $f_x$ 表示满足 $x$ 为根的子树都满足条件的所需最少操作数，$g_x$ 表示满足条件后 $x$ 节点的最大可能权值（为何最大：给祖先留值域）。

对于叶子 $x$：$f_x=1,g_x=r_x$。

对于非叶子 $x$，设儿子的 $f$ 和为 $F$，$g$ 和为 $G$：

* $G\ge l_x$，可以不用动，$f_x=F,g_x=\min(r_x,G)$。

* $G< l_x$，必须要在此节点操作，$f_x=F+1,g_x=r_x$。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug cerr<<"Line#"<<__LINE__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int long long
#define N 200010
#define pi pair<int,int>
int n,f[N],g[N]; 
pi a[N];
vector<int> e[N];
void work(){
	cin>>n;
	For(i,1,n) e[i].clear();
	int x,y; 
	For(i,2,n){
		cin>>x;
		e[x].pb(i);
	}
	For(i,1,n) cin>>a[i].fir>>a[i].sec; 
	Rof(i,n,1){
		if(e[i].empty()){
			f[i]=1;
			g[i]=a[i].sec;
		}else{
			x=0;y=0;
			for(int j:e[i]){
				x+=f[j];
				y+=g[j];
			}
			if(y>=a[i].fir){
				f[i]=x;
				g[i]=min(a[i].sec,y);
			}else{
				f[i]=x+1;
				g[i]=a[i].sec;
			}
		}
	}
	cout<<f[1]<<endl;
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

## 作者：kbzcz (赞：4)




### 思路
可以从叶子节点往上考虑。显然，每个叶子节点必须分别进行一次操作，因为不在同一路径上。   
继续考虑每次加的值。因为数组要求单调递增，所以 $c_i$ 越大，对于 $c_{i-1}$ 的选择就越多，显然可以贪心，因此我们让每个叶子节点的值都赋成 $r_i$。

那对于树上的一个节点 $x$，假设他的所有子节点的权值都已经确定，因为加的序列单调不降，则该节点的最大取值就是 $val_x=\sum\limits_{v\in son_x} val_v$。所以，当这个点的 $l_x > val_x$ 时，就代表还需进行一次操作，而根据贪心，直接把权值加成 $r_x$ 最优。   
而当 $val_x > l_x$ 时，这个点就不需要进行操作了，直接和 $r_x$ 取 $\min$。

### 代码
```cpp
bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define _int __int128
#define LL long long
#define DB double
#define ull unsigned long long
#define PII pair<int,int>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp inline void read(T& x) {
	x=0;char c=getchar();bool f=0;
	for(;c<48||c>57;c=getchar()) f|=c=='-';
	for(;c>47&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	f&&(x=-x);
}Ts inline void read(T& x,_T&... y) {read(x),read(y...);}
const int INF=0x3f3f3f3f;
const LL LNF=1e18;
const int N=2e5+5;
int n;
struct edge {
	int x,y,pre;
}a[N];int alen,last[N];
void ins(int x,int y) {
	a[++alen]=edge{x,y,last[x]};
	last[x]=alen;
}
pair<LL,LL> val[N];
LL f[N],ans;
void dfs(int x) {
	LL sum=0;
	for(int k=last[x];k;k=a[k].pre) {
		int y=a[k].y;
		dfs(y);
		sum+=f[y];
	}
	if(sum>=val[x].first) f[x]=min(sum,val[x].second);
	else f[x]=val[x].second,ans++;
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	int T;read(T);
	while(T--) {
		memset(f,0,sizeof(f));
		alen=0;memset(last,0,sizeof(last));
		read(n);
		for(int i=2;i<=n;i++) {
			int x;read(x);
			ins(x,i);
		}
		for(int i=1;i<=n;i++) read(val[i].first),read(val[i].second);
		ans=0,dfs(1);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Purple_Circle (赞：4)

这道题很明显是一道树形 DP。

设 $x$ 为当前节点, $sum$ 为 $x$ 的所有子节点权值和。

考虑将当前 $a_x$ 最大化，使得其父节点尽量减少操作次数。

则当左区间 $l_x>sum$ 时，将点权赋值为 $r_x$，此时必须完成一次操作，且后续为最优。

否则将点权赋值为 $\min(r_x,sum)$，不会增加操作且为最优。

DP 代码：
```cpp
void dfs(int x){
	ll sum=0;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		dfs(y);
		sum+=p[y].a;
	}
	if(p[x].l>sum){
		ans++;
		p[x].a=p[x].r;
	}else{
		p[x].a=min(p[x].r,sum);
	}
}
```

AC代码如下：
```cpp
#include <bits/stdc++.h>
#define rd read()
using namespace std;
using ll=long long;//将long long 重定义为ll，与define同作用
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
ll T,n,fa[2000010],ans;
struct node{
	ll a;
	ll l;
	ll r;
}p[2000010];
ll tot,head[2000010];
struct edge{
	ll to;
	ll next;
}e[2000010];
void add(int x,int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}
//dfs函数见上
int main(){
	T=rd;
	while(T--){
		n=rd;
		tot=0,ans=0;
		memset(head,0,sizeof(head));
		for(int i=2;i<=n;i++){
			fa[i]=rd;
			add(fa[i],i);
		}
		for(int i=1;i<=n;i++){
			p[i].l=rd;
			p[i].r=rd;
		}
		dfs(1);
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：Argon_Cube (赞：3)

* **【题目链接】**

[Link:CF1693B](https://www.luogu.com.cn/problem/CF1693B)

* **【解题思路】**

考虑哪些点一定要进行一次到它的操作。我们假设每一个点已经定好了目标权值。

显然，当一个点的所有儿子的权值和大于等于该点权值，那么就没有必要对它进行一次操作，否则就要多使用一次操作。

我们考虑从儿子到父亲依次处理出所有点的权值，与所有儿子的权值之和（显然父亲的权值不能大于所有儿子的权值之和，否则需要额外操作）。并且无论如何，这个点的权值取得越大越好。

于是，当这个点无论如何都要进行一次操作（即儿子权值和小于该点权值下限），那么我们就直接让这个点的权值为上限，并增加答案；否则，我们就让这个点的权值为权值上限与儿子权值和中的较小值。

边界条件：叶子节点儿子权值和为 $0$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<int,200001>			father;
array<long long,200001>		subt_sum;
array<pair<int,int>,200001>	target;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int cnt,ans=0;
		cin>>cnt;
		subt_sum[1]=0;
		for(int i=2;i<=cnt;i++)
			cin>>father[i],subt_sum[i]=0;
		for(int i=1;i<=cnt;i++)
			cin>>target[i].first>>target[i].second;
		for(int i=cnt;i;i--)
			if(subt_sum[i]>=target[i].first)
				subt_sum[father[i]]+=min<long long>(target[i].second,subt_sum[i]);
			else
				++ans,subt_sum[father[i]]+=target[i].second;
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：cmrhhh (赞：1)

## 思路
从叶子向上更新的方向思考，并用递归实现。因为父节点依赖于子节点（单调不降），这样做就不需要考虑根节点的初始增量。每个子节点贪心一点要尽可能大，使父节点的调控次数尽可能少。父节点的增量需要提供每个子节点，贪心后至多是子节点增量之和，再和父节点的最小值比较，小了就必定要多一次操作。否则就和父节点最大值比较，不操作。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,p,l[maxn],r[maxn],a[maxn];
int ans=0;
vector<int>g[maxn];
void dfs(int x){
	int sum=0;
	for(int i=0;i<g[x].size();++i){
		dfs(g[x][i]);
		sum+=a[g[x][i]];
	}
	if(sum<l[x])a[x]=r[x],ans++;
	else a[x]=min(r[x],sum);
}int t;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=2;i<=n;++i)cin>>p,g[p].push_back(i);
		for(int i=1;i<=n;++i)cin>>l[i]>>r[i];
		dfs(1);
		cout<<ans<<"\n";
		for(int i=1;i<=n;++i)g[i].clear(),a[i]=0;
	}
	return 0;
}
```

---

## 作者：wwxxbb (赞：0)

## 题意

> 树上每个点都有一个权值，初始为 $0$，至少进行几次操作才能使得每个点的数字都在指定的范围内$(l_v\le a_v\le r_v)$，操作如下：
>
> - 选择某个顶点 $v$。
>
> - 令 $b_1,b_2,\cdots,b_k$ 是从根节点 $1$ 到点 $v$ 的路径上的点 ，即 $b_1=1,b_k=v,b_i=p_{b_i}$。
> - 选择一个长度为 $k$ 的非递减数组 $c$ ，其中 $c_1\le c_2\le\cdots\le c_k$ 且数组元素都是非负整数。
> - 对于每个 $i\in[1,k]$，给 $a_{b_i}$ 加上 $c_i$。

## 思路

贪心地，对于每个节点 $u$，因为 $c$ 数组非递减，所以我们要使 $c_u$ 尽量大，这样可以使父节点尽量减少操作次数，所以我们把权值赋成 $r_u$ 最优。

假设节点 $u$ 的所有子节点的权值都已经确定，则该节点的最大权值为 $\sum_{v\in\text{son}_u}a_v$。如果该值比左边界 $l_u$ 小，那就把它赋成 $r_u$，并让答案加 $1$；否则，就不需要任何操作，直接和 $r_u$ 取 $\min$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int t, n, l[N], r[N];
struct Edge {int to, ne;} e[N<<1]; // 单向边即可，写错了，但没有关系
int h[N], idx;
void add(int u, int v) {e[idx] = {v, h[u]}, h[u] = idx ++;}

long long f[N], ans;
void dfs(int u, int fa) {
    for (int i = h[u]; ~i; i = e[i].ne) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
        f[u] += f[v];
    }
    if (f[u] < l[u]) f[u] = r[u], ans ++;
    else f[u] = min(f[u], 1ll * r[u]);
}

void solve() {
    memset(h, -1, sizeof h); idx = 0;
    memset(f, 0, sizeof f); ans = 0; // clear
    cin >> n;
    for (int i = 2, u; i <= n; i ++) {
        cin >> u;
        add(u, i), add(i, u); // 这里加单向边就可以了
    }
    for (int i = 1; i <= n; i ++)
        cin >> l[i] >> r[i];
    dfs(1, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t --) solve();
    return 0;
}
```

---

## 作者：_zhx (赞：0)

# CF1693B Fake Plastic Trees 题解

### 大致思路

贪心，从叶子节点往上推。

对于当前节点，先记录自己子树（除自己）的贡献。

- 如果贡献小于自己的左区间，那么就使用一次机会，将自己的权值直接上传到根节点。

- 否则就将贡献与右区间取最小值。最后输出答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
long long t,n,w[N],l[N],r[N],p,ans;
vector<long long>v[N];
void dfs(long long u)
{
	long long sum=0;
	for(long long i=0;i<v[u].size();i++)
	{
		dfs(v[u][i]);
		sum+=w[v[u][i]];
	}
	if(sum<l[u]) w[u]=r[u],ans++;
	else w[u]=min(r[u],sum);
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(long long i=1;i<=n;i++) v[i].clear();
		for(long long i=2;i<=n;i++)
		{
			cin>>p;
			v[p].push_back(i);
		}
		for(long long i=1;i<=n;i++) cin>>l[i]>>r[i];
		ans=0;dfs(1);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

## 思路
贪心，从叶子节点往上。对于当前节点，先记录自己儿子的贡献，如果贡献小于自己的左区间，那么就使用一次机会，将自己的权值直接顶到有区间，否则就将贡献与右区间取最小值。最后输出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
int w[N],l[N],r[N];
vector<int>G[N];
int n;
int ans;
void dfs(int u){
	int cnt=0;
	for(int i=0;i<G[u].size();i++){
		dfs(G[u][i]);
		cnt+=w[G[u][i]];
	}
	if(cnt<l[u]){
		w[u]=r[u];
		ans++;
	}
	else{
		w[u]=min(r[u],cnt);
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		for(int i=1;i<=n;i++){
			G[i].clear();
		}
		cin>>n;
		ans=0;
		for(int i=2;i<=n;i++){
			int p;
			cin>>p;
			G[p].push_back(i);
		}
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
		}
		dfs(1);
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：baka24 (赞：0)

对于每个点算出它的贡献最高值，计算满足它是否可以直接利用它子树内节点所使用的次数，不行就次数加一。

具体地说，我们计 $q_u$ 表示当前节点能填的最高价值。

$$
q_u=
\begin{cases}
\sum q_{son}<l_u &r_u &\text{增加 }ans\\
r_u \ge \sum q_{son}\ge l_u &\sum q_{son}\\
\sum q_{son}>r_u &r_u
\end{cases}
$$

扫一遍全树求每个点的 $q_u$ 即可。

### code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=200010;
int t,n,p[MAXN],l[MAXN],r[MAXN],ans,q[MAXN];
struct Edge{int v,nx;}edge[MAXN<<1];int h[MAXN],CNT;void init(){for(int i=1;i<=n;i++)q[i]=0,h[i]=-1;CNT=0;}
void add_side(int u,int v){edge[++CNT]={v,h[u]};h[u]=CNT;}
void dfs(int now){
    if(h[now]==-1){
        q[now]=r[now];ans++;
        return;
    }
    int sum=0;
    for(int i=h[now];i!=-1;i=edge[i].nx){
        dfs(edge[i].v);
        q[now]+=q[edge[i].v];
    }
    if(l[now]>q[now]){
        q[now]=r[now];ans++;
    }
    if(q[now]>r[now])q[now]=r[now];
}
void slv(){ans=0;
    scanf("%lld",&n);init();
    for(int i=2;i<=n;i++){
        scanf("%lld",&p[i]);
        add_side(p[i],i);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l[i],&r[i]);
    }
    dfs(1);
    printf("%lld\n",ans);
}
signed main(){
    scanf("%lld",&t);
    while(t--)slv();
    return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 题意简述
树的根是顶点 $1$，顶点 $v$ 的父节点是 $p_v$。调整每个顶点上的数字，使得每个顶点的数字都在其指定的范围内 $(l_v \le a_v \le r_v)$。

在单次调整中，我们执行以下操作：

- 选择某个顶点 $v$。
- 令 $b_1,b_2,...,b_k$ 是从顶点 $1$ 到顶点 $v$ 的路径上的顶点（即 $b_1=1$，$b_k=v$，并且 $b_i$ 是 $p_{b_{i+1}}$。
- 选择一个长度为 $k$  的**非递减**数组 $c$ ，其中 $c_1 \le c_2 \le ... \le  c_k$ 数组元素都是**非负整数**。
- 对于每个 $i\ (1 \le i \le k)$，给 $a_{b_i}$ 加上 $c_i$。

求至少需要多少次操作才能完成这个调整。
# 思路解析
考虑**DFS**。
我们从根节点开始进行深度优先搜索，计算每个节点的值。

对于每个节点 $u$，我们计算其子节点的值之和 $tag$。
- 如果 $tag > {r_u}$，则 $u$ 的值为 $r_u$。
- 如果 $tag < l_u$，则需要进行一次操作，将 $u$  的值增加到 $r_u$，并将操作次数加 $1$。
- 否则 $u$ 的值为 $tag$。
# 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, fa[N], l[N], r[N], ans, T;
vector<int> edge[N];
int dfs(int u) {
    int tag = 0;
    for (int v : edge[u])
        tag += dfs(v);
    if (tag > r[u])
        return r[u];
    if (tag < l[u]) {
        ans++;
        return r[u];
    }
    return tag;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    while (T--) {
        ans = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
        }
        for (int i = 2; i <= n; ++i) {
            cin >> fa[i];
            edge[fa[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i)
            cin >> l[i] >> r[i];
        dfs(1);
        cout << ans << '\n';
    }
    return 0;
}
```

---

