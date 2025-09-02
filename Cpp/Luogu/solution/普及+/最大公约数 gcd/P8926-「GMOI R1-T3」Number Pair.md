# 「GMOI R1-T3」Number Pair

## 题目描述

我们定义满足如下条件的数对 $(x,y)$ 叫做奇妙数对：

$k \times \gcd(x,y)=\operatorname{lcm}(x,y)$ 并且 $P \le \gcd(x,y) \le Q$（保证 $P \le Q$）。

有 $T$ 组数据，对于每一组数据，给定 $k,P,Q$ 三个数，求符合条件的数对 $(x,y)$ 的对数。

**答案对 $10^9+7$ 取模。**

## 说明/提示

**注意并不寻常的时间限制。**

对于 $100\%$ 的数据 $1 \le k \le 10^{16}$，$1 \le T \le 50$，$1 \le P \le Q \le 2\times 10^9$。

| 测试点 | $k$ | $T$ | $P$ | $Q$ | 总分 |
| :----------: | :----------: | :----------: | :-------------: | :----------: | :----------: |
| $1\sim 3$ | $k \le 3$ | $T=1$ | $P=1$ | $Q=1$ | $15$ |
| $4\sim 8$ | $k \le 100$ | $T \le 8$ | $P \le 30$ |  $Q \le 30$ |$15$ |
| $9\sim 13$ | $k \le 10^3$ | $T \le 50$ | $P \le 500$ | $Q \le 500$ | $25$ |
| $14\sim 18$ | $k \le 10^{12}$ | $T \le 50$ | $P \le 10^4$ | $Q \le 10^4$ | $15$ |
| $19\sim 22$ | $k \le 10^{13}$ | $T \le 50$ | $P \le 10^6$ | $Q \le 10^6$ | $12$ |
| $23\sim 28$ | $k \le 10^{16}$ | $T \le 50$ | $P \le 2\times10^9$ | $Q \le 2\times10^9$ | $18$ |

**本题保证 $k$ 随机生成，并不存在极限卡人数据，时限已经开到 std 两倍，请各位选手放心。**

## 样例 #1

### 输入

```
5
10 1 3
30 1 5
997 24 35
34 39 99
210 1000 1001```

### 输出

```
12
40
24
244
32```

# 题解

## 作者：yinhy09 (赞：14)

## 官方题解

令 $\gcd(x,y)=d$ 且 $x=d \times x_{1},y=d \times y_{1}$，且 $\gcd(x_{1},y_{1})=1$。

可算得 $\operatorname{lcm}(x,y)=d \times x_{1} \times y_{1}$。

故原式化简为：$k \times d=d \times x_{1} \times y_{1}$
约去 $d$，变为 $k=x_{1} \times y_{1}$ 且 $\gcd(x_{1},y_{1})=1$。

由算术基本定理，设 $k$ 中含有 $n$ 个不同的质因子。则可设：$k=a_{1}^{\alpha_{1}} \times  a_{2}^{\alpha_{2}} \cdots \times a_{n}^{\alpha_{n}}$，其中 $a_{1},a_{2} \cdots a_{n} \in \operatorname{Prime}$。

若想将 $k$ 拆为两个互质的数相乘，则对于 $\forall i \in [1,n]$，若 $a_{i} \mid x_{1}$ 则有 $a_{i} \nmid y_{1}$。

故对于 $\forall i \in[1,n]$，$a_{i}$ 可以为 $x_{1}$ 或  $y_{1}$ 的因数。所以总情况数为 $2^n$ 种。

然而这 $n$ 种是在 $d$ 唯一确定的时候，然而原题目要求仅是 $P \le d \le Q$，所以 $d$ 还有 $Q-P+1$ 中取值，故答案为 $2^n\times(Q-P+1) \pmod {10^9+7}$。

那么此时，唯一的难点就变成了求 $n$ 的值。那么我们就需要采取试除的办法，每找到一个新的质因子就把计数器 $cnt++$，最终返回 $cnt$ 即可。

但是如果每一次都判断质数会非常的慢，所以我们采用线性筛将 $10^8$ 以内的质数全部预处理出来，就可以快速判断了。

---

## 作者：Tx_Lcy (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P8926)

## 思路

简单题，就是稍微有点坑。

先化简一下柿子：

$k \times \gcd(x,y)=\operatorname{lcm}(x,y)$

$k \times \gcd(x,y)=\dfrac{x \times y}{\gcd(x,y)}$

$k \times \gcd(x,y)^2=x \times y$

$\dfrac{x}{\gcd(x,y)} \times \dfrac{y}{\gcd(x,y)}=k$

设 $x=a \times \gcd(x,y),y=b \times \gcd(x,y)$，则 $ab=k$。

显然 $\gcd(a,b)=1$。

接下来我们就要找出满足 $ab=k,\gcd(a,b)=1$ 的所有 $(a,b)$ 的数量，然后再乘上 $\gcd(x,y)$ 有 $q-p+1$ 种可能性。

不难发现 $(a,b)$ 数量就是 $2^z$，其中 $z$ 表示 $k$ 的不同质因子个数。

直接做最坏是 $\mathcal O(T \sqrt k)$，接下来你可以直接 $\rm pr$ 或者采用正解做法：线性筛出质数然后暴力。

而且本题还有个模数，我比赛的时候没看到模数获得了 $82$ 分的高分......

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
int const N=6e6+10;
int cnt,prime[N];
long long const mod=1e9+7;
bitset<100000001>vis;
inline long long qpow(long long a,long long b,long long t=1){for(;b;b>>=1,a=a*a%mod)if(b&1)t=t*a%mod;return t;}
inline void work(int n){
	for(int i=2;i<=n;++i){
		if (!vis[i]) prime[++cnt]=i;
		for (int j=1;j<=cnt && i*prime[j]<=n;++j){
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		} 
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;work(100000000);
	while (t--){
		long long ans=0,k,p,q;
		cin>>k>>p>>q;
		for (int i=1;i<=cnt && prime[i]*prime[i]<=k;++i){
			if (k%prime[i]==0) ++ans;
			while (k%prime[i]==0) k/=prime[i];
		}
		if (k!=1) ++ans;
		cout<<(q-p+1)*qpow(2,ans)%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：Daidly (赞：4)

将条件换个形式：


$$

k=\frac{\text{lcm}(x,y)}{\gcd(x,y)}=\frac{xy}{\gcd(x,y)^2}=\frac{x}{\gcd(x,y)}\cdot\frac{y}{\gcd(x,y)}

$$

考虑从 $k$ 下手，最暴力的方法就是 $O(\sqrt{n})$ 枚举因子，若两因子互质则计数器自增二，这种方法时间复杂度为 $O(T\sqrt{n}\log n)$，有 $82$ 分。

遇到因子，考虑唯一分解定理，对 $k=\prod_{i=1}^mp_i^{\alpha_i}$ 来说，若想把 $\sum_{i=1}^m\alpha_i$ 个 $p_i$ 分成两组保证得到的数互质，那就必有：对于 $p_i$，一个数取完 $\alpha_i$，一个不取。证明显然。可以得出有 $2^m$ 种方案，每一种都可以对应 $Q-P+1$ 个 $\gcd(x,y)$，答案即为 $2^m(Q-P+1)$。

我们预处理 $10^8$ 以内的质数来辅助唯一分解定理，可以预处理 $2^i$。这样分解的复杂度在 $O(\log n)\sim O(\sqrt{n})$ 之间，数据随机，没有问题。

- 注意代码细节以及空间。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll read(){
	ll x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e8+5,M=6e7+5,mod=1e9+7;
ll k,P,Q;
int tt,p[M],num,p2[21],cnt;
bool notp[N];

inline void init(int maxn){
	notp[1]=1;
	for(int i=2;i<=maxn;++i){
		if(!notp[i])p[++num]=i;
		for(int j=1;j<=num&&i*p[j]<=maxn;++j){
			notp[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	p2[0]=1;
	for(int i=1;i<=20;++i)p2[i]=(p2[i-1]<<1);
}

inline void solve(){
	k=read(),P=read(),Q=read();cnt=0;
	for(int i=1;i<=num;++i){
		if(k%p[i]==0){
			cnt++;
			while(k%p[i]==0)k/=p[i];
		}
		if(p[i]*p[i]>k)break;//这里注意是平方，可以省很多时间
	}
	if(k>1)cnt++;
	print(p2[cnt]*(Q-P+1)%mod),putchar('\n');
}

int main(){
	init(1e8),tt=read();
	while(tt--)solve();
	return 0;
}
```

如果觉得有帮助就点个赞吧。

---

## 作者：tobie (赞：2)

题目就给了一个式子，我们化简一下它。

$$k\times\gcd(x,y)=\operatorname{lcm}(x,y)$$
因为 $\operatorname{lcm}(x,y)=\dfrac{xy}{\gcd(x,y)}$

代入得到

$$\dfrac{xy}{\gcd^2(x,y)}=k$$

将 $xy$ 拆开，每人分一个 $\gcd(x,y)$ 得到

$$\dfrac{x}{\gcd(x,y)}\times\dfrac{y}{\gcd(x,y)}=k$$

所以我们就是要把 $k$ 分解为 $ab$ 的形式，其中 $a$ 与 $b$ 互质。

我们记 $t$ 为 $k$ 中**不同**的质因子的个数，则根据乘法原理，$k$ 有 $2^t$ 种拆分形式。

然后考虑 $\gcd(x,y)$，发现这个东西和我们的拆分本身无关，所以对于每种可行的 $k$ 的拆分，有 $Q-P+1$ 种 $\gcd(x,y)$ 值可与之对应。

那么答案就是 $2^t\times(Q-P+1)$，算法的瓶颈在于分解质因数。

由于我的电脑性能没那么好，筛 $\sqrt{n}$ 内的素数会寄，所以我们考虑使用 [P3653](https://www.luogu.com.cn/problem/P3653) 的方法，只筛出 $\sqrt[3]n$ 内的素数。

那么对于一个 $k$，去除 $\sqrt[3]n$ 内的素数后会有如下 $3$ 中情况（其中 $p$ 和 $q$ 为两个不相等的质数）

1.  $\frac{k}{c}=pq$
1.  $\frac{k}{c}=p$
1.  $\frac{k}{c}=p^2$

判断 $p^2$ 可以手写 `sqrt` 函数，判断 $p$ 可以用 `Miller-rabin` 算法。

~~一道绿题用 `Miller-rabin` 确实很离谱。~~

~~但是效率比筛 $\sqrt n$ 的算法快到不知道哪去了。~~

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=220009; 
bool b[N+10];
int p[6000000];
void getp()//筛出sqrt(n)内的素数。
{
	for(int i=2;i<=N;i++)
	{
		if(!b[i]) p[++p[0]]=i;
		for(int j=1;j<=p[0]&&i*p[j]<=N;j++)
		{
			b[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
//	cout<<p[0]<<endl;
}
#define int long long
const int mod=1000000007;
int Test[10]={2,3,5,7,11,13,17,19};
inline int Mul(int x,int y,int z){return (x*y-(int)((long double)x/z*y)*z+z)%z;}
inline int powmod(int x,int y,int z)
{
	if(y==0) return 1;
	if(y&1) return Mul(x,powmod(x,y^1,z),z);
	int t=powmod(x,y>>1,z);
	return Mul(t,t,z);
}
inline bool mr(int x,int y)//Miller-Rabin
{
	if(x==1) return 0;
	if(x==y) return 1;
	int t=x-1,u=0;
	while(t%2==0) t/=2,u++;
	int now=powmod(y,t,x);
	while(u--)
	{
		int nxt=Mul(now,now,x);
		if(nxt==1&&now!=1&&now!=x-1) return 0;
		now=nxt;
	}
	return now==1;
}
inline bool ispr(int x)
{
	for(int i=0;i<=7;i++)
		if(!mr(x,Test[i])) return 0;
	return 1;
}
void work()
{
	int k,p1,q;
	scanf("%lld%lld%lld",&k,&p1,&q);
	int cnt=0;
	for(int i=1;i<=p[0]&&k>=p[i];i++)
	if(k%p[i]==0)
	{
		cnt++;
		while(k%p[i]==0) k/=p[i];
	}
	if(k>1)
	{
	//	cout<<k<<endl;
		if(ispr(k)) cnt++;//,cout<<"Is prime\n";
		else
		{//判断是否为平方数
			int qwq=0;
			for(int i=30;i>=0;i--)
			if((qwq+(1ll<<i))*(qwq+(1ll<<i))<=k) qwq+=(1ll<<i);
			if(qwq*qwq==k) cnt++;
			else cnt+=2;//如果都不是，那只能是两个不同的质数相乘得到。
		}
	}
	printf("%lld\n",powmod(2,cnt,mod)*(q-p1+1)%mod);
}
signed main()
{
	int T;
	scanf("%lld",&T);
	getp();
	while(T--) work();
}
```

---

## 作者：喵仔牛奶 (赞：2)

由 $k\times\gcd(x,y)=\operatorname{lcm}(x,y)$ 得： $k\times\gcd^2(x,y)=xy$，$k=\frac{x}{\gcd(x,y)}\times\frac{y}{\gcd(x,y)}$。

令 $a=\frac{x}{\gcd(x,y)},b=\frac{y}{\gcd(x,y)},d=\gcd(x,y)$，则问题转化为求有多少个 $(a,b,d)$ 满足 $ab=k$，$\gcd(a,b)=1$ 且 $P\leq d\leq Q$。发现 $d$ 对于 $(a,b)$ 没有限制，每一个 $(a,b)$ 都有 $Q-P+1$ 种 $d$，所以可以省略 $d$，将答案乘上 $Q-P+1$。

由于 $\gcd(a,b)=1$，我们可以对 $k$ 分解质因数。设 $k$ 有 $s$ 种不同的质因数，一种质因数只能属于 $a,b$ 中的一个，所以 $(a,b)$ 有 $2^s$ 个，$(a,b,d)$ 有 $2^s\times(Q-P+1)$ 个。

对于分解质因数，因为 $k$ 只有一个 $>\sqrt{k}$ 的质因数，我们可以枚举 $1\sim\sqrt{k}$ 的质因数，一边统计一边除，最后剩下的就是 $>\sqrt{k}$ 的质因数。由于一个个枚举太慢，可以把 $1\sim\sqrt{k}$ 的质数全部处理出来枚举。

因为 $1\sim\sqrt{k}$ 的质数大约有 $\frac{\sqrt k}{\log k}$ 个，所以时间复杂度是 $\mathcal{O}(k+\frac{T\sqrt k}{\log k})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 1e8 + 5, M = 7e6 + 5, mod = 1e9 + 7;
LL T, k, p, q, tot, a[N];
bitset<N> prime;
LL ksm(LL bas, LL k) {
	LL ans = 1;
	for (; k; bas = bas * bas % mod, k >>= 1)
		if (k & 1) ans = ans * bas % mod;
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	for (int i = 2; i <= 1e8; i ++) {
		if (!prime[i]) a[++ tot] = i;
		for (int j = 1; j <= tot && i * a[j] <= 1e8; j ++) {
			prime[i * a[j]] = true;
			if (i % a[j] == 0) break;
		}
	}
	while (T --) {
		LL cnt = 0;
		cin >> k >> p >> q;
		for (LL i = 1; i <= tot && a[i] * a[i] <= k; i ++) {
			if (k % a[i] == 0) cnt ++;
			while (k % a[i] == 0) k /= a[i];
		}
		if (k != 1) cnt ++;
		cout << ksm(2, cnt) * (q - p + 1) % mod << '\n';
	}
	return 0;
}
```


---

## 作者：_shy (赞：1)

## 思路
1. 设 $x=\gcd(x,y)x_1$ 与 $y=\gcd(x,y)y_1$，则易得 $\gcd(x_1,y_1)=1$。由 $k\gcd(x,y)=\operatorname{lcm}(x,y)$ 得，$k{\gcd(x,y)}^2=xy$，进而 $k=x_1y_1$，故欲求满足条件的 $(x,y)$ 的对数，我们需要找到 $k$ 分解成**两个互质的数相乘的方案数**。
2. 根据唯一分解定理把 $k$ 分解成 $p_1^{r_1}p_2^{r_2}\cdots p_n^{r^n}$。若 $p_i \mid x_1$，则 $p_i \nmid y_1$。故可知，$k$ 分解成两个互质的数相乘的方案数是 $2^n$，可由**快速幂**得到。
3. 如何得到 $k$ 的标准分解式。因为 $p_i,i\in \{1,2\dots n\}$ 中**至多有一个大于 $\sqrt{k}$ 的素数**，所以我们可以先通过**线性筛**得到 $1$ 到 $10^8$ 内所有的素数。因为 $1$ 到 $10^8$ 中只有 $28724216$ 个素数，故我们要**卡着这个值开数组，避免MLE**。我们将 $n$ 初始化为 $0$，然后枚举这些素数，如果某个素数可以整除 $k$，那么 $n + 1$，并不断用这个素数除 $k$ 直到这个素数 $\nmid k$。若退出循环后 $k\ne1$，则说明 $k$ 的标准分解式中有一个大于 $\sqrt{k}$ 的素数，那么 $n+1$。
4. 因为 $P\leq \gcd(x,y)\leq Q$，所以最后的答案就是 $(Q-P+1)2^n$。
5. 但是这个题卡常了，于是我们要优化。我们发现在枚举素数进行试除的时候，若某个素数 $p$ 满足了条件 $p^2>k$，则没有必要再枚举了，这时候退出循环就可以了。
6. 最坏时间复杂度为 $\mathcal O(10^8+28724216T)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int maxn = 1e8 + 10;
int t, p, q, pi, zs[28724221], ans;
bool vis[maxn];
long long k; 
void Init () 
{
	for (int i = 2; i <= 1e8; i++) 
	{
		if (!vis[i]) zs[++ pi] = i;
		for (int j = 1; j <= pi; j++) 
		{
			if (1ll * zs[j] * i > 1e8) break;
			vis[zs[j] * i] = 1;
			if (i % zs[j] == 0) break;
		}
	}
}
int quickpower (int b) 
{
	if (b == 0) return 1;
	if (b == 1) return 2;
	int mid = quickpower (b / 2);
	if (b & 1) return 2ll * mid * mid % MOD;
	else return 1ll * mid * mid % MOD; 
}
int main ()
{
	Init ();
	scanf ("%d", &t);
	while (t --) 
	{
		scanf ("%lld %d %d", &k, &p, &q);
		int n = 0;
		for (int i = 1; i <= pi && k != 1; i++) 
		{
			if (1ll * zs[i] * zs[i] > k) break;
			if (k % zs[i] == 0) 
			{
				n ++;
				while (k % zs[i] == 0 && k != 1) k /= zs[i];
			}
		}
		if (k != 1) n ++;
		ans = 1ll * quickpower (n) * (q - p + 1) % MOD;
		printf ("%d\n", ans);
	}
	return 0;
}

```
~~修改了一句不太恰当的语句。~~

---

## 作者：JackMerryYoung (赞：0)

# 前言

T3, 较为简单的数论？

# 正文

条件里有 $\gcd$ 和 $\operatorname{lcm}$, 我们便考虑将 $\operatorname{lcm}$ 分解，这样也许能得到根号级枚举算法。

对柿子进行展开：

$$
\begin{aligned}
k \times \gcd(x, y) &= \operatorname{lcm}(x, y) \\
k \times \gcd(x, y) &= \frac{x \times y}{\gcd(x, y)} \\
k &= \frac{x \times y}{\gcd(x, y)^2} \\
\end{aligned}
$$

啊可惜了没法直接枚举 gcd(x, y). 不过没关系，也许可以拆开来换元。

令 $m = \dfrac{x}{\gcd(x, y)}, n = \dfrac{y}{\gcd(x, y)}$, 则有 $m \times n = k, \gcd(p, q) = 1$. 

有意思的性质出现了。
既然如此，那么我们不妨对 $k$ 分解~~只~~质因数，可以得到二元组 $(m, n)$ 有 $2^{\Omega(k)}$ 个，

那么答案乘以 $\gcd(x, y)$ 的个数 $Q - P + 1$ 即可。

可是 $k$ 太大了，直接 $\mathcal{O}(\sqrt{k})$ 分解好像不太好做容易被卡。

这里我们采取一个打表法，从 OI-wiki 上面学到的。

就是先用线性筛搞出 $\sqrt{k}$ 一下的质数，然后拿筛出来的质数暴力除就行。

这样子复杂度大大下降，大概 $\mathcal{O}(\sqrt{k} + \dfrac{T\sqrt{k}}{\ln{k}})$. 不超过 $1 \times 10^9$ 次，两秒时限应该轻松过吧？

注意要记得取模，有人好像因为没取模拿了 82pts???

# 后言

这道题难度也还行。不过比赛感觉没啥人 AC...

---

## 作者：Day_Dreamer_H (赞：0)

# P8926 题解
~~细节多的题目是真的EX啊~~

## 一些错误情况
WA 第二个点是要特判当 $k=1$ 时直接输出 $q-p+1$

TLE $23$ 到 $26$ 的点是要特判 $prime_i^2>k$ 之后直接退出分解

WA $14$ 之后的点是要在分解 $k$ 之后若 $k\ge2$ 则质因子数加 $1$

~~为什么我知道，因为我错了个遍~~
## 思路
题目给的柿子长这样 $k\times\gcd(x,y)=\operatorname{lcm}(x,y)$

我们知道这个柿子 $x\times y=\gcd(x,y)\times\operatorname{lcm}(x,y)$

那我们把 $\operatorname{lcm}(x,y)$ 变成 $\dfrac{x\times y}{\gcd(x,y)}$

再把左式的 $\gcd(x,y)$ 除过去就会变成 $k=\dfrac{x}{\gcd(x,y)}\times\dfrac{y}{\gcd(x,y)}$

那不就是在说，对于每一个不同的 $\gcd(x,y)$，把 $k$ 拆分成两个**互质**的数的乘积吗

我们有一个定理是 $N=p_1^{c_1}p_2^{c_2}...p_n^{c_n}$，其中 $p_i$ 为质数，$c_i\ge0$

那我们可以把 $k$ 分解质因数，其中要预处理一下 $10^8$ 以内的所有质数，这个可以线性筛解决

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int prime[10000005],pos;
bool vis[100000005];
long long k,p,q;
long long bin_pow(long long a,long long b){
	long long result = 1;
	while(b){
		if(b&1){
			result*=a;
			result%=MOD;
		}
		a*=a;
		a%=MOD;
		b>>=1;
	}
	return result;
}//快速幂没什么好说的
int main(){
	for(register int i = 2;i<=100000001;i++){
		if(!vis[i]){
			prime[pos++] = i;
		}
		for(register int j = 0;j<pos&&prime[j]*i<=100000001;j++){
//			printf("%d %d %d\n",i,prime[j],i*prime[j]);
			vis[i*prime[j]] = true;
			if(i%prime[j] == 0)break;
		}
	}//线性筛也没什么好说的了
	int T;
	cin>>T;
	while(T--){
		long long counter = 0;
		cin>>k>>p>>q;
		if(k == 1){
			cout<<(q-p+1)%MOD<<endl;
			continue;
		}//特判
		for(register int i = 0;i<pos;i++){
			if(k%prime[i] == 0)counter++;
			while(k%prime[i] == 0){
				k/=prime[i];
			}//每次找到质因子就把所有的这个质因子除掉
			if(k == 1||prime[i]*prime[i]>k){
              break;
            }//如果k为1了或当前质因子已经超过根号k了就没必要在找了
		}
		if(k>=2)counter++;//如果k还剩一个质因子还要加上去
		cout<<bin_pow(2,counter)*((q-p+1)%MOD)%MOD<<endl;
	}
}
```

完结撒花~

---

## 作者：strlen_s_ (赞：0)

## 分析

观察柿子：

$k=\dfrac {\operatorname{lcm}(x,y)}{\gcd(x,y)}=\dfrac{x \cdot y}{\gcd(x,y)^2}=x' \cdot y'$。

考虑一对 $x',y'$ 对答案的共享是 $Q-P+1$。

对 $k$ 分解质因数，又因为 $\gcd(x',y')=1$，所以同种质因数必须都在 $x'$ 或 $y'$ 中，否则会导致$\gcd(x',y')$ 不为一。

然后考虑把所有质因数分成 $x',y'$，每种质因数有在 $x'$ 和在 $y'$ 中的两种状态，设 $k$ 的质因数个数为 $s$ ,则答案为 $2^s \times (Q-P+1)$。

线性筛预处理出小于 $10^{8}$ 的质数，分解质因数即可。

## code

```
#include<bits/stdc++.h>
#define in inline
#define re register
#define int long long
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=1e8+100,M=6e6+5,MX=1e8,mod=1e9+7;
bool b[N];
int pr[M],cnt;
int ans;
int k,p,q,T;
void prime(){                   //线性筛。
	for(int i=2;i<=MX;i++){
		if(!b[i])pr[++cnt]=i;
		for(int j=1;pr[j]*i<=MX&&j<=cnt;j++){
			b[pr[j]*i]=1;
			if(i%pr[j]==0)break;
		}
	}
}
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res*=a,res%=mod;
		b>>=1,a*=a,a%=mod;
	}
	return res;
}
signed main(){
	prime();
	T=read();
	while(T--){
		k=read(),p=read(),q=read();
		ans=0;
		for(int i=1;pr[i]*pr[i]<=k&&i<=cnt;i++){        //必须要有 pr[i]*pr[i]<=k 的判断，否则会超时。
			if(k%pr[i]==0){
				ans++;
				while(k%pr[i]==0)k/=pr[i];
			}
		}
		if(k!=1)ans++;
		ans=ksm(2,ans)*(q-p+1)%mod;         //统计答案。
		printf("%lld\n",ans%mod);
	}
	return 0;
}

```

---

## 作者：allenchoi (赞：0)

### 前言：  
由于睡午觉，比赛只打了一个小时多一点，第三题赛时没写完...  
### 思路：  
设 $\operatorname{gcd}(x,y)=g,x=a\times g,y=b\times g$ （ $a,b$ 互质）。  
则 $\operatorname{lcm}(x,y)=a\times b\times g$  
又因为 $\operatorname{lcm}(x,y)=k\times g$  
所以 $a\times b=k$  
那么 $a,b$ 有多少种解呢？  
设 $k$ 有 $c$ 种质因子。
因为 $a,b$ 互质，所以 $k$ 的每种质因子要么全部是 $a$ 的因子，要么全部是 $b$ 的因子，否则就会有大于 $1$ 的公因数。方案数显然是 $2^c$ （乘法原理）。  
$g$ 在 $[P,Q]$ 中取任意值即可。  
时间复杂度： $O(T\times\sqrt K)$  
[然而超时力...](https://www.luogu.com.cn/record/98457157)  
考虑优化..
显然，我们可以只枚举小于 $\sqrt K$ 的质数。用线性筛筛出小于 $10^8$ （ $\sqrt K$ 的最大值）的质数即可。  
时间复杂度： $O(N+T\times \frac{\sqrt K}{\log\sqrt K})$ ，能过。   
### 代码：  
~~~ cpp
#include <cstdio>
#include <vector>
using namespace std;
const int mod = 1e9 + 7,N = 1e8;
int T,p,q,cnt,tot,pr[10000010];
long long k;
bool flag[N + 5];
int ksm(int x,int y)
{
	int ret = 1;
	while(y)
	{
		if(y & 1) ret = 1LL * ret * x % mod;
		x = 1LL * x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main()
{
	flag[0] = flag[1] = 1;
	for(int i = 2;i <= N;i++)
	{
		if(!flag[i]) pr[++tot] = i;
		for(int j = 1;j <= tot && i * pr[j] <= N;j++)
		{
			flag[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%d%d",&k,&p,&q);
		cnt = 0;
		for(int i = 1;k != 1 && i <= tot && 1LL * pr[i] * pr[i] <= k;i++)
			if(k % pr[i] == 0)
			{
				cnt++;
				while(k % pr[i] == 0) k /= pr[i];
			}
		if(k != 1) cnt++;
		printf("%d\n",1LL * ksm(2,cnt) * (q - p + 1) % mod);
	}
	return 0;
}
~~~  
[AC ！！！！！！！1111111111111111](https://www.luogu.com.cn/record/98459789)

---

## 作者：yizcdl2357 (赞：0)

# 题目描述

给定 $k,P,Q$，求：有多少个正整数数对 $x,y$，满足 $\gcd(x,y)\in[P,Q]$ 且 $k\times \gcd(x,y)=\text{lcm}(x,y)$。

数据组数 $\le 50,k\le 10^{16},P,Q\le 2\times 10^9$。

# 解法

## step 1：计数
看到 $\gcd$ 就要枚举。设 $\gcd(x,y)=g$，再设 $x=ag,y=bg$。

显然此时 $\gcd(a,b)=1$，否则 $\gcd(a,b)$ 就成为 $x,y$ 还没提干净的公因子。

代入原式得：

$k\times\gcd(x,y)=kg=\text{lcm}(x,y)=abg$

$ab=k$

因此，$(a,b)$ 是将 $k$ 拆为两个互质数之积的方法之一。

略加思索，可以发现将 $k$ 拆为两个互质数之积的任何方法都可以作为一对 $(a,b)$；同时，在 $[P,Q]$ 间挑出的任何数都可以作为一个 $g$。

因此，答案等于：$n\times(Q-P+1)$，其中 $n$ 是将 $k$ 拆为两个互质数之积的方法数。

考虑 $n$ 的计算。将 $k$ 质因数分解为 $\prod_{i=1}^c p_i^{a_i}$，要保证 $a$ 和 $b$ 互质，必须将一整个 $p_i^{a_i}$ 分给 $a$ 或 $b$（否则 $p_i$ 就是 $a$ 和 $b$ 的公约数了）。

每个 $p_i^{a_i}$ 有两种分法（给 $a$ 或 $b$）；根据乘法原理，$c$ 个 $p_i^{a_i}$ 总共就有 $2^c$ 种分法，即 $n=2^c$。

## step 2：$c$ 的计算

直接质因数分解是 $O(T\sqrt k)$ 的，能拿到 $82$ 分。如何优化呢？

容易想到使用 [Pollard-Rho](https://www.luogu.com.cn/problem/P4718) 进行质因数分解。复杂度 $O(Tn^{1/4})$，可以过。

但这已经大大超出了普及组考纲。~~虽然我们接下来介绍的方法也大大超出了~~。

使用一个套路：预处理出 $1\sim \sqrt[3]k$ 的质数。

计算 $c$ 时，先筛掉 $k$ 的所有 $\le \sqrt[3]k$ 的质因子。易得此时 $k$ 的质因子不超过两个（若有三个，则最小的那个 $\le \sqrt[3]k$，从而被筛去）。

这时，$k$ 只有四种情况：$k=1,k=p,k=p^2,k=pq$。

若 $k=1$，不必继续处理；若 $k=p$ 或 $p^2$，$c$ 加上一；若 $k=pq$，$c$ 加二。

可以用 Miller_Rabin 判断 $k$ 是否是质数；使用二分法计算 $k$ 的平方根，从而判断 $k$ 是否是质数的平方；如果都不是，那 $k$ 只能是 $pq$ 了。

注意：此套路并没有具体求出 $k$ 的质因数分解（事实上，当 $k=pq$ 时次套路不能求出 $p,q$）；但是可以求出其不同质因数个数。

# 代码

不要忘记步步取模，我赛时就因为这个寄了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define N 1000000
#define PN 100000
#define M 1000000007
#define IAKIOI
using namespace std;
bool isp[N+5];
int pn,prm[PN],T,k,l,r;
void sieve()
{
	memset(isp,1,sizeof(isp));
	isp[1]=0;
	for(int i=2;i<=N;i++)
	{
		if(isp[i]) prm[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			int now=i*prm[j];
			if(now>N) break;
			isp[now]=0;
			if(i%prm[j]==0) break;
		}
	}
}
inline int Mul(int x,int y,int z)
{return (x*y-(int)((long double)x/z*y)*z+z)%z;}
inline int powmod(int x,int y,int z)
{
	if(y==0) return 1;
	if(y&1) return Mul(x,powmod(x,y^1,z),z);
	int t=powmod(x,y>>1,z);
	return Mul(t,t,z);
}
inline bool mr(int x,int y)
{
	if(x==1) return 0;
	if(x==y) return 1;
	int t=x-1,u=0;
	while(t%2==0) t/=2,u++;
	int now=powmod(y,t,x);
	while(u--)
	{
		int nxt=Mul(now,now,x);
		if(nxt==1&&now!=1&&now!=x-1) return 0;
		now=nxt;
	}
	return now==1;
}
inline bool ispr(int x)
{
	for(int i=1;i<=12;i++)
		if(!mr(x,prm[i])) return 0;
	return 1;
}
inline bool issq(int x)
{
	int l=1,r=1e9+1;
	while(r-l>1)
	{
		int mid=(l+r)/2;
		if(mid*mid<=x) l=mid;
		else r=mid;
	}
	return l*l==x;
}
signed main()
{
	sieve();
	cin>>T;
	while(T--)
	{
		scanf("%lld%lld%lld",&k,&l,&r);
		int ans=(r-l+1)%M;
		for(int i=1;i<=pn;i++)
			if(k%prm[i]==0)
			{
				ans=(ans*2)%M;
				while(k%prm[i]==0) k/=prm[i];
			}
		if(k==1) IAKIOI;
		else if(ispr(k)||issq(k)) ans*=2;
		else ans*=4;
		printf("%lld\n",ans%M);
	}
	return 0;
}
```
# 习题

列出一些用到此套路的题。

- [P3653 小清新数学题](https://www.luogu.com.cn/problem/P3653)
- [P5150 生日礼物](https://www.luogu.com.cn/problem/P5150)
- [P4446 [AHOI2018初中组]根式化简](https://www.luogu.com.cn/problem/P4446)

---

## 作者：qczrz6v4nhp6u (赞：0)

~~1e8 线性筛，你值得拥有~~
## Solution
化简一下条件：

记 $\gcd(x,y)=d,x'=\dfrac x d,y'=\dfrac y d$;

那么我们有 $k\times d=\dfrac{x\times y}{d}=x'\times y'\times d$；

即 $x'\times y'=k$。

此时我们又有 $\gcd(x',y')=1$，于是问题转化为统计这样的 $(x',y')$ 的数量。

消掉一个未知数，有 $\gcd(x',\dfrac k {x'})=1$。

考虑分解质因数，记 $x'=\prod\limits_{i}p_{i}^{a_i},k =\prod\limits_{i}p_i^{b_i}$，其中 $p_i$ 为质数。

那么 $\gcd(x',\dfrac k {x'})=\prod\limits_ip_i^{\min(a_i,b_i-a_i)}=1$。

即 $a_i,b_i-a_i$ 中必有一个为 $0$。

那么对于 $k$ 的每一个不同的质因子都有两种选择：$a_i=b_i.a_i=0$。

记 $c=$ 【$k$ 的不同质因子个数】，于是满足条件的 $(x',y')$ 共有 $2^c$ 对。

因为统计过程与 $\gcd(x,y)$ 无关（即 $\gcd(x,y)$ 可以取范围内任意值），答案乘上 $(Q-P+1)$ 即可。

---
暴力分解质因数是 $O(\sqrt n)$ 的，无法通过，需要优化。

我们先把 $[1,10^8]$ 以内的质数筛出来，再在这基础上分解质因数。

时间复杂度就优化成了 $O(\dfrac{\sqrt n}{\log n})$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e8;
const int LIM=1e7+5;
const int M=1e9+7;
int p[LIM],plen;
bool v[N+5];
void sieve(){
	for(int i=2;i<=N;i++){
		if(!v[i])p[++plen]=i;
		for(int j=1;i*p[j]<=N;j++){
			v[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
ll qpow(ll a,int b){
	ll res=1;
	for(;b;b>>=1,a=a*a%M)
		if(b&1)res=res*a%M;
	return res;
}
int c;
void decomp(ll n){
	c=0;
	for(int i=1;1ll*p[i]*p[i]<=n;i++){
		if(n%p[i]==0){
			c++;
			while(n%p[i]==0)n/=p[i];
		}
	}
	c+=(n>1);
}
ll k,P,Q;
int main(){
	sieve();
	int t;scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld",&k,&P,&Q);
		decomp(k);
		printf("%lld\n",(Q-P+1)%M*qpow(2,c)%M);
	}
}
```


---

## 作者：kbtyyds (赞：0)

# P8926 题解

建议在[博客](https://www.luogu.com.cn/blog/453059/solution-p8926)里食用：

[题目链接](https://www.luogu.com.cn/problem/P8926)

---

## 题目描述

求 $k\times\gcd(x,y)=\operatorname{lcm}(x,y)$ 且 $P\le\gcd(x,y)\le Q$ 的数对 $(x,y)$ 的数量。

## 分析

我们记 $\gcd(x,y)=t,x=at,y=bt$，则 $\operatorname{lcm}(x,y)=\dfrac {xy} {\gcd(x,y)}=abt$ 且 $a\perp b$。再结合已知式，有：

$$kt=abt$$

$$\text{即 }k=ab$$

所以我们求的数对 $(a,b)$ 的数量为**将 $k$ 分解为两个互质的数的乘积的方案数**。

当然，最终结果是 $(x,y)$ 即 $(at,bt)$，不要忘记乘上了 $t$ 的范围 $(Q-P+1)$。

## 求解

我们考虑将 $k$ 化为唯一分解形式，即：

$$k=\prod_{i=1}^m p_i^{c_i}$$

其中 $m$ 为 $k$ 的质因数种类数。

接着，要想让 $a\perp b$，那么 $a$ 与 $b$ 不能分到同样的质因子（否则 $\gcd(a,b)=\text{该质因子}$ 与题意违背），因此我们对于每一种质因子要么分到 $a$ 身上，要么分到 $b$ 身上。

再考虑以上分法相互独立，由乘法原理知总共有 $2^m$ 种方案。

于是我们只要求出 $m$ ，对 $k$ 分解质因数即可。

## 其他

- 不要忘了开 `long long` 。（应该不会忘吧）

- 有意思的就是求 $m$ 的过程，笔者简单地写了个暴力根号枚举发现被卡，所以我们要先筛出 $\sqrt k$ 以内的质数，用挨个枚举质数去代替直接枚举。

- 时间复杂度 $\mathcal O(\sqrt k+T\times\dfrac {\sqrt k} {\log k})$，可以通过本题。

## 代码

[云剪切板](https://www.luogu.com.cn/paste/301k3qhy)

---

## 作者：shinzanmono (赞：0)

一看题目，最大公约数，最小公倍数……

一言不合推式子：

令 $t=\gcd(x,y)$，则 $x=t\cdot x_0, y=t\cdot y_0, \operatorname{lcm}(x,y) = t\cdot x_0\cdot y_0$，显而易见 $\gcd(x_0,y_0)=1$。

$\therefore$ 原式可变形为 $t\cdot k=t\cdot x_0\cdot y_0$

$\therefore k=x_0\cdot y_0$

我们知道，两个数互质的充要条件是两个数没有共同的质因数，对于 $k$，我们对其分解质因数。设 $k$ 有 $cnt$ 种质因数，则任意一种质因数必将作为 $x_0$ 或 $y_0$ 的质因数，根据乘法原理，一共有 $2^{cnt}$ 种情况。

上面的情况只是当 $t$ 唯一的时候，所以 $t\in[P,Q]$ 时，一共是 $Q-P+1$ 种取值。所以答案为 $2^{cnt}\cdot(Q-P+1)$。

我们使用线性筛预处理出 $[1, 100000000]$ 中所有的质数，采用试除法，查找出 $k$ 的质因数种类个数，然后求的答案即可。

本题的空间可能有一点小，需要使用 bitset 进行优化。

附代码：

```cpp
#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>
using ll = long long;
const int mod = 1e9 + 7;
const int sz = 1e8 + 10;
ll qpow(ll base, ll exp) {
    ll ans = 1;
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}
std::bitset<sz> vis;
std::vector<ll> primes;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    int n = 1e8;
    for (int i = 2; i <= n; i++) {
        if (!vis[i])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0)
                break;
        }
    }
    while (t--) {
        ll k, p, q, ans = 0;
        std::cin >> k >> p >> q;
        if (k == 1) {
            std::cout << q - p + 1 << "\n";
            continue;
        }
        for (ll p: primes) {
            if (p * p > k) break;
            if (k % p == 0) {
                ans++;
                while (k % p == 0) k /= p;
            }
        }
        if (k > 1) ans++;
        std::cout << qpow(2, ans) * (q - p + 1) % mod << "\n";
    }
    return 0;
}

```

---

