# [ABC366E] Manhattan Multifocal Ellipse

## 题目描述

二维平面上有 $N$ 个点 $(x_1,y_1),(x_2,y_2),\ldots,(x_n,y_n)$，给你一个正整数 $D$，求有多少组 $(x,y)$ 满足 

$$\sum\limits^N_{i=1}(|x-x_i|+|y-y_i|) \leq D$$

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$

- $0 \leq D \leq 10^6$

- $-10^6 \leq x_i,y_i \leq 10^6$

- 保证对于所有的 $i \ne j$，$(x_i,y_i) \ne (x_j,y_j)$。

- 所有输入均为整数。

## 样例 #1

### 输入

```
2 3
0 0
1 0```

### 输出

```
8```

## 样例 #2

### 输入

```
2 0
0 0
2 0```

### 输出

```
0```

## 样例 #3

### 输入

```
6 100
9 -6
10 -1
2 10
-1 7
-7 5
-1 -4```

### 输出

```
419```

# 题解

## 作者：_ZML_ (赞：15)

# 写在前面的话
本篇题解篇幅较长，但是如果你想彻底把这道题弄懂，请静下心来，把这篇题解看完，相信对你的提升会很大。如果有看不懂的地方欢迎给我发私信，我会详细地解答。
# 题目简述
平面上有 $n$ 个点 $(x_i,y_i)$，求有多少个点 $(x,y)$ 满足这 $n$ 个点到它的哈夫曼距离之和不超过 $D$。

后面半句话也就是，$\sum_{i=1}^n(|x-x_{i}|,|y-y_{i}|) \le D$。
# 思路

对上式进行变形：
$$
\sum_{i=1}^n|y-y_i|\le D-\sum_{i=1}^n|x-x_i|
$$
我们可以枚举所有的 $x$，带入上式右边，然后计算有多少个 $y$ 满足。
# 实现
枚举 $x$ 的坐标的话，我们需要实现 $\Theta(1)$ 查询 $\sum_{i=1}^n|x-x_i|$。

思考 $x$ 坐标每往右移 $1$，它对答案的影响会发生什么，什么会导致它发生变化。

这里先说结论，从点 $p$，到 $p+1$ 它对答案的变化是点 $p+1$ 右边有多少个 $x_i$，减去左边有多少个 $x_i$。

更为形式化的，设之前的答案为 $old$，现在的答案 $now$，点 $p+1$ 的左边有 $l$ 个满足条件的 $x_i$，右边有 $r$ 个满足条件的，那么 $now=old-l+r$。

为什么这么做可以？

看图，其中黄色点是 $x_i$，蓝色点是 $p$，红色点是 $p+1$，蓝色线是 $p$ 所有 $x_i$ 到它的距离之和，也就是我们要算的东西，红色点同理。

从图中我们可以直观的看到从点 $p$ 到 $p+1$，红点左侧的每条线段长度都比之前长了 $1$，右边的线段长度都减少了 $1$。左边有两个点就减少 $2$，右边 $3$ 个点就增加 $3$。

和我们的结论是一样的。

![QwQ图不见了](https://cdn.luogu.com.cn/upload/image_hosting/3vcub7y5.png)

第一个问题已经解决了，我们还需要 $\Theta(1)$ 求出有多少个 $y$ 满足式子。

预处理所有的 $y$ 的值，用算 $x$ 的方法求出 $\sum_{i=1}^n|y-y_i|$ 的值，放进一个桶里，然后进行前缀和，就行了。

这里这道题也就讲完了。

最后总结一下算法流程：
1. 预处理所有 $y$ 的可能值，放进桶里，前缀和。

2. 用类似的办法，枚举 $x$ 的可能值，对每个 $x$ 算出有多少个 $y$ 满足条件。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 6e6 + 10;
int x[maxn], y[maxn];
int cnt[maxn], sum[maxn];
int mpx[maxn], mpy[maxn];
signed main()
{
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        mpx[x[i] + 2000000]++, mpy[y[i] + 2000000]++;
    }
    int now = 0, l = 0, r = n, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        now += abs((-(2e6 + 1)) - y[i]);
    }
    for (int i = -2e6; i <= 2e6; i++)
    {
        now += l, now -= r;
        if (now <= d)
            cnt[now]++;
        l += mpy[i + 2000000], r -= mpy[i + 2000000];
    }
    for (int i = 0; i <= d; i++)
    {
        sum[i] = sum[i - 1] + cnt[i];
    }
    now = 0, l = 0, r = n;
    for (int i = 1; i <= n; i++)
    {
        now += abs(-(2e6 + 1) - x[i]);
    }
    for (int i = -2e6; i <= 2e6; i++)
    {
        now += l, now -= r;
        if (now <= d)
            ans += sum[d - now];
        l += mpx[i + 2000000], r -= mpx[i + 2000000];
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Him_shu (赞：8)

## 题目+样例

给你 $n$ 个点和一个整数 $D$，求二元组 $(x,y)$ 满足 $\displaystyle \sum_{i=1}^N (|x-x_i|+|y-y_i|) \leq D$ 的个数。



---

#### 输入样本

```
2 3
0 0
1 0
``` 

#### 输出样例

```
8
```

下图展示了样本 $1$ 的输入和答案。蓝色点代表输入。蓝色和红色点共八个，满足语句中的条件。

![](https://img.atcoder.jp/abc366/2b6d85ce3511e14c65dc80e052d62bca.png)

## 分析

考虑到 $1 \leq N \leq 2 \times 10^5$ 所以连二元组 $(x,y)$ 都无法枚举，那么只能要考虑分解再运算。

那么 $\displaystyle \sum_{i=1}^N (|x-x_i|+|y-y_i|) \leq D$ 其实可以分解成 $\displaystyle \sum_{i=1}^N |x-x_i|+\displaystyle \sum_{i=1}^N |y-y_i| \leq D$，这样的话问题就被简单化了。

只需要先预处理 $\displaystyle \sum_{i=1}^N |x-x_i|$ 和 $\displaystyle \sum_{i=1}^N |y-y_i|$ 在排序用二分即可。



---

问：那么 $\displaystyle \sum_{i=1}^N |t-x_i|$ 如何预处理？

回答：对 $x$ 数组排序，因为此时 $x$ 以单调，在枚举未知数 $x$ 即可，$y$ 也一样。
![](https://cdn.luogu.com.cn/upload/image_hosting/hkifbq1b.png)

```cpp
sort(x+1,x+n+1);
sort(y+1,y+n+1);
for(int i=1;i<=n;i++){
  xp[i]=xp[i-1]+x[i];
  yp[i]=yp[i-1]+y[i];
}
for(int i=n;i>=1;i--){
  xs[i]=xs[i+1]+x[i];
  ys[i]=ys[i+1]+y[i];
}
for(int i=mi;i<=mx;i++){
  int k=upper_bound(x+1,x+n+1,i)-x;
  ax.push_back(i*(k-1)-xp[k-1]+xs[k]-i*(n-k+1));
  k=upper_bound(y+1,y+n+1,i)-y;
  ay.push_back(i*(k-1)-yp[k-1]+ys[k]-i*(n-k+1));
}
```
---

问：如何排序二分？

```cpp
sort(ax.begin(),ax.end());
sort(ay.begin(),ay.end());//排序
ay.push_back(inf);
for(auto i:ax){
  if(d-i<0){
    continue;
  }
  ans+=(upper_bound(ay.begin(),ay.end(),d-i)-ay.begin());//二分查找
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/ppo30ube.png)
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 200005
#define M 1e6
#define inf 1e14
#define mod 998244353
int n,d;
int x[N],xs[N],xp[N],y[N],ys[N],yp[N],ans,mx,mi;
vector<int>ax,ay;
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	mi=-M*2;
	mx=M*2;
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for(int i=1;i<=n;i++){
		xp[i]=xp[i-1]+x[i];
		yp[i]=yp[i-1]+y[i];
	}
	for(int i=n;i>=1;i--){
		xs[i]=xs[i+1]+x[i];
		ys[i]=ys[i+1]+y[i];
	}
	for(int i=mi;i<=mx;i++){
		int k=upper_bound(x+1,x+n+1,i)-x;
		ax.push_back(i*(k-1)-xp[k-1]+xs[k]-i*(n-k+1));
		k=upper_bound(y+1,y+n+1,i)-y;
		ay.push_back(i*(k-1)-yp[k-1]+ys[k]-i*(n-k+1));
	}
	sort(ax.begin(),ax.end());
	sort(ay.begin(),ay.end());
	ay.push_back(inf);
	for(auto i:ax){
		if(d-i<0){
			continue;
		}
		ans+=(upper_bound(ay.begin(),ay.end(),d-i)-ay.begin());
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：PineappleSummer (赞：6)

提供一个非常自然的思路。

题目中有 $\displaystyle \sum_{i=1}^n (|x-x_i|+|y-y_i|) \leq D$ 这个限制，发现可以转化为 $\displaystyle \sum_{i=1}^n |x-x_i|+\displaystyle \sum_{i=1}^n|y-y_i| \leq D$，所以 $x_i,y_i$ 是相互独立的，可以分别计算。

首先我们可以计算出 $X_i$ 和 $Y_i$，其中 $X_i$ 表示 $\displaystyle \sum_{j=1}^n|i-x_j|$，$Y_i$ 是同理的。

考虑从 $-2\times 10^6\sim 2\times 10^6$ 枚举 $i$，每个 $X_i$ 可以在 $\mathcal O(\log n)$ 的时间内求出。具体地，我们可以将 $x$ 数组排序，预处理 $x$ 数组的前缀和 $fx$ 和后缀和 $bx$。对于枚举到的 $i$，`lower_bound` 查找在 $x$ 数组中的位置，记为 $l$，则 $X_i$ 为 $i\times (l-1)-fx_{l-1}+bx_l-i\times(n-l+1)$。其实就是计算数轴上各个点到 $i$ 的距离之和。

对于计算 $Y$ 数组是同理的。

记 $cnt_i$ 为 $\displaystyle \sum_{j=-2\times 10^6}^{2\times 10^6}[Y_j\le i]$，这个可以 $\mathcal O(V)$ 求出。

枚举 $i$，对于 $X_i\le d$ 的情况，计算 $Y_i\le d-X_i$ 的数量，这个数量即为 $cnt_{d-X_i}$。

时间复杂度 $\mathcal O(V\log n)$，其中 $V$ 为 $4\times 10^6$。

```cpp
unordered_map <int, int> X, Y;
const int Mi = -2e6, Ma = 2e6;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> d;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	sort (x + 1, x + n + 1);
	for (int i = 1; i <= n; i++) fx[i] = fx[i - 1] + x[i];
	for (int i = n; i >= 1; i--) bx[i] = bx[i + 1] + x[i];
	for (int i = Mi; i <= Ma; i++) {
		if (i < x[1]) X[i] = fx[n] - i * n;
		else if (i > x[n]) X[i] = i * n - fx[n];
		else {
			int l = lower_bound (x + 1, x + n + 1, i) - x;
			X[i] = bx[l] - i * (n - l + 1) + i * (l - 1) - fx[l - 1];
		}
	}
	
	sort (y + 1, y + n + 1);
	for (int i = 1; i <= n; i++) fy[i] = fy[i - 1] + y[i];
	for (int i = n; i >= 1; i--) by[i] = by[i + 1] + y[i];
	for (int i = Mi; i <= Ma; i++) {
		if (i < y[1]) Y[i] = fy[n] - i * n;
		else if (i > y[n]) Y[i] = i * n - fy[n];
		else {
			int l = lower_bound (y + 1, y + n + 1, i) - y;
			Y[i] = by[l] - i * (n - l + 1) + i * (l - 1) - fy[l - 1];
		}
	}
	
	for (int i = Mi; i <= Ma; i++) {
		if (Y[i] > d) continue;
		cnt[Y[i]] ++;
	}
	for (int i = 1; i <= d; i++) cnt[i] += cnt[i - 1];
	
	for (int i = Mi; i <= Ma; i++) {
		if (X[i] > d) continue;
		int t = d - X[i];
		ans += cnt[t];
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：_Day_Tao_ (赞：4)

这个题的正解应该是不带 $\log$ 的，但是似乎因为 AT 的机子太牛了导致放很多带 $\log$ 的过去了（？）

考虑把原来的柿子拆成 $\sum\limits_{i=1}^N |x-x_i|$ 和 $\sum\limits_{i=1}^N |y-y_i|$。现在我们设 $fx_j$ 为 $\sum\limits_{i=1}^N |x-x_i|=j$ 的方案数，设 $fy_j$ 为 $\sum\limits_{i=1}^N |y-y_i|=j$ 的方案数，那么最终要求的就是 $fx+fy\le D$ 的总方案数，不难想可以把 $fy$ 前缀和一下，然后枚举 $fx$，设前缀和之后的 $fy$ 为 $fy'$，则 $ans=\sum\limits_{i=0}^D fx_i\times fy'_{d-i}$。

接着考虑怎么求 $fx$ 和 $fy$。拿 $fx$ 举例，我们记录每条直线 $x$ 上方点的数量为 $cntx$，考虑从上到下扫，在下移的过程中，位于当前直线上方的点的贡献增加，位于当前直线下方的点的贡献减小，对于每条直线的总贡献若在 $D$ 之内的话就累加到 $fx$ 中。具体的实现可以参考代码。

几个细节：

注意答案要开 `long long`；考虑最极限的情况，点的坐标在 $-1\times 10^6$ 级别的，而 $D$ 又在 $1\times 10^6$ 级别，所以对于输入的点都加上一个 $2\times 10^6 +1$ 的偏移量，然后从 $1$ 开始往后做。

复杂度为 $O(V)$ 级别。

[上述实现的 Code](https://atcoder.jp/contests/abc366/submissions/56746511)

[优化了一些之后的 Code（24ms，你谷和 AT 上都是最优解 rk1）](https://atcoder.jp/contests/abc366/submissions/56747170)

---

## 作者：incra (赞：4)

提供一个非常直观，不用脑子，只需要代码能力的做法。

不难发现 $x,y$ 的和其实独立，所以先给 $x,y$ 排序，然后考虑枚举 $x$，然后求出对应的 $y$ 的数量。

根据仓库选址那题，我们可以得到 $\displaystyle\sum_{i=1}^n|y-y_i|$ 其实是以 $y_{\left\lceil \frac{n}{2}\right\rceil}$ 为峰的单峰函数，所以我们可以二分处理。

代码中用双指针优化了当前不大于 $x,y$ 的 $x_i,y_i$ 的最大 $i$。


```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
#define endl '\n'
const int N = 2000010;
int n,d;
LL x[N],y[N];
LL slx[N],srx[N],sly[N],sry[N];
int posx;
int mp[2 * N];
LL get (LL a,LL posx,LL sl[N],LL sr[N]) {
	return posx * a - sl[posx] + sr[posx + 1] - (n - posx) * a;
}
bool check (LL a,LL b) {
	int posy = mp[b + N];
//	cout << a << ' ' << b << ' ' << get (a,posx,slx,srx) + get (b,posy,sly,sry) << endl;
	return get (a,posx,slx,srx) + get (b,posy,sly,sry) <= d;
}
int main () {
	cin >> n >> d;
	for (int i = 1;i <= n;i++) cin >> x[i] >> y[i];
	sort (x + 1,x + n + 1),sort (y + 1,y + n + 1);
	int j = 0;
	for (int i = -2e6;i <= 2e6;i++) {
		while (j + 1 <= n && y[j + 1] <= i) j++;
		mp[i + N] = j;
	}
	for (int i = 1;i <= n;i++) slx[i] = slx[i - 1] + x[i],sly[i] = sly[i - 1] + y[i];
	for (int i = n;i >= 1;i--) srx[i] = srx[i + 1] + x[i],sry[i] = sry[i + 1] + y[i];
	LL ans = 0;
	for (int a = -2e6;a <= 2e6;a++) {
		while (posx + 1 <= n && x[posx + 1] <= a) posx++;
		int l = -2e6,r = y[(n + 1) / 2];
		while (l < r) {
			int mid = l + r >> 1;
			if (check (a,mid)) r = mid;
			else l = mid + 1;
		}
		if (!check (a,l)) continue;
		int pos = l;
		l = y[(n + 1) / 2],r = 2e6;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (check (a,mid)) l = mid;
			else r = mid - 1;
		}
		if (!check (a,l)) continue;
//		cout << a << ' ' << "[" << pos << ',' << l << "]    \n";
		ans += l - pos + 1;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：SpringFullGarden (赞：3)

## 题意

有 $N$ 个点 $(x_1, y_1), (x_2, y_2), \dots, (x_n, y_n)$ 和一个非负整数 $d$ 。

求 $\sum \limits_{i=1}^n (|x-x_i|+|y-y_i|) \leq d$ 的整数对 $(x, y)$ 的个数。

## 思路

可以发现，横坐标和纵坐标是没有关联的，所以可以将 $x_i$ 和 $y_i$ 分别排序。

枚举横坐标 $x$，与每个点的距离为 $\sum \limits_{i=1}^n |x-x_i|$，找到最大的 $t$ 使 $x_t < x$，化简得 $\sum \limits_{i = 1}^t (x - x_i) + \sum \limits_{i = t + 1}^{n} (x_i - x)$，可以用桶和前缀和处理。以算出的距离距离作下标，设把它存在数组 $X$ 里。

同理求出纵坐标上 $y$ 与每个点的距离，设把它存在数组 $Y$ 里。

将 $Y$ 数组前缀和处理，设前缀和数组为 $d$。

答案为 $\sum \limits_{i = 0}^m X_i \cdot d_{m - i}$。
## 代码

```cpp
ll x[200005], y[200005];
ll dx[200005], dy[200005], b[10000007], c[10000007];
ll X[2000006], Y[2000006];

signed main() {
	ll n = rd(), m = rd();
	for(ll i = 1; i <= n; i++) {
		x[i] = rd(), y[i] = rd();
		b[x[i] + 3000000]++, c[y[i] + 3000000]++;
	}
	sort(x + 1, x + n + 1), sort(y + 1, y + n + 1);
	for(ll i = 0; i <= 1e7; i++) b[i] += b[i - 1];
	for(ll i = 1; i <= n; i++) dx[i] = dx[i - 1] + x[i] + 3000000;
	for(ll i = 0; i <= 1e7; i++) c[i] += c[i - 1];
	for(ll i = 1; i <= n; i++) dy[i] = dy[i - 1] + y[i] + 3000000;
	for(ll i = 0; i <= 1e7; i++) {
		ll cnt = b[i], lsum = dx[cnt], rsum = dx[n] - dx[cnt];
		ll res = rsum - (n - cnt) * i +	cnt * i - lsum;
		if(res > m) continue;
		X[res]++;
	}
	for(ll i = 0; i <= 1e7; i++) {
		ll cnt = c[i], lsum = dy[cnt], rsum = dy[n] - dy[cnt];
		ll res = rsum - (n - cnt) * i + cnt * i - lsum;
		if(res > m) continue;
		Y[res]++;
	}
	for(ll i = 0; i <= m; i++) Y[i] += Y[i - 1];
	ll ans = 0;
	for(ll i = 0; i <= m; i++) ans += X[i] * Y[m - i];
	cout << ans;
	return 0;
}
```

---

## 作者：Lotus_Land (赞：3)

### 题意

给你一个二维平面上的 $N$ 点 $(x_1, y_1), (x_2, y_2), \dots, (x_N, y_N)$ 和一个非负整数 $D$。

求使得 $\displaystyle \sum_{i=1}^N (|x-x_i|+|y-y_i|) \leq D$ 的整数对 $(x, y)$ 的个数。

### 分析

观察到 $\sum\limits_{i=1}^{N}(|x-x_i|+|y-y_i|)$ 这个数的计算不需要依赖 $(x_i,y_i)$ 的对应关系，即可以转化成 $\sum\limits_{i=1}^{N}|x-x_i|+\sum\limits_{i=1}^{N}|y-y_i|$。设枚举范围的大小为 $T$。（$T$ 与 $N$ 同阶）

计算每个 $x$ 对应的 $\sum\limits_{i=1}^{N}|x-x_i|$ 可以从 $O(N)$ 优化到 $O(\log N)$。先把所有点的横坐标排序，并求出前缀和 $s$，对于每个 $x$，二分找出它在横坐标中的位置，得到小于 $x$ 的数的个数 $t$，$\sum\limits_{i=1}^{N}|x-x_i|=s_n-s_t-x(n-t)+xt-s_t$。对于纵坐标同理。连同排序，预处理求出枚举范围中的每个 $x$ 和 $y$ 对应的贡献的时间复杂度 $O(N\log N+N+T\log N)=O(N\log N)$。

把上面求出的每个 $x$ 的贡献排序，枚举 $y$，二分求出有多少个 $x$ 满足条件，相加即可。时间复杂度 $O(N\log N)$。

总时间复杂度 $O(N\log N)$。

注意：$x$ 和 $y$ 的枚举范围都是 $-2\times 10^6$ 到 $2\times 10^6$，存贡献的数组要开到 $4\times 10^6$。如果枚举范围只有 $-10^6$ 到 $10^6$ 会被极限数据卡掉。

```cpp
int n,d,a[200005],b[200005];
LL x[4000006],y[4000006];
LL ans,s[200005];
const int N=2000000;
int main(){
	n=read();
	d=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
	}
	for(int i=-N;i<=N;i++){
		int pos=lower_bound(a+1,a+1+n,i)-a;
		x[i+N]=s[n]-s[pos-1]-1ll*(n-pos+1)*i+1ll*(pos-1)*i-s[pos-1];
	}
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+b[i];
	}
	for(int i=-N;i<=N;i++){
		int pos=lower_bound(b+1,b+1+n,i)-b;
		y[i+N]=s[n]-s[pos-1]-1ll*(n-pos+1)*i+1ll*(pos-1)*i-s[pos-1];
	}
	sort(x,x+1+N*2);
	for(int i=-N;i<=N;i++){
		int pos=upper_bound(x,x+1+N*2,d-y[i+N])-x;
		ans+=pos;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ANDER_ (赞：3)

感觉比 F 还难，场上花了二十分钟，赛后花了快一个小时才想好怎么做。部分思路来自 @[2huker](https://www.bilibili.com/video/BV14uY7eiEus/?vd_source=17bf174db393d6095a675397f301b9f4)。

## 题意

给定 $n$ 个点 $(x_i,y_i)$ 和一个常数 $d$，需要求出平面上的任意点 $(x_0,y_0)$ 满足:

$$
  (x_0,y_0 \isin \Z) \wedge (\displaystyle\sum_{i = 1}^{n}(|x_0-x_i| + |y_0-y_i|) \le d)
$$

全部点对的个数（曼哈顿距离）。

曼哈顿距离有一个特点，它的计算方式 $x$ 与 $y$ 坐标互相独立。这给了我们处理题目的一个思路。我们考虑对上面那个级数进行变化：

$$
  \displaystyle\sum_{i = 1}^{n}(|x_0-x_i| + |y_0-y_i|)  = \displaystyle\sum_{i = 1}^{n}(|x_0-x_i|) + \displaystyle\sum_{i = 1}^{n}(|y_0-y_i|)
$$

不妨设函数 $f(j) = \displaystyle\sum_{i = 1}^{n}(|j-x_i|)$，$g(j) = \displaystyle\sum_{i = 1}^{n}(j-y_i)$。记 $f(i)$ 为 $F_i$，$g(x)$ 为 $G_x$。如果我们预处理出 $F$ 和 $G$ 的值，题目就转化为了经典的双指针问题。

现在考虑怎么预处理出 $F$，$G$ 同理。首先将 $x_i$ 排序，然后拆绝对值。观察级数 $\displaystyle\sum_{i = 1}^{n}(|j-x_i|)$，注意到当 $j \ge x_i$ 时，$i$ 一定为某个“前缀”；$j \le x_i$ 时，$i$ 为“后缀”。具体的，设 $\text{MAX}$ 为 $x_i$ 的最大值，$\text{MIN}$ 为 $x_i$ 的最小值。我们可以做出如下转换：

$$\displaystyle\sum_{i = 1}^{n}(|j-x_i|) = \displaystyle\sum_{i = x_j}^{\text{MAX}}(i - x_j) + \displaystyle\sum_{i = \text{MIN}}^{x_j}(x_j - i)$$

这两个级数相似，我们现在来讨论第一个级数的做法。令 $cnt_i$ 表示 $x_j < i$ 的 $j$ 的数量。$sum_i$ 表示 $x_j < i$ 的 $x_j$ 的和。这样 $\displaystyle\sum_{i = x_j}^{\text{MAX}}(i - x_j)$ 就被转换为了 $i \times cnt_i - sum_i$。关于 $cnt_i$ 和 $sum_i$，我们可以用权值树状数组来维护。正确性显然，我们可以将 $x_j$ 作为下标，当扫到 $x_j$ 就加入树状数组，再扫描到 $j$ 时，比 $j$ 小的就一定能加入树状数组。

在计算第二个级数时，树状数组要倒过来使用，因为是后缀和。处理完所有东西后，就可以用双指针 AC 这道题了。时间复杂度比较抽象，大概是 $O(N\lg N)$，$N=2 \times 10^6$。约等于 $41863137$，不太会证。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define endl "\n"
using namespace std;
//#define MSOD
const int N = 4e6 + 5, M = 2e6 + 2 , MOD = 1e9 + 7;

inline int C(int n, int m) {return (n == m || m == 0) ? 1 : C(n - 1, m) + C(n - 1, m - 1); }
inline int lowbit(int x) {return x & (-x); }
inline int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b); }
inline int lcm(int a, int b) {return a * b / gcd(a, b); }
inline int exgcd(int a, int b, int &x, int &y) {if(!b) {x = 1, y = 0; return a; } int d = exgcd(b, a % b, y, x); y -= (a / b) * x; return d; }
inline int inv(int a, int m) {int x, y; exgcd(a, m, x, y); return (x % m + m) % m; }
inline int quick_pow(int a, int b) {int res = 1; while(b) {if(b & 1) {res = res * a % MOD; }a = a * a % MOD, b >>= 1; }return res; }

int n, d, ans, x[N], y[N], tr[2][N], dis_x[N], dis_y[N];
inline void update(int m, int u, int d) {
	for(int i = u ; i < N ; i += lowbit(i)) {
		tr[m][i] += d;
	}
	return;
}
inline int query(int m, int u) {
	int res = 0;
	for(int i = u ; i ; i -= lowbit(i)) {
		res += tr[m][i]; 
	}
	return res;
}
inline void solve() {
	cin>>n>>d;
	for(int i = 1 ; i <= n ; i ++) {
		cin>>x[i]>>y[i];
		x[i] += M, y[i] += M;
	} 
	sort(x + 1, x + n + 1);
	sort(y + 1, y + n + 1);
	for(int i = 1, j = 1 ; i < N ; i ++) {
		while(j <= n && x[j] <= i) {
			update(0, x[j], 1);
			update(1, x[j], x[j]);
			j ++;
		}
		dis_x[i] = query(0, i) * i - query(1, i);
	} 
	memset(tr, 0, sizeof(tr));
	for(int i = 1, j = 1 ; i < N ; i ++) {
		while(j <= n && y[j] <= i) {
			update(0, y[j], 1);
			update(1, y[j], y[j]);
			j ++;
		}
		dis_y[i] = query(0, i) * i - query(1, i);
	}
	memset(tr, 0, sizeof(tr));
	for(int i = N - 1, j = n ; i ; i --) {
		while(j && x[j] >= i) {
			update(0, x[j], 1);
			update(1, x[j], x[j]);
			j --; 
		} 
		dis_x[i] += query(1, N - 1) - query(1, i - 1) - (query(0, N - 1) - query(0, i - 1)) * i; 
	} 
	memset(tr, 0, sizeof(tr));
	for(int i = N - 1, j = n ; i ; i --) {
		while(j && y[j] >= i) {
			update(0, y[j], 1);
			update(1, y[j], y[j]);
			j --; 
		} 
		dis_y[i] += query(1, N - 1) - query(1, i - 1) - (query(0, N - 1) - query(0, i - 1)) * i; 
	}
	sort(dis_x + 1, dis_x + N);
	sort(dis_y + 1, dis_y + N);
	for(int i = 1, j = N - 1 ; i < N ; i ++) {
		while(j && dis_x[i] + dis_y[j] > d) {
			j --;
		}
		if(j && dis_x[i] + dis_y[j] <= d) {
			ans += j;
		}
	}
	cout<<ans;
	return;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
    int T = 1;
#ifdef MSOD
	cin>>T;
#else
#endif
	while(T --) {
    solve();
	}
	return 0;
}
```

---

## 作者：a_sad_soul (赞：3)

### E

观察到 $x,y$ 可以拆开来讨论。

整理一下式子可以得到这个约束：

$$\large D-\sum\limits_{i=1}^{n}{|x-x_i|}\ge \sum\limits_{i=1}^{n}{|y-y_i|}$$

预处理每个 $y$ 的贡献，然后枚举每个 $x$ ，再计算答案即可。过程可以用双指针和树状数组维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,D;
const int MAXN = 1e7+10;
long long x[MAXN],y[MAXN];
long long px[MAXN],py[MAXN];
int tree[MAXN];
int lowbit(int i){
	return i&(-i);
}
void add(int i){
	if(i==0){
	tree[0]++;
	return ;
	}
	for(;i<=D;i+=lowbit(i))tree[i]++;
}
int ask(int i){
	int re=tree[0];
	for(;i;i-=lowbit(i))re+=tree[i];
	return re;
}
bool cmp(long long a,long long b){
	return a<b;
}
int main(){
	scanf("%lld%lld",&n,&D);
	for(int i=1;i<=n;++i)scanf("%lld%lld",&x[i],&y[i]);

	sort(x+1,x+1+n,cmp);
	sort(y+1,y+1+n,cmp);
	for(int i=1;i<=n+1;++i){
		px[i]=px[i-1]+x[i];
		py[i]=py[i-1]+y[i];
	}
	y[n+1]=1e8;
	x[n+1]=1e8;
	long long pos=1;
	for(long long i=y[1]-D;i<=y[n]+D;++i){
		long long v=0;
		while(y[pos]<i)++pos;
		v+=i*(pos-1)-py[pos-1];
		v+=py[n]-py[pos-1]-i*(n-pos+1);
		if(v<=D)add(v);
	}
	pos=1;
	long long ans=0;
	for(long long i=x[1]-D;i<=x[n]+D;++i){
		long long v=0;
		while(x[pos]<i)++pos;
		v+=i*(pos-1)-px[pos-1];
		v+=px[n]-px[pos-1]-i*(n-pos+1);
		if(v>D)continue;
		v=D-v;
		ans+=ask(v);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：zengziqvan (赞：2)

注意到 $x$ 轴上的距离与 $y$ 轴上的距离可以分开计算，且距离最大是 $10^6$。所以考虑分别记录 $x$ 轴与 $y$ 轴上距离为 $k$ 的点分别有多少个，再用前缀和累加。

如何算距离呢？这里以 $x$ 轴为例。把所有点按照 $x$ 坐标从小到大排序，扫描所有可能的 $x$ 坐标。显然，当前 $x$ 坐标与所有点在 $x$ 轴上的距离之和为 $cnt1\times x-sum1+sum2-cnt2\times x$。

其中 $cnt1$ 表示 $x$ 坐标比当前枚举的 $x$ 坐标小的点的个数，$cnt2$ 表示 $x$ 坐标大于等于的当前枚举的 $x$ 的点的个数，$sum1$ 表示 $x$ 坐标比当前小的点的 $x$ 坐标之和，$sum2$ 表示 $x$ 坐标大于等于当前枚举的 $x$ 坐标的 $x$ 坐标之和。

对 $y$ 坐标再做一次，是线性的。

时间复杂度 $\operatorname{O}(n\log n)$。

若使用桶排序可以做到 $\operatorname{O}(n)$。

代码

```c++
const int N=2e5+10;
int n,d;
struct Node {
	int x,y;
}a[N],b[N];
int cmp(Node x,Node y) {
	return x.y<y.y;
}
int cmp2(Node x,Node y) {
	return x.x<y.x;
}
int cnt[3000000],sum[200010],cx[1000010],cy[1000010],cnty[3000000];
LL ans=0;
main() {
	cin>>n>>d;int mn=1e9,mx=-1e9,Min=1e9,Max=-1e9;
	FOR(i,1,n) {
		a[i].x=read();
		cnt[a[i].x+1000000]++;
		mn=min(a[i].x,mn);
		a[i].y=read();
		cnty[a[i].y+1000000]++;
		mx=max(a[i].x,mx);
		Max=max(a[i].y,Max);
		Min=min(a[i].y,Min);
		b[i]=a[i];
	}
	sort(a+1,a+n+1,cmp2);
	sort(b+1,b+n+1,cmp);
	int l=mn-d,r=mx+d;
	LL Mn=0,Mx=0,cmn=0,cmx=n;
	FOR(i,1,n) Mx+=a[i].x;
	FOR(x,l,r) {
		if(x+1000000>=0) Mx-=x*cnt[x+1000000],Mn+=x*cnt[x+1000000],cmn+=cnt[x+1000000],cmx-=cnt[x+1000000];
		LL disx=Mx-cmx*x+cmn*x-Mn;
		if(disx<=d) cx[disx]++;
	}
	l=Min-d,r=Max+d;
	cmx=n;cmn=Mn=Mx=0;
	FOR(i,1,n) Mx+=a[i].y;
	FOR(y,l,r) {
		if(y+1000000>=0) Mx-=y*cnty[y+1000000],Mn+=y*cnty[y+1000000],cmn+=cnty[y+1000000],cmx-=cnty[y+1000000];
		LL disy=Mx-cmx*y+cmn*y-Mn;
		if(disy<=d) cy[disy]++;
	}
	FOR(i,1,d) cy[i]+=cy[i-1];
	FOR(i,0,d) ans+=cx[i]*cy[d-i];
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：xqh07 (赞：2)

注意到横坐标与纵坐标相互独立，不妨分开研究。

先将平面上的所有点按 $x$ 排序，将答案点的横坐标从最中间开始（即使得 $x$ 方向上的总距离最小的位置）分别向左右移动，可以 $O(1)$ 动态求出总距离，直到总距离 $>  D$ 停止。将所得全部合法距离排序后丢入数组 $b$ 中。

按类似方法，将 $y$ 方向上的所有合法距离排序后放入数组 $c$ 中。

从小到大枚举 $b$ 中的每一个数，先二分求出 $c$ 数组满足 $b_{1}+c_{i} \le D$ 的最大 $i$ ，枚举过程中将 $i$ 不断往回跳至最大合法位置，将所有 $i$ 求和即为答案。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000005
int n, m, d, cnt1, cnt2, b[N << 1], c[N << 1], cnt, ans, res, mn = 1e9, mx = -1e9, pos, RES;
int sz1, sz2;
map<int, int> mp1, mp2;
struct node{
	int x, y;
}a[200005];
bool cmp1(node p, node q)
{
	return p.x != q.x ? p.x < q.x : p.y < q.y;
}
bool cmp2(node p, node q)
{
	return p.y != q.y ? p.y < q.y : p.x < q.x;
}
signed main()
{
	scanf("%lld%lld", &n, &d);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &a[i].x, &a[i].y), ++mp1[a[i].x], ++mp2[a[i].y];
	sort(a + 1, a + n + 1, cmp1);
	int i = a[n / 2 + 1].x;
	for(int j = 1; j <= n; j++) res += abs(a[j].x - i);
	RES = res;
	if(res > d) return printf("0\n"), 0;
	for(int j = 1; j <= n; j++)
	{
		if(a[j].x < i) ++cnt1;
		else ++cnt2;
	}
	b[++cnt] = res;
	for(int j = i - 1; ; j--)
	{
		res += cnt2 - cnt1;
		cnt1 -= mp1[j], cnt2 += mp1[j];
		if(res <= d) b[++cnt] = res;
		else break;
	}
	cnt1 = cnt2 = 0, res = RES;
	for(int j = 1; j <= n; j++)
	{
		if(a[j].x <= i) ++cnt1;
		else ++cnt2;
	}
	for(int j = i + 1; ; j++)
	{
		res += cnt1 - cnt2;
		cnt1 += mp1[j], cnt2 -= mp1[j];
		if(res <= d) b[++cnt] = res;
		else break;
	}
	sort(b + 1, b + cnt + 1), sz1 = cnt;
	cnt = res = cnt1 = cnt2 = 0;
	sort(a + 1, a + n + 1, cmp2);
	i = a[n / 2 + 1].y;
	for(int j = 1; j <= n; j++) res += abs(a[j].y - i);
	RES = res;
	if(res > d) return printf("0\n"), 0;
	for(int j = 1; j <= n; j++)
	{
		if(a[j].y < i) ++cnt1;
		else ++cnt2;
	}
	c[++cnt] = res;
	for(int j = i - 1; ; j--)
	{
		res += cnt2 - cnt1;
		cnt1 -= mp2[j], cnt2 += mp2[j];
		if(res <= d) c[++cnt] = res;
		else break;
	}
	cnt1 = cnt2 = 0, res = RES;
	for(int j = 1; j <= n; j++)
	{
		if(a[j].y <= i) ++cnt1;
		else ++cnt2;
	}
	for(int j = i + 1; ; j++)
	{
		res += cnt1 - cnt2;
		cnt1 += mp2[j], cnt2 -= mp2[j];
		if(res <= d) c[++cnt] = res;
		else break;
	}
	sort(c + 1, c + cnt + 1), sz2 = cnt;
	int pos = upper_bound(c + 1, c + sz2 + 1, d - b[1]) - c - 1;
	ans += pos;
	for(int i = 2; i <= sz1; i++)
	{
		if(d - b[i] < 0) break;
		while(c[pos] > d - b[i]) --pos;
		ans += pos;
	}
	printf("%lld\n", ans);
	return 0;
}

```

~~代码很长，抱歉~~

---

## 作者：forever_nope (赞：1)

我们将，

$$
\def\abs#1{\left\lvert{#1}\right\rvert}
\sum_{i=1}^n\left(\abs{x-x_i}+\abs{y-y_i}\right)
$$

拆为，

$$
\def\abs#1{\left\lvert{#1}\right\rvert}
\sum_{i=1}^n\abs{x-x_i}+\sum_{i=1}^n\abs{y-y_i}
$$

设，

$$
\def\abs#1{\left\lvert{#1}\right\rvert}
F(x)=\sum_{i=1}^n\abs{x-x_i}
$$

$$
\def\abs#1{\left\lvert{#1}\right\rvert}
G(y)=\sum_{i=1}^n\abs{y-y_i}
$$

问题即求满足，

$$
F(x)+G(y)\le D
$$

的点对 $x$ 数量。

---

考虑两边分别处理，假设我们已经求出了 $F,G$ 的值。

我们枚举每一个 $x$，那么就知道了 $F(x)$，然后考虑另一侧，

问题转化为，求满足，

$$
G(y)-D\le-F(x)
$$

的 $y$ 的数量。

我们可以在预处理 $G(x)$ 的时候，将 $G(y)-D$ 扔到 `vector` 里 `lower_bound` 即可。

那么这个问题就很简单了。

---

然后考虑求 $F(x),G(y)$ 的值。

发现绝对值不好处理，于是应用经典方法，拆绝对值，

$$
\def\sub#1{\left({#1}\right)}
F(x)=\sum_{i=1}^n\sub{x-x_i}[x_i\le x]+\sum_{i=1}^n\sub{x_i-x}[x_i>x]
$$

我们提前将所有的 $x_i$ 升序排序，设 $P(x)$ 表示最后一个 $x_i\le x$ 的 $i$，

$$
\def\sub#1{\left({#1}\right)}
F(x)=\sum_{i=1}^{P(x)}\sub{x-x_i}+\sum_{i=P(x)+1}^n\sub{x_i-x}
$$

将合式拆开，

$$
\def\sub#1{\left({#1}\right)}
F(x)=\sub{xP(x)-\sum_{i=1}^{P(x)}x_i}+\sub{\sum_{i=P(x)+1}^nx_i-nx+xP(x)}
$$

整理得，

$$
\def\sub#1{\left({#1}\right)}
F(x)=\sum_{i=P(x)+1}^nx_i-\sum_{i=1}^{P(x)}x_i-nx+2xP(x)
$$

设 $S_i$ 为 $x_i$ 的前缀和，即，

$$
S_i=\sum_{j=1}^ix_j
$$

那么，

$$
\def\sub#1{\left({#1}\right)}
F(x)=S_n-2S_{P(x)}-nx+2xP(x)
$$

容易发现 $P(x)$ 可以二分得到，而前面部分直接前缀和解决。

我们可以类似的求出 $G(y)$ 的值，问题解决。

---

代码：

```cpp
using ll = long long;

constexpr int N = 2e5 + 10;
constexpr int V = 2e6 + 10;

int n, D;

int X[N], Y[N];
ll F[2 * V + 10], G[2 * V + 10];
ll S[2 * V + 10], T[2 * V + 10];
int P[2 * V + 10], Q[2 * V + 10];

void calc(int *x, ll *s, ll *f, int *p) {
	sort(x + 1, x + n + 1);
	for (int i = -V; i <= V; ++i)
		p[i + V] = upper_bound(x + 1, x + n + 1, i) - 1 - x;
	for (int i = 1; i <= n; ++i)
		s[i] = x[i] + s[i - 1];
	for (int i = -V; i <= V; ++i)
		f[i + V] = s[n] - 2 * s[p[i + V]] - 1ll * n * i + 2ll * i * p[i + V];
}

void Main() {
	cin >> n >> D;
	for (int i = 1; i <= n; ++i)
		cin >> X[i] >> Y[i];
	calc(X, S, F, P);
	calc(Y, T, G, Q);
	vector<ll> bucket;
	bucket.reserve(2 * V);
	for (int y = -V; y <= V; ++y)
		bucket.push_back(G[y + V] - D);
	sort(bucket.begin(), bucket.end());
	ll ans = 0;
	for (int x = -V; x <= V; ++x)
		ans += upper_bound(bucket.begin(), bucket.end(), -F[x + V]) - bucket.begin();
	cout << ans << endl;
}
```

注意可能的点的坐标有可能超过 $10^6$，直接开到 $2\times10^6$ 即可。

---

## 作者：zrl123456 (赞：1)

[[ABC366E] Manhattan Multifocal Ellipse ](https://www.luogu.com.cn/problem/AT_abc366_e)  

题目考察：排序，二分，前缀和。（但需要一定的思维）   
题目简述：
给你 $n$ 个点，第 $i$ 个点的坐标是 $(x_i,y_i)$，求有多少个点 $(a,b)$ 使得 $(\sum_{i=1}^n|x_i-a|+|y_i-b|)\le d$。  
数据范围：  
- $1\le n\le 2\times 10^5$
- $0\le d\le 10^6$
- $\forall i\in[1,n],-10^6\le x_i,y_i\le 10^6$
---
由于 X 坐标和 Y 坐标互不相干，所以我们分开讨论。  

我们将 X 坐标和 Y 坐标分别排序。由于 $|x_i-a|+|y_i-b|\le d$ 的点 $(a,b)$ 才有贡献（$i\in[1,n]$），那么 $|x_i-a|\le d$ 且 $|y_i-b|\le d$ 的点才有可能做出贡献。  
我们枚举 X 坐标，设 $num_i$ 为当 X 坐标为 $i-2\times 10^6$ 时 X 坐标与其他点的 X 坐标的距离，$sumx_i$ 就等于 $\displaystyle\sum_{j=1}^ix_i$，那么 $num_p$ 等于（下面的 $id$ 指在序列中满足 $x_{id-1}<p-2\times 10^6$ 且 $x_{id}\ge p-2\times 10^6$ 的唯一的一个数）：  
$$\begin{aligned}num_p&=\sum_{i=1}^n|p-2\times 10^6-x_i|\\&=|\sum_{i=1}^{id-1}p-2\times 10^6-x_i|+|\sum_{i=id}^nx_i-p+2\times 10^6|\\&=|(p-2\times 10^6)(id-1)-\sum_{i=1}^{id}x_i|+|(\sum_{i=id+1}^nx_i)-(p-2\times 10^6)(n-id+1)|\\&=|(p-2\times 10^6)(id-1)-sumx_i|+|sumx_n-sumx_i-(p-2\times 10^6)(n-id+1)|\end{aligned}$$
这样我们就能求出它们之间的距离了。  

然后我们设 $res_j$ 等于 $\displaystyle\sum_{i=0}^Vnum_i=j$（$V$ 是值域），再对 $res$ 求前缀和。  

再看 Y 坐标，跟上面一样求出 Y 坐标与其他店的 Y 坐标的总距离，设其为 $id$，若 $id\le d$，则它的贡献就是 $res_{d-id}$。  

时间复杂度为 $\Theta(V\log n)$。  
[代码](https://atcoder.jp/contests/abc366/submissions/56550280)

---

## 作者：zjj2024 (赞：1)

### 思路

由于数据范围非常大，考虑二分。

因为 $\displaystyle \sum_{i=1}^N (|x-x_i|+|y-y_i|)=\bigg(\displaystyle \sum_{i=1}^N |x-x_i|\bigg)+\bigg(\displaystyle \sum_{i=1}^N |y-y_i|\bigg)$，考虑将 $x$ 和 $y$ 分类讨论。

可以使用前缀和的方法分别计算出横轴的每一个点与其他每一个 $x_i$ 的差的绝对值记为 $w_i$。

可以从前往后做一遍，再从后往前做一遍即可。

纵轴同样处理。

对横轴上每一个点 $i$ 而言，纵轴的差成一个凸函数，将峰值两边分开做二分，找到两个边界上的点，使得 $D-w_i$ 小于等于等于纵轴上的差的绝对值之和。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005,B=2000005;//可能答案绝对值大于1000000
//B表示偏移量
ll numf[2*B],numg[2*B],numfy[2*B],numgy[2*B];
ll f[2*B],g[2*B],fy[2*B],gy[2*B],x[N],y[N];//有1G空间
//f记录从前到后，g记录从后到前，num表示个数，y表示横轴(？)
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		numf[x[i]+B]++;
		numg[x[i]+B]++;
		numfy[y[i]+B]++;
		numgy[y[i]+B]++;//个数加一
	}
	for(int i=2;i<2*B;i++)
	{
		numf[i]+=numf[i-1];
		numfy[i]+=numfy[i-1];
		f[i]=f[i-1]+numf[i-1];
		fy[i]=fy[i-1]+numfy[i-1];//统计个数
	}
	for(int i=2*B-3;i>=1;i--)
	{
		numg[i]+=numg[i+1];
		numgy[i]+=numgy[i+1];
		g[i]=g[i+1]+numg[i+1];
		gy[i]=gy[i+1]+numgy[i+1];//统计前缀和后缀的差值之和
	}
	ll minn=1e18,hi;
	for(int i=1;i<2*B;i++)
	{
		if(fy[i]+gy[i]<minn)//fy[i]+gy[i]=w[i]
		{
			minn=fy[i]+gy[i];
			hi=i;//下凸函数峰值
		}
	}
	ll ans=0;
	for(int i=1;i<2*B;i++)
	{
		if(f[i]+g[i]>d)continue;//已经超标，跳出，不用计算
		ll l=1,r=hi,mid,p=d-f[i]-g[i],ly;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(fy[mid]+gy[mid]>p)l=mid+1;
			else r=mid;
		}
		if(fy[l]+gy[l]>p)l++;//二分
		ly=l;
		l=hi+1;
		r=2*B-1;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(fy[mid]+gy[mid]>p)r=mid-1;
			else l=mid;
		}
		if(fy[l]+gy[l]>p)l--;
		ans+=l-ly+1;
	}
	cout<<ans<<'\n';
	return 0;
}

```

---

## 作者：Big_Dinosaur (赞：1)

**本题解复杂度较劣，本机上至少 $2$ 秒，但在 AT 上快很多。**

切入正题，暴力枚举 $x,y$ 显然不行，考虑枚举 $x$，统计合法的 $y$ 总数。

如何计算呢？先看看式子：$ \displaystyle \sum_{i=1}^N(|x-x_i|+|y-y_i|)$，去括号后重新写一下式子，变成了 $\displaystyle \sum_{i=1}^N|x-x_i|+\displaystyle \sum_{i=1}^N|y-y_i|$。

其中第一个 $\sum$ 与 $y$ 无关，而且可以用前缀和维护计算。然而对于后一个 $\sum$ 取值与 $x$ 无关，对于每一个 $y$ 都有确定的值，也可以前缀和维护计算。

由于式子值 $\le D$，可以对于每个 $y$ 对应的 $\displaystyle \sum_{i=1}^N|y-y_i|$ 排序，二分。

也可以对每个 $x$ 对应的 $\displaystyle \sum_{i=1}^N|x-x_i|$ 排序，用双指针做。我用了后者。

排序排到多少？$\displaystyle\max_{i=1}^Nx_i-\displaystyle\min_{i=1}^Nx_i$、$\displaystyle\max_{i=1}^Ny_i-\displaystyle\min_{i=1}^Ny_i$ 可能不够，$4\times10^6$（也就是之前的值加上 $2\times D$）够了。

理由：当点很少切 $D$ 较大时可能有答案 $x,y$ 过大或过小。事实上样例已经涉及到这一点。

赛时 AC 记录：<https://atcoder.jp/contests/abc366/submissions/56558014>

---

## 作者：wly09 (赞：1)

~~赛时因为数组开小没过~~

## 题意

在二维平面上给你 $N$ 个整点，问有多少个整点到这 $N$ 个点的曼哈顿距离之和小于等于 $D$。

## 思路

观察式子

$$
\sum_{i=1}^N (|x-x_i|+|y-y_i|) \leq D
$$

发现我们可以将 $x$ 和 $y$ 分开考虑，统计结果。

以 $x$ 为例，记

$$
\sum_{i=1}^N |x-x_i|=X
$$

统计对于每个 $X$，$x$ 的数量。

考虑遍历 $x$，由于 $|D|,|x_i|\le 10^6$，只需遍历 $[-2\times 10^6,2\times 10^6]$ 内的整数。

考虑如何 $O(1)$ 递推。

假如已经知道 $x=t$ 时 $X$ 的值，如果令 $x\gets t+1$，显然 $X$ 需要减去 $|\{x_i\mid x_i>t\}|-|\{x_i\mid x_i\le t\}|$，这个东西可以均摊 $O(1)$ 地推出来（需要提前对 $x_i$ 排序），或者用树状数组维护。

$y$ 是类似的。

剩下对其中一个数组做前缀和，双指针扫一遍即可。

[AC 记录](https://atcoder.jp/contests/abc366/submissions/56573348)

---

## 作者：xpz0525 (赞：0)

### [ABC366E] Manhattan Multifocal Ellipse 题解
注意到这个式子中 $x$ 和 $y$ 其实可以分开考虑。我们可以分别求出对于每个 $x$，$\sum \nolimits_{i=1}^N(\vert x-x_i \vert)$ 的值；以及对于每个 $y$，$\sum \nolimits_{i=1}^N(\vert y-y_i \vert)$ 的值。后对结果排序后，就可以用双指针的方法去统计出两值之和小于等于 $D$ 的 $(x,y)$ 数对个数了。
**AC** 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n,d,x[200001],y[200001];
vector<ll> calc(int a[]){
	vector<ll> res;
	ll sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
	}
	res.push_back(sum+2000000ll*n); // 在-2000000坐标时，所有点到它的距离
	int j=0; // j代表在当前坐标及左侧的点个数
	for(ll i=-1999999;i<=2000000;i++){
		ll nxt=res.back();
		nxt-=n-j; // 与右侧的每个点距离都减少1，总共减少n-j
		nxt+=j; // 与左侧及当前位置每个点所有距离都增加1，总共增加j
		while(j+1<=n&&a[j+1]<=i){ // 更新j
			j++;
		}
		res.push_back(nxt); // 所有点到当前位置i的距离之和
	}
	sort(res.begin(),res.end()); // 从?到?将距离之和排序
	return res;
}
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i]; 
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	vector<ll> vx=calc(x),vy=calc(y); // 分别求出x，y?向上所有坐标的距离之和
	int j=vy.size()-1;
	ll ans=0;
	for(int i=0;i<vx.size();i++){ // 双指针
		while(j>=0&&vx[i]+vy[j]>d) j--;
		ans+=j+1;
	}
	cout<<ans;
}
```

---

## 作者：Walter_Fang (赞：0)

`ABC` 最水的一场。

### 题意
给定二维平面上的 $N$ 个点 $(x_{1},y_{1}),(x_{2},y_{2})\ldots(x_{N},y_{N})$ 和非负整数 $D$，试求满足 $\sum_{i=1}^n(|x-x_{i}|,|y-y_{i}|) \le D$ 的整数对 $(x,y)$ 的个数。

### 解析
需要满足的条件为 $\sum_{i=1}^n(|x-x_{i}|,|y-y_{i}|) \le D$，移项即得 $D-\sum_{i=1}^n{|x-x_i|} \geq \sum_{i=1}^n|y-y_i|$。

不妨枚举所有的 $x$ 与 $y$，并将其排序并记录，然后用双指针维护即可。理论二分也可行，未尝试。

### 赛时代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e6+10,M=(N<<2)+10;
ll n,d,i,j,t,s,ans,x[N],y[N],f1[M],f2[M],s1[M],s2[M];
int main(){
	cin>>n>>d;
	for(i=1;i<=n;i++)cin>>x[i]>>y[i],f1[(N<<1)+y[i]+1]++,f2[(N<<1)+y[i]-1]++;
	for(i=0;i<=M;i++)t+=f1[i],f1[i]=0,s+=t,s2[i]+=s;
	t=s=0;
	for(i=M;i>=0;i--)t+=f2[i],f2[i]=0,s+=t,s2[i]+=s;
	for(i=1;i<=n;i++)f1[(N<<1)+x[i]+1]++,f2[(N<<1)+x[i]-1]++;
	t=s=0;
	for(i=0;i<=M;i++)t+=f1[i],f1[i]=0,s+=t,s1[i]+=s;
	t=s=0;
	for(i=M;i>=0;i--)t+=f2[i],f2[i]=0,s+=t,s1[i]+=s;
	t=M;stable_sort(s1,s1+t+1);stable_sort(s2,s2+t+1);
	for(i=t;i>=0;i--){
		while(j<=t&&s1[i]+s2[j]<=d)j++;
		ans+=j;
	}
	cout<<ans;
}
```

---

## 作者：Otue (赞：0)

观察这个柿子 $\sum_{i=1}^n(|x-x_{i}| + |y-y_{i}|) \le D$ 可以发现先可以拆成 $\sum_{i=1}^n|x-x_{i}| + \sum_{i=1}^n|y-y_{i}| \le D$。即发现 $x,y$ 是完全的独立的。

那么我们可以对于每个 $-2 \times 10^6\leq x\leq 2 \times 10^6$，预处理出 $\sum_{i=1}^n|x-x_{i}|$ 记为 $A_i$。对 $y$ 数组（记为 $B_i$）也同理。

处理答案：枚举 $(x,y)$ 数对中的 $x$，此部分造成 $A_x$ 贡献，只需要查出有多少个 $y$ 满足 $B_y\leq D-A_x$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)

const int N = 1e6 + 5;
int n, d, x[N], y[N], pre[N], suf[N], cnt[N], res;
unordered_map<int, int> t1, t2;

signed main() {
	cin >> n >> d;
	_for(i, 1, n) cin >> x[i] >> y[i];
	sort(x + 1, x + n + 1);
	_for(i, 1, n) pre[i] = pre[i - 1] + x[i];
	_pfor(i, n, 1) suf[i] = suf[i + 1] + x[i];
	_for(i, -2e6, 2e6) {
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (x[mid] <= i) l = mid;
			else r = mid - 1;
		}
		if (x[l] <= i) t1[i] = i * l - pre[l] + suf[l + 1] - i * (n - l);
		else t1[i] = pre[n] - i * n;
	}
	sort(y + 1, y + n + 1);
	_for(i, 1, n) pre[i] = pre[i - 1] + y[i];
	_pfor(i, n, 1) suf[i] = suf[i + 1] + y[i];
	_for(i, -2e6, 2e6) {
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (y[mid] <= i) l = mid;
			else r = mid - 1;
		}
		if (y[l] <= i) t2[i] = i * l - pre[l] + suf[l + 1] - i * (n - l);
		else t2[i] = pre[n] - i * n;
		if (t2[i] <= d) cnt[t2[i]]++;
	}
	_for(i, 1, d) cnt[i] += cnt[i - 1];
	_for(i, -2e6, 2e6) {
		if (t1[i] > d) continue;
		res += cnt[d - t1[i]];
	}
	cout << res << endl;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
你会发现 $|x-x_i|$ 和 $|y-y_i|$ 是独立的，所以可以分开计算。因为 $D\le10^6$，$x_i,y_i\le10^6$，所以我们只要把 $x\in[-2\times10^6,2\times10^6]$ 进行枚举，并利用前缀和优化 $O(1)$ 计算 $\sum|x-x_i|$，若 $\sum|x-x_i|\le D$，则把它放进桶里。$y$ 的计算同理。我们只要把任意一个桶进行前缀和并更具乘法原理求出 $\sum(sx_i\times sy_{D-i})$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, d, id = 0, a[200005], b[200005], s1[1000005], s2[1000005];
ll x, s[200005], sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> d;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i] >> b[i];
	sort (a + 1, a + 1 + n), sort (b + 1, b + 1 + n);
	for (int i = 1; i <= n; ++ i)
		s[i] = s[i - 1] + a[i];
	for (int i = -2e6, tmp = 2e6; i <= tmp; ++ i) {
		while (id < n && a[id + 1] <= i)
			++ id;
		x = (id * (ll) i - s[id]) + (s[n] - s[id] - (ll) (n - id) * i);
		if (x <= d)
			++ s1[x];
	}
	for (int i = 1; i <= n; ++ i)
		s[i] = s[i - 1] + b[i];
	id = 0;
	for (int i = -2e6, tmp = 2e6; i <= tmp; ++ i) {
		while (id < n && b[id + 1] <= i)
			++ id;
		x = (id * (ll) i - s[id]) + (s[n] - s[id] - (ll) (n - id) * i);
		if (x <= d)
			++ s2[x];
	}
	for (int i = 1; i <= d; ++ i)
		s2[i] += s2[i - 1];
	for (int i = 0; i <= d; ++ i)
		sum += s1[i] * (ll) s2[d - i];
	cout << sum;
	I AK IOI
}
```

---

## 作者：Milthm (赞：0)

发现 $x$ 和 $y$ 的贡献可以分开，这启示我们分开处理。

对于 $\sum |x-x_i|$ 这样的式子，我们可以枚举 $x$，然后通过二分和前缀和快速地算出对应的值，因为有小于等于 $D$ 的限制，我们可以只枚举 $-2\times 10^6 \sim 2\times 10^6$ 的值，这样就不会超时了。对于 $y$ 也是一样的操作。

接下来问题转化成了：给定两个数组，求 $a_x+b_y\le D$ 的二元组 $(x,y)$ 个数，这是一个经典问题，可以通过给 $a$ 正序排序，$b$ 倒序排序，然后双指针 $O(n)$ 求得。

时间复杂度 $O(V \log n)$，其中 $V$ 是枚举的值域，也就是 $4\times 10^6$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 4000007
using namespace std;
int x[N],y[N],n,fx[N],fy[N],r[N],b[N],d,ovo,ans;
int cmp(int x,int y){
	return x>y;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;++i)cin>>x[i]>>y[i];
	sort(x+1,x+n+1);sort(y+1,y+n+1);
	for(int i=1;i<=n;++i)fx[i]=fx[i-1]+x[i],fy[i]=fy[i-1]+y[i];
	memset(r,0x3f,sizeof(r));
	for(int i=-2e6;i<=2e6;++i){
		int k=upper_bound(x+1,x+n+1,i)-x-1;
		r[++ovo]=i*k-fx[k]+fx[n]-fx[k]-i*(n-k);
	}
	sort(r+1,r+ovo+1);
	ovo=0;
	for(int i=-2e6;i<=2e6;++i){
		int k=upper_bound(y+1,y+n+1,i)-y-1;
		b[++ovo]=i*k-fy[k]+fy[n]-fy[k]-i*(n-k);
	}
	sort(b+1,b+ovo+1,cmp);
	int now=1;
	for(int i=1;i<=ovo;++i){
		while(r[now]+b[i]<=d&&now<=ovo)++now;
		ans+=now-1; 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yanlikun (赞：0)

# 题意
给定 $n$ 个点的坐标，以及一个正整数 $d$，求有多少个点与这 $n$ 个点的曼哈顿距离之和小于等于 $d$。
# 思路
显然，直接去求曼哈顿距离会很麻烦，我们不妨将这 $n$ 个点的 $x_i$ 和 $y_i$ 拆开来分别求解。

首先，将 $x_i$ 和 $y_i$ 排序。其次，通过观察数据范围可以发现，符合要求的点它的坐标总是在 $-2 \times 10^6 \le X \le 2 \times 10^6, -2 \times 10^6 \le Y \le 2 \times 10^6$ 之间。所以，我们可以通过分别枚举 $X$ 的值和 $Y$ 的值，并判断是否小于等于 $d$。如何判断详见代码。最后，用前缀和、组合数学统计答案即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
int a[2000005],b[2000005];
ll d,suma,sumb,ansa[2000005],ansb[2000005];
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		suma+=a[i];
		sumb+=b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	ll presum=0;
	int now=1;
	for(ll i=-2e6;i<=2e6;i++)
	{
		while(now<=n&&a[now]<=i)
		{
			suma-=a[now];
			presum+=a[now];
			now++;
		}
		ll dis=i*(now-1)-presum+suma-i*(n-now+1);//用前缀和和后缀和算出当前的X与这n个x的距离
		if(dis<=d)
			ansa[dis]++;
	}
	now=1;
	presum=0;
	for(ll i=-2e6;i<=2e6;i++)
	{
		while(now<=n&&b[now]<=i)
		{
			sumb-=b[now];
			presum+=b[now];
			now++;
		}
		ll dis=i*(now-1)-presum+sumb-i*(n-now+1);//用前缀和和后缀和算出当前的Y与这n个y的距离
		if(dis<=d)
			ansb[dis]++;
	}
	ll ans=0;
	for(ll i=1;i<=d;i++)
		ansa[i]+=ansa[i-1];//小优化
	for(ll i=0;i<=d;i++)
		ans+=ansb[i]*ansa[d-i];//组合数学乘法原理计算总搭配数对(X,Y)
	cout<<ans;
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
尺取法，首先我们需要预处理出对于 $-2\times 10^6 \leq X \leq 2\times 10^6$ 的 $\sum_{i=1}^{n} {\left|X-x_i\right|}$，以及对于 $-2\times 10^6 \leq Y \leq 2\times 10^6$ 的 $\sum_{i=1}^{n} {\left|Y-y_i\right|}$。然后对两个数组排序，于是现在的问题就是你要求对于在上述范围内的 $X$，你需要求出有多少个满足题意的 $Y$，将这样的方案数累加就是答案，发现这个东西可以采用尺取法去维护。
### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int N=5e5+5,Max=2e6;
int n,d,f[Max*2+5],g[Max*2+5];
struct node{
	int x,y;
}a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	} 
	sort(a+1,a+n+1,[](const node &A,const node &B){
		return A.x<B.x; 
	});
    int cnt=0;
    for(int i=1;i<=n;i++) f[0]+=a[i].x+Max;
	for(int i=-Max+1;i<=Max;i++){
        while(a[cnt+1].x<i&&cnt<n) cnt++;
        f[i+Max]=f[i+Max-1]+2*cnt-n;
    }
    sort(a+1,a+n+1,[](const node &A,const node &B){
		return A.y<B.y; 
	});
    cnt=0;
    for(int i=1;i<=n;i++) g[0]+=a[i].y+Max;
    for(int i=-Max+1;i<=Max;i++){
        while(a[cnt+1].y<i&&cnt<n) cnt++;
        g[i+Max]=g[i+Max-1]+2*cnt-n;
    }
    // cout<<f[Max]<<' '<<g[Max]<<'\n';
    int ans=0;
    // for(int i=-1;i<=2;i++) cout<<f[i+Max]<<' ';
    // cout<<'\n';
    // for(int i=-1;i<=1;i++) cout<<g[i+Max]<<' ';
    // cout<<'\n';
    sort(f,f+2*Max+1);sort(g,g+2*Max+1);
    // for(int i=0;i<=20;i++){
        // cout<<f[i]<<' '<<g[i]<<'\n';
    // }
    // cout<<"count:\n";
    for(int i=0,j=2*Max;i<=2*Max;i++){
        while(f[i]+g[j]>d&&j>0) j--;
        // cout<<i<<' '<<j<<'\n';
        if(f[i]+g[j]<=d) ans+=j+1;
        // else break;
    }cout<<ans;
	return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解：
观察式子：
 $$\sum_{i=1}^N (|x-x_i|+|y-y_i|) \leq D$$
有两个变量不好维护，考虑分开计算，即：
 $$sum_x=\sum_{i=1}^N |x-x_i|$$
 $$sum_y=\sum_{i=1}^N |y-y_i|$$
我们要求：
 $$sum_x+sum_y \leq D$$
先暴力枚举每个 $x$ 的可能，再将其对应的 $sum_x$ 排序并记录下来，$sum_y$ 同理，后用尺取法（或二分）去统计每个当 $sum_x$ 固定时的 $sum_y$ 的可能情况。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,d,x[N+5],y[N+5];
long long ans=0,bz[4*N+5],bz2[4*N+5],sum1[4*N+5],sum2[4*N+5];
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
    {
		cin>>x[i]>>y[i];
		++bz[2*N+y[i]+1],++bz2[2*N+y[i]-1];
	}
	long long tmp=0,add=0;
	for(int i=0;i<=4*N;i++)
    {
		tmp+=bz[i],bz[i]=0;
		add+=tmp,sum2[i]+=add;
	}
	tmp=add=0;
	for(int i=4*N;i>=0;i--)
    {
		tmp+=bz2[i],bz2[i]=0;
		add+=tmp,sum2[i]+=add;
	}
	for(int i=1;i<=n;i++)
    {
		++bz[2*N+x[i]+1],++bz2[2*N+x[i]-1];
	}
	tmp=add=0;
	for(int i=0;i<=4*N;i++)
    {
		tmp+=bz[i],bz[i]=0;
		add+=tmp;
		sum1[i]+=add;
	}
	tmp=add=0;
	for(int i=4*N;i>=0;i--)
    {
		tmp+=bz2[i],bz2[i]=0;
		add+=tmp;
		sum1[i]+=add;
	}
	int w=4*N;
	sort(sum1,sum1+w+1);
	sort(sum2,sum2+w+1);
	for(int i=w,j=0;i>=0;i--)
    {
		while(j<=w&&sum1[i]+sum2[j]<=d) j++;
		ans+=j;
	}
	cout<<ans;
}
```

---

## 作者：EricWan (赞：0)

我们观察发现，两种坐标的代价可以分开计算。

先讲怎样快速计算 $(x, y)$ 的价值：我们可以分别对点的两个坐标排序，那么对于 $x_i\le x$ 的点，它的横坐标对总代价产生的影响就是 $x-x_i$，反之，对于 $x_i>x$ 的点，它的横坐标对总代价产生的影响就是 $x_i-x$，我们排序后二分出这个边界，用前缀和快速计算总代价就可以在 $O(\log n)$ 的复杂度内完成横坐标的代价计算，纵坐标同理。

考虑最优情况，也就是 $x$ 是中位数的情况，我们可以向两边扫，找出 $x$ 是中位数时 $y$ 的取值范围，我们可以证明，当 $x$ 从中位数不断缩小或增大时，$y$ 的取值范围会不断缩小，我们维护两个坐标，在调整 $x$ 时同时调整它们就可以在 $O(A\log n)$ 的复杂度内求出答案了。

数组要开大，我开了两倍空间好像还 WA 了（莫名吃了一个罚时）。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 1e18
#define MAXN 8000005
using namespace std;
int n, d, x[MAXN], y[MAXN], l, r, xs[MAXN], ys[MAXN], sx[MAXN], sy[MAXN], ans;
int check(const int nowx, const int nowy) {
	int xi = lower_bound(xs + 1, xs + 1 + n, nowx) - xs - 1;
	int ans = 0;
	ans += xi * nowx - sx[xi];
	ans += sx[n] - sx[xi] - (n - xi) * nowx;
	ans += yi * nowy - sy[yi];
	ans += sy[n] - sy[yi] - (n - yi) * nowy;
	return ans;
}
signed main() {
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
		x[i] += 2000000;
		y[i] += 2000000;
		xs[i] = x[i];
		ys[i] = y[i];
	}
	sort(xs + 1, xs + 1 + n);
	sort(ys + 1, ys + 1 + n);
	for (int i = 1; i <= n; i++) sx[i] = sx[i - 1] + xs[i];
	for (int i = 1; i <= n; i++) sy[i] = sy[i - 1] + ys[i];
	const int midx = xs[(n + 1) / 2];
	l = ys[(n + 1) / 2], r = ys[(n + 1) / 2] - 1;
	while (check(midx, l - 1) <= d) l--;
	while (check(midx, r + 1) <= d) r++;
	const int widestl = l, widestr = r;
	ans = widestr - widestl + 1;
	for (int i = midx - 1; i >= 0; i--) {
		while (check(i, l) > d && l <= r) l++;
		while (check(i, r) > d && l <= r) r--;
		ans += r - l + 1;
		if (r < l) break;
	}
	l = widestl, r = widestr;
	for (int i = midx + 1; i <= 4000000; i++) {
		while (check(i, l) > d && l <= r) l++;
		while (check(i, r) > d && l <= r) r--;
		ans += r - l + 1;
		if (r < l) break;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

这场 ABC 打完之后上青了，写篇题解留作纪念。

### 题意简述

在坐标系上有 $N$ 个点，求到这些点曼哈顿距离总和不超过 $D$ 的整点数量的总和。

### 题目分析

我们可以将一个点到这 $N$ 个点的曼哈顿距离拆分成这个点与这些点的 $x$ 坐标的差之和，以及这个点与这些点的 $y$ 坐标的差之和（即 $\sum_{i=1}^{N}\lvert X-x_i\rvert+\sum_{i=1}^{N}\lvert Y-y_i\rvert$）。

因为 $D\le 10^6$，所以所有合法点的 $x,y$ 坐标都在 $[-2\times 10^6,2\times 10^6]$ 之间。考虑枚举合法点的 $x$ 坐标，并预处理对于每一个 $y$ 坐标，对应的点与题目中给出的点的 $y$ 坐标的差之和，枚举时二分即可。

注意坐标中可能有负数，读入时把 $x,y$ 坐标都平移 $2\times 10^6$ 个单位就可以解决。

[AC 记录](https://atcoder.jp/contests/abc366/submissions/56560714)。

---

## 作者：WerChange (赞：0)

推荐在 [cnblogs](https://www.cnblogs.com/WerChange/p/18354476) 上阅读
# Solution
## 题意简述

二维平面上有 $N$ 个点 $(x_1,y_1),\dots,(x_N,y_N)$ 和一个非负整数 $D$。

求有多少对点对 $(x,y)$ 满足 $\sum\limits_{i=1}^N (|x-x_i|+|y-y_i|)\le D$。

## 思路

发现 $x_i$ 与 $y_i$ 的捆绑关系不强（其实是几乎没有关联），所以我们分开考虑，也就是先考虑 $\sum\limits_{i=1}^n|x-x_i|$，得到结论后另外一边也是一样的。

见到绝对值先拆绝对值，我们可以先对 $x_i$ 排个序，就可以通过枚举知道 $x$ 的相对位置，结合前缀和，可以 $O(1)$ 得到上面这个和式的值。设这个值为 $A_x$，我们可以直接枚举 $x\in [-10^6,10^6]$，然后 $O(M)$ 得到 $A_x$。另外一边照葫芦画瓢，也可以快速得知 $B_y$ 的值。

现在考虑计数。首先可以枚举值域内的每个 $x$，枚举中的子任务为求有多少个 $y$ 满足 $B_y\leq D-A_x$。这是很简单的，对所有 $B_y$ 排个序，二分答案即可。

[code](https://atcoder.jp/contests/abc366/submissions/56620096)

---

