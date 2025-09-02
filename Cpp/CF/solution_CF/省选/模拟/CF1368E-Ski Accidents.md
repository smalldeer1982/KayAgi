# Ski Accidents

## 题目描述

### 题意

有一个由 $n$ 个点 $m$ 条边组成的有向无环图，每个点出度至多为2。您需要标记一些点（**不超过** $\frac{4}{7}n$ 个）。标记一个点 $u$ 将会**删除所有与** $u$ **连接的边**。

您需要找到一种标记点的方案，使得删边后的图中每一条路径至多有一条边。

## 说明/提示

- $1 \leq n \leq 2 \times 10^5$，并且所有数据中 $n$ 的和不超过 $2 \times 10^5$。

- $1 \leq x < y \leq n$

## 样例 #1

### 输入

```
2
4 6
1 2
1 3
2 3
2 4
3 4
3 4
7 6
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
2
3 4 
4
4 5 6 7```

# 题解

## 作者：lucifer1004 (赞：29)

### Ski Accidents

[Codeforces-1368E](https://codeforces.com/problemset/problem/1368/E)

#### 题目大意

有 $n$ 个顶点，以及 $m$ 条有向边，所有有向边 $(u,v)$ 均满足 $u<v$ ，且所有顶点的出度都不超过 $2$ ，要求从中删去不超过 $\frac{4}{7}n$ 个顶点，使得图中不存在长度超过 $1$ 的路径。


#### 题目分析

$\frac{4}{7}n$ 是一个很明显的信号，提示存在一种特定的方案，该方案下删除的点数目不会超过 $\frac{4}{7}n$ ，且剩下的点一定满足要求。

$\frac{4}{7}$ 还能让人想到什么？$1+2+4=7$????

暗示我们可以把顶点分成三组 $A$ 、$B$ 、$C$ ，三组的规模满足：

$$
|C|\leq2|B|\leq4|A|
$$

此时， $C$ 组的元素数目一定少于 $\frac{4}{7}n$。

那么，如何划分这三组呢？

不妨先把所有入度为 $0$ 的点都放入 $A$ ，把至少有一条入边都来自 $A$ ，但没有来自 $B$ 的入边的点放入 $B$ ，然后把至少有一条入边来自 $B$ 的入边的点放入 $C$ ，剩下的点（所有入边都来自 $C$ ）放入 $A$ 。

此时，各组包含的顶点情况为：
- $A$ ：入度为 $0$，或所有入边都来自 $C$
- $B$ ：至少有一条入边来自 $A$，但没有来自 $B$ 的入边
- $C$ ：至少有一条入边来自 $B$

容易看出 $A$ 、 $B$ 、 $C$ 的交集为空，并集为全集，说明这是一个有效的划分。

由于所有点的出度都不超过 $2$ ，$A$ 的出边至多有 $2|A|$ 条，所以 $2|A|\geq|B|$ ；同理，因为 $B$ 的出边至多有 $2|B|$ 条，所以 $2|B|\geq|C|$。

此时 $C$ 的顶点数目一定不超过 $\frac{4}{7}n$ 。不妨将 $C$ 的顶点全部删除，此时只剩下 $A$ 和 $B$ 两组。由于 $A$ 和 $B$ 都没有来自 $B$ 的入边，而 $A$ 也没有来自 $A$ 的入边，所以一定不存在长度超过 $1$ 的路径。

从而说明，进行上述划分后，将 $C$ 中顶点全部删除，就可以得到一个满足题意的解。

因为是有向无环图，所以可以在 $O(n)$ 时间内完成上述划分。


#### 参考代码

```cpp
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
class Solution {
public:
  void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<set<int>> to(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      to[v - 1].insert(u - 1);
    }
    vector<int> color(n);
    for (int i = 0; i < n; ++i) {
      for (int u : to[i]) {
        if (color[u] == 1)
          color[i] = 2;
        if (color[i] != 2 && color[u] == 0)
          color[i] = 1;
      }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i)
      if (color[i] == 2)
        ans.emplace_back(i + 1);
    printf("%d\n", (int)ans.size());
    for (int i : ans)
      printf("%d ", i);
    printf("\n");
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  scanf("%d", &t);
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}
```

---

## 作者：约瑟夫用脑玩 (赞：9)

这道题好像没这么神，虽然我没想到但还是很套路。

首先构造题肯定是按要求完成，要求每条路径只有一条边。

由于这是个拓扑图，为了方便，先设每个点有个深度 $dp_x$。

我们规定由 $x\to y$ 的边一定满足 $dp_y=dp_x+1$，同时我们规定当其中有点被删掉时这个条件可以失效。

初始有没有被指向的点，它们的深度为 $1$，由它们指出去的点应该有深度为 $2$ 的点。

但肯定不是所有都是，因为有一些会被删掉。

由于我们希望达到一个构造下界，所有我们肯定能不删就不删。

如果一个深度为 $2$ 的点指向了一个点，那么这个点必定被删掉。

而一个点肯定不能随便成为一个深度为 $2$ 的点，考虑这个图的特性，这是个拓扑图。

所以当拓扑序比它小的点都确定了，并且有深度为 $1$ 指向它的时候，它就会成为深度为 $2$ 点。

被删掉的点看作深度为 $3$，它们指向的点拓扑序都更大，可能是深度为 $2$，也有可能深度未定。

同理，当拓扑序比它小的点都确定了，并且有深度为 $3$ 指向这些深度未定的点时其深度为 $4$。

不难发现它们与深度为 $1$ 的点类似，因为深度为 $3$ 的点已经被删掉，它们的边可以看作不存在，就可以看作没有被点指向。

于是按照 $dp_x\bmod 3$ 的循环构造即可。

最后来证明这个下界是多少：令 $c_x$ 为深度为 $x$ 的点的个数。

显然有 $\forall x\bmod3\neq0,2c_x\ge c_{x+1}$，因为每个点只有两条出边，而有的出边可能指向同一个点。

故有 $\forall k\in N,4c_{3k+1}\ge2c_{3k+2}\ge c_{3k+3}$。

解一下就知道 $\sum c_{3k+3}\le \frac47 n$，故这样构造满足题意。

---

## 作者：vectorwyx (赞：4)

有向无环图，考虑做拓扑排序。每次不断拿出入度为 $0$ 的那些点，称为集合 $A$。然后把集合 $A$ 连向的所有点拿出来，**只看这些点和这些点之间的边得到一张子图**，对这张子图进行拓扑排序：先拿出入度为 $0$ 的点（注意这里入度是对于子图意义下的），把这些点纳入一个新的集合 $B$，然后把这些点连向的所有点（注意也是子图意义下的）纳入另一个集合 $C$，随后把这些入度为 $0$ 的点以及它们连向的点在子图里一并删掉，继续做拓扑排序。整个子图的拓扑排序结束后，集合 $A$ 连向的所有点要么被划到 $B$ 中要么被划到 $C$ 中，找出被划到 $B$ 的那些点，把它们在原图意义上连向的点也都并到 $C$ 里去。至此我们得到了三个集合 $A,B,C$ 满足：原图中没有点连向 $A$，$A$ 连向的点均落在集合 $A$ 或集合 $B$  中。$B$ 中的点均有至少一条来自 $A$ 的入边且 $B$ 集合中的点相互之间没有连边。$C$ 中的点都至少有一条来自集合 $A$ 或集合 $B$ 的入边。标记 $C$ 集合中的点，然后把 $A,B,C$ 这三个集合的点在原图上全部删去，重复第一步直至图被删空。

首先说正确性：对于每轮拓扑排序找出 $A,B,C$ 的过程，从 $A$ 出发走一步只能走到 $B$（因为 $C$ 被标记），又因为从 $B$ 出发走到的点全落在 $C$ 里，所以从 $A$ 或 $B$ 出发的路径的前两步一定会经过一个被标记的点。次数也是合法的，因为有 $2|A|\ge |B|,2|B|\ge |C|$，所以每一轮标记的点占删去的点的比例小于等于 $\frac{4}{7}$。

具体实现可以把整个过程（包括对子图的拓扑排序）纳入对原图拓扑排序求拓扑序的过程。

代码如下：（码字不易，给个赞再走好不好QAQ）

```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5;
vector<int> e[N];
int n,m,deg[N],stk[N],top,f[N];

void solve(){
	cin>>n>>m;
	fo(i,1,n) deg[i]=f[i]=0,e[i].clear();
	fo(i,1,m){
		int x=read(),y=read();
		e[x].eb(y);deg[y]++;
	}
	top=0;fo(i,1,n) if(!deg[i]) stk[++top]=i;
	vector<int> ans;
	fo(i,1,top){
		int x=stk[i];
		for(int j:e[x]){
			if(!(--deg[j])) stk[++top]=j;
//			if(f[x]==0){
//				if(f[j]!=2) f[j]=1;
//			}else if(f[x]==1) f[j]=2;
			big(f[j],(f[x]+1)%3);
		}
	}
	fo(i,1,n) if(f[i]==2) ans.eb(i);
//	assert((int)ans.size()<=4*n/7);
	cout<<ans.size()<<'\n';
	for(int i:ans) cout<<i<<' ';HH;
}

signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```



---

## 作者：xiaolilsq (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF1368E)

## 题意简述

给定一个 $n$ 个点的**有向无环图**，其中每个点的出度**最多为 $2$** ，请删去不超过 $\frac{4}{7}n$ 个点，使得图中**不存在长度大于等于 $2$ 的路径**。

## 题目分析

把 $n$ 个点分成三个不相交的点集 $V_0,V_1,V_2$ ，它们满足的条件如下：

- 若一条边的终点属于点集 $V_0$ ，那么这条边的起点属于点集 $V_2$ 。
- 若一条边的终点属于点集 $V_1$ ，那么这条边的起点属于点集 $V_0$ 或者 $V_2$。
- 若一条边的起点属于点集 $V_1$ ，那么这条边的终点属于点集 $V_2$ 。

不难发现，这样规定后，如果删除点集 $V_2$ 后，就已经不存在长度大于等于 $2$ 的路径了，因此我们肯定会最小化点集 $V_2$ 的大小，于是题目变成：

给定 $n$ 个变量，其中每个变量的取值范围是 $[0,2]$ ，有若干个诸如“若变量 $x$ 的取值为 $a$ ，那么变量 $y$ 的取值为 $b$ 或者为 $c$ ”的限制，请最小化取值为 $2$ 的变量的数量。

显然发现貌似往这方面去想好想没有思路了，考虑直接规定 $V_0,V_1,V_2$ 是哪些点：

- 若一个点入度为 $0$ ，那么这个点属于 $V_0$ 。
- 若所有以这个点为终点的边，其起点都属于 $V_2$ ，那么这个点属于 $V_0$ 。
- 若所有以这个点为终点的边，至少有一条起点属于 $V_0$ ，其它的起点都属于 $V_2$ ，那么这个点属于 $V_1$ 。
- 若所有以这个点为终点的边，至少有一条起点属于 $V_1$ ，其它的起点都属于 $V_0$ 或者 $V_2$ ，那么这个点属于 $V_2$ 。

经过一番规定， $V_0,V_1,V_2$ 都可以很好算出来了，只需从 $1$ 到 $n$ 扫一遍即可，然后将所有属于 $V_2$ 的点删去后即可满足图中**不存在长度大于等于 $2$ 的路径**的要求。

那么 $V_2$ 会有多少个呢？不妨设每个点集的大小分别为 $S_0,S_1,S_2$ ，由于每个点出度**最多为 $2$** ，属于 $V_1$ 的点必须要有一条从 $V_0$ 出去的边指向它，所以 $S_1\le 2S_0$ ，同样的 $S_2\le 2S_1$ ，所以有： $S_2\le 2S_1\le 4S_0$ ， $4S_2\le 4S_2,2S_2\le 4S_1,1S_2\le 4S_0$ ，加起来得到 $7S_2\le 4n \Leftrightarrow S_2\le \frac{4}{7}n$ ，刚好满足题目要求。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
const int maxn=200005;
struct Edge{
	int v,nt;
	Edge(int v=0,int nt=0):
		v(v),nt(nt){}
}e[maxn*2];
int hd[maxn],num;
void qwq(int u,int v){
	e[++num]=Edge(v,hd[u]);hd[u]=num;
}
int ans[maxn],vis[maxn][2];
int main(){
	int T;read(T);
	while(T--){
		int n,m;
		read(n),read(m);
		for(int i=1;i<=n;++i)
			hd[i]=vis[i][0]=vis[i][1]=0;num=0;
		while(m--){
			int x,y;
			read(x),read(y);
			qwq(x,y);
		}
		int cnt=0;
		for(int i=1;i<=n;++i){
			int type=(vis[i][1]?2:vis[i][0]?1:0);
			if(type==2)ans[++cnt]=i;
			else{
				for(int j=hd[i];j;j=e[j].nt){
					int v=e[j].v;vis[v][type]=true;
				}
			}
		}
		write(cnt),pc('\n');
		for(int i=1;i<=cnt;++i)
			write(ans[i]),pc(" \n"[i==cnt]);
	}
	return 0;
}
```

---

## 作者：lovely_codingcow (赞：3)

## 思路

首先我们看到题中给出，这个图是一个 DAG，因此很容易的就可以想到拓扑排序。那么我们在思考一下，如何满足题目中给出的删除的点不超过 $\frac{4}{7}n$ 的要求。我们可以举一个例子，看到下面的二叉树：

![](https://cdn.jsdelivr.net/gh/lixuannan/img/graph-2024-2-25.png)

如果我们按照拓扑排序遍历，每次遍历到深度对 $3$ 取模为 $0$ 的节点，就删除。那么很显然，这个策略可以正常的分割出符合条件的链。同时，对于这个具有 $7$ 个节点的图，他只删除了 $4$ 个节点，满足题目 $\frac{4}{7}n$ 的限制。

由此我们可以发现，无论怎么删除，都可以满足题目 $\frac{4}{7}n$ 的限制。那么只要我们按照拓扑序遍历这个图，遇到深度超的就删除，就可以简单的水掉这一道紫题。

## 代码

拓扑序遍历即可，注意多测要清空。代码如下：

 ```cpp
 #include <iostream>
 #include <vector>
 #include <queue>
 #include <algorithm>
 
 using namespace std;
 
 int n, m, u, v, d[200009], dp[200009];
 vector<int> g[200009], ans, a[4];
 
 int main() {
     int t;
     cin >> t;
     while (t--) {
         for (int i = 1; i <= n; i++) {
             d[i] = 0;
             dp[i] = 0;
             g[i].clear();
         }
         ans.clear();
         cin >> n >> m;
         for (int i = 1; i <= m; i++) {
             cin >> u >> v;
             g[u].push_back(v);
             d[v] += 1;
         }
         queue<int> q;
         for (int i = 1; i <= n; i++) {
             if (!d[i]) {
                 q.push(i);
                 dp[i] = 1;
             }
         }
         while (!q.empty()) {
             int u = q.front();
             q.pop();
             if (dp[u] >= 3) {
                 dp[u] = 0;
                 ans.push_back(u);
             }
             for (int v: g[u]) {
                 d[v] -= 1;
                 dp[v]= max(dp[v], dp[u] + 1);
                 if (!d[v]) {
                     d[v] = -1;
                     q.push(v);
                 }
             }
         }
         cout << ans.size() << endl;
         for (int i: ans) {
             cout << i << " ";
         }
     }
 }
 ```

---

## 作者：bsdsdb (赞：1)

题意：有个 DAG，每个点出度不超过 $2$，你需要删掉至多 $\frac47n$ 个点，使得图中没有边数为 $2$ 的路径。

注意到 

$$
1+2+4=7\\
1\times2=2\\
2\times2=4
$$

所以把没有入度的点加入集合 $A$，把距离 $A$ 中点最长路不超过 $1$ 的加入集合 $B$，距离 $B$ 中点最短路不超过 $1$ 的加入集合 $C$，故 $|A|\ge2|B|,|B|\ge2|C|,|C|\le\frac47|A\cup B\cup C|$。$C$ 加入答案集合 $D$，把 $A,B,C$ 从图中删掉，继续这个流程直到 $G$ 为空。$|D|\le\frac47n$。

牛逼。

---

