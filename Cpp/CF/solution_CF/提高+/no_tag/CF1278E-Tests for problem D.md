# Tests for problem D

## 题目描述

We had a really tough time generating tests for problem D. In order to prepare strong tests, we had to solve the following problem.

Given an undirected labeled tree consisting of $ n $ vertices, find a set of segments such that:

1. both endpoints of each segment are integers from $ 1 $ to $ 2n $ , and each integer from $ 1 $ to $ 2n $ should appear as an endpoint of exactly one segment;
2. all segments are non-degenerate;
3. for each pair $ (i, j) $ such that $ i \ne j $ , $ i \in [1, n] $ and $ j \in [1, n] $ , the vertices $ i $ and $ j $ are connected with an edge if and only if the segments $ i $ and $ j $ intersect, but neither segment $ i $ is fully contained in segment $ j $ , nor segment $ j $ is fully contained in segment $ i $ .

Can you solve this problem too?

## 样例 #1

### 输入

```
6
1 2
1 3
3 4
3 5
2 6
```

### 输出

```
9 12
7 10
3 11
1 5
2 4
6 8
```

## 样例 #2

### 输入

```
1
```

### 输出

```
1 2
```

# 题解

## 作者：Sol1 (赞：6)

来一个超级好想的解法。

这道题给了一棵 $n$ 个点的树，要求我们构造 $n$ 个区间，使得对于任意两个区间 $i,j$，如果它们之间相交但是没有包含关系，则 $i,j$ 之间有边；反之则无边。

显然，对于一个点 $u$，取任意两个与之相连的点 $v_1,v_2$，则第 $v_1$ 个区间和第 $v_2$ 个区间一定不相交或者包含。

不妨我们只让一个邻接的点在左边与 $u$ 相交，剩下的都在右边和 $u$ 相交，并互相包含。

于是我们整理一下思路，就有方法了：

- 从 $1$ 开始 dfs，`dfs(u)` 之前 $u$ 的左端点已经确定为 $l_u$。
- 保存一个全局 $R$，初始 $R=1$。
- 每次进入 $u$ 节点时，如果 $u$ 有 $k$ 个儿子，$R$ 增加 $k+1$。
- 依次遍历所有儿子，对于第 $i$ 个儿子 $v_i$，确定 $l_{v_i}=r_u-i$，并递归 $v_i$。

具体看代码。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
int n, hd[500005], pnt, ansl[500005], ansr[500005], rpnt, dgr[500005];
Edge e[1000005];

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread();
	for (register int i = 1;i < n;i++) {
		register int u = qread(), v = qread();
		AddEdge(u, v);
		AddEdge(v, u);
		dgr[u]++; dgr[v]++;
	}
}

inline void Dfs(int u, int fa) {
	register int cnt = 1;
	if (fa != -1) rpnt += dgr[u];
	else rpnt += dgr[u] + 1;
	ansr[u] = rpnt;
	for (register int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) {
			ansl[e[i].to] = ansr[u] - cnt;
			cnt++;
			Dfs(e[i].to, u);
		}
	}
}

inline void Solve() {
	ansl[1] = 1;
	rpnt = 1;
	Dfs(1, -1);
	for (register int i = 1;i <= n;i++) printf("%d %d\n", ansl[i], ansr[i]);
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}

```

---

## 作者：x义x (赞：3)

@土田共戈 的题解说得很好，但是此题不需要什么启发式合并。

构造策略：

- 遍历节点 $x$ 的每个儿子，分别处理这些儿子对应的子树。此时这些儿子的右端点尚未确定。

- 新安排一个位置（``idx++``），它是 $x$ 的左端点。

- 逆序遍历 $x$ 的每个儿子，依次向右安排它们的右端点（``idx++``）。

具体见代码。

~~也推荐看@土田共戈 的图解。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

int N;
int lnk[500005];
int pre[1000005],tgt[1000005],cnt;
void add_E(int u,int v){
	pre[++cnt]=lnk[u],tgt[cnt]=v,lnk[u]=cnt;
}

int idx;
int ANSL[500005],ANSR[500005];
int stk[500005],len;
void DFS(int x,int f){
	for(int e=lnk[x];e;e=pre[e]) if(tgt[e]!=f)
		DFS(tgt[e],x);
	for(int e=lnk[x];e;e=pre[e]) if(tgt[e]!=f)
		stk[++len]=tgt[e];
	ANSL[x]=++idx;
	while(len)
		ANSR[stk[len]]=++idx,len--;
}

int main(){
	scanf("%d",&N);
	for(int i=1;i<N;i++){
		int u,v;scanf("%d%d",&u,&v);
		add_E(u,v);add_E(v,u);
	}
	DFS(1,0);
	ANSR[1]=++idx;
	for(int i=1;i<=N;i++)
		printf("%d %d\n",ANSL[i],ANSR[i]);
}
```

---

## 作者：huangrenheluogu (赞：1)

本来看到这道题没有什么思路，于是观察了一下样例，就有思路了。

首先，自己构造发现构造不出来，猜测这种构造方法不会很多。

看看样例，发现听有规律？好了。

注：因为样例 $1$ 是在最右边，我比较喜欢把 $1$ 放左边，所以方向不一样，题解中，我用 $ansl_x,ansr_x$ 表示 $x$ 区间左右端点的编号。

我们遍历到一个节点 $x$，它的区间中间一定包含了 $ansr_{fa}$ 和 $ansl_{v},v\in son_x$。其中，兄弟节点用全包含的形式保证不相交。

就这样构造，可以随便写写，调调就好了。

还是简单说一下我的构造方法。先预处理出每个节点的儿子个数 $szs_x$。

首先，对于一个节点 $x$，我传入了四个参数，$x,fa,nowl,nowr$，前面两个参数是比较易懂的，后面的表示 $ansl_x$ 和 $ansr_x$ 上一个兄弟传过来的 $r$，显然，我们这一个节点需要包含上一个兄弟（如果没有上一个兄弟，可以理解为是 $[ansr_fa, ansr_{fa}]$ 这个区间。

这个节点的有端点肯定是 $ansr_x+szs_x$，儿子的左端点肯定满足 $ansl_x<ansl_v<ansr_x,v\in son_x$，那么我们就让 $ansl_v$ 从 $ansr_x-1$ 开始遍历，每次减 $1$，这样，儿子的左端点就填好了。

右端点需要包含上一个兄弟的右端点，所以可以让函数返回目前兄弟填到了哪里，然后更新当前节点儿子的 $nowr$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n, ansl[N], ansr[N], idx = 1, u, v, fir[N], nxt[N << 1], son[N << 1], tot, szs[N], dep[N];
bool vis[N << 1];
inline void add(int x, int y){
    nxt[++tot] = fir[x];
    fir[x] = tot;
    son[tot] = y;
}
inline void dfs(int x, int ff = 0){
    for(int i = fir[x]; i ; i = nxt[i]){
        if(son[i] == ff) continue ;
        szs[x] ++;
        dfs(son[i], x);
    }
}
inline int solve(int x, int ff, int lnow, int rnow){
    vis[ansl[x] = lnow] = 1;
    rnow += szs[x];
    lnow = rnow - 1;
    vis[ansr[x] = rnow] = 1;
    for(int i = fir[x]; i ; i = nxt[i]){
        if(son[i] == ff) continue ;
        rnow = solve(son[i], x, lnow, rnow + 1);
        lnow--;
    }
    return rnow;
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    solve(1, 0, 1, 2);
    for(int i = 1; i <= n; i++){
        printf("%d %d\n", ansl[i], ansr[i]);
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Preface

自认为这是目前最短代码。

### Analysis

以 $1$ 为根，DFS 整棵树。每个节点如图构造，每个子树递归下去。由于下一个子树的起始位置由上一个子树的大小决定，我们 DFS 时传回结束位置即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/f62cuqs9.png)

（图中虚线框表示子树递归）

时间 $O(n)$

### Code

[Link](https://codeforces.com/contest/1278/submission/150411285)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb emplace_back
#define fir first
#define sec second
#define For(i,j,k) for(int i=j;i<=k;i++)
#define N 500010
#define endl '\n'
int n;
pair<int,int> a[N];
vector<int> e[N];
int dfs(int rt,int fa,int le){
	a[rt].sec=le+e[rt].size();//e.size=cnt_son+1
	int L=a[rt].sec,R=a[rt].sec;
	for(int i:e[rt]){
		if(i==fa) continue;
		a[i].fir=--L;
		R=dfs(i,rt,R);
	}
	return R;
}
signed main(){IOS;
	cin>>n;
	int x,y;
	For(i,1,n-1){
		cin>>x>>y;
		e[x].pb(y);e[y].pb(x);
	}
	e[1].pb(0);
	a[1].fir=1;
	dfs(1,0,1);
	For(i,1,n) cout<<a[i].fir<<" "<<a[i].sec<<endl;
return 0;}
```

---

## 作者：caidzh (赞：1)

把官方题解扔到Google翻译里发现似乎什么都没讲（也许是我理解能力过差qwq）？于是过来补篇题解

采取这样递归的构造方式：把当前处理的子树的根的右端点放在最右，我们把它的儿子在线段上一层层套起来，然后把左端点放到它的儿子套住的点处

这样说似乎没法理解，下面给出图示：
![](https://cdn.luogu.com.cn/upload/image_hosting/kjork8q7.png)

这是我们要得到的树

对于$3,5,6,7$三个点，我们直接给他们置为$[1,2]$

然后我们考虑合并$2,5$，显然答案可以是：$[2,4],[1,3]$，实际上我们是通过把$5$放在左边，然后套住了$[2]$作为$2$的左端点，再把$2$的右端点置为$2\times size_2$得到的

接下来合并$4,6,7$，我们把$6,7$套在一起：$[1,5],[2,4]$，注意到腾出了$3$这个位置，所以$4$即为$[3,6]$

所以你应该大致知道上面说的到底是什么玩意儿了，接下来我们通过合并上图中的三棵子树来讲怎么避免非儿子节点的影响

由于线段上最右边那个点肯定属于子树的根，根在接下来的合并中是作为儿子出现的

我们想要让这些根一层层套起来，首先取出$4$这棵子树，我们把$4$的左端点和子树中的点都放进去（右端点先让它等等）
![](https://cdn.luogu.com.cn/upload/image_hosting/613thagy.png)

然后我们加入第二棵子树$2$，还是让根的右端点等一会儿
![](https://cdn.luogu.com.cn/upload/image_hosting/6goub9j7.png)

最后加入点$3$，我们上面说过一定要用儿子套住一个点，所以中间空出一个点（右端点同样）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9zf3cx8s.png)

然后我们加入现在要加入的根的左端点，之前用栈记录儿子的出现，然后反着加入回去：
![](https://cdn.luogu.com.cn/upload/image_hosting/i1m6x98f.png)

这样就做完了，可以发现根肯定不会向儿子子树内除儿子外节点连边，之后的处理也是类似的

直接做复杂度是$O(n^2)$，发现对于第一个被加入的子树左右端点位置没有变化，所以我们类似启发式合并的方式做就好了

UPD：在作者成功发现自己是一个傻逼后，深刻地进行了反省以及虔诚膜拜了巨佬x义x

这题直接线性加入点就好了，没必要像下面代码一样这么麻烦，具体可见x义x巨佬的题解
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
int n,head[maxn],cnt,size[maxn],ansx[maxn],ansy[maxn],sta[maxn],top;
struct Edge{int nxt,to;}edge[maxn<<1];
void add_edge(int x,int y){
	edge[++cnt].nxt=head[x];edge[cnt].to=y;head[x]=cnt;
}vector<int>p[maxn];
void dfs(int x,int fa){
	int lst=0,now=0;size[x]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;dfs(v,x);size[x]+=size[v];
		if(size[v]>size[now])now=v;
	}if(size[x]==1){p[x].push_back(x);ansx[x]=1;ansy[x]=2;return;}
	swap(p[x],p[now]);p[x].push_back(x);lst=2*size[now]-1;sta[++top]=now;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa||v==now)continue;sta[++top]=v;
		for(int j=0;j<p[v].size();j++){
			ansx[p[v][j]]+=lst;if(p[v][j]!=v)ansy[p[v][j]]+=lst;p[x].push_back(p[v][j]);
		}lst+=2*size[v]-1;
	}lst++;ansx[x]=lst;ansy[x]=2*size[x];
	while(top){int v=sta[top--];ansy[v]=++lst;}
}
int main()
{
	scanf("%d",&n);for(int i=1;i<n;i++){int x,y;scanf("%d%d",&x,&y);add_edge(x,y);add_edge(y,x);}
	dfs(1,0);for(int i=1;i<=n;i++)cout<<ansx[i]<<" "<<ansy[i]<<endl;return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
本题的精华在于题目中“构造 $n$ 个区间”这句话，鲜明地表达了本题的算法：构造。所以我们它的正确性就不用考虑了，我们只关心如何构造。
## 分析。
考虑维护一个链表。开始时我们让第 $1$ 号结点为根结点，并把第 $1$ 号结点的所代表的区间的两个端点插入链表。然后从第 $1$ 号结点开始进行搜索。每遍历到一个新结点，就把它所代表的区间的左端点插入它父亲所代表的区间的右端点的左边，再把它所代表的区间的右端点插入它父亲所代表的线段的右端点的右边，可以简单理解为合并两个区间，最后遍历整个链表，给每个区间的端点分配一个下标，随后输出。

时间复杂度 $O\left(n\right)$ 绰绰有余。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,v,u;
struct node{
    int l,r;
}a[500005*2],ans[500005];
struct edge{
    int nex,to;
}b[500005*2];
int head[500005];
int sum,c=2,countt=0;
void add_edge(int u,int v){
    b[c].to=v;
    b[c].nex=head[u];
    head[u]=c++;
}
void build(int son,int fa){
	int left=a[fa<<1|1].l,right=a[fa<<1|1].r;
    a[left].r=son<<1;
    a[right].l=son<<1|1;
    a[son<<1].l=left;
    a[son<<1].r=fa<<1|1;
    a[fa<<1|1].l=son<<1;
    a[fa<<1|1].r=son<<1|1;
    a[son<<1|1].l=fa<<1|1;
    a[son<<1|1].r=right;
}
void dfs(int id,int fa){
    if(fa!=0){
	    build(id,fa);
	}
    for(int i=head[id];i;i=b[i].nex){
        if(b[i].to==fa){
		    continue;
		}
        dfs(b[i].to,id);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n-1;i++){
        cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);
    }
    a[1<<1].r=1<<1|1;
    a[1<<1|1].l=1<<1;
    dfs(1,0);
    for(int i=2;i<=(n<<1|1);i++){
        if(a[i].l==0){
		    sum=i;
			break;
		}
	}
    while(a[sum].r!=0){
        countt++;
        if(sum%2==1){
		    ans[sum>>1].r=countt;
		}
        else{
		    ans[sum>>1].l=countt;
		}
        sum=a[sum].r;
    }
    if(sum%2==1){
	    ans[sum>>1].r=countt+1;
	}
    else{
	    ans[sum>>1].l=countt+1;
	}
    for(int i=1;i<=n;i++){
    	cout<<ans[i].l<<" "<<ans[i].r<<"\n";
	}
    long long isejr=0;
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：MatrixGroup (赞：0)

来点奇怪做法。

## 题意

给定一棵 $n$ 个结点的树。

试构造 $n$ 条线段 $[l_i,r_i]$，它们的端点组成一个 $1\sim 2n$ 的排列，且这棵树上结点 $i$ 与结点 $j$ 间有边当且仅当 $[l_i,r_i]$ 与 $[l_j,r_j]$ 既不是包含关系也不是相离关系（换言之，$l_i<l_j<r_i<r_j$ 或 $l_j<l_i<r_j<r_i$）。

$n\le5\times10^5$。

## 

考虑增量法。假设我们填好了一部分，新加了一个叶子，应该怎么修改呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/3qtue0gz.png)

设其父亲是 $[l_i,r_i]$，则不难证明，填入 $[r_i-0.5,r_i+0.5]$ 可以满足区间的相对关系（因为在该区间内只有 $r_i$）。例如，在上面就可以填入 $[6.5,7.5]$。然后再离散化就可以满足整数的要求了。复杂度是 $O(n^2)$ 的，无法通过。

线段树似乎并不能像在 Cantor 展开里那样很好地维护答案。为了保证**相对顺序**，我们使用的数据结构应当为**链表**。用链表维护插入过程即可。

时间复杂度 $O(n)$。

---

## 作者：Qiaoqia (赞：0)

终于做出来了，我觉得我把构造不出来的想法都试了个遍（

首先这棵树可能是多叉，这就意味着你不可能通过把一个点和它的儿子通过不同的相交方式连在一起，即你不能对于一个儿子把它的右端点放在自己的区间里，而对另一个儿子则是左端点。所以必须是覆盖，比如对于简单的 $1 \to 2, 1 \to 3$ 的树得是 

![](https://s4.ax1x.com/2022/01/26/7qZSaQ.png)

那么如何再连上其它的子树呢？直接再把前面都盖掉是不行的，因为这样要把几个子树合并在一起的时候会使它和它的子子孙孙都连上边。而前面我们知道不能通过不同的方式相交，所以必须在前面那个子树的另一个方向继续加点并保证完全不交，即这样

![](https://s4.ax1x.com/2022/01/26/7quum6.png)

这样可以确保要么覆盖要么完全没有交。最后把最右边的（红色）连起来就是把子树合并了。

这样我们就有了一个大概的构造想法，可是如何去实现这样的一个想法呢？这也是这题很有趣的一个地方。我们并不能一下子通过一种顺序得出每条线段的左右端点，因为一个点的右端点要往右拓展是收到它子树的限制的，而它子树的左端点向左拓展上是受到它限制的，且有的情况下还要空出一个点来一边它的父亲连向它。

为了解决顺序不同的问题，可以先反向确定下来右端点，因为一个点直接相连的子节点的右端点是不需要递归就可以直接确定的。然后再设置一个全局变量作为左边的边界，在往下递归的时候根据是否需要预留一个节点（第一个子树需要）决定是否多拓宽一个左边界，再递归下去即可。最后把当前点的左端点放到下面预留出来的那个点上（儿子就多拓展一个）。

实现我使用了左闭右闭区间并通过返回值传递空出的节点。

```cpp
int dfs(int u, int fa, int rb, int op) {
    int an = 0;
    if (op) an = --rb;
    for (int i = (int)g[u].size()-1; i >= 0; i--) {
        int v = g[u][i];
        if (v == fa) continue;
        R[v] = --rb;
    }
    lb = rb;
    int flag = 0, sp = 0;
    for (int v : g[u]) if (v != fa) {
        if (!flag) sp = dfs(v, u, lb, 1), flag = 1;
        else dfs(v, u, lb, 0);
    }
    if (flag) L[u] = sp;
    else L[u] = --lb;
    return an;
}
void main() {
	std::cin >> n;
	for (int i = 1, x, y; i < n; i++) {
	    std::cin >> x >> y;
	    g[x].push_back(y), g[y].push_back(x);
	} 
	lb = 1;
	dfs(1, 0, 0, 0);
	int min = std::min(*std::min_element(L + 1, L + 1 + n),
	                   *std::min_element(R + 1, R + 1 + n));
	for (int i = 1; i <= n; i++)
	    L[i] -= min - 1, R[i] -= min - 1;
	for (int i = 1; i <= n; i++) std::cout << L[i] << ' ' << R[i] << '\n';
}
```

---

