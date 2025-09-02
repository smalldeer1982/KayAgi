# [ABC383D] 9 Divisors

## 题目描述

找出不大于 $N$ 且恰好有 $9$ 个因数的正整数的个数。

## 说明/提示

- $1 \leq N \leq 4 \times 10^{12}$

- 所有输入值均为整数。

样例一解释：

三个正整数 $36,100,196$ 满足条件。

## 样例 #1

### 输入

```
200```

### 输出

```
3```

## 样例 #2

### 输入

```
4000000000000```

### 输出

```
407073```

# 题解

## 作者：da_ke (赞：7)

# AT_abc383_d [ABC383D] 9 Divisors

题意：求 $N$ 以内恰有 $9$ 个因子的数的个数。

设 $n\in[1,N]$。一般的，一个数的因子是**对称的**，这意味着 $a$ 是 $n$ 的因子，$\dfrac{n}{a}$ 也是 $n$ 的因子。而 $n$ 有 $9$ 个因子，说明 $n$ 是**完全平方数**。

设 $n$ 分解质因数的结果为 $\prod\limits_{i=1}^{k}p_i^{a_i}$。则 $n$ 的因子个数为 $\prod\limits_{i=1}^{k}(a_i+1)$。

所以我们知道 $n$ 要满足条件，必定满足以下条件之一：

- $n$ 只有质因数 $a$，且 $n=a^8$。
- $n$ 只有两个质因数 $a,b$，且 $n=a^2b^2$。

对 $\sqrt{N}$ 以内的数埃筛，筛出所有质数。根据单调性，用双指针求出所有质数 $(a,b)$ 满足 $n=a^2b^2$。再暴力试出满足 $n=a^8$ 的 $a$ 的个数。

时间复杂度 $O(\sqrt N\ln\ln\sqrt N)$。

```cpp
#include <bits/stdc++.h>

typedef long long ll;
#define rep(i,l,r) for(ll i=(l);i<=(r);i++)
#define fdn(i,r,l) for(ll i=(r);i>=(l);i--)
#define pii pair<int,int>
using namespace std;

typedef double db;
typedef __int128 i128;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
std::mt19937_64 rnd64(std::chrono::steady_clock::now().time_since_epoch().count());

ll slow_power(ll a)
{
    ll ans=1;rep(i,1,8) ans*=a;return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    ll N;
    cin>>N;
    ll M=sqrt(1.0*N+0.5);
    ll cnt=0;
    vector<ll> prime(M+1);
    vector<bool> is_prime(M+2,1);
    is_prime[0] = is_prime[1] = false;
    rep(i,2,M)
        if (is_prime[i])
            for (ll j = i * i; j <= M; j += i) is_prime[j] = false;
    rep(i,2,M) if(is_prime[i]) prime[++cnt]=i;
    ll ans=0;
    ll j=cnt;
    rep(i,1,cnt)
    {
        while(prime[i]*prime[i]*prime[j]*prime[j]>N&&j>i) j--;
        ans+=max(0ll,j-i);
    }
    rep(i,1,cnt)
        if(slow_power(prime[i])<=N) ans++;
        else break;
    cout<<ans<<endl;
}
```

---

## 作者：xyx404 (赞：6)

## 思路：

一个数若要恰好有九个约数，它必须是以下两种形式之一：
1. $p^8$，其中 $p$ 是一个质数。
2. $p^2 \cdot q^2$，其中 $p$ 和 $q$ 是不同的质数。

为什么是这两种形式，原因如下。 

一个数的约数个数可以通过其质因数分解来确定。假设有一个正整数 $n$，它的质因数分解为：

$$ n = p_1^{e_1} \cdot p_2^{e_2} \cdot \ldots \cdot p_k^{e_k} $$

其中 $p_1, p_2, \ldots, p_k$ 是不同的质数，而 $e_1, e_2, \ldots, e_k$ 是这些质数在 $n$ 的质因数分解中的指数。

根据约数个数定理，$n$ 的约数个数 $d(n)$ 可以通过下面的公式计算得出：

$$ d(n) = (e_1 + 1)(e_2 + 1)\dots(e_k + 1) $$

要让 $n$ 恰好有九个约数，我们需要找到一种方法使得上述乘积等于 $9$。由于 $9$ 可以被分解为两个因数的乘积，即 $9 = 9 \times 1 = 3 \times 3$，因此我们可以得出两种可能的情况：

1. 当我们有一个质数的八次幂时，比如 $p^8$，这时只有一个质因子，其指数加一等于 $9$，所以它有 $8 + 1 = 9$ 个约数。
2. 当我们有两个不同质数的平方相乘时，比如 $p^2 \cdot q^2$，这时有两个质因子，每个的指数加一都等于 $3$，所以它们一起产生 $(2 + 1)(2 + 1) = 3 \times 3 = 9$ 个约数。

这两种情况是能使一个数恰好有九个约数的形式，因为除此之外没有其他方法可以将 $9$ 分解为大于 $1$ 的整数之积。这就是为什么我们要找的数必须是 $p^8$ 或者 $p^2 \cdot q^2$ 的形式。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL n;
vector<bool>is_prime;
vector<LL>primes;
void hs1(LL lim){
	is_prime.assign(lim+1,1);
	is_prime[0]=is_prime[1]=0;
	for(LL i=2;i*i<=lim;i++){
		if(is_prime[i]){
			for(LL j=i*i;j<=lim;j+=i)is_prime[j]=0;
		}
	}
	for(LL i=2;i<=lim;i++)if(is_prime[i])primes.push_back(i);
}
LL solve(LL n){
	LL ans=0;
	int len=primes.size();
	for(LL i=0;i<len;i++){
		LL num=primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i];
		if(num>n)break;
		ans++;
	}
	for(LL i=0;i<len;i++){
		LL a=primes[i]*primes[i];
		if(a*a>n)break;
		for(LL j=i+1;j<len;j++){
			LL num=a*primes[j]*primes[j];
			if(num>n)break;
			ans++;
		}
	}
	return ans;
}
int main(){
	cin>>n;
	hs1(static_cast<LL>(sqrt(n)));
	cout<<solve(n)<<"\n";
	return 0;
}


```

---

## 作者：PUTONGDEYITIREN (赞：4)

# 思路
### 题目分析
我们先来看一下题面，他叫我们求在 $n$ 以内有 $9$ 个正因子的正整数。听到因子个数，我相信你一定想起了自己在小升初时做的那些奥数题，也想起了那个求因数个数的公式，那就让我们来一起回忆一下。
### 公式
设 $m$ 的因数个数为 $t$，把 $m$ 做质因数分解后分解为 $p_1$ 到 $p_k$，则 $t=\prod_{i=1}^k p_i+1$。
### 核心思路
听到这里，想信很多人已经懂了，这时候我们只需要分两种情况讨论。

一：吧 $9$ 分解成 $3 \times 3$，我们只用看在 $\sqrt{n}$ 之内有多少个数是由两个质数相乘得到的就行了。

二：吧 $9$ 分解成 $1 \times 9$，我们只用看在 $n$ 之内有多少个数是质数的八次方就行了。

质数这一点也非常简单，用一个线性筛筛出 $\sqrt{n}$ 内的质数就行了。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
bool p[10000001]={1,1};
long long prime[10000001],m,l,x[10000001],xx,ans,pp[10000001];
void ol(long long n){
	long long top=1;
	for(long long i=2;i<=n;i++){
		if(p[i]==0){
			prime[top++]=i;
		}
		for(long long j=1;j<=top&&i*prime[j]<=n;j++){
			p[i*prime[j]]=1;
			if(i%prime[j]==0){
				break;
			}
		}
	}
} 
int main(){
	cin>>xx;
	ol(2000005);
	for(int i=1;prime[i]<=sqrt(xx);i++){
		for(long long j=1;prime[i]*prime[j]<=sqrt(xx);j++){
			if(i!=j){
				if(pp[prime[i]*prime[j]]==0) ans++;
				pp[prime[i]*prime[j]]=1;
			} 
		}		
	}
	for(int i=1;prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]<=xx;i++){
		ans++;
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：Dream_poetry (赞：2)

### 题意：

求出从 $1$ 到 $n$ 中因子个数恰好是 $9$ 的数的个数。

### 思路：

突破点在于 $9$ 个因子这一部分。

显然我们可以发现结果必然是一个完全平方数。

在经过思考，我们可以发现这个完全平方数还是由两个质数相乘得到的。

思考路程如下：

设两个质数 $a,b$ 且 $a \ne b$，它们乘积的平方为所得完全平方数，即 $a^2b^2$。

此时有因子 $1,a,b,a^2,ab,b^2,a^2b,ab^2,a^2b^2$，恰好为 $9$。

可以证明惟有 $a,b$ 是不相等质数时有如上结论。

此外我们还需考虑八次方数，易证。

先用线性筛筛出所有质数，然后枚举即可。

由于极限情况下可以发现答案并不大，所以暴力即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int pd[2000005];
int ans[2000005];
int sum;
int cnt;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	pd[1]=1; 
	for(int i=2;i*i<=n;i++){
		if(!pd[i]){
			ans[++sum]=i;
		} 
		for(int j=1;j<=sum&&i*ans[j]<=sqrt(n);j++){
			pd[ans[j]*i]=1; 
			if(i%ans[j]==0){
				break;
			} 
		}
	}
	for (int i=1;i<=sum;i++){
		int val=ans[i];
		for (int j=2;j<=8;j++){
			val*=ans[i];
			if (val>n){
				val=0;
				break;
			}
		}
		if (val){
			cnt++;
		}
		for (int j=i+1;ans[j]*ans[i]<=sqrt(n) && j<=sum;j++){
			cnt++;
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：hjyowl (赞：2)

### 题目大意

给定 $n$，求 $n$ 以内，有多少个数恰好有 $9$ 个约数。

### 朴素思路

枚举每一个数，去看有多少个约数，时间复杂度 $\Theta(n^2)$。

### 稍加优化

枚举每一个数时，根据约数个数公式，可以对于每个数 $\Theta(\sqrt n)$ 求解。

这样，时间复杂度 $\Theta(n \sqrt n)$。

### 正解

观察约数和式子。

发现要想那一大堆相乘等于 $9$，要么是一个质数的 $8$ 次方，要么就是两个不同的质数的平方相乘。

对于质数的 $8$ 次方，我们只需要枚举直到那个质数的 $8$ 超过了 $n$，否则就答案加一。

对于两个质数的平方，类似，也是去暴力枚举两个质数，相乘超过了就停止，否则就加一。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
const int N = 5010;
char g[N][N];
bool st[N][N];
int main(){
	int n,m,k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			cin >> g[i][j];
		}
	}
	queue<pair<pair<int,int>,int>>q;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			if (g[i][j] == 'H'){
				q.push({{i,j},0});
				st[i][j] = 1;
			}
		}
	}
	while (q.size()){
		auto [t,stt] = q.front();
		q.pop();
		int x = t.first,y = t.second;
		if (stt >= k){
			continue;
		}
		for (int i = 0; i < 4; i ++ ){
			int gx = x + dx[i],gy = y + dy[i];
			if (gx >= 1 && gx <= n && gy >= 1 && gy <= m && !st[gx][gy] && g[gx][gy] != '#'){
				st[gx][gy] = 1;
				q.push({{gx,gy},stt + 1});
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 1; j <= m; j ++ ){
			if (st[i][j] && g[i][j] != '#'){
				res ++; 
			}
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：jinhangdong (赞：1)

首先普通的数的因数个数是偶数个的，只有完全平方数才会是奇数个的，于是我们就枚举完全平方数。先预处理欧拉筛用来分解质因子，然后再分解质因子，把对应的质因子个数加 $1$ 然后就可以计算因子个数了，因子个数就是把所有的质因子个数加 $1$ 再相乘。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,cnta[2000005],cnt,nxt[2000005],vis[2000005],p[2000005];
int main()
{
	for(int i=2;i<=2000005;++i)//欧拉筛预处理每个数的最小质因子
	{
		if(vis[i]==0) p[++cnt]=i,nxt[i]=i;
		for(int j=1;j<=cnt&&i*p[j]<=2000005;++j)
		{
			vis[i*p[j]]=1;
			nxt[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	}
	cin>>n;
	for(int i=1;i<=sqrt(n);++i)//枚举所有完全平方数
	{
		int x=i,l=2;
		long long s=1;
		while(x!=1)//分解质因子
		{
			cnta[nxt[x]]++;
			x/=nxt[x];
		}
		int y=i;
		while(y!=1)
		{
			s*=(cnta[nxt[y]]*2+1);//如果i有x个质因子是y，那么i*i就有2x个质因子是y
			cnta[nxt[y]]=0;//归0
			y/=nxt[y];
		}
		if(s==9) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括

给定一个整数 $N$，请你求出小于等于 $N$ 并所有因数个数为 $9$ 的数的个数。

## 思路分析

### 前置知识 - 因数个数定理

当一个数 $s_i = a_1^{k_1} \times a_2^{k_2} \times \dots \times a_n^{k_n}$ 时，它的因数有 $(k_1+1) \times (k_2+1) \times \dots \times (k_n+1)$ 个（$a_1,a_2,\dots,a_n$ 为质数）。

### 其证明

乘法原理，每个幂匹配其他的幂。

如 $12$ 的因数：$1,2,3,4,6,12$。

$12 = 2^2 \times 3^1$，$1 = 2^0 \times 3^0$，$2 = 2^1 \times 3^0$，$3 = 2^0 \times 3^1$，$4 = 2^2 \times 3^0$，$\dots$，以此类推。

### 解题思路

因为根据题意，$s_i$ 有 $9$ 个因数。

所以 $s_i$ 有两种情况：

- $s_i = a^8$ 时。

- $s_i = a_1^2 \times a_2^2$ 时（$a_1 \ne a_2$）。

所以接下来就好做了，先用线性筛筛一遍，再枚举质数。

## 代码解析

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
unsigned long long x,a,sum;
long long vis[3000010]={0},prime[100100],num=1;
void sunshine(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[num]=i;
			num++;
		}
		for(int j=1;j<=num&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
	cin>>x;
	sunshine(sqrt(x)+1);
	for(int i=1;i<num;i++){
		a=prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i];
		if(a<=x)sum++;
		else break;
	}
	for(int i=1;i<num;i++){
		int j;
		for(j=i+1;j<num;j++){
			a=prime[i]*prime[j]*prime[i]*prime[j];
			if(a<=x)sum++;
			else{
				break;//跳出这轮 
			}
		}
		if(j==i+1)break;//没有答案了 
	}
	cout<<sum;
	sjh0626s code;
}
```

---

## 作者：Cosine_Func (赞：1)

数学题。对 $9$ 分解因数得 $9=1\times 9$ 或 $9=3\times3$，因此分类讨论。

1. $n = p_1^8$，其中 $p_1$ 是一个质数。我们需要找出所有不大于 $N$ 的质数 $p_1$，使得 $p_1^8 \leq N$。这可以通过试除法或素数筛法来找出小于等于 $\sqrt[8]{N}$ 的所有质数，然后检查每个质数的 $8$ 次方是否小于等于 $N$。
3. $n = p_1^2 \times p_2^2$，其中 $p_1$ 和 $p_2$ 是两个不同的质数。我们需要找出所有不大于 $\sqrt{N}$ 的质数对 $(p_1, p_2)$，使得 $p_1^2 \cdot p_2^2 \leq N$。这同样可以通过素数筛法来找出小于等于 $\sqrt{N}$ 的所有质数，然后检查每对质数的平方乘积是否小于等于 $N$。

[参考代码](https://atcoder.jp/contests/abc383/submissions/60537443)

---

## 作者：Toorean (赞：1)

# 题意
给出 $n \le 4\times10^{12}$，求 $[1,n]$ 中所有**恰有** $9$ 个正因子的正整数的个数。

# 分析
由算术基本定理，设 $n=\prod\limits_{i=1}^{m}p^{\alpha_i}$，则 $n$ 的正因子个数为 $\prod\limits_{i=1}^m(\alpha_i+1)$。显然，当 $\alpha_i>0$ 时才会有贡献。故对于 $m$ 进行分类讨论。

- $m=1$，则 $\alpha_1=8$，即此时能够做出贡献的数为 $p^8$，其中 $p$ 为质数，且 $p^8\le n$.
- $m=2$，由于 $9$ 只由质因子 $3$ 构成，故 $\alpha_1=\alpha_2=2$。故只需t统计所有满足 $p_1^2\times p_2^2\le n$ 的质数 $p_1$ 与 $p_2$ 即可。
- $m\ge3$，由于 $9=3^2$，故无法将 $9$ 继续分解，所以此类形式的数对答案没有贡献。

注意到 $n\le 4\times10^{12}$，故结合两个情况得 $p_{\max}\le10^6$，显然易于预处理。对于情况 1，枚举所有满足条件的质数即可。对于情况 2，利用双指针统计答案即可。

# Code
```cpp
for (auto p : prime) if (qpow (p, 8) <= n) ++ ans; else break;
int j = prime.size () - 1;
for (int i = 0; i < j && i < prime.size (); i ++) {
    while (qpow (prime[i], 2) * qpow (prime[j], 2) > n) j --;
    if (j <= i) break ;
    ans += j - i;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
有两种情况，第一种是 $p^8$，第二种是 $p^2\times q^2$（$p$、$q$ 为质数），可以发现只需考虑 $\sqrt{N}$ 以内的质数就行。先筛出 $\sqrt{N}$ 以内的质数，情况一直接枚举，情况二可以二分或双指针，我用的二分。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
const int N=1e7+10,inf=1e15;
int n,ans,cnt,p[N];
bool isp[N];
void init(){ //埃筛
	for(int i=2;i<=n;++i)
		if(!isp[i]){
			p[++cnt]=i;
			for(int j=2;i*j<=n;++j) isp[i*j]=1;
		}
}
signed main(){
	cin>>n; n=sqrt(n); init();
	if(n==1) return cout<<0,0;
	for(int i=1;i<=cnt;++i) ans+=upper_bound(p+1,p+cnt+1,n/p[i])-p-1-(p[i]*p[i]<=n);
	ans/=2; //每对质数会被算两次
	for(int i=1;i<=n;++i)
		if(p[i]*p[i]*p[i]*p[i]<=n) ++ans;
		else break; //防止爆 long long
	cout<<ans;
	return 0;
}
```

---

## 作者：wht_1218 (赞：0)

赛时做法。

第一个有 $9$ 个正因数的数是 $36$，它的正因数有 $1,2,3,4,6,9,12,18,36$。不难发现除了 $6$，其他的因数两两相乘都是 $36$。而 $6\times 6$ 也是 $36$。

对于更大的例子也是如此。

这就是本题**第一种**数的规律：都是平方数。

$\sqrt{36}=6$，发现 $6$ 的因数有 $1,2,3,6$。这其中质因数正好有 $2$ 个，$6^2$ 的因数就有 $1,2,3,2\times 2,36\div(2\times 2),2\times 3,3\times 3,36\div(3\times 3),6^2$。

设第 $i(1\le i \le 2)$ 个质因数为 $a_i$。则 $(a_1a_2)^2$ 的因数有 $1,a_1,a_2,a_1^2,(a_1a_2)^2\div(a_1^2),a_1a_2,a_2^2,(a_1a_2)^2\div(a_2^2),(a_1a_2)^2$。

这一种数可以使用素数筛法预处理 $\le \sqrt{10^{12}\times 4}$ 的质因数个数。

**第二种**数就是 $i^8$，此时这个数的因数有 $1,i,i^2,i^3,i^4,i^5,i^6,i^7,i^8$。

这一种数可以暴力枚举 $i$，注意 $i$ 要是素数，这里也可使用素数筛法优化。

关于素数筛法详见[这里](https://oi-wiki.org/math/number-theory/sieve/)。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+17;
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
//#define abs(x) (x>0?x:-x)
inline int abs(auto x){
	return x>0?x:-x;
}
#define imx INT_MAX
#define imn INT_MIN
#define lmx LLONG_MAX
#define lmn LLONG_MIN
#define nmx (N)
#define nmn (-N)
#define umap unordered_map
#define pii pair<int,int>
#define mset multiset

/**/
int cnt1[N],cnt2[N];
void init(){
	for(int i=2;i<=N-5;++i){
		if(!cnt1[i]&&!cnt2[i]){
			cnt1[i]=cnt2[i]=0;
			for(int j=i+i;j<=N-5;j+=i){
				if(cnt1[j]>0){
					cnt2[j]=i;
				}else cnt1[j]=i;
			}
		}
	}
}
int ans=0;
main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	init();
	for(int i=2;i*i*i*i*i*i*i*i<=n;++i){
		if(!cnt1[i])ans++;
	}
	for(int i=2;i*i<=n;++i){
		if(cnt1[i]*cnt2[i]==i)ans++;
	}cout<<ans;
    return 0;
}
```

---

## 作者：Dtw_ (赞：0)

# 题意
给定 $n$ 求不大于 $n$ 的数中满足因子个数为 $9$ 的数的数量。
# Solution
考虑因子数为 $9$，因子数是这样算的：把一个数质因数分解为 $p_1^{k_1}\times p_2^{k_2}\times \cdots \times p_n^{k_n}$ 那他的因子数为 $\prod _{i = 1} ^ n (k_i + 1)$。然后考虑把 $9$ 质因子分解为 $1,3,9$ 所以考虑要么有 $2$ 个 $2$ 次幂，要么有 $1$ 个 $8$ 次幂。

因为至少要有 $2$ 次幂，所以我们可以把 $\sqrt n$ 内的质数全跑出来，然后枚举第一个质数选啥，第二个质数一定单调，可以二分或者双指针。这样就知道了第一类情况的数量，然后考虑第二种情况直接枚举这个数是啥，然后 $\times$ 上 $8$ 次，看是否 $\leq n$ 就行了。

注意这个数很大，所以算的时候要开 `__int128`。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 4e6 + 10;

int m;

int p[N];

bool vis[N];

void prime(int n)
{
	for (int i = 2; i <= n; i++)
	{
		if (vis[i] == 0)
		{
			p[++m] = i;
			vis[i] = 1;
		}
		for (int j = 1; j <= m && i * p[j] <= n; j++)
		{
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	} 
}

signed main()
{
    fst
    // 要么有两个质因子且指数为 2
    // 要么有一个质因子指数为 8
    int n;
    cin >> n;
    prime(sqrt(n) + 10);
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int x = p[i] * p[i];
        int l = i + 1, r = m, res = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (x * p[mid] >= n) r = mid - 1;
            if ((__int128)x * p[mid] * p[mid] <= n) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        ans += max(0ll, res - i);
    }
    for (int i = 1; i <= m; i++)
    {
        __int128 x = 1;
        bool f = 1;
        for (int j = 1; j <= 8; j++)
        {
            x *= p[i];
            if (x > n) f = 0;
        }
        if (x <= n) ans += f;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

个人认为官方题解讲的不太细致，所以这篇题解我们来解决里面的问题。

首先，在官方题解说：我们很容易发现答案就是这样的式子：

设 $p$ 为单调递增的质数序列，$n$ 为其大小，$a=p_i$，$b=p_j$。

则答案为：
$$
\sum_{i = 1}^{n}[a^8 \le n] + \sum_{i = 1}^{n}\sum_{j = i  + 1}^{n}[a^2b^2 \le n]
$$
那为什么呢？

先来看前半部分，一个数是一个质数 $a$ 的 $8$ 次方，由于整数唯一分解定理，其所有因数就是 $1,a,a^2,a^3\dots a^8$，正好 $9$ 个。

再看后半部分，$a^2b^2$ 的全部因数有：$1,a,b,a^2,b^2,ab,a^2b,ab^2,a^2b^2$，也是 $9$ 个。

然后就好啦！注意不要溢出。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,  vis[1000005], p[1000005], cnt, ans;
void prime(){
    int len = 1e6;//筛 1e6 内的质数
	for(int i = 2; i <= len; i ++){
		if(!vis[i]){
			p[++ cnt] = i ;
		}
		for(int j = 1; p[j] * i <= len; j ++){
			vis[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
int main(){
    cin >> n;
    prime();
    for(int i = 1; i <= cnt; i ++){
        if(p[i] * p[i] * p[i] * p[i] > n) break;//两个式子的值都大于它，它爆了其它的也要爆
        if(p[i] <= 100 && p[i] * p[i] * p[i] * p[i] * p[i] * p[i] * p[i] * p[i] <= n){//p[i] > 100 可能会爆 long long
            ans ++;
        }
        for(int j = i + 1; j <= cnt; j ++){
            if(p[i] * p[i] * p[j] * p[j] <= n){
                ans ++;
            }
            else break;//大了就没必要找了
        }
    }
    cout << ans;
	return 0;
}
```

---

## 作者：11400F (赞：0)

### AT_ABC383_D 题解

我们知道，一个数的因数个数就是先把他拆分为 ${p_1}^{a_1}{p_2}^{a_2}\cdots{p_n}^{a_n}$（$p_1 \sim p_n$ 均为质数），然后他的质因数个数就是 $(a_1+1)(a_2+1) \cdots (a_n+1)$。

然后因为这个数有 $9$ 个质因数，而 $9 = 1 \times 9 = 3 \times 3$，所以这个数就只能是 $(p_x)^8$ 或是 $(p_x)^2 \times (p_y)^2$（$p_x \neq p_y$）。

枚举质数的 $8$ 次方是好写的，毕竟 $38^8$ 才刚刚超过 $4 \times 10^{12}$。

然后枚举两个不同质数的乘积的平方，因为 $(p_x)^2 \times (p_y)^2 \le 4\times10^{12}$，则 $p_x \times p_y \le 2 \times 10^6$。

我们可以对 $2\times 10^6$ 以下的质数打个质数表（这里用的是埃氏筛 + bitset），然后把所有是质数的数提取出来，设一共有 $lim$ 个质数。

我们维护两个指针，第一个指针 $i$ 从 $1 \sim lim$ 枚举，第二个指针 $j$ 维护的就是使 $p_i \times p_j \le \sqrt{n}$ 的最大的 $j$。这个 $j$ 因为随着 $i$ 的增大而减小，所以直接双指针扫一遍，遇到不符合的 $j$ 就让 $j$ 减 $1$，直到它符合。对于每一个 $i$，他对答案的贡献就是 $\max(j-i, 0)$。所以当 $j \le i$ 的时候就可以直接不扫了，`break` 掉。

最后的答案就是 $8$ 次方的情况的答案加上两个不同质数的乘积的平方的答案。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6+6;
bitset<N> isprime;
typedef long long ll;
ll n;
int lim = 2e6;
ll pri[N];
int prilen = 0;
void init(){
    for(int i=2;i<=lim;i++){
        if(!isprime[i]){
            pri[++prilen] = i;
            for(int j=i*2;j<=lim;j+=i){
                isprime[j] = 1;
            }
        }
    }
}
ll ans = 0;
ll get8pow(ll x){
    return x*x*x*x*x*x*x*x;
}
void bfpow8(){
    ll now = 2;
    while(get8pow(now) <= n){
        if(isprime[now]){
            now++;
            continue;
        }
        ans ++;
        now ++;
        
    }
}
void getprimerange(){
    ll rlim = sqrtl(n);
    int lpos = 1, rpos = prilen;
    for(;lpos<=rpos;lpos++){
        while(pri[lpos] * pri[rpos] > rlim && rpos >= 1){
            rpos --;
        }
        if(rpos <= lpos) break;
        ans += (rpos - lpos);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n;
    init();
    bfpow8();
    getprimerange();
    cout<<ans;
    return 0;
}
```

---

## 作者：HuangBarry (赞：0)

思路：数学。  
首先，我们有公式（$p_i$ 是质数）：
$$
n=\prod_{i=1}^kp_i^{a_i}=p_1^{a_1}\cdot p_2^{a_2}\dots p_k^{a_k}
$$
然后我们还有如何求一个数有多少个因数的公式，是由上公式推导下来的：
$$
f(n)=\prod_{i=1}^k(a_i+1)=(a_1+1)(a_2+1)\cdots(a_k+1)
$$
数学有点基础的同学们都知道，如果一个数的因数个数为奇数，那么这个数一定是完全平方数，因为 $n=因子*因子$ 所以因子是一对一对的，那么大部分情况因子数是偶数个，但是如果是完全平方数，$n=\sqrt n^2$ 就会有个 $\sqrt n$ 的单独的因子，并不是一对的，所以导致因子个数是奇数，所以满足题目要求的数一定是完全平方数。

经过数学推导，可得满足条件的数有两种情况：  
* $s=a^8$ 时，9 个因子分别是 $a^0,a^1,a^2\cdots a^8$。
* $s=a_1^2\cdot a_2^2(a_1\ne a_2)$ 时，9 个因子分别是：

$$ 
a_1^0\times a_2^0，
a_1^0\times a_2^1，
a_1^0\times a_2^2，
a_1^1\times a_2^0，
a_1^1\times a_2^1，
a_1^1\times a_2^2，
a_1^2\times a_2^0，
a_1^2\times a_2^1，
a_1^2\times a_2^2
$$
接下来就可实现代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define Made return
#define by 0
#define Barry +0
#define fre(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using ll=long long;
const int N=2e6+26;
ll n,ans=0;
vector<ll>primes;
bitset<N>bs(0);
int main(){
    //fre("name");
    cin>>n;
    for(ll i=2;i<=sqrt(n)+1;i++){//模版线性筛
        if(!bs[i])
            primes.push_back(i);
    	for(int j=0;j<primes.size()&&primes[j]*i<=sqrt(n)+1;j++){
            bs[primes[j]*i]=1;
            if(!(i%primes[j]))
            	break;
        }
    }
    int len=primes.size();
    for(int i=0;i<len;i++){//s=a^9的情况
        if(n>=primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i]*primes[i])
            ans++;
        else//若已经大于n那么后面不用找了
            break;
    }
    for(int i=0;i<len;i++){//s=a_1^2*a_2^2的情况
        int j;
        for(j=i+1;j<len;j++){
            if(primes[i]*primes[i]*primes[j]*primes[j]<=n)
                ans++;
        	else//d大于不用找了
            	break;
        }
        if(j==i+1)//后面肯定都是大于，不用找了
            break;
    }
    cout<<ans<<endl;
    Made by Barry;
}
```

---

## 作者：cyq32ent (赞：0)

### 因数个数定理
对于$n$的一个质因数分解

$$n=\prod_{i}p_i^{a_i}$$

$n$ 共有 $\prod_{i}(a_i+1)$ 个正因子。

### 题解
显然符合要求的数为以下两种之一：$(pq)^2$ 或 $p^8$，其中 $p$ 和 $q$ 为素数。两种都可以二分求出。复杂度 $\mathcal O(\sqrt{N})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int prime[2000110],cnt=0;
bool is_prime[2000110];

void Eratosthenes(int n) {
	is_prime[0]=is_prime[1]=0;
	for(int i=2;i<=n;++i)is_prime[i]=1;
	for(int i=2;i<=n;++i){
		if(is_prime[i]){
			prime[++cnt]=i;
			if(i*i<=n)for(int j=i*i;j<=n;j+=i)is_prime[j]=0; 
		}
	}
}int X[50],ct=0;
signed main(){
	int N;cin>>N;
	Eratosthenes(sqrt(N)+100);
	for(int i=1;i<=45;i++){
		if(!is_prime[i])continue;
		int l=1;
		for(int j=1;j<=8;j++)l*=(i);
		X[++ct]=l;
	}
	int k=sqrt((long double)N);long long ans=0;
	for(int i=1;prime[i]<=k&&i<=cnt;i++){
		int up=min(k/prime[i],prime[i]-1);
		int a1=(upper_bound(prime+1,prime+1+cnt,up)-1-prime);
		ans+=a1;
		
	}
	cout<<ans+(upper_bound(X+1,X+1+ct,N)-X-1)<<endl;
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

好久没见过一句话的题目了。

## 题目大意

给定正整数 $N$，求出不大于 $N$ 且刚好有 $9$ 个正因子的正整数个数，数据范围 $N\le 4\times 10^{12}$。

## 解题思路

数学题，首先有一个定理。若一个正整数 $M$ 被质因数分解为 $p_1^{f_1}\times p_2^{f_2}\times \cdots \times p_k^{f_k}$，则其含有的正因子个数即为 $(f_1+1)(f_2+1)\cdots (f_k+1)$（组合数学可得证）。于是在本题中为了使正因子个数为 $9$，只有两种可能：$f_1=8,f_{2\sim k}=0$ 或 $f_1=f_2=2,f_{3\sim k}=0$。因此对于两个质数 $p,q$，只有 $p^8$ 与 $p^2q^2$ 含有 $9$ 个质因子，先筛出所有不大于 $\sqrt{N}$ 的质数，然后两两相乘或者一个质数的 $4$ 次方判断是否超过 $\sqrt{N}$，统计答案即可。

## AC 代码

我用的是普通的暴力，没有用筛法，时间复杂度 $O(\sqrt{N})$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,t,p[1000001],cnt,ans;

bool prime(ll x)
{
    for(R int i=2; i*i<=x; ++i)
    {
        if(!(x%i))
        return false;
    }

    return true;
}

int main()
{
    n=read(); t=sqrt(n);

    for(R int i=2; i<=t; ++i)
    {
        if(prime(i)) p[++cnt]=i;
    }

    for(R int i=1; i<=cnt; ++i)
    {
        for(R int j=i+1; j<=cnt; ++j)
        {
            if(p[i]*p[j]<=t) ++ans;
            else break;
        }
    }

    for(R int i=1; i<=cnt; ++i)
    {
        if(pow(p[i],4)<=t) ++ans;
        else break;
    }

    write(ans);
    return 0;
}
```

---

## 作者：yhl110804 (赞：0)

## AT_abc383_d [ABC383D] 9 Divisors

### 题目大意
给你一个数 $n$ 求小于等于 $n$ 的数中有九个因数的数的个数。
### 做法
将一个符合要求的数 $a$ 质因数分解得：

$a=p_1^{k_1}\times p_2^{k_2}\times...\times p_m^{k_m}$

$a$ 的因数个数 $sum=(k_1+1)\times(k_2+1)\times……\times(k_m+1)$。

因为 $sum=9$，所以 $(k_1+1)\times(k_2+1)\times……\times(k_m+1)=9$，即 $k_1+1,k_2+1,……k_m+1$ 均为 $9$ 的因数。所以 $k_i$ 仅有 $0,2,8$ 三种可能。所以 $a$ 要么是一个质数的 $8$ 次方，要么是两个不同质数平方的积。

在计算符合要求的数时，可以剪枝，设有 $x$ 个数符合要求，则时间复杂度是 $O(\sqrt n+x)$ 可以通过本题。
### Code:
```cpp
#include<bits/stdc++.h>
//#define int long long
#define int __int128
using namespace std;
inline int read()
{
   int x=0,f=1;char ch=getchar();
   while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
   while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
   return x*f;
}
void write(int x)
{
   if(x<0)putchar('-'),x=-x;
   if(x<10)putchar(x+'0');
   else write(x/10),putchar(x%10+'0');
}
const int N=5e6;
const int mod=1e9+7;
int n;
int p[N];
int top;
bool vis[N];
int ans;
signed main(){
	n=read();
    int t=2e6;
	for(int i=2;i<=t;i++){
		if(!vis[i])p[++top]=i;
		for(int j=1;j<=top;j++){
			if(p[j]*i>t)break;
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=top;i++){	
		for(int j=i+1;j<=top;j++){
			if(p[i]*p[i]*p[j]*p[j]>n)break;
			ans++;
		}
	}
	for(int i=1;i<=top;i++){
		if(p[i]*p[i]*p[i]*p[i]*p[i]*p[i]*p[i]*p[i]>n)break;
		ans++;
	}
	write(ans);
  return 0;
}

```

```

---

