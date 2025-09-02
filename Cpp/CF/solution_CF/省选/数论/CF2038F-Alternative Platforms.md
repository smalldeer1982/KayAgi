# Alternative Platforms

## 题目描述

Suppose you are working in the Ministry of Digital Development of Berland, and your task is to monitor the industry of video blogging.

There are $ n $ bloggers in Berland. Recently, due to the poor state of the main video platform in Berland, two alternative platforms were introduced. That's why bloggers started to reupload their videos to these alternative platforms. You've got the statistics that the $ i $ -th blogger uploaded $ v_i $ videos to the first alternative platform and $ r_i $ videos to the second alternative platform.

You think that a potential user will be upset if even at least one of his favorite bloggers doesn't upload anything. However, if a blogger uploads videos to both platforms, the user will watch that blogger on the platform where more videos are available. So, you've come up with the following function to estimate user experience. Suppose a user watches $ k $ bloggers $ b_1, b_2, \dots, b_k $ ; then, let user experience be $ $$$E(b_1, \dots, b_k) = \max\left(\min_{i=1..k}{v[b_i]}, \min_{i=1..k}{r[b_i]}\right). $ $ </p><p>In order to get some statistics, you want to calculate the value  $ \\mathit{avg}\_k $  that is equal to an average experience among all subsets of bloggers of size  $ k $ . Also, you have to calculate  $ \\mathit{avg}\_k $  for each  $ k $  from  $ 1 $  to  $ n $ .</p><p>Since answers may be too large, print them modulo  $ 998\\,244\\,353$$$.

## 说明/提示

In the first example, $ 332748119 $ is $ \frac{4}{3} $ . In the third example, $ 199648873 $ is $ \frac{12}{5} $ .

## 样例 #1

### 输入

```
3
2 1 2
1 2 1```

### 输出

```
2 332748119 1```

## 样例 #2

### 输入

```
4
5 5 5 5
0 0 0 0```

### 输出

```
5 5 5 5```

## 样例 #3

### 输入

```
5
1 9 3 7 5
2 4 6 8 5```

### 输出

```
6 4 3 199648873 2```

# 题解

## 作者：_jimmywang_ (赞：5)

首先把平均值换成总和除以方案数。

总所周知，$\max\{a,b\}=a+b-\min\{a,b\}$。

所以我们可以把原式写成：

$$E(b_1,b_2,\dots,b_k)=\min_{i=1}^k v[b_i]+\min_{i=1}^k r[b_i]-\min_{i=1}^k (\min\{v[b_i],r[b_i]\})$$

我们发现此时 $v[i],r[i],\min\{v[i],r[i]\}$ 构成了 3 个可以独立计算的数列，我们要算的就是对于一个数列，所有大小为 $k$ 的子集的最小值之和。

假设我们考虑的数列叫 $a_1,a_2,\dots a_n$。因为考虑的是子集，所以可以放心进行排序。我们先从小到大排序，并枚举最小值所在的位置。

那么所有大小为 $k$ 的子集的最小值之和 $sum_k$ 就等于：

$$\sum_{i=1}^{n-k+1}a_i\binom{n-i}{k-1}$$

如果你很会卷，那么你能一眼看出这玩意 FFT 一下就做完了，但是如果你不会卷，那么我们来推式子。

$$\begin{align}sum_k&=\sum_{i=1}^{n-k+1}a_i\binom{n-i}{k-1}\\&=\sum_{i=1}^{n-k+1}a_i\dfrac{(n-i)!}{(k-1)!(n-i-k+1)!}\\&=\dfrac{1}{(k-1)!}\sum_{i=1}^{n-k+1}\dfrac{a_i(n-i)!}{(n-i-k+1)!}\end{align}$$

设 $F(x)=\sum_{i=1}^na_i(n-i)!x^i, G(x)=\sum_{i=0}^n\dfrac{x^i}{i!}$，那么 $sum_k$ 就等于：

$$\dfrac{1}{(k-1)!}[x^{n-k+1}]F \times G$$

然后把三个序列都做一遍并把结果相加，最后每个 $sum_k$ 都除以 $\binom{n}{k}$ 即可。


其实你发现每个序列独立，那么我们将这三个序列分别排序（设排完序以后 $v,r,\min\{v,r\}$ 分别变成 $A,B,C$ 三个序列），那么我们对 $a_i=A_i+B_i-C_i$ 求一次 $sum_k$ 就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;++i)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
const ll Bit=19;
const ll PoL=(1<<Bit)+5;
ll but[PoL],pw[2][PoL],Curl=-1;
void out(ll *a,ll n){f(i,0,n)printf("%lld ",a[i]);puts("");}
const ll mod=998244353,G=3,Gi=332748118;
ll qp(ll a,ll b=mod-2){ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}return ans%mod;
}
namespace poly{
	ll jc[PoL+10],inv[PoL+10],inc[PoL+10];
	ll w[PoL]={1},qwq=0,Curl=-1;
	// ll usla[PoL],uslb[PoL];
	bool hpre=0;
	void pre(){
		if(hpre)return;hpre=1;
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,PoL-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}
	ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
	#define ck(x) ((x)>=mod?(x)-mod:(x))
	void revbit(ll k){
		if(Curl==k)return;Curl=k;
		f(i,0,k-1)but[i]=but[i>>1]>>1|((i&1)?(k>>1):0);
	}
	ll NTT(ll *a,ll *to,ll n,ll o){
		ll _n=1;while(_n<=n)_n<<=1;n=_n;
		revbit(n);qwq=0;
		ll inv=qp(n);
		
		// memcpy(to,a,sizeof(to));
		f(i,0,n-1)to[i]=a[i];
		f(i,0,n-1)if(i<but[i])swap(to[i],to[but[i]]);
		
		for(int l=1;l<n;l<<=1){qwq++;
			ll Wn=qp((o==1?G:Gi),((mod-1)/(l<<1)));
			for(int i=1;i<l;i++)w[i]=w[i-1]*Wn%mod;
			for(int j=0;j<n;j+=l+l){
				for(int i=0;i<l;i++){
					int tt=w[i]*to[i|j|l]%mod;
					to[i|j|l]=mod+to[i|j]-tt;
					to[i|j]=to[i|j]+tt;
				}
			}if(qwq%9==0)f(i,0,n-1)to[i]%=mod;
		}if(o==1)inv=1;
		f(i,0,n-1)to[i]=to[i]*inv%mod;
		return n-1;
	}
	void Mul(ll *f,ll *g,ll *to,ll n,ll m){
		static ll _f[PoL],_g[PoL],_n,_m;_n=n,_m=m;
		f(i,0,_n)_f[i]=f[i];
		f(i,0,_m)_g[i]=g[i];
		_m+=_n,_n=1;
		_n=NTT(_f,_f,_m,1);NTT(_g,_g,_m,1);
		f(i,0,_n)to[i]=_f[i]*_g[i]%mod;
		NTT(to,to,_m,-1);
		f(i,_m+1,_n)to[i]=0;
		f(i,0,_n)_f[i]=_g[i]=0;
	}
}
using namespace poly;
ll f[PoL],g[PoL];
ll n,m;
ll a[200010],b[200010],c[200010];
ll res[200010];
int main(){
	pre();
	n=d;
	f(i,1,n)a[i]=d;f(i,1,n)b[i]=d;
	f(i,1,n)c[i]=min(a[i],b[i]);
	sort(a+1,a+n+1),sort(b+1,b+n+1),sort(c+1,c+n+1);
	f(i,1,n)a[i]+=b[i]-c[i];
	f(i,0,n)f[i]=a[i]*jc[n-i]%mod,g[i]=inc[i];
	Mul(f,g,f,n,n);
	// f(k,1,n){
	// 	f(i,1,n)res[k]=(res[k]+a[i]*C(n-i,k-1))%mod;
	// }
	f(i,1,n)cout<<f[n-i+1]*inc[i-1]%mod*qp(C(n,i))%mod<<" ";
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

有两个长度为 $n$ 的序列 $v,r$，定义 $U=\{1,2,3,\cdots,n\}$。

对于一个集合 $S\subseteq U$，定义其的权值 $E(S)$ 为：

$$
E(S)=\max\left(\min_{k\in S} v_k, \min_{k\in S} r_k\right)
$$

你需要对于 $k\in[1,n]$，求出所有大小为 $k$ 的 $S$ 的权值平均值。答案对 $998,244,353$ 取模。

$1\leq n\leq 2\times 10^5,0\leq r_i,v_i\leq 10^6$。

## 思路

首先我们发现设 $f(k)$ 表示大小为 $k$ 的 $S$ 的权值总和，则要求的就是 ${\binom{n}{k}}^{-1}f(k)$。将 $f(k)$ 的式子写下来：

$$
f(k)=\sum_{S\subseteq U,|S|=k}E(S)=\sum_{S\subseteq U,|S|=k}\sum_{i=0}^{+\infty}[E(S)=i]i
$$

通过经典 trick（好像是期望里的？），继续变形：

$$
f(k)=\sum_{S\subseteq U,|S|=k}\sum_{i=0}^{+\infty}[E(S)=i]i=\sum_{S\subseteq U,|S|=k}\sum_{i=1}^{+\infty}[E(S)\geq i]
$$

考察这个式子：

$$
\sum_{S\subseteq U,|S|=k}\sum_{i=1}^{+\infty}[E(S)\geq i]
$$

不妨探究 $E(S)\geq i$ 的等价条件。不难发现只要满足下列两个条件任意之一就可以得到 $E(S)\geq i$，反之亦然：

$$
\begin{aligned}
&\min_{k\in S} v_k\geq i\\
&\min_{k\in S} r_k\geq i
\end{aligned}
$$

然后我们只需要对这两个序列计数即可。

我们计算出 $v$ 中大于等于 $i$ 的元素数量 $A_i$，$r$ 中大于等于 $i$ 的元素数量 $B_i$，$v_i,r_i$ 均大于等于 $i$（即 $\min(v_j,r_j)\geq i$）的元素数量 $C_i$。

则答案就是：

$$
\sum_{i=1}^{+\infty} \binom{A_i}{k}+\binom{B_i}{k}-\binom{C_i}{k}
$$

计算 $A,B,C$ 的话，观察到值域 $10^6$ 并不大，直接开三个桶再做三遍后缀和即可。

现在我们可以做到 $O(n^2+V)$ 难以通过本题。其中 $V$ 为值域。

定义：

$$
f_a(k)=\sum_{i=1}^{+\infty} \binom{a_i}{k}=\sum_{i=1}^{+\infty} \frac{a_i!}{k!(a_i-k)!}=\frac{1}{k!}\sum_{i=1}^{+\infty}\frac{a_i!}{(a_i-k)!}
$$

记 $t_a(i)=\sum_j[a_j=i]$，则有：

$$
f_a(k)=\frac{1}{k!}\sum_{i=1}^{+\infty}\frac{a_i!}{(a_i-k)!}=\frac{1}{k!}\sum_{i=0}^{n} \frac{i!\cdot t_a(i)}{(i-k)!}
$$

定义 $g(i)=(n-i)!$，代入原式得：

$$
f_a(k)=\frac{1}{k!}\sum_{i=0}^{n} \frac{i!\cdot t_a(i)}{(i-k)!}=\frac{1}{k!}\sum_{i=0}^{n} \frac{i!\cdot t_a(i)}{g(n+k-i)}
$$

用 NTT 优化即可。

时间复杂度 $O(n\log n+V)$。

## 代码

[Submission Link](https://codeforces.com/contest/2038/submission/292404816)。

核心代码：

```cpp
const int N = 2e5 + 5, M = 1e6 + 5, FFT_N = 1e6 + 5;
int n, a[N], b[N], c[N], A[M], B[M], C[M];
int fact[N], inv[N];
 
constexpr int mod = 998244353, g = 3, ginv = 332748118;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }
 
int binom(int n, int m){ return n < m ? 0 : Mul(fact[n], Mul(inv[m], inv[n - m])); }
 
int fastpow(int x, int y){
    int ret = 1;
    for(;y;y>>=1,x=Mul(x, x)){ if(y & 1) ret = Mul(ret, x); }
    return ret;
}
 
void init(int n){
    fact[0] = inv[0] = fact[1] = inv[1] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = Mul(fact[i - 1], i);
        inv[i] = Mul(inv[mod % i], mod - mod / i);
    }
    for(int i=1;i<=n;i++) inv[i] = Mul(inv[i - 1], inv[i]);
}

int res_a[N], res_b[N], res_c[N], cnt[N], m;

void solve(int* a, int* res){
    for(int i=0;i<=n;i++) cnt[i] = 0;
    for(int i=1;i<=m;i++) cnt[a[i]]++;
    Poly poly1(n + 1), poly2(n + 1);
    for(int i=0;i<=n;i++) poly1[i] = Mul(fact[i], cnt[i]);
    for(int i=0;i<=n;i++) poly2[i] = inv[n - i];
    Poly res_poly = poly1 * poly2;
    for(int i=1;i<=n;i++) res[i] = res_poly[i + n];
}
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i], c[i] = min(a[i], b[i]);
    m = max(*max_element(a + 1, a + n + 1), *max_element(b + 1, b + n + 1));
    for(int i=1;i<=n;i++) A[a[i]]++, B[b[i]]++, C[c[i]]++;
    for(int i=m;~i;i--) A[i] += A[i + 1], B[i] += B[i + 1], C[i] += C[i + 1];
    init(n);
    solve(A, res_a), solve(B, res_b), solve(C, res_c);
    for(int k=1;k<=n;k++){
        int ans = Sub(Add(res_a[k], res_b[k]), res_c[k]);
        ans = Mul(ans, inv[k]);
        cout << Mul(ans, fastpow(binom(n, k), mod - 2)) << ' ';
    }
    return 0;
}
```

---

## 作者：songhongyi (赞：1)

题意：给定 $a,b$ 两个序列，定义某个 $\{1,2,\cdots,n\}$ 的子集 $S$ 的权值为：
$$
\max\left(\min_{i \in S} a_i, \min_{i \in S} b_i\right)
$$
求大小为 $k$ 的所有子集的权值和。

考虑某个 $a_i$ 作为答案产生贡献，此时 $S$ 需要满足什么。首先要有 $\forall x \in S, \, a_x \ge a_i$，其次，如果 $b_i > a_i$，则额外要求 $\exist x \in S \text{ s.t. } b_x \le a_i$。因此我们需要排除掉 $\min{b_j} > a_i$ 的 $S$，这可以通过二维数点数出。交换 $a,b$ 后同理。那我们的贡献全部变成了诸如给定一个 $i$，则对所有的 $j \le i$ 产生系数为 $\binom {i}{j}$ 的贡献。

转化一下，可以变成给定一个 $v_i$，对每个 $i$ 求出 $\sum_{j \ge i} \binom{j} {i}v_j$。

拆开后不难发现，设：
$$
F = \sum i!\cdot v_i x^i,  \quad G = \sum \dfrac 1 {i!} x^{-i}
$$
，则 $\dfrac {[x^i] F \cdot G}{i!}$ 即为答案。

复杂度瓶颈在二维数点和卷积，是 $O(n \log n)$ 的。

```cpp
struct Node
{
    int v, r;
    int id;
} a[ MAXN ];
mint v[ MAXN ];
mint res[ MAXN ];
int main()
{
    cin.tie( 0 );
    int n;
    cin >> n;
    init( n );
    for ( int i = 1; i <= n; i++ )
    {
        a[ i ].id = i;
        cin >> a[ i ].v;
    }
    for ( int i = 1; i <= n; i++ )
    {
        cin >> a[ i ].r;
        M = max( M, a[ i ].r + 1 );
    }
    sort( a + 1, a + n + 1,
          [&]( Node a, Node b ) { return ( a.v == b.v ? a.id < b.id : a.v > b.v ); } );
    for ( int i = 1; i <= n; i++ )
    {
        int ct = i - 1 - T.query( a[ i ].v );
        if ( a[ i ].r <= a[ i ].v )
        {
            v[ i - 1 ] += a[ i ].v;
        }
        else
        {
            v[ i - 1 ] += a[ i ].v;
            v[ ct ] -= a[ i ].v;
        }
        T.add( a[ i ].r, 1 );
    }
    T.init();
    sort( a + 1, a + n + 1,
          [&]( Node a, Node b ) { return ( a.r == b.r ? a.id < b.id : a.r > b.r ); } );
    for ( int i = 1; i <= n; i++ )
    {
        int ct = i - 1 - T.query( a[ i ].r - 1 );
        if ( a[ i ].v < a[ i ].r )
        {
            v[ i - 1 ] += a[ i ].r;
        }
        else
        {
            v[ i - 1 ] += a[ i ].r;
            v[ ct ] -= a[ i ].r;
        }
        T.add( a[ i ].v, 1 );
    }
    vector< mint > f( n + 1 );
    vector< mint > g( n + 1 );
    for ( int i = 0; i <= n; i++ )
    {
        f[ i ] = v[ i ] * fac[ i ];
        g[ i ] = ifac[ n - i ];
    }
    vector< mint > h = multiple( f, g );
    for ( int i = 0; i < n; i++ )
    {
        res[ i + 1 ] = h[ i + n ] * ifac[ i ];
    }
    for ( int i = 1; i <= n; i++ )
    {
        res[ i ] = res[ i ] * qpow( C( n, i ), pmod - 2 );
        cout << raw( res[ i ] ) << " ";
    }
    cout << endl;
}
```

---

## 作者：TTpandaS (赞：1)

唐氏选手做题记录。

首先 $k=1$ 的答案可以先计算出来。 

考虑计算每个 $v_i$ 和 $r_i$ 的贡献。因为对于相等的值两边都计算会算重，所以以下只在计算 $v_i$ 贡献时考虑 $r_j$ 的最小值与 $v_i$ 相同的情况。  

先考虑 $v_i$ 的贡献。

按照 $v_i$ 排序，令 $v_i$ 是最小值，且比要取的 $r_j$ 最小值大，令 $a_i$ 表示满足 $p>i,r_p \leq v_i$ 的 $p$ 的数量。

如果 $r_i>v_i$，那么在满足条件的 $a_i$ 中必须要取至少一个数，所以枚举取的数量为 $j$，那么对大小为 $2 \leq k \leq n-i+1$ 的答案的贡献为 $v_i \times \sum_{j=1}^{a_i} C_{a_i}^{j} \times C_{n-i-a_i}^{k-1-j}$。其中 $\sum_{j=1}^{a_i} C_{t}^{j} \times C_{n-i-a_i}^{k-1-j}=C_{n-i}^{k-1}-C_{n-i-a_i}^{k-1}$。

如果 $r_p \leq v_i $，那么对取的数没有要求，所以对大小为 $2 \leq k \leq n-i+1$ 的答案的贡献为 $v_i \times C_{n-i}^{k-1}$。

两种情况都有 $v_i \times C_{n-i}^{k-1}$ 的贡献，考虑先算出这部分贡献，再减去 $r_i>v_i$ 时的 $v_i \times C_{n-i-a_i}^{k-1}$ 即可。

设 $A_k=v_i \times C_{n-i}^{k-1}$，令 $F(x)=v_i \times (n-i)! \times x^i,G(x)=\dfrac{x^i}{i!} $，那么 $A_k=\dfrac{1}{(k-1)!} [x^{n-k+1}]F(x) \times G(x)$，所以一个 NTT 就完了。

要减去的部分看起来不太好处理，先放在一边。

接下来考虑 $r_i$ 的贡献。

按照 $r_i$ 排序，令 $r_i$ 是最小值，且比要取的 $v_j$ 最小值大，令 $b_i$ 表示满足 $p>i,v_p<r_i$ 的 $p$ 的数量。

如果 $v_i \geq r_i$，那么在满足条件的 $b_i$ 中必须要取至少一个数，所以枚举取的数量为 $j$，那么对大小为 $2 \leq k \leq n-i+1$ 的答案的贡献为 $r_i \times \sum_{j=1}^{b_i} C_{b_i}^{j} \times C_{n-i-b_i}^{k-1-j}$。其中 $\sum_{j=1}^{b_i} C_{t}^{j} \times C_{n-i-b_i}^{k-1-j}=C_{n-i}^{k-1}-C_{n-i-b_i}^{k-1}$。

如果 $v_i < r_i$，那么对取的数没有要求，所以对大小为 $2 \leq k \leq n-i+1$ 的答案的贡献为 $r_i \times C_{n-i}^{k-1}$。

两种情况都有 $r_i \times C_{n-i}^{k-1}$ 的贡献，考虑先算出这部分贡献，再减去 $v_i \leq r_i$ 时的 $r_i \times C_{n-i-b_i}^{k-1}$ 即可。

令 $A'_x=r_i \times C_{n-i}^{k-1}$，那么与求 $A_x$ 类似的，令 $F'(x)=r_i \times (n-i)! \times x^i,G'(x)=\dfrac{x^i}{i!} $，那么 $A'_k=\dfrac{1}{(k-1)!} [x^{n-k+1}]F'(x) \times G'(x)$，所以还是一个 NTT 就完了。

要减去的部分还是看起来不太好处理，但是让我们把两个需要减的情况让一起考虑。

难处理的部分在于 $C_{n-i-a_i}^{k-1}$ 和 $C_{n-i-b_i}^{k-1}$，换个形式写就是 $C_{n-(i+a_i)}^{k-1}$ 和 $C_{n-(i+b_i)}^{k-1}$。观察 $i+a_i$ 和 $i+b_i$ 是什么。

在按 $v_i$ 排序时，如果 $r_i>v_i$，那么对于 $j<i$ 的所有 $j$ 都有 $v_j \leq v_j$，所以 $\min(r_j,v_j) \leq v_i$。然后对于满足条件的那 $a_i$ 个数 $p$ ，都有 $r_p \leq v_i$，所以也满足 $\min(r_p,v_p) \leq v_i$，而其余数 $j$ 都不满足 $\min(r_j,v_j) \leq v_i$，所以 $i+a_i$ 本质上是按照 $\min(r_j,v_j)$ 排序后 $i$ 的排名。

在按 $r_i$ 排序时，如果 $v_i \geq r_i$，那么对于 $j<i$ 的所有 $j$ 都有 $r_j \leq r_j$，所以 $\min(r_j,v_j) \leq r_i$。然后对于满足条件的那 $b_i$ 个数 $p$ ，都有 $v_p < r_i$，所以也满足 $\min(r_p,v_p) \leq r_i$，而其余数 $j$ 都不满足 $\min(r_j,v_j) \leq r_i$，所以 $i+b_i$ 本质上是按照 $\min(r_j,v_j)$ 排序后 $i$ 的排名。

然后可以发现满足 $r_i>v_i$ 和 $v_i \geq r_i$ 两个条件的 $i$ 无交且并集为全集，所以就相当于是按照 $\min(r_i,v_i)$ 排序后，对答案的贡献为 $- \min(r_i,v_i) \times C_{n-i}^{k-1}$。

令 $A''_x=\min(r_i,v_i) \times C_{n-i}^{k-1}$，那么与上面相同，令 $F''(x)=\min(r_i,v_i) \times (n-i)! \times x^i,G''(x)=\dfrac{x^i}{i!} $，那么 $A''_k=\dfrac{1}{(k-1)!} [x^{n-k+1}]F''(x) \times G''(x)$，所以还是一个 NTT 就完了。

然后唐氏选手就做完了。然后唐氏选手发现他干的事情本质上就是拆分 $\max(a,b)=a+b-\min(a,b)$，这是一个经典 trick，所以他是唐氏选手。

---

## 作者：Petit_Souris (赞：0)

奶龙题，做完了一看题解发现写的也是一篇比一篇奶龙，补个简洁点的题解。

首先考虑一步 min - max 容斥，现在相当于计算 $\min v_k+\min r_k-\min(\min v_k,\min r_k)$。下面只考虑给定序列 $a$，计算 $k$ 元子集的最小值之和这个问题，上面式子的三部分显然都可以用相同方法解决。

运用经典的套路，最小值之和就相当于计算最小值 $\le x$ 的方案数，对所有 $x\ge 1$ 求和（这样最小值 $=x$ 的恰好算了 $x$ 次）。因此设 $a$ 序列中 $\ge x$ 的有 $c$ 个，会对 $ans_k$ 贡献 $\binom{c}{k}$。

那么问题就是对于一个给定的 $c$ 序列，计算每个 $k$ 的 $\sum \binom{c_i}{k}$。先把相同的 $c$ 放一起，然后发现就是个差卷积形式，直接 NTT 即可。时间复杂度 $\mathcal O(n\log n)$。值域比较小只是方便你桶排的，开大了一样可以做。


```cpp
using namespace Poly;
ll n,a[N],b[N],c[N],bin[N],cnt[N],ans[N],s;
poly f,g;
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    Init(V+2);
    rep(i,1,n)a[i]=read();
    rep(i,1,n)b[i]=read(),c[i]=min(a[i],b[i]);
    memset(bin,0,sizeof(bin));
    memset(cnt,0,sizeof(cnt));
    rep(i,1,n)bin[a[i]]++;
    s=0;
    per(i,V,1){
        s+=bin[i];
        cnt[s]++;
    }
    f.resize(n+1),g.resize(n+1);
    rep(i,1,n)f[i]=cnt[i]*fac[i]%Mod;
    rep(i,0,n)g[n-i]=ifac[i];
    f=f*g;
    rep(i,n+1,n+n)ans[i-n]=(ans[i-n]+1ll*f[i]*ifac[i-n])%Mod;
    memset(bin,0,sizeof(bin));
    memset(cnt,0,sizeof(cnt));
    rep(i,1,n)bin[b[i]]++;
    s=0;
    per(i,V,1){
        s+=bin[i];
        cnt[s]++;
    }
    f.a.clear(),g.a.clear();
    f.resize(n+1),g.resize(n+1);
    rep(i,1,n)f[i]=cnt[i]*fac[i]%Mod;
    rep(i,0,n)g[n-i]=ifac[i];
    f=f*g;
    rep(i,n+1,n+n)ans[i-n]=(ans[i-n]+1ll*f[i]*ifac[i-n])%Mod;
    memset(bin,0,sizeof(bin));
    memset(cnt,0,sizeof(cnt));
    rep(i,1,n)bin[c[i]]++;
    s=0;
    per(i,V,1){
        s+=bin[i];
        cnt[s]++;
    }
    f.a.clear(),g.a.clear();
    f.resize(n+1),g.resize(n+1);
    rep(i,1,n)f[i]=cnt[i]*fac[i]%Mod;
    rep(i,0,n)g[n-i]=ifac[i];
    f=f*g;
    rep(i,n+1,n+n)ans[i-n]=(ans[i-n]-1ll*f[i]*ifac[i-n]%Mod+Mod)%Mod;
    rep(i,1,n)write(ans[i]*inv(C(n,i))%Mod),putchar(' ');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF2038F. Alternative Platforms](https://codeforces.com/contest/2038/problem/F)

[my blog](https://yhddd123.github.io/post/2024-2025-icpc-nerc-southern-and-volga-russian-regional-contest-zuo-ti-ji-lu/)

### 思路

等于选 $k$ 个的总和 $ans_k$ 除以 $\binom{n}{k}$。

按 $(a_i,b_i)$ 降序，枚举最大值取到 $a_i$，枚举 $k$，要求在 $[1,i-1]$ 中选 $k-1$ 个且至少有一个 $b_j\le a_i$。容斥为减去所有都大于 $a_i$ 的情况，记 $num_i=\sum_{j\le i}[b_j> a_i]$，$ans_k=a_i\times(\binom{i-1}{k-1}-\binom{num_i}{k-1})$。

$a_i\times\binom{i-1}{k-1}$ 差卷积。记 $val_j=\sum a_i\times [num_i=j]$，$val_j\times\binom{j}{k-1}$ 差卷积。交换 $a_i,b_i$，把大于等于改为严格大于再做一遍。

### code

```cpp
int n;
pii a[maxn];
int num[maxn];
int lsh[maxn<<1],len;
int tree[maxn<<1];
#define lb(x) (x&(-x))
void upd(int x,int w){
	while(x<=len){tree[x]+=w,x+=lb(x);}
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){
	if(m<n||m<0||n<0)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int ans[maxn],val[maxn];
using ploy::mul;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i].fi=read(),lsh[++len]=a[i].fi;
	for(int i=1;i<=n;i++)a[i].se=read(),lsh[++len]=a[i].se;
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i].fi=lower_bound(lsh+1,lsh+len+1,a[i].fi)-lsh;
	for(int i=1;i<=n;i++)a[i].se=lower_bound(lsh+1,lsh+len+1,a[i].se)-lsh;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	sort(a+1,a+n+1);reverse(a+1,a+n+1);
	vector<int> f(n+1),g(n+1);
	f[0]=0;for(int i=1;i<=n;i++)f[i]=lsh[a[i].fi]*fac[i-1]%mod;
	for(int i=0;i<=n;i++)g[i]=inv[n-i];
	f=mul(f,g);
	for(int k=1;k<=n;k++)ans[k]=f[k+n]*inv[k-1]%mod;
	// for(int i=1;i<=n;i++){
		// for(int k=1;k<=n;k++)(ans[k]+=lsh[a[i].fi]*C(i-1,k-1))%=mod;
	// }
	for(int i=1;i<=n;i++){
		int num=que(len)-que(a[i].fi);
		if(a[i].se>a[i].fi)(val[num]+=lsh[a[i].fi])%=mod;
		upd(a[i].se,1);
	}
	f.resize(n),g.resize(n+1);
	for(int i=0;i<n;i++)f[i]=mod-val[i]*fac[i]%mod;
	for(int i=0;i<=n;i++)g[i]=inv[n-i];
	f=mul(f,g);
	for(int k=1;k<=n;k++)(ans[k]+=f[n+k-1]*inv[k-1])%=mod;
	// for(int i=0;i<n;i++){
		// for(int k=1;k<=n;k++)(ans[k]+=mod-val[i]*C(i,k-1)%mod)%=mod;
	// }
	for(int i=0;i<=n;i++)val[i]=0;
	for(int i=0;i<=len;i++)tree[i]=0;
	for(int i=1;i<=n;i++)swap(a[i].fi,a[i].se);
	sort(a+1,a+n+1);reverse(a+1,a+n+1);
	f.resize(n+1),g.resize(n+1);
	f[0]=0;for(int i=1;i<=n;i++)f[i]=lsh[a[i].fi]*fac[i-1]%mod;
	for(int i=0;i<=n;i++)g[i]=inv[n-i];
	f=mul(f,g);
	for(int k=1;k<=n;k++)(ans[k]+=f[k+n]*inv[k-1])%=mod;
	// for(int i=1;i<=n;i++){
		// for(int k=1;k<=n;k++)(ans[k]+=lsh[a[i].fi]*C(i-1,k-1))%=mod;
	// }
	for(int i=1;i<=n;i++){
		int num=que(len)-que(a[i].fi-1);
		if(a[i].se>=a[i].fi)(val[num]+=lsh[a[i].fi])%=mod;
		upd(a[i].se,1);
	}
	f.resize(n),g.resize(n+1);
	for(int i=0;i<n;i++)f[i]=mod-val[i]*fac[i]%mod;
	for(int i=0;i<=n;i++)g[i]=inv[n-i];
	f=mul(f,g);
	for(int k=1;k<=n;k++)(ans[k]+=f[n+k-1]*inv[k-1])%=mod;
	// for(int i=0;i<n;i++){
		// for(int k=1;k<=n;k++)(ans[k]+=mod-val[i]*C(i,k-1)%mod)%=mod;
	// }
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]*ksm(C(n,i))%mod);puts("");
}
```

[https://codeforces.com/contest/2038/submission/292187658](https://codeforces.com/contest/2038/submission/292187658)

---

## 作者：ZepX_D (赞：0)

$\max(\min\{v\},\min\{r\})$ 太难看了！！！

运用经典 trick: $\max(a,b)=a+b-\min(a,b)$，可得:
$$\max(\min\{v\},\min\{r\})=\min\{v\}+\min\{r\}-\min(\min\{v\},\min\{r\})$$

我们设 $a_i=\min(v_i,r_i)$，式子变成 $\min\{v\}+\min\{r\}-\min\{a\}$，这是三个相同的子问题。

现在问题转化为对一个序列求出所有大小为 $k$ 的子集的最小值之和，设其为 $f(k)$。

首先答案与序列的顺序无关，所以先把序列从小到大排序。然后钦定 $a_i$ 为集合最小值，我们要从其后面 $n_i$ 个数中选 $k-1$ 个，那么其贡献为 $a_i\times\binom{n-i}{k-1}$，即 $f(k)=\sum\limits_{i=1}^{n-k+1}a_i\binom{n-i}{k-1}$。

现在我们对 $1\sim n$ 中的每个 $k$ 都求一遍答案，时间复杂度为 $O(n^2)$，不能接受。

简单化一下式子，把组合数拆开：
$$f(k)=\frac{1}{(k-1)!}\left(\sum\limits_{i=1}^{n-k+1}a_i(n-i)!\times\frac{1}{(n-i-k+1)!}\right)$$
发现这个东西是卷积的形式，我们定义数组 $F$ 满足 $F_i=a_i(n-i)!$，$G$ 满足 $G_i=\frac{1}{i!}$，将两个数组卷积之后基本就能得到我们需要的答案了，我们现在求的是所有方案的总和，最后除以一个方案数即可。

时间复杂度 $O(n\log n)$。

---

## 作者：happybob (赞：0)

题意：

给定两个长度为 $n$ 的非负整数序列 $a_1,a_2,\cdots,a_n$ 与 $b_1,b_2,\cdots,b_n$，对于一个 $\{1,2,\cdots,n\}$ 的子集 $S$，定义其分数 $c(S)=\max(\min \limits_{i \in S} a_i, \min \limits_{i \in S} b_i)$。对于 $k=1,2,\cdots,n$，求所有大小为 $k$ 的子集分数期望，对 $998244353$ 取模。

$1 \leq n \leq 2 \times 10^5$，$0 \leq a_i, b_i \leq 10^6$，时限 $2$ 秒。

解法：

首先对于值钦定一个顺序，值相等按照下标排。这样序列中不存在相等的数。

先考虑暴力怎么做。

假设较大的最小值取在 $a$ 中，在 $b$ 中的情况交换 $a,b$ 再做一次就行。

枚举对答案产生贡献的最小值 $a_i$，那么其余在集合内的数，其 $a$ 值必须严格大于 $a_i$。记有 $c$ 个位置符合条件，则方案数为 $\dbinom{c}{k-1}$，但是可能存在某些选法使得最大值在 $b$ 那边。再求出有多少 $a_j>a_i,b_j>b_i$ 同时成立，记为 $nc$，此时只选 $nc$ 内的数会让最大值在 $b$ 中取到，所以贡献为 $-\dbinom{nc}{k-1}$，所以答案为 $\sum \limits_{i=1}^n a_i \left(\dbinom{c_i}{k-1}-\dbinom{nc_i}{k-1}\right)$。

$c_i$ 和 $nc_i$ 都是容易求的。具体的，求 $c$ 只需要排序一遍，求 $nc$ 只需要维护树状数组或平衡树。

现在对于固定的 $k$，我们可以做到 $O(n)$，所以总复杂度 $O(n^2)$，无法通过。考虑如何优化。首先同时计算两个组合数没意义，这两个组合数形式相同，不妨考虑我们需要计算 $\sum \limits_{i=1}^n a_i \dbinom{c_i}{k-1}$，现在 $k$ 增加 $1$，并不容易直接动态维护值。但是考虑直接将组合数拆开，结果为 $\sum \limits_{i=1}^n a_i \dfrac{c_i!}{(k-1)!(c_i-(k-1))!}$。$\dfrac{1}{(k-1)!}$ 扔到前面，变成 $\dfrac{1}{(k-1)!}\sum \limits_{i=1}^n a_i \dfrac{c_i!}{(c_i-(k-1))!}$。进一步地，$c_i - (c_i-(k-1)) = k-1$，所以这个东西可以卷积优化。对于每个 $c_i$ 求 $a_i$ 之和，构造多项式 $F(x) = \sum s_i i!x^i$ 与 $G(x) = \sum \limits \dfrac{1}{i!}x^i$，然后 NTT 即可。注意这里的卷积是下标减，取反后偏移即可。时间复杂度 $O(n \log n)$，但是你还要对 $nc$ 做一次，然后再对 $b$ 做一次，总共 $4$ 次，所以轻微卡常。

[Submission Link.](https://codeforces.com/contest/2038/submission/292196419)

---

