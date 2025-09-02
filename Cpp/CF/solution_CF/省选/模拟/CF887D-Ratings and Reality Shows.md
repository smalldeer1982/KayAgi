# Ratings and Reality Shows

## 题目描述

在顶级模特的生活中主要有两种活动：时装表演和照片拍摄。参加任何这些活动都会影响适当的顶级模特的评级。每次拍照后，模特的评分会增加 $a$，每次时装秀后会减少 $b$。此外，有时顶级模特会参加脱口秀。参加脱口秀后，模特变得更受欢迎，她在拍照后的评分增加为 $c$，在时装秀后的评分减少为 $d$。

伊莎贝拉想参加脱口秀，但她想以这样的方式使她的评分不会变成负值。请帮助她找到一个合适的时机来参加脱口秀。

让我们假设模特的职业生涯从 $0$ 时刻开始，在那一刻，伊莎贝拉的评分等于 $start$ 。如果脱口秀在 $t$ 时刻发生，那么将影响模特生活中的所有事件，时间间隔为 $[t \cdots t+len)$（包括 $t$ 和不包括 $t+len$），其中 $len$ 是影响的时间。

伊莎贝拉想参加一个脱口秀节目，但她希望在**脱口秀前或脱口秀影响期间**，她的评分不会变成负值。请帮助她找到一个合适的时机来参加谈话节目。

## 样例 #1

### 输入

```
5 1 1 1 4 0 5
1 1
2 1
3 1
4 0
5 0
```

### 输出

```
6```

## 样例 #2

### 输入

```
1 1 2 1 2 1 2
1 0
```

### 输出

```
-1```

# 题解

## 作者：方123456 (赞：1)

来自官方题解。

可以发现题目中的答案要么是 $0$，要么是 $t_i+1$，证明这个非常简单，考虑 $t_i+2$ 的情况一定是不优于 $t_i+1$ 的，假设 $t_i<t_i+1<t_i+2<t_{i+1}$，那么就是整个区间从 $[t_i+1,t_i+1+len]$ 变成了 $[t_i+2,t_i+2+len]$ 的情况，这种情况下会有可能多进去一个点，因此一定不优。

否则的话 $t_i+1=t_{i+1}$ 一定存在一个 $t_{i+1}+1=t_i+2$。

然后我们就去思考如何计算答案，可以知道的是我们确定的那个区间一定是单调的，可以用双指针来查找。

我们已经把一段前缀和一段区间给划分出来了。

首先需要满足的是，这段前缀的和的最小值一定是非负的，这东西可以直接找。

然后我们去思考，如何查找区间内的最小值。

也许你会说可以直接上线段树来做，但是我们思考一种更加优秀的做法。

我们已经维护了一个 $[l,r]$ 区间的最小值，那么推到 $[l+1,r1]$，首先我们把 $[r,r1]$ 内的前缀最小值先加进去，然后把前缀和和最小值减掉 $a_{l}$。

为啥这东西是对的呢，因为最小值他在个区间，把 $l$ 删掉了之后所有前缀一定都减去这个数，所以最小值一定不变。

代码非常简洁可以自己理解一下。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=3e5+5;
int t[INF],q[INF],n,a,b,c,d,st,len;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>a>>b>>c>>d>>st>>len;
	for (int i=1;i<=n;i++) 
		cin>>t[i]>>q[i]; 
	t[0]=-1;
	int r=0,M=1e18,S=st,F=0;
	for (int i=1;i<=n;i++) {
		while (t[r+1]-t[i]<len && r+1<=n) 
			r++,F+=q[r]==1?c:-d,M=min(M,F);
		if (S+M>=0) {cout<<t[i-1]+1<<"\n";return 0;}
		S+=q[i]==1?a:-b;
		F-=q[i]==1?c:-d;
		M-=q[i]==1?c:-d;
//		cout<<S<<" yiw\n";
		if (S<0) {cout<<"-1\n";return 0;}
	}
	cout<<t[n]+1<<"\n";
	return 0; 
}
```


---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF887D)

在顶级模特的生活中主要有两种活动：时装表演和照片拍摄。参加任何这些活动都会影响适当的顶级模特的评级。每次拍照后，模特的评分会增加 $a$，每次时装秀后会减少 $b$。此外，有时顶级模特会参加脱口秀。参加脱口秀后，模特变得更受欢迎，她在拍照后的评分增加为 $c$，在时装秀后的评分减少为 $d$。

伊莎贝拉想参加脱口秀，但她想以这样的方式使她的评分不会变成负值。请帮助她找到一个合适的时机来参加脱口秀。

让我们假设模特的职业生涯从 $0$ 时刻开始，在那一刻，伊莎贝拉的评分等于 $start$ 。如果脱口秀在 $t$ 时刻发生，那么将影响模特生活中的所有事件，时间间隔为 $[t \cdots t+len)$（包括 $t$ 和不包括 $t+len$），其中 $len$ 是影响的时间。

伊莎贝拉想参加一个脱口秀节目，但她希望在**脱口秀前或脱口秀影响期间**，她的评分不会变成负值。请帮助她找到一个合适的时机来参加谈话节目。

$1\le n\le 3\times 10^5$，$1\le a,b,c,d,len\le 10^9$，$0\le start\le 10^9$。

### 题目类型

前缀和，线段树。

### 解题思路

首先把不进行脱口秀的评分和进行脱口秀的评分分成两个数组，分别为 $a,b$。

假设进行脱口秀的时间为 $t$，对应在 $a$ 数组的区间为 $[1,x]$，在 $b$ 数组的区间为 $[x+1,k]$，将这两个区间的数组提取出来合并成一个数组，要保证这个数组的任意前缀和加上 $start$ 不为负数。

$a$ 数组取完前 $x$ 个，在 $x$ 到 $x+1$ 这个过程有一个时间段，$t$ 可以自由选择，但是为了保证 $b$ 数组的影响尽可能小，即尽可能减小 $k$，要使得 $t$ 尽可能小，那么就是取到完成第 $x$ 个节目的下一秒。

那么这道题就解决了。遍历 $a$ 数组，遍历到 $x$ 时，表示完成了 $x$ 个节目（要合法），然后二分查找 $k$，最后线段树查询 $b$ 数组的区间 $[x+1,k]$ 是否合法，即 $b$ 数组做个前缀和，线段树维护区间最小值即可。

注意 $0$ 时刻就进行脱口秀。

时间复杂度为 $O(n\log{n})$。

### code


```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 2000100
using namespace std;

ll n, m, k, x, y, tem, sum, a, b, c, d, num[N], arr[N], cnt[N];
ll ans[N], vis[N], tot;
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }
void pushup(ll p)
{
	ans[p] = min(ans[ls(p)], ans[rs(p)]); // 维护区间最小值
}
void build(ll l, ll r, ll p)
{
	if (l == r)
	{
		ans[p] = cnt[l];
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(p));
	build(mid + 1, r, rs(p));
	pushup(p);
}
void query(ll nl, ll nr, ll l, ll r, ll p, ll k)
{

	if (nl <= l && r <= nr)
	{
		if (ans[p] < k)
		{
			x = 0;
		}
		return;
	}
	ll mid = (l + r) >> 1;
	if (nl <= mid)
		query(nl, nr, l, mid, ls(p), k);
	if (nr > mid)
		query(nl, nr, mid + 1, r, rs(p), k);
	return;
}
void solve()
{
	cin >> n >> a >> b >> c >> d >> sum >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i] >> x;
		if (x == 1)
		{
			num[i] = a;
			cnt[i] = c;
		}
		else
		{
			num[i] = -b;
			cnt[i] = -d;
		}
		cnt[i] += cnt[i - 1];
	}
	x = 1;
	y = upper_bound(arr, arr + 2 + n, k - 1) - arr; // 二分查找
	for (int i = 1; i < y; i++)						// 0时刻进行脱口秀
	{
		if (sum + cnt[i] < 0)
			x = 0;
	}
	if (x)
	{
		cout << "0\n";
		return;
	}
	build(1, n, 1);
	x = 1;
	arr[n + 1] = 1e16;
	tem = -1;
	for (int i = 1; i <= n; i++)
	{
		sum += num[i];
		if (sum < 0 || tem >= 0)
			break;
		x = 1;
		y = upper_bound(arr, arr + 2 + n, arr[i] + k) - arr;
		/// cout<<y<<" n\n";
		query(i + 1, y - 1, 1, n, 1, cnt[i] - sum);
		if (x)
		{
			tem = arr[i] + 1;
			break;
		}
		else if (i == n)
			tem = arr[i] + 1;
	}
	cout << tem << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

