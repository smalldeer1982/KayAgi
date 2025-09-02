# [USACO24JAN] Cowlendar S

## 题目描述

Bessie 在一个陌生的星球上醒来。这个星球上有 $N$（$1\le N\le 10^4$）个月，分别有 $a_1,\ldots,a_N$ 天（$1\le a_i\le 4\cdot 10^9$，所有 $a_i$ 均为整数）。此外，这个星球上还存在周，一周为 $L$ 天，其中 $L$ 是一个正整数。有趣的是，Bessie 知道以下事情：

- 对于正确的 $L$，每个月至少有 $4$ 周。
- 对于正确的 $L$，$a_i\bmod L$ 至多有 $3$ 个不同值。

不幸的是，Bessie 忘记了 $L$ 是多少！请通过输出 $L$ 的所有可能值之和来帮助她。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**

## 说明/提示

### 样例解释 1

$L$ 的可能值为 $1$，$2$，$3$，$4$，$5$，$6$ 和 $7$。例如，$L=7$ 是合法的，因为每个月的至少有 $4\cdot 7=28$ 天，且每个月的天数模 $7$ 的余数均为 $0$，$2$ 或 $3$。

### 样例解释 2

$L$ 的可能值为 $1$，$2$，$3$，$4$，$6$ 和 $7$。例如，$L=6$ 是合法的，因为每个月的至少有 $4\cdot 6=24$ 天，且每个月的天数模 $6$ 的余数均为 $1$，$4$ 或 $5$。

### 测试点性质

- 测试点 $3-4$：$1\le a_i\le 10^6$。
- 测试点 $5-14$：没有额外限制。

## 样例 #1

### 输入

```
12
31 28 31 30 31 30 31 31 30 31 30 31```

### 输出

```
28```

## 样例 #2

### 输入

```
4
31 35 28 29```

### 输出

```
23```

# 题解

## 作者：EricWan (赞：33)

我们充分发扬人类智慧：

假如一个数不是合法的 $K$ 则它的倍数也不是。

根据数学直觉，虽然 $K\in[1,10^9]$，$K$ 的质因数有极大概率均小于等于 $10^7$。

所以我们线性筛 $10^7$ 中的所有质数，之后对于每一个质数 $p$ 找到最大的 $pow_p$ 使得 $p^{pow_p}\in\{K\}$，那么合法的 $K$ 就最多有 $\prod (pow_p+1)$ 个。

再次根据数学直觉，$\prod (pow_p+1)$ 不会很大，DFS 一遍即可，DFS 过程中记得剪枝。

这样速度快得飞起，在 $n=10000$ 时都可以在 200ms 内过。

> Q&A：
> 
> Q1：每次判断一个数是否是合法的 $K$ 是 $O(n)$ 复杂度的，怎么办？
> 
> A1：首先，我们对天数排重，如果这个数是合法的 $K$，的确是 $O(n)$ 的，但是如果不是，前几个数就可以让余数数量很多，直接跳出即可。
> 
> Q2：我这样写了，但是只有 65 分，怎么办？
> 
> A1：是的，上面的逻辑很难卡掉，但是还是有漏洞，对于**天数的取值只有小于等于三个**时，$[1,\frac{\max_{i=1}^na_i}4]$ 中的整数都是合法的 $K$，因此，我们特判这种情况，就可以过了。

求赞

---

## 作者：Cuiyi_SAI (赞：20)

## $\large{\text{Question}}$

给定 $n\in [1,10^4]$ 个数 $a_i\in [1,4\cdot 10^9]$，问对于所有满足要求的 $L$ 的和是多少。

- $4\cdot L<=\min(a_i)$
- 对于所有的 $a_i\bmod L$，最多只有三个不同的值。

## $\large{\text{Solution}}$


第一条限制很容易，只需要枚举 $L\in [1,\frac{\min(a_i)}{4}]$ 即可，主要是第二条。

显然去重不会影响答案（因为去重后 $L$ 对每个 $a_i$ 的余数种类不变），所以先去个重。

有个简单的小结论，若 $a_i\equiv a_j\pmod L$，则有 $a_i-a_j\equiv 0\pmod L$，也就是说 $L\mid a_i-a_j$。因此**合法的 $L$ 只可能是序列中某一对同余的 $(a_i,a_j)$ 的差的因数**。所以固然我们可以不用从 $L$ 的值域来枚举，直接枚举这些差的因数就会节省大量时间。

但是我们并不知道哪些 $(a_i,a_j)$ 会是同余的呀，就只好 $O(n^2)$ 枚举这些数对了吗？

其实可以利用鸽巢原理来优化，合法的 $L$ 只会产生 $3$ 种余数，**因此前 $4$ 数个中必定有至少一对是同余的**，我们**只需要在前 $4$ 个数中枚举肯定能枚举出所有同余的情况**（如果前 $4$ 个数漏掉了某一种同余，那么前 $4$ 个数的余数肯定互不相同，与限制二不符）。

如上枚举方法是 $O(\sqrt{V})$ 的，即可保证每一个合法的 $L$ 都会被选到，并且大大优化了时间。

枚举出 $L$ 以后，就可以 $O(n)$ 的判断是否满足限制了。算法复杂度是 $O(n\sqrt{V})$，$V$ 为 $a$ 的值域，显然卡不满。

建议还是有不懂的人可以去看看 USACO 的官方题解，讲得深入而详细——反正对我有很大帮助。

## $\large{\text{Code}}$


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[10010],minn=1e15,len;
set<int> s;
bool check(int x){
    set<int> ch;
    for(int i=1;i<=len;i++){
        ch.insert(a[i]%x);
        if(ch.size()>3) return false;
    }
    return true;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],minn=min(minn,a[i]);
    sort(a+1,a+1+n);
    len=unique(a+1,a+1+n)-a-1;
    if(len<=3){
        cout<<1ll*(minn/4)*(minn/4+1)/2;
        return 0;
    }
    for(int i=1;i<=4;i++){
        for(int j=i+1;j<=4;j++){
            int num=abs(a[j]-a[i]);
            for(int k=1;k*k<=num;k++){
                if(num%k!=0) continue;
                if(k*4>minn) break;
                if(check(k)) s.insert(k);
                if((num/k)*4<=minn&&check(num/k)) s.insert(num/k);
            }
        }
    }
    int ans=0;
    for(auto i:s) ans+=i;
    cout<<ans;
    return 0;
}
```

---

## 作者：zhanglh (赞：5)

考虑枚举。数据范围太大了，考虑降低枚举量。

先对序列 $a$ 去重，对答案没有影响。观察到，要求不同的 $a_i \bmod L$ 的数量不超过 $3$。因此，根据鸽巢原理，对于 $1 ≤ i, j ≤ 4$，必然存在 $a_i \equiv a_j \pmod L$。转化一下，有 $L | a_i - a_j$。

对于去重后大于等于 $4$ 的 $n$，求 $\operatorname{abs}(a_i - a_j), 1 ≤ i, j ≤ 4$ 的所有因数。这样就得到了所有可能的 $L$，再判断一下是否合法。

对于去重后小于 $4$ 的 $n$，那么一定满足不同的 $a_i \bmod L$ 的数量不超过 $3$，输出 $\min \lfloor a_i / 4 \rfloor$ 就可以了！

```
#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 10010;
const ll inf = 1e18;

ll n, a[N];
set<ll> L;

inline void calc(ll x)
{
    for (ll i = 1; i <= x / i; i ++ )
    {
        if (x % i == 0)
        {
            L.insert(i);
            L.insert(x / i);
        }
    }
}

inline bool check(ll x)
{
    set<ll> s;
    for (ll i = 1; i <= n; i ++ )
    {
        if (x * 4 > a[i]) return false;
        s.insert(a[i] % x);
        if (s.size() > 3) return false;
    }
    return true;
}

int main()
{
    cin >> n;
    ll minx = inf;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> a[i];
        minx = min(minx, a[i]);
    }
    sort(a + 1, a + n + 1);
	n = unique(a + 1, a + n + 1) - a - 1;
    if (n <= 3)
    {
        ll t = minx / 4, sum = 0;
        for (int i = 1; i <= t; i ++ ) sum += i;
        cout << sum << endl;
    }
    else
    {
        for (int i = 1; i <= 4; i ++ )
            for (int j = i + 1; j <= 4; j ++ ) calc(abs(a[i] - a[j]));
        ll sum = 0;
        for (ll i : L)
            if (check(i)) sum += i;
        cout << sum << endl;
    }
    return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：4)

[博客食用更佳](https://www.cnblogs.com/lemon-cyy/p/18010713)

### 题意简述

原题已经很简了，没有什么简述的必要了。

### 思维路径
请注意本题解可以保证正确性但不保证如果有极端的 Hack 数据能够通过。

拿到这道题上来的暴力想必是很容易的，即枚举每个 $L$ 判断是否合法。

接着我们就考虑优化，减少需要枚举的 $L$ 的量。题目中要求余数最多有 $3$ 种，而余数相同对的数相减所得的数的约数才有可能作为 $L$。

我们对 $a$ 数组进行排序，则由于抽屉原理，最小的四个数一定有两个是同余的，枚举他们的差的约束，如果算过就直接跳过，否则就暴力算是否满足。如果存在一个数是满足上述条件的，那么它的约数就一定也满足，可以直接标记。

在目前的数据下这个做法是可以通过的，但是要是这个差很大就 emmmm。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100009;
ll n,a[N],nn,ans,x;
map<ll,ll> ok,vst;

void input(){
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(ll i=1,j=1;i<=n;i++){
		if(a[i]==a[i-1]) continue;
		a[j]=a[i]; nn=j; j++;
//		cout<<a[j];
	}
	n=nn;
}

void cal(ll u){
	vst.clear();
	ll cnt=0;
	for(ll i=1;i<=n;i++){
		if(!vst[a[i]%u]) cnt++;
		vst[a[i]%u]=1;
	}
	if(cnt<=3){
		for(ll i=1;i*i<=u;i++){
			if(u%i) continue;
			if(!ok[i]) ans+=i;
			ok[i]=1;
			if(!ok[u/i]) ans+=u/i;
			ok[u/i]=1;
		}
	}
}

void solve(){
	if(n<=3){
		cout<<(1+a[1]/4)*(a[1]/4)/2;
		return;
	}
	ok[1]=ok[2]=ok[3]=1; ans=6;
	x=a[2]-a[1];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	x=a[3]-a[1];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	x=a[4]-a[1];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	x=a[3]-a[2];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	x=a[4]-a[2];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	x=a[4]-a[3];
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			if(x/i<=a[i]/4&&(!ok[x/i])) cal(x/i);
			if(i<=a[i]/4&&(!ok[i])) cal(i);
		}
	}
	cout<<ans;
}

int main(){
	input();
	solve();
	return 0;
}
```

---

## 作者：hytallenxu (赞：4)

## 观前提示
本题解**并不一定是**正解。如需正解还请观看其他的题解。这份题解主要是提供一种**选手赛时容易想到的思路**。

## 题目大意
有 $n$ 个数 $a_1 \dots a_n$。

有以下条件：

1. $a$ 数组的所有数必须 $\ge x\times 4$。
2. $a_i \bmod x$ $(1 \le i \le n)$ 的不同值不能超过 $3$ 个。

求所有符合条件的 $x$ 的和。

## 思路
暴力搜索，枚举答案。

设 $mini$ 为 $\min \{a_1 \dots a_n \} \div 4$。

首先，我们先从 $1$ 枚举到 $10^6$，假如 $\ge$ $mini$ 就退出。

接下来剩下来的情况就是 $mini$ $\ge 10^6$ 的情况了。

我们枚举每一对 $a_i, a_j$，假如他们的差值大于 $10^6$ 的话就做如下操作：

枚举断点 $k$，假如 $(a_j - a_i) \bmod k=0$ 的话，就把 $(a_j-a_i) \div k$ 存入一个数组 $brr$。

接着，枚举 $brr$ 里的每个数，然后再暴力验证答案即可。

## Code
代码私聊可以获得。

---

## 作者：masonpop (赞：3)

对此题的难度不予评价。

设值域为 $V$。朴素的枚举 $O(nV)$ 的，考虑如何减少枚举量。这里有一个关键点，就是如果去重后前四个元素都满足要求，那么设当前枚举到 $x$，必存在 $1\le i<j\le 4$ 满足 $x\mid(a_i-a_j)$。证明提一句，就是如果只能有三种不同余数，那么根据鸽笼原理，必存在 $i,j$ 使得 $(a_i\operatorname{mod}x)=(a_j\operatorname{mod}x)$，相减即是上式。

那么 $x$ 的范围就被大大缩小了。而熟知的 $d(x)\le 2\sqrt x$，因此复杂度就降到了 $O(n\sqrt V)$。当然这是一个很松的上界，实际是跑不满的。[代码](https://www.luogu.com.cn/paste/8tlfhof2)。

---

## 作者：1234567890regis (赞：2)

# 思路分析：

本题很难，本人的代码也不是一般的长，但是是很好理解的。

不难发现，因为 $a_1,a_2,\cdots,a_n \pmod L$ 中最多有三个不同值，所以根据抽屉原理，随便取四个数 $a_1,a_2,a_3,a_4$ 中必有一对 $a_i,a_j$ 使得 $a_i \equiv a_j \pmod L$，即 $L \mid a_i - a_j$。

于是我们可以找出所有 $C_4^2=6$ 个数的约数，$L$ 必在这里面。

然后我们再取四个数，$L$ 必在两个集合的交集中。最后枚举所有的 $L$ 即可。

# AC 代码：

你可能不相信，但这是赛时代码，3.2 KB，用一个小时打出来的，并且 AC 了。

```cpp
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#define int long long
using namespace std;

const int MAXN = 1e4 + 7;
int a[MAXN], mn_month = (long long)(9e18); // mn_month 代表天数最少的月的天数
vector<int> diff, might, might1, might2, primes;

int qpow(int a, int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res *= a;
		b >>= 1;
		a *= a;
	}
	return res;
}

void remove_same(vector<int>& n) // 此处可以用 unique 函数
{
	if (n.size() == 0) return;
	sort(n.begin(), n.end());
	vector<int> res;
	res.push_back(n[0]);
	for (int i = 1; i < n.size(); i++) if (n[i - 1] != n[i]) res.push_back(n[i]);
	n = res;
}

void get_all_divisors(vector<int>& ans, vector<pair<int, int> > pr, int depth = 0, int now_num = 1) // 求 num 的所有约数
{
	if (depth >= pr.size()) {
		if (now_num <= mn_month / 4) ans.push_back(now_num);
		return;
	}
	for (int i = 0; i <= pr[depth].second; i++)
	{
		get_all_divisors(ans, pr, depth + 1, now_num * qpow(pr[depth].first, i));
	}
}

std::vector<int> Euler_Sieve(const int& n) // 欧拉筛素数
{
	std::vector<int> primes;
	std::vector<bool> is_prime(n);
	for (int i = 2; i < n; i++)
		is_prime[i] = true;
	for (int i = 2; i < n; i++)
	{
		if (is_prime[i])
			primes.push_back(i);
		for (int j = 0; j < primes.size() && primes[j] * i < n; j++)
		{
			is_prime[primes[j] * i] = false;
			if (!(i % primes[j]))
				break;
		}
	}
	return primes;
}

vector<pair<int, int> > prime_fac(int n) // 对 n 分解质因数
{
	vector<pair<int, int> > ret;
	for (int i = 0; i < primes.size(); i++)
	{
		int cnt = 0;
		while (n % primes[i] == 0) cnt++, n /= primes[i];
		if (cnt != 0) {
			ret.push_back(make_pair(primes[i], cnt));
		}
	}
	return ret;
}

signed main()
{
	primes = Euler_Sieve(70000);
	int n;
	cin >> n;
	bool t = false;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		mn_month = min(mn_month, a[i]);
		if (t) continue;
		if (diff.size() >= 8) t = true;
		bool isin = false;
		for (int j = 0; j < diff.size(); j++) if (a[i] == diff[j])
		{
			isin = true;
			break;
		}
		if (!isin) {
			diff.push_back(a[i]);
		}
	}
	if (diff.size() <= 3) { // 如果本来就只有少于三个月的天数不同
		cout << (mn_month / 4) * (mn_month / 4 + 1) / 2;
		return 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j) continue;
			get_all_divisors(might1, prime_fac(abs(diff[i] - diff[j])));
		}
	}
	remove_same(might1);
	if (diff.size() >= 8) {
		for (int i = 4; i < 8; i++)
		{
			for (int j = 4; j < 8; j++)
			{
				if (i == j) continue;
				get_all_divisors(might2, prime_fac(abs(diff[i] - diff[j])));
			}
		}
		remove_same(might2);
		for (int i = 0; i < might1.size(); i++) {
			bool found = false;
			for (int j = 0; j < might2.size(); j++)
			{
				if (might1[i] == might2[j]) {
					found = true;
					break;
				}
			}
			if (found) might.push_back(might1[i]);
		}
		remove_same(might);
	}
	else {
		might = might1;
	}
	int cnt = 0;
	for (int i = 0; i < might.size(); i++)
	{
		bool t = true;
		vector<int> dif;
		for (int j = 0; j < n; j++)
		{
			if (!t) break;
			if (dif.size() >= 4) t = false;
			bool isin = false;
			for (int k = 0; k < dif.size(); k++) if (a[j] % might[i] == dif[k]) {
				isin = true;
				break;
			}
			if (!isin) dif.push_back(a[j] % might[i]);
		}
		if (t) cnt += might[i];
	}
	cout << cnt;
}
```

---

## 作者：Jerrywang09 (赞：1)

很有意思的数学题。

一个很显然的结论：将原序列**去重**不会影响答案。

本题的核心是枚举，考虑如何减少枚举量。因为 $a_i \bmod L$ 最多有 $3$ 个不同值，所以如果 $L$ 是合法的，由鸽巢原理得 $a_1\sim a_4$ 中一定能找到 $a_i\equiv a_j\pmod L$。

移项得 $a_i-a_j\equiv 0\pmod L$，因此 $L|a_i-a_j$。枚举 $1\le i,j\le 4$，再枚举 $a_i-a_j$ 的所有因数，就一定能枚举到所有可能的 $L$。然后验证即可。

如果去重后还剩 $\le 3$ 个数，令 $x=\min \lfloor a/4 \rfloor$，则 $L$ 可以取 $1\sim x$ 任意一数。

```cpp
// Title:  Cowlendar
// Source: USACO24JAN Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=10010;
using namespace std;

int n; ll a[N];
vector<ll> d;
void Divisor(ll x)
{
    d.clear();
    for(ll i=1; i*i<=x; i++)
        if(x%i==0)
        {
            d.push_back(i);
            if(i*i!=x) d.push_back(x/i);
        }
}
bool ok(ll x)
{
    set<ll> S;
    rep(i, 1, n)
    {
        if(x>a[i]/4) return 0;
        S.insert(a[i]%x);
        if(S.size()>3) return 0;
    }
    return 1;
}

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%d", &n);
    rep(i, 1, n) scanf("%lld", a+i);
    sort(a+1, a+n+1); n=unique(a+1, a+n+1)-a-1;
    if(n<=3)
    {
        ll x=a[1]/4;
        printf("%lld", x*(x+1)/2);
        return 0;
    }
    set<ll> res;
    rep(i, 1, 4) rep(j, i+1, 4)
    {
        ll delta=abs(a[i]-a[j]);
        Divisor(delta);
        for(ll x:d) if(ok(x)) res.insert(x);
    }
    ll s=0; for(ll x:res) s+=x;
    printf("%lld", s);
    
    return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

看到这道题，我们会发现 $N$ 的范围很大，直接枚举是不行的。但是题目中有这样一句话：
- 对于正确的 $L$，$a_i\bmod L$ 至多有 $3$ 个不同值。

因此，考虑对 $a$ 去重，根据抽屉原理，对于 $1\le i,j\le 4$，必然有 $a_i\equiv a_j\pmod L$，也就是说 $L\mid(a_i-a_j)$。

所以，我们对所有 $1\le i,j\le4$ 的 $\mid a_i-a_j\mid$ 求因数，就可以得到所有可能的 $L$。最后暴力判断一下每个 $L$ 是否合法，累加答案即可。

但如果去重后 $a$ 的长度 $\le3$，那么一定满足不同的 $a_i\bmod L$ 的数量不超过 $3$，所以 $1$ 到 $\lfloor\frac{\min\{a_i\}}{4}\rfloor$ 的每一个数都可以作为合法的 $L$，累加即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const int N=1e4+5;
int n;
LL a[N];
set<LL>s;
void C(LL x){
  for(LL i=1;i*i<=x;i++){
    if(x%i)continue;
    s.insert(i);
    s.insert(x/i);
  }
}
bool P(LL x){
  set<LL>t;
  for(int i=1;i<=n;i++){
     if(a[i]<4*x){
      return 0;
     }
     t.insert(a[i]%x);
     if(t.size()>3){
      return 0;
     }
  }
  return 1;
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
  }
  sort(a+1,a+n+1);
  n=unique(a+1,a+n+1)-a-1;
  if(n<4){
    LL t=a[1]/4;
    cout<<t*(t+1)/2,exit(0);
  }
  for(int i=1;i<=4;i++){
    for(int j=1;j<=4;j++){
      C(abs(a[i]-a[j]));
    }
  }
  LL c=0;
  for(auto x:s){
    P(x)&&(c+=x);
  }
  cout<<c;
  return 0;
}
```

---

## 作者：Little_Cabbage (赞：0)

# 解题思路

暴力的方法非常显然意见，可以尝试去优化暴力算法。

由题意可知，将 $a$ 数组去重是对最终答案没有影响的，所以可以现将 $a$ 数组去重。

如果数组 $a$ 去重后就满足了题目的要求，即 $a$ 数组里的元素个数 $\le 3$，直接输出从 $1$ 到 $a$ 的最小值的和即可。

由抽屉原理可得，对于一个满足题意的 $L$，在数组的前 $4$ 个元素中，至少由 $2$ 个数同余于 $L$，也就是 $L \bmod |a_i - a_j| = 0$，其中 $a_i,a_j \in \{x|1\le x\le4\}$ 且 $a_i \ne j$。可以枚举 $|a_i - a_j|$ 的因数，然后判断即可。

时间复杂度：$O(n\times \sqrt{\max a_i})$。

---

## 作者：joe_zxq (赞：0)

# Part 1 - 算法思路

首先想到暴力枚举 $L$，喜提通过 $4$ 个测试点的好成绩。于是，我们思考如何降低枚举量。

第一步，给 $a$ 去重。当 $a$ 中相同元素比较多的时候就会起到很大的作用。

第二步，运用我们伟大无需多言的抽屉原理。因为 $a_i\bmod L$ 至多有 $3$ 个不同值，所以对于 $1 \le i,j \le 4$，必然有 $a_i \equiv a_j \pmod{L}$，即 $L \mid \operatorname{abs}(a_i-a_j)$。

设 $m$ 为去重后 $a$ 的长度。若 $m \le 3$，设 $x$ 为 $a$ 中的最小值，则 $1,2,\dots ,\left \lfloor \frac{x}{4} \right \rfloor $ 均为合法的 $L$。

若 $m > 3$，则对于 $1 \le i,j \le 4$，分别检验 $\operatorname{abs}(a_i-a_j)$ 的因子是否合法。

# Part 2 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, a[1000005], mn = 1e18, ans = 0;
set<ll> s;

void primefactor(ll x) {
	for (ll i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			s.insert(i);
			s.insert(x / i);
		}
	}
}

bool check(ll l) {
	set<ll> mod;
	for (ll i = 1; i <= n; i++) {
		mod.insert(a[i] % l);
		if (l * 4 > a[i] || (ll)mod.size() > 3) {
			return 0;
		}
	}
	return 1;
}

int main() {

	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		mn = min(mn, a[i]);
	}
	sort(a + 1, a + n + 1);
	n = unique(a + 1, a + n + 1) - a - 1;
	if (n <= 3) {
		ll num = mn / 4;
		printf("%lld", num * (num + 1) / 2);
	} else {
		// Drawer principle
		for (ll i = 1; i <= 4; i++) {
			for (ll j = i + 1; j <= 4; j++) {
				primefactor(abs(a[i] - a[j]));
			}
		}
		for (ll l : s) {
			if (check(l)) {
				ans += l;
			}
		}
		printf("%lld", ans);
	}

	return 0;
}

```

# Part 3 - 警示后人

全是 $1 \le a_i \le 4 \cdot 10^9$ 惹的祸。

1. 因为 $4 \times 10^9 > 2147483647$，所以不开 long long 见祖宗。

2. 因为 $4 \times 10^9 > 2147483647$，所以最小值的初始值不能是 $2147483647$。

---

## 作者：Kevin911 (赞：0)

充分发扬人类智慧
## 思路
相同的数重复出现无意义，所以先去重。

设 $l$ 是一个正确的模数，如果取 $4$ 个数必然会有两个模 $l$ 同余，则这两个数的差是 $l$ 的倍数。

也就是在 $4$ 个数中选两个数，枚举它们差的因数，检查是否能是正确的模数，然后统计答案就行了。

算上常数，时间复杂度是 $O(6n\sqrt V)$，看似会爆炸的离谱，实际上跑的时候会减少很多的情况，跑得飞快。

 _talk is cheap,show me your code_
 
 ```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10010],b[4];
map<int,int> mp;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	int m=unique(a+1,a+n+1)-a-1,r=a[1]/4;
	if(m<=3)
	{
		cout<<(r+1)*r/2;
		return 0;
	}
	int ans=0;
	for(int i=1;i<=4;i++)
		for(int j=i+1;j<=4;j++)
		{
			int p=a[j]-a[i];
			for(int k=1;k*k<=p;k++)
			{
				if(p%k!=0) continue;
				if(k<=r&&!mp[k])
				{
					int cnt=0,flag=0;
					for(int l=1;l<=n;l++)
					{
						if(b[1]==a[l]%k||b[2]==a[l]%k||b[3]==a[l]%k) continue;
						b[++cnt]=a[l]%k;
						if(cnt>3)
						{
							flag=1;
							break;
						}
					}
					if(!flag) mp[k]=1,ans+=k;
				}
				if(k*k==p) break;
				if(p/k<=r&&!mp[p/k])
				{
					int cnt=0,flag=0;
					for(int l=1;l<=n;l++)
					{
						if(b[1]==a[l]%(p/k)||b[2]==a[l]%(p/k)||b[3]==a[l]%(p/k)) continue;
						b[++cnt]=a[l]%(p/k);
						if(cnt>3)
						{
							flag=1;
							break;
						}
					}
					if(!flag) mp[p/k]=1,ans+=p/k;
				}
			}
		}
	cout<<ans;
}
```


---

## 作者：Vindictae (赞：0)

# 题目思路
尝试分析数据范围，可以轻而易举的看出暴力方法。我们需要对暴力进行优化。

首先考虑将数组 $a$ 去重，应为没有影响。判断此时还有几个数，如果只有 $3$ 个，或者更少，那么就直接输出从 $1$ 到 $a$ 最小值的和即可（BS 学员提醒您：运算有风险，右移需谨慎；顺序不规范，代码两行泪）。

根据抽屉原理可得，对于一个合法的 $L$，在数组 $a$ 的前 $4$ 个元素中，至少有两个同余于 $l$。换句话说，就是 $L$ 整除 $|a_i - a_j|$（$i,j$ 表示 $1$ 至 $4$ 中的两个不同的数）。我们可以枚举 $|a_i - a_j|$ 的因数，判断即可。

时间复杂度：$O(n \times \sqrt{w})$（$w$ 表示值域）。
# AC Code
```cpp
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

using namespace std;

const int N = 1e4;

void init ();

int n;
int a[N + 5];
int _Mn = lnf, _Sm;
set <int> _St;

bool _Chck (int x) {
	set <int> _St_;
	
	for (register int i = 1; i <= n; ++ i) {
		if ((x << 2) > a[i]) {
			return 0;
		}
		
		_St_.insert (a[i] % x);
		
		if (_St_.size () > 3) {
			return 0;
		}
	}
	
	return 1;
}

int x;

signed main () {
	init ();
	cin >> n;
	
	for (register int i = 1; i <= n; ++ i) {
		cin >> a[i];
		_Mn = min (_Mn, a[i]);
	}
	
	sort (a + 1, a + n + 1);
	n = unique (a + 1, a + n + 1) - a - 1;
	
	if (n <= 3) {
//		cout << ((((_Mn * _Mn) >> 2) + _Mn) >> 3) << endl;
		cout << ((_Mn / 4) * (_Mn / 4) + _Mn / 4) / 2;
		return 0;
	}
	
	for (register int _ = 1; _ < 4; ++ _) {
		for (register int __ = _ + 1; __ <= 4; ++ __) {
			x = abs (a[_] - a[__]);
			
			for (register int i = 1; i <= x / i; ++ i) {
				if (x % i == 0) {
					_St.insert (i);
					_St.insert (x / i);
				}
			}
		}
	}
	
	for (int it : _St) {
		if (_Chck (it)) {
			_Sm += it;
		}
	}
	
	cout << _Sm << endl;
	return 0;
}

void init () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
}
```

---

