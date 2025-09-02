# Kuroni and the Punishment

## 题目描述

Kuroni is very angry at the other setters for using him as a theme! As a punishment, he forced them to solve the following problem:

You have an array $ a $ consisting of $ n $ positive integers. An operation consists of choosing an element and either adding $ 1 $ to it or subtracting $ 1 $ from it, such that the element remains positive. We say the array is good if the greatest common divisor of all its elements is not $ 1 $ . Find the minimum number of operations needed to make the array good.

Unable to match Kuroni's intellect, the setters failed to solve the problem. Help them escape from Kuroni's punishment!

## 说明/提示

In the first example, the first array is already good, since the greatest common divisor of all the elements is $ 2 $ .

In the second example, we may apply the following operations:

1. Add $ 1 $ to the second element, making it equal to $ 9 $ .
2. Subtract $ 1 $ from the third element, making it equal to $ 6 $ .
3. Add $ 1 $ to the fifth element, making it equal to $ 2 $ .
4. Add $ 1 $ to the fifth element again, making it equal to $ 3 $ .

The greatest common divisor of all elements will then be equal to $ 3 $ , so the array will be good. It can be shown that no sequence of three or less operations can make the array good.

## 样例 #1

### 输入

```
3
6 2 4```

### 输出

```
0```

## 样例 #2

### 输入

```
5
9 8 7 3 1```

### 输出

```
4```

# 题解

## 作者：I_am_Accepted (赞：35)

~~良心题解，管理员求过。~~

有任何关于此篇题解的问题皆可私信[我](https://www.luogu.com.cn/user/101868)。

### 题意简述

简述不了 qwq。

### 题目分析

设最终答案为 $ans$,即最少操作次数。

两个显而易见的结论：① **$ans$ 最大不超过 $n$**。

证明（反证）：

若 $ans>n$ 则，

**将序列中所有奇数都加 $1$，满足 $2$ 是它们全部的公因数，$2 \mid \gcd$，成立。**

此时操作数为原序列奇数个数，不大于 $n$，所以小于 $ans$，假设矛盾。

②**必有一半及以上的元素不变、加 $1$ 或减 $1$。**

证明（反证）：

若在 $ans$ 中没有一半及以上的元素不变、加 $1$ 或减 $1$ 则，

有一半以上的元素变化量至少为 $2$。

此时 $ans\leq n=2\times \frac{n}{2} <$ 操作数，此方法一定不是最优方案，假设矛盾。

若一个数在 $ans$ 中不变、加 $1$ 或减 $1$，将它加一减一，共 $3$ 个数（排除 $0$）**分别分解质因数，将质因数存入 $set$，其中必有一个素数是最终 $\gcd$ 的因数**。

而每个数在 $ans$ 中不变、加 $1$ 或减 $1$的概率不小于一半。

所以我们在序列中随机找一个数 $50$ 次，钦定它不变、加 $1$ 或减 $1$，作上述操作。

结束后我们 $set$ 里有至多 $600$ 个质数（每个数至多 $12$ 个），遍历每一个素数，**看看序列里每个数操作至该素数的倍数的最小操作数之和是否能更新 $ans$** 即可。

时间复杂度 $O(600N+10^6C)$ 除 $N$ 外均为常数

### Details

要是不对，原因是 $50$ 次随机找数找到的元素变化量均至少为 $2$。

概率小于 $\frac{1}{2^{50}}$ 你要是没过可以去买彩票了。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3fffffffffffffff
#define ll long long
#define FOR(i,j,k) for(register int i=j;(j<k)?(i<=k):(i>=k);i+=(j<k)?1:(-1))
#define IO ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 200010
#define C 1000000

int n;
ll ans=inf,sum;
ll a[N],pr[C/10];
set<ll> s;//要处理的素数集合 
bool p[C+1];
void init(){//埃氏筛素数（<=10^6） 
	FOR(i,2,C)p[i]=1;
	FOR(i,2,C){
		if(!p[i])continue;
		pr[++pr[0]]=i;
		for(ll j=1ll*i*i;j<=C;j+=i) p[j]=0;
	}
}
int Rand(int x,int y){//随机函数 
	int res=0;
	FOR(i,1,9)res=res*10+rand()%10;
	return x+res%(y-x+1);
}
void work(ll x){//质因数分解x后质因数插入set 
	FOR(i,1,pr[0]){
		if(x==1)break;
		if(x%pr[i]==0){
			x/=pr[i];
			s.insert(pr[i]);
		}
		while(x%pr[i]==0)x/=pr[i];
	}
	if(x>1)s.insert(x);
}
signed main(){
	srand(time(NULL));//seed 
    IO;
    init();
    cin>>n;
    FOR(i,1,n)cin>>a[i];
	int x;
	FOR(i,1,50){//50次，保险 
		x=Rand(1,n);
		//Δ=0/1/-1 
		work(a[x]+1);
		work(a[x]);
		if(a[x]>1)work(a[x]-1);
	}
	for(set<ll>::iterator it=s.begin();it!=s.end();it++){//遍历set 
		sum=0;
		FOR(i,1,n){
			if(a[i]<*it)sum+=*it-a[i];
			else sum+=min(a[i]%(*it),(*it)-a[i]%(*it));
		}
		ans=min(sum,ans);//update 
	}
	cout<<ans<<endl;
    return 0;
}

```

~~看完了，点个赞再走吧。~~

---

## 作者：xht (赞：10)

首先可以知道答案一定 $\le n$，这个界还可以再紧一点，一定 $\le$ 奇数的个数，设为 $t$。

考虑找到所有最终可能的 $\gcd$，随便找一个数 $x$，由于最多 $+t/-t$，因此这个 $x$ 最终只能在 $[a_i-t, a_i+t]$ 这个范围内，因此 $\gcd$ 也只能在这个范围内的数的质因数中。

我们对这个范围做区间筛，即可找到所有的质因数。具体而言，设这个区间为 $[l,r]$，则可能的 $\gcd$（即所有质因数）包括：

1. $2 \sim \sqrt r$ 内的所有质数，称为**小质数**。
2. 对于 $x \in [l,r]$，$x$ 超过 $\sqrt r$ 的质因数，而这个质因数最多只有一个，称为**大质数**。

把这些可能的 $\gcd$ 全部暴力 check，check 的时候剪枝就行了。

看起来复杂度不太对，但是实际上**长得很像答案的 $\gcd$** 最多只有 $12$ 个，其中 $10$ 个是小质数，$2$ 个是相邻的大质数。

```cpp
const int N = 2e5 + 7;
const ll M = 2e6;
int n;
bool v[M|1];
ll a[N];
vector<ll> p, q;

int main() {
	for (ll i = 2; i <= M; i++) {
		if (v[i]) continue;
		p.pb(i);
		for (ll j = i * i; j <= M; j += i) v[j] = 1;
	}
	q = p;
	rd(n), rda(a, n);
	sort(a + 1, a + n + 1);
	ll d = a[1];
	for (int i = 2; i <= n; i++) d = __gcd(d, a[i]);
	if (d != 1) return print(0), 0;
	ll t = 0;
	for (int i = 1; i <= n; i++) t += a[i] & 1;
	ll l = max(M + 1, a[n] - t), r = a[n] + t;
	map<ll, ll> w;
	for (ll i = l; i <= r; i++) w[i] = i; 
	for (ll x : p) 
		for (ll i = l / x * x; i <= r; i += x)
			if (i >= l) while (!(w[i] % x)) w[i] /= x;
	for (ll i = l; i <= r; i++)
		if (w[i] > M) q.pb(w[i]);
	for (ll x : q) {
		if (x == 2) continue;
		ll o = 0;
		for (int i = 1; i <= n; i++) {
			o += min(a[i] < x ? x : a[i] % x, x - a[i] % x);
			if (o >= t) break;
		}
		t = min(t, o);
	}
	print(t);
	return 0;
}
```

---

## 作者：Wen_kr (赞：7)

由于我们总能将每个数经过小于等于一次操作变成 $2$ 的倍数，因此我们能证明答案上界为 $n$。

接着我们可以证明一个结论：在最终的答案中，一定存在至少一半的元素，它们最多被操作过一次。

证明：若存在超过一半的元素被操作了多于一次，那么操作次数至少是 $\lceil\frac{n+1}{2}\rceil\times2>n$，这超过了答案上界。

因此，当我们随机一个元素时，这个元素将有至少 $\frac{1}{2}$ 的概率被最多操作一次。

我们考虑随机若干次元素，将这个元素不变/$+1$/$-1$分别做因数分解，然后对于每个因数计算答案，那么随机 $k$ 次的正确率就是 $1-\frac{1}{2^k}$。

当 $k$ 足够大时可以通过。

比赛时笔者写的是另一种做法：

随机一个元素，再随机一种操作，这样每次正确的概率是 $\frac{1}{6}$，实际上与上面的做法本质相同。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

inline LL mul(LL a, LL b, LL mod) {
	return (a * b - (LL)((long double)a / mod * b + 0.5) * mod + mod) % mod;
}

inline LL Pow(LL x, LL y, LL mod) {
	LL res = 1;
	for (; y; y >>= 1, x = (LL)mul(x, x, mod)) if (y & 1) res = mul(res, x, mod);
	return res;
}

const int _A[] = {2, 3, 5, 7, 11, 13, 131};

inline bool Miller_Rabin(LL n) {
	if (n == 1) return false;
	LL tmp = n - 1; int ct = 0;
	while (!(tmp & 1)) tmp >>= 1, ct++;
	for (int i = 0; i < 7; i++) {
		if (n == _A[i]) return true;
		LL a = Pow(_A[i], tmp, n), nxt = a;
		for (int j = 1; j <= ct; j++) {
			nxt = mul(a, a, n);
			if (nxt == 1 && a != 1 && a != n - 1) return false;
			a = nxt;
		}
		if (a != 1) return false;
	}
	return true;
}

inline LL _rand(LL x, LL c, LL mod) {
	return (mul(x, x, mod) + c) % mod;
}

inline LL _rand() {
	return (LL)rand() << 48 | (LL)rand() << 32 | rand() << 16 | rand();
}

inline LL _abs(LL x) {
	return x >= 0 ? x : -x;
}

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

inline LL Pollard_Rho(LL n) {
	LL s = 0, t = 0, c = _rand() % (n - 1) + 1, val = 1;
	for (int cir = 1; ; cir <<= 1, s = t, val = 1) {
		for (int i = 0; i < cir; i++) {
			t = _rand(t, c, n), val = mul(val, _abs(t - s), n);
			if (i % 127 == 0) {
				LL g = gcd(val, n);
				if (g != 1) return g;
			} 
		}
		LL g = gcd(val, n);
		if (g != 1) return g;
	}
}

vector<LL> divisors; 

inline void Factor(LL n) {
	if (n < 1) return ;
	if (n == 1) return;
	if (Miller_Rabin(n)) return divisors.push_back(n), void();
	LL d = n;
	while (d == n) d = Pollard_Rho(n);
	while (n % d == 0) n /= d;
	Factor(n), Factor(d);
}

int n;
long long seq[200050];
map<long long,int> mp,vis;

int mrand()
{
	return rand() << 15 | rand();
}

int main()
{
	srand((unsigned long long)(new char));
	scanf("%d",&n);
	int lim = 0;
	for(int i = 1;i <= n; ++ i)
	{
		scanf("%lld",&seq[i]);
		lim += seq[i] % 2;
	}
	int sz = 1000;
	for(int i = 1;i <= sz; ++ i)
	{
		int po = mrand() % n + 1;
		Factor(seq[po] + mrand() % 3 - 1);
		vis.clear();
		for(auto v : divisors)
		{
			if(v > 35)
			{
				if(vis[v]) continue;
				vis[v] = 1;
				mp[v] ++;
			}
		}
		divisors.clear();
	}
	for(long long j = 2;j <= 35; ++ j)
	{
		if(j > 1)
		{
			if(Miller_Rabin(j))
			{
				long long cur = 0;
				for(int k = 1;k <= n; ++ k)
				{
					long long val = seq[k] / j * j;
					if(!val)
					{
						cur += val + j - seq[k];
					}
					else
						cur += min(seq[k] - val,val + j - seq[k]);
					if(cur > lim)
						break;
				}
				lim = min(lim * 1ll,cur);
			}
		}
	}
	for(auto v : mp)
	{
		{
			long long j = v.first;
			long long cur = 0;
			for(int k = 1;k <= n; ++ k)
			{
				long long val = seq[k] / j * j;
				if(!val) cur += val + j - seq[k];
				else cur += min(seq[k] - val,val + j - seq[k]);
				if(cur > lim)
					break;
			}
			lim = min(lim * 1ll,cur);
		}
	}
	printf("%d\n",lim);
}
```

---

## 作者：JiaY19 (赞：3)

**[更好的阅读体验](https://www.cnblogs.com/mfeitveer/p/16665042.html)**

一道比较简单的题，我居然调了这么久。

### 思路

看一眼这个题，发现好像没有什么思路。

考虑来用一些巧妙的手法，比如随机化。

首先证明一个结论，至少有一半的数只会被操作一次或者不操作。

这个结论比较好证明。

可以知道，答案一定小于等于 $n$。

所以如果有超过一半的数会被操作两次。

那么这个答案必然不是最优的答案。

所以，我们可以随即选出一个数 $x$，将 $x$，$x+1$，$x-1$ 分解质因数，来判断这个质数是否可以更新答案，每次找到最优的概率是 $\dfrac{\ 1\ }{2}$。

这样，就可以随机找出 $\text{50}$ 个数来判断即可。

错误的概率为 $\dfrac{1}{\ 2^{50}\ }$。

### 一个细节

这个细节让我调了特别久。

当你在用 `rand` 调用随机数时，请不要这样写。

```cpp
x = rand() % n + 1;
```

请这样写。

```cpp
x = rand() * rand() % n + 1;
```

一个惨痛的教训。


### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 200010;
 
int n , ans , top , a[N] , stk[N];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
inline void calc(int x)
{
    for(int i = 2;i * i <= x;i++)
    {
        if(x % i == 0)
            stk[++top] = i;
        while(x % i == 0)
            x /= i;
    }
    if(x != 1) stk[++top] = x;
}
 
inline void solve(int x)
{
    int sum = 0;
    for(int i = 1;i <= n;i++)
        sum += min((a[i] >= x ? a[i] % x : (int)1e17) , x - a[i] % x);
    ans = min(ans , sum);
}
 
signed main()
{
    n = read() , srand(time(0));
    for(int i = 1;i <= n;i++)
        a[i] = read() , ans += (a[i] & 1);
    int res = 50;
    while(res--)
    {
        int x = rand() * rand() % n + 1;
        calc(a[x]) , calc(a[x] + 1) , calc(a[x] - 1);
    }
    sort(stk + 1 , stk + top + 1);
    top = unique(stk , stk + top + 1) - stk - 1;
    for(int i = 1;i <= top;i++) solve(stk[i]);
    cout << ans << endl;
    return 0;
}

```

---

## 作者：Sai0511 (赞：3)

首先证明 $2$ 个结论（其实显然易见）。   
1. 操作次数最多为 $n$，若 $\gcd=2$ 那么要改的数的数量就是序列中奇数的数量，最大为 $n$。      
2. 操作次数 $\geq 2$ 的数的数量一定 $\leq \frac{n}{2}$，根据结论 $1$ 可推出。     

所以说，一个随机化算法顺势而出了，把序列全部打乱，然后随机选 $k$个数，设选出的数的可重集合为 $S$，对于 $x \in S$，将 $x-1,x,x+1$ 分解质因数，算出要使 $\gcd$ 是它们的某一个质因数所需的最小的操作数，答案对其取 $\min$ 即可。       
因为对于 $x \in S$，$x$ 的操作数 $\geq 2$ 的概率最多为 $\frac{1}{2}$，所以错误的概率为 $\frac{1}{2^k}$。  
当 $k \geq 30$ 时一般不会出错。     
```cpp
#include <bits/stdc++.h>
#define int long long

const int N = 2e5 + 10;
const int M = 1e6 + 5;
typedef long long ll;

int n, m, i, j, k, tot;
int prim[M];
ll a[N];
bool vis[M];
std::map<ll, bool> infac;    
std::vector<ll> factors;   

inline void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      prim[++tot] = i;
    }
    for (int j = 1; j <= tot && i * prim[j] <= n; j++) {
      vis[i * prim[j]] = 1;
      if (i % prim[j] == 0) {
        break;    
      }
    }
  }
}       
inline void solve(ll x) {
  for (int i = 1; i <= tot && 1ll * prim[i] <= x; i++) {
    if (x % prim[i] == 0) {
      if (!infac[prim[i]]) {
        infac[prim[i]] = 1;
        factors.emplace_back(prim[i]);    
      }   
      while (x % prim[i] == 0) {
        x /= prim[i];  
      }
    }
  }
  if (x > 1) {
    if (!infac[x]) {
      factors.emplace_back(x);
      infac[x] = 1;
    }
  }
}
inline ll calc(int p) {
  ll res = 0;  
  for (int i = 1; i <= n; i++) {
    if (a[i] < p) {
      res += p - a[i];
    } else {
      res += std::min(a[i] % p, p - a[i] % p);
    }
  }
  return res;    
}

signed main() {
  srand(time(NULL));
  sieve(1e6);   
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  std::random_shuffle(a + 1, a + n + 1);   
  for (int i = 1; i <= std::min(n, 100ll); i++) {
    solve(a[i]);
    solve(a[i] - 1);
    solve(a[i] + 1);
  }       
  ll ans = n;
  for (auto p : factors) {
    ans = std::min(ans, calc(p));
  } 
  printf("%lld\n", ans);
  return 0;   
}
```

---

## 作者：stOqwqOrz (赞：1)

[LG CF1305F](https://www.luogu.com.cn/problem/CF1305F)

[CF1305F](https://codeforces.com/problemset/problem/1305/F)

**简要题意：**

- 给定 $n$ 个数，每次操作可以选择对于一个数 $+1$ 或者 $-1$，询问最小的操作数使得所有的数字的 $\gcd>1$

- $n\leq 2\times 10^5$，$a_i\leq 10^{12}$，$2.5s$，$250 \operatorname{MB}$ 

**题解：**

- 首先通过 $2$ 这个质数就可以使得操作次数 $\leq n$，这就意味在最终的答案中操作次数 $>1$ 的数不会超过一半

- 那么我们每次随机取一个数 $x$，将 $x,x-1,x+1$ 分解质因数，将分解出来的质数放入 `set` 中，最后对于 `set` 中的每个质数进行查询

- 假设取了 $num$ 个数，每次取到最终操作次数 $\leq 1$ 的数的概率为 $\frac{1}{2}$，那么这个算法最终正确的概率就是 $1-\frac{1}{2^{num}}$

- 时间复杂度为 $O(num\times (3\sqrt V+n))$，空间复杂度为 $O(n)$，正确率 $O(1-\frac{1}{2^{num}})$

**注意事项：**

- 随机函数可以考虑用 `mt19937`，`rand()` 函数的值域达不到 $2\times 10^5$

**参考代码：**

```cpp
const int N=1e6+10;
int a[N],n,vis[N];
set<int> s;
mt19937 rd(time(0));

signed main(){
//start at 16:34
//end at 16:43
#ifdef LOCAL
    Fin("1");
#endif
    srand(time(0));
    auto divide = [&] (int x) {
        for(int i=2;i<=sqrt(x);++i) {
            if(x%i) continue ;
            while(x%i==0) x/=i;
            s.insert(i);
        }
        if(x>1) s.insert(x);
    };
    n=read();FOR(i,1,n) a[i]=read();
    FOR(i,1,min(50,n)) {
        int x=rd()%n+1;
        while(vis[x]) x=rd()%n+1;
        vis[x]=1;
        divide(a[x]);divide(a[x]+1);if(a[x]!=1) divide(a[x]-1);
    }
    int ans=1e9;
    for(int x:s) {
        int res=0;
        FOR(i,1,n) {
            if(a[i]<x) res+=x-a[i];
            else res+=min(a[i]%x,x-a[i]%x);
        }
        ans=min(ans,res);
    }cout<<ans<<endl;
#ifdef LOCAL        
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
    return 0;
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1305F)

妙妙题！

首先答案显然不会超过奇数个数。

然后考虑答案上界最多为 $n$，所以至少有一半数至多被操作一次。

这个模型你肯定考虑质因数分解，但是 $a_i \le 10^{12}$，直接分解就寄了。

然后你会发现你不能对 $n$ 个数都分解，只能分解一小部分。

但是发现你只需要找到至多被操作一次的数 $x$，它只会变成 $x$ 或 $x-1$ 或 $x+1$，然后你对这三个数分解一下质因数，然后暴力匹配即可。

所以问题是怎么找到这样的数。

注意到这样的数在序列里至少有一半，所以你直接暴力随机个几十次你大概率就找到这样的数了。

假设你随机 $k$ 次，你不过的概率就是 $\dfrac{1}{2^k}$，然后你取个 $k=30$ 是不是就过了。

当然 $a_i \le 10^{12}$，所以处理质因数的时候最好写得好看点。比如埃氏筛。

做完了。

---

## 作者：墨舞灵纯 (赞：1)

### 题意

给定 $n$ 个数。每次可以选择将一个数 $+1$ 或 $−1$ 。求至少多少次操作使得整个序列全部元素的 $\gcd>1$

### 题解
我们意识到答案最多为奇数个数——因为你可以考虑把它们都变成偶数，就有了 $\gcd=2$ ，这显然是合法的。

考虑怎么让这个答案更小：我们发现每个数最多操作 $1$ 次，那么有 $\frac{1}{2}$ 的概率它被操作。那我们考虑随机一些数，对这些数进行 $+1,-1$ 操作或者不操作（也就是 $+0$ ）。由于最后整个序列的 $\gcd >1$ ，这个数被操作之后的某个质因子肯定是这个序列的 $\gcd$ ，那我们只需要把这些可能的 $\gcd$ 记录下来，一一检验最终 $\gcd$ 是某个 $d$ 时需要操作的最小次数就行了。

那么怎么证明这个做法的正确概率有保证呢？每个数有 $\frac{1}{2}$ 的概率被操作，假设我们随机了 $k$ 个数，正确率就是 $\frac{1}{2^k}$ ，把 $k$ 取在 $100$ 左右基本就是稳过了。由于每次分解因数最多是 $\sqrt{a_i}$ 的，总复杂度大概 $O(k*\sqrt{a_i})$ 。

### 代码

按照上述过程做即可。

---

## 作者：liuyongle (赞：1)

#### 题意简述：

> 给定长度为 $n$ 的数组 $a_i$。每次你可以花费 $1$ 的代价使 $a_i$ 加上或者减去 $1$。要求最小化代价使得所有 $a_i$ 都是质数 $k$ 的倍数。$n \leq 10^5,\ a_i \leq 10^{12}$。

#### 思路分析：

首先我们令 $k = 2$，得到 $ans \leq n$。也就是说，对于最优解的画面，至多有 $\lfloor \frac n 2 \rfloor$ 个整数的变化幅度超过 $1$。

设定阀值 $\omega$，我们随机从 $a_{1 \dots n}$ 中选择 $k$ 个数 $x_{1 \dots k}$，每次检查 $x-1,x,x+1$ 的每个质因子是否为答案。复杂度为 $O(n \sigma (a) \times \omega)$，正确率为 $ 1 - (\frac 1 2)^{\omega}$。

#### 细节分析：

1. 可以用通过 `clock()` 函数控制循环次数。本题时限2.50s，实测  `time_limit` 设为 0.10s 可通过本题。

2. 由于洛谷对于CF题目采用RemoteJudge方式评测，即将代码发回CF测评，考虑到CF采用windows环境评测，`rand()` 函数的取值范围在 $[0, 32767]$，考虑使用 `std::mt19937` 替代。

模板代码：

```cpp
std::mt19937 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
```

完整代码：

```cpp
#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
std::mt19937 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
const int N=2e5+10;
int n;
long long a[N];
std::set<long long> checked,calced;
long long check(long long x){
  if(checked.count(x))return LLONG_MAX;
  checked.insert(x);
  long long ans=0;
  for(int i=1;i<=n;i++)if(a[i]<=x){
    ans+=x-a[i];
  }else{
    ans+=std::min(a[i]%x,x-a[i]%x);
  }
  return ans;
}
long long calc(long long x){
  if(!x||calced.count(x))return LLONG_MAX;
  calced.insert(x);
  long long ans=LLONG_MAX;
  // printf("check %lld => ",x);
  for(long long i=2;i*i<=x;i++)if(x%i==0){
    ans=std::min(ans,check(i));
    while(x%i==0)x/=i;
  }
  if(x!=1)ans=std::min(ans,check(x));
  // printf("œ%lld\n",ans);
  return ans;
}
int main(){
#ifdef CF1305F
  freopen("data.in","r",stdin);
#endif
  read(n),srand(20040725);
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=n;i>=1;i--)std::swap(a[i],a[rand(1,i)]);
  long long ans=LLONG_MAX;
  for(int k=1;k<=n&&clock()/(double)CLOCKS_PER_SEC<.1;k++){
    ans=std::min(ans,calc(a[k]));
    ans=std::min(ans,calc(a[k]+1));
    ans=std::min(ans,calc(a[k]-1));
  }
  printf("%lld\n",ans);
}
```

---

## 作者：太阳起晚了呢 (赞：0)

### 解

先不管正负数，把负数加到 $1$ 肯定是没问题的，接下来考虑如何让 $\gcd>1$ 这个问题。

有一个非常直接的想法是，答案大小和 $\gcd$ 大小是否有关系，然后发现，答案至少是不会比 $n$ 还要大的

那么根据这个结论我们可以得到，最少有一半的元素都只进行了 $<2$ 次的操作，就得到了答案，那么对此我们可以考虑枚举答案。

具体地，每次随便挑一个数出来，对它上下浮动 $1$，再对得到的结果分解质因数存起来，然后这样重复个 $k$ 次，最后把分解出来的质数求一下答案取最小值就可以了。

显然这样子不正确的概率大概不会多于 $\frac{1}{2^k}$ 所以就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=2e5+10;
const int maxm=5e6+10;
bool vis[maxm];
int pri[maxm],tot;
set<int> s;
void getprim()
{
    for(int i=2;i<maxm;i++)
    {
        if(!vis[i]) pri[++tot]=i;
        for(int j=1;j<=tot && i*pri[j]<maxm;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
}
void gets(int x)
{
	for(int p=1;pri[p]*pri[p]<=x;p++)
	{
		if(x==1) break;
		if(x%pri[p]) continue;
		s.insert(pri[p]);
		while(x%pri[p]==0) x/=pri[p];
	}
	if(x>1) s.insert(x);
}
int Rand(int x,int y){
	int res=0;
	for(int i=1;i<=9;i++) res=res*10+rand()%10;
	return x+res%(y-x+1);
}
int ans,n,a[maxn];
signed main()
{
	srand(14314);
	getprim();
	//for(int i=1;i<=10;i++) cout<<pri[i]<<' ';
	//cout<<endl;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    int k=63;
    while(k--)
	{
		int x=Rand(1,n);x=a[x];
		if(x>1)gets(x);
		if(x+1>1)gets(x+1);
		if(x>2) gets(x-1);
	} 
	int res=5e17;
    for(auto u=s.begin();u!=s.end();u++)
    {
    	//if((double)clock()/CLOCKS_PER_SEC>=2.3) break;
        int tmp=0,x=*u;
       	
        for(int i=1;i<=n;i++)
        {
            tmp+=(a[i]>=x)?min(a[i]%x,x-a[i]%x):x-a[i];
            if(tmp>res) break;
        }
		//cout<<x<<' '<<tmp<<endl;
        res=min(res,tmp);
    }
    printf("%lld\n",res);
    return 0;
}
```

---

