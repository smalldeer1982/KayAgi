# Deck-Building Game

## 题目描述

你和你的朋友正在玩一款构筑牌组的游戏。有 $N$ 张卡牌，编号从 $1$ 到 $N$。第 $i$ 张卡牌的数值为 $A_i$。

你需要为你和你的朋友各自构建一个牌组。一张卡牌不能同时出现在两个牌组中，也可以选择不使用所有 $N$ 张卡牌。允许某个牌组为空，即不包含任何卡牌。

一个牌组的“力量”定义为该牌组中所有卡牌数值的按位异或（XOR）结果。空牌组的力量为 $0$。

如果两个牌组的力量相等，则认为这局游戏是平衡的。

请你计算有多少种不同的方法可以构建两个牌组，使得游戏平衡。只要有一个牌组包含至少一张不同的卡牌，就认为两种方法不同。由于答案可能很大，请输出答案对 $998\,244\,353$ 取模的结果。

## 说明/提示

样例输入输出 1 说明

设 $S$ 和 $T$ 分别为你和你朋友的牌组。共有 $9$ 种方法可以使游戏平衡。

- $S = \{\}$，$T = \{\}$。两个牌组的力量均为 $0$。
- $S = \{2, 3, 4\}$，$T = \{\}$。两个牌组的力量均为 $0$。
- $S = \{\}$，$T = \{2, 3, 4\}$。两个牌组的力量均为 $0$。
- $S = \{2, 4\}$，$T = \{3\}$。两个牌组的力量均为 $4$。
- $S = \{3\}$，$T = \{2, 4\}$。两个牌组的力量均为 $4$。
- $S = \{2, 3\}$，$T = \{4\}$。两个牌组的力量均为 $8$。
- $S = \{4\}$，$T = \{2, 3\}$。两个牌组的力量均为 $8$。
- $S = \{3, 4\}$，$T = \{2\}$。两个牌组的力量均为 $12$。
- $S = \{2\}$，$T = \{3, 4\}$。两个牌组的力量均为 $12$。

样例输入输出 2 说明

唯一能使游戏平衡的方法是两个牌组都为空。

样例输入输出 3 说明

共有 $5$ 种方法可以使游戏平衡。

- $S = \{\}$，$T = \{\}$。两个牌组的力量均为 $0$。
- $S = \{1, 2\}$，$T = \{\}$。两个牌组的力量均为 $0$。
- $S = \{\}$，$T = \{1, 2\}$。两个牌组的力量均为 $0$。
- $S = \{1\}$，$T = \{2\}$。两个牌组的力量均为 $1$。
- $S = \{2\}$，$T = \{1\}$。两个牌组的力量均为 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
16 12 4 8```

### 输出

```
9```

## 样例 #2

### 输入

```
4
1 2 4 8```

### 输出

```
1```

## 样例 #3

### 输入

```
2
1 1```

### 输出

```
5```

## 样例 #4

### 输入

```
6
1 1 1 2 2 2```

### 输出

```
169```

# 题解

## 作者：BreakPlus (赞：8)



+ 题目相当于让我们找两个不交的异或值相等的集合，可以等价于找一个异或和为 $0$ 的集合 $S$ 再对其进行划分，划分方案数为 $2^{|S|}$。

+ 定义 $x^a \cdot  x^b = x^{a \oplus b}$，易用生成函数刻画答案：$\prod (2x^{a_i}+1)$ 的常数项系数即为答案。

+ 问题变成如何短时间内完成 $n$ 个上述形式的二项式的异或卷积。

----

+ 我们从分治 NTT 的思想中得到启发。为什么多个一次式乘积可以用分治优化？

+ 核心原因在于，两个多项式的卷积的复杂度取决于次数较高的一个。又因为 $\deg (AB) = \deg(A) + \deg(B)$，分治思想尽量让次数相近的多项式相乘，起到了优化算法的作用。

------

+ 那么其是否也能在异或卷积上起到类似的效果？

+ 为了实现类似的效果，我们可以考虑将**较多**的 $(2x^{a_i}+1)$ 卷到一起，但是卷出来的多项式的项数**较少**。

+ 我们发现如果有一堆数，其在二进制表示下有较多的位都相等（比如一个前缀都相等），那么从中选一个子集异或起来，相等的这些位要么不变，要么全变成 $0$，只有不相等的位有多种变化。

+ 具体地，假设有一个 $A \in [0, 2^k)$，将前 $k$ 位为 $A$ 的所有 $a_i$ 全部取出来。这时我们 **取出的 $a_i$ 的数量** 和 **这些数能异或得到的值的种类** 同阶。

+ 这是因为，$a_i$ 的数量是 $2^{n-k}$ 个（其中 $2^n$ 是值域大小），异或得到的值也只有后 $n-k$ 位能自由动，前面 $k$ 为要么都是 $0$，要么就是 $a$，共 $2^{n-k+1}$ 种。

+ 利用这个性质，按位分治，由钦定前 $k$ 位递归到 $k+1$ 位的情况，进行类似分治 NTT 的操作，写法、复杂度分析也与分治 NTT 类似。

+ 具体实现细节建议读者自行思考。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll mod=998244353, inv=(mod+1)/2;
ll Add(ll a,ll b){ if(a+b<mod) return a+b; return a+b-mod; }
ll Minus(ll a,ll b){ if(a-b<0) return a-b+mod; return a-b;}
ll n,a[1<<17],cnt[1<<17],t1[1<<17],t2[1<<17],t3[1<<17],t4[1<<17];
ll res0[18][1<<17], res1[18][1<<17], pre0[1<<17], pre1[1<<17];
void fwt(ll *a,ll n,ll tp=1){
	for(ll i=0;i<n;i++){
		for(ll j=0;j<(1ll<<n);j++){
			if((j>>i)&1) continue;
			ll a0 = a[j], a1 = a[j^(1ll<<i)];
			if(tp==1){
				a[j] = Add(a0, a1);
				a[j^(1ll<<i)] = Minus(a0, a1);
			}else{
				a[j] = 1ll * (a0 + a1) * inv % mod;
				a[j^(1ll<<i)] = 1ll * Minus(a0,a1) * inv % mod;
			}
		}
	}
} 
const ll B = 17;
void solve(ll i,ll sta){
	for(ll j=0;j<(1ll<<B-i);j++) res0[i][j]=res1[i][j]=0;
	if(i==B){
		res0[i][0] = pre0[cnt[sta]]; res1[i][0] = pre1[cnt[sta]];
		return;
	}
	solve(i+1, sta+(1ll<<B-1-i)); 
	for(ll j=0;j<(1ll<<B-1-i);j++) res0[i][j] = res0[i+1][j], res1[i][j^(1ll<<B-1-i)] = res1[i+1][j];
	solve(i+1, sta);
	for(ll j=0;j<(1ll<<B-i);j++) t1[j] = res0[i][j], t2[j] = res1[i][j];
	for(ll j=0;j<(1ll<<B-i);j++)  t3[j] = res0[i+1][j], t4[j] = res1[i+1][j];
	
	fwt(t1, B-i); fwt(t2, B-i); fwt(t3, B-i); fwt(t4, B-i); 
	for(ll j=0;j<(1ll<<B-i);j++) res0[i][j] = Add(1ll*t1[j]*t3[j]%mod, 1ll*t2[j]*t4[j]%mod);
	for(ll j=0;j<(1ll<<B-i);j++) res1[i][j] = Add(1ll*t1[j]*t4[j]%mod, 1ll*t2[j]*t3[j]%mod);
	fwt(res0[i], B-i, -1); fwt(res1[i], B-i, -1);
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]), cnt[a[i]]++;
	pre0[0]=1, pre1[1]=0;
	for(ll i=1;i<(1ll<<B);i++){
		pre0[i]=Add(pre0[i-1],Add(pre1[i-1],pre1[i-1]));
		pre1[i]=Add(Add(pre0[i-1],pre0[i-1]),pre1[i-1]);
	}
	solve(0, 0);
	printf("%lld\n", Add(res0[0][0], res1[0][0]));
	return 0;
}
```

---

## 作者：EuphoricStar (赞：5)

[UNR #2 黎明前的巧克力](https://uoj.ac/problem/310)。

枚举两个人选的卡的并集 $S$，那么当 $\bigoplus\limits_{i \in S} a_i = 0$ 时 $S$ 有贡献 $2^{|S|}$。

考虑将 $2^{|S|}$ 分摊到每个元素上，也就是每个元素有 $2$ 的贡献，然后把这些贡献乘起来。所以题目其实是想让我们算这个东西：$[x^0] \prod\limits_{i = 1}^n (1 + 2x^{a_i})$，定义 $x^i \times x^j = x^{i \oplus j}$。

令 $F_i(x) = 1 + 2x^{a_i}$，考虑给每个 $F_i$ FWT 一下，对位乘后再逆 FWT 回去。因此我们已经有了一个 $O(nV)$ 的做法，显然不能通过。

考虑 $F_i$ FWT 后的结果，因为此处 $\text{FWT}(a)_i = \sum\limits_{j} (-1)^{\text{popcount}(i \& j)} a_j$，容易发现 $\text{FWT}(F_i)$ 只含有 $3$ 或 $-1$。因此我们对位乘后第 $i$ 位的结果可以表示成 $(-1)^{x_i} 3^{n - x_i}$。

令 $G = \text{FWT}(F_1) + \text{FWT}(F_2) + \cdots + \text{FWT}(F_n)$，那么我们有 $-x_i + 3(n - x_i) = G_i$。解得 $x_i = \frac{3n - G_i}{4}$。又因为 FWT 的线性性我们有 $G = \text{FWT}(F_1 + F_2 + \cdots F_n)$，所以 $G_i$ 和 $x_i$ 都能快速求出来。所以我们求出这样对位乘后第 $i$ 位的结果，最后再逆 FWT 回去即可得到 $[x^0] \prod\limits_{i = 1}^n F_i$。

总时间复杂度 $O(n \log V)$。

```cpp
// Problem: K. Deck-Building Game
// Contest: Codeforces - 2023-2024 ICPC, Asia Jakarta Regional Contest (Online Mirror, Unrated, ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/problemset/problem/1906/K
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 131100;
const int N = 131072;
const ll mod = 998244353;
const ll inv2 = (mod + 1) / 2;

inline ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

ll n, a[maxn];

inline void FWT(ll *a, ll o) {
	for (int k = 1; k < N; k <<= 1) {
		for (int i = 0; i < N; i += (k << 1)) {
			for (int j = 0; j < k; ++j) {
				ll x = a[i + j], y = a[i + j + k];
				a[i + j] = (x + y) * o % mod;
				a[i + j + k] = (x - y + mod) * o % mod;
			}
		}
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		a[x] += 2;
	}
	a[0] += n;
	FWT(a, 1);
	ll inv4 = qpow(4, mod - 2);
	for (int i = 0; i < N; ++i) {
		ll x = (n * 3 - a[i] + mod) * inv4 % mod;
		a[i] = ((x & 1) ? mod - 1 : 1) * qpow(3, n - x) % mod;
	}
	FWT(a, inv2);
	printf("%lld\n", a[0]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：dAniel_lele (赞：3)

首先有一个容易的 $O(nV\log V)$ 的 FWT，在此不再阐述。

考虑优化，考虑分治，钦定前 $i$ 位，后 $17-i$ 位选出的数异或起来 $j$ 的方案数。每次合并的时候将第 $i$ 位为 $0/1$ 的情况分别从下一层对后 $17-i$ 位进行异或卷积。

注意到后 $17-i$ 位中选出的数的数量的奇偶性同样很重要（决定了前一位是 $0$ 还是 $1$），额外加一维记录即可。

对于每一层，我们需要对后 $17-i$ 位进行 FWT $2^i$ 次，故每一层复杂度就是 $O(V\log V)$，总共 $\log V$ 层，故总复杂度为 $O(V\log^2V)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005];
void makefac(){
	fac[0]=1; for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[1000000]=qp(fac[1000000],mod-2); for(int i=999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod; 
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int dp[2][20][1<<17];
int cnt[1<<17];
void init(){
	for(int i=0;i<(1<<17);i++){
		for(int j=0;j<=cnt[i];j++){
			if(j&1) (dp[1][0][i]+=qp(2,j)*C(cnt[i],j))%=mod;
			else (dp[0][0][i]+=qp(2,j)*C(cnt[i],j))%=mod;
		}
	}
}
void dft(int x,int y,int d,int ft,int tag){
	for(int i=0;i<d;i++){
		for(int j=0;j<(1<<d);j++){
			if((j>>i)&1){
				int p=ft+j-(1<<i),q=ft+j,vp=dp[x][y][p],vq=dp[x][y][q];
				if(tag==1){
					dp[x][y][p]=(vp+mod-vq)%mod;
					dp[x][y][q]=(vp+vq)%mod;
				}
				else{
					dp[x][y][p]=(vp+vq)*inv2%mod;
					dp[x][y][q]=(vq+mod-vp)*inv2%mod;
				}
			}
		}
	}
}
void solve(int l,int r,int lev){
	if(l==r){
		return ;
	}
	solve(l,mid,lev-1);
	solve(mid+1,r,lev-1);
	int len=(1<<(lev-1));
	dft(0,lev-1,lev-1,l,1);
	dft(1,lev-1,lev-1,l,1);
	dft(0,lev-1,lev-1,mid+1,1);
	dft(1,lev-1,lev-1,mid+1,1);
	for(int i=l;i<=mid;i++){
		(dp[0][lev][i]+=dp[0][lev-1][i]*dp[0][lev-1][i+len])%=mod;
		(dp[0][lev][i+len]=dp[1][lev-1][i]*dp[1][lev-1][i+len])%=mod;
		(dp[1][lev][i]+=dp[1][lev-1][i]*dp[0][lev-1][i+len])%=mod;
		(dp[1][lev][i+len]+=dp[0][lev-1][i]*dp[1][lev-1][i+len])%=mod;
	}
	dft(0,lev,lev-1,l,-1);
	dft(1,lev,lev-1,l,-1);
	dft(0,lev,lev-1,mid+1,-1);
	dft(1,lev,lev-1,mid+1,-1);
}
signed main(){
	makefac();
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		int a; cin>>a;
		cnt[a]++;
	}
	init();
	solve(0,(1<<17)-1,17);
	cout<<(dp[0][17][0]+dp[1][17][0])%mod;
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

问题等价于先选出一个异或和为 $0$ 的子集，再选出这个集合的一个子集。

可以通过生成函数刻画答案，不妨令 $a \times x^p \times b \times x^q = a \times b \times x^{p \oplus q}$。答案就是多项式 $\prod_{i=1}^n (1+2 \times x^{A_i})$ 的 $x^0$ 项的系数。

我们考察下 $(1+2 \times x^{A_i})$ 做异或 FWT 运算之后会得到什么，由于异或 FWT 的定义之一是 $\text{FWT}(A)_i = \sum_j (-1)^{\text{popc}(i \cap j)} \times A_j$，所以得到的数组第 $j$ 位会因为 $popc(i \cap j)$ 的奇偶性为 $-1$ 或者 $3$。

不妨设 $\text{FWT} \prod_{i=1}^n (1+2 \times x^{A_i})$ 第 $i$ 位被贡献了 $t_i$ 个 $-1$，第 $i$ 位的值就是 $(-1)^{t_i} \times 3^{n - t_i}$。求出每一位的值后，做一遍逆异或 FWT 就能求出答案。

下面考虑求解 $t_i$ 的值，考虑这样一个算法：记序列 $F = \sum \text{FWT}(1+2 \times 2^{A_i})$，有 $F_i = -t_i + 3 \times (n-t_i)$。也就是如果能求出 $F$ 序列，就能求出 $t_i$。

根据 FWT 的线性性，$F = \text{FWT} \sum (1+2 \times x^{A_i})$，于是可以在 $O(n+V \log V)$ 的时间复杂度内求出答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = (1<<20);
int a[maxn],n;
void fwt_xor(int *f,int x=1){
    for(int o=2,k=1;o<=maxn;o<<=1,k<<=1){
        for(int i=0;i<maxn;i+=o){
            for(int j=0;j<k;j++){
                int a=f[i+j];
                int b=f[i+j+k];
                f[i+j]=(a+b)%mod;
                f[i+j+k]=(a+mod-b)%mod;
                f[i+j]=f[i+j]*x%mod,f[i+j+k]=f[i+j+k]*x%mod;
            }
        }
    }
}
int b[maxn];
int c[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],b[0]++,b[a[i]]+=2;
    fwt_xor(b);
    for(int i=0;i<maxn;i++) b[i]=((3*n+mod-b[i])%mod)/4;
    for(int i=0;i<maxn;i++) c[i]=qpow(mod-1,b[i])*qpow(3,n-b[i])%mod;
    fwt_xor(c,(mod+1)/2);
    cout<<c[0]<<"\n";
    return 0;
}
```

---

## 作者：shinkuu (赞：0)

很有趣的题。

首先一个必要的转化是，注意到对于一个 $\bigoplus_{x\in S}x=0$ 的 $S$，对于答案有 $2^{|S|}$ 的贡献，于是考虑从这方面去计数。

然后是 $2^{|S|}$ 比较难搞，考虑拆给每一个集合中的元素，也就是说令每个元素初始就有 $2$ 种选取的方案，于是就只需要计数选出 $\bigoplus_{x\in S}x=0$ 的 $S$ 的方案数。

那么就有一个显然的 $O(nV\log V)$ 做法，即每次异或卷积合并。考虑优化。首先的一个感觉是，直接合并太蠢了，如果排序之后再做，前面部分异或卷积可以少枚举一点。然后就能推广了：对于最高的若干位相同的数，可以只对剩下的位做异或卷积，并记录选了奇/偶数个。

于是就可以考虑一个分治的结构：考虑设 $f_{i,0/1}$ $[p,p+2^k)(2^k|p)$ 内选出若干个，使得后 $k$ 位异或和为 $i$ 且选了奇/偶数个数的方案数。那么就可以先对于 $[p,p+2^{k-1}),[p+2^{k-1},p+2^k)$ 求解，再对后 $k$ 位异或卷积合并。时间复杂度为 $T(V)=2T(\frac V2)+O(V\log V)=O(V\log^2V)$。

code：

```cpp
int n,m,c[N],f[N][2];
int fac[N],ifac[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int binom(int x,int y){if(x<0||y<0||x<y){return 0;}return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;}
il int qpow(int x,int y){int ret=1;while(y){if(y&1){ret=1ll*ret*x%mod;}x=1ll*x*x%mod,y>>=1;}return ret;}
void initFac(int n){fac[0]=1;rep(i,1,n){fac[i]=1ll*fac[i-1]*i%mod;}ifac[n]=qpow(fac[n],mod-2);drep(i,n-1,0){ifac[i]=1ll*ifac[i+1]*(i+1)%mod;}}
void FWT(int L,int R,int op){
	for(int k=2;k<=R-L;k<<=1){
		int l=k>>1;
		for(int i=L;i<R;i+=k){
			rep(j,i,i+l-1){
				rep(p,0,1){
					f[j][p]=Mod(f[j][p],f[j+l][p]);
					f[j+l][p]=Mod(f[j][p],mod-Mod(f[j+l][p],f[j+l][p]));
					f[j][p]=1ll*f[j][p]*op%mod,f[j+l][p]=1ll*f[j+l][p]*op%mod;
				}
			}
		}
	}
}
void solve(int l,int r){
	if(l+1==r){
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid,r);
	int d=mid-l;
	FWT(l,mid,1),FWT(mid,r,1);
	int tmp[2][2];
	rep(i,l,mid-1){
		tmp[0][0]=1ll*f[i][0]*f[i+d][0]%mod;
		tmp[0][1]=1ll*f[i][1]*f[i+d][0]%mod;
		tmp[1][0]=1ll*f[i][1]*f[i+d][1]%mod;
		tmp[1][1]=1ll*f[i][0]*f[i+d][1]%mod;
		f[i][0]=tmp[0][0],f[i][1]=tmp[0][1];
		f[i+d][0]=tmp[1][0],f[i+d][1]=tmp[1][1];
	}
	FWT(l,mid,(mod+1)/2),FWT(mid,r,(mod+1)/2);
}
void Yorushika(){
	read(n),initFac(n);
	rep(i,1,n){
		int x;read(x);
		c[x]++;
	}
	rep(i,0,1<<17){
		f[i][0]=1;
		rep(j,1,c[i]){
			f[i][j&1]=Mod(f[i][j&1],1ll*binom(c[i],j)*qpow(2,j)%mod);
		}
	}
	solve(0,1<<17);
	printf("%d\n",Mod(f[0][0],f[0][1]));
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Mashu77 (赞：0)

有大小为 $n$ 的多重集 $A$。求找到两个不相交子集，使它们各自的异或和相等的方案数。

很容易将其转换为求：$\displaystyle sum_{S\subset A}{2^{|S|}\cdot [\oplus_{x\in S}x=0]}$。

解法：
构造多项式 $F$，使得 $\displaystyle F_i(A)=\sum_{S\in A}{2^{|S|}\cdot [\oplus_{x\in S}x=i]}$，要求的结果是 $F_0(A)$。

那么 $F$
 满足如下特性：$F(A\cup B)=F(A) \oplus F(B)$，其中 $\oplus$ 代表多项式的异或卷积。

对只包含同一个数的集合，容易求出多项式只包含两项：

$$F(\{i\}\cdot n)=a_0+a_i\cdot x^i,a_i=\frac{1}{2}((-1)^n+3^n),a_0=3^n-a_i$$ 
 

记 $U=2^{\lceil \log \max A\rceil}$，则卷积合并所有多项式即可得到答案，时间复杂度 $O(U^2\log U)$。

考虑采用分治卷积优化时间复杂度。记 $G(l,r)$ 为所有 $i\in[l,r)$
 对应多项式的卷积，可以观察到如下性质：

- 若采用分治法计算，则一定有 $r-l\equiv2^b,l\equiv r\equiv0\pmod 2^b$；
- $G(l,r)$ 中所有项的次数落在区间 $[0,r-l)$
 和 $[l,r)$
 内。
 
因此，分治的每一层只需维护两个次数小于 $r-l$
的多项式，合并时计算四次卷积即可。根据主定理可得时间复杂度为 $O(U^2\log^2U)$。

---

## 作者：蒟蒻君HJT (赞：0)

注意到分配的过程等价于先选出一个异或和为 $0$ 的下标集合 $S$，再将 $S$ 划分为无交并为 $S$ 的两个集合 $S_1$ 和 $S_2$，方案数 $2^{|S|}$。

因此可以求出总方案数为 $\displaystyle\prod_{i=1}^{n}(1+2x^{a_i})$ 的 $x^0$ 项前的系数，其中指数上的加法对应非负整数的异或运算，即对 $n$ 个单项式做[异或卷积](https://www.luogu.com.cn/problem/P4717)。

联想到对 $n$ 个次数较低（不超过某一常数）的单项式做加法卷积的时间复杂度可以用分治 $\text{FFT}$ 控制在 $\Theta(n\log^2 n)$，因此对 $n$ 个次数较低的单项式做异或卷积的时间复杂度也可以用分治 $\text{FWT}$ 控制在 $\Theta(n\log^2 n)$。然而这道题里面我们要面对的是次数可能很高的若干单项式的异或卷积，所以分治就显得没有意义了······吗？

单项式卷积的相对顺序是无所谓的，如果用类似 01-trie 的分治方式来做的话，发现在高位上的取值只有两种，且完全取决于下层取的元素 $(x^{t})$ 个数的奇偶性。因此除了记录低位的信息之外，再额外记一维表示选了奇数个还是偶数个就行了。这一维的运算也符合异或运算的规律。

对于相同的 $a_i$ 需要在底层手动合并，分别计算选奇数个和选偶数个的方案数之和，式子是容易的。

记 $C=131072$，对于分治区间长度为 $2^{w}$ 的第 $w$ 层，每个区间只需要做一次长度为 $2^{w+1}$ 的异或卷积，时间复杂度 $\Theta(\displaystyle\frac{C}{2^w}\times (w+1)2^{w+1})=\Theta(Cw)$，总时间复杂度 $\displaystyle\sum_{w=0}^{\log_2 C}\Theta(Cw)=\Theta(C\log^2 C)$。空间用 ```std::vector``` 动态开辟，总共 $\Theta(C\log C)$。

---

