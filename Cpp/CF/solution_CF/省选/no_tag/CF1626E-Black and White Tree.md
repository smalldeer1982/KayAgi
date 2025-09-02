# Black and White Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. Some of the vertices (at least two) are black, all the other vertices are white.

You place a chip on one of the vertices of the tree, and then perform the following operations:

- let the current vertex where the chip is located is $ x $ . You choose a black vertex $ y $ , and then move the chip along the first edge on the simple path from $ x $ to $ y $ .

You are not allowed to choose the same black vertex $ y $ in two operations in a row (i. e., for every two consecutive operations, the chosen black vertex should be different).

You end your operations when the chip moves to the black vertex (if it is initially placed in a black vertex, you don't perform the operations at all), or when the number of performed operations exceeds $ 100^{500} $ .

For every vertex $ i $ , you have to determine if there exists a (possibly empty) sequence of operations that moves the chip to some black vertex, if the chip is initially placed on the vertex $ i $ .

## 样例 #1

### 输入

```
8
0 1 0 0 0 0 1 0
8 6
2 5
7 8
6 5
4 5
6 1
7 3```

### 输出

```
0 1 1 1 1 0 1 1```

# 题解

## 作者：dottle (赞：27)

设 $f_i$ 代表 $i$ 可否到达以 $i$ 为根的子树中的某个黑点。那么 $f_i=1$ 需要满足以下三个条件中的至少一个：

1. $c_i=1$；
2. $c_{son}=1$；
3. $f_{son}=1\ \wedge\ sum_{son}>1$。

其中 $son$ 是 $i$ 的某一个儿子，$sum_i$ 是以 $i$ 为根的子树中黑点的数量。

前两个条件很显然。对于第三个条件，考虑从 $son$ 到其子树内黑点的过程中第一个选择的黑点，无论选择的是哪一个，$i$ 都可以选择 $son$ 子树内的另一个黑点以到达 $son$。

然后套换根 dp 的板子就是了。时间复杂度 $O(n)$。

~~我认为这个思路是最自然而简洁的，因为全场没人写的比我快。~~

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1000005;
using namespace std;
 
#define _to e[i].to
#define fore(k) for(int i=hd[k];i;i=e[i].nx)
struct edge{
    int to,nx;
}e[N];int hd[N],S;
void add(int fr,int to){
    e[++S]=(edge){to,hd[fr]},hd[fr]=S;
}
 
int n,a[N];
int f[N],g[N],sz[N];
 
void dfs(int k,int fa){
	if(a[k]==1)f[k]=1;
	sz[k]=a[k];
	fore(k)if(_to!=fa){
		dfs(_to,k);
		sz[k]+=sz[_to];
		if(sz[_to]>=2&&f[_to])f[k]=1;
		if(a[_to]==1)f[k]=1;
	} 
}
 
void df5(int k,int fa){
	if(a[fa]==1)g[k]=1;
	if(f[k]==1)g[k]=1;
	fore(k)if(_to!=fa){
		if(g[k]&&sz[1]-sz[_to]>=2)
			g[_to]=1;
		df5(_to,k);
	} 
}
 
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		add(x,y),add(y,x); 
	}
	dfs(1,0);
	df5(1,0);
	for(int i=1;i<=n;i++)
		cout<<(f[i]||g[i])<<' ';
}
 
main(){
	int _T=1;//cin>>_T;
	while(_T--)solve();
}
```

---

## 作者：xkcdjerry (赞：5)

写一个题解纪念一下第一次在赛时打出的 E。 ~~虽然因为 Codeforces 断电没交上去~~ ~~后面交就 AC 了~~

这道题是一个分类讨论+一丁点数据结构的题，所以这里先把样例中的树摆出来，后面会与其对照解释各情况。（加粗的点表示黑点）

首先指派节点 $1$ 为根节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/otsy6hs8.png?x-oss-process=image/resize,m_lfit,h_350)

令 $f_i$ 为 $i$ 点是否可以到达黑点，则显然所有黑点和所有黑点的邻居 $x$ 均有 $f_x=1$。点 $2,3,5,7,8$ 属于此类。

而对于任何一对黑点 $i,j$：  

如果 $i$ 在 $j$ 的子树内，则因为可以轮流向 $i$ 与 $j$ 移动，所以 $j$ 子树外的所有点与 $i$ 子树内的所有点 $x$ 均有 $f_x=1$。

如如果 $j$ 在 $i$ 的子树内，同理可得 $j$ 子树内的所有点和 $i$ 子树外的所有点均有 $f_x=1$。

本图中不存在上面两类。

如果上面两个均不满足，即 $i$ 与 $j$ 互不包含，同理可得 $i$ 与 $j$ 子树内的点均有 $f_x=1$。点 $2,3,7$ 属于此类。

（可以注意到点 $4$ 虽然可以达到黑点但是此处未找到，将会在后面处理）

这样 naive 做的话复杂度是 $O(n^3)$ 的，考虑优化标记的复杂度。

首先可以将 $f_x \leftarrow 1$ 操作改为 $f_x \leftarrow f_x+1$，最后处理的时候将所有 $>1$ 的数视为 $1$ 即可。

那么可以使用树上差分维护：  
令 $fa_i$ 表示点 $i$ 的直接父亲，则可以构造 $g$ 数组满足：

$$g_i=
\begin{cases}
f_i& i=1\\
f_i-f_{fa_i}& {i \neq 1}
\end{cases}$$

那么显然 $f_i$ 即为 $i$ 到根路径上包括自己所有点的 $g_i$ 之和。

利用 $g$ 数组可以 $O(1)$ 完成标记操作：  
* $i$ 子树中所有点 $+1$：$g_i \leftarrow g_i+1$
* $i$ 子树外所有点 $+1$：$g_1 \leftarrow g_1+1,g_i \leftarrow g_i-1$  

最后利用 $g$ 数组的性质一次 `dfs` 即可求出 $f$ 数组。

再考虑：由于让 $i$ 的子树外/内的点可行只需要一个点在 $i$ 的子树内/外而不要求位置，所以可以利用树上前缀和来 $O(1)$ 判断是否有除了 $i$ 的黑点在 $i$ 的子树内/外。最后就优化到了 $O(n)$ 的复杂度。

还记不记得可以到达黑点但是没有找到的 $4$ 节点？这里蒟蒻也没有想出办法把它包括进分类讨论里，就用了一个最笨的办法：处理完所有前面的点之后以每个可以到达黑点的点为起点再 `dfs` 一遍，如果对于以这个点为根的树，如果对于某个儿子除了这个子树之外有两个黑点，那么这个子树内的点显然可以到达黑点（原因同上）。这虽然会进行 $n$ 次 `dfs` 但是施以一个 `vis` 数组就可以使其也为 $O(n)$ 复杂度。

蒟蒻的代码如下：

```c++
#include <cstdio>
#include <vector>
#define N 300010
using std::vector;
vector<int> e[N];
int n;
bool f[N];
//g 为 f 的树上差分数组，h 为 c 的树上前缀和数组
int g[N], h[N];
int c[N];
int father[N];

int sum;
void dfs2(int o,int fa=-1)
{
	if (sum) f[o] = true;
	sum += g[o];
	for (auto i : e[o]) if (i != fa) dfs2(i, o);
	sum -= g[o];
}

int dfs1(int o, int fa = -1)
{
	int sum = 0;
	for (auto i : e[o]) if (i != fa) sum+=dfs1(i, o);
	if (c[o])
	{
		sum++;
		f[o] = true;
		for (auto i : e[o]) f[i] = true;
	}
	h[o] = sum;
	father[o] = fa;
	return sum;
}
//ff 作 vis
bool ff[N];
void dfs3(int o, int fa = -1)
{
	f[o] = true;
	ff[o] = true;
	//向root方向拓展
	if (father[o]!=-1&&h[o] >= 2&&!f[father[o]]) dfs3(father[o], o);
	//向儿子方向拓展
	for (auto i : e[o])
	{
		if (i != father[o] && !f[i] && h[1] - h[i] >= 2)
		{
			dfs3(i, o);
		}
	}
}
int main()
{
	constexpr int ROOT = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(ROOT);
	for (int i = 1; i <= n; i++)
	{
		//记得必须以黑点为基础拓展
		if (c[i])
		{
			if (h[i] - 1)
			{
				g[ROOT]++;
				g[i]--;
			}
			if (h[i] != h[ROOT])
			{
				g[i]++;
			}
		}
	}
	dfs2(ROOT);
	//丑陋的补救措施
	for (int i = 1; i <= n; i++) if(f[i]&&!ff[i]) dfs3(i);
	//所有>1的均视为1
	for (int i = 1; i <= n; i++) printf("%d ", f[i] ? 1 : 0);
}
```

[评测记录](https://www.luogu.com.cn/record/67027768)

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 2400}$
---
### 解题思路：

首先可以发现任意黑点或者与黑点相邻的点都一定是可行的点。关键就在于其它的点应当如何求解其他的点。

当一个点可以到达一个可以到达黑点的点且如果以当前点为根节点，那个后继点的子树上至少有两个黑点的话当期点就一定可以到达黑点。方案为选择后继点方案中不是第一个选择的那一个黑点到达后继点然后直接按照和后继点一样的方案做就行了。

然后证明不满足这个条件的一定不可行，当后继点不能达到黑点，则无论如何选择黑点以到达后继点也不可能进行下一步的操作。当后继点子树的黑点数只有一个的时候，只能选择相同的黑点，而这与条件冲突。

实现的时候用换根 $\text{DP}$ 就行了。


---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=600005;
int n,p[MAXN],head[MAXN],nxt[MAXN],num[MAXN],tot,f[MAXN],size[MAXN],x,y;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void dfs(int now,int fa){
	if(p[now]==1)f[now]=1,size[now]=1;;
	if(p[fa]==1)f[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		dfs(num[i],now);
		if(f[num[i]]==1&&size[num[i]]>=2)f[now]=1;
		if(p[num[i]]==1)f[now]=1;
		size[now]+=size[num[i]];
	}
}
void re_dfs(int now,int fa){
	if(p[fa]==1)f[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		if(f[now]==1&&size[1]-size[num[i]]>=2)f[num[i]]=1;
		re_dfs(num[i],now);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	re_dfs(1,0);
	for(int i=1;i<=n;i++)
	printf("%d ",f[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：Jorge_Filho (赞：2)

# CF1626E Solution

## 题意:
给你一棵树（不是无根树，这题翻译有问题），每一个节点要不然是黑色的，要不然是白色的，且黑色的节点至少有两个。先要求你选择**每一个**节点（无论黑白），每次可以向任意一个黑色节点移动一条边（但不能连续两次向同一个黑色移动），问最终能否走到一个黑点（任意一个都可）。注意：当步数超过 $10^{500}$ 的时候，视为无法走到一个黑点。

## 解析:

首先明确一点，~~通过感性分析和实际验证我们发现~~走不到就是走不到，如果走得到早就在 $10^{500}$ 步以前走到了（实际上最坏情况是一条链，最多需要在不冤枉的情况下走 $n-1$ 次就可以），所以我们只需要判断能都走到就行了（感性分析过程：计算无法在给定时间内模拟出这么多次移动，且 $n$ 的最大值 $3 \times 10^5$ 的数量级远小于 $10^{500}$）。

接着我们来模拟一下样例，发现如果一颗子树里只含有一个黑点，那我们永远无法达到这棵子树更深的地方以到达黑点（因为向这个唯一的黑点移动了一条边以后无法再次向这个黑点移动），除非我们移动的下一步就是黑点。于是我们一遍Dfs求出以任意一个节点为根的子树里有多少个黑点（当然用黑点的总数减去它就得到了以这条边为分割线的另一颗树的黑点个数），如果个数不小于2，那么说明至少从这个节点的父亲节点走到这个节点**可能**可行，如果下一步就是黑点，那么**一定**可行。那么怎么进一步处理呢？

我们新建一个图，保留所有原先的节点，但一开始没有边。我们对可能可行和一定可行的走法连一条边（例如从 $u$ 节点走到 $v$ 节点可能可行，我们就从 $u$ 向 $v$ 连一条有向边），如果一个节点是可以走到一个黑色节点的，那么它通过几条可能可行的的边一定会走到一条一定可行的边（并且在原图上的路径就和新图的路径是一样的），反之，就算其一开始有可能可行的边，最后也无法走到一定可行的边。画两个个图大家就明白了：

![走得到](https://cdn.luogu.com.cn/upload/image_hosting/fr5otmi6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

0号节点可以最终可以走到3号节点。

![走不到](https://cdn.luogu.com.cn/upload/image_hosting/lfangqo0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

0号节点一开始有可能可行的边但最终走不到黑色节点。

于是最后判断从每一个节点出发能否达到一个黑色节点即可。

问题来了，这样的时间复杂度将会达到无法令人接收的 $n^2$ 级别（实际可能远远达不到，但出题人可以卡你）。考虑优化：对于每一条边，我们反向建边，然后从每一个黑色节点出发，看能到达的点有哪些。因为反向建边了，黑色节点能达到的点在不反向建边的情况下一定能够走到黑色节点。再利用一个标记桶（如果以前已经走到过就不再继续搜索了），这样判断可达性的时间复杂度就直接降次了。

最后来分析一下时间复杂度：输入的 $O(n)$，加上求每一棵子树里含有黑色节点的个数的Dfs的 $O(n)$ 和反向建边以及判断可达性的 $O(n)$，最终的渐进时间复杂度：$O(n)$。（这个的常数极大，那要不然为什 $3 \times 10^5$ 的数据跑了 $243ms$）

Code：（为了各位读者我格式化了一下毒瘤码风）
```cpp
#include<bits/stdc++.h>
#define Add1(x,y) e1[idx1]=y,ne1[idx1]=h1[x],h1[x]=idx1++;
#define Add2(x,y) e2[idx2]=y,ne2[idx2]=h2[x],h2[x]=idx2++;
using namespace std;
const long long N=3e5,M=N-1,C=1;
int n,m,t,x,y,s[N+5]/*存储所有黑色节点的编号以便后面判断可达性*/,top,bla[N+5]/*以每一个节点为根的子树里面的黑色节点数量*/,fat[N+5];
int h1[N+5],ne1[2*M+5],e1[2*M+5],idx1;//原始图
int h2[N+5],ne2[2*M+5],e2[2*M+5],idx2;//新建的反向建边的图
bool c[N+5]/*color,是1表示黑,否则是白*/,bjt[N+5]/*判断可达性的标记桶*/;
void Dfs1(const int &x,const int &fa) { //确定父子关系以及每一颗子树里面的黑色节点数量
	for(int i=h1[x]; ~i; i=ne1[i]) {
		int cur=e1[i];
		if(cur==fa) continue;
		Dfs1(cur,x);
		fat[cur]=x;
		bla[x]+=bla[cur];
	}
}
void Dfs2(const int &x) { //判断可达性
	for(int i=h2[x]; ~i; i=ne2[i]) {
		int cur=e2[i];
		if(bjt[cur]) continue;
		bjt[cur]=1;
		Dfs2(cur);
	}
}
int main() {
	scanf("%d",&n);
	fill(h1+1,h1+n+1,-1);
	fill(h2+1,h2+n+1,-1);
	m=n-1;
	for(int i=1; i<=n; i++) {
		scanf("%d",&t);
		if(t) {
			c[i]=1;
			bla[i]=1;
			s[++top]=i;
		} else c[i]=0;
	}
	for(int i=1; i<=m; i++) {
		scanf("%d%d",&x,&y);
		Add1(x,y);
		Add1(y,x);
	}
	Dfs1(1,0);
	for(int i=1; i<=n; i++)
		for(int j=h1[i]; ~j; j=ne1[j]) {
			int cur=e1[j];
			if(fat[i]==cur) continue;
			if(bla[cur]>1/*可能可行*/||c[cur]/*一定可行*/) Add2(cur,i);
			if(top-bla[cur]>1/*可能可行*/||c[i]/*一定可行*/) Add2(i,cur);
		}
	for(int i=1; i<=top; i++) {
		bjt[s[i]]=1;
		Dfs2(s[i]);
	}
	for(int i=1; i<=n; i++) {
		if(bjt[i]) printf("%d ",1);
		else printf("%d ",0);
	}
	return 0;
}
```
[AC记录](https://codeforces.com/contest/1626/submission/146055667)

注：个人认为此方法非常容易理解，思维难度其实也挺小的（可能就是时间复杂度劣了一点）。

---

## 作者：wqc2011 (赞：1)

[题目传送门](https://codeforces.com/contest/1626/problem/E)

首先，对于任意点 $x$ 为根，有 3 种情况能走到黑点：

- $x$ 本身为黑点。
- $x$ 有一个儿子 $y$ 为黑点。
![](https://cdn.luogu.com.cn/upload/image_hosting/xdfrhowu.png)
- $x$ 有一个儿子 $y$ 可以走到黑点，且子树 $y$ 中的黑点数量 $si_y>1$。
![](https://cdn.luogu.com.cn/upload/image_hosting/ih5q2ngo.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/22gdcqbi.png)

如果以每个点为根暴力 dfs 肯定会超时，所以我们先以 $1$ 为根搜出每棵子树 $y$ 中的黑点个数 $si_y$，并求出每个节点是否能从自己儿子 $son$ 走到黑点，如样例，$(8,5,7,2)$ 均可行。
![](https://cdn.luogu.com.cn/upload/image_hosting/12hik72b.png)
再进行第二次搜索，把自己父亲 $f_x$ 看作一个儿子，父亲的黑点数为总黑点数 $cnt$ 减当前节点的黑点数 $si_x$，再进行判断即可。
### 代码附上————

```cpp
#include<bits/stdc++.h>
// #define int long long
using namespace std;
const int maxn = 300010;
const int inf = 1e9;
//unsigned long long 
//cout << fixed << setprecision(3)
//cout << setw(5) << 
//continue
int a[maxn], si[maxn], f[maxn], cnt, cnt1, t[maxn * 2], nxt[maxn * 2], head[maxn];
bool ans[maxn];
void add(int x, int y){
    cnt1++;
    t[cnt1] = y;
    nxt[cnt1] = head[x];
    head[x] = cnt1;
}
void dfs(int x, int fa){
    si[x] = a[x];
    f[x] = fa;
    for(int i = head[x];i;i = nxt[i]){
        int to = t[i];
        if(to == fa) continue;
        dfs(to, x);
        si[x] += si[to];
		if(a[to] || (si[to] >= 2 && ans[to])){
			ans[x] = 1;
		}
    }
}
void dfs1(int x, int fa){
	if(a[fa]) ans[x] = 1;
    for(int i = head[x];i;i = nxt[i]){
		int to = t[i];
		if(to == fa) continue;
		if(ans[x] && si[1] - si[to] >= 2){
			ans[to] = 1;
		}
		dfs1(to, x);
	}
}
signed main(){
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        cnt += a[i];
        ans[i] = a[i];
    } 
    // cout << cnt << endl;
    for(int i = 1;i < n;i++){
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    dfs1(1, 0);
    for(int i = 1;i <= n;i++){
        cout << ans[i] << ' ';
    }
    return 0;
}
```
### 感谢阅读！

---

## 作者：Claire0918 (赞：1)

纪念校内模拟赛首次**有记录**切紫。

记 $a_u$ 表示 $u$ 点的颜色。

先令 $1$ 为树的根，考量 $1$ 可以到达黑点的条件，不难想到以下可能的两条：

1. $1$ 有一条边连向黑点。
2. $1$ 有一条边连向 $u$，而 $u$ 可以到达黑点。

但是，第二条条件有反例。如下图，加粗的为黑点。

![](https://cdn.luogu.com.cn/upload/image_hosting/j0uoo7ew.png)

$2$ 显然是可以到达 $3$ 的。$1$ 有边直接连向 $2$，但是在选定 $3$ 并到达 $2$ 之后，不能再选择 $3$ 来从 $2$ 到 $3$。

我们发现如果 $1$ 可以到达 $3$，不仅需要 $2$ 可以到达 $3$，$2$ 子树内除 $3$ 外还需要一个黑点，否则我们只能选定 $3$ 才能走到 $2$，此时无法再选择另外一个黑点了。

综上，我们得到了完全正确的条件：

1. $1$ 有一条边连向黑点。
2. $1$ 有一条边连向 $u$，$u$ 可以到达黑点且 $u$ 子树中有至少两个黑点。

我们从 $1$ 开始 DFS，记 $cnt_u$ 表示 $u$ 子树内黑点的数量，$f_u$ 表示仅考虑 $u$ 子树中的点时 $u$ 是否能到达黑点。有显然的转移
$$
f_u = a_u \vee (\vee_{v \in \operatorname{son}(u)} \{a_v \vee (f_v \wedge (cnt_v \geq 2))\})
$$
如果每求一个点的答案都要重新 DFS，时间复杂度会达到 $\mathcal{O}(n^2)$，无法通过。考虑换根。对于 $u$，如果 $v \in \operatorname{son}(u)$，那么 $v$ 的正确答案 $f'_v$ 的转移是
$$
f'_v = f_v \vee (a_u \vee (f'_u \wedge (cnt_1 - cnt_u \geq 2)))
$$
即将 $u$ 看作 $v$ 的一个儿子。$cnt_1 - cnt_u$ 表示以 $1$ 为根时不在 $v$ 子树内的黑点数量，即以 $v$ 为根时在 $u$ 子树内的黑点数量，与 $f_u$ 的转移式中 $cnt_v$ 意义相同。

再从 $1$ 开始进行一次 DFS，在 $u$ 通过上文转移式和已知的 $f'_u$ 对于每一个儿子 $v$ 计算 $f'_v$。总时间复杂度 $\mathcal{O}(n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 3e5 + 10;

struct{
    int v, nex;
} edge[maxn << 1];

int n;
bool a[maxn], f[maxn];
int cnt[maxn];
int head[maxn], top = 0;

inline void add(int u, int v){
    edge[++top].v = v;
    edge[top].nex = head[u];
    head[u] = top;
}

inline void dfs1(int u, int fa){
    cnt[u] = f[u] = a[u];
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (v != fa){
            dfs1(v, u);
            cnt[u] += cnt[v];
            f[u] |= a[v] || cnt[v] >= 2 && f[v];
        }
    }
}

inline void dfs2(int u, int fa){
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (v != fa){
            f[v] |= a[u] || cnt[1] - cnt[v] >= 2 && f[u];
            dfs2(v, u);
        }
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++){
        printf("%d ", f[i]);
    }

return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1626E - Black and White Tree 题解

## 题目大意

给定一棵 $n$ 个定点的无根树，其中有一些顶点是黑色的（至少两个），其余则是白色的

你可以从任意一个顶点出发，按如下规则行进（也可以不行动）：

- 选择任意一个黑色顶点，沿着当前顶点到该黑色顶点的简单路径前进一步
- 注意：除第一次行动之外，你每次选择的顶点不可以与上次选择的顶点相同
- 你可以行动至多 $100^{500}$ 次，如果到达黑色顶点，则立即终止

已知这棵树的形态和黑色顶点的分布，请你求出每个顶点能不能在规定次数内到达黑色顶点

数据范围保证：$n\le 3\times10^5$

## 思路分析

我们定义一次从 $u$ 到 $v$ 的“有效边”表示从可以 $u$ 行动到 $v$ 并且接下来一步可以走到 $v$ 的子节点或者直接结束行动而不是走回 $u$

那么一条原树上从 $a$ 到 $b$ 的有向边成为一条“有效边”的条件是

1. $b$ 是黑色顶点 ，走到 $b$ 后直接结束
2. $a$，$b$ 不连通后，$b$ 所在的连通块内至少有 $2$ 个黑色顶点，这样我们可以选择其中的一个从 $a$ 到 $b$，然后选择另一个从 $b$ 走到 $b$ 的子节点

满足以上两种之一的边都是“有效边”，如果我们把所有的有效边建成一张图 $S$ 那么原问题就转换为了每个 $S$ 中的顶点能否沿着 $S$ 里的边到达黑色顶点，对于这个问题，可以把 $S$ 里的每条边取反，然后用一遍 BFS 判断哪些顶点是黑色顶点可以到达的

**注意：$S$ 里面的边是有向边**

时间复杂度：$\Theta(n)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+1;
vector <int> edge1[MAXN],edge2[MAXN];
//edge1是原图，edge2是S 
int siz[MAXN],cnt;
bool dot[MAXN],vis[MAXN];
inline void add1(int u,int v) {
	edge1[u].push_back(v);
}
inline void add2(int u,int v) {
	edge2[u].push_back(v);
}
inline void dfs(int pos,int f) {
	//dfs判断每条边是否是有效边 
	if(dot[pos]) {
		//siz记录以pos为根的节点内有多少黑色顶点 
		++siz[pos];
	}
	for(register auto i:edge1[pos]) {
		if(i==f) continue;
		dfs(i,pos);
		siz[pos]+=siz[i];
		if(dot[i]||siz[i]>1) {
			//判断当前节点到其儿子的边是否是有效边 
			add2(i,pos); //注意取反边 
		}
	}
	if(dot[f]||cnt-siz[pos]>1) {
		//判断当前节点到其父亲的边是否是有效边 
		add2(f,pos); //注意取反边 
	}
	return ;
}
queue <int> q;
signed main() {
	int n;
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) {
		scanf("%d",&dot[i]);
		if(dot[i]) {
			++cnt;
			vis[i]=true;
			q.push(i);
		}
	}
	for(register int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		add1(u,v);
		add1(v,u);
	}
	dfs(1,0); //DFS建出图S
	//BFS判断每个点是否能到达 
	while(!q.empty()) {
		int pos=q.front();
		q.pop();
		for(register auto i:edge2[pos]) {
			if(!vis[i]) {
				vis[i]=true;
				q.push(i);
			}
		}
	}
	for(register int i=1;i<=n;++i) printf("%d ",vis[i]);
	putchar('\n');
	return 0;
} 
```



---

## 作者：IdnadRev (赞：0)

想了好久，最后猜了一个小结论过了。

## 题意

给定一棵无根树，点有颜色（黑/白），对于每个 $x$，求出从 $x$ 出发，每次可以选择一个黑点（与上次选择的黑点不能重复），使得白点向黑点移动一步，求出是否能到达黑点。

$1\leqslant n\leqslant 3\times 10^5$

## 分析

类似换根 dp，我们考虑先求出一个点能不能到其子树内的黑点，然后再求全局的答案。

手玩一下可以发现一个性质：给定两个黑点 $x,y$，若一个点是 $\text{lca}(x,y)$ 的距离小于等于 $1$，那么 $\text{lca}(x,y)$ 的祖先都能到达子树内的黑点。

那么随便维护一下就好了，复杂度 $O(n)$。

## 代码
```
#include<algorithm>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<map>
using namespace std;
const int maxn=300005;
int n,m,T,tot;
int a[maxn],sz[maxn],f[maxn];
vector<int>v[maxn];
string s;
void dfs1(int x,int last) {
	int flg=0;
	sz[x]=a[x];
	if(a[x]||a[last])
		f[x]=1;
	for(int i=0; i<v[x].size(); i++) {
		int y=v[x][i];
		if(y==last)
			continue;
		dfs1(y,x),sz[x]+=sz[y];
		if(a[y]||(f[y]&&sz[y]>1))
			f[x]=1;
	}
}
void dfs2(int x,int last) {
	for(int i=0; i<v[x].size(); i++) {
		int y=v[x][i];
		if(y==last)
			continue;
		if(f[x]&&tot-sz[y]>1)
			f[y]=1;
		dfs2(y,x);
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]),tot+=a[i];
	for(int i=1,x,y; i<n; i++)
		scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs1(1,0),dfs2(1,0);
	for(int i=1; i<=n; i++)
		printf("%d%c",f[i],i==n? '\n':' ');
	return 0;
}
```

---

## 作者：滑蒻稽 (赞：0)

## Sol

考虑换根 DP，并考虑一些基础事实：
- 称可以走到黑色的点，即最后答案为 $1$ 的点是「合法」的。
- 如果一个点 $u$ 的子树内至少有两个黑点，那么 $u$ 的祖先就可以走到 $u$。
- 如果一个点 $u$ 自己是黑色，或有任意一个儿子是黑色，那么 $u$ 就是「直接合法」的。
- 如果一个点 $u$ 能走到任意一个「直接合法」的点，那么 $u$ 就是「间接合法」的。

我们使用一个数组 `ok` 来标记「使得所有祖先合法」的点。如果一个点直接合法，并且祖先能走到自己（即子树内至少有两个黑点），那么它的 `ok` 便为 `true`；如果一个点有任意一个儿子的 `ok` 为 `true`，那么它的 `ok` 也为 `true`。

这样，对于每次的树根，如果 `ok` 为 `true`，或者它自己是直接合法的，那么它便是合法的。

在换根的时候需要重新计算 `ok`，所以需要维护一个点子树内黑点数量、`ok` 标记为 `true` 的儿子数量、邻点是黑色点的数量。重新计算完毕后就可以进入儿子。

## My Code

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5;
int n, c[N], sz[N], ok[N], ans[N], cnt[N], okc[N];
// sz 为子树内黑点数量，cnt 表示邻点和自己是黑色的数量，okc 表示 ok 为 true 的儿子数量 
vector<int> g[N];
void dfs(int u, int f) {
	if(c[u] == 1) sz[u] = 1;
	for(int &v : g[u]) {
		if(v != f) {
			dfs(v, u);
			okc[u] += ok[v], sz[u] += sz[v];
		}
	}
	cnt[u] = c[u];
	for(int &v : g[u])
		if(v != f) cnt[u] += c[v];
	if((sz[u] >= 2 && cnt[u]) || okc[u]) ok[u] = true; 
}
void croot(int u, int f) {
	// 判定答案 
	ans[u] = ok[u] | c[u];
	for(int &v : g[u]) ans[u] |= c[v];
	
	for(int &v : g[u]) {
		if(v != f) {
			// 存储会改变的信息 
			int oszu = sz[u], oszv = sz[v], ooku = ok[u];
			int ookv = ok[v], octu = cnt[u], octv = cnt[v];
			int ookcu = okc[u], ookcv = okc[v];
			// 为换根做准备 
			sz[u] -= sz[v], sz[v] += sz[u];
			cnt[u] -= c[v], cnt[v] += c[u]; 
			okc[u] -= ok[v], ok[u] = (sz[u] >= 2 && cnt[u]) || okc[u]; 
			okc[v] += ok[u], ok[v] = (sz[v] >= 2 && cnt[v]) || okc[v];
			croot(v, u);
			// 还原改动过的信息 
			sz[u] = oszu, sz[v] = oszv, ok[u] = ooku;
			ok[v] = ookv, cnt[u] = octu, cnt[v] = octv;
			okc[u] = ookcu, okc[v] = ookcv;
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> c[i];
	for(int i = 1, u, v; i < n; i++)
		cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
	dfs(1, 0);
	croot(1, 0);
	for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
	
	return 0;
}
```

---

