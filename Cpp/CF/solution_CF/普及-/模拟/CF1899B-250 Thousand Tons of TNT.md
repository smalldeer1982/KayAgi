# 250 Thousand Tons of TNT

## 题目描述

Alex is participating in the filming of another video of BrMeast, and BrMeast asked Alex to prepare 250 thousand tons of TNT, but Alex didn't hear him well, so he prepared $ n $ boxes and arranged them in a row waiting for trucks. The $ i $ -th box from the left weighs $ a_i $ tons.

All trucks that Alex is going to use hold the same number of boxes, denoted by $ k $ . Loading happens the following way:

- The first $ k $ boxes goes to the first truck,
- The second $ k $ boxes goes to the second truck,
- $ \dotsb $
- The last $ k $ boxes goes to the $ \frac{n}{k} $ -th truck.

Upon loading is completed, each truck must have exactly $ k $ boxes. In other words, if at some point it is not possible to load exactly $ k $ boxes into the truck, then the loading option with that $ k $ is not possible.

Alex hates justice, so he wants the maximum absolute difference between the total weights of two trucks to be as great as possible. If there is only one truck, this value is $ 0 $ .

Alex has quite a lot of connections, so for every $ 1 \leq k \leq n $ , he can find a company such that each of its trucks can hold exactly $ k $ boxes. Print the maximum absolute difference between the total weights of any two trucks.

## 说明/提示

In the first case, we should pick two trucks, so the first one will have only the first box, and the second one will have only the second box.

In the second case, we should pick six trucks, so the maximum will be $ 10 $ , the minimum will be $ 1 $ , and the answer is $ 10 - 1 = 9 $ .

In the third case, for any possible $ k $ , the trucks will have the same total weight of boxes, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
2
1 2
6
10 2 3 6 1 3
4
1000000000 1000000000 1000000000 1000000000
15
60978 82265 78961 56708 39846 31071 4913 4769 29092 91348 64119 72421 98405 222 14294
8
19957 69913 37531 96991 57838 21008 14207 19198```

### 输出

```
1
9
0
189114
112141```

# 题解

## 作者：wmrqwq (赞：3)

# 题目链接

[CF1899B 250 Thousand Tons of TNT](https://www.luogu.com.cn/problem/CF1899B)

# 题意简述

有 $n$ 个数需要分成 $k$ 组，当且仅当 $n \bmod k=0$，同时分组方式为：

$\{a_1,a_2, \dots a_{n/k}\},\{a_{n/k+1},a_{n/k+2},\dots a_{2 \times n/k}\},\dots,\{a_{(n-1) \times n/k+1},a_{(n-1)/k+2},\dots,a_{n}\}$。

共分成 $k$ 组，你需要构造一个 $k$ 使得分成的所有组中的最大值和最小值的绝对值之差最大。

# 解题思路

首先大家肯定会有一个思路，就是暴力枚举 $n$ 的因数，但是时间复杂度为 $O(n^2)$，不能通过此题，这时我们考虑优化一下，容易发现枚举到 $\sqrt{n}$ 的时候就可以枚举完 $n$ 的所有因数了，时间复杂度为 $n \times \sqrt{n}$，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200010],sum[200010],ans;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			sum[i]=0;
		for(int i=1;i<=n;i++)
			cin>>a[i],sum[i]=sum[i-1]+a[i];
		sort(a+1,a+1+n);
		for(int i=1;i*i<=n;i++)
		{
			if(n%i==0)
			{
				long long maxn=-1e18,minn=1e18;
				for(int j=i;j<=n;j+=i)
				{
					maxn=max(maxn,sum[j]-sum[j-i]);
					minn=min(minn,sum[j]-sum[j-i]);
				}
				ans=max(ans,maxn-minn);
				maxn=-1e18,minn=1e18;
				for(int j=n/i;j<=n;j+=n/i)
				{
					maxn=max(maxn,sum[j]-sum[j-n/i]);
					minn=min(minn,sum[j]-sum[j-n/i]);
				}
				ans=max(ans,maxn-minn);
			}
		}
		cout<<ans<<endl;
	}
	QwQ;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1899B 250 Thousand Tons of TNT](https://www.luogu.com.cn/problem/CF1899B)

## 解题思路

显然 $n$ 必须是 $k$ 的倍数才能使每辆车的箱子数量相同，所以 $n$ 的因子就是所有可能的 $k$。

枚举 $n$ 的所有因子，对于每个因子 $k$，用前缀和计算 $\frac{n}{k}$ 辆车重量的极差，最后取最大值即为答案。

时间复杂度低于调和级数：$O(\sum_{d|n}\frac{n}{d})<O(\sum_{i=1}^{n}\frac{n}{i})=O(n\log{n})$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
const int N=150005;
ll a[N];
ll f(int n,int k)
{
	ll mx=-inf,mn=inf;
	for(int i=0;i<n/k;i++)
	{
		ll val=a[k*(i+1)]-a[k*i];
		mx=max(mx,val);
		mn=min(mn,val);
	}
	return mx-mn;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			a[i]+=a[i-1];
		}
		ll ans=-inf;
		for(int i=1;i<=n;i++)
		{
			if(n%i==0)
			{
				ans=max(ans,f(n,i));
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Focalors (赞：1)

由于 $n$ 的范围较小，且 $k$ 为 $n$ 的因数，可以暴力枚举每个 $k$ 进行计算。

然后求出每 $k$ 个一组时的最大总和和最小总和之差，将这些差取最大值即可。

时间复杂度 $\mathcal{O}(n\sqrt{n})$。

代码：
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read() {
	ll x = 0, y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c & 15), c = getchar();
	return x * y;

}
const int N = 15e4 + 7;
ll T, n, t[N], ans;
void fufu(ll i) {
	ll sum = 0;
	ll maxn = LLONG_MIN, minn = LLONG_MAX; 
	for (int j = 1; j <= n; j++) {
		sum += t[j];
		if (j % i == 0) {
			minn = min(minn, sum);
			maxn = max(maxn, sum);
			sum = 0;
		}
	}
	ans = max(ans, maxn - minn);
}
int main() {
	T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; i++) {
			t[i] = read();
		}
		ans = 0;
		for (int i = 1; i * i <= n; i++)
			if (n % i == 0) {
				fufu(i);
				if (i * i != n) fufu(n / i);
			}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：BugGod (赞：0)

首先考虑暴力做法，我们可以枚举 $n$ 的因数 $k$，然后暴力求和计算答案，求最大值。一个数的因数数量最多有 $\sqrt{n}$ 个，每次计算要枚举一遍每个数，复杂度为 $O(n\sqrt{n})$，可能会被卡。看到连续一段区间和，想到前缀和优化求和计算，复杂度低于 $\sum_{i=1}^n\frac{n}{i}=n(\sum_{i=1}^n\frac{1}{i})\approx n\log n$，所以可以轻松通过。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int t,n,a[150010],sum[150010],ans,ys[150010],cnt;//ys记录n的因数，即k的所有情况
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cnt=0;ans=0;//多测不清空，亲人两行泪
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n;i++)if(n%i==0)ys[++cnt]=i;
		for(int i=1;i<=cnt;i++)
		{
			int maxx=0,minn=9e18;
			for(int j=1;j<=n;j+=ys[i])
			{
				int s=sum[ys[i]+j-1]-sum[j-1];
				maxx=max(maxx,s);
				minn=min(minn,s);
			}
			ans=max(ans,maxx-minn);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题面](https://www.luogu.com.cn/problem/cf1899b)

[CodeForces 原题面](https://codeforces.com/problemset/problem/1899/B)

有 $t$ 组数据。每组数据给定 $n(1\le n\le 1.5\times 10^5)$ 个货物，重量为序列 $a(1\le a_i\le 10^9)$。

定义一组的重量为这一组中所有货物的重量之和。

请你找到一个分组数量 $k$（$k$ 是 $n$ 的因数），并按照如下方案分组后，使得每一组的重量的最大值减去每一组的重量的最小值最小。输出这个最小值。

- 第 $1\sim k$ 个货物为第 $1$ 组；

- 第 $k+1 \sim 2\times k$ 个货物为第 $2$ 组；

- $\dots$

- 第 $n-k+1\sim n$ 个货物为第 $\dfrac{k}{n}$ 组。

# 分析
不难想到需要枚举 $k$。

那么，对于每一个 $k$，我们需要求出每一组货物重量的最大值和最小值。

此时的时间复杂度是 $O(n^2)$ 的。

但是可以注意到，由于一组内的货物在原序列上一定时连续的。那么我们就可以使用前缀和优化，然后每次 $O(1)$ 求解一组货物的重量。

此时的时间复杂度为 $O(n\log n)$，可以通过此题。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 1.5e5 + 5;
int n, a[MAXN], qz[MAXN];
int get(int l, int r){
  return qz[r] - qz[l - 1];
}
void Solve(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
    qz[i] = qz[i - 1] + a[i];
  }
  int ans = -1;
  for (int i = 1; i <= n; i++){
    if (n % i == 0){
      int minn = 1e18, maxx = -1e18;
      for (int j = 1; j <= n; j += i){
        minn = min(minn, get(j, j + i - 1));
        maxx = max(maxx, get(j, j + i - 1));
      }
      ans = max(ans, maxx - minn);
    }
  }
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

考虑枚举 $k$，发现这个 $k$ 一定要是 $n$ 的因数，所以合法的 $k$ 最多只会有 $\log n$ 级别的数量。

那么已知 $k$ 就可以直接用前缀和优化一下即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,inf = (int)(1e18) + 10;
int T,n;
int arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int ans = -inf;
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = arr[i - 1] + read();
    for (re int i = 1;i <= n;i++){
        if (n % i == 0){
            int Min = inf,Max = -inf;
            for (re int j = i;j <= n;j += i){
                int sum = arr[j] - arr[j - i];
                Max = max(Max,sum);
                Min = min(Min,sum);
            }
            ans = max(ans,Max - Min);
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

解法 $1$：

枚举 $n$ 的因数，暴力算出每个 $k$ 对应的答案，最后求最大值。

由于一个数的因数个数最多只有 $\sqrt[3]{n}$，因此复杂度为 $O(\sum n\times\sqrt[3]{n})$。

```cpp
void sol1(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(n%i==0){
			int mx=-0x3f3f3f3f,mn=0x3f3f3f3f;
			for(int j=1;j<=n;j++){
				int sum=0;
				for(int k=i;k<=i+j-1;k++){
					sum+=a[k];
				}
				mx=max(mx,sum);
				mn=min(mn,sum);
				//此处可以用前缀和优化。
			}
			ans=max(ans,mx-mn);
		}
	}
	cout<<ans<<endl;
}
```


------------
解法 $2$：

暴力枚举 $k$，利用前缀和思想优化，再在所有合法答案中取最大值即可。

时间复杂度为：$O(\sum\sum\limits^{n}_{i=1}\frac{n}{i})$，因为 [级数求和](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971?fr=ge_ala)，所以复杂度为 $O(\sum n\log n)$。

```cpp
int sum[150005];
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int mx=-0x3f3f3f3f,mn=0x3f3f3f3f;
		bool fg=true;
		for(int j=1;j<=n;j+=i){
			mx=max(mx,sum[j+i-1]-sum[j-1]);
			mn=min(mn,sum[j+i-1]-sum[j-1]);
			if(j+i>n){
				fg=false;
				break;
			}
		}
		if(fg) ans=max(ans,mx-mn);
	}
```


------------

解法 $3$：

将上面两种方法优化，也就是将解法 $1$ 中的暴力求和改为前缀和。

```cpp
void sol3(){
	int sum[150005];
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(n%i==0){
			int mx=-0x3f3f3f3f,mn=0x3f3f3f3f;
			for(int j=1;j<=n;j+=i){
				mx=max(mx,sum[j+i-1]-sum[j-1]);
				mn=min(mn,sum[j+i-1]-sum[j-1]);
			}
			ans=max(ans,mx-mn);
		}
	}
	cout<<ans<<endl;
}
```


---

## 作者：zhangshuhang2011 (赞：0)

## 思路

- 因为车必须装满，所以 $k$ 必须是 $n$ 的因数。
- 枚举因数可以做到 $O(\sqrt{n})$，所以每一类的计算最多 $O(n)$。
- 于是考虑前缀和优化，经试验可行，故最终算法为**模拟+前缀和优化**。

## 注意

- 组内的和最多为 $10^9 \times 150000 = 1.5 \times 10^{15}$，**要开 `long long`**。
- 同理最小值的初始值应大于 $1.5 \times 10^{15}$，代码中使用 $10^{18}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[150005], sa[150005];
void solve(){
    cin >> n;
    sa[0] = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        sa[i] = sa[i-1] + a[i];
    }
    int maxd = 0;
    for(int i = 1; i*i <= n; i++){
        if(n % i == 0){
            int maxx = 0;
            int minx = 1e18;
            for(int j = 1; j <= n; j += i){
                int x = sa[j+i-1] - sa[j-1];
                minx = min(minx, x);
                maxx = max(maxx, x);
            }
            maxd = max(maxd, maxx - minx);
            if(i * i < n){
                maxx = 0;
                minx = 1e18;
                for(int j = 1; j <= n; j += n/i){
                    int x = sa[j+n/i-1] - sa[j-1];
                    minx = min(minx, x);
                    maxx = max(maxx, x);
                }
                maxd = max(maxd, maxx - minx);
            }
        }
    }
    cout << maxd << endl;
}
signed main(){
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

暴力。

对于一个 $k$，若 $n$ 是 $k$ 的倍数，则暴力枚举出来每一辆卡车装载货物的重量。此时的最大差值就是最大重量与最小重量之差。用前缀和就可以求出来。最后的答案就是每个 $k$ 所对应的最大差值的最大值。不难发现，在求每辆卡车装载货物的重量的复杂度是 $O(\frac{n}{k})$ 的。加起来就大约是 $O(n\log n)$。

## 代码

[Link](https://codeforces.com/contest/1899/submission/233113671).

---

