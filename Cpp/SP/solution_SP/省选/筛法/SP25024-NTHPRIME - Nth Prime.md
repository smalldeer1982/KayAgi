# NTHPRIME - Nth Prime

## 题目描述

There is no tedious description for this problem. You are just required to calculate and output the **Nth** prime number.

## 样例 #1

### 输入

```
4```

### 输出

```
7```

# 题解

## 作者：Leasier (赞：1)

前置芝士：[Meissel-Lehmer 算法](https://en.wikipedia.org/wiki/Prime-counting_function)

显然，第 $n$ 个质数就是满足 $\pi(p) = n$ 的最小 $p$，发现可以对 $p$ 二分答案。时间复杂度为 $O(n^{\frac{2}{3}} \log n + N + KM)$。

具体细节见代码注释。

代码：
```cpp
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;

const int N = 6e6 + 7, M = 7, K = 2 * 3 * 5 * 7 * 11 * 13 * 17;
int prime[N], pi[N], phi[K + 7][M + 7], product[M + 7];
bool p[N];
map<ll, ll> mp;

inline int init(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i < N; i++){
		if (!p[i]) prime[++cnt] = i;
		pi[i] = cnt;
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	product[0] = 1;
	for (register int i = 0; i <= K; i++){
		phi[i][0] = i;
	}
	for (register int i = 1; i <= M; i++){
		product[i] = product[i - 1] * prime[i];
		for (register int j = 1; j <= K; j++){
			phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];
		}
	}
	return cnt;
}

inline ll sqrt(ll n){
	ll ans = sqrt((double)n);
	while (ans * ans <= n) ans++;
	return ans - 1;
}

ll get_euler(ll n, ll m){
	if (m == 0) return n;
	if (m <= M) return phi[n % product[m]][m] + n / product[m] * phi[product[m]][m];
	if (n <= prime[m] * prime[m]) return pi[n] - m + 1;
	if (n <= prime[m] * prime[m] * prime[m] && n < N){
		ll t = pi[sqrt(n)], ans = pi[n] - (m + t - 2) * (t - m + 1) / 2;
		for (register ll i = m + 1; i <= t; i++){
			ans += pi[n / prime[i]];
		}
		return ans;
	}
	return get_euler(n, m - 1) - get_euler(n / prime[m], m - 1);
}

inline ll cbrt(ll n){
	ll ans = cbrt((double)n);
	while (ans * ans * ans <= n) ans++;
	return ans - 1;
}

ll prime_count(ll n){
	if (n < N) return pi[n];
	if (mp.count(n)) return mp[n];
	ll a = prime_count(cbrt(n)), b, c, t = sqrt(n), ans;
	b = prime_count(sqrt(t));
	c = prime_count(t);
	ans = get_euler(n, b) + (b + c - 2) * (c - b + 1) / 2;
	for (register ll i = b + 1; i <= c; i++){
		ll x = n / prime[i];
		ans -= prime_count(x);
		if (i <= a){
			ll t = prime_count(sqrt(x));
			for (register ll j = i; j <= t; j++){
				ans -= prime_count(x / prime[j]) - (j - 1);
			}
		}
	}
	return mp[n] = ans;
}

inline ll get_nth_prime(ll n, ll max_ans, int cnt){
	if (n <= cnt) return prime[n];
	ll l = N, r = max_ans;
	while (l < r){
		ll mid = (l + r) >> 1;
		if (prime_count(mid) >= n){
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	return l;
}

int main(){
	int n, cnt;
	cin >> n;
	cnt = init();
	cout << get_nth_prime(n, 22801763489ll, cnt); // 22801763489 为第 10^9 个质数
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

用朴素 Min_25 水 Meissel-Lehmer 是真的快乐。

* **【题目链接】**

[Link:SP25024](https://www.luogu.com.cn/problem/SP25024)

* **【解题思路】**

首先请确保你可以在洛谷上 $5\textrm s$ 之内跑完 [Meissel-Lehmer 板子](https://www.luogu.com.cn/problem/P7884) 的数据范围，在我写这篇题解的时候这就意味着你可以通过 P7884。

首先我们只需要像 [SP26045](https://www.luogu.com.cn/problem/SP26045) 一样把 [P5493](https://www.luogu.com.cn/problem/P5493) 的 Min_25 中的除法改成乘法我们就可以在单点 $4.5\textrm s$ 之内跑过去 Meissel-Lehmer 板子。然后我们就可以拿它来做这题。

首先我们可以直接二分。然后你会发现它还是过不去。

然后考虑一个优化，当二分的区间很小时，我们其实需要确定的只有这个区间内每个数的素性，在这种情况下还用 Min_25 显然是不优的，于是当二分的区间长度小于 $10^5$ 时我们停止二分，暴力枚举区间里的数并使用 Miller-Rabin 判素。当然你用区间筛应该能跑的更快，如果用 Miller-Rabin 的话区间长度阈值似乎 $10^5$ 是最优的，多了少了都不行。

然后我们还是过不去。如果你对于这一类题做的比较多就应该做过 [SP3587](https://www.luogu.com.cn/problem/SP3587)，然后就容易联想到对于第 $i$ 个质数 $p_i$ 有估计 $p_i\approx i\ln i$ 且 $p_i\geq i\ln i$，然后我们把二分起始左端点设为 $i\ln i$。

然后就过了。

* **【实现细节】**

不知道为什么我这里要特判 $n=1$ 的情况，目前猜测是 $0$ 可以通过素性检验。

* **【代码实现】**

```cpp
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>

using namespace std;

typedef __int128 llint;

llint fast_pow(llint base,llint exp,llint prime)
{
    llint result;
    for(result=1;exp;exp&1?result=result*base%prime:true,base=base*base%prime,exp>>=1);
    return result;
}

array<long long,1000001>	DP_arr,blk_pos;
const array<__int128,8>		mprimes={2,3,5,7,37};
array<double,500001>		invp;
array<int,500001>			idx_sml,idx_lrg;
array<int,500000>			primes;
bitset<500001>				prime;
const int					primecnt=5;

bool miller_rabin(long long num)
{
	llint num_t=num-1,rem_odd;
	rem_odd=num_t;
	int power_2=0;
	while(rem_odd%2==0)
		rem_odd/=2,power_2++;
	for(int i=0;i<primecnt;i++)
	{
		if(num==mprimes[i])
			return true;
		if(num%mprimes[i]==0)
			return false;
		if(fast_pow(mprimes[i],rem_odd,num)==1)
			goto next_check;
		for(int j=0;j<power_2;j++)
			if(fast_pow(mprimes[i],rem_odd*fast_pow(2,j,num),num)==num-1)
				goto next_check;
		return false;
		next_check:;
	}
	return true;
}

long long Min_25_part1(long long n)
{
	long long tmp,range=sqrt(n);
	int blkcnt=0;
	for(long long i=1;i<=n;i=n/(n/i)+1)
	{
		tmp=n/i;
		blk_pos[++blkcnt]=tmp;
		DP_arr[blkcnt]=tmp-1;
		if(tmp<=range)
			idx_sml[tmp]=blkcnt;
		else
			idx_lrg[n/tmp]=blkcnt;
	}
	long long temp;
	for(int i=1;1ll*primes[i]*primes[i]<=n;i++)
		for(int j=1;1ll*primes[i]*primes[i]<=blk_pos[j];j++)
			tmp=blk_pos[j]*invp[i]+1e-6,DP_arr[j]=DP_arr[j]-DP_arr[tmp>range?idx_lrg[n/tmp]:idx_sml[tmp]]+i-1;
	return DP_arr[1];
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long range=sqrt(22801763489)+100;
	int cntp=0;
	for(int i=2;i<=range;i++)
	{
		if(!prime.test(i))
			primes[++cntp]=i,invp[cntp]=1.0/i;
		for(int j=1;j<=cntp&&i*primes[j]<=range;j++)
		{
			prime.set(i*primes[j]);
			if(i%primes[j]==0)
				break;
		}
	}
	long long target;
	cin>>target;
	if(target==1)
		return cout<<2,0;
	long long rgl=target*log(target),rgr=22801763489ll,mid;
	while(rgr-rgl>1e5)
	{
		mid=rgl+rgr>>1;
		if(Min_25_part1(mid)>=target)
			rgr=mid;
		else
			rgl=mid+1;
	}
	int curp=Min_25_part1(rgl);
	long long ptr=rgl;
	while(curp<target)
		ptr++,curp+=miller_rabin(ptr);
	cout<<ptr;
	return 0;
}
```

---

