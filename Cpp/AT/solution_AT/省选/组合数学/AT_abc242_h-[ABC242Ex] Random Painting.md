# [ABC242Ex] Random Painting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc242/tasks/abc242_h

$ 1 $ から $ N $ までの番号が振られた $ N $ 個のマスがあり、始めすべてのマスは白く塗られています。

また、箱の中に $ 1 $ から $ M $ までの番号が振られた $ M $ 個のボールが入っています。

以下の操作を、$ N $ 個のマスがすべて黒く塗られるまで繰り返します。

1. 箱から $ 1 $ つボールを取り出す。取り出し方は完全ランダムであり、各ボールは等確率で選ばれる。
2. 取り出したボールの番号を $ x $ として、マス $ L_x,\ L_x+1,\ \ldots,\ R_x $ を黒く塗る。
3. 取り出したボールを箱に戻す。

操作回数の期待値を $ \text{mod\ }\ 998244353 $ で求めてください（注記参照）。

## 说明/提示

### 注記

求める期待値は必ず有理数となることが証明できます。またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

### 制約

- $ 1\ \leq\ N,M\ \leq\ 400 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- すべてのマス $ i $ についてある整数 $ j $ が存在し、$ L_j\ \leq\ i\ \leq\ R_j $
- 入力はすべて整数

### Sample Explanation 1

求める期待値は $ \frac{7}{2} $ です。 $ 499122180\ \times\ 2\ \equiv\ 7\pmod{998244353} $ なので、$ 499122180 $ を出力します。

## 样例 #1

### 输入

```
3 3
1 1
1 2
2 3```

### 输出

```
499122180```

## 样例 #2

### 输入

```
13 10
3 5
5 9
3 12
1 13
9 11
12 13
2 4
9 12
9 11
7 11```

### 输出

```
10```

## 样例 #3

### 输入

```
100 11
22 43
84 93
12 71
49 56
8 11
1 61
13 80
26 83
23 100
80 85
9 89```

### 输出

```
499122193```

# 题解

## 作者：_maojun_ (赞：6)

实现了一下学长讲的 $O(m^2\log n)$ 做法。

---

设状态为 $S=\{(l_i,r_i)\}$，合法为这些区间的并达到 $[1,n]$。

停时的期望等于所有不合法状态的“出现概率”与“离开期望步数”乘积的总和。

大小为 $k$ 的集合的“离开期望步数”为 $\dfrac m{m-k}$，只需求大小为 $k$ 的不合法集合出现总概率。

区间双关键字排序后，设 $f_{i,j,k}$ 表示考虑了前 $i$ 个区间，覆盖了 $[1,j]$，用了 $k$ 的区间的方案数，则最后不合法的概率：

$$p_k=\dfrac{{m\choose k}-f_{m,n,k}}{m\choose k}$$

$f$ 有转移：

$$f_{i,j,k}\gets f_{i-1,j,k}\\f_{i,\max\{j,r_i\},k+1}\gets f_{i-1,j,k},j\ge l_i-1$$

可以做到 $O(nm^2)$。

```cpp
typedef pair<int,int> pi;
#define fi first
#define se second
typedef long long ll;
const int N=405,MOD=998244353;
int n,m;pi a[N];

inline ll ksm(ll x,int y=MOD-2){ll r=1;for(;y;y>>=1,x=x*x%MOD)if(y&1)r=r*x%MOD;return r;}
ll I[N],C[N];
inline void ad(int&x,int y){x+=y;x>=MOD&&(x-=MOD);}
int f[N][N][N];
inline void main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i].fi,&a[i].se);
	sort(a+1,a+m+1);
	I[1]=1;for(int i=2;i<=m;i++)I[i]=I[MOD%i]*(MOD-MOD/i)%MOD;
	C[0]=1;for(int i=1;i<=m;i++)C[i]=C[i-1]*i%MOD*I[m-i+1]%MOD;
	f[0][0][0]=1;
	for(int i=1;i<=m;i++)for(int j=0;j<=n;j++)for(int k=0;k<i;k++)if(f[i-1][j][k]){
		ad(f[i][j][k],f[i-1][j][k]);
		if(a[i].fi<=j+1)ad(f[i][max(j,a[i].se)][k+1],f[i-1][j][k]);
	}
	ll rs=0;
	for(int k=0;k<m;k++)rs=(rs+(1-f[m][n][k]*C[k])%MOD*I[m-k])%MOD;
	printf("%lld\n",(rs+MOD)*m%MOD);
}
```

---

三维状态，比较难以优化，但是可以把第三维写成生成函数形式：$F_{i,j}(x)=\sum f_{i,j,k}x^k$，则转移变为：

$$F_{i,j}(x)\gets F_{i-1,j}(x)\\F_{i,\max\{j,r_i\}}(x)\gets xF_{i-1,j}(x),j\ge l_i-1$$

最后代入 $m+O(1)$ 个 $x$ 把 $F_{m,n}$ 的系数插出来。

这个转移的过程形如单点修改区间乘法和查询区间和，线段树维护即可，复杂度 $O(m^2\log n)$。

---

代码可能写得比较丑。

```cpp
typedef pair<int,int> pi;
#define fi first
#define se second
typedef long long ll;
const int N=405,MOD=998244353;
int n,m;pi a[N];
inline ll ksm(ll x,int y=MOD-2){ll r=1;for(;y;y>>=1,x=x*x%MOD)if(y&1)r=r*x%MOD;return r;}
ll I[N],C[N];

const int S=N<<2;
ll vl[S],tg[S];
#define ls p<<1
#define rs p<<1|1
#define md (l+r>>1)
#define Ls ls,l,md
#define Rs rs,md+1,r
#define al 1,0,n
inline void pu(int p){vl[p]=(vl[ls]+vl[rs])%MOD;}
inline void ch(int p,int k){vl[p]=vl[p]*k%MOD;tg[p]=tg[p]*k%MOD;}
inline void pd(int p){if(tg[p]^1){ch(ls,tg[p]);ch(rs,tg[p]);tg[p]=1;}}
void B(int p,int l,int r){vl[p]=!l;tg[p]=1;if(l==r)return;B(Ls);B(Rs);pu(p);}
void U1(int p,int l,int r,int x,int k){
	vl[p]=(vl[p]+k)%MOD;if(l==r)return;pd(p);x<=md?U1(Ls,x,k):U1(Rs,x,k);
}
void U2(int p,int l,int r,int L,int k){
	if(L<=l)return ch(p,k);pd(p);if(L<=md)U2(Ls,L,k);U2(Rs,L,k);pu(p);
}
ll Q(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return vl[p];pd(p);return L>md?Q(Rs,L,R):R<=md?Q(Ls,L,R):(Q(Ls,L,R)+Q(Rs,L,R))%MOD; 
}

const int G=3,iG=ksm(G);
int Ln,Rv[512],*mG[10],wG;
inline void INIT(){
	wG=ksm(G,MOD-1>>9);
	for(int i=1;i<512;i++)Rv[i]=Rv[i>>1]>>1|(i&1)<<8;
	for(int k=0;k<9;k++){
		const ll w=ksm(iG,MOD-1>>k+1);
		mG[k]=new int[1<<k];mG[k][0]=1;
		for(int i=1;i<1<<k;i++)mG[k][i]=mG[k][i-1]*w%MOD;
	}
}
inline void NTT(int*A){
	for(int i=0;i<512;i++)if(i<Rv[i])swap(A[i],A[Rv[i]]);
	for(int k=0;k<9;k++)for(int i=0;i<512;i+=1<<k+1)for(int j=0;j<1<<k;j++){
		int x=A[i|j],y=(ll)A[i|1<<k|j]*mG[k][j]%MOD;
		A[i|j]=(x+y)%MOD;A[i|1<<k|j]=(x-y+MOD)%MOD;
	}
}
int A[512];
inline void main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&a[i].fi,&a[i].se);
	sort(a+1,a+m+1);
	I[1]=1;for(int i=2;i<=m;i++)I[i]=I[MOD%i]*(MOD-MOD/i)%MOD;
	C[0]=1;for(int i=1;i<=m;i++)C[i]=C[i-1]*i%MOD*I[m-i+1]%MOD;
	INIT();
	for(int t=0,x=1;t<512;t++,x=(ll)x*wG%MOD){
		B(al);
		for(int i=1,l=0;i<=m;i++){
			l=max(l,a[i].fi-1);
			if(l<=a[i].se)U1(al,a[i].se,Q(al,l,a[i].se)*x%MOD);
			if(a[i].se^n)U2(al,a[i].se+1,x+1);
		}
		A[t]=Q(al,n,n);
	}
	NTT(A);ll iv=ksm(512),as=0;
	for(int k=0;k<m;k++)as=(as+(1-A[k]*iv%MOD*C[k])%MOD*I[m-k])%MOD;
	printf("%lld\n",(as+MOD)*m%MOD);
}
```

---

## 作者：mskqwq (赞：6)

很好的 min-max 容斥。

设 $S_{max}$ 表示点集 $S$ 中的每个点，第一次被覆盖到的时间的最大值，$S_{min}$ 同理。那么我们要求的就是 $E([1,n]_{max})$，考虑 min-max 容斥，变成求 $\sum_{T \subseteq [1,n]} (-1)^{|T|+1}E(T_{min})$。

考虑如何计算 $E(T_{min})$，我们只需求出有多少个区间与 $T$ 有交，假设个数为 $k$，那么 $E(T_{min})=\dfrac m k$。考虑 dp，设 $f_{i,j}$ 表示考虑了 $[1,i]$，有 $j$ 个区间与 $T$ 有交的方案数，并钦定 $i \in T$。转移枚举下一个点 $k$，需要计算有多少个新的区间包含 $k$，对 $l,r$ 预处理二维前缀和就能 $O(1)$ 转移。

注意边界为 $f_{0,0}=-1$ 而不是 $1$。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=410,mod=998244353;
int n,m,f[N][N],s[N][N];ll ans;
ll qp(ll a,ll b){ll r=1;for(;b;b>>=1,a=a*a%mod)if(b&1)r=r*a%mod;return r;}
void misaka(){
    n=read(),m=read();
    rep(i,1,m){
        int l=read(),r=read();
        s[l][r]++;
    }
    rep(i,1,n)rep(j,1,n) s[i][j]+=s[i-1][j];
    _rep(j,n,1)rep(i,1,n) s[i][j]+=s[i][j+1];
    f[0][0]=mod-1;
    rep(i,0,n-1)rep(j,0,m)if(f[i][j])
        rep(k,i+1,n) (f[k][j+s[k][k]-s[i][k]]+=mod-f[i][j])%=mod;
    rep(i,1,n)rep(j,1,m)if(f[i][j])
        (ans+=qp(j,mod-2)*f[i][j]%mod*m)%=mod;
    printf("%lld",ans);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：i_am_not_feyn (赞：3)

令 $t_i$ 为 $i$ 位置第一次被染色的时间。

$$
\begin{aligned}
ans&=E(\max(t_i))\\
&=\sum_{T}(-1)^{|T|+1}E(\min\limits_{i\in T}(t_i))
\end{aligned}
$$
考虑与 $T$ 相交的区间有 $g(T)$ 个，则一次抽中 $T$ 的概率为 $\dfrac{g(T)}m$，那么 $E(\min(T_i))=\dfrac{m}{g(T)}$。

故考虑 $f(i,j)$ 表示选了 $i$ 以及 $i$ 之前的若干元素，且选到的 $g(T)=j$ 的方案数。

注意到 $i$ 对 $g(T)$ 的影响只与 $i$ 前面最后被选到的元素有关，令 $num_{x}$ 表示 $L\in[x,i],R\in[i,+\infty)$ 的区间个数，则有
$$
f(i,j)=\sum_{k=0}^{i-1}f(k,j-num_{k+1})
$$
最后在状态中加入 01 表示 $-1$ 的贡献即可，复杂度 $O(n^2m)$。

[代码](https://atcoder.jp/contests/abc242/submissions/44703419)。

---

## 作者：UltiMadow (赞：3)

一个暴力的 $\mathcal O(nm\log n)$ 做法（

考虑把求期望转为求概率：$E(t)=\sum_{i\ge 0} P(t>i)$，相当于要求在 $i$ 时刻还存在至少一个点没被覆盖。

考虑容斥，钦定一个点集 $S$ 没被覆盖，记 $f(S)$ 为不包含 $S$ 中的点的区间个数，那么有：
$$
\begin{aligned}
E(t)&=\sum_{i\ge 0}P(t>i)\\
&=\sum_{i\ge 0}\sum_S (-1)^{|S|+1}(\frac{f(S)}{m})^i\\
&=\sum_S (-1)^{|S|+1}\frac{m}{m-f(S)}
\end{aligned}
$$

这个式子可以进行 dp：记 $f_{i,j}$ 为前 $i$ 个数中选了 $j$ 个数的容斥系数和，则有 $f_{i,j}=-\sum_{k<i}f_{k,j-c(k+1,i-1)}$，其中 $c(l,r)$ 表示完全被 $[l,r]$ 包含的区间个数。

这样我们就得到了一个 $\mathcal O(n^2m)$ 的做法，考虑用数据结构维护这个 dp。

按 $i$ 从小到大的顺序 dp，维护 $m$ 棵线段树，第 $j$ 棵线段树维护转移到 $f_{i,j}$ 的所有值，那么不难发现加入一个区间 $[l,r](r<i)$ 时会使第 $j$ 棵线段树中 $[0,l)$ 的位置移到第 $j+1$ 棵线段树中。

这可以直接线段树分裂+合并实现，实际实现中可以线段树上二分找到 $l$ 的位置，若 $l$ 在当前点的左子树则不操作，否则对左子树进行上述的移动操作并递归到右子树中。

时间复杂度 $\mathcal O(nm\log n)$，注意下线段树最好动态开点而不是事先把线段树建好（在 $n,m\le 3000$ 的时候速度大概差了 $5$ 倍（

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 3010
#define MAXM 20000010
#define mod 998244353
#define pb push_back
using namespace std;
int add(int x,int y){return x+y<mod?x+y:x+y-mod;}
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ret=1ll*ret*x%mod;
	return ret;
}
int n,m;
vector<int>qr[MAXN];
int rt[20][MAXN];
struct Segtree{
	int t[MAXM],lc[MAXM],rc[MAXM],tot;
	void pushup(int p){t[p]=add(t[lc[p]],t[rc[p]]);}
	void update(int &p,int l,int r,int pos,int d){
		if(!p)p=++tot;t[p]=add(t[p],d);if(l==r)return;
		int mid=(l+r)>>1;
		if(pos<=mid)update(lc[p],l,mid,pos,d);
		else update(rc[p],mid+1,r,pos,d);
	}
	int query(int p,int l,int r,int L,int R){
		if(L>R)return 0;if(L<=l&&r<=R)return t[p];
		int mid=(l+r)>>1;
		if(R<=mid)return query(lc[p],l,mid,L,R);
		if(L>mid)return query(rc[p],mid+1,r,L,R);
		return add(query(lc[p],l,mid,L,R),query(rc[p],mid+1,r,L,R));
	}
	void split(int dep,int l,int r,int pos){
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid){
			for(int i=0;i<=m;i++)rt[dep+1][i]=lc[rt[dep][i]];
			split(dep+1,l,mid,pos);
		}else{
			for(int i=m-1;i>=0;i--)lc[rt[dep][i+1]]=lc[rt[dep][i]];
			lc[rt[dep][0]]=0;
			for(int i=0;i<=m;i++)rt[dep+1][i]=rc[rt[dep][i]];
			split(dep+1,mid+1,r,pos);
		}
		for(int i=0;i<=m;i++)pushup(rt[dep][i]);
	}
}T;
signed main(){
	scanf("%d%d",&n,&m);n++;
	for(int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		r++;qr[r].pb(l);
	}
	T.update(rt[0][0],0,n,0,1);
	for(int i=1;i<=n;i++){
		for(auto j:qr[i])T.split(0,0,n,j);
		for(int j=0;j<=m;j++)T.update(rt[0][j],0,n,i,mod-T.t[rt[0][j]]);
	}
	int ans=0;
	for(int j=0;j<m;j++){
		int now=T.query(rt[0][j],0,n,n,n);
		ans=(ans+1ll*now*m%mod*qpow(m-j,mod-2)%mod)%mod;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

**update：发现错别字有点多，修改一下。**

考虑最值反演。

由最值反演：

$$E_{\max(S)}=\sum\limits_{T \in S} (-1)^{|T|+1} \times E_{\min(T)}$$

这里 $\max(S)$ 就是所有点中被覆盖的点，其覆盖时刻最晚的时刻。

因为 $N,M \le 400$，所以可以枚举某个区间作为最早覆盖时刻，然后求出其容斥系数贡献。

定义 $dp_{i,j}$ 表示前 $i$ 个数中第 $i$ 个数选（后面 $n-i$ 个数不选），且与 $j$ 个已知区间有交的容斥系数贡献。

设 $f_{l,r}$ 表示 $[l,r]$ 这个区间被已知区间的覆盖次数，$h_i$ 表示 $i$ 这个点被已知区间的覆盖次数。

因为对于含 $i$，不含 $i+1 \sim n$ 的集合的系数贡献可以从前面含 $j$，不含 $j+1 \sim n$ 的集合的系数贡献转移过来。

且如果选了 $i$，所以该项的系数要取反为 $-1$。

从 $j$ 转移过来，即：不管 $1 \sim j-1$，选了 $j$，不选 $j+1 \sim i-1$，选了 $i$，$i+1 \sim n$ 不选。

所以对于第二维要减去覆盖到 $[j+1,i-1]$ 的已知区间数，这个等价于覆盖 $i$ 的区间数加上覆盖 $j$ 的区间数，减去覆盖 $[i,j]$ 的区间数。（即 $k+h_i-f_{i,j}$）

那么状态转移方程为：

$$dp_{i,k+h_i-f_{i,j}}=\sum\limits_{j=0}^{i-1} (-1) \times dp_{j,k}$$

之后答案就好算了，前面说要枚举 $E_{\min(T)}$，即选到有交的某个区间的期望次数，就是 $m$ 个区间选到 $j$ 个区间的其中一个的期望次数为 $\frac{m}{j}$。

所以答案为：

$$\sum\limits_{i=1}^n \sum\limits_{j=0}^m dp_{i,j} \times \frac{m}{j}$$

时间复杂度：$O(N^2 \times M)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=405;
const ll mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1ll) 
		  ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1ll;
    }
    return ans;
}
ll n,m,ans=0;
ll h[N];
ll dp[N][N],f[N][N];
struct Node{
	ll x,y;
}a[N];
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++)
      a[i]={read(),read()};
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        for(int k=1;k<=m;k++)
          if((a[k].x<=i&&i<=a[k].y)&&(a[k].x<=j&&j<=a[k].y)) 
		    f[i][j]++;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++) 
	    h[i]+=(a[j].x<=i&&i<=a[j].y);
    dp[0][0]=mod-1;
    for(int i=1;i<=n;i++)
      for(int j=0;j<=i-1;j++)
        for(int k=0;k<=m;k++)
          dp[i][k+h[i]-f[i][j]]=(dp[i][k+h[i]-f[i][j]]-dp[j][k]+mod)%mod;
    for(int i=1;i<=n;i++)
      for(int j=0;j<=m;j++)
		ans=(ans+(((dp[i][j]*m)%mod)*qpow(j,mod-2))%mod)%mod;
    write(ans);
    return 0;
}
```


---

## 作者：云浅知处 (赞：1)

设 $t_i$ 表示 $i$ 第一次被染色的时间，则答案为 $E[\max\{t_i\}]$。套路地进行 min-max 容斥，有
$$
\mathbb E[\max\{t_i\}]=\sum_{T\subseteq S}(-1)^{|T|+1}\mathbb E[\min_{i\in T}t_i]
$$
考虑怎么算 $E[\min_{i\in T}t_i]$，发现如果能算出与 $T$ 有交的区间 $[L_i,R_i]$ 个数 $x$，那么相当于每次有 $\frac{x}{m}$ 的概率命中，一旦命中就立即结束；因此有 $E[\min(T)]=\frac{m}{x}$。记这个 $x$ 是 $f(T)$。

提前把 $[L_i,R_i]$ 二维前缀和一手，设 $\text{dp}(i,j)$ 表示从前 $i$ 个数中选子集，且必须选 $i$，且 $f(T)=j$ 的方案数，然后枚举上一个选的位置直接 DP 就是 $O(n^2m)$ 的，可以通过。

<https://atcoder.jp/contests/abc242/submissions/41285151>

---

## 作者：tzl_Dedicatus545 (赞：1)

Min-max 容斥。

记 $t_i$ 是 $i$ 被满足的时间，答案是 $\mathbb E[\max\{t_i\}] $

根据 Min-max 容斥，我们有：

$$
\mathbb E[\max\{t_i\}]=\sum_{T\subseteq S}(-1)^{|T|+1}\mathbb E[\min_{i\in T}t_i]
$$
然后最小值的期望就是**第一次被满足的时间**，设一共有 $k$ 个线段与 $S$ 相交，他就是 $\frac mk$。

然后随便 dp。

---

## 作者：piggy123 (赞：0)

Min-Max 容斥做法。

令某种方案中覆盖位置 $i$ 的时间为 $p_i$，题目所求即 $E(\max(p_i))$，容斥一遍得到 $E(\max(p_i))=\sum_{T}(-1)^{|T|+1}E(min_{j\in T}(p_j))$。

接下来考虑这个 $\min$ 怎么求。先考虑对于一个 $T$，设有 $x$ 个线段不包含任何一个关键点，即集合中的点，则答案为 $\sum_{a=0}^{\infty} (a+1)(\frac{x}{m})^a(1-\frac{x}{m})$，组合意义就是枚举选了多少个无意义的，再算出第一次覆盖时间，即 $\min$。

上面这玩意套用几次等比数列求和公式可以得到 $=\frac{1}{1-\frac{x}{n}}$。于是我们发现对于一个集合 $T$，他的具体值不重要了，重要的只有如下几个因素：

1. $|T|$ 的奇偶性
2. 有多少个线段不包含任何一个集合中的点。

然后发现等价类只有 $2m$ 种，暴力动态规划做即可。

AC Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

struct ball{
	ll l,r;
}p[405];
ll cnt[405][405],dp[405][405][2];
const ll mod=998244353;

ll get(ll l,ll r){
	return cnt[r][r]-cnt[l-1][r]-cnt[r][l-1]+cnt[l-1][l-1];
}

ll qkp(ll a,ll k){
	ll ans=1;
	while (k){
		if (k&1)ans*=a,ans%=mod;
		a*=a,a%=mod;
		k>>=1;
	}
	return ans;
}

int main(){
	/*
	max(S)=∑(-1)^{|T|+1}min(T) 
	如何求一个集合的min？
	若有x个都不包含的，则有n-x个至少包含一个的
	∑(x/n)^a(1-x/n)(a+1)=1/(1-x/n)
	*/
	// 那么即计数有多少个子集满足恰好有k个都不包含的,分奇偶 
	// Easy
	ll n,m;
	cin >>n>> m;
	for (ll i=1;i<=m;i++){
		cin >> p[i].l>>p[i].r;
		cnt[p[i].l][p[i].r]++;
	}
	for (ll i=1;i<=n;i++){
		for (ll j=1;j<=n;j++){
			cnt[i][j]+=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
		}
	}
	dp[0][0][0]=1;
	for (ll i=1;i<=n;i++){
		for (ll j=0;j<i;j++){
			ll cnt=get(j+1,i-1);
//			cout<<j+1<<"~"<<i-1<<" --> "<<cnt<< endl;
			for (ll k=cnt;k<=m;k++){
				dp[i][k][0]+=dp[j][k-cnt][1];
				dp[i][k][1]+=dp[j][k-cnt][0];
				dp[i][k][0]%=mod;
				dp[i][k][1]%=mod;
			}
		}
//		for (ll j=0;j<=m;j++){
//			cout<<i<<","<<j<<":"<<dp[i][j][0]<<" "<<dp[i][j][1]<< endl;
//		}
	}
	ll ans=0;
	for (ll i=0;i<=n;i++){
		ll cnt=get(i+1,n);
		for (ll j=0;j<=m;j++){
			ll v=qkp(1-(j+cnt)*qkp(m,mod-2)%mod+mod,mod-2);
//			if (j+cnt==m)v=1;
			if (j+cnt>m)continue;
//			cout<<j+cnt<<":"<<v<<" "<<dp[i][j][1]<<" "<<dp[i][j][0]<< endl;
			ans-=dp[i][j][0]*v%mod;
			ans+=dp[i][j][1]*v%mod;
			ans=(ans+mod)%mod; 
		}
	}
	cout<< ans<< endl;
	return 0;
}
```


---

## 作者：DengDuck (赞：0)

Min-Max 容斥入门题。

对于一种染色方案，我们把所有方格被染色的时间扔进一个集合 $S$。

那么根据 Min-Max 容斥，我们显然有：

$$
\max(S)=\sum_{T\sube S}(-1)^{T+1}\min(T)
$$
根据期望的线性性，有：

$$
E(\max(S))=E(\sum_{T\sube S}(-1)^{T+1}\min(T))\\
E(\max(S))=\sum_{T\sube S}(-1)^{T+1}E(\min(T))\\
$$

显然左边的东西 $S=[1,n]$ 就是我们的答案，那看看右边这个咋求。

对于一个 $T$ 来说，计算它的 $\min(T)$，其实只需要选中一条包含 $T$ 内格子的线段就行，那咋办呢？

那显然我们只需要 DP 来维护，设 $F_{i,j,k}$ 表示最后一项是 $i$，已经选择了 $j$ 个线段，$k$ 个格子的方案数。

等一下，这超时了啊？

我们发现 $i$ 是不可舍去的，$j$ 也是实打实的需要拿去计算，但是 $k$ 好像只关心奇偶性啊？所以我们舍去它，顺便直接把 $-1$ 扔进来吧。

就是说，我们的 $F_{i,j}$ 在转移时，子状态要乘上 $-1$ 系数在转移过来做贡献。
```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=505;
//const LL M;
const LL Mod=998244353;
//const LF eps;
//const LL P;
LL n,m,F[N][N],G[N][N],L[N],R[N],Ans;
void Add(LL &x,LL y){x=(x+y+Mod)%Mod;}
LL Ksm(LL x,LL y)
{
	LL Ans=1;
	while(y)
	{
		if(y&1)Ans=Ans*x%Mod;
		x=x*x%Mod,y>>=1;
	}
	return Ans;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&L[i],&R[i]);
	}
	for(int l=1;l<=n;l++)
	for(int r=l;r<=n;r++)
	for(int i=1;i<=m;i++)
	{
		G[l][r]+=(L[i]<=l&&l<=R[i])&&(L[i]<=r&&r<=R[i]);
	}
	F[0][0]=Mod-1;
	for(int i=1;i<=n;i++)
	for(int j=0;j<=i-1;j++)
	for(int k=0;k<=m;k++)
	{
		Add(F[i][k+G[i][i]-G[j][i]],Mod-F[j][k]);
	}
	for(int i=1;i<=n;i++)
	for(int j=0;j<=m;j++)
	{
		Add(Ans,F[i][j]*m%Mod*Ksm(j,Mod-2)%Mod);
	}
	printf("%lld\n",Ans);
	return 0;
}
//RP++
```

---

## 作者：Zi_Gao (赞：0)

发现对于某一种情况的操作，操作次数取决于最后一个被染色的方块，根据套路考虑 min-max 容斥，记随机变量 $t_i$ 表示抽到第 $i$ 张卡的时间。

$$
\begin{aligned}
Ans&=E\left(\max\left\{t_i\right\}\right)\\
&=\sum_{S\subset U} \left(-1\right)^{\left|S\right|+1}\min\left(S\right)
\end{aligned}
$$

然后考虑如何计算 $\min\left(S\right)$，那么在第一个这里面的格子被染色前，染色的格子只能宣导 $S$ 以外的，记 $cnt_S$ 表示和 $S$ 相交的区间的个数，所以期望就是 $E\left(\min\left(S\right)\right)=\frac{m}{cnt_S}$。直接子集枚举显然做不了，于是考虑记一个 $dp_{i,j}$ 表示考虑了前 $i$ 个格子，选到 $cnt_S=j$ 的所有集合的**带系数**和，为了方便写出转移式子，记 $f_{i,j}$ 表示 $L\in\left[i,j\right],R\in\left[j,n\right]$ 的区间个数。

$$
dp_{i,j}=-\sum_{k=0}^{i-1}dp_{k,j-f_{k+1,i}}
$$

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define MODINT_TYPE long long

namespace MODINT{
	unsigned long long d;
    __uint128_t m;
    const unsigned int barK=64;
    void init(long long mod){
        m=(((__uint128_t)1)<<barK)/(d=mod);
        return;
    }

    inline unsigned long long mod(register unsigned long long x){
        register unsigned long long w=(m*x)>>barK;
        w=x-w*d;
        return w>=d?w-d:w;
    }

    MODINT_TYPE exgcd(MODINT_TYPE a,MODINT_TYPE b,MODINT_TYPE &x,MODINT_TYPE &y){
        if(!b){
            x=1;
            y=0;
            return a;
        }
        MODINT_TYPE d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    MODINT_TYPE inv(MODINT_TYPE n,MODINT_TYPE p){
        MODINT_TYPE x,y;
        exgcd(n,p,x,y);
        x%=p;
        return x>=0?x:x+p;
    }

    struct MODNUM{
        MODINT_TYPE val;
        MODNUM(MODINT_TYPE x){
            if(x<0){
                val=d-mod(-x);
                if(val>=d) val-=d;
            }else val=mod(x);
            return;
        }
        MODNUM(){val=0;}
        inline MODNUM operator + (const MODNUM& o) const{return (MODNUM){(val+o.val>=d)?(val+o.val-d):(val+o.val)};}
        inline MODNUM operator + (const MODINT_TYPE& o) const{return *this+MODNUM(o);}
        inline MODNUM operator - (const MODNUM& o) const{return (MODNUM){(val-o.val<0)?(val-o.val+d):(val-o.val)};}
        inline MODNUM operator - (const MODINT_TYPE& o) const{return *this-MODNUM(o);}
        inline MODNUM operator * (const MODNUM& o) const{return (MODNUM){mod(val*o.val)};}
        inline MODNUM operator * (const MODINT_TYPE& o) const{return *this*MODNUM(o);}
        inline MODNUM operator / (const MODNUM& o) const{return (MODNUM){mod(val*inv(o.val,d))};}
        inline MODNUM operator / (const MODINT_TYPE& o) const{return *this/MODNUM(o);}

        inline MODNUM operator ++(){
            ++val;
            if(val>=d) val-=d;
            return *this;
        }
        inline MODNUM operator ++(const int){
            MODNUM tmp=*this;
            ++val;
            if(val>=d) val-=d;
            return tmp;
        }
        inline MODNUM operator --(){
            --val;
            if(val<0) val+=d;
            return *this;
        }
        inline MODNUM operator --(const int){
            MODNUM tmp=*this;
            --val;
            if(val<0) val+=d;
            return tmp;
        }

        inline MODNUM& operator += (const MODNUM& o) {return *this=*this+o;}
        inline MODNUM& operator += (const MODINT_TYPE& o) {return *this=*this+o;}
        inline MODNUM& operator -= (const MODNUM& o) {return *this=*this-o;}
        inline MODNUM& operator -= (const MODINT_TYPE& o) {return *this=*this-o;}
        inline MODNUM& operator *= (const MODNUM& o) {return *this=*this*o;}
        inline MODNUM& operator *= (const MODINT_TYPE& o) {return *this=*this*o;}
        inline MODNUM& operator /= (const MODNUM& o) {return *this=*this/o;}
        inline MODNUM& operator /= (const MODINT_TYPE& o) {return *this=*this/o;}

        operator MODINT_TYPE(){
            return val;
        }
    };
};

MODINT::MODNUM dp[410][410],cnt[410];
std::vector<int> rpos[410];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    MODINT::init(998244353);

    register int i,j,k,l,r;
    register MODINT::MODNUM res=0;
    int n=read();
    int m=read();

    for(i=0;i<m;++i){
        l=read();r=read();
        rpos[l].push_back(r);
    }

    dp[0][0]=-1;
    for(i=1;i<=n;++i){
        for(j=i;j;--j){
            cnt[j]=cnt[j+1];
            for(auto r:rpos[j]) cnt[j]+=(r>=i);
        }
        for(j=1;j<=m;++j)
            for(k=0;k<i;++k)
                if(j-cnt[k+1]>=0)
                    dp[i][j]-=dp[k][j-cnt[k+1]];
        for(j=1;j<=m;++j) res+=dp[i][j]/j;
    }

    print(res*m);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：Graphcity (赞：0)

考虑 min-max 容斥，我们需要求出对于每个方块集合 $T$，其中至少有一个元素被覆盖时的期望次数。容易发现，这个期望次数只跟包含这些元素的区间数量有关。正难则反，设 $f_{i,j}$ 表示选择方块 $i$，有 $j$ 个区间 **没有覆盖** 方块集合的容斥系数之和。设 $cnt_p$ 表示被区间 $(p,i)$ 完全包含的区间个数，则有：
$$
f_{i,j}=-\sum_{p<i}f_{p,j-cnt_p}
$$
初始值 $f_{0,0}=1$，终止状态为 $f_{n+1}$。朴素转移是 $O(n^2m)$ 的。

考虑直接维护 $f_i$ 这个多项式。每次我们需要支持区间 $\times x$ 和区间求和，直接用线段树维护可以做到 $O(nm\log n)$。

最终答案就是 $\sum_{i=1}^mf_{n+1,m-i}\dfrac{m}{i}$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=400,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,L[Maxn+5],R[Maxn+5];
int f[Maxn+5][Maxn+5],cnt[Maxn+5];
vector<int> v[Maxn+5];

int main()
{
    cin>>n>>m;
    For(i,1,m) cin>>L[i]>>R[i];
    For(i,1,m) v[R[i]].push_back(L[i]);
    f[0][0]=1;
    For(i,1,n+1)
    {
        for(auto j:v[i-1]) For(k,0,j-1) cnt[k]++;
        For(j,0,i-1) For(k,0,m-cnt[j])
            f[i][k+cnt[j]]=(f[i][k+cnt[j]]-f[j][k]+Mod)%Mod;
    }
    int ans=0;
    For(i,0,m-1)
    {
        int k=1ll*m*Pow(m-i,Mod-2)%Mod;
        ans=(ans+1ll*f[n+1][i]*k)%Mod;
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：HBWH_zzz (赞：0)

# [[ABC242Ex] Random Painting](https://atcoder.jp/contests/abc242/tasks/abc242_h)

>给定 $m$ 条线段，每次随机在 $m$ 条线段中选择一个，求覆盖 $[1,n]$ 时的期望次数。$n,m\leq 400$。

$f_i$ 表示在 $m$ 个线段中选恰好 $i$ 个使得这些线段的并为 $[1,n]$。

将线段按照 $L_i$ 升序排序。设 $dp_{i,j,k}$ 表示选前第 $i$ 条线段，覆盖了 $[1,j]$，恰好用了 $k$ 条的方案数。则有：
$$
dp_{i,j,k}=\begin{cases}
  \text{if } j< R_i, & dp_{i-1,j,k}
  \\
  \text{if } j=R_i, & dp_{i-1,j,k}+\sum\limits_{l=L_i-1}^{R_i}dp_{i-1,l,k-1}
  \\
  \text{if } j>R_i, & dp_{i-1,j,k-1}+dp_{i-1,j,k}
\end{cases}.
$$
由于中间只有 $j=R_i$ 时需要用到约为 $O(n)$ 的求和，所以总的 dp 复杂度是 $O(m^2n)$ 的。

那么原题的答案就是：在选出的集合大小为 $|S|$ 时没有覆盖 $[1,n]$ 的概率乘上选出一个新的元素的期望次数的加和。即：
$$
\sum_{i=0}^m\frac{\binom{m}{i}-dp_{m,n,i}}{\binom{m}{i}}\times\frac{m}{m-i}.
$$
所以最后的瓶颈在于 $O(m^2n)$ 的 dp 部分。[代码](https://atcoder.jp/contests/abc242/submissions/38113213)

理论上官方题解里有个 $O(m^2\log n)$ 的奇妙做法，但是暂时没有看懂，所以暂时咕掉了。

---

