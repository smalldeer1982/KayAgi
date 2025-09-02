# Intersecting Subtrees

## 题目描述

你正在和 Li Chen 玩一个奇怪的游戏。你们有一棵包含 $n$ 个节点的树画在纸上，所有节点都是无标号且可区分的。你们每个人都独立地将树的节点标号为 $1$ 到 $n$。你们彼此都不知道对方的标号方式。

你和 Li Chen 各自选择了树上的一个子树（即一个连通子图）。你的子树包含你标号下的 $x_1, x_2, \ldots, x_{k_1}$ 这些节点，Li Chen 的子树包含他标号下的 $y_1, y_2, \ldots, y_{k_2}$ 这些节点。$x_1, x_2, \ldots, x_{k_1}$ 和 $y_1, y_2, \ldots, y_{k_2}$ 的值你们双方都知道。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044B/f8d6eab9a505e94e56f3fbc02db7e9ddfae952fb.png) 图中展示了同一棵树的两种标号方式：左侧是你的标号，右侧是 Li Chen 的标号。高亮部分是你们各自选择的子树。两棵子树有两个公共节点。

你想要判断你们的子树是否至少有一个公共节点。幸运的是，你的朋友 Andrew 同时知道你们两个人的标号方式。你最多可以向 Andrew 询问 $5$ 个问题，每个问题有以下两种形式之一：

- A x：Andrew 会查看你标号下的节点 $x$，并告诉你该节点在 Li Chen 标号下的编号。
- B y：Andrew 会查看 Li Chen 标号下的节点 $y$，并告诉你该节点在你的标号下的编号。

请在询问一些问题后，判断你们的子树是否有至少一个公共节点。如果有，请输出你标号下的任意一个公共节点编号。

## 说明/提示

对于第一个样例，Li Chen 的隐藏排列为 $[2, 3, 1]$，对于第二个样例，他的隐藏排列为 $[5, 3, 2, 4, 1, 6]$。

在第一个样例中，树为一条三节点的链。上方是你的标号和你选择的子树，下方是 Li Chen 的标号和他选择的子树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044B/20da1d3951c06c9ea90b744aab9f3033dac72c43.png)在第一个问题中，你询问 Andrew 你标号下的节点 $1$ 在 Li Chen 标号下的编号，Andrew 回答 $2$。此时你知道你们的子树包含同一个节点（即你标号下的节点 $1$），所以你可以输出 "C 1" 并结束。当然，你也可以询问 Andrew Li Chen 标号下的节点 $2$ 在你标号下的编号，Andrew 回答 $1$（这一步只是为了演示如何提问）。

对于第二个样例，有两组测试数据。第一组如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044B/f8d6eab9a505e94e56f3fbc02db7e9ddfae952fb.png)我们首先询问 "B 2"，Andrew 会告诉我们 $3$。此时我们知道 $3$ 是一个公共节点，而且任何包含节点 $3$ 的大小为 $3$ 的子树必然包含节点 $1$，所以我们可以输出 "C 1" 或 "C 3" 作为答案。

第二组测试数据如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044B/90d5b00e08570be05b2931735d98bbcd805bf31f.png)在这种情况下，你知道唯一一个不包含节点 $1$ 的大小为 $3$ 的子树是 $4,5,6$。你询问 Andrew 你标号下的节点 $1$ 在 Li Chen 标号下的编号，Andrew 回答 $5$。此时你知道 Li Chen 的子树不包含节点 $1$，所以他的子树一定是 $4,5,6$（在你的标号下），因此两棵子树没有公共节点。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
3
1 2
2 3
1
1
1
2
2
1
```

### 输出

```
A 1
B 2
C 1
```

## 样例 #2

### 输入

```
2
6
1 2
1 3
1 4
4 5
4 6
4
1 3 4 5
3
3 5 2
3
6
1 2
1 3
1 4
4 5
4 6
3
1 2 3
3
4 1 6
5
```

### 输出

```
B 2
C 1
A 1
C -1
```

# 题解

## 作者：ZMQ_Ink6556 (赞：4)

## 题解：CF1044B Intersecting Subtrees

### 题意简述

给你一棵树，你和对方都有各自不同的树的节点的编号方式，每个人选择一些节点染色。你可以询问你的节点 $x$ 在对方的编号方法中的编号或对方的节点 $x$ 在你的编号方法中的编号。最多询问 $5$ 次。保证双方染色的节点各自成为一个连通图。请你找出一个双方都染色的点或者报告不存在这样的点。

### 解题思路

首先，你可以看到自己染色的点，因为其联通，所以应该是这样的结构：

![pic1](https://cdn.luogu.com.cn/upload/image_hosting/pahyvjm7.png)

此时，你可以询问对方任意一个染色的点在你的编号方式下的编号（为了方便观察，我们假定这棵树有两个方向，左边和右边），那么会出现以下两种情况：

![pic2](https://cdn.luogu.com.cn/upload/image_hosting/00vlqr1n.png)

![pic3](https://cdn.luogu.com.cn/upload/image_hosting/ynn5j0w4.png)

这时，我们可以用搜索找到一个离目前已知的对面对应我们的点进行一次搜索，深搜或广搜均可。

**贪心**的选择离这个点**最近的你染色的点**，如果这个点对方也染色了，那么即为答案，否则输出 `-1`。

正确性理解：

- 情况 $1$，左右都有点：因为原图是一棵树，所以你的点会将树分割成左右两个部分，而因为要求联通，所以必定有点重合。
- 情况 $2$，只在一边：仍然因为原图是一棵树，所以我们贪心选择的这个点会将树分成左右两个部分。如果有其他点为答案，则必定有一条路径连接我们初始查找的点和那个答案，则转化为情况 $1$。反之，如果这个点不是答案，则必然没有答案。

特判提示：如果你第一次询问到的点恰好你也染色了，直接输出即可。

最多使用 $2$ 次询问，复杂度 $\mathcal O(n)$，可以通过此题。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , k1 , k2 , a[1005] , x[1005] , y[1005] , mte[1005] , ysy , mind , pl;
vector<int> mp[1005];
bool srl[1005] , rdw[1005];
inline void add(int u , int v)
{
	mp[u].push_back(v);
	return;
}
inline void fill(int p , int deep)
{
	if(mte[p] != -1)
	{
		return;
	}
	mte[p] = deep;
	for(int i = 0 ; i < mp[p].size() ; i++)
	{
		fill(mp[p][i] , deep + 1);
	}
	return;
}
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			mp[i].clear();
		}
		for(int i = 1 ; i < n ; i++)
		{
			int u , v;
			cin >> u >> v;
			add(u , v);
			add(v , u);
		}
		memset(srl , 0 , sizeof(srl));
		memset(rdw , 0 , sizeof(rdw));
		for(int i = 1 ; i <= n ; i++)
		{
			mte[i] = -1;
		}
		cin >> k1;
		for(int i = 1 ; i <= k1 ; i++)
		{
			cin >> x[i];
			srl[x[i]] = 1; 
		}
		cin >> k2;
		for(int i = 1 ; i <= k2 ; i++)
		{
			cin >> y[i];
			rdw[y[i]] = 1;
		}
		cout << "B " << y[1] << endl;
		cin >> ysy;
		if(srl[ysy])
		{
			cout << "C " << ysy << endl;
			continue;
		}
		fill(ysy , 0);
		mind = 1000000007;
		pl = -1;
		for(int i = 1 ; i <= n ; i++)
		{
			if(mte[i] < mind && srl[i])
			{
				mind = mte[i];
				pl = i;
			}
		}
		cout << "A " << pl << endl;
		cin >> ysy;
		if(rdw[ysy])
		{
			cout << "C " << pl << endl;
			continue;
		}
		cout << "C -1" << endl;
	}
	return 0;
}
```

---

## 作者：FFTotoro (赞：4)

这题需要一些对树形结构的了解。

先从已知的 Li Chen 的树上有染色的点随便选一个来询问它在“我”的树上的编号，如果该点被染色，答案即为该点。如果该点没有被染色，找出在“我”的树上离这个最近的有染色的点再进行一次询问，如果 Li Chen 的树上的该点有染色那么该点就是答案，否则无解。

尝试证明为什么如果 Li Chen 的树上第二次询问的点没有染色一定无解。显然“我”的树上有染色的点构成的子树把整个树的没染色的点分成了若干棵**互不相交**的子树，第二次询问的点即为 Li Chen 的子树和“我”的子树**有可能**相交的地方。如果 Li Chen 的这个点没有被染色，那么 Li Chen 的子树必然被“我”的有染色子树隔绝在了那互不相交的子树中的一个之中，不可能再通过其他的点和“我”的有染色子树相交。

时间复杂度 $O(Tn)$，询问次数最多为 $2$，足以通过题目。

代码实现较为容易。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,s; cin>>n;
    vector<vector<int> > g(n);
    vector<bool> b(n),b2(n),v(n);
    for(int i=1;i<n;i++){
      int u,v; cin>>u>>v;
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }
    int k; cin>>k;
    while(k--){
      int x; cin>>x;
      b[x-1]=true;
    }
    cin>>k;
    while(k--){
      int x; cin>>x;
      b2[s=x-1]=true;
    }
    cout<<"B "<<s+1<<endl;
    cin>>s;
    if(b[--s]){
      cout<<"C "<<s<<endl;
      continue;
    } // 第一轮的点就满足条件
    queue<int> q;
    q.emplace(s),v[s]=true;
    while(!q.empty()){
      int u=q.front(); q.pop();
      if(b[u]){s=u+1; break;}
      for(int i:g[u])
        if(!v[i])v[i]=true,q.emplace(i);
    } //  BFS 找最近的点
    cout<<"A "<<s<<endl;
    int x; cin>>x;
    if(b2[x-1])cout<<"C "<<s<<endl;
    else cout<<"C -1"<<endl;
  }
  return 0;
}
```

---

## 作者：rui_er (赞：1)

有意思的交互题。

题意：

多测。

你和 Li Chen 各有一棵形态相同但标号不一定相同的树，你们分别选择了一个连通块，你知道你的树的节点编号、你选择的连通块每个点在你的树上的编号、Li Chen 选择的连通块每个点在他的树上的编号。

你可以用 `A x` 询问你的树上编号为 $x$ 的点在他的树上的编号，或者用 `B x` 询问他的树上编号为 $x$ 的点在你的树上的编号，最多进行 $5$ 次询问。你需要用 `C x` 给出一个点 $x$（在你的树中的编号），使得它既在你的连通块里，也在 Li Chen 的连通块里，或者告诉我这样的点不存在。

---

我们可以先随便找一个 Li Chen 选了的点，然后询问在我的树上的编号。如果这个点我也选了，运气很好，直接输出答案即可。

但是如果我没选呢？

因为选的点都是连通的，而这个点没有被我选，说明我选的连通块一定在这个点为根的 **一个** 子树内，此时的树如图：（蓝色是那个 Li Chen 选的点，绿色是我选的连通块）

![](https://cdn.luogu.com.cn/upload/image_hosting/9eroudmk.png)

此时我的连通块中所有点的最近公共祖先一定也在连通块内，即图中最右边子树的根，可以通过一次 dfs 或者 bfs 来找到，我用的 bfs。

我们可以询问这个点在 Li Chen 的树中的编号，判断这个点是否在他的连通块内，如果在那这个点就是公共点，否则的话 Li Chen 的连通块在这个点的另一侧，而这个点没有取，所以我选的连通块子树的所有点都不能取到（因为取的所有点连通）。此时两个连通块没有交集。

对于每组数据：使用 $2$ 次询问，时间复杂度 $O(n)$。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 1e3+5; 

int T, n, colA[N], colB[N], vis[N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}
vector<int> a, b, e[N];
int ask(char op, int val) {
	printf("%c %d\n", op, val);
	fflush(stdout);
	int res = 0;
	if(op != 'C') {
		scanf("%d", &res);
		if(res == -1) exit(0);
	}
	return res;
}
int bfs(int s) {
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(colA[u]) return u;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int v : e[u]) {
			if(!vis[v]) q.push(v);
		}
	}
	return -1;
}

int main() {
	for(scanf("%d", &T);T;T--) {
		scanf("%d", &n);
		rep(i, 1, n-1) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		int k;
		scanf("%d", &k);
		a.resize(k);
		rep(i, 0, k-1) scanf("%d", &a[i]);
		for(int i : a) colA[i] = 1;
		scanf("%d", &k);
		b.resize(k);
		rep(i, 0, k-1) scanf("%d", &b[i]);
		for(int i : b) colB[i] = 1;
		int u = ask('B', b[0]);
		if(colA[u]) ask('C', u);
		else {
			int v = bfs(u);
			int qwq = ask('A', v);
			if(colB[qwq]) ask('C', v);
			else ask('C', -1);
		}
		rep(i, 1, n) colA[i] = colB[i] = vis[i] = 0;
		a.clear(); b.clear();
		rep(i, 1, n) e[i].clear();
	}
	return 0;
}
```

---

