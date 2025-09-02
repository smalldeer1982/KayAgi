# Eugene and an array

## 题目描述

Eugene likes working with arrays. And today he needs your help in solving one challenging task.

An array $ c $ is a subarray of an array $ b $ if $ c $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

Let's call a nonempty array good if for every nonempty subarray of this array, sum of the elements of this subarray is nonzero. For example, array $ [-1, 2, -3] $ is good, as all arrays $ [-1] $ , $ [-1, 2] $ , $ [-1, 2, -3] $ , $ [2] $ , $ [2, -3] $ , $ [-3] $ have nonzero sums of elements. However, array $ [-1, 2, -1, -3] $ isn't good, as his subarray $ [-1, 2, -1] $ has sum of elements equal to $ 0 $ .

Help Eugene to calculate the number of nonempty good subarrays of a given array $ a $ .

## 说明/提示

In the first sample, the following subarrays are good: $ [1] $ , $ [1, 2] $ , $ [2] $ , $ [2, -3] $ , $ [-3] $ . However, the subarray $ [1, 2, -3] $ isn't good, as its subarray $ [1, 2, -3] $ has sum of elements equal to $ 0 $ .

In the second sample, three subarrays of size 1 are the only good subarrays. At the same time, the subarray $ [41, -41, 41] $ isn't good, as its subarray $ [41, -41] $ has sum of elements equal to $ 0 $ .

## 样例 #1

### 输入

```
3
1 2 -3```

### 输出

```
5```

## 样例 #2

### 输入

```
3
41 -41 41```

### 输出

```
3```

# 题解

## 作者：AutumnKite (赞：9)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

不知道为什么 CF 的评论里有很多人说这题很难，感觉好像就是个套路题？

首先考虑求出 $a_i$ 的前缀和 $b_i=\sum\limits_{j=1}^{i} a_j$，那么一个区间 $(l,r]$ 合法当且仅当不存在 $l\le j < i\le r$ 使得 $b_i=b_j$。

考虑对于一个 $b_i$，求出上一个与 $b_i$ 相同的位置 $lst_i$，即
$$lst_i=\max\{j\ |\ j<i,b_j=b_i\}$$

不存在则 $lst_i=-1$。

那么区间 $(l,r]$ 合法的条件变为对于所有 $0\le i\le n$，满足 $l > lst_i$ 或 $r < i$。

那么我们只要从左往右枚举 $r$，那么 $l$ 需要大于 $\max\{lst_j\ |\ j \le r\}$，直接在枚举的同时维护 $lst$ 数组的前缀 $\max$ 即可。

### 代码

```cpp
const int N = 200005;

int n, lst[N];
long long a[N];
std::map<long long, int> M;

void solve() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] += a[i - 1];
	}
	for (int i = 0; i <= n; ++i) { // 用 std::map 计算 lst 数组
		if (!M.count(a[i])) {
			lst[i] = -1;
		} else {
			lst[i] = M[a[i]];
		}
		M[a[i]] = i;
	}
	int mx = -1;
	long long ans = 0;
	for (int i = 0; i <= n; ++i) {
		mx = std::max(mx, lst[i]);
		ans += i - mx - 1;
	}
	print(ans);
}
```

---

## 作者：Lskkkno1 (赞：4)

- [CF1333C Eugene and an array](https://www.luogu.com.cn/problem/CF1333C)


这题可以预处理出每一个极小的不可行区间，然后枚举右端点，左端点的范围就确定了。

预处理极小不可行区间要用 `map / unordered_map`。 

看到这题很多用 `unordered_map` 的都被卡了，很不甘心。

于是我来教大家如何用 `unordered_map` 不被卡吧。

[也可以直接到我博客上看](https://www.cnblogs.com/Lskkkno1/p/12667149.html)。

先说一下为什么会被卡 :

很多 CF 上的大神直接根据 STL 的源代码来造出 hack 数据，导致 `unordered_map` 单次复杂度劣化成 $O(n)$。

那有没有防止被卡的方法呢？

当然有，那就是自己写哈希函数，然后让哈希函数与时间戳有关就行了。~~（难道还能预判一个时间来构造 hack 数据不成？~~

下面给出哈希函数的代码 :

```cpp
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		return x; 
	}
	size_t operator () (uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); // 时间戳
		return splitmix64(x + FIXED_RANDOM);
	}
};
```


然后再定义 `unordered_map` 的时候就可以像下面这样定义了 :

```cpp
unordered_map<uint64_t, int, custom_hash> safe_map;
```

然后这题的代码 :

```cpp
#include <bits/stdc++.h>
#define N 200005

using namespace std;

int n;
int a[N], rig[N];

struct custom_hash {
	static long long splitmix(long long x) {
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		return x; 
	}
	size_t operator () (long long x) const {
		static const long long 
		FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix(x + FIXED_RANDOM);
	}
};

unordered_map<long long, int, custom_hash> p;

int main() {
	scanf("%d", &n);
	p[0] = 0;
	long long psum = 0;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		psum += x;
		if(p.count(psum))
			rig[i] = p[psum] + 1;
		p[psum] = i;
	}
	long long ans = 0;
	for(int i = 1, rigMost = 0; i <= n; ++i) {
		rigMost = max(rigMost, rig[i]);
		ans += i - rigMost;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：PDAST (赞：3)

这是一篇代码简洁的题解。
## 题意
给出一个数组 $A$，求 $A$ 中有多少个子数组，和不为 $0$ 且该子数组的所有子数组和均不为 $0$。
## 分析
当两个位置的前缀和相等时，满足条件的子数组不能包含这两个位置，所以只需要枚举右端点，即可求出左端点与该区间的满足条件的子数组的个数。
## 思路
采用贪心，每次加上一个输入的值，并设立左端点，每次加上右端点减左端点作为答案。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,sum,x,n,l;
map<int,int>mp;
signed main(){
	cin>>n;
	mp[0]=0;
	for(int i=1;i<=n;i++){
		cin>>x;
		sum+=x;
		if(mp.count(sum))l=max(l,mp[sum]+1);
		ans+=i-l;
		mp[sum]=i;
	}
	cout<<ans;
	return 0;
}
~~~

---

## 作者：gyh20 (赞：3)

直接算不好算，可以对于每一个位置求答案。

一个错误的做法：每一个位置最多能延伸到的位置就是下一个前缀和和他前一个位置的前缀和相等的位置（有点绕，对着样例理解一下），直接用 map 存储答案（unordered_map 会被卡）。

来看看这个做法为什么是错的：

比如这组数据：

$3$

$2\space -1\space 1$

如果按上述做法做，$2$ 就能一直延伸，全部合法，然而 $1\sim 3$ 这个区间是不合法的。

看上去不好处理，实际上我们令 $ans_i$ 表示延伸到的位置，那么 $ans_i$ 对 $ans_{i+1}$ 去 $\min$ 即可。如上述例子， $-1\space 1$ 已经被考虑到了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,a[200002],b[200002],m,t,sum,x,ans[200002];
map<int,int>v;
signed main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	for(re int i=1;i<=n;++i){
		v[b[i-1]]=i;
		b[i]=b[i-1]+a[i];
		ans[v[b[i]]]=i;
}ans[n+1]=1e9;
	for(re int i=n;i;--i){
	//	if(a[i]==0)ans[i]=i;
		if(!ans[i])ans[i]=n+1;
		ans[i]=min(ans[i],ans[i+1]);
		sum+=ans[i]-i;
	}
	printf("%lld",sum);
}
```



---

## 作者：换个思路 (赞：2)

思维题 想到简单 想不到难。

首先我们的目标肯定是要找到连续的一段的和是否为0，然后我们才可以进行计算。那问题来了，我们要用什么方法找到这个和为0的区间呢。那么 前缀和就来了。如果说 a[l] == a[r] 那么 我们就可以说，在[l + 1 , r]这个区间的和为0，然后我们再用一个变量动态更新最大的l就可以轻松a掉了。 简短的代码：
```cpp
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
map <long long, long long> a;
long long ans, zz[200010], mx = -1, sum;
int n, x;
int main(void) {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n; a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x; zz[i] += zz[i - 1] + x;
        if (a.count(zz[i])) mx = max(mx, a[zz[i]]);
        a[zz[i]] = i;
        ans += i - mx - 1;
    }
    cout << ans <<endl;
    return 0;
}
```

---

## 作者：Scintilla (赞：2)

题解修改，请予通过，谢谢！

[CF传送门](https://codeforces.com/contest/1333/problem/C) && [luogu传送门](https://www.luogu.com.cn/problem/CF1333C)

### 题意

给你一个序列，让你求使得该子串没有和为 $0$ 的子串的子串的个数。

### 思路

设 $f[i]$ 表示以 $i$ 结尾的合法子串数量。

考虑不合法的情况。若子串 $s_j \dots s_i (j \leq i)$ 不合法，则定存在 $l,r \in [j, i], l \leq r$ 满足 $\sum \limits_{k=l}^ra[k]=0$。于是我们只需要找到 $maxl \leq maxr \leq i$，使得 $\sum \limits_{k=maxl}^{maxr}a[k]=0$，且 $maxl$ 最大。

设 $sum[i] = \sum \limits_{k=1}^ia[k]$。我们发现 
$$\sum \limits_{k=l_i}^{r_i}a[k]=0 \Leftrightarrow sum[r_i] = sum[l_i - 1]$$
开一个 $map \ M$，对于每个 $i$，$M[j]$ 表示当前最大 $l < i$，使得 $\sum \limits_{k=1}^la[k]=j$。若 $M[sum[i]] \ne 0$ (即存在满足条件的的 $l$ )，则
$$\sum \limits_{k=M[sum[i]] + 1}^{i}a[k]=0$$
 更新 $maxl$，此时
$$maxl = max(maxl, M[sum[i]] + 1)$$
注意，若 $sum[i] = 0$ 且 $M[i] = 0$ 时，也要更新 $maxl$，
$$maxl = max(maxl, 1)$$
答案已经呼之欲出了：$f[i] = i - maxl$，只有
$$s_{maxl  + 1}\dots s_i, \dots,s_{i - 1}s_i, s_i$$
这些以 $i$ 结尾的子串合法。统计完后，还要更新 $M[sum[i]] = i$。

上面的规律，大家随便拿几组数据手玩一下就可以明白了。
 
然后，我们发现 $f$ 数组是没有必要的，只需在每次循环中统计答案即可。最后输出答案，就能愉快地通过这道题了。总时间复杂度是 $O(n \log n)$。

### $Code:$
```
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)

const int N = 200010;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

map<long long, int> M;

int n, nmax;

long long ans, sum;

int main() {
    n = read();
    Rep(i, 1, n) {
        int x = read();
        sum += x;
        if (M[sum]) nmax = max(nmax, M[sum] + 1);
        else if (!sum) nmax = max(nmax, 1);
        M[sum] = i, ans += i - nmax;
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：syksykCCC (赞：1)

我们记 $f_i$ 表示 **以 $i$ 结尾的合法段的个数**，显然，这题就是要我们求 $\sum_{i=1}^{n} f_i$。

我们考虑依次求出每一个 $f_i$。设想，我们这次要求的段的右端点显然都是 $i$，左端点可以是 $[1, i]$ 中的每一个值。那么哪些左端点是合法的呢？显然这是一个后缀，也就是说，如果左端点是 $p$ 的时候已经不合法了，那么左端点是 $q$（$q<p$）的时候显然是不合法的，因为后者包含了 **前者所包含的全部子段**。

那么我们只要求出最小的合法的位置 $p$，就知道 $f_i = i - p + 1$ 了（即 $[p, i]$ 中的位置的个数）。我们知道 $i$ 以前可能会有若干个和为 $0$ 的段，那么，$p$ 就是这些段的 **左端点的最大值 $\textbf{+1}$**，因为当 $p$ 小于等于这个左端点的最大值时，这个含有最大左端点的 $0$ 段就一定被完整包含了。

所以我们可以每次计算完 $i$ 的贡献后更新这个左端点的最大值。显然只要计算一遍前缀和（仍然存在 $a$ 中），那么如果有一个位置 $j$（$j < i$）满足 $a_j = a_i$，那么 $[j+1,i]$ 就是一个 $0$ 段。这里我们可以用 `map` 来存储一下上一次出现某个数的位置，记作 $lastpos_{a_i}$，那么 $[lastpos_{a_i} + 1, i]$ 就是一个 $0$ 段，左端点为 $lastpos_{a_i} + 1$。那么第 $i$ 个数考虑过后的 $p$，就是 $\max\{\text{old } p, (lastpos_{a_i}+1)+1\}$。

程序里面为了方便，存储的 `maxl` 其实就是 $p - 1$，那么更新答案应该改为 $i - (p - 1) = i - maxl$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], ans;
map<int, int> lastpos;
signed main()
{
	lastpos[0] = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] += a[i - 1];
	}
	for(int i = 1, maxl = 0; i <= n; i++)
	{
		if(lastpos.count(a[i])) maxl = max(maxl, lastpos[a[i]] + 1);
		ans += i - maxl;
		lastpos[a[i]] = i;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：2018LZY (赞：1)

[更好的效果](https://blog.csdn.net/qq_42886072/article/details/105407584)

考虑以每个位置结尾的合法开头位置.

设当前结尾为$i$,最前的合法开头为$j$.则有:

$s[(j-1)\sim i]$的数互不相同

设$mx=\max_{j=1}^i lastpos[s[j]]$.

则:$s[mx+1\sim i]$的数互不相同.

对应的最前的$j=mx+2$,对答案的贡献为$i-j+1=i-(mx+2)+1=i-mx-1$

直接用map暴力一发即可.
```cpp
int n,mx;
ll s[N],ans;
map<ll,int> h;

int main() {
	qr(n); mx=-1;//mx+2(1)是合法开头 
    h[0]=0;//初始化.
	for(int i=1;i<=n;i++) {
		qr(s[i]); s[i]+=s[i-1];
		if(h.count(s[i]))mx=max(mx,h[s[i]]);
		h[s[i]]=i; 
		ans+=i-mx-1;
	} pr2(ans);
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1333C](https://www.luogu.com.cn/problem/CF1333C)

[Eugene and an array](https://codeforces.com/contest/1333/problem/C)

### 思路

求一段区间 $i$ 到 $j$ 的 $sum$ 为 $0$，即求出前缀和 $sum[]$，$sum[j]-sum[i-1]=0$ ，即两处前缀和值相等。当对于 $l\le i < j\le r$，区间 $(l,r]$ 合法，则 $sum[i-1]\neq sum[j]$。

对 $sum[i]$ 记录 $lst_i$ 表示上一个与它相等的值，则以 $i$ 结尾的区间起点至多为 $lst_i+1$。又因为如果 $lst_i+1$ 至 $i$ 之间有一个坏区间，则 $lst_i+1$ 至 $i$ 也是坏区间。所以只能选 $\max \limits_{1\le x\le i}lst_x+1$ 至 $i$ 的区间。

用 map 记录。

对于每个 $i$，统计贡献。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int a[maxn],n,ans,lst,cnt,mx=-1,sum;
map <int,int> mp;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n;i++){
		sum+=a[i];
//		cout<<a[i]<<" "<<sum<<endl;
		if(mp[sum]){
			lst=mp[sum]-1;
		}
		else lst=-1;
		mp[sum]=i+1;
//		cout<<sum<<" "<<lst<<" "<<mp[sum]<<" ";
		mx=max(mx,lst);
		ans+=i-mx-1;
//		cout<<ans<<endl;
	}
	printf("%lld",ans);
}
```



---

## 作者：happybob (赞：0)

提供一种复杂度为 $O(n \log^2 n)$ 的做法。

考虑数据结构加二分。

如果我们指定某个区间的 $l$，那么你可以发现的是，区间是否存在连续子序列和为 $0$ 是单调性的，即如果 $r = x$ 时，有区间和为 $0$，那么对于 $r>x$，也一定有。

所以可以考虑枚举 $l$，二分 $r$。接下来考虑如何判定区间是否有和为 $0$。

可以将原序列做一次前缀和，那么如果一个区间内有和为 $0$，意味着区间内有一个数本身为 $0$，或者其前缀和中有两个或以上相同的数。判断是否有两个或以上相同的可以考虑莫队等数据结构维护，但是是离线的，而二分必须在线。考虑设 $sum_i = \sum \limits_{j=1}^i a_j$，即前缀和，设 $pre_i$ 为 $j_{\max}(sum_i=sum_j)$，询问区间 $l, r$，相当于询问区间的 $pre$ 的最大值。考虑 st 表预处理。询问是否有 $0$ 本身，即询问区间内某个数的出现次数，考虑 `vector` 上二分可以在线处理。

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

#define int long long

const int N = 2e5 + 5, M = 25;

int a[N], n, pre[N], p[N], LG2[N], s2[N];
vector<int> b;

map<int, vector<int> > pee;

void Init()
{
	LG2[1] = 0;
	LG2[2] = 1;
	for (int i = 3; i < N; i++)
	{
		LG2[i] = LG2[i / 2] + 1;
	}
}

int f[N][M];

inline int query(int l, int r)
{
	int x = LG2[r - l + 1];
	return max(f[l][x], f[r - (1LL << x) + 1][x]);
}

signed main()
{
	Init();
	scanf("%lld", &n);
	int ret = n * (n - 1) / 2 + n;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		if (a[i] == 0) ret--;
		a[i] += a[i - 1];
		s2[i] = a[i];
		b.push_back(a[i]);
		pee[a[i]].push_back(i);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
	for (int i = 1; i <= n; i++)
	{
		pre[i] = p[a[i]];
		p[a[i]] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = pre[i];
	}
	for (int j = 1; j < M; j++)
	{
		for (int i = 1; i + (1ll << j) - 1 <= n; i++)
		{
			f[i][j] = max(f[i][j - 1], f[i + (1ll << (j - 1))][j - 1]);
		}
	}
	for (int i = 1; i < n; i++)
	{
		int l = i, r = n + 1, place = -1;
		while (l + 1 < r)
		{
			int mid = l + r >> 1;
			int x = query(i, mid);
			if ((x >= i - 1 && x != 0) || upper_bound(pee[-s2[i - 1]].begin(), pee[-s2[i - 1]].end(), mid) - lower_bound(pee[-s2[i - 1]].begin(), pee[-s2[i - 1]].end(), i) >= 1) r = mid, place = mid;
			else l = mid;
		}
		//printf("%lld %lld %lld\n", i, place, query(i, place));
		if (place != -1) ret -= (n - place + 1);
	}
	printf("%lld\n", ret);
	return 0;
}
```


---

