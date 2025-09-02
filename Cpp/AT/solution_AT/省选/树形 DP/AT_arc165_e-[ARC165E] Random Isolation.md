# [ARC165E] Random Isolation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_e

頂点に $ 1 $ から $ N $ の番号が付いた $ N $ 頂点からなる木があります。 $ i $ 番目の辺は頂点 $ A_i,B_i $ を結びます。

グラフの連結成分が含む頂点の数がそれぞれ $ K $ 以下になるまで以下の操作を行い続けます。

- $ N $ 個の頂点のうち、$ K+1 $ 個以上の頂点を含む連結成分に属する頂点を $ 1 $ つ一様ランダムに選ぶ。選んだ頂点を端点とする辺をすべて削除する。
 
操作を行う回数の期待値を $ \bmod\ 998244353 $ で求めてください。

 期待値 $ \text{mod\ }{998244353} $ の定義 求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。 よって、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。 この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ <\ N\ \leq\ 100 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- 与えられるグラフは木
- 入力される値はすべて整数
 
### Sample Explanation 1

例えば $ 1 $ 回目の操作で頂点 $ 2 $ が選ばれた場合、操作によって全ての辺が削除され、操作後は各連結成分が含む頂点の数はそれぞれ $ 2 $ 以下であるため操作を終了します。一方 $ 1 $ 回目の操作で頂点 $ 1 $ が選ばれた場合、操作後頂点 $ 2,3,4 $ からなる連結成分が残るため、$ 2 $ 回目の操作が行われます。 操作回数の期待値は $ \frac{7}{4} $ です。

## 样例 #1

### 输入

```
4 2
1 2
2 3
2 4```

### 输出

```
249561090```

## 样例 #2

### 输入

```
20 10
16 8
6 2
18 3
3 12
5 1
13 9
13 19
3 11
5 13
17 6
8 14
1 16
16 20
11 15
3 10
15 4
5 18
1 7
1 17```

### 输出

```
181196154```

# 题解

## 作者：樱雪喵 (赞：16)

好厉害的题，不会做。看了官方题解。

## Description

给一棵 $n$ 个节点的树和一个整数 $K$。每次操作，等概率随机选一个所在连通块大小大于 $K$ 的点，并删掉这个点和与之相连的所有边。重复操作直到图上所有连通块大小不超过 $K$，求期望操作次数，答案对 $998244353$ 取模。

$1\le K < N\le 100$。

## Solution

将题目的操作转化为：对于随机的长度为 $n$ 的排列 $p$，我们按 $p_1,p_2,\dots,p_n$ 的顺序依次考虑。若 $p_i$ 所在连通块的大小大于 $K$，那么在当前的树上删除 $p_i$；否则不进行任何操作。求有效操作的期望次数。

考虑为什么这和原问题是等价的。忽略掉所有无效的操作，则当前局面下，所有可以有效操作的点在下一步被选取的概率均相等。而对于这步无效的点显然不会后面删着删着变有效了，所以它在哪里都对期望次数没有影响。

设 $p(T)$ 表示原树的子树 $T$ 恰好在删的过程中作为完整的连通块出现的概率。根据期望的线性性，我们考虑每棵子树对答案的贡献。对于一个 $size>K$ 的子树 $T$，它一定要在 $T$ 形态下被操作一次，对答案的期望产生 $1\times p(T)$ 的贡献。而经过这次操作后，$T$ 就不再是 $T$，它变成了若干棵别的子树，这部分的贡献已经被它变成的新子树统计了。也就是说，每个 $T$ 对期望次数的贡献是 $p(T)$。答案的总期望为 $\sum\limits_{size_T>K} p(T)$。

问题瓶颈变成怎么求 $p(T)$。我们设 $size_T=n$，与 $T$ 里的点有边直接相连，且不属于 $T$ 的点有 $m$ 个。即，$T$ 向子树外有 $m$ 条直接连边。

那么根据 $T$ 独立存在的条件，我们知道：$T$ 内的 $n$ 个点都还没被操作，且与 $T$ 相连的这 $m$ 个点都被操作过了。回到一开始把操作转化成的排列，上述条件等价于：某 $m$ 个点在排列上的位置均在某 $n$ 个点前面。不难得出这个的概率为 $\dfrac{n!m!}{(n+m)!}$。

剩下的最后一个问题是如何对 $T$ 进行计数。发现 $T$ 对答案的贡献只与 $n$ 和 $m$ 的值有关，考虑基于这点合并统计 $n$ 和 $m$ 均相等的子树的数量，可以树形 DP。

令 $f_{u,i,j}$ 表示以点 $u$ 为根，点数为 $i$，且 **不包括 $u$ 的父亲** 与之相连的点数为 $j$ 的连通块个数。这么设是因为把 $u$ 的父亲也算进去，向上转移又要减掉这部分贡献很麻烦。

树形背包转移即可，式子这里不写了。时间复杂度是 $O(n^2K^2)$。

```cpp
#define int long long
const int N=105,mod=998244353;
int n,K;
int f[N][N][N];
struct edge{int nxt,to;}e[N<<1];
int head[N],cnt;
il void add(int u,int v) {e[++cnt]={head[u],v};head[u]=cnt;}
int siz[N],jc[N<<1],inv[N<<1];
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
il void init(int n)
{
    jc[0]=inv[0]=1;
    for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    inv[n]=qpow(jc[n]);
    for(int i=n-1;i;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int tmp[N][N];
void dfs(int u,int fa)
{
    f[u][1][0]=1,siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to; if(v==fa) continue;
        dfs(v,u);
        memset(tmp,0,sizeof(tmp));
        f[v][0][1]=1;
        for(int j=0;j<=siz[u];j++)
            for(int k=0;k<=siz[u];k++)
                for(int s=0;s<=siz[v];s++)
                    for(int t=0;t<=siz[v];t++)
                        tmp[j+s][k+t]=(tmp[j+s][k+t]+f[u][j][k]*f[v][s][t]%mod)%mod;
        siz[u]+=siz[v];
        for(int j=0;j<=siz[u];j++)
            for(int k=0;k<=siz[u];k++) f[u][j][k]=tmp[j][k];
    }
}
signed main()
{
    n=read(),K=read();
    init(2*n);
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=K+1;j<=siz[i];j++)
            for(int k=0;k<=siz[i];k++)
            {
                int rl=k+(i!=1);
                ans=(ans+f[i][j][k]*jc[j]%mod*jc[rl]%mod*inv[j+rl]%mod)%mod;
            }
    printf("%lld\n",ans);
    return 0;
}
```

luogu 怎么还没爬 ARC165 的题。>_<

---

## 作者：i_am_not_feyn (赞：15)

题外话：AT 里很是有几道这样的题，可以做做看。如果您像大佬 [Feyn](https://www.luogu.com.cn/user/302383) 一样板刷了 ARC 的话应该是能做到的。

考虑要求的期望相当于之前每个还可以再次操作的局面出现的概率之和（这些局面必定会贡献出一次操作）。

从树上抠出来一个大小大于 $k$ 的子树，若要在操作中出现它，则需要把与其有边的非子树点先删掉。

令子树大小为 $n$，有 $m$ 个非子树点与其相连。套路地将操作序看成一个排列，排列中有些点会操作，有些不会。

显然只有当 $m$ 个点全排在 $n$ 个点之前时，这个子树会出现。

由于其他点对该排列并不会产生影响，故只考虑这 $n+m$ 个点。

共有 $(n+m)!$ 种排列，其中有 $n!m!$ 种合法，则有 $\dfrac{n!m!}{(n+m)!}$ 的概率出现这棵子树。尽管有些排列是等价的，但是这些等价排列总的概率等于每个等价排列的概率之和，所以可以看作每个排列出现的概率相同。

剩下的就是树形 dp。令 $f(x,i,j)$ 为 $x$ 子树中选了包含 $x$ 在内的 $i$ 个点，有 $j$ 个点与之相连的方案数，背包转移一下即可，可以通过。

[code](https://atcoder.jp/contests/arc165/submissions/45702961)

---

## 作者：Feyn (赞：13)

题外话：AT 里很是有几道这样的题，可以做做看。至于题号我记不得了，如果你像大佬 [赵悦岑](https://www.luogu.com.cn/user/291248) 一样板刷了 ARC 的话应该是能做到的。

套路地把期望拆到每个点上，记 $E_x$ 表示点 $x$ 产生贡献的概率，那么答案自然是所有的 $E$ 累加起来的结果，思考这个东西应该怎么求。按照类似于 [ARC150D](https://www.luogu.com.cn/problem/AT_arc150_d) 的思想，考虑按照一个排列选点，如果选的点不合法就忽略此次操作，会发现这样是不会影响期望的。于是 $E_x$ 的含义变成了断掉所有排列中比点 $x$ 更靠前的点的连边之后，剩下的联通块大小仍然大于 $k$ 的概率，显然这个概率就是这个点产生贡献的概率。

于是就可以 DP 了。用 $f_{x,p,q}$ 表示子树 $x$ 中选择了 $p$ 个点在 $x$ 之前，并且子树内有 $q$ 个点和根在同一连通块内的方案数，转移上就是一个树形背包，在根处用得到的方案数（当然要乘上两边点内部的排列）除以总的排列数即可。可以通过。

```cpp
#include<bits/stdc++.h>
// #define feyn
#define int long long
#define ptt pair<int,int>
#define mp make_pair
using namespace std;
const int N=110;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

struct edge{
    int t,nxt;
}e[N<<1];
int head[N],esum;
inline void add(int fr,int to){
    e[++esum]=(edge){to,head[fr]};
    head[fr]=esum;
}

inline int qp(int s1,int s2){
    if(s2==0)return 1;int an=qp(s1,s2>>1);
    if(s2&1)return an*an%mod*s1%mod;
    else return an*an%mod;
}
inline void Add(int &s1,int s2){
    s1=(s1+s2)%mod;
}

int p[N],q[N],inv[N];
void initC(){
    p[0]=p[1]=q[0]=q[1]=inv[0]=inv[1]=1;
    for(int i=2;i<N;i++){
        p[i]=p[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        q[i]=q[i-1]*inv[i]%mod;
    }
}
inline int ask(int s1,int s2){
    if(s1<0||s2<0||s1<s2)return 0;
    return p[s1]*q[s1-s2]%mod*q[s2]%mod;
}

int m,n,ans,siz[N],f[N][N][N],g[N][N];
void dfs(int wh,int fa){
    siz[wh]=1;
    memset(f[wh],0,sizeof(f[wh]));
    f[wh][0][0]=1;
    for(int i=head[wh],th;i;i=e[i].nxt){
        if((th=e[i].t)==fa)continue;
        dfs(th,wh);
        for(int x=0;x<=siz[wh]+siz[th];x++){
            for(int y=0;y<=siz[wh]+siz[th];y++){
                g[x][y]=0;
            }
        }
        for(int sx=0;sx<=siz[wh];sx++){
            for(int sy=0;sy<=siz[th];sy++){
                for(int cx=0;cx<=siz[wh];cx++){
                    for(int cy=0;cy<=siz[th];cy++){
                        Add(g[sx+sy][cx+cy],f[wh][sx][cx]*f[th][sy][cy]);
                    }
                }
            }
        }
        for(int x=0;x<=siz[wh]+siz[th];x++){
            for(int y=0;y<=siz[wh]+siz[th];y++){
                f[wh][x][y]=g[x][y];
            }
        }
        siz[wh]+=siz[th];
    }
    for(int s=1;s<=siz[wh];s++){
        Add(f[wh][s][siz[wh]],ask(siz[wh]-1,s-1));
    }
    return;
}
void work(int wh){
    int all=1,ss[N]={1};
    for(int i=1;i<=m;i++)all=all*i%mod,ss[i]=ss[i-1]*i%mod;
    all=qp(all,mod-2);
    dfs(wh,0);
    for(int s=0;s<=m;s++){
        for(int c=0;c<=m;c++){
            if(c+n>=m)continue;
            if(f[wh][s][c]==0)continue;
            Add(ans,f[wh][s][c]%mod*all%mod*ss[s]%mod*ss[m-1-s]%mod);
        }
    }
}
void solve(){
    initC();
    read(m);read(n);
    for(int i=1;i<m;i++){
        int s1,s2;read(s1);read(s2);
        add(s1,s2);add(s2,s1);
    }
    for(int i=1;i<=m;i++)work(i);
    printf("%lld\n",(ans%mod+mod)%mod);
}

signed main(){
	
    #ifdef feyn
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    int test=1;
    while(test--)solve();

    return 0;
}
```

---

## 作者：翼德天尊 (赞：6)

其实很容易想到树形 dp 来做，但是难点在于如何计算连通块的贡献。对吧，我们既不知道连通块被删的先后顺序，也不清楚如何计算当前连通块被分割之后的贡献。

但是我们发现我们并不需要知道这些啊？如果对于当前局面，存在一个大小为 $x>k$ 的连通块，无论如何我们一定会删它一次，它无论如何都会造成一次删除代价。所以其实只要我们知道该连通块出现的概率，我们就可以得到它对于问题的贡献。而删这个连通块之后的代价则可以交给其子连通块统计，对于当前连通块的贡献我们就不用再管了。所以最终的答案即为所有 $x>k$ 的连通块出现的概率之和。

所以现在问题来到了，**如何统计某个连通块的出现概率**。

考虑将问题进行神秘的转化：随机一个长度为 $n$ 的排列 $P$，从 $P_1$ 到 $P_n$ 依次考虑每一个节点当前所在连通块大小是否 $>k$，若是则删除，否则不删，求有效删除次数的期望。两个问题是等价的，因为固定了前若干个有效删除位置之后，下一个有效删除位会等概率出现。

设连通块大小为 $x$，与该连通块相连的节点个数为 $y$，此时我们可以将统计连通块的出现概率转化为统计在 $P$ 中 $x$ 个节点在 $y$ 个节点之后的概率，即为 $\frac{x!y!}{(x+y)!}$。**可以发现上步转化通过将随机删点转化为随机排列，使得我们对于概率的描述变得清晰了许多。**

于是我们现在只剩下了最后一个任务，统计每一种 $(x,y)$ 的连通块各有多少个。

这个使用树形 dp 统计就很方便了。可以设 $dp_{u,x,y}$ 表示以 $u$ 为根，大小为 $x$，且有 $y$ 个节点与之相接的连通块个数，转移套路树形背包即可。总时间复杂度 $O(n^2k^2)$。

将统计的主体转化成每个连通块，将随机删点转化为随机排列，很巧妙的题目啊。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
const int V=200;
const ll mod=998244353;
int n,m,siz[N];
ll jc[N<<1],inv[N<<1],dp[N][N][N],f[N][N];
struct Edge{
    int to[N<<1],next[N<<1],head[N],tot;
    void adde(int u,int v){
        to[++tot]=v,next[tot]=head[u],head[u]=tot;
    }
}S;
ll read(){
    ll w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}
ll ksm(ll x,int y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans;
}
void init(){
    jc[0]=inv[0]=1;
    for (int i=1;i<=V;i++) jc[i]=jc[i-1]*i%mod;
    inv[V]=ksm(jc[V],mod-2);
    for (int i=V-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
void dfs(int u,int fa){
    siz[u]=1,dp[u][1][0]=1;
    for (int i=S.head[u];i;i=S.next[i]){
        int v=S.to[i];
        if (v==fa) continue;
        dfs(v,u);
        for (int j=siz[u]+siz[v];j>=0;j--)
            for (int k=siz[u]+siz[v];k>=0;k--)
                f[j][k]=dp[u][j][k],dp[u][j][k]=0;
        for (int j=siz[u];j>=1;j--)
            for (int k=siz[u]-j;k>=0;k--){
                dp[u][j][k+1]=(dp[u][j][k+1]+f[j][k])%mod;
                for (int p=siz[v];p>=1;p--)
                    for (int q=siz[v]-p;q>=0;q--){
                        // if (u==1&&j==1&&k+1==1) cout<<f[j][k]<<"\n";
                        dp[u][j+p][k+q]=(dp[u][j+p][k+q]+f[j][k]*dp[v][p][q]%mod)%mod;
                    }                
            }

        siz[u]+=siz[v];
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    init();
    n=read(),m=read();
    for (int i=1;i<n;i++){
        int u=read(),v=read();
        S.adde(u,v),S.adde(v,u);
    }
    dfs(1,0);
    ll ans=0;
    for (int u=1;u<=n;u++){
        for (int i=m+1;i<=siz[u];i++){
            for (int j=0;j<=siz[u]-i;j++)
                ans=(ans+dp[u][i][j]*jc[i]%mod*jc[j+(u!=1)]%mod*inv[i+j+(u!=1)]%mod)%mod;//,cout<<u<<" "<<i<<" "<<j<<" "<<dp[u][i][j]<<"\n";
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Register_int (赞：2)

非常好计数，使我的背包旋转。

显然一个点操作两次是没有意义的，所以可以将操作序列转换为排列，问的就是期望能操作的点的个数。

枚举连通块大小。对于原树中一个以 $u$ 为根，大小为 $i$ 的连通块，他能造成贡献，当且仅当与这个连通块相邻的 $j$ 个点全部在他之前删除。剩下的点对他没有影响，所以只要考虑这 $i+j$ 个点即可。产生贡献的概率是好算的，随便排是 $(i+j)!$ 种，$j$ 个先全删的有 $i!j!$ 种，概率为 $\frac{i!j!}{(i+j)!}$。

问题转化为对前面那一坨计数。连通的还有个 $u$ 的父亲，很烦，所以干脆不要，最后再特判。于是直接 $dp_{u,i,j}$ 表示以 $u$ 为根，连通块 $i$ 个点，除父亲外相邻了 $j$ 个，转移就是将两部分的 $i,j$ 分别相加，树上背包即可。要注意，不选子节点的子树可以无中生有出来一个相邻点，所以要单独转移。时间复杂度 $O(n^4)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll inv_c(int n, int m) {
	return fac[n] * fac[m] % mod * ifac[n + m] % mod;
}

vector<int> g[MAXN]; int s[MAXN];

ll dp[MAXN][MAXN][MAXN], f[MAXN][MAXN];

inline 
void dfs(int u, int fa) {
	s[u] = dp[u][1][0] = 1;
	for (int v : g[u]) {
		if (v == fa) continue; dfs(v, u);
		for (int i = 0; i <= s[u] + s[v]; i++) {
			for (int j = 0; j <= s[u] + s[v]; j++) f[i][j] = 0;
		}
		for (int i = 0; i <= s[u]; i++) {
			for (int j = 0; j <= s[u]; j++) {
				for (int k = 0; k <= s[v]; k++) {
					for (int l = 0; l <= s[v]; l++) {
						f[i + k][j + l] = (f[i + k][j + l] + dp[u][i][j] * dp[v][k][l] % mod) % mod;
					}
				}
				f[i][j + 1] = (f[i][j + 1] + dp[u][i][j]) % mod;
			}
		}
		s[u] += s[v];
		for (int i = 0; i <= s[u]; i++) {
			for (int j = 0; j <= s[u]; j++) dp[u][i][j] = f[i][j];
		}
	}
}

int n, m; ll ans;

int main() {
	scanf("%d%d", &n, &m), init(n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = m + 1; j <= s[i]; j++) {
			for (int k = 0; k <= s[i] - j; k++) {
				if (!dp[i][j][k]) continue;
				ans = (ans + dp[i][j][k] * inv_c(j, k + (i > 1)) % mod) % mod;
			}
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：yllcm (赞：2)

考虑计算 $p_u$ 表示 $u$ 在操作过程中被删除的概率，答案就是 $\sum p_u$。

考虑枚举 $u$ 在删除的时候所在的联通块 $S$，然后计算概率使得满足两个条件：

* 在删除 $u$ 之前，$u$ 所在联通块的形态恰好为 $S$。
* $u$ 在 $S$ 中第一个被删除。

发现第一个条件只和联通块 $S$ 的邻域 $T$ 的大小有关。我们定义 $x\in T$ 当且仅当 $x\notin S$ 且 $x$ 与 $S$ 通过恰好一条边相连。

那么条件相当于 $T$ 中所有点都在 $u$ 之前删除，$S\setminus \{u\}$ 中所有点都在 $u$ 之后被删除（或者不被删除）

删除 $T$ 中的点是不需要考虑联通块大小大于 $k$ 的条件的。假如我们枚举 $T$ 中点删除的顺序，那么计算概率的方式是：不断计算当前点在剩余所有点中第一个被删除的概率，然后将其删去。那么概率是：

$$
|T|!\prod_{i=0}^{|T|-1}\frac{1}{|T|+|S|-i}
$$

前面乘上一个 $|T|!$ 的系数是因为我们枚举了排列的顺序。

而计算 $u$ 在剩下点中第一个被删除的概率是简单的，乘上 $\frac{1}{|S|}$ 即可。

所以概率为：

$$
|T|!\frac{1}{(|T|+|S|)^{\underline{|T|}}}\frac{1}{|S|}
$$

剩下的问题只需要求出 $f_{u,i,j}$ 表示 $|S|=i,|T|=j$ 的联通块数量即可，不难使用树形 DP 得到。

树形 DP 的复杂度为 $\mathcal{O}(n^3)$。由于需要对每个 $u$ 都做一遍，总复杂度为 $\mathcal{O}(n^4)$。

本题是一个常见的概率模型：由于整体的限制较为复杂，不妨考虑局部成为“第一个”的概率。类似的思想在 ARC108E Random IS 也有体现。

upd：有老哥指出单次 DP 的复杂度是 $\mathcal{O}(n^4)$ 的，所以这个做法其实上是 $\mathcal{O}(n^5)$，但是常数比较小。实际上可以直接在 LCA 处统计联通块 $S$ 的数量，然后再乘上点数，从而只需要一次 DP。

~~当然你发现转移是卷积，所以可以插 $n^2$ 个值，做 $n$ 次 DP 之后再 $\mathcal{O}(n^4)$ 插回来。~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long 
#define db double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
  int x = 0; bool op = false;
  char c = getchar();
  while(!isdigit(c))op |= (x == '-'), c = getchar();
  while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return op ? -x : x;
}
const int N = 110;
const int P = 998244353;
void add(int &a, int b) {a += b; a >= P ? a -= P : 0;}
void sub(int &a, int b) {a -= b; a < 0 ? a += P : 0;}
int ksm(int x, int k) {
  int res = 1;
  for(int pw = x; k; (k & 1) ? res = 1ll * res * pw % P : 0, pw = 1ll * pw * pw % P, k >>= 1);
  return res;
}
int n, k;
int fac[N], ifac[N];
void init() {
  fac[0] = ifac[0] = 1;
  for(int i = 1; i < N; i++)fac[i] = 1ll * fac[i - 1] * i % P;
  ifac[N - 1] = ksm(fac[N - 1], P - 2);
  for(int i = N - 2; i; i--)ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
  return ;
}
vector<int> G[N];
int ans;
int f[N][N][N], sz[N];
void dfs(int u, int fa) {
  for(int i = 0; i <= sz[u]; i++) {
    for(int j = 0; j <= sz[u]; j++) {
      f[u][i][j] = 0;
    }
  }
  f[u][1][0] = 1; sz[u] = 1;
  for(int v : G[u])if(v != fa) {
    dfs(v, u);
    for(int i = sz[u]; ~i; i--) {
      for(int j = sz[u]; ~j; j--) {
        add(f[u][i][j + 1], f[u][i][j]);
        for(int k = sz[v]; ~k; k--) {
          for(int l = sz[v]; ~l; l--) {
            add(f[u][i + k][j + l], 1ll * f[u][i][j] * f[v][k][l] % P);
          }
        }
        f[u][i][j] = 0;
      }
    }
    sz[u] += sz[v];
  }
  return ;
}
void work(int u) {
  dfs(u, 0);
  for(int i = k + 1; i <= n; i++) {
    for(int j = 0; j <= n; j++) {
      int coef = 1ll * fac[i - 1] * fac[j] % P * ifac[i + j] % P;
      add(ans, 1ll * f[u][i][j] * coef % P);
    }
  }
  return ;
}
int main() {
  init();
  n = read(); k = read();
  for(int i = 1; i < n; i++) {
    int u = read(), v = read();
    G[u].pb(v); G[v].pb(u);
  }
  for(int i = 1; i <= n; i++)work(i);
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：orz_z (赞：1)



什么神仙。

将期望转到局面上。

发现期望相当于每个还可以操作的局面出现的概率之和。

于是我们找到局面，算概率即可。

找到树上一个大小为 $a$ 的子图，满足 $a>k$，如果有 $b$ 个之外的点与之相连。

我们考虑将操作的序列看成排列，那么出现这种局面的概率为 $\frac{a!b!}{(a+b)!}$，因为这 $b$ 个数都得在 $a$ 的前面，相对关系确定了。

然后树上背包转移即可，令 $f_{u,i,j}$ 表示只考虑 $u$ 的子树内的点，$u$ 在子树内的联通块大小为 $i$，与之相连的点有 $j$ 个的方案数。

---

## 作者：王熙文 (赞：1)

对我而言是一道期望好题，记录一下。

## 思路

考虑换一种随机方式：每次操作等概率随机一个**之前没有随机到**的点，如果当前点所在连通块大小大于 $k$ 就删掉这个点以及与它相连的所有边，并将期望次数加一。

这样的答案不会改变，因为当前点如果随机到了以后就没有用了。对于当前状态，当前合法的点随机到的概率都是一样的。如果此时随机了一些不合法的点，下一个点是合法的，则这些点的答案期望不变。相当于将每个合法的点的出现次数乘上了某个数，而期望不变。

其实是数学归纳，如果证明了更小的点集这样的答案不变，则根据上面可以证明当前答案不变。

这样转化之后操作本质上是一个排列。

接下来考虑计算每个连通块的贡献。对于每个连通块，只要它在操作中出现过，则可以给答案贡献 $1$。相当于这个连通块给答案的贡献是它的概率。那么最终的答案就是所有大小大于 $k$ 的连通块出现概率之和。

设连通块大小为 $n$，所有可以到达连通块的点的个数为 $m$，则连通块中的点在排列中的位置一定在这 $m$ 个点之后。所以这样的连通块的概率是 $\dfrac{n!m!}{(n+m)!}$。

设 $dp_{i,j,k}$ 表示点 $i$ 作为根的连通块大小为 $j$，在 $i$ 子树内可以到达连通块的点的个数为 $k$ 的连通块个数。按照树上背包的转移即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int qpow(int a,int b)
{
	int ans=1;
	while(b!=0)
	{
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
int jc[110],invjc[110];
int n,k;
vector<int> e[110];
int siz[110];
int dp[110][110][110],gt[110][110];
int ans=0;
void dfs(int u,int fa)
{
	siz[u]=1,dp[u][1][0]=1;
	for(int v:e[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		for(int i=1; i<=siz[u]+siz[v]; ++i)
		{
			for(int j=0; j<=n-i; ++j) gt[i][j]=(j==0?0:dp[u][i][j-1]);
		}
		for(int i=1; i<=siz[u]; ++i)
		{
			for(int j=1; j<=siz[v]; ++j)
			{
				for(int k=0; k<=n-i; ++k)
				{
					for(int l=0; l<=n-j; ++l)
					{
						gt[i+j][k+l]=(gt[i+j][k+l]+dp[u][i][k]*dp[v][j][l])%mod;
					}
				}
			}
		}
		for(int i=0; i<=siz[u]+siz[v]; ++i)
		{
			for(int j=0; j<=n-i; ++j) dp[u][i][j]=gt[i][j];
		}
		siz[u]+=siz[v];
	}
	for(int i=k+1; i<=siz[u]; ++i)
	{
		for(int j=0; j<=n-i; ++j)
		{
			int gt=j+(fa!=0);
			ans=(ans+dp[u][i][j]*jc[i]%mod*jc[gt]%mod*invjc[i+gt])%mod;
		}
	}
}
signed main()
{
	jc[0]=1; for(int i=1; i<=100; ++i) jc[i]=jc[i-1]*i%mod;
	invjc[100]=qpow(jc[100],mod-2); for(int i=99; i>=0; --i) invjc[i]=invjc[i+1]*(i+1)%mod;
	cin>>n>>k;
	for(int i=1; i<=n-1; ++i)
	{
		int u,v; cin>>u>>v;
		e[u].push_back(v),e[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：_YangZj (赞：1)

首先对题目进行如下转化（其实就是定一个操作的顺序），定义一个排列的权值 $v$ 生成方式如下：

依次考虑 $p_1,p_2,...,p_n$，如果当前点 $x$ 所在联通块大小 $\geq k$，则将 $x$ 删去，$v\leftarrow v+1$，否则不做任何操作。

问所有排列的权值期望。

我想到这里的时候以为这样转化每种状态的并非 **均匀** 的，因为不被删去的点的顺序会有影响。

实际上并非，在某一局面下，肯定不会被操作的点是确定的，对每种方案的贡献都是一样的，因此下一个被选取的点的选择过程是 **均匀且随机 **的。

然后考虑转化后的问题怎么求解。我的方法是，**正难则反**，计数在多少个排列中 $x$ 不会被操作。

倒过来考虑，也就是只排列中考虑在 $x$ 之后的点，$x$ 所在连通块大小 $\leq k$，此时 $x$ 所在条件已经满足了条件。

对这个计数也是容易的，考虑树形 $\text{dp}$，计数 $x$ 的贡献时，以 $x$ 为根，这样不需要考虑子树外的贡献。设 $f_{x,i,j}$  表示 $x$ 子树中，有 $i$ 个点在排列中在 $x$ 之前，在 $x$ 之后的点与 $x$ 构成的连通块大小为 $j$。转移朴素树形背包。

枚举根节点 $O(n)$，树形 $\text{dp}$ 一次 $O(n^3)$。总复杂度 $O(n^4)$。

code 

```cpp
#include<bits/stdc++.h>
using namespace std;

#define vc vector
#define pb emplace_back

const int N = 105, P = 998244353;

//calc
inline void inc(int &x,int y) { x += y-P; x += (x>>31)&P; }
inline void dec(int &x,int y) { x -= y; x += (x>>31)&P; }
inline int pls(int x,int y) { x += y-P; x += (x>>31)&P; return x; }
inline int power(int a,int b) { int res = 1; for(;b;b >>= 1,a = 1ll*a*a%P) if(b&1) res = 1ll*res*a%P; return res; }

int n, k, ans, sz[N], fc[N], ifc[N], f[N][N][N], g[N][N];
vc<int> G[N];

inline void prework(int n) {
	fc[0] = ifc[0] = 1;
	for(int i = 1; i <= n; i++) fc[i] = 1ll * i * fc[i-1] % P, ifc[i] = power(fc[i], P - 2);
}

inline void dfs(int x, int fa) {
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) f[x][i][j] = 0;
	sz[x] = 1; f[x][0][1] = 1;
	for(auto y:G[x]) if(y != fa) {	
		dfs(y, x);
		for(int i = 0; i <= sz[x]; i++) for(int j = 0; j <= sz[x]; j++) if(f[x][i][j]) 
			for(int a = 0; a <= sz[y]; a++) for(int b = 0; b <= sz[y]; b++) if(f[y][a][b]) 
				inc(g[i+a][j+b], 1ll * f[x][i][j] * f[y][a][b] % P);
		sz[x] += sz[y];
		for(int i = 0; i <= sz[x]; i++) for(int j = 0; j <= sz[x]; j++) 
			f[x][i][j] = g[i][j], g[i][j] = 0;
	}
	for(int i = sz[x]; i > 0; i--) {
		f[x][i][0] = 0;
		for(int j = 0; j <= sz[x]; j++) inc(f[x][i][0], f[x][i-1][j]);
	}
}

inline void solve(int rt) {
	dfs(rt, 0); int res = 0;
	for(int i = 0; i < n; i++) for(int j = 1; j <= k; j++) if(f[rt][i][j]) 
		inc(res, 1ll * fc[i] * fc[n - i - 1] % P * f[rt][i][j] % P);
	res = 1ll * pls(fc[n], P - res) * ifc[n] % P;
	inc(ans, res);
}

signed main() {
	cin >> n >> k; prework(n);
	for(int i = 1, u, v; i < n; i++) cin >> u >> v, G[u].pb(v), G[v].pb(u);
	for(int i = 1; i <= n; i++) solve(i);
	cout << ans << endl;
	return 0;
}
```





---

## 作者：鲤鱼江 (赞：0)

感觉 AT 和 CF 甚至模拟赛都很有这一类题目啊！

考虑求出每种连通块对答案的贡献，对于一个大小大于 $k$ 的连通块 $S$，求出与 $S$ 中点有直接连边但是不属于 $S$ 的节点个数 $m$，那么 $S$ 造成贡献的概率是 $\frac{(|S|)!m!}{(|S|+m)!}$。

理由的话可以考虑只有在 $m$ 个节点都被删掉之后，连通块 $S$ 才是独立的，否则它就不是连通块 $S$ 了。我们要求的是对于每种独立连通块的贡献，不然可能会算重。

由期望的线性性，直接把所有连通块造成贡献的概率加起来就行了。

现在考虑 DP 一下贡献，发现 $S$ 的贡献只和 $|S|$ 与 $m$ 有关，把这两个东西刻画入状态里面做树形 DP 就行了，$f_{i,j,k}$ 表示以 $i$ 为根的子树，子树内（强行钦定 $i$ 必选）选了 $j$ 个节点作为连通块，且 $m=k$ 的方案数。背包一下即可，写得好看一点可以做到 $O(n^4)$ 注意别写得太难看。

谨记连通块大小严格大于而非大于等于 $k$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=110;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}f[N][N][N],g[N][N],ans;
int n,k,siz[N];vector < int > v[N];

template < int Max >
struct Choose{
	modint frac[Max+10],inv[Max+10];
	Choose(){
		frac[0]=inv[0]=1;for(int i=1;i<=Max;++i) frac[i]=frac[i-1]*i;
		inv[Max]=frac[Max].inv();for(int i=Max-1;i;--i) inv[i]=inv[i+1]*(i+1);
	}
	modint* operator [](const int x){return x?frac:inv;}
	modint operator ()(const int x,const int y){return x<y||y<0?0:frac[x]*inv[y]*inv[x-y];}
};
Choose < N*N > C;

inline modint Calc(int x,int y){
	return C[1][x]*C[1][y]*C[0][x+y];
}
void dfs(int x,int y){
	f[x][1][v[x].size()]=1;siz[x]=1;
	for(int i:v[x]){
		if(i==y) continue;
		dfs(i,x);
		for(int j=0;j<=siz[x];++j) for(int k=0;k<=n;++k) g[j][k]=f[x][j][k];
		for(int j=1;j<=siz[x];++j){
			for(int k=1;k<=n;++k){
				for(int a=1;a<=siz[i];++a){
					for(int b=1;b<=n;++b){
						f[x][j+a][k+b-2]+=g[j][k]*f[i][a][b];
					}
				}
			}
		}
		siz[x]+=siz[i];
	}
	for(int i=k;i<=siz[x];++i) for(int j=0;j<=n;++j) ans+=f[x][i][j]*Calc(i,j);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;++k;for(int i=1,x,y;i<n;++i){cin>>x>>y;v[x].emplace_back(y);v[y].emplace_back(x);}
	dfs(1,0);
//	modint res=0;
//	for(int i=1;i<=n;++i){
//		for(int j=k;j<=siz[i];++j){
//			for(int l=0;l<=n;++l){
//				if(f[i][j][l].val) cout<<i<<' '<<j<<' '<<l<<' '<<f[i][j][l]<<' '<<Calc(j,l)<<endl;
//				res+=f[i][j][l]*Calc(j,l);
//			}
//		}
//	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：天命之路 (赞：0)

比较强的概率转化，如果没见过真的很难想。

原过程中，一个点被选的概率与当前 $>K$ 的连通块有关，根本做不得。

考虑进行转化，我们不妨允许找到一个所在连通块大小小于 $K$ 的点进行切分，但是如果出现这种情况，我们定义这次操作不消耗时间，称其为“无效操作”。

容易发现，无效操作怎么做都不会影响有效操作的情况，而且每个有效操作的执行概率仍然是均等的。所以这个转化的正确性可以理解。

转化完之后，我们把每一步删去的点列出来，设 $P_i$ 表示第 $i$ 步删除的点。我们对所有排列 $P$ 算贡献之和即可。

一个排列 $P$ 中，如果位置 $i$ 满足，当删到 $P_i$ 时，其所属的连通块大小 $>K$，那么这个位置就有 $1$ 的贡献。

枚举 $P_i = x$。假设我们可以枚举删到这个点时其所属的连通块 $S$。设 $S$ 的周围一圈的点集为 $T$。那么删到 $x$ 时连通块为 $S$ ，当且仅当所有 $T$ 中的点都在 $x$ 前被删，所有 $S$ 中的点都在 $x$ 后被删。因为我们只需算概率，所以只用考虑这 $|S| + |T|$ 个点的相对位置，那么 $T$ 在 $S$ 之前的概率为 $\dfrac{1}{\binom{|S|+|T|}{|S|}}$，$x$ 在 $S$ 中第一个被删的概率为 $\dfrac{1}{|S|}$。那么，删到 $x$ 时连通块恰好为 $S$ 的概率就是 $\dfrac{1}{\binom{|S|+|T|}{|S|}|S|}$。

于是我们只需对于每个 $(x,a,b)$ 计算，$|S| = a$ 且 $|T| = b$ 的连通块数即可。以 $x$ 为根跑一遍树形背包即可，单次背包的复杂度为 $O(n^4)$。

所以总时间复杂度为 $O(n^5)$，常数较小所以可以通过，也可通过插值优化背包合并的过程，做到 $O(n^4)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5,P = 998244353;
inline void Plus(int &x,const int &y) { x += y;if(x >= P) x -= P;}
int fac[N],ifac[N],inv[N];
inline void init(int n) {
	fac[0] = 1;
	for(int i = 1;i <= n;i++) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[1] = 1;
	for(int i = 2;i <= n;i++) inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
	ifac[0] = 1;
	for(int i = 1;i <= n;i++) ifac[i] = 1ll * ifac[i - 1] * inv[i] % P;
}
inline int C(int n,int m) { if(n < 0 || m < 0 || n < m) return 0;return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;}
inline int invC(int n,int m) { if(n < 0 || m < 0 || n < m) return 0;return 1ll * ifac[n] * fac[m] % P * fac[n - m] % P;}
int dp[N][N][N],sze[N]; // 选一个包含根的连通块，[根][内点][界点]
int n,K;
vector<int> G[N];

void DP(int x,int fa) {
	static int tmp[N][N];
	memset(tmp,0,sizeof tmp);
	memset(dp[x],0,sizeof dp[x]);
	dp[x][0][0] = 1;sze[x] = 0;
	int cnt = 0;
	for(auto y : G[x]) {
		if(y == fa) continue;
		DP(y,x);++cnt;
		for(int a = 0;a <= sze[x];a++)
			for(int b = 0;a + b <= sze[x];b++) {
				Plus(tmp[a][b + 1],dp[x][a][b]); // 这个子树不选任何一个点
				for(int c = 0;c <= sze[y];c++)
					for(int d = 0;c + d <= sze[y];d++)
						Plus(tmp[a + c][b + d],1ll * dp[x][a][b] * dp[y][c][d] % P);
			}
		sze[x] += sze[y];
		for(int a = 0;a <= sze[x];a++)
			for(int b = 0;a + b <= sze[x];b++)
				dp[x][a][b] = tmp[a][b],tmp[a][b] = 0;
	}
	++sze[x];
	for(int a = sze[x];a >= 1;a--)
		for(int b = 0;a + b <= sze[x];b++)
			dp[x][a][b] = dp[x][a - 1][b],dp[x][a - 1][b] = 0;
}
int Solve(int x) {
	int res = 0;
	DP(x,0);
	for(int a = K + 1;a <= n;a++)
		for(int b = 1;a + b <= n;b++) { // 这里算漏了连通块为全集的情况，所以在最后的答案中补上了一个 1。
			Plus(res,1ll * dp[x][a][b] * invC(a + b,a) % P * inv[a] % P);
		}
	return res;
}
int main() {
	cin >> n >> K;
	for(int i = 1,a,b;i < n;i++)
		cin >> a >> b,G[a].push_back(b),G[b].push_back(a);
	init(n);
	int res = 1;
	for(int i = 1;i <= n;i++) Plus(res,Solve(i));
	cout << res << endl;
	return 0;
}
```





---

## 作者：lfxxx (赞：0)

好题。

首先随机过程中每一步的样本空间在不断变化，这个比较难受，考虑这样一步转化：每次会随机抽取一个点割去与其相邻所有边，但是只有抽到的点当前所在连通块大小超过 $K$ 时才会给这次随机过程产生一次贡献，不难发现由于如果将产生贡献的点作为这次随机过程的状态，一个状态会等概率向后继转移，所以是一个等价转化，但是还有一个不好的事情是这样的转化后可能会出现抽取重复点的情况并且操作序列长度可能会很长，于是考虑一个新的转化：随机一个点的排列，然后依次进行操作，由于还是满足一个状态会等概率向后继转移所以依然是等价转化。

考虑怎么比较好的计算贡献，在每个点上计算贡献貌似不太好做，发现每次产生贡献一定是一个大于 $K$ 的连通块中选择了一个点并将其切割开来，我们考虑以这个连通块作为计算贡献的主体，假设这个连通块大小为 $i$ 且其四周（连通块所有点的一级邻域并再去掉连通块内点）有 $j$ 个点，那么有 $\frac{i! \times j!}{(i+j)!}$ 的概率，会出现这个连通块四周的点全部被删掉后（也就是这个连通块形成）再从连通块内选出一个点并分裂连通块产生贡献，于是只需要计算这样的连通块数量再乘上 $\frac{i! \times j!}{(i+j)!}$ 贡献到答案即可。

计算这样的连通块数是简单的，考虑设计 $dp_{u,i,j}$ 表示考虑以 $u$ 为根的子树，包含 $u$ 的有 $i$ 个点四周有 $j$ 个点的连通块数，转移是一个树形背包，枚举上界优化一下即可做到 $O(n^4)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 114;
int C[maxn][maxn];
int dp[maxn][maxn][maxn];
int g[maxn][maxn];
int sz[maxn];
vector<int> E[maxn];
int n,k;
int ans;
int fac[maxn],inv[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b&1) res=res*a%mod;
    return res;
}
void dfs(int u,int fa){
    dp[u][1][0]=1;
    sz[u]=1;
    for(int v:E[u]){
        if(v!=fa){
            dfs(v,u);
            memset(g,0,sizeof(g));
            for(int i=0;i<=sz[u];i++){
                for(int p=0;p<=n;p++){
                    for(int j=1;j<=sz[v];j++){
                        for(int q=0;q<=n;q++){
                            if(p+q<=n) g[i+j][p+q]=(g[i+j][p+q]+dp[u][i][p]*dp[v][j][q]%mod)%mod;
                        }
                    }
                    if(p+1<=n) g[i][p+1]=(g[i][p+1]+dp[u][i][p])%mod;
                }
            }
            sz[u]+=sz[v];
            for(int i=0;i<=sz[u];i++){
                for(int p=0;p<=n;p++){
                    dp[u][i][p]=g[i][p];
                }
            }
        }
    }
    for(int i=k+1;i<=sz[u];i++){
        for(int p=0;p<=n;p++){
            int q=p;
            if(fa!=0) q++;
            //i q
            //i!*q!/(i+q)!*dp[u][i][p]
            if(i+q<=n){
                ans=(ans+fac[i]*fac[q]%mod*inv[i+q]%mod*dp[u][i][p]%mod)%mod;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    fac[0]=inv[0]=1;
    for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Schi2oid (赞：0)


## 题意简述

给定一棵有 $n$ 个结点的树，每次进行如下操作，直到图中不存在大小大于 $K$ 的连通块：

- 在所有所属连通块点数大于 $K$ 的点中等概率随机一个点，将其邻边删去。

求期望操作次数。$n\le100$。

## 题解

将题意改为有一个初始为 $0$ 的计数器，每次删去一个点，在剩余点中等概率随机，如果随到的点的所在连通块大小 $>K$，则将计数器加一。因此我们将所有操作刻画为一个排列。

考虑一个图中大小 $>K$ 的连通块。如果它在某时刻出现（其内部点连通，与外部点都不连通），那么它在之后一定会被切分为更小的连通块，即其出现则对计数器产生 $1$ 的贡献。因此考虑统计每一个连通块的出现概率。将所有大小 $>K$ 的连通块的出现概率求和即为答案。

对于一个连通块，设其大小为 $n$，与其通过一条边直接相连的点个数为 $m$，那么其出现当且仅当所有 $m$ 个点在所有 $n$ 个点之前出现。因此，其概率为 $\frac{m!n!}{(m+n)!}$。这是由上述转化题意直接导出的。

因此，dp 求出每种 $(n,m)$ 的连通块个数，这可以树上背包，总复杂度 $O(n^4)$。



---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc165_e)

**题目大意**

> 给定 $n$ 个点的树，每次在所有大小 $>k$ 的连通块中随机选择一个点删除，直到所有连通块大小 $\le k$，求期望操作数。
>
> 数据范围：$n\le 100$。

**思路分析**

枚举每个大小 $>k$ 的连通块 $S$ 有多少概率出现，显然出现概率之和就是期望操作次数。

设 $|S|=x$，$S$ 的邻域大小为 $y$，那么 $S$ 出现要求 $y$ 个邻居都出现在 $S$ 中点之前，概率为 $\dfrac{x!y!}{(x+y)!}$。

那么就可以树形 dp，设 $dp_{u,i,j}$ 表示以 $u$ 为根满足 $x=i,y=j$ 的 $S$ 有多少个。

时间复杂度 $\mathcal O(n^4)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353;
ll fac[105],ifac[105],ans,f[105][105][105],tmp[105][105];
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int n,k,siz[105];
vector <int> G[105];
void dfs(int u,int fz) {
	f[u][1][0]=1,siz[u]=1;
	for(int v:G[u]) if(v^fz) {
		dfs(v,u);
		memset(tmp,0,sizeof(tmp));
		for(int i=1;i<=siz[u];++i) for(int j=0;i+j<=siz[u];++j) if(f[u][i][j]) {
			tmp[i][j+1]=(tmp[i][j+1]+f[u][i][j])%MOD;
			for(int x=1;x<=siz[v];++x) for(int y=0;x+y<=siz[v];++y) if(f[v][x][y]) {
				tmp[i+x][j+y]=(tmp[i+x][j+y]+f[u][i][j]*f[v][x][y])%MOD;
			}
		}
		memcpy(f[u],tmp,sizeof(f[u])),siz[u]+=siz[v];
	}
	for(int i=k+1;i<=siz[u];++i) for(int j=0;i+j<=siz[u];++j) if(f[u][i][j]) {
		ans=(ans+f[u][i][j]*ifac[i+j+(!!fz)]%MOD*fac[i]%MOD*fac[j+(!!fz)])%MOD;
	}
}
signed main() {
	scanf("%d%d",&n,&k);
	for(int i=fac[0]=ifac[0]=1;i<=n;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=1,u,v;i<n;++i) {
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

