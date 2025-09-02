# [ARC181D] Prefix Bubble Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc181/tasks/arc181_d

$ (1,2,\dots,N) $ の順列 $ P=(P_1,P_2,\dots,P_N) $ が与えられます。

この順列に対して以下のような操作 $ k\ (k=2,3,\dots,N) $ を考えます。

- 操作 $ k $ : $ i=1,2,\dots,k-1 $ の順に「 $ P_i\ >\ P_{i+1} $ ならば $ P $ の $ i,i+1 $ 項目の値を入れ替える」を行う。
 
長さ $ M $ の**広義単調増加**数列 $ A=(A_1,A_2\dots,A_M)\ (2\ \leq\ A_i\ \leq\ N) $ が与えられます。

各 $ i=1,2,\dots,M $ について、 $ P $ に対し操作 $ A_1,A_2,\dots,A_i $ をこの順に適用した後の $ P $ の転倒数を求めてください。

   数列の転倒数とは 長さ $ n $ の数列 $ x=(x_1,x_2,\dots,x_n) $ の転倒数とは、 整数の組 $ (i,j)\ (1\leq\ i\ であって、\ x_i\ >\ x_j $ を満たすものの個数です。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ A_i\ \leq\ N $
- $ P $ は $ (1,2,\dots,N) $ の順列
- $ i=1,2,\dots,M-1 $ に対して $ A_i\ \leq\ A_{i+1} $ が成り立つ
- 入力される値はすべて整数
 
### Sample Explanation 1

まず最初に操作 $ 4 $ が行われます。操作 $ 4 $ の過程で $ P $ は $ (3,2,4,1,6,5)\rightarrow\ (2,3,4,1,6,5)\rightarrow\ (2,3,4,1,6,5)\ \rightarrow\ (2,3,1,4,6,5) $ と変化します。操作 $ 4 $ が行われた後の $ P $ の転倒数は $ 3 $ です。 続けて操作 $ 6 $ が行われると $ P $ は最終的に $ (2,1,3,4,5,6) $ に変化し、転倒数は $ 1 $ になります。

## 样例 #1

### 输入

```
6
3 2 4 1 6 5
2
4 6```

### 输出

```
3
1```

## 样例 #2

### 输入

```
20
12 14 16 8 7 15 19 6 18 5 13 9 10 17 4 1 11 20 2 3
15
3 4 6 8 8 9 10 12 13 15 18 18 19 19 20```

### 输出

```
117
116
113
110
108
105
103
99
94
87
79
72
65
58
51```

# 题解

## 作者：yemuzhe (赞：13)

赛时花了 30 min 切了这题（做得甚至比 BC 还快）。

套用逆序对的经典结论，交换相邻的两个数 $P _ i, P _ {i + 1}$（$P _ i > P _ {i + 1}$）只会使逆序对数减少 $1$。

于是我们只需找出每一次操作发生交换的次数，用原来的逆序对数减去交换次数即可。

但是怎么找出每一次操作交换的次数呢？

手动模拟一下操作，发现一次操作会使一些数往后“跳”一段距离，另外一些数往前“滑动”一格，如下图（其中红线代表“跳”，黑线代表“滑动”）：

![](https://cdn.luogu.com.cn/upload/image_hosting/bdngoipu.png)

其实我们可以把除了“滑动”之外的都称为“跳”，例如上图中的 $3, 7, 8$。

你发现了什么？**我们交换的次数其实就等于往前“滑动”的数字个数！**

那么哪些数字会向前“滑动”呢？

对于一次操作 $A _ i$，**一个数 $P _ j$（$P _ j \le A _ i$）往前“滑动”当且仅当 $P _ j$ 不是 $P$ 序列的前缀最大值**。

也就是说，只要 $P _ j \le A _ i$ 且 $P _ j$ 前面有比它大的数，它就会往前“滑动”恰好一格。

问题解决了，接下来如何统计答案？

由于题目保证 $A _ i \le A _ {i + 1}$，所以**一个数 $P _ j$ 只会在一段连续的操作中往前“滑动”**。

我们找出最小的 $k$ 使得 $A _ k \ge P _ j$，并设 $P _ j$ 前面有 $t _ j$ 个数比 $P _ j$ 大。

这说明 $P _ j$ 会在第 $k \sim (k + t _ j - 1)$ 次操作中往前“滑动”，因为前面有 $t _ j$ 个数比它大，它就能往前“滑动” $t _ j$ 次。

于是 $P _ j$ 就对 $[k, k + t _ j - 1]$ 这段区间有 $1$ 的贡献，做个差分就能计算出答案。

```cpp
#include <cstdio>
#include <algorithm>
#define N 200005
using namespace std;

int n, m, p[N], a[N], tr[N], t[N], s[N];
long long ans;

void add (int p)
{
    for (; p; p &= p - 1) tr[p] ++;
    return ;
}

int ask (int p)
{
    int res = 0;
    for (; p <= n; p += p & -p) res += tr[p];
    return res;
}

int main ()
{
    scanf ("%d", &n);
    for (int i = 1; i <= n; i ++)
    {
        scanf ("%d", &p[i]), t[i] = ask (p[i]);
        ans += t[i], add (p[i]);
    }
    scanf ("%d", &m);
    for (int i = 1; i <= m; i ++)
    {
        scanf ("%d", &a[i]);
    }
    for (int i = 1; i <= n; i ++)
    {
        int l = lower_bound (a + 1, a + m + 1, i) - a;
        s[l] ++, s[min (l + t[i], m + 1)] --;
    }
    for (int i = 1; i <= m; i ++) s[i] += s[i - 1];
    for (int i = 1; i <= m; i ++)
    {
        ans -= s[i], printf ("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：EityDawn (赞：5)

## 思路

对题意进行转化，发现每次操作即对 $[1,A_i]$ 进行一次冒泡排序，要求统计操作后整个序列的逆序对数。

考虑进行一次冒泡排序对逆序对数产生的影响。我们定义 $pre_i$ 为 $i$ 所在位置前的比 $i$ 大的数的个数，那么逆序对数就为 $\sum_{i=1}^npre_i$ 。

我们看进行完一次前缀冒泡排序会有什么影响。

以样例为例，进行第一次操作前

|$i$|$pre_i$|
|:-:|:-:|
|1|3|
|2|1|
|3|0|
|4|0|
|5|1|
|6|0|

进行第一次操作，我们对前缀 $[1,4]$ 进行冒泡排序

|$i$|$pre_i$|
|:-:|:-:|
|1|2|
|2|0|
|3|0|
|4|0|
|5|1|
|6|0|

对于 $1,2,3,4$ 在区间 $[1,4]$ 内，它们的 $pre_i$ 的变化为 $\max(pre_i-1,0)$。

那么可以拿线段树进行动态维护 $pre_i$，但 $i$ 的位置会发生变化，怎么办？

有这样的一个性质，$A_i$ **单调不减**，每次我们对前缀操作时，这个前缀存在的数**不发生改变**，且对位置只影响比它长度更小的前缀，而我们**不可能**再对长度更小的前缀进行操作了，所以每次直接对 $[1,A_i]$ 进行区间加和区间取 $\max$ 的操作就行了。

## code
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<climits>
#include<cmath>
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf=INT_MAX;
const int N=2e5+10;
int t[N],pre[N],n,m;
int a[N],rt=1;
#define lowbit(x) (x&-x)
void add(int x)
{
	while(x<=n)
		++t[x],x+=lowbit(x);
	return;
}
int query(int x)
{
	int res=0;
	while(x)
		res+=t[x],x-=lowbit(x);
	return res;
}
struct node{
	int sum;int tag;
	int mi,se,cnt;
} tr[N<<2];
#define ls i<<1
#define rs i<<1|1
#define sum(i) tr[i].sum
#define mi(i) tr[i].mi
#define se(i) tr[i].se
#define c(i) tr[i].cnt
#define tag(i) tr[i].tag	
inline void push_up(int i)
{
	sum(i)=sum(ls)+sum(rs);
	se(i)=min(se(ls),se(rs));
	mi(i)=min(mi(ls),mi(rs));
	if(mi(ls)==mi(rs))
		c(i)=c(ls)+c(rs);
	else {
		c(i)=(mi(ls)<mi(rs))?c(ls):c(rs);
		se(i)=min(se(i),max(mi(ls),mi(rs)));
	}
	return;
}
inline void addtag(int x,int i)
{
	if(x<=mi(i)) return;
	sum(i)+=c(i)*(x-mi(i));
	mi(i)=x;return;
}
inline void addtag(int len,int v,int i)
{
	sum(i)+=len*v,mi(i)+=v,se(i)+=v,tag(i)+=v; 
}
inline void push_down(int l,int r,int i)
{
	int mid=(l+r)>>1;
	if(tag(i))
		addtag(mid-l+1,tag(i),ls),addtag(r-mid,tag(i),rs),tag(i)=0;
	addtag(mi(i),ls),addtag(mi(i),rs);
}
inline void build(int l,int r,int i)
{
	if(l==r)
	{
		sum(i)=mi(i)=pre[l];
		se(i)=inf;c(i)=1;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls);build(mid+1,r,rs);
	return push_up(i);
}
inline void Max(int p,int q,int x,int l,int r,int i)
{
	if(mi(i)>=x) return;
	if(p<=l&&q>=r&&se(i)>x) return addtag(x,i);
	push_down(l,r,i);
	int mid=(l+r)>>1;
	if(p<=mid) Max(p,q,x,l,mid,ls);
	if(q>mid) Max(p,q,x,mid+1,r,rs);
	return push_up(i);
}
inline void add(int p,int q,int l,int r,int i)
{
	if(p<=l&&q>=r) return addtag(r-l+1,-1,i);
	push_down(l,r,i);
	int mid=(l+r)>>1;
	if(p<=mid) add(p,q,l,mid,ls);
	if(q>mid) add(p,q,mid+1,r,rs);
	return push_up(i);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],add(a[i]),pre[i]=i-query(a[i]);
	build(1,n,rt);
	cin>>m;int x;
	while(m--)
	{
		cin>>x;
		add(1,x,1,n,rt),Max(1,x,0,1,n,rt);
		cout<<sum(rt)<<'\n';
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：3)

我们来刻画一下操作的本质。观察样例不难注意到操作等价于提取出前缀最大值，每一个前缀最大值移动到后一个前缀最大值的前一个位置。

我们维护每一个点向前的逆序对个数 $h_i$，从而得到操作等价于令 $\max(0,h_i-1) \to h_i$。

不难使用吉司机线段树维护。代码真的不难，就不放了。

---

## 作者：SJZ2010 (赞：2)

## 题意

给出不降的序列 $A$，每次对排列 $P$ 的前 $A_i$ 项进行**一轮**冒泡排序。问每次操作后有几个逆序对。

## 做法

首先我们要关注这个冒泡排序，经过思考可以发现：

- 逆序对数在减小，而且对于每次每个数，对于逆序对数的负贡献最大为 $1$。产生负贡献的条件是前面有比它大的数。

- 总的排序下来，每个数最多会向前移动它对逆序对的贡献次。

- 对于贡献，我们只关心逆序对里小的数就行了。

于是我们可以胡出一个做法，令数的原始贡献为 $mov_{i}$，先算出最开始的答案 $ans$。每次操作 $k$ 就是首先 $ans \gets ans - \sum_{i = 1}^k [mov_i = 0]$，原因见上。然后我们对于 $1 \le i \le n$，$mov_i \gets mov_i - 1$，因为这些数字往前移动了一位。这显然可以线段树维护。（维护最小值和最小值数量）

然而这是假的，因为可能出现负数，区间数 $0$ 就不行了。但我们注意到每个数只有一次成为 $0$ 的机会，因此当检测到 $0$ 的时候，暴力把 $0$ 改成 $+\infty$ 即可。但这样数不了 $0$ 了，因此出现 $0$ 时还得拿个树状数组记一下有几个 $0$。

简而言之，线段树维护过程，再用一个树状数组维护答案。

暴力把一个 $0$ 改成 $+\infty$ 的复杂度是 $O(\log n)$，最多暴力 $n$ 次，复杂度 $O(n \log n)$，线段树复杂度 $O(m \log n)，$复杂度显然是 $O((n + m) \log n)$。

[AC.](https://atcoder.jp/contests/arc181/submissions/56420087)

---

## 作者：ClearluvXL (赞：1)

# D - Prefix Bubble Sort
## 思路
注意到，交换相邻的两个数，首先是满足 $x_{i}>x_{i+1}$ 的。那么，这样只会使得逆序对的个数 $-1$。

那么一段区间内，进行冒泡操作，会减少多少逆序对呢？

很明显，我们减少的逆序对个数为向前移动了一个位置的数的个数。

至于那些数会向前移动一个位置嘛，对于一次操作 $a_{i}$，当且仅当一个位置 $p$， 满足 $1\leq p\leq a_{i}$ 上的数，不是 $[1,p]$ 内最大值。

关于证明：
* 如果不是区间最大值的话，那么前面一定会有最大值一直向后交换，自然就会和 $p$ 交换。
* 如果是区间内最大值的话，前面的数都比他小，那么无论 $p-1$ 是谁，都肯定不会和 $p$ 这个位置进行交换，那么 $p$ 肯定不会向前。

因为给出的 $a_{i}$ 是单调递增的，所以 $[a_{i-1}+1,a_{i}]$ 这个区间内就肯定会执行 $n-i+1$ 次操作。 

设 $i$ 前面有 $t_{i}$ 个数比 $x_{i}$ 大，并且第一个包含 $p$ 的是 $a_{j}$ 那么 $p$ 会对 $[j,\min(m,j+t_{i}-1)]$ 这些点做出贡献。用个差分即可。
## 代码
```c++
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

const int N=2e5+10;

typedef long long ll;

int n,m;
int p[N],a[N];

int tr[N];

int lowbit(int x){
	return x&(-x);
}//end

void add(int x,int c){
	for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}//end

int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=tr[i];
	return res;
}//end

int t[N],s[N];

int main(){
	
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	
	ios::sync_with_stdio(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	
	ll ans=0;
	
	for(int i=1;i<=n;i++){
		int x=p[i];
		t[i]=query(n)-query(x);
		ans+=t[i];
		add(x,1);	
	}
	
	cin>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	
	for(int i=1;i<=n;i++){
		int pos=lower_bound(a+1,a+m+1,i)-a;
		int r=min(pos+t[i]-1,m);
		if(!t[i]) continue;
		s[pos]+=1; s[r+1]-=1;
	}
	
	for(int i=1;i<=m;i++) s[i]=s[i-1]+s[i];
		
	for(int i=1;i<=m;i++){
		ans-=s[i];
		cout<<ans<<endl;
	}
		
	return 0;
}//end
```

---

## 作者：cyh_qwq (赞：1)

先将没操作前，每个位置的逆序对数，即每个位置前有多少个比它大的数求出来，BIT 即可维护。

思考一下冒泡排序的过程：每次只交换相邻两个前大后小的数，因此每个数的逆序对数至多减少 $1$。又因为是从 $1$ 位置开始进行冒泡排序，所以如果某个位置前有比它大的数，它的逆序对数一定会减 $1$ 并向前移动。然后注意到，每次操作完的逆序对数就等于操作前的逆序对数减去交换次数。

考虑如何求每次操作的交换次数，由于操作是单增的，因此一个数逆序对的减少是连续的。无脑的方法是用线段树维护区间减与区间与 $0$ 取最大值。显然这是可做的，但由于以上原因，一个数最操作的贡献也是连续的，即对操作的贡献为区间减 $1$。可以二分找到区间左端点，即对于位置 $i$ 找到第一个大于等于 $i$ 的 $A_i$，再用差分维护贡献。


```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N],n,c[N],b[N],d[N],m;
ll res;
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}
inline int lowbit(int x){
	return x&(-x);
}
inline void add(int x,int val){
	while(x<=n){
		c[x]+=val;
		x+=lowbit(x);
	}
}
inline int ask(int x){
	register int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	register int x,i;
	register ll sum=0;
	n=read();
	for(i=1;i<=n;++i){
		x=read();
		a[i]=ask(n)-ask(x);
		res+=a[i];
		add(x,1);
	}
	m=read();
	for(i=1;i<=m;++i)b[i]=read();
	for(i=1;i<=n;++i){
		if(a[i]){
			x=lower_bound(b+1,b+1+m,i)-b;
			d[x]++,d[min(x+a[i],m+1)]--;
		}
	}
	for(i=1;i<=m;++i){
		sum+=d[i];
		printf("%lld\n",res-sum);
		res-=sum;
	}
}
```

---

## 作者：快斗游鹿 (赞：1)

提供一种不依赖 $A_i$ 不降的做法。

可以发现一次操作相当于从 $p_1$ 开始，不断找到后面第一个比它大的数 $x$，把它挪到 $x$ 前面，并对 $x$ 进行上述操作。每次减少的逆序对数就是没被操作的数的个数。会被操作的数实际上就是每个前缀最大值，所以不会被操作的数的个数必然满足前面有个数比它大。

设 $h_i$ 表示在 $p_i$ 前比 $p_i$ 大的数个数，若 $h_i>0$，则这轮操作过后，前面肯定会有数被挪到它后面，而且只会有一个。

现在问题转化为，多次操作，每次选择一段前缀 $[1,x]$，$\forall i\in [1,x],h_i=\max(0,h_i-1)$，最后询问 $\sum h_i$。可以使用吉司机线段树维护。时间复杂度 $O(q\log^2n)$。

---

## 作者：luanyanjia (赞：1)

### 题目大意

一个排列，每次对一个**前缀**进行一次冒泡排序，并询问一次全局逆序对数量。

### 题目分析

设 $r_i$ 为 $p_i$ 前面比它大的数字数量，显然总逆序对数为 $\sum{r_i}$。

每对一个前缀进行一次冒泡排序，对于 $r_i = 0$ 的位置，它前面的数字都比它小，不会交换到前面，而它本身也不会和后面比它大的数字交换，因此 $r_i$ 还是为 $0$。

对于 $r_i > 0$ 的位置， 只会有前面最大的和它交换，因此 $r_i$ 减 $1$。

这样问题就转化成：一个数组，每次把一个前缀中大于 $0$ 的减 $1$，等于 $0$ 的不变，然后查询全局和。

至于顺序的问题也不用管它，因为每次操作的 $a_i$ 从小到大，且冒泡排序中前缀中的数也不会交换到后面去。

用树状数组直接维护即可。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=2e5+5;
int n,m,a[N],p[N],v[N];
namespace BIT1{
	int t[N];
	inline void Add(int x,int v){while(x<=n)t[x]+=v,x+=x&-x;}
	inline int Query(int x){int ans=0;while(x)ans+=t[x],x-=x&-x;return ans;}
}
namespace BIT2{
	int t[N<<1];
	inline void Add(int x,int v){while(x<=n+m)t[x]+=v,x+=x&-x;}
	inline int Query(int x){int ans=0;while(x)ans+=t[x],x-=x&-x;return ans;}
}
signed main(){
	rd(n);for(int i=1;i<=n;i++)rd(p[i]);
	rd(m);for(int i=1;i<=m;i++)rd(a[i]);
	int ans=0;
	for(int i=1;i<=n;i++){
		BIT1::Add(p[i],1);
		v[i]=i-BIT1::Query(p[i]);
		ans+=v[i];
	}
	int now=0,tag=0;
	for(int i=1;i<=m;i++){
		while(now<a[i]){
			++now;
			if(v[now]+tag==0)continue;
			BIT2::Add(v[now]+tag,1);
		}
		++tag;
		ans-=BIT2::Query(n+m)-BIT2::Query(tag-1);
		printf("%lld\n",ans);
	}
	return 0;
}


```

---

## 作者：QianianXY (赞：1)

## Solution
给个不用线段树，好写一点的做法。

先用树状数组求逆序对，得出数组总共的逆序对数量 $tot$。设 $a_i$ 和它**前面**的数共组成 $inv_i$ 对逆序对。

手玩样例后不难理解，操作 $i$ 的本质，其实就是对所有 $j\le i$，若 $a_j$ 非零，则 $a_j-1$。设执行操作 $i$ 前有 $m$ 个 $a_j$ 非零，则执行操作后整个序列的逆序对数量减少 $m$。

由于操作保证升序，所以每次操作都可以把新的非零 $a_j$ 放入优先队列，并将优先队列里的元素全部减一。当然，只用新建一个变量 $O(1)$ 记录减的值即可。若计算得出队头为零，则弹出。$m$ 即为优先队列的规模。$tot-m$ 为当前答案。

每个 $a_i$ 最多入队出队各一次，时间复杂度为 $O(n\log n)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll N = 1e6 + 10;

ll n, a[N], q, sum[N], tr[N], ans, flg;
priority_queue<ll, vector<ll>, greater<ll> > que;

ll lowbit(ll x) {return x & -x;}

void add(ll x, ll c)
{
	for (; x <= n; x += lowbit(x))
		tr[x] += c;
}

ll query(ll x)
{
	ll res = 0;
	for (; x > 0; x -= lowbit(x))
		res += tr[x];
	return res; 
}

int main()
{
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	scanf("%lld", &q);
	ll p = 1;
	for (ll i = 1; i <= n; i++) {
		sum[i] = i - query(a[i]) - 1;
		ans += sum[i];
		add(a[i], 1);
	}
	while (q--) {
		++flg;
		ll x;
		scanf("%lld", &x);
		while (p <= x) {
			if (sum[p] + flg - 1 > 0 && sum[p])
				que.push(sum[p] + flg - 1);
			++p;
		}
		ans -= que.size();
		while (que.size() && que.top() <= flg)
			que.pop();
		
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Yanami_Anna (赞：0)

考虑冒泡排序的过程，首先是第一个数，往后找到第一个比他要大的数，然后到那个位置上再用那个比他大的数去找。

这个东西就是前缀最大值，假设操作了前 $x$ 个数，里面有 $y$ 个前缀最大值，则有 $x-y$ 个逆序对被减掉了。

显然一个点一旦成为前缀最大值就不可能再不成为前缀最大值，所以我们考虑维护一个点成为可用前缀最大值的时间（我们认为目前没操作到的前缀最大值不可用）

容易发现一个点前面比他大的数，每做一次冒泡排序，这些数中有且仅有一个一定会到他的后面去，这样直到他前面没有比他大的数，他就是前缀最大值了，我们可以维护每个点什么时候第一次被操作，那么什么时候被操作成前缀最大值就是可以计算的，我们把这个东西差分一下再前缀和回去就行了。

那么现在有了前缀最大值个数，维护逆序对的变化量就是容易的了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int A[200005];
int B[200005];
int num[200005];
int ed[200005];
int diff[200005];
int ans;
class BIT{
    public:
    int c[200005];
    int lowbit(int x){return x&-x;}
    void add(int x,int y){
        while(x<=n){
            c[x]+=y;
            x+=lowbit(x);
        }
        return;
    }
    int ask(int x){
        int sum=0;
        while(x){
            sum+=c[x];
            x-=lowbit(x);
        }
        return sum;
    }
}P;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&A[i]);
        num[i]=i-1-P.ask(A[i]);
        P.add(A[i],1);
        ans+=num[i];
    }
    scanf("%lld",&m);
    for(int i=1;i<=m;i++){
        scanf("%lld",&B[i]);
        for(int j=B[i-1]+1;j<=B[i];j++){
            ed[j]=i+num[j]-1;//ed[j]表示第j个点会在第ed[j]次操作之后成为可用前缀最大值
            diff[ed[j]+1]++;
        }
    }
    for(int i=1;i<=m;i++){
        diff[i]+=diff[i-1];
    }
    //diff[i]表示第i次操作之前的前缀最大值数量
    for(int i=1;i<=m;i++){
        ans-=(B[i]-diff[i]);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

