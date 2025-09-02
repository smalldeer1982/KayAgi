# [ABC370F] Cake Division

## 题目描述

有一个圆形蛋糕，被切成了 $N$ 块，每一刀都是从圆心到圆弧上的某一点。

每一块蛋糕和每一道切口都按顺时针方向编号为 $1, 2, \ldots, N$，第 $i$ 块蛋糕的质量为 $A_i$。我们也把第 $1$ 块蛋糕称作第 $N+1$ 块。

第 $i$ 道切口位于第 $i$ 块和第 $i+1$ 块蛋糕之间，顺时针顺序为：第 $1$ 块蛋糕、切口 $1$、第 $2$ 块蛋糕、切口 $2$、……、第 $N$ 块蛋糕、切口 $N$。

现在要将这个蛋糕分给 $K$ 个人，分配需要满足以下条件。设第 $i$ 个人获得的蛋糕总质量为 $w_i$。

- 每个人都必须获得至少一块**连续的**蛋糕。
- 没有任何一块蛋糕会被遗漏。
- 在满足上述两个条件的前提下，使 $\min(w_1, w_2, \ldots, w_K)$ 的值最大。

请你求出满足条件的分法中，$\min(w_1, w_2, \ldots, w_K)$ 的最大值 $x$，以及在所有满足条件的分法中，切口没有被切开的切口数 $y$。这里，切口 $i$ 被切开是指第 $i$ 块和第 $i+1$ 块蛋糕被分给了不同的人。

## 说明/提示

### 限制条件

- $2 \leq K \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 10^4$
- 所有输入均为整数

### 样例解释 1

以下分法满足条件：
- 一个人获得第 $2, 3$ 块，另一个人获得第 $4, 5, 1$ 块。第 $2, 3$ 块的质量和为 $14$，第 $4, 5, 1$ 块的质量和为 $13$。
- 一个人获得第 $3, 4$ 块，另一个人获得第 $5, 1, 2$ 块。第 $3, 4$ 块的质量和为 $14$，第 $5, 1, 2$ 块的质量和为 $13$。
满足条件的分法中，$\min(w_1, w_2)$ 的最大值为 $13$，且无论哪种分法，只有切口 $5$ 没有被切开，因此答案为 $13\ 1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2
3 6 8 6 4```

### 输出

```
13 1```

## 样例 #2

### 输入

```
6 3
4 7 11 3 9 2```

### 输出

```
11 1```

## 样例 #3

### 输入

```
10 3
2 9 8 1 7 9 1 3 5 8```

### 输出

```
17 4```

# 题解

## 作者：lfxxx_ (赞：17)

- 前置芝士：倍增，二分。

## 题目描述
- 给出一个长度为 $N$ 的环，要求分成 $K$ 段，设第 $i$ 段的总和为 $S_i$，则求出 $\min(S_1,S_2,S_3,\cdots,S_K)$ 的最大值。

## 题目分析
- 拆环为链，使得长度为 $N$ 的环变成长度 $2\times N$ 的链 $A$。

- 明显，看到让最小值最大，自然想到二分，转化为判定性问题。

- 我们令 $f_{i,0}$ 为一个最小的 $j$，使得 $\sum_{k=i}^{j} \ge mid$，明显这个值可以用双指针算法得到。

- 我们再令 $f_{i,j}$ 为 $i$ 向后跳 $2^j$ 步能到达的地方的下一个位置，这样方便处理。

- 递推转移式子就脱颖而出，就是 $f_{i,j}=f_{f_{i,j-1},j-1}$。

- 然后将 $K$ 二进制分解，然后倍增就可以了，如果跳了 $K$ 步以后仍在 $i$ 开头的链中，则这个 $mid$ 可行。

- 若跳了 $K$ 步以后跳出去了，则这个点就没有被切割。

- 时间复杂度 $O(n \log^2n)$。

## 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,K,a[N],sum[N],dp[N][21],f[N];
void init(int mid)
{
	int j=0;
	for(int i=1;i<=n*2;++i)
	{
		while(j<n*2&&sum[j]-sum[i-1]<mid)
			++j;
		dp[i][0]=j+1;
	}
	dp[n*2+1][0]=n*2+1;
}
bool check(int mid)
{
	init(mid);
	for(int j=1;j<=20;++j)
		for(int i=1;i<=2*n+1;++i)
			dp[i][j]=dp[dp[i][j-1]][j-1];
	bool flag=0;
	for(int i=1;i<=n;++i)
	{
		int pos=i;
		for(int j=20;j>=0;--j)
			if(K&(1<<j))
				pos=dp[pos][j];
		f[i]=pos;
		if(pos<=i+n)
			flag=1;
	}
	return flag;
}
signed main()
{
	cin>>n>>K;
	for(int i=1;i<=n;++i)
		cin>>a[i],sum[i]=sum[i-1]+a[i];
	for(int i=n+1;i<=n*2;++i)
		a[i]=a[i-n],sum[i]=sum[i-1]+a[i];
	int l=0,r=2e9+1;
	while(l+1<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	check(l);
	int ans=0;
	for(int i=1;i<=n;++i)
		if(f[i]>i+n)
			++ans;
	cout<<l<<' '<<ans;
}
```

---

## 作者：incra (赞：7)

### Sol
难度不是很高的一题，不知道赛时为啥过的人这么少。

显然 $x$ 越小，$x$ 越有可能满足条件，所以考虑二分。

考虑如何 `check`，设要 `check` 的数为 $x$，那么考虑从一个起点 $s$ 开始，每次跳到下一个和大于等于 $x$ 的离 $x$ 最近的点，如果跳了 $k$ 次后跳的总距离不超过 $n$，那么就合法。

看到跳的字眼，不难想到倍增优化。

第一问就做完了，考虑求第二问。

显然从 $s$ 开始跳，那么 $s-1$ 这条分割线必然有，所以我们只需要在 `check` 里统计一下有多少个 $s$ 满足条件。

然后就做完了，代码实现和思路略有不同。
### Code
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
#define desktop "C:\\Users\\MPC\\Desktop\\"
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
#define endl '\n'
#define puts(s) cout << s << endl
const int N = 400010,MAX_LOG = 20;
int n,k;
int a[N];
LL s[N];
int f[N][MAX_LOG];
bool g[N];
bool check (int x) {
	for (int i = 1,j = 0;i <= 2 * n;i++) {
		while (s[i] - s[j + 1] >= x) j++;
		f[i][0] = j;
	}
	for (int j = 1;j < MAX_LOG;j++) {
		for (int i = 1;i <= 2 * n;i++) {
			if (!f[i][j - 1]) f[i][j] = 0;
			else f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	bool ans = false;
	for (int i = n + 1;i <= 2 * n;i++) {
		int p = i;
		for (int j = MAX_LOG - 1;j >= 0;j--) {
			if (k >> j & 1) p = f[p][j];
			if (!p) break;
		}
		g[i] = p >= i - n;
		ans |= g[i];
	}
	return ans;
}
int main () {
	cin >> n >> k;
	for (int i = 1;i <= n;i++) cin >> a[i],a[i + n] = a[i];
	for (int i = 1;i <= 2 * n;i++) s[i] = s[i - 1] + a[i];
	int l = 1,r = 2e9;
	while (l < r) {
		int mid = (LL)l + r + 1 >> 1;
		if (check (mid)) l = mid;
		else r = mid - 1;
	}
	check (l);
	int ans = n;
	for (int i = n + 1;i <= 2 * n;i++) ans -= g[i];
	cout << l << ' ' << ans << endl;
	return 0;
}
```

---

## 作者：rhn7 (赞：5)

赛时居然把二分边界开小了，痛失 575pts，写篇题解纪念一下。

看到最小值最大，肯定二分。关键是这题是个环，设有一段是 $[1,x]$ 和 $[y,n]$，枚举 $x$，求最小的 $y$ 使得 $[x+1,y-1]$ 能分成 $k-1$ 段，最后看 $[1,x]$ 与 $[y,n]$ 的和是否 $\ge mid$。

怎么求最小的 $y$ 呢？从 $x+1$ 开始，每次跳到以当前点为起点区间和 $\ge mid$ 的最小终点后面，跳 $k-1$ 次得到的位置就是 $y$。跳的过程用倍增实现。

第一问解决，第二问看起来有点麻烦，但我们发现如果一个点后面有分割，相当于把环变成链。如果 $x$ 后面有分割，$x$ 就不能走到 $x+1$，就变成了 $[x+1,n]$ 和 $[1,x]$

考虑把 $w$ 数组复制接在后面，这样 $i$ 后面有分割相当于 $[i+1,i+n]$ 能分成 $k$ 段每段都 $\ge ans$，用类似第一问的倍增跳即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=4e5+5;
ll n,k,a[N],f[N][20],ans2;
bool chk(ll x){
	memset(f,0,sizeof(f));
	for(ll i=1;i<=n;i++){
		ll l=i,r=n,t=-1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(a[mid]-a[i-1]>=x) t=mid,r=mid-1;
			else l=mid+1;
		}
		f[i][0]=t+1;
	}
	for(ll j=1;(1ll<<j)<k;j++){
		for(ll i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(ll i=1;i<=n;i++){
		ll p=i+1;
		for(ll j=19;j>=0;j--){
			if((k-1)&(1ll<<j)){
				p=f[p][j];
			}
		}
		if(p>i&&p<=n+1&&a[i]+a[n]-a[p-1]>=x) return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
	ll l=1,r=2e9,ans;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(chk(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<" ";
	memset(f,0,sizeof(f));
	for(ll i=1;i<=n;i++) a[i+n]=a[i]+a[n];
	for(ll i=1;i<=n*2;i++){
		ll l=i,r=n*2,t=-1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(a[mid]-a[i-1]>=ans) t=mid,r=mid-1;
			else l=mid+1;
		}
		f[i][0]=t+1;
	}
	for(ll j=1;(1ll<<j)<=k;j++){
		for(ll i=1;i<=n*2;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(ll i=1;i<=n;i++){
		ll p=i+1;
		for(ll j=19;j>=0;j--){
			if(k&(1ll<<j)){
				p=f[p][j];
			}
		}
		if(p>=i+1&&p<=i+n+1) ans2++; 
	}
	cout<<n-ans2;
    return 0;
}
```

---

## 作者：I_AK_IoI_2030 (赞：3)

提供一种 $O(n\log n)$ 的已通过的算法，欢迎 Hack。

## 一、题意
给出一个长为 $N$ 的**环**，要求分成 $K$ 段，设第 $i$ 段的总和为 $S_i$，求出 $\min \limits_{i=1}^{K} \{ S_i \}$ 的最大值。

## 二、分析与做法
心路历程：开始和其他题解想的一样，先倍长破环为链，再考虑跳等等，但是没有想到倍增。同时鉴于我定义的状态，我只好不再破环为链，但歪打正着地想到了如下做法。

题目要求最大的最小值，我比较自然地想到二分答案。check 时需要一点贪心：如果我们定下一段的终点，我们希望前面划分的段数尽量多，同时最开始可能会剩下一段无法单独成段的边角料，我们则希望它尽可能大，以便后期我们把后面的边角料跟它配起来能尽量再成为一段。

因此，我们定义：在已知每段的和最小为 $mid$ 的前提下，$f_i$ 为以 $i$ 号分割线为一段的终点线，前部所能划分的最多段数，$g_i$ 为达到 $f_i$ 时第一段可能的最右侧的起点线；$f_i'$，$g_i'$ 为后部的定义类似的两个量。如果我们最后求完所有的以上四个量，那么存在一种方案划分了 $i$ 号分割线当且仅当 $f_i+f_i'+[\sum \limits_{j=1}^{g_i} A_j+\sum \limits_{j=g_i'+1}^{N} A_j \geq mid] \geq K$，$mid$ 合法当且仅当存在一个分割线可能被划分。

下面考虑如何求得以上四个量，以前两个为例。我们可以用双指针维护最后一个 $l$ 满足 $l$ 和 $i$ 两个分割线间可以成为合法的一段。考虑到 $l$ 变大，要么 $f_l$ 变大，要么 $g_l$ 不降，所以是不劣的。所以**如果** $\sum \limits_{j=l+1}^{i} A_i \geq mid$，则 $f_i=f_l+1,g_i=g_l$；否则（此时一定有 $l=0$）$f_i=0,g_i=i$。

于是我们可以二分 $mid$，时间复杂度 $O(n\log n)$。

## 三、代码

如下，一些细节记在注释里了。

```cpp
#include<iostream>
using namespace std;
const int N=2e5+10;
int n,k,a[N],vis[N],ans;
long long qzh[N],f[N],g[N],f2[N],g2[N];//以切割线为准 
int check(long long x){
	int l=0,flag=0;
	for(int i=1;i<=n;i++){
		while(qzh[i]-qzh[l+1]>=x) l++;
		if(qzh[i]<x) f[i]=0,g[i]=i;
		else f[i]=f[l]+1,g[i]=g[l];
	}l=n;
	for(int i=n;i;i--){
		while(qzh[l-1]-qzh[i]>=x) l--;
		if(qzh[n]-qzh[i]<x) f2[i]=0,g2[i]=i;
		else f2[i]=f2[l]+1,g2[i]=g2[l];
	}
	for(int i=1;i<=n;i++){
		if(f[i]+f2[i]>=k) vis[i]=1,flag=1;
		else if(f[i]+f2[i]==k-1){
			if(qzh[g[i]]+qzh[n]-qzh[g2[i]]>=x) vis[i]=1,flag=1;
			else vis[i]=0;
		}
		else vis[i]=0;
	}return flag;
}
int main(){
	cin>>n>>k;ans=n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),qzh[i]=qzh[i-1]+a[i];
	long long l=1,r=2e9+10,mid;
	while(l<r){
		mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}check(l);//!!! l 有可能不等于最后的 mid
	for(int i=1;i<=n;i++) ans-=vis[i];
	printf("%d %d",l,ans);
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# 题目翻译

你有一个圆形的蛋糕，被分成了 $n$ 块，每一块都有美味程度 $a_i$。第 $i$ 条分割线位于第 $i$ 块和第 $i+1$ 块之间。

你需要选择 $k$ 条分割线分出 $k$ 段交给 $k$ 个人，满足每个人都收到了一段连续的蛋糕块，且不存在有块没有交给任何人。

你需要解决两问。设 $w_i$ 表示第 $i$ 个人得到的连续的蛋糕块的美味程度。第一问需要求出 $\min\{w_1,w_2,\dots,w_k\}$ 的最大值。第二问需要求出，在满足 $\min\{w_1,w_2,\dots,w_k\}$ 最大的所有可能划分方案中，有多少分割线从没被使用过。

$2 \leq k \leq n \leq 2 \times 10^5$，$1 \leq a_i \leq 10^4$。

# 题目思路

先破环成链两条链拼一起。

最大化最小值可以考虑二分答案。设二分需要 check 的是 $mid$，我们就是问能不能凑出 $\geq k$ 段满足每段和都 $\geq mid$。

我们先处理 $nxt_i$ 表示从 $i$ 开始在 $nxt_i-1$ 的位置结尾，也就是 $[i,nxt_i)$ 的区间和 $\geq mid$。如果不存在这样的 $nxt_i$ 就把 $nxt_i$ 设为极大值。

之后我们就是要判断跳 $k$ 次 $nxt_i$ 是否会跳到边界外。这里认为边界是 $i+n$。

直接暴力跳肯定不行，考虑倍增优化跳的过程。设 $nxt_{i,j}$ 表示 $i$ 开始往后跳 $2^j$ 步到了哪里。倍增转移显然。

之后我们枚举开头的 $i$，倍增跳至多跳 $\log n$ 次，这样单次 check 复杂度降为了 $\mathcal O(n\log n)$。加上二分是 $\mathcal O(n\log^2 n)$。

第一问做完了，考虑第二问。我们发现这个有 $i$ 的分割线就代表从 $i$ 开始跳是合法的。我们重复上面判定『跳 $k$ 次 $nxt_i$ 是否会跳到边界外』的过程，如果有一个没跳出的就说明在 $i$ 位置可以成为分割线。

找出所有可能成为分割线的位置用 $n$ 减掉这个个数即可。

# 完整代码

[AT submission 57561975](https://atcoder.jp/contests/abc370/submissions/57561975)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
int n, k;
ll s[400020];
ll a[400020];
int nxt[20][400020];
ll S(int l, int r) { return l > r ? 0 : s[r] - s[l - 1]; }
int check(ll mid)
{
    memset(nxt, 0x3f, sizeof(nxt));
    int l = 1, r = 0;
    while (l <= 2 * n)
    {
        if (r < l)
            r = l;
        while (r + 1 <= 2 * n && S(l, r) < mid)
            r++;
        if (S(l, r) >= mid)
            nxt[0][l] = r + 1;
        l++;
    }
    // if (mid > 20)
    //     return 0;
    // cout << mid << endl;
    // for (int i = 1; i <= 2 * n; i++)
    //     cout << nxt[0][i] << " ";
    // cout << endl;
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= 2 * n; i++)
            nxt[j][i] = nxt[j - 1][i] == inf ? inf : nxt[j - 1][nxt[j - 1][i]];
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        int p = i;
        for (int j = 19; j >= 0; j--)
        {
            if (nxt[j][p] <= i + n)
                p = nxt[j][p], cnt |= 1 << j;
        }
        if (cnt >= k)
            ret++;
    }
    return ret;
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++)
        s[i] = s[i - 1] + a[i];
    ll L = 0, R = 4e9, ans = 0;
    while (L <= R)
    {
        ll mid = L + R >> 1;
        if (check(mid))
            L = (ans = mid) + 1;
        else
            R = mid - 1;
    }
    cout << ans << " " << n - check(ans) << endl;
    return 0;
}
```

---

## 作者：Kingna (赞：2)

**题意：** 环形数列分段，要求最小值最大。

**思路：**

考虑二分 $x$，因为是环状，则需要找到一个起始点。从这个起始点开始分段，若当前一个人的总和大于等于 $x$，就给新一个人分。若 $K$ 个人都分配完蛋糕，且还有数字剩余，意味着二分的值可以增加。复杂度 $O(n^2\log V)$。

此算法瓶颈在于：对于每一个起始点，不能快速算出分配 $K$ 个人后是否还有剩余。为了方便，将数组破环成链，即 $a_{i+n}=a_i$。定义 $f_{i,j}$ 数组表示，从第 $i$ 个位置开始，分配 $j$ 个人后到达的位置。

$f_{i,0}$ 即定义为最小的 $j\leq 2\times n +1$ 使得 $a_i+a_{i+1}+\dots + a_{j-1}\geq x$，即分配后的下一个位置。若不存在这样的 $j$，将 $f_{i,0}$ 设置为正无穷。

使用基于 $f_{i,2},f_{i,4},f_{i,8}$ 的倍增技巧，很容易求出 $f_{i,K}$。现在枚举起始点 $i$，若 $f_{i,K}\leq i+n$，就代表可以分配。

如何判断哪些分段点从未被使用过？$f_{i,K}\leq i+n$ 可以第 $i$ 个位置使用过，但是后面的分割位置无法被统计。但事实上是：从后面的分割位置开始分，也可以分割成功，因为这是一个环状。所以直接看 $f_{i,K}\leq i+n$ 的数量有多少个即可。

**代码：**

```cpp
int n, m, a[N], sum[N], f[N][23], dis[N][23], res;

int check(int md) {
	_for(i, 1, n) _for(j, 0, 21) f[i][j] = dis[i][j] = 0;
	if (sum[n] < md) return 0;
	_for(i, 1, 2 * n) {
		int l = i, r = 2 * n;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (sum[mid] - sum[i - 1] >= md) r = mid;
			else l = mid + 1;
		}
		if (sum[l] - sum[i - 1] >= md) f[i][0] = l + 1; 
		else f[i][0] = 2 * n + 2;
	}
	_for(j, 0, 21) f[2 * n + 1][j] = 2 * n + 1;
	_for(j, 0, 21) f[2 * n + 2][j] = 2 * n + 2;
	_for(j, 1, 21) {
		_for(i, 1, 2 * n + 2) f[i][j] = f[f[i][j - 1]][j - 1];
	}
	res = 0;
	_for(i, 1, n) {
		int t = i;
		_pfor(j, 21, 0) if (m >> j & 1) t = f[t][j];
		if (t <= i + n) res++;
	}
	return res != 0;
}

signed main() {
	cin >> n >> m;
	int l = 2e18, r = 2e18;
	_for(i, 1, n) cin >> a[i], a[i + n] = a[i], l = min(l, a[i]);
	_for(i, 1, 2 * n) sum[i] = sum[i - 1] + a[i];
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	res = 0;
	check(l);
	cout << l << ' ' << n - res << endl;
}
```

---

## 作者：Zhaohongrui (赞：2)

如果这题只需要求 $x$ 要怎么做？

我们可以二分答案 $x$，并判断是否可行。

由于蛋糕是环形的，我们需要破环成链，并对于 $\forall i,1\le i\le n$，判断 $a_{i\dots i+n-1}$ 是否能分割成 $k$ 段，使每一段的和都 $\ge x$。

时间复杂度 $O(n^2\log\sum a)$，无法通过本题。

考虑优化，设 $nxt_{i,1}$ 为使 $\sum_{j=i}^{k-1} a_j\ge x$ 的最小 $k$，$nxt_{i,j}=nxt_{nxt_{i,j-1},1}$，则原问题转化为 $\exists i, 1\le i\le n$，使 $nxt_{i, k}\le n+k$。

可以通过倍增将时间复杂度优化到 $O(n \log n\log \sum a)$，可以通过本题。

但我们需要求出 $y$，通过观察发现，分割线 $i$ 从未被分割当且仅当 $nxt_{i,k}>n+i$

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5, maxn = 2e9, M = 17;
int n, k;
LL a[(N << 1) + 5];
int nxt[M + 1][(N << 1) + 5];
bool check(int mid) {
	for (int i = 1, j = 1; i <= n << 1; i++) {
		while (j < n << 1 && a[j] - a[i - 1] < mid) j++;
		nxt[0][i] = j + 1;
	}
	nxt[0][n << 1 | 1] = n << 1 | 1;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= (n << 1 | 1); j++)
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
	for (int i = 1; i <= n; i++) {
		int now = i;
		for (int j = M; j >= 0; j--)
			if (k >> j & 1) now = nxt[j][now];
		if (now <= n + i) return true;
	}
	return false;
}
int binary() {
	int l = 1, r = maxn;
	while (l < r) {
		int mid = (LL)l + r + 1 >> 1;
		check(mid) ? l = mid : r = mid - 1;
	}
	return l;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		a[n + i] = a[i];
	}
	for (int i = 1; i <= n << 1; i++)
		a[i] += a[i - 1];
	int ans = binary();
	printf("%d ", ans);
	for (int i = 1, j = 1; i <= n << 1; i++) {
		while (j < n << 1 && a[j] - a[i - 1] < ans) j++;
		nxt[0][i] = j + 1;
	}
	nxt[0][n << 1 | 1] = n << 1 | 1;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= (n << 1 | 1); j++)
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
	ans = 0;
	for (int i = 1; i <= n; i++) {
		int now = i;
		for (int j = M; j >= 0; j--)
			if (k >> j & 1) now = nxt[j][now];
		ans += now > n + i;
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：gutongxing2030 (赞：1)

## F - Cake Division

### 思路

首先，对于这个问题，一看就知道要使用**二分答案**来解决。

于是我们就将问题转换成将蛋糕分给 $k$ 个人，使得每个人都能至少得到权值为 $w$ 的方案是否可行。如果可以，那么那些边一定不能删。

我们先来看是否可行的问题。

首先我们可以先破环为链，预处理出来从第 $i(i\in[1,n])$ 个蛋糕开始满足 $sum(i,j)\ge w$ 的最小值，记录为 $f(i)$，如果不存在，就是 $f(i)=\infty$。我们枚举第一个人先拿的是那一块蛋糕，那么我们一定会给他分配到第 $f(i)$ 块蛋糕，接着第二个人就从 $f(i)+1$ 开始拿蛋糕，一直到 $f(f(i)+1)$ 块蛋糕，可以证明这个定是分配时最优秀的情况。只要有一个 $i$ 满足要求，那么这个 $w$ 就是可行的。

但是暴力这样的时间复杂度是 $O(n^2\log_2 n+nk\log_2 n)$ 的，会超时。

于是我们可以试着给 $i$ 和 $f(i)+1$ 连一条有向边，那么求得就是 $i$ 向前走的第 $k-1$ 个父亲。这个可以使用倍增解决。

而关于怎么求 $f(i)$，直接使用双指针求就行，这样时间复杂度被我们降为了 $O(n\log^2_2 n)$ 的，非常理想。

所以我们就已经知道了最大的 $w$，已经解决了第一问。

对于最大的 $w$，我们已经知道 $w$ 对于那个（些）$i$ 是满足限制的。我们可以对 $i$ 打一个标记，于是问题变成了在一个 DAG 里面，有一些点上面有标记，标记会顺着边一路往前，求有那些点没有被打过标记。

这个问题很经典，就是一个拓扑序 DP。实际上我们只关心 $i$ 的下一个是谁，这样就可以递推进行了。

我的思路很复杂，代码可能有一点难写。

### 代码

```cpp
// Problem: F - Cake Division
// Contest: AtCoder - Toyota Programming Contest 2024#9（AtCoder Beginner Contest 370）
// URL: https://atcoder.jp/contests/abc370/tasks/abc370_f
// Memory Limit: 1024 MB
// Time Limit: 5000 ms

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
#pragma GCC optimize(2)
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
	const int MAXN = 4e5+10;
	const int LOGN = log2(MAXN)+2;
	const int INF = 0x3f3f3f3f;
	int n,k;
	int fath[MAXN][LOGN],sum[MAXN];
	bitset<MAXN> b;
	int get(int x,int w){
		int k = 0;
		while(w){
			if(w&1){
				if(x!=INF) x = fath[x][k];
			}
			w>>=1;
			k++;
		}
		return x;
	}
	bool check(int w){
		for(int i = 1;i<=2*n+5;i++) for(int j = 0;j<LOGN;j++) fath[i][j] = INF;
		int end=1;
		for(int i = 1;i<=2*n;i++){
			while(end<=2*n&&(sum[end]-sum[i-1])<w) end++;
			end = min(end,2*n);
			if((sum[end]-sum[i-1])<w) fath[i][0] = INF;
			else fath[i][0] = end+1;
		}
		for(int j = 1;j<LOGN;j++){
			for(int i = 1;i<=2*n;i++){
				fath[i][j] = (fath[i][j-1]==INF)?INF:fath[fath[i][j-1]][j-1];
			}
		}
		for(int j = 1;j<=n;j++){
			if(get(j,k)-1<j+n) return true;
		}
		return false;
	}
	signed main(){
		read(n);read(k);
		int p = 0;
		for(int i = 1;i<=n;i++){
			read(sum[i]);
			sum[i+n] = sum[i];
			p+=sum[i];
		}
		for(int i = 1;i<=2*n;i++) sum[i]+=sum[i-1];
		int l = 0,r = p/k,ans = 0;
		while(l<=r){
			int mid = (l+r)>>1;
			if(check(mid)){
				l = mid+1;
				ans = mid;
			}else r= mid-1;
		}
		write(ans,' ');
		for(int i = 1;i<=2*n+5;i++) for(int j = 0;j<LOGN;j++) fath[i][j] = INF;
		int end=1;
		
		for(int i = 1;i<=2*n;i++){
			while(end<=2*n&&(sum[end]-sum[i-1])<ans) end++;
			end = min(end,2*n);
			if((sum[end]-sum[i-1])<ans) fath[i][0] = INF;
			else fath[i][0] = end+1;
		}
		for(int j = 1;j<LOGN;j++){
			for(int i = 1;i<=2*n;i++){
				fath[i][j] = (fath[i][j-1]==INF)?INF:fath[fath[i][j-1]][j-1];
			}
		}
		for(int j = 1;j<=n;j++){
			if(get(j,k)-1<j+n){
				b.set(j);
			}
		}
		for(int j = 1;j<=2*n;j++){
			if(b[j]&&fath[j][0]!=INF) b[(fath[j][0]>n)?fath[j][0]-n:fath[j][0]]=1;
		}
		write(n-(int)b.count());
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

题意：$n$ 个数 $a_i$ 排成一个环，你要将环分为恰好 $k$ 段，使得每一段的 $a_i$ 之和中的最小值最大，并输出有多少个分割点不可能作为前者最大时的任何一种情况的分割点。$1 \le k \le n \le 2\times 10^5$。

场上给我整不会了，还是比较神奇的。

显然要套一层二分。现在问题变为是否可以使环被分为至少 $k$ 段使得每一段的 $a_i$ 之和都不小于 $mid$。

首先做一点因为没对上电波导致的冗余思考。发现主要恶心的点在于环和第二问。

环的话肯定要在某个地方把它掰开成链然后想办法快速维护，然而这第二问在链上反而更抽象了，令人升华。但是如果把第二问放到环上考虑，那你会发现它就等价于：求有多少个分割点使得如果把环在这个分割点上劈开变成一条链，不存在合法解。换句话说就是破环为链之后有多少个 $a_i$ 不可能作为起点。感觉瞬间就好维护了！

所以我们需要维护每个起点是否合法，考虑令 $f_{i,j}$ 表示 $a_i$ 作为起点，要从这里开始分 $j$ 段使得每一段的 $a_i$ 之和都不小于 $mid$，长度之和最短是多少。我们需要知道所有的 $f_{i,k}$。$f_{i,1}$ 可以双指针得到，但还是会剩下一个 $O(nk)$ 的转移。你发现这东西本质上是个置换，或者是让你想起了倍增的定义，总之就是它有非常好的可合成性。所以可以用类似快速幂的方式同时求解所有的 $f_{i,k}$ 砍成 $\log$。

最后看看有几个分割点满足 $f_{i,k}>n$ 即可。总复杂度 $O(n\log^2)$。

```cpp
ll n,k,a[N];
struct dp {
	ll a[N];
	dp() { memset(a,0,sizeof(a)); }
	friend dp operator * (dp x,dp y) {
		for (ll i=0;i<n;i++) x.a[i]+=y.a[(i+x.a[i])%n];
		return x;
	}
	friend dp operator ^ (dp x,ll y) {
		dp ret;
		while (y) { if (y&1) ret=ret*x; x=x*x,y>>=1; }
		return ret;
	}
} b;
bool chk(ll mid,ll as) {
	for (ll i=0,sum=0,j=0;i<n;i++) {
		while (sum<mid) sum+=a[(i+j)%n],j++;
		b.a[i]=j,sum-=a[i],j--;
	}
	b=b^k;
	ll sum=0;
	for (ll i=0;i<n;i++) sum+=b.a[i]>n;
	if (as) cout<<mid<<" "<<sum;
	return sum<n;
}
void mian() {
	scanf("%lld%lld",&n,&k);
	for (ll i=0;i<n;i++) scanf("%lld",&a[i]);
	ll l=1,r=accumulate(a,a+n,0ll),mid,res=0;
	while (l<=r) {
		mid=l+r>>1;
		if (chk(mid,0)) l=mid+1,res=mid;
		else r=mid-1;
	}
	chk(res,1);
}
```

---

## 作者：1234567890sjx (赞：1)

**节选自 [场上过不去的简单题 - $\bf{I}$](https://www.cnblogs.com/yhbqwq/p/18404602)** 。

首先套路的破换成链，然后二分答案 $p$。

对于每一个二分的答案 $p$，考虑先二分出 $f_{i,0}$ 表示 $i$ 之后第一个满足 $\sum\limits_{j=i}^{f_{i,0}} a_j\ge p$ 的 $f_{i,0}$，然后倍增的设 $f_{i,j}$ 表示 $i$ 之后满足 $2^j$ 次上述条件的下标为 $f_{i,j}$。特殊的若不可以满足则令 $f_{i,j}=-1$。

然后考虑枚举起点，直接暴力倍增计算出 $k$ 次操作之后的答案即可。时间复杂度为 $O(n\log^2n)$。代码有点混乱。

```cpp
const int N=400100,mod=998244353;
int a[N],s[N],n,k,now,nxt[N][20],res;
bool chk(int p){
    memset(nxt,-1,sizeof nxt);
    F(i,1,n+n){
        int l=i,r=i+n-1,best=-2;
        r=min(r,n+n);
        while(l<=r){
            int mid=l+r>>1;
            if(s[mid]-s[i-1]>=p)best=mid,r=mid-1;
            else l=mid+1;
        }
        nxt[i][0]=best+1;
    }
    nxt[n+n+1][0]=n+n+1;
    F(i,1,19)
        F(j,1,n+n+1)
            if(~nxt[j][i-1])
                nxt[j][i]=nxt[nxt[j][i-1]][i-1];
    // F(i,1,n+n)
    //     cout<<i<<": "<<nxt[i][0]<<' '<<nxt[i][1]<<" qwq\n";
    int cnt=0;
    F(i,1,n){
        int x=i;
        G(j,19,0)
            if(k>>j&1){
                x=nxt[x][j];
                if(x==-1||x>i+n)break;
            }
        if(x!=-1&&x<=i+n)
            ++cnt;
    }
    if(cnt)
        res=n-cnt;
    return !!cnt;
}
signed main(){
    cin>>n>>k;
    F(i,1,n)cin>>a[i],s[i]=s[i-1]+a[i];
    F(i,1,n)a[i+n]=a[i],s[i+n]=s[i+n-1]+a[i];
    int l=1,r=s[n],best=-1;
    while(l<=r){
        int mid=l+r>>1;
        if(chk(mid))best=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<best<<' '<<res<<'\n';
}

```

---

## 作者：Gordon_Song (赞：1)

运用解决环问题的一个基本思路——断环为链。然后问题转化成了在链上有多少个节点满足 $1 \leq i \leq n$，且 $i+1$ 到 $i+n$ 划分出来的段和的最小值最大。先考虑求一个询问 $x$ 的时候如何处理。很明显可以跑二分。

然而，在这题中，对于每个断点都跑一次这样的二分是无法通过的。然而，我们好像并没有二分以外的做法。所以，要使用整体二分的思想。

具体而言对于当前锁定的答案区间 $l,r$，对于每个询问考虑从后往前跳，每次找到最近的一个满足当前段和大于等于 $mid$ 的位置，并调到那个位置上。如果一个位置 $i+n$ 跳 $k$ 次后仍然位于 $[i+1,i+n]$ 这个区间上，那么 $i$ 的答案就大于 $mid$。每次对于当前的可能贡献最优解的位置集合都判断一次，如果有答案大于 $mid$ 的位置就往大的递归，否则往小的递归。

乍一看这个过程似乎还是很暴力，但实际上这是一个容易优化的问题。每次二分时，预处理出每个位置的最近的一个位置使得这一段的和大于等于 $mid$，将这个最近的位置设置为父节点。然后用倍增预处理，那么查询时就可以做到 $\log_2 k$。

所以，总复杂度是 $O(n \log V \log n)$

[代码](https://atcoder.jp/contests/abc370/submissions/57549025)

---

