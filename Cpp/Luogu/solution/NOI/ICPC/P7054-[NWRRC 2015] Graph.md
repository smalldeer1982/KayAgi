# [NWRRC 2015] Graph

## 题目描述

序列 $a_{1}, a_{2}, \ldots, a_{n}$ 被称为一个排列，如果它包含从 $1$ 到 $n$ 的每一个整数。

如果顶点的排列 $a_{1}, a_{2}, \ldots, a_{n}$ 是一个有向图的拓扑排序，那么对于每一条从 $u$ 到 $v$ 的有向边，顶点 $u$ 在这个排列中出现在 $v$ 之前。

排列 $a_{1}, a_{2}, \ldots, a_{n}$ 在字典序上小于排列 $b_{1}, b_{2}, \ldots, b_{n}$，如果存在某个 $m$ 使得对于每一个 $1 \le i < m$，都有 $a_{i} = b_{i}$，并且 $a_{m} < b_{m}$。

给定一个有向无环图，最多添加 $k$ 条有向边，使得结果图仍然没有环，并且图的字典序最小的拓扑排序尽可能大。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 3 2
1 4
4 2
1 3
```

### 输出

```
5 1 4 2 3
2
4 3
5 1
```

## 样例 #2

### 输入

```
2 2 20
1 2
1 2
```

### 输出

```
1 2
1
1 2
```

# 题解

## 作者：x义x (赞：11)

> **题意.**
>
> 给定一张 $n$ 点 $m$ 条边的 DAG，你可以至多添加 $k$ 条有向边，使得这仍然是一个 DAG，使得字典序最小的拓扑序的字典序尽量大。
>
> 输出这个拓扑序以及方案。
>
> $n,m,k\le 10^5$。

啊又是开门一个 key obeservation 的题。

> **引理.**
>
> 若最终拓扑序为 $p$，那么存在一种最优方案满足所有加的边都形如 $p_i\Rightarrow p_{i+1}$。

> **证明.**
>
> 否则，我们总是可以把 $p_{i}\Rightarrow p_j$ 替换为 $p_{i+1}\Rightarrow p_j$。说明如下。
>
> 设替换后的新排列为 $q$。
>
> - 显然 $p_1=q_1,...,p_i=q_i$。这部分的拓扑排序完全和这条边没关系。
> - 又可以发现 $q_{i+1}\neq p_j$，因为此时仍存在 $p_{i+1}\Rightarrow p_j$。其他点的情况和该边换不换没关系，所以 $q_{i+1}=p_{i+1}$。
> - 如果再往后，那所有点的情况都和该边换不换没关系。

现在我们逐位确定 $p$。如果 $k=0$，那自然是没戏唱了，直接开始拓扑排序即可。

否则，

> 现在将所有入度为 $0$ 的节点取出，考虑其中的最小者 $u$：
>
> - 如果 $u$ 并非唯一的入度为 $0$ 元素，那我们肯定不希望 $u$ 当上当前位置，所以我们希望临时**加一条边**把 $u$ 放到后面去（让它的度数不为 $0$）。
> - - $k\leftarrow k-1$；显然这条边连肯定是能连的（$u$ 并非唯一的入度为 $0$ 元素）；至于这条边到底和谁连，我们**暂时不关心**。到时候只需要在求出 $p$ 之后根据上面的引理编出所需的边即可。
> - 如果 $u$ 就是唯一的入度为 $0$ 元素，那么只好把 $u$ 作为当前位置，删去 $u$。

听起来十分美好，但这个过程是**明显有问题的**。这个问题体现在最后【删去 $u$】处：我们没有考虑 $u$ 可能连出了一些**新加边**，自然也就没有更新目标节点的度，它们就永远入度为 $1$ 了！

所以我们应当维护两个集合：

- 所有【明显是入度为 $0$】的节点；
- 和所有【因为被一条**新加边**连入而可能现在是入度为 $0$】的节点。

顺便，我们指出，对于这些【可能是入度为 $0$】的节点，我们在任何时刻钦定它入度为 $0$ 都是合法的：显然只要我们不认为它入度为 $0$，它的后继节点们就不可能被处理，从而不会连出环。

下面是修正后的流程。

> 现在将所有入度为 $0$ 的节点取出，考虑其中的最小者 $u$：
>
> - 如果 $u$ 并非唯一的入度为 $0$ 元素，那我们肯定不希望 $u$ 当上当前位置，所以我们希望临时**加一条边**把 $u$ 放到后面去（让它的度数不为 $0$）。
> - - $k\leftarrow k-1$；显然这条边连肯定是能连的（$u$ 并非唯一的入度为 $0$ 元素）；至于这条边到底和谁连，我们**暂时不关心**。到时候只需要在求出 $p$ 之后根据上面的引理编出所需的边即可。
> - 如果 $u$ 就是唯一的入度为 $0$ 元素：
> - - 那么我们应当把【可能是入度为 $0$】的节点中的最大者取出替换掉 $u$。（当然，如果它比 $u$ 小那还不如不换，还是把认定 $u$ 就是当前位置并删除吧）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int n, K, k;
vector<int> G[maxn];
int deg[maxn];

priority_queue<int, vector<int>, greater<int> > U;
priority_queue<int> V;

void del(int u) {
    for (int v : G[u])
        if (!(--deg[v])) U.push(v);
}
int p[maxn], tot;
bool qaq[maxn];

int main() {
    int m;
    scanf("%d%d%d", &n, &m, &K);
    while (m--) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        deg[v]++;
    }
    for (int i = 1; i <= n; i++) if (deg[i] == 0) U.push(i);
    while (tot != n) {
        if (U.empty()) {
            int u = V.top(); V.pop();
            del(u); p[++tot] = u; continue;
        }
        int u = U.top(); U.pop();
        if (k == K) { del(u); p[++tot] = u; continue; }
        if (!U.empty()) {
            k++;
            qaq[u] = 1;
            V.push(u);
            continue;
        }
        if (V.empty()) { del(u); p[++tot] = u; continue; }
        int v = V.top();
        if (v < u) { del(u); p[++tot] = u; continue; }
        V.pop(), V.push(u), U.push(v), qaq[u] = 1, k++;
    }
    for (int i = 1; i <= n; i++) printf("%d ", p[i]); printf("\n");
    printf("%d\n", k);
    for (int i = 2; i <= n; i++) if (qaq[p[i]]) printf("%d %d\n", p[i - 1], p[i]);
}
```

---

## 作者：cwxcplh (赞：7)

虽然是道黑题，但不得不说：确实简单（相对于其他黑题而言，当然我不是说我做过黑题啊）。

**前言：** 最初看到是道黑题感觉特别难，一看题解就才五篇，理解了很久的题解，终于是想明白了，但题解说的都有点隐晦，于是产生了这篇题解。

题目简化：通过增加至多 $k$ 条边使得这个有向无环图的拓扑序的最小字典序最大。

首先让我们回忆一下拓扑排序的过程：

1. 将这个点出队，并加入拓扑数组中。

2. 遍历这个点的所有出度。

3. 将其出度点的入度数量减少一。

4. 如果其出度点入度为 $0$，入队。

所以一个有向无环图的拓扑序有很多种，而我们要找字典序最小的那种，所以我们只需要把这个队列换成小根堆就行了。

现在我们真正要做的是添加 $k$ 条边使得这个拓扑序的字典序尽可能的大。也就是说我们要让越大的数越往前靠，这样就能保证字典序尽可能的大了。

由上，我们可以这么思考：我们先设一个小根堆 $q$ 用来进行拓扑排序，再设一个大根堆 $p$ 用来记录可以拿来与这个图上的入度为 $0$ 的点连边的点，然后分类讨论。

先用文字描述一下：我们可以尝试将 $q$ 中的元素放入 $p$ 中，如果 $q$ 中只剩下一个元素了，就没有必要再浪费连边机会去连边，否则就一直放入元素并使 $k$ 一直减 $1$，直到 $k=0$ 或者 $q$ 为空就停止。

操作完后如果 $q$ 中还有元素，那就把当前拓扑序的最优解的第 $i$ 个设为 $q$ 中的第一个，否则就把第 $i$ 个设为 $p$ 中的第一个并且与上个最优解连边，最后把当前最优解计入答案并把与它所连的点的入度减 $1$。

相信很多人看完都是懵的：为什么要把 $q$ 中的放入 $p$？为什么 $q$ 中还有元素 $q$ 的第一个元素就是最优解？为什么 $q$ 或 $p$ 中的第一个元素就是当前最优解？那我在这里就用图示的方法解释一下。

我们来考虑这么一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gwlxbh7w.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

其中 $5$ 号点和 $6$ 号点是单独的两个点，左边是一个十分完美的有向无环图。

首先，像我上面说的：我们要让字典序最大，就要让开头的数字尽可能的大，这个图中 $6$ 是最大的点，而且可以用来连其他的点。

最初，我们因为要做拓扑排序，所以 $1,5,6$ 号点会最先被推入小根堆（我们要求字典序最小的拓扑序），那么这几个点就彻底和其他点断绝关系了（不是真正的断绝关系，即不是与这个点相连的点的入度减 $1$），但是它们成了单独的点就可以用来与其他点连接，于是就把它们推入了 $p$ 这个大根堆（让越靠前的数越大），这就是为什么要尝试将 $q$ 中的数放入 $p$ 中。

接着，当我们做完拓扑后，如果 $q$ 里还有数，说明还有一些入度为 $0$ 的点，那这些点就只能先成为当前的解，如果没了，就可以开始连边了，只需要将上一个最优解与当前最优解（$p$ 中的第一个数）连起来，然后再记录进答案，最后彻底断绝这个点与与它相连的点的关系（入度减 $1$）。

最后重复以上操作，直到 $n$ 个点都被算过就行了。

[提交记录，完美 AC](https://www.luogu.com.cn/record/199766305)

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x,y,rd[100006],sx[100006];
priority_queue<int>p;
priority_queue<int,vector<int>,greater<int>>q;
vector<pair<int,int>>v;
vector<int>edge[100006];
signed main() {
	cin>>n>>m>>k;
	for(int i=1; i<=m; i++) {
		cin>>x>>y;
		edge[x].emplace_back(y);
		rd[y]++;
	}
	for(int i=1; i<=n; i++) {
		if(!rd[i]) {
			q.emplace(i);
		}
	}
	int a,b;
	for(int i=1; i<=n; i++) {
		while(!q.empty()&&k) {
			int x=q.top(),y=-1;
			if(!p.empty()) {
				y=p.top();
			}
			if(x>y&&q.size()==1) {
				break;
			}
			q.pop();
			p.emplace(x);
			k--;
		}
		if(!q.empty()) {
			b=q.top();
			q.pop();
		} else {
			b=p.top();
			p.pop();
			v.emplace_back(make_pair(a,b));
		}
		sx[i]=b;
		for(auto j:edge[b]) {
			rd[j]--;
			if(!rd[j]) {
				q.emplace(j);
			}
		}
		a=b;
	}
	for(int i=1; i<=n; i++) {
		cout<<sx[i]<<" ";
	}
	cout<<endl<<v.size()<<endl;
	for(auto i:v) {
		cout<<i.first<<" "<<i.second<<endl;
	}
	return 0;
}
```

---

## 作者：DeepSeaSpray (赞：5)

首先最小拓扑序可以在拓扑排序的基础上将队列改成小根堆求出。

如何使得最小拓扑序变大？

我们在拓扑排序的某一时刻，此时当前所有入度为 $0$ 的点处于小根堆中。

对于编号最小的点，我们即将删掉它。

此时我们可以给这个点增加一条入边，使得其入度变成 $1$。

这样我们就增大了拓扑序。

所以我们可以贪心的考虑，对于每一个即将被删掉的点，我们都为它新增一条入边，这样显然是最优的。

问题在于这一条入边的起点在那里，我们发现起点为其拓扑序中的上一个即可，这样可以确保它一定出现在它当前拓扑序位置中。

那么他的拓扑序位置在哪里呢？其实可以由我们随意指定。

但需要注意的是你仍需保证其在这一时刻最小（因为实际上我们只是令它在这一时刻入度为 $0$）。

那么我们再把这样的点用大根堆存储起来，在需要的位置插入即可。

具体来说，算法流程如下：

初始化：将入度为 $0$ 的点放入小根堆中。

- 小根堆大小大于 $1$
  - 若 $K > 0$：为当前堆顶添加入边（打标记并放入大根堆中）
  - 否则：删掉堆顶（与普通拓扑序相同）
- 小根堆大小等于 $1$
  - 若 $K > 0$ 且大根堆不为空且大根堆堆顶更大：为当前堆顶添加入边，删掉大根堆堆顶
  - 否则：删掉堆顶
- 小根堆大小等于 $0$
  - 删掉大根堆堆顶

最后，打过标记的点和它在拓扑序列前一个点连边即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define P pair<int,int>
const int maxn=1e5;
int n,m,K;
vector<int> E[maxn+5];
int dg[maxn+5];
int ans[maxn+5],anst;
P ae[maxn+5];int aet;
bool flg[maxn+5];
priority_queue<int,vector<int>,greater<int>> q;
priority_queue<int,vector<int>,less<int>> p;
inline void Insert(int u){K--,flg[u]=1,p.push(u);}
inline void Delete(int u){
    ans[++anst]=u;
    if(flg[u]) ae[++aet]=P(ans[anst-1],ans[anst]);
    for(int v:E[u]) if(!(--dg[v])) q.push(v);
}
signed main(){
    int u,v;
    scanf("%d%d%d",&n,&m,&K);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        E[u].emplace_back(v);
        dg[v]++;
    }
    for(int i=1;i<=n;i++) if(!dg[i]) q.push(i);
    while(q.size()||p.size()){
        if(q.size()==0) u=p.top(),p.pop(),Delete(u);
        else if(q.size()==1){
            if(K&&p.size()&&q.top()<p.top()){
                u=q.top(),q.pop(),Insert(u);
                u=p.top(),p.pop(),Delete(u);
            }
            else u=q.top(),q.pop(),Delete(u);
        }
        else{
            if(K) u=q.top(),q.pop(),Insert(u);
            else u=q.top(),q.pop(),Delete(u);
        }
    }
    for(int i=1;i<=anst;i++) printf("%d ",ans[i]);
    putchar('\n');
    printf("%d\n",aet);
    for(int i=1;i<=aet;i++)
        printf("%d %d\n",ae[i].first,ae[i].second);
    return 0;
}
```

---

## 作者：DengDuck (赞：4)

其实这题的想法特别简单，也许大家有点讲复杂了？

简单来说，我们的想法是贪心地使第一位最大，然后在这个前提下保证第二位最大，如此类推。

所以对于当前入度为 $0$ 的点，假如有多个，那么我肯定希望给比较小的点加一个连向它的边，这样就只能选大一点的点了。

问题是谁来连呢？我们发现连向我们的点甚至可以不是当前入度为 $0$ 的点，所以考虑起来是很复杂的事情。

所以这里有个很聪明的做法是摆烂先不考虑，我们直接用个大根堆来存这些要连边的点，等什么时候我要去到这些点的时候，我让已经拓扑的上一个点向它连边就行。

于是我们直接做拓扑，同时跑贪心就可以了。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e5+5;
int n,m,k,D[N];
vector<int>E[N];
priority_queue<int,vector<int>,greater<int> >Q;
priority_queue<int>P;
struct Edge{int u,v;};
vector<Edge>Ans;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		E[u].pb(v),D[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(!D[i])Q.push(i);
	}
	int Lst=0;
	while(!P.empty()||!Q.empty())
	{
		while(!Q.empty()&&k)
		{
			int x=Q.top(),y=0;
			if(!P.empty())y=P.top();
			if(x>y&&Q.size()==1)break;
			Q.pop(),P.push(x),k--;
		}
		int x;
		if(!Q.empty())x=Q.top(),Q.pop();
		else
		{
			x=P.top(),P.pop();
			if(Lst)Ans.pb({Lst,x});
		}
		printf("%d ",x);
		for(int i:E[x])
		{
			D[i]--;
			if(!D[i])Q.push(i);
		}
		Lst=x;
	}
	putchar('\n');
	printf("%d\n",Ans.size());
	for(Edge i:Ans)
	{
		cout<<i.u<<' '<<i.v<<endl;
	}
}
```

---

## 作者：Mirasycle (赞：2)

开两个堆，一个小根堆和一个大根堆。小根堆维护字典序最小的拓扑序，大根堆维护决策。

小根堆内部存的的是入度为 $0$ 的点，每次取出小根堆中的堆顶，为了最大化这个点，我们需要给它一个入度使得其无法在本次被选择，但是由哪个点连向这个点需要进行考虑，直接做很难。我们就暂时搁置这件事，直接把这个点放入大根堆中表示待决策。需要这个点的时候，直接令拓扑序比它小 $1$ 的点向它连边即可，这样子就可以直接取出这个点了。大根堆保证了最大化这个条件。

时间复杂度 $O(n\log n)$。

---

## 作者：岸芷汀兰 (赞：2)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P7054)

[codeforces原题](https://codeforces.com/gym/100801)

# 二、思路：

一道史诗级的思维题。

首先我们来考虑，如果没有加边操作，怎么才能求出来字典序最小的拓扑序，无非就是将普通拓扑排序中的队列换成小根堆。

再来考虑加边操作。对于当前小根堆中保存的入度为 0 的点，我们肯定想加一些**指向它们的边**从而不让它们出现在这一位；反过来，我们又想在这一位放入尽可能大的点。所以可以有以下算法：

维护一个大根堆 $q$ 和一个小根堆 $p$。$p$ 维护的是当前所有入度为 0 的点，$q$ 中维护的是已经确定要连一条**指向它们的边**的那些点。设 $a$ 为最优拓扑序的上一位，$b$ 为最优拓扑序的当前位（等待被求解）。

尝试将 $p$ 中的元素加入到 $q$ 中。如果 $p$ 中只有一个元素且该元素还比 $q$ 的堆顶大，那么就可以不用浪费一次加边的机会，直接将该点确定为 $b$。否则的话，依次将 $p$ 中的元素插入到 $q$ 并让 $k\gets k-1$，直到 $p$ 变空或者 $k$ 变成 $0$。

操作完一轮后，如果 $p$ 中还有元素，说明我们不得不将 $p$ 的堆顶作为 $b$。否则就可以将 $q$ 的堆顶作为 $b$，并连一条新边 $(a,b)$。

最后，令 $b$ 的后继的入度自减 1。要是减为 0，就加入到 $p$ 中。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXN = 100005;

int n, m, K;
int in[MAXN], ans[MAXN];

vector<int>linker[MAXN];
vector<pair<int, int> >add;

priority_queue<int, vector<int>, greater<int> >p;
priority_queue<int>q;

int main() {
    FILEIN("graph.in"); FILEOUT("graph.out");
    n = read(); m = read(); K = read();
    for (int i = 1; i <= m; ++ i) {
        int x = read(), y = read();
        linker[x].push_back(y);
        ++ in[y];
    }
    for (int i = 1; i <= n; ++ i) {
        if (!in[i]) p.push(i);
    }
    int a, b;
    for (int i = 1; i <= n; ++ i) {
        while (!p.empty() && K > 0) {
            int y = -1, x = p.top();
            if (q.size()) y = q.top();
            if (x > y && p.size() == 1) break;
            p.pop(); q.push(x); -- K;
        }
        if (!p.empty()) {
            b = p.top(); p.pop();
        }
        else {
            b = q.top(); q.pop();
            add.push_back({ a, b });
        }
        ans[i] = b;
        for (auto &y : linker[b]) {
            -- in[y];
            if (!in[y]) p.push(y);
        }
        a = b;
    }
    for (int i = 1; i <= n; ++ i) printf("%d ", ans[i]);
    puts("");
    printf("%d\n", (int)add.size());
    for (auto &p : add)
        printf("%d %d\n", p.first, p.second);
    return 0;
}
```



---

## 作者：IGpig (赞：2)

## 题解：P7054 [NWRRC2015] Graph
观察题目，我们要让**字典序最小**，就是要让第一位最小，然后第二位，以此类推，则可以想到贪心。\
连 $k$ 条边，就是要在拓扑排序中有 $k$ 步可以选择，且每一步找一个小一点的点来连。那么这个点怎么连呢？
这里参考了 @DengDuck 大佬的思路，直接把所有这样的点用一个大根堆存起来，在拓扑的过程中取出来用。\
同时，要字典序最小，需要把拓扑排序的队列换成小根堆，并且记录路径。

**注意：如果你的代码没过样例不着急**\
不要忘了有 
```special judge```，对于第一组样例，这个输出是可以的（~~被耽误了很久~~）：

```
5 1 4 2 3
2
5 1
2 3
```
### Code

```
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
using LL=long long;
LL n,m,in[500005],k,tmp[500005],cnt;
vector<LL> v[500005],order;
priority_queue<LL,vector<LL>,greater<LL> > q;
priority_queue<LL,vector<LL>,less<LL> > p;
vector<pair<LL,LL> > res;
void topsort(){
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
    while((q.size()+p.size())){
        cnt++;tmp[cnt]=tmp[cnt-1];
        while(min(k,LL(q.size()))){
            if(q.top()>(!p.empty() ? p.top() : 0)&&q.size()==1) break;
            p.push(q.top()),q.pop(),k--;
        }
        if(!q.empty()){
            tmp[cnt]=q.top(),q.pop();
        } else{
            tmp[cnt]=p.top(),p.pop();
            if(tmp[cnt-1]) res.push_back({tmp[cnt-1],tmp[cnt]});
        }
        for(auto i : v[tmp[cnt]]){
            in[i]--;
            if(!in[i]) q.push(i);
        }
        order.push_back(tmp[cnt]);
    }
    return ;
}
int main(){
    cin>>n>>m>>k;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        v[x].push_back(y);
        in[y]++;
    }
    topsort();
    for(auto i : order){
        cout<<i<<' ';
    }
    cout<<endl;
    cout<<res.size()<<endl;
    for(auto i : res){
        cout<<i.first<<' '<<i.second<<endl;
    }
    return 0;
}
```

---

## 作者：Lonelyhacker (赞：1)

学校模拟赛碰见的，写此篇题解梳理思路以加深印象。

## 题意

给你 $n$ 个点和 $m$ 条有向边，构成一个有向无环图。同时给你 $k$ 次添加一条有向边的机会，使得新图仍是一个有向无环图的同时，要求使得新图的拓扑序字典序最小的同时最大。输出最终新图字典序最小的拓扑序及新边所连接的两个点的编号。

$1 \le n \le 10^5$，$0 \le m, k \le 10^5$。

## 题解

#### Part 1: 使拓扑结果字典序最小

拓扑的过程如下：

1. 找出所有入度为 $0$ 的点，加入拓扑序列（通常是队列）中。
2. 选中一个点，使与之相连的点的入度减一。
3. 若入度为 $0$，则加入拓扑序列中。
4. 重复上述步骤，直到队列为空。

若有一些点的入度始终不能为 $0$，说明有环，使得它们不能被加入进队列中。

由此可见，一个图的拓扑序有很多。如果我们要求最小字典序的拓扑序，只需要把上述拓扑序列的数据结构由队列改为优先队列（即小根堆）即可。这样，一个图的字典序最小的拓扑序我们就可以求出。

#### Part 2: 使字典序最小的结果最大

看拓扑的过程，首先是需要加入入度为 $0$ 的点。因此我们可以动动手脚，使得原本应该入度为 $0$ 的点因我们的连边而不为 $0$，导致第一个该遍历的点不是原来的点，再用一些较大的点去连，这样就实现这个效果了。

为了要求最后结果的字典序最大，我们可以用另一个大根堆来维护可用来连边的点的集合。这里假设用于拓扑的小根堆为 $tp$，用于优选的大根堆为 $q$。注意，$q$ 中的点来源于 $tp$，说明 $q$ 中的点的入度也是为 $0$ 的。记住，如果进入了 $q$，说明里面的点**一定会消耗一次连有向边的机会**，至于是和谁连边就看情况另说了。

#### Part 3: 过程实现

为了使结果最优，我们肯定会贪心地将 $tp$ 堆顶的点取出，放在 $q$ 堆内，用 $q$ 堆顶的点作为下一个遍历的点。但是一直只从 $q$ 中取堆顶点进行拓扑会有缺漏：如果 $tp$ 就只有一个点，且这个点的值还比 $q$ 的堆顶的值大，这时候我们还将这个元素转移至 $q$ 就很不明智了，相当于我们多连了一条边到这个点，而它原本就在 $tp$ 堆里。即：原本可通过正常拓扑实现字典序最小时最大，但我们多此一举地连了一条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/h2xvfjjb.png)

举一个例子：如上图，初始时有 $tp = \{5, 6, 11\}, q = \varnothing$，按照要求，我们可以将 $tp$ 堆顶的元素放到优选堆 $q$ 中：$tp = \{11\}, q = \{6, 5\}$。此时 $top_{tp} > top_q$。如果我们还把 $11$ 扔进 $q$ 中，使得 $tp = \varnothing, q = \{11, 6, 5\}$，再从 $q$ 中取出 $11$ 来进行拓扑，这看似没毛病，但之后就出事了：$11$ 会更新其相连的点使得 $12, 13$ 入度为 $0$，即 $tp = \{12, 13\}, q = \{6, 5\}$。按照刚刚的做法，我们将 $tp$ 中的点一股脑地扔进 $q$ 中，使得 $tp = \varnothing, q = \{13, 12, 6, 5\}$，再选择 $13$ 作为拓扑序的下一个点。别忘了 $q$ 中的点是需要连边的，而 $13$ 本来就与 $11$ 相连，此举相当于又连接了一条到 $13$ 的边（至于是谁连接至 $13$ 的还不确定），浪费了一次连有向边的机会。

而正确做法是：只需要等到 $tp$ 堆顶就剩 $13$ 时直接令其作为拓扑序的下一个目标点继续，即不必将 $13$ 加入 $q$ 中。这也很显然。

但是也不是所有情况下都是当 $tp$ 剩最后一个点时就令其为下一个拓扑序的点。假设：$tp = \{6\}, q = \{13, 12, 8\}$，这时最优结果显然不是 $6$，而是 $top_q = 13$。即连一条到 $6$ 的边（目前谁连的还无法判断），使其入度不为 $0$，然后便可以顺利成章地遍历到 $13$，使得结果最优。然后就是 $13$ 更新使得 $6$ 的入度又变成 $0$，顺便将与 $13$ 相连的其它点的入度减一，可能会加入一些别的入度变为 $0$ 的点，然后重复上述操作。

至于为什么 $6$ 的入度为 $0$ 却没有进入 $tp$ 中？或者说为什么 $q$ 中的点可以一直在里面好好呆着而不用弹出什么的？记得我们说过，$q$ 中的点一定会消耗一次连有向边的机会。因此，$6$ 肯定是要连边的，而 $tp$ 中的点是不必连边，是本该为正常拓扑序的点。我们是为了结果最优才将 $6$ 从 $tp$ 转移至 $q$ 的。

**进入 $q$ 中只是说明需要对里面的点进行连边以更改顺序，至于是谁连接的，还有待观察。**

如果还不懂，最后举一个例子，也可以自己手玩一些数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/1w5s3hle.png)

上图中有 $n = 6, m = 3$，而给出的 $k$ 不同，答案也截然不同：

1. 当 $k = 10^9$ 时，我们可以随便连边。首先，$tp = \{2, 3, 5\}$，我们将 $2, 3$ 连边，加入 $q$ 中，使得 $5$ 作为首位。然后，$4, 6$ 被加入进 $tp$ 中，形成 $tp = \{4, 6\}, q = \{3, 2\}$。为了最优，继续将 $4$ 扔进 $q$ 中，遍历 $6$，$1$ 的入度变为 $0$，加入 $tp$ 中，为了最优继续将它扔进 $q$ 中，形成：$tp = \varnothing, q = \{4, 3, 2, 1\}$。由于 $tp$ 为空，接下来只能从 $q$ 中取点。那和谁连边呢？拓扑的上一个点。在这里指的是 $6$。然后先后连接 $6 \rightarrow 4 \rightarrow 3 \rightarrow 2\rightarrow 1$。最后的结果就是：$\{5, 6, 4, 3, 2, 1\}$
2. 当 $k = 3$ 时，我们仍可以在开始时连边至 $2, 3$ 两点以改变顺序，到了 $6$ 时依然可以连边至 $4$ 改变顺序。但当我们想将 $1$ 加入 $q$ 时，我们的 $k$ 归零了，意味着我们无法继续改变顺序，$1$ 只能在 $tp$ 中呆着等待被遍历。综上，我们只能连接 $1 \rightarrow 4 \rightarrow 3 \rightarrow 2$。结果为：$\{5, 6, 1, 4, 3, 2\}$
3. 当 $k = 2$ 时，我们就只能在 $2, 3$ 上连边了。$4, 1$ 我们无法改变顺序。连边：$1 \rightarrow 3 \rightarrow 2$。结果为：$\{5, 4, 6, 1, 3, 2\}$
4. 当 $k = 1$ 时，我们选择在 $2$ 连边以将结果最优化。连边：$1 \rightarrow 2$。结果为：$\{3, 5, 4, 6, 1, 2\}$
5. 当 $k = 0$，显然我们无法操作。结果为：$\{2, 3, 5, 4, 6, 1\}$

最后总结操作：

1. $tp$ 还有多的点，且 $k > 0$ 我们就选择继续连边，但如果 $top_{tp} > top_q$ 且 $tp$ 仅有一个点，连边就不必要，直接继续进行拓扑。
2. 如果 $tp$ 非空，就从中取堆顶进行拓扑；否则从 $q$ 中选取堆顶，并连接一条由上一个拓扑的点至此堆顶的边。
3. 记得用变量保存一下上一个拓扑点，用数据结构存储拓扑序和连接边。

## 代码

放一下主要的拓扑的代码。

```cpp
void topo(){
	int lst, now;
	while (!tp.empty() || !q.empty()){ // 其实可以for 1~n取代，因为topo每个点都会被遍历到 
		while (!tp.empty() && k){
			int x = tp.top(), y = q.empty()? -1 : q.top();
			if (x > y && tp.size() == 1) break;
			tp.pop();
			q.push(x);
			k--;
		}
		if (!tp.empty()){
			now = tp.top();
			tp.pop();
		} else {
			now = q.top();
			q.pop();
			line.push_back(mp(lst, now)); // 记得连边 
		}
		order.push_back(now);
		for (int j = head[now], v; j != -1; j = e[j].nxt){ // 更新 
			v = e[j].to;
			in[v]--;
			if (!in[v]) tp.push(v);
		}
		lst = now;
	}
}
```

## 后日谈

这是本人第一篇黑题题解，~~虽然我感觉这只有蓝罢了~~。

打 CSP-S 的考试的 T3 就给我出这题，当时嫌无聊用原题机搜，直接给我吓哭了。

---

## 作者：Glacial_Shine (赞：1)

~~又是我不会的题……~~

感觉非常妙。

首先考虑对于一个我想输出的方案，最小要加几条边才能从原图输出。

设输出的方案为 $a_i$，明显就是只会存在从 $a_i$ 连向 $a_{i + 1}$ 的边。

现在考虑如何做这道题。

首先知道，题目就是求拓扑序的时候用了小根堆，在有多个入度为 $0$ 的点中最小的。

接下来考虑加边，如果 $k = 0$ 显然直接做，接下来考虑 $k > 0$。

如果当前入度为 $0$ 的点有多个，我们显然不能输出最小的，考虑往最小的点连边，此时我们并不需要确定是哪个店往最小的点连边，只需要知道它会被连边，至于哪个点往其连边在输出它的时候将上一个输出的数向它连边即可。

于是我们再开一个大根堆维护入度为 $0$ 但是有点向它连边的点。

然后就做完了，具体实现可以看代码（有注释）。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, Ecnt, last[100005], rd[100005];
struct Edge { int next, to; } E[200005];
struct node { int u, v; } a[100005];
void addedge(int u, int v) { Ecnt++, E[Ecnt].next = last[u], last[u] = Ecnt, E[Ecnt].to = v; }
priority_queue <int> q, p;
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addedge(u, v), rd[v]++;
    m = 0;
    for (int i = 1; i <= n; i++)
        if (!rd[i])
            q.push(-i);
    int lastx = 0;
    while (!q.empty() || !p.empty()) {
        int x;
        while (!q.empty() && k && (q.size() > 1 || (!p.empty() && -q.top() < p.top())))
            p.push(-q.top()), q.pop(), k--;//如果这个点比当前能输出的点要小（有比他大的点入度为 0）则把其加入大根堆里
        if (!q.empty())
            x = -q.top(), q.pop();
        else
            x = p.top(), p.pop(), m++, a[m].u = lastx, a[m].v = x;//如果要取大根堆里的点则将上一个点与其连边
        printf("%d ", x), lastx = x;
        for (int xy = last[x]; xy; xy = E[xy].next) {
            rd[E[xy].to]--;
            if (!rd[E[xy].to])
                q.push(-E[xy].to);
        }
    }
    printf("\n");
    printf("%d\n", m);
    for (int i = 1; i <= m; i++)
        printf("%d %d\n", a[i].u, a[i].v);
    return 0;
}
```

还有就是当你错第三个点的时候大概率是你的做法假了（别问我咋知道的

---

## 作者：Ptll (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7054)
# **题目分析**
题目说的很清楚，如果没有 $k$ 就是纯**拓扑**；

题目说最小的拓扑序的最大，俗称第一位最小，第二位第二小等；这一看就是**贪心**；

虽说知道了大致方向但如何贪又是一个问题；
# **思路**
贪心：对于当前入度为 $0$ 的点，假如有多个，给比较小的点加一个连向它的边，然后选大一点的点。

拓扑：在拓扑中不断进行选择，从 $in$ 为 $0$ 的点开始依次抉择，每一步找一个小一点的点来连；

所以总体思路就是贪心和拓扑；

那么怎么存呢？

众所周知，实现拓扑时会使用到**队列**这~~很容易~~想到 `priority_queue` 来排最小字典序的拓扑序，因为为了满足字典序最小，我把拓扑排序的队列换成小根堆，并且记录路径（其实无所谓，用 `priority_queue` 也行）；

我们要让连边后的拓扑序字典序最大，那就要让越靠前的数越大，不难想到：我们只需要用一个大根堆来存储当前能与其他点连边的点就行了（大根堆会自动从大到小排序）。
# **Code**

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+5;
ll n,in[N],m,k;
struct node {
    ll u,v;
};
vector<ll> v[N];
vector<node> ans;
priority_queue<ll,vector<ll>,greater<ll>> pq;
priority_queue<ll,vector<ll>,less<ll>> q;//用priority_queue<ll>也行
void tosort() {
    ll root=-1;
    while(!q.empty()||!pq.empty()) {
        while(!pq.empty()&&k>0) {
            ll num=pq.top();
            pq.pop();
            ll sum=q.empty()?0:q.top();
            if(sum<num&&pq.empty()) {
                pq.push(num);
                break;
            }
            q.push(num);
            k--;
        }
        ll num=-1;
        if(pq.empty()) {
            num=q.top();
            q.pop();
            if(root!=-1) {
                ans.push_back({root,num});
            }
        }
        else {
            num=pq.top();
            pq.pop();
        }
        cout<<num<<' ';
        for(ll i=0;i<v[num].size();i++) {
            in[v[num][i]]--;
            if(in[v[num][i]]==0) {
                pq.push(v[num][i]);
            }
        }
        root=num;
    }
}
int main() {
    cin>>n>>m>>k;
    for(ll i=1;i<=m;i++) {
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        in[y]++;
    }
    for(ll i=1;i<=n;i++) {
        if(in[i]==0) {
            pq.push(i);
        }
    }
    tosort();
    cout<<endl<<ans.size()<<endl;
    for(ll i=0;i<ans.size();i++) {
        cout<<ans[i].u<<' '<<ans[i].v<<endl;
    }
    return 0;
}
```
感谢 [plh](https://www.luogu.com.cn/user/427045) 对本题解的帮助。

---

