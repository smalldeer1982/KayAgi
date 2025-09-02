# [ABC377D] Many Segments 2

## 题目描述

给定长度为 $N$ 的正整数列 $L=(L_1,L_2,\ldots,L_N),R=(R_1,R_2,\ldots,R_N)$ 和整数 $M$。

求同时满足以下条件的整数组 $(l,r)$ 的个数。

- $1\le l\le r\le M$

- 对于所有 $1\le i\le N$，区间 $[l,r]$ 不完全包含区间 $\left[L_i,R_i\right]$。

## 说明/提示

#### 约定

- $1\le N,M\le 2\times 10^5$
- $1\le L_i\le R_i\le M$
- 所有输入均为整数


 $(l,r)=(1,1),(2,2),(2,3),(3,3),(4,4)$ 这 $5$ 个都满足条件。

例如 $(l,r)=(1,3)$ 不满足条件。这是因为区间 $[1,3]$ 完全包含了区间 $[1,2]$。


此时不存在满足条件的整数对。


Translation by @[$\frak{Lorentz}$](/user/1232305) and @[Jie_XuSheng](/user/1332013)。

## 样例 #1

### 输入

```
2 4
1 2
3 4```

### 输出

```
5```

## 样例 #2

### 输入

```
6 5
1 1
2 2
3 3
4 4
5 5
1 5```

### 输出

```
0```

## 样例 #3

### 输入

```
6 20
8 12
14 20
11 13
5 19
4 11
1 6```

### 输出

```
102```

# 题解

## 作者：___PatrickChen___ (赞：12)

显然地，我们有一个性质：若 $(l, r)$ 符合条件，则 $(l + 1, r)$ 也符合条件。

考虑处理出 $a_r$ 表示对于任意一个正整数 $l$ 当且仅当 $a_r\le l\le r$ 时 $(l, r)$ 符合条件。那么答案就是 $\sum\limits_{r = 1}^m (r - a_r + 1)$。

关于处理 $a_r$，我们可以得到 $a_r = \max\{a_{r - 1},\max\limits_{R_i = r}L_i + 1\}$。因此对于每个 $R_i = r$ 统计最大值然后进行前缀最大值即可。

code: 

```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll = long long;

const ll N = 2e5 + 5;

int n, m, a[N];
ll ans;

void init() {}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) a[i] = 1;
	for (int i = 1, l, r; i <= n; ++i) {
		cin >> l >> r;
		a[r] = max(a[r], l + 1);
	}
	for (int i = 1; i <= m; i++) a[i] = max(a[i], a[i - 1]);
	for (int i = 1; i <= m; i++) ans += i - a[i] + 1;
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int _ = 1;
	// cin >> _;
	init();
	while (_--) solve();
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：4)

估值要掉了，写篇题解。

大水题呀！

发现当 $l\le L$ 且 $R \le r$ 时不满足。

所以对于每个 $R$，只用考虑最大的 $L$。

记录上面这个信息很轻松。

接着，枚举每个 $r$。

只有之前所有的 $L$ 的最大值 $maxL<l$ 是满足题意，直接统计即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int l[200010],r[200010];
int mx[200010];
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
	for(int i=1;i<=n;i++) mx[r[i]]=max(mx[r[i]],l[i]);//求 l 的 max 
	int ans=0,ml=0;
	for(int r=1;r<=m;r++) ml=max(ml,mx[r]),ans+=r-ml;//统计 
	cout<<ans;//优雅 
	return 0;
}
```

---

## 作者：zlqwq (赞：4)

## 思路：

维护一个堆。

我们先将所有区间将右端点的贡献来排序。

我们这样就可以直接 $O(N)$ 的去寻找最好的右端点 $r$，然后在找到右端点的基础上继续寻找贡献最大的左端点 $l$ 即可。

## 代码：


```cpp
//zzl ak cspj2024!
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
#define PII pair<int,int>
using namespace std;
int n,m;
int l[200005],r[200005];
struct node {
	int l,r;
}ed[200005];
bool cmp(node a,node b){
	/*
	if(a.l==b.l)return a.r<b.r;
	else*/ return a.l<b.l;
}
priority_queue<int,vector<int>,greater<int> > q;
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>l[i]>>r[i];
		ed[i]=node{l[i],r[i]};
	}
	sort(ed+1,ed+1+n,cmp);
	int ans=0,p=n;
	for(int i=m;i>=1;--i){
		while(ed[p].l>=i&&p){
			q.push(ed[p].r);
			p--;
		}
		int o=m+1-i;
		if(q.size()){
			o=min(o,q.top()-i);
		}
		ans+=o;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liuziqin (赞：4)

## 思路

由于 $m \le 2 \times 10^5$，因此可以直接枚举每条合法线段的右端点 $R$。

对于枚举到的右端点 $R$，如果某条线段 $[l,r]$ 被完全包含，仅当 $r \le R$ 且 $l \ge L$。因此我们可以先将所有线段按**右端点**权值进行排序，在枚举 $R$ 时用双指针找出所有的 $r \le R$ 的线段，再用一个**大根堆**维护满足条件的最大的左端点 $l$，最后统计答案即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
const int N=200005;
struct line{
	int l,r;
}a[N];
bool cmp(line a,line b){
	return a.r<b.r;
}
signed main(){
	int m,n;
	cin>>m>>n;
	for(int i=1;i<=m;i++)cin>>a[i].l>>a[i].r;
	sort(a+1,a+m+1,cmp);//按右端点排序
	priority_queue<int>q;
	q.push(0);//初始化
	int ans=0;
	for(int i=1,j=1;i<=n;i++){
		while(j<=m&&a[j].r<=i){
			q.push(a[j].l);
			j++;
		}//用双指针维护合法线段
		ans+=i-q.top();//统计答案
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：kczw (赞：1)

# 题意
给出 $N$ 个区间 $[l_i,r_i](1\le i\le N,l_i\le r_i\le M)$，问有多少个区间 $[l,r](1\le l\le r\le M)$ 满足不会包含任意给出区间。
# 思路
先只求所有左端点为 $1$ 的合法区间数量，若当右端点为 $R$ 时已经包含了某个给出区间导致区间 $[l,R]$ 不合法了，那么区间 $[l,R+1]$ 也是不合法的。所以对于一个左端点，合法的右端点一定是连续的，所以我们只需要求出对于每个左端点的最大合法右端点即可。

最开始不考虑任何给出区间时，对于左端点 $1$ 的最大合法右端点为 $M$。考虑计入一个给出区间 $[l_1,r_1]$，不难知道最小不合法右端点为 $r_1$，所以最大合法右端点为 $r_1-1$。考虑再计入一个给出区间 $[l_2,r_2]$，同理，最大合法右端点为 $\min(r_1,r_2)-1$。

对于一个给出区间 $[l,r]$ 易知，左端点如果在 $l$ 右侧，则无论如何都不会包含区间 $[l,r]$，所以对于合法右端点的影响只对左端点小于等于 $l$ 的有效。

根据情况维护区间修改，单点查询最小值即可，此处使用线段树。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=2e5+5;
int n,m;
struct SGT{
	int mn[M<<2],lz[M<<2];
	inline void build(int p,int l,int r){
		mn[p]=lz[p]=m;
		if(l==r)return;
		build(p<<1,l,l+r>>1);
		build(p<<1|1,(l+r>>1)+1,r);
	}
	inline void uplz(int p,int w){
		mn[p]=min(mn[p],w);
		lz[p]=min(lz[p],w);
	}
	inline void pushdown(int p){
		if(lz[p]^m){
			uplz(p<<1,lz[p]);
			uplz(p<<1|1,lz[p]);
			lz[p]=m;
		}
	}
	inline void modify(int p,int l,int r,int L,int R,int w){
		if(L<=l&&r<=R)return uplz(p,w);
		pushdown(p);
		if(L<=l+r>>1)modify(p<<1,l,l+r>>1,L,R,w);
		if(R>l+r>>1)modify(p<<1|1,(l+r>>1)+1,r,L,R,w);
	}
	inline long long query(int p,int l,int r){
		if(l==r)return max(mn[p]-l+1,0);
		pushdown(p);
		return query(p<<1,l,l+r>>1)+query(p<<1|1,(l+r>>1)+1,r);
	}
}tr;
inline void solve(){
	scanf("%d%d",&n,&m);
	tr.build(1,1,m);
	for(int i=1,l,r;i<=n;i++){
		scanf("%d%d",&l,&r);
		tr.modify(1,1,m,1,l,r-1);
	}
	printf("%lld",tr.query(1,1,m));
}
int main(){
	int t=1;//scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：sherry_lover (赞：0)

# AT_abc377_d [ABC377D] Many Segments 2 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc377_d)

## 思路

给一种不用双指针的做法。

考虑位置 $i$ 的答案是什么，是满足 $l_j \ge i$ 的所有的 $j$ 的 $\min r_j$ 减去 $i$。

设 $ans_i$ 表示上面所说的 $\min r_j$，先把每个  `ans[a[i].l] = min(ans[a[i].l],a[i].r)`，然后将答案数组从后往前扫一遍后缀最小值，注意要初始化成 $m+1$。

时间复杂度 $O(n+m)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r;
}a[200005];
int n,m,ans[200005];
long long tot;
bool cmp(node x,node y){
    return x.l > y.l;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++) cin >> a[i].l >> a[i].r;
	for(int i = 1;i <= m+1;i++) ans[i] = m+1;
	for(int i = 1;i <= n;i++) ans[a[i].l] = min(ans[a[i].l],a[i].r);
	for(int i = m;i >= 1;i--)
	{
		ans[i] = min(ans[i],ans[i+1]);
		tot += (ans[i]-i);
	}
	cout << tot;
    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

一个区间 $[L_i,R_i]$ 对 $[l,r]$ 的限制是：若 $l\in[1,L_i]$，则 $R\in[1,R_i-1]$。

枚举 $l$，$r$ 的最大值为所有 $L_i\ge l$ 的 $R_i-1$ 的最小值。考虑从大到小枚举 $l$，限制会不断增加，动态维护最小值即可。

```cpp
int n,m; ll ans; pii p[N]; vi v[N];
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) p[i]={rd(),rd()},v[p[i].fir].pb(i);
	for(int i=m,mn=m+1;i;i--) {for(int x:v[i]) cmin(mn,p[x].sec); ans+=mn-i;}
	wrll(ans,"\n");
}
```

---

## 作者：cjh_trailblazer (赞：0)

[原题面](https://atcoder.jp/contests/abc377/tasks/abc377_d)
## 题目分析：
考虑每次给定的序列，我们可以固定左端点，找到它可选的最大右端点，可以在输入时处理第一遍，因为这里对于左端点来说一定是输入的右端点。  
因为有一些点没有输入，那么我们再从右往左扫一遍，处理那些没处理过的点，因为对于一个点来说，它可取到的右端点一定小于等于它右边的数可取到的右端点，最后累计答案即可。
## [Code](https://atcoder.jp/contests/abc377/submissions/59219474)

---

## 作者：daitangchen2008 (赞：0)

## 分析：
思路：排序是必要的，我们把每组限制条件按左端点递减排序，再按值域枚举每个左端点。如果一组条件的左端点等于现在枚举到的左端点就把右端点加入优先队列。此时以当前枚举到的值为左端点的右端点最大值即为所有枚举到了的限制条件的右端点的值，用优先队列维护即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans;
const int N=2e5+10;
struct node
{
	int x;
	int y;
}t[N];
bool cmp(node x,node y)
{
	if(x.x==y.x)
		return x.y<y.y;
	return x.x<y.x;
}
priority_queue<int>q;
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>t[i].x>>t[i].y;
	sort(t+1,t+n+1,cmp);
	int l=n;
	q.push(-m-1);
	for(int i=m;i>=1;i--)
	{
		while(l>=1&&t[l].x==i)
		{
			q.push(-t[l].y);
			l--;
		}
		ans+=max((long long)0,-q.top()-i); 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

