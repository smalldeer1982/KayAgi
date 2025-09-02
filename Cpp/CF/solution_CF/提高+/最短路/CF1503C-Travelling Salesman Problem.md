# Travelling Salesman Problem

## 题目描述

There are $ n $ cities numbered from $ 1 $ to $ n $ , and city $ i $ has beauty $ a_i $ .

A salesman wants to start at city $ 1 $ , visit every city exactly once, and return to city $ 1 $ .

For all $ i\ne j $ , a flight from city $ i $ to city $ j $ costs $ \max(c_i,a_j-a_i) $ dollars, where $ c_i $ is the price floor enforced by city $ i $ . Note that there is no absolute value. Find the minimum total cost for the salesman to complete his trip.

## 说明/提示

In the first test case, we can travel in order $ 1\to 3\to 2\to 1 $ .

- The flight $ 1\to 3 $ costs $ \max(c_1,a_3-a_1)=\max(9,4-1)=9 $ .
- The flight $ 3\to 2 $ costs $ \max(c_3, a_2-a_3)=\max(1,2-4)=1 $ .
- The flight $ 2\to 1 $ costs $ \max(c_2,a_1-a_2)=\max(1,1-2)=1 $ .

The total cost is $ 11 $ , and we cannot do better.

## 样例 #1

### 输入

```
3
1 9
2 1
4 1```

### 输出

```
11```

## 样例 #2

### 输入

```
6
4 2
8 4
3 0
2 3
7 1
0 1```

### 输出

```
13```

# 题解

## 作者：7KByte (赞：15)

对于每个城市 $i$，我们把 $a_i$ 看作他的海拔。

那么我们就可以对城市进行势能分析，向下走不需要花费代价，而向上走需要花费的总代价只与起点和终点有关。

再考虑 $c_i$，首先$c_i$是必须要加入答案的。

除了$c_i$，还需要考虑额外代价，表示扩大 $c_i$ 。每个城市可以到达海拔最大为 $a_i+c_i$ 的城市。我们对所有城市按海拔排序，如果存在一个 $i$ 使得前 $i$ 个数的 $a_i+c_i$ 的最大值小于$a_{i+1}$，就需要花费额外代价扩大 $c_i$，使得能够达到 $a_{i+1}$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n;long long ans;
struct node{
	int a,c;
	bool operator<(const node o)const{return a<o.a;}
}a[N];
multiset<node>p;
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&a[i].a,&a[i].c),ans+=a[i].c;
	sort(a+1,a+n+1);
	int cur=0;
	rep(i,1,n){
		cur=max(cur,a[i].a+a[i].c);
		if(cur<a[i+1].a)ans+=a[i+1].a-cur;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：9)

[传送门](https://codeforces.ml/contest/1503/problem/C)

这场水D+E，可惜还是不会做E，结果人均四题，再次掉大分。

观察这个式子：$\max\{c_i,a_j-a_i\}$.

发现 $ans>=\sum c_i$. 不妨加上去，然后最小化额外贡献。即 $\max\{0,a_j-a_i-c_i\}$.

首先发现起点并不重要，任选 $start$ 然后访问所有城市后回到 $start$ 都是合法的。又因为现在要搞的是 $a$. 这启发我们对 $a$ 排序。

以下的位置均指排序后的位置。

假设我们走到了 $i$. 注意到从 $i$ 到所有 $j<=i$ 的城市都没有额外贡献。然后如果从一个城市 $j$ 往后走，它可以**无额外贡献**地走到 $k<=a_j+c_j$ 的点。那么我们在 $[1,i] $ 中寻找一个这样的最大的城市 $j$. 然后重新拓展右端点。直到无法拓展为止。此时我们必须要有额外贡献了。令边界为 $l$，则为了走到 $l+1$，我们需要花费 $a_{l+1}-\max\{a_j+c_j\mid j<=l\}\}$. 

可以发现拓展的正确性：假设我们实际上要走到 $l+2$，那么从 $l+1$ 拓展到 $l+2$ 的代价应该不必直接拓展（指从 $<=l$ 的 $j$ 拓展）差。此处拓展的正确性同时保证了官方题解 $2$ 的正确性。

于是我们在 $O(n\log n)$ 的时间内解决了这个 TSP 问题（事实上它真的是个TSP）

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
pi a[MAXN];
ll n,ans,idx,pre[MAXN]; 
int LowerBound(int val){
	//最后一个小于等于val的 
	int L=1,R=n,ans=n;
	while(L<=R){
		int mid=(L+R)>>1;
		if(a[mid].fr<=val){
			ans=mid;
			L=mid+1;
		}else{
			R=mid-1;
		}
	}
	return ans;
}
int main(){
	cin>>n;
	rep(i,1,n){
		cin>>a[i].fr>>a[i].se;ans+=a[i].se;
	} 
	sort(a+1,a+1+n);
	rep(i,1,n){
		pre[i]=Max(pre[i-1],a[i].fr+a[i].se);
	}
	idx=1;
	while(idx<n){
		int pos=LowerBound(pre[idx]);
		if(pos==n)break;
		//拓展到pos+1
		ans+=Max(0,a[pos+1].fr-pre[pos]); 
		idx=pos+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Warriors_Cat (赞：7)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1503C) & [CF 题面传送门](http://codeforces.com/problemset/problem/1503/C)。

题意：

* 给 $n$ 个城市，分别有权值 $a_i, c_i$。
* 从城市 $i$ 走到城市 $j$ 的代价为 $\max\{c_i, a_j - a_i\}$。
* 从城市 $1$ 出发，问至少要花费多少代价才能走遍所有城市。
* $n \le 10^5$，$a_i, c_i \le 10^9$。

~~怎么这场 CF 思维题这么多啊，ilil（~~

---

### Solution：

注意到 $\max\{c_i, a_j - a_i\}=c_i + \max\{0, a_j - a_i - c_i\}$，因此答案一定不小于 $\sum\limits_{i=1}^nc_i$，于是可以先把这一部分答案加上，然后再考虑 $\max\{0, a_j - a_i - c_i\}$ 的部分。

又注意到当 $a_j < a_i$ 时 $\max\{0, a_j - a_i - c_i\}$ 对答案是没有任何影响的，所以我们需要看的只是所有 $a_j > a_i$ 的部分，所以我们可以直接对每个城市关于 $a$ 的值排序。

记下面所有 $a, c$ 值均为排序后的值。

我们考虑每一个 $a_i$，发现它最多能拓展到的无贡献的值就是 $a_i + c_i$。因此我们可以从 $a_1$ 出发，一直找 $a$ 序列中 $a_i + c_i$ 的后继，然后把贡献都加上即可。时间复杂度为 $O(n\log n)$。

当然我们也不必要这么做，我们直接存储枚举时当前的 $a_i + c_i$ 的最大值，然后与 $a_{i+1}$ 比较即可，简单来说，答案就是下面这个东西：

$$\sum_{i=2}^n\max\{0, a_i - \max_{j=1}^{i-1}\{a_j + c_j\}\}$$

时间复杂度为 $O(n)$。

---

### Code：

注意答案要用 `long long` 存储。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 100010;
struct node{
	int x, y, idx;
	bool operator < (const node&rhs)const{
		return x < rhs.x;
	}
}a[N];
int n, maxx; ll ans;
inline void mian(){
	n = read();
	rep(i, 1, n) a[i].x = read(), a[i].y = read(), ans += a[i].y, a[i].idx = i;
	sort(a + 1, a + n + 1);
	rep(i, 1, n - 1){
		maxx = max(maxx, a[i].x + a[i].y);
		ans += max(0, a[i + 1].x - maxx);
	}
	printf("%lld\n", ans);
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```


---

## 作者：Mihari (赞：3)

# 壹、题目描述 &para;

[传送门 to CF](https://codeforces.com/contest/1503/problem/C)

# 贰、题解 &para;

真的一个脑瘫题，我还往线段树优化建图想......

首先注意到，其实从哪个点出发都一样，因为我们最后反正要走一个哈密顿回路出来。

我们得将 $\max\{c_i,a_j-a_i\}$ 改写一下，有
$$
\max\{c_i,a_j-a_i\}=c_i+\max\{0,a_j-a_i-c_i\}
$$
由于我们每个点都要经过一次，所以我们可以先忽略 $c_i$，最后将答案加上 $\sum c_i$ 即可。

现在我们想要最小化 $\max\{0,a_j-a_i-c_i\}$.

首先可以将原序列按照 $a_i$ 升序排列，然后我们就有了两种解法。

## &sect; 建图最短路 &sect;

一定有 $j\rightarrow i(j>i)$ 的花费为 $0$，所以我们就有了第一种边：连接所有 $i+1\rightarrow i$，权值为 $0$.

不仅仅这种边是免费的，还有 $a_j-a_i-c_i\le 0$ 的边。

本来我们需要连接所有这样的、满足条件的点对，但是由于第一种边的存在，我们只需要连接最大的 $a_j$ 的点，就可以覆盖所有的点了，而这个最大的 $j$ 怎么找呢？二分查找是个好办法！

但是我们还要走付费边啊，我们找到了 $j$，那么从 $i\rightarrow j+1$ 的就得是付费边了吧，我们将这样付费相邻的点串起来，就达到了类似第一种边的效果。这是第三种边。

把这三种边全部连起来，直接上 $\tt dijkstra$ 就行了。

## &sect; 左右端点想法 &sect;

将 $a_i$ 排序之后，答案就是：
$$
\sum_{i=2}^n\max\{0,a_i-\max_{j<i}\{a_j+c_j\}\}
$$
这很简单吧？但是为什么是这样的啊？对于 $i$，我们将其看作 $\lang l_i,r_i\rang=[a_i,a_i+c_i]$ 的区间，那么问题就抽象为：从区间 $i$ 走到 $j$，你需要花费的是 $\max\{0,l_j-r_i\}$，也就是后一个区间的左端点和前一个区间的右端点的差值，或者 $0$，问经过所有区间的最小花费，将区间按照左端点排序之后，最优的就是从最大的右端点开始走，走到下一个区间，而从最后一个区间走回 $1$ 呢？显然有 $r_n\ge l_1$，那里的花费就是 $0$，所以我们只需要计算上面的式子就行了......时间复杂度 $\mathcal O(n\log n)$.

# 叁、参考代码 &para;

没写第一种，写的第二种 ~~因为它很短~~

```cpp
#define Endl putchar('\n')
#define mp(a, b) make_pair(a, b)
#define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
#define fep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
template<class T>inline T fab(T x){ return x<0? -x: x; }
template<class T>inline T readin(T x){
	x=0; int f=0; char c;
	while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
	for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
	return f? -x: x;
}

const int maxn=1e5;

struct node{
	int a, c;
	node(){}
	node(int A, int C): a(A), c(C){}
	inline int operator <(const node rhs) const{
		return a<rhs.a;
	}
}p[maxn+5];

int n;

inline void input(){
	n=readin(1);
	int a, c;
	rep(i, 1, n){
		a=readin(1), c=readin(1);
		p[i]=node(a, c);
	}
	sort(p+1, p+n+1);
}

signed main(){
	input();
	int maxx=p[1].a+p[1].c; ll ans=p[1].c;
	rep(i, 2, n){
		ans=ans+max(0, p[i].a-maxx);
		maxx=max(maxx, p[i].a+p[i].c);
		ans+=p[i].c;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：qzmoot (赞：2)

# 题目大意
让我们贪心地求从一个城市走遍所有的城市后再回到出发点的最小代价。
# 题目思路
遇到这种代价题目，我们直接 ```sort``` 进行快速排序，按照 $a_i$ 为关键字。

接下来，我们仔细观察一下这个式子：$\max(c_i,a_j-a_i)$。我们是不是可以把这个式子改编成：$c_i+\max(0,a_j-a_i-c_i)$。于是我们就发现这个 $c_i$ 是每次必须要加的，所以我们直接在输出时就可以先统计了。

接着，我们就要关注 $\max(0,a_j-a_i-c_i)$ 这个式子，来求出我们的贪心策略。因为我们已经排好序的缘故，我们从最后一个点往前走的时候，可以把没有经过的点给经过，并代价为 $0$。所以我们就直接考虑从最开始的点到最后点的方案。

我们可以把这个问题给抽象一下，在一个数轴上，$a_i$ 是横坐标，$c_i$ 是延伸的距离，如果有点在我们当前这个距离里面，我们就选择这些点当中 $a_j+c_j$ 最大的点，这样我们后面的代价会尽量的小。但是如果没有怎么办呢？我们就直接往右走就行了，这样我们移动的代价是最小的，因为我们已经排完序了。

于是我们就推导完成了，接下来就是万人喜的代码环节了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,las;
long long sum;
struct node{
	int a,c;
}x[N];
int read()
{
	int x=0;
	char ch=getchar();
	while(!isdigit(ch))
		ch=getchar();
	while(isdigit(ch))
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
bool cmp(node a,node b)
{
	return a.a<b.a;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		x[i].a=read(),x[i].c=read(),sum+=x[i].c;
	sort(x+1,x+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		las=max(las,x[i].a+x[i].c);
		if(las<x[i+1].a)
			sum+=x[i+1].a-las;
	}
	return 0//防抄袭 
	printf("%lld",sum);
	return 0;
}
```
看到这里了，就点个赞吧。

---

## 作者：Alan_Zhao (赞：2)

## CF1503C 题解

赛后，看了一眼 Editorial 的转化，但没想到后面比较妙的计算方式。

考虑将 $\max(c_i,a_j-a_i)$ 转化成 $c_i+\max(0,a_j-a_i-c_i)$。由于每个点都会经过恰好一次，所以答案最小就是 $\sum c_i$，然后只需要处理 $\max$ 即可。

将所有城市按照 $a_i$ 升序排序，并将它们重编号为 $1\sim n$。这时候答案可以表示为 $1\to n \to 1$ 且每个点恰好经过一次的最小花费。

可以发现，$n\to 1$ 的代价恒为 $0$。于是只需要考虑 $1\to n$ 的最小代价，然后从 $n\to 1$ 的路径上再覆盖未被经过的点即可。

设 $f_i$ 为 $i\to n$ 的最小代价。首先二分求出 $k$，表示最小的满足 $a_k-a_i-c_i>0$ 的位置。然后 $f_i=\min\left(\min(f_{i+1},f_{i+2},\dots , f_{k-1}),\min(f_{k}+a_k,\dots,f_{n}+a_n)-a_i-c_i\right)$。

前半部分用线段树维护，后半部分开个数组维护即可。

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <utility>
#include <algorithm>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T>
inline bool chkmax(T &i,const T&j){return i<j?(i=j,1):0;}
template<typename T>
inline bool chkmin(T &i,const T&j){return i>j?(i=j,1):0;}
template<typename T> void Read(T &x){
	快读略;
}
typedef long long ll;
const int N=1e5+5;const ll Infll=0x3f3f3f3f3f3f3f3f;
typedef pair<ll,ll> Pll;
int n;Pll a[N];ll min2[N],f[N];
#define ls(xx) ((xx)<<1)
#define rs(xx) ((xx)<<1|1)
struct Node{Node():v(Infll){}ll v;}t[N<<2];
void Pushup(int p){t[p].v=min(t[ls(p)].v,t[rs(p)].v);}
void Modify(int p,int L,int R,int x,ll k){
	if(L==R){
		t[p].v=k;return;
	}int mid=(L+R)>>1;
	if(x<=mid) Modify(ls(p),L,mid,x,k);
	else Modify(rs(p),mid+1,R,x,k);
	Pushup(p);
}
ll QMin(int p,int L,int R,int l,int r){
	if(l<=L&&R<=r) return t[p].v;
	int mid=(L+R)>>1;ll res=Infll;
	if(l<=mid) chkmin(res,QMin(ls(p),L,mid,l,r));
	if(r>mid) chkmin(res,QMin(rs(p),mid+1,R,l,r));
	return res;
}
int main(){
	Read(n);
	For(i,1,n){
		Read(a[i].first);Read(a[i].second);
	}
	sort(a+1,a+n+1);
	min2[n+1]=Infll;
	min2[n]=a[n].first;Modify(1,1,n,n,0);
	Dec(i,n-1,1){
		int k=upper_bound(a+i+1,a+n+1,make_pair(a[i].first+a[i].second,Infll))-a;
		f[i]=min(QMin(1,1,n,i,k-1),min2[k]-a[i].first-a[i].second);
		Modify(1,1,n,i,f[i]);min2[i]=min(min2[i+1],f[i]+a[i].first);
	}
	ll ans=f[1];
	For(i,1,n) ans+=a[i].second;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：kradcigam (赞：2)

题目翻译：

有 $n$ 个城市，第 $i$ 个城市有两个值 $a_i$ 和 $c_i$。

现在一个人要从 $1$ 号城市出发，经过每个城市最后回到 $1$ 号城市。从第 $i$ 号城市到 第 $j$ 号城市需要花费 $\max(c_i,a_j-a_i)$ 的费用。求环游的最少花费。

$a$ 从小到大排序，上方 $a+c$ 更大就跳过去，对答案贡献是$\max(0,now.a+now.c-nxt.a)$。也就是说一条路径如果能让你到的更远就走，否则不走。

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define mp make_pair
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=1e5+10;
int a[N],c[N],f[N],mx;
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
	int n=read();LL ans=0;
	F(i,1,n)a[i]=read(),c[i]=read(),ans+=c[i],f[i]=i;
	sort(f+1,f+n+1,cmp);
	F(i,1,n-1){
		mx=max(mx,a[f[i]]+c[f[i]]);
		if(mx<a[f[i+1]])ans+=a[f[i+1]]-mx;
	}cout<<ans;
	return 0;
}
```

---

## 作者：charm1 (赞：1)

## 分析

首先我们分析一下代价式，

$max(c_i,a_j-a_i)=max(0,a_j-a_i-c_i)+c_i$

设 $h_i=a_i+c_i$

则$ans=\sum_{i=1}^{n}c_i+\sum_{i=1}^n max(0,a_j-h_i)$

显然向 $h_i \ge a_j$ 更小的地方走不耗费代价

所以不断向 $h_i$ 更大的地方走更优

然后计算每次走的代价，再加上$\sum_{i=1}^{n}c_i$就好了

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100005;
int n,ans,nowh;
struct nod{
	int h,val,pos;
}a[maxn];
bool cmp(nod x,nod y){return x.val<y.val;}
inline int read(){
	int ret=0,f=1;	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f; 
}
signed main(){
	n=read();
	for(int k=1;k<=n;k++){
		int c,val;
		val=read();	c=read();
		ans+=c;
		a[k].h=c+val;
		a[k].pos=k;
		a[k].val=val;
	}
	sort(a+1,a+n+1,cmp);//先考虑a[i]小的
	nowh=a[1].h;
	for(int k=1;k<=n;k++){
		int val=a[k].val;
		if(val>nowh)	ans+=val-nowh;
		nowh=max(nowh,a[k].h);
  		//nowh为当前h最大值，如果h[i]<nowh就最后再走
	}
	printf("%lld\n",ans);
	return 1;//防抄
}
```


---

## 作者：Kingna (赞：0)

### 题面翻译

C 国有 $n$ 个城市（编号为 $1$ 到 $n$），第 $i$ 个城市有美丽值 $a_i$ 和基价 $c_i$。

一位旅行商要旅行，他希望从城市 $1$ 开始，经过其他的每个城市正好一次，然后回到城市 $1$。

对于任意 $i\not=j$，从城市 $i$ 到达城市 $j$ 需要 $\max(c_i,a_j-a_i)$ 个金币。求旅行商完成旅行所需花费的最少金币数。

$2\leq n\leq10^5,0\leq a_i,c_i\leq10^9$

### 思路

是一道非常巧妙的题。将城市按照 $a_i$ 从小到大排序。观察 $\max(c_i,a_j-a_i)$ 的形式，发现所有 $c_i$ 一定是计算进答案了的。所以可以这样考虑：先对每个城市**都统计上** $c_i$，如果存在第 $i$ 个城市的指标为 $c_i+a_i$，满足存在城市 $j(j ≠i)$ 使得 $a_j\leq c_i+a_i$，那么从 $i$ 走到 $j$ 就是免费的。

那么可以这样考虑：如果当前统计到的 $c_j+a_j$ 的最大值小于 $a_i$，那么额外加上 $a_i-c_j-a_j$ 即可。如何达成此条件？就是从 $c_j+a_j$ 最大值的位置走到当前节点 $i$。最大值的位置会不会走到多个节点？答案是不会。每当遇到一次 $c_j+a_j$ 的最大值小于 $a_i$ 的情况，最大值的位置都会被当前的 $a_i+c_i$ 更新掉。

代码：https://pastebin.com/921Mc2Fg

---

## 作者：FxorG (赞：0)

~~吃啥补啥，所以我补C~~。

## 分析
首先 $max(c_i,a_j-a_i)$ 就很烦，我们发现 $ ans \ge \sum c_i \ (i \in [1,n]) $.

那么我们可以先计算 $c_i$ 对其他的我们按a排序后分类讨论。

若 $c_i \ge a_j-a_i$ 即 $c_i+a_i \ge a_j$ 即最后统计不用再算，反之，我们需要 $ ans+=a_j-a_i-c_i $.

所以最后遍历时记录 $c_i+a_i$ 就好了。

##  Code
```cpp

#include <bits/stdc++.h>

#define N (int)(2e5+5)
#define int long long

using namespace std;

struct node {
	int a,c;
}g[N];

bool operator < (node x,node y) {
	return x.a<y.a;
}

int n;

signed main() {
	scanf("%lld",&n);
	int ans=0;
	for(int i=1;i<=n;i++) {
		scanf("%lld%lld",&g[i].a,&g[i].c);
		ans+=g[i].c;
	}
	sort(g+1,g+1+n);
	int pre=0;
	for(int i=1;i<=n;i++) {
		pre=max(pre,g[i].a+g[i].c);
		if(pre<g[i+1].a) ans+=g[i+1].a-pre;
	}
	printf("%lld",ans);
	return qwq;
} 

```


---

