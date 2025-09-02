# Treeland Tour

## 题目描述

The "Road Accident" band is planning an unprecedented tour around Treeland. The RA fans are looking forward to the event and making bets on how many concerts their favorite group will have.

Treeland consists of $ n $ cities, some pairs of cities are connected by bidirectional roads. Overall the country has $ n-1 $ roads. We know that it is possible to get to any city from any other one. The cities are numbered by integers from 1 to $ n $ . For every city we know its value $ r_{i} $ — the number of people in it.

We know that the band will travel along some path, having concerts in some cities along the path. The band's path will not pass one city twice, each time they move to the city that hasn't been previously visited. Thus, the musicians will travel along some path (without visiting any city twice) and in some (not necessarily all) cities along the way they will have concerts.

The band plans to gather all the big stadiums and concert halls during the tour, so every time they will perform in a city which population is larger than the population of the previously visited with concert city. In other words, the sequence of population in the cities where the concerts will be held is strictly increasing.

In a recent interview with the leader of the "road accident" band promised to the fans that the band will give concert in the largest possible number of cities! Thus the band will travel along some chain of cities of Treeland and have concerts in some of these cities, so that the population number will increase, and the number of concerts will be the largest possible.

The fans of Treeland are frantically trying to figure out how many concerts the group will have in Treeland. Looks like they can't manage without some help from a real programmer! Help the fans find the sought number of concerts.

## 样例 #1

### 输入

```
6
1 2 3 4 5 1
1 2
2 3
3 4
3 5
3 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 2
1 3
2 4
3 5
```

### 输出

```
3
```

# 题解

## 作者：Piwry (赞：43)

模拟赛做到这题的加强版（$n\leq 2\cdot 10^5$），然而我一直没想到另维护一个下降子序列，结果最后只写出一个 $n^2$ 换根 \kk

写完才发现文章有点长，因此有许多细节部分可能因为排版混乱（不太会排长文章...）导致表意不清，还请见谅qaq

有疑惑可以在评论区问我

## 解析

这题的做法好像还蛮多的...这里就把目前我知道的做法都讲一遍把X

### 换根做法（$O(n^2)$）

首先任意规定一个根做树 dp，计算出以每个结点为子序列结尾，子序列开头在其**子树**内的最长上升子序列长度。转移可以暴力转，也可以用各种方式优化

此时根的 dp 值就是以根为子序列结尾，能得到的最长上升子序列长度

接着考虑换根。可以每次直接暴力转移受影响的两个结点的 dp 值。这个转移我想不到什么能优化的方法（也成为了这种做法的复杂度瓶颈 \kk）

对每次换根得到的 dp 值取 $\max$ 即可

### 一个 trick

（其实也不算是 trick，但我想不出更合适的小标题名字...）

在换根 dp 做法中，我们始终默认当前结点是整个上升子序列的结尾，从而导致最后非换根不可。因为这样我们无法统计当前结点为序列**中间点**时的答案

于是思考有没有办法维护当前结点为序列中间点时的答案。可以发现，这实际上就是把一个以当前结点为结尾的上升子序列和**下降子序列** “拼” 起来（合并）

不过这样还是有些问题，我们没法统计到当前结点为中间点，子序列**一部分在父亲处**的答案。实际上，在每个结点处，我们只需统计两部分分别在该结点两个儿子子树中的子序列就行了

于是只需另维护一个下降子序列，在每个结点处均两两合并统计一次答案即可

### 合并的具体方式

上一节提到的 “把一个以当前结点为结尾的上升子序列和下降子序列 ‘拼’ 起来” 的具体实现其实还有待商讨

（首先在合并每个子树的线段树/数组前，我们都**默认**先将当前结点插入线段树/数组，以方便讨论。因为求的是严格上升子序列，因此这样不会对答案造成影响（即使求的不是严格上升子序列，也可以考虑在统计合并的答案后，还原新的线段树/数组，再将新线段树/数组合并））

可以发现，如果在将所有**儿子**子树贡献都合并后（因具体做法而异）再找一条最长上升子序列和最长下降子序列拼在一起，它们之间可能会有**共用**的元素。具体来说，不应当组合来自同一个儿子子树的最长上升子序列和最长下降子序列

形式化地讲，我们有 $m$ 个集合 $A_1, A_2, \cdots, A_m$，最后答案 $(a, b)$（$a, b$ 之间无序） 必须满足 $a\in A_i, b\in A_j, i\not=j$

设 $f(A, B)$ 表示统计所有 $(a, b)$ 满足 $a\in A, b\in B$。如果暴力地枚举带入 $A_i$，则共需要计算 $m^2$ 次 $f(A, B)$（况且每次计算的复杂度也不低）。我们考虑一个方法：

设当前已合并的集合 $S$（初始为空），新加入的集合 $A_i$，我们计算一次 $f(S, A_i)$，然后再将 $A$ 并入 $S$，如此重复。可以证明这样和刚才的方式是等价的

考虑一个元素 $a\in A_i$。在 $A_i$ 被并入 $S$ 时，$f$ 统计了所有可能的 $(a, b)$ 满足 $a\in A_i, b\in A_j, j<i$；在 $A_i$ 被并入 $S$ 后，$f$ 统计了所有可能的 $(a, b)$ 满足 $a\in A_i, b\in A_j, j>i$。由此可证得每种合法的 $(a, b)$ 都被统计了

$f(A, B)$ 的计算是可以优化的，但根据具体实现其方式可能有不同。在下面**每节的最后**都会分析合并的复杂度

### dsu on tree I（$O(n\log^2 n)$）

不带修改的全局子树贡献统计——很自然地就能想到 dsu on tree

如果按 “换根做法” 那一节的 dp 方式，需要用线段树优化转移（权值线段树，动态开点。动态开点按本题数据范围可能不需要）

具体来说，我们开 $\log n$ 个线段树；若某个结点到根经过了 $i$ 条轻边，就使用第 $i+1$ 个线段树。dfs 到 $u$ 时，先继承重儿子的线段树，将 $u$ 插入该线段树，再暴力地将所有轻儿子子树内结点插入该线段树

由于 dfs 同一时刻只会处理一条到根经过了 $i$ 条轻边的重链，因此线段树的占用不会冲突。但是记得在**叶子结点**重置线段树

每次继承重儿子线段树并插入的复杂度是 $O(\log n)$ 的；每个结点**每次**作为轻儿子子树内结点被暴力统计的复杂度是 $O(\log n)$ 的。因此这部分的总复杂度为 $O(n\log n+n\log^2 n)$

&nbsp;

最后考虑如何快速合并最长上升子序列和最长下降子序列

考虑在**合并轻儿子子树前**先统计每个轻儿子子树内结点作为答案链的中间一点的情况

具体来说，若假设 $x$ 作为答案链的中间一点，那么就在继承的重儿子线段树中查找出适合的上升/下降链拼上去，并与答案比较

每个轻儿子子树内结点每次被统计贡献的复杂度是 $\log n$ 的。最终复杂度就为 $O(n\log n+n\log^2 n+n\log^2 n)$

### dsu on tree II（$O(n\log^2 n)$）

同样是 dsu on tree，还可以考虑用维护辅助数组的 dp 方法

设 $g(k)$ 表示长度为 $k$ 的子序列末端最小/最大的元素。可以发现 $g(k)$ 的值随 $k$ 的增加是单调的，于是就可以二分转移

具体来说，我们仍旧开 $\log n$ 个 `g` 数组。dfs 到 $u$ 时，直接继承重儿子的 `g` 数组，二分得到 `dp[u]`，然后按下标暴力合并轻儿子的 `g` 数组（注意每 dfs 完一个轻儿子就要合并，不然数组使用会冲突）

每次计算 `dp[.]` 的复杂度是 $O(\log n)$ 的；`g` 数组最坏大小为子树大小，因此我们就粗略地将合并 `g` 数组视为暴力统计子树内的每个结点，且统计单个结点的复杂度为 $O(1)$，因此每个结点对暴力统计的复杂度做出的贡献就可以视为是 $O(\log n)$ 的（实际上并跑不满）。于是这部分的总复杂度就为 $O(n\log n+n\log n)$

&nbsp;

最后考虑如何快速合并

在合并轻儿子子树前，我们仍旧考虑先统计轻儿子子树内结点作为答案链的中间一点的情况，但这个结点**必须在该子树的 `g[.]` 中出现过**（实现时只遍历轻儿子的 `g` 数组就行了）

具体来说，若假设 $x$ 作为答案链的中间一点，那么就在继承的重儿子 `g[.]` 中二分查找出适合的上升/下降链拼上去，并与答案比较

每个轻儿子子树内结点每次被统计贡献的复杂度是 $\log n$ 的。最终复杂度就为 $O(n\log n+n\log n+n\log^2 n)$

### 线段树合并（$O(n\log n)$）

思考 “dsu on tree” 中的第一种实现方法，可以想到每次不一个个暴力插入轻儿子子树内的结点，而是直接**合并轻儿子的线段树**。接着还发现，这时候复杂度已经和 dsu on tree 没什么关系了，每次也不需要一定先继承重儿子的线段树，继承任意一个线段树就可以了

每次继承线段树并插入的复杂度是 $O(\log n)$ 的；线段树合并的总复杂度是 $O(n\log n)$ 的。因此这部分的总复杂度为 $O(n\log n+n\log n)$

&nbsp;

考虑如何统计合并的答案

看起来我们只能暴力遍历新线段树中的每个元素（叶节点）并为它们在已合并的线段树找到合适的链 “拼” 上去，但实际上我们可以直接在线段树合并时统计答案

首先维护的最长上升和最长下降子序列的信息可以放到一个线段树中；

具体来说，设我们正在合并的两个线段树结点 $x1, x2$，我们只考虑统计跨 $mid=\frac {l_x+r_x} 2$ 的答案，那么显然只需在 $[l, mid]$ 中找出一条最长的 最长上升/下降子序列 与 $[mid+1, r]$ 中找出的一条最长的 最长上升/下降子序列 拼在一起。这样找出的两条拼在一起一定是合法的，因为线段树的下标即为结尾元素的值。而这个操作显然可以在合并 $x1, x2$ 的递归函数中 $O(1)$ 完成

最后统计出来的答案也是不遗漏的

也可参考这段代码：

```cpp
void merge(int &x1, int x2){
	/*...*/
	int tmp =max(data_LIS[ls[x1]]+data_LDS[rs[x2]], data_LIS[rs[x1]]+data_LDS[ls[x2]]);
	Ans =max(Ans, tmp);
	merge(ls[x1], ls[x2]), merge(rs[x1], rs[x2]);
}
```

这样，答案统计的复杂度就被均摊到线段树合并中了。最终复杂度就为 $O(n\log n+n\log n+n\log n)$

### 长剖（$O(n\log n)$）

思考 “dsu on tree” 中的第二种实现方法，我们的 `g[.]` 的下标上限实际上是和当前链长（深度）有关的，并且计算 `dp[.]` 的复杂度和 dsu on tree 部分无关，因此可以考虑用长剖优化

具体实现直接套用长剖维护 `g[.]` 的合并就行了，如对长剖不熟悉可以参考后面的代码

每次计算 `dp[.]` 的复杂度是 $O(\log n)$ 的；计算 `g[.]` 的总复杂度是 $O(n)$ 的。因此这部分的总复杂度为 $O(n\log n+n)$

&nbsp;

考虑如何统计合并的答案

在合并轻儿子子树前，我们仍旧考虑先统计轻儿子子树内结点作为答案链的中间一点的情况。和 dsu on tree II 一样，这个结点**必须在该子树的 `g[.]` 中出现过**（实现时只遍历轻儿子的 `g` 数组就行了）

具体来说，若假设 $x$ 作为答案链的中间一点，那么就在继承的重儿子 `g[.]` 中二分查找出适合的上升/下降链拼上去，并与答案比较

（上面两段也基本都是 copy 的X）

每条链会且仅会被合并一次。即使 `g` 数组都是最坏情况，即下标为每条链的链长，每条链在被合并、统计答案时，统计答案部分也只会做出 $O(\log n)$ 乘链长（`g` 数组下标）的复杂度。于是总的复杂度就为 $O(n\log n+n+n\log n)$

&nbsp;

这种做法理论上应该是跑得最快的了，并且复杂度瓶颈是在 `lower_bound`（二分查找）。不过我的实现貌似并不优秀，并且为了方便直接用 `vector` 实现了长剖，因此常数可能会有点大 \kk

## CODE

这里只实现了两种

### 换根做法

注意每次从 dfs 返回时要还原 dp 值，否则后面暴力转移时会出错

```cpp
#include <cstdio>
#include <vector>
using std::vector;
using std::max;

const int MAXN =6e3+50;

/*------------------------------Map------------------------------*/

vector<int> E[MAXN];

inline void addedge(int u, int v){
	E[u].push_back(v), E[v].push_back(u);
}

/*------------------------------Dfs------------------------------*/

int Ans =0;
int a[MAXN];
int dp[MAXN];

int dfs_find(int u, int fa, const int &val){
	int ret =(a[u] < val) ? dp[u] : 0;
	for(int v:E[u])
		if(v != fa)
			ret =max(ret, dfs_find(v, u, val));
	return ret;
}

void dfs1(int u, int fa){
	for(int v:E[u])
		if(v != fa)
			dfs1(v, u);
	dp[u] =0;
	dp[u] =dfs_find(u, fa, a[u])+1;
	Ans =max(Ans, dp[u]);
}

void dfs2(int u, int fa){
	for(int v:E[u])
		if(v != fa){
			int tmp1 =dp[u];
			dp[u] =0;
			dp[u] =dfs_find(u, v, a[u])+1;
		//	Ans =max(Ans, dp[u]);/*一定不更优*/
			
			int tmp2 =dp[v];
			dp[v] =0;
			dp[v] =dfs_find(v, 0, a[v])+1;
			Ans =max(Ans, dp[v]);
			dfs2(v, u);
			
			dp[u] =tmp1;
			dp[v] =tmp2;/*<- 需要还原*/
		}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read();
	for(int i =1; i <= n; ++i)
		a[i] =read();
	for(int i =0; i < n-1; ++i)
		addedge(read(), read());
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%d", Ans);
}
```

### 长剖做法

这里为了方便，直接通过将元素取反、维护最长上升子序列的方式来维护最长下降子序列

写得可能不是很标准...仅供参考

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "-funroll-loops", "-fdelete-null-pointer-checks")
#pragma GCC target("ssse3", "sse3", "sse2", "sse", "avx2", "avx")
using std::vector;
using std::max;
using std::min;
using std::lower_bound;

const int MAXN =6e3+50;

/*------------------------------Map------------------------------*/

vector<int> E[MAXN];

inline void addedge(int u, int v){
	E[u].push_back(v), E[v].push_back(u);
}

/*------------------------------Dfs------------------------------*/

int Ans =1;
int a[MAXN];

inline void add(vector<int> &v, const int &ai){/*更新 LIS/LDS*/
	int len =lower_bound(v.begin(), v.end(), ai)-v.begin()-1;
	if(len+1 >= (int)v.size())
		v.push_back(ai);
	else
		v[len+1] =min(v[len+1], ai);
}

void updata_ans(const vector<int> &v1, const vector<int> &v2){
	for(int len_v1 =0; len_v1 < (int)v1.size(); ++len_v1)
		Ans =max(Ans, len_v1 + (int)(lower_bound(v2.begin(), v2.end(), -v1[len_v1])-v2.begin()-1));
}

inline void vector_free_memory(vector<int> &v){/*释放 vector 内存 ( 实际上在本题没啥必要 X )*/
	vector<int> tmp;
	v.swap(tmp);
}

void merge(vector<int> &v1, vector<int> &v2){/*合并 v2 到 v1*/
	for(int i =0; i < (int)v2.size(); ++i){
		/*注意 g[.] 的下标上限不一定就等于链长*/
		/*因此即使继承了长儿子的 g[.]，也要考虑下标越界的情况*/
		if(i >= (int)v1.size())
			v1.push_back(v2[i]);
		else
			v1[i] =min(v1[i], v2[i]);
	}
	vector_free_memory(v2);
}

/*下面这些即为题解中所述的 "g[.]"*/
vector<int> tail_LIS[MAXN];/*长度为 i 的最小结尾元素；可知随 i 减小 tail[i] 单调不增*/
vector<int> tail_LDS[MAXN];/*同上，这里为了方便直接将元素都取反了*/

int dfs(int u, int fa){
	int mxlen =0, mxi =-1;
	for(int v:E[u])
		if(v != fa){
			int tmp =dfs(v, u);
			if(tmp > mxlen)
				mxlen =tmp, mxi =v;
		}
	tail_LIS[u].push_back(-0x7f7f7f7f), tail_LIS[u].push_back(a[u]);
	tail_LDS[u].push_back(-0x7f7f7f7f), tail_LDS[u].push_back(-a[u]);
	if(mxi != -1){
		int v =mxi;
		add(tail_LIS[v], a[u]), add(tail_LDS[v], -a[u]);
		updata_ans(tail_LIS[u], tail_LDS[v]);
		updata_ans(tail_LDS[u], tail_LIS[v]);
		tail_LIS[u].swap(tail_LIS[v]);
		tail_LDS[u].swap(tail_LDS[v]);
	}
	for(int v:E[u])
		if(v != fa && v != mxi){
			add(tail_LIS[v], a[u]), add(tail_LDS[v], -a[u]);
		/*1. 更新答案 - 有用到一个小 trick*/
		/*2. 虽然两个集合都可能有以 a[u] 结尾的链，但它们并不会连在一起*/
		/*2. 如果 < 被改成 <=，也可做：*/
		/*2. 具体来说，每次给 v 的答案加上 a[i]，与已遍历的 u 答案合并，再还原 v 的答案并加入已遍历的 u 答案即可 V*/
			updata_ans(tail_LIS[v], tail_LDS[u]);
			updata_ans(tail_LDS[v], tail_LIS[u]);
		//	modify(tail_LIS[v]), modify(tail_LDS[v]);/*<- 就像这样 2.*/ 
			merge(tail_LIS[u], tail_LIS[v]);
			merge(tail_LDS[u], tail_LDS[v]);
		}
	return mxlen+1;
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read();
	for(int i =1; i <= n; ++i)
		a[i] =read();
	for(int i =0; i < n-1; ++i)
		addedge(read(), read());
	dfs(1, 0);
	printf("%d", Ans);
}
```

---

## 作者：Captain_Paul (赞：10)

题意：给定一棵带点权树，求树上最长上升子序列的长度$(n<=6000)$



------------

这个数据范围，可以很暴力

用朴素求解LIS的$nlogn$做法，做$n$次$dfs$

$n^2logn$的复杂度可以跑过

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=6005;
struct node
{
	int to,nxt;
}edge[N<<1];
int n,w[N],num,head[N],ans,f[N];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num]=(node){to,head[from]};
	head[from]=num;
}
void dfs(int k,int fa)
{
	int pos=lower_bound(f+1,f+n+1,w[k])-f;
	ans=max(ans,pos); int tmp=f[pos]; f[pos]=w[k];
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v!=fa) dfs(v,k);
	}
	f[pos]=tmp;
}
int main()
{
	n=read();
	for (reg int i=1;i<=n;w[i++]=read());
	for (reg int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add_edge(x,y); add_edge(y,x);
	}
	memset(f,127/3,sizeof(f));
	for (reg int i=1;i<=n;i++) dfs(i,0);
	printf("%d\n",ans);
	return 0;
}
```



------------


要是数据范围再大一点这个就$GG$了

$Q:$那咋办啊

$A:$对于每个点，维护以它子树内的点为结尾的$LIS$和$LDS$,放到权值线段树中合并信息

$Q:$咋更新答案啊

$A$:用(左儿子的$LIS+$右儿子的$LDS$)和(左儿子的$LDS+$右儿子的$LIS$)更新

别忘了**离散化**一下

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=6005;
struct node
{
	int to,nxt;
}edge[N<<1];
int n,w[N],num,head[N],t[N],tot,rt[N],cnt,ans,ret;
int ls[N*40],rs[N*40],lis[N*40],lds[N*40];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num]=(node){to,head[from]};
	head[from]=num;
}
void insert(int &now,int l,int r,int x,int c,int *a)
{
	if (!now) now=++cnt; a[now]=max(a[now],c);
	if (l==r) return; int mid=(l+r)>>1;
	if (x<=mid) insert(ls[now],l,mid,x,c,a);
	else insert(rs[now],mid+1,r,x,c,a);
}
int merge(int a,int b)
{
	if (!a) return b; if (!b) return a;
	lis[a]=max(lis[a],lis[b]); lds[a]=max(lds[a],lds[b]);
	ans=max(ans,max(lis[ls[a]]+lds[rs[b]],lds[rs[a]]+lis[ls[b]]));
	ls[a]=merge(ls[a],ls[b]); rs[a]=merge(rs[a],rs[b]);
	return a;
}
int query(int L,int R,int l,int r,int now,int *a)
{
	if (l>R||r<L||!now) return 0;
	if (l>=L&&r<=R) return a[now];
	int mid=(l+r)>>1;
	if (mid>=R) return query(L,R,l,mid,ls[now],a);
	if (mid<L) return query(L,R,mid+1,r,rs[now],a);
	return max(query(L,mid,l,mid,ls[now],a),query(mid+1,R,mid+1,r,rs[now],a));
}
void dfs(int k,int fa)
{
	int mlis=0,mlds=0;
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==fa) continue; dfs(v,k);
		int ilis=query(1,w[k]-1,1,tot,rt[v],lis);
		int ilds=query(w[k]+1,tot,1,tot,rt[v],lds);
		rt[k]=merge(rt[k],rt[v]);
		ans=max(ans,max(ilis+mlds,ilds+mlis)+1);
		mlis=max(mlis,ilis); mlds=max(mlds,ilds);
	}
	insert(rt[k],1,tot,w[k],mlis+1,lis);
	insert(rt[k],1,tot,w[k],mlds+1,lds);
}
int main()
{
	n=read(); cnt=n;
	for (reg int i=1;i<=n;i++) w[i]=t[i]=read(),rt[i]=i;
	for (reg int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add_edge(x,y); add_edge(y,x);
	}
	sort(t+1,t+n+1);
	tot=unique(t+1,t+n+1)-t-1;
	for (reg int i=1;i<=n;i++) w[i]=lower_bound(t+1,t+tot+1,w[i])-t;
	dfs(1,0); printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Ranya (赞：7)

前言：

发现题解区没有点分治（哭），树上路径问题不应该直接无脑大力点分治吗（哭哭）

这里提供一种 $O(n\log^2 n)$ 的点分治，供思路相同的同学参考。

### 题意

给出一颗带点权树，求树上所有路径的严格上升子序列的最大值。

$n\le 10^5 \quad a_i\le10^9$

### 题解

正如前言所述，我们思考点分治在当前分治中心 $u$ 如何计算答案。

一个显然的思路是记录 $up_i,dn_i$ 分别表示从叶子往 $u$ 走的所有路径中，以  $i$ 结尾的严格递增/递减子序列的最长长度。

他们的求法可以通过离散化+记录时间戳 $dfn$ 后线段树统计，对于 $up$，我们将点按照权值由小到大一次加入线段树，每次询问一个子树内的最大值，也就是线段树上单点加和区间查询。$dn$ 则是由大到小。

然后将 $up$ 做前缀 $\max$，$dn$ 做后缀 $\max$，设 $w$ 为 $u$ 的点权，然后答案统计就可以分为：

1. 子序列包含 $u$：$up[w-1]+dn[w+1]+1$
2. 子序列不包含 $u$：$\max {up[i]+dn[i+1]}$

但聪明的你肯定会想到，要是两条路径分别来自同一棵子树，那不就寄了吗 QAQ

所以套路的，对 $up,dn$ 记录最大值、最大值来自哪颗子树、次大值、次大值来自哪颗子树。然后答案统计的时候特判一下就好了。

常数在校内 OJ $n=10^5$ 的情况下是常数最小的线段树合并的 4 倍。。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int read() {
	int x=0; char ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48, ch=getchar();
	return x;
} 

const int N=1e5+3;
int n, ans, a[N], b[N], m, c[N];
vector<int> e[N];

int rt, all, mx[N], sz[N], vis[N];
int L[N], R[N], tim, bl[N];
int up1[N], gu1[N], up2[N], gu2[N], dn1[N], gd1[N], dn2[N], gd2[N];
vector<int> id[N];

void get_root(int u, int dad) {
	mx[u]=0, sz[u]=1;
	for (int v:e[u]) if (v!=dad&&!vis[v]) {
		get_root(v, u);
		mx[u]=max(mx[u], sz[v]);
		sz[u]+=sz[v];
	}
	mx[u]=max(mx[u], all-sz[u]);
	if (mx[u]<mx[rt]) rt=u;
}

void dfs(int u, int dad) {
	sz[u]=1;
	b[++m]=a[u];
	L[u]=++tim;
	for (int v:e[u]) if (v!=dad&&!vis[v]) {
		dfs(v, u);
		sz[u]+=sz[v];
	}
	R[u]=tim;
}
void dfs(int u, int dad, int o) {
	c[u]=lower_bound(b+1, b+1+m, a[u])-b;
	bl[u]=o;
	for (int v:e[u]) if (v!=dad&&!vis[v]) {
		dfs(v, u, o);
	}
	id[c[u]].push_back(u);
}

#define Rt 1, 1, all
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
#define Ls ls, l, mid
#define Rs rs, mid+1, r
int t[N<<2], lz[N<<2];
int ask(int i, int l, int r, int x, int y) {
	if ((x<=l&&r<=y)||!t[i]) return t[i];
	if (lz[i]) t[ls]=t[rs]=0, lz[ls]=lz[rs]=1, lz[i]=0;
	if (x>mid) return ask(Rs, x, y);
	if (y<=mid) return ask(Ls, x, y);
	return max(ask(Ls, x, y), ask(Rs, x, y));
}
void add(int i, int l, int r, int x, int v) {
	if (l==r) return t[i]=v, void();
	if (lz[i]) t[ls]=t[rs]=0, lz[ls]=lz[rs]=1, lz[i]=0;
	if (x<=mid) add(Ls, x, v);
	else add(Rs, x, v);
	t[i]=max(t[ls], t[rs]);
}
void New(int &fir, int &ff, int &sec, int &ss, int tmp, int o) {	
	if (tmp>fir) {
		if (ff!=o||ss==o) sec=fir, ss=ff;
		fir=tmp, ff=o;
	}
	else if (tmp>sec&&ff!=o) {
		sec=tmp, ss=o;
	}
}
void calc(int i, int &fir, int &ff, int &sec, int &ss) {
	fir=ff=sec=ss=0;
	queue<int> q;
	for (int u:id[i]) {
		int tmp=ask(Rt, L[u], R[u])+1;
		New(fir, ff, sec, ss, tmp, bl[u]);
		q.push(tmp);
	}
	for (int u:id[i]) add(Rt, L[u], q.front()), q.pop();
}
void split(int u) {
	m=tim=0;
	dfs(u, 0);
	sort(b+1, b+1+m);
	m=unique(b+1, b+1+m)-b-1;
	for (int v:e[u]) 
		if (!vis[v]) dfs(v, u, v);
	c[u]=lower_bound(b+1, b+1+m, a[u])-b;
	lz[1]=1, t[1]=0;
	for (int i=1; i<=m; i++) {
		calc(i, up1[i], gu1[i], up2[i], gu2[i]);
		New(up1[i], gu1[i], up2[i], gu2[i], up1[i-1], gu1[i-1]);
		New(up1[i], gu1[i], up2[i], gu2[i], up2[i-1], gu2[i-1]);
	}
	dn1[m+1]=gd1[m+1]=dn2[m+1]=gd2[m+1]=0;
	lz[1]=1, t[1]=0;
	for (int i=m; i>=1; i--) {
		calc(i, dn1[i], gd1[i], dn2[i], gd1[i]);
		New(dn1[i], gd1[i], dn2[i], gd2[i], dn1[i+1], gd1[i+1]);
		New(dn1[i], gd1[i], dn2[i], gd2[i], dn2[i+1], gd2[i+1]);
	}
	if (gu1[c[u]-1]!=gd1[c[u]+1]) ans=max(ans, up1[c[u]-1]+dn1[c[u]+1]+1);
	else {
		ans=max({ans, up1[c[u]-1]+dn2[c[u]+1]+1, up2[c[u]-1]+dn1[c[u]+1]+1});
	}
	for (int i=1; i<m; i++) {
		if (gu1[i]!=gd1[i+1]) ans=max(ans, up1[i]+dn1[i+1]);
		else {
			ans=max({ans, up1[i]+dn2[i+1], up2[i]+dn1[i+1]});
		}
	}
	for (int i=1; i<=m; i++) id[i].clear();
	vis[u]=1;
	for (int v:e[u]) if (!vis[v]) {
		rt=0, all=sz[v], get_root(v, u);
		split(rt);
	}
}

signed main() {
	n=read();
	for (int i=1; i<=n; i++) a[i]=read();
	for (int i=1; i<n; i++) {
		int u=read(), v=read();
		e[u].push_back(v), e[v].push_back(u);
	}
	mx[0]=n+1;
	rt=0, all=n, get_root(1, 0);
	split(rt);
	cout<<ans<<'\n';
	return 0;
}


```


---

## 作者：清烛 (赞：5)

宣传一下[博客](https://blog.imyangty.com/sol-cf490f/)

说明：本题解更为详细的阐述了线段树合并的做法

## 题意

求树上严格 LIS 的长度。$n\le 6000$。

## 题解

比较平凡的 $O(n^2\log n)$ 做法这里不考虑。

假定一个最朴素的 dp 状态：$f_{u, 0/1, x}$ 表示 $u$ 子树中往上延伸的结尾为 $x$ 的 LIS/LDS 的最大长度。然后我们注意到，一棵子树中有很多这样的 $f$ 值是相等的。所以可以考虑用长链剖分或者线段树合并来优化这个 dp。本题解使用线段树合并。

对于每个节点维护一棵线段树，下标 $i$ 处维护的是结尾为 $i$ 的 LIS/LDS 的最大长度。不难发现其非常通过线段树合并把子树的信息合并到根。

至于统计答案，一条合法的 LIS 路径必然是由上升到下降的两段组成的（虽然可能其中一段不存在）。当我们在处理 $u$ 子树的时候，可以假定 $u$ 就为一段路径的中间必经点，现在就只需要在子树里找到一截尾部小于 $w_u$ 的 LIS，和一截尾部大于 $w_u$ 的 LDS，加起来再加一就行了。

但是，仍然会存在一些没被统计的答案，这个时候就线段树合并的时候边合并边统计就行了。具体地可以看代码的合并部分。

然后处理完一棵子树之后是需要更新以其为端点的最大 LIS/LDS 长度的。详见代码。

(一开始不要忘记离散化)

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 6005;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

il int max(int a, int b) {return a > b ? a : b;}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int n, maxa, a0[maxn], a[maxn];

struct node
{
    int ls, rs, lis, lds;
} t[maxn * 50];

int root[maxn], cnt;
int ans = 0;

#define L(k) t[k].ls
#define R(k) t[k].rs
#define M ((i + j) >> 1)

il void pushup(int k)
{
    t[k].lis = max(t[L(k)].lis, t[R(k)].lis);
    t[k].lds = max(t[L(k)].lds, t[R(k)].lds);
    return;
}

void modify(int &k, int i, int j, int pos, int lis, int lds)
{
    if (!k) k = ++cnt;
    if (i == j)
    {
        t[k].lis = max(t[k].lis, lis);
        t[k].lds = max(t[k].lds, lds);
        return;
    }
    if (pos <= M) modify(L(k), i, M, pos, lis, lds);
    else modify(R(k), M + 1, j, pos, lis, lds);
    pushup(k);
    return;
}

void query(int k, int i, int j, int x, int y, int &lis, int &lds)//查询结尾数字在 [x, y] 的 LIS/LDS
{
    if (!k) return;
    if (x <= i && y >= j)
    {
        lis = max(lis, t[k].lis), lds = max(lds, t[k].lds);
        return;
    }
    if (x <= M) query(L(k), i, M, x, y, lis, lds);
    if (y > M) query(R(k), M + 1, j, x, y, lis, lds);
    return;
}

void merge(int &x, int y)
{
    if (!x || !y)
    {
        x |= y;
        return;
    }
    t[x].lds = max(t[x].lds, t[y].lds);
    t[x].lis = max(t[x].lis, t[y].lis);
    ans = max(ans, max(t[L(x)].lis + t[R(y)].lds, t[R(x)].lds + t[L(y)].lis));//合并的时候统计答案
    merge(L(x), L(y)), merge(R(x), R(y));
    return;
}

void dfs(int u, int fa)
{
    int mlis = 0, mlds = 0;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);

        int vlis = 0, vlds = 0, tmp;
        query(root[v], 1, maxa, 1, a[u] - 1, vlis, tmp);
        query(root[v], 1, maxa, a[u] + 1, maxa, tmp, vlds);

        ans = max(ans, mlis + vlds + 1);
        ans = max(ans, mlds + vlis + 1);//统计经过 u 点的路径的答案
        mlis = max(mlis, vlis), mlds = max(mlds, vlds);

        merge(root[u], root[v]);
    }
    modify(root[u], 1, maxa, a[u], mlis + 1, mlds + 1);//当然要更新一下，插入答案
    return;
}

int main()
{
    n = read();
    FOR(i, 1, n) a0[i] = a[i] = read();
    std::sort(a0 + 1, a0 + n + 1);
    maxa = std::unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(a0 + 1, a0 + maxa + 1, a[i]) - a0;
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    FOR(i, 1, n) modify(root[i], 1, maxa, a[i], 1, 1);
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：louhao088 (赞：4)

## 法一 

枚举每个节点当作起点，DFS下去，采用单调栈，动态维护起点到目前点的单调栈，在链上更新最长上升子序列


时间（O(n^2log(n))）
由于数据太水n<=6000 方法可行


## 法二
那能不能对其进行优化呢？

在这里我们进行启发式合并。

把一条路径u,v分别到他们的lca节点

从根开始dfs，对于每个点维护两个单调栈，一个上升子序列，一个下降子序列
在rt节点处，在每次子节点合并前，我们先用小的上升子序列在大的下降子序列中进行二分，求出经过rt的路径中的最长上升子序列（分两种情况讨论，选rt和不选rt）

然后将两个子树的单调栈启发式合并（用size小的更新size大的）

最后用rt点更新单调栈



### 复杂度分析
1）启发式合并每个点最多合并log(n)次而考虑每个点每合并一次
共合并n*log（n）次

2）每次合并需要log(n)的时间（二分）

时间复杂度：O(nlog^2(n)）而且常数极小







---

## 作者：chenxia25 (赞：2)

考虑这题的 $n\leq 10^5$ 加强版。

考虑枚举以每个点 $x$ 为 lca 的 LIS。那么就设 $dp1_x$ 表示从 $x$ 往下的 LDS，$dp2_x$ 是 LIS，那么贡献有三种：

1. $\max(dp1_x,dp2_x)$；
2. 对两个不同的儿子子树里的节点 $y,z$，满足 $a_y<a_x<a_z$，$dp1_y+1+dp2_z$；
3. 对两个不同的儿子子树里的节点 $y,z$，满足 $a_y<a_z$，$dp1_y+dp2_z$。

第一种傻逼。第二种我们要搞一个子树内值域在某一范围内的 $\max$（相当于是个不可差分的二维数点），DP 的转移也要，第三种则更难。

先考虑这个类二维数点。它是在线、动态的，必须用树套树，由于不可差分还必须要用线段树套线段树。我曾尝试用后序遍历编号，这样可以假装是静态的，可以用主席树处理……吗？它不可差分…………所以树套树是大常数 2log 的，而且还不想写。

对于子树数颜色之类不可数据结构维护的东西，我们很容易想到 dsu on tree。但像这种暧昧的，可以区间 ds 维护但又比较劣的就想不到 dsu on tree。事实上是可以 dsu on tree 的，我们考虑之。就实时维护该子树内，关于值域的一个线段树。那么类二维数点这玩意就搞完了，第三种怎么处理呢？考虑在 dsu on tree 的轻子树合并进来的时候，与实时维护的到目前去掉当前子树的所有子树的 $\min\max$ 发生关系即可。这样子是小常数 2log，是个经典的 dsu on tree 优化 DP。

那么这个 dsu on tree 还可以改成线段树合并。对于第三种怎么处理呢？合并两个线段树的时候，类似 cdq 分治地在以每个节点为分界的地方更新答案即可。

---

## 作者：丛雨 (赞：2)

### [Treeland Tour](https://www.luogu.com.cn/problem/CF490F)

> 题意：树上最长严格上升子序列

不难想到枚举$lca$,计算子树内的$\text{LIS,LDS}$的$n^2\log_2n$的暴力

由于$f_{u,x}$表示长度为$x$的$u$的$\tt LIS,LDS$的结尾最大/小值。

由于不会超过子树高度，考虑长链剖分

时间复杂度$O(n\log_2 n)$


```cpp
#include<bits/stdc++.h>
using namespace std;
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
vector<int>G[100005];
int s,a[100005],h[100005],son[100005],ans,hx[300005],NOW;
void dfs(int n,int fa){
	for(int i=0;i<G[n].size();++i)
		if(G[n][i]!=fa){
			dfs(G[n][i],n);
			if(h[son[n]]<=h[G[n][i]])son[n]=G[n][i];
		}h[n]=h[son[n]]+1;
}
int cmp(int x,int y){return x>y;}
int* New(int n){
	int* w=hx+NOW;NOW+=n;
	return w;
}
void dfs(int n,int fa,int* Up,int* Down){
	if(son[n])dfs(son[n],n,Up,Down);
	int w=lower_bound(Up,Up+h[n]+1,a[n])-Up;
	ans=max(ans,w);Up[w]=a[n];
	w=lower_bound(Down,Down+h[n]+1,a[n],cmp)-Down;
	ans=max(ans,w);Down[w]=a[n];
	for(int i=0;i<G[n].size();++i)
		if(G[n][i]!=son[n]&&G[n][i]!=fa){
			int u=G[n][i],*x=New(h[u]+1),*y=New(h[u]+1);
			memset(x,0x7f,h[u]+1<<2);x[0]=-x[0];
			memset(y,-0x7f,h[u]+1<<2);y[0]=-y[0];
			dfs(u,n,x,y);
			for(int j=1;j<=h[u];++j){
				if(y[j]>-2e9){
					w=lower_bound(Up,Up+h[n]+1,y[j])-Up-1;
					ans=max(ans,w+j);
				}
				if(x[j]<2e9){
					w=lower_bound(Down,Down+h[n]+1,x[j],cmp)-Down-1;
					ans=max(ans,w+j);
				}
			}
			for(int j=0;j<=h[u];++j){
				Up[j]=min(Up[j],x[j]);
				Down[j]=max(Down[j],y[j]);
			}
			w=lower_bound(Up,Up+h[n]+1,a[n])-Up;
			ans=max(ans,w);Up[w]=a[n];
			w=lower_bound(Down,Down+h[n]+1,a[n],cmp)-Down;
			ans=max(ans,w);Down[w]=a[n];
		}
}
int main(){
	s=read;
	for(int i=1;i<=s;++i)a[i]=read;
	for(int i=1;i<s;++i){
		int u=read,v=read;
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1,0);
	int *x=New(h[1]+1),*y=New(h[1]+1);
	memset(x,0x7f,h[1]+1<<2);x[0]=-x[0];
	memset(y,-0x7f,h[1]+1<<2);y[0]=-y[0];
	dfs(1,0,x,y);
	cout<<ans<<endl;
	return 0;
}	
```

考场上打爆了 :smiley:,得了$20pt$


---

## 作者：zhendelan (赞：2)

求树上的最长上升**子序列**。  
注意是子序列，一开始看成连续的就打错了。。。  
树形$dp$。设$f[i][j][x]$为$i$的子树中，以数$j$结尾的，方向向上(1)或向下(0)的最长上升子序列。这里是没有存方向又向上又向下的，即序列上的点深度单调。  
那么答案可以在合并儿子节点的时候求出来。   
$$ans=\max{f[v][k][1]+f[u][j][0]},k<j$$
$$\max f[v][k][0] + f[u][j][1] ,j<k$$  
这时候枚举$u,j,k$时间复杂度是$O(n^3)$
用一个前缀和优化一下就可以$O(n^2)$了    

还有一些细节：$val[i]$很大，所以要离散化才能存。

$f[i][j][k]274M$刚好会爆内存，所以要用$short$，省了一半就够了。   

其实这一题还可以用线段树合并做到$O(nlogn)$。

```
#include<bits/stdc++.h>
using namespace std;
// 1 up  0 down
int n;
const int N = 6002;
short f[N][N][2];
int nex[N*2],head[N],to[N*2],b[N];
short premaxx[N],sufmaxx[N];
int ans;
int cnt,val[N],tot;
void add(int x,int y)
{
	nex[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
}
void dfs(int u,int pre)
{
	f[u][val[u]][0] = f[u][val[u]][1] = 1;
	for(int i=head[u];i;i=nex[i])
	{
		int v = to[i];
		if(v==pre) continue;		
		dfs(v,u);
		premaxx[0] = 0;
		sufmaxx[tot+1] = 0;
		register int j;
		for(j=1;j<=tot;j++)
		  premaxx[j] = max(premaxx[j-1],f[u][j][1]);
		for(j=tot;j>=1;j--)
		  sufmaxx[j] = max(sufmaxx[j+1],f[u][j][0]);
		for(j=1;j<=tot;j++)
			ans = max(ans,sufmaxx[j+1]+f[v][j][1]);
		for(j=1;j<=tot;j++)
			ans = max(ans,premaxx[j-1]+f[v][j][0]);
		for(j=1;j<=tot;j++)
		{
			f[u][j][1] = max(f[u][j][1],f[v][j][1]);
			if(j<val[u])  f[u][val[u]][1] = max(f[u][val[u]][1],(short)(f[v][j][1] + 1));
			f[u][j][0] = max(f[u][j][0],f[v][j][0]);
			if(j>val[u])  f[u][val[u]][0] = max(f[u][val[u]][0],(short)(f[v][j][0] + 1));
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&val[i]),b[i] = val[i];
	sort(b+1,b+n+1);
	tot = unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
	  for(int j=0;j<=tot;j++)
	    f[i][j][0] = f[i][j][1] = -1e4;
	for(int i=1;i<=n;i++)
	  val[i] = lower_bound(b+1,b+tot+1,val[i])-b;
	int x,y;
	for(int i=1;i<n;i++)
	  scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}

```  

---

## 作者：FutaRimeWoawaSete (赞：1)

很久以前做省选模拟赛的 T1 ，那时候数据范围是 $2 \times 10 ^ 5$ 于是果断敲了个平衡树套启发式合并……现在学了线段树合并后感觉还是挺简单的。          

我们考虑在枚举一个点时维护两种树上最长上升子序列：          

- 经过该点的最长上升子序列；

- 不经过该点的最长上升子序列；                    

对于第一种很简单，我们考虑维护以一个点结尾的最长上升子序列以及以一个点开头的最长下降子序列，那么我们合并时就直接选子树中两个最长的合法最长上升子序列和最长下降子序列即可，这些都可以线段树合并维护。            

对于第二种情况，我们直接在线段树合并的时候从合并的两棵线段树里每层的左右子树里面选左边的最长上升子序列，右边的最长下降子序列合并即可，记得交换一下两棵树的顺序再更新一次答案。                 

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,lsh[Len],head[Len],cnt,val[Len],ans,Cnt,maxnans[Len][2],Ans;
struct T_T
{
	int lc[Len * 80] , rc[Len * 80] , maxn[Len * 80][2],ans[Len * 80],rt[Len],tot;
	void push_up(int x)
	{	
		maxn[x][0] = max(maxn[lc[x]][0] , maxn[rc[x]][0]);
		maxn[x][1] = max(maxn[lc[x]][1] , maxn[rc[x]][1]);
	}
	int clone(){tot ++; lc[tot] = rc[tot] = maxn[tot][0] = maxn[tot][1] = 0 ; return tot;}
	int merge(int a,int b,int l,int r)
	{
		Ans = max(Ans , max(maxn[lc[a]][1] + maxn[rc[b]][0] , maxn[lc[b]][1] + maxn[rc[a]][0]));
		if(!a || !b) return a + b;
		if(l == r)
		{
			maxn[a][0] = max(maxn[a][0] , maxn[b][0]) ; maxn[a][1] = max(maxn[a][1] , maxn[b][1]);
			return a;
		}
		int mid = (l + r) >> 1;
		lc[a] = merge(lc[a] , lc[b] , l , mid) , rc[a] = merge(rc[a] , rc[b] , mid + 1 , r);
		push_up(a);
		return a;	
	} 
	void update(int p,int l,int r,int idx,int opt,int w)
	{	
		if(l == r) 
		{
			maxn[p][opt] = max(maxn[p][opt] , w);
			return;
		}
		int mid = (l + r) >> 1;
		if(idx <= mid) 
		{
			if(!lc[p]) lc[p] = clone();
			update(lc[p] , l , mid , idx , opt , w);
		}
		else 
		{
			if(!rc[p]) rc[p] = clone();
			update(rc[p] , mid + 1 , r , idx , opt , w);
		}
		push_up(p);
	}
	int query(int p,int l,int r,int nl,int nr,int opt)
	{
		if(nl <= l && nr >= r) return maxn[p][opt];
		int mid = (l + r) >> 1 , res = 0;
		if(nl <= mid) 
		{
			if(!lc[p]) lc[p] = clone();
			res = query(lc[p] , l , mid , nl , nr , opt);
		}
		if(nr > mid) 
		{
			if(!rc[p]) rc[p] = clone();
			res = max(res , query(rc[p] , mid + 1 , r , nl , nr , opt));
		}
		return res;
	}
}S1;
struct node
{
	int next,to;
}edge[Len << 1];
struct Node
{
	int x,y;
}fos[Len];
bool cmpx(Node x,Node y){return x.x < y.x;}
bool cmpy(Node x,Node y){return x.y < y.y;}
void add(int from,int to){edge[++ cnt].to = to ; edge[cnt].next = head[from] ; head[from] = cnt;}
void dfs(int x,int f)
{
	S1.rt[x] = S1.clone();
	int tots = 0;int maxn[2] = {0 , 0};
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x);
	}
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		tots ++;
		Ans = 0;
		if(val[x] == Cnt) fos[tots].x = 1;
		else fos[tots].x = S1.query(S1.rt[to] , 1 , Cnt , val[x] + 1 , Cnt , 0) + 1;
		if(val[x] == 1) fos[tots].y = 1;
		else fos[tots].y = S1.query(S1.rt[to] , 1 , Cnt , 1 , val[x] - 1 , 1) + 1;
		maxn[0] = max(maxn[0] , fos[tots].x);
		maxn[1] = max(maxn[1] , fos[tots].y);
		S1.rt[x] = S1.merge(S1.rt[x] , S1.rt[to] , 1 , Cnt);
		ans = max(ans , Ans);
	}
	if(!tots){ans = max(ans , 1);maxn[0] = maxn[1] = 1;}
	else if(tots == 1)
	{
		ans = max(ans , fos[tots].x);
		ans = max(ans , fos[tots].y);
	}
	else
	{
		sort(fos + 1 , fos + 1 + tots , cmpx);
		sort(fos + 1 , fos + tots , cmpy);
		ans = max(ans , fos[tots].x + fos[tots - 1].y - 1);
		sort(fos + 1 , fos + 1 + tots , cmpy);
		sort(fos + 1 , fos + tots , cmpx);
		ans = max(ans , fos[tots].y + fos[tots - 1].x - 1);
	}
	S1.update(S1.rt[x] , 1 , Cnt , val[x] , 0 , maxn[0]);
	S1.update(S1.rt[x] , 1 , Cnt , val[x] , 1 , maxn[1]);
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&val[i]);
		lsh[++ Cnt] = val[i];
	}
	sort(lsh + 1 , lsh + 1 + Cnt);
	Cnt = unique(lsh + 1 , lsh + 1 + Cnt) - lsh - 1;
	for(int i = 1 ; i <= n ; i ++) val[i] = lower_bound(lsh + 1 , lsh + 1 + Cnt , val[i]) - lsh;
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	dfs(1 , 0);
	printf("%d\n",ans);
 	return 0;
}
```

---

## 作者：RainFestival (赞：1)

这里有一种其他做法

记 $f_{i,j}=$ 其子树延伸的最长上升子序列 (Longest increasing subsequence) 到 $i$ 结束，最大的一个数字是 $j$

记 $g_{i,j}=$ 其子树延伸的最长下降子序列 (Longest descending subsequence) 到 $i$ 结束，最小的一个数字是 $j$

最后的答案一定是 $1$ 条子序列或者 $2$ 条交于 $1$ 点的子序列拼在一起

我们做类似树形 dp 可以求出并且每次统计答案

这样是 $O(nk)$ 的，其中 $k=\max\limits_{i=1}^n r_i$

我们考虑将 $r$ 离散化，使得 $k\le n$

这样就可以通过了

不过还有一个内存问题

发现我们需要保存的 dp 值数据数量是 $n\times\max\limits_{i=1}^n d_i,d_i$ 是 $i$ 点深度，不需要的 dp 值可以直接删除

所以我们随机钦定一个点为根，这样最坏(一条链)期望树深度是 $\frac34n$ ,可以砍掉 $\frac14$ 的内存

然后多提交几发就过了

代码：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<bitset>
#include<cstdlib>
#include<ctime> 
std::queue<int> q; 
std::vector<int> a[6005];
std::vector<int> g;
std::bitset<1000005> f;
int n,p[6005];
short int dp1[6005][6005],dp2[6005][6005],ans=0,now=0;
void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
int make(){if (q.empty()) q.push(++now);int x=q.front();q.pop();return x;}
void clear(int x){q.push(x);}
void dfs(int v,int fa)
{
	for (int i=0;i<a[v].size();i++)
    {
    	int u=a[v][i];
    	if (u==fa) continue;
    	g[u]=make();
    	dfs(u,v);
	}
	for (int j=0;j<=n;j++) dp1[g[v]][j]=dp2[g[v]][j]=0;
	dp1[g[v]][p[v]]=dp2[g[v]][p[v]]=1;
	short s1[6005],s2[6005];
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
		if (u==fa) continue;
		for (int x=0;x<=n;x++) s1[i]=s2[i]=0;
		s1[0]=0;for (int x=1;x<=n;x++) s1[x]=std::max(s1[x-1],dp1[g[v]][x]);
		s2[n]=0;for (int x=n-1;x>=0;x--) s2[x]=std::max(s2[x+1],dp2[g[v]][x]);
		//calcualte point i's up value&down value
		for (int x=0;x<=n;x++) ans=(short int)std::max((int)ans,s1[x]+(x<n?dp2[g[u]][x+1]:0));
		for (int x=n;x>=0;x--) ans=(short int)std::max((int)ans,s2[x]+(x>0?dp1[g[u]][x-1]:0));
		//calcualte point i's contribution
		for (int x=0;x<=n;x++) dp1[g[v]][x]=std::max(dp1[g[v]][x],dp1[g[u]][x]);
		for (int x=0;x<=n;x++) dp2[g[v]][x]=std::max(dp2[g[v]][x],dp2[g[u]][x]);
		//write point i's value(without i)
		for (int x=0;x<p[v];x++) dp1[g[v]][p[v]]=(short int)std::max((int)dp1[g[v]][p[v]],dp1[g[u]][x]+1);
		for (int x=n;x>p[v];x--) dp2[g[v]][p[v]]=(short int)std::max((int)dp2[g[v]][p[v]],dp2[g[u]][x]+1);
		clear(g[u]);
		//write point i's value(within i)
    }
	for (int x=0;x<=n;x++) ans=std::max(ans,dp1[g[v]][x]);
	for (int x=0;x<=n;x++) ans=std::max(ans,dp2[g[v]][x]);
}
int main()
{
	srand(time(0));
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&p[i]);
	for (int i=1;i<=n;i++) f[p[i]]=1;
	for (int i=0;i<=1000001;i++) g.push_back(0);
	for (int i=1;i<=1000000;i++) g[i]=g[i-1]+f[i];
	for (int i=1;i<=n;i++) p[i]=g[p[i]];
	g.clear();
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int rt=rand()%n+1;
	g[rt]=make();
	dfs(rt,-1);
	clear(g[rt]);
	printf("%hd\n",ans);
	return 0;
}
//lmytsdy
```

---

## 作者：ezoixx130 (赞：1)

这题的n很小，只有6000，可以$O(n^2logn)$跑过去。

然而其实有更优秀的算法。

首先用动态开点权值线段树维护每个结点的LIS和LDS。

然后在dfs过程中Merge一下就可以了。

Merge的过程用线段树合并实现。

于是我们就31ms跑过了这道题。

代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 200010

int head[MAXN],to[MAXN<<1],nxt[MAXN<<1];
int n,id[MAXN],ls[4000000],rs[4000000],cnt,val[MAXN],ans,tot;
 
 class IO
{
    char buffer[10000001];char *h;int len;
    inline char gchar(){return *h++;}
    inline bool validdigit(char c){return c>='0' && c<='9';}
public:
    inline void init(){len=fread(buffer,1,10000000,stdin);h=buffer;}
    inline int nextint(){register int i=0;register char c;do c=gchar();while(!validdigit(c));do{i=i*10+c-48;c=gchar();}while(validdigit(c));return i;}
}io;
 
struct data
{
    int val,id;
    bool operator<(const data &d)const
    {
        return val<d.val;
    }
}tmp[MAXN];
 
struct SGT
{
    int maxo[4000000];
    SGT(){cnt=0;}
    int query(int o,int l,int r,int ql,int qr)
    {
        if(!o)return 0;
        if(ql<=l && r<=qr)return maxo[o];
        int mid=(l+r)>>1,ans=0;
        if(ql<=mid)ans=max(ans,query(ls[o],l,mid,ql,qr));
        if(qr>mid)ans=max(ans,query(rs[o],mid+1,r,ql,qr));
        return ans;
    }
    void update(int &o,int l,int r,int p,int x)
    {
        if(!o)o=++cnt;maxo[o]=max(maxo[o],x);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid)update(ls[o],l,mid,p,x);
        else update(rs[o],mid+1,r,p,x);
    }
}LIS,LDS;
 
void merge(int &a,int b)
{
    if(a==0||b==0)
    {
        a+=b;
        return;
    }
    LIS.maxo[a]=max(LIS.maxo[a],LIS.maxo[b]);LDS.maxo[a]=max(LDS.maxo[a],LDS.maxo[b]);
    ans=max(ans,max(LIS.maxo[ls[a]]+LDS.maxo[rs[b]],LIS.maxo[ls[b]]+LDS.maxo[rs[a]]));
    merge(ls[a],ls[b]);merge(rs[a],rs[b]);
}
 
void dfs(int u,int fa)
{
    int maxlis=0,maxlds=0;
    for(int i=head[u];i;i=nxt[i])
    {
    	int v=to[i];
        if(v==fa)continue;
        dfs(v,u);
        int vlis=LIS.query(id[v],1,MAXN,1,val[u]-1),vlds=LDS.query(id[v],1,MAXN,val[u]+1,MAXN);
        ans=max(ans,max(vlis+maxlds+1,vlds+maxlis+1));
        merge(id[u],id[v]);
        maxlis=max(maxlis,vlis);
        maxlds=max(maxlds,vlds);
    }
    LIS.update(id[u],1,MAXN,val[u],maxlis+1);
    LDS.update(id[u],1,MAXN,val[u],maxlds+1);
}
 
int main()
{
    io.init();
    n=io.nextint();
    for(int i=1;i<=n;++i)
    {
    	tmp[i].val=io.nextint();
        tmp[i].id=i;
    }
    sort(tmp+1,tmp+n+1);
    int now=0;
    tmp[0].val=-1;
    for(int i=1;i<=n;++i)
    {
        if(tmp[i].val!=tmp[i-1].val)++now;
        val[tmp[i].id]=now;
    }
    for(int i=1;i<n;++i)
    {
        int u=io.nextint(),v=io.nextint();
        nxt[++tot]=head[u];
        to[tot]=v;
        head[u]=tot;
        nxt[++tot]=head[v];
        to[tot]=u;
        head[v]=tot;
    }
    dfs(1,0);
    printf("%d\n",ans);
}
```

---

