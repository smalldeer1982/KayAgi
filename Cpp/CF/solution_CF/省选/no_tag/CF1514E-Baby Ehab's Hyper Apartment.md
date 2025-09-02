# Baby Ehab's Hyper Apartment

## 题目描述

This is an interactive problem.

Baby Ehab loves crawling around his apartment. It has $ n $ rooms numbered from $ 0 $ to $ n-1 $ . For every pair of rooms, $ a $ and $ b $ , there's either a direct passage from room $ a $ to room $ b $ , or from room $ b $ to room $ a $ , but never both.

Baby Ehab wants to go play with Baby Badawy. He wants to know if he could get to him. However, he doesn't know anything about his apartment except the number of rooms. He can ask the baby sitter two types of questions:

- is the passage between room $ a $ and room $ b $ directed from $ a $ to $ b $ or the other way around?
- does room $ x $ have a passage towards any of the rooms $ s_1 $ , $ s_2 $ , ..., $ s_k $ ?

He can ask at most $ 9n $ queries of the first type and at most $ 2n $ queries of the second type.

After asking some questions, he wants to know for every pair of rooms $ a $ and $ b $ whether there's a path from $ a $ to $ b $ or not. A path from $ a $ to $ b $ is a sequence of passages that starts from room $ a $ and ends at room $ b $ .

## 说明/提示

In the given example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1514E/d99856b2abe4009b979ccdf65944f218e75effb1.png)

The first query asks whether there's a passage from room $ 3 $ to any of the other rooms.

The second query asks about the direction of the passage between rooms $ 0 $ and $ 1 $ .

After a couple other queries, we concluded that you can go from any room to any other room except if you start at room $ 3 $ , and you can't get out of this room, so we printed the matrix:

```  
1111  
1111  
1111  
0001  
```

The interactor answered with $ 1 $ , telling us the answer is correct.

## 样例 #1

### 输入

```
1
4

0

0

1

1

1```

### 输出

```
2 3 3 0 1 2

1 0 1

1 0 2

2 2 1 1

3
1111
1111
1111
0001```

# 题解

## 作者：zhoukangyang (赞：20)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/14679797.html)

能在场上想出来自己不怎么擅长的交互题还是比较开心的（

但是因为不了解 ``Extra Registration``（在 $30$ 分钟之后就不能报名了），没能交上去...

## 题面

给定一张 $n$ 个点竞赛图，你可以进行一些询问，询问有两种： 
- $1$ $a$ $b$：查询是否有从 $a$ 到 $b$ 的有向边。这种询问次数 $\le 9n$。
- $2$ $x$ $k$ $s_1$ $s_2$ $...$ $s_k$ : 查询 $x$ 到 $s_1$，$s_2$，...，$s_k$ 是否存在一条有向边。这种询问次数 $\le 2n$。

最后要求输出对于所有 $(i, j)$，是否有 $i$ 到 $j$ 的 **路径**。多测。

## 题解

因为把竞赛图缩点之后形成的强联通分量是一条链，如果知道了这些强联通分量就可以得出答案。

接下来分成两个步骤：

1. 找到一条包括 $1, 2, ..., n$ 的路径。

2. 在这条路径上进行缩点。

### 步骤1

考虑增量，设这条链原先是 $v_1, v_2, ..., v_k$，现在要加入点 $k$。

因此要找出一个位置 $p$ （$1 \le p \le k + 1$） 满足有一条从 $v_{p-1}$ 到 $k$ 的边且有一条从 $k$ 到 $v_p$ 的边，并在 $p$ 之前插入 $k$。

发现如果有从 $v_{l-1}$ 到 $k$ 的边且有从 $k$ 到 $v_r$ 的边，那么可以在 $[l, r]$ 找到答案。

考虑二分答案，如果有 $k$ 到 $v_{mid}$ 的边，那么在 $[l,mid]$ 中可以找到答案，否则在 $[mid+1, r]$ 中可以找到答案。

需要 $n \log n$ 个询问 $1$。

### 步骤2

设目前缩出来的链是 $S_1 \to S_2 \to ... \to S_k$。

从后往前缩点，对于一个 $S_t$ 中的点 $z$，如果存在一条从 $z$ 到 $S_1, S_2, ..., S_{t - 1}$ 中的点的边，那么 $S_t$ 和 $S_{t-1}$ 必然在一个集合中。

不停地这样缩点即可得到最终答案。需要 $2n$ 个询问 $2$。

## 代码

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define pii pair<int, int>
#define db double
#define x first
#define y second
#define ull unsigned long long
#define sz(a) ((int) (a).size())
#define vi vector<int>
using namespace std;
const int N = 233;
int n, tot, v[N];
set < int > S[N];
void merge(int x, int y) {
	for(int k : S[y]) S[x].insert(k);
	S[y].clear();
}
int getin() {
	int k;
	return cin >> k, k;
}
bool check(int x, int y) {
	return cout << 1 << " " << x << " " << y << endl, getin();
}
bool all[N][N], vis[N];
int rmain() {
	memset(all, 0, sizeof(all)), memset(vis, 0, sizeof(vis)), memset(v, 0, sizeof(v));
	L(i, 1, tot) S[i].clear();
	tot = 0;
	cin >> n;
	L(i, 0, n - 1) {
		int l = 1, r = tot + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(mid == tot + 1 || check(i, v[mid])) r = mid;
			else l = mid + 1;
		}
		R(i, tot, l) v[i + 1] = v[i];
		++tot, v[l] = i;
	}
	L(i, 1, tot) S[i].insert(v[i]);
	int now = tot;
	while(now > 1) {
		for(int v : S[now]) if(!vis[v]) {
			cout << 2 << " " << v << " ";
			int cnt = 0;
			L(i, 1, now - 1) cnt += sz(S[i]);
			cout << cnt << " ";
			L(i, 1, now - 1) for(int u : S[i]) cout << u << " ";
			cout << endl;
			if(getin()) {
				merge(now - 1, now);
				break;	
			}
			vis[v] = true;
		}
		--now;
	}
	L(i, 1, tot) L(j, i, tot) for(int u : S[i]) for(int v : S[j]) all[u][v] = true;
	cout << 3 << endl;
	L(i, 0, n - 1) {
		L(j, 0, n - 1) cout << all[i][j];
		cout << endl;	
	} 
	return getin(), 0;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while(T--) rmain();
	return 0;
} 
```

**祝大家学习愉快！**

---

## 作者：syksykCCC (赞：15)

官方题解的操作好炫酷啊……

因为我们能得知的关于边的信息非常有限，所以考虑求出一条「通用」的路径，使得仅通过这些极少的路径就可以完成整张图的连通性的判断。

下面记题目中给出的两种询问分别为 $\text{OneEdge}(u, v)$ 和 $\text{ManyEdges}(u, S)$。

自然的，我们将目光投向这张竞赛图的**哈密顿路径**上。

考虑归并。比如我们现在在找 $[l, r]$ 这些点的哈密顿路径，那么可以分为两个部分 $[l, mid]$ 和 $[mid +1,r]$，递归求解这两部分的哈密顿路径。

比如 $[l, mid]$ 的哈密顿路径的起点是 $u$，$[mid+1, r]$ 的哈密顿路径的起点是 $v$，那么我们调用 $\text{OneEdge}(u, v)$，如果边是 $u \to v$ 的，那么我们就把 $u$ 放在 $[l, r]$ 的哈密顿路径的第一个，否则把 $v$ 放在第一个。

上面这么做为什么可行呢？

比如边是 $u \to v$ 的，那么当把 $u$ 放在第一位后，无论下一位是 $v$ 还是 $[l, mid]$ 中 $u$ 的后继，$u$ 都有一条直接连向后面的边，所以哈密顿路径的性质不会被破坏。

第一位确定以后，我们再继续按照上面的方法去确定第二位、第三位……即可。这个过程本质上就是对两个有序数组的归并。

当然，其实完全可以不用手写这个归并过程，我们可以调用 STL 的 `stable_sort`，而 $\text{OneEdge}$ 恰好就是 Compare 函数！

也就是说，我们先构造一个数组 $path_i = i$，接下来调用 `stable_sort(path + 1, path + n + 1, OneEdge)`，得到的 $path_1 \to path_2 \to \cdots \to path_n$ 就是图中的一条哈密顿路径了。

上述调用 $\text{OneEdge}$ 的次数约 $n \log n$。

求出哈密顿路径后，显然所有 $path_i \to path_j (i < j)$ 的边就没有意义了，故只需要考虑**反向边**。

于是我们逆序遍历 $path$ 数组，同时维护一下**当前通过反向边最远能追溯到哪里**，其实也就是维护一个指针 $p$，只要 $\text{ManyEdges}(path_{now}, \{path_1, path_2, \cdots, path_p\}) = 1$，就说明至少可以追溯到前 $p$ 位。

因为 $now$ 和 $p$ 都是单调下降的，所以上述过程是线性的，调用 $\text{ManyEdges}$ 的次数约为 $2n$。

于是这个问题就很好地得到了解决，代码非常短。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, ret;
bool ans[105][105];
vector<int> path;
inline bool ManyEdges(const int &x, int len) // len 表示询问的 S 是 path[0] ~ path[len]
{
	if(len < 0) return false;
	cout << "2 " << x << ' ' << len + 1 << ' ';
	for(unsigned i = 0; i <= len; i++) cout << path[i] << ' ';
	cout << endl;
	cin >> ret;
	return ret;
}
inline bool OneEdge(const int &a, const int &b)
{
	cout << "1 " << a << ' ' << b << endl;
	cin >> ret;
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--)
	{
		cin >> n;
		memset(ans, true, sizeof(ans));
		path.clear();
		for(int i = 0; i < n; i++) path.push_back(i);
		stable_sort(path.begin(), path.end(), OneEdge);
		int far = n - 2;
		for(int i = n - 1; ~i; i--)
		{
			if(far == i)
			{
				for(int j = 0; j <= i; j++) for(int k = i + 1; k < n; k++) ans[path[k]][path[j]] = false;
				far--;
			}
			while(ManyEdges(path[i], far)) far--;
		}
		cout << "3\n";
		for(int i = 0; i < n; i++, cout << endl) for(int j = 0; j < n; j++) cout << ans[i][j];
		cin >> n;
	}
}
```

---

## 作者：Leap_Frog (赞：7)

### P.S.
前来补题。  
昨晚降智，甚至没想到随机快排复杂度期望 $\log$。  
其实昨天已经基本胡出正确做法了，但是自以为复杂度假了 ![](//xn--9zr.tk/ll)  

### Description.
交互题，有一张 $n\ (n\le100)$ 个点的竞赛图。  
询问1：可以询问 $x$ 到 $y$ 单向边方向，询问次数限制 $9n$。  
询问2：可以询问 $x$ 到 $\{s_k\}$ 中有无 $x\rightarrow s_k$ 方向的边。  
现在需要查询竞赛图任意两点联通状态。  

### Solution.
每次查询只能得到的信息量是 1bit。  
但是需要我们输出的信息量看上去是 n^2bit。  
如果不利用输出仅需要查询是否联通这个特性，显然没法做。  

首先，根据竞赛图特性，它缩点之后肯定形成一条链。  
那么我们可以按照链的先后顺序，给每个结点标号为 $a_i$。  
相当于所有 $a_i\ge a_j$ 的点对 $i,j$，$i$ 可以走到 $j$。  
大致想法就是先按照 $a_i$ 排序，然后再判相等。  
考虑如何排序，有如下结论成立：  
- 如果存在单向边 $i\rightarrow j$，那么有 $a_i\ge a_j$。  

证明显然，因为要么它们在同一个联通块内，否则只能前面的联通块指向后面的。  
那么我们可以通过一次询问来比较 $a_i$ 和 $a_j$。  
因为询问数量限制是 $9n$，不禁让我们想到了快速排序。  
所以直接快排即可，注意要随机化，复杂度期望 $O(n\log n)$。  

然后，按照 $a_i$ 排序后我们还需要判断 $a_i$ 是否相等。  
因为现在第一种询问已经用完了，考虑第二种。  
现在我们查询第 $x$ 个点和 $[1,s]\ (s<x)$ 内的所有点是否有连边。  
那么就相当于查询了 $x$ 是否和 $[1,s]$ 中每个数是否有相同。  
这个信息显然具有单调性，那么我会二分！复杂度 $O(n\log n)$ 飞了。  
考虑双指针，从大到小扫，每次双指针找到当前最小的那个和当前数不相同的位置。  
每次维护这个指针即可。  
注意最后还需要在每个点所有可达点的可达点取最小值。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
//int debug[105][105];
inline char qry1(int x,int y)
{
	printf("1 %d %d\n",x,y),fflush(stdout);//return debug[x][y];
	char w;return read(w),w;
}
inline char qry2(int x,vector<int>v)
{
	printf("2 %d %d ",x,(int)v.size());for(auto y:v) printf("%d ",y);
	//putchar('\n'),fflush(stdout);int r=0;for(auto y:v) r|=debug[x][y];return r;
	char w;return putchar('\n'),fflush(stdout),read(w),w;
}
mt19937 getrand(114514);int Ca,n,ls[105];char rs[105][105];
inline vector<int>srt(const vector<int>&v)
{
	int bas;if((int)v.size()<2) return v;else bas=getrand()%v.size();
	vector<int>l,r,rs;for(int i=0;i<(int)v.size();i++) if(i^bas) (qry1(v[i],v[bas])?l:r).push_back(v[i]);
	l=srt(l),r=srt(r);for(auto x:l) rs.push_back(x);rs.push_back(v[bas]);for(auto x:r) rs.push_back(x);
	return rs;
}
inline void solve()
{
	read(n);vector<int>v(n);for(int i=0;i<n;i++) v[i]=i,ls[i]=0;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) rs[i][j]=0;
	//for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%1d",&debug[i][j]);
	v=srt(v);for(int i=0;i<n;i++) for(int j=i;j<n;j++) rs[v[i]][v[j]]=1;
	int nw=n-2;for(int i=n-1;~i;i--) for(nw-=nw==i;;)
	{
		if(nw<0) {ls[i]=0;break;}
		vector<int>q;for(int j=0;j<=nw;j++) q.push_back(v[j]);
		if(qry2(v[i],q)) nw--;else {ls[i]=nw+1;break;}
	}
	for(int i=0;i<n;i++) for(int j=ls[i];j<=i;j++) ls[i]=min(ls[i],ls[j]);
	for(int i=0;i<n;i++) for(int j=ls[i];j<=i;j++) rs[v[i]][v[j]]=1;
	puts("3");for(int i=0;i<n;i++,putchar('\n')) for(int j=0;j<n;j++) printf("%d",rs[i][j]);
	fflush(stdout);int FUCK;read(FUCK);
}
int main() {for(read(Ca);Ca--;) solve();return 0;}
```

---

## 作者：7KByte (赞：1)

竞赛图。

竞赛图一定存在一条哈密顿路径。

我们先找到哈密顿路径，然后缩点的时候一定是连续的一段缩成一个点。

考虑寻找哈密顿路径，我们递归处理。先找前 $i-1$ 个点的哈密顿路径，再将第 $i$ 个点插入。这是个经典问题直接二分即可。

至于缩点，我们倒叙枚举当前点 $i$ ，找到 $i\sim n$ 的点中能到达的哈密顿路径中最前面的点的标号。

不难发现能到达的最前面的点具有单调性，直接双指针扫一遍即可。

注意每组测试数据结束后一定要再读入一个反馈（因为这个调了一个小时

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 105
using namespace std;
int n,u[N],fa[N],mat[N];
bool get(int x,int y){
	cout<<"1 "<<x-1<<" "<<y-1<<endl;
	int op;cin>>op;return op;
}
bool ask(int x,int l,int r){
	cout<<"2 "<<u[x]-1<<" "<<r-l+1<<" ";
	rep(i,l,r)cout<<u[i]-1<<" ";
	cout<<endl;int op;cin>>op;return op;
}
void solve(){
	memset(fa,0,sizeof(fa));
	memset(u,0,sizeof(u));
	memset(mat,0,sizeof(mat));
	cin>>n;
	u[1]=1;fa[1]=1;
	int tot=0;
	rep(i,2,n){
		int l=0,r=i;
		while(l+1<r){
			int mid=(l+r)>>1;
			int cur=get(u[mid],i);
			tot++;
			if(cur)l=mid;else r=mid;
		}
		pre(j,i-1,r)u[j+1]=u[j];
		u[l+1]=i;
	}
	int cur=n;
	pre(i,n,2){
		cur=min(cur,i);
		while(cur>1&&ask(i,1,cur-1))cur--;
		fa[i]=cur;
	}
	rep(i,1,n)rep(j,fa[i],i)fa[i]=min(fa[i],fa[j]);
	rep(i,1,n)mat[u[i]]=i;
	cout<<"3 "<<endl;
	rep(i,1,n){
		rep(j,1,n)if(fa[mat[i]]==fa[mat[j]])putchar('1');
		else if(mat[i]<mat[j])putchar('1');else putchar('0');
		cout<<endl;
	}int op;cin>>op;
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：Lsrh666 (赞：0)

# [CF1514E](https://www.luogu.com.cn/problem/CF1514E)
[${\color{Red} \mathbb{更好的阅读体验} }$](https://flowus.cn/xinyu47/share/81adae42-b4aa-4eaa-b8a1-cc2e271760b1?code=TNS9V9&embed=true)

## Warning

每组测试数据结束后还有一个数需要读入。

## description

给你一个竞赛图。

有两种询问：  
询问 $1$：$x→y$ 的单向边的方向。  
询问 $2$：$x→{\{s_k \}}$ 中有无 $x→{s_i}$ 方向的边  $1 \leq i  \leq k $。  

现在查询竞赛图内任意两点的联通状态，有多测。

## solution

### preparation

竞赛图是通过在无向完全图中为每个边缘分配方向而获得的有向图。  
也就是说，它是一个完整图形的方向，等价于一个有向图，其中每对不同的顶点通过单个有向边连接。  
即每对顶点之间都有一条边相连的有向图称为竞赛图。  
设 $D$ 为 $n$ 阶有向简单图，若 $D$ 的基图为 $n$ 阶无向完全图，则 $D$ 为 $n$ 阶竞赛图。  
简单来说，竞赛图就是将完全无向图的无向边给定了方向。  

竞赛图有一些性质，如下：  

1. 缩点之后是链。  

2. 竞赛图的强连通块存在一条哈密顿回路。  

3. 竞赛图存在一条哈密顿路径。  

### process

1. 归并排序找哈密顿路径。 

  正如其他题解说的，就是经典问题：  
找 $[l,r]$ 这些点的哈密顿路径，就二分区间变成 $[l,mid]$ 和 $[mid+1,r]$。  
考虑左区间的哈密顿路径的起点 $x$ 和右区间的起点 $y$，   
若 $x→y$ 则 $[l,r]$ 的哈密顿路径的第一位放 $x$ ，否则放 $y$。

先不关注证明，看实现：  

  首先递归是显然的，然后发现这就是对两个有序数组的归并排序，使用 `stable_sort` 就能实现。  

  这里注意一下，不是 `sort` 而是 `stable_sort` 。  
前者在 OI WiKi 中的定义如下：  

  > C++ 标准并未严格要求此函数的实现算法，具体实现取决于编译器。  
[libstdc++](https://github.com/mirrors/gcc/blob/master/libstdc++-v3/include/bits/stl_algo.h) 和 [libc++](http://llvm.org/svn/llvm-project/libcxx/trunk/include/algorithm) 中的实现都使用了[内省排序](https://oi-wiki.org/basic/quick-sort/#%E5%86%85%E7%9C%81%E6%8E%92%E5%BA%8F)。

  因此我们最好不要用 `sort`。  

  而后者在主流的编译器中是严格的归并排序。

  关于操作正确性的证明如下：  
$x$ 放在第一位之后，下一位只可能是 $x$ 的后继或 $y$，这时候 $x$ 无论连谁，仍能构成哈密顿路径。

2. 倒序查询能否回溯，能回溯就连通。

  求出归并后的数组之后，考虑反向边，倒序遍历数组，维护当前的回溯最远，实现比较简单，用指针就行了。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
bool ManyEdges(int x,vector<int> s)
{
    printf("2 %d %d",x,s.size());
    for (int i:s)
    printf(" %d",i);
    printf("\n");
    fflush(stdout);
    int ret;
    scanf("%d",&ret);
    if (ret==-1)
    exit(0);
    return ret;
}
bool OneEdge(int a,int b)
{
    printf("1 %d %d\n",a,b);
    fflush(stdout);
    int ret;
    scanf("%d",&ret);
    if (ret==-1)
    exit(0);
    return ret;
}
vector<int> getprefix(vector<int> v,int p)
{
    vector<int> ret;
    for (int i=0;i<=p;i++)
    ret.push_back(v[i]);
    return ret;
}
vector<vector<int> > getMap(int n)
{
    vector<vector<int> > ret(n,vector<int>(n,1));
    vector<int> path;
    for (int i=0;i<n;i++)
    path.push_back(i);
    stable_sort(path.begin(),path.end(),OneEdge);
    int p=n-2;
    for (int i=n-1;i>=0;i--)
    {
        if (p==i)
        {
            for (int j=0;j<=i;j++)
            {
                for (int k=i+1;k<n;k++)
                ret[path[k]][path[j]]=0;
            }
            p--;
        }
        while (ManyEdges(path[i],getprefix(path,p)))
        p--;
    }
    return ret;
}
int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        int n;
        scanf("%d",&n);
        auto res=getMap(n);
        puts("3");
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            printf("%d",res[i][j]);
            printf("\n");
        }
        fflush(stdout);
        int ok;
        scanf("%d",&ok);
        if (ok==-1)
        exit(0);
    }
}
```

---

## 作者：ZillionX (赞：0)

# Description

交互题。给定一张 $n$ 个点的竞赛图，有两种询问：

- 询问是否存在边 $x \rightarrow y$，次数限制 $9n$。

- 询问是否存在 $x$ 到点集 $S$ 的单向边，次数限制 $2n$。

试求出任意两点联通情况。

$n \le 100$，时限 1s。

# Solution

有意思的交互题。

相信各位熟知竞赛图的套路，这里挂一下竞赛图的一些[基本事实](https://blog.csdn.net/ezoilearner/article/details/103289915)。

不难看出这里我们可以使用性质 1，比较可观的想法是获取每个点所在的强联通分量在链中的编号。

那么我们现在要找到一条把 $1 \sim n$ 串起来的路径，并且把路径缩点。

考虑数学归纳法的思想，如果我们现在已经有了一条链 $a_{1 \sim x-1}$，我们需要把当前点 $x$ 插进去。

可以插进去的充要条件就是对于位置 $p$，有边 $a_{p-1} \rightarrow x$ 和 $x \rightarrow a_p$，这个明显可以二分。假设现在二分到区间 $[l,r]$，如果有边 $x \rightarrow a_{\rm mid}$，那么可以在 $[l,\rm mid]$ 中 可以找到答案，否则 $[{\rm mid+1},r]$。

这样需要 $n \log n$ 个询问 1，可以通过这个数据。

接下来我们需要缩点，并且只能用询问 2，假设我们现在的链是 $G_{1 \sim k}$（$G_i$ 是强联通分量），那么我们可以从后往前缩点，如果有 $g \in G_i$ 到 $G_{1 \sim i-1}$ 的单向边，那么 $G_i$ 和 $G_{i-1}$ 必然可以被缩成同一点。

不难发现需要 $2n$ 个询问 2，至此本题被解决。

# Code

```cpp
const int N=105;
 
int T,n,a[N];
set<int> G[N];
bitset<N> v[N],g[N];
 
int sd() {
	int x;
	cin>>x;
	return x;
}
 
int main() {
	cin>>T;
	while (T--) {
		cin>>n;
		for (int i=0;i<N;i++) G[i].clear(),v[i]=0;
		for (int i=0;i<N;i++)
			for (int j=0;j<N;j++)
				g[i][j]=0;
		for (int i=0;i<N;i++) a[i]=0;
		for (int i=0;i<n;i++) {
			int l=1,r=i+1;
			while (l<r) {
				int mid=(l+r)>>1;
				if (mid==i+1) r=mid;
				else {
					cout<<1<<" "<<i<<" "<<a[mid]<<endl;
					if (sd()) r=mid;
					else l=mid+1;
				}
			}
			for (int j=i;j>=l;j--) a[j+1]=a[j];
			a[l]=i;
		}
		for (int i=1;i<=n;i++) G[i].insert(a[i]);
		for (int p=n;p>1;p--)
			for (auto x:G[p]) if (v[x]==0) {
				cout<<2<<" "<<x<<" ";
				int sz=0;
				for (int i=1;i<=p-1;i++) sz+=G[i].size();
				cout<<sz<<" ";
				for (int i=1;i<=p-1;i++)
					for (auto y:G[i]) cout<<y<<" ";
				cout<<endl;
				if (sd()) {
					for (auto y:G[p])
						G[p-1].insert(y);
					break;
				}
				v[x]=1;
			}
		for (int i=1;i<=n;i++)
			for (int j=i;j<=n;j++)
				for (auto x:G[i]) for (auto y:G[j])
					g[x][y]=true;
		cout<<3<<endl;
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) cout<<(g[i][j]&1);
			cout<<endl;
		}
		sd();
	}
	return 0;
}
```

---

