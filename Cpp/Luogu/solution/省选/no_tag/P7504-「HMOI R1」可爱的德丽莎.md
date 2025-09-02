# 「HMOI R1」可爱的德丽莎

## 题目背景

Polaris_Dane 非常菜，他不仅沉迷于数论，而且喜欢玩崩坏 3。

## 题目描述

可爱的德丽莎希望你能帮她求出

$$
\sum_{x = 1}^n\sum_{y = 1}^n\sum_{i = 1}^x[x \bot k_1][i \bot x]\cdot i\cdot \sum_{j = 1}^y[y \bot k_2][j \bot y]\cdot j
$$
的结果。

其中 $[x \bot y] = \begin{cases}1 & \operatorname{gcd}(x,y)=1 \\ 0 & \operatorname{gcd}(x,y)\neq 1\end{cases}$

德丽莎这么可爱，你怎么能不答应她呢？

由于答案可能很大，所以德丽莎只想知道它对 $998244353$ 取模后的结果。

## 说明/提示

**本题测试点编号倒序排列。**

对于所有数据：
- $1 \le n, k_1, k_2 \le 2 \times 10^9$。

---------

**本题采用捆绑测试。**

| No. | Constraints                   | Score |
| ----------- | ----------------------------- | ----- |
| $1$         | $1\le n,k_1,k_2\le 100$         | $10$  |
| $2$         | $1\le n,k_1,k_2\le 3000$ | $20$  |
| $3$         | $1\le n,k_1,k_2\le 5\times 10^5$ | $20$  |
| $4$         | No further constraints        | $50$  |

---------------

- Idea: Polaris_Dane
- Solution: Polaris_Dane
- Code: Polaris_Dane
- Data: Polaris_Dane

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
4 2 2```

### 输出

```
16```

# 题解

## 作者：Leasier (赞：5)

前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/mobius/)、[杜教筛](https://oi-wiki.org/math/number-theory/du/)

本题解省略部分分做法及其代码。

设 $solve(n, m) = \displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] \sum_{j = 1}^i [\gcd(i, j) = 1] j$，则原式 $= solve(n, k1) solve(n, k2)$。

$solve(n, m) = \displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] \sum_{j = 1}^i j \sum_{d \mid \gcd(i, j)} \mu(d)$

$ = \displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] \sum_{d \mid i} \mu(d) \sum_{d \mid j}^i j$

设 $S_1(n) = \displaystyle\sum_{i = 1}^n i$，则：

$solve(n, m) = \displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] \sum_{d \mid i} \mu(d) d S_1(\frac{i}{d})$

$ = \frac{\displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] i \sum_{d \mid i} \mu(d) (\frac{i}{d} + 1)}{2}$

$ = \frac{\displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] i (\varphi(i) + \epsilon(i))}{2}$

$ = \frac{\displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] i \varphi(i)  + 1}{2}$

到此为止，问题转变为了快速求出 $f(n) = [\gcd(n, m) = 1] n \varphi(n)$ 的前缀和。

想到 $id_2 = id * (id \cdot \varphi)$ 且 $\epsilon(\gcd)$ 为完全积性函数，发现 $\epsilon(\gcd) \cdot id_2 = (\epsilon(\gcd) \cdot id) * (\epsilon(\gcd) \cdot id \cdot \varphi)$，考虑杜教筛。

显然 $\displaystyle\sum_{i = 1}^n [\gcd(i, m) = 1] i = \displaystyle\sum_{d \mid m} \mu(d) d S_1(\lfloor \frac{n}{d} \rfloor)$，$\epsilon(\gcd) \cdot id_2$ 的前缀和同理。至此可以杜教筛。时间复杂度为 $O(\sqrt{n} (\tau(k_1) + \tau(k_2)) + n^{\frac{2}{3}})$。

代码：
```cpp
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;

const int N = 1587401 + 7, M = 1536 + 7, mod = 998244353, inv2 = 499122177, inv6 = 166374059;
int limit;
int prime[N], phi[N], divisor[M], mu_list[M];
ll f[N], g[N], h[N], f_sum[N], g_sum[N], h_sum[N];
bool p[N];
map<int, ll> mp1, mp2, mp3;

inline void init1(){
	int cnt = 0;
	p[0] = p[1] = true;
	phi[1] = 1;
	for (register int i = 2; i <= limit; i++){
		if (!p[i]){
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= limit; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}
			phi[t] = phi[i] * (prime[j] - 1);
		}
	}
}

inline int mu(int n){
	int ans = 1;
	for (register int i = 2; i * i <= n; i++){
		if (n % i == 0){
			n /= i;
			if (n % i == 0) return 0;
			ans = -ans;
		}
	}
	if (n > 1) ans = -ans;
	return ans;
}

inline int init2(int n){
	int prime_cnt = 0, divisor_cnt = 0, t = sqrt(n);
	p[0] = p[1] = true;
	f[1] = 1;
	g[1] = 1;
	h[1] = 1;
	for (register int i = 2; i <= limit; i++){
		if (!p[i]){
			prime[++prime_cnt] = i;
			f[i] = n % i == 0 ? 0 : (ll)i * phi[i] % mod;
			g[i] = n % i == 0 ? 0 : (ll)i * i % mod;
			h[i] = n % i == 0 ? 0 : i;
		}
		for (register int j = 1; j <= prime_cnt && i * prime[j] <= limit; j++){
			int t = i * prime[j];
			p[t] = true;
			f[t] = f[i] != 0 && n % prime[j] != 0 ? (ll)t * phi[t] % mod : 0;
			g[t] = g[i] * g[prime[j]] % mod;
			h[t] = h[i] * h[prime[j]] % mod;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i < N; i++){
		f_sum[i] = (f_sum[i - 1] + f[i]) % mod;
		g_sum[i] = (g_sum[i - 1] + g[i]) % mod;
		h_sum[i] = (h_sum[i - 1] + h[i]) % mod;
	}
	for (register int i = 1; i <= t; i++){
		if (n % i == 0){
			divisor_cnt++;
			divisor[divisor_cnt] = i;
			mu_list[divisor_cnt] = mu(i);
			if (i * i != n){
				int tn = n / i;
				divisor_cnt++;
				divisor[divisor_cnt] = tn;
				mu_list[divisor_cnt] = mu(tn);
			}
		}
	}
	return divisor_cnt;
}

inline ll sum2(int n){
	return (ll)n * (n + 1) % mod * ((ll)n * 2 % mod + 1) % mod * inv6 % mod;
}

inline ll get_g_sum(int n, int cnt){
	if (n <= limit) return g_sum[n];
	if (mp2.count(n)) return mp2[n];
	ll ans = 0;
	for (register int i = 1; i <= cnt; i++){
		ans = ((ans + (ll)mu_list[i] * divisor[i] % mod * divisor[i] % mod * sum2(n / divisor[i]) % mod) % mod + mod) % mod;
	}
	return mp2[n] = ans;
}

inline ll sum1(int n){
	return (ll)n * (n + 1) / 2 % mod;
}

inline ll get_h_sum(int n, int cnt){
	if (n <= limit) return h_sum[n];
	if (mp3.count(n)) return mp3[n];
	ll ans = 0;
	for (register int i = 1; i <= cnt; i++){
		ans = ((ans + mu_list[i] * divisor[i] % mod * sum1(n / divisor[i]) % mod) % mod + mod) % mod;
	}
	return mp3[n] = ans;
}

inline ll get_f_sum(int n, int cnt){
	if (n <= limit) return f_sum[n];
	if (mp1.count(n)) return mp1[n];
	ll ans = get_g_sum(n, cnt);
	for (register int i = 2, j; i <= n; i = j + 1){
		int tn = n / i;
		j = n / tn;
		ans = ((ans - get_f_sum(tn, cnt) * (get_h_sum(j, cnt) - get_h_sum(i - 1, cnt)) % mod) % mod + mod) % mod;
	}
	return mp1[n] = ans;
}

inline ll solve(int n, int m){
	int cnt = init2(m);
	mp1.clear();
	mp2.clear();
	mp3.clear();
	return (get_f_sum(n, cnt) + 1) * inv2 % mod;
}

int main(){
	int n, k1, k2;
	cin >> n >> k1 >> k2;
	limit = pow(n, 2.0 / 3.0);
	init1();
	cout << solve(n, k1) * solve(n, k2) % mod;
	return 0;
}
```

---

## 作者：Krimson (赞：1)

~~好像被我推复杂了...~~

## 简述题意

求：
$$
\sum^{n}_{x=1}\sum^{n}_{y=1}\sum^{x}_{i=1}i[(x,k_{1})=1][(i,x)=1]\sum^{y}_{j=1}[(y,k_{2})=1][(y,j)=1]j
$$
$n,k_1,k_2\leq 2\times 10^9$。

## Solution

首先是推式子：

$$
\begin{aligned}
ans&=\sum^{n}_{x=1}\sum^{x}_{i=1}i[(x,k_{1})=1][(i,x)=1]\sum^{n}_{y=1}\sum^{y}_{j=1}[(y,k_{2})=1][(y,j)=1]j\\
\end{aligned}
$$

注意到左右两边形式一样，设 $S(n,k)=\sum^{n}_{x=1}\sum^{x}_{i=1}i[(x,k)=1][(i,x)=1]$。

那么有：
$$
\begin{aligned}
ans&=S(n,k_{1})\times S(n,k_{2})\\
\\
S(n,k)&=\sum^{n}_{x=1}\sum^{x}_{i=1}i[(x,k)=1][(i,x)=1]\\
&=\sum^{n}_{x=1}[(x,k)=1]\sum^{x}_{i=1}i\sum_{g|\gcd(i,x)}\mu(g)\\
&=\sum^{n}_{x=1}[(x,k)=1]\sum^{}_{g|x}\mu(g)g C_{2}(\frac{x}{g})\\
&=\sum^{n}_{x=1}\sum_{t|\gcd(x,k_1)}\mu(t)\sum^{}_{g|x}\mu(g)g C_{2}(\frac{x}{g})\\
&=\frac{1}{2}\sum^{}_{t|k_{1}}\mu(t)\sum^{\lfloor\frac{n}{t}\rfloor}_{x=1}x\sum^{}_{g|x}\mu(g)\frac{x}{g}+\mu(g)\\
&=\frac{1}{2}\sum^{}_{t|k_{1}}\mu(t)\sum^{\lfloor\frac{n}{t}\rfloor}_{x=1}x\varphi(x)+[x=1]\\
&=1+\frac{1}{2}\sum^{}_{t|k_{1}}\mu(t)\sum^{\lfloor\frac{n}{t}\rfloor}_{x=1}tx\varphi(tx))\\
\end{aligned}
$$
如果是求 $i\varphi(i)$ 的前缀和，可以直接上 `Min_25` ，可是这里的形式比较诡异，不能直接求。

不过注意到 $\mu(t)\not = 0$，当且仅当 $t$ 中的每一个质因子只出现一次，似乎是可以做一个DP。

我们令 $p$  表示 $t$ 中的某一个质因子，同时定义一个新的函数 $G(n,t)$。
$$
\begin{aligned}
G(n,t)&=\sum^{n}_{x=1}x\varphi(tx)\\
&=\sum^{n}_{x=1}[\gcd(x,p)=1]x\varphi(x\frac{t}{p})(p-1)+\sum^{\lfloor\frac{n}{p}\rfloor}_{x=1}xp^2\varphi(xp\frac{t}{p})\\
&=\sum^{n}_{x=1}x\varphi(x\frac{t}{p})(p-1)+\sum^{\lfloor\frac{n}{p}\rfloor}_{x=1}xp\varphi(xt)\\
&=(p-1)G(n,\frac{t}{p})+pG(\lfloor\frac{n}{p}\rfloor,t)\\
\\
G(n,1)&=\sum^{n}_{i=1}i\varphi(i)=F(n)\\
\\
S(n,k)&=1+\frac{1}{2}\sum_{t|k \And \mu(t)\not = 0}t\mu(t)G(\lfloor \frac{n}{t} \rfloor,t)

\end{aligned}
$$
加上记忆化之后，复杂度便正确了。

首先是 $G$ 部分，总共状态个数是 $O(k^{\frac{1}{3}}n^{\frac{1}{2}})$ 的，每次转移是 $O(1)$。

然后是 $F$ 部分，只有 $O(\sqrt{n})$ 个取值，只需要在 `Min_25` 内加一个记忆化也是可以做到 $O(n^{\frac{3}{4}}) $ 或者 $O(\frac{n^{\frac{3}{4}}}{\ln n})$ 。

视 $n,k$ 同阶，那么总复杂度为 $O(n^{\frac{5}{6}})$ ，实测跑的还是比较快的，完全跑不满，瓶颈反而在 `Min_25` 内记忆化所使用的 `map` 中。

## Code

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<unordered_map>
using namespace std;
#define ll long long 
#define ri int
#define pii pair<int,int>
const ll mod=998244353,inv=mod+1>>1,inv3=332748118;
ll add(ll x,ll y){return (x+=y)<mod?x:x-mod;}
ll dec(ll x,ll y){return (x-=y)<0?x+mod:x;}
ll ksm(ll d,ll t){ll res=1;for(;t;t>>=1,d=d*d%mod) if(t&1) res=res*d%mod;return res;}
const int MAXN=1e5+7;
int totcnt=0;
namespace Getphi{
    const int MAXM=1e7+7;
    int val[MAXM],as[MAXM],nxt[MAXM],mapcnt;
    struct hmap{
        static const int P=10007;
        int hed[P];
        bool count(int x){
            int c=hed[x%P];
            while(c){
                if(val[c]==x) return 1;
                c=nxt[c];
            }return 0;
        }
        int& operator [](int x){
            int c=hed[x%P];
            while(c){
                if(val[c]==x) return as[c];
                c=nxt[c];
            }
            ++mapcnt;val[mapcnt]=x;nxt[mapcnt]=hed[x%P];hed[x%P]=mapcnt;
            return as[mapcnt];
        }
        int size(){return mapcnt;}
    }S[4650];
    int n,p1[MAXN],p2[MAXN],cnt,N,flag[MAXN],prim[MAXN],w[MAXN];
    int pos(int x){
        if(1ll*x*x<=n) return p1[x];
        else return p2[n/x];
    }
    ll g1[MAXN],g2[MAXN];
    ll C2(ll x){return x*(x+1)/2%mod;}
    ll C3(ll x){return C2(x)*(x+x+1)%mod*inv3%mod;}
    void init(int _n){
        n=_n;
        N=sqrt(n);
        for(ri i=2;i<=N;++i){
            if(!flag[i]) prim[++prim[0]]=i;
            for(ri j=1;j<=prim[0]&&i*prim[j]<=N;++j){
                flag[i*prim[j]]=1;
                if(i%prim[j]==0) break;
            }
        }
        for(ri l=1,r;l<=n;l=r+1){
            int cur=n/l;r=n/cur;
            w[++cnt]=cur;
            if(1ll*cur*cur<=n) p1[cur]=cnt;
            else p2[n/cur]=cnt;
            g1[cnt]=C2(cur)-1;
            g2[cnt]=C3(cur)-1;
        }
        for(ri t=1;t<=prim[0];++t){
            for(ri i=1;i<=cnt&&w[i]>=prim[t]*prim[t];++i){
                int nxtl=pos(w[i]/prim[t]),nxtr=(t==1?0:pos(prim[t-1]));
                g1[i]=dec(g1[i],dec(g1[nxtl],g1[nxtr])*prim[t]%mod);
                g2[i]=dec(g2[i],dec(g2[nxtl],g2[nxtr])*prim[t]%mod*prim[t]%mod);
            }
        }
    }
    ll getS(int n,int cur){
        int P=pos(n);
        if(cur&&prim[cur]>=n) return 0;
        if(S[cur].count(P)) return S[cur][P];
        int r=pos(n),l=cur==0?0:pos(prim[cur]);
        ll ans=dec(dec(g2[r],g2[l]),dec(g1[r],g1[l]));
        for(ri i=cur+1;i<=prim[0]&&1ll*prim[i]*prim[i]<=n;++i){
            for(ll e=1,v=prim[i],W=1;v<=n;++e,v*=prim[i],W*=prim[i]){
                ll res=getS(n/v,i);
                if(e!=1) ++res;
                res=res*v%mod*W%mod*(prim[i]-1)%mod;
                ans=add(ans,res);
            }
        }
        return S[cur][P]=ans;
    }
    ll getphi(ll x){
        ll now=getS(x,0)+1;
        return now;
    }
}
ll ans;
ll sta[64],top;
int f[64][MAXN];
ll g(ll n,int cur){
    if(n==0) return 0;
    int P=Getphi::pos(n);
    if(~f[cur][P]) return f[cur][P];
    if(cur==0) return f[cur][P]=Getphi::getphi(n);
    return f[cur][P]=add((sta[cur]-1)*g(n,cur-1)%mod,sta[cur]*g(n/sta[cur],cur)%mod);
}
ll S(ll n,ll k){
    ll res=1;
    for(ri t=1;t*t<=k;++t){
        if(k%t) continue;
        if(t<=n){
            ll x=t;
            int now=1;
            top=0;
            for(ll i=2;i*i<=t&&i<=x;++i){
                int cnt=0;
                while(x%i==0) ++cnt,x/=i;
                if(cnt>1) goto Nex;
                if(cnt) sta[++top]=i,now=-now;
            }
            if(x>1) now=-now,sta[++top]=x;
            for(ri i=0;i<=top;++i) for(ri j=0;j<=Getphi::cnt;++j) f[i][j]=-1;
            if(now== 1) res=add(res,g(n/t,top)*t%mod);
            if(now==-1) res=dec(res,g(n/t,top)*t%mod);
            Nex:;
        }
        if(t*t!=k&&k/t<=n){
            ll x=(k/t);
            int now=1;
            top=0;
            for(ll i=2;i*i<=(k/t)&&i<=x;++i){
                int cnt=0;
                while(x%i==0) ++cnt,x/=i;
                if(cnt>1) goto Next;
                if(cnt) sta[++top]=i,now=-now;
            }
            if(x>1) now=-now,sta[++top]=x;
            for(ri i=0;i<=top;++i) for(ri j=0;j<=Getphi::cnt;++j) f[i][j]=-1;
            if(now== 1) res=add(res,g(n/(k/t),top)*(k/t)%mod);
            if(now==-1) res=dec(res,g(n/(k/t),top)*(k/t)%mod);
            Next:;
        }
    }
    return res*inv%mod;
}
ll n,k1,k2;
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    scanf("%lld%lld%lld",&n,&k1,&k2);
    Getphi::init(n);
    printf("%lld\n",S(n,k1)*S(n,k2)%mod);
}
```



---

## 作者：_lbw_ (赞：1)

#### 注意！此题解需要有莫比乌斯反演基础

设 $f(n)=\sum\limits_{i=1}^ni[i\perp n]$，$g(n,k)=\sum\limits_{i=1}^n[k\perp i]f(i)$

非常容易发现答案为 $g(n,k1)g(n,k2)$

于是考虑快速求出 $g(n,k)$

然后如果你先对 $f$ 莫反，再对 $g$ 莫反就会写出一个很诡异的式子，无法优化

我们考虑把 $g$ 的 $[k\perp i]$ 保留下来，对 $f$ 莫反

$$f(n)=\sum\limits_{i=1}^ni[i\perp n]$$

$$=\sum\limits_{i=1}^ni\sum_{d|i,d|n}\mu(d)$$

$$=\sum\limits_{d|n}\mu(d)\sum\limits_{i=1}^{n/d}id$$

设 $S(n)=\frac{n\times (n+1)}{2}$

$$=\sum\limits_{d|n}S(n/d)\mu(d)d$$

继续推 $g$ 的式子

$$g(n,k)=\sum\limits_{i=1}^n[k\perp i]f(i)$$

$$=\sum\limits_{T=1}^n[k\perp T]\sum\limits_{d|T}S(d)\mu(T/d)d$$

$$=\sum\limits_{d=1}^nd\times \mu(d)\sum\limits_{d|T}[k\perp T]S(T/d)$$

设 $T=id$

$$=\sum\limits_{d=1}^nd\times \mu(d)\sum\limits_{i=1}^{n/d}[k\perp id]S(i)$$

发现 $[k\perp id]=[k\perp i][k\perp d]$

$$=\sum\limits_{d=1}^nd\times \mu(d)\sum\limits_{i=1}^{n/d}[k\perp i][k\perp d]S(i)$$

$$=\sum\limits_{d=1}^n[k\perp d]d\times \mu(d)\sum\limits_{i=1}^{n/d}[k\perp i]S(i)$$

数论分块后变成求 $\sum\limits_{d=1}^n[k\perp d]d\times \mu(d)$ 与 $\sum\limits_{i=1}^{n}[k\perp i]S(i)$

前面是积性函数可以筛，后面反演后变成$\sum\limits_{d|k}^n\mu(d)h(d)$

$h(d)$ 为与 $d$ 有关的低次多项式且已知

发现只在 $k$ 的因数上有值，把 $k$ 分解出来

因为 $k$ 的因数最大值在 $1500$ 左右，所以是可过的










---

