# [POI 2011] SMI-Garbage

## 题目描述

有一个可以看成无向图的城市，上面有 $n$ 个点和 $m$ 条边。

每一天，有若干辆垃圾车按照**环形**来跑一圈。并且，**对于一辆垃圾车，** 除了起点以外不能跑两次。

一条路有 $2$ 种状态：清洁的（用 `0` 表示）或不清洁的（用 `1` 表示）。每次垃圾车经过，都会改变这条路的状态。

因为有些路上的人不交垃圾清理费，所以市长想要那些路变得不清洁；除此之外的路要清洁。那么，如何安排垃圾车，才能使得市长目的达到呢？

By @[dengziyue](/user/387840)

感谢 @cn：苏卿念 提供SPJ

## 样例 #1

### 输入

```
6 8
1 2 0 1
2 3 1 0
1 3 0 1
2 4 0 0
3 5 1 1
4 5 0 1
5 6 0 1
4 6 0 1```

### 输出

```
2
3 1 3 2 1
3 4 6 5 4```

# 题解

## 作者：寒鸽儿 (赞：25)

本篇代码能过(经过减小vector的数量取得足够高的效率)2019.11.08  
欧拉回路拆环  
考虑在入栈的时候检查该元素是否在栈中,若在,表示成环。  
注意:由于常见的求欧拉路的程序给出的结尾都不是开头点,所以在dfs调用后栈里面还剩下一个环,输出即可。  
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#define itra vector<int>::iterator

using namespace std;

const int N = 123456, M = 1234567;
int head[N], deg[N], ver[M<<1], vis[M<<1], nex[M<<1], tot;
inline void addedge(int u, int v) {
	ver[tot] = v; nex[tot] = head[u]; head[u] = tot++;
}

vector<int> va[N/10];
vector<int> sta;


int instack[N], vist[N], tt;
void dfs(int cur) {
	vist[cur] = 1;
	for(int i = head[cur]; ~i; i = nex[i])
		if(!vis[i]) {
			vis[i] = vis[i^1] = 1;
			head[cur] = nex[i];
			dfs(ver[i]);
			if(instack[ver[i]]) {
				va[tt].push_back(ver[i]);
				while(sta.back() != ver[i]) {
					va[tt].push_back(sta.back());
					instack[sta.back()] = 0;
					sta.pop_back();
				}
				va[tt].push_back(ver[i]);
				++tt;
			} else {
				sta.push_back(ver[i]);
				instack[ver[i]] = 1;
			}
		}
}

int main() {
	memset(head, -1, sizeof(head));
	int n, m, u, v, f, t, flg = 1;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &u, &v, &f, &t);
		if(f^t) {
			addedge(u, v); addedge(v, u);
			++deg[u]; ++deg[v];
		}
	}
 	for(int i = 1; i <= n; ++i) {
 		if(deg[i]%2) {
 			flg = 0;
 			break;
 		}
 	}
 	if(!flg) {
 		printf("NIE\n");
 		return 0;
	 }
	 for(int i = 1; i <= n; ++i) 
	 	if(!vist[i]) {
	 		dfs(i);
	 		if(instack[i]) {
	 			va[tt].push_back(i);
	 			while(!sta.empty()) {
	 				va[tt].push_back(sta.back());
	 				instack[sta.back()] = 0;
	 				sta.pop_back();
	 			}
	 			++tt;
	 		}
	 	}
	 printf("%d\n", tt);
	 for(int i = 0; i < tt; ++i) {
	 	printf("%d ", va[i].size()-1);
	 	for(itra it = va[i].begin(); it != va[i].end(); ++it) {
	 		printf("%d ", (*it));
	 	}
	 	printf("\n");
	 }
	return 0;
} 
```

---

## 作者：big_turkey (赞：24)

### 2024/11/29 更新
题解又被人hack了，来补。

把原来存欧拉回路的空间上限增大了。

这里感谢 [@chenxi2009](https://www.luogu.com.cn/user/1020063) 指出错误。

### 2021/10/18 更新

题解被人hack了，一年后过来补。

这里感谢 @fzj2007 提供的hack数据。

下面代码已通过LOJ的强数据和hack数据。

**下面部分更新的地方都用粗体表示**

### 题目分析
 
总共有m条边，走过一条边就是修改该边权值。
 
每次要求走过一个简单环上的边，即从某个点开始走过该点存在的联通图（原图可能不联通），初始权值与最终权值相等的边走偶数次，不相等的走奇数次。
 
为什么用欧拉回路？
 
- 欧拉回路的定义：存在一条从某个点开始，恰好不重不漏经过每条边一次（点可重复），最终回到该点。
 
- 欧拉图的定义：存在欧拉回路的图。
 
- 欧拉图的判定：每个点的度数都为偶数。
 
通过以上定义和判定，可以考虑权值不相等的边通过找欧拉回路的方法来。
 
权值相等的边，因为每次都必须走偶数次，相当于拆成了两条边，这样实际上就使得改边对连接的两点度数加了 +2，根据欧拉回路的定义，删去这条边即对两点度数 -2，还使得图成为欧拉图了（只用走剩下的边一次），就可以直接找欧拉回路了。
 
原代码没有处理**不经过重复边或起点以外结点的环**，即每次**只能走以起点开始的环**

这样的话，就可以**再开一个栈专门来存当前的欧拉回路**，如果当前的点已经在栈中，说明已经形成一个环，将该环储存答案并弹出。

### 代码细节处理

我原来的代码是用栈模拟 dfs 的搜索和回溯过程。

每次取栈顶元素，遍历其**没有遍历过的边**，将出点存入栈中。

遍历没有遍历过的边后要将链头都要**指向下一条未遍历的边**，以保证时间复杂度正确。

如果没有可遍历的出边，那么就应该回溯，将该点弹出并存入答案栈中，此时答案栈存入的即是**以 $s$ 为起点能遍历完所有可到达的边的欧拉回路，可能包含除起点以外的环**，所以存入时要判断是否形成环，成环时将答案处理。

### 代码

以下代码省去模板和一些简单的宏。

~~应该没问题吧~~


~~~cpp
const ll maxn=1e5+5,maxm=1e6+5;

ll n,m,cnt=1,head[maxn];
ll deg[maxn];

ll tot;
vector<ll> ans[maxm];

ll stk[maxm],tp;
ll stkans[maxm],tpans;//存欧拉回路的答案栈
bool instk[maxm]；//标记是否在答案栈中
bool vis[maxm];

struct edge{
	ll to,next,vis;
}e[maxm<<1];

void add(ll x,ll y){
	e[++cnt]=(edge){y,head[x],0};
	head[x]=cnt;
	deg[x]++;
}

#define failed return puts("NIE"),0

void euler(ll s){
	stk[tp=1]=s;
	for(ll x,i;tp;){
		x=stk[tp],i=head[x];
		while(i&&e[i].vis) 
			head[x]=i=e[i].next;
		if(i){
			stk[++tp]=e[i].to;
			e[i].vis=e[i^1].vis=true;
			head[x]=e[i].next;//链头指向下一条边
		}
		else{
			tp--;
			vis[x]=true;
			if(instk[x]){
				ans[++tot].push_back(x);
				while(tpans&&stkans[tpans]!=x)
					ans[tot].push_back(stkans[tpans]),
					instk[stkans[tpans--]]=false;
				ans[tot].push_back(x);
			}
			else instk[stkans[++tpans]=x]=true;
		}
	}
}

void output(){
	printf("%lld\n",tot);
	FOR(i,1,tot){
		printf("%lld\n",ans[i].size()-1);
		for(auto x:ans[i]) printf("%lld ",x);
		puts("");
	}
}

int main(){
	n=read(),m=read();
	for(ll x,y,o,p;m;m--){
		x=read(),y=read(),o=read(),p=read();
		if(o^p) add(x,y),add(y,x);
	}
	FOR(i,1,n) if(deg[i]&1) failed;
	FOR(i,1,n) if(!vis[i]) euler(i);
	output();
	return 0;
}
~~~

### 如果有错误的地方，请私信我

---

## 作者：chenxi2009 (赞：5)

## 思路
**本文包含 vector 存图写法。**

首先要知道欧拉回路相关问题的经典结论：每条边的经过次数可以对二取余。也就是说，存在一个方案经过这条边两次，就存在方案不经过这条边；经过奇数次同理，这里不证。

所以令初态与终态不同的边是需要经过一次的，相同的边可以直接舍去，问题变为给出一个方案用若干个环覆盖每条边恰好一次。

如果一个点度为奇数，它的边必然不能被若干个环全部覆盖，无解；否则任一点度为偶数，对于此图每个连通块存在欧拉回路，一条回路必然能拆成若干个简单环。

考虑一个欧拉回路的序列（这条回路经过的所有点构成的序列），如下图，此图存在欧拉回路 `1 2 3 5 6 7 3 4 1`：\
![](https://cdn.luogu.com.cn/upload/image_hosting/5r6bjek5.png)\
发现标蓝的边和标红的边分别是一个简单环，共同构成回路。如果把蓝边拆出，红边环序列为 `1 2 3 4 1`。

进一步探究，发现所有回路本质上都是若干个简单环，根据简单环的定义可知**简单环的序列首尾相同，除此外其他数字仅出现一次**。\
在寻找欧拉回路并存入栈的过程中，如果说当前结点入栈时栈里有相同的结点，说明构成了一个环，这时出栈直到碰到此结点，保留此点，就成功地摘除了该环。

**欧拉回路正确性相关**

此图是无向图，我们需要保证每条边只经过一次，那么势必要在一条边走过后用正确的方式打上标记。考虑存边时为其编号，每次走过一条边给对应编号打上标记，有效地防止其被双向经过。

**欧拉回路效率相关**

本题边范围达到百万，考虑双向存边发现 $2m\le2\times10^6$，必须使用 $O(m)$ 级的算法。

为防止重复考虑同边，令一个点的边按顺序遍历，每遍历一条边就舍弃它。手写邻接表存图可以将表头移动至下一条边，vector 存图可以标记第一条有用边的下标（初始为零）。

**欧拉回路伪代码**

自行理解，由于不会有边被重复考虑，时间复杂度 $O(m)$。
```
搜索点 u:
    从 head_u 开始 i 遍历出边:
        if i < head_u: i <- head_u - 1
        elif num_边 被标记: head_u <- i + 1
        else: head_u <- i + 1, 标记 num_边, 搜索此边入点
    if u 在栈中:
        环数 + 1
        u 入环
        重复 将栈顶入环，将栈顶出栈 直到栈顶为 u
        u 入环
    else:
        将 u 入栈
```
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,u,v,s,t,d[100001],head[100001],cnt;
bool bg[1000001],ins[100001];
vector<int>e[100001],bh[100001];
vector<int>vs[1000001];
stack<int>stk;
void sch(int u){
	for(unsigned i = head[u];i < e[u].size();i ++){
		if(int(i) < head[u]){//这一个判断防止内层搜索经过该点时舍弃的边被重复考虑
			i = head[u] - 1;
			continue;
		}
		if(bg[bh[u][i]]){//标记
			head[u] = i + 1;
			continue;
		}
		head[u] = i + 1;
		bg[bh[u][i]] = true;
		sch(e[u][i]);
	}
	if(ins[u]){
		cnt ++;
		vs[cnt].push_back(u);
		while(stk.top() != u){
			vs[cnt].push_back(stk.top());
			ins[stk.top()] = false;
			stk.pop();
		}
		vs[cnt].push_back(u);
	}
	else stk.push(u),ins[u] = true;//标记入栈
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i ++){
		scanf("%d%d%d%d",&u,&v,&s,&t);
		if(s == t) continue;
		e[u].push_back(v),e[v].push_back(u),d[u] ++,d[v] ++;
		bh[u].push_back(i),bh[v].push_back(i);
	}
	for(int i = 1;i <= n;i ++){//判无解
		if(d[i] & 1){
			printf("NIE");
			return 0;
		}
	}
	for(int i = 1;i <= n;i ++){
		if(head[i] < int(e[i].size())){//对于每一个连通块都要找欧拉回路
			sch(i);
			ins[stk.top()] = false;//最后栈中还剩下一个点，出栈
			stk.pop();
		}
	}
	printf("%d\n",cnt);
	for(int i = 1;i <= cnt;i ++){
		printf("%d ",int(vs[i].size()) - 1);
		for(auto j : vs[i]) printf("%d ",j);
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：P2441M (赞：3)

## 题意
给定一张 $n$ 个点 $m$ 条边的无向图，边有 $0/1$ 边权和目标的 $0/1$ 边权。每次可以选取一个简单环，将环上的边权取反。求一个合法方案。$1\leq n\leq 10^5,1\leq m\leq 10^6$。

## 题解
之前做过但有点忘了，重做一下。

考虑 $s=t$ 的边，它们需要被经过偶数次，我们任取两个经过它的简单环，如果将该边删去，那完全可以把这两个简单环合并成一个，一定更优。于是只需要保留 $s\neq t$ 的边，DFS 找环，用栈记录方案。判无解等价于判断是否存在欧拉回路，即每个点都是偶度的。加上当前弧优化，时间复杂度为 $\mathcal{O}(n+m)$。

TLE 大概是当前弧写假了。

## 代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 5, M = 2e6 + 5;

int n, m, k, deg[N], head[N];
int top, stk[N];
bool ve[M], in_stk[N], v[N];
vector<int> ans[M];

struct AdjList {
	int tot, head[N], nxt[M], to[M];
	void init() {
		tot = -1;
		for (int i = 1; i <= n; ++i) head[i] = -1;
	}
	void insert(int x, int y) {
		to[++tot] = y;
		nxt[tot] = head[x], head[x] = tot;
	}
} g;

void dfs(int x) {
	v[x] = 1;
	for (int &i = g.head[x]; ~i; i = g.nxt[i]) {
		if (ve[i]) continue;
		ve[i] = ve[i ^ 1] = 1;
		dfs(g.to[i]);
	}
	if (in_stk[x]) {
		ans[++k].push_back(x);
		while (top && stk[top] != x) {
			int y = stk[top--];
			ans[k].push_back(y), in_stk[y] = 0;
		}
		ans[k].push_back(x);
	} else in_stk[x] = 1, stk[++top] = x;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m, g.init();
    while (m--) {
    	int u, v, s, t; cin >> u >> v >> s >> t;
    	if (s == t) continue;
    	g.insert(u, v), g.insert(v, u);
    	++deg[u], ++deg[v];
	}
	for (int i = 1; i <= n; ++i) if (deg[i] & 1) return cout << "NIE", 0;
	for (int i = 1; i <= n; ++i) if (!v[i]) dfs(i);
	cout << k << '\n';
	for (int i = 1; i <= k; ++i) {
		cout << ans[i].size() - 1 << ' ';
		for (int j : ans[i]) cout << j << ' ';
		cout << '\n';
	}
    return 0;
}
```

---

## 作者：NaNO2_Cabbage (赞：2)

# [POI2011] SMI-Garbage Solution

## 题意描述

一条路有两种状态，每次访问会改变路的状态。显然，初始状态与目标状态相同的路并不需要加入这个无向图，因此题意转为：给定一个无向图，求所有简单环。

## 解法分析

由求简单环不难想到欧拉回路，由欧拉回路性质知，无向图中不存在欧拉回路的条件是存在度数为奇数的点，至此，无解情况处理完毕。利用一个元素两次出现来判断是否存在一个环，若出现环，将其输出到一个 vector 中存储。

## 参考代码

``` cpp
#include <bits/stdc++.h>
#define upf(i, n, k) for (int i = k; i <= n; i++)
#define lowf(i, n, k) for (int i = n; i >= k; i--)
#define Max(a, b, c) max(a, max(b, c))
#define Min(a, b, c) min(a, min(b, c))
#define ofile(N) freopen(N ".in", "r", stdin), freopen(N ".out", "w", stdout)
#define ri register int
#define ie inline
#define ll long long
#define read() input<int>()
#define readll() input<ll>()
using namespace std;

template <typename TT>
ie TT input() {
	TT s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}

template <typename TT>
ie void out(TT a) {
	if (a < 0) putchar('-'), a = -a;
	if (a >= 10)
		out(a / 10);
	putchar(a % 10 + '0');
}

const int mn = 1e6 + 5;
int n, m, x, y, now, tar, cnt, nb, vis[10000010], dg[mn], viss[mn], ins[mn];
int head[mn << 1], nxt[mn << 1], ver[mn << 1], tot;
inline void add(int u, int v) {
	ver[tot] = v, nxt[tot] = head[u], head[u] = tot++;
}
vector<int> ret[mn << 1];
stack<int> s;

inline void dfs(int u) {
	viss[u] = 1; //标记该点是否走过
	for (ri i = head[u]; ~i; i = nxt[i])
		if (!vis[i]) {
			vis[i] = vis[i ^ 1] = 1; //标记边是否经过
			head[u] = nxt[i]; //当前弧优化
			int v = ver[i];
			dfs(v);
		}
	if (ins[u]) {
		ret[++cnt].push_back(u);
		while (s.top() != u) ret[cnt].push_back(s.top()), ins[s.top()] = 0, s.pop();
		ret[cnt].push_back(u); //保存答案
	} else
		s.push(u), ins[u] = 1;
}

int main() {
	memset(head, -1, sizeof head);
	n = read(), m = read();
	for (ri i = 1; i <= m; i++) {
		x = read(), y = read(), now = read(), tar = read();
		if (now ^ tar) add(x, y), add(y, x), dg[x]++, dg[y]++;
	}
	for (ri i = 1; i <= n; i++)
		if (dg[i] & 1) return puts("NIE"), 0; //欧拉回路判断无解
	for (ri i = 1; i <= n; i++)
		if (!viss[i]) 
			dfs(i);
	out(cnt), puts("");
	for (ri i = 1; i <= cnt; i++) {
		out(ret[i].size() - 1), putchar(' ');
		for (auto j : ret[i])out(j), putchar(' ');
		puts("");
	}
	return 0;
}
```

## 后记

本题细节较多，作者太菜了调了许久，作题解以纪念。

是道锻炼思维/练习欧拉回路的好题。

---

## 作者：qzmoot (赞：2)

# 题目大意
[题目传送门](https://luogu.com.cn/problem/P3520)

给我们一个无向图，需要找到所有的简单环。
# 思路
首先这些边中有许多边是没有用的，直接判断```s==t```就不要，否则就要这条边。

判断是否是```NIE```十分简单，看有没有点的度是奇数即可。

接着我们进行 dfs，将判断过的简单环上的点全部标记，之后可以用 vector 或栈存储答案都行。

---

## 作者：TangyixiaoQAQ (赞：1)

# 思路解析
将道路分为需要反转和不需要反转两类：

如果有一种方案中边被至少两个环经过，那么容易把两个环组合去掉重复边，依然能变成若干个简单环。

如果存在方案，则一定有恰好只经过一次需要反转的道路的方案。

因此直接考虑如何用环路经过所有需要反转的道路。这是典型的欧拉回路问题，直接解决即可。

---

## 作者：BDFZ_hym_AK_hym_ing (赞：1)

### 前置知识：
[欧拉图](https://oi-wiki.org/graph/euler/)  
然后好像也就没啥了。
### 思路分析：
易得会有一个发现：当 $s\ne t$ 时才需要将边加入，此时只需判断每个连通块是否都存在欧拉回路，即可判断是否有合法方案。  
我们来证明一下：  
当有边的状态相等（即 $s=t$）时，因为在环里除起点外不会出现两次，即不会有两个及以上的点在同一个环内出现两次，所以这一条边至少出现在两个不同的环里，所以这条边至少出现在两个不同的环里。  
我们令这条边的端点为 $a,b$，而两个环分别为 $a,u_1,u_2,\ldots,u_n,b$ 和 $b,v_1,v_2,\ldots,v_m,a$，注意到此时可以合并为 $a,u_1,u_2,\ldots,u_n,b,v_1,v_2,\ldots,v_m$，此时少掉了两条 $a$ 到 $b$ 的边，发现可以直接舍去，即所有边最多只需要存在 $1$ 次，所以只有当 $s\ne t$ 时才需要将边加入。  
然后就可以直接跑回路了，但这题边的数量较大，所以只能使用 $O(m)$ 复杂度的（不过不知道是不是我常数太大了），尽量不要用 map。  
对于答案的输出，当回路中碰上一个已出现过的数，直接将两个相同数中间的数连同这两个相同数一起按顺序输出就行了。
### 代码：
个人认为讲的已经清楚了，所以直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int v,id;
}; 
inline int read(){
	int x=0;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
int n,m; 
bool use[1000005];
vector<node>g[100005];
int gs=0;
vector<int>ans[5000005];
int s[100005],hd;
int x[100005];
int d[100005];
bool vis[100005];
int ins[100005];
void dfs(int now){
	int i;
	for(i=x[now];i<g[now].size();i=x[now])
	{
		x[now]++;
		if(use[g[now][i].id])
		{
			continue;
		}
		use[g[now][i].id]=true;
		vis[g[now][i].v]=true;
		dfs(g[now][i].v);
	}
	if(ins[now])
	{
		gs++;
		ans[gs].push_back(now);
		while(s[hd]!=now)
		{
			ans[gs].push_back(s[hd]);
			ins[s[hd]]--;
			hd--;
		}
		ans[gs].push_back(now);
	}
	else
	{
		ins[now]++;
		s[++hd]=now;
	}
}
int main(){

	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	n=read();
	m=read();
	int i,j;
	for(i=1;i<=m;i++)
	{
		int u=read(),v=read(),a=read(),b=read();
		if(a!=b)
		{
			g[u].push_back(node{v,i}); 
			g[v].push_back(node{u,i});
			d[u]++;
			d[v]++;
		}
	}
	for(i=1;i<=n;i++)
	{
		if(d[i]&1)
		{
			cout<<"NIE";
			return 0;
		}
	}
	for(i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=true;
			dfs(i);
			ins[s[hd]]--;
			hd--;
		}
	}
	cout<<gs;
	for(i=1;i<=gs;i++)
	{
		cout<<"\n"<<ans[i].size()-1;
		for(j=0;j<ans[i].size();j++)
		{
			cout<<" "<<ans[i][j];
		}
	}

	return 0;
}
```

---

## 作者：许多 (赞：0)

我们阅读题意不难发现，初始颜色和目标颜色相同的边完全可以删掉，因为如果要走这条边的话，必然要经过偶数次这条边。显然每两个环都可以选择不走这条边从而合并成一个环。故初始颜色和目标颜色相同的边删掉就可以。

下面就是一个比较裸的欧拉回路问题了。在一个无向图中，如果每个点的度数都是偶数则存在欧拉回路，如果每个节点可以走多次的话则必然存在一种方案一笔走完每一条边最后回到起点，这个起点是谁都可以。~~然而这个题阴间地说：对于一辆垃圾车， 除了起点以外不能跑两次。~~

没关系，我们可以分解成 $k$ 次欧拉回路，每次跑到一个走过的点就记录一下就可以，这个过程我们用 $dfs$ 维护，然后把走过的边删掉就可以。

# CODE


```cpp
struct Edge{
    int where,to,next,now,last;
    int vis;
}edge[M<<1];
int head[N],cnt,d[N];
void add(int u,int v){
    edge[cnt].to=v;
    edge[cnt].where=u;
    edge[cnt].next=head[u];
    edge[cnt].now=1;
    edge[cnt].vis=1;
    if(head[u]!=-1)
        edge[head[u]].last=cnt;
    head[u]=cnt;
    cnt++;
    return ;
}
int n,m;
vector<vector<int>>b;
int vis[N];
vector<int>nowedge;
void del(int now){
    edge[edge[now].last].next=edge[now].next;
    edge[now].vis=0;
    if(head[edge[now].where]==now)
        head[edge[now].where]=edge[now].next;
    if(edge[now].next!=-1)
        edge[edge[now].next].last=edge[now].last;
    return ;
}
int dfs(int now){
    if(vis[now]){
        nowedge.push_back(now);
        return now;
    }
    vis[now]=1;
    for(int i=head[now];i!=-1;i=edge[i].next)
        if(edge[i].vis){
            del(i);del(i^1);
            int goal=dfs(edge[i].to);
            nowedge.push_back(now);
            if(goal==now){
                b.push_back(nowedge);
                nowedge.clear();
            }
            else {
                vis[now]=0;
                return goal;
            }
        }
    return -1;
}
int main(){
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int a=read(),b=read(),s=read(),t=read();
        if(s==t)continue;
        add(a,b);add(b,a);
        d[a]++,d[b]++;
    }
    for(int i=1;i<=n;i++)
        if(d[i]&1){
            cout<<"NIE";
            return 0;
        }
    for(int i=1;i<=n;i++)
        dfs(i);
    printf("%d\n",b.size());
    for(int i=0;i<b.size();i++){
        printf("%d ",b[i].size()-1);
        for(int j=0;j<b[i].size();j++)
            printf("%d ",b[i][j]);
        puts("");
    }
    return 0;
}
```

---

## 作者：Rindong (赞：0)

# 思路

通过观察发现，对于不需要改变状态的道路，即 $s = t$ 的情况下，这种道路可以直接舍弃，并不会影响我们的答案。

比如考虑如下这张图：

```
9 10
1 2 0 1
2 3 0 1
3 4 0 1
4 5 0 1
5 6 0 1
6 7 0 1
7 8 0 1
8 9 0 1
9 1 0 1
3 7 0 0
```

发现 3 和 7 之间的边一开始就满足了条件，如果你硬要把它算进答案里，会得到下面的答案：

```
2
6 1 2 3 7 8 9 1
5 3 4 5 6 7 3
```

但是如果你当它不存在并不影响我们的正确性：

```
1
9 1 2 3 4 5 6 7 8 9 1
```

并且这样做有个好处就是我们不用处理这种特殊的边，毕竟不是每条 $s = t$ 的边都像这样可以存在两条路径恰好路过它，所以决定把这种边忽视。

回到题目，注意看这个描述：**除了起点以外不能跑两次**。仔细思考，这不是**欧拉回路**吗（不知道的该去补课了）？所以问题就变成了：在一个无向图中找出所有的欧拉回路。

但是这题还有个小坑，就是题目虽然要求的是欧拉回路，但是也要求了除了起点以外不能跑两次，而欧拉回路的路径中只保证每条边只经过一次，并不保证每个点只经过一次。因此我们可以改造一下我们的搜索，记录每个节点是否出现过，如果已经出现过，可以从之前的位置到当前位置作一个新的欧拉路径。

# 代码

注意个细节，由于每个点可能属于不止一个欧拉回路，所以记录欧拉回路的数组要开大一点，hack 来自[这篇帖子](https://www.luogu.com.cn/discuss/1006168)。

```cpp
#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 100005
#define MAX_M 2000005
struct Edge {
	int v, bind;
};
int idle = 1;
int head[MAX_N] = { 0 }, nex[MAX_M] = { 0 };
Edge edge[MAX_M] = { 0 };
void add(int u, int v, int b) {
	nex[idle] = head[u];
	head[u] = idle;
	edge[idle++] = { v, b };
}
int degree[MAX_N] = { 0 };
int blo = 0;
vector<int> block[MAX_N];
int id[MAX_N] = { 0 };
void dfs1(int node, int b) {
	id[node] = b;
	block[b].push_back(node);
	for (int ind = head[node]; ind; ind = nex[ind]) {
		int v = edge[ind].v;
		if (id[v]) continue;
		dfs1(v, b);
	}
}
bool vis[MAX_M] = { 0 };
int top = 0;
int stack[MAX_N] = { 0 };
int ans1 = 0;
vector<int> ans2[MAX_N << 2];
//标记前面是否出现过，在哪个下标出现的
int hit[MAX_N] = { 0 };
void dfs2(int u) {
	for (int& ind = head[u]; ind;) {
		int v = edge[ind].v;
		if (vis[ind]) {
			ind = nex[ind];
			continue;
		}
    //删边优化，如果一个图是单个点的超级自环，每次遍历同一个点的话会TLE
		vis[ind] = vis[ind + edge[ind].bind] = true;
		ind = nex[ind];
		dfs2(v);
	}
	if (hit[u]) {
		//发现一个新的欧拉回路
		ans1++;
		ans2[ans1].push_back(u);
		for (int x = hit[u] + 1; x <= top; x++) 
		    ans2[ans1].push_back(stack[x]), hit[stack[x]] = 0;
		ans2[ans1].push_back(u);
		top = hit[u] - 1;
	}
	stack[++top] = u;
	hit[u] = top;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int x = 1; x <= m; x++) {
		int u, v, s, t;
		scanf("%d%d%d%d", &u, &v, &s, &t);
		if (s == t) continue;
		add(u, v, 1);
		add(v, u, -1);
		degree[u]++, degree[v]++;
	}
	for (int x = 1; x <= n; x++) if (!id[x]) dfs1(x, ++blo);
	for (int x = 1; x <= blo; x++)
		for (auto it : block[x])
			if (degree[it] % 2) {
				printf("NIE");
				return 0;
			}
	for (int x = 1; x <= blo; x++) {
		if (block[x].size() < 2) continue;
		top = 0;
		dfs2(block[x][0]);
	}
	printf("%d\n", ans1);
	for (int x = 1; x <= ans1; x++) {
		printf("%d", ans2[x].size() - 1);
		for (auto it : ans2[x]) printf(" %d", it);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：zzhbpyy (赞：0)

**2024/11/26 更新**

## [POI2011 SMI-Garbage](https://www.luogu.com.cn/problem/P3520)

~~一篇题解记录这道写了三天的题。~~

容易发现，题目需要找到几个环使得一些边恰好经过一次。忽略掉不用改变颜色的边，题目就转化为找到覆盖剩下所有边的欧拉回路，所以无解情况也就是有点度数是奇数的情况。

但是欧拉回路中会有重复点，这里我们可以用栈维护当前经过的点，如果遍历到的点在栈中出现过，就弹栈记录答案，然后继续从该点跑欧拉回路。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int u,v,nxt;
}a[2000005];
int n,m,ct=1,deg[100005],head[100005],now[100005],ans;
bool vis[200005],vv[2000005];//vis记录是否在栈中
stack<int>s;
vector<int>res[1000005];
void add(int u,int v){
	a[++ct]={u,v,head[u]};
	head[u]=ct;
}
void dfs(int u){
	s.push(u);--deg[u];//到达一点度数减一，统计度数方便统计是否所有边都遍历到
	if(vis[u]){
		++ans;s.pop();res[ans].push_back(u);
		while(!s.empty()){
			if(s.top()==u)break;
			vis[s.top()]=false;
			res[ans].push_back(s.top());
			s.pop();
		}res[ans].push_back(u);
	}
	vis[u]=true;
	for(int i=now[u];i;i=now[u]){
		now[u]=a[i].nxt;
		if(vv[i]||vv[i^1])continue;
		vv[i^1]=vv[i]=true;--deg[u];//遍历下一个点时度数减一
		dfs(a[i].v);break;
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,u,v,s,t;i<=m;i++){
		cin>>u>>v>>s>>t;
		if(s==t)continue;//不用改的边忽略
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)if(deg[i]&1)cout<<"NIE",exit(0);//判无解
	for(int i=1;i<=n;i++)now[i]=head[i];
	for(int i=n;i>=1;i--)
		while(deg[i])deg[i]++,dfs(i);
	cout<<ans<<'\n';
	for(int i=1;i<=ans;i++){
		cout<<(int)res[i].size()-1<<' ';
		for(auto v:res[i])cout<<v<<' ';
		cout<<'\n';
	}
}
```

---

