# [ABC284E] Count Simple Paths

## 题目描述

给定一个有 $N$ 个顶点、$M$ 条边的简单无向图，顶点编号为 $1$ 到 $N$，边编号为 $1$ 到 $M$。第 $i$ 条边连接顶点 $u_i$ 和顶点 $v_i$。此外，每个顶点的度数都不超过 $10$。

请计算以顶点 $1$ 为起点的所有简单路径（即不经过同一顶点多次的路径）的数量，记为 $K$。请输出 $\min(K,\ 10^6)$。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq \min\left(2 \times 10^5,\ \frac{N(N-1)}{2}\right)$
- $1 \leq u_i,\ v_i \leq N$
- 输入给出的图是简单图
- 输入给出的图中每个顶点的度数都不超过 $10$
- 输入的所有值均为整数

## 样例解释 1

满足条件的路径有以下 $3$ 个（注意长度为 $0$ 的路径也要计数）：
- 顶点 $1$
- 顶点 $1$，顶点 $2$
- 顶点 $1$，顶点 $2$，顶点 $3$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 2
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
16```

## 样例 #3

### 输入

```
8 21
2 6
1 3
5 6
3 8
3 6
4 7
4 6
3 4
1 5
2 4
1 2
2 7
1 4
3 5
2 5
2 3
4 5
3 7
6 7
5 7
2 8```

### 输出

```
2023```

# 题解

## 作者：Orange_qwq (赞：6)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc284_e) && [AT 传送门](https://atcoder.jp/contests/abc284/tasks/abc284_e)

此篇题解存在~~乱搞~~优化成分，仅供参考。（但是其实在赛场或考场上这样是会很有用的）

## 思路

讲讲赛时是怎么搞出来的吧。

首先这个菜鸡看了一眼题，果断认错这是一棵树。于是第一步想法诞生了。我们可以手动模拟一下，从根节点开始，每一次跨出一个节点，就是多了一条路径；缩回去跨到另外一个节点，也是多了一条路径。这是候我们就能明白了，可以进行 dfs 遍历，每一次遍历到一个点，答案就 $+1$。

写出了最简单的 dfs 之后，我们~~又~~意识到这里头可能有环（例如样例二）。于是我们可以想到需要打标记和回溯，因为不能在一个环上转圈圈，路径的计算会重复。

这时候代码大概就出来了，但是，这道题毕竟是 E 题，我们可能还得多想一步。因为这道题中可能会有环，每个节点可能会重复走，好像……走太多会超时？（事实证明真的会超时，菜鸡就因为没有多想一步吃了罚时）我们需要一个小优化。题目中说了，最后输出的答案 $K=\min(K,10^6)$，所以，如果答案超过了 $10^6$，就可以输出 $10^6$ 然后结束程序了。

## 代码

这个菜鸡仅仅因为这是 AT 而用了 `vector` 存图，在正式的比赛或考试中不建议用 `vector` 存图，因为怕被出题人卡掉。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans;
bool fl[200010];
vector < int > tr[200010];
void dfs(int x, int fa) {
	if (x == fa) return;
	for (auto v : tr[x]) {
		if (v == fa) continue;
		if (fl[v]) continue;  // 一个环里不重复走
		ans ++;               // 累计答案
		fl[v] = 1;            // 打标记
		if (ans >= 1e6) {     // 小优化
			puts("1000000");
			exit(0);
		}
		dfs(v, x);
		fl[v] = 0;           // 回溯
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	fl[1] = 1;
	dfs(1, 0);
	printf("%d", min(ans + 1, 1000000));
	return 0;
}
```


## 小小的总结

+ 题目要看全，样例最好都手动模拟，避免看错题目要求或限制。

+ 题目看错别怕，也许是正解的第一步。

+ 考虑一下是否需要回溯。

+ 是否需要多想一步呢？代码是不是完全 OK 没有任何差错了捏？是不是还得加上一点点什么东西例如小优化？

+ 最好不要用 `vector` 存图。当且仅当打 AT 的时候可以稍稍偷一下懒，其他比赛最好不要用。

可能会有小小的用处 qwq。

---

## 作者：FFTotoro (赞：5)

本题可以使用**深度优先搜索**解决。

每遍历到一个点，计数器自增 $1$，然后就去找没有走过且相邻的点。

因为本题的特殊约束“每个顶点度 $\le 10$”，所以可以放心地直接搜索。

如果搜的点数量大于 $10^6$，那就直接输出 $10^6$ 并用 `exit(0)` 强制结束程序即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200001];
bool b[200001];
int c=0;
void dfs(int u){
  if(++c>=1e6)cout<<(int)1e6<<endl,exit(0);
  for(int i:g[u])
    if(!b[i])b[i]=true,dfs(i),b[i]=false;
  return;
}
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,m; cin>>n>>m;
  for(int i=1;i<=m;i++){
    int u,v; cin>>u>>v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  b[1]=true; dfs(1);
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：Pengzt (赞：4)

[ABC284E](https://www.luogu.com.cn/problem/AT_abc284_e)

即让我们找这个图中从 $1$ 开始的简单路径的条数，答案 $K = \min(K, 10 ^ 6)$。

其实度数 $\leqslant 10$ 这个条件并没有什么用。

因为答案 $\leqslant 10 ^ 6$，直接 dfs 即可。

[评测记录](https://atcoder.jp/contests/abc284/submissions/37831609)

---

## 作者：李宇涵 (赞：3)

## 图上 dfs 遍历

这是一道图论题，要求统计图中从 $1$ 号顶点出发的**简单路径**的条数。其中，简单路径指的是没有多次经过某一顶点的路径。

这道题的关键是答案的处理方式：若符合要求的路径条数为 $K$，则输出 $A=\min(K,10^6)$。

这个处理方式很重要——因为 $K$ 有可能很大，也不容易在时间限制内用 dp 等方式求出（毕竟点数 $n\le 2\times10^5$ 呢）。而我们知道，直接 dfs 遍历图上的所有简单路径，时间复杂度是 $O(K)$ 的。因为每次找到一条路径，操作是 $O(1)$ 的（遍历路径的方法在下面会说明），而程序需遍历完 $K$ 条路径。

加上限制 $A=\min(K,10^6)$ 之后，在 $K>10^6$ 时，不需要遍历完 $K$ 条路径，只需要在找到 $10^6$ 条路径后，停止遍历并输出 $A=10^6$ 即可。因为就算 $K$ 再大，答案 $A$ 也最多到 $10^6$。所以就不用找出更多的路径了。这样，程序的时间复杂度就是 $O(A)$，且 $A\le10^6$，能够通过。

下面说明 dfs 遍历的方法：从 $1$ 号节点出发，遍历到节点 $u$ 时，每次找到一个与 $u$ 相连的、没有经过的节点 $v$，**在路径上加入一条以 $v$ 结束的新的路径**，并把 $v$ 作为上面提到的 $u$ 继续遍历（类似 dfs 的做法）。直到所有与 $u$ 相连的、没有经过的节点 $v$ 都遍历过之后，返回 $u$ 的上一层节点 $f$（之前从 $f$ 走到的 $u$，就称 $f$ 是 $u$ 的上一层节点）。

注意：在节点 $u$ 时，以其结尾的路径若不同，则以其为经过点的路径也不同。例如 $1\to 2\to 4$ 和 $1\to 3\to 4$ 是两条不同的路径，所以 $1\to 2\to 4\to 5\to 6$ 和 $1\to 3\to 4\to 5\to 6$ 也是两条不同的路径。这也就说明了——先遍历到的节点有不同，后遍历到的节点无论是否相同，都是两条不同的路径。这也就解释了为什么 dfs 遍历时，不会出现相同的路径——每次更改至少有一层上的某个节点与原先的所有路径不同。

按上面的方法，遍历 $u\to v$ 时，需要保证 $v$ 是一个没有经过的节点。所以用一个 $vis$ 数组记录当前路径 $1\to\cdots\to u$ 中经过的节点。如果发现 $vis_v=1$，也就是 $v$ 节点在 $1\to\cdots\to u$ 中，就不能再走 $v$。反之则可以走 $v$，这时需要把 $vis_v$ 设成 $1$，表示 $v$ 现在已经在走过的路径里面了。当 $v$ 遍历结束，返回到 $u$ 时，要把 $vis_v$ 设成 $0$，表示 $v$ 现在不在走过的路径里了。（注意：要求不能走**前面的路径中经过的节点**，而不是“曾经遍历到的节点（可能不在现在的路径里面）”，所以要有这一步 $vis_v\leftarrow 0$ 的回溯操作）。

注意：记得把 $vis_1$ 设成 $1$，因为 $1$ 号节点永远在路径里面（起始节点）。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mx=1e6;
ll n,m,ans;
bool vis[200020];
vector<ll> e[200020];
void dfs(ll u)
{
	if(ans==mx) return;// 超过10^6条路径，不搜了
	ans++;
	for(ll i=0;i<e[u].size();i++)
	{
		ll v=e[u][i];
		if(vis[v]) continue;// 走过就不搜
		vis[v]=1;// 记录走过
		dfs(v);// 往下搜
		vis[v]=0;// 回溯
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=m;i++)
	{
		ll t1,t2;
		cin>>t1>>t2;
		e[t1].push_back(t2);
		e[t2].push_back(t1);
	}
	vis[1]=1;
	dfs(1);
	cout<<ans;
	return 0;
}
```


---

## 作者：NightStriker (赞：2)

这和 C 题一样，还是无脑 dfs。

---

题意：

> 给你一个简单的无向图，$n$ 个顶点和 $m$ 条边，边 $i$ 连接两个顶点，每个顶点的深度最多为 $10$。让你求从顶点 $1$ 开始的所有没有重复走的路径的数量。

看到“每个顶点的深度最多为 $10$”这句话，就说明 dfs 可以直接过掉，甚至不需要剪枝。

思路很简单，就是搜出来所有的路径，搜完的打上标记，没搜完的继续搜。如果超过 $10^6$ 就不搜了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,ans;
vector<int>v[200001];//vector存图
bool vis[200001];//标记
void dfs(int n) {
	if(vis[n]||ans>=1e6) return;//如果搜过了或者答案超过 1e6
	vis[n] = 1;//打标记
	ans++;//累加路径方案
	for(int i = 0; i<v[n].size(); i++) dfs(v[n][i]);//全都搜一遍
	vis[n] = 0;//回溯，撤标记
}

int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1);//从节点1开始搜
	cout<<ans<<endl;
	return 0;
}
```
缺点是稍微有点慢，但是 $195$ ms 完全足够过掉这道题了。


---

## 作者：快乐的大童 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc284_e)

个人感觉是 ABC 做过的最简单的 E 之一。
## 题意简述
求从编号 $1$ 开始、不经过重复点、长度任意的路径条数对 $10^6$ 取最小值。

原图无重边自环，不保证连通。
## 思路
dfs 遍历从编号 $1$ 开始的每个点。

为了处理不经过重复点，我们在 dfs 这个点之前给这个点打上标记，表示之后不能再访问这个点。遍历完取消标记。

为了处理任意的长度，只需在 dfs 的开头让 `ans++` 即可。
## 代码
（删掉火车头和快读快输）

```
/*R()是快读函数，write()是快输函数*/
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define graph(i,j,k) for(int i=head[j];i;i=k[i].nxt)
const int maxn=2e5+5,limit=1e6;
int n,m,ans;
struct edge{
	int to,nxt;
}a[maxn<<1];
int head[maxn],cnt;
void add(int x,int y){
	a[++cnt]=(edge){y,head[x]};
	head[x]=cnt;
}
bool vis[maxn];
void dfs(int x){
	ans++;
	if(ans==limit){
		writeln(limit);
		exit(0);
	}
	graph(i,x,a){
		int u=a[i].to;
		if(!vis[u]){
			vis[u]=1;
			dfs(u);
			vis[u]=0;
		}
	}
}
int main(){
	n=R(),m=R();
	rep(i,1,m){
		int x=R(),y=R();
		add(x,y),add(y,x);
	}
	vis[1]=1;
	dfs(1);
	write(ans);
}
```


---

## 作者：Hell0_W0rld (赞：1)

## E
+ [link](https://atcoder.jp/contests/abc284/tasks/abc284_e)
+ 难度：黄
+ *1075。

这是一道非常简单的爆搜题。

具体来说，我们用一个 $\mathrm{vst}$ 数组，$\texttt{bool}$ 类型。记录当前路径每个点是否被访问。从起点出发 $\texttt{DFS}$。先累加答案，挑没走过的点访问。注意如果答案 $\geq10^6$ 则输出答案。
```cpp
vector<ll> to[200009];
ll cnt=0;
ll n,m,lmt=1e6;
bool vst[200009];
void dfs(ll u){
	if(vst[u])return;
	if(cnt>=lmt){
		cout<<lmt<<endl;
		exit(0);
	}
	vst[u]=1;
	cnt++;
	for(ll i=0;i<to[u].size();i++){
		dfs(to[u][i]);
	}
	vst[u]=0;
}
int main(){
	cin>>n>>m;
	rep(i,1,m){
		ll u,v;cin>>u>>v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dfs(1);
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：Lyu_echo (赞：1)

## 题意

给定一个 $n$ 个节点 $m$ 条边的无向图。 

保证每个节点的度 $\le 10$。

求：从节点 1 出发的简单路径数量与 $10^6$ 的较小值。

简单路径的定义为：没有重复经过节点的路径。

## 解题思路

由于每个点的度较小，且简单路径数大于 $10^6$ 可以直接结束，所以使用 DFS 解题。

在 DFS 搜索过程中：

- 若简单路径数大于 $10^6$ 直接输出结果。

- 否则，继续搜索简单路径。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
vector <int> G [200010]; //使用 邻接表 存图
bool in_path [200010]; //记录当前节点是否在路径中
int ans;
void dfs (int u) {
    ans++;
    if (ans == 1000000) {
        cout << 1000000; //大于 10^6 则直接输出 10^6
        exit(0); //直接结束程序
    }
    for(auto &v : G [u]) {
        if (!in_path [v]) {
            //DFS回溯 模板
            in_path [v] = true;
            dfs (v);
            in_path [v] = false; 
        }
    }
}
int main () {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G [u].push_back (v); //邻接表建图
        G [v].push_back (u);
    }
    in_path [1] = true;
    dfs (1);
    cout << ans;
   	return 0;
}
```



---

## 作者：tZEROちゃん (赞：1)

这道题给了一个很有用的限制，就是如果答案 $\ge 10^6$，就直接输出 $10^6$。

这提示着我们使用一些朴素的做法。

具体是这样的，使用一个朴素的 dfs 搜索，只要当前我们找到的路径数大于 $10^6$，就输出 $10^6$ 并结束程序。

考虑复杂度，dfs 显然最多只会被调用 $10^6$ 次，因为题目保证了每个点的度数最多是 $10$，所以计算的最多次数只能达到 $10^6\times 10 = 10^7$，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;

int n, m;

vector<int> g[N];
bool vis[N];

int ans = 0;

void dfs(int rt) {
   ++ans;
   vis[rt] = 1;
   if (ans >= 1e6) {
      cout << (int)1e6 << endl;
      exit(0);
   }
   for (auto i : g[rt]) {
      if (!vis[i]) {
         dfs(i);
	  }
   }
   vis[rt] = 0;
}

int main() {
   cin >> n >> m;
   for (int i = 1; i <= m; ++i) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   dfs(1);
   cout << ans << endl;
}
```

---

## 作者：yeshubo_qwq (赞：0)

## Solution

题目要求答案对 $10^6$ 取 $\min$。

找到 $10^6$ 条可行路径后，因为此时的答案已经 $\ge 10^6$，取 $\min$ 一定是 $10^6$ 小，再寻找路径只是浪费时间，就可以直接结束了。

直接搜索，因为每走一步都是一条新增的路径，因此时间复杂度为 $O(\min(K,10^6))$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int limit=1e6;
int n,m,i,x,y,vis[200005],ans;
vector <int> G[200005];
void dfs(int x){
	if (++ans==limit){cout<<limit;exit(0);}
	for (int i=0;i<(int)G[x].size();i++)
		if (!vis[G[x][i]]) vis[G[x][i]]=1,dfs(G[x][i]),vis[G[x][i]]=0;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for (i=1;i<=m;i++) cin>>x>>y,G[x].push_back(y),G[y].push_back(x);
	return vis[1]=1,dfs(1),cout<<ans,0;
}

```


---

## 作者：_Ch1F4N_ (赞：0)

首先说结论：暴力遍历可过。

为什么？

因为说了假设答案超过 $10^6$ 次方，就输出 $10^6$ 即可。

我们考虑：每遍历到一个点，答案都会加 $1$。

接下来遍历其他点时，如果这个点在路径里面，则不遍历。

那么我们分析势能。

每次遍历一个点，花费是遍历它的出度，贡献是 $1$。

而题目规定一个点的出度不超过 $10$。

也就是说最劣情况下 $10$ 花费得到 $1$ 贡献。

而我们只需要 $10^6$ 的贡献。

因此最大花费为 $10^7$。

所以暴力遍历可过。

代码就不放了，写暴力都会吧？

---

## 作者：CarroT1212 (赞：0)

#### 题目大意

有一个 $N$ 个点 $M$ 条边的简单无向图，设 $K$ 为图中从节点 $1$ 出发的简单路径数量，输出 $\min(K,10^6)$。

+ 简单路径指不重复经过任何点的路径。

数据范围：$1 \le N \le 2\times 10^5$，$0 \le M \le \min(2\times 10^5,\frac{N(N-1)}{2})$，每个节点的度数不超过 $10$。

#### 解法分析

赛时害我瞪了五分钟，发现是大诈骗题后三分钟码完切了。

首先如果我们用最暴力的方法求答案，肯定是直接从 $1$ 出发 dfs 全图，不能重复经过路径上的点，带回溯。进入 dfs 函数的次数就是答案。但显然这样做是无法通过此题的，$N$ 最大到 $2 \times 10^5$，绝对 T 飞。——如果你没看到答案是 $\min(K,10^6)$ 的话你一定会这么想。

答案是 $\min(K,10^6)$ 代表着什么？

如果你在 dfs 的过程中发现答案已经达到 $10^6$ 你就可以直接输出 $10^6$ 退出了，总数之后怎么增加都对你输出的结果没有影响。

所以我们只要在暴力程序上加个判断就可以解决一切了，最多只进 $10^6$ 次递归的话我们还是可以卡得进时限的。

一定要读题啊……

#### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const int N=2e5+7;
int n,m,ans,vis[N];
vector <int> v[N];
void dfs(int pos) {
	ans++;
	if (ans>=1e6) { printf("1000000"); exit(0); } // 答案已经确定了退出即可
	for (int i:v[pos]) if (!vis[i]) vis[i]=1,dfs(i),vis[i]=0;
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,r1,r2;i<=m;i++) scanf("%d%d",&r1,&r2),v[r1].pb(r2),v[r2].pb(r1);
	vis[1]=1,dfs(1),printf("%d",ans);
	return 0;
}
```

---

## 作者：Neil_Qian (赞：0)

# [ABC284E] Count Simple Paths 题解
给出一张简单无向图，让你求出从 $1$ 开始的不经过重复顶点的路径有多少条，长度为 $0$ 的也算。设答案为 $K$，则输出 $K$ 和 $10^6$ 的最小值。

一看到题目，可能会想到一些复杂的算法，如动态规划。但是，仔细想一想，从 $1$ 开始的路径，不就是从 $1$ 开始深度优先搜索且不经过重复顶点的路径吗？而且，其实题目中已经暗示了，一般的题目都是输出答案对一个数取模，而这道题却说输出 $\min(K,10^6)$，所以搜索到答案为 $10^6$ 就可以直接输出答案然后跳出了。时间复杂度最坏 $O(10^6+m\times d)$，其中 $d$ 为每个顶点的度数，可以通过。

感谢 @[SweetOrangeOvO](https://www.luogu.com.cn/user/236862) 指出文章中的错误。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=4e5+2;
int n,m,x,y,head[N],nxt[N],to[N],ans,cnt;bool vis[N];
inline void add(int x,int y)//建边
{nxt[++cnt]=head[x];head[x]=cnt;to[cnt]=y;}
inline void dfs(int x){
	ans++;
	if(ans==1e6)printf("%d\n",ans),exit(0);//min(K,1e6)=1e6，输出吧
	for(int i=head[x];i;i=nxt[i])if(!vis[to[i]])//没有经过
		vis[to[i]]=1,dfs(to[i]),vis[to[i]]=0;//加标记->dfs->去标记
}
int main(){
	scanf("%d%d",&n,&m),vis[1]=1;//建图
	while(m--)scanf("%d%d",&x,&y),add(x,y),add(y,x);
	return dfs(1),printf("%d\n",ans),0;
}
```

完结撒花！

题外话：这次的第五题是多少场中最简单的一道，然而听说很多人都卡住了。

---

## 作者：紊莫 (赞：0)

## Part 0 题意简述  

给一个图，求从 $1$ 开始有多少条简单路径。  

## Part 1 思路  

注意到题中要求输出的是 $\min(K,\ 10^6)$。  
这启示我们可以暴力！  

从 $1$ 开始一次深搜，中间答案若超过 $10^6$，直接输出。  

这样的总的运算次数不会超过 $10^6$，可以稳过。  

## Part 2 参考代码  

仅供参考。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
#define mkpr make_pair
#define fi first
#define se second
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define dF(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
using namespace __gnu_cxx;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if (x < 0) x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
inline void writeln(int x){write(x);putchar('\n');}
inline void writesp(int x){write(x);putchar(' ');}
inline int lowbit(int x) {return x&(-x);}
typedef pair<int,int> Pair;
const int N=200005;
int n,m,vis[N],ans;
vector<int> p[N];
void dfs(int now){
	vis[now]=1;
	ans++;if(ans>1e6){
		cout<<1000000;exit(0);
	}
	for(auto i:p[now])
		if(!vis[i]) dfs(i);
	vis[now]=0;
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
	F(i,1,m){
		int u,v;cin>>u>>v;
		p[u].push_back(v);p[v].push_back(u);
	}
	dfs(1);
	cout<<min(ans,1000000);
    return 0;
}
```


---

