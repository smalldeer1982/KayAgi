# [THUPC 2023 初赛] 快速 LCM 变换

## 题目描述

小 I 今天学习了快速最小公倍数变换（Fast Least-Common-Multiple Transform, FLT），于是他想考考你。

给定一个长度为 $n$ 的正整数序列 $r_1,r_2,\cdots,r_n$。你需要做以下操作恰好一次：

- 选择整数 $i,j$ 使得 $1 \le i < j \le n$。在序列末尾加入 $(r_i+r_j)$，并将 $r_i$ 和 $r_j$ 从序列中删除。

可以注意到总共有 $\frac{n(n-1)}{2}$ 种可能的操作，每种操作会得到一个长度为 $n-1$ 的序列。

你需要对所有的这 $\frac{n(n-1)}{2}$ 个序列，求出序列中所有元素的最小公倍数，并给出它们的和模 $998244353$ 的值。

## 说明/提示

#### 样例解释 1

- $i=1,j=2$ 时，得到的序列为 $\{4,5\}$，最小公倍数为 $20$；
- $i=1,j=3$ 时，得到的序列为 $\{3,6\}$，最小公倍数为 $6$；
- $i=2,j=3$ 时，得到的序列为 $\{2,7\}$，最小公倍数为 $14$。

因此输出为 $20+6+14=40$。

#### 子任务

对于所有测试数据，$2 \le n \le 5 \times 10^5, 1 \le r_1,r_2,\cdots,r_n \le 10^6$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。

## 样例 #1

### 输入

```
3
2 3 4
```

### 输出

```
40
```

# 题解

## 作者：Mobius127 (赞：7)

[题传](https://www.luogu.com.cn/problem/P9135)

赛时想着莫反去了，有点可惜没想出来，实际上还是挺有趣的。

发现删掉 $a_{i}, a_{j}$ 再加上 $a_{i}+a_{j}$  很不好算，要是能有什么东西能将三个操作的贡献独立分开就好了。

考虑所有数为 $2^{x}$ 的情况，如果一对 $(i,j)$ 会改变原来的 $\operatorname{lcm}$，那么 $i/j$ 至少有一个是 $2$ 的最高次幂，现在假定最高的是 $i$，看 $j$ 和次高的关系。

1. 若 $x_{j}<x_{i}$，则 $i$ 的贡献是 $2^{mx'-x_{i}}$（$mx'$ 是次大值），$j$ 不会产生任何贡献，此时 $a_{i}=2^{k'} a_{j}$，那么 $a_{i}+a_{j}=(2^{k'}+1)a_{j}$，即其指数为 $x_{j}$ 不会产生贡献。

2. 若 $x_{i}=x_{j}$，那么 $a_{i}+a_{j}$ 会多分出一个 $2^{1}$。

不妨令 $h(x)$ 为删掉一个 $x$ 后 $\operatorname{lcm}$ 的变化系数，$g(x)$ 为新增一个 $x$ 后 $\operatorname{lcm}$ 的变化系数。根据上面的讨论，$h(a_{i}),h(a_{j}), g(a_{i}+a_{j})$ 中最多有一个不为 $1$，新的 $\operatorname{lcm}$ 可以用原 $\operatorname{lcm}$ 乘上三者的积得到。

不难推广到多个质数的情况（因为质数之间互不影响）。

那么答案即为 

$$\sum_{i<j} \operatorname{lcm}(a_{k})g(a_{i}+a_{j})h(a_{i})h(a_{j})$$

$$=\operatorname{lcm}(a_{k})\sum_{k} g(k) \sum_{a_{i}+a_{j}=k} h(a_{i})h(a_{j})$$

后面的求和直接卷积做就好了，复杂度 $O(A\log A)$，$A$ 是值域。


### Code:

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <vector>
#include <queue>
#include <bitset>
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using namespace std;
typedef long long ll;
typedef pair <int, int> Pii;
const int INF=0x3f3f3f3f;
const int cp=998244353;
inline int mod(int x){if(x>=cp) x-=cp;if(x<0) x+=cp;return x;}
inline void plust(int &x, int y){x=mod(x+y);return ;}
inline void minut(int &x, int y){x=mod(x-y);return ;}
inline int read(){
char ch=getchar();int x=0, f=1;
while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a, int b=cp-2){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%cp)
		if(b&1) ret=1ll*ret*a%cp;
	return ret;
}
const int g0=3;
const int invg=ksm(g0);
const int inv2=ksm(2);
const int N=5e5+5;
const int M=1.5e3+5;
const int S=2.1e6+5;
const int T=2e6;
const int Pcnt=240;
int n, tot, ans, LCM, pr[Pcnt], mn[S], inv[S], a[N], mx[S], cmx[S];
int g[S], h[N], len=1<<21, f[S], to[S];
void init(){
	n=read();for(int i=1; i<=n; ++i) a[i]=read();inv[0]=inv[1]=1;
	for(int i=2; i<=T; ++i) inv[i]=1ll*(cp-cp/i)*inv[cp%i]%cp;
	mn[1]=1;for(int i=2; i<=T; ++i) if(!mn[i]) for(int j=i; j<=T; j+=i) mn[j]=i;
	for(int i=1; i<=n; ++i){
		int x=a[i];
		while(x>1){
			int p=mn[x], s=1;
			while(mn[x]==p) x/=p, s*=p;
			if(mx[p]<s) swap(mx[p], s);
			if(cmx[p]<s) swap(cmx[p], s);
		}
	}
	LCM=1;
	for(int i=1; i<=T; ++i) if(mx[i]) LCM=1ll*LCM*mx[i]%cp;
	for(int i=1; i<=n; ++i){
		int x=a[i], t=LCM;
		while(x>1){
			int p=mn[x], s=1;
			while(mn[x]==p) x/=p, s*=p;
			if(cmx[p]<s) t=1ll*t*inv[s]%cp*max(1, cmx[p])%cp;
		}
		h[i]=t;
	}
	for(int i=1; i<=T; ++i){
		int x=i, t=LCM;
		while(x>1){
			int p=mn[x], s=1;
			while(mn[x]==p) x/=p, s*=p;
			if(mx[p]<s) t=1ll*t*inv[mx[p]]%cp*s%cp;
		}
		g[i]=t;
	}
}
void NTT(int *F, int flag){
	for(int i=0; i<len; i++)
		if(i<to[i]) swap(F[i], F[to[i]]);
	for(int s=2; s<=len; s<<=1){
		int size=s>>1;
		int omega=ksm(flag>0?g0:invg, (cp-1)/s);
		for(int L=0; L<len; L+=s){
			int buf=1;
			for(int i=L; i<L+size; i++, buf=1ll*omega*buf%cp){
				int F2=1ll*buf*F[i+size]%cp;
				F[i+size]=mod(F[i]-F2);
				F[i]=mod(F[i]+F2);
			}
		}
	}
	if(~flag) return ;int invlen=ksm(len);
	for(int i=0; i<=len; ++i) F[i]=1ll*F[i]*invlen%cp;
}
signed main(){
	init();
	memset(f, 0, sizeof(f));
	for(int i=1; i<=n; ++i) plust(f[a[i]], h[i]);
	for(int i=0; i<=len; i++) to[i]=(to[i>>1]>>1)|((i&1)?len>>1:0);
	NTT(f, 1);
	for(int i=0; i<=len; ++i) f[i]=1ll*f[i]*f[i]%cp;
	NTT(f, -1);
	for(int i=1; i<=n; ++i) minut(f[a[i]+a[i]], 1ll*h[i]*h[i]%cp);
	// for(int i=1; i<=8; ++i) printf("%d*%d ", f[i], g[i]);
	for(int i=1; i<=T; ++i) plust(ans, 1ll*f[i]*g[i]%cp);
	LCM=1ll*LCM*LCM%cp;LCM=ksm(LCM);
	ans=1ll*ans*LCM%cp;ans=1ll*ans*inv2%cp;
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：Alex_Wei (赞：5)

> [P9135 [THUPC 2023 初赛] 快速 LCM 变换](https://www.luogu.com.cn/problem/P9135)

对质数 $p$，我们单独分析贡献。设 $r_i$ 有 $k_1$ 个 $p$（$k_1 = v_p(r_i)$），$r_j$ 有 $k_2$ 个 $p$，$r_i + r_j$ 有 $k_3$ 个 $p$，且 $p$ 在所有 $r_i$ 的最高次数为 $mx_p$，第二大次数为 $smx_p$。不妨设 $k_1 \geq k_2$。

- 当 $k_1 > k_2$ 时，$k_3 = k_2$。此时若 $a_i = mx_p$，则 $p$ 的指数变成 $smx_p$，否则指数不变。注意这和 $k_2$ 是否等于 $smx_p$ 无关。
- 当 $k_1 = k_2$ 时，$k_3\geq k_1$。$p$ 的指数变成 $\max(k_3, smx_p)$。

考虑设 $c_i$ 表示若去掉 $i$，则 $\operatorname{lcm}$ 会变成原来的多少倍，即若 $v_p(r_i) = mx_p$，则 $c_i$ 乘上 $\frac 1 {p ^ {mx_p - smx_p}}$。计算 $(i, j)$ 的贡献时，先考虑情况一，当成 $c_ic_j$ 算，再加入 $r_i + r_j$ 的情况二的贡献：若 $v_p(r_i + r_j) > mx_p$，则 $\operatorname{lcm}$ 乘上 $p ^ {v_p(r_i + r_j) - mx_p}$。

对于每个 $k$，计算使得 $r_i + r_j = k$ 的 $c_ic_j$ 的贡献是标准卷积形式，NTT 即可。

时间复杂度 $\mathcal{O}(V\log V)$，其中 $V$ 是值域。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

bool Mbe;
constexpr int N = 1 << 21;
constexpr int mod = 998244353;
constexpr int iv3 = (mod + 1) / 3;
void add(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

int rev[N];
void NTT(int L, int *a, int type) {
  static ull f[N], w[N];
  for(int i = 0; i < L; i++) {
    rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? L >> 1 : 0);
    f[i] = a[rev[i]];
  }
  for(int d = 1; d < L; d <<= 1) {
    int wn = ksm(type ? 3 : iv3, (mod - 1) / (d + d));
    for(int i = w[0] = 1; i < d; i++) w[i] = w[i - 1] * wn % mod;
    for(int i = 0; i < L; i += d + d)
      for(int j = 0; j < d; j++) {
        int y = f[i | j | d] * w[j] % mod;
        f[i | j | d] = f[i | j] + mod - y, f[i | j] += y; 
      }
    if(d == (1 << 16)) for(int i = 0; i < L; i++) f[i] %= mod;
  }
  int inv = ksm(L, mod - 2);
  for(int i = 0; i < L; i++) a[i] = f[i] % mod * (type ? 1 : inv) % mod;
}

int vis[N], pr[N], mpr[N], cnt;
int n, r[N], coe[N], f[N];
pair<int, int> mx[N], smx[N];
vector<pair<int, int>> buc[N];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for(int i = 2; i < N; i++) {
    if(!vis[i]) pr[++cnt] = mpr[i] = i;
    for(int j = 1; j <= cnt && i * pr[j] < N; j++) {
      vis[i * pr[j]] = 1, mpr[i * pr[j]] = pr[j];
      if(i % pr[j] == 0) break;
    }
    int tmp = i;
    while(tmp > 1) {
      int p = mpr[tmp], c = 0;
      while(tmp % p == 0) tmp /= p, c++;
      buc[i].push_back({p, c});
    }
  }
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> r[i], coe[i] = 1;
    for(auto _ : buc[r[i]]) {
      int p = _.first, c = _.second;
      pair<int, int> v = {c, i};
      if(v > mx[p]) smx[p] = mx[p], mx[p] = v;
      else if(v > smx[p]) smx[p] = v;
    }
  }
  int lcm = 1;
  for(int i = 2; i < N; i++) {
    if(!mx[i].first) continue;
    lcm = 1ll * lcm * ksm(i, mx[i].first) % mod;
    int v = ksm(i, mx[i].first - smx[i].first);
    coe[mx[i].second] = 1ll * coe[mx[i].second] * ksm(v, mod - 2) % mod;
  }
  for(int i = 1; i <= n; i++) add(f[r[i]], coe[i]);
  NTT(N, f, 1);
  for(int i = 0; i < N; i++) f[i] = 1ll * f[i] * f[i] % mod;
  NTT(N, f, 0);
  for(int i = 1; i <= n; i++) add(f[r[i] + r[i]], mod - 1ll * coe[i] * coe[i] % mod);
  int ans = 0;
  for(int i = 1; i < N; i++) {
    if(!f[i]) continue;
    int other = 1;
    for(auto _ : buc[i]) {
      int p = _.first, c = _.second;
      other = 1ll * other * ksm(p, max(0, c - mx[p].first)) % mod;
    }
    add(ans, 1ll * lcm * other % mod * f[i] % mod);
  }
  cout << 1ll * ans * (mod + 1 >> 1) % mod << "\n";
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

简单数学题。

首先，考虑对于所有素数，求出它在 $r$ 中出现的最大幂次。假设质数 $p$ 的最大幂次为 $w_p$。那么所有数的最小公倍数就是 $\prod p^{w_p}$。

然后考虑你删掉了 $r_i$ 和 $r_j$ 并且加上了 $r_i+r_j$ 会产生什么样的影响。

我们发现，我们只需要关系质数的幂次中最大值，次大值和第三大值，我们记为 $a$，$b$ 和 $c$。

我们首先要明白一个事实：记 $v_p(n)$ 为 $n$ 中因子 $p$ 的个数。那么如果 $v_p(x) \neq v_p(y)$，那么 $v_p(x+y) = \min \{ v_p(x),v_p(y)\}$。

那么你考虑，如果 $a = b$，那么无论如何，$p$ 的最大幂次不会变小。我们直接忽略这个素数，最后只需要比较 $v_p(r_i+r_j)$ 和 $a$ 的大小即可。

否则，考虑如果你不取走最大值，那么实际上与上面这种情况是类似的。

因此我们只需要单独考虑取走了最大值的情况。

如果另一个取走了次大值，很显然 $v_p(r_i+r_j)=b$，最终 $p$ 的幂次是 $b$；如果另一个取走了其他的数，很显然 $v_p(r_i+r_j) \le b$，最终 $p$ 的幂次还是 $b$。

于是，相当于最大值自带一个 $p^{b-a}$ 的 debuff。

因此我们可以这样做：

每个数有一个权值 $c_i$ 表示它的 debuff。（这个对于每个质数可以单独处理出来）

考虑求出 $\sum_{i<j , r_i+r_j=t} c_ic_j$ 的值。这个可以 NTT 之后稍加处理即可。（删掉 $i=j$ 的部分之后除以 $2$，让我想起了 CMO2023P2 的惨状，痛失 $21$ 分）

然后考虑处理一下 $t$ 中超过原有质因子最大幂次的质因子幂次。把所有答案一并修改一下即可。

好久没写代码了，可能写的有点丑，凑合着看看。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e6+10,MOD=998244353;
int qpow(int base,int p) {
	int res=1;
	while(p) {
		if(p&1) res=res*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return res;
}
int n,m,a[MAXN],c[MAXN],fv[MAXN];
//=====POLY======
int rev[MAXN];
void init_rev(int l,int r,int val) {
	int mid=l+r>>1;
	rev[mid+1]+=val,rev[r+1]-=val;
	if(l==r) return ;
	init_rev(l,mid,val<<1),init_rev(mid+1,r,val<<1);
	return ;	
}
void NTT(int *f,int op) {
	ffor(i,0,m-1) if(rev[i]>i) swap(f[i],f[rev[i]]);
	int lst=1;
	while(lst<m) {
		int len=lst,omega=qpow(3,(MOD-1)/(lst<<1)); lst<<=1;
		if(op==-1) omega=qpow(omega,MOD-2);
		ffor(i,0,m/lst-1) {
			int l=i*lst,r=(i+1)*lst-1,tmp=1;
			ffor(j,l,l+len-1) {
				int x=f[j],y=f[j+len];
				f[j]=(x+tmp*y)%MOD,f[j+len]=(x-tmp*y)%MOD,tmp=tmp*omega%MOD;
			}
		}
	}
	if(op==-1) {
		int inv=qpow(m,MOD-2);
		ffor(i,0,m-1) f[i]=f[i]*inv%MOD;	
	}
	return ;
}
//======Number Theory=====
int flg[MAXN],lst[MAXN];
vector<int> pr;
void init(int Mx) {
	ffor(i,2,Mx) {
		if(flg[i]==0) pr.push_back(i),lst[i]=i;
		for(auto v:pr) {
			if(i*v>Mx) break;
			flg[i*v]=1,lst[i*v]=v;
			if(i%v==0) break;
		}
	}
	return ;
}
//=====Two values=====
pair<int,int> mx[MAXN],nmx[MAXN];
void update(int pos,pair<int,int> pr) {
	if(pr>mx[pos]) nmx[pos]=mx[pos],mx[pos]=pr;
	else if(pr>nmx[pos]) nmx[pos]=pr;
	return ;
}
void dvd(int v,int id) {
	while(v!=1) {
		int p=lst[v],cnt=0;
		while(v%p==0) cnt++,v/=p;
		update(p,{cnt,id});
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i];
	m=(1<<21); init_rev(0,m-1,1); ffor(i,1,m-1) rev[i]+=rev[i-1];
	init(2000000);
	ffor(i,1,n) dvd(a[i],i),c[i]=1;
	for(auto p:pr) {
		if(mx[p].first==nmx[p].first) continue ;
		c[mx[p].second]=c[mx[p].second]*qpow(qpow(p,MOD-2),mx[p].first-nmx[p].first)%MOD;
	}
	ffor(i,1,n) fv[a[i]]=(fv[a[i]]+c[i])%MOD;
	NTT(fv,1);
	ffor(i,0,m-1) fv[i]=fv[i]*fv[i]%MOD;
	NTT(fv,-1);
	int ans=0,tmp=1;
	ffor(i,1,n) fv[a[i]+a[i]]=(fv[a[i]+a[i]]-c[i]*c[i])%MOD;
	ffor(i,0,m-1) fv[i]=(fv[i]*(MOD+1)/2)%MOD;
	for(auto p:pr) tmp=tmp*qpow(p,mx[p].first)%MOD;
	ffor(i,1,2000000) {
		int mul=1,k=i;
		while(k!=1) {
			int p=lst[k],cnt=0;
			while(k%p==0) cnt++,k/=p;
			if(cnt>mx[p].first) mul=mul*qpow(p,cnt-mx[p].first);	
		}
		ans=(ans+tmp*mul%MOD*fv[i])%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：chroneZ (赞：1)

考虑将操作的贡献拆分为删除和加入两部分的贡献。计数对象是所有元素的 $\text{lcm}$，因此可以对每个质数 $p$ 单独分析。记 $v_p(x)$ 表示 $x$ 的唯一分解中 $p$ 的指数，并记 $k_i \gets v_p(a_i), k_j \gets v_p(a_j), m_p = \max v_p(a), m'_p$ 为**非严格**次大 $v_p(a)$。不妨设 $k_i \geq k_j$。

删除元素 $a_i$ 时 $\text{lcm}$ 发生改变的必要条件是 $k_i = m_p$（与 $k_j$ 是否为 $m'$ 无关），此时 $p$ 的指数会变为 $m'_p$，因此贡献（$\text{i.e. lcm}$ 的变化系数）为 $\frac{1}{p^{m_p - m'_p}}$。用 $d_{i} = [k_i = m_p] \frac{1}{p^{m_p - m'_p}}$ 表示删除 $a_i$ 的贡献。则删除 $a_i, a_j$ 的贡献可以被表示为 $d_{i}d_{j}$（即使存在 $m_p = m'_p$ 的情况，可以发现这样计算也是正确的）。

加入 $x = a_i + a_j$ 时，贡献为 $h_x = p ^ {\max(0, v_p(x) - m_p)}$（此处忽略了 $x$ 中其它非 $p$ 的质因子的贡献）。至此我们可以把操作对质因子 $p$ 的贡献表示为 $d_id_jh_{a_i + a_j}$，可以证明这样计算不会使删除和加入两部分的贡献产生冲突。

推广到多个质数的情况，有 $d'_i = \prod_p [v_p(a_i) = m_p]\frac{1}{p^{m_p - m'_p}}$，$h_x = \prod_p p^{\max(0, v_p(x) - m_p)}$，操作贡献依旧可以表示为 $d'_id'_jh_{a_i + a_j}$。记 $L \gets $ 原序列 $\text{lcm}$，答案可写作
$$
\sum_{i < j} d'_{i}d'_{j}h_{a_i + a_j}L
$$
将 $d'$ 的定义域转为值域，记 $c_x$ 表示 $x$ 在 $a$ 中的出现次数，得 $d_{x} = c_x\prod_p [v_p(x) = m_p] \frac{1}{p ^ {m_p - m'_p}}$。转为枚举值域，得
$$
L\sum_k h_k \sum_{x + y = k} d_xd_y
$$
后式是一个比较明显的卷积，因此可以 $\mathcal{O}(V \log V)$ 计算。

注意计算结果需要减去选择了同一个数的情况，即 $L\sum_{i = 1} ^ n {d'_i}^ 2h_{2a_i}$（注意是 $d'$ 而非 $d$），由于选择是无序的最后应除以 $2$。

---

