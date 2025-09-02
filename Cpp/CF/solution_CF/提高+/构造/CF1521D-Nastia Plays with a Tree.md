# Nastia Plays with a Tree

## 题目描述

Nastia has an unweighted tree with $ n $ vertices and wants to play with it!

The girl will perform the following operation with her tree, as long as she needs:

1. Remove any existing edge.
2. Add an edge between any pair of vertices.

What is the minimum number of operations Nastia needs to get a bamboo from a tree? A bamboo is a tree in which no node has a degree greater than $ 2 $ .

## 说明/提示

Note the graph can be unconnected after a certain operation.

Consider the first test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1521D/13d06b5ce6ef542dc457141b641d924a2e34ea5d.png) The red edges are removed, and the green ones are added.

## 样例 #1

### 输入

```
2
7
1 2
1 3
2 4
2 5
3 6
3 7
4
1 2
1 3
3 4```

### 输出

```
2
2 5 6 7
3 6 4 5
0```

# 题解

## 作者：too_later (赞：27)

[link](http://codeforces.com/contest/1521/problem/D)

### 题目大意：

- 给出一棵 $n$ 节点的树，每次操作可以拆一条边并且移动到规定位置。

- 求最少的操作数量，使得这棵树变为一条链。

- $1\le n\le 2\times 10^5$。

### 思路：

#### 初步思路

最后是一条链，不难想到，最后每一个节点，都只有一个儿子。

对于多余的儿子，肯定要想千方百计把他干掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/qucui1to.png)

这里的 10 号节点和 23 号节点，同样其和子树均为一条链，但他们的链不一样， 23 号节点的链不跨过 23 号节点，但是 10 号节点的链要跨过 10 号节点。

这两种链，处理方法也不一样。不跨过的（称为 1 号链），其加上父亲节点还是链。跨过的（成为 2 号链），其加上父亲节点就不是链了。

#### 链的合并方式

对于一个节点，下面可能有许多 1 号链和 2 号链。

期望：有两个一号链（形成 2 号链），有一个一号链（形成 1 号链。）

其中二号链肯定是要杀干净的。

我们举 17 号节点为例子，其中有一个 1 号链和一个 2 号链。

这个二号链怎么杀干净呢？其**本质为一条链**，那么只要将其全部拖到 13 那里，就完成了杀链。

也就是 $5-8-20-10-7$ 作为整体拖过去，把 $10-17$ 断开，这样就杀掉了一个二号链。这样是最简单的杀二号链的方法。

再比如说到了 $15$ 号的时候，两个为二号链（已经处理好了），一个为一号链，那么就把两个二号链杀掉，将 $11-12-9$ 和 $2-4-23-19-3$ 拖到 $21$ 下面，形成一个一号链。

对于一号链，就比较容易了，直接牵到一号链末端上。

比如说 $19$，那么就把 $23-4$ 拖到 $3$ 后面，断掉 $19-23$。

比如说 $14$，$18$ 号节点处理完了是一个一号链，$16$ 号也是一号链，直接把 $16$ 接到 $18$ 这条链后面即可。

还没懂的话就拿这个图模拟一下。

#### 链的合并贪心

对于两个一号链，能留着就留着，毕竟升为二号链说不定还能一次卷走，如果合并为一号链的话，这里就多一个操作，肯定不值得。

如果要合并的全都是二号链，那也没办法，毕竟要加上父亲为链，那只能将左链和右链合并在一起形成一个一号链。

为啥这样子是对的呢？

因为我们保证了每一个搜索到的点，其形成链的次数最少。

纵观全局，二号链的处理是**本质**的优化。每一次二号链的出现都减少一次操作次数。（本来要合并后再在 father 合并，现在不需合并之一次卷走。）

有没有更优的方法？没有的，因为三号链不为链，要先处理成为为二号链才能继续。其要花一的代价形成二号链再减少一的代价。而在哪里形成二号链都是一样的，其本身移动一个要一的代价，二号链减少一的代价。**你不可能移到其他点硬生生把一号链变成二号链**，移动的代价为 1，二号链的代价为 1，原来的话一号链代价为 1，显然这个更优，所以原地形成二号链是最优选择。

所有大于二号的链，就算现在不处理至二号链，之后也是一样的处理，且代价等大，消除二号链是唯一的优化。至于一号链，一次把两个一号链串起来也是最高效的操作，所以是最优的。

#### 代码要处理的：

- 一个二号链的起点和终点，一号链的起点和终点。

- （这里申明一下定义，一个二号链的起点和终点需要左右分明，同时记录其左右儿子，这样在二号链合并为一号链的时候，可以分清楚链的左右节点。一号链的起点为其本身，终点为深度最大的点。）

- 一号节点/二号节点，图，记录答案的栈（输出长度）

就是在链的合并时候，注意一下细节，不要搞错就行了。

### Code:

干干净净的 O(n)，虽然时间限制为 $3s$，只跑了 $0.15s$。

```cpp

// 无防作弊
#include<bits/stdc++.h>
#define I inline
#define RI register int
#define rep(i,a,b) for(RI i=a;i<=b;++i)
#define dow(i,a,b) for(RI i=a;i>=b;--i)
#define edg(i,u,v) for(RI i=head[u],v;v=e[i].to,i;i=e[i].next)
using namespace std;
const int N=2e5+5;
struct node {
	int a,b,c,d;
	node() {}
	node(int aa,int bb,int cc,int dd) {
		a=aa,b=bb,c=cc,d=dd;
	}
} a[N]; // 记录答案的栈 
struct edge {
	int to,next;
} e[N<<1]; 
int T,n,x,y,cnt,top,mi[N],mj[N],dp[N],son[N][2],head[N<<1];
// mi,mj : 分别为起点和终点
// dp: 表示这个点是 1/2 号链
// son: 表示二号链的左右儿子 
I void add(int from,int to) {
	e[++cnt]=(edge) { to,head[from] };
	head[from]=cnt;
}
I void dfs(int u,int f) {
	dp[u]=1;
	mi[u]=mj[u]=u; // 每个节点一开始都为一号链，那么其起点终点都为其本身。 
	RI sum=0,res=0;
	edg(i,u,v) if(v^f) {
		dfs(v,u); // 先对儿子进行处理 
		res++; // 这里是儿子个数 
		sum+=dp[v]==1; // 这里记录一号链的个数 
	}
	if(sum>=2) { 
		// 如果有两个以上一号链，那么这两个一号链保留，其他接到他们两个身上，新城形成二号链。 
		RI x=0,y=0; // 分别记录两个一号链 
		dp[u]=2; // 二号链 
		edg(i,u,v) if(v^f&&dp[v]==1) {
			if(!x) x=v;
			else {
				y=x,x=v;
				break;
			}
		}
		son[u][0]=x,son[u][1]=y; // 记录子节点（其实这里是写反的，但是不想改了，不影响答案） 
		mi[u]=mj[y],mj[u]=mj[x]; // 目前这个二号链起点/终点为一号链的终点（一号链起点为本身） 
		edg(i,u,v) if(v^f&&v^x&&v^y) { // 如果都不是这三者，那么需要链转移
			a[++top]=node(v,u,mj[v],mj[u]); // 记录答案 
			mj[u]=mi[v]; // 接在了 mj[u]（终点）后面，那么终点更新为链的另一头（是另一头！） 
		}
	} else if(sum==1) {
		RI x=0; // 如果只有一个一号链
		edg(i,u,v) if(v^f&&dp[v]==1) x=v; 
		mj[u]=mj[x]; //先认定当前节点终点为这个一号链的终点 
		edg(i,u,v) if(v^f&&v^x) { // 果都不是这两者，那么需要链转移
			a[++top]=node(v,u,mi[v],mj[u]); // 记录答案 
			mj[u]=mj[v];// mi[v] 接在了 mj[u]（终点）后面，那么终点更新为链的另一头 mj[v]（是另一头！） 
		}
	} else if(res) { // 也要看，必须要有二号链才能合并 
		RI x=0;
		edg(i,u,v) if(v^f) x=v; // 认定一个二号链，其他的链都放在这个上面 
		edg(i,u,v) if(v^f&&v^x) {
			a[++top]=node(v,u,mi[v],mi[x]); // 直接卷走 
			mi[x]=mj[v]; // 解释如上 
		}
		a[++top]=node(son[x][1],x,mi[x],mj[x]); 
		//左右合并，这里 son 数组起作用，son[x][1]其实就是 mi[x] 的起点，其与x断掉，左右链低端合并 
		mj[u]=son[x][1];
		// 右边的 son[x][1] 开始的链，由于是下面练过来，那么链末就是 son[x][1] 了（你也可以换着来） 
	}
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		rep(i,2,n) scanf("%d%d",&x,&y),add(x,y),add(y,x);
		top=0,dfs(1,0);
		printf("%d\n",top);
		rep(i,1,top) printf("%d %d %d %d\n",a[i].a,a[i].b,a[i].c,a[i].d);
		rep(i,1,n) head[i]=mi[i]=mj[i]=dp[i]=son[i][0]=son[i][1]=0;  
		cnt=0;
	}
	return 0;
}
```

too_late 永远可爱！

完结散花！感谢观看！qwqqqqqqqqqqqqq

如果文章帮到你的话，如果你觉得博主非常之良心细致的话，就点点赞呗QwQ。

---

## 作者：岸芷汀兰 (赞：12)

# 一、题目：

[codeforces原题](https://codeforces.com/problemset/problem/1521/D)

[洛谷原题](https://www.luogu.com.cn/problem/CF1521D)

# 二、思路：

这是一道非常清奇的贪心题。

考虑这样一件事情，假设我们切了 $x$ 刀后把整棵树变成了一堆链，那么链的个数一定是 $x+1$ 。

这样的话，我们只需要将这些链**首尾相连**，最终形成的树也一定是一条链，而首尾相连的操作次数也一定是 $x$ 。

我们又可以发现，先切哪一刀和先连哪一条边是无所谓的。我们只需要关心哪些边需要被切来使得切的次数最小。

考虑贪心。首先我们任选一个点作为根。然后假设我们现在要处理以 $v$ 为根的子树。

1. 递归处理 $v$ 的所有儿子。
2. 设 $v$ 现在有 $c$ 个儿子，对 $c$ 进行分类讨论。
   1. 若 $c\leq 1$，啥都不需要干。
   2. 若 $c=2$，切断 $v$ 和 $v$ 的父亲（如果有的话）。
   3. 若 $c\ge 3$，先切断 $v$ 和 $v$ 的父亲（如果有的话），然后随便切断 $v$ 的 $c-2$ 个儿子。

现在我们来感性理解一下为什么这样贪心是对的。当执行完第1步后，$v$ 的所有儿子变成了一条链的**一端**。对于 $v$ 来说，我们需要**尽可能**使得 $v$ 的父亲的儿子数减少，这是因为一个点的儿子数越少，操作数也会变得越少。所以当有必要时，首先考虑切 $v$ 的父亲 ，再切 $v$ 的儿子。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int maxn = 1e5 + 5;

int T, n, head[maxn], tot, top, deg[maxn];
bool vis[maxn];

pair<int, int>pa[maxn];

struct Edge {
    int y, next;
    bool tag;
    Edge() {}
    Edge(int _y, int _next, bool _tag) : y(_y), next(_next), tag(_tag) {}
}e[maxn << 1];

struct Opt{
    int x1, y1, x2, y2;
}opt[maxn];

inline void connect(int x, int y) {
    e[++ tot] = Edge(y, head[x], 1);
    head[x] = tot;
}

void dfs(int x, int fa) {
    int pos = 0;
    for (int i = head[x]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == fa) { pos = i; continue; }
        dfs(y, x);
    }
    int cnt = 0;
    for (int i = head[x]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == fa || !e[i].tag) continue;
        ++ cnt;
    }
    if (cnt <= 1) return;
    if (cnt == 2) {
        if (!fa) return;
        e[pos].tag = e[pos ^ 1].tag = false;
        opt[++ top].x1 = x; opt[top].y1 = fa;
        -- deg[x]; -- deg[fa];
        return;
    }

    if (fa) {
        e[pos].tag = e[pos ^ 1].tag = false;
        opt[++ top].x1 = x; opt[top].y1 = fa;
        -- deg[x]; -- deg[fa];
    }
    int tmp = 0;
    for (int i = head[x]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == fa || !e[i].tag) continue;
        ++ tmp;
        if (tmp <= cnt - 2) {
            e[i].tag = e[i ^ 1].tag = false;
            opt[++ top].x1 = x; opt[top].y1 = y;
            -- deg[x];
            -- deg[y];
        }
    }
}

void dfs2(int x, int fa, int &to) {
    int cnt = 0;
    vis[x] = true;
    for (int i = head[x]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == fa || !e[i].tag) continue;
        dfs2(y, x, to);
        ++ cnt;
    }
    if (!cnt) to = x;
}

int main() {
    T = read();
    while (T --) {
        tot = 1;
        memset(head, 0, sizeof head);
        memset(deg, 0, sizeof deg);
        memset(vis, false, sizeof vis);

        n = read();
        for (int i = 1; i < n; ++ i) {
            int a = read(), b = read();
            connect(a, b); connect(b, a);
            ++ deg[a]; ++ deg[b];
        }
        top = 0;
        dfs(1, 0);
        printf("%d\n", top);

        top = 0;
        for (int x = 1; x <= n; ++ x) {
            if (deg[x] == 0 && !vis[x]) {
                vis[x] = true;
                pa[++ top] = make_pair(x, x);
            }
            if (deg[x] == 1 && !vis[x]) {
                int y = 0;
                dfs2(x, 0, y);
                pa[++ top] = make_pair(x, y);
            }
        }
        -- top;
        for (int i = 1; i <= top; ++ i) {
            opt[i].x2 = pa[i].second;
            opt[i].y2 = pa[i + 1].first;
            printf("%d %d %d %d\n", opt[i].x1, opt[i].y1, opt[i].x2, opt[i].y2);
        }
    }
    return 0;
}

```



---

## 作者：流水行船CCD (赞：9)

来一发很恶心的 DP 做法。

# 思路

- 设 $F_x$ 表示将 $x$ 子树转化为一条以 $x$ 为端点的链最小操作次数（注意我这里和其他题解不一样的是我同时删边加边，树始终保持联通）。设 $G_x$ 表示将 $x$ 子树转化为一条跨越 $x$ 的链的最小操作次数。
- 先考虑对于 $G$ 的转移，不难发现一共有如下三种情况：

![pic1](https://cdn.luogu.com.cn/upload/image_hosting/nu9ggh2q.png)

- 其中 $F1,F2$ 的选择我们不必枚举，可以贪心的选择儿子中将 $G_x$ 换为 $F_x$ 答案最小的两个，即 $F_x - G_x$ 最小的两个，设这两个儿子为 $son_1,son_2$，$x$ 的儿子为 $son_{1,2,\dots,k}$。不难列出如下三个状态转移方程：
  -  况一：$G_x = F_{son_1} + F_{son_2} + \sum_{i=3}^{i \le k} G_i + k - 2$。
  -  况二：$G_x = F_{son_1} +\sum_{i=2}^{i \le k} G_i + k - 1$。
  -  况三：$G_x = \sum_{i=1}^{i \le k} G_i + k - 1$。
- 而对于 $F_x$ 的转移，就是上文提及的况二和况三。

- 计算完最优步数，难点在于输出方案。
- 我们记录每一个 DP 状态由谁转移而来，在第二次 DFS 的时候就可以确定每一个点是用上述那种情况修改最优了。发现在当前 $x$ 处，我们只需要考虑上图中删除的边和新增的绿色边，其余转为子问题递归求解，我们只需要记录当前子树转化的链的链头和链尾，用 `pair<int, int>` 回传，在每一个点处拼接即可。
- 一共五种情况，注意不要漏算即可。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
namespace fast_IO{
...
}using namespace fast_IO;
const int N = 2e5 + 7;
namespace bestpiclib {
	int Test, n;
	struct Opera {int x1, y1, x2, y2;}; vector<Opera> Ans;
	int f[N], g[N], pf[N], pg[N];
	vector<int> T[N], son[N];
	inline void solve(int x, int p) {
		int Gsum = 0; 
		for (int i = 0, v = 0; i < (int)T[x].size(); ++i) {
			v = T[x][i];
			if (v == p) continue;
			solve(v, x), son[x].emplace_back(v), Gsum += g[v] + 1;
		} 
		sort(son[x].begin(), son[x].end(), [](int a, int b) {return g[a] - f[a] > g[b] - f[b];});
		if (son[x].empty()) {
			f[x] = g[x] = 0;
		} else if (son[x].size() == 1) {
			// son[x][0] 选择 G 
			if (f[son[x][0]] <= g[son[x][0]] + 1) {
				f[x] = g[x] = f[son[x][0]], pf[x] = pg[x] = 3;
			} else {
				f[x] = g[x] = g[son[x][0]] + 1, pf[x] = pg[x] = 2;
			}
		} else {
			//son[x][0][1][2] 选择 G 2
			//son[x][0] 选择 F，son[x][1][2][3] 选择 G 3
			//son[x][0] son[x][1] 选择 F，son[x][2][3][4] 选择 G 1
			if (Gsum - g[son[x][0]] + f[son[x][0]] - 1 <= Gsum) {
				f[x] = Gsum - g[son[x][0]] + f[son[x][0]] - 1, pf[x] = 3;
			} else {
				f[x] = Gsum, pf[x] = 2;
			}
			if (Gsum <= Gsum - g[son[x][0]] - g[son[x][1]] + f[son[x][0]] + f[son[x][1]] - 2 && Gsum <= Gsum - g[son[x][0]] + f[son[x][0]] - 1) {
				g[x] = Gsum, pg[x] = 2;
			} else if (Gsum - g[son[x][0]] - g[son[x][1]] + f[son[x][0]] + f[son[x][1]] - 2 <= Gsum - g[son[x][0]] + f[son[x][0]] - 1) {
				g[x] = Gsum - g[son[x][0]] - g[son[x][1]] + f[son[x][0]] + f[son[x][1]] - 2, pg[x] = 1;
			} else {
				g[x] = Gsum - g[son[x][0]] + f[son[x][0]] - 1, pg[x] = 3;			
			}
		}
	}
	inline pair<int, int> getans(int x, int op) {
		int head = x, tail = x;
		if (son[x].empty()) return make_pair(x, x);
		if (op) { // G
			if (pg[x] == 1) {
				for (int i = 0; i < son[x].size(); ++i) {
					pair<int, int> t = getans(son[x][i], i <= 1 ? 0 : 1);
					if (i >= 2) Ans.emplace_back((Opera) {x, son[x][i], tail, t.first});
					tail = t.second;
					if (i == 0) head = t.second;
				}
			} else if (pg[x] == 3) {
				for (int i = 0; i < son[x].size(); ++i) {
					pair<int, int> t = getans(son[x][i], i <= 0 ? 0 : 1);
					if (i >= 1) Ans.emplace_back((Opera) {x, son[x][i], tail, t.first});
					tail = t.second;
				}
			} else {
				for (int i = 0; i < son[x].size(); ++i) {
					pair<int, int> t = getans(son[x][i], 1);
					Ans.emplace_back((Opera) {x, son[x][i], tail, t.first});
					tail = t.second;
				}
			} 
		} else {  // F
			if(pf[x] == 2) {
				for (int i = 0; i < son[x].size(); ++i) {
					pair<int, int> t = getans(son[x][i], 1);
					Ans.emplace_back((Opera) {x, son[x][i], tail, t.first});
					tail = t.second;
				}
			} else {
				for (int i = 0; i < son[x].size(); ++i) {
					pair<int, int> t = getans(son[x][i], i <= 0 ? 0 : 1);
					if (i >= 1) Ans.emplace_back((Opera) {x, son[x][i], tail, t.first});
					tail = t.second;
				}
			}
		}
		return {head, tail};
	}
	signed main() {
		ld >> Test; int u = 0, v = 0;
		while (Test--) {
			ld >> n;
			REP(i, 2, n) {
				ld >> u >> v;
				T[u].emplace_back(v), T[v].emplace_back(u);
			}
			solve(1, 0), getans(1, 1);
//			if (Ans.size() ^ min(f[1], g[1])) return jyt << "FUCKKKKKK\n", 0;
			jyt << (int)Ans.size() << '\n';
			for (Opera P : Ans) jyt << P.x1 << ' ' << P.y1 << ' ' << P.x2 << ' ' << P.y2 << '\n';
			Ans.clear(); REP(i, 1, n) T[i].clear(), son[i].clear(), pf[i] = pg[i] = f[i] = g[i] = 0;
		}
		return 0;
	}
}
signed main() {
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	bestpiclib::main();
	return 0;
}
```

---

## 作者：Imitators (赞：5)

由于我们切的边和加的边个数相等。

策略显然为把原树剖成一堆链，然后首尾相连。

问题转化为，切断最少的边把一棵树剖分成一堆链。

官方给的是贪心，不过没给官方证明，评论区有个老哥发了一个，我不是很懂......

这里给出一个 dp 做法。

---

$f_{x,0}$ 表示把 $x$ 的子树剖分成一堆链最少切几条边。

$f_{x,1}$ 表示把 $x$ 的子树剖分成一堆链最少切几条边，并且 $x$ 是一条链的一段。

$son_x$ 表示 $x$ 的儿子个数。

转移一共有三种情况。

1. $x$ 被当成一个单独的点，$v_1=\sum\limits_{u\in sub(x)} f_{u,0}+son_x$
2. $x$ 作为一条链的一端, $v_2=\sum\limits_{u\in sub(x)}f_{u,0}-Max \{f_{u,0}-f_{u,1}\}+son_x-1$
3. $x$ 作为两条链的合并点，$v_3=\sum\limits_{u\in sub(x)}f_{u,0}-Max \{f_{u,0}-f_{u,1}\}-SecondMax \{f_{u,0}-f_{u,1}\}+son_x-2$

根据定义，有 $f_{u,0}=Min\{v_1,v_2,v_3\}$,$f_{u,1}=Min\{v_1,v_2\}$。

---

求具体方案也很基础，直接根据 $f$ 的转移情况来处理。

复杂度 $\mathcal{O(n)}$。

处理次大那个地方我直接排序的，复杂度$\mathcal{O(n\log n)}$。

注意没有次大的时候 $v_3$ 相当于 $-\infty$，而不是 $0$。

$\mathcal{Code}$ （可能会长一些

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int x,y;
vector<int> v[100010],e[100010];
int f[100100][2];
inline bool cmp(int x,int y){
    return f[x][0]-f[x][1]>f[y][0]-f[y][1];
}
inline void predfs(int x,int fa){
    for(auto y:e[x]){
        if(y==fa) continue;
        v[x].push_back(y);
        predfs(y,x);
    }
}
inline void dfs(int x){
    int ch=0,sum=0;
    for(auto y:v[x]){
        dfs(y);
        sum+=f[y][0];ch++;
    }
    if(ch==0){
        f[x][0]=f[x][1]=0;
        return ;
    }
    sort(v[x].begin(),v[x].end(),cmp);
    int y=v[x][0],z;
    f[x][1]=min(sum+ch,sum-(f[y][0]-f[y][1])+ch-1);
    if(v[x].size()>=2){
        z=v[x][1];
        f[x][0]=sum-(f[y][0]-f[y][1])-(f[z][0]-f[z][1])+ch-2;
    }
    else f[x][0]=f[x][1];
    f[x][0]=min(f[x][1],f[x][0]);
}
// dfs 为计算 f[x][0],f[x][1] 的函数
int ind[100100];bool vis[100100];
inline void link(int x,int y){
    e[x].push_back(y),e[y].push_back(x);
    ind[x]++,ind[y]++;
}
vector<pair<int,int> > sb,ad;
inline void getans(int x,int flag){
    int ch=0,sum=0;
    for(auto y:v[x]){ch++;sum+=f[y][0];}
    if(ch==0){
        return ;
    }
    int y=v[x][0],z;
    if(flag==1||f[x][0]==f[x][1]){
        if(f[x][1]==sum+ch)
            for(auto y:v[x]) getans(y,0),sb.push_back(make_pair(x,y));
        else{
            getans(y,1);link(x,y);
            for(int i=1;i<v[x].size();i++){int y=v[x][i];getans(y,0);sb.push_back(make_pair(x,y));}
        }
        return ;
    }
    if(v[x].size()>=2){
        z=v[x][1];
        getans(y,1);link(x,y);
        getans(z,1);link(x,z);
        for(int i=2;i<v[x].size();i++){int y=v[x][i];getans(y,0);sb.push_back(make_pair(x,y));}
    }
    else {
        if(f[x][0]==sum+ch)
            for(auto y:v[x]) getans(y,0),sb.push_back(make_pair(x,y));
        else{
            getans(y,1);link(x,y);
            for(int i=1;i<v[x].size();i++){int y=v[x][i];getans(y,0);sb.push_back(make_pair(x,y));}
        }
    }
}
// getans 为求解删的边的函数
int ed=0;
inline void paint(int x,int fa){
    vis[x]=1;ed=x;
    for(auto y:e[x]){
        if(y==fa) continue;
        paint(y,x);
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<=n;i++)ind[i]=f[i][0]=f[i][1]=vis[i]=0,v[i].clear(),e[i].clear();
        sb.clear();ad.clear();
        for(int i=1;i<n;i++){
            int x,y;cin>>x>>y;
            e[x].push_back(y),e[y].push_back(x);
        }
        predfs(1,0);
        for(int i=0;i<=n;i++) e[i].clear();
        dfs(1);
        getans(1,0);
        //-----------------------------------
        int pre=0;
        for(int i=1;i<=n;i++){
            if(ind[i]==1||ind[i]==0){
                if(vis[i]) continue;
                paint(i,0);
                if(pre!=0) ad.push_back(make_pair(pre,i));
                pre=ed;
            }
        }
        // 以上为求解加边的过程
        cout<<f[1][0]<<endl;
        for(int k=0;k<sb.size();k++) cout<<sb[k].first<<" "<<sb[k].second<<" "<<ad[k].first<<" "<<ad[k].second<<endl;
    } 
}// sb -> 删边 ; ad -> add 加边
```

---

## 作者：Unnamed114514 (赞：0)

因为加的边数和断的边数相等，我们只需要最小化断的边数就行了。

对每个点处理完后的儿子数 $c$ 进行讨论：

- $c=1$，就是一条链，什么也不干。

- $c=2$，断掉它和它父亲之间的边。

- $c>2$，断掉它和它父亲之间的边，然后保留 $c-2$ 个儿子。

为什么先断父亲是对的呢？因为如果此时不断父亲只断儿子，那么它的父亲可能会因为儿子很多而断掉和它的边，这样的话就多断了条边。

而先断掉父亲，因为儿子已经操作完了，所以儿子和它的边一定不会断掉，所以不会产生多余消耗，因此它是对的。

这样做最后会得到若干条链，把它们首尾相连即可。

---

## 作者：TernaryTree (赞：0)

Preface：这题估计是凭借这个输出方案得到的 $2500$。

树形 dp。$f_{u,1/2}$ 表示以结点 $u$ 为根的子树变成链，$u$ 必须/不一定 成为链的一端的最小次数。

则 

$$f_{u,1}=\min_{u\to v'}\left(f_{v',1}+\sum_{u\to v,v\neq v'}\min(f_{v,1},f_{v,2})+1\right)$$

$$f_{u,2}=\min_{u\to v'_1,u\to v'_2,v'_1\neq v'_2}\left(f_{v'_1,1}+f_{v'_2,1}+\sum_{u\to v,v\neq v'_1,v\neq v'_2}\min(f_{v,1},f_{v,2})+1\right)$$

这个随便做，记一个 $s=\sum\limits_{u\to v}\min(f_{v,1},f_{v,2})+1$ 和最大以及次大的 $\min(f_{v,1},f_{v,2})+1-f_{v,1}$ 即可。代码贪图方便排序了一下，多一个 $\log$ 无伤大雅。

最小操作次数即为 $f_{1,2}$。

考虑递归地构造方案，令 `solve(u, fa, id) -> pair<int, int> ` 表示当前要将 $u$ 以内子树变成链，$u$ 必须/不一定 成为链的一端，构造出来的链的两端点。分类讨论。具体实现巨大多喝水。

[Code 3.05KB](https://www.luogu.com.cn/paste/aa26b17k)

---

## 作者：E1_de5truct0r (赞：0)

DP 题，但是记录方案数比较恶心。

好在运气比较好，写完一遍过了，没有体会到调试的恶心（

## 思路

首先我们要最小化操作数，其实就是最小化删边数量。

那么删边数量是多少呢？就是把一棵树删成若干条链（可能为单个点）的最小次数。

所以考虑 DP。$dp_{u,0/1}$ 表示 $u$ 的子树内，$u$ 是否在链的一端的时候，把 $u$ 子树删成若干条链的最小代价。

这分别是两种情况的图示：

- $u$ 在链的一端：

	![](https://cdn.luogu.com.cn/upload/image_hosting/y1n5djga.png)

- $u$ 不在链的一端（在一条链上）：

	![](https://cdn.luogu.com.cn/upload/image_hosting/youlmsq5.png)

那么明显地，我们可以对不在链的一端的情况，强制选择两个子节点；对在链一端的情况，强制选一个子节点。

那么有 DP 转移：

$$\begin{cases}dp_{u,0}=\min\{dp_{u,1}+dp_{v,1},dp_{u,0}+\min\{dp_{v,0},dp_{v,1}\}+1\}\\dp_{u,1}=\min\{S+dp_{v,1},dp_{u,1}+\min\{dp_{v,0},dp_{v,1}\}+1\}\\S=S+\min\{dp_{v,0},dp_{v,1}\}+1\end{cases}$$

答案为 $\min\{dp_{1,0},dp_{1,1}\}$。

关于记录路径，我们可以建一个数组表示对于 $dp_{u,0/1}$，最优策略选择了哪（两）个点。然后我们从最后的位置开始向前递归，用两个 vector 分别记录删除的边和加入的边。如果出现了 $v \in E_u$ 并且 $u$ 没有被选择，那么 $v,u$ 就要删除；同时我们加入 $v$ 所在的链。一开始的递归之前，我们先加入 1 所在的链。

然后我们假设出现了 $m$ 条需要删除的边以及 $m+1$ 条链，我们把这 $m+1$ 条链首尾相连连出 $m$ 条边即可。

## 代码

[Code & Submission](https://codeforces.com/contest/1521/submission/219734843)

---

