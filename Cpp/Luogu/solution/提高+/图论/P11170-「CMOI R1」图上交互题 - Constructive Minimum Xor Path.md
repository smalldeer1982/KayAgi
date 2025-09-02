# 「CMOI R1」图上交互题 / Constructive Minimum Xor Path

## 题目背景

2024 年 1 月 13 日 15:59:31，随着最后一发交互 J 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了，也意味着在 ICPC 生涯中第一次打铁。

痛定思痛，小 G 决定批量生产交互题给自己做。如何批量生产交互题？只要在一个数据结构中有若干个未知量 $a_i$，每次询问给定向量 $x$，交互库会返回关于 $a_i$ 的函数 $f(x)$，这样就能批量生产交互题了！

~~那为什么这题并不是交互题呢。~~

## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\bigoplus\limits_{i=1}^{k} a_{e_i}$。其中 $\bigoplus$ 表示异或。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）



定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最小值**。特别地，当 $x=y$ 时，$f(x,y)=0$。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。

## 说明/提示

### 样例解释

答案输出的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/06683y6o.png)

考虑 $f(1,2)$：

+ 考虑路径 $1\rightarrow 2$，路径的代价为 $2$。

+ 考虑路径 $1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2$，路径的代价为 $2\oplus3\oplus114514\oplus2=114513$。

此外还存在其他路径，但可以证明不存在代价比 $2$ 更小的路径，故 $f(1,2)=2$。

### 数据范围

**本题采用捆绑测试。**

|$\text{Subtask}$ |特殊性质|分数|
|-:|-:|-:|
|$1$|保证有解|$20$|
|$2$|$m\le n+10$|$30$|
|$3$||$50$|

对于 $100\%$ 的数据，$1\le n,m\le 5\times 10^5$，$1\le u_i,v_i\le n$，$0\le f(u_i,v_i)<2^{31}$。

## 样例 #1

### 输入

```
3 3
1 2 2
2 3 3
3 1 1```

### 输出

```
Yes
2 3 114514```

## 样例 #2

### 输入

```
1 1
1 1 1```

### 输出

```
No```

# 题解

## 作者：__DIOsama__ (赞：4)

~~这题赛时竟然灵感突发做出来了， 所以来水一发题解（~~

这道题实际上就是让我们通过路径最小异或代价来构建合法的边权值。我们需要分析给定的边及其对应的代价 $f(u_i, v_i)$，并构建一个合法的边权值 $a_i$，使得所有路径的异或代价符合这些要求。每条边的代价是未知的，我们需要根据输入的代价 $f(u_i, v_i)$ 来推出每条边的权值。

定义路径代价为所经过边权值的异或。对于任意两点 $x$ 和 $y$，我们需要确保从 $x$ 到 $y$ 的所有路径中，最小的代价为 $f(x, y)$。

若有环，并且在环上进行异或运算，环的代价应当为 $0$。如果 $f(u_i, v_i) = f(u_i, u_i) \oplus a_i \oplus f(v_i, v_i)$，则可以推导出边的权值。我们可以利用并查集来维护，并进行路径压缩和合并。在每次合并两个点 $u$ 和 $v$ 时，记录边的权值。

对于每条边，我们可以构建一个方程：  

$$f(u_i, v_i) = f(u_i, u_i) \oplus a_i \oplus f(v_i, v_i) $$

（其中 $f(u_i, u_i)$ 和 $f(v_i, v_i)$ 为已知值）

对于每对节点 $u_i$ 和 $v_i$，可以通过并查集查找到它们的根节点，并确保它们在同一个连通分量中，然后就可以利用异或来逐步构建出合法的边权值 $a_i$。并且在合并的过程中，要检查是否存在矛盾。若有矛盾，直接输出`NO`即可。

完整代码如下

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <cstdio>

#define int long long
#define function auto
#define rop(a, b, c) for(int a = b; a < c; ++ a)
#define por(a, b, c) for(int a = b; a > c; -- a)
#define rep(a, b, c) for(int a = b; a <= c; ++ a)
#define per(a, b, c) for(int a = b; a >= c; -- a)

namespace Space {

    template < typename _Tp > inline function
    read(_Tp& t) -> void {
        int f = 0, ch = getchar (); t = 0;
        while (!isdigit (ch)) f |= (ch == '-'), ch = getchar ();
        do {t = (t << 1) + (t << 3) + (ch & 15); ch = getchar ();}
        while (isdigit(ch)); t = f ? -t : t;
    }

    template < typename _Tp, typename... _Args > inline function
    read(_Tp& t, _Args&... args) -> void {
        read(t); read(args...);
    }
}

using namespace Space;

class Find {
public:
    std::vector<int> parent, rank, xorValue;
    
    Find(int n) : parent(n), rank(n, 0), xorValue(n, 0) {
        rop(i, 0, n) parent[i] = i;
    }
public:
    inline function
    find(int x) -> int {
        if (parent[x] != x) {
            int root = this -> find(parent[x]);
            xorValue[x] ^= xorValue[parent[x]];
            parent[x] = root;
        } return parent[x];
    }

    inline function
    uunion(int x, int y, int value) -> bool {
        int rootX = this -> find(x);
        int rootY = this -> find(y);
        if (rootX == rootY) return (xorValue[x] ^ xorValue[y]) == value;
        if (rank[rootX] < rank[rootY])std::swap(rootX, rootY);
        parent[rootY] = rootX;
        xorValue[rootY] = xorValue[x] ^ xorValue[y] ^ value;
        if (rank[rootX] == rank[rootY])rank[rootX] ++;
        return true;
    }
};

signed main() {
    int n, m;read(n, m);
    std::vector<int> u(m), v(m), f(m);
    rop(i, 0, m){
        read(u[i], v[i], f[i]);
        -- u[i]; -- v[i];
    }
    Find uf(n); bool possible = true;
    rop(i, 0, m) {
        if (!uf.uunion(u[i], v[i], f[i])) {
            possible = false; break;
        }
    }
    if (!possible) std::printf("No\n");
    else {
        std::printf("Yes\n");
        std::vector<int> a(m, 0);
        rop(i, 0, m) a[i] = f[i];
        for (auto x : a) std::cout << x << ' ';
        std::printf("\n");
    }
    return 0;
}
```

---

## 作者：hhiron (赞：3)

## 路径分析

首先题目规定**路径可以经过重复点和重复边**。我们考虑能否优化这种叙述。走过的边无非就两种情况：

1、该边被经过了奇数次，根据异或的性质，这种情况等价于该边只走了一次。

2、该边被经过了偶数次。对于一幅图，我们删去其中经过偶数次的边，然后由于每个偶数边的进入离开次数都为偶数，我们可以把这些进入和出去的边两两相连，直到图中没有偶数边为止，这样一直操作过后走过的路径依然合法。根据异或的性质，偶数边的代价记为 $0$，则删后的代价与原代价相等，视为等价。

以下图为例，其中黑色的箭头代表原来经过的情况，那么红色的 $e$ 边被经过了两次，如果我们删掉红色的 $e$ 边，将四条黑边改成如图所示的绿边，则原路径依然联通，只需要改变几个边的方向即可视为等价。

![](https://cdn.luogu.com.cn/upload/image_hosting/bfvd6nu8.png)

## 特殊图分析

根据以上两条性质，我们仅需要考虑简单路径即可 (指每条边仅被经过一次)。

有了以上的性质，我们考虑这张图为树的情况，那么一个合法的构造方案显然可以将各个边的长度 $w(u_i,v_i)$ 赋值为 $f(u_i,v_i)$。

题目中的图与树不同的本质在于有环，因此我们考虑简单环，记一个环上各个边的 $f(u_i,v_i)$ 的异或和为 $a$。模拟一下样例可以发现当 $a$ 的值为 $0$ 时合法。因为对于任意两个相邻的节点 $u,v$， 将它们之间边的长度 $w(u,v)$ 赋值为 $f(u,v)$，则无论从环的哪个方向走，路径的权值一定为 $w(u,v)$ 或 $w(u,b) \oplus a$。不难发现这种构造一定满足。

接下来考虑必要性，假设 $a$ 不为 $0$，那么必然存在一个最高位异或后的结果为 $1$，设这一位为第 $k$ 位，也必然存在两个相邻的节点 $u,v$，它们的 $f(u,v)$ 的第 $k$ 位也为 $1$，根据异或的性质，由于 $a$ 的第 $k$ 位为 $1$ 那么 $a\oplus f(u,v)<f(u,v)$。这反映在路径上是指不直接到达，反方向绕一圈的情况，该情况的代价比 $f(u,v)$ 小，与题目中 $f(u,v)$ 为最小路径代价矛盾。因此我们得出：**当且仅当对于图中所有的环，环上每一条边的 $f(u,v)$ 的异或和为 $0$ 时有解，且构造的方式为将各个边的长度 $w(u,v)$ 赋值为 $f(u,v)$**。

## 结论

最后将环和树结合起来考虑，可以将题目中给定的图视作一棵树和若干环构成，我们可以在遍历树上节点的时候找到环，运用类似树上差分的操作，计算出每个环的异或长度，判断该异或值是否为 $0$ 即可。具体的，在DFS时记录每个节点到根节点的异或和 $dis[u]$，$dis[u]=dis[fa]\oplus f(fa,u)$，当发现某条边 $e(u,v)$ 指向已经被遍历过的点时可以算出这个环的异或和 $dis[u]\oplus dis[v]\oplus f(u,v)$，最后判断它是否为 $0$ 即可。

结合下图理解，其中蓝色代表 $dis[v]$ ，绿色代表 $dis[u]$ ，红色代表一条指向已被遍历过的点的边，构成一个紫色的环。不难发现紫色环的各边异或和等于红，绿，蓝三个值的异或和。

![](https://cdn.luogu.com.cn/upload/image_hosting/uhvxr3qx.png)

## code

最丑的环节：

```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
typedef long long ll;
using namespace std;
const int N=1e6+6;
int n,m,tot=0,head[N],a[N];
struct node{
	int nxt,to,w;
}e[N<<2];
void addEdge(int u,int v,int w){
	e[++tot]=(node){head[u],v,w};
	head[u]=tot;
	e[++tot]=(node){head[v],u,w};
	head[v]=tot;
}
int dis[N];
bool ans=1;
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dis[v]!=-1){
			if(dis[u]^e[i].w^dis[v]) ans=0;
			continue;
		}
		dis[v]=dis[u]^e[i].w;
		dfs(v);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		addEdge(x,y,z); a[i]=z;
	}
	for(int i=1;i<=n;i++) dis[i]=-1;
	for(int i=1;i<=n;i++){
		if(dis[i]==-1){
			dis[i]=0;
			dfs(i);
		} 
	}
	if(ans){
		puts("Yes");
		for(int i=1;i<=m;i++) printf("%d ",a[i]);
	}else puts("No");
	return 0;
}
```

这是蒟蒻的第一篇题解，如有不足，欢迎指正。

---

## 作者：Grand_Dawn (赞：3)

结论：存在 $a_i$ 当且仅当图上**所有** $f(x_i,y_i)$ 所形成的环异或和为 $0$。有解时，直接令 $a_i=f(x_i,y_i)$ 即可。证明见后。

### 代码实现

采用 [P4151](https://www.luogu.com.cn/problem/P4151) 的方法是可以的。

或者，如果学习过数学分析的话，可以证明所有环异或和为 $0$ 和有势场是等价的。钦定某一个点的势为 $0$，直接 `dfs` 一次计算出每个点的势，并最后检查一下是否满足每条边两边的势差为 $f(x_i,y_i)$ 即可。

----

By [Argon_Cube](https://www.luogu.com.cn/user/372983)：

简单来说就是，对于一个连通块随便选一个根 $r$ 拉出一个生成树，然后计算树上每个点 $u$ 到根路径的权值作为该点的点权 $b_u$。原图合法当且仅当对于图中的每条边，边两端的点权异或和等于边权。

显然如果边 $(u,v,w)$ 满足 $b_u\oplus b_v\neq w$ 那么直接选取环 $u\to r\to v\to u$ 就是一个异或和非 $0$ 的环。否则任意路径 $u\to v$ 的权值都是 $b_u\oplus b_v$，特别的环的权值一定是 $0$。

----

```cpp
#include<bits/stdc++.h>
#define N 1000009
using namespace std;
int n,m;
vector<int>to[N];
struct{
	int x,y,f;
}e[N];
int phi[N],vst[N];
void dfs(int x,int val){
    phi[x]=val;vst[x]=1;
    for(int abc=0;abc<to[x].size();abc++){
    	int i=to[x][abc],y=e[i].x^e[i].y^x;
    	if(!vst[y])dfs(y,val^e[i].f);
	}
}
int main(){
	//freopen("1-5.in","r",stdin);
	//freopen("1-5.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].f); 
		to[e[i].x].push_back(i);
		to[e[i].y].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(!vst[i])dfs(i,0);
	}
	for(int i=1;i<=m;i++)
		if((phi[e[i].x]^phi[e[i].y])!=e[i].f){
			cout<<"No"<<endl;
			return 0; 
		}
	cout<<"Yes"<<endl;
	for(int i=1;i<=m;i++)printf("%d ",e[i].f);
	return 0;
}

```

### 判断有解性的证明

用反证法，假设存在一个回路 $a_1,a_2,...,a_k$ 使得 $\bigoplus\limits_{i=1}^{k} f(a_i,a_{i+1})\neq 0$，则必然存在一位最高二进制位使得该异或值这一位为 $1$。

由于该位异或值为 $1$，则显然至少会存在一个 $i$ 使得 $f(a_i,a_{i+1})$ 这一位为 $1$，不妨 $f(a_n,a_1)$ 这一位为 $1$。而再考虑 $a_n$ 到 $a_1$ 沿着 $a_n$ 到 $a_{n-1}$ 到......到 $a_{1}$，此时路径的代价函数为 $\bigoplus\limits_{i=1}^{k-1} f(a_i,a_{i+1})$，而该值的这位二进制位为 $0$，比原本的 $f(a_n,a_1)$ 更小，矛盾。

因此所有回路均有异或和为 $0$。

### 构造正确性的证明

~~显然由数学分析知识，有势场为保守场，故路径的代价函数和路径无关，即刚好为 $a_i=f(x_i,y_i)$。~~

By [Argon_Cube](https://www.luogu.com.cn/user/372983)：显然 $u$ 到 $v$ 的任意两条路径都形成了一个环，又因为任意环异或和为 $0$ 所以这两条路径权值相等，所以从 $u_i$ 到 $v_i$ 的任意路径等价于边 $(u_i,v_i)$。

### 彩蛋

+ 为什么不是交互题？因为即使询问了所有的 $f(x,y)$ 后 $a_i$ 依然不是唯一的！

+ 如果你做过 [P4151](https://www.luogu.com.cn/problem/P4151) 的话，那么它的思路很可能并不会帮助你解决这道题。

+ 如何想到算法？考虑类似 Floyd 算法的松弛思想即可。

---

## 作者：AmaoFox (赞：1)

对于三个节点 $x$ 和 $y$ 和 $z$，如果 $f(x,y) \ne f(x,z) \oplus f(z,y)$，那么这个输入肯定是不合法的，其中有一个函数值肯定是不够小的。  
推广出来，我们对于每一个输入的 $x$ 和 $y$ 连边，以 $f(x,y)$ 作为边权，那么这个图中所有的环上的边，异或值都为 $0$。不然就会出现两点之间两条路径异或值不相等的情况，那么肯定是有至少一个边权还不够小。

假设已经满足了上面这个条件，则我们可以发现 $x$ 到 $y$ 中间已经有一条边长度为 $f(x,y)$，并且根据这个条件保护的性质使得剩下所有路径的异或值也是 $f(x,y)$，所以这种构造是可行的。

为了满足上面这个条件，我们可以从一个点出发进行 dfs，如果发现某个点的下一个节点已经被访问过但是异或距离并不符合就可以直接 `No` 了。具体细节看代码。


``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 500005;

struct Edge {
  int v, w;
};

vector<Edge> g[N];
int dis[N], vis[N], ans[N];

void dfs(int u, int x) { // x 是调试遗留产物
  vis[u] = 1;
  for(auto v : g[u]) {
    if(vis[v.v] && dis[v.v] != (dis[u] ^ v.w)) { // 我们发现从一开始那个点开始，经过 u 到 v.v 和另一条到 v.v 的距离不相等
      cout << "No";
      exit(0);
    } else if(!vis[v.v]) {
      dis[v.v] = dis[u] ^ v.w;
      dfs(v.v, dis[v.v]);
    }
  }
}

signed main() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v >> ans[i];
    g[u].push_back({v, ans[i]});
    g[v].push_back({u, ans[i]});
  }
  for(int i = 1; i <= n; i++) {
    if(!vis[i]) {
      dfs(i, 0);
    }
  }
  cout << "Yes\n";
  for(int i = 1; i <= m; i++) {
    cout << ans[i] << ' ';
  }
}
```

---

## 作者：锦依卫小生 (赞：1)

# P11170  
## 基本思路  
注意到输入的 $f(u,v)$ 约束只作用于现有边。不难得出结论：若答案存在，那么将 $f(u,v)$ 作为 $u$，$v$ 的边权一定是合法答案之一。简单证明：若出现 $f(x,y) \bigoplus f(y,z) < f(x,z)$，此时一定无解；反之将 $f(u,v)$ 作为 $u$，$v$ 的边权一定合法。   
问题转化判断无向图是否满足异或意义上的任意直接相连的两点的最短路径就是其边权。先给出结论：当且仅当所有的环，其上所有边权异或和为 $0$ 时满足条件。  
反证：以 $3$ 点为例。假设存在异或和非 $0$ 时满足条件。令 $a < b < c$，则 $a \bigoplus b > c$，$a \bigoplus c > b$，$b \bigoplus c > a$。则 $c = a \bigoplus b \bigoplus k$，$k$ 满足最高位 $1$ 的位置 $a$，$b$ 在该位出现 $1$ 与 $0$。条件转为 $a \bigoplus k > a$，$b \bigoplus k > b$，至少一个不等式无法满足。多于三点类推可得（逃），得证。  
判断过程显然不需要找到所有环。借助广搜，若当前由 $u$ 遍历到的点 $v$ 未遍历过，则 $f_{v} \gets f_{u} \bigoplus w$，入队；否则判断 $f_{v} = f_{u} \bigoplus w$，若不等则输出并退出程序。详见代码。 
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=5e5+5;
int ans[MAX],f[MAX];
bool vis[MAX];
queue<int> q;
struct edge{
	int nxt,to,w;
};
edge e[MAX*2];
int n,m,tot,h[MAX];
void addedge(int u,int v,int w){
	e[++tot].to=v;
	e[tot].nxt=h[u];
	e[tot].w=w;
	h[u]=tot;
}
void bfs(int x){
	q.push(x);
	vis[x]=1;
	while(!q.empty()){	
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(vis[v]){
				if(f[v]!=(f[u]^e[i].w)){
					cout<<"No";
					exit(0);
				}
			}
			else{
				vis[v]=1;
				f[v]=(f[u]^e[i].w);
				q.push(v);
			}
		}
	}
}
int read(){
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-'){
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = x*10+c-'0';
		c = getchar();
	}
	return x*f;
}

int main(){
	cin>>n>>m;
	bool flag=0;
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		addedge(u,v,w);
		addedge(v,u,w);
		ans[i]=w;			
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			bfs(i);
		} 
	cout<<"Yes"<<endl;
	for(int i=1;i<=m;++i)
		printf("%d ",ans[i]);
} 
```

---

## 作者：Dream_Realizer (赞：0)

赛时思路想的没那么复杂，就把这个问题转换成一个图上的最短路径问题，但这里的“最短路径”用的是异或运算，而不是常规的加法运算。

先构建一棵最小生成树，尝试确定边权，并使得每条边的路径代价等于给定的 $f(u_i, v_i)$。对于一个图的两点 $x$ 和 $y$，如果 $x$ 到 $y$ 的某条路径的异或代价是某个值，那么图中所有 $x$ 到 $y$ 的路径的异或值都具有相同的模 2 和相同的特征。因此，路径之间的异或值构成了一个线性方程组。

往细来说大概是这样，对于每条边 $(u_i,v_i)$，我们有：

$$f(u_i, v_i) = a_i$$

对于任意一条从 $u$ 到 $v$ 的路径，由路径上每条边的边权 $a_{e_i}$ 构成的异或和，必须等于给定的 $f(u,v)$。这可以表示为：

$$f(u, v) = a_{e_1} \oplus a_{e_2} \oplus \cdots \oplus a_{e_k}$$

其中 $(𝑒_1,𝑒_2,\cdots,𝑒_𝑘)$是从 $u$ 到 $𝑣$ 的路径上的边。

对于图中的每对节点，我们可以基于其路径建立一个方程。对于 $m$ 条边，我们可以写出如下方程组：

$$\begin{aligned}
f(u_1, v_1) &= a_1 \\
f(u_2, v_2) &= a_2 \\
&\vdots \\
f(u_k, v_k) &= a_{e_1} \oplus a_{e_2} \oplus \cdots \oplus a_{e_k}
\end{aligned}$$

将上述方程组转化为矩阵形式：

$$A \cdot x = b$$

其中 $A$ 是基于图的结构生成的系数矩阵，每一行代表一条路径上的边；$x$ 是包含所有边权 $a_i$ 的向量；$b$ 是包含所有已知的 $f(u_i, v_i)$ 的向量。

此时就可以通过高斯消元处理。在异或运算下，该方程组实际上是一个线性方程组，只不过运算是基于模 2 的加法运算：

$$\text{Gaus} \Rightarrow x = A^{-1} \cdot b$$

如果该方程组有解，则可以求出所有边权 $a_i$；如果无解，则表示不存在满足条件的边权分配。

那其实就很好办了，用并查集来维护每个点所在的连通分量，以及当前点到其祖先节点的异或值。对于每条边 $(u_i, v_i, f(u_i, v_i))$，首先检查 $u_i$ 和 $v_i$ 是否已经连通。如果不连通，则将其合并，并记录边的异或值。如果已经连通，则检查路径的异或值是否与 $f(u_i, v_i)$ 相符。如果不符，则说明无解。

时间复杂度为 $O(\alpha(n))$，其中 $\alpha(n)$ 是反阿克曼函数。但好像实际应用里跟常数差不多。空间复杂度很明显就是 $O(n)$ 了，存并查集结构。

赛时代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct UF {
    vector<int> p, r, x;
    UF(int n) : p(n), r(n, 0), x(n, 0) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int fnd(int a) {
        if (p[a] != a) {
            int rt = fnd(p[a]);
            x[a] ^= x[p[a]];
            p[a] = rt;
        }
        return p[a];
    }
    bool uni(int a, int b, int v) {
        int ra = fnd(a), rb = fnd(b);
        if (ra == rb) return false;
        if (r[ra] > r[rb]) {
            p[rb] = ra;
            x[rb] = v ^ x[a] ^ x[b];
        } else if (r[ra] < r[rb]) {
            p[ra] = rb;
            x[ra] = v ^ x[a] ^ x[b];
        } else {
            p[rb] = ra;
            x[rb] = v ^ x[a] ^ x[b];
            r[ra]++;
        }
        return true;
    }
    bool con(int a, int b) {
        return fnd(a) == fnd(b);
    }
    int get(int a, int b) {
        return x[a] ^ x[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    UF uf(n);
    vector<tuple<int, int, int>> e(m);
    for (int i = 0; i < m; ++i) {
        int u, v, f;
        cin >> u >> v >> f;
        e[i] = {u - 1, v - 1, f};
    }
    for (auto &[u, v, f] : e) {
        if (uf.con(u, v)) {
            if (uf.get(u, v) != f) {
                cout << "No\n";
                return 0;
            }
        } else {
            uf.uni(u, v, f);
        }
    }
    cout << "Yes\n";
    for (auto &[u, v, f] : e) {
        cout << f << " ";
    }
    cout << "\n";
    return 0;
}
```

---

