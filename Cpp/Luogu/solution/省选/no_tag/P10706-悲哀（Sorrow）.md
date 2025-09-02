# 悲哀（Sorrow）

## 题目背景

>$$你是天使，$$
>
>$$于光与圣歌中降临。$$
>
>$$我是恶魔，$$
>
>$$从血与污泥中爬出。$$
>
>$$我想拥抱你，$$
>
>$$但是害怕血，$$
>
>$$染红你洁白的羽翼。$$

## 题目描述

给出一棵有 $n$ 个节点且以 $1$ 为根节点的树，每个节点有两个权值 $a_i,b_i$（$1\le i\le n$）。$a_i$ 已经给出，$b_i$ 初始为 $0$。

现在对于每一对节点 $(u,v)$（$1\le u<v\le n$），设 $x=\operatorname{LCA}(u,v)$，如果 $\gcd(a_u,a_v)>1$ 那么 $b_x\gets b_x+a_u\times a_v$，否则不做任何操作。

对于每个 $1\le i\le n$ 求出 $b_i\bmod998244353$。

## 说明/提示

#### 【样例解释】

![](https://cdn.luogu.com.cn/upload/image_hosting/bti6350r.png)

建出的树如图。

有以下贡献：

- 对 $1$ 号节点：

$(3,4)$ 贡献 $4$。

$(3,5)$ 贡献 $4$。

$(3,7)$ 贡献 $144$。

$(3,8)$ 贡献 $48$。

$(1,6)$ 贡献 $9$。

$(1,7)$ 贡献 $216$。

$(1,8)$ 贡献 $72$。

$(6,7)$ 贡献 $216$。

$(6,8)$ 贡献 $72$。

总共 $785$。

- 对 $4$ 号节点：

$(4,5)$ 贡献 $4$。

$(4,7)$ 贡献 $144$。

$(4,8)$ 贡献 $48$。

$(5,8)$ 贡献 $48$。

$(7,8)$ 贡献 $1728$。

总共 $1972$。

- 对 $5$ 号节点：

$(5,7)$ 贡献 $144$。

总共 $144$。

其他节点显然都为 $0$。

#### 【数据范围】

| subtask 编号 | $n$ | $a_i$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $100$ | $\le 1000$ | $-$ | $5$ |
| $1$ | $2000$ | $\le 10^5$ | $-$ | $10$ |
| $2$ | $10^5$ | $\le 5 \times 10^5$ | $A$ | $25$ |
| $3$ | $2 \times  10^5$ | $\le 5 \times 10^5$ | $B$ | $30$ |
| $4$ | $2 \times  10^5$ | $\le 5 \times 10^5$ | $-$ | $30$ |

特殊性质 $A$：保证所有的 $a_i$ 随机生成。

特殊性质 $B$：保证树的形态是一棵完全二叉树。

对于 $100\%$ 的数据，$1\le n\le2\times10^5$，$1\le a_i\le5\times10^5$。

**特别提醒：本题使用 subtask 捆绑测试，只有通过一个子任务的全部测试点才能获得此子任务的分数。**

## 样例 #1

### 输入

```
8
3 7 2 2 2 3 72 24 
1 2
1 3
1 4
4 5
2 6
5 7
4 8
```

### 输出

```
785
0
0
1972
144
0
0
0```

## 样例 #2

### 输入

```
15
73 83 31 9514 1189 43 79 2 2 1798 5063 2 5 2573 53 
1 2
2 3
1 4
4 5
1 6
3 7
5 8
5 9
6 10
7 11
10 12
9 13
7 14
13 15
```

### 输出

```
23952214
633788
79763
38056
4
0
13027099
0
0
3596
0
0
0
0
0```

# 题解

## 作者：yywlp (赞：2)

## 题解

一句话总结：质因数分解后建模，树上启发式合并。

先考虑不在树上该如何解决。

假设现在数字分为两组 $S,T$（看成是两颗子树中的数）。

我们对其中的每个数字质因数分解，并且每个质因子只保留一位，具体地，假设一个数为 

$$c_i=p_1^{a_1}\times p_2^{a_2}\times \dots \times p_n^{a_n}$$

那么我们把它变成 

$$c_i'=p_1\times p_2\times \dots \times p_n$$

对这个 $c_i$ 我们向 $c_i'$ 的**所有因数**连边，可以发现，因为 

$$2\times 3\times 5\times 7\times 11\times 13\times 17=510510>500000$$ 

所以一个数在变形后最多只有 $6$ 个质因子，那么它的因数个数最大就为 

$$\binom{6}{1}+\binom{6}{2}+\dots+\binom{6}{6}=63$$

所以一个数**最多**产生 $63$ 条边。

处理完所有数后发现被连了边的数的因子中**没有质数的平方**。我们遍历这些数。对于一个数 $x$，设 $T$ 中向 $x$ 连边的数的集合为 $Q$，$S$ 中向 $x$ 连边的数的集合为 $P$。

如果 $x$ 有**奇数个**质因子就会产生贡献：

$$\sum_{x\in Q}\sum_{y\in P}x\times y$$

如果 $x$ 有**偶数个**质因子就会产生贡献：

$$-\sum_{x\in Q}\sum_{y\in P}x\times y$$

这两个求和实际上是可以写成这样的：

$$\sum_{x\in Q}x\sum_{y\in P}y$$

那么求个和乘起来即可。

为什么这样做呢？我们考虑两个数 $a,b$，先对它们做最开始的处理变成 $a',b'$。不难发现，如果 $\gcd(a,b)>1$ 那么 $\gcd(a',b')>1$，所以我们现在只需要判断 $a',b'$ 的关系，按照上面的式子，在 

$$p_1,p_2\dots p_n$$

的地方 $a',b'$ 都会被统计进答案，这明显算多了，但是在 

$$p_1p_2,p_1p_3\dots p_np_{n-1}$$

的地方 $a',b'$ 又产生了负贡献，到这里已经可以发现这个其实就是**容斥**了。

会算重的质因子 $a',b'$ 一定都有，那么**这些质因子组合出来的数**同样也是 $a',b'$ 的因子，所以按照这样算完刚好满足容斥的式子，也即每一对数刚好被贡献了一次。时间复杂度 $ \Theta (n)$ 有一个 $63$ 的常数。

放在树上只需要加一个启发式合并，在加一个数的时候先计算答案再把这个数要连的边加上即可，多一个 $\log$。

总复杂度 $ \Theta (n\log{n})$ 有一个 $63$ 的常数，不过因为质因子分解几乎卡不满，所以会稍微快一点点，勉强通过。

但是这题如果直接按因数建虚树也能过，只是常数会大，为了尽量卡这种做法我就把时间调的比较小了QAQ。

不过有人写 $\Theta(n)$ 的虚树加上卡常依然能过，只能说我这道题出的真的不好，考虑的太少了QAQ。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int M=2e5+10,N=5e5+10,mod=998244353;
int n,a[M];
vector<int>G[M];
int p[N],isp[N],fr[N],mu[N];
vector<int>r1[N],rc[N];
LL pb[N],pc[N][20];
LL b[M],c[M];
int sz[M],son[M];
bool pd[N];
void dfs(int k,int m,int last,int sum,vector<int>&ps,vector<int>&st){
	if(m-k>(int)st.size()-last)return;
	if(k==m){
		ps.push_back(sum);
		return;
	}
	for(int i=last;i<(int)st.size();i++){
		dfs(k+1,m,i+1,sum*st[i],ps,st);
	}
}
void init(){
	isp[1]=mu[1]=1;
	for(int i=2;i<N;i++){
		if(!isp[i])p[++p[0]]=i,fr[i]=i,mu[i]=-1;
		for(int j=1;j<=p[0]&&i*p[j]<N;j++){
			isp[i*p[j]]=true;
			fr[i*p[j]]=p[j];
			if(i%p[j]==0)break;
			mu[i*p[j]]=-mu[i];
		}
		int s=i;
		if(pd[s]){
			while(s>1){
				int np=fr[s];
				while(fr[s]==np)s/=np;
				r1[i].push_back(np);
			}
			for(int j=1;j<=(int)r1[i].size();j++)dfs(0,j,0,1,rc[i],r1[i]);
		}
	}
}
void init(int u,int f){
	sz[u]=1;
	for(int v:G[u]){
		if(v==f)continue;
		init(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void dfs_count(int u,int f,int fr){
	for(int v:rc[a[u]])b[fr]-=mu[v]*pb[v]%mod*a[u]%mod,b[fr]%=mod;
	for(int v:G[u]){
		if(v==f)continue;
		dfs_count(v,u,fr);
	}
}
void dfs_add(int u,int f){
	for(int v:rc[a[u]])pb[v]+=a[u];
	for(int v:G[u]){
		if(v==f)continue;
		dfs_add(v,u);
	}
}
void dfs_del(int u,int f){
	for(int v:rc[a[u]])pb[v]-=a[u];
	for(int v:G[u]){
		if(v==f)continue;
		dfs_del(v,u);
	}
}
void dfs(int u,int f){
	for(int v:G[u]){
		if(v==f||v==son[u])continue;
		dfs(v,u);
		dfs_del(v,u);
	}
	if(son[u]){
		dfs(son[u],u);
		for(int v:rc[a[u]]){
			b[u]-=mu[v]*pb[v]%mod*a[u]%mod;
			b[u]%=mod;
			pb[v]+=a[u];
		}
		for(int v:G[u]){
			if(v==f||v==son[u])continue;
			dfs_count(v,u,u);
			dfs_add(v,u);
		}
	}else for(int v:rc[a[u]])pb[v]+=a[u];
}
int read() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-') w = -1;       
		ch = getchar();              
	}
	while (ch >= '0' && ch <= '9') {  
		x = x * 10 + (ch - '0'); 
		ch = getchar();  
	}
	return x * w;  
}
void write(LL x) {
	if (x < 0) {  
		x = -x;
		putchar('-');
	}
	if (x > 9) write(x / 10); 
	putchar(x % 10 + '0');  
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)a[i]=read(),pd[a[i]]=true;
	init();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	init(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++)write((b[i]+mod)%mod),putchar('\n');
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：1)

~~非常好卡常，使我破防。~~

注意到树有根，考虑树上启发式合并。

考虑质因数分解以后将贡献放到对应的质因数上进行计算，此时发现会算重。如果有两个数的最大公因数不为 $1$，会导致它们的贡献被统计若干次。

怎么去处理呢？

我们可以改为将贡献放到因数 $d$ 上，然后进行容斥，容易想到容斥项系数为 $(-1)^{\pi(d)}$，其中 $\pi(d)$ 表示 $d$ 的质因数个数。紧接着，我们发现对于 $a_i=4$ 没有产生贡献。我们让每一个数的分解形式的指数都为 $1$，就解决了这个问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+3,M=5e5+3,P=998244353;
inline int ad(int x,ll y){return x+y>=P?x+y-P:x+y;}
inline int dt(int x,ll y){return x-y<0?x-y+P:x-y;}
inline int read(){
    int x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
vector<int>e[N],d[N];
int sz[N],son[N],cnt[M],p[M],dfn[N],id[N],tmp[M],a[N],b[N];
int n,tot,tim,res;
bool vis[M];
void add(int u,int v){
    e[u].push_back(v);
    e[v].push_back(u);
}
void dfs1(int x,int f){
    sz[x]=1;dfn[x]=++tim;id[tim]=x;
    for(auto y:e[x])if(y^f){
        dfs1(y,x);
        sz[x]+=sz[y];
        if(sz[son[x]]<sz[y])son[x]=y;
    }
}
void clear(int x,int f){
    int len=dfn[x]+sz[x]-1;
    for(int k=dfn[x];k<=len;++k){
        int x=id[k];
        for(auto y:d[x])tmp[y]=dt(tmp[y],a[x]);
    }
}
void ins1(int x,int f){
    int len=dfn[x]+sz[x]-1;
    for(int k=dfn[x];k<=len;++k){
        int x=id[k];
        for(auto y:d[x])
        if(cnt[y]&1)res=ad(res,1ll*tmp[y]*a[x]%P);
        else res=dt(res,1ll*tmp[y]*a[x]%P);
    }
}
void ins2(int x,int f){
    int len=dfn[x]+sz[x]-1;
    for(int k=dfn[x];k<=len;++k){
        int x=id[k];
        for(auto y:d[x])tmp[y]=ad(tmp[y],a[x]);
    }
}
void solve(int x,int f){
    res=0;
    for(auto y:e[x])
        if(y!=f&&y!=son[x])
            solve(y,x),clear(y,x);
    if(son[x])solve(son[x],x);
    res=0;
    for(auto y:e[x])
        if(y!=f&&y!=son[x])
            ins1(y,x),ins2(y,x);
    for(auto y:d[x]){
        if(cnt[y]&1)res=ad(res,1ll*tmp[y]*a[x]%P);
        else res=dt(res,1ll*tmp[y]*a[x]%P);
        tmp[y]=ad(tmp[y],a[x]);
    }
    b[x]=res;
}
int main(){
    int u,v,w,x,y,z;
    for(int i=2;i<M;++i){
        if(!vis[i])p[++tot]=i;
        for(int j=1;j<=tot&&p[j]*i<M;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
    for(int i=1;i<M;++i){
        int k=i;
        for(int j=1;p[j]*p[j]<=k;++j)
            while(k%p[j]==0)++cnt[i],k/=p[j];
        if(k>1)++cnt[i];
    }
    n=read();
    for(int i=1;i<=n;++i){
        a[i]=read();int k=a[i];vector<int>l;
        for(int j=1;p[j]*p[j]<=k;++j)
            if(k%p[j]==0){
                l.push_back(p[j]);
                while(k%p[j]==0)k/=p[j];
            }
        if(k>1)l.push_back(k);
        int len=l.size();
        for(int s=1;s<1<<len;++s){
            int k=1;
            for(int i=0;i<len;++i)
                if(s&(1<<i))k*=l[i];
            d[i].push_back(k);
        }
    }
    for(int i=1;i<n;++i)add(read(),read());
    dfs1(1,0);solve(1,0);
    for(int i=1;i<=n;++i)printf("%d\n",b[i]);
    return 0;
}
```

---

## 作者：冷却心 (赞：0)

联考 NOIP T4，由于莫反细节写错导致 $100 \to 0$，赫赫，原题 600ms 神人卡常，联考时限放宽数据范围缩小放过虚树做法还是太有素质了。值得一提的是该假做法成功通过你谷非 Subtask 3 随机数据以外的所有数据，/bangbangt。

先把 LCA 限制去掉，我们考虑求出 $f_p$ 表示满足条件的 $u,v$ 在 $p$ 子树内的 $a_u \times a_v$ 的总和，那么 $b_p=f_p-\sum_{q \in \text{son}(p)} f_q$。

然后用莫反把 $\gcd$ 限制去掉。要求不互质数对乘积和，转而考虑求互质数对乘积和。我们考虑一个弱化叫做给定一个序列 $\{a_n\}$ 求出其中所有互质数对乘积和。显然值域上开个桶，接着莫反直接做。具体而言，记 $m$ 为值域，$s_i$ 表示值为 $i$ 的数的总和，那么答案为 $\displaystyle\sum_{i=1}^m s_i \sum_{j=1}^m s_j [\gcd(i,j)=1]$。莫反后变成 $\displaystyle \sum_{i=1}^m s_i \sum_{k\mid i}\mu(k) \sum_{k \mid j} s_j$，于是我们先求出 $g_k=\sum_{k|i} s_i$，然后对每个 $i$ 枚举因数莫反。把上述过程放到树上就是对每颗子树做，需要支持动态加入一个数求莫反答案，和上述过程本质相同，然后用 dsu on tree 维护求出 $f_p$ 做到 $\mathcal O(d(m)n\log n)$。堂堂倒闭 TLE。一个 naive 的优化是注意到如果 $\mu(i)=0$ 那么他对答案毫无贡献.所以因数只枚举 $\mu(i)$ 非零的部分，可以一开始用调和级数复杂度预处理因数 `vector`。$\mu(i)$ 非零的因数个数即为每个质因子只出现 $0/1$ 次的因数个数，至多 $2^{\omega(m)}=64$ 次，复杂度 $\mathcal O(n2^{\omega(m)}\log n)$，轻微卡常就可通过。

卡常小技巧：处理 $\mu(i)$ 非零的因数时不考虑不在原序列内出现过的数，然后轻松通过。

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define uint unsigned int
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int M = 5e5 + 10;
const uint MOD = 998244353;
int n, m = 5e5, A[N]; vector<int> G[N];
int prime[M], ptot; uint mu[M]; bool is[M], vis[M];
vector<int> D[M]; int cnt[M];
void Sieve() {
	mu[1] = 1;
	for (int i = 2; i <= m; i ++) {
		if (!is[i]) { mu[i] = MOD - 1, prime[++ ptot] = i; }
		for (int j = 1; j <= ptot && i * prime[j] <= m; j ++) {
			is[i * prime[j]] = 1, mu[i * prime[j]] = (MOD - mu[i]) % MOD;
			if (i % prime[j] == 0) { mu[i * prime[j]] = 0; break; }
		}
	} 
	return ;
}

uint cur = 0, sum[M], Ans[N];
int sz[N], hson[N], dfn[N], R[N], dfncnt, inv[N]; uint W[N];
void DFS1(int u, int f) {
	sz[u] = 1; dfn[u] = R[u] = ++ dfncnt; inv[dfncnt] = u; W[u] = A[u];
	for (int v : G[u]) if (v != f) {
		DFS1(v, u); if (sz[v] > sz[hson[u]]) hson[u] = v;
		R[u] = R[v]; sz[u] += sz[v]; 
		Ans[u] = (Ans[u] + Ans[v] + 1ull * W[u] * W[v]) % MOD;
		W[u] = (W[u] + W[v]) % MOD;
	} return ;
}
void add(int u, uint k) {
	for (int d : D[u]) {
		cur = (cur + 1ull * mu[d] * sum[d] % MOD * k % MOD) % MOD;
		sum[d] = (sum[d] + k) % MOD; 
	} return ;
}
void del(int u, uint k) {
	for (int d : D[u]) {
		sum[d] = (sum[d] + MOD - k) % MOD; 
		cur = (cur + 1ull * mu[d] * sum[d] % MOD * (MOD - k) % MOD) % MOD;
	} return ;
}
void DFS2(int u, int f, bool kp) {
	for (int v : G[u]) if (v != f && v != hson[u]) DFS2(v, u, false);
	if (hson[u]) { DFS2(hson[u], u, true); }
	for (int v : G[u]) if (v != f && v != hson[u]) 
		for (int i = dfn[v]; i <= R[v]; i ++) add(A[inv[i]], A[inv[i]]);
	add(A[u], A[u]); Ans[u] = (Ans[u] + MOD - cur) % MOD;
	if (!kp) for (int i = dfn[u]; i <= R[u]; i ++) del(A[inv[i]], A[inv[i]]);
}


#define getchar getchar_unlocked
#define putchar putchar_unlocked
int read() {
	int x = 0; char c = getchar();
	for (; !isdigit(c); c = getchar());
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x;
}
void write(int x) {
	if (x >= 10) write(x / 10);
	putchar(x % 10 + 48);
}

int main() {
	freopen(".in", "r", stdin); freopen(".ans", "w", stdout); 
	n = read(); Sieve();
	for (int i = 1; i <= n; i ++) A[i] = read(), vis[A[i]] = 1;
	for (int i = 1, u, v; i < n; i ++) {
		u = read(), v = read(); G[u].push_back(v); G[v].push_back(u);
	}
	for (int i = 1; i <= m; i ++) if (mu[i] != 0)
		for (int j = i; j <= m; j += i) if (vis[j]) cnt[j] ++;
	for (int i = 1; i <= m; i ++) if (vis[i]) D[i].resize(cnt[i]), cnt[i] = 0;
	for (int i = 1; i <= m; i ++) if (mu[i] != 0)
		for (int j = i; j <= m; j += i) if (vis[j]) D[j][cnt[j] ++] = i;
	DFS1(1, 0); DFS2(1, 0, true);
	for (int i = 1; i <= n; i ++)
		for (int j : G[inv[i]]) if (dfn[j] > i) Ans[inv[i]] = (Ans[inv[i]] + MOD - Ans[j]) % MOD;
	for (int i = 1; i <= n; i ++) write(Ans[i]), putchar('\n');
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

## 分析
不难想到对于每个质因子分别进行计算，但是我们发现可能会重，所以需要考虑容斥。

我们发现由于 $a_i\le5\times 10^5$，所以最多有 $6$ 个不同的质因子，于是我们可以 $2^6$ 枚举这些质因子组成的不同的数，然后容斥系数就是 $(-1)^p$，$p$ 代表不同质因子个数。

然后考虑树上怎么做这些，由于我们总的新组成数的个数是 $2\times 10^5 \times 64$ 的，所以我们可以思考在每个节点上直接记录儿子有哪些数，但是直接记会超时。

所以考虑 dsu on tree，这样子我们能直接保存重儿子记录的东西，然后加入的结点个数就只有 $n\log n$ 了。

## Code
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
//#include <immintrin.h>
//#include <emmintrin.h>
#define ll long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define pii pair<int,int>
#define fi first
#define se second
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
mt19937_64 rnd(time(0));
#define rand() abs((int)rnd())
const int N=5e5+5,base=999983,Mod=998244353;
char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//int _base=1;
//inline int mol(const int x){return x-Mod*((__int128)_base*x>>64);}
//inline void Add(int &x,const int y){x=mol(x+y);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int n,a[N];
vector<int>q[N];
int d[N][64],O[N];
int prime[N],tot;bool isp[N];
int lst[N];
int cnt[N],son[N],bg[N],ed[N],idx,id[N];
int sum[N],siz[N];
void dfs1(int x,int faz){
	siz[x]=1;bg[x]=++idx;id[idx]=x;
	for(auto y:q[x]){
		if(y==faz)continue;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])son[x]=y;
	}ed[x]=idx;
}
int answer[N];
void dfs2(int x,int faz){
	for(auto y:q[x]){
		if(son[x]!=y&&y!=faz){
			dfs2(y,x);
			For(i,bg[y],ed[y]){
				int u=id[i];
				For(ss,0,O[u]-1){
					int v=d[u][ss];
					sum[v]+=Mod-a[u];
					(sum[v]>=Mod?sum[v]-=Mod:1);
				}
			}
		}
	}if(son[x]) dfs2(son[x],x);
	ll res=0;
	for(auto y:q[x]){
		if(son[x]!=y&&y!=faz){
			For(i,bg[y],ed[y]){
				int u=id[i];
				For(ss,0,O[u]-1){
					int v=d[u][ss];
					if(cnt[v]&1) (res+=1ll*sum[v]*a[u])%=Mod;
					else (res+=1ll*(Mod-sum[v])*a[u])%=Mod;
				}
			}For(i,bg[y],ed[y]){
				int u=id[i];
				For(ss,0,O[u]-1){
					int v=d[u][ss];
					sum[v]+=a[u];
					(sum[v]>=Mod?sum[v]-=Mod:1);
				}
			}
		}
	}For(ss,0,O[x]-1){
		int v=d[x][ss];
		if(cnt[v]&1) (res+=1ll*sum[v]*a[x])%=Mod;
		else (res+=1ll*(Mod-sum[v])*a[x])%=Mod;
	}For(ss,0,O[x]-1){
		int v=d[x][ss];
		sum[v]+=a[x];
		(sum[v]>=Mod?sum[v]-=Mod:1);
	}
	answer[x]=res;
}int zhi[N];
signed main(){
//	_base=((__int128)_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read();
	For(i,1,n) a[i]=read();
	isp[0]=isp[1]=1;
	For(i,2,N-5){
		if(!isp[i]) prime[++tot]=i;
		For(j,1,tot){
			if(i*prime[j]>N-5) break;
			isp[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}For(i,1,tot)For(j,1,(N-5)/prime[i])lst[j*prime[i]]=prime[i],cnt[j*prime[i]]++;
	For(i,1,n){
		int last=-1,x=a[i];int tot=0;
		while(x!=1){
			if(last!=lst[x]) zhi[++tot]=lst[x];
			last=lst[x];
			x/=lst[x];
		}For(j,1,(1<<tot)-1){
			int p=1;
			For(t,1,tot) if(j&(1<<(t-1))) p=p*zhi[t];
			d[i][O[i]++]=p;
		}
	}For(i,2,n){
		int u=read(),v=read();
		q[u].push_back(v);
		q[v].push_back(u);
	} dfs1(1,0);dfs2(1,0);
	For(i,1,n) printf("%d\n",answer[i]);
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

