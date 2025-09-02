# [AGC023F] 01 on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc023/tasks/agc023_f

すぬけ君は、$ N $ 頂点からなる根付き木を持っています。 頂点には $ 1 $ から $ N $ までの番号が振られています。 頂点 $ 1 $ はこの木の根です。 頂点 $ i $ ( $ 2\leq\ i\ \leq\ N $ ) の親は頂点 $ P_i $ ( $ P_i\ <\ i $ ) です。 各頂点には、$ 0 $ または $ 1 $ が書かれていて、頂点 $ i $ に書かれている数は $ V_i $ です。

すぬけ君は、この木の頂点を横一列に並べたいと考えています。 その際、どの頂点についても、その頂点より右側にその頂点の先祖となる頂点がないようにします。

頂点を並べ終えたあと、頂点に書かれている数を頂点の並び順に沿って並べた数列を $ X $ とします。 すぬけ君は、$ X $ の転倒数 ( ※ ) を最小化したいです。 $ X $ の転倒数の最小値を求めてください。

## 说明/提示

### 注釈

ある長さ $ N $ の数列 $ Z $ の転倒数とは、整数 $ i,\ j $ ( $ 1\ \leq\ i\ <\ j\ \leq\ N $ ) の組であって、$ Z_i\ >\ Z_j $ を満たすものの個数を意味します。

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ <\ i $ ( $ 2\ \leq\ i\ \leq\ N $ )
- $ 0\ \leq\ V_i\ \leq\ 1 $ ( $ 1\ \leq\ i\ \leq\ N $ )
- 入力はすべて整数である。

### Sample Explanation 1

頂点を $ 1,\ 3,\ 5,\ 6,\ 2,\ 4 $ の順に並べると、$ X\ =\ (0,\ 1,\ 0,\ 0,\ 1,\ 0) $ となり、 転倒数は $ 4 $ になります。 これ以上転倒数を小さくすることは出来ないので、$ 4 $ を出力します。

### Sample Explanation 2

$ X\ =\ (0) $ で、転倒数は $ 0 $ です。

## 样例 #1

### 输入

```
6
1 1 2 3 3
0 1 1 0 0 0```

### 输出

```
4```

## 样例 #2

### 输入

```
1

0```

### 输出

```
0```

## 样例 #3

### 输入

```
15
1 2 3 2 5 6 2 2 9 10 1 12 13 12
1 1 1 0 1 1 0 0 1 0 0 1 1 0 0```

### 输出

```
31```

# 题解

## 作者：FelFa_1414666 (赞：40)

很典型的一个贪心类型，这种题目通常会用一个叫做 `Exchange Argument` 的方法来构造正确的贪心策略。

[atcoder 题目传送门](https://atcoder.jp/contests/agc023/tasks/agc023_f) & [洛谷题目传送门](https://www.luogu.com.cn/problem/AT3957)

---

## Description

有一个 $n$ 个节点的树，每个节点有权值 $v_i=0\lor v_i=1$ ，求这颗树上节点的一个**拓扑序**（保证所有节点在它祖先之后），使得所有 $v_i$ 组成的序列中**逆序对数**最小，输出最小逆序对个数。

- $1\le n\le 2\times 10^5$
- $v_i=0\lor v_i=1$

---

## Analysis

考虑没有拓扑序限制的情况下，最优解一定形如：`0,0,...,1,1,1,...`，所有 1 放在最后，逆序对数为 0。

我们希望答案的拓扑序尽可能的接近这个序列，所以有一个初步贪心的想法：

> 一旦可选节点中有 $v_i=0$，先选这个节点一定不会更劣。所以对于 $v_i=0$ 的节点，一旦父亲被选了，就立即选它。

基于这个想法，我们可以将这个节点与父亲节点“**合并**”，因为它们一定是序列中相邻的。

接下来考虑合并后的节点如何维护他的权值。这里要用到 `Exchange Argument` 的套路。设两个节点（单个节点或多个合并的节点）分别为 $a$ 和 $b$，设 $a$ 节点包含的所有小节点中有 $a_0$ 个 0 和 $a_1$ 个 1。同样地，$b$ 包含的所有小节点中有 $b_0$ 个 0 和 $b_1$ 个 1。分别考虑先选 $a$ 与先选 $b$ 造成的逆序对个数谁更优，当且仅当：$a_1\times b_0<b_1\times a_0$ 时，先选 $a$ 更优。即：

$$\dfrac{a_1}{a_0}<\dfrac{b_1}{b_0}$$

所以新合并节点的权值就是 $\dfrac{cnt_1}{cnt_0}$。

---

## Solution

由于我们已经证明了这个贪心的正确性，接下来我们要做的，就是维护一个**优先队列**，每次取出权值最小的节点，将其与父节点合并。每次合并时统计对答案的贡献，直到所有节点合并为 1 个为止。在过程中就已经将最优答案求了出来。

具体实现上，用**并查集**去维护一下合并节点中的信息。注意权值$\dfrac{cnt_1}{cnt_0}$ 中当 $cnt_0=0$ 要取 $+\infty$。

- 时间复杂度：$O(n\log n)$，忽略并查集操作的复杂度。

- 空间复杂度：$O(n)$

---

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pdi pair<double,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const double INF=1e18;
int n,a[200005],fa[200005],p[200005];
bool vis[200005];
ll ans,cnt1[200005],cnt0[200005];
int find(int x){return (fa[x]==x?x:find(fa[x]));}
void merge(int x,int y)//并查集合并操作
{
	x=find(x),y=find(y);
	ans+=cnt1[y]*cnt0[x];//记录对逆序对总数的贡献
	cnt1[y]+=cnt1[x];//合并后加上0 1个数
	cnt0[y]+=cnt0[x];
	fa[x]=y;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	p[0]=-1;
	for(int i=1;i<n;i++)
	{
		cin>>p[i];
		--p[i];
	}
	priority_queue<pdi,vector<pdi>,greater<pdi> > pq;//优先队列按权值升序存节点
	for(int i=0;i<n;i++)
	{
		fa[i]=i;
		cin>>a[i];
		if (a[i]) ++cnt1[i];
		else ++cnt0[i];
		pq.push(mp((cnt0[i]==0?INF:1.0*cnt1[i]/(1.0*cnt0[i])),i));
	}
	while(!pq.empty())
	{
		int u=pq.top().S;
		pq.pop();
		if (vis[u])
			continue;
		vis[u]=1;
		if (p[u]!=-1)//与父亲所在节点合并
		{
			int x=find(p[u]);
			merge(u,x);
			pq.push(mp((cnt0[x]==0?INF:1.0*cnt1[x]/(1.0*cnt0[x])),x));//将新节点加入优先队列
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

希望题解对你有帮助！

---

## 作者：Lice (赞：15)

### Description

给定一颗 $n$ 个结点的树，每个点有一个点权 $v$。点权只可能为 $0$ 或 $1$。

现有一个空数列，每次可以向数列尾部添加一个点 $i$ 的点权 $v_i$，但必须保证此时 $i$ 没有父结点。添加后将 $i$ 删除。

这样可以一个长为 $n$ 的数列 $x$。求 $x$ 中逆序对数的最小值。

### Hint

- $1\le n\le 2\times 10^5$
- $v_i \in \{0, 1\}$

### Solution

由于一个结点的父结点尚未被删除，那么现在该结点则无法被加入数列。可见题目要求我们 **从树根自顶向下** 删除。

但显然我们不会这样做——我们 **将所有结点视作独立，向父亲方向合并**。

----------------------

我们不妨先考虑这样一个问题：对于一个根结点为 $x$ 的树，其子结点为 $y_1, y_2, \cdots y_k$。假设子树 $y_1, y_2, \cdots y_k$ 都已经合并好了，那么我们只要将这些子树合并答案，向上传答案即可。

首先，由题意得，结点 $x$ 的点权必须排在最前面。接下来就需要合理安排顺序，使得 **跨越子树的逆序对** 数量最小。由于子树内在前期早已统计完毕，此处无需再做讨论。

为方便讨论，在这里我们还需维护子树中 $0, 1$ 的个数，分别记为 $\text{cnt}(\cdots, 0), \text{cnt}(\cdots, 1)$。

若要使逆序对尽可能小，而权值就只有 $0, 1$，第一直觉就是 **贪心地把** $0$ **尽量排前面**。

但直觉是很模糊的，我们需要一个明确的标准。

对于两个子树 $y_i, y_j$，如果 $y_i$ 排在前面，那么会产生 $\text{cnt}(y_i, 1)\times \text{cnt}(y_j, 0)$ 个逆序对，反正则会产生 $\text{cnt}(y_j, 1)\times \text{cnt}(y_i, 0)$ 个。

显然我们应选择结果较少的策略——优先选取 $\dfrac{\text{cnt}(y, 0)}{\text{cnt}(y, 1)}$ 较小的。*为避免除以零造成 RE，需要化除为乘。*

---------------------

但此题不能直接递归处理，需要全局一起算，即上文中“将所有结点视作独立，向父亲方向合并”的思路。

那么子树的 $\text{cnt}$ 值就变成了 **连通块** 的 $\text{cnt}$ 值，容易发现上面的贪心思路于此仍然有效。

此处涉及连通块整块信息的维护，不难想到 **并查集**。连通块的有序维护，可以使用 *堆*。

在每个点向上合并后，父亲方向结点需要删去，这对于堆来说就不太方便（当然可以考虑 multiset 或 [可删堆](https://www.cnblogs.com/-Wallace-/p/13226223.html)）

但其实不用这么麻烦：直接根据 $\text{cnt}$ 值判断是否已经被合并然后选择性跳过即可。

最后做到 1 号点就不用重新插入堆中了。

### Code

https://www.cnblogs.com/-Wallace-/p/13278211.html

---

## 作者：樱雪喵 (赞：5)

Tags: 贪心，Exchange Argument

其实这个奇怪名字的东西就是临项交换。

在树上删点不好做，我们考虑把过程倒过来：从 $n$ 个点的初始状态开始，每个选择一个点，令它与原树上的父亲连边。这在原题意中表示删完父亲之后立即删除这个点所在的连通块。

那么在合并的过程中，同一个连通块内部的最少贡献是不变的。我们所要做的事情是合理地安排它们的顺序，使不同连通块之间的产生贡献最小。

设节点 $a,b$ 所在连通块的 $0,1$ 个数分别为 $a_0,a_1,b_0,b_1$，那么如果 $a$ 排在 $b$ 前面，跨过连通块的贡献为 $a_1\times b_0$。也就是说，$a$ 排在 $b$ 前面更优的条件是

$$
a_1\times b_0<b_1\times a_0
$$
即
$$\frac{a_1}{a_0}<\frac{b_1}{b_0}$$

故我们将连通块按照 $\frac{a_1}{a_0}$ 的值从小到大进行合并即为最优方案。这可以使用大根堆维护。

```cpp
#define int long long
const int N=2e5+5;
int n,f[N];
int fa[N];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
int ans;
struct node
{
	int x,cnt[2];
	friend bool operator <(const node &x,const node &y)
    {
		return x.cnt[0]*y.cnt[1]<x.cnt[1]*y.cnt[0];
	}
}a[N];
priority_queue<node> q;
void merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return;
	fa[y]=x;
	ans+=a[x].cnt[1]*a[y].cnt[0];
	a[x].cnt[1]+=a[y].cnt[1],a[x].cnt[0]+=a[y].cnt[0];
}
signed main()
{
	n=read();
	for(int i=2;i<=n;i++) f[i]=read();
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		int x=read(); a[i].x=i;
		a[i].cnt[x]++; q.push(a[i]);
	}
	while(!q.empty())
	{
		node u=q.top(); q.pop();
		int x=find(u.x);
		if(a[x].cnt[0]!=u.cnt[0]||a[x].cnt[1]!=u.cnt[1]) continue;
		if(f[x]) 
		{
			merge(f[x],x);
			q.push(a[find(f[x])]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xht (赞：5)

## [01 on Tree](https://atcoder.jp/contests/agc023/tasks/agc023_f)

### 题意

- 给定一棵 $n$ 个节点的有根树，每个点上有一个 $0/1$ 的权值。
- 你要将这些节点排成一行，要求每个节点的右侧不存在它的祖先，在此基础上最小化逆序对数。
- $n \le 2 \times 10^5$。

### 题解

考虑一开始每个节点为单独一个点，然后依次向上合并。

设此时节点 $i$ 中的点集为 $s_i$，记 $a_i$ 为其中 $0$ 的个数，$b_i$ 为其中 $1$ 的个数。

那么每次将 $\frac {a_i}{b_i}$ 最大的合并到 $p_i$ 是最优的，考虑一下某个点的两个儿子哪个先合并的贡献小就可以证明了。

于是用 `set` 和并查集维护这个过程，每次合并将答案加上贡献即可，时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 2e5 + 7;
int n, p[N], v[N], a[N], b[N], f[N];
ll ans;

struct G {
	int x, y, i;
	inline G() {}
	inline G(int i) : x(a[i]), y(b[i]), i(i) {}
	inline bool operator < (G o) const {
		if (1ll * x * o.y == 1ll * o.x * y) return i < o.i;
		return 1ll * x * o.y < 1ll * o.x * y;
	}
};
set<G> s;

int get(int x) {
	return x == f[x] ? x : (f[x] = get(f[x]));
}

int main() {
	rd(n), rda(p + 1, n - 1), rda(v, n);
	for (int i = 1; i <= n; i++) v[i] ? ++b[i] : ++a[i];
	for (int i = 2; i <= n; i++) s.insert(G(i));
	iota(f + 1, f + n + 1, 1);
	while (s.size()) {
		int i = (--s.end()) -> i, x = get(p[i]);
		s.erase(G(i));
		ans += 1ll * b[x] * a[i];
		if (x != 1) s.erase(G(x));
		a[x] += a[i], b[x] += b[i], f[i] = x;
		if (x != 1) s.insert(G(x));
	}
	print(ans);
	return 0;
}
```

---

## 作者：lzk5627 (赞：5)

考虑如果是逆序对最小的话,那么每次肯定能选0就选0.

那么可以考虑新建一颗树,仅有a为1的点,然后每个点有一个点权,大小为选了这个点之后能继续选的0的个数,要求一个顺序,选了父亲才能选儿子,使得 $\sum i*val_{p_i}$ 最小,这个东西发现对于最大的点,如果父亲选了他,那么下一个肯定要选他,所以就可以一直合并节点来做

时间复杂度nlogn

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read(){
	register int x=0;
	register char ch=getchar();
	while(ch<'0'||ch>'9')	ch=getchar();
	while(ch>='0'&&ch<='9')	x=x*10+(ch^48),ch=getchar();
	return x;
}
int n,a[N],b[N],f[N],si[N],fa[N];
int find(int x){
	return f[x]?f[x]=find(f[x]):x;
}
struct each{
	int x,y,id;
	each (int xx=0,int yy=0,int dd=0){
		x=xx,y=yy,id=dd;
	}
	bool operator < (const each k) const{
		return 1LL*x*k.y<1LL*k.x*y;
	}
};
priority_queue<each>que;
long long ans;
int main(){
	//freopen("1.out","w",stdout);
	//freopen("1.in","r",stdin);
	n=read();
	for(int i=2;i<=n;i++)	fa[i]=read();
	for(int i=1;i<=n;i++)	a[i]=read();
	for(int i=1;i<=n;i++)	si[i]=1;
	for(int i=2;i<=n;i++)
		if(!a[i])	f[i]=find(fa[i]),si[f[i]]+=si[i];
	for(int i=1;i<=n;i++)	if(a[i])	b[i]=1,ans+=(--si[i]);
	for(int i=2;i<=n;i++)	if(a[i])	que.push(each(si[i],b[i],i));
	for(int i=1;i<=n;i++)	fa[i]=find(fa[i]);
	for(int i=1;i<=n;i++)	f[i]=0;
	while(!que.empty()){
		each x=que.top();	que.pop();
		int k=x.id,y=find(fa[k]);
		if(!y||x.x!=si[k])	continue;
		ans+=1LL*b[y]*x.x,si[y]+=si[k],b[y]+=b[k],f[k]=y;
		que.push(each(si[y],b[y],y));
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：约瑟夫用脑玩 (赞：4)

这种套路的题起码见了 5 次以上。。。

显然是贪心选择使代价最小，而在树上只要子树总代价可以分开贡献通常就会拆开，考虑每次向父亲合并的贡献。

这道题先反着看转换成从子树往上走，然后逆序对的贡献显然可以拆开，上个可删堆就完了。

这类题通常的套路是贪心合并计算贡献，在这道题上合并的理解就是把儿子的排列接在祖先合并后的排列后面。

之前写这类题目都是用的 `priority_queue<Node>` ，看题解区全都是这样写的，但可删堆写着老麻烦了。

这里提供一下直接把 set 的 cmp 类手写一下的实现，我写包票绝对好用，~~话说这种技巧算是特别基础的吧怎么没人用啊~~。

```
template<class T>
struct cmp
{
	constexpr bool operator()(const T& x, const T& y) const
	{//compare
		return ((LL)sm[1][x]*sm[0][y]==(LL)sm[1][y]*sm[0][x])?x<y:((LL)sm[1][x]*sm[0][y]<(LL)sm[1][y]*sm[0][x]);
	}
};
set<int,cmp<int> >st;
//main：
	for(;!st.empty();)
	{
		x=*st.begin();st.erase(st.begin());fa[x]=y=Gf(pr[x]);//find x and y,then y <- x
		if(y^1)st.erase(st.find(y));//delete
		ans+=(LL)sm[1][y]*sm[0][x];sm[0][y]+=sm[0][x];sm[1][y]+=sm[1][x];//calc
		if(y^1)st.insert(y);//insert
	}
```

---

## 作者：1saunoya (赞：3)

首先呢，我们发现这个树，删的是没有祖先的。

反之我们可以让他反过来，删叶子，叶子删完了才能删祖先（这样方便一点。）

把每个子树独立化，然后我们发现这个其实是可以用堆贪心的，按照 $\frac{c0}{c1}$ 的大小选就好了。
（就考虑 i 在 j 前面的话产生的贡献其实是 $c1_i \times c0_j$，显然择优嘛…）


```cpp
#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct item {
	int c0, c1, i;
	bool operator <(const item &rhs) const {
		return (i64)c0 * rhs.c1 < (i64)c1 * rhs.c0;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> par(n, -1);
	for (int i = 1; i < n; i++) {
		std::cin >> par[i];
		--par[i];
	}
	std::vector<std::vector<int>> cnt(n, std::vector<int>(2, 0));
	for (int i = 0; i < n; i++) {
		int x;
		std::cin >> x;
		cnt[i][x]++;
	}
	std::vector<int> p(n);
	std::iota(p.begin(), p.end(), 0);
	i64 ans = 0;
	std::priority_queue<item> q;
	for (int i = 1; i < n; i++) {
		q.push({cnt[i][0], cnt[i][1], i});
	}
	auto find = [&](int x) ->int{
		while (x != p[x]) {
			x = p[x] = p[p[x]];
		}
		return x;
	};
	while (!q.empty()) {
		auto it = q.top(); q.pop();
		int x = find(it.i), c0, c1;
		std::tie(c0, c1) = {it.c0, it.c1};
		if (cnt[x][0] != c0) {
			continue;
		} else if (cnt[x][1] != c1) {
			continue;
		} else {
			int y = find(par[x]);
			ans += (i64)cnt[y][1] * cnt[x][0];
			cnt[y][0] += cnt[x][0];
			cnt[y][1] += cnt[x][1];
			p[x] = y;
			if (y != 0) {
				q.push({cnt[y][0], cnt[y][1], y});
			}
		}
	}
	std::cout << ans << "\n";
	return 0;
}
```

---

## 作者：Kinandra (赞：3)

标签: 构造.

考虑构造一个合法的排列: 初始将每个点看成一个连通块, 每次选择一个之前未被选择过的非根节点 $u$ , 将 $u$ 和 $u$ 的父亲连通块合并, $u$ 连通块代表的序列接在其父亲之后. 容易发现这个构造方法可以构造出所有的合法排列.

我们发现必然有一个最优的选择方案使得每次选择都是选择**连通块内 $0$ 的个数除以 $1$ 的个数($1$ 的个数为 $0$ 是为 $+\infty$)最大的点**. 所以我们使用堆(或者set)来维护一下每个连通块的比值就好了.

时间复杂度 $\mathcal O(n\log n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n;
int p[400005], fa[400005];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct P {
    long long s[2], i;
    P operator+(P a) { return (P){s[0] + a.s[0], s[1] + a.s[1], i}; }
    bool operator<(P a) const {
        if (s[0] * a.s[1] == s[1] * a.s[0])
            return (s[0] == a.s[0]) ? (s[1] == a.s[1] ? i < a.i : s[1] < a.s[1])
                                    : s[0] < a.s[0];
        return s[0] * a.s[1] < s[1] * a.s[0];
    }
    bool operator==(P a) const {
        return s[0] == a.s[0] && s[1] == a.s[1] && i == a.i;
    }
} t[400005];

struct Q {
    priority_queue<P> q1, q2;
    void ins(P t) { q1.push(t); }
    void del(P t) { q2.push(t); }
    P top() {
        while (!q1.empty() && !q2.empty() && q1.top() == q2.top())
            q1.pop(), q2.pop();
        return q1.top();
    }

} q;

int main() {
    n = read();
    for (int i = 2; i <= n; ++i) p[i] = read();
    for (int i = 1; i <= n; ++i) t[i].s[read()] = 1, t[i].i = fa[i] = i;
    for (int i = 2; i <= n; ++i) q.ins(t[i]);
    long long res = 0;
    for (int i = 2; i <= n; ++i) {
        P u = q.top(), v = t[find(p[u.i])];
        if (v.i != 1) q.del(v);

        q.del(u), res += v.s[1] * u.s[0], v = v + u, fa[u.i] = fa[v.i];
        t[u.i] = u, t[v.i] = v;

        if (v.i != 1) q.ins(v);
    }

    printf("%lld\n", res);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：Illus1onary_Real1ty (赞：2)

很套路的题目。

考虑到每次取出数字都是以一条链的形式取出的，我们考虑把它分成很多个块，进行邻项交换。

对于每个块，必然有 $cnt0$ 和 $cnt1$。

假设 $a$ 块在前，若 $cnt1_a \times cnt0_b > cnt0_a \times cnt1_b$，那么交换 $a$ 块和 $b$ 块必然不劣。

整理式子，发现我们可以以 $\frac{cnt0}{cnt1}$ 为权值，权值越大的越先取出，显然可以用堆维护。

我们再考虑如何处理取出这件事。

考虑到树上贪心常用的套路，又考虑到此题的要求，可以将当前取出的块合并到其父亲所在的块，可以用并查集维护。

时间复杂度 $O(n \times \log{n})$，附代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef double db;
const int N = 2e5 + 10;
const int INF = 200001;
int n, ans = 0, p[N], fa[N], vis[N], cnt0[N], cnt1[N];

struct Node{
	int u;
	db val;
	
	Node() {}
	
	Node(int u_, db val_){
		u = u_;
		val = val_;
	}
	
	bool operator < (const Node& b) const{
		return val < b.val;
	}
};

priority_queue<Node> pq;

int Find(int x){
	if (fa[x] == x)
		return x;
	
	return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
	x = Find(x);
	y = Find(y);
	
	ans += cnt1[y] * cnt0[x];
	fa[x] = y;
	cnt0[y] += cnt0[x];
	cnt1[y] += cnt1[x];
}

signed main(){
	cin >> n;
	for (int i = 2; i <= n; i++)
		cin >> p[i];
	for (int i = 1, x; i <= n; i++){
		cin >> x;
		fa[i] = i;
		
		if (x)
			cnt1[i]++;
		else	cnt0[i]++;
		
		pq.push(Node(i, (cnt1[i]==0?INF*1.0:1.0*cnt0[i])));
	}
	
	while (!pq.empty()){
		int u = pq.top().u;
		pq.pop();
		
		if (vis[u])
			continue;
		vis[u] = 1;
		
		if (u == 1)
			continue;
		
		Merge(u, p[u]);
		u = Find(u);
		pq.push(Node(u, (cnt1[u]==0?INF*1.0:1.0*cnt0[u]/cnt1[u])));
	}
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：小超手123 (赞：2)

##### 题意：

[[AGC023F] 01 on Tree](https://www.luogu.com.cn/problem/AT_agc023_f)

##### 分析：

如果没有子节点必须在父节点后选的限制条件，最终序列一定为 $0,0,\dots,0,1,1,\dots,1$。

考虑一个弱化问题：

> 给定 $n$ 个 $01$ 序列，可以任意排列这 $n$ 个序列的位置，求逆序对的最小值。

设两个序列的 $0$ 与 $1$ 的个数分别为 $A_{0},A_{1},B_{0},B_{1}$，那么有：

-  $A$ 在 $B$ 前面：$\Delta_{逆序对}=A_{1}B_{0}$。
- $B$ 在 $A$ 前面：$\Delta_{逆序对}=A_{0}B_{1}$。

当 $A_{1}B_{0} < A_{0}B_{1}$ 时，$A$ 会放在 $B$ 前面，即 $\frac{A_{1}}{A_{0}} < \frac{B_{1}}{B_{0}}$。

回到原问题，对于节点 $x$ 的一个儿子 $y$，若其为 $0$，在选择 $x$ 后立刻选择 $y$ 一定不会更劣。

因此可以用并查集维护每个连通块，每次从数据结构中找到 $\frac{A_{1}}{A_{0}}$ 的最小的连通块，把它与它的父亲连通块合并（即钦定它的父亲连通块选完后立刻选 $y$）。

时间复杂度 $O(n \log n)$。

##### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n;
int father[N], a[N], fa[N];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int s0[N], s1[N], P[N];
struct node {
	int x;
	friend bool operator < (node A, node B) {
		if(s1[A.x] * s0[B.x] == s0[A.x] * s1[B.x]) return A.x < B.x;
		return s1[A.x] * s0[B.x] < s0[A.x] * s1[B.x];
	}
};
set<node>Q;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++) cin >> father[i];
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		fa[i] = i;
		if(a[i] == 0) s0[i] = 1;
		else s1[i] = 1;
		if(i != 1) Q.insert((node){i});
	}
	while(!Q.empty()) {
		auto Get = Q.begin();
		node cmp = (*Get);
		if(cmp.x != 1) Q.erase(Get);
		int fx = find(cmp.x), fy = find(father[cmp.x]);
		if(cmp.x == 1 || fx == fy) continue;
		fa[fx] = fy;
		if(fy != 1) Q.erase((node){fy}); 
		P[fy] += (P[fx] + s1[fy] * s0[fx]);
		s0[fy] += s0[fx];
		s1[fy] += s1[fx];
		if(fy != 1) Q.insert((node){fy}); 
	}
	cout << P[find(1)];
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/AT_agc023_f)，[个人博客内食用更佳](https://www.luogu.com.cn/blog/Hok/solution-AT_agc023_f)。

补题的时候补到的，好题。
## 思路分析
考虑贪心，题目要求我们造出来最后的序列是要逆序对最少，观察题目发现只有 $1,0$，所以只要尽量让 $0$ 在前，$1$ 在后就可以造成最少的逆序对数了。

那我们就考虑如果目前拿的节点里有个是 $0$ 的就直接拿他，这样肯定是最优的。

反正 $0$ 的节点在他的父亲拿走了之后他就要直接拿走，那他不就可以和他的父亲节点合并起来了吗，再考虑一下新点的权值即为 $\frac{cnt_1}{cnt_0}$。

那我们便可以得到每个点拿掉的价值，考虑用优先队列维护，答案每次加上贡献即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long
using namespace std;
struct node
{
	int x,y,id;
	node(int xx=0,int yy=0,int idd=0){x=xx,y=yy,id=idd;}
	bool operator<(const node a)
		const{return x*a.y<a.x*y;}
};
int n,ans;
int fa[200010],a[200010],f[200010],si[200010],b[200010];
priority_queue<node>q;
int find(int x){return f[x]?f[x]=find(f[x]):x;}
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),f(1);char c(getchar());
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
	n=read();
	for(int i=2;i<=n;i++) fa[i]=read();
	for(int i=1;i<=n;i++) a[i]=read(),si[i]=1;
	for(int i=2;i<=n;i++) if(!a[i]) f[i]=find(fa[i]),si[f[i]]+=si[i];
	for(int i=1;i<=n;i++) if(a[i]) b[i]=1,ans+=(--si[i]);
	for(int i=2;i<=n;i++) if(a[i]) q.push(node(si[i],b[i],i));
	for(int i=1;i<=n;i++) fa[i]=find(fa[i]);memset(f,0,sizeof f);
	while(!q.empty())
	{
		node x=q.top(); q.pop();int k=x.id,y=find(fa[k]);
		if(!y||x.x!=si[k]) continue;
		ans+=b[y]*x.x,si[y]+=si[k],b[y]+=b[k],f[k]=y;
		q.push(node(si[y],b[y],y));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：tommymio (赞：1)

看了 $\text{WC2021}$ 后来补的这道题。

不妨先想一个更强的问题，一棵 $n$ 个点的树，每个点上有一串 $0/1$ 序列，求按一定顺序取完所有点以后构成的 $0/1$ 序列的逆序对数最少。

可以考虑两个序列 $p$ 中相邻的点 $p_i,p_{i+1}$，设点 $x$ 的序列中有 $a_x$ 个 $0$，$b_x$ 个 $1$。显然交换这两个点后，贡献由 $b_{p_i}\times a_{p_{i+1}}$ 变为 $b_{p_{i+1}}\times a_{p_i}$。我们希望交换后贡献更小，所以仅当 $b_{p_{i+1}}\times a_{p_i}\leq b_{p_{i}}\times a_{p_{i+1}}$ 时才交换这两者，把这个不等式变形得到 $\frac{a_{p_i}}{b_{p_i}}\leq \frac{a_{p_{i+1}}}{b_{p_{i+1}}}$。

现在加上祖先节点必须先于子孙节点被取的限制，可以发现我们根据上述性质，将当前 $\frac{a_x}{b_x}$ 最小的点调整到 $x$ 的父亲之后第一个位置，不会更劣。那我们就这样调整就好了，每次合并当前 $\frac{a_x}{b_x}$ 最小的 $x$ 及其父亲所在的连通块，使用并查集维护连通块，小根堆维护比值最小即可。

这里需要用到一个灵性的科技，当然 $\text{lyd}$ 在他的蓝书入门篇中就已提及到了。就是支持删除队列中任一元素的小根堆，我们可以使用对顶堆实现。但值得注意的是，**对顶堆的重载函数真值表必须唯一确定**，否则会存在两个堆内元素顺序不定，无法退堆的情况。

```cpp
#include<cstdio>
#include<queue>
typedef long long ll;
struct node {
    node() {}
    node(const node &coc) {
        x=coc.x; fa=coc.fa; c[0]=coc.c[0]; c[1]=coc.c[1];
    }
    inline node operator=(const node &coc) {
        x=coc.x; fa=coc.fa; c[0]=coc.c[0]; c[1]=coc.c[1];
        return *this;
    }
    int x,fa,c[2];
}p[200005];
int fa[200005];
inline bool operator==(const node &x,const node &y) {return x.x==y.x&&x.c[0]==y.c[0]&&x.c[1]==y.c[1];}
//inline bool operator<(const node &x,const node &y) {return x.c[0]*y.c[1]>x.c[1]*y.c[0];}
inline bool operator<(const node &x,const node &y) {
    if(x.c[0]*1ll*y.c[1]==x.c[1]*y.c[0]) {
        return x.c[0]==y.c[0]? (x.c[1]==y.c[1]? x.x<y.x:x.c[1]<y.c[1]):x.c[0]<y.c[0];
    }
    return x.c[0]*1ll*y.c[1]<x.c[1]*1ll*y.c[0];
}
struct SuperQueue {
    std::priority_queue<node> q1,q2;
    inline void push(const node &x) {q1.push(x);}
    inline void pop(const node &x) {q2.push(x);}
    inline const node top() {
        while(q1.size()&&q2.size()&&q1.top()==q2.top()) q1.pop(),q2.pop();
        return q1.top();
    }
}Q;
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
int main() {
    int n=read(); ll res=0;
    for(register int i=2;i<=n;++i) p[i].fa=read();
    for(register int i=1;i<=n;++i) {p[i].c[read()]=1; p[i].x=fa[i]=i;}
    for(register int i=2;i<=n;++i) Q.push(p[i]);
    for(register int T=1;T<n;++T) {
        node now=Q.top(),pref=p[find(now.fa)];
        if(pref.x!=1) Q.pop(pref);
        Q.pop(now); res+=now.c[0]*1ll*pref.c[1]; 
        pref.c[0]+=now.c[0]; pref.c[1]+=now.c[1];
        fa[now.x]=fa[pref.x]; p[pref.x]=pref;
        if(pref.x!=1) Q.push(pref);
    }
    printf("%lld\n",res);
    return 0;
}
```



---

## 作者：activeO (赞：1)

## 题目大意

算了，这里不讲了，[题面](https://www.luogu.com.cn/problem/AT3957)已经讲的很清楚了。

## 思路

首先知道要使逆序对数最小，只要尽量把 $ 0 $ 放在前面，**就是 $ 0 $ 尽早入序列就好了。**

然后你去考虑从父亲节点删下去会发现不好想，于是一个很经典的处理方法，反着来！我们就**一开始让每一个节点独立，然后每次操作用并查集合并就好了。**

然后考虑每次出现 $ 1 $ 对答案的影响，这里记 $ cnt_{u,0/1} $ 表示在以 $ u $ 为根节点的子树中 $ 0,1 $ 的个数。然后就知道每次把 $ v $ 放在 $ u $ 前就会多 $ cnt_{v,1} \times cnt_{u,0} $，所以如果我们要让这个影响最小，就会优先选择 $ \frac{cnt_{x,0}}{cnt_{x,1}} $ 小的，然后未避免除以 $ 0 $，把他改成乘法形式。

我觉得这种贪心还挺好想的吧，主要是实现。

就有一个细节：有点向上合并时，堆中的父节点删掉，这里其实就把 $ cnt_{fa,0/1} $ 修改加上子节点的值就好了，然后每次判断 $ cnt_{u,0/1} $ 和堆中记录的一不一样就好了。（不一样就直接跳过）

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=2e5+5;
struct node{
	int id,cnt0,cnt1;
	bool operator <(const node &b) const {
		return cnt0*b.cnt1<cnt1*b.cnt0;
	}
	node(int ii,int c0,int c1){
		id=ii;
		cnt0=c0;
		cnt1=c1;
	}
};
priority_queue<node> que;
int fa[maxn],f[maxn];
//f->并查集
int cnt[maxn][3];

int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
inline void init(int n){
	for(int i=1;i<=n;i++) f[i]=i;
}

signed main(){
	
	int n;
	
	scanf("%lld",&n);
	for(int i=2;i<=n;i++) scanf("%lld",&fa[i]);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%lld",&x);
		cnt[i][x]++;
	}
	
	init(n);
	
	for(int i=2;i<=n;i++) que.push(node(i,cnt[i][0],cnt[i][1]));
	
	int res=0;
	
	while(!que.empty()){
		int u=que.top().id,cnt0=que.top().cnt0,cnt1=que.top().cnt1;
		que.pop();
		if(cnt[u][0]!=cnt0||cnt[u][1]!=cnt1) continue;
		int g=find(fa[u]);
		res+=cnt[g][1]*cnt[u][0];
		cnt[g][0]+=cnt[u][0];
		cnt[g][1]+=cnt[u][1];
		f[u]=g;
		if(g!=1) que.push(node(g,cnt[g][0],cnt[g][1]));
	}
	
	printf("%lld\n",res);
	
	return 0;
}
```


---

## 作者：chenxia25 (赞：1)

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/AT3957 ) & [AtC 题目页面传送门]( https://atcoder.jp/contests/agc023/tasks/agc023_f )
>
> 题意见洛谷里的翻译，节点 $i$ 权值为 $a_i$。

这是个 AGC 的 F，挺吓人的。但是仔细看发现跟 [P4437]( https://www.cnblogs.com/ycx-akioi/p/Luogu-P4437.html ) 差不多的，所以这是一个 AGC F 中的水题。

假设有 $m$ 个 $1$，这个 $m$ 显然是固定的。然后我们设 $m$ 个 $1$ 的位置为 $p_{1\sim m}$，这个 $p$ 定下来整个序列显然也定下来了。对于 $p$ 的一个取值，答案显然为 $\sum\limits_{i=1}^m(n-p_i-(m-i))$。随便推一下发现等于 $m(n-m)+\dfrac{m(m+1)}2-\sum\limits_{i=1}^mp_i$。于是题目转化为最大化 $ans=\sum\limits_{i=1}^mp_i$。

仿照 P4437 的推，我们考虑当前能选的节点集合中的任意两个点 $x,y$，若 $x$ 放最前面，尝试将 $y$ 换到最前面来变得更优。我们统一使用「将 $y$ 放到最前面，将 $y$ 前面依赖于或等于 $x$ 的全部顺移一位」这种方法来移动。

1. $a_x=a_y=0$：显然所有 $1$ 都往后移了，$ans$ 肯定增大，\sqrt{}；
2. $a_x=a_y=1$：稍有一丝复杂，注意到所有人移动距离之和等于 $0$，$y$ 的移动占据了所有负贡献，而其他的又不全是 $1$，所以最终对 $ans$ 变化量的总贡献是负的，\times；
3. $a_x=0,a_y=1$：跟 $2$ 类似，\times；
4. $a_x=1,a_y=0$：跟 $1$ 类似，\sqrt{}；

综合一下就是 \sqrt{} 当且仅当 $a_y=0$。合理性也挺好理解的，就跟 P4437 差不多嘛。然后如果没有 $0$ 的话，那显然就随便选了……于是与爸爸合并。然后考虑合并以后该如何比较。不难发现 $sz_id_i$ 守恒，然后 $ans$ 的贡献总值是 $\sum\limits_i cnt_id_i$。$cnt_id_i=\dfrac{cnt_i}{sz_i}sz_id_i$，于是找 $\dfrac{cnt_i}{sz_i}$ 当作最小的放在 $y$ 处与唯一的负距离贡献相乘即可。

**_UPD：_**然后发现，$\sum\limits_{i=1}^mp_i=\sum\limits_{i=1}^nia'_i$，那不就严格弱于 P4437 了吗？那我前面分析了那么多分析了个寂寞啊？

把 P4437 代码改几个字交上去就 A 了。

---

## 作者：良心WA题人 (赞：0)

假设没有必须取当前没有父亲的点这个限制，则必然是先 $0$ 后 $1$。

然而有这个性质。我们尝试把一些选点合并起来，防止过程中选择了一个有父亲的点。考虑点 $i$ 这个点有 $a$ 个 $0$ 和 $b$ 个 $1$。将内部的贡献计算完后，必然是按照 $\dfrac{b}{a}$ 排序。

那么如何去合并呢？考虑当我们被迫选择了一个不想选的点后会发生什么，此时当前点有一个权值 $\dfrac{b}{a}$。那么显然这个权值是目前所有可以取到的点里面最小的。取完这个后，如果接下来能取的所有点里面有权值更小的点，则下一步一定会取其中权值最小的一个（否则会取其他子树中一个权值大于 $\dfrac{b}{a}$ 的点，一定不优），则不断找到权值最小的与当前点合并起来，直到不存在权值比当前点更小的点。

当所有可取的点比当前点的权值都大时，排序的结果必然在当前点之后，所以不再进行合并。

找到可取的点中最小的是简单的。维护一个优先队列，将每个子树中最小的权值放入队列，每次取最小的一个即可。当某个子树的权值被取则将这个子树中的比它略大的权值放入队列即可。

至于继承子树信息的部分，当然可以使用可并堆，时间复杂度是 $O(n\log n)$ 的。不过本题数据范围宽裕，使用启发式合并 $O(n\log^2 n)$ 能够通过此题。

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[[AGC023F] 01 on Tree](https://www.luogu.com.cn/problem/AT_agc023_f)
## 分析
一个很显而易见的结论：**若能选的点中有点权为 $0$ 的点，那么先选该点一定是最优**。

不妨换个角度，这个点在其父被选择时，若该点在其父最前一次操作被选，那么一定最优，所以，我们可以将这些点与其父合并在一起，可以用并查集。

此时的问题是：以怎样的方式去合并两个并查集，不妨设一个集合 $i$ 中 $0$ 的个数为 $cnt_{i,0}$，$1$ 的个数为 $cnt_{i,1}$。

对于两个并查集 $i,j$ 若 $i$ 在 $j$ 前所增加的贡献数为 $cnt_{i,1} \times cnt_{j,0}$。

同理 若 $j$ 在 $i$ 前所增加的贡献数为 $cnt_{j,1} \times cnt_{i,0}$。

于是乎我们只需要比较上述两式，则 $i$ 在前更优的条件为：

$$ cnt_{i,1} \times cnt_{j,0} \lt cnt_{i,0} \times cnt_{j,1}$$

即 

$$ \frac{ cnt_{i,1} }{cnt_{i,0}} \lt \frac{cnt_{j,1}}{cnt_{j,0}} $$

所以，我们可以将每个并查集用 $\frac{cnt_{i,1}}{cnt_{i,0}}$，然后将这些分数塞进一个优先队列中，每次取出队首元素，并将其与其父亲的并查集合并，每次合并计算一次答案（计算方法见上文）。

最后合并为一个并查集之后所有合并的代价和即为答案。

时间复杂度为 $n\times\log n \times\alpha(n) $，可以通过。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const double inf=1e18;
struct node
{
	double dis;
	int id;
	bool operator <(const node &y)const
	{
		return dis>y.dis;
	}
};
priority_queue < node >q;
int p[200010];
int fa[200010];
int n;
int sum[200010][2];
int book[200010];
int ans;
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
signed main()
{
	scanf("%lld",&n);
	p[0]=-1;
	for(int i=1;i<n;i++)
	{
		scanf("%lld",&p[i]);
		p[i]--;
	}
	for(int i=0;i<n;i++)
	{
		fa[i]=i;
		int x;
		scanf("%lld",&x);
		sum[i][x]++;
		if(sum[i][0]==0)q.push((node){inf,i});
		else q.push((node){1.0*sum[i][1]/(1.0*sum[i][0]),i});
	}
	while(!q.empty())
	{
		int id=q.top().id;
		q.pop();
		if(book[id])continue;
		book[id]=1;
		if(p[id]!=-1)
		{
			int x=find(p[id]);
			int tx=find(id),ty=find(x);
			ans+=sum[ty][1]*sum[tx][0];
			sum[ty][1]+=sum[tx][1];
			sum[ty][0]+=sum[tx][0];
			fa[tx]=ty;
			if(sum[x][0]==0)
			q.push((node){inf,x});
			else q.push((node){1.0*sum[x][1]/(1.0*sum[x][0]),x});
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

