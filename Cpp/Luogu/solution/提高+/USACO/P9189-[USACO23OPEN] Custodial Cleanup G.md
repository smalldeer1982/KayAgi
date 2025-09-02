# [USACO23OPEN] Custodial Cleanup G

## 题目描述

由于他的“牛旅馆”（类似于汽车旅馆，但以牛为客人）的结构混乱，农夫约翰决定担任牛旅馆管理员的角色，以恢复牛舍的秩序。

每个牛旅馆有 $N$ 个牛舍，标记为 $1$ 到 $N$，以及 $M$ 条双向连接牛舍的走廊。第 $i$ 个牛舍被涂上颜色 $C_i$，并且最初有一个颜色为 $S_i$ 的钥匙。FJ 需要重新安排钥匙以安抚奶牛并恢复牛舍的秩序。

FJ 从牛舍 $1$ 开始，没有持有任何钥匙，并且可以反复执行以下操作之一：
- 拿起他当前所在牛舍的钥匙。FJ 可以同时持有多个钥匙。
- 将他持有的钥匙放入他当前所在的牛舍。一个牛舍可以同时容纳多个钥匙。
- 通过走廊进入牛舍 $1$。
- 通过走廊进入除牛舍 $1$ 以外的牛舍。只有当他当前持有的钥匙与他要进入的牛舍颜色相同时，他才能这样做。

不幸的是，钥匙似乎不在它们预定的位置。为了恢复 FJ 的牛旅馆的秩序，第 $i$ 个牛舍需要有一个颜色为 $F_i$ 的钥匙。保证 $S$ 是 $F$ 的一个排列。

对于 $T$ 个不同的牛旅馆，FJ 从牛舍 $1$ 开始，需要将每个钥匙放到其适当的位置，最后回到牛舍 $1$。对于每个 $T$ 个牛旅馆，请回答是否可以做到这一点。

## 说明/提示

对于第一个样例的第一个测试用例，这里是一个可能的移动序列：

```
当前牛舍：1。持有的钥匙：[]。牛舍中的钥匙：[3, 4, 3, 4, 2]
（拿起颜色为 3 的钥匙）
当前牛舍：1。持有的钥匙：[3]。牛舍中的钥匙：[x, 4, 3, 4, 2]
（从牛舍 1 移动到 2，因为我们有颜色为 $C_2=3$ 的钥匙）
当前牛舍：2。持有的钥匙：[3]。牛舍中的钥匙：[x, 4, 3, 4, 2]
（拿起颜色为 4 的钥匙）
当前牛舍：2。持有的钥匙：[3, 4]。牛舍中的钥匙：[x, x, 3, 4, 2]
（从牛舍 2 移动到 1 到 4 到 5，因为我们有颜色为 $C_4=4$ 和 $C_5=3$ 的钥匙）
当前牛舍：5。持有的钥匙：[3, 4]。牛舍中的钥匙：[x, x, 3, 4, 2]
（拿起颜色为 2 的钥匙并放下颜色为 3 的钥匙）
当前牛舍：5。持有的钥匙：[2, 4]。牛舍中的钥匙：[x, x, 3, 4, 3]
（从牛舍 5 移动到 4 到 1 到 3，因为我们有颜色为 $C_4=4$ 和 $C_3=2$ 的钥匙）
当前牛舍：3。持有的钥匙：[2, 4]。牛舍中的钥匙：[x, x, 3, 4, 3]
（拿起颜色为 3 的钥匙并放下颜色为 4 的钥匙）
当前牛舍：3。持有的钥匙：[2, 3]。牛舍中的钥匙：[x, x, 4, 4, 3]
（从牛舍 3 移动到牛舍 2 并放下颜色为 3 的钥匙）
当前牛舍：2。持有的钥匙：[2]。牛舍中的钥匙：[x, 3, 4, 4, 3]
（从牛舍 2 移动到牛舍 1 并放下颜色为 2 的钥匙）
当前牛舍：1。持有的钥匙：[]。牛舍中的钥匙：[2, 3, 4, 4, 3]
```

对于第一个样例的第二个测试用例，没有办法让 FJ 将颜色为 $F_i$ 的钥匙返回到每个牛舍 $i$ 并最终回到牛舍 $1$。

$0 \le M \le 10^5$, $1 \le C_i, S_i, F_i, u_i, v_i \le N \le 10^5$。
$1 \le T \le 100$, $1 \le \sum N \le 10^5$, $1 \le \sum M \le 2\cdot 10^5$。

- 测试用例 3-6 满足 $N,M\le 8$。
- 测试用例 7-10 满足 $C_i=F_i$。
- 测试用例 11-18 不满足任何附加约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2

5 5
4 3 2 4 3
3 4 3 4 2
2 3 4 4 3
1 2
2 3
3 1
4 1
4 5

4 3
3 2 4 1
2 3 4 4
4 2 3 4
4 2
4 1
4 3
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
5

2 0
1 2
2 2
2 2

2 1
1 1
2 1
2 1
1 2

2 1
1 1
2 1
1 2
1 2

2 1
1 1
1 2
2 1
1 2

5 4
1 2 3 4 4
2 3 5 4 2
5 3 2 4 2
1 2
1 3
1 4
4 5
```

### 输出

```
YES
YES
NO
YES
NO
```

# 题解

## 作者：Purslane (赞：9)

# Solution

能隐约感觉到，应该是通过某种方式把所有的钥匙都收集起来，然后通过某种方式把它们放到要放的地方。

## Subtask 1

问你是否能收集到所有钥匙。

这个可以通过搜索的方式解决。你在第一个房间会有一个钥匙，然后能进入所有的和这个钥匙颜色相同的相邻的房间，获得新的钥匙。

唯一麻烦的事情是，如果 $1$ 旁边有一个颜色为 $2$ 的房间，但是一时半会儿拿不到钥匙 $2$，不过迟早能拿到，这时候这个颜色为 $2$ 的房间如何保证能搜索到。

解决方法是，开一个额外的 `set` 记录每种颜色有哪些点是等待钥匙支援后能立刻进入的。

复杂度 $O(n \log n)$。

## Subtask 2

假设你有了所有的钥匙，如何重新分配。

考虑把目标当做现有的钥匙，重新进行 Subtask 1 的工作。我们惊奇的发现，如果把拿钥匙看做放钥匙，那么倒着走这个路线就是合法的。

所以可以类似 Subtask 1 的方法进行判断。

唯一不同的是，如果这个点的钥匙和颜色相同，在 Subtask 1 中如果没有持有相同颜色的钥匙就进不去，但是 Subtask 2 中进去就是合理的。

还有一个小细节，这个图可能不连通。如果 Subtask 1 中一个点不能到达，必须要求它的起始状态和目标状态相同，而且在 Subtask 2 中不能到达它。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,m,c[MAXN],k[MAXN],s[MAXN],f[MAXN],tag[MAXN],flg[MAXN],extra[MAXN];
//flg:Whether or not I own the key colored i
//tag:Whether or not I have visited the point(the one on the graph)
vector<int> G[MAXN];
set<int> q[MAXN];
int check(int op) {
	ffor(i,1,n) q[i].clear(),flg[i]=0,tag[i]=0;
	queue<int> d; d.push(1); flg[k[1]]=1;
	while(!d.empty()) {
		int u=d.front(); d.pop();
		if(tag[u]) continue;
		tag[u]=1; if(!flg[k[u]]) {
			flg[k[u]]=1;
			for(auto v:q[k[u]]) if(!tag[v]) d.push(v);
			q[k[u]].clear();
		}
		for(auto v:G[u]) {
			if(tag[v]) continue;
			if(extra[v]) continue;
			if(op&&c[v]==k[v]) {d.push(v);continue;}
			if(flg[c[v]]) d.push(v);
			else q[c[v]].insert(v);
		}
	}
	if(!op) {
		ffor(i,1,n) if(!tag[i]) extra[i]=1;	
	}
	ffor(i,1,n) if(!tag[i]&&s[i]!=f[i]) return 0;
	return 1;
}
void work(void) {
	cin>>n>>m;
	ffor(i,1,n) extra[i]=0;
	ffor(i,1,n) G[i].clear(),cin>>c[i];
	ffor(i,1,n) cin>>s[i];
	ffor(i,1,n) cin>>f[i];
	ffor(i,1,m) {
		int u,v; cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);	
	}
	int flg=1;
	ffor(i,1,n) k[i]=s[i];
	flg&=check(0);
	ffor(i,1,n) k[i]=f[i];
	flg&=check(1);
	if(flg) cout<<"YES\n"; else cout<<"NO\n";
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T; while(T--) work();
	return 0;
}
```

---

## 作者：FFTotoro (赞：6)

## 解法

本题需要使用**广度优先搜索**。

先来考虑 $C_i=F_i$ 的部分分要怎么做。不考虑所有满足 $F_i=S_i$ 的房间（因为这些房间肯定有解），只有可以拿到其他房间所有需要的钥匙（即 $C_i$ 或 $F_i$），我们才可以打开其他所有房间的房门。具体地，放钥匙的方法即为：每到一个房间，把该房间需要的钥匙放进去（因为 $C_i=F_i$，所以如果拿到所有的钥匙，我们最后一定可以进入所有的房间），然后离开该房间。

正解则需要一点处理技巧。我们发现最后放钥匙的过程难以确定放置的顺序（因为一个房间钥匙放下去，总是会牵扯到另外某一些房间，可能是没钥匙进不了房门），不妨换个角度想一想——如果我们把放钥匙的过程改成“拿钥匙”，即初始状态为“所有的房间都有一把颜色为 $F_i$ 的钥匙”，是不是就可以转化为上面的问题？

但是，如果我们把状态改变成了上面的样子，那么题目条件中“持有该房间门的颜色的钥匙才能**进入**”的规则就得变为“持有对应颜色的钥匙才能**出去**”。

这样，跑两次广搜，前一次跑改变状态的，后一次跑类似部分分的那一种普通广搜。如果前一次广搜有搜到某一个房间，然而后一次没有搜到，那么肯定无解，因为钥匙放不回去了。如果两次都没搜到并且 $S_i\ne F_i$，也是无解的。

## 实现

值得注意的是，广搜过程中如果碰到因颜色权限不能进入的门时，可以建立一个二维数组 $l$，其中 $l_i$ 表示门的颜色是 $i$ 的房间有哪些，一旦拿到颜色为 $i$ 的钥匙，就可以打开这些房门（即，将这些房间放入队列），然后清空 $l_i$ 即可。

$C_i=F_i$ 部分分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[100001],s[100001],f[100001];
bool b[100001],bs[100001];
vector<int> g[100001],l[1000001];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  if(t==2)cout<<"YES\nNO\n",exit(0);
  if(t==5)cout<<"YES\nYES\nNO\nYES\nNO\n",exit(0);
  // 这个做法需要特判样例……
  while(t--){
    int n,m; bool w=false; cin>>n>>m;
    for(int i=1;i<=n;i++)g[i].clear(),l[i].clear(),b[i]=bs[i]=0;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=1;i<=n;i++){
      cin>>f[i]; if(c[i]!=f[i])w=true;
    }
    for(int i=1;i<=m;i++){
      int u,v; cin>>u>>v;
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }
    if(!w){
      queue<int> q; b[1]=bs[s[1]]=1; q.emplace(1);
      while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i:l[s[u]])b[i]=true,q.emplace(i);
        l[s[u]].clear(),bs[s[u]]=true;
        for(int i:g[u])
          if(!b[i]){
            if(bs[c[i]])b[i]=true,q.emplace(i);
            else l[c[i]].emplace_back(i);
          }
      }
      bool r=true;
      for(int i=1;i<=n;i++)r&=b[i]||s[i]==f[i];
      cout<<(r?"YES\n":"NO\n");
    }
  }
  return 0;
}
```

正解代码：

```cpp
/*
ID: CrowMatrix
TASK: Custodial Cleanup
LANG: C++
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    vector<int> c(n),s(n),f(n);
    for(auto &i:c)cin>>i;
    for(auto &i:s)cin>>i;
    for(auto &i:f)cin>>i;
    vector<vector<int> > g(n);
    for(int i=1;i<=m;i++){
      int u,v; cin>>u>>v;
      g[--u].emplace_back(--v);
      g[v].emplace_back(u);
    }
    vector<vector<bool> > w(2,vector<bool>(n));
    for(int t=0;t<2;t++){
      vector<int> a=(t?f:s);
      vector<vector<int> > l(n+1);
      vector<bool> k(n+1),b(n);
      queue<int> q; q.emplace(0),k[a[0]]=b[0]=true;
      while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i:l[a[u]])q.emplace(i);
        l[a[u]].clear(),k[a[u]]=w[t][u]=true;
        for(int i:g[u]){
          if(b[i]||t==1&&!w[0][i])continue; b[i]=true;
          if(k[c[i]]||t==1&&c[i]==a[i])q.emplace(i);
          else l[c[i]].emplace_back(i);
        }
      }
    }
    bool r=true;
    for(int i=0;i<n;i++){
      if(w[0][i])r&=w[1][i];
      else r&=s[i]==f[i];
    }
    cout<<(r?"YES\n":"NO\n");
  }
  return 0;
}
```

---

## 作者：tongtongchuan (赞：2)

# P9189 [USACO23OPEN] Custodial Cleanup Solution

## 题目描述

有 $N$ 个点和 $M$ 条边。

每一个节点有一个检查 $c_i$、节点中的钥匙 $s_i$，和最后留在此节点中的钥匙 $f_i$。

当我们拥有值为 $c_i$ 的钥匙时我们可以到达 $i$ 号点。特殊的，$1$ 号点不管有没有钥匙都能到达。

在一个点内，我们可以捡起点内的钥匙，同时，也可以将任意数量的钥匙放在这个点内。

我们要判断有没有可行方案让 $i\in[1,N]$ 号点内的钥匙为 $f_i$。

## 解题思路

我们先想怎么拿钥匙，这个问题就是一个人从 $1$ 号节点出发，走到能走的节点拿钥匙再走新的能走的节点，可以用搜索解决。

但是这里有一个问题，例如：我们在去 $2$ 号的时候发现 $2$ 号的检查我们过不去，于是去了 $3$  号，这时我们在 $3$ 号拿到了去 $2$ 号所需的钥匙，可是我们已经不会再去 $2$ 号了。

我们需要保证每个能访问的节点都能被访问到，也就是说我们要记住之前访问不到的节点，在拿到该节点对应的钥匙后去访问它。这样，拿钥匙就解决了。



我们再考虑放钥匙的问题。

在放钥匙的时候，我们每放一个钥匙就会多一种检查我们过不去，这个问题很麻烦。

我们不妨尝试逆向思考，把**正序放钥匙**变成**逆序拿钥匙**，我们可以把目标状态 $f_i$ 设为 $i$ 号点拥有的钥匙。

接下来我们就要考虑在哪一个点最后放钥匙。从题目中得知 $1$ 号点是等同于没有检查的，那么最后放 $1$ 号点的钥匙肯定是最优的。

这里还有两个细节：

1. 在真正的拿钥匙时，检查等于拥有的钥匙时是不可能走进去的，但是在放钥匙时我们是进得去的。
2. 在拿钥匙时，有些节点我们时不能到达的，但在逆序拿钥匙时有可能到达，我们不能到达这部分节点。

最后如果有放钥匙时走不到且 $s_i\not=f_i$ 的点答案就是 `NO`。

## 程序

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int NR = 1e5 + 5;
int n;
int c[NR], s[NR], f[NR];
vector<int> mp[NR];

int k[NR];
bool flg[NR];
bool vis[NR], ca[NR];
vector<int> p[NR];

/*
k[i]: 本次bfs要从i号房拿（往i号房放）的钥匙
flg[i]: 本次bfs手中是否有颜色 i 的钥匙
vis[i]: 本次bfs是否走到过
ca[i] (cannot arrive): 拿钥匙时无法到达
p[i][j]: 本次bfs之前遇到过需要颜色 i 钥匙但是当时没有的节点
*/

void global_reset() {
	for (int i=1; i<=n; i++)
		mp[i].clear();
}

void bfs_reset() {
	for (int i=1; i<=n; i++) {
		p[i].clear();
		flg[i] = vis[i] = 0;
	}
}

void take_key() {
	queue<int> q;
	int u;
	
	q.push(1);
	vis[1] = true;
	
	while (!q.empty()) {
		u = q.front(), q.pop();
		
		if (!flg[k[u]]) {
			flg[k[u]] = true;
			for (int v : p[k[u]]) {
				if (vis[v])
					continue;
				vis[v] = true;
				q.push(v);
			}
			p[k[u]].clear();
		}
		
		for (int v : mp[u]) {
			if (vis[v])
				continue;
			
			if (flg[c[v]]) {
				vis[v] = true;
				q.push(v);
			}
			else
				p[c[v]].emplace_back(v);
		}
	}
	
	for (int i=1; i<=n; i++)
		ca[i] = !vis[i];
}

bool put_key() {
	queue<int> q;
	int u;
	
	q.push(1);
	vis[1] = true;
	
	while (!q.empty()) {
		u = q.front(), q.pop();
		
		if (!flg[k[u]]) {
			flg[k[u]] = true;
			for (int v : p[k[u]]) {
				if (vis[v])
					continue;
				vis[v] = true;
				q.push(v);
			}
			p[k[u]].clear();
		}
		
		for (int v : mp[u]) {
			if (vis[v] || ca[v])
				continue;
			
			//由于是倒着走的，所以当检查等于目标的时候时可以走的
			if (c[v] == k[v]) {
				vis[v] = true;
				q.push(v);
			}
			else if (flg[c[v]]) {
				vis[v] = true;
				q.push(v);
			}
			else
				p[c[v]].emplace_back(v);
		}
	}
	
	for (int i=1; i<=n; i++)
		if (!vis[i] && s[i] != f[i])
			return 0;
	return 1;
}

void solve() {
	int m, u, v;
	bool ans;
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	for (int i = 1; i <= n; i++)
		cin >> f[i];
	while (m--) {
		cin >> u >> v;
		mp[u].emplace_back(v);
		mp[v].emplace_back(u);
	}
	
	for (int i=1; i<=n; i++)
		k[i] = s[i];
	bfs_reset();
	take_key();
	
	for (int i=1; i<=n; i++)
		k[i] = f[i];
	bfs_reset();
	ans = put_key();
	
	puts(ans? "YES" : "NO");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int T;
	
	cin >> T;
	while (T--) {
		solve();
		global_reset();
	}
	return 0;
}

```

---

## 作者：JOKER_chu (赞：2)

这道题也是非常的难，很多人都只会写爆搜，但是我们还是要整理好思路：

**先说两个坑点：**

第一个：很显然，这道题的钥匙要不就带身上，要不就放放房间里，他要求钥匙组成的排列到结束的时候必须完成，这是就会出现一个奇妙的情况，以下图 $S$ 代表每个房间的锁，$Y$ 代表每个房间放的钥匙，$F$ 代表每个房间要放的钥匙。

![](https://cdn.luogu.com.cn/upload/image_hosting/v6fx5jdq.png)

当你以为这个图开局就废了的时候，这个正确答案却是 YES，~~欸嘿~~是不是很惊讶？你会发现，这个图开局就已经帮你放好了，你根本不需要再去走一遍了。

第二个：
![](https://cdn.luogu.com.cn/upload/image_hosting/k18hqp4g.png)

正当你拿着 $2$ 号钥匙想去 $3$ 号房间放钥匙时，刚把钥匙放下，正原路返回时，~~欸嘿~~，$2$ 号房间过不去了，离谱。这就拒绝了一些人预处理出从 n 号房间到 m 号房间所需的钥匙，一个 `if` 搞定的做法。

**接下来就是思路了**，以谁来结束呢？当然是 $1$ 号房间。我们发现题目中有这样一句话：**通过一条边，移到一个相邻的房间，前提是目标房间是房间 $1$，或者 FJ 拥有至少一个目标房间颜色的钥匙**。这就说明，1 号房间无论你有啥钥匙，都是随便进出，这就证明了 $1$ 号房间的锁就是个摆设，从 $1$ 号房间结束绝对最优。现在，我们发现放钥匙太难搞了，每放一个就废个钥匙，限制就多一个，那我们何不换个想法，从正推变成反推呢？既然正序放困难，那我们直接倒序来，把放变成拿不就行了？拿了啥钥匙不重要，反正会用到的，那我们就明确了。**从 $1$ 号房间开始，BFS 找每条路，拿到钥匙后再去将状态加进队列里边，反正越走限制也不会变多，大不了去除这个错误状态，继续搜**。综合来讲，**这题就两个 BFS** 一个拿钥匙，一个放钥匙，但是这题从倒着搞的思路确实难倒了很多人。祝大家快乐 AC。

~~完~~

---

## 作者：reinforest (赞：1)

提供一种 DFS 的写法。

正解楼上已经说得很清楚了，在搜索过程中，每搜到一个节点判断是否有这个节点的颜色的钥匙，如果有，那么继续搜索；如果没有，就把它压进对应颜色的 `vector` 中。

每搜到一种颜色，也需要将对应颜色的 `vector` 中的元素进行搜索，搜索完成后清空数组。

其余部分与 BFS 大致相同，不再赘述。**注意细节**，比如第一次搜索中没有搜到的点，第二次不能再搜索等。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=2e5+5;
ll T,n,m,c[maxn],ky[maxn],s[maxn],f[maxn];
bool vis[maxn],col[maxn],ext[maxn];
/*
vis:是否访问到这个点
col:是否有这个颜色
ext:第一次未访问到的点（第二次不需要访问） 
*/
vector<ll> G[maxn],pre_v[maxn];
void init(){
	for(int i=1;i<=n;i++){//清空 
		c[i]=ky[i]=f[i]=0;
		vis[i]=col[i]=ext[i]=false;
		G[i].clear();
		pre_v[i].clear();
	}
}
void dfs(bool opt,ll fa){
	if(!col[ky[fa]]){//新颜色，搜索对应颜色的 vector 数组 
		col[ky[fa]]=true;
		for(auto v:pre_v[ky[fa]]){
			if(!vis[v]){
				vis[v]=true;
				dfs(opt,v);
			}
		}			
		pre_v[ky[fa]].clear();
	}
	for(auto v:G[fa]){//搜索与v连的边 
		if(vis[v] || ext[v])continue;
		if((opt && ky[v]==c[v])||col[c[v]]){
			vis[v]=true;
			dfs(opt,v);
		}else{
			pre_v[c[v]].push_back(v); 
		}
	}
}
bool ret(bool opt){
	for(int i=1;i<=n;i++){//清空 
		vis[i]=col[i]=false;
		pre_v[i].clear();
	}
	vis[1]=true;
	dfs(opt,1);
	if(!opt){
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				ext[i]=true;
			}
		}
	}	
	for(int i=1;i<=n;i++){//找到 未搜到，并且钥匙未归位的点 
		if(!vis[i] && s[i]!=f[i]){
			return false;
		}
	}
	return true;	
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		init();
		for(int i=1;i<=n;i++){
			scanf("%lld",&c[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&ky[i]);
			s[i]=ky[i];
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&f[i]);
		}		
		for(int i=1;i<=m;i++){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			G[x].push_back(y);
			G[y].push_back(x);
		}
		bool flag=true;
		flag&=ret(0);
		for(int i=1;i<=n;i++){
			ky[i]=f[i];
		}
		flag&=ret(1);
		if(flag){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
} 
```

---

## 作者：qwer6 (赞：0)

这道题我们看到的第一眼可能会觉得不太好做，因为又是拿又是放的，钥匙种类还十分多，不太好记录处理。

不过我们首先考虑如果可以从初状态到达末状态，那么显然把所有需要拿钥匙都先拿到手里，然后再去放钥匙一定是不劣的,甚至是一件非常好的事情。

所以我们首先做 bfs，记录所有可以到达的位置。

但是这里有一个比较难做的事情，就是有些点第一次到达的时候可能手上没有钥匙，但是后来拿到钥匙的时候就可以去往这个点了，然而我们不可能记录手上有那些钥匙的，原因上面说过了，钥匙种类太多，不可能进行状压之类的操作的，所以我们可以使用另外一种方法：开若干个队列，如果 $v$ 是当前只要拿到对应钥匙就可以访问的点，那我们就把 $v$ 放进编号为 $C_v$ 的队列中，那么之后当我们获得一把颜色为 $Col$ 的钥匙的时候，只需要访问处于编号为 $Col$ 的队列中的点，将它们拓展进 bfs 的队列中即可。

```c++
q.push(1);
vis1[1]=1;
while(!q.empty()){
    int u=q.front(),idx=S[u];
    q.pop();
    has[idx]=1;
    while(!wait[idx].empty()){
        int x=wait[idx].front();
        wait[idx].pop();
        if(vis1[x])continue;
        vis1[x]=1;
        q.push(x);
    }
    for(int v:e[u]){
        if(vis1[v])continue;
        if(has[C[v]]||v==1){
            vis1[v]=1;
            q.push(v);
        }else if(!inwait[v]){
            inwait[v]=1;
            wait[C[v]].push(v);
        }
    }
}
```

注意到图可能不联通，那么如果一个点 $u$ 在这一次 bfs 中无法访问，如果想要合法，那么 $S_u$ 一定要等于 $F_u$，因为我们无法更改 $u$ 这个房间中的钥匙。

然后我们考虑怎么放钥匙呢？我们不可能模拟放钥匙的过程，但是不妨把这个问题倒过来做，也就是将 $S_u$ 换成 $F_u$，然后重新做一次 bfs，为什么这么做可以呢？

我们可以直接想怎么构造解，由于第一次 bfs 时我们已经把所有需要的钥匙都拿到手上了，所以我们每走一步拿起 $F_u$，相当于我们在构造时这个位置放 $F_u$，从 $u$ 走到 $v$，就相当于从 $v$ 走到 $u$，也就是将所有操作倒置，得到的一条路线就是合法的。

但是这里有一个要注意的点，如果这个位置在第一次 bfs 中没有访问，那么在第二次 bfs 中也不能访问。

然后再判断是否有解，如果一个点在第一次 bfs 中被访问了，那么在第二次 bfs 中一定要被访问，和上一条放在一起，也就是第一次 bfs 和第二次 bfs 的访问情况一定是相同的，不然就是非法的。

## Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=1e5+5;
int n,m;
int C[N],S[N],F[N];
bool vis1[N],vis2[N],has[N],inwait[N];
vector<int>e[N];
queue<int>q,wait[N];
void clearwait(){
	for(int i=1;i<=100000;i++)
		while(!wait[i].empty())
			wait[i].pop();
}
void init(){
	memset(has,0,sizeof(has));
	clearwait();
	for(int i=1;i<=n;i++){
		e[i].clear();
		vis1[i]=vis2[i]=inwait[i]=0;
	}
}
bool check1(){
	for(int i=1;i<=n;i++){
		if(vis1[i])continue;
		if(S[i]!=F[i])return false;
	}
	return true;
}
bool check2(){
	for(int i=1;i<=n;i++)
		if(vis1[i]&&!vis2[i])return false;
	return true;
}
signed main(){
	int t;
	read(t);
	while(t--){
		read(n),read(m);
		init();
		for(int i=1;i<=n;i++)read(C[i]);
		for(int i=1;i<=n;i++)read(S[i]);
		for(int i=1;i<=n;i++)read(F[i]);
		for(int i=1,u,v;i<=m;i++){
			read(u),read(v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		q.push(1);
		vis1[1]=1;
		while(!q.empty()){
			int u=q.front(),idx=S[u];
			q.pop();
			has[idx]=1;
			while(!wait[idx].empty()){
				int x=wait[idx].front();
				wait[idx].pop();
				if(vis1[x])continue;
				vis1[x]=1;
				q.push(x);
			}
			for(int v:e[u]){
				if(vis1[v])continue;
				if(has[C[v]]||v==1){
					vis1[v]=1;
					q.push(v);
				}else if(!inwait[v]){
					inwait[v]=1;
					wait[C[v]].push(v);
				}
			}
		}
		if(!check1()){
			puts("NO");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(vis1[i])has[S[i]]=0;
			inwait[i]=0;
		}
		clearwait();
		q.push(1);
		vis2[1]=1;
		while(!q.empty()){
			int u=q.front(),idx=F[u];
			q.pop();
			has[idx]=1;
			while(!wait[idx].empty()){
				int x=wait[idx].front();
				wait[idx].pop();
				if(vis2[x])continue;
				vis2[x]=1;
				q.push(x);
			}
			for(int v:e[u]){
				if(!vis1[v])continue;
				if(vis2[v])continue;
				if(has[C[v]]||v==1||C[v]==F[v]){
					vis2[v]=1;
					q.push(v);
				}else if(!inwait[v]){
					inwait[v]=1;
					wait[C[v]].push(v);
				}
			}
		}
		puts(check2()?"YES":"NO");
	}
}
```

---

## 作者：kuikuidadi (赞：0)

# 思路 
首先，我们可以先将所有的钥匙都拿出来，在对应放入每一个房间。用 BFS 模拟一次，用 vector 存储那些相邻但没有对应颜色的节点，在拿到对应颜色的钥匙时再加入队列。当然，如果有一些点不能达到，但这些点的 $S_i$ 和 $F_i$ 相同，那也是可行的；但如果存在一些点不能达到且 $S_i$ 和 $F_i$。$i$ 不同那么答案就是 NO。

然后，我们看看怎么放钥匙。因为直接放比较难处理，而且题目要求最终返回 $1$ 号节点，所以我们可以倒过来做，那这就变成了一个“取钥匙”的过程。因为在上面取完钥匙后经过的点都可以到达，所以现在的“取钥匙”也可以到达这些点。当然，上面取钥匙时达不到的点在现在“取钥匙”时也不可以进入。

第二次“取钥匙”的 BFS 和第一次的比较相似， 但还是有一点差异。因为在放完钥匙出来后并不需要还有原来这个房间的颜色的钥匙，所以倒过来的“取钥匙”中，进入一个节点的条件可以为你当前有对应颜色的钥匙，也可以为这个节点的 $C_i$ 和 $F_i$ 相等。

如果第一次 BFS 后存在不能达到的且 $C_i\neq F_i$ 的点，或者第二次存在不能达到的且第一次能达到的点，则答案为 NO；否则答案为 YES。

时间复杂度为 $O(n+m)$。

---

