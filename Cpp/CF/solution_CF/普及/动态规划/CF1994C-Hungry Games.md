# Hungry Games

## 题目描述

### 题目大意

Yaroslav 正在玩一款电脑游戏，他的角色遇到了 $n$ 个蘑菇，第 $i$ 个蘑菇的毒性定义为 $a_i$。Yaroslav 可以选择两个整数 $1\le l\le r\le n$，并操控他的角色依次食用第 $l,l+1,\dots,r$ 个蘑菇。

Yaroslav 的角色有一个中毒属性 $g$，初始为 $0$。当他食用第 $i$ 个蘑菇时，$g$ 会增加 $a_i$，若此时 $g$ 超过了一个预设的最大中毒值 $x$，则 $g$ 会重置为 $0$。

Yaroslav 想知道有多少种选择 $l,r$ 的方案能使他的角色食用完蘑菇后，中毒属性 $g$ 不为 $0$。

## 样例 #1

### 输入

```
5
4 2
1 1 1 1
3 2
1 2 3
1 6
10
6 3
1 2 1 4 3 8
5 999999999
999999999 999999998 1000000000 1000000000 500000000```

### 输出

```
8
2
0
10
7```

# 题解

## 作者：_ZML_ (赞：5)

# 题目大意

有一个 $sum$，每次 $sum$ 会增加 $a_i$ 如果 $sum>x$，那就让 $sum=0$。

问有多少个区间使得最后 $sum$ 的值不为零。

# 思路

显然是一个动态规划的题目，设 $dp_i$ 表示以 $i$ 为左端点的合法区间。

假设当前的左端点为 $L$。

再假设从左端点 $L$ 出发，第一次使 $sum$ 为零的右端点为 $P$，也就是第一个让 $a_L+a_{L+1}+\cdots+a_P>x$ 的 $P$。（若没有满足条件的 $P$，令 $P=n+1$）。

那么以 $L$ 到 $P-1$ 为右端点区间肯定都满足条件，一共 $P-L$ 个。

又因为 $sum$ 加到 $P$ 的时候就会变为 $0$。

所以左端点在 $L$，右端点在 $P$ 以后的区间数量相当于左端点在 $P+1$ 的区间合法数量，也就是 $dp_{P+1}$。

上面这句话有点绕，可以对照样例手搓一下。

所以状态转移方程也就出来了，倒序转移即可。
$$
dp_L=dp_{P+1}+P-L
$$
还有一个问题，如何求 $P$？

我这里有两个方法。

法一（二分加前缀和）：

​	设前缀和数组是 $S$，则若 $S_{mid}-S_{L-1}>x$ 那么答案肯定在 $L$ 到 $mid$ 里，否则在 $mid+1$ 到 $n$ 里。

法二（双指针）：

​	枚举 $L$，每次让 `L--,now+=a[L]`。

​	最开始让 $P=n+1$，如果 $now>x$ ，那就重复执行 `P--` 操做。

​	这时的 $now\le x$ 所以计算的时候 $P$ 得加上 $1$ 。

这道题就做完了。

最后提醒多测清空 $dp$ 数组。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, x;
int a[200010], f[200010], sum[200010];
int g(int st)
{
    int l = st, r = n, ans = n + 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (sum[mid] - sum[st - 1] > x)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return ans;
}
void solve()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> a[i], f[i] = 0, sum[i] = sum[i - 1] + a[i];
    f[n + 1] = f[n + 2] = 0;
    int ans = 0;
    for (int i = n; i >= 1; i--)
    {
        int p = g(i) + 1;
        f[i] = f[p] + p - i - 1;
        ans += f[i];
    }
    cout << ans << "\n";
}
signed main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：MrJC_Pandingding (赞：3)

# 解题思路
从每个蘑菇开始吃，$g$ 会有若干（可能为 $0$）次变为 $0$。建立一个数组 $b$，$b_i$ 表示从第 $i$ 个蘑菇开始吃，$g$ 第一次变为 $0$ 的蘑菇编号。建立一个数组 $c$，$c_i$ 表示从第 $i$ 个蘑菇开始吃，到任意位置结束，会有几种情况 $g=0$。则 $c_i=c_{b_i+1}+1$。最后，用总区间数减 $c$ 中的数之和，即为答案。注意用 `long long`。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int a[maxn+10],b[maxn+10];
int c[maxn+10],n,t,x;
long long f[maxn+10],sumn;
int main()
{
	int i;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		for(i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			f[i]=f[i-1]+a[i];
		}
		for(i=1;i<=n;++i)
			b[i]=upper_bound(f+1,f+n+1,f[i-1]+x)-f;
		memset(c,0,sizeof(c));
		for(i=n;i>=1;--i)
			if(b[i]<=n)
				c[i]=c[b[i]+1]+1;
		sumn=1ll*n*(n+1)>>1;
		for(i=1;i<=n;++i)
			sumn-=c[i];
		printf("%lld\n",sumn);
	}
	return 0;
}
```

---

## 作者：anonymous_Y (赞：3)

[题目传送门](https://codeforces.com/contest/1994/problem/C)


题目大意：有一个 $g$,初始值为 $0$,在第 $i$ 个位置，$g$ 增加 $a_i$ 。

如果 $g \leq x$，则过程继续；

否则, $g$ 变为零，过程继续。

求所有在操作结束后值不为 $0$ 的区间数。

___

显然我们可以发现对于一个左端点为 $i$ 的区间，可以分为两部分，一部分为 $a_i$\~$a_q$，这部分他们的总和就是 $\leq x$，显然不涉及到“归零”这个操作，答案直接加上 $q-i-1$ 。

那么另外一部分就涉及到“归零”这个操作了。不难得出在 $q+1$ 这个位置时 $g$ 是为 $0$ 的。那么这不就变成了要求 $q$ 为左端点的合法区间数了嘛。

所以我们不难得出一个转移方程。

```cpp
dp[i]=dp[q]+q-i-1;
```

最后就是如何寻找 $q$ 的位置？二分搜索就好啦。

___
代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int x,n;
		cin>>n>>x;
		vector<int> a(n+1);
		for(int i=1;i<=n;i++) cin>>a[i];
		partial_sum(a.begin()+1,a.end(),a.begin()+1);
		vector<int> dp(n+2);
		for(int i=n-1;i>=0;i--){
			int q=upper_bound(a.begin(),a.end(),a[i]+x)-a.begin();
			dp[i]=dp[q]+q-i-1;
		}
		cout<<accumulate(dp.begin(),dp.end(),0ll)<<endl;
	}
	return 0;
}
```
完结撒花！

---

## 作者：CNS_5t0_0r2 (赞：2)

我不怎么刷 CF 的题，第一次知道这种题要用 DP，写一篇题解记录一下。

设状态 $dp_l$ 表示以 $l$ 为左端点的区间中合法的区间数量。

假设 $l$ 后**第一个使 $g$ 重置为 $0$ 的右端点**为 $p$（没有的话设为 $n + 1$），那么 $[l,l],[l,l + 1],\cdots,[l,p - 1]$ 这 $p - l$ 个区间肯定是合法的 ，然后如果 $[p + 1,r]$ 是合法的，那么 $[l,r]$ 也是合法的，这样合法的 $[p + 1,r]$ 总共有 $dp_{p + 1}$ 个。

综上，得到转移方程：

$$dp_l = dp_{p + 1} + p - l$$

其中 $l$ 显然要从后往前枚举。

现在的问题就是如何求出 $p$ 了。

我用的是双指针法（参考[这篇](https://www.luogu.com.cn/article/bjq6y3bi)），记 $now$ 为 $[l,p]$ 的 $g$ 值（其实就是区间和，），在移动 $l,p$ 的时候， $now$ 是可以 $O(1)$ 更新的。每移动一次 $l$，当 $now > x$ 时，我们就移动 $p$ 直到 $now \leq x$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 9;
int n,x;
int a[N];
int dp[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		cin >> n >> x;
		for(int i = 1;i <= n + 2;i++)//多测不清空，爆零两行泪 
			dp[i] = 0;
		for(int i = 1;i <= n;i++)
			cin >> a[i];
		int p = n + 1,now = 0;
		int ans = 0;
		for(int l = n;l >= 1;l--){
			now += a[l];
			while(now > x){//注意这里得是while不能是if（我写代码的时候脑抽了）
				p--;
				now -= a[p];
			}
			dp[l] = dp[p + 1] + p - l;
			ans += dp[l];
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

## 解题思路

双指针，DP。

考虑从 $l$ 开始，第一次分数变为 $0$ 的位置是最小的满足 $a_l+a_{l+1}+\cdots+a_r\gt x$ 的 $r$，显然可以双指针遍历 $O(n)$ 求得每一个 $i$ 对应的第一次分数变为 $0$ 的位置，记为 $r_i$。

接下来考虑转移：记 $cnt_i$ 表示左端点为 $i$ 的，进行所有操作后分数为 $0$ 的右端点个数。

如果不存在左端点为 $i$ 的分数变为 $0$ 的位置，那么 $cnt_i=0$，否则 $cnt_i=cnt_{r_i+1}+1$。

因为左端点为 $i$ 的区间有一个 $[i,r_i]$ 必定分数为 $0$，继续往右满足分数为 $0$ 的右端点与 $r_i+1$ 是相同的，故转移方程为 $cnt_i=cnt_{r_i+1}+1$。

$O(n)$ 转移求和即可。

---

## 作者：_O_w_O_ (赞：1)

设 $f_i$ 为以 $i$ 开头且满足从 $i\rightarrow j$ 的等级最终为 $0$ 的 $j$ 的数量。

那么答案为 $\frac{n\times(n+1)}{2}-\sum_{i=1}^n f_i$。

我们注意到若从一个 $i$ 出发到一个 $j$，满足 $i$ 到 $i\sim j-1$ 中任意一个数等级均为正，且 $i$ 到 $j$ 等级为 $0$，那么 $f_i=f_{j+1}+1$。

那么我们的目标就变成了为每个 $i$ 找到第一个满足 $\sum_{k=i}^ja_k>x$ 的 $j$。

这个过程直接双指针就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5;
int n,x,a[N],cnt[N],dp[N];

void solve(){
	fill(dp+1,dp+n+2,0);
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=1,r=0,sum=0;
	for(;l<=n;l++){
		while(r<=n&&sum<=x) r++,sum+=a[r];
		cnt[l]=r;
		sum-=a[l];
	}
	sum=0;
	for(int i=n;i>=1;i--){
		if(cnt[i]==n+1) continue;
		else dp[i]=dp[cnt[i]+1]+1;
		sum+=dp[i];
	}
	cout<<n*(n+1)/2-sum<<endl;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：qinziao (赞：1)

# 洛谷 CF1994C
## 题目大意
题目大意是求有多少个子段满足要求：子段和小于等于 $X$，其中若超过了 $X$，子段和变为 $0$，不影响后面的数相加，只要最后的结果满足要求即可。
## 解法说明
我们从 $i$ （代表子段的左端）开始，用 $j$ 代表右端，可能存在多个 $j$ 使得整个和变为 $0$，我们要找的是第一个这样的 $j$。若找不出来，说明整个右边全部相加都没事。

用 $l[i]$ 来保存对于 $i$ 这样的 $j$ 的位置。
```cpp
vector<long long>a(n);
for(int i=0;i<n;i++){
    cin>>a[i];
}
vector<int>l(n,-1);
j=0;
for(int i=0;i<=n-1;i++){
	if(j<n and sum<=x)
  		sum+=a[j];
  		j++;
	l[i]=j-1;//j的
	if(sum<=x)//如果sum仍然小于等于x，说明j到底了
    l[i]=-1;//那么可以退出了，因为剩下的i越往右边走，
//sum肯定会越来越小，剩下的l[i]都为-1。
		break;
	
	sum-=a[i];
}
```
剩下的是 dp 部分，用 $vis[i]$ 代表 $i$ 的右边有多少个不能用的点，先处理一下，算是个边界吧，待会的 dp 会建立在这个边界上。
```cpp
for(int i=0;i<n;i++){
    val[i]=(l[i]!=-1);//括号中成立则为1，否则为0；
}
```
接着倒着 dp。
```cpp
for(int i=n-1;i>=0;i--){
	if(l[i]==-1||l[i]==n-1) continue;
    val[i]+=val[l[i]+1];
}
```
最后统计答案。
```cpp
for(int i=0;i<n;i++){
	ans+=n-i-val[i];
}
```

---

## 作者：I_will_AKIOI (赞：1)

首先枚举两个端点的复杂度为 $n^2$，绝对炸。那么我们就只枚举左端点 $l$，另外一个右端点 $r$ 我们二分一下，使得他满足吃完这个区间的蘑菇后，$g=0$，并且这个 $r$ 最小。我们把这个 $r$ 记为 $next_l$。由于 $\displaystyle\sum_{i=l}^{r-1}a_i<x$，所以对于 $\forall i\in[l,r)$，吃掉区间 $[l,i]$ 的蘑菇后，$g$ 都不为 $0$。于是我们就可以统计一下当前的方案数，也就是 $r-l$。

那么怎么计算答案呢？我们枚举指针 $p=[1,n]$，表示当前的左端点是啥。然后处理完区间后，将 $p$ 跳到 $next_p$ 处，然后继续统计答案，最后加在一起。

但是我们每次将指针跳到下一个的过程可能会有 $n$ 次，加上枚举了 $n$ 次指针，那么复杂度是 $n^2$ 的，还是会 TLE。

你说这个将指针往后跳的过程怎么这么像 KMP 的前缀数组呢？同时会想到由前缀数组构成的失配树。那么为什么不像失配树一样，将 $p$ 和 $next_p$ 连一条边，然后来处理呢？

连边之后，我们发现每一条边的权值就是方案数 $nxt_i-i$。一条边会被 $i$ 的所有子节点往上跳一遍。所以我们处理出 $i$ 的子树大小 $sz_i$，然后用这条边的边权乘上子树大小，累加起来就是答案。

虽然我这题只写了半小时，但是感觉我这个方法实在是太复杂了，若有简便方法，欢迎在评论区提出。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
#pragma GCC optimize("O3")
using namespace std;
int n,x,ans,a[N],sum[N],nxt[N],sz[N];
vector<pair<int,int> >v[N];
void dfs(int k)
{
	sz[k]=1;
	for(auto now:v[k])
	{
		dfs(now.first);
		sz[k]+=sz[now.first];
		ans+=sz[now.first]*now.second;//算出子树和边权，乘在一起
	}
	return;
}
void solve()
{
  cin>>n>>x;
	ans=0;
	for(int i=1;i<=n+1;i++) v[i].clear();
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)
	{
		nxt[i]=upper_bound(sum+1,sum+n+1,x+sum[i-1])-sum;//利用STL函数方便求出nxt[i]
		if(nxt[i]>n) v[n+1].push_back({i,nxt[i]-i});
		else v[nxt[i]+1].push_back({i,nxt[i]-i});
      //特判一下没找到在i的后面使得g为0的点
	}
	dfs(n+1);
	cout<<ans<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 3. Hungry Games / 黄

有一排蘑菇。

每次可以选择一个区间依次吃蘑菇，初始受毒性为 $0$，吃掉第 $i$ 个蘑菇会使得受毒性增加 $a_i$。每次吃掉一个蘑菇后，若受毒性超过一个常数 $x$，则将受毒性归零。问有多少个区间使得依次吃完蘑菇后的受毒性不为 $0$。

正难则反。虽然正也不难，但是反更好想。

结果不为 $0$=总区间数-结果为 $0$。

计算方式类似拓扑排序。

记 $d_i$ 表示以 $i$ 为区间右端点时有多少个左端点 $j$ 满足从 $j$ 吃到 $i$ 后受毒性为 $0$。

遍历到一个位置 $i$ 时，找到第一个满足 $\sum_{j=i}^t a_j>x$ 的端点 $t$，将 $d_t$ 增加 $d_i+1$。因为，$d_i$ 所记录的方案满足最终受毒性为 $0$，而从 $i$ 到 $t$ 的最终受毒性也是 $0$，所以可以看作将两个区间拼接起来。最终受毒性仍然为 $0$。

时间复杂度 $O(n)$。

```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
int n, k, r;
ll a[N], dp[N], cur, res;
void run()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", a + i);
    }
    memset(dp + 2, 0, n << 3);
    cur = 0;
    r = 1;
    for (int i = 1; i <= n; i++)
    {
        cur -= a[i - 1];
        while (r <= n and cur <= k)
            cur += a[r], r++;
        if (cur <= k)
            continue;
        dp[r] += dp[i] + 1;
    }
    res = n;
    res *= n + 1;
    res /= 2;
    for (int i = 2; i <= n + 1; i++)
    {
        res -= dp[i];
    }
    printf("%lld\n", res);
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```

---

## 作者：Bad_Luck_No_Fun (赞：0)

感觉 C 比 B 简单， C 我一眼秒了。

### 题目描述

给定长为 $n$ 的数列 $a$ 以及一个数 $x$。求有多少个区间 $[l,r]$ 满足以下性质：

开始时 $sum = 0$，从 $l$ 向 $r$ 走，每次 $sum$ 增加 $a_i$，如果 $sum>x$，$sum$ 归零，最终走到 $r$ 时 $sum >0$。

### 思路

预处理从每个位置向后走到哪个位置刚好没被清零，记为 $g(i)$ 。然后进行动态规划，设 $f(i)$ 表示从 $i$ 向后走存在多少个 $sum > 0$ 的情况。

于是易得转移方程 $f(i)=f(g(i)+2)+(g(i)-i+1)$ 。很明显倒着转移可以 $O(n)$。

然后就做完了。

### $Code$

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 2e5 + 5;
int T, n, x;
int s[N];
int a[N];
int g[N];
int f[N];

int query(int l, int r) {
	return s[r] - s[l - 1];
}

void init() {
	for (int i = 1; i <= n; i++) {
		int l = i, r = n;
		int ans = i - 1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (query(i, mid) <= x) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
//		cout << ans << endl;
		g[i] = ans;
//		cout << g[i] << endl;
	}
}

void solve() {
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	init();
	f[n + 1] = 0 ;
	f[n + 2] = 0;
	int ans = 0;
	for (int i = n; i; i--) {
		f[i] = (g[i] - i + 1) + f[g[i] + 2];
		ans += f[i];
	}
	cout << ans << endl;
}

signed main() {
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：AKPC (赞：0)

先假设 $to_i$，其意义是 $\sum_{j=i}^{to_i}a_i>x$，而 $\sum_{j=i}^{to_i-1}a_i\leq x$，如果不存在 $to_x$ 则默认为 $n+1$。$\sum_{j=i}^{x}a_i$ 单调递增，故可以用线性类似队列的方法计算出 $to$ 这个数组。

由题很容易发现，$(i,r\in[i,to_i))$ 都是合法的方案，显然 $(i,r\in[to_i+1,to_{to_i+1}))$ 也是合法方案，以此类推。换言之，$(to_i+1,r\in[to_i+1,to_{to_i+1}))$ 这样的答案也会被同样次数地计算在 $(i,r\in[to_i+1,to_{to_i+1}))$ 这样的答案。可以通过这个性质，记录每个 $r\in[to_i+1,to_{to_i+1})$ 被记录为答案的不同 $l$ 个数，计算后乘数即可。

```cpp
n=read(),x=read();
for (int i=1;i<=n;i++) a[i]=read(),cnt[i]=0;
a[n+1]=1e18;
int r=0,sum=0,ans=0;
for (int i=1;i<=n;i++){
	while (sum<=x) sum+=a[++r];
	to[i]=r,sum-=a[i];
}
for (int i=1;i<=n;i++) cnt[i]++,cnt[to[i]+1]+=cnt[i];
for (int i=1;i<=n;i++) ans+=cnt[i]*(to[i]-i);
cout<<ans<<'\n';
```

---

