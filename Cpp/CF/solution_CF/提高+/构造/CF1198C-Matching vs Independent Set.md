# Matching vs Independent Set

## 题目描述

给定一个包含 $3 \cdot n$ 个顶点和 $m$ 条边的图。你需要找到一个大小为 $n$ 的匹配，或者一个大小为 $n$ 的独立集。

一组边称为匹配，当且仅当任意两条边没有公共端点。

一组顶点称为独立集，当且仅当任意两点之间都没有边相连。

## 说明/提示

前两个图是相同的，既存在大小为 $1$ 的匹配，也存在大小为 $1$ 的独立集。任意一种匹配或独立集都是正确答案。

第三个图不存在大小为 $2$ 的匹配，但存在大小为 $2$ 的独立集。实际上还存在大小为 $5$ 的独立集：2 3 4 5 6。但这样的答案不正确，因为题目要求找到恰好大小为 $n$ 的独立集（或匹配）。

第四个图不存在大小为 $2$ 的独立集，但存在大小为 $2$ 的匹配。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2
1 3
1 2
1 2
1 3
1 2
2 5
1 2
3 1
1 4
5 1
1 6
2 15
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
```

### 输出

```
Matching
2
IndSet
1
IndSet
2 4
Matching
1 15
```

# 题解

## 作者：81179332_ (赞：12)

另外两篇题解有些误人子弟了，根本就没有 `Impossible` 的情况，这道题实际上是一道构造题

我们每加入一条边，如果这条边的两个端点都没有被标记，那么我们把这两个端点标记一下，并将这条边加入边独立集中

加入所有边后，所有未标记的点即为点独立集中的点

正确性显然

为什么没有 `Impossible`？设最后边独立集中有 $x$ 条边，则点独立集中有 $3n-x$ 个点，易知这二者中必有一个 $\ge n$

```cpp
const int N = 500010;
bool book[N];
int n,m,ans[N],cnt;
int main()
{
	int T = read();
	while(T--)
	{
		n = read(),m = read();cnt = 0;
		for(int i = 1;i <= 3 * n;i++) book[i] = 0;
		for(int i = 1;i <= m;i++)
		{
			int u = read(),v = read();
			if(!book[u] && !book[v]) book[u] = book[v] = 1,ans[++cnt] = i;
		}
		if(cnt <= n)
		{
			puts("IndSet");int now = 0;
			for(int i = 1;i <= 3 * n && now < n;i++)
				if(!book[i]) pprint(i),now++;
			putchar('\n');
		}
		else
		{
			puts("Matching");
			for(int i = 1;i <= n;i++) pprint(ans[i]);
			putchar('\n');
		}
	}
}

```

---

## 作者：ljc20020730 (赞：5)

这是一个非常**无脑**的随机化算法。

首先你需要知道一个东西叫做$random\_shuffle()$这个函数可以帮助你随机地打乱一个数组。



判断独立集，如果数据存在一个合法的独立集的话，那么显然随机选择一个点，它有$\frac{1}{3}$的概率在独立集中，一旦确定了一个点在独立集中，我们显然可以构造出一个合法的独立集了。

如何保证正确性？我只需要多做几次就行了。

判断匹配也是相同的道理。

所以，这个题目可以在$O(n)$的复杂度内随机化出解。


```cpp
# include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,M=5e5+10;
vector<int>E[N];
struct node{
	int u,v;
}Edge[M];
bool vis[N];
int n,m,p[N],e[M],t[N];
bool work1()
{
	memset(vis,false,sizeof(vis));
	int cnt = 0; random_shuffle(p+1,p+1+3*n);
	for (int i=1;i<=3*n;i++) if (!vis[p[i]]) {
	 	t[++cnt]=p[i];
	 	if (cnt == n) {
	 		puts("IndSet");
	 		for (int j=1;j<=cnt;j++) printf("%d ",t[j]);
			puts(""); return true;
		 }
		 for (int j=0;j<(int)E[p[i]].size();j++) vis[E[p[i]][j]]=true;
	 }
	 return false;
}
bool work2()
{
	memset(vis,false,sizeof(vis));
	int cnt = 0; random_shuffle(e+1,e+1+m);
	for (int i=1;i<=m;i++) {
		int u=Edge[e[i]].u,v=Edge[e[i]].v;
		if (vis[u] || vis[v]) continue;
		vis[u] = vis[v] = 1;
		t[++cnt] = e[i];
		if (cnt == n) {
			puts("Matching");
	 		for (int j=1;j<=cnt;j++) printf("%d ",t[j]);
			puts(""); return true;
		}
	}
	return false;
}
int main()
{
	srand(time(NULL)*100007);
	int T; scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&m);
		for (int i=1;i<=3*n;i++) p[i]=i,E[i].clear();
		for (int i=1;i<=m;i++) e[i]=i;
		for (int i=1;i<=m;i++) {
			int u,v; scanf("%d%d",&u,&v);
			Edge[i]=(node){u,v};
			E[u].push_back(v);
			E[v].push_back(u);
		}
		int flag = 0;
		for (int i=1;i<=10;i++)
		 if (work1()) { flag = 1; break;}
		if (flag) continue;
		flag = 0;
		for (int i=1;i<=10;i++)
		 if (work2()) { flag = 1; break;}
		if (flag) continue;
		puts("Impossible");
	}
	return 0;
}

```


---

## 作者：_lyx111 (赞：3)

# CF1198C Matching vs Independent Set

[题目传送门](https://codeforces.com/problemset/problem/1198/C)

## 分析

维护一个点集 $S$ 和一个边集 $T$。初始时，$S=\{1,2,\cdots,3n\},T=\varnothing$。

遍历所有 $m$ 条边，若当前边 $(u,v)$ 满足 $u\in S$ 且 $v\in S$，那么完成以下两个操作：

1. 将点 $u,v$ 从 $S$ 中拿出来（此时 $|S|$ 减少 $2$）；

2. 将边 $(u,v)$ 加入集合 $T$（此时 $|T|$ 增加 $1$）。

那么遍历完所有边之后一定有 $S$ 是一个点独立集，$T$ 是一个边独立集,并且 $|S|+2|T|=3n$，由**抽屉原理**可以得到，$\max\{|S|,|T|\}\ge n$。

那么取 $S,T$ 中大小较大的一个输出就好了，要注意题目重要的是大小为 $n$ 的点独立集或边独立集，所以只要输出 $S$ 或 $T$ 的前 $n$ 个编号。

通过上述方法可以证明本题一定有解，不存在要输出 `Impossible` 的情况。

### [代码](https://codeforces.com/problemset/submission/1198/192248635)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：Zechariah (赞：2)

其实这题没有那么吓人  
在读入的边中依次找出两端点没有被标记的边并给端点打上标记，之后判断没被标记的点格式是否$\ge n$是的话输出$n$个没被标记的点就是独立集了；如果被找出来的边个数$\ge n$，输出$n$个就是一个边独立集(好像是叫这个)了  
都没有当然就Impossible啦  

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 4e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
bool flag[N];
int edge[N];

int main() {
	rg int T = fast_IO::read();
	while (T--) {
		rg int n = fast_IO::read(), m = fast_IO::read(), tot = 0;
		memset(flag, 0, sizeof(bool) * (n * 3 + 1)); *edge = 0;
		for (rg int i = 1; i <= m; ++i) {
			rg int x = fast_IO::read(), y = fast_IO::read();
			if (!flag[x] && !flag[y])flag[x] = flag[y] = true, tot += 2, edge[++*edge] = i;
		}
		if (3 * n - tot >= n) {
			puts("IndSet");
			for (rg int i = 1, num = 1; i <= 3 * n && num <= n; ++i)
				if (!flag[i])fast_IO::write(i), putchar(num == n ? '\n' : ' '), ++num;
		}
		else if (*edge >= n) {
			puts("Matching");
			for (rg int i = 1; i <= n; ++i)
				fast_IO::write(edge[i]), putchar(i == n ? '\n' : ' ');
		}
		else puts("Impossible");
	}
	return 0;
}

```


---

## 作者：_22222222_ (赞：1)

被搬到模拟的一道题，

当时好像有奇怪的贪心过了？

#### 题面

[link](https://www.luogu.com.cn/problem/CF1198C)

给定点数 $3\cdot n$ 边数 $m$ 的一张图 $G$，

你需要找到一组**大小为 $n$** 的匹配或者独立集。

#### solution 

注意到大小为 $n$ 的一个匹配，其点集大小为 $2\cdot n,$

而大小为 $n$ 的独立集，点集大小显然是 $n$,

而两者大小的和，显然是 $3\cdot n$。

所以，如果不存在一个大小为 $n$ 的独立集，则必然存在一个大小为 $n$ 的匹配。

反之亦然。

证明考虑接下来的构造方式：

对于每条边，尝试将其加入匹配。

如果成功加入 $n$ 条边，说明我们找到了一组合法匹配。

那么直接输出这 $n$ 条边编号就行了。

否则，因为匹配用掉的点数不足 $2\cdot n$，不在匹配中的点至少为 $n$。

然后，不在匹配中的点，其所有连边必然和在匹配中的点连边，

否则就可以将其加入匹配。

事实上，在匹配中的点集和不在匹配中的点集交集为空。

所以，我们选出 $n$ 个不在匹配中的点，它们两两不连边，

也就是说选出来一个大小为 $n$ 的独立集了。

~~所以 `Impossible` 是 `Impossible` 的。~~

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int o=2222222;
ifstream fin("choice.in");
ofstream fout("choice.out");
#define fin cin
#define fout cout
struct node{
	int s,t;
}p[o];
int v[o],n,m,ans1,ans2;
vector<int>ans;
void in(){
	fin>>n>>m;
	for(int i=1;i<=m;i++){
		fin>>p[i].s>>p[i].t;
	}
}
void work(){
	for(int i=1;i<=m;i++){
		int x=p[i].s,y=p[i].t;
		if(v[x]||v[y])continue;
		v[x]=v[y]=1;
		ans.push_back(i);
	}
	if(ans.size()>=n){
		while(ans.size()>n)ans.pop_back();
		ans2=1;return;
	}
	ans1=1;ans.clear();
	for(int i=1;i<=3*n;i++){
		if(!v[i])ans.push_back(i);
		if(ans.size()==n)return;
	}
}
void out(){
	if(ans1)fout<<"IndSet\n";
	if(ans2)fout<<"Matching\n";
	for(auto i:ans)fout<<i<<" ";
	fout<<"\n";
}
void clear(){
	for(int i=1;i<=m;i++)p[i]=p[0];
	for(int i=1;i<=3*n;i++)v[i]=0;
	ans.clear();
	ans1=ans2=0;	
}
int main(){
	ios::sync_with_stdio(0);
	fin.tie(0),fout.tie(0);
	int T;fin>>T;
	while(T--){
		in();work();out();clear();
	}
	return 0;
}
```


---

## 作者：duyi (赞：1)

# CF1198C Matching vs Independent Set

## 题意大意

[题目链接](https://codeforces.com/problemset/problem/1198/C)

给定一张 $3\cdot n$ 个节点、$m$ 条边，无自环、无重边的无向连通图。

定义一个**匹配**是一个边的集合，满足其中任意两条边没有公共端点。

定义一个**独立集**是一个点的集合，满足其中任意两个点没有边直接相连。

请你找出一个 $n$ 条边的匹配，**或**一个 $n$ 个点的独立集。

数据范围：$1\leq n\leq 10^5$，$0\leq m\leq 5\cdot 10^5$。

## 本题题解

容易想到去求最大匹配。但是求一般图最大匹配的带花树算法时间复杂度是 $\mathcal{O}(n^3)$ 的。

考虑退而求其次，找出任意一个**极大匹配**。具体来说：我们每次取出一条边，并将它的两个端点删掉（一个点被删掉后，所有与它相连的边也被删掉），如此重复直到图上没有边为止。显然：

- **被我们取出的边，是一个匹配**。因为一个点第一次被取到后，所有和它相连的边就都被删掉了，所以取出的边之间不会有公共点。
- **最终剩下的点，是一个独立集**。首先，最终状态下，剩下的点之间肯定没有边（否则就还能继续取）。并且它们之间原来也不会有边，因为原图上的一条边，不会在两个端点都未被删除的情况下，平白无故消失。

考虑最终我们取出的边的数量，记为 $k$。

- 若 $k \geq n$，则我们已经找出了一个 $n$ 条边的匹配。
- 若 $k < n$，因为这 $k$ 条边是匹配，所以没有公共端点，所以它们恰好占用了 $2k$ 个点，所以还剩下 $3n - 2k \geq n$ 个点。这意味着我们找出了一个 $n$ 个点的独立集。

综上所述，一定有解。

时间复杂度 $\mathcal{O}(n + m)$。

[参考代码-在CF查看](https://codeforces.com/contest/1198/submission/108219266)





---

## 作者：henrytb (赞：0)

题目让我们找出一个大小为 $n$ 的独立集或者匹配。

考虑假如我们手上已经有一组极大匹配了，由于它是极大的，那么所有不在匹配中的点之间就不可能有边了。因为如果有边，那么显然可以把这条边加进匹配里，让匹配更大，这样原来的极大性就不满足了。

所以问题变成了找一组极大匹配，如果匹配 $\ge n$ 那直接符合题意了，输出即可。

否则剩下的点数是 $3n - 2m$，其中 $m$ 表示匹配的边数，这里 $m$ 一定 $< n$，因此 $3n - 2m > n$。这样在剩下的点里选 $n$ 个点即可构成一个点独立集。

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1198C)

## 题目分析

图上构造题。

以任意顺序找出两端点没有标记的边，取出并标记端点，这样我们就得到了一个边集 $E$。

因为这些边的端点不重复，即边互不相连，则这是一个边的独立集。

这时可以判断 $n\le|E|$ 是否成立。

若成立，则存在符合要求的边的独立集，输出 $E$ 中的 $n$ 个元素。

否则存在符合要求的点的独立集，输出 $n$ 个未被标记的点。

上述做法的正确性基于结论。在一张无向图中，``IndSet`` 和 ``Matching`` 至少一个成立，即不存在 ``Impossible``。

假设 $|E| < n$，则已标记点的数量为 $2|E|$。

由反证法得，未标记点互不相连。若相连，则此两点间的边不应在 $E$ 外。

所以未标记点组成点的独立集 $P$，$|P|=3n-2|E|$。

显然 $3n-2|E|>n$ 成立，证毕。

## code

标记 b 数组按需清零，不要用 memset，笔者之前踩坑挂了几发。

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 500010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

template <typename T> inline void write(T x)
{
	char c[N], tot = 0;
	while (x)
	{
		c[++tot] = x % 10 + 48;
		x /= 10;
	}
	while (tot) putchar(c[tot--]);
}

int T, n, m, ans[N], tot;
bool b[N];

inline void work()
{
	read(n); read(m); tot = 0;
	for (rei i = 1; i <= n * 3; i++) b[i] = 0;
	for (rei i = 1; i <= m; i++)
	{
		int x, y;
		read(x), read(y);
		if (!b[x] && !b[y]) ans[++tot] = i, b[x] = b[y] = 1;
	} 
	if (tot >= n) 
	{
		printf("Matching\n");
		for (rei i = 1; i <= n; i++) write(ans[i]), putchar(' ');
	}
	else
	{
		printf("IndSet\n");
		tot = 0;
		for (rei i = 1; i <= n * 3 && tot < n; i++)
			if (!b[i]) write(i), putchar(' '), tot++;
	}
	putchar('\n');
}

int main()
{
	read(T); 
	while (T--) work();
	return 0;
}
```


---

