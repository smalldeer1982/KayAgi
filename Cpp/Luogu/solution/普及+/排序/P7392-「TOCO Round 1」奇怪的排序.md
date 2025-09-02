# 「TOCO Round 1」奇怪的排序

## 题目背景

欢喜不问天，风流不问天，温柔不问天，良辰不问天，良缘不问天。

问你不问天。

## 题目描述

情人节那天 $\color{orange}\texttt{Biadocy}$ 被虐得好惨，尤其是上流的公爵和小孩说什么《和你在一起的每一天，都叫情人节》。于是他找到了一个机会来报复。

现在有 $n$ 对情人编号为 $1\sim n$ 按任意顺序排成一列，$\color{orange}\texttt{Biadocy}$ 对他们执行了下面这段排序的伪代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/yny3xh8d.png)

$\color{orange}\texttt{Biadocy}$ 想知道有多少种初始排列满足按照这段伪代码排序后情人们的编号有序。也许这能让他好受一点。

## 说明/提示

对于前 $10\%$ 的数据，$T=0$。  
对于前 $30\%$ 的数据，$T\leq 10$，$n\leq 7$。  
对于另外 $10\%$ 的数据，$k=0$。  
对于另外 $10\%$ 的数据，$k=100$。  
对于 $100\%$ 的数据，$0\leq T\leq 10^5$，$1\leq n\leq 10^6$，$0\leq k\leq 100$。

## 样例 #1

### 输入

```
3
3 1
10 2
1 0```

### 输出

```
3
25200
1```

## 样例 #2

### 输入

```
5
502520 0
502520 1
502520 2
502520 3
502520 4```

### 输出

```
1
218102685
429650441
770595802
584122358```

# 题解

## 作者：_saltFish_ (赞：10)

题意很明显，该伪代码就是归并排序的版子，只不过是规定了层数为 $(k-1)$。

我们知道对于一个有 $x$ 个数的子序列它本身有序的概率是 $\dfrac{1}{x!}$。

因为归并排序是从中间划分并递归，所以在第 $k-1$ 层的划分序列必定是 $\dfrac{n}{{2}^k}$ 或 $\dfrac{n}{{2}^k}+1$ 向下取整。而这两种子集的数量是可以求出来的的，留给读者思考，在代码中也有体现。

只要将全排列数 $n!$ 乘上每一个第 $(k-1)$ 层子集有序的概率就能得出最终的答案。

而对于分数的乘法相当于除法，在需要取摸的情况下要求逆元。

----

**特殊的**，对于 $n \le {2}^k$ 的情况，无论序列如何都可以完成排序，所以答案为全排列数 $n!$。

但由于 $k$ 可能会很大，而当 $k > 20$ 时 ${2}^k$ 一定大于任意的 $n \le {10}^6$。为了避免 ${2}^k$ 溢出导致误判，需要添加一个 $k > 20$ 的特判。

当 $k = 0$ 时，只有原序列有序才能在不排序的情况下有序，所以只有 $1$ 种方案。

----

```cpp
#include<iostream>
#define ll long long
const int mod(1e9+7);
using namespace std;
ll t,n,k,jc[1000005]={0,1};
ll qpow(ll a,ll b){
	ll s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
int main(){
	#ifdef ytxy
	freopen("in.txt","r",stdin);
	#endif
	cin>>t;
	for(int i=2;i<=1e6;i++) jc[i]=jc[i-1]*i%mod;
	while(t--){
		cin>>n>>k;
		if(k>20||(1<<k)>=n)
			cout<<jc[n]<<'\n';
		else if(k==0)
			cout<<1<<'\n';
		else
			cout<<1ll*qpow(qpow(jc[n/(1<<k)],mod-2)/*逆元*/,1<<k)
            *qpow(qpow(n/(1<<k)+1,mod-2),n%(1<<k))%mod/*此前为求概率（所有第k层子集有序的总概率）*/
			*jc[n]/*全排列数*/%mod<<'\n'; 
	}
}
```

---

## 作者：donotctjuntilAFO (赞：5)

首先，我们来分析这个函数，

这个函数其实是归并排序，然后我们可以发现 $k$ 其实是层数的限制，简单点说，就是最多往下递归 $k$ 层。

求一共有多少种排列可以被排序成功。

由于一共有 $x$ 个数字，所以一开始就是升序的概率是 
$\dfrac{1}{x!}$ 又由于每个数列是平均分配的，所以每一段是 $\dfrac{n}{2^k}$ 个，其中一半向上取整，一半向下取整。

最后把每个子数列有序的概率乘起来就可以了。

时间复杂度为 $O(T \times \log n)$ 刚好可以过。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#include<set>
#include<map>
#define f(i,l,r) for(register int i=l;i<=r;++i)
#define F(i,r,l) for(register int i=r;i>=l;--i)
#define LL long long
#define ULL unsigned long long
using namespace std;
const LL mod=1000000007;
const int N=1000001;
LL t,n,k,ans,jc[1000009],fjc[1000009];
inline LL power(LL a,LL b){//快速幂
	LL ans=1,bb=a;
	while(b>0){
		if(b&1){
			ans*=bb;
            ans%=mod;
    	}
        bb*=bb;
        bb%=mod;
		b>>=1;
	}
	return ans;
}
int main(){
	jc[0]=1;
	f(i,1,N)
		jc[i]=jc[i-1]*i%mod;
	fjc[N]=power(jc[N],mod-2);
	F(i,N,1)
		fjc[i-1]=fjc[i]*i%mod;
	scanf("%lld",&t);
	while(t--){
		ans=1;
		scanf("%lld%lld",&n,&k);
		if(k>20||(1<<k)>=n){
			printf("%d\n",jc[n]);
			continue;
		}
		else if(!k){
			printf("1\n");
			continue;
		}
		LL x=power(fjc[n/(1<<k)],(1<<k));
		LL y=power(power(n/(1<<k)+1,mod-2),(n%(1<<k)));
		ans=x*y%mod;
		printf("%lld\n",ans*jc[n]%mod);
	}
	return 0;
}

```


---

## 作者：UID341736 (赞：4)

### 算法一

人口普查分，啥都不干就行。

### 算法二

全排列然后模拟。

### 算法三

相当于不排序，输出 $1$。

### 算法四

相当于普通归并排序，输出 $n!$。

### 算法五

其实就是一个带深度的归并排序。可以发现原序列被分成了若干个小块，小块内不进行排序。

显然块的大小只有两种，可以 $O(\min\{k,log n\})$ 模拟计算出两种块的大小和数量。根据归并排序的性质，这些块内的数在排序后仍然会保持原顺序，那么这些块内部就必须是排好序的。所以答案就是 $n!$ 除去每个块大小的阶乘，用快速幂简单计算。

---

## 作者：HPXXZYY (赞：4)

$\color{blue}{\texttt{[Solution]}}$

首先，这个函数就是一个归并排序的模板，只是多了一个参数 $k$。很容易可以知道，这个 $k$ 是用来限制递归次数的，即最多只能递归 $(k-1)$ 次。

可以发现，递归树最底下一层其实是把原数列分成了 $2^{k}$ 个子序列。如果我们要满足最后有序，我们必须要保证最底下的那 $2^{k}$ 个子序列本身是有序的（因为归并的过程不改变原来子序列内部的顺序，只是把相邻两个子序列有序地合并了起来）。

设每个子序列内有 $x$ 个数字，那么它本身就是升序的概率就是 $\dfrac{1}{x!}$（$x!$ 表示 $x$ 的阶乘，下同）。

由于数列是平均分配的，所以最后每个子序列要么有 $\left \lfloor \dfrac{n}{2^{k}} \right \rfloor$ 个数，要么有 $\left ( \left \lfloor \dfrac{n}{2^{k}} \right \rfloor +1 \right )$ 个数，而且每种数列的个数我们是可以算出来的，最后有序的概率就是每个子数列有序的概率的总乘积。

由于一共有 $n!$ 中不同的排列，最后用上面算出的概率值乘以 $n!$ 就是最终的答案。

拿样例 $1$ 举例：

1. $n=3,k=1$，把长度为 $3$ 的数列分成 $2$ 份，一份长 $1$，一份长 $2$，最后有序的概率为 $\dfrac{1}{1!} \times \dfrac{1}{2!}=\dfrac{1}{2}$，因此答案为 $3! \times \dfrac{1}{2}=3$。
2. $n=10,k=2$，分成 $2,2,3,3$ 四份，答案应为 $10! \times \dfrac{1}{2! \times 2!\times 3! \times 3!}=25200$。
3. $n=3,k=0$，只能分成 $3$ 一份，答案为 $3! \times \dfrac{1}{3!}=1$。

总的时间复杂度 $O(T \times \log n)$。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e6+100;
const int mod=1e9+7;
int fac[N],inv[N],n,k,ans;
inline int ksm(int a,int b){
	register int ret=1;
	while (b){
		if (b&1) ret=1ll*ret*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}
	return ret;
}
inline void init_fac_inv(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*i*fac[i-1]%mod;
	inv[n]=ksm(fac[n],mod-2);
	for(int i=n;i;i--)
		inv[i-1]=1ll*i*inv[i]%mod;
}
int main(){
	init_fac_inv(1e6);
	for(int T=1,G=read();T<=G;T++){
		n=read();k=read();ans=1;
		if (k>20||(1<<k)>=n){
			printf("%d\n",fac[n]);
			continue;
		}
		else if (k==0){
			printf("1\n");
			continue;
		}
		ans=1ll*ksm(inv[n/(1<<k)],(1<<k))*ksm(ksm(n/(1<<k)+1,mod-2),(n%(1<<k)))%mod;
		printf("%lld\n",1ll*ans*fac[n]%mod);
	}
	return 0;
}
```

---

## 作者：Dream__Sky (赞：2)

以下所用的变量，除有特殊说明，均与题目含义相同。

考虑归并算法的本质，实际上是将块与块进行排序，块内部不会进行排序。那么进行 $k$ 次归并之后，会把序列分成 $2^k$ 个块。如果要保证它升序，根据归并的性质，每个块内部必须是升序的。

那如何算每个块中是升序的概率呢？设每个块长 $x$，那么概率为 $\dfrac{1}{x!}$。即全排列中只有一种升序的可能，即 $1,2,3,4,\dots,x$。

知道了这个，我们又怎么算最后的各个块长呢？手玩一下样例可以发现，最终块长只有两部分，一些是 $\left\lfloor\dfrac{n}{2^k}\right\rfloor$，一些是 $\left\lfloor\dfrac{n}{2^k}\right\rfloor +1$。根据归并排序的另一个性质，后面的情况共有 $n\mod 2^k$ 个,那么前面的情况，就是总数减去后面的数量，即 $2^k - (n \mod 2^k)$ 个。

但是需要注意的是，当 $k> \log n$ 时，归并排序一定能够将数列排序完成，所以只需要输出 $n$ 的全排列，即 $n!$。

在计算时需要用到快速幂与阶乘求逆元。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
const int N=1e6;
const int M=1e6+1e5;
int fac[M],inv[M],T,n,k;
int qpow(int base,int temp)
{
	int ans=1;
	for(;temp;base=base*base%MOD,temp>>=1)
		if(temp&1) ans=ans*base%MOD;
	return ans;
}//快速幂
void init()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%MOD;
	inv[N]=qpow(fac[N],MOD-2);
	for(int i=N-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}//预处理阶乘逆元
int work()
{
	cin>>n>>k;
	if(log2(n)<k) return fac[n];//特判
	return qpow(inv[n/(1<<k)],(1<<k)-n%(1<<k))%MOD*qpow(inv[n/(1<<k)+1],n%(1<<k))%MOD*fac[n]%MOD;//计算公式
}
signed main()
{
	cin>>T;
	init();
	for(int i=1;i<=T;i++) 
		cout<<work()<<"\n";//多测
	return 0;
}
```


---

## 作者：Neil_Qian (赞：1)

## P7392 「TOCO Round 1」奇怪的排序 题解

比较水，是因为给同学看题想出来一个新做法来写的。

首先注意到 $k>20$ 的情况是很简单的，特判掉就好了。

定义 $[x]$ 为 $x$ 向下取整。

然后发现要求的东西只和 $n,k$ 有关，记答案为 $f(n,k)$，不难发现可以递推求解，$k$ 从 $k-1$ 推过来，$n$ 按照题意分为两部分 $[\frac{n}{2}]$ 和 $[\frac{n+1}{2}]$，写出来就是：

$f(n,k)=f([\frac{n}{2}],k-1)\times f([\frac{n+1}{2}],k-1)\times C_{n}^{[\frac{n}{2}]}$。

最后的组合数是因为两边都只有自己长度的排列，而现在要合并，且不改变大小关系，产生的方案数。

瓶颈在于预处理，时间和空间复杂度都是 $O(nk)$ 的，空间比较卡，可以把询问离线掉按 $k$ 排序再把 $k$ 那一位滚动优化掉。

同学按这个方法过了，代码也很简单，就不给了。

---

## 作者：Transfixion_ (赞：1)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P7392)
## $\textbf{Solution}$
显然就是一个归并排序，但是限制了递归层数为 $k$。

对于递归层数 $k$，由于归并排序的划分方式为截半并向下取整，那么就相当于把原本的 $n$ 个数分成了 $2^k$ 块。考虑每个块中数的个数：一半是 $\left\lfloor\dfrac{n}{2^k}\right\rfloor$，一半是$\left\lfloor\dfrac{n}{2^k}\right\rfloor+1$。

那么只需求出这些块中元素均有序的概率再乘上全排列数 $A_n^n=n!$ 即可。

然后是一些特殊情况：
- 若 $n\le2^k$，则必然能完成排序，答案为 $n!$。考虑到 $2^k$ 有溢出的风险，应当加入特判。
- 若 $k=0$，显然只有一种方案。

注意分数取模使用逆元。时间复杂度 $O(\log n)$。
## $\textbf{AC Code}$
```cpp
#include <bits/stdc++.h>
#define continue(x...) { x; continue; }
const int N = 1e6 + 5;
const int p = 1e9 + 7;
int T, fac[N], inv[N], n, k;

inline int qpow(int a, int b) {
    int res = 1;
    for(; b; b >>= 1) {
        if(b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    } return res;
}

void Init() {
    fac[0] = 1;
    for(int i = 1; i < N; i++)
        fac[i] = 1ll * fac[i - 1] * i % p;
	inv[N - 1] = qpow(fac[N - 1], p - 2);
	for(int i = N - 1; i; i--)
        inv[i - 1] = 1ll * i * inv[i] % p;
}

signed main() {
    Init();
	std::cin >> T;
    for(int n, k; T--; ) {
    	std::cin >> n >> k;
        int blk = 1 << k; //divide into 2 ^ k blocks
        if(k > 20 || blk >= n)
			continue(std::cout << fac[n] << '\n');
        if(!k) continue(puts("1"));
        int a = qpow(inv[n / blk], blk) % p;
        int b = qpow(qpow(n / blk + 1, p - 2), n % blk) % p;
        int ans = 1ll * a * b % p * fac[n] % p;
        std::cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：laol (赞：0)

# 题解：P7392
[传送门](https://www.luogu.com.cn/problem/P7392)

## 分析
这里笔者先用样例 $1$ 的第二组数据 $n=10$，$k=2$ 画张图解释一下题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/2gciy80h.png)

若要使`按照这段伪代码排序后情人们的编号有序`，我们要保证位置在 $1$ 到 $3$，$4$ 到 $5$，$6$ 到 $8$，$9$ 到 $10$ 的情人们的编号有序。

则本组数据的方案数为 $C_{10}^{3}\times C_{7}^{2} \times C_{5}^{3}\times C_{2}^{2}$ 即 $25200$，读者可自行计算。

## 参考代码
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}

int mpow(int a,int b,int s=1){
	while(b){
		if(b&1)s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}return s;
}//求逆元用的
int f[N],g[N],a[N],tot,n,k,ans;
void init(){
	f[0]=1;
	for(int i=1;i<=1e6;i++){f[i]=f[i-1]*i%mod;}
	g[1000000]=mpow(f[1000000],mod-2);
	for(int i=1e6-1;i;i--)g[i]=g[i+1]*(i+1)%mod;//线性求逆元
}
int C(int x,int y){return f[x]*g[x-y]%mod*g[y]%mod;}
void get(int l,int r,int k){
	if(k==0||l==r)return a[++tot]=r-l+1,void();
	int mid=(l+r)>>1;
	get(l,mid,k-1);
	get(mid+1,r,k-1);
}//获取每一小块的大小
void solve(){
	n=read();k=read();
	tot=0;ans=1;
	get(1,n,k);
	for(int i=1;i<tot;i++)	ans=ans*C(n,a[i])%mod,n-=a[i];
	printf("%lld\n",ans);
}
signed main(){
	init();
	int T=read();
	while(T--)solve();
	return 0;
}
```
~~没看数据范围的笔者一交程序，$40$ 分，剩下的超时了。~~ 以上做法时间复杂度为 $O(Tn)$，不能通过本题。

## 优化
考虑将时间复杂度优化到 $O(T\log n)$ 或以下。

根据暴力程序找规律发现，需要初始有序的小段的段数为 $\min(2^k,n)$，而每一小段的长度最多有两种，分别是 $\lfloor\frac{n}{\min(2^k,n)} \rfloor$ 和 $\lceil\frac{n}{\min(2^k,n)} \rceil$。

把组合数 $C$ 全部拆开乘起来我们发现，其分子部分是 $1$ 到 $n$ 的阶乘，其分母部分是每一小段长度的阶乘的乘积。答案非常好求，读者也可自己推推，以下放出主要代码。
``` cpp
//快速幂和阶乘及其逆元暴力代码放了，这里就不放了
void solve(){
	n=read();k=read();
	tot=min(mpow(2,k),n);//计算小段数量
	ans=f[n];
	c=n/tot;//向下取整的小段长度
    d=n%tot;//向上取整的小段数量
	ans=ans*mpow(g[c],tot-d)%mod*mpow(g[c+1],d)%mod;
	printf("%lld\n",ans);
}
```

感谢阅读！

---

## 作者：COsm0s (赞：0)

## $\mathcal{Solution}$

观察伪代码。

显然此伪代码表示的是归并排序的特殊形式：**只递归 $k$ 次**。

由于要求最后的序列有序（本题指单调不降），而我们知道对于任意一个序列其有序的概率为 $\dfrac{1}{n!}$。

所以在递归 $k$ 次之后，仍未处理的序列必须有序，其概率即为 $\dfrac{1}{len!}$。

再次考虑性质，由于归并排序每次递归后的序列长度 $len\in \{\lfloor \dfrac{n}{2^k} \rfloor,\lfloor \dfrac{n}{2^k} \rfloor+1\}$，因此我们只要将全排列数 $\dfrac{1}{n!}$ 除以每一个递归 $k$ 次后的子集的有序的概率即可。

需要注意，题中所给递归数 $k\leq100$，直接进行 $2^k$ 会炸。我们注意到当 $k>\log n$ 时，最后一层的数一定 $\leq1$，此时无论序列怎样都一定可以排列成功，因此特判输出 $\dfrac{1}{n!}$ 即可。

根据上面的特判，我们发现合法的 $k$ 必定 $\leq \log n$，因此复杂度 $\Theta(n\log n)$。

## $\mathcal{Code}$
```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e6 + 5, mod = 1e9 + 7;

int a[N], n, k, fac[N], divs[N], ans;

int qpow(int x, int y) {
	
	int ans = 1;
	
	while(y) {
		
		if(y & 1) ans = ans * x % mod;
		
		y >>= 1;
		
		x = x * x % mod;
	}
	
	return ans;
}

void init() {
	
	fac[0] = 1;
	
	for(int i = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
}

void slove() {
	
	int n, k;
	
	cin >> n >> k;
	
	if(__lg(n) < k) {
		
		cout << fac[n] << '\n';
		
		return ;
	}
	
	int yu = n / (1 << k), op = n % (1 << k);
		
	cout << fac[n] * qpow(qpow(fac[yu], (1 << k) - op), mod - 2) % mod * qpow(qpow(fac[yu + 1], op), mod - 2) % mod << '\n';
}

signed main() {

	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    
	init();

	int T;
	
	cin >> T;
	
	while(T --) slove();
	
	return 0;
}
```


---

