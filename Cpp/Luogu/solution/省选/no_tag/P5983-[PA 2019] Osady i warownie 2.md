# [PA 2019] Osady i warownie 2

## 题目描述

$n\times m$ 的网格，从上到下依次为第 $0$ 到 $n-1$ 行，从左到右依次为第 $0$ 到 $m-1$ 列，每个点都不是障碍格。

定义一条从起点 $(0,0)$ 到终点 $(n-1,m-1)$ 的路径是合法的，当且仅当这条路径经过恰好 $n+m-1$ 个格子(包括起点和终点)，且每一步要么往右走一格，要么往下走一格。当然，这条路径不能经过障碍格(包括起点和终点)。

你有一个 $int$ 变量 $v=0$，你现在需要模拟 $k$ 次操作，每次操作会给出三个非负整数 $r,c,z$，令 $x=(r \operatorname{xor}
 v)\bmod n,y=(c \operatorname{xor}
 v)\bmod m$：
1. 如果 $(x,y)$ 是障碍格，那么忽略这次操作，输出 `NIE`。
2. 否则如果将 $(x,y)$ 变成障碍格后仍然存在合法路径，那么将 $(x,y)$ 变成障碍格，输出 `NIE`。
3. 否则如果将 $(x,y)$ 变成障碍格后不存在合法路径，那么输出 `TAK`，并将 $v $ 修改为 $v \operatorname{xor} z$。

## 说明/提示

对于 $100\%$ 的数据,$2\le n,m\le 10^5$， $1\le k\le 10^6$，$0\le r,c,z<2^{20}$。

----


### 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/e5k1plm4.png)

## 样例 #1

### 输入

```
3 5 7
0 1 123
1 0 0
4 8 0
2 2 16
2 3 0
18 19 17
3 0 0```

### 输出

```
NIE
TAK
NIE
TAK
NIE
TAK
NIE```

# 题解

## 作者：Felix72 (赞：4)

桑格莉娅不止一次地启发我做网格行走相关题目：

![](https://cdn.luogu.com.cn/upload/image_hosting/8w9zto1p.png)

贴模型走路是一个很实用的技巧，可以在这类网格路径题中有效地去除一些重复冗余状态。

比如这道题，定义首末两行、两列为**边缘**部分，其他为**非边缘**部分，我们可以发现无论怎么在非边缘部分添加障碍，都存在至少两条合法路径，如下图：

```txt
OOOOO
O.X.O
OXX.O
OX.XO
OOOOO
```

```X``` 代表障碍，```O``` 代表边缘部分，```.``` 是普通的空地。我们发现只要存在边缘部分，我们就不用管普通的空地。

但是边缘部分可能会改变。比如在一个空的 $5 \times 5$ 网格中添加一个障碍：

```txt
OOOX.
O.OOO
O...O
O...O
OOOOO
```

不难发现障碍的作用是“如果处在原来的边缘部分，就把这个边缘部分挪个地方到左下角/右上角”，或者说“如果处在原来的边缘部分，则令自己左下角/右上角不可能再为边缘部分”。到底哪个角就要看自己原先处在左下角的边缘还是右上角的边缘。如果同时处在两类边缘，那说明没有路径可以走了，此时输出 ```TAK```，我们也顺便获得了是否有路径的充要条件。

边缘的修改是可以均摊的，因为每个点最多被一类边缘用一次，于是写一个事件驱动模拟。其中需要找最大最小值，set 常数大，换成堆就可以了。

```cpp
 /* NE_Cat 4.1 */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010;
typedef pair < int, int > PII;
struct Point {int x, y, val, id;} p[N * 10];
int n, m, k, lim[4][N]; map < PII, int > mp;
priority_queue < PII, vector < PII >, greater < PII > > conS[4][N];
priority_queue < PII > conL[4][N];

inline bool check(int opt, Point pos)
{
	if(opt == 0 && pos.y <= lim[0][pos.x]) return true;
	if(opt == 1 && pos.x >= lim[1][pos.y]) return true;
	if(opt == 2 && pos.y >= lim[2][pos.x]) return true;
	if(opt == 3 && pos.x <= lim[3][pos.y]) return true;
	return false;
}
inline void search_A(Point pos);
inline void search_B(Point pos);
inline void get(int opt, int id);
inline void get(int opt, int id)
{
	if(opt == 0)
	{
		while(!conS[0][id].empty() && conS[0][id].top().first <= lim[0][id])
		{
			PII cur = conS[0][id].top();
			conS[0][id].pop();
			search_A(p[cur.second]);
		}
	}
	else if(opt == 1)
	{
		while(!conL[1][id].empty() && conL[1][id].top().first >= lim[1][id])
		{
			PII cur = conL[1][id].top();
			conL[1][id].pop();
			search_A(p[cur.second]);
		}
	}
	else if(opt == 2)
	{
		while(!conL[2][id].empty() && conL[2][id].top().first >= lim[2][id])
		{
			PII cur = conL[2][id].top();
			conL[2][id].pop();
			search_B(p[cur.second]);
		}
	}
	else
	{
		while(!conS[3][id].empty() && conS[3][id].top().first <= lim[3][id])
		{
			PII cur = conS[3][id].top();
			conS[3][id].pop();
			search_B(p[cur.second]);
		}
	}
}
inline void search_A(Point pos)
{
//	cerr << "A " << pos.x << " " << pos.y << '\n';
	if(pos.x - 1 >= 1)
	{
		lim[0][pos.x - 1] = max(lim[0][pos.x - 1], pos.y + 1);
		get(0, pos.x - 1);
	}
	if(pos.y + 1 <= m)
	{
		lim[1][pos.y + 1] = min(lim[1][pos.y + 1], pos.x - 1);
		get(1, pos.y + 1);
	}
}
inline void search_B(Point pos)
{
//	cerr << "B " << pos.x << " " << pos.y << '\n';
	if(pos.x + 1 <= n)
	{
		lim[2][pos.x + 1] = min(lim[2][pos.x + 1], pos.y - 1);
		get(2, pos.x + 1);
	}
	if(pos.y - 1 >= 1)
	{
		lim[3][pos.y - 1] = max(lim[3][pos.y - 1], pos.x + 1);
		get(3, pos.y - 1);
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= k; ++i) cin >> p[i].x >> p[i].y >> p[i].val, p[i].id = i;
	memset(lim[1], 0x3f, sizeof(lim[1]));
	memset(lim[2], 0x3f, sizeof(lim[2]));
	lim[0][n] = m; lim[1][1] = 1;
	lim[2][1] = 1; lim[3][m] = n;
	for(int i = 1, v = 0; i <= k; ++i)
	{
		p[i].x ^= v, p[i].y ^= v;
		p[i].x %= n, p[i].y %= m;
		++p[i].x, ++p[i].y;
//		cerr << p[i].x << " " << p[i].y << " +++++++++++++++++++++++++++++\n";
		if(mp[{p[i].x, p[i].y}]) {cout << "NIE" << '\n'; continue;}
		mp[{p[i].x, p[i].y}] = true;
		if(!check(0, p[i]) && !check(1, p[i]) && !check(2, p[i]) && !check(3, p[i]))
		{
			cout << "NIE" << '\n';
			conS[0][p[i].x].push({p[i].y, i});
			conL[1][p[i].y].push({p[i].x, i});
			conL[2][p[i].x].push({p[i].y, i});
			conS[3][p[i].y].push({p[i].x, i});
		}
		else if((check(0, p[i]) || check(1, p[i])) && (check(2, p[i]) || check(3, p[i])))
		{
			cout << "TAK" << '\n';
			v ^= p[i].val; mp[{p[i].x, p[i].y}] = false;
		}
		else if(check(0, p[i]) || check(1, p[i])) cout << "NIE" << '\n', search_A(p[i]);
		else cout << "NIE" << '\n', search_B(p[i]);
	}
	return 0;
}
/*

*/
```

---

## 作者：FQ04gty (赞：4)

##### [原题链接](https://www.luogu.com.cn/problem/P5983)

---

考虑维护最靠上的可行路径和最靠下的可行路径。

其中，最靠上的路径的定义是：在路径可行的情况下，贪心地优先往 $y$ 方向走。

最靠下的路径定义以此类推，贪心地往 $x$ 方向走。

这样定义之后，可以发现，如果 $(x,y)$ 同时处于这两条路径之中，那么在这个位置上添加障碍，就会使合法路径不存在。

那么如何维护这两条路径呢？

这里展开最靠上的路径的维护方法，最靠下的路径可以以此类推。

我们记录对于每一个 $y=i$，在这一列中路径 $x$ 的最大位置 $v_i$。这里的最大不是使路径位置最大化，而是找到这条路径当前列的最靠下的点。

那么在一开始，这些值都是 $0$，特别的，$v_{m-1}=n-1$。

考虑加入一个新点 $(x,y)$。

若 $(x,y)$ 在路径上方，即 $x<v_{y-1}$。我们可以忽略这个点。

若 $(x,y)$ 在路径之中，即 $v_{y-1}\leq x\leq v_y$。我们发现要把路径绕过这个点，也就要把 $v_{y-1},v_y,\cdots,v_{m-1}$ 和 $x+1$ 来取 $\max$。这一操作可以用树状数组实现。

然后我们发现，绕过这个点以后，可能又会遇到新的障碍，因此我们递归地更新路径（具体方法见下文）。

若 $(x,y)$ 在路径下方，即 $x>v_y$。我们开两组 `set`，把它分别加入对应行、列的 `set` 中。

递归更新路径时在新路径所位于的行列的 `set` 里查一下有没有新障碍，如果有，递归更新。

我们更新路径的过程，实际上和贪心的过程是一致的，因此在答案上具有正确性。

由于一个点不会被更新路径两次，而对于输出 **TAK** 的需要撤销的操作只需要判断点的位置。

因此总时间复杂度是 $O(n\log n)$ 的（假设 $n$、$k$ 同阶）。

### Code

```cpp
#include<cstdio>
#include<set>
#include<cctype>
#define lowbit(x) (x&-x)
typedef std::pair<int,int> pii;
const int SIZE=1e5+1;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x;
}
inline void TAK(){putchar('T'),putchar('A'),putchar('K'),putchar('\n');}
inline void NIE(){putchar('N'),putchar('I'),putchar('E'),putchar('\n');}
int n,m,k,r,c,z,v,X,Y,f1,f2,c1,c2;
std::set<int>lin[SIZE],cur[SIZE];
inline void insert(const int x,const int y){lin[x].insert(y),cur[y].insert(x);}
inline void erase(const int x,const int y){lin[x].erase(y),cur[y].erase(x);}
namespace FLOOR
{
    int t[SIZE];
    inline void build(){for(int i=0;i<=m;i++)t[i]=1;}
    inline void modify(int x,const int val){while(x<=m)t[x]=std::max(t[x],val),x+=lowbit(x);}
    inline int query(int x){int res=0;while(x)res=std::max(res,t[x]),x-=lowbit(x);return res;}
    void dfs(const int x,const int y)
    {
        if(x<query(y-1))return;
        erase(x,y),modify(y-1,x+1);
        std::set<int>::iterator tmp;
        if(x^n)
        {
            tmp=lin[x+1].lower_bound(y-1);
            if(tmp!=lin[x+1].end())dfs(x+1,*tmp);
        }
        if(y^1)
        {
            tmp=cur[y-1].lower_bound(x+1);
            if(tmp!=cur[y-1].begin())dfs(*(--tmp),y-1);
        }
    }
}
namespace CEIL
{
    int t[SIZE];
    inline void build(){for(int i=0;i<=m;i++)t[i]=n;}
    inline void modify(int x,const int val){while(x)t[x]=std::min(t[x],val),x-=lowbit(x);}
    inline int query(int x){if(!x)return 1;int res=n+1;while(x<=m)res=std::min(res,t[x]),x+=lowbit(x);return res;}
    void dfs(const int x,const int y)
    {
        if(x>query(y))return;
        erase(x,y),modify(y,x-1);
        std::set<int>::iterator tmp;
        if(x^1)
        {
            tmp=lin[x-1].lower_bound(y+1);
            if(tmp!=lin[x-1].begin())dfs(x-1,*(--tmp));
        }
        if(y^m)
        {
            tmp=cur[y+1].lower_bound(x-1);
            if(tmp!=cur[y+1].end())dfs(*tmp,y+1);
        }
    }
}
inline void check(const int x,const int y)
{
    if(x==1&&y==1||x==n&&y==m)return v^=z,TAK();
    f1=FLOOR::query(y-1),c2=CEIL::query(y);
    if(x<f1||x>c2)return NIE();
    f2=FLOOR::query(y),c1=CEIL::query(y-1);
    if(c1<=x&&x<=c2&&f1<=x&&x<=f2)return v^=z,TAK();
    NIE();
    if(x<f1||x>c2)return;
    if(c1<=x&&x<=c2)return CEIL::dfs(x,y);
    if(f1<=x&&x<=f2)return FLOOR::dfs(x,y);
    insert(x,y);
}
int main()
{
    n=read(),m=read(),k=read();
    FLOOR::build(),FLOOR::modify(m,n),CEIL::build();
    for(int i=1;i<=k;i++)
    {
        r=read(),c=read(),z=read();
        X=(r^v)%n+1,Y=(c^v)%m+1;
        if(lin[X].count(Y)){NIE();continue;}
        check(X,Y);
    }
    return 0;
}
```

---

## 作者：Eznibuil (赞：0)

喜提最劣解一份。

很容易想到一个经典的模型：有一个矩形的黑白图片，如果白色无法从左边界连通到右边界，则黑色必然能从上边界连通到下边界。同理如果白色无法从左上角连通到右下角，则黑色必然能从左边界或下边界连通到右边界或上边界。

但是这道题有一个毒瘤的限制：必须只能往下或者往右。

于是略微地对模型稍加修改：对于一个点 $(r_1,c_1)$ 如果存在点 $(r_2,c_2)$ 满足 $r_2=r_1-1\land c_2\le c_1+1\lor r_2\ge r_1-1\land c_2=c_1+1$ 则从前者向后者连一条有向边。现在只需要时刻检查能否从左下边界走到右上边界。

然后就只需要建立三个集合代表可以从左下边界走到的点、可以走到右上边界的点和不知道能不能走的点。每次读入点时采用 DFS 更新集合即可。

时间复杂度 $O(k\log k)$。
```cpp
#include<iostream>
#include<set>
int n,m;
std::set<int>sr[100001],sc[100001],tr[100001],tc[100001],ur[100001],uc[100001];
void dfs(int r,int c)
{
	ur[r].erase(c),uc[c].erase(r),sr[r].insert(c),sc[c].insert(r);
	if(r)
	{
		auto it{ur[r-1].upper_bound(c+1)};
		if(it!=ur[r-1].begin())
			dfs(r-1,*--it);
	}
	if(c<m-1)
	{
		auto it{uc[c+1].lower_bound(r-1)};
		if(it!=uc[c+1].end())
			dfs(*it,c+1);
	}
	return;
}
void dft(int r,int c)
{
	ur[r].erase(c),uc[c].erase(r),tr[r].insert(c),tc[c].insert(r);
	if(r<n-1)
	{
		auto it{ur[r+1].lower_bound(c-1)};
		if(it!=ur[r+1].end())
			dft(r+1,*it);
	}
	if(c)
	{
		auto it{uc[c-1].upper_bound(r+1)};
		if(it!=uc[c-1].begin())
			dft(*--it,c-1);
	}
	return;
}
int main()
{
	std::cin.tie(nullptr)->sync_with_stdio(0);
	int k,v{};
	std::cin>>n>>m>>k;
	while(k--)
	{
		int r,c,z;
		std::cin>>r>>c>>z,r=(r^v)%n,c=(c^v)%m;
		if(sr[r].count(c)||tr[r].count(c)||ur[r].count(c))
		{
			std::cout<<"NIE\n";
			continue;
		}
		bool bs{r==n-1||!c||sr[r+1].lower_bound(c-1)!=sr[r+1].end()||sc[c-1].upper_bound(r+1)!=sc[c-1].begin()},bt{!r||c==m-1||tr[r-1].upper_bound(c+1)!=tr[r-1].begin()||tc[c+1].lower_bound(r-1)!=tc[c+1].end()};
		if(bs&&bt)
		{
			std::cout<<"TAK\n",v^=z;
			continue;
		}
		ur[r].emplace(c),uc[c].emplace(r),std::cout<<"NIE\n";
		if(bs)
			dfs(r,c);
		if(bt)
			dft(r,c);
	}
	return 0;
}
```

---

## 作者：Leasier (赞：0)

感觉维护最上最下两条可行路径有点太抽象了。

------------

直接维护连通性实在是太抽象了，考虑来维护一些特殊的路径——比如说**最靠上**（即可行时尽量往 $y$ 递增方向走）和**最靠下**（即可行时尽量往 $x$ 递增方向走）的路径，记之为 $P_1, P_2$。

- 当 $(x, y)$ 在 $P_1$ 上方或 $P_2$ 下方或在 $P_1, P_2$ 之间，其对 $P_1, P_2$ 无影响，于是可以插入。
- 当 $(x, y)$ 同时在 $P_1, P_2$ 上，显然所有路径都会经过这里，于是插入后不存在合法路径。
- 当 $(x, y)$ 在 $P_1, P_2$ 之一上，其会发生变化但必然存在合法路径，我们来讨论其变化。下面钦定 $(x, y) \in P_1$。

我们首先需要一种便于维护的方式表出 $P_1$：考虑设 $\operatorname{up}_i$ 表示 $P_1$ 在第 $i$ 列上最下方点的 $x$ 坐标，初始 $\forall i \in [0, m), \operatorname{up}_i = 1$，$\operatorname{up}_m = n$。

于是一个 $(x, y)$ 在 $P_1$ 上等价于 $x \in [\operatorname{up}_{y - 1}, \operatorname{up}_y]$。

当我们需要绕过一个 $(x, y)$，首先我们需要 $\forall i \in [y - 1, m]$，令 $\operatorname{up}_i \leftarrow \max(\operatorname{up}_i, x + 1)$。

但问题在于此时 $(x + 1, y - 1)$ 的右边或上边可能存在原来在 $P_1$ 下方的障碍，现在我们同样需要绕过它们。

递归处理即可。不难发现任何一个障碍都只会至多一次从“在 $P_1$ 下方”变为“在 $P_1$ 上方”，于是递归总次数为 $O(q)$。

树状数组维护 $\operatorname{up}_i$ 即可。

$P_2$ 可以类似地维护。时间复杂度为 $O(q(\log n + \log m))$。

代码：
```cpp
#include <set>
#include <cstdio>

using namespace std;

set<int> s1[100007], s2[100007];

inline int lowbit(int x){
	return x & (-x);
}

namespace Up {
	int tree[100007];
	
	inline void chkmax(int n, int x, int k){
		n++;
		x++;
		while (x <= n){
			tree[x] = max(tree[x], k);
			x += lowbit(x);
		}
	}
	
	inline int get_val(int x){
		int ans = 0;
		x++;
		while (x > 0){
			ans = max(ans, tree[x]);
			x -= lowbit(x);
		}
		return ans;
	}
	
	void forbid(int x, int y, int n, int m){
		if (x < get_val(y - 1)) return;
		s1[x].erase(y);
		s2[y].erase(x);
		chkmax(m, y - 1, x + 1);
		if (x < n){
			set<int>::iterator it = s1[x + 1].lower_bound(y - 1);
			if (it != s1[x + 1].end()) forbid(x + 1, *it, n, m);
		}
		if (y > 1){
			set<int>::iterator it = s2[y - 1].lower_bound(x + 1);
			if (it != s2[y - 1].begin()) forbid(*(--it), y - 1, n, m);
		}
	}
}

namespace Down {
	int tree[100007];
	
	inline void init(int n){
		n++;
		for (register int i = 1; i <= n; i++){
			tree[i] = 0x7fffffff;
		}
	}
	
	inline void chkmin(int x, int k){
		x++;
		while (x > 0){
			tree[x] = min(tree[x], k);
			x -= lowbit(x);
		}
	}
	
	inline int get_val(int n, int x){
		int ans = 0x7fffffff;
		n++;
		x++;
		while (x <= n){
			ans = min(ans, tree[x]);
			x += lowbit(x);
		}
		return ans;
	}
	
	void forbid(int x, int y, int n, int m){
		if (x > get_val(m, y)) return;
		s1[x].erase(y);
		s2[y].erase(x);
		chkmin(y, x - 1);
		if (x > 1){
			set<int>::iterator it = s1[x - 1].lower_bound(y + 1);
			if (it != s1[x - 1].begin()) forbid(x - 1, *(--it), n, m);
		}
		if (y < m){
			set<int>::iterator it = s2[y + 1].lower_bound(x - 1);
			if (it != s2[y + 1].end()) forbid(*it, y + 1, n, m);
		}
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline bool check(int x, int y, int n, int m){
	if (s1[x].count(y)) return false;
	int p1 = Up::get_val(y - 1), q2 = Down::get_val(m, y);
	if (x < p1 || x > q2) return false;
	int p2 = Up::get_val(y), q1 = Down::get_val(m, y - 1);
	bool f = p1 <= x && x <= p2, g = q1 <= x && x <= q2;
	if (f && g) return true;
	if (f){
		Up::forbid(x, y, n, m);
	} else if (g){
		Down::forbid(x, y, n, m);
	} else {
		s1[x].insert(y);
		s2[y].insert(x);
	}
	return false;
}

int main(){
	int n = read(), m = read(), k = read(), v = 0;
	Down::init(m);
	Up::chkmax(m, 0, 1);
	Up::chkmax(m, m, n);
	Down::chkmin(0, 1);
	Down::chkmin(m, n);
	for (register int i = 1; i <= k; i++){
		int r = read(), c = read(), z = read(), x, y;
		x = (r ^ v) % n + 1;
		y = (c ^ v) % m + 1;
		if (check(x, y, n, m)){
			printf("TAK\n");
			v ^= z;
		} else {
			printf("NIE\n");
		}
	}
	return 0;
}
```

---

