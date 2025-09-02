# [JOISC 2021] 道路の建設案 (Road Construction) (Day2)

## 题目背景

10s,2048M

## 题目描述

JOI 国是一个 $x\times y$ 的二维平面，王国里有 $n$ 个城镇，分别编号为 $1, 2, \cdots, n$，其中第 $i$ 个城镇的 **坐标** 为 $(x_i, y_i)$。

在 JOI 国，正计划修建连接两座城镇的路（下文简称：**「修路的项目」**），路有 $k$ 条。连接两个不同的城镇 $a$ 和 $b$ 将花费 $|x_a − x_b| + |y_a − y_b|$ 元。若有一条连接 $c$，$d$ 的路，则不需要也不可以在建一条连接 $d$，$c$ 的路，因为它们是相同的。

你要管理这个「修路的项目」，为了计算花费情况，你得弄明白连接一些城镇所需的花费。在这 $\dfrac{n\cdot(n-1)}{2}$ 条道路中，你想了解最便宜的 $k$ 条道路的花费。

给你城镇的坐标以及 $k$，请计算最便宜的 $k$ 条路所需要的钱。

## 说明/提示

#### 样例 #1 解释
有 $\dfrac{3 \times 2}{2} = 3$ 种方案。

- 城镇 $1 \to$ 城镇 $2$，$|(-1)-0|+|0-2| = 3$ 日元。
- 城镇 $1 \to$ 城镇 $3$，$|(-1)-0|+|0-0| = 1$ 日元。
- 城镇 $2 \to$ 城镇 $3$，$|0-0|+|2-0| = 2$ 日元。

将其进行排序为 $1,2,3$，所以输出是 $1$ 和 $2$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #2 解释

有 $\dfrac{5 \times 4}{2} = 10$ 种方案。

将钱数排序后是 $2, 2, 3, 3, 3, 3, 4, 4, 4, 4$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #3 解释

本样例满足 Subtask $1, 2, 4, 5, 6$。

#### 样例 #4 解释

本样例满足 Subtask $1, 4, 5, 6$。

#### 数据范围与约定

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | $n$ | $k$ | $y_i$ |
| :----: | :----: | :----: | :----:| :----: |
| $1$ | $5\%$ | $\le 10^3$ | / | / |
| $2$ | $6\%$ | / | / | $=0$ |
| $3$ | $7\%$ | / | $=1$ | / |
| $4$ | $20\%$ | / | $\le 10$ | / |
| $5$ | $27\%$ |  / | $\le 10 ^ 5$ | / |
| $6$ | $35\%$ | / | / | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：
- $2 \le n \le 2.5 \times 10^5$；
- $1 \le k \le \min(2.5\times 10^5,\ \dfrac{n\cdot(n-1)}{2}$)；
- $-10^9 \le x_i, y_i \le 10^9$，且 $1 \le i \le n$；
- $(x_i,y_i)\not = (x_j, y_j)$ 且 $1 \le i < j \le n$。

#### 说明

本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 2 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/2021-sp-d2-notice.pdf) [T2 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/road_construction.pdf)。


## 样例 #1

### 输入

```
3 2
-1 0
0 2
0 0
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
5 4
1 -1
2 0
-1 0
0 2
0 -2
```

### 输出

```
2
2
3
3
```

## 样例 #3

### 输入

```
4 6
0 0
1 0
3 0
4 0
```

### 输出

```
1
1
2
3
3
4
```

## 样例 #4

### 输入

```
10 10
10 -8
7 2
7 -8
-3 -6
-2 1
-8 6
8 -1
2 4
6 -6
2 -1
```

### 输出

```
3
3
4
5
6
6
6
7
7
7
```

# 题解

## 作者：_LHF_ (赞：13)

看到题解区都是双 $\log$ 的做法，我提供一种单 $\log$ 的做法。

为了方便，我们先曼哈顿距离转切比雪夫距离。

看到了第 $k$ 大，我们考虑二分答案，考虑如何判断是否合法。

这里我们采取对平面进行分块，假设当前二分的答案为 $d$，我们就每 $d$ 个分成一块。

如何统计答案呢？考虑到直接对于当前点所在的块以及相关的八个方向爆枚一通。

可以证明，这样的复杂度是 $O(n)$ 的。

所以总复杂度 $O(n\log a)$。

不过常数太大了，所以跑得跟两个 $\log$ 估计也差不多。

```cpp
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<vector>
#define ll long long
#define pir pair<ll,ll>
using namespace std;
const int N=5e5+10,P=1e7+7;
vector<pir> v[N];
namespace ht
{
	struct edge{
		int next;
		ll x,y;
	}e[N];
	int first[P],len,q[N],cnt;
	int qry(ll x,ll y,bool p)
	{
		int w=(x*1919+y*811)%P;
		if(w<0) w+=P;
		for(int i=first[w];i;i=e[i].next)
			if(e[i].x==x&&e[i].y==y) return i;
		if(!p) return -1;
		e[++len]=edge{first[w],x,y};
		if(!first[w]) q[++cnt]=w;
		first[w]=len;
		return len;
	}
	void clear()
	{
		for(int i=1;i<=len;i++) v[i].clear();
		for(int i=1;i<=cnt;i++) first[q[i]]=0;
		len=cnt=0;
	}
}
int len,k,p,n;
ll ans[N<<2];
ll calc(ll a,ll b)
{
	if(a>=0) return a/b;
	else return (a+1)/b-1;
}
void push(ll x)
{
	ans[++len]=x;
}
void work(ll d,ll x,ll y,int i)
{
	if(i<0) return;
	if(len>=k&&p) return;
	ll w;
	for(pir a:v[i])
	{
		w=max(abs(a.first-x),abs(a.second-y));
		if(w<=d) push(w);
	}
}
const int f1[10]={0,1,1,1,0,-1,-1,-1,0},f2[10]={0,1,0,-1,-1,-1,0,1,1};
ll x[N],y[N],a,b;
bool chk(ll d)
{
	ht::clear(),len=0;
	for(int i=1;i<=n;i++)
	{
		a=calc(x[i],d),b=calc(y[i],d);
		for(int k=0;k<9;k++)
			work(d,x[i],y[i],ht::qry(a+f1[k],b+f2[k],0));
		v[ht::qry(a,b,1)].push_back({x[i],y[i]});
		if(p&&len>=k) return 1;
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&a,&b),x[i]=a+b,y[i]=a-b;
	ll l=1,r=4e9,mid;
	p=1;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(chk(mid)) r=mid;
		else l=mid+1;
	}
	chk(l);
	sort(ans+1,ans+len+1);
	for(int i=1;i<=k;i++)
		printf("%lld\n",ans[i]);
}
```

---

## 作者：hfjh (赞：11)

# P7561[JOISC 2021 Day2] 道路の建設案 (Road Construction) 题解

## 题目描述

JOI 国是一个 $x\times y$ 的二维平面，王国里有 $n$ 个城镇，分别编号为 $1, 2, \cdots, n \in [1,2.5 \times 10^5]$，其中第 $i$ 个城镇的 **坐标** 为 $(x_i, y_i)$。

在 JOI 国，正计划修建连接两座城镇的路（下文简称：**「修路的项目」**），路有 $k$ 条。连接两个不同的城镇 $a$ 和 $b$ 将花费 $|x_a − x_b| + |y_a − y_b|$ 元。若有一条连接 $c$，$d$ 的路，则不需要也不可以在建一条连接 $d$，$c$ 的路，因为它们是相同的。

你要管理这个「修路的项目」，为了计算花费情况，你得弄明白连接一些城镇所需的花费。在这 $\dfrac{n\cdot(n-1)}{2}$ 条道路中，你想了解最便宜的 $k$ 条道路的花费。

给你城镇的坐标以及 $k$，请计算最便宜的 $k$ 条路所需要的钱。

## 解析

首先你要知道什么是曼哈顿距离和切比雪夫距离及相互转化。

推荐学习[曼哈顿距离与切比雪夫距离的互化](https://www.cnblogs.com/SGCollin/p/9636955.html)。

现在我把点坐标转化后就是要求解这样一个问题：

$$
\max(|x_i-x_j|,|y_i-y_j|)
$$

选出前 $k$ 小。

我们可以二分一下第 $k$ 小的值 $mid$，再 `check` 有没有 $k$ 个距离小于 $mid$。

同时我们不需要真正数有多少点对，点对数 $≥k$ 时直接返回 `true` 即可。

具体操作是先按照 $x$ 排序。

假设当前到了 $x_i$，将所有 $[x_i-mid,x_i]$ 的点放入 `set` 里面，

之前在 $[x_{i-1}-mid,x_{i-1}]$ 里面的但不在 $[x_i-mid,x_i]$ 删掉（用双指针维护）。

然后在 `set` 里面先二分找到 $y_i-mid$，枚举到 $y_i + mid$ ，每枚举到一个就 `++ans`。

当 $ans \ge k$ 的时候就直接 `return `。

最后如何求出答案？

找到第 $k$ 小的值 $mid$ 了之后，再 `check` 一次 $mid-1$，这样一定可以找到小于 $k$ 个长度小于 $mid$ 的长度，最后再用 $mid$ 把 $k$ 补满，就是答案。

因为 $ans \ge k$ 会 `return` 所以严格 $O(n\log n)$。

### 温馨提示

1.因为转化为切比雪夫距离，又要互相加减，所以要开 `long long `。

2.用 `multiset`，因为可能有相同长度。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 3e7 + 10; 
int n, k;
ll x,y,an[N],ans = 0,l,r,mid;
queue<int>q;
struct node{
	ll x, y;
	bool operator <(const node a)const{
		return x < a.x; 
	} 
}p[N];
struct Node{
	ll x, y;
	bool operator <(const Node a)const{
		return y < a.y; 
	} 
};
multiset<Node>s;
void input(){
	cin>>n>>k;
	for(int i = 1; i <= n; ++i){
		cin>>x>>y;
		p[i].x = x - y;
		p[i].y = x + y;
	}
	sort(p + 1,p + 1 + n);
}
bool check(ll mid){
	q = queue<int>();
	s = multiset<Node>();
	ans = 0;
	for(int i = 1; i <= n; ++i){
		while(q.size() && p[i].x - p[q.front()].x > mid){
			multiset<Node>:: iterator w = s.find((Node){0,p[q.front()].y});
			s.erase(w);
			q.pop();
		}	
		multiset<Node>::iterator lz = s.lower_bound((Node){0,p[i].y - mid});
		while(lz != s.end() && (*lz).y <= p[i].y + mid){
			an[++ans] = max(abs((*lz).x - p[i].x),abs((*lz).y - p[i].y));
			if(ans >= k) return 1;
			++lz;
		}
		q.push(i);
		s.insert((Node){p[i].x,p[i].y}); 
	}
	return 0;
}
void op(){
	
	l = 0,r = 4e9,mid;
	while(l < r){
		mid = (l + r) >> 1;
		if(check(mid)){
			r = mid;
		}else{
			l = mid + 1;
		}
	} 
	check(l - 1);
}
void output(){
	sort(an + 1,an + 1 + ans);
	int i;
	for(i = 1; i <= ans; ++i){
		cout<<an[i]<<'\n';
	}
	for(; i <= k; ++i){
		cout<<l<<'\n';
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	input();
	op();
	output();
	return 0;
}
```

---

## 作者：GK0328 (赞：7)

### $\rm KDT$

曼哈顿距离$k$近点对？看起来十分神仙的样子。

但是！我们都会乱搞！

听起来好像有点像[Luogu4357[CQOI2016]K 远点对](https://www.luogu.com.cn/problem/P4357)，但是$k$比较大，我们可以试一试。

对于所有点建$\rm KDT$，然后维护一个堆，一个点一个点枚举，如果堆顶元素小于等于当前节点到询问矩形中可能的最短距离，停止搜索。注意需要去除一个点与自己匹配的贡献。

在$\rm KDT$中查询的时候，一个点到一个矩形的最短距离不再是这个点到矩形四个顶点的最短距离，而是各维度坐标到矩形对应维度边界的绝对值差的最小值之和。

由于询问为无序点对，我们可以在堆中存储$2k$个有序点对的距离，输出时隔一个数依次选取$k$个距离即为答案。

然后我们就草率地通过了这道题，吸氧后最大点仅仅耗时$1.60s$。

$Code:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define N 250005
#define ll long long
using namespace std;
int n,k;
ll ans[N];
struct Point
{
    int x,y;
    Point () {}
    Point (int xx,int yy):x(xx),y(yy) {}
}a[N];
ll dis(Point A,Point B)
{
    return (ll)abs(A.x-B.x)+abs(A.y-B.y);
}
priority_queue<ll>q;
bool cmpX(const Point &A,const Point &B)
{
    return A.x<B.x;
}
bool cmpY(const Point &A,const Point &B)
{
    return A.y<B.y;
}
struct node
{
    int xl,xr,yl,yr;
}tr[N << 2];
void build(int p,int l,int r,bool opt)
{
    if (l==r)
    {
        tr[p].xl=tr[p].xr=a[l].x;
        tr[p].yl=tr[p].yr=a[l].y;
        return;
    }
    int mid(l+r >> 1);
    nth_element(a+l,a+mid,a+r+1,(!opt)?cmpX:cmpY);
    build(p << 1,l,mid,!opt),build(p << 1 | 1,mid+1,r,!opt);
    tr[p].xl=min(tr[p << 1].xl,tr[p << 1 | 1].xl);
    tr[p].xr=max(tr[p << 1].xr,tr[p << 1 | 1].xr);
    tr[p].yl=min(tr[p << 1].yl,tr[p << 1 | 1].yl);
    tr[p].yr=max(tr[p << 1].yr,tr[p << 1 | 1].yr);
}
void ckmax(int &x,int y)
{
    x=(x>y)?x:y;
}
void calc(int p,int l,int r,int x)
{
    if (q.size()==k)
    {
        ll D=0;
        if (tr[p].xl>a[x].x || tr[p].xr<a[x].x)
            D+=min(abs(a[x].x-tr[p].xl),abs(a[x].x-tr[p].xr));
        if (tr[p].yl>a[x].y || tr[p].yr<a[x].y)
            D+=min(abs(a[x].y-tr[p].yl),abs(a[x].y-tr[p].yr));
        if (D>=q.top())
            return;
    }
    if (l==r)
    {
        ll D=dis(a[x],Point(tr[p].xl,tr[p].yl));
        if (!D)
            return;
        if (q.size()==k)
            q.pop();
        q.push(D);
        return;
    }
    int mid(l+r >> 1);
    calc(p << 1,l,mid,x);
    calc(p << 1 | 1,mid+1,r,x);
}
int main()
{
    scanf("%d%d",&n,&k);
    k=k << 1;
    for (int i=1;i<=n;++i)
        scanf("%d%d",&a[i].x,&a[i].y);
    build(1,1,n,0);
    for (int i=1;i<=n;++i)
        calc(1,1,n,i);
    for (int i=1;i<=(k >> 1);++i)
        ans[i]=q.top(),q.pop(),q.pop();
    for (int i=(k >> 1);i;--i)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：Daniel13265 (赞：4)

> 给定平面上 $n$ 个点 $\left(x_i,y_i\right)$，求曼哈顿距离前 $k$ 小的无序点对。
>
> $2\le n\le2.5\times10^5$，$1\le k\le\min\left(2.5\times 10^5,\ \dfrac{n\cdot(n-1)}{2}\right)$，$\left|x_i\right|,\left|y_i\right|\le10^9$。

设定阈值 $m\ge k$。二分距离 $d$ 并求出曼哈顿距离小于等于 $d$ 的点对的距离。求这些距离的过程中一旦发现点对个数超过 $m$ 就立刻退出并缩小 $d$；如果点对个数不到 $k$ 就增大 $d$；否则选择前 $k$ 小距离即可。假设 $\left|x_i\right|,\left|y_i\right|\le a$，那么使用数组存储这些距离并最后求出前 $k$ 小可以做到时间复杂度 $O\left(\left(n\log n+m\right)\log a+k\log k\right)$，空间复杂度 $O\left(n+m\right)$ ；使用堆动态维护前 $k$ 小可以做到时间复杂度 $O\left(\left(n\log n+m\log k\right)\log a\right)$，空间复杂度 $O\left(n+k\right)$。理论上 $m=k$ 时最优，但是值得注意的是 $m$ 增大时，二分的次数就会相应地减小。

关于二分距离 $d$ 后求出曼哈顿距离小于等于 $d$ 的点对：可以转化为切比雪夫距离后将点按照横坐标为第一关键字，纵坐标为第二关键字排序，然后使用双指针得到横坐标在范围内的其他点。维护按照纵坐标排序的 `std::set`，那么只需要依序遍历纵坐标也在范围内的点即可。

代码写起来很简单，不放了。

---

## 作者：Purslane (赞：2)

# Solution

首先转为切比雪夫距离，这样两点距离为 $\max\{|x_i-x_j|,|y_i-y_j|\}$。

考虑二分答案，判定有多少对距离小于等于 $mid$，也就相当于两维的距离差都小于等于 $mid$。

直接按照第一维排序，用双指针维护当前 $x$ 合法的数，然后暴力加入 $y$ 合法的数。如果你发现超过了 $k$ 个就停止。

于是你判定一次就是 $O(n \log n)$ 量级的。

二分答案，变为 $O(n \log^2 n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2.5e5+10;
struct Node {int x,y;}t[MAXN];
int n,k,cnt;
vector<int> ans;
multiset<pair<int,int>> st;
int check(int len) {
	ans.clear(),st.clear();
	int pos=1; cnt=0;
	ffor(i,1,n) {
		if(i-1) st.insert({t[i-1].y,i-1});
		while(t[i].x-t[pos].x>len) st.erase({t[pos].y,pos}),pos++;
		auto it=st.lower_bound({t[i].y-len,0});
		while(it!=st.end()&&it->first<=t[i].y+len) {
			cnt++,ans.push_back(max(abs(t[i].y-it->first),abs(t[i].x-t[it->second].x))),it++;
			if(cnt>k) return 0;
		}
	}
	return 1;
}
void bfind(int l,int r) {
	int aans=0;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) aans=mid,l=mid+1;
		else r=mid-1;
	}
	check(aans);
	ffor(i,1,k-cnt) ans.push_back(aans+1);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) {int x,y; cin>>x>>y,t[i]={x+y,x-y};}
	sort(t+1,t+n+1,[](Node A,Node B) {
		if(A.x!=B.x) return A.x<B.x;
		return A.y<B.y;	
	});
	bfind(1,4000000000);
	sort(ans.begin(),ans.end());
	for(auto v:ans) cout<<v<<'\n';
	return 0;
}
```

---

## 作者：7KByte (赞：2)

这应该是 JOISC2021 最简单的一题了。

求前 $k $ 大的曼哈顿距离，先考虑求第 $k$ 大的距离。

第 $k$ 大的距离，比较套路的做法是二分答案，然后计算距离 $\le dis$ 的点对数。

曼哈顿距离不好求，考虑转化为切比雪夫距离，原来的点 $(x,y)\to (x+y,x-y)$ 。

那么这就是一个经典的二维数点问题。

同时我们不需要真正数有多少点对，点对数 $\ge k$ 时直接返回即可。

所以具体操作是对所有点按 $x$ 坐标排序，用队列维护 $x$ 坐标在 $dis$ 范围内的点，同时用 ``set`` 维护队列中的点的 $y$ 坐标。

值域为 $S$ ，则时间复杂度为 $\mathcal{O}((n+k)\log n\log S+k\log k)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 250005
#define inf 0x3f3f3f3f3f3f3f3fLL
#define int long long
using namespace std;
int n,k;
typedef pair<int,int> Pr;
#define X first
#define Y second
set<Pr>s;queue<Pr>q;Pr a[N];
int ans[N],T;
bool check(int dis){
	T=0;s.clear();
	while(!q.empty())q.pop();
	rep(i,1,n){
		while(!q.empty()&&q.front().X+dis<a[i].X)s.erase(make_pair(q.front().Y,q.front().X)),q.pop();
		set<Pr>::iterator it=s.lower_bound(make_pair(a[i].Y-dis,-inf));
		while(it!=s.end()&&(*it).X<=dis+a[i].Y){
			ans[++T]=max(abs((*it).X-a[i].Y),a[i].X-(*it).Y);
			it++;if(T>=k)return true;
		}
		s.insert(make_pair(a[i].Y,a[i].X));q.push(make_pair(a[i].X,a[i].Y));
	}
	return false;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	rep(i,1,n){
		int x,y;scanf("%lld%lld",&x,&y);
		a[i].X=x+y;a[i].Y=x-y;
	}
	sort(a+1,a+n+1);puts("No Copy");
	int l=1,r=4000000000,ed=0;
	while(l<=r){
		int mid=(0LL+l+r)>>1;
		if(check(mid))ed=mid,r=mid-1;
		else l=mid+1;
	}
	check(ed-1);
	sort(ans+1,ans+T+1);
	rep(i,1,T)printf("%lld\n",ans[i]);
	rep(i,1,k-T)printf("%lld\n",ed);
	return 0;
} 
```

---

## 作者：Corzica (赞：1)

先将题目中的曼哈顿距离转化成切比雪夫距离。

进行二分，找到最大的一个数满足合法点对数量小于等于 $m$，考虑怎么进行 $check$。

对于切比雪夫距离而言，我们一定有两个点的纵坐标和横坐标差均小于等于 $mid$。

考虑可持久化线段树。将所有点按照 $x$ 坐标大小排序，在线段树上对自己的 $y$ 坐标加 $1$，符合条件的点对可以表示为两个线段树上的区间相减。

输出的时候暴力找到所有点对即可。

时间复杂度 $n\log^2n$。

但是万恶的卡常邪神直接让我们的程序得到了高达 38pts 的分数，可以使用一些方法进行优化：

- 若当前的点对数量大于 $m$，直接返回。
- 查询两个线段树相减时，同时在两颗线段树上查询。

然后就能通过这题啦。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node {
	int l, r, ls, rs, sum;
} b[40000007];
int n, m;
struct dot {
	ll x, y;
	int name;
} a[250005];
ll x[250005], y[250005];
int cx, cy, ccnt, rt[250005];
inline int gdx(ll p) {
	if (x[1] > p) return 0;
	return upper_bound(x + 1, x + cx + 2, p) - x - 1;
}
inline int gux(ll p) {
	return upper_bound(x + 1, x + cx + 2, p - 1) - x;
}
inline int gdy(ll p) {
	return upper_bound(y + 1, y + cy + 2, p) - y - 1;
}
inline int guy(ll p) {
	return upper_bound(y + 1, y + cy + 2, p - 1) - y;
}
inline int gx(ll p) {
	return lower_bound(x + 1, x + cx + 1, p) - x;
}
inline int gy(ll p) {
	return lower_bound(y + 1, y + cy + 1, p) - y;
}
inline bool cmpx(dot p, dot q) {
	return p.x < q.x;
}
inline bool cmpy(dot p, dot q) {
	return p.y < q.y;
}
inline int change(int p, int q, int w, int flg) {
	if (flg) {
		b[++ccnt] = b[p];
		p = ccnt;
	}
	if (b[p].l == b[p].r) {
		b[p].sum += w;
		return p;
	}
	b[p].sum += w;
	int mid = (b[p].l + b[p].r) >> 1;
	if (q <= mid) {
		if (!b[p].ls) {
			b[p].ls = ++ccnt;
			b[ccnt] = node{b[p].l, mid, 0, 0, 0};
			flg = 0;
		}
		b[p].ls = change(b[p].ls, q, w, flg);
	} else {
		if (!b[p].rs) {
			b[p].rs = ++ccnt;
			b[ccnt] = node{mid + 1, b[p].r, 0, 0, 0};
			flg = 0;
		}
		b[p].rs = change(b[p].rs, q, w, flg);
	}
	return p;
}
inline int query(int p, int q, int l, int r) {
	if (p == q) return 0;
	if (b[p].l >= l && b[p].r <= r) return b[p].sum - b[q].sum;
	int mid = (b[p].l + b[p].r) >> 1;
	if (r <= mid) return query(b[p].ls, b[q].ls, l, r);
	else if (l > mid) return query(b[p].rs, b[q].rs, l, r);
	return query(b[p].ls, b[q].ls, l, mid) + query(b[p].rs, b[q].rs, mid + 1, r);
}
inline ll solve(ll mid) {
	ll cnt = 0	;
	ccnt = rt[0] = 1;
	b[1] = node{1, cy, 0, 0, 0};
	sort(a + 1, a + n + 1, cmpx);
	a[0].x = a[1].x - 1;
	int op;
	op = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].x != a[i - 1].x) {
			rt[op + 1] = rt[op];
			op++;
		}
		cnt += query(rt[op], rt[gdx(a[i].x - mid - 1)], guy(a[i].y - mid), gdy(a[i].y + mid)) ;
		if (cnt > m) return m + 1;
		rt[op] = change(rt[op], gy(a[i].y), 1, 1);
	}
	return cnt;
}
vector<ll> ans;
set<int> son[250005];
inline void print(ll p) {
	sort(a + 1, a + n + 1, cmpx);
	int r = 1;
	for (int i = 1; i <= n; i++) {
		while (r < i && a[i].x - a[r].x > p) {
			son[gy(a[r].y)].erase(r);
			r++;
		}
		for (int j = guy(a[i].y - p); j <= gdy(a[i].y + p); j++) {
			for (int k : son[j]) {
				ans.push_back(max(a[i].x - a[k].x, abs(a[i].y - a[k].y)));
			}
		}
		son[gy(a[i].y)].insert(i);
	}
	sort(ans.begin(), ans.end());
	m -= ans.size();
	for (ll i : ans) cout << i << "\n";
	while ((m--) >= 1) cout << p + 1 << "\n";
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
		a[i] = dot{a[i].x - a[i].y, a[i].x + a[i].y};
		x[i] = a[i].x, y[i] = a[i].y;
		a[i].name = i;
	}
	sort(x + 1, x + n + 1), sort(y + 1, y + n + 1);
	cx = unique(x + 1, x + n + 1) - x - 1, cy = unique(y + 1, y + n + 1) - y - 1;
	x[cx + 1] = y[cy + 1] = 4000000000;
	ll l = 0, r = 4000000000, mid;
	while (l < r) {
		mid = (l + r + 1) >> 1;
		if (solve(mid) <= m) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	print(l);
}
```

---

## 作者：takanashi_mifuru (赞：1)

### 简要题意

一个平面上共 $n$ 个点，求出前 $k$ 小的两点之间的曼哈顿距离

### 思路

曼哈顿距离非常愚蠢，所以我们考虑转成切比雪夫距离。即 $\left(x,y\right)$ 转化为 $\left(x+y,x-y\right)$，此时两点的切比雪夫距离就是原图上的曼哈顿距离。

我们考虑二分出第 $k$ 小的曼哈顿距离——这个明显是有单调性的——考虑 check 怎么写。

先设我这次二分出来的值为 $mid$，在 check 里面我们只关心有多少点对而不关心点对的距离，那么我们很容易就能想到先用尺取法筛掉 $x$ 的间隔超过 $mid$ 的点，对于我新加入进来的点 $rt$，查询出目前还在我尺取的区间内的点中，$y$ 坐标在 $\left[y_{rt}-mid,y_{rt}+mid\right]$ 之内的点有多少个，这个东西可以离散化后丢进 BIT 里面。

二分出第 $k$ 小的曼哈顿距离后，用上述方法尺取，但是我们现在只关心点对的距离，所以我们开 $n$ 个 set，$st_i$ 存储满足 $y_j=i$ 的 $x_j$。

然后在 $\left[y_{rt}-mid,y_{rt}+mid\right]$ 的 set 里面查出 $x$ 的表丢进小根堆就行了。

时间复杂度 $O\left(n \log^2 n\right)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k,pos;
struct node
{
    int x, y,id;
} a[250005];
bool cmp(node a, node b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cmp2(node a,node b){
    return a.y<b.y;
}
int val[250005];
unordered_map<int,int> mp;
inline int findsuf(int x){
    int lt=0,rt=pos+1;
    while(lt+1<rt){
        int mid=lt+rt>>1;
        if(val[mid]>=x){
            rt=mid;
        }
        else{
            lt=mid;
        }
    }
    return rt;
}
inline int findpre(int x){
    int lt=0,rt=pos+1;
    while(lt+1<rt){
        while(lt+1<rt){
            int mid=lt+rt>>1;
            if(val[mid]>x){
                rt=mid;
            }
            else{
                lt=mid;
            }
        }
    }
    return lt;
}
set<int> st[250005];
multiset<int> q;
bool tag;
class BIT{
    public:
    int c[250005];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x,int y){
        while(x<=pos){
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
    int query(int x,int y){
        return ask(y)-ask(x-1);
    }
    void clean(){
        for(int i=1;i<=pos;i++){
            c[i]=0;
        }
        return;
    }
}P;
inline bool check(int X){
    P.clean();
    int sum=0;
    int lt=1,rt=0;
    while(rt<n){
        rt++;
        while(lt<rt&&a[rt].x-a[lt].x>X){
            P.add(mp[a[lt].y],-1);
            lt++;
        }
        int L=findsuf(a[rt].y-X);
        int R=findpre(a[rt].y+X);
        sum+=P.query(L,R);
        P.add(mp[a[rt].y],1);
    }
    return sum>=k;
}
inline bool getans(int X){
    q.clear();
    for(int i=1;i<=pos;i++){
        st[i].clear();
    }
    int lt=1,rt=0;
    int sum=0;
    while(rt<n){
        rt++;
        while(lt<rt&&a[rt].x-a[lt].x>X){
            st[mp[a[lt].y]].erase(a[lt].x);
            lt++;
        }
        int L=findsuf(a[rt].y-X);
        int R=findpre(a[rt].y+X);
        for(int i=L;i<=R;i++){
            for(int v:st[i]){
                if(max(abs(a[rt].y-val[i]),abs(v-a[rt].x))<=X){
                    q.insert(max(abs(a[rt].y-val[i]),abs(v-a[rt].x))),sum++;
                    if(q.size()>k){
                        q.erase(q.begin(),q.begin());
                    }
                }
            }
        }
        st[mp[a[rt].y]].insert(a[rt].x);
    }
    return sum>=k;
}
signed main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i].x,&a[i].y);
        int tmpx=a[i].x+a[i].y;
        int tmpy=a[i].x-a[i].y;
        a[i].x=tmpx;
        a[i].y=tmpy;
    }
    sort(a + 1, a + 1 + n, cmp2);
    pos=1;
    val[pos]=a[1].y;
    mp[a[1].y]=pos;
    for(int i=2;i<=n;i++){
        if(a[i].y!=a[i-1].y){
            pos++;
            mp[a[i].y]=pos;
            val[pos]=a[i].y;
        }
    }
    sort(a+1,a+1+n,cmp);
    int lt=0,rt=4000000000+1;
    while(lt+1<rt){
        int mid=lt+rt>>1;
        if(check(mid)){
            rt=mid;
        }
        else{
            lt=mid;
        }
    }
    tag=true;
    getans(rt);
    for(int v:q){
        printf("%lld\n",v);
        k--;
        if(!k)break;
    }
    return 0;
}
```

---

## 作者：rmxsxhl (赞：0)

## 简述

看了目前的题解，要么是从曼哈顿距离转成切比雪夫距离再计算，要么是用 `KD-Tree` 等，还有对平面进行分治再计算的。这里提供一个很简单的做法，供大家参考。


## 平面最近点对

我们知道，在计算平面最近点对时，有一个简单的做法是：

- 先求任意一个点对的距离，获得初始的最小距离 $min\_dis$

- 对所有点，按 $x$ 从小到大的顺序排序，如果 $x$ 相等，再按 $y$ 从小到大。

- 按顺序遍历所有点，

  - 对于已经遍历过的点，放在一个先按 $y$ 再按 $x$ 排序的 `set` 里

  -  当遍历到第 $i$ 个点时，获得 `set` 里区间 $[pt[i].y - min\_dis, pt[i].y + min\_dis]$ 的所有点：
 
      - 如果此点距离 $pt[i].x$ 超过 $min\_dis$ ，从 `set` 删除
      - 否则此点与 $pt[i]$ 计算距离，是否可以替代 $min\_dis$
  - 把第 $i$ 点放进 `set` 
- 直到所有点遍历完成，最小点对也计算出来了

## 题解

本题也是同样思路，只是把所有计算过的点对的距离放入
一个优先队列。

如果优先队列的个数不足 $K$ ，那么我们要跟 `set` 里所有点进行计算

如果优先队列的个数达到 $K$ ，那么我们把第 $K$ 个距离，也就是优先队列的 $top$ 值( $lim$ )当作之前平面点对的 $min\_dis$ 一样，删除 $x$ 差距过大的点，只跟 $y$ 距离范围在 $lim$ 之内的点计算。

## 参考代码 

```cpp
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <bitset>

using namespace std;

typedef long long lld;

int getIt() {
    int ans = 0, sign = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') {
            sign = -sign;
        }
        ch = getchar();
    }
    while (isdigit(ch)) {
        ans = ans * 10 + ch - '0';
        ch = getchar();
    }
    return ans * sign;
}

const int kSiz = 2.5e5 + 10;
const lld kInf = 1e16 + 10;

struct Point {
    lld x, y;
    bool operator<(const Point& o) const {
        if (y != o.y) {
            return y < o.y;
        }
        return x < o.x;
    }
};

int N, K;
Point pt[kSiz];
lld ans[kSiz];
priority_queue<lld> pq;

bool cmp(const Point& a, const Point& b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

void read() {
    N = getIt();
    K = getIt();
    for (int i = 1; i <= N; i++) {
        pt[i].x = getIt();
        pt[i].y = getIt();
    }
    sort(pt + 1, pt + 1 + N, cmp);
}

lld getLim() {
    if (pq.size() < K) {
        return kInf;
    }
    return pq.top();
}

void addResult(lld d) {
    pq.push(d);
    if (pq.size() > K) {
        pq.pop();
    }
}

lld dist(const Point& a, const Point& b) {
    lld d = abs(a.x - b.x);
    d += abs(a.y - b.y);
    return d;
}

void work() {
    set<Point> st;

    Point o = { 0 };
    for (int i = 1; i <= N; i++) {
        lld lim = getLim();
        o.y = pt[i].y - lim;
        auto it = st.lower_bound(o);
        while (it != st.end() && it->y <= pt[i].y + lim) {
            if (it->x < pt[i].x - lim) {
                it = st.erase(it);
            }
            else {
                lld d = dist(*it, pt[i]);
                if (d <= lim) {
                    addResult(d);
                    lim = getLim();
                }
                it++;
            }
        }
        st.insert(pt[i]);
    }

    while (!pq.empty()) {
        ans[pq.size()] = pq.top();
        pq.pop();
    }
    for (int i = 1; i <= K; i++) {
        printf("%lld\n", ans[i]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);

    // freopen("test.in", "r", stdin);

    read();
    work();

    return 0;
}
```

----

[目前的最优解](https://www.luogu.com.cn/record/227693097)  374ms

---

## 作者：Miss_SGT (赞：0)

单 $\log$ 为什么这么慢？

前 $k$ 小的套路是，对于每一个点找到最优的，放进堆里，每次取最小的，然后拓展（第二优、第三优。。。）。

这个题，我们可以用主席树轻松找到每个点最优的。问题在怎么在线找到次优的。因为主席树有依赖关系，不能直接删除最优的。但是我们可以每次删除时，新建一条根节点到叶子的链，这样就不会影响其他的了。

注意 $y$ 相等时要钦定一个顺序，其实直接排序不去重即可。主席树要先建完再删除。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2.5e5+5;
#define ll long long
const ll inf=1ll<<40;
int n,k,root1[N],root2[N],tot;
struct node{int x,y;}a[N],w[N];
inline bool cmp(node x,node y){return x.x<y.x;}
struct Tree{
	int ls,rs;
	ll v;
}t[N*100];
#define mid ((l+r)>>1)
void change(int &p,int l,int r,int x,ll v){
	t[++tot]=t[p],p=tot;
	t[p].v=min(t[p].v,v);
	if(l<r){
		if(x<=mid) change(t[p].ls,l,mid,x,v);
		else change(t[p].rs,mid+1,r,x,v);
	}
}
struct po{
	ll res;
	int i,op;
	inline bool operator<(po y)const{return res>y.res;}
};
priority_queue<po> hp;
ll query(int p,int l,int r,int lt,int rt){
	if(!p||(lt<=l&&r<=rt)||t[p].v==inf) return t[p].v;
	ll ans=inf;
	if(lt<=mid) ans=query(t[p].ls,l,mid,lt,rt);
	if(mid<rt&&t[t[p].rs].v<ans) ans=min(ans,query(t[p].rs,mid+1,r,lt,rt));
	return ans;
}
void del(int &p,int l,int r,int lt,int rt,ll v){
	t[++tot]=t[p],p=tot;
	if(l==r) return t[p].v=inf,void();
	if(lt<=mid&&(rt<=mid||(lt<=l&&t[t[p].ls].v==v)||(r<=rt&&t[t[p].rs].v!=v))) del(t[p].ls,l,mid,lt,rt,v);
	else del(t[p].rs,mid+1,r,lt,rt,v);
	t[p].v=min(t[t[p].ls].v,t[t[p].rs].v);
}
inline ll getl(int i){
	if(a[i].y==1) return inf;
	ll res=query(root1[i],1,n,1,a[i].y-1);
	del(root1[i],1,n,1,a[i].y-1,res);
	return res+a[i].x+w[a[i].y].x;
}
inline ll getr(int i){
	if(a[i].y==n) return inf;
	ll res=query(root2[i],1,n,a[i].y+1,n);
	del(root2[i],1,n,a[i].y+1,n,res);
	return res+a[i].x-w[a[i].y].x;
}
int main(){
	read(n),read(k);
	for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i) w[i]={a[i].y,i};
	sort(w+1,w+n+1,cmp);
	for(int i=1;i<=n;++i) a[w[i].y].y=i;
	t[0].v=inf;
	for(int i=1;i<=n;++i){
		change(root1[i]=root1[i-1],1,n,a[i].y,-a[i].x-w[a[i].y].x);
		change(root2[i]=root2[i-1],1,n,a[i].y,-a[i].x+w[a[i].y].x);
	}
	for(int i=1;i<=n;++i){
		hp.push((po){getl(i),i,1});
		hp.push((po){getr(i),i,2});
	}
	while(k--){
		po u=hp.top();hp.pop();
		print(u.res),pc('\n');
		if(u.op==1) hp.push((po){getl(u.i),u.i,1});
		else hp.push((po){getr(u.i),u.i,2});
	}
	flush();
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7561)

# 前置知识

[K-D Tree](https://oi-wiki.org/ds/kdt/)

# 解法

观察到所求是一个邻域查询的形式，尝试使用 KD-Tree，但需注意最坏时间复杂度并不正确（因为本题数据稍弱所以可以通过）。

同 [luogu P2093 [国家集训队] JZPFAR](https://www.luogu.com.cn/problem/P2093)，不妨开一个大小为 $2k$ 的堆加入答案时不断和堆顶比较，在输出答案时跳着取答案。

启发式搜索时估价函数取到子矩形的最近距离即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll inf=0x7f7f7f7f7f7f7f7f;
struct node
{
	int pos[2];
}a[250010];
int cur,cnt=0;
ll ans[250010];
priority_queue<ll>q;
bool cmp(node x,node y)
{
	return x.pos[cur]<y.pos[cur];
}
ll get_dis(int x,int y)
{
	return llabs(a[x].pos[0]-a[y].pos[0])+llabs(a[x].pos[1]-a[y].pos[1]);
}
struct KDT
{
	int root;
	struct kd_tree
	{
		int ls,rs,pos[2],mx[2],mn[2];
	}tree[250010];
	#define lson(rt) (tree[rt].ls)
	#define rson(rt) (tree[rt].rs)
	int build_rt(int id)
	{
		int rt=id;
		lson(rt)=rson(rt)=0;
		for(int i=0;i<=1;i++)
			tree[rt].pos[i]=tree[rt].mx[i]=tree[rt].mn[i]=a[id].pos[i];
		return rt;
	}
	void pushup(int rt)
	{
		for(int i=0;i<=1;i++)
		{
			tree[rt].mx[i]=tree[rt].mn[i]=tree[rt].pos[i];
			if(lson(rt)!=0)
			{
				tree[rt].mx[i]=max(tree[rt].mx[i],tree[lson(rt)].mx[i]);
				tree[rt].mn[i]=min(tree[rt].mn[i],tree[lson(rt)].mn[i]);
			}
			if(rson(rt)!=0)
			{
				tree[rt].mx[i]=max(tree[rt].mx[i],tree[rson(rt)].mx[i]);
				tree[rt].mn[i]=min(tree[rt].mn[i],tree[rson(rt)].mn[i]);
			}
		}
	}
	void build(int &rt,int l,int r,int dir)
	{
		int mid=(l+r)/2;  cur=dir;
		nth_element(a+l,a+mid,a+r+1,cmp);  rt=build_rt(mid);
		if(l<=mid-1)  build(lson(rt),l,mid-1,dir^1);
		if(mid+1<=r)  build(rson(rt),mid+1,r,dir^1);
		pushup(rt);
	}
	ll cost(int rt,int pos)
	{
		ll ans=0;
		for(int i=0;i<=1;i++)
		{
			if(a[pos].pos[i]<tree[rt].mn[i])  ans+=tree[rt].mn[i]-a[pos].pos[i];
			if(a[pos].pos[i]>tree[rt].mx[i])  ans+=a[pos].pos[i]-tree[rt].mx[i];
		}
		return ans;
	}
	void query(int rt,int l,int r,int pos)
	{
		int mid=(l+r)/2;
		if(rt!=pos&&get_dis(rt,pos)<q.top())
		{
			q.pop();  q.push(get_dis(rt,pos));
		}
		ll fl=((l<=mid-1)?cost(lson(rt),pos):inf);
		ll fr=((mid+1<=r)?cost(rson(rt),pos):inf); 
		if(fl<q.top()&&fr<q.top())
		{
			if(fl<fr)
			{
				query(lson(rt),l,mid-1,pos);
				if(fr<q.top())  query(rson(rt),mid+1,r,pos);
			}
			else
			{
				query(rson(rt),mid+1,r,pos);
				if(fl<q.top())  query(lson(rt),l,mid-1,pos);
			}
		}
		else  if(fl<q.top())  query(lson(rt),l,mid-1,pos);
		else  if(fr<q.top())  query(rson(rt),mid+1,r,pos);
	}
}K;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,k,i;
	cin>>n>>k;  k*=2;
	for(i=1;i<=n;i++)  cin>>a[i].pos[0]>>a[i].pos[1];
	for(i=1;i<=k;i++)  q.push(inf);
	K.build(K.root,1,n,0);
	for(i=1;i<=n;i++)  K.query(K.root,1,n,i);
	for(i=k;i>=1;i--)
	{
		ans[i]=q.top();  q.pop();
	}
	for(i=1;i<=k;i+=2)  cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

比较暴力的 2log 做法，但是经过各种卡常成功过了。

我们考虑开一个优先队列装一个三元组 $(i,k,val_k)$ 表示距离点 $(x_i,y_i)$ 第 $k$ 远的点距离为 $val_k$，然后每次取出 $val$ 最小的点，然后再把 $(i,k+1,val_{k+1})$ 塞进去即可。

需要注意的一点是，这样子一条线段 $(x_i,y_i)-(x_j,y_j)$ 会被记两遍，但是我们实际上只能输出一遍，解决方案是，我们只输出第奇数次取出的 $val$ 即可。

则现在关键问题是，然后找到距离点 $(x,y)$ 第 $k$ 远的点。

我们考虑曼哈顿转切比雪夫，然后二分，看一下 $[x-mid,x+mid]-[y-mid,y+mid]$ 间是否有 $\ge k$ 个点，主席树显然能做。

然后就做完了，复杂度 $\Theta((n+k)\log{V}\log{n})$。

再说一下如何卡常：

1. 超级快读 & 快输。
2. 查询 $[x-mid,x+mid]-[y-mid,y+mid]$ 点的数量时要把两个历史版本的树同时递归，这样子能少 $\frac{1}{2}$ 的常数。
3. 对于每个节点记一个值 $f$ 表示距离第 $k$ 远的点的距离，下一次二分就从 $l=f$ 开始。
4. 同理记一下距离的 $k+1$ 远的点的上限 $g$，下一次二分从 $r=g$ 开始。
5. 开 C++98。

然后就能过了！

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define uint unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
void file_IO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N=2.5e5+5;
namespace IO {
	char Is[(1<<21)+10],Os[(1<<21)+10];
	int Ipt,Opt;
	inline char gc() {
		if(Ipt==1<<21)
			Ipt=0;
		if(!Ipt)
			Is[fread(Is,1,1<<21,stdin)]=0;
		return Is[Ipt++];
	}
	inline void flush() {
		fwrite(Os,1,Opt,stdout);
		Opt=0;
	}
	inline void pc(char x) {
		if(Opt==1<<21)
			flush();
		Os[Opt++]=x;
	}
	inline int read() {
		int x=0,f=1;
		char ch=gc();
		while(ch<'0'||ch>'9') {
			if(ch=='-')
				f=-1;			
			ch=gc();
		}
		while(ch<='9'&&ch>='0')
			x=x*10+ch-'0',ch=gc();
		return x*f;
	}
	void write(ll x) {
		if(x>9)
			write(x/10);
		pc(x%10+48);
	}
}
using namespace IO;
PII a[N];
int n,k,t[N],t1[N],p[N],len;
inline int get_id(int x) {
	return lower_bound(t+1,t+len+1,x)-t;
}
struct PSGT {
	struct node {
		int lson,rson,val;
	}; node tree[N*20];
	int p;
	inline int new_node(int k) {
		tree[++p]=tree[k];
		return p;
	}
	void update(int &k,int l,int r,int qx,int val) {
		k=new_node(k);
		tree[k].val+=val;
		if(l==r)
			return;
		int mid=l+((r-l)>>1);
		if(qx<=mid)
			update(tree[k].lson,l,mid,qx,val);
		else
			update(tree[k].rson,mid+1,r,qx,val);
	}
	int query(int kl,int kr,int l,int r,int ql,int qr) {
		if(!(tree[kr].val-tree[kl].val))
			return 0;
		if(ql<=l&&r<=qr)
			return tree[kr].val-tree[kl].val;
		int mid=l+((r-l)>>1),res=0;
		if(ql<=mid)
			res=query(tree[kl].lson,tree[kr].lson,l,mid,ql,qr);
		if(qr>=mid+1)
			res+=query(tree[kl].rson,tree[kr].rson,mid+1,r,ql,qr);
		return res;
	}
	int root[N],cnt;
	inline void ins(int x,int val) {
		++cnt;
		root[cnt]=root[cnt-1];
		update(root[cnt],1,len,x,val);
	}
	inline int query(int _l,int _r,int l,int r) {
		if(_l>_r||l>r)
			return 0;
		l=get_id(l); r=get_id(r+1)-1;
		return query(root[_l-1],root[_r],1,len,l,r);
	}
}; PSGT T;
map<ll,int> used;
inline int get_id(int x,bool op) {
	if(!op)
		return lower_bound(t1+1,t1+n+1,x)-t1;
	else
		return lower_bound(t1+1,t1+n+1,x+1)-t1-1;
}
ll f[N],g[N],h[N];
inline ll calc(int p,int k) {
	if(k>=n)
		return INFLL;
	int x=a[p].first,y=a[p].second;
	ll l=f[p],r=g[p],ans=INFLL;
	g[p]=h[p];
	h[p]=4e9;
	while(l<=r) {
		ll mid=(l+r)>>1;
		int val=T.query(get_id(max(x-mid,(ll)-2e9),0),get_id(min(x+mid,(ll)2e9),1),max(y-mid,(ll)-2e9),min(y+mid,(ll)2e9));
		if(val>=k+1) {
			if(val>k+1) {
				chkmin(g[p],mid);
				if(val>k+2)
					chkmin(h[p],mid);
			} else
				chkmax(f[p],mid);
			ans=mid,r=mid-1;
		} else
			l=mid+1;
	}
	chkmax(f[p],ans);
	return ans;
}
struct node {
	int p,k;
	ll val;
	bool operator > (const node &tmp) const {
		return val>tmp.val;
	}
}; priority_queue<node,vector<node>,greater<node> > heap;
void solve() {
	n=read(); k=read();
	rep(i,1,n) {
		int x=read(),y=read();
		a[i]={x+y,x-y};
		t1[i]=a[i].first;
		t[++len]=a[i].second;
		f[i]=0; g[i]=h[i]=4e9;
	}
	sort(t+1,t+len+1);
	sort(t1+1,t1+n+1);
	len=unique(t+1,t+len+1)-t-1;
	sort(a+1,a+n+1);
	rep(i,1,n)
		T.ins(get_id(a[i].second),1);
	rep(i,1,n)
		heap.push({i,1,calc(i,1)});
	while(true) {
		node t=heap.top(); heap.pop();
		if(!used[t.val]) {
			used[t.val]=true;
			write(t.val);
			pc('\n');
			if(!--k)
				break;
		} else
			used[t.val]=false;
		heap.push({t.p,t.k+1,calc(t.p,t.k+1)});
	}
	flush();
}
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	return 0;
}
```

---

## 作者：SunnyYuan (赞：0)

如果您不想在阁楼里继续阅读，可以选择[更好的阅读体验](https://www.cnblogs.com/Yuan-Jiawei/p/18357571)。

这篇文章主要讲一下问什么要二分以后还要 `check(l - 1)`，以及怎么找距离小于等于 $k$ 的边的数量。

## 题目

给定 $n$ 个点，求出任意两个点的曼哈顿距离的集合的前 $k$ 大。

## 思路

我们先将曼哈顿距离转化为切比雪夫距离：我们知道形如 $(x, y)$ 点之间的曼哈顿距离等于 $(x + y, x - y)$ 点之间的切比雪夫距离。

转化为切比雪夫距离之后，怎么求前 $k$ 大又是个问题。

我们可以二分一个 $dis$，看看小于等于 $dis$ 距离的数量是否大于等于 $k$，如果大于等于 $k$，那么可以缩小 $dis$，如果小于 $k$，我们将 $dis$ 调大。

那么二分怎么 check 呢？

假设现在 check 的是距离 dis。

我们可以先将所有坐标按照横坐标从小到大的顺序进行排序。

定义一个队列 queue 从前往后录入点；一个多重集 multiset 将 queue 中的点进行排序，按照纵坐标 $y$ 进行排序。

队列和集合维护的点的集合是相同的，不会出现一个点在 queue 中，不在 multiset 中，所以增加数字的时候一起加，删除数字的时候一起删。

我们从 $1$ 到 $n$ 枚举每一个点，首先第 $i$ 个点要进队列，所有点的横坐标 $x$ 小于 $x_i - dis$ 的点的距离都与 $i$ 保持了超过 $dis$ 的距离，所以要将他们从队尾弹出并从集合中删除；因为是切比雪夫距离，我们已经保证了横坐标不会超过 $dis$，接下来就看纵坐标，所有 $y_i - dis \le y_x \le y_i + dis$ 的点的距离都小于等于 $dis$，可以采纳，这一步我们可以使用 multiset 中的 `lower_bound` 函数实现，找到第一个纵坐标大于等于 $y_i - dis$ 的点，然后一直找这个点的后继（平衡树的后继，在 multiset 中直接将指针 +1 即可，非常方便），直到超过 $y_i + dis$，将这些点的距离放入答案数组 $ans$，即 $ans$ 数组新增 $\max(x_i - x_p, |y_i - y_p|)$，$x$ 不用写绝对值，因为已经排过序了；如果 $ans$ 数组记录的答案个数已经超过 $k$，立即返回成功（true），不能再记下去了；最后我们将点 $(x_i, y_i)$ 放入 queue 的队头和 multiset，必须最后放入，因为不能将自己和自己的距离（0）统计进去。

二分完以后我们还要再 `check(l - 1)` 一下，因为 $dis = l$，会导致个数大于等于 $k$，但是我们刚刚超过 $k$ 个时直接返回了，所以后面还有小于 $dis$ 距离没有统计到，我们又不是从小到大将距离添加到 $ans$ 的，所以我们退而求其次，将所有 $dis = l - 1$ 的部分求出来后，其一定小于 $k$ 个，再在 $ans$ 的数组后面添加距离 $l$，将其补齐到 $k$ 个，最后将 $ans$ 排序并输出。

时间复杂度：$O(n \log^2 n)$。

## 代码

注意 multiset 必须先放入极大值和极小值。

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int N = 250010;
const i64 INF = 1e18;

struct node {
    i64 x, y;
} p[N];

struct cmp {
    bool operator()(const node& a, const node& b) const {
        return a.y < b.y;
    }
};

int n, k;
i64 ans[N], cnt;

bool check(i64 dis) {
    multiset<node, cmp> mp;
    queue<int> q;
    mp.insert({INF, INF});
    mp.insert({-INF, -INF});
    cnt = 0;

    for (int i = 1; i <= n; i++) {
        while (q.size() && p[q.front()].x < p[i].x - dis) {
            mp.erase(mp.find({p[q.front()].x, p[q.front()].y}));
            q.pop();
        }
        auto pos = mp.lower_bound({INF, p[i].y - dis});
        while ((pos->y) <= p[i].y + dis) {
            ans[++cnt] = max(p[i].x - (pos->x), abs(p[i].y - (pos->y)));
            if (cnt >= k) return true;
            pos++;
        }
        q.push(i);
        mp.insert({p[i].x, p[i].y});
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        i64 a, b;
        cin >> a >> b;
        p[i].x = a + b, p[i].y = a - b;
    }
    sort(p + 1, p + n + 1, [](const node& a, const node& b) { return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y)); });
    i64 l = 1, r = INF;
    while (l < r) {
        i64 mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    check(l - 1);
    sort(ans + 1, ans + cnt + 1);
    for (int i = 1; i <= cnt; i++) cout << ans[i] << '\n';
    for (int i = cnt + 1; i <= k; i++) cout << l << '\n';
    return 0;
}
```

---

