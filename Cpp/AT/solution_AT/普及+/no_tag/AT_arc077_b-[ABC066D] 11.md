# [ABC066D] 11

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc066/tasks/arc077_b

$ 1,...,n $ の $ n $ 個の整数からなる長さ $ n+1 $ の数列 $ a_1,a_2,...,a_{n+1} $ が与えられます。 この数列には $ 1,...,n $ のどの整数もかならず $ 1 $ 回以上出現することが分かっています。

$ k=1,...,n+1 $ のそれぞれについて、与えられた数列の長さ $ k $ の（連続とは限らない）部分列の個数を求め、 $ 10^9+7 $ で割ったあまりを出力して下さい。

## 说明/提示

### 注意

- $ 2 $ つの部分列が数列として同じであれば、元の数列での位置が異なっていたとしても、$ 1 $ 通りと数えます。
- 数列 $ a $ の長さ $ k $ の部分列とは、$ a $ の要素のうち $ k $ 個を選んで、 それらを順番を変えずに取り出して並べた数列のことを指します。 例えば、数列 $ 1,2,3,4,5 $ の長さ $ 3 $ の部分列には、 $ 1,3,5 $ や $ 1,2,3 $ などがあります。 一方で、$ 3,1,2 $ や $ 1,10,100 $ はこの数列の部分列ではありません。

### 制約

- $ 1\ \leq\ n\ \leq\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ n $
- $ 1,...,n $ のどの整数も必ず数列に出現する。
- $ n,a_i $ は整数である。

### Sample Explanation 1

長さ $ 1 $ の部分列は $ 1 $、$ 2 $、$ 3 $ の $ 3 $ 通りです。 長さ $ 2 $ の部分列は $ 1,1 $、$ 1,2 $、$ 1,3 $、$ 2,1 $、$ 2,3 $ の $ 5 $ 通りです。 長さ $ 3 $ の部分列は $ 1,1,3 $、$ 1,2,1 $、$ 1,2,3 $、$ 2,1,3 $ の $ 4 $ 通りです。 長さ $ 4 $ の部分列は $ 1,2,1,3 $ の $ 1 $ 通りです。

### Sample Explanation 2

長さ $ 1 $ の部分列は $ 1 $ の $ 1 $ 通りです。 長さ $ 2 $ の部分列は $ 1,1 $ の $ 1 $ 通りです。

### Sample Explanation 3

$ 10^9+7 $ で割ったあまりを出力することに注意して下さい。

## 样例 #1

### 输入

```
3
1 2 1 3```

### 输出

```
3
5
4
1```

## 样例 #2

### 输入

```
1
1 1```

### 输出

```
1
1```

## 样例 #3

### 输入

```
32
29 19 7 10 26 32 27 4 11 20 2 8 16 23 5 14 6 12 17 22 18 30 28 24 15 1 25 3 13 21 19 31 9```

### 输出

```
32
525
5453
40919
237336
1107568
4272048
13884156
38567100
92561040
193536720
354817320
573166440
818809200
37158313
166803103
166803103
37158313
818809200
573166440
354817320
193536720
92561040
38567100
13884156
4272048
1107568
237336
40920
5456
528
33
1```

# 题解

## 作者：Buried_Dream (赞：2)

组合题。

因为只有一个重复的数字，那就好做了。

先用桶来把这个重复的数字找到，我们考虑容斥，用总的方案数减去不合法的方案数即可。

总的方案数显然是 $C_{n+1}^{k}$。

什么时候子序列会重复。

![](https://cdn.luogu.com.cn/upload/image_hosting/lmu4xsd7.png)

左边的红色线是重复的数字第一次出现的位置，右边是第二次出现的位置。

出现重复的序列当且仅当选了左边的一部分，右边的一部分加上中间两个中的一个。

所以重复的方案数为 $C_{(l-1)+(n+1-r)}^{k}$。

最终的答案为 $C_{n+1}^{k} - C_{(l-1)+(n+1-r)}^{k}$。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
#define int ll
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int Mod = 1e9 + 7;

inline int read() {
    int res = 0, f = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) f |= (ch == '-');
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch - '0');
    return f ? - res : res;
}

inline int ksm(int a, int b) {
	int base = a, res = 1;
	while(b) {
		if(b & 1) res = (res * base) % Mod;
		base = (base * base) % Mod, b >>= 1;
	} return res % Mod;
}

int fac[N], a[N], t[N];
int num, l[N], r[N];

inline int C(int n, int m) {
	if(n < m) return 0; 
	return ( (fac[n] * ksm (fac[n - m], Mod - 2)) % Mod * ksm (fac[m], Mod - 2) ) % Mod;
}

signed main() {
	int n = read();
	for(int i = 1; i <= n + 1; i++) {
		a[i] = read(), t[a[i]]++;
		if(t[a[i]] == 1) l[a[i]] = i;
		if(t[a[i]] == 2) r[a[i]] = i, num = a[i];
	}
	fac[0] = 1;
	for(int i = 1; i <= n + 10; i++) fac[i] = (fac[i - 1] * i) % Mod; 
	for(int k = 1; k <= n + 1; k++)
		std::cout << (C(n + 1, k) - C(l[num] + n - r[num], k - 1) + Mod) % Mod, putchar('\n');
	return 0;
}
```

---

## 作者：zplqwq (赞：2)

算是排列组合基础题。

首先题目有个隐藏条件，即只有一个重复的数。

首先很明显，假设我们不考虑重复的话，答案为：
$C_{k}^{n+1}$

那么我们只需算出重复的，两者相减即可。

那么我们记录一下这个重复的数字第一次和最后一次出现的位置，设为 $l,r$ 。

那么，显然在 $l,r$ 之间的都是无解的，即重复的。

那么问题就变成了，在 $[1,l-1]$ 和 $[id+1,r]$ 中选出 $k-1$ 个数。

这个直接套组合数，就是 $C_{k-1}^{l-1+n+1-id-1}$ 。

所以答案就是$C_{k}^{n+1}-C_{k-1}^{l-1+n+1-id-1}$ 。




---

## 作者：Krimson (赞：2)

刚开始没看到是$n+1$个元素,还在大力推DP式子,结果发现是诈骗...  
一共$n+1$个元素,其中保证$[1,n]$中的元素个数至少有一个,不就是只有一个重复的数吗?  
开个桶暴力把这个数找出来,然后来推一下答案  
设$res$表示这个数第一次出现的位置,$id$为这个数第二次出现的位置,要从中选长度为$k$的子序列  
如果不考虑重复的情况,答案应该是$C^{n+1}_{k}$  
然后可以发现重复的序列中一定要满足选过这个重复的数,然后其它选的数的位置不可能在$[res,id]$之间,否则不满足子序列了,所以就相当于在$res$前和在$id$后的数中选$k-1$个的方案数  
所以多计算的方案数就是$C^{(res-1)+(n+1-id+1)}_{k-1}$  
最后不同的方案数就是$C^{n+1}_{k}-C^{(res-1)+(n+1-id+1)}_{k-1}$  
代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
const int MAXN=1e5+7;
const ll mod=1e9+7;
int bucket[MAXN];
int id,n,res;
il ll ksm(ll d,ll tim){
    ll rest=1;
    while(tim){
        if(tim&1) rest=rest*d%mod;
        d=d*d%mod;
        tim>>=1;
    }
    return rest;
}
ll jc[MAXN];
void init(int n){
    jc[0]=1,inv[0]=1;
    for(ri i=1;i<=n;++i){
        jc[i]=i*jc[i-1]%mod;
    }
}
il ll C(ll x,ll y){
    if(x<y) return 0;
    return jc[x]*ksm(jc[y]*jc[x-y]%mod,mod-2)%mod;
}
int main(){
    n=read();
    for(ri i=1;i<=n+1;++i){
        int x=read();
        if(bucket[x]){
            res=bucket[x];
            id=i;
            break;
        }
        bucket[x]=i;
    }
    init(n+1);
    for(ri i=1;i<=n+1;++i){
        print((C(n+1,i)-C(res+n-id,i-1)+mod)%mod);
    }
    return 0;
}
```


---

## 作者：Cloud_Umbrella (赞：1)

乍一看，是道数学题。细一想，是道排列组合。

## 分析

题目明确地说了，$[1,n]$ 中每个数至少出现一次，而一共有 $n+1$ 个数，说明只有一个数字重复。如若没有重复，答案显然是 $\large{C^{k}_{n+1}}$。而现在有重复的数字，利用容斥思想，用总的减去重复的，不就是正确答案了吗？

我们用 $start$ 表示重复数字第一次出现的位置，用 $last$ 表示重复数字第二次出现的位置（也可以说是最后一次），那么重复计算的子序列个数就是 $\large{C^{k-1}_{start+n-last-1}}$，相减可得答案。

在写排列组合函数的时候，是要取模的，所以相减可能会得到负数，但答案不可能是负数，所以应该先加上模数再模。

因为数据范围的原因，肯定要用快速幂。代码细节还挺多的。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,M=1e9+7;
int n,f[N],fact[N];//fact数组用于存阶乘

int Fpower(int x,int y){//快速幂
	int k=x,ans=1;
	while(y){
		if(y&1) ans=ans*k%M;
		k=k*k%M;
		y>>=1;
	}
	return ans;
}

int C(int x,int y){
	if(x<=0 || y<=0 || x<y) return 0;//不特判会出错
	return fact[x]*Fpower(fact[x-y]*fact[y]%M,M-2)%M;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	n++;
	int start,last;//分别表示重复数字第一和第二次出现的位置
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(f[x]){//注意，要先判断
    		start=f[x];//f[x]存的是x第一次出现的位置
    		last=i;
		}
		f[x]=i;//用于存位置
	}
	fact[0]=1;
	cout<<n-1<<"\n";//要先输出，否则会错！
	for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%M;//存下阶乘
    for(int i=2;i<=n;i++){
    	int ans=C(n,i)-C(start+n-last-1,i-1);
    	ans=(ans+M)%M;//避免出现负数
    	cout<<ans<<"\n";
    }
    return 0;//好习惯伴终生
}


```
 

---

## 作者：Hope888 (赞：1)

# 思路
既然有 $n+1$ 个数，且 $[1,n]$ 都出现过，那么有且仅有 $1$ 个数重复。

如果不考虑重复，那么显然共有 $C^{n+1}_k$ 种方案，我们只需删除掉其中重复的即可。

令 $l,r$ 为重复数字的第一次和最后一次出现的位置则。

当选择了下标 $<l$ 的数和下标 $>r$ 的数和 $l,r$ 中一个数时会出现重复的序列，则选了 $k-1$ 个数。

则重复的序列一共有：
$$C^{(l-1)+(n+1-r)}_{k-1}$$

最终的答案为：
$$C^{n+1}_k-C^{(l-1)+(n+1-r)}_{k-1}$$

过程中需要使用逆元，我在求组合数的函数 `C` 中使用了费马小定理求逆元。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7,MAXN=1e6+5;
int n,a[MAXN],tong[MAXN],fac[MAXN],l,r;
int fastpow(int a,int b)
{
	int base=a,sum=1,temp=b;
	while(b>0)
	{
		if(b&1)sum*=base;
		base*=base;
		b>>=1;
        sum%=MOD;
        base%=MOD;
	}
	return sum;
}
int C(int n, int m)
{
	if(n<m)return 0; 
	return((fac[n]*fastpow(fac[n-m],MOD-2))%MOD*fastpow(fac[m],MOD-2))%MOD;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n+1;i++)
	{
		cin>>a[i];
		if(tong[a[i]])//重复的数
		{
			l=tong[a[i]];
			r=i;
			break;
		}
		tong[a[i]]=i;
	}
	fac[0]=1;
	for(int i=1;i<=n+114514;i++)fac[i]=fac[i-1]*i%MOD;//预处理阶乘 
	for(int k=1;k<=n+1;k++)cout<<(C(n+1,k)-C(l+n-r,k-1)+MOD)%MOD<<endl;
	return 0;
}
```

---

## 作者：火车司机 (赞：1)

## 简要分析

一共 $n+1$ 个数， $[1,n]$ 每个数至少出现一次，很显然只会有一个重复的数

先找出这个重复的数，考虑答案应该怎么算

如果我们不考虑重复的情况，显然答案应该为 $C^{n+1}_{k}$

再把重复的序列容斥减掉

当重复的数从左边到右边时，只有它们俩中间的数与它们的相对位置会发生变化

所以重复的序列个数 $=$ 重复的数第一次出现之前 $+$ 第二次出现之后的所有数中选出 $k-1$ 个

因此答案为 $C^{n+1}_{k}-C^{l-1+n+1-r+1}_{k-1}$

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 100005
using namespace std;
const int P = 1e9 + 7;
int n, l, r, fac[N], inv[N], cnt[N];
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
inline int pwr(int x, int k)
{
	ri t = 1;
	for (; k; k >>= 1, x = x * x % P)
		if (k & 1)
			t = t * x % P;
	return t;
}
inline int C(int n, int m)
{
	if (n < m)
		return 0;
	return fac[n] * inv[m] % P * inv[n - m] % P;
}
inline int dec(int a, int b)
{
	return (a -= b) < 0 ? a + P : a;
}
signed main()
{
	read(n), ++n, fac[0] = 1;
	for (ri i = 1, x; i <= n; ++i)
	{
		read(x);
		if (cnt[x])
		{
			l = cnt[x], r = i;
			break;
		}
		cnt[x] = i;
	}
	for (ri i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i % P;
	inv[n] = pwr(fac[n], P - 2);
	for (ri i = n; i; --i)
		inv[i - 1] = inv[i] * i % P;
	for (ri i = 1; i <= n; ++i)
		print(dec(C(n, i), C(n - r + l - 1, i - 1))), puts("");
	return 0;
}
```


---

## 作者：ycy1124 (赞：0)

### 题意
有一个长度为 $n+1$ 的序列中所有的数都在 $1\sim n$ 之间且所有数都出现了至少一次。试分别求出长度为 $1\sim n+1$ 的不同子序列个数。
### 思路
不难发现只有一个数出现了 $2$ 次。我们求方案的时候只需要考虑这两个相同的数所带来的重复的子序列即可。考虑什么时候会有重复方案，我们设左边的相同数在 $l$ 位置上，右边的相同数在 $r$ 位置上。当我们的两种方案分别选择了这两个相同数的一个，且其余数字选在了 $l$ 左侧以及 $r$ 右侧那么这两个方案就是重复的。到这里方案就很好算了，对于长度为 $i$ 的，它的答案为 $\dbinom{n+1}{i}-\dbinom{n+1-r+l-1}{i-1}$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define md 1000000007
using namespace std;
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(!(ch>='0'&&ch<='9'))
		ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=getchar();
	return x*f;
}
inline void write(register int x){
    (x>9)?write(x/10):void();
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
int n,sum[100005],las[100005],inv[100005],a,b;
inline int power(int w){
    int qwq=md-2,base=w,Sum=1;
    while(qwq){
        (qwq&1)?Sum*=base,Sum%=md:qwq;
        qwq>>=1;
        base*=base;
        base%=md;
    }
    return Sum;
}
inline void getinv(int n){
	inv[0]=1;
	for(int i=1;i<=n;i++){
		inv[i]=power(sum[i]);
	}
}
inline void getsum(int n){
	sum[0]=1;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]*i%md;
	}
}
inline int C(int N,int M){
	if(N<M){
		return 0;
	}
	return sum[N]*inv[N-M]%md*inv[M]%md;
}
signed main(){
	n=read();
	getsum(n+1);//预处理前缀和，逆元
	getinv(n+1);
	for(int i=1;i<=n+1;i++){
		int w=read();
		if(las[w]){//找到那个相同的数
			a=las[w],b=i;
		}
		else{
			las[w]=i;
		}
	}
	for(int i=1;i<=n+1;i++){//求答案
		int ans=(C(n+1,i)-C(a-1+n-b+1,i-1)+md)%md;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

### 思路

组合数学题。

题目说有 $n+1$ 个数且 $[1,n]$ 都出现过，则只有 $1$ 个数重复。如果不算重复，则方案为 $\large C_{k}^{n+1}$。接着我们考虑容斥

我们设这个重复的数字第一次为 $l$，最后一次出现的位置为 $r$。则 $l \sim r$ 都无解，那么重复计算的子序列个数就是 $\large {C_{k-1}^{l+n-i-1}}$。答案相减即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
int n, a[N], k, vis[N];
int fac[N], inv[N];
int ksm(int a, int b) 
{
	int res = 1;
	for(; b; b >>= 1) 
	{
		if(b & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}
int C(int x, int y) 
{
	if(x < y) return 0;
	return fac[x] * inv[y] % MOD * inv[x - y] % MOD;
}
void init()
{
	fac[0] = inv[0] = 1;
	rep(i, 1, n)
	{
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = ksm(fac[i], MOD - 2);
	}
}
main() 
{
	scanf("%lld", &n); ++ n; init();
	rep(i, 1, n)
	{
		scanf("%lld", &a[i]);
		if(!vis[a[i]]) vis[a[i]] = i;
		else k = i - vis[a[i]] + 1;
	}
	rep(i, 1, n)
	{
		int ans = C(n, i) % MOD;
		int cnt = C(n - k, i - 1) % MOD;
		printf("%lld\n", (ans + MOD - cnt) % MOD);
	}
}
```

---

## 作者：Xu__ (赞：0)

题目链接：[AT2649 [ARC077B] 11](https://www.luogu.com.cn/problem/AT2649)
#### 题目概括
- 一个长度为 $n$ 的数列 $A$ 中 $[1,n]$ 的每一个数字都至少出现了一次，对每个 $k(1\le k \le n)$，询问长度为 $k$ 的子序列个数。
#### 题目分析
先上图

![](https://z3.ax1x.com/2021/10/16/5GA9aj.png)

（其中 $\texttt{First}$ 和 $\texttt{Second}$ 表示重复出现的数字在数列中的位置）



很容易发现正向考虑很难考虑到所有情况，所以可以反过来考虑，使用子序列总数减去重复的子序列个数。



从全部 $n + 1$ 个数中选择 $k$ 个数，总共 $\binom{n+1}{k}$ 个子序列。


![](https://z3.ax1x.com/2021/10/16/5GEFTH.png)
如上图所示，如果在一种子序列中所有元素只灰框圈出的部分，则这个子序列一定会被计算 $\texttt{2}$ 次，需要从总数中减去。这一部分子序列的数量为：
$$
\sum_{r=0}^{k-1}\binom{First-1}{r}\binom{n+1-Second}{k-1-r}=\binom{First-1+n+1-Second}{k-1}
$$
所以答案即为
$$
\binom{n+1}{k}-\binom{First+n-Second}{k-1}
$$
以上算法一次求解的时间复杂度为 $O(\log (1e9+7))$。

**注意，要注意取模后两数相减导致的负数情况。**

---------------------------


#### 组合数的求法
由于 $n$ 的数据范围很大，直接使用组合数的递推式无法在规定时间内求解，所以可以使用组合数的原始式子结合逆元求解即可。
$$
\binom{n}{m}=\frac{n!}{m!(n-m)!}=n!\times[m!(n-m)!]^{-1}=n!\times[m!(n-m)!]^{1e9+5}
$$


#### 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
#define Efor(xx, yy) for(int xx = Head[yy]; xx; xx = Next[xx])
#define Lfor(xx, yy, zz, xyz) for(int xx = yy; xx <= zz; xx += xyz)
#define Rfor(xx, yy, zz, xyz) for(int xx = yy; xx >= zz; xx -= xyz)
using namespace std;
const int N = 1e6 + 16, Mod = 1e9 + 7;
int n, First, Second, A[N], Xor, JC[N], T[N];
int C(int, int);
int NY(int);
int F_Pow(int, int);
signed main()
{
#ifdef FIO
    freopen("D:/VS Code/In.in", "r", stdin);
    freopen("D:/VS Code/Out.out", "w", stdout);
#endif
	JC[0] = 1;
	cin >> n;
	Lfor (i, 1, n + 1, 1) cin >> A[i], T[A[i]] ? Xor = A[i] : T[A[i]] = 1, JC[i] = JC[i - 1] * i % Mod; // 输入 and 处理重复出现的数字 and 计算阶乘
	Lfor (i, 1, n + 1, 1)
	{
		if (A[i] == Xor)
		{
			if (First) Second = i;
			else First = i;
		}
	}
	Lfor (k, 1, n + 1, 1)
		cout << (C(n + 1, k) - C(First - 1 + n + 1 - Second, k - 1) + Mod) % Mod << "\n"; // 注意取模后的负数问题
	
    return 0;
}

int C(int n, int m)
{
	return n >= m ? JC[n] * NY(JC[m] * JC[n - m]) % Mod : 0;
}

int NY(int x) { return F_Pow(x % Mod, Mod - 2); } // 求逆元

int F_Pow(int a, int b) // 快速幂
{
	int Ans = 1;
	while (b)
	{
		if (b & 1) Ans = (Ans * a) % Mod;
		a = (a * a) % Mod;
		b >>= 1;
	}
	return Ans;
}


```


---

