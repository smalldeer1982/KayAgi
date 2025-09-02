# [ABC282Ex] Min + Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc282/tasks/abc282_h

$ 2 $ つの長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ および $ B\ =\ (B_1,\ B_2,\ \ldots,\ B_N) $ が与えられます。

$ 1\ \leq\ l\ \leq\ r\ \leq\ N $ を満たす整数の組 $ (l,\ r) $ であって下記の条件を満たすものの個数を出力してください。

- $ \min\lbrace\ A_l,\ A_{l+1},\ \ldots,\ A_r\ \rbrace\ +\ (B_l\ +\ B_{l+1}\ +\ \cdots\ +\ B_r)\ \leq\ S $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ S\ \leq\ 3\ \times\ 10^{14} $
- $ 0\ \leq\ A_i\ \leq\ 10^{14} $
- $ 0\ \leq\ B_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1\ \leq\ l\ \leq\ r\ \leq\ N $ を満たす整数の組 $ (l,\ r) $ であって問題文中の条件を満たすものは、 $ (1,\ 1),\ (1,\ 2),\ (2,\ 2),\ (2,\ 3),\ (3,\ 3),\ (4,\ 4) $ の $ 6 $ 個です。

## 样例 #1

### 输入

```
4 15
9 2 6 5
3 5 8 9```

### 输出

```
6```

## 样例 #2

### 输入

```
15 100
39 9 36 94 40 26 12 26 28 66 73 85 62 5 20
0 0 7 7 0 5 5 0 7 9 9 4 2 5 2```

### 输出

```
119```

# 题解

## 作者：Galex (赞：13)

一种很新的套路，至少我从来没见过。

根据最小值分治。

### 具体过程

当我们求解区间 $[L,R]$ 的答案时，可以先找到区间中最小值所在的位置 $M$，然后求对于所有 $L \le l \le M \le r \le R$ 的合法区间数量，最后递归到 $[L,M-1]$ 和 $[M+1,R]$。

#### 找区间中最小值所在的位置

方法很多，这里我用的是 st 表。

#### 求对于所有 $L \le l \le M \le r \le R$ 的合法区间数量

当我们确定了 $l$ 和 $r$ 的其中一个时，另一个可以通过二分直接得到，所以我们枚举值域更小的那个。即：若 $M-L<R-M$，枚举 $l$，否则，枚举 $r$。

#### 复杂度

每次枚举的区间对于上次枚举的来说至少是减半的，所以，每个位置顶多被枚举 $\log n$ 次，总复杂度是 $O(n \log^2 n)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}
 
int n, S;
int a[200005], b[200005], s[200005];
int pos[200005][20];
 
#define pw(x) (1 << (x))
#define merge(x, y, i) (a[pos[x][i]] < a[pos[y][i]] ? pos[x][i] : pos[y][i])
 
void build() {
	for (int i = 1; i <= n; i++)
		pos[i][0] = i;
	for (int j = 1; pw(j) <= n; j++)
		for (int i = 1; i + pw(j) - 1 <= n; i++)
			pos[i][j] = merge(i, i + pw(j - 1), j - 1);
}
 
int qry(int l, int r) {
	int i = log(r - l + 1) / log(2);
	return merge(l, r - pw(i) + 1, i);
}
 
int ans = 0;
 
int calcl(int x, int L, int R, int S) {
	int l = L - 1, r = R + 1;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (s[mid] - s[x - 1] <= S)
			l = mid;
		else
			r = mid;
	}
	return l;
}
 
int calcr(int x, int L, int R, int S) {
	int l = L - 1, r = R + 1;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (s[x] - s[mid - 1] <= S)
			r = mid;
		else
			l = mid;
	}
	return r;
}
 
void Solve(int l, int r) {
	if (l > r)
		return ;
	int mid = qry(l, r);
	if (mid - l < r - mid)
		for (int i = l; i <= mid; i++)
			ans += calcl(i, mid, r, S - a[mid]) - mid + 1;
	else
		for (int i = mid; i <= r; i++)
			ans += mid + 1 - calcr(i, l, mid, S - a[mid]);
	Solve(l, mid - 1), Solve(mid + 1, r);
}
 
signed main() {
	n = read(), S = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		b[i] = read(), s[i] = s[i - 1] + b[i];
	build();
	Solve(1, n);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：lzyqwq (赞：9)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17756459.html)**

两只 $\log$ 跑得快，序列分治真可爱。

**[洛谷](https://www.luogu.com.cn/problem/AT_abc282_h) [AT](https://atcoder.jp/contests/abc282/tasks/abc282_h)**

> - 给出两个长为 $n$ 的序列 $a,b$ 和常数 $S$，求有多少个区间 $[l,r]\,(1\le l\le r\le n)$，满足：
>
>   $$\min\limits_{i=l}^r a_i+\sum_{j=l}^rb_j\le S$$
>
> - $n\le 2\times 10^5$。

考虑分治。设当前分治区间为 $[l,r]$，分治中点 $mid=\left\lfloor\dfrac{l+r}{2}\right\rfloor$。

考虑如何统计跨过中点的区间个数。枚举左端点 $i$，同时记录 $s=\sum\limits_{x=i}^{mid}b_x$ 和 $minn=\min\limits_{y=i}^{mid} a_y$。求出有多少个合法的右端点 $j$。

对于 $(mid,r]$ 这部分区间的所有 $j$，预处理 $sum_j=\sum\limits_{u=mid+1}^j b_u$，$pre_j=\min\limits_{v=mid+1}^j a_v$。

把右端点 $j$ 分成两种，分别统计：

- $pre_j\ge minn$，则符合条件的区间满足 $s+sum_j+minn\le S$，那么统计有多少 $j$ 满足 $sum_j\le S-s-minn$。

- $pre_j< minn$，则符合条件的区间满足 $s+sum_j+pre_j\le S$，那么统计有多少 $j$ 满足 $sum_j+pre_j\le S-s$。

考虑**从右往左**枚举左端点 $i$，不难发现**可以找到一个分界点 $\boldsymbol k$ 使得当 $\boldsymbol{j\in (mid,k)}$ 时，区间满足第一种情况；当 $\boldsymbol{j\in[k,r]}$ 时，区间满足第二种情况。且随着 $\boldsymbol{i}$ 的减小，$\boldsymbol k$ 单调不降。**

使用平衡树 $t_1,t_2$ 分别维护 $(mid,k)$ 中 $sum_j$ 的权值集合和 $[k,r]$ 中 $sum_j+pre_j$ 的权值集合。分界点 $k$ 右移时（接下来的 $k$ 是右移前的 $k$），在 $t_1$ 中插入 $sum_k$，在 $t_2$ 中删除 $sum_k+pre_k$。可以完成⌈查询集合内有多少数不超过某个定值⌋这个操作。

有人可能会说平衡树小题大做，但是 `__gnu_pbds::tree` 真的很方便。

时间复杂度为 $\mathcal{O}(n\log^2 n)$，空间复杂度为 $\mathcal{O}(n)$。

**[评测记录（含代码）](https://atcoder.jp/contests/abc282/submissions/46443860)**

代码还是贴个图吧，让大家感受一下 $33$ 行 $1.33\text{KB}$ 小清新代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/tt2mt9k2.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)

---

## 作者：Zpair (赞：9)

考虑固定一个右端点去统计左端点。

把两个贡献分开统计，后缀最小值直接单调栈，栈里面维护每一段后缀最小值相等的区间，则每次弹栈都相当于一段区间加，考虑操作次数。

称每次插入的时候对应的那一段为本段，则不难发现每一段作为非本段只会被在弹栈时区间加一次，所以操作次数仍为线性。

区间和显然也是区间加。

然后就是分块经典问题：区间加，区间查询小于等于 $S$ 的个数。

设块长为 $B$ 。

对于每一块维护一个排序后的序列。

查询整块暴力二分散块直接暴力时间复杂度为 $O(\frac n B \log B + B)$ 。

修改整块打标记，散块时先在排完序的序列中提取出区间加所涉及的数，以及不涉及的数，之后等价于将两个有序数列归并，时间复杂度为 $O(\frac n B + B)$ 。

令：$B=\sqrt {n \log n}$ ，则总时间复杂度为 $O(n \sqrt {n \log n})$ ，可以通过。

注意区间加的次数前面有一个常数，而区间加时散块重构较慢，所以可以调小 $B$ 来优化常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
int B,n;ll a[N],c[N],S;
int b[N];
#define mp(x) ((x-1)/B)
#define bg(x) ((x)*B+1)
#define ed(x) (min(((x)+1)*B,n))
int aa[N],bb[N];
void rebuild(int x,int y,ll v,int z){
	for(int i=bg(z);i<=ed(z);++i)
		a[i]+=c[z];
	int sz1=0,sz2=0;
	for(int i=bg(z);i<=ed(z);++i){
		if(b[i]>=x&&b[i]<=y)
			bb[sz2++]=b[i];
		else aa[sz1++]=b[i];
	}
	for(int i=x;i<=y;++i)a[i]+=v;
	int tp1=0,tp2=0;
	for(int i=bg(z);i<=ed(z);++i){
		if(tp2==sz2||(tp1!=sz1&&a[aa[tp1]]<=a[bb[tp2]]))
			b[i]=aa[tp1],tp1++;
		else b[i]=bb[tp2],tp2++;
	}
	c[z]=0;
}
void add(int x,int y,ll v){
	if(mp(x)==mp(y))
		rebuild(x,y,v,mp(x));
	else{
		rebuild(x,ed(mp(x)),v,mp(x));
		rebuild(bg(mp(y)),y,v,mp(y));
		for(int i=mp(x)+1;i<mp(y);++i)
			c[i]+=v;
	}
}//区间加
int qry(int x,int y){
	if(mp(x)==mp(y)){
		int ans=0;
		for(int i=x;i<=y;++i)
			if(a[i]+c[mp(x)]<=S)ans++;
		return ans;
	}
	else{
		int ans=0;
		for(int i=x;i<=ed(mp(x));++i)
			if(a[i]+c[mp(x)]<=S)ans++;
		for(int i=bg(mp(y));i<=y;++i)
			if(a[i]+c[mp(y)]<=S)ans++;
		for(int i=mp(x)+1;i<mp(y);++i){
			int l=bg(i),r=ed(i),mid=(l+r)>>1,k=bg(i)-1;
			while(l<=r){
				if(a[b[mid]]+c[i]<=S)
					k=mid,l=mid+1;
				else r=mid-1;
				mid=(l+r)>>1;
			}
			ans+=k-bg(i)+1;
		}
		return ans;
	}
}
int ql[N],qr[N],tot;
ll qv[N];
ll Av[N],Bv[N];
void ins(int x){
	add(x,x,Av[x]);
	while(tot&&qv[tot]>=Av[x]){
		add(ql[tot],qr[tot],Av[x]-qv[tot]);
		tot--;
	}
	ql[tot+1]=qr[tot]+1,qr[tot+1]=x,qv[tot+1]=Av[x],tot++;
	add(1,x,Bv[x]);
}
int main(){
	cin>>n>>S;
	B=sqrt(n*log2(n))/4+1;
	for(int i=1;i<=n;++i)
		scanf("%lld",&Av[i]);
	for(int i=1;i<=n;++i)
		scanf("%lld",&Bv[i]);
	for(int i=1;i<=n;++i)
		b[i]=i;
	ll ans=0;
	for(int i=1;i<=n;++i){
		ins(i);
		ans+=qry(1,i);
	}
	cout<<ans;
}
```

喜提最劣解（不过好像还可以卡卡的说

---

## 作者：ran_qwq (赞：8)

观察式子，当一个端点固定时，随着区间长度的增加，$\sum\limits_{i=l}^r B_i$ 单调递增，然而 $\min\limits_{i=l}^rA_i$ 单调递减。所以直接扫行不通。

考虑分治（我也不知道怎么想到的，感觉好神奇）。设一个区间 $[l,r]$ 的中点为 $mid$，则该区间的合法子区间数量分为三部分：

1. 区间 $[l,mid]$ 的合法子区间数量。

1. 区间 $[mid+1,r]$ 的合法子区间数量。

1. 左端点在 $[l,mid]$ 间，右端点在 $[mid+1,r]$ 间的合法子区间数量。

前两种可以继续分治。当 $l=r$ 时，只需判断 $A_l+B_l$ 是否 $\le m$ 即可。

第三种比较麻烦，又分为两部分：

- 最小值取在 $[l,mid]$ 间的数量。

- 最小值取在 $[mid+1,r]$ 间的数量。

这两种计算方式一样，我们来看前者。

进一步观察式子，发现当一个端点固定，以及 $\min\limits_{i=l}^rA_i$ 确定时，随着区间长度的增加，$\sum\limits_{i=l}^r B_i+\min\limits_{i=l}^rA_i$ 就是单调递增的。

先进行一些定义：

- 设合法区间为 $[i,j](l\le i\le mid,mid<j\le r)$。

- 设区间 $[i,mid](i\le mid)$ 的最小值为 $m1_i$。

- 设区间 $[mid+1,i](i>mid)$ 的最小值为 $m2_i$。

- 设区间 $[i,mid](i\le mid)$ 的最小值为 $s1_i$。

- 设区间 $[mid+1,i](i>mid)$ 的最小值为 $s2_i$。

枚举左端点 $i$，因为最小值取在 $[l,mid]$ 间，所以 $m1_i<m2_j$（否则最小值就在 $[mid+1,r]$ 间了）。

因为 $j$ 越大 $m2_j$ 越小，所以所有 $m1_i<m2_j$ 的 $j$ 都在一个区间 $[mid+1,pos]$ 内，其中 $pos$ 是使得 $m1_i<m2_{pos}$ 最大的 $pos$。

又因为 $i$ 越小 $m1_i$ 也越小，所以 $m2_j$ 的下界也越小，$j$ 可以取到更远的位置。换句话说，$i$ 越小，$pos$ 越大。

有这个性质，我们就可以双指针维护 $pos$。

我们还要保证 $\min\limits_{k=i}^jA_k+\sum\limits_{k=i}^jB_k\le S$，即 $\min(m1_i,m2_j)+s1_i+s2_j\le S$，所以不是所有 $mid<j\le pos$ 的 $j$ 都可以取到。

因为 $m1_i<m2_j$，所以式子可以进一步转化为 $s2_j\le S-m1_i-s1_i$，左边是未知的，右边是已知的。

显然 $s2_j$ 是单调递增的，二分最大的 $j$，贡献即为 $j-mid$。

最小值在 $[mid+1,r]$ 内同理，这里不多赘述。

每层处理总时间复杂度 $O(n)$，层数一个 $\log$，二分又一个 $\log$，时间复杂度 $O(n\log^2n)$。

```cpp
int n,m,ans,a[N],b[N],sumL[N],sumR[N];
void solve(int l,int r)
{
	if(l==r) {ans+=a[l]+b[l]<=m;return;}
	int mid=l+r>>1;solve(l,mid),solve(mid+1,r),sumL[mid+1]=sumR[mid]=0;
	for(int i=mid;i>=l;i--) sumL[i]=sumL[i+1]+b[i];
	for(int i=mid+1;i<=r;i++) sumR[i]=sumR[i-1]+b[i];
	for(int i=mid,j=mid,mn=INF;i>=l;i--)
	{
		mn=min(mn,a[i]);
		while(j<r&&a[j+1]>mn) j++;
		if(j==mid) continue;
		int s=mid+1,t=j;
		while(s<=t)
		{
			int p=s+t>>1;
			if(sumL[i]+sumR[p]+mn>m) t=p-1;
			else s=p+1;
		}
		ans+=t-mid;
	}
	for(int i=mid+1,j=mid+1,mn=INF;j<=r;j++)
	{
		mn=min(mn,a[j]);
		while(i>l&&a[i-1]>=mn) i--;
		if(i==mid+1) continue;
		int s=i,t=mid;
		while(s<=t)
		{
			int p=s+t>>1;
			if(sumL[p]+sumR[j]+mn<=m) t=p-1;
			else s=p+1;
		}
		ans+=mid-t;
	}
}
void solve()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	solve(1,n),write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

---

## 作者：shinkuu (赞：4)

昨天刚做了这个 trick 的[板子题](https://www.luogu.com.cn/problem/CF1156E)，今天竟然又来一道。

涉及到区间 $\min$ 和计数，一般的方法是比较难做的。所以可以从笛卡尔树和单调栈的角度入手。这题考虑单调栈，固定最小值位置后，就要计算有多少个跨过该位置，并且最小值在该位置上，还满足题目要求的区间。

解决这个问题可以考虑用单调栈处理出左右第一个比它小的数，然后枚举其中一侧，另一侧用二分找到可行区间。问题就在于应该怎么枚举。我们先猜测每次都枚举更短的那一侧是正确的。交上去，发现过了。

下面浅浅证明一下：设 $T(n)$ 为序列长度为 $n$ 时的复杂度。则有 $T(n)=\max\limits_{2\times x\le n} (T(x)+T(n-x)+O(x))$。容易发现，每个位置如果产生了一次贡献，则它所在的区间长度至少减半，所以每个位置最多产生 $O(\log n)$ 次贡献。所以复杂度为 $O(n\log n)$，再加上二分的复杂度，总复杂度即为 $O(n\log^2n)$。

还有一个在这种单调栈处理中常用的技巧：当遇到重复数字又不想算重时，可以考虑一边取等，一边不取的做法，具体可以参考代码。

code：

```cpp
int n,top,b[N],st[N],f[N],g[N];
ll m,a[N],s[N];
void Yorushika(){
	scanf("%d%lld",&n,&m);
	rep(i,1,n)scanf("%lld",&a[i]);
	rep(i,1,n)scanf("%d",&b[i]),s[i]=s[i-1]+b[i];
	a[0]=a[n+1]=-1;
	rep(i,1,n+1){
		while(top&&a[st[top]]>=a[i])f[st[top--]]=i;
		st[++top]=i;
	}
	top=0;
	drep(i,n,0){
		while(top&&a[st[top]]>a[i])g[st[top--]]=i;
		st[++top]=i;
	}
	ll ans=0;
	rep(i,1,n){
		if(i-g[i]<=f[i]-i){
			rep(j,g[i],i-1){
				ll x=m+s[j]-a[i];
				int p=upper_bound(s,s+n+1,x)-s-1;
				if(p<i)continue;
				p=min(p,f[i]-1);
				ans+=p-i+1;
			}
		}else{
			rep(j,i,f[i]-1){
				ll x=s[j]+a[i]-m;
				int p=lower_bound(s,s+n+1,x)-s;
				if(p>=i)continue;
				p=max(p,g[i]);
				ans+=i-p;
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Phartial (赞：4)

考虑直接 CDQ 分治。对于一个区间 $[l,r]$，从中点 $m$ 向两边求出 $al_i=\min_{j=i}^ma_j$，$bl_i=\sum_{j=i}^mb_j$，$ar_i=\min_{j=m+1}^ia_j$，$br_i=\sum_{j=m+1}^ib_j$。

对跨越了中点的点对 $i,j$，约束条件变成 $\min(al_i,ar_j)+bl_i+br_j\le S$。

分类讨论：

1. $al_i\ge ar_j$：$ar_j+bl_i+br_j\le S$，即 $ar_j+br_j\le S-bl_i$，可以使用树状数组简单维护。
2. $al_i< ar_j$：$al_i+bl_i+br_j\le S$，即 $br_j\le S-al_i-bl_i$，也可以使用树状数组简单维护。

综上，直接用树状数组计算跨越中点的点对数量，就变成了经典 CDQ 了。时间复杂度 $O(n\log^2n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n;
LL s, a[kN], b[kN], ans, al[kN], bl[kN], ar[kN], br[kN], dl[kN], dr[kN];
vector<LL> p[2];
LL bc[2][kN];

void Ad(int o, int x, LL v) {
  for (; x <= p[o].size(); x += x & -x) {
    bc[o][x] += v;
  }
}
LL Sm(int o, int x) {
  LL s = 0;
  for (; x; x -= x & -x) {
    s += bc[o][x];
  }
  return s;
}
void Z(int o, int x) {
  for (; x <= p[o].size(); x += x & -x) {
    bc[o][x] = 0;
  }
}
int G(int o, LL x) {
  return lower_bound(p[o].begin(), p[o].end(), x) - p[o].begin() + 1;
}
void S(int l, int r) {
  if (l == r) {
    ans += a[l] + b[l] <= s;
    return;
  }
  int m = l + r >> 1;
  S(l, m), S(m + 1, r);
  // ===== 计算 al,bl 并排序 =====
  al[m] = a[m], bl[m] = b[m];
  for (int i = m - 1; i >= l; --i) {
    al[i] = min(al[i + 1], a[i]), bl[i] = bl[i + 1] + b[i];
  }
  iota(dl + l, dl + m + 1, l);
  sort(dl + l, dl + m + 1, [](int i, int j) { return al[i] < al[j]; });
  // ===== 计算 ar,br 并排序 =====
  ar[m + 1] = a[m + 1], br[m + 1] = b[m + 1];
  for (int i = m + 2; i <= r; ++i) {
    ar[i] = min(ar[i - 1], a[i]), br[i] = br[i - 1] + b[i];
  }
  iota(dr + m + 1, dr + r + 1, m + 1);
  sort(dr + m + 1, dr + r + 1, [](int i, int j) { return ar[i] < ar[j]; });
  // ===== 离散化 =====
  p[0].clear(), p[1].clear();
  for (int i = l; i <= m; ++i) {
    p[0].push_back(s - bl[i]);
    p[1].push_back(s - al[i] - bl[i]);
  }
  for (int i = m + 1; i <= r; ++i) {
    p[0].push_back(ar[i] + br[i]);
    p[1].push_back(br[i]);
  }
  sort(p[0].begin(), p[0].end());
  int l0 = unique(p[0].begin(), p[0].end()) - p[0].begin();
  p[0].resize(l0);
  sort(p[1].begin(), p[1].end());
  int l1 = unique(p[1].begin(), p[1].end()) - p[1].begin();
  p[1].resize(l1);
  // ===== 统计点对数量 =====
  for (int i = m + 1; i <= r; ++i) {
    Ad(1, G(1, br[i]), 1);
  }
  int j = m + 1;
  for (int i = l; i <= m; ++i) {
    for (; j <= r && ar[dr[j]] <= al[dl[i]]; ++j) {
      Ad(0, G(0, ar[dr[j]] + br[dr[j]]), 1);
      Ad(1, G(1, br[dr[j]]), -1);
    }
    ans += Sm(0, G(0, s - bl[dl[i]])) + Sm(1, G(1, s - al[dl[i]] - bl[dl[i]]));
  }
  // ===== 清零 =====
  for (int k = m + 1; k <= r; ++k) {
    Z(0, G(0, ar[k] + br[k]));
    Z(1, G(1, br[k])); 
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> s;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  S(1, n);
  cout << ans;
  return 0;
}
```

---

## 作者：__stick (赞：3)

## 题意
给出序列 $a,b$，求出满足：
$$
\sum_{i=l}^rb_i+\min_{i=l}^r a_i\le s
$$
的 $(l,r)$ 数量，其中 $1\le l\le r\le n$。
## 思路

算是比较套路的题了，区间问题想一下分治总之没有错。

我们对序列分治，然后处理出来分治中点到左右端点的 $a$ 的前缀最小值，$b$ 的前缀和。

然后当前分治区间内的问题就变成了：
$$
\min(mmin_i,mmin_j)+sum_i+sum_j\le s,i\in[l,mid],j\in[mid+1,r]
$$

的 $(i,j)$ 个数。

其中 $mmin$ 和 $sum$ 就表示从分治中点到位置 $i$ 的前缀最小值和前缀和（当然，对于左半区间其实是后缀）。

我们盯一下上面的柿子，发现只需要去掉 $\min$ 就会非常好做。

由于 $b_i\ge0$ 所以 $sum$ 其实是单调的，而 $mmin$ 肯定是单调的，我们枚举 $i$ ，二分出来 $mmin_j\ge mmin_i$ 的 $j$ 的位置，然后对于小于当前位置的 $j$ ，$mmin_j\ge mmin_i $ 一定成立。所以柿子就是：
$$
mmin_i+sum_i+sum_j\le s,j\in[mid+1,p]
$$
$p$ 是满足 $mmin_j\ge mmin_i$ 的最靠后的位置。

$i$ 此时已经确定了，二分一下 $j$ 就行了。

这里追求效率可以将第一次二分改为双指针扫描。
## code
```cpp
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vii; 
#define X first
#define Y second
int mod;
const int MAXN=2e5+10;
int n;ll s;
ll a[MAXN];
int b[MAXN];
ll mmin[MAXN],sum[MAXN];
ll ans=0;
void solve(int l,int r)
{
	if(l==r)return ans+=a[l]+b[r]<=s,void();
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	mmin[mid+1]=a[mid+1],sum[mid+1]=b[mid+1];
	for(int i=mid+2;i<=r;i++)mmin[i]=min(mmin[i-1],a[i]);
	for(int i=mid+2;i<=r;i++)sum[i]=sum[i-1]+b[i];
	mmin[mid]=a[mid],sum[mid]=b[mid];
	for(int i=mid-1;i>=l;i--)mmin[i]=min(mmin[i+1],a[i]);
	for(int i=mid-1;i>=l;i--)sum[i]=sum[i+1]+b[i];
	vector<ll>L,R;
	for(int i=mid+1;i<=r;i++) R.push_back(sum[i]);
	for(int i=mid;i>=l;i--) L.push_back(sum[i]);
	int i=l,j=r;
	while(i<=mid||j>mid)
	{
		if(j<=mid||mmin[i]<=mmin[j]&&i<=mid)
		{
			int p=upper_bound(R.begin(),R.begin()+j-mid,s-mmin[i]-sum[i])-R.begin();
			ans+=p;
			i++;
		}
		else
		{
			int p=upper_bound(L.begin(),L.begin()+mid-i+1,s-mmin[j]-sum[j])-L.begin();
			ans+=p;
			j--;
		}
	}
}
signed main()
{	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	solve(1,n);cout<<ans<<'\n';
	return 0;
} 
```



---

## 作者：analysis (赞：2)

个人感觉知道是分治后还是比较好做的。

这里也可以 CDQ 分治，但是笛卡尔树分治应该是更好想一点的。

对于区间 $[L,R]$，我们找到其 $A_i$ 最小的点 $x$。

递归处理 $[L,x-1]$，$[x+1,R]$。

接下来考虑 $(i,j)$，$i \leq x \leq j$。

显然此区间合法的条件为：

$$
\sum_{k=i}^{j}B_k + A_x \leq s
$$

由于笛卡尔树分治的不平衡性，我们应枚举较小区间。

例如：$x-i+1 \leq j-x+1$，此时我们应当枚举 $x$ 到 $i$，用二分法确定最大的 $j$，然后统计答案。

然后就没了，时间复杂度应为 $O(n\log^2{n})$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s;
int a[200005],b[200005],sum[200005];
int ans;
int mn[200005][20],ps[200005][20];
void solve(int l,int r)
{
    if(l > r)
    {
        return;
    }
    if(l == r)return ans += (b[l] + a[l] <= s),void(0);
    int vv = log2(r - l + 1);
    int p1 = l,p2 = r - (1 << vv) + 1;
    int mid,minn;
    if(mn[p1][vv] < mn[p2][vv])
    {
        mid = ps[p1][vv];
        minn = mn[p1][vv];
    }
    else
    {
        mid = ps[p2][vv];
        minn = mn[p2][vv];
    }
    solve(l,mid-1);
    solve(mid+1,r);
    if(mid - l + 1 <= r - mid + 1)
    {
        int sb = 0;
        for(int i=mid;i>=l;i--)
        {
            sb += b[i];
            int L = mid-1,R = r;
            while(L < R)
            {
                int Mid = (L + R + 1) >> 1;
                if(sum[Mid] - sum[mid] + sb + minn <= s)L = Mid;
                else R = Mid - 1;
            }
            ans += R - mid + 1;
        }
    }
    else
    {
        int sb = 0;
        for(int i=mid;i<=r;i++)
        {
            sb += b[i];
            int L = l,R = mid+1;
            while(L < R)
            {
                int Mid = (L + R) >> 1;
                if(sum[mid-1] - sum[Mid-1] + sb + minn <= s)R = Mid;
                else L = Mid + 1;
            }
            ans += mid - L + 1;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
        mn[i][0] = a[i];
        ps[i][0] = i;
    }
    for(int j=1,mid=1;j<=18;j++,mid<<=1)
    {
        for(int i=1;i<=n;i++)
        {
            if(i + mid > n)mn[i][j] = mn[i][j-1],ps[i][j] = ps[i][j-1];
            else if(mn[i][j-1] < mn[i+mid][j-1])
            {
                mn[i][j] = mn[i][j-1],ps[i][j] = ps[i][j-1];
            }
            else mn[i][j] = mn[i+mid][j-1],ps[i][j] = ps[i+mid][j-1];
        }
    }
    for(int i=1;i<=n;i++)
    {
        cin >> b[i];
        sum[i] = sum[i-1] + b[i];
    }
    solve(1,n);
    cout<<ans;
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：2)

按最小值分治。

考虑统计 $l,r$ 内跨过最小值位置 $m$ 的满足条件的区间个数。

遍历 $[l,m],[m,r]$ 中较小的一个区间。设 $s_i=\sum\limits_{j=1}^i b_j$。

- $m-l\le r-m$：遍历左端点 $i\in[l,m]$，则右端点 $j\in[m,r]$ 满足 $a_m+\sum\limits_{x=i}^jb_x=a_m+s_j-s_{i-1}\le S$，即 $s_j\le S+s_{i-1}-a_m$。

二分最大的 $j_0$，则 $j\in[m,j_0]$ 都满足条件，答案加上 $j_0-m+1$。

- $m-l>r-m$：遍历右端点 $i\in[m,r]$，则左端点 $j\in[l,m]$ 满足 $a_m+\sum\limits_{x=j}^ib_x=a_m+s_i-s_{j-1}\le S$，即 $s_{j-1}\ge s_i+a_m-S$。

二分最小的 $j_0$，则 $j\in[j_0,m]$ 都满足条件，答案加上 $m-j_0+1$。

总复杂度 $O(n\log^2n)$。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
long long s, q, a[200050], b[200050], f[20][200050];
long long Q(int l, int r)
{
    int k = __lg(r - l + 1);
    return a[f[k][l]] < a[f[k][r - (1 << k) + 1]] ? f[k][l] : f[k][r - (1 << k) + 1];
}
void F(int l, int r)
{
    if (l > r)
        return;
    int m = Q(l, r);
    if (m - l <= r - m)
        for (int i = l, j; i <= m; ++i)
        {
            j = upper_bound(b + 1, b + r + 1, s + b[i - 1] - a[m]) - b - 1;
            if (j >= m)
                q += j - m + 1;
        }
    else
        for (int i = m, j; i <= r; ++i)
        {
            j = lower_bound(b + l - 1, b + n + 1, b[i] + a[m] - s) - b + 1;
            if (j <= m)
                q += m - j + 1;
        }
    F(l, m - 1);
    F(m + 1, r);
}
int main()
{
    scanf("%d%lld", &n, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i), f[0][i] = i;
    for (int i = 1; 1 << i <= n; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            f[i][j] = a[f[i - 1][j]] < a[f[i - 1][j + (1 << i - 1)]] ? f[i - 1][j] : f[i - 1][j + (1 << i - 1)];
    for (int i = 1; i <= n; ++i)
        scanf("%d", b + i), b[i] += b[i - 1];
    F(1, n);
    printf("%lld", q);
    return 0;
}
```


---

## 作者：zifanwang (赞：2)

考虑对于每一个 $A_i$，找到左边第一个小于和右边第一个不大于该值的数的下标 $L_i,R_i$，那么 $A_i$ 就是所有满足 $L_i<l\le i\le r<R_i$ 的区间 $[l,r]$ 的最小值。

如果 $i-L_i<R_i-i$ 则枚举 $l$，否则枚举 $r$，再二分找到满足要求的另一个端点的区间即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,tot,q[mxn],l[mxn],r[mxn],rt[mxn];
ll s,mx,ans,a[mxn],b[mxn];
signed main(){
	scanf("%d%lld",&n,&s);
	rep(i,1,n)scanf("%lld",&a[i]);
	rep(i,1,n)scanf("%lld",&b[i]),b[i]+=b[i-1],mx=max(mx,b[i]);
	rep(i,1,n){
		while(tot&&a[i]<a[q[tot]])tot--;
		l[i]=q[tot];
		q[++tot]=i;
	}
	tot=0,q[0]=n+1;
	drep(i,n,1){
		while(tot&&a[i]<=a[q[tot]])tot--;
		r[i]=q[tot];
		q[++tot]=i;
	}
	rep(i,1,n){
		l[i]++,r[i]--;
		if(i-l[i]<r[i]-i){
			rep(j,l[i],i)if(b[i]<=s-a[i]+b[j-1]){
				ans+=upper_bound(b+i,b+r[i]+1,s-a[i]+b[j-1])-b-i;
			}
		}else{
			rep(j,i,r[i])if(a[i]+b[j]-s<=b[i-1]){
				ans+=i-(lower_bound(b+l[i]-1,b+i,a[i]+b[j]-s)-b);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

- # 前言

  为什么这道题放了暴力没有放 $\log(n)^3$ 啊！神奇。这道题我用了一个与其他分支有点不同的做法，比其他的好想但是码量要大一点。

  # 思路

  首先对于这道题可以发现对于两个值一个是单调不递减的一个是单调不递增的所以没办法直接算，那么我们考虑固定一个，所以这里我们可以用分治的做法对于那些会跨越 $mid$ 的区间进行计算即可。这里需要分类讨论。

  - 当最小值在 $l\sim mid$ 中时我们考虑去枚举左端点 $i$ 然后我们能得到 $l\sim mid$ 的最小值 $x$，然后我们再算出来一个最大的 $x1$ 使得 $i\sim x1$ 的最小值也为 $x$ 即可，这个也已用 ST 表和二分搞，我们还需要对于区间和算出来一个最大的 $x2$ 使得 $\sum_{j=l}^{x2} b_j+x\leq s$ 这个也可以用前缀和加二分搞定，那么右端点能扩展到的区间便为 $mid+1\sim \min(x1,x2)$。

  - 对于最小值在 $mid+1\sim r$ 中时其实也和上面一种差不了多少，也是分别求出 $y1$ 和 $y2$ 那么能满足条件的区间便是 $\max(y1,y2)\sim mid$。

  这里还有一种情况需要考虑。

  ```
  3
  0 0 0
  ```

  我们可以发现对于这种情况当 $l=1,r=3$ 时我们算最小值在左边和最小值在右边都会将区间 $1\sim 3$ 算入，那么我们只需要将这种情况去除即可，就是在枚举左端点 $i$ 之后算出 $z1$ 和 $z2$ 使得 $mid+1\sim z1$ 的最小值也为 $i\sim mid$ 的最小是且 $z1$ 最大 $z2$ 最小，那么我们要去掉的就是 $\min(x1,\min(x2,z1))-\min(x2,\min(x1,z2))$，这里注意 $z1$ 和 $z2$ 可能在区间 $mid+1\sim \min(x1,x2)$ 的外面。

  # 代码

  代码有一点长，建议自己打一下。

  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  #define ll long long
  #define int long long
  #define pb push_back
  #define rep(i,x,y) for(register int i=x;i<=y;i++)
  #define rep1(i,x,y) for(register int i=x;i>=y;--i)
  #define fire signed
  #define il inline
  int T=1;
  int n;
  #define in(x) scanf("%lld",&x)
  const int N=2e5+10;
  ll a[N];
  int b[N],log1[N];
  int ans;
  ll s;
  ll sum[N],f[N][22];
  int Ans(int x,int y) {
  	int s=log1[y-x+1];
  	return min(f[x][s],f[y-(1<<s)+1][s]);
  }
  il void Minleft(int l,int r){
  	int mid=l+r>>1;
  	rep(i,l,mid) {
  		int l1=mid+1,r1=r,res=-1;
  		int b=Ans(i,mid);
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(Ans(i,mid1)>=b) l1=mid1+1,res=mid1;
  			else r1=mid1-1;
  		}
  		if(res==-1) continue;
  		int nows=s-b;
  		l1=mid+1,r1=r;
  		int res1=-1;
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(sum[mid1]-sum[i-1]<=nows) l1=mid1+1,res1=mid1;
  			else r1=mid1-1;
  		}
  		if(res1==-1) continue;
  		int now=min(res,res1);
  		int tx=false;
  		l1=mid+1,r1=r;
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(Ans(mid+1,mid1)<=b) tx=mid1,l1=mid1+1;
  			else r1=mid1-1;
  		}
  		ans+=now-mid;
  	}
  }
  il void Minright(int l,int r) {
  	int mid=l+r>>1;
  	rep(i,mid+1,r) {
  		int l1=l,r1=mid,res=-1;
  		int b=Ans(mid+1,i);
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(Ans(mid1,i)>=b) r1=mid1-1,res=mid1;
  			else l1=mid1+1;
  		}
  		if(res==-1) continue;
  		l1=l,r1=mid;
  		int now=s-b;
  		int res1=-1;
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(sum[i]-sum[mid1-1]<=now) r1=mid1-1,res1=mid1;
  			else l1=mid1+1;
  		}
  		if(res1==-1) continue;
  		int now1=max(res,res1);
  		ans+=(mid-now1+1);
  		l1=l,r1=mid;
  		int tx=false,ty=false;
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(Ans(mid1,mid)>=b) {
  				r1=mid1-1;
  				tx=(Ans(mid1,mid)==b?mid1:tx);
  			}
  			else l1=mid1+1;
  		}
  		if(!tx) continue;
  		l1=tx,r1=mid;
  		while(l1<=r1) {
  			int mid1=l1+r1>>1;
  			if(Ans(mid1,mid)==b) l1=mid1+1,ty=mid1;
  			else r1=mid1-1;
  		}
  		if(tx<now1&&ty<now1) continue;
  		tx=max(tx,now1);
  		ty=max(ty,now1);
  		ans-=(ty-tx+1);
  	}
  }
  il void get(int l,int r) {
  	if(l==r) {
  		if(a[l]+b[l]<=s) ans++;
  		return ;
  	}
  	int mid=l+r>>1;
  	Minleft(l,r);
  	Minright(l,r);
  	get(l,mid);
  	get(mid+1,r);
  }
  fire main() {
  	in(n),in(s);
  	rep(i,1,n) in(a[i]),f[i][0]=a[i];
  	rep(i,1,n) in(b[i]),sum[i]=sum[i-1]+b[i];	 
  	log1[2]=1;
  	rep(i,3,n) log1[i]=log1[i/2]+1;
  	rep(j,1,20) rep(i,1,n-(1<<j)+1) f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
  	get(1,n);
  	printf("%lld\n",ans);
  	return false;
  }
  ```

注意这里求最小值时只能用 $O(1)$ 算法，因为这道题没放 $n\times \log(n)^3$ 过。

---

## 作者：mi_Y13c (赞：1)

### 算法
#### (笛卡尔树、启发式分治)  

对于整数  $L$，$R$，考虑用分治法来解决区间  $[L, R]$  上的问题 (即统计区间  $[L, R]$  中所包 含的好数对  ($l, r)$  的个数  )  。具体而言，我们可以取一个满足  $L \leqslant M \leqslant R$  的整数  $M$  ， 只统计那些满足  $l \leqslant M \leqslant r$  的好对  $(l, r)$  的个数，剩下的就是递归地求解区间  $[L, M-1]$  和区间  $[M, R]$  上的问题。

那么我们应该如何统计区间  $[L, R]$  中满足  $l \leqslant M \leqslant r$  的好对  $(l, r)$  的个数呢?

我们可以取  $M $ 使得  $A_{M}=\min \left(A_{L}, A_{L+1}, \cdots, A_{R}\right)$  ，并统计区间  $[L, R]$  中满足  $l \leqslant M \leqslant r  的好对  (l, r)$  的个数。
根据  $M $ 的选择来看，对于区间中所有满足  $l \leqslant M \leqslant r$  的整数对  $(l, r)$  而言，$\min \left(A_{l}, A_{l+1}, \cdots, A_{r}\right)$  恒等于  $A_{M}$  。所以，当固定  $l$  或  $r$  时，另一个使得  $(l, r)$  是好对 的变量值域可以通过对  $B$  上的区间累加和二分找到。
所以，如果  $[L, M]$  的长度更短，则固定  $l$  来统计好对的个数；如果  $[M, R]$  长度更短，则 固定 $ r$  来统计好对的个数。

然后在序列 $A$ 上建笛卡尔树，左键记录当前点的最左边大于当前点权值的下标，右键记录当前点的最右边大于当前点的权值的下标。

时间复杂度 $O\left(N \log ^{2} N\right) $。

### 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using namespace std;
using ll = long long;
using P = pair<int, int>;

int main() {
    int n; ll s;
    cin >> n >> s;

    vector<ll> a(n), b(n), c(n+1);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];
    rep(i, n) c[i+1] = c[i]+b[i];

    a.push_back(-1);
    vector<P> to(n+1, P(-1, -1));
    {
        stack<int> st;
        rep(i, n+1) {
            int l = -1;
            while (st.size() and a[st.top()] > a[i]) {
                int j = st.top(); st.pop();
                to[j].second = l;
                l = j;
            } 
            to[i].first = l;
            st.push(i);
        }
    }

    ll ans = 0;
    auto f = [&](auto f, int v, int l, int r) {
        if (v == -1) return;
        if (v-l < r-v) {
            for (int i = l; i <= v; ++i) {
                ans += upper_bound(c.begin()+v+1, c.begin()+r+1, s-a[v]+c[i]) - (c.begin()+v+1);
            }
        }
        else {
            for (int i = v+1; i <= r; ++i) {
                ans += v+1-(lower_bound(c.begin()+l, c.begin()+v+1, -s+a[v]+c[i]) - c.begin());
            }
        }
        f(f, to[v].first, l, v);
        f(f, to[v].second, v+1, r);
    };
    f(f, to[n].first, 0, n);

    cout << ans << '\n';

    return 0;
}
```

---

## 作者：hhhqx (赞：0)

# [ABC282Ex] Min + Sum 题解

[题面传送门](https://www.luogu.com.cn/problem/AT_abc282_h)。

题目要求有多少对 $(l, r)$ 满足 $1 \le l \le r \le n$ 且 $\sum_{i=l}^{r}{b_i} + \min_{i=l}^{r}{a_i} \le S$。

考虑 **CDQ 分治**，那么我们需要**不断寻找**有多少对 $(l,r)$ 满足 $L \le l \le M < r \le R$ 且 $\sum_{i=l}^{r}{b_i} + \min_{i=l}^{r}{a_i} \le S$。因为第一条限制，所以第二条限制可以转化为 $\sum_{i=M+1}^{r}{b_i} + \sum_{i=l}^{M}{b_i} + \min(\min_{i=l}^{M}{a_i}, \min_{i=M+1}^{r}{a_i}) \le S$。

这显然需要先进行**前后缀和**。我们无法做到枚举 $l$ 又枚举 $r$。所以考虑枚举 $r$。**容易发现** $\min_{i=x}^{M}{a_i} \le \min_{i=x + 1}^{M}{a_i}$，于是我们**双指针**，找到一个 $x$，对于当前枚举到的 $r$ 满足 $\min_{i=x}^{M}{a_i} < \min_{i=M+1}^{r}{a_i} \le \min_{i=x + 1}^{M}{a_i}$。

那么现在，$[L,x]$ 中的点 $l$ 需要满足 $\min_{i=l}^{M}{a_i} + \sum_{i=l}^{M}{b_i} + \sum_{i=M+1}^{r}{b_i} \le S$。

$(x,M]$ 中的点 $l$ 需要满足 $\sum_{i=l}^{M}{b_i} + \min_{i=M+1}^{r}{a_i} + \sum_{i=M+1}^{r}{b_i} \le S$。

由于我们已知右端点 $r$，所以可以分类讨论左端点 $l$ 的情况。对不等式移项，求出其限制，最后发现这是一个插入删除后，求多少个插入后保留数满足小于某个数，这显然可以用 **01 - trie** 来解决。

最后时间复杂度 $O(n \log n \log S)$。

# AC Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = 2e5 + 3;

int n;
LL S, ans = 0, a[MAXN], b[MAXN]; 
LL smi[MAXN], ssum[MAXN];

int top[2] = {1, 1}, eg[2][MAXN * 50][2], cnt[2][MAXN * 50];

inline void Insert(int op, LL x){ // 01 - trie 插入 
  int p = 1;
  for(int i = 49; i >= 0; i--){ int col = (x >> i) & 1;
    if(!eg[op][p][col]) eg[op][p][col] = ++top[op];
    p = eg[op][p][col], cnt[op][p]++;
  }
}
inline void Erase(int op, LL x){ // 01 - trie 删除 
  int p = 1;
  for(int i = 49; i >= 0; i--){ int col = (x >> i) & 1;
    p = eg[op][p][col], cnt[op][p]--;
  }
}
inline int query(int op, LL x){ // 01 - trie 求小于 x 的个数 
  if(x <= 0) return 0;
  int p = 1, ret = 0;
  for(int i = 49; i >= 0; i--){ int col = (x >> i) & 1;
    if(col == 1 && eg[op][p][0]) ret += cnt[op][eg[op][p][0]];
    if(!eg[op][p][col]) eg[op][p][col] = ++top[op];
    p = eg[op][p][col];
  }
  return ret;
}
void Clear(){ // 清空 01 - trie 
  for(int op = 0; op <= 1; op++){
    for(int i = 1; i <= top[op]; i++) cnt[op][i] = eg[op][i][0] = eg[op][i][1] = 0;
    top[op] = 1;
  }
}

void Solve(int l, int r){ // CDQ 分治 
  if(l == r){
    ans += (a[l] + b[l] <= S); // 统计 l = r 的区间 
    return;
  } 
  int mid = (l + r) >> 1;
  smi[mid] = a[mid], ssum[mid] = b[mid], Insert(0, ssum[mid] + smi[mid]); // 预处理 [l,mid] 区间 
  for(int i = mid - 1; i >= l; i--) smi[i] = min(smi[i + 1], a[i]), ssum[i] = ssum[i + 1] + b[i], Insert(0, ssum[i] + smi[i]);
  
  LL mi = 1e17, sum = 0;
  for(int i = mid + 1, j = mid + 1; i <= r; i++){ // 在 (mid,r] 中枚举答案右端点 
    mi = min(mi, a[i]), sum += b[i];
    while(j > l && smi[j - 1] >= mi) j--, Insert(1, ssum[j]), Erase(0, ssum[j] + smi[j]); // 01 - trie 处理 
    ans += query(1, S - sum - mi + 1) + query(0, S - sum + 1); // 通过 01 - trie 找到合法的在 [l,mid] 中的答案左端点，统计答案 
  }
  Clear(), Solve(l, mid), Solve(mid + 1, r); // 清空 01 - trie 后继续递归处理 
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> S;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i];
  Solve(1, n); 
  cout << ans;  
  return 0;
}
```

---

## 作者：_XHY20180718_ (赞：0)

考虑对序列进行分治来统计贡献。

对于一个区间 $[L,R]$，将其分成两半 $[L,mid]$ 和 $[mid+1,R]$，然后递归下去统计两边区间内部的答案。

边界条件很显然就是区间只有一个数的时候是否符合条件，符合返回 $1$，不符合返回 $0$。

接下来我们要做的就是统计跨过中点 $mid$ 的两边的贡献。

将这个贡献拆成两部分，考虑谁来做最小值，这样好计算一些：

考虑计算左边为最小值时的贡献，从左到右枚举点 $p$，找到他作为左端点，最小值在 $[p,mid]$ 中的合法区间个数。

先将 $[p,mid]$ 的最小值求出来，然后二分出区间 $[p,R]$ 中，最小值在 $[p,mid]$ 中的最后一个点 $r$，对于区间 $[p,r]$，由于最小值确定，我们可以二分出最后一个使得区间 $[p,q]$ 满足题目中条件的 $q$。

以 $p$ 为左端点，并且最小值在 $[p,mid]$ 中的合法区间数量便是这个区间的长度。

右边区间类似，反过来就可以了，不过要注意一下有一边二分以这边的数为最小值的最长区间时可以相等，另一边不能相等。

二分最小值的时候可以用 st 表 $O(1)$ 求出区间最小值。

分治层数是 $O(\log n)$ 的，每一层要枚举每一个数并且二分，所以总复杂度是 $O(n\log^2n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(x,y) (x>y?x:y)
using namespace std;
const int N=2e5+5;
int n,S,a[N],b[N],ans;
int s[N],Log[N],st[20][N];
inline int getmin(int l,int r){
    if(l>r){cerr<<"Error\n";return 0;}
    r=min(r,n);int t=Log[r-l+1];
    return min(st[t][l],st[t][r-(1<<t)+1]);
}
inline void calc(int L,int R){
    if(L==R){ans+=(a[L]+b[R]<=S);return;}
    int Mid=L+(R-L>>1);
    for(int i=L; i<=Mid; ++i){
        int l=Mid+1,r=R+1,mid;
        int mnx=getmin(i,Mid);
        while(l<r){
            mid=l+(r-l>>1);
            if(mnx>getmin(Mid+1,mid))r=mid;
            else l=mid+1;
        }
        l=Mid+1;
        while(l<r){
            mid=l+(r-l>>1);
            if(s[mid]-s[i-1]>S-mnx)r=mid;
            else l=mid+1;
        }--r,ans+=r-Mid;
    }
    for(int i=R; i>Mid; --i){
        int l=L,r=Mid+1,mid;
        int mnx=getmin(Mid+1,i);
        while(l<r){
            mid=l+(r-l>>1);
            if(mnx>=getmin(mid,Mid))l=mid+1;
            else r=mid;
        }r=Mid+1;
        while(l<r){
            mid=l+(r-l>>1);
            if(s[i]-s[mid-1]>S-mnx)l=mid+1;
            else r=mid;
        }ans+=Mid-l+1;
    }
    calc(L,Mid),calc(Mid+1,R);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>S;
    for(int i=1; i<=n; ++i)
        cin>>a[i],st[0][i]=a[i];
    for(int i=2; i<=n; ++i)
        Log[i]=Log[i>>1]+1;
    for(int j=1; j<=Log[n]; ++j)
        for(int i=1; i+(1<<j)-1<=n; ++i)
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    for(int i=1; i<=n; ++i)
        cin>>b[i],s[i]=s[i-1]+b[i];
    calc(1,n);
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：ainivolAGEM (赞：0)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-at-abc282-h)

## 题目大意

[题目](https://www.luogu.com.cn/problem/AT_abc282_h)意思很明确了，就是给了两个序列 $A$ 和 $B$，请问有多少对 $( l , r )$ 满足 $1 \le l \le r \le  n$，且
$$
\sum _ { i = l } ^ r B _ i + \min _ { i = l } ^ r A_i \le S
$$

## 题目分析

发现 $S$ 已给定且序列范围过大，考虑分治思想。

我们根据分治思想先简化问题，把题目变成在区间 $( l , r )$ 中，然后再做转化。可以发现区间中必定会有一个最小值。那么可以得知，这个区间中的所有子区间都可以分为经过和不经过这个最小值的两种情况。设最小值为 $m$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wgxsss2s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

则不经过 $m$ 的情况可以分治下去处理，只需要处理经过 $m$ 的情况。

我们可以尝试在 $m$ 的两侧进行遍历，每次都走过 $m$ 的一边，然后再遍历另外一边，重复直到超过 $S$ 就可以了。

但是肯定会超时就对了，怎么办呢？

可以发现遍历一边时，剩余分给另外一边的可表现为：（设一边遍历为 $x$）

$$
S - m - x
$$

则可知另一侧的取值是单调递增的。那么可以用前缀和和二分进行维护，每次遍历一侧时，在另一侧找出一个能取到的最大位置（记它为 $a$），则 $\lvert a - m \rvert$ 就是当前遍历的方案数。

![](https://cdn.luogu.com.cn/upload/image_hosting/3tf9tpeu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那还是会超限，咋办？

其实考虑最坏情况可以得知，如果每次都选固定的一边遍历而另一边二分，还是相当于 $O ( N ^ 2 )$。所以我们只需要每次选短的一边进行遍历，长的一边就进行二分就可以解决了。

## AC code

```cpp
#include<bits/stdc++.h>
#define Tmin(x,y,i) (a[pos[x][i]]<a[pos[y][i]]?pos[x][i]:pos[y][i])
using namespace std;
typedef long long ll;
const int N=1e6+4;
const int T=50;
const int inf=0x3f3f3f3f;
ll n,s,a[N],b[N];
ll s1[N],s2[N];
ll pos[N][T];
void Build(){ //求区间最小值
	for(int i=1;i<=n;i++){
		pos[i][0]=i;
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			pos[i][j]=Tmin(i,i+(1<<(j-1)),j-1);
		}
	}
}
ll getId(ll l,ll r){
	ll t=log(r-l+1)/log(2);
	return Tmin(l,r-(1<<t)+1,t);
}
ll getA(ll l,ll r,ll m){
	while(r-l>=1){
		ll mid=(l+r)/2+1;
		if(s1[mid]-s1[m-1]<=s){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	return l;
}
ll getB(ll l,ll r,ll m){
	while(r-l>=1){
		ll mid=(l+r)/2;
		if(s2[mid]-s2[m+1]<=s){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	return r;
}
ll solve(ll l,ll r){
	ll id=getId(l,r);
//	cout<<id<<'\n';
	ll sum=0;
	if(l<=id-1){
		sum+=solve(l,id-1);
	}
	if(id+1<=r){
		sum+=solve(id+1,r);
	}
	if(id-l<=r-id){
		for(int i=id;i>=l;i--){
			if(s2[i]-s2[id+1]+a[id]>s){
				break;
			}
			s-=s2[i]-s2[id]+a[id];
			sum+=getA(id,r,id)-id+1;
			s+=s2[i]-s2[id]+a[id];
		}
	}else{
		for(int i=id;i<=r;i++){
			if(s1[i]-s1[id-1]+a[id]>s){
				break;
			}
			s-=s1[i]-s1[id]+a[id];
			sum+=id-getB(l,id,id)+1;
			s+=s1[i]-s1[id]+a[id];
		}
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		s1[i]=s1[i-1]+b[i];
//		cout<<s1[i]<<' ';
	}
//	cout<<'\n';
	for(int i=n;i>=1;i--){
		s2[i]=s2[i+1]+b[i];
	}
//	cout<<getA(3,n,3)<<' '<<getB(1,n-2,n-2);
//	for(int i=1;i<=n;i++){
//		cout<<s2[i]<<' ';
//	}
//	cout<<'\n';
	Build();
	cout<<solve(1,n);
}
```


---

## 作者：ast123 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc282_h)

## Part 0 自我批判
~~为了一个很简单的错误调了一下午，必须提出批斗。~~

## Part 1 分析
发现 $\sum_{i=l}^{r}b_i$ 当一个端点 $l$ 固定时是单调不降的，但 $\min_{i=l}^{r}a_i$ 是单调不增的，所以不能简单地二分。但是 $n$ 的取值范围是 $n \leq 2 \times 10^5$，时间复杂度至少是 $O(n \sqrt n)$ 或 $O(n \log n)$，所以可以考虑分治。

考虑简化这个问题，如果最小值确定，可以直接枚举其中一个端点然后二分，如果枚举最小值，就可以求出这个问题的答案。枚举最小值可以用枚举区间代替，然后用st表求最小值。

于是可以二分区间，设最小值的位置为 $mn$，当前区间为 $[l,r]$,则这个区间的答案为经过 $mn$ 的合法区间加上区间 $[l,mn-1]$ 和 $[mn+1,r]$ 的答案， $l>r$ 时可以直接返回0。经过 $mn$ 的区间可以枚举某个端点然后二分。但是如果数据故意构造一个单调的序列，就不能简单的任选一个端点枚举，而是要选长度小的一边，具体看代码。

## Part 2 代码
```cpp
#include <cstdio>
#define ll long long
using namespace std;
const int N = 2e5+5;
int n, lg[N], st[N][21];
ll s, a[N], b[N];
inline int query(int l, int r){
	int m = lg[r-l+1];
	if(a[st[l][m]] < a[st[r-(1<<m)+1][m]]) return st[l][m];
	else return st[r-(1<<m)+1][m];
}
inline int bsl(int l, int r, int u, int mn){
	int mid; --l; ++r;
	while(r-l > 1){
		mid = l+r>>1;
		if(b[u]-b[mid-1]+a[mn] <= s) r = mid;
		else l = mid;
	}
	return r;
}
inline int bsr(int l, int r, int u, int mn){
	int mid; --l; ++r;
	while(r-l > 1){
		mid = l+r>>1;
		if(b[mid]-b[u-1]+a[mn] <= s) l = mid;
		else r = mid;
	}
	return l;
}
inline ll solve(int l, int r){
	if(l > r) return 0;
	int mn = query(l, r);
	ll ans = 0;
	if(r-mn < mn-l)//这里要判断最小值哪一边的数量少，就枚举哪一边，然后二分另一边
		for(int i=mn; i<=r; ++i)
			ans += mn-bsl(l, mn, i, mn)+1;//注意另一边最多到mn，不然不一定取得到mn
	else
		for(int i=l; i<=mn; ++i)
			ans += bsr(mn, r, i, mn)-mn+1;
	return ans + solve(l, mn-1) + solve(mn+1, r);
}
int main(){
	scanf("%d%lld", &n, &s); lg[0] = -1;
	for(int i=1; i<=n; st[i][0]=i, ++i){
		scanf("%lld", &a[i]); lg[i] = lg[i>>1]+1;
	}
	for(int i=1; i<=n; b[i]+=b[i-1], ++i)
		scanf("%lld", &b[i]);
	
	for(int j=1; j<=lg[n]; ++j)//st表存最小值的位置
		for(int i=1; i+(1<<j)-1<=n; ++i)
			if(a[st[i][j-1]] < a[st[i+(1<<j-1)][j-1]])
				st[i][j] = st[i][j-1];
			else st[i][j] = st[i+(1<<j-1)][j-1];
	printf("%lld\n", solve(1, n));
	return 0;
}
```

---

## 作者：Dream__Sky (赞：0)

考虑分治。

我们发现，只要一个 $a_i$ 是一个区间内的最小值，那么它就有可能会产生贡献，需要枚举一遍。由于每个 $a_i$ 作为最小值的范围是互不干扰的，都有它独自的“管辖范围”，那我们可以就可以根据最小值来分治，达到这个目的。

因为要根据最小值分治，我们需要一个快速求出区间最小值的**位置**的数据结构。可以用 ST 表维护。ST 表的维护就不过多赘述了。

现在考虑如何分治。前面提到，按照最小值分治。首先用 ST 表来求出当前区间 $[L,R]$ 的最小值位置 $mid$。对于这个区间，我们分成在 $mid$ 左右的两部分。此时我们对于这个区间中，更小的符合要求的区间是未知的。因此，我们就要枚举 $mid$ 其中一边的 $l$，用二分（对于区间和，先维护前缀和，由于没有负数，那么具有单调性）来算出另一边的 $r$。那么对于枚举的这个 $l$，它的贡献就是 $r-mid+1$。累加即可。接着我们继续分治，分成 $[L,mid-1]$，$[mid,R]$ 这两个区间。

还有一个问题，我们怎么考虑枚举 $mid$ 的哪一边。很显然，长度短的那边更优。因为每多枚举一个，就要增加一只 $\log$ 的复杂度。每次的小区间，即 $mid$ 的长度短的一边的长度，必定小于等于大区间的长度的一半。故总复杂度为 $O(n\log^2n)$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define log(x) log2(x)
using namespace std;
const int N=2e5+10;
int n,s,ans,a[N],b[N],c[N],f[N][25];
int Max(int l,int r,int i)
{
	if(a[f[l][i]]<a[f[r][i]]) return f[l][i];
	else return f[r][i];
}
void init()
{
	for(int i=1;i<=n;i++) f[i][0]=i;
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=Max(i,i+(1<<(j-1)),j-1);
}
int query(int l,int r)
{
	return Max(l,r-(1<<(int)log(r-l+1))+1,log(r-l+1));
}
int checkl(int l,int r,int x,int sum)
{
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(c[mid]-c[x-1]<=sum) l=mid+1;
		else r=mid-1;
	}
	return r;
}
int checkr(int l,int r,int x,int sum)
{
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(c[x]-c[mid-1]<=sum) r=mid-1;
		else l=mid+1;
	}
	return l;
}
void dfs(int l,int r)
{
	if(l>r) return ;
	int mid=query(l,r);
	if(mid-l<r-mid)
	{
		for(int i=l;i<=mid;i++)
			ans+=checkl(mid,r,i,s-a[mid])-mid+1;
	}
	else 
	{
		for(int i=mid;i<=r;i++)
			ans+=mid-checkr(l,mid,i,s-a[mid])+1;
	}	dfs(l,mid-1);dfs(mid+1,r);
}
signed main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i],c[i]=c[i-1]+b[i];
	init();
	dfs(1,n);
	cout<<ans;
	return 0;
}
```



---

## 作者：Xiphi (赞：0)

板子题。考虑 st 表加二分预处理出对于每个 $a_i$，它向左右延伸且最小值为其本身的区间中，最大的区间的左端点右端点 $l_i,r_i$。然后需要注意的是，若有两个下标对应的 $l_i,r_i$ 相等，则下标靠后的那个 $l_i$ 变成前一个 $l_i,r_i$ 与其相等的数。

然后就可以枚举了，我们对于一段区间，只枚举短的那边，复杂度带上二分的话均摊 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define BF_SIZE 100000
bool IOerr = 0;
inline char nc() {
	static char buf[BF_SIZE], * p1 = buf + BF_SIZE, * pend = buf + BF_SIZE;
	if (p1 == pend) {
		p1 = buf;
		pend = buf + fread(buf, 1, BF_SIZE, stdin);
		if (pend == p1) { IOerr = 1; return -1; }
	}
	return *p1++;
}
inline bool bla(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
inline long long read()
{
	char ch;
	long long x = 0;
	while (bla(ch = nc()));
	if (IOerr) { return 0; }
	for (x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = (x << 1) + (x << 3) + ch - '0');
	return x;
}
#define max(x,y) x>y?x:y
#define min(x,y) x>y?y:x
long long n,s;
long long sum[200005],a[200005];
int b[200005];
int L[200005],R[200005];
long long st[20][200005];
map<pair<int,int>,int> mp;
#define ll long long
ll query(int l,int r){
	int len=__lg(r-l+1);
	return min(st[len][l],st[len][r-(1<<len)+1]);
}
signed main(){
	n=read(),s=read();
	for(int i=1;i<=n;++i) a[i]=read(),st[0][i]=a[i];
	for(int i=1;i<=n;++i) b[i]=read(),sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=18;++i){
		for(int j=1;(j+(1<<i)-1)<=n;++j){
			st[i][j]=min(st[i-1][j],st[i-1][(1<<(i-1))+j]);
		}
	}
	for(int i=1;i<=n;++i){
        int l=1,r=i;
        while(l<=r){
            int mid=l+r>>1;
            if(query(mid,i)==a[i]){
                r=mid-1;L[i]=mid;
            }else l=mid+1;
        }
        l=i,r=n;
        while(l<=r){
            int mid=l+r>>1;
            if(query(i,mid)==a[i]){
                l=mid+1;R[i]=mid;
            }else r=mid-1;
        }
        if(mp.count({L[i],R[i]})==1) { int tt=mp[{L[i],R[i]}];mp[{L[i],R[i]}]=i;L[i]=tt+1;}
		else mp[{L[i],R[i]}]=i;
    }
    long long ans=0;
    for(int i=1;i<=n;++i){
        if(R[i]-i+1>i-L[i]+1){
            for(int j=L[i];j<=i;++j){
            	int l=i,r=R[i],t=-1;
            	ll B=s-a[i];
            	while(l<=r){
            		int mid=l+r>>1;
            		if((sum[mid]-sum[j-1])<=B){
            			t=mid,l=mid+1;
					}else r=mid-1;
				}
				if(t!=-1) ans+=(t-i+1);
            }
        }else{
            for(int j=i;j<=R[i];++j){
            	int l=L[i],r=i,t=-1;
            	ll B=s-a[i];
            	while(l<=r){
            		int mid=l+r>>1;
            		if((sum[j]-sum[mid-1])<=B){
            			t=mid,r=mid-1;
					}else l=mid+1;
				}
				if(t!=-1) ans+=(i-t+1);
            }
        }
	}
    cout<<ans;
    return 0;
}
```

---

## 作者：SnowTrace (赞：0)

什么超级无敌简单套路板子题。

这居然能有 AT2600，很难相信。

看到最小值我们很想把他拆掉，所以我们使用单调栈。

从而对于一个点 $i$，我们可以确定 $l_i,r_i$，使得：

若一个区间的左端点在 $(l_i,i]$ 之间，右端点在 $[i,r_i)$ 之间，则这个区间的最小值是 $a_i$。

这个玩意本质上是笛卡尔树。

给出下面这样一种算法：

枚举左（或右）端点，然后二分得到最左的左端点/最右的右端点，计算答案。

如果 $r_i-i\leq i-l_i$ 我们枚举右端点。

否则就枚举左端点。

这个算法的时间复杂度是 $O(n\log^2n)$，可以通过。

具体证明：

考虑建出笛卡尔树，那我们每次遍历的是每个点左右子树中大小较小的那颗子树，根据启发式合并的原理可以知道我们枚举到的点是 $O(n \log n)$ 级别的，加上一个二分就是 $O(n\log^2n)$。

代码实现里面不需要笛卡尔树。

超级无敌短短短代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,s;
int l[200005],r[200005],pre[200005],a[200005],b[200005];
signed main(){
	cin>>n >> s;
	for(int i = 1;i<=n;i++)cin >> a[i];
	for(int i = 1;i<=n;i++)cin >> b[i];
	vector<int>p;a[0] = -1,a[n+1] = -1;
	p.push_back(0);
	for(int i = 1;i<=n;i++){
		while(a[p.back()]>=a[i])p.pop_back();
		l[i] = p.back();p.push_back(i);
	}p.clear();p.push_back(n+1);
	for(int i =n;i>=1;i--){
		while(a[p.back()]>a[i])p.pop_back();
		r[i] = p.back();p.push_back(i);
	}int ans =0 ;
	for(int i = 1;i<=n;i++)pre[i] =pre[i-1]+b[i];
	for(int i = 1;i<=n;i++){
		if(i-l[i]<r[i]-i){
			for(int j = i;j>l[i];j--){
				if(pre[i]-pre[j-1]>s-a[i])break;
				int L = i,R = r[i]-1;
				while(L<R){
					int mid = L+R+1>>1;
					if(pre[mid]-pre[j-1]<=s-a[i])L = mid;
					else R = mid-1;
				}ans+=L-i+1;
			}
		}else{
			for(int j = i;j<r[i];j++){
				if(pre[j]-pre[i-1]>s-a[i])break;
				int L = l[i]+1,R = i;
				while(L<R){
					int mid = L+R>>1;
					if(pre[j]-pre[mid-1]<=s-a[i])R = mid;
					else L = mid+1;
				}ans+=i-R+1;
			}
		}
	}cout << ans << endl; 
	return 0;
} 
```


---

## 作者：ABookCD (赞：0)

## ABC282Ex **[Min + Sum](https://atcoder.jp/contests/abc282/tasks/abc282_h)(Diff. 2,412)**

> 摘自文章[序列分治](https://www.cnblogs.com/arizonayyds/articles/fenzhi.html) I.ABC282Ex Min + Sum

#### Solution:

看到寻找符合条件的区间，不难想到使用分治解决。

按照套路寻找左端点，找有哪些右端点符合条件。

设区间为 $[l,r]$，当前枚举的左端点为 $lpos$，区间 $[l,mid]$ 的最小值是 $lmin$，那么所有的右端点 $i$ 可以按照 $[mid+1,i]$ 的最小值 $rmin_i$ 与 $lmin$ 的大小分成两类。

由于 $rmin_i$ 单调非严格递减，且所以正好是左右两段。

1. $rmin_i\ge lmin$：这类情况下，区间 $[l,i]$ 的值为区间和加上 $lmin$，由于区间和也是单调递增的，所以我们可以二分解决这一段。

2. $rmin_i<lmin$：这类情况下区间的值不再具有单调性，我们对 $b$ 数组求一个前缀和，那么区间和可以表示成 $(pfs[i]-pfs[lpos-1]+rmin_i)$。我们将与有半部分有关的提取出来，那么剩下的是 $pfs[lpos-1]$，满足单调递减性质，所以我们可以把所有右端点存入一个数据结构里面，每此更新左端点时把所有已经不满足限制的删去即可。

   不满足限制的情况有两种，一种是当前点在更新左端点后不属于第二类了，另外一种是在算答案贡献的时候已经不满足 $s$ 的限制了，后面也不可能满足，删去。

   查询则查询值小于等于阈值 $s-pfs[lpos-1]$ 的个数即可。

   不难想到可以用 std::set 维护。

时间复杂度 $O(n\log^2n)$。



#### Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,a[300010],b[300010],ans;
int qzamin[300010],pfs[300010];
#define pr pair<int,int>
#define mp make_pair
void solve(int l,int r){
	if(l==r){
		ans+=((a[l]+b[l])<=m);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	int lemin=1e18,rxend=mid;
	qzamin[mid]=1e18;
	for(int i=mid+1;i<=r;i++) qzamin[i]=min(qzamin[i-1],a[i]);
	set<pr> s1;
	for(int i=mid+1;i<=r;i++) s1.insert(mp(-qzamin[i]-pfs[i]+pfs[mid],i));
	for(int lpos=mid;lpos>=l;lpos--){
		lemin=min(lemin,a[lpos]);	
		while(rxend<r&&qzamin[rxend+1]>=lemin){
			rxend++;
			auto it=s1.find(mp(-qzamin[rxend]-pfs[rxend]+pfs[mid],rxend));
			if(it!=s1.end()) s1.erase(it);
		}
		int ql=mid+1,qr=rxend,cur=mid;
		while(ql<=qr){
			int md=(ql+qr)>>1;
			if(pfs[md]-pfs[lpos-1]+lemin<=m){
				cur=md,ql=md+1;
			}else qr=md-1;
		}
		ans+=cur-mid;
		while(!s1.empty()){
			pr x=*s1.begin();
			if((-x.first+pfs[mid]-pfs[lpos-1])<=m){
				break;
			}
			s1.erase(s1.begin()); 
		}
		ans+=s1.size();
	}	
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),pfs[i]=pfs[i-1]+b[i];
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
```



----------------


---

## 作者：Register_int (赞：0)

看到题目有个 $\min$ 就很难受啊！怎么办呢？

假设我们要求解区间 $[l,r]$ 的答案，考虑直接找到最小值的位置 $k$，这样只要钦定左端点 $\in[l,k]$ 且右端点 $\in[k,r]$ 就可以不用管最小值的限制了。之后再计算两个端点在同一侧的情况，即 $[l,k-1]$ 与 $[k+1,r]$ 的答案，累加即可。

对 $b_i$ 做前缀和得到 $s_i=\sum^i_jb_j$，再枚举任意一侧的端点，找到另一侧的最远端点，便可以计算对应的方案数。具体可以用二分实现，这里不再赘述。

然而，最小值并没有像中点那样优秀的性质，可以使得每次区间大小减半，复杂度仍为 $O(n^2)$。但是别忘了，我们可以**任选一边**求解方案数。那么每次只要处理较短的区间，每次处理的长度仍在区间长度的一半以下，就可以保证复杂度为 $O(n\log^2 n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10; 

int n; ll a[MAXN], b[MAXN], s;

int f[MAXN][19], lg[MAXN];

inline 
void init(int n) {
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= n; i++) f[i][0] = i;
	for (int j = 1; j <= lg[n]; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			if (a[f[i][j - 1]] <= a[f[i + (1 << j - 1)][j - 1]]) f[i][j] = f[i][j - 1];
			else f[i][j] = f[i + (1 << j - 1)][j - 1];
		}
	}
}

inline 
int qmax(int l, int r) {
	int k = lg[r - l + 1];
	return a[f[l][k]] <= a[f[r - (1 << k) + 1][k]] ? f[l][k] : f[r - (1 << k) + 1][k];
}

// b[x] <= s - a[mid] + b[i - 1]
// b[i] + a[mid] - s <= b[x - 1]

inline 
ll solve(int l, int r) {
	if (l >= r) return l == r && a[l] + b[l] - b[l - 1] <= s;
	int mid = qmax(l, r), k; ll ans = 0;
	if (mid - l < r - mid) {
		for (int i = l; i <= mid; i++) {
			k = upper_bound(b + mid, b + r + 1, s - a[mid] + b[i - 1]) - b - 1;
			ans += k - mid + 1;
		}
	} else {
		for (int i = mid; i <= r; i++) {
			k = lower_bound(b + l - 1, b + mid, b[i] + a[mid] - s) - b + 1;
			ans += mid - k + 1;
		}
	}
	return ans + solve(l, mid - 1) + solve(mid + 1, r);
}

int main() {
	scanf("%d%lld", &n, &s);
	for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]); init(n);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]), b[i] += b[i - 1];
    printf("%lld", solve(1, n));
}
```

---

