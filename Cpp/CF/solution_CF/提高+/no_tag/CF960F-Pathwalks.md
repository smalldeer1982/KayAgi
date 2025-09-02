# Pathwalks

## 题目描述

给定 $n$ 个点 $m$ 条边的有向图，可能不连通，可能有重边，也可能会有自环。求最长的路径(可以经过重复节点)，使得这条路径的编号和权值都**严格**单调递增，其中编号指输入的顺序。路径的长度是指经过边的数量。

## 样例 #1

### 输入

```
3 3
3 1 3
1 2 1
2 3 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5
1 3 2
3 2 3
3 4 5
5 4 0
4 5 8
```

### 输出

```
3```

# 题解

## 作者：皎月半洒花 (赞：21)

比较巧的一道题。

考虑这题本质其实是一个有向图上边的 LIS。于是就可以用类似 LIS 的贪心方式来做，只是转移的时候多了一个限制而已。

具体的，对每个 $x$ 维护一个 `map` （或者线段树），存入边权值为 $v$ 时的最长递增路径。考虑每次加进来一条边 $(u,v,w)$，答案就是从 $u$ 的 map 里找出最大的小于 $w$ 的值，根据单调性可知这一定是小于 $w$ 的那个最大值。然后暴力改就好了。不难知道这样做每条边至多被加一次、删一次，复杂度是 $O(m\log n)$ 。


```cpp
#include <map>

#include <cstdio>

#include <algorithm>

using std :: map ;

using std :: lower_bound ;

#define en end
#define be begin

#define lbd lower_bound

const int N = 300010 ;

typedef long long ll ;

int ans ;
int res ;
int n, m ;

map <int, ll> lis[N] ;

int search(int x, int v){
    int ret = 0 ;
    auto p = lis[x].lbd(v) ;
    ret = (p == lis[x].be()) ? 0 : ((-- p) -> second) ; return ret ;
}

int main(){
    scanf("%d%d", &n, &m) ; int x, y, z ;
    for (int i = 1 ; i <= m ; ++ i){
        scanf("%d%d%d", &x, &y, &z) ;
        res = search(x, z) ; ++ res ;
        if (res > search(y, z)){
            auto p = lis[y].lbd(z) ; lis[y][z] = res ;
            for (auto q = p ; q != lis[y].en() ; ){
                if ((q -> second) > res) break ; q = lis[y].erase(q) ;
            }
        }
        ans = std :: max(ans, res) ;
    }
    printf("%d\n", ans) ; return 0 ;
}

```

---

## 作者：Lucifer_Bartholomew (赞：8)

# 线段树模拟
因为题目要求时间和边权严格递增,所以按照时间顺序来处理边,这样就满足且可以保证时间严格递增。

用线段树以图中的点为根,边权大小为键值建树(不是原来的倍增),维护可以取得的最大边数。

对于一条新边(u,v),查询到u的可取最大边数,假设取边(u,v)更新答案并在线段树上对于v更新小于边(u,v)权值的所有点。

最后输出答案即可。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mod 1000000007
#define lson l,m,tre[rt].l
#define rson m+1,r,tre[rt].r
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct tree{
    int l,r,maxn;
}tre[3000005];//建树方式不一样所以空间要开更大,这个大小实测能过
int cnt,rt[100001];//rt[]记录每个点对应的根
inline void pushup(int rt)//上传维护区间最大值
{
    tre[rt].maxn=max(tre[tre[rt].l].maxn,tre[tre[rt].r].maxn);
}
inline void update(int pos,int x,int l,int r,int&rt)
{
	if(!rt)rt=++cnt;//加新点建树
	if(l==r)
	{
		tre[rt].maxn=max(tre[rt].maxn,x);//更新最大值
		return;
	}
	int m=l+r>>1;
	if(pos<=m)update(pos,x,lson); 
	else update(pos,x,rson);
	pushup(rt);
}
inline int query(int L,int R,int l,int r,int rt)//区间最大值查询
{
	if(L>R||!rt)return 0;
	if(L<=l&&r<=R)return tre[rt].maxn;
	int m=l+r>>1,ans=0;
	if(L<=m)ans=query(L,R,lson);
	if(m<R)ans=max(ans,query(L,R,rson)); 
	return ans; 
}
int main()
{
    int n=read(),m=read(),ans=0;
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read(),w=read(),tmp=query(1,w,1,100000,rt[u])+1;//查询
        ans=max(ans,tmp);//更新答案
        update(w+1,tmp,1,100000,rt[v]);//更新
    }
    printf("%d\n",ans);
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：hgzxwzf (赞：4)

第一眼看去很容易想到 LIS 问题，从而想到 DP 去解决这道题。

这个题和 LIS 的区别就是状态转移时还要保证两个点在原图中有边，而且以一个点可以由多个边转移过来，所以我们状态转移方程里要加上一维表示最后的边权。

定义 $dp[i,w]$ 为以 $i$ 结尾，最后一次边权为 $w$ 的最长路径。

对于一条有向边 $(u,v,w)$，有 $dp[v][w]=\max(dp[v][w],dp[u][w\prime]+1)(w\prime<w)$。

如果直接暴力转移的话，我们要暴力枚举 $w\prime$，那时间复杂度和空间复杂度就成了 $O(nm)$，肯定是不可行的。

我们并不需要要枚举 $w\prime$，因为边总共只有 $m$，条，连向一个点的边最多只有 $m$ 条，况且我们只考虑编号比 $(u,v)$ 这条边小的。

我们可以对每个点用 map 维护。

首先在 $map[u]$ 的第一关键字里二分查找 $w$，设指针位置为 $it$，那么 $it-1$ 的第二关键字就是最大的 $dp[u][w]$。

同时我们要维护 $map[v]$ 的第一关键字和第二关键字的双单调性，因为如果存在 $dp[v][w\prime]<dp[v][w]$ 且 $w\prime>w$ 那么 $dp[v][w\prime]$ 肯定不是最优值。

通过维护双单调性，我们也保证了第一步的正确性，同样这么用 map 还有[UVA12161](https://www.luogu.com.cn/problem/UVA12161)，都运用到了 map 第一关键字的自动排序。

## 代码：

```cpp
#include<cstdio>
#include<map>
#include<cstring>
#define rep(x,y,z) for(int x=y;x<=z;x++)
using namespace std;
const int N=1e5+10;
map<int,int>dp[N];
int find(int u,int x)
{
	auto it=dp[u].lower_bound(x);
	return it==dp[u].begin()?0:(--it)->second;
}
int main()
{
	int n,m,ans=0;
	scanf("%d%d",&n,&m);
	rep(i,1,m)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		int res=find(u,k)+1; 
		if(res>find(v,k))
		{
			auto it=dp[v].lower_bound(k);
			dp[v][k]=res;
			while(it!=dp[v].end()&&it->second<=res) dp[v].erase(it++);
		}
		ans=max(ans,res);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：E_huan (赞：3)

## 线段树优化 DP

#### 朴素DP：

题目要求编号和权值都要严格单调，边与边还要首尾相接（否则不叫路径）。编号顺序只要顺着 DP 就能保证。

$f[i]$ 表示考虑前 $i$ 条边，$i$ 号边强制被选的最长路径。转移就是枚举前面每位条边看它的权值和终点是否满足，在满足的状态中取最大值。时间的复杂度 $O(n^2)$。

#### 优化：

发现对于“权值严格单调递增的路径”的条件，其实是对于在值域区间 $[1,k)$ 的、终点是当前边起点的路径 $j$，求 $f[j]+calc(j+1,i)$ 的最大值。如果先不考虑“终点是当前边起点”，转移操作其实就是求区间最大值，这可以线段树维护。但是“终点是当前边起点”怎么保证呢？

可以对于每个点建一颗权值线段树，维护终点是这个点的所有边的 $f$ 值。即第 $u$ 个线段树的第 $i$ 个位置表示终点是 $u$ 且权值是 $i$ 的边的最大 $f$ 值。由于每条边只对应一个线段树上的叶节点，动态开点的时空间复杂度均为 $O(n \log n)$。

每次转移只需要查询自己起点对应的线段树上 $[0,k)$ 区间的最大值就可以了。

#### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010,up=100000;
int n,m;
int ls[N*22],rs[N*22],mx[N*22],rt[N],tot;
int query(int u,int l,int r,int ql,int qr)
{
    if((!u)||ql>qr||l>r) return 0;
    if(ql<=l&&r<=qr) return mx[u];
    int mid=(l+r)>>1,res=0;
    if(ql<=mid) res=query(ls[u],l,mid,ql,qr);
    if(qr>mid) res=max(res,query(rs[u],mid+1,r,ql,qr));
    return res;
}
void modify(int &u,int l,int r,int pos,int v)
{
    if(!u) u=++tot;
    if(l==r) { mx[u]=max(mx[u],v); return;}
    int mid=(l+r)>>1;
    if(pos<=mid) modify(ls[u],l,mid,pos,v);
    else modify(rs[u],mid+1,r,pos,v);
    mx[u]=max(mx[ls[u]],mx[rs[u]]);
}
int main()
{
    scanf("%d%d",&n,&m);
    int a,b,k; 
    while(m--)
    {
        scanf("%d%d%d",&a,&b,&k);
        int f=query(rt[a],0,up,0,k-1)+1;
        modify(rt[b],0,up,k,f);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,mx[rt[i]]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：LlLlCc (赞：3)

如果不考虑编号和权值必须递增，不妨设：

$\large f_x:$ 点$x$为终点最多经过几条边

那么对于边$(u\rightarrow v)$，可以转移：

$\large f_v=f_u+1$

接下来我们考虑编号和权值的递增

首先，编号如果不排序，我们是不需要处理的，因为是按给出的顺序。所以我们只要考虑权值递增即可

对于每个点，我们建一棵线段树，记录终边分别为$0$到$10^5$时的最多经过边数，所以我们只要单点修改和区间查询最大值即可

显然数据规模达到了$10^5$级别，我们要动态开点来优化空间

## code
```
#include<bits/stdc++.h>
#define maxn 100005
#define maxe 20000005
using namespace std;
int n,m,x,y,z,lc[maxe],Mx[maxe],rc[maxe],rt[maxe],Ans,tot;
struct lc{
	int x,y,z;
}e[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline int Get(int &k,int L,int R,int l,int r){
	if (!k) return 0;
	if (L>=l&&R<=r) return Mx[k];
	int mid=L+R>>1,mx=0;
	if (l<=mid) mx=max(mx,Get(lc[k],L,mid,l,r));
	if (r>mid) mx=max(mx,Get(rc[k],mid+1,R,l,r));
	return mx;
}
inline void Change(int &k,int L,int R,int x,int data){
	if (!k) k=++tot;
	if (L==R){Mx[k]=max(data,Mx[k]);return;}
	int mid=L+R>>1;
	if (x<=mid) Change(lc[k],L,mid,x,data);
	else Change(rc[k],mid+1,R,x,data);
	Mx[k]=max(Mx[lc[k]],Mx[rc[k]]);
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++) e[i].x=read(),e[i].y=read(),e[i].z=read();
	for (int i=1;i<=m;i++){
		int Now=Get(rt[e[i].x],0,1e5,0,e[i].z-1)+1;
		Ans=max(Ans,Now);
		Change(rt[e[i].y],0,1e5,e[i].z,Now);
	}
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：Boxxxxxx (赞：2)

[博客链接](https://blog.csdn.net/qq_43804974/article/details/106724228)

**首先，这不是正解，甚至歪的很过分，你还要吸氧，~~但是我就是要发~~。**
根据题意我们可以知道首先要求

 1. 转移的路径编号的转移必须是从小到大
 2. 转移的权值必须从小到大
 3. 一条边的终点转移到另一条边的起点，起点终点需要相同


我的思路是什么呢，这是三个要求，而且头两个要求很二维偏序对不对，那么第三个要求我们可以稍稍强行理解一下一下然后上CDQ分治，毕竟模板的CDQ分治就是三维偏序。

要考虑怎么写CDQ分治，首先这里的瓶颈是什么就是条件三，那我们在CDQ分治的时候就可以和普通的处理不太一样，我们之前的处理都是处理中点之前的修改，回答中点之后的询问，利用树状数组去解决。但是如果在这题我们直接使用树状数组的话会有一个问题，你当前边的权值为V，你在树状数组里找权值小于V的最大值有可能那条边是非法的，就是不能满足条件3.

我们的处理方案是什么呢，就是遍历一遍区间，把所有的点拿出来，按照修改的终点和查询的起点相同的那些路拿出来单独处理，分多次处理，这样树状数组里的都是合法的值都可以转移。然后由于总边数是固定的，所以这样子的操作不会改变复杂度。

由于树状数组的log，所以总复杂度是两个log，但是又由于我们在路上用了很多stl，所以常数有点大，你还得丢人的去吸氧。

```cpp
int B[max_], MC = 1e5 + 7;
inline void Ins(int i, int x) { for (; i <= MC; i += i & -i) B[i] = max(B[i], x); }
inline void Clr(int i) { for (; i <= MC; i += i & -i) B[i] = 0; }
inline int Qur(int i) { int A = 0; for (; i; i -= i & -i) A = max(A, B[i]); return A; }
int N, M,qn;
struct kk {
	int op, id, now, to, val,yuanid;//op = 1;修改 ，op = 0是询问
	kk(){}
	kk(int a, int b, int c, int d, int e,int f) {
		op = a, id = b, now = c, to = d, val = e,yuanid = f;
	}
}node[2 * max_];
queue<kk> que[max_];
set<int> S;
int f[max_];
void dfs(int L, int R) {
	if (L == R)return;
	int mid = (L + R) >> 1;
	dfs(L, mid);
	for (int i = L; i <= R; i++) {
		if (node[i].id <= mid && node[i].op == 1) {//修改
			if (!S.count(node[i].to))S.insert(node[i].to);
			que[node[i].to].push(node[i]);
		}
		if (node[i].id > mid && node[i].op == 0) {//询问
			if (!S.count(node[i].now))S.insert(node[i].now);
			que[node[i].now].push(node[i]);
		}
	}
	for (auto quanzhi : S) {
		set<int> del;
		while (!que[quanzhi].empty()){
			kk tou = que[quanzhi].front(); que[quanzhi].pop();
			if (tou.op == 1) {
				if (!del.count(tou.val))del.insert(tou.val);
				Ins(tou.val, f[tou.yuanid]);
			}
			else {
				int t = Qur(tou.val - 1);
				f[tou.yuanid] = max(f[tou.yuanid], t + 1);
			}
		}
		for (auto to : del) {
			Clr(to);
		}
		del.clear();
	}
	S.clear();
	dfs(mid + 1, R);
}
signed main() {
	N = read(); M = read();
	for (int i = 1; i <= M; i++) {
		f[i] = 1;
		int now = read(), to = read(), val = read();
		++qn;node[qn] = kk(0, qn, now, to, val + 1,i);
		++qn; node[qn] = kk(1, qn, now, to, val + 1,i);
	}
	dfs(1, qn);
	int ans = 0;
	for (int i = 1; i <= M; i++) {
		//cout << f[i] << " ";
		ans = max(ans, f[i]);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：Fzrcy (赞：1)

首先，本题的本质是有向图的 LIS 问题，按照题目输入的顺序依次加边，设 $f_{i,j}$ 表示以 $i$ 结尾，路径权值的最大值为 $j$ 的最长链的长度，有状态转移方程 $f_{i,j}=\max(f_{k,s})+1(k\to i,s<j,val(k\to j)=k)$，直接转移时间空间复杂度直接爆炸，考虑用动态加点线段树维护 $f_{i,j}$，即加入一条 $i\to j$，且权值为 $k$ 的边时，有 $f_{j,k}=\max_{x=0}^{k-1}(f_{i,x})+1$，区间查询即可。时间复杂度为 $O(m\log V)$。[代码](https://codeforces.com/contest/960/submission/204911524)。

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

~~也就是最长上升子序列弄到图上~~

假设节点 $i$ 上面有一个函数 $f_i(x)$ 等于最长的连长度使得这个连终点是 $i$，最后一条边的权值是 $x$。显然 $f_i(x) \le f_i(x+1)$，考虑用 set 维护这个非递减函数。

我们在 set 里维护一些 pair，这个 pair 的第一元素是 $x$ 严格上升，第二元素是 $f_i(x)$ 严格上升。

每一次加入一个新条边对起点 lower bound 找出最好转移位置。然后我们对终点先 insert 一下找到 insert 位置。如果 insert 的指针前面有一个比插入 $f_i(x)$ 大的一个 $f_i(y<x)$，我们现在插入的 $f_i(x)$ 没用，删了。如果已经有一个 $x$ 为插入值并且 $f_i(x)$ 更大，我们插入的没用，删了。现在如果还没删就开始找后面有多少个因为现在插入的元素变没用了，也就是第二元素更小的 pair，用 while 遍历并且删。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

set<pii> ans[100005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int gb = 0;
    int n, m; cin >> n >> m;
    rep1(i, n) ans[i].insert({-1, 0});
    while(m--) {
        int u, v, w; cin >> u >> v >> w;
        int cn = prev(ans[u].lower_bound({w,-1}))->se+1;
        gb = max(gb, cn);
        auto [it, _] = ans[v].insert({w,cn});
        if(next(it) != ans[v].end() && next(it)->fi == w) {
            ans[v].erase(it);
            continue;
        }
        if(it != ans[v].begin() && prev(it)->se >= cn) {
            ans[v].erase(it);
            continue;
        }
        if(it != ans[v].begin() && prev(it)->fi == w) ans[v].erase(prev(it));
        it = next(it);
        while(it != ans[v].end() && cn >= it->se) it = ans[v].erase(it);
    }
    cout << gb << endl;
}


```

---

## 作者：AlicX (赞：1)

## Solution

发现有一个限制条件是无用的：就是按顺序选择边，解决方案是直接安顺去模拟就行。然后只剩下一个限制条件：权值单调递增。接下来设 $f_i$ 表示以第 $i$ 条边结尾的最长路径，更新他只需要在 $1 \sim i-1$ 条边中找到 $f$ 最大的点。因为值域为 $10^5$，所以不需要动态开点。但是我的代码写的是它，码量较少容易实现。

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/CF960F
// CF : https://codeforces.com/problemset/problem/960/F
// AT : 
// FTOJ : 
// Contest : Divide by Zero 2018 and Codeforces Round 474 (Div. 1 + Div. 2, combined)
// Cnblogs : 
// Memory Limit: 250 MB
// Time Limit: 1000 ms 
// 2023/8/1     

#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=30*1e5+10,INF=1e9+7;  
int n,m; 
int cnt=0; 
int rt[N],tr[N];
int ls[N],rs[N]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void pushup(int u){
	tr[u]=max(tr[ls[u]],tr[rs[u]]); 
}
il int add(int u,int l,int r,int x,int w){
	if(!u) u=++cnt; 
	if(l==r){ 
		tr[u]=max(tr[u],w); 
		return u; 
	} int mid=l+r>>1; 
	if(x<=mid) ls[u]=add(ls[u],l,mid,x,w); 
	else rs[u]=add(rs[u],mid+1,r,x,w); 
	pushup(u); return u;  
} 
il int query(int u,int l,int r,int ql,int qr){ 
	if(!u) return 0;  
	if(ql<=l&&r<=qr) return tr[u]; 
	int mid=l+r>>1,w=0; 
	if(ql<=mid) w=query(ls[u],l,mid,ql,qr); 
	if(qr>mid) w=max(w,query(rs[u],mid+1,r,ql,qr)); 
	return w; 
} 
signed main(){ 
	int ans=0; 
	n=read(),m=read();  
	while(m--){ 
		int u=read(),v=read(),w=read(); 
		int x=query(rt[u],0,1e5,0,w-1)+1; 
		rt[v]=add(rt[v],0,1e5,w,x); 
	} for(int i=1;i<=n;i++) ans=max(ans,tr[rt[i]]); printf("%d\n",ans); 
	return 0;
} /* */ 
```


---

## 作者：Gaode_Sean (赞：0)

考虑 dp，设 $f_{x,val}$ 表示最后一个点是 $x$，最后一条边的权值是 $val$ 的路径的最长长度。

则有 $f_{x,val}=\max\limits_{1 \le w \le val-1} (f_{y,w})+1$。

对于该 dp 式，能想到用动态开点线段树来维护。

时间复杂度 $\mathcal{O(n \log n)}$，空间复杂度 $\mathcal{O(n)}$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
struct node{int l,r,ls,rs,x;}t[N<<5];
int n,m,rt[N],ans,tot;
int ask(int &p,int l,int r,int val)
{
	if(!p) return 0;
	if(r<=val) return t[p].x;
	int mid=(l+r)>>1;
	if(val<=mid) return ask(t[p].ls,l,mid,val);
	else return max(ask(t[p].rs,mid+1,r,val),t[t[p].ls].x);
}
void update(int &p,int l,int r,int w,int val)
{
	if(!p) p=++tot;
	t[p].x=max(t[p].x,val);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(w<=mid) update(t[p].ls,l,mid,w,val);
	else update(t[p].rs,mid+1,r,w,val);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		int val=ask(rt[x],1,N-1,z)+1;
		ans=max(ans,val);
		update(rt[y],1,N-1,z+1,val);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Luciylove (赞：0)

直接讲做法罢。

考虑固定最好固定的编号这一维，那么我们记录此时 $f_{u, w}$ 表示走到 $u$ 节点的最大权为 $w$。

那么考虑 $(u, v, w)$ 有如下转移 ：$f_{v, w} \gets f_{u, w'} + 1$。

显然这是一个最长上升子序列的形式，可以用线段树维护，然后需要注意的是这个 $u$ 和 $v$ 不是同一棵树，可以考虑动态开点。

```cpp
// LUOGU_RID: 97498885
#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5, M = 2e5 + 5;

int n, m, tot, ans, rt[N], dp[N], mx[N * 24], ls[N * 24], rs[N * 24];

inline void modify (int & u, int l, int r, int pos, int k) {
    if (! u) u = ++ tot;
    if (l == r) { mx[u] = max(mx[u], k); return ; }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(ls[u], l, mid, pos, k);
    else modify(rs[u], mid + 1, r, pos, k);
    mx[u] = max(mx[ls[u]], mx[rs[u]]);
}
inline int query (int u, int l, int r, int ql, int qr) {
    if (! u) return 0;
    if (ql <= l && r <= qr) return mx[u];
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid) res = max(res, query(ls[u], l, mid, ql ,qr));
    if (qr > mid) res = max(res, query(rs[u], mid + 1, r, ql, qr));
    return res;
}
int main () {
	cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i ++) {
        scanf("%d%d%d", & u, & v, & w);
        dp[i] = query(rt[u], 1, M, 1, w + 1) + 1;
        modify(rt[v], 1, M, w + 2, dp[i]), ans = max(ans, dp[i]);
    }
    cout << ans;
	return 0;
} 
```

---

## 作者：Arghariza (赞：0)

一发 $\mathtt\color{lightgreen}AC$ 祭。

类似图上 $\mathtt{LIS}$，我们考虑 $dp$ 做法。

由于要求边的编号严格递增，于是我们可以令 $f_i$ 表示考虑前 $i$ 条边，必须选第 $i$ 条边的最长满足要求的路径。设 $u_i,v_i$ 分别表示第 $i$ 条边连接的两个节点，$w_i$ 表示其权值。

于是有转移：$f_i=\max\limits_{v_j=u_i,w_j<w_i}\{f_j\}+1$。

暴力 $O(n^2)$，我们考虑用数据结构优化。

你发现这个形式和最长上升子序列非常像，于是考虑维护以每个权值结尾的最长路径长度，由于题目自带的 $v_j=u_i$ 的限制，我们还要对每个点都建出这样的一个数据结构，并查询 $u_i$ 处的值，修改 $v_i$ 处的值。

于是我们需要支持 $n$ 个**区间取 $\min$，单点修改**的数据结构，显然如果不需要 $n$ 个的话我们可以用树状数组解决。但是由于题目需要，使用动态开点权值线段树。复杂度 $O(n\log n)$。

[$\color{lightgreen}\mathtt{AC\ Code}$](https://codeforces.com/contest/960/submission/164438366)

---

## 作者：诚实的抱抱熊 (赞：0)

首先，读题。

题目的意思是寻找到一条经过的边最多的路径，并且 路上的边的路径在**按输入的顺序递增**的同时也**按边的权值递增**。

那么，这个问题不就是 有向图上的最长上升子序列 吗？

既然这样，我们先像最长上升子序列一样 dp 一下。

### 朴素 dp

考虑一个朴素的 dp，设：

$f[i][j]$ 为以点 $i$ 为终点，最后一条边的值为 $j$ 的路径，最多经过多少条边。

显然，对于一条边权为 $w$ 的有向边 $(u,v)$，可以转移：

$f[v][w] = \max \limits_{1 \leq x < w}(f[u][x]) + 1$

这个 dp 的时间复杂度和空间复杂度都是是 $O(N^2)$，显然过不了。

### 优化

我们观察这个 dp 的转移，显然可以被数据结构优化，在这里，我选择线段树。

那么我们对于每个点都开一个维护区间最大值的动态开点权值线段树，直接在线段树上互相转移。

那么，时间复杂度是 $O(n \log n)$ 的。

因为我们使用的是动态开点权值线段树，每次修改最多增加一条长度为 $\log n$ 的节点，那么空间复杂度也是 $O(n \log n)$ 的。

### 代码环节

[指针版](https://www.luogu.com.cn/paste/0hvrswpf)

[数组版](https://www.luogu.com.cn/paste/uj8jw1ge)

---

## 作者：青鸟_Blue_Bird (赞：0)

一道挺考验思维和数据结构能力的题。

首先，假设没有题目中的限制，同时用每条边的终点来代表这条边的话，我们可以轻易地写出 $dp$ 方程:  $dp_v = dp_u + 1$。

然后加入题目中的两个要求：

1. 必须按照顺序来
1. 大小必须单调递增

对于第一个要求，我们可以在转移时直接按照顺序枚举边，这样就可以避免存在编号较大边的状态，方便判断和转移。

对于第二个要求，在转移时，我们就要枚举 $u$ 号点的入边，同时记录**每条入边**带来的 $dp$ 值，然后判断是否符合条件即可转移。但是，口胡简单，怎么实现呢？如果暴力用 $vector$ 对每个点进行存储，而且暴力枚举转移边的话，时间肯定是过不去的。（菊花图）

所以，考虑优化上述操作。 没错，我们可以利用权值线段树 + 动态开点，对每个节点开一棵线段树，对应下标存储权值为 $w$ 的入边的 $dp$ 值，那么时间就可以优化到 $O(mlogw)$ 的级别了。 

上代码：（注意各种细节）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define M 20000005
#define ll long long

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){ if(c == '-') s = -1; c = getchar(); }
	while(isdigit(c)){ x = x * 10 + (c ^ '0'); c = getchar(); }
	a = x * s;
	return ;
}

struct node{   // 存边 
	int u, v, w; 
} t[N];

struct Segment_tree{  // 权值线段树 
	struct node{
		int lc, rc;
		int maxn; 
	} e[M];   // 控制好大小，防止空间挂掉 
	
	#define lson e[o].lc
	#define rson e[o].rc
	int id;
	
	Segment_tree(){
		this -> id = 1; // 初始化为 1 
		return ; 
	}
	
	inline void pushup(int o){
		e[o].maxn = max(e[lson].maxn, e[rson].maxn);
		return ; 
	}
	
	void update(int& o, int l, int r, int x, int k){
		if(!o) o = this->id++;  
		if(l > x || r < x) return ;
		if(l == r && l == x){
			e[o].maxn = max(e[o].maxn, k);
			return ; 
		}
		int mid = l + r >> 1;
		update(lson, l, mid, x, k);
		update(rson, mid + 1, r, x, k);
		pushup(o);
		return ; 
	}
	
	int query(int& o, int l, int r, int in, int end){
		if(!o) return 0;
		if(l > end || r < in) return 0;
		if(l >= in && r <= end) return e[o].maxn;
		int mid = l + r >> 1;
		return max(query(lson, l, mid, in, end), query(rson, mid + 1, r, in, end)); 
	}
	
} tree; 

int n, m; 
int dp[N]; 
int root[N]; 

int main(){
	read(n), read(m);
	for(int i = 1; i <= m; i++)
		read(t[i].u), read(t[i].v), read(t[i].w); 
	for(int i = 1; i <= m; i++){
		int tmp = tree.query(root[t[i].u], 0, 1e5, 0, t[i].w - 1) + 1;     // 注意是从 0 开始查，有权值为 0 的边 
		dp[t[i].v] = max(dp[t[i].v], tmp); 
		tree.update(root[t[i].v], 0, 1e5, t[i].w, tmp);  
	}
	int ans = 0; 
	for(int i = 1; i <= n; i++)
		ans = max(ans, dp[i]); 
	cout << ans << endl;
	return 0; 
}


```

 

---

## 作者：__phiu (赞：0)

## Solution

这题本质上是求一个有向图上的不降最长路径，由于要满足输入顺序，所以依次更新每个点最长路径就好了，设 $f$ 代表每个点为结尾的最长路径，每条边至多更新长度加一，所以我们有式子 $f_v=f_u+1$。

考虑优化查询边权小于这条边的路径，对于每个点，建立权值线段树，每次对于一条边，查询边起点的小于该边权的最长路径，线段树的节点保存长度，按照结尾边作为权值插入，每次更新完再次按照这条边权值插入到边的终点的线段树中。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0' or c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0' and c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}//快读
struct tree{
    int l,r,maxx;
}t[3000005];
int cnt,root[2000050];
void up(int p)
{
    t[p].maxx=max(t[t[p].l].maxx,t[t[p].r].maxx);
}
void update(int &p,int pos,int x,int l,int r)//pos代表结尾边的边权，x代表以这条边结尾的最长路径长度
{
    if(!p)
        p=++cnt;//动态开点
    if(l==r)
    {
        t[p].maxx=max(t[p].maxx,x);
        return ;
    }
    int mid=l+r>>1;
    if(pos<=mid)
        update(t[p].l,pos,x,l,mid);
    else
        update(t[p].r,pos,x,mid+1,r);
    up(p);
}
int query(int p,int l,int r,int L,int R)
{
    if(l>r or !p) return 0;
    if(L<=l and r<=R) return t[p].maxx;
    int mid=l+r>>1,ans=0;
    if(L<=mid) ans=max(ans,query(t[p].l,l,mid,L,R));
    if(R>mid)  ans=max(ans,query(t[p].r,mid+1,r,L,R));
    return ans;
}
signed main(){
    int n=read();int m=read();int ans=0;
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        int w=read();
        int tot=query(root[u],1,100000,1,w)+1;//查询1到w的路径
        ans=max(ans,tot);
        update(root[v],w+1,tot,1,100000);//因为严格小于所以要w+1才能用到
    }
    cout<<ans;
}
```


---

