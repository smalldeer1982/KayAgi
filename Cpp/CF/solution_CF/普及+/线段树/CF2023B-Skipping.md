# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1```

### 输出

```
16
200
100
1000```

# 题解

## 作者：AquariusZhao (赞：14)

最短路简单题。

题目链接：
- [Codeforces](https://codeforces.com/contest/2023/problem/b)
- [Luogu](https://www.luogu.com.cn/problem/CF2023B)

## 题意

有 $n$ 个物品，每个物品有一个价值 $a_{i}$ 和一个参数 $b_{i}$。

对于第 $i$ 个物品，你可以选择：
- **获得**这个物品，收获 $a_{i}$ 的价值，并去往最后一个没有“到过”的位置 $j$，满足 $j\le i$；
- **放弃**这个物品，并去往最后一个没有“到过”的位置 $j$，满足 $j\le b_{i}$。

这里，无论你选择**获得**还是**放弃**这个物品，你都已经“到过”这个位置了，也就是说以后不能再遇到这个物品了。

你需要最大化获得的价值和。

范围：
- $1\le b_{i} \le n \le 4\times 10^{5}$
- $ 1 \le a_{i} \le 10^{9}$

## 思路

### 一、转化

首先，看到「从 $u$ 到 $v$」这种条件，容易想到连边。

然后我们考虑答案是什么：假设你放弃的位置的集合为 $S$，最后一次放弃之后到达的编号为 $dst$。那么由于接下来可以直接往回走，所以答案为
$$
\sum_{i=1}^{dst} a_{i} [i \notin S]
$$
即
$$
\sum_{i=1}^{dst} a_{i} - \sum_{i\in S} a_{i}
$$
注意到左边跟 $S$ 的内容没有关系，所以对于所有到达 $dst$ 的方案，我们本质上就要最小化 $\sum_{i\in S} a_{i}$。换言之，我们要求出从 $1$ 到达 $dst$ 的最小价值。这不就是最短路么？

### 二、最短路

那么我们具体的连边方案也出来了：

![](https://cdn.luogu.com.cn/upload/image_hosting/sqm2ffce.png)

此时到每个点的最短路 $dis_{i}$ 表示到 $i$ 所需的最小的 $\sum_{j\in T} a_{j}$。

其中绿边的是**放弃**之后走到 $b_{i}$ 的边（没有画全），边权为 $a_{i}$；蓝边的是 $0$ 权边，因为每个位置都可以通过**获得**来直接或间接到达之前的每个位置。

然后从节点 $1$ 跑 Dijkstra 即可，最后答案就是之前那个式子。时间复杂度 $\mathcal{O}(\sum n\log n)$。

## 代码

完全没难度，但还是[放一下](https://codeforces.com/contest/2024/submission/287441397)吧。

## 后记

~~赛时的我还傻傻地写了个前缀优化建图，赛后才想起来根本不需要~~

如果有任何错误或者疑问，欢迎评论或私信指出！

If you can，~~点个赞呗。~~

---

## 作者：gcx114514 (赞：6)

~~（Div.2 两发罚时挂出前 $10$。）~~

首先发现，如果从第 $i$ 道开始，不跳过可以获得在 $[1,i]$ 这个区间内的所有题的贡献。可以先做前缀和得到 $sum$ 数组。现在考虑我们枚举通过若干跳过或作答到达的最大编号的问题是 $i$ ，发现到达它的代价是那些跳过的题的价值之和 $dis_i$（因为你跳过就做不到了），那么答案就是 $\max\limits_{i=1}^n (sum_i-dis_i)$。现在考虑如何计算这个 $dis$ 数组。可以发现，在第 $i$ 个点有以下两种决策：

1. 花费 $a_i$ 的代价移动到 $b_i$。
2. 花费 $0$ 的代价移动到 $i-1$。

由于是从一号问题开始，可以发现 $dis_i$ 就是按照上述两种方法建图后的最短路，那么只需要求出单源最短路即可。时间复杂度 $O(n\log_2n)$。

注意要开`long long`。

[赛时代码](https://codeforces.com/contest/2024/submission/286930518)

---

## 作者：Xy_top (赞：3)

因为赛时特判 $b_1=1$ 时没输出空格导致掉大分，写一篇题解以留念。

本篇题解采用线段树解法。

容易发现，答案一定形如跳完最后一道题后剩下的题全部做掉（相当于废话）。

所以可以枚举跳到的最后一道题。设 $f_i$ 为通过跳题和做题到第 $i$ 个点时，跳过的题分数总和的最小值。显然 $f_i=\min\limits_{j=i+1}^{b_i-1}{f_j}+a_i$，而这个直接上线段树就行了。

最终答案为 $\min\limits_{i=1}^n (\sum\limits_{j=1}^i a_j) - f_i$。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x, y;
int a[400005], b[400005], mx[1600005];
int f[400005];//f[i]：到位置 i 的最小损失
void update (int l, int r, int k) {
	if (l == r) {
		mx[k] = min (mx[k], y);
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) update (l, mid, k << 1);
	else update (mid + 1, r, k << 1 | 1);
	mx[k] = min (mx[k << 1], mx[k << 1 | 1]);
}
int query (int l, int r, int k) {
	if (x <= l && y>= r) return mx[k];
	int mid = l +r >> 1, res = 100000000000000000LL;
	if (x <= mid) res = query (l, mid, k << 1);
	if (y > mid) res = min (res, query (mid + 1, r, k << 1 | 1) );
	return res;
}
void solve () {
	cin >> n;
	For (i, 1, n) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	For (i, 1, n) cin >> b[i];
	if (b[1] == 1) {
		cout << a[1];
		return;
	}
	For (i, 1, n) f[i] = 100000000000000000LL;
	For (i, 1, 4 * n) mx[i] = 100000000000000000LL;
	f[1] = 0;
	x = b[1];
	y = a[1];
	update (1, n, 1);
	f[b[1] ] = a[1];
	For (i, 2, n) {
		if (i > b[i] - 1) continue;
		x = i, y = b[i] - 1;
		f[b[i] ] = min (f[b[i] ], query (1, n, 1) + a[i] - a[i - 1]);
		x = b[i], y = f[b[i] ];
		update (1, n, 1);
	}
	int ans = 0;
	For (i, 1, n) ans = max (ans, a[i] - f[i]);
	cout << ans << '\n';
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) solve ();
	return 0;
}
```

---

## 作者：zhm080507 (赞：2)

# [skipping](https://codeforces.com/contest/2023/problem/b?csrf_token=685e22737286d5a21ddc43781db947a3)

### 题目大意

共有 $n$ 道题，从第 $1$ 道开始，对每道题可以选择：

- 跳过，然后可以在 $1\sim b_i$ 中选一道题做，同时你无法再做这一题；
- 完成，然后可以在 $1\sim i-1$ 中选一道做，同时你的得分增加 $a_i$。

### 算法分析

其实还是容易想到用图来解决这一问题，我们把边权设为这一操作的代价，就可以得到以下两种连边方式：

- 跳过，即连一条 $i$ 到 $b_i$ 边权为 $a_i$ 的边；
- 完成，即连一条 $i$ 到 $i-1$ 边权为 $0$ 的边。

然后再从 $1$ 号点跑一遍单源最短路就行，代码很简单。

### code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back

const int N=500000,inf=1e15;
int T,n,a[N],x;
int sum[N],dis[N],ans;
bool vis[N];
vector<pair<int,int>>e[N];
priority_queue<pair<int,int>> q; 

void dj(){
	for(int i=1;i<=n;i++)
		dis[i]=inf,vis[i]=0;
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto k:e[u]){
			int v=k.first;
			if(dis[v]>dis[u]+k.second){
				dis[v]=dis[u]+k.second;
				q.push({-dis[v],v});
			}
		}
	}
	return;
}

void sol(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		if(i!=n) e[i+1].pb({i,0});
		e[i].pb({x,a[i]});
	}
	dj();ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,sum[i]-dis[i]);
        e[i].clear();
	}
	cout<<ans<<"\n";
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		sol();
	}
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：2)

什么数据结构都不会写，菜是原罪。

做法：可以做出 $a_i$ 前缀和，然后维护每个 $a_i$ 选或不选，把不选的权值和丢到线段树里维护，取最小值，用前缀和减去这个权值和里就行了。

因为是区间赋值，单点求值，可以线段树。

具体见代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,k,r,p,vst,t;
ll a[500005],b[500005],qz[500005];
ll tr[2000020];
void build(int u,int le,int ri) {
	tr[u]=LLONG_MAX;
	if(le==ri)
		return;
	int mid=(le+ri)>>1;
	build(u<<1,le,mid);
	build(u<<1|1,mid+1,ri);
}
void pdn(int u,int le,int ri) {
	tr[u<<1]=min(tr[u<<1],tr[u]);
	tr[u<<1|1]=min(tr[u<<1|1],tr[u]);
}
bool inr(int le,int ri,int L,int R) {
	return (L<=le)&&(ri<=R);
}
bool otr(int le,int ri,int L,int R) {
	return (le>R)||(ri<L);
}
ll query(int u,int le,int ri,int L,int R) {
	if(otr(le,ri,L,R))return 0;
	if(inr(le,ri,L,R))return tr[u];
	int mid=(le+ri)>>1;
	pdn(u,le,ri);
	return query(u<<1,le,mid,L,R)|query(u<<1|1,mid+1,ri,L,R);
}
void update(int u,int le,int ri,int L,int R,ll x) {
	if(otr(le,ri,L,R))
		return;
	if(inr(le,ri,L,R)) {
		tr[u]=min(tr[u],x);
		return;
	}
	int mid=(le+ri)>>1;
	pdn(u,le,ri);
	update(u<<1,le,mid,L,R,x);
	update(u<<1|1,mid+1,ri,L,R,x);
} //上面是线段树板子
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
			cin >> b[i];
		for (int i = 1; i <= n; i++)
			qz[i] = qz[i - 1] + a[i];//求前缀和
		build(1, 1, n);
		update(1, 1, n, 1, 1, 0);//把 [1,1] 不选的设置成 0
		ll ans = 0;
		for (int i = 1; i <= n; i++){
			ll mt = query(1, 1, n, i, i);//求 [1,i] 有多少个不选，注意这里 tr[i] 表示的是 [1,i] 不选的和
			ans = max(ans, qz[i] - mt);//[1,i] 的总和减去不选的就是选的值
			update(1, 1, n, 1, b[i], mt + a[i]);//a[i] 选的处理完了，继续处理 a[i] 不选的
		} 
		cout << ans << "\n";
	}
}
```

---

## 作者：Jordan_Pan (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Jordan-Pan/p/18492674)

[原题](https://codeforces.com/contest/2023/problem/B)

首先要读懂题目：每次机器选择的是**小于且先前没操作过的最大位置**，机器的选择是唯一的。

这道题看上去就很贪心或者 dp，然而我太菜了两条都走到了死路。然而我们还是能注意到一些性质的。

从一个点开始一直选择吃掉 $a_i$，最后会走到 $1$ 号点，并且把 $1$ 到 $i$ 上的所有还没吃过的点全部吃掉。

注意到 $a_i>0$，那么我们肯定是拿的点要尽量多，这时如果 $b_i \le i$，那选择跳 $b_i$ 就是很不优的，因为这样就把 $a_i$ 放弃了，而选择一个一个地吃过去也能到达同样的位置，并且把 $a_i$ 吃掉了。于是最后的路径大概是这样的：向右跳 $b$，向左吃几个（可能是 0 个），向右跳 $b$，向左吃几个……最后走到一个最右边的点，往前把没吃过的点全部吃掉。

发现吃掉点的最大值很不好维护，正难则反，考虑维护放弃的最小值。把能到达最右侧的点为 $i$ 时放弃的点的最小值设为 $f_i$，则用前缀和减掉他就是吃掉点的最大值，最后取 $\max$ 即可。

到这里已经可以直接建图跑最短路，然后就做完了。

具体地，向 $i-1$ 连一条权值为 $0$ 的边，向 $b_i$ 连一条权值为 $a_i$ 的边，跑出来到 $1$ 到 $i$ 的最短路就是 $f_i$。代码实现用了 Dij。

~~~cpp
rd(n);
for(int i=1;i<=n;i++)
	g[i].clear(),dis[i]=1e18;
for(int i=1;i<=n;i++)rd(a[i]),a[i]+=a[i-1];
for(int i=1;i<=n;i++){
	rd(b[i]);
	g[i].push_back({b[i],a[i]-a[i-1]});
	if(i>1)g[i].push_back({i-1,0});
}
q.push({dis[1]=0,1});
for(;!q.empty();q.pop()){
	long long ww=q.top().first;
	int u=q.top().second;
	if(dis[u]<ww)continue;
	for(auto i:g[u]){
		int v=i.first,w=i.second;
		if(dis[u]+w<dis[v])q.push({-(dis[v]=dis[u]+w),v});
	}
}
ans=0;
for(int i=1;i<=n;i++)
	ans=std::max(ans,a[i]-dis[i]);
printf("%lld\n",ans);
~~~

然而这个菜鸡太菜了，没想到这个做法……~~所以我是怎么写出来的~~

我们继续思考最后的路径还有哪些性质，发现向左吃的时候一定不会超过上一个放弃掉的点。同时也是从这个点跳到此时路径最右侧，也就是上一个跳 $b$ 的点。

什么意思呢，如果 $b_1=4$，$b_2=3$，这样走一定不是最优的：

$$2 \to 3 \to 1 \to 4$$

这样吃掉了 `3` 和 `4` 两个点。然而我们可以这么走：

$$2 \to 1 \to 4 \to 3$$

这样吃掉了 `4`，`3`，`2` 三个点。可以看到，我们在 `2` 如果选择跳 $b$，就会白白浪费掉 $a_2$，并且在 `2` 的左侧完全有一个 `1` 能够跳到更远的位置。

或者说，最后的路径上不会出现“外面套着里面”的形状，一定是“相扣”的。

这样一来，我们就能够利用 $i$ 到 $b_i$ 中间只有一个从前面跳过来的 $b$ 进行转移。

$$f_{b_i}= \min_{j=i}^{b_i-1}f_j+a_i$$

看到这个单点修改、区间求 $\min$ 的东西，这个菜鸡想到了线段树。注意不能走到的点是不能继续转移的。

~~~cpp
rd(n);
for(int i=1;i<=n;i++)rd(a[i]),a[i]+=a[i-1];
for(int i=1;i<=n;i++)rd(b[i]);
Bld(1,1,n);Chg(1,1,n,1,0);
ans=a[1];
for(int i=1;i<=n;i++){
	if(b[i]<=i)continue;
	long long val=Qry(1,1,n,i,b[i]-1);
	if(val>1e15)continue;
	val+=a[i]-a[i-1];
	Chg(1,1,n,b[i],val);
	ans=std::max(ans,a[b[i]]-val);
}
printf("%lld\n",ans);
~~~

---

## 作者：OIbishop (赞：1)

# 前言
一个不用脑子的做法。
# 做法
这种跳来跳去的题目一看就是建图。  
首先考虑暴力建图，将 $[i,b_i]$ 向 $b_i$ 建一条边权为 $a_i$ 的边。答案就是 $\max_{i=1}^n (sum_i - dis_i)$ 其中 $sum_i$ 为前 $i$ 个 $a_i$ 的和，$dis_i$ 为 $1$ 到 $i$ 的最短路。  
然后发现可以线段树优化建图，需要稍微卡卡空间。时间复杂度 $O(n\log^2 n)$ 可以通过。  
具体实现请看代码，应该比较清楚。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int t , n , pre[N * 5];
struct node {int a , b;} a[N];
vector < pair <signed , signed> > e[N * 5];
#define ls (o << 1)
#define rs (o << 1 | 1)
inline void build (int o , int l , int r)
{
    if (l == r) return pre[l] = o , void ();
    int mid = l + r >> 1;
    build (ls , l , mid) ; build (rs , mid + 1 , r);
    e[ls].push_back ({o , 0}) , e[rs].push_back ({o , 0});
}
inline void change (int o , int l , int r , int x , int y , int nd , int w)
{
    if (x > y) return ;
    if (l == x && r == y) return e[o].push_back ({nd , w}) , void ();
    int mid = l + r >> 1;
    if (y <= mid) change (ls , l , mid , x , y , nd , w);
    else if (x > mid) change (rs , mid + 1 , r , x , y , nd , w);
    else change (ls , l , mid , x , mid , nd , w) , change (rs , mid + 1 , r , mid + 1 , y , nd , w);
}
bool vis[N * 5]; int dis[N * 5];
inline void Dij ()
{
    priority_queue < pair <long long , signed> > q;
    q.push ({0 , pre[1]}); dis[pre[1]] = 0;
    while (q.size ())
    {
        int u = q.top ().second ; q.pop ();
        if (vis[u]) continue; vis[u] = 1;
        for (auto i : e[u])
        {
            int v = i.first , w = i.second ;
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w , q.push ({-dis[v] , v});
        }
    }
}
signed main ()
{
    cin >> t;
    while (t--)
    {
        for (int i = 1; i <= n * 5; i++) e[i].clear () , vis[i] = 0 , pre[i] = 0;
        cin >> n;
        for (int i = 1; i <= n * 5; i++) dis[i] = (long long)0x3f3f3f3f3f3f3f3f;
        for (int i = 1; i <= n; i++) cin >> a[i].a;
        for (int i = 1; i <= n; i++) cin >> a[i].b;
        build (1 , 1 , n);
        for (int i = 1; i <= n; i++)
            change (1 , 1 , n , i , a[i].b , pre[a[i].b] , a[i].a);
        Dij ();
        int sum = 0 , ans = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += a[i].a;
            ans = max (sum - dis[pre[i]] , ans);
        }
        cout << ans << "\n";
    }
	return 0;
}

```

---

## 作者：lwwwb_555 (赞：1)

我们发现如果我们能取到的位置已经到 $i$，那么我们能取到的最大值就是 $\sum_{j=1}^{i} a_j$。所以我们考虑算要将取得位置搞到 $i$ 所需要的最小代价。

我们考虑在 $i$ 位置，如果我们要跳过则相当于 $i+1 \sim b_i$ 的代价可以等于 $c_i+b_i$ 这里的 $c_i$ 相当于到 $i$ 所需要花费的代价，而同一个位置的 $c$ 可能会被更新多次，所以我们只需要用一颗线段树来维护取 $\min$ 操作就好了。

最后的答案就是 $\max_{i=1}^{n} sum_i-c_i$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[400050],b[400050];
int read(){
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
} 
struct node{
	int ll,rr;
	long long w;
}tt[1600050];
void build(int p,int l,int r){
	tt[p]={l,r,1000000000000000000ll};
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p*2,l,mid),build(p*2+1,mid+1,r);
}
void pushdown(int p){
	if(tt[p].ll==tt[p].rr) return;
	tt[p*2].w=min(tt[p*2].w,tt[p].w),tt[p*2+1].w=min(tt[p*2+1].w,tt[p].w);
	return;
}
void update(int p,int l,int r,long long k){
	if(tt[p].ll>=l && tt[p].rr<=r){
		tt[p].w=min(tt[p].w,k);
		return;
	}
	pushdown(p);
	int mid=(tt[p].ll+tt[p].rr)>>1;
	if(l<=mid) update(p*2,l,r,k);
	if(r>mid) update(p*2+1,l,r,k);
	return;
}
long long query(int p,int l){
	if(tt[p].ll==tt[p].rr) return tt[p].w;
	pushdown(p);
	int mid=(tt[p].ll+tt[p].rr)>>1;
	if(l<=mid) return query(p*2,l);
	return query(p*2+1,l);
}
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) b[i]=read();
		build(1,1,n);
		update(1,1,1,0);
		long long sum=0,ans=0;
		for(int i=1;i<=n;i++){
			sum+=a[i];
			long long u=query(1,i);
			if(u==1e18) break;
			ans=max(ans,sum-u);
			if(b[i]>i) update(1,i+1,b[i],u+a[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```

---

## 作者：__3E24AC7002AD9292__ (赞：1)

不会建图，场上写了个树状数组优化 DP。

发现对于 $\forall i$，如果 $b_i\leq i$，那么在达到 $i$ 的时候跳过 $i$ 一定不比提交 $i$ 这个问题更优。

设 $dp_i$ 表示 $[1,i)$ 区间内所有题目均提交的答案。如果提交 $i$ 问题，则答案为 $\sum\limits_{j=1}^ia_i$，反之为 $\max\limits_{j=i+1}^{b_i}dp_j-a_i$（这个部分需要使用树状数组维护）。故有转移方程 $dp_i=\max(\sum\limits_{j=1}^ia_i,\max\limits_{j=i+1}^{b_i}dp_j-a_i)$，注意要倒序枚举。

```cpp
for (int i=1;i<=n;i++)
  a[i]=read(),pre[i]=pre[i-1]+a[i],c[i]=0;
for (int i=1;i<=n;i++)
	b[i]=max(i,read());
for (int i=n;i>=1;i--){
	t[i]=max(pre[i],qry(b[i])-a[i]);
	add(i,t[i]);
}
```

---

## 作者：aeiouaoeiu (赞：1)

本质上在点 $i$ 的决策就是：往回扫没有看到过的题 $j$，要么加进答案，要么跳到 $b_j$ 处继续扫。

于是设 $f_i$ 表示跳到点 $i$ 时，丢掉的题目的 $a$ 值总和的最小值。答案即为 $\max_{1\le i\le n}{(\sum_{1\le j\le i}{a_j})-f_i}$。

一种解法是连单向边 $(i,i-1,0)$ 与 $(i,b_i,a_i)$ 跑最短路。还有一种比较不聪明的做法。

显然 $f_i$ 只能由 $1\le j<i$ 的 $j$ 转移而来。于是遍历 $1$ 到 $n$ 依次确定 $f$，确定 $f_i$ 后可以做转移 $f_i+a_j\to f_{b_j}$，其中 $j\le i$。

观察式子，可以发现 $f_x$ 由一系列满足 $b_j=x$ 的 $a_j$ 加上一个满足 $i\ge j$ 的 $f_j$ 转移过来。

设 $x$ 左边第一个满足 $b_j=x$ 的 $j$ 为 $v_x$。则转移可以分为两部分：$i\isin[1,v_x-1]$ 与 $i\isin[v_x,x-1]$。

可以将转移表示成这个形式：$f_x=\min(c_x,m_x+\min_{v_x\le i<x}f_i)$。其中 $c_x$ 为第一部分转移的结果，$m_x=\min_{b_j=x}a_j$。$m$ 可以在遍历时更新。

同样，在遍历时更新 $c_x$。设 $j$ 左边第一个满足 $b_k=b_j$ 的 $k$ 为 $p_j$。则遍历到 $i$ 时，$c_{b_i}=\min(c'_{b_i},m'_{b_i}+\min_{1\le j<i}f_j)$。注意这里转移时由于统计的是不包括 $i$ 的转移，要在更新 $c$ 后更新 $m$。

用线段树区间查询 $f$ 最小值，时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef __int128 LL;
const ll maxn=400007,ee=1e18;
ll n,a[maxn],b[maxn],f[maxn],pre[maxn],vis[maxn],mn[maxn],cur[maxn],ans;
struct Tree{
	ll val[maxn<<2],lf[maxn<<2];
	void pushup(ll rt){val[rt]=min(val[rt<<1],val[rt<<1|1]);}
	void build(ll l,ll r,ll rt){
		val[rt]=ee;
		if(l==r) return lf[l]=rt,void(); ll mid=(l+r)>>1;
		build(l,mid,rt<<1),build(mid+1,r,rt<<1|1);
	}
	void upd(ll x,ll z){
		x=lf[x];
		for(;x;x>>=1) val[x]=min(val[x],z);
	}
	ll qry(ll l,ll r,ll x,ll y,ll rt){
		if(y<l||x>r||l>r) return ee;
		if(x<=l&&r<=y) return val[rt]; ll mid=(l+r)>>1;
		return min(qry(l,mid,x,y,rt<<1),qry(mid+1,r,x,y,rt<<1|1));
	}
}tree;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		cin>>n; ans=0;
		for(int i=1;i<=n;i++) pre[i]=vis[i]=0,f[i]=cur[i]=mn[i]=ee;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(i<b[i]) vis[b[i]]=i,pre[i]=pre[b[i]],pre[b[i]]=i;
		}
		tree.build(1,n,1);
		for(int i=1;i<=n;i++){
			if(vis[i]) f[i]=min(mn[i]+tree.qry(1,n,vis[i],i-1,1),cur[i]);
			if(i==1) f[i]=0;
			cur[b[i]]=min(cur[b[i]],mn[b[i]]+tree.qry(1,n,pre[i],i-1,1));
			mn[b[i]]=min(mn[b[i]],a[i]);
			tree.upd(i,f[i]);
		}
		for(ll i=1,s=0;i<=n;i++) s+=a[i],ans=max(ans,s-f[i]);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Introl (赞：1)

# CF2023B/CF2024D
## 题意分析
首先我们可以发现，在第 $i$ 个点上时，所得的得分为从 $1$ 到 $i$ 之和减去跳过的问题。所以此题可以转化为求跳过的题目的最小值。所以答案就是

$$ans=\max_{i=1}^{n}(sum_i-dis_i)$$

其中的 $sum_i$ 表示从 $1$ 到 $i$ 的前缀和，$dis_i$ 表示从 $1$ 到 $i$ 的代价最小值。

关于如何求 $dis_i$，我们可以建图跑最短路，对 $i\rightarrow i-1$ 建边，权值为 $0$，对 $i\rightarrow b_i$ 建边，权值为 $a_i$。之后通过最短路求出 $dis_i$，然后枚举答案即可。
## Code
```cpp
#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define ONLINE_JUDGE
#define MULTI_CASES
#define endl '\n'
const int MaxN = 4e5+100;
const int INF = 1e15;
const int mod=212370440130137957ll;
int T=1, N, M;
// int dis[MaxN];
vector<pair<int,int>>G1[MaxN];
struct Dijkstra{
	int d[MaxN], vis[MaxN];
	struct Point {
		int id, x;
		inline bool operator<(const Point &aa)const {
			return x > aa.x;
		}
	};
	priority_queue<Point>q;
	inline void solve(int S) {
		for(int i = 1; i <= N; i++) d[i] = INF, vis[i] = 0;

		d[S] = 0;
		q.push((Point){ S, 0 });
		while(!q.empty()) {
			auto [x, w] = q.top(); q.pop();
			if (vis[x]) continue;
			vis[x] = 1;
			for(auto it : G1[x]) {
				int y = it.first;
				int z = it.second;
				if(d[x] + z < d[y]) {
					d[y] = d[x] + z;
					if(!vis[y])  q.push((Point){ y, d[y] });
				}
			}
		}
	}
};
inline void Solve()
{
	cin>>N;
    // vector<pair<int,int>> G1[MaxN];
    vector<int>sum(N+1);
    vector<int>a(N+1);
    for(int i=1;i<=N;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
        if(i!=1)
            G1[i+1].push_back(make_pair(i,0));
    }
    for(int i=1;i<=N;i++){
        int x;
        cin>>x;
        G1[i].push_back(make_pair(x,a[i]));
    }
    Dijkstra dij;
    dij.solve(1);
    int ans=0;
    for(int i=1;i<=N;i++){
        // cout<<dij.d[i]<<" ";
        ans=max(ans,sum[i]-dij.d[i]);
        G1[i].resize(0);
    }
    cout<<ans<<endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

#ifdef MULTI_CASES
    cin >> T;
    while (T--)
#endif
       Solve();
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

---

## 作者：hh弟中弟 (赞：1)

考虑最后的决策一定是走到一个地方后不再跳跃，直接从当前位置走到 $0$，这时获得的贡献就是这个位置的前缀和减去不能获得的价值和，想要让到达每个位置时不能获得的价值和最小。考虑连边最短路，首先有 $i$ 连向 $i-1$，边权为 $0$，然后有 $i$ 连到 $b_i$，边权为 $a_i$ 表示损失了 $a_i$ 的价值。跑一遍最短路后 $\max(sum_i-dis_i)$ 就是答案。

---

## 作者：naroto2022 (赞：0)

# CF2023B 题解

### 题面

[原题传送门](https://codeforces.com/problemset/problem/2023/B)

### 题意

有 $n$ 个物品，每个物品有 $a_i$ 的价值和一个参数 $b_i$，初始每个物品都是未解锁的，只有第一个物品是解锁的。

对于第 $i$ 个物品有以下三种操作选一种。

1. 如果这个物品没有被解锁，结束整个过程。
2. 将第 $i+1\sim b_i$ 设为已解锁的。
3. 获得 $a_i$ 的价值，然后将 $i$ 加 $1$。

求出最后获得价值的最大值。

### 思路

设 $dp_i$ 是从 $i$ 开始到 $n$ 的最大金币数量，于是有。

$$\begin{aligned}dp_i=\max(a_i,\max_{i+1\leqslant j\leqslant b_i} dp_j+\sum_{k=i+1}^{j-1}a_k)\end{aligned}$$

直接打是 $O(n^2)$ 的，这是不够的，考虑优化。

把式子拆开会发现一次转移相当于如下三个步骤。

1. $i+1\sim b_i$ 区间查询 $dp$ 的最大值。
2. $i+1\sim n$ 的区间加 $a_i$。
3. $i$ 单点加 $dp_i$。

于是就可以用上线段树来优化，最终的时间复杂度为 $O(n\log n)$ 的。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=5e5+5;
ll n,a[MN],dp[MN],b[MN];
struct tree{ll l,r,num,tag;}t[MN<<2];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void build(ll p, ll l, ll r){
    t[p].l=l;t[p].r=r;t[p].num=t[p].tag=0;
    if(l==r) return;
    ll mid=l+r>>1;
    build(ls,l,mid);build(rs,mid+1,r);
    t[p].num=max(t[ls].num,t[rs].num);
}
void pushdown(ll p){
    if(t[p].tag){
        t[ls].tag+=t[p].tag;t[rs].tag+=t[p].tag;
        t[ls].num+=t[p].tag;t[rs].num+=t[p].tag;
        t[p].tag=0;
    }
}
void change(ll p, ll l, ll r, ll v){
    if(l<=t[p].l&&t[p].r<=r){
        t[p].num+=v;t[p].tag+=v;
        return;
    }
    pushdown(p);
    ll mid=t[p].l+t[p].r>>1;
    if(l<=mid) change(ls,l,r,v);
    if(r>mid) change(rs,l,r,v);
    t[p].num=max(t[ls].num,t[rs].num);
}
ll query(ll p, ll l, ll r){
    if(l<=t[p].l&&t[p].r<=r) return t[p].num;
    pushdown(p);
    ll mid=t[p].l+t[p].r>>1,res=-1e18;
    if(l<=mid) res=max(res,query(ls,l,r));
    if(r>mid) res=max(res,query(rs,l,r));
    return res;
}
void solve(){
    for(int i=1; i<=4*n; i++) t[i].tag=t[i].num=0;//一定不要忘了初始化！
    n=read();build(1,1,n);
    for(int i=1; i<=n; i++) a[i]=dp[i]=read();
    for(int i=1; i<=n; i++) b[i]=read();
    for(int i=n; i>=1; i--){
        ll l=i+1,r=(b[i]==1?0:b[i]);
        dp[i]=max(dp[i],(l<=r?query(1,l,r):0ll));
        change(1,l,n,a[i]);change(1,i,i,dp[i]);
    }
    write(dp[1]);putchar('\n');
}
int main(){
    ll T=read();while(T--)solve();
    return 0;
}
```

---

## 作者：superl61 (赞：0)

[题目传送门](https://codeforces.com/contest/2024/problem/D) 

 [更好的阅读体验](https://www.cnblogs.com/superl61/p/18516678) 

## 题意

从 $1$ 开始决策，若选当前数，则累计贡献 $a_i$ 并跳到 $j$ 位置，$j$ 是 $\lt i$ 且没有决策过（包括选了和没选）的最大位置（操作 $1$）。若不选当前数，则跳转到 $j$ 位置，$j$ 是 $\le b_i$ 且没有决策过（包括选了和没选）的最大位置（操作 $2$）。求最大得分。

## 思路

看到的第一眼以为是动态规划，想了一下觉得 dp 顺序太难搞了，好像也会有后效性。（但据说 dp 能做？）

考场上猜了一个结论：应该可以找一个拐点，到达之后就一直用操作 $1$。下来一看这个结论是对的。

感性理解一下，就是用操作 $2$ 一定是为了能拿更远处的数，当操作 $2$ 不再优后，我们只用操作 $1$ 就是最优的。

设我们用操作 $2$ 放弃了 $p_1,p_2,\dots,p_m$，最后拐点是 $i$。（也是最远点，因为不是最远点的话肯定不优）

所以答案就是 $\max_{1 \le i \le n} presum_i - \sum_{1 \le j \le m}a_{p_j}$。

现在问题转化成了对于每个 $i$，我们要**最小化** $\sum_{1 \le j \le m}a_{p_j}$，即 “放弃贡献”。

这些点并不是按编号大小依次放弃的，也存在顺序问题，考虑构图。

我们连边 $(i \to i - 1, 0), (i \to b_i, a_i)$。最后得到一张带权有向图。

用 Dijkstra​ 跑一遍，$dis_i$ 就是每个拐点最小的 “放弃贡献”。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i(l);i<=(r);++i)
#define G(i,r,l) for(int i(r);i>=(l);--i)
#define int ll
using namespace std;
using ll = long long;
const int N = 4e5 + 5;
const int inf = 0x3f3f3f3f3f3f3f3f;
struct node{
	int v, w, ne;
}e[N << 1];
int T, n, idx = 0;
int a[N], b[N], dis[N], sm[N], first[N];
bool vis[N];
void add(int x, int y, int z){
	e[++ idx] = (node){y, z, first[x]};
	first[x] = idx;
}
priority_queue<pair<int, int> > q;
int solve(){
	cin >> n;
	F(i, 1, n) first[i] = vis[i] = 0, dis[i] = inf;
	dis[1] = idx = 0;

	F(i, 1, n) cin >> a[i], sm[i] = sm[i - 1] + a[i];
	F(i, 1, n) cin >> b[i], add(i, b[i], a[i]);
	F(i, 2, n) add(i, i - 1, 0);
		
	q.push({0, 1});
	while(q.size()){
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = first[u]; i; i = e[i].ne){
			int v = e[i].v, w = e[i].w;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				q.push({-dis[v], v});
			}
		}
	}
	
	int mx = 0;
	F(i, 1, n) mx = max(mx, sm[i] - dis[i]);
	return mx;
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> T;
	while(T --){
		cout << solve() << '\n';
	}
	return fflush(0), 0;
}
```

## 总结

首先是要大胆猜结论，好验证的话就拿小样例验证一下，更重要的是利用这个性质做进一步的处理。

对于转移顺序没有明显规律，视具体数据转移的题，**考虑构图**。

遇到最大化问题，尝试转成最小化问题，或许就会有更多发挥空间，比如用 Dijkstra 跑最短路，二分之类的。

## 参考博客

 [Codeforces Round #980 Editorial - Codeforces](https://codeforces.com/blog/entry/135341) 

 [Codeforces Round 980 div2 个人题解(A~D) - ExtractStars - 博客园](https://www.cnblogs.com/extractstars/p/18488245)

---

## 作者：liugh_ (赞：0)

## [Skipping](https://codeforces.com/contest/2023/problem/B)

首先有两个容易想到的结论：

1. 若 $b_i\le i$ 则 skip 一定不优。
2. 每次 skip 到达的点一定在之前到达的所有点的右边。

这启发我们得出最关键的一个结论：

- 最终访问过的点一定构成一个前缀。

那么我们实际要求的就是一个前缀中没有 skip 的点的点权和，这些点不连续，于是考虑容斥，用前缀和减去 skip 的点的点权。问题转化为快速求出到达这个前缀的右端点的最小代价。结合第 $1,2$ 条结论，我们知道 skip 的过程一定是跳到一个点，往回走一段路，再跳到更右边的一个点……往回走没有代价，而在 $i$ skip 需要 $a_i$ 的代价，这启发我们建图跑最短路，每个点 $i$ 连边 $i\to i-1$，且若 $b_i>i$ 则连边 $i\to b_i$。记 $sum_i=\sum_{j=1}^{i} a_j$，设 $dis_i$ 为 $1$ 到 $i$ 的最短路，那么有 $ans=\min_{i=1}^{n} sum_i-dis_i$。时间复杂度 $O(n\log n)$。

---

## 作者：zengziqvan (赞：0)

~~听说比赛前几天发题解可以 RP++，来试一试。~~

考虑到达每个点时的两种情况：

- 停住不动，老老实实开始往前做题。

- 太难不做往 $b_i$ 跳。

跳过的题就不能再跳了。

注意到跳到第 $i$ 个题目后，第 $i$ 题目前面的所有没被做过的题目就都可以做了。

而最优解一定是全部做上，可以前缀和预处理。

问题转换成怎样跳到 $i$，使得跳过的题目总代价最小。

考虑建图跑最短路。

如何建图？

我们发现，从 $i$ 跳到 $i-1$ 代价显然为 $0$，因为可以做上 $i$ 后直接往前走。

至于跳过一个题，从 $i$ 可以跳到 $b_i$，直接从 $i$ 向 $b_i$ 连一条长度为 $a_i$ 的边即可。

在这里，边权即为走这条边需要的代价。

非负权图，最短路可以直接使用 Dijkstra，自然满足不重复走点的限制。

复杂度 $O(n\log n)$。

```c++
const int N=4e5+10;
int n,a[N],b[N],dis[N],vis[N],s[N];
vector<pair<int,int> >e[N];
void Dijkstra() {
	priority_queue<pair<int,int>>q;
	FOR(i,0,n) dis[i]=1e18,vis[i]=0;
	dis[1]=0;
	q.push(mkp(0,1));
	while(q.size()) {
		int x=q.top().se;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(auto o:e[x]) {
			int y=o.fr,z=o.se;
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(mkp(-dis[y],y));
			}
		}
	}
}
void solve() {
	cin>>n;
	FOR(i,1,n) {
		a[i]=read();
		e[i].pb(mkp(i-1,0));
	}
	FOR(i,1,n) {
		b[i]=read();
		e[i].pb(mkp(b[i],a[i]));
	}
	Dijkstra();
	FOR(i,1,n) s[i]=s[i-1]+a[i];
	LL ans=0;
	FOR(i,0,n) cmax(ans,s[i]-dis[i]);
	cout<<ans<<"\n";
	FOR(i,1,n) e[i].clear();
} 
main() {
	int t=read();
	while(t--) solve();
	return 0;
}
```

---

