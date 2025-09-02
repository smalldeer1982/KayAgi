# Cookies

## 题目描述

Mitya 和 Vasya 正在玩一个有趣的游戏。他们有一棵有根树，这棵树有 $n$ 个顶点，顶点编号从 $1$ 到 $n$。根节点的编号为 $1$。对于每个 $i \ge 2$ 的顶点 $i$，它有一个父节点 $p_i$，顶点 $i$ 被称为顶点 $p_i$ 的子节点。

树上的每个顶点都有一些饼干：在顶点 $i$ 上有 $x_i$ 块饼干。在顶点 $i$ 吃一块饼干需要恰好 $t_i$ 的时间。树上还有一个芯片，最初位于树根。将芯片沿着连接顶点 $i$ 与其父节点的边移动，需要花费 $l_i$ 的时间。

Mitya 和 Vasya 轮流进行游戏，Mitya 先手。

- Mitya 可以将芯片从当前位置移动到它的某个子节点。
- Vasya 可以从芯片当前位置到其某个子节点的边中，移除一条边。Vasya 也可以选择跳过这回合。

Mitya 可以在自己的任意回合选择停止游戏。一旦他停止游戏，他会将芯片沿着路径返回到根节点，并在沿途的顶点吃掉一些饼干。Mitya 可以自行决定在每个经过的顶点吃多少块饼干。下行、上行和吃饼干所花费的总时间不能超过 $T$。请注意，游戏结束时芯片必须回到树根：Mitya 不能将芯片留在其他顶点，即使他已经吃够了饼干——他必须将芯片带回根节点（每次从顶点 $v$ 移动到其父节点都需要 $l_v$ 的时间）。

无论 Vasya 如何操作，请你求出 Mitya 最多能吃到多少块饼干。

## 说明/提示

在第一个样例测试中，Mitya 可以先将芯片移动到顶点 $2$。无论 Vasya 如何操作，Mitya 至少都能吃到 $11$ 块饼干。下面是详细的操作过程：

1. Mitya 将芯片移动到顶点 $2$。
2. Vasya 移除了与顶点 $4$ 相连的边。
3. Mitya 将芯片移动到顶点 $5$。
4. 由于顶点 $5$ 没有子节点，Vasya 不移除任何边。
5. Mitya 停止游戏，并将芯片带回根节点，在沿途吃掉饼干（在顶点 $5$ 吃 $7$ 块，在顶点 $2$ 吃 $3$ 块，在顶点 $1$ 吃 $1$ 块）。

Mitya 下行花费 $1+0$ 时间，上行花费 $0+1$ 时间，在顶点 $5$ 吃 $7$ 块饼干花费 $7\times 2$ 时间，在顶点 $2$ 吃 $3$ 块饼干花费 $3\times 3$ 时间，在顶点 $1$ 吃 $1$ 块饼干花费 $1\times 1$ 时间。总时间为 $1+0+0+1+7\times 2+3\times 3+1\times 1=26$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 26
1 5 1 7 7
1 3 2 2 2
1 1
1 1
2 0
2 0
```

### 输出

```
11
```

## 样例 #2

### 输入

```
3 179
2 2 1
6 6 6
1 3
2 3
```

### 输出

```
4
```

# 题解

## 作者：览遍千秋 (赞：6)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF530Div2)，欢迎来踩。

## F - Cookies

这题在考试时间内有了正确的思路但没有写完。。。

### $\mathrm{Vasya}$的策略

题目的表述中，$\mathrm{Vasya}$是可以随便剪断当前标记所在结点$x$到任意一棵子树的。

但是题目要求我们求的是最坏情况下的最小值，我们可以只考虑$\mathrm{Vasya}$创造了最坏的条件，即剪掉了本来可以取到最优解的子树。

### 树形$\mathrm{DP}$

首先做一次$\mathrm{DP}$，求出$\mathrm{Vasya}$不剪时的最优解，同时记录取到最优解的位置。

接下来标记不得进入之前最优解的位置，再做一次$\mathrm{DP}$。

这两次$\mathrm{DP}$等价于维护了每个结点的最优解和次优解。

在$\mathrm{DP}$的过程中使用了贪心的思想，显然从根到$x$的路径上，尽量吃花费时间少的饼干。

### 维护饼干

我一开始是想通过$\mathrm{vector}$或者$\mathrm{Heap}$来维护的，可是发现这样不太好实现，并且在链的情况下复杂度会退化为$O(n^2)$。

我$\color{purple} \text{太菜了}$并不会多少数据结构，于是自然而然想到使用树状数组来维护，树状数组的下标为$t$，插入的值为饼干数目。

然后二分$t$就行了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define maxn 100003
int n,T;
int x[maxn],t[maxn];
int Head[maxn],tot,Next[maxn],to[maxn],w[maxn];
int aa,bb;
int ans[maxn];
int fake;
template<typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

struct BIT{
	#define lowbit(x) (x&(-x))
	int c[1001003];
	void add(int x,int k){
		while(x<=1001000){
			c[x]+=k;x+=lowbit(x);
		}
	}
	int query(int x){
		int re=0;
		while(x){
			re+=c[x];x-=lowbit(x);
		}
		return re;
	}
}a,b;

void add(int x,int y,int z){
	to[++tot]=y,Next[tot]=Head[x],Head[x]=tot,w[tot]=z;
}

int erfen(int fa){
	int l=0,r=1000000,mid,re=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(a.query(mid)<=fa) re=mid,l=mid+1;
		else r=mid-1;
	}
	fake=l;
	return re;
}

int find(int node){
	int l=fake,r=1000000,re=0,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(b.query(mid)!=ans[node]) re=mid,r=mid-1;
		else l=mid+1;
	}
	return re;
}

void dfs(int node,int dis){
    int rest=T-2*dis;
    a.add(t[node],x[node]*t[node]);
    b.add(t[node],x[node]);
    int flag=erfen(rest);
    if(flag) ans[node]=b.query(flag),rest-=a.query(flag);
    flag=find(node);
    if(flag) ans[node]+=rest/flag;
    for(int i=Head[node];i;i=Next[i]){
    	dfs(to[i],dis+w[i]);
	}
    a.add(t[node],-x[node]*t[node]);
    b.add(t[node],-x[node]);
    int mx=0,del=0;
    for(int i=Head[node];i;i=Next[i]){
    	if(ans[to[i]]>mx){
    		mx=ans[to[i]],del=to[i];
    	}
    }
    if(node==1){
		ans[node]=max(ans[node],mx);
		return;
	}
    for(int i=Head[node];i;i=Next[i]){
    	if(to[i]==del) continue;
    	ans[node]=max(ans[node],ans[to[i]]);
    }
}

int main(){
	read(n);read(T);
	for(register int i=1;i<=n;i++){
		read(x[i]);
	}
	for(register int i=1;i<=n;i++){
		read(t[i]);
	}
	for(register int i=2;i<=n;i++){
		read(aa);read(bb);
		add(aa,i,bb);
	}
	dfs(1,0);
	printf("%I64d\n",ans[1]);
	return 0;
}
```

---

## 作者：CaoXian (赞：3)

校内模拟赛搬了这道题，考场上想出来的一个感觉更加无脑的方法，不需要 dp，但是实现起来会更恶心，细节多很多，码量大概是其它做法的两倍，仅供参考。

---

首先我们可以用线段树上二分来求出根节点到每个结点的路径能够吃掉的最大饼干数量。

具体的做法是：树上 dfs 的时候维护从根到当前节点的链上每个结点的饼干。贪心地想，想要在相同时间内吃掉更多的饼干，那么肯定是需要时间更短的饼干先吃。

所以对吃掉饼干需要的时间建线段树，维护某个时间区间（这个区间代表着它包含的每个饼干需要的时间下限和上限）吃掉所有的饼干所需时间以及饼干数量，要求出能吃掉的最大数量的饼干就可以线段树上二分解决了。

这一步需要注意，每次进入下一个结点的时候要将剩余时间减去边权的两倍，因为往返的时间都要计算。

接着我们可以将求得的所有答案从大到小排序。

因为先手是希望吃掉最多的饼干，所以后手肯定是想要将这些可能的答案从大到小依次给抹除。

当然，后手不是直接将这些答案去掉的，是通过让先手不能走这条链上的某些边来限制先手的。

于是我们可以考虑这条链上可以被加上限制的边，这些边应该是这条链上除了与根节点直接相连以外的所有边，并且只用割掉这些边中的一条就够了，割多了没用。

会是“深度”最小的那条边吗（这里的“深度”是指连接的两结点中较小的深度）？不是，反例很容易举出来，就是构造一个全局次大值与之相连。

那是不是割掉“深度”最大的边呢？手动模拟一下感觉好像是对的，但是感觉不好证明。其实可以用一个贪心的思路去理解：在同一条链上，深度越小的点覆盖到的子树越大，对应的可以去掉的答案范围也更大，应该留给更需要割与这个点相连的边的答案。

这一点类似与一个非常经典的贪心问题，就是每个任务有一个权重和一个最晚的完成时间，要求一个安排这些任务的方案。我们每次会选择在可选范围内最晚的时间去完成，因为越早的时间可以分配给的任务数量越多，它的可利用价值就更大，应该安排给时间范围更窄的任务。

回到这一题也是同样的道理，割掉哪一条边就对应着“时间”，每次割边给出的链就对应着“最晚完成时间”。

贪心策略已经有了，但是现在还有一个问题：每次后手只能割掉与所在点相连的一条边，如果按照上面的贪心策略可能会多割掉一些边或是在还没走到一个点的时候就割掉了下面的边。如何证明这种做法的正确性？

其实我们刚刚所谓的“割边”并不是真正的割掉了某条边，而是排除掉了先手可能的一些答案，我们选择了一条边“割掉”相当于在这条边上打了个标记，如果先手走到了这条边连接的点上，那么后手割掉这条边是最优的。所以最后如果真正模拟一边先手和后手的决策，仍然是符合题目要求的。

当然不用真的再模拟一遍，因为在排除答案时如果某个答案无法通过割边排除掉，直接输出这个答案就好。

下面是关于代码实现的一些细节：

在“割边”，也就是对边打标记的时候，要注意需要把标记打在深度较低的点上，因为决策是在走到每个结点上做出的，而且这样做也会更方便我们之后判断“割”哪条边的环节。

在对一条边打了标记过后，需要把以深度较大的结点为根的子树上的所有节点打上标记（这里的标记是另一个），因为“割掉”这条边的时候可能会把一些另外的答案排除掉，需要对整棵子树标记一下。在判断一个答案能否被排除掉的时候也要先检查有没有被打过标记。子树覆盖和单点查询就再另外用一个数据结构对 dfn 序维护一下就好了，我的代码实现里用了线段树。

我在考场上脑抽了最开始统计答案的时候没用普通线段树而是用了主席树，实际上只需要在 dfs 的过程中，进入一个结点的时候加入这个节点的饼干，退出结点的时候删掉这上面的饼干就行了。

时间复杂度的话是 $\mathcal{O}(n \log n)$，涉及到了排序，线段树，并查集，倍增。

快速找到应该被“割掉”的边这一部分我是用并查集实现的，因为打标记的时候正好可以通过更改结点的“父结点”（这里的父结点是在并查集中的）来达到打标记的效果，就是以后访问到这个结点的时候会直接跳过然后访问它的“父节点”。

我的做法大概是一个数据结构的融合，就是哪里的时间复杂度高了哪里就用数据结构优化一下，所以会很丑陋也不是很优雅，可以配合代码看一下。对于贪心的证明可能有一点模糊，欢迎提问。

代码里在比较关键的地方写了详细的注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, cnt, x[100005], t[100005], p[100005], l[100005], father[100005], dfn[100005], edf[100005], dep[100005], fa[100005][18];
ll tim[100005];
vector<int> g[100005];
vector< pair<ll, int> > v;
struct Segment_Tree {//主席树
	struct Segment {
		int lc, rc;
		ll sum, cnt;
		Segment(int Lc = 0, int Rc = 0, ll Sum = 0, ll Cnt = 0): lc(Lc), rc(Rc), sum(Sum), cnt(Cnt) {}
		Segment operator = (const Segment& _) {
			lc = _.lc, rc = _.rc, sum = _.sum, cnt = _.cnt;
			return *this;
		}
	} t[10000005];
	int idx, root[100005];
	#define mid ((l + r) >> 1)
	int new_node(int k) {
		++idx;
		t[idx] = t[k];
		return idx;
	}
	int change(int k, const ll& pos, const ll& v, int l = 1, int r = 1000000) {//加入一个饼干
		int rt = new_node(k);
		t[rt].sum += pos * v, t[rt].cnt += v;
		if(l == r) return rt;
		if(pos <= mid) t[rt].lc = change(t[rt].lc, pos, v, l, mid);
		else t[rt].rc = change(t[rt].rc, pos, v, mid + 1, r);
		return rt;
	}
	ll ask(int k, ll rk, int l = 1, int r = 1000000) {//主席树上二分
		if(rk >= t[k].sum) return t[k].cnt;
		if(rk <= 0) return 0;
		if(l == r) return min(rk / l, t[k].cnt);
		if(t[t[k].lc].sum >= rk) return ask(t[k].lc, rk, l, mid);
		else return t[t[k].lc].cnt + ask(t[k].rc, rk - t[t[k].lc].sum, mid + 1, r);
	}
	#undef mid
} tree;
struct SGT {//这颗线段树是处理子树的标记的，用了标记永久化，也可以改成懒标记
	int L, R, l[400005], r[400005];
	bool tag[400005];
	#define lc (k << 1)
	#define rc (lc | 1)
	#define mid ((l[k] + r[k]) >> 1)
	void build(int k) {
		if(l[k] == r[k]) return;
		l[lc] = l[k], r[lc] = mid, l[rc] = mid + 1, r[rc] = r[k];
		build(lc), build(rc);
	}
	void change(int k) {
		if(tag[k]) return;
		if(L <= l[k] && r[k] <= R) {
			tag[k] = true;
			return;
		}
		if(L <= mid) change(lc);
		if(R > mid) change(rc);
	}
	bool get(int k, const int& pos) {
		if(tag[k]) return true;
		if(l[k] == r[k]) return false;
		if(pos <= mid) return get(lc, pos);
		else return get(rc, pos);
	}
	void change(int lt, int rt) {
		L = lt, R = rt;
		return change(1);
	}
} tr;
int findset(int x) {return father[x] == x ? x : father[x] = findset(father[x]);}//并查集
void dfs(int now) {//搜索得到dfn序，处理倍增数组
	dep[now] = dep[p[now]] + 1, fa[now][0] = p[now];
	for(int i = 1; i <= __lg(n); ++i) fa[now][i] = fa[fa[now][i - 1]][i - 1];
	dfn[now] = ++cnt;
	for(const auto& i : g[now]) {
		dfs(i);
	}
	edf[now] = cnt;
}
bool check(int pos) {
	if(pos == 1) return false;//特判根节点的情况，但是好像没什么用？
	if(tr.get(1, dfn[pos])) return true;//被打过标记了就不用再多割别的边了
	int ck = findset(p[pos]);
	if(ck == 1) return false;//如果需要割与根节点相连的边就可以直接返回了，因为先手是先移动然后后手再割边的，与根节点相连的边不可能被割掉
	while(dep[pos] > dep[ck] + 1) pos = fa[pos][__lg(dep[pos] - dep[ck] - 1)];//这里是倍增找到需要打标记的子树的根节点，边的标记是打在深度较低的点上的，但是给子树打标记需要找到深度较大的点
	tr.change(dfn[pos], edf[pos]);//给子树打标记
	father[ck] = father[p[ck]];//给边打标记，这里把深度较低的点的“父结点”更改了的话以后就不会访问到这个结点了。
	return true;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> tim[0];
	for(int i = 1; i <= n; ++i) cin >> x[i];
	for(int i = 1; i <= n; ++i) cin >> t[i];
	for(int i = 2; i <= n; ++i) {
		cin >> p[i] >> l[i];
		g[p[i]].push_back(i);
	}
	//考试的时候看到题目的父结点输入方式就想到了这样处理
	//实际的话换成dfs就可以避免使用主席树了，我这样处理本质上是bfs，所以得用主席树
	for(int i = 1; i <= n; ++i) {//这一步是求走到每个结点的时候可以获得的最大饼干数量
		father[i] = i;
		tim[i] = tim[p[i]] - l[i] - l[i];
		tree.root[i] = tree.change(tree.root[p[i]], t[i], x[i]);
		v.push_back(make_pair(-tree.ask(tree.root[i], tim[i]), i));
	}
	stable_sort(v.begin(), v.end());//将可能的答案从大到小排序
	tr.l[1] = 1, tr.r[1] = n;//这里的线段树是“割边”的时候给子树打标记用的线段树
	tr.build(1);
	dfs(1);//处理dfn序，同时也处理倍增数组
	for(const auto& i : v) {
		if(!check(i.second)) {
			cout << -i.first;//无法把这个答案去掉的时候就输出答案
			break;
		}
	}
	return 0;
}
```

---

## 作者：XG_Zepto (赞：3)

### [Description](https://codeforces.com/contest/1099/problem/F)

Mitya 和 Vasya 在玩一个有趣的游戏。他们有一颗 $n$ 个节点，以 $1$ 为根的树。除了根之外的每一个节点 $i$，$p_i$ 是它父亲的编号。

对于树的每一个节点 $i$，它包含 $x_i$ 个曲奇，Mitya 需要 $t_i$ 的时间吃掉一块曲奇；在根节点有一块芯片，Mitya 可以花上 $l_i$ 的时间将它移至当前节点的任意一个儿子 $i$ 处。

Mitya 和 Vasya 将轮流进行如下操作（Mitya 先开始）：

- Mitya 将芯片向当前节点的儿子移动；
- Vasya 切断当前节点到一个儿子的连接。

Mitya 可以在轮到他的时候结束游戏，然后花时间将芯片移回根节点，并且顺路选择性地吃掉一些饼干。我们规定，整个流程（游戏开始到芯片回到根节点）的限时为 $T$。

求出在限定时间内，最坏情况下，Mitya 能吃掉曲奇的最大数量。

### Idea

我们从根开始 $DP$，最坏情况就是 Vasya 切断了最优的那个儿子，我们从次优的儿子处转移答案即可，计算答案只要考虑是否在当前节点折返。

我们用树状数组维护沿路上所有曲奇的消耗时间和数量，如果选择在当前节点折返，贪心地选择耗时最小的曲奇吃掉即可，这一步骤可以二分完成。

### Code

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define ll long long
#define maxn 100001
#define maxt 1000100
using namespace std;
int t[maxn],p[maxn];
int d[maxn],x[maxn];
vector<int> g[maxn];
ll ans[maxn];
ll T;int n;
struct BT{
	ll t[maxn<<4];
	void add(int x,ll v){while(x<maxt)t[x]+=v,x+=(x&-x);}
	ll sum(int x){ll r=0;while(x) r+=t[x],x-=(x&-x);return r;}
}st,pt;
void Dfs(int u,ll dis){
	ll cur=T-2*dis;
	st.add(t[u],1ll*x[u]*t[u]);
	pt.add(t[u],x[u]);
	int l=0,r=maxt-1,res=0;
	while(l<=r){
		if (st.sum(mid)<=cur)
			res=mid,l=mid+1;
		else r=mid-1;
	}
	if (res)
	ans[u]=pt.sum(res),
	cur-=st.sum(res);
	r=maxt-1,res=0;
	while(l<=r){
		if (pt.sum(mid)!=ans[u])
			res=mid,r=mid-1;
		else l=mid+1;
	}
	if (res) ans[u]+=cur/res;
	for (auto v:g[u])
		Dfs(v,dis+d[v]);
	st.add(t[u],-1ll*x[u]*t[u]);
	pt.add(t[u],-x[u]);
	ll mx=0;int nxt=0;
	for (auto v:g[u])
		if (ans[v]>mx) mx=ans[v],nxt=v;
	if (u==1) {ans[u]=max(ans[u],mx);return;}
	mx=0;
	for (auto v:g[u])
		if (ans[v]>mx&&v!=nxt)
			mx=max(mx,ans[v]);
	ans[u]=max(ans[u],mx);
}
int main(){
	cin>>n>>T;
	for (int i=1;i<=n;++i)
		cin>>x[i];
	for (int i=1;i<=n;++i)
		cin>>t[i];
	for (int i=2;i<=n;++i)
		cin>>p[i]>>d[i],
		g[p[i]].push_back(i);
	Dfs(1,0);
	cout<<ans[1]<<endl;
	return 0;
}
```



---

## 作者：Aria_Math (赞：2)

笔者的搞笑做法。

首先用线段树二分求出 $f_u$ 表示先手从根走到 $u$ 再折回去能吃多少曲奇。

然后考虑二分答案，将所有 $f_u \ge mid$ 的点标记为黑点，现在需要判定后手能不能断边让先手到不了任意一个黑点。

设 $g_u$ 表示先手已经到 $u$ 点了，后手需要提前断几条边（在先手到 $u$ 之前就断掉）才能让先手到不了黑点。转移考虑后手肯定是断掉 $g_v$ 最大的那些儿子，先手再选剩下的儿子里最大的，于是有 
$$g_u=\max(0,\min (g_v + cnt(g_v)-1))$$
其中 $cnt(g_v)$ 表示其他儿子中有几个的 $g \ge g_v$，减一是因为先手到 $u$ 之后后手本来就可以操作一次。最后判断 $1$ 的儿子中最大的 $g$ 是否大于 $0$ 即可。时间复杂度 $\mathcal{O}(n\log n\log V)$。

$\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const int V = 1e6;
struct SGT {
	ll sum, siz;
} t[V * 4];
int n, x[N], c[N]; 
ll T, f[N], g[N];
vector<pair<int, int>> G[N];
void Mdf(int u, int pos, int k, int p = 1, int q = V) {
	t[u].sum += 1ll * pos * k, t[u].siz += k;
	if(p == q) return ; int mid = p + q >> 1;
	if(pos <= mid) Mdf(u * 2, pos, k, p, mid);
	else Mdf(u * 2 + 1, pos, k, mid + 1, q);
}
ll Qry(int u, ll k, int p = 1, int q = V) {
	if(p == q) return min(t[u].siz, k / p);
	int mid = p + q >> 1;
	if(k < t[u * 2].sum) return Qry(u * 2, k, p, mid);
	return Qry(u * 2 + 1, k - t[u * 2].sum, mid + 1, q) + t[u * 2].siz;
}
void Dfs(int u, ll now) {
	Mdf(1, c[u], x[u]);
	f[u] = Qry(1, T - now * 2);
	for(auto [v, w] : G[u]) Dfs(v, now + w);
	Mdf(1, c[u], -x[u]);
}
void Dfs1(int u, ll mid) {
	if(f[u] >= mid) return ;
	vector<ll> d;
	for(auto [v, w] : G[u]) {
		Dfs1(v, mid); if(g[v]) d.push_back(g[v]);
	}
	sort(d.begin(), d.end());
	g[u] = d.size();
	for(int i = 0; i < d.size(); ++i) if(!i || d[i] != d[i - 1])
		g[u] = min(g[u], d[i] + (ll)(d.size() - i - 1));
	g[u] = max(g[u] - 1, 0ll);
}
bool Check(ll mid) {
	for(int i = 1; i <= n; ++i) g[i] = 1e18;
	Dfs1(1, mid);
	ll mxn = 0;
	for(auto [v, w] : G[1]) mxn = max(mxn, g[v]);
	return mxn > 0;
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> T; ll all = 0;
	for(int i = 1; i <= n; ++i) cin >> x[i], all += x[i];
	for(int i = 1; i <= n; ++i) cin >> c[i];
	for(int i = 2, w, fa; i <= n; ++i)
		cin >> fa >> w, G[fa].push_back({i, w});
	Dfs(1, 0);
	ll l = 0, r = *max_element(f + 1, f + n + 1), ans = 0;
	while(l <= r) {
		ll mid = l + r >> 1;
		if(Check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：eggegg185 (赞：2)

[洛谷题面](https://www.luogu.com.cn/problem/CF1099F)
[CF题面](https://codeforces.com/problemset/problem/1099/F)

# $Description:$
红黄饼干玩游戏。

有一棵以 $1$ 号节点为根的树，节点 $i$ 上有 $x_i$ 个饼干，在节点 $i$ 上吃一个饼干要花 $t_i$ 时间。

对于 $i$ 号节点 $(i > 2)$，他的父亲为 $p_i$ 且到达他的父亲需要花 $l_i$ 时间。

黄饼干一开始在 $1$ 号节点。黄饼干和红饼干轮流操作。在每回合：

- 黄饼干可以走到自己所在节点的任意一个儿子
- 黄饼干走完后，红饼干可以割掉黄饼干所在节点的任意一个连接儿子的边，当然他可以不割掉任何边。

黄饼干可以在任意他的回合结束游戏，结束游戏后他要返回到根节点，可以顺路吃点饼干，且黄饼干赶路和吃饼干的总时间不能超过 $T$。

那么请问，在红饼干操作最优时，黄饼干最多能吃到多少饼干？

# $Solution:$

我们先思考红饼干不割边时黄饼干最多能吃到多少饼干。考虑黄饼干在节点 $x$ 结束游戏时能吃到多少饼干。

赶路时间是一定的，所以我们要多吃时间少的饼干。按时间排序饼干太池沼了，我们考虑另一个策略：找到一个 $t$，我们把时间小于 $t$ 的饼干全吃完，而且这样可以吃到最多的饼干。然后，我们找到吃时间大于 $t$ 的第一个饼干，尽可能吃这种饼干。什么？你问最后一种饼干不够吃怎么办？最后一种饼干不够吃就代表你吃完了最后一种饼干，那么在 $t$ 等于最后一种饼干的时间时，就可以吃到更多的饼干，与前面说的不符，所以最后一种饼干是吃不完的。我们可以在树状数组二分 $t$ 来实现这种策略——也就是用树状数组记录饼干的总共吃时间和数量。具体的可以参考代码。

现在我们可以让红饼干割边了。红饼干的策略肯定是让黄饼干不能达到这些儿子里的最优解。如果我们记录了钦定在哪个节点的子树节点里返回最多能吃多少饼干，那么红饼干一定会割掉连接能吃最多的子树节点的边。为什么呢？因为要吃到这些饼干，这条边是必经之路。我们也可以顺便记录一下在黄饼干目前子树里最多可以吃到多少饼干。不过要注意到如果黄饼干在 $1$ 号节点的话红饼干就无可奈何了，因为是黄饼干先走，然后才是红饼干。当然，我们最后的答案就是 $1$ 号节点子树的答案——因为这就是整个树的答案 QwQ

好的，话已至此，$[\text{SHOW YOU THE CODE}]$！！！！！！

$Code:$
```cpp
#include <iostream>
using namespace std;
#define int long long
int n,T;
int t[114514],len[114514],x[114514],qwq[114514];
int head[114514],to[114514],nxt[114514],cnt = 0;
void add(int u,int v) {
	cnt++;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
struct tree {
	int a[16919810];
	inline int lowbit(int u) {return u&(-u);}
	void add(int u,int v) {
		for(int i = u; i <= 1000001; i += lowbit(i)) {
			a[i] += v;
		}
	}
	int query(int u) {
		int ans = 0;
		for(int i = u; i; i -= lowbit(i)) {
			ans += a[i];
		}
		return ans;
	}
}timi,coky;
void dfs(int now,int dis) {
	int tim = T-(dis<<1);
	timi.add(t[now],t[now]*x[now]);
	coky.add(t[now],x[now]);
	int l = 0,r = 1000001,ans = -1;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(timi.query(mid) <= tim) {
			ans = mid;
			l = mid+1;
		} else {
			r = mid-1;
		}
	}
	if(ans != -1) {
		qwq[now] = coky.query(ans);
		tim -= timi.query(ans);
	}
	r = 1000001,ans = -1;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(coky.query(mid) != qwq[now]) {
			ans = mid;
			r = mid-1;
		} else l = mid+1;
	}
	if(ans != -1) {
		qwq[now] += tim/ans;
	}
	for(int i = head[now]; i; i = nxt[i]) {
		dfs(to[i],dis+len[to[i]]);
	}
	int son = 0,mx = 0;
	for(int i = head[now]; i; i = nxt[i]) {
		if(qwq[to[i]] > mx) {
			son = to[i],mx = qwq[to[i]];
		}
	}
	if(now == 1) {qwq[now] = max(qwq[now],mx);}
	else {
		mx = 0;
		for(int i = head[now]; i; i = nxt[i]) {
			if(to[i] != son && qwq[to[i]] > mx) {
				mx = qwq[to[i]];
			}
		}
		qwq[now] = max(qwq[now],mx);
	}
	timi.add(t[now],-t[now]*x[now]);
	coky.add(t[now],-x[now]);
}

signed main() {
	ios::sync_with_stdio(false);
	cin >> n >> T;
	for(int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> t[i];
	}
	for(int i = 2; i <= n; i++) {
		int k;
		cin >> k >> len[i];
		add(k,i);
	}
	dfs(1,0);
	cout << qwq[1];
	return 0;
}
```

---

## 作者：ethan0328 (赞：1)

## 思路

我们可以先算出在每个点结束能吃到的饼干。显然，你最后选择吃的饼干一定是 $t_i$ 尽可能小的一段，所以可以通过在权值线段树上二分来求出最多可以吃的饼干数量。

你可以遍历整棵树，每进入一个点的时候加入线段树，回溯的时候在线段树上把这个点清空就可以了。

然后就有一个显然的 DP，令 $val_i$ 表示在 $i$ 结点结束的答案，$dp_i$ 表示在 $i$ 的子树中结束的最大答案。对于删边的人，显然删 $dp_i$ 最大的子树。对于走的人，在剩下的边里选择 $dp_i$ 第二大的走最优。如果无法前进，$dp_i$ 就等于 $val_i$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,t,dis[N],a[N],b[N],val[N],dp[N];
int num[N*4],sum[N*4];
vector<int> e[N];
void push_up(int p)
{
    num[p]=num[p*2]+num[p*2+1];
    sum[p]=sum[p*2]+sum[p*2+1];
}
void update(int p,int l,int r,int x,int y)
{
    if(l==r)
    {
        num[p]+=y;
        sum[p]+=y*l;
        return;
    }
    int mid=(l+r)/2;
    if(x<=mid)
    {
        update(p*2,l,mid,x,y);
    }else
    {
        update(p*2+1,mid+1,r,x,y);
    }
    push_up(p);
}
int query(int p,int l,int r,int x)
{
    if(l==r)
    {
        return l;
    }
    int mid=(l+r)/2;
    if(sum[p*2]<x&&num[p*2+1]>0)
    {
        return query(p*2+1,mid+1,r,x-sum[p*2]);
    }else
    {
        return query(p*2,l,mid,x);
    }
}
int qnum(int p,int l,int r,int nl,int nr)
{
    if(nl<=l&&r<=nr)
    {
        return num[p];
    }
    int mid=(l+r)/2,ret=0;
    if(nl<=mid)
    {
        ret+=qnum(p*2,l,mid,nl,nr);
    }
    if(nr>mid)
    {
        ret+=qnum(p*2+1,mid+1,r,nl,nr);
    }
    return ret;
}
int qsum(int p,int l,int r,int nl,int nr)
{
    if(nl<=l&&r<=nr)
    {
        return sum[p];
    }
    int mid=(l+r)/2,ret=0;
    if(nl<=mid)
    {
        ret+=qsum(p*2,l,mid,nl,nr);
    }
    if(nr>mid)
    {
        ret+=qsum(p*2+1,mid+1,r,nl,nr);
    }
    return ret;
}
void dfs(int x,int fa)
{
    int t1,t2=0,t3=0;
    dis[x]+=dis[fa];
    if(dis[x]*2>=t)
    {
        return;
    }
    update(1,1,1e6,b[x],a[x]);
    t1=query(1,1,1e6,t-dis[x]*2);
    if(t1>1)
    {
        t2=qnum(1,1,1e6,1,t1-1);
        t3=qsum(1,1,1e6,1,t1-1);
    }
    t3=t-t3-dis[x]*2;
    val[x]=t2+min(t3/t1,qnum(1,1,1e6,t1,t1));
    for(auto y:e[x])
    {
        dfs(y,x);
    }
    update(1,1,1e6,b[x],-a[x]);
}
void dfs2(int x)
{
    int t1=0,t2=0;
    dp[x]=val[x];
    for(auto i:e[x])
    {
        dfs2(i);
        if(dp[i]>dp[t1])
        {
            t2=t1;t1=i;
        }else if(dp[i]>dp[t2])
        {
            t2=i;
        }
    }
    if(x==1)
    {
        dp[x]=max(dp[x],dp[t1]);
    }else
    {
        dp[x]=max(dp[x],dp[t2]);
    }
}
signed main()
{
    int x;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=2;i<=n;i++)
    {
        cin>>x;
        e[x].push_back(i);
        cin>>dis[i];
    }
    dfs(1,0);
    dfs2(1);
    cout<<dp[1];
}
```


---

## 作者：shinkuu (赞：1)

想到这道题可以线段树上二分就知道题解一定有人会写 BIT+二分。结果居然全都是/jy

继续宣传**树状数组上二分**小科技。当 $\operatorname{lowbit}(x)> y$ 的时候，$tr_{x+2^y}$ 内存储的是 $(x,x+2^y]$ 的和。所以可以考虑类似倍增的东西。从大到小枚举 $2^k$ 并尝试将当前倍增到的位置加上 $2^k$。也可以看看我的[这篇题解](https://www.luogu.com.cn/blog/Kato-Megumi/solution-cf899f)。

回到这题。首先可以考虑求出在每个点结束最多获得多少饼干，可以 BIT 维护。然后考虑一个 dp：$dp_u$ 表示如果答案在以 $u$ 为根的子树内，最大值是多少。则当 $u=1$ 时，$dp_u=\max(dp_u,\max(dp_v))$，否则 $dp_u=\max(dp_u,\operatorname{secmax}(dp_v))$。$v$ 为 $u$ 的儿子，$\operatorname{secmax}$ 为次大值。$dp_u$ 即为答案。

时间复杂度 $O(n\log V)$。遥遥领先！

code：

```cpp
int n,a[N],b[N];
ll m,dis[N],dp[N];
int tot,head[N];
struct node{int to,nxt,cw;}e[N];
il void add(int u,int v,int w){e[++tot]={v,head[u],w},head[u]=tot;}
struct BIT{
	ll tr[M][2];int n;
	#define lb(x) (x&(-x))
	il void upd(int x,int y){
		int p=x;
		while(x<=n)tr[x][0]+=y,tr[x][1]+=1ll*p*y,x+=lb(x);
	}
	il ll qry(ll x){
		int p=0;ll s=0,cnt=0;
		drep(i,20,0)if(p+(1<<i)<=n&&s+tr[p+(1<<i)][1]<=x)p+=1<<i,s+=tr[p][1],cnt+=tr[p][0];
		if(p<n)cnt+=(x-s)/(p+1);
		return cnt;
	}
	#undef lb
}T;
void dfs(int u,int f){
	T.upd(b[u],a[u]);
	dp[u]=T.qry(m-dis[u]);
	vector<ll> vec;
	go(i,u){
		int v=e[i].to;
		dis[v]=dis[u]+e[i].cw*2;
		dfs(v,u),vec.eb(dp[v]);
	}
	sort(vec.begin(),vec.end(),greater<int>());
	if(u==1)dp[u]=max(dp[u],*vec.begin());
	else if(vec.size()>1)dp[u]=max(dp[u],*(++vec.begin()));
	T.upd(b[u],-a[u]);
}
void Yorushika(){
	scanf("%d%lld",&n,&m);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,1,n)scanf("%d",&b[i]);
	rep(v,2,n){
		int u,w;scanf("%d%d",&u,&w);
		add(u,v,w);
	}
	T.n=1e6,dfs(1,0);
	printf("%lld\n",dp[1]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：zhongpeilin (赞：1)

## 题目大意：
一棵树，每个点到他的父亲节点需要 $t_{i}$ 秒，每个节点上有 $a_{i}$ 块饼干，一个小球每在这个节点吃一个饼干就要 $b_{i}$ 秒。初始小球在 `1` 号节点，两个人轮流进行以下操作：  
Alice 先操作，他可以将球移动到当前节点的任意一个儿子节点上。  
Bob 可以将当前节点到某个子节点的路切断。  
请问如果从根节点向下走的时间加上从节点走回根节点的时间再加上吃饼干的时间不超过 $T$ 的前提下，Alice 最多可以让小球吃多少饼干？注意，Alice 和 Bob 都是聪明绝顶的。

## 解题思路：
首先看到这种题我们先来想一下吃饼干的顺序，不难想到一定是先走到目标节点，然后向回走的路上吃饼干，因为如果在一个点吃饼干的话，Bob 会把道路全部切断。而饼干是没有价值大小的，所以优先吃时间快的饼干。  

那我们向下搜索的时候怎么维护呢？我们维护一个优先队列？这肯定不行，因为回退的时候不好回退，所以考虑用个数据结构来维护，而数据结构可以以 $t_{i}$ 为下标，那么吃的饼干一定是一段前缀，所以数据结构的任务是：快速找到最后一个不会超时的饼干的时间，那么你想到了什么？  
**线段树二分**！！  

但是这道题 $n \le 10^5$，而又是 3 秒实现，说明我们可以写一个 $O(n \log n \times \log n)$ 时间复杂度的代码，也就是说我们可以先二分一个答案，然后树状数组维护个数和时间，这可比线段树二分好写多了。  

但问题来了，我们没有处理 Bob 这个捣蛋鬼，不过也很简单，因为 Bob 是在 Alice 之后操作的，所以就相当于 Alice 在点 `1` 时走最优解，而其他点都会走次优解。  
所以还是 $O(n \log n \log n)$。

## ACCODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node{
	int y, dis;
};
vector<node> g[100005];
int n, T, a[100005], b[100005], dp[100005];
int C_sum[1000005], C_cnt[1000005], dis[100005];

void add_sum(int x, int c){
	for(int i = x; i <= 1000001; i += (i & (-i))) C_sum[i] += c;
} 
void add_cnt(int x, int c){
	for(int i = x; i <= 1000001; i += (i & (-i))) C_cnt[i] += c;
}
int ask_sum(int x){
	int ans = 0;
	for(int i = x; i; i -= (i & (-i))) ans += C_sum[i];
	return ans;
}
int ask_cnt(int x){
	int ans = 0;
	for(int i = x; i; i -= (i & (-i))) ans += C_cnt[i];
	return ans;
}

void dfs(int x){
	add_sum(b[x], a[x] * b[x]); //加上时间
	add_cnt(b[x], a[x]); // 加上个数
	
	int maxn = 0, maxnn = 0;
	for(auto y : g[x]){  // 算子树的最优解和次优解
		dis[y.y] = dis[x] + y.dis;
		dfs(y.y);
		maxnn = max(maxnn, dp[y.y]);
		if(maxnn > maxn) swap(maxn, maxnn);
	}
	
	int l = 0, r = 1000000, ans = 0;
	while(l <= r){ //二分当前如果在x点停下会有多少价值
		int mid = (l + r) / 2;
		if(ask_sum(mid) <= T - dis[x] * 2){
			l = mid + 1, ans = mid;
		} else {
			r = mid - 1;
		}
	}
	
	int cnt = ask_cnt(ans) + min((T - dis[x] * 2 - ask_sum(ans)) / (ans + 1), ask_cnt(ans + 1) - ask_cnt(ans)); // 这里要和ask_cnt(ans + 1) - ask_cnt(ans)取min，否则会WRONGANSWERONTEST9
	if(x == 1) dp[x] = max(cnt, maxn);
	else dp[x] = max(cnt, maxnn);
	
	add_sum(b[x], -1ll * a[x] * b[x]); //清除标记
	add_cnt(b[x], -1ll * a[x]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin >> n >> T;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 2; i <= n; i++){
		int bb, D; //父亲，边的长度
		cin >> bb >> D;
		g[bb].push_back((node){i, D});
	} 
	dfs(1); //遍历树
	cout << dp[1] << endl; 
	return 0;
}
```
创作不易，点个赞吧！

---

## 作者：ybc2026lhy (赞：0)

考虑如果最终在点 $u$ 选择返回，那么路程上花的时间为从点 $1$ 到点 $u$ 的时间的两倍，剩余的时间都拿来吃饼干。因为最终比的是饼干的数量，所以优先吃 $t_i$ 比较小的饼干。

我们建权值线段树，以每块饼干的时间为下标，维护区间内饼干总时间和饼干总数。在向子节点走时对应线段树上的添加，在回溯时对应线段树的删除，用线段树上二分来查询前缀和小于等于时间限制的最大饼干数量即可。

得到了在每个点返回对应的答案之后，我们跑树形 dp：如果 $x\neq 1$，我们用 $dp_y$ 的次大值更新 $dp_x$，其中 $y$ 是 $x$ 的子节点；仅对于 1，我们用 1 的子节点中最大的 $dp_y$ 的值更新。因为小 A 先手，所以只有在 1 时他可以任选走哪个儿子，其他时候最多只能走次优。注意，要从叶子向根更新。

时间复杂度 $O(n\log n)$。

---

## 作者：Unnamed114514 (赞：0)

简单题。

容易想到把时间放到线段树上维护，下标表示时间，然后维护数量和数量乘上时间的和。对于单次查询，可以用线段树上二分。

注意到线段树单点加是可撤销的，所以我们可以用 `dfs`，进入的时候加一下，回溯的时候就给它删掉，这样到每个点的时候就可以只有它到根节点的路径了。

最后考虑子树的贡献，显然贪心地，肯定断掉的是 $ans$ 最大的边，所以每个点的 $ans$ 和次大儿子 $ans$ 取 $\max$ 即可。

注意根节点没有断边，所以根节点是和最大值取 $\max$。

$O(n\log n)$。

---

