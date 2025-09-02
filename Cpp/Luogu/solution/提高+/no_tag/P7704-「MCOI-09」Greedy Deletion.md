# 「MCOI-09」Greedy Deletion

## 题目描述

小于等于 $n$ 的正整数形成集合 $S_n=\{1,2,\dots,n\}$。

删除值为 $i$ 的元素代价为 $i^k$，其中每一个元素至多被删一次。

给定正整数 $n$ 和 $k$，求：最小代价使 $S_n$ 乘积变为完全平方数是什么？答案对 $998244353$ 取模。

**注意你需要求最小代价，模 $998244353$，而不是模 $998244353$ 后的代价的最小值。**

你需要回答 $T$ 组询问，其中所有 $k$ 相同。

## 说明/提示

#### 样例 1 解释

对于 $n=1$，$S_1$ 乘积为完全平方数，不需要删除。

对于 $n=6$，可以删除 $5$ 使得 $S_6$ 乘积变为完全平方数。

#### 数据规模与约定

 - Subtask 1（7 pts）：$\max n\le 20$。
 - Subtask 2（37 pts）：$\max n\le 1000$。
 - Subtask 3（11 pts）：$T\le 1000$。
 - Subtask 4（45 pts）：无额外限制。

对于 $100\%$ 的数据，$1\le \max n\le 5\times 10^6$，$1\le T\le 5\times 10^5$，$1\le k< 998244353$。

**保证** $1\le n\le \max n$。

## 样例 #1

### 输入

```
2 2 6
1
6```

### 输出

```
0
25```

# 题解

## 作者：vectorwyx (赞：5)

设 $x=\prod_{i=1}^{\infty}p_i^{e_i}$（$p_i$ 表示第 $i$ 个质数），则 $x$ 为完全平方数当且仅当 $\forall i\in \mathbb{N_+},2|e_i$。即 $x$ 为完全平方数当且仅当把 $x$ 分解质因数后每个质数对应的指数为偶。

如果 $S_n=\prod_{i=1}^ni$ 分解质因数后有若干个质数对应的指数为奇，因为当 $i,j\ge2,k\in\mathbb{N_+}$ 时有 $i^kj^k\ge i^k+j^k$，所以最优策略肯定是把这些质数从集合里依次删去。

由于 $S_n$ 本身很大，所以考虑对区间 $[1,n]$ 里的每个正整数分解质因数，然后把每个质数对应的指数相加。这是经典问题，我们有预处理 $O(n)$ 单次分解 $O(\log{n})$ 的线性筛做法。记 $mn_i$ 为 $i$ 的最小质因数，用线性筛筛出 $mn_{1\sim n}$，分解 $x$ 时不断把 $x$ 除以 $mn_x$ 直至 $x=1$ 即可。很显然单次的最坏复杂度为 $O(\log{x})$。这个做法还可以拓展，记 $e_i$ 为 $i$ 的最小质因子对应的次数，$pre_i$ 为 $mn_i^{e_i}$。分解 $x$ 时不断把 $x$ 除以 $pre_x$。最坏情况下复杂度仍为 $O(\log x)$，但是常数小很多。

这样的复杂度是 $O(\sum_{i=1}^T n_i\log n_i)$ 的，还是很劣。可以把所有询问操作离线下来按 $n_i$ 排序，这样对于第 $i$ 次询问只需要分解区间 $[n_{i-1}+1,n_i]$ 里的正整数，总时间复杂度就变成 $O(n \log{n})$ 的了。

代码如下（码 $\LaTeX$ 不易，希望能给个赞！QAQ）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=5e6+5,qlr=998244353,lim=20;
int pme[N],top,mn[N],e[N],pre[N],ok[N],ask[N],a[N],od[N/10],Ans[N/10],pw[N],_k;

inline int ksm(int x,int y){
	int t=x,ans=1;
	while(y){
		if(y&1) ans=1ll*ans*t%qlr;
		t=1ll*t*t%qlr;
		y>>=1;
	}
	return ans;
}

void xxs(int n){
	fo(i,2,n){
		if(!ok[i]){
			pme[++top]=i,mn[i]=pre[i]=i,e[i]=1;
			pw[i]=ksm(i,_k);
		} 
		fo(j,1,top){
			int p=pme[j],k=i*p;
			if(k>n) break;
			ok[k]=1;
			if(i%p) mn[k]=pre[k]=p,e[k]=1;
			else{
				mn[k]=p,pre[k]=pre[i]*p,e[k]=e[i]+1;
				break;
			} 
		}
	}
}

bool cmp(int x,int y){return ask[x]<ask[y];} 

int main(){
	int T=read(),k=read(),n=read(),lst=2,ans=0;_k=k;
	xxs(n);
	fo(i,1,T) ask[i]=read(),od[i]=i;
	sort(od+1,od+1+T,cmp);
	fo(i,1,T){
		fo(j,lst,ask[od[i]]){
			int t=j;
			while(t>1){
				if(e[t]&1){
					a[mn[t]]^=1;
					if(a[mn[t]]) ans=(ans+pw[mn[t]])%qlr;
					else ans=(ans-pw[mn[t]]+qlr)%qlr;
				}
				t/=pre[t];
			}
		}lst=ask[od[i]]+1;
		Ans[od[i]]=ans;
	}fo(i,1,T) printf("%d\n",Ans[i]);
	return 0;
}
```


---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P7704)
## 题意
有一个集合 $S_n=\{x|x\in\Bbb{N}_+,x\le n\}$，其权值为 $\prod_{i\in S_n}i$，从集合中删除一数 $x$ 的代价为 $x^k$，若要将其权值变为完全平方数，求最小代价。对 $998244353$ 取模。多组数据。

$T\le5\times10^5$，$1\le n\le\max n\le5\times 10^6$，$0\le k<998244353$
## 思路
先吐槽一下，这题大概应该放在 T3 的位置...

我们发现完全平方数仅要求其所有质因子的指数为 $1$，所以只删质因数定能将其变为完全平方数。

又因 $a,b,k\ge 2$ 时 $a^k+b^k\le a^kb^k$，所以只删质因数的代价是最少的。
#### 算法 1
可以离线询问，排序，然后对于排完序后的 $n'_i$，将 $n'_{i-1}+1$ 至 $n'_i$ 之间的数分解质因数，算其贡献，最后对询问进行前缀和即可。

时间复杂度 $O(n^{\frac 5 4}+n\log\log n\log \text{mod}+T\log T)$，期望得分 $44$ 分。
#### 算法 2
考虑筛出 $n$ 以内质数的所有倍数，在倍数处计算前缀和贡献，可以使用前向星将质数与其倍数之间连边，将倍数从 $1$ 扫到 $\max n$，再统计是加入 $i^k$ 的贡献还是 $-i^k$ 的贡献。注意，为了防止带上 $\log \bmod$，质数的 $k$ 次幂可以提前预处理。

时间复杂度 $O(n\log\log n+T)$，期望得分 $100$ 分。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=5e6+10,mod=998244353;
int maxn,k,T,anss[N],qp[N];
ll cur;
bool app[N];
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
bitset<N>p;
int pri[N],cnt;
int head[N],cntg;
struct Edge{
	int to,nxt;
}a[N<<2];
inline void add(int u,int v){
	cntg++;
	a[cntg].to=v;
	a[cntg].nxt=head[u];
	head[u]=cntg;
}
inline void sieve(int n){
	p[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]){
			pri[++cnt]=i;
			qp[cnt]=qpow(i,k);
			for(ll j=i;j<=n;j*=i)
				for(int q=j;q<=n;q+=j)
					app[q]^=1;
			for(int j=i;j<=n;j+=i)
				if(app[j])
					add(j,cnt),app[j]=0;
		}
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++){
			p[i*pri[j]]=1;
			if(i%pri[j]==0)
				break;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=a[j].nxt)
			cur+=((app[a[j].to]^=1)?qp[a[j].to]:mod-qp[a[j].to]);
		anss[i]=cur%mod;
	}
}
int main(){
	T=read(),k=read(),maxn=read();
	sieve(maxn);
	while(T--){
		int n=read();
		write(anss[n]);
		putc('\n');
	}
	flush();
}
```
再见 qwq~

---

## 作者：Prean (赞：2)

来一个特别暴力的做法。

首先，如果删掉 $ x $ 和 $ y $ 的效果一定和删掉 $ xy $ 的效果相同，且代价一定比后者小。

于是我们只删除质数，题目就变成了寻找 $ i!(1 \leq i \leq \max n) $ 中有多少个质数出现了奇数次。

给差分一下，变成求 $ i $ 的质因子分解。

有人可能会认为这里需要用到 PR，其实并不需要，因为所有的 $ i \leq \max n $，所以只需要记录下每一个 $ i $ 最小的质因子，然后直接跳即可。

复杂度的话，$ i $ 的质因子总数一定不超过 $ \log_2 i $（最坏情况是存在一个 $ k $ 使得 $ i=2^k $），所以复杂度是 $ O(n\log n+T) $ 的，且常数较小

加上 快读&快输&加减法优化&整数除法转实数乘法&预处理逆元 后最大点才 349ms，轻松通过。

ps:这题思维难度和代码难度都不高，评绿吧。。。
```cpp
#include<cstdlib>
#include<cstdio>
#include<cctype>
const int M=5e6+5,mod=998244353;
int T,n,k,top,p[M],ans[M],pri[M],pos[M];bool vis[M];
double inv[M];
inline int read(){
	int n=0;char s;
	while(!isdigit(s=getchar()));
	while(n=n*10+(s^48),isdigit(s=getchar()));
	return n;
}
inline void write(int n){
	char s[10];int top=0;
	while(s[++top]=n%10^48,n/=10);
	while(putchar(s[top]),--top);
}
inline int Add(const int&a,const int&b){
	return a+b>=mod?a+b-mod:a+b;
}
inline int Del(const int&a,const int&b){
	return b>a?a-b+mod:a-b;
}
inline int pow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
	return ans;
}
inline void sieve(const int&M){
	register int i,j,x;
	for(i=2;i<=M;++i){
		ans[x=i]=ans[i-1];
		if(!pos[i]){
			pri[pos[i]=++top]=i;inv[top]=1./i+1e-15;
			ans[i]=Add(ans[i],p[top]=pow(i,k));vis[top]=1;
		}
		else{
			while(x^1){
				ans[i]=(vis[pos[x]]^=1)?Add(ans[i],p[pos[x]]):Del(ans[i],p[pos[x]]);
				x=x*inv[pos[x]];
			}
		}
		for(j=1;(x=i*pri[j])<=M;++j)if((pos[x]=j)==pos[i])break;
	}
}
signed main(){
	register int i;
	T=read();k=read();sieve(read());
	while(T--)write(ans[read()]),putchar(10);
}
```

---

## 作者：_7thRC_CB_CRP_ (赞：0)

首先我们肯定是想要去借助一些质数相关的性质。

那么假设原始积为：$\prod p_i^{q_i}$。那么我们想要去让它变成完全平方数，我们就直接把某个不是偶次幂的质数用 $p_i^k$ 的贡献删掉。

我们可以通过类似埃氏筛的方法把那些位置标记出来，那么可以借助这些在加上前缀和就做完了。

我们在这里先枚举每个质数，然后在去枚举他的每个次方，将这些位置改变（他是否要让后面的次幂翻转），然后呢在筛中间要用到一次前缀和，要前缀求出这个地方是否要改变幂次（这里复杂度不高其实只是在对他的倍数做一个异或前缀）。

那么我们再枚举这些位置，然后做差分（这里差分的是贡献）。然后最后在做前缀。

查询直接访问我们已经预处理的值。

```cpp

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
ll v[5000001];
ll cnt, prim[500001];
ll r[5000001];
ll tp[5000001];
ll qpow(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1)res = res * x, res %= mod;
		x = x*x % mod;
		y >>= 1;
	}
	return res;
}
void init(ll n, ll k) {
	for (int i = 2; i <= n; i++) {
		if (!v[i]) prim[++cnt] = i;
		for (int j = 1; prim[j]*i <= n; j++) {
			v[i*prim[j]] = 1;
			if (i % prim[j] == 0)
				break;
		}
	}
	for (int i = 1; i <= cnt; i++) {
		ll p = 1;
		while (p * prim[i] <= n) {
			p *= prim[i];
			for (int j = 1; p * j <= n; j++) {
				tp[p*j] ^= 1;
			}
		}
		p = prim[i];
		ll val = -qpow(p, k);
		for (int j = 1; p * j <= n; j++) {
			if (tp[p * j])
				val = -val;
			if (tp[p * j])
				r[j * p] += val, r[j * p] %= mod;
		}
		for (int j = 1; p * j <= n; j++)
			tp[p * j] = 0;
	}
	for (int i = 1; i <= n; i++)
		r[i] += r[i - 1], r[i] %= mod, r[i] += mod, r[i] %= mod;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll t, n, k;
	cin >> t >> k >> n;
	init(n, k);
	while (t--) {
		ll op;
		cin >> op;
		cout << r[op] << '\n';
	}
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 思路

首先设最终的乘积为 $\prod\limits_{i=1}^{k}p_i^{q_i}$，设集合 $S$ 为满足 $q_i$ 为奇数对应的 $p_i$，那么最终的方案一定是删掉 $S$ 中的数，因为对于 $x,y\ge2,k\ge1$，一定有 $(xy)^{k}\ge x^k+y^k$。

题目转化为了求 $1\sim n$ 的乘积分解质因数后哪些质数的指数为奇数。

考虑预处理答案，枚举一个质数 $p$，枚举他的倍数 $x$，将 $\log_px$ 暴力求出，当这个数为奇数时，$1\sim x$ 的乘积分解质因数后 $p$ 的指数奇偶性会改变，统计其贡献，最后做一遍前缀和就行了。

这样做的时间复杂度是 $O(n\log n)$ 的（$x$ 分解质因数后指数之和不会超过 $\log x$），常数很小，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6+5,mod = 998244353;
int T,k,n,ans[N],s[N];
bool vis[N];
inline int qpow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x%mod;
		y>>=1;
		x = x*x%mod;
	}
	return res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T>>k>>n;
	int pp = 0;
	for(int i = 2;i<=n;i++)
	{
		if(vis[i]) continue;
		int pw = qpow(i,k);
		int cnt = 0;
		for(int j = i;j<=n;j+=i)
		{
			vis[j] = 1;
			int now = 0,x = j;
			while(x%i==0) x/=i,now^=1;
			if(now)
			{
				cnt^=1;
				if(cnt) (ans[j]+=pw)%=mod;
				else (ans[j]+=mod-pw)%=mod;
			}
		}
	}
	for(int i = 2;i<=n;i++)
		(ans[i]+=ans[i-1])%=mod;
	while(T--)
	{
		int x;cin>>x;
		cout<<ans[x]<<'\n';
	}
	return 0;
}
```

---

## 作者：_Arahc_ (赞：0)

注意到完全平方数的要求实际上相当于乘积的每个质因数的质数都是偶数。

考虑到对于一个奇数指数的质因子，如何将其删掉。注意到这样一个事实：对于 $p,q\geq 2,k\geq 1$，有 $(pq)^k \geq p^k+q^k$。因此将多个质因子合并和一个一个分别干这些质因子比起来，后者一定是更优的。

$S_n$ 本身是很大的。考虑对 $1\sim n$ 暴力分解质因数。注意到我们并不关心每个质数的具体指数，只关心每个质数的指数的奇偶性。

欧拉筛预处理出每个数字的最小质因子，对于一个数字 $x$ 你就不断地用 $x$ 去除它的最小质因子，每次最少除掉 $2$ 因此除到 $1$ 显然只需要 $\log x$ 次。

然后每次算就可以把 $1\sim n$ 里的数字都拿出来按照这样去除，单次询问的复杂度为 $n\log n$。

把所有的询问离线下来，就可以做到总复杂度 $n\log n$ 了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool Begin;
const int max_n=5000006,mod=998244353;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
inline int mi(int a,int p=mod-2){
    int res=1;
    while(p){
        if(p&1) res=res*a%mod;
        a=a*a%mod,p>>=1;
    }
    return res;
}
inline int MOD(int x){return x>=mod?x-mod:x;}

int n,T,K;

int ans[max_n];
vector<int> vec[max_n];

int mnp[max_n],pr[max_n],ml[max_n];
bool isp[max_n];
inline void GetPr(){
    memset(isp,1,sizeof(isp)),isp[1]=0;
    for(int i=2;i<=n;++i){
        if(isp[i]){
            pr[++*pr]=i;
            mnp[i]=i,ml[i]=mi(i,K);
        }
        for(int j=1;j<=*pr && i*pr[j]<=n;++j){
            isp[i*pr[j]]=0;
            mnp[i*pr[j]]=pr[j];
            if(i%pr[j]==0){
                break;
            }
        }
    }
}

int res;
bool a[max_n];

bool End;
#define File ""
signed main(){
    T=read(),K=read(),n=read();
    GetPr();
    for(int i=1;i<=T;++i)
        vec[read()].emplace_back(i);
    for(int i=2;i<=n;++i){
        int x=i;
        while(x>1){
            a[mnp[x]]^=1;
            if(a[mnp[x]])
                res=MOD(res+ml[mnp[x]]);
            else
                res=MOD(res+mod-ml[mnp[x]]);
            x/=mnp[x];
        }
        for(auto p:vec[i])
            ans[p]=res;
    }
    for(int i=1;i<=T;++i)
        write(ans[i]),putchar('\n');
    return 0;
}
```

---

