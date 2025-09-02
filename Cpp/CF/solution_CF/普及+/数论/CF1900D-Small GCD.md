# Small GCD

## 题目描述

$ a, b, c $ 为整数，定义 $ f(a, b, c) $ 如下:

将三个数排序，使得 $ a \le b \le c $。则函数返回 $ \gcd(a, b) $ , 这里 $ \gcd(a, b) $ 表示 [最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) 。简而言之，函数返回较小的两个数的最大公约数。

你会得到数组 $ a $，包含 $ n $ 个元素。求 $ f(a_i, a_j, a_k) $ 之和，其中 $ 1 \le i< j < k \le n $。

形式化的讲，求 $ \sum_{i = 1}^n \sum_{j = i+1}^n \sum_{k =j +1}^n f(a_i, a_j, a_k)$。

## 样例 #1

### 输入

```
2
5
2 3 6 12 17
8
6 12 8 10 15 12 18 16```

### 输出

```
24
203```

# 题解

## 作者：Kevin911 (赞：18)

首先，可以处理出所有数的因子。

由于顺序不会影响到三元组的情况，所以先排序。

答案可以转化为$\sum_{k=1}^{n}\sum_{i=1}^{k}\sum_{j=1}^{i}\gcd(a[i],a[j])$。

数组值域最多只会到 $100000$，因数个数不超过 $128$。

考虑对于 $f$, $g$ 数组，$f$ 表示以这个数为与当前数的公因数的数量，$g$ 数组表示当有这个因子的数的个数。

因为公因数之间可能存在重复的情况，所以通过容斥原理扣除它与它的倍数之间的重复情况（不包括他自己）。

具体细节见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int a[maxn],f[maxn],g[maxn];
vector<int> fac[maxn];
signed main()
{
	for(int i=1;i<=1e5;i++)
		for(int j=i;j<=1e5;j+=i) fac[j].push_back(i);
	for(int i=1;i<=1e5;i++) reverse(fac[i].begin(),fac[i].end());
	int t;
	cin>>t;
	for(int p=1;p<=t;p++)
	{
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0,tmp=0;
		for(int i=1;i<=n;i++)
		{
			ans+=tmp;
			for(auto u:fac[a[i]])
			{
				f[u]=g[u];
				for(auto v:fac[a[i]/u])
					if(v!=1) f[u]-=f[u*v];//容斥原理
				tmp+=u*f[u];
			}
			for(auto u:fac[a[i]]) g[u]++;
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：Phartial (赞：13)

爆标了。

首先对 $a_i$ 排序，则答案即为 $\displaystyle\sum_{j=1}^n(n-j)\sum_{i=1}^{j-1}\gcd(a_i,a_j)$。考虑对该式进行莫比乌斯反演（以下设 $v=a_n$，即 $a$ 中的最大值）：

$$
\begin{aligned}
  &\sum_{j=1}^n(n-j)\sum_{i=1}^{j-1}\gcd(a_i,a_j)\\
  =&\sum_{g=1}^{v}g\sum_{j=1}^n(n-j)\sum_{i=1}^{j-1}[\gcd(a_i,a_j)=g]\\
  =&\sum_{g=1}^{v}g\sum_{g\mid a_j}(n-j)\sum_{g\mid a_i,i<j}[\gcd(a_i,a_j)=g]\\
  =&\sum_{g=1}^{v}g\sum_{g\mid a_j}(n-j)\sum_{g\mid a_i,i<j}[\gcd(\frac{a_i}{g},\frac{a_j}{g})=1]\\
  =&\sum_{g=1}^{v}g\sum_{g\mid a_j}(n-j)\sum_{g\mid a_i,i<j}\sum_{p\mid \frac{a_i}{g},p\mid\frac{a_j}{g}}\mu(p)\\
  =&\sum_{g=1}^{v}g\sum_{p=1}^v\mu(p)\sum_{gp\mid a_j}(n-j)\sum_{gp\mid a_i,i<j}1
\end{aligned}
$$

设 $t=gp$。

$$
\begin{aligned}
  &\sum_{g=1}^{v}g\sum_{p=1}^v\mu(p)\sum_{gp\mid a_j}(n-j)\sum_{gp\mid a_i,i<j}1\\
  =&\sum_{t=1}^v\left(\sum_{t\mid a_j}(n-j)\sum_{t\mid a_i,i<j}1\right)\left(\sum_{g\mid t}^{v}g\mu(\frac{t}{g})\right)\\
  =&\sum_{t=1}^v\varphi(t)\sum_{t\mid a_j}(n-j)\sum_{t\mid a_i,i<j}1\\
\end{aligned}
$$

注意到 $i<j\impliedby a_i<a_j$，因此我们枚举 $t$，并枚举 $t$ 的所有倍数作为 $a_j$，所有满足 $t\mid a_i\land a_i<a_j$ 的 $a_i$ 都会被统计进答案（如果我们从小到大枚举 $t$ 的倍数，则满足该条件的数的个数是不难统计的）。而对于 $a_i=a_j\land i<j$ 的答案可以简单预处理。对每个 $t$ 算出该数并乘上 $\varphi(t)$ 即可。时间复杂度 $\mathcal{O}(n\log n+v\log v)$，遥遥领先！

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 8e4 + 1, kV = 1e5 + 1;

int tt, n, a[kN], phi[kV], c[kV];
LL b[kV], s[kV], ans;
bool v[kV];
vector<int> p;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  phi[1] = 1;
  for (int i = 2; i < kV; ++i) {
    if (!v[i]) {
      p.push_back(i), phi[i] = i - 1;
    }
    for (int j : p) {
      if (1LL * i * j >= kV) {
        break;
      }
      v[i * j] = 1;
      if (i % j) {
        phi[i * j] = phi[i] * (j - 1);
      } else {
        phi[i * j] = phi[i] * j;
        break;
      }
    }
  }
  for (cin >> tt; tt--;) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= a[n]; ++i) {
      c[i] = b[i] = s[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      b[a[i]] += c[a[i]] * (n - i), s[a[i]] += n - i;
      ++c[a[i]];
    }
    ans = 0;
    for (int t = 1; t <= a[n]; ++t) {
      LL _s = 0;
      for (int j = t, _c = 0; j <= a[n]; j += t) {
        _s += _c * s[j] + b[j], _c += c[j];
      }
      ans += _s * phi[t];
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：_always_ (赞：11)

# CF1900D Small GCD 题解
[原题链接](https://codeforces.com/contest/1900/problem/D)

## 题意
一个序列求所有三元组中两个较小的值的 $\gcd$ 之和。  
$$
\sum_{i=1}^{n}\sum_{j=i+1}^{n}\sum_{k=j+1}^{n}f(a_i,a_j,a_k)
$$
$f(a_i,a_j,a_k)$ 表示取其中两个较小值的 $\gcd$。

## 思路
首先，朴素的做法就是直接按照给出的公式求解，时间复杂度大约为 $O(n^3\log n)$，显然是不行的，并且通常带有求和公式的题目都不会直接模拟计算。  

由题可知三元组是不重复的（与三元组内元素出现的顺序无关），并且只需要用三元组中两个较小的值，从小到大排序是没有问题的。并且可以想到对于每一个三元组**枚举中间数**，对于中间数 $a_j$ 只需要将所有的 $i<j$ 的 $a_i$ 和 $a_j$ 求一个 $\gcd$ 即可，并且注意，因为三元组中的最大值是可以随意选取的，这个值需要乘一个 $(n-j)$。  
如下：
$$
\sum_{i=1}^{n}\sum_{j=1}^{i-1}\gcd(a_i,a_j)\times(n-i)
$$
时间复杂度顺利优化成 $O(n^2\log n)$。

但是这个时间复杂度还是远远不够的。但是还能怎么优化呢？  
需要用到一个数论知识：
## 欧拉反演

**欧拉函数**：对正整数 $n$，欧拉函数是少于或等于 $n$ 的数中与 $n$ 互质的数的数目，用 $\phi(x)$来表示 $x$ 的欧拉函数值。  
[欧拉函数如有不懂戳这里](http://oi-wiki.com/math/number-theory/euler-totient/)。

**欧拉反演**是欧拉函数的一条性质，即：
$$
n=\sum_{d|n}\phi(d)
$$
这里简单证明一下：
$$\begin{aligned}
n&=\sum_{d|n}\sum_{j=1}^{n}\gcd(j,n)==d \\
&=\sum_{d|n}\sum_{j=1}^{\frac{n}{d}}\gcd(j,\frac{n}{d})==1 \\
&=\sum_{d|n}\phi(\frac{n}{d}) \\
&=\sum_{d|n}\phi(d) \\
\end{aligned}$$

有了这条性质，可以应用：  
一个较为简单的：  
$$\begin{aligned}
\gcd(i,j)=\sum_{d|\gcd(i,j)}\phi(d)
=\sum_{d|i} \sum_{d|j} \phi(d)\\
\end{aligned}$$
所以：
$$\begin{aligned}
\sum_{i=1}^n\gcd(i,n)&=\sum_{i=1}^n\sum_{d|i} \sum_{d|n} \phi(d) \\
&=\sum_{d|n} \sum_{i=1}^n\sum_{d|i} \phi(d) \\
&=\sum_{d|n} \frac{n}{d}\phi(d)\\
\end{aligned}$$   

将其应用到本题：

$$\begin{aligned}
&\sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \gcd(a_i, a_j) (n - i)\\
&= \sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \sum_{d | a_i, d | a_j} \phi(d)(n - i)\\
&= \sum_{i = 1}^{n} (n - i) \sum_{j = 1}^{i - 1} \sum_{d | a_i} \phi(d)[d | a_j] \\
&= \sum_{i = 1}^{n} (n - i) \sum_{d | a_i} \phi(d) \sum_{j = 1}^{i - 1} [d | a_j] \\
&= \sum_{i = 1}^{n} (n - i) \sum_{d | a_i} \phi(d) cnt_{i - 1, d}
\end{aligned}$$

对于欧拉函数，用一个欧拉筛就可以解决了。

最终时间复杂度：$O(n\sqrt{n})$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=8e4+10,Maxn=1e5+10;
int t,n,cnt=0;
ll a[N],prime[Maxn],phi[Maxn],sum[Maxn];
ll ans=0;
bool f[Maxn];

void phii(int x){//预处理欧拉函数
	for(int i=2;i<=x;i++) f[i]=true;
	f[1]=f[0]=false;
	phi[1]=1;
	for(int i=2;i<=x;i++){
		if(f[i]) prime[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*prime[j]<=x;j++){
			f[i*prime[j]]=false;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return ;
}

int main(){
	phii(1e5);
	scanf("%d",&t);
	while(t--){
		memset(sum,0,sizeof(sum));
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			for(int j=1;j*j<=a[i];j++){//枚举a[i]的所有因数
				if(a[i]%j==0){
					ans+=sum[j]*phi[j]*(n-i);
					sum[j]++;//注意这里是先计算再修改 
					if(j*j!=a[i]){
						ans+=sum[a[i]/j]*phi[a[i]/j]*(n-i);
						sum[a[i]/j]++;
					}
				}
			}
		}
		printf("%lld\n",ans);
		ans=0;
	}
	return 0;
}
```

这个数学证明应该难度不算很高，读者有问题可以在评论区提出。看到了尽量回答。

完结撒花！

---

## 作者：nynkqh_yzq (赞：11)

# CF 1900D Small GCD

题意：给定一个 $n$ 和一个序列 $a$，求：
$$
 \sum_{i  =  1}^{n} \sum_{j  =  i  +  1}^{n} \sum_{k  =  j  +  1}^{n}  f(a_i,  a_j, a_j)
$$

其中 $f(a_i,  a_j,  a_j)$ 表示三个数中的**较小的两个数的** $\gcd$。

数据范围：$3 \le n \le 8 \times 10^4$，$1 \le a_i \le 10^5$。

前置芝士（欧拉反演）：
$$
 n = \sum_{d \mid n} \varphi(d)
$$

首先，反正都是枚举三个数，那么顺序并不重要，所以我们可以**把 $a$ 按从小到大排个序，然后枚举三个数中的第二小的值，即可求出这个数的贡献**，即有：

$$
 \sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \gcd(a_i, a_j) (n - i)
$$

看到 $a_i$ 的值都不大，可以考虑欧拉反演，即有：

$$
 \sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \sum_{d \mid \gcd(a_i, a_j)} \varphi(d) \times (n - i)
$$

既然 $d$ 是 $\gcd(a_i, a_j)$ 的因数，那么 $d$ 也是 $a_i$ 和 $a_j$ 的因数，则有：

$$
 \sum_{i = 1}^{n} \sum_{j = 1}^{i - 1} \sum_{d \mid a_i, d \mid a_j} \varphi(d) \times (n - i)
$$

那么转换一下，则有：

$$
 \sum_{i = 1}^{n} (n - i) \times \sum_{j = 1}^{i - 1} \sum_{d \mid a_i} \varphi(d) \times [d | a_j] 
$$

$$
 \sum_{i = 1}^{n} (n - i) \times \sum_{d \mid a_i} \varphi(d) \times \sum_{j = 1}^{i - 1} [d | a_j] 
$$

此时，后面的 $\sum_{j = 1}^{i - 1} [d \mid a_j] $ 可以设为 $cnt_{i - 1}$，则有：

$$
 \sum_{i = 1}^{n} (n - i) \times \sum_{d \mid a_i} \varphi(d) \times cnt_{i - 1}
$$

单次时间复杂度为 $O(n\sqrt{n})$，可以通过本题，其中 $cnt_i$ 在分解 $a_i$ 的时候顺便求出即可（详见代码）。

好了，直接上代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 10;
int phi[N], cnt[N], a[N], p[N];
bool zs[N];
int n, t, tot, ans;
vector<int> prime;

int split(int x) {
	tot = 0; int xx = sqrt(x), res = 0;
	for (int i = 1; i <= xx; i ++) {
		if (!(x % i)) {
			res += phi[i] * cnt[i], cnt[i] ++; //分解因数，顺便求贡献
			if (i * i != x) res += phi[x / i] * cnt[x / i], cnt[x / i] ++; //同理
		}
	}
	return res;
}

void get_phi() {
	phi[1] = 1;
	for (int i = 2; i <= N - 5; i ++) {
		if (!zs[i]) zs[i] = true, prime.push_back(i), phi[i] = i - 1;
		for (int j = 0; j < prime.size() && prime[j] * i <= N - 5; j ++) {
			auto h = prime[j]; zs[i * h] = true;
			if (!(i % h)) { phi[i * h] = phi[i] * h; break; }
			phi[i * h] = phi[i] * phi[h];
		}
	}
	return ;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> t; get_phi(); //线性筛求欧拉函数
	while (t --) {
		cin >> n; ans = 0;
		for (int i = 1; i <= N - 5; i ++) cnt[i] = 0;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		sort(a + 1, a + n + 1);
		for (int i = 1; i < n; i ++) {
			int h = split(a[i]); 
			ans += h * (n - i); //三元组中的最大的一个数可以任选，故乘上后面的数的个数
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：10)

原题链接：[CF1900D](https://www.luogu.com.cn/problem/CF1900D)，题意不多赘述。

首先可以将 $a$ 数组排序，并且枚举中间的那个数 $a_i$。那么答案就是 $\sum_{j=1}^{i-1} \gcd(a_j,a_i)\times (n-i)$。重点在于求前面的 $\gcd$。可以用欧拉反演，但是也可以不用，因为我不会。

假设我们当前已经枚举到了 $a_i$，设 $f_k$ 表示 $a_1$ 到 $a_{i-1}$ 中是 $k$ 的倍数的数有多少个，$g_k$ 表示 $a_{1}$ 到 $a_{i-1}$ 中满足 $\gcd(a_j,a_i)=k$ 的数有多少个。$f_k$ 可以直接通过枚举每一个数的所有因子算出，$g_k$ 可以考虑用容斥算出。具体的，首先将 $g_k$ 赋值为 $f_k$，但是我们会发现有一些数不满足条件。比如 $4$ 和 $8$ 都是 $2$ 的倍数，但是 $\gcd(4,8) \ne 2$，所以我们直接将每一个 $g_k$ 都减去 $g_x(k \mid x,x \mid a_i)$ 即可。对于每一个 $a_i$，最终答案为 $\sum g_j\times j \times (n-i)$。

可以先预处理出 $1$ 到 $100000$ 的所有因数，小常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
int t,n,a[MAXN],f[MAXN],g[MAXN]; 
vector <int> v[MAXN];
signed main()
{
	for(int i = 1e5;i >= 1;i--)
		for(int j = i;j <= 1e5;j += i) v[j].emplace_back(i);
	cin >> t;
	while(t--)
	{
		memset(f,0,sizeof f),memset(g,0,sizeof g);
		cin >> n;
		for(int i = 1;i <= n;i++) cin >> a[i];
		sort(a + 1,a + n + 1);
		int ans = 0;
		for(int i = 1;i <= n;i++)
		{
			for(auto j : v[a[i]]) g[j] = f[j],f[j]++;
			for(auto j : v[a[i]])
				for(auto k : v[j]) if(k != j) g[k] -= g[j];
			for(auto j : v[a[i]]) ans += (g[j] * (n - i) * j);
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：Sampson_YW (赞：7)

将 $a$ 排序后枚举次小值 $a_j$，那么 $k$ 有 $n-j$ 种取值且不影响答案。

答案就是 $\sum_{j=1}^{n}(n-j)\sum_{i<j}\gcd(a_i,a_j)$，重心在后面的 $\gcd$ 之和。

$\gcd$ 一定是 $a_j$ 的因数。将 $a_j$ 的因数提取出来后容斥。

设 $f_x$ 为 $i\in [1, j-1]$ 的 $a_i$ 中有多少个是 $x$ 的倍数，设 $g_x$ 为 $i\in [1,j-1]$ 有多少个 $\gcd(a_i,a_j) = x$。

$f_x$ 好求，扫 $a_j$ 的同时枚举因数就行。$g_x$ 怎么求？从大到小枚举 $x$，首先 $g_x=f_x$，如果有 $y>x$ 且 $y$ 是 $x$ 的倍数，那么有 $g_y$ 个 $a_i$ 满足 $\gcd(a_i,a_j)=g_y$ 且 $a_i$ 的因数中有 $x$，因此 $g_x$ 需要减去 $g_y$。

复杂度 $O(n\max d^2(V))$，当 $V=10^5$ 时 $\max d(V)=128$，且常数很小。

[code](https://codeforces.com/contest/1900/submission/234526029)

---

## 作者：EuphoricStar (赞：3)

不是很懂官方题解在干嘛。

设 $g_x$ 为满足 $x \mid f(a_i, a_j, a_k)$ 且 $i, j, k$ 两两不同的所有无序三元组的个数。则容易容斥求出 $h_x$ 为 $x = f(a_i, a_j, a_k)$ 的个数。答案即为 $\sum h_x x$。下面只考虑 $g_x$。

枚举 $x$，不妨设 $a_i \le a_j \le a_k$，则 $a_i, a_j$ 都必须是 $x$ 的倍数。那么再枚举 $a_j$，$a_i$ 能取 $\le a_j$ 的 $x$ 的倍数，$a_k$ 能取 $\ge a_j$ 的所有数。前缀和优化后即可 $O(1)$ 计算。

注意因为三元组是无序的，所以要分别讨论 $a_i = a_j, a_k = a_j$ 的情况。

时间复杂度 $O(n + V \log V)$。

[code](https://codeforces.com/contest/1900/submission/234568236)

---

## 作者：_RainCappuccino_ (赞：1)

# CF1900D - Small GCD【数论超好题】

## 前置知识

- [欧拉函数 - OI Wiki ](https://oi-wiki.org/math/number-theory/euler-totient/#性质)
- [筛法 - OI Wiki ](https://oi-wiki.org/math/number-theory/sieve/#筛法求欧拉函数)

## 正题

### 题意

给定一个数组 $a$，找出 $a$ 中所有不同的三元组 $(x, y, z)$，求所有 $\gcd(min1, min2)$ 的和，$min1$ 为三元组中最小的数，$min2$ 为三元组中次小的数。

### 思路

由于该题是取三元组中较小的两个数，所以说最大的那个数并不重要，只需要找出所有二元组，并乘上可以为第三个数的数的个数即可。

再而，取三元组并不需要考虑下标，所以我们可以将 $a$ 数组升序排序，快速得到可以为第三个数的数的个数，即 $n - j$（$j$ 为次小的数的排序后下标）。

显然，我们现在就可以得到一个 $\text{O}(n^2\log n)$ 的做法。

```cpp
sort(a + 1, a + 1 + n);
for (int i = 1; i <= n; i ++) {
	for (int j = i + 1; j <= n; j ++) {
		ans += gcd(a[i], a[j]) * (n - j);
	}
}
```

那怎么优化呢？

一种优化思路是：仅枚举三元组中一个数，再用每种算法快速求出可能的三元组的值。

那枚举哪个数呢？

中间值：枚举出它之后，最大数的个数已知，且最小数的范围也已知。

那么我们需要快速求出的值就变为了 $\sum_{i = 1}^{j - 1} \gcd(a_i, a_j)$。

接着，我们对 $\gcd(a_i,a_j)$ 进行欧拉反演：
$$
\gcd(a_i,a_j) = \sum_{d \mid \gcd(a_i, a_j)} \varphi(d) = \sum_{d \mid a_j} \varphi(d) [d \mid a_i]
$$
再将其代回原式：
$$
\sum_{i = 1} ^ {j - 1} \sum_{d \mid a_j} \varphi(d)[d | a_i]
$$
将统计可以相约的循环移进来：
$$
\sum_{d \mid a_j} \varphi(d) \sum_{i = 1}^{j - 1}[d | a_i]
$$
然后我们惊奇的发现，$ \sum_{i = 1}^{j - 1}[d | a_i]$ ，为小于 $a_j$ 的数中包含因数 $d$ 的数的个数，可以递推出来！

所以复杂度瓶颈仅在于 $\sum_{d \mid a_j} \varphi(d)$。

又因为 $\varphi(d)$ 可以用线性筛快速求出，且一个数的因数个数近似于 $\sqrt{n}$。

所以时间复杂度近似于 $\text{O}(n+t\times\sqrt{n})$，可以通过此题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N = 8e4 + 10, M = 1e5 + 10;
typedef long long ll;
ll n, t, ans;
ll a[N], pri[M], tot, phi[M], cnt[M];
vector<ll> evn[M];
bool isp[M];
void pre(int Max){//线性筛求欧拉函数
	for(int i = 1; i <= Max; i ++) isp[i] = 1;
	isp[1] = 0;
	phi[1] = 1;
	for(int i = 2; i <= Max; i ++){
		if(isp[i]){
			pri[++ tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1;j <= tot && i * pri[j] <= Max;j ++){
			isp[i * pri[j]] = 0;
			if(i % pri[j]) phi[i * pri[j]] = phi[i] * phi[pri[j]];//积性函数的性质
			else{
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	for (int i = 1; i <= 1e5; i ++) {//预处理因数
		for (int j = 1; j * j <= i; j ++) {
			if (i % j == 0) {
				evn[i].push_back(j);
				if (j * j != i) evn[i].push_back(i / j);
			}
		}
	}
	pre(1e5);
	for (cin >> t; t; t --) {
		cin >> n;
		ans = 0;
		for (int i = 1; i <= 1e5; i ++) cnt[i] = 0;//多测清空
		for (int i = 1; i <= n; i ++) cin >> a[i];
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; i ++) {
			// cntd * phi[d] * (n - i)
			for (auto d : evn[a[i]]) ans += cnt[d] * phi[d] * (n - i);//上文推论
			for (auto d : evn[a[i]]) cnt[d] ++;//更新 cnt[d]
		}
		cout << ans << endl;
	}
	return 0;
}
```
# Updata

- 2024.4.1 因数个数应该为 $\sqrt{n}$。

---

## 作者：fcy20180201 (赞：1)

## 思路
对于每个 $i(1\le i \le \max{a})$，算 $f$ 值为 $i$ 的三元组个数，设为 $res_i$，则 $i$ 对答案的贡献是 $res_i\times i$。

算 $res_i$ 可以先算 $f$ 值**为 $i$ 的倍数**的三元组个数，再减掉 $res_{2i},res_{3i}...$。**总时间复杂度 $\mathcal{O}((\max{a})\log(\max{a}))$。**

对于算 $f$ 值为 $i$ 的倍数的三元组个数（设为 $mul_i$），不难想到可以将数组排序后暴力枚举三元组的中值，枚举到 $a_j$ 时用 $\mathcal O(\sqrt{a_j})$ 的时间复杂度暴力找因数。对于 $a_j$ 的每一个因数 $k$，$a_j$ 对 $mul_k$ 的贡献显然是 **$a_j$ 之前 $k$ 的倍数的个数**（枚举前面中值的因数时顺带计算了）乘上**位置在 $a_j$ 后的元素个数（即 $n-j$）**。时间复杂度 $\mathcal O(n\sqrt{\max a})$。

总时间复杂度 $\mathcal O(T((\max{a})\log(\max{a})+n\sqrt{\max a}))$，能过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int t,n,a[80005];
ll cnt[100005],ans[100005],aans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+n+1);//排序
		memset(cnt,0,sizeof(cnt));//多测不清空，
		memset(ans,0,sizeof(ans));//亲人两行泪。
		for(int i=1;i<=n;i++){
			for(int j=1;j*j<=a[i];j++){//暴力枚举因数
				if(a[i]%j)continue;
				ans[j]+=(cnt[j]++)*(n-i);//对于每个因数算贡献，顺带计算每个数已经出现的倍数的个数。
				if(j*j<a[i])ans[a[i]/j]+=(cnt[a[i]/j]++)*(n-i);
				//一定要特判 j=sqrt(a_i) 的情况。
			}
		}
		aans=0;
		for(int i=a[n];i;i--){//从 f 值为 i 的倍数的三元组中减掉 f 值为多倍的。
			for(int j=2;i*j<=a[n];j++)ans[i]-=ans[i*j];	
			aans+=ans[i]*i;//计算答案
		}
		printf("%lld\n",aans);
	}
	return 0;
}

```

---

## 作者：Diaоsi (赞：1)

[Small GCD](https://www.luogu.com.cn/problem/CF1900D)

欧拉反演

将 $a$ 按照升序排序，转化成求

$$\sum_{i=1}^n(n-i)\sum_{j=1}^{i-1}\text{gcd}(a_i,a_j)$$

套用以下著名等式

$$n=\sum_{d|n}\varphi(d)$$

我们有

$$\begin{aligned}&\sum\limits_{i=1}^n(n-i)\sum\limits_{j=1}^{i-1}\text{gcd}(a_i,a_j)\\=&\sum\limits_{i=1}^n(n-i)\sum\limits_{j=1}^{i-1}\sum\limits_{d|\text{gcd}(a_i,a_j)}\varphi(d)\\=&\sum\limits_{i=1}^n(n-i)\sum\limits_{d|a_i}\varphi(d)\sum_{j=1}^{i-1}[d|a_j]\end{aligned}$$

认为 $n$ 与 $a_i$ 的值域同阶，预处理 $\varphi(n)$ 就可以 $\mathcal{O}(n\sqrt{n})$ 地求这串和式了。

更进一步地，若提前求出 $1\sim n$ 所有数的因数，时间复杂度可降至 $\mathcal{O}(n\log n)$。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N=100010,M=1000010,INF=0x3f3f3f3f;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline void swap(ll &x,ll &y){x^=y^=x^=y;}
ll T,n,ans,a[N],c[N],phi[N];
unordered_map<ll,ll> mp;
void init(){
    phi[1]=1;
    for(ll i=2;i<N;i++)phi[i]=i;
    for(ll i=2;i<N;i++){
        if(phi[i]==i){
            for(ll j=i;j<N;j+=i)
                phi[j]=phi[j]/i*(i-1);
        }
    }
}
void solve(){
	scanf("%lld",&n);
	ans=0;mp.clear();
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(ll i=1;i<=n;i++){
		ll res=0;
		for(ll j=1;j*j<=a[i];j++){
			if(a[i]%j!=0)continue;
            if(j*j==a[i]){
                res+=phi[j]*mp[j];
                continue;
            }
            res+=phi[j]*mp[j];
            res+=phi[a[i]/j]*mp[a[i]/j];
		}
        for(ll j=1;j*j<=a[i];j++){
            if(a[i]%j!=0)continue;
            if(j*j==a[i]){
				mp[j]++;
                continue;
            }
            mp[j]++;
            mp[a[i]/j]++;
        }
        ans+=res*(n-i);
	}
	printf("%lld\n",ans);
}
int main(){
	init();
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```


---

## 作者：hycqwq (赞：1)

赛时没做出来。

第二天把题告诉同机房大佬，想了一天说不会 /ch。

后面看了[官方题解](https://codeforces.com/blog/entry/122677)，同时感谢[这位佬](/user/369181) /bx。

## Solution

与官方题解相似。

定义：

- $m = \max\limits_{j = 1}^n a_j$。
- $cg_i$ 表示对于任意 $1 \le x < y < z \le n$，$f(a_x, a_y, a_z) = i$ 的 $(x, y, z)$ 个数；
- $cm_i$ 表示对于任意 $1 \le x < y < z \le n$，$i | f(a_x, a_y, a_z)$ 的 $(x, y, z)$ 个数；
- $ca_i$ 表示数 $i$ 在 $a$ 中出现的次数；
- $sa_i = \sum\limits_{1 \le j < i, i | j} ca_j$；
- $sc_i = \sum\limits_{j = i}^m ca_i$（后缀和）。

---

答案可表示为：

$$\sum_{j = 1}^m j \cdot cm_j$$

直接求 $cg_i$ 是不容易的，所以我们考虑间接求值。

注意到 $cm_i = \sum\limits_{1 \le j \le m, i |j} cg_j$，可推导出 $cg_i = cm_i - \sum\limits_{i < j \le m, i | j} cg_j$。

于是，我们只需从大到小（$m \to 1$）枚举 $i$，算出 $cg_i$ 代入公式即可。

---

下面讨论 $cm_i$ 的求法。

不妨设 $a_x \le a_y \le a_z$，这导致 $f(a_x, a_y, a_z)$ 与 $a_z$ 无关，所以我们只讨论 $x, y$。

我们知道，若 $i | \gcd(u, v)$，则必有 $i | u, i | v$，反之亦然。

所以，我们要找到 $i | \gcd(a_x, a_y)$ 的方案数，只需找到 $i | a_x, i | a_y$ 的方案数即可。

枚举 $1 \le j \le m, i | j$，考虑取 $j$ 作为 $a_y$ 的情况：

- 若 $a_x < a_y < a_z$，共有 $sa_j \cdot ca_j \cdot sc_{j + 1}$ 种方案；
- 若 $a_x < a_y = a_z$，共有 $sa_j \cdot \left(\large^{ca_j}_2\right)$ 种方案；
- 若 $a_x = a_y < a_z$，共有 $\left(\large^{ca_j}_2\right) \cdot sc_{j + 1}$ 种方案；
- 若 $a_x = a_y = a_z$，共有 $\left(\large^{ca_j}_3\right)$ 种方案。

上述情况可叠加。

于是这道题就这么愉快地结束啦！

对于每个 $1 \le i \le m$，进行两次步长为 $i$ 的遍历，复杂度为 $O(\lfloor \frac{m}{i}\rfloor)$，而 $\sum\limits_{i = 1}^m \lfloor \frac{m}{i}\rfloor \approx m \log m$，于是总复杂度约为 $O(m \log m)$。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int infi = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
#define elif else if
#define il inline

int t, n, m;
ll ca[100005]; // 每个数的计数器
ll sc[100005]; // ca 的后缀和
ll cg[100005]; // 以每个数为 f 的三元组个数

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        memset(ca, 0, sizeof(ca));
        memset(sc, 0, sizeof(sc));
        memset(cg, 0, sizeof(cg));
        m = 0;
        for (int i = 1, a; i <= n; i++)
            cin >> a, ca[a]++, m = max(m, a);
        for (int i = m; i >= 1; i--)
            sc[i] = sc[i + 1] + ca[i];
        for (int i = m; i >= 1; i--) // 从大到小枚举计算 cg
        {
            // 先计算出 f 为 i 的倍数（或 i）的三元组个数
            // 假设三元组为 (a, b, c) 且 a < b < c
            // 枚举 b
            int sa = 0; // 比目前的 b 小的 a 的个数
            for (int b = i; b <= m; b += i)
            {
                // 选至少一个 b，并且不只是最大的
                if (ca[b] >= 1) // 取 1 个 b
                    // 1 小 + 1 b + 1 大
                    cg[i] += sa * ca[b] * sc[b + 1];
                if (ca[b] >= 2) // 取 2 个 b
                    // 1 小 + 2 b + 0 大 / 0 小 + 2 b + 1 大
                    cg[i] += (ca[b] * (ca[b] - 1) / 2) * (sa + sc[b + 1]);
                if (ca[b] >= 3) // 取 3 个 b
                    // 0 小 + 3 b + 0 大
                    cg[i] += ca[b] * (ca[b] - 1) * (ca[b] - 2) / 6;
                sa += ca[b];
            }
            // 再把所有倍数的都减掉
            for (int j = i * 2; j <= m; j += i)
                cg[i] -= cg[j];
        }
        ll ans = 0;
        for (int i = 1; i <= m; i++)
            ans += cg[i] * i;
        cout << ans << endl;
    }
    return 0;
}
```

注释写的有点乱，无伤大雅。

---

## 作者：_sunkuangzheng_ (赞：1)

赛时代码敲错一个地方，一度以为式子推假了，浪费 30min 左右问 chatgpt 要做法，什么也没得到。最后 15 分钟过掉了这题。

简要题意：给定序列 $a$，求：

$$\sum \limits_{i=1}^n(n-i)\sum\limits_{j=1}^{i-1}\gcd(a_i,a_j)$$

推式子。以下记 $ct_j$ 为数组里 $j$ 的出现次数，$p_j$ 为 $j$ 的倍数个数，$m$ 为值域上界。**注意在枚举到 $i$ 时，两个数组的含义是 $1 \sim i-1$ 中的出现次数**。我们把后面一部分提出来：

$$\begin{aligned}&\sum\limits_{j=1}^{i-1}\gcd(a_i,a_j)\\= & \sum\limits_{d|a_i} d \sum \limits_{j=1}^{i-1}[\gcd(a_i,a_j) = d]\\= & \sum\limits_{d|a_i} d \sum \limits_{j=1}^{n}ct_j[\gcd(a_i,j) = d]\\= & \sum\limits_{d|a_i} d \sum \limits_{j=1}^{n}ct_j[\gcd(a_i,j) = d]\\= & \sum\limits_{d|a_i} d \sum \limits_{d|j}ct_j[\gcd(\dfrac{a_i}{d},\dfrac{j}{d}) = 1]\\= & \sum\limits_{d|a_i} d \sum \limits_{j=1}^{\frac{m}{d}}ct_{jd}[\gcd(\dfrac{a_i}{d},j) = 1]\\= & \sum\limits_{d|a_i} d \sum \limits_{j=1}^{\frac{m}{d}}ct_{jd}\sum\limits_{k|\frac{a_i}{d},k|j}\mu(k)\\= & \sum\limits_{d|a_i} d \sum\limits_{k|\frac{a_i}{d}}\mu(k)p_{dk}\end{aligned}$$

考虑对于一个 $i$ 求答案的复杂度。预处理 $\mu$，$p$ 的值在插入元素 $a_i$ 时动态维护可以做到单次 $\mathcal O(\sqrt m)$。单次计算的复杂度等于 $\mathcal O(\sum \limits_{x|a_i}d(x)) \le \mathcal O(\sqrt m \log \sqrt m)$（$d(x)$ 表示 $x$ 的约数数量），那么总复杂度 $\mathcal O(n \sqrt{m} \log \sqrt{m})$，实际根本跑不满。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 26.11.2023 23:47:10
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using namespace std;
#define int long long
const int N = 1e5+5;
int t,n,mu[N],vis[N],ct[N],a[N];vector<int> fac[N],p;
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    for(int i = 1;i < N;i ++)
        for(int j = i;j < N;j += i) fac[j].push_back(i);
    mu[1] = 1,vis[1] = 1,n = N - 1;
    for(int i = 2;i <= n;i ++){
        if(!vis[i]) p.push_back(i),mu[i] = -1;
        for(int j : p){
            if(1ll * i * j > n) break;
            vis[i * j] = 1,mu[i * j] = -mu[i];
            if(i % j == 0){mu[i * j] = 0;break;} 
        }
    }
    while(t --){
        cin >> n,memset(ct,0,sizeof(ct));
        for(int i = 1;i <= n;i ++) cin >> a[i];
        sort(a+1,a+n+1);int res = 0;
        for(int i = 1;i <= n;i ++){
            int ans = 0;
            for(int j : fac[a[i]])
                for(int k : fac[a[i] / j]) ans += j * mu[k] * ct[j * k];
            for(int j : fac[a[i]]) ct[j] ++;
            res += ans * (n - i);
        }cout << res << "\n";
    }
}

```



---

## 作者：huangrenheluogu (赞：0)

VP 的时候没切，真的太菜了。

容易想到将数组排序，枚举两个数，然后算 $\gcd$，第三个数的位置是可以求的，这样容易求得 $ans$，可惜时间复杂度 $\mathcal{O}(n^2)$，无法通过本题。

首先我们需要知道一个常识：一个数的因数不会很多，好像我以前做的一道题中 $5\times 10^5$ 以内因数最多的也只有 $240$ 个（数字可能不准确，请打表验证）。上面这个常识是感觉和因数有关的题需要积累的，这种题多做几遍就会了。

所以，我们可以预处理出一个数的因数，并且把 $a$ 数组正序排序。

对于一个 $i$ 如果我知道 $i$ 和前面的数组成 $\gcd$ 的和 $sum$，那么就可以知道对答案的贡献就是 $sum\times(n-i)$，现在需要求 $sum$。

怎么求 $sum$，考虑容斥。

在处理 $1\sim i-1$ 的时候，我们可以处理出对于一个数 $x$，一个数的因数为 $x$ 这个数的个数。

那么在处理第 $i$ 项的时候，我们对于它的一个因数 $x$，要求**恰好** $\gcd$ 为 $j$ 的个数，记为 $g_j$。

显然，$g_j\le f_j$。

那么 $g_j$ 可以从 $f_j$ 开始，减去 $g_{2j},g_{3j}\dots$，注意减去的这些数的下标也需要满足是 $a_i$ 的因数，这样才说明 $j$ 是 $a_i$ 和另外某一个数的 $\gcd$。

容斥解决。

注意这里每一个数的因数需要倒序取出，这样才可以保证取 $g_i$ 的时候 $g_{2i}$ 等已经处理好了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 8e4 + 5, M = 1e5 + 5, maxn = 1e5;
int T, n, a[N], f[M], tem, cnt, ans, qp[M][32], tot, g[M];
vector<int>num[M], c;
inline void init(){
	for(int i = 1; i <= maxn; i++) f[i] = g[i] = 0ll;
	ans = 0ll;
}
inline int get(int x, int val){
	int res = 0;
	for(auto xx : num[val / x]){
		if(xx != 1) g[x] -= g[x * xx];
	}
	return g[x];
}
inline void solve(){
	for(int i = 1; i < n; i++){
		cnt = 0ll;
		for(auto x : num[a[i]]){
			g[x] = f[x];
			cnt += get(x, a[i]) * x;
		}
		for(auto x : num[a[i]]){
			f[x]++;
		}
//		printf("%d %d\n", i, cnt);
		cnt *= (n - i);
		ans += cnt;
	}
}
inline bool cmp(int x, int y){
	return x > y;
}
signed main(){
	scanf("%lld", &T);
	for(int i = 2; i <= maxn; i++){
		qp[i][0] = 1;
		for(int j = 1; qp[i][j - 1] <= maxn; j++){
			qp[i][j] = qp[i][j - 1] * i;
		}
	}
	num[1].push_back(1);
	for(int i = 2; i <= maxn; i++){
		tem = i;
		tot = 0;
		num[i].push_back(1ll);
		for(int j = 2; j * j <= i; j++){
			if(tem % j) continue ;
			cnt = 0;
			while(tem % j == 0){
				cnt++;
				tem /= j;
			}
			c = num[i];
			for(auto x : c){
				for(int kk = 1; kk <= cnt; kk++){
					num[i].push_back(x * qp[j][kk]);
				}
			}
		}
		if(tem > 1){
			c = num[i];
			for(auto x : c){
				num[i].push_back(tem * x);
			}
		}
		sort(num[i].begin(), num[i].end(), cmp);
	}
	while(T--){
		init();
		scanf("%lld", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sort(a + 1, a + n + 1);
		solve();
		printf("%lld\n", ans);
	}
	return 0;
}
```

[评测链接](https://codeforces.com/contest/1900/submission/236882183)

---

## 作者：233L (赞：0)

莫反练手题。不妨先令 $a$ 为升序，那么 $f(a_i,a_j,a_k)=\gcd(a_i,a_j)\ (i<j<k)$。

做的时候没有马上意识到，应该以 $j$ 作为 “ 中心 ”，$i,k$ 的方案数都容易算出来。

开始反演（我用的欧拉反演），
$$
\sum_{d|n} \varphi(d) =n
$$
代入得到
$$
 ans = \sum_{i=1}^n \sum_{j=i+1}^n \sum_{k=j+1}^n \gcd(a_i,a_j)
$$
$$
= \sum_{i=1}^n \sum_{j=i+1}^n (n-j) \gcd(a_i,a_j)
$$
$$
= \sum_{i=1}^n \sum_{j=i+1}^n (n-j) \sum_{d|\gcd(a_i,a_j)}\varphi(d) $$
$$
= \sum_{d=1}^L \varphi(d) \sum_{i=1}^n \sum_{j=i+1}^n [d|a_i][d|a_j](n-j)
$$
由于 $a$ 在值域上不连续，记 $c_x=\sum_{i=1}^n [a_i=x]$，$s_x=\sum_{i=1}^n [a_i \le x]$，前者是计数，后者是前缀和。先考虑 $a_i<a_j<a_k$ 的答案。
$$
\sum_{d=1}^L \varphi(d) \sum_{i=1}^{\left \lfloor \frac{L}{d} \right \rfloor } sum \times c_{d\times i}(n-s_{d \times i})
$$
其中 $sum=\sum_{j=1}^{i-1}c_{d \times j}$，即过往 $c_{d \times i}$ 的和。

再求 $a_i=a_j<a_k$ 的答案
$$
\sum_{d=1}^L \varphi(d) \sum_{i=1}^{\left \lfloor \frac{L}{d} \right \rfloor } {c_{d\times i} \choose 2}(n-s_{d \times i})
$$

$a_i<a_j=a_k$ 的答案
$$
\sum_{d=1}^L \varphi(d) \sum_{i=1}^{\left \lfloor \frac{L}{d} \right \rfloor } sum{c_{d\times i} \choose 2}
$$

$a_i=a_j=a_k$ 的答案

$$
\sum_{d=1}^L \varphi(d) \sum_{i=1}^{\left \lfloor \frac{L}{d} \right \rfloor } {c_{d\times i} \choose 3}
$$

全部相加即可。时间复杂度 $O(n+V \log V)$。[submission](https://codeforces.com/contest/1900/submission/234469671)


---

## 作者：Mars_Dingdang (赞：0)

来点科技。

受到 CF1575G 的启发，我们使用莫比乌斯反演。

首先，将 $a$ 序列排序，这样 $a_k$ 的贡献就变成了个数上的贡献，式子化为：

$$
\sum_{i=1}^n\sum_{j=i+1}^n\gcd(a_i,a_j)\times (n-j)$$

$$=\sum_{j=2}^{n-1}(n-j)\sum_{i=1}^{j-1} \gcd(a_i,a_j)$$

$$=\sum_{j=2}^{n-1}(n-j)\sum_{i=1}^{j-1}\sum_{d|a_i,d|a_j}\varphi(d)$$

$$=\sum_{j=2}^{n-1}(n-j)\sum_{d|a_j}\varphi(d)\sum_{i=1}^{j-1}[d|a_i]$$

$$=\sum_{j=2}^{n-1}(n-j)\sum_{d|a_j}\varphi(d)cnt_d$$ 

其中 $cnt_d$ 表示当前 $j$ 之前所有 $a$ 是 $d$ 的倍数的个数。

可以 $O(n\ln n)$ 得到所有数的因数，然后直接做就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int T, n, a[maxn];
int prime[maxn], tot, phi[maxn];
bool vis[maxn];
inline void getPhi(int N) {
	vis[0] = vis[1] = 1;
	phi[1] = 1;
	rep(i, 2, N) {
		if(!vis[i]) prime[++ tot] = i, phi[i] = i - 1;
		for(int j = 1; j <= tot && i * prime[j] <= N; ++ j) {
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}
vector <int> pos[maxn], d[maxn];
int cnt[maxn];
inline void getD(int N) {
	rep(i, 1, N) pos[i].clear(), d[i].clear(), cnt[i] = 0;
	rep(i, 1, n) pos[a[i]].push_back(i);
	rep(i, 1, N) 
		for(int v = i; v <= N; v += i) 
			for(auto p : pos[v]) d[p].push_back(i);
}
inline void solve() {
	read(n);
	rep(i, 1, n) read(a[i]);
	sort(a + 1, a + n + 1);
	getD(100000);
	ll ans = 0;
	for(auto div : d[1]) cnt[div] ++;
	rep(j, 2, n - 1) {
		ll res = 0;
		for(auto div : d[j]) {
			res += 1ll * phi[div] * cnt[div];
			cnt[div] ++;
		}
		ans += res * 1ll * (n - j);
	}
	writeln(ans);
}
int main () {
	getPhi(100000);
	read(T);
	while(T --) solve();
	
	return 0;
}
```

---

