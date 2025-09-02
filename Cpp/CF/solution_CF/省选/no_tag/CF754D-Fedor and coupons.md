# Fedor and coupons

## 题目描述

All our characters have hobbies. The same is true for Fedor. He enjoys shopping in the neighboring supermarket.

The goods in the supermarket have unique integer ids. Also, for every integer there is a product with id equal to this integer. Fedor has $ n $ discount coupons, the $ i $ -th of them can be used with products with ids ranging from $ l_{i} $ to $ r_{i} $ , inclusive. Today Fedor wants to take exactly $ k $ coupons with him.

Fedor wants to choose the $ k $ coupons in such a way that the number of such products $ x $ that all coupons can be used with this product $ x $ is as large as possible (for better understanding, see examples). Fedor wants to save his time as well, so he asks you to choose coupons for him. Help Fedor!

## 说明/提示

In the first example if we take the first two coupons then all the products with ids in range $ [40,70] $ can be bought with both coupons. There are $ 31 $ products in total.

In the second example, no product can be bought with two coupons, that is why the answer is $ 0 $ . Fedor can choose any two coupons in this example.

## 样例 #1

### 输入

```
4 2
1 100
40 70
120 130
125 180
```

### 输出

```
31
1 2 
```

## 样例 #2

### 输入

```
3 2
1 12
15 20
25 30
```

### 输出

```
0
1 2 
```

## 样例 #3

### 输入

```
5 2
1 10
5 15
14 50
30 70
99 100
```

### 输出

```
21
3 4 
```

# 题解

## 作者：Jorisy (赞：3)

有一定思维的贪心。

对于所有区间，我们可以按左端点升序。

然后用小根堆维护右端点。

因为要恰好为 $k$，所以当堆里元素个数超过 $k$ 时，就弹出。

记 $ans$ 为最大区间交集，$l$ 表示该交集的左端点（求右端点直接 $l+ans-1$ 即可）。每次当堆中元素个数等于 $k$ 时，便处理 $ans$ 和 $l$。

对于最后选方案，只要 $O(n)$ 遍历一下，在区间内的就输出即可（注意特判 $ans=0$ 和满足的区间数 $>k$ 的）。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int l,r,id;
	bool operator<(const node &x)const
	{
	    return l<x.l;
	}
}a[1000005];
priority_queue<int,vector<int>,greater<int>>q;

int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);//排序
	int l=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		q.push(a[i].r);
		if(q.size()>k) q.pop();//弹出
		if(q.size()==k&&ans<q.top()-a[i].l+1)
		{
			ans=q.top()-a[i].l+1;
			l=a[i].l;//更新
		}
	}
	if(!ans)//ans=0 的特判
	{
		puts("0");
		for(int i=1;i<=k;i++)
		{
			cout<<a[i].id<<' ';
		}
		return 0;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n&&k>0/*满足区间超过 k 的特判*/;i++)
	{
		int x=a[i].l,y=a[i].r;
		if(x<=l&&l+ans-1<=y)//在最大的区间内
		{
			cout<<a[i].id<<' ';//注意输出原序号
			k--;//区间数减一
		}
	}
	return 0;
}
```

---

## 作者：丧黑福造 (赞：2)

# 标签：贪心$+$优先队列

思路：

我们可以确定，如果$k$个区间有一个公共部分，那么这个公共部分区间的左端点一定是这个k个区间里最靠右的，右端点一定是这$k$个区间里面最靠左的。如果当前得到的右端点$<$左端点，说明区间不存在。

我们可以先把区间按照左端点排序，保证后访问的左端点一定比之前访问的都要靠右，然后优先队列按照右端点小的先出，这样保证每次队列首部的右端点是最靠左的，既然题目要求k个区间，就要一直保证区间大小为$k$，如果不满足就$pop$，直到满足为止。

这样每次得到的答案$len$ $= $队首的右端点 $-$ 当前遍历到的左端点，用来更新答案，至于选择$k$个区间，只要遍历一遍所有区间，选择左端点 $\le$ 公共左端点，右端点 $\ge$ 公共右端点即可。


代码和@MILLOPE写得差不多，就不放了

---

## 作者：CQ_Bab (赞：1)

# 前言
这题能有紫？
# 思路
感觉比较一眼，首先我们可以证明如果能凑出长度为 $l$ 的公共区间那么一定是一段 $x\sim x+l-1$ 的公共区间并且一定是以某个区间的左端点为开头的，所以我们考虑二分答案 $x$ 然后我们可以枚举区间的左端点为 $l$ 然后能算出 $r$ 取到的位置因为我们的 $l$ 可以从小到大枚举所以可以直接双指针最后另一边就是一个一维偏序直接上树状数组即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,k;
const int N=6e5+10;
int tr[N];
int l[N],r[N],vis[N],mm;
int lowbit(int x) {
	return x&-x;
} 
void add(int x,int k) {
	for(;x<=mm;x+=lowbit(x)) tr[x]+=k;
}
int Ans(int x) {
	int res=0;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
int arr[N],tot;
struct node{
	int l,r,id;
	friend bool operator<(const node&a,const node&b) {
		return a.l<b.l;
	}
}s[N];
bool check(int x) {
	int l=1,res=0,id=0,kk=0;
	rep(i,1,mm) tr[i]=0;
	rep(i,1,mm) {
		while(s[l].l<=i&&l<=n) {
			add(s[l].r,1);
			l++;
		}
		int kk1=lower_bound(arr+1,arr+1+mm,arr[i]+x-1)-arr-1;
		int now=l-1-Ans(kk1);
		if(now>=k) return 1;
	}return 0;
}
void solve() {
	in(n),in(k);
	rep(i,1,n) {
		in(l[i]),in(r[i]);
		arr[++tot]=l[i];
		arr[++tot]=r[i];
	}
	sort(arr+1,arr+1+tot);
	mm=unique(arr+1,arr+1+tot)-arr-1;
	arr[++mm]=1e18;
	rep(i,1,n) l[i]=lower_bound(arr+1,arr+1+mm,l[i])-arr,r[i]=lower_bound(arr+1,arr+1+mm,r[i])-arr;
	rep(i,1,n) s[i]={l[i],r[i],i};
	sort(s+1,s+1+n);
	int l=1,r=2000000001,res=0;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	cout<<res<<endl;
	if(res==0) {
		rep(i,1,k) cout<<i<<' ';
		return;
	}
	l=1;
	rep(i,1,mm) tr[i]=0;
	rep(i,1,mm) {
		while(s[l].l<=i&&l<=n) {
			add(s[l].r,1);
			l++;
		}
		int kk1=lower_bound(arr+1,arr+1+mm,arr[i]+res-1)-arr-1;
		int now=l-1-Ans(kk1);
		if(now>=k) {
			rep(kk2,1,l-1) {
				if(s[kk2].r>kk1) {
					cout<<s[kk2].id<<' ';
					k--;
					if(!k) return;
				}
			}
		}
	}
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：MILLOPE (赞：1)

## 题目
我们所有的角色都有某些习惯。Fedor 也一样。他在邻近的超市享受购物。

超市的不同货物有不同的整数 ID。对于每个整数也有一个产品的 ID 和这个整数相同。Fedor 有 $n$ 张折扣券，它们中的第 $i$ 张可以用于 ID 范围介于 $[l_i, r_i]$ 的产品。今天 Fedor 想要携带恰好 $k$ 张折扣券。

Fedor 想要选择 $k$ 张折扣券，使得所有的折扣券都可以用于尽可能多的产品数目 $x$ (为了最好的理解，参见样例)。Fedor 同时也想节省时间，所以他请求你为他选择折扣券。请帮帮 Fedor！

简要题意: 从$n$个区间中选出恰好$k$个, 最大化公共部分的长度.

[CF754D Fedor and coupons](https://www.luogu.org/problemnew/show/CF754D)
## 题解
- 将左端点从小到大排序，然后用小根堆堆维护右端点（堆的大小为k）
- 为什么要用小根堆呢：因为我们要让区间长度尽可能的长，所以我们要每次弹出最小值qwq

## $code$
```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 300000 + 100; 

template <class T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, k; 
struct node { 
	int l, r, id; 
	bool operator <(const node &A) const {
		return l < A.l; 
	}
}; 
node s[maxn]; 
priority_queue<int> p; 

int main() {
	read(n), read(k); 
	for (int i = 1; i <= n; ++i) {
		read(s[i].l), read(s[i].r); 
		s[i].id = i; 
	}

	sort(s + 1, s + n + 1); 

	int len = 0, L = 0, R = 0; 
	for (int i = 1; i <= n; ++i) {
		p.push(-s[i].r); 
		if (p.size() > k) p.pop(); 
		if (p.size() == k) {
			int now = (-p.top()) - s[i].l + 1; 
			if (now > len) {
				len = now; 
				L = s[i].l; 
				R = (-p.top()); 
			}
		}
	}

	printf("%d\n", len); 
	if (!len) {
		for (int i = 1; i <= k; ++i) 
			printf("%d ", i); 
	} 
	else {
		// printf("L = %d R = %d\n", L, R); 
		for (int i = 1, j = 1; i <= n && j <= k; ++i) {
			if (s[i].l <= L && s[i].r >= R) {
				printf("%d ", s[i].id), ++j; 
			}
		}
	}
	return 0; 
}

```

---

## 作者：xrk2006 (赞：0)

# 【题解】CF754D Fedor and coupons

## 题目链接

[CF754D Fedor and coupons](https://www.luogu.com.cn/problem/CF754D)

[CF1029C Maximal Intersection](https://www.luogu.com.cn/problem/CF1029C)

后者是前者的加强版。

## 思路分析

最开始，先考虑不删区间 $(k=0)$ 的情况：

也就是给你一大堆区间，让你找他们的交集。

这个还是比较好想的，我们刚开始让第二个区间与第一个区间相交，得到的是一个以 $\max(l_1,l_2)$ 为左端点，以 $\min(r_1,r_2)$ 为右端点的区间，然后再让这个区间与后面的区间相交，每次得到的交集都是以两者 $l$ 取 $\max$，$r$ 取 $\min$ 的区间。

所以我们找位于**最右边**的 $l$，位于**最左边**的 $r$，得到的交集为 $[\max_l,\min_r]$ 那么 $r-l+1$ 即为答案。

如果 $l>r$，那么答案为 $0$。

---

再考虑 $k=1$ 的情况（即 CF1029C）：

也就是删去一个区间，然后使得剩下的区间交集最大。

比较好想的就是直接枚举删去了哪个区间，然后考虑剩下区间的交集。

剩下区间的交集我们每次可以用 $k=0$ 的思路做，但是时间复杂度过高。

我们考虑删掉一个区间与没有删去区间时的原答案有什么变化：

假设原答案的交集区间的左端点是 $L$，右端点是 $R$。

那么如果删掉的这个区间左端点 $l=L$，且所有区间中只有这一个 $l=L$ 的区间，那么删掉这个区间后，新的答案交集左端点就变成了所有区间中第二大的左端点 $ml$。

同理，如果删掉的这个区间右端点 $r=R$，且所有区间中只有这一个 $r=R$ 的区间，那么删掉这个区间后，新的答案交集右端点就变成了所有区间中第二小的右端点 $mr$。

综上所述，我们可以遍历所有的区间，然后处理出所有区间中左端点最大和次大，右端点最小和次小，然后依次考虑删去每个区间后对答案的影响，所有情况下的答案取最大值即可。

具体见下方代码。（这是 $k=1$ 情况下的**第一种思路**）

---

最后考虑 $k>1$ 的情况（即 CF754D）：

也就是删去 $k$ 个区间，然后使得剩下的区间交集最大。

根据上述两种情况，我们很自然想到：删去了 $k$ 个区间，要使得最后剩下的区间交集最大，那么答案区间左端点就是剩下区间左端点最大值 $\max_l$，右端点就是剩下区间右端点最小值 $\min_r$。

$k=1$ 的时候我们是处理了所有区间的最大和次大，那么这个 $k>1$ 怎么办呢，那按照 $k=1$ 的思路，我们应该处理前 $k+1$ 大。

前 $k$ 大问题可以让人联想到优先队列。但是怎么用呢？

如果按照 $k=1$ 的思路继续走下去，我们自然是开一个大根堆，一个小根堆，一个维护 $l$ 的前 $k+1$ 大，一个维护 $r$ 的前 $k+1$ 小。接下来枚举删掉的 $k$ 个区间……这时候就存在问题了，之前因为 $k=1$，所以枚举区间是 $O(n)$ 的复杂度，可以接受。现在 $k$ 本身就是 $3\times 10^5$ 这个级别的，直接枚举复杂度显然接受不了，说明直接照搬 $k=1$ 的思路是不可行的。

考虑怎么改进做法。

正难则反，删去 $k$ 个区间，实际上就相当于保留 $m=n-k$ 个区间。

实际上就是找到 $m$ 个区间，使得这 $m$ 个区间 $\min_r-\max_l$ 最小。

那么我们可以将 $l$ 排序，用小根堆来维护 $r$ 的前 $m$ 小。

在排序后的序列中，从 $1$ 到 $n$ 枚举每个区间，并将其右端点丢进小根堆。如果当前堆中元素 $>m$ 就将堆顶元素弹出堆。如果当前堆中元素 $=m$ 就判断当前 $\min_r-\max_l$ 与当前答案 $ans$ 的关系，并更新 $ans$。

那么这个题就做完了。

**注：原题中的 $n$ 实际上相当于这里的 $m$，为了方便照应 $k=0$ 和 $k=1$，我就直接把这种情况当做 $k>1$ 的来处理了。**

---

根据上面的分析过程来看，$k=1$ 的思路几乎与 $k=0$ 一致，只是稍作改变，区别是 $k=1$ 的思路增加了处理最大和次大。同时这个最大和次大又为 $k>1$ 的思路中用优先队列处理前 $m$ 小的 $r$ 提供了启发。

除此之外，$k=1$ 的思路除了我上面提到的这种做法之外，还有另外一种大同小异的处理方法：

枚举删哪个区间，假设我们枚举的区间是 $i$，那么答案区间的左端点就是前 $i-1$ 个区间 $\max_l$ 与第 $i+1$ 到第 $n$ 个区间的 $\max_l$ 取最大值，同理，右端点是前 $i-1$ 个区间 $\min_r$ 与第 $i+1$ 到第 $n$ 个区间的 $\min_r$ 取最小值。

基于此， 我们可以考虑维护前缀/后缀 $\max_l$ 和 $\min_r$，然后枚举删哪个区间，考虑贡献即可。（这是 $k=1$ 情况下**第二种思路**）

同时，由于 $k=1$ 实际上就是 $k>1$ 的特殊情况，依然可以沿用 $k>1$ 的思路，此时就相当于 $m=n-1$。（$k=1$ 情况下**第三种思路**）

## 代码实现

$k=1$ 第一种思路：

```cpp
//CF1029C
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=3e5+10;
const int INF=1e9;
int l[maxn],r[maxn],ml,mr,mml,mmr;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	int n=read();
	ml=0;mr=INF;
	mml=0;mmr=INF;
	for(int i=1;i<=n;i++)
	{
		l[i]=read(),r[i]=read();
		if(l[i]>=ml)
		{
			mml=ml;
			ml=l[i];
		}
		else if(l[i]>mml)mml=l[i];
		if(r[i]<=mr)
		{
			mmr=mr;
			mr=r[i];
		}
		else if(r[i]<mmr)mmr=r[i];
	}
	int L,R,ans=0;
	for(int i=1;i<=n;i++)
	{
		if(l[i]==ml)L=mml;
		else L=ml;
		if(r[i]==mr)R=mmr;
		else R=mr;
		ans=max(ans,R-L);
	}
	cout<<ans<<'\n';
	return 0;
}
```

$k>1$：

```cpp
//CF754D
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<set>
#define mk make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=3e5+10;
int ans;

struct Node{int l,r,id;}a[maxn];

priority_queue<pii>q;

set<int>s;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int cmp(Node a,Node b){return a.l<b.l;}

int main()
{
	int n,k;
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i].l=read(),a[i].r=read(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		q.push(mk(-a[i].r,i));
		if(q.size()>k)q.pop();
		if(q.size()==k&&-q.top().first-a[i].l+1>ans)ans=-q.top().first-a[i].l+1;
	}
	if(ans==0)
	{
		cout<<ans<<'\n';
		for(int i=1;i<=k;i++)cout<<i<<" ";
		exit(0);
	}
	while(!q.empty())q.pop();
	for(int i=1;i<=n;i++)
	{
		q.push(mk(-a[i].r,i));
		s.insert(a[i].id);
		if(q.size()>k)s.erase(s.find(a[q.top().second].id)),q.pop();
		if(q.size()==k&&-q.top().first-a[i].l+1==ans)
		{
			cout<<ans<<'\n';
			for(int v:s)cout<<v<<" ";
			exit(0);
		}
	}
}
```

$k=1$ 第二种思路：

```cpp
//CF1029C
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=3e5+10;
int l[maxn],r[maxn],prel[maxn],prer[maxn],sufl[maxn],sufr[maxn];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	int n=read();
	prer[0]=sufr[n+1]=1e9;
	for(int i=1;i<=n;i++)
	{
		l[i]=read();
		r[i]=read();
		prel[i]=max(prel[i-1],l[i]);
		prer[i]=min(prer[i-1],r[i]);
	}
	for(int i=n;i>=1;i--)
	{
		sufl[i]=max(sufl[i+1],l[i]);
		sufr[i]=min(sufr[i+1],r[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int L=max(prel[i-1],sufl[i+1]);
		int R=min(prer[i-1],sufr[i+1]);
		ans=max(R-L,ans);
	}
	cout<<ans<<'\n';
	return 0;
}
```

$k=1$ 第三种思路：

```cpp
//CF754D
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<set>
#define mk make_pair
#define pii pair<int,int>
using namespace std;
const int maxn=3e5+10;
int ans;

struct Node{int l,r,id;}a[maxn];

priority_queue<pii>q;

set<int>s;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int cmp(Node a,Node b){return a.l<b.l;}

int main()
{
	int n,k;
	n=read();k=n-1;
	for(int i=1;i<=n;i++)a[i].l=read(),a[i].r=read(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		q.push(mk(-a[i].r,i));
		if(q.size()>k)q.pop();
		if(q.size()==k&&-q.top().first-a[i].l>ans)ans=-q.top().first-a[i].l;
//		cout<<-q.top().first<<" "<<q.top().second<<'\n';
	}
	if(ans==0)
	{
		cout<<ans<<'\n';
//		for(int i=1;i<=k;i++)cout<<i<<" ";
		exit(0);
	}
	while(!q.empty())q.pop();
	cout<<ans<<'\n';
//	for(int i=1;i<=n;i++)
//	{
//		q.push(mk(-a[i].r,i));
//		s.insert(a[i].id);
//		if(q.size()>k)s.erase(s.find(a[q.top().second].id)),q.pop();
//		if(q.size()==k&&-q.top().first-a[i].l==ans)
//		{
//			cout<<ans<<'\n';
//			for(int v:s)cout<<v<<" ";
//			exit(0);
//		}
//	}
}

```



---

## 作者：出言不逊王子 (赞：0)

看到全局交集最大，我们一步步来。

首先，如果全部保留怎么做？

全局交集也是个区间，区间的左端点是最右的左端点。同理可得区间的右端点是最左的右端点。

所以将所有区间扫一遍，找出 $\max\ l_i$ 和 $\min\ r_i$ 即可，答案就是 $\min\ r_i-\max\ l_i+1$。

这启发我们要寻找这两个变量。根据扫描线的思路，如果我们按照 $l_i$ 从小到大扫描，则可以固定一维。

在第一维固定后，我们希望 $\min\ r_i$ 最大。为了快速知道当前的 $\min r_i$ 是啥，我们考虑用 `priority_queue` 维护。

我们每次加入一个点时，保证当前的优先队列中有 $k$ 个 $r_i$。然后我们从这里面选出一个作为 $r_i$ 即可。

可是如果优先队列里的 $r_i$ 的个数超过了 $k$ 个咋办？那就踢一个走呗。

踢哪个呢？因为我们希望最小的 $r_i$ 最大，所以我们踢掉最小的 $r_i$。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=400001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
priority_queue<int,vector<int>,greater<int> > q; 
struct node{int l,r,id;}a[N];
bool cmp(node l,node r){return l.l<r.l;}
int n,k,res,lef,rig;
signed main(){
	n=read(),k=read();
	fs(i,1,n,1) a[i].l=read(),a[i].r=read(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	fs(i,1,n,1){
		q.push(a[i].r);
		if(q.size()>k) q.pop();
		if(q.size()==k){
			int cur=q.top()-a[i].l+1;
			if(cur>res) res=cur,lef=a[i].l,rig=q.top();
		}
	} 
	printf("%lld\n",res);if(!res){
		fs(i,1,k,1) printf("%lld ",i);
		return 0; 
	}
	int id=0;
	fs(i,1,n,1){
		if(a[i].l<=lef&&a[i].r>=rig) printf("%lld ",a[i].id),id++;
		if(id==k) return 0;
	}
	return 0;
}
//删除不好做，转成保留
//我们需要找到k个区间，满足(minR-maxL)最大 
//那么我们先按照L排序
//然后从左往右加入L，往优先队列里塞R
//很显然我们要的是当前最小的R
//所以一旦大于了k个，我们就优先删掉那个最小的R
```

---

