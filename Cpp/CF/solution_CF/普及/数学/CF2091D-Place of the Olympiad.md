# Place of the Olympiad

## 题目描述

首届 IT Campus "NEIMARK" 奥林匹克的决赛场地被布置为一个矩形区域。你可以认为该场地被划分为 $n$ 行，每行包含 $m$ 个参赛者座位的点位。共有 $k$ 名参赛者注册了决赛，每位参赛者将坐在单独的座位上。现在，组委会需要为这些座位选择具体位置。

每个座位占据某一行中的 $m$ 个点位之一。此外，若同一行中多个连续的座位被占据，我们称这样的座位组为一个长凳，组内座位的数量称为长凳的长度。例如，在 $3 \times 4$ 的场地（$n = 3$, $m = 4$）中安排 $7$ 名参赛者的座位可能如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091D/f5385f1942a12d0af05982f4772fe392160619db.png)  
上图中，第一行有一个长度为 $3$ 的长凳，第二行有一个长度为 $2$ 的长凳，第三行有两个长度为 $1$ 的长凳。

组委会希望选择座位位置使得最长长凳的长度尽可能小。例如，同样的 $7$ 个座位可以被更优地安排，使得所有长凳的长度都不超过 $2$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091D/cb2856101ccbe650ed0a0bdeca813ffe1ec02c80.png)  
给定整数 $n$、$m$ 和 $k$，请确定最长长凳的最小可能长度。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 4 7
5 5 5
1 13 2
2 4 7
1 5 4```

### 输出

```
2
1
1
4
2```

# 题解

## 作者：Eysiking (赞：6)

# # CF2091E Interesting Ratio 题解

实际上是个简单的数学题，用到了鸽笼原理。大意是说 $n$ 个物品放入 $k$ 个盒子，则至少有一个盒子放入的物品数至少为 $\lceil \frac{n}{k}\rceil$ 个。

回到这题，显然一行放得越多，可能拼凑出的长度越大，那么数量最多的一行至少有 $\lceil \frac{n}{k}\rceil$ 个桌子，我们肯定不希望有两个空位连在一起造成浪费，那么该行会有 $m-\lceil \frac{n}{k}\rceil$ 个空位，于是该行的 $\lceil \frac{n}{k}\rceil$ 个作为物品放入 $m-\lceil \frac{n}{k}\rceil+1$ 个位置中，再用一次鸽笼原理，连缀起来的最长桌子是 $\lceil\frac{\lceil \frac{n}{k}\rceil}{m-\lceil \frac{n}{k}\rceil+1}\rceil$。
```cpp
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    cout << m / (m - (k + n - 1) / n + 1) << "\n";
}
```

---

## 作者：ZMQ_Ink6556 (赞：4)

## 题解：CF2091D Place of the Olympiad

### 解题思路

考虑**贪心**选择。不浪费长凳长度。

此时长凳的摆放方式如下：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/wm0zdj6y.png)

也就是说若选择长凳长度为 $q$，则每行必须空出 $\lfloor\frac{m}{q}\rfloor$ 个位置。也就是说，每行最多选择 $m - \lfloor\frac{m}{q}\rfloor$ 个位置，总共最多选 $n * (m - \lfloor\frac{m}{q}\rfloor)$ 个位置。

**二分** $q$ 即可。若 $q \ge k$，则代表能够坐下所有人；若 $q < k$ 则代表不能。

时间复杂度：$O(\log n \log m)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t , n , m , k , l , r , mid , ans;
inline long long calc(long long q)
{
	long long p = m / q;
	return n * (m - p);
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> m >> k;
		l = 1;
		r = 1000000009;
		while(l <= r)
		{
			mid = (l + r) / 2;
			if(calc(mid) >= k)
			{
				ans = mid;
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		cout << ans - 1 << '\n';
	}
	return 0;
}
```

---

## 作者：dbywsc (赞：3)

### 题目大意

有 $k$ 个人要分布到 $n \times m$ 个位置上，如果同一行有多个人挨在一起则为他们放一个长凳，要求最长的长凳的长度尽可能的小。

### 思路

最长的长度尽可能的小，具有二段性，考虑二分答案。计算最长的长度，如果按照这个长度摆放长凳可以放下所有的人就移动右端点，反之移动左端点。

### 代码

```cpp
#include <bits/stdc++.h>
#define int signed long long
#define IOS std::ios::sync_with_stdio(0);
#define endl '\n'
#define INF INT_MAX
#define T
//#define FDEBUG
const int N = 2 * 1e5 + 10;
int n, m, k;
int a[N];
using namespace std;
bool judge(int x) {
    int s = m / (x + 1);
    int rem = m % (x + 1);
    int cnt = s * x + min(rem, x);
    return n * cnt >= k;
}
void solve(void) {
    cin >> n >> m >> k;
    int l = 1, r = m;
    int ans = m;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(judge(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
        //cout << l << " " << r << endl;
    }
    cout << ans << endl;
}
signed main(void) {
    IOS
#ifdef FDEBUG
    freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
#endif
#ifdef T
    int t; cin >> t;
    while(t--) solve();
#else
    solve();
#endif
    return 0;
}
```

---

## 作者：_299817_ (赞：2)

## Part 0：前言

考场没怎么想数学的 $O(1)$ 的方法，直接二分糊上去了。

## Part 1：思路

这道题要我们尽量减少最长长凳的长度，抓关键词，让最大值最小，于是考虑二分。

我们二分最长长凳的长度，设我们二分出来的数是 $k$，于是那么我们显然可以得出最优解就是每行先放 $k$ 个凳子，再空一格，接着再放 $k$ 个凳子，一直这样放下去，瞪眼一下就可以知道每行一共 $m$ 个空位能放 $m-\lfloor\frac{m}{k}\rfloor$ 个凳子。

按照如上思路二分即可。

## Part 2：代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool check(int L, int n, int m, int k) {
    ll st = (m / L + 1) * 1LL * L + (m % L + 1);
    ll total = st * n;
    return total >= k;
}

int solve(int n, int m, int k) {
    int low = 1;
    int high = m;
    int ans = m;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid, n, m, k)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << solve(n, m, k) << '\n';
    }
    return 0;
}
```

---

## 作者：bssmessi (赞：1)

我们注意到这个题目的答案是具有单调性的，因此可以考虑二分。

对于每一行，我们可以想到一个容易的策略，就是对于每个需要 check 的值（也就是当前能放的最大连续数量），对于每行，我们放最大的数量，然后放一个空格，再放最大的数量，最后剩余的放满，就是每行能完成的最大数量。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,k;
bool check(int x){
	return (m/(x+1)*x+m%(x+1))*n>=k;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;	
		int l=0,r=1e9;
		while(l<r){
			int mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		} 
		cout<<l<<"\n";
	}
	return 0;
}
```

---

## 作者：Andy1101 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF2091D)
# 思路
这题很明显可以用二分答案。

每次检查以 $mid$ 为最长长度的长凳的凳子数量是否不小于 $k$。若成立则保存答案且移动右端点，否则移动左端点。
# AC Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m;
long long k;
bool check(int x)
{
	long long r=n*((m/(x+1)*x)+(m%(x+1)));
	return r>=k;
}
void solve()
{
	cin >>n>>m>>k;
	long long l=1,r=m;
	long long ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout <<ans<<'\n';
}
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 开始解题！

很一眼的二分。

设答案为 $x$，由于需要一个间隔，所以实际**每行**只能放下 $\lfloor \dfrac{m}{x + 1} \rfloor$ 个完整的长凳，算上那些不完整的部分，则每一行可以放下 $x \times \lfloor \dfrac{m}{x + 1} \rfloor + (m \bmod (x + 1))$ 个课桌，由于有 $n$ 行，所以至多可以放下 $n \times (x \times \lfloor \dfrac{m}{x + 1} \rfloor + (m \bmod (x + 1)))$ 个课桌，我们判断这个值是否大于等于 $k$ 即可得知这个答案是否可行。

最后，由于答案具有单调性，所以二分是对的，注意要让 $x$ 最小。

贴一下代码：

```cpp
// Problem: D. Place of the Olympiad
// Contest: Codeforces - Codeforces Round 1013 (Div. 3)
// URL: https://codeforces.com/contest/2091/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Auther: Lyw_and_Segment_Tree

#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, k, q, a[200005]; string s;

ll opt, l, r, ans = 0;

bool ck(ll x) {
    ll res = x * (m / (x + 1)) + m % (x + 1);
    
    return n * res >= k;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);
    
    ll i, j, x, y, z, res = 0, now;
    
    ll T = rd();
    
    while (T--) {
        n = rd(), m = rd(), k = rd();
        
        l = 0, r = m, ans = 0;
        
        while (l <= r) {
            ll md = (l + r) >> 1;
            
            if (ck(md)) {
                r = md - 1, ans = md;
            } else {
                l = md + 1;
            }
        }
        
        wt(ans), puts("");
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2091/submission/312801031)

---

## 作者：zhangli828 (赞：0)

## 题目思路
给你 $n,m,k$ 三个整数，你要把 $n\times m$ 的表格中任意的 $k$ 个格子涂成黑色，请问一行中连续的黑色格子的数量为多少。
## 题目思路
我们可以把题目转化一下求最小的 $x$ 使得每行最多只有 $x$ 个连续被涂黑的格子，并且可以涂 $k$ 个格子。我们发现如果 $x$ 越大，则可以涂的格子越多，$x$ 越小，则涂的格子越少，所以满足单调性，可以用二分求解。
## 题目解法
对于每个 $x$，我们可以计算最多可以涂多少个格子，我们发现因为最多只能连续涂 $x$ 个格子，所以最少一定有 $\lfloor\frac{m}{x}\rfloor$ 个没有被涂色的格子，所以每一行最多有 $m-\lfloor\frac{m}{x}\rfloor$ 个被涂色的格子，则最多一共有 $n\times(m-\lfloor\frac{m}{x}\rfloor)$ 个被涂色的格子。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, m, k;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> m >> k;
    int l = 1, r = 1e9;
    for (; l <= r;) {  // 二分
      int mid = l + r >> 1;
      if (n * (m - m / mid) >= k) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << l - 1 << '\n';
  }
  return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

## 思路

求最小的最大值，考虑二分。

设答案为 $x$。每一行最长长凳长度为 $x$，最多可可以放 $\lfloor \frac{m}{x + 1} \rfloor$ 个（两个长凳之间需要一个间隔隔开），剩余可以放 $m \bmod (x+1)$ 个长凳。$n$ 行共 $n \times (\lfloor \frac{m}{x + 1} \rfloor +m \bmod (x+1))$ 个，判断是否大于等于 $k$，若成立则保存答案且移动右端点，否则移动左端点。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k, l, r, ans;

bool checker(int x) {
	return n * (m / (x + 1) * x + m % (x + 1)) >= k;
}

void solve() {
	cin >> n >> m >> k;
	ans = 0;
	l = 1, r = m;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (checker(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

