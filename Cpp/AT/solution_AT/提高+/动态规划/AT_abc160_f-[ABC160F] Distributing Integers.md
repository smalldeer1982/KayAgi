# [ABC160F] Distributing Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc160/tasks/abc160_f

$ 1 $ から $ N $ までの番号が付けられた $ N $ 個の頂点を持つ木があります。この木の $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。  
 $ k=1,...,N $ に対して、以下の問題を解いてください。

- 以下の手順に従って,木の各頂点に整数を書くことを考える。
  - まず、頂点 $ k $ に $ 1 $ を書く。
  - $ 2,...,N $ を順番に頂点に書く。書き込む頂点は、次のように決める。
      - まだ整数が書かれていない頂点であって、整数が書かれた頂点に隣接しているものを選ぶ。このような頂点が複数存在する場合は、その中からランダムに選ぶ。
- 整数の書き方として考えられるものの数を $ 10^9+7 $ で割ったあまりを求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- 与えられるグラフは木である

### Sample Explanation 1

この入力中のグラフは以下のようなものです。 !\[図\](https://img.atcoder.jp/ghi/1c88b0eb716ba399b1c5d6565ab62337.png) $ k=1 $ に対する問題において、以下のように $ 2 $ 通りの整数の書き方が考えられます。 - 頂点 $ 1,2,3 $ に、それぞれ $ 1,2,3 $ を書く - 頂点 $ 1,2,3 $ に、それぞれ $ 1,3,2 $ を書く

### Sample Explanation 2

この入力中のグラフは以下のようなものです。 !\[図\](https://img.atcoder.jp/ghi/c47c7798f88e7bfec30fbd664dc9ad50.png)

### Sample Explanation 3

この入力中のグラフは以下のようなものです。 !\[図\](https://img.atcoder.jp/ghi/e9c09403f8d96ae4e679a226993defa6.png)

### Sample Explanation 4

この入力中のグラフは以下のようなものです。 !\[図\](https://img.atcoder.jp/ghi/a85459a03d436560bfe2e911d8cec4e6.png)

## 样例 #1

### 输入

```
3
1 2
1 3```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
1
1```

## 样例 #3

### 输入

```
5
1 2
2 3
3 4
3 5```

### 输出

```
2
8
12
3
3```

## 样例 #4

### 输入

```
8
1 2
2 3
3 4
3 5
3 6
6 7
6 8```

### 输出

```
40
280
840
120
120
504
72
72```

# 题解

## 作者：ix35 (赞：19)

第一次 ABC 打到 Rank 3（21min），写篇题解纪念一下。

考虑计算询问中第 $i$ 项的答案，我们容易发现以 $i$ 为根时，题目要求的填数方案就是：一个点的数必须在父亲之后填。

所以这就是一个拓扑排序计数问题。

对于树上拓扑排序计数，有结论 $\dfrac{n!}{\prod siz_u}$，这是因为每个点 $u$ 的子树内部排列都只有 $\dfrac{1}{siz_u}$ 种是合法的（即 $u$ 在最前面的那一些）。

$n!$ 是固定的不用管，我们只需要求出以每个点为根的 $\prod {siz_u}$ 即可，这是个经典的换根 DP，设这个值为 $dp_i$。

首先以 $1$ 为根做第一次扫描，算 $siz$，并且 $dp_1=\prod siz_u$。

接下来做二次扫描，根据转移方程：

$$dp_x=dp_{fa}\times \dfrac{(n-siz_x)}{siz_x}$$

其实就是考虑了 $x$ 的子树和父亲的子树。

从上到下做 DFS 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010,P=1e9+7;
int n,x,y,eg,hd[MAXN],ver[2*MAXN],nx[2*MAXN],siz[MAXN],f[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
int qpow (int a,int b) {
	int res=1;
	while (b) {
		if (b&1) {res=(1ll*res*a)%P;}
		a=(1ll*a*a)%P,b>>=1; 
	}
	return res;
}
void dfs1 (int x,int fa) {
	siz[x]=1;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs1(ver[i],x);
		siz[x]+=siz[ver[i]];
	}
	f[1]=(1ll*f[1]*siz[x])%P;
	return;
}
void dfs2 (int x,int fa) {
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		f[ver[i]]=(1ll*f[x]*((1ll*(n-siz[ver[i]])*qpow(siz[ver[i]],P-2))%P))%P; 
		dfs2(ver[i],x);
	}
	return;
}
int main () {
	scanf("%d",&n);
	f[1]=1;
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
	}
	dfs1(1,0);
	dfs2(1,0);
	int tmp=1;
	for (int i=1;i<=n;i++) {tmp=(1ll*tmp*i)%P;}
	for (int i=1;i<=n;i++) {printf("%d\n",(1ll*tmp*qpow(f[i],P-2))%P);}
	return 0;
}
```


---

## 作者：Guess00 (赞：7)

本题做法:换根DP

前置知识:逆元

不妨设$k$号点为这颗树的根。

令$size_v$为$v$号点的孩子个数，$dp_v$为以$v$为根的子树的填写方案数。

我们可以~~从官方题解~~发现$dp_v=(size_v-1)!\prod\limits_{u\in son_v}\dfrac{dp_u}{size_u!}$。

设$x_v=\prod\limits_{u\in son_v}\dfrac{dp_u}{size_u!}$，于是$dp_v=(size_v-1)!x_v$

于是可以发现$x_v=\prod\limits_{u\in son_v}\dfrac{dp_u}{size_u!}=\prod\limits_{u\in son_v}\dfrac{(size_u-1)!x_u}{size_u!}=\prod\limits_{u\in son_v}\dfrac{x_u}{size_u}=\dfrac{1}{\prod\limits_{u\in tree_v} size_u}$

于是$dp_k=(size_k-1)!x_k=\dfrac{(n-1)!}{\prod\limits_{u\in [1,n]\&\&u!=k}size_u}=\dfrac{n!}{\prod\limits_{u\in [1,n]}size_u}$

由于本题$n!$是固定的，那么只需求出$\prod\limits_{u\in [1,n]}size_u$。

令$f_v=\prod\limits_{u\in tree_v}size_u$。

于是就可以用换根DP求出$f$。

第一次扫描求出以$1$为根的$size$和$f_1$(所有$size$的积)。

第二次扫描换根求$f$。($f_v=\dfrac{f_{fa_v}\times(n-size_v)}{size_v}$)

最后按顺序输出$\dfrac{n!}{f_k}$即可。

$\mathbb{CODE:}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 200005
#define mod 1000000007
using std::vector;
int n,i,x,f[MAXN],size[MAXN];
vector<int> G[MAXN];
bool vis[MAXN];
inline void read(int &x)  //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)   //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a,int n,int p)  //快速幂(求逆元用的) 
{
	int Ret(1);
	while (n)
	{
		if (n&1)
			(Ret*=a)%=p;
		(a*=a)%=p,n>>=1;
	}
	return Ret;
}
inline void dfs(int u)
{
	vis[u]=true,size[u]=1;
	for (int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if (vis[v])
			continue;
		dfs(v);
		size[u]+=size[v];   //求size 
	} 
	(f[1]*=size[u])%=mod;   //求f1 
}
inline void dfs2(int u)
{
	vis[u]=true;
	for (int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if (vis[v])
			continue;
		f[v]=f[u]*((n-size[v])*ksm(size[v],mod-2,mod)%mod)%mod;  //计算f 
		dfs2(v);
	}
}
signed main(void)
{
	read(n);
	for (i=1;i<n;i++)
	{
		int u,v;
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	f[1]=1;
	dfs(1);
	memset(vis,false,sizeof(vis));
	dfs2(1);
	for (i=x=1;i<=n;i++)  //n!
		(x*=i)%=mod;
	for (i=1;i<=n;i++)
		print((x*ksm(f[i],mod-2,mod))%mod),putchar('\n');
	return 0;
}
```

---

## 作者：August_Light (赞：6)

# [ABC160F] Distributing Integers 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc160_f)

## 题意简述

给定一棵 $n$ 个点的无根树，每次操作可以删除一个度数**不超过** $1$ 的结点。对于 $1 \le i \le n$，求 $n$ 次操作将整棵树删空，且 $i$ 是最后一个被删的方案数。答案对 $10^9+7$ 取模。

两种方案不同当且仅当至少一次操作删除的结点不同。

$n \le 2 \times 10^5$。

## 写在前面

这个题和 [NOIP 冲刺计划【2023 / 后期】](https://class.luogu.com.cn/course/yugu23nob)第三场比赛 [T1 虚无悲叹](https://www.luogu.com.cn/problem/T378408) 重了。

## 解法

树上 DP。

对于每个 $i$，钦定 $i$ 为根。

设 $siz_u$ 为 $u$ 的子树大小。

设 $f_u$ 为删去 $u$ 的子树，且 $u$ 为最后一个被删的方案数。

采取归并的思想，有以下状态转移：

```cpp
void dfs1(int u, int fa) {
    siz[u] = 0;
    f[u] = 1;
    for (auto v : G[u]) {
        if (v == fa)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        f[u] *= f[v] * C(siz[u], siz[v]);
        // 这里为了看得更清晰，所以没有写取模。
    }
    siz[u]++;
}
```

时间复杂度 $O(n^2)$。

使用换根 DP 优化。设 $ans_u$ 为以 $u$ 为根时的答案。

通过第一遍 DFS，求出根为 $1$ 时的 $f$ 数组。

换根 DP 转移：

$$ans_u = f_u \times \left(\dfrac {ans_{fa}} {f_u \times \binom {n-1} {siz_u}} \times \binom {n-1} {siz_u-1}\right)$$

其含义为：先从 fa 的答案中把 u 的子树（红色）去除，算出以 fa 为根的蓝色树的方案数，再用一样的方法合并到 u 的答案上。

![](https://cdn.luogu.com.cn/upload/image_hosting/vp0mx9sq.png)

化简得：

$$ans_u = ans_{fa} \times \dfrac {siz_u} {n - siz_u}$$

特殊地，$ans_{root} = f_{root}$。

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 5;
const ll MOD = 1e9 + 7;

int n;
vector<int> G[MAXN];

ll fac[MAXN], invfac[MAXN], inv[MAXN];
void init() {
    fac[0] = 1; fac[1] = 1;
    invfac[0] = 1; invfac[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invfac[i] = invfac[i-1] * inv[i] % MOD;
    }
}
ll C(ll n, ll m) {
    return fac[n] * invfac[m] % MOD * invfac[n-m] % MOD;
}

int siz[MAXN];
ll f[MAXN], ans[MAXN];
void dfs1(int u, int fa) {
    f[u] = 1;
    for (auto v : G[u]) {
        if (v == fa)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        (f[u] *= f[v] * C(siz[u], siz[v]) % MOD) %= MOD;
    }
    siz[u]++;
}
void dfs2(int u, int fa) {
    if (fa == 0)
        ans[u] = f[u];
    else
        ans[u] = ans[fa] * siz[u] % MOD * inv[n - siz[u]] % MOD;
    for (auto v : G[u]) {
        if (v == fa)
            continue;
        dfs2(v, u);
    }
}

int main() {
    cin >> n;
    init();
    for (int i = 1; i <= n-1; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int u = 1; u <= n; u++)
        cout << ans[u] << '\n';
    return 0;
}
```


---

## 作者：ykzzldz (赞：4)

先考虑以一个固定的点为根时的答案，这里先给出结论，答案为 $\frac{n!}{\prod size_i}$，其中 $size_i$ 表示 $i$ 结点子树的大小。感性理解一下这个结论，在每个子树中，根结点一定要先填数，于是在这棵子树中合法的方案占方案数的 $\frac{1}{size_i}$，合法方案数占总方案数 $n!$ 的  $\frac{1}{\prod size_i}$。

问题转化为求出每个点为根时的 $\prod size_i$，这里我们可以使用换根 dp 求解。

令 $f_i$ 表示 $i$ 子树内所有结点的 $size$ 之积，即：$f_i=\prod_{j\in tree_i} size_j$。

第一次 dfs 求出以 $1$ 结点为根时，每个结点的 $f_i$。

第二次 dfs，有转移方程 $f_i=f_{fa}\times\frac{n-size_i}{size_i}$。根从 $fa$ 变为 $i$，只有 $size_{fa}$ 和 $size_i$ 会改变，从上往下 dp 即可。下面给出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=1e9+7;
int poww(int a,int b){
	int ans=1;
	while(b){
		if(b%2)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,x=1,f[N],siz[N];
vector<int>a[N];
void dfs1(int u,int fa){
	siz[u]=1;
	for(int v:a[u]){
		if(v==fa)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
	f[1]=(f[1]*siz[u])%mod;
}
void dfs2(int u,int fa){
	for(int v:a[u]){
		if(v==fa)continue;
		f[v]=f[u]*(n-siz[v])%mod*poww(siz[v],mod-2)%mod;
		dfs2(v,u);
	}
}
signed main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		x=(x*i)%mod;
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	f[1]=1;
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		cout<<x*poww(f[i],mod-2)%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：hyxgg (赞：4)

[题目](https://www.luogu.com.cn/problem/AT_abc160_f)
## 思路
### 主体思路

先用树上 DP 求出从 $1$ 开始的答案，再转移到其他点上。

### DP 部分

#### 状态
设 $dp_i$ 表示以 $i$ 为根的子树中的方案数，$gs_i$ 表示子树中的点数。

#### 转移
设当前遍历到的根为 $i$，子节点为 $j$，之前遍历过的子树中的节点总数为 $qd$，则有
$$dp_i=dp_i\times C_{qd+gs_j}^{gs_j} \times dp_j$$

即子树内的部分乘上不同子树之间的顺序关系。
### 换根部分

设 $ans_i$ 为从 $i$ 开始的答案。

设 $j$ 为 $i$ 的子节点，已知 $ans_i$，需求 $ans_j$。

很显然 $ans_j$ 就是 $dp_j$ 乘**其他部分**的方案数再乘他们之间的顺序关系。

#### 其他部分

**其他部分**也就是，以 $i$ 为根，除了以 $j$ 为根的子树之外的点。

那 $ans_i$ 排除以 $j$ 为根的子树的影响后的值就是**其他部分**的方案数。

也就是 $\frac{ans_i}{dp_j\times C_{n-1}^{gs_j}}$。

#### 带入前面
得：
$$ans_j=dp_j\times \frac{ans_i}{dp_j\times C_{n-1}^{gs_j}} \times C_{n-1}^{gs_j-1}$$

## 代码
注意取模，别像我第一次做时一样犯傻。

有问题评论区见。

上代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=1e9+7;
struct edge{
	ll q,z,xg;
}ed[400005];
ll n,dd[200005],db=1,dp[200005],js[200005],jc[200005],gs[200005],ans[200005];
void fjq(ll q,ll z){
	ed[db].q=q,ed[db].z=z,ed[db].xg=dd[q],dd[q]=db++;
}
ll ny(ll x){
	ll dc=x,m=mod-2,s=1;
	while(m){
		if(m&1)s*=dc,s%=mod;
		dc=dc*dc%mod;
		m>>=1;
	}
	return s;
}
ll C(ll a,ll b){
	return jc[a]*ny(jc[a-b])%mod*ny(jc[b])%mod;
}
void dfs(ll root,ll fa){
	dp[root]=1;
	for(ll i=dd[root];i;i=ed[i].xg){
		ll to=ed[i].z;
		if(to==fa)continue;
		js[root]++;
		dfs(to,root);
		dp[root]*=dp[to]*C(gs[root]+gs[to],gs[to])%mod;
		dp[root]%=mod;
		gs[root]+=gs[to];
	}
	gs[root]++;
}
void dfs2(ll root,ll fa){
	if(root!=1){
		ans[root]=dp[root]*ans[fa]%mod*ny(dp[root])%mod*ny(C(n-1,gs[root]))%mod*C(n-1,gs[root]-1)%mod;
	}
	for(ll i=dd[root];i;i=ed[i].xg){
		ll to=ed[i].z;
		if(to==fa)continue;
		dfs2(to,root);
	}
}
int main(){
	scanf("%lld",&n);
	jc[0]=1;
	for(ll i=1;i<=n;i++){
		jc[i]=jc[i-1]*i;
		jc[i]%=mod;
	}
	ll aa,bb;
	for(ll i=1;i<n;i++){
		scanf("%lld%lld",&aa,&bb);
		fjq(aa,bb),fjq(bb,aa);
	}
	dfs(1,0);
	ans[1]=dp[1];
	dfs2(1,0);
	for(ll i=1;i<=n;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
} 
```

---

## 作者：feecle6418 (赞：4)

大概是套路换根 dp 题？可我还是做的那么慢。

首先求出在每个点的子树内的方案数。合并两棵子树相当于合并两个有序序列，根据插板法，有 

$$\large f_x\times f_y\times \mathrm{C}_{size_x+size_y-1}^{size_x-1}$$

种方法，`size` 为当前子树大小。

换根的时候，先去掉 $y$ 这个儿子的贡献（乘以上面那一坨的逆元），然后把 $x$ 当作一颗大小为 $n-size_y$ 的子树，用上面的式子算即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod=1000000007;
int n,jc[200005]={1},ny[200005]={1};
vector<int> g[200005];
ll f[200005],f2[100005],size[200005];
int Power(int x,long long y,int mod) {
	int ret=1;
	while(y) {
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
int C(int x,int y){
	return 1ll*jc[x]*ny[y]%mod*ny[x-y]%mod;
}
void DFS(int x,int fa) {
	f[x]=size[x]=1;
	for(int y:g[x]) {
		if(y==fa)continue;
		DFS(y,x);
		f[x]=1ll*f[x]*f[y]%mod*C(size[x]+size[y]-1,size[x]-1)%mod;
		size[x]+=size[y];
	}
}
void HuanGen(int x,int fa){
	for(int y:g[x]){
		if(y==fa)continue;
		int tmp=1ll*f2[x]*Power(C(n-1,n-size[y]-1),mod-2,mod)%mod*Power(f[y],mod-2,mod)%mod;
		f2[y]=1ll*f[y]*tmp%mod*C(n-1,size[y]-1)%mod;
		HuanGen(y,x);
	}
}
int main() {
	cin>>n;
	for(int i=1; i<n; i++) {
		int x,y;
		cin>>x>>y;
		g[x].push_back(y),g[y].push_back(x);
	}
	for(int i=1; i<=n; i++)jc[i]=1ll*jc[i-1]*i%mod;
	ny[n]=Power(jc[n],mod-2,mod);
	for(int i=n-1; i>=1; i--)ny[i]=1ll*(i+1)*ny[i+1]%mod;
	memset(size,0,sizeof(size));
	DFS(1,0);
	f2[1]=f[1];
	HuanGen(1,0);
	for(int i=1;i<=n;i++)cout<<f2[i]<<endl;
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc160_f)。

## Solution

要求对于每个点，求出以之为根时的方案数，$n \le 2\times 10^5$，考虑换根 $\operatorname{dp}$。

若以点 $rt$ 为根，则操作要求变为每个点填数前其父亲必须已经填写，即在每个子树中，子树的根节点是最先填的。记 $sz_i$ 为以 $i$ 为根子树的大小，$ans=\prod\limits_{i=1}^{n}sz_i$，则此时的答案为 $\frac{n!}{ans}$（子树根先填的方案占子树总方案树的 $\frac{1}{sz_i}$，整棵树共 $n!$ 种填写方案）。

所以我们先用一次 $\operatorname{dfs}$ 得到以 $1$ 为根节点的 $ans_1$。现在考虑 $ans_u$ 到 $ans_v$ 的转移：画图不难发现，子树大小数量变化的点只有 $u$ 和 $v$，$sz_v$ 变为 $n$，$sz_u$（原来为 $n$） 变为 $n-sz_v$（原来的 $sz_v$）。所以推出 $ans_v=ans_u \times \frac{n-sz_v}{sz_v}$（原来的 $sz_v$）。那么第二次 $\operatorname{dfs}$ 后就得到了所有的 $ans_i$。

逆元用快速幂即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;
const int N=2e5+5;
const int P=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

il int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=P;
		(a*=a)%=P,b>>=1; 
	}
	return ans;
}

int n,b=1,cnt,head[N],ans[N],son[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

void dfs(int u,int fa){
	son[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v^fa) dfs(v,u),(son[u]+=son[v])%=P;
	}
	(ans[1]*=son[u])%=P;
}

void solve(int u,int fa){
	if(u^1) ans[u]=ans[fa]*(n-son[u])%P*qpow(son[u],P-2)%P;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v^fa) solve(v,u);
	}
}

main(){
	n=wrd(),ans[1]=1; for(int i=2;i<=n;++i) (b*=i)%=P;
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
	}
	dfs(1,0),solve(1,0);
	for(int i=1;i<=n;++i) printf("%lld\n",b*qpow(ans[i],P-2)%P);
	return 0;
} 
```


---

## 作者：KMYC (赞：1)

## 计算方法

其实这题不需要用很复杂的组合数学。

比如说这样的一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/ueluieul.png)

以 $1$ 为根的方案数就是：$\frac{5!}{5\times1\times3\times1\times1}$。

设 $X$= 点的数量的阶乘 },$f(i)$= 以各个点为根的子树大小。

这个公式就是 $\frac{X}{\prod_{i=1}^{n} f(i)}$

公式看起来抽象，实际很好理解：还是以那个图为例 一开始所有方案数都是可行的，然后从根开始选所以要除以节点数，接着再计算以 $\text{2}$，$\text{3}$ 为根的子树的方案。

得到这个公式之后就很好做了，求一个乘法逆元，然后换根正常做就行了。

换根的思路都写在注释里了。

## AC 代码：

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7; 
const int N=200010;
int n,sz[N],prod[N];
/*
sz:子树大小
prod：答案
*/
int inv[N];
vector<int> g[N];
void up(int u,int fa){
	sz[u]=1,prod[u]=1;
	for(auto v:g[u]){
		if(v!=fa){
			up(v,u);
			prod[u]*=prod[v];
			sz[u]+=sz[v];
			prod[u]%=mod;
		}
	}
	prod[u]*=inv[sz[u]];
	prod[u]%=mod;
}
void down(int u,int fa){
	for(auto v:g[u]){
		if(v!=fa){
			prod[v]=prod[u];
			prod[v]*=sz[v];
			prod[v]%=mod;
			prod[v]*=inv[n-sz[v]];
			prod[v]%=mod;
			down(v,u);
		}
	}
}
signed main(){
	cin>>n;
	inv[1]=1;
	for(int i=2;i<=n;i++) inv[i]=-(mod/i)*inv[mod%i]%mod;//求逆元
	for(int i=1;i<=n-1;i++){
		int a,b; cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
  //正常存图
	}
	up(1,0);//计算以每个点为根时的子树大小
	for(int i=1;i<=n;i++) prod[1]*=i,prod[1]%=mod;//计算阶乘
	down(1,0);//计算答案
	for(int i=1;i<=n;i++) cout<<(prod[i]+mod)%mod<<"\n";
	return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

组合计数加换根 DP 的简单题，但细节比较多。

注意到这是树上问题，我们可以将

> 选择一个仍未写有数字且与已写有数字的点相邻的点,如果有多个这样的点,随机选择一个。

转化为：一个点被写有数字，当且仅当这个数的父节点被写了数字。

先不考虑换根，随便钦定一个点为全局根节点，推出整体的方案数。假设不必须满足上面的条件，则方案数很显然是 $n!$，若假如上面的条件，则是在原来选择的基础上添加限制。通俗一点的将，若以节点 $x$ 为根的子树节点个数为 $size_x$，则 $size_x$ 想要被写上数字必须要 $x$ 写上数字。考虑推广到全局，因为各子树互不影响，所以根据乘法原理，最终的方案数应当为：

$$\frac{n!}{\prod \limits _{i=1} ^{n} size_i}$$

不妨设 $dp_j$ 表示以 $j$ 为全局根节点的 $\prod \limits _{i=1} ^{n} size_i$。

接下来考虑换根。假设当前节点为 $x$，同时 $x$ 为全局根节点，现在要将根节点转移到 $nxt$ 上。不难发现除 $size_x$ 和 $size_{nxt}$ 外其他子树在转移过程中均不变。变化的只有 $x$ 和 $nxt$ 这两个点。

原来的 $x$ 为全局根节点，$size_x$ 为 $n$，现在将会变成 $nxt$ 的子树，通过简单容斥可得现为 $n-size_i$，而原来的 $nxt$ 将作为全局根节点，故转移方程为 

$$dp_{nxt}=\frac{dp_x\times (n-size_{nxt})}{size_i}$$

特别的，对于需要取模的除法，应当求出逆元。由于模数是一个质数，可以直接用费马小定理。

最后，输出所有的 $\frac{n!}{dp_i}$ 即可。

code:

```cpp
#define int long long
#define mod 1000000007
int n;
int sz[500086];
int f[500086];//即上文的 dp
std::vector<int>e[500086];
int qpow(int b,int p){
    int ans=1;
    while(p){
        if(p&1)
            ans=ans*b%mod;
        b=b*b%mod;
        p>>=1;
    }
    return ans;
}//快速幂
void dfs(int x,int fa){
    sz[x]=1;
    for(int i:e[x])
        if(i!=fa){
            dfs(i,x);
            sz[x]+=sz[i];//求子树内的节点个数
        }
    f[1]=f[1]*sz[x]%mod;//求积。
    return;
}
void afs(int x,int fa){
    for(int i:e[x])
        if(i!=fa){
            f[i]=f[x]*(n-sz[i])%mod*qpow(sz[i],mod-2)%mod; //即上文的转移方程
            afs(i,x);
        }
    return;
}
int fac;
signed main(){
    std::cin>>n;
    f[1]=1;
    for(int i=1;i<n;i++){
        int x,y;
        std::cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);//存图
    }
    dfs(1,0);//以任意点为根，这里用1
    afs(1,0);//换根
    fac=1;
    for(int i=1;i<=n;i++)
        fac=fac*i%mod;//fac=n!
    for(int i=1;i<=n;i++)
        std::cout<<fac*qpow(f[i],mod-2)%mod<<"\n";//输出
    return 0;//撒花！
}

```

一定要多取模！

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

首先，按照题目的描述，我们很容易知道他求的就是树上拓扑序的数量。同时，我们知道其公式 $\frac{n!}{\prod_{i=1}^nsiz_i}$。

那么，这道题就是一道很明显的换根 DP 了。

具体怎么换呢？我们考虑两个点 $a,b$，他们之间有边连接。假设我们已经知道以 $a$ 为根的答案 $v_a$，分析二者的不同。

我们很容易发现，二者不同的地方有且仅有 $siz_a$ 和 $siz_b$。换根前，$siz_a=n$。换根后，$siz_a$ 变为 $n-siz_b$，$siz_b$ 变为 $n$。

这时候我们再次分析答案中的变化。可以发现，因为变化后的 $siz_b$ 就等于变化前的 $siz_a$，所以以 $b$ 为根的答案 $v_b=v_a\times\frac{siz_b}{n-siz_b}$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int mod = 1e9 + 7, szv = 1e6 + 5;
vector<int>son[szv];
int n, siz[szv], ans[szv], jc, ny[szv];
inline void dfsz(const int& p, const int& f) {
	siz[p] = 1;
	for (int sp : son[p])
		if (sp != f) 
			dfsz(sp, p), 
			siz[p] += siz[sp];
	ans[1] = ans[1] * ny[siz[p]] % mod;
}
inline void dfsa(const int& p, const int& f) {
	if (f) ans[p] = ans[f] * ny[n - siz[p]] % mod * siz[p] % mod;
	for (int sp : son[p]) if (sp != f) dfsa(sp, p);
}
inline int qpow(int a) {
	int tmp = 1, b = mod - 2;
	while (b) {
		if (b & 1) tmp *= a, tmp %= mod;
		a *= a; a %= mod; b >>= 1;
	}
	return tmp;
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n; jc = 1;
	for (int i = 1, l, r; i < n; ++i)
		cin >> l >> r,
		son[l].emplace_back(r),
		son[r].emplace_back(l);
	for (int i = 2; i <= n; ++i) jc = jc * i % mod;
	for (int i = n; i >= 0; i--) ny[i] = qpow(i);
	ans[1] = jc; dfsz(1, 0); dfsa(1, 0);
	for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
	return 0;
}
//私は猫です
```

---

## 作者：LJB00131 (赞：1)

这题难度怎么也不止绿吧。。。

[博客](https://www.cnblogs.com/LJB00131/p/12590040.html)内观影体验更佳

赛时没切掉 /kk 我发现我并不会多重集的排列这个东西。

简单介绍一下，令 $S$ 为 $k$ 种不同类型对象(每种集合里的对象等价)的多重集合，从S中取r个数构成排列的方案数称为 $S$ 的 $r$ 排列。当 $r = n$ 时，有
$P(n, n_1*a_1, ..., n_k*a_k) = \frac{(n - 1)!}{\prod_{i = 1}^{k}n_k!}$

回到这道题，我们首先取1为根，做一遍树形dp, 令 $f[i]$ 表示以i为根的树有多少种填数字的方案。

$$
f[x] = 
\begin{cases}
\frac{(sz[x] - 1)!}{\prod_{i \in{ch(x)}}{sz[i]!}} \times \prod_{i \in{ch(x)}}{f[i]} , sz[x] > 1 \\
1, sz[x] = 1
\end{cases}
$$

是叶子结点就是1， 不是叶子结点就是我把每个子树看做一个集合做多重集排列(得出顺序), 然后直接乘每个每个子树的贡献就行。

做完第一次树形dp之后进行换根dp，这一步应该比较简单，只要每次换的时候消除/加入影响即可

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 200005
const int mod = 1e9 + 7;
#define add(x, y) (x + y >= mod ? x + y - mod : x + y)
#define dec(x, y) (x < y ? x - y + mod ? x - y)

int n, a[N], head[N], nxt[N << 1], to[N << 1], cnt = 0, sz[N], f[N], fac[N], inv[N], g[N];

int Pow(int x, int k)
{
	int base = x, ans = 1;
	while(k)
	{
		if(k & 1) ans = 1ll * ans * base % mod;
		base = 1ll * base * base % mod;
		k >>= 1;
	}
	return ans;
}

void adde(int x, int y)
{
	cnt++;
	to[cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}

void dfs(int x, int fa)
{
	sz[x] = 1;
	for(int p = head[x]; p; p = nxt[p])
	{
		int v = to[p];
		if(v == fa) continue;
		dfs(v, x);
		sz[x] += sz[v];
	}
	f[x] = fac[sz[x] - 1];
	for(int p = head[x]; p; p = nxt[p])
	{
		int v = to[p];
		if(v == fa) continue;
		f[x] = 1ll * f[x] * inv[sz[v]] % mod * f[v] % mod; 
	}
}

void dfs2(int x, int fa)
{
	for(int p = head[x]; p; p = nxt[p])
	{
		int v = to[p];
		if(v == fa) continue;
		int t = 1ll * g[x] * fac[n - 1 - sz[v]] % mod * inv[n - 1] % mod * fac[sz[v]] % mod * Pow(f[v], mod - 2) % mod;
		int ns = n - sz[v];
		// cout << x << ' ' << v << ' ' << t << ' ' << ns << endl;
		g[v] = 1ll * f[v] * t % mod * inv[ns] % mod * fac[n - 1] % mod * inv[sz[v] - 1] % mod;
		dfs2(v, x);
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
	}
	fac[0] = 1, inv[0] = 1, fac[1] = 1, inv[1] = 1;
	for(int i = 2; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod, inv[i] = Pow(fac[i], mod - 2);
	dfs(1, 1);
	// cout << f[1] << endl;
	g[1] = f[1];
	dfs2(1, 1);
	for(int i = 1; i <= n; i++)
		printf("%d\n", g[i]);
	return 0;
}
```

---

## 作者：_Gabriel_ (赞：0)

### 思路

有根树的树上拓扑序问题。

对于每一个 $i$，以 $i$ 为根。

树上拓扑序问题有一个公式，为 $n! \times \prod \limits_{i=1}^n \dfrac{1}{Sz_i}$（$Sz_i$ 指的是一个子树点的个数）。

公式证明可以看 [这篇博客](https://blog.csdn.net/qq_50285142/article/details/126436749)。

可以先把 $1 \sim n$ 的逆元数组 $inv$ 给预处理。

设 $ans_i$ 为根为 $i$ 时的答案。

先 DFS 一遍求出以 $1$ 为根的 $Sz$。

接下来的 $ans_2 \sim ans_n$ 用换根即可。

即 $ans_v=ans_u \times Sz_v \times inv_{n-Sz_v}$。

最后输出一下 $ans_1 \sim ans_n$ 即可。

复杂度 $O(n)$。

### 代码


```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
ll inv[N], sz[N], ans[N];
vector<int> G[N];
int n;

void dfs1(int u, int fa) {
    sz[u] = 1;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
    ans[1] = ans[1] * inv[sz[u]] % mod;
}
void dfs2(int u, int fa) {
    for (auto v : G[u]) {
        if (v == fa) continue;
        ans[v] = ans[u] * sz[v] % mod * inv[n - sz[v]] % mod;
        dfs2(v, u);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
    	inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
    ans[1] = 1;
    for (int i = 1; i <= n; i++) {
    	ans[1] = ans[1] * i % mod;
	}
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
    	printf("%lld\n", ans[i]);
	}
    return 0;
}
```

---

## 作者：MatrixGroup (赞：0)

- 解法

考虑如果只要求一次会怎么样。

不妨反过来考虑（因为这样方便树形 dp）：

- 你可以涂叶子节点。
- 你可以涂与任意已涂色节点相邻的节点。

首先为每个叶子内部确定好顺序，是 $\prod\limits_{u\text{ is son of }v}dp_u$。

然后排列，有 $(siz_v-1)!$ 种，但是因为叶子内部相对顺序不能变，所以要除掉 $\prod\limits_{u\text{ is son of }v}siz_u!$。

综上，$dp_v=(siz_v-1)!\prod\limits_{u\text{ is son of }v}\dfrac{dp_u}{siz_u!}$。

然后考虑换根 dp。

如果原来 $u$ 是根，现在 $v$ 是根，那么：

$dp'_u=dp_u\times\dfrac{(siz'_u-1)!siz_v!}{(siz_u-1)!dp_v}$（把 $siz_u$ 替换为 $siz'_u$，消除 $dp_v$ 和 $siz_v$ 的影响）

$dp'_v=dp_v\times\dfrac{(siz'_v-1)dp'_u}{(siz_v-1)siz'_u}$（同理，记住这次是变化后的 $u$）

于是就可以愉快地换根 dp 了。

记住有两种逆元：预处理的阶乘逆元和 $dp$ 的逆元。

复杂度 $O(n\log p)$。（$p=10^9+7$）

- 代码

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)
#define rep1(i,n) for(int i=1,_##i##__end=(n);i<=_##i##__end;++i)
#define pb push_back
typedef long long ll;
using namespace std;
const ll mod2=1000000007;
int n,u,v;
vector<int> con[222222];
int siz[222222];
ll dp[222222];
ll ans[222222];
ll fac[222222];
ll inv[222222];
ll qkpw(ll a,ll b)//快速幂（求逆元）
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod2;
		a=a*a%mod2;
		b>>=1;
	}
	return res;
}
void init()//阶乘逆元
{
	fac[0]=1;
	rep1(i,200000) fac[i]=fac[i-1]*i%mod2;
	inv[200000]=qkpw(fac[200000],mod2-2);
	per(i,200000) inv[i]=inv[i+1]*(i+1)%mod2; 
}
void dfs(int x,int p)//预处理以1为根的dp
{
	dp[x]=1;
	siz[x]=1;
	rep(i,con[x].size())
	{
		int ver=con[x][i];
		if(ver==p) continue;
		dfs(ver,x);
		siz[x]+=siz[ver];
		dp[x]=dp[x]*dp[ver]%mod2*inv[siz[ver]]%mod2;
	}
	dp[x]=dp[x]*fac[siz[x]-1]%mod2;
}
void root(int u,int v)//换u和v,u是原来的，v是现在的（根）
{
	dp[u]=dp[u]*qkpw(dp[v],mod2-2)%mod2*inv[siz[u]-1]%mod2*fac[siz[u]-siz[v]-1]%mod2*fac[siz[v]]%mod2;
	siz[u]-=siz[v];
	siz[v]+=siz[u];
	dp[v]=dp[v]*dp[u]%mod2*fac[siz[v]-1]%mod2*inv[siz[v]-siz[u]-1]%mod2*inv[siz[u]]%mod2;
}
void reroot(int x,int p)//换根dp
{
	ans[x]=dp[x];
	rep(i,con[x].size())
	{
		int ver=con[x][i];
		if(ver==p) continue;
		root(x,ver);
		reroot(ver,x);
		root(ver,x);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n;
	rep(i,n-1)
	{
		cin>>u>>v;
		con[u].pb(v);
		con[v].pb(u);
	}
	init();
	dfs(1,-1);
	reroot(1,-1);
	rep1(i,n)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

