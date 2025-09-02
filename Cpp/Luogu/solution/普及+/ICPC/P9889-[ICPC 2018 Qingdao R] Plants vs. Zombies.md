# [ICPC 2018 Qingdao R] Plants vs. Zombies

## 题目描述

BaoBao 和 DreamGrid 正在玩游戏《植物大战僵尸》。在游戏中，DreamGrid 种植植物来保护他的花园免受 BaoBao 的僵尸攻击。

![](https://cdn.luogu.com.cn/upload/image_hosting/9tyl9ix3.png)

《植物大战僵尸（？）》

（图片来自 pixiv。ID: 21790160；艺术家：socha）

DreamGrid 的花园里有 $n$ 株植物，按一条直线排列。从西到东，植物从 1 到 $n$ 编号，第 $i$ 株植物位于 DreamGrid 的房子东边 $i$ 米处。第 $i$ 株植物的防御值为 $d_i$，生长速度为 $a_i$。最初，所有 $1 \le i \le n$ 的 $d_i = 0$。

DreamGrid 使用一个机器人来浇灌植物。机器人最初在他的房子里。在一次浇水步骤中，DreamGrid 会选择一个方向（东或西），机器人沿该方向正好移动 1 米。移动后，如果第 $i$ 株植物位于机器人的位置，机器人将浇灌植物，并将 $a_i$ 加到 $d_i$ 上。由于机器人的水是有限的，最多可以进行 $m$ 步。

花园的防御值定义为 $\min\{d_i | 1 \le i \le n\}$。DreamGrid 需要你的帮助来最大化花园的防御值并赢得比赛。

- 每次机器人必须在浇灌植物之前移动；
- 机器人可以移动超过 $n$ 米到房子东边，或者移回房子，甚至移动到房子西边。

## 说明/提示

在下面的解释中，`E` 表示机器人从当前位置向东移动 1 米，`W` 表示机器人从当前位置向西移动 1 米。

对于第一个测试用例，一个候选方向序列是 $\{E, E, W, E, E, W, E, E\}$，这样我们有 $d = \{6,6,12,6\}$ 在浇水后。

对于第二个测试用例，一个候选方向序列是 $\{E, E, E, E, W, E, W, E, W\}$，这样我们有 $d = \{10, 10, 4\}$ 在浇水后。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
4 8
3 2 6 6
3 9
10 10 1```

### 输出

```
6
4```

# 题解

## 作者：_sh1kong_ (赞：6)

[In Luogu](https://www.luogu.com.cn/problem/P9889)

### Solution
容易发现答案具有单调性，考虑二分。

令 $mid$ 为当前二分到的答案。

从第 $1$ 个植物开始遍历。

假设当前遍历到第 $i$ 植物，高度为 $h_i$，那么便会有两种情况。

1. $h_i \geq mid$，那么这个植物不需要继续增长。
2. $h_i < mid$，此时这个植物没有达到要求，需要增长。

对于第一种情况，继续往右走一步即可。

对于第二种情况，显然有一个贪心的策略：不断地在这个植物以及右边的那个植物之间走动，直到当前这个植物的高度达到要求为止。

对于第二种情况，代码如下。

```cpp
if (high[i] < x)
{
	int t = (x - high[i] - 1) / b[i] + 1;//需要的次数
	high[i] += t * b[i];
	high[i + 1] += b[i + 1] * (t - 1);
	num -= (t << 1);++ num;
}
```

最后判断步数是否 $\leq m$ 即可。

注意 ```long long```。

### Code
```cpp
bool chk(int x)
{
	for (int i = 1; i <= n; i ++ ) high[i] = 0;
	int num = m;
	for (int i = 1; i <= n; i ++ )
	{
		if (high[i] < x)
		{
			int t = (x - high[i] - 1) / b[i] + 1;
			high[i] += t * b[i];
			high[i + 1] += b[i + 1] * (t - 1);
			num -= (t << 1);++ num;
		}
		else 
		{
			if (i == n) return true;
			-- num;
		}
		if (num < 0) return false;
	}
	return num >= 0;
}

void solve()
{	
	n = re, m = re;
	for (int i = 1; i <= n; i ++ ) b[i] = re;
	int l = 0, r = 0x3f3f3f3f3f3f, ans = 0;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (chk(mid + 1)) l = mid + 1, ans = mid + 1;
		else r = mid;
	}
	cout << ans << '\n';
}
```

---

## 作者：Alex_Wei (赞：5)

### [P9889 [ICPC2018 Qingdao R] Plants vs. Zombies](https://www.luogu.com.cn/problem/P9889)

*目前为止，本题的所有题解均没有给出贪心的正确性证明。这样不求甚解的态度是需要避免的。

二分高度 $h$ 求出每个位置至少走多少次，记作 $c_i = \lceil \frac h {a_i} \rceil $，并计算达到该目标至少走多少次。

因为 $c_i > 0$，所以一定会走到最右侧。考虑贪心，如果当前位置 $p$ 左侧还需要走，那么往左走，否则往右走。

> **证明**
>
> 如果左侧已经不需要走，那么往左走显然是不优的。
>
> 如果左侧需要走，那么 $p\geq 2$。考虑接下来的路径 $P$，若 $P$ 在当前这一步向右走，则它总会回到 $p$ 并向左走。
>
> - 如果向左走之后仍回到 $p$，那么将 $P$ 在 $p$ 及其左边的这一段平移到当前这一步。
> - 如果向左走之后不回到 $p$，那么：
>   - 若 $p = 2$，则路径最终会停在 $1$，将 $p\to Q\to p\to 1$ 调整为 $p\to 1\to p\to Q ^ R$ 即可，其中 $Q ^ R$ 是 $Q$ 翻转后的结果。
>   - 若 $p > 2$，根据贪心过程，如果不是位置 $p - 2$ 已经达到目标，路径不会走到 $p$，于是路径最终会停在 $p - 1$，类似 $p = 2$ 证明即可。这部分需要归纳以保证正确性：$p$ 正确推出 $p + 1$ 的前提。
>
> 于是，对于任意一条最优路径，总可以将其每一步依次调整为上述贪心过程走过的路径，这也就证明了贪心的正确性。$\square$

贪心过程直接模拟即可，注意路径最终可能停在 $n - 1$，并注意中途累计的步数可能很大，需要在不合法时立刻停止。

时间复杂度 $\mathcal{O}(n\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

// ---------- templates above ----------

constexpr int N = 1e5 + 5;

ll n, m, a[N], f[N], g[N];
bool check(ll x) {
  ll nxt = 0, res = 0;
  for(int i = 1; i <= n; i++) {
    ll cnt = (x - 1) / a[i] + 1 - nxt;
    if(cnt > 0 || i < n) res++, cnt--;
    cnt = max(cnt, 0ll);
    res += cnt * 2, nxt = cnt;
    if(res > m) return 0;
  }
  return 1;
}
void solve(int T) {
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> a[i];
  if(n > m) {
    cout << "0\n";
    return;
  }
  ll l = 1, r = m * 1e5;
  while(l < r) {
    ll mid = l + r + 2 >> 1;
    if(check(mid)) l = mid;
    else r = mid - 1;
  }
  cout << l << "\n";
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  cin >> T;
  while(T--) solve(T);
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：CaiZi (赞：4)

#### [题目链接](https://www.luogu.com.cn/problem/P9889)
### 题目描述
有 $n$ 个被冰车碾了的植物（初始高度为 $0$），种在 $1 \sim n$ 的的位置，你初始处于戴夫家（位置为 $0$）。每步可以使自己的位置 $+1$ 或 $-1$。求在走完 $m$ 步后最小植物高度的最大值。
### 题目分析
求最小值的最大值的题目大概率都是二分答案。

然而确实是，让我们分析一下如何二分。显然答案具有单调性，若最小植物高度最大值为 $x$，那么小于 $x$ 的数也一定能达到。所以选择二分 $x$。其中下界为 $0$，上界为 ```LONG_LONG_MAX```，当然你设置一些其他的数字也可以。

接下来我们创建一个 $b$ 数组，表示第 $i$ 个植物需要浇 $b_i$ 次水才可以达到 $mid$，设 $b_i=\Large\lceil\frac{a_i}{mid}\rceil$。那么很显然，最优解便是使位置不断 $+1$ 再 $-1$。因此对于每棵植物，如果其还没有走到足够的步数，那么便将总步数增加 $b_i \times 2+i-u-2$，同时将 $b_{i+1}\gets b_{i+1}-b_i+1$，其中 $u$ 为上一个没有走到足够步数的点，而减少的两步目的是减少走完后多走的 $1$ 次，$i-u$ 为两个无需浇水之间点的距离。
### 代码
在过程中 $ans$ 有可能超过 ```long long``` 范围，所以应该在 $ans>m$ 时立刻退出循环，同样也可以优化时间复杂度，其余代码在前文均有提及。

时间复杂度 $O(Tn \log q)$，其中 $q$ 为二分上界，空间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[114514],b[114514],l,r,mid,ans,u;
bool flag;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		flag=true;
		l=0;
		r=LONG_LONG_MAX;
		while(l<=r){
			mid=(l+r)>>1;
			ans=u=0;
			flag=true;
			for(int i=1;i<=n;i++){
				b[i]=ceil(1.0*mid/a[i]);
			}
			for(int i=1;i<=n;i++){
				if(b[i]>0){
					ans+=i-u-2+(b[i]<<1);
					u=i;
					b[i+1]-=b[i]-1;
				}
				if(ans>m){
					flag=false;
					break;
				}
			}
			flag?l=mid+1:r=mid-1;
		}
		cout<<l-1<<'\n';
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：3)

假设 $d$ 中的每个数都**至少**为 $\textit{low}$，那么 $\textit{low}$ 越大，操作次数就越多，有单调性，可以**二分答案**。

由于必须从最左边开始，所以我们要从左到右计算。

在计算前，还需要说明一个转换关系：我们可以把任何一种或长或短的、来来回回的移动方式，转换成若干组「左右横跳」，也就是在 $1$ 和 $2$ 之间的左右横跳，在 $2$ 和 $3$ 之间的左右横跳，在 $3$ 和 $4$ 之间的左右横跳，……依此类推。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/80vfah6j.png)

从第一个数开始。设 $p=a_1$，至少要增加 $k=\left\lceil\dfrac{\textit{low}}{p}\right\rceil$ 次。

第一次操作需要从 $0$ 走到 $1$，后面的 $k-1$ 次增加可以在 $1$ 和 $2$ 之间左右横跳。

所以一共需要

$$
2(k-1)+1 = 2k-1
$$

次操作。

注意这会导致下一个数已经操作了 $k-1$ 次。

如此循环，直到最后一个数。如果循环中发现操作次数已经超过 $m$，退出循环。

注意，如果最后一个数还需要操作的次数 $\le 0$，那么是不需要继续操作的，退出循环。

下面代码采用开区间二分。

- 开区间左端点初始值：$0$。无需操作，一定可以满足要求。
- 开区间右端点初始值：$\left\lceil\dfrac{m}{2}\right\rceil\cdot \min(a)+1$。假设第一个数是最小值，那么它可以通过左右横跳操作 $\left\lceil\dfrac{m}{2}\right\rceil$ 次。结果 $+1$ 之后一定无法满足要求。

[本题视频讲解](https://www.bilibili.com/video/BV1ekN2ebEHx/?t=50m34s)

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T, n;
    long long m;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vector<int> a(n);
        for (int& x : a) {
            cin >> x;
        }

        auto check = [&](long long low) -> bool {
            long long rem = m, pre = 0;
            for (int i = 0; i < n; i++) {
                long long k = (low - 1) / a[i] + 1 - pre; // 还需要操作的次数
                if (i == n - 1 && k <= 0) { // 最后一个数已经满足要求
                    break;
                }
                k = max(k, 1LL); // 至少要走 1 步
                rem -= k * 2 - 1; // 左右横跳
                if (rem < 0) {
                    return false;
                }
                pre = k - 1; // 右边那个数顺带操作了 k-1 次
            }
            return true;
        };

        long long left = 0;
        long long right = (m + 1) / 2 * ranges::min(a) + 1;
        while (left + 1 < right) {
            long long mid = (left + right) / 2;
            (check(mid) ? left : right) = mid;
        }
        cout << left << '\n';
    }
    return 0;
}
```

**时间复杂度**：$\mathcal{O}(n\log U)$。

---

## 作者：niuzh (赞：1)

### 思路

由于题目中让我们求最小值最大，并具有单调性，所以可用二分答案。

`check` 函数中，先让一个数组 $t$ 满足 $t_i \times d_i \ge mid$。对于 $t_i \ge 1$ 都需要在 $t_i$ 与 $t_{i+1}$ 之间走 $2\times t_i-1$ 次才能满足条件，而 $t_{i+1}$ 项也要去掉 $t_i-1$ 次。如果走的总次数 $cnt$ 大于等于 $m$ 了，就返回 `false`，否则返回 `true`。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll n,m,t[N],d[N];
bool check(ll u)
{
	ll cnt=0;
	for (int i=1; i<=n; i++)
	{
		t[i]=ceil(1.0*u/d[i]);
	}
	for (int i=1; i<=n; i++)
	{
		if (t[i]<=0)
		{
			cnt++;
			continue;
		}
		cnt+=2*t[i]-1;
		t[i+1]-=t[i]-1;
		if (cnt>m)
		{
			return false;
		}
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while (T--)
	{
		ll maxx=0;
		cin>>n>>m;
		for (int i=1; i<=n; i++)
		{
			cin>>d[i];
			maxx=max(maxx,d[i]);
		}
		ll l=0,r=min(m*maxx,LONG_LONG_MAX),ans;
		while (l<=r)
		{
			ll mid=l+(r-l)/2;
			if (check(mid))
			{
				l=mid+1;
				ans=mid;
			}
			else
			{
				r=mid-1;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：immortal_immortals (赞：1)

## 题意

给出植物数 $n$ 和机器人能走的步数 $m$，给出每棵植物的生长速度，然后问这个花园的防御值最大是多少。

这个花园的防御值是机器人走 $m$ 步之后所有植物中防御值最小的那一个数值。

## 思路

最小值最大化问题，且具有单调性，采用二分加验证的方法。

注意：要开 `long long`。
## 代码
```
#include<bits/stdc++.h>
long long t,i,x,r,l,n,m,a[100005];
bool A(long long x)
{
    long long i,k,z,b[100005]{0};
    for(i=0,k=m;i<n-1;i++)
    {
        if(b[i]>=x)
        {
            if(k>0)k--;
            else return 0;
            continue;
        }
        z=x-b[i];
        if(z%a[i])z=z/a[i]+1;
        else z=z/a[i];
        if(k<z*2-1)return 0;
        k-=z*2-1;
        b[i+1]+=(z-1)*a[i+1];
    }
    if(b[i]<x)
    {
        z=x-b[i];
        if(z%a[i])z=z/a[i]+1;
        else z=z/a[i];
        if(k<z*2-1)return 0;
    }
    return 1;
}
int main()
{
    scanf("%lld",&t);
    for(int kl=1;kl<=t;kl++)
    {
        scanf("%lld%lld",&n,&m);
        r=1e17;
        for(i=0;i<n;i++)
        {
            scanf("%lld",&a[i]);
            if(r>a[i]*m)r=a[i]*m;
        }
        l=0;
        while(r-l>1)
        {
            x=(r+l)/2;
            if(A(x))l=x;
            else r=x;
        }
        if(A(r))printf("%lld\n",r);
        else printf("%lld\n",l);
    }
    return 0;
}
```


---

## 作者：ADNAP (赞：0)

首先，是一些废话。对于答案 $x$,至少需要走 $a$ 步,那么对于 $y$，一定能在 $b(b\le a)$ 步内完成答案 $y$ 或更优的解，反之亦然。说明答案具有可二分性。

不妨设答案为 $ans$，则必有 $0\le ans\le \max(a_i) \times m$。其中$\max(a_i) \times m \le 10^{12}+10^5=10^{17}$，答案能在约 $60$ 次内二分出来，只要我们用 $O(n)$ 的复杂度内 check 出来答案是否成立。

我们考虑怎么走一定是最优的。用一个数组来记录要满足答案至少要走到当前位置多少次。每次让当前位置的高度满足答案，必须通过向两边走再走回来来到达当前位置。其中第一个位置向第二位置走显然比走回起点要优。那么第一个位置就要靠往后踱步满足答案。每一次踱步必定经过下列过程，从当前位置直接走到位置 $k$，经过一系列操作回到 $k$，再直接回到原位置，我们考虑从当前位置直接走到位置 $k$ 再直接走回来，并如此重复若干次，当然最后也要走出去的方案能否优化或等效替换。显然，这样一头一尾分别走了 $q+1$ 次，中间的位置走了 $2q+1$ 次，那么我们可以换成在前两个点来回踱步 $q+1$ 次，第二和第三个点踱步 $q$ 次，第三和第四个点踱步 $q+1$ 次来等效替换。

上述说明，每次只考虑在当前点和下一个点之间踱步的方案一定是最优的！

所以我们 check 的时候只用考虑通过下一个点踱步到当前点满足条件时即可，并且这样必定最后回到当前点。这样再考虑下一个点时该点相当于起点，跟位置 $0$ 和第一个位置的关系进行了统一。注意每一次踱步可能把下一个点也踱完了，可以进行标记，下一次直接向前走即可。

为了方便理解，最后一个点要用前一个点踱步，可以分开写。
### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+1e4,M=1e3+1e2;
ll t;
ll n,m;
ll a[N];
ll b[N];
ll mx;
bool check(ll cnt)
{
    ll res=0;
    for(ll i=1;i<=n;i++)b[i]=cnt/a[i]+(cnt%a[i]!=0);
    for(ll i=1;i<=n-1;i++)
    {
        if(b[i]<=0)
        {
            res++;//直接走到下一个点
            continue;
        }
        res+=2*b[i]-1,b[i+1]-=(b[i]-1);
        //踱回当前位置
    }
    if(b[n]>0)res+=2*b[n]-1;
    if(res>m)return false;
    return true;
}
signed main()
{
    cin>>t;
    while(t--)
    {
        mx=0;
        cin>>n>>m;
        for(ll i=1;i<=n;i++)
        {
            cin>>a[i];
            mx=max(a[i],mx);
        }
        ll l=0,r=mx*m;
        while(l<r)
        {
            ll mid=(r+l+1)>>1;
            if(check(mid))l=mid;
            else r=mid-1;
        }
        cout<<l<<"\n";
    }
}
```

---

## 作者：Karl_Aldrich (赞：0)

[题目传送](https://www.luogu.com.cn/problem/P9889)
## 分析
~~二分答案~~
### 裸题
给出一个长度为 $n$ 的字符串和 $m$ 次操作次数，要求在 $m$ 次操作后，序列中的最小值 $\min\{d_i|1\le i\le n\}$ 最大。

优先考虑二分答案。

题干要求最小值 $d_i$ 最大，设这个最大值为 $x$，则该序列中其他元素值一定大于等于 $x$，该序列具有**单调性**，具备二分答案所必须的条件。
### 代码实现分析
首先考虑 check 函数的实现。

对于已经满足要求的 $d_i$ 直接跳过。

对于仍未满足要求的 $d_i$ ~~手动分析得出~~ 最优做法为左右左右走，每一个 $d_i$ 满足要求后，判断步数是否大于 $m$ 即可。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int T;
int n,m;
int d[100010];
int a[100010];
int l,r;
int ans=-1;
bool check(int u){
	int cnt=0;
	for(int i=1;i<=n;++i)d[i]=ceil(1.0*u/a[i]);
	for(int i=1;i<=n;++i){
		if(d[i]<=0){
			cnt++;
			continue;
		}
		cnt+=2*d[i]-1;
		d[i+1]-=d[i]-1;
		if(cnt>m)return false;
	}
	return true;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld %lld",&n,&m);
		for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
		l=0,r=LONG_LONG_MAX,ans=-1;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：tomAmy (赞：0)

## 题目大意

---

[题目传送门](https://www.luogu.com.cn/problem/P9889)

有 $n$ 个高度为 $0$ 的植物，~~莫非是被车子压扁了不成~~？种在 $1\sim n$ 列上。你在 $0$ 列（~~疯狂戴夫家里~~），你可以左右移动给植物浇水，每次浇水会让 $i$ 列的植物长高 $a_i$。限制你的步数为 $m$，使得最矮植物的高度最大。

## 实现思路

---

显然，若能满足最矮植物的高度不低于 $x$，则一定能满足最矮植物的高度低于 $x$。答案复合单调性，考虑二分答案。

我们接下来考虑 check 函数的写法。如果要满足最矮植物的高度不低于 $x$，则 $i$ 列就要浇 $\lceil \dfrac{x}{a_i}\rceil$ 次水。我们不妨模拟一下。

记 $i$ 列浇水次数为 $d_i$，植物高度为 $h_i$。

假设 $x=8,a=\{3,2,6\}$，则三列植物分别需要浇 $3,4,1$ 次水。

第一步，从 $0$ 列移动到 $1$ 列，此时 $d=\{1,0,0\},h=\{3,0,0\}$。

第二步，$0$ 列不需要浇，只能浇 $2$ 列，此时 $d=\{1,1,0\},h=\{3,2,0\}$。

第三步，因为 $1$ 列只浇了 $1$ 次，从 $2$ 列返回 $1$ 列，此时 $d=\{2,1,0\},h=\{6,2,0\}$。

第四步，只能浇 $2$ 列，此时 $d=\{2,2,0\},h=\{6,4,0\}$。

第五步，因为 $1$ 列只浇了 $2$ 次，从 $2$ 列返回 $1$ 列，此时 $d=\{3,2,0\},h=\{9,4,0\}$。

第六步，因为 $1$ 列已经浇了 $3$ 次，从 $1$ 列走到 $2$ 列，此时 $d=\{3,3,0\},h=\{9,6,0\}$。

第七步，$1$ 列已经浇过了，只能浇 $3$ 列，此时 $d=\{3,3,1\},h=\{9,6,8\}$。

第八步，因为 $2$ 列只浇了 $3$ 次，从 $3$ 列返回 $2$ 列，此时 $d=\{3,4,1\},h=\{9,8,8\}$。

此时，因为 $3$ 列已经浇过 $1$ 次了，不需要再走一步。

不难看出，对于第 $i$ 列的植物，最优做法是右右左右左......需要 $2d_i-1$ 步，还会顺便浇 $d_i-1$ 次 $i+1$ 列。如果 $d_i\le0$（也就是顺便浇完了），只需要 $1$ 步右。若 $d_n\le0$，不用再走 $1$ 步了，需要跳过。

时间复杂度 $O((\sum n)\log(\sum n))$。

完结撒花！

## 蒟蒻的代码

---

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long // 不开long long见祖宗
using namespace std;

const int N = 1e5 + 5;
int a[N], d[N];
int n, m;

bool chk(int x)
{   
    int sum = 0; // 记录总步数
    // 预处理浇水次数d[i]
	for (int i = 1; i <= n; i++)
		d[i] = ceil(1.0 * x / a[i]);
	for (int i = 1; i <= n; i++)
	{
	    // 分情况讨论
		if (d[i] <= 0) 
		{
		    sum++;
		    continue; // 跳过
		}
		sum += 2 * d[i] - 1;
		d[i + 1] -= d[i] - 1;
		if (sum > m) return false; // 一定要提前判断，否则会爆long long
	}
	return true;
}

signed main()
{
	int T;
	scanf("%d", &T);
	while (T--) // 多组数据
	{
	    
		scanf("%lld%lld", &n, &m); // scanf和printf别忘%lld
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		// 二分答案
		int L = 0, R = 1e18, ans = -1; // 注意答案可能是0
		while (L <= R)
		{
			int mid = (L + R) / 2;
			if (chk(mid))
			{
				L = mid + 1;
				ans = mid;
			}
			else R = mid - 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

蒟蒻的第一篇题解，不喜勿喷。

---

## 作者：zheng_zx (赞：0)

## P9889 [ICPC2018 Qingdao R] Plants vs. Zombies

[题目传送门](https://www.luogu.com.cn/problem/P9889)

### 分析

---

二分答案，然后从左往右走，如果遇到一个点处的值没有满足条件，则在它和它后面的数之间来回走动，判断所需步数是否小于等于 $m$ 即可。

注：

- 即使当前的数已经满足条件了，也要往后走一步（最后一格除外）。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, T, a[100010], b[100010];
bool ok(long long x){
    long long num = m;
    for(int i = 0; i < n; ++i)a[i]=0;
    for(int i = 0; i < n; ++i){
        if(a[i] < x) {
            long long t = (x - a[i] - 1) / b[i] + 1;
            a[i] += b[i] * t, a[i + 1] += b[i + 1] * (t - 1);
            num -= 2 * t - 1;
        }
        else{
            if(i == n - 1)
                return 1;
            num--;
        }
        if(num < 0)
            return 0;
    }
    return num >= 0;
}
long long vs(long long l, long long r) {
    while(l < r){
        long long mid = (l + r) >> 1;
        ok(mid + 1) ? l = mid + 1 : r = mid;
    }
    return l;
}
int main() {
    cin >> T;
    while(T--){
        cin >> n >> m;
        for(int i = 0; i < n; ++i)
            cin >> b[i];
        cout << vs(0, 0x3f3f3f3f3f3f) << endl;
    }
    return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

发现此题答案具有单调性，因为防御值能达到一个值的话，比这个值低的也肯定能达到，所以此题考虑二分。

二分的显然是防御值。

考虑 check 函数如何写：

首先，预处理出每一株植物的浇水最小次数。

然后遍历所有植物，对于每一株植物，如果已经满足要求则跳过，否则最优的方案是一直左右左右走，直到当前植物满足要求，再把步数累加到总数。

最后判断步数总数是否小于等于 $m$。

但是这样做可能会爆 `long long`！所以我们在每次累加后都判断一下是否大于 $m$，如果大于直接跳出。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int t,n,m,a[1000005],mb[1000005],l,r,ma,an;
bool ch(int x){//check
	int no=0,su=0;//no:上一个没有跳过的，su:总步数
	afor(k,1,n,STB)mb[k]=ceil(x*1.0/a[k]);//预处理最少次数
	afor(k,1,n,STB){
		if(mb[k]<=0)continue;//满足要求
		su+=(k-no+2*(mb[k]-1)),no=k,mb[k+1]-=(mb[k]-1);
		if(su>m)return false;//判断
	}return true;
}signed main(){
	ios::sync_with_stdio(0)/*读入优化*/,cin>>t;
	afor(i,1,t,STB){
		cin>>n>>m,l=1,ma=-1,an=0,r=0x3f3f3f3f3f3f3f3f;//初始化
		afor(j,1,n,STB)cin>>a[j],ma=max(ma,a[j]);
		while(l<=r){//二分
			int mi=l+r>>1;
			if(ch(mi))l=mi+1,an=mi;
			else r=mi-1;
		}cout<<an<<endl;
	}return 0;
}
```

---

