# Approximate Diameter

## 题目描述

Jack has a graph of $ n $ vertices and $ m $ edges. All edges are bidirectional and of unit length. The graph is connected, i. e. there exists a path between any two of its vertices. There can be more than one edge connecting the same pair of vertices. The graph can contain self-loops, i. e. edges connecting a node to itself.

The distance between vertices $ u $ and $ v $ is denoted as $ \rho(u, v) $ and equals the minimum possible number of edges on a path between $ u $ and $ v $ . The diameter of graph $ G $ is defined as the maximum possible distance between some pair of its vertices. We denote it as $ d(G) $ . In other words, $ d(G) = \max_{1 \le u, v \le n}{\rho(u, v)} $. Jack plans to consecutively apply  $ q $  updates to his graph. Each update adds exactly one edge to the graph. Denote as  $ G\_i $  the graph after exactly  $ i $  updates are made. Jack wants to calculate  $ q + 1 $  values  $ d(G\_0), d(G\_1), d(G\_2), \\ldots, d(G\_q) $ .However, Jack suspects that finding the exact diameters of  $ q + 1 $  graphs might be a difficult task, so he is fine with approximate answers that differ from the correct answers no more than twice. Formally, Jack wants to find a sequence of positive integers  $ a\_0, a\_1, a\_2, \\ldots, a\_q $  such that  $ \left\lceil \frac{d(G_i)}{2} \right\rceil \le a_i \le 2 \cdot d(G_i) $  for each  $ i $.

## 说明/提示

In the first example, the correct sequence of $ d(G_0), d(G_1), d(G_2), \ldots, d(G_q) $ is $ 6, 6, 6, 3, 3, 3, 2, 2, 2 $ .

In the second example, the input contains an extra line that you can omit reading. It is not a part of the test and will be used for verifying your answer. The output of the second example contains the correct values of $ d(G_i) $ .

## 样例 #1

### 输入

```
9 10 8
1 2
2 3
2 4
3 5
4 5
5 6
5 7
6 8
7 8
8 9
3 4
6 7
2 8
1 9
1 6
4 9
3 9
7 1```

### 输出

```
10 6 5 6 2 4 2 2 1```

## 样例 #2

### 输入

```
8 7 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
1 5
3 7
2 4
4 6
6 8
8 2
5 4
2 4
3 3
1 652997 124613 653029 653029 124613 124613 124613 648901 124613 653029```

### 输出

```
7 5 4 4 4 3 3 3 3 3```

# 题解

## 作者：strlen_s_ (赞：11)

挺好的一道题，考察你对题目条件的充分运用。

观察这个柿子：

$$
\lceil \frac{d(G_i)}{2} \rceil \le a_i \le 2 \cdot d(G_i)
$$

我们要充分运用它。

先看左半部分：

$$
a_i \ge  \lceil \frac{d(G_i)}{2} \rceil
$$

有一个经典结论：

对于图上任意一点 $u$，它与其它点距离的最大值 $s$ 一定满足:

$$\lceil \frac{d(G_i)}{2} \rceil \le s \le  d(G_i) $$

**证明:**

考虑 $s$ 是图的直径上的点，那么 $s$ 到直径两端点的最大距离肯定大于等于 $\lceil \frac{d(G_i)}{2} \rceil$。

当 $s$ 不是直径上的点时，$s$ 必须先走到直径上，再走到两端点，肯定也会大于等于 $\lceil \frac{d(G_i)}{2} \rceil$。

而柿子右半部分显然。

所以 $\lceil \frac{d(G_i)}{2} \rceil \le s \le  d(G_i) $。

但是题目要求是小于 $2 \cdot d(G_i)$，限制更加宽松，考虑如何利用这个限制。

设最后答案为 $x$，则 $x \le 2 \cdot s$。

那么我们可以让 $x$ 做为一段询问的答案，直到 $x > 2 \cdot s$，这一部分可以二分求出临界点。

再将 $x$ 赋值为 $s$，则基本相当于把 $x$ 变为 $\lfloor \frac{x}{2} \rfloor$，而 $x$ 属于 $n$ 级别的，所以不同的 $x$ 至多只有 $\log n$ 个。

所以只需要确定一个点，如 $1$，再求出它到所有点的距离的最大值，再二分什么时候需要更改答案，又因为只有 $\log n$ 个不同的 $x$，所以最多只需要二分 $\log n$ 次，时间复杂度 $O(n \log^2 n)$。

**code:**

```
#include<bits/stdc++.h>
#define in inline
#define re register
//#define int long long
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+10;
int h[N],nex[N<<2],to[N<<2],ti[N<<2],tot;
int dis[N],s[N];
bool vis[N];
int n,m,q;
void add(int x,int y,int t){to[++tot]=y,ti[tot]=t,nex[tot]=h[x],h[x]=tot;}
int get(int st,int t){
    if(s[t])return s[t];
    memset(vis,0,sizeof(vis));
    vis[st]=1;dis[st]=0;
    s[t]=max(s[t],dis[st]);
    queue<int>q;
    q.push(st);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=h[u];i;i=nex[i]){
            int v=to[i];
            if(ti[i]>t||vis[v])continue;
            dis[v]=dis[u]+1;
            s[t]=max(s[t],dis[v]);
            vis[v]=1;
            q.push(v);
        }
    }
    return s[t];
}
int main(){
    n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        add(x,y,0),add(y,x,0);
    }
    for(int i=1;i<=q;i++){
        int x=read(),y=read();
        add(x,y,i),add(y,x,i);
    }
    int x=get(1,0),p=1;
    printf("%d ",x);
    while(p<=q){
        int l=p,r=q;
        while(l<=r){
            int mid=l+r>>1;
            if(get(1,mid)*2>=x)l=mid+1;
            else r=mid-1;
        }
        for(int i=p;i<=r;i++)printf("%d ",x);
        p=r+1;x=s[p];
    }
    return 0;
}
```

---

## 作者：小木虫 (赞：5)

### Preface
十分有趣的一道思维题。  
### Problem  
给你一个 $n$ 个点，$m$ 条边的无向图，现在有 $q$ 次加边操作，你需要在一开始以及每一次加边后输出这个无向图的直径的模糊值 $a_i$，使得：  
$$\lceil \frac{d(G_i)}{2} \rceil \leq a_i\leq 2\times d(G_i)$$  
其中 $d$ 表示图的直径，$G_i$ 代表第 $i$ 次加边结束之后的无向图。  
数据范围：$n,m,q\leq 10^5$。
### Solution  
观察这道题，发现这个输出模糊值的设定十分有趣。  
你发现，如果想求出一个无向图的具体直径是 $O(n^2)$ 的，你需要对每一个点开始做一次 BFS 才能求解。  

但是你注意到，你设 $\alpha(G,s)$ 为对于无向图 $G$，从 $s$ 开始 BFS，离他最远的点离他的距离，你会发现无论 $s$ 取什么值， $\alpha(G,s)$ 都始终满足：  
$$\lceil \frac{d(G_i)}{2} \rceil \leq \alpha(G_i,s)\leq d(G_i)$$  
这和模糊值的定义式非常相似。  
关于证明，对于直径上的 $s$，这个结论显然，而对于不在直径上的点，你可以先走到直径上，然后也可以得到这个结论。  

继续探究，你发现对于每一次加边，对于任意 $\alpha(G,s)$ 肯定是变小的。  
你只需要把 BFS 搜索树建出来，这个操作实际上等于移植一棵子树，这最多会导致 $\alpha(G,s)$ 折半。  

你把所有的操作离线下来，由于模糊值的定义式允许你小于等于直径的二倍，那么你自然而然地想到，你一次算出的 $\alpha$ 可以被使用多次，直到直径变为其一半。  
直径太不好处理了，我们干脆把他也变成 $\alpha$，现在问题就是你可以用一个 $\alpha$ 值直到一个时间点，使这个时间点的 $\alpha$ 为它的一半。  
这个太好做了，我们直接可以二分跳到哪个节点。  

然后你发现，由于每一次跳跃会使答案除二，你最多会跳跃 $\log n$ 次，二分后继的复杂度是 $O(\log n)$ 的，你做一次 BFS 计算 $\alpha$ 的复杂度是 $O(n)$ 的，总复杂度就是 $O(n \log ^2 n)$：  

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+10;
int n,m,q,u[N],v[N],dep[N];
vector <int> edge[N];
queue <int> Q;
int BFS(){int res=0;
	for(int i=1;i<=n;i++)
		dep[i]=1e9;
	Q.push(1);dep[1]=0;
	while(Q.size()){
		int u=Q.front();
		for(auto v:edge[u]){
			if(dep[v]>dep[u]+1)
				dep[v]=dep[u]+1,Q.push(v);
		}
		if(Q.size()==1)
			res=dep[u];
		Q.pop();
	}return res;
}
int check(int x){
	for(int i=1;i<=x;i++)
		edge[u[i]].pb(v[i]),edge[v[i]].pb(u[i]);
	int tmp=BFS();//cout<<"debug: "<<x<<" "<<tmp<<endl;
	for(int i=x;i>=1;i--)
		edge[u[i]].pop_back(),edge[v[i]].pop_back();
	return tmp;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>u[0]>>v[0];
		edge[u[0]].pb(v[0]),edge[v[0]].pb(u[0]);
	}for(int i=1;i<=q;i++)cin>>u[i]>>v[i];
	for(int i=0;i<=q;i++){
		int now=check(i);
		int l=i,r=q;
		while(l<r){
			int mid=(l+r+1)/2;
			if(check(mid)*2<now)
				r=mid-1;
			else l=mid;
		}
		for(int j=i;j<=l;j++)cout<<now<<" ";
		i=l;
	}
	return 0;
}
```


---

## 作者：pengyule (赞：5)

这个题帮我纠正了一个误区：图的直径不能通过两次 BFS 求出。

这么看，图的直径的唯一正确求法就是 $O(nm)$ 暴力了？不过两次 BFS 也有它的用武之地（然而主要在这道题）。

一开始，我的第一反应就是这不是二分一下 + 两次 BFS 求图的直径就 $O(n\log n\log q)$ 做完了吗？后来发现图的直径不能 $O(m)$ 求之后稍微猜了一下改了一丁点居然就过了！

具体来说，答案是单调不降的，而由于题目只要求毛估估，所以我们自然考虑当前的这个 $a_i$ 能够尽量用多久。那么 $a_i=\lceil\frac{d_1}{2}\rceil,a_j=2\cdot d_2,a_i=a_j$，解得 $d_2\approx \frac {d_1}{4}$，一共有 $\log_4 n$ 段。

后来发现两次 BFS 过不了样例，但是跟答案“八九不离十”，于是考虑反正 $\log_4 n$ 绰绰有余，不如就把 $a_i:=d_1$ 算了，不用除以二。然后它就过了。复杂度是 $O(n\log_2\log_2q)$，其中 $\log_2 q$ 为二分的复杂度。

**那这个到底为什么对呢？事实上，任意一个点出发的 BFS 树高称作图的半径，而半径和直径之间存在三角不等式 $d\le 2r$。**

哦对另外，只用一次 BFS 就行了，我懒得改了。这道题还是 `*2700` 题里相当水的啊！

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
const int N=1e5+5;
int n,m,q,ans[N];
pair<int,int>e[N];
queue<pair<int,int> >Q;
vector<int>G[N];bool FL;
bool vis[N];
inline pair<int,int> bfs(int st){
	for(int i=1;i<=n;i++)vis[i]=0;
	int ed=st,eds=0;
	Q.push(make_pair(st,0)),vis[st]=1;
	while(!Q.empty()){
		int x=Q.front().first,s=Q.front().second;Q.pop();
		ed=x,eds=s;//if(FL)cerr<<x<<' '<<s<<'\n';
		for(int y:G[x])if(!vis[y])vis[y]=1,Q.push(make_pair(y,s+1));
	}
	return make_pair(ed,eds);
}
inline int gD(){
	return bfs(bfs(1).first).second;
}
inline int calc(int tim){//if(tim==5)FL=1;
	for(int i=1;i<=tim;i++)G[e[i].first].emplace_back(e[i].second),G[e[i].second].emplace_back(e[i].first);
	int ret=gD();
	for(int i=tim;i>=1;i--)G[e[i].second].pop_back(),G[e[i].first].pop_back();//if(tim==5)FL=0;
	return ret;
}
int main(){
	n=read(),m=read(),q=read();
	for(int i=1,u,v;i<=m;i++)u=read(),v=read(),G[u].emplace_back(v),G[v].emplace_back(u);
	for(int i=1;i<=q;i++)e[i].first=read(),e[i].second=read();
	ans[0]=gD();
	for(int now=0,nxt;now<=q;now=nxt){
		int L=now,R=q+1,mid;
		while(L<R-1){
			mid=L+R>>1;
			if(2*calc(mid)>=ans[now])L=mid;
			else R=mid;
		}
		nxt=R;
		if(nxt<=q)ans[nxt]=calc(nxt);
		for(int i=now+1;i<nxt;i++)ans[i]=ans[now];
	}
	for(int i=0;i<=q;i++)cout<<ans[i]<<' ';
}
```

---

## 作者：幽云蓝 (赞：3)

提供一种简单的分治做法。

图的直径太难了，记 $dis(i,j)$ 为 $i$ 和 $j$ 的距离，再记 $p(i)=\max_j\{dis(i,j)\}$，那么我们任意找一个点 $x$ 求出 $p(x)$，若真正的直径为 $d$，那么有 $d\le 2p(x)\le 2d$。方便起见我们取 $1$ 就行。

但我们发现题目要求甚至更松，于是我们再砍个 $\frac{1}{2}$。首先，$p(1)$ 在不断操作后显然是单调变小的。可以想到，我们求出 $i$ 次操作后的 $p(1)$，记其为 $p_i$，同理定义 $p_j$，那么如果 $p_i\le 2p_j$，那么我们不妨用 $p_i$ 替代 $p_j$。

根据上述思路我们可以考虑分治。首先记 $l=0,r=q$，然后求出 $p_l$ 和 $p_r$，在记 $mid=\lfloor\frac{l+r}{2}\rfloor$，求出 $p_{mid}$。查看左右区间，如果有一个区间全部可以用 $p_l$ 或者 $p_{mid}$ 替代了，就不分治它，否则分治下去。

然后就做完了撒花撒花。

---

## 作者：FReQuenter (赞：2)

很有意思的题。

首先明确求图的直径的做法（$O(nm)$）：从每个点进行一次 bfs。

题目的输出非常有意思：直径的 $1/2$ 到 $2$ 倍之间。

单次更新可以通过从当前新加的边开始 bfs 使得总复杂度变为 $O(mq)$。

但是还是不够呀。所以利用输出的性质。

我们考虑在特定的时间节点进行更新。因为每一次更新我们希望至少将答案减少一半。所以最多有 $\log m$ 次更新是必要的。

那么怎么找这么多次更新呢？我们可以二分当前的答案可以用多久。然后就做完了。

复杂度 $O(m \log^{2} q)$。

---

## 作者：DiDi123 (赞：0)

给一点更详细的证明。

对于这道题，大佬们都给出了一个结论，即对于任何一个联通图 $G$ 以及任意一个 $G$ 中的点 $u$，距离 $u$ 最大的点和 $u$ 的距离 $d_u$ 满足 $d_u\geq \lceil \dfrac{d(G)}{2}\rceil$。我们定义直径为长度为 $d(G)$ 的一条链，且该链上所有点之间的最短路都在这条链上。那么对于直径上的一个点，这个结论是显然的。设直径的两个端点为 $s,t$，对于直径外的一个点 $v$，我们需要证明 $\max(dis_{s,v},dis_{t,v})\geq \lceil \dfrac{d(G)}{2}\rceil $。其实我们不一定可以走到直径上，因为有可能不满足最短路的性质，但是我们可以考虑用直径上所有点之间都是最短距离的性质来证明。设直径的长度为 $len$，我们有 $dis_{v,s}+dis_{v,t}\geq len$ 因为如果 $dis_{v,s}+dis_{v,t}< len$，那么直径就不满足 $s$ 和 $t$ 距离最短了，矛盾。

其他的部分就和其他题解一样了，大概就是发现可以只输出 $\log n$ 段，然后二分一下就可以做到 $n\log^2 n$。

---

## 作者：Egg_laying_master (赞：0)

## Description

给定一个 $n$ 个点 $m$ 条边的初始无向图，有 $q$ 次更新，每次更新向图中添加一条边。设 $d(G_i)$ 代表加入 $i$ 条边后的图中两点之间的最大距离，你需要输出 $q+1$ 个整数 $a_0,a_1,\dots,a_q$，满足 $\left\lceil\dfrac{d(G_i)}{2}\right\rceil\le a_i\le 2\cdot d(G_i)$。

$n,m,q\le 10^5$，图连通。

## Solution

首先一个普通图的 $d$ 肯定是不好求的，这题也没有让求，考虑转化。

设 $s_i$ 表示加入 $1\sim i$ 条边，$1$ 到其他点的最长距离，易知 $s_i\leq d(G_i)$。

如果 $1$ 在 $G_i$ 的直径上，则必有 $s_i\geq\left\lceil\dfrac{d(G_i)}{2}\right\rceil$。如果不在直径上的话就先走到直径上，$s_i$ 只会变得更大。

所以 $\left\lceil\dfrac{d(G_i)}{2}\right\rceil\leq s_i\leq d(G_i)$。

显然 $s_i$ 是满足条件的 $a_i$，暴力求就可以做到 $O(n^2)$。

---

观察到 $\left\lceil\dfrac{d(G_i)}{2}\right\rceil\leq s_i\leq d(G_i)$ 的右边界是没有卡满的，甚至只卡到了原来的 $\dfrac{1}{2}$，又因为左边界是递减的，所以考虑让 $s_i$ 代替后面的一部分 $s_j$。

考虑什么条件下 $i$ 能代替 $j(i\leq j)$。

根据上面的式子可得：$\left\lceil\dfrac{d(G_j)}{2}\right\rceil\leq s_j\leq d(G_j)$，$s_i\leq 2\times d(G_j)$。

所以当 $s_i\leq 2\times s_j$ 时 $i$ 能够代替 $j$，即 $s_j\geq \left\lceil\dfrac{s_i}{2}\right\rceil$。由于 $s_i$ 是递减的，所以可以二分 $j$ 找到 $i$ 能**确保**代替的最大的 $j$。

这样做每次 $s_j$ 相比 $s_i$ 会减半，所以最多会二分 $\log n$ 轮，每轮 $\log q$ 次，时间复杂度就是 $O(n\log n\log q)$。

注意：这里 $s_j<\left\lceil\dfrac{s_i}{2}\right\rceil$ 不代表 $i$ 不能代替 $j$，不过不管它对结果没什么影响。

## Code

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

// #define int long long

const int kMaxN = 1e5 + 5;

int n, m, q;
int u[kMaxN], v[kMaxN], s[kMaxN], d[kMaxN];
std::vector<int> G[kMaxN], nG[kMaxN];

int bfs() {
  std::fill(d + 1, d + 1 + n, -1);
  std::queue<int> q;
  q.emplace(1), d[1] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : nG[u]) {
      if (!~d[v]) {
        q.emplace(v), d[v] = d[u] + 1;
      }
    }
  }
  return *std::max_element(d + 1, d + 1 + n);
}

int get(int x) {
  if (~s[x]) return s[x];
  for (int i = 1; i <= n; ++i)
    nG[i] = G[i];
  for (int i = 1; i <= x; ++i)
    nG[u[i]].emplace_back(v[i]), nG[v[i]].emplace_back(u[i]);
  return s[x] = bfs();
}

void dickdreamer() {
  std::cin >> n >> m >> q;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    std::cin >> u >> v;
    G[u].emplace_back(v), G[v].emplace_back(u);
  }
  for (int i = 1; i <= q; ++i)
    std::cin >> u[i] >> v[i];
  std::fill(s, s + 1 + q, -1);
  for (int i = 0, j = 0; i <= q; i = j + 1) {
    int L = i - 1, R = q + 1;
    while (L + 1 < R) {
      int mid = (L + R) >> 1;
      if (get(mid) >= (get(i) + 1) / 2) L = j = mid;
      else R = mid;
    }
    for (int k = i; k <= j; ++k)
      std::cout << get(i) << ' ';
  }
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  // std::cin >> T;
  while (T--) dickdreamer();
  // std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's' << std::endl;
  return 0;
}
```



---

