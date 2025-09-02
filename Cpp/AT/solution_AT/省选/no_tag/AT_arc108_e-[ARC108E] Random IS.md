# [ARC108E] Random IS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_e

$ N $ 脚のイスが左から右に並んでいます。 左から $ i $ 番目のイスのIDは $ a_i $ です。ここで、$ a_i $ がすべて相異なることが保証されます。

すぬけ君は何脚かのイスに印をつけ、印をつけたイス以外を捨てることにしました。はじめ、どのイスにも印はついていません。 印のついたイスたちのIDが左から右に単調増加になっているような印のつけ方を *よい印のつけ方* と呼びます。

すぬけ君は以下の手続きに従って印をつけることにしました。

1. イス $ x $ に新たに印をつけても印のつけ方がよい印のつけ方のままであるとき、イス $ x $ を *良いイス* とする。現在の良いイスの脚数を $ k $ とする
2. $ k=0 $ なら印のついていないイスを取り除き手続きを終了する。そうでないなら、$ k $ 脚の良いイスから等確率で $ 1 $ つを選んで印をつけ手順 1 へ戻る

手続き終了時に残るイスの脚数の期待値が有理数になることが証明できます。その値を $ P/Q $ (既約分数)とします。また $ M=10^{9}+7 $ とします。このとき、$ 0 $ 以上 $ M-1 $ 以下の整数 $ R $ がただ一つ存在して $ P\ \equiv\ Q\ \times\ R\ \pmod{M} $ となることが証明でき、その値は $ P\ \times\ Q^{-1}\ \pmod{M} $ と等しくなります。ここで、$ Q^{-1} $ はモジュラ逆数です。$ R $ を求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ a_i\ \leq\ N $
- $ a_i $ はすべて相異なる

### Sample Explanation 1

\- はじめにイス $ 1 $(IDが $ 1 $ のイスです) に印がついたとき、最終的に残るイスはイス $ 1,2 $ の $ 2 $ 脚です。 - はじめにイス $ 2 $ に印がついたとき、最終的に残るイスはイス $ 1,2 $ の $ 2 $ 脚です。 - はじめにイス $ 3 $ に印がついたとき、最終的に残るイスはイス $ 3 $ の $ 1 $ 脚です。 - イスは等確率で選ばれるので手続き終了時に残るイスの脚数の期待値は $ \frac{5}{3} $ となります。$ 5\ \equiv\ 3\ \times\ 666666673\ \pmod{M} $ より、$ R=666666673 $ です。

## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
666666673```

## 样例 #2

### 输入

```
30
26 16 28 30 23 11 29 18 22 15 20 13 27 9 21 7 5 25 4 19 8 3 1 24 10 14 17 12 2 6```

### 输出

```
297703424```

# 题解

## 作者：intel_core (赞：11)

如果考虑以时间轴 $\text{DP}$，会发现即使是最终方案相同，标记顺序不同会导致概率不同。所以需要换一种方式 $\text{DP}$。

注意到若 $a_l,a_r$ 都被选定，那么对于 $l\le i \le r,a_l\le a_i\le a_r$ 的 $a_i$ 来讲，单独考虑 $[l,r]$ 内和整体考虑两种方式下，$a_i$ 成为 $[l,r]$ 内下一个被选中的概率是一样的。

基于上述结论，我们可以考虑区间 $\text{DP}$。令 $f_{l,r}(l<r)$ 表示当前已经选定 $a_l,a_r$ 后，在 $[l,r]$ 中期望还能选出数的个数。同时，我们记 $g_{l,r}$ 表示 $l\le i \le r , a_l\le a_i \le a_r$ 的 $i$ 的个数。

直接枚举中间点 $x$ 即可轻松转移：$f_{l,r}=\frac{\sum_{l\le x\le r,a_l\le a_x\le a_r}f_{l,x}+f_{x,r}}{g_{l,r}}+1$。

以上做法复杂度显然为 $O(n^3)$，考虑优化。

不难发现转移的求和式为一个值域范围内的求和，所以我们可以把 $\sum f_{l,x}$ 和 $\sum f_{x,r}$ 分别用树状数组维护。同时，$g_{l,r}$ 也可以在区间 $\text{DP}$ 的过程中用树状数组维护。

单次转移复杂度 $O(\log n)$，总复杂度 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e3+10;
const int MOD=1e9+7;
#define int long long
int n,a[NR],f[NR][NR];
void add(int &x,int y){x=(x+y)%MOD;} 

int quickpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=(res*x)%MOD;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}
int Inv(int x){return quickpow(x,MOD-2);}

struct BIT{
	int c[NR];
	int lowbit(int x){
		return x&(-x);
	}
	void modify(int x,int y){
		while(x<=n){
			add(c[x],y);
			x+=lowbit(x); 
		}
	}
	int ask(int x){
		int res=0;
		while(x){
			add(res,c[x]);
			x-=lowbit(x);
		}
		return res; 
	}
	int calc(int l,int r){
		if(l>r)return 0;
		return ask(r)-ask(l-1);
	}
}T[NR],t1[NR],t2[NR];

signed main(){
	cin>>n;
	for(int i=2;i<=n+1;i++)cin>>a[i],a[i]++;
	a[1]=1;a[n+2]=n+2;n+=2;
	for(int i=1;i<n;i++)T[i].modify(a[i+1],1);
	for(int len=2;len<n;len++)
		for(int l=1,r;l<=n-len;l++){
			r=l+len;
			int sum=T[l].calc(a[l]+1,a[r]-1);
			if(sum>0)
				f[l][r]=(t1[l].calc(a[l]+1,a[r]-1)+t2[r].calc(a[l]+1,a[r]-1))*Inv(sum)%MOD+1;
			T[l].modify(a[r],1);
			t1[l].modify(a[r],f[l][r]);t2[r].modify(a[l],f[l][r]);
		}
	cout<<(f[1][n]+MOD)%MOD<<endl;
	return 0;
} 
```

---

## 作者：5ab_juruo (赞：3)

对于一段区间，如果两个端点都选中了，则中间的期望和外面就没有任何关系了。设 $f(i,j)$ 为选中 $i$ 和 $j$ 的时候，$(i,j)$ 的答案。为了方便，在整个序列前加上 $-\infty$，在末尾加上 $\infty$。

设 $cnt=\sum_{i<k<j}[a_i<a_k<a_j]$，则：

$$f(i,j)=1+\frac{1}{cnt}\sum_{i<k<j\land a_i<a_k<a_j}f(i,k)+f(k,j)$$

直接做的复杂度是 $\mathcal{O}(n^3)$ 的，考虑优化。枚举时固定 $i$ 向右枚举 $j$。需要维护：

- 当前区间内满足 $a_i<a_k<a_j$ 的 $k$ 个数；
- 当前区间内满足 $a_i<a_k<a_j$ 的 $k$ 的 $\sum f(i,k)$；
- 当前区间内满足 $a_i<a_k<a_j$ 的 $k$ 的 $\sum f(k,j)$。

用权值树状数组维护，每次 $j$ 右移时插入 $f(k,j)$ 和 $f(i,j)$，复杂度 $\mathcal{O}(n^2\log n)$。

```cpp
const int max_n = 2000, mod = int(1e9) + 7;

// mod_int 是自动取模的整数类型
using mint = mod_int<mod>;

inline int lowbit(int x) { return x & -x; }
struct fwt
{
	mint tr[max_n + 3];
	int n;
	
	void init(int _n)
	{
		n = _n;
		fill(tr, tr + n + 1, 0);
	}
	void add(int x, int v)
	{
		for (x++; x <= n; x += lowbit(x))
			tr[x] += v;
	}
	mint get(int x)
	{
		mint ret = 0;
		for (x++; x; x -= lowbit(x))
			ret += tr[x];
		return ret;
	}
	mint get(int x, int y)
	{
		if (x > y)
			return 0;
		return get(y) - get(x - 1);
	}
} tr[max_n + 2], gcnt, kv;

mint dp[max_n + 2][max_n + 2];
int a[max_n + 2];

void Init()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
}

signed main()
{
	Init();
	
	int n;
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	a[0] = 0, a[n + 1] = n + 1;
	for (int i = 0; i <= n + 1; i++)
		tr[i].init(n + 2);
	for (int i = n; i >= 0; i--)
	{
		gcnt.init(n + 2);
		kv.init(n + 2);
		for (int j = i + 1; j < n + 2; j++)
		{
			int cnt = gcnt.get(a[i], a[j]).val();
			gcnt.add(a[j], 1);
			if (!cnt)
				continue;
			dp[i][j] = (kv.get(a[i], a[j]) + tr[j].get(a[i], a[j])) / cnt + 1;
			kv.add(a[j], dp[i][j].val());
			tr[j].add(a[i], dp[i][j].val());
		}
	}
	
	cout << dp[0][n + 1] << endl;
	
	return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

这个题有一点深刻的，思考。

发现按照时间加入其实是个很不明智的选择，但是这个 $\frac{1}{k}$ 的概率很容易让人陷入全局决策的思维定势。

但是如果我们放到一个局部来考虑，假设目前有两个相邻的已经选出的元素 $x<y$，那么 $[x+1,y-1]$ 之间满足 $a_x<a_i<a_y$ 的所有元素 $i$ 作为 $[x,y]$ 内下一次被选中的概率和只考虑 $[x,y]$ 这段区间，外面全部删除，下一次选中 $i$ 的概率是相同的，因此每一段内部就变成了独立的子问题。

有了这个思想原问题就很简单了。在开头结尾加入 $a_0=0,a_{n+1}=n+1$，设 $f_{l,r}$ 表示目前有一段相邻的两个端点为 $[l,r]$，内部期望再选出多少个元素。转移枚举下一个被选到的位置 $i$，$f_{l,r}=\frac{1}{c}\sum\limits_{i=l+1}^{r-1}[a_l<a_i<a_r](f_{l,i}+f{i,r}+1)$，其中 $c$ 表示合法转移数量。如果你不明白为什么中间是 $+$ 而非 $\times$，请重新阅读上一段。

暴力做是 $\mathcal O(n^3)$ 的，显然可以用树状数组优化到 $\mathcal O(n^2\log n)$，于是这题就被解决了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e3+9,Mod=1e9+7;
ll n,a[N],dp[N][N],s[N][N],cnt[N][N],inv[N];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
ll bit[2][N][N];
void Upd(ll id,ll r,ll x,ll k){
    x++;
    while(x<=n+2)bit[id][r][x]=(bit[id][r][x]+k)%Mod,x+=(x&(-x));
}
ll Query(ll id,ll r,ll x){
    x++;
    ll res=0;
    while(x)res=(res+bit[id][r][x])%Mod,x-=(x&(-x));
    return res;
}
ll Query(ll id,ll r,ll u,ll v){
    return (Query(id,r,v)-Query(id,r,u-1)+Mod)%Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    rep(i,1,n)inv[i]=pw(i,Mod-2);
    a[0]=0,a[n+1]=n+1;
    rep(i,0,n+1)s[0][i]=1;
    rep(i,1,n+1){
        rep(j,0,n+1)s[i][j]=s[i-1][j];
        rep(j,a[i],n+1)s[i][j]++;
    }
    rep(i,0,n+1){
        rep(j,i+1,n+1){
            if(a[i]<a[j])cnt[i][j]=s[j][a[j]-1]-s[j][a[i]]-(i?s[i-1][a[j]-1]-s[i-1][a[i]]:0ll);
        }
    }
    rep(len,3,n+2){
        rep(l,0,n+1-len+1){
            ll r=l+len-1,c=cnt[l][r];
            if(a[l]>a[r]||!c)continue;
            ll s=(Query(0,l,a[l],a[r])+Query(1,r,a[l],a[r]))%Mod;
            dp[l][r]=(s*inv[c]+1)%Mod;
            Upd(0,l,a[r],dp[l][r]),Upd(1,r,a[l],dp[l][r]);
        }
    }
    write(dp[0][n+1]);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：翼德天尊 (赞：2)

~~考虑最终标记方案一定是原序列中一个极大的上升子序列，设长度为 $x$，则显然我们一共有 $x!$ 种顺序将其标记。~~

~~故不妨设 $dp_{i,j}$ 表示前 $i$ 个数中，极大上升子序列长度为 $j$，且强制选择第 $i$ 个数的方案数，$g_{i,j}$ 表示该情况下的总贡献，最后除一下即可。~~

~~转移时枚举 $i$ 前的决策 $k$，判断 $a_i$ 是否为 $[k+1,i]$ 中的最小值，若是则可以进行转移，总时间复杂度 $O(n^3)$。~~

~~考虑优化转移，利用值域树状数组辅助转移，时间复杂度 $O(n^2\log n)$。~~

> 每次均匀选取标记。

假了，因为每种方案的概率不同。

好吧，看来从选取结果来推期望这条路是行不通了，那我们就考虑对选取过程进行 dp。

发现该选取过程是满足区间可划分性的，即如果我们已经选取了 $a_l,a_r$，要在区间 $[l+1,r-1]$ 中均匀选择一个满足 $a_l<a_i<a_r$ 的 $a_i$，则选取过后，整个区间就被我们分成了两段，也就是被我们变成了两个子问题。于是就会想到区间 dp 了！

设 $dp_{i,j}$ 表示强制选择 $a_i,a_j$ 时区间 $[i+1,j-1]$ 的答案，$g_{i,j}$ 表示 $[l,r]$ 内满足 $a_l<a_s<a_r$ 的 $s$ 的个数，则有转移方程：
$$
dp_{i,j}=\frac{\sum_{s=l+1}^{r-1}[a_i<a_s<a_r]dp_{i,s}+dp_{s,j}}{g_{i,j}}+1
$$
注意当 $g_{i,j}=0$ 时需要特判 $dp_{i,j}=0$。此时时间复杂度 $O(n^3)$。考虑优化。

观察到式子的主要部分是求和式，考虑将其拆开，看看能不能快速维护：

- $\sum_{s=l}^r[a_l<a_s<a_r]dp_{l,s}$
- $\sum_{s=l}^r[a_l<a_s<a_r]dp_{s,r}$
- $g_{l,r}$

先考虑第一个式子。发现这其实是一个二维偏序问题，于是我们可以开 $n$ 个树状数组，每次处理完 $[l,r]$ 时动态地将 $dp_{l,r}$ 加入第 $l$ 个树状数组的第 $a_r$ 项，以此消掉一维，转移时在左端点树状数组中区间查询第二维即可。第二、三个式子同理。

于是复杂度就变成 $O(n^2\log n)$ 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
const int mod=1e9+7;
int n,a[N];
ll dp[N][N];
struct BIT{
    ll c[N][N];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int o,int x,ll k){
        for (int i=x;i<=n+2;i+=lowbit(i))
            c[o][i]=(c[o][i]+k)%mod;
    }
    ll Query(int o,int x){
        ll ans=0;
        for (int i=x;i;i-=lowbit(i))
            ans=(ans+c[o][i])%mod;
        return ans;
    }
    ll query(int o,int l,int r){
        return (Query(o,r)-Query(o,l-1)+mod)%mod;
    }
}A,B,C;
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}
ll ksm(ll x,ll y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	n=read();
    for (int i=1;i<=n;i++) a[i]=read()+1;
    a[0]=1,a[n+1]=n+2;
    for (int i=0;i<=n;i++) 
        C.add(i,a[i+1],1);
    for (int len=3;len<=n+2;len++){
        for (int l=0;l<=n+2-len;l++){
            int r=l+len-1;
            if (a[l]>a[r]) continue;
            // cout<<l<<" "<<r<<"\n";
            ll x=C.query(l,a[l],a[r]);
            if (x>0) dp[l][r]=((A.query(l,a[l],a[r])+B.query(r,a[l],a[r]))*ksm(x,mod-2)%mod+1)%mod;
            // cout<<A.query(l,a[l],a[r])<<"\n";
            // cout<<B.query(r,a[l],a[r])<<" "<<C.query(l,a[l],a[r])<<"\n";
            A.add(l,a[r],dp[l][r]),B.add(r,a[l],dp[l][r]),C.add(l,a[r],1);
            // cout<<l<<" "<<r<<" "<<dp[l][r]<<"\n";
        }
    }
    cout<<dp[0][n+1]<<"\n";
	return 0;
}
```

---

## 作者：harmis_yz (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

考虑区间 DP。

定义状态函数 $f_{l,r}$ 表示钦定选择了 $a_l,a_r(a_l<a_r)$ 时，区间 $(l,r)$ 还能选择的期望数量。则有：$f_{l,r}=1+\frac{1}{k}\times \sum\limits_{l < p < r\land a_l < a_p < a_r}^{}f_{l,p}+f_{p,r}$。其中 $k$ 表示 $p$ 的数量。不难发现，$\sum$ 中的二者独立。所以当我们枚举 $l$ 后枚举 $r$ 时，我们可以通过任意方式快速得到 $k$，$\sum\limits_{l < p < r\land a_l < a_p <a_r}^{}f_{l,p}$ 和 $\sum\limits_{l < p < r\land a_l < a_p <a_r}^{}f_{p,r}$。然后加起来就行了。使用树状数组的时间复杂度是 $O(n^2\log n)$ 的。

## 代码

```cpp
il void solve(){
	n=rd,a[0]=0,a[n+1]=n+1;
	for(re int i=1;i<=n;++i) a[i]=rd;
	for(re int l=n;l>=0;--l)
	for(re int r=l+1;r<=n+1;++r){
		c[l][r]=cnt[l].Ans(a[l],a[r]);
		cnt[l].add(a[r],1);
	}
	for(re int l=n;l>=0;--l)
	for(re int r=l+1;r<=n+1;++r){
		int Sum=(pre[r].Ans(a[l],a[r])+nxt[l].Ans(a[l],a[r]))%p;
		if(c[l][r]) f[l][r]=(Sum*qmi(c[l][r],p-2,p)%p+1)%p;
		pre[r].add(a[l],f[l][r]);
		nxt[l].add(a[r],f[l][r]);
	}
	printf("%lld\n",f[0][n+1]);
    return ;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑 $dp_{i,j}$ 表示 $[i,j]$ 区间期望打多少个标记。

首先求出 $a_i<a_p<a_j$ 且 $i<p<j$ 的 $a_p$ 数量，设为 $k$。则：

$$dp_{i,j}=\dfrac{\displaystyle\sum_{a_i<a_p<a_j,\ i<p<j}(dp_{i,p-1}+dp_{p+1,j})}{k}+1$$

用树状数组维护 $x<t$ 的 $dp_{i,x}$ 和 $x>t$ 的 $dp_{x,j}$ 即可 $O(n\log n)$ 转移。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int a[2005],dp[2005][2005];
struct bit{
	int f[2005];
	void init(){
		memset(f,0,sizeof(f));
	}
	void add(int pos,int x){
		pos++;
		while(pos<=2003){
			f[pos]+=x;
			pos+=lowbit(pos);
		}
	}
	int qry(int pos){
		pos++;
		int ans=0;
		while(pos){
			ans+=f[pos];
			pos-=lowbit(pos);
		}
		return ans%mod;
	}
}treer[2005],treel,treec;
signed main(){
	int n; cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
	n++; a[n]=n;
	for(int i=n-1;i>=0;i--){
		treel.init();
		treec.init();
		for(int j=i+1;j<=n;j++){
			if(a[j]<a[i]) continue;
			dp[i][j]=(treel.qry(a[j])+(treer[j].qry(n)+mod-treer[j].qry(a[i])))*qp(treec.qry(a[j]),mod-2)%mod;
			if(!treec.qry(a[j])) dp[i][j]=1;
			treel.add(a[j],dp[i][j]);
			treec.add(a[j],1);
			treer[j].add(a[i],dp[i][j]);
			// cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
		}
	}
	cout<<dp[0][n]-1;
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

注意到选择的椅子会把内部和外部分隔，所以考虑区间 DP。

设 $f_{i,j}$ 为选择了 $i,j$ 两把椅子后 $(i,j)$ 内还能选的椅子期望个数。

枚举选择的第一把椅子 $k$，则有 $\frac{\sum_{i<k<j,a_i<a_k<a_j}f_{i,k}+f_{k,j}}{\sum_{i<k<j}[a_i<a_k<a_j]}$。

考虑用 BIT 优化，倒着扫 $i$ 正着扫 $j$ 即可动态维护。时间复杂度 $O(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=2005;
ll ksm(ll a,ll b,ll p){
    a=a%p;
    ll r=1;
    while(b){
        if(b&1)r=r*a%p;
        a=a*a%p;
        b>>=1;
    }
    return r%p;
}
int n,a[N];
ll f[N][N];
struct DS1{
    int lb(int x){
        return x&(-x);
    }
    ll tr[N];
    void clr(int n){
        rep(i,1,n)tr[i]=0;
    }
    void add(int i,ll x){
        for(;i<=n;i+=lb(i))tr[i]=(tr[i]+x)%mod;
    }
    ll q(int i){
        ll r=0;
        for(;i;i-=lb(i))r=(r+tr[i])%mod;
        return r;
    }
    ll Q(int l,int r){
        if(l>r)return 0;
        return (q(r)-q(l-1)+mod)%mod;
    }
}tr1,tr2,ts[N];
void slv(){
	scanf("%d",&n);
    n+=2,a[1]=1,a[n]=n;
    rep(i,2,n-1)scanf("%d",&a[i]),a[i]++;
    per(i,n,1){
        tr1.clr(n);
        tr2.clr(n);
        rep(j,i,n){
            int c=tr1.Q(a[i]+1,a[j]-1);
            ll s=(tr2.Q(a[i]+1,a[j]-1)+ts[j].Q(a[i]+1,a[j]-1))%mod;
            if(c)f[i][j]=(s*ksm(c,mod-2,mod)%mod+1)%mod;
            tr1.add(a[j],1);
            tr2.add(a[j],f[i][j]);
        }
        rep(j,i,n)ts[j].add(a[i],f[i][j]);
    }
    printf("%lld\n",f[1][n]);
}
void main(){
	int T=1;
//	int csid=0;scanf("%d",&csid);
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

如果确定两个点 $x, y$ 满足 $x, y$ 都被选定且 $x < y$，那么 $(x, y)$ 之间选点的贡献独立于全局，这是因为外界不可能有比 $a_x$ 和 $a_y$ 更紧的值域限制，并且 $(x, y)$ 之内早晚都要选，因此可以和外界拆开看待。

容易写出区间 DP 如下：

```cpp
inline int solve(int l, int r)
{
	if(f[l][r] != -1) return f[l][r];
	f[l][r] = 0; int cnt = 0;
	for(int i = l + 1; i < r; ++i)
	{
		if(a[l] < a[i] && a[i] < a[r])
		{
			++cnt;
			f[l][r] = (1ll * f[l][r] + 1 + solve(l, i) + solve(i, r)) % mod;
		}
	}
	f[l][r] = f[l][r] * Inv(cnt) % mod; return f[l][r];
}
```

因为没有卷积环节，所以可以让 $r - l + 1 : 1 \to \max$，即按照区间长度顺序填表法 DP，用数据结构优化。数据结构部分是简单的二维偏序问题，树状数组即可胜任。

```cpp
 /* NE_Cat 4.0 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 2010, mod = 1e9 + 7;
int n, a[N]; long long f[N][N];
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b) {if(b & 1) res = res * a % mod; b >>= 1, a = a * a % mod;}
	return res;
}

struct BIT
{
	long long c[N];
	inline void add(int pos, long long num)
	{for(int i = pos; i <= n + 1; i += lowbit(i)) c[i] = (c[i] + num) % mod;}
	inline long long ask(int pos)
	{
		long long res = 0;
		for(int i = pos; i; i -= lowbit(i)) res = (res + c[i]) % mod;
		return res;
	}
	inline long long query(int l, int r)
	{if(l > r) return 0; return (ask(r) - ask(l - 1) + mod) % mod;}
}; BIT T[3][N];

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	a[0] = 0, a[n + 1] = n + 1;
	for(int len = 2; len <= n + 2; ++len)
	{
		for(int l = 0; l + len - 1 <= n + 1; ++l)
		{
			int r = l + len - 1;
			if(a[l] < a[r])
			{
				f[l][r] = (f[l][r] + T[0][l].query(a[l] + 1, a[r] - 1)) % mod;
				f[l][r] = (f[l][r] + T[1][r].query(a[l] + 1, a[r] - 1)) % mod;
				int cnt = T[2][l].query(a[l] + 1, a[r] - 1); f[l][r] = (f[l][r] + cnt) % mod;
				f[l][r] = f[l][r] * qpow(cnt, mod - 2) % mod;
				if(r <= n) T[0][l].add(a[r], f[l][r]);
				if(l >= 1) T[1][r].add(a[l], f[l][r]);
				if(r <= n) T[2][l].add(a[r], 1);
			}
		}
	}
	cout << f[0][n + 1] << '\n';
	return 0;
}
/*

*/
```

---

## 作者：Purslane (赞：0)

# Solution

考虑现在已经选取了 $i_1 < i_2 < \cdots < i_k$ 这些下标。

容易发现，我们可以将剩余的序列化为 $(0,i_1)$、$(i_1,i_2)$、$\cdots$、$(i_{k-1},i_k)$、$(i_k,n+1)$ 等很多段。

发现每一段内所有位置被选择的概率是均等的，因此划分成了很多子问题。

于是设 $dp_{l,r}$ 表示，当前段的端点是 $l$ 和 $r$，期望能增加多少数。

如果 $\exists l < u < r$ 使得 $a_l < a_u < a_r$，转移为

$$
dp_{l,r} = 1 + \dfrac{\sum_{l < u < r,a_l < a_u < a_r} dp_{l,u}+dp_{u,r}}{\sum_{l<u < r,a_l < a_u < a_r}1} 
$$

否则，$dp_{l,r}=0$。

容易使用树状数组优化到 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD=1e9+7;
int n,a[MAXN],dp[MAXN][MAXN],inv[MAXN];
struct BIT {
	vector<int> vc;
	void init(void) {return vc.resize(n+2),void();}
	void update(int pos,int v) {
		while(pos<=n) vc[pos]=(vc[pos]+v)%MOD,pos+=pos&-pos;
		return ;	
	}
	int query(int pos) {
		int ans=0;
		while(pos) ans=(ans+vc[pos])%MOD,pos-=pos&-pos;
		return ans;
	}
}s1[MAXN],s2[MAXN],s3[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	a[0]=0,a[n+1]=n+1;
	ffor(i,0,n+1) s1[i].init(),s2[i].init(),s3[i].init();
	ffor(i,1,n) inv[i]=qpow(i,MOD-2);
	ffor(i,0,n) if(a[i]<a[i+1]) if(i+1!=n+1) s1[i].update(a[i+1],1);
	ffor(len,3,n+2) for(int l=0,r=len-1;r<=n+1;l++,r++) if(a[l]<a[r]) {
		int cnt=s1[l].query(a[r]-1);
		if(cnt) dp[l][r]=(s2[l].query(a[r]-1)+s3[r].query(n-a[l]))%MOD*inv[cnt]%MOD+1;
		if(r!=n+1) s1[l].update(a[r],1),s2[l].update(a[r],dp[l][r]);
		if(l) s3[r].update(n-a[l]+1,dp[l][r]);
	}
	cout<<dp[0][n+1]%MOD;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 前言
有一位大佬的互测题中选到了这道题，赛时想出了 $n^3$ 却没想出优化，~~废了~~。
# 思路
发现如果只正着做会有后效性所以考虑区间 dp，我们定义 $f_{i,j}$ 表示区间 $i\sim j$ 中选了 $i,j$ 的能选的期望次数，其实转移方程也很简单 $f_{i,j}=\frac{1}{cnt}\sum f_{i,k}+f_{k,j}+1,a_i<a_k<a_j$ 那么现在也就得出了 $n^3$ 的做法，考虑优化。我们发现对于两个 $f$ 一定有一个左端点是 $i$ 一个的右端点是 $j$ 所以考虑维护 $n$ 个树状数组，因为这里的 $j-i+1>k-i+1$ 所以直接在 $j$ 和 $i$ 那个树状数组上区间查询即可，时间复杂度就是 $O(n^2\times \log(n))$。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n;
const int N=2e3+10,mod=1e9+7;
int a[N],f[N][N],cnt[N][N];
il int qmi(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int inv[N],tr[N];
int lowbit(int x) {
	return x&-x;
}
void add(int x,int k) {
	x+=2;
	for(;x<=n+3;x+=lowbit(x)) tr[x]+=k;
}
int Ans(int x) {
	x+=2;
	int res=false;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
int tt[N][N];
void add1(int x,int k,int i) {
	x+=2;
	for(;x<=n+3;x+=lowbit(x)) tt[i][x]+=k,tt[i][x]%=mod;
}
int Ans1(int x,int i) {
	x+=2;
	int res=0;
	for(;x;x-=lowbit(x)) res+=tt[i][x],res%=mod;
	return res;
}
fire main() {
	in(n);
	rep(i,1,n) in(a[i]);
	a[0]=0,a[n+1]=n+1;
	rep(i,1,n) inv[i]=qmi(i,mod-2);
	rep(i,0,n+1) {
		rep(j,1,n+3) tr[j]=false;
		int j=i+1;
		while(j<=n+1) {
			if(a[i]<=a[j]) cnt[i][j]=Ans(a[j])-Ans(a[i]);
			add(a[j],1);
			j++;
		}
	}
	rep(l,3,n+2) {
		rep(i,0,n+1-l+1) {
			int j=i+l-1,cc=false;
			if(a[i]>a[j]) continue;
			cc=cnt[i][j];
			f[i][j]=((cnt[i][j]-Ans1(a[i]-1,j)+Ans1(a[j],j)+Ans1(a[j],i)-Ans1(a[i]-1,i))%mod+mod)%mod;
			f[i][j]=f[i][j]*inv[cc]%mod;
			add1(a[i],f[i][j],j);
			add1(a[j],f[i][j],i);
		}
	}
	print(f[0][n+1]);
	return false;
}
```

---

## 作者：xuyiyang (赞：0)

### [[ARC108E] Random IS](https://www.luogu.com.cn/problem/AT_arc108_e)
### Solution
首先发现选取顺序会影响到概率，所以对于一个 IS 的生成方式的各个概率是不同的。所以不能直接 DP。$\\$
发现若取了 $l,r$ 两个点，则在 $(l,r)$ 中的点选不选与 $[1,l) \cup (r,n]$ 无关，因为被 $l,r$ 的限制比外界限制更强，则可以区间 DP。$\\$
令 $f_{l,r}$ 表示区间 $[l,r]$ 强制选了 $l,r$，可以最多选数个数的期望。令当前可以选的数的个数为 $p$，则：
$$f_{l,r}=\frac{1}{p}\sum \limits _ {k = l+1} ^ {r-1} (f_{l,k}+f_{k,r}+1)[w_l \lt w_k \lt w_r]$$
直接转移是 $\mathcal O(n^3)$ 的，考虑优化。发现 $l \lt k \lt r$ 和 $w_l \lt w_k \lt w_r$ 这两个条件是个偏序数点，那直接树状数组优化就可以了。具体的，当 $[l,r]$ 区间转移完后，开 $n$ 个 BIT，在第 $l$ 个 BIT 中加入 $(w_r,f_{l,r})$ 这个二元组，再类似维护两个即可。
```cpp
struct BIT {
	int c[N]; 
	void add(int x, int y) { while (x <= n + 2) (c[x] += y) %= mod, x += (x & -x); }
	int qry(int x) {
		int res = 0;
		while (x) (res += c[x]) %= mod, x -= (x & -x);
		return res;
	}
	int s(int l, int r) { return (qry(r) - qry(l - 1) + mod) % mod; }
} tr[N][3];

int main() {
	scanf("%d", &n); inv[1] = 1;
	for (int i = 2; i <= n; i ++ ) inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod; 
	for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]), w[i] ++ ;
	w[0] = 1, w[n + 1] = n + 2;
	for (int i = 0; i < n + 1; i ++ ) tr[i][2].add(w[i + 1], 1);
	for (int len = 3; len <= n + 2; len ++ ) for (int l = 0; l + len - 1 <= n + 1; l ++ ) {
		int r = l + len - 1; if (w[l] > w[r]) continue ;
		int cnt = tr[l][2].s(w[l], w[r]);
		if (cnt > 0) {
			(f[l][r] += (LL)tr[l][0].s(w[l], w[r]) + tr[r][1].s(w[l], w[r]) + cnt) %= mod;
			f[l][r] = (LL)f[l][r] * inv[cnt] % mod;
		}
		tr[l][0].add(w[r], f[l][r]), tr[r][1].add(w[l], f[l][r]), tr[l][2].add(w[r], 1);
	} printf("%d\n", f[0][n + 1]); return 0;
}
```

---

## 作者：Aigony (赞：0)

首先发现，在最终序列一样的情况下，标记的顺序会对后面的概率造成影响。也就是说 dp 数组需要维护整个标记序列，这显然是不可做的。

发现一条性质：对于 IS 来说，只要我们在其中选择了一对点 $(l,r)$，这个序列就被划分成了互不相关的三部分。在这两个点之间的所有位置怎么选不会被这两个点之外的数影响。这启发我们直接把选择的数塞进状态，设 $f_{l,r}$ 表示已经选了 $l,r$ 位置上的数，这个区间内期望还会选多少个数。

那么设 $x$ 为 $[l,r]$ 内可以选的点数，转移不难写出：
$$
f_{l,r}=\sum_{a_l<a_k<a_r} \frac{1}{x}(f_{l,k}+f_{k,j}+1)
$$

看起来取得了很大进展！但是直接转移是 $\mathcal{O}(n^3)$ 的。

考虑倒序枚举 $l$，正序枚举 $r$，这符合区间 dp 的转移顺序要求。同时，对式子里的三项分别维护权值树状数组，时间复杂度 $\mathcal{O}(n^2\log n)$。

```cpp
#define int long long
const int N=2005,mod=1e9+7;
int n,a[N],f[N][N];
struct BIT
{
    int tr[N];
    il void add(int x,int k) {for(;x<=n+2;x+=x&(-x)) tr[x]=(tr[x]+k)%mod;}
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res=(res+tr[x])%mod;return res;}
    il int ask(int l,int r) {return (query(r)-(l?query(l-1):0)+mod)%mod;}
}L[N],R[N],ct[N];
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read()+1;
    a[n+1]=n+2,a[0]=1;
    for(int i=n;i>=0;i--)
    {
        for(int j=i+1;j<=n+1;j++)
        {
            int inv=qpow(ct[i].ask(a[i]+1,a[j]-1));
            if(inv) f[i][j]=(1+inv*(L[i].ask(a[i]+1,a[j]-1)+R[j].ask(a[i]+1,a[j]-1))%mod)%mod;
            ct[i].add(a[j],1),L[i].add(a[j],f[i][j]),R[j].add(a[i],f[i][j]);
        }
    }
    printf("%lld\n",f[0][n+1]);
    return 0;
}
```

---

