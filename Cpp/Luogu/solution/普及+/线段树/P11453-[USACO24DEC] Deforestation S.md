# [USACO24DEC] Deforestation S

## 题目描述

Farmer John 正在扩大他的农场！他已经找到了完美的位置——红黑森林，由数轴上的 $N$ 棵树（$1≤N≤10^5$）组成，第 $i$ 棵树位于位置 $x_i$（$−10^9≤x_i≤10^9$）。

环境保护法限制了 Farmer John 可以砍伐哪些树来为他的农场腾出空间。有 $K$ 个限制（$1≤K≤10^5$），规定在线段 $[l_i,r_i]$（包含端点）中必须始终至少存在 $t_i$ 棵树（$−10^9≤l_i,r_i≤10^9$）。输入保证红黑森林初始时满足这些限制。

Farmer John 想要他的农场尽可能大。请帮助他计算他可以砍伐的树的最大数量，同时仍然满足所有限制！

## 说明/提示

### 样例解释

对于第一个测试用例，Farmer John 可以砍伐前 $4$ 棵树，留下位于 $x_i=2,6,7$ 的树来满足限制。

对于第二个测试用例，额外的限制不会影响 Farmer John 可以砍伐哪些树，因此他可以砍伐相同的树并同时满足两个限制。

对于第三个测试用例，Farmer John 至多只能砍伐 $3$ 棵树，因为初始时有 $7$ 棵树，但第二个限制要求他至少留下 $4$ 棵树不砍伐。

### 测试点性质

测试点性质：
- 测试点 1：样例。
- 测试点 2：$N,K≤16$。
- 测试点 3-5：$N,K≤1000$。
- 测试点 6-7：对于所有的 $i=1,\cdots,K$ 有 $ti=1$。
- 测试点 8-11：没有额外限制。

## 样例 #1

### 输入

```
3
7 1
8 4 10 1 2 6 7
2 9 3
7 2
8 4 10 1 2 6 7
2 9 3
1 10 1
7 2
8 4 10 1 2 6 7
2 9 3
1 10 4```

### 输出

```
4
4
3```

# 题解

## 作者：masonxiong (赞：10)

# 题目分析

~~这道题似乎就是 CSP-S T2 的加强版~~

根据 CSP-S T2 得出的经验，我们可以贪心地从左往右删，因为如果在这个位置删满足条件，那么在右边删可能会浪费条件导致不优，但一定不会因为改到右边而多删。

那么这样我们就可以非常简单的写出一个 $O(nk)$ 的暴力贪心了。接下来我们只需要考虑如何将这个算法优化即可。

这里阐述官方题解的优化方法，即用优先队列进行优化，具体实现比较巧妙。

我们将限制按左端点从小到大排序，树按坐标从小到大排序，并将这两个排序后的结果合并起来记为 `events`。

然后我们开一个优先队列 `Q`，它的第一位是最多能砍多少棵树，第二位是目前处理到的右端点坐标。它以第二位为第一关键字，第一位为第二关键字的小根堆。

我们扫一遍 `events`：

若这是一个限制，则我们按照贪心策略尝试将这个限制中所有能砍的树全砍了，即 `Q.emplace(answer + p, r);`。

若这是一棵树，我们先把所有没有管辖这棵树的限制全都从 `Q` 中弹出，由于我们已经将 `events` 排序，所有左端点一定合法，我们只需要判断右端点是否合法即可。

若 `Q` 中无元素，说明无限制管辖这棵树，自然可以砍掉它，令答案自增；或者若“目前最多砍的树的数量比目前答案要大（`Q.top().first > answer`）”，说明这个限制中的树我们还没有砍完，那我们也可以砍掉这棵树。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 5e5 + 5;
int t, n, k, l, r, p;
int trees[Maxn];

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	for (cin >> t; t--; ) {
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> trees[i];
		sort(trees, trees + n);
		vector<tuple<int, int, int, int>> events;
		// 第一位是（限制：左端点 / 树：坐标），第二位表示类型（0：限制 / 1：树）。
		// 第三位是（限制：右端点 / 树：无意义），第四位是（限制：这个区间内还能砍多少棵树 / 树：无意义）。
		// 特别注意第二位的类型不能调换顺序，因为我们要先处理限制再处理树。
		for (int i = 0; i < n; i++)
			events.emplace_back(trees[i], 1, 0, 0);
		while (k--) {
			cin >> l >> r >> p;
			events.emplace_back(l, 0, r, upper_bound(trees, trees + n, r) - lower_bound(trees, trees + n, l) - p /* 计算区间内还能砍多少棵树。 */);
		}
		sort(events.begin(), events.end());
		// 将所有东西按照左端点从小到大排序。
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		// 第一位是最多能砍多少棵树，第二位是目前处理到的右端点坐标。
		// 以第二位为第一关键字，第一位为第二关键字的小根堆。
		int answer = 0;
		for (const auto& event : events) {
			tie(l, k, r, p) = event;
			if (k == 0) {
				Q.emplace(answer + p, r);
				// 将这个限制所对应的区间内的树全都砍掉，并更新右端点。
			} else {
				for (; !Q.empty() && Q.top().second < l; Q.pop());
				// 将未包含这棵树的限制全都清除掉。
				answer += Q.empty() // 没有限制可以管辖这棵树，当然可以砍掉。
						  || Q.top().first > answer; // 这个限制还没有砍完，根据贪心策略我们能砍就砍。
			}
		}
		cout << answer << '\n';
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：6)

## 思路分析

正难则反。我们可以转而求满足每个要求所需要的最少的树的数量。

但是，树不连续啊！

无所谓啊，我们强制把树压到一起，然后将区间也压到相应的那些树的位置，于是变成了[种树](https://www.luogu.com.cn/problem/P1250)的加强版，用差分约束就做完了。差分约束的细节可以看[这篇](https://www.luogu.com.cn/article/3e7l1tou)题解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, x[100005], dis[100005];
struct node {
    int p, v;
    node(int pi = 0, int vi = 0) :p(pi), v(vi) {};
}; vector<node>son[100005];
queue<int>q; bool vis[100005];
signed main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> n >> m;
        for (int i = 0; i <= n; ++i) son[i].clear();
		for (int i = 1; i <= n; ++i) cin >> x[i];
		sort(x + 1, x + n + 1);
        for (int i = 1, l, r, v; i <= m; ++i)
            cin >> l >> r >> v,
            l = lower_bound(x + 1, x + n + 1, l) - x,
            r = upper_bound(x + 1, x + n + 1, r) - x - 1,
            son[l - 1].emplace_back(r, v);
        for (int i = 0; i <= n; ++i) {
            if (i != 0) son[i - 1].emplace_back(i, 0), dis[i] = -1e9;
            if (i != n) son[i].emplace_back(i - 1, -1);
        }
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); vis[u] = 0; q.pop();
            for (node sp : son[u])
                if (dis[sp.p] < dis[u] + sp.v) {
                    dis[sp.p] = dis[u] + sp.v;
                    if (!vis[sp.p])q.push(sp.p), vis[sp.p] = 1;
                }
        }
        cout << n - dis[n] << endl;
	}
}
```

---

## 作者：XGTD (赞：6)

# P11453 Deforestation 题解
介绍一种和堆贪心正解不同，更加直白好想，用树状数组或线段树的方法。
## Preface
这题堆贪心正解还是挺难想的。
赛时想出了这个解法，但是因为是银组懒得写树状数组拿了前五个点就跳了去做第三题，没想到第三题虽然想出正解居然没调出来，痛失金组。赛后老老实实写树状数组这题秒了。~~哭死。~~
## Problem statement
[P11453](https://www.luogu.com.cn/problem/P11453)
解释的比较清楚了。

## Solution
首先发现砍树不好想，考虑最少种几棵树。
发现希望每棵树满足尽量多的区间。
尝试贪心，考虑按右端点升序排序，对于每一个区间肯定尽量种最靠右的树。

这样我们就有了一个 $O(nk)$ 的贪心暴力，因为每砍一棵树需要将他做了贡献的区间需要种的树的数量减一。

想优化就需要一个能够快速统计一个区间里已经种了多少棵树的数据结构，考虑线段树或树状数组。每次维护之前右端点较小的区间已经在目前这个区间里种了多少棵树，这次就可以少种这么多棵。

同时注意到我们还需要一个数据结构，支持二分最大的比目前右端点小的树，和删除树两种操作，我用了 `multiset`。

## Code

```cpp
/*
I hate this problem
it's a good problem, but I really could've solved it in contest
I was so dumb
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct seg{
	int l, r, val, ori;
	const bool operator<(const seg &a) const{
		if(r != a.r)return r<a.r;
		else return l < a.l;
		//always remember to write the ELSE!!!!!!!
	}
} a[100005];
struct event{
	int pos, typ, ori, val;
	const bool operator<(const event &a) const{
		return pos < a.pos;
	}
}eve[300005];
int cmp(int x,int y){//for sort
    return x>y;
}
int n, t, k, p[100005], ans, c[300005], v[300005];
//position of each tree
int rang;
void add(int x, int y){
	for(int i = x; i <= rang; i += i & -i){
		c[i] += y;
	}
}
int get(int x){
	int anst = 0;
	for(int i = x; i > 0; i -= i & -i){
		anst += c[i];
	}
	return anst;
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans = n;
		vector<int> e[100005];		
		for(int i = 1; i <= n; i++){
			int x;
			cin>>x;
			eve[i].pos = x;
			eve[i].typ = 0;//a tree is type 0
			eve[i].ori = i;//the ith tree
		}
		for(int i = 1; i <= k; i++){
			int x, y, z;
			cin>>x>>y>>z;
			eve[2 * i - 1 + n].pos = x;
			eve[2 * i - 1 + n].typ = 1;//type1 = region left end
			eve[2 * i - 1 + n].ori = i;
			eve[2 * i - 1 + n].val = z;
			eve[2 * i + n].pos = y;
			eve[2 * i + n].typ = 2;//type2 = right end
			eve[2 * i + n].ori = i;
			eve[2 * i + n].val = z;
		}
		sort(eve + 1, eve + n + 2 * k + 1);
		int rank = 0;
		eve[0].pos = 1e9 + 10;//out of bound
		for(int i = 1; i <= n + 2 * k; i++){
			if(eve[i].pos != eve[i - 1].pos)rank++;
			if(eve[i].typ == 0){
				//a tree
				p[eve[i].ori] = rank;
			}else{
				if(eve[i].typ == 1){
					a[eve[i].ori].l = rank;
					a[eve[i].ori].val = eve[i].val;
				}else{
					a[eve[i].ori].r = rank;
				}
			}
		}
		//discretization done
		sort(a + 1, a + k + 1);
		//ascending regarding right end
		sort(p + 1, p + n + 1);
		//sort so we can binary search
		rang = n + 2 * k;
		//range
		multiset<int> tr;
		for(int i = 1; i <= rang; i++)c[i] = 0;		
		for(int i = 1; i <= n; i++){
			tr.insert(p[i]);
		}
		for(int i = 1; i <= k; i++){
			int now = get(a[i].r) - get(a[i].l - 1);
			if(now >= a[i].val)continue;
			a[i].val -= now;
			//region already satisfied
			auto it = tr.upper_bound(a[i].r);
			it--;
			while(a[i].val){
				//take this tree
				a[i].val--;
				ans--;
				add(*it, 1);
				tr.erase(it--);
				//first erase then --
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
## Result
[Result](https://www.luogu.com.cn/record/195884640)

这场银组真的好简单，三道题我都想出解了~~虽然两道都没过~~及格线还这么低。

---

## 作者：Your_Name (赞：5)

## 题解
这是 [超速检测](https://www.luogu.com.cn/problem/P11232) 的加强版。

沿用那道题的贪心，先按右端点排序，然后每次尽量选右边的树种即可。

直接离散化然后用线段树维护哪里可以种，二分种到哪棵，然后区间覆盖，注意细节就行。
## AC_Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5;
int T, n, m, ans, x[N], l, r, t;
struct node2
{
	int l, r, q, ti;
};
vector<node2> v;
vector<int> k;
struct TR
{
	int l, r, tag, sum;
} tr[N * 4];
void pushup(int k)
{
	int lc = k * 2, rc = k * 2 + 1;
	tr[k].sum = tr[lc].sum + tr[rc].sum;
}//算里面有多少棵树还每种。
void build(int k, int l, int r)
{
	tr[k].l = l, tr[k].r = r, tr[k].tag = -1;
	if (l == r){
		tr[k].sum = 0;
		return;
	}
	int mid = l + r >> 1, lc = k * 2, rc = k * 2 + 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(k);
}
void lazy(int k, int x){
	tr[k].tag = x;
	tr[k].sum = x * (tr[k].r - tr[k].l + 1);
}
void pushdown(int k){
	int lc = k * 2, rc = k * 2 + 1;
	if(tr[k].tag == -1)return;
	lazy(lc, tr[k].tag);
	lazy(rc, tr[k].tag);
}
void co(int k, int l, int r, int x){
	if(tr[k].l >= l && tr[k].r <= r){
		lazy(k, x);
		return;
	}
	pushdown(k);
	int mid = tr[k].l + tr[k].r >> 1, lc = k * 2, rc = k * 2 + 1;
	if(r <= mid){
		co(lc, l, r, x);
	}else if(l > mid){
		co(rc, l, r, x);
	}else{
		co(lc, l, mid, x);
		co(rc, mid + 1, r, x);
	}
	pushup(k);
}//区间覆盖
int askpo(int k, int pos)
{
	if (tr[k].l == tr[k].r)
	{
		return tr[k].sum;
	}
	pushdown(k);
	int mid = tr[k].l + tr[k].r >> 1, lc = k * 2, rc = k * 2 + 1;
	if (pos <= mid)
		return askpo(lc, pos);
	else
		return askpo(rc, pos);
}//单点查询
void modi(int k, int pos, int x)
{
	if (tr[k].l == tr[k].r)
	{
		tr[k].sum += x;
		return;
	}
	pushdown(k);
	int mid = tr[k].l + tr[k].r >> 1, lc = k * 2, rc = k * 2 + 1;
	if (pos <= mid)
		modi(lc, pos, x);
	else
		modi(rc, pos, x);
	pushup(k);
}//单点修改
int ask(int k, int l, int r)
{
	if (tr[k].l >= l && tr[k].r <= r)
		return tr[k].sum;
	pushdown(k);
	int mid = tr[k].l + tr[k].r >> 1, lc = k * 2, rc = k * 2 + 1;
	if (r <= mid)
		return ask(lc, l, r);
	else if (l > mid)
		return ask(rc, l, r);
	else
		return ask(lc, l, mid) + ask(rc, mid + 1, r);
}//区间查询
bool cmp(node2 a, node2 b)
{
	return a.r < b.r || (a.r == b.r && a.l < b.l);
}
int find(int x){
	return lower_bound(k.begin(), k.end(), x) - k.begin() + 1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--)
	{
		k.clear();
		v.clear();
		cin >> n >> m;
		for(int i = 1; i <= n; i ++){
			cin >> x[i];
			k.push_back(x[i]);
		}
		for(int i = 1; i <= m; i ++){
			cin >> l >> r >> t;
			k.push_back(l);
			k.push_back(r);
			v.push_back({l, r, t, 0});
		}
		sort(k.begin(), k.end());
		k.erase(unique(k.begin(), k.end()), k.end());
		build(1, 1, N);
		for(int i = 1; i <= n; i ++){
			x[i] = find(x[i]);
			modi(1, x[i], 1);
		}
		for (int i = 0; i < m; i++)
		{
			v[i].l = find(v[i].l);
			v[i].r = find(v[i].r);
			v[i].ti = ask(1, v[i].l, v[i].r);
		}
		sort(v.begin(), v.end(), cmp);
		for (int i = 0; i < v.size(); i++)
		{
			int l = v[i].l, r = v[i].r, mid;
			v[i].q -= v[i].ti - ask(1, l, r);//减掉已经种了的
			if (v[i].q <= 0)continue;
			int res;
			while (l <= r)
			{
				mid = l + r >> 1;
				if (ask(1, mid, v[i].r) >= v[i].q){
					res = mid;
					l = mid + 1;
				}else r = mid - 1;
			}//找到第一个小于要种的棵树的地方。
			v[i].q -= ask(1, res, v[i].r);
			co(1, res, v[i].r, 0);
			if(v[i].q){
				r --;
				while(v[i].q && r >= v[i].l){
					if(askpo(1, r))modi(1, r, max(-v[i].q, -askpo(1, r)));
					r --;
				}
			}//防止有多个树在一个地方，暴力往前删。
		}
		cout << tr[1].sum << '\n';//直接输出剩下的树。
	}
	return 0;
}
```
 _完结撒花。_

---

## 作者：Mr_Az (赞：5)

# P11453 [USACO24DEC] Deforestation S

### Algorithm:

贪心。

### Solution:

思路有点像 P11232 [CSP-S 2024] 超速检测。

我们将每一个限制按照右端点递增排序后，我们贪心地去选择留下哪些树。很明显留下最右边的一段树是最优的，因为这里的一棵树能贡献到的区间比左边的区间要更多。

所以做法就是将所有区间排序后，贪心地去选择最右边的一段直到满足这一个限制。

**细节**

1. 为了时间复杂度的正确性，需要二分选择最右边一段的左端点。也可以直接在线段树上二分。
2. 也可以直接用平板电视，每次删除排名在 $[\operatorname{rnk}(l),\operatorname{rnk}(r)]$ 的数直到满足限制。
3. 绝对不会告诉你直接 for 过去也行。

---

## 作者：vanueber (赞：4)

一道十分类似 [P11232 [CSP-S 2024] 超速检测](https://www.luogu.com.cn/problem/P11232) 的题，其他题解做法已经讲的很明白了，这里给出一种差分约束的解法。

# 题目分析

观察到坐标很大，先进行离散化。

考虑建立一个前缀和数组 $pre$，要最小化 $pre_n$，那么跑最长路。

于是对于一条限制 $i$，先求出 $l_i,r_i$ 偏移后的下标 $l_i',r_i'$，可以看做一个点的编号。

那么应该满足的不等关系为：
$$
r_i'-l_i' \geq t_i
$$

于是建一条从 $l_i'$ 到 $r_i'$，边权为 $t_i$ 的边。

同时，为了满足解是满足条件的，还要加上一些附加限制：

$$
0 \leq pre_i-pre_{i-1} \leq 1
$$

最后跑一遍 spfa，$n-dis_n$ 就是最终答案。


# 代码


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int maxn=3e5+10;
int T,n,k,pos[maxn],tmp[maxn];
struct node
{
    int v,w;
};
vector<node> G[maxn];
int dis[maxn],inq[maxn];
void spfa(int s)//差分约束spfa
{
    memset(inq,0,sizeof inq);
    fill(dis,dis+n+1,-1e18);
    queue<int> Q;
    Q.push(s);
    dis[s]=0,inq[s]=1;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop(),inq[u]=0;
        for(node &k:G[u])
        {
            int v=k.v,w=k.w;
            if(dis[v]<dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!inq[v])
                {
                    Q.push(v),inq[v]=1;
                }
            }
        }
    }
}

signed main()
{
    #ifndef ONLINE_JUDGE
    // freopen("in.txt","r",stdin);
    #endif
    T=read();
    while(T--)
    {
        memset(pos,0,sizeof pos);
        memset(tmp,0,sizeof tmp);//多测清空
        n=read(),k=read();
        for(int i=1;i<=n;++i)
        {
            tmp[i]=pos[i]=read();
        }
        sort(tmp+1,tmp+n+1);
        for(int i=1;i<=n;++i)
        {
            pos[i]=lower_bound(tmp+1,tmp+n+1,pos[i])-tmp;
        }
        for(int i=1,l,r,t;i<=k;++i)
        {
            l=read(),r=read(),t=read();
            l=lower_bound(tmp+1,tmp+n+1,l)-tmp,r=upper_bound(tmp+1,tmp+n+1,r)-tmp-1;
            G[l-1].push_back({r,t});//注意在前缀和数组下表表示中，l要-1
        }
        for(int i=1;i<=n;++i)
        {
            G[i-1].push_back({i,0});
            G[i].push_back({i-1,-1});
        }//附加条件，见上
        spfa(0);
        cout<<n-dis[n]<<endl;
        for(int i=0;i<=n;++i) G[i].clear();
    }
    return 0;
}
```

---

## 作者：silly_mouse (赞：2)

## 思路

将所有数进行离散化，很显然一道差分约束模板。$s_i$ 表示有多少个 $1-i$ 的数，题目给了 $k$ 个约束，即：

$$
s_{r_i}-s_{{l_i}-1} \ge t_i
$$

将 $l_i-1$ 与 $r_i$ 连一条边权为 $t_i$ 的边，跑个最长路。但是关于 SPFA，它四了。

---

没有关系，加一个优化即可卡过此题。

最后附上丑陋的代码。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<deque>
#define int long long
using namespace std;
const int N=300005,INF=1145141919;
int T,n,k,u,v,w,st,en,d[N],x[N];
bool vis[N];
deque<int> q;
vector<pair<int,int> > t[N];
void SLF(){
	if(q.size()&&d[q.front()]<d[q.back()])swap(q.front(),q.back());
}
void SPFA(int st){
	memset(d,-0x3f,sizeof(d));
	memset(vis,false,sizeof(vis));
	d[st]=0;
	q.push_back(st);
	while(q.size()){
		int x=q.front();
		q.pop_front();
		vis[x]=false;SLF();
		for(int i=0;i<t[x].size();i++){
			int y=t[x][i].first,w=t[x][i].second;
			if(d[y]<d[x]+w){
				d[y]=d[x]+w;
				if(!vis[y]){
					vis[y]=true;
					q.push_back(y);
					SLF();
				}
			}
		}
	}
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		st=INF;en=-INF;
		for(int i=1;i<=n;i++)cin>>x[i];
		for(int i=0;i<=n+1;i++)t[i].clear();
		sort(x+1,x+n+1);
		while(k--){
			cin>>u>>v>>w;
			u=lower_bound(x+1,x+n+1,u)-x;
			v=upper_bound(x+1,x+n+1,v)-x-1;
			st=min(st,u-1);en=max(en,v);
			t[u-1].push_back(make_pair(v,w));
		}
		for(int i=st+1;i<=en;i++){
			t[i].push_back(make_pair(i-1,-1));
			t[i-1].push_back(make_pair(i,0));
		}
		SPFA(st);
		cout<<n-d[en]<<"\n";
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：2)

## 题意回顾

数轴上有 $ n $ 个给定的整点，请判断你最多可以删除多少个结点，还能满足 $ k $ 条限制：

* 在 $ [l_i,r_i] $ 范围内存在至少 $ t_i $ 个未被删除的整点。

多测，$ 1 \le \sum k,\sum n \le 3 \times 10^5 $。

## 知识点及题目评析

* 【3】贪心法
* 【6】线段树 / 树状数组

## 分析

正难则反，考虑将问题转化为最少保留几个整点。

每个限制都有左右端点的要求，不太好直接贪心，我们考虑按照右端点从左到右排序，那么对于一个区间如果仍未符合要求，我们显然选取尽可能靠右的给定整点保留是更优的，因为这些整点一定满足之后所有区间的右端点范围要求，且如果不是最靠右的给定整点满足其他左端点范围要求的情况下，这些区间的左端点范围要求一定能被最靠右的给定整点满足。

因此，我们得到贪心策略：对于这些区间，我们不断地去保留最靠右的未被保留的范围内给定整点，直到区间满足要求。离散化所有给定整点和区间范围的相对位置后，用线段树维护区间选取个数及最靠右的未被选取的整点即可。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
int T;
int n, k;
int x[N];
struct node {
	int l, r, t;
	bool operator<(node p1) {
		return r < p1.r;
	}
} a[N];
inline void read(int &Rd) {
	Rd = 0;
	int Fh = 1;
	char ch = '#';
	while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if(ch == '-') Fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') Rd = (Rd << 1) + (Rd << 3) + ch - '0', ch = getchar();
	Rd *= Fh;
}
inline void write(long long Rd) {
	if(Rd == 0) {
		putchar('0');
		return;
	} 
	char wri[25];
	int lt = 0;
	while(Rd) {
		wri[++lt] = Rd % 10;
		Rd /= 10;
	}
	while(lt) {
		putchar(wri[lt--] + '0');
	}
}
int Find(int X) {
	if(x[n] < X) return n + 1;
	int l, r, mid;
	l = 0, r = n;
	while(l + 1 < r) {
		mid = (l + r) >> 1;
		if(x[mid] >= X) r = mid;
		else l = mid;
	}
	return r;
}
struct info {
	int sum, rit;//count point saveed, right point cutted
	info operator+(info p1) {
		return (info){sum + p1.sum, max(rit, p1.rit)};
	}
} d[N * 4];
void build(int s, int t, int p) {
	if(s == t) {
		d[p] = (info){0, s};
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, p * 2);
	build(mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
void update(int x, int s, int t, int p) {
	if(s == t) {
		d[p] = (info){1, 0};
		return;
	}
	int mid = (s + t) >> 1;
	if(x <= mid) update(x, s, mid, p * 2);
	else update(x, mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
info query(int l, int r, int s, int t, int p) {
	if(l <= s && t <= r) return d[p];
	int mid = (s + t) >> 1;
	info tmp = (info){0, 0};
	if(l <= mid) tmp = tmp + query(l, r, s, mid, p * 2);
	if(mid < r) tmp = tmp + query(l, r, mid + 1, t, p * 2 + 1);
	return tmp;
}
int main() {
	read(T);
	for(int ti = 1; ti <= T; ti++) {
		read(n), read(k);
		for(int i = 1; i <= n; i++) read(x[i]);
		sort(x + 1, x + n + 1);
		for(int i = 1; i <= k; i++) read(a[i].l), read(a[i].r), read(a[i].t);
		sort(a + 1, a + k + 1);
		for(int i = 1; i <= k; i++) {
			a[i].l = Find(a[i].l);
			a[i].r = Find(a[i].r + 1) - 1;
			if(a[i].t == 0) a[i].l = a[i].r = 1, a[i].t = 0;
		}
		build(1, n, 1);
		for(int i = 1; i <= k; i++) {
			while(true) {
				info now = query(a[i].l, a[i].r, 1, n, 1);
				if(now.sum >= a[i].t) break;
				update(now.rit, 1, n, 1);
			}
		}
		write(n - query(1, n, 1, n, 1).sum);
		puts("");
	}
	return 0;
}
```

---

## 作者：违规用户名720023 (赞：2)

[P11453](https://www.luogu.com.cn/problem/P11453)

# P11453 Deforestation S  (砍树)

## 1.Problem Statement （题目描述）

有 $n$ 个在数轴上的点，每个点有个在 $-10^9$ 和 $10^9$ 之间的坐标。

另有 $k$ 个区间，要求对于区间 $l_i$ 到 $r_i$，它至少要包含 $t_i$ 个点。

现在你可以删除一些点，使得剩下的这些点仍然满足这些限制。求能删的最大点数。

## 2.分析

坐标到了 $10^9$，肯定离散化。

前两个测试点是好做的。枚举每个点删还是不删，复杂度指数级。

对于第三个到第五个点，$n, k \leq 1000$，可以贪心。发现左侧的点对后面区间的贡献一定小于右侧的。所以删除每个区间的左侧的点一定不差于删右边的。每次暴力扫一个区间，计算要删几个，然后从左到右能删就删。

第六个到第七个点，同 P11232 超速检测，不再赘述，具体看 P11232 题解。

想拿到满分，考虑优化上面第三个到第五个点的贪心。可以在离散化之后使用二分查找满足区间范围的树的数量，不用暴力做了。后面使用 `priority_queue` 优化查找删除的过程。每次先计算包含它的区间里面最靠左的。如果那个区间都允许删除这个点，那么一定可删除，就删，删到那个区间不能删除为止。这里要注意，一定要弹出前面已经做完的区间。

## 3.Code:
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <cstdio>
#define int __int128
#define rd() read128()
#define pr(a) print128(a)
#define pc(b) putchar(b)
#define pel(c) pr(c), pc('\n')
#define psp(d) pr(d), pc(' ')
using namespace std;
int read128()
{
	int ttpttp = 0, flgflg = 1;
	char chrchr = getchar();
	if(chrchr == '-') flgflg = -1;
	while((chrchr < '0' || chrchr > '9') && chrchr != '-') chrchr = getchar();
	if(chrchr == '-') flgflg = -1, chrchr = getchar();
	while(chrchr >= '0' && chrchr <= '9') ttpttp = ttpttp * 10 + chrchr - '0', chrchr = getchar();
	return ttpttp * flgflg;
}
void print128(int ttpttp)
{
	char char_inserted_list[38];
	if(ttpttp < 0) putchar('-'), ttpttp *= -1;
	int iiiiii = 0;
	while(ttpttp > 0)
	{
		char_inserted_list[++iiiiii] = (char)(ttpttp % 10 + '0');
		ttpttp /= 10;
	}
    if(iiiiii == 0) putchar('0');
    else
    {
    	for(int i = iiiiii; i >= 1; i--) putchar(char_inserted_list[i]);
	}
}//快读
int lsh[500010];
signed main()
{
	int T = rd();
	while(T--)
	{
		int n = rd(), k = rd();
		memset(lsh, 0, sizeof(lsh));
		vector<tuple<int, int, int, int> > vec;//不知道tuple是什么的可以学习一下
		for(int i = 1; i <= n; i++)
		{
			int t = rd();
			lsh[i] = t;
			vec.push_back({t, 1, 0, 0});
		}
		sort(lsh + 1, lsh + n + 1);
		for(int i = 1; i <= k; i++)
		{
			int l = rd(), r = rd(), t = rd();
			int tp = upper_bound(lsh + 1, lsh + n + 1, r) - lower_bound(lsh + 1, lsh + n + 1, l) - t;//计算可删除数量
			//pel(tp);
			vec.push_back({l, 0, r, tp});
		}
		sort(vec.begin(), vec.end());
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
		int ans = 0;
		for(int i = 0; i < n + k; i++)
		{
			int l;
			bool typ;
			int r, p;
			tie(l, typ, r, p) = vec[i];
			if(typ == 0) pq.push(make_pair(ans + p, r));//存入删除“方案”
			else
			{
				//psp(pq.size());
				if(!pq.empty()) for(pair<int, int> pp = pq.top(); !pq.empty() && pp.second < l; pp = pq.top()) pq.pop();//弹出做完的区间
				//psp(i);
				//psp(pq.size());
				if(pq.empty() || pq.top().first != ans) ans++;//遇到树才更新答案，前面的只是方案
				//pel(ans);
			}
		}
		pel(ans);
	}
	return 0;
}//没有挖坑
```

## 4.后记

  其实还有一种做法，离散化之后前缀和，然后就转变为了一个差分约束问题。记 $r_i$ 离散化之后的点为 $R_i$， $l_i$ 离散化之后的点为 $L_i$。`s[R[i]] - s[L[i - 1]] >= t` 并且为了使得答案最小，要求两个点之间最多有一棵树，即 `s[v] - s[v - 1] <= 1`（$v$ 是任意一点）。可以用差分约束卡过。

---

## 作者：Jorisy (赞：2)

CSP-S T2 加强版。

沿用贪心思路，按右端点排序，取后缀。

赛时上了线段树，写烦了，在这里膜拜 KE 的简洁写法。

我们可以用栈记录未选择的区间，要看区间内已经选了多少数直接在栈上二分即可。
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;

struct node{
    int l,r,t;
}seg[N];
pair<int,int>b[N];
int n,k,m,a[N],sum[N],ans,st[N],tl,pre[N];

bool cmp(node x,node y)
{
    return x.r!=y.r?x.r<y.r:x.l<y.l;
}

int bis(int x)
{
    int l=0,r=tl;
    while(l+1<r)
    {
        int mid=l+r>>1;
        if(x<=st[mid]) r=mid;
        else l=mid;
    }
    return r;
}

void sol()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    a[0]=-1e9-1;
    m=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==a[i-1]) b[m].second++;
        else b[++m]={a[i],1};
    }
    for(int i=1;i<=m;i++)
    {
        sum[i]=sum[i-1]+b[i].second;
    }
    for(int i=1;i<=k;i++)
    {
        int l,r,t;
        scanf("%d%d%d",&l,&r,&t);
        l=lower_bound(b+1,b+m+1,make_pair(l,1))-b;
        r=lower_bound(b+1,b+m+1,make_pair(r+1,1))-b-1;
        seg[i]={l,r,t};
    }
    sort(seg+1,seg+k+1,cmp);
    ans=tl=0;
    for(int i=1;i<=k;i++)
    {
        for(int j=seg[i-1].r+1;j<=seg[i].r;j++)
        {
            st[++tl]=j;
            pre[tl]=pre[tl-1]+b[j].second;
        }
        int p=bis(seg[i].l),t=seg[i].t-(sum[seg[i].r]-sum[seg[i].l-1]-(pre[tl]-pre[p-1]));
        if(t<=0) continue;
        ans+=t;
        tl-=t;
    }
    printf("%d\n",n-ans);
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--) sol();
    return 0;
}
```

---

## 作者：Modulus998244353 (赞：2)

**解题思路**

---

考虑贪心，每个保留的树要发挥最大作用，即为每个保留的树在尽可能多的区间。

则我们可以讲每个区间按照右端点排序，则如果要让每个被保留的树有最大的贡献，即使让这颗树的位置尽量往后排，这样被后面的区间包含的可能更大。

用一个树状数组维护一下每棵树的状态即可。

**代码**

---

```C++
struct Binary_Tree{
    int bit[Maxn];
    inline void init(){
        for(int i=0;i<Maxn;i++) bit[i]=0;
    }
    inline void chnge(int i,int val){
        while(i<Maxn) bit[i]+=val,i+=lowbit(i);
    }
    inline int sum(int i){
        int res=0;
        while(i) res+=bit[i],i-=lowbit(i);
        return res;
    }
    inline int query(int l,int r){
        int res=sum(r)-sum(l-1);
        return res;
    }
  	// findk 是 n 颗树中，从左到右第 k 个被保留的树。
    inline int findk(int n,int k){
        int pos=0,now=1<<(__lg(n));
        while(now>0){
            int nxt=pos+now;
            if(nxt<=n && bit[nxt]<k){
                k-=bit[nxt];pos=nxt;
            }
            now>>=1;
        }
        return pos+1;
    }
}T;
struct Node{
    int l,r,t;
} ast[Maxm];
inline bool cmp(Node x,Node y){
    return x.r<y.r;
}
int x[Maxn];
inline void init1(int n,int k){
    for(int i=0;i<Maxn;i++) x[i]=0;
    for(int i=0;i<Maxm;i++) ast[i].l=ast[i].r=ast[i].t=0;
}
inline void solve(){
    int n,k;
    scanf("%lld%lld",&n,&k);
    init1(n,k);
    T.init();
    for(int i=0;i<n;i++) scanf("%lld",&x[i]);
    for(int i=1;i<=n;i++) T.chnge(i,1); // 每棵树在初始状态为被砍掉，然后对每个区间考虑，要加多少棵树。（1为被砍掉，0为被保留）
    for(int i=0;i<k;i++) scanf("%lld%lld%lld",&ast[i].l,&ast[i].r,&ast[i].t);
    sort(x,x+n);
    sort(ast,ast+k,cmp); // 按右端点排序
    // for(int i=0;i<k;i++) printf("%lld %lld %lld\n",ast[i].l,ast[i].r,ast[i].t);
    int all_need=0;
    int sum=0;
    for(auto [l,r,t]:ast){
        int L=lower_bound(x,x+n,l)-x,R=upper_bound(x,x+n,r)-x-1; // 找在 [l,r] 中最左边的树的位置和最右边的位置。（注：这里不考虑有没有被砍掉）
        if(L>R || L<0 || R<0 || L>=n || R>=n) continue;
        int now_need=t-(R-L+1)+T.query(L+1,R+1); // 计算在 [l,r] 中有多少个被保留的树，now_need 为现在需要几棵树。（第一处）
        if(now_need<=0) continue;
        while(now_need){
            now_need--;all_need++;
            int loc=T.findk(n,T.sum(R+1)); // loc代表现在要加的树的位置。（第二处）
            T.chnge(loc,-1); // 加树 从最右边开始。
        }
    }
  	// 这里在对树状数组操作的时候要对坐标+1，由于读入时是从0开始，但树状数组要从1开始。（这两处在前面标上了）
    int ans=n-all_need;
    printf("%lld\n",ans);
}
```

最后，**多测要清空！！** **多测要清空！！！** **多测要清空！！！** **多测要清空！！！** **多测要清空！！！**。

原因是驻波在写的时候因为没清空完整导致调了2h。暨！

---

## 作者：Roy_2010 (赞：1)

# [USACO24DEC] Deforestation S 题解
提供一种特殊的方法，见实现部分。
## 思路
我们先将问题简单化，即离散化一下，缩小值域。\
有个明显的贪心，和大部分人的一样，先按右端点排序，然后依次满足区间内的树的个数，如果不满足就从右边开始填。
## 实现
我们先考虑暴力，直接填充，那么复杂度不用算也知道无法通过。\
但事实上我们只需要维护两个操作就可以了。\
首先，我们要维护区间的之前种的树的个数。\
其次，我们需要维护对于每个点之前的离他最近的未种植的树。
### 操作一
我们可以用树状数组解决。
### 操作二
有人说了也可以用树状数组维护啊，但这样做似乎，也没什么问题。但我考场上没有想到。所以我们考虑另一种维护方法。\
我们观察到因为我们按右边排序，往左填，不需要维护所有地方的操作二，所以我们可以引入一个链头数组，记录的是以其为右端点的连通块的左端点，每次跳链去找就可以了。而每次填完后都将右端点的链头赋值为我填的当前位置即可。\
为什么只需要赋值右端点，因为通过这么跳到的位置一定是一个连通块的右端点或空位，而既然每一个填的时候都是这样可行，那么对于所有的也就可行（一个不够严谨的证明）。\
那么为什么这样可以保证复杂度呢？如果每一次我跳链都跳满不是跟暴力一样吗？但事实上是不会的，因为每次我如果跳了多次链，那么最终这些链会被我压缩成为一个链，我多跳的链数等于我压缩掉的链数，从右端点直接跳到当前位置（类似路径压缩），又因为链的数量不会超过树的数目，所以总复杂度是 $O(N)$ 的。均摊是 $O(1)$ 的。\
因为以上内容大部分比较抽象，可以结合代码看看。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;

int T;

int n,m;

struct BIT{
	int Tree[100050];
	void Build(){memset(Tree,0,sizeof(Tree));}
	int Lowbit(int x){return x&(-x);}
	void Update(int x){for(int i=x;i<=n;i+=Lowbit(i)){++Tree[i];}}
	int Query(int x){int sum=0;for(int i=x;i;i-=Lowbit(i)){sum+=Tree[i];}return sum;}
}tr;

int Tree[100050];
int pre[100050];

struct Node{
	int l,r,k;
	bool operator <(const Node &b){
		return this->r<b.r;
	}
}q[100050];

int efl(int x){
	int l=1,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(Tree[mid]<x){
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	return l;
}
int efr(int x){
	int l=1,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(Tree[mid]>x){
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return r;
}

void Work(){
	tr.Build();
	memset(pre,0,sizeof(pre));
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>Tree[i];
	} 
	sort(Tree+1,Tree+n+1);
	for(int i=1;i<=m;++i){
		cin>>q[i].l>>q[i].r>>q[i].k;
	}
	sort(q+1,q+m+1);
	for(int i=1;i<=m;++i){
		int l=efl(q[i].l),r=efr(q[i].r);
		if(tr.Query(r)-tr.Query(l-1)<q[i].k){
			int lft=q[i].k-tr.Query(r)+tr.Query(l-1);
			int p=r;
			if(lft){
				if(pre[p]){	
					while(pre[p]){
						p=pre[p]-1;
					}
				}	
				tr.Update(p);
				--lft;
			}
			while(lft){
				--p;
				if(pre[p]){	
					while(pre[p]){
						p=pre[p]-1;
					}
				}
				tr.Update(p);
				--lft;
			}
			pre[r]=p;
		}
	}
	cout<<n-tr.Query(n)<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	for(int i=1;i<=T;++i){
		Work();
	} 
	return 0;
} 
/*
1
14 5
1 10000 10001 10002 10003 10004 10005 10006 10007 10008 100009 100003 100007 100008
-1000 100000 1
10003 10005 2
10005 10009 3
10000 100009 7
10004 10008 5
*/
```
最后由于树状数组的小常数以及跳链的优异复杂度，跑到了最优解的第一页（目前）。\
总时间复杂度是 $O(n\log n)$ 的。

---

## 作者：hyk2019 (赞：1)

简明题意：

已知数轴上有 $N$ 个位置，每个位置上有一个点，有 $K$ 个关于区间 $[l_i,r_i]$ 上至少需要有 $t_i$ 个点的限制，求能够删去的点数的最大值。

可以把上面的题意稍微转换一下，改成“初始这些位置上都没有点，要在每个位置上放置点，使得这些点满足要求，并且点的数目最少”。那么“能够删去的点数的最大值” $=N-$ “最少需要放置的点的数目”。

**特殊性质**：$a_i=1$。

就是每个区间内至少要有一个点。回忆 [CSP-S 2024 超速检测](/problem/P11232)：

> 其次，为了节能，部门想关闭一部分测速仪。然而，他们**不希望漏掉超速的车**，也就是说，当 $n$ 辆车里的某辆车在所有测速仪都开启时被判定为超速，他们希望在关闭一部分测速仪以后**它依然被判定为超速**。上司还想知道在这样的条件下最多可以关闭多少测速仪。

[题解](li681r1a)：

> 我们可以**将这段区间看成一个限定条件**，即我们在所选出来的测速仪中，对于每一个限定条件 $l_i,r_i$，**至少有一个**测速仪（假设这个测速仪的位置为 $x$）满足 $l_i\le x\le r_i$，并且我们希望选出来的测速仪尽可能少。

发现其实 $t_i=1$ 就是去掉了加速度的“超速检测”。按照这一题的思路解题即可。

现在考虑**正解**。

我们在“超速检测”中，将所有的区间按照**右端点从左到右、左端点从左到右排序**，然后按顺序遍历每一个区间，碰到一个还没有被测速仪检测到的区间，就把这个区间里**最右侧**的测速仪开启。

回到本题，我们也可以将所有的区间按照右端点从左到右、左端点从左到右排序，然后按顺序遍历每一个区间，碰到一个内部**不满** $t_i$ 个点的区间，就**从右到左**逐个向区间内还没有添加点的位置添加点，直到区间内一共有 $t_i$ 个点。

上面的操作涉及到对一个区间内的所有点都设置为 $1$ 的操作，可以用线段树解决。确定填充区间时，可以二分 $x_i$ 使得 $[l_i,x_i]$ 内已放置点的个数与 $r_i-x_i$ 的和等于 $t_i$，然后将 $[x_i+1,r_i]$ 都设置为 $1$ 即可。

时间复杂度 $O(N\log^2N\times T)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, N, K, a[100005] = {-2147483647};
struct Sec {
  int l, r, c;
  bool operator<(Sec b) const {
    if(r ^ b.r)
      return r < b.r;
    if(l ^ b.l)
      return l < b.l;
    return c < b.c;
  }
} s[100005];
map<int, int> mp;
struct Node {
  int L, R, l, r, v, t;
  void tag(int x) {
    v = x * (R - L + 1), t = x;
  }
} ns[200005];
int cnt = 0;
void pushdown(int u) {
  if(ns[u].t) {
    ns[ns[u].l].tag(ns[u].t);
    ns[ns[u].r].tag(ns[u].t);
    ns[u].t = 0;
  }
}
void pushup(int u) {
  ns[u].v = ns[ns[u].l].v + ns[ns[u].r].v;
}
void build(int L, int R, int u) {
  ns[u] = {L, R, 0, 0, 0, 0};
  if(L == R)
    return;
  int M = (L + R) / 2;
  build(L, M, ns[u].l = ++cnt);
  build(M + 1, R, ns[u].r = ++cnt);
}
void modify(int L, int R, int x, int u) {
  if(L <= ns[u].L && ns[u].R <= R) {
    ns[u].tag(x);
    return;
  }
  pushdown(u);
  int M = (ns[u].L + ns[u].R) / 2;
  if(L <= M)
    modify(L, R, x, ns[u].l);
  if(R > M)
    modify(L, R, x, ns[u].r);
  pushup(u);
}
int query(int L, int R, int u) {
  if(L <= ns[u].L && ns[u].R <= R)
    return ns[u].v;
  pushdown(u);
  int M = (ns[u].L + ns[u].R) / 2, ans = 0;
  if(L <= M)
    ans += query(L, R, ns[u].l);
  if(R > M)
    ans += query(L, R, ns[u].r);
  return ans;
}
int main() {
  scanf("%d", &T);
  while(T --) {
    memset(ns, 0, sizeof ns);
    cnt = 1;
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; i ++)
      scanf("%d", a + i);
    sort(a + 1, a + N + 1);
    build(1, N, 1);
    mp.clear();
    for(int i = 1; i <= N; i ++)
      mp[a[i]] = i;
    for(int i = 1; i <= K; i ++) {
      scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].c);
      s[i].l = lower_bound(a + 1, a + N + 1, s[i].l) - a;
      s[i].r = upper_bound(a + 1, a + N + 1, s[i].r) - a - 1;
      if(s[i].r == 0)
        K --, i --;
    }
    sort(s + 1, s + K + 1);
    for(int i = 1; i <= K; i ++) {
      int l = s[i].l, r = s[i].r;
      if(query(l, r, 1) >= s[i].c)
        continue;
      if(r - l + 1 == s[i].c) {
        modify(l, r, 1, 1);
        continue;
      }
      int lt = l, rt = r - 1;
      while(lt < rt) {
        int mt = (lt + rt) / 2, at = query(l, mt, 1);
        if(at + (r - mt) > s[i].c)
          lt = mt + 1;
        else
          rt = mt;
      }
      modify(lt + 1, r, 1, 1);
    }
    printf("%d\n", N - query(1, N, 1));
  }
  return 0;
}
```

---

## 作者：Milky_Cat (赞：1)

这题貌似有一大堆原题。

显然的贪心策略是，按右端点从小到大排，尽量往右种。

离散化一下，用线段树维护需要处理的位置种或不种就好了。

```cpp
#include<bits/stdc++.h>
#define mxn 300005
using namespace std;
int T, n, m, pos[mxn];
struct node{
	int l, r, x;
}a[mxn];
struct nnode{
	int l, r, vl, lzy;
}tr[mxn << 2 | 3];
int ls(int u){
	return (u << 1);
}
int rs(int u){
	return (u << 1 | 1);
}
int md(int l, int r){
	return (l + r) >> 1;
}
void pup(int u){
	tr[u].vl = tr[ls(u)].vl + tr[rs(u)].vl;
}
void build(int u, int l, int r){
	tr[u].l = l;
	tr[u].r = r;
	tr[u].vl = 0;
    tr[u].lzy = 0;
	if (l == r)
		return;
	int mid = md(l, r);
	build(ls(u), l, mid);
	build(rs(u), mid + 1, r);
	pup(u);
}
void pdn(int u, int l, int r){
	int mid = md(l, r);
	tr[ls(u)].vl = mid - l + 1;
	tr[rs(u)].vl = r - mid;
	tr[ls(u)].lzy = tr[rs(u)].lzy = 1;
	tr[u].lzy = 0;
}
bool inr(int l, int r, int ql, int qr){
	return (ql <= l && qr >= r);
}
bool otr(int l, int r, int ql, int qr){
	return (ql > r || qr < l);
}
void upd(int u, int ql, int qr, int &x){
	if (!x)
		return;
	if (inr(tr[u].l, tr[u].r, ql, qr)){
		if (tr[u].r - tr[u].l + 1 - tr[u].vl <= x){
			x -= (tr[u].r - tr[u].l + 1 - tr[u].vl);
			tr[u].vl = tr[u].r - tr[u].l + 1;
			tr[u].lzy = 1;
			return;
		}
	}
	if (otr(tr[u].l, tr[u].r, ql, qr))
		return;
	if (tr[u].lzy)
		pdn(u, tr[u].l, tr[u].r);
    upd(rs(u), ql, qr, x);
	upd(ls(u), ql, qr, x);
	pup(u);
}
int qry(int u, int ql, int qr){
	int res = 0;
	if (inr(tr[u].l, tr[u].r, ql, qr))
		return tr[u].vl;
	if (otr(tr[u].l, tr[u].r, ql, qr))
		return 0;
    if (tr[u].lzy)
	    pdn(u, tr[u].l, tr[u].r);
	res += (qry(ls(u), ql, qr) + qry(rs(u), ql, qr));
	return res;
}
int fdle(int x){
    int l = 1, r = n, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (pos[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
int fdri(int x){
    int l = 1, r = n, mid;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (pos[mid] > x)
            r = mid - 1;
        else
            l = mid;
    }
    return l;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			cin >> pos[i];
        sort(pos + 1, pos + n + 1);
		for (int i = 1; i <= m; i++)
			cin >> a[i].l >> a[i].r >> a[i].x;
		sort (a + 1, a + 1 + m, [](node u, node v){return u.r < v.r;});
		build(1, 1, n);
		int cnt = 0;
		for (int i = 1; i <= m; i++){
			int rl = fdle(a[i].l), rr = fdri(a[i].r);
			if (rr >= rl){
				int js = qry(1, rl, rr);
				if (js < a[i].x){
					int qwq = a[i].x - js;
					cnt += qwq;
					upd(1, rl, rr, qwq);
				}
			}
		}
		cout << n - cnt << "\n";
	}
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：1)

首先发现这个问题可以贪心地从左往右删，因为如果在这个位置删满足条件，那么在右边删可能会浪费条件导致不优，但一定不会因为改到右边而多删。

所以维护该点目前被多少区间覆盖、这些区间分别剩余多少可以删除，这个可以线段树做，只要维护区间 $-1$ 和单点赋值（加入时赋值为初始剩余量，退出和初始时赋值为 `inf`）即可。

此外加一个优先队列来维护出入线段树的时机（包含的区间按右端点排序），然后只需要预处理按区间左端点排序即可。

时间复杂度~~大常数~~ $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,x[N],k,tmp[N<<3],cnt,sum[N<<3],sum2[N<<3];
struct node{
    int l,r,t,id;
    bool operator<(const node&b) const{
        return r>b.r;
    }
}a[N];
priority_queue<node>pq;
struct tree{int l,r,mn,lztg;}t[N<<2];
void build(int x,int l,int r){
    t[x].l=l,t[x].r=r,t[x].mn=1e9,t[x].lztg=0;
    if(l==r)return;
    int mid=l+r>>1;
    build(x<<1,l,mid),build(x<<1|1,mid+1,r);
}
void change(int x,int pos,int y){
    if(t[x].l==t[x].r){t[x].mn=y;return;}
    int mid=t[x].l+t[x].r>>1;
    if(t[x].lztg){
        t[x<<1].mn+=t[x].lztg,t[x<<1|1].mn+=t[x].lztg;
        t[x<<1].lztg+=t[x].lztg,t[x<<1|1].lztg+=t[x].lztg;
        t[x].lztg=0;
    }
    if(pos<=mid)change(x<<1,pos,y);
    else change(x<<1|1,pos,y);
    t[x].mn=min(t[x<<1].mn,t[x<<1|1].mn);
}

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    for(cin>>T;T--;){
        int ans=0;
        memset(sum,0,sizeof sum);
        memset(sum2,0,sizeof sum2);
        memset(tmp,0,sizeof tmp);
        cin>>n>>k;
        cnt=0;
        for(int i=1;i<=n;++i)cin>>x[i],tmp[++cnt]=x[i];
        for(int i=1;i<=k;++i)cin>>a[i].l>>a[i].r>>a[i].t,tmp[++cnt]=a[i].l,tmp[++cnt]=a[i].r;
        sort(tmp+1,tmp+cnt+1);
        int len=unique(tmp+1,tmp+cnt+1)-tmp-1;
        for(int i=1;i<=n;++i)x[i]=lower_bound(tmp+1,tmp+len+1,x[i])-tmp,sum[x[i]]++,sum2[x[i]]++;
        for(int i=1;i<=k;++i)a[i].l=lower_bound(tmp+1,tmp+len+1,a[i].l)-tmp,
                             a[i].r=lower_bound(tmp+1,tmp+len+1,a[i].r)-tmp;
        for(int i=1;i<=len;++i)sum[i]+=sum[i-1];
        for(int i=1;i<=k;++i)a[i].t=sum[a[i].r]-sum[a[i].l-1]-a[i].t;
        sort(a+1,a+k+1,[&](node a,node b){return a.l<b.l;});
        build(1,1,k);
        for(int i=1,j=1;i<=len;++i){
            while(pq.size()&&pq.top().r<i)change(1,pq.top().id,1e9),pq.pop();
            while(j<=k&&a[j].l==i)change(1,j,a[j].t),pq.push({a[j].l,a[j].r,a[j].t,j}),++j;
            if(sum2[i]&&t[1].mn>=1){
                for(int k=1;k<=sum2[i];++k){
                    if(t[1].mn<1)break;
                    ans++;
                    t[1].mn--;
                    t[1].lztg--;
                }
            }
        }
        while(pq.size())pq.pop();
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：_Jocularly_ (赞：0)

策略题。首先进行转化，如果要砍掉尽量多的树，就可以转化为要保留尽量少的，那么此时我们运用贪心思想即可。其次考虑贪心策略，如果每个区间保留靠右侧的树，那么显然根据右端点升序排序最优，因为此时小区间能够对大区间产生贡献。比如说样例一，如果先考虑大区间，那么对于大区间和小区间的答案需要分别考虑，但是如果先考虑小区间，大区间的有一些就可以省去。

那么此时明白了转化策略后，来看一下具体做法。我们考虑怎么计算贡献，排序之后依次处理每一个区间，此时对于小区间来说，我们每一次保留下一棵树之后，在单点处加一。在处理大区间时，先进行区间求和，表示小区间给大区间产生的贡献，那么此时需要的就没有那么多了，满足最优策略。那么要处理区间单点加和和区间求和，采用线段树或树状数组，注意要进行离散化。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
int t;
int n,k;
int cnt;
int maxn;
int ans;
set<int> use;
int l[500005],r[500005],num[500005];
int x[500005];
int a[500005];
int discret[500005];
int del[500005];
struct section{
    int num;
    int l,r;
}p[500005];
struct node{
    int sum;
    int l,r;
}tree[1600005];
int lazy[1600005];
int len(int x){
    return (tree[x].r - tree[x].l + 1);
}
void pushup(int x){
    tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum;
}
void pushdown(int x){
    if(lazy[x]){
        lazy[ls(x)] += lazy[x];
        lazy[rs(x)] += lazy[x];
        tree[ls(x)].sum += lazy[x] * len(ls(x));
        tree[rs(x)].sum += lazy[x] * len(rs(x));
        lazy[x] = 0;
    }
}
void build(int l,int r,int x){
    tree[x].l = l;
    tree[x].r = r;
    lazy[x] = 0;
    if(l == r){
        tree[x].sum = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l,mid,ls(x));
    build(mid+1,r,rs(x));
    pushup(x);
}
void update(int ql,int qr,int l,int r,int x,int k){
    if(ql <= l && r <= qr){
        tree[x].sum += k * len(x);
        lazy[x] += k;
        return;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    if(ql <= mid) update(ql,qr,l,mid,ls(x),k);
    if(qr > mid) update(ql,qr,mid+1,r,rs(x),k);
    pushup(x);
}
int query(int ql,int qr,int l,int r,int x){
    if(ql <= l && r <= qr){
        return tree[x].sum;
    }
    pushdown(x);
    int ans = 0;
    int mid = (l + r) / 2;
    if(ql <= mid) ans += query(ql,qr,l,mid,ls(x));
    if(qr > mid) ans += query(ql,qr,mid+1,r,rs(x));
    return ans;
}
void discretizing(){
    int tot = 0;
    memset(discret,0,sizeof(discret));
    for(int i=1;i<=n;i++){
        discret[++ tot] = x[i];
    }
    for(int i=1;i<=k;i++){
        discret[++ tot] = l[i];
        discret[++ tot] = r[i];
        discret[++ tot] = num[i];
    }
    sort(discret+1,discret+1+tot);
    sort(x+1,x+1+n);
    tot = unique(discret+1,discret+1+tot) - discret;
    for(int i=1;i<=n;i++){
        x[i] = lower_bound(discret+1,discret+1+tot,x[i]) - discret;
        maxn = max(maxn,x[i]);
        use.insert(x[i]);
    }
    maxn = max(maxn,tot);
    for(int i=1;i<=k;i++){
        l[i] = lower_bound(discret+1,discret+1+tot,l[i]) - discret;
        r[i] = lower_bound(discret+1,discret+1+tot,r[i]) - discret;
    }
}
int cmp(section a,section b){
    return a.r < b.r;
}
signed main(){
    //首先一定从小区间开始，因为小区间有可能会对大区间产生贡献，那么一定最优
    //其次我们选树的时候有的树已经被占用了，我们就不能再用了，每个树是唯一的因此用set来存
    //然后取完了树会对大区间产生影响，那么我们在这棵树上加一，代表着大区间需要额外处理的减一
    //如果大区间需要的数小于等于已经有的那就根本不需要处理，区间求和显然用线段树或者树状数组
    //线段有负数要离散化
    //多测记得清空
    cin >> t;
    while(t --){
        //init
        use.clear();
        cnt = 0;
        ans = 0;
        //input
        cin >> n >> k;
        for(int i=1;i<=n;i++){
            cin >> x[i];
        }
        for(int i=1;i<=k;i++){
            cin >> l[i] >> r[i] >> num[i];
        }
        discretizing();
        for(int i=1;i<=k;i++){
            p[++ cnt].l = l[i];
            p[cnt].r = r[i];
            p[cnt].num = num[i];
        }
        sort(p+1,p+1+cnt,cmp);
        build(1,maxn,1);
        for(int i=1;i<=k;i++){
            int l = p[i].l;
            int r = p[i].r;
            int num = p[i].num;
            int now = query(l,r,1,maxn,1);//现在总共有几个
            if(now >= num) continue;//已经够了
            int need = num - now;//还需要的
            set<int>::iterator it = use.upper_bound(r);//从最右边开始
            it --;
            int tot = 0;
            for(int j=1;j<=need;j++){
                ans ++;//保留下来
                update(*it,*it,1,maxn,1,1);
                del[++ tot] = *it;
                it --;
            }
            for(int j=1;j<=tot;j++){
                use.erase(del[j]);
            }
        }
        cout << n - ans << endl;
    }
    return 0;
}
/*
1
7 1
8 4 10 1 2 6 7
2 9 3

4
*/

/*
3
7 1
8 4 10 1 2 6 7
2 9 3
7 2
8 4 10 1 2 6 7
2 9 3
1 10 1
7 2
8 4 10 1 2 6 7
2 9 3
1 10 4

4
4
3
*/
```

---

