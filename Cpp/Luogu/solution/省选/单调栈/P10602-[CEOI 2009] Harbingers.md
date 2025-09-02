# [CEOI 2009] Harbingers

## 题目描述

给定一颗树，树中每个结点有一个邮递员，每个邮递员要沿着唯一的路径走向 capital（$1$ 号结点），每到一个城市他可以有两种选择：

1. 继续走到下个城市；
2. 让这个城市的邮递员替他出发。

每个邮递员出发需要一个准备时间 $W_i$，他们的速度是 $V_i$，表示走一公里需要多少分钟。现在要你求出每个城市的邮递员到 capital 的最少时间（不一定是他自己到 capital，可以是别人帮他）？

## 说明/提示

对于 $20\%$ 的数据，$N\leq 2500$；

对于 $50\%$ 的数据，树是一条链；

对于所有数据，$3\leq N\leq 10^5$，$0\leq W_i,V_i\leq 10^9$，每条边长度不超过 $10^4$。

## 样例 #1

### 输入

```
5
1 2 20
2 3 12
2 4 1
4 5 3
26 9
1 10
500 2
2 30```

### 输出

```
206 321 542 328```

# 题解

## 作者：xtzqhy (赞：6)

双倍经验：[P2305 [NOI2014] 购票](https://www.luogu.com.cn/problem/P2305)

题解里竟然没有出栈序写法，我来写一篇。

首先列出朴素的 DP 式：
$$
f_u=\min_{v \in pre_u} f_v+v_u(dis_u-dis_v)+w_u
$$
拆开以后发现是个一次函数，直接李超树维护。

但是是链查，难道要树剖加树套树？3 个 $\log$ 难以接受。

这里介绍一个 trick：**出栈序**，就是每个节点 $\operatorname{dfs}$ 时出栈的时间戳。设时间戳为 $T_i$，如果 $u$ 能直接到 $v$，那么直接查 $[T_u,T_v]$ 就是对的，因为区间内不在路径上的点一定还没被更新到。

原题题解区没有对此给出说明，只是说画图可知。个人感性理解了一下，大概是因为按原顺序 $\operatorname{dfs}$，那么当前在的点一定是所有还没有更新的点中出栈序最小的，那么区间内不在路径上的点一定还没被更新到，所以直接查是正确的。

注意这道题要离散化横坐标（本人因为离散化写错调了半天）。

### Code
```cpp
#include"bits/stdc++.h"
#define re register
#define int long long
#define k(i) (-t[(i)].dis)
#define b(i) (f[(i)])
using namespace std;
const int maxn=1e6+10,inf=1e18;
int n,len,cnt,tim,tot,segcnt;
int v[maxn],w[maxn],head[maxn],f[maxn],c[maxn];
struct edge{
	int to,nxt,w;
}e[maxn<<1];
struct node{
	int dis,out;
}t[maxn];
struct lct{
	int ls,rs,id;
}tr[maxn<<1];
struct line{
	int k,b;
}lin[maxn];
struct tree{
	int rt;
}root[maxn<<2];
inline void add(int u,int v,int w){
	++cnt;
	e[cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
inline int calc(int x,int id){return lin[id].k*c[x]+lin[id].b;}
inline void dfs1(int u,int fa){
	for(re int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		t[v].dis=t[u].dis+e[i].w;
		dfs1(v,u);
	}
	t[u].out=++tim;
}
inline void add(int x){
	++tot;
	lin[tot].k=k(x);
	lin[tot].b=b(x);
}
inline void update(int l,int r,int id,int &p){
	if(!p) p=++segcnt;
	int mid=(l+r)>>1;
	if(calc(mid,id)<calc(mid,tr[p].id)) swap(id,tr[p].id);
	if(calc(l,id)<calc(l,tr[p].id)) update(l,mid,id,tr[p].ls);
	if(calc(r,id)<calc(r,tr[p].id)) update(mid+1,r,id,tr[p].rs);
}
inline void update(int l,int r,int pos,int id,int p){
	update(1,len,id,root[p].rt);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) update(l,mid,pos,id,p<<1);
	else update(mid+1,r,pos,id,p<<1|1);
}
inline int query(int l,int r,int pos,int p){
	if(!p) return inf;
	int mid=(l+r)>>1;
	int res=calc(pos,tr[p].id);
	if(l==r) return res;
	if(pos<=mid) return min(res,query(l,mid,pos,tr[p].ls));
	else return min(res,query(mid+1,r,pos,tr[p].rs));
}
inline int query(int l,int r,int L,int R,int p,int pos){
	if(l>=L&&r<=R) return query(1,len,pos,root[p].rt);
	int mid=(l+r)>>1,res=inf;
	if(L<=mid) res=min(res,query(l,mid,L,R,p<<1,pos));
	if(R>mid) res=min(res,query(mid+1,r,L,R,p<<1|1,pos));
	return res;
}
inline void dfs(int u,int fa){
	if(u!=1) f[u]=query(1,n,t[u].out,t[1].out,1,v[u])+t[u].dis*c[v[u]]+w[u];
	add(u);
	update(1,n,t[u].out,tot,1);
	for(re int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(re int i=1,u,v,w;i<n;++i) cin>>u>>v>>w,add(u,v,w),add(v,u,w);
	for(re int i=2;i<=n;++i) cin>>w[i]>>v[i];
	for(re int i=0;i<=n;++i) lin[i].b=inf;
	for(re int i=1;i<n;++i) c[i]=v[i+1];
	sort(c+1,c+n-1+1);
	len=unique(c+1,c+n-1+1)-(c+1);
	for(re int i=2;i<=n;++i) v[i]=lower_bound(c+1,c+len+1,v[i])-c;
	dfs1(1,0);
	dfs(1,0);
	for(re int i=2;i<=n;++i) cout<<f[i]<<" ";
	return 0;
}
```

---

## 作者：win114514 (赞：3)

小清新数据结构优化 dp。

### 思路

考虑基本的 dp 式。

$$\begin{aligned}
f_{x}&=w_{x}+\max_{i 是 x 的祖先}v_{x}\times (dep_{x}-dep_{i})+f_i\\
&=w_{x}+v_{x}\times dep_{x}+\max_{i 是 x 的祖先}-dep_{i}\times v_{x}+f_i
\end{aligned}$$

发现 $-dep_{i}\times v_{x}+f_i$ 是一次函数形式。

可以用李超树优化。

由于李超树是严格 $O(\log n)$，所以肯定支持撤回。

我们只需要遍历一遍即可。

时间复杂度 $O(n\log n)$。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/17 07:47:35
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1e5 + 10;
const int I = 1e9;

int n, ct, tp, tt, rt;
int w[N], v[N], f[N], dep[N], head[N];
int t[N << 5];
int ls[N << 5];
int rs[N << 5];
int*s1[N << 5];
int s2[N << 5];
struct edge {
  int to, nxt, val;
} e[N << 1];
struct line {
  int k, b;
  inline int get(int x) { return k * x + b; }
} d[N];

inline void add(int x, int y, int z) {
  e[++ct] = {y, head[x], z}, head[x] = ct;
  e[++ct] = {x, head[y], z}, head[y] = ct;
}
inline void bak(int t) {
  while (tp > t) *s1[tp] = s2[tp], tp--;
}
inline void evl(int&x, int y) {
  ++tp, s1[tp] = &x, s2[tp] = x, x = y;
}
inline void upd(int&p, int l, int r, int x) {
  if (!p) p = ++tt;
  if (!t[p]) return evl(t[p], x);
  if (l == r) return d[t[p]].get(l) > d[x].get(l) ? evl(t[p], x) : void();
  int mid = (l + r) >> 1, cur = t[p];
  if (d[t[p]].get(mid) > d[x].get(mid)) evl(t[p], x), x = cur;
  if (d[t[p]].get(l) > d[x].get(l)) upd(ls[p], l, mid, x);
  if (d[t[p]].get(r) > d[x].get(r)) upd(rs[p], mid + 1, r, x);
}
inline int ask(int p, int l, int r, int x) {
  if (!p || !t[p]) return 1e18;
  int mid = (l + r) >> 1, num = d[t[p]].get(x);
  if (mid >= x) num = min(num, ask(ls[p], l, mid, x));
  if (mid <  x) num = min(num, ask(rs[p], mid + 1, r, x));
  return num;
}
inline void dfs(int now, int fa) {
  if (now != 1) {
    f[now] = w[now] + v[now] * dep[now] + min(0ll, ask(rt, 0, I, v[now]));
    d[now] = {-dep[now], f[now]};
    upd(rt, 0, I, now);
  }
  int tim = tp;
  for (int i = head[now]; i; i = e[i].nxt) {
    if (e[i].to == fa) continue;
    dep[e[i].to] = dep[now] + e[i].val;
    dfs(e[i].to, now);
    bak(tim);
  }
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  fro(i, 1, n - 1) {
    int a, b, c;
    cin >> a >> b >> c;
    add(a, b, c);
  }
  fro(i, 2, n) cin >> w[i] >> v[i];
  dfs(1, 0);
  fro(i, 2, n) cout << f[i] << " ";
  return 0;
}
```

---

## 作者：huhangqi (赞：2)

我们可以考虑使用动态规划来解决。

在线性情况下，我们可以直接将状态设为 $dp_i$ 表示走到 $i$ 号点的时候的最小路程。

可以得到状态转移方程：

$$$
dp_i=\min(dp_j+(l_i-l_j)\times v_i+s_i)
$$$

其中 $l_i$ 表示 $i$ 号点到根节点的距离，可以直接预处理或者在深搜时处理。

此时我们的时间复杂度是 $O(n^2)$ 无法通过，而且还需要转化为树状。

先考虑如何减小时间复杂度，我们会发现这条式子明显可以使用斜率优化。

由于每个节点选择值不具有单调性，我们不考虑使用单调队列，而是选择单吊栈和二分。

接着我们需要转为树状图，只需要在每一个节点的查询结束以后，将这个栈改为原本的情况即可。

但是由于我们维护的是一个单调栈，所以可能被删掉的数量会比较多，可能会超时。

所以我们再在单调栈里面二分出要删掉的位置，同时修改要修改位置的值和长度，并将被修改的值和原长度记录下来。

在回溯时，我们只需要再次修改长度和这个位置的值即可。

也就是说原数字仍然保留在栈中，但是不在范围内，所以不需要重新赋值。

最后注意在比较斜率时可能会超过爆掉。

代码：

```cpp
/*
dp[i]=min(dp[j]+(l[i]-l[j])*v[i])+s[i]
x<y
y better
dp[x]-l[x]*v[i]>dp[y]-l[y]*v[i]
Y[x]=dp[x]
X[x]=l[x]
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,st[100005],top,s[100005],v[100005],dp[100005],x[100005],y[100005],l[100005],b[100005];
struct P{
	int x,y;
};
vector<P> e[100005];
bool check(int i,int j,int k){
	return (__int128)(y[i]-y[j])*(x[j]-x[k])<=(__int128)(y[j]-y[k])*(x[i]-x[j]);
}
int calc(int i,int j){
	return dp[j]+(l[i]-l[j])*v[i]+s[i];
}
pair<int,int> push(int x){
	int now=top,tmp,l=1,r=top;
	while(l<r){
		int mid=l+r>>1;
		if(check(x,st[mid+1],st[mid]))r=mid;
		else l=mid+1;
	}
	top=l;
	tmp=st[++top],st[top]=x;
	return {now,tmp};
}
void reset(int x,int y){
	st[top]=y;
	top=x;
}
int find(int v){
	int l=1,r=top;
	while(l<r){
		int mid=l+r>>1;
		if(calc(v,st[mid])>=calc(v,st[mid+1]))l=mid+1;
		else r=mid;
	}
	return st[l];
}

void dfs(int p,int fa,int sum){
	l[p]=sum;
	dp[p]=calc(p,find(p));
	x[p]=l[p];
	y[p]=dp[p];
	pair<int,int> tmp2=push(p);
	for(P i:e[p])if(i.x!=fa)dfs(i.x,p,sum+i.y);
	reset(tmp2.first,tmp2.second);
}
signed main(){
	cin>>n;
	for(int i=1,a,b,c;i<n;i++){
		cin>>a>>b>>c;
		e[a].push_back({b,c});
		e[b].push_back({a,c});
	}
	for(int i=2;i<=n;i++)cin>>s[i]>>v[i];
	dfs(1,0,0);
	for(int i=2;i<=n;i++)cout<<dp[i]<<' ';
	return 0;
}
``````

---

## 作者：XFlypig (赞：2)

单调栈斜率优化。

贪心不会，那就 DP 一下。

## 基本 DP 式

$\begin{aligned}
f_{x}
&=w_{x}+\max_{i 是 x 的祖先}v_{x}\times (dep_{x}-dep_{i})+f_i\\
&=w_{x}+v_{x}\times dep_{x}+\max_{i 是 x 的祖先}-dep_{i}\times v_{x}+f_i
\end{aligned}$

咳咳，这是从另一篇题解哪里拷过来的，因为写的太好的，所以~~抄袭~~借鉴一下，这不重要，重要的是怎么维护。

这个式子就是枚举当前点走到哪个祖先然后换人。

先不管 max，移项，得到一个一次函数转移式，非常明显的斜率优化。

类似于 $y=k \times x+b$，其中 $y$ 是 $f_i$，$k$ 是 $v_x$，$x$ 是 $dep_i$，$b$ 是 $f_x-w_x-v_x\times dep_x$。

要求截距最小，所以维护下凸包，加入的点横坐标单增，询问无单调性，对于普通问题大概就是一个二分找点单 log 复杂度。

这里的维护方式选择用单调栈，效率不错，500ms 左右。

## 单调栈维护

如果是一般的序列问题，单调队列维护即可，如果是树，也可以想到用栈维护到祖先的一条路径。

但问题在于这里要维护凸包，就要用单调栈，那就是均摊复杂度，那回溯时的复杂度就会爆炸（70pts）。

所以我们不能真的做单调栈，但这个栈又必须得单调，不然转移个嘚。

因为要回溯，所以这个栈大概率还是要保留到根的所有点。

那单调性怎么办？没逝，虽然栈不单调，但我们可以告诉转移方程，这个栈是单调的！放心转移！~~啪！~~

~~单调栈本质上就是一个单调的栈~~，也就是栈里某个结点，它下面的结点就是它前面第一个比它大/小的结点，这很像一个指针，所以我们维护的栈并不单调，但我们同时维护一个指针，指向前面第一个比他大/小的结点，那我们从栈顶开始沿指针走的话，路径就是单调栈了。

所以我们以此来维护这个栈，维护 $pre_i$ 表示栈中第$i$个结点，它指向前面的哪个结点，$nxt_i$ 表示**当前**谁指向 $i$，虽然有多个，但我们只要**当前**单调栈中指向它的那个，$g_{i,j}$ 表示 $i$ 在单调栈中向栈底走 $2^j$ 步走到谁，注意这几个数组的下标和值都是指当前在栈中的位置，这三个数组都要在 dfs 中实时维护。

最后转移式用倍增跳一跳找到转移点，再维护下单调栈也就是那几个数组就行了，然后回溯时除了弹栈，别忘了把修改过的 $nxt$ 数组改回来，因为他要的是**当前**单调栈谁指向它。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define int long long

using namespace std;

const int N = 100010, M = N << 1;

int n;
int w[N], v[N];
int h[N], e[M], ew[M], ne[M], idx;
int dep[N], q[N], f[N];
int g[N][17], pre[N], nxt[N];
int stk[N], top;

int read()
{
    char c;
    while (c = getchar(), c < '0' || c > '9');
    int t = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
        t = (t << 3) + (t << 1) + c - '0';
    return t;
}

void add(int a, int b, int c)
{
    e[idx] = b, ew[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int p)
{
    if (u != 1)
    {
        int pos = top;
        for (int k = 16; k >= 0; k -- )
        {
            int t = g[pos][k];
            if (!t) continue;
            if ((double)(f[stk[nxt[t]]] - f[stk[t]]) > (double)v[u] * (dep[stk[nxt[t]]] - dep[stk[t]]))
                pos = g[pos][k];
        }
        f[u] = w[u] + f[stk[pos]] + (dep[u] - dep[stk[pos]]) * v[u];
    }
    
    int pos = top;
    for (int k = 16; k >= 0; k -- )
    {
        int t = g[pos][k];
        if (!t) continue;
        if ((double)(f[u] - f[stk[nxt[t]]]) * (dep[stk[nxt[t]]] - dep[stk[t]])
            < (double)(f[stk[nxt[t]]] - f[stk[t]]) * (dep[u] - dep[stk[nxt[t]]])) pos = t;
    }
    
    stk[ ++ top] = u, pre[top] = g[top][0] = pos;
    int t = nxt[pos]; nxt[pos] = top;
    for (int k = 1; k <= 16; k ++ )
        g[top][k] = g[g[top][k - 1]][k - 1];
    
    for (int i = h[u]; ~i; i = ne[i])
    {
        int ver = e[i];
        if (ver == p) continue;
        dep[ver] = dep[u] + ew[i];
        dfs(ver, u);
    }
    nxt[pos] = t, top -- ;
}

signed main()
{
    n = read();
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }
    for (int i = 2; i <= n; i ++ )
        w[i] = read(), v[i] = read();
    
    dfs(1, 0);
    
    for (int i = 2; i <= n; i ++ )
        printf("%lld ", f[i]);
    
    return 0;
}

```

---

## 作者：MerlinLee (赞：1)

朴素 dp 大约就是 $f_x=f_y+v+x\times (d_x-d_y)+s_x$，y 是 x 的祖先。

当然，这个式子可以斜率优化，在以 $d_y$ 为横坐标，$f_y$ 为纵坐标的坐标系中，斜率为 $v_x$。

我们应该用单调栈维护一个到根的树链。由于回溯的时候 $v_x$ 不一定单调，取 $f_x$ 的 dp 值的时候应该在完整的凸壳上进行一个二分。

插入决策点时，按照普通序列上的斜率优化弹栈（朴素）。很多人的问题是回溯还原栈状态的复杂度，其实你真正修改的值只有插入进去的位置，如果你没有使用 STL 的话弹栈的操作实际上是没有进行的，他们保留在栈中，只需要将栈顶指针还原即可，每次回溯的个数是 $O(1)$ 级别的。

实际插入决策点时，因为时间复杂度的问题需要二分插入位置。如果你以乘代除，注意开 __int128。
```cpp
#include<bits/stdc++.h>
#define cmin(x, y) x = std::min(x, y)
#define cmax(x, y) x = std::max(x, y)
#define fors(i, l, r, ...) for(int i = (l), REP##i = (r), ##__VA_ARGS__; i <= REP##i; ++i)
#define dfors(i, r, l, ...) for(int i = (r), REP##i = (l), ##__VA_ARGS__; i >= REP##i; --i)
typedef long long ll;
int n, q[100100], l = 1, r;
ll f[100100], v[100100], s[100100], d[100100];
std::vector<std::pair<int, ll>> e[100100];
void pre_dfs(const int x, int fa) {
    for(const auto [y, w] : e[x]) if(y != fa) d[y] = d[x]+w,pre_dfs(y, x);
}
ll up(const int i, const int j) { return f[j]-f[i]; }
ll down(const int i, const int j) { return d[j]-d[i]; }
ll cal(const int i, const int j) { return f[j]+v[i]*(d[i]-d[j])+s[i]; }
int bisect_optimal_decision(const ll k) {
    int l = ::l, r = ::r, res = l; l++;
    for(int mid; l <= r;) {
        mid = (l+r)>>1;
        if(up(q[mid-1], q[mid]) <= (__int128)k*down(q[mid-1], q[mid])) l = mid+1,res = mid;
        else r = mid-1;
    }
    return q[res];
}
int bisect_insert_position(const int x) {
    int l = ::l, r = ::r, res = l; l++;
    for(int mid; l <= r;) {
        mid = (l+r)>>1;
        if((__int128)up(q[mid-1], q[mid])*down(q[mid], x) <= (__int128)up(q[mid], x)*down(q[mid-1], q[mid])) l = mid+1,res = mid;
        else r = mid-1;
    }
    return res;
}
void dp_dfs(const int x, const int fa) {
    if(x != 1) f[x] = cal(x, bisect_optimal_decision(v[x]));
    int _r = r, t, tt;
    r = bisect_insert_position(x);
    t = r+1,tt = q[r+1],q[++r] = x;
    for(const auto [y, w] : e[x]) if(y != fa) dp_dfs(y, x);
    q[t] = tt,r = _r;
}
signed main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n;
    fors(i, 1, n-1, x, y, z) {
        std::cin >> x >> y >> z;
        e[x].emplace_back(y, z);
        e[y].emplace_back(x, z);
    }
    fors(i, 2, n) std::cin >> s[i] >> v[i];
    pre_dfs(1, 0),dp_dfs(1, 0);
    fors(i, 2, n) std::cout << f[i] << " \n"[i == n];
    return 0;
}

```

---

## 作者：CQ_Bab (赞：0)

# 思路
首先可以列出一个转移方程式，我们设 $f_i$ 表示 $i$ 走到 $1$ 的最短时间，那么 $f_i=\min(f_l+(dep_i-dep_l)\times v_i)$ 然后你发现这个东西是 $n^2$ 的，考虑优化，我们发现这个式子很符合一次函数，所以我们把它打开变成 $f_i=\min(f_i,f_l+dep_i\times v_i-dep_l\times v_i)$ 那么我们发现每次查询都是查询一条到根节点的路径上这个东西的最小值直接上可持久化李超线段树即可。
# 代码
细节见代码。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=1e5+10,M=1e9+1;
vector<pair<int,int>>v[N];
int idx;
struct line{
	int k,b;
	int id;
};
int calc(int x,line g) {
	return g.k*x+g.b;
}
struct node{
	int l,r;
	line mx;
}tr[N*30];
int rt[N];
int modify(int u,int l,int r,line k) {
	int p=++idx;
	tr[p]=tr[u];
	if(!tr[p].mx.id) {
		tr[p].mx=k;
		return p;
	}
	int l1=calc(l,k),r1=calc(r,k);
	int l2=calc(l,tr[p].mx),r2=calc(r,tr[p].mx);
	if(l2>l1&&r2>r1) {
		tr[p].mx=k;
		return p;
	}
	else if(l2>l1||r2>r1) {
		int mid=l+r>>1;
		int mid1=calc(mid,k),mid2=calc(mid,tr[p].mx);
		if(mid1<mid2) swap(tr[p].mx,k);
//		cout<<l<<' '<<r<<' '<<k.id<<' '<<tr[u].mx.id<<endl;
		l1=calc(l,k),r1=calc(r,k);
		l2=calc(l,tr[p].mx),r2=calc(r,tr[p].mx);
		if(l1<l2) {
//			cout<<"fdafa\n";
			tr[p].l=modify(tr[u].l,l,mid,k);
		}
		if(r1<r2) tr[p].r=modify(tr[u].r,mid+1,r,k);
	}
	return p;
}
int Ans(int u,int l,int r,int x) {
	if(!tr[u].mx.id) return 1e18;
	int res=calc(x,tr[u].mx);
	if(l==r) return res;
	int mid=l+r>>1;
	if(mid>=x) res=min(res,Ans(tr[u].l,l,mid,x));
	else res=min(res,Ans(tr[u].r,mid+1,r,x));
	return res;
}
int dis[N],w[N],vv[N],f[N],n;
void dfs(int x,int fa) {
	if(x!=1) f[x]=Ans(rt[x],1,M,vv[x])+w[x]+dis[x]*vv[x];
	for(auto to:v[x]) {
		if(to.first==fa) continue;
		line c={-dis[x],f[x],x};
		rt[to.first]=modify(rt[x],1,M,c);
		dis[to.first]=dis[x]+to.second;
		dfs(to.first,x);
	}
}
int si;
void solve() {
	in(n),in(si);
	rep(i,1,n-1) {
		int x,y,z;
		in(x),in(y),in(z);
		v[x].pb({y,z});
		v[y].pb({x,z});
	}
	memset(f,0x3f,sizeof f);
	f[1]=false;
	rep(i,2,n) in(w[i]),in(vv[i]);
	dfs(1,0);
	rep(i,2,n)  printf("%lld ",f[i]);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：Forg1weN (赞：0)

## 分析
[P10602 [CEOI 2009] Harbingers](www.luogu.com.cn/problem/P10602)

可持久化李超树。

发现是“每个点到 $i$ 的最小贡献”，于是从叶子到根的线段树合并行不通，需要用可持久化李超树。记 $f_i$ 表示从 $1$ 到 $i$ 的最小贡献，$dis_i$ 为从根到 $i$ 的距离。有转移：

$f_i=\min\limits_{j \in anc(i)} f_j+w_i+v_i(dis_i-dis_j)$

分离常数可以确定这是一个一次函数，不难确定 $k$ 和 $b$。

初始化相关：在取最小值的题目不难发现区间中永久化的线段需要一个初值，由于是单点查询，与其去写 `build` 函数，不妨在访问到一个区间时，若区间内永久化标记为空，则将该线段赋值上去然后退出区间加。这样子就可以不用遍历整棵树，在需动态开点的线段树中尤其好用。查询时访问到不存在的节点直接返回相反极值即可。

分析复杂度：如果要在 $[l,r]$ 的定义域内插入线段而非全局插入，那么定位到这个区间 $[l,r]$ 本身就需要 $O(\log n)$ 的时间，于是复杂度就是 $O(n\log ^2 n)$ 的。在李超树优化动态规划中，线段的插入往往是在值域内的插入，于是就可以省去查找插入区间的 $O(\log n)$，复杂度是 $O(n\log n)$ 的。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
const int V=1e9;
const double INF=1000000000000000000;
const double eps=1e-9;

int n,m,cnt,tot;
ll t[maxn],spd[maxn],dis[maxn];
int s[maxn*2*50],root[maxn];
int lc[maxn*2*50],rc[maxn*2*50];
vector< pair<int,int> >G[maxn];
double f[maxn];
struct line {double k,b;}p[maxn];
#define lson (lc[now])
#define rson (rc[now])
#define mid ((l+r)>>1)
int cp(double x,double y) {
	if(x-y>eps)return -1;
	if(y-x>eps)return  1;
	return 0;
}
double calc(int u,int x) { return p[u].k*x+p[u].b; }
void add(double k,double b) { p[++cnt].k=k,p[cnt].b=b; }
void upd(int &now,int pre,int l,int r,int u) {
	now=++tot;
	s[now]=s[pre];
	if(!s[now]) { s[now]=u; return; }
	int &v=s[now];
	int bmid=cp(calc(u,mid),calc(v,mid));
	if(bmid==1) swap(u,v);
	if(l==r)return;
	int bl=cp(calc(u,l),calc(v,l)),br=cp(calc(u,r),calc(v,r));
	if(bl==1) upd(lson,lc[pre],l,mid,u);
	else lson=lc[pre];
	if(br==1) upd(rson,rc[pre],mid+1,r,u);
	else rson=rc[pre];
}
double query(int now,int l,int r,int x) {
	if(!now) return INF;
	double res=calc(s[now],x);
	if(l==r) return res;
	if(x<=mid) res=min(res,query(lson,l,mid,x));
	else res=min(res,query(rson,mid+1,r,x)); 
	return res;
}
void dfs(int u,int fa) {
	add(-dis[u],f[u]);
	upd(root[u],root[fa],0,V,cnt);
	for(auto [v,w]:G[u]) {
		if(v==fa)continue;
		dis[v]=dis[u]+w;
		f[v]=query(root[u],0,V,spd[v])+t[v]+spd[v]*dis[v];
		dfs(v,u);
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1;i< n;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	for(int i=2;i<=n;i++) scanf("%lld%lld",&t[i],&spd[i]);
	dfs(1,0);
	for(int i=2;i<=n;i++) printf("%.0lf ",f[i]);
	return 0; 
}
```

---

## 作者：free_fall (赞：0)

给定一棵树，树上每个节点（除了 $1$ 号节点）都有一个邮递员，邮递员想将信送到 $1$ 号节点，他要花 $w_i$ 时间准备，每走一个单位长度花费 $v_i$ 时间，他还可以将信交给遇到的邮递员代他送信。求每个节点上的邮递员将信送到 $1$ 号节点所花的最短时间。

树上问题通常转化为序列问题更加方便思考，如果是一条链，我们应该如何解决问题？

设 $i$ 号节点上的邮递员将信送到所花的时间为 $f_i$，$i$ 号节点距离 $1$ 号节点的距离为 $dis_i$。

我们假设当前节点为 $i$，$i$ 节点之前的任意节点 $j$ 的答案已经被计算出，那么我们容易得到以下转移方程：

$f_i=w_i+\min_{\forall j} f_j+(dis_i-dis_j)v_i$

暴力枚举所有 $j$，时间复杂度 $O(n^2)$。

但其实看到这个式子之后，优化已经很显然了，我们把 $j$ 当作最优的那个点，去掉 $\min$，这样式子更好看一点：

$f_i=w_i+f_j+(dis_i-dis_j)v_i$

$f_i=w_i+f_j+dis_i\times v_i-dis_j\times v_i$

$f_i-dis_i\times v_i-w_i=-dis_j\times v_i+f_j$

转化成这个样子之后我们可以将这个问题变成：有许多形式为 $y=k\times x+b$ 的直线，它们的 $k=-dis_j$，$b=f_j$，求一条直线 $x=v_i$ 与这些直线相交的点的纵坐标的最小值 $mi$，那么 $f_i$ 就等于 $mi+dis_i\times v_i+w_i$。

于是我们可以使用李超线段树来维护这些线段，时间复杂度为 $O(n\log n)$。

回到树上，一个邮递员有可能遇到的邮递员只有可能是当前节点到 $1$ 号节点的路径上的，所以对于每一个树上的节点来说，相当于在 $1$ 号节点到它的路径上做序列上一样的操作。

那么问题就变得清晰起来了，我们需要维护 $1$ 号节点到 $i$ 这条路径上的所有线段，于是我们可以利用可持久化李超树，每次加入一条线段就在它父亲节点的李超树基础上增加，查询也是在它的父亲上查询，这样其它无关节点中的线段就不会影响到我们的查询结果。因为李超树使用的也是永久化标记，所以可持久化起来非常方便，时间复杂度还是 $O(n\log n)$。直接描述可能有点抽象，具体内容见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-f;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=1e5+5,M=N*40,inf=0x3f3f3f3f3f3f3f3f;
int n,tot,w[N],v[N],dis[N],f[N];
int a[N],uni;
struct kk{int to,val;};
vector<kk> edge[N];
struct line{
	int k,b;
	int f(int x){return k*x+b;}
}line[N];
int rt[N];
struct LC_tree{
	int t[M],ls[M],rs[M],tot;
	int change(int p,int l,int r,int id){
		int now=++tot,mid=l+r>>1;
		t[now]=t[p],ls[now]=ls[p],rs[now]=rs[p];
		if(line[t[now]].f(a[mid])>line[id].f(a[mid]))swap(t[now],id);
		if(l==r)return now;
		if(line[t[now]].f(a[l])>line[id].f(a[l]))ls[now]=change(ls[p],l,mid,id);
		if(line[t[now]].f(a[r])>line[id].f(a[r]))rs[now]=change(rs[p],mid+1,r,id);
		return now;
	}
	int query(int p,int l,int r,int x){
		if(l==r)return line[t[p]].f(a[x]);
		int mid=l+r>>1,res=line[t[p]].f(a[x]);
		if(x<=mid)res=min(res,query(ls[p],l,mid,x));
		if(mid<x)res=min(res,query(rs[p],mid+1,r,x));
		return res;
	}
}lc;
void dfs(int now,int las){
	if(now!=1)f[now]=lc.query(rt[las],1,uni,v[now])+dis[now]*a[v[now]]+w[now];
	line[++tot]={-dis[now],f[now]};
	rt[now]=lc.change(rt[las],1,uni,tot);//在父亲的基础上增加线段
	for(int i=0;i<edge[now].size();i++){
		int to=edge[now][i].to,val=edge[now][i].val;
		if(to==las)continue;
		dis[to]=dis[now]+val;
		dfs(to,now);
	}
	return;
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		edge[u].push_back({v,w});
		edge[v].push_back({u,w});
	}
	for(int i=2;i<=n;i++){
		w[i]=read(),v[i]=read();
		a[++uni]=v[i];
	}
	sort(a+1,a+uni+1);
	uni=unique(a+1,a+uni+1)-a-1;
	for(int i=1;i<=n;i++)v[i]=lower_bound(a+1,a+uni+1,v[i])-a;
	line[0]={0,inf};
	dfs(1,0);
	for(int i=2;i<=n;i++)printf("%lld ",f[i]);
	printf("\n");
	return 0;
}
```

---

