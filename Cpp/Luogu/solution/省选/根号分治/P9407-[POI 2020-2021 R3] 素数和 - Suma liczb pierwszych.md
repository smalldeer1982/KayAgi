# [POI 2020/2021 R3] 素数和 / Suma liczb pierwszych

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Suma liczb pierwszych](https://szkopul.edu.pl/problemset/problem/8brtPux-IyytS6rOoOR1cJTL/statement/)。

d2t3。

## 题目描述

给你一个数字 $n$，求 $l,r$，使 $[l,r]$ 区间内的所有质数之和等于 $n$。

如果有多解，任意一组均可；无解输出 `NIE`。

## 说明/提示

对于所有数据，$1\leq n\leq 10^{11}$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 10000$ | 15 |
| 2 | $n\leq 10^8$ | 20 |
| 3 | $n\leq 2\times 10^9$ | 40 |
| 4 |  | 25 |

## 样例 #1

### 输入

```
15
```

### 输出

```
3 7
```

## 样例 #2

### 输入

```
9992
```

### 输出

```
4993 4999
```

## 样例 #3

### 输入

```
100000000
```

### 输出

```
NIE
```

## 样例 #4

### 输入

```
1000000007
```

### 输出

```
1000000007 1000000007
```

## 样例 #5

### 输入

```
99999999996
```

### 输出

```
295693 1693067
```

# 题解

## 作者：World_Creater (赞：9)

考虑 $n$ 小的时候怎么做。

直接预处理出 $n$ 以内的所有质数，做一个前缀和，然后双指针即可，这一部分是简单的，复杂度 $\mathcal{O}(n)$。

当 $n$ 大时这样显然寄了，考虑用这种做法做到上限为 $L$，即解决所有答案右端点在 $[1,L]$ 内的情况，这个时候，答案右端点显然在 $(L,n]$ 内，不难发现，满足如上情况时答案的质数个数只有 $\mathcal{O}(\dfrac{n}{L})$ 级别。

考虑枚举质数个数，设现在枚举的质数个数为 $t$，则答案肯定在 $\dfrac{n}{t}$ 附近，设答案区间的左右端点落在 $[l',r']$ 内，由素数密度我们可以知道，$r'-l'=\mathcal{O}(t\ln n)$。因此我们暴力的范围最终很小，像上面那样再做双指针即可。

时间复杂度 $\mathcal{O}(L+\dfrac{n^2}{L^2}\ln n\operatorname{check}(n))$，其中 $\operatorname{check}(n)$ 为检验一个大数 $n$ 是否为质数的复杂度，假如我们用米勒拉宾算法来求质数，那么取 $L=n^{\frac{2}{3}}\log n$ 可以做到复杂度 $\mathcal{O}({n^\frac{2}{3}\log n})$（这里让 $\ln n$ 和 $\log n$ 同级）。

当然数字较大的时候一个一个判素数还是太笨蛋了，因为最终的暴力区间不会很大，因此可以考虑使用筛区间质数的方法，即：假如我们要筛 $[l,r]$ 内的质数，我们枚举 $\sqrt{r}$ 内的质数去更新当前区间的质数信息，显然枚举的质数个数不会很多。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,pre[5000005],prp[5000005],cnt;
bitset<100000005> f;
bitset<200005> chk;
void solve(int l,int r)
{
	chk.reset();
	// memset(chk,0,sizeof(chk));
	for(int i=1;i<=cnt&&prp[i]*prp[i]<=r;i++)
	{
		// cerr<<"????"<<i<<"\n";
		for(int j=(l+(prp[i]-1))/prp[i];j*prp[i]<=r;j++)
		{
			// cerr<<j*prp[i]<<"\n";
			chk[prp[i]*j-l]=1;
		}
	}
}
int findnxt(int x,int g)
{
	int i=x+1;
	while(chk[i-g]) i++;
	return i;
}
int findpre(int x,int g)
{
	int i=x-1;
	while(i>=2&&chk[i-g]) i--;
	return i;
}
bool check(int n)
{
	if(n==1) return 0; 
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0) return 0;
	}
	return 1;
}
signed main()
{
	cin>>n;
	for(int i=2;i<=20000000&&i<=n;i++)
	{
		if(!f[i]) prp[++cnt]=i;
		for(int j=1;j<=cnt&&i*prp[j]<=20000000&&i<=n;j++)
		{
			f[i*prp[j]]=1;
			if(i%prp[j]==0) break ;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		pre[i]=pre[i-1]+prp[i];
	}
	int l=1;
	if(n==1)
	{
		cout<<"NIE";
		return 0;
	}
	if(check(n))
	{
		cout<<n<<" "<<n;
		return 0;
	}
	for(int i=1;i<=cnt;i++)
	{
		while(l<i&&pre[i]-pre[l-1]>n) l++;
		if(pre[i]-pre[l-1]==n)
		{
			cout<<prp[l]<<" "<<prp[i]<<"\n";
			return 0;
		}
	}
	for(int i=2;i<=5000;i++)
	{
		int t=n/i;
		int base=20;
		if(i<=5) base=200;
		int LIM=max(t-max(i*base,100000ll),1ll);
		solve(LIM,t+max(i*base,100000ll));
		int r=findnxt(t,LIM);
		vector<int> pp;
		pp.emplace_back(r);
		if(r<=2e7) break ;
		int sum=r,cnt=1,l=r,it=0;
		while(cnt<i) l=findpre(l,LIM),sum+=l,cnt++,pp.emplace_back(l);
		// cerr<<"???"<<t<<" "<<l<<" "<<r<<"\n";
		reverse(pp.begin(),pp.end());
		while(sum<n) sum-=l,l=pp[++it],r=findnxt(r,LIM),sum+=r,pp.emplace_back(r);
		if(sum==n)
		{
			cout<<l<<" "<<r;
			cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC;
			return 0;
		} 
	}
	cout<<"NIE";
}
```

---

## 作者：robinyqc (赞：3)

做过最复杂的复杂度。

看到这个题的第一眼：这不就质数筛一下然后双指针吗。也就是，先把 $10^8$ 以内的质数筛出来，枚举区间右端点 $p_r$，找到满足 $\left(\sum_{i = l}^{r} p_i\right) \leq n$ 的最小的 $l$，判断是否有 $\left(\sum_{i = l}^{r} p_i\right) = n$ 即可。

仔细一想发现不是一眼题，以上做法复杂度 $O(n)$，而本题范围是 $n\leq 10^{11}$，还需要优化。

但是，可以发现，如果 $[1, 10^8]$ 以内的质数都不能凑出 $n$，那么和可以为 $n$ 的质数会在 $\Omega(10^8)$ 级别。而范围一大，数量就会小：最多 $1000$ 个 $10^8$ 级别的质数，它们的和等于 $n$。再多一定大于 $n$。

这启发我们设置一个阈值 $B$，先跑 $[1, B]$ 的质数看是否可行。如果不行，枚举质数个数 $x$（$1\leq x\leq \frac nB$），由于质数密度那套理论，质数大致是均匀的，可行的区间将会在 $\frac nx$ 左右。所以可以设置一个常数 $K$，只需要判断 $[\frac nx - K, \frac nx + K]$ 是否存在一个子区间质数和为 $n$。根据质数密度 $\frac 1{\ln n}$，$K$ 取 $x\ln n$。

怎么判断 $[L, R]$ 内是否存在子区间质数和为 $n$ 呢？显然可以类似开头的方法，筛出 $[L, R]$ 的质数，然后双指针。更具体地，枚举 $1\sim \sqrt R$ 的质数 $p$（开头筛过质数，这里可以直接用），和 Eratosthenes 筛一样，将 $[L, R]$ 内 $p$ 的倍数标记。最终未被标记的就是质数。复杂度分析和 Eratosthenes 筛一样，是 $O[(R - L)\ln\ln R]$ 的。加上前面枚举质数，总的复杂度是 $O[(R - L)\ln\ln R + \frac {\sqrt R}{\ln n}]$。

分析整个程序的复杂度：开始跑 $[1, B]$ 是 $O(B)$ 的，然后枚举 $x$，$O(\frac nB)$，判断区间是否可行，$O[x\ln n\ln\ln (\frac nx + x\ln n) + \frac {\sqrt{\frac nx + x\ln n}}{\ln n}]$。所以总复杂度是：

$$
O\left(B + \left(\frac nB\right)^2\ln n \ln\ln \left(B + \frac nB \ln n\right) + \frac {n\sqrt{B + \frac nB \ln n}}{B\ln n}\right)
$$

有点绕，可以仔细想想。恕我能力有限只能大概化成这样了，也许还存在更紧的界。你也可以理解为 $O(\text{能过})$。极值我也不会求，反正 $B = 10^8$ 稳过。


### 代码实现

实现复杂度可能和上文略有不同，但大致一样。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

#define LL long long

const int N = 100000000;

LL n;
bitset<N + 8> v;
bitset<100008> nv;
vector<int> p;

template<bool type, int len>
void solve(LL l, LL r, bitset<len>& b)
{
    if (type) {
        b.reset();
        for (LL i : p) {
            if (i * i > r) break;
            for (LL j = (l + i - 1) / i * i; j <= r; j += i) b.set(j - l);
        }
    }
    LL sum = 0, pl = l;
    for (LL i = l; i <= r; i++) {
        if (!b[i - l]) {
            sum += i;
            while (sum > n) {
                if (!b[pl - l]) sum -= pl;
                ++pl;
            }
            if (sum == n) {
                cout << max(pl, 1ll) << ' ' << i << '\n';
                exit(0);
            }
        }
    }
}

signed main() 
{
    cin >> n;
    p.reserve(min(n, (LL)N) / 14);
    v.set(1), v.set(0);
    for (int i = 2, q = min(n, (LL)N); i <= q; i++) {
        if (!v[i]) p.push_back(i);
        for (int j : p) {
            if (i * j > q) break;
            v.set(i * j);
            if (i % j == 0) break;
        }
    }
    solve<0, N + 8>(0, min(n, (LL)N), v);
    if (n > N) {
        for (int i = 1, ed = n / N; i <= ed; i++) {
            LL mid = n / i;
            solve<1, 100008>(max(1ll, mid - 50 * i), mid + 50 * i, nv);
        }
    }
    cout << "NIE\n";
    return 0;
}
```

---

## 作者：novax (赞：2)

#### 题意

给你一个数 $n$，找出一个区间 $[l,r]$ 使得该区间内的质数之和为 $n$。无解输出 ``NIE``。

#### 思路

首先合法区间的两端点没有必要是合数，为了方便，可以直接找到区间最靠近两端的两个质数作为端点。

考虑一个简单的思路：我们枚举每个质数作为区间的左端点，预处理全部质数的前缀和然后二分查找是否有满足条件的位置。这个做法在 $n$ 过大时显然是不可行的，但在 $n$ 较小时可以以 $k\log k$ 时间找出答案，其中 $k$ 是 $n$ 以内的质数数量。

考虑另一种思路：我们枚举答案区间包含的质数个数。假设枚举的质数个数为 $len$，那么由于答案是连续的一段区间，这 $len$ 个数一定是在 $\frac{n}{len}$ 附近的一段连续质数。因此我们只需要找出 $\frac{n}{len}$ 前后各 $len$ 个质数，求前缀和然后双指针判断是否存在可行的区间。这个做法缺点在于要枚举 $O(n)$ 次长度，每次还要进行大量的质数判断。

考虑结合一下上面两种做法：答案区间的质数较多，这些质数就越小。所以可以先用第一种算法，查找在较小的值域范围内是否有合法方案；然后再使用第二种算法，解决答案区间较小的情况。

因为算法二在找质数是需要大量的质数判断而很慢，因此两种做法间的阈值应足够大以平衡时间常数。

#### 代码

卡常卡了很久，使用了 ``miller-rabin`` 加速判定质数。

分治阈值 $2.4 \times 10^8$。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <deque>
#include <cstdlib>
const int Nx=240000005;
int prime[Nx/16],cnt;
long long N,sum[Nx];
std::vector<bool> isp;
long long pow(__int128 x,long long y,long long mod)
{
	if(y==0)
		return 1;
	x%=mod;
	__int128 ret=pow(x,y/2,mod);
	ret=(y&1)?ret*ret%mod*x%mod:ret*ret%mod;
	return ret;
}
bool isprime(long long n)
{
	if(n<3||n%2==0)
		return n==2;
	long long i,u=n-1,t=0,s;
	while(u%2==0) 
		u/=2,++t;
	for(i=0;i<8;++i)
	{
		long long a=rand()%(n-2)+2,v=pow(a,u,n);
		if(v==1)
			continue;
		for(s=0;s<t;++s) 
		{
			if(v==n-1)
				break;
			v=(__int128)v*v%n;
		}
		if(s==t)
			return 0;
	}
	return 1;
}
bool check(int d)
{
	int i;
	long long k,w,now;
	w=N/d;
	std::deque<long long> deq,sum;
	now=w;
	while(deq.size()<=d)
	{
		if(isprime(now))
			deq.push_back(now);
		now++;
	}
	if(deq.back()<Nx)
		return 0;
	now=w-1;
	while(now>1&&deq.size()<=2*d)
	{
		if(isprime(now))
			deq.push_front(now);
		now--;
	}
	deq.push_front(0);
	sum.resize(deq.size());
	sum[0]=0;
	for(i=1;i<deq.size();i++)
		sum[i]=sum[i-1]+deq[i];
	k=1;
	for(i=1;deq[i]<=w;i++)
	{
		//k=std::lower_bound(sum.begin()+i,sum.end(),sum[i-1]+N)-sum.begin();
		while(k+1<deq.size()&&sum[k+1]-sum[i]<=N)
			k++;
		if(sum[k]-sum[i-1]==N)
		{
			printf("%lld %lld\n",deq[i],deq[k]);
			return 1;
		}
	}
	return 0;
}
int main()
{
	isp.resize(Nx+5);
	int i,j,k;
	for(i=2;i<Nx;i++)
	{
		if(!isp[i])
			prime[++cnt]=i;
		for(j=1;j<=cnt&&prime[j]*i<Nx;j++)
		{
			isp[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
		}
	}
	for(i=1;i<=cnt;i++)
		sum[i]=sum[i-1]+prime[i];
	scanf("%lld",&N);
	k=1;
	for(i=1;i<=cnt;i++)
	{
		//k=std::lower_bound(sum+i,sum+cnt+1,sum[i-1]+N)-sum;
		while(k<=cnt&&sum[k+1]-sum[i]<=N)
			k++;
		if(sum[k]-sum[i-1]==N)
		{
			printf("%lld %lld\n",prime[i],prime[k]);
			return 0;
		}
	}
	if(isprime(N))
	{
		printf("%lld %lld\n",N,N);
		return 0;
	}
	k=0;
	for(i=2;i<=420;i++)
	{
		k=check(i);
		if(k)
			break;
	}
	fprintf(stderr,"%d\n",clock());
	if(k==0)
		printf("NIE\n");
}
```


---

