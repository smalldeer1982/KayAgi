# Max to the Right of Min

## 题目描述

You are given a permutation $ p $ of length $ n $ — an array, consisting of integers from $ 1 $ to $ n $ , all distinct.

Let $ p_{l,r} $ denote a subarray — an array formed by writing down elements from index $ l $ to index $ r $ , inclusive.

Let $ \mathit{maxpos}_{l,r} $ denote the index of the maximum element on $ p_{l,r} $ . Similarly, let $ \mathit{minpos}_{l,r} $ denote the index of the minimum element on it.

Calculate the number of subarrays $ p_{l,r} $ such that $ \mathit{maxpos}_{l,r} > \mathit{minpos}_{l,r} $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
6
5 3 6 1 4 2```

### 输出

```
4```

## 样例 #3

### 输入

```
10
5 1 6 2 8 3 4 10 9 7```

### 输出

```
38```

# 题解

## 作者：蒟蒻君HJT (赞：22)

题意：给定一个排列长度为 $n$ 的排列 $p_i$，问有多少子区间满足其最大值的出现位置在其最小值的出现位置的右边。

数据范围：$n\leq 10^6$。

套路地，考虑一次性枚举最大值为 $p_x$ 的所有区间。

记 $rm_i$ 为 $p_i$ 右边首个大于 $p_i$ 的下标（不存在则为 $n+1$），$lm_i$ 为 $p_i$ 左边首个大于 $p_i$ 的下标（不存在则为 $0$）。

则最大值为 $p_x$ 的区间，左端点 $\in[lm_i+1,i]$，右端点 $\in[i, rm_i-1]$。

先判掉某一端点为 $p_x$ 的情况。

然后，考虑一种暴力。直接枚举右端点 $r$，找出 $[x,r]$ 区间上的最小值 $m_1$，然后找出 $m_1$ 左端第一个比 $m_1$ 小的数 $m_2$，则左端点把 $m_2$ 囊括进去就可以了。

暴力枚举左端点也是类似的。当然这样做复杂度是错的，构造一个 $p_i=i$，且每次都枚举左端点就炸了。

但是如果比较左端点的可能值个数和右端点的可能值个数，并选择少的那个枚举，总复杂度就是 $\mathcal{O}(n\log n)$，这叫做启发式分裂。

原因在于考虑每个数被枚举到的所有时刻。下一时刻的区间长度至多为上一时刻的区间长度的一半，故被枚举到的次数不超过 $\log_{2} n$ 次。

代码：

```cpp
#include <bits/stdc++.h>
int a[1000005], n;
int lmi[1000005], rmi[1000005], lma[1000005], rma[1000005];
int tp = 0, st[1000005];
long long ans = 0ll;
void wk1(int l, int x, int r){
  int e = 1e9, y;
  for(int i = x - 1; i >= l; --i){
    if(a[i] < e){
      e = a[i];
      y = rmi[i];
    }
    ans += 1ll * std::min(y - x - 1, r - x);
  }
  return ;
}
void wk2(int l, int x, int r){
  int e = 1e9, y;
  for(int i = x + 1; i <= r; ++i){
    if(a[i] < e){
      e = a[i];
      y = lmi[i];
    }
    ans += 1ll * std::max(0, y - l + 1);
  }
  return ;
}
int main(){
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  tp = 0; st[0] = 0;
  for(int i = 1; i <= n; ++i){
    while(tp && a[i] < a[st[tp]]) --tp;
    lmi[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = 0;
  for(int i = 1; i <= n; ++i){
    while(tp && a[i] > a[st[tp]]) --tp;
    lma[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = n + 1;
  for(int i = n; i >= 1; --i){
    while(tp && a[i] < a[st[tp]]) --tp;
    rmi[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = n + 1;
  for(int i = n; i >= 1; --i){
    while(tp && a[i] > a[st[tp]]) --tp;
    rma[i] = st[tp];
    st[++tp] = i;
  }
  for(int i = 1; i <= n; ++i){
    int lm = lma[i] + 1, rm = rma[i] - 1;
    if(i - lm + 1 <= rm - i + 1) wk1(lm, i, rm);
    else wk2(lm, i, rm);
    ans += 1ll * (i - lm);
    //printf("%d %d %d %lld\n", i, lm, rm, ans);
  }
  printf("%lld\n", ans);
  return 0;
}
```




---

## 作者：masterhuang (赞：18)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)，第九题。

考虑对于每个右端点统计答案。假设在 $r$ 时，数组 $a$ 满足：若区间 $[l,r]$ 满足条件，则 $a_l=1$，否则 $a_l=0$。

我们考虑 $r\gets r+1$ 时对于数组 $a$ 的影响。发现只有 $a_{r+1}$ 为最大/小值时才会发生影响。
  
设 $i$ 前第一个比 $a_i$ 大的位置为 $b_i$，第一个比 $a_i$ 小的位置为 $c_i$。$b,c$ 容易单调栈维护求出。
  
+ 若 $b_{r+1}<r$（即 $a_r<a_{r+1}$），则 $a_{r+1}$ 只能当在它为**最大值**时造成影响。容易发现影响为：$\forall x\in[b_i+1,r],a_x\gets 1$。
  
+ 否则 $a_r>a_{r+1}$，类似的，$a_{r+1}$ 只能当在它为**最小值**时造成影响。影响为：$\forall x\in[c_i+1,r],a_x\gets 0$。
  
于是问题转变为区间赋值 $01$，区间和，线段树维护即可。复杂度 $O(n\log n)$。
  
代码：  
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e6+5;
int n,a[N],b[N],c[N],t1,t2;LL ans;
namespace SGT
{
	LL a[N<<2];int lt[N<<2];
	inline void pushup(int wz){a[wz]=a[wz<<1]+a[wz<<1|1];}
	inline void upd(int l,int r,int wz,int x){a[wz]=1ll*(r-l+1)*x;lt[wz]=x;}
	inline void pushdown(int l,int r,int wz)
	{
		int t=lt[wz],mid=(l+r)>>1;if(t==-1) return;
		upd(l,mid,wz<<1,t);upd(mid+1,r,wz<<1|1,t);lt[wz]=-1;
	}
	void updata(int l,int r,int wz,int L,int R,int x)
	{
		if(L<=l&&r<=R) return upd(l,r,wz,x);
		int mid=(l+r)>>1;pushdown(l,r,wz);
		if(L<=mid) updata(l,mid,wz<<1,L,R,x);
		if(mid<R) updata(mid+1,r,wz<<1|1,L,R,x);pushup(wz);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];b[1]=c[1]=t1=t2=1;
	for(int i=1;i<=(n<<2);i++) SGT::lt[i]=-1;
	for(int i=2;i<=n;i++)
	{
		while(t1&&a[b[t1]]<a[i]) t1--;
		while(t2&&a[c[t2]]>a[i]) t2--;int p1=b[t1]+1,p2=c[t2]+1;
		if(p1<=i-1) SGT::updata(1,n,1,p1,i-1,1);
		else SGT::updata(1,n,1,p2,i-1,0);
		ans+=SGT::a[1];b[++t1]=c[++t2]=i;
	}cout<<ans;
	return 0;
}
```

---

## 作者：KingPowers (赞：14)

[题目链接](https://www.luogu.com.cn/problem/CF1849E)

这里是线段树题解，其实是个套路题。

类似扫描线的思想，我们可以枚举右端点 $r$，那么我们的任务就是在 $r$ 向右移动时维护出每个 $l$ 对答案的贡献。

我们记 $mx_i$ 表示 $i$ 左边第一个比 $p_i$ 大的数的位置，$mn_i$ 表示 $i$ 左边第一个比 $p_i$ 小的数的位置，这两个东西显然都可以用单调栈线性求出。

如果 $mx_i<i-1$，那么当 $l\in[mx_i+1,i-1]$ 时，区间的最大值的位置都在 $r$，一定在最小值的右边，因此 $[mx_i+1,i-1]$ 的贡献要全部赋成 $1$。

如果 $mn_i<i-1$，那么当 $l\in[mn_i+1,i-1]$ 时，区间的最小值的位置都在 $r$，一定在最大值的右边，因此 $[mn_i+1,i-1]$ 的贡献要全部赋成 $0$。

事实上，因为 $p$ 是个排列，不难注意到 $mx_i$ 和 $mn_i$ 中一定有且仅有一个小于 $i-1$。

当 $l$ 在剩下的那些未被考虑到的位置时，$r$ 位置一定既不是最大值也不是最小值，对答案不会有影响，继承之前的结果即可。

时间复杂度：$O(n\log n)$。

```cpp
int n,p[N],mx[N],mn[N];
int top,st[N];
namespace DS{
    #define ls(now) now<<1
    #define rs(now) now<<1|1
    int sum[N<<2],tag[N<<2];
    void pushup(int now){
        sum[now]=sum[ls(now)]+sum[rs(now)];
    }
    void cov(int l,int r,int now,int c){
        sum[now]=(r-l+1)*c;tag[now]=c;
    }
    void pushdown(int l,int r,int now){
        if(tag[now]==-1) return;
        int mid=(l+r)>>1;
        cov(l,mid,ls(now),tag[now]);
        cov(mid+1,r,rs(now),tag[now]);
        tag[now]=-1;
    }
    void modify(int x,int y,int c,int l,int r,int now){
        if(x<=l&&r<=y) return cov(l,r,now,c);
        pushdown(l,r,now);
        int mid=(l+r)>>1;
        if(x<=mid) modify(x,y,c,l,mid,ls(now));
        if(y>mid) modify(x,y,c,mid+1,r,rs(now));
        pushup(now);
    }
}
void Main(){
    cin>>n;
    For(i,1,n) cin>>p[i];
    st[top=1]=n;
    Rof(i,n-1,1){
        while(top&&p[st[top]]<p[i]) mx[st[top--]]=i;
        st[++top]=i;
    }
    st[top=1]=n;
    Rof(i,n-1,1){
        while(top&&p[st[top]]>p[i]) mn[st[top--]]=i;
        st[++top]=i;
    }
    ll ans=0;
    For(i,2,n){
        if(mx[i]!=i-1) DS::modify(mx[i]+1,i-1,1,1,n,1);
        if(mn[i]!=i-1) DS::modify(mn[i]+1,i-1,0,1,n,1);
        ans+=DS::sum[1];
    }
    cout<<ans<<'\n';
}
```

---

## 作者：Register_int (赞：5)

其实完全没那么复杂，双 $\log$ 做法是能过的。

考虑分治，每次以大区间的 $minpos$ 做为分界点，计算左右端点在两侧的答案。选择较短的区间，在长区间上进行二分找到满足 $maxpos>minpos$ 的第一个端点：

- 枚举左端点，找到第一个前缀最大值比左边大的右端点。
- 枚举右端点，找到第一个后缀最大值比右边小的左端点。

由于前、后缀最大值都有单调不减的性质，因此可以将找到的端点往后的所有端点都计入答案中，查询可以使用 st 表。由于每次选的区间一定不超过当前区间长度的一半，那么每个位置被枚举的次数即为 $O(n\log n)$，总时间复杂度 $O(n\log^2 n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1e6 + 10;
 
int n, a[MAXN], p[MAXN][21], f[MAXN][21], lg[MAXN];
 
inline 
int cmin(int i, int j) {
	return a[i] < a[j] ? i : j;
}
 
inline 
void init() {
	for (int i = 1; i <= n; i++) p[i][0] = i, f[i][0] = a[i];
	for (int j = 1; j <= lg[n]; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			p[i][j] = cmin(p[i][j - 1], p[i + (1 << j - 1)][j - 1]);
			f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
		}
	}
}
 
inline 
int qpos(int l, int r) {
	int k = lg[r - l + 1];
	return cmin(p[l][k], p[r - (1 << k) + 1][k]);
}
 
inline 
int qmax(int l, int r) {
	int k = lg[r - l + 1];
	return max(f[l][k], f[r - (1 << k) + 1][k]);
}
 
inline 
int bound1(int ql, int qr, int x) {
	if (qmax(ql, qr) <= x) return qr + 1;
	int l = ql, r = qr, mid;
	for (; l < r; qmax(ql, mid = l + r >> 1) <= x ? l = mid + 1 : r = mid);
	return l;
}
 
inline 
int bound2(int ql, int qr, int x) {
	if (a[qr] >= x) return qr + 1;
	int l = ql, r = qr, mid;
	for (; l < r; qmax(mid = l + r >> 1, qr) > x ? l = mid + 1 : r = mid);
	return l;
}
 
inline 
ll solve(int l, int r) {
	if (l >= r) return 0;
	int mid = qpos(l, r); ll res = 0;
	if (mid - l < r - mid) {
		for (int i = l; i <= mid; i++) {
			res += r - bound1(mid, r, qmax(i, mid)) + 1;
		}
	} else {
		for (int i = mid; i <= r; i++) {
			res += mid - bound2(l, mid, qmax(mid, i)) + 1;
		}
	}
	return res + solve(l, mid - 1) + solve(mid + 1, r);
}
 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1; init();
	printf("%lld", solve(1, n));
}
```
~~我去除了绝大部分的标题行，但我保留了一部分，为的是让你知道你看的是 Ri 的题解~~

---

## 作者：L0vely_NaiL0ng (赞：2)

套路的枚举区间最大值的位置，记为 $i$，预处理 $i$ 左边第一个比它大的位置 $l$、右边第一个比它大的位置 $r$。先处理有一个端点是 $i$（一定是右端点）的区间，有 $i - l - 1$ 个。

考虑一种方法：枚举左端点 $j$，$l + 1\le j \le i - 1$，从右往左扫，边扫边记录区间 $[j, i - 1]$ 的**最小值的位置**，记为 $pos$ ，我们想让 $pos$ 成为区间的最小值（只有这样才能满足最小值在最大值左边），找到 $pos$ 右边第一个比 $pos$ 小的位置 $rp$，那么区间右端点最多可以到 $rp - 1$，区间数有 $rp - 1 - i$ 个（有个细节就是 $rp - 1$ 最大取到 $r - 1$）。

还有另一种方法：枚举右端点 $j$，$i + 1\le j \le r - 1$，从左往右扫，边扫边记录区间 $[i + 1, j]$ 的**最小值的位置**，记为 $pos$，我们不能让 $pos$ 成为区间最小值，要让 $i$ 左边有比 $pos$ 更小的值 ，找到 $pos$ 左边第一个比 $pos$ 小的值 $lp$，区间左端点至少要取到 $lp$，区间数为 $lp - (l + 1) + 1 = lp - l$（有个细节 $lp$ 最小取到 $l$）。

现在考虑结合这两种做法，如果枚举左端点的次数比枚举右端点少，采用第一种方法，否则第二种。这个东西叫启发式分裂，每个点最多被枚举到 $O(\log n)$ 次，总复杂度 $O(n \log n)$。

感性证明一下：考虑钦定枚举 $i$ 时按照 $a_i$ 从大往小枚举，每次将 $i$ 标记，那么每次找 $l$、$r$ 其实就是找左边第一个有标记、右边第一个有标记的，考虑你枚举了其中一个区间，这个区间肯定小于 $[l + 1, r - 1]$ 的一半，然后你把 $i$ 标记，下次你枚举到那个区间中的某个数时枚举量肯定小于等于那个区间的一半。换句话说，如果一个位置相邻 $2$ 次被 $2$ 个区间给枚举到了，后面这个区间的大小最多是前面那个区间大小的一半,首先区间大小一定变小了，且这一次又在前面那个区间中打了一个标记，挑选更小的区间，所以最多一半，每个位置最多被枚举到 $O(\log n)$ 次。**建议自己画个图理解一下**。

```
#include<bits/stdc++.h>
#define int long long
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define mid ((l + r) >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
#define pb push_back
#define For(i, x, y) for (int i = (x); i <= (y); i++)
#define foR(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
const int N = 1e6 + 5, mod = 998244353;
void cmin(int &x, int y) { x = min(x, y); return; }
void cmax(int &x, int y) { x = max(x, y); return; }
int ksm(int x, int y) {
	int v = 1;
	while (y) {
		if (y & 1) v = v * x % mod;
		x = x * x % mod; y >>= 1;
	}
	return v;
}
int n;
int a[N], lmax[N], rmax[N], lmin[N], rmin[N], st[N], t;
void solve() {
	cin >> n;
	For (i, 1, n) cin >> a[i];
	a[0] = a[n + 1] = n + 1;
	t = 0; st[++t] = 0;
	For (i, 1, n) {
		while (t && a[st[t]] < a[i]) t--;
		lmax[i] = st[t]; st[++t] = i;
	}
	t = 0; st[++t] = n + 1;
	foR (i, n, 1) {
		while (t && a[st[t]] < a[i]) t--;
		rmax[i] = st[t]; st[++t] = i;
	}	
	a[0] = a[n + 1] = 0;
	t = 0; st[++t] = 0;
	For (i, 1, n) {
		while (t && a[st[t]] > a[i]) t--;
		lmin[i] = st[t]; st[++t] = i;
	}
	t = 0; st[++t] = n + 1;
	foR (i, n, 1) {
		while (t && a[st[t]] > a[i]) t--;
		rmin[i] = st[t]; st[++t] = i;
	}
	int ans = 0;
	For (i, 1, n) {
		int l = lmax[i] + 1, r = rmax[i] - 1;
		//cout << i << " " << l << " " << r << endl;
		ans += i - l;
		if (i - l < r - i) {
			int minn = n + 1, pos;
			foR(j, i - 1, l) {
				if (minn > a[j]) {
					minn = a[j]; pos = j;
				} 
				int rp = rmin[pos] - 1;
				//cout << j << " " << rp << endl;
				rp = min(rp, r);
				ans += rp - i;
			}
		} else {
			int minn = n + 1, pos;
			For (j, i + 1, r) {
				if (minn > a[j]) {
					minn = a[j]; pos = j;
				}
				int lp = lmin[pos];
				//cout << j << " " << lp << endl;
				lp = max(lp, l - 1);
				ans += lp - l + 1;
			}
		}
		//cout << ans << endl;
	}
	cout << ans;
	return;
}
signed main() {
	//freopen("1.in", "r", stdin);
	int T;
	T = 1;
	while (T--) solve();
	return 0;
}
```

---

## 作者：hanjinghao (赞：2)

# 题意

给定一个长度为 $ n $ 的排列，问有多少个区间，满足其中最大值所在位置在最小值所在位置的右边。

 ( $ 1 \le n \le 10^6 $ )
 
# 思路

对于每一个 $ i $，用单调栈求出以 $ a_i $ 为最大值的区间的左端点最小值 $ l_i $ 和右端点最大值 $ r_i $，以及 $ i $ 左边的第一个比 $ a_i $ 小的数的位置 $ s_i $、$ i $ 右边的第一个比 $ a_i $ 小的位置 $ t_i $。接下来有两种计算方法：

一、枚举区间的左端点 $ j $ ( $ l_i \le j \lt i $ )，求出 $ j $ 到 $ i - 1 $ 之间的最小值的位置 $ p $。然后考虑右端点，一个区间**不合法**，当且仅当在 $ i + 1 $ 到右端点之间，存在比 $ a_p $ 小的数，即右端点大于等于 $ t_p $。用区间总数减去不合法的区间数量，即可求出合法的区间数量。

二、枚举区间的右端点 $ j $ ( $ i \lt j \le r_i $ )，求出 $ i + 1 $ 到 $ j $ 之间的最小值的位置 $ p $。然后考虑左端点，一个区间**合法**，当且仅当在左端点到 $ i - 1 $ 之间，存在比 $ a_p $ 小的数，即左端点小于等于 $ s_p $。**注意，$ j = i $ 的情况要单独计算。**

为了保证时间复杂度，我们将两种方法结合起来：如果 $ i - l_i \lt r_i - i $，使用方法一；否则使用方法二。

时间复杂度证明：按区间最大值从大到小的顺序计算。一个点每次被扫描到的时候，当前区间长度不会超过上一个区间长度的一半。因此，每个点最多被扫描 $ \log n $ 次。总时间复杂度为 $ O(n \log n) $。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

char buf[1000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 1000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
	if (flg) x = -x;
}

const int N = 1e6 + 5;
int a[N], sta[N], l[N], r[N], l2[N], r2[N];

inline void Chkmin(int &x, int y)
{
	if (y < x) x = y;
}

inline void Chkmax(int &x, int y)
{
	if (y > x) x = y;
}

int main()
{
	int n, Top = 0;
	read(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= n; ++i)
	{
		while (Top && a[sta[Top]] < a[i])
			--Top;
		if (Top) l[i] = sta[Top] + 1;
		else l[i] = 1;
		sta[++Top] = i;
	}
	Top = 0;
	for (int i = n; i; --i)
	{
		while (Top && a[sta[Top]] < a[i])
			--Top;
		if (Top) r[i] = sta[Top] - 1;
		else r[i] = n;
		sta[++Top] = i;
	}
	Top = 0;
	for (int i = 1; i <= n; ++i)
	{
		while (Top && a[sta[Top]] > a[i])
			--Top;
		if (Top) l2[i] = sta[Top] + 1;
		else l2[i] = 1;
		sta[++Top] = i;
	}
	Top = 0;
	for (int i = n; i; --i)
	{
		while (Top && a[sta[Top]] > a[i])
			--Top;
		if (Top) r2[i] = sta[Top] - 1;
		else r2[i] = n;
		sta[++Top] = i;
	}
	ll ans = 0ll;
	for (int i = 1; i <= n; ++i)
	{
		if (l[i] == i) continue;
		if (r[i] == i)
		{
			ans += i - l[i];
			continue;
		}
		if (i - l[i] < r[i] - i)
		{
			ans += (ll)(i - l[i]) * (r[i] - i + 1ll);
			int minp = i;
			for (int j = i - 1; j >= l[i]; --j)
			{
				if (a[j] < a[minp]) minp = j;
				if (r2[minp] < r[i]) ans -= r[i] - r2[minp];
			}
		}
		else
		{
			ans += i - l[i];
			int minp = i;
			for (int j = i + 1; j <= r[i]; ++j)
			{
				if (a[j] < a[minp]) minp = j;
				if (l2[minp] > l[i]) ans += l2[minp] - l[i];
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Leasier (赞：1)

笛卡尔树分治的比较符号两端写反导致 TLE 了一发 /cf

------------

考虑枚举最值所在位置 $x < y$ 计数，此时合法的 $[x, y] \subseteq [l, r]$ 需要满足：

- $l \in [\max(\operatorname{lmax}_x, \operatorname{lmin}_y), x]$，其中 $\operatorname{lmax}_i$ 表示 $p_i$ 左侧最后一个 $\leq$ 它者，$\operatorname{lmin}_i$ 表示 $p_i$ 左侧最后一个 $\geq$ 它者。
- $r \in [y, \max(\operatorname{rmax}_x, \operatorname{rmin}_y)]$，其中 $\operatorname{rmax}_i$ 表示 $p_i$ 右侧最后一个 $\leq$ 它者，$\operatorname{rmin}_i$ 表示 $p_i$ 右侧最后一个 $\geq$ 它者。

单调栈处理出 $\operatorname{lmin}_i, \operatorname{rmin}_i, \operatorname{lmax}_i, \operatorname{rmax}_i$ 后直接做是 $O(n^2)$ 的，显然不能接受。

考虑枚举 $x$，则 $y \in [x, \operatorname{rmax}_x]$。注意到这个东西的本质是枚举大根笛卡尔树上每个点的右子树。

注意到若我们只枚举左右儿子中较小的一侧，这个东西将变成笛卡尔树分治；而显然我们同样可以枚举 $y \in [\operatorname{lmax}_x, x]$ 并容斥出原本的答案。

时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

typedef long long ll;

int p[1000007], lmin[1000007], rmin[1000007], lmax[1000007], rmax[1000007];
stack<int> s;

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int main(){
	int n = read();
	ll ans = 0;
	for (register int i = 1; i <= n; i++){
		p[i] = read();
	}
	for (register int i = 1; i <= n; i++){
		while (!s.empty() && p[i] < p[s.top()]) s.pop();
		if (s.empty()){
			lmin[i] = 1;
		} else {
			lmin[i] = s.top() + 1;
		}
		s.push(i);
	}
	while (!s.empty()) s.pop();
	for (register int i = n; i >= 1; i--){
		while (!s.empty() && p[i] < p[s.top()]) s.pop();
		if (s.empty()){
			rmin[i] = n;
		} else {
			rmin[i] = s.top() - 1;
		}
		s.push(i);
	}
	while (!s.empty()) s.pop();
	for (register int i = 1; i <= n; i++){
		while (!s.empty() && p[i] > p[s.top()]) s.pop();
		if (s.empty()){
			lmax[i] = 1;
		} else {
			lmax[i] = s.top() + 1;
		}
		s.push(i);
	}
	while (!s.empty()) s.pop();
	for (register int i = n; i >= 1; i--){
		while (!s.empty() && p[i] > p[s.top()]) s.pop();
		if (s.empty()){
			rmax[i] = n;
		} else {
			rmax[i] = s.top() - 1;
		}
		s.push(i);
	}
	for (register int i = 1; i <= n; i++){
		if (i - lmax[i] <= rmax[i] - i){
			ans--;
			for (register int j = lmax[i]; j <= i; j++){
				int l = max(lmax[i], lmin[j]), r = min(rmax[i], rmin[j]);
				if (l <= j && i <= r) ans += (ll)(j - l + 1) * (r - i + 1);
			}
		} else {
			ans += (ll)(i - lmax[i] + 1) * (rmax[i] - i + 1);
			for (register int j = i; j <= rmax[i]; j++){
				int l = max(lmax[i], lmin[j]), r = min(rmax[i], rmin[j]);
				if (l <= i && j <= r) ans -= (ll)(i - l + 1) * (r - j + 1);
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

容易想到对一个数，找到它是最大值的区间，然后进行求解。

这样，一个最大数就把区间分成了两部分 $[l,pos-1],[pos+1,r]$。

如果我们枚举一遍的贡献，构造单增/单减的序列就直接 $O(n^2)$ 了，无法接受。

这时候，我参考了 [蒟蒻君HJT](https://www.luogu.com.cn/user/131591) 的 [题解](https://www.luogu.com.cn/blog/hokarikanae/cf1849e-max-to-the-right-of-min-ti-xie) 可以发现启发式分裂。

原来不知道，怎么办？

~~积累一下。~~

其实这个和启发式合并有一点像，如果分治是不等分的，枚举数量少的那一边，枚举量 $n$ 显然和区间长度 $L$ 满足 $n\le\dfrac{L}{2}$，这样复杂度就是 $O(n\log n)$。所以，可以类比想一下。

如果枚举左边，看右边的贡献。我们找到了 $i\sim pos$ 的最小值的位置 $minn$，然后知道了 $minn$ 右边第一个比它小的（如果没有就是 $\inf$ 或者 $n+1$）$R_{minn}$，那么，只要不选择 $R_{minn}$，$minn$ 的位置就是最小值，满足条件，所以方案总数是 $R_{minn}-pos$（取的区间是 $[pos,R_{minn}-1]$）。注意，这里需要从 $pos-1$ 开始枚举，否则会出现只有一个 $pos\sim pos$ 的情况，那么 $maxpos_{l,r}=minpos_{l,r}=pos$，和题目中要求的 $maspos_{l,r}>minpos_{l,r}$ 不符合。

注意，如果 $R_{minn}-1\ge r$，那么右边的贡献只能算到 $r$。

如果枚举右边，看左边的贡献。同理，对于最小值的位置 $minn$，需要找到左边第一个比自己小的 $L_{minn}$，那么可以选择的左端点就是 $l\sim L_{minn}$ 共 $L_{minn}-l+1$ 个。特判 $L_{minn}<l$ 的情况。

[code](https://codeforces.com/contest/1849/submission/239194778)

备注：本代码需要再洛谷 C++17 才可以跑过，用 C++14 会 MLE，原因（大概）是会递归导致 MLE。但是因为目前使用 C++14 的 NOI 系列赛事空间基本开到 512MB，因此应该没有关系。

---

## 作者：a_grain (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1849E)

------------
本蒟蒻在这里提供一种最普通的分治思路，即对于所有左右端点在区间 $[l,r]$ 时的答案，可以从 $[l,mid]$ 与 $[mid+1,r]$ 中得到，同时再去处理左端点在 $mid$ 前，右端点在 $mid+1$ 后的区间数量。

~~这有点太过于朴素了。~~

------------
处理时可能会遇到一些细节。

可以分成三种情况去考虑区间数量：
1. 最小值在 $mid$ 左边，最大值在 $mid+1$ 右边
2. 最小值在 $mid$ 左边，最大值在 $mid$ 左边
3. 最小值在 $mid+1$ 右边，最大值在 $mid+1$ 右边

这只要预处理一个右区间的前缀最大与最小值，再来一个左区间的后缀最大与最小值，然后再枚举左右其中一端点，然后二分一下就行了。

但这是 $O(n \log^2 n)$。

可以实现成 $O(n \log n)$，我这里贴出这种时间复杂度的代码。

~~码风恶臭~~

------------
**AC code**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int mi[N],ma[N],a[N],mi1[N],ma1[N];
int n,i;
int solve(int l,int r){
	if(l==r)return 0;
	int mid=l+r>>1;
	int ans=solve(l,mid)+solve(mid+1,r);
	mi[mid]=2e9;ma[r+1]=2e9;mi[r+1]=2e9;ma[mid]=0;
	for(int i=mid+1;i<=r;i++)mi[i]=min(mi[i-1],a[i]),ma[i]=max(ma[i-1],a[i]);//处理前缀 
	mi1[mid+1]=2e9;ma1[mid+1]=0;
	mi1[l-1]=0;ma1[l-1]=2e9;
	for(int i=mid;i>=l;i--)mi1[i]=min(mi1[i+1],a[i]),ma1[i]=max(ma1[i+1],a[i]);//处理后缀 
	int R1,R2,pos_ma,pos_mi,minn,maxx,L1,L2;
	L1=L2=mid+1;mi[r+1]=0;
	for(int i=mid;i>=l;i--){//处理第一种情况 
		minn=mi1[i];
		maxx=ma1[i];
		while(mi[L1]>minn)L1++;
		L1--;
		while(ma[L2]<maxx)L2++;
		ans+=max(0ll,L1-L2+1);
	}
	mi[r+1]=2e9;
	L1=L2=mid+1;minn=2e9;maxx=0;
	for(int i=mid;i>=l;i--){//处理第二种情况 
		if(minn>a[i])minn=a[i],pos_mi=i;
		if(maxx<a[i])pos_ma=i,maxx=a[i];
		while(mi[L1]>minn)L1++;
		L1--;
		while(ma[L2]<maxx)L2++;
		L2--;
		if(pos_ma>pos_mi)ans+=min(L1,L2)-mid;
	}
	minn=2e9;maxx=0;R1=R2=mid;
	for(int i=mid+1;i<=r;i++){//处理第三种情况 
		if(minn>a[i])minn=a[i],pos_mi=i;
		if(maxx<a[i])pos_ma=i,maxx=a[i];
		while(mi1[R1]>minn)R1--;
		R1++;
		while(ma1[R2]<maxx)R2--;
		R2++;
		if(pos_ma>pos_mi)ans+=mid-max(R1,R2)+1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	cout<<solve(1,n);
	return 0;
}
```


------------
# The End.

---

## 作者：Little09 (赞：0)

扫描线，从左往右扫 $r$。根据经典套路，我们可以用单调栈维护出对于每个左端点 $l$ 的这段区间的 max 和 min。考虑怎么维护答案？

在指针从 $r-1$ 移动到 $r$ 的过程中，我们发现变化只有 $a_r$ 可能在一些区间中担任 min 或 max，那么如果 $a_r$ 是 max，那么这个区间当前一定合法；如果 $a_r$ 是 min，那么当前一定不合法；如果 $a_r$ 既不担任 max 也不担任 min，那么这个区间的答案继承 $r-1$ 即可。

所以问题转化成区间 $01$ 赋值、全局求和，使用线段树解决。

---

## 作者：DiDi123 (赞：0)

提供一个不用分治的暴力做法。

首先我们还是用一下单调栈和 st 表，预处理出来区间的最小值、最大值以及第 $i$ 个数右边第一个比它大的数 $rb_i$ 和第一个比它小的数 $rs_i$。

然后我们直接暴力地枚举枚举 $i$ 作为区间的左端点，我们需要知道有多少个右端点符合要求。于是我们用两个变量 $l,r$，分别表示当前局面区间最大值的位置和区间最小值的位置。对于当前的局面，假设有 $l>r$，那么我们就需要将 $r$ 向右移动到第一个不符合条件的位置。注意这个时候 $r$ 维护的并不是 $i\sim l$ 的最小值，所以我们需要将 $r$ 变到 $rs_{\min(i\sim l)}$，这个时候我们把答案加上 $rs_{\min(i\sim l)}-\max(l,r)$。同理，当 $l<r$ 的时候，我们需要将 $l$ 向右移到第一个符合条件的位置，我们只需要将 $l$ 变到 $rb_{\max(i\sim r)}$ 即可。

然后我们发现这样的话程序会被卡T，于是我们再加一个小优化：对于所有的左端点，我们记录一下它这个左端点的答案，然后如果我们发现当前有 $l=r-1$，我们直接让 $f_i+=f_l$ 即可。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000010
typedef long long ll;
int mn[MAXN][21],mx[MAXN][21],n,p[MAXN],ps[MAXN],lg[MAXN],rb[MAXN],rs[MAXN],f[MAXN];
stack <int> st;
ll ans;
int qmn(int l,int r)
{
	int len=lg[r-l];
	return min(mn[l][len],mn[r-(1<<len)+1][len]);
}
int qmx(int l,int r)
{
	int len=lg[r-l];
	return max(mx[l][len],mx[r-(1<<len)+1][len]);
}
int main()
{
	cin.sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) cin>>p[i],ps[p[i]]=i,mn[i][0]=mx[i][0]=p[i];
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
		}
	for(int i=1;i<=n;i++)
	{
		while(st.size() && p[i]>p[st.top()])
			rb[st.top()]=i,st.pop();
		st.push(i);
	}
	while(st.size()) rb[st.top()]=n+1,st.pop();
	for(int i=1;i<=n;i++)
	{
		while(st.size() && p[i]<p[st.top()])
			rs[st.top()]=i,st.pop();
		st.push(i);
	}
	while(st.size()) rs[st.top()]=n+1,st.pop();
	for(int i=n-1;i>=1;i--)
	{
		int l=i,r=i+1; //l:max r:min
		if(p[l]>p[r]) l=rb[l];
		while(l<=n && r<=n)
		{
			int tr=rs[ps[qmn(i,l)]];
			f[i]+=tr-max(l,r),r=tr;
			if(l==r-1) 
			{
				f[i]+=f[l];
				break;
			}
			if(r<=n) l=rb[ps[qmx(i,r)]];
		}
		ans+=f[i];
	}
	cout<<ans;
}
```


---

