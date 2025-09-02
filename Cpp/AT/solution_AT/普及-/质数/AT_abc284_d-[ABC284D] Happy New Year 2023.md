# [ABC284D] Happy New Year 2023

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc284/tasks/abc284_d

正整数 $ N $ が与えられます。$ N $ は、$ 2 $ つの相異なる素数 $ p,q $ を用いて $ N=p^2q $ と表せることがわかっています。

$ p,q $ を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\leq\ T\leq\ 10 $
- $ 1\leq\ N\ \leq\ 9\times\ 10^{18} $
- $ N $ は、$ 2 $ つの相異なる素数 $ p,q $ を用いて $ N=p^2q $ と表せる
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて、$ N=2023=17^2\times\ 7 $ です。よって、$ p=17,q=7 $ です。

## 样例 #1

### 输入

```
3
2023
63
1059872604593911```

### 输出

```
17 7
3 7
104149 97711```

# 题解

## 作者：Pengzt (赞：7)

[ABC284D](https://www.luogu.com.cn/problem/AT_abc284_d)

题意：

给定一个正整数 $N$，保证 $N = p^2 q$ 且 $p$，$q$ 均为质数。

挺简单的一道题。

因为 $N\leqslant 9\times 10^{18}$，则 $\min(p,q)\leqslant 3\times 10^6$。

直接枚举 $\min(p,q)$ 即可。

时间复杂度：$\mathcal{O}(T\sqrt[3]{n})$

[评测记录](https://atcoder.jp/contests/abc284/submissions/37818302)

因为 $p,q$ 都是质数，便有第二种解法。

先筛出 $1\sim \sqrt[3]{n}$ 中的质数，然后枚举即可。

$3\times 10^6$ 内约有 $2\times 10^5$ 个质数，可过。


时间复杂度：$\mathcal{O}(2\times 10^5\times T)$

[评测记录](https://atcoder.jp/contests/abc284/submissions/37902095)

---

## 作者：MoyunAllgorithm (赞：3)

**题意**

给你正整数 $N$。已知 $N$ 可以被表示为 $p^2q$ ( $p$ 和 $q$ 是不相同的质数）。求 $p$ 和 $q$。数据保证有解且唯一。

$N \le 9 \times 10^{18}$，时限、空限较宽松。

**给出一种时间、空间复杂度不太优秀但确实能够通过的解法。**

**第一轮**：首先，如果 $N$ 是偶数则必然含有 $2$，特判即可。

**第二轮：** 接下来，因为我们知道 $100$ 以内有哪些质数，所以接下来我们枚举 $100$ 以内的 $24$ 个奇质数，将它们作为 $p$ 和 $q$，判断。

**第三轮：** 如果 $N$ 仍然不包含上面的那些质因子，说明 $p,q >100$。 我们枚举 $p$。但是，因为 $p^2=\dfrac{N}{q}$，而 $q>100$，所以 $p$ 的范围是 $[100,\sqrt{9 \times 10^{16}}=3 \times 10^8]$。 我们提前用欧拉筛筛出 $3 \times 10^8$ 的质数（约有 $10^7$ 个），对于每个不能被 $<100$ 的质数分解的 $N$，枚举这些质数作为 $p$ 进行判断。

多组询问，$T \le 10$，时间复杂度为 $(10^8+10^7 T)$，$T \le 10$，且很多 $N$ 会在第一轮和第二轮快速筛掉而不用进行第三轮，再加上时限为 $3$ 秒，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=3e8+5; 
int N,Q;
int prime[MAXN];
bool isprime[MAXN];
int tot=0;
int smallprime[30]={0,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
void EulerSieve()
{
    for(int i=2;i<=MAXN-5;i++) isprime[i]=1;
    for(int i=2;i<=MAXN-5;i++)
    {
        if(isprime[i]) prime[++tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=MAXN-5;j++)
        {
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0) break;
        }
    }
}
int T;
int main()
{
    scanf("%d",&T);
    EulerSieve();
    while(T--)
    {
        long long N;
        scanf("%lld",&N);
        if(N%4==0)
        {
        	printf("%d %lld\n",2,N/4);
        	continue;
		}
		if(N%2==0)
		{
			long long k=N/2;
			k=sqrt(k);
			printf("%lld %d\n",k,2);
			continue;
		}
  //第一轮：筛掉偶数
		bool find=0;
		for(int i=1;i<=24;i++)
		{
			int a=smallprime[i],b=a*a;
			long long k=N/a;
			k=sqrt(k);
			if(N%b==0) printf("%d %lld\n",a,N/b);
			else if(N%a==0) printf("%lld %d\n",k,a);
			if(N%b==0||N%a==0) 
			{
				find=1;
				break;
			}
		}
		if(find) continue;
    //第二轮：筛掉含有100以内质因数的数                        
		for(int i=1;i<=tot;i++)
		{
			int x=prime[i];
			if(N%(1ll*x*x)==0)
			{
				printf("%d %lld\n",x,N/(1ll*x*x));
				break;
			}
		}
  //第三轮
    }
    return 0;
}
```



---

## 作者：CarroT1212 (赞：1)

#### 题目大意

$T$ 组数据。每组数据给定一个正整数 $N$，保证 $N=p^2q$，其中 $p,q$ 为两个不同的质数。求 $p,q$。

数据范围：$1 \le T \le 10$，$1 \le N \le 9\times 10^{18}$，可以证明每组数据都有唯一解。

#### 解法分析

由于题目保证有解，所以 $p,q$ 中的最小值最大也就是一个 $10^6$ 级别的数。

而且很明显只要我们知道了 $p,q$ 中的一个，另一个很容易就可以求出来。

所以我们可以考虑枚举出这个最小值，然后通过简单计算判断一下这个最小值是 $p$ 还是 $q$，就是分别把 $p,q$ 设为这个最小值并计算出另一个，如果另一个是整数就满足条件。由于题目保证有唯一解（也非常显然），直接输出即可。

而枚这个最小值也很简单，只要从 $2$ 开始升序枚举每一个数，第一个能整除 $N$ 的数就是最小值。因为 $p,q$ 都是质数，所以 $N$ 一定不会有比 $p,q$ 都小的因数，$1$ 除外。

最后，记得开 `long long`。赛时有一发挂在这了。

#### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
void solve() {
	ll n;
	scanf("%lld",&n);
	for (ll i=2;;i++) if (n%i==0) {
		ll j=sqrt(n/i); // q=i 时的 p
		if (j*j==n/i) printf("%lld %lld\n",j,i); // p 是整数，成立
		else printf("%lld %lld\n",i,n/i/i);
		return;
	}
}
int main() {
	int t; scanf("%d",&t); for (;t--;) solve();
	return 0;
}
```

---

## 作者：expnoi (赞：1)

因为题中给定的数是三个质数乘积，那么显然其中最小的质数一定只有两百多万。

我们直接枚举求出最小的质数，显然题中所给 $n$ 最小除 $1$ 以外的最小因子一定是质数，也就是 $p$ 和 $q$ 的其中一个。

那么我们分类讨论，分别让 $p$ 和 $q$ 取这个质数的值，并判断这种情况是否合法，计算出另一个答案即可。

这是代码：

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*w;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}
inline int Sqrt(int x)
{
	int l=0,r=1e18,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(mid*mid<=x)
		{
			res=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return res;
}
int T,n;
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		int a=2,p=0,q=0;
		for(;a*a<=n;a++)//先暴力搞出一个质数 
		{
			if(n%a==0)break;
		}
		if(n%(a*a)==0)
		{
			q=n/(a*a);
			print(a);
			putchar(' ');
			print(q);
			puts("");
			continue;
		}
		else
		{
			print(Sqrt(n/a));
			putchar(' ');
			print(a);
			puts("");
		}
	}
}
```

---

## 作者：Hell0_W0rld (赞：1)

## D
+ [link](https://atcoder.jp/contests/abc284/tasks/abc284_d)
+ 难度：橙/黄。
+ *658。

题目给定一个数 $N$，要求分解成 $p^2q$ 的形式，其中 $p,q\in \mathrm{Prime}$。

稍加分析可知，$\min (p, q)\leq \sqrt[3]{N}$。于是我们只需要枚举 $i\in [2,\sqrt[3]{n}]$，如果 $i^2$ 是 $N$ 的因数，则 $p=i,q=\frac{N}{i^2}$；否则如果 $i$ 是 $N$ 的因数，则 $q=i,p=\sqrt{\frac{N}{i}}$。记得一定要强制类型转换。
```cpp
void div(ll n){
	for(ll i=2;;i++){//一定有解
		ll j=i*i;
		if(n%j==0){
			cout<<i<<" "<<n/j<<endl;
			return;
		}
		else if(n%i==0){
			cout<<(ll)(sqrt(n/i))<<" "<<i<<endl;
			return;
		}
	}
}
```

---

## 作者：aeiouaoeiu (赞：0)

考虑枚举 $p,q$。

不难发现 $p,q$ 中必有一者小于等于 $\sqrt[3]{N}$（反证法，若 $p,q$ 两者均大于 $\sqrt[3]{N}$，那么 $p^2q>(\sqrt[3]{N})^3=N$，与原题 $p^2q=N$ 不符），而 $N\le 9\times 10^{18}$。

所以我们可以先筛出 $\sqrt[3]{9\times 10^{18}}\approx 2.1\times 10^{6}$ 范围内的质数，对于每个 $N$ 枚举所有的质数，如果枚举到了能整除 $N$ 的质数 $x$，那么就有两种合法的情况：

- 如果 $x^2$ 能整除 $N$ 且 $\dfrac{N}{x^2}$ 为质数，那么 $p=x,q=\dfrac{N}{x^2}$。
- 如果 $\sqrt{\dfrac{N}{x}}$ 是一个质数并且 $\sqrt{\dfrac{N}{x}}$ 能整除 $N$，那么 $p=\sqrt{\dfrac{N}{x}},q=x$。

最后注意一下要开 ```long long```。

以下是代码：（判断质数时加了一点常数优化）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2100005;
ll prime[maxn],n,q,cnt,t;
bool v[maxn];
bool isp(ll x){
	if(x%2==0) return false;
	for(ll i=3;i*i<=x;i+=2){
		if(x%i==0) return false;
	}
	return true;
}
int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	for(int i=2;i<=maxn;i++){
		if(!v[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			v[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	while(t--){
		cin>>n;
		for(int i=1;i<=cnt;i++){
			if(n%prime[i]!=0) continue;
			ll x=prime[i];
			if(n%(x*x)==0){
				ll q=n/(x*x);
				cout<<x<<" "<<q<<endl;
				break;
			}else{
				ll sq=sqrt(n/x);
				if(n%sq==0&&isp(sq)){
					cout<<sq<<" "<<x<<endl;
					break;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：lwx20211103 (赞：0)

## 题意

这题题意很简单明确：给你一个数字 $n$，要求把 $n$ 分解成 $p^2q$，其中 $p,q$ 得要是质数。因为题目保证 $n$ 能分解成那样的形式，所以可以大胆做，放心做。

## 分析

这肯定要用到质数筛，为了不重复造轮子，我就写了一个模板，通用于质数筛的，时间复杂度 $\Theta (n)$。

```cpp
typedef long long ll;

class get_prime
{
private:
	bitset<100000007> m;
	ll total;
	void _config()
	{
		m.set();
		m[1] = 0;
	}
public:
	ll ans;
	vector<ll> primes;
	void setsize(ll n)//设置范围
	{
		_config();
		total = n;
		long long i, j;
		for (i = 1; i <= n + 5; i++)
		{
			if (m[i])
			{
				for (j = (i << 1); j <= n + 5; j += i)
					m[j] = 0;
			}
		}
	}
	int getsum()//统计质数数量
	{
		for (ll i = 1; i <= total; i++)
		{
			if (m[i])
				ans++;
		}
		return ans;
	}
	vector<ll> getnums()//获得质数数列
	{
		for (ll i = 1; i <= total; i++)
		{
			if (m[i])
				primes.push_back(i);
		}
		return primes;
	}
}; //现成的质数模板
```

现在模板有了，怎么办呢？我们可以先枚举到 $\sqrt{n}$，找出第一个能被 $n$ 整除的质数，如果这个数字的平方也能被 $n$ 整除，那么这个数字就是 $p$，否则是 $q$。如果对这个还有点不理解的可以看注释。时间复杂度为 $\Theta (\sqrt[3]{n})$，同时，因为只用枚举到 $\sqrt[3]{n}$，而 $n \leq 9 \times 10^{18}$，所以质数只用筛到 $3 \times 10^6$。

于是，完整代码就出来了，此题不算难。
```cpp
#include <bits/stdc++.h> //I AK IOI.
using namespace std;

typedef long long ll;

class get_prime
{
private:
	bitset<100000007> m;//bitset初始化，可以自行搜索其使用
	ll total;//大小
	void _config()//质数筛初始化
	{
		m.set();
		m[1] = 0;
	}
public:
	ll ans;
	vector<ll> primes;
	void setsize(ll n)//设置范围
	{
		_config();
		total = n;
		long long i, j;
		for (i = 1; i <= n + 5; i++)
		{
			if (m[i])
			{
				for (j = (i << 1); j <= n + 5; j += i)
					m[j] = 0;
			}
		}
	}
	int getsum()//统计质数数量
	{
		for (ll i = 1; i <= total; i++)
		{
			if (m[i])
				ans++;
		}
		return ans;
	}
	vector<ll> getnums()//获得质数数列
	{
		for (ll i = 1; i <= total; i++)
		{
			if (m[i])
				primes.push_back(i);
		}
		return primes;
	}
}; //现成的质数模板

get_prime a;

const int maxn = 3e6;
vector<ll> nums;

int main()
{
	int t;
	cin >> t;
	a.setsize(maxn);
	nums = a.getnums();//获得质数
	while (t--)
	{
		long long n = 0,p = 0, q = 0;
		cin >> n;
		for (int i = 0; nums[i] <= sqrt(n); i++)//枚举
		{
			if (n % nums[i] == 0)
			{
				n /= nums[i];//先把 n 除以数字，再进一步判断
				if (n % nums[i] == 0)
				{
					p = nums[i];//标记p
					break;
				}
				else
				{
					q = nums[i];//另一个质数q
					break;
				}
			}
		}
		if (p > 0) q = n / p; //执行完后有p存在
		else p = sqrt(n); //如果没有，p就为n的算术平方根
		cout << p << " " << q << "\n";
	}
	
	return 0;
}

```



---

## 作者：LaDeX (赞：0)

## 题意

有 $T$ 组数据。

每组数据给定一个整数 $N$，对于每一个 $N$，都有两个质数 $p,q$ 满足 $p^2q=N$，试求出 $p,q$。

## 解法

$N\leq 9\times10^{18}$，$N$ 过大，无法暴力求。

一个线性筛即可。

$N=p^2q$，$p^2$ 与 $q$ 成反比，显然的，$p$ 增大，则 $q$ 变小，二者最接近时是为 $\sqrt[3]{N}$，所以 $p,q$ 之间必然有一个小于 $\sqrt[3]{9}\times 10^6$ 且是 $N$ 的因数。

所以我们只需要线性筛筛到 $10^7$，筛出 $10^7$ 以内的质数，再找出任意一个 $N$ 的因数即可。

设 $k$ 为用以上方法找出的 $N$ 的第一个因数（最小的质因子）。

如果 $\sqrt{\frac{N}{k}}$ 是个整数，则 $k$ 就为上文中的 $q$，$\sqrt{\frac{N}{k}}$ 就为上文中的 $p$。

如果 $\frac{N}{k\times k}$ 是一个整数，则 $k$ 就为上文中的 $p$，$\frac{N}{k\times k}$ 就为上文中的 $q$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mkp(x, y) make_pair(x, y)
#define eb(x) emplace_back(x)
// I Love Yukino Forever!
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 1e7 + 10;
const LL LIMIT = 1e7;
LL is[N], prime[N], n, m;
 
void InitPrimes(){
	is[1] = 1;
	for (LL i = 2; i <= LIMIT; i ++){
		if (!is[i])
			prime[++ m] = i;
		for (LL j = 1; j <= m && i * prime[j] <= LIMIT; j ++){
			is[prime[j] * i] = 1;
			if (i % prime[j] == 0)
				break;
		}
	}
	return ;
}

int main(){
	Fcin;
	InitPrimes();
	LL t;
	cin >> t;
	while (t --){
		LL n;
		cin >> n;

		LL k = -1;
		for (LL i = 1; i <= m; i ++)
			if (n % prime[i] == 0){
				k = i;
				break;
			}
			
		LL p = prime[k], q = n / p / p;
		if (p * p * q == n){
			cout << p << " " << q << "\n";
			continue;
		}

		q = prime[k]; p = (LL)(sqrt(n / q));
		if (p * p * q == n){
			cout << p << " " << q << "\n";
			continue;
		}

	}
	return 0;
}
```


---

## 作者：code_hyx (赞：0)

首先，要证明：若有解，$\min(p,q)^3 \le N$。  
可以采用反证法，假设 $\min(p,q)^3>N$。  
假如 $\min(p,q)=p$，则 $q>p$，$p^2q>p^3>N$，无解。  
假如 $\min(p,q)=q$，则 $p>q$，$p^2q>q^3>N$，无解。  
与有解矛盾，所以命题成立。  
接下来，直接暴力枚举就行了，因为 $N \le 9 \times 10^{18}$，所以最多只会枚举到几百万就可以停止了。  
对于判断素数，可以用埃氏筛预处理。   
代码：
```
#include<bits/stdc++.h>
using namespace std;
long long zhishu[50005],flag[20000005],flag1[20000005];
void getprime()
{
	for(int i=2;i<=50000;i++)
	{
		if(flag[i]==1)continue;
		zhishu[++zhishu[0]]=i;
		for(int j=2;i*j<=50000;j++)flag[i*j]=1;
	}
}
int main()
{
	long long l=1,r=6666666;
	for(int i=1;i<=zhishu[0];i++)
	{
		long long t=l/zhishu[i];
		if(t*zhishu[i]<l)t++;
		if(t==1)t++;
		while(t*zhishu[i]<=r)
		{
			flag1[zhishu[i]*t-l+1]=1;
			t++;
		}
	}
	int t;
    long long x;
	cin>>t;
    while(t--)
    {
        cin>>x;   
        for(long long i=2;i*i*i<=x;i++)
        {
            if(!flag1[i])
            {
            	long long p=i,q=x/(i*i);
            	if(p*p*q==x)
				{
					cout<<p<<" "<<q<<"\n";
					break;
				}
            	q=i;
            	p=(long long)(sqrt(x/i));
            	//cout<<i<<" "<<q<<" "<<p<<"\n";
            	if(p*p*q==x)
				{
					cout<<p<<" "<<q<<"\n";
					break;
				}
			}
		}
    }
	return 0;
}
```


---

## 作者：Neil_Qian (赞：0)

# [ABC284D] Happy New Year 2023 题解
给定 $N$，求出满足 $N=p^2\times q$，要求 $p,q$ 都是质数。

题目上明确说了 $p,q$ 都是质数，也就是说，我们枚举质因数 $i$，它既可以作为 $p$，也可以作为 $q$。作为 $p$ 应当满足 $i\times i|n$，作为 $q$ 应当满足 $n/i$ 是完全平方数。

我们如何枚举质因数 $i$ 呢？一个循环即可，$i$ 不设上限。最坏要枚举多少次呢？其实枚举到 $K=^3\sqrt N$ 就可以了。为什么呢？我们假设 $K$ 以内都没有解，则解最小为 $N=(K+1)^2\times(K+1)$，而带入 $K=^3\sqrt N$ ，显然灯饰不可能成立。时间复杂度 $O(T\times ^3\sqrt N)$，可以通过。

注：其实，我们直接枚举 $i$ 即可，因为 $i$ 只会枚举到 $3\times 10^6$，不会超时。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;ll T,n,i,w;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n),w=sqrt(n/2);
		if(n%2==0&&w*w==n/2)//小优化：先处理2，分情况如上
		{printf("%lld 2\n",w);continue;}
		if(n%4==0){printf("2 %lld\n",n/4);continue;}
		for(i=3;;i+=2)if(n%i==0){//后面枚举奇数即可
			if(n%(i*i)==0){printf("%lld %lld\n",i,n/i/i);break;}
			w=sqrt(n/i);
			if(w*w==n/i){printf("%lld %lld\n",w,i);break;}
		}
	}
	return 0;
}
```

完结撒花！

---

## 作者：紊莫 (赞：0)

## Part 0 题意简述  

给定一个 $N$，保证其能表示成 $N=p^2q$ 的形式，且 $p$，$q$ 均为质数，请你求出这两个数。  

## Part 1 思路  

由给定的分解可知，$N$ 必然只有两个质因数，我们只要知道其中一个就必然可以求出余下的一个。但是 $N$ 的取值非常大，不可能每次 $O(\sqrt{n})$ 的枚举因数。   

于是想到可以先线性筛出 $\sqrt{n}$ 以内的质数，显然这样的数字不会很多，然后直接枚举即可。  

找到了其中一个质数后，判断一下它是 $p$ 还是 $q$ 即可。  

实际的时间复杂度表现非常好。  

## Part 2 参考代码 

仅供参考。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
#define int long long
#define mkpr make_pair
#define fi first
#define se second
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define dF(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
using namespace __gnu_cxx;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if (x < 0) x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
inline void writeln(int x){write(x);putchar('\n');}
inline void writesp(int x){write(x);putchar(' ');}
inline int lowbit(int x) {return x&(-x);}
typedef pair<int,int> Pair;
const int N=100005,maxn=1e7+5;
int n,m,a[N],v[maxn],pri[maxn],cnt=0;
void p(int n){
	for(int i=2;i<=n;i++){
		if(!v[i])
			pri[++cnt]=v[i]=i;
		for(int j=1;j<=cnt;j++)	{
			if(v[i]<pri[j]||pri[j]>n/i) break;
			v[i*pri[j]]=pri[j];
		}
	}
}
signed main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    p(maxn-5);
	int T;cin>>T;
	while(T--){
		cin>>n;int p,q;
		for(int i=1;pri[i]*pri[i]<=n;i++){
			if(n%pri[i]==0) {
				p=pri[i];
				break;
			}
		}
		q=sqrt(n/p);
		if(q*q*p==n){
			cout<<q<<' '<<p<<'\n';
		}else{
			cout<<p<<' '<<n/p/p<<'\n';
		}
	}
    return 0;
}
```


---

## 作者：Esperance (赞：0)

暴力水题，但是有坑。

## 题意

给你一个整数 $ n $，让你求出两个质数 $ p $ 和 $ q $ 使得 $ p^2q=n $。保证**有解**且 $ p, q $ 是**唯一解**。

## 思路

小暴力。因为保证有解，只需枚举 $ i $，当 $ i \mid n $ 时，判断 $ i $ 是 $ p $ 还是 $ q $，并结束循环即可。

- 当 $ {i}\mid{\frac{n}{i}} $ 时，$ i = p $, $ q = \frac{n}{i^2}$ 

- 当 $ {i}\nmid{\frac{n}{i}} $ 时，$ i = q $，$ p = \sqrt{\frac{n}{i}} $

因为是三个数相乘，则找到 $ i $ 时 $ i \leq \sqrt[3]{n} $，完全不会超时。

坑点：输出 $ \sqrt{\frac{n}{i}} $ 时一定要提前存储在变量里，因为```sqrt()```函数的返回值是 $\texttt{double}$，输入的值是 $\texttt{long\ long}$，直接输出会有一定的精度损失，会使你丢掉一半的分。~~本蒟蒻就是因为这个硬是调了半天。~~

## 代码

```
#include <iostream>
#include <cmath>
using namespace std;
long long n, t;
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 2; i*i*i <= n; i++)
			if (n % i == 0)
			{
				long long ljp = n / i, wyx = sqrt(ljp);
				if (ljp % i == 0) cout << i << ' ' << ljp/i << endl;
				else cout << wyx << ' ' << i << endl;
				break;
			}
	}
	return 0;
} 
```

---

## 作者：Lyu_echo (赞：0)

## 题意

**本题多测。**

每组测试数据中：给定整数 $n$。

求：质数 $p,q$，使得 $p^2q = n$。

保证数据有解且唯一解。

注意：$1\le n \le 9\times 10^{18}$。

## 解题思路

考虑 $p,q$ 同阶。

不难发现：$1 \le p,q \le 3\times 10^6$。

枚举即可。

注意数据范围，需要开 `long long`。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long //需要开 long long
using namespace std;

signed main () {
    int t;
    cin >> t; //本题多测
    while (t--) {
        int n;
        cin >> n;
        for (int i = 2; ; i++) {
            if (n % i ==0) { //如果当前 i 为 n 的因数
                if (n % (i*i) == 0) { //i^2 亦为 n 的因数，即符合 p 要求
                    cout << i << " " << n / i / i << endl;
                    break;
                }
                else { //符合 q 要求
                    cout << (int)sqrt(n/i) << " " << i << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
```



---

## 作者：loser_seele (赞：0)

提供两种不同的做法。

第一种：观察到 $ \mathcal{O}(T\sqrt{n}) $ 难以通过本题，但是 $ \mathcal{O}(Tn^\frac{1}{4}) $ 可以，不难想到直接上 Pollard-rho 板子分解质因数，然后分解后的集合内出现两次的数显然为 $ p $，剩下的那个就是 $ q $。时间复杂度同上，可以通过。代码实现是这个方法。

第二种：首先答案既然被写成三个质因数分解的形式，那么其中必定有一个 $ \leq n^\frac{1}{3} $。于是不难想到枚举这个数。

具体地，如果这个数是 $ p $，则直接判断 $ q=\frac{n}{p \times p} $ 是不是整数即可。

如果这个数是 $ q $，则有 $ p \times p=\frac{n}{q} $，判断 $ \frac{n}{q} $ 是否是完全平方数即可。

实现上，直接枚举所有 $ \leq n^\frac{1}{3} $ 的数也可以通过，但注意到 $ p,q $ 都是质数，所以线性筛先预处理出素数之后只枚举素数判断即可。第二种方法赛时比第一种更晚想到，因为第一种比较好想，所以就没写。

时间复杂度 $ \mathcal{O}(T \times \max \{ \pi(n^\frac{1}{3}) \}) $，可以通过。

给出第一种方法的实现代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p)
{
    a+=b;
    if(a>=p)
    a-=p;
    return a;
}
inline int mul(int a,int b,int mod)
{
return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
    ans = mul(ans, a, m);
  return ans;
}
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
  if (x == 1) 
  return false;
  ll s = x - 1; 
  int d = 0;
  while (!(s & 1)) 
  ++d, s >>= 1;
  for (int i = 0; i < cnt; ++i) 
  {
    if (x % p[i] == 0) 
    return x == p[i];
    if (!MR_check(p[i], x, s, d)) 
    return false;
  }
  return true;
}
namespace Pollard_Rho 
{
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  factor_(x, v);
  std::sort(v.begin(), v.end());
}
}
using Pollard_Rho::factor;
signed main()
{
    int T;
    for(r(T);T;--T)
    {
        int n;
        r(n);
        vector<int>p;
        factor(n,p);
        if(p[0]==p[1])
        cout<<p[0]<<' '<<p[2]<<'\n';
        else if(p[1]==p[2])
        cout<<p[1]<<' '<<p[0]<<'\n';
        else
        cout<<p[0]<<' '<<p[1]<<'\n';
    }
}
```


---

