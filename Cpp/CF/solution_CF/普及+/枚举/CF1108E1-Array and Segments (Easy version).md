# Array and Segments (Easy version)

## 题目描述

给定你一个长度为 $n$ 的数组 $a$，再给定你 $m$ 对数字 $[l_i,r_i]$。你可以选择其中的几对数字作为两个端点，再将数组 $a$ 中的两个端点内的数字全部减一。（例如现有一对 $[l_i,r_i]$ 为 $[1,3]$ ，而数组 $a$ 为 `1 2 3 4 5`，若使用这对 $[l_i,r_i]$ 数组就会变成 `0 1 2 4 5`）

现在请你求出怎样使得数组 $a$ 中的最大值减去最小值最大。

## 样例 #1

### 输入

```
5 4
2 -2 3 1 2
1 3
4 5
2 5
1 3
```

### 输出

```
6
2
1 4 
```

## 样例 #2

### 输入

```
5 4
2 -2 3 1 4
3 5
3 4
2 4
2 5
```

### 输出

```
7
2
3 2 
```

## 样例 #3

### 输入

```
1 0
1000000
```

### 输出

```
0
0

```

# 题解

## 作者：liruixiong0101 (赞：6)

### 题意简述：
给你 $n$ 个数 $a_1,a_2,\dots,a_{n-1},a_n$ 再给你 $2\times m$ 个数，分别为 $l_1,l_2,\dots,l_{m-1},l_m$ 和 $r_1,r_2,\dots,r_{m-1},r_m$，输入的 $r_i,l_i$ 分别为一条 $[l_i,r_i]$ 的线段，请你选出若干条线段，在这条线段里的每一个数都减一，请问最后 $a$ 数组里的最大值减最小值最大为多少？

### 思路：
这一题的 $n$ 范围较小，$n,m\le300$，$O(n^3)$ 及以下的时间复杂度都可过。

------------

首先暴力做，就是跑一遍 dfs 每次考虑是选这条线段还是不选，若选则将这条线段里的所有数减一，否则不减，时间复杂度：$O(2^m)$，不可过。~~本人没试过，不可确定暴力能否过。~~

------------

因为最后的最大最小值都不确定，所以我们需要枚举最后的最大最小值，我们仔细想一想就可以知道，枚举最大最小值同时满足最大值最大和最小值最小，十分麻烦，其实我们只需要枚举最小值即可（枚举最大值也可以），只要让最小值最小，最大值减最小值的差也就最大了。  
我们用 $get(x)$ 函数表示以第 $x$ 个数为最小值所可以得到的最大的最大值减最小值的差，函数代码如下：
```cpp
int get(int x){
	int b[N] = {};
	memcpy(b , a , sizeof(a));//将a数组的值赋予b数组
	for(int i = 1; i <= m; i++){
		if(l[i] <= x && r[i] >= x){
			//若这条线段包含x那么使用这一条线段
			for(int j = l[i]; j <= r[i]; j++){
				b[j]--;
			}
		}
	}
	int maxn = INT_MIN , minn = INT_MAX;
	for(int i = 1; i <= n; i++){
		maxn = max(maxn , b[i]);
		minn = min(minn , b[i]); 
	}//找到最大最小值
	return maxn - minn;//返回最大值减最小值的差
}
```
然后你就会发现这段代码：
```cpp
for(int j = l[i]; j <= r[i]; j++){
	b[j]--;
}
```
就是区间修改，于是就可以用上差分，修改后 $get(x)$ 函数就变成 $O(n)$ 的时间复杂度了，代码如下：
```cpp
int get(int x){
    int d[N] = {};//差分数组
    for(int i = 1; i <= n; i++){
        d[i] = a[i] - a[i - 1];
    }
    for(int i = 1; i <= m; i++){
        if(l[i] <= x && r[i] >= x){
            d[r[i] + 1]++ , d[l[i]]--;
        }//区间修改
    }
    int maxn = INT_MIN , minn = INT_MAX;
    for(int i = 1; i <= n; i++){
        d[i] += d[i - 1];
        maxn = max(maxn , d[i]);
        minn = min(minn , d[i]);
    }
    return maxn - minn;
}
```
感谢 @[yqr123YQR](https://www.luogu.com.cn/user/554886) 发现这题可以用差分做。

---


设计好 $get(x)$ 函数，我们枚举最小值，找到 $get(i)$ 最小的一个 $i$ 记为 $p$，输出 $get(p)$ 为第一行的答案，在枚举所有的线段，输出使用的线段和使用的线段数即可。  
此方法的时间复杂度：枚举 $O(n)$，$get(x)$ 函数 $O(n)$。  
总时间复杂度  $O(n^2)$，时间没问题，可以试试。

------------
代码挺简单的，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 305;
int n , m;
int a[N] , l[N] , r[N];
int anss[N];
int get(int x){
    int d[N] = {};
    for(int i = 1; i <= n; i++){
        d[i] = a[i] - a[i - 1];
    }
    for(int i = 1; i <= m; i++){
        if(l[i] <= x && r[i] >= x){
            d[r[i] + 1]++ , d[l[i]]--;
        }
    }
    int maxn = INT_MIN , minn = INT_MAX;
    for(int i = 1; i <= n; i++){
        d[i] += d[i - 1];
        maxn = max(maxn , d[i]);
        minn = min(minn , d[i]);
    }
    return maxn - minn;
}
int main(){
	scanf("%d%d" , &n , &m);
	for(int i = 1; i <= n; i++) scanf("%d" , &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d%d" , &l[i] , &r[i]);
	//输入
	int x , ans = INT_MIN;
	for(int i = 1; i <= n; i++){
		if(ans < get(i)) x = i , ans = get(i);
	}//求得最大的差值和最后的最小值
	printf("%d\n" , ans);
	ans = 0;
	for(int i = 1; i <= m; i++){
		if(l[i] <= x && r[i] >= x){
			anss[++ans] = i;
		}
	}//求出需要使用的线段
	printf("%d\n" , ans);
	for(int i = 1; i <= ans; i++) printf("%d " , anss[i]);//输出
	return 0;
}
```

---

## 作者：whiteqwq (赞：2)

[CF1108E1 Array and Segments (Easy version)](https://www.luogu.com.cn/problem/CF1108E1)&[CF1108E2 Array and Segments (Hard version)](https://www.luogu.com.cn/problem/CF1108E2)解题报告:

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1766551)

## 题意
- 给定一个长度为$n$的序列$a$,你可以进行$m$次操作中的任意一些操作,每个操作为$[l,r]$,表示让区间$[l,r]$减一,求使得序列极差最大的操作方案.
- Easy Version:$1\leqslant n\leqslant 300,0\leqslant m\leqslant 300$.
- Hard Version:$1\leqslant n\leqslant 10^5,0\leqslant m\leqslant 300$.

## 分析
首先,因为极差=最大值-最小值,而一个同时包含最大值和最小值的区间如果不改变最大值和最小值的位置,是不会对极差造成影响的,因此我们有一个初步的想法:

我们枚举最大值位置,然后进行所有不包含最大值位置的操作,并得到最小值,最后将所有的极差取$\max$.

这样做的复杂度是$O(nq\log n)$的,可以通过Easy Version.

优化也很简单,我们发现上述算法枚举的操作区间或起来都不是全集(要给最大值留位置),很容易想到枚举没有进行的操作,因为操作区间或不是全集,因此没有进行的操作区间与起来不为空集,这样至少会有一个位置没有操作过,可以成为最大值.

我们先加入所有区间,然后枚举每一个位置,先撤销以这个位置开始的操作,求得一个极差,然后再重新进行以这个位置结束的操作,这样我们就能保证求极差时撤销的区间都包含当前位置.

只需要写一个区间加,区间$\min/\max$的线段树就好了.

时间复杂度:$O(n+m\log n)$,可以通过Hard Version.

## 代码
```
#include<stdio.h>
#include<vector>
#define inf 1000000000
using namespace std;
const int maxn=100005,maxk=maxn<<2;
int n,m,ans,pos,cnt;
int a[maxn],lc[maxk],rc[maxk],maxx[maxk],minn[maxk],lazy[maxk],xx[maxn],yy[maxn];
vector<int>l[maxn],r[maxn];
inline void pushup(int now){
	maxx[now]=max(maxx[lc[now]],maxx[rc[now]]);
	minn[now]=min(minn[lc[now]],minn[rc[now]]);
}
inline void getlazy(int now,int v){
	maxx[now]+=v,minn[now]+=v,lazy[now]+=v;
}
inline void pushdown(int now){
	if(lazy[now]==0)
		return ;
	getlazy(lc[now],lazy[now]),getlazy(rc[now],lazy[now]);
	lazy[now]=0;
}
void build(int l,int r,int now){
	if(l==r){
		maxx[now]=minn[now]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	lc[now]=now<<1,rc[now]=now<<1|1;
	build(l,mid,lc[now]),build(mid+1,r,rc[now]);
	pushup(now);
}
void update(int l,int r,int now,int L,int R,int v){
	if(L<=l&&r<=R){
		getlazy(now,v);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(now);
	if(L<=mid)
		update(l,mid,lc[now],L,R,v);
	if(mid<R)
		update(mid+1,r,rc[now],L,R,v);
	pushup(now);
}
int main(){
	maxx[0]=-inf,minn[0]=inf;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		xx[i]=x,yy[i]=y;
		l[x].push_back(y),r[y].push_back(x);
		update(1,n,1,x,y,-1);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<l[i].size();j++)
			update(1,n,1,i,l[i][j],1);
		if(maxx[1]-minn[1]>ans)
			ans=maxx[1]-minn[1],pos=i;
		for(int j=0;j<r[i].size();j++)
			update(1,n,1,r[i][j],i,-1);
	}
	printf("%d\n",ans);
	for(int i=1;i<=m;i++)
		if(xx[i]>pos||yy[i]<pos)
			cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=m;i++)
		if(xx[i]>pos||yy[i]<pos)
			printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1108E1（luogu）](https://www.luogu.com.cn/problem/CF1108E1)

[CF1108E2（luogu）](https://www.luogu.com.cn/problem/CF1108E2)

[CF1108E1（codeforces）](https://codeforces.com/problemset/problem/1108/E1)

[CF1108E2（codeforces）](https://codeforces.com/problemset/problem/1108/E2)


# 解题思路

这篇题解分 E1，E2 两个部分来讲。

## E1 sol：

我们发现可以暴力枚举最后经过所有操作之后的最大值，那么显然的，我们将不会做任何经过这个位置的操作，会做不经过这个区间的所有操作。

直接暴力进行操作即可。

时间复杂度 $O(n^2 + nm)$。

## E2 sol：

发现这个暴力的过程可以使用区间加，区间最大值，区间最小值的线段树来维护，此时时间复杂度变为 $O(nm \log n)$，并不能通过此题，那么此时，我们可以再打一个标记表示当前树内是否加过这个区间，由于区间是连续的一段，并且我们枚举的最大值也是连续的一段，因此有一个性质，那就是每个区间至多被操作过两次，此时时间复杂度变为 $O(n + m \log n)$，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll int
#define pb push_back
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define mid ((l+r)>>1)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
/*
0 -4 1 1 2
*/
ll n,m;
ll id;
ll maxn;
ll a[100010],b[100010],c[100010];
ll l[100010],r[100010];
ll vis[510];
struct node{
    ll l,r,minn,maxn,tag;
}tree[400010];
struct nide{
	ll x,id;
}d[100010];
bool cmp(nide x,nide y){
	return x.x<y.x;
}
void pushup(ll x){
    tree[x].minn=min(tree[x*2].minn,tree[x*2+1].minn);
    tree[x].maxn=max(tree[x*2].maxn,tree[x*2+1].maxn);
}
void pushdown(ll x)
{
    tree[x*2].minn+=tree[x].tag;
    tree[x*2+1].minn+=tree[x].tag;
    tree[x*2].tag+=tree[x].tag;
    tree[x*2+1].tag+=tree[x].tag;
    tree[x*2].maxn+=tree[x].tag;
    tree[x*2+1].maxn+=tree[x].tag;
    tree[x].tag=0;
}
void build(ll x,ll l,ll r)
{
    tree[x].l=l,tree[x].r=r;
    if(l==r)
    {
        tree[x].minn=a[l];
        tree[x].maxn=a[l];
        return ;
    }
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void add(ll x,ll l,ll r,ll y)
{
    if(l<=tree[x].l && tree[x].r<=r)
    {
        tree[x].minn+=y;
        tree[x].maxn+=y;
        tree[x].tag+=y;
        return ;
    }
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2;
    if(l<=Mid)
        add(x*2,l,r,y);
    if(Mid<r)
        add(x*2+1,l,r,y);
    pushup(x);
}
ll querymin(ll x,ll l,ll r)
{
    if(l<=tree[x].l && tree[x].r<=r)
        return tree[x].minn;
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2,ans=1e9;
    if(l<=Mid)
        Min(ans,querymin(x*2,l,r));
    if(Mid<r)
        Min(ans,querymin(x*2+1,l,r));
    return ans;
}
ll querymax(ll x,ll l,ll r)
{
    if(l<=tree[x].l && tree[x].r<=r)
        return tree[x].maxn;
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2,ans=-1e9;
    if(l<=Mid)
        Max(ans,querymax(x*2,l,r));
    if(Mid<r)
        Max(ans,querymax(x*2+1,l,r));
    return ans;
}
ll check(ll x)//x最终为最大值 
{
//	forl(i,0,n+2)
//		c[i]=0;
	forl(i,1,m)
	{
		if(l[i]>x || r[i]<x)
		{
			if(!vis[i])
				add(1,l[i],r[i],-1),vis[i]=1;
		}
		else
		{
			if(vis[i])
				add(1,l[i],r[i],1),vis[i]=0;
		}
	}
			//c[l[i]]--,c[r[i]+1]++;
//	forl(i,1,n)
//		c[i]+=c[i-1];
	ll maxn=-1e9,minn=1e9;
	maxn=querymax(1,1,n),minn=querymin(1,1,n);
//	forl(i,1,n)
//		cout<<querymax(1,i,i)<<' ';
//	cout<<endl;
//	forl(i,1,m)
//		if(l[i]>x || r[i]<x)
//			add(1,l[i],r[i],1);
///	forl(i,1,n)
//		Max(maxn,c[i]+a[i]),
//		Min(minn,c[i]+a[i]);
//		cout<<a[i]+c[i]<<' ';
//	cout<<endl;
//	cout<<"<"<<minn<<' '<<maxn<<endl;
	return maxn-minn;
}
void check2(ll x)//x最终为最大值 
{
	vector<ll>ans;
	forl(i,0,n+2)
		c[i]=0;
	forl(i,1,m)
		if(l[i]>x || r[i]<x)
			ans.pb(i);
	cout<<ans.size()<<endl;
	for(auto i:ans)
		cout<<i<<' ';
//		{
//			cout<<
//		}
//			c[l[i]]--,c[r[i]+1]++;
//	forl(i,1,n)
//		c[i]+=c[i-1];
//	ll maxn=-1e18,minn=1e18;
///	forl(i,1,n)
//		Max(maxn,c[i]+a[i]),
//		Min(minn,c[i]+a[i]);
//		cout<<a[i]+c[i]<<' ';
//	cout<<endl;
//	cout<<minn<<' '<<maxn<<endl;
//	return maxn-minn;
}
void solve()
{
	_clear();
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i];//,d[i].x=a[i],d[i].id=i;
	build(1,1,n);
	forl(i,1,m)
		cin>>l[i]>>r[i];
	maxn=-1e9;
//	check(5);
//	sort(d+1,d+1+n,cmp);
	forl(i,1,n)
		if(Max(maxn,check(i)))
			id=i;
/*	forr(i,n,max(5001,n-5000))
		if(Max(maxn,check(i)))
			id=i;	*/
	cout<<maxn<<endl;
	check2(id);
	
}
int main()
{
//	freopen("tst.txt","r",stdin);
//	freopen("sans.txt","w",stdout);
	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
观察数据，这道题的数据量非常小，所以我们可以考虑用暴力的算法。一层循环枚举最大值的下标，再用一层循环枚举最小值的下标，最后用一层循环枚举所有区间来选择区间。

如果当前区间**包括最大值又包括最小值**，最大值的差和最小值的差**不会改变**，对答案没有优化**不选择**。

如果当前区间只**包括最大值**，则最大值的差和最小值的差**减去一**，对答案没有优化，**不选择**。

如果当前区间只**包括最小值**，则最大值的差和最小值的差**加上一**，对答案有优化，**选择**。

只要每次选择区间选择只包括最小值的，然后最后取全局最优输出就是答案了。时间复杂度 $O(n^2m)$，顺利拿下。

code:
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m,tt;
struct st{
	int x,y;
}b[301];
struct stt{
	int ans,t;
}c[90601];
int a[301];
bool cmp(stt a,stt b)
{
	return a.ans>b.ans;
}
vector<int> v[90601];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		cin>>b[i].x>>b[i].y;
	}
	for(int i=1;i<=n;i++)//最大 
	{
		for(int j=1;j<=n;j++)//最小 
		{
			int ans=a[i]-a[j];
			tt++;
			for(int k=1;k<=m;k++)
			{
				if(b[k].x<=j&&b[k].y>=j&&!(b[k].x<=i&&b[k].y>=i))//判断区间
				{
					ans++;
					v[tt].push_back(k);
				}
			}
			c[tt].ans=ans;
			c[tt].t=tt;
		}
	}
	sort(c+1,c+tt+1,cmp);
	cout<<c[1].ans<<"\n";
	cout<<v[c[1].t].size()<<"\n";
	for(auto it:v[c[1].t])
	{
		cout<<it<<" ";
	}
	return 0;
}
```

---

## 作者：二叉苹果树 (赞：0)

依次枚举每个点 $i$ 作为最大值，然后操作所有不包含 $i$ 的区间，统计极差。时间复杂度 $\mathcal{O} \left(mn\log n\right)$，可以轻松通过 Easy Version。

区间修改和最值的维护使用线段树即可。

这里给出时间复杂度为 $\mathcal{O} \left(m\log n\right)$ 的代码，把操作的部分改成对于每个点的全部修改就是暴力 $\mathcal{O} \left(mn\log n\right)$ 的做法了。

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define lc (x * 2)
#define rc (x * 2 + 1)

int a[maxn], lzy[maxn << 2];
struct node
{
    int val, max, min;
} t[maxn << 2];
void pushup(int x)
{
    t[x].max = std::max(t[lc].max, t[rc].max);
    t[x].min = std::min(t[lc].min, t[rc].min);
}
void build(int x, int l, int r)
{
    if (l == r)
    {
        t[x].val = a[l];
        t[x].max = a[l];
        t[x].min = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(x);
}
void maketag(int x, int len, int k)
{
    t[x].val += len * k;
    t[x].max += k;
    t[x].min += k;
    lzy[x] += k;
}
void pushdown(int x, int l, int r)
{
    int mid = (l + r) >> 1;
    maketag(lc, mid - l + 1, lzy[x]);
    maketag(rc, r - mid, lzy[x]);
    lzy[x] = 0;
}
bool inrange(int l, int r, int L, int R)
{
    return (l >= L && r <= R);
}
bool outrange(int l, int r, int L, int R)
{
    return (l > R || r < L);
}
void update(int x, int l, int r, int L, int R, int k)
{
    if (inrange(l, r, L, R))
        maketag(x, r - l + 1, k);
    else if (!outrange(l, r, L, R))
    {
        int mid = (l + r) >> 1;
        pushdown(x, l, r);
        update(lc, l, mid, L, R, k);
        update(rc, mid + 1, r, L, R, k);
        pushup(x);
    }
}
int l[maxn], r[maxn];
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, p, ans = 0, cnt = 0;
    std::vector<int> pre[maxn], nxt[maxn];
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    build(1 ,1, n);
    for (int i = 1; i <= m; i++)
    {
        std::cin >> l[i] >> r[i];
        update(1, 1, n, l[i], r[i], -1);
        nxt[l[i]].push_back(r[i]);
        pre[r[i]].push_back(l[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < nxt[i].size(); j++)
            update(1, 1, n, i, nxt[i][j], 1);
        if (t[1].max - t[1].min > ans)
            ans = t[1].max - t[1].min, p = i;
        for (int j = 0; j < pre[i].size(); j++)
            update(1, 1, n, pre[i][j], i, -1);
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= m; i++)
        if (outrange(p, p, l[i], r[i]))
            cnt++;
    std::cout << cnt << '\n';
    for (int i = 1; i <= m; i++)
        if (outrange(p, p, l[i], r[i]))
            std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}
```


---

## 作者：nikangle (赞：0)

# 题意简述

给出一个长度为 $n$ 的序列和对于该序列的 $m$ 个操作，在这 $m$ 个操作中，第 $i$ 个操作可以让序列中 ${l_i,r_i}$ 这段区间内的数都减 $1$。要求从这 $m$ 个操作中选出任意多个进行，让操作完成后序列中的最大值减最小值的差最大。

# 思路

## 概述

> **对于每个数，求出当它最小时，最大值与最小值的差，再在这当中找出最大值。**

总结起来就上面一句话。

具体来说，就是依次**遍历每一个位置**，设为 $i$，则假定**最小值**是 $a_i$。我们只需要使用所有包含第 $i$ 个位置的操作，**忽略**其他操作。最后从 $a_1\cdots a_n$ 中分别找到**最大**和**最小**的那一个，作差，更新最大值即可。

## 证明

选择第 $i$ 个操作，$\mathit{a}_{l_i,r_i}$ 中**任意两项**之间的差都**不会改变**，而**操作区间外**的数减去**操作区间内**的数比修改前多**一**。

在前面的思路中，对于第 $i$ 个数，我们**只选择**包含第 $i$ 个数的操作，所以每一次操作都**只会**让其他数减 $a_i$ 的差**不变或变大**。这样就能**保证**遍历到第 $i$ 个数时找到**最大的** $\max\limits_{i=1}^n \mathit{a}_i-\min\limits_{i=1}^n \mathit{a}_i$。

## 复杂度

在空间上不需要额外的空间，时间复杂度为 $O(n^2m+n^2)$。

## 优化

由于修改操作是区间减，所以想到可以用**差分**来优化一层循环，让时间复杂度变为 $O(nm+n^2)$。

# 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
}q[305];
int n,m,a[305],c[305],lxz[305],maxs[305],x,lmax=-100000000,lmin=100000000,cnt,maxx=0,maxn;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		lmax=max(lmax,a[i]);
		lmin=min(lmin,a[i]);
	}
	maxn=lmax-lmin;//一个规则都不使用的情况
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].x,&q[i].y);
	}
	for(int i=1;i<=n;i++){
		cnt=0;
		x=0;
		lmax=-100000000;
		lmin=100000000;
		for(int j=1;j<=n;j++){
			c[j]=a[j]-a[j-1];//维护差分数组
		}
		for(int j=1;j<=m;j++){
			if(q[j].y>=i&&q[j].x<=i){//如果第i个位置在第j个区间里
				c[q[j].x]--;
				c[q[j].y+1]++;
				lxz[++cnt]=j;
			}
		}
		for(int j=1;j<=n;j++){//求出最大值与最小值
			x=x+c[j];
			lmax=max(lmax,x);
			lmin=min(lmin,x);
		}
		if(lmax-lmin>maxn){
			maxx=cnt;
			maxn=lmax-lmin;
			for(int j=1;j<=cnt;j++){
				maxs[j]=lxz[j];
			} 
		}
	}
	cout<<maxn<<endl<<maxx<<endl;
	for(int i=1;i<=maxx;i++){
		printf("%d ",maxs[i]);
	}
	return 0;
}
```

#### 注：对于一个数据可能有多种达成差最大的方法，本代码与样例 $2$ 答案不同，但评测能过。

---

## 作者：linxuanrui (赞：0)

### 写在前面

前置知识（不会的请先了解一下，不然看不懂）：`vector` 和差分~~暴力~~。

这篇题解是 $O(n^2+nm)$ 的，因此加强版过不了。

### 思路

题目求的是最大值 - 最小值，因此**在最大值固定的时候，最小值越小差越大**。

因此，我们可以枚举最大值，再尽量使最小值变小。

我们将每个数作为最大值的情况都枚举一下，再算出最小值。

注意，**我们既然枚举这个数是最大的，就不要改变这个值**，而且再这个基础上还要使最小值最小，因此我们就把**所有不包含 $a_i$ 的 $l_i$ 与 $r_i$ 都减去**。

这里解释一下我的代码：（这里是解释代码，所以没用 $\LaTeX$，请不要以此原因打回）

+ 这里的 `vector` 是存储答案的，其中 `v[i]` 表示要选 `l[i]` 和 `r[i]`，`v2` 存储最优答案。

+ 因为每次选定 `l[i]` 和 `r[i]` 时，`a[l[i]]` 到 `a[r[i]]` 都要减 1，因此这里可以用差分数组。

### 代码

```cpp
#pragma GCC optmize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int INF = 0x3f3f3f3f;
int n,m,a[301],l[301],r[301],tmp,cf[301],tmp2[301],maxx,minn,ans = -INF;
//cf[i] 是差分数组
//tmp2[i] 是临时保存差分的数组
vector<int> v,v2;
//v 存储个顶点用到的 l[i] 和 r[i] 中的 i
//v2 保存最终答案
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++)cin >> a[i],cf[i] = a[i] - a[i - 1];
	for(int i = 1;i <= m;i++)cin >> l[i] >> r[i];
	for(int i = 1;i <= n;i++){
		tmp = 0;
		maxx = -INF,minn = INF;
		v.clear();//多测不清空，调 bug 两行泪
		memcpy(tmp2,cf,sizeof(cf));
		for(int j = 1;j <= m;j++){
            //枚举最大值，因此不能将 a[i] 也减去 
			if(l[j] > i || r[j] < i)tmp2[l[j]]--,tmp2[r[j] + 1]++,v.push_back(j);
		}
		for(int j = 1;j <= n;j++){
			tmp += tmp2[j];
			maxx = max(maxx,tmp);
			minn = min(minn,tmp);
		}
		if(maxx - minn > ans){
			v2.assign(v.begin(),v.end());
			ans = maxx - minn;
		}
	}
	cout << ans << endl << v2.size() << endl;
	for(int i = 0;i < v2.size();i++)cout << v2[i] << " ";
}
```

---

## 作者：andyli (赞：0)

考虑枚举最大值不动，执行所有其他操作来获得最小值。注意到 $m$ 较小，可以将区间上的坐标离散化，预处理每段初始的最大/最小值，然后暴力执行操作。时间复杂度 $O(n + m^2)$。

```cpp
int main() {
    dR(int, n, m);
    dRV(int, a, n);
    dRV(pi, b, m);

    vi c{0, n};
    for (auto&& [l, r]: b)
        c.eb(--l), c.eb(r);
    UNIQUE(c);
    for (auto&& [l, r]: b)
        l = LB(c, l), r = LB(c, r);
    vi mn(len(c) - 1, inf<int>);
    vi mx(len(c) - 1, -inf<int>);
    _for (i, n) {
        int t = UB(c, i) - 1;
        chkmin(mn[t], a[i]);
        chkmax(mx[t], a[i]);
    }
    pi ans{-inf<int>, -1};
    _for (i, len(c) - 1) {
        vi new_mn{mn};
        for (auto&& [l, r]: b)
            if (l > i || r <= i)
                _for (j, l, r)
                    new_mn[j]--;
        if (chkmax(ans.first, mx[i] - min(new_mn)))
            ans.second = i;
    }
    print(ans.first);
    vi Ans;
    _for (i, m) {
        auto&& [l, r] = b[i];
        if (l > ans.second || r <= ans.second)
            Ans.eb(i + 1);
    }
    print(len(Ans));
    print(Ans);
    return 0;
}
```

---

