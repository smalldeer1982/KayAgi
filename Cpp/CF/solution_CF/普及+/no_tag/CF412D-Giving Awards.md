# Giving Awards

## 题目描述

## 问题描述

R1 公司的员工们喜欢一起消磨时间，他们一起看球赛，一起去野餐，一起做 Codeforces 的比赛。所以，一个人替另一个人结账是没什么大不了的事情。

今天是发奖金的日子，R1 公司的 CEO 会把员工一个一个请到他的办公室去，按照他们这个月的工作努力程度发奖金。CEO 知道谁欠谁的钱，而且他知道，如果他邀请 $x$ 去他的办公室，然后马上邀请 $y$ 去他办公室，且 $y$ 借给了 $x$ 一些钱，那么他们就能相遇，发生比较尴尬的事情，然后 $x$ 得到的钱就变少了。因此，R1 公司的 CEO 决定按照一个合适的顺序（即上述情况不会发生在任意一对员工之间）邀请员工。

但是，由于员工特别多，CEO 的时间是有限的，于是这个安排顺序的工作就落在了你的手中。给你员工之间的所有债务关系，请你为 R1 公司的 CEO 决定一个邀请员工的顺序。

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
2 1 3 
```

# 题解

## 作者：wxzzzz (赞：4)

### 题意

给定 $m$ 组关系，每组关系给定一个 $x_i,y_i$。构造一种的顺序，使得在新的顺序中满足任意 $x_i≠y_i-1$。

### 思路

首先构造一种顺序，使得任意 $x_i=y_i-1$。

然后把这组数据倒序输出，显然就是一种答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, idx, cnt, v[1000005], h[1000005], ne[1000005], ans[1000005];
bool vis[1000005];
inline void add(int a, int b) {
    v[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
inline void dfs(int x) {
    vis[x] = 1;

    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (!vis[y])
            dfs(y);
    }

    ans[++cnt] = x;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i);

    for (int i = 1; i <= cnt; i++)
        cout << ans[i] << ' ';

    return 0;
}
```

---

## 作者：Shimotsuki (赞：3)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF412D)

[传送门 to CF](https://codeforces.com/problemset/problem/412/D)

题目翻译十分清晰，可将员工看成点，将债务关系看成边，建图模拟。因为债务关系是单向的，所以图是有向图。然后对图进行搜索，开一个桶来记录某位员工是否来过，最后以未来过的员工做源点搜索即可。

$Code$
```cpp
//Problem:CF412D Giving Awards
//Time:2022.3.20
//Author:Leonador

#include<cstdio>

using namespace std;

#define N (int)(1e5+10)

struct edge{
    int next,to;
}e[N<<1];//链式前向星

int head[N],cnt=0,tot=0;
bool vis[N];
int ans[N];

inline void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void dfs(int u){
    vis[u]=true;
    for(int i=head[u];i;i=e[i].next){
        if(vis[e[i].to]) continue;
        dfs(e[i].to);
    }
    ans[++tot]=u;
}
int main(){
    int n,m,u,v;
    scanf("%d %d",&n,&m);
    while(m--){
    	scanf("%d %d",&u,&v);
    	add(u,v);//加边
	}
    for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i);//搜索
	for(int i=1;i<=tot;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```


---

## 作者：zzx0826 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF412D)
## 分析
我们可以采取搜索的办法

首先，这道题是$ 100\% $有解的

用一个$ vector $数组存储，$ v[i][j] $表示第$ i $个人欠了第 $ j $个人的前。

我们在搜索的时候以第 $ i $个人为第$ 1 $个,但先不把他加进去，$ mark[i] $记录第$ i $个人是否来过,对于第$ i $个人，我们枚举他欠过的人，让他们就在第$ i $个人之前先加进去，最后$ans$数组统计答案即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e4 + 5;
int n,m,a,b,ans[N],vis;
bool mark[N];
vector<int> v[N];
void dfs(int k)
{
    mark[k] = true;
    for(int i=0;i<v[k].size();i++)
    {
        if(!mark[v[k][i]])
        {
            dfs(v[k][i]);
        }
    }
    ans[++vis] = k;
}
int main()
{
    scanf("%d %d",&n,&m);
    while(m--)
    {
        scanf("%d %d",&a,&b);
        v[a].push_back(b);
    }
    for(int i=1;i<=n;i++)
    {
        if(mark[i])
        {
            continue;
        }
        dfs(i);
    }
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：UperFicial (赞：1)

我们把 $a_i$ 向 $b_i$ 连一条有向边，设 $f(x)$ 表示从 $x$ 开始的序列。

考虑 $x$ 的所有出点 $y$，$f(y)$ 一定在 $f(x)$ 之前进行。

这个可以用 `dfs` 来实现，对于当前节点 $x$，搜索其所有子节点后，将 $x$ 加入答案序列即可。


---

## 作者：出言不逊王子 (赞：1)

看这个题目第一眼，我还以为是拓扑排序。

构造一个 DAG ，如果 $a$ 欠了 $b$ 钱，说明 $b$ 得在 $a$ 前面，即让 $b$ 往 $a$ 连边。

然后在这个 DAG 上跑拓扑排序即可。

然后手模样例 $2$ 会发现他们的欠钱关系中有**环**。

分析样例 $2$ ，会发现虽然 $2$ 欠了 $3$ 钱，但是 $2$ 只要没有**正好**在 $3$ 前面进办公室就**不会**出事。

这启发我们可以仅针对每一个人，让欠他钱的人先进去就够了。

具体实现起来，如果 $a$ 欠了 $b$ 钱就让 $a$ 往 $b$ 连边，跑一次 DFS ，让所有**没入栈的节点**入栈，在跑完所有会欠他钱的节点后，将这个节点加入 `ans` 数组（可以理解成二叉树的后序遍历）。

我想到这里的时候，第一反应是：这不就是拓扑排序吗？

但是它和拓扑排序最大的差异是：

拓扑排序要求绝对纯洁（没欠任何人钱）的节点作为开头，但是在数据中可能不存在这种情况。

而这个 DFS 它只考虑到对于没访问过的节点，只加入**直接欠他钱的人**而不用考虑**欠了“直接欠他钱的人”的钱的人**。

因为只要一个人没有在**直接欠他钱的人**之前拿钱，那他就啥事没有。

[AC 代码](https://www.luogu.com.cn/paste/sujevqrx)

---

## 作者：KID2695 (赞：0)

发现这个题目中有一个很神奇的描述：只有欠了钱的 $x$ 先被叫走，接着被借了钱的 $y$ 接着被叫过去才会发生尴尬的事情，所以我们第一反应是卡一下 bug，对于这对 $x$ 与 $y$，先叫走 $y$，再叫走 $x$，即使他们两个擦肩而过也没问题。

所以我们建立反图，顺着边输出，然后就会发现十分难写，因为很容易先输出了一个没有入度的点，然后接着就输出了与它相连的点，所以我们换种写法。

正着建图，每次找到一个没有走过的点，然后搜索所有与它相连的点（顺着边的方向），搜索完每一个点之后输出这个点的编号。

接下来简单证明一下正确性：假设有一对关系是 $A$ 借给了 $B$ 钱，建的图中就有 $A$ 连向 $B$，假设我们先搜到了 $A$ 并且紧接着搜到了 $B$，此时先输出 $B$ 后输出 $A$，符合要求；如果是先搜到了 $B$ 并且紧接着搜到了 $A$，此时 $B$ 没有出边（貌似没有什么作用），这时候先输出 $B$后输出 $A$，依旧合法。整个问题可以分成若干个上面的有关系的点与一些没有关系的点，正确性显然。

~~核心代码不放了~~

```cpp
void dfs(int u,int fa){
	vis[u]=1;
	for(int i=e.frt[u];i;i=e.nxt[i]){
		int v=e.to[i];
		if(vis[v]||v==fa) continue;
		dfs(v,u);
	}
	printf("%d ",u);
}
int main(){
	//输入略
	FOR(i,1,m){
		int u=iread(),v=iread();
		e.add(u,v);//e存图，连有向边
	}
	FOR(i,1,n){
		if(!vis[i]){
			dfs(i,0);
		}
	}
	return 0;
}
```

---

