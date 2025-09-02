# [USACO20JAN] Springboards G

## 题目描述

Bessie 在一个仅允许沿平行于坐标轴方向移动的二维方阵中。她从点 $(0,0)$ 出发，想要到达 $(N,N)$（$1 \leq N \leq 10^9$）。为了帮助她达到目的，在方阵中有 $P$（$1 \leq P \leq 10^5$）个跳板。每个跳板都有其固定的位置 $(x_1,y_1)$，如果 Bessie 使用它，会落到点 $(x_2,y_2)$。

Bessie 是一个过程导向的奶牛，所以她仅允许她自己向上或向右行走，从不向左或向下。类似地，每个跳板也设置为不向左或向下。Bessie 需要行走的距离至少是多少？

## 说明/提示

### 样例解释

Bessie 的最佳路线为：

- Bessie 从 (0,0) 走到 (0,1)（1 单位距离）。
- Bessie 跳到 (0,2)。
- Bessie 从 (0,2) 走到 (1,2)（1 单位距离）。
- Bessie 跳到 (2,3)。
- Bessie 从 (2,3) 走到 (3,3)（1 单位距离）。

Bessie 总共走过的路程为 3 单位距离。

### 子任务

- 测试点 $2 \sim 5$ 满足 $P \leq 1000$。
- 测试点 $6 \sim 15$ 没有额外限制。

## 样例 #1

### 输入

```
3 2
0 1 0 2
1 2 2 3```

### 输出

```
3```

# 题解

## 作者：zhoukangyang (赞：30)

## 蒟蒻语
有神仙让蒟蒻讲思路, 蒟蒻就写了篇题解 qwq
## 蒟蒻解
先将所有坐标的 $y$ 坐标离散化。

然后把所有坐标按照 $x$ 为第一关键字, $y$ 为第二关键字排序。

从前往后遍历, 用 $dp_i$ 表示从 $(0, 0)$ 到 $x_i, y_i$ 的答案。

怎么更新信息?

考虑用 $k$ 节点更新 $i$ 节点。

如果 $k$ 节点可以直接用跳板直接跳到 $i$ 节点, 那么 $dp$ 值相同。

否则要一步一步走过去。如果能更新, 那么 $dp_i = dp_k + x_i - x_k + y_i - y_k$

那么 $dp_i - x_i - y_i = dp_k - x_k - y_k$

如果设 $f_i = dp_i - x_i - y_i$，那么 $f_i = f_k$ !

那么现在丢掉 $dp$ 数组然后使用 $f$ 数组。

现在如果$k$ 节点可以直接用跳板直接跳到 $i$ 节点

$f_i = dp_i - x_i - x_j = dp_k - x_i - y_i = f_k + x_k + y_k - x_i - y_i$

那么考虑谁能够更新他呢？

只有 $x$ 坐标小于等于他而且 $y$ 坐标小于等于他的节点可以更新。

这时显然  $x$ 坐标小于等于 $i$ 节点已经满足, 而 $y$ 坐标没有满足。 现在要求 $y$ 坐标处于 $0 ... y_i$ 的节点。

$f_i$ 是 $min(f_{1,2...i-1})$ , 显然每次把 $f$ 值丢进树状数组里面就可以单次 $O(\log n)$ 维护了

如果 $i$ 是一个跳板的末端, 直接更新一下就好了qwq

最后答案就是 $min(f_i + n + n)$ (如果把他当作一个节点, 那么 $f$ 值就是 $min(f_i)$, 所以答案是 $min(f_i + n + n)$)

细节看蒟蒻丑陋的代码吧 qwq

```cpp
#include<bits/stdc++.h>
#define N 200010
using namespace std;
int n, m, a[N], fr[N], to[N], Ans;
struct node {
	int x, y, yy, id;
} p[N];
bool cmp(node aa, node bb) {
	return aa.x == bb.x ? aa.y < bb.y : aa.x < bb.x;
}
bool ycmp(node aa, node bb) {
	return aa.y < bb.y;
}
int ans[N];
void add(int x, int val) {
	for(; x <= m * 2; x += (x & -x)) ans[x] = min(ans[x], val);
} 
int qzh(int x) {
	int Ans = 0; 
	for(; x; x -= (x & -x)) Ans = min(Ans, ans[x]);
	return Ans;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &p[i].x, &p[i].y), p[i].id = i;
		scanf("%d%d", &p[i + m].x, &p[i + m].y), p[i + m].id = i;
	}
	sort(p + 1, p + m * 2 + 1, ycmp);
	p[0].y = -1;
	for(int i = 1; i <= 2 * m; i++) p[i].yy = p[i - 1].yy + (p[i - 1].y != p[i].y);
	sort(p + 1, p + m * 2 + 1, cmp);
	for(int i = 1; i <= m * 2; i++) {
		if(fr[p[i].id]) to[p[i].id] = i;
		else fr[p[i].id] = i;
	}
	for(int i = 1; i <= m * 2; i++) {
		a[i] = min(a[i], qzh(p[i].yy));
		if(fr[p[i].id] == i) a[to[p[i].id]] = min(a[to[p[i].id]], 
			a[i] + p[i].x + p[i].y - p[to[p[i].id]].x - p[to[p[i].id]].y);
		add(p[i].yy, a[i]);
		Ans = min(Ans, a[i]);
	}
	printf("%d\n", Ans + n * 2);
	return 0;
}
```

---

## 作者：Sol1 (赞：15)

貌似没有 1log + 纯 BIT 的题解呢~

那我来水一篇~

首先考虑 dp。

设 $dp_i$ 为只使用前 $i$ 个跳板，且必须使用第 $i$ 个，能够**省下**的**最大距离**。转移方程如下：

$$dp_{i}=\max\limits_{x_2(j)\leq x_1(i),y_2(j) \leq y_1(i)}dp_{j}+x_2(i)-x_1(i)+y_2(i)-y_1(i)$$

显然暴力转移是 $O(p^2)$ 的。考虑如何优化。

发现实际上如果把 $dp_i$ 的值赋值到 $(x_2(i),y_2(i))$ 这个点上面，那么现在就是一个二维统计问题。

~~于是就可以愉快地树套树/CDQ了~~

说好的纯 BIT 呢？

既然要纯 BIT，显然需要降维。（因为二维树状数组空间飞了 QwQ）。发现本质上是个可以离线的加点/矩形查询，所以考虑排序。

将所有的点的 $y$ 坐标离散化，把 $(x_1,y_1)$ 和 $(x_2,y_2)$ 分开离散化；

然后我们就有了 $2p$ 个单点，然后按照 $x$ 为第一关键字，$y$ 为第二关键字排序。

然后就可以直接二维数点套路了：对于每一个 $(x_1,y_1)$，可以查询区间 $(1,y_1)$ 的最大值，并记录 $dp$ 值；否则就把 $dp$ 值打到 $y_2$ 上面。

所以现在我们需要一个数据结构，支持单点修改、前缀查询最大值。显然可以树状数组。

最后求出 $dp$ 之后，答案就是 $2n - \max dp$。

于是这道题就解决了~

总时间复杂度 $O(p \log p)$，空间复杂度 $O(p)$。

附个代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

//这个结构体原来是我用来保存跳板的，但是貌似现在不用也可以（
struct Node {
	int x1, y1, x2, y2, xx1, yy1, xx2, yy2;
	inline bool operator < (const Node& nd) const {
		return (x2 ^ nd.x2 ? x2 < nd.x2 : y2 < nd.y2);
	}
};
//这是必要的了。保存跳板拆完后的单点。
struct _Node {
	int x, y, xx, yy, idx;//分别代表原坐标、离散化后坐标、对应的原跳板的下标
	bool type;//表示是起点还是终点
	inline bool operator < (const _Node& nd) const {
		return (x ^ nd.x ? x < nd.x : y < nd.y);
	}
};
Node nd[100005];
_Node _nd[200005];
int n, p, dp[100005], c[200005];

//树状数组
inline int Lowbit(int x) {
	return x & -x;
}

inline void Update(int i, int x) {
	for (register int j = i;j <= 200000;j += Lowbit(j)) c[j] = Max(c[j], x);
}

inline int Query(int i) {
	register int ans = 0;
	for (register int j = i;j >= 1;j -= Lowbit(j)) ans = Max(ans, c[j]);
	return ans;
}
//读入没啥好说的
inline void Read() {
	n = qread(); p = qread();
	for (register int i = 1;i <= p;i++) {
		nd[i].x1 = qread();
		nd[i].y1 = qread();
		nd[i].x2 = qread();
		nd[i].y2 = qread();
	}
}
//离散化坐标，注意x1和x2要放在一起离散化，y1和y2同理。
inline void Prefix() {
	vector <int> vc;
	for (register int i = 1;i <= p;i++) vc.push_back(nd[i].x1);
	for (register int i = 1;i <= p;i++) vc.push_back(nd[i].x2);
	sort(vc.begin(), vc.end());
	for (register int i = 1;i <= p;i++) nd[i].xx1 = lower_bound(vc.begin(), vc.end(), nd[i].x1) - vc.begin() + 1;
	for (register int i = 1;i <= p;i++) nd[i].xx2 = lower_bound(vc.begin(), vc.end(), nd[i].x2) - vc.begin() + 1;
	vc.clear();
	for (register int i = 1;i <= p;i++) vc.push_back(nd[i].y1);
	for (register int i = 1;i <= p;i++) vc.push_back(nd[i].y2);
	sort(vc.begin(), vc.end());
	for (register int i = 1;i <= p;i++) nd[i].yy1 = lower_bound(vc.begin(), vc.end(), nd[i].y1) - vc.begin() + 1;
	for (register int i = 1;i <= p;i++) nd[i].yy2 = lower_bound(vc.begin(), vc.end(), nd[i].y2) - vc.begin() + 1;
}

inline void Solve() {
	//拆点
	for (register int i = 1;i <= p;i++) {
		_nd[i - 1 << 1 | 1].x = nd[i].x1;
		_nd[i - 1 << 1 | 1].y = nd[i].y1;
		_nd[i - 1 << 1 | 1].xx = nd[i].xx1;
		_nd[i - 1 << 1 | 1].yy = nd[i].yy1;
		_nd[i - 1 << 1 | 1].idx = i;
		_nd[i - 1 << 1 | 1].type = 0;
		_nd[i << 1].x = nd[i].x2;
		_nd[i << 1].y = nd[i].y2;
		_nd[i << 1].xx = nd[i].xx2;
		_nd[i << 1].yy = nd[i].yy2;
		_nd[i << 1].idx = i;
		_nd[i << 1].type = 1;
	}
	//排序
	sort(_nd + 1, _nd + (p << 1) + 1);
	for (register int i = 1;i <= (p << 1);i++) {
		if (_nd[i].type == 0) {//起点，发生转移
			dp[_nd[i].idx] = Query(_nd[i].yy);
		} else {//终点，加入dp值
			dp[_nd[i].idx] += nd[_nd[i].idx].x2 - nd[_nd[i].idx].x1 + nd[_nd[i].idx].y2 - nd[_nd[i].idx].y1;
			Update(_nd[i].yy, dp[_nd[i].idx]);
		}
	}
	//统计答案
	register int ans = 0;
	for (register int i = 1;i <= p;i++) {
		if (nd[i].x2 <= n && nd[i].y2 <= n) ans = Max(ans, dp[i]);
	}
	printf("%lld", (n << 1) - ans);
}

signed main() {
	Read();
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：RenaMoe (赞：13)

提前声明：这是一篇 CDQ 的题解，码量超级小的呢。

> N*N 的矩阵，从 (0,0) 走到 (N,N)，每次只能往右和往上走（求曼哈顿距离），有 P 个跳板可以从 $(x_1,y_1)$ 无代价转移到 $(x_2,y_2)$，求需要行走的最少距离
>
> $N\le10^9,P\le 10^5$


萌新初学 CDQ，可能讲的比较啰嗦，求谅解qwq。



## 思路

### 问题转化

$O(N^2)$ 和 $O(P^2)$ 的最短路都显然不行，我们可以观察一些性质并考虑 dp。

每次答案距离只能从左下方转移而来，即 $f(x_1,y_1)\rightarrow f(x_2,y_2)$ 满足 $x1\le x_2,y1\le y_2$。

直接 dp 需要考虑不从跳板走的距离，正难则反，我们设 $f(x,y)$ 表示走到 $(x,y)$ 能够省下的最大距离。

我们需要维护 $x1\le x_2,y1\le y_2$ 的最大 $f(x_1,y_1)$，至此我们将问题转化成二维偏序。

### CDQ

现在的问题是，每个跳板有两个端点：起点 $(x_1,y_1)$ 和终点 $(x_2,y_2)$，并且只能从前一个终点转移到其右上方的一个起点。

我们可以把一个跳板拆成两个点，起点作为查询，终点作为修改。

接下来就是 CDQ 的套路：处理左区间，更新左区间对右区间的贡献，处理右区间，一定要保证分治的先后顺序正确。

时间复杂度 $O(nlog^2n)$。

### 细节

写完交上去一直 WA 一个点，还下不了数据急躁半天。

后来想到，可能会有某个跳板的终点的另一个跳板的起点重合，排序不当会处理不了。

可以输入时提前处理掉，或者排序时保证位置重合的修改在询问之前就行（具体见代码的 cmp 函数）。

## 代码

```cpp
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

template<typename TT> inline void read(TT &x) {}

const int N = 2e5 + 9;

struct Node {
	int x1, y1, x2, y2;
};
struct Point {
	int x, y, opt, id;
};

int n, m, cnt;
int f[N], ans[N], len[N];
Node a[N];
Point p[N];

inline int calc_dis(int x1, int y1, int x2, int y2) {
	return x2 - x1 + y2 - y1;
}

inline bool cmp_x(const Point &i, const Point &j) {
	if (i.x == j.x) {
		if (i.y == j.y) return i.opt > j.opt;// 位置重合，让修改在前
		return i.y < j.y;
	}
	return i.x < j.x;
}
inline bool cmp_y(const Point &i, const Point &j) {
	if (i.y == j.y) {
		if (i.x == j.x) return i.opt > j.opt;
		return i.x < j.x;
	}
	return i.y < j.y;
}

void CDQ(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid), sort(p+mid+1, p+r+1, cmp_y);
	int maxn = 0;
	for (int i = mid+1, j = l, k = -1; i <= r; ++i) {
		if (p[i].opt) continue;
		int id = p[i].id;
		while (j <= mid && p[j].y <= p[i].y) {
			if (p[j].opt)
				maxn = max(maxn, ans[p[j].id]);
			j++;
		}
		ans[p[i].id] = max(ans[p[i].id], maxn + len[p[i].id]);
	}
	sort(p+mid+1, p+r+1, cmp_x);
	CDQ(mid+1, r);
	sort(p+l, p+r+1, cmp_y);
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; ++i)
		read(a[i].x1), read(a[i].y1), read(a[i].x2), read(a[i].y2);
	for (int i = 1; i <= m; ++i)
		p[++cnt] = (Point){a[i].x1, a[i].y1, 0, i}, p[++cnt] = (Point){a[i].x2, a[i].y2, 1, i};
	p[++cnt] = (Point){0, 0, 1, 0}, p[++cnt] = (Point){n, n, 0, m+1};
	sort(p+1, p+cnt+1, cmp_x);
	for (int i = 1; i <= m; ++i)
		len[i] = calc_dis(a[i].x1, a[i].y1, a[i].x2, a[i].y2);
	CDQ(1, cnt);
	printf("%d\n", n + n - ans[m+1]);
    return 0;
}
```

可惜跑的不快欸。

---

## 作者：dozenX (赞：6)

考场考到这个题，看了一眼感觉是建图跑最短路，仔细一想......


就开始建图跑最短路 $($


首先看到这个题第一想法应该将每个跳板和对应落点以及起点终点向着 $x$ 坐标与 $y$ 坐标都大于它的对应点连边权为 $|x_u-x_v|+|y_u-y_v|$ 的边，但是这样边数是 $O(n^2)$ 的肯定跑不出来，让我们来考虑一下优化建图。

怎么优化呢？首先注意到因为距离是曼蛤顿距离，所以只需要起点和每个落点向着跳板和终点连边即可，减小常数。这样我们把起点和终点加进点的集合当中，把跳板和终点染成黑色，起点和落点染成白色。

然后我们惊喜地看到这个连边的限制像一个二维偏序，考虑CDQ分治。我们把每个点按 $x$ 坐标排序，考虑一个分治区间，设其长度为 $len$ ，每次只要将左半区间的白点向右边区间的黑点连边。我们将左右区间都按 $y$ 坐标排序，然后发现每次连边都是左边区间的一个点向右边区间的一个前缀连边。我们新建 $O(len)$ 虚点代表每个前缀区间，每个前缀虚点只需要向上一个前缀虚点连一条的边，再向这一次新加入的节点连一条边，这样每一个前缀虚点都可以到达对应前缀的所有点。最后我们只要将左边的点连向右边对应的前缀区间的虚点，就可以每次新增 $O(len)$ 个点和边将图建好了。

边权怎么办？首先如果要连边 $x_v$ 和 $y_v$ 必然大于 $x_u$ 和 $y_u$ ，这样我们就能把绝对值消去。然后就可以把 $u$ 和 $v$ 对边权的影响分开考虑。我们从左区间的一个点 $u$ 向右区间对应的一个前缀点 $p_v$ 连一条边权为 $-x_u-y_u$ 的边，从前缀点 $p_v$ 向要新加入的节点 $v$ 连一条边权为 $x_v+y_v$ 的边，前缀点之间的连边边权都是 $0$ 。这样我们从一个点 $u$ 走到点 $v$ ，经过的边权和正好是 $x_v+y_v-x_u-y_u$ ，这样边权问题就十分美好地解决了。

测了一下一条链的极限数据发现只有大约 $1\times 10^6$ 个点 $2\times 10^6$ 条边，兴高采烈地跑SPFA，然后T飞了。

不是，这个图是个dag，那我凭什么要跑最短路嘛。

拓扑一下，冲完了。

拍了两组挂了，我们发现有的黑点会和白点重合，为了防止黑点在白点左边连不上边，我们把cmp函数改成如果 $x$ 坐标相等则按白点在前黑点在后排序，这个问题也愉快地解决了。

我在分治里直接写的sort排序，所以时间复杂度是 $O(n\log^2n)$ ，改成归并排序复杂度是 $O(n\log n)$ 的，非常舒适。

考场代码，略丑勿喷。

```cpp
#include<bits/stdc++.h>
//lrz dhty tie tie
using namespace std;
int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return x;
}
const int N=1e5+5;
typedef long long ll;
struct EDGE{
	int to,next;ll val;
}edge[N*40];
int head[N*20],deg[N*20],num_edge;
void add_edge(int from,int to,ll val){
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].val=val;
	deg[to]++;
}
struct ND{
	ll x,y;int id;bool md;
	ND(ll _x=0,ll _y=0,int _id=0,ll _md=0){x=_x,y=_y,id=_id,md=_md;}
}nd[N<<2],us[N<<2],uu[N<<2];
bool cmp1(ND p,ND q){return p.x==q.x?(p.y==q.y?p.md<q.md:p.y<q.y):p.x<q.x;}
bool cmp2(ND p,ND q){return p.y>q.y;}
int cc,id[N<<2],m,n,cnt;
void solve(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1,uc=0,ct=0;
	solve(l,mid),solve(mid+1,r);
	for(int i=mid+1;i<=r;i++)if(nd[i].md)us[++uc]=nd[i];
	if(!uc)return ;
	sort(us+1,us+1+uc,cmp2);
	for(int i=l;i<=mid;i++)if(!nd[i].md)uu[++ct]=nd[i];
	if(!ct)return ;
	sort(uu+1,uu+1+ct,cmp2);
	id[1]=++cnt,add_edge(id[1],us[1].id,us[1].x+us[1].y);
	for(int i=2;i<=uc;i++)
		id[i]=++cnt,add_edge(id[i],id[i-1],0),add_edge(id[i],us[i].id,us[i].x+us[i].y);
	for(int i=1,j=0;i<=ct;i++){
		while(j<uc&&us[j+1].y>=uu[i].y)j++;
		if(j!=0)add_edge(uu[i].id,id[j],-uu[i].x-uu[i].y);
	}
}
ll dis[N*20];bool vis[N*20];int tj[N*20];
queue<ll>q;
void topo(int S){
	for(int i=1;i<=cnt;i++){
		if(!deg[i])q.push(i);
		dis[i]=1e10;
	}
	dis[S]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			dis[v]=min(dis[v],dis[u]+edge[i].val),deg[v]--;
			if(!deg[v])q.push(v);
		}
	}
}
void flie(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
}
int main(){
	m=read(),n=read();
	for(int i=1;i<=n;i++){
		ll sx=read(),sy=read(),tx=read(),ty=read();
		cnt++,nd[cnt]=ND(sx,sy,cnt,1),cnt++,nd[cnt]=ND(tx,ty,cnt,0);
		add_edge(cnt-1,cnt,0);
	}
	int s,t;
	cnt++,s=cnt,nd[cnt]=ND(0,0,cnt,0);
	for(int i=1;i<cnt;i++)if(nd[i].x==0&&nd[i].y==0)add_edge(cnt,i,0);
	cnt++,t=cnt,nd[cnt]=ND(m,m,cnt,1);
	for(int i=1;i<cnt;i++)if(nd[i].x==m&&nd[i].y==m)add_edge(i,cnt,0);
	sort(nd+1,nd+1+cnt,cmp1);
	solve(1,cnt);
	topo(s);
	printf("%lld\n",dis[t]);
	return 0;
}
```


---

## 作者：fighter (赞：6)

一开始想错了，还以为是什么神仙建图跑最短路……

后来发现其实就是个非常套路的数据结构优化DP。

朴素的DP应该不用多说，从左下方转移过来，跳板单独转移即可。这样是$O(P^2)$的，但是我们可以通过优化降低复杂度。

先不考虑跳板，那么这就是一个类似二维数点的问题。我们将所有的点先按照x坐标排序，然后用线段树维护y坐标。实际上我们要查询的就是一个y轴上的前缀最小值。

这里有一个实现上的细节。我们朴素的转移方程是$f[i]=min\{f[j]+dis(i,j)\}$，这里$dis$指的是曼哈顿距离。这怎么使用线段树维护转移呢？我们可以把$dis(i,j)$拆开，由于从左下方转移，那么直接去掉绝对值，$f[i]=min\{f[j]+x_i+y_i-x_j-y_j\}$。

于是我们在线段树中并不直接插入$f[j]$，而是插入$f[j]-x_j-y_j$，这样我们转移的时候就直接$f[i]=min\{f[j]-x_j-y_j\}+x_i+y_i$即可。

接着考虑跳板，其实直接开一个map就行，对于每个跳板，我们转移完之后把它的$f$值挂到目标点的map上，然后在每个点转移的时候看看map中是否有对应的跳板能够转移到它，如果有，就直接从map里拿出来转移一下就好了。因为跳板最多只有$P$个，所以这一部分复杂度最多只有$P\log P$。

结合线段树操作，总复杂度$O(P\log P)$。

## 代码

注意y坐标需要离散化。

```cpp
#include <bits/stdc++.h>
#define MAX 200015
#define INF (ll)1e16
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
#define mid ((l+r)>>1)
#define mk(x, y) (make_pair(x, y))
#define ll long long
using namespace std;

struct node{
    int x, y, tx, ty;
    friend bool operator <(node a, node b){
        if(a.x != b.x) return a.x < b.x;
        else if(a.y != b.y) return a.y < b.y;
        else if(a.tx != b.tx) return a.tx < b.tx;
        return a.ty < b.ty;
    }
}a[MAX];

int n, m, cnt, tot;
int b[MAX], id[MAX];
ll s[MAX*4], f[MAX];
map<pair<int, int>, ll> mp, vis;

void build(int p, int l, int r){
    if(l == r){
        s[p] = INF;
        return;
    }
    build(lc(p), l, mid), build(rc(p), mid+1, r);
    s[p] = min(s[lc(p)], s[rc(p)]);
}
void update(int p, int l, int r, int u, ll k){
    if(l == r){
        s[p] = min(s[p], k);
        return;
    }
    if(mid >= u) update(lc(p), l, mid, u, k);
    else update(rc(p), mid+1, r, u, k);
    s[p] = min(s[lc(p)], s[rc(p)]);
}
ll query(int p, int l, int r, int ul, int ur){
    if(l >= ul && r <= ur) return s[p];
    ll res = INF;
    if(mid >= ul) res = min(res, query(lc(p), l, mid, ul, ur));
    if(mid < ur) res = min(res, query(rc(p), mid+1, r, ul, ur));
    return res;
}

int main()
{
    cin >> m >> n;
    a[++cnt] = (node){0, 0, 0, 0}, b[++tot] = 0;
    int x1, x2, y1, y2;
    for(int i = 1; i <= n; ++i){
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        b[++tot] = y1, b[++tot] = y2;
        a[++cnt] = (node){x1, y1, x2, y2}, a[++cnt] = (node){x2, y2, 0, 0};
    }
    a[++cnt] = (node){m, m, 0, 0}, b[++tot] = m;
    sort(b+1, b+tot+1);
    tot = unique(b+1, b+tot+1)-b-1;
    for(int i = 1; i <= cnt; ++i){
        a[i].y = lower_bound(b+1, b+tot+1, a[i].y)-b;
        if(a[i].ty) a[i].ty = lower_bound(b+1, b+tot+1, a[i].ty)-b;
    }
    sort(a+1, a+cnt+1);
    memset(f, 0x3f, sizeof(f));
    build(1, 1, tot);
    f[1] = 0;
    update(1, 1, tot, a[1].y, -a[1].x-b[a[1].y]);
    for(int i = 2; i <= cnt; ++i){
        ll mn = query(1, 1, tot, 1, a[i].y);
        f[i] = min(f[i], mn+a[i].x+b[a[i].y]);
        if(vis.count(mk(a[i].x, b[a[i].y]))) f[i] = min(f[i], mp[mk(a[i].x, b[a[i].y])]);
        if(a[i].ty){
            pair<int, int> p = mk(a[i].tx, b[a[i].ty]);
            if(!vis[p]){
                mp[p] = f[i];
                vis[p] = 1;
            }
            else mp[p] = min(mp[p], f[i]);
        }
        update(1, 1, tot, a[i].y, f[i]-a[i].x-b[a[i].y]);
    }
    cout << f[cnt] << endl;

    return 0;
}
```



---

## 作者：gargantuar (赞：5)

## 听说没有人写分块题解,那么我来一发

前几天学校模拟赛的时候遇到了这道题，吓得我直接骗了30分(

然而机房的大佬们都纷纷拿出 CDQ，树状数组，平衡树各显神通，~~蒟蒻自闭~~。

我就想反正树状数组我也会写，思路听明白了写一遍也是浪费时间(

但是作为新时代好青年，题还是要补的。

为了最大化利用补题时间效率，我就用全新的分块A了这道题。

### 题目分析


------------
先说30分的写法，显而易见， $p<1000$  ，此时只要给每一个踏板的起点进行双关键字排序，进行 dp，维护在每个跳板**强制跳跃** 后到达终点可以节省的最大步数，最后用 $n* 2$ 减去即可。

然后考虑 $p<10^5$ ，此时显然不能暴力 dp 了，先对 $x$ 和 $y$ 分别进行离散化，然后以 $\sqrt p$ 为长宽，对矩阵进行分块，按照跳板起点位置依次把所有的跳板装进块里，注意普通数组容易炸空间，用 vector 存。

很明显我们要减少对于每一个跳板的状态转移次数，时我们选择改变维护的信息，选择维护每个跳板的位置到终点可以节省的最大步数，注意这里我们**不强制跳跃**。

这样做的好处就是一个跳板可以直接表示他右上所有路径的最优解。

![](https://cdn.luogu.com.cn/upload/image_hosting/26necbmi.png)

如图，红色点为跳板起点，蓝色点为终点，黑色为其他跳板的起点。发现两种转移方法，分别是从粉色线上的点直接转移到红色点，表示不选择跳跃，直接走到其他点，和从绿色线上的黑点转移到蓝色点，再加上从红到蓝节省的步数，表示选择跳跃，再走到其他点。剩下的黑点就不用管了。

此时聪明的我已经想到了，对于每一个块记录块内的左下方没有点的点，块间转移时之考虑这些点，之后如果发现一个块的块内有点，右上方的块就不去查询了。至于块内，暴力就行。

但此时聪明的你马上拿出来一组数据来 hack 我

![](https://cdn.luogu.com.cn/upload/image_hosting/ym3o448i.png)

如图，每一个黑点都会转移到所有红点，此时时间瞬间被卡到了 $p^2$ 。

然后分析，为什么时间会被卡爆呢？显然发现，在之前的图中，如果你选中了一个点
作为转移对象，那么这个点的右上方就没必要查询了。然而红点的信息互不包含，黑点只能暴力转移了。而且黑点和黑点也互不构成包含关系。

既然没有点能包含红点，那就新建一些节点包含不就行了？如果我们给每一个块的左下角加上一个新节点，那么这个节点就会包含块内的所有信息。

![](https://cdn.luogu.com.cn/upload/image_hosting/hri9xlm5.png)

如图，黄线表示块边界，绿点表示新建的节点，此时每一个黑节点只会从恰好一个绿节点进行转移，而每一个红节点又恰好被至少一个绿节点进行包含，绿点数量也为 $O(p)$ 。所以时间复杂度就降到了 $O(p)$ 了

然后聪明的你又拿出了一组数据 hack 我。

![](https://cdn.luogu.com.cn/upload/image_hosting/m6uthoz2.png)

看样子绿点也丧失作用了。

但事实真的如此吗？别忘了我们是对 $x$ 和 $y$ 分别进行离散化的，也就是说块的长宽最大为 $\sqrt p$ ，同时块内也最多存 $\sqrt p$ 个点，也就是说，最坏情况块间转移的复杂度也是  $O(p)$ 的。而且这样的转移是有限的，平均下来，复杂度应该是 
$O(p\sqrt p)$。

当然了，有时候情况会极端一点，例如 $x$ 的取值为分散，但 $y$ 只会取 $1$ 或 $2$，这种情况下 一个块内也可能出现 $p$ 级别的点数。但此时发现点大多的坐标都是重合的。所以写两个数组，分别记录 $x$ 为某个值时的最大转移方案数，和 $y$ 为某个值时的最大转移方案数。

现在，最终方案已经近在咫尺了，对于每个点，我们只需要维护正上方块的转移，正右方块的转移，以及右上方第一个绿点的转移即可。别忘了对块内进行暴力转移。

### AC代码


------------
吸氧优化情况下 $2s$ 不开是 $5s$ 左右，卡卡常数应该可以更快

其实还有很多优化可以加速，不过我是懒狗，就不加了

蒟蒻码风难看，请见谅。

```cpp
#include<bits/stdc++.h>
#define intl long long
using namespace std;
int n,m,eont,eont2,k,k2,mp[400005],mp2[400005],ll[5005],rr[5005],ll2[5005],rr2[5005],bl[400005],bl2[400005],sq,sq2,fnk[2000][2000],fmk[2000][2000],zont,ans;
vector<vector<int> > fzz;
vector<int> fx;
vector<vector<vector<int> > > fk;
vector<vector<vector<int> > > fnmdp;
int xmm[400005],ymm[400005];
struct lsh {
	int val,id,w;
} e[800005],e2[800005];
struct node {
	int x,y,a,b,v,k;
} a[400005];
bool cmp(lsh a,lsh b) {
	return a.val<b.val;
}
bool ccp(node a,node b) {
	if(a.x==b.x)return a.y>b.y;
	return a.x>b.x;
}
inline void fbl(int bx,int by,int z,int zx,int zy,bool adSelf) {
	for(int i=1; i<=fmk[bx][by]; ++i) {
		int ii=fk[bx][by][i];
		if(a[ii].x>=zx&&a[ii].y>=zy&&ii!=z) {
			if(adSelf)a[z].k=max(a[z].k,a[z].v+a[ii].k);
			else a[z].k=max(a[z].k,a[ii].k);
		}
	}
}
inline void fd(int z,int t,bool adSelf) {
	if(adSelf)a[z].k=max(a[z].k,a[z].v+a[t].k);
	else a[z].k=max(a[z].k,a[t].k);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		scanf("%d",&e[++eont].val);
		e[eont].id=i;
		e[eont].w=1;
		scanf("%d",&e2[++eont2].val);
		e2[eont2].id=i;
		e2[eont2].w=2;
		scanf("%d",&e[++eont].val);
		e[eont].id=i;
		e[eont].w=3;
		scanf("%d",&e2[++eont2].val);
		e2[eont2].id=i;
		e2[eont2].w=4;
		a[i].k=a[i].v=e[eont].val-e[eont-1].val+e2[eont2].val-e2[eont2-1].val;
	}
	sort(e+1,e+1+eont,cmp);
	sort(e2+1,e2+1+eont2,cmp);
	e[0].val=e[1].val-1;
	e2[0].val=e2[1].val-1;
	for(int i=1; i<=eont; ++i) {
		e[i].val!=e[i-1].val?k++:0;
		mp[i]=e[i].val;
		if(e[i].w==1) {
			a[e[i].id].x=k;
		} else if(e[i].w==3) {
			a[e[i].id].a=k;
		}
	}
	for(int i=1; i<=eont2; ++i) {
		e2[i].val!=e2[i-1].val?k2++:0;
		mp2[i]=e2[i].val;
		if(e2[i].w==2) {
			a[e2[i].id].y=k2;
		} else if(e2[i].w==4) {
			a[e2[i].id].b=k2;
		}
	}
	for(int i=1; i<=m; ++i) {
	}
	sq=sqrt(k);
	sq2=sqrt(k2);
	fx.push_back(0);
	for(int i=1; i<=sq2+5; ++i)fzz.push_back(fx);
	for(int i=1; i<=sq+5; ++i)fk.push_back(fzz);
	for(int i=1; i<=sq+5; ++i)fnmdp.push_back(fzz);
	for(int i=1; i<=sq; ++i) {
		ll[i]=k/sq*(i-1)+1;
		rr[i]=k/sq*i;
	}
	for(int i=1; i<=sq2; ++i) {
		ll2[i]=k2/sq2*(i-1)+1;
		rr2[i]=k2/sq2*i;
	}
	rr[sq]=k,rr2[sq2]=k2;
	for(int i=1; i<=sq; ++i)
		for(int j=ll[i]; j<=rr[i]; ++j)
			bl[j]=i;
	for(int i=1; i<=sq2; ++i)
		for(int j=ll2[i]; j<=rr2[i]; ++j)
			bl2[j]=i;
	for(int i=1; i<=sq; ++i) {
		for(int j=1; j<=sq2; ++j) {
			if(fmk[i][j]==0) {
				++zont;
				++fmk[i][j];
				fk[i][j].push_back(m+zont);
				a[m+zont].x=a[m+zont].a=ll[i];
				a[m+zont].y=a[m+zont].b=ll2[j];
				a[m+zont].v=0;
				a[m+zont].k=0;
			}
		}
	}
	sort(a+1,a+m+1,ccp);
	for(int i=1; i<=m; ++i) {
		++fmk[bl[a[i].x]][bl2[a[i].y]];
		fk[bl[a[i].x]][bl2[a[i].y]].push_back(i);
		++fnk[bl[a[i].a]][bl2[a[i].b]];
		fnmdp[bl[a[i].a]][bl2[a[i].b]].push_back(i);
	}
	for(int xx=sq; xx>=1; --xx)
		for(int yy=sq2; yy>=1; --yy) {
			if(xx!=sq&&yy!=sq2) {
				xmm[rr[xx]]=max(xmm[rr[xx]],a[fk[xx+1][yy+1][1]].k);
				ymm[rr2[yy]]=max(ymm[rr2[yy]],a[fk[xx+1][yy+1][1]].k);
			}
			for(int ii=1; ii<=fnk[xx][yy]; ++ii) {
				int i=fnmdp[xx][yy][ii];
				for(int q=a[i].a; q<=rr[xx]; ++q) {
					if(!xmm[q])continue;
					a[i].k=max(a[i].k,a[i].v+xmm[q]);
				}
				for(int q=a[i].b; q<=rr2[yy]; ++q) {
					if(!ymm[q])continue;
					a[i].k=max(a[i].k,a[i].v+ymm[q]);
				}
			}
			for(int ii=2,z=1; z||ii==1; ++ii) {
				if(ii>fmk[xx][yy])z=0,ii=1;
				int i=fk[xx][yy][ii];
				int xxx=bl[a[i].a],yyy=bl2[a[i].b];
				//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--
				fbl(xx,yy,i,a[i].x,a[i].y,0);
				if(xx!=sq)fbl(xx+1,yy,i,a[i].x,a[i].y,0);
				if(yy!=sq2)fbl(xx,yy+1,i,a[i].x,a[i].y,0);
				if(xx!=sq&&yy!=sq2)fd(i,fk[xx+1][yy+1][1],0);
				//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--
				fbl(xxx,yyy,i,a[i].a,a[i].b,1);
				if(xxx!=sq&&yyy!=sq2)fd(i,fk[xxx+1][yyy+1][1],1);
				ans=max(ans,a[i].k);
				xmm[a[i].x]=max(xmm[a[i].x],a[i].k);
				ymm[a[i].y]=max(ymm[a[i].y],a[i].k);
			}
		}

	printf("%d",n*2-ans);
}
```






---

## 作者：devout (赞：4)

~~开班会水题解美滋滋~~

具体的树状数组的做法楼上ClCN大佬已经讲得很清楚了%%%！

这里主要做一点点补充和代码上的优化qwq

前面都还是一样，我们考虑走的距离最短不好求可以转化成我们跳的距离最长

所以可以推出一个转移方程

$$f_i=\max\{f_j+dis(i)\}(x_i\geq x_j,y_i\geq y_j)$$

其中$dis(i)$表示这个跳板跳的距离

然后我们将每个跳板拆成起点和终点，然后先按$x$为第一关键字$y$为第二关键字排序，这样我们可以把询问转化成在$y$轴上的一维询问，离散化一下用树状数组维护前缀max就可以了

但是实际上不用拆点拆的那么麻烦，我们只需要拆成两个点，对于$dis$的求解，直接在读入的时候进行预处理就可以了

注意最后答案只能是$x,y$都$\leq n$的里面的max就可以了

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,p,nsz;
int b[N],sz;
int f[N],dis[N];
int bit[N];
int ans;

struct node{
    int x,y,opt,bel;
    bool operator < (const node &cmp)const{
        if(x!=cmp.x)return x<cmp.x;
        if(y!=cmp.y)return y<cmp.y;
        return opt<cmp.opt;
    }
}a[N];

int lowbit(int o){
    return o&-o;
}

int add(int o,int x){
    for(;o<=nsz;o+=lowbit(o))bit[o]=max(bit[o],x);
}

int ask(int o){
    int res=0;
    for(;o;o-=lowbit(o))res=max(res,bit[o]);
    return res;
}

int main()
{
    read(n),read(p);
    Rep(i,1,p){
        int x,y;
        read(x),read(y);
        a[++sz]=(node){x,y,0,i};
        b[sz]=y;
        dis[i]-=x+y;
        read(x),read(y);
        a[++sz]=(node){x,y,1,i};
        b[sz]=y;
        dis[i]+=x+y;
    }
    a[++sz]=(node){n,n,2,0};
    sort(b+1,b+sz+1);
    nsz=unique(b+1,b+sz+1)-b-1;
    Rep(i,1,sz)a[i].y=lower_bound(b+1,b+nsz+1,a[i].y)-b;
    sort(a+1,a+sz+1);
    Rep(i,1,sz){
        if(a[i].opt==2){
            Rep(j,1,p)if(a[i].x>=a[j].x&&a[i].y>=a[j].y)ans=max(ans,f[j]);
            printf("%d\n",2*n-ans);
            return 0;
        }
        if(!a[i].opt)f[a[i].bel]=ask(a[i].y)+dis[a[i].bel];
        else add(a[i].y,f[a[i].bel]);
    }
    return 0;
}
```


---

## 作者：hater (赞：4)

这个蒟蒻太菜了 根本不会离散化 

之后只能菜菜的用平衡树 

只有$Ins$没有$Del$ 代码简短好评 

还是稍微讲一下思路 

$O(n^2)$思路很好想 

$f_{i}$表示从起点到点$i$的最小步数

$f_{i}=min( f_{i} , f_{j} + dis(i,j) )  $  

其中$dis(i,j)$是两点距离 保证$a_{j}$ 的坐标 不大于 $a_{i}$ 的 坐标

以 每个点 $x$ 坐标为第一关键字 , $y$ 坐标为第二关键字 排序

我们能保证 $a_{1,x}$到$a_{i-1,x}$ 比$a_{i,x}$小 

之后显然需要优化 平衡树瞎搞搞 

$Ins$的值是 $f_{i}-a_{i,x}-a_{i,y}$ 

把$y$坐标比$a_{i,y}$小的$split$出来

更新就成了这个样子 $f_{i}=query(a_{i,y})+a_{i,x}+a_{i,y}$ 

还有一个跳板 单独转移 

处理好像比较麻烦 但是多开几个数 ， 映射搞一搞就好了 

具体见代码 ： 

```cpp
#include <bits/stdc++.h> 
#define Inf 0x7f7f7f7f   
#define rg register 
#define i60 long long 
#define il inline 
#define fp( i , x , y ) for(rg int i=(x); i<=(y); ++i) 
#define fq( i , x , y ) for(rg int i=(y); i>=(x); --i) 
using namespace std ; 
const int N = 3e5+50 ; 
i60 n , p , f[N] , tot ; map <pair<int,int>,int> Map ;  pair<int,int> tep ; 
struct node { int sx , sy , ex , ey ; } a[N] ;  
inline bool cmp( rg node A , rg node B ) { return A.ex!=B.ex ? A.ex<B.ex : A.ey<B.ey; } 
inline int min( rg int A , rg int B ) { return A < B ? A : B ; } ;  
inline int dis( rg int i ) { return a[i].ex-a[i].sx+a[i].ey-a[i].sy ; } 
struct hgs_treap { 
    int ch[N][2] , rnd[N] , siz[N] , val[N] , val2[N] , Min[N] , cnt , sed ;  
    il void start( ) { Min[0] = 0 ; siz[0] = 0 ; cnt = 0 ; sed = 233 ; }   
	il int rrand( ) { return sed = int(sed * 482711ll % 2147483647); }  
	int New_node ( int Val , int Val2 ) { 
	    rnd[++cnt] =  rrand( ) ; ch[cnt][0] = ch[cnt][1] = 0 ; 
	    val[cnt] = Val ; val2[cnt] = Min[cnt] = Val2 ; 
	    siz[cnt] = 1 ; return cnt ; }  
    il void updata( rg int rt ) { 
	    siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1 ; 
		Min[rt] = min( Min[ch[rt][0]] , Min[ch[rt][1]] ) ; 
		Min[rt] = min( Min[rt] , val2[rt] ) ; } 
	il void split( rg int rt , rg int &x , rg int &y , rg int k ) { 
	    if( !rt ) { x = y = 0 ; return ; }  
	    if( val[rt] <= k ) x = rt , split( ch[rt][1] , ch[x][1] , y , k ) ; 
		  else y = rt , split( ch[rt][0] , x , ch[y][0] , k ) ; 
		updata( rt ) ; } 
	il void merge( rg int &rt , rg int x , rg int y ) { 
	    if( !x || !y ) { rt = x+y ; return ; } 
	    if( rnd[x] < rnd[y] ) rt = x , merge( ch[rt][1] , ch[x][1] , y ) ;
	      else rt = y , merge( ch[rt][0] , x , ch[y][0] ) ; 
	    updata( rt ) ; } 
	void Ins( int &rt , int Val , int Val2 ) { 
	    int z = New_node( Val , Val2 ) , x = 0 , y = 0 ; 
		split( rt , x , y , val[z] ) ; 
		merge( x , x , z ) ; merge( rt , x , y ) ; } 
	int query( int rt , int Val ) { 
	    int x = 0 , y = 0 ; split( rt , x , y , Val ) ;  
		int ans = Min[x] ; merge( rt , x , y ) ;  
		return ans ; } 
} hgs ;  
signed main( ) { 
    ios::sync_with_stdio(false) ; cin.tie(0) ; cout.tie(0) ;  
    rg int tx , ty , etx , ety , rot = 0 ; cin >> n >> p ; 
	fp( i , 1 , p ) cin >> tx >> ty >> etx >> ety , 
	  a[++tot] = (node) { -1 , -1 , tx , ty } , 
	  a[++tot] = (node) { tx , ty , etx , ety } ; 
	a[++tot] = (node) { -1 , -1 , 0 , 0 } ; 
	a[++tot] = (node) { -1 , -1 , n , n } ; 
	sort( a+1 , a+1+tot , cmp ) ; 
	fp( i , 1 , tot ) Map[make_pair(a[i].ex , a[i].ey)] = i ; 
	hgs.start( ) ; hgs.Ins( rot , 0 , 0 ) ; f[1] = 0 ;  
	fp( i , 2 , tot ) { 
	    f[i] = a[i].ex + a[i].ey + hgs.query( rot , a[i].ey ) ; 
	    tep = make_pair( a[i].sx , a[i].sy ) ; 
		if( a[i].sx != -1 ) f[i] = min( f[i] , f[Map[tep]]  ) ; 
		hgs.Ins( rot , a[i].ey , f[i]-a[i].ex-a[i].ey ) ;   
	} cout << f[tot] << endl ; return 0 ; 
} 
```

吸口氧跑的没压力 

~~一开始seed没赋初值 还以为平衡树不能搞~~ 

~~手动狗头~~

---

## 作者：lxzy_ (赞：1)

题外话：做这种毒瘤题目的时候可以试着把一些不同于往常、需要改变的量记录在草稿纸上，~~这是我把p*2写成n然后三天才调出来的经验~~

> 定义 $sx_i,sy_i,ex_i,ey_i$ 分别表示当前编号为 $i$ 的点的起点 $x,y$ 坐标，终点 $x,y$ 坐标。

首先，由于题目中的 $N$ 在 $10^9$ 的范围内，而 $p$ 却只有 $10^5$ ，因此可以考虑将每一个跳板作为状态，进行DP。然后可以想到如下的做法：

$\color{blue}\text{方法一：}$

将所有跳板按照 $sx$ 为第一关键字， $sy$ 为第二关键字进行排序，定义 $f[i]$ 表示当前走到第 $i$ 号跳板的最小步数。转移方程如下：

$$f[i]=\min\limits_{ex_j\leq sx_i,ey_j\leq ey_i}(f[j])+sx_i+sy_i-ex_j-ey_j$$

复杂度 $O(P^2)$ ，可以拿到 $33pts$ 的好成绩。

考虑进行优化。可以使用某种数据结构储存下每一次转移后的 $f[i]$ 值，然后使用 $O(\log P)$ 的时间复杂度查找最小的值。但由于转移方程涉及到 $ex_j,ey_j$ 等变量会影响转移后的解的最优性。因此诞生了第二个dp方式。

$\color{blue}\text{方法二：}$

定义 $f[i]$ 表示行走到点$i$时所能节省下来的最大距离（相对于完全不走跳板的 $2n$ 步走法），那么可以得出如下转移方程：

$$f[i]=\max\limits_{ex_j\leq sx_i,ey_j\leq ey_i}(f[j])+ex_i+ey_i-sx_i-ex_j$$

此时 $i$ 不会受到 $j$ 号跳板的坐标的影响，因此可以使用数据结构优化。优化的大致方法为以 $x$ 的大小顺序遍历，以 $y$ 为下标建立树状数组，维护对应的 $f[i]$ 值。

具体做法如下：

> 定义点 $i$ 离散化前的 $x,y$ 坐标为 $x_i,y_i$ ，离散化后的坐标为 $px_i,py_i$.

将所有的起点，终点放在一个数组内，每个点记录下当前原始坐标 $idx_i$ ， $i$ 号跳板的起点坐标为 $i$ ，终点坐标为 $i+p$.

然后将 $x$ 和 $y$ 分开离散化，定义 $pos_i$ 表示原始坐标为 $i$ 的点在离散化后的数组内的下标。

接着进行DP，便利一遍所有的点，有如下两种情况

1. 如果当前点 $i$ 是起点（ $idx_i\leq p$ ），那么定义：

$$now[i]=\max\limits_{py_j\leq py_{i}}(f[j])$$

并且不需要转移；

2. 如果当前点 $i$ 是终点，则套用公式，其中取max的部分应当改为 $i$ 对应的起点的 $now$ 值）。

Q: 为什么不在搜索到所有终点的时候再查找符合条件的最优$f[j]$，而是要在起点的时候查找？

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7qyow7h6.png)

~~（为了方便我直接使用原始坐标代替离散化后的坐标）~~

如果在遍历到最后一个点 $i+p$ 的时候才查找符合条件的最优$f[j]$ ，那么就会查找到像 $j+p$ 这种 $py_{j+p}\leq py_{i}$ 但是 $px_{j+p}>px_{i}$ 的非法点。在点 $i$ 直接查找可以避免。

最后的答案即为：

$$ans=2n-\max\limits_{1\leq i\leq 2p}(f[i])$$

Code:

```cpp
#include<cstdio>
#include<iomanip>
#include<algorithm>
#define lowbit(i) i&(-i)
#define p1 (p<<1)//p*2
using namespace std;
const int N=2e5+50;
struct point{
	int x,y,px,py,idx;
}a[N];
int f[N],c[N],pos[N],now[N];
int n,p;
inline int Max(int a,int b){return a>b?a:b;}
bool cmp1(point p,point q)//离散化y的排序 
{
	if(p.x!=q.x) return p.x<q.x;
	else return p.y<q.y;
}
bool cmp2(point p,point q)//离散化x的排序 
{
	if(p.y!=q.y) return p.y<q.y;
	else return p.x<q.x;
}

//树状数组 
inline void Insert(int x,int y){for(;x<=p1;x+=lowbit(x)) c[x]=Max(c[x],y);}
inline int Query(int x)
{
	int ans=0;
	for(;x>0;x-=lowbit(x)) ans=Max(ans,c[x]);
	return ans;
}

//离散化 
void Work() 
{
	sort(a+1,a+1+p1,cmp2);//y的离散化 
	a[0].py=1;
	for(int i=1;i<=p1;i++){
		if(a[i].y==a[i-1].y) a[i].py=a[i-1].py;
		else a[i].py=a[i-1].py+1;
	}
	sort(a+1,a+1+p1,cmp1);//这里默认DP时按x从小到大排序，因此x的离散化放后面 
	a[0].px=1;
	for(int i=1;i<=p1;i++){
		if(a[i].x==a[i-1].x) a[i].px=a[i-1].px;
		else a[i].px=a[i-1].px+1;
		pos[a[i].idx]=i;//储存下原始坐标对应的离散化后的坐标 
	}	
}
int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=p;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		scanf("%d%d",&a[i+p].x,&a[i+p].y);
		a[i].idx=i,a[i+p].idx=i+p;
	}
	Work();

	//DP
	for(int i=1;i<=p1;i++){
		if(a[i].idx>p){
			f[i]=now[pos[a[i].idx-p]]+a[i].x+a[i].y-a[pos[a[i].idx-p]].x-a[pos[a[i].idx-p]].y;
			//pos[a[i].idx-p]]即为终点i对应的起点 
			Insert(a[i].py,f[i]);
		}
		else now[i]=Query(a[i].py);
	}
	int maxn=0;
	for(int i=1;i<=p1;i++) maxn=Max(maxn,f[i]);
	printf("%d\n",(n<<1)-maxn);
	return 0;
}
```

---

## 作者：Hongse_Fox (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P6007)
# 零.前记
排序注意以什么为关键词排序

这真的很重要$!$（笔者因为这个卡了一个下午）

$and$这篇博客中默认从上到下从左到右是正方向

# 一.思路

这道题也许会想到图论（虽然我并没有想到）

但是建图时$O(n^2)$的复杂度已经可以劝退了

我们又发现落地之后前面怎么跳都不会对后面有任何影响

而且我们最优的走法分成若干段必然也是最优的

即满足最优子结构性质和无后效性

因此我们可以往$dp$方向考虑了

# 二.详细做法

因为走的最少步数$=2\times n-$可以省的最大步数

而跳一次跳板可以省的步数就是$x_2+y_2-x_1-y_1$

于是我们设$sv_i$表示跳完第$i$个跳板之后可以省下的最大步数

[![cJR8Tf.png](https://z3.ax1x.com/2021/04/08/cJR8Tf.png)](https://imgtu.com/i/cJR8Tf)

如图我们假设某个跳板$i$的起点是$A$终点是$B$

那么如果要跳$i$号跳板

上一次跳的落点必须在这些红色格子当中（如果没跳就当作落点为$1,1$）

即可以写出这样的一条状态转移方程$:$

$$sv_i=max\{ sv_j\}+x_b+y_b-x_a-y_a(j \in red)$$

现在的问题变成了怎么样维护红色区域的最值

不难想到先维护每一列的最值再求区间最值来实现

我们先把所有格子以$y1$为第一关键字$x1$为第二关键字从小到大排序

排出来的顺序就和读现代书籍的顺序是一样的

这样就可以保证在跳$i$的时候落点在红色区域的点（即所有的点$j$）已经被遍历过了

但是在这些点之中可能会出现起跳点在$A$前但是落点在$A$后的点

对于这种情况我们可以再开一个优先队列存储所有的$sv_i$

每次便利到新的起点$A$时判断是否有一些落点可以加入考虑

到这我们发现我们要维护一个可以随时更新的区间最值

我们就可以先离散化之后用线段树维护每一列的最大值

**code**
```cpp
for(register int i=1;i<=p;i++){
	hh h;
	hh u={a[i].xx1,a[i].y1,0};//起点的值 
	while(!q.empty() && check(q.top(),u)){//将所有落点在起点前的点加入线段树 
		h=q.top();q.pop();
		query(1,1,m,h.x,h.sv);//单点修改 
	}
	int sv=search(1,1,m,1,a[i].xx1);//求第1列到a[i].xx1列的最值 
	h.x=a[i].xx2;h.y=a[i].y2;h.sv=sv+a[i].y2+a[i].x2-a[i].x1-a[i].y1;
	q.push(h);//新求出的落点加入优先队列 
}
```

### 注意
#### $i.$由于$n$的范围太大要对$x$进行离散化 而$y$可以不用

#### $ii.$线段树的大小为离散化之后最大的$x$

#### $iii.$单点修改是与原来的点比大小而不是完全修改

#### $iv.$最后可能还剩下一些落点 在统计答案的时候要统计上去

# 三.代码
```cpp
#include<cstdio>
#include<cctype>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
inline int R(){
	int r=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return r;
}
int n,ans;
int p,m;
struct node{
	int x1,y1,x2,y2;
	int xx1,xx2;//xx1xx2为离散化之后的x1x2 
}a[100005];
vector <int> c;
inline bool comp(node a,node b){//开始时的排序 从上到下从左到右 
	if(a.y1!=b.y1) return a.y1<b.y1;
	return a.x1<b.x1;
}
int tree[800005];
inline int search(int now,int l,int r,int ql,int qr){//线段树求区间最值 
	if(ql<=l && r<=qr){
		return tree[now];
	}
	int mid=(l+r)>>1;
	int sum=0;
	if(ql<=mid) sum=search(now<<1,l,mid,ql,qr);
	if(qr>mid) sum=max(sum,search(now<<1|1,mid+1,r,ql,qr));
	return sum;
}
inline void query(int now,int l,int r,int k,int sv){//线段树单点修改 
	if(l==r){
		tree[now]=max(tree[now],sv);
		return ;
	}
	int mid=(l+r)>>1;
	if(k<=mid) query(now<<1,l,mid,k,sv);
	if(k>mid) query(now<<1|1,mid+1,r,k,sv);
	tree[now]=max(tree[now<<1],tree[now<<1|1]);
	return ;
}
struct hh{//落点的结构体 
	int x,y,sv;
	friend bool operator < (hh a,hh b){
		if(a.y!=b.y) return a.y>b.y;
		return a.x>b.x;
	}
};
inline bool check(hh x,hh y){//判断哪个点在前面 
	if(x.y<y.y) return 1;
	if(x.y==y.y && x.x<=y.x) return 1;
	return 0;
}
priority_queue <hh> q;//落点的优先队列 
int main(){
	n=R();p=R();
	for(register int i=1;i<=p;i++){
		a[i].x1=R();a[i].y1=R();
		a[i].x2=R();a[i].y2=R();
		c.push_back(a[i].x1);c.push_back(a[i].x2);
	}
	sort(c.begin(),c.end());//离散化 
	for(register int i=1;i<=p;i++){//离散化 
		a[i].xx1=lower_bound(c.begin(),c.end(),a[i].x1)-c.begin()+1;
		a[i].xx2=lower_bound(c.begin(),c.end(),a[i].x2)-c.begin()+1;
		m=max(a[i].xx1,m);m=max(a[i].xx2,m);
	}
	sort(a+1,a+p+1,comp);//按照先y再x的顺序排序 
	for(register int i=1;i<=p;i++){
		hh h;
		hh u={a[i].xx1,a[i].y1,0};//起点的值 
		while(!q.empty() && check(q.top(),u)){//将所有落点在起点前的点加入线段树 
			h=q.top();q.pop();
			query(1,1,m,h.x,h.sv);//单点修改 
		}
		int sv=search(1,1,m,1,a[i].xx1);//求第1列到a[i].xx1列的最值 
		h.x=a[i].xx2;h.y=a[i].y2;h.sv=sv+a[i].y2+a[i].x2-a[i].x1-a[i].y1;
		q.push(h);//新求出的落点加入优先队列 
	}
	while(!q.empty()){//最后可能还有一些落点要考虑 
		hh h=q.top();q.pop();
		query(1,1,m,h.x,h.sv);
	}
	ans=n+n-search(1,1,m,1,m);//答案为2n-最大省去的步数 
	printf("%d\n",ans);
	return 0;
}
```
# 四.后记
本题考察了如何灵活地运用数据结构优化动态规划

要想想一个跳板的两个点$x1,y1$和$x2,y2$带来的限制

而且要注意离散化

Finally，谢谢大家

[更好的阅读体验](https://www.luogu.com.cn/blog/HongseFox/solution-p6007)

---

## 作者：白鲟 (赞：1)

## 前言
不太清醒。

太不清醒。

## 分析
首先想到建图。

于是开始想的是神仙优化建图最短路。

未果。

后来写出式子猛然醒悟。

将题目中给定的点记录下来，设 $f_i$ 表示走到点 $i$ 的最小步数，有：

$$
f_i=\min_{x_j\le x_i,y_j\le y_i}f_j+w_{j,i}
$$

其中 $w_{j,i}$ 表示点 $j$ 与点 $i$ 的距离，设题目所给 $0$ 权边集为 $E$，有：

$$
w_{j,i}=
\begin{cases}
0,(j,i)\in E\\
x_i-x_j+y_i-y_j,(j,i)\notin E
\end{cases}
$$

容易看出是经典数据结构优化的状态转移方程式。前一种情况单独转移，时间复杂度为 $\operatorname{O}(n)$；后一种情况将式子参变分离，变形为 $f_i=(\min_{x_j\le x_i,y_j\le y_i}(f_j-x_j-y_j))+(x_i+y_i)$，发现离散化后将 $f_j-w_j-y_j$ 使用树状数组维护前缀最小值即可每次 $\operatorname{O}(\log n)$ 转移。

总时间复杂度为 $\operatorname{O}(n\log n)$。

## 代码
“`i+=lowbit(x);`”。

不愧是我，考场奇迹。

另外注意点可能重复。由于排序不稳定，$f_{tot}$ 可能不是最后的答案，最后一个点对应的才是。

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
const int maxn=1e5;
int n,p,tot,x1,y1,x2,y2,newtot,copies[(maxn<<1)+10],f[(maxn<<1)+10],BIT[(maxn<<1)+10],from[(maxn<<1)+10];
struct node
{
	int x,y,no;
	node(int t1=0,int t2=0,int t3=0):x(t1),y(t2),no(t3){}
}a[(maxn<<1)+10];
inline bool cmp(const node &t1,const node &t2)
{
	return t1.x==t2.x?t1.y<t2.y:t1.x<t2.x;
}
inline int lowbit(int x)
{
	return x&(-x);
}
void change(int x,int value)
{
	for(int i=x;i<=newtot;i+=lowbit(i))
		BIT[i]=min(BIT[i],value);
	return;
}
int query(int x)
{
	int res=0x3f3f3f3f3f3f3f3fll;
	for(int i=x;i;i-=lowbit(i))
		res=min(res,BIT[i]);
	return res;
}
signed main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=p;++i)
	{
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		if(x1<=n&&y1<=n&&x2<=n&&y2<=n)
		{
			++tot;
			a[tot]=node(x1,y1,tot);
			++tot;
			a[tot]=node(x2,y2,tot);
			from[tot]=tot-1;
		} 
	}
	++tot;
	a[tot]=node(0,0,tot);
	++tot;
	a[tot]=node(n,n,tot);
	for(int i=1;i<=tot;++i)
		copies[i]=a[i].y;
	sort(a+1,a+tot+1,cmp);
	sort(copies+1,copies+tot+1);
	newtot=unique(copies+1,copies+tot+1)-copies-1;
	memset(f,0x3f,sizeof f);
	change(1,0);
	f[a[1].no]=0;
	for(int i=2;i<=tot;++i)
	{
		int pos=lower_bound(copies+1,copies+newtot+1,a[i].y)-copies;
		f[a[i].no]=min(f[from[a[i].no]],query(pos)+a[i].x+a[i].y);
		change(pos,f[a[i].no]-a[i].x-a[i].y);
	}
	printf("%lld",f[a[tot].no]);
	return 0;
}
```

---

## 作者：momo5440 (赞：1)

这个蒟蒻太菜了，只会$O(Plog^{2}P)$的解法，**我们考虑从原路返回**，其实完全没有必要，令

$dp[i]$ 为$(N,N)$到$（x1,y1)$ 这个点最多**节省**多少路径，**同时必须要用**$i$这个跳板

转移就是从所有满足$x1_{j}>=x2_{i}$&&$y1_{j}>=y2_{i}$的$j$中找最大的那个然后直接转移过来，直观地写出来就是

$dp[i]=x2_{i}-x1_{i}+y2_{i}-y1_{i}+max(dp_{j}) ($ $x1_{j}>=x2_{i}$且$y1_{j}>=y2_{i}$ $)$

写的话就是先把一维定序然后用一个线段树套线段树暴力即可，还要加上离散化，为了方便我在代码中把N与P换了一下，而且由于巨大的常数这份代码在洛谷上不吸氧会T一个点，但是当时在USACO上跑过了

代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=1e5+5;
typedef long long ll;
struct tre{
	int lc,rc;
	int val;
};
tre t1[maxn*200];
int top;
int lenx;
int leny;
inline int newn(){
	return ++top;
}
void co(int u){
	t1[u].val=max(t1[t1[u].lc].val,t1[t1[u].rc].val);
}
inline int insert(int u,int l,int r,int id,int x){
	if (u==0) u=newn();
	if (l==r){
		t1[u].val=max(t1[u].val,x);
		return u;
	}
	int mid=(l+r)/2;
	if (id<=mid) t1[u].lc=insert(t1[u].lc,l,mid,id,x);
	else t1[u].rc=insert(t1[u].rc,mid+1,r,id,x);
	co(u);
	return u;
}
inline int qmax(int u,int l,int r,int ql,int qr){
	if (u==0) return 0;
	if (ql<=l&&r<=qr){
		return t1[u].val;
	}
	int mid=(l+r)/2;
	int res=0;
	if (ql<=mid) res=max(res,qmax(t1[u].lc,l,mid,ql,qr));
	if (mid+1<=qr) res=max(res,qmax(t1[u].rc,mid+1,r,ql,qr));
	return res;
}
////
inline int lc(int u){
	return u<<1;
}
inline int rc(int u){
	return u<<1|1;
}
int rt[maxn*6];
void inserty(int u,int l,int r,int x,int y,int val){
	rt[u]=insert(rt[u],1,lenx,x,val);
	if (l==r) return;
	int mid=(l+r)/2;
	if (y<=mid) inserty(lc(u),l,mid,x,y,val);
	else inserty(rc(u),mid+1,r,x,y,val);
}
inline int qmaxy(int u,int l,int r,int qlx,int qrx,int qly,int qry){
	if (qly<=l&&r<=qry){
		return qmax(rt[u],1,lenx,qlx,qrx);
	}
	int res=0;
	int mid=(l+r)/2;
	if (qly<=mid) res=max(res,qmaxy(lc(u),l,mid,qlx,qrx,qly,qry));
	if (mid+1<=qry) res=max(res,qmaxy(rc(u),mid+1,r,qlx,qrx,qly,qry));
	return res;
}
struct node{
	int x1,y1,y2,x2;
};
bool cmp(node a1,node b1){
	if (a1.x1==b1.x1) return a1.y1>b1.y1;
	return a1.x1>b1.x1;
}
node a[maxn];
int n,m;
int dp[maxn];
int numx[maxn*2],numy[maxn*2];
int main(){
	//freopen("boards.in","r",stdin);
	//freopen("boards.out","w",stdout);
	cin>>m>>n;
	for (int i=1;i<=n;i++){
		scanf("%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
		numx[++lenx]=a[i].x1;
		numx[++lenx]=a[i].x2;
		numy[++leny]=a[i].y1;
		numy[++leny]=a[i].y2;
	}
	sort(numx+1,numx+lenx+1);
	sort(numy+1,numy+leny+1);
	lenx=unique(numx+1,numx+lenx+1)-numx-1;
	leny=unique(numy+1,numy+leny+1)-numy-1;
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++){
		int tpx=lower_bound(numx+1,numx+lenx+1,a[i].x2)-numx;
		int tpy=lower_bound(numy+1,numy+leny+1,a[i].y2)-numy;
		dp[i]=qmaxy(1,1,leny,tpx,lenx,tpy,leny)+a[i].x2+a[i].y2-a[i].x1-a[i].y1;
		int curx=lower_bound(numx+1,numx+lenx+1,a[i].x1)-numx;
		int cury=lower_bound(numy+1,numy+leny+1,a[i].y1)-numy;
		inserty(1,1,leny,curx,cury,dp[i]);
	}
	int ans=m*2;
	for (int i=1;i<=n;i++){
		ans=min(ans,m*2-dp[i]);
	}
	cout<<ans<<endl;
}
```


---

## 作者：lkytxdy (赞：0)

## P6007 [USACO20JAN]Springboards G

注意到 $n\leq 10^9$，而 $p\leq 10^5$，故考虑将每一个跳板当做状态进行 dp。

将所有跳板按 $(sx,sy)$ 排序，设 $f_i$ 表示以第 $i$ 个跳板为结尾的最小步数，那么 $f_i=\min\limits_{ex_j\leq sx_i,ey_j\leq sy_i}f_j+sx_i+sy_i-ex_j-ey_j$。朴素转移 $\mathcal O(p^2)$。

考虑优化，$-ex_j-ey_j$ 不好处理，于是设 $f_i$ 表示以第 $i$ 个跳板为结尾，**最多能少走多少步**。那么 $f_i=\max\limits_{ex_j\leq sx_i,ey_j\leq sy_i}f_j+ex_i+ey_i-sx_i-sy_i$，这样跳板 $i$ 的转移不会受到 $ex_j,ey_j$ 的影响，只需要求出 $\max\limits_{ex_j\leq sx_i,ey_j\leq sy_i}f_j$ 即可。把 $(ex,ey)$ 看作修改，$(sx,sy)$ 看作查询，CDQ 分治即可。注意如果有某个 $(sx,sy)$ 与某个 $(ex,ey)$ 重合，把 $(ex,ey)$ 放前面。

最后答案为 $2n-\max\limits_{1\leq i\leq p} f_i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,sx,sy,ex,ey,val[N],t,f[N],ans;
struct node{
	int x,y,id,op;
}a[N*2];
bool cmp(node x,node y){return x.x==y.x?(x.y==y.y?x.op<y.op:x.y<y.y):x.x<y.x;}
void cdq(int l,int r){
	if(l==r){f[a[l].id]=max(f[a[l].id],val[a[l].id]);return ;}
	int mid=(l+r)/2,j=l,mx=0;
	cdq(l,mid);
	sort(a+l,a+1+mid,[](node x,node y){return x.y<y.y;});
	sort(a+mid+1,a+1+r,[](node x,node y){return x.y<y.y;});
	for(int i=mid+1;i<=r;i++) if(a[i].op){
		while(j<=mid&&a[j].y<=a[i].y){if(!a[j].op) mx=max(mx,f[a[j].id]); j++;} 
		f[a[i].id]=max(f[a[i].id],mx+val[a[i].id]);
	}
	sort(a+mid+1,a+1+r,cmp);
	cdq(mid+1,r);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		val[i]=abs(sx-ex)+abs(sy-ey),a[++t]={sx,sy,i,1},a[++t]={ex,ey,i,0};
	}
	sort(a+1,a+1+t,cmp),cdq(1,t);
	for(int i=1;i<=m;i++) ans=max(ans,f[i]);
	printf("%d\n",n*2-ans);
	return 0;
} 
```

---

## 作者：Fairicle (赞：0)

朴素 dp，考虑从 $i$ 转移到 $j$，则有 $f_i+x_j-x_i+y_j-y_i=f_j$ 即 $f_i-x_i-y_i=f_j-x_j-y_j$

那么不妨设 $g_i=f_i-x_i-y_i$，则对于没有跳板的情况有 $g_i=g_j$

有跳板的情况为 $f_i=f_j$ 即 $g_i+x_i+y_i-x_j-y_j=g_j$，此时可以 $O(P^2)$ 做。

我们考虑将 $x$ 排序，对于一个 $g_i$ 可以从两种地方转移，一是从跳板跳到它，二是找出 $y$ 比它小的 $g$ 的最小值，将其赋值为这个最小值。

最后答案是 $f_{(n,n)}=g_{(n,n)}-n-n$

转移顺序是一件需要考虑的事。

如果你选择让**跳板终点被跳板起点更新**，那么你就要强制让跳板起点被更新过，也就是说当跳板起点是前面某个跳板终点时要先更新它作为终点时的答案。

如果选择让**跳板起点更新跳板终点**，那么这个起点即使作为前面跳板的终点，也被前面跳板的起点更新过了，所以不需要钦定顺序。

很不幸我写的是前面一种。

code：

```cpp
#define ll long long
#define ri register int
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 100010
int n,m,bg[N],ed[N],g[N<<1],c[N<<1],x,y;
struct springboard{
    int x,y,yp,idx,op;
}s[N<<1];
inline bool cmpy(springboard a,springboard b){return a.y<b.y;}
inline bool cmpx(springboard a,springboard b){if(a.x==b.x&&a.y==b.y) return a.op<b.op;if(a.x==b.x) return a.y<b.y;return a.x<b.x;}
inline int lowbit(int x){return x & ( - x ) ;}
inline int query(int x){int tmp=0;for(ri i=x;i>0;i-=lowbit(i)) tmp=min(tmp,c[i]);return tmp;}
inline void change(int x,int v){for(ri i=x;i<=2*m;i+=lowbit(i)) c[i]=min(c[i],v);}
int main()
{
	n=rd(),m=rd();
	for(ri i=1;i<=m;++i){
        x=rd(),y=rd();
        s[i].x=x,s[i].y=y,s[i].idx=i,s[i].op=1;
        x=rd(),y=rd();
        s[i+m].x=x,s[i+m].y=y,s[i+m].idx=i,s[i+m].op=0;
    }
    sort(s+1,s+1+2*m,cmpy);
    s[0].y=-1;
    for(ri i=1;i<=2*m;++i) s[i].yp=s[i-1].yp+(s[i-1].y!=s[i].y);
    sort(s+1,s+1+2*m,cmpx);
    for(ri i=1;i<=2*m;++i){
        if(bg[s[i].idx]) ed[s[i].idx]=i;
        else bg[s[i].idx]=i;
    }
    int ans=0;
    for(ri i=1;i<=2*m;++i){
        g[i]=query(s[i].yp);
        if(i==ed[s[i].idx]) g[i]=min(g[i],g[bg[s[i].idx]]+s[bg[s[i].idx]].x+s[bg[s[i].idx]].y-s[i].x-s[i].y);
        ans=min(ans,g[i]);
        change(s[i].yp,g[i]);
    }
    cout<<ans+2*n;
    return 0;
}
```


---

## 作者：xixiup (赞：0)

### 初步思考

首先我们需要说明一点：从点 $(x_a,y_a)$ 走到点 $(x_b,y_b)$，所有的路径都是唯一的。

且有：一个跳板，它对减小走路距离的贡献为 $\left|x_2-x_1\right|+\left|y_2-y_1\right|$。

所以我们求出一条可能的路径，使得路径上所有跳板的减小走路距离的贡献最大。

仔细思考，其实很像一个二维偏序，为什么呢？

因为思考，对于一个跳板 $i$，如果使用完跳板 $j$ 还可以使用跳板 $i$ 的话，那么肯定需要满足 $x_{2,j} \leqslant x_{1,i} $且$ y_{2,j} \leqslant y_{1,i}$。

但是光这么做肯定是不行的，为什么呢？

因为二维偏序是用于处理点的，而不是用于处理线段的。所以这道题你在第一维排序的时候并不知道是以 $x_1$ 为关键字排序还是以 $x_2$ 为关键字排序。

但是可以考虑如何优化。

### 思路分享

由于我们的树状数组已经可以维护 $y$ 坐标了，所以我们只需要考虑如何维护 $x$ 坐标。

然后思考，假如我们先以 $x_1$ 为关键字排序，然后使用一个堆维护 $x_2$，使得现在将所有 $x_{2,j}\leqslant x_{1,i}$ 的 $j$ 加入树状数组，即可了。

又由于我们前文按照 $x_1$ 进行了排序，且堆满足了 $x_2$ 的单调性，所以每个跳板仅会被加入树状数组 $1$ 次，且不会被删除，所以加入的均摊复杂度为 $\Theta(1)$，综合的复杂度为 $\Theta(p^2)$，可以过这道题。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200100;
//这里需要开2e5，开1e5会迷之WA
int n,m,nx,ny,fx[maxn],fy[maxn],tx[maxn],ty[maxn];
int c[maxn],Max,numa[maxn],la;
//fx:x1、fy:y1、tx:x2、ty:y2
int numx[maxn*2],numy[maxn*2];
priority_queue<pair<int,int> >q; 
//维护加跳板的顺序
struct node{
	int len,fx,fy,tx,ty;
	bool operator <(node u)const{
		return fx==u.fx?tx<u.tx:fx<u.fx;
	}
}jump[maxn];
//树状数组维护二维偏序
int lowbit(int x){
	return x&(-x);
}
int query(int x){
	int sum=0;
	while(x>0){
		sum=max(c[x],sum);
		x-=lowbit(x);
	}
	return sum;
}
int change(int x,int i){
	while(x<=ny){
		c[x]=max(c[x],i);
		x+=lowbit(x);
	}
}
map<int,int>mapx,mapy;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&fx[i],&fy[i],&tx[i],&ty[i]);
		jump[i].len=tx[i]-fx[i]+ty[i]-fy[i];
		numx[i*2-1]=fx[i],numx[i*2]=tx[i];
		numy[i*2-1]=fy[i],numy[i*2]=ty[i];
	}//这里需要离散化
	sort(numx+1,numx+1+m+m);
	sort(numy+1,numy+1+m+m);
	numx[0]=numy[0]=-1;
	nx=ny=0;
	for(int i=1;i<=m*2;i++){
		if(numx[i]!=numx[i-1]){
			nx++;
			mapx[numx[i]]=nx;
		}
		if(numy[i]!=numy[i-1]){
			ny++;
			mapy[numy[i]]=ny;
		}
	}
	for(int i=1;i<=m;i++){
		jump[i].fx=mapx[fx[i]];
		jump[i].tx=mapx[tx[i]];
		jump[i].fy=mapy[fy[i]];
		jump[i].ty=mapy[ty[i]];
	}
	sort(jump+1,jump+1+m);
	for(int i=1;i<=m;i++){
		while(!q.empty()&&-(q.top().first)<=jump[i].fx){//加入跳板
			change(jump[q.top().second].ty,numa[q.top().second]);
			q.pop();
		}
		numa[i]=query(jump[i].fy);
		numa[i]+=jump[i].len;
		Max=max(Max,numa[i]);
		q.push(make_pair(-(jump[i].tx),i)); 
	}
	printf("%d\n",(n*2)-Max);//Max即为对减少走路步数的贡献
    //没有跳板时走的路为(n*2)
	return 0;
}

```

---

