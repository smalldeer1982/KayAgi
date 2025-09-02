# R2D2 and Droid Army

## 题目描述

An army of $ n $ droids is lined up in one row. Each droid is described by $ m $ integers $ a_{1},a_{2},...,a_{m} $ , where $ a_{i} $ is the number of details of the $ i $ -th type in this droid's mechanism. R2-D2 wants to destroy the sequence of consecutive droids of maximum length. He has $ m $ weapons, the $ i $ -th weapon can affect all the droids in the army by destroying one detail of the $ i $ -th type (if the droid doesn't have details of this type, nothing happens to it).

A droid is considered to be destroyed when all of its details are destroyed. R2-D2 can make at most $ k $ shots. How many shots from the weapon of what type should R2-D2 make to destroy the sequence of consecutive droids of maximum length?

## 说明/提示

In the first test the second, third and fourth droids will be destroyed.

In the second test the first and second droids will be destroyed.

## 样例 #1

### 输入

```
5 2 4
4 0
1 2
2 1
0 2
1 3
```

### 输出

```
2 2
```

## 样例 #2

### 输入

```
3 2 4
1 2
1 3
2 2
```

### 输出

```
1 3
```

# 题解

## 作者：QwQcOrZ (赞：6)

首先题意可以转化为求一个最长的区间，使得区间内第 $i(1\leq i\leq m)$ 种细节的最大值之和小于等于 $k$

显然当区间右端点 $r$ 固定，左端点 $l$ 右移时，这个最大值之和是递减的

那么就可以用 `2-pointers` 做了，也就是每次将区间的右端点右移一位，如果不合法就不停的将左端点右移，直到答案合法

其中找最大值的过程可以用单调队列优化，那么总复杂度就是 $O(nm)$ 的了

$Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=6;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int a[N][M],q[M][N],h[M],t[M],ans[M];
//这里开了m个单调队列
int calc(int m)
{
	int ret=0;
	for (int i=1;i<=m;i++) ret+=a[q[i][h[i]]][i];
	return ret;
}
//计算当前最大值之和

signed main()
{
	int n=read(),m=read(),k=read(),Max=0;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++) a[i][j]=read();
	for (int j=1;j<=m;j++) h[j]=1,t[j]=0;
	for (int l=1,r=1;r<=n;r++)
	{
		for (int i=1;i<=m;i++)
		{
			while (h[i]<=t[i]&&a[q[i][t[i]]][i]<=a[r][i]) t[i]--;
			q[i][++t[i]]=r;
		}//右端点右移
		while (l<=r&&calc(m)>k)
		{
			l++;
			for (int i=1;i<=m;i++)
			if (q[i][h[i]]<l)
			h[i]++;
		}//左端点右移
		if (r-l+1>Max)
		{
			Max=r-l+1;
			for (int i=1;i<=m;i++) ans[i]=a[q[i][h[i]]][i];
		}//计算最大值
	}
	for (int i=1;i<=m;i++) print(ans[i],' ');

	return 0;
}
```

---

## 作者：迟暮天复明 (赞：2)

[题面](https://codeforces.com/contest/514/problem/D)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16343819.html)

Description:

有 $n$ 个敌人，每个敌人有 $m$ 种属性值，第 $i$ 个敌人的每个属性分别为 $a_{i,1},a_{i,2},\ldots,a_{i,m}$。你要构造一个长度为 $m$ 的数列 $b_{1\ldots m}$，规定敌人 $i$ 被杀死当且仅当 $a_{i,1}\leq b_1,a_{i,2}\leq b_2,\ldots,a_{i,m}\leq b_m$ 全部满足。

数列 $b$ 要满足以下条件：
1. $\sum b_i\leq k$；
2. 连续的被杀死的敌人数量最多。

$1\leq n\leq 10^5,1\leq m\leq 5,1\leq k\leq 10^9$。

-----
从第 $l$ 到第 $r$ 个敌人都被杀死的必要条件是 $\max_{l\leq i\leq r}\{a_{i,m}\}\leq b_m$。既然要做最大值，首先想到用 ST 表维护。

然后我要连续的人数最多，所以二分连续的人数。对于每个长度 $x$，我枚举数列中所有长度为 $x$ 的区间，看我能否杀死这个区间中所有的敌人。形式化的，对于区间 $[l,r]$，我能杀死该区间内所有敌人，当且仅当 
$$\sum_{i=1}^m \max_{j=l}^r a_{j,i}\leq k$$

那明显通过 ST 表做这个东西的复杂度是 $O(m)$ 的。算上二分的复杂度，总复杂度为 $O(nm\log n)$，可以通过本题。

实现时注意最大长度为 $0$ 时的输出方式。

[代码](https://paste.ubuntu.com/p/Gfj7P7KbNH/)

---

## 作者：reyik (赞：2)

二分+线段树即可

我们枚举左端点，希望用二分找到满足条件的最远的右端点，显然满足单调性

然后考虑$check$函数，当一个区间内$m$个属性的最大值的和$<=k$，这个区间满足条件，所以我们可以开$m$棵线段树来维护区间最大值，$check$的时候查询一下就可以了

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N=100005;
int n,m,k;
int t[N<<2][6],a[N][6],maxn=0,Ans[6],ls[6],ans[6];
void pushup(int x,int u) {
  t[x][u]=max(t[x<<1][u],t[x<<1|1][u]);
}
void build(int x,int l,int r,int u) {
  if(l==r) {
    t[x][u]=a[l][u];
    return ;
  }
  int mid=(l+r)>>1;
  build(x<<1,l,mid,u);
  build(x<<1|1,mid+1,r,u);
  pushup(x,u);
}
int query(int x,int l,int r,int L,int R,int u) {
  if(L<=l && r<=R) return t[x][u];
  int mid=(l+r)>>1;
  int ret=0;
  if(L<=mid) ret=max(ret,query(x<<1,l,mid,L,R,u));
  if(R>mid) ret=max(ret,query(x<<1|1,mid+1,r,L,R,u));
  return ret;
}
bool check(int l,int r) {
  memset(ls,0,sizeof(ls));int sum=0;
  for (int i=1;i<=m;++i) {ls[i]=query(1,1,n,l,r,i);sum+=ls[i];}
  if(k>=sum) return 1;
  return 0;
}
int solve(int x) {
  int l=x,r=n,ret=0;
  while(l<=r) {
    int mid=(l+r)>>1;
    if(check(x,mid)) {
      ret=mid;
      for (int i=1;i<=m;++i) Ans[i]=ls[i];
      l=mid+1;
    }
    else r=mid-1;
  }
  return ret;
}
int main() {
  scanf("%d%d%d",&n,&m,&k);
  for (int i=1;i<=n;++i) {
    for (int j=1;j<=m;++j) scanf("%d",&a[i][j]);
  }
  for (int i=1;i<=m;++i) build(1,1,n,i);
  for (int i=1;i<=n;++i) {
    int ret1=solve(i);
    if((ret1-i+1)>=maxn) {
      maxn=ret1-i+1;
      for (int j=1;j<=m;++j) ans[j]=Ans[j];
    }
  }
  for (int j=1;j<m;++j) printf("%d ",ans[j]);
  printf("%d\n",ans[m]);
  return 0;
}

```

---

## 作者：快速herself变换 (赞：1)

提供一个无脑二分+线段树/ ST 表做法。

首先看到这个题一定可以想到转化成寻找 $l$ 和 $r$ ，使得 $r - l + 1$ 最大且 $[l,r]$ 这个区间内所有种类属性值的最大值之和 $<= k$ 。

转化成这个样子之后就比较好做了

对于这种求最大区间长度的题我的做法是会采取二分长度的方法来解决

具体就是二分长度,然后在 $check$ 函数里面枚举 $l$ , 用 ST 表/线段树查询  $[l, r]$ 中的最大值,看看最大值之和是不是合法

整体复杂度 $O (nm \log n)$ 或 $O (nm \log^2 n)$ , 能过

一道水紫就这样切掉了

祝各位 csp rp++

---

## 作者：hank0402 (赞：1)

upd : 修正了笔误与空格问题。

### 题解思路：

观察题面，容易得出，若想要销毁第 $l$ 至 $r$ 的人，则所需要的操作次数为：

$$\sum^m_{i=1} \max_{l\le j\le r}a_{j,i}$$

其中 $a_{i,j}$ 表示第 $i$ 个人的第 $j$ 个属性值。若使用 ST 表，$O(n \log n)$ 预处理，$O(1)$ 计算。（因为 $m$ 很小，我们把它视为常数略去）

朴素的枚举肯定是 $O(n^2)$ 的，我们考虑进行优化。

观察到，在右端点 $r$ 向右移的过程中，最优的 $l$ 一定会不断向右移，因为在区间增大的过程中最大值一定不会减大。所以，我们可以记录上一次的最优左端点 $p$，$l$ 在 $p$ 到 $r$ 的范围枚举即可，省去了枚举 $1$ 到 $p-1$ 这一段，这样，每个点最多会被左端点 $l$ 遍历一次，故复杂度为 $O(n)$，这也就是著名的双指针法。

结合前面的 ST 表预处理，总复杂度为 $O(n \log n)$.

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48; ch = getchar(); }
	return x*f;
}
int n, m, k, LOG[N], f[7][N][35], ans;
vector<int> A;
int query(int l, int r) { // 计算销毁l到r的人的次数
	int qans = 0, k = LOG[r - l + 1];
	for(int i = 1; i <= m; ++i) {
		qans += max(f[i][l][k], f[i][r - (1 << k) + 1][k]);
	}
	return qans;
}
void update(int l, int r) { //记录答案
	int k = LOG[r - l + 1];
	vector<int> _new;
	for(int i = 1; i <= m; ++i) {
		_new.push_back(max(f[i][l][k], f[i][r - (1 << k) + 1][k]));
	}
	A = _new;
}
signed main() {
	n = read(), m = read(), k = read();
	LOG[1] = 0;
	for(int i = 0; i < m; ++i) A.push_back(0); // 答案初始为什么也不操作
	for(int i = 2; i <= n; ++i) LOG[i] = LOG[i >> 1] + 1; 
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			f[j][i][0] = read();
		}
	}
	for(int p = 1; p <= m; ++p) {
		for(int j = 1; (1 << j) <= n; ++j) {
			for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
				f[p][i][j] = max(f[p][i][j - 1], f[p][i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	int pl = 1;
	for(int i = 1; i <= n; ++i) {
		while(pl <= i && query(pl, i) > k) pl ++; //双指针法
		if(i - pl + 1 > ans) {
			update(pl, i);
			ans = i - pl + 1;
		}
	}
	for(int i : A) {
		cout << i << ' ';
	}
	return 0;
}
```

---

## 作者：_Felix (赞：1)

### 题意

一共有N个人，每个人有M个属性值，
当一个人的所有属性值都小于等于0的时候，这个人就算被销毁了。

我们每次操作可以选一种属性值进行攻击，
使得所有人的这个属性的值都-1.

我们最多可以进行K次操作,
问我们最多可以干掉多少个连续的人。
问这种时候的具体操作（每一种属性用了多少次操作）

 $n \le 10^5 \ m \le 5 \ k \le 10^9$ 

### 解法

二分干掉的连续人数

直接枚举每个长度为mid的区间

单调队列求区间最大值。

当所有 各属性的区间最大值 的和 $sum \le K$ 时，存在方案干掉 $mid$ 个人。

复杂度$O(nlogn)$

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define rd(x) scanf("%d",&x);
typedef long long LL;
const int N=1e5+10,M=7;
int n,m,hd[M],tl[M],a[N][M],qaq[M],maxx[M];
LL k; 
int check(int len){
	rep(i,1,m) hd[i]=1,tl[i]=0;
	int q[M][N];memset(q,0,sizeof(q));
	int p[M][N];memset(p,0,sizeof(p));
	rep(i,1,n){
		LL sum=0;
		rep(j,1,m){
			while(hd[j]<=tl[j]&&q[j][tl[j]]<=a[i][j]) tl[j]--;
			q[j][++tl[j]]=a[i][j],p[j][tl[j]]=i;
			while(hd[j]<=tl[j]&&p[j][hd[j]]<=i-len) hd[j]++;
			if(i>=len) sum+=q[j][hd[j]],maxx[j]=q[j][hd[j]];
		}
		if(i>=len&&sum<=k){
			rep(j,1,m) qaq[j]=maxx[j];
			qaq[m]+=k-sum;return 1;
		} 
	}
	return 0;
}
int main(){
	rd(n);rd(m);scanf("%lld",&k);
	rep(i,1,n) rep(j,1,m)
		rd(a[i][j]);
	int l=0,r=n,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	rep(i,1,m) printf("%d ",qaq[i]);
	return 0;
}
```

~~恭喜，一道水紫！~~

---

## 作者：Adchory (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF514D)。

## 思路

问题问的是可以干掉多少个**连续**的人并输出方案。

由于是连续的，那么干掉的人一定连成了一个区间，该区间消耗的点数为 $\displaystyle \sum_{i=1}^m \max_{l\le j\le r}a_{j,i}$，$\max$ 我们可以用 ST 表维护，直接暴力做是 $O(n^2m)$ 的。

假如我们现在找到了一个合法区间 $[l,r]$，考虑对它进行扩展，若区间消耗的点数小于等于 $k$，继续扩展并更新答案，否则固定右指针，往右移动左指针（往左只会增加点数），直到该区间合法。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e5+7;
ll n,m,k,a[Maxn][6],f[6][Maxn][20],Log[Maxn],ans;
vector<ll>pans;
inline ll query(ll l,ll r,ll num){
	ll p=Log[r-l+1];
	return max(f[num][l][p],f[num][r-(1<<p)+1][p]);
}
inline ll Q(ll l,ll r){
	ll res=0;
	for(ll i=1;i<=m;i++) res+=query(l,r,i);
	return res;
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			scanf("%lld",&f[j][i][0]);
	for(ll i=1;i<=m;i++) pans.emplace_back(0);
	for(ll i=2;i<=Maxn-7;i++) Log[i]=Log[i>>1]+1;
	for(ll i=1;i<=m;i++)
		for(ll j=1;(1<<j)<=n;j++)
			for(ll p=1;p+(1<<j)-1<=n;p++)
				f[i][p][j]=max(f[i][p][j-1],f[i][p+(1<<(j-1))][j-1]);
	ll l=1,r=0;
	while(r<n){
		r++;
		while(l<=r&&Q(l,r)>k) l++;
		if(r-l+1>ans){
			ans=r-l+1;
			vector<ll>nw;
			for(ll i=1;i<=m;i++) nw.emplace_back(query(l,r,i));
			swap(nw,pans);
		}
	}
	for(auto i:pans) printf("%lld ",i);
	return 0;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

首先，可以转化题意，找到一个极长的区间 $[l,r]$ 使得（其中 $mx_i$ 表示 $[l,r]$ 区间中属性 $i$ 的最大值）：

$$
\sum_{i = 1}^{m}mx_i \leq k
$$

显然对于这个东西当 $l,r$ 发生移动时，是极其好维护的，所以想到双指针。

因为 $m \leq 5$，所以我们可以直接开 $m$ 个 ST 表维护即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define pot(x) (1 << x)

using namespace std;

const int N = 1e5 + 10,M = 10,K = 20;
int n,m,k,ans;
int lg[N],a[N];
int arr[N][M];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void init(){
	for (re int i = 2;i <= n;i++) lg[i] = lg[i / 2] + 1;
}

struct ST{
	int dp[N][K];
	
	inline void init(){
		for (re int j = 1;j <= lg[n];j++){
			for (re int i = 1;i + pot(j) - 1 <= n;i++) dp[i][j] = max(dp[i][j - 1],dp[i + pot(j - 1)][j - 1]);
		}
	}
	
	inline int query(int l,int r){
		int k = lg[r - l + 1];
		return max(dp[l][k],dp[r - pot(k) + 1][k]);
	}
}st[M];

inline bool check(int l,int r){
	int sum = 0;
	for (re int i = 1;i <= m;i++) sum += st[i].query(l,r);
	return (sum <= k);
}

signed main(){
	n = read();
	m = read();
	k = read();
	init();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= m;j++) arr[i][j] = read();
	}
	for (re int j = 1;j <= m;j++){
		for (re int i = 1;i <= n;i++) st[j].dp[i][0] = arr[i][j];
		st[j].init();
	}
	for (re int l = 1,r = 1;r <= n;r++){ 
		while (l <= r && !check(l,r)) l++;
		if (ans < r - l + 1){
			ans = r - l + 1;
			for (re int i = 1;i <= m;i++) a[i] = st[i].query(l,r);
		}
	}
	for (re int i = 1;i <= m;i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

乱搞题。

考虑将区间 $[l,r]$ 中所有人干掉的代价。设 $cnt_{i}=\max\limits_{j=l}^{r}a_{j,i}$，则代价为：$\sum\limits_{i=1}^{m}cnt_i$。很显然，只有在 $\sum\limits_{i=1}^{m}cnt_i \le k$ 是，我们才能将这些人全部干掉。

考虑枚举右端点 $r$，与每个 $r$ 对应的最小能干掉的区间左端点 $l$。不难发现随着区间的缩进，$cnt_i$ 的值是不增的，所以完全可以使用指针求出 $l$，复杂度是 $O(n)$ 的。而在指针移动的时候，$cnt_i$ 的值不方便直接计算，但注意到范围：$m \le 5$，这可以用线段树乱搞维护。总的复杂度是 $O(n \log n)$（$m$ 忽略不计）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e5+10,M=10;
struct node{
	int s[M];
}a[N];
int n,m,k;
struct tree{
	int l,r,mx[M];
}tr[N<<2];
int ANS[M];

il void up(int now){
	tr[now].mx[1]=max(tr[now<<1].mx[1],tr[now<<1|1].mx[1]);
	tr[now].mx[2]=max(tr[now<<1].mx[2],tr[now<<1|1].mx[2]);
	tr[now].mx[3]=max(tr[now<<1].mx[3],tr[now<<1|1].mx[3]);
	tr[now].mx[4]=max(tr[now<<1].mx[4],tr[now<<1|1].mx[4]);
	tr[now].mx[5]=max(tr[now<<1].mx[5],tr[now<<1|1].mx[5]);
	return ;
}
il tree get(tree a,tree b){
	tree ans={0,0,0,0,0,0,0};
	ans.mx[1]=max(a.mx[1],b.mx[1]);
	ans.mx[2]=max(a.mx[2],b.mx[2]);
	ans.mx[3]=max(a.mx[3],b.mx[3]);
	ans.mx[4]=max(a.mx[4],b.mx[4]);
	ans.mx[5]=max(a.mx[5],b.mx[5]);
	return ans;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r){
		tr[now].mx[1]=a[l].s[1];
		tr[now].mx[2]=a[l].s[2];
		tr[now].mx[3]=a[l].s[3];
		tr[now].mx[4]=a[l].s[4];
		tr[now].mx[5]=a[l].s[5];
		return ;
	}
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	up(now);
	return ;
}
il tree query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now];
	tree ans={0,0,0,0,0,0,0};int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) ans=get(ans,query(now<<1,l,r));
	if(mid<r) ans=get(ans,query(now<<1|1,l,r));
	return ans;
}

il void solve(){
	cin>>n>>m>>k;
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=m;++j){
			cin>>a[i].s[j];
		}
	}
	build(1,1,n);
	int maxx=0;
	for(re int i=1,l=1;i<=n;++i)
		while(l<=i){ 
			tree now=query(1,l,i); 
			int sum=now.mx[1]+now.mx[2]+now.mx[3]+now.mx[4]+now.mx[5];
			if(sum<=k){ 
				if(i-l+1>maxx)
					ANS[1]=now.mx[1],ANS[2]=now.mx[2],ANS[3]=now.mx[3],ANS[4]=now.mx[4],ANS[5]=now.mx[5],
					maxx=i-l+1;
				break; 
			} 
			else l++;
		}
	for(re int i=1;i<=m;++i){
		cout<<ANS[i]<<" ";
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：ballpoint_pen (赞：0)

## 题解

提供一种单调队列做法。

我们首先二分最多干掉多少连续的人。

设需要 check 的连续值为 $mid$。相当于长度为 $mid$ 的区间求 $m$ 种指标的最大值，也就是 $m$ 个滑动窗口，单调队列可做。

形式化一点，对于一个区间 $[l,r]$ 就是：

$\sum_{i=1}^{m}(\mathop{max}_{j=l}^{r}\{a_{i,j}\}) \le K$

于是只要判是否存在一个区间使得上面的式子成立。求出左边式子的最小值即可。

时间复杂度：$O(nm\log n)$

注意在一开始就直接将 $m$ 个指标求和，再做单调队列求**指标之和**的最值是错误的。

```
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int a[100005][6];
int ans[6];
int mx[100005][6];
bool check(int mid){
	if(mid==0) return 1;
	memset(mx,0,sizeof mx);
	deque<int> q[6];
	for(int i=1;i<=mid;i++){
		for(int j=1;j<=m;j++){
			while(!q[j].empty()&&a[i][j]>=a[q[j].back()][j])q[j].pop_back();
			q[j].push_back(i);
		}
	}
	for(int i=1;i<=m;i++) mx[mid][i]=a[q[i].front()][i];
	for(int i=mid+1;i<=n;i++){
		for(int j=1;j<=m;j++){
			while(!q[j].empty()&&q[j].front()<i-mid+1) q[j].pop_front();
			while(!q[j].empty()&&a[q[j].back()][j]<=a[i][j]) q[j].pop_back();
			q[j].push_back(i);
			mx[i][j]=a[q[j].front()][j];
		}
	}
	int mn=1e9,sm=0;
	for(int i=mid;i<=n;i++){
		sm=0;
		for(int j=1;j<=m;j++)sm+=mx[i][j];
		if(sm<mn){
			mn=sm;
			if(mn<=k)
				for(int j=1;j<=m;j++)ans[j]=mx[i][j];
		}
	}
	return mn<=k;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	int l=0,r=n,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<' ';
	cout<<endl;
	return 0;
}

```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF514D)
## 思路
这里提供一种不需要动脑的双 $\log$ 做法。

首先我们可以枚举左端点，需要 $O(n)$ 的时间效率，然后我们发现 ${l,r}$ 区间的答案就等于 $\sum \max b_{i,j} \ (l \le i \le r,1 \le j \le m)$。这个东西显然具有单调性，所以可以二分，中间再套个 $\verb!ST!$ 表查询区间 $\max$，为了深入贯彻我们不需要脑子的宗旨，所以我决定不把 $\verb!ST!$ 表优化成 $O(1)$ 查询，时间复杂度 $O(n \log^2 n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e5+10;
int a[N][6],now[9],k,m,f[6][N][20];
inline int query(int q,int ll,int rr){
    int nowmax=0;
    for (int i=30;~i;--i)
        if (ll+(1LL<<i)-1<=rr){
            nowmax=max(nowmax,f[q][ll][i]);
            ll+=(1LL<<i);
        }
    return nowmax;
}
inline bool check(int l,int r){
    memset(now,0,sizeof(now));
    if (l>r) return 1;
    int ans=k;
    for (int q=1;q<=m;++q){
        int nowmax=query(q,l,r);
        ans-=nowmax;now[q]=nowmax;
        if (ans<0) return 0;
    }
    return 1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n>>m>>k;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            cin>>a[i][j];
    for (int q=1;q<=m;++q){
        for (int i=1;i<=n;++i) f[q][i][0]=a[i][q];
        for (int j=1;j<=30;++j)
            for (int i=1;i+(1<<(j-1))<=n;++i)
                f[q][i][j]=max(f[q][i][j-1],f[q][i+(1<<(j-1))][j-1]);
    }
    int ans=-1,ans1[9];
    for (int i=1;i<=n;++i){
        int q[9],r=n,l=i-1;
        memset(q,0,sizeof(q));
        while (l<r){
            if (l+1==r){
                if (check(i,r)){
                    for (int j=1;j<=m;++j) q[j]=now[j];
                    l=r;
                }
                break;
            }
            int mid=(l+r)>>1;
            if (check(i,mid)){
                for (int j=1;j<=m;++j) q[j]=now[j];
                l=mid;
            }else r=mid-1;
        }
        if (l-i+1>ans){
            ans=l-i+1;
            for (int j=1;j<=m;++j) ans1[j]=q[j];
        }
    }
    for (int i=1;i<=m;++i) cout<<ans1[i]<<' ';
    cout<<'\n';
    return 0;
}
```


---

## 作者：Arghariza (赞：0)

发现即求一个最大的区间 $[l,r]$，使得 $\sum\limits_{i=1}^{m}\max\limits_{j=l}^{r}\{a_{j,i}\}\le k$，$a_{i,j}$ 表示第 $i$ 个人第 $j$ 种属性的值。

## Solution 1

考虑枚举左端点 $l$，发现如果固定这个端点，则 $\sum\limits_{i=1}^{m}\max\limits_{j=l}^{r}\{a_{j,i}\}$ 一定随着 $r$ 增大而增大。并且如果对于 $l<l'$，有 $r$ 使得 $\sum\limits_{i=1}^{m}\max\limits_{j=l}^{r}\{a_{j,i}\}\le k$，则 $\sum\limits_{i=1}^{m}\max\limits_{j=l'}^{r}\{a_{j,i}\}$ 也一定满足。于是满足条件最大的 $r$ 一定是单调递增的，于是我们可以使用双指针在 $O(nm)$ 的复杂度内解决。

## Solution 2

还是固定左端点 $l$，发现右端点 $r$ 满足单调性，可以二分确定。

二分右端点 $r$，用 `st` 表可以预处理出区间最大值，所以 `check` 可以 $O(m)$，总复杂度 $O(nm\log n)$。

只写了第二种方法的代码，因为好写。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int maxm = 20;
int n, m, k, la, ra, ta, a[maxn][10], f[maxn][maxm][10];

int query(int l, int r, int k) {
	int len = log2(r - l + 1);
	return max(f[l][len][k], f[r - (1 << len) + 1][len][k]);
}

int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			a[i][j] = read();
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) f[j][0][i] = a[j][i];
		for (int j = 1; (1 << j) <= n; j++) {
			for (int k = 1; k + (1 << j) - 1 <= n; k++) {
				f[k][j][i] = max(f[k][j - 1][i], f[k + (1 << (j - 1))][j - 1][i]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		int sum = 0;
		for (int j = 1; j <= m; j++) {
			sum += a[i][j];
		}
		if (sum > k) continue;
		int l = i, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			int tp = 0;
			for (int j = 1; j <= m; j++) {
				tp += query(i, mid, j);
			}
			if (tp > k) r = mid - 1;
			else {
				l = mid + 1;
				if (ta < mid - i + 1) {
					ta = mid - i + 1;
					la = i;
					ra = mid;
				}
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		write(query(la, ra, i)), putchar(' ');
	}
	return 0;
}

```

---

## 作者：AlicX (赞：0)

## Solution 

首先对题目进行转化：因为共有 $k$ 次操作，但是 $k \leq 10^9$，枚举不太现实，且没有单调性，所以考虑将区间 $[l,r]$ 能被消灭的条件变为 $\sum\limits_{i=1}^{m}\max\limits_{l \leq j \leq r} a_j \leq k$，因为加入区间内的每个属性的最大值之和能被去除，那么小于最大值的自然也可以被去除。

继续思考性质可以发现：对于 $[l,r]$ 这段区间，当 $l$ 变大时，$\sum\limits_{i=1}^{m}\max\limits_{l+1 \leq j \leq r} a_j$ 一定不增，所以考虑用双指针维护。每次 $r$ 向右移动时，$l$ 向右移动到最小的满足条件的下标，此时答案一定最优。

至于维护区间最大值，用线段树维护即可。时间复杂度为 $O(nm \log n)$

```cpp
#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e5+10,M=7,INF=1e9+7;  
int n,m,k; 
int ans[M];  
int a[N][M]; 
struct Node{
	int l,r; 
	int w[M]; 
}tr[N<<2]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
};  
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void pushup(int u){
	for(int i=1;i<=m;i++) tr[u].w[i]=max(tr[u<<1].w[i],tr[u<<1|1].w[i]); 
}
il void build(int u,int l,int r){ 
	tr[u]={l,r}; 
	if(l==r){ 
		for(int i=1;i<=m;i++) tr[u].w[i]=a[l][i]; 
		return ; 
	} int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
il int query(int u,int l,int r,int s){ 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w[s]; 
	int mid=tr[u].l+tr[u].r>>1,w=0; 
	if(l<=mid) w=query(u<<1,l,r,s); 
	if(r>mid) w=max(w,query(u<<1|1,l,r,s)); 
	return w; 
} 
il bool check(int l,int r){ 
	int res=0; 
	for(int i=1;i<=m;i++) res+=query(1,l,r,i); 
	return (res>k);   
} 
signed main(){ 
	n=read(),m=read(),k=read(); int l=1,res=0;  
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=read(); build(1,1,n); 
	for(int r=1;r<=n;r++){ 
		while(l<=r&&check(l,r)) l++; 
		if(!check(l,r)){ 
			if(r-l+1>res){
				res=r-l+1; 
				for(int i=1;i<=m;i++) ans[i]=query(1,l,r,i); 
			} 
		} 
	} for(int i=1;i<=m;i++) printf("%d ",ans[i]); puts(""); 
	return 0;
} /* */ 
```

CSP2023 RP++。



---

## 作者：45dino (赞：0)

枚举区间的左端点，计算在满足要求的情况下右端点最远能到哪里。

假如区间是 $[l,r]$，那么把该区间所有机器全部销毁的代价是 
$$\sum_{i=1}^m \max_{j=l}^r a_{i,j}$$
所以这个是随着区间的增长单调递增的。基于这一点，可以用双指针或者二分去求，要用线段树或 ST 表进行维护，复杂度为 $\Theta(m\times n\log_2 n)$。

然而这一题也可以用单调队列做，复杂度为 $\Theta(n\times m)$。这是我万万没想到的。

总结：还是菜了点。

---
Upd 2021/9/15: 修复了空格问题。

---

