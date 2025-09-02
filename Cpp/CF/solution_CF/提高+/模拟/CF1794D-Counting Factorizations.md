# Counting Factorizations

## 题目描述

The prime factorization of a positive integer $ m $ is the unique way to write it as $ \displaystyle m=p_1^{e_1}\cdot p_2^{e_2}\cdot \ldots \cdot p_k^{e_k} $ , where $ p_1, p_2, \ldots, p_k $ are prime numbers, $ p_1 < p_2 < \ldots < p_k $ and $ e_1, e_2, \ldots, e_k $ are positive integers.

For each positive integer $ m $ , $ f(m) $ is defined as the multiset of all numbers in its prime factorization, that is $ f(m)=\{p_1,e_1,p_2,e_2,\ldots,p_k,e_k\} $ .

For example, $ f(24)=\{2,3,3,1\} $ , $ f(5)=\{1,5\} $ and $ f(1)=\{\} $ .

You are given a list consisting of $ 2n $ integers $ a_1, a_2, \ldots, a_{2n} $ . Count how many positive integers $ m $ satisfy that $ f(m)=\{a_1, a_2, \ldots, a_{2n}\} $ . Since this value may be large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first sample, the two values of $ m $ such that $ f(m)=\{1,2,3,3\} $ are $ m=24 $ and $ m=54 $ . Their prime factorizations are $ 24=2^3\cdot 3^1 $ and $ 54=2^1\cdot 3^3 $ .

In the second sample, the five values of $ m $ such that $ f(m)=\{2,2,3,5\} $ are $ 200, 225, 288, 500 $ and $ 972 $ .

In the third sample, there is no value of $ m $ such that $ f(m)=\{1,4\} $ . Neither $ 1^4 $ nor $ 4^1 $ are prime factorizations because $ 1 $ and $ 4 $ are not primes.

## 样例 #1

### 输入

```
2
1 3 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
2 2 3 5```

### 输出

```
5```

## 样例 #3

### 输入

```
1
1 4```

### 输出

```
0```

# 题解

## 作者：tyr_04 (赞：7)

upd：2025-03-05 修改了一些错误的内容

upd：2025-03-06 又修改了一些错误的内容。。。

[传送门](https://www.luogu.com.cn/problem/CF1794D)

## 题意

将某一个数分解质因数，将质因数和指数存入一个数组 $a$ 里（长度为 $2n$），求出这个数组中的数分别作质因数或指数时能构成的数的数量（质因数和指数必须两两配对）。

## 思路

1h 场切，很有意思的 dp。

首先明确两个性质：

+ 如果这个数分解出的质因数不同，则这两个数一定不同。

+ 如果这个数分解出的质因数相同，但某个质因数的指数不同，则这两个数一定不同。

根据题目，每个质数最多选一次作质因数，我们假设质因数已经确定，还剩 $k$ 种数，每种数有 $r_k$ 个，考虑方案数。

根据多重组合：

$$
\begin{aligned}
  \begin{pmatrix}
    n\\
    r_{1},r_{2},\dots,r_{k}\\
  \end{pmatrix}
  &=
  \begin{pmatrix}
    n\\
    r_{1}\\
  \end{pmatrix}
+
  \begin{pmatrix}
    n-r_{1}\\
    r_{2}\\
  \end{pmatrix}
+
\cdots
+
  \begin{pmatrix}
    n-(r_{1}+r_{2}+\dots+r_{k-1})\\
    r_k\\
  \end{pmatrix}
\\&=
  \frac{n!}{r_{1}!(n-r_{1})}
  \times
  \frac{(n-r_{1})!}{r_{2}!(n-(r_{1}+r_{2}))}
  \times
\cdots
  \times
  \frac{(n-(r_{1}+r_{2}+\dots+r_{k-1}))!}{r_{k}!}
\\&=
  \frac{n!}{r_{1}!+r_{2}!+\dots+r_{k}!}
\end{aligned}
$$

所以只需要确定质因数再计算上面这个式子就可以算出所有方案数了。但 $n \le 2022$，找出所有质因数的情况数量非常大，无法枚举，考虑用 dp 维护质因数个数。

定义：$dp_{i}$ 表示目前选了 $i$ 个数作质因数（其他遍历过的数全作指数）时的方案数。

线性筛求出所有质数，将数组 $a$ 中的数去重并记录个数，注意到 $mod=998244353$，考虑用乘法逆元代替除法，这样我们可以在转移的同时计算将剩下的数当作指数分配给 $n$ 个位置的方案数（可以将 $dp_{0}$ 初始化为 $n!$ 或在最后将答案乘 $n!$）。

+ 如果当前数不为质数：$dp_{j}=(dp_{j} \times ny_{sum_{i}})$

+ 如果当前数为质数：$dp_{j}=(dp_{j} \times ny_{sum_{i}})+(dp_{j-1} \times ny_{sum_{i}-1})$

其中 $j$ 要类似 $01$ 背包的方式从大往小枚举，$ny_k$ 表示 $k!$ 的乘法逆元，$sum_i$ 表示第 $i$ 种数的个数，时间复杂度 $O(\max_{i=1}^{n}a_i + n^2)$，~~据说还有更快的做法（逃~~。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,no=0,mod=998244353,jc[6005],ny[6005],dp[6005],zs[1000005],sum=0;
bool z[1000005]={0},nz[1000005]={0};
struct node
{
	int x,sum;
}a[6005];
int ksm(int x,int y)
{
	int now=1;
	while(y!=0)
	{
		if(y%2==1)
		{
			now*=x;
			now%=mod;
		}
		x*=x;
		x%=mod;
		y/=2;
	}
	return now;
}
bool cmp(node x,node y)
{
	return x.x<y.x;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	jc[0]=1;
	for(int i=1;i<=6000;i++)
	{
		jc[i]=(jc[i-1]*i)%mod;
	}
	for(int i=0;i<=6000;i++)
	{
		ny[i]=ksm(jc[i],mod-2);
	}
	cin>>n;
	n*=2;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i].sum=1;
	}
	int m=0;
	for(int i=2;i<=1e6;i++)
	{
		if(z[i]==0)
		{
			m++;
			zs[m]=i;
		}
		z[i]=1;
		for(int j=1;j<=m;j++)
		{
			if(i*zs[j]>1e6)
			{
				break;
			}
			z[i*zs[j]]=1;
			if(i%zs[j]==0)
			{
				break;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		nz[zs[i]]=1;
	}
	sort(a+1,a+n+1,cmp);
	no=n;
	for(int i=1;i<=n;i++)
	{
		if(a[i].x==a[i+1].x)
		{
			no--;
			a[i+1].sum=a[i].sum+1;
			a[i].x=INT_MAX;
		}
	}
	sort(a+1,a+n+1,cmp);
	n/=2;
	dp[0]=1;
	for(int i=1;i<=no;i++)
	{
		if(nz[a[i].x]==0)
		{
			for(int j=0;j<=n;j++)
			{
				dp[j]=dp[j]*ny[a[i].sum];
				dp[j]%=mod;
			}
		}
		else
		{
			for(int j=n;j>=0;j--)
			{
				if(j!=n)
				{
					dp[j+1]+=dp[j]*ny[a[i].sum-1];
					dp[j+1]%=mod;
				}
				dp[j]=dp[j]*ny[a[i].sum];
				dp[j]%=mod;
			}
		}
	}
	cout<<(dp[n]*jc[n])%mod;
	return 0;
}
```

---

## 作者：小木虫 (赞：4)

### Preface  
这个数据范围就是简单的计数 dp 题，没有 hard version 太可惜了...  
### Problem  
一个数能被分解成若干个质数的幂次之乘的形式，即：  
$$n=\prod_{p_x|n} p_{x}^{e_x}$$  
其中 $p_x$ 均为质数。  
这些 $p_x,e_x$ 会组成一个可重集 $f(n)=\{p_1,e_1,p_2,e_2.......p_k,e_k\}$。  
现在给你一个大小为 $2\times n$ 的可重集 $S$，请你求出有多少个数字 $x$ 的 $f(x)=S$。  
$n\leq 2022$。可以加强到 $10^5$。  
### Solution  
首先，容易发现 $p_x$ 两两不同，于是对于这个可重集内的相同质数，最多有一个可以作为质因数，剩下的为指数。  

然后你发现，当质因数选完之后你对这些不同的质因数选择指数的方案共有：  
$$\frac{n!}{\prod_{i=1}^{i\leq k}\{cnt_{i}-c(i)\}!}$$  
其中 $cnt_i$ 为第 $i$ 个数的个数，而 $c$ 则在这个数被选为质因数的时候为 1，其他时候为 0。  
然后你设 dp 数组为 $f_{i,j}$，初始状态 $f_{0,0}$ 为 $n!$，表示目前选到了第 $i$ 个数字，选了 $j$ 个质因数的方案数。转移方程为：  
记 $\mathbb P$ 代表质数集。

$$
f_{i, j} = \left\{
\begin{aligned}
&\frac{f_{i-1, j-1}}{(cnt_i-1)!} + \frac{f_{i-1, j}}{cnt_i!},&S_i \in \mathbb P \\
&\frac{f_{i-1, j}}{{cnt_i!}},&S_i\not\in\mathbb P
\end{aligned}
\right.
$$
那么这个问题就能在 $O(n\times(n+\log n)+V)$ 的时间复杂度内解决。  
$n \log n$ 是求逆元的，$n^2$ 是 dp 的，$V$ 是线性筛的。  

但是这个问题显然可以继续优化！  
你发现，你把 dp 数组滚动后消去第一维看成一个多项式 $g(x)$。  
$$g(x)=v_0+v_1x+v_2x^2.....v_nx^n$$  
其中 $v_i$ 就是 $f_{now,i}$。  
然后你第 $x$ 次转移就是乘上一个一次多项式 $E(x)$：  
$$E(x)=\frac{1}{cnt_i!}+\frac{1}{(cnt_i-1)!}x$$  
这个是当 $S_x\in \mathbb P$ 的情况，另一种同理。  
然后你发现，由于多项式乘法是有结合律的，你可以分治。  
简单来说，我们设 $U(L,R)$ 为从 $L$ 到 $R$ 个多项式的乘积，则  
$$U(L,R)=U(L,mid)\times U(mid+1,R)$$  
这样的分治结构的复杂度是 $O(n \log n)$ 的，由于分治后每一层的多项式次数加和为 $O(n)$，你可以用 NTT 来维护多项式乘法，这样的复杂度就是 $O(n \log^2  n)$。  
暴力 dp 代码：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4050;
const int M=2e6+10;
const int mod=998244353;
int n,a[M],is_prime[M],maxval,f[N][N],x[N],y[N],tot,inv[N],fac[N];
vector <int> prime;
void Get_Prime(){
	for(int i=2;i<=maxval;i++){
		if(!is_prime[i])prime.push_back(i);
		for(int j=0;j<prime.size()&&i*prime[j]<=maxval;j++){
			is_prime[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}int p[35];
int qpow(int a,int b){
	p[0]=a;int res=1;
	for(int i=1;i<=30;i++)
		p[i]=(p[i-1]*p[i-1])%mod;
	for(int i=30;i>=0;i--){
		if(b>=(1<<i))
			res=(res*p[i])%mod,b-=(1<<i);
	}return res;
}
map <int,int> b;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;is_prime[1]=1;
	for(int i=1;i<=2*n;i++)
		cin>>a[i],maxval=max(maxval,a[i]),b[a[i]]++;
	Get_Prime();inv[0]=1;fac[0]=1; 
	for(int i=1;i<=2*n;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=2*n;i++)inv[i]=qpow(fac[i],mod-2);
	f[0][0]=fac[n];
	for(auto now:b)++tot,x[tot]=now.first,y[tot]=now.second;
	for(int i=1;i<=tot;i++){
		if(!is_prime[x[i]]){
			f[i][0]=(f[i-1][0]*inv[y[i]])%mod;
			for(int j=1;j<=i;j++)
				f[i][j]=(f[i-1][j-1]*inv[y[i]-1]+f[i-1][j]*inv[y[i]])%mod;
		}else{
			for(int j=0;j<=i;j++)
				f[i][j]=(f[i-1][j]*inv[y[i]])%mod;
		}
	}cout<<f[tot][n];
	return 0;
}
```


---

## 作者：Kisaragi_Nanami (赞：3)

提供一个稍稍有些不同的思路。

考虑这样一个事实：如果确定了 $n$ 个质因数，那么方案数就是剩下 $n$ 个指数做多重集全排列。

由于每个质因数只能出现一次，所以设 $P$ 为 $A$ 中的不同质数集合，$|P|=m$。问题转化为求在 $P$ 中选择 $n$ 个数相对应的多重集全排列之和。

若 $m<n$，那么无解，因为必须满足有 $n$ 个质因数。

若 $m=n$，那么答案就是

$$
\frac{(2n-m)!}{\prod_{i=1}^{2n} (cnt_{A_i}!)}
$$

其中 $cnt_{A_i}$ 表示 $A_i$ 在 $A-P$ 中出现的次数。

若 $m>n$，那么就是要把 $m-n$ 个数放到指数集合中，由于放哪些数会影响全排列的值，所以考虑用 DP 求所有合法的全排列的和。

设 $f_{i,j}$ 表示考虑前 $i$ 个数，已经选了 $j$ 个，$f_{0,0}$ 就是上面那个式子。

如果不选，直接继承 $f_{i-1,j}$。如果选，就会让指数集合增大 $1$，且 $P_i$ 相应的集合增大 $1$，因此


$$
f_{i,j} = f_{i-1,j} + [j>0] \Big(f_{i-1,j-1} \cdot\frac{2n-m+j}{cnt_{P_i}+1} \Big)
$$

答案 $f_{m,m-n}$。


>本人不懂多项式，这个式子是否更容易实现优化呢？


```cpp
// 常数挺大的
#include<bits/stdc++.h>
using namespace std;
#define SET(a,b) memset(a,b,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define rep(i,j,k) for(int i=(j);i<=(k);++i)
#define per(i,j,k) for(int i=(j);i>=(k);--i)
int read() {
	int a=0, f=1; char c=getchar();
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) a=a*10+c-'0', c=getchar();
	return a*f;
}
const int N=4050, M=1e6+5, mod=998244353;
int n, m, facn, nn, D, a[N], p[N], cnt[M], f[N][N/2];
int tot, pr[M];
bool v[M], mp[M], mpp[M];
int fac[N], inv[N];
int fp(int a,int b) {
	int c=1;
	for(;b;a=1ll*a*a%mod,b>>=1) if(b&1) c=1ll*c*a%mod;
	return c;
}
void init() {
	for(int i=2;i<=1e6;++i) {
		if(!v[i]) pr[++tot]=i;
		for(int j=1;j<=tot&&i*pr[j]<=1e6;++j) {
			v[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
	fac[0]=inv[0]=1;
	for(int i=1;i<=2*n;++i) fac[i]=1ll*fac[i-1]*i%mod;
	inv[2*n]=fp(fac[2*n],mod-2);
	for(int i=2*n-1;i;--i) inv[i]=1ll*inv[i+1]*(i+1)%mod; 
}
int rev(int x) { return fac[x-1]*inv[x]%mod; }
signed main() {
	n=read();
	for(int i=1;i<=2*n;++i) a[i]=read(), ++cnt[a[i]];
	init();
	D=1;
	for(int i=1;i<=2*n;++i) {
		if(a[i]!=1&&!v[a[i]]&&!mp[a[i]]) mp[a[i]]=1, --cnt[a[i]], p[++m]=a[i];
		if(cnt[a[i]]&&!mpp[a[i]]) mpp[a[i]]=1, D=1ll*D*inv[cnt[a[i]]]%mod;
	}
	nn=2*n-m, facn=fac[nn];
	if(m<n) { puts("0"); exit(0); }
	if(m==n) {
		printf("%lld\n",1ll*facn*D%mod);
		exit(0);
	}
	f[0][0]=1ll*facn*D%mod;
	for(int i=1;i<=m;++i) for(int j=0;j<=m-n&&j<=i;++j) {
		if(!j) f[i][j]=f[i-1][j];
		else f[i][j]=(1ll*f[i-1][j-1]*(nn+j)%mod*rev(cnt[p[i]]+1)%mod+f[i-1][j])%mod;
	}
	printf("%d\n",f[m][m-n]);
}
```



---

## 作者：masonpop (赞：0)

一道有趣的计数 dp。

容易发现，我们的选取方式在于先确定 $n$ 个不同的素数作为底数，再对剩余的指数做多重集全排列。

我们先将原数列去重后排序，记为 $b_1,b_2,\cdots b_m$。记每个值出现的次数为 $c_i$。那么，我们选取素数的方式就会影响这些值剩余的个数，也会影响多重集全排列的方案数。

设 $vis_i$ 表示一个值是否被选为底数，值为 $0$ 或 $1$。那么，在确定素数选取方案后答案就是 $\frac{n!}{\prod\limits_{i=1}^{m}(c_i-vis_i)!}$。分子是一个定值，可以不管。

可以这样考虑：每确定一个新的 $vis_i$（即每个数是否选取），分母下面就会多除上一个 $(c_i-vis_i)!$。这启发我们使用 dp。

设 $dp_{i,j}$ 表示考虑前 $i$ 个数中选择了 $j$ 个底数时可能的 $\frac{1}{\prod\limits_{k=1}^i(c_k-vis_k)!}$ 之和。通过枚举当前数是否选为底数可以很方便的转移，具体细节见代码。

时间复杂度 $O(n^2)$。[代码](https://codeforces.com/contest/1794/submission/214425675)。

---

