# [AGC003D] Anticube

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc003/tasks/agc003_d

高橋君は誕生日にお母さんから正の整数 $ s_1,...,s_N $ をもらいました。ただし、要素の重複は許されます。 高橋君は、これらの$ N $個の整数のうちのいくつかを丸で囲みます。

高橋君は立方数が嫌いなので、$ s_i,s_j(i\ ≠\ j) $の両方が丸で囲まれているなら、その積$ s_is_j $は立方数とならないようにしたいです。 例えば、$ s_1=1,s_2=1,s_3=2,s_4=4 $のとき、$ s_1 $と$ s_2 $を同時に丸で囲むことはできません。また、$ s_3 $と$ s_4 $を同時に丸で囲むこともできません。

高橋君が丸で囲むことができる整数の個数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ s_i\ ≦\ 10^{10} $
- 入力はすべて整数である。

### Sample Explanation 1

$ 1,2,3,5,6,7 $ を丸で囲むことができます。

## 样例 #1

### 输入

```
8
1
2
3
4
5
6
7
8```

### 输出

```
6```

## 样例 #2

### 输入

```
6
2
4
8
16
32
64```

### 输出

```
3```

## 样例 #3

### 输入

```
10
1
10
100
1000000007
10000000000
1000000009
999999999
999
999
999```

### 输出

```
9```

# 题解

## 作者：CYJian (赞：21)

## AGC003D

这道题不算很难，不过有需要注意的小细节。

首先第一步是非常清晰的：先把所有数按照某种条件分解。

我们会发现，如果直接分解出所有的质因数，复杂度就是 $O(n \sqrt{s_{mx}})$ 的，妥妥 T 飞。

考虑优化：我们首先先剔除掉每个数里形如 $x^3$ 的因子。注意到 $x \in [1, \sqrt[3]{s_{mx}}]$ ，并且只需要枚举这个范围内的质数，所以可以很快做完这一步。

删除掉立方因子之后，如果有剩下 $1$，那么答案至少有 $1$。

然后考虑其他的数：我们再用 $x \in [1,\sqrt[3]{s_{mx}}]$ 的所有质数 $x$ 来分解掉所有的 $s_i$。然后我们可以发现，这时候 $s_i$ 至多有两个质因子。然后我们按以下几种情况讨论以下：

- 如果 $s_i=1$，那就将其上一步分解出来的 $x$ 的乘积放入第三类数中；
- 否则如果这个 $s_i$ 是完全平方数，那么我们把它上一步分解的 $x$ 的乘积分到第一类数中；
- 否则如果 $s_i$ 是一个在 $\sqrt{s_{mx}}$ 范围内的质数，则分到第二类数中；
- 否则就一定不存在一个数能和它相乘得到一个完全平方数，它就可以直接放进答案。（若不能直接领会，请看下文 证明 部分。）

不难发现，这时候能通过相乘变成完全立方数的情况，只会发生在 第三类数 $\times$ 第三类数 ； 第一类数 $\times$ 第二类数 中。

先考虑 第三类数 $\times$ 第三类数。这个时候的乘积是一一对应的关系（去除所有立方因子），可以找到其对应的一个数，然后扔进 ${\rm map}$ 里头直接计数取最大就好了。

然后就是 第一类数 $\times$ 第二类数，这里还有一个大于 $\sqrt[3]{s_{mx}}$ 的数的限制。不过可以直接用 ${\rm vector}$ 当桶直接装下，然后对于 第一类数，放进其剩下的 $\sqrt{s_i}$ 这个桶里头，对于第二类数，直接放进剩下的 $s_i$ 这个桶里头。然后对于两类数相同的桶，就可以类比上一种情况，直接统计取最大就好了。

复杂度 $O(n \log n + n \sqrt[3]{s_{mx}})$，实测效率挺高的。

---

证明：

首先显然的是，如果这个 $s_i$ 是大于 $\sqrt{s_{mx}}$ 的质数，那么以它为因子的最小完全立方数是大于 $s_{mx}^{\frac{3}{2}}$ 的。超出了数据范围，不存在能构成完全立方数的情况。

如果经过 $x \in [1, \sqrt[3]{s_{mx}}]$ 的 $x$ 筛过 $s_i$ 之后，$s_i$ 既不是完全平方数，也不是一个质数，那么其一定是通过两个 $p \in [\sqrt[3]{s_{mx}},\sqrt{s_{mx}}]$ 的质数 $p_1,p_2$ 相乘得到。注意到如果要有另一个数能和其相乘得到一个完全平方数，则必须至少包含 $p_1^2p_2^2$ 这个因子。显然这一项的范围在 $[s_{mx}^{\frac{4}{3}},s_{mx}^2]$ 内，超出数据范围，所以不可能存在构成完全立方数的情况。

---

${\rm Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

const int MAXN = 100010;

ll sq3[2200];
ll s[MAXN];

int tot;
int pri[2200];
int chk[2200];

inline void Get_Prime(int n) {
	for(int i = 2; i <= n; i++) {
		if(!chk[i]) pri[++tot] = i;
		for(int j = 1; j <= tot; j++) {
			if(i * pri[j] > n) break;
			chk[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
		}
	}
}

inline void init(int n) {
	for(int i = 1; i <= n; i++)
		sq3[i] = 1LL * i * i * i;
}

inline ll work(ll x) {
	for(int i = 1; i <= tot; i++)
		while(x % sq3[pri[i]] == 0) x /= sq3[pri[i]];
	return x;
}

inline ll doit(ll&s, ll&x, ll&r) {
	x = r = 1;
	for(int i = 1; i <= tot; i++)
		if(s % pri[i] == 0) {
			if(s % (pri[i] * pri[i]) == 0) r *= pri[i], x *= pri[i] * pri[i];
			else x *= pri[i], r *= pri[i] * pri[i];
			while(s % pri[i] == 0) s /= pri[i];
		}
	return s;
}

struct Node {
	ll t, r;

	Node() {}
	Node(ll t, ll r):t(t), r(r) {}
};

vector<Node> c1[MAXN];
vector<Node> c2[MAXN];
map<ll, int> mp1, mp2;

int main() {
#ifdef LOCAL
	FILE("");
#endif

	init(2160), Get_Prime(2160);

	int n = ri;
	for(int i = 1; i <= n; i++) s[i] = work(rl);
	sort(s + 1, s + 1 + n);

	int res = s[1] == 1;
	for(int i = 1; i <= n; i++) {
		if(s[i] == 1) continue;
		ll t, r;
		ll v = sqrt(doit(s[i], t, r));
		while(v * v > s[i]) --v;
		while(v * v < s[i]) ++v;
		if(v * v == s[i]) c2[v].push_back(Node(t, r));
		else if(s[i] <= 100000) c1[s[i]].push_back(Node(t, r));
		else ++res;
	}

	for(auto x : c2[1]) c1[1].push_back(x);
	for(auto x : c1[1]) mp1[x.t]++;
	for(auto x : c1[1]) res += max(mp1[x.t], mp1[x.r]), mp1[x.t] = mp1[x.r] = 0;

	for(int i = 2; i <= 100000; i++)
		if(!c1[i].size() || !c2[i].size()) res += c1[i].size() + c2[i].size();
		else {
			mp1.clear(), mp2.clear();
			for(auto x : c1[i]) mp1[x.t]++;
			for(auto x : c2[i]) mp2[x.t]++;
			for(auto x : c1[i]) res += max(mp1[x.t], mp2[x.r]), mp1[x.t] = mp2[x.r] = 0;
			for(auto x : c2[i]) res += max(mp2[x.t], mp1[x.r]), mp2[x.t] = mp1[x.r] = 0;
		}
	
	cout << res << endl;
	return 0;
}
```

---

## 作者：LinkWish (赞：13)

题解区没有用网络流求答案的，蒟蒻就来发一发题解。至于为什么用网络流，当然是没有想到直接算答案的方法，而且网络流也容易想到。

本题解分成两部分：分解质因数与答案求解。

在这之前，我们先考虑什么情况下，两个数不能被同时选择。

可以发现，设 $x=\prod\limits_{i=1}p_i^{a_i},y=\prod\limits_{i=1}p_i^{b_i}$，则 $xy=\prod\limits_{i=1}p_i^{a_i+b_i}$。如果 $xy$ 是一个完全立方数，那么一定满足 $\forall i,a_i+b_i\equiv 0 \pmod{3}$。

那么，我们将所有的满足 $\forall i,a_i\equiv b_i \pmod{3}$ 的 $x,y$ 视作相同的数，那么我们就可以拿重新定义的这些数去进行匹配。

## part 1 分解质因数

由于值域为 $10^{10}$，我们不可以直接使用根号算法分解质因数，可以考虑如下算法：

对于当前数 $x$，首先将所有小于等于 $\sqrt[3]{x}$ 的质因数分解，设分解后的数为 $x'$。易知 $x'$ 的组成有三种：$1$ 或两个质数相乘或一个质数。

如果 $x'\leq 10^5$，我们就将其剩下的质因数分解出来，或判定其为质数。现在我们给 $x'^2$ 标记为 $x'$ 所有质因数的平方，只有 $x'^2$ 才能与 $x'$ 组成一个完全立方数。

如果 $x'> 10^5$，我们就看它有没有被标记过即可。

## part 2 网络流建边

由于我们重新定义了数的相等，易知一个数与另一个数相乘能组成完全立方数的匹配是唯一的，如果我们将乘起来能够组成完全立方数的数对连边，容量为 $\infty$，然后对原图染色，源点向每个白点连接一条容量等于其数量的边，每个黑点向汇点连接一条容量等于其数量的边，跑最小割即可，由于是二分图，所以复杂度为 $\Theta(n\sqrt{m})$。

注意，原本就为完全立方数的数只能算一个。

时间复杂度：$\Theta(10^{\frac{10}{3}}n+n\sqrt{m})$。

代码还是比较可读的，细节在代码里了。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
typedef const int ci;
typedef long long ll;
typedef pair<int,int> pii;
const int iinf=0x7fffffff;
const ll linf=4e18;
using namespace std;
ci N=100005,s=0,t=N-1,lim=100000;
struct edge{
	int to,w,de;
	inline edge(int x,int y,int z){to=x,w=y,de=z;}
};
vector<edge> e[N];
inline void add(int x,int y,int w){
	e[x].emplace_back(y,w,e[y].size());
	e[y].emplace_back(x,0,e[x].size()-1);
}
int cnt[N],fl[N],num,tot;
inline int np(){
	num++,tot++;
	return num;
}
int isap(int x,int val){
	if(x==t||!val)return val;
	int now=val,res;
	for(edge &i:e[x]){
		if(i.w>0&&fl[x]==fl[i.to]+1){
			res=isap(i.to,min(i.w,now));
			i.w-=res,e[i.to][i.de].w+=res,now-=res;
			if(!now)return val;
		}
	}
	cnt[fl[x]]--;
	if(!cnt[fl[x]])fl[s]=tot;
	cnt[++fl[x]]++;
	return val-now;
}
inline int work(){
	cnt[0]=tot;
	int ans=0;
	while(fl[s]<tot)ans+=isap(s,iinf);
	return ans;
}
bool is[N];
int p[N],amt;
inline void init(){
	memset(is,1,sizeof is);
	is[1]=0;
	for(int i=2;i<=lim;i++){
		if(is[i])p[++amt]=i;
		for(int j=1;j<=amt&&i*p[j]<=lim;j++){
			is[i*p[j]]=0;
			if(i%p[j]==0)break;
		}
	}
}
map<vector<pii>,pii> q;
map<int,vector<pii>> vis;
map<int,pii> tag;
map<int,bool> did;
bool flag[N];
inline vector<pii> rev(vector<pii> x){
	for(pii &i:x)i.se=3-i.se;
	return x;
}
int cub;
inline void f(int x){
	if(vis.count(x))return ;
	vector<pii> now;
	int org=x;
	for(int i=1;i<=amt&&p[i]*p[i]*p[i]<=x;i++){
		if(x%p[i]==0){
			int pk=0;
			while(x%p[i]==0)x/=p[i],pk++;
			if(pk%3)now.push_back({p[i],pk%3});
		}
	}
	if(x<=lim){
		for(int i=1;i<=amt&&p[i]*p[i]<=x;i++){
			if(x%p[i]==0){
				if(p[i]*p[i]==x){
					now.push_back({p[i],2});
					tag[x*x]={p[i],p[i]};
				}
				else{
					now.push_back({p[i],1});
					now.push_back({x/p[i],1});
					tag[x*x]={p[i],x/p[i]};
				}
				x=1;
				break;
			}
		}
		if(x>1){
			now.push_back({x,1});
			tag[x*x]={x,-1};
		}
	}
	else if(x>1)now.push_back({x,1});
	vis[org]=now;
}
inline void push(int x){
	if(did[x])return ;
	vector<pii> &now=vis[x];
	if(now.empty())return ;
	x=now.back().fi;
	if(x>lim&&tag.count(x)&&now.back().se==1){
		now.pop_back();
		if(tag[x].se==-1)now.push_back({tag[x].fi,2});
		else if(tag[x].fi==tag[x].se)now.push_back({tag[x].fi,1});
		else now.push_back({tag[x].fi,2}),now.push_back({tag[x].se,2});
	}
	sort(now.begin(),now.end());
	did[x]=1;
}
inline void match(int x){
	vector<pii> now=vis[x];
	if(!q.count(now)){
		pii &it=q[now];
		it.fi++,it.se=np();
		if(q.count(rev(now))&&now.size()){
			pii lst=q[rev(now)];
			flag[it.se]=flag[lst.se]^1;
			if(flag[lst.se])add(it.se,lst.se,iinf);
			else add(lst.se,it.se,iinf);
		}
		else flag[it.se]=0;
	}
	else if(now.size())q[now].fi++;
	else cub++;
}
int n,a[N];
signed main(){
	tot=2;
	init();
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)f(a[i]);
	for(int i=1;i<=n;i++)push(a[i]);
	for(int i=1;i<=n;i++)match(a[i]);
	for(auto &[x,y]:q){
		if(flag[y.se])add(y.se,t,y.fi);
		else add(s,y.se,y.fi);
	}
	cout<<n-cub-work();
	return 0;
}
```


---

## 作者：K8He (赞：12)

## [「题解报告」[AGC003D] Anticube](https://www.luogu.com.cn/problem/AT_agc003_d)

首先想到暴力，然后发现数据范围太大了。

一个显而易见的思路是，对于一个数 $x$ 我们把他分解质因数成 $p_{1}^{k_1}p_{2}^{k_2}\cdots p_{n}^{k_n}$，会有一个对应数 $x' = p_{1}^{k_1\bmod{3}}p_{2}^{k_2\bmod{3}}\cdots p_{n}^{k_n\bmod{3}}$，若存在一个 $y$ 的对应数 $y'$ 与 $x'$ 的积为立方数，那么 $x$ 与 $y$ 的积也是立方数。

不难发现对于一个已知的 $x'$，与它对应的 $y'$ 也是一定的。那么对于一组对应的 $x',y'$，选了其中一个就不能选另一个，且对其他数的选取不会产生任何影响。因此我们只需要统计出所以可能的 $x'$ 的数量，在 $x'$ 与其对应的 $y'$ 中选取数量最多的一个。

对于一个已知的 $x$，$x'$ 是很好求的，只需要枚举 $[2, 10^{\frac{10}{3}}]$ 之间的质数的立方。问题是如何快速求对应的 $y'$？

首先我们把 $x'$ 小于 $10^{\frac{10}{3}}$ 的质因数 $p_i$全部除掉，并让 $y'$ 乘上 $p_i^{2k_i\bmod{3}}$，然后考虑剩下的数是什么情况（这里的质数都大于 $10^{\frac{10}{3}}$）：

- 一个质数。
- 两个质数之积。
- 一个质数的平方。

对于前两种情况，令 $y'$ 乘上这个数的平方；对于第三种情况，令 $y'$ 乘上这个质数。

这里 $10^{\frac{10}{3}}$ 可以直接取 $2160$。

Code:

```cpp
const ll N = 1e5 + 10;
namespace SOLVE {
	ll n, a[N], b[N], vis[N], ans;
	std::vector <ll> prime;
	std::map <ll, ll> mp;
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline void Pre () {
		_for (i, 2, 2160) {
			if (!vis[i]) prime.push_back (i);
			far (j, prime) {
				if (i * j > 2160) break;
				vis[i * j] = 1;
				if (!(i % j)) break;
			}
		}
		return;
	}
	inline void In () {
		n = rnt ();
		_for (i, 1, n) a[i] = rnt ();
		return;
	}
	inline void Solve () {
		Pre ();
		_for (i, 1, n) {
			far (j, prime) {
				ll x = j * j * j;
				while (!(a[i] % x)) a[i] /= x;
			}
			ll qwq = a[i]; ++mp[a[i]], b[i] = 1;
			far (j, prime) {
				if (qwq % j) continue;
				if (!(qwq % (j * j))) b[i] *= j;
				else b[i] *= j * j;
				while (!(qwq % j)) qwq /= j;
			}
			ll s = (ll)(sqrt (qwq));
			if (s * s == qwq) b[i] *= s;
			else b[i] *= a[i] * a[i];
		}
		_for (i, 1, n) {
			if (a[i] == 1) continue;
			ans += std::max (mp[a[i]], mp[b[i]]);
			mp[a[i]] = mp[b[i]] = 0;
		}
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans + (bool)(mp[1]));
		return;
	}
}
```

---

## 作者：yijan (赞：12)

这个数据范围不太能分解质因数。

于是考虑枚举 $\sqrt[3]{A_i}$ 内得质因子，于是我们可以把每个数分解成质数次幂不超过 $3$ ，高于 $3$ 直接 $\bmod 3$ 即可。这样操作后，不难发现每个 $A_i$ 对应着唯一一种数，也就是每个次幂取反后的数，它们俩乘起来会得到一个立方数。于是一个显然的思路就是，对于每个数求出它对应的数，然后看这俩数哪个出现的次数大，拿出现的多的。

但是这有一个问题，我们怎么求出在 $\sqrt[3]{x}$ 到 $\sqrt x$ 之间的质因子以及次数呢？

如果我们把一个数的所有不到 $\sqrt[3]{x}$ 的质因子全部除去，那么剩下的这个数一定长成 $pq,p^2,p$ 这三种形式之一。如果这个数不到 $10^5$ ，显然这个数不可能是 $p^2,pq$ 的形式，因为如果这样必然存在不到 $\sqrt[3]{x}$ 的质因子。所以我们直接给它的对应数乘上 $p^2$ 即可。

剩下的数大于了 $10^5$ 考虑如果剩下的是 $p$ ，那么明显，不可能有一个数和这个数对应。因为如果存在一个对应的数，那么这个数至少有 $p^2$ 这个因子，但是它已经爆掉 $10^{10}$ 了。

如果剩下的是 $pq$ ，那么对应数至少有 $p^2q^2$ ，它又爆掉 $10^{10}$ 了。

也就是说我们只需要判一下剩下的数是否为一个平方数，如果是，我们就给对应数乘上 $\sqrt c$ 即可。

复杂度 $O(n\sqrt[3]{A_i} + n\log n)$ 。

```cpp
int n;
ll A[MAXN];
int pri[MAXN] , en , ee , isp[MAXN];
void sieve( ) {
	for( int i = 2 ; i < MAXN ; ++ i ) {
		if( !isp[i] ) pri[++ en] = i;
		if( !ee && i > 4000 ) ee = en;
		for( int j = 1 ; j <= en && pri[j] * i < MAXN ; ++ j ) {
			isp[i * pri[j]] = 1;
			if( i % pri[j] == 0 ) break;
		}
	}
}

ll Sqrt( ll x ) {
	int t = sqrt( 1. * x );
	rep( i , max( 1 , t - 5 ) , t + 5 ) if( i * 1ll * i == x ) return i;
	return -1;
}

map<ll,ll> cn , to;
void solve() {
	sieve( );
	cin >> n;
	rep( i , 1 , n ) {
		scanf("%lld",A + i);
		ll rv = 1 , c = A[i];
		rep( j , 1 , ee ) if( A[i] % pri[j] == 0 ) {
			ll p3 = pri[j] * pri[j] * 1ll * pri[j] , p2 = pri[j] * pri[j];
			while( A[i] % p3 == 0 ) A[i] /= p3 , c /= p3;
			if( A[i] % p2 == 0 ) 
				rv *= pri[j];
			else if( A[i] % pri[j] == 0 )
				rv *= p2;
			while( c % pri[j] == 0 ) c /= pri[j];
		}
		if( c > 100000 ) {
			ll t = Sqrt( c );
			if( t == -1 ) rv = -1;
			else if( !isp[t] ) {
				rv *= t;
			} else assert( 0 );
		} else if( c != 1 ) {
			if( !isp[c] ) rv *= c * 1ll * c;
			else rv = -1;
		}
		to[A[i]] = rv;
		++ cn[A[i]];
	}
	int as = 0;
	for( auto [x , t] : cn ) {
//        cout << x << ' ' << t << ' ' << to[x] << ' ' << as << endl;
		if( !cn.count( to[x] ) ) as += t;
		else if( x < to[x] ) {
			if( cn.count( to[x] ) ) if( x < to[x] ) as += max( t , cn[to[x]] );
		}
	}
	cout << as + cn.count( 1 ) << endl;
}

signed main() {
//    int T;cin &gt;&gt; T;while( T-- ) solve();
    solve();
}
```

---

## 作者：louhao088 (赞：10)

一道比较好的根号分治题。


------------


我们令 $s_i$ 表示 $s_i$ 的最大值。

首先我们发现两数积是完全立方数，当且仅当两数乘起来后所有质因子都是 3 的幂次方。

我们可以先把每个数的大于三次方的因子，每次减三，直至小于三次，那么上述条件就变为：两数积是完全立方数，当且仅当两数乘起来后所有质因子的次数都是 3。

而且这样每个数质因数只可能是 1 次，或 2次。条件可以进一步强化，两数积是完全立方数，当且仅当两数拥有的质因子相同，且 1 个次数为 1，1 个次数为 2。


------------

我们很容易想到 $n \sqrt s_i $ 的做法，即对质数是否大于 $\sqrt s_i$ 讨论。然而，$s_i$ 非常大，竟有 $10^{10}$。很明显这样做是不行的。


------------

那么我们考虑优化，我们虽然不能分类 $\sqrt s_i$ ，但我们可以分类 $\sqrt[3] s_i$ 的质数。

首先我们用 $n\sqrt[3] s_i$ 的时间，把所有小于 $\sqrt[3] s_i$ 的质因数全部扫出来，用 $z1$ 记录所有小于 $\sqrt[3] s_i$ 质数乘积， $z2$ 记录能与 $z1$ 形成完全立方数的最小数。这样每个数会剩下一个数 x。

我们对 $x$ 进行讨论：

1. 如果 $x = 1$ ，那么能选的数就是同为 $x=1$ 数中 $z1$ 数量与 $z2$ 数量的较大值。

2. 如果 $x$ 是一个小于 $\sqrt s_i$ 的质数。我们只要能选的数就是 $x=x$ 时 $z1$ 的数量 与 $x=x^2$ 时 $z2$ 的数量较大值。

3. 如果 $x$ 是一个小于 $\sqrt s_i$ 的质数的平方。与第二类类似。
4. 如果 $x$ 是其他数，那这个数肯定能选，因为他的平方肯定大于 ${10}^{10}$。

最后统计答案即可。

时间复杂度 $n \sqrt[3] s_i$ 。

------------


代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
const int maxn=2e5+5,M=1e10,t=1e5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn],q,p[maxn],vis[maxn],cnt,g,b[maxn],c[maxn],h[maxn],num,ans,f[maxn],o;
map<int,int>s[maxn][2];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),q=2154;//3次根号下1e10
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=t;i++)
	{
		if(!vis[i])vis[i]=1,p[++cnt]=i,h[i]=1;
		if(i<=q)g=cnt;
		for(int j=1;j<=cnt&&p[j]*i<=t;j++)vis[p[j]*i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=g;j++)
		{
			if(a[i]<p[j]*p[j]*p[j])break;
			if(a[i]%(p[j]*p[j]*p[j])==0)a[i]=a[i]/p[j]/p[j]/p[j],j--;
		}int z=1,z2=1;
		if(a[i]==1){ans=1;continue;}
		for(int j=1;j<=g;j++)
			if(a[i]%p[j]==0)
			{
				a[i]=a[i]/p[j];z=z*p[j];
				if(a[i]%p[j]==0)a[i]=a[i]/p[j],z=z*p[j],z2=z2*p[j];
				else z2=z2*p[j]*p[j];
			}
		b[i]=z,c[i]=z2;o=sqrt(a[i]);
		if(a[i]==1)
		{
			s[0][0][z]++;
			if(s[0][0][z]==1&&s[0][0][z2]==0)f[i]=1;
		}
		else if(a[i]<=t&&h[a[i]]==1)
		{
			s[a[i]][0][z]++;
			if(s[a[i]][0][z]==1&&s[a[i]][1][z2]==0)f[i]=1;
		}
		else if(o*o==a[i])
		{
			s[o][1][z]++;
			if(s[o][1][z]==1&&s[o][0][z2]==0)f[i]=1;
		}
		else num++;
	}
	ans=ans+num;num=0;
	for(int i=1;i<=n;i++)
		if(f[i]==1)
		{
			if(a[i]==1)ans=ans+max(s[0][0][b[i]],s[0][0][c[i]]);
			else if(a[i]<=t&&h[a[i]]==1)ans=ans+max(s[a[i]][0][b[i]],s[a[i]][1][c[i]]);
			else o=sqrt(a[i]),ans=ans+max(s[o][1][b[i]],s[o][0][c[i]]);
		}
	cout<<ans;
 	return 0;
}

```



---

## 作者：C　C　A (赞：6)

$$\Large\rm [AGC003D]Anticube$$

$\large\rm Part1$

$\quad$首先我们可以发现，如果将每个数质因数分解，那么两个数不能同时选，当且仅当它们所有质因数的指数之和都为 $3$ 的倍数。于是如果知道一个确定的 $x$，我们就可以计算出唯一的 $y$，满足 $xy=z^3,z\in Z^+.$

$\quad$于是对于每个 $x$ 求出其对应的 $y$，取数量多的那个即可。需要注意的是，本来就是完全立方数的数只能取一个。

$\quad$于是我们就得到了一个 $\Theta[n(\sqrt{w}+\log n)]$ 的做法。复杂度瓶颈在分解质因数，如果使用 $\rm Pollard-Rho$ 算法分解质因数则可以做到 $\Theta(nw^{\frac{1}{4}}+n\log n)$，~~可以通过此题。~~

$\large\rm Part2$

$\quad$考虑首先剔除所有数中的立方因子。我们发现完全立方因子形如 $k^3$，有 $k\leqslant \sqrt[3]{w}$，于是我们只需要枚举 $[1,\sqrt[3]{w}]$ 中的质数即可。

$\quad$如果剔除立方因子后剩下了 $1$，那么说明这个数本身就是一个完全立方数，将这些数去掉，答案的初值设为 $1.$

$\quad$考虑记 $a$ 在去除立方因子后小于 $\sqrt[3]{w}$ 的因子的乘积为 $x$，记 $a$ 在去除所有 $[1,\sqrt[3]{w}]$ 中因子后的数为 $s.$ 我们发现 $s$ 最多有两个质因子，于是考虑进行分类讨论 ：

- 若 $s=1$，则说明这个数只有 $[1,\sqrt[3]{w}]$ 中的质因子，于是将 $x$ 放进集合 $S$ 中并暴力分解质因数。
- 若 $s=p,p\in [\sqrt[3]{w},\sqrt{w}]\cup Prime$，则将 $px$ 放进 $S$ 中并暴力分解质因数。
- 若 $s=p^2,p\in [\sqrt[3]{w},\sqrt{w}]\cup Prime$，则将 $p^2x$ 放进 $S$ 中并暴力分解质因数。
- 剩下的情况仅有两种，即 $s=p',p'\in [\sqrt{w},w]\cup Prime$ 和 $s=pq,p,q\in [\sqrt[3]{w},\sqrt{w}]\cup Prime$，显然这两种情况的对应数都大于 $w$，故可以直接加入答案。

$\quad$对于 $S$ 中的数，我们已经将其质因数分解，于是可以使用 `pbds` 中的 `hash_table` 存储，遍历所有 $S$ 中的元素，如果它的数量大与其对应数的数量，则将其数量加入答案。

$\quad$时间复杂度 $\Theta(n\frac{\sqrt[3]{w}}{\log w}+n\log n).$

$\large\rm Code$

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define int long long
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define dep(i, r, l) for (int i = r; i >= l; i--)

const int N = 1e5 + 10, sqr3 = 2200;

int n, a[N], x[N][20], cnt[N], num[N][20], ans;
int notp[sqr3], pri[sqr3], tot, S[N], siz;
gp_hash_table <int, int> Map;

int SupSet (int i) {
	int A = a[S[i]], T = 1;
	if ((int)sqrt(A) * (int)sqrt(A) == A) T *= sqrt(A);
	else T *= A * A;
	rep(j, 1, cnt[S[i]])
		if (num[S[i]][j] == 2) T *= x[S[i]][j];
		else T *= x[S[i]][j] * x[S[i]][j];
	return T;
}
// 寻找补集

signed main () {

	// freopen("sample.in", "r", stdin);

	scanf("%lld", &n);
	rep(i, 1, n) scanf("%lld", &a[i]);
	
	notp[1] = true;
	rep(i, 2, sqr3 - 1) {
		if (!notp[i]) pri[++tot] = i;
		for (int j = 1; i * pri[j] < sqr3 && j <= tot; j++) {
			notp[i * pri[j]] = true;
			if (i % pri[j] == 0) break;
		}
	}
	// 筛 sqrt{w} 以内的质数
	
	rep(i, 1, n) {
		x[i][0] = 1;
		for (int j = 1; j <= tot; j++) if (a[i] % pri[j] == 0) {
			x[i][++cnt[i]] = pri[j];
			while (a[i] % pri[j] == 0) a[i] /= pri[j], num[i][cnt[i]]++;
			num[i][cnt[i]] %= 3;
			if (!num[i][cnt[i]]) cnt[i]--;
			else x[i][0] *= pow(pri[j], num[i][cnt[i]]);
		}
		if (!cnt[i] && a[i] == 1) ans = 1;
	}
	// 剔除立方因子，求出每个 sqrt[3]{w} 以内的因子的数量
	
	/*
	rep(i, 1, n) {
		printf("now here is %lld :\n", i);
		printf("a[i] = %lld\n", a[i]);
		rep(j, 0, cnt[i]) printf("%lld %lld\n", x[i][j], num[i][j]);
		puts("");
	}
	*/

	rep(i, 1, n) {
		if (!cnt[i] && a[i] == 1) continue;
		if ((int)sqrt(a[i]) * (int)sqrt(a[i]) == a[i])
			S[++siz] = i, Map[a[i] * x[i][0]]++;
		else if (a[i] > N) ans++;
		else S[++siz] = i, Map[a[i] * x[i][0]]++;
	}
	// 分类讨论
	
	/*
	puts("There are some number in the S :");
	rep(i, 1, siz) printf("%lld ", S[i]);
	puts("\n");
	*/
	
	rep(i, 1, siz) {
		int T = SupSet(i);
		// printf("The subset of %lldth number is %lld\n", i, T);
		if (Map.find(T) == Map.end())
			ans += Map[a[S[i]] * x[S[i]][0]], Map[a[S[i]] * x[S[i]][0]] = 0;
		else {
			ans += max(Map[a[S[i]] * x[S[i]][0]], Map[T]);
			Map[a[S[i]] * x[S[i]][0]] = Map[T] = 0;
		}
	}
	// 寻找补集并计算答案
	
	printf("%lld\n", ans);

	return 0;
}
```


---

## 作者：Arghariza (赞：4)

神仙题。

由于时间限制 $5\text s$，我们可以整点怪的，比如根号分解质因子。

但是直接分解是 $O(n\sqrt w)$ 的，值域为 $w$ 即 $10^{10}$，肯定会炸。

毛估估一下，如果需要分解质因数，大概只能分解到 $O(\sqrt[3]{w})$ 的质数。

我们把小于 $\sqrt[3] w$ 的质数记为 $p_1,p_2,...,p_m$，显然 $s_i$ 能够表示为 $\prod p_k^{q_k}\times t$ 的形式。那么 $t$ **不可能**有次数大于等于 $3
$ 的质因子。

由于要取出尽量多的数，考虑建立映射，记录形如 $a_i=\prod p_k^{q_k\ \text{mod}\ 3}\times t$  的数的个数。和 $a_i$ 能组成立方数的 $b_i$ 就一定形如 $b_i=\prod p_k^{-q_k\ \text{mod}\ 3}\times t'$，其中 $t\times t'$ 为完全立方数。

假如我们知道 $t'$ 的值，将所有 $a_i$ 扔进 map 里，向对应的 $b_i$ 连双向边，两边点权均为出现次数，答案就是带权最大独立集。

我们发现每个 $a_i$ 与 $b_i$ 是**一一对应**的，这个图其实是个二分图，每个连通块里面只有一条边，贪心取两边权值较大的即可。现在的问题变成了根据 $t$ 如何求 $t'$。

由于 $t$ 的质因子**全部大于** $\sqrt[3] w$，那么显然 $t$ **至多包含** $2$ 个质因子，那么 $t$ 就只有三种表示：$t=p/pq/p^2$，$p,q$ 均为质数。

我们将根号的精神 **贯 彻 到 底**，考虑根号分治：

1. $t\le \sqrt w(t\neq 1)$：

显然 $t$ 只能表示成 $p$ 的形式，所以 $t'=p^2$。

1. $t>\sqrt w$：

- 若 $t=pq$，则 $t'=p^2q^2$，超过了 $w$，不用管。
- 若 $t=p$，则 $t'=p^2$，也超过了 $w$，也不用管。
- 若 $t=p^2$，则 $t'=p$，符合条件。

于是对于这种情况，判断 $t$ 是否是平方数即可。

然后就做完了，$1$ 的情况要讨论一下。

[评测记录。](https://atcoder.jp/contests/agc003/submissions/38875546)

---

## 作者：hank0402 (赞：3)

首先，可以把对答案没有影响的立方因子全部筛掉。

剩下的数可以被表示成 $a^2\times b$ 的形式。这里，$b$ 不含平方因子。

显然的，这里的 $\min\{a,b\}\leq a_i^{\frac{1}{3}}$。其中，记 $a_i$ 为 $s_i$ 筛掉立方因子后的结果。

在代码中，我们可以枚举 $j=1\sim a_i^{\frac{1}{3}}$ ，对于 $j$ 作为 $a$ 或 $b$ 分开讨论，其中，若 $a_i\not = 1$，最后只要满足求出的 $a$ 最大，就可以保证 $b$ 中不含平方因子，因为若 $b$ 中含平方因子，都可以有一种方案，使得 $a$ 比原来的更大。

对于每一个 $a_i$ 所代表的数对 $(a,b)$，只有数对 $(b,a)$ 会与之冲突。

所以我们可以用 map 统计每个数对出现的次数，最后答案累加上 $\max\{cnt_{(a,b)},cnt_{(b,a)}\}$ 即可。

记得 $a=b=1$ 的情况要分开讨论。

[Code](https://atcoder.jp/contests/agc003/submissions/37924814)

---

## 作者：Jerrycyx (赞：2)

前置知识：埃氏筛法（或线性筛法）、质因数分解。

再次感谢 @[Tenshi](https://www.luogu.com.cn/article/exj3xpf2) 的[题解](https://www.luogu.com.cn/article/exj3xpf2)，提供了重要思路。

本题解在更加详细的同时，增加了一些结论证明，简化了找质因数的过程，不需要再使用 Pollard-Rho 这种高级算法。通过这种方法，这道题的难度可以降低到蓝或更低。

-----

题目要求“任意两个数的积都不是完全立方数”，即数与数之间存在互斥关系。又要求“选出最多的数”，很容易想到**最大独立集**。考虑如何快速判断两个数是否互斥：

将一个数质因数分解后，是否是立方数只与其是否所有质因子的指数都是 $3$ 的倍数有关，所以可以**将所有的指数都模 $3$**，不影响结果。

如此操作以后，一个数可以在所有质因子指数都模 $3$ 以后简化，使所有质因子的指数都属于 $\{0,1,2\}$，而两个数是否互斥（乘积是否为立方数）也很好判断了。将 $x$ 的简化形式 $x'$ 质因数分解为 $\prod p_i^{c_i}$，某个数 $y$ 与 $x$ 的乘积为立方数当且仅当其简化形式 $y'=\prod p_i^{(3-c_i) \bmod 3}$（注意需要再次取模）。

这样，**某个数的简化形式的互斥对象就有了唯一确定的简化形式，并且这是一一对应的**，$x'$ 与 $y'$ 互斥时，$y'$ 也与 $x'$ 互斥，例如 $2$ 和 $4$。

-----

根据这个计算方式建图，以所有的简化形式为结点，所有的互斥关系为边，所求即为这张图上的最大独立集。

这样建图出来以后可以发现，所有的完全立方数简化形式都为 $1$，互斥对象也都为 $1$。即：**所有的完全立方数都两两互斥，只能选一个，且完全立方数不与其它任何点连边，是孤立的**。

此外，**非完全立方数的互斥对象都一定不是自己**，证明：对非完全立方数进行简化，其至少有一个质因子的指数不为 $0$（否则就是完全立方数了），只可能是 $1$ 或 $2$，对应的互斥指数分别为 $2$ 和 $1$，都不可能与自己相同。所以非完全立方数的互斥对象至少有一个质因子的指数与自己不同。根据唯一分解定理，这两个数也一定不同。

综上所述，除去完全立方数是可能有自环的孤点，其它**非完全立方数点总是两两一对连边，且不会形成自环**，在这样的图上找最大独立集就简单多了，两侧的点只能选一边，当然是选大的那一侧了。

具体来说，设简化形式 $x'$ 出现了 $p$ 次，其互斥对象 $y'$ 出现了 $q$ 次，那么这一对点的最大独立集就是 $\max\{p,q\}$。

-----

接下来考虑如何求取某个数的简化形式和其互斥对象的简化形式：

简化某个数需要将其质因数分解，暴力当然是不行的，我们需要一些优化。

+ 首先利用埃筛/线筛找出 $\sqrt{10^{10}}=10^5$ 内的所有质数，数量级为 $\frac{10^5}{\ln 10^5} \approx 10^4$ 个。

+ 然后对于每一个**非完全立方数** $a_i$，遍历质数集合将其质因数分解，记录每一个质因子的出现次数 $c$，将 $p^{c \bmod 3}$ 计入简化形式，$p^{(3- c \bmod 3) \bmod 3}$ 计入互斥对象简化形式。

+ 分解完毕后即获得这个数和其互斥对象的简化形式，分解时还可判断 $p_i^2 \le x$ 来加速。

+ 记录互斥关系，累加该简化形式的出现次数。

+ 统计答案，对于每一对互斥关系，取两边较大的出现次数（注意互斥关系需要判重）；如果输入有完全立方数则需额外加一。

记 $V = \sqrt{\max s}$，极限时间复杂度为 $O(V \log\log V + \frac{V}{\ln V} N)$（埃筛）或 $O(V + \frac{V}{\ln V} N)$（线筛），随机数据下对单个数分解质因数平均循环次数不到 $1000$，可过此题。

-----

AC 记录：[洛谷](https://www.luogu.com.cn/record/191851902)，[AtCoder](https://atcoder.jp/contests/agc003/submissions/60276790)。

代码：

```cpp
#include<cstdio>
#include<bitset>
#include<vector>
#include<unordered_map>
#define LL long long
using namespace std;

const int N=1e5+5,SA=1e5;
int n;
LL a[N];

bitset<SA+5> is_prime;
int prime[N],prime_idx;
void Erato()
{
	for(int i=2;i<=SA;i++)
		is_prime[i]=true;
	for(int i=2;i<=SA;i++)
		if(is_prime[i])
		{
			prime[++prime_idx]=i;
			for(LL j=1ll*i*i;j<=SA;j+=i)
				is_prime[j]=false;
		}
	return;
}

unordered_map<LL,int> ump;
unordered_map<LL,LL> rev;
void connect(int id)
{
	LL x=a[id];
	auto spow = [&](LL x,int y) -> LL //计算x的y次方（y≤3）
	{
		switch(y)
		{
			case 0: return 1;
			case 1: return x;
			case 2: return x*x;
			case 3: return 1;
			default: return -1;
		}
	};
	LL simp=1,cur=1;
	for(int i=1;i<=prime_idx&&prime[i]*prime[i]<=x;i++)
		if(x%prime[i]==0)
		{
			int cnt=0;
			while(x%prime[i]==0)
			{
				x/=prime[i];
				cnt++;
			}
			cnt%=3;
			simp*=spow(prime[i],cnt);
			cur*=spow(prime[i],3-cnt);
		}
	if(x>1)
	{
		simp*=spow(x,1);
		cur*=spow(x,2);
	}
	ump[simp]++;
	rev[simp]=cur;
	rev[cur]=simp;
	ump[cur];
	return;
}

unordered_map<LL,bool> is_cub;
unordered_map<LL,bool> vst;
int main()
{
	Erato();
	for(int i=1;i<=2200;i++)
		is_cub[1ll*i*i*i]=true;
	scanf("%d",&n);
	bool have_cube=false;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		if(is_cub[a[i]]) have_cube=true;
		else connect(i);
	}
	int ans=0;
	for(pair<LL,int> p: ump)
	{
		if(vst[p.first]) continue;
		ans+=max(p.second,ump[rev[p.first]]);
		vst[rev[p.first]]=true;
	}
	printf("%d\n",ans+have_cube);
	return 0;
}
```

---

## 作者：翼德天尊 (赞：2)

一道数论相关的分讨好题。

首先立方数具有的一个性质是，每一种质因子的个数一定是三的倍数。

关于质因子有一个很广泛的性质是，对于一个数 $x$，最多只有一个大于 $\sqrt{x}$ 的质因子。

所以设题中 $s$ 的上界为 $S$，我们很容易想到分解每一个 $s_i$ 然后比较，如果 $s_i$ 存在一个大于 $\sqrt{S}$ 的质因子，那么这个数显然不可能和其他数乘积凑成立方数——因为其他数最多也只有一个相同的质因子，不可能凑成三个；然后随便怎么搞一下。

但是这样单分解质因子的时间复杂度就是 $O(n\sqrt{S})$ 了，显然是不对的。

可以考虑进一步扩展这个性质吗？对于一个数 $x$，最多只有两个大于 $\sqrt[3]{x}$ 的质因子。

如果我们能利用这个性质让时间复杂度基于 $O(n\sqrt[3]{S})$，显然就可以了。

怎么利用这个性质呢？首先考虑简化问题，先枚举 $[1,\sqrt[3]{S}]$，将每一个 $s_i$ 的立方根因子干掉，保证每一种质因数的个数都在两个以内，并找到每一个 $s_i$ 每一个立方根因子剩下的具体个数。

然后我们开始进行分类讨论。

- 对于一个数 $x$，如果它拥有一个大于 $\sqrt{n}$ 的质因子，显然不会和其他任何数冲突。
- 除此之外，它还可能拥有一个或者两个大小在 $\sqrt[3]{n}$ 和 $\sqrt{n}$ 之间的质因子，那么显然，只有在这个范围内质因子大小相同，且个数分别为 $1$ 个和 $2$ 个的数才可能会冲突。所以假设 $x$ 含有的两个在这个范围内的质因子大小不同，显然无法和其它数凑对；如果只有一个或者有两个大小相同的质因子，才可能可以凑对。
- 对于不存在 $\sqrt[3]{n}$ 以上质因子的 $s_i$，只会互相冲突。

于是我们就将他们分了个类，并且注意到，如果将每一个质因子的个数都取模 $3$ 以后，产生冲突的数应该是两两对应的，即对于一个数 $x$，如果我们将它的每一个质因子的个数都对于 $3$ 取个差，就是会和它产生冲突的数。

那么计算贡献的方案就明了起来了。

- 第一种数我们可以直接计入贡献；

- 第三种则可以开一个 map，对于当前的 $s_i$（已经将质因子个数取模过的），考虑找到会和其产生冲突的数 $x$，将 $s_i$ 所在项加 $1$ 后和 $x$ 所在项取最大值即为这一对值对于答案的贡献；

- 第二种则类似，含有两个不同大质因子时可以直接计入贡献；否则对于每一个大质因子分别开一个 map，或者用两个关键词查询 map 即可。

时间复杂度 $O(n\sqrt[3]{n}+n\log n)$.

注意对于本来就是立方数的数，只能存在一个，需要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=1e5;
const int SQ2=1e5;
const int SQ3=2154;
int n,s[N+5],zhi[N+5],ztot2,ztot3,maxn,g[400],ans;
bool izhi[N+5];
map<int,int> m0;
map<pair<int,int>,int> m1,m2;
int read(){
	int w=0,f=1;
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
void init(){
	for (int i=2;i<=SQ2;i++){
		if (!izhi[i]) zhi[++ztot2]=i;
		if (i==SQ3) ztot3=ztot2;
		for (int j=1;j<=ztot2&&i*zhi[j]<=SQ2;j++){
			izhi[i*zhi[j]]=1;
			if (i%zhi[j]==0) break;
		}
	}
}
void solve(int x){
	memset(g,0,sizeof(g));
	int sum1=1,sum2=1;
	for (int i=1;i<=ztot3;i++){
	//	while (x%(zhi[i]*zhi[i]*zhi[i])==0) x/=(zhi[i]*zhi[i]*zhi[i]);
		while (x%zhi[i]==0) x/=zhi[i],g[i]++;
		g[i]%=3;
		if (g[i]==1) sum1*=zhi[i],sum2*=zhi[i]*zhi[i];
		else if (g[i]==2) sum1*=zhi[i]*zhi[i],sum2*=zhi[i];
	}
	int p=sqrt(x);
	if (x>SQ3&&x<=SQ2&&izhi[x]==0){
		int zc1=++m1[make_pair(x,sum1)];
		int zc2=m2[make_pair(x,sum2)];
		if (zc1>zc2) ++ans;
	}else if (x>SQ2&&p*p==x&&izhi[p]==0){
		int zc1=++m2[make_pair(p,sum1)];
		int zc2=m1[make_pair(p,sum2)];
		if (zc1>zc2) ++ans;
	}else if (x==1){
		if (sum1==1&&sum2==1){
			if (m0[sum2]==0) ++ans;
			m0[sum2]=1;
			return;
		}
		int zc1=++m0[sum1];
		int zc2=m0[sum2];
		if (zc1>zc2) ++ans;
	}else ++ans;
}
signed main(){
	init();
	n=read(); 
	for (int i=1;i<=n;i++) s[i]=read();
	for (int i=1;i<=n;i++){
		solve(s[i]);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Tenshi (赞：2)

## 分析

提供一个从建图入手的做法，个人感觉这个做法比较接近本质，而且过程十分简洁。

考虑对每个数进行质因数分解，并对所有质因子的次数 $\% 3$。

下面开始建图：将 $n$ 个数看作 $n$ 个点，考虑对于两个数，如果积为立方数，那么就连边，记这个图为 $G$。发现这题本质上就是求 $G$ 的**最大独立集**。（也就是选出最大的点集使任意两点间没有连边）

然后对图 $G$ 进行拆分：

1. 对于所有立方数，可以发现他们之间构成了一个完全图，因此最多只能选一个点。

2. 而对于其它数而言，他们之间构成一个二分图，而且这个二分图比较特殊：设我们有 $x$ 个点质因数分解并 $\%3$ 结果都是 $C = \prod p_i ^ {c_i}$，那么这 $x$ 个点能且仅能和分解结果为 $C' = \prod p_i ^ {(3-c_i)\% 3}$ 的点（设有 $y$ 个）连边（也就是 $x \times y$ 条边）。因为二分图**最大独立集大小**等于点的总数减去最大匹配数目。对于这个二分图而言，最大匹配显然是 $\min(x, y)$，故这样的二分图的最大独立集大小就是 $x+y-\min(x, y) = \max(x, y)$。

> 为什么非立方数之间一定构成二分图呢？
假设非立方数之间存在奇环，那么我们从环上找到一点 $u$，不妨设它有一个质因子 $p$ 次数为 $1$，那么沿环从 $u$ 出发经过的每个点次数一定是 $1,2,1...$，可以发现奇环会导致与 $u$ 连接的点次数也为 $1$，那么不能构成立方数，矛盾。

## 实现
质因数分解（采用 $\texttt{pollard-rho}$），然后将每个数的分解结果分组，对于每一组都像上述过程一样找到 $\max(x, y)$ 并加入答案 $res$ 中即可，当然如果存在立方数那么答案 $+1$。

```cpp
// Problem: D - Anticube
// Contest: AtCoder - AtCoder Grand Contest 003
// URL: https://atcoder.jp/contests/agc003/tasks/agc003_d
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()

#define x first
#define y second
#define int long long
using pii = pair<int, int>;
using ll = long long;

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=2e5+5, s=20;

mt19937_64 rd(time(NULL));
int fac[N], cnt;

inline int mul(int a, int b, int mod){
	return (__int128)a*b%mod;
}

inline int fpow(int x, int p, int mod){
	int res=1;
	for(; p; p>>=1, x=mul(x, x, mod)) if(p&1) res=mul(res, x, mod);
	return res;
}

inline bool rabin(int n, int a){
	int d=n-1, ct=0; 
	while(~d&1) d>>=1, ct++;
	int x=fpow(a, d, n);
	if(x==1) return true;
	rep(i,1,ct){
		if(x==n-1 || x==1) return true;
		x=mul(x, x, n); 
	}
	return false;
}


inline bool isp(int n){
	if(n<2) return false;
	static const int pri[] = {2, 3, 5, 7, 11, 13, 31, 61, 24251};
	for(auto x: pri) {
		if(n==x) return true;
		if(!rabin(n, x)) return false;
	}
	return true;
}

inline int f(int x, int c, int mod){
	return (mul(x, x, mod)+c)%mod;
}

inline int pollard_rho(int n){
	int c=rd()%(n-1)+1; int v1=0;
	for(int s=1, t=2; ; s<<=1, t<<=1){
		int pro=1, v2=v1, cnt=0;
		rep(i,s+1,t){
			v2=f(v2, c, n), pro=mul(pro, abs(v1-v2), n), cnt++;
			if(cnt%127==0){
				cnt=0; int d=__gcd(pro, n);
				if(d>1) return d;
			}
		}
		int d=__gcd(pro, n);
		if(d>1) return d;
		v1=v2;
	}
}

inline void find(int n){
	if(isp(n)) return fac[++cnt]=n, void();
	int p;
	while((p=pollard_rho(n))==n) ;
	find(p), find(n/p);
}

map<int, int> get(map<int, int> mp){
	for(auto &[x, y]: mp) y=3-y;
	return mp;
}

signed main(){
	int n; read(n);
	
	map<map<int, int>, int> c;
	int res=0;
	rep(i,1,n){
		cnt=0;
		int x; read(x);
		map<int, int> mp;
		if(x==1){
			res=1;
			continue;
		}
		find(x);
		rep(j,1,cnt){
			int f=fac[j];
			int p=0;
			while(x%f==0) p++, x/=f;
			if(p%3) mp[f]=p%3;
		}	
		
		if(!mp.size()){
			res=1;
			continue;
		}
		c[mp]++;
	}

	set<map<int, int>> st;
	for(auto [x, y]: c) if(!st.count(x)){
		auto e=get(x);
		res+=max(c[e], y);
		st.insert(e);
	}
	cout<<res<<endl;
	
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：2)

首先对于每一个质因数的指数我们都可以 $\%3$ ，因为成为完全立方数只要每个指数都是三的倍数。然后对于每一种处理完后数，我们都记录下它的个数，而不能与它同时选的数只有每一项与其指数和均为 $3$ 的数，我们只要对于每一组不能同时选的数都只选择两项中个数较多的一类即可，而对于 $1$ 显然能且只能选一个。

```
#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
using namespace std;
const int N = 1e5 + 10;
int n;
long long s[N];
int num;
int sf[N];
long long pri[N];
long long a[N], b[N];
map<long long, long long>ma;
int main()
{
	scanf("%d", &n);
	sf[0] = sf[1] = 1;
	for (int i = 2; i < 5010; ++ i)
	{
		if(sf[i] == 0)
		{
			pri[++ num] = i;
			for (int j = 2 * i; j < 5010; j += i)
			{
				sf[j] = 1;
			}
		}
	}
	for (int i = 1; i <= n; ++ i)
	{
		long long o;
		scanf("%lld", &o);
		long long now = 1, dy = 1;
		for (int i = 1; i <= num; ++ i)
		{
			int tot = 0;
			while(o % pri[i] == 0)
			{
				o /= pri[i];
				++ tot;
			}
			tot %= 3;
			if(tot)
			{
				for (int j = 1; j <= tot; ++ j)
				now *= pri[i];
				for (int j = tot + 1; j <= 3; ++ j)
				dy *= pri[i];
			}
		}
		now *= o;
		if((long long)sqrt(o) * (long long)sqrt(o) != o)
		dy *= o * o;
		else
		dy *= sqrt(o);
		++ ma[now];
		a[i] = now;
		b[i] = dy;
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++ i)
	{
		if(a[i] == 1)continue;
		ans += max(ma[a[i]], ma[b[i]]);
		ma[a[i]] = ma[b[i]] = 0;
	}
	ans += ma[1] > 0;
	printf("%lld", ans);
}
```


---

## 作者：Ebola (赞：2)


以前做过一个假的Pollard-Rho练习题，好像是POI2010的什么非凡因子啥的题，那题用Pollard-Rho光荣T了，当时学习了一下题解，发现了一种奇妙分解法。好像这题刚好能用

考虑对于一个数a，我们将它的质因数分解出来，然后所有质因子的幂次对3取模，再乘回来得到一个新的数x。我们发现，若规定质因子幂次小于等于3，那么选了x后不能选的数就只有唯一的一个

若a按上述算法得到x，b按上述算法得到y，选了x后不能选y，那不难发现选了a后不能选b。该结论对任意能通过上述算法算出x、y的a、b均成立

于是我们可以对于所有的x，统计出按上述算法能算出它的a有多少个，记作“x的数量”，用map存储即可。然后对于每个a，按上述算法算出x，再算出选了x之后不能选的数y，我们在x和y中选一个数量更多的，再打上已选标记就行了。因为x和y是一一对应的，所以这个贪心策略的正确性是显然的

现在问题是如何对于一个数x，算出它对应的x

考虑朴素的质因数分解，那非常容易实现，只要事先把1e5内的质数筛出来就行了。可是那样复杂度显然是不可接受的，于是考虑之前做过的那题类似的方法

我们只筛出三次根级别的质数，然后对这些质数跑一遍分解。分解a之后有四种情况：

1. a变成了1。此时已经分解干净了，直接算x即可
2. a是一个大于二次根级别的质数。显然x直接等于a，不能选的就是a平方
3. a是两个介于三次根与二次根级别之间的不同质数之积。处理方式同情况2
4. a是一个介于三次根与二次根级别之间的质数平方。显然x还是a，但是选了x之后不能选的数是sqrt(x)

对于情况2和情况3，我们没必要去区分它，只要它不等于1，又不是完全平方数，那就按那样的方式去处理就行了

此外，在所有立方数中，至多只能选一个，因此贪心选取时要把x=1的情况特判掉

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline LL read()
{
    LL x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=100010;
LL a[N],b[N][2];
bool mask[3010];
int prm[3010],tot=0,n;
unordered_map<LL,int> cc;
unordered_map<LL,bool> fucked;

LL maxc(const LL &a,const LL &b){return cc[a]>cc[b]?a:b;}

void preprework()
{
    for(int i=2;i<=2200;i++)
    {
        if(mask[i]) continue;
        prm[++tot]=i;
        for(int j=i;j<=2200;j+=i)
            mask[j]=1;
    }
}

void prework()
{
    for(int i=1;i<=n;i++)
    {
        LL x=1,y=1;
        for(int j=1;j<=tot;j++)
        {
            if(a[i]%prm[j]) continue;
            int cnt=0;
            while(a[i]%prm[j]==0)
                a[i]/=prm[j],cnt++;
            if(!(cnt%=3)) continue;
            for(int k=1;k<=cnt;k++) x=x*prm[j];
            for(int k=cnt+1;k<=3;k++) y=y*prm[j];
        }
        LL t=(LL)sqrt(a[i]);
        if(t*t==a[i]) x=x*t*t,y=y*t;
        else x=x*a[i],y=y*a[i]*a[i];
        b[i][0]=x;b[i][1]=y;
        if(!cc.count(x)) cc[x]=1;
        else cc[x]++;
    }
}

int main()
{
    LL ans=0;n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    preprework();prework();
    for(int i=1;i<=n;i++)
    {
        LL c1=b[i][0],c2=b[i][1];
        if(fucked[c1]||fucked[c2]) continue;
        LL x=maxc(c1,c2);fucked[x]=1;
        ans+=(x==1)?1:cc[x];
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：_l_l_ (赞：1)

[AGC003D - AtCoder](https://atcoder.jp/contests/agc003/tasks/agc003_d)

[AGC003D - Luogu](https://www.luogu.com.cn/problem/AT2004)

> 给你 $n$ 个数 $s_i$，选择最多的数，使得任意两个数的积都不是完全立方数。
$1\leq n\leq10^5,1\leq s_i\leq10^{10}$。
> 

首先将每个 $s_i$ 拆成 $s'_ix_i^3$ 的形式，我们发现 $s'_is'_j$ 是否为完全立方数与 $s_is_j$ 是否为完全立方数是等价的，所以直接拿 $s'$ 替换 $s$，仅需枚举 $\sqrt[3]{\max s}$ 以内的质数即可。同时每个数有且仅有一个对应的数使得它两乘积为完全立方数。

一开始先特判 $s=1$ 的情况，此时只能拿一个。

令 $z_i$ 为 $s_i$ 中大于 $\sqrt[3]{\max s}$ 的质因数的乘积。

分类讨论一下：

1. $z_i=1$：记录一下 $s_i$。
2. $z_i=p,p\in(\sqrt[3]{\max s},\sqrt{\max s}]$：记录一下 $s_i$。
3. $z_i=p^2,p\in(\sqrt[3]{\max s},\sqrt{\max s}]$：记录一下 $s_i$，只需要利用 sqrt 就能判断。
4. $z_i=pq,p,q\in(\sqrt[3]{\max s},\sqrt{\max s}]$：无法构成完全立方数，直接加入答案。
5. $z_i=p,p\in(\sqrt{\max s},\infty]$：直接加入答案。

然后将上面被记录的数塞进一个 map 里面，重新判断一下，如果有对 $s_i$ 冲突则选择个数较多的那方。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#include <stack>
using namespace std;
int primes[10005], ptot; bool tags[100005];
void prime(int n) {
	for (int i = 2; i <= n; i++) {
		if (tags[i] == 0) primes[++ptot] = i;
		for (int j = 1; j <= ptot && i * primes[j] <= n; j++) {
			tags[i * primes[j]] = 1; if (i % primes[j] == 0) break;
		}
	} 
}
long long s[100005], z[100005]; int y[100005][330]; bool is1[100005];
stack<long long> clist; map<long long, int> mp;
int main() {
	int n; scanf("%d", &n); long long maxs = 0;
	for (int i = 1; i <= n; i++) scanf("%lld", &s[i]), maxs = max(maxs, s[i]);
	int sqrt3s = (int)pow(maxs, 1. / 3), sqrts = (int)sqrt(maxs);
	prime(sqrts); int ans = 0;
	for (int i = 1; i <= n; i++) {
		y[i][0] = 1;
		for (int j = 1; j <= ptot && primes[j] <= sqrt3s; j++) {
			while (s[i] % primes[j] == 0) y[i][j]++, s[i] /= primes[j];
			y[i][j] %= 3;
			if (y[i][j]) y[i][0] *= primes[j];
			if (y[i][j] == 2) y[i][0] *= primes[j];
		}
		z[i] = s[i]; s[i] *= y[i][0]; is1[i] = s[i] == 1; if (is1[i]) ans = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (is1[i]) continue;
		if (z[i] == 1) clist.push(i), mp[s[i]]++;
		else if (z[i] <= sqrts && tags[z[i]] == 0) clist.push(i), mp[s[i]]++;
		else if ((long long)sqrt(z[i]) * (int)sqrt(z[i]) == z[i]) clist.push(i), mp[s[i]]++;
		else ans++;
	}
	while (clist.empty() == 0) {
		int u = clist.top();
		clist.pop();
		long long invnum = 1;
		if ((long long)sqrt(z[u]) * (int)sqrt(z[u]) == z[u]) invnum = sqrt(z[u]);
		else invnum = z[u] * z[u];
		for (int j = 1; j <= ptot && primes[j] <= sqrt3s; j++) {
			if (y[u][j]) invnum *= primes[j];
			if (y[u][j] == 1) invnum *= primes[j];
		}
		if (mp[invnum]) {
			ans += max(mp[s[u]], mp[invnum]);
			mp[s[u]] = 0; mp[invnum] = 0;
		}
		else {
			ans += mp[s[u]]; mp[s[u]] = 0;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：ETHANK (赞：1)

有一说一这题没到黑题难度吧，算是比较常规的数论题（

对于每个正整数 $x$ 我们考虑两种数，$Pair(x)$ 表示与 $x$ 相乘为立方数的最小正整数，而 $Norm(x)$ 表示 $x$ 去掉所有立方因子后的正整数。可以发现两个数如果拥有同样的 $Norm$ ，那么也会有同样的 $Pair$ ，也就是这两个数本质上是相同的。而如果一个数的 $Norm$ 是另一个数的 $Pair$ ，那么这两数显然不能同时选入答案。于是答案就是对于 $s[i]$ 中所有本质不同的 $x$ ，求 $s[i]$ 中本质为 $Norm(x)$ 或 $Pair(x)$ 的个数的最大值。

下面考虑如何求解 $Norm(x)$ ，其实只需要筛掉所有立方因子就可以了，也就是 $\le 10^\frac{10}{3}\approx 2160$ 的质数的立方。筛完之后把这些质数剩下的次幂也从 $x$ 中筛掉，并贡献给 $Pair(x)$ 。由于剩下的因子大于原来 $x^\frac{1}{3}$ ，推出最后剩下的 $x$ 只有几类：

- $x$ 为质数
- $x$ 为质数的平方
- $x$ 为不同质数的积

对于第一类和第三类，容易得出 $Pair(x)=x^2$ 。而对于第二类，$Pair(x)=\sqrt x$ 。最后把这个数加入 $Norm(x)$ 的桶里即可。

时间复杂度：$O(N\frac{(MAX s_i)^\frac13}{\log MAX s_i})+O(N\log N)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e5+10;
ll n,pri[N],tot;
ll a[N],b[N],ans;
bool vis[N];
map<ll,ll>mp;
int main(){
    n=read();
    rep(i,2,2160){
        if(!vis[i])pri[++tot]=i;
        for(int j=1;j<=tot&&pri[j]*i<=2160;j++){
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
    rep(i,1,n){
        scanf("%lld",&a[i]);
        ll norm=1,pair=1;
        rep(j,1,tot){
            ll cube=pri[j]*pri[j]*pri[j];
            while(a[i]%cube==0)a[i]/=cube;
        }
        ++mp[a[i]];norm=a[i];
        rep(j,1,tot){
            if(a[i]%pri[j]!=0)continue;
            if(a[i]%(pri[j]*pri[j]))pair*=pri[j]*pri[j];
            else pair*=pri[j];
            while(a[i]%pri[j]==0)a[i]/=pri[j];
        }
        ll sqr=(ll)sqrt(a[i]);
        if(sqr*sqr!=a[i])pair*=a[i]*a[i];
        else pair*=sqr;
        a[i]=norm;b[i]=pair;
    }
    rep(i,1,n){
        if(a[i]==1)continue;
        ans+=max(mp[a[i]],mp[b[i]]);
        mp[a[i]]=mp[b[i]]=0;
    }
    printf("%lld\n",ans+!!mp[1]);
    return 0;
}
```



---

## 作者：飞野同学 (赞：1)

给出一种复杂度更优的 $\text{Pollard-rho}$ 做法。

首先分解质因子，可以发现如果两数的所有质因子次数加起来模 $3$ 等于 $0$，则两数中只能选一个，那么就选数量多的那个，注意本身是完全立方数的数最多选一个。

时间复杂度 $\mathcal O(ns^{\frac{1}{4}}+n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ldb;

const int N = 100005;

ll qmul(ll a, ll b, ll mod) {
	return ((a * b - (ll)((ldb) a * b / mod + 0.5) * mod) % mod + mod) % mod;
}
ll qpow(ll a, ll b, ll mod) {
	ll t = 1;
	while(b) {
		if(b & 1) t = qmul(t, a, mod);
		a = qmul(a, a, mod); b >>= 1;
	}
	return t;
}
bool miller_rabin(ll n, int p) {
	ll d = n - 1; int r = 0;
	while((d & 1) == 0) {
		d >>= 1; ++r;
	}
	ll t = qpow(p, d, n);
	if(t == 1) return 1;
	for(int i = 0; i < r; ++i) {
		if(t == n - 1) return 1;
		t = qmul(t, t, n);
	}
	return 0;
}
bool is_prime(ll n) {
	const int prime[8] = {2, 3, 5, 7, 11, 13, 17, 37};
	if(n <= 1) return 0;
	for(int i = 0; i < 8; ++i) {
		if(n == prime[i]) return 1;
		if(n % prime[i] == 0) return 0;
		if(!miller_rabin(n, prime[i])) return 0;
	}
	return 1;
}
ll R(ll n) {
	static int _ = (srand(19260817), 1);
	ll n1 = rand(), n2 = rand(), n3 = rand(), n4 = rand();
	return (n1 | (n2 << 16) | (n3 << 32) | (n4 << 48)) % n;
}
ll F(ll x, ll c, ll mod) {
	return (qmul(x, x, mod) + c) % mod;
}
ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
ll pollard_rho(ll n) {
	ll c = R(n - 1) + 1, s = 0; int k = 1;
	while(1) {
		ll t = s, d = 1;
		for(int i = 1; i <= k; ++i) {
			t = F(t, c, n);
			d = qmul(d, abs(t - s), n);
			if(i % 127 == 0 && gcd(d, n) != 1) return gcd(d, n);
		}
		if(gcd(d, n) != 1) return gcd(d, n);
		s = t; k <<= 1;
	}
}
map<ll, int> s;
void decompose(ll n, int c) {
	if(n == 1 || c % 3 == 0) return;
	if(is_prime(n)) {
		s[n] += c; return;
	}
	ll t = n;
	while(t == n) t = pollard_rho(n);
	int k = 0;
	while(n % t == 0) {
		n /= t; ++k;
	}
	decompose(n, c);
	decompose(t, c * k);
}

pair<pair<ll, ll>, pair<ll, ll> > t[N];
int main() {
	int n;
	scanf("%d", &n);
	map<pair<ll, ll>, int> cnt;
	for(int i = 1; i <= n; ++i) {
		ll a;
		scanf("%lld", &a);
		s.clear();
		decompose(a, 1);
		map<ll, int>::iterator it = s.begin();
		ll sum1 = 0, pro1 = 1, sum2 = 0, pro2 = 1;
		while(it != s.end()) {
			if((*it).second % 3 == 1) {
				sum1 += (*it).first;
				pro1 *= (*it).first;
				sum2 += (*it).first * (*it).first;
				pro2 *= (*it).first * (*it).first;
			}
			else if((*it).second % 3 == 2) {
				sum1 += (*it).first * (*it).first;
				pro1 *= (*it).first * (*it).first;
				sum2 += (*it).first;
				pro2 *= (*it).first;
			}
			it++;
		}
		t[i] = make_pair(make_pair(sum1, pro1), make_pair(sum2, pro2));
		cnt[make_pair(sum1, pro1)]++;
	}
	int sum = 0;
	for(int i = 1; i <= n; ++i) {
		if(t[i].first == t[i].second && cnt[t[i].first] > 0) {
			sum++; cnt[t[i].first] = 0;
		}
		else if(cnt[t[i].first] > cnt[t[i].second]) {
			sum += cnt[t[i].first]; cnt[t[i].first] = 0; cnt[t[i].second] = 0;
		}
		else {
			sum += cnt[t[i].second]; cnt[t[i].first] = 0; cnt[t[i].second] = 0;
		}
	}
	printf("%d\n", sum);
	return 0;
}
```

---

