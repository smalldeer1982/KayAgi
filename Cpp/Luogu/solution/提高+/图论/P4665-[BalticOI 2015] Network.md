# [BalticOI 2015] Network

## 题目描述

拜特朗政府已经决定，现在是时候将他们的小国家与互联网连接起来，以便所有公民都能参加节目比赛，观看可爱猫的视频。当是时候建设这个国家的网络骨干时，他们给互联网乐观主义者公司分配了连接所有N个拜特兰德的电脑。这些连接是作为计算机对之间的直接连接，使任何一对计算机都通过一系列的链接连接起来。

拜特朗是一个发展中国家，因此，为了将成本降到最低，网络拓扑是以树的形式构建的(即有N−1个计算机之间的直接连接)。为时已晚，人们意识到这一解决方案存在严重缺陷。如果只有一个链接断了，那么拜特兰德的计算机就会被分割，这样一些计算机就不能互相通信了！为了提高拜特朗网络的可靠性，人们决定至少要容忍单个链路中断。你的任务是帮助互联网乐观主义者公司以最便宜的方式改进网络。给出了拜特朗的网络拓扑(即N−1个计算机对是通过直接链接连接的)，找到需要添加的最少数量的链接，以便如果任何单个链接中断，网络仍将被连接。

## 样例 #1

### 输入

```
6
1 2
2 3
2 4
5 4
6 4```

### 输出

```
2
1 5
3 6```

# 题解

## 作者：Leasier (赞：8)

题意可以转化为：在一棵树上加尽量少的边，使得每条边至少在一个环中。

首先不难通过样例发现下面两个结论：

- Observation 1. $k = \lceil \frac{leaf}{2} \rceil$，其中 $leaf$ 表示叶子数。
- Observation 2. 最优方案中的所有 $a, b$ 一定均为叶子。

Observation 2 的证明：

我们显然可以将加一条边 $(u, v)$ 等效为：

- 让树上 $u, v$ 这条链上的所有边达成“至少在一个环中”的目标。

于是（下文假定我们随意钦定一个点为根且 $a$ 的深度小于 $b$）：

1. $a$ 为 $b$ 的祖先

首先，由于 $n \geq 3$，原树中不可能仅仅存在 $1$ 个叶子。

于是此时我们将 $b$ 替换为一个 $b$ 子树内的叶子、将 $a$ 替换为一个叶子 $a'$ 使得 $lca(a', b)$ 为 $a$ 的祖先。

2. $a$ 不为 $b$ 的祖先

此时可以达成目标的最浅点固定为 $lca(a, b)$。

于是我们把 $a, b$ 分别替换为其子树内的一个叶子即可。

Observation 1 的证明：

首先这玩意显然是答案下界——因为我们会尽量不重复地选叶子。

然后就是人类智慧的一步了——

- 我们把所有叶子抓出来，按 dfs 序升序排序，前一半与后一半的对应点配对，如果最后单出一个最大的就跟最小的配对。

那它为什么是对的？我们考虑一个非根节点 $u$。

1. $u$ 子树内叶子个数 $\leq \lfloor \frac{leaf}{2} \rfloor$

此时 $u \to fa_u$ 一定会达成目标，因为一定有从内向外的连边。

2. $u$ 子树内叶子个数 $> \lfloor \frac{leaf}{2} \rfloor$

显然此时 $u$ 子树内不会涵盖所有叶子，于是最小 / 最大之一总会向其中连边。

至此 Observation 1 得证。然后这道题就做完了。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int head[500007], deg[500007], rnk[500007], leaf[500007];
Edge edge[1000007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u, int father, int &id){
	rnk[++id] = u;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father) dfs(x, u, id);
	}
}

int main(){
	int n, id = 0, leaf_cnt = 0, half;
	scanf("%d", &n);
	for (int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		deg[a]++;
		deg[b]++;
		add_edge(a, b);
		add_edge(b, a);
	}
	dfs(1, 0, id);
	for (int i = 1; i <= n; i++){
		if (deg[rnk[i]] == 1) leaf[++leaf_cnt] = rnk[i];
	}
	half = leaf_cnt / 2;
	printf("%d\n", (leaf_cnt + 1) / 2);
	for (int i = 1; i <= half; i++){
		printf("%d %d\n", leaf[i], leaf[i + half]);
	}
	if (leaf_cnt % 2 != 0) printf("%d %d", leaf[1], leaf[leaf_cnt]);
	return 0;
}
```

---

## 作者：2344b (赞：8)

题意是让你连最少的边，使一颗树上的每一个点都被包括在某一个环上。

即使树上每个点被环覆盖。

### 先胡一个连叶子是最优情况的证明:

连两个点即可使这两点到其lca上的点被覆盖。

记连接的点为$x$,$y$。

1. 对于其中一个点是叶子(假设是$y$)

- 若$x$是$y$的祖先，此次连边可以覆盖$x$到$y$路径上的点。而连接$x$另一个子树中的点与$y$必能使$x$到$y$路径上的点被覆盖。

- 若$x$不是$y$的祖先，此次连边可以覆盖$x$,$y$到他们lca上的所有点。而连接$x$子树内的任意一点必能使$x$,$y$到他们lca上的所有点被覆盖。

2. 如果连接的不是叶节点。

- 若$y$在$x$子树中($x$在$y$子树中同理)。对于此次连边，必定不能覆盖到$y$子树中的点，而连接$y$子树内的任意一点与$x$必定能使$x$到$y$的路径被覆盖。

- 若$y$不在$x$的子树，那么此次连边之后，必定还需要若干次连边使$x$子树和$y$子树中的点被覆盖。而连接$x$子树或$y$子树中的任意一点，必能使点$x$,$y$被覆盖。

至此，可以知道连接两叶节点能覆盖的点包括不连叶节点的情况，且所有点都可以通过连接叶节点进行覆盖。所以连叶节点是一种最优情况。

### 再胡一个能完全覆盖叶节点的证明。

~~(这下标题行不长了吧。。)~~

连dfs序下第$i$个叶子和第$i+$ $\lceil$ $k/2$ $\rceil$个叶子就一定能覆盖所有点。(k为叶节点个数)

对于叶节点，只要连边就能覆盖。

对于其他点$x$，只要$x$子树内有叶节点连到其他子树，$x$和$fa[x]$就会被覆盖。

dfs序中，子树内叶节点连续。

记有一非叶节点$x$。

1. 若$x$中叶节点个数小于等于$\lceil$ $k/2$ $\rceil$。任意叶节点的连边都会连到非$x$子树内的点。

2. 若$x$中叶节点个数大于$\lceil$ $k/2$ $\rceil$。前$\lceil$ $k/2$ $\rceil$个叶节点会被dfs序小的非$x$子树内的叶节点连边。后$\lceil$ $k/2$ $\rceil$个叶节点会向dfs序大的非$x$子树内的叶节点连边。

至此，可以知道连dfs序下第$i$个叶子和第$i+$ $\lceil$ $k/2$ $\rceil$个叶子就一定能满足上述情况，即能完全覆盖所有点。

### 表述不是很清加上口胡的证明--感性理解吧。。。

### 代码就很简单了

注意要从度数不为1的点开始搜，如果没有，特判一下就好了。

```cpp
#include<bits/stdc++.h>
const int Mx=5e5+10;
int n,m,fir[Mx],nex[Mx<<1],to[Mx<<1],tot,de[Mx];
struct Edge{int x,y;}E[Mx];
void addEdge(int x,int y){
    nex[++tot]=fir[x];fir[x]=tot;to[tot]=y;de[x]++;
    nex[++tot]=fir[y];fir[y]=tot;to[tot]=x;de[y]++;
}
int rem[Mx],top;
void dfs(int x,int f){
    int flag=0;
    for(int i=fir[x];i;i=nex[i]){
        int v=to[i];
        if(v==f)continue;
        dfs(v,x);
        flag=1;
    }
    if(flag==0)rem[++top]=x;
}
int main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<n;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    int st=0;
    for(int i=1;i<=n;i++)if(de[i]>1){st=i;break;}
    if(st==0)return puts("1"),0;
    dfs(st,0);
    for(int i=1;i<=top/2;i++)E[++m]=(Edge){rem[i],rem[i+top/2]};
    if(top&1)E[++m]=(Edge){rem[1+top/2],rem[top]};
    printf("%d\n",m);
    for(int i=1;i<=m;i++)printf("%d %d\n",E[i].x,E[i].y);
}
```
~~还有两天就退役的我还在这边写博客。~~


---

## 作者：Algha_Porthos (赞：7)

这道题很明显，是要链接所有叶子结点。

然后看脸黑不黑。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int du[1050005],tot;
int a[1050005];
signed main(){
	srand(time(NULL));
	cin>>n;
	for(int i=1,x,y;i<=n-1;++i){
		scanf("%lld %lld",&x,&y);
		du[x]++;
		du[y]++;
	}
	for(int i=1;i<=n;++i){
		if(du[i]==1)
			tot++,a[tot]=i;
	}
	cout<<(tot+1)/2<<endl;
	random_shuffle(a+1,a+tot+1);
	random_shuffle(a+1,a+tot+1);
	random_shuffle(a+1,a+tot+1);
	for(int i=1;i<=tot/2;++i)
		printf("%lld %lld\n",a[i],a[tot-i+1]);
	if(tot%2==1)
		printf("%lld %lld\n",a[1],a[tot/2+1]);
}
```
暴力枚举过样例，random_shuffle出奇迹！

---

## 作者：hj23308 (赞：4)

[题目传送门](/problem/P4665)
### $ \mathcal{Problem} $ 
给定一颗 $ n $ 个节点的树，求至少加多少条边满足断掉任意一条边，图仍然联通。  

### $ \mathcal{Solution} $ 
原题可以转化为：选择尽可能少的点对路径，使得任意一条边至少被一条路径覆盖。  

不难发现**选择一对叶子节点不比其他点对劣**，因为任意一条路径均可以被一条由叶子节点构成的路径覆盖。  
设 $ k $ 为叶子节点的个数，考虑将叶子节点两两配对，这样答案的下界为 $ \lceil \dfrac k 2 \rceil $，分析如何达到这个下界。  

任选一个非叶子节点为根，将叶子节点按 dfs 序排列，若 $ k $ 为奇，拿出来一个最后随便连一个叶子。  
按顺序分为大小 $ \lfloor \dfrac k 2 \rfloor $ 的两组，**组与组之间按顺序两两配对**，即第 $i$ 个叶子和第 $ i + \lfloor \dfrac k 2 \rfloor $ 个叶子配对。

正确性证明：  
对于一个非根节点 $ u $，$ fa $ 为其父节点，其子树中有 $ x $ 个叶子节点，由 dfs 的性质，$ x $ 个叶子节点在序列中一定连续的，长度为 $ x $，考虑边 $ (u,fa) $：
- 若 $ x \le \lfloor \dfrac k 2 \rfloor $，**总会有一个叶子向“外”匹配**，覆盖边 $ (u,fa) $。  

- 若 $ x > \lfloor \dfrac k 2 \rfloor $，那么 $ k - x \le \lfloor \dfrac k 2 \rfloor $，同理**总会有一个叶子向“内”匹配**，覆盖边 $ (u,fa) $。

时间复杂度 $ O(n) $，空间复杂度 $ O(n) $。

### $ \mathcal{Code} $ 
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxN = 5e5 + 5;

int n, d[maxN];
vector<int> leaf, edge[maxN];

void dfs(int u, int prt) {
	if (d[u] == 1) leaf.push_back(u);
	for (auto v: edge[u])
		if (v != prt)
			dfs(v, u);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
  
	cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		edge[u].push_back(v), d[u]++;
		edge[v].push_back(u), d[v]++;
	}
	for (int i = 1; i <= n; i++)
		if (d[i] != 1) {
			dfs(i, 0);
			break;
		}
	n = (int)leaf.size();
	cout << ceil(n / 2.0);
	for (int i = 0; i < n / 2; i++)
		cout << '\n' << leaf[i] << ' ' << leaf[i + n / 2];
	if (n & 1) cout << '\n' << leaf[0] << ' ' << leaf[n - 1];

	return 0;
}
```

---

## 作者：MY（一名蒟蒻） (赞：4)

翻译好评。

[原题传送门](https://www.luogu.com.cn/problem/P4665)

## 题意简化
给定一颗 $\text{n}$ 个点的无根树，求最少加多少条边使形成的图任意删除一条边后都联通，边是无向的。
输出最少加边数和任意一种加边方案。

---
一道不错的构造题。

首先显然连接的边都是叶子肯定不会比其它方案要劣。

如果这个图是个环，那么断一条边就不会使此图不连通。所以选两个叶节点连接最优。这使得环上节点最多。

于是问题转换为选出尽量少的起点和终点都是叶子节点的路径覆盖完树上所有边。

这种题可以**尝试证明答案的上/下界**然后对着构造。这题假设叶子节点有 $\text{m}$ 个，显然答案不会小于  $\lceil \frac{m}{2} \rceil$ 。因为每个叶子都需要一条边来使其与父亲双联通。

考虑构造一个答案为 $\lceil \frac{m}{2} \rceil$ 的解。

---
假如我们选取了一个节点 $\text{x}$ 作为根，我们希望每个叶子都能和一个与它不属于同一棵（根节点儿子为根）子树的叶子匹配。

令 $a_k$ 表示其各个儿子节点子树内的叶子个数。我们相当于每次选择一组非零的 $a_i$ , $a_j$ 将它们都减 1，表示这两个子树内选择两个叶子匹配，执行到最后如果剩下了一个 1 就将其随便和一个**其它**子树的叶子匹配。

显然当最大的 $a_i$ 的两倍超过 $\sum{a_i}$ 时就不存在任何可行方案。那么我们就找一个类似“重心”的点（只不过是子树大小改为子树叶子个数）作为根，然后每次贪心地选取最大的一组 $a_i$, $a_j$ 去匹配，各自减 $1$ 放回去，直到无法执行就好了。

为什么这样一定能出解呢？考虑归纳证明，选取最大的 $a_i$, $a_j$ 都减 $1$ 塞回去，
$a_k$ 依然满足最大值两倍不超过总和。

然后边界情况两个 $1$ 是显然成立的。证毕。时间复杂度 $\text{O(nlogn)}$。

---
由于`dfs`的性质，我们搞出所有叶子节点后掐头掐尾即可完成匹配。即**每个叶子都能和一个与它不属于同一棵（根节点儿子为根）子树的叶子匹配。**

记得要选一个非叶节点作为根跑`dfs`。

可能大家听得云里雾里，放一下代码给大家参考吧。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N=5e5+10;

int n,fir[N],tot,du[N],leaf[N],cnt;
struct node {int to,nex;} e[N << 1];

void add(int u,int v)
{
	e[++tot].to=v;
	e[tot].nex=fir[u];
	fir[u]=tot; du[v]++;
	return ;
}

void dfs(int x,int dad)
{
	bool f=true;
	for(int i=fir[x];i;i=e[i].nex)
		if(e[i].to^dad) {f=false; dfs(e[i].to,x);}
	if(f) leaf[++cnt]=x;
	return ;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	int root=0;
	for(int i=1;i<=n && !root;i++) if(du[i] > 1) root=i;
	if(!root) return printf("1"),0;//边界
	dfs(root,0);
	printf("%d\n",(cnt+1)>>1);
	for(int i=1;i<=cnt>>1;i++) printf("%d %d\n",leaf[i],leaf[i+(cnt>>1)]);
	if(cnt&1) printf("%d %d",leaf[(cnt>>1)+1],leaf[cnt]);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
感谢阅读！您的点赞和评论是对作者最大的支持!

---

## 作者：白鲟 (赞：2)

### 前言
大概思路会流畅些。

### 题意简述
在一棵树上选择若干无边的两点连边，使得删去任意一条边后图仍连通。

### 分析
给两点连边后，删去两点路径上的边不再影响连通性。于是问题等价于覆盖若干点对间路径，使得每条树边至少被覆盖一次。

由于与叶结点相连的边只能被叶结点覆盖，故每个叶结点至少需连一条边。设共有 $k$ 个叶结点，考虑将叶结点两两连边即为答案下界 $\lceil\dfrac{k}{2}\rceil$。

考虑是否能构造出满足答案下界的合法方案。考虑固定一个非叶结点为根，发现若每条边连接的两叶结点均不在根结点的同一棵子树中，则根到每个叶结点的路径都被覆盖，这与每条边均被覆盖等价。

一个朴素的贪心想法是在获得 dfs 序中访问每个叶结点的顺序后，使得连边的两个叶结点在该顺序中距离最小值尽量大，即将第 $i$ 个访问的叶结点与第 $i+\lfloor\dfrac{k}{2}\rfloor$ 个访问的叶结点连边。

事实上这一贪心策略是正确的（可以在其它题解找到论述）——但不够显然。但若这棵树满足根结点的子树中叶结点个数均不超过 $\lfloor\dfrac{k}{2}\rfloor$，策略便显然正确了。考虑是否能够找到一个这样的根结点，发现该点性质事实上与树的重心极其类似。于是模仿树的重心的平移法，可知满足条件的点是存在的，且使用求出子树叶结点数最大值最小的点的的方法即可求出。

当叶结点个数为奇数时，最后访问的叶结点将无连边。此时将其与最先访问的叶结点连边即可。

时间复杂度为 $\operatorname{O}(n)$。

### 代码
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(int i=(from);i<=(to);++i)
using namespace std;
const int maxn=5e5;
int n,x,y,g,leaves,size[maxn+1],maxsize[maxn+1],order[maxn+1];
vector<int> edge[maxn+1];
void dfs1(int now,int parent){
	size[now]=(edge[now].size()==1);
	for(auto to:edge[now])if(to!=parent)dfs1(to,now),size[now]+=size[to],maxsize[now]=max(maxsize[now],size[to]);
	maxsize[now]=max(maxsize[now],leaves-size[now]);
	if(maxsize[now]<maxsize[g]&&edge[now].size()!=1)g=now;
	return;
}
void dfs2(int now,int parent){
	if(edge[now].size()==1)order[++order[0]]=now;
	for(auto to:edge[now])if(to!=parent)dfs2(to,now);
	return;
}
int main(){
	scanf("%d",&n);
	loop(i,1,n-1)scanf("%d%d",&x,&y),edge[x].push_back(y),edge[y].push_back(x);
	loop(i,1,n)leaves+=(edge[i].size()==1);
	maxsize[0]=n,dfs1(1,0),dfs2(g,0);
	printf("%d\n",(leaves+1)/2);
	loop(i,1,leaves/2)printf("%d %d\n",order[i],order[i+leaves/2]);
	if(leaves&1)printf("%d %d\n",order[1],order[leaves]);
	return 0;
}
```

---

## 作者：良月澪二 (赞：2)

黑的还行

### 题意：在一棵树内新建最少的边使得任意切掉一条边后图（加边之后的树）仍然是联通的

叶节点被切掉相邻的那条边之后一定就出这个联通块了

所以dfs找到所有的叶节点记下来，为cnt

要输出加的边数，即cnt-cnt/2

然后挑两个点输出来就可以

最后特判一下奇偶的情况

------------

前向星，要比我的vector快四倍多：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <vector>
#define A 1000010

using namespace std;
typedef long long ll;
struct node {
	int next, to;
}e[A];
int head[A], num;
void add(int fr, int to) {
	e[++num].next = head[fr];
	e[num].to = to;
	head[fr] = num;
}
int n, m, cnt, f[A], fa[A], x, y, in[A];
void dfs(int fr) {
	if (in[fr] == 1) f[++cnt] = fr;
	for (int i = head[fr]; i; i = e[i].next) {
		int ca = e[i].to;
		if (ca == fa[fr]) continue;
		fa[ca] = fr;
		dfs(ca);
	}
}

int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
		in[x]++, in[y]++;
	}
	for (int i = 1; i <= n; i++)
		if (in[i]) {
			dfs(i);
			break;
		}
	printf("%d\n", cnt - cnt / 2);
	for (int i = 1; i <= cnt / 2; i++)
		if (f[i] < f[i + cnt / 2]) printf("%d %d\n", f[i], f[i + cnt / 2]);
		else printf("%d %d\n", f[i + cnt / 2], f[i]);
	if (cnt & 1) printf("%d %d\n", f[cnt / 2], f[cnt]);
}
```
$vector$:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <vector>
#define A 1000010

using namespace std;
typedef long long ll;
vector<int> v[A];
int n, m, cnt, f[A], x, y, fa[A];
void dfs(int fr) {
	if (v[fr].size() == 1) f[++cnt] = fr;
	for (int i = 0; i < v[fr].size(); i++) {
		int ca = v[fr][i];
		if (ca == fa[fr]) continue;
		fa[ca] = fr;
		dfs(ca);
	}
}

int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (v[i].size()) {
			dfs(i);
			break;
		}
	printf("%d\n",cnt - cnt / 2);
	for (int i = 1; i <= cnt / 2;i++) printf("%d %d\n", f[i], f[i + cnt / 2]);
	if (cnt & 1) printf("%d %d\n", f[cnt / 2], f[cnt]);
	return 0;
}
```

---

## 作者：VenusM1nT (赞：1)

$\text{Dfs}$。黑掉紫确实挺让人唏嘘的【笑】，不过这题也确实挺简单的……找到所有叶子节点，也就是度为 $1$ 的点，把它们连起来就行了……

因为要保证相邻的连上，跑一遍 $\text{Dfs}$ 即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1];
int n,ans[MAXN],tot,deg[MAXN];
void AddEdge(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs(int u,int faz)
{
	if(deg[u]==1) ans[++tot]=u;
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz) continue;
		Dfs(v,u);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
		deg[x]++;
		deg[y]++;
	}
	Dfs(1,0);
	printf("%d\n",tot-tot/2);
	for(int i=1;i<=tot/2;i++)
	{
		if(ans[i]>=ans[i+tot/2]) swap(ans[i],ans[i+tot/2]);
		printf("%d %d\n",ans[i],ans[i+tot/2]);
	}
	if(tot&1) printf("%d %d\n",ans[tot/2],ans[tot]);
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

首先有一个关键性质是说给出这个树之后连叶子结点一定最优。因此记录下每一个度数为 $1$ 的点，并将其两两匹配。因为这样匹配成功的概率非常大，因此直接 random_shuffle 所有叶子即可。有概率能过。

当然正确做法是说维护两个指针 $p_1$ 和 $p_2$ 分别位于叶子结点数组的左侧和中间，然后往右滑动，维护加边。叶子结点之间按照 dfn 序从小到大排序。直接写一个 dfs，时间复杂度为 $O(n)$。

---

## 作者：qzmoot (赞：0)

# 题目大意
给你一个树，让你加最少的边使得这个树全都由环构成。
# 题目思路
这里给一个很新奇的思路，缩点。你肯定会问，你怎么缩点啊？题目没给你环啊之类的。

但是不用慌，我们先预处理出所有的叶子节点，放进一个序列中，每次将其中的两个点进行连边，之后进行缩点，一直到最后只有 1 个点为止。

注意，这个地方我们的点只能链接不在自己子树内的点，否则你这个环不是最优的。

然后因为我们是动态连点的，所以我们需要存下来我们的所有答案，最后一起输出。

正确性是怎么满足的呢？我们肯定是构造的环越大越好，我们只要不连接在自己子树内的点，我们构成的环有一部分是这个树的一条链，且通过了所有的子树。

我们便可以得出了结论，$i$ 进行连接 $i+\lfloor\displaystyle \frac{k}{2}\rfloor$，$k$ 是叶子节点的总个数。

然后你就可以用这个结论写了，我只是用了缩点的思想来进行推导而已，没说非要用缩点写哦。

相信在座的各位都知道欧拉图吧，那就肯定知道 $0$ 是什么时候输出吧？那就直接上代码！
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=500005;
int n,deg[N],ans,xl[N],idx;
vector<int>a[N];
void dfs(int u,int fa)
{
	if(deg[u]==1)
	{
		xl[++idx]=u;
		return;
	}
	for(int v:a[u])
	{
		if(v==fa)
			continue;
		dfs(v,u);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		a[u].push_back(v);
		a[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]!=1)
		{
			dfs(i,0);
			break;
		}
	if(idx%2==0)
		printf("%d\n",idx/2);
	else
		printf("%d\n",idx/2+1);
	for(int i=1;i<=idx/2;i++)
		printf("%d %d\n",xl[i],xl[i+idx/2]);
	if(idx%2==1)
		printf("%d %d",xl[1],xl[idx]);
	return 0;
}
```
看到这了就点个赞吧！

---

## 作者：do_while_true (赞：0)

以任意非叶节点为根求 dfs 树，设叶子节点为 $k$，答案的下界是 $\left\lceil\frac{k}{2}\right\rceil$，现在给出一组构造方案证明这个下界可以达到。

把叶子节点按照 dfn 排序，然后第 $i$ 个叶子连向第 $i+k/2$ 个叶子。

如果每条边都在一个环里，那么这个图没有割边，如果根节点的子树包含的叶子节点都 $<k/2$，那么每个叶子都能和另外一个子树的叶子匹配，显然每条边都会被覆盖到。

如果存在一个子树 $>k/2$，那么没有和子树外的点匹配的只有这个子树内的叶子，单独考虑这棵子树，一定是前若干个叶子和后若干个叶子匹配，如果它们不在这个子树的一棵子树内，就合法了，否则还会存在一个更下一层的子树，前若干个叶子和后若干个叶子匹配。如此递归下去，到了最底层的时候显然合法。

所以整个构造方案是合法的。

---

