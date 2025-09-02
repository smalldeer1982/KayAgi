# Banquet Preparations 2

## 题目描述

The chef has cooked $ n $ dishes yet again: the $ i $ -th dish consists of $ a_i $ grams of fish and $ b_i $ grams of meat.

Banquet organizers consider two dishes $ i $ and $ j $ equal if $ a_i=a_j $ and $ b_i=b_j $ at the same time.

The banquet organizers estimate the variety of $ n $ dishes as follows. The variety of a set of dishes is equal to the number of different dishes in it. The less variety is, the better.

In order to reduce the variety, a taster was invited. He will eat exactly $ m_i $ grams of food from each dish. For each dish, the taster determines separately how much fish and how much meat he will eat. The only condition is that he will eat exactly $ m_i $ grams of the $ i $ -th dish in total.

Determine how much of what type of food the taster should eat from each dish so that the value of variety is the minimum possible. If there are several correct answers, you may output any of them.

## 样例 #1

### 输入

```
5

3
10 10 2
9 9 0
10 9 1

2
3 4 1
5 1 2

3
7 2 5
6 5 4
5 5 6

1
13 42 50

5
5 7 12
3 1 4
7 3 7
0 0 0
4 1 5```

### 输出

```
1
1 1
0 0
1 0
2
0 1
1 1
2
3 2
0 4
1 5
1
8 42
2
5 7
3 1
4 3
0 0
4 1```

# 题解

## 作者：jdsb (赞：4)

## 分析
- 首先显然只有 $a_i+b_i-m_i$ 相同的菜才有可能最后相同，所以先将 $a_i+b_i-m_i$ 相同的菜分到一组，然后再考虑组内的划分。

- 对于第 $i$ 道菜，我们设最后它的 $a_i$ 变成了 $x_i$，这个 $x_i$ 的取值一定是一段连续的区间，设这段区间为 $[l_i,r_i]$，那么有 $l_i=\max(0,a_i-m_i),r_i=a_i-\max(0,m_i-b_i)$。

- 若对于每道菜都求出 $l_i$，$r_i$，则两道菜 $i$， $j$ 最后可能相同的充要条件就是 $i$ 和 $j$ 在同一组，并且 $[l_i,r_i] \cap[l_j,r_j] \not= \varnothing$。

- 那我们就可以将问题转化为在数轴上有若干条线段，我们要在数轴上放最少数量的点，满足每条线段上至少放一个点。
- 对于这个问题我们可以使用贪心，我们将线段按照右端点从小到大排序，若右端点相同则按照左端点从小到大排序。对于最左侧的线段，我们必须在上面放一个点，那我们可以贪心的考虑将这个点放在最右侧，这样一定是最优的，那么包含这个点的线段最后都是相同的，并且这个点就是这些线段的最后取值，我们将这些线段删除，重复上述操作，即可得到答案。

## 代码
```cpp
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=2e5+5;
struct node{
	int x,y,m,id,s,l,r;
}a[N];
inline int cmp(const node x,const node y){
	if(x.s^y.s) return x.s<y.s;
	if(x.r^y.r) return x.r<y.r;
	return x.l<y.l;
}
inline int cmp2(const node x,const node y) { return x.id<y.id; }
int n,ans[N];
void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].m=read();
		a[i].id=i;
		a[i].s=a[i].x+a[i].y-a[i].m;
		a[i].l=max(0,a[i].x-a[i].m);
		a[i].r=a[i].x-max(0,a[i].m-a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	int tot=0;
	for(int l=1;l<=n;l++){
		int r=l;
		while(r+1<=n&&a[r+1].s==a[l].s) r++;
		for(int i=l;i<=r;i++){
			int j=i;
			while(j+1<=r&&a[j+1].l<=a[i].r){
				j++;
				ans[a[j].id]=a[i].r;
			}
			ans[a[i].id]=a[i].r;
			tot++;
			i=j;
		}
		l=r;
	}
	sort(a+1,a+n+1,cmp2);
	printf("%d\n",tot);
	for(int i=1;i<=n;i++){
		int t=a[i].x-ans[i];
		printf("%d %d\n",t,a[i].m-t);
	}
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```


---

## 作者：二gou子 (赞：1)

## Sol

首先有一个很显然的观察：如果两道菜 $i,j$ 最后能变成相同种类的菜，一定满足 $a[i]+b[i]-m[i]=a[j]+b[j]-m[j]$ 。所以我们按照 $a[i]+b[i]-m[i]$ 分组，在每组内分别处理，最后把答案合并起来即可。

考虑对于处理之后的 $a[i]$ 的范围是多少，由于在一组内 $a[i]+b[i]-m[i]$ 都相等，所以显然如果操作后的 $a[i]=a[j]$ ，$i,j$ 这两道菜就肯定是同一种类了。显然 $a[i]$ 最小的情况就是从 $a[i]$ 吃掉 $m[i]$ ，所以 $a[i]_{min}=max(0,a[i]-m[i])$；$a[i]$ 最大的情况就是从 $b[i]$ 吃掉 $m[i]$ ，所以 $a[i]_{max}=a[i]+min(0,b[i]-m[i])$ ，这两个式子手玩一下就能理解。

那么现在我们将每道菜 $a[i]$ 的范围看成一条线段，我们的问题就转化为了如下问题：选出最少的点数覆盖所有线段，求最小点数，并输出每个点的坐标（用于输出方案）。则我们有如下贪心策略：每次在还没有覆盖到的线段中选右端点最靠左的那条线段的右端点，然后标记所有能覆盖的线段，重复此步骤直到所有线段都被覆盖。

这样的正确性很轻松就可以证明：因为第一条没有被覆盖的线段必须要有点覆盖，而如果要尽可能使挑选的这个点也能覆盖后面的点，选在右端点显然是最优的。

所以我们对于所有线段排序之后从前往后扫一遍就行了，每次选到的点就是被覆盖到的线段的 $a[i]$ 的取值，根据这个可以算出 $a[i],b[i]$ 各减少了多少，也就是合法方案了。总时间复杂度 $O(n\log n)$ 

这题的代码不难写，所以就不放了。

---

## 作者：TLEWA (赞：0)

我们不好判断任意两组 $a_i.b_i,c_i$ 能否位置相同，考虑将问题规模缩小，发现 $a_i+b_i-m_i$ 不同的两组数显然不可能构造成相同，于是我们按照 $a_i+b_i-m_i$ 划分，此时我们发现在同一组内的两组数的 $a_i^{'} $ 和 $b_i^{'}$ 只要有一个相等另一个也相等（因为 $a_i^{'} + b_i^{'} = a_i+b_i-m_i$，而同组内 $a_i+b_i-m_i$ 的值相等）。也就是说我们只需要构造出 $a_i^{'}$ 和 $a_j^{'}$ 中的任意一个相等就可满足条件，笔者在这里考虑构造 $a_i^{'}$ 相同， $b_i^{'}$ 同理。

发现  $a_i^{'}$  的可能取值是一个区间，简单计算可以得出取值范围应该为 $\left[\max(a_i-m_i,0),a_i-\max(m_i-b_i,0) \right]$，这个时候其实就是一个非常经典的问题了，我们把右端点作为第一关键字，左端点作为第二关键字排序，然后贪心分组，这道题就做完了。

注意 $a_i$ 和 $b_i$ 的取值最高可以到 $10^{6}$，同时要求输出具体方案，在清零多测数据和枚举 $a_i + b_i - m_i$ 时需要采取一定的特殊手段（比如把输入数据离线）。

AC 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=200005,A=2000005,INF=1e8;

int T;
int n;

vector<pair<int,int> > vec[A],que[A];
set<int> input_list;

struct Node {
	int a,b,m;
}inputs[N];

int main() {
	cin >> T;
	while(T--) {
		cin >> n;
		
		input_list.clear();
		
		int a,b,m;
		for(int i=1;i<=n;++i) {
			cin >> a >> b >> m;
			if(input_list.find(a+b-m)==input_list.end()) {
				vec[a+b-m].clear();que[a+b-m].clear();
			}
			vec[a+b-m].push_back(make_pair(a-max(0,m-b),max(a-m,0)));
			input_list.insert(a+b-m);
			inputs[i]={a,b,m};
		}
		
		int ans=0,rmax=0;
		
		for(auto now:input_list) {
			sort(vec[now].begin(),vec[now].end());
			
			rmax=vec[now][0].first,ans++;
			for(auto u:vec[now]) {
				if(u.second>rmax) {
					que[now].push_back(make_pair(u.first-1,rmax));
					rmax=u.first,ans++;
				}
			}
			que[now].push_back(make_pair(INF,rmax));
		}
		
		cout << ans << endl;
		
		for(int i=1;i<=n;++i) {
			a=inputs[i].a,b=inputs[i].b,m=inputs[i].m;
			auto p=*(upper_bound(que[a+b-m].begin(),que[a+b-m].end(),make_pair(a-max(0,m-b),-INF)));
			
			cout << a-p.second << ' ' << m-(a-p.second) << endl;
		}
	}
	return 0;
}

```


---

## 作者：SegTree (赞：0)

### 题意

$n$ 个三元组 $(A_i,B_i,m_i)$。你需要构造 $x_i$ 和 $y_i$ 使 $x_i+y_i=m_i$，令 $a_i\gets A_i-x_i,b_i\gets B_i-y_i$ 且 $a_i,b_i\ge 0$ 满足不同的二元组 $(a_i,b_i)$ 的数量最小。

### 题解

对于每个三元组 $(A_i,B_i,m_i)$，我们可以求出操作后 $a_i$ 和 $b_i$ 的范围。记 $s_i=a_i+b_i-m_i$，则有 $a_i\ge 0,a_i\le A_i,s-a_i\ge 0,s-a_i\le B_i$。即可解出 $\max(0,s_i-B_i)\le a_i\le \min(s_i,A_i)$。

另外我们还考虑到这样一件事情。如果 $a_i=a_j,b_i=b_j$ 则有 $a_i+b_i=a_j+b_j$，可以得出 $A_i+B_i-m_i=A_j+B_j-m_j$。也就是说，对于每个 $i$ 满足 $A_i+B_i-m_i$ 分成一组，每个组有若干个区间确定了 $a_i$ 的范围，让你选最少数量的 $a_i$ 属于所有的区间。因为 $a_i$ 相等并且满足被分在一组那么 $b_i$ 也相等。

现在，我们需要解决下面这个问题：

+ 给你若干个区间 $[l_i,r_i]$，求最少点让每个区间都被点覆盖。

不难考虑按照 $r$ 端点排序然后扫一遍，如果一个区间内没有被点覆盖过，那么就用一个点覆盖在它的结尾就行。可以用一个 `set` 维护覆盖的点的位置。

求出这个点就是 $a_i$，对应的算出 $x_i$ 和 $y_i$ 即可。时间复杂度 $\mathcal{O}(n\log n)$，可通过本题。

[CF Record](https://codeforces.com/contest/1607/submission/219897424)。

---

## 作者：GaryH (赞：0)

# CF1607H 题解

### Nov/18/2021. Upd:修改了一个笔误
### Nov/25/2021. Upd:修改了第二个笔误

**题意**：给 $n$ 个二元组和一个数组 $m[1...n]$，第 $i$ 个二元组形如 $(a_i, b_i)$。

需要你构造出 $n$ 个新的二元组，要求是：

第 $i$ 个新二元组 $(a'_i, b'_i)$ 需要满足以下条件：$a'_i \leq a_i, b'_i \leq b_i, a'_i + b'_i = a_i + b_i - m_i$。

请最小化新的 $n$ 个二元组中的本质不同二元组个数并给出方案，

其中两个二元组 $(a, b) , (c, d)$ 本质不同，当且仅当 $a \neq c$ 或 $b \neq d$。

**做法**：

首先，我们定义 $val_i = a_i + b_i - m_i$，则有 $val_i = a'_i + b'_i$，

故若 $val_i \neq val_j$，则 $(a'_i,b'_i)$ 与 $(a'_j, b'_j)$ 必然本质不同。

那么，我们将原来的 $n$ 个二元组按 $val$ 值分类后，不同类的两个元素必本质不同，

而对于属于同一类的两个二元组 $(a_i, b_i), (a_j, b_j)$，想要使这两者对应的新二元组本质相同，

我们只需要让 $a'_i = a'_j$ 即可， 因为若 $val_i = val_j$，则 $a'_i + b'_i = a'_j + b'_j$。

我们同时可以发现，对某个二元组 $(a_i, b_i)$，由它构造出的新二元组 $(a'_i, b'_i)$ 必满足以下条件：

- $a'_i \leq a_i$ 

- $a'_i \leq val_i$ 
- $a'_i \geq 0$
- $a'_i \geq a'_i - m_i$
- $a'_i + b'_i = val_i$

以上五个条件是构造出的新二元组 $(a'_i, b'_i)$ 合法的充要条件。

我们将上面五个条件合并，即可得出：

 $a_i \in [\max(0,a_i - m_i), \min(a_i, val_i)]$，且 $a'_i + b'_i = val_i$。

此时我们发现，当 $a'_i$ 固定后， $b'_i$ 也跟着固定，且所有满足条件的 $a'_i$ 构成一段区间。

此时，我们可以尝试从一种不同的角度来刻画这个问题：

我们构造一条数轴，数轴上有若干个点，我们可以在一定范围内挪动这个点，

而我们需要的，是让这些点尽可能的重合，并使最后不在同一个位置的点的数量最少。

我们发现，这些点的初始位置无关紧要，重要的只有其可以到达的范围。

同时，“使最后不在同一个位置的点的数量最少” 这个条件，可以用一种更简洁的方式描述：

我们直接在数轴上选取若干个位置，作为初始的每个点最后到达的位置集合，

那么我们需要做到的，就是让原先的每个点，在最后都有一个 "落脚点" 在位置集合中。

那么，我们就可以将原问题转化成以下问题：

给定 $n$ 段在数轴上的区间，要求放置若干个点，使得每段区间内都包含至少一个点，

请最小化放置的点数并给出方案。

这就是一个典型的区间覆盖问题了，我们可以用贪心来解决。

首先，对于两个区间 $[l_1, r_1], [l_2, r_2]$，若存在 $l_1 \leq l_2, r_1 \geq r_2$，即 $[l_2, r_2]\in [l_1, r_1]$，

则当区间 $[l_2, r_2]$ 中包含了至少一个点，那么区间 $[l_1, r_1]$ 也至少包含了一个点，

此时同时考虑区间 $[l_1, r_1]$ 和 $ [l_2, r_2]$ 是多余的，我们就可以删除区间 $[l_1, r_1]$。

故对于两个存在包含关系的区间，我们可以删除更大的那个。

于是，对剩下的区间按左端点升序排序后，其右端点必单调递增。

此时，我们只需要贪心的放点即可，具体来说，就是：

遍历每个区间并记录当前放置的最靠右的点，若该点落在当前区间内就不管，

否则新放一个点在当前区间的右端点，并更新当前放置的最靠右的点的位置。

这个的正确性可以用扰动法证明，就不在此赘述了。

复杂度瓶颈在于排序，是 $O(n \log n)$ 的。

**代码**：

```
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

const int N (2e5 + 10);
int n, tot, x[N], rx[N], ry[N];

struct Node { int a, b, m, s, id; } d[N];
struct Line {int l, r, v, id;} a[N];

inline bool cmp (Node u, Node v) { return u.s < v.s; }
inline bool cmp2 (Line u, Line v) {
	if (u.r ^ v.r) return u.r < v.r;
	return u.l < v.l;
}
 
inline int solve (int st, int en) {
	int ans = 0; tot = 0;
	rep (i, st, en) a[++tot] = (Line) 
	  {max(0ll, d[i].a - d[i].m), min(d[i].a, d[i].s)},
	  a[tot].v = d[i].a, a[tot].id = i;
	sort (a + 1, a + tot + 1, cmp2); int pos = -1e18;
	rep (i, 1, tot) {
		if (pos < a[i].l) ans++, pos = a[i].r;
		x[a[i].id] = a[i].v - pos;
	} return ans;
}
 
inline void work () {
	n = read();
	rep (i, 1, n) {
		x[i] = rx[i] = ry[i] = 0;
		d[i].a = read(), d[i].b = read(), d[i].m = read();
		d[i].s = d[i].a + d[i].b - d[i].m, d[i].id = i;
	}
	sort (d + 1, d + n + 1, cmp); int l = 0, r = 0, ans = 0;
	while (r <= n) {
		l = ++r; if (r > n) break ;
		while (r + 1 <= n && d[r + 1].s == d[l].s) ++r;
		ans += solve (l, r);
	}
	cout << ans << endl;
	rep (i, 1, n) rx[d[i].id] = x[i], ry[d[i].id] = d[i].m - x[i];
	rep (i, 1, n) cout << rx[i] << ' ' << ry[i] << endl;
}
 
signed main() {
	int tasks = read();
	while (tasks--) work();
	return 0;
}
```



---

## 作者：Summer_Night_Sky (赞：0)

## $ Translation $
$t$ 组数据，每组数据输入 $n$ 行，每行输入三个数 $a_i, b_i,m_i(1≤i≤n)$ ，表示从一对数 $a_i,b_i$ 中总共减去 $m_i$ 的值，使两者变成 $a_i^{'},b_i^{'} $ 。若满足

$$a_i^{'}=a_j^{'},b_i^{'}=b_j^{'}(1≤i≤n,1≤j≤n,i≠j)$$

则把 $i$ 和 $j$ 归为一组。

问最少要把它们分成多少组？

$1≤t≤10^{4},1≤n≤2⋅10^{5}$

## $ Solution $
两对数 $i$ 和 $j$ 能归为一组的一个必要条件是这两对数经过处理之后它们的和相等，即

$$a_i+b_i-m_i=a_j+b_j-m_j$$

也就是

$$a_i^{'}+b_i^{'}=a_j^{'}+b_j^{'}$$

然后对于每一个 $i$ ，记录 $a_i^{'}$ 可以达到的最大值和最小值，最后做线段覆盖即可。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define maxn 200005
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
struct point
{
	int a,b,m,id,fa_l,fa_r,fsum;
}p[maxn];
struct answer
{
	int a,b;
}ans[maxn];
int read()
{
	char c=getchar(); int x=0;
	while(c<48) c=getchar();
	while(c>47) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
bool cmp(const point &a,const point &b)
{
	if(a.fsum==b.fsum)
	{
		if(a.fa_r==b.fa_r) return a.fa_l<b.fa_l;
		return a.fa_r<b.fa_r;
	}
	return a.fsum<b.fsum;
}
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),cnt=0;
		for(int i=1;i<=n;i++)
		{
			p[i].a=read(),p[i].b=read(),p[i].m=read();
			p[i].fsum=p[i].a+p[i].b-p[i].m;
			p[i].fa_l=max(0,p[i].a-p[i].m);
			p[i].fa_r=p[i].a+min(0,p[i].b-p[i].m);
			p[i].id=i;
		}
		sort(p+1,p+n+1,cmp);
		int now=-1;
		for(int i=1;i<=n;i++)
		{
			if(p[i].fsum!=p[i-1].fsum||p[i].fa_l>now)
			{
				now=p[i].fa_r,cnt++;
				ans[p[i].id].a=p[i].a-now;
				ans[p[i].id].b=p[i].m-ans[p[i].id].a;
				continue;
			}
			ans[p[i].id].a=p[i].a-now;
			ans[p[i].id].b=p[i].m-ans[p[i].id].a;
		}
		printf("%d\n",cnt);
		for(int i=1;i<=n;i++) printf("%d %d\n",ans[i].a,ans[i].b);
	}
	return 0;
}
```


---

