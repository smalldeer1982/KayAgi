# Natlan Exploring

## 题目描述

You are exploring the stunning region of Natlan! This region consists of $ n $ cities, and each city is rated with an attractiveness $ a_i $ . A directed edge exists from City $ i $ to City $ j $ if and only if $ i < j $ and $ \gcd(a_i,a_j)\neq 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Starting from City $ 1 $ , your task is to determine the total number of distinct paths you can take to reach City $ n $ , modulo $ 998\,244\,353 $ . Two paths are different if and only if the set of cities visited is different.

## 说明/提示

In the first example, the five paths are the following:

- City $ 1\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 4\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 4\rightarrow $ City $ 5 $

In the second example, the two paths are the following:

- City $ 1\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $

## 样例 #1

### 输入

```
5
2 6 3 4 6```

### 输出

```
5```

## 样例 #2

### 输入

```
5
4 196 2662 2197 121```

### 输出

```
2```

## 样例 #3

### 输入

```
7
3 6 8 9 11 12 20```

### 输出

```
7```

## 样例 #4

### 输入

```
2
2 3```

### 输出

```
0```

# 题解

## 作者：zhouruoheng (赞：6)

dp 加容斥。

逐步推导，设 $f_i$ 为从 $1$ 到 $i$ 的方案数，按题意模拟就有：
$$
    f_1=1 
$$
$$
    f_i=f_i+f_j (1 \le j < i,\gcd(a_i,a_j)\neq 1)
$$
这样做是 $O(n^2)$ 的。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
const int N=2e5+5,mod=998244353,M=1e6+5;
int n;
int a[N];
int f[N];
int gcd(int x,int y)
{
    return y ? gcd(y,x%y) : x;
}
vector<int> g[M],h[N];
set<int> v;
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    f[1]=1;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=i-1;j++) 
            if(gcd(a[i],a[j])!=1) 
				f[i]=(f[i]+f[j])%mod;
    cout<<f[n]<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

考虑优化，不难发现我们其实并不在意具体的 $\gcd(a_i,a_j)$ 是啥，只要求不为 $1$，将 $a_i$ 质因数分解，$a_i$ 与 $a_j$ 是通过相同的质因数产生联系的。每次分解 $a_i$，找前面的位置进行转移。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
const int N=2e5+5,mod=998244353,M=1e6+5;
int n;
int a[N],f[N];
vector<int> g[M],h[N];
set<int> v;
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int x=a[1];
    for(int j=2;1ll*j*j<=n;j++)
    {
        if(x%j==0) 
        {
            g[j].push_back(1);
            while(x%j==0) x/=j;
        }
    }
    if(x>1) g[x].push_back(1);
    f[1]=1;
    for(int i=2;i<=n;i++)
    {
        int x=a[i];
        for(int j=2;1ll*j*j<=x;j++)
        {
            if(x%j==0) 
            {
                for(int k:g[j]) 
                {
                    if(v.count(k)==0) f[i]=(f[i]+f[k])%mod;
                    v.insert(k);
                }
                g[j].push_back(i);
                while(x%j==0) x/=j;
            }
        }
        if(x>1) 
        {
            for(int k:g[x]) 
            {
                if(v.count(k)==0) f[i]=(f[i]+f[k])%mod;
                v.insert(k);
            }
            g[x].push_back(i);
        }
        v.clear();
    }
    cout<<f[n]<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

但这样还是过不了。因为这最坏还是 $O(n^2)$ 的，随便就能卡掉。

然后不妨按质因数划分集合，设 $b_x$ 为质因数为 $x$ 的数产生的贡献。这样每次 $a_i$ 分解出 $x$ $f_i$ 只需要加上 $b_x$ 就行了。但是仅仅如此的话连样例都过不了。

考虑这样一组数据 $\mathtt{12,12}$。$i=1$，$f_1=1$，更新 $b$，有 $b_2=1,b_3=1$。$i=2$，$f_2=b_2+b_3=2$，但实际上是 $f_2=1$。

这里就是 $2$ 和 $3$ 重复算了，因为这里显然还要减去 $6$ 出现的次数 $1$。可知，当一个数有两个及以上的质因数时，会出现重复计算的情况。

如何避免这样情况呢？用容斥原理。

将 $a_i$ 质因数分解后，每个质因数**只取一次**相乘得到 $y$，取 $y$ 的所有约数放在动态数组 `g[a[i]]` 中。比如 `g[12]={2,3,6}`，这时候可以计算上面例子，$i=1$，有 $b_2=b_3=b_6=1$，$i=2$，有 $f_2=b_2+b_3-b_6=1$。

也就是说在每次更新 $f_i$ 时对于 `g[a[i]]` 中的每个元素 $x$，如果 $x$ 的质因数个数为奇数，说明要加上贡献，否则减去贡献。同样 $b_x$ 的更新也需要取 `g[a[i]]` 中的每个元素 $x$。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5,M=1e6+5,mod=998244353;
int n;
int a[N],b[M],f[N];
vector<int> g[M],h[M];
void divide1(int x,int id)
{
    for(int i=2;1ll*i*i<=x;i++)
    {
        if(x%i==0) 
        {
            h[id].push_back(i);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) h[id].push_back(x);
}
void divide2(int x,int id)
{
    x=1;
    for(auto t:h[id]) x*=t;
    for(int i=2;1ll*i*i<=x;i++)
    {
        if(x%i==0)
        {
            g[id].push_back(i);
            if(x!=i) g[id].push_back(x/i);
        }
    }
    if(x>1) g[id].push_back(x);
}
void solve()
{
    cin>>n;
    int mx=0;
    for(int i=1;i<=n;i++) cin>>a[i],mx=max(mx,a[i]);
    for(int i=2;i<=mx;i++) divide1(i,i),divide2(i,i);
    f[1]=1;
    for(int i=1;i<=n;i++)
    {
        for(auto x:g[a[i]])
        {
            if(h[x].size()&1) f[i]=(f[i]+b[x])%mod;
            else f[i]=(f[i]+mod-b[x])%mod;
        }
        for(auto x:g[a[i]]) b[x]=(b[x]+f[i])%mod;
    }
    cout<<f[n]<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：Super_Cube (赞：5)

# Solution

设 $dp_i$ 表示到 $i$ 的方案数。很明显的转移：$dp_i=\displaystyle\sum_{j=1}^{i-1}dp_j[\gcd(a_i,a_j)\ne 1]$，初始化 $dp_1=1$，答案为 $dp_n$。

设 $s_i=\displaystyle\sum_{j=1}^i dp_j$，那么 $dp_i=s_{i-1}-\displaystyle\sum_{j=1}^{i-1}dp_j[\gcd(a_i,a_j)=1]$。

直接上莫比乌斯反演：$dp_i=s_{i-1}-\displaystyle\sum_{j=1}^{i-1}dp_j\sum_{k\mid\gcd(a_i,a_j)}\mu(k)$。

所以枚举 $a_i$ 的因数 $k$，打个桶对 $k$ 累加 $j\in[1,i)$ 且 $k\mid a_j$ 的贡献 $dp_j$。

莫比乌斯函数值可提前预处理得到，每个数的所有约数直接根号暴力枚举。

时间复杂度：$O(n\sqrt V)$。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=998244353;
int mu[1000005];
int sum[1000005];
int n;
int main(){
	mu[1]=1;
	for(int i=1;i<=500000;++i)
		if(mu[i])
			for(int j=i<<1;j<=1000000;j+=i)
				mu[j]-=mu[i];
	scanf("%d",&n);
	for(int i=1,pre=0,dp,x;i<=n;++i){
		scanf("%d",&x);
		dp=(i==1?-1:0);
		for(int j=1;j*j<=x;++j)
			if(!(x%j)){
				if(mu[j])mu[j]==1?(dp+=sum[j])>=mod&&(dp-=mod):(dp-=sum[j])<0&&(dp+=mod);
				if(j*j!=x&&mu[x/j])mu[x/j]==1?(dp+=sum[x/j])>=mod&&(dp-=mod):(dp-=sum[x/j])<0&&(dp+=mod);
			}
		if((dp=pre-dp)<0)dp+=mod;
		if(i==n)return 0&printf("%d",dp);
		for(int j=1;j*j<=x;++j)
			if(!(x%j)){
				(sum[j]+=dp)>=mod&&(sum[j]-=mod);
				if(j*j!=x)(sum[x/j]+=dp)>=mod&&(sum[x/j]-=mod);
			}
		if((pre+=dp)>=mod)pre-=mod;
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：5)

观察到 $\gcd(i, j)$ 总是 $i$ 中一个或多个质因子倍数，而 $a_i\leq 1000000$，本质不同的质因子只有 $7$ 个，于是可以容斥。

具体思路如下：

每一轮取出 $a_i$，找到所有质因子，枚举每个选或者不选，然后预处理 $pre_k$ 表示 $\sum\limits_{j\in [1, i-1], a_j | k} f_j$，那么枚举完每个选或者不选后，当前情况可以 $O(1)$ 解答，算完 $f_i$ 后遍历所有因子更改 $pre$。

时间复杂度 $O(n\times\sqrt{a_i}+2^{w(1000000)}\cdot n)$，其中 $w(1000000)=7$，可以通过。

代码：


```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int a[1000005], f[1000005], pre[1000005];
vector <int> z[1000005], zz[1000005];
const int mod = 998244353;
signed main () {
	cin >> n;
	For (i, 1, n) {
		cin >> a[i];
		z[i].push_back (a[i]);
		int x = sqrt (a[i]);
		for (int j = 2; j <= x; j ++) {
			if (a[i] % j == 0) {
				z[i].push_back (j);
				if (j * j != a[i]) z[i].push_back (a[i] / j);
			}
		}
		int t = a[i];
		for (int j = 2; j <= x; j ++) {
			if (t % j == 0) {
				zz[i].push_back (j);
				while (t % j == 0) t /= j;
			}
		}
		if (t != 1) zz[i].push_back (t);
	}
	f[1] = 1;
	for (int j : z[1]) pre[j] = (pre[j] + 1) % mod;
	For (i, 2, n) {
		int sz = zz[i].size ();
		for (int j = 1; j < (1 << sz); j ++) {
			int num = 1, cnt = 0;
			For (k, 0, sz - 1) {
				if (j & (1 << k) ) {
					num = num * zz[i][k];
					++ cnt;
				}
			}
			if (cnt & 1) f[i] = (f[i] + pre[num]) % mod;
			else f[i] = (f[i] - pre[num] + mod) % mod;
		}
		for (int j : z[i]) pre[j] = (pre[j] + f[i]) % mod;
	}
	cout << f[n];
	return 0;
}

```

卡空间差评，害我吃罚时。

---

## 作者：Nt_Tsumiki (赞：3)

这不是我们 ARC185E 吗。

考虑沿用那一题的做法对于一个 $a_i$ 把他的非零因数上都加上 $f_i$，这样的话对于一个 $a_j$，我们去遍历他的非零因数并且希望只会在 $\gcd(a_i,a_j)$ 处得到一个 $f_i$ 的贡献，考虑容斥。

我们维护一个容斥系数 $v_i$，满足 $\sum_{d|i\land d\ne 1}v_d=1$，那么有 $v_i=1-\sum_{d|i\land d\ne 1\land d\ne i} v_d$，这显然可以 $O(n\ln n)$ 做。

正确性的话你考虑对于每个 $i$ 假如它是应该被当成 $\gcd$ 造成贡献的数，按照上面的方法，他的每个因数都会被当成 $\gcd$ 造成贡献，那么因为 $\sum_{d|i\land d\ne 1}v_d=1$ 的性质，所以多余贡献就被消掉了。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define N 1000005
#define LL long long
#define MOD 998244353

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,char Extra=0) {
    if (x<0) putchar('-'),x=-x; if (x>9) W(x/10);
    putchar(x%10+'0'); if (Extra) putchar(Extra);
}

using namespace std;
int n,a[N]; LL f[N],g[N],val[N];

int main() {
    n=R();
    for (int i=1;i<=n;i++) a[i]=R();
    for (int i=2;i<=N;i++) {
        val[i]=1-val[i];
        for (int j=2*i;j<N;j+=i) val[j]+=val[i];
    }
    f[1]=1;
    for (int i=1;i<n;i++) {
        for (int j=1;j*j<=a[i];j++)
            if (a[i]%j==0) {
                if (j!=1) (g[j]+=f[i])%=MOD;
                if (j!=a[i]/j) (g[a[i]/j]+=f[i])%=MOD;
            }
        for (int j=1;j*j<=a[i+1];j++)
            if (a[i+1]%j==0) {
                if (j!=1) (f[i+1]+=1ll*val[j]*g[j]%MOD)%=MOD;
                if (j!=a[i+1]/j) (f[i+1]+=1ll*val[a[i+1]/j]*g[a[i+1]/j]%MOD)%=MOD;
            }
    }
    W((f[n]+MOD)%MOD,'\n');
    return 0;
}
```

容易发现 $v_i=-\mu(i)$，因为我们有 $\sum_{d|i} \mu(d)=\varepsilon(i)$，当 $i\ne 1$ 时有 $\sum_{d|i\land i\ne 1}-\mu(d)=1-\varepsilon(i)=1$。

---

## 作者：InQueue (赞：2)

首先发现图是一个 DAG，由此很好想到 dp。

设 $dp_i$ 为从点 $1$ 走到点 $i$ 的方案数。

边界：$dp_1=1$。

转移：对于 $i>1$：

$$\begin{aligned}
dp_i &= \sum_{j=1}^{i-1}[\gcd(a_i,a_j)\neq1]dp_j
\\ &= (\sum_{j=1}^{i-1}dp_j) - (\sum_{j=1}^{i-1}[\gcd(a_i,a_j)=1]dp_j)
\\ &= (\sum_{j=1}^{i-1}dp_j) - (\sum_{j=1}^{i-1}\sum_{d|a_i,d|a_j}\mu(d)dp_j)
\\ &= (\sum_{j=1}^{i-1}dp_j) - (\sum_{d|a_i}\mu(d)\sum_{1\le j\le i-1,d|a_j}dp_j)
\end{aligned}$$

于是 $\mu$ 可以预处理。另外 dp 时维护一个数组 $rec$，其中 $rec_j$ 表示此时（前 $i-1$ 个位置）所有 $a$ 值是 $j$ 的倍数的位置的 $dp$ 值之和，即 $rec_j = \sum_{k=1}^{i-1}[j|a_k]dp_k$。这样做在一个位置 $i$ 只需枚举 $a_i$ 的因数先求得 $dp_i$，再枚举 $a_i$ 的因数去更新 $rec$。总时间复杂度 $O(V\log V+n\times d(V))$，其中 $V$ 表示值域，$d(x)$ 表示小于等于 $x$ 的数中，因数个数最多的数的因数个数。本题中 $d(V=10^6)=240$，可以接受。

答案：$dp_n$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define psbk push_back
#define fst first
#define scd second
#define umap unordered_map
#define pqueue priority_queue
#define vc vector
#define endl '\n'
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
constexpr int inf = 0x3f3f3f3f, mo = 998244353;
int n, a[200005], pri[100005], pcnt, mu[1000005], dp[200005], rec[1000005], sum;
bool np[1000005];
vc<int> dv[1000005];
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=1000000;i++)
	{
		for(int j=i;j<=1000000;j+=i)
		{
			dv[j].psbk(i);
		}
	}
	mu[1] = 1;
	for(int i=2;i<=1000000;i++)
	{
		if(!np[i])
		{
			pri[++pcnt] = i;
			mu[i] = -1;
		}
		for(int j=1;j<=pcnt&&pri[j]*i<=1000000;j++)
		{
			np[pri[j] * i] = 1;
			if(i % pri[j] == 0)
			{
				mu[pri[j] * i] = 0;
				break;
			}
			mu[pri[j] * i] = mu[pri[j]] * mu[i];
		}
	}
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		if(i == 1)
		{
			dp[i] = 1;
		}
		else
		{
			dp[i] = sum;
			for(int j : dv[a[i]])
			{
				dp[i] = (dp[i] - (mu[j] * rec[j] + mo) % mo + mo) % mo;
			}
		}
		for(int j : dv[a[i]])
		{
			(rec[j] += dp[i]) %= mo;
		}
		(sum += dp[i]) %= mo;
	}
	cout << dp[n] << endl;
	return 0;
}
```

---

## 作者：YipChip (赞：1)

一眼看过去会是一个方案数 $dp$，但是不这么好直接干出来，因为边是不定的，而且无法全部建出来。

不妨设 $f(i)$ 表示到达城市 $i$ 的方案数，容易得到：

$$f(i) = \sum_{j = 1}^{i - 1} f(j) [\gcd(a_i, a_j) \neq 1]$$

看见这玩意直接来一发莫比乌斯反演。

$$f(i) = \sum_{j = 1}^{i - 1} f(j)\sum_{\substack{d \mid \gcd(a_i, a_j)\\d \neq 1}}\mu(d)$$

移一下项，把 $a_i$ 放到前面去，$a_j$ 留在后面：

$$f(i) = \sum_{\substack{d \mid a_i\\d \neq 1}}\mu(d)\sum_{j = 1}^{i - 1} f(j)[d \mid a_j]$$

此刻，我们发现一个非常好的一点，后者是 $d, i$ 相关独立的，可以提出来。

不妨设 $g(n, d) = \sum\limits_{j = 1}^{n}f(j)[d \mid a_j]$，容易发现：

$$g(i, d) = g(i - 1, d) + f(i)[d \mid a_i]$$

在计算 $f(i)$ 的过程中可以顺带把 $g(i, d)$ 给计算出来。

每次算完 $f(i)$ 更新 $g(i - 1, d)$，因此可以降下一维，满足空间需求。

线性筛筛出莫比乌斯函数，预处理因数 $O(A\ln{A})$，或枚举因数 $O(n\sqrt{A})$ 即可。

不过预处理比枚举因数慢是令我没想到的。

参考代码（预处理）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, M = 2e5 + 10, mod = 998244353;
int n, a[M];
int st[N], primes[N], cnt, mu[N];
vector<int> factors[N];
ll f[M], g[N];

void init()
{
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, mu[i] = 1;
        for (int j = 0; primes[j] * i < N; j ++ )
        {
            st[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
            mu[i * primes[j]] = -mu[i];
        }
    }
    for (int i = 2; i < N; i ++ )
        for (int j = i; j < N; j += i)
            factors[j].push_back(i);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n, init();
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    f[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        for (auto d : factors[a[i - 1]])
            if (a[i - 1] % d == 0)
                (g[d] += f[i - 1]) %= mod;
        for (auto d : factors[a[i]])
            if (mu[d])
                (f[i] += mu[d] * g[d]) %= mod;
    }
    cout << (f[n] + mod) % mod;
    return 0;
}
```

参考代码（枚举）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, M = 2e5 + 10, mod = 998244353;
int n, a[M];
int st[N], primes[N], cnt, mu[N];
vector<int> factors[N];
ll f[M], g[N];

void init()
{
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, mu[i] = 1;
        for (int j = 0; primes[j] * i < N; j ++ )
        {
            st[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
            mu[i * primes[j]] = -mu[i];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n, init();
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    f[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        for (int d = 1; d * d <= a[i - 1]; d ++ )
        {
            if (a[i - 1] % d) continue;
            if (d != 1) (g[d] += f[i - 1]) %= mod;
            if (d * d != a[i - 1]) (g[a[i - 1] / d] += f[i - 1]) %= mod;
        }
        for (int d = 1; d * d <= a[i]; d ++ )
        {
            if (a[i] % d) continue;
            if (d != 1) (f[i] += mu[d] * g[d]) %= mod;
            if (d * d != a[i]) (f[i] += mu[a[i] / d] * g[a[i] / d]) %= mod;
        }
    }
    cout << (f[n] + mod) % mod;
    return 0;
}
```

---

## 作者：KaruAWA (赞：1)

Welcome to Natlan！

感觉这题 trick 挺典的，可以积累一下。

先想一个朴素的 $O(n^2)$ 转移，设 $dp_i$ 表示到第 $i$ 个点有多少种方案，累加前面若干个可以转移过来的点，最后输出 $dp_n$。考虑在这上面优化，时间复杂度瓶颈显然在转移上。观察题目要求的转移条件为 $i\rightarrow j(i<j)$ 当且仅当 $\gcd(i,j)\ne 1$，这就提示我们要从因数入手。并且实际上我们发现我们并不关心公因数具体是几，只需要保证有公因数就行。

因此我们考虑枚举 $a_i$ 能转移到哪些质因数上去，统计的时候再从 $a_i$ 所拥有的质因数转移过来。并且由于 $2\times3\times5\times7\times11\times13\times17\times19>10^6$ 了，因此一个数所拥有的质因数不会超过 $7$ 个。但这样会算重，比方说 $a_1=6,a_2=6$，$a_1$ 会将质因数 $2,3$ 的贡献都加一，而 $a_2$ 统计的时候会将 $2,3$ 都统计，导致算重。

因此考虑容斥，设 $S$ 为 $a_i$ 质因数的子集，答案就是 $\sum\limits_{T\in S} (-1)^{|T|+1} dp_{\prod\limits_{i\in T} p_i}$，$dp_j$ 表示因数为 $j$ 的贡献。考虑这东西的实质是枚举 $a_i$ 与之前数的 $\gcd$ 是形如 $p_1^{q_1}p_2^{q_2}...p_m^{q^m}$ 时的贡献，只是由于我们并不关心 $q$ 的取值，因此这是不重不漏的。

code：

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
const int M=1e6+5;
const int mod=998244353;
int n,a[N];
bool vis[M];
vector<int>prim;
int divi[M];

void pre(){
    vis[1]=true;
    for(int i=2;i<=(int)1e6;++i){
        if(!vis[i]) prim.push_back(i);
        for(int j=0;j<prim.size();++j){
            int v=prim[j];
            if(1ll*i*v>(ll)1e6) break;
            vis[i*v]=true;
            divi[i*v]=v;
            if(!(i%v)) break;
        }
    }
}

vector<int>fac[N];

void work(int x,int now){
    if(now==1) return;
    if(!vis[now]){
        fac[x].push_back(now);
        return;
    }
    int tmp=divi[now];
    fac[x].push_back(tmp);
    while(!(now%tmp))
        now/=tmp;
    work(x,now);
}

map<int,ll>f;

ll get(int now,int prod,bool num,int x){
    if(now==fac[x].size()){
        if(prod==1) return 0;
        if(num) return f[prod];
        return (mod-f[prod])%mod;
    }
    return (get(now+1,prod,num,x)+get(now+1,1ll*prod*fac[x][now],!num,x))%mod;
}

void trans(int now,int prod,ll k,int x){
    if(now==fac[x].size()){
        if(prod!=1){
            ll tmp=f[prod];
            tmp=(tmp+k)%mod;
            f[prod]=tmp;
        }
        return;
    }
    trans(now+1,prod,k,x);
    trans(now+1,1ll*prod*fac[x][now],k,x);
}

int main(){
    ios::sync_with_stdio(false);
    pre();
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        work(i,a[i]);
    }

    for(int i=1;i<=n;++i){
        ll sum=0;
        if(i==1) sum=1;
        else sum=get(0,1,0,i);
        trans(0,1,sum,i);
        if(i==n) cout<<sum<<" ";
    }
    return 0;
}
/*
维护一些点表示截止目前 gcd 若是这些的贡献
对于 dp[i]，它要转移到至多 2^7 个点
再用容斥从 2^7 个点转移过来
也就是先线性筛，并处理出每个 a[i] 有哪些质因子
再 dp
*/
~~~

---

## 作者：xiezheyuan (赞：1)

## 简要题意

纳塔国有 $n$ 座城市，城市 $i$ 的“魅力值”为 $a_i$。城市 $i$ 与城市 $j$ 之间存在一条有向边，当且仅当 $i<j$ 且 $\gcd(a_i,a_j)\neq 1$。

你需要求出从城市 $1$ 出发到达城市 $n$ 的路径数。答案对 $998,244,353$ 取模。

$2\leq n\leq 2\times 10^5,1\leq a_i\leq 10^6$。

## 思路

不是，CF 2000 的题目也开始考莫反了？

不妨先 dp，设 $f_i$ 表示从 $1$ 到达 $i$ 的路径数，显然有 $f_1=1$，且：

$$
f_i=\sum_{j=1}^{i-1}[\gcd(a_i,a_j)\neq 1]f_j
$$

时间复杂度 $O(n^2\log a_i)$ 难以承受。

观察到后面那个东西很像莫反，先将式子变形得：

$$
f_i=\sum_{j=1}^{i-1}[\gcd(a_i,a_j)\neq 1]f_j=\sum_{j=1}^{i-1}f_j - \sum_{j=1}^{i-1}[\gcd(a_i,a_j)=1]f_j
$$

考察后面的和式（因为前面的和式很好做），套用经典结论 $\mu\ast 1=\epsilon$ 得：

$$
\sum_{j=1}^{i-1}[\gcd(a_i,a_j)=1]f_j=\sum_{j=1}^{i-1}f_j\sum_{d\mid a_i,d\mid a_j}\mu(d)=\sum_{d\mid a_i}\mu(d)\sum_{d\mid a_j}f_j
$$

考虑转移的时候直接枚举 $d$，开个桶记录一下 $g(d)=\sum_{d\mid a_j}f_j$ 即可。

时间复杂度 $O(a_i\log a_i+n\sum d(a_i))$。由于 $\max d(a_i)=240$，所以可以通过本题。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 2e5 + 5, M = 1e6 + 5;
int n, pri[N], tot, mu[M], a[N], g[M];
vector<int> d[M];
bool vis[M];

void sieve(int n){
    mu[1] = 1;
    for(int i=2;i<=n;i++){
        if(!vis[i]) mu[i] = mod - 1, pri[++tot] = i;
        for(int j=1;j<=tot&&1ll*i*pri[j]<=n;j++){
            vis[i * pri[j]] = 1;
            if(!(i % pri[j])) break;
            mu[i * pri[j]] = mod - mu[i];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i) d[j].emplace_back(i);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sieve(*max_element(a + 1, a + n + 1));
    int sumt = 1, f = 0;
    for(int j : d[a[1]]) g[j] = 1;
    for(int i=2;i<=n;i++){
        int tmp = 0;
        for(int j : d[a[i]]) tmp = Add(tmp, Mul(mu[j], g[j]));
        f = Sub(sumt, tmp);
        sumt = Add(sumt, f);
        for(int j : d[a[i]]) g[j] = Add(g[j], f);
    }
    cout << f << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：postpone (赞：0)

对于点 $u$ 和 $v$，若 $u<v$，且 $\gcd(u, v)\neq1$，那么到 $u$ 的所有路径都能到 $v$，由此我们能想到一个对位置枚举的状态转移。但每次从头枚举位置，复杂度是 $O(n^2)$，需要一个更快的方法。

设 $f_i$ 表示从起点到 $i$ 有多少路径，则列出状态转移，并推一下式子。

$$
\begin{align*}
f_i &= \sum^{i-1}_{j = 1}f_j
[{\gcd(i, j) \neq 1}]\\
&= \sum^{i-1}_{j = 1}\left(f_j\times\sum_{d\mid\gcd(a_i, a_j), d\neq 1}\mu(d)\right)\\
&= \sum_{d\mid a_i, d\neq 1}\left(\mu(d)\times\sum_{j=1}^{i-1}f_j[d\mid a_j]\right)
\end{align*}
$$

现在，更新的方式变为：对于 $a_i$ 的每个因子 $d$，统计它的贡献：莫比乌斯函数与后面这个东西的乘积。

这个 $\displaystyle \sum_{j=1}^{i-1}f_j[d\mid a_j]$，它的意思是 $d$ 为 $a_j$ 的因子时，就算一次该位置的贡献 $f_j$，看起来有点像多了一个维度的前缀和。

单独考虑它的转移，设 $\displaystyle g_{i, d}=\sum_{j=1}^{i-1}f_j[d\mid a_j]$，转移为：对于 $a_i$ 的每个因子 $d$，有 $g_{i,d}=g_{i-1, d}+f_i$。

那么这道题就做出来了，先预处理莫比乌斯函数，以及值域内所有数的因子；再如上所述维护 $f$ 与 $g$，其中 $g$ 去掉第一维，通过滚动的方式更新。复杂度 $O(n\sqrt m)$，其中 $m=\max \{a_i\}$。

```cpp
// Z 为取模类
int main() {
    cin.tie(nullptr)
        ->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    const int m = *max_element(a.begin(), a.end());

    // 莫比乌斯系数
    vector<Z> c(m + 1, 1);
    c[1] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 2 * i; j <= m; j += i) {
            c[j] -= c[i];
        }
    }

    // 预处理出每个数的因数
    vector ds(m + 1, vector<int>());
    for (int i = 1; i <= m; i++) {
        if (c[i].val() == 0) { // 剪枝：莫比乌斯函数为 0 就没必要统计因子了
            continue;
        }
        for (int j = i; j <= m; j += i) {
            ds[j].push_back(i);
        }
    }
    vector<Z> g(m + 1), f(n);
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        for (auto d : ds[a[i]]) {
            f[i] += g[d] * c[d];
        }
        for (auto d : ds[a[i]]) {
            g[d] += f[i];
        }
    }
    cout << f[n - 1] << "\n";

    return 0;
}
```

---

## 作者：Iniaugoty (赞：0)

### CF2037G Natlan Exploring

设 $f _ i$ 表示从 $a _ 1$ 走到 $a _ i$ 的方案数。直接转移有 $O(n ^ 2 \log n)$。

$i \to j$ 的转移要求 $\gcd(a _ i, a _ j) \neq 1$，强行刻画的话避免不了枚举每个数。于是经典容斥（莫反？）拆贡献。

根据莫反的 $[n = 1] = \sum _ {d \vert n} \mu (d)$，有结论 $[n \neq 1] = \sum _ {d \neq 1, d \vert n} -\mu (d)$。于是将 $f _ i [\gcd(a _ i, a _ j) \neq 1]$ 的贡献拆成了 $-f _ i \mu (d)$ 上。

那么转移的时候，只需要对因数打标记，以及求因数的标记之和。

需要线性筛预处理 $\mu$，和以 $O(V \log V)$ 枚举每个数的倍数的方式预处理每个数的因数。

时间复杂度是 $O(V \log V + \sum d(a _ i))$，[code](https://codeforces.com/contest/2037/submission/291968182)。

---

## 作者：MattL (赞：0)

建议评蓝（别问为啥，dp+数论，数论虚高）

考虑 dp，统计从 1 到 $i$ 的路径数。

观察 $\gcd(a_i,a_j)\neq 1$ 的条件，不难想到枚举 $1\leq j< i$。答案即：

$$f_i=\sum_{1\leq j<i \&\gcd(j,i)\neq1}f_j$$

这样是 $\mathcal O(n^2)$ 的，显然无法通过。

考虑优化。我们只需要统计 $\gcd(i,j)\neq 1$ 的答案，不难想到枚举 $a_i$ 的因数，统计它们的答案，同时把现在的答案也存在 $a_i$ 的因数里。

但是这样会重复统计。所以考虑容斥，对该因数的质因数个数分类讨论，奇数个加，偶数个减即可。

考虑 $a_i$ 有多个相同质因数，发现可以只用质因数的答案，往上无需枚举。故答案只用单个质因数的积，答案也存在单个质因数的积里。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (now<<1)
#define rs (now<<1|1)
#define LL long long
#define f(i,n) for(int i=1;i<=n;i++)
#define f_(i,n) for(int i=n;i>=1;i--)
#define ff(i,a,b) for(int i=a;i<=b;i++)
#define ff_(i,a,b) for(int i=a;i>=b;i--)
#define pi pair<int,int> 
#define pb push_back
#define vi vector<int>
#define yes cout<<"Yes"<<endl
#define no cout<<"No"<<endl
#define fs(i,s) for(int i=0;i<s.size();i++)
#define re return
#define con continue
#define bre break
#define mkp make_pair



const int N=1e6+10;
int pri[N],cntpri;
bool nop[N];
void shai(int n){
    for(int i=2;i<=n;i++){
    	if(!nop[i])
    		pri[++cntpri]=i;
		for(int o=1;i*pri[o]<=n&&o<=cntpri;o++){
			nop[i*pri[o]]=1;
			if(i%pri[o]==0)break;
		}
	}
}
const int mod=998244353;
int n,a[N],f[N],maxn,ans,cnt,mi=1;
vector<int> p;
void dfs(int k){
	if(k==p.size()){
		if(mi==1)return ;
		if(cnt&1)ans=(ans+f[mi])%mod;
		else ans=(ans-f[mi]+mod)%mod;
		return ;
	}
	int tmp=mi;
	dfs(k+1);
	mi=1ll*mi*p[k]%mod;
	cnt++;
	dfs(k+1);
	mi=tmp,cnt--;
}
void dfss(int k){
	if(k==p.size()){
		if(mi==1)return ;
		f[mi]=(f[mi]+ans)%mod;
		return ;
	}
	int tmp=mi;
	dfss(k+1);
	mi=1ll*mi*p[k]%mod;
	dfss(k+1);
	mi=tmp;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;
	f(i,n)cin>>a[i],maxn=max(maxn,a[i]);
	shai(maxn);//先线性筛
	f(i,n){
		p.clear();
		if(!nop[a[i]])p.pb(a[i]);
		else{
			for(int o=1;pri[o]*pri[o]<=a[i];o++)
				if(a[i]%pri[o]==0){
					p.pb(pri[o]);
					while(a[i]%pri[o]==0)a[i]/=pri[o];
				}
			if(a[i]!=1)p.pb(a[i]);
		}
		if(i==1)ans=1;
		else ans=0,dfs(0);
		dfss(0);//写成dfs优化常数
	}
	cout<<ans<<endl;
    return 0;
}
```

---

