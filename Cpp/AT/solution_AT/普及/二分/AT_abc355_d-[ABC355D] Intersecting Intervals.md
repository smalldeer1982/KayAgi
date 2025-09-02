# [ABC355D] Intersecting Intervals

## 题目描述

### 问题陈述

给你 $N(2 \leq N \leq 5 \times 10^5)$ 个实数区间。第 $i$ $(1 \leq i \leq N)$ 个区间是 $[l _ i, r _ i](0 \leq l_i < r_i \leq 10^9)$ 。求有多少对 $(i, j),(1 \leq i < j \leq N)$ 中，$i$ 和 $j$ 两个区间相交。

## 样例 #1

### 输入

```
3
1 5
7 8
3 7```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 4
2 5
1 6```

### 输出

```
3```

## 样例 #3

### 输入

```
2
1 2
3 4```

### 输出

```
0```

# 题解

## 作者：I_Love_DS (赞：16)

## 思路

暴力方法：用 $i$ 和 $j$ 枚举每一对区间，如果重合，答案加一，最后输出答案。

但是，这样时间复杂度为 $O(n^2)$，无法通过此题。

### 优化

我们只需要知道两个前置知识，就可以通过此题：

1. **如果两个区间 $i,j$ 不相交，有以下两种情况：**
	- $l_j > r_i$
	- $r_j < l_i$
2. **相交的对数 = 区间对数总数 - 不相交区间对数，所以统计出不相交区间对数，然后推公式就可以求出相交的对数了。（因为不相交区间对数更好求）**

那么开 $b$ 数组为 $l_i$ 的升序结果，开 $c$ 数组为 $r_i$ 的升序结果。

那么**二分查找**第 $i$ 个区间，有多少对区间符合 $r_j < l_i$，有多少对区间符合 $l_j > r_i$。把这些贡献累加到 $sum$ 里。

但是，一对不相交的区间会计算两次，因为算第 $i$ 个不相交的区间时，会把第 $j$ 个区间加一次；然后算第 $j$ 个不相交的区间时，会把第 $i$ 个区间加一次。所以最后把 $sum \div 2$ 即可。

所有的区间对数为 $n \times (n - 1) \div 2$，不相交的对数为 $sum$，那么相交的对数就是 $n \times (n - 1) \div 2 - sum$。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct node {
	int l,r;
} a[500050],b[500050],c[500050];
bool st1(const node &x,const node &y){
	return x.l < y.l;
}
bool st2(const node &x,const node &y){
	return x.r < y.r;
}
long long sum = 0;
int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d%d",&a[i].l,&a[i].r);
	memcpy(b,a,sizeof(b));
	memcpy(c,a,sizeof(c));
	sort(b + 1,b + n + 1,st1);
	sort(c + 1,c + n + 1,st2);
	//复制，排序
	for (int i = 1; i <= n; i++) {
		int l,r,mid;
		l = 0,r = n + 1;
		while (l + 1 < r) {
			mid = (l + r) / 2;
			if (b[mid].l > a[i].r) r = mid;
			else l = mid;
		}
		sum += n - r + 1;
		//l_j > r_i
		l = 0,r = n + 1;
		while (l + 1 < r) {
			mid = (l + r) / 2;
			if (c[mid].r < a[i].l) l = mid;
			else r = mid;
		}
		sum += l;
		//r_j < l_i
	}
	sum /= 2;
	printf("%lld",1LL * n * (n - 1) / 2 - sum);
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：8)

一眼二分。

考虑按左端点 $l_i$ 升序排序。

枚举 $i$，二分查找最小的 $k$ $(i+1 \leq k\leq N)$，使得 $l_k>r_i$。

计算一下贡献：$ans=ans+k-i$。

## Code

[Link](https://atcoder.jp/contests/abc355/submissions/53856416)

---

## 作者：tder (赞：7)

[ABC355 场记](https://tder6.github.io/articles/ABC355A%20to%20ABC355E%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。 

---

**【题意】**

给定 $n$ 个闭区间 $[L_i,R_i]$，求其中相交的对数。

**【思路】**

赛后听说有很多人拿二分过的？

考虑扫描线。

![](https://cdn.luogu.com.cn/upload/image_hosting/rgnd3a2z.png)

如上图所示，将每个区间拆成左右端点 $L_i$ 和 $R_i$，并排序。

想象有一条扫描线，从左到右扫，用 $c$ 表示当前其所在的区间个数：

- 当扫到左端点 $L_i$，第 $i$ 个区间在此处开始，所在区间个数增加 $1$，即 $c\gets c+1$。如上图红线所示；
- 当扫到右端点 $R_i$，第 $i$ 个区间在此处终止，所在区间个数减少 $1$，即 $c\gets c-1$。同时，将答案累加 $c$，即 $\text{ans}\gets\text{ans}+c$。如上图蓝线所示。

下面证明其正确性。

我们知道，若两个区间 $x,y$ 相交，其中 $L_x<L_y$，可分为：

- $x$ 不完全包含 $y$，即先扫到 $x$ 的左端点，再扫到 $y$ 的左端点，再扫到 $x$ 的左端点，最后扫到 $y$ 的右端点。如上图的第 $1$ 个和第 $2$ 个区间；
- $x$ 完全包含 $y$，即先扫到 $x$ 的左端点，再扫到 $y$ 的左端点，再扫到 $y$ 的左端点，最后扫到 $x$ 的右端点。如上图的第 $2$ 个和第 $3$ 个区间。

也就是说：

- 若 $x$ 不完全包含 $y$，则在扫到 $x$ 的右端点时，扫描线一定在 $y$ 上，即 $c$ 中有 $y$ 的贡献；
- 若 $x$ 完全包含 $y$，则在扫到 $y$ 的右端点时，扫描线一定在 $x$ 上，即 $c$ 中有 $x$ 的贡献。

故每个右端点处的 $c$ 之和即为答案。

特别的，对于如图所示的紫线，即同时在某区间左端点又在另一区间右端点，应先处理左端点。这是因为本题中给定的是闭区间，这两个线段是相交的，先处理左端点才能对 $c$ 产生贡献。

时间复杂度 $O(n\log n)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e3 + 5;
int n, c, ans;
struct Node {
	int t, p;
};
bool operator<(Node x, Node y) {
	if(x.p != y.p) return x.p < y.p;
	else return x.t < y.t;
}
vector<Node> d;
signed main() {
	cin>>n;
	for(int i = 1; i <= n; i++) {
		int l, r; cin>>l>>r;
		d.push_back({0, l}); d.push_back({1, r});
	}
	sort(d.begin(), d.end());
	for(auto i : d) {
		if(!i.t) c++;
		else ans += (--c);
	}
	cout<<ans<<endl;
}
```

---

## 作者：int_stl (赞：6)

一道二分题。

注意到区间 $A$ 和 $B$ 相交当且仅当 $A_r \ge B_l$，再结合数据范围，启发我们考虑二分。

那么，我们先把这些区间从小到大排序，然后对于每个 $i$，二分查找出一个满足 $A_{i_r} \ge A_{p_l}$ 的最大的 $p$，把答案加上 $p-i$ 即可。

时间复杂度 $O(n\log n)$。

代码如下：
```cpp
int n;
struct P {
	int l, r;
} a[500006];
bool cmp(P A, P B) {
	if (A.l != B.l) return A.l < B.l;
	return A.r < B.r;
}
int main() {
	read(n);
	rep(i, 1, n, 1) {
		read(a[i].l, a[i].r);
	}
	ll ans = 0;
	sort(a + 1, a + n + 1, cmp);
	rep(i, 1, n, 1) {
		/*int pos = i;
		while (pos < n && a[i].r >= a[pos].l) ++pos;
		if (a[i].r < a[pos].l) --pos;
		*/
		int l = i, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (a[i].r >= a[mid].l) {
				l = mid + 1;
			}
			else r = mid - 1;
		}
		// cout << l << endl;
		ans += (r - i);
		// cout << pos << endl;
	}
	write(ans);
}
```

---

## 作者：Redamancy_Lydic (赞：5)

涨大分了，乐。~~LC真可爱~~
## 题意

给你几个区间，问有几对区间相交。

## 分析

暴力显然不可做。

考虑先把所有区间按照左端点为第一关键字排序，然后离散化，接着我们开始从第一条线段遍历，由于线段是排好序的，所以对于每一条新加入的线段，它与先前已经添加过的线段相交的条件只能是它的左端点在先前线段的右端点左边。

于是我们对于新加入的线段，只要找到之前有几个线段的右端点在它左端点的右边，累加答案，并把这条线段的右端点加入右端点集合就行了。

所以就可以用一个裸的单点修改区间查询的线段树维护了。

这道题当然有其他更简单的方法，我在此只是想提供一种赛场上容易想到的思路。

## Code

```cpp
#include<bits/stdc++.h>
//#include<atcoder/modint>
#define int long long
#define mod 998244353
using namespace std;
//using mint=atcoder::modint998244353;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
int n;
struct no
{
	int l,r;
}a[maxn];
int li[maxn*2],tot;
void lisanhua()
{
	sort(li+1,li+tot+1);
	tot=unique(li+1,li+tot+1)-li-1;
	for(int i=1;i<=n;i++)
	{
		a[i].l=lower_bound(li+1,li+tot+1,a[i].l)-li;
		a[i].r=lower_bound(li+1,li+tot+1,a[i].r)-li;
	}
}
struct tree
{
	int l,r,d,add;
}t[maxn*4];
void upd(int p)
{
	t[p].d=t[p*2].d+t[p*2+1].d;
}
void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)
	{
		return ;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	upd(p);
}
void add(int p,int x)
{
	if(t[p].l==t[p].r)
	{
		t[p].d++;
		return ;
	}
	int mid=(t[p].l+t[p].r)>>1;
	if(x<=mid)add(p*2,x);
	else add(p*2+1,x);
	upd(p);
}
int ask(int p,int l,int r)
{
	if(t[p].l>=l&&t[p].r<=r)
	{
		return t[p].d;
	}
	int mid=(t[p].l+t[p].r)>>1,sum=0;
	if(l<=mid)sum+=ask(p*2,l,r);
	if(mid<r) sum+=ask(p*2+1,l,r);
	return sum;
}
int ans=0;
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		a[i].l=read();
		a[i].r=read();
		li[++tot]=a[i].l;
		li[++tot]=a[i].r;
	}
	sort(a+1,a+n+1,[](no x,no y){
		return x.l<y.l||x.l==y.l&&x.r<y.r;
	});
	lisanhua();
	build(1,1,maxn);
	for(int i=1;i<=n;i++)
	{
		ans+=ask(1,a[i].l,maxn);
		add(1,a[i].r);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qhr2023 (赞：2)

## 题意

给出 $N$ 个区间，求相交区间个数。

## 思路

我们不妨假设任意两个区间都相交，总数再减去不合法的区间数即为答案，这样问题就转化为求不相交的区间数。

先将左右端点分别排序，枚举左端点，则当前左端点与其左面的所有右端点都不相交，对于下一个左端点，与它不相交的右端点一定包括与上一个左端点不相交的右端点，所以我们再记录下当前右端点，这样问题就可以线性的解决。

这么说可能比较抽象，建议结合代码和样例帮助理解。

## 实现

贪心加双指针。

我们用 $i$ 表示当前左端点，用 $j$ 表示当前右端点，因为我们从 $0$ 计数，所以 $j$ 也是与在当前左端点左面点的个数，用 $ans$ 统计答案。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l[500005], r[500005];
int main(){
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> l[i] >> r[i];
	sort(l, l+n);
	sort(r, r+n);
	long long ans=1ll*n*(n-1)/2;
	for(int i=0, j=0; i<n; i++){
		while(j<n&&r[j]<l[i])
			j++;
		ans-=j;
	}
    cout << ans;
    return 0;
}
```

---

## 作者：Hughpig (赞：2)

对于所有区间，我们以 $l_i$ 作为关键字进行排序，然后对于区间 $i$，我们想办法计算它对后方的区间的贡献。

对于区间 $i$，它后面的区间 $j$ 必然满足 $l_i\le l_j$。因此如果区间 $j$ 要和区间 $i$ 相交，必然要满足 $l_j\le r_i$，也就是说，区间 $j$ 的左端点要被区间 $i$ 包含才行。

问题转化为对于某个区间 $i$，找出它后面有多少区间 $j$ 满足 $l_j\le r_i$。 

用一个数组 $a$ 存下所有区间的左端点，然后对于区间 $i$，在 $a$ 中找到有多少个元素大于等于 $r_i$ 即可，这可以用 `upper_bound` 二分实现。

时间复杂度 $O(N\log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int N=5e5+7;

ll n,ans,a[N];
struct Range{
	ll l,r;
	friend bool operator <(Range a,Range b){
		return a.l<b.l;
	}
}r[N];

int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)cin>>r[i].l>>r[i].r,a[i]=r[i].l;
    sort(r+1,r+n+1);
   	sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
    	ans+=upper_bound(a+1,a+n+1,r[i].r)-a-1-i;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yinxiangbo2027 (赞：2)

### [博客食用更加](https://www.luogu.com.cn/article/b1ypio7l)

## 分析：

本题十分简单。

首先我把这些区间按 $r$ 从小到大排个序，保证 $r$ 单调递增。然后依次遍历每个区间，因为我们保证了 $r$ 单调递增的，所以我们只需要看当前区间的 $l$ 小于等于前面哪些的 $r$ ，然后累加起来就好了，但时间复杂度是 $O(n^2)$，我们就要加一点点优化，我们在前面保证了 $r$ 单调递增，于是在看当前区间的 $l$ 小于等于前面哪些的 $r$ 时，我们就不用一个一个去遍历，只需用二分就好了,时间复杂度是 $O(n \log{n})$

## code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	long long l,r;
}a[1000005];
bool cmp(node x,node y){
	return x.r<y.r;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
	}
	sort(a+1,a+1+n,cmp);
	long long x=-1,cnt=0;
	for(int i=1;i<=n;i++){
		int x=1,y=i-1;
		while(x<=y){
			int mid=(x+y)/2;
			if(a[i].l<=a[mid].r){
				y=mid-1;
			}
			else{
				x=mid+1;
			}
		}
		cnt+=(i-1)-x+1;
	}
	cout<<cnt;
	return 0;
}
~~~

---

## 作者：Special_Tony (赞：2)

# 提示
1. 正难则反，可以总数减去无交集的部分；
1. $i$ 与 $j$ 无交集的条件是 $r_j<l_i$ 或 $l_j>r_i$
1. 二分是个好东西。

# 思路
上面基本已经说了大致思路。我们设 $l,r$ 为原数组，$L,R$ 也是原数组，但是单独排序了。然后我们枚举每个 $i$，只要分别二分一下 $R_j<l_i$ 和 $L_j>r_i$ 的数量即可。最后注意这个总和要除以 $2$，因为会把 $i<j$ 和 $i>j$ 都算进去。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, l[500005], r[500005];
ll sum;
pii a[500005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> l[i] >> r[i], a[i] = {l[i], r[i]};
	sort (l, l + n), sort (r, r + n);
	for (int i = 0; i < n; ++ i)
		sum += (lower_bound (r, r + n, a[i].first) - r) + (l + n - upper_bound (l, l + n, a[i].second));
	cout << n * (n - 1ll) / 2 - sum / 2;
	return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

# 1.题意
给定 $n$ 个区间 $l_i,r_i$，问你满足 $(i,j)$ 满足 $i<j$ 且区间 $i$ 和区间 $j$ 相交的个数。
# 2.解题思路
区间 $i$ 和区间 $j$ 相交（设 $l_i \le l_j$），当且仅当 $l_j \le r_i$。

因此我们可以按照 $l_i$ 递增将 $n$ 个区间排好序，跟第 $i$ 个区间有相交的就是 $(i+1,j)$，$j$ 为 $l_k \le r_i$ 的最大 $k$。

最后答案加上 $j-i$。
# 3.代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[500010],b;
long long ans;
struct o{
	int a,b;
	bool operator<(const o&t){return a<t.a;}
}s[500010];
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++)scanf("%d%d",&s[w].a,&s[w].b);
	sort(s+1,s+n+1);
	for(int w=1;w<=n;w++)a[w]=s[w].a;
	for(int w=1;w<=n;w++){
		int l=w+1,r=upper_bound(a+1,a+n+1,s[w].b)-a;
		if(l<r)r--,ans+=r-l+1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：1)

[Problem](https://www.luogu.com.cn/problem/AT_abc355_d)

题意：给 $n$ 个区间，求有几对区间相交。
- $1\le n\le 5\times 10^5,0\le l_i,r_i\le 10^9$

提供一种赛时写的复杂做法。

首先离散化，然后按照以左端点为第一关键字，右端点为第二关键字排序。

对于一个区间 $i$，考虑 $1\sim i-1$ 区间中与区间 $i$ 相交的个数，发现只要满足 $r_j\ge l_i(1\le j\le i-1)$ 这两个区间就会相交。

写一个权值线段树，每次答案加上大于 $l_i$ 的 $r_j$ 的个数，并在线段树中加入 $r_j$。

[赛时代码](https://atcoder.jp/contests/abc355/submissions/53866048)，复杂度 $O(n\log n)$。

---

## 作者：MMXIandCCXXII (赞：1)

$\Large{\text{Solution}}$

先按右端点从小到大排序，然后遍历，当前线段的左端点小于等于前面的线段的右端点就会产生贡献。

所以遍历到第 $i$ 条线段时，判断前 $i - 1$ 条线段中右端点有多少大于等于它的左端点。因为已经按右端点排序了，答案具有单调性，放到一个数组里二分即可。

时间复杂度 $\Omicron(n\log n)$。

$\Large{\text{Code}}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
	int l, r;
} a[500010];

bool cmp(node x, node y)
{
	return x.r < y.r;
}

vector <int> v;


signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    	cin >> a[i].l >> a[i].r;
    sort (a + 1, a + n + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
    	if (i == 1) v.push_back (a[i].r);
    	else
    	{
    		int x = lower_bound (v.begin (), v.end (), a[i].l) - v.begin ();
    		ans += v.size () - x;
    		v.push_back (a[i].r);
		}
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题目大意
给定 $n$ 个闭区间，问其中有多少对区间相交，包括在端点处有公共点的区间对。

### 思路大意
我们知道两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 相交的条件是 $l_1\leq l_2 \leq r_1$ 或者 $l_2\leq l_1 \leq r_2$。如果我们限定有 $l_1\leq l_2$，那么判定条件就变成了唯一的 $l_1\leq l_2 \leq r_1$。

既然涉及到端点坐标的大小，我们就考虑给区间排序，但是并没有什么用。

那么我们换种方法，给每个端点按坐标从小到大排序，并记录每个端点是一个区间的左端点还是右端点。

接着我们从小到大遍历每个端点。如果我们遇到了一个左端点，就代表一个区间开始了，这个区间与当前所有没有结束的区间相交，没有结束的区间数量加一。如果这是一个右端点，就代表一个区间结束了，没有结束的区间数量减一。

另外要注意，排序的时候坐标相等的端点，左端点要排在右端点前面，这样就不会漏算相交在端点的区间对。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,tp;//x:坐标，tp:0为左端点，1为右端点
	node(){}
	node(int x,int tp):x(x),tp(tp){} 
	bool operator < (const node & B)const{
		if(x==B.x)return tp<B.tp;//坐标相等的左端点在前面
		return x<B.x;
	}
}a[1000005];
int n;
long long ans,sum;
//ans:最终答案
//sum:当前未结束的区间个数
int main(){
	cin>>n;
	for(int i=0;i<2*n;i++){ //区间不用记了，直接记2n个端点就行
		cin>>a[i].x;
		if(i%2==1)a[i].tp=1;//如果是奇数就是右端点
		else a[i].tp=0;//否则是左端点
	}
	sort(a,a+2*n);
	for(int i=0;i<2*n;i++){
		int x=a[i].x,tp=a[i].tp;
		if(tp==0)ans+=sum,sum++;//一个区间开始了，记录答案，更新sum
		else sum--;//一个区间结束了
	}
	cout<<ans<<endl;
	return 0;//完结撒花
}
```

---

## 作者：LZYAC (赞：1)

## 思路
此题会发现判断相交其实不那么好判断，所以正难则反，对每个线段判断与之不相交的段数。

不难看出，两线段不相交的情况在 $a_r < b_l$ 时成立。

于是想到二分：对于每个线段的 $r$ 在 $l$ 数组中进行查找，最后用总数减去不相交数即可。

详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int l;
	int r;
}a[500010];
int n,ans,ll[500010],rr[500010],tmp;
bool cmp(node t1,node t2){
	return t1.l<t2.l;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].l,&a[i].r);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		ll[i]=a[i].l;
		rr[i]=a[i].r;
	}
	for(int i=1;i<n;i++){
		tmp=upper_bound(ll+1,ll+1+n,rr[i])-ll-1;
		ans=ans+tmp-i;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[[ABC355D] Intersecting Intervals](https://atcoder.jp/contests/abc355/tasks/abc355_d)

不用任何数据结构的方法。

按照左端点从小到大排序，对于每个 $i$，如果 $l_i\le r_j\le r_i$，那么 $i$ 和 $j$ 这两个线段相交。

只需 `upper_bound` 便可求出 $l_i\le r_j\le r_i$ 的 $r_j$ 的个数。

时间复杂度 $O(n\log n)$。

代码很短：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 10;
int n, L[N];
LL ans;
struct ST { int l, r; } a[N];
bool operator < (ST a, ST b) { return a.l < b.l; }
int main()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d %d", &a[i].l, &a[i].r);
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) L[i] = a[i].l;
	for (int i = 1; i <= n; i++)
		ans += upper_bound (L + 1, L + n + 1, a[i].r) - L - 1 - i;
	printf ("%lld", ans);
	return 0;
}
```

---

## 作者：wbw_121124 (赞：0)

可以考虑贪心。

你会发现不能使用树状数组，因为如果 $l_i<l_j(i \ne j)$ 时，不一定 $r_i>l_j$。

可以贪心地排序（第一关键字为位置，第二关键字为是否为 $l_i$，第三关键字为区间的编号），让枚举区间的 $l_i$ 时，答案加上前面没有闭合的区间，就行了。

```cpp
#include<bits/stdc++.h>
typedef int int32;
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, cnt, ans;
struct node {
	int x, id;
	bool f;
	bool operator< (const node& u) const
	{
		if (x != u.x)
			return x < u.x;
		if (f == u.f)
			return id < u.id;
		return f;
	}
};
vector<node>a(N);
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		a.push_back({ x,i,true });
		a.push_back({ y,i,false });
	}
	sort(a.begin(), a.end());
	for (auto& x : a)
		if (x.f == true)
			ans += cnt, cnt++;
		else
			cnt--;
	cout << ans;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定 $n$ 条线段，第 $i$ 条线段覆盖 $[l_i,r_i]$。

求有多少对线段之间有交集。

### 思路：

考虑按照左端点从小到大排序。

然后考虑第 $i$ 条线段右边有哪些线段与自己有交集。

因为 $i$ 后面的线段最端点都大于第 $i$ 条线段的左端点，即相当于要找到后面有多少条线段的左端点小于等于第 $i$ 条线段树的右端点。

直接二分即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=5e5+10;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r;
	bool operator<(const Node&rhs)const{
		if(l!=rhs.l)
		  return l<rhs.l;
		return r<rhs.r;
	}
}a[N];
ll n,ans;
ll l[N],r[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].l=read();
		a[i].r=read();
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	  l[i]=a[i].l,r[i]=a[i].r;
	for(int i=1;i<=n;i++){
		ll t=upper_bound(l+1,l+n+1,r[i])-(l+1);
		ans+=(t-i);
	} 
	write(ans);
	return 0;
}
```

---

## 作者：Guizy (赞：0)

- ### 题意

给你 $n$ 条线段 $[l_i,r_i]$，求有几对线段相交。

- ### 做法

输入有点乱，考虑先排序推一下（按 $l$ 为第一关键字 $r$ 为第二关键字排序）。

因为直线 $x,y$ 和 $y,x$ 相交对答案的贡献只算一次，所以我们只需要统计当前线段与前面线段的贡献即可。发现我们可以用一个小根堆维护。对于每个输入，如果堆顶的右端点小于现在的左端点，就把堆顶弹出，然后答案加上当前堆里的个数（其实就是相交的个数），最后把右端点加入堆。

- ### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
//不开 long long 见祖宗
using namespace std;

const int Max=500001;
int n,ans;
priority_queue<int,vector<int>,greater<int> >q; //STL小根堆
struct node{
	int l,r;
}ln[Max];//结构体方便排序

bool cmp(node x,node y){
	if(x.l==y.l) return x.r<y.r;
	else return x.l<y.l;
}

signed main(){
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>ln[i].l>>ln[i].r;
	sort(ln+1,ln+n+1,cmp);
	
	for(int i=1;i<=n;i++){
		int lft=ln[i].l;
		while(!q.empty()&&lft>q.top()) q.pop();
     		//用top之前判断一下是否非空不然会RE
		ans+=q.size();//统计答案
		q.push(ln[i].r);
	}
	cout<<ans;
}
```

---

## 作者：__Dist__ (赞：0)

按照左端点从小到大排序，左端点相同就按照右端点从小到大排序。

枚举 $1\sim n$，二分找到 $i$ 后面的区间第一个 $j$ 满足 $l_j > r_i$，也就是这两个区间没有重合，把答案增加 $j - 1 - i$。

不用考虑 $i$ 前面的区间，因为在考虑位置 $<i$ 的线段的时候已经考虑过了。

**警钟长鸣，不要忘记删 `std::cerr` 调试语句！**

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar

typedef long long ll;
const int MAXN = 5e5 + 5;
const int mod = 998244353;

ll read() {
	ll x = 0, f = 1;char ch = gt();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
	while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
	return x * f;
}

ll n;
std::pair<ll, ll> a[MAXN];
ll c[MAXN];

int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i].first = read();
		a[i].second = read();
	}
	std::sort(a + 1, a + n + 1);
	ll res = 0;
	for (int i = 1; i <= n; i++) c[i] = a[i].first;//为了方便二分，用 c 储存排序后的 l[i]
	for (int i = 1; i < n; i++) {
		ll p = std::upper_bound(c + i + 1, c + n + 1, a[i].second) - c;
		res += p - 1 - i;
	}
	std::cout << res << '\n';
	return 0;
}
```

---

## 作者：MicroSun (赞：0)

将所有区间按左端点位置排序。

排序后，如果区间 $[l_i,r_i],[l_j,r_j](i<j)$ 有交集，那么一定有 $r_j\ge r_i$。

观察到至于较大，所以需要离散化。

离散化后树状数组维护即可。

Code：

```cpp
// Problem: D - Intersecting Intervals
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=1e6+10;

pll a[maxn],b[maxn];
ll t[maxn],n=1e6;
#define lb(x) ((x)&-(x))
void upd(ll x){
	while(x){
		++t[x];
		x-=lb(x);
	}
}
ll get(ll x){
	ll ans=0;
	while(x<=n){
		ans+=t[x];
		x+=lb(x);
	}
	return ans;
}
void solve(){
	int n;
	cin>>n;
	rep(i,1,n) cin>>a[i].fst>>a[i].scd;
	map<int,int> mp;
	rep(i,1,n) mp[a[i].fst]=mp[a[i].scd]=1;
	int cnt=0;
	for(pii i:mp)
		mp[i.fst]=++cnt;
	rep(i,1,n){
		a[i].fst=mp[a[i].fst];
		a[i].scd=mp[a[i].scd];
	}
	sort(a+1,a+1+n);
	ll ans=0;
	rep(i,1,n){
		ans+=get(a[i].fst);
		upd(a[i].scd);
	}
	cout<<ans;		
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc355_d)
### 思路
如果这两个序列相互包含，说明其中一定有一个 $r_i$ 大于等于 $l_j$,且 $r_i \le r_j,i<j$。

我们可以按照 $r$ 从小到大排序，随后枚举每一个 $l_j$，在这个 $l$ 前面的数字中二分查找一个 $r_i$，使得 $r_i \ge l_j,i<j$，因为序列已经保证 $r_i \le r_j$，所以可以忽略第二个条件，最后有多少个序列就是这个位置到 $j$ 一共有多少个位置，将所有答案累加即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct jie
{
	int s1;
	int s2;
}a[500005]; 
bool cmp(jie w1,jie w2)
{
	return w1.s2<w2.s2;
}
int main()
{
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>a[i].s1>>a[i].s2;
	}
	long long ans=0;
	sort(a,a+n,cmp);
	for (int i=0;i<n;i++)
	{
		int l=0,r=i;
		while(l<r)
		{
			int mid=(l+r)/2;
			if (a[mid].s2>=a[i].s1)
			{
				r=mid;
			}
			else
			{
				l=mid+1;
			}
		}
		ans=ans+i-r;
	} 
	cout<<ans<<endl;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc355_d)
## 思路
发现如果把线段按照右端点从小到大排序。对于排完序后第 $i$ 条线段，前 $i - 1$ 条线段有几个的右端点大于等于第 $i$ 条线段的左端点，对答案的贡献就是几。
## 做法
先用结构体存下线段，然后按右端点从小到大排序。依次遍历每一条线段，由于右端点的单调性，可以用二分来求出有几条线段的右端点比当前的左端点大。**答案应该开 long long。**
## AC code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
const I N = 500100;
I n;
LL ans;//不开 long long 见祖宗 
struct line{//存储线段 
	I l,r;
	bool operator <(const line &B){
		return r < B.r;
	}
}a[N];
I main(){
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	sort(a + 1,a + n + 1);//按照上文排序 
	for(I i = 1;i <= n;i++){
		I l = 0,r = i;//二分求答案 
		//printf("%d %d\n",a[i].l,a[i].r);/*调试代码*/
		while(l + 1 < r){
			I mid = (l + r) / 2;
			if(a[mid].r < a[i].l){//分界线，左边的都不相交，右边的相交 
				l = mid;
			}else{
				r = mid;
			}
		}
		ans += (i - 1) - l;//对答案的贡献 
		//printf("%d\n",i - 1 - l);/*调试代码*/
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ThisIsLu (赞：0)

将区间按照左端点排序，问题就转化成前面有哪些右端点大于等于新加入的区间的左端点。

显然可以离散化后用树状数组计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6;
int c[N*2+5];
int lowbit(int x){
    return x&(-x);
}
struct line{
    int l,r;
    friend bool operator<(line x,line y){
        if(x.l==y.l) return x.r>y.r;
        return x.l<y.l;
    }
} p[N+5];
struct node{
    int x,id,op;
    friend bool operator<(node x,node y){
        return x.x<y.x;
    }
} b[(N<<1)+5];
int n;
int cnt;
void init(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].l>>p[i].r;
    }
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++){
        b[2*i-1].x=p[i].l;
        b[2*i-1].id=i;
        b[2*i-1].op=0;
        b[2*i].x=p[i].r;
        b[2*i].id=i;
        b[2*i].op=1;
    }
    sort(b+1,b+2*n+1);
    cnt=0;
    int last=-1;
    for(int i=1;i<=2*n;i++){
        if(b[i].x!=last){
            cnt++;
            last=b[i].x;
        }
        if(b[i].op==0) p[b[i].id].l=cnt;
        else p[b[i].id].r=cnt;
    }
}
void update(int x,int k){
    while(x<=cnt){
        c[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x){
    int res=0;
    while(x){
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}
int main(){
    init();
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=i-1-query(p[i].l-1);
        update(p[i].r,1);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 按照**左端点进行从小到大排序**，这样找到当前 $R_{i}$ 最多能超过第 $k$ 个 $L_{k}$，用 $ans$ 加上 $k-i$ 即可。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define _for(i,a,b) for(register int i=(a);i>=(b);i--)

const int N=500010;

int n;
int L[N],R[N];
int ans,k;
struct node{
	int l,r;
}a[N];
bool cmp(node x,node y){
	return x.l<y.l;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	rep(i,1,n) cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);
	rep(i,1,n){
		L[i]=a[i].l,R[i]=a[i].r;
	}
//	rep(i,1,n){
//		cout<<L[i]<<" "<<R[i]<<"\n";
//	}
	rep(i,1,n-1){
		k=upper_bound(L+1,L+n+1,R[i])-L-1;
		ans+=(k-i);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
将给定 $n$ 个区间按左端点和右端点排序，把所有端点离散化。对于区间 $[l_i, r_i]$，查询在权值线段树中大于等于 $l_i$ 的区间个数，然后把 $r_i$ 加入权值线段树中。因为在排序的这一步已经保证当前区间的左端点不会小于之前所有区间左端点，所以查询之前区间中右端点大于等于 $l_i$ 的区间个数，就是和当前区间相交，查询一步用权值线段树做。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
using namespace std;
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rep(i,j,k) for(int i=j;i>=k;i--)
#define ls(c) c<<1
#define rs(c) c<<1|1
#define int long long
#define lowbit(x) ((x)&(-x))
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x){
    x<0?x=-x,putchar('-'):0;
    static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
}
inline char read(char &ch){return ch=getchar();}
inline char write(const char &ch){return putchar(ch);}
template<typename type,typename ...T>
inline void read(type &x,T&...y){read(x),read(y...);}
template<typename type,typename ...T>
inline void write(type x,T...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
const int N=5e6+5,Mod=1e9+7;
int n,lsh[N],tot,ans;
struct node{
    int x,y;
}a[N];
bool cmp(node A,node B){
    if(A.x!=B.x) return A.x<B.x;
    else return A.y<B.y;
}
struct seg{
	int l,r,Max,add,sum;
}t[N<<2];
inline void push_up(int c){
	t[c].Max=max(t[ls(c)].Max,t[rs(c)].Max); 
    t[c].sum=t[ls(c)].sum+t[rs(c)].sum;
}
inline void push_down(int c){
	if(t[c].add){
		t[ls(c)].add+=t[c].add;
		t[rs(c)].add+=t[c].add;
		t[ls(c)].Max+=t[c].add;
		t[rs(c)].Max+=t[c].add;
		t[c].add=0;
		return;
	}
}
inline void build(int c,int l,int r){
	t[c].l=l;t[c].r=r;t[c].Max=0;t[c].add=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls(c),l,mid);
	build(rs(c),mid+1,r);
	push_up(c);return;
}
inline void update(int c,int l,int r,int k){
	if(l<=t[c].l&&r>=t[c].r){
		t[c].Max+=k;t[c].add+=k;
        t[c].sum+=k;
		return;
	}push_down(c);int mid=(t[c].l+t[c].r)>>1;
	if(l<=mid) update(ls(c),l,r,k);
	if(r>mid) update(rs(c),l,r,k);
	push_up(c);return;
}
int query(int c,int l,int r){
	if(l<=t[c].l&&r>=t[c].r) return t[c].sum;
	push_down(c);int mid=(t[c].l+t[c].r)>>1,res=0;
	if(l<=mid) res+=query(ls(c),l,r);
	if(r>mid) res+=query(rs(c),l,r);
	return res;
}inline void change(int c,int l,int r,int k){
	if(l<=t[c].l&&r>=t[c].r){
		t[c].Max=k;t[c].add=0;
		return;
	}push_down(c);int mid=(t[c].l+t[c].r)>>1;
	if(l<=mid) change(ls(c),l,r,k);
	if(r>mid) change(rs(c),l,r,k);
	push_up(c);return;
}
signed main(){
	read(n);vector<int> v;
    For(i,1,n){
        read(a[i].x,a[i].y);
        v.push_back(a[i].x);v.push_back(a[i].y);
    }sort(a+1,a+n+1,cmp);v.push_back(Mod);
    sort(v.begin(),v.end());
    int l=unique(v.begin(),v.end())-v.begin();
    For(i,1,n) a[i].x=lower_bound(v.begin(),v.end(),a[i].x)-v.begin()+1,a[i].y=lower_bound(v.begin(),v.end(),a[i].y)-v.begin()+1;
    build(1,1,v.size());
    For(i,1,n){
        int c=query(1,a[i].x,v.size());
        ans+=c;
        update(1,a[i].y,a[i].y,1);
    }
    write(ans);
	return 0;
}
```

---

## 作者：huangzhixia (赞：0)

[**场记**](https://www.luogu.com.cn/article/grncdeld)观赏效果更佳。

----

开始一眼**分治**！但我写到搜的时候直接卡住不会写了。然后认定是**分治**，卡住不会了。

后来想想了，这是**二分**。

可能说是单调性比较难找，我们需要把所有的 $l_i$ 和 $r_i$ 都从小到大排序。

然后去二分，我写的 ```lower_bound```，每次将排完序的数组 $a$ 二分，每次二分出来的结果要**减去** $a$。

之后就简单了，二分出结果，输出就可以了，我代码还算长度，有些巨佬写的很少。

直接给提交记录吧，[Link](https://atcoder.jp/contests/abc355/submissions/53883734)。

你以为这道题就完了？首先不开 ```long long``` 见祖宗，其次注意数组大小，$a$ 数组是 $5 \times 10^5$ 的两倍！我因为这个 RE 了一次，警钟敲烂。

---

## 作者：Breath_of_the_Wild (赞：0)

~~感觉这次 abc_d 水了。~~

题意：给你 $n$ 个区间，求相交的区间个数。

考虑使用堆（小根堆）维护 $A_i$ 右端点。先将 $A$ 按左端点升序，相等则右端点升序排序。

于是，每次先把右端点小于 $A_i$ 的左端点的区间从小根堆里扔掉，直到有大于等于 $A_i$ 左端点的。扔完之后，就给答案加上当前堆中的元素个数。最后，把 $A_i$ 右端点放入小根堆中。

核心代码：
```cpp
for(int i=1;i<=n;i++){
	while(!pq.empty()&&a[i].l>pq.top()) pq.pop();
	ans+=pq.size();
	pq.push(a[i].r);
}
```

---

