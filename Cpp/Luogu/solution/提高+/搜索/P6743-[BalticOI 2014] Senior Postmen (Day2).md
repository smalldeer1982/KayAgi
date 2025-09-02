# [BalticOI 2014] Senior Postmen (Day2)

## 题目背景

# 滥用本题评测将被封号

## 题目描述

给定一张 $N$ 点 $M$ 边的无向图，求从中找出若干个环，使得：

- 这些环没有重复的边。
- 这些环覆盖了所有的点和边。

## 说明/提示

#### 样例说明

对于样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/z5q8d4du.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（38 pts）：$N \le 2000$，$M \le 10^5$。
- Subtask 2（17 pts）：$N,M \le 10^5$。
- Subtask 3（45 pts）：无特殊限制。

对于 $100\%$ 的数据，$3 \le N,M \le 5 \times 10^5$。

**本题使用 Special Judge。**

感谢 spj 提供者 @[tiger2005](https://www.luogu.com.cn/user/60864)。

#### 说明

翻译自 [BalticOI 2014 Day2 C Senior Postmen](https://boi.cses.fi/files/boi2014_day2.pdf)。

## 样例 #1

### 输入

```
10 15
1 3
5 1
2 3
9 2
3 4
6 3
4 5
7 4
4 8
5 7
8 5
6 7
7 8
8 10
10 9```

### 输出

```
2 3 4 5 8 10 9
7 8 4
1 5 7 6 3```

# 题解

## 作者：Starrykiller (赞：5)

[传送门](https://www.luogu.com.cn/problem/P6743)

调了整整两天才过 qvq，在此感谢@[北京](https://www.luogu.com.cn/user/322285)大佬！

可以在 [Starrykiller's blog](https://starrykiller.blog.luogu.org/solution-p6743) 中阅读，或许会有更好的阅读体验。

## 题意简述

给出一张图，将其分成若干个环，其中这些环没有重复的边，且这些环覆盖了所有的点和边。

## 解法

考虑搜索。

我们有如下性质：若一个图的所有节点的度数均为**偶数**，则我们可以将这个图按题目要求分成不同的环。

我们不妨这么考虑：任选一个点作为起点进行 dfs（前提是经过的边没有访问过），并对访问过的边进行标记。

在 dfs 过程中，设当前点为 $u$。

（1）dfs 完后（for 循环**结束后**），如果 $u$ 在栈中，这意味着我们之前已经访问过 $u$ 了，栈中的序列是这个样子的：$u, v_1, v_2, \cdots, v_n$。我们将 $v_1, v_2, \cdots, v_n$ 依次输出并出栈，取消标记，直到栈顶为 $u$ 为止，$v_1, v_2, \cdots, v_n$ 和点 $u$ 共同构成了一个环。

大部分人可能用 while 来实现出栈的过程，需要注意的是，循环结束的时候，需要**将栈顶的点**（即点 $u$）**一并输出并出栈**。否则这个环是不完整的。

最后将 $u$ 入栈，因为 $u$ **可能被多个环所包含**。

（2）若 $u$ 不在栈中，我们将 $u$ 入栈，并打上入栈标记。

这样直到 dfs 结束，我们就将图按题目的要求分成了一些互不相交的环。

## Tips

### Special Judge

该题目的 SPJ **并不会自动忽略行末空格**（除最后一个空行外），会导致判定数字时加上空格而“不符合数字的格式”从而 WA，需要特殊处理。

## 优化

（1）

考虑 dfs 的过程，当前节点为 $u$，要访问的点为 $v$，边 $u\to v$ 为 $e(u, v)$。

(a)若 $e(u,v)$ 被访问过了，以后就不会再访问到了。我们可以令 `head[u]=nxt[u]`。

(b)若 $e(u,v)$ 未被访问过，现在访问了，以后也不会再访问到了，同样可以令 `head[u]=nxt[u]`。

综上，我们在每次 for 循环时令 `head[u]=nxt[u]`。另外注意 `for` 循环更新为 `i=head[u]`，否则会导致效率大大降低。（TLE $\to \sim 120  \text{ms}$）

（2）使用 bitset 存储 vis 数组，或许可以提高效率和减少空间开销。

（3）合理使用快读和快写。

其实最重要的是优化 $1$，有了优化 $1$ 之后其他都不重要，没有优化 $1$ 只有优化 $2$、$3$ 则很难 AC（当然也可能是我太菜了）。

## 代码

不要 copy 代码哦 www

```cpp
const int MAXN=5e5+10, MAXM=1e6+10;
int n, m;
struct {
    int nxt, to;
} e[MAXM]; int head[MAXN], tot=1; // 双向边优化
inline void add(int u, int v) {
    e[++tot].to=v, e[tot].nxt=head[u], head[u]=tot;
}
bitset<MAXM> vis, in_stack;
int stk[MAXN], r;
inline void dfs(int u) { // 感谢rzy神！！！
    for (int i=head[u]; i; i=head[u]) {
    // 注意这里的循环赋值
        int to=e[i].to;
        head[u]=e[i].nxt; // 优化1
        if (vis[i]) continue;
        vis[i]=vis[i^1]=true;
        dfs(e[i].to);
    }
    // 进出栈过程
    if (in_stack[u]) {
        while (stk[r]!=u && r) {
            in_stack[stk[r]]=false;
            write(stk[r--]); putchar(' ');
        }
        write(stk[r--]); putchar('\n'); // 本题专属的SPJ优化
    }
    else in_stack[u]=true;
    stk[++r]=u;
}
int main() {
    n=read(), m=read();
    int x, y;
    for (int i=1; i<=m; ++i) {
        x=read(), y=read();
        add(x,y), add(y,x);
    }
    dfs(1);
    return 0;
}
```

这是 sk 酱的第一篇题解哦~

**一定会有错误或者不足之处，欢迎大家指出，也请大家多多见谅 qaq**

## Reference

[Solution on DM::OJ](https://dmoj.ca/problem/btoi14p6/editorial)

[Offical solution for BalticOI 2014](https://github.com/boi-2014/tasks) （虽然我没看懂）（悲）


---

## 作者：GFyyx (赞：3)

## 解题思路
直接 DFS 找环。但是题目要求环不能有相同边，我们可以开一个数组 $evis$ 记录一下已用边，便于遍历。

再用栈维护已遍历的点，若新找到的点已经在栈中，则形成了环。直接退栈知道栈顶为环的根（即刚刚 DFS 所遍历到的点）。

### DFS 代码
```cpp
void dfs(int u){
	for(register int i=head[u]; i; i=e[i].nxt){
		int v=e[i].to;
		if(evis[i]) continue;
		evis[i]=evis[i^1]=1;
		dfs(v);
	}
	if(isi[u]){
		while(st.top()!=u){
			cout << st.top() << " ";
			isi[st.top()]=0;
			st.pop();
		}
		cout << st.top() << endl;
	}
	else st.push(u),isi[u]=1;
}
```

交上去，~~恭喜你，拿下 55 分。~~

### 代码优化
度数为 $n$ 的点 $x$ 会被遍历 $n$ 次，每次访问更新 ```head[x]```，指向未访问的边，避免每次重复遍历访问过的边。

具体实现看如下代码（附有注释）。

## AC Code
```cpp
#include <iostream>
#include <stack>
using namespace std;
struct edge{int nxt,to;}e[1919810];
int tot,head[114514<<3];//链式前向星
inline void add(int x,int y){e[++tot]={head[x],y};head[x]=tot;}
int n,m;
stack<int> st;//用栈维护已遍历的点及其顺序 
bool evis[1919810],isi[114514<<3];//数组分别表示边已使用，点已入栈
inline void dfs(int u){
	for(register int i=head[u]; i; i=head[u]){
		int v=e[i].to;head[u]=e[i].nxt;//边不能重复走，直接干掉
		if(evis[i]) continue;
		if(i&1) evis[i]=evis[i+1]=1;
		else evis[i]=evis[i-1]=1;//i分奇偶两种情况标记已走边 
		dfs(v);
	}
	if(isi[u]){//形成环 
		while(st.top()!=u){
			cout << st.top() << " ";
			isi[st.top()]=0;
			st.pop();//退栈输出 
		}
		cout << st.top() << endl;
	}
	else st.push(u),isi[u]=1;//标记入栈 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	int a,b;
	for(register int i=1; i<=m; i++){
		cin >> a >> b;
		add(a,b);add(b,a);//存边 
	}
	dfs(1);
	return 0;
}
```


---

## 作者：gghack_Nythix (赞：2)

## 前言:
感觉并不是很难，主要问题在于时间复杂度优化，想明白了很简单。

[题目传送门](https://www.luogu.com.cn/problem/P6743)

## 分析:

刚开始看到这个题目，我是觉得很水的，于是准备打深搜水过去，毕竟时间可是给了五秒。

#### 暴力方法:

因为使用过的边不能重复用，所以遍历到这一条边标记一下就好了，下次不搜他。

至于环的判定，明显是一个点被重复搜索过两次才会形成一个环，那么我们如果搜到一个重复的点，就可以把他之前直到再次回到本身的点全部输出，用一个栈可以很方便的维护。

[血压升高的评测记录](https://www.luogu.com.cn/record/133532808)

以下是代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1 << 20],*p1,*p2;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2)?0:*p1++)
int read(){
	int x = 0,w = 1;
	char c = 0;
	while(c < '0' || c > '9'){
		if(c == '-')w = -1;
		c = getc();
	}
	while(c <= '9' && c >= '0'){
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getc();
	}
	return x * w;
}
inline void print(register long long x){
	if(x < 0){
		x = -x;
		putchar('-');
	}
	if(x > 9)print(x / 10);
	putchar(x % 10 + 48);
}
struct node{
	int v,id;
};
vector<node>g[1919810];
int n,m,cnt;
stack<int>st;
bool used[1919810],dused[1919810];
void dfs(int now){
	for(register int i = 0;i < signed(g[now].size());++i){
		node son = g[now][i];
		if(used[son.id])continue;
		if(son.id & 1)used[son.id] = used[son.id + 1] = 1;//双向边两个方向都要标记。
		else used[son.id] = used[son.id - 1] = 1;
		dfs(son.v);
	}
	if(dused[now]){
		while(st.top() != now){
			print(st.top());
			putchar(' ');
			dused[st.top()] = 0;
			st.pop();
		}
		print(st.top());
		putchar('\n');
	}
	else dused[now] = 1,st.push(now);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	n = read(),m = read();
	for(register int i = 1;i <= m;++i){
		register int u = read(),v = read();
		g[u].push_back(node{v,++cnt});
		g[v].push_back(node{u,++cnt});

	}
	dfs(1);
	return 0;
}
```

当我寻找超时原因时，我貌似发现了一个问题：当我输出当前遍历到的点的时候发现：部分点被重复覆盖了。也就是说我们搜到了一些没用的点。

这个时候我们应该怎么办呢？自然是剪枝。

（此处优化做法来源于@ MoriyaSuwako 大佬）

可以发现邻接表的深搜顺序一定是先搜小的再搜大的，因此我们可以放心的记录搜到的点，下次直接不搜他（也就是将循环起始点慢慢增大）。

然后还可以直接利用记录边的数组，让遍历儿子的变量每次等于当前父亲的遍历过的点的数量，这样子也可以跳过一部分的重复点。因为在更深层的深搜中我们肯定使用过这一堆点了，直接跳过就可以了。

代码：

```cpp
#include<iostream>
#include<stack>
#include<vector>
#include<cstring>
using namespace std;
char buf[1 << 20],p1,p2;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2)?0:*p1++)
int read(){
	int x = 0,w = 1;
	char c = 0;
	while(c < '0' || c > '9'){
		if(c == '-')w = -1;
		c = getc();
	}
	while(c <= '9' && c >= '0'){
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getc();
	}
	return x * w;
}
inline void print(register int x){
	if(x < 0){
		x = -x;
		putchar('-');
	}
	if(x > 9)print(x / 10);
	putchar(x % 10 + 48);
}
struct node{
	int v,id;
};
vector<node>g[1919810];
int n,m,cnt;
stack<int>st;
bool used[1919810],dused[1919810];
int ddd[1919810];
inline void dfs(int now){
	for(register int i = ddd[now];i < signed(g[now].size());i = ddd[now]){
		++ddd[now];
		node son = g[now][i];
		if(used[son.id])continue;
		if(son.id & 1)used[son.id] = used[son.id + 1] = 1;
		else used[son.id] = used[son.id - 1] = 1;
		dfs(son.v);
	}
	if(dused[now]){
		while(st.top() != now){
			print(st.top());
			putchar(' ');
			dused[st.top()] = 0;
			st.pop();
		}
		print(st.top());
		putchar('\n');
	}
	else dused[now] = 1,st.push(now);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	n = read(),m = read();
	for(register int i = 1;i <= m;++i){
		register int u = read(),v = read();
		g[u].push_back(node{v,++cnt});
		g[v].push_back(node{u,++cnt});
	}
	dfs(1);
	return 0;
}
```

---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6743)。

## 思路

对于本题，我们只需保证经过每条边并且每条边只被一个唯一的环经过一次即可。

我们只需在 DFS 中将边标记，这样我们就能保证经过的边不同了。

回溯时将经过的点加入栈内，并将该点标记为入栈元素，如果当前回溯到的点 $u$ 已经在栈内了，那么不断弹出栈顶，直到栈顶元素为 $u$，在把栈顶元素弹出，这些弹出的点形成了一个合法的环，不断这样遍历下去，我们就能找到所有的环。

当然，这样还是不能通过，我们只保证了每条边只被经过一次，而不保证每个点只经过一次，如果一个点有度数很大，那么时间复杂度将退化到 $O(m^2)$。

由于题目已经保证每条边只能被经过一次，所以遍历的时候我们不妨记录一下每个点当前遍历边 `now[u]`，我们只需在遍历这个点的时候从 `now[u]` 开始遍历边即可。

时间复杂度 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=2e6+7;
int n,m,now[Maxn];
int stk[Maxn],tot=1,tp;
vector<pair<int,int> >e[Maxn];

bool vis[Maxn],Instk[Maxn];

void DFS(int u){
	for(int i=now[u];i<e[u].size();i=now[u]){
		auto v=e[u][i];
		now[u]=i+1;
		if(vis[v.second]) continue;
		vis[v.second]=vis[v.second^1]=1;
		DFS(v.first);
	}
	if(Instk[u]){
		while(stk[tp]!=u){
			Instk[stk[tp]]=0;
			printf("%d ",stk[tp]);
			tp--;
		}
		printf("%d\n",stk[tp]);tp--;
	}
	else Instk[u]=1;
	stk[++tp]=u;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		e[u].emplace_back(v,++tot),
		e[v].emplace_back(u,++tot);
	DFS(1);
	return 0;
}



```


---

## 作者：ZPB2011 (赞：0)

# [Senior Postmen](https://www.luogu.com.cn/problem/P6743)

## 思路

一道爆搜优化题。

因为这题时间给了整整五秒，于是立刻想到了 `dfs`。

暴力就是使用过的边不能用，标记一下然后存进栈即可，如果搜到一个之前搜过的点，就输出栈一直输出到这个点。

然后你就得到了 55pts，[让我红温的提交记录](https://www.luogu.com.cn/record/181297482)。

超时的原因是搜了太多没用的点，我们可以利用一个数组，让儿子节点每次都等于父亲节点的遍历过的点的数量，这样就可以跳过一部分没用的点。

## Code

```cpp
#include <iostream>
#include <vector>
#include <stack>
#define pii pair<int, int>
#define fir first
#define sec second
#define endl '\n'
using namespace std;

const int N = 1e6 + 5;

int cnt, a[N];
bool vis[N], viss[N];
vector<pii> g[N];
stack<int> stk;

void dfs(int u) {
	for(int i = a[u]; i < g[u].size(); i = a[u]) {
		int v = g[u][i].fir, id = g[u][i].sec;
		a[u]++;//优化
		if(!vis[id]) {
			if(id % 2 == 1) vis[id] = vis[id + 1] = true;
			else vis[id] = vis[id - 1] = true;
			dfs(v);
		}
	}
	if(viss[u]) {//输出环
		while(stk.top() != u) {
			cout << stk.top() <<' ';
			viss[stk.top()] = false;
			stk.pop();
		}
		cout << stk.top() << endl;
	}
	else {//存入栈
		viss[u] = true;
		stk.push(u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back({v, ++cnt});
		g[v].push_back({u, ++cnt});
	}
	dfs(1);
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题目描述

[P6743 BalticOI 2014 Day2 Senior Postmen](https://www.luogu.com.cn/problem/P6743)

# 题目解法

看到题目想到直接爆搜。

根据题意，只要找出所有互不相交的简单环即可。题目保证了合法性。

跑 dfs，每次到达一个点 $u$ 就将其放入栈 $stk$ 中。如果栈 $stk$ 中已经有点 $u$，那么就弹栈。

同时每经过一条边 $i$，那么就将 $vis_i$ 设为 $1$，防止重复计数。

~~做法和 Tarjan 求联通分量有些相似。~~

所以：

```cpp
vector<int> stk;
int ins[maxn], vis[maxn<<1];

void dfs(int u)
{
    for(int i=head[u];i;i=nxt[i])
    {
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        dfs(to[i]);
    }
    if(ins[u])
    {
        while(stk.back()!=u)
        {
            cout<<stk.back()<<' ';
            ins[stk.back()]=0;
            stk.pop_back();
        }
        return cout<<stk.back()<<'\n', void();
    }
    ins[u]=1;
    stk.emplace_back(u);
}
```

喜提 $\color{orange} \textsf{55pts}$。**TLE** on #22 #24

------

仔细一想，因为每条边只能被使用一次，所以每次可以将 $head_u$ 更新为 $nxt_i$。

修改后：（dfs 函数第三行）

```cpp
    for(int i=head[u];i;i=head[u]=nxt[i])
```

还是 $\color{orange} \textsf{55pts}$。只是变成了 **TLE** on #22

-----

经过一通乱改，最后采取在 dfs 其余节点之前将 $head_u$ 更新为 $nxt_i$，所以循环处将 $i$ 更新为 $head_u$。

修改后：（以及写的极丑的栈）

```cpp
int stk[maxn], *top=stk;
int ins[maxn], vis[maxn<<1];

void dfs(int u)
{
    for(int i=head[u];i;i=head[u])
    {
        head[u]=nxt[i];
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        dfs(to[i]);
    }
    if(ins[u])
    {
        while(*top!=u)
        {
            cout<<*top<<' ';
            ins[*top--]=0;
        }
        return cout<<*top<<'\n', void();
    }
    ins[*++top=u]=1;
}
```

成功 $\color{green} \textsf{AC}$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 500005

int head[maxn], to[maxn<<1], nxt[maxn<<1], tot=1;
void link(int u, int v)
{
    to[++tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}

int stk[maxn], *top=stk;
int ins[maxn], vis[maxn<<1];

void dfs(int u)
{
    for(int i=head[u];i;i=head[u])
    {
        head[u]=nxt[i];
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        dfs(to[i]);
    }
    if(ins[u])
    {
        while(*top!=u)
        {
            cout<<*top<<' ';
            ins[*top--]=0;
        }
        return cout<<*top<<'\n', void();
    }
    ins[*++top=u]=1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1, u, v;i<=m;i++)
    {
        cin>>u>>v;
        link(u, v);
        link(v, u);
    }
    dfs(1);
}
```

---

## 作者：封禁用户 (赞：0)

# [BalticOI 2014 Day2] Senior Postmen 题解

一开始觉得是道暴力遍历题，最后超时了好几发。

## 思路

发现出栈顺序关系每一个环。

每次重复出栈即为一个环，所以可以通过 dfs 遍历找环输出。

由于题目要求用完所有的边且不重复，每次将用过的边标记一下即可。

写完交上去发现超时了，想不出来更好的做法。

所以只能考虑优化 dfs。

在调试的时候发现每次遍历一个点会遍历许多重复的边，所以实际上我们应该每一次都跳过之前遍历的边。

具体操作为改变链式前向星一开始遍历的边的编号，即 $nex_i \to head_i$。

最后注意两个点：

1. 标记边的时候，由于是双向边，所以两条边都不能用了，都要标记。

2. 在输出环的时候需要多输出一个，因为重复出栈的元素本身也在环中，并且这个时候并不需要`top--`。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
#define inf 0x3f3f3f3f
#define il inline
#define db double
#define F(i,a,b) for(re int i=(a);i<=(b);i++)
#define f(i,a,b) for(re int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define kg putchar(' ')
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
const int N=1e6+10;
struct node
{
	int nex;
	int to;
}a[N];
int tot,head[N];
il void add(int u,int v)
{
	a[++tot].nex=head[u];
	head[u]=tot;
	a[tot].to=v;
}
bool vis[N],v[N];//vis标记是否遍历过这个边，v标记是否在栈中 
int st[N],top;//栈 
void dfs(int u)
{
	for(int i=head[u];i;i=head[u])
	{
		head[u]=a[i].nex;//更新head，让下次从下一个点开始遍历 
		if(vis[i]) continue;//已经遍历过 
		vis[i]=vis[i&1?i+1:i-1]=1;//双向边所以两个方向的边都要标记 
		dfs(a[i].to);
	}
	if(v[u])
	{
		int y=st[top];
		while(y!=u)
		{
			v[y]=0;
			print(y),kg;
			y=st[--top];
		}
		put(st[top]);
	}
	else
	{
		v[u]=1;
		st[++top]=u;
	}
}
int n,m;
int x,y;
il void solve()
{
	n=read(),m=read();
	F(i,1,m)
	{
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1);
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```



---

## 作者：orpg (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P6743)
### 解答思路
我们考虑搜索，我们遍历所有边，以边是否访问为判断条件搜索。

我们用一个栈来维护，当环上的点遍历完后，就会出现一个相同的点，我们把区间输出，就是结果了。

![](https://cdn.luogu.com.cn/upload/image_hosting/j81m0q9q.png)

入上图，dfs 遍历顺序为：$1,2,3,4,5,3,1,6,7,3$。出栈：$1,3,7,6,3,5,4,3,2,1$。
则我们得到的环就是 $(3,6,7),(3,4,5),(1,2,3)$。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=5e5+5;
int n,m;
struct node{
    int to,nxt;
}ed[maxn<<1];
int head[maxn<<1];
short vis[maxn<<1];
stack<int> st;
short visn[maxn];
int tot;
inline void add(int u,int v){
    ed[++tot].to=v;
    ed[tot].nxt=head[u];
    head[u]=tot;
}
inline void dfs(int u){
    for(int i=head[u];i;i=head[u]){
        int to=ed[i].to;
        head[u]=ed[i].nxt;
        if(vis[i]==1) continue;
        if(i&1)vis[i]=vis[i+1]=1;
        else vis[i]=vis[i-1]=1;
        dfs(to);
    }
    if(visn[u]==1){//u点存在
        while(st.top()!=u){
            cout<<st.top()<<" ";
            visn[st.top()]=0;
            st.pop();
        }
        cout<<st.top()<<'\n';
        // st.pop();
    }
    else{
        st.push(u);
        visn[u]=1;
    }
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(register int a,b,i=1;i<=m;i++){
        cin>>a>>b;
        add(a,b);add(b,a);
    }
    dfs(1);
    return 0;
}
```


---

## 作者：Claire0918 (赞：0)

前置知识：tarjan SCC（思想即可）。

本题要求找环，可以使用类似 tarjan 的 DFS 解决。

特别的是，本题 `vis` 存储的不是点是否经过，而是边是否经过。

DFS Code: 
```cpp
inline void dfs(int u){
	for (int i = head[u]; i; i = head[u]){
		const int v = edge[i].v;
		if (!vis[i]){
			vis[i] = vis[i ^ 1] = true;
			dfs(v);
		}
	}
	if (instack[u]){
		while (!stk.empty() && stk.top() != u){
			instack[stk.top()] = false;
			printf("%d ", stk.top());
			stk.pop();
		}
		if (!stk.empty()){
			printf("%d\n", stk.top());
			stk.pop();
		}
	}else{
		instack[u] = true;
	}
	stk.push(u);
}
```

但是，本题数据~~毒瘤~~很大，需要加入优化。

1. 因为边不能重复经过，所以可以在走过某条边后用 `head[u] = edge[i].nex` 排除。
2. `vis` 和 `instack` 可以使用 `bitset`，优化内存利用和查询时间。
3. 可以使用快读快写~~虽然不用也能过~~。

Code: 
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 5e5 + 10, maxm = 5e5 + 10;

struct{
	int v, nex;
} edge[maxm << 1];

int n, m;
bitset<maxm << 1> vis, instack;
int head[maxn], top = 1;
stack<int> stk;

inline void add(int u, int v){
	edge[++top].v = v;
	edge[top].nex = head[u];
	head[u] = top;
}

inline void dfs(int u){
	for (int i = head[u]; i; i = head[u]){
		const int v = edge[i].v;
		head[u] = edge[i].nex;
		if (!vis[i]){
			vis[i] = vis[i ^ 1] = true;
			dfs(v);
		}
	}
	if (instack[u]){
		while (!stk.empty() && stk.top() != u){
			instack[stk.top()] = false;
			printf("%d ", stk.top());
			stk.pop();
		}
		if (!stk.empty()){
			printf("%d\n", stk.top());
			stk.pop();
		}
	}else{
		instack[u] = true;
	}
	stk.push(u);
}

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1);

return 0;
}
```

---

