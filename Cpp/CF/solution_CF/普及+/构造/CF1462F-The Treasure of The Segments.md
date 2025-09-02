# The Treasure of The Segments

## 题目描述

$Polycarp$有$n$个数字区间，每个区间有两个参数$l[i]$（起始），$r[i]$（结束）。

$Polycarp$对一个好集合的定义是：

你在所有元素中选取部分元素组成这个集合。

你可以在这个集合中找到一个元素$p[i]$，使这个集合中每个元素都至少含有$p[i]$左右区间涵盖的数字之一。

题目给的样例$[[1,4],[2,3],[3,6]]$是一个好集合。$[[1,2],[2,3],[3,5],[4,5]]$则不是一个好集合。

现在给你$n$个数字区间，让你求从中至少删去多少个元素，才能使该集合为一个好集合。

## 样例 #1

### 输入

```
4
3
1 4
2 3
3 6
4
1 2
2 3
3 5
4 5
5
1 2
3 8
4 5
6 7
9 10
5
1 5
2 4
3 5
3 8
4 8```

### 输出

```
0
1
2
0```

# 题解

## 作者：mot1ve (赞：8)

看到别的大佬的一篇题解，思路非常巧妙并且简单，不需要离散化和任何数据结构。

洛谷还没这种做法。我补充一下。

很显然题目可以转化为求与其他直线相交的最多的一条直线交了几条直线，要删的直线个数就是总直线数减去它。

如果一个直线和另一个直线没有交点，要么它的左端点大于当前直线的右端点，要么它的右端点小于当前直线的左端点。累加起来就行了。先排序，然后用二分查找来确定位置。

```
#include<bits/stdc++.h>
using namespace std;
int T;
struct node{
	int x,y;
}a[1000010];
vector<int> l,r;
int main()
{
	cin>>T;
	while(T--)
	{
		int n;
		scanf("%d",&n);
		l.clear();
		r.clear();
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a[i].x,&a[i].y);
			l.push_back(a[i].x);
			r.push_back(a[i].y);
		}
		sort(l.begin(),l.end());
		sort(r.begin(),r.end());
		int ans=1e9;
		for(int i=1;i<=n;i++)
		{
			int res=0;
			int dl=upper_bound(l.begin(),l.end(),a[i].y)-l.begin();
			res+=(n-dl+1);
			int dr=lower_bound(r.begin(),r.end(),a[i].x)-r.begin();
			res+=(dr-1);
			ans=min(ans,res);
		}
		cout<<ans<<endl;
	} 
	return 0;
} 
```

---

## 作者：Eibon (赞：6)

如果两条线段想要相交，则一条线段的左端点需大于另一条的左端点且小于另一条的右端点，而这条线段的右端点需大于另一条的右端点。

那么，对于每条线段，我们只需要知道左端点比它的右端点大的线段数量，与右端点比其左端点小的线段数量之和。

可以用 vector 维护，用 lower_bound 进行查找，在查找左端点比它的右端点更大的时候，要给它的右端点加 $1$，因为最后要用 $n$ 减去这个数，不能取等。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int T,n,res,ans;
struct node
{
	int l,r;
};
node a[maxn];
vector<int>l,r;
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		l.clear();r.clear();
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a[i].l,&a[i].r);
			l.push_back(a[i].l);
			r.push_back(a[i].r);
		}
		sort(l.begin(),l.end());
		sort(r.begin(),r.end());
		ans=1e18;
		for(int i=1;i<=n;i++){
			int ll=lower_bound(l.begin(),l.end(),a[i].r+1)-l.begin();
			int rr=lower_bound(r.begin(),r.end(),a[i].l)-r.begin();
			ans=min(ans,n+rr-ll);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Warriors_Cat (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1462F)

题意可以从这里看，这里不在赘述。

---

### $Solution:$

枚举那个要与所有线段相交的线段，统计需要删掉的线段个数即可。

很显然当一个线段的右端点小于这条线段的左端点，或者一个线段的左端点大于这条线段的右端点时，这个线段需要删除。

所以可以先统计每个点存在的端点个数，再用前缀和优化一下就行了。

注意到 $l, r \le 10^9$，于是需要离散化。

over，时间复杂度为 $O(n \log n)$。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
#define ll long long
#define fi first
#define se second
#define y1 y_csyakioi_1
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010;
int t, n, lsh[N << 1], len, cl[N << 1], cr[N << 1];
struct node{
    int l, r;
}a[N];
inline int id(int x){ return lower_bound(lsh + 1, lsh + len + 1, x) - lsh; }
inline void work(){
	n = read(); len = 0;
	for(int i = 1; i <= n; ++i) a[i].l = read(), a[i].r = read();
	for(int i = 1; i <= n; ++i) lsh[2 * i - 1] = a[i].l, lsh[2 * i] = a[i].r;
	sort(lsh + 1, lsh + 2 * n + 1);
	len = unique(lsh + 1, lsh + 2 * n + 1) - lsh - 1;
	for(int i = 1; i <= n; ++i) a[i].l = id(a[i].l), a[i].r = id(a[i].r);
	for(int i = 1; i <= 2 * n; ++i) cl[i] = cr[i] = 0;
	for(int i = 1; i <= n; ++i) ++cl[a[i].l], ++cr[a[i].r];
	for(int i = 1; i <= 2 * n; ++i) cl[i] += cl[i - 1], cr[i] += cr[i - 1];
	int ans = 0x7f7f7f7f;
	for(int i = 1; i <= n; ++i){
   		ans = min(ans, cr[a[i].l - 1] + cl[2 * n] - cl[a[i].r]);
	}
	printf("%d\n", ans);
}
int main(){
	t = read(); while(t--) work();
	return 0;
}
```


---

## 作者：sccc_ (赞：1)

## Solution

用 vector 数组维护每条线段的左右端点。

如果两条线段相交，证明其右边的线段的左端点一定大于左边线段的左端点，小于左边线段的右端点，右边线段的右端点一定大于左边线段的右端点，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/krtzsf22.png)

最后，先排序端点，再用 `lower_bound` 寻找位置即可。

```c++
  #include <bits/stdc++.h>
  using namespace std;

  #define int long long
  const int N = 200005;
  int t;
  int n;

  struct node
  {
    int l, r;
  }a[N];

  vector<int> lt, rt;
  int minn = 1e18;

  void work()
  {
    lt.clear(), rt.clear();
    minn = 1e18;
    cin >> n;
    for (int i = 1; i <= n; i ++)
      cin >> a[i].l >> a[i].r, lt.push_back(a[i].l), rt.push_back(a[i].r);
    sort (lt.begin(), lt.end());
    sort (rt.begin(), rt.end());
    for (int i = 1; i <= n; i ++)
    {
      int sum = 0;
      int idl = lower_bound(lt.begin(), lt.end(), a[i].r + 1) - lt.begin();
      int idr = lower_bound(rt.begin(), rt.end(), a[i].l) - rt.begin();
      minn = min (minn, n - idl + idr);
    }
    cout << minn << '\n';
    return ;
  }

  signed main()
  {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t --)
      work();
    return 0;
  }
```

---

## 作者：Cure_Wing (赞：1)

[CF1462F The Treasure of The Segments](https://www.luogu.com.cn/problem/CF1462F)

### 思路

首先题目原意是说，删除最少的线段使得有一条线段与其它线段都相交。

我们可以理解为选择一条线段删除不与它相交的线段条数的最小值，也就是要求区间内包含的线段条数的最大值。

本来是二分的，但是被我想坏了想成了[莫队](http://oi-wiki.com/misc/mo-algo/)。

具体是这么想的：对于一个区间 $[l,r]$，如果右端点需要右移，那么如果遇到区间左端点，那么将区间计入；如果右端点需要左移，那么如果遇到区间左端点，那么把区间删去。左端点移动也是如此，只不过配对的是右端点了。

剩下的操作就是莫队的基本操作了。但是本题的值域比较大，需要先离散化。

[时间复杂度 $O(\sum(n\sqrt{n}+n\log n))$](http://oi-wiki.com/misc/mo-algo/#%E5%A4%8D%E6%9D%82%E5%BA%A6%E5%88%86%E6%9E%90)。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using std::cin;using std::cout;
constexpr int N=200005;
int t,n,a[N*2],l[N*2],r[N*2],base;
struct node{int l,r;}edge[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    for(cin>>t;t--;){
        cin>>n;base=sqrt(n);
        for(int i=1;i<=n;++i){
            cin>>edge[i].l>>edge[i].r;
            a[i*2-1]=edge[i].l;a[i*2]=edge[i].r;
        }
        std::sort(a+1,a+2*n+1);
        int k=std::unique(a+1,a+2*n+1)-a-1;
        for(int i=1;i<=n;++i){
            edge[i].l=std::lower_bound(a+1,a+k+1,edge[i].l)-a;
            edge[i].r=std::lower_bound(a+1,a+k+1,edge[i].r)-a;
        }//离散化
        for(int i=1;i<=2*n;++i) l[i]=r[i]=0;
        for(int i=1;i<=n;++i){++l[edge[i].l];++r[edge[i].r];}
        std::sort(edge+1,edge+n+1,[](node a,node b){if(a.l/base!=b.l/base) return a.l/base<b.l/base;return a.r/base<b.r/base;});//莫队基本操作
        int u=1,v=0,sum=0,ans=n;
        for(int i=1;i<=n;++i){
            while(edge[i].l<u){--u;sum+=r[u];}
            while(v<edge[i].r){++v;sum+=l[v];}
            while(u<edge[i].l){sum-=r[u];++u;}
            while(edge[i].r<v){sum-=l[v];--v;}//左右端点的移动
            ans=std::min(ans,n-sum);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：zztqwq (赞：1)

[更好的阅读体验](https://www.cnblogs.com/juruo-zzt/p/14165398.html)

## Solution

枚举哪个线段与其他所有线段重合，并通过树状数组计算与之重合的线段的数量，数量最多的即为所求线段。

至于如何统计，可以将所有线段以左端点为第一关键字、右端点为第二关键字排序，对于每一个线段 $[l_i,r_i]$，左端点小于它的（$[l_1,r_1],[l_2,r_2],\cdots,[l_{i-1},r_{i-1}]$），统计右端点处于区间 $[l_i,+\infty)$ 的有多少个；左端点大于它的（$[l_{i+1},r_{i+1}],[l_{i+2},r_{i+2}],\cdots,[l_n,r_n]$），统计左端点处于区间 $[l_i,r_i]$，二者相加的和即与该线段重合的线段的数量。由于 $1 \leq l \leq r \leq 10^9$，树状数组统计前需要离散化。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=2e5;
struct segment
{
	int l,r;
	segment() {}
	bool operator < (const segment &x) const {return l==x.l?r<x.r:l<x.l;}
}a[N+10];
int c1[N*2+10],c2[N*2+10],n,m,t[N*2+10];
void modify(int *c,int x,int d) {for(;x<=m;x+=x&-x) c[x]+=d;}
int query(int *c,int x)
{
	int ans=0;
	for(;x;x-=x&-x) ans+=c[x];
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",&a[i].l,&a[i].r);
			t[i*2-1]=a[i].l;
			t[i*2]=a[i].r;
		}
		sort(a+1,a+n+1);
		sort(t+1,t+n*2+1);
		m=unique(t+1,t+n*2+1)-t-1;
		for(int i=0;i<=m;i++)
		{
			c1[i]=0;
			c2[i]=0;
		}
		for(int i=1;i<=n;i++)
		{
			a[i].l=lower_bound(t+1,t+m+1,a[i].l)-t;
			a[i].r=lower_bound(t+1,t+m+1,a[i].r)-t;
		}
		int ans=0;
		for(int i=1;i<=n;i++) modify(c2,a[i].l,1);
		for(int i=1;i<=n;i++)
		{
			ans=max(ans,query(c1,m)-query(c1,a[i].l-1)+query(c2,a[i].r)-query(c2,a[i].l-1));
			modify(c2,a[i].l,-1);
			modify(c1,a[i].r,1);
		}
		printf("%d\n",n-ans);
	}
	return 0;
}
```

---

## 作者：mango2011 (赞：0)

贡献一发复杂的题解（怎么做出 *2200 的感觉了？）。

首先，题意就是问我们：至少删掉多少条线段，才能至少存在一条线段，使得所有线段都与它相交。

转化：我们找到一条线段，使得有最多的线段与之相交，设与之相交的线段条数为 $ans_0$，则答案为 $n-ans_0$。

接下来我们考虑 $ans_0$：

先枚举每一条线段，对于第 $i$ 条线段，与这条线段相关的线段有两类：

1) 左端点在 $[l_i,r_i]$ 内，右端点在 $[l_i,r_i]$ 内，这一类线段数量为 $s_0$。

2) 左右端点都在 $[l_i,r_i]$ 内，这一类线段数量为 $s_1$。

则与之相交的线段数量就是 $s_0-s_1$。

**先对所有线段离散化。**

$s_0$ 分成两类计算，一个前缀和搞定；至于 $s_1$ 的话，我们可以先按照左端点排好序，然后使用分块的方法，在单次询问 $\sqrt n$ 的时间复杂度内解决。

初始时令 $ans_0=0$，每一次令 $ans_0=\max(ans_0,s_0-s_1)$，最后输出 $n-ans_0$ 即可。

**注意：本题的空间限制对分块算法极不友好，需要把块长设置成 $2000$ 左右。**

综上，我们在~~不优秀的~~ $O(n\sqrt n+n\log n)$  的复杂度内做完了本题。

---

## 作者：紊莫 (赞：0)

首先有一个重要的转化：最少的删除次数就是相离的线段条数，那么我们可以贪心地找相离条数最小的即为答案。

这样就很简单了，考虑 $i$ 和 $j$ 相离的条件，$l_i>r_j$ 或 $r_i<l_j$，显然这两者不可能同时满足，那么直接分别计算再相加求最值即可。

核心代码如下。

```cpp
cin>>n;
F(i,1,n){
	cin>>L[i]>>R[i];
	x[i]={L[i],R[i]};
}
sort(L+1,L+n+1);
sort(R+1,R+n+1);
int ans=inf;
F(i,1,n){
	int a=upper_bound(L+1,L+n+1,x[i].r)-L-1;a=n-a;
	int b=lower_bound(R+1,R+n+1,x[i].l)-R-1;
	ans=min(ans,a+b);
}
cout<<ans<<'\n';
```



---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

`vector` 数据类型也是可以排序的。

题目就是求与其他直线相交的最多的一条直线相交的直线数，要删的直线个数就用总直线数减去这个最多的直线数。如果一个直线和另一个直线没有交点，只有两种可能：

- 左端点大于右端点。
- 右端点小于当左端点。

这个东西累加起来就是答案了。

我们要先排序，再用二分确定位置。

参考代码：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node
{
	int x, y;
} a[1000005];
vector <int> l, r;

int main()
{
    int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		l.clear();
		r.clear();
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i].x >> a[i].y;
			l.push_back(a[i].x);
			r.push_back(a[i].y);
		}
		sort(l.begin(), l.end());
		sort(r.begin(), r.end());
		int ans = 1e9;
		for (int i = 1; i <= n; i++)
		{
			int res = 0;
			int t1 = upper_bound(l.begin(), l.end(), a[i].y) - l.begin();
			res += (n - t1 + 1);
			int t2 = lower_bound(r.begin(), r.end(), a[i].x) - r.begin();
			res += (t2 - 1);
			ans = min(ans, res);
		}
		cout << ans << endl;
	} 
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

# $\mathcal{Solution}$

首先离散化一下，线段的值域变为 $[1,2n]$。

对于一条线段 $i$ 来说，考虑它作为和全部线段有交的那个线段来更新答案。

那么统计有多少线段和它不相交即可，只有在它左边或在它右边，那么就相当于对于每个 $i$ 查询一下有多少 $j$ 满足 $r_j<l_i$ 或 $l_j>r_i$。

两种询问分别离线下来扫一遍即可。

# $\mathcal{Cdoe}$


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
namespace do_while_true {
	#define ld double
	#define ll long long
	#define re register
	#define pb push_back
	#define fir first
	#define sec second
	#define pp std::pair
	#define mp std::make_pair
	const ll mod = 1000000007;
	template <typename T>
	inline T Max(re T x, re T y) { return x > y ? x : y; }
	template <typename T>
	inline T Min(re T x, re T y) { return x < y ? x : y; }
	template <typename T>
	inline T Abs(re T x) {	return x < 0 ? -x : x; }
	template <typename T>
	inline void read(re T& r) {
		r = 0; bool w = 0; char ch = getchar();
		while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
		while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
		r = w ? -r : r;
	}
	template <typename T>
	inline T qpow(re T x, re T y) {
		re T sumq = 1; x %= mod;
		while(y) {
			if(y&1) sumq = sumq * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return sumq;
	}
}
using namespace do_while_true;

const int N = 401000;
int n, ans, b[N], l[N], r[N], c1[N], c2[N], as1[N], as2[N];
struct Q1 {
	int l, p;
	bool operator < (const Q1& x) const {
		return l < x.l;
	}
}vec1[N];
struct Q2 {
	int l, p;
	bool operator < (const Q2& x) const {
		return l < x.l;
	}
}vec2[N];

void solve() {
	read(n); ans = n;
	for(int i = 1; i <= n; ++i) {
		read(l[i]); read(r[i]);
		b[i*2-1] = l[i], b[i*2] = r[i];
	}
	for(int i = 0; i <= 2 * n + 1; ++i) c1[i] = c2[i] = 0;
	std::sort(b + 1, b + 2 * n + 1);
	int tot = std::unique(b + 1, b + 2 * n + 1) - b - 1;
	for(int i = 1; i <= n; ++i)
		l[i] = std::lower_bound(b + 1, b + tot + 1, l[i]) - b,
		r[i] = std::lower_bound(b + 1, b + tot + 1, r[i]) - b,
		vec1[i].l = l[i],
		vec2[i].l = r[i],
		vec1[i].p = i,
		vec2[i].p = i,
		c1[r[i]]++,
		c2[l[i]]++;
	std::sort(vec1 + 1, vec1 + n + 1);
	std::sort(vec2 + 1, vec2 + n + 1);
	int p = 0;
	for(int i = 1, sum = 0; i <= n; ++i) {
		while(p < vec1[i].l) sum += c1[p], ++p;
		as1[vec1[i].p] = sum;
	}
	p = 2 * n + 1;
	for(int i = n, sum = 0; i >= 1; --i) {
		while(p > vec2[i].l) sum += c2[p], --p;
		as2[vec2[i].p] = sum;
	}
	for(int i = 1; i <= n; ++i)
		ans = Min(ans, as1[i] + as2[i]);
	printf("%d\n", ans);
}

signed main() {
	#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	#endif
//	freopen("out1.txt", "w", stdout);
	int T = 1;
	read(T);
	while(T--)
		solve();
	fclose(stdin);	
	return 0;
}
```

---

## 作者：lzx1999 (赞：0)

#### 题目求的是删除最少的线段使存在一条线段能够和其他所有线段均重合
因此我就可以取查找每条线段能与多少条线段重合,找到最大的重合数目和n做差再减1就是答案,这里减1是再把这条线段本式减掉\
因此我们考虑一条线段设为[l,r]很容易就发现一条线段和其他线段相交的数量只有两种情况\
①线段的左端点在区间[l,r]中间\
②线段左端点小于等于l,右端点大于等于l的,也就是说和左端点l有重合的线段

对于第一种情况我们需要将建立一个前缀数组sum1[i], sum1[i]表示区间[1,i]中间存在多少左端点\
```cpp
	for(int i = 1 ; i <= n ; i ++) sum1[l[i]] ++;
  	for(int i = 1 ; i <= 2 * n ; i ++) sum1[i] += sum1[i - 1];
	//其中l[i]已经经过离散化处理,因为有n个线段,也就是说存在2n个点
```
对于第二种情况我们也可以维护一个前缀数组,利用来得到经过[l,r]的左端点的线段数目
```cpp
	for(int i = 1 ; i <= n ; i ++) sum2[l[i]] ++, sum2[r[i]+1]--;
  	for(int i = 1 ; i <= 2 * n ; i ++) sum2[i] += sum2[i - 1];
	//其中l[i]和r[i]已经经过离散化处理,因为有n个线段,也就是说存在2n个点
```
因此我们考虑枚举所有线段求一下当前线段覆盖其余线段数量的最大值在+1
```cpp
	for(int i = 1 ; i <= n ; i ++)
		ans = max(ans, sum1[l[i]] + sum1[r[i]] - sum1[l[i]]);
	cout << n - ans << endl;
// 其中每条线段的贡献不需要在+1是因为我们在之前预处理的时候就已经把当前线段的贡献也加到前缀数组
```



---

