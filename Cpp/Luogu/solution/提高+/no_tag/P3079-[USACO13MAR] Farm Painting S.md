# [USACO13MAR] Farm Painting S

## 题目描述

After several harsh winters, Farmer John has decided it is time to re-paint his farm.  The farm consists of N fenced enclosures (1 <= N <= 50,000), each of which can be described by a rectangle in the 2D plane whose sides are parallel to the x and y axes.  Enclosures may be contained within other enclosures, but no two fences intersect, so if two enclosures cover the same area of the 2D plane, one must be contained within the other.

FJ figures that an enclosure contained within another enclosure will not be visible to the outside world, so he only wants to re-paint enclosures that are themselves not contained within any other enclosures.  Please help FJ determine the total number of enclosures he needs to paint.

经过几个严冬，农场主约翰决定是重新粉刷农场的时候了。该农场由$n$个围栏围成（$1<=n=50000$），每一个都可以用二维平面上的矩形来描述，其两侧平行于x和y轴。牛圈可能包含在其他牛圈中，但没有两个栅栏相交（不同牛圈的边不会有接触）。因此如果两个牛圈覆盖了二维平面的同一区域，那么一个必须包含在另一个内。

FJ知道，被其他牛圈包含的牛圈是不会被外面的人看到的。众所周知，FJ非常懒，所以他只想刷露在外面的牛圈，请帮助他求出总共需要刷的牛圈的个数。


## 说明/提示

There are three enclosures.  The first has corners (2,0) and (8,9), and so on.


Enclosure 3 is contained within enclosure 1, so there are two enclosures not contained within other enclosures.


## 样例 #1

### 输入

```
3 
2 0 8 9 
10 2 11 3 
4 2 6 5 
```

### 输出

```
2 
```

# 题解

## 作者：Dream__Sky (赞：3)

此题用暴力的解法，即枚举每一个是否能被其它牛圈覆盖，复杂度 $O(n^2)$ ，并不能通过。本题可以使用优化暴力的做法。

我这里用 $x_i,y_i,x1_i,y1_i$ 表示第 $i$ 个牛圈的上左下右。用 $x_j,y_j,x1_j,y1_j$ 表示第 $j$ 个牛圈的上左下右。

首先要注意，如何判断有没有被包含：

当牛圈 $j$ 包含 牛圈 $i$ 时，

$x_j < x_i$

$y_j < y_i$

$y1_j > y1_i$

$x1_j > x1_i$

接着，我们可以用类似单调队列的想法，将所有牛圈按照某一条边排序，使牛圈有序。例如，如果按照 $x_i$ 从小到大排序后，当前面的牛圈的最底下一条边，即 $x1_i < x_j$ 时，那么肯定是不可行的。也就是说，每一次我们不必从头开始查询，只要从上一次查询的地方起，去掉那些已经不可能被包含的牛圈，再开始判断能否被包含即可。


附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[50001],ans,l=1,r=2;
struct node
{
	int x,y,xx,yy;//分别是上左下右的坐标
}a[50001];
bool cmp(node x,node y)
{
	return x.x<y.x;
}//按照边排序
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y>>a[i].xx>>a[i].yy;
	sort(a+1,a+n+1,cmp);
	ans=n;
	while(r<=n)
	{
		while(a[l].xx<=a[r].x)l++;//将前面已不可能被包围的牛圈删去
		for(int i=l;i<=r;i++)
		  if(a[r].x>a[i].x&&a[r].yy<a[i].yy&&a[i].y<a[r].y&&a[i].xx>a[r].xx)
			{ 
				ans--;
				break;
			}//在可能的牛圈中，逐个比较，直到发现被包围
         		//如果发现，那么不被包围的牛圈个数就减一
		r++;
	}
	cout<<ans;//输出答案
   	return 0;
}
```


---

## 作者：zifanwang (赞：3)

看大家好多写的都用了四维偏序，给一个不用偏序的解法。

简化一下题目，就是给你 $n$ 个矩形，第 $i$ 个矩形用 $(x1_i,y1_i,x2_i,y2_i)$ 表示，问你有多少个 $i$ 满足：

* 不存在另一个 $j$ 使得 $x1_j\le x1_i\le x2_j\wedge y1_j\le y1_i\le y2_j$。

我们从左到右扫描每一个 $x$。

我们建立一个数组，对于每一个 $i$，我们可以在 $x=x1_i$ 的时候把数组上的第 $y1_i$ 个数到第 $y2_i$ 个数全部加一，在 $x=x2_i+1$ 的时候再全部减一。

这样对于任意一个 $i$，我们只要判断当 $x=x1_i$ 时，数组上的第 $y1_i$ 个数是否为 $1$（这个矩形也在自己内） 就可以知道这个矩形是否在其它的矩形内了，只有这个数为 $1$，才说明这个矩形不在任何其它的矩形内。

这个数组可以用树状数组维护，时间复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
#define mxn 1000003
using namespace std;
struct node{
	int x,i;
};
int n,ans,c[mxn];
bool fl[50003];
vector<pair<int,int> >ad[mxn],dl[mxn];
vector<node>q[mxn];
void add(int x,int y){
	for(;x<=1000001;x+=x&-x)c[x]+=y;
}
int ask(int x){
    int num=0;
    for(;x;x-=x&-x)num+=c[x];
    return num;
}
signed main(){
	scanf("%d",&n);
	for(int i=0,x1,y1,x2,y2;i<n;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		y1++,y2++;
		ad[x1].push_back(make_pair(y1,y2));
		dl[x2].push_back(make_pair(y1,y2));
		q[x1].push_back({y1,i});
	}
	for(int i=0;i<1000001;++i){
		for(pair<int,int>p:ad[i]){
			add(p.first,1);
			add(p.second+1,-1);
		}
		for(node j:q[i]){
			if(ask(j.x)!=1)fl[j.i]=1;
		}
		for(pair<int,int>p:dl[i]){
			add(p.first,-1);
			add(p.second+1,1);
		}
	}
	for(int i=0;i<n;++i)if(!fl[i])ans++;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：GHJhandsome (赞：3)

设矩形左上角和右下角的坐标为 $(x_{1},y_{1})(x_{2},y_{2})$ ，
当矩形 $i$ 包含矩形 $j$ 时，
$$x_{1,i}<x_{1,j}$$
$$y_{1,i}<y_{1,j}$$
$$x_{2,i}>x_{2,j}$$
$$y_{2,i}>y_{2,j}$$
转换一下，得
$$x_{1,i}<x_{1,j}$$
$$y_{1,i}<y_{1,j}$$
$$-x_{2,i}<-x_{2,j}$$
$$-y_{2,i}<-y_{2,j}$$
观察可得为四维偏序， KD-tree 可做。所以我们以 $(x_{1,i},y_{1,i},-x_{2,i},-y_{2,i})$ 为四个维度，建立一棵 KD-tree ，然后从 $1$ 到 $n$ 枚举矩形 $i$ ，在求出所以在矩形 $i$ 内的矩形 $j$ ，记录状态，最后在统计一下没有被包含的矩形个数就可以了。

时间复杂度为 $O(n^{1.75})$ ， $n=50000$ 的数据可能会 TLE ，所以需要存子树最值进行整体判断包含情况以剪枝，另外已经被包含的矩形 $j$ 不用判断是否包含其他矩形或被其他矩形包含。

上代码
```
#include<iostream>
#include<algorithm>
#define minx(a,b) ((a)<(b)?(a):(b))
#define maxx(a,b) ((a)>(b)?(a):(b))
using namespace std;
int n,i,j,o,ch[50007][2],minn[50007][4],maxn[50007][4],z=0;
//minn和maxx指子树的最值
bool ans[50007]={},vis[50007];
//ans和vis记录子树和节点的状态
struct node{
	int a[4];
}a[50007];
bool cmp(node a,node b){ 
	return a.a[o%4]<b.a[o%4];
}
int build(int l,int r){
	if(l>r)return 0;
	++o;
	int mid=(l+r)>>1;
	nth_element(a+l,a+mid,a+r+1,cmp);
	ch[mid][0]=build(l,mid-1);
	ch[mid][1]=build(mid+1,r);
	for(int j=0;j<4;++j){
		minn[mid][j]=a[mid].a[j];
		if(ch[mid][0])minn[mid][j]=minx(minn[mid][j],minn[ch[mid][0]][j]);
		if(ch[mid][1])minn[mid][j]=minx(minn[mid][j],minn[ch[mid][1]][j]);
		maxn[mid][j]=a[mid].a[j];
		if(ch[mid][0])maxn[mid][j]=maxx(maxn[mid][j],maxn[ch[mid][0]][j]);
		if(ch[mid][1])maxn[mid][j]=maxx(maxn[mid][j],maxn[ch[mid][1]][j]);
	}
	--o;
	return mid;
}
void se(int l,int r){
	if(l>r)return;
	int mid=(l+r)>>1;
	if(ans[mid])return;
	for(int j=0;j<4;++j){
		if(a[i].a[j]>=maxn[mid][j])return;
	}
	ans[mid]=1;
	for(int j=0;j<4;++j){
		if(a[i].a[j]>=minn[mid][j])ans[mid]=0;
	}
	if(ans[mid]){
		for(int j=l;j<=r;++j)vis[j]=1;
		return;
	}
	if(!vis[mid]){
		vis[mid]=1;
		for(int j=0;j<4;++j){
			if(a[i].a[j]>=a[mid].a[j])vis[mid]=0;
		}
	}
	se(l,mid-1);
	se(mid+1,r);
	if(vis[mid]&&ans[ch[mid][0]]&&ans[ch[mid][1]])ans[mid]=1;
}
int main(){
	cin>>n;
	for(i=1;i<=n;++i){
		for(j=0;j<4;++j)cin>>a[i].a[j];
		a[i].a[2]=-a[i].a[2];
		a[i].a[3]=-a[i].a[3];
	}
	o=-1;
	build(1,n);
	for(i=1;i<=n;++i){
		if(!vis[i])se(1,n);
	}
	for(i=1;i<=n;++i){
		if(vis[i])++z;
		//cout<<ans[i]<<" "<<vis[i]<<endl;
	}
	cout<<n-z;
}
```


---

## 作者：梦回还 (赞：2)

看了看楼下的题解，一个偏玄学（分治什么的我也是一脸懵）；另一个是很优秀的用条件优化暴力的想法，但我以为以n<=50000的数据，要卡一卡还是可以，当然我也很推崇这种做法，代码精简，对于随机数据简直是利器。我还是来讲一讲自己的做法。

对于这一类二维平面中的矩形问题，似乎线段树是个优秀的选择，经常模拟一条扫描线，维护染色的区间，能搞过很多题。对于本题，我们假想有一条扫描线从上往下运动，碰到每一个矩形的上端，先将下端高于上端的矩形踢出，再检查这段区间是否全部被覆盖。若区间已经被覆盖，就可以无视这个矩形；否则就将计数器加一，将这个矩形所在的区间标记。

为什么这样做有显然的正确性？如楼下大佬所说，数据中没有部分重合的矩形，我们仅需要维护一个矩形的上端，左端与右端。通过排序使矩形按照扫描线的顺序一个个进行维护，通过线段树的区间+1和-1对区间染色，套一个优先队列维护矩形退出的顺序，及时更新；查询时只要区间最小值不是0，就说明这个矩形被覆盖了。

（上代码qwq）

```cpp
#include<queue>
#include<vector>
#include<cstdio>
#include<cctype>
#include<climits>
#include<cstring>
#include<algorithm>
#define ls d << 1
#define rs d << 1 | 1
using namespace std;

const int N = 50001, M = 100001;//M是考虑到若所有坐标不一致，数组要开两倍空间
int n, s[M], top, minn[M << 2], ans, lazy[M << 2];
struct Node{
	int u, d, l, r;
	bool operator < (Node &t) {
		return u < t.u;
	}
}a[N];//小于号重定义，只为不打cmp（宝宝押韵好厉害
struct cmp{
	bool operator() (int x, int y) {
		return a[x].d > a[y].d;
	}
};//然而还是为优先队列打了，重写比较函数

int read() {
	int x = 0; char ch = getchar(); bool f = 0;
	while(!isdigit(ch)) {
		if(ch == '-') f = 1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ '0');
		ch = getchar();
	}
	return ! f ? x : -x;
}//超长的读入优化，不想压行嘻嘻~

int found(int x) {
	int l = 1, r = top;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(s[mid] < x) l = mid + 1;
		if(s[mid] > x) r = mid - 1;
		if(s[mid] == x) return mid;
	}
	return 0;
}//离散化必不可少，效率稳定O（nlogn）

void maintain(int d) {
	minn[d] = min(minn[ls], minn[rs]);
	return;
}//线段树组成部分就不解释了

void pushdown(int d) {
	int &x = lazy[d];
	if(x) {
		lazy[ls] += x;
		lazy[rs] += x;
		minn[ls] += x;
		minn[rs] += x;
		lazy[d] = 0;
	}
	return;
}

void update(int l, int r, int d, int L, int R, int k) {
	if(L <= l && r <= R) {
		minn[d] += k;
		lazy[d] += k;
		return;
	}
	pushdown(d);
	int mid = (l + r) >> 1;
	if(L <= mid) update(l, mid, ls, L, R, k);
	if(mid < R) update(mid + 1, r, rs, L, R, k);
	maintain(d);
	return;
}

int query(int l, int r, int d, int L, int R) {
	if(L <= l && r <= R) return minn[d];
	pushdown(d);
	int mid = (l + r) >> 1, mi = INT_MAX;//INT_MAX是climits中的一个值，保存的就是int型最大值，使用很方便，就是要注意不要加别的东西导致溢出
	if(L <= mid) mi = min(mi, query(l, mid, ls, L, R));
	if(mid < R) mi = min(mi, query(mid + 1, r, rs, L, R));
	return mi;
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i].u = read();
		a[i].l = read();
		s[++top] = a[i].l;
		a[i].d = read();
		a[i].r = read();
		s[++top] = a[i].r;
	}
	sort(s + 1, s + top + 1);
	top = unique(s + 1, s + top + 1) - s;//二分查找前一定记得排序去重
	for(int i = 1; i <= n; i++)
		a[i].l = found(a[i].l),
		a[i].r = found(a[i].r);
	sort(a + 1, a + n + 1);
	priority_queue<int, vector<int>, cmp> q;
	for(int i = 1; i <= n; i++) {
		while(!q.empty()) {
			int x = q.top();
			if(a[x].d > a[i].u) break;
				else {
					update(1, top, 1, a[x].l, a[x].r, -1);
					q.pop();
				}
		}
		if(!query(1, top, 1, a[i].l, a[i].r)) ans++;
		update(1, top, 1, a[i].l, a[i].r, 1);
		q.push(i);
	}//循环过程如上述，每次操作都是O（logn),很稳定（小骄傲
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Phartial (赞：2)

### 前言

为啥题解里一堆大佬用的是神仙算法啊。。。

这题不是用扫描线就可以过了吗。。。

### 正文

首先不难得到一个粗略的想法：存下所有矩形的左边界与右边界，然后从左到右扫一遍边界，用一个集合维护当前 $x$ 坐标穿过的矩形的上下边界，则根据当前边界是左边界还是右边界可以分类讨论：

- 若当前边界是左边界：直接插入集合，然后在集合中找到比当前矩形的上边界更高的最矮的矩形上边界，然后判断当前矩形是否包含于此矩形，更新答案。
- 若当前边界是右边界：直接从集合中删除即可。

然而上面这种思想是错误的，Hack 数据如下：

```
3
0 -4 7 3
1 1 6 2
2 -3 4 0
```

可以发现错误原因是因为当计算到第 3 个矩形时程序会误以为第 2 个矩形才有可能包含第 3 个矩形而忽略了第 1 个矩形。

解决方案也很简单，只要每次只让没有被包含的矩形加入集合中即可。

代码如下：

```cpp
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
using Pii = pair<int, int>;

const int kN = 50001;

struct R {
  int l, d, r, u;
} e[kN];

struct L {
  int i, x, u, d;

  bool operator<(const L &o) const {
    return x < o.x;
  }
} a[kN * 2];

int n, ans;
set<Pii> s;

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> e[i].l >> e[i].d >> e[i].r >> e[i].u;
    a[i] = {0, e[i].l, e[i].u, e[i].d}, a[i + n] = {1, e[i].r, e[i].u, e[i].d};  // 存下左右边界
  }
  sort(a + 1, a + 2 * n + 1);  // 以 x 坐标为关键字排序
  for (int i = 1; i <= 2 * n; ++i) {
    if (a[i].i) {                 // 如果当前边界是右边界
      s.erase({a[i].u, a[i].d});  // 直接删除
    } else {
      Pii j = *s.lower_bound({a[i].u, a[i].d});       // 找到第一个可能包含当前矩形的矩形
      if (j.first >= a[i].u && a[i].d >= j.second) {  // 如果包含当前矩形
        ++ans;                                        // 更新答案
      } else {
        s.insert({a[i].u, a[i].d});  // 否则直接插入集合
      }
    }
  }
  cout << n - ans;  // 输出答案
  return 0;
}

```


---

## 作者：Dtw_ (赞：1)

# 思路
题目中说矩形的关系只有相离和包含，所以说只要判断任意一条边即可，所以考虑扫描线。

因为只考虑边的关系，所以没必要用线段树，用个 `set` 维护一下即可。

具体的：

先用结构体存储每个边的性质，按 $x$ 或 $y$ 排序，这里我按的 $x$。访问每条边，如果此边是起始边，则判断一下是否被之前的矩形包含。可以二分出 `set` 里第一个包含当前边的边，设当前边的上下端点为 $a,b$，第一个包含其的边的上下端点为 $x,y$，那么有 $x\geq a,y\leq b$。最后统计出被包含的矩形数量，用总数减掉这个即为答案。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n;

struct Line
{
	int id, x, a, b;
}a[N];

signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		int x, y, p, q;
		cin >> x >> p >> y >> q;
		a[i] = {0, x, q, p}, a[i + n] = {1, y, q, p};
	}
	sort(a + 1, a + 2 * n + 1,[](Line x, Line y) {return x.x < y.x;});
	set<pair<int, int>> S;
	int res = 0;
	for(int i=1; i<=2*n; i++)
	{
		if(a[i].id == 1)
		{
			S.erase({a[i].a, a[i].b});
		}
		else
		{
			auto j = *S.lower_bound({a[i].a, a[i].b});
			if(j.fi >= a[i].a && a[i].b >= j.se)
			{
				res++;
			}
			else
			{
				S.insert({a[i].a, a[i].b});
			}
		}
	}
	cout << n - res;
	return 0;
}



```

---

## 作者：Itst (赞：1)

看到这道题目，是一个四维偏序(如果存在$i,j$满足$x_{i1}<x_{j1},y_{i1}<y_{j1},x_{i2}>x_{j2},y_{i2}>y_{j2}$，那么$j$不会被计入贡献)

#### 那就直接上$CDQ+CDQ+$树状数组的四维偏序就好啦

复杂度$O(nlog^3n)$，我常数过大要开$O2$才能过，被暴力包菜了qaq

关于如何实现四维偏序，稍微提一下

我们在做三个维度$(a,b,c)$求偏序的时候，先对$a$排序，然后保证$b$单调的情况下用树状数组维护$c$的数量，从而求得偏序。在四维偏序中是类似的。

考虑四个维度$(a,b,c,d)$，我们先对$a$排序，假设当前分治到区间$(l,r)$，我们现在要对$b$排序，然后考虑$c,d$两个维度的影响。可是对$b$排序之后$a$就无序了。我们这么处理：排序之前将左半部分区间打上$L$标记，右半部分区间打上$R$标记，用标记代替$a$维度。那么四个维度就变成了$(L/R,b,c,d)$。

这个时候我们对$b$排序，将数组$copy$一份，用新$copy$的数组在$b,c,d$三维上做第二层$CDQ$，注意在第二层$CDQ$中只能是带有$L$标记的点对带有$R$标记的点产生影响，在维护树状数组时判断即可。

$ps:$突然发现$CDQ$分治好好写qwq

代码如下

```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    bool f = 0;
    while(!isdigit(c)){
        if(c == '-')
            f = 1;
        c = getchar();
    }
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return f ? -a : a;
}

const int MAXN = 50010;
struct node{
    //mark表示代替x2维度的L/R标记，mark==0表示L
    //代码中的维度考虑顺序：x2->y2->x1->y1
    int x1 , y1 , x2 , y2 , ind;
    bool mark;
    inline void init(){
        x1 = read();
        y1 = read();
        x2 = read();
        y2 = read();
    }
    bool operator <(const node a)const{
        return x2 > a.x2;
    }
}now[MAXN] , pot[MAXN];
int lshx[MAXN << 1] , lshy[MAXN << 1] , Tree[MAXN << 1] , N , cnt;
bool vis[MAXN];

bool cmp1(node a , node b){
    return a.y2 > b.y2; 
}

bool cmp2(node a , node b){
    return a.x1 < b.x1;
}

inline int lowbit(int a){
    return a & -a;
}

inline void add(int x , int num){
    while(x <= N << 1){
        Tree[x] += num;
        x += lowbit(x);
    }
}

inline bool get(int x){
    while(x){
        if(Tree[x])
            return 1;
        x -= lowbit(x);
    }
    return 0;
}

//第二层CDQ
void CDQ2(int l , int r){
    if(l == r)
        return;
    CDQ2(l , mid);
    CDQ2(mid + 1 , r);
    int p = l , q = mid + 1;
    while(p <= mid && q <= r)
        if(pot[p].x1 < pot[q].x1){
            if(!pot[p].mark)
                add(pot[p].y1 , 1);
            ++p;
        }
        else{
            if(pot[q].mark)
                vis[pot[q].ind] |= get(pot[q].y1);
            ++q;
        }
    while(q <= r){
        if(pot[q].mark)
            vis[pot[q].ind] |= get(pot[q].y1);
        ++q;
    }
    while(--p >= l)
        if(!pot[p].mark)
            add(pot[p].y1 , -1);
    sort(pot + l , pot + r + 1 , cmp2);
}

//第一层CDQ
void CDQ1(int l , int r){
    if(l == r)
        return;
    CDQ1(l , mid);
    CDQ1(mid + 1 , r);
    for(int i = l ; i <= mid ; ++i)
        now[i].mark = 0;
    for(int i = mid + 1 ; i <= r ; ++i)
        now[i].mark = 1;
    sort(now + l , now + r + 1 , cmp1);
    memcpy(pot + l , now + l , sizeof(node) * (r - l + 1));
    CDQ2(l , r);
}

int main(){
    N = read();
    for(int i = 1 ; i <= N ; ++i){
        now[i].init();
        lshx[++cnt] = now[i].x1;
        lshy[cnt] = now[i].y1;
        lshx[++cnt] = now[i].x2;
        lshy[cnt] = now[i].y2;
        now[i].ind = i;
    }
    sort(lshx + 1 , lshx + cnt + 1);
    sort(lshy + 1 , lshy + cnt + 1);
    for(int i = 1 ; i <= N ; ++i){
        now[i].x1 = lower_bound(lshx + 1 , lshx + cnt + 1 , now[i].x1) - lshx;
        now[i].x2 = lower_bound(lshx + 1 , lshx + cnt + 1 , now[i].x2) - lshx;
        now[i].y1 = lower_bound(lshy + 1 , lshy + cnt + 1 , now[i].y1) - lshy;
        now[i].y2 = lower_bound(lshy + 1 , lshy + cnt + 1 , now[i].y2) - lshy;
    }
    sort(now + 1 , now + N + 1);
    CDQ1(1 , N);
    int cnt = N;
    for(int i = 1 ; i <= N ; ++i)
        cnt -= vis[i];
    cout << cnt;
    return 0;
}
```

---

## 作者：_VirtualPoint_ (赞：0)

# 前言或声明
本部分不超过总内容 $20\%$。

- 本题解的参考代码不仅可以通过本题，在经过极度细微的修改之后还可以通过 [P5490](https://www.luogu.com.cn/problem/P5490)。

- 本题解参考代码可能有部分累赘内容，与 [P5490](https://www.luogu.com.cn/problem/P5490) 有关，在这里请大家谅解。

- 本题解假定大家已经对扫描线有一定的了解。如果你还不知道扫描线是什么，我贴心的提供了 [学习链接](https://oiwiki.com/geometry/scanning/)。

- 本题居然还可以写题解？？？

# 分析与思考
本题使用扫描线。怎么想到？我们以后做这种类型题的时候，如果敏锐地注意到题目中有关“矩形”的交错、包含、链接，那大概率就是扫描线或者可以用扫描线解决。

考虑先把所有矩形的所有横向边存起来，每条边存左端点横坐标、右端点横坐标、纵坐标与一个“标记值”。这里标记值干什么的后面会解释，只需要知道对于每个矩形，它上方横向边的标记值是 $-1$，下方横向边的标记值是 $1$。

之后维护一个初始全部为 $0$ 的序列（可以理解为平行于 X 坐标轴的一个线形结构），用一个朴素的扫描线从下往上扫。每碰到一条矩形下方的横向边，把这个边对应在序列上的区间标记。每碰到一条矩形上方的横向边，就把这个边对应在序列上的区间取消标记（因为这个区间之前一定被一条下侧边标记过）。如何实现这个功能？这就是刚刚的标记值的用处。我们用一些方法把标记值累加到序列即可。

之后，我们发现，每碰到一条下侧横向边，就把它压到那个序列里。看看整个序列被标记的总长度有没有增加。如果增加了，就说明这个边的矩形没有被其他矩形包含。

想到了之后，我们就可以开始尝试实现了。

# 提示与实现
如何维护刚刚提到的序列？我提供一种比较奇怪的方式。我们可以用特殊的方式实现一个权值线段树，可以保证即能够维护边的正常标记和取消标记，也能够 $O(1)$ 求出标记的总长度（注意，这里重合部分只计算一次）。这种方式比较玄妙，大家可以看看代码，自己领会。

注意到坐标范围可能很大，所以我们把坐标进行离散化之后再进行标记边等处理。

这里需要打 LazyTag。作者很蒟，代码中的 LazyTag 不是很正规，大家略微看看就好，希望能够谅解。

代码请有需要的同学自行取用，切勿抄题解！这可能导致又一位作弊者的产生。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define lson(x) (x) << 1
#define rson(x) (x) << 1 | 1

long long n;
long long X1, Y1, X2, Y2;

long long ans=0;
long long top1=0;
long long top2=0;

long long tre[3000005];
long long dts[3000005];

long long tag[3000005];

struct line {
	long long l, r, h, v;
	
	bool operator<(const line &oth) const {
		return h < oth.h;
	}
} lne[300005];

void push_up(long long rt, long long nl, long long nr) {
	if (tag[rt] > 0) {
		tre[rt] = dts[nr+1]-dts[nl];
	} else {
		tre[rt] = tre[lson(rt)]+tre[rson(rt)];
	}
}

void update(long long rt, long long nl, long long nr, long long l, long long r, long long fla) {
	if (nr + 1 <= l || nl >= r) {
		return;
	}
	if (l <= nl && nr + 1 <= r) {
		tag[rt] += fla;
		push_up(rt, nl, nr);
		return;
	}
	
	long long mid = (nl + nr) >>1;
	
	if (l <= mid) {
		update(lson(rt), nl, mid, l, r, fla);
	}
	if (r > mid) {
		update(rson(rt), mid+1, nr, l, r, fla);
	}
	
	push_up(rt, nl, nr);
}

int main() {
	cin >> n;
	
	for (long long i = 1; i <= n; i++) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		
		lne[++top1] = (line){X1, X2, Y1, 1};
		dts[top1] = X1;
		lne[++top1] = (line){X1, X2, Y2, -1};
		dts[top1] = X2;
	}
	
	sort(lne+1, lne+top1+1);
	sort(dts+1, dts+top1+1);
	
	long long top2 = unique(dts+1, dts+top1+1)-dts-1;
	
	for (long long i = 1; i < top1; i++) {
		long long L = lower_bound(dts+1, dts+top2+1, lne[i].l)-dts;
		long long R = lower_bound(dts+1, dts+top2+1, lne[i].r)-dts;
		
		long long tmp = tre[1];
		update(1, 0, top2-1, L, R, lne[i].v);
		
		if (tre[1] > tmp) {
			ans++;
		}
	}
	
	cout << ans;
	return 0;
}
```

---

## 作者：ViXbob (赞：0)

 首先，正解肯定不是模拟
 
 我想应该是cdq分治求偏序，我们已知对角点的坐标分别为$(x_1, y_1) (x_2, y_2)$
 
 因为题目中保证矩形与矩形之间不相交，所以为我们只用考虑其中的任意三个参数就可以
 
 再第一维$x_2$排完序以后，我们想知道的是对于每个矩形$i$,有$ans_1$个矩形满足$x_{j, 1} < x_{i, 1}$ && $y_{j, 1} < y_{i, 1}$, 和有$ans_2$个矩形满足$x_{j, 2} < x_{i, 1}$ && $y_{j, 1} < y_{i, 1}$
 
 
 如果$ans_1>ans_2$那么这个点就被覆盖了，否则没有被覆盖
 
 最后拿$n$减去被覆盖的点的个数就是最终的答案了
 
 $PS:$我打了个树套树，空间被卡爆了，所以我想应该是cdq分治，但是我并没学，所以只能给大家提供一个相对正确的思路

---

