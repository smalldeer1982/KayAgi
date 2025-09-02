# Rectangle Shrinking

## 题目描述

你有一个长为 $10^9$，宽为 $2$ 的矩形网格。

起初，网格上有 $n$ 个矩形，这些矩形的边沿着单元格的边。对于第 $i$ 个矩形，左上角为 $(u_i,l_i)$，右下角为 $(d_i,r_i)$。这些矩形两两之间可能相交、重合或包含。

对于每个矩形，你可以进行以下操作一种或者不操作：

- 删除这个矩形。

- 用一个非空的子矩形来替换它。

要求：在完成所有操作后，剩下的所有矩形中不允许任意两个矩形有交。

求剩余矩形覆盖的总面积最大为多少，以及达到最大的任意一种方案。

$1 \le u_i \le d_i \le 2$，$1 \le l_i \le r_i \le 10^9$，$\sum n \le 2 \times 10^5$。

## 样例 #1

### 输入

```
8
5
1 2 2 4
2 4 2 8
1 4 2 7
1 2 1 2
1 9 1 10
2
1 1 1 10
1 5 1 15
2
1 1 1 10
1 1 1 10
5
1 3 1 7
1 3 1 8
1 1 1 4
1 2 1 7
1 10 1 11
2
1 1 2 10
1 5 1 8
2
1 5 2 10
1 2 1 7
2
1 5 2 10
2 2 2 15
5
2 6 2 7
1 4 2 5
1 5 1 9
1 7 2 10
1 2 1 6```

### 输出

```
15
1 2 2 4
2 5 2 8
1 5 1 7
0 0 0 0
1 9 1 10
15
1 1 1 10
1 11 1 15
10
1 1 1 10
0 0 0 0
10
0 0 0 0
1 8 1 8
1 1 1 4
1 5 1 7
1 10 1 11
20
1 1 2 10
0 0 0 0
15
1 5 2 10
1 2 1 4
20
1 5 1 10
2 2 2 15
16
2 6 2 6
2 4 2 5
0 0 0 0
1 7 2 10
1 2 1 6```

# 题解

## 作者：honglan0301 (赞：3)

感谢这道 "trash problem" 把我送到了 rank 200-。

## 题目分析

不难猜到最优解一定就是最初矩形的并集，那么我们尝试来构造。

我们考虑先将矩形按左端点从小到大排序，并用两个单调队列来记录上下两行中被前面矩形所覆盖住的范围。接下来我们来分类讨论如何处理当前矩形。

1.当前矩形被之前的矩形所完全覆盖。如下图所示（以下蓝色矩形均表示当前矩形，黑色矩形表示之前的矩形）这时显然直接把它删掉就行了。
![](https://cdn.luogu.com.cn/upload/image_hosting/or95bhd7.png)

2.当前矩形仅有一行未被完全覆盖。如下图所示，此时把它更改为未被覆盖的部分并加入该行的单调队列。
![](https://cdn.luogu.com.cn/upload/image_hosting/pvo4ngu1.png)

3.当前矩形在两行中都未被完全覆盖。如下图所示，此时把单调队列内的所有矩形的右边界置于当前矩形左边界的左侧（若不合法则删掉），并清空单调队列，仅加入当前矩形即可。当前矩形的范围不需更改。
![](https://cdn.luogu.com.cn/upload/image_hosting/6a2zb3r0.png)

容易发现有且仅有以上三种情况，故可以通过本题。

## 代码
[赛时代码](https://codeforces.com/contest/1782/submission/189338601)。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
#define int long long

int t,n,u,v,w,s,b[400005],m;
deque <int> Q[3];

struct jx
{
	int l,r,u,d,bh;
}jx[200005];
bool cmp(struct jx x,struct jx y)
{
	return x.l!=y.l?x.l<y.l:x.r>y.r;
}
bool cmp2(struct jx x,struct jx y)
{
	return x.bh<y.bh;
}

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n; while(!Q[1].empty()) Q[1].pop_back(); while(!Q[2].empty()) Q[2].pop_back();
		for(int i=1;i<=n;i++)
		{
			cin>>jx[i].u>>jx[i].l>>jx[i].d>>jx[i].r; jx[i].bh=i;
		}
		sort(jx+1,jx+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			int nowl=jx[i].l;
			while(!Q[1].empty()&&jx[Q[1].back()].r<nowl) Q[1].pop_back();
			while(!Q[2].empty()&&jx[Q[2].back()].r<nowl) Q[2].pop_back();
			if(jx[i].u==jx[i].d)
			{
				if(!Q[jx[i].u].empty()&&jx[i].r<=jx[Q[jx[i].u].front()].r)
				{
					jx[i].l=jx[i].r=jx[i].u=jx[i].d=0;
				}
				else
				{
					if(!Q[jx[i].u].empty()) jx[i].l=jx[Q[jx[i].u].front()].r+1;
					Q[jx[i].u].push_front(i);
				}
			}
			else
			{
				if(!Q[1].empty()&&!Q[2].empty()&&jx[i].r<=jx[Q[1].front()].r&&jx[i].r<=jx[Q[2].front()].r)
				{
					jx[i].l=jx[i].r=jx[i].u=jx[i].d=0;
				}
				else if(!Q[1].empty()&&jx[i].r<=jx[Q[1].front()].r)
				{
					if(!Q[2].empty()) jx[i].l=jx[Q[2].front()].r+1;
					jx[i].u=jx[i].d;
					Q[2].push_front(i);
				}
				else if(!Q[2].empty()&&jx[i].r<=jx[Q[2].front()].r)
				{
					if(!Q[1].empty()) jx[i].l=jx[Q[1].front()].r+1;
					jx[i].d=jx[i].u;
					Q[1].push_front(i);
				}
				else
				{
					while(!Q[1].empty())
					{
						if(jx[Q[1].front()].l<jx[i].l)
						{
							jx[Q[1].front()].r=jx[i].l-1;
						}
						else
						{
							jx[Q[1].front()].r=jx[Q[1].front()].l=jx[Q[1].front()].u=jx[Q[1].front()].d=0;
						}
						Q[1].pop_front();
					}
					while(!Q[2].empty())
					{
						if(jx[Q[2].front()].l<jx[i].l)
						{
							jx[Q[2].front()].r=jx[i].l-1;
						}
						else
						{
							jx[Q[2].front()].r=jx[Q[2].front()].l=jx[Q[2].front()].u=jx[Q[2].front()].d=0;
						}
						Q[2].pop_front();
					}
					Q[1].push_front(i); Q[2].push_front(i);
				}
			}
		}
		sort(jx+1,jx+n+1,cmp2);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(jx[i].d==0) continue;
			ans+=(jx[i].d-jx[i].u+1)*(jx[i].r-jx[i].l+1);
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;i++)
		{
			cout<<jx[i].u<<" "<<jx[i].l<<" "<<jx[i].d<<" "<<jx[i].r<<endl;
		}
	}
}
```
写法好像有点麻烦。

---

## 作者：zac2010 (赞：2)

### 前言

终于过了。感觉我太菜了，这道题目做了将近 $4$ 个来小时，前面 $1.5$ 时，后面 $2.5$ 时（不过至少是独立做出来的）。

我的做法思维难度不怎么大，但是如果不注意封装函数的话那代码的长度会加大。

### 思路

首先，抓住特殊性质：只有 $2$ 行。

然后我们通过手推样例发现面积和是这些矩形面积的并。

因为我们考虑完全包含的情况那么里面一定是可以不要的，那么再经过思考发现其他矩形和他有相交的地方一定是边缘，必定有一个可以丢弃掉。

就比如说分类讨论可以解决：
1. 高一行的和高两行的的相交

	在高一行的里面去掉高一行的那个矩形与当前高两行的重复部分。
2. 两个高两行的相交

	任取一个删去相交部分即可。
3. 两个同一行的也是高一行的相交

	任取一个删去相交部分即可。

那么我们思考这道题的难点——方案。

你觉得按上面的方法能过吗？你的这个过程很可能要执行n这个级别的次数次甚至更多，而每次是 $O(n)$ 的，会不会超时想想就知道了。

一看就是构造题，我们要去用一种方法构造一种方案！！！

于是我们可以把高一行且同一行的重复部分先去掉，再把高两行的矩形之间的重复也去了，然后我们又分别处理两行，只是把高两行的也加入当前这行的矩形队列里。对于处理每一行，我们不难发现是高两行的矩形要优先保留，因为他的重叠部分如果去掉了，可能会对另外一行的贡献产生影响。如果还不清楚可以看图（蓝色为高两行的矩形，绿色为与其重叠的矩形，紫色为其他矩形）：
![](https://cdn.luogu.com.cn/upload/image_hosting/fvjmaxt5.png)

所以额外再记录一个答案数组即可。注意可以封装函数以缩短码量。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 2e5 + 10;
struct A{
	int u, l, d, r, i, t;
}a[N], b[N], c[N], ans[N]; 
int n, la, lb, lc, t; ll sum;
bool cmp(A x, A y){return (x.r == y.r)? x.l > y.l : x.r < y.r;}
int Dispose(int l, A d[], int typ = 3){
	vector<A> v;
	if(l) v.push_back(d[1]);
	L(i, 2, l){
		int id = (int)(v.size() - 1);
		for(; id >= 0; id--){
			if(d[i].l <= v[id].l){
				if(typ == 3) ans[v[id].i].u = 3;
				else if(typ == 2) ans[v[id].i].d--;
				else ans[v[id].i].u++;
				v.pop_back();
			}
			else break;
		}
		if(id >= 0 && d[i].l <= v[id].r){
			if(d[i].t == 3)
				ans[v[id].i].r = v[id].r = d[i].l - 1;
			else ans[d[i].i].l = d[i].l = v[id].r + 1;
		}
		if(d[i].i) v.push_back(d[i]);
	}
	t = 0; L(i, 0, (int)(v.size() - 1)) d[++t] = v[i];
	return t;
}
void Solve(){
	scanf("%d", &n);
	sum = la = lb = lc = 0;
	L(i, 1, n){
		int u, l, d, r;
		scanf("%d%d%d%d", &u, &l, &d, &r);
		ans[i] = {u, l, d, r, i};
		if(u == 1 && d == 1) a[++la] = {u, l, d, r, i, 1};
		else if(u == 2 && d == 2) b[++lb] = {u, l, d, r, i, 2};
		else c[++lc] = {u, l, d, r, i, 3};
	}
	sort(a + 1, a + la + 1, cmp);
	sort(b + 1, b + lb + 1, cmp);
	sort(c + 1, c + lc + 1, cmp);
	la = Dispose(la, a, 1);
	lb = Dispose(lb, b, 2);
	lc = Dispose(lc, c);
	L(i, 1, lc) a[la + i] = b[lb + i] = c[i];
	sort(a + 1, a + la + lc + 1, cmp);
	sort(b + 1, b + lb + lc + 1, cmp);
	int s = Dispose(la + lc, a, 1); s = Dispose(lb + lc, b, 2);
	L(i, 1, n){
		if(ans[i].u > ans[i].d || ans[i].l > ans[i].r){
			ans[i] = {}; continue;
		}
		sum += (ans[i].d - ans[i].u + 1) * (ans[i].r - ans[i].l + 1);
	}
	printf("%d\n", sum);
	L(i, 1, n)
		printf("%d %d %d %d\n", ans[i].u, ans[i].l, ans[i].d, ans[i].r);
}
int main(){
	int T; scanf("%d", &T);
	while(T--) Solve();
	return 0;
}
```

---

## 作者：migeater (赞：1)

## 一些表示

+ $S$：作为题目输入的矩形集合。
+ $\operatorname{area}(x)$：一个函数，接收一个矩形集合 $x$ 作为参数，返回值是 $x$ 中所有矩形的并集组成的图形。

## 本题解特点

+ 分类情况相对较少。
+ 实现上用了三个数组来表示和存储不重叠图形。在没搞什么特别优化的情况下，执行时间在当前数据集能排到前 2%，空间花费目测也是比较优秀的。
+ 代码有详细注释，不过要求一定的 C++ 语法知识。

## 题目分析

1. 猜测 $S$ 中所有矩形的并集的面积是能取到的。证明就是算法本身，类似数学归纳法。
2. $S$ 是无序的，不妨进行排序，可有效减少分类讨论的种类。在这题中，可按矩形所处列的最小值排，也可按矩形所处列的最大值排，后者简单心想了下发现要考虑的情况更多。
3. 不断往 $S$ 中添加新的矩形，然后在原先放置方法基础上，构造新的放置方法。
4. 模拟的具体写法。

## 构造放置方法

一开始创建一个空集合 $s$。

对 $S$ 排序后遍历矩形，假设当前遍历到矩形 $e$，$e$ 之前遍历过的矩形均已加入到 $s$ 中，未遍历的矩形则未加入 $s$ 中。

再引入一个能帮助分类讨论的循环不变式：若 $e$ 中包含 $\operatorname{area}(s)$ 中的点，则 $e$ 中位于该点正左侧（同一行，列数严格小于）的点均在 $\operatorname{area}(s)$ 中。不难发现它在我下面将要描述的算法过程中一直成立。

$e$ 加入 $s$ 具体有以下3种情况，不加入的情况不列出来（看代码实现，有的实现方式默认不加进去）：

1. 若 $e$ 的宽度为 1：
	+ 把 $e$ 缩小成未被 $\operatorname{area}(s)$ 覆盖的部分，加入 $s$ 中。
2. 若 $e$ 的宽度为 2：
	1. 若 $e$ 未被 $\operatorname{area}(s)$ 覆盖的部分只有一行：
		+ 把 $e$ 缩小成该未被覆盖的部分，加入 $\operatorname{area}(s)$ 中。
	2. 若 $e$ 未被 $\operatorname{area}(s)$ 覆盖的部分两行都有：
        + 则计划把 $e$ 完整的加入 $s$，为防止重叠，应该：
            + 被 $e$ 完全包含的矩形，直接删除；
            + 与 $e$ 部分重叠的矩形，只需要改变它们的右边界，使得它们不与 $e$ 重叠。
        + 然后再把 $e$ 加入 $s$。


## 模拟的具体实现

把题目要求的输出（若干矩形位置信息）分成三部分：用两个数组表示只占据一行的矩形，用一个数组表示占据两行的矩形，每个数组中矩形均从左至右排好序。

通过上面提及的循环不变式可知，只需要找到数组的最后一个元素就能找出 $e$ 未被覆盖的部分。

代码见 [CF](https://codeforces.com/contest/1782/submission/192044827)。

注意事项：计算矩形面积的时候，`rect(0,0,0,0)` 这种矩形面积应为 0。

## 时间复杂度

$O(n\log{n})$ 瓶颈在排序。

---

## 作者：yingkeqian9217 (赞：0)

提供一个不用脑子的做法。

注意到答案即为矩形的并，构造如下：先填宽为 1 的矩形，如果当前区间已被某一个矩形完全覆盖，就舍去当前矩形，否则直接区间覆盖，显然最终每个矩形为开始矩形的子矩形。

然后考虑宽为 2 的，同理，不过要对于上下两行判断是否被完全覆盖，选择合适的行并赋值。

注意到我们要维护一个区间赋值，区间查询颜色（是否都为同一种），可以离散化后使用并查集什么的，但是这里笔者使用了更方便的动态开点线段树直接维护。

统计答案，直接遍历整一棵树，因为保证每个颜色构成矩形，所以直接算左右端点（即最小、最大位置）即可。

时间复杂度 $O(n\log n)$ 或 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define maxn 210005
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define max(x,y) ((x)<(y)?(y):(x))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>0?(x):-(x))
#define sqr(x) ((x)*(x))
#define cub(x) ((x)*(x)*(x))
#define lg(x) ((x)>0?(int)(log2(x)):-1)
#define gc() getchar()
#define pc(x) putchar(x)
//#define int long long
using namespace std;
const double eps=1e-9;
const int inf=1e9+7,Inf=1e16+7,N=300000,Mod=998244353,Inv=(Mod+1)/2,V=10000;

int n;
struct rec{
	int sx,sy,ex,ey;
}a[maxn];
int cnt,sum;
pair<int,int>p[maxn];
struct node{
	int ls,rs,tg,sum;
	node(){
		ls=rs=0;
		tg=-1;
		sum=0;
	}
}s[maxn*150];
int add(int x,int y){
	if(x==-1||y==-1) return -1;
	return x==y?x:-1;
}
void pushdown(int x){
	if(s[x].tg==-1) return;
	if(!s[x].ls) s[x].ls=++cnt;
	if(!s[x].rs) s[x].rs=++cnt;
	s[s[x].ls].tg=s[s[x].ls].sum=s[x].tg;
	s[s[x].rs].tg=s[s[x].rs].sum=s[x].tg;
	s[x].tg=-1;
}
void pushup(int x){
	s[x].sum=add(s[s[x].ls].sum,s[s[x].rs].sum);
}
int update(int x,int l,int r,int sl,int sr,int k){
	if(!x) x=++cnt;
	if(sl<=l&&r<=sr) return s[x].tg=s[x].sum=k,x;
	int mid=l+r>>1;
	pushdown(x);
	if(sl<=mid) s[x].ls=update(s[x].ls,l,mid,sl,sr,k);
	if(mid<sr) s[x].rs=update(s[x].rs,mid+1,r,sl,sr,k);
	pushup(x);
	return x;
}
int query(int x,int l,int r,int sl,int sr){
	if(sl<=l&&r<=sr) return s[x].sum;
	int mid=l+r>>1,res=0;
	pushdown(x);
	if(sl<=mid&&mid<sr) return res=add(query(s[x].ls,l,mid,sl,sr),query(s[x].rs,mid+1,r,sl,sr));
	if(sl<=mid) res|=query(s[x].ls,l,mid,sl,sr);
	if(mid<sr) res|=query(s[x].rs,mid+1,r,sl,sr);
	return res;
}
void query(int x,int l,int r){
	if(s[x].tg!=-1){
		if(!s[x].tg) return;
		sum+=r-l+1;
		p[s[x].tg].fi=min(p[s[x].tg].fi,l);
		p[s[x].tg].se=max(p[s[x].tg].se,r);
		return;
	}
	int mid=l+r>>1;
	if(s[x].ls) query(s[x].ls,l,mid);
	if(s[x].rs) query(s[x].rs,mid+1,r);
}
int rt[2];
inline void solve(){
	sum=0;
	scanf("%d",&n);
	rt[0]=rt[1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&a[i].sx,&a[i].sy,&a[i].ex,&a[i].ey);
		if(a[i].sx==a[i].ex){
			if(query(rt[a[i].sx-1],1,inf,a[i].sy,a[i].ey)>0) continue;
			rt[a[i].sx-1]=update(rt[a[i].sx-1],1,inf,a[i].sy,a[i].ey,i);
		}
	}
	for(int i=1;i<=n;i++){
		p[i]=make_pair(inf,-inf);
		if(a[i].sx==a[i].ex) continue;
		if(query(rt[0],1,inf,a[i].sy,a[i].ey)>0) a[i].sx=2;
		else rt[0]=update(rt[0],1,inf,a[i].sy,a[i].ey,i);
		if(query(rt[1],1,inf,a[i].sy,a[i].ey)>0) a[i].ex=1;
		else rt[1]=update(rt[1],1,inf,a[i].sy,a[i].ey,i);
	}
	query(rt[0],1,inf),query(rt[1],1,inf);
	printf("%d\n",sum);
	for(int i=1;i<=n;i++){
		if(p[i].fi==inf||a[i].sx>a[i].ex) printf("0 0 0 0\n");
		else printf("%d %d %d %d\n",a[i].sx,p[i].fi,a[i].ex,p[i].se);
	}
}

signed main(){
//	freopen("test.out","w",stdout);
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//	srand(time(0));
	int T=1;
	scanf("%d",&T);
//	cin>>T;
//	init();
	while(T--) solve();
	return 0;
}
*/
```

---

## 作者：windflower (赞：0)

用的是很直接的一个思路，但是模拟略复杂。

首先题目给出的矩形可以分为三类：只在第一行的，只在第二行的和横跨两行的。我们考虑以下几种情况的处理：

1. 两个只在第一行的矩形重叠。任选一个修改边界使得两个矩形刚好相邻，面积不变。比如把范围在 $[l,r]$ 和 $[l',r'](l<l'<r<r')$ 的两个矩形改成两个范围在 $[l,r]$ 和 $[r+1,r']$ 的矩形。

2. 一行的矩形在横跨两行的矩形内部，直接删除一行的矩形。

3. 一行的矩形的一个端点在横跨两行的矩形内部，那么修改这个一行矩形的在横跨两行的矩形的内部的边界使它与横跨两行的矩形相邻，如一个横跨两行的 $[l,r]$ 与一个一行的 $[l',r'](l<l'<r<r')$ 可修改为一个两行的 $[l,r]$ 与一个一行的 $[r+1,r']$。

4. 若横跨两行的矩形的范围包含在了只在一行的矩形的范围内，那么直接把这个横跨两行的矩形修改为只在另一行的矩形。

通过以上操作，并不改变矩形整体的面积，并且可以消除所有的重叠部分。具体操作见代码注释（可能模拟用的不是最方便的写法）。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,u,d,l,r,cnta,cntb,cntc,cntea,cnteb,la,lb,lc,rc,squ;
struct T{
	int l,r,id;
	bool operator<(T a){
		return l==a.l?r<a.r:l<a.l;
	}
}a[200005],b[200005],c[200005],Exa[200005],exb[200005];
//a,b,c表示一开始读入后以及后续化简过程中留存的矩形，a表示只在第一行。 
//b表示只在第二行，c表示横跨两行。
//Exa与exb表示由原本是横跨两行的矩形转化而来的一行矩形。 
struct P{
	int u,l,d,r;
}ans[200005];
//用来处理情况1 
void simply(T* a,int &n){
	if(n==0)return;
	int l=0,r=1;
	while(r<n){
		while(r<n&&a[r].r<=a[l].r)r++;
		if(r==n)break;
		if(a[r].l<=a[l].r)a[r].l=a[l].r+1;
		l++;
		a[l]=a[r];
		r++;
	}
	n=l+1;
}
//用来处理情况2+3
void more_simply(T* a,int &n){
	if(n==0)return;
	lc=0;
	for(int i=0;i<n;i++){
		while(lc<cntc&&c[lc].r<a[i].l)lc++;
		if(lc==cntc)break;
		rc=lc;
		if(c[lc].l<=a[i].l)a[i].l=c[lc].r+1;
		while(rc<cntc&&c[rc].r<a[i].r)rc++;
		if(rc==cntc)break;
		if(c[rc].l<=a[i].r)a[i].r=c[rc].l-1;
	}
	int l=r=0;
	while(r<n){
		while(r<n&&a[r].l>a[r].r)r++;
		if(r==n)break;
		a[l]=a[r];
		l++;
		r++;
	}
	n=l;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cnta=cntb=cntc=cntea=cnteb=squ=0;
		for(int i=0;i<=n;i++)a[i]=b[i]=c[i]=Exa[i]=exb[i]={0,0,0};
		for(int i=0;i<=n;i++)ans[i]={0,0,0,0};
		for(int i=0;i<n;i++){
			cin>>u>>l>>d>>r;
			if(u!=d)c[cntc++]={l,r,i};
			else if(u==1)a[cnta++]={l,r,i};
			else b[cntb++]={l,r,i};
		}
		sort(a,a+cnta);
		sort(b,b+cntb);
		sort(c,c+cntc);
		//排序后，后续操作都可以在线性时间复杂度内完成。 
		simply(a,cnta);
		simply(b,cntb);
		simply(c,cntc);
		more_simply(a,cnta);
		more_simply(b,cntb);
		la=lb=0;
		//处理情况4
		//枚举每一个横跨两行的矩形。
		//在上述两次化简后，最多只有一个只在第一行的矩形和一个只在第二行的矩形
		//可能与这个横跨两行的矩形重叠
		//并且如果重叠，那么一行矩形的范围必定包含两行矩形的范围。 
		for(int i=0;i<cntc;i++){
			while(la<cnta&&a[la].r<c[i].r)la++;
			while(lb<cntb&&b[lb].r<c[i].r)lb++; 
			//两行的一行矩形均与两行矩形重叠，直接删除两行矩形。 
			if(la<cnta&&lb<cntb&&a[la].l<=c[i].l&&b[lb].l<=c[i].l)c[i].l=c[i].r=0;
			//第一行的矩形与两行矩形重叠，将两行矩形转化为第二行的矩形 
			else if(la<cnta&&a[la].l<=c[i].l){
				exb[cnteb++]=c[i];
				c[i].l=c[i].r=0;
			//同上 
			}else if(lb<cntb&&b[lb].l<=c[i].l){
				Exa[cntea++]=c[i];
				c[i].l=c[i].r=0;
			}
		}
		//将所有的答案整合起来,顺便计算面积。
		//整合过程中不会访问被删去的矩形，所以ans中被删去的矩形对应的就是ans的初始值{0,0,0,0}; 
		for(int i=0;i<cnta;i++)ans[a[i].id]={1,a[i].l,1,a[i].r},squ+=a[i].r-a[i].l+1;
		for(int i=0;i<cntb;i++)ans[b[i].id]={2,b[i].l,2,b[i].r},squ+=b[i].r-b[i].l+1;
		for(int i=0;i<cntc;i++)if(c[i].l)ans[c[i].id]={1,c[i].l,2,c[i].r},squ+=2*(c[i].r-c[i].l+1);
		for(int i=0;i<cntea;i++)ans[Exa[i].id]={1,Exa[i].l,1,Exa[i].r},squ+=Exa[i].r-Exa[i].l+1;
		for(int i=0;i<cnteb;i++)ans[exb[i].id]={2,exb[i].l,2,exb[i].r},squ+=exb[i].r-exb[i].l+1;
		cout<<squ<<endl;
		for(int i=0;i<n;i++)printf("%d %d %d %d\n",ans[i].u,ans[i].l,ans[i].d,ans[i].r);
	}
}
```


---

## 作者：vectorwyx (赞：0)

很独特的一道题目。不难看出最优的面积就是这些矩形的面积并，现在就变成了在并集不变的前提下调整矩形使得它们互不相交。可行的方案与思路有很多，但是并不是所有的思路都能导向简洁的做法。以下称占据上下两行的矩形为大矩形，只占据了一行的矩形为线段。

首先这东西可以离散化，因为收缩后有意义的边界只有 $l_i-1,l_i,r_i,r_i+1$。

### 解法一（赛时思路）

从左往右考虑。找到最靠左的非空格子，分两种情况考虑：

* 如果这一格子上有一个大矩形 $[l,r]$，直接选定这个矩形，将涉及到的其他矩形的左边界向右收缩至 $r+1$（当然，会有一些矩形因此而消失）。然后递归进子问题。
* 否则，找出以这个格子为起点且长度最长的线段，看看它的右端点是否被大矩形盖住了。如果是的话就把右边界收缩至最近的没有被大矩形覆盖的位置。然后选定这条线段，把涉及到的线段的左边界收缩，而对于涉及到的大矩形，让它们收缩成一条线段。由于特殊处理了右端点被大矩形覆盖的情况，这样不会把任何矩形切成不合法的形状。于是递归进子问题。

在这个过程中，最靠左的非空格子是单调递增的。于是可以从左往右扫，用线段树维护所需要的操作。选定矩形会让其他矩形收缩，这不太好维护，但是我们可以先确定选定矩形的顺序，然后倒序加入矩形依次覆盖。至于 把右边界收缩至最近的没有被大矩形覆盖的位置，这是连通性相关的结构，可以用并查集维护线段之间的连通块然后预处理出来。总复杂度大概是 $O(n\log n)$，但是特别难写。还有很多古怪的细节。

[code](https://codeforces.com/problemset/submission/1781/189716583)。注意这里偷工减料了一下，把右边界收缩至最近的没有被大矩形覆盖的位置 是暴力搞的，同时也没离散化，但是数据没卡。

### 解法二（赛后想到的）

两行的比较复杂，而如果只有一行就很容易调整成互不相交的状态。这启发我们将两行的问题降维变成一行的问题考虑。

大矩形优先级看起来比较高，先把它们调整成互不相交的形态。然后对于每个大矩形，分别去看它的上半部分和下半部分是否能被线段完全覆盖：

* 如果均能被线段完全覆盖，则抹除这个大矩形。
* 如果有且仅有一行的部分被线段完全覆盖，则把它调整成另一行上的线段。
* 如果两部分均不能被线段完全覆盖，则钦定这个大矩形不收缩，为此会对两行上的线段产生一些影响。这种影响可以直接写成前缀 $r$ 取 $\min$ 和后缀 $l$ 取 $\max$ 的形式，由于大矩形互不相交，这一影响可以在讨论结束后统一处理出来。

这一过程结束后，上下两行变为独立的两行，分别调整即可。复杂度瓶颈在于离散化。如果使用基数排序则复杂度为线性。

[code](https://codeforces.com/problemset/submission/1781/189794598)。



---

