# Summer Dichotomy

## 题目描述

 $ T $ students applied into the ZPP class of Summer Irrelevant School. The organizing committee of the school may enroll any number of them, but at least $ t $ students must be enrolled. The enrolled students should be divided into two groups in any manner (it is possible that one of the groups will be empty!)

During a shift the students from the ZPP grade are tutored by $ n $ teachers. Due to the nature of the educational process, each of the teachers should be assigned to exactly one of two groups (it is possible that no teacher will be assigned to some of the groups!). The $ i $ -th teacher is willing to work in a group as long as the group will have at least $ l_{i} $ and at most $ r_{i} $ students (otherwise it would be either too boring or too hard). Besides, some pairs of the teachers don't like each other other and therefore can not work in the same group; in total there are $ m $ pairs of conflicting teachers.

You, as the head teacher of Summer Irrelevant School, have got a difficult task: to determine how many students to enroll in each of the groups and in which group each teacher will teach.

## 样例 #1

### 输入

```
10 20
3 0
3 6
4 9
16 25
```

### 输出

```
POSSIBLE
4 16
112
```

## 样例 #2

### 输入

```
1 10
3 3
0 10
0 10
0 10
1 2
1 3
2 3
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：小粉兔 (赞：26)

也就是要把老师分成两组，满足每组的 $[l_i, r_i]$ 的交集，“相加”后与 $[t, T]$ 有交。

如果有三个老师的 $[l_i, r_i]$ 两两无交集，那么就完蛋了，根本没法分组。

否则，如果我们考虑其中一组的人数为 $n_1 = \min \{ r_i \}$，另一组的人数为 $n_2 = \max \{ l_i \}$。

如果 $n_1 \ge n_2$，也就是所有老师的 $[l_i, r_i]$ 两两有交的情况，那么这种情况下每个老师都可以任意选组。

如果 $n_1 < n_2$，那么这也是最“松”的一种方案了，如果 $n_1$ 增大或 $n_2$ 减小都会导致某个老师无法选组的情况。

那么，也就是说 $n_1$ 只能减小，$n_2$ 只能增大。

然而，现在 $n_1 + n_2$ 还不一定满足在 $[t, T]$ 内的情况。

所以如果 $n_1 + n_2 < t$，就只能增大 $n_2$；如果 $n_1 + n_2 > T$，就只能减小 $n_1$。

那么就可以算出最优的一个 $n_1$ 和 $n_2$ 的选取方案，再根据这个方案对老师进行一次二分图染色判定即可。

时间复杂度为 $\mathcal O (n + m)$，[评测链接](https://codeforces.com/contest/538/submission/72777616)。

---

## 作者：xht (赞：13)

> [CF538H Summer Dichotomy](https://codeforces.com/contest/538/problem/H)

## 题意

- 有 $T$ 名学生，你要从中选出至少 $t$ 人，并将选出的人分成两组，可以有某一组是空的。
- 有 $n$ 名老师，每名老师要被分配到两个小组之一，对于第 $i$ 名老师，要求所在的小组中的学生人数 $\in [l_i, r_i]$。
- 此外，有 $m$ 对老师不能在同一个小组中。
- 你需要判断能否满足所有要求，如果可以，请给出一种方案。
- $t \le T \le 10^9$，$n,m \le 10^5$。

## 题解

先不考虑 $t,T$ 的限制，可以证明 $n_1 = \min_{i=1}^n r_i$，$n_2 = \max_{i=1}^n l_i$ 是最优的。

证明如下：

将所有 $[l_i, r_i]$ 当作一条数轴上的线段，那么有三种情况：

1. 有三条线段两两不交，则无解。
2. 所有线段两两有交，即有 $n_1 \ge n_2$，则在这种情况下，每个老师都可以随意的选择小组。
3. $n_1 < n_2$，在这种情况下，显然 $n_1$ 不能更大，而更小则不优，$n_2$ 同理。

因此 $n_1 = \min_{i=1}^n r_i$，$n_2 = \max_{i=1}^n l_i$ 一定是最优的。

如果考虑 $t,T$ 的限制呢？可以发现，若 $n_1 + n_2 < t$，则无论哪种情况下，只增大 $n_2$ 是最优的；若 $n_1 + n_2 > T$，则无论哪种情况下，只减小 $n_1$ 的最优的。

因此我们可以直接求出最优的 $n_1,n_2$，最后做一次二分图染色即可。

时间复杂度 $\mathcal O(n+m)$。

## 代码

```cpp
#define Fail return prints("IMPOSSIBLE"), 0

const int N = 1e5 + 7;
int t, T, n, m, l[N], r[N], n1 = 1e9 + 1, n2 = -1, c[N];
vi e[N];

inline bool pd(int x, int i) {
	return l[i] <= x && x <= r[i];
}

bool dfs(int x) {
	for (auto y : e[x])
		if (!c[y]) {
			c[y] = 3 - c[x];
			if (!dfs(y)) return 0;
		} else if (c[x] == c[y]) return 0;
	return 1;
}

int main() {
	rd(t), rd(T), rd(n), rd(m);
	for (int i = 1; i <= n; i++)
		rd(l[i]), rd(r[i]), n1 = min(n1, r[i]), n2 = max(n2, l[i]);
	if (n1 + n2 < t) n2 = t - n1;
	if (n1 + n2 > T) n1 = T - n2;
	if (n1 < 0 || n2 < 0) Fail;
	for (int i = 1; i <= n; i++) {
		bool o1 = pd(n1, i), o2 = pd(n2, i);
		if (!o1 && !o2) Fail;
		if (o1 && !o2) c[i] = 1;
		if (!o1 && o2) c[i] = 2;
	}
	for (int i = 1, x, y; i <= m; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	for (int i = 1; i <= n; i++) if (c[i] && !dfs(i)) Fail;
	for (int i = 1; i <= n; i++)
		if (!c[i]) {
			c[i] = 1;
			if (!dfs(i)) Fail;
		}
	string ans = "";
	for (int i = 1; i <= n; i++) ans += c[i] + '0';
	prints("POSSIBLE"), print(n1, ' '), print(n2), prints(ans); 
	return 0;
}
```

---

## 作者：木xx木大 (赞：7)

[CF538H Summer Dichotomy](https://www.luogu.com.cn/problem/CF538H)  

一道不错的题。解法很多。为方便表述，设两个小组的学生数分别为 $n_1,n_2 $

**算法一：**

首先，看到` 有m对老师不能在同一个小组中 `，想到 **2-SAT**。又看到 $[l_i,r_i]$ 的限制，想到前缀优化建图。于是我们得到了一个类似[CF1215F Radio Stations](https://www.luogu.com.cn/blog/flyingfan/cf1215f-radio-stations-qian-zhui-you-hua-jian-tu-2-sat)的做法。但本题 $T$ 过大，这样建图无法通过。发现，可以构造一组解使 $n_1,n_2$ 只在 $0,t,l_i,r_i,t-l_i,t-r_i$ 中取值，如果只建这些点，跑 2-SAT，复杂度就会降到 $O(n+m)$。 

**算法二：**（参考资料：[CF官方题解](https://codeforces.com/blog/entry/17612)）

将老师们的关系连边，这样会产生一些联通块，显然如果这个图不是二分图就无解，否则对于一个联通块，可以分成分组不同的两个集合，令这两个集合对学生人数要求的区间的交为 $l_1,r_1,l_2,r_2$。
从每一个 $(l_1,r_1,l_2,r_2)$ 入手，将 $(n1,n2)$ 看作二维平面上的一个点，每个连通块对应的合法点集是 $r(l_1,l_2,r_1,r_2)\bigcup r(l_2,l_1,r_2,r_1)$ ，而全局合法点是每个连通块合法点的交，其中 $r(a,b,c,d)$ 表示以 $( a,b)$ 为左上角，$(c,d)$ 为右下角的矩形。用**扫描线**维护，取答案的时候判一下 $[t,T]$ 的限制即可。复杂度 $O(n\log n)$

**算法三：**

我 orz 题解以后得到了这个优秀的做法。这个做法的代码是如此之短以至于我看到它就不想写自己 yy 出来的做法了。~~没错上面两种做法都是我口胡的~~

设 $n1\le n2$ ，如果没有 $[t,T]$ 的限制，我们贪心地让 $n1=\min r_i,n2=\max l_i$。因为 $n1<n2$ ，如果存在某个 $r_i<n1$ ，则 $i$ 无法分组。$n2$ 同理。所以这样贪心会使限制条件是最“松”的，且 $n1$ 可以变小不能变大， $n2$ 可以变大不能变小。

加入 $[t,T]$ 的限制，如果 $n1+n2>T$ 就调小 $n1$，如果 $n1+n2<t$ 就调大 $n2$。于是我们可以求出一组合法的 $(n1,n2 )$。

然后考虑如何构造方案。先从只可能被分到某一组的老师开始，像算法二那样进行二分图染色，如果不是二分图就无解。复杂度 $O(n+m)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FGF
{
	int n,m,t,T;
	const int N=1e5+5;
	int l[N],r[N],n1=0x3f3f3f3f,n2,ans[N];
	vector<int> g[N];
	void dfs(int u,int col)
	{
		if(ans[u])
		{
			if(ans[u]!=col)
			{
				puts("IMPOSSIBLE");
				exit(0);
			}
			return;
		}
		ans[u]=col;
		for(auto v:g[u])
			dfs(v,3-col);
	}
	void work()
	{
		scanf("%d%d%d%d",&t,&T,&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&l[i],&r[i]),n1=min(n1,r[i]),n2=max(n2,l[i]);
		if(n1+n2<t)n2=t-n1;
		else if(n1+n2>T)n1=T-n2;
		if(n1<0||n2<0){puts("IMPOSSIBLE");return;}
		for(int i=1,u,v;i<=m;i++)
			scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
		for(int i=1;i<=n;i++)
		{
			if((l[i]<=n1&&n1<=r[i])&&!(l[i]<=n2&&n2<=r[i]))dfs(i,1);
			if(!(l[i]<=n1&&n1<=r[i])&&(l[i]<=n2&&n2<=r[i]))dfs(i,2);
			if(!(l[i]<=n1&&n1<=r[i])&&!(l[i]<=n2&&n2<=r[i])){puts("IMPOSSIBLE");return;}
		}
		for(int i=1;i<=n;i++)
			if(!ans[i])dfs(i,1);
		puts("POSSIBLE");
		printf("%d %d\n",n1,n2);
		for(int i=1;i<=n;i++)
			printf("%d",ans[i]);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：syzf2222 (赞：5)

自己学的时候不太读的懂粉兔和 xht 的题解，于是尝试写一篇详细一点的。

容易发现如果存在三个老师两两无交直接就无解了。

我们先忽略 $t,T,m$ 构造一个能够合法划分老师的两部个数 $n_1,n_2$。

- 所有老师都两两有交，则我们取交的两个端点即可（实际上取任意一点在交内即可）。称作情况 $1$。

- 存在两个老师无交，则我们选择最靠左的右端点作为 $n_1$，最靠右的左端点作为 $n_2$，其余线段一定至少与其中之一有交，否则这三个线段两两无交了。称作情况 $2$。注意到这种情况下 $n_1$ 变大和 $n_2$ 变小都是不合法的。

注意到这两种情况下 $n_1,n_2$ 都可以表示为 $\min\{r_i\}$ 和 $\max\{l_i\}$。

考虑 $t,T,m$ 的限制，$t,T$ 的限制确定了 $n_1,n_2$ 的增减，$m$ 限制了 $n_1,n_2$ 要包含尽量大的老师集合。

- $n_1+n_2\in[t,T]$。若为情况 $1$，则若 $m$ 条限制为二分图则 $n_1,n_2$ 已经是合法解；否则若 $n_1$ 减小则包含的集合为之前的子集，$n_2$ 增大亦然。

- $n_1+n_2<t$。若为情况 $2$，则只能是 $n_2$ 增大；否则 $n_1$ 减小的话 $n_2$ 需要增加更多，两边都是子集了，于是 $n_1$ 只能增大，若 $n_1,n_2$ 都大于交的右端点则不合法了，则必然有一个在交内，则位于交的右端点最优。故应当 $n_2$ 增大。

- $n_1+n_2>T$。同理，只能 $n_1$ 减小。

此时我们已经确定了最优秀的 $n_1,n_2$，剩下的判定是简单的。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,tl,tr,n1=inf,n2,l[maxn],r[maxn],col[maxn],ok=1;
#define pb push_back
vector<int>G[maxn];
inline void dfs(int x){
	for(auto t:G[x]){
		if(col[t]==col[x])ok=0;
		if(!col[t])col[t]=3-col[x],dfs(t);
	}
}
int main(){
	tl=read(),tr=read(),n=read(),m=read();
	for(int i=1;i<=n;i++)
		l[i]=read(),r[i]=read(),n1=min(n1,r[i]),n2=max(n2,l[i]);
	if(n1+n2<tl)n2=tl-n1;if(n1+n2>tr)n1=tr-n2;
	if(n1<0||n2<0)return puts("IMPOSSIBLE")&0;
	for(int i=1;i<=n;i++){
		int f1=(l[i]<=n1&&n1<=r[i]);
		int f2=(l[i]<=n2&&n2<=r[i]);
		if(!f1&&!f2)return puts("IMPOSSIBLE")&0;
		if(!f1)col[i]=2;if(!f2)col[i]=1;
	}for(int i=1,x,y;i<=m;i++)
		x=read(),y=read(),G[x].pb(y),G[y].pb(x);
	for(int i=1;i<=n;i++)if(col[i])dfs(i);
	for(int i=1;i<=n;i++)if(!col[i])col[i]=1,dfs(i);
	if(!ok)return puts("IMPOSSIBLE")&0;
	puts("POSSIBLE");printf("%d %d\n",n1,n2);
	for(int i=1;i<=n;i++)printf("%d",col[i]);puts("");
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：fade_away (赞：4)

大家好，我是个憨憨，我不会大家都会的线性做法，我只会大暴力线段树（据说官解也是线段树？！）。
## Solution

### Part one
首先我们知道老师的$m$个敌对关系是一个经典的2-SAT,若存在连通块有奇环，则无解。否则，我们可以对于每个连通块，求出所有奇数深度的点的区间交$[l, r]$和偶数深度的点的区间交$[L, R]$。

我们可以维护一个当前第一组可选的学生数区间$[L_1,R_1]$和第二组可选学生数区间$[L_2, R_2]$。

现在要把奇数深度点和偶数深度点分别分配给第一第二组（不能分配到同一组），相当于第一组选择$[l,r]$和$[L,R]$中的一个做区间交，第二组选另一个做区间交。

每个连通块都给两组做完区间交之后，设给定的总学生数区间为$[T_l, T_r]$，我们要求$[L_1+ L_2, R_1+R_2]\cap[T_l,T_r]\not = \emptyset$，这样我们就可以选出第一组的人数$x$和第二组的人数$y$，然后对于每个连通块通过其两个区间的限制判断它在偶数深度点为第一组还是奇数深度点为第一组去构造方案了。

### Part two
现在问题转化为了：如何对于每个连通块，合理分配$[l,r]$和$[L,R]$使得上述条件成立。

这个似乎不好直接做，因此我们考虑线段树维护。一个线段树的结点$[l,r]$表示第一组的可选人数在$[l,r]$之间时，第二组的可选区间是什么，操作是一个区间对另一个区间做区间交。

对于一个连通块奇偶深度的区间$[l,r]$和$[L,R]$，我们不妨假设$l < L$。分三种情况讨论：

- $r < L$，这样两个区间不交，因此若我们选择的第一组的人数在$[l,r]$内，第二组只能选择$[L,R]$，于是我们在线段树$[l,r]$内打上$[L,R]$的tag，表示其只能选择$[L,R]$之间的人数；若我们选择的第一组人数在$[L,R]$之间，那么在$[L,R]$的线段树结点上打上$[l,r]$的tag；最后在其他结点上打上$[Tr, 0]$的表示不可行的tag。
- $r < R$，此时这两个区间中间有一段区间$[L, r]$相交了，这表示什么呢？这表示这段区间内的点可以任意选择偶数和深度的点，因此这段区间要打上$[l,R]$的标记！因为我们可以任意调换使得第二组的人数在$[l,R]$都可行，对于其他部分还是和上面一样的，分类讨论即可。
- $r \geq R$，此时$[l,r]$包含$[L,R]$，还是像上面一样分类讨论即可。

注意这里我们可以用动态开点线段树+标记永久化维护，时间复杂度为大常数$O(nlogT_r)$。

### Part three
最后就是怎么求$x,y$了，我们最终可以把线段树的$tag$下放，直至到一个没有左右儿子的结点，相当于我们求出了一个有第一组选择的人数在$[L_1,R_1]$之间时，第二组人数在$[L_2,R_2]$内都可行的信息。

于是我们再通过简单的分类讨论看看是否存在$x\in[L_1,R_1], y\in[L_2, R_2]$使得$x+y\in[T_l, T_r]$，求出$x,y$后就可以$O(n+m)$构造方案了。

具体实现可参照代码（虽然感觉大家也不会来看这个又暴力又长的做法的）。
## Code

```cpp
//此处省略70行快读和头文件

vector<int> e[MAXN];
int dep[MAXN], vis[MAXN], ls[MAXN * 20], rs[MAXN * 20], flag[MAXN], Ans[MAXN], nodenum = 0, Ansx, Ansy, Tl, Tr, n, m;
PR A[MAXN], B[2], C[MAXN][2], tag[MAXN * 20];
PR operator & (PR x, PR y) { return MP(max(x.fi, y.fi), min(x.se, y.se)); }
PR operator | (PR x, PR y) { return MP(min(x.fi, y.fi), max(x.se, y.se)); }
void dfs(int x, int father) { //求出[l, r]和[L, R] 
	vis[x] = 1;
	dep[x] = dep[father] + 1;
	B[dep[x] & 1] = B[dep[x] & 1] & A[x];
	for (auto v : e[x]) {
		if (!vis[v]) dfs(v, x);
		else if ((dep[x] & 1) == (dep[v] & 1)) { cout << "IMPOSSIBLE" << endl; exit(0); } 
	}
}
void Dfs(int x, int opt) { //构造方案 
	vis[x] = 1;
	if ((dep[x] & 1) == opt) Ans[x] = 1;
	else Ans[x] = 2;
	for (auto v : e[x]) if (!vis[v]) Dfs(v, opt);
}

int update(int x, int l, int r, int L, int R, PR y) {
	if (!x) tag[x = ++ nodenum] = MP(0, Tr);
	if (l >= L && r <= R) { tag[x] = tag[x] & y; return x; }
	int mid = (l + r) >> 1;
	if (R <= mid) ls[x] = update(ls[x], l, mid, L, R, y);
	else if (L > mid) rs[x] = update(rs[x], mid + 1, r, L, R, y);
	else ls[x] = update(ls[x], l, mid, L, mid, y), rs[x] = update(rs[x], mid + 1, r, mid + 1, R, y);
	return x;
}
void check(int l, int r, int L, int R) { // 找合法的x, y 
	if (l > r || L > R) return;
	if (l + L > Tr) return;
	if (l + L >= Tl) { Ansx = l, Ansy = L; return; }
	if (Tl - (l + L) > (r - l) + (R - L)) return;
	if (Tl - (l + L) > (r - l)) { Ansx = r, Ansy = L + (Tl - (l + L) - (r - l)); return; }
	Ansx = l + (Tl - (l + L)), Ansy = L;
}
void solve(int x, int l, int r, PR y) {  
	if (Ansx || Ansy) return;
	y = y & tag[x];
	if (!ls[x] && !rs[x]) { check(l, r, y.fi, y.se); return; }
	int mid = (l + r) >> 1;
	if (ls[x]) solve(ls[x], l, mid, y);
	if (rs[x]) solve(rs[x], mid + 1, r, y);
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	read(Tl), read(Tr), read(n), read(m);
	for (int i = 1; i <= n ; ++ i) {
		read(A[i].fi), read(A[i].se), upmin(A[i].se, Tr);
		if (A[i].fi > A[i].se) { cout << "IMPOSSIBLE" << endl; return 0; }
	}
	for (int i = 1, u, v; i <= m ; ++ i) read(u), read(v), e[u].PB(v), e[v].PB(u);
	tag[nodenum = 1] = MP(0, Tr);
	for (int i = 1; i <= n ; ++ i)
		if (!vis[i]) {
			B[0] = B[1] = MP(0, Tr);
			dfs(i, 0);
			flag[i] = 1, C[i][0] = B[0], C[i][1] = B[1];		
			if (B[0].fi > B[1].fi) swap(B[0], B[1]);	
			if (B[0].se < B[1].fi) {
				if (B[0].fi > 0) update(1, 0, Tr, 0, B[0].fi - 1, MP(Tr, 0));
				if (B[0].fi <= B[0].se) update(1, 0, Tr, B[0].fi, B[0].se, B[1]);
				if (B[0].se + 1 <= B[1].fi - 1) update(1, 0, Tr, B[0].se + 1, B[1].fi - 1, MP(Tr, 0));
				if (B[1].fi <= B[1].se) update(1, 0, Tr, B[1].fi, B[1].se, B[0]);
				if (B[1].se < Tr) update(1, 0, Tr, B[1].se + 1, Tr, MP(Tr, 0));
			} //Condition 1
			else if (B[0].se < B[1].se) {
				if (B[0].fi > 0) update(1, 0, Tr, 0, B[0].fi - 1, MP(Tr, 0));
				if (B[0].fi < B[1].fi)  update(1, 0, Tr, B[0].fi, B[1].fi - 1, B[1]);
				if (B[1].fi <= B[0].se) update(1, 0, Tr, B[1].fi, B[0].se, B[0] | B[1]);
				if (B[0].se < B[1].se)  update(1, 0, Tr, B[0].se + 1, B[1].se, B[0]);
				if (B[1].se < Tr) update(1, 0, Tr, B[1].se + 1, Tr, MP(Tr, 0));
			}//Condition 2
			else {
				if (B[0].fi > 0) update(1, 0, Tr, 0, B[0].fi - 1, MP(Tr, 0));
				if (B[0].fi < B[1].fi)  update(1, 0, Tr, B[0].fi, B[1].fi - 1, B[1]);
				if (B[1].fi <= B[1].se) update(1, 0, Tr, B[1].fi, B[1].se, B[0]);
				if (B[1].se < B[0].se)  update(1, 0, Tr, B[1].se + 1, B[0].se, B[1]);
				if (B[0].se < Tr) update(1, 0, Tr, B[0].se + 1, Tr, MP(Tr, 0));
			}//Condition 3
		}
	solve(1, 0, Tr, MP(0, Tr));
	if (!Ansx && !Ansy) { cout << "IMPOSSIBLE" << endl; return 0; }
	cout << "POSSIBLE" << endl;
	print(Ansx), putc(' '), print(Ansy), putc('\n');
	for (int i = 1; i <= n ; ++ i) vis[i] = 0;
	for (int i = 1; i <= n ; ++ i) {
		if (!flag[i]) continue;
		if (C[i][0].fi <= Ansx && Ansx <= C[i][0].se && C[i][1].fi <= Ansy && Ansy <= C[i][1].se) Dfs(i, 0); //判断第一组拿偶数点还是奇数点。 
		else Dfs(i, 1);
	}
	for (int i = 1; i <= n ; ++ i) putc('0' + Ans[i]);
	return 0;
}
```


---

## 作者：lprdsb (赞：2)

### 题意

- 有一些同学和$n$个老师，要求从中选出至少$t$个至多$T$学生分成两组
- 要求第$i$名老师所分得的学生人数在$[l_i, r_i]$的范围内并且每个老师都要分到某一组去
- 并且有一些老师不能在同一组
- 构造一组方案

先不考虑$t, T$的限制，那么分情况考虑：

1. 所有区间都有交集
2. 最后答案将老师分成两个集合，且两集合交集的交集为空



对于情况1，只要在交集里面选两个点就好



对于情况2，考虑选的较小的那个点$x$，可以发现这个点一定会在所有$r_i$的前面，否则另外一个点更大，那这个$r_i$就无法分组了，所以这个点一定会满足：
$$
x\leq\min_{i=1}^{n}\{r_i\}
$$
再考虑较大的那个点$y$，同样的，这个点一定会所有$l_i$的后面，否则同样不满足题意，即：
$$
y\geq\max_{i=1}^n\{l_i\}
$$
然后再考虑$t,T$的限制，同样有两种情况：

1. $x+y<t$，由于$x$只能减小，所以只能增大$y$，但增大多可能会不满足区间的限制，所以尽量让$y$更小
2. $x+y>T$，同理只能最小地减小$x$

于是，我们能得到的最终的$x,y$一定能满足题意，否则就无解，之后建出二分图跑跑就好了

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a), en = (b); i <= en; ++i)
#define Rof(i, a, b) for(int i = (a), en = (b); i >= en; --i)
#define Tra(u, i) for(int i = hd[u]; ~i; i = e[i].net)
#define cst const
#define LL long long
#define DD double
#define LD long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-12
#define maxn 100000
using namespace std;

int T, t, n, m, mn = inf, mx = 0, L[maxn + 5], R[maxn + 5], col[maxn + 5];

template <class T>
void read(T &x){
	char ch;
	bool ok;
	for(ok = 0, ch = getchar(); !isdigit(ch); ch = getchar()) if(ch == '-') ok = 1;
	for(x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	if(ok) x = -x;
}

int fa[2 * maxn + 5], to[maxn + 5];
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}

int main(){
	//freopen("in", "r", stdin);
	read(t); read(T); read(n); read(m);
	For(i, 1, n){
		read(L[i]); read(R[i]);
		mn = min(mn, R[i]);
		mx = max(mx, L[i]);
	}
	if(mn + mx < t) mx = t - mn;
	if(mn + mx > T) mn = T - mx;
	if(mn + mx < t || mn + mx > T || mn < 0){puts("IMPOSSIBLE"); return 0;};
	For(i, 1, 2 * n) fa[i] = i;
	For(i, 1, m){
		int u, v; read(u); read(v);
		if(find(u) == find(v)){puts("IMPOSSIBLE"); return 0;}
		fa[find(n + u)] = find(v);
		fa[find(n + v)] = find(u);
	}
	For(i, 1, n) if(find(n + i) != n + i) to[find(n + i)] = find(i);
	For(i, 1, n) L[find(i)] = max(L[find(i)], L[i]), R[find(i)] = min(R[find(i)], R[i]);
	For(i, 1, n) if(find(i) == i){
		if(L[i] > R[i]){puts("IMPOSSIBLE"); return 0;}
		if(!to[i]){
			//cout << L[i] << " " << R[i] << endl;
			if(mn >= L[i] && mn <= R[i]) col[i] = 1;
			else if(mx >= L[i] && mx <= R[i]) col[i] = 2;
			else{puts("IMPOSSIBLE"); return 0;}
		}
		else{
			if(mn >= L[i] && mn <= R[i] && mx >= L[to[i]] && mx <= R[to[i]]){
				col[i] = 1;
				col[to[i]] = 2;
			}
			else if(mn >= L[to[i]] && mn <= R[to[i]] && mx >= L[i] && mx <= R[i]){
				col[i] = 2;
				col[to[i]] = 1;
			}
			else{puts("IMPOSSIBLE"); return 0;}
		}
	}
	puts("POSSIBLE");
	printf("%d %d\n", mn, mx);
	For(i, 1, n) printf("%d", col[find(i)]);
	return 0;
}
```



---

## 作者：封禁用户 (赞：1)

### 题解
令两组人数为 $n_1,n_2$。

分析易得，若无 $n_1+n_2 \in[t,T]$ 的限制，在最优选择下 $n_1=min{\{r_i}\}(i\in[1,n]),n2=max{\{l_i\}}(i\in[1,n])$。

再考虑加上 $n_1+n_2 \in[t,T]$ 的限制，此时有两种情况：
- 若 $n_1+n_2<t$，此时增加 $n_2$ 最优。
- 同理，若 $n_1+n_2>T$，此时减少 $n_1$ 最优。

对于一对不能被分在同一组的老师 $a$ 和 $b$，建边 $a \rightarrow b,b \rightarrow a$。

最后，用染色法判断建的图是否为二分图，并输出答案即可。

---

## 作者：RainsAFO (赞：1)

很明显的贪心模型。

无$t,T$限制下的两组人数$s1,s2$。

下证$s1$在$r_i$中取 $min$，s2在$l_i$中取$max$时最优。

首先区间$l_i,r_i$必须有交。

若$s2 \leq s1$，可以任意选组。

反之，$s1$增加必有一人无法选组。

对$s2$亦然。

有限制时过小增大$s2$，过大减小$s1$。

最后不能在同一组内的人连边，二分图染色即可。

code:

```cpp
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

int n , m , t , T;

int x , y;

vector <int> g[100005];

int c[100005] , l[100005] , r[100005];

bool dfs(int x) {
	for(auto y : g[x]) {
		if(!c[y]){
			c[y] = 3 - c[x];
			if(!dfs(y))
				return 0;
		}
		else
			if(c[x] == c[y])
				return 0;
	}
	return 1;
}

bool pd(int x , int i){
	return x >= l[i] && x <= r[i];
}

int main() {
	cin >> t >> T >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> l[i] >> r[i];
	for(int i = 1; i <= m; i++) {
		cin >> x >> y;
		g[x].push_back(y) , g[y].push_back(x);
	}
	int t1 = 0x3f3f3f3f , t2 = 0;
	for(int i = 1; i <= n; i++)
		t1 = min(t1 , r[i]) , t2 = max(t2 , l[i]);	
//	cout << t1 << " " << t2 << endl;
	if(t1 + t2 < t)
		t2 =  t - t1;
	if(t1 + t2 > T)
		t1 = T - t2;
	if(t1 < 0 || t2 < 0) {
		cout << "IMPOSSBLE" << endl;
		return 0;
	}
	for(int i = 1; i <= n; i++) {
		bool a = 0 , b = 0;
		if(t1 >= l[i] && t1 <= r[i])
			a = 1;
		if(t2 >= l[i] && t2 <= r[i])
			b = 1;
		if(!a && !b) {
			cout << "IMPOSSBLE" << endl;
			return 0;
		}
		if(a && !b)
			c[i] = 1;
		if(!a && b)
			c[i] = 2;
	}
	for(int i = 1; i <= n; i++)
		if(!dfs(i) && c[i]) {
			cout << "IMPOSSBLE" << endl;
			return 0;
		}
	for(int i = 1; i <= n; i++) {
		if(!c[i]) {
			c[i] = 1;
			if(!dfs(i)) {
				cout << "IMPOSSIBLE" << endl;
				return 0;
			}
		}
	}
	cout << "POSSIBLE" << endl;
	cout << t1 << " " << t2 << endl;
	for(int i = 1; i <= n; i++)
		cout << c[i];
	return 0;
}
```




---

## 作者：skylee (赞：1)

# [CF538H]Summer Dichotomy

### 题目大意：

​	将若干个学生分为两个班级$S_1,S_2$，每个班的学生数分别为$n_1,n_2$（甚至可以没有学生，也可以没有老师）。给出限制$t_{\min},t_{\max}$，要求$t_{\min}\le n_1+n_2\le t_{\max}$。有$n(n\le10^5)$个老师，每个老师希望他所任教的班级人数在$[l_i,r_i]$范围内。有$m(m\le10^5)$对老师之间有一些私人恩怨，不能分在一个班级。问是否存在合法的分班方案。如果有，求出其中的任意一种，输出每个班的总人数以及各个老师所任教的班级。

### 思路：

​	对于所有$[l_i,r_i]$的限制，我们不妨假设$n_1=\min\{r_i\},n_2=\max\{l_i\}$，显然这是比较松的约束。再考虑$t_{\min},t_{\max}$的限制，确定可行的一组$n_1,n_2$。考虑二分图染色构造老师分配的方案。对于只能分到$S_1$或只能分到$S_2$的老师DFS遍历染色，若更新到的结点与已染色结点矛盾，说明根本不是二分图，不存在合法的方案。对于两个都不可以分进去的，说明也不存在合法方案。最后再对于$S_1$和$S_2$都可以的进行染色。

### 源代码：

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<climits>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
constexpr int N=1e5;
int l[N],r[N],ans[N];
std::vector<int> e[N];
inline void add_edge(const int &u,const int &v) {
	e[u].push_back(v);
	e[v].push_back(u);
}
void dfs(const int &x,const int &c) {
	if(ans[x]) {
		if(ans[x]!=c) throw(0);
		return;
	}
	ans[x]=c;
	for(auto &y:e[x]) {
		dfs(y,3-c);
	}
}
int main() {
	const int t_min=getint(),t_max=getint();
	const int n=getint(),m=getint();
	int n1=INT_MAX,n2=INT_MIN;
	for(register int i=0;i<n;i++) {
		n2=std::max(n2,l[i]=getint());
		n1=std::min(n1,r[i]=getint());
	}
	if(n1+n2<t_min) n2=t_min-n1;
	else if(n1+n2>t_max) n1=t_max-n2;
	if(n1<0||n2<0) {
		puts("IMPOSSIBLE");
		return 0;
	}
	for(register int i=0;i<m;i++) {
		add_edge(getint()-1,getint()-1);
	}
	for(register int i=0;i<n;i++) {
		try {
			if(!(l[i]<=n1&&n1<=r[i])&&!(l[i]<=n2&&n2<=r[i])) throw(0);
			if((l[i]<=n1&&n1<=r[i])&&!(l[i]<=n2&&n2<=r[i])) dfs(i,1);
			if((l[i]<=n2&&n2<=r[i])&&!(l[i]<=n1&&n1<=r[i])) dfs(i,2);
		} catch(...) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	for(register int i=0;i<n;i++) {
		try {
			if(!ans[i]) dfs(i,1);
		} catch(...) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts("POSSIBLE");
	printf("%d %d\n",n1,n2);
	for(register int i=0;i<n;i++) {
		printf("%d",ans[i]);
	}
	return 0;
}
```



---

## 作者：_lbw_ (赞：1)

我们设两个小组人数为 $x,y$

先处理不能在同一小组的限制，连边后二分图染色可以直接消除掉这个限制。

剩下属于 $[l_i,r_i]$ 可以建立出二维平面，将限制画上去。

最后枚举 $x$ 扫描线，建立维护最大值的线段树，将限制内的点 $+1$，最后 $y\in[t-x,T-x]$ 查最大值是否为 $n$ 即可。

---

## 作者：BlankAo (赞：1)

来点暴力且直观的算法。

首先这种选择两种分组的问题可以转化为 2-SAT。

注意到对于两个区间 $[l_1,r_1],[l_2,r_2]$，如果 $r_1<l_2$ 或者 $l_1>r_2$，那么这两个人不能分到同一组里。

那么根据这个限制建立出 2-SAT 模型即可。直接用前缀后缀优化建图，即可将时空复杂度优化到 $O(n)$。

注意由于优化建图，要离散化原区间。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define per(i,x,y) for(int i=x;i>=y;--i)
#define lon long long
#define mar(o) for(int E=fst[o],v=e[E].to;E;E=e[E].nxt,v=e[E].to)
#define root(x) rot[x],1,inf
#define lson tre[o].lv,l,mid
#define rson tre[o].rv,mid+1,r
using namespace std;
mt19937 rng( time(0) );
const int n7=2012345,z7=401234,m7=n7*2;
struct dino{int to,nxt;}e[m7];
struct golf{int id,l,r,L,R;}a[z7];
struct mist{int lv,rv;}tre[n7];
int n,m,cnt,ecnt,fst[n7],t,dfn[n7],low[n7],ans[z7],lsh[n7];
int top,sak[n7],in[n7],colc,col[n7],id[4][n7];

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

void edge(int p,int q){
	ecnt++;
	e[ecnt]=(dino){q,fst[p]};
	fst[p]=ecnt;
}

void tar(int o){
	t++,dfn[o]=low[o]=t;
	top++,sak[top]=o,in[o]=1;
	mar(o){
		if(!dfn[v])tar(v),low[o]=min(low[o],low[v]);
		else if(in[v]==1)low[o]=min(low[o],dfn[v]);
	}
	if(low[o]^dfn[o])return;
	colc++;
	while(sak[top+1]^o){
		col[ sak[top] ]=colc;
		in[ sak[top] ]=0;
		top--;
	}
}

void Dlsh(){
	int sz=0;
	rep(i,1,n)sz++,lsh[sz]=a[i].l,sz++,lsh[sz]=a[i].r;
	sort(lsh+1,lsh+sz+1);
	sz=unique(lsh+1,lsh+sz+1)-lsh-1;
	rep(i,1,n){
		a[i].L=lower_bound(lsh+1,lsh+sz+1,a[i].l)-lsh;
		a[i].R=lower_bound(lsh+1,lsh+sz+1,a[i].r)-lsh;
	}
}

int main(){
	int l0=rd(),r0=rd();
	n=rd(),m=rd(),cnt=n+n;
	rep(i,1,n)a[i]=(golf){i,rd(),rd()};
	Dlsh();
	rep(i,0,3)rep(j,1,n*2)cnt++,id[i][j]=cnt;
	rep(i,0,3){
		if(i<2){
			per(j,n*2-1,1)edge(id[i][j],id[i][j+1]);
		}
		else{
			rep(j,2,n*2)edge(id[i][j],id[i][j-1]);
		}
	}
	rep(i,1,n)edge(id[0][ a[i].L ],a[i].id+n);
	rep(i,1,n)edge(id[1][ a[i].L ],a[i].id);
	rep(i,1,n)edge(id[2][ a[i].R ],a[i].id+n);
	rep(i,1,n)edge(id[3][ a[i].R ],a[i].id);
	rep(i,1,n)edge(a[i].id,id[0][ a[i].R+1 ]);
	rep(i,1,n)edge(a[i].id+n,id[1][ a[i].R+1 ]);
	rep(i,1,n)edge(a[i].id,id[2][ a[i].L-1 ]);
	rep(i,1,n)edge(a[i].id+n,id[3][ a[i].L-1 ]);
	rep(i,1,m){
		int p=rd(),q=rd();
		edge(p,q+n),edge(p+n,q);
		edge(q,p+n),edge(q+n,p);
	}
	rep(i,1,cnt)if(!dfn[i])tar(i);
	rep(i,1,n)if(col[i]==col[i+n]){puts("IMPOSSIBLE");return 0;}
	int l1=0,r1=1e9,l2=0,r2=1e9;
	rep(i,1,n){
		if(col[i]>col[i+n]){
			ans[i]=1,l1=max(l1,a[i].l),r1=min(r1,a[i].r);
		}
		else{
			ans[i]=2,l2=max(l2,a[i].l),r2=min(r2,a[i].r);
		}
	}
	if(l1>r1||l2>r2||l1+l2>r0||r1+r2<l0){puts("IMPOSSIBLE");return 0;}
	puts("POSSIBLE");
	int ll=l1,rr=r1,val1=0,val2=0;
	while(ll<=rr){
		int mid=(ll+rr)>>1;
		if(l2+mid>r0)rr=mid-1;
		else if(r2+mid<l0)ll=mid+1;
		else{val1=mid;break;}
	}
	ll=l2,rr=r2;
	while(ll<=rr){
		int mid=(ll+rr)>>1; 
		if(val1+mid>r0)rr=mid-1;
		else if(val1+mid<l0)ll=mid+1;
		else{val2=mid;break;}
	}
	printf("%d %d\n",val1,val2);
	rep(i,1,n)printf("%d",ans[i]);
	return 0;
}

```

---

## 作者：Sky_Maths (赞：0)

题解里没有的思考方法。

对于 $m$ 个限制，我们得到了一个图，若不是二分图则无解，否则对于每个连通块有 $[l_1, r_1], [l_2, r_2]$ 的限制，表示对于两组的人数限制（注意此处 $1, 2$ 并不代表组 $1$，$2$）。

不妨令 $n_1\ge n_2, (r_1 > r_2 \operatorname{or} r_1 == r_2 \operatorname{and} l_1 < l_2)$，则对于 $l_1\ge l_2$，必定是 $[l_1, r_1]$ 限制 $n_1$，$[l_2, r_2]$ 限制 $n_2$。

对于 $l_1 < l_2$，两者是包含关系，可能是以下两种之一：
1. $n_1\in [l_1, r_1], n_2\in [l_2, r_2]$
2. $n_1\in [l_2, r_2], n_2\in [l_1, r_1]$

因为 $n_1\ge n_2$ 所以：
1. $n_1\in [l_2, r_1], n_2\in [l_2, r_2]$
2. $n_1\in [l_2, r_2], n_2\in [l_1, l_2)$

在二维平面上考虑限制，对于区间 1 与区间 2 不包含的是一个矩形，对于包含的是一个矩形挖掉右下角。

可以先求矩形的交，再挖掉右下角。

对于 $t\le n_1 + n_2\le T$，是两条 $y = -x + b$ 的斜线，若矩形内有在两者中的，矩形的左/上边界必有其中的，而挖掉右下角对左/上边界影响最小，对于挖掉的维护矩形的左/上边界即可。

时间复杂度 $\mathcal O(n)$。

二分图染色的内容实现的不是很好。

[code](https://codeforces.com/contest/538/submission/282134678)

---

## 作者：Graphcity (赞：0)

来一发码量比较大的大力分类讨论解法。

首先对原图的限制进行二分图染色，每个连通块相互独立。这样就可以用两个区间来刻画一个连通块：$[l_1,r_1]$ 和 $[l_2,r_2]$，表示这个连通块被划分成两个集合之后分别代表的区间。对于孤立点，就相当于额外增加一个 $(-\infty,\infty)$ 的区间。

接下来用不等式来表示原题的限制：

$$
\begin{cases}
l_{1\max}\le r_{1\min} \\
l_{2\max}\le r_{2\min} \\
r_{1\min}+r_{2\min}\ge t\\
l_{1\max}+l_{2\max}\le T
\end{cases}
$$

注意到整个限制只跟每个集合 $l,r$ 的最小最大值有关系。

我们找到所有区间中 $l$ 的最大值 $l_{\max}$ 和 $r$ 的最小值 $r_{\min}$，并分类讨论：

- $l_{\max}$，$r_{\min}$ 不在同一集合

假设 $l_{\max}$ 在集合 1，$r_{\min}$ 在集合 2，那么限制可以转化为：

$$
\begin{cases}
l_{\max}\le r_1 \\
l_2\le r_{\min} \\
r_1\ge t-r_{\min}\\
l_{2}\le T-l_{\max}
\end{cases}
$$

暴力判断每个点所代表的两个区间分别在哪个集合即可。

- $l_{\max}$，$r_{\min}$ 在同一集合

注意此时需要 $l_{\max} \le r_{\min}$，限制转化为：

$$
\begin{cases}
l_2\le r_2 \\
r_2\ge t-r_{\min}\\
l_2\le T-l_{\max}
\end{cases}
$$

后面两个限制都很好解决，问题在于第一个限制。使用扫描线扫描 $x$，检查是否满足 $l_2\le x$ 且 $r_2\ge x$，这样就可以间接检查限制。

时间复杂度 $O(n\log n+m)$。

[Code](https://www.luogu.com.cn/paste/e3w8p3as)

---

