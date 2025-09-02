# Lucky Chains

## 题目描述

Let's name a pair of positive integers $ (x, y) $ lucky if the greatest common divisor of them is equal to $ 1 $ ( $ \gcd(x, y) = 1 $ ).

Let's define a chain induced by $ (x, y) $ as a sequence of pairs $ (x, y) $ , $ (x + 1, y + 1) $ , $ (x + 2, y + 2) $ , $ \dots $ , $ (x + k, y + k) $ for some integer $ k \ge 0 $ . The length of the chain is the number of pairs it consists of, or $ (k + 1) $ .

Let's name such chain lucky if all pairs in the chain are lucky.

You are given $ n $ pairs $ (x_i, y_i) $ . Calculate for each pair the length of the longest lucky chain induced by this pair. Note that if $ (x_i, y_i) $ is not lucky itself, the chain will have the length $ 0 $ .

## 说明/提示

In the first test case, $ \gcd(5, 15) = 5 > 1 $ , so it's already not lucky, so the length of the lucky chain is $ 0 $ .

In the second test case, $ \gcd(13 + 1, 37 + 1) = \gcd(14, 38) = 2 $ . So, the lucky chain consists of the single pair $ (13, 37) $ .

## 样例 #1

### 输入

```
4
5 15
13 37
8 9
10009 20000```

### 输出

```
0
1
-1
79```

# 题解

## 作者：Erinyes (赞：13)

### 废话

赛时过了的，结束时大概 400 名左右，应该是能上波分的。

结果第二天被同班同学叉了 /kk，写篇题解纪念一下。

### 求解

设最终得到的两个不互质的数为 $x+k$ 和 $y+k$，也就是说 $\gcd(x+k,y+k)\neq1$。

这个时候 $x+k$ 和 $y+k$ 都是变量，不好做，怎么办呢？

假设 $p\mid (x+k), p\mid (y+k)$，根据整除的性质可知 $p\mid [(y+k)-(x+k)]\to p\mid (y-x)$。

则我们得到的性质就是 $p\mid (x+k),p\mid (y-x)$。

现在我们的目标变成了找到一个最小的 $k$，使得 $\gcd(x+k,y-x)\neq1$。

很明显 $y-x$ 是不变的，那么问题就简单多了，直接枚举 $y-x$ 的因数然后求出 $k$ 取最小值就完事了。

那 $-1$ 的情况怎么判呢？其实就是满足 $\gcd(x+k,y-x)$ 始终为 $1$，那么合理的情况就只有 $y-x=1$。

### 关于时间复杂度

我们要对 $y-x$ 分解质因数，在预处理出素数的情况下是 $\log_2$ 的复杂度，然后本来是可以只筛到 $10^4$ 的，结果我赛时脑抽直接筛完了 $10^7$，然后还 `#define int long long`，结果寄了。

其实筛到 $10^7$ 是能过的，但是不能开 `long long`。（悲伤

### 代码

千万别 `#define int long long`！！！

另外，`cin,cout` 好像有点卡常，建议加个
```cpp
#define endl '\n'
ios::sync_with_stdio(false); cin.tie(0),cout.tie(0);
```
#### ~~不完整代码~~

```cpp
void getprime(){
    //质数筛，p存质数，vst=0表示是质数
}
void solve(){
    int a,b; cin>>a>>b;
    int k=b-a;
    if(k==1) return cout<<"-1"<<endl,void();
    vector<int> h;
    for(int x:p){
        if(k%x==0) h.push_back(x);
        while(k%x==0) k/=x;
        if(!vst[k] || k==1) break;
    }
    if(k!=1) h.push_back(k);
    int ans=1e9;
    for(int x:h){
        //⌈a/x⌉*x-a 等同于 a-a%x
        int res=ceill(1.0*a/x)*x-a;
        ans=min(ans,res);
    }
    cout<<ans<<endl;
}
```


---

## 作者：2huk (赞：4)

## Description

给定两个整数 $x, y$。请你求出最大的整数 $k$ 使得 $\gcd(x, y) = \gcd(x + 1, y + 1) = \gcd (x + 2, y + 2) = \dots = \gcd(x + k, y + k) = 1$。

若 $k = \infty$ 输出 $-1$，若不存在合法的 $k$ 输出 $0$。

$n$ 组询问。$n \le 10^6$，$1 \le x < y \le 10^7$。

## Solution

先特判两个特殊的：

- 若 $y - x = 1$，那么很显然怎么加都是互质的。输出 $-1$；
- 若 $\gcd(x, y) \ne 1$，那么根据题意答案为 $0$。

若 $\gcd(x + k, y + k) \ne 1$，令这个不为 $1$ 的数为 $d$，那么有 $d \mid (x + k)$，$d \mid (y + k)$。

根据整除的性质，有 $d \mid [(y + k) - (x + k)]$ 即 $d \mid (y - x)$。所以令 $b = y - x$，那么 $d$ 一定是 $b$ 的约数。

令 $a = x$，那么问题就变成了：

> 给定 $a, b$，求最小的整数 $k$ 使得 $\gcd(a + k, b) \ne 1$。（Q1）

重新定义 $\gcd(a + k, b) = d$，那么显然 $d$ 是 $b$ 和 $a + k$ 的约数。那么我们可以枚举 $b$ 的所有**质**因数（因为合因数一定包含质因数）作为 $d$，然后做这个问题：

> 给定 $a, d$，求最小的整数 $k$ 使得 $d$ 是 $a + k$ 的约数。（Q2）

首先如果 $a$ 已经是 $d$ 的倍数了，显然 $k = 0$。否则很显然有 $a \bmod d + k = d$，移项得 $k = d - a \bmod d$。那么 Q2 就解决了。

回到 Q1。对于每一个 $b$ 的质因子 $d$ 都求解出一个对应的 $k$，求所有 $k$ 的最小值即为 Q1 的答案。

那么整个问题就解决了。

## Code

```cpp
int main()
{
	scanf("%d", &n);
	
	for (int i = 2; i <= 1e7; ++ i )
	{
		if (!st[i]) p[ ++ cnt] = i;
		for (int j = 1; p[j] <= n / i; ++ j )
		{
			st[i * p[j]] = true;
			if (i % p[j] == 0) break;
		}
	}
	
	while (n -- )
	{
        scanf("%d%d", &x, &y);
		
		if (__gcd(x, y) != 1)
		{
			puts("0");
			continue;
		}
		
		int a = x + 1, b = y - x;
		
		if (b == 1)
		{
			puts("-1");
			continue;
		}
		
		int res = INF;
		for (int i = 1; p[i] <= b / p[i]; ++ i )
		{
			int t = p[i];
			if (b % t) continue;
			while (b % t == 0) b /= t;
			res = Min(res, t - a % t);
		}
		
		if (b > 1)
		{
			int t = b;
			if (b % t) continue;
			while (b % t == 0) b /= t;
			res = min(res, t - a % t);
		}
		
		printf("%d\n", res);
	}
	return 0;
}
```



---

## 作者：Alex_Wei (赞：2)

固定 $x, y, d$，考虑最小的 $k$ 使得 $\gcd(x + k, y + k) = d$。当 $d\nmid y - x$ 时，显然无解。否则若 $x + k$ 为 $d$ 的倍数，则 $y + k$ 同样为 $d$ 的倍数。

因此，当 $d\mid x$ 时，答案为 $0$。否则还需要 $d - (x\bmod d)$ 次操作使得 $x$ 变为 $d$ 的倍数。

考虑 $y - x$ 的所有约数 $d_i$，对它们的答案取最小值即为所求。时间复杂度 $\mathcal{O}(nd(y))$，无法接受。

若 $d_i\mid d_j$，则当 $x + k$ 为 $d_j$ 的倍数时，$x + k$ 显然为 $d_i$ 的倍数。所以只需考虑 $y - x$ 的所有素因子。埃氏筛或线性筛出每个数的最小质因子，时间复杂度 $\mathcal{O}(n\log y)$。[代码](https://codeforces.com/contest/1766/submission/185019885)。

---

## 作者：Exp10re (赞：1)

又名《论线性筛的妙用》。

## 解题思路

考虑第一个满足 $\gcd (x+k,y+k) \ne 1$ 的 $k$，其必定满足 $\gcd (y-x,x+k) \ne 1$。

此时显然当 $y-x=1$ 时互质序列长度无限长，输出 `-1`。

当 $\gcd (x,y) \ne 1$ 时不构成序列（当 $k=0$ 时就已经不满足条件），输出 `0`。

否则，记 $t$ 为 $y-x$ 的某个因子，则有当 $t \mid (x+k)$ 时 $k$ 必定有 $\gcd (x+k,y+k) \ne 1$。显然满足条件的最小的 $k$ 为 $t-(x\bmod t)\text{*}$。

------------

$\text{*}$ 注：当 $x\bmod t=0$ 时显然 $\gcd (x,y) \ne 1$，该种情况在开头已经特判过，应输出 `0`。 

------------

考虑枚举 $y-x$ 的每个因子 $t$，求得 $t-(x\bmod t)$ 的最小值并输出就一定是答案。由于 $y-x$ 的因子个数很多，这种做法一定会 TLE。

注意到若 $t$ 是一个合数，记 $p \mid t$，那么 $p-(x\bmod p)$ 一定小于等于  $t-(x\bmod t)$。

证明：记 $pq=t$，则 $(x\bmod pq)-(x\bmod p) \leq (q-1)p$，即 $p-(x\bmod p)\leq pq-(x\bmod pq)$。

那么显然 $t$ 取 $y-x$ 的质因子一定比 $y-x$ 的合数因子更优，又有 $1\times 10^7$ 以内的数最多不超过 $8$ 个质因子，那么用线性筛来维护每个数最小质因子，枚举任意数的质因子时间复杂度都是 $\log n$ 的。

总时间复杂度是 $q \log n$ 的，可以接受，详情见代码。

代码多了一个对 $l=1$ 的特判，不难理解，就不加注释了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e7+9;
int isprime[MAXN],prime[MAXN],pcnt;
void init()
{
	int i,j;
	for(i=1;i<=MAXN-1;i++)
	{
		isprime[i]=1;
	}
	for(i=2;i<=MAXN-1;i++)
	{
		if(isprime[i]==1)
		{
			pcnt++;
			prime[pcnt]=i;
		}
		for(j=1;j<=pcnt&&i*prime[j]<=MAXN-1;j++)
		{
			isprime[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
	return;
}
int gcd(int ta,int tb)
{
	int tc=ta%tb;
	while(tc!=0)
	{
		ta=tb;
		tb=tc;
		tc=ta%tb;
	}
	return tb;
}
void work()
{
	int l,r,m,g,flag,ans;
	scanf("%d%d",&l,&r);
	m=r-l;
	if(l==1)
	{
		l++;
		r++;
		flag=1;
	}
	else
	{
		flag=0;
	}
	if(gcd(l,r)!=1)
	{
		printf("%d\n",flag);
		return;
	}
	if(m==1)
	{
		printf("-1\n");
		return;
	}
	g=isprime[m];
	if(g==1)
	{
		g=m;
	}
	ans=flag+g-l%g;
	while(g!=1)
	{
		ans=min(ans,flag+g-l%g);
		while(m%g==0)
		{
			m/=g;
		}
		g=isprime[m];
		if(g==1)
		{
			g=m;
		}
	}
	printf("%d\n",ans);
	return;
}
int main()
{
	init();
	int T,t;
	scanf("%d",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1766D)。

## 思路

事实上我们求的就是最小的 $k$ 使得 $\gcd(x+k+1,y+k+1)\not =1$。

我们不妨设 $d=\gcd(x+k+1,y+k+1)$，那么有 $d\mid(x+k+1),d\mid (y+k+1)$。

根据整除有 $d\mid ((y+k+1)-(x+k+1))\rightarrow d\mid(y-x)$。

通过前文可以得到 $d=\gcd(y-x,x+k+1)$。

显然这个序列有无限长当且仅当 $y-x=1$。

我们不妨枚举 $y-x$ 的**质因子** $d$（合因子没有用，因为一个合因子里面必定含有一个质因子），那么我们现在只需找到一个最小的正整数 $k$ 使得 $(x+k)\bmod d$ 为 $0$ 即可，通过一定的转换能够得到 $k=d-x\bmod d$。

对于求出 $10^7$ 以内数的质因子集合，我们只用依靠线性筛即可，我们筛出范围内数的最小质因子（这个很好求，因为线性筛定义就是这样的），然后找数 $x$ 的质因子集合只需不断将 $x$ 除以最小质因子就能找完。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxn=1e7+7;
int T,x,y; 
bitset<Maxn-1>isp;
vector<int>p;
int lmx[Maxn];
inline void init(int N){
	isp[1]=isp[0]=1;
	for(int i=2;i<=N;i++){
		if(!isp[i]) p.push_back(i),lmx[i]=i;
		for(auto j:p){
			if(i*j>N) break;
			isp[i*j]=1;
			lmx[i*j]=j;
			if(!(i%j)) break;
		}
	}
}
int main(){
	scanf("%d",&T);
	init(Maxn-7);
	while(T--){
		scanf("%d%d",&x,&y);
		int ans=2e9,num=y-x;
		if(__gcd(x,y)!=1){
			printf("0\n");
			continue;
		}
		if(num==1){
			printf("-1\n");
			continue;
		}
		while(num>1){
			int k=(lmx[num]-x%lmx[num]);
			ans=min(ans,k);
			num/=lmx[num];	
		}
		if(ans==2e9) ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
/*
1
8 21
*/

```


---

## 作者：ABookCD (赞：1)


## [D. Lucky Chains](https://codeforces.com/contest/1766/problem/D)

### 简要题意：

有 $n$ 组数据 $(1 \le n \le 10^6)$，每组输入两个数 $x,y,(1\le x,y \le 10^7)$。

找一个最小的自然数 $k$，使得 $\gcd(x+k,y+k)\neq1$，如果找不到，输出 $-1$。

### Idea：

考虑 $x $ 和 $y$ 的差 $d$。

由题意，不妨设 $m |(x+k)$，$m|(y+k)$。

有整除的可减性，得到 $m|(x+k-y-k)$ 即 $m|d$。

相当于在 $d$ 的因子中找一个 $m$，使得 $k$ 最小。

形式化地，有
$$
opt(x,y)=\min_{m|d}(x+m-1)/m*m-x
$$

枚举 $d$ 的因子 $m$，我们得到了一种 $O(n\sqrt{d})$ 的做法。

### Solution：

上面的做法不能通过本题，考虑优化。

考虑 $d$ 的两个质因子 $p,t$ （假设有），发现 $m$ 取 $p$ 或 $t$ 时的解肯定不劣于 $m$ 取 $pt$ 时的，因为 $pt|x+k$ 时同时满足 $p|x+k$ 、$t|x+k$ ，反之则不一定。所以只枚举 $d$ 的质因数即可。

如果我们知道值域内每个数的一个质因数，则枚举 $d$ 的质因子这一问题可以通过递归解决，时间复杂度 $O(\log w)$  ($w$ 为值域，$1 \le w \le 10^7$）。

预处理值域内每个数的一个质因数可以通过埃氏筛解决，时间复杂度 $O(w \log w)$。

至此，本问题在 $O(w \log w + n \log w)$ 时间内解决。

### Code：

代码很短。

```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+100;
int a[maxn];
void init(){
	for(int i=1;i<maxn;i++) a[i]=i;
	for(int i=2;i<maxn;i+=2){
		a[i]=2;
	}
	for(int i=3;i<maxn;i+=2){
		if(a[i]!=i){
			continue;
		}
		for(int j=3;i*j<maxn;j+=2){
			a[i*j]=i;
		}
	} 
} 
int opt(int x,int y){
	int d=y-x;
	int ans=1e9+100;
	if(d==1){
		return -1;
	}
	while(d>1){
		ans=min(ans,a[d]-x%a[d]);
		if(x%a[d]==0){
			ans=0;
			break;
		}
		d/=a[d];
	}
	return ans;
}
int main(){
	init();
	int t;
	scanf("%d",&t);
	int x,y;
	while(t--){
		scanf("%d%d",&x,&y);
		printf("%d\n",opt(x,y));
	}
	return 0;
}
```


---

## 作者：linxinyu330 (赞：0)

## 思路

题目数据范围很大（$ 1 \le n \le 10^6,1 \le x_i < y_i \le 10^7 $），直接枚举会超时，但 $x$ 和 $y$ 的范围提示了我们，这道题可能可以使用欧拉筛法，因此从这方面考虑。

原问题可转化为，给定 $(x,y)$，找到最小的 $k$，使得 $gcd(x+k,y+k) \ne 1$。利用 $gcd$ 的性质：$gcd(a,b)=gcd(a,b-a)$，我们可以得出 $gcd(x+k,y+k)=gcd(x+k,y-x)$，$x+k$ 和 $y-x$ 至少有一个相同的质因子，因为 $y-x$ 不是变量，所以我们可以先求出它的所有质因子，再枚举质因子 $p$，使得 $(x+k) \bmod p=0$，因此，$k=-x(\bmod \hspace{0.1cm} p)$，再把求出来的所有 $k$ 取最小值即可。

## 代码
```cpp
#include<iostream>
#include<vector>
#include<bitset>
using namespace std;
typedef long long ll;
const int N=1e7+5,inf=2e18;

int minp[N];//minp[x]表示x最小的质因子

void euler(int n)
{
	vector<int>primes;
	bitset<N>ip;
	ip[0]=ip[1]=1;
	for(int i=2;i<=n;++i)
	{
		if(!ip[i])primes.push_back(i),minp[i]=i;//质数的最小质因子是它本身
		for(int j=0;j<int(primes.size()) && i*primes[j]<=n;++j)
		{
			ip[i*primes[j]]=1;
			minp[i*primes[j]]=primes[j];//欧拉筛法是用一个数最小的质因子去筛，因此i*primes[j]的最小质因子就是primes[j]
			if(i%primes[j]==0)break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	euler(N);
	int t;
	cin>>t;
	while(t--)
	{
		ll x,y;
		cin>>x>>y;
		y-=x;//y-x
		if(y==1)cout<<-1<<'\n';//1与任何数互质，链无限长
		else
		{
			ll ans=inf;
			while(y>1)//从小到大枚举质因子p
			{
				int p=minp[y];
				ans=min(ans,(-x%p+p)%p);//k=-x(mod p)
				while(y%p==0)y/=p;
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：run_away (赞：0)

## 题意

给定 $T$ 组整数 $x,y(1\le x,y\le 10^7)$，求出整数 $k$，使得 $(x,y),(x+1,y+1),\cdots,(x+k,y+k)$ 互质，$(x+k+1,y+k+1)$ 不互质，若 $k$ 有无数解，输出 `-1`，否则输出 $k$ 的值。

## 分析

当 $y-x=1$ 时，$k$ 有无数组解。

因为 $\gcd(x+k,y+k)\ne 1$，由小学奥数的“更相减损术”，$\gcd(y-x,x+k)\ne 1$。

设 $y-x$ 的因子为 $a$，则最小的 $k$ 为 $a-(x\bmod a)$。

可以直接枚举 $a$，但因子太多了会超时。

发现质因子肯定比合因子更优，所以可以直接用素数筛，求解出 $i$ 的最小质因子 $lmx_i$，则可以直接用 $lmx_{lmx_i}$ 代替暴力的枚举。

因为质因子最多有 $\log y$ 个，所以总时间复杂度 $O(T\log y)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=1e7+5;
ll t,num[maxn],tot,lmx[maxn];
bool vis[maxn];
inline void prime_set(ll n){
	vis[0]=vis[1]=1;
	for(ll i=2;i<=n;++i){
		if(!vis[i]){
            num[++tot]=i,lmx[i]=i;
        }
        for(ll j=1;j<=tot&&i*num[j]<=n;++j){
            vis[i*num[j]]=num[j];
            lmx[i*num[j]]=num[j];
            if(i%num[j]==0)break;
        }
	}
}
signed main(){
    t=read();
    prime_set(10000000);
    while(t--){
        ll x=read(),y=read(),ans=LLONG_MAX,dis=y-x;
        if(dis==1){puts("-1");continue;}
        if(__gcd(x,y)!=1){puts("0");continue;}
        while(dis>1){
            ans=min(ans,lmx[dis]-x%lmx[dis]);
            dis/=lmx[dis];
        }
        if(ans==LLONG_MAX)ans=-1;
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先因为 $ \gcd $ 的差分性质 $ \gcd(n,m)=\gcd(n-m,m) $，则可以得到 $ \gcd(a+k,b+k)=\gcd(a+k,b-a) $，这步是显然的。

然后可以得知 $ \gcd(a+k,b+k) $ 一定为 $ b-a $ 的某个质因子，否则不会大于 $ 1 $ 或者其为合数因子显然不优，因为如果为合数因子则 $ \gcd $ 一定会在这之前达到某个质因子。

找出 $ b-a $ 的所有质因子 $ d $，于是问题转化为了对于一个给定的 $ d $，求最小的 $ k $ 使得 $ d \mid a+k $，不难得到 $ k=d-a \bmod d $，对于所有的 $ d $ 计算出 $ k $ 之后取最小值即可。

这里先用线性筛求出了所有质数之后对于所有的质数暴力跑一遍分解质因数，实际上只需要分解到 $ \sqrt{\max{a_i}} $ 的级别即可，这个范围内的质因子不会很多，实际上有 $ 447 $ 个，所以总时间复杂度为 $ \mathcal{O}(\sqrt{\max{a_i}}+T \times (k\log{\max{a_i}})) $，其中 $ k=447 $ 为素数个数，实际上不会跑满，所以可以通过。

注意用 Pollard-rho 分解质因数虽然理论复杂度更优，但并无法通过，因为常数太大。如果有人通过了可以私信我。

update：时隔两年 Pollard-rho 过去了，但是是经过高度卡常优化，且加了一个乱搞：记忆化，如果发现需要分解的数重复则直接用上一次的结果，否则会 T 掉一个点，最慢点 $ 2 $ 秒左右。代码太长了挂在云剪贴板 [link](https://www.luogu.com.cn/paste/3bmj6gk3) 这里了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
const int maxn=1e7+20;
int prime[maxn];
bool vis[maxn];
int tot=0;
void pre(int n)
{
for(int i=2;i<n;i++)
{
    if(!vis[i])
    prime[tot++]=i;
    for(int j=0;j<tot;++j)
    {
    if(i*prime[j]>n)
    break;
    vis[i*prime[j]]=1;
    if(i%prime[j]==0)
    break;
    }
}
}
unordered_map<int,vector<int> >p;
signed main()
{
    pre(sqrt(1e7)+1);
    int T;
    for(r(T);T;--T)
    {
    	int a,b;
        r(a),r(b);
        if(b-a==1)
        	cout<<-1<<'\n';
        else if(__gcd(a,b)!=1)
        	cout<<0<<'\n';
        else
        {
        	int x=b-a;
        	vector<int>d;
        	for(int i=0;i<tot;i++)
        		if(x%prime[i]==0)
        		{
        			d.push_back(prime[i]);
        			while(x%prime[i]==0)
        				x/=prime[i];
        		}
        		else if(x<prime[i])
        			break;
        	if(x!=1)
        		d.push_back(x);
        	int ans=2e9;
        	for(auto x:d)
        		ans=min(ans,x-a%x);
        	cout<<ans<<'\n';
        }
    }
}
```

另外还有一个奇怪的做法，和上面那个其实本质一样，但时间复杂度更优：预处理求出一个数的最小质因子，这个可以朴素线性筛实现，然后对于每个数不断除其最小质因子，更新答案，递归下去，因为质因子 $ \geq 2 $，所以递归层数不会超过 $ \log{\max{a_i}} $ 层，本质上还是质因数分解，但节约了枚举无用约数的时间，时间复杂度 $ \mathcal{O}(\max{a_i}+T\log{\max{a_i}}) $，跑得比上面那个快。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
const int maxn=1e7+20;
int primes[maxn],minp[maxn],cnt;
bool st[maxn];
void pre(int n)
{
	for(int i = 2 ; i <= n ; i++)
	{
		if(!st[i]) 
		minp[i] = i,primes[cnt++] = i;
		for(int j = 0 ; primes[j] * i <= n ;j++)
		{
			int t = primes[j] * i;
			st[t] = true;
			minp[t] = primes[j];
			if(i % primes[j] == 0) 
            break;
		}
	}
}
unordered_map<int,vector<int> >p;
signed main()
{
    pre(1e7);
    int T;
    for(r(T);T;--T)
    {
    	int a,b;
        r(a),r(b);
        if(b-a==1)
        cout<<-1<<'\n';
        else if(__gcd(a,b)!=1)
        cout<<0<<'\n';
        else
        {
        int x=b-a;
        int ans=2e9;
        while(x>1)
        ans=min(ans,minp[x]-a%minp[x]),x/=minp[x];
        cout<<ans<<'\n';
        }
    }
}
```


---

## 作者：氧少Kevin (赞：0)

## CF1766D - Lucky Chains
- https://codeforces.com/problemset/problem/1766/D

## 题意
- 给出两个正整数 $(x,y)$，满足 $(x,y),(x+1,y+1),(x+2,y+2),\dots,(x+k,y+k)$ 都是互质的，直到 $(x+k+1,y+k+1)$ 起不互质
- 问 $k$ 的值，或指出这个互质的序列长度为 $0$ 或是无限长的

## 思路
- 根据辗转相除法得出的性质：$\gcd(x,y)=\gcd(x,y-x)\ \ (y>x)$
- 在这里，$\gcd(x+k+1,y+k+1)=\gcd(x+k+1,y-x)\ \ (y>x)$
- 因此，要求 $x+k+1$，枚举 $y-x$ 的所有质因子，对于每个质因子，求出一个最小的、$>x+k+1$的、是$y-x$质因子倍数的数字 $X$。
- 为什么一定是最小的？
    - 因为 *最小的、$>x+k+1$的、是$y-x$质因子倍数的数字* 能满足 $\gcd(x+k+1,y+k+1)>1$，并且这里 $k$ 还最小
    - 实际上，我们可以打表看出类似这样的结果：
```
gcd(x,y) = 1
gcd(x+1,y+1) = 1
gcd(x+2,y+2) = 1
···
gcd(x+A-1,y+A-1) = 1
gcd(x+A,y+A) = y-x 的某个质因子 D1 （它最小，这就是我们需要求的）
gcd(x+A+1,y+A+1) = 1
gcd(x+A+2,y+A+2) = 1
···
gcd(x+B-1,y+B-1) = 1
gcd(x+B,y+B) = y-x 的某个质因子 D2
gcd(x+B+1,y+B+1) = 1
gcd(x+B+2,y+B+2) = 1
···
gcd(x+C-1,y+C-1) = 1
gcd(x+C,y+C) = y-x 的某个质因子 D3
gcd(x+C+1,y+C+1) = 1
gcd(x+C+2,y+C+2) = 1
```
- 每个 $X$ 取最小值即为答案

---

## 作者：Polaris_Australis_ (赞：0)

$\gcd(x+k,y+k)=1$，根据辗转相减，转化为 $\gcd(x+k,y-x)=1$，当 $y-x=1$ 时永远不互质，输出 $-1$，否则容易发现，$\gcd(x+k,y-x)\ne1$，与 $x-k$ 是 $y-x$ 的某个质因子的倍数，这两句话是等价的。而 $y-x\le10^7$，质因子不超过 $8$ 个，提前筛出来，处理询问的时候枚举每个质因子，并找到每个质因子的最小的倍数 $d$，满足 $d\ge x$，并更新答案即可。

代码：

```cpp
// Problem: D. Lucky Chains
// Contest: Codeforces - Educational Codeforces Round 139 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1766/problem/D
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion{
void gi(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
int gcd(int x,int y){
	while(y){
		int t(x);
		x=y;
		y=t%x;
	}
	return x;
}
int n,x,y,pr[4000010],cnt,p[10000010][9],num[10000010];
bool np[10000010];
void init(){
	for(int i(2);i<=10000000;++i){
		if(!np[i])pr[++cnt]=i,num[i]=1,p[i][0]=i;
		for(int j(1);j<=cnt&&i*pr[j]<=10000000;++j){
			np[i*pr[j]]=true;
			if(!(i%pr[j])){
				for(int k(0);k<num[i];++k)p[i*pr[j]][k]=p[i][k];
				num[i*pr[j]]=num[i];
				break;
			}
			p[i*pr[j]][0]=pr[j];
			for(int k(0);k<num[i];++k)p[i*pr[j]][k+1]=p[i][k];
			num[i*pr[j]]=num[i]+1;
		}
	}
}
void solve(){
	gi(x);
	gi(y);
	if(gcd(x,y)!=1){
		puts("0");
		return;
	}
	if(abs(x-y)==1){
		puts("-1");
		return;
	}
	if(x>y)swap(x,y);
	int delt=y-x;
	x%=delt;
	int ans(delt);
	for(int i(0);i<num[delt];++i){
		ans=min(ans,((x-1)/p[delt][i]+1)*p[delt][i]-x);
	}
	printf("%d\n",ans);
}
void main(){
	gi(n);
	init();
	while(n--)solve();
}
}  // namespace Std
#undef int
int main(){
	Wilson_Inversion::main();
	return 0;
}
```


---

