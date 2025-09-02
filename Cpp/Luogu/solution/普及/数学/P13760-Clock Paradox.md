# Clock Paradox

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/a4u4v5x2.png)

（来自 phigros 曲绘，侵删）

## 题目描述

给定一个序列 $a$，要求区间 $[l,r]$ 满足 $a_l$ 至 $a_r$ 每个数只在该区间出现一次。设共 $t$ 个区间满足要求，编号为 $[l_1,r_1]$ 至 $[l_t,r_t]$。

求：

$$\sum_{i=1}^t\sum_{j=l_i}^{r_i}a_j$$

请将答案对 $10^9+7$ 取模。

## 说明/提示

数据范围
| 测试点编号 | $n$ | $a_i$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |:-----------: |
| $1$ | $n\le2×10^5$ | $0\le a_i\le10^9$ | A |
| $2$ | $n\le2×10^5$ | $0\le a_i\le10^9$ | B |
| $3,4$ | $n\le 2×10^5$| $0\le a_i\le1$ | |
|$5,6$|$n\le500$|$0\le a_i\le10^9$ | |
|$7\sim10$|$n\le 5×10^3$|$0\le a_i\le n$| |
|$11\sim20$|$n\le2×10^5$|$0\le a_i\le10^9$| |

特殊性质 A：满足所有 $a_i$ 都相等。

特殊性质 B：满足所有 $a_i$ 都互不相等。

对于 $100\%$ 的数据，满足 $1\le n\le2×10^5,0\le a_i\le 10^9$。


## 样例 #1

### 输入

```
6
1 2 3 3 2 1```

### 输出

```
40```

## 样例 #2

### 输入

```
13
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
239```

## 样例 #3

### 输入

```
10 
5 4 3 2 5 6 1 3 1 4```

### 输出

```
315```

# 题解

## 作者：A_Bit_Cold (赞：1)

出题人题解。

对于题目，显然有如下结论。

- 对于满足条件的区间 $[l,r]$，若 $[l,r]$ 为区间的最大限制（即 $[l-1,r]$ 和 $[l,r+1]$ 均不满足条件），则被 $[l,r]$ 内包含的区间都满足条件（包括本身）， 包含 $[l,r]$ 的所有区间都不满足要求（不包括本身）。

对于以上的结论，我们可以这样考虑，每次以 $r\in[1,n]$ 做为结尾，看最多能往前推多少个，记最小左边界为 $l_0$，则区间 $[l_0+k,r](k\in[0,r-l_0])$ 均满足条件。

然而，我们在求 $l_0$ 时，显然不能一个个枚举，由于数字范围较大，考虑使用 map，$v$ 记录数字最近出现的位置，发现到 $l_0$ 是非递减的，我们可以将每次新增入的数与最近出现的位置进行比较，看是不是包含在已选区间内，如果包含，直接调到最近出现的数的后一个位置即可。每次答案为 $r-l_0$。那 $\sum$ 的问题如何考虑呢？

有以下等式：

$$\sum_{i=l}^r(i-l+1)×a_i=\sum_{i=1}^ri×a_i-\sum_{i=1}^{l-1}i×a_i-(l-1)\left(\sum_{i=1}^ra_i-\sum_{i=1}^{l-1}a_i\right)$$

发现到，等式的右边三项只需要我们用 $O(n)$ 的时间复杂度用前缀和预处理 $\sum\limits_{i=1}^ni×a_i$ 和 $\sum\limits_{i=1}^na_i$，其中 $\sum\limits_{i=1}^ni×a_i$ 这一项可以借助 $\sum\limits_{i=1}^na_i$ 使用双重前缀和推，也可以直接使用一次前缀和求出。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const long long MOD=1e9+7;
long long a[N],s[N],s2[N],ans;
map <long long,int> v;
int main() {
	int n; cin>>n;
	for(int i=1;i<=n;i++)
        cin>>a[i];
	for(int i=1;i<=n;i++)
        s[i]=(s[i-1]+a[i])%MOD;
	for(int i=1;i<=n;i++)
        s2[i]=(s2[i-1]+(a[i]*i)%MOD)%MOD;
	int l=1;
	for(int i=1;i<=n;i++) {
		int r=i;
        l=max(l,v[a[i]]+1),v[a[i]]=i;
	    ans=(ans+(s2[r]-s2[l-1]+MOD)%MOD-((l-1)*((s[r]-s[l-1]+MOD)%MOD)%MOD)%MOD+MOD)%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yihang2011 (赞：1)

### [P13760 Clock Paradox](https://www.luogu.com.cn/problem/P13760)

前缀和套前缀和。

~~根据标签~~，得知应该用双指针做。枚举右端点 $r$，找到以 $r$ 为右端点，以 $l$ 为左端点时区间 $[l, r]$ 满足条件的最小的 $l$，那么这个右端点 $r$ 对答案的贡献为：

$$\begin{aligned} 
& \sum_{i = l}^{r} \sum_{j = i}^{r} a_j \\

=& \space (a_l + a_{l + 1} + \cdots + a_r) + (a_{l + 1} + \cdots + a_r) + \cdots + (a_{r - 1} + a_r) + a_r
\end{aligned}
$$

直接求时间无法承受，考虑前缀和优化，记 $s_i = \sum_{j = 1}^{i}{a_j}$，原式变为：

$$
(s_r - s_{l - 1}) + (s_r - s_l) + \cdots + (s_r - s_{r - 2}) + (s_r - s_{r - 1})
$$

显然，这样算时间复杂度为 $\mathcal{O}(n^2$)，依然无法承受，可以将其变形：

$$
(r - l + 1) \times s_r - (s_{l - 1} + s_l + s_{l + 1} + \cdots + s_{r - 2} + s_{r - 1})
$$

可以看出，后面一部分依然可以使用前缀和优化，所以记 $ss_i = \sum_{j = 1}^{i}{s_j}$，则最后 $r$ 对答案的贡献为：

$$
(r - l + 1) \times s_r - (ss_{r - 1} - ss_{l - 2})
$$

请注意 $ss_{l - 2}$ 可能存在的下标越界。

----

为判断区间合法性，可以使用 `std::map`，$mp_x$ 的值为 $x$ 在当前区间 $[l, r]$ 内的位置，如果没有则为 $0$。每遍历到新的 $r$，都需要判断对应的 $mp_{a_r}$ 是否存在，如果存在，需要先将 $mp_{a_i} \gets 0\space(l \le i \le mp_{a_r})$，不属于本区间的元素位置置为 $0$；再将 $l \gets mp_{a_r} + 1$，以保证区间合法。 

时间复杂度 $\mathcal{O}(n \log n)$。

可以使用 `std::unordered_map`，时间复杂度可以做到接近 $\mathcal{O}(n)$，实测确实会快一点。

注意减法取模问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define seta(f, x) memset(f, x, sizeof f)
using ll = long long;
#define gc getchar()
ll read() { ll x = 0, f = 1; char ch = gc; while (ch < '0' || ch > '9') { if (ch == '-') { f = -1; } ch = gc; } while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0', ch = gc; } return x * f; }
#define rd read()
void write(const string& s) { for (char c : s) { putchar(c); } }
void write(ll x) { if (x < 0) { putchar('-'), x = -x; } if (x > 9) { write(x / 10); } putchar(x % 10 + '0'); }
void write(double x, int len) { ll i = x, s = round(1.0 * (x - i) * (pow(10, len))); write(i); putchar('.'); write(s); } 
template<typename... Args> void wrt(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrt(rest...); } }
template<typename... Args> void wrln(ll x, Args... rest) { write(x); if constexpr (sizeof...(rest) > 0) { putchar(' '); wrln(rest...); } else { putchar('\n'); } }
#define wln(x) write(x); putchar('\n')
#define wt(x) write(x); putchar(' ')

const int N = 2e5 + 10, mod = 1e9 + 7;
int n, a[N];
ll s[N], ss[N], ans;
map<int, int> mp;

int main() {
    n = rd;
    for (int i = 1; i <= n; i++) {
        a[i] = rd;
        s[i] = (s[i - 1] + a[i]) % mod;
        ss[i] = (ss[i - 1] + s[i]) % mod;
    }
    for (int l = 1, r = 1; r <= n; r++) {
        if (mp[a[r]] != 0) {
            int tmp = l;
            l = mp[a[r]] + 1;
            for (int k = tmp; k <= mp[a[r]]; k++) {
                mp[a[k]] = 0;
            }
        }
        mp[a[r]] = r;
        (ans += ((r - l + 1) * s[r] % mod) + mod - ((ss[r - 1] - ss[max(0, l - 2)]) % mod)) %= mod;
    }
    wln(ans);
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/231931680)，使用 `std::map`。

[AC Record](https://www.luogu.com.cn/record/231943155)，使用 `std::unordered_map`。

---

## 作者：Milky_Cat (赞：1)

标题是题目背景对应的收藏品。

这个题真的有一点板子啊。

很容易发现答案是单调的，然后我们要维护每一段区间。

考虑双指针，维护区间和，很容易在向右移动的时候加上应该加的贡献。

但是有一个问题是，左端点移动后，对于新的左端点，有一些区间不会被扫到。我们尝试多维护一个东西。

可以发现，以当前扫到的 $l$ 为左端点，右端点不在当前扫到的 $r$ 右侧的区间是容易维护的。于是维护这个东西。左端点右移只需要减去左端点处的值乘区间数。这样子移完左端点可以直接加上扫不到的区间的贡献。然后就做完了。

用 `unordered_map` 统计扫到区间内的每一个数个数。也可以手写哈希表，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000005], ans, hc;
const int mod = 1000000007;
unordered_map<int, int> mp;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int l = 1, r = 0, sum = 0;
	for (; l <= n; l++){
		ans = (ans + hc) % mod;
		while (r < n && !mp[a[r + 1]]){
			++r;
			mp[a[r]]++;
			sum = (sum + a[r]) % mod;
			hc = (hc + sum) % mod;
			ans = (ans + sum) % mod;
		}
		mp[a[l]]--;
		hc = ((hc - (r - l + 1) * a[l] % mod) % mod + mod) % mod;
		sum = ((sum - a[l]) % mod + mod) % mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Curry_mvp (赞：1)

预估有黄。

计算满足所有元素只出现一次的区间的元素和的总和。

好绕口啊······

首先想到的是双指针做法，主要是受到[这道题的启发](https://www.luogu.com.cn/problem/P1638)，双指针遍历整个数组，用桶数组记录出现的次数，但元素太大，所以暂时放弃桶数组。

考虑优化，双指针依旧能用，离散化映射一下，再用前缀和，高效运算区间和。

说一下区间贡献，对于每个右端点，我们需要计算所有以优选店结尾的无重复元素子区间的和的总和，先加上所有区间的总和，再减去左端点以前的所有区间的总和，记为左右端点之间所有区间的总和。注意判断好下标范围，防止出现负数下标。

我代码中的第二个前缀和数组，也就是前缀和的前缀和数组，同样是区间计算的优化。

注意取模。

具体可以看一下代码，我也说不清楚。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long int
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int mod=1e9+7;
const int maxn=2e5+5;
int a[maxn]; 
int b[maxn];
int c[maxn];
int d[maxn];
int cnt[maxn];
int tmp[maxn];
int n;
int l=1;
int r=1;
int ans=0;
int tot;
int len;
int t;
void begin()
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(d,0,sizeof(d));
	memset(cnt,0,sizeof(cnt));
	memset(tmp,0,sizeof(tmp));
}
int res=0;
signed main() 
{
    n=read();
    begin();
    for(int i=1;i<=n;i++) 
	{
        cin>>a[i];
        tmp[i]=a[i];
    }
    sort(tmp+1,tmp+n+1);
    tot=unique(tmp+1,tmp+n+1)-tmp-1;//去重 
    for(int i=1;i<=n;i++) 
    {
    	b[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;//离散化 
	}
    for(int i=1;i<=n;i++)
	{
		c[i]=(c[i-1]+a[i])%mod;//计算原数组的前缀和数组 
	}
    d[0]=c[0];
    for(int i=1;i<=n;i++)
	{
		d[i]=(d[i-1]+c[i])%mod;//前缀和数组的前缀和数组 
	}

    for(r=1;r<=n;r++) 
	{
        cnt[b[r]]++;
        while(cnt[b[r]]>1)
		{
			cnt[b[l]]--;
			l++;
		}
        len=r-l+1;
        t=0;
        if(l!=1)
        {
        	t=d[l-2];
		}
        res=(len*c[r]%mod-(d[r-1]-t+mod)%mod+mod)%mod;//计算区间贡献 
        ans=(ans+res)%mod;
    }
    cout<<ans<<"\n";  
    return 0;
}
```

---

## 作者：jzy20241021062 (赞：0)

## 题目简述

对于一个序列 $a$，要求找到它的所有无重复元素的连续子序列，求出这些子序列的和。

## 题解

我们可以定义两个前缀和，记 $S$ 为 $a$ 的前缀和，$R$ 为 $S$ 的前缀和。

我们用滑动窗口 $[l,r]$，使得其中元素两两不相同。

维护一个哈希表 $h[x]$，记录 $x$ 上次出现的下标，对于每个新的右端点 $r$，更新 
$$l=\max(l, h[a_r]+1)$$
同时更新 $h[a_r]$。

此时可以保证 $[l, r]$ 是所有以 $r$ 为右端点，且无重复元素的最长连续子序列。

于是计算所有以 $r$ 为右端点的所有合法子序列的和. 其中合法子序列区间下标为 $[t,r],\:l\leq t\leq r$，于是它们的区间和
$$\begin{aligned}\sum_{t=l}^{r}\sum_{k=t}^{r}a_k&=\sum_{t=l}^{r}\left(S_r-S_{t-1}\right)\\&=\left(r-l+1\right)S_r-\sum_{t=l}^{r}S_{t-1}\\&=(r-l+1)S_r-(R_{r-1}-R_{l-2})\end{aligned}$$

为了防止数组越界，需要特判 $l=1$ 的情况。

## AC 代码
```
#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 2e5 + 5, mod = 1e9 + 7;

int a[N], S[N], R[N];

unordered_map<int, int> h;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) S[i] = (S[i - 1] + a[i]) % mod;
    for (int i = 1; i <= n; i ++) R[i] = (R[i - 1] + S[i]) % mod;
    int ans = 0;
    int l = 1;
    for (int r = 1; r <= n; r ++){
        if (h.count(a[r]))
            l = max(l, h[a[r]] + 1);
        h[a[r]] = r;
        int cnt = r - l + 1;
        int s1 = (R[r - 1] - (l >= 2 ? R[l - 2] : 0) + mod) % mod;
        int s2 = ((long long) cnt * S[r] % mod - s1 + mod) % mod;
        ans = (ans + s2) % mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：lyx128 (赞：0)

看到 $\sum_{i=1}^t\sum_{j=l_i}^{r_i}a_j$ 这个式子，很快就能想到前缀和套前缀和，而要求只能出现一次很快就能想到用二分或者双指针实现。思路很简单，代码更简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5;
const ll mod=1e9+7;
int n;
ll a[N+5];
ll o[N+5];
ll sum[N+5];
ll ssum[N+5];
ll ans;

unordered_map<ll,ll> t;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=(sum[i-1]+a[i])%mod;
        ssum[i]=(ssum[i-1]+sum[i])%mod;
    }
    int j=1;
    for(int i=1;i<=n;i++){
        while(j<=n&&!t[a[j]])
            ++t[a[j++]];
        ans+=(ssum[j-1]-ssum[i-1]+mod-sum[i-1]*((j-1)-i+1)%mod+mod)%mod;
        ans%=mod;
        --t[a[i]];
    }
    cout<<ans<<"\n";
    return 0;
}

```

---

