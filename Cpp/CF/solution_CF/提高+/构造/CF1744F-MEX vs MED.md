# MEX vs MED

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ of length $ n $ of numbers $ 0, \ldots, n - 1 $ . Count the number of subsegments $ 1 \leq l \leq r \leq n $ of this permutation such that $ mex(p_l, p_{l+1}, \ldots, p_r) > med(p_l, p_{l+1}, \ldots, p_r) $ .

 $ mex $ of $ S $ is the smallest non-negative integer that does not occur in $ S $ . For example:

- $ mex({0, 1, 2, 3}) = 4 $
- $ mex({0, 4, 1, 3}) = 2 $
- $ mex({5, 4, 0, 1, 2}) = 3 $

 $ med $ of the set $ S $ is the median of the set, i.e. the element that, after sorting the elements in non-decreasing order, will be at position number $ \left \lfloor{ \frac{|S| + 1}{2} } \right \rfloor $ (array elements are numbered starting from $ 1 $ and here $ \left \lfloor{v} \right \rfloor $ denotes rounding $ v $ down.). For example:

- $ med({0, 1, 2, 3}) = 1 $
- $ med({0, 4, 1, 3}) = 1 $
- $ med({5, 4, 0, 1, 2}) = 2 $

A sequence of $ n $ numbers is called a permutation if it contains all the numbers from $ 0 $ to $ n - 1 $ exactly once.

## 说明/提示

The first test case contains exactly one subsegment and $ mex({0}) = 1 > med({0}) = 0 $ on it.

In the third test case, on the following subsegments: $ [1, 0] $ , $ [0] $ , $ [1, 0, 2] $ and $ [0, 2] $ , $ mex $ is greater than $ med $ .

In the fourth test case, on the following subsegments: $ [0, 2] $ , $ [0] $ , $ [0, 2, 1] $ and $ [0, 2, 1, 3] $ , $ mex $ greater than $ med $ .

## 样例 #1

### 输入

```
8
1
0
2
1 0
3
1 0 2
4
0 2 1 3
5
3 1 0 2 4
6
2 0 4 1 3 5
8
3 7 2 6 0 1 5 4
4
2 0 1 3```

### 输出

```
1
2
4
4
8
8
15
6```

# 题解

## 作者：Allanljx (赞：11)

## 思路
假设当前的 mex 值是 $i$ 那么区间一定包含 $0\sim i-1$，同时区间长度小于等于 $i\times 2$。我们对于每个 mex 值为 $i$ 都仅考虑包含它的长度为 $i\times 2$ 和长度为 $i\times 2-1$ 的区间的个数，因为长度为 $i\times 2-2$ 的区间一定在 mex 值为 $i-1$ 时统计过。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int a[200005],to[200005];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			to[a[i]]=i;
		}
		int l=INT_MAX,r=0;
		for(int i=0;i<n;i++)
		{
			l=min(l,to[i]),r=max(r,to[i]);
			int len=i*2+2;//长度为i*2的区间
			int l1,r1;
			if(r-l+1>len) continue;
			l1=max(1ll,r-len+1),r1=min(l,n-len+1);
			ans+=max(0ll,(r1-l1+1));
			len--;//长度为i*2-1的区间
			if(r-l+1>len) continue;
			l1=max(1ll,r-len+1),r1=min(l,n-len+1);
			ans+=max(0ll,(r1-l1+1));
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：OrezTsim (赞：10)

看到 $\text{mex}>\text{med}$，想到一定满足 $[0,\text{med}]$ 都在区间内出现过。

那么考虑枚举 $\text{med}$，对于每一个 $\text{med}$ 计算答案。

每次加入一个新元素，如果它原本不在区间内，就把左端点 / 右端点设为它。

考虑 $\text{med}$ 的定义，分两种情况。

1. 区间内比它小的有 $x$ 个，比它大的也有 $x$ 个。

因为按照我们的做法，$[0,\text{med}-1]$ 此时都被包含在区间内，即 $x$ 确定。我们只需要枚举左侧放多少个比它大的，然后判断右侧是否放得下就可以了。实际上它是一个不等式，解一下就好了。

假设当前区间为 $[l,r]$。

那么左侧最多放 $l-1$ 个，右侧最多放 $n-r$ 个，总共还需要放 $\text{med}-p$ 个。

此处 $p$ 表示 $[l,r]$ 内 $>\text{med}$ 的数。

解不等式即可。

2. 区间内比它小的有 $x$ 个，比它大的也有 $x+1$ 个。

同理。

~~因为数组开小了，吃了一发罚时。~~

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
int t, n, a[N], pos[N];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> t; while (t--) {
        cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i], pos[a[i]] = i;
        int res = 1, cnt = 0; int l = pos[0], r = pos[0];
        if (l > 1) ++res; if (r < n) ++res;
        for (int i = 1; i < n; ++i) {
            int cur = pos[i];
            if (cur < l) {
                for (int j = l - 1; j >= cur; --j)
                    if (a[j] > i) ++cnt;
                l = cur;
            } else if (cur > r) {
                for (int j = r + 1; j <= cur; ++j)
                    if (a[j] > i) ++cnt;
                r = cur;
            } else --cnt;
            int Min = r - l - cnt, Max = cnt;
            int sum = Min; sum -= Max;
            int lef = max(0ll, sum - n + r), rig = min(l - 1, sum);
            res += max(rig - lef + 1, 0ll);
            sum = Min + 1; sum -= Max;
            lef = max(0ll, sum - n + r), rig = min(l - 1, sum);
            res += max(rig - lef + 1, 0ll);
        }
        cout << res << endl;
    }
    return 0;
}
```

---

## 作者：y_kx_b (赞：6)

### 原题意：
给定一个从 $0$ 到 $n-1$ 的排列 $p$，求有多少个区间 $[l,r]$ 满足 $\operatorname{mex}(p_l,p_{l+1},\dots,p_r)>\operatorname{med}(p_l,p_{l+1},\dots,p_r)$。

其中 $\operatorname{mex}(S)$ 为没有在 $S$ 中出现的最小非负整数；$\operatorname{med}(S)$ 为 $S$ 从小到大排序后 $S_{\left\lfloor\frac{\vert S\vert-1}2\right\rfloor}$ 的值（下标从 $0$ 开始）。

$\sum n\leqslant 2\times10^5$。

---
设 $w=\operatorname{med}(p_l,p_{l+1},\dots,p_r)$，因为我们想让 $\operatorname{mex}$ 比 $w$ 大，所以我们希望这个序列包含 $\left[0,w\right]$ 这样 $\operatorname{mex}\geqslant w+1$ 达到了我们的目标。因为 $w\geqslant\left\lfloor\dfrac{r-l}2\right\rfloor$（由 $\operatorname{med}$ 定义以及“排列中的数互不相同”，显然），所以 $\{p_l,p_{l+1},\dots,p_r\}\supseteq[0,w]\supseteq\left[0,\left\lfloor\dfrac{r-l}2\right\rfloor\right]$，所以 $w\geqslant\left\lfloor\dfrac{r-l}2\right\rfloor$ 必然取等。那么有

### 转化题意：
给定一个从 $0$ 到 $n-1$ 的排列 $p$，求有多少个区间 $[l,r]$ 满足 $\left[0,\left\lfloor\dfrac{r-l}2\right\rfloor\right]\subseteq\{p_l,p_{l+1},\dots,p_r\}$。

因为原 $p$ 是排列，所以每个数只会出现一次。所以我们知道 $\left[0,\left\lfloor\dfrac{r-l}2\right\rfloor\right]$ 里面的所有数的位置，也就知道了能包含它们的最短区间。枚举长度 $len$ 从 $1$ 到 $n$，如果 $len$ 为奇数那么对上次的最短区间 $[l,r]$ 进行扩充（即设 $t=S_{\left\lfloor\frac{r-l}2\right\rfloor},tpos$ 为 $t$ 在 $p$ 中的位置（下标）则扩充操作为对用 $tpos$ 对 $l$ 取 $\min$，对 $r$ 取 $\max$），原因显然，一次操作复杂度 $O(1)$。

然后对于每个区间长度 $len$ 我们知道了最短区间为 $[l,r]$，我们需要统计 $[ql,qr]$ 的数量使其满足 $[l,r]\subseteq [ql,qr]\subseteq [1,n]$ 且 $qr-ql+1=len$，那么易得 $qr\geqslant\max\{r,len-1\}(ql=qr-len+1\geqslant0)$，$ql\leqslant\min\{l,n-len\}(qr=ql+len-1\leqslant n-1)$，那么这个区间实际可移动的范围只有 $len-(\max\{r,len-1\}-\min\{l,n-len\}+1)+1=len-\max\{r,len-1\}+\min\{l,n-len\}$。
$$
|------------------------|\\
0\kern{220pt}n-1\\
|------\kern{3 .4pt}-----|\\
l\kern{114pt}r\\
|-------------------|\\
ql\kern{187pt}qr
$$
最后要注意有可能 $\max\{r,len-1\}-\min\{l,n-len\}+1$ 可能超过 $len$（因为给的限制太多了），所以答案要对 $0$ 取 $\max$（防止出现负数贡献）。
```cpp
int arcp[N];
bool major(){
	n=read();
	for(int i=0;i<n;i++)arcp[read()]=i;
	int l=arcp[0],r=l;
	ll ans=0;
	for(int i=0;i<n;i++){//calc len = 2i+1 or 2i+2 ans
		l=min(l,arcp[i]),r=max(r,arcp[i]);
		int len=i*2+1;
		lbw:ans+=max(0,len-max(r,len-1)+min(l,n-len));
		if(len==n)break;
		len++;
		if(!(len&1))goto lbw;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_HCl_ (赞：3)

非常好玩的一个双指针题。

# CF1744F 题解

**题意简述**

给定一个 $[0,n-1]$ 的全排列 $p$，求有多少个区间 $[l,r]$ 满足 $mex(p_l,p_{l+1},\dots,p_r)>med(p_l,p_{l+1},\dots,p_r)$。

其中 $mex(S)$ 是 $S$ 中未出现的第一个非负整数，$med(S)$ 是 $S$ 的中位数。

**思路引导**

不难想到，为了使 $mex(S)>med(S)$（下文中用 $mex$ 和 $med$ 简述），必须要保证 $[0,med]$ 中的数都要被包含在 $S$ 中。

同时，为了保证 $med$ 是 $S$ 的中位数，$S$ 的长度 $|S|$ 满足 $|S|=2\cdot med+1$ 或者 $|S|=2\cdot med+2$。

这是因为此时已经有 $med$ 个数比 $med$ 小，那我们就需要 $med$ 或 $med+1$ 个数比 $med$ 大，因此最终的 $|S|$ 为 $2\cdot med+1$ 或 $2\cdot med+2$。

再来考虑如何取出这个区间。我们可以枚举 $med$，然后使用双指针来找到满足 $[0,med]\in T$ 的最小区间 $T$。具体做法是：如果当前的数不在当前的区间内，就将区间扩展到那个数的位置。

因为 $[0,med]$ 已经被包含在的这个最小区间 $T$ 内了，所以在 $T$ 外的数都是比 $med$ 大的。因此我们只需要取出 $|S|=2\cdot med+1$ 或 $|S|=2\cdot med+2$，并且包含了 $T$ 的所有 $S$ 即可。

由于只需要统计个数，因此这个过程可以在 $\mathcal{O}(1)$ 内完成。我们可以统计合法的 $S$ 左端点 $pnt$ 的个数。下文记 $T=[L,R]$，并且使用 $1$ 作为索引的起始。

左端点 $pnt$ 满足 $1\leq pnt \leq L$，右端点 $(pnt+|S|-1)$ 满足 $R\leq pnt+|S|-1\leq n$。解不等式，解得 $\max(1,R-|S|+1)\leq pnt \leq \min(L,n-|S|+1)$。

根据这个左端点可以取到的区间统计对答案的贡献即可。

**实现**

对于每一组数据：

1. 读入，记录每一个数的位置。
1. 枚举 $med$。

对于每一轮循环：

1. 扩展区间 $T$，计算 $|S|$。
1. 如果 $|S|\geq |T|$，统计对答案的贡献。
1. 输出答案

请注意，在每一轮循环中，都需要计算两次，因为 $|S|$ 可以取 $2\cdot med+2$，亦可以取 $2\cdot med+1$。

还需要注意，当 $\max(1,R-|S|+1)>\min(L,n-|S|+1)$ 时，不进行统计，或者说对答案的贡献为 $0$。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[1000001],rcd[1000001];
void solve(){
	cin>>n;
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		rcd[a[i]]=i;//记录位置 
	} 
	int L=1e9,R=0;
	int ans=0;
	for(int i=0;i<n;++i){
		L=min(L,rcd[i]),R=max(R,rcd[i]);//双指针扩展区间T 
		int len=(i+1)*2;//计算|s| 
		if(R-L+1>len)continue;//特判一下 
		int l=max(1ll,R-len+1),r=min(L,n-len+1);//左端点可以取到的区间 
		ans+=max(0ll,(r-l+1));//计算贡献 
		len--;//下面的同理 
		if(R-L+1>len)continue;
		l=max(1ll,R-len+1),r=min(L,n-len+1);
		ans+=max(0ll,(r-l+1));
	}
	cout<<ans<<"\n";
}
signed main(){
	int T; 
	cin>>T;
	while(T--)solve();
}

```


---

## 作者：小超手123 (赞：3)

观察条件 $\text{mex}(a_l,a_{l+1},...,a_r)> \text{med}(a_l,a_{l+1},...,a_r)$。

从 $mex$ 入手，假如 $[0,d]$ 都在该区间出现过，那么 $mex > d$，不妨假设 $med = d$。

设 $P_i$ 为 $i$ 在排列中的下标。

记 $L = min(P_l.....P_r)$，$R = max(P_l.....P_r)$。

那么目标区间一定包含 $[L,R]$，设目标区间为 $[i,j]$，换言之 $i\in[1,L]$。

但光有这个条件是不够的，还要保证 $med = d$，容易发现答案区间的 $Len=2d+2$ 或 $2d + 1$。

即 $R \leq i+Len-1 \leq n$。

总而言之 $max(1,R-Len+1) \leq i \leq min(L, n - Len + 1)$。

时间复杂度 $O(n)$。

```cpp

#include<bits/stdc++.h>
#define N 10000007
#define int long long
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0; char ch = getchar(); int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
}
int n, L = 1e9, R, ans, t;
int a[N], p[N];
void get(int Len) {
    int l = max(1ll, R - Len + 1), r = min(L, n - Len + 1); 
    ans += (r - l + 1 >= 0 ? r - l + 1 : 0); 
}
signed main() {
    read(t);
    while(t--) {
        ans = 0;
        L = 1e9;
        R = 0;
        read(n); 
        for(int i = 1; i <= n; i++) {
            read(a[i]);
            p[a[i]] = i;
	    }
	    for(int d = 0; d < n; d++) {
	        L = min(L, p[d]);
	        R = max(R, p[d]);
	    //cout << L << " " << R << endl;
	        get(2 * d + 2);
	        get(2 * d + 1);
	    }
	    cout << ans << endl;
	}
    return 0;
}
```

---

## 作者：zhlzt (赞：2)

### 题解

从小到大枚举 $\text{med}(p_l,p_{l+1},\ldots,p_r)$，设为 $k$。

显然有 $\{0,1,\ldots,k\}\in \{p_l,p_{l+1},\ldots,p_r\}$，且 $(r-l+1)\in \{2k+1,2k+2\}$。

设满足 $\{0,1,\ldots,k\}\in \{p_l,p_{l+1},\ldots,p_r\}$ 的最小区间为 $[l_0,r_0]$，有 $l\le l_0\le r_0\le r$。

按 $(r-l+1)$ 的取值分类计算答案：

- $r-l+1=2k+1$，若 $2k+1\le n \land 2k+1\ge r_0-l_0+1$，则满足条件的区间 $[l,r]$ 有 $\min(n-(2k+1)+1,l_0)-\max(1,r_0-(2k+1)+1)$ 个（这里按 $l$ 的取值范围考虑，当然也可以按 $r$ 的取值范围考虑）。

- $r-l+1=2k+2$，若 $2k+2\le n \land 2k+2\ge r_0-l_0+1$，则满足条件的区间 $[l,r]$ 有 $\min(n-(2k+2)+1,l_0)-\max(1,r_0-(2k+2)+1)$ 个（这里按 $l$ 的取值范围考虑，当然也可以按 $r$ 的取值范围考虑）。


### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
int p[maxn],q[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) cin>>p[i],q[p[i]]=i;
		int l=q[0],r=q[0];
		ll ans=0;
		for(int i=0;i<(n+1)/2;i++){
			if((i<<1|1)>=r-l+1){
				ans+=min(n-(i<<1),l)-max(1,r-(i<<1))+1;
			}
			if((i<<1)+2>=r-l+1 and (i<<1)+2<=n){
				ans+=min(n-(i<<1|1),l)-max(1,r-(i<<1|1))+1;
			}
			l=min(l,q[i+1]),r=max(r,q[i+1]);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：May_Cry_ (赞：2)

一道不错的思维题
## 思路
这道题初看上去似乎不太可做，但是我们发现序列值域为 $0$ 到 $n - 1$，设其中一个子段长度为 $s$，这意味着如果想让 Mex > Med，那么从 $0$ 到 $\left( s-1\right) /2$ 都应该在这个子段中，所以我们可以枚举每个子段长 $s$，利用两个指针 $l$ 和 $r$ 来判断可不可行，然后统计答案。注意 ``ans`` 初始值为 ``1``。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;
int T ,ans ,n;
int a[N] ,pos[N];
void solve() {
//	if (n == 1) {cout << 1 << endl;return;}
	ans = 1;
	int l = pos[0] ,r = pos[0];
	for (int i = 2;i <= n;i ++) { 
	    int mid = (i - 1) / 2;
		l = min(l ,min(pos[mid] ,n - i + 1));
		r = max(r ,max(pos[mid] ,i));
		if (r - l < i) ans += (i - (r - l));
	}
	cout << ans << endl;
}
signed main() {
	cin >> T;
	while(T --) {
		cin >> n;
		memset(pos ,0 ,sizeof pos);
		for (int i = 1;i <= n;i ++) cin >> a[i] ,pos[a[i]] = i;
		solve();
	}
}
```


---

## 作者：small_john (赞：2)

## 题目大意

给定一个数列，求满足 $\operatorname{mex}(a_l\sim a_r)>\operatorname{med}(a_l\sim a_r)$ 的区间 $[l,r]$ 的个数。

## 解题思路

记 $p_i$ 为 $i$ 出现的位置。

我们可以枚举 $d$，先确定 $\operatorname{mex}(a_l\sim a_r)>d$ 的区间。由于数列是 $0\sim n-1$ 的排列，所以这个区间必须包含 $0\sim d$。用 $l$ 记录区间最大左端点，$r$ 记录区间最小左端点。可以在线维护 $l,r$，即 $l  = \min\{l,p_d\},r = \max\{r,p_d\}$。

接下来在考虑 $\operatorname{med}(a_l\sim a_r)=d$。由于这个区间已经包含了 $0\sim d$，所以长度就是 $2\times d+2$ 和 $2\times d+1$。知道长度后，就可以 $O(1)$ 统计答案了。

时间复杂度为 $O(n)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0; char ch = getchar(); int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
}
const int N = 1e7+5,mod = 41719;
int ans,n,a[N],l = N+1,r,p[N];
void work(int len)
{
	if(r-l+1>len) return;
	int _l = max(1ll,r-len+1),_r = min(l,n-len+1);
	ans+=max(0ll,_r-_l+1);
}
signed main()
{
	read(n);
	for(int i = 1;i<=n;i++)
		read(a[i]),p[a[i]] = i;
	for(int i = 0;i<n;i++)
	{
		l = min(l,p[i]),r = max(r,p[i]);
		int len = i*2+2;
		work(len),work(len-1);
	}
	cout<<((n+1)*n/2-ans)%mod;
	return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

[不会有更好的食用体验。](https://www.cnblogs.com/Tomoyuki-Mizuyama/p/18304413)
# 题目大意
注意多组数据，所以一定要清空。
# 题目实现
设当前序列是 $S$，要想满足题意，那么 $[0,med(S)]$ 中的数一定要全部出现在 $S$ 中，这是第一个要求，可以用双指针来维护。

在满足第一个要求的前提下，如果 $med(S) = i$，那么 $|S|=i\times 2 +1$ 或 $|S|=i\times 2+2$，自己模拟一下就可以发现。 

设原序列包含 $[0,med(S)]$ 的最小区间是 $[l,r]$，那么对于任意一个满足两个要求的序列 $S=[T,T+|S|-1]$，我们必须满足 $1\le T\le l$ 且 $r\le T+|S|-1\le n$，解不等式得 $\max(1,r-|S|+1)\le T\le \min (l,n-|S|+1)$，统计答案即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
typedef long long ll ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 2e5 + 7 ;
int t ,n ,p[N] ,l ,r ,a[N] ;
ll ans ;
inline void init () {
	l = INT_MAX ;
	r = 0 ;
	ans = 0 ;
}
inline void solve (int &x) {
	if (r - l + 1 > x) return ; // 剪枝
	int L = max (1 ,r - x + 1) ,R = min (l ,n - x + 1) ;
	R - L + 1 > 0 ? ans += (ll) (R - L + 1) : 0 ; // 排除非法情况
}
int main () {
	read (t) ;
	do {
		read (n) ;
		f (i ,1 ,n ,1) {
			read (a[i]) ;
			p[a[i]] = i ; // 记录下标
		}
		init () ;
		f (i ,0 ,n ,1) {
			l = min (l ,p[i]) ;
			r = max (r ,p[i]) ;
			int len = i * 2 + 1 ;
			solve (len) ;
			solve (++ len) ;
		}
		cout << ans << '\n' ;
	} while (t -- != 1) ;
	return 0 ;
}
```

---

## 作者：ax_by_c (赞：1)

定义： $\operatorname{mex}(S)$ 为没有在 $S$ 中出现的最小非负整数；$\operatorname{med}(S)$ 为 $S$ 从小到大排序后 $S_{\left\lfloor\frac{\vert S\vert+1}2\right\rfloor}$ 的值（下标从 $0$ 开始）。

以下将 $\operatorname{mex}$ 写作 $m$，将 $\operatorname{med}$ 写作 $p$。

考虑 $m\ge p$ 的条件，显然区间内包含了 $[0,p]$ 中所有数。

于是枚举 $p$，并记包含不超过 $p$ 的所有数的最小区间 $[L,R]$。

然而还需要使 $\operatorname{med}$ 的值是 $p$，则 $p$ 应在区间中排第 $p+1$ 位，可得区间长度为 $2p+1$ 或 $2p+2$。设 $[L,R]$ 的长度为 $x$，另选的数共有 $y$ 个，可得 $x+y=2p+1$ 或 $x+y=2p+2$，易解得 $y_0,y_1$。

对于其中一个 $y$，我们需要求 $0\le i\le y$ 且 $i\le L-1$ 且 $y-i \le n-R$ 的 $i$ 的个数。将式子变形得 $\max(0,R+y-n)\le i\le \min(y,L-1)$，结果显然。

时间复杂度 $O(n)$。

---

## 作者：紊莫 (赞：1)

遇到此类问题可以先钦定一个值，然后考虑计算其他的贡献。

这里以长度为例，假设当前长度为 $len$，那么我们想让要 $\text{mex}>\text{med}$，等价于让第 $\left \lfloor  \dfrac{len-1}{2} \right \rfloor$ 个数字作为 $\text{mex}-1$。

由于这是一个排列，我们发现很多美好的性质，首先，随着 $len$ 变大，$\text{mex}$ 也变大，包含 $\text{mex}$ 的最小区间一定是不减的（因为始终要含有 $0\dots \text{mex}-1$，这个集合只会越来越大），也就是可以 $O(1)$ 维护左右端点的变化。

最后统计答案，可以参考这幅图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ddujpq9w.png)

示例代码如下。

```cpp
int n,m,a[N],p[N];
void solve(){
	n=rd();F(i,1,n){
		a[i]=rd();
		p[a[i]]=i;
	}
	int ans=1,l=p[0],r=p[0];
	F(len,2,n){
		int mid=(len-1)/2;
		l=min({l,p[mid],n-len+1});
		r=max({r,p[mid],len});
		ans+=max(0ll,len-(r-l));	
	}
	cout<<ans<<endl;
}
```


---

