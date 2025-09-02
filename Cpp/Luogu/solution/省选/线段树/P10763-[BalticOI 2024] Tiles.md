# [BalticOI 2024] Tiles

## 题目背景

翻译自 [BalticOI 2024 Day2 T2](https://boi2024.lmio.lt/tasks/d2-tiles-statement.pdf)。

## 题目描述

有一个存在 $N$ 个顶点的大教堂，顶点坐标依次为 $(x_i,y_i)$，对于每个 $1 \leq i < N$，存在一条 $i$ 与 $i+1$ 之间的边，此外，还存在一条 $N$ 到 $1$ 的边。

大教堂每条边都与 $x$ 轴或 $y$ 轴平行。此外，大教堂是一个简单多边形，即：

- 每个顶点恰好由两条边相交
- 任何一对边只能在顶点处相交

你有无数块 $2 \times 2$ 的瓷砖，你希望用这些瓷砖覆盖大教堂的大部分区域，具体来说，你想选择一条垂直线，并覆盖该线左侧的大教堂部分。对于任何整数 $k$，设 $L_k$ 为包含 $x$ 坐标等于 $k$ 的点的垂直线。对 $L_k$ 左侧大教堂部分的覆盖，是指在平面上放置一定数量的瓷砖，使得：

- 多边形内部且 $x$ 坐标小于 $k$ 的每个点都被某块瓷砖覆盖
- 多边形外部或 $x$ 坐标大于 $k$ 的点都不被任何瓷砖覆盖
- 瓷砖的内部不重叠

大教堂中任何顶点的最小 $x$ 坐标为 $0$。我们设 $M$ 为大教堂中任何顶点的最大 $x$ 坐标。

请你求出最大的满足条件的 $k\ (0 \leq k \leq M)$，根据定义，一定存在答案为 $0$。

## 说明/提示

| 子任务编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $N=4$ | $4$ |
| $2$ | $N \leq 6$ | $9$ |
| $3$ | $x_N=0,y_N=0$，对于 $1 \leq i \leq N-2$，$x_i \leq x_{i+1},y_i \geq y_{i+1}$ | $11$ |
| $4$ | $M \leq 1000$ 且 $y_i \leq 1000$ | $19$ |
| $5$ | $y_i$ 都为偶数 | $22$ |
| $6$ | $x_i$ 都为偶数 | $25$ |
| $7$ | 无特殊性质 | $10$ |

对于所有数据，$4 \leq N \leq 2 \times 10^5$，$1 \leq M \leq 10^9$，$0 \leq y_i \leq 10^9$，$\min(\{x_i\}) = 0,\max(\{x_i\}) = M$。

对于样例一，下面是对于 $k=2$ 的覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/q9qi2e3b.png)

可以发现这是最大的情况了。

对于样例二，没有正值 $k$，使得 $L_k$ 左侧的教堂部分可以用瓷砖覆盖。

对于样例三，图示如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/6kpbkvbn.png)

## 样例 #1

### 输入

```
14 6
0 1
0 3
2 3
2 4
0 4
0 6
3 6
3 7
4 7
6 7
6 5
3 5
3 2
3 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
0 0
0 3
3 3
3 0```

### 输出

```
0```

## 样例 #3

### 输入

```
18 9
0 2
2 2
2 1
4 1
4 0
9 0
9 2
4 2
4 4
7 4
7 3
9 3
9 6
4 6
4 5
2 5
2 4
0 4```

### 输出

```
6```

# 题解

## 作者：wangyizhi (赞：3)

挺好想但是非常难写的一道题。。。

## 题目分析

显然我们可以扫描线。在从左往右扫的过程中若不合法的情况则输出此时的答案。

题目给的条件相当于：此时扫描到的任意一条线段长为偶数；一条线段加进来与踢出去的位置奇偶性相同。

于是可以维护两个 `set<pair<int,int>>`，分别存在偶数下标和奇数下标加进来的线段。但在加入时，可以将其与边上的线段合并。此时可以维护奇数线段的个数。删除同理。若加完或删完后奇数线段的个数大于 $0$，则不合法。在加入前我们还需一些特判。这条线段不能在两个 set 中都有能覆盖的线段，也不能被包含在奇偶性不同的那个 set 的线段中，否则不合法。至于如何判断一条线段时加还是删，也可以采取类似的方法，若在 set 中的线段能把它包含，就删除，否则加入。

然后来统计答案。若此时两个 set 其中一个为空，说明不会出现交错的情况，否则当前不行。若奇偶性不同的 set 为空，则把答案更新为当前坐标减一；若奇偶性相同的 set 为空，则把答案更新为当前坐标。需要注意的是，这些操作应在加入删除线段之前之后都做一遍。

于是就做完了。显然 $O(n \log n)$。

## AC Code

跑得还挺快的啊。

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
//bool Mst;
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
const int N=2e5+5;
vector<pii> seg[N];
int b[N],bc,cnt;
set<pii> st[2];
int len(pii x){return (x.second-x.first)&1;}
bool check(set<pii> &st,pii x)
{
	auto it=st.lower_bound(x);
	if(it!=st.end()&&it->first<=x.first&&it->second>=x.second) return 1;
	if(it==st.begin()) return 0;
	it--;
	if(it->first<=x.first&&it->second>=x.second) return 1;
	return 0;
}
bool in(set<pii> &st,pii x)
{
	auto it=st.lower_bound(x);
	if(it!=st.end()&&it->first>=x.first&&it->second<=x.second) return 1;
	if(it==st.begin()) return 0;
	it--;
	if(it->first>=x.first&&it->second<=x.second) return 1;
	return 0;
}
void insert(set<pii> &st,pii x)
{
	auto it=st.lower_bound(x);
	if(it!=st.end())
	{
		if(it->first==x.second) x.second=it->second,cnt-=len(*it),st.erase(*it);
	}
	it=st.lower_bound(x);
	if(it!=st.begin())
	{
		it--;
		if(it->second==x.first) x.first=it->first,cnt-=len(*it),st.erase(*it);
	}
	cnt+=len(x),st.insert(x);
}
void erase(set<pii> &st,pii x)
{
	auto it=st.lower_bound(x);
	if(it==st.end()||it->first>x.first) it--;
	if(it->first<x.first)
	{
		pii y={it->first,x.first};
		cnt+=len(y),st.insert(y);
	}
	if(it->second>x.second)
	{
		pii y={x.second,it->second};
		cnt+=len(y),st.insert(y);
	}
	cnt-=len(*it),st.erase(*it);
}
pii p[N];
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i].first>>p[i].second,b[++bc]=p[i].first;
	sort(b+1,b+bc+1),bc=unique(b+1,b+bc+1)-b-1;
	for(int i=1;i<=n;i++) p[i].first=lower_bound(b+1,b+bc+1,p[i].first)-b;
	p[0]=p[n];
	for(int i=1;i<=n;i++)
	{
		if(p[i].first==p[i-1].first)
		{
			int le=min(p[i].second,p[i-1].second),ri=max(p[i].second,p[i-1].second);
			seg[p[i].first].push_back({le,ri});
		}
	}
	for(int i=1;i<=bc;i++)
	{
		int x=b[i]&1;
		if(st[x].empty()) ans=b[i]-1;
		if(st[!x].empty()) ans=b[i];
		for(pii e:seg[i])
		{
			if((in(st[0],e)&&in(st[1],e))||check(st[!x],e))
			{
				cout<<ans<<"\n";
				return 0;
			}
			if(check(st[x],e)) erase(st[x],e);
			else insert(st[x],e);
		}
		if(st[x].empty()) ans=b[i]-1;
		if(st[!x].empty()) ans=b[i];
		if(cnt) break;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Linge_Zzzz (赞：3)

如果你 RE 4pts，并且只有一个点 WA，那么去看我代码注释。

# 鲜花

模拟赛上写了巨大码量的离散化+线段树，用了三种不一样的线段树。写了 5k。还没调出来。看了 [大佬的博客](https://www.cnblogs.com/Idtwtei/p/18361234) 学习了特别厉害的写法，遂写篇题解分享之。

# Sol

看到这种题肯定扫描线。不妨把所有竖着的线段提取出来。考虑什么时候不合法。

1. 手玩样例一可发现，我们需要把所有竖着的线段的横坐标奇偶分类。**如果一个纵坐标在加入和删除时的横坐标奇偶性不同**，则不合法。

2. 手玩样例二可发现，**如果存在一条竖着的长度为奇数的连通块**，则不合法。

3. 手玩样例三可发现，**如果场上只有横坐标为偶数的线段或只有横坐标为奇数的线段，当前横坐标才是可能合法的**。而且所谓的“当前横坐标”也需要特判。当场上的线段横坐标和当前横坐标奇偶性不同时需要减一。我在场上这个地方写挂了所以没调出来。

此时我们有一个非常 naive 的做法：把所有出现过的纵坐标离散化，然后在这上面建立两种线段树。第一种线段树支持区间覆盖成 0/1，查询全局有没有长度为奇数的连通块。第二种线段树支持区间覆盖成 0/1，查询一个区间内的 0/1 存在性。我在场上为了解决第三种限制还又开了个线段树记录插入时的横坐标。。。

这种写法是非常臭的。显然有更优美的写法。

下面要讲的写法本质是平衡树。但由于其维护信息的特殊性，可以使用 STL map 来代替。平衡树天生不需要离散化，所以避免了很多讨论。。。

我们把那两种线段树取缔掉。其实连通块在纵向看就是一条条线段，所以我们只需要维护线段的属性。建立两个 int 到 int 的 map，第一个维护左端点对应的右端点是哪个，第二个维护左端点所对应的线段的横坐标的奇偶性。

插入操作，由于我们的多边形十分的优美，不会保证有线段重叠，所以可以直接在 map 里插入。插入之后判一下左右有没有能合并的，如果有就合并上。

删除操作，其实就是把线段分裂开。直接 upper_bound 找相交线段然后分裂开就行。记得判一下两个相交的线段的横坐标奇偶性一不一样，不一样直接输出当前 ans。

又因为我们只关心全局的信息，所以我们在插入、合并的同时只需要记录有没有长度为奇数的线段就可以。

关于复杂度正确性，可以考虑均摊。线段插入的时候，每合并一条线段，场上线段减少 $1$，产生 $O(\log n)$ 复杂度。线段分裂的时候，会先删除一些线段，每删除一条线段场上线段减少 $1$，产生 $O(\log n)$ 复杂度，然后产生 $O(1)$ 个新线段。所以总复杂度是 $O(n\log n)$ 的。

# Code

代码有注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,x[N],y[N];
struct line{
	int x,l,r;
	line(){}
	line(int x,int l,int r):x(x),l(l),r(r){}
	bool operator<(line y){return x<y.x;}
}c[N];
int tot=0;
map<int,int> seg,par; 
int pcnt[2],ocnt,ans;
void del(int l){// 删除一条线段，同时维护信息 
	ocnt-=(seg[l]-l)%2;
	pcnt[par[l]]--;
	seg.erase(l);
	par.erase(l);
}
void ins(int l,int r,int p){// 插入一条线段，左右端点为 l,r，横坐标奇偶性为 p，同时维护信息 
	ocnt+=(r-l)%2;
	pcnt[p]++;
	par[l]=p;
	auto it=seg.insert(mp(l,r)).fi;
	int ll=prev(it)->fi,rl=next(it)->fi,rr=next(it)->se;
	//只有横坐标奇偶性相同才能合并 
	if(seg[ll]==l&&par[ll]==p)del(ll),del(l),ins(ll,r,p);//往左合并 
	else if(r==rl&&p==par[rl])del(l),del(rl),ins(l,rr,p);//往右合并 
}
void spl(int l,int r,int x,int p){
	int y=seg[x];
	if(l>=y||r<=x)return;
	if(p!=par[x]){//不同奇偶线段有交集 
		cout<<ans<<endl;
		exit(0);
	}
	del(x);
	if(x<l)ins(x,l,p);//往左分裂 
	if(y>r)ins(r,y,p);//往右分裂 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	x[0]=x[n],y[0]=y[n];
	for(int i=1;i<=n;i++)
		if(x[i]==x[i-1])
			c[++tot]=line(x[i],min(y[i],y[i-1]),max(y[i],y[i-1]));
	sort(c+1,c+1+tot);
	seg[-INF]=-INF,seg[INF]=INF;//设置边界避免分讨首尾迭代器 
	int lst=0;
	for(int i=1;i<=tot;i++){
		if(c[i].x!=lst){// 如果横坐标改变，统计一次答案 
			if(ocnt){
				cout<<ans<<endl;
				exit(0);
			}
			if(!pcnt[0])ans=max(ans,c[i].x-!(c[i].x%2));
			if(!pcnt[1])ans=max(ans,c[i].x-c[i].x%2);
		}
		auto it=seg.upper_bound(c[i].l);
		if(prev(it)->se<=c[i].l&&c[i].r<=it->fi)ins(c[i].l,c[i].r,c[i].x%2);//不存在就插入 
		else while(it->se>=c[i].l)spl(c[i].l,c[i].r,(it--)->fi,c[i].x%2);//一直删，直到没有相交的线段
		/*上一行的错误示范： 
		else while(it->se>=c[i].l)spl(c[i].l,c[i].r,it->fi,c[i].x%2),it--;
		原因是 (it--)->fi 会先传参，再 it-- 最后执行函数。如果执行函数之后再 it-- 会因为 it 已经被删除而出错。 
		错误写法会 RE 4pts，并且只有一个点 WA。 
		*/
		lst=c[i].x;
	}
	cout<<m<<endl;
	return 0;
}
```

---

## 作者：hnczy (赞：1)

这道题也是非常的抽象。

部分分就是一个阶梯状的多边形。每一次判断两个点是否合法即可。

满分整体的思路就是一个对于 $y$ 的扫描线，分别对 $x$ 为奇数和 $x$ 为偶数的线段进行叠加，看是否有奇数的长度的区间。 用两个线段树维护即可。

如何记答案？

第一，可以在每一个竖直的线段都搞完了就可以了。

第二，横坐标为当前的奇偶性的在这个横坐标所有的竖直的线段都做完了之后还是有长度为奇数的线段就可以记答案直接输出。

思路知道了，还需要一些细节：

$y$ 需要离散化。

每次在加入的时候需要判断另一个奇偶性的这一个区间不能有值。

在一条线段的中间的点可以直接删除。

大概就这么多了，但是写的时候还是需要把细节列出才好写。

```c++
#include <bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N = 2e5 + 5;
int n, m, x[N], y[N], b[N], cnt, tot;
struct Line {
	int l, r, x, op;
	bool operator<(const Line &a) const {
		return x < a.x;
	}
} li[N];
void init() {
	int now = 1;
	for (int i = 2; i <= n; ++i)
		if (x[i] == x[i - 1])
			li[++cnt] = { y[i - 1], y[i], x[i] };
	if (x[n] == x[1])
		li[++cnt] = { y[n], y[1], x[1] };
	for (int i = 2; i <= cnt; ++i) {
		if (li[now].x == li[i].x)
			li[now].r = li[i].r;
		else li[++now] = li[i];
	}
	while (now && li[now].x == li[1].x) li[1].l = li[now--].l;
	cnt = now;
	for (int i = 1; i <= cnt; ++i) b[++tot] = li[i].l, b[++tot] = li[i].r;
	sort(li + 1, li + cnt + 1);
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	bool opt = 0;
	if (li[1].l > li[1].r)opt = 1;
	for (int i = 1; i <= cnt; ++i) {
		if (li[i].l > li[i].r) {
			swap(li[i].l, li[i].r);
			li[i].op = opt;
		} else li[i].op = opt ^ 1;
		li[i].l = lower_bound(b + 1, b + tot + 1, li[i].l) - b;
		li[i].r = lower_bound(b + 1, b + tot + 1, li[i].r) - b - 1;
		//cout<<li[i].r <<endl;
	}
}
struct Node {
	int len, l, r, sum;
	bool flag;
	Node operator+(const Node &a) const {
		Node res;
		res.len = len + a.len;
		res.flag = flag | a.flag;
		res.sum = sum + a.sum;
		if (l == len)
			res.l = l + a.l;
		else {
			res.l = l;
			if (a.l != a.len)
				res.flag |= r + a.l & 1;
		}
		if (a.r == a.len)res.r = r + a.r;
		else res.r = a.r;
		return res;
	}
	Node operator+(const int &a) const {
		Node res;
		res.len = len;
		res.l = res.r = res.sum = a * len;
		res.flag = 0;
		return res;
	}
	bool check() {
		return flag | (l & 1) | (r & 1);
	}
};
struct Seg {
	Node c[N << 2];
	int tag[N << 2];
	void pushup(int p) {
		c[p] = c[ls] + c[rs];
	}
	void pushtag(int p, int v) {
		tag[p] = v;
		c[p] = c[p] + v;
	}
	void pushdown(int p) {
		if (tag[p] != -1) {
			pushtag(ls, tag[p]);
			pushtag(rs, tag[p]);
			tag[p] = -1;
		}
	}
	void build(int p, int l, int r) {
		if (l == r) {
			c[p] = { b[l + 1] - b[l], 0, 0, 0, 0 };
			tag[p] = -1;
			return;
		}
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(p);
	}
	void change(int p, int l, int r, int L, int R, int v) {
		if (l >= L && r <= R)
			return pushtag(p, v);
		pushdown(p);
		int mid = l + r >> 1;
		if (mid >= L)
			change(ls, l, mid, L, R, v);
		if (mid < R)
			change(rs, mid + 1, r, L, R, v);
		pushup(p);
	}
	Node query(int p, int l, int r, int L, int R) {
		if (l >= L && r <= R)
			return c[p];
		pushdown(p);
		int mid = l + r >> 1;
		if (mid >= L && mid < R)
			return query(ls, l, mid, L, R) + query(rs, mid + 1, r, L, R);
		if (mid < R)
			return query(rs, mid + 1, r, L, R);
		return query(ls, l, mid, L, R);
	}
	bool check() {
		return c[1].sum != 0;
	}
} seg[2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
	init();
	tot--;
	seg[0].build(1,1,tot);
	seg[1].build(1,1,tot);
	int ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		int l = li[i].l, r = li[i].r, f = li[i].x & 1;
		if (seg[f^1].query(1, 1, tot , l, r).sum)
			break;
		seg[f].change(1,1,tot,l,r,li[i].op);
		if(i==cnt){
			ans=m;
			break;
		}
		if (li[i].x != li[i + 1].x) {
			if (seg[0].c[1].check() || seg[1].c[1].check())
				break;
			if (!seg[0].check() && seg[1].check()) {
				ans = li[i + 1].x;
				if (ans%2==0)--ans;
			}
			if (seg[0].check() && !seg[1].check()) {
				ans = li[i + 1].x;
				if (ans&1)--ans;
			}
		}
		//cout<<ans<<endl;
	}//
	printf("%d", ans);
	return 0;
}
```

~~线段树写错了也是服了~~

---

## 作者：huhangqi (赞：1)

很明显是一个扫描线问题，但是明显比大部分扫描线复杂，因为除了要预处理还需要大量的分析。

由于题目要求我们求出在 $x$ 左边铺上满足要求的最大值，所以可以以纵轴平行的边作为扫描线。

由于每条边之间可能会有一些没有用的端点，在建边时需要对这些边进行一个合并操作，即把两个边加在一起。

由于要进行区间操作，还需要对于纵坐标的值进行离散化，这样预处理就完成了。

预处理代码:

```cpp
struct L{
	int l,r,x,op;//记录下纵坐标上下端以及横坐标，op表示是增边还是减边
	bool friend operator<(L a,L b){
		return a.x<b.x;
	}
}line[200001];
void init(){
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>x[i]>>y[i];
	int now=1;
	for(int i=1;i<n;i++)if(x[i]==x[i-1])line[++cnt]={y[i-1],y[i],x[i]};
	if(x[n-1]==x[0])line[++cnt]={y[n-1],y[0],x[0]};
	for(int i=2;i<=cnt;i++){
		if(line[now].x==line[i].x)line[now].r=line[i].r;
		else line[++now]=line[i];
	}
	while(now&&line[now].x==line[1].x)line[1].l=line[now--].l;
	n=now;
	cnt=0;
	for(int i=1;i<=n;i++){
		tmp[++cnt]=line[i].l;
		tmp[++cnt]=line[i].r;
	}
	sort(line+1,line+n+1);
	sort(tmp+1,tmp+cnt+1);
	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
	bool f;
	if(line[1].l>line[1].r)f=1;//由于顺时针还是逆时针不确定，排序后此处为最早加入的边，以此为标准
	else f=0;
	for(int i=1;i<=n;i++){
		if(line[i].l>line[i].r){
			line[i].op=f;
			swap(line[i].l,line[i].r);
		}else line[i].op=f^1;
		line[i].l=lower_bound(tmp+1,tmp+cnt+1,line[i].l)-tmp;
		line[i].r=lower_bound(tmp+1,tmp+cnt+1,line[i].r)-tmp-1;//由于需要区间操作，每一个数表示一个区间，r要减一，扫描线常见套路
	}
}
``````

然后问题就是怎么样通过扫描线记录下答案了。

可以先分析一下什么情况下是合法的。

首先如果我将横坐标为偶数的边加入原本有横坐标为奇数的边，不可行，因为此时二者距离必定不为偶数。

其次如果某些边组成了奇数长度的连续区间，那么也不可行。

那么就可以考虑怎么解决了。

第一步，我们可以分别开两个线段树分别维护纵坐标不同奇偶的情况下组成的几段区间，加入线段前判断一下是否有不同奇偶的线在此范围内。

第二步，我们可以直接在线段树中维护有多少个奇数区间即可。

关于线段树的部分代码如下：

```cpp
struct P{
	int len,l,r,s;
	bool f;
	P friend operator +(P a,P b){
		P c;
		c.len=a.len+b.len;
		c.f=a.f|b.f;
		c.s=a.s+b.s;
		if(a.l==a.len)c.l=a.l+b.l;
		else {
			c.l=a.l;
			if(b.l!=b.len)c.f|=a.r+b.l&1;
		}
		if(b.r==b.len)c.r=a.r+b.r;
		else c.r=b.r;
		return c;
	}
	P friend operator +(P a,int b){
		P c;
		c.len=a.len;
		c.l=c.r=c.s=a.len*b;
		c.f=0;
		return c;
	}
	bool check(){
		return (f|(l&1)|(r&1));
	}
};
struct ST{
	P c[800001];
	int tag[800001];
	#define ls p<<1
	#define rs p<<1|1
	void Tag(int p,int v){
		tag[p]=v;
		c[p]=c[p]+v;
	}
	void pushup(int p){
		c[p]=c[ls]+c[rs];
	}
	void pushdown(int p){
		if(tag[p]==-1)return;
		Tag(ls,tag[p]);
		Tag(rs,tag[p]);
		tag[p]=-1;
	}
	void build(int p,int l,int r){
		tag[p]=-1;
		if(l==r){
			c[p]={tmp[r+1]-tmp[l],0,0,0,0};
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int L,int R,int v){
		if(l>=L&&r<=R)return void(Tag(p,v));
		pushdown(p);
		int mid=l+r>>1;
		if(mid>=L)change(ls,l,mid,L,R,v);
		if(mid<R)change(rs,mid+1,r,L,R,v);
		pushup(p);
	}
	P query(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R)return c[p];
		pushdown(p);
		int mid=l+r>>1;
		if(mid>=L&&mid<R)return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		else if(mid<R)return query(rs,mid+1,r,L,R);
		else return query(ls,l,mid,L,R);
	}
	bool check(){
		return c[1].s!=0;
	}
}tr[2];
``````

最后就是激动人心的统计答案环节了。

在可以统计答案时，还有一些要关注的。

首先，在之后还有相同的纵坐标值的时候，不可以统计答案，否则可能会产生误判。

其次，如果此时既有横坐标为奇数的，又有横坐标为偶数的，那么不能统计答案，因为这截止的横坐标确定后，这两种情况就不可能都取到值。

如果此时只有奇数，那么纵坐标也一定是奇数。

如果此时只有偶数，那么纵坐标也一定是偶数。

统计答案到最后，如果可行，直接输出最大值 $m$ 即可。

总代码(统计答案在主函数)：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x[200001],y[200001],cnt,tmp[200001];
struct L{
	int l,r,x,op;
	bool friend operator<(L a,L b){
		return a.x<b.x;
	}
}line[200001];
struct P{
	int len,l,r,s;
	bool f;
	P friend operator +(P a,P b){
		P c;
		c.len=a.len+b.len;
		c.f=a.f|b.f;
		c.s=a.s+b.s;
		if(a.l==a.len)c.l=a.l+b.l;
		else {
			c.l=a.l;
			if(b.l!=b.len)c.f|=a.r+b.l&1;
		}
		if(b.r==b.len)c.r=a.r+b.r;
		else c.r=b.r;
		return c;
	}
	P friend operator +(P a,int b){
		P c;
		c.len=a.len;
		c.l=c.r=c.s=a.len*b;
		c.f=0;
		return c;
	}
	bool check(){
		return (f|(l&1)|(r&1));
	}
};
struct ST{
	P c[800001];
	int tag[800001];
	#define ls p<<1
	#define rs p<<1|1
	void Tag(int p,int v){
		tag[p]=v;
		c[p]=c[p]+v;
	}
	void pushup(int p){
		c[p]=c[ls]+c[rs];
	}
	void pushdown(int p){
		if(tag[p]==-1)return;
		Tag(ls,tag[p]);
		Tag(rs,tag[p]);
		tag[p]=-1;
	}
	void build(int p,int l,int r){
		tag[p]=-1;
		if(l==r){
			c[p]={tmp[r+1]-tmp[l],0,0,0,0};
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int L,int R,int v){
		if(l>=L&&r<=R)return void(Tag(p,v));
		pushdown(p);
		int mid=l+r>>1;
		if(mid>=L)change(ls,l,mid,L,R,v);
		if(mid<R)change(rs,mid+1,r,L,R,v);
		pushup(p);
	}
	P query(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R)return c[p];
		pushdown(p);
		int mid=l+r>>1;
		if(mid>=L&&mid<R)return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		else if(mid<R)return query(rs,mid+1,r,L,R);
		else return query(ls,l,mid,L,R);
	}
	bool check(){
		return c[1].s!=0;
	}
}tr[2];
void init(){
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>x[i]>>y[i];
	int now=1;
	for(int i=1;i<n;i++)if(x[i]==x[i-1])line[++cnt]={y[i-1],y[i],x[i]};
	if(x[n-1]==x[0])line[++cnt]={y[n-1],y[0],x[0]};
	for(int i=2;i<=cnt;i++){
		if(line[now].x==line[i].x)line[now].r=line[i].r;
		else line[++now]=line[i];
	}
	while(now&&line[now].x==line[1].x)line[1].l=line[now--].l;
	n=now;
	cnt=0;
	for(int i=1;i<=n;i++){
		tmp[++cnt]=line[i].l;
		tmp[++cnt]=line[i].r;
	}
	sort(line+1,line+n+1);
	sort(tmp+1,tmp+cnt+1);
	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
	bool f;
	if(line[1].l>line[1].r)f=1;
	else f=0;
	for(int i=1;i<=n;i++){
		if(line[i].l>line[i].r){
			line[i].op=f;
			swap(line[i].l,line[i].r);
		}else line[i].op=f^1;
		line[i].l=lower_bound(tmp+1,tmp+cnt+1,line[i].l)-tmp;
		line[i].r=lower_bound(tmp+1,tmp+cnt+1,line[i].r)-tmp-1;
	}
}
signed main(){
	init();
	tr[0].build(1,1,cnt-1);
	tr[1].build(1,1,cnt-1);
	int ans=0;
	for(int i=1;i<=n;i++){
		int l=line[i].l,r=line[i].r,now=(line[i].x&1);
		if(tr[now^1].query(1,1,cnt-1,l,r).s)break;
		tr[now].change(1,1,cnt-1,l,r,line[i].op);
		if(i==n||line[i].x!=line[i+1].x){
			if(tr[0].c[1].check()||tr[1].c[1].check())break;
			if(i==n){
				ans=m;
				break;
			}
			if(!tr[0].check()&&tr[1].check()){
				ans=line[i+1].x;
				if(!(ans&1))ans--;
			}
			if(tr[0].check()&&!tr[1].check()){
				ans=line[i+1].x;
				if(ans&1)ans--;
			}
		}
	}
	cout<<ans;
	return 0;
}

``````

---

## 作者：qwer6 (赞：1)

好抽象的题目，写了巨久。

## 子任务一，二

我们发现点的数量十分的少，所以我们知道形状的数量极其有限，我们直接分类讨论即可。

我们以 $N=4$ 时的矩形为例。

我们发现，当矩形的宽为奇数的时候，答案为 $0$。

而当矩形的长为偶数时，我们显然可以使用地砖铺满整个教堂，答案为 $m$。

当矩形的长为奇数时，答案就是 $m-1$ ，最后会空出一列不能铺满。

当 $N=5$ 的时候也是矩形，只是有一个点在一条边上，去掉这个点当成 $N=4$ 的情况来即可。

那 $N=6$ 的时候呢？

这里放出几种可能的图形。

![](https://cdn.luogu.com.cn/upload/image_hosting/1chenf0u.png)

显然都可以分割为两个矩形，从左到右求解即可。

注意六个点也可以变成矩形，和 $N=5$ 时同理。

代码过于简单，一堆 if 嵌套，这里不做演示。

## 子任务三

图形与 $N=6$ 的时候基本一致，是一个阶梯状的图形，可以分割为矩形求解。

我们从左到右一点一点判过来就可以了。

但是这个时候，这道题的难点之一就显示出来了。

我们需要对这一堆点做一点预处理，方便我们求解。

这里我们需要做这些处理：找到左下角的点，即 $x$ 坐标等于 $0$,且 $y$ 坐标最小的点作为起点，并且使得所有的点按照顺时针顺序排列；如果有三个及以上的点在一条线段上，我们只保留两个端点。

第一个处理的第一步十分好做，直接遍历一次所有点就可以了。

```c++
for(int i=1;i<=n;i++)
		if(!x[i])
			if(y[i]<miy)
                idx=i,miy=y[i];//idx 表示换了之后的起点
```

然后，我们以找到的这个点作为第一个点，将整个数组平移。

```c++
for(int i=idx;i<=n;i++)xx[i-idx+1]=x[i],yy[i-idx+1]=y[i];//这里 x,y 是原来的数组，xx,yy 是平移后的数组
for(int i=1;i<idx;i++)xx[n-idx+1+i]=x[i],yy[n-idx+1+i]=y[i];
```

如果第一个点和第二个点 $y$ 坐标相同，那么说明点是逆时针给出的，我们再对 $2\sim n$ 的点做一次翻转即可。

```c++
if(yy[1]==yy[2]){
    for(int i=2;i<=n;i++)x[i]=xx[i],y[i]=yy[i];
    for(int i=2;i<=n;i++)xx[i]=x[n+2-i],yy[i]=y[n+2-i];
}
```

现在我们已经完成了第一步，接下来我们完成第二步。

我们先假定第一个点和第二个点为一条边的两个端点，然后从第三个点开始遍历，如果连续三个点的 $x$ 坐标相同，说明这三个点在同一条竖线上，以第三个点的 $y$ 坐标作为端点的 $y$ 坐标即可，如果有连续三个点的 $y$ 坐标相同，说明这三个点在同一条横线上

以第三个点的 $x$ 坐标作为端点的 $y$ 坐标即可，如果都不满足，说明三点不共线，将第三点存入数组即可。

```c++
x[1]=xx[1],y[1]=yy[1];//这里的 xx,yy 和上面的是同一个
x[2]=xx[2],y[2]=yy[2];
for(int i=3;i<=n;i++){
    if(x[cnt]==xx[i]&&x[cnt-1]==xx[i])y[cnt]=yy[i];
    else if(y[cnt]==yy[i]&&y[cnt-1]==yy[i])x[cnt]=xx[i];
    else{
        cnt++;
        x[cnt]=xx[i];
        y[cnt]=yy[i];
    }
}
```

然后我们发现只需要储存竖线和对应的 $x$ 坐标就可以判断答案了，所以我们直接处理即可。

```c++
struct line{
	int l,r,x,tp;
	bool operator <(const line &a)const{return x<a.x;}
}a[N];
```

```c++
for(int i=1;i<=n;i+=2){
    if(y[i]<y[i+1])a[(i+1)>>1]={y[i],y[i+1],x[i]};
    else a[(i+1)>>1]={y[i+1],y[i],x[i]};
}
```

最后判断答案。

```c++
sort(a+1,a+cnt+1);
if((a[1].r-a[1].l)&1){
    putchar('0');
    exit(0);
}
for(int i=2;i<=cnt;i++){
    if((a[i].x-a[i-1].x)&1){//为什么这么做？看子任务一，二的解释
        ans=a[i].x-1;
        break;
    }
    if((a[i].r-a[i].l)&1){
        ans=a[i].x;
        break;
    }
}
```

## 正解

我们仔细观察一下样例，会发现，只要当前竖线没有长度为奇数的线段，那么就可以继续向下铺，直到有新的线加入，或者距离下一条线只剩一列了，就停下。

我们继续思考，还有什么时候是不可以的呢？类比 $N=4$ 时的矩形思路，我们可以发现这样一个结论。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ye7i04k.png)

~~我知道图有点抽象，但是凑合着看吧。~~

我们发现，最右边的竖线加进来的时候，它覆盖的区域原来就被覆盖了，并且那若干条竖线的 $x$ 坐标的奇偶性和这条竖线的奇偶性不同，所以不能加入，答案就是 $2$。 

还是类比矩形，我们发现还是有一个统计答案时候的细节问题，就是竖线间的距离，如果为奇数，那么答案就是距离减一。

那么我们使用两颗线段树，需要实现区间覆盖，查询区间内有无线段，查询全局有无长为奇数的线段，比较板子。

注意需要离散化。

## Code

```c++
/*by qwer6*/
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("______________________________")
namespace FastIO{
	inline int read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		a*=f;
		return a;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		std::stack<int>st;
		do{
		   st.push(x%10);
		   x/=10;
		}while(x);
		while(!st.empty())putchar(st.top()+'0'),st.pop();
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=2e5+5;
int n,m,cnt,tot,ans;
int x[N],y[N],xx[N],yy[N];
struct line{
	int l,r,x,tp;
	bool operator <(const line &a)const{return x<a.x;}
}a[N];
struct Node{
	int len,lmx,rmx,sum;
	bool flag;
	Node friend operator +(Node a,Node b){
		Node res;
		res.len=a.len+b.len,res.sum=a.sum+b.sum;
		res.lmx=a.lmx,res.rmx=b.rmx;
		if(a.lmx==a.len)res.lmx+=b.lmx;
		if(b.rmx==b.len)res.rmx+=a.rmx;
		res.flag=(a.flag|b.flag);
		if((a.rmx!=a.len)&&(b.lmx!=b.len)&&((a.rmx+b.lmx)&1))res.flag=1;
		return res;
	}
	Node operator +(const int &a)const{
		Node res=*this;
		res.flag=0;
		if(a)res.sum=res.lmx=res.rmx=res.len;
		else res.sum=res.lmx=res.rmx=0;
		return res;
	}
	bool odd(){return flag|(lmx&1)|(rmx&1);}
};
struct Segment_tree{
	Node c[N<<2];
	int tag[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid (l+r>>1)
	void pushup(int p){c[p]=c[ls]+c[rs];}
	void Tag(int p,int v){
		tag[p]=v;
		c[p]=c[p]+v;
	}
	void pushdown(int p){
		if(tag[p]==-1)return ;
		Tag(ls,tag[p]);
		Tag(rs,tag[p]);
		tag[p]=-1;
	}
	void build(int p,int l,int r){
		tag[p]=-1;
		if(l==r){
			c[p].lmx=c[p].rmx=c[p].sum=c[p].flag=0;
			c[p].len=y[r+1]-y[l];
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int L,int R,int v){	 
		if(L<=l&&r<=R)return Tag(p,v);
		pushdown(p);
		if(mid>=L)change(ls,l,mid,L,R,v);
		if(mid<R)change(rs,mid+1,r,L,R,v);
		pushup(p);	
	}
	Node query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return c[p];
		pushdown(p);
		if(mid>=L&&mid<R)return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		if(mid>=L)return query(ls,l,mid,L,R);
		return query(rs,mid+1,r,L,R);
	}
}Set[2];
int init(){
	int cnt=2,idx;
	for(int i=1,mi=0x3f3f3f3f;i<=n;i++){
		if((!x[i])&&mi>y[i]){
			mi=y[i];
			idx=i;
		}
	}
	for(int i=idx;i<=n;i++)xx[i-idx+1]=x[i],yy[i-idx+1]=y[i];
	for(int i=1;i<idx;i++)xx[n-idx+1+i]=x[i],yy[n-idx+1+i]=y[i];
	if(yy[1]==yy[2]){
		for(int i=2;i<=n;i++)x[i]=xx[i],y[i]=yy[i];
		for(int i=2;i<=n;i++)xx[i]=x[n+2-i],yy[i]=y[n+2-i];
	}
	x[1]=xx[1],y[1]=yy[1];
	x[2]=xx[2],y[2]=yy[2];
	for(int i=3;i<=n;i++){
		if(x[cnt]==xx[i]&&x[cnt-1]==xx[i])y[cnt]=yy[i];
		else if(y[cnt]==yy[i]&&y[cnt-1]==yy[i])x[cnt]=xx[i];
		else{
			cnt++;
			x[cnt]=xx[i];
			y[cnt]=yy[i];
		}
	}
	if(y[1]==y[2]){
		for(int i=2;i<=cnt;i++)xx[i]=x[i],yy[i]=y[i];
		for(int i=2;i<=cnt;i++)x[i]=xx[cnt+2-i],y[i]=yy[cnt+2-i];
	}
	return cnt;
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)read(x[i]),read(y[i]);	
	n=init();	
	for(int i=1;i<=n;i+=2){
		if(y[i]<y[i+1])a[(i+1)>>1]={y[i],y[i+1],x[i],1};
		else a[(i+1)>>1]={y[i+1],y[i],x[i],0};
	}
	cnt=n>>1;
	sort(a+1,a+cnt+1);
	sort(y+1,y+n+1);
	tot=unique(y+1,y+n+1)-y-1;
	for(int i=1;i<=cnt;i++){
		a[i].l=lower_bound(y+1,y+tot+1,a[i].l)-y;
		a[i].r=lower_bound(y+1,y+tot+1,a[i].r)-y;
	}
	Set[0].build(1,1,tot-1),Set[1].build(1,1,tot-1);
	for(int i=1,x,l,r;i<=cnt;i++){		
		l=a[i].l,r=a[i].r-1,x=a[i].x&1;
		if(Set[x^1].query(1,1,tot-1,l,r).sum)break;	
		Set[x].change(1,1,tot-1,l,r,a[i].tp);
		if(i==cnt){ans=m;break;}
		if(a[i].x!=a[i+1].x){
			if(Set[0].c[1].odd()||Set[1].c[1].odd())break;
			if(Set[0].c[1].sum&&Set[1].c[1].sum)continue;
			ans=a[i+1].x;
			if(Set[0].c[1].sum&&((ans&1)==1))ans--;
			if(Set[1].c[1].sum&&((ans&1)==0))ans--;
		}
	}
	write(ans);
}
```

---

## 作者：内拉组里 (赞：0)

这题绝对有黑。

乍看没思路，只能从部分分入手。

# Pts 4

> 白给的，边长测出来判一下就行了。
>
> 不展开了。

***

# Pts 13

> Subtask #2 其实是 Subtask #3 的简化版，这里就一起切了。
>
> 画出来的图形一定是这样的：
>
> ```
> ######
> #~~~~#
> #~~~~#####
> #~~~~~~~~#
> #~~~~~~~~#####
> #~~~~~~~~~~~~#
> #~~~~~~~~~~~~#####
> #~~~~~~~~~~~~~~~~#
> ##################
> ```
>
> 并且一定是个凸多边形，还是平行于坐标轴的。
>
> 故直接横着跑扫描线デス～
>
> 如果两条相邻的线段距离为奇数就扫不下去了。
>
> 同样地，如果扫到一半发现纵截距为奇数，也不能再扫了。
>
> 如果没有发生任何问题，那说明整个教堂可以填满瓷砖，输出 $ m $ デス～

## Analyses :

> 相应时间复杂度 $ \Theta (N) $。
>
> 相应空间复杂度 $ \Theta (N) $。

***

# Pts 100

> 把上面的部分分切完大概就能感受到这道题与扫描线的关系了。
>
> 那肯定要搬出线段树了，~~因为平衡树不会~~ 。
>
> 首先要明确线段树要维护的是什么，
>
> 这里选择维护区间内是否存在长度为奇数的线段，
>
> 为此，需要维护五个值：离散化后的间距，从左和从右开始的连续区间，区间元素和以及是否存在长度为奇数的连续区间的 $ flag $ 标记。
>
> 这里从两侧开始的连续区间部分可以参照 [<font color=#3498DB>**P2894 [USACO08FEB] Hotel G**</font>](https://www.luogu.com.cn/problem/P2894) 的写法。
>
> 离散化后间距以及区间元素和可以直接简单相加。
>
> 对于 $ flag $ 标记，应该是由 $ flag_{ls} $ 和 $ flag_{rs} $ 按位或得到。
>
> 除此之外还要判断中间由两子区间拼接而成的区间长度是否为奇数。
>
> 至于 $ lazy $ 标记的话这里采用覆盖标记 $ cover $，因为这题并不在乎每一个节点具体的值。
>
> 其余的特判和 **Pts13** 里的差不多。

## Analyses :

> 总时间复杂度 $ \Theta (N \log{N}) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code :

> 有点长，放在[云剪贴板](https://www.luogu.com.cn/paste/ryx6blka)里。

---

