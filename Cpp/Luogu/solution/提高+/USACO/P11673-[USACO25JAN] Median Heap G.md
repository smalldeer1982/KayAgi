# [USACO25JAN] Median Heap G

## 题目描述

**注意：本题的时间限制为 4 秒，通常限制的 2 倍。**

Farmer John 有一棵包含 $N$ 个结点的二叉树，结点编号从 $1$ 到 $N$（$1 \leq N < 2\cdot 10^5$，$N$ 为奇数）。对于 $i>1$，结点 $i$ 的父结点为 $\lfloor i/2\rfloor$。每个结点都有一个初始整数值 $a_i$，以及将初始值修改为任意其他整数值的代价 $c_i$（$0\le a_i,c_i\le 10^9$）。

他被联邦牛务局（Federal Bovine Intermediary，FBI）委托在这棵树中求出一个近似中位数值，并为此设计了一个聪明的算法。

他从最后一个结点 $N$ 开始向前执行。在算法的每一步，如果一个结点不是它和它的两个结点的中位数，他就交换当前结点和值为中位数的子结点的值。在这个算法结束时，结点 $1$（根结点）上的值即为近似中位数。

FBI 同时给 Farmer John 提供了一份包含 $Q$（$1 \leq Q \leq 2\cdot 10^5$）个独立的询问的清单，每一个询问指定一个目标值 $m$（$0\le m\le 10^9$）。对于每一个询问，FJ 首先会修改某些结点的初始值，然后执行近似中位数算法。对于每一个询问，求 FJ 使得算法输出等于 $m$ 所需要的最小总代价。

## 说明/提示

样例 1 解释

为了使近似中位数等于 $40$，FJ 可以将结点 3 的值修改为 $60$。这需要花费 $c_3=100$。

为了使近似中位数等于 $45$，FJ 可以将结点 3 的值修改为 $60$，结点 5 的值修改为 $45$。这需要花费 $c_3+c_5=100+1=101$。

- 测试点 $2\sim 4$：$N,Q\le 50$。
- 测试点 $5\sim 7$：$N,Q\le 1000$。
- 测试点 $8\sim 16$：没有额外限制。

## 样例 #1

### 输入

```
5
10 10000
30 1000
20 100
50 10
40 1
11
55
50
45
40
35
30
25
20
15
10
5```

### 输出

```
111
101
101
100
100
100
100
0
11
11
111```

# 题解

## 作者：FFTotoro (赞：8)

金组签到题。

定义**修改操作**为将某个结点的值修改为另一个值的操作，定义**替换操作**为将某个结点的值替换为它与两个儿子的值的中位数的操作。

考虑暴力：对于每个询问 $m$，暴力地从下往上做树形 DP，假设当前考虑到结点 $u$ 且 $u$ 有两个儿子；令 $f_{u,0/1/2}$ 分别表示使结点 $u$ 上**执行替换操作后**的值小于 / 等于 / 大于 $m$ 的最小花费，$w_{u,0/1/2}$ 分别表示使结点 $u$ 上**执行修改操作后、执行替换操作前**的值小于 / 等于 / 大于 $m$ 的最小花费，$u$ 的两个儿子为 $k_1,k_2$，则有转移：

$f_{u,i}=\min\limits_{\operatorname{med}(x,y,z)=i}f_{k_1,x}+f_{k_2,y}+w_{u,z}$

其中 $\operatorname{med}(x,y,z)$ 表示 $x,y,z$ 的中位数。$w$ 的值直接考虑结点的初始值是否需要被修改即可。对于 $u$ 没有儿子的情况，则 $f_u\gets w$。

观察到可以离线所有询问：将询问 $m$ 从小到大排序，$w_{u,0/1/2}$ 的值至多被修改 $2$ 次（小于变为等于，等于变为大于），而每次修改只会影响到 $u$ 以及 $u$ 的祖先，而完全二叉树的树高是 $O(\log n)$ 级别的，所以暴力往上跳父亲进行修改即可。时间复杂度 $O(n\log n+q\log q)$

赛时代码，常数较大。放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int median(int x,int y,int z){
  return x+y+z-max({x,y,z})-min({x,y,z});
} // 求三个数的中位数
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,l1=0,l2=0; cin>>n;
  vector<int> a(n+1),c(n+1);
  for(int i=1;i<=n;i++)
    cin>>a[i]>>c[i];
  vector<int> ps(n);
  iota(ps.begin(),ps.end(),1);
  sort(ps.begin(),ps.end(),[&](int x,int y){
    return a[x]<a[y];
  }); // 将结点按权值排序，方便找到需要修改的结点
  vector f(n+1,vector<ll>(3,1e18));
  int q; cin>>q;
  auto upd=[&](int u,int m){
    f[u]=vector<ll>(3,1e18);
    vector<ll> w(3);
    if(a[u]<m)w[1]=w[2]=c[u];
    else if(a[u]==m)w[0]=w[2]=c[u];
    else w[0]=w[1]=c[u];
    // 预处理修改花费 w
    if((u<<1|1)<=n){
      for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
          for(int k=0;k<3;k++){
            int m=median(i,j,k);
            f[u][m]=min(f[u][m],f[u<<1][i]+f[u<<1|1][j]+w[k]);
          } // 暴力枚举三个结点的值
    } // 有儿子
    else f[u]=w; // 没有儿子
  };
  auto g=[&](int x,int m){
    for(int i=0;x>>i;i++)
      upd(x>>i,m);
  }; // 暴力跳祖先进行更新
  vector<pii> Q(q);
  for(int i=0;i<q;i++)
    cin>>Q[i].first,Q[i].second=i;
  vector<ll> R(q);
  sort(Q.begin(),Q.end());
  for(int i=n;i;i--)
    g(i,0);
  for(auto [m,p]:Q){
    while(l1<n&&a[ps[l1]]<m)g(ps[l1++],m);
    while(l2<n&&a[ps[l2]]<=m)g(ps[l2++],m);
    R[p]=f[1][1];
  } // 离线下来扫描
  for(ll i:R)cout<<i<<'\n';
  return 0;
}
```

---

## 作者：_LSA_ (赞：7)

本做法来自官方题解。

考虑单次询问 $m$ 怎么做。

我们定义 $\text{med}({a,b,c})$ 表示 $a,b,c$ 的中位数，

我们再定义
$$p_m(x) = \begin{cases} 0 & x < m \\ 1&x = m \\2 & x > m\end{cases}$$

容易发现

$$p_m(\text{med}({a,b,c}))=\text{med}({p_m(a),p_m(b),p_m(c)})$$

也就是说对于一个固定的询问 $m$，我们只关心树上每个节点的 $a$ 与 $m$ 的大小关系，这样我们就得到了一个状态数为 $3\times n$ 的 dp。

即设 $f_{i,j}$ 表示节点 $i$ 在操作完整棵子树后得到的中位数 $x$ 的 $p_m(x)=j$ 的最小花费，其中 $j=0/1/2$。

转移直接 $3^3$ 暴力枚举自己和两个儿子的 $p_m(x)$ 即可，这样单次询问的复杂度为 $O(n)$。

多次询问时，我们发现可以将询问离线并按 $m$ 从小到大扫，而由于每个节点的 dp 值会发生变化当且仅当它的儿子的 dp 值改变，或它自己 $p_m(x)$ 从发生改变。所以我们先对最小的 $m$ 做一次 dp，而在扫 $m$ 的过程中每当某个节点的 $p_m(x)$ 值发生改变时，我们暴力把这个节点和它所有的祖先的 dp 值重新计算一遍即可，由于树高是 $O(\log n)$ 级别的，所以暴力修改一次的复杂度也是 $O(\log n)$ 级别的。又由于我们将 $m$ 从小到大扫，每个节点的 $p_m(x)$ 最多变化两次，所以这么做的总复杂度是 $O(n\log n)$ 级别的，有个 $2\times3^3$ 的常数。

加上排序，我们做到了 $O(n \log n+q\log q)$，足以通过此题。

---

## 作者：Gordon_Song (赞：3)

dp 题。

首先先把 $a$ 和 $m$ 离散化，变成 $[1,n+q]$ 之间的数。

现在来分析这一“近似中位数”的特性：不妨设当前节点为 $x$，$p_i$ 表示 $i$ 的子树操作完后，$i$ 这个节点上的值是多少。那么 $p_x = y$ 的充要条件是 $a'_x$（替换操作进行完之后的 $a_x$ 值，与原来的 $a_x$　做区分），$p_{2x}$，$p_{2x+1}$ 中，恰好有一个小于等于 $y$，一个等于 $y$，一个大于等于 $y$。

此时，就能自然而然地设出一个 dp 的状态：设 $dp_{i,j}$ 表示希望令 $p_i = j$，至少需要在子树内支付多少代价。但是我们发现直接这样设好像无法转移，还需要两个辅助数组： $dp1_{i,j}$ 表示希望令 $p_i \leq  j$　的最小代价，$dp2_{i,j}$ 表示希望令 $j \leq p_i$ 的最小代价。转移方程比较繁琐，但不难推导（具体见文末的代码的  `push_down` 函数 
）。

就这样，我们有了一个 $O(n^2)$ 的做法。但是这样只能拿到 $7$ 个测试点的分数，显然不够。

然而，如果考虑 $j$ 的值从 $y$ 变成 $y+1$，会发现实际上 $dp$ 值变化的点很少。对于所有 $x | a_x = y-1$ 以及 $x| a_x = y$ 的 $x$，只有 $x$ 以及他到根的节点的值可能会变！由于这些数加起来一共只有 $O(n)$ 个，所以在 $j$ 从 $1$ 一直移动到 $n+q$ 的过程中总共只需要改变 $n \log n$ 个位置的 $dp$ 值。

所以我们可以添加一个优化，只在 $dp_{x,j}$ 中更改 $a_x = j$ 或 $a_x = j+1$ 的 $x$ 到根的路径上的节点的 $dp$ 值，从而得到 $dp_{x,j+1}$，经过优化后的复杂度为 $O((n+q) \log n)$。不明白为什么开 4 秒……


```cpp
int n,q;
const int MAXN=2e6+5;
int a[MAXN],c[MAXN];
int p[MAXN],l,now;
int d[MAXN]; 
vector<int>que[MAXN],poi[MAXN];
ll tox[MAXN],toe[MAXN],tod[MAXN];//tox：文中的 dp1，toe：文中的 dp，tod：文中的 dp2
void push_up(int x){//转移方程
	tox[x]=min({tox[x<<1]+(a[x]>now)*c[x],tox[x<<1|1]+(a[x]>now)*c[x],tox[x<<1]+tox[x<<1|1]});
	tod[x]=min({tod[x<<1]+(a[x]<now)*c[x],tod[x<<1|1]+(a[x]<now)*c[x],tod[x<<1]+tod[x<<1|1]});
	toe[x]=min({min(tox[x<<1]+tod[x<<1|1],tod[x<<1]+tox[x<<1|1])+(a[x]!=now)*c[x],
	toe[x<<1]+min((a[x]>now)*c[x]+tod[x<<1|1],(a[x]<now)*c[x]+tox[x<<1|1]),
	toe[x<<1|1]+min((a[x]>now)*c[x]+tod[x<<1],(a[x]<now)*c[x]+tox[x<<1])});
}
ll ans[MAXN];
void dfs(int x){
	if(x>n){
		toe[x]=1e18;
		return ;
	}
	if((x<<1)>n){
		toe[x]=(a[x]!=now)*c[x];
		tod[x]=(a[x]<now)*c[x];
		tox[x]=(a[x]>now)*c[x];
	}else{
			
		dfs(x<<1);dfs(x<<1|1);
		push_up(x);
	}
//	printf("%d  %d %d %lld %lld %lld\n",x,a[x],c[x],tod[x],tox[x],toe[x]);
}
void pus(int x){
	if(!x)return ;
	if(x*2>n){
		toe[x]=(a[x]!=now)*c[x];
		tod[x]=(a[x]<now)*c[x];
		tox[x]=(a[x]>now)*c[x];
		
	}else{
		push_up(x);
	}
	
	pus(x>>1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&c[i]);
		p[++l]=a[i];
	}scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&d[i]);p[++l]=d[i];
	}

  //离散化
	sort(p+1,p+1+l);
	l=unique(p+1,p+1+l)-p-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(p+1,p+1+l,a[i])-p;
		poi[a[i]].push_back(i);
	}
	for(int i=1;i<=q;i++){
		d[i]=lower_bound(p+1,p+1+l,d[i])-p;
		que[d[i]].push_back(i);
	}


	dfs(1);
//	now=4;
//	dfs(1);
	
	for(int i=1;i<=l;i++){
		now=i;
//		dfs(1);
		
		for(int j=0;j<poi[i-1].size();j++){
			pus(poi[i-1][j]);
		}
		for(int j=0;j<poi[i].size();j++){
			pus(poi[i][j]);
		}
		for(int j=0;j<que[i].size();j++){
			ans[que[i][j]]=toe[1];
		}
	//	printf("now=%d:\n",i);
	//	for(int j=1;j<=n;j++){
	//		printf("%d %d %d %lld %lld %lld\n",j,a[j],c[j],tox[j],toe[j],tod[j]);
	//	}
	}
	for(int i=1;i<=q;i++){
		printf("%lld\n",ans[i]);
	}
}

```

---

## 作者：ty_mxzhn (赞：3)

感觉质量还可以的题。

因为中位数显然是可以二分的，所以干脆直接利用它的单调性解题。设计 $f_{u,j}$ 表示 $u$ 子树内换上来的点 $<x,=x,>x$，记为 $0,1,2$。

转移是 $\displaystyle f_{u,j}=\min_{\mathcal{M}(a,b,c)=j}f_{ls_u,a}+f_{us_u,b}+W_{u,c}$。其中 $W_{u,c}=[\mathrm{sgn}(a_u-x)=c]$。

考虑 $x$ 的改变。直接离线下来，每个点的 $W_{u,c}$ 至多改变两次，改变的时候往上跳修改 dp 即可。

---

## 作者：MoGuYun_12 (赞：2)

对于每组询问，我们只关心每个点的 $a_i$ 与 $m$ 的相对大小，因为小于 $m$ 和大于 $m$ 的肯定不会成为中位数。而且题目中说每个点可以任意修改成其他数，所以想到用 $f_{i,0/1/2}$ 分别表示以 $i$ 为根的子树得到的中位数小于，等于，大于的最小代价。最后答案即为 $f_{1,1}$。

转移时枚举根节点，左儿子，右儿子与 $m$ 的相对关系，共有 $27$ 种状态。对于每种状态看根节点是否需要与儿子交换位置，用相应的 $w_i$ 转移即可。

然后把询问离线按 $m$ 升序排序，并且把点按 $a_i$ 升序排序。用双指针维护与当前 $a_i$ 与 $m$ 大小发生相对变化的点有哪些，进行更新。

因为是二叉树而且用双指针修改，时间复杂度 $O(n\log n)$，常数很大，但可以通过。


```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ls (x<<1)
#define rs (x<<1|1)

const int inf = 1e19;
const int N = 2e5+5;
int n,q,a[N],c[N],ans[N],f[N][3];
struct query{
	int m,id;
}b[N];
struct node{
	int a,id;
}d[N];

bool cmp1(node x,node y){
	return x.a<y.a;
}
bool cmp2(query x,query y){
	return x.m<y.m;
}
int cal(int x,int y,int z){
	return x+y+z-min({x,y,z})-max({x,y,z});   
}
void update(int x,int m){
	f[x][0]=f[x][1]=f[x][2]=inf;
	vector<int> w(3);
	if(a[x]<m) w[0]=0,w[1]=w[2]=c[x];
	if(a[x]==m) w[1]=0,w[0]=w[2]=c[x];
	if(a[x]>m) w[2]=0,w[0]=w[1]=c[x];
	if(rs>n){
		f[x][0]=w[0],f[x][1]=w[1],f[x][2]=w[2];
		return;
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				int p=cal(i,j,k);
				f[x][p]=min(f[x][p],f[ls][i]+f[rs][j]+w[k]);
			}
		}
	}
}
void pushup(int p,int m){
	while(p){
		update(p,m); p>>=1;
	}
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>c[i],d[i].a=a[i],d[i].id=i;
	sort(d+1,d+n+1,cmp1);
	cin>>q;
	for(int i=1;i<=q;i++) cin>>b[i].m,b[i].id=i;
	sort(b+1,b+q+1,cmp2);
	for(int i=0;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=inf;
	for(int i=n;i>=0;i--) update(i,0);
	int l1=1,l2=1;
	for(int i=1;i<=q;i++){
		while(l1<=n && d[l1].a<b[i].m) pushup(d[l1].id,b[i].m),l1++;
		while(l2<=n && d[l2].a<=b[i].m) pushup(d[l2].id,b[i].m),l2++;
		ans[b[i].id]=f[1][1];
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	return 0;
}

```

---

## 作者：Xy_top (赞：2)

简单题，和 AGC003D 套路一样，但是离线的时候用 map 对于询问映射答案就错了，不清楚为什么。

显然，中位数只和数字之间的相对大小有关，如果先考虑单组询问，可以发现一个很显然的做法。

设目标值为 $x$，设 $dp_{u,0}$ 为以 $u$ 为根的子树，近似中位数 $<x$，$dp_{u,1}$ 是等于 $x$，$dp_{u,2}$ 是大于 $x$，就可以 $O(n)$ 转移。

现在有多组询问，显然可以排序，当我们从小到大排序后，依次更改某些特定节点的点权。我们发现每个点的点权最多改两次，从 $2$ 到 $1$，再从 $1$ 到 $0$。由于是二叉树，每次更新之后暴力跳父亲重新计算 $dp$ 数组是可以接受的。

复杂度 $O(n\log n)$。

``map`` 代码（不知道为什么错了，求调）：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m;
int q1[200005], q2[200005];
int val[200005], cost[200005], dp[200005][3];
struct Node {int p, id;}a[200005];
bool cmp (Node n1, Node n2) {return n1.p < n2.p;}
vector <int> v[200005];
map <int, int> ans;
int get (int i, int j, int k) {
	int b[3] = {i, j, k};
	sort (b, b + 3);
	return b[1];
}
int cg (int x, int y) {
	if (val[x] == y) return 0;
	return cost[x];
}
void mi (int &x, int y) {if (x > y) x = y;}
void upd (int u) {
	if (u * 2 + 1 > n) {
		if (val[u] == 0) {
			dp[u][0] = 0;
			dp[u][1] = dp[u][2] = cost[u];
		} else if (val[u] == 1) {
			dp[u][1] = 0;
			dp[u][0] = dp[u][2] = cost[u];
		} else {
			dp[u][2] = 0;
			dp[u][0] = dp[u][1] = cost[u];
		}
		upd (u / 2);
		return;
	}
	dp[u][0] = dp[u][1] = dp[u][2] = 1000000000000000000LL;
	For (i, 0, 2) For (j, 0, 2) For (k, 0, 2)
		mi (dp[u][get (i, j, k)], cg (u, i) + dp[u * 2][j] + dp[u * 2 + 1][k]);
	if (u == 1) return;
	upd (u / 2);
}
signed main () {
	cin >> n;
	For (i, 1, n) {
		cin >> a[i].p >> cost[i];
		a[i].id = i;
	}
	sort (a + 1, a + n + 1, cmp);
	For (i, 1, n) val[i] = 2;
	foR (i, n, 1) upd (i);
	cin >> m;
	For (i, 1, m) {
		cin >> q1[i];
		q2[i] = q1[i];
	}
	sort (q1 + 1, q1 + m + 1);
	int m_ = m;
	m = unique (q1 + 1, q1 + m + 1) - q1;
	int tail = 0;
	For (i, 1, m) {
		if (i != 1 && tail && q1[i - 1] == a[tail].p) {
			int j = tail;
			while (j && a[j].p == q1[i - 1]) {
				val[a[j].id] = 0;
				upd (a[j].id);
				-- j;
			}
		}
		while (tail != n && a[tail + 1].p < q1[i]) {
			++ tail;
			val[a[tail].id] = 0;
			upd (a[tail].id);
		}
		while (tail != n && a[tail + 1].p == q1[i]) {
			++ tail;
			val[a[tail].id] = 1;
			upd (a[tail].id);
		}
		ans[q1[i] ] = dp[1][1];
	}
	For (i, 1, m_) cout << ans[q2[i] ] << '\n';
	return 0;
}
/*
0 是小于 2 是大于
1 是等于，原先所有都是大于
指针将划到最后一个小于等于当前询问 val_root 值的位置
默认全为大于
*/
```

AC 代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m;
int ans[200005], val[200005], cost[200005], dp[200005][3];
struct Node {int p, id;}a[200005];
struct Query {int num, id;}q1[200005];
bool cmp1 (Query q1, Query q2) {return q1.num < q2.num;}
bool cmp (Node n1, Node n2) {return n1.p < n2.p;}
int get (int i, int j, int k) {
	int b[3] = {i, j, k};
	sort (b, b + 3);
	return b[1];
}
int cg (int x, int y) {
	if (val[x] == y) return 0;
	return cost[x];
}
void mi (int &x, int y) {if (x > y) x = y;}
void upd (int u) {
	if (u * 2 + 1 > n) {
		For (i, 0, 2) dp[u][i] = cg (u, i);
		upd (u / 2);
		return;
	}
	dp[u][0] = dp[u][1] = dp[u][2] = 10000000000000000LL;
	For (i, 0, 2) For (j, 0, 2) For (k, 0, 2)
		mi (dp[u][get (i, j, k)], cg (u, i) + dp[u * 2][j] + dp[u * 2 + 1][k]);
	if (u == 1) return;
	upd (u / 2);
}
signed main () {
	cin >> n;
	For (i, 1, n) {
		cin >> a[i].p >> cost[i];
		a[i].id = i;
	}
	sort (a + 1, a + n + 1, cmp);
	For (i, 1, n) val[i] = 2;
	foR (i, n, 1) upd (i);
	cin >> m;
	For (i, 1, m) {
		cin >> q1[i].num;
		q1[i].id = i;
	}
	sort (q1 + 1, q1 + m + 1, cmp1);
	int tail = 0, lst = -1;
	q1[0].num = -10;
	For (i, 1, m) {
		if (q1[i].num == q1[i - 1].num) {
			ans[q1[i].id] = ans[q1[i - 1].id];
			continue;
		}
		if (lst != -1 && lst == a[tail].p) {
			int j = tail;
			while (j && a[j].p == lst) {
				val[a[j].id] = 0;
				upd (a[j].id);
				-- j;
			}//原来等于的，现在小于
		}
		while (tail != n && a[tail + 1].p < q1[i].num) {
			++ tail;
			val[a[tail].id] = 0;
			upd (a[tail].id);
		}//原来一部分大于的，现在也小于
		while (tail != n && a[tail + 1].p == q1[i].num) {
			++ tail;
			val[a[tail].id] = 1;
			upd (a[tail].id);
		}//原来某些大于的，现在等于
		ans[q1[i].id] = dp[1][1];
		lst = q1[i].num;
	}
	For (i, 1, m) cout << ans[i] << '\n';
	return 0;
}
/*
0 是小于 2 是大于
1 是等于，原先所有都是大于
指针将划到最后一个小于等于当前询问 val_root 值的位置
默认全为大于
*/

```

---

## 作者：hyk2019 (赞：1)

这是一道 **DP** 题。

先处理**单个询问**的情况。

由于我们只关心一个值是否能够通过中位数操作移动到根结点，所以对于每一个值，只需要知道它和 $m$ 的**大小关系**就可以了。因此，我们可以将所有的数**分成三类**：小于 $m$（$j=0$）、等于 $m$（$j=1$）、大于 $m$（$j=2$）。

这样，我们用 $dp_{i,j}$ 表示一个结点的子树经过修改和中位数操作后，该结点的数值的类型是 $j$ 的花费的最小值。

当结点的编号 $\le\lfloor\frac N2\rfloor$ 时：因为一个结点的值**只和自己、左儿子、右儿子三个结点的数值有关**，因此可以枚举这三个数值的 $j$，分别计算出中位数属于哪种类型 $j_0$，然后将结果转移到对应的 $dp_{i,j_0}$ 即可。~~肉眼可见的大常数就是这么来的。~~

$$
dp_{i,j_0}\leftarrow dp_{2i,j_1}+dp_{2i+1,j_3}+
\begin{cases}
0&(a_i<m\land j_2=0)\lor (a_i=m\land j_2=1)\lor (a_i>m\land j_2=2)\\
c_i&\text{otherwise.}
\end{cases}
$$

当结点的编号 $>\lfloor\frac N2\rfloor$ 时：因为**没有儿子**，所以自己的值就是中位数。同样枚举类型 $j$ 即可。

$$
dp_{i,j}=
\begin{cases}
0&(a_i<m\land j=0)\lor (a_i=m\land j=1)\lor (a_i>m\land j=2)\\
c_i&\text{otherwise.}
\end{cases}
$$

转移时注意要**从后往前**进行。时间复杂度 $O(N\cdot Q)$，可获得 $40\%$ 的分数。

**优化算法**，发现可以将这些 $m$ 都**离线下来排个序**，因为在 $m$ 增大的过程中，原来 $0$ 类的数都保持 $0$ 类不变，原来 $2$ 类的数可能变成 $1$ 类或 $0$ 类，原来 $1$ 类的数会变成 $0$ 类，所以只要在一个结点的数值的类型**发生变化时**，在该结点到根的**路径上重新 DP** 即可。

这样的时间复杂度是 $O(N\log N)$，可通过本题。4s 时间应该是用来放大常数做法过的。

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, Q, a[200005], cv = -1;
long long c[200005], dp[200005][3];
struct Query {
	int v, n;
	long long w;
	bool operator<(Query q) const {
		return n < q.n;
	}
} qs[200005];
struct Node {
	int v, n;
	bool operator<(Node q) const {
		if(v ^ q.v)
			return v < q.v;
		return n > q.n;
	}
} ns[200005];
long long min(long long x, long long y, long long z) {
	return min(x, min(y, z));
}
void cal(int u) {
	if(u > N / 2) {
		if(cv > a[u])
			dp[u][1] = dp[u][2] = c[u], dp[u][0] = 0;
		else if(cv == a[u])
			dp[u][0] = dp[u][2] = c[u], dp[u][1] = 0;
		else if(cv < a[u])
			dp[u][0] = dp[u][1] = c[u], dp[u][2] = 0;
		return;
	}
	dp[u][0] = dp[u][1] = dp[u][2] = 0x7fffffffffffffffll;
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j ++)
			for(int k = 0; k < 3; k ++) {
				long long ct = dp[u * 2][i] + dp[u * 2 + 1][k] + !(cv > a[u] && j == 0 || cv == a[u] && j == 1 || cv < a[u] && j == 2) * c[u];
				if(!i && !j || !j && !k || !k && !i)  // <
					dp[u][0] = min(dp[u][0], ct);
				else if(i == 2 && j == 2 || j == 2 && k == 2 || k == 2 && i == 2)  // >
					dp[u][2] = min(dp[u][2], ct);
				else  // =
					dp[u][1] = min(dp[u][1], ct);
			}
}
bool cmp(Query x, Query y) {
	return x.v < y.v;
}
int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++) {
		scanf("%d%lld", a + i, c + i);
		ns[i] = {a[i], i};
	}
	sort(ns + 1, ns + N + 1);
	scanf("%d", &Q);
	for(int i = 0; i < Q; i ++) {
		scanf("%d", &qs[i].v);
		qs[i].n = i;
	}
	sort(qs, qs + Q, cmp);
	for(int u = N; u; u --)
		cal(u);
	int pt /* <= */ = 1, cp /* < */ = 1;
	for(int i = 0; i < Q; i ++) {
		cv = qs[i].v;
		for(; cp <= N && ns[cp].v < cv; cp ++)
			for(int x = ns[cp].n; x; x >>= 1)
				cal(x);
		for(; pt <= N && ns[pt].v <= cv; pt ++)
			for(int x = ns[pt].n; x; x >>= 1)
				cal(x);
		qs[i].w = dp[1][1];
	}
	sort(qs, qs + Q);
	for(int i = 0; i < Q; i ++)
		printf("%lld\n", qs[i].w);
	return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

## P11673 [USACO25JAN] Median Heap G 题解

坑了比较久，来篇题解。

第一反应，放在第一题的位置应该是思维题，但推了推感觉没什么性质，而且时间限制不是默认的两秒而是四秒。结合样例感觉可能是和凸性的但不会证也不会利用它优化。

考虑最简单的动态规划，令 $dp_{i,j}$ 表示节点 $i$ 权值为 $j$ 的最小代价，转移比较繁琐但是不难想到，前后缀优化即可做到 $O(nV)$ 的复杂度，离散化后可以做到 $O(n^2)$。

但这样还有一个性质没有用到：树是完全二叉树，也就是说树高只有 $O(\log n)$，即对于节点 $i$，$dp_{i,j}$ 不同的连续段只有 $i$ 子树内的节点个数个，总的状态数只有 $O(n\log n)$，可以通过本题。细节比较多，放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;using P=pair<ll,ll>;
const int N=4e5+10;ll n,a[N],c[N],lsh[N],cnt,f1[N];vector<P> dp[N];
inline void dfs(ll x){
	if((x<<1)>n&&(x<<1|1)>n){
		dp[x].emplace_back(P{1,c[x]}),dp[x].emplace_back(P{a[x],0}),
		dp[x].emplace_back(P{a[x]+1,c[x]});return;
	}
	dfs(x<<1),dfs(x<<1|1);
	vector<ll> lsh;lsh.emplace_back(a[x]),lsh.emplace_back(a[x]+1);
	for(P x:dp[x<<1])lsh.emplace_back(x.first);
	for(P x:dp[x<<1|1])lsh.emplace_back(x.first);
	sort(lsh.begin(),lsh.end()),lsh.resize(unique(lsh.begin(),lsh.end())-lsh.begin());
	int n=lsh.size(),p=0,q=0;vector<ll> f1(n),f2(n),pre1(n),suf1(n),pre2(n),suf2(n);
	dp[x<<1].emplace_back(P{cnt+1,1e18}),dp[x<<1|1].emplace_back(P{cnt+1,1e18});
	for(int i=0;i<n;i++){
		while(p+1<(ll)dp[x<<1].size()&&dp[x<<1][p+1].first<=lsh[i])p++;
		f1[i]=dp[x<<1][p].second,pre1[i]=min((!i?(ll)1e18:pre1[i-1]),f1[i]);
	}
	for(int i=n-1;i>=0;i--)suf1[i]=min(((i==n-1)?(ll)1e18:suf1[i+1]),f1[i]);
	for(int i=0;i<n;i++){
		while(q+1<(ll)dp[x<<1|1].size()&&dp[x<<1|1][q+1].first<=lsh[i])q++;
		f2[i]=dp[x<<1|1][q].second,pre2[i]=min((!i?(ll)1e18:pre2[i-1]),f2[i]);
	}
	for(int i=n-1;i>=0;i--)suf2[i]=min(((i==n-1)?(ll)1e18:suf2[i+1]),f2[i]);
	for(int i=0;i<n;i++){
		ll now=min(pre1[i]+(lsh[i]!=a[x])*c[x]+suf2[i],pre2[i]+(lsh[i]!=a[x])*c[x]+suf1[i]);
		now=min(now,f1[i]+min((a[x]>lsh[i])*c[x]+suf2[i],(a[x]<lsh[i])*c[x]+pre2[i])),
		now=min(now,f2[i]+min((a[x]>lsh[i])*c[x]+suf1[i],(a[x]<lsh[i])*c[x]+pre1[i])),
		dp[x].emplace_back(P{lsh[i],now});
	}
}
int main(){
//	freopen(".in","r",stdin),freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>c[i],lsh[++cnt]=a[i],lsh[++cnt]=a[i]-1;
	lsh[++cnt]=1e18,sort(lsh+1,lsh+cnt+1),cnt=unique(lsh+1,lsh+cnt+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+cnt+1,a[i])-lsh;
	dfs(1);ll p=0;dp[1].emplace_back(P{cnt+1,1e18});
	for(int i=1;i<=cnt;i++){
		while(p+1<(int)dp[1].size()&&dp[1][p+1].first<=i)p++;
		f1[i]=dp[1][p].second;
	}
	ll Q;cin>>Q;
	while(Q--){ll x;cin>>x,x=lower_bound(lsh+1,lsh+cnt+1,x)-lsh,cout<<f1[x]<<"\n";}
	return 0;
}
```

---

## 作者：Register_int (赞：1)

考虑单组询问怎么做。对于 $x$，我们将 $a$ 中等于 $x$ 的设为 $1$，小于 $x$ 的设为 $0$，大于 $x$ 的设为 $2$，则可以 $dp_{u,0/1/2}$ 求让 $u$ 节点权值变为 $0/1/2$ 的最小代价。设当前目标为 $t$：

- 可以让这三个点中的至少两个为 $t$。
- 若 $t=1$，则这三个点可以为 $0,1,2$ 的排列。

转移是简单的，答案为 $dp_{1,1}$。

多组询问怎么办呢？将询问离线下来从小到大扫，则每个点的权值最多被修改两次，更新 dp 数组只要暴力跳父亲更新即可。由于树高为 $O(\log n)$，总复杂度为 $O(n\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, x[MAXN], a[MAXN], b[MAXN], c[MAXN], d[MAXN][3];

int t[MAXN << 2], tot; ll dp[MAXN][3], ans[MAXN];

vector<int> g[MAXN << 1], q[MAXN << 1];

inline 
void upd(int u, int k) {
	b[u] = a[u] < k ? 0 : a[u] > k ? 2 : 1;
	d[u][0] = d[u][1] = d[u][2] = c[u], d[u][b[u]] = 0;
}

inline 
void pushup(int u) {
	if (u * 2 > n) {
		for (int i = 0; i < 3; i++) dp[u][i] = d[u][i];
		return ;
	}
	for (int i = 0; i < 3; i++) {
		dp[u][i] = d[u][i] + min(dp[u << 1][i], dp[u << 1 | 1][i]);
		dp[u][i] = min(dp[u][i], dp[u << 1][i] + dp[u << 1 | 1][i]);
	}
	array<int, 3> a({ 0, 1, 2 });
	do {
		dp[u][1] = min(dp[u][1], d[u][a[0]] + dp[u << 1][a[1]] + dp[u << 1 | 1][a[2]]);
	} while (next_permutation(a.begin(), a.end()));
}

inline 
void modify(int u, int k) {
	upd(u, k);
	for (; u; u >>= 1) pushup(u);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &c[i]), t[++tot] = a[i];
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", &x[i]), t[++tot] = x[i];
	sort(t + 1, t + tot + 1), tot = unique(t + 1, t + tot + 1) - t - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + tot + 1, a[i]) - t;
	for (int i = 1; i <= m; i++) x[i] = lower_bound(t + 1, t + tot + 1, x[i]) - t;
	for (int i = n; i; i--) upd(i, 0), pushup(i);
	for (int i = 1; i <= n; i++) g[a[i]].emplace_back(i);
	for (int i = 1; i <= m; i++) q[x[i]].emplace_back(i);
	for (int i = 1; i <= tot; i++) {
		for (int u : g[i - 1]) modify(u, i);
		for (int u : g[i]) modify(u, i);
		for (int j : q[i]) ans[j] = dp[1][1];
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}
```

---

## 作者：Wei_Han (赞：0)

考虑一个暴力 dp，设 $f_{u,j}$ 表示以 $u$ 为根的子树，$u$ 的数交换过后是 $j$ 的最小代价，转移是 $O(nV^2)$ 的。

发现上面的状态其实是冗余的，对于要求的数 $m$，其实只把所有数分为了三类 $<m$,$=m$,$>m$，因此，考虑以此重新设计状态优化，即 $f_{u,0/1/2}$ 表示以 $u$ 为根的子树，$u$ 节点上的数 $<m$，$=m$，$>m$ 枚举转移即可，单次查询复杂度 $O(n)$，总复杂度 $O(nq)$。

进一步地考虑优化，发现所有数最多只会有两次状态变换，换句话讲，假如每有一个点初值修改我们就跑一遍 dp，修改操作只会有 $O(n)$ 个，而本题给定了是完全二叉树，因此树高只有 $O(\log n)$，考虑暴力修改，每次更新一个点初值，然后再更新其父亲，逐个向上，单次修改复杂度 $O(\log n)$，总复杂度 $O(q+n\log n)$。

具体实现可以将询问离线，排序后指针扫描逐个加点。

```cpp
const ll N=1e6+5,M=2e4+5;
ll n,q,fa[N],f[N][3],b[N],c[N],ans[N],g[N][3],vis[N];
struct node{ll i,a,c;}a[N];
vector<pii> A;vector<ll> G[N];
inline ll med(ll x,ll y,ll z){ll mx=max({x,y,z});if(x==mx) return max(y,z);if(y==mx) return max(x,z);return max(x,y);}
inline void dfs(ll x,ll fa)
{
    f[x][2]=0,f[x][0]=f[x][1]=c[x];ll ls=0,rs=0;vis[x]=2;
    for(ll y:G[x]) if(y!=fa) dfs(y,x),ls?rs=y:ls=y;
    if(!ls||!rs) return;g[x][0]=g[x][1]=g[x][2]=inf;
    fo(0,i,2) fo(0,j,2) fo(0,k,2) ckmn(g[x][med(i,j,k)],f[ls][i]+f[x][j]+f[rs][k]);
    fo(0,i,2) f[x][i]=g[x][i];
}
inline void upd(ll x,ll k)
{
    if(!x) return;
    if(vis[x]==0) f[x][0]=0,f[x][1]=f[x][2]=c[x];
    if(vis[x]==1) f[x][1]=0,f[x][0]=f[x][2]=c[x];
    if(vis[x]==2) f[x][2]=0,f[x][0]=f[x][1]=c[x];
    ll ls=0,rs=0;for(ll y:G[x]) if(y!=fa[x]) ls?rs=y:ls=y;
    if(!ls||!rs) return upd(fa[x],2);g[x][0]=g[x][1]=g[x][2]=inf;
    fo(0,i,2) fo(0,j,2) fo(0,k,2) ckmn(g[x][med(i,j,k)],f[ls][i]+f[x][j]+f[rs][k]);
    fo(0,i,2) f[x][i]=g[x][i];
    upd(fa[x],2);
}
signed main(){
    // freopen("median.in","r",stdin);
    // freopen("median.out","w",stdout);
    read(n,q);fo(1,i,n) (i!=1?G[i/2].pb(i),G[i].pb(i/2):void()),fa[i]=i/2,read(a[i].a,a[i].c),c[i]=a[i].c,b[i]=a[i].c,a[i].i=i;
    sort(a+1,a+1+n,[&](node i,node j){return i.a<j.a;});ll x,y;
    fo(1,i,q) read(x),A.pb(mk(x,i));sort(all(A));
    ll i1=1,i2=1;dfs(1,0);
    for(auto [x,id]:A)
    {
        while(i2<=n&&a[i2].a<x) ++i2;
        while(i1<=n&&a[i1].a<x) vis[a[i1].i]=0,upd(a[i1].i,0),++i1;
        while(i2<=n&&a[i2].a==x) vis[a[i1].i]=1,upd(a[i2].i,1),++i2;
        // wr(x),pp,wr(id),pp,wr(i1),pp,wr(i2),pr;
        ans[id]=f[1][1];
    }
    fo(1,i,q) wr(ans[i]),pr;
    return 0;
}

```

---

## 作者：Cipher0128 (赞：0)

值域很大，且只询问一些特定的值，这启发我们只考虑数的相对大小。

如果只有一个 $m$，我们考虑怎么 dp。我们需要知道每个字数凑出每个数的代价，但其实本质上只有三类：小于、等于、大于 $m$。那么我们设 $f_{x,0/1/2}$ 表示在 $x$ 的子树中凑出的数小于、等于、大于 $m$ 的最小代价，答案是 $f_{1,1}$。思考可以得出转移方程：$f_{x,p}=\min_{i,j,k} \{f_{lc,i}+f_{rc,j}+c_{x,k}\}$。其中 $p$ 是 $i,j,k$ 的中位数，$c_{x,k}$ 是把 $x$ 初始值修改至与 $m$ 满足 $k$ 的关系的代价。

如果 $m$ 很多，会发现如果将 $m$ 排序，每次相对于上次的 $c$ 只有一部分会改变，均摊每个 $c_x$ 只会改变两次：从小于到等于到大于。而每改变一个 $c_x$ 只会影响一条链上 $\log$ 个点，所以总复杂度 $O(n\log n)$。

注意处理值相等的情况。

代码如下：
```cpp
#include<bits/stdc++.h>
#define rd read()
#define ll long long
#define for_(a,b,c) for(int a=b;a<=c;++a)
#define lc (x<<1)
#define rc (x<<1|1)
#define Cmin(a,b) (a=min(a,b))
using namespace std;
int n,m;
const int N=2e5+10;
ll a[N],c[N],f[N][3],ans[N],cur,st[N],tp,b[N],id[N];
struct QRY{
	ll val,id;
	bool operator<(QRY o)const{
		return val<o.val;
	}
}Q[N],e[N];
int med(int a,int b,int c){
	return a^b^c^min(a,min(b,c))^max(a,max(b,c));
}
int w(int x,int i){
	if(i==0)return (a[x]>=Q[cur].val)*c[x];
	if(i==1)return (a[x]!=Q[cur].val)*c[x];
	if(i==2)return (a[x]<=Q[cur].val)*c[x];
}
void dfs(int x){
	if(x>n)return;
	dfs(lc);dfs(rc);
	f[x][0]=f[x][1]=f[x][2]=1e18;
	if(lc>n)for_(i,0,2)f[x][i]=w(x,i);
	else for_(i,0,2)for_(j,0,2)for_(k,0,2)Cmin(f[x][med(i,j,k)],f[lc][j]+f[rc][k]+w(x,i));
}
void up(int x){
	if(!x)return;
	f[x][0]=f[x][1]=f[x][2]=1e18;
	if(lc>n)for_(i,0,2)f[x][i]=w(x,i);
	else for_(i,0,2)for_(j,0,2)for_(k,0,2)Cmin(f[x][med(i,j,k)],f[lc][j]+f[rc][k]+w(x,i));
	up(x>>1);
}
inline ll read(){ll d=0,f=0;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}while(ch<='9'&&ch>='0'){d=(d<<1)+(d<<3)+ch-'0';ch=getchar();}return f?-d:d;}
int main(){
	n=rd;
	for_(i,1,n)a[i]=rd,c[i]=rd,e[i]={a[i],i};
	sort(e+1,e+1+n);
	for_(i,1,n)b[i]=e[i].val,id[i]=e[i].id;
	m=rd;
	for_(i,1,m)Q[i]={rd,i};
	sort(Q+1,Q+1+m);
	memset(f,0x3f,sizeof(f));
	cur=1;dfs(1);ans[Q[1].id]=f[1][1];
	for_(i,2,m){
		cur=i;
		if(Q[i].val==Q[i-1].val){
			ans[Q[i].id]=f[1][1];
			continue;
		}
		int L=lower_bound(b+1,b+1+n,Q[cur-1].val)-b,R=upper_bound(b+1,b+1+n,Q[cur].val)-b-1;
		if(e[L].val<=Q[i].val)for_(j,L,R)up(id[j]);
		ans[Q[i].id]=f[1][1];
	}
	for_(i,1,m)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

首先考虑解决单个询问。设 $f_{u,0/1/2}$ 代表节点 $u$ 的子树的中位数是 $<,=,>m$ 的最小代价。容易 $\mathcal{O}(n)$ 转移。

考虑对询问的 $m$ 排序，那么过程中一些 $2$ 会变成 $1$，一些 $1$ 会变成 $0$，考虑这些变化。发现如果变的是节点 $u$ 的值，只会对 $fa(u),fa(fa(u)),\cdots ,1$ 有 $f$ 的更改，因为树高 $\log$，可以暴力修改。

最多修改 $\mathcal{O}(n)$ 次，总复杂度 $\mathcal{O}(n\log n)$，大常数。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

int n,Q,a[N],c[N],ty[N];
ll f[N][3];

struct node {
	int x,id;
} p[N];

bool cmp(node x,node y){
	return x.x<y.x;
}

int med(int x,int y,int z){
	if (x>y) swap(x,y);
	if (y>z) swap(y,z);
	if (x>y) swap(x,y);
	return y;
}

void chkm(ll &x,ll y){
	if (x>y) x=y;
}

void upd(int u){
	if (u*2>n){
		for (int i=0; i<3; i++){
			if (i==ty[u]) f[u][i]=0;
			else f[u][i]=c[u];
		}
		return;
	}
	for (int i=0; i<3; i++) f[u][i]=1e18;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			chkm(f[u][med(i,j,ty[u])],f[u*2][i]+f[u*2+1][j]);
			for (int k=0; k<3; k++){
				ll ad=c[u];
				if (ty[u]==k) ad=0;
				chkm(f[u][med(i,j,k)],f[u*2][i]+f[u*2+1][j]+ad);
			}
		}
	}
}

void dfs(int u){
	if (u>n) return;
	dfs(u*2);
	dfs(u*2+1);
	upd(u);
}

struct quy {
	int m,id;
} q[N];

bool cmq(quy u,quy v){
	return u.m<v.m; 
}

void Upd(int u){
	int x=u;
	while (x){
		upd(x);
		x/=2;
	}
}

ll ans[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++){
		cin>>a[i]>>c[i];
		p[i]={a[i],i};
		ty[i]=2;
	}
	sort(p+1,p+1+n,cmp);
	memset(f,0x3f,sizeof f);
	dfs(1);
	cin>>Q;
	for (int i=1; i<=Q; i++){
		cin>>q[i].m;
		q[i].id=i;
	}
	sort(q+1,q+1+Q,cmq);
	int l=0,r=0;
	for (int i=1; i<=Q; i++){
		while (r+1<=n && p[r+1].x<=q[i].m){
			ty[p[r+1].id]=1;
			Upd(p[r+1].id);
			r++;
		}
		while (l+1<=n && p[l+1].x<q[i].m){
			ty[p[l+1].id]=0;
			Upd(p[l+1].id);
			l++;
		}
		ans[q[i].id]=f[1][1];
	}
	for (int i=1; i<=Q; i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Erine (赞：0)

简单题。感觉比 Cu T1 简单。有一种 CNOI 特色风味的感觉。改成任意二叉树就更 CNOI 了（）

考虑单次询问，记 $<x$ 为 $0$，$=x$ 为 $1$，$\gt x$ 为 $2$。可以设计状态 $f_{u,0/1/2}$ 表示让 $u$ 上算出来的中位数是 $0/1/2$ 的最小代价。转移显然。直接做到单次 $27n$。

多组询问先对 $x$ 排序，然后考虑每个点 $0/1/2$ 会发生变化，并且每个点至多变化两次。所以等价于修点权，计算根的 dp 值。

想直接上一个动态 dp 发现不用。因为告诉你树高 $\Theta(\log n)$，所以从被修改点暴力往上修改祖先的 dp 值就行了。

```cpp
void dfs(int u) {
	f[u][0] = f[u][1] = f[u][2] = inf;
	int g[3] = {w[u] == 0 ? 0 : c[u], w[u] == 1 ? 0 : c[u], w[u] == 2 ? 0 : c[u]};
	if ((u << 1 | 1) > n) {
		rep(i, 0, 2) f[u][i] = g[i];
		return;
	}
	dfs(ls), dfs(rs);
	rep(l, 0, 2) rep(r, 0, 2) rep(x, 0, 2) {
		int c[3] = {l, r, x};
		sort(c, c + 3);
		f[u][c[1]] = min(f[u][c[1]], f[ls][l] + f[rs][r] + g[x]);		
	}
}

void modify(int u) {
	if (!u) return;
	f[u][0] = f[u][1] = f[u][2] = inf;
	int g[3] = {w[u] == 0 ? 0 : c[u], w[u] == 1 ? 0 : c[u], w[u] == 2 ? 0 : c[u]};
	if ((u << 1 | 1) > n) {
		rep(i, 0, 2) f[u][i] = g[i];
		modify(u >> 1);
		return;
	}
	rep(l, 0, 2) rep(r, 0, 2) rep(x, 0, 2) {
		int c[3] = {l, r, x};
		sort(c, c + 3);
		f[u][c[1]] = min(f[u][c[1]], f[ls][l] + f[rs][r] + g[x]);		
	}
	modify(u >> 1);
}
```

---

## 作者：Departure_ (赞：0)

一个很粗暴的做法。注意到一个点的取值只能是在其子树内出现过的值，考虑设 $f(u,i)$ 为点 $u$ 的取值为 $i$ 时，$u$ 子树的最小花费。转移是显然的，设 $u$ 的两个儿子 $lc,rc$，$u$ 的取值只有三种情况，若最后 $u$ 的值在其中一点取到，那么另外两点的取值一大一小，预处理前后缀 $\min$ 即可。即
```cpp
for(int i=0;i<(int)ls[u].size();i++){
    int lp=fnd(ls[lc],ls[u][i]);
    int rp=fnd(ls[rc],ls[u][i]);
    int res=inf;
    tomin(res,f[u][i]+min(pre[lc][lp]+suf[rc][rp],suf[lc][lp]+pre[rc][rp]));
    tomin(res,f[lc][lp]+min(pre[u][i]+suf[rc][rp],suf[u][i]+pre[rc][rp]));
    tomin(res,f[rc][rp]+min(pre[u][i]+suf[lc][lp],suf[u][i]+pre[lc][lp]));
    f[u][i]=res;
}
```
由此题二叉树的性质，空间复杂度 $\Theta(n\log n)$，有一些极限；时间复杂度 $\Theta(n\log^2 n)$。
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<numeric>
#include<bitset>
using namespace std;namespace _{static void main();}signed main(){
    #ifdef LGH
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin.tie(0)->sync_with_stdio(0);
    // signed cse;cin>>cse>>ws;while(cse--)
    _::main();
}namespace _{
#define ll long long
#define pb push_back
#define ve vector
#define fi first
#define se second
#define pii pair<int,int>
#define all(x) (x).begin(),(x).end()
#ifndef BUG
#define bug(x) {}
#define bua(a,l,r) {}
#else
#define bug(x) cout<<":"<<__LINE__<<": ";x
#define bua(a,l,r) cout<<#a": ";for(int i=(l),j=(r);i<=j;i++)cout<<a[i]<<' ';cout<<endl;
#endif
constexpr static void tomin(auto&x,auto&&y){if(y<x)x=y;}
constexpr static void tomax(auto&x,auto&&y){if(y>x)x=y;}

#define int ll
constexpr int maxn=2e5+10,inf=0x3f3f3f3f3f3f3f3fll;

int n,Q,a[maxn],c[maxn];
ve<int> ls[maxn],f[maxn],pre[maxn],suf[maxn];
#define fnd(x,y) (upper_bound(all(x),y)-(x).begin()-1)

void dfs(int u){
    if(u>n)return;
    #define lc (u<<1)
    #define rc (u<<1|1)
    dfs(lc),dfs(rc);
    f[u]=ve<int>(ls[u].size(),c[u]);
    f[u][fnd(ls[u],a[u])]=0;
    pre[u]=suf[u]=f[u];
    for(int i=1;i<(int)pre[u].size();i++)tomin(pre[u][i],pre[u][i-1]);
    for(int i=suf[u].size()-2;i>=0;i--)tomin(suf[u][i],suf[u][i+1]);
    if(lc>n)return;
    for(int i=0;i<(int)ls[u].size();i++){
        int lp=fnd(ls[lc],ls[u][i]);
        int rp=fnd(ls[rc],ls[u][i]);
        int res=inf;
        tomin(res,f[u][i]+min(pre[lc][lp]+suf[rc][rp],suf[lc][lp]+pre[rc][rp]));
        tomin(res,f[lc][lp]+min(pre[u][i]+suf[rc][rp],suf[u][i]+pre[rc][rp]));
        tomin(res,f[rc][rp]+min(pre[u][i]+suf[lc][lp],suf[u][i]+pre[lc][lp]));
        f[u][i]=res;
    }
    pre[u]=suf[u]=f[u];
    for(int i=1;i<(int)pre[u].size();i++)tomin(pre[u][i],pre[u][i-1]);
    for(int i=suf[u].size()-2;i>=0;i--)tomin(suf[u][i],suf[u][i+1]);
}

void main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>c[i];
        for(int x=i;x;x>>=1){
            ls[x].pb(a[i]);
            ls[x].pb(a[i]+1);
        }
    }
    for(int i=1;i<=n;i++){
        ls[i].pb(0);
        sort(all(ls[i]));
        ls[i].resize(unique(all(ls[i]))-ls[i].begin());
    }
    dfs(1);
    for(cin>>Q;Q--;){
        int x;cin>>x;
        cout<<f[1][fnd(ls[1],x)]<<'\n';
    }
}
}
```

---

