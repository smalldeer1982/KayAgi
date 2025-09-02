# Hospital Queue

## 题目描述

There are $ n $ people (numbered from $ 1 $ to $ n $ ) signed up for a doctor's appointment. The doctor has to choose in which order he will appoint these people. The $ i $ -th patient should be appointed among the first $ p_i $ people. There are also $ m $ restrictions of the following format: the $ i $ -th restriction is denoted by two integers $ (a_i, b_i) $ and means that the patient with the index $ a_i $ should be appointed earlier than the patient with the index $ b_i $ .

For example, if $ n = 4 $ , $ p = [2, 3, 2, 4] $ , $ m = 1 $ , $ a = [3] $ and $ b = [1] $ , then the only order of appointment of patients that does not violate the restrictions is $ [3, 1, 2, 4] $ . For $ n =3 $ , $ p = [3, 3, 3] $ , $ m = 0 $ , $ a = [] $ and $ b = [] $ , any order of appointment is valid.

For each patient, calculate the minimum position in the order that they can have among all possible orderings that don't violate the restrictions.

## 说明/提示

In the first example, $ [3, 1, 2, 4] $ the only one valid order, so the minimum position of each patient is equal to their position in this order.

In the second example, any order is valid, so any patient can be appointed first.

In the third example, there are three valid orders: $ [4, 2, 3, 1, 5] $ , $ [3, 4, 2, 1, 5] $ and $ [4, 3, 2, 1, 5] $ .

## 样例 #1

### 输入

```
4 1
2 3 2 4
3 1```

### 输出

```
2 3 1 4```

## 样例 #2

### 输入

```
3 0
3 3 3```

### 输出

```
1 1 1```

## 样例 #3

### 输入

```
5 3
4 3 3 2 5
3 1
1 5
4 2```

### 输出

```
4 2 1 1 5```

# 题解

## 作者：Alex_Wei (赞：14)

**赛时做法**：答案具有可二分性。设当前检查是否有 $p_i\leq k$，相当于 $p_i := k$ 并检查是否有解。检查是否有解：设 $a_i$ 表示 $i$ 能到达的所有点 $j$ 的 $p_j$ 的最小值，拓扑排序时贪心选取当前队列中 $a_i$ 最小的点并扩展。若当前取出的点已经打破限制，则无解。时间复杂度 $\mathcal{O}(nm\log ^ 2 n)$，[TLE](https://codeforces.com/contest/1765/submission/185240086)。因为取出的点的 $a_i$ 单调不降，所以将优先队列换成若干个桶可以做到 $\mathcal{O}(nm\log n)$，[勉强通过](https://codeforces.com/contest/1765/submission/185240247)。

**官方做法**：很巧妙！将整个过程倒过来，将 $i$ 尽量往后放，也就是从 $n$ 到 $i$ 找到第一个时刻 $j$ 使得除了 $i$ 以外，当前没有可以取出的位置，则 $j$ 即为 $i$ 的答案。当时刻不大于一个位置的限制时，它可以被取出，优先队列或若干个桶维护。时间复杂度 $\mathcal{O}(nm)$。[代码](https://codeforces.com/contest/1765/submission/185280634)。

---

## 作者：dayz_break404 (赞：4)

### 题目描述

给出 $n$ 个人，$m$ 条关系，有对每个人的位置限制 $p_i$，求在所有合法的排队方案中，每个人能排在的最前的位置。

### 题目分析

由于给出的数据一定合法，图显然是一张有向无环图。

不难发现，每个人能排在的最前的位置具有单调性，考虑二分答案。

因为有两人前后的限制，所以每次只能取入度为 $0$ 的点，想到拓扑排序。

对于二分答案的判断，不难想到一种贪心策略：对于拓扑排序过程中的入度为 $0$ 的点，设 $minn_u$ 为以点 $u$ 为起点所能到达所有点的 $p_v$ 最小值，拓扑排序中每次取出入度为 $0$ 的点扩展时，选取 $minn_u$ 最小的点，并记录每个点的拓扑序。若 $minn_u > p_u$，则二分的答案是不合法的。

具体的做法，我们可以对关系 $u \to v$ 分别建一个正图 $e_1$ 与反图 $e_2$，对反图跑拓扑计算每次 $minn_u$ 的值。对正图再跑一次拓扑，每次取出当前 $minn_u$ 最小的点进行拓展即可。

需要注意的是，取出最小点若用优先队列，复杂度较高会超时，所以将优先队列换成桶进行处理。

时间复杂度：$O(nm \log n)$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+20;
struct node{
	int next,to;
}e1[maxn];
struct node2{
	int next,to;
}e2[maxn];
int l,r,n,m,head1[maxn],idx1,head2[maxn],idx2,p[maxn],ind[maxn],minn[maxn],ans[maxn];
queue<int> q;
vector<int> k[maxn];
inline void add(int u,int v){
	e1[++idx1].to=v,e1[idx1].next=head1[u],head1[u]=idx1;
	e2[++idx2].to=u,e2[idx2].next=head2[v],head2[v]=idx2;
}
inline void toposort(int x,int y){
	for(int i=1;i<=n;i++) ind[i]=0;
	for(int i=1;i<=n;i++){
		minn[i]=p[i];
		for(int j=head2[i];j;j=e2[j].next){
			ind[e2[j].to]++;
		}
	} 
	minn[x]=y;
	for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head2[u];i;i=e2[i].next){
			int v=e2[i].to;
			minn[v]=min(minn[v],minn[u]);
			ind[v]--;
			if(!ind[v]) q.push(v);
		}
	}
}
inline int check(){
	int now=0,tot=1;
	for(int i=1;i<=n;i++) k[i].clear(),ind[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=head1[i];j;j=e1[j].next){
			ind[e1[j].to]++;
		}
	}
	for(int i=1;i<=n;i++) if(!ind[i]) k[minn[i]].push_back(i);
	while(now<n){
		while(k[tot].empty()) tot++;
		int u=k[tot].back();
		now++;
		k[tot].pop_back();
		if(now>tot) return 0;
		for(int i=head1[u];i;i=e1[i].next){
			int v=e1[i].to;
			ind[v]--;
			if(!ind[v]) k[minn[v]].push_back(v);
		}
	}
	return 1;
}
int main(){
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		l=1,r=p[i];
		while(l<=r){
			int mid=(l+r)>>1;
			toposort(i,mid);
			if(check()) ans[i]=mid,r=mid-1;
			else l=mid+1;
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
} 
```

多次判断记得清空。

---

## 作者：hanjinghao (赞：4)

题意是有 $ n $ 个病人来排队看病，一种合法的排队方案需要满足以下条件：

一、${\forall}$ $ 1 $ ${\leq}$ $ i $ ${\leq}$ $ n $，编号为 $ i $ 的病人必须排在前 $ p_i $  位。

二、${\forall}$ $ 1 $ ${\leq}$ $ i $ ${\leq}$ $ m $，编号为 $ a_i $ 的病人必须排在编号为 $ b_i $ 的病人前面。

你需要对于每一位病人，求出在所有合法的排队方案中，他能排在的最靠前的位置。

**数据保证一定存在合法的排队方案。**

保证 $ 1 $ ${\leq}$ $ n $ ${\leq}$ $ 2000 $；$ 0 $ ${\leq}$ $ m $ ${\leq}$ $ 2000 $

==================================================================

这 $ n $ 个人，$ m $ 组有向关系，可以看成一张 $ n $ 个点，$ m $ 条边的有向图。

如果图中存在环，那么一定无解。但是**数据保证一定存在合法的排队方案**，因此，图中一定无环。

既然是有向无环图，又要求满足 $ m $ 组有向关系，那么，你想到了什么？没错，拓扑排序！但是，考虑到 $ p_i $ 的限制，如果用传统的拓扑排序，不一定能构造出合法的排队方案。那么这是什么导致的呢？是因为按照传统的拓扑排序，如果在某一时刻，图中存在多个入度为零的点，那么这些点被放入队列的先后顺序无法保证。我们既然要构造合法方案，就要在这个时候，让入度为零的点中，限制更严格的点被优先放入队列。何为限制更严格？我们设 $ minn_i $ 表示从 $ i $ 出发，能走到的所有点 $ j $（包括 $ i $ 本身）中，最小的 $ p_j $。原因是，根据拓扑排序的性质，$ i $ 能走到 $ j $，$ i $ 就要排在 $ j $ 前面，那么 $ j $ 需要满足的 $ p_j $ 的限制，自然也与 $ i $ 有关。$ minn $ 的值越小，限制就越严格。

我们对于每一个病人，进行二分答案，假设当前第 $ i $ 个人二分的答案为 $ x $ ，则在检验的时候把 $ p_i $ 对 $ x $ 取 $ min $，然后按照上述方法跑一遍拓扑排序。由于上述方法已经是每一步都往合法方案去凑了，如果这样都不能构造出合法方案，则当前答案 $ x $ 无法取到。能构造出合法方案，则当前答案 $ x $ 可以取到。

然而，我们会发现，如果朴素地实现上述拓扑排序，需要用到优先队列。二分答案要带一个 $\log $，优先队列又要带一个 $\log $ ，复杂度为 $ n ^ 2\log ^ 2 n $，无法通过。所以，我们需要在 $ O(n) $ 的时间内，把这个原本是 $ n\log n $ 的拓扑排序模拟出来，以此把总复杂度变为 $ n ^ 2\log n $。有一个结论：${\forall}$ $ 1 $ ${\leq}$ $ i $, $ j $ ${\leq}$ $ n $，如果从 $ i $ 出发能到达 $ j $，则 $ minn_i $ 一定小于等于 $ minn_j $，根据 $ minn $ 数组，可以在 $ O(n) $ 时间内计算出每个点的拓扑序。

以下是核心代码：

```cpp

void dfs(int x)
{
	minn[x] = p[x];
	for (auto i : G[x])
	{
		if (!minn[i]) dfs(i);
		minn[x] = min(minn[x], minn[i]);
	}
}

bool Check(int x, int num)
{
	for (register int i = 1; i <= n; ++i)
		minn[i] = s[i] = 0;
	int tmp = p[x];
	p[x] = num;
	for (register int i = 1; i <= n; ++i)
		if (!minn[i]) dfs(i);
	for (register int i = 1; i <= n; ++i)
		++s[minn[i]];
	for (register int i = 1; i <= n; ++i)
		s[i] += s[i - 1];
	for (register int i = 1; i <= n; ++i)
		if (s[minn[i]] > p[i])
		{
			p[x] = tmp;
			return 0;
		}
	p[x] = tmp;
	return 1;
}
 
int main()
{
	read(n);
	read(m);
	for (register int i = 1; i <= n; ++i)
		read(p[i]);
	for (register int i = 1; i <= m; ++i)
	{
		int x, y;
		read(x);
		read(y);
		G[x].push_back(y);
	}
	for (register int i = 1; i <= n; ++i)
	{
		int lft = 1, rgh = p[i], ans = 0;
		while (lft <= rgh)
		{
			int md = (lft + rgh) >> 1;
			if (Check(i, md))
			{
				ans = md;
				rgh = md - 1;
			}
			else lft = md + 1;
		}
		writesp(ans);
	}
	putchar(10);
	return 0;
}
```

---

## 作者：MSavannah (赞：2)

神仙题

对于第二条限制很套路，相当于给你 $n$ 个点，$m$ 条有向边。很容易联想到拓扑排序来解决这个限制。

那么第一个限制怎么办呢，发现正图很难做，考虑建反图，对于每个数 $i$，尽可能的让它填的靠后一点，也就是说，我们只有在一个位置不得不填 $i$ 的时候，再把 $i$ 填进去。这样我们就得到了正图中这个点出现最早的位置。

对于一个点不得不填有 $2$ 种情况：
1. 已经没有点可填了
2. 不填他后面的就无法满足条件 $1$ 了

时间复杂度 $O(nm)$。

[code](https://www.luogu.com.cn/record/155946076 "code")

最后 [P1954](https://www.luogu.com.cn/problem/P1954) 这道题可以算是一个双倍经验了，只比这道题多一个随便输出一个合法方案

---

## 作者：bsdsdb (赞：0)

题意：给 $\{p_{n\le2000}\},\{a_{m\le2000}\},\{b_m\}$，一个排列 $\{{p'}_n\}$ 合法，当且仅当：

- $\forall i:{p'}_i\le p_i$；
- $\forall i:{p'}_{a_i}\le p_{b_i}$。

对于 $i\in[1,n]$ 求 $\min_{j'}{j'}_i$，保证存在合法 $p'$。

提示：考虑从后往前填 $p'$。

从前往后填的话，可能由于第一条限制，填着填着后面挤不下了，但是从后往前就没有这种问题。假设现在正在求解 $x$ 的答案，从后往前遍历到了 $t$。考虑维护所有现在能填的数 $i$，他们需要满足：

- 还没填；
- $p_i\ge t$；
- 不存在 $j$，满足 $a_j=x$，且 $b_j$ 还没填。

建个图 $G=(V=[1,n],E=\{(b_i,a_i)\mid i\in[1,m]\}$，那么第三条就变成「删掉所有已经填的数在图上的点后，$x$ 入度为 $0$」，很好维护。维护能填的数用个队列就行，$x$ 能不填就不填。由于每次要复制入度数组，复杂度是 $\Omicron(n^2+nm)$。如果数据范围不是 $n,m\le2000$ 是 $nm\le2\times10^5$，可以用可持久化数组维护入度做到 $\Omicron(nm\log n)$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
const ll MAXN = 2e3 + 5;
 
ll n, m, a[MAXN], b[MAXN], p[MAXN], ind[MAXN], ind1[MAXN];
vector<ll> e[MAXN], p2p[MAXN];

void slv(ll x) {
	memcpy(ind, ind1, sizeof ind1);
	queue<ll> q;
	for (ll t = n; t; --t) {
		for (ll i : p2p[t]) if (!ind[i]) q.emp(i);
		if (q.front() == x && q.size() != 1) q.push(q.front()), q.pop();
		ll pl = q.front();
		for (ll i : e[pl]) {
			if (--ind[i] == 0 && p[i] >= t) q.emp(i);
		}
		q.pop();
		if (pl == x) {
			write(t), space();
			return;
		}
	}
}

int main() {
    read(n), read(m);
    for (ll i = 1; i <= n; ++i) read(p[i]), p2p[p[i]].empb(i);
    for (ll i = 1; i <= m; ++i) read(a[i]), read(b[i]), e[b[i]].empb(a[i]), ++ind1[a[i]];
    for (ll i = 1; i <= n; ++i) slv(i);
    enter();
	return 0;
}
 
;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;
 
   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：xiazha (赞：0)

~~首先我们要知道这题有重题。~~

进入正题，你会发现这题正着来会爆炸，于是考虑倒着，我们枚举每一个 $i$，内层从 $n\sim 1$ 枚举 $i$ 的最优位置 $j$。

贪心的，考虑目前有没有符合条件可以放在 $j$ 这个位置的数 $k$，那么 $k$ 需满足 $p_k\le j$ 且不存在 $v$ 需要在 $k$ 右边但是并没有被放入队列。如果存在的话任意放入一个到队列并且更新条件，否则 $j$ 即为答案终止循环。

你会想知道如何维护 $p_k\le j$ 这一条件，那么我们将目前满足不存在 $v$ 需要在 $k$ 右边但是并没有被放入队列的数扔进一个优先队列里，每次取出来最大的数看是不是小于 $j$ 就搞定了。

还有要注意的就是当你枚举 $i$ 的时候不要把 $i$ 扔进优先队列里了。

~~我讲的还是没有那么清楚，看看代码吧。~~


```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[2002],t[2002],tt[2002],deg[2002];
vector<int> g[2002];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		t[u]++;g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		memcpy(deg,t,sizeof(t));
		priority_queue<pair<int,int>> q;
		for(int j=1;j<=n;j++)
			if(!deg[j]&&j!=i)
				q.push({a[j],j});
		for(int j=n;j>=1;j--)
		{
			if(q.empty()||q.top().first<j)
			{
				cout<<j<<" ";
				break;
			}
			int x=q.top().second;q.pop();
			for(int y:g[x])
			{
				deg[y]--;
				if(deg[y]==0&&y!=i) q.push({a[y],y});
			}
		}
	}
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

真的很妙的一道题。

由于题目中有一些先后关系，想到拓扑排序。

题目要求 $i$ 在正序列中尽可能往前放，那么就是在反序列中尽量往后放。显然反过来做会比正着做要容易。于是考虑在反图上解决这个问题。

显然，必须填 $i$ 的条件是：$i$ 不得不选或者填其他的数都比它劣。

那么我们每次填的时候就贪心地在可选所有数中选择一个最优的 $i$。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int N = 2005;
int n, m;
int p[N], in[N], du[N];
vector <int> g[N];
priority_queue < pair <int, int> > q;
void topo(int x) {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        du[i] = in[i];
        if (du[i] == 0 && i != x)
            q.push(make_pair(p[i], i));
    }
    for (int i = n; i; i--) {
        if (q.empty() || q.top().first < i) {
            cout << i << ' ';
            break;
        }
        int u = q.top().second; q.pop();
        for (int j = 0, v; j < (int)g[u].size(); j++) {
            v = g[u][j];
            if (v != x && du[v] > 0) {
                du[v]--;
                if (du[v] == 0) q.push(make_pair(p[v], v));
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        g[y].push_back(x);
        in[x]++;
    }
    for (int i = 1; i <= n; i++) topo(i);
}
```

---

## 作者：ethan0328 (赞：0)

## 思路

感觉官方题解的做法很妙。

对于每个数 $i$，考虑从后往前填这个序列，经量让 $i$ 靠后被填，不得不填 $i$ 的位置就是答案。

考虑哪些数可以被填。首先保证必须填在它后面的数被填，从后往前做让我们可以很方便的处理这个，可以对每个 $b_i$ 向 $a_i$ 连边，然后按拓扑序填。

同时，贪心的选 $p_i$ 最大的先填。

当无数可填或所有数的 $p_i$ 都大于要填的位置 $j$ 时，则不得不填 $i$。

## 代码

```cpp
#include<bits/stdc++.h>
#define mkp make_pair
#define fir first
#define sec second
using namespace std;
const int N=2e3+10;
int n,m,a[N],dx[N],dx2[N];
vector<int> e[N];
priority_queue<pair<int,int> > q;
signed main()
{
	int x,y;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		e[y].push_back(x);
		dx[x]++;
	}
	for(int i=1;i<=n;i++)
	{
		while(!q.empty())
		{
			q.pop();
		}
		for(int j=1;j<=n;j++)
		{
			dx2[j]=dx[j];
			if(dx2[j]==0&&j!=i)
			{
				q.push(mkp(a[j],j));
			}
		}
		for(int j=n;j;j--)
		{
			if(q.empty()||q.top().fir<j)
			{
				cout<<j<<" ";
				break;
			}
			x=q.top().sec;
			q.pop();
			for(auto y:e[x])
			{
				if(y!=i&&dx2[y]>0)
				{
					dx2[y]--;
					if(dx2[y]==0)
					{
						q.push(mkp(a[y],y));
					}
				}
			}
		}
	}
}
```


---

## 作者：快斗游鹿 (赞：0)

首先想到一个很经典的贪心策略，就是建反图再跑拓扑排序。那么问题就是怎么让一个病人尽量靠前，而在反图上就转变为让一个病人尽量靠后。也就是说，只有在他不得不排入队列，再将他排入队列。

不得不排入队列有两种情况，一是他现在不排，后面的人就再也排不进去了，二是他现在不排，后面的病人就没法排完。

部分代码：

```cpp
void topob(int x){
	priority_queue<pair<int,int>,vector<pair<int,int> >,less<pair<int,int> > >q;
	for(int i=1;i<=n;i++)d[i]=D[i];
	for(int i=1;i<=n;i++){
		if(!d[i])q.push(make_pair(k[i],i));
	}
	ttt=0;
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(u==x){
			if(q.empty()){
				cout<<n-ttt<<" ";return;
			}
			else{
				u=q.top().second;q.pop();q.push(make_pair(k[x],x));
			}
		}
		if(n-ttt>k[u]){
			cout<<n-ttt<<" ";return;
		}
		ttt++;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			d[v]--;
			if(!d[v]){
				q.push(make_pair(k[v],v));
			}
		}
	}
	//for(int i=ttt;i>=1;i--)cout<<ansa[i]<<" ";
}
```


---

