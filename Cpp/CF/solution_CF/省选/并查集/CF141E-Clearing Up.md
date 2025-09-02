# Clearing Up

## 题目描述

After Santa Claus and his assistant Elf delivered all the presents and made all the wishes come true, they returned to the North Pole and found out that it is all covered with snow. Both of them were quite tired and they decided only to remove the snow from the roads connecting huts. The North Pole has $ n $ huts connected with $ m $ roads. One can go along the roads in both directions.

The Elf offered to split: Santa Claus will clear up the wide roads and the Elf will tread out the narrow roads. For each road they decided who will clear it: Santa Claus or the Elf. To minimize the efforts they decided to clear the road so as to fulfill both those conditions:

- between any two huts should exist exactly one simple path along the cleared roads;
- Santa Claus and the Elf should clear the same number of roads.

At this point Santa Claus and his assistant Elf wondered which roads should they clear up?

## 说明/提示

A path is called simple if all huts on it are pairwise different.

## 样例 #1

### 输入

```
1 2
1 1 S
1 1 M
```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 3
1 2 S
1 3 M
2 3 S
```

### 输出

```
2
2 1 
```

## 样例 #3

### 输入

```
5 6
1 1 S
1 2 M
1 3 S
1 4 M
1 5 M
2 2 S
```

### 输出

```
-1
```

# 题解

## 作者：hsfzLZH1 (赞：11)

题目大意： 有一个 $n$ 个点 $m$ 条边的无向图，每条边可能有两种颜色 $S$ 或 $M$ ，请你判断是否存在并输出一种这样的方案，使得其生成树中边的颜色为 $S$ 和 $M$ 的正好各占一半。如果无解，输出 $-1$ ，否则先输出这样的生成树的边的个数，再输出一种合法的情况的边的集合。

$1\le n \le 10^3,1\le m \le 10^5$

很不错的一道思维题。

分步骤解决这个问题。

1.如果点数 $n$ 为偶数，那么其生成树的边数 $n-1$ 为奇数，不满足正好一半的条件，此时应输出 $-1$。

2.将所有可能加入的不构成环的颜色为 $S$ 的边加入（用并查集维护信息并判断是否有环出现）。如果能加入的边数小于 $\frac{n-1}2$，输出$-1$。之后形成的就是一个森林。

3.将所有能加入而不构成环的颜色为 $M$ 的边加入。如果此时不能形成一棵树，输出 $-1$。

4.将能加入而不使得颜色为 $M$ 的边构成环的边加入，直至颜色为 $M$ 的边的边数达到 $\frac{n-1}2$ 。此时每加入一条边对应的就是删除一条颜色为 $S$ 的边。如果能加入的颜色为 $M$ 的边的数量不够，输出 $-1$ 。

5.此时一定可以保证存在这样的答案。我们重新依次判断边的颜色为 $S$ 的边加入能否形成环，形成一棵生成树。

6.输出 $n-1$ 和生成树上的边的序号。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=100010;
int n,e,u,v,curs,curm,f[maxn],cnt,cnt2;
bool tf[maxm],ans[maxm];
char op;
struct edge
{
	int u,v,id;
}s[maxm],m[maxm];
int findp(int x){return f[x]?f[x]=findp(f[x]):x;}
int main()
{
	scanf("%d%d",&n,&e);
	if(!(n&1)){printf("-1\n");return 0;}
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d %c",&u,&v,&op);
		if(op=='S')curs++,s[curs].u=u,s[curs].v=v,s[curs].id=i;
		else curm++,m[curm].u=u,m[curm].v=v,m[curm].id=i;
	}
	for(int i=1;i<=curs;i++)
	{
		u=findp(s[i].u);
		v=findp(s[i].v);
		if(u!=v)cnt++,f[u]=v;
	}
	if(cnt<(n-1)/2){printf("-1\n");return 0;}
	for(int i=1;i<=curm;i++)
	{
		u=findp(m[i].u);
		v=findp(m[i].v);
		if(u!=v)tf[i]=true,cnt2++,f[u]=v;
	}
	if(cnt+cnt2<n-1){printf("-1\n");return 0;}
	memset(f,0,sizeof f);
	for(int i=1;i<=curm;i++)if(tf[i])
	{
		u=findp(m[i].u);
		v=findp(m[i].v);
		if(u!=v)f[u]=v,ans[m[i].id]=true;
	}
	for(int i=1;i<=curm&&cnt2<(n-1)/2;i++)if(!tf[i])
	{
		u=findp(m[i].u);
		v=findp(m[i].v);
		if(u!=v)cnt2++,f[u]=v,ans[m[i].id]=true;
	}
	if(cnt2<(n-1)/2){printf("-1\n");return 0;}
	for(int i=1;i<=curs;i++)
	{
		u=findp(s[i].u);
		v=findp(s[i].v);
		if(u!=v)f[u]=v,ans[s[i].id]=true;
	}
	printf("%d\n",n-1);
	for(int i=1;i<=e;i++)if(ans[i])printf("%d ",i);
	printf("\n");
	return 0;
}
```

---

## 作者：_Railgun (赞：3)

### 形式化题意：

给定一张 $n$ 点 $m$ 边的图，每条边为黑色或者白色，问你是否存在一个生成树，满足恰好一半的边是黑色，一半白色。有解请给出方案，否则输出 -1.

$1 \le n \le 10^3, 1 \le m \le 10^5$.

时间限制：1s。

### 正解

> 闲话，在读 cf tutorial 的时候不懂，翻评论找证明看到说是需要拟阵来证明？非常震撼，遂来洛谷看题解，感觉还是讲的不是很清楚，后来问同学得到了一个感觉没问题的解法以及证明，遂打算发上来。

首先考虑一个引理，假设一个图中有 $w$ 条不成环的白色边和若干黑色边，且这个图联通，那么存在一个生成树包含所有 $w$ 条白色边。证明考虑先钦定选 $w$ 条白色边，然后逐渐加入黑色边构成树。如果这个不够清晰，那么考虑令白色边权值为 $-1$ 黑色边为 $1$，对图跑 kruskal，不难发现由于白色边不构成环所以前 $w$ 条白色边必然都会被我们贪心的 kruskal 加入(模拟 kruskal，能加入的边贪心加入)，由于 kruskal 正确，所以我们可以跑出来 "最小生成树"，并且保证包含 $w$ 条白色边。

**于是我们就是想找是否存在那么 $(n-1)/2$ 条白色边，他们自己不成环，同时加入所有黑色边之后图联通。**

现在考虑一开始我们加入所有黑色边(用并查集维护)，此时如果图不连通，就说明我们必须要一些白色边来构成生成树，如果我们需要超过 $(n-1)/2$ 条白色边使图联通显然无解，否则如果不到 $(n-1)/2$ 条边，我们直接任取一个把图联通的边集，钦定选这些边，假设只考虑白色边，我们钦定选这些之后，再去选择一些边，保证不成环，凑到 $(n-1)/2$ 条白边即可。

接下来我们说明任取一个白色边集使得加入所有黑边联通，然后删除所有黑边，加不成环白边是正确的。

首先我们如果能找到方案，一定满足选这些白色边之后，加入所有黑色边图联通，这是因为一开始钦定选的那些白色边就已经保证了图联通，故我们找到一个解选择恰一半不成环白边，加入所有黑边图联通的白边集，按照引理的证明跑 kruskal 就可以找到所求解。

接下来证明一开始任选一个白边集不会影响后续的选取，即如果有解，一开始怎么选都有解，考虑我们存在一个解，选择的白边集合称为 $A$，我们现在选的让图联通的边集称为 $B$，如果我们总能从 $A$ 里挑一条 $B$ 中没有的边，并且和 $B$ 原有的边不构成环，直到 $B$ 和 $A$ 大小相同，是不是就意味着怎么选都无所谓了，因为我们总可以从某个不知名的解里挑边，直到我们的集合也选择一半的不成环白边，满足要求。

来证明这个定理，注意到 $B$ 集合大小一直小于 $A$ (在相等之前)，那么 $A$ 对应的连通块个数就要少一些(边越多连通块越少)，那么 $A$ 中一定存在一个连通块，包含 $B$ 中至少两个不同连通块之间的点，否则如果 $A$ 中某个连通块至多包含 $B$ 中一个连通块的点，$A$ 的连通块个数一定不小于 $B$ 与假设矛盾，现在不妨设这个连通块是 $X$，包含了 $B$ 对应的 $Y$ 和 $Z$ 连通块，那么考虑将 $X$ 中的点分成 $Y$ 部分和 $Z$ 部分，显然存在一条联通 $Y$ 和 $Z$ 的边，这条边满足加入 $B$ 不成环，因为联通了新连通块，而且不在 $B$ 中，否则 $Y$ 和 $Z$ 会是同一个连通块，于是我们找到一条边，即定理得证。

希望我讲清楚了，最后总结一下：

先把所有黑边加入并查集，接下来加入一些白边使整个图变成一棵树(联通)，证明了如果有解随便选白边集合都有解于是直接选这些边，然后清空并查集，加入这些已经确定的边，然后考虑其他白边，如果他们加进去不成环就加入，直到我们有 $(n-1)/2$ 条白边，由于一开始的定理我们知道此时有解，故只需要再重新考虑黑边，一条条加边构成树即可。

(说实话真的觉得没必要附代码)。

```cpp
int n, m;
vv<array<int, 3>> E;
char str[10];
int fa[1010];
 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return false; 
	else return fa[x] = y, true;
}
 
int main() {
	in(n, m), E.resize(m + 2);
	if (n % 2 == 0) return puts("-1"), 0;
	u32 K = n / 2; // 注意.
	Fr (i, 1, m) in(E[i][0], E[i][1]), scanf("%s", str), E[i][2] = str[0] == 'S';
	Fr (i, 1, n) fa[i] = i;
	Fr (i, 1, m) if (E[i][2]) merge(E[i][0], E[i][1]);
	set<int> ts1;
	Fr (i, 1, n) ts1.insert(find(i));
	if (ts1.size() > K + 1) return puts("-1"), 0;
	vv<int> Ans, t2;
	Fr (i, 1, m) if (!E[i][2] && merge(E[i][0], E[i][1])) Ans.eb(i);
	else if (!E[i][2]) t2.eb(i);
	int t1 = find(1); Fr (i, 2, n) if (find(i) != t1) return puts("-1"), 0;
	Fr (i, 1, n) fa[i] = i;
	for (auto i : Ans) merge(E[i][0], E[i][1]);
	for (auto i : t2) {
		if (Ans.size() == K) break;
		if (merge(E[i][0], E[i][1])) Ans.eb(i);
	}
	if (Ans.size() < K) return puts("-1"), 0;
	Fr (i, 1, m) if (E[i][2] && merge(E[i][0], E[i][1])) Ans.eb(i);
	out(Ans.size()), out(Ans);
	return 0;
}
```


### 夹带私货

是这样的，凡思维题必有猥琐解法。

选 $k$ 白边这个东西听起来是不是很 wqs 二分？但是 wqs 只能求截距而不能求具体方案，但是如果恰好切到那个点跑出来的不就是方案吗，直接随机化赋值所有边权，那么现在 $f(t)$ 表示恰好选 $t$ 白边的最小生成树权值，这玩意前人证明过是凸函数，我们现在如果选 $k$ 这个点不和之前的 $(k - 1, f(k - 1))$ 共线就会恰好切到 $(k, f(k))$，那么此时跑出来的 kruskal 就是我们所求的方案，直接 while 卡时 + 随机化 wqs 二分，亲测可过，事实上你跑五遍就过去了，不需要卡时(卡时当然最好)。

```cpp
using i64 = int64_t;
std::mt19937_64 mt_rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
#define rnd(l, r) std::uniform_int_distribution<i64>(l, r)(mt_rnd)
 
const int M = 1e5 + 5, N = 1e3 + 5;
const int INF = 1e5 + 5;
 
int n, m;
 
struct Edge {
	int u, v, ty, id, val;
	friend bool operator<(const Edge &a, const Edge &b) {
		if (a.val != b.val) return a.val < b.val;
		return a.ty < b.ty;
	}
} e[M];
std::vector<int> ans;
 
void randomValue() {
	for (int i = 1; i <= m; ++i) {
		e[i].val = rnd(1, INF) * e[i].ty;
	}
}
int sum, block;
int f[N];
inline int find(int x) {
	return x == f[x] ? x : f[x] = find(f[x]);
}
void check(int add) {
	for (int i = 1; i <= m; ++i) {
		if (e[i].ty == 1) {
			e[i].val += add;
		}
	}
	for (int i = 1; i <= n; ++i) {
		f[i] = i;
	}
	sum = 0;
 
	std::sort(e + 1, e + m + 1);
	block = n;
	for (int i = 1; i <= m && block > 1; ++i) {
		int u = e[i].u, v = e[i].v;
		u = find(u), v = find(v);
		if (u != v) {
			sum += e[i].ty;
			f[u] = v;
			--block;
		}
	}
	if (sum == 0 && block == 1) {
		for (int i = 1; i <= n; ++i) {
			f[i] = i;
		}
		int block = n;
		for (int i = 1; i <= m && block > 1; ++i) {
			int u = e[i].u, v = e[i].v;
			u = find(u), v = find(v);
			if (u != v) {
				ans.push_back(e[i].id);
				f[u] = v;
				--block;
			}
		}
	}
 
	for (int i = 1; i <= m; ++i) {
		if (e[i].ty == 1) {
			e[i].val -= add;
		}
	}
}
 
bool useful() {
	int l = -INF * 3, r = INF * 3;
	bool suc = false;
	while (l <= r) {
		int mid = l + ((r - l) >> 1);
		check(mid);
		if (sum == 0 && block == 1) {
			suc = true;
			break;
		} else if (sum < 0) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return suc;
}
 
signed main() {
	clock_t c = clock();
	std::cin.tie(nullptr)->sync_with_stdio(false);
 
	std::cin >> n >> m;
	if (n % 2 == 0) {
		puts("-1");
	} else if (n == 1) {
		puts("0");
	} else {
		for (int i = 1; i <= m; ++i) {
			int u, v; char ty;
			std::cin >> u >> v >> ty;
			e[i] = {u, v, ty == 'S' ? -1 : 1, i, 0};
		}
		
		// while ((double)(clock() - c) / CLOCKS_PER_SEC <= 0.9) {
		for (int i = 1; i <= 5; ++i) {
			randomValue();
			useful();
		}
			// if (useful()) break;
		// }
		if (ans.size() == (unsigned)0) {
			puts("-1");
		} else {
			std::cout << n - 1 << '\n';
			for (int i = 0; i < n - 1; ++i) {
				std::cout << ans[i] << " \n"[i == n - 2];
			}
		}
	}
}
```

---

## 作者：Hoks (赞：1)

## 前言
很好的一道思维题，看到这题首先想到的是 [Tree I](https://www.luogu.com.cn/problem/P2619)，但其实关联不是很大？

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先看到这个题肯定是不好做的。

因为要求的是一个生成树，所以不能有环。

而我们又要保证两种颜色数量相同，看上去就很难办。

同时维护两种颜色未免有点太哈人了，考虑单调性搞下一种颜色再维护另一种颜色。

首先当点数为偶数时，显然无解，因为无法均分。

显然的是同一种颜色的边连成的环是无意义的，所以我们先固定一种颜色（这里是 `M`），把所有 `M` 边不成环的全部加进来。

接着尝试加入不成环的 `S` 边。

加完后如果图的形态不是一棵树显然是无解的，若 `S` 数量大于一半也是无解的。

因为我们优先加入所有可行的 `M` 边已经保证 `M` 边是极大的了，如果这样了还没有到一半显然是无解的。

接着考虑去掉一些 `M` 边加入些 `S` 边。

实现上即为找到一条 `S` 边满足他两端点的路径上还有 `M` 边，把这条边放进来。

思考下为什么这样是对的。

因为最初 `M` 边已经极大了，所以一条条减下来，肯定能找到刚好均分的情况。

若没找到则是无解。

那为什么满足**两端点的路径上还有 `M` 边**的 `S` 边都是等价的呢？

因为加上这条边，肯定可以去掉一条 `M` 边，使得 `M` 边减少 `S` 边增加。

因为去掉一条 `M` 边很难办，所以我们可以考虑最后再扫一遍 `M` 边，把未成环的都加进来，成环的都扔掉。

实现时并查集即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,V=1e5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
struct query{int u,v,w,id;}e[N];
int n,m,l,k,tot,mp[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
struct DSU
{
    vector<int> h;
    inline void init(int n){h=vector<int>(n+10);for(int i=1;i<=n;i++) h[i]=i;}
    inline int find(int x){return h[x]==x?x:h[x]=find(h[x]);}
}f;
inline bool cmp(query x,query y){return x.w<y.w;}
signed main()
{
    n=read(),m=read();for(int i=1;i<=m;i++) e[i].u=read(),e[i].v=read(),rd(s,l),l=0,e[i].w=(s[1]=='M'),e[i].id=i;
    sort(e+1,e+1+m,cmp);f.init(n);
    for(int i=m;i>=1;i--)
    {
        int x=f.find(e[i].u),y=f.find(e[i].v);
        if(x==y) continue;mp[i]=1;tot+=!e[i].w,k++,f.h[x]=y;
    }if(k!=n-1||!(n%2)||tot>n/2){put("-1");goto genshin;}f.init(n);
    for(int i=1;i<=m&&!e[i].w;i++) if(mp[i]){int x=f.find(e[i].u),y=f.find(e[i].v);f.h[x]=y;}
    for(int i=1;i<=m&&tot<n/2;i++)
    {
        if(e[i].w) break;if(mp[i]) continue;
        int x=f.find(e[i].u),y=f.find(e[i].v);
        if(x==y) continue;mp[i]=1;tot++;f.h[x]=y;
    }
    if(tot!=n/2){put("-1");goto genshin;}
    for(int i=1;i<=m;i++)
    {
        if(!e[i].w||!mp[i]) continue;
        int x=f.find(e[i].u),y=f.find(e[i].v);
        if(x==y){mp[i]=0;continue;}f.h[x]=y;
    }print(n-1);put('\n');for(int i=1;i<=m;i++) if(mp[i]) print(e[i].id),put(' ');
    genshin:;flush();return 0;
}
```

---

