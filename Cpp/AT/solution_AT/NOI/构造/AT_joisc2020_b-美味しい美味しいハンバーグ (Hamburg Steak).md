# 美味しい美味しいハンバーグ (Hamburg Steak)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2020/tasks/joisc2020_b

## 说明/提示



由 ChatGPT 4.1 翻译

# 题解

## 作者：MhxMa (赞：4)

### 题意

给 $n$ 个矩形，在平面上选定 $k$ 个点使每个矩形内至少有一个被选定的点。

### 分析
考虑随机化。随机选择点，检查是否满足条件。枚举每两个矩阵，计算两个矩形的交集，随机选择 $k$ 个矩形作为初始点集。

随机出来的结果可能并没有选到所有的矩阵中，则使用循环来不断尝试不同的点集，直到找到一个满足条件的点集。详细解释见代码中注释。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, k;

struct node {
	int x1, y1, x2, y2;
} a[N];

node ans[6];

node js(node a, node b) { // 计算交集
	if (max(a.x1, b.x1) > min(a.x2, b.x2) || max(a.y1, b.y1) > min(a.y2, b.y2)) {
		return (node) {
			0, 0, 0, 0 // 两个矩形不相交
		};
	} else {
		return (node) {
			max(a.x1, b.x1), max(a.y1, b.y1), min(a.x2, b.x2), min(a.y2, b.y2)
		};
	}
}

int main() {
	srand(time(NULL));

	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
	}

	bool fl = 0; // 本轮计算是否符合题意
	while (1) {
		fl = 0;
		for (int i = 1; i <= k; ++i) {
			ans[i] = a[i];
		}

		for (int i = 1; i <= n; ++i) {
			int tp = 0; // 当前会选择第 tp 个点
			for (int j = 1; j <= k; ++j) { // 选择每两个矩阵，检查是否每个矩形都至少包含一个选定的点。
				if (!(max(a[i].x1, ans[j].x1) > min(a[i].x2, ans[j].x2) || max(a[i].y1, ans[j].y1) > min(a[i].y2, ans[j].y2))) { // 判断矩形 a[i] 是否包含点 ans[j]
					tp = j;
				}
			}
			if (!tp) { // 当前矩形不包含任何选定的点
				swap(a[i], a[rand() % (i - 1) + 1]);
				fl = 1;
				break;
			}
			ans[tp] = js(a[i], ans[tp]);
		}
		
		if (!fl) {
			for (int i = 1; i <= k; ++i) {
				printf("%d %d\n", ans[i].x1, ans[i].y1);
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# JOISC2020B 题解

[Problem Link](https://qoj.ac/problem/3553)

**题目大意**

> 给 $n$ 个矩形，在平面上选定 $k$ 个点使每个矩形内至少有一个被选定的点。
>
> 数据范围：$n\le 5\times 10^5$，$k\le 4$，保证有解。

**思路分析**

先考虑 $k\le3$ 的情况。

先求出所有矩形的交，如果非空，那么任取一个都可以。

如果一边非空（最大左端点 $\le$ 最小右端点），可以根据调整法证明点一定放在中间，因此可以降成一维的情况，那么一维的情况直接贪心按右端点放就行。

如果两边都为空（最大左端点 $>$ 最小右端点，最大上端点 $>$ 最小下端点），显然每个边界上至少要有一个点，但又由于 $k\le 3$，那么至少要有一个交点上有点，枚举选了哪个端点然后递归处理即可。

$k=4$ 的时候，若依然有点是交点，则也进行刚才同样的爆搜处理。

接下来我们只要处理四个边界上分别恰有一个点的情况，能够证明四个点一定在四条边界构成的矩形上。

对坐标离散化，然后建立 2-SAT 模型，如 $L_i$ 表示左边界上 $i$ 是不是被选的点。

考虑分类讨论每个矩形和几条边界有交：

- 若有 $3$ 或 $4$ 条边界有交，显然至少有一条边界被完全包含，则这个矩形一定满足。
- 若和 $1$ 条边界有交，显然直接更新对应的可能被选区间。
- 若不和区间有交，至少要一个点放在边界矩形内部，那么这种情况一定在刚刚选拐点的过程中处理过。
- 若和 $2$ 条边界有交，那么限制形如 $X_{l_1,r_1}\lor Y_{l_2,r_2}=1$，其中 $X,Y$ 是边界，$[l_1,r_1],[l_2,r_2]$ 表示对应边界上的一个子区间，但限制关系，考虑前缀和优化，注意到 $X_{l,r}=(X_{1,r}\land\lnot X_{1,l-1})$，因此原限制条件可以拆成 $\mathcal O(1)$ 组前缀变量上的限制关系，这样限制关系数就可以接受。

时间复杂度：$\mathcal O(4^kn+n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,inf=1e9;
struct Rect { int lox,hix,loy,hiy; };
inline Rect merge(Rect a,Rect b) {
	return {max(a.lox,b.lox),min(a.hix,b.hix),max(a.loy,b.loy),min(a.hiy,b.hiy)};
}
typedef array<int,2> Pair;
inline vector<Pair> dfs(const vector<Rect> &now,int k) {
	if(!k) return vector<Pair>(0);
	Rect inter{1,inf,1,inf};
	for(auto re:now) inter=merge(inter,re);
	int L=inter.lox,R=inter.hix,D=inter.loy,U=inter.hiy;
	if(L<=R&&D<=U) return vector<Pair>(k,{L,D});
	if(L<=R) {
		vector <Pair> sec,ans;
		for(auto re:now) sec.push_back({re.loy,re.hiy});
		sort(sec.begin(),sec.end(),[&](auto I,auto J){ return I[1]<J[1]; });
		int lst=0;
		for(auto s:sec) if(lst<s[0]) ans.push_back({L,lst=s[1]});
		if((int)ans.size()>k) ans.clear();
		else while((int)ans.size()<k) ans.push_back({inf,inf});
		return ans;
	}
	if(D<=U) {
		vector <Pair> sec,ans;
		for(auto re:now) sec.push_back({re.lox,re.hix});
		sort(sec.begin(),sec.end(),[&](auto I,auto J){ return I[1]<J[1]; });
		int lst=0;
		for(auto s:sec) if(lst<s[0]) ans.push_back({lst=s[1],U});
		if((int)ans.size()>k) ans.clear();
		else while((int)ans.size()<k) ans.push_back({inf,inf});
		return ans;
	}
	for(int o:{0,1,2,3}) {
		int x=(o&1)?L:R,y=(o&2)?U:D;
		vector <Rect> nxt;
		for(auto Re:now) if(x<Re.lox||x>Re.hix||y<Re.loy||y>Re.hiy) nxt.push_back(Re);
		vector <Pair> ans=dfs(nxt,k-1);
		if(ans.empty()) continue;
		ans.push_back({x,y});
		return ans;
	}
	return vector<Pair>(0);
}
int U[MAXN*2][2],D[MAXN*2][2],L[MAXN*2][2],R[MAXN*2][2];
int vx[MAXN*2],vy[MAXN*2];
vector <int> G[MAXN*16];
inline void link(int u,int v) { G[u].push_back(v); }
int dfn[MAXN*16],low[MAXN*16],dcnt;
int stk[MAXN*16],tp;
bool ins[MAXN*16];
int bel[MAXN*16],scnt;
inline void tarjan(int u) {
	dfn[u]=low[u]=++dcnt;
	ins[stk[++tp]=u]=true;
	for(int v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		int k; ++scnt;
		do {
			ins[k=stk[tp--]]=false;
			bel[k]=scnt;
		} while(k^u);
	}
}
signed main() {
	int n,k;
	scanf("%d%d",&n,&k);
	vector <Rect> a(n);
	for(int i=0;i<n;++i) scanf("%d%d%d%d",&a[i].lox,&a[i].loy,&a[i].hix,&a[i].hiy);
	auto ans=dfs(a,k);
	if(!ans.empty()) {
		for(auto I:ans) printf("%d %d\n",I[0],I[1]);
		return 0;
	}
	for(auto re:a) {
		vx[++vx[0]]=re.lox,vx[++vx[0]]=re.hix;
		vy[++vy[0]]=re.loy,vy[++vy[0]]=re.hiy;
	}
	sort(vx+1,vx+vx[0]+1),vx[0]=unique(vx+1,vx+vx[0]+1)-vx-1;
	sort(vy+1,vy+vy[0]+1),vy[0]=unique(vy+1,vy+vy[0]+1)-vy-1;
	for(auto &re:a) {
		re.lox=lower_bound(vx+1,vx+vx[0]+1,re.lox)-vx;
		re.hix=lower_bound(vx+1,vx+vx[0]+1,re.hix)-vx;
		re.loy=lower_bound(vy+1,vy+vy[0]+1,re.loy)-vy;
		re.hiy=lower_bound(vy+1,vy+vy[0]+1,re.hiy)-vy;
	}
	Rect inter{1,inf,1,inf};
	for(auto re:a) inter=merge(inter,re);
	int l=inter.hix,r=inter.lox,d=inter.hiy,u=inter.loy;
	int vcnt=0;
	for(int i=l;i<=r;++i) U[i][0]=++vcnt,D[i][0]=++vcnt;
	for(int i=d;i<=u;++i) L[i][0]=++vcnt,R[i][0]=++vcnt;
	for(int i=l;i<=r;++i) U[i][1]=++vcnt,D[i][1]=++vcnt;
	for(int i=d;i<=u;++i) L[i][1]=++vcnt,R[i][1]=++vcnt;
	for(int i=l;i<r;++i) {
		link(U[i][1],U[i+1][1]);
		link(U[i+1][0],U[i][0]);
		link(D[i][1],D[i+1][1]);
		link(D[i+1][0],D[i][0]);
	}
	link(D[r][0],D[r][1]);
	link(U[r][0],U[r][1]);
	for(int i=d;i<u;++i) {
		link(L[i][1],L[i+1][1]);
		link(L[i+1][0],L[i][0]);
		link(R[i][1],R[i+1][1]);
		link(R[i+1][0],R[i][0]);
	}
	link(L[u][0],L[u][1]);
	link(R[u][0],R[u][1]);
	for(auto re:a) {
		int tl,tr,tu,td;
		bool il=(tl=re.lox)<=l,ir=(tr=re.hix)>=r;
		bool id=(td=re.loy)<=d,iu=(tu=re.hiy)>=u;
		int sum=il+ir+id+iu;
		if(sum>=3) continue;
		if(sum==1) {
			if(il) {
				link(L[td-1][1],L[td-1][0]);
				link(L[tu][0],L[tu][1]);
			}
			if(ir) {
				link(R[td-1][1],R[td-1][0]);
				link(R[tu][0],R[tu][1]);
			}
			if(id) {
				link(D[tl-1][1],D[tl-1][0]);
				link(D[tr][0],D[tr][1]);
			}
			if(iu) {
				link(U[tl-1][1],U[tl-1][0]);
				link(U[tr][0],U[tr][1]);
			}
		}
		if(sum==2) {
			if(il&&iu) {
				link(U[tr][0],L[td-1][0]);
				link(L[td-1][1],U[tr][1]);
			}
			if(il&&id) {
				link(L[tu][0],D[tr][1]);
				link(D[tr][0],L[tu][1]);
			}
			if(ir&&iu) {
				link(U[tl-1][1],R[td-1][0]);
				link(R[td-1][1],U[tl-1][0]);
			}
			if(ir&&id) {
				link(R[tu][0],D[tl-1][0]);
				link(D[tl-1][1],R[tu][1]);
			}
			if(il&&ir) {
				link(L[td-1][1],R[td-1][0]);
				link(L[td-1][1],R[tu][1]);
				link(L[tu][0],R[td-1][0]);
				link(L[tu][0],R[tu][1]);
				link(R[td-1][1],L[td-1][0]);
				link(R[td-1][1],L[tu][1]);
				link(R[tu][0],L[td-1][0]);
				link(R[tu][0],L[tu][1]);
			}
			if(id&&iu) {
				link(D[tl-1][1],U[tl-1][0]);
				link(D[tl-1][1],U[tr][1]);
				link(D[tr][0],U[tl-1][0]);
				link(D[tr][0],U[tr][1]);
				link(U[tl-1][1],D[tl-1][0]);
				link(U[tl-1][1],D[tr][1]);
				link(U[tr][0],D[tl-1][0]);
				link(U[tr][0],D[tr][1]);
			}
		}
	}
	for(int i=1;i<=vcnt;++i) if(!dfn[i]) tarjan(i);
	for(int i=d;i<=u;++i) {
		bool lst0=(i==d||bel[L[i-1][0]]<bel[L[i-1][1]]);
		bool now1=bel[L[i][0]]>bel[L[i][1]];
		if(lst0&&now1) printf("%d %d\n",vx[l],vy[i]);
	}
	for(int i=d;i<=u;++i) {
		bool lst0=(i==d||bel[R[i-1][0]]<bel[R[i-1][1]]);
		bool now1=bel[R[i][0]]>bel[R[i][1]];
		if(lst0&&now1) printf("%d %d\n",vx[r],vy[i]);
	}
	for(int i=l;i<=r;++i) {
		bool lst0=(i==l||bel[D[i-1][0]]<bel[D[i-1][1]]);
		bool now1=bel[D[i][0]]>bel[D[i][1]];
		if(lst0&&now1) printf("%d %d\n",vx[i],vy[d]);
	}
	for(int i=l;i<=r;++i) {
		bool lst0=(i==l||bel[U[i-1][0]]<bel[U[i-1][1]]);
		bool now1=bel[U[i][0]]>bel[U[i][1]];
		if(lst0&&now1) printf("%d %d\n",vx[i],vy[u]);
	}
	return 0;
}
```

---

## 作者：Wilderness_ (赞：0)

### 思路
$k$ 的范围不大，先考虑枚举，发现 $n$ 范围较大，不能通过此题。

考虑在此基础上贪心，先选定 $k$ 个矩形，然后对其余矩形和枚举选定的矩形，若与其有相交部分则取相交所得的矩形。然而对于每个剩余矩形，有相交的矩形可能不止一个，而交的顺序不同可能导致最后答案也会不同，所以这个贪心是错误的。对此，所以我们考虑在此基础上进行随机化。

然而，若我们每次都打乱整个序列，仍会出现超时情况。因此我们每找出一个无法与前面所选矩形相交的矩形，就将其同前面的矩形随机交换。至此，便可以通过此题。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
	{
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
        putchar('-');
        write(-x);
        return;
    }
    if(x>9)write(x/10);
    putchar(x%10+48);
    return;
}
struct zf
{
	int x1,y1,x2,y2;
	friend bool operator!(zf b){return (!b.x1)&&(!b.y1)&&(!b.x2)&&(!b.y2);}
}p[500010],ans[5];
mt19937 dg(time(NULL));
int main()
{
	int n=read(),k=read();
	for(int i=1;i<=n;++i)p[i].x1=read(),p[i].y1=read(),p[i].x2=read(),p[i].y2=read();
	while(true)
	{
		auto U=[](zf a,zf b)
		{
			int lx=max(a.x1,b.x1),rx=min(a.x2,b.x2),dy=max(a.y1,b.y1),uy=min(a.y2,b.y2);
			if(lx>rx||dy>uy)return (zf){0,0,0,0};
			else return (zf){lx,dy,rx,uy};
		};
		bool fg=1;
		for(int i=1;i<=k;++i)ans[i]=p[i];
		for(int i=1;i<=n;++i)
		{
			int tp=0;
			for(int j=1;j<=k;++j)if(!(!U(p[i],ans[j])))tp=j;
			if(!tp)
			{
				fg=0;
				swap(p[i],p[dg()%(i-1)+1]);
				break;
			}
			ans[tp]=U(p[i],ans[tp]);
		}
		if(fg)
		{
			for(int i=1;i<=k;++i)write(ans[i].x1),putchar(' '),write(ans[i].y2),puts("");
			return 0;
		}
	}
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

给一个构造类随机化的通用流程：

- 判断当前状态在某种策略下是否存在方案。

- 如果存在，直接输出方案；如果不存在，对状态进行微扰再回到第一步。

微扰可以考虑 `random_shuffle`，但是在一般情况下，为了优化掉这个 $O(n)$，我们可以考虑 `swap`。

接下来考虑第一步，因为同一个情况下也可能有多种策略，我们可以考虑通过类似于贪心的思路来 $O(n)$ 判断是否存在方案，而不是暴力搜索。

最初考虑的是从 $1$ 到 $n$ 遍历，如果能放到当前组就放，否则就新建一个组。

但是这样是过不了的，因为每次放的组都是连续的区间，单次微扰并不能改变大致的分组。

此时，我们应该考虑随机分组。

注意到分成 $k$ 组一定不劣，因为如果不分成 $k$ 组把一组拆开显然不会让有解变成无解。

所以我们可以先把 $[1,k]$ 放到这 $k$ 组里面，对于每个 $i\in [k+1,n]$，考虑找到哪些组是可以放的，随机放到一个组里面即可；如果没有，报告无解。

这样做仍然过不了。

发现直接交换之后对无解的位置的微扰还是不够，仍然有可能出现在同样的位置，同样的矩形无解的情况。

考虑把这个位置变成有解，最简单的一种思路就是放到初始的矩阵里面，这样一定能让它自己变得可行。

上述过程都是在扩大单次微扰的效率和影响。

事实证明，上述做法可过。

---

## 作者：封禁用户 (赞：0)

### 题解
本题实际上就是将 $n$ 个矩形分出不大于 $k$ 组，使得每一组的矩形两两有交。

首先，有一个显而易见的**错误的**贪心策略：\
维护每一组矩阵的交集。对于第 $i$ 个矩阵（此时前 $i-1$ 个已分组），枚举 $k$ 组，若第 $j$ 组矩阵的交集与第 $i$ 个矩阵有交集，则将第 $i$ 个矩阵加入到第 $j$ 组。

容易发现，矩阵的加入顺序对答案有影响，而我们又不可能枚举全排列。

就能想到随机化。

令 $order_i$ 表示第 $i$ 个进行分组的矩阵。

那么每次循环，都要重新排列 $order$。\
但随机排列一次是 $\mathcal{O}(n\log n)$，显然会 TLE。

因此，考虑用 `swap` 代替 `random_shuffle`。

若第 $i$ 个进行分组的矩阵无法进行合法分组，则让该矩阵优先分组。\
即随机交换 $order_i,order_j,j<i$。

### 记录
![](https://cdn.luogu.com.cn/upload/image_hosting/nu16wib4.png)

---

