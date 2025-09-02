# [ICPC 2022 Jinan R] Tree Distance

## 题目描述

给定一个无根的加权树 $T$，其顶点为 $1, 2, \ldots, n$。请回答一些查询。

我们定义 $\texttt{dist}(i,j)$ 为顶点 $i$ 和顶点 $j$ 在树 $T$ 中的距离。

对于每个查询，给定两个整数 $l, r$。请回答以下值：

$$\min_{l\le i< j\le r}(\texttt{dist}(i,j)).$$

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
1 2 5
1 3 3
1 4 4
3 5 2
5
1 1
1 4
2 4
3 4
2 5
```

### 输出

```
-1
3
7
7
2
```

# 题解

## 作者：lzyqwq (赞：18)

**[CNBLOGS](https://www.cnblogs.com/MnZnOIerLzy/articles/17791271.html)**

**[洛谷](https://www.luogu.com.cn/problem/P9058)**


> - 给出一棵 $n$ 个点的树，边有边权。
>
> - 记 $\text{dist}(u,v)$ 为 $u,v$ 两点简单路径上的边的权值之和。
>
> - 有 $q$ 次询问，每次询问给出 $l,r$，求 $\min\limits_{l\le i<j\le r} \text{dist}(i,j)$。
>
> - $n\le 2\times 10^5$，$q\le 10^6$。

称 $(i,j)\,(i<j)$ 为一个点对，若把 $\text{dist}(i,j)$ 看作改点对的权值，则我们要求解一个二维偏序问题。

现在的问题就是点对太多了，一共有 $\mathcal{O}(n^2)$ 个。不过，真的需要这么多点对吗？比如现在有两个点对 $(x_1,y_1)$ 和 $(x_2,y_2)$ 满足 $x_1\le x_2\le y_2\le y_1$ 且 $\text{dist}(x_1,y_1)\ge \text{dist}(x_2,y_2)$，你发现若查询的区间包含了 $(x_1,y_1)$，就一定包含了 $(x_2,y_2)$，而且 $(x_2,y_2)$ 的权值更小。因此 $(x_1,y_1)$ 这个点对是没有用的。我们称 **$\boldsymbol{(x_2,y_2)}$ 支配了 $\boldsymbol{(x_1,y_1)}$**。

我们称一个点对为支配点对，**当且仅当它不被其他点对支配**。

考虑找出一个集合 $T$ 包含所有的支配点对且大小可接受。我们来找一下一个点对成为支配点对的**必要**条件。

考虑点分治，对于一个支配点对 $(i,j)$，则一定存在一个分治重心 $rt$ 满足 $i,j$ 在 $rt$ 不同儿子的子树中。不妨钦定 $\text{dist}(i,rt)\le \text{dist}(j,rt)$。设 $S$ 表示当前联通块中满足 $\text{dist}(x,rt)\le \text{dist}(j,rt)$ 且 $x\ne j$ 的 $x$ 构成的集合，**则 $\boldsymbol{i}$ 一定是 $\boldsymbol{S}$ 中最大的 $\boldsymbol{<j}$ 的数（前驱）或最小的 $\boldsymbol{ >j}$ 的数（后继）**。

为什么？考虑反证法，以前驱为例，设 $j$ 的前驱为 $pre$，若 $i<pre$，根据 $S$ 的定义可知 $\text{dist}(i,rt),\text{dist}(pre,rt)\le \text{dist}(j,rt)$。

此时一定满足：

- $\text{dist}(i,pre)\le \text{dist}(i,rt)+\text{dist}(pre,rt)\le \text{dist}(i,rt)+\text{dist}(j,rt)=\text{dist}(i,j)$。

  $\text{dist}(i,pre)\le \text{dist}(i,rt)+\text{dist}(pre,rt)$ 是因为相较于后者前者要减去根到 $\text{LCA}$ 路径的边权和。

- $i<pre<j$。

你发现 $(i,j)$ 被 $(i,pre)$ 支配了。后继的证法类似，此处不再赘述。

考虑这样一个过程，对于每一层点分治，对于每一个点维护集合 $S$，并找到前驱、后继并将该点对加入 $T$。那么任意一个支配点对 $(i,j)$，点分治进行到使得它们在两棵不同子树中的联通块时，因为 $i$ 一定是前驱或后继，那么对于 $j$ 这个点找前驱、后继的时候，就把这个点对找到了。**所以这样找到的 $\boldsymbol T$ 集合包含了所有支配点对。**

**并且，由于点分治只会进行 $\boldsymbol{\mathcal{O}(\log n)}$ 层，每一层每个点带来 $\boldsymbol{\mathcal{O}(1)}$ 个点对，因此找到的总点对数量为 $\boldsymbol{\mathcal{O}(n\log n)}$ 个**。

具体地，如何实现这个构造 $T$ 的过程？对于每一个联通块的点分治，将所有点 $u$ 按照编号升序排序。正着反着扫一遍，维护一个随着 $u$ 递增 / 递减，$\text{dist}(u,rt)$ 不降的单调栈。那么对于一个点 $v$，它就是被它出栈的那些点的前驱 / 后继。

我们已经得到了集合 $T$，那么拿 $T$ 中的点对去做二维数点即可。考虑离线 + 倒序扫描 $i$ 保证 $l\le i$，用树状数组维护 $j\le r$ 求前缀最值即可。至于 $\text{dist}(i,j)$，用树剖 + $\text{LCA}$ 求一下即可。

时间复杂度为 $\mathcal{O}(n\log^2 n+q\log n)$，空间复杂度为 $\mathcal{O}(n\log n+q)$。

**[提交记录](https://www.luogu.com.cn/record/131796238) [代码](https://www.luogu.com.cn/paste/c2h16j1b)**

---

## 作者：WrongAnswer_90 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17944113)

[P9678 [ICPC2022 Jinan R] Tree Distance](https://www.luogu.com.cn/problem/P9678)

支配对，不是非常难。

显然如果 $a\leq b<c\leq d$ 且 $dis(a,d)>dis(b,c)$ 则点对 $(a,d)$ 是无用的，猜想点对数不会太多，事实也正是如此。

树上距离是很复杂的东西，考虑简化：使 $root$ 为根，暂且让 $dis(x,y)=dep_x+dep_y$（正确性后面会证）。此时一个点对 $(x,y)$ 是有用的的充要条件是不存在 $x\leq a<b\leq y$ 且 $dep_a+dep_b<dep_x+dep_y$。

这个条件仍然不好刻画，观察一下性质可以发现充要条件可以变成：$dep_x,dep_y$ 是区间 $[x,y]$ 中 $dep$ 的最小和次小值，充分性和必要性都显然。这样钦定一个根最多会有 $\mathcal O(siz_x)$ 个点对。

一个推论是支配点对一定不会出现相交。所以可以类似分治的思想：把点按照编号排序，此时能和最左边的点匹配的点一定是类似单调栈一样的东西，可以记录 $nx_i$ 表示编号比 $i$ 大且 $dep$ 比 $i$ 小的最小的点，这样暴力跳，因为一定不会出现相交，分治的时候递归 $(now,nx_{now})$ 即可。

上面还有一个问题：我们是强制让 $dis(x,y)=dep_x+dep_y$ 的，但是实际距离可能并不是。但是这个并不会影响任何东西。首先如果 $(x,y)$ 作为支配点对出现，那不会影响任何东西（常熟可能会大一些）。如果通过 $a\leq x<y\geq b$ 用 $(x,y)$ 把 $(a,b)$ 叉掉了，那如果 $dis(x,y)$ 变得更小一定更能叉掉。所以上面讨论的实际上是一个必要的点对，但是复杂度是对的。剩下的东西就是淀粉质板子了。最后扫描线树状数组维护后缀 $\min$，复杂度 $\mathcal O(n\log^2n+q\log n)$。

```cpp
	int n,m,cnt,len,ans[1000010],head[200010],v[400010],to[400010],nex[400010];
	inline void add(int x,int y,int z){v[++cnt]=z,to[cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
	vector<pii> ve[200010],qu[200010];
	namespace BIT
	{
		int t[200010];
		inline void add(int x,int y){for(;x;x-=x&-x)Mmin(t[x],y);}
		inline int ask(int x){int s=INF;for(;x<=n;x+=x&-x)Mmin(s,t[x]);return s;}
	}
	using namespace BIT;
	namespace Starch
	{
		int nx[200010],id[200010],siz[200010],dep[200010],a[200010],len,root,all;
		bool vis[200010];
		set<int> st;
		void find(int x,int fa)
		{
			siz[x]=1;int maxn=0;
			for(int i=head[x];i;i=nex[i])
			{
				if(to[i]==fa||vis[to[i]])continue;
				find(to[i],x),siz[x]+=siz[to[i]],Mmax(maxn,siz[to[i]]);
			}
			if(max(maxn,all-siz[x])<=all/2)root=x;
		}
		void dfs(int x,int fa)
		{
			a[++len]=x;
			for(int i=head[x];i;i=nex[i])
			{
				if(to[i]==fa||vis[to[i]])continue;
				dep[to[i]]=dep[x]+v[i],dfs(to[i],x);
			}
		}
		void calc(int l,int r)
		{
			int now=l+1;
			while(now&&now<=r)
			{
				ve[a[now]].eb(mp(a[l],dep[a[l]]+dep[a[now]]));
				if(dep[a[now]]<dep[a[l]]||!nx[now])return calc(now,r);
				calc(now,min(r,nx[now])),now=nx[now];
			}
		}
		inline bool cmp(int x,int y){return dep[a[x]]<dep[a[y]]||(dep[a[x]]==dep[a[y]]&&x>y);}
		void starch(int x)
		{
			find(x,0),find(x=root,0),vis[x]=1,dep[x]=len=0,dfs(x,0),sort(a+1,a+1+len);
			for(int i=1;i<=len;++i)id[i]=i;
			sort(id+1,id+1+len,cmp),st.clear();
			for(int i=1;i<=len;++i)
			{
				auto it=st.lower_bound(id[i]);
				if(it==st.end())nx[id[i]]=0;else nx[id[i]]=*it;
				st.insert(id[i]);
			}
			calc(1,len);
			for(int i=head[x];i;i=nex[i])if(!vis[to[i]])all=siz[to[i]],starch(to[i]);
		}
	}
	using namespace Starch;
	inline void mian()
	{
		read(n),all=n;int x,y,z;
		for(int i=1;i<=n;++i)t[i]=INF;
		for(int i=1;i<n;++i)read(x,y,z),add(x,y,z),add(y,x,z);
		read(m),starch(1);
		for(int i=1;i<=m;++i)read(x,y),qu[y].eb(mp(x,i));
		for(int i=1;i<=n;++i)
		{
			for(auto j:ve[i])add(j.fi,j.se);
			for(auto j:qu[i])ans[j.se]=ask(j.fi);
		}
		for(int i=1;i<=m;++i)write(ans[i]==INF?-1:ans[i],'\n');
	}
```

---

## 作者：寄风 (赞：5)

## 废话
推荐评分：上位紫~中位黑

这题我在赛场上写了 1.5h，因为调试过久还差点没能写出 C 题而痛失 Rank1。

下文中 $\operatorname{dis}(x,y)$ 表示树上 $x$ 和 $y$ 之间的距离。
## 题解
- 我会暴力！ 

对不起，暴力的时间复杂度是 $O(q\times n^3)$，在这题的数据范围下妥妥的超时。
- 我会 $\operatorname{LCA}$！

$\operatorname{LCA}$ 虽然可以把求路径长度的复杂度变为 $O(\log n)$，但是这样的话总时间复杂度还是 $O(q\times n^2 \log n)$，还是超时。

- 我会点分治！

重点来了。

由于点对数量过多，考虑只保留一些有用的点对，也就是所谓的”支配点对“。

考虑点分治。

设当前点分治到了节点 $now$，那我们考虑 $now$ 子树内的一个点 $x$，我们只需要找到一些 $y$，满足 $\operatorname{dis}(now,x) \ge \operatorname{dis}(now,y)$ 且 $x$ 与 $y$ 不在 $now$ 的同一子树内既可。

进一步考虑到底哪些点会保留。

如果存在两个满足条件的点 $c1,c2$，且 $x \ge c2 \ge c1$，那么这个时候的 $\operatorname{dis}(c1,c2)$ 到底是什么呢？

$\operatorname{dis}(c1,c2)=\operatorname{dis}(now,c1)+\operatorname{dis}(now,c2) \le \operatorname{dis}(now,c1)+\operatorname{dis}(now,x)$，也就是说，在这个时候，保留 $(c1,c2)$ 这个点对是不会比保存 $(c1,x)$ 这个点对更劣的，即 $(c1,x)$ 此时不可能为支配点对。

所以我们对于每个 $x$，设集合 $S$ 表示所有不与 $x$ 在 $now$ 的同一子树内，且 $\operatorname{dis}(now,x) \ge \operatorname{dis}(now,y)$ 的点 $y$ 所构成的集合。

那么我们发现我们只要保留 $x$ 在 $S$ 中的前驱和后继即可，其余的都不是支配点对。

然后我们可以发现，如果我们找到的是一个在 $now$ 的同一子树内的点对 $(x,y)$，那么其中的一个点肯定会劣于另外一个点。

所以子树这个限制可以去掉。

所以点对数量是 $n \log n$ 级别的，可以接受。

然后直接在点分治的时候统计出 $now$ 子树内节点的深度，排个序，顺逆各来一个单调栈求出前驱和后继就行了。

最后对询问右端点来一遍扫描线就完事了。
## 代码
（~~我直接全开 `long long` 都可以在 2s 内跑完，这就是常数给我的自信~~）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , q , vis[200005] , siz[200005] , maxsize[200005] , ans[1000005];
vector < pair < int , int > > e[200005] , que[200005] , dis[200005] , dep;
inline void Findroot(int now , int fa , int big , int& root) {
    siz[now] = 1;
    maxsize[now] = 0;
    for(auto [v , w] : e[now]){
        if(v != fa && !vis[v]){
            Findroot(v , now , big , root);
            maxsize[now] = max(maxsize[now] , siz[v]);
            siz[now] += siz[v];
        }
    }
    maxsize[now] = max(maxsize[now] , big - siz[now]);
    if(!root) root = now;
    if(maxsize[now] < maxsize[root]) root = now;
}
inline void dfs(int now , int fa = 0 , int sum = 0){
    dep.emplace_back(now , sum);
    for(auto [v , w] : e[now]){
        if(v != fa && !vis[v]){
            dfs(v , now , sum + w);
        }
    }
}
inline void solve(int now){
    int root = 0; 
    Findroot(now , 0 , siz[now] , root);
    now = root;
    vis[now] = 1;
    dep.clear();
    dfs(now);
    sort(dep.begin(), dep.end());
    int st[200005] , tp = 0;
    for(int i = 0;i < dep.size();i++){
        int v = dep[i].first , w = dep[i].second;
        while(tp && dep[st[tp]].second > w){
            tp--;
        }
        if(tp){
            dis[v].emplace_back(dep[st[tp]].first , w + dep[st[tp]].second);
        }
        st[++tp] = i;
    }
    tp = 0;
    for(int i = dep.size() - 1;~i;i--){
        int v = dep[i].first , w = dep[i].second;
        while(tp && dep[st[tp]].second > w){
            tp--;
        }
        if(tp){
            dis[dep[st[tp]].first].emplace_back(v , w + dep[st[tp]].second);
        }
        st[++tp] = i;
    }
    for(auto [v , w] : e[now]){
        if(!vis[v]) solve(v);
    }
}
struct BIT{
    int t[200005];
    BIT(){
        memset(t , 0x3f , sizeof(t));
    }
    inline int lowbit(int x){
        return x & (-x);
    }
    inline void update(int pos , int x){
        for(;pos <= n;pos += lowbit(pos)){
            t[pos] = min(t[pos] , x); 
        }
    }
    inline int query(int pos){
        int ans = 1ll << 60;
        for(;pos;pos -= lowbit(pos)){
            ans = min(ans , t[pos]); 
        }
        return ans; 
    }
} dd;
inline void add(int u , int v , int w){
    e[u].emplace_back(v , w);
    e[v].emplace_back(u , w);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    cin >> n;
    for(int i = 1;i < n;i++){
        int u , v , w;
        cin >> u >> v >> w;
        add(u , v , w);
    }
    siz[1] = n;
    solve(1);
    cin >> q;
    for(int i = 1;i <= q;i++){
        int l , r;
        cin >> l >> r;
        que[r].emplace_back(l , i);
    }
    for(int r = 1;r <= n;r++){
        for(auto [l , w] : dis[r]){
            dd.update(n - l + 1 , w);
        }
        for(auto [l , id] : que[r]){
            if(l == r){
                ans[id] = -1;
            }
            else{
                ans[id] = dd.query(n - l + 1);
            }
        }
    }
    for_each(ans + 1 , ans + q + 1 , [&](int i){cout << i << '\n';});
    return 0;
}
```

---

## 作者：Luciylove (赞：2)

# 闲话

这个题今年一二月份就看到了，知道现在才心血来潮补了。

这个题解教会你怎样公式化过题⚡⚡

# Sol

这种东西感觉上就很支配点对。所以我们考虑找出这些对子。

树上路径要求你拍上去一个树上静态链分治，这里我们用点分。

然后就是很自然的按照编号从小到大排序，然后扫两遍。

然后套用支配点对 $(i, j)$， 中间来了一个 $k$ 要把这个东西叉掉。

可以叉掉的条件是满足以下两个东西中的一个：

$$a_i + a_k < a_i + a_j$$
$$a_j + a_k < a_i + a_j$$

然后你就可以有 $a_k < a_j, a_k < a_i$。所以你就发现想要 $(i, j)$ 不被叉掉，就要 $\max\{a_i, a_j\} <\ \min a_k$。

如果 $a_i \leq a_j$，那么 $a_i$ 是 $a_j$ 左边第一个比他小的，如果 $a_j \leq a_i$，那么 $a_j$ 是 $a_i$ 右边第一个比他大的。
# Code 

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define ckmin(x, v) x = x > v ? v : x 
using namespace std;
using ll = long long;
const int _ = 2e5 + 5;
const ll inf = 1e18;

int n, q, all, num;
int top, stk[_];
int root, sz[_], msz[_], vis[_], a[_];
vector <pair<int, ll> > e[_];

int read() {
	int X = 0;
	char ch = 0, w = 0;
	while (ch < 48 || ch > 57)ch = getchar(), w |= (ch == '-');
	while (ch >= 48 && ch <= 57)X = X * 10 + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

struct FenwickTree {
	ll t[_];
	FenwickTree () { fill(t + 1, t + _, inf); }
	void insert (int x, ll v) { for ( ; x; x -= x & -x) ckmin(t[x], v); }
	ll qry (int x) {
		ll ret = inf;
		for ( ; x <= n; x += x & -x) ckmin(ret, t[x]);
		return ret;
	}
} T;
ll ans[_ * 10], d[_];
vector <pair<int, ll> > cv[_];
vector <pair<int, int> > qv[_];

void findroot (int x, int fa) {
	sz[x] = 1, msz[x] = 0;
	for (auto [y, w] : e[x])
		if (!vis[y] && y ^ fa) {
			findroot(y, x);
			msz[x] = max(msz[x], sz[y]), sz[x] += sz[y];
		}
	msz[x] = max(msz[x], all - sz[x]);
	if (msz[x] < msz[root]) 
		root = x; 
}
void getInfo (int x, int fa) {
	a[++ num] = x;
	for (auto [y, w] : e[x])
		if (!vis[y] && y ^ fa)
			d[y] = d[x] + w, getInfo(y, x);
}
void findpair () {
//	cout << num << endl;
	sort(a + 1, a + 1 + num), top = 0;
	rep(i, 1, num) {
		while (top >= 1 && d[stk[top]] >= d[a[i]])
			cv[a[i]].push_back({stk[top], d[a[i]] + d[stk[top]]}), top --;
		stk[++ top] = a[i];
	} top = 0;
	per(i, num, 1) {
		while (top >= 1 && d[stk[top]] >= d[a[i]])
			cv[stk[top]].push_back({a[i], d[a[i]] + d[stk[top]]}), top --;
		stk[++ top] = a[i];
	} 
}
void solve (int x) {
	vis[x] = 1, d[x] = 0;
	num = 0, getInfo(x, 0), findpair();	
	for (auto [y, w] : e[x]) {
		if (vis[y]) continue ;
		root = 0, all = sz[y];
		findroot(y, x), solve(root);
	}		
}
int main () {
	msz[0] = 0x3f3f3f3f;
	n = read();
	rep(i, 1, n - 1) {
		int x = read(), y = read(), w = read();
		e[x].push_back({y, w}), e[y].push_back({x, w});
	}
	all = n, findroot(1, 0), solve(root);

	q = read();
	rep(i, 1, q) {
		int l = read(), r = read();
		qv[r].push_back({l, i});
	} 
	rep(r, 1, n) {
		for (auto [l, v] : cv[r]) T.insert(l, v);
		for (auto [l, id] : qv[r]) ans[id] = T.qry(l);
	} 	
	rep(i, 1, q) printf("%lld\n", ans[i] == inf ? -1 : ans[i]);
	return 0;
}
```

---

## 作者：Eterna (赞：1)

树上路径，考虑点分治。对于当前根 $r$，先找出所有的 $d_x=\mathrm{dis}(x,r)$。则对于任意一条路径 $(x,y)$，我们用 $d_x+d_y$ 表示其长度。

对于在 $r$ 同一颗子树的 $x,y$，我们会将其路径算长，但当我们继续递归，一定会算到正确的路径，所以这样做对答案没有影响。

于是我们有若干点对 $(x,d_x)$，按 $x$ 增序排列。每次求 $l \le x,y \le r$ 的最小的 $d_x+d_y$，我们不可能每次询问都来求一边 rmq。考虑找支配点对。

对于一个支配点对 $(x,y)$，显然满足 $\max(d_x,d_y)\le \min _{i \in (x,y)}d_i$，否则 $x$ 或 $y$ 可以向内缩，得到更优解。

如果 $d_x \le d_y$，$d_x$ 为 $y$ 之前第一个比 $d_y$ 小的元素。如果 $d_y \le d_x$，$d_y$ 为 $x$ 之后第一个比 $d_x$ 小的元素。

正反分别做单调栈维护，每个点贡献 $\mathcal{O}(1)$ 个支配对。加上点分治，一共 $\mathcal{O}(n \log n)$ 个支配对。

扫描线，二维数点即可。时间复杂度 $\mathcal{O}(n \log^2 n +q \log n)$，空间复杂度 $\mathcal{O}(n \log n+q)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rd read()
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
static char buf[100000], * pa(buf), * pb(buf);
inline int read()
{
	register int x=0,s=gc;
	while(!isdigit(s))s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=gc;
	return x;
}
const int N=200005,M=1000005,inf=1e16;
bool vis[N];
int n,m,rt,sz,mx[N],siz[N],ans[M];
vector<pair<int,int> > v[N],q[N],p[N],d;
inline void chkmax(int &x,int y){x=(x<y?y:x);}
inline void chkmin(int &x,int y){x=(x>y?y:x);}
inline void find(int x,int f)
{
	siz[x]=1,mx[x]=0;
	for(auto [i,j]:v[x])
		if(i!=f&&!vis[i])find(i,x),siz[x]+=siz[i],chkmax(mx[x],siz[i]);
	chkmax(mx[x],sz-siz[x]);
	if(mx[x]<mx[rt])rt=x;
}
inline void get(int x,int l,int f)
{
	if(vis[x])return;
	d.push_back({x,l});
	for(auto [i,j]:v[x])if(i!=f)get(i,l+j,x);
}
inline void sol(int x)
{
	if(vis[x])return;
	vis[x]=1;
	for(auto [i,j]:v[x])get(i,j,x);
	d.push_back({x,0}),sort(d.begin(),d.end());	
	stack<pair<int,int> > st;
	for(auto [i,j]:d)
	{
		while(st.size()&&st.top().second>j)st.pop();
		if(st.size())p[i].push_back({st.top().first,st.top().second+j});
		st.push({i,j});
	}
	while(st.size())st.pop();
	reverse(d.begin(),d.end());
	for(auto [i,j]:d)
	{
		while(st.size()&&st.top().second>j)st.pop();
		if(st.size())p[st.top().first].push_back({i,st.top().second+j});
		st.push({i,j});
	}
	d.clear();
	for(auto [i,j]:v[x])if(!vis[i])rt=0,sz=siz[i],find(i,x),sol(rt);	
}
struct BIT
{
	int c[N];
	inline void chk(int x,int y){while(x)chkmin(c[x],y),x^=(x&-x);}
	inline int ask(int x){int s=LONG_LONG_MAX;while(x<=n)chkmin(s,c[x]),x+=(x&-x);return s;}
}G;
signed main()
{
	n=rd;for(int i=1,x,y,w;i<n;v[x].push_back({y,w}),v[y].push_back({x,w}),++i)x=rd,y=rd,w=rd;
	m=rd;for(int i=1,l;i<=m;++i)l=rd,q[rd].push_back({l,i});
	mx[0]=n+1,rt=0,sz=n,find(1,0),sol(rt),memset(G.c,0x3f,sizeof(G.c));
	for(int i=1;i<=n;++i)
	{
		for(auto [l,k]:p[i])G.chk(l,k);
		for(auto [l,id]:q[i])ans[id]=G.ask(l);
	}
	for(int i=1;i<=m;++i)cout<<(ans[i]>inf?-1:ans[i])<<'\n';
	return 0;
}
```

---

## 作者：dengchengyu (赞：1)

### [P9678 [ICPC 2022 Jinan R] Tree Distance](https://www.luogu.com.cn/problem/P9678)

### [P9058 [Ynoi2004] rpmtdq](https://www.luogu.com.cn/problem/P9058)

以下 $(i,j)$ 代表 $dist(i,j)$。

我们把 $(i,j)$ 看做点对 $i,j$ 的权值，那么原题转化为了二维数点问题，直接做是 $O((q+n^2)\log n)$。

瓶颈在于点对有 $O(n^2)$ 个，注意到很多点对是没有用的，实际上有用的点对很少，我们可以找出**支配点对**。

> 如果点对 $x,y$ 和 $a,b$ 满足 $a\le x\le y\le b\land(x,y)\le (a,b)$ 则 $a,b$ 显然是没有用的，我们称 $a,b$ 被 $x,y$ 支配。
> 如果点对 $x,y$ 不被任何另一对点支配，则 $x,y$ 称作**支配点对**。

我们可以找到一种支配点对的**必要条件**。将所有可能为支配点对的点对加入集合 $S$ 并且要使 $S$ 的大小可接受。

由于是与点对有关的信息，考虑点分治，设当前分治重心为 $rt$。我们把当前连通块内任意两点 $x,y$ 的距离看做 $(x,rt)+(y,rt)$ 即可，因为如果一个支配点对 LCA 不为 $rt$，则可以在其他分治重心被统计到。

先给出结论：对于 $x<y<z$ 且 $(x,rt),(y,rt)\le (z,rt)$，点对 $x,z$ 一定不是支配点对。$x>y>z$ 也如此。在这里 $x,z$ 和 $y,z$ 都在 $rt$ 的不同子树内，否则可以在其他重心被统计到。证明如下：

> $(x,y)\le(x,rt)+(y,rt)\le(x,rt)+(z,rt)=(x,z)$

所以 $x,z$ 被 $x,y$ 支配。

因此只要对 $x$，将满足 $y<x$ 且 $(y,rt)\le(x,rt)$ 的最大 $y$ 与满足 $y>x$ 且 $(y,rt)\le (x,rt)$ 的最小 $y$ 与 $x$ 组成点对加入 $S$ 即可。

可以将连通块内的点排序后使用单调栈维护。 

这样连通块内的每个点都有 $O(1)$ 个点对，而点分治均摊有 $O(n\log n)$ 个点，就有 $O(n\log n)$ 个点对。

剩下的就很简单了，离线后对 $l$ 扫描线，用树状数组维护 $r$ 的前缀最小值做二维数点。

时间复杂度 $O(n\log ^2n+q\log n)$。

代码：

```cpp
const int N=2e5+5;
int n;
vp g[N];
namespace sp {
	int top[N],fa[N],dep[N],son[N],sz[N];
	ll ds[N];
	void dfs1(int x,int y) {
		sz[x]=1, dep[x]=dep[y]+1, fa[x]=y;
		for(auto [v,w]:g[x]) {
			if(v==y) continue;
			ds[v]=ds[x]+w;
			dfs1(v,x);
			sz[x]+=sz[v];
			if(sz[v]>sz[son[x]]) son[x]=v;
		}
	}
	void dfs2(int x){
		if(son[fa[x]]==x) top[x]=top[fa[x]];
		else top[x]=x;
		if(son[x]) dfs2(son[x]);
		for(auto [v,w]:g[x]) {
			if(v!=fa[x]&&v!=son[x]) dfs2(v);
		}
	}
	int lca(int x,int y ){
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=fa[top[x]];
		}
		if(dep[x]<dep[y]) return x;
		return y;
	}
	ll dis(int x,int y ){
		int l=lca(x,y);
		return ds[x]+ds[y]-2*ds[l];
	}
};
int vis[N];
namespace gg{
	int sz[N];
	void dfs1(int x,int y) {
		sz[x]=1;
		for(auto [v,w]:g[x]) {
			if(v==y) continue;
			if(!vis[v]) dfs1(v,x),sz[x]+=sz[v];
		}
	}
	int Min,rt,res;
	void dfs2(int x,int y) {
		int Max=sz[rt]-sz[x];
		for(auto [v,w]:g[x]) {
			if(v==y) continue;
			if(!vis[v]) dfs2(v,x),Max=max(Max,sz[v]);
		}
		if(Max<Min) Min=Max,res=x;
	}
	int getg(int x) {
		Min=2e9,rt=x;
		dfs1(x,0),dfs2(x,0);
		return res;
	}	
};
const int L=8e6;
int tot;
struct path {
	int u,v; ll w;
};
path s[L];
int sz;
pl pt[N];
void init(int x,int y,ll len) {
	pt[++sz]={x,len};
	for(auto [v,w] : g[x] ){
		if(!vis[v]&&v!=y) init(v,x,len+w);
	}
}
int stk[N],top;
void add(int u,int v) {
	if(u>v) swap(u,v);
	s[++tot]={u,v,sp::dis(u,v)};
}
void dfs(int x) {
	x=gg::getg(x);
	sz=0;
	for(auto [v,w] : g[x]) {
		if(!vis[v]) init(v,x,w);
	}
	pt[++sz]={x,0};
	sort(pt+1,pt+1+sz);
	top=0;
	fo(i,1,sz) {
		while(top&&pt[stk[top]].se>pt[i].se) --top;
		if(top) add(pt[stk[top]].fi,pt[i].fi);
		stk[++top]=i;
	}
	top=0;
	fd(i,sz,1){
		while(top&&pt[stk[top]].se>pt[i].se) --top;
		if(top) add(pt[stk[top]].fi,pt[i].fi);
		stk[++top]=i;
	}
	vis[x]=1;
	for(auto [v,w] : g[x])  {
		if(!vis[v]) dfs(v);
	}
} 
#define lowbit(x) ((x)&(-(x)))
struct BIT{
	ll v[N];
	void update(int x,ll y) {
		while(x<N) v[x]=min(v[x],y),x+=lowbit(x);
	}
	ll query(int x) {
		ll _v=1e18;
		while(x) _v=min(_v,v[x]),x-=lowbit(x);
		return _v;
	}
	void init() {
		memset(v,0x3f,sizeof v);
	}
}bit;
const int qn=1e6+5;
pair<pi,int> q[qn];
int Q;
ll ans[qn];
signed main(){
	read(n);
	fu(i,1,n)  {
		int u,v,w; read(u,v,w);
		g[u].pb({v,w}),g[v].pb({u,w});
	}
	sp::dfs1(1,0),sp::dfs2(1);
	dfs(1);
	sort(s+1,s+1+tot,[](auto x,auto y) {
		return x.u>y.u;
	});
	bit.init();
	read(Q);
	fo(i,1,Q) read(q[i].fi.fi,q[i].fi.se),q[i].se=i;
	sort(q+1,q+1+Q,[](auto x,auto y) {
		return x.fi.fi>y.fi.fi;
	});
	int t=1;
	fo(i,1,Q) {
		while(t<=tot&&s[t].u>=q[i].fi.fi) {
			bit.update(s[t].v,s[t].w);
			++t;
		}
		ll res=bit.query(q[i].fi.se);
		if(res==1e18) ans[q[i].se]=-1;
		else ans[q[i].se]=res;
	}
	fo(i,1,Q) write(ans[i],'\n');
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

算是一个 trick 题吧。

# Solution

考虑点分治，假设当前的重心为 $r$，当前连通块的点集为 $S$，令 $dis_x$ 为 $x$ 到 $r$ 的距离，则连通块内的点对 $(x,y)$ 的距离是小于等于 $dis_x+dis_y$ 的（如果在同一棵子树，则是小于），可以发现这些点对中可能成为答案的只占这里面的小部分。

考虑什么样的点对是对答案可能产生贡献的，不难发现，如果对于 $x<y<z$，且 $dis_z>dis_y$，则点对 $(x,z)$ 是不可能成为答案的。可以得到一个结论：如果 $\max(dis_x,dis_y)<\min\limits_{z\in S,x<z<y} dis_z(x<y)$，因为如果 $x$ 和 $y$ 之间如果存在 $z$ 满足 $\max(dis_x,dis_y)\ge dis_z$，则把 $dis_x$ 和 $dis_y$ 中较大的那个节点换为 $z$ 一定更优。

再考虑如何实现，先把 $S$ 中的点按节点编号从小到大排序，在维护一个单调递增的单调栈（从栈底到栈顶），每插入一个节点，就把这一次弹出栈的点和当前节点作为有效点对存起来，再把当前节点和插入当前节点前的栈顶存起来。不难发现这样是对的，对于弹出栈的节点，由于 $dis$ 大于当前节点，对于后面一定是没用的，且对于当前节点是有用的，因为是原来的后缀最小值。把没用的节点后弹出栈后，由于当前节点的 $dis$ 是大于栈顶的，所以和栈顶下面的节点也是不可能对答案造成贡献的。这样做完一遍后，当前连通块的有效点对个数就是 $O(\vert S\vert)$ 的，有效点对总数也就是 $O(n\log n)$ 的。

剩下的就是一个类似二维偏序的东西，把询问和有效点对按照其中一个点排序，遍历到有效点对就在树状数组中另一个点的位置进行单点修改，询问就在树状数组里查另一个点的前 / 后（前或后取决于是按哪个点排序的）缀的最大值，时间复杂度 $O(n\log^2n+q\log n)$。

# Code
```
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
#include<bits/extc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
using namespace __gnu_pbds;
//using namespace atcoder;
const int N=2e5+1,M=1e6;
int n,m,T[N],ans[M],s[N];
vector<P> a,g[N],C[N],Q[N];
int siz[N],Size,root,rmax;
bool st[N];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
void Dfs(int u,int fa,int maxs=0) {
	siz[u]=1; for (auto &[v,w]:g[u]) if (v^fa&&!st[v]) Dfs(v,u),siz[u]+=siz[v],maxs=max(maxs,siz[v]);
	maxs=max(maxs,Size-siz[u]); if (maxs<rmax) rmax=maxs,root=u;
}
void dfs(int u,int fa,int dis=0) {
	a.push_back({u,dis}); for (auto &[v,w]:g[u])
	if (v^fa&&!st[v]) dfs(v,u,dis+w);
}
void solve(int u)
{
	rmax=Size,root=u,Dfs(u,0),Dfs(root,0),a.clear();
	dfs(root,0),st[root]=true,sort(a.begin(),a.end() );
	for (int i=0,top=0;i<a.size();i++) {
		while (top&&a[i].second<=a[s[top] ].second)
		C[a[s[top] ].first].push_back({a[i].first,a[i].second+a[s[top] ].second}),top--;
		if (top) C[a[s[top] ].first].push_back({a[i].first,a[i].second+a[s[top] ].second}); s[++top]=i;
	}
	for (auto &[v,w]:g[root])
	if (!st[v]) Size=siz[v],solve(v);
}
void add(int x,int y) { while (x<=n) T[x]=min(T[x],y),x+=x&-x; }
int query(int x,int res=LLONG_MAX) { while (x) res=min(res,T[x]),x&=x-1; return res; }

main()
{
	Size=n=read();
	for (int i=1,x,y,z;i<n;i++) {
		x=read(),y=read(),z=read();
		g[x].push_back({y,z}),g[y].push_back({x,z});
	}
	solve(1),memset(T,0x3f,sizeof T);
	m=read(); for (int i=0,x,y;i<m;i++)
	x=read(),Q[x].push_back({read(),i});
	for (int i=n;i;i--) {
		for (P o:C[i]) add(o.first,o.second);
		for (P o:Q[i]) ans[o.second]=query(o.first);
	}
	for (int i=0;i<m;i++)
	printf("%lld\n",ans[i]>1e15?-1:ans[i]);
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

之前模拟赛也考到过这种转化成支配点对来维护的问题，所以来整理一下题解。

首先这明显是一个二维偏序问题，但点数在 $O(n^2)$ 级别，肯定无法接受，但刻画一下条件，我们感性理解可以发现其实有大多数点是没有用的。

具体而言，我们观察二元组 $(i,k),(j,k)$，其中满足 $i<j<k$，如果 $dis(i,k)>dis(j,k)$，那么在统计的时候我们肯定会统计到 $(j,k)$ 而不是 $(i,k)$，换言之，$(i,k)$ 这对点是无用点对，我们称 $(j,k)$ 是 $(i,k)$ 的支配点对。

考虑点分治，那么重新刻画支配点对的条件，令当前分治中心为 $r$，$d_i=dis(i,r)$，我们将此时邻域内的所有点按下标排序，那么当 $d_i+d_k>d_j+d_k$，也就是 $d_i>d_j$ 时，$i$ 就会变成一个无用点，因为后面所有点和 $j$ 匹配一定由于 $i$。

此时，对于条件的刻画已经非常清楚了，考虑维护，每一轮分治先将所有点按下标排序，维护一个下标与值域单调递增的单调栈，考虑插点时，所有弹出栈外的点都是因为这个点而变成无用点的，所以这些点会和当前插入的这个点形成一个关键点对，特别地，和弹完栈后的栈顶元素也会成为关键点对，因为后来的点的深度一定不会大于当前插入的点。

注意到每一轮分治中的所有点都只会被匹配 $O(1)$ 次，所以总的支配点对的数量是 $O(n \log n)$ 级别的。

接下来就简单了，是一个二维偏序求最小值，左端点从大到小排序用树状数组维护前缀最小值就行了。

时间复杂度 $O(n \log^2 n + q \log n)$，空间复杂度 $O(n \log n + q)$。

讲的可能不好，所以贴个代码。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
int n,Q;
struct edge{
    int to;
    int next;
    int w;
}ed[400005];
int cnt;
int h[200005];
void add(int x,int y,int w){
    ed[++cnt]={y,h[x],w};
    h[x]=cnt;
}
struct query{
    int l,r;
    int id;
}q[1000005];
ll res[1000005];
// 点分治
struct Key{
    int l,r;
    ll w;
}p[10000005];//关键点对
int top;
int Root;
int maxx[200005],sz[200005];
bool vis[200005];
void get_sz(int x,int fa){
    sz[x]=1;
    for(int i=h[x];i;i=ed[i].next){
        int v=ed[i].to;
        if(v==fa||vis[v])continue;
        get_sz(v,x);
        sz[x]+=sz[v];
    }
}
void get_Root(int x,int fa,int sum){
    maxx[x]=0;
    for(int i=h[x];i;i=ed[i].next){
        int v=ed[i].to;
        if(v==fa||vis[v])continue;
        get_Root(v,x,sum);
        maxx[x]=max(maxx[x],sz[v]);
    }
    maxx[x]=max(maxx[x],sum-sz[x]);
    if(maxx[x]<maxx[Root])Root=x;
}
ll dep[200005];
vector<int>vec;//id
int stk[200005];
void get_dis(int x,int fa){
    vec.push_back(x);
    for(int i=h[x];i;i=ed[i].next){
        int v=ed[i].to;
        if(v==fa||vis[v])continue;
        dep[v]=dep[x]+ed[i].w;
        get_dis(v,x);
    }
}
void calc(int x){
    vec.clear();
    dep[x]=0;
    vec.push_back(x);
    for(int i=h[x];i;i=ed[i].next){
        int v=ed[i].to;
        if(vis[v])continue;
        dep[v]=dep[x]+ed[i].w;
        get_dis(v,x);
    }
    //现在已经找到了该分治中心子树中的所有点
    sort(vec.begin(),vec.end());//按id排序
    int t=0;//栈顶
    for(int x:vec){
        while(t&&dep[stk[t]]>=dep[x]){
            p[++top]={stk[t],x,dep[stk[t]]+dep[x]};
            --t;
        }
        if(t)p[++top]={stk[t],x,dep[stk[t]]+dep[x]};
        stk[++t]=x;
    }
}
void solve(int x){
    vis[x]=1;
    calc(x);
    for(int i=h[x];i;i=ed[i].next){
        int v=ed[i].to;
        if(vis[v])continue;
        get_sz(v,x);
        maxx[Root=0]=1e9;
        get_Root(v,x,sz[x]);
        solve(Root);
    }
}
struct Binary_indexed_tree{
    ll tree[200005];
    int lowbit(int i){return i&-i;}
    void clear(){
        memset(tree,0x3f,sizeof tree);
    }
    void add(int pos,ll val){
        for(int i=pos;i<=n;i+=lowbit(i))tree[i]=min(tree[i],val);
    }
    ll ask(int pos){
        ll ans=1e18;
        for(int i=pos;i;i-=lowbit(i))ans=min(ans,tree[i]);
        return ans;
    }
}T;
signed main(){
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read(),w=read();
        add(x,y,w),add(y,x,w);
    }
    //find key point
    
    maxx[Root=0]=1e9;
    get_sz(1,0);
    get_Root(1,0,n);
    solve(Root);
    // for(int i=1;i<=top;i++)cerr<<p[i].l<<' '<<p[i].r<<' '<<p[i].w<<'\n';
    //answer
    T.clear();
    Q=read();
    for(int i=1;i<=Q;i++){
        q[i].l=read(),q[i].r=read(),q[i].id=i;
    }
    sort(q+1,q+1+Q,[&](query a,query b){return a.l>b.l;});
    sort(p+1,p+1+top,[&](Key a,Key b){return a.l>b.l;});
    int now=1;
    for(int i=1;i<=Q;i++){
        while(now<=top&&p[now].l>=q[i].l){
            T.add(p[now].r,p[now].w);
            ++now;
        }
        if(q[i].l==q[i].r)res[q[i].id]=-1;
        else res[q[i].id]=T.ask(q[i].r);
    }
    for(int i=1;i<=Q;i++){
        cout<<res[i]<<'\n';
    }
    return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

一年多前就想写的题，然后今年 T4 被支配对类问题薄纱，然后回来做。

支配关系是显然的，就是 $(l_1,r_1)$ 支配 $(l_2,r_2)$ 的条件是 $l_2 \le l_1 < r_1 \le r_2$ 并且 $\text{dist}(l_1,r_1) \le \text{dist}(l_2,r_2)$。

考虑把所有支配对扒出来，首先给拍一个点分治上去，然后 $(x,y)$ 会存在一个使其不同子树的根 $rt$。

然后对于 $u$ 只需要找到满足 $x \ne u,\text{dist}(x,rt) \le \text{dist}(u,rt)$ 的 $u$ 的前驱后缀就行。

每一层产生 $O(n)$ 个支配对，总共产生 $O(n \log n)$，求完弄下来做一遍二维数点。

支持负权边要麻烦一点，可能要加个维护前驱后继的东西做一下。

总时间复杂度 $O(n \log^2 n + q \log n)$。

---

## 作者：_Ch1F4N_ (赞：0)

我怎么模拟赛被支配对干掉了？

赶紧加练下支配对。

假若 $l_1 \leq l_2 < r_2 \leq l_2$ 并且 $dis(l_1,r_1) \geq dis(l_2,r_2)$，那么显然 $(l_1,r_1)$ 是根本没有用处的。

但是你考虑 $dis(u,v)$ 貌似只能在树上刻画，直接用其去 check 哪些对是没用的很麻烦，所以考虑对原树做点分治，每次处理横跨分治中心的点对，也就是两个不同连通块中的点 $u,v$ 的距离为 $dep_u + dep_v$，注意到假若 $u,v$ 在同一个连通块中，$dep_u + dep_v \geq dis(u,v)$，这个贡献是不优的，因此我们可以无视 $u,v$ 处于不同连通块中这个限制。

现在要解决 $i,j$ 的贡献是 $dep_i + dep_j$ 这个问题，下面不妨 $i<j$，注意到一定有 $\min_{k=i+1}^{j-1} dep_k > \max(dep_i,dep_j)$，不然你把 $i,j$ 往内侧移一定不劣，由于 $\max$ 比较烦并且里面只有两项就先考虑把其拆开，不妨假设 $dep_j \geq dep_i$，那么限制变成 $\min_{k=i+1}^{j-1} > dep_j$ 或者说 $dep_i \leq \min_{k=i}^j dep_k$，按照下标从前往后扫，以 $dep$ 建立单调栈后你发现显然 $i$ 会是扫到 $j$ 时单调栈上一个点，因为不在单调栈上的点一定是被其后面一个比其小的点弹掉了，不符合条件，接下来我们发现，这这个点一定是单调栈上最后一个点，因为假若取了单调栈上其余点，那么这个其余点与 $j$ 匹配不如这个其余点与单调栈最后一个点匹配，因此可以求出 $O(sz)$ 个有效的点对，当 $dep_j \leq dep_i$ 时倒着这么做一遍即可，因此总共可以求出 $O(n \log n)$ 个有效点对，回答询问就是一个简单扫描线。

时间复杂度 $O(n \log^2 n + q \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int maxq = 1e6+114;
const int inf = 1e18+114;
int n,q;
vector< pair<int,int> > E[maxn];
int sz[maxn];
int siz,mid;
int vis[maxn];
void dfs(int u,int lst){
    sz[u]=1;
    int mx=0;
    for(pair<int,int> nxt:E[u]){
        int v=nxt.first,w=nxt.second;
        if(vis[v]==0&&v!=lst){
            dfs(v,u);
            sz[u]+=sz[v];
            mx=max(mx,sz[v]);
        }
    }
    if(mx*2<=siz&&(siz-sz[u])*2<=siz) mid=u;
}
vector<int> P;//(id,dep)
int dep[maxn];
void calc(int u,int lst,int depth){
    dep[u]=depth;
    P.push_back(u);
    sz[u]=1;
    for(pair<int,int> nxt:E[u]){
        int v=nxt.first,w=nxt.second;
        if(vis[v]==0&&v!=lst){
            calc(v,u,depth+w);
            sz[u]+=sz[v];
        }
    }
}
vector< pair<int,int> > key[maxn];//(l,dis) 挂在 r 上
int stk[maxn],tp;
void solve(int u,int sum){
    if(sum==1) return ;
    siz=sum,mid=0;
    dfs(u,0);
    vis[mid]=1;
    P.clear();
    dep[mid]=0;
    P.push_back(mid);
    for(pair<int,int> nxt:E[mid]){
        int v=nxt.first,w=nxt.second;
        if(vis[v]==0) calc(v,0,w);
    }
    tp=0;
    sort(P.begin(),P.end());
    for(int i:P){
        while(tp>0&&dep[stk[tp]]>dep[i]) tp--;
        if(tp!=0) key[i].push_back(make_pair(stk[tp],dep[stk[tp]]+dep[i]));
        stk[++tp]=i;
    }
    reverse(P.begin(),P.end());
    tp=0;
    for(int i:P){
        while(tp>0&&dep[stk[tp]]>dep[i]) tp--;
        if(tp!=0) key[stk[tp]].push_back(make_pair(i,dep[stk[tp]]+dep[i]));
        stk[++tp]=i;
    }
    for(pair<int,int> nxt:E[mid]){
        int v=nxt.first,w=nxt.second;
        if(vis[v]==0) solve(v,sz[v]);
    }
}
vector< pair<int,int> > Q[maxn];
int answer[maxq];
int tr[maxn<<2];
void upd(int cur,int lt,int rt,int pos,int v){
    tr[cur]=min(tr[cur],v);
    if(lt==rt){
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid) upd(cur<<1,lt,mid,pos,v);
    else upd(cur<<1|1,mid+1,rt,pos,v);
}
int ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return inf;
    if(l<=lt&&rt<=r){
        return tr[cur];
    }
    int mid=(lt+rt)>>1;
    return min(ask(cur<<1,lt,mid,l,r),ask(cur<<1|1,mid+1,rt,l,r));
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    for(int i=0;i<maxq;i++) answer[i]=inf;
    for(int i=0;i<(maxn<<2);i++) tr[i]=inf;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        E[u].push_back(make_pair(v,w));
        E[v].push_back(make_pair(u,w));
    }
    solve(1,n);
    cin>>q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        Q[r].push_back(make_pair(l,i));
    }
    for(int r=1;r<=n;r++){
        for(pair<int,int> now:key[r]) upd(1,1,n,now.first,now.second);
        for(pair<int,int> now:Q[r]) answer[now.second]=ask(1,1,n,now.first,r);
    }
    for(int i=1;i<=q;i++) cout<<(answer[i]<inf?answer[i]:-1)<<'\n';
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到点对数量有 $N^2$ 个，考虑丢掉一些无用的点对。

对于点对 $(x_1,y_1),(x_2,y_2)$，满足 $x_1 \le x_2 < y_2 \le y_1$，即区间 $[x_2,y_2]$ 被 $[x_1,y_1]$ **包含**，此时满足若询问到了 $[x_1,y_1]$，则一定会询问到 $[x_2,y_2]$。

若满足 $\operatorname{dis}(x_1,y_1) \ge \operatorname{dis}(x_2,y_2)$，那么此时可以将 $(x_1,y_1)$ **舍弃**，因为若要用 $(x_1,y_1$) 的贡献，不如直接去看 $(x_2,y_2)$ 的贡献，毕竟 $(x_1,y_1)$ 的贡献一定不会比 $(x_2,y_2)$ 更优。

那么我们可以定义若两个点对 $(x_1,y_1),(x_2,y_2)$ 满足以下条件，则称 $(x_1,y_1)$ 被 $(x_2,y_2)$ **支配**：

- $x_1 \le x_2 < y_2 \le y_1$。

- $\operatorname{dis}(x_1,y_1) \ge \operatorname{dis}(x_2,y_2)$。

此时定义一个**支配点对**满足没有被任何一个点对**支配**，即我们需要找出所有的**支配点对**来计算贡献。

注意到是一个树上点对距离问题，考虑**点分治**解决。

令当前**分治重心**为 $rt$，对于点 $v$，令 $S_v$ 表示当前联通块中**所有**满足 $\operatorname{dis}(i,rt) \le \operatorname{dis}(v,rt)$ 的 $i$ 组成的一个**集合**。

那么可以与 $v$ 组成**支配点对**的点一定是 $S_v$ 中 $v$ 的**前驱**和**后继**，即 $S_v$ 中 $<v$ 中**最大的数**和 $>v$ 中**最小的数**。

简单证一下，设 $S_v$ 中 $v$ 的**前驱**为 $u$：

- 有 $\operatorname{dis}(i,u) \le \operatorname{dis}(i,rt) + \operatorname{dis}(u,rt) \le \operatorname{dis}(i,rt) + \operatorname{dis}(v,rt) = \operatorname{dis}(i,v)$，即 $\operatorname{dis}(i,u) \le \operatorname{dis}(i,v)$。

- 注意到此时 $i < u < v$ 或 $u < v < i$，即 $(i,v)$ 被 $(i,u)$ **支配**或 $(u,i)$ 被 $(v,i)$ **支配**。

- 那么只有当 $i=u$ 时，$(u,u)$ 点对**不存在**，$(u,v)$ 不会被其它 $S_v$ 中的点对支配。

**后继**情况类似，就不多说了。

然后考虑如何快速找到**支配点对**，直接按照上面的方法找 $S_v$，复杂度肯定是 $O(N^2)$ 起步，考虑优化。

首先对于整个联通块的所有点，按照点的**编号**排序升序，然后维护一个 $\operatorname{dis}(i,rt)$ 不降的**单调栈**。

那么有一个性质是，对于被点 $i$ 弹出去的点 $u$，肯定满足 $i$ 是 $u$ 后面**第一个**小于等于 $\operatorname{dis}(u,rt)$ 的点且编号最小，即 $i$ 是 $S_u$ 中 $u$ 的**前驱**；然后再倒着降序做一遍**单调栈**找**后继**即可。

此时我们来估算一下**支配点对**的数量，每个点最多被 $\log N$ 个**分治重心**包含，每次包含最多增加 $2$ 对**支配点对**，即总**支配点对**的数量为 $N \log N$ 左右。

现在求出了全部的**支配点对**，即有贡献的点对，现在考虑如何求被一个区间**包含**的所有**支配点对**的最小贡献值，可以在线使用**树套树**，但是没必要。

考虑离线使用**扫描线**算法，因为树状数组不好维护后缀最值，考虑倒着扫左端点，然后对于每个点对，在左端点处将右端点贡献加入进去；那么对于一个在左端点的询问，就是一个前缀最小值。

时间复杂度为 $O(N \log^2 N + Q \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const ll N=2e5+10,M=1e6+10,INF=1e18; 
bool Begin;
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
int n,q;
ll ans[M];
vector<int> G[N];
vector<pair<int,ll>> E[N],Q[N];
void add(int u,int v,int w){
	E[u].push_back({v,w});
	E[v].push_back({u,w});
}
namespace Lowbit{
	ll a[N];
	inline void init(){
		for(int i=1;i<=n;i++)
		  a[i]=INF;
	}
	inline void add(int x,ll w){
		for(int i=x;i<=n;i+=lowbit(i))
		  a[i]=min(a[i],w);
	}
	inline ll query(int x){
		ll ans=INF;
		for(int i=x;i;i-=lowbit(i))
		  ans=min(ans,a[i]);
		return ans;
	}	
};
namespace LCA{
	int p[N],t[N],z[N],d[N],fa[N];
	ll dep[N];
	inline void dfs1(int u,int f){
		p[u]=1;
		for(auto t:E[u]){
			int v=t.first,w=t.second;
			if(v==f)
			  continue;
			dep[v]=dep[u]+w;
			d[v]=d[u]+1;
			fa[v]=u;
			dfs1(v,u);
			p[u]+=p[v];
			if(p[v]>p[z[u]])
			  z[u]=v;
		}
	}
	inline void dfs2(int u,int k){
		t[u]=k;
		if(!z[u])
		  return ;
		dfs2(z[u],k);
		for(auto t:E[u]){
			int v=t.first;
			if(v==fa[u]||v==z[u])
			  continue;
			dfs2(v,v);
		}
	}
	inline int Lca(int u,int v){
		while(t[u]!=t[v]){
			if(d[t[u]]<d[t[v]])
			  swap(u,v);
			u=fa[t[u]];
		}
		return d[u]<d[v]?u:v;
	}
	inline ll dis(int u,int v){
		return dep[u]+dep[v]-(dep[Lca(u,v)]<<1ll);
	}
	inline void init(){
		dfs1(1,1);
		dfs2(1,1);
	}
};
namespace Tree{
	int sum,cnt,top,Max,root;
	int T[N],siz[N];
	pair<int,ll> dis[N];
	bool del[N];
	inline void add(int x,int y){
		if(x>y)
		  swap(x,y);
		G[x].push_back(y);
	}
	inline void getroot(int u,int fa){
		int s=0;
		siz[u]=1;
		for(auto t:E[u]){
			ll v=t.first;
			if(del[v]||v==fa)
			  continue;
			getroot(v,u);
			siz[u]+=siz[v];
			s=max(s,siz[v]);
		}
		s=max(s,sum-siz[u]);
		if(s<Max){
			Max=s;
			root=u;
		}
	}
	inline void Get(int u,int p){
		root=0;
		sum=Max=p;
		getroot(u,0);
		getroot(root,0);
	}
	inline void getdis(int u,int fa,ll d){
		dis[++cnt]={u,d};
		for(auto t:E[u]){
			int v=t.first,w=t.second;
			if(v==fa||del[v])
			  continue;
			getdis(v,u,d+w);
		}
	}
	inline void calc(int u){
		cnt=0;
		getdis(u,0,0);
		sort(dis+1,dis+cnt+1);
		top=0;
		for(int i=1;i<=cnt;i++){
			while(top&&dis[i].second<=dis[T[top]].second){
				add(dis[i].first,dis[T[top]].first);
				top--;
			}
			T[++top]=i;
		}
		top=0;
		for(int i=cnt;i>=1;i--){
			while(top&&dis[i].second<=dis[T[top]].second){
				add(dis[i].first,dis[T[top]].first);
				top--;
			}
			T[++top]=i;			
		}
	}
	inline void solve(int u){
		calc(u);
		del[u]=1;
		for(auto t:E[u]){
			int v=t.first;
			if(del[v])
			  continue;
			Get(v,siz[v]);
			solve(root);
		}
	}	
	void work(){
		Lowbit::init();
		LCA::init();
		Get(1,n);
		solve(root);
	}
};
bool End;
int main(){
//	open("A.in","A.out");
	n=read();
	for(int u,v,w,i=1;i<n;i++){
		u=read(),v=read(),w=read();
		add(u,v,w); 
	}
	q=read();
	for(int l,r,i=1;i<=q;i++){
		l=read(),r=read();
		Q[l].push_back({i,r});
	}
	Tree::work();
	for(int i=n;i>=1;i--){
		for(auto v:G[i])
		  Lowbit::add(v,LCA::dis(i,v));
		for(auto t:Q[i])
		  ans[t.first]=Lowbit::query(t.second);
	}
	for(int i=1;i<=q;i++){
		write(ans[i]==INF?-1:ans[i]);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：win114514 (赞：0)

支配点对实在是太有意思了。

本质上就是一个合法的减枝。

### 思路

考虑维护树上路径问题。

容易想到点分治。

考虑在当前的分治中心 $\text{rt}$，每个点到当前分治中心的距离为 $dp_x$。

求出每一组点对的贡献。

假设每个点对在距离长的那部分贡献，即 $dp_i>dp_j$，求出所有的 $j$。

结论：每个点只需要求出符合条件下的前驱后继即可。

如何证明。

假设有 $dp_j,dp_k<dp_i$，$k<j<i$。

那么如果选了 $i,k$ 两点，那么是绝对不如选 $j,k$ 两点的。

后继同理。

那么我们只要在点分治时。

用一个单调栈来维护这个东西。

我们按节点编号从小到大，从大到小排序做两次，维护一个单调不降的单调栈。

每个点的前驱后继就是把它弄出栈的那个点。

把所有点对扯出来以后，可以使用扫描线和树状数组维护。

代码很好写。

### Code

```cpp
/**
 * @file P9678.cpp
 * @author win114514
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 998244353;

int n, m, rt, rtsz;
int sz[N], mz[N], vs[N];
i64 t[N], dp[N], ans[N];
vector<int> son;
vector<pair<int, i64>> to[N], que[N];
vector<tuple<int, int, i64>> fin;

inline int lb(int x)
	{ return x & (-x); }
inline void upd(int x, i64 v)
	{ while(x <= n) t[x] = min(t[x], v), x += lb(x); }
inline i64 ask(int x)
	{ i64 res = 1e17; while(x) res = min(res, t[x]), x -= lb(x); return res; }
inline void frt(int x, int fa = 0)
{
	sz[x] = 1, mz[x] = 0;
	for(auto [y, w] : to[x])
	{
		if(y == fa || vs[y]) continue;
		frt(y, x), sz[x] += sz[y];
		mz[x] = max(mz[x], sz[y]);
	}
	mz[x] = max(mz[x], rtsz - sz[x]);
	if(mz[x] < mz[rt]) rt = x;
}
inline void dfs(int x, int fa = 0)
{
	son.eb(x), sz[x] = 1;
	for(auto [y, w] : to[x])
	{
		if(y == fa || vs[y]) continue;
		dp[y] = dp[x] + w, dfs(y, x);
		sz[x] += sz[y];
	}
}
inline void calc(int x)
{
	son.clear(), dp[x] = 0, dfs(x);
	sort(son.begin(), son.end());
	static int stk[N]; int top = 0;
	for(auto i : son)
	{
		while(top && dp[stk[top]] >= dp[i])
			fin.eb(stk[top], i, dp[stk[top]] + dp[i]), top--;
		stk[++top] = i;
	}
	top = 0;
	sort(son.begin(), son.end(), greater<>());
	for(auto i : son)
	{
		while(top && dp[stk[top]] >= dp[i])
			fin.eb(stk[top], i, dp[stk[top]] + dp[i]), top--;
		stk[++top] = i;
	}
}
inline void solve(int x)
{
	vs[x] = 1, calc(x);
	for(auto [y, w] : to[x])
	{
		if(vs[y]) continue;
		rt = 0, rtsz = sz[y];
		frt(y), solve(rt);
	}
}
inline void solve()
{
	cin >> n;
	fro(i, 1, n - 1)
	{
		int x, y, w;
		cin >> x >> y >> w;
		to[x].eb(y, w), to[y].eb(x, w);
	}
	rtsz = mz[0] = n, frt(1), solve(rt);
	memset(t, 0x3f, sizeof t);
	cin >> m;
	fro(i, 1, m)
	{
		int l, r;
		cin >> l >> r;
		que[l].eb(r, i);
	}
	fro(i, 1, n) to[i].clear();
	for(auto [x, y, w] : fin)
	{
		if(x > y) swap(x, y);
		to[x].eb(y, w);
	}
	pre(i, n, 1)
	{
		for(auto [x, w] : to[i])
			upd(x, w);
		for(auto [x, id] : que[i])
			ans[id] = ask(x);
	}
	fro(i, 1, m)
		cout << (ans[i] == 1e17 ? -1 : ans[i]) << "\n";
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 1024;
	cerr << " Memory: " << Mib << "\n", assert(Mib<=Lim);
	solve();
	return 0;
}

```

---

