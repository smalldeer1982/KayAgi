# Normal

## 题目描述

某天 WJMZBMR 学习了一个神奇的算法：树的点分治！

这个算法的核心是这样的：

```cpp
time = 0
Solve(Tree a) {
  time += a.size;
  if (a.size == 1) return;
  else {
    select x in a;
    delete a[x];
  }
}
```

```
消耗时间 = 0
Solve(树 a)
  消耗时间 += a 的大小
  如果 a 中 只有 1 个点
    退出
  否则
    在 a 中选一个点x
    在 a 中删除点x
```

那么 $a$ 变成了几个小一点的树，对每个小树递归调用 `Solve`。

我们注意到的这个算法的时间复杂度跟选择的点 $x$ 是密切相关的，如果 $x$ 是树的重心，那么时间复杂度就是 $O(n \log n)$。

WJMZBMR 决定随机在 $a$ 中选择一个点作为 $x$，Sevenkplus 告诉他这样做的最坏复杂度是 $O(n^2)$，但是 WJMZBMR 就是不信，于是 Sevenkplus 花了几分钟写了一个程序证明了这一点，你也试试看吧。

现在给你一颗树，你能告诉 WJMZBMR 他的算法需要的期望消耗时间吗（以给出的 `Solve` 函数中的为标准）？

## 说明/提示

对于所有的数据，保证 $1\leq n\leq 30000$。

## 样例 #1

### 输入

```
3
0 1
1 2```

### 输出

```
5.6667```

# 题解

## 作者：critnos (赞：5)

我知道你想卷，但你先别急.jpg

容易看出答案就是所有链点数的倒数和。大概就是考虑一个点在点分树上的深度期望，就是一个，把这个点看作根，然后每次随一个点并把这个子树删掉的次数。那么一个点被选中当且仅当他比他的祖先都更早被选中。

接下来我们可以解决实数情形下的带点权的上述问题。这个是[经典技巧](https://www.luogu.com.cn/problem/CF1578G)。

考虑点分治，那么相当于要做一个，支持给 $v$ 对集合 $S$ 求 $\sum_{x\in S} \frac 1 {x+v}$。对于所有 $p=3^k$，记 $\Delta=v-p$，考虑：

$$\sum_{x\in S} \frac 1 {x+p+\Delta}$$

$$\sum_{x\in S} \frac 1 {x+p} \frac {x+p} {x+p+\Delta}$$

$$\sum_{x\in S} \frac 1 {x+p} \frac {1} {1-(-\frac {\Delta} {x+p})}$$

$$\sum_{x\in S} \frac 1 {x+p} \sum_{i\ge 0}(-\frac {\Delta} {x+p})^i$$

$$\sum_{i\ge 0} (-\frac {\Delta} p)^i\sum_{x\in S} \frac 1 {x+p} (\frac p {x+p})^i$$

可以找到 $p$ 使得 $|\frac {\Delta} p|\le 0.5$，于是 $i$ 可以有 $O(\log n\epsilon^{-1})$ 的求和上界。

时间复杂度总计 3log。

---

## 作者：Milmon (赞：4)

一个点对答案的贡献就是其在点分树上的深度。一对点 $u,v$ 若满足在点分树上，$u$ 是 $v$ 的祖先或者 $v$ 是 $u$ 的祖先，就会对答案造成 $1$ 的贡献。设 $u,v$ 的距离为 $d$，即 $u$ 到 $v$ 的路径（含端点）上有 $d+1$ 个点。由于选点的概率是均匀的，$u$ 是 $v$ 的祖先当且仅当这 $d+1$ 个点中 $u$ 第一个被选中，故 $u$ 和 $v$ 有祖先关系的概率为 $d+1$。

问题转化为求出距离为 $d=1,2,\cdots$ 的点对分别有多少。考虑点分治，在一个结点上只统计点对路径经过该结点的点对。只需计算出每棵子树中各个深度的点数，注意到要让深度为 $d$，则需要两个在不同子树中找到两个深度和为 $d$ 的点，可以将各个深度的点数的数组做卷积。设有子树 $T_1,T_2,\cdots,T_m$ 的大小按照升序排序，则对于任意 $i > 1$，都令 $T_1+T_2+\cdots+T_{i-1}$ 和 $T_i$ 做卷积即可。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：FLY_lai (赞：3)

# 【题意】

求点分治的期望复杂度。保留四位小数。

（从树里等概率选点，遍历子树，再递归进子树）

$n\le 3\times 10^4$。

# 【题解】

**期望题，先把随机变量说明白。**

令 $p_{i,j}$ 为 $i$ 在某次分治中作为根结点，被 $j$ 贡献复杂度的概率。有 $p_{i,j}=\frac{1}{dis(i,j)+1}$，其中 $dis(i,j)$ 为 $i,j$ 边数。因为要使得 $i$ 作为根结点时 $j$ 能贡献，必然是 $i,j$ 路径上每个点都没有被选作分治点。

答案即 $\sum\sum p_{i,j}$。为了方便统计和避免精度损失，改求 $cnt_i$ 为有 $i$ 条边的路径总数。答案即 $2(\sum_{i=2}^{n-1}cnt_i\cdot \dfrac{1}{i+1})+n$，乘  $2$ 是因为 $p_{i,j},p_{j,i}$ 要算两次，$+n$ 是因为 $p_{i,i}$ 算一次。

---

接下来的问题是怎么求 $cnt_i$。涉及树上路径统计，考虑点分治。

设当前的根是 $x$，有子结点  $u_1\sim u_k$。对于 $u_i$，设 $x$ 到它子树内各长度路径条数为 $cnt_i[1\sim dth_i]$。

令 $s_i[j]=\sum_{k=1}^{i}cnt_k[j]$。那么经过 $x$ 的路径的贡献可以表示为：

$$
cnt_x\leftarrow cnt_x+\sum_{i=1}^{k}\sum_{a=1}^{x-1}s_{i-1}[a]\cdot cnt_i[x-b]
$$

这是卷积的形式。考虑多项式优化。

把 $u_1\sim u_k$ 按照子树深度从小到大排序。

对子树 $u_i$ 定义生成函数 $F_i(x)=\sum cnt_i[j]\cdot x^j$，$G_i(x)=\sum_{i=1}^{i}F_i(x)$。贡献可以简单写作 $G_{i-1}(x)*F_i(x)$。

相邻的直接卷即可。

复杂度分析：

$F$ 的大小为子树深度，设排序后深度为 $d_1\le d_2\le \cdots\le d_k$。

先考虑 $G_i(x)$，它是 $F_i(x)$ 的前缀和，也就是一次分治计算 $G$ 的复杂度是 $d_1+d_2+\cdots+d_k\le sz_1+sz_2+\cdots+sz_k$，而即使是 $sz_1+sz_2+\cdots+sz_k$，因为点分树每个点子树大小求和是 $O(n\log n)$ 的，所以这一部分的复杂度是 $O(n\log n)$。

再考虑 $G_{i-1}(x)*F_i(x)$。因为按深度排序了，所以单次乘法复杂度是 $O(\,(|G_{i-1}|+|F_i|)\log (|G_{i-1}|+|F_i|)\,)=O((d_{i-1}+d_i)\log (d_{i-1}+d_i))=O(d_i\log d_i)$，类似分析可以得到复杂度 $O(n\log^2n)$。

因此总复杂度 $O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 3e4 + 5, MOD = 998244353, inf = 0x3f3f3f3f;

int n;
vector<int> e[N];

namespace Poly {
	typedef vector<int> poly;
	
	ll fpow(ll a, ll b, ll p) {
		ll mul = 1;
		while (b) {
			if (b & 1)
				mul = mul * a % p;
			a = a * a % p;
			b >>= 1;
		}
		return mul;
	}
	ll mmi(ll a, ll p) {
		return fpow(a, p - 2, p);
	}
	
	int rev[N * 4];
	void DFT(poly &a, int lim, int op = 1) {
		for (int i = 0; i < lim; i++)
			if (i < rev[i])
				swap(a[i], a[rev[i]]);
		for (int i = 1; i < lim; i <<= 1) {
			ll wn = fpow((op == 1 ? 3 : (MOD + 1) / 3), (MOD - 1) / (i << 1), MOD);
			for (int j = 0; j < lim; j += (i << 1)) {
				ll w = 1;
				for (int k = 0; k < i; k++, w = w * wn % MOD) {
					ll x = a[j + k], y = w * a[j + k + i] % MOD;
					a[j + k] = (x + y) % MOD;
					a[j + k + i] = ((x - y + MOD) % MOD);
				}
			}
		}
		if (op == -1) {
			ll inv = fpow(lim, MOD - 2, MOD);
			for (int i = 0; i < lim; i++)
				a[i] = a[i] * inv % MOD;
		}
	}
	poly NTT(poly a, poly b) {
		int len = a.size() + b.size() - 1;
		int lim = 1, pw = 0;
		while (lim < len)
			lim <<= 1, pw++;
		a.resize(lim);
		b.resize(lim); 
		for (int i = 0; i < lim; i++)
			rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (pw - 1)));
		DFT(a, lim, 1);
		DFT(b, lim, 1);
		for (int i = 0; i < lim; i++)
			a[i] = 1ll * a[i] * b[i] % MOD;
		DFT(a, lim, -1);
		a.resize(len);
		return a;
	}
	poly operator*(poly a, poly b) {
		return NTT(a, b);
	}
	poly operator+(poly a, poly b) {
		if (a.size() < b.size())
			swap(a, b);
		for (int i = 0; i < b.size(); i++)
			a[i] = (1ll * a[i] + b[i]) % MOD;
		return a;
	}
	void print(poly &a) {
		printf("%d:", a.size());
		for (int i = 0; i < a.size(); i++)
			printf("%d ", a[i]);
		puts("");
	}
}
using namespace Poly;

bool vis[N] = {};
int sz[N], allsz;
int mn, cen;

void getsz(int x, int pr) {
	sz[x] = 1;
	for (auto i: e[x])
		if (i != pr && !vis[i]) {
			getsz(i, x);
			sz[x] += sz[i];
		}
}
void getcen(int x, int pr) {
	int mx = -1;
	for (auto i: e[x])
		if (i != pr && !vis[i]) {
			getcen(i, x);
			mx = max(mx, sz[i]);
		}
	mx = max(mx, allsz - sz[x]);
	if (mx < mn) {
		mn = mx;
		cen = x;
	}
}
typedef pair<int, int> pii;
int getdth(int x, int pr) {
	int ret = 0;
	for (auto i: e[x])
		if (i != pr && !vis[i])
			ret = max(ret, getdth(i, x) + 1);
	return ret;
}

poly ans;
poly a, b, tmp;
void upd(int x, int pr, int dth) {
	b[dth]++;
	for (auto i: e[x])
		if (i != pr && !vis[i])
			upd(i, x, dth + 1);
}
void slv(int x) {
	getsz(x, 0);
	allsz = sz[x];
	mn = inf, cen = -1;
	getcen(x, 0);
	x = cen;
	
	//统计所有经过x的路径 
	vector<pii> v;
	for (auto i: e[x])
		if (!vis[i])
			v.push_back(make_pair(getdth(i, x) + 1, i));
	if (v.size() > 0) {
		sort(v.begin(), v.end());
		a.resize(1);
		a[0] = 1;
		for (auto i: v) {
			b.resize(i.first + 1);
			for (int j = 0; j <= i.first; j++)
				b[j] = 0;
			upd(i.second, x, 1);
			tmp = a * b;
			ans = ans + tmp;
			a = a + b;
		}
	}
	
	vis[x] = true;
	for (auto i: e[x])
		if (!vis[i])
			slv(i);
}

int main() {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		u++, v++;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	ans.resize(n);
	slv(1);
	double sum = 0.0;
	for (int i = 1; i < n; i++)
		sum += ans[i] * 1.0 / (i + 1);
	sum *= 2;
	sum += n;
	printf("%.4lf\n", sum);
	return 0;
}
```

---

## 作者：cheng2010 (赞：1)

为啥感觉大苣们写的这么复杂呢？那蒟蒻我就来写一篇题解吧。

首先，我们可以考虑拆贡献，每个点被删除的概率是 $1$ 那么考虑以某个点 $x$ 为根时，$y$ 可以对 $x$ 贡献的概率，由于路径上每个点都被删的概率相同，由期望的线性性即 $P(x+y)=P(x)+P(y)$，可以得出这个概率为 $\frac{1}{dis(x,y)+1}$，设它为 $P(x,y)$，那么答案即为 $\displaystyle \sum_{i=1}^{n} \sum_{j=1}^n P(i,j)$。

考虑优化，记录每一个 $dis(i,j)$ 出现的次数，为 $cnt_i$ 那么答案变成了 $\displaystyle \sum_{i=1}^{n-1} \frac{cnt_i}{i+1}$ 注意是从 $1$ 开始的，**不是 $2$。**

对于树上路径题，可以利用点分治，对于当前分治中心 $x$，我们记它一个儿子为 $v$。

以下约定：

$lst_i$ 为之前遍历的所有儿子以 $x$ 为起点的长度为 $i$ 路径数。

$cnt_i$ 为 $v$ 子树内以 $x$ 为起点的长度为 $i$ 路径数。

$path_i$ 为经过 $x$ 的长度为 $i$ 路径数。

$dis_i$ 为所有长度为 $i$ 路径数。

那么对于一个 $x$，有 $path_{i+j}=lst_i \times cnt_j $，于是可以卷了！

我们有：$path=lst*cnt$，NTT 或 FFT 随便做。

$dis$ 的更新即把每个 $path$ 加起来即可。

答案即 $2\displaystyle \sum_{i=1}^{n-1} \frac{dis_i}{i+1}+n$，加 $n$ 是因为单点也算，乘 $2$ 是因为 $i$ 到 $j$ 与 $j$ 到 $i$ 是两条路径，但点分治只算了一次。

时间复杂度 $O(n \log^2 n)$，但跑得比暴力慢也是十分糖了。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+7;
const int Mod=998244353;
const int G=3,IG=332748118; 
int a[N],b[N];
int limit;
int rev[N];
inline int ks(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
		{
			res=res*a%Mod;
		}
		a=a*a%Mod;
		b>>=1;
	}
	return res;
}
inline void NTT(int *A,int opt)
{
	for(int i=0;i<limit;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
	for(int mid=1;mid<limit;mid<<=1)
	{
		int one=ks(opt==1?G:IG,(Mod-1)/(mid<<1));
		for(int len=mid<<1,i=0;i<limit;i+=len)
		{
			int w=1;
			for(int j=0;j<mid;j++,w=w*one%Mod)
			{
				int a1=A[i+j],a2=w*A[i+j+mid]%Mod;
				A[i+j]=(a1+a2%Mod)%Mod;
				A[i+j+mid]=(a1-a2+Mod)%Mod;
			}
		}
	}
}
inline void MUL(int *ans,int *A,int *B,int len)
{
	for(int i=0;i<=len;i++) a[i]=A[i],b[i]=B[i];
	limit=1;
	int l=0;
	while(limit<=len*2) limit<<=1,l++;
	for(int i=1;i<limit;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1);
	NTT(a,1);
	NTT(b,1);
	for(int i=0;i<limit;i++)
		a[i]=a[i]*b[i]%Mod;
	NTT(a,0);
	int inv=ks(limit,Mod-2);
	for(int i=0;i<=len*2;i++)
	{
		a[i]=a[i]*inv%Mod;
		ans[i]+=a[i];
	}
	for(int i=0;i<=limit;i++) a[i]=b[i]=0;
}
int n;
vector<int> edge[N];
inline void add(int x,int y){edge[x].push_back(y);}
int rt,Min;
int siz[N];
bool vis[N];
inline void get_rt(int x,int fa,int all)
{
	siz[x]=1;
	int Max=0;
	for(int v:edge[x])
	{
		if(v==fa||vis[v]) continue;
		get_rt(v,x,all);
		siz[x]+=siz[v];
		Max=max(Max,siz[v]); 
	}
	Max=max(Max,all-siz[x]);
	if(Min>Max)
	{
		Min=Max;
		rt=x;
	}
}
int dis[N],cnt[N],path[N],lst[N];
int st[N],top;
bool bz[N];
int md;
inline void get_dis(int x,int fa,int d)
{
	md=max(md,d);
	if(!bz[d]) st[++top]=d;
	cnt[d]++;
	for(int v:edge[x])
	{
		if(v==fa||vis[v]) continue;
		get_dis(v,x,d+1);
	}
}
inline void solve(int x)
{
	int am=0;
	for(int v:edge[x])
	{
		if(vis[v]) continue;
		md=0;
		get_dis(v,x,1);
		am=max(am,md);
		MUL(path,lst,cnt,am); 
		for(int i=1;i<=md;i++) lst[i]+=cnt[i];
		for(int i=1;i<=top;i++) bz[st[i]]=0,cnt[st[i]]=0;
		top=0;
	}
	for(int i=1;i<=am*2;i++) dis[i]+=path[i],path[i]=0,lst[i]=0;
}
inline void dfs(int x)
{
	vis[x]=1;
	solve(x);
	for(int v:edge[x])
	{
		if(vis[v]) continue;
		Min=1e9;
		get_rt(v,0,siz[v]);
		dfs(rt);
	}
}
signed main()
{
	lst[0]=1;
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%lld %lld",&x,&y);
		x++,y++;
		add(x,y);
		add(y,x);
	}
	Min=1e9;
	get_rt(1,0,n);
	dfs(rt);
	double ans=0;
	for(int i=1;i<n;i++)
		ans=ans+(double)dis[i]/(double)(i+1);
	ans=ans*2.0;
	printf("%.5lf\n",ans+n*1.0);
}
```

---

## 作者：LastKismet (赞：0)

# Sol
考虑如何简单地计算这个期望值，或者说考虑如何优美地拆贡献。

考虑定义 $v_{i,j}$ 表示以 $i$ 为根节点时 $j$ 做出的贡献，不难发现，若此时 $i,j$ 连通，贡献为 $1$。否则贡献为 $0$。

那么考虑表示 $i,j$ 连通的概率，每个点是否存在是等概率的，二者连通当且仅当二者路径上所有点均存在，那么概率即为 $\frac{1}{\mathrm{dis(i,j)+1}}$。

那么我们可以对路径考虑贡献，于是考虑点分治。

对于一个根节点，我们可以找出所有位于其子树内且经过其的路径。通过统计各长度的路径数量，我们可以枚举长度计算贡献。显然长度不超过子树大小。

考虑统计长为 $k$ 的路径数量，先计算出所有点到根节点的距离，然后这就是一个简单的卷积，FFT 或 NTT 解决即可。

值得注意的是，一条长度为正的路径的贡献应当乘二，因为可以将另一端视作根节点。

# code
```cpp
const int N=3e4+5;

namespace NTT{
    const mint p=0,g=3,gi=332748118;
    typedef vec<mint> poly;
    vec<int> r;
    void ntt(int lim,poly &a,int type){
        a.resize(lim);
        repl(i,0,lim)if(i<r[i])swap(a[i],a[r[i]]);
        for(int mid=1;mid<lim;mid<<=1){
            mint w1=((~type)?g:gi)^((p-1)/(mid<<1));
            for(int j=0;j<lim;j+=(mid<<1)){
                mint w=1;
                repl(k,0,mid){
                    mint x=a[j+k],y=w*a[j+mid+k];
                    a[j+k]=x+y;
                    a[j+mid+k]=x-y;
                    w=w*w1;
                }
            }
        }
    }
    poly operator*(poly a,poly b){
        int lim=1,l=0,len=a.size()+b.size()-1;
        while(lim<a.size()+b.size())lim<<=1,l++;
        r.resize(lim);
        repl(i,0,lim)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        ntt(lim,a,1);ntt(lim,b,1);
        repl(i,0,lim)a[i]=a[i]*b[i];
        ntt(lim,a,-1);
        a.resize(len);
        mint inv=(mint)lim^(p-2);
        repl(i,0,a.size())a[i]*=inv;
        return a;
    }
    poly operator+(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]+b[i];
        return a;
    }
    poly operator-(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]-b[i]+p;
        return a;
    }
}
using namespace NTT;

int n;
vec<int> G[N];

bool don[N];

int cnt,siz[N];
void getsiz(int now,int fid){
    ++cnt;siz[now]=1;
    for(auto nxt:G[now]){
        if(nxt==fid||don[nxt])continue;
        getsiz(nxt,now);
        siz[now]+=siz[nxt];
    }
}
int rot,mx[N];
void getrot(int now,int fid){
    mx[now]=cnt-siz[now];
    for(auto nxt:G[now]){
        if(nxt==fid||don[nxt])continue;
        getrot(nxt,now);
        chmax(mx[now],siz[nxt]);
    }
    if(mx[now]<mx[rot])rot=now;
}
poly a,b,c;
void dfs(int now,int fid,int dis){
    ++b[dis];
    for(auto nxt:G[now]){
        if(nxt==fid||don[nxt])continue;
        dfs(nxt,now,dis+1);
    }
}
flt ans;
void calc(int rt){
    cnt=0;getsiz(rt,0);
    rot=0;mx[0]=inf;getrot(rt,0);don[rot]=1;
    a.clear();a.resize(cnt);a[0]=1;
    for(auto nxt:G[rot]){
        if(don[nxt])continue;
        b.clear();b.resize(cnt);
        dfs(nxt,rot,1);
        c=a*b;c.resize(cnt);
        repl(i,1,cnt)ans+=flt(c[i].x)/(i+1)*2;
        a=a+b;
    }
    for(auto nxt:G[rot])if(!don[nxt])calc(nxt);
}

inline void Main(){
    read(n);
    repl(i,1,n){
        int x,y;
        read(x,y);++x,++y;
        G[x].pub(y);G[y].pub(x);
    }
    calc(1);
    put(ans+n);
}
```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑一对有序点对 $(u,v)$ 产生贡献的概率，记为 $P_{u,v}$。由于一对点 $(u,v)$ 产生的价值为 $1$ 单位时间，所以答案是 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}P_{i,j}$。

首先 $P_{u,u}=1$。对于一对 $(u,v),u\ne v$，如果 $id=u$ 的时候 $v$ 在这 $a$ 个点中，那么 $u,v$ 应该是联通的。又因为树上简单路径唯一，所以 $P(u,v)$ 这条路径上所有不为 $u$ 的点被删的时间应该在 $u$ 之后。对于其它的点因为与 $(u,v)$ 没有关系所以不考虑 $u$ 和它们删除时间的关系。那么有：$P_{u,v}=\frac{1}{dis_{u,v}+1}$。

那么答案就是 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\frac{1}{dis_{i,j}+1}$。套个点分治就行了，每次暴力的时候维护出 $d_{i}+d_{j}=k$ 的方案数 $c_k$，那么这个重心的贡献就是 $\sum c_k \frac{1}{k+1}$。时间复杂度 $O(n\log^2 n)$。

## 代码

```cpp
il void fft(Cmp a[],int len,int inv){
	for(re int i=0;i< len;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(re int i=1;i< len;i<<=1){
		for(re int j=0;j< len;j+=(i<<1)){
			Cmp w=1;
			for(re int k=0;k< i;++k){
				Cmp w(cos(2*pi*(j+k)/(i<<1)),inv*sin(2*pi*(j+k)/(i<<1)));
				Cmp x=a[j+k],y=a[j+k+i]*w;
				a[j+k]=(x+y),
				a[j+k+i]=(x-y);
			}
		}
	}
	return ;
}
il void ntt(int a[],int len,int inv){
	for(re int i=0;i< len;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(re int i=1;i< len;i<<=1){
		int Wn=qmi((inv==1)?G:Gi,(p-1)/(i<<1),p);
		for(re int j=0;j< len;j+=(i<<1)){
			int w=1;
			for(re int k=0;k< i;++k){
				int x=a[j+k]%p,y=a[j+k+i]*w%p;
				a[j+k]=(x+y)%p,
				a[j+k+i]=(x-y+p)%p;
				w=w*Wn%p;
			}
		}
	}
	return ;
}
il void work_ntt(int a[],int b[],int c[],int len){
	ntt(a,len,1),ntt(b,len,1);
	for(re int i=0;i< len;++i) c[i]=a[i]*b[i]%p;
	ntt(c,len,-1);
	return ;
}
il void work_fft(Cmp a[],Cmp b[],Cmp c[],int len){
	fft(a,len,1),fft(b,len,1);
	for(re int i=0;i< len;++i) c[i]=a[i]*b[i];
	fft(c,len,-1);
	return ;
}
il void init(){
	k=1,L=0;
	while(k<n+m+1) k<<=1,++L;
	for(re int i=0;i<=k;++i) rev[i]=((rev[i>>1]>>1)|((i&1)<<(L-1)));
	return ;	
}
il void find(int u,int fa){
	siz[u]=1,maxp[u]=0;
	for(auto v:e[u])
	if(v!=fa&&!vis[v]){
		find(v,u);
		siz[u]+=siz[v],
		maxp[u]=max(maxp[u],siz[v]);
	}
	maxp[u]=max(maxp[u],Siz-siz[u]);
	if(maxp[u]<maxp[Root]) Root=u;
	return ;
}
il void dfs(int u,int fa,int dis){
	++dis;
	mdep=max(mdep,dis);
	++cnt[dis];
	for(auto v:e[u])
	if(v==fa||vis[v]) continue;
	else dfs(v,u,dis);
	return ;
}
il void calc(int u){
	mdep=0;
	++cnt[0];
	for(auto v:e[u])
	if(!vis[v]) dfs(v,u,0);
	n=m=mdep+1;
	init();
	for(re int i=0;i<=k+1;++i) c[i]=a[i]=b[i]=Cmp(0,0);
	for(re int i=0;i<=mdep;++i) a[i]=b[i]=Cmp(cnt[i],0);
	work_fft(a,b,c,k);
	for(re int i=0;i<=k;++i){
		int Cnt=(int)(c[i].real()*1.0/k+0.5);
		res+=Cnt*1.0*(1.0/(i+1));
	}
	for(re int i=0;i<=mdep;++i) cnt[i]=0;
	for(auto v:e[u])
	if(!vis[v]){
		mdep=0;
		dfs(v,u,0);
		n=m=mdep+1;
		init();
		for(re int i=0;i<=k+1;++i) c[i]=a[i]=b[i]=Cmp(0,0);
		for(re int i=0;i<=mdep;++i) a[i]=b[i]=Cmp(cnt[i],0);
		work_fft(a,b,c,k);
		for(re int i=0;i<=k;++i){
			int Cnt=(int)(c[i].real()*1.0/k+0.5);
			res-=Cnt*1.0*(1.0/(i+1));
		}
		for(re int i=0;i<=mdep;++i) cnt[i]=0;
	}
	return ;
}
il void work(int u){
	vis[u]=1;
	calc(u);
	for(auto v:e[u])
	if(!vis[v]){
		Siz=siz[v],Root=0,maxp[0]=pt+1;
		find(v,0);
		work(Root);
	}
	return ;
}

il void solve(){
	Gi=qmi(G,p-2,p);
	pt=rd;
	for(re int i=1;i<pt;++i){
		int u=rd+1,v=rd+1;
		e[u].push_back(v),
		e[v].push_back(u);
	}
	Siz=pt,maxp[0]=pt+1,vis[0]=1,find(1,0);
	work(Root);
	printf("%.4lf\n",res);
    return ;
}
```

---

