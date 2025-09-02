# [USACO20FEB] Clock Tree S

## 题目描述

Farmer John 的新牛棚的设计十分奇怪：它由编号为 $1\ldots N$ 的 $N$ 间房间（$2\leq N\leq 2\,500$），以及 $N−1$ 条走廊组成。每条走廊连接两间房间，使得每间房间都可以沿着一些走廊到达任意其他房间。

牛棚里的每间房间都装有一个在表盘上印有标准的整数 $1\ldots 12$ 的圆形时钟。然而，这些时钟只有一根指针，并且总是直接指向表盘上的某个数字（它从不指向两个数字之间）。

奶牛 Bessie 想要同步牛棚中的所有时钟，使它们都指向整数 $12$。然而，她头脑稍有些简单，当她在牛棚里行走的时候，每次她进入一间房间，她将房间里的时钟的指针向后拨动一个位置。例如，如果原来时钟指向 $5$，现在它会指向 $6$，如果原来时钟指向 $12$，现在它会指向 $1$。如果 Bessie 进入同一间房间多次，她每次进入都会拨动这间房间的时钟。

请求出 Bessie 可能的出发房间数量，使得她可以在牛棚中走动并使所有时钟指向 $12$。注意 Bessie 并不拨动她出发房间的时钟，但任意时刻她再次进入的时候会拨动它。时钟不会自己走动；时钟只会在 Bessie 进入时被拨动。此外，Bessie 一旦进入了一条走廊，她必须到达走廊的另一端（不允许走到一半折回原来的房间）。

## 说明/提示

#### 样例解释：
在这个例子中，当且仅当 Bessie 从房间 $2$ 出发时她可以使所有房间的时钟指向 $12$（比如，移动到房间 $1$，$2$，$3$，$2$，最后到 $4$）。

#### 子任务：
- 测试点 $2$-$7$ 满足 $N\leq 100$。
- 测试点 $8$-$15$ 没有额外限制。

## 样例 #1

### 输入

```
4
11 10 11 11
1 2
2 3
2 4```

### 输出

```
1```

# 题解

## 作者：泥土笨笨 (赞：62)

因为题目求起点有多少个，那么我们依次枚举每个点作为起点，把它当做树根，从它出发往孩子走，看看能不能做到。

每当Farmer John沿着一条线在树上走的时候，遇到的每个点时间都往前加1。考虑从树上某个结点u走到它的孩子v，那么u和v上的时间都往前加1了。也就是说要改就父子一起改，父子之间的差是不变的。既然题目中是验证是否能完成，我们不妨贪心地看，每次不停地从父子之间来回走，直到把孩子改成12，这时候根据父子差固定，我们就能知道u现在是多少。然后再去搞下一个孩子，再确定u的值。直到把所有孩子都改好，此时u固定到了某个数。回到上一层，再由父亲把u改成12

那么这么一轮下来，最后除了根，其他点都是12了。那么根如果正好是12，说明是可以的。如果根不是12呢？其实根是1也行，因为这样就最后的时候从根的最后一个孩子停下，不走回来。这时候根和最后一个孩子的时间会差一个。除了这两种情况，其他都不行。

这样枚举每个点做根，每次根确定以后，一遍dfs，总的时间复杂度是$O(n^2)$，不超时。实际写的时候，用一个c数组表示每个点现在的时间，然后用0表示12，这样每次对12取模就行了，写起来比较方便。最终目标也是把所有点调成0.

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN = 2505;
int n, c[MAXN], t[MAXN], ans;
vector<int> adj[MAXN];

void dfs(int u, int f) {
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == f) continue;
        //先递归孩子，把孩子调到0
        dfs(v, u);
        //当前点和孩子的差不变，求出当前点的值
        t[u] = (t[u] - t[v] + 12) % 12;
    }
}

int main() {
//    freopen("clocktree.in","r",stdin);
//    freopen("clocktree.out","w",stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
        c[i] %= 12;
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        //先把c数组拷贝到t数组里面，去操作t数组。免得c被改掉了下次循环数不对了。
        memcpy(t, c, sizeof(t));
        dfs(i, 0);
        //最后根上剩下0或者1就是可以的
        if (t[i] == 0 || t[i] == 1) ans++;
    }
    cout << ans << endl;
    return 0;
}
```

后记，后来比赛完才想起来有个O(n)的二分染色算法，其他大佬写过题解了，我就不写了。

---

## 作者：7KByte (赞：14)

本题纯属思维题。


出题人太过仁慈放$\operatorname{O(N^2)}$的``DP``过了……



-------------

解题思路

我们对整棵树进行黑白染色，相邻两点异色。

对于白色节点权值和记作$S_0$，黑色节点权值和记作$S_1$。

对于每一个点，设它的颜色为$C$。

该节点能作为起点，当且仅当$S_C-S_{1-C}\equiv0\  \operatorname{or}\  1\pmod{12}$。

时间复杂度$\operatorname{O(N)}$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 2505
using namespace std;
int s[2],n,u[N],h[N],tot;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
int v[N];
void dfs(int x,int op,int f){
	s[v[x]=op]+=u[x];
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=f)
	  dfs(e[i].to,op^1,x);
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&u[i]);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,0);
	int ans=0;
	rep(i,1,n){
		int val=((s[v[i]]-s[v[i]^1])%12+12)%12;
		if(val==1||val==0)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ix35 (赞：10)

## P6150 USACO 20 FEB ClockTree

这是一道很有意思的 DP 题。

首先发现 $N\leq 2500$，所以我们可以暴力枚举每个点，判断从这个点出发能不能完成任务。

首先先掌握一个技能：反复横跳。

如果你现在在 $u$ 点，有边 $(u,v)$，那么你可以沿着 $u\to v\to u\to v\to u\to \cdots$ 这样一直运动下去，假设你最后回到了 $u$，那么 $u$ 和 $v$ 在这个过程中指针移动的距离是相等的。

首先考虑叶结点的情况，想将叶结点调回 $12$ 只能借助它和父亲的边上反复横跳，所以我们可以得知它对父结点的"贡献"。接下来，叶结点的父结点再对它的父结点产生贡献，最后回到根结点。这个就是大体思路。

具体的 DP 状态是：设 $dp(i)$ 表示：从 $i$ 出发，往子树内部走，使得子树内除了 $i$ 以外所有点都指到 $12$ 时，最后回到 $i$ 的情况下，$i$ 点的钟所指的位置。

转移就是考虑贡献，$dp(i)$ 一开始就是 $a_i$（初始状态），然后对于一个子结点 $j$，为了将 $j$ 变为 $12$，需要在 $(i,j)$ 上反复横跳 $12-dp(j)$ 次，将这个值加到 $dp(i)$ 上即可。

最后考虑根结点的 $dp$ 值，如果 $dp(rt)=12$，那么显然可行，但是反过来是不对的，因为我们现在只统计了回路的情况（从根结点出发回到根结点），还有停在其他点的情况。

比如说，$dp(rt)=1$，那么我们考虑最后一步，是从根结点的一个儿子走到根结点，如果这一步不走，那么根结点就会少移动一格，正好指向 $12$，也是可行的。

有没有其他可能性呢？没有了，如果我们停在了根结点儿子的儿子，那么我们可以先走到根结点，然后在根结点和根结点一个儿子的位置反复横跳 $11$ 次，产生等效的效果，且最终停在了根结点，所以终态只有 $dp(rt)$ 为 $12$ 或 $1$ 两种情况可行。

时间复杂度为 $O(N^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2510;
int n,x,y,eg,ans,hd[MAXN],ver[2*MAXN],nx[2*MAXN],a[MAXN],dp[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	dp[x]=12-a[x];
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs(ver[i],x);
		dp[x]=(dp[x]-dp[ver[i]]+12)%12;
	}
	return;
}
int main () {
	freopen("clocktree.in","r",stdin);
	freopen("clocktree.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {scanf("%d",&a[i]);}
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
	}
	for (int i=1;i<=n;i++) {
		dfs(i,0);
		if (dp[i]==0||dp[i]==11) {ans++;}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：WeLikeStudying (赞：5)

- 这应该是一道让我记忆犹新的题目，作者从看到这道题，到写这篇博客，到写出它的正解，花了将近半年的时间。
- 作者的智商由很大的进步空间。

**题意**
- [链接](https://www.luogu.com.cn/problem/P6150)。
- 给出一棵 $n$ 个节点的树，每个节点上有一个 $1$ 到 $12$ 的时刻（小时）。
- 奶牛可以从树上的某个节点开始走到另一个节点，每次**通过走廊到达**一个房间都会将该房间的时钟向后拨 $1$ 小时。
- 如果让奶牛从某些起点出发，则她有可能将树上所有节点上的时刻都变为 $12$ 小时，输出有多少可能的起点。
- $n\le 2500$。

**分析**
- 想起路径问题就让我想起了某道题，是个结论题。
- 当然，这道题它的形式就很奇怪，我们先研究合法的路径满足怎样的特征，然后对 $12$（是个偶数）取模也是个性质。
- 考虑一种合法的情况，显然可以等价为节点 $u$ 的儿子形成的奇数（代表在这里终止）或者偶数条路径，容易发现，显然 $u$ 需要处理这些节点。
- 如果 $u$ 的所有儿子只是上传给 $u$ 都是偶数条路径，$u$ 可以选择~~自尽~~在该节点结束，在这之前，可以截留偶数条路径作为自己的一次贡献。
- 否则 $u$ 无法自尽，但是还是可以截留偶数条路径作为自己的一次贡献。
- 但是，根没有上司，它无法截留，还有叶子的情况也需要注意。
- 综上，我们可以打出一个很暴力的 $\text{DP}$，由于算法描述的不确定性，它是难以实现的（或许可以打下）。
- 我们可以来一点构造的思想，思考一些构造方案的替代。
- 构造元件：反复，技能用途，如果你经过了某条边一次，你可以将这起点加上 $x-1$，终点加上 $x$。
![](https://cdn.luogu.com.cn/upload/image_hosting/5b34ieww.png)
- 构造元件：回来，如果你从某地出发并且回到了源点，你可以在某条路径上的两个点加上任意的数值 $x$，其实就是由反复横跳得到的。
- 构造元件：回路，如果你从某地出发并回到源点，你可以在任意的边的两个端点加上一个任意的值 $x$。
- 你会发现：“回路”操作已经替代了我们所有从根开始回到根的操作了，我们可以把除了根以外的所有颜色都进行染色，然后我们发现只有根是 $1$ 或 $12$ 是有解的。
- 如果还需要发现性质的话就是如果对数进行二分图染色，黑点和白点的差是固定的，所以有相当简洁的线性算法，[代码](https://www.luogu.com.cn/paste/y8dae423)。

---

## 作者：kkauplz (赞：4)

~~啊啊啊比赛的时候本来想靠这题翻盘，结果一看觉得太难就放弃了，其实一点也不难啊！~~

言归正传

## 算法分析

不难发现，N个节点N-1条边，说明谷仓与走廊组成了一棵树，同时由于每个谷仓可以经过多次，一般的搜索肯定是不行的。

~~一般遇到树的题都从叶子结点开始想~~ 首先，让我们考虑只有两个谷仓的情况，如何改变某一个谷仓中的指针指向？无非就是往返于两个谷仓之间。对于每一个叶子结点，改变其指向的唯一方法就是往返于该叶子结点于其父结点之间。那么为了使某一个父结点的所有子结点都指向12，该父结点就必须要被经过每一个子结点需要经过次数的和。

## 算法实现

枚举起始结点，深搜，若起始点的值为0或11即可以实现。
这里0或11是因为起始结点没有父，其值则不能再被改变，同时因为可以停在树中间，不回到起始结点，则总和会少1，所以11也是可以的。

## 代码

代码写起来还是很容易的，就是稍微有一点思考难度

```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<int> G[2505];
int n;
int c[2505];
bool vis[2505] = {false};

int dfs(int fa) {
    int tmp = 0;
    for (int i = 0; i < G[fa].size(); ++i) {
        if (!vis[G[fa][i]]) {
            vis[G[fa][i]] = true;
            tmp += dfs(G[fa][i]);
            vis[G[fa][i]] = false;
        }
    }
    //cout << 12 - ((c[fa] + tmp) % 12) << endl;
    return 12 - ((c[fa] + tmp) % 12);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2505; ++j) {
            vis[j] = false;
        }
        vis[i] = true;
        int tmp = dfs(i);
        //cout << tmp << endl;
        if (tmp % 12 == 0 || tmp % 12 == 11) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：_szs9601 (赞：3)

#### 题意
给出一个无向图，通过行走，使每个点的值都到达 12。
#### 思路
我们枚举每一个点作为根，首先将叶子节点的值变成 12。回到上一层，再把父亲改成 12。所以最后我们只要判断根节点就可以了。

根如果正好是 12，就说明是可以的。当根是 1 的时候，也是可以的。因为这样就是最后的时候从根的最后一个儿子停下，不走回来。这时候根和最后一个儿子的值会差 1。除了这两种情况，其他都不行。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,b[3000],c[3000],ans,x,y;
vector<int>a[3000];
void sc(int t,int fa){
	int x;
	for(int i=0;i<a[t].size();i++){
		x=a[t][i];
		if(x==fa) continue;
		sc(x,t);
		c[t]=(c[t]+12-c[x])%12;
	}
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&b[i]);
	for(i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}//建图
	for(i=1;i<=n;i++){
		memcpy(c,b,sizeof(c));
		sc(i,0);
		if(c[i]==0||c[i]==1) ans++;
	}//枚举根
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：信守天下 (赞：3)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6150)
## 思路
路径的可能性太多，难以入手。

但我们只需要求起点的数量，所以需要分析路径的特性，对问题进行化简。

⾸先考虑路径的范围，我们可以让路径必然经过所有的点。

假定存在⼀条路径没有经过所有的点。

那么找到离路径最近的未到点 $A$ ，令它在路径中的邻点为 $B$ 。

我们可以在路径到达时，额外来回走过 $AB$ $12$ 次。

这样答案不变，但是路径会经过 $A$ 。

然后考虑路径的终点，如果起点到终点的距离⼤于1。

令终点到起点的路径为 $T , A , B ...$ ，那么我们可以延伸终点到 $B$ 。

然后反复⾛过 $11$ 次，这样答案不变，但是终点离起点更近了。

最终我们可以确保终点和起点距离不超过 $1$ 。

综上所述，如果⼀个点可以作为起点。

必然可以从它开始遍历完所有的节点并回到起点。

此时所有节点的值都为 $0$ ，⽽起点的值可以为 $0$ 或 $1$ 。

那么枚举起点，再遍历求解即可。
## 复杂度分析
### 时间复杂度
枚举起点 $O(N)$ 。

遍历 $O(N)$ 。

总共 $O(N^2)$ 。

本题还可以使用换根的方式做到 $O(N)$ ， 但没有必要， $O(N^2)$ 完全能过。
### 空间复杂度
存储树 $O(N)$ 。
## $code$
~~~cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int kMaxN = 2501;
struct V {
  int _v, v;
  vector<int> p;  // 邻点
} v[kMaxN];
int n, x, y, s;
void T(int f, int x) {
  v[x].v = (v[x]._v + 1) % 12;  // 第一次到达
  for (int i = 0; i < v[x].p.size(); i++) {
    if (v[x].p[i] != f) {
      T(x, v[x].p[i]);                               // 遍历儿子
      v[x].v = (v[x].v + 13 - v[v[x].p[i]].v) % 12;  // 将儿子调好
    }
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i]._v;
  }
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    v[x].p.push_back(y);
    v[y].p.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    T(0, i);
    s += v[i].v == 1 || v[i].v == 2;  // 不回起点或者回到起点，起点多算了一次
  }
  cout << s;
  return 0;
}

~~~

---

## 作者：tanghg (赞：2)

本题看到了 $n-1$ 条边和保证联通就可以想到是棵树。

然后说求有几个也可以发现是问假设每个结点做一次根的话，有几个是合理的。

之后就是调整了，我们不妨就从叶子结点和其父节点想起，这也是边界了。

首先要知道 **两个点之间只有一条唯一路径可以到达，没有其他路径了。** 这也是之后贪心的基础。

那么聪明的读者可能已经想到了，父节点和叶子结点互相走其实是很优秀的，因为如果再往上的话早晚还得下来，反而可能浪费机会。

在父节点和子节点来回走到子节点变成 $12$ 时父节点是多少呢？由于差不变，所以就是 $(t_u - t_v +12)\bmod 12 $， 差不变，所以用差 $+12$ 就是变的，之后膜一下确定边界就行了，把这个推到整体也就是答案了。

怎么确定答案呢？ 因为根节点没有父节点了，所以它无法调整，如果在子树都处理好了的时候它也正好走到了 $12$ 就可以了，或者根是 $1$，这说明和孩子差一个，那么不回来就是正好的。

```cpp
#include<iostream>
#include <vector>
#include <queue>
using namespace std;
typedef int ll;
const ll MAXN=1e4+5;
ll n,c[MAXN],t[MAXN];
vector<ll>adj[MAXN];
void dfs(ll u,ll f){
    for (int i = 0; i <adj[u].size() ; ++i) {
        ll v=adj[u][i];
        if(v==f){
            continue;
        }
        dfs(v,u);
        t[u]=(t[u]-t[v]+12)%12;
    }
}
int main(){
    cin>>n;
    for (int i = 1; i <=n ; ++i) {
        cin>>c[i];
    }
    for (int i = 1; i <n ; ++i) {
        ll u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans=0;
    for (int i = 1; i <=n ; ++i) {
        for (int j = 1; j <=n ; ++j) {
            t[j]=c[j];
        }
        dfs(i,0);
        if(t[i]==0||t[i]==1){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：gongyubin2011 (赞：1)

看到很多大佬用的 DP ，那我就交一篇 DFS 的题解吧！

## 思路

可以将这个图看作一棵树。从底部出发，每次只能拨一格，运用减法。假设一共 $4$ 层，第 $3$ 层时间减第 $4$ 层时间，第 $2$ 层时间减第 $3$ 层时间，第 $1$ 层时间减第 $2$ 层时间。也就是说，我们只需要讲第 $1$ 层的时间加上第 $3$ 层的时间，再减去第 $2$ 层加上第 $4$ 层的时间就可以了 $(a+c)-(b+d)$。用一个巧妙的方法——染色。用奇数层的和减去偶数层的和。

## 注意

若果最后两个的时间相差剩 $1$，也可以完成要求。因为题目中并没有要求必须回到原点，或已可以停留在另一个点上。


具体实现方法在代码中，请自行查看。

```cpp
#include<bits/stdc++.h>
using namespace std;
int op[7],n,a[2505],hand[2505],v[2505],sum;
struct Point
{
	int to;
	int nxt;
}edge[5005]; 
void f(int x,int y)
{
	edge[++sum].to=y;
	edge[sum].nxt=hand[x];
	hand[x]=sum;
}//建边(链式前向星加边) 
void dfs(int x,int flag,int f) 
{
	v[x]=flag; 
	op[flag]+=a[x];
	for(int i=hand[x];i!=0;i=edge[i].nxt)
	{
		if(edge[i].to!=f) 
		{
			dfs(edge[i].to,1-flag,x);//1-1=0 (黑变白) 1-0=1 (白变黑) 
		}
	}
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)cin>>a[i];//输入 
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;//边读入，边建立双向边 
		f(x,y);
		f(y,x);//双向边 
	}
	dfs(1,0,0);//DFS一测 
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		int yu=((op[v[i]]-op[1-v[i]])%12+12)%12;//因为 op[v[i]]-op[1-v[i]] 可能会变为负数，所以要加12之后在%一遍12 
		if(yu==1 || yu==0)ans++;//最后两点相差1格时，可以停在除起点外的另一个时钟没到达12点的点上 
	}
	cout<<ans<<endl;//输出答案 
	return 0;
}
//o(n)算法 
```


---

## 作者：c_y_y (赞：1)

# [P6150题解](https://www.luogu.com.cn/problem/P6150)
打模拟赛时遇到了这道题，可是老师把源文件设为了 `clock`。这就导致了虽然我想到了贪心正解，但是大暴力 T 飞了……

所以，我们先来讨论 Clock **Tree** 的证明。

---
注：后面我们把一个房间里面时钟指向的方向称为该房间的值。

---
### 为什么走廊和房间构成的图是 Tree？
第一眼看到题目时，首先想到的就是特判出现环或局部环的情况。~~尽管赛后我才想到~~，注意到题目中的第一句话：
>Farmer John 的新牛棚的设计十分奇怪：它由编号为 $1\ldots N$ 的 $N$ 间房间，**以及 $N-1$ 条走廊组成**。

如果一个图里面有环，那么所有的点必须有一条与其相连且没有被选择过的一条边（想一想）。那么，作为一个**连通图**，必然至少有 $N$ 条边，与题目矛盾。

因此，走廊和房间构成的图必然没有环，即是**一棵树**。

那么，~~胡扯~~证明出了不会出现一个环，有什么用呢？
### “贪心”证明最优解
由于我们只用输出合法的房间个数，那么我们只需要判断以该房间作为起点能否合法就行了。也就是说**我们可以自由地安排路径！**

每次我们把起点设为该树的根。既然从头不好想，那么我们从最后开始想。

由于前面的证明，我们知道肯定有一个节点只有一条边与之相连，这个节点（后面我们称它为 $a$ 点）肯定只有一个父亲（后面我们称它为 $b$ 点）。

**从局部看**，Bessie 要想让 $a$ 的值为 $12$，Bessie 只能从 $b$ 来到 $a$ 点。所以，Bessie 可以在这两个房间里面来回移动，**直至 $a$ 房间的值为 $12$** 。此时，$b$ 房间的值我们也可以知道（数学）。

然后，Bessie 可以走到 $b$ 的父亲，和 $a$ 一样的套路将 $b$ 的值调为 $12$ ，然后，Bessie 可以走到 $b$ 的父亲的父亲，和 $b$ 一样的套路将 $b$ 的值调为 $12$……

看到了吗，这是一个**递归的过程**。我们按照这个套路把所有非起点的房间的值调为 $12$。最后，我们判断起点的值就行了。如果起点是 $12$（走回起点）或 $1$（不走回起点），都可以判断该方案可行。

### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2510;
int c[N],n,t[N];
vector<int> G[N];
void dfs(int son,int father) {
	for(int i=0;i<G[son].size();i++){
		int v=G[son][i];
		if(v==father) continue;
		dfs(v,son);
		t[son]=(t[son]-t[v]+12)%12;
		if(t[son]==0) t[son]=12;
	}
}
int main() {
	//freopen("clock.in","r",stdin);
	//freopen("clock.out","w",stdout);
	cin.tie(0),cout.tie(0),ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memcpy(t,c,sizeof(c));
		dfs(i,-114514);
		if(t[i]==1 || t[i]==12) ans++;
	}
	cout<<ans;
	return 0;
}
```
本蒟蒻的第四篇题解，多多支持～

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6150)

主要知识点：图上dfs。

## 思路

这道题给出我们的是一个 $n$ 个房间，$n-1$ 条走廊，其实就是 $n$ 个点，$m$ 条边。每一个房间都可以走到另外的房间，说明它是连通的，那么 $n$ 个点 $n-1$ 条边连通的一个图，那这道题给我们的就是一棵树。

他既然要求那一个节点是可以当作起点，那就可以把它当作这棵树的根来看。所以我们可以枚举每一个点，看看这个点是不是可以把所以的房间都变成 $12$，最后再统计答案就可以了。

假设现在从点 $u$ 到点 $v$，要把这个点 $v$ 给改成 $12$，既然我们可以发现可以从 $u$ 到 $v$，再从点 $v$ 到 $u$。那么最后总能把这个点 $v$ 调成 $12$。那调完 $v$ 以后呢？$u$ 也总得改值吧。如果是这样来把孩子的的值调整为 $12$，那么 $u$ 和 $v$ 一直的差也是不变的，所以 $u$ 就等于 $(u+(12-v))$。但是在计算 $u$ 到 $v$ 的话，必须得先把 $v$ 能到的点先给改成 $12$，但是不能遍历到 $u$。

最后，我们就可以看一下当做起点的值是不是变成了 $12$。其实变成 $1$ 也可以。我们可以在最后的那个点再蹦回来的时候，就截至，就不让最后那个点在返回来让起点 $+1$。也就是把起点变回了 $12$。

直接上代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long n,a[N],u,v,t[N],ans;
vector<long long> b[N];
void dfs(long long x, long long fa) 
{
    for(long long i=0;i<b[x].size();i++) 
	{
        long long o=b[x][i];
        if(o==fa) 
		{
			continue;
		}
        dfs(o,x);
        t[x]=(t[x]+(12-t[o]))%12;
        t[o]=0;
    }
}
int main() 
{
    cin>>n;
    for(long long i=1;i<=n;i++)
	{
        cin>>a[i];
        a[i]%=12;
    }
    for(long long i=1;i<n;i++) 
	{
        cin>>u>>v;
        b[u].push_back(v);
        b[v].push_back(u);
    }
    for(long long i=1;i<=n;i++) 
	{
        for(long long j=1;j<=n;j++) 
		{
			t[j]=a[j];
		}
        dfs(i*1,0);
        if(t[i]==1||t[i]==0) 
		{
			ans++;
		}
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：GWBailang (赞：0)

[**原题传送**](https://www.luogu.com.cn/problem/P6150)

首先，$O(n^2)$ 的复杂度可以过，不难想到可以分别去枚举每一个点，判断这个点能否作为出发房间。

题目说给定的图有 $N$ 个点和 $N-1$ 条边，并且是无相连通图，说明这是一颗树。我们先考虑叶节点如何将指针转到 $12$：在父节点与叶节点之间一直走，直到将叶节点的指针转到 $12$，然后回到父节点。这样就将一个叶节点搞定了，以后就不用再考虑这个点了。

当一个节点的所有的孩子都通过上述的方法将指针转到了 $12$，那么我们就又可以将这个节点当做一个叶节点，用同样的方法去拨指针。

最后会去拨根节点和它的孩子，拨完以后如果根节点的指针指向 $12$，说明这个节点是可以作为初始房间的。需要注意的是，我们最后波动完根节点的所有的孩子以后不一定非要回到根节点，为了方便，我们的算法会让奶牛直接回到根节点。所以当最后根节点的指针指向 $1$ 时，这个节点也是可以被作为初始房间的。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2505];
int cl[2505];
//a数组用于存放所有房间的指针的初始值
//cl数组也用于存放所有房间的初始值，
//只不过在遍历的过程中会被改变
//所以需要用一个新数组(cl)存
vector<int>bian[2505];//邻接表
int n;
void csh(){//初始化
	for(int i=1;i<=n;i++){
		cl[i]=a[i];
	}
}
void dfs(int u,int fa){
	for(auto v:bian[u]){
		if(v==fa)continue;
		dfs(v,u);
		cl[u]=(cl[u]-cl[v]+12)%12;
		//孩子转动几次，父节点也要跟着转动几次
		//记得要mod 12，cl[u]=0就相当于指针转到了12
	}
}
int main(){
	int u,v,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		cin>>u>>v;
		bian[u].push_back(v);
		bian[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
	//枚举每一个节点能否当做初始房间
		csh();
		dfs(i,0);
		cnt+=(cl[i]<2);
		//cl等于0或1时都是可以作为初始房间的
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

