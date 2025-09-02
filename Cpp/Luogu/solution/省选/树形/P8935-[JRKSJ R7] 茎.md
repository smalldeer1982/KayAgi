# [JRKSJ R7] 茎

## 题目描述

你有一棵 $n$ 个点的根节点为 $1$ 的有根树，现在你要对这棵树进行剪枝，每次你可以选择一个还未被剪掉的节点 $u$ 进行操作，然后剪掉 $u$ 的子树所有点（包括 $u$）。当且仅当你剪掉 $1$ 时，操作停止。  

你知道 $1$ 到 $x$ 这条路径是这棵树的茎，需要特殊处理。所以你需要在第 $k$ 次剪枝时对 $x$ 进行操作，而非仅仅将其剪掉，即你不能在第 $k$ 次及以前对其祖先进行操作使其被连带剪掉。 

求有多少种不同的操作序列，两个操作序列不同当且仅当长度不同或存在一次操作 $i$ 使得两操作序列在第 $i$ 次时选择的 $u$ 不同。输出答案模 $10^9+7$。

## 说明/提示

### 样例解释

对于样例 $1$，只有一种操作方法满足条件，第一次操作 $3$，第二次操作 $2$，第三次操作 $1$。  

对于样例 $2$，满足条件的操作序列：$\{3,4,1\},\{3,4,2,1\},\{3,4,5,1\},\{3,4,5,2,1\},\\ \{5,4,1\},\{5,4,2,1\},\{5,4,2,3,1\},\{5,4,3,1\},\{5,4,3,2,1\}$。

### 数据规模
本题采用捆绑测试。

|$\text{Subtask}$|$n\le$|特殊性质|$\text{Score}$|
|:-:|:-:|:-:|:-:|
|$1$|$7$|无|$5$|
|$2$|$17$|无|$10$|
|$3$|$50$|$\text A$|$5$|
|$4$|$50$|无|$15$|
|$5$|$500$|$\text A$|$5$|
|$6$|$500$|$\text B$|$5$|
|$7$|$500$|$\text C$|$10$|
|$8$|$500$|无|$45$|

特殊性质 $\text A$：保证 $k=1$。\
特殊性质 $\text B$：保证 $x=1$。\
特殊性质 $\text C$：保证 $\forall i\in[1,n-1],i$ 与 $i+1$ 有边。

对于 $100\%$ 的数据，$1\le k,x\le n\le 500$。  


## 样例 #1

### 输入

```
3 2 2
1 2
1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5 2 4
1 2
1 3
2 4
2 5```

### 输出

```
9```

## 样例 #3

### 输入

```
5 1 4
1 2
1 3
2 4
2 5```

### 输出

```
12```

# 题解

## 作者：abruce (赞：8)

目前已改正为 $O(n^2)$，数据有可能之后会加强。

在正解中，我们先求出 $f_{u,k}$ 表示 $u$ 子树内进行了 $k$ 次操作的方案，树形背包即可，这部分 $O(n^2)$。同时我们也解决了 $k=1$ 或 $x=1$。  
考虑到钦定 $x$ 操作位置会影响其所有祖先选择，可以想到把祖先和他们的其它子树分开，但这样具有后效性（因为难以保证 $u$ 的子树的操作都在 $u$ 之前），所以我们考虑从根进行二次 dp。  
首先，我们把 $1$ 到 $x$ 这条链称为“茎”，和题目描述一样。  
设 $g_{u,k}$ 为当前茎从根选到了 $u$，剩余 $k$ 操作给茎 $u$ 后面的点留着，**这些操作有相对顺序但并未被实际放在操作序列的某一个位置上**。最终答案就是 $g_{x,k-1}$ （强制钦定到达 $x$ 时 $k$ 这个位置 dp 值不能拷贝过来即可）。  
考虑转移，当从 $fa$ 转移到 $u$ 时，我们先考虑 $u$ 选不选。如果不选，直接拷贝，否则设它和父亲之间填了 $p$ 个操作，从 $g_{fa,k}$ 转移过来的话，那么操作序列就必须按顺序填 $fa$ 给他留的 $p$ 个操作。所以转移到 $g_{u,k-p}$，可以通过一个前缀和优化做到单次 $O(n)$，总共 $O(n^2)$。  
接下来我们考虑把 $u$ 不在茎上的子树的操作填进去，不难发现这些操作都是给后面留的，于是背包一下即可。复杂度分析可以看做一棵以 $x$ 为根的树做树形背包，复杂度 $O(n^2)$。  
综上，我们在 $O(n^2)$ 的时间通过了本题。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x*f;
}
namespace tokidosaya {
    const int maxn=505,mod=1e9+7;
    struct edge {
        int next,to;
    } e[maxn*2];
    int h[maxn],cnt,n,k,X,d[maxn],ff[maxn],siz[maxn],now,zc[maxn],o;
    ll f[maxn][maxn],ans,fac[maxn],inv[maxn],g[2][maxn],w[maxn];
    void addedge(int x,int y) {
        e[++cnt].next=h[x],e[cnt].to=y,h[x]=cnt;
    }
    ll qpow(ll x,int y) {
        ll w=1;
        while(y) {
            if(y&1)w=w*x%mod;
            x=x*x%mod,y>>=1;
        }
        return w;
    }
    ll C(int x,int y) {
        if(y>x||y<0)return 0;
        return fac[x]*inv[x-y]%mod*inv[y]%mod;
    }
    void dfs(int u,int fa) {
        ff[u]=fa,f[u][0]=1;
        for(int i=h[u]; i; i=e[i].next) {
            int v=e[i].to;
            if(v==fa)continue;
            dfs(v,u);
            for(int j=siz[u]; j>=0; j--)
                for(int k=siz[v]; k; k--)f[u][j+k]=(f[u][j+k]+f[u][j]*f[v][k]%mod*C(j+k,k))%mod;
            siz[u]+=siz[v];
        }
        for(int i=siz[u]; i>=0; i--)f[u][i+1]=(f[u][i+1]+f[u][i])%mod;
        siz[u]++;
    }
    int getw(int u) {
        int nc=0;
        memset(w,0,sizeof(w)),w[0]=1;
        for(int i=h[u]; i; i=e[i].next) {
            int v=e[i].to;
            if(d[v])continue;
            for(int j=nc; j>=0; j--)
                for(int k=siz[v]; k; k--)w[j+k]=(w[j+k]+w[j]*f[v][k]%mod*C(j+k,k))%mod;
            nc+=siz[v];
        }
        return nc;
    }//这个相当于把不在茎上的子树合并进去
    int main() {
        int x,y;
        n=read(),k=read(),X=read(),fac[0]=1;
        for(int i=1; i<=n; i++)fac[i]=fac[i-1]*i%mod;
        inv[n]=qpow(fac[n],mod-2);
        for(int i=n; i; i--)inv[i-1]=inv[i]*i%mod;
        for(int i=1; i<n; i++) {
            x=read(),y=read();
            addedge(x,y),addedge(y,x);
        }
        dfs(1,0),x=X;
        while(x)d[x]=1,zc[++o]=x,x=ff[x];
        reverse(zc+1,zc+o+1),getw(1);
        for(int i=0; i<n; i++)g[1][i]=w[i];
        for(int i=2; i<=o; i++) {
            int now=i&1,lst=now^1,u=zc[i],nc=getw(u);
            memcpy(g[now],g[lst],sizeof(g[now]));
            ll sum=0;
            for(int j=n-1; j>=0; j--) {
                sum=(sum+g[now][j])%mod;
                if(i==o)g[now][j]=0;
                g[now][j]=(g[now][j]+sum)%mod;
            }
            for(int j=n-1; j>=0; j--)
                if(g[lst][j])for(int k=nc; k; k--)g[now][j+k]=(g[now][j+k]+g[now][j]*w[k]%mod*C(j+k,k))%mod;
        }
        printf("%lld",g[o&1][k-1]);
        return 0;
    }
}
int main() {
    return tokidosaya::main();
}

```

---

## 作者：Felix72 (赞：4)

这个题的难点在于钦定第 $k$ 次删除特定点。考虑到这个 $k$ 的限制，我们或许就会想到把操作分为 $k$ 前面和 $k$ 后面两类。如果这样背包就会变为多维的，将难以优化。

换个思路，使用延迟钦定的方法，先不管一个点做的操作是在那一步，而是用组合数的思想把他们插入操作序列，这样转移将变得方便。而对于茎上的点需要做点特殊处理：

- 如果这个点不操作，那么操作序列无需做任何变化；
- 如果这个点操作，那么相当于先在操作序列上插入一个点，再连同这个点一起删掉后面的部分。这是因为它的后代操作时间一定早于它。
- 注意，根节点和 $x$ 必须操作。

这类插入思想（或者叫延迟钦定）常用于对排列计数、连续段 DP、$\operatorname{mex}$ 相关计数等等。

这样，通过设 $f_i$ 表示当前操作序列长度为 $i$ 的方案数，我们可以如上方法 $O(n^2)$ 转移。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 510, mod = 1e9 + 7;
long long fac[N], inv[N];
inline long long C(int n, int m)
{
	if(n < 0 || n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return res;
}
inline void init_math()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 500; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[500] = qpow(fac[500], mod - 2);
	for(int i = 499; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int n, m, k; vector < int > tr[N];
long long f[N], g[N][N]; int fa[N], siz[N], son[N];
inline bool init(int now, int prt)
{
	bool flag = (now == k);
	fa[now] = prt; g[now][0] = 1;
	for(int to : tr[now])
	{
		if(to == prt) continue;
		if(init(to, now)) son[now] = to, flag = true;
		long long tmp[N] = {0};
		for(int n_sz = 0; n_sz <= siz[now]; ++n_sz)
			for(int t_sz = 0; t_sz <= siz[to]; ++t_sz)
				tmp[n_sz + t_sz] = (tmp[n_sz + t_sz] + g[now][n_sz] * g[to][t_sz] % mod * C(n_sz + t_sz, n_sz)) % mod;
		siz[now] += siz[to];
		for(int i = 0; i <= siz[now]; ++i) g[now][i] = tmp[i];
	}
	++siz[now];
	for(int i = siz[now]; i >= 1; --i) g[now][i] = (g[now][i] + g[now][i - 1]) % mod;
	return flag;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init_math(); cin >> n >> m >> k;
	for(int i = 1, x, y; i < n; ++i)
	{
		cin >> x >> y;
		tr[x].push_back(y);
		tr[y].push_back(x);
	}
	init(1, 0);
	int p = 1, len = 0; f[0] = 1;
	while(p)
	{
		long long tmp[N] = {0}; ++len;
		for(int i = 0; i <= len; ++i) tmp[i] = f[i] % mod;
		for(int i = len - 1; i >= 0; --i) tmp[i] = (tmp[i] + tmp[i + 1]) % mod;
//		cerr << p << " tmp : "; for(int i = 0; i <= len; ++i) cerr << tmp[i] << " "; cerr << '\n';
		for(int i = 0; i <= len; ++i) f[i] = (f[i] * (p != 1 && p != k) + tmp[i]) % mod;
//		cerr << p << " current : "; for(int i = 0; i <= len; ++i) cerr << f[i] << " "; cerr << '\n';
		for(int to : tr[p])
		{
			if(to == fa[p] || to == son[p]) continue;
			long long tmp[N] = {0};
			for(int n_sz = 0; n_sz <= len; ++n_sz)
				for(int t_sz = 0; t_sz <= siz[to]; ++t_sz)
					tmp[n_sz + t_sz] = (tmp[n_sz + t_sz] + f[n_sz] * g[to][t_sz] % mod * C(n_sz + t_sz, n_sz)) % mod;
			len += siz[to];
			for(int i = 0; i <= len; ++i) f[i] = tmp[i];
		}
//		cerr << p << " final : "; for(int i = 0; i <= len; ++i) cerr << f[i] << " "; cerr << '\n';
		p = son[p];
	}
	cout << f[m - 1] << '\n';
	return 0;
}
/*

*/
```

---

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8935)
## 题意
你有一棵 $n$ 个点的根节点为 $1$ 的有根树，现在你要对这棵树进行剪枝，每次你可以选择一个还未被剪掉的节点 $u$ 进行操作，然后剪掉 $u$ 的子树所有点（包括 $u$）。当且仅当你剪掉 $1$ 时，操作停止。 

你需要在恰好第 $k$ 次剪枝时对 $x$ 进行操作，求有多少种不同的操作序列，对 $10^9+7$ 取模。

$1\le k\le n\le 500$。
## 思路
考虑先算 $f_{u,i}$ 表示 $u$ 子树内进行 $i$ 次操作，不必须删完的方案数。先得到不考虑 $u$ 的方案数，转移为 $f_{u,0}=1$，$\displaystyle\forall t\in \text{sons}(u),f_{u,i}f_{t,j}\binom{i+j}{j}\to f_{u,i+j}$。再考虑 $u$，$f_{u,i}\gets f_{u,i}+f_{u,i-1}$。

令 $x$ 与其祖先组成的点集为 $S$，从 $1$ 开始向 $x$ 倒序 DP。我们定义 $g_{u,i}$ 表示考虑到 $S$ 中 $u$ 及其所有祖先，我们已经钦定了这些点的不在 $S$ 中的子树的**在 $u$ 之前**的 $i$ 个操作。这些操作有相对顺序，但还未被放在操作序列中。

我们令 $h_{u,i}$ 表示 $u$ 不在 $S$ 内的子树进行 $i$ 次操作的方案数。$h_{u,0}=1$，$\displaystyle\forall t\in \text{sons}(u)\text{ and }t\notin S,h_{u,i}f_{t,j}\binom{i+j}{j}\to h_{u,i+j}$。

考虑一次转移，当 $u$ 不被操作时，$g_{u,i}=g_{fa_u,i}$。注意 $x$ 不能不被操作。当 $u$ 被放在 $p$ 位置时，$g_{fa_u,p+k}$ 都可以转移到 $g_{u,p}$。再将 $u$ 不在 $S$ 中的子树的操作加入到 $j$ 中：$\displaystyle g_{x,i}h_{x,l}\binom{i+l}{l}\to g_{x,i+l}$。

最终的答案为 $g_{x,k-1}$。

使用后缀和优化，时间复杂度为 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=500+10,mod=1e9+7;
int n,k,p,fac[N],ifac[N],cnt,head[N];
struct Edge{
	int to,nxt;
}a[N<<1];
inline void add(int u,int v){
	cnt++;
	a[cnt].to=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y/=2; 
	}
	return res;
}
inline void Prefix(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i;i--)
		ifac[i-1]=1ll*ifac[i]*i%mod;
}
inline int C(int n,int m){
	return n<m?0:1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int f[N][N],g[2][N*2],pr[N],tmp[N],fr[N],siz[N],ans;
bool fl[N];
inline void dfs(int x,int fa){
	f[x][0]=1,fr[x]=fa;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		dfs(t,x);
		for(int j=siz[x];j>=0;j--)
			for(int k=siz[t];k>=1;k--)
				f[x][j+k]=(f[x][j+k]+1ll*f[x][j]*f[t][k]%mod*C(j+k,k))%mod;
		siz[x]+=siz[t];
	}
	for(int i=siz[x];i>=0;i--)
		f[x][i+1]=(f[x][i+1]+f[x][i])%mod; 
	siz[x]++;
}
inline void oth(int x){//这个节点其它子树 i 次操作的方案数 
	int s=0;
	tmp[0]=1;
	for(int i=1;i<=n;i++)
		tmp[i]=0;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fr[x]||fl[t]) continue;
		for(int j=s;j>=0;j--)
			for(int k=siz[t];k>=1;k--)
				tmp[j+k]=(tmp[j+k]+1ll*tmp[j]*f[t][k]%mod*C(j+k,k))%mod;
		s+=siz[t];
	}
}
vector<int>s;
int main(){
	n=read(),k=read(),p=read();
	Prefix(n);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	int t=p;
	while(t){
		s.push_back(t);
		fl[t]=1,t=fr[t];
	}
	reverse(s.begin(),s.end());
	oth(s[0]);
	int l=s.size();
	for(int j=0;j<=n;j++)
		g[0][j]=tmp[j];
	for(int i=1;i<s.size();i++){
		int c=i&1;
		oth(s[i]);
		int sz=siz[s[i]];
		if(i!=l-1) sz-=siz[s[i+1]];
		for(int t=0;t<=n;t++)
			g[c][t]=g[!c][t]*(i!=l-1);
		for(int t=n;t>=0;t--)
			pr[t]=(pr[t+1]+g[!c][t])%mod;
		for(int d=n;d>=0;d--)
			g[c][d]=(g[c][d]+pr[d])%mod;
		for(int j=n-1;j>=0;j--)
			for(int d=sz;d;d--)
				g[c][j+d]=(g[c][j+d]+1ll*g[c][j]*tmp[d]%mod*C(j+d,d))%mod;
	}
	write(g[l-1&1][k-1]);
	flush();
}
```

---

## 作者：Officer_Xia_ZhuRen (赞：0)

题目的做法就和名字一样，良心！

称**点 $1$ 到点 $X$ 的路径为茎**，考虑先求出 $g_{i,j}$ 代表以 $i$ 为根，选取子树中非茎点的方案数。

要求 $X$ 在第 $k$ 次被转移，所以我们从上向下设 $f_{i,j}$ 为到节点 $i$，有 $j$ 个**非茎节点**在 $i$ 前面删除的方案数。

由于茎上节点的删除顺序是一定的，为了统计答案，依然采用钦定的方法：直接钦定 $i$ 前面有多少个，转移自然是直接统计父亲状态的后缀和，注意不转移的话直接继承。

茎上 DP 大约是这样的：

![](https://img.picui.cn/free/2025/02/25/67bdbaab8f6d0.png)

然后统计自己答案的时候再对非茎节点之间做个背包即可。

复杂度即树上背包，$\mathcal{O}(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll1;
const ll1 mod=1e9+7;
const int N=1005;
struct edge{
	int u,v,nxt;
}E[N*2];
int head[N],tote=0;
void ae(int u,int v){
	E[++tote]=(edge){u,v,head[u]};
	head[u]=tote;
}
ll1 C[N][N];
int n,X,K;
int sz[N];
ll1 g[N][N];
bool onx[N];
bool inx[N];
ll1 f[N][N];
int stk[N],top=0;
bool dfs1(int u,int Fa,bool Op){
	if(u==X)Op=onx[u]=1;
	inx[u]=Op;g[u][0]=1;
	for(int e=head[u],v;e;e=E[e].nxt){
		v=E[e].v;if(v==Fa)continue;
		onx[u]|=dfs1(v,u,Op);
		if(!onx[v]){//非茎，考虑对g进行累计
			for(int i=sz[u];i>=0;i--){
				for(int j=sz[v];j>0;j--){
					(g[u][i+j]+=
					g[u][i]*g[v][j]%mod*C[i+j][j]%mod)%=mod;
				}
			}
			sz[u]+=sz[v];
		}
	}
	sz[u]++;
	for(int i=sz[u];i>=0;i--){
		if(i&&!onx[u])(g[u][i]+=g[u][i-1])%=mod;
	}
	if(u==X)//清空>k-1的部分
		for(int i=K;i<=sz[u];i++)g[u][i]=0;
	if(onx[u]){
		stk[++top]=u;
	}
	return onx[u];
}
//f[u][j]:钦定了在 u 之前的 j 次非茎操作
//考虑这个怎么搞
int sufsm[N];
void work(){
	dfs1(1,0,0);
	for(int i=0;i<=n;i++)f[1][i]=g[1][i];
	top--;
	int fa=1;
	while(top){
		int u=stk[top--];
		for(int i=n;i>=0;i--)
			sufsm[i]=(sufsm[i+1]+f[fa][i])%mod;
		for(int i=0;i<=n;i++)
			f[u][i]=(sufsm[i]+((u==X)?0:f[fa][i]))%mod;
		for(int j=n-1;j>=0;j--)
		for(int i=sz[u];i;i--)
			(f[u][i+j]+=f[u][j]*g[u][i]%mod*C[i+j][i]%mod)%=mod;
		fa=u;
	}
	ll1 ans=f[X][K-1];
	printf("%lld\n",ans);
}
void init(){
	C[0][0]=1;
	for(int i=1;i<=1000;i++){
		C[i][0]=1;
		for(int j=1;j<=1000;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	scanf("%d%d%d",&n,&K,&X);
	int u,v;
	for(int i=1;i<n;i++)
		scanf("%d%d",&u,&v),ae(u,v),ae(v,u);
}
int main(){
	// freopen("1.in","r",stdin);
	init();
	work();
	return 0;
}
```

---

